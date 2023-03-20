# Copyright (c) 2023 Nordic Semiconductor ASA
# SPDX-License-Identifier: Apache-2.0

import argparse
from pathlib import Path
import pickle
import re
import sys
from typing import Optional, List, Dict, Tuple

from devicetree import edtlib
from runners.core import ZephyrBinaryRunner, RunnerCaps, RunnerConfig, BuildConfiguration


_UICR_ADDR = {
    "CP_APPLICATION": 0x0FFF8000,
    "CP_NETWORK": 0x0FFFA000,
}

_DOM2COP = {
    "application": "CP_APPLICATION",
    "radiocore": "CP_NETWORK",
    "ppr": "CP_APPLICATION",
    "secure": "CP_SECURE",
    "sysctrl": "CP_APPLICATION",
}


class NrfJprog54ProgrammerBinaryRunner(ZephyrBinaryRunner):
    """Runner front-end for nrfjprog (nRF54 SoCs)."""

    def __init__(
        self,
        cfg: RunnerConfig,
        dev_id: Optional[str],
        erase_storage: Optional[bool],
    ) -> None:
        super().__init__(cfg)

        self._dev_id = dev_id
        self._erase_storage = erase_storage

        self.require("nrfjprog")
        self._check_version()

    @classmethod
    def name(cls):
        return "nrfjprog54"

    @classmethod
    def capabilities(cls):
        return RunnerCaps(commands={"flash"}, dev_id=True)

    @classmethod
    def do_add_parser(cls, parser):
        parser.add_argument("--erase-storage", action="store_true",
                            help="Erase storage partition/s")

    @classmethod
    def do_create(
        cls, cfg: RunnerConfig, args: argparse.Namespace
    ) -> "NrfJprog54ProgrammerBinaryRunner":
        return NrfJprog54ProgrammerBinaryRunner(
            cfg,
            dev_id=args.dev_id,
            erase_storage=args.erase_storage,
        )

    def do_run(self, command: str, **kwargs):
        if command != "flash":
            raise RuntimeError(f"Unsupported command: {command}")

        images, storage = self._discover()

        self.logger.info("Clearing UICRs")
        self._clear_uicr("CP_NETWORK")
        self._clear_uicr("CP_APPLICATION")

        if self._erase_storage and storage:
            self.logger.info("Erasing storage")
            self._nrfjprog([
                "--erasepage",
                f"0x{storage[0]:08x}-0x{storage[1]:08x}"
            ])

        for domain, image in images.items():
            self.logger.info(f"Programming {domain} image")
            self._program(_DOM2COP[domain], image)

        self._nrfjprog(["--pinreset"])

    def _check_version(self) -> None:
        version = self.check_output(["nrfjprog", "--version"])
        version = version.decode(sys.getdefaultencoding()).strip().splitlines()

        m = re.match(r"nrfjprog version: (\d+)\.(\d+)\.(\d+) (\w+)", version[0])
        nrfjprog_v = tuple(int(i) for i in m.groups()[0:3])
        if nrfjprog_v < (10, 21, 0) or m.group(4) not in ("internal", "haltium"):
            raise RuntimeError(f"Unsupported nrfjprog version: {version[0]}")

    def _discover(self) -> Tuple[Dict[str, Path], Optional[Tuple[int, int]]]:
        images = dict()
        storage = None

        for p in Path(self.cfg.build_dir).glob("**/zephyr/zephyr.hex"):
            domain = BuildConfiguration(p.parents[1]).get("CONFIG_SOC_DOMAIN_NAME")

            with open(p.parent / "edt.pickle", "rb") as f:
                edt = pickle.load(f)

            s = edt.label2node.get("storage_partition")
            if s:
                start = s.parent.parent.regs[0].addr | s.regs[0].addr
                size = s.regs[0].size
                storage = (start, start + size)

            merged_image = p.parent / "uicr_merged.hex"
            if merged_image.exists():
                image = merged_image
            else:
                image = p

            images[domain] = image

        return images, storage

    def _nrfjprog(self, args: List[str]) -> None:
        cmd = ["nrfjprog", "-f", "nrf54h"]
        if self._dev_id:
            cmd += ["--snr", self._dev_id]
        cmd += args

        self.check_call(cmd)

    def _clear_uicr(self, coprocessor: str) -> None:
        cmd = [
            "--coprocessor",
            coprocessor,
            "--erasepage",
            f"0x{_UICR_ADDR[coprocessor]:08x}",
        ]

        self._nrfjprog(cmd)

    def _program(self, coprocessor: str, hexfile: Path) -> None:
        cmd = [
            "--coprocessor",
            coprocessor,
            "--program",
            str(hexfile),
            "--verify",
        ]

        self._nrfjprog(cmd)
