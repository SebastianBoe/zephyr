#!/usr/bin/env python3
#
# Copyright (c) 2021 Nordic Semiconductor ASA
# SPDX-License-Identifier: Apache-2.0

import os
import subprocess

from west.commands import WestCommand
from west import log
from build_helpers import find_build_dir
from zcmake import CMakeCache
from zephyr_ext_common import ZEPHYR_BASE


NRFX_BUILD     = f"{str(ZEPHYR_BASE)}/../modules/hal/nordic_haltium/nrfx-build"
NRFX_MDK       = f"{str(ZEPHYR_BASE)}/../modules/hal/nordic_haltium/nrfx/mdk"
YAML_FILE      = "example.yaml"
YAML_COMMAND   = f"python3 {NRFX_BUILD}/yaml/scripts/merge_yaml.py"
YAML_ARGUMENTS = " -i {incoming} -o {outgoing} -d {device}"
UICR_COMMAND   = f"python3 {NRFX_BUILD}/libraries/per_hex_gen/scripts/icr_hex_gen.py"
UICR_ARGUMENTS = " -i {incoming} -s {svd_file} -b {uicr_address} -o {outgoing}"

class Uicr(WestCommand):

    def __init__(self):
        super().__init__(
            'uicr',
            'Generate UICR hex for SecDomFW',
            'Generate UICR hex for SecDomFW using merge_yaml.py and per_hex_gen.')
        self.build_dir = None
        self.source_dir = None
        self.cache = None
        self.board = None


    def do_add_parser(self, parser_adder):
        parser = parser_adder.add_parser(self.name,
                                         help=self.help,
                                         description=self.description)
        return parser

    def do_run(self, args, unknown_args):
        self.build_dir = find_build_dir(None, guess=True)
        if not self.build_dir:
            log.die("Couldn't determine Zephyr build directory.")

        self.cache = CMakeCache.from_build_dir(self.build_dir)
        if not self.cache:
            log.die("Couldn't determine CMake cache.")

        self.source_dir = self._find_source_dir()
        if not self.source_dir:
            log.die("Couldn't determine Zephyr source directory.")

        self.board = self._find_board().upper()
        if not self.source_dir:
            log.die("Couldn't determine board name.")

        if not os.path.exists(NRFX_BUILD) or not os.path.exists(NRFX_MDK):
            log.die("NRFX not in expected path.")

        yaml_path = self.source_dir + "/example.yaml"
        yaml_out_path = self.build_dir + "/output.yaml"
        log.inf(f"Retrieving YAML from: {yaml_path}")

        yaml_full = YAML_COMMAND + YAML_ARGUMENTS.format(incoming=yaml_path,
                                                         outgoing=yaml_out_path,
                                                         device=self.board)
        val = subprocess.run(yaml_full, shell=True)
        if val.returncode != 0:
            log.die("Merge YAML failed.")

        uicr_out_path = self.build_dir + "/uicr.hex"

        (svd, uicr) = self._get_nrfx_properties(self.board)

        log.inf("Generating UICR hex.")
        uicr_full = UICR_COMMAND + UICR_ARGUMENTS.format(incoming=yaml_out_path,
                                                         outgoing=uicr_out_path,
                                                         svd_file=svd,
                                                         uicr_address=uicr)
        val = subprocess.run(uicr_full, shell=True)
        if val.returncode != 0:
            log.die("UICR generation failed.")

    def _find_source_dir(self):
        source_dir = self.cache.get('CMAKE_HOME_DIRECTORY')
        if not source_dir:
            log.die(f"Build directory {self.build_dir} CMake cache has no CMAKE_HOME_DIRECTORY.")
        return os.path.abspath(source_dir)

    def _find_board(self):
        board = self.cache.get('CACHED_BOARD')
        if not board:
            log.die(f"Build directory {self.build_dir} CMake cache has no CACHED_BOARD.")
        return board

    def _get_nrfx_properties(self, board):
        nrfx_file_path = NRFX_BUILD + "/cmake/device/" + board.upper() + ".cmake"
        with open(nrfx_file_path) as file:
            for line in file:
                if "SVD_FILE" in line and "NOT" not in line:
                    svd = line.split("\"")[1]
                    svd = NRFX_MDK + "/" + svd
                if "UICR_ADDRESS" in line and "NOT" not in line:
                    uicr = line.split(" ")
                    uicr = list(filter(None, uicr))[1].replace(")","").strip()
        return (svd, uicr)
