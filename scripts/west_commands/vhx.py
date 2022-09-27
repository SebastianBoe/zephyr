#!/usr/bin/env python3
#
# Copyright (c) 2020 Nordic Semiconductor ASA
# SPDX-License-Identifier: Apache-2.0

import os
import sys
from textwrap import dedent
from pathlib import Path

from west.commands import WestCommand
from west import log
from build_helpers import find_build_dir, FIND_BUILD_DIR_DESCRIPTION

sys.path.append(os.fspath(Path(__file__).parent.parent))
import vhx_convert


class Vhx(WestCommand):

    def __init__(self):
        super().__init__(
            'vhx',
            'Convert .hex file to .vhx format',
            dedent('''
            Convert .hex file to .vhx format that is understandable
            by Palladium emulator.
            '''))

    def do_add_parser(self, parser_adder):
        parser = parser_adder.add_parser(self.name,
                                         help=self.help,
                                         description=self.description)
        parser.add_argument('-d', '--build-dir', default='',
                            help=FIND_BUILD_DIR_DESCRIPTION)
        return parser

    def do_run(self, args, unknown_args):
        build_dir = find_build_dir(
            args.build_dir if args.build_dir else None, guess=True)
        if not build_dir:
            log.die("Couldn't determine Zephyr build directory")
        src_path = build_dir + "/zephyr/zephyr.hex"
        dest_path = build_dir + "/zephyr/zephyr.vhx"
        log.inf("Converting {} to {} ...".format(os.path.relpath(src_path),
                                                 os.path.relpath(dest_path)))
        vhx_convert.convert_hex2vhx(src_path, dest_path)
