#!/usr/bin/env python3
#
# Copyright (c) 2018 Intel Corporation
#
# SPDX-License-Identifier: Apache-2.0

# This script will parse the serial console log file and create the required
# gcda files.
# Usage python3 ${ZEPHYR_BASE}/scripts/gen_gcov_files.py -i console_output.log
# Add -v for verbose



import sys
import argparse
import os
import re
import string
import hexdump

def retrieve_data(input_file):
    extracted_coverage_info = {}
    capture_data=False
    with open(input_file, 'r') as fp:
        for line in fp.readlines():
            if re.search("GCOV_COVERAGE_DUMP_START", line):
                capture_data = True
                continue
            if re.search("GCOV_COVERAGE_DUMP_END", line):
                capture_data = True
                break
            # Loop until the coverage data is found.
            if capture_data == False:
                continue

            # Remove the leading delimiter "*"
            file_name = line.split("<")[0][1:]
            # Remove the trailing new line char
            hex_dump = line.split("<")[1][:-1]
            extracted_coverage_info.update({file_name:hex_dump})
    return extracted_coverage_info

def create_gcda_files(extracted_coverage_info):
    if args.verbose:
        print("Generating gcda files")
    for filename, hexdump_val in extracted_coverage_info.items():
        if args.verbose:
            print(filename)

        with open(filename, 'wb') as fp:
            fp.write(hexdump.dehex(hexdump_val))


def parse_args():
    global args
    parser = argparse.ArgumentParser(
        description=__doc__,
        formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("-i", "--input", required=True,
                        help="Input dump data")
    parser.add_argument("-v", "--verbose", action="count", default =0,
                        help="Verbose Output")
    args = parser.parse_args()



def main():
    parse_args()
    input_file= args.input

    extracted_coverage_info = retrieve_data(input_file)
    create_gcda_files(extracted_coverage_info)


if __name__ == '__main__':
    main()
