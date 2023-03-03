# Copyright (c) 2023 Nordic Semiconductor ASA
# SPDX-License-Identifier: Apache-2.0

import argparse
from pathlib import Path
import re
import sys
from typing import Optional, List

from runners.core import ZephyrBinaryRunner, RunnerCaps, RunnerConfig


_UICR_ADDR = {
    "CP_APPLICATION": 0x0FFF8000,
    "CP_NETWORK": 0x0FFFA000,
}


class NrfJprog54ProgrammerBinaryRunner(ZephyrBinaryRunner):
    """Runner front-end for nrfjprog (nRF54 SoCs)."""

    def __init__(
        self,
        cfg: RunnerConfig,
        dev_id: Optional[str],
        bicr: Optional[str],
        secdom: Optional[str],
        sysctrl: Optional[str],
        radio: Optional[str],
        ppr: Optional[str],
    ) -> None:
        super().__init__(cfg)

        self._dev_id = dev_id
        self._bicr = Path(bicr) if bicr else None
        self._secdom = Path(secdom) if secdom else None
        self._sysctrl = Path(sysctrl) if sysctrl else None
        self._radio = Path(radio) if radio else None
        self._ppr = Path(ppr) if ppr else None

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
        parser.add_argument("--bicr", help="Path to BICR")
        parser.add_argument("--secdom", help="Path to secure domain image")
        parser.add_argument("--sysctrl", help="Path to system controller image")
        parser.add_argument("--radio", help="Path to radio core image")
        parser.add_argument("--ppr", help="Path to PPR image")

    @classmethod
    def do_create(
        cls, cfg: RunnerConfig, args: argparse.Namespace
    ) -> "NrfJprog54ProgrammerBinaryRunner":
        return NrfJprog54ProgrammerBinaryRunner(
            cfg,
            dev_id=args.dev_id,
            bicr=args.bicr,
            secdom=args.secdom,
            sysctrl=args.sysctrl,
            radio=args.radio,
            ppr=args.ppr,
        )

    def do_run(self, command: str, **kwargs):
        if command != "flash":
            raise RuntimeError(f"Unsupported command: {command}")

        secdom = self._secdom or (
            Path(self.cfg.build_dir)
            / "secdom"
            / "src"
            / "secdom-build"
            / "zephyr"
            / "zephyr.hex"
        )

        sysctrl = self._sysctrl or (
            Path(self.cfg.build_dir)
            / "sysctrl"
            / "src"
            / "sysctrl-build"
            / "zephyr"
            / "uicr_merged.hex"
        )

        radio = (
            self._radio
            or Path(self.cfg.build_dir) / "hci_rpmsg" / "zephyr" / "uicr_merged.hex"
        )

        ppr = self._ppr or Path(self.cfg.build_dir) / "remote" / "zephyr" / "zephyr.hex"

        app = Path(self.cfg.build_dir) / "zephyr" / "uicr_merged.hex"
        if not app.exists():
            raise FileNotFoundError(f"Application firmware image not found: {app}")

        self.logger.info("Clearing UICRs")
        self._clear_uicr("CP_NETWORK")
        self._clear_uicr("CP_APPLICATION")

        try:
            if self.build_conf.get("CONFIG_SOC_DOMAIN_NAME") == "application":
                self.logger.info("Programming application core")
                self._program("CP_APPLICATION", app)

                if radio.exists():
                    self.logger.info("Programming radio core")
                    self._program("CP_NETWORK", radio)
            else:
                self.logger.info("Programming radio core")
                self._program("CP_NETWORK", app)

            if ppr.exists():
                self.logger.info("Programming PPR core")
                # NOTE: s/CP_APPLICATION/CP_PPR once programmer is fixed
                self._program("CP_APPLICATION", ppr)

            if secdom.exists():
                self.logger.info("Programming secure domain")
                self._program("CP_SECURE", secdom)

            if sysctrl.exists():
                self.logger.info("Programming system controller")
                # NOTE: s/CP_APPLICATION/CP_SYSCTRL once programmer is fixed
                self._program("CP_APPLICATION", sysctrl)
        finally:
            if self._bicr:
                self.logger.info("Programming BICR")
                self._program("CP_APPLICATION", self._bicr)

        self._reset()

    def _check_version(self) -> None:
        version = self.check_output(["nrfjprog", "--version"])
        version = version.decode(sys.getdefaultencoding()).strip().splitlines()

        m = re.match(r"nrfjprog version: (\d+)\.(\d+)\.(\d+) (\w+)", version[0])
        nrfjprog_v = tuple(int(i) for i in m.groups()[0:3])
        if nrfjprog_v < (10, 21, 0) or m.group(4) not in ("internal", "haltium"):
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
        cmd = [
            "--coprocessor",
            coprocessor,
            "--erasepage",
            f"{_UICR_ADDR[coprocessor]}",
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
