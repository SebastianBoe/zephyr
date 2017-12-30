# For portability reasons; No shebang
#
# SPDX-License-Identifier: Apache-2.0

"""QEMU wrapper script

This script allows us to modify the Qemu command line without
triggering a CMake reconfiguration.

It does so by wrapping qemu (STDIN/STDERR and signals are 'forwarded'
to qemu) and constructing a qemu command line based on environment
variables and the CMake constructed qemu command line.

Specifically, the contents of the environment variable 'run_args' will
be appended to the command line when "make run" is invoked. The same
applies for the make target 'debugserver' with the environment
variable 'debugserver_args', and any other qemu targets.

"""

import subprocess
import argparse
import signal
import sys
import os
import shlex

child = None

def main():
    cmd = construct_qemu_cmd_from_env_and_cli()

    # Print the resulting command when VERBOSE
    if "VERBOSE" in os.environ:
        print("qemu command: '{}'".format(" ".join(shlex.quote(s) for s in cmd)))

    global child
    child = subprocess.Popen(
        cmd
    )

    # Forward all signals
    catchable_signums = set(signal.Signals) - {signal.SIGKILL, signal.SIGSTOP}
    for signum in catchable_signums:
        signal.signal(signum, forward_the_signal)

    child.communicate()

def forward_the_signal(signum, frame):
    # Pass on the signal to the child process
    global child
    child_is_alive = child.poll() == None
    if child_is_alive:
        try:
            child.send_signal(signum)
        except ProcessLookupError:
            # The child has died, so there is no point in sending it a
            # signal
            pass

def construct_qemu_cmd_from_env_and_cli():
    # The first element is the path to this file and can be discarded.

    # The second element is the target (run/debugserver) and is used
    # to determine which environment variable should be used.
    target = sys.argv[1]

    append_args = os.getenv("{}_args"       .format(target), "")
    remove_args = os.getenv("{}_remove_args".format(target), "")

    sys_argv_str = " ".join(sys.argv[2:])

    # Remove the CMake-provided flags that match <target>_remove_args
    for token in shlex.split(remove_args):
        sys_argv_str = sys_argv_str.replace(token, '')

    return shlex.split(sys_argv_str + " " + append_args)

if __name__ == '__main__':
    main()
