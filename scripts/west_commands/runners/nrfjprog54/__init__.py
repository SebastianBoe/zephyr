# Copyright (c) 2023 Nordic Semiconductor ASA
# SPDX-License-Identifier: Apache-2.0

import argparse
from pathlib import Path
import re
import sys
from typing import Optional, List

from runners.core import ZephyrBinaryRunner, RunnerCaps, RunnerConfig


class NrfJprog54ProgrammerBinaryRunner(ZephyrBinaryRunner):
    """Runner front-end for nrfjprog (nRF54 SoCs)."""

    def __init__(self, cfg: RunnerConfig, dev_id: Optional[str]) -> None:
        super().__init__(cfg)

        self._dev_id = dev_id

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
        pass

    @classmethod
    def do_create(
        cls, cfg: RunnerConfig, args: argparse.Namespace
    ) -> "NrfJprog54ProgrammerBinaryRunner":
        return NrfJprog54ProgrammerBinaryRunner(cfg, dev_id=args.dev_id)

    def do_run(self, command: str, **kwargs):
        if command != "flash":
            raise RuntimeError(f"Unsupported command: {command}")

        secdom = (
            Path(self.cfg.build_dir)
            / "secdom"
            / "src"
            / "secdom-build"
            / "zephyr"
            / "zephyr.hex"
        )
        if not secdom.exists():
            raise RuntimeError("Secure domain firmware image not found")

        sysctrl = (
            Path(self.cfg.build_dir)
            / "sysctrl"
            / "src"
            / "sysctrl-build"
            / "zephyr"
            / "uicr_merged.hex"
        )
        if not sysctrl.exists():
            raise RuntimeError("System controller firmware image not found")

        app = Path(self.cfg.build_dir) / "zephyr" / "uicr_merged.hex"
        if not app.exists():
            raise RuntimeError("Application firmware image not found")

        ppr = Path(self.cfg.build_dir) / "remote" / "zephyr" / "zephyr.hex"
        radio = Path(self.cfg.build_dir) / "hci_rpmsg" / "zephyr" / "uicr_merged.hex"

        # clear all UICR
        self._clear_uicr("CP_SYSCTRL")
        self._clear_uicr("CP_APPLICATION")
        self._clear_uicr("CP_NETWORK")

        # program images
        self._program("CP_SECURE", secdom)
        self._program("CP_SYSCTRL", sysctrl)
        self._program("CP_APPLICATION", app)

        if radio.exists():
            self._program("CP_NETWORK", radio)

        if ppr.exists():
            self._program("CP_PPR", ppr)

        self._reset()

    def _check_version(self) -> None:
        version = self.check_output(["nrfjprog", "--version"])
        version = version.decode(sys.getdefaultencoding()).strip().splitlines()

        m = re.match(r"nrfjprog version: (\d+)\.(\d+)\.(\d+) (\w+)", version[0])
        nrfjprog_v = tuple(int(i) for i in m.groups()[0:3])
        if nrfjprog_v < (10, 20, 2) or m.group(4) != "haltium":
            raise RuntimeError(f"Unsupported nrfjprog version: {version[0]}")

    def _nrfjprog(self, args: List[str]) -> None:
        cmd = ["nrfjprog", "-f", "nrf54h"]
        if self._dev_id:
            cmd += ["--snr", self._dev_id]
        cmd += args

        self.check_call(cmd)

    def _reset(self) -> None:
        self._nrfjprog(["--pinreset"])

    def _clear_uicr(self, coprocessor: str) -> None:
        uicr = Path(__file__).parent / f"clear_UICR_{coprocessor[3:]}.hex"
        if not uicr.exists():
            raise FileNotFoundError(f"UICR not found: {uicr}")

        self._nrfjprog(
            [
                "--coprocessor",
                coprocessor,
                "--program",
                str(uicr),
                "--sectorerase",
                "--verify",
            ]
        )

    def _program(self, coprocessor: str, hexfile: Path) -> None:
        self._nrfjprog(
            [
                "--coprocessor",
                coprocessor,
                "--program",
                str(hexfile),
                "--sectorerase",
                "--verify",
            ]
        )
