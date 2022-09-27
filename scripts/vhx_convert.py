#!/usr/bin/env python3
#
# Copyright (c) 2021 Nordic Semiconductor ASA
#
# SPDX-License-Identifier: Apache-2.0
#

import argparse
import sys
from intelhex import IntelHex


def convert_bin2vhx(infile, outfile):
    with open(infile, "rb") as infile:
        with open(outfile, "w") as outfile:
            while True:
                s = infile.read(16)
                if not s:
                    break
                s = bytearray(s)
                s.reverse()
                o = ''.join(["%.2X" % i for i in s])

                outfile.write(o)
                outfile.write('\n')
    infile.close()
    outfile.close()


def convert_hex2vhx(infile, outfile):
    def bin_reader(input_array):
        for i in range(0, len(input_array), 16):
            yield input_array[i:i+16]

    ih = IntelHex(infile)
    b = ih.tobinarray()

    with open(outfile, "w") as outfile:
        for s in bin_reader(b):
            s = bytearray(s)
            s.reverse()
            o = ''.join(["%.2X" % i for i in s])

            outfile.write(o)
            outfile.write('\n')
    outfile.close()


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("file", type=str, help="input file name")
    parser.add_argument("-o", "--output", type=str, default="out.vhx",
        help="output file name (default, out.vhx")
    parser.add_argument("-f", "--input-format", type=str,
        choices=["bin", "hex"], default="bin",
        help="Input file format (default, bin)")
    args = parser.parse_args()

    if args.input_format == "bin":
        convert_bin2vhx(args.file, args.output)
    elif args.input_format == "hex":
        convert_hex2vhx(args.file, args.output)


if __name__ == "__main__":
    main()
