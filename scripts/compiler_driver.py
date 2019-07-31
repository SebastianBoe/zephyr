#!/usr/bin/env python3

# TODO: Ensure the shebang works for all *nix platforms

# This script is executed like this:
#
# [COMPILER_DRIVER_OVERRIDE=arm-none-eabi-gcc] compiler_driver.py [--override=arm-none-eabi-gcc] arm-zephyr-eabi-gcc [compiler_options]
#
# It will possibly consume the optional --override flag, and then
# execute the rest of the command (after modifying it according to the
# --override flag, or env var).
#
# Limitations in ccache and Windows prevent us from just using one
# mechanism unfortunately.
#
# This is used to change which compiler is executed by CMake, in spite
# of CMake not supporting multiple compilers.

import subprocess
import sys
import os

def main():
    # TODO: Ensure file-not-found has a good error message

    cmd = sys.argv

    # Skip sys.argv[0] (which is this file) # TODO: Is it though? Even when python is in the command?
    cmd = cmd[1:]

    if '--override=' in cmd[0]:
        compiler = cmd[0].replace("--override=", '')
        cmd = cmd[1:]
    else:
        compiler = os.environ.get('COMPILER_DRIVER_OVERRIDE')

    cmd[0] = compiler

    completed_process = subprocess.run(cmd)

    sys.exit(completed_process.returncode)

main()
