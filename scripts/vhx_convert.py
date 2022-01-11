#!/usr/bin/env python3
#
# Copyright (c) 2021 Nordic Semiconductor ASA
#
# SPDX-License-Identifier: Apache-2.0
#

import argparse
from intelhex import IntelHex

SUPPORTED_BYTE_WIDTHS = [64, 128]


def convert_bin2vhx(infile, outfile, width):
    byte_width = width//8
    if width not in SUPPORTED_BYTE_WIDTHS:
        raise ValueError(f"Invalid byte width; must be {SUPPORTED_BYTE_WIDTHS},"
                         f" got {byte_width}.")

    with open(infile, "rb") as in_file:
        with open(outfile, "w") as out_file:
            while True:
                s = in_file.read(byte_width)
                if not s:
                    break
                s = bytearray(s)
                s.reverse()
                o = ''.join(["%.2X" % i for i in s])

                out_file.write(o)
                out_file.write('\n')
    in_file.close()
    out_file.close()


def convert_hex2vhx(infile, outfile, width):
    byte_width = width//8
    if width not in SUPPORTED_BYTE_WIDTHS:
        raise ValueError(f"Invalid byte width; must be {SUPPORTED_BYTE_WIDTHS},"
                         f" got {byte_width}.")

    def bin_reader(input_array):
        for i in range(0, len(input_array), byte_width):
            yield input_array[i:i+byte_width]

    ih = IntelHex(infile)
    b = ih.tobinarray()

    with open(outfile, "w") as out_file:
        for s in bin_reader(b):
            s = bytearray(s)
            s.reverse()
            o = ''.join(["%.2X" % i for i in s])

            out_file.write(o)
            out_file.write('\n')
    out_file.close()


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("file", type=str, help="input file name")
    parser.add_argument("-o", "--output", type=str, default="out.vhx",
        help="output file name (default, out.vhx")
    parser.add_argument("-f", "--input-format", type=str,
        choices=["bin", "hex"], default="bin",
        help="Input file format (default, bin)")
    parser.add_argument("-w", "--width", type=int,
        choices=SUPPORTED_BYTE_WIDTHS, default=128,
        help="Line width of the VHX output")
    args = parser.parse_args()
    if args.input_format == "bin":
        convert_bin2vhx(args.file, args.output, args.width)
    elif args.input_format == "hex":
        convert_hex2vhx(args.file, args.output, args.width)


if __name__ == "__main__":
    main()
