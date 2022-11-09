#!/usr/bin/env python2
#
# Copyright (C) 2020 Rockchip Electronics Co., Ltd
#
# SPDX-License-Identifier:     GPL-2.0+
#
"""
A script to decode bl31.elf to binary
"""

import os
import sys
import getopt
import logging
import struct

def unpack_elf(filename):
    with open(filename, 'rb') as file:
        elf = file.read()
    if elf[0:7] != b'\x7fELF\x02\x01\x01' or elf[18:20] != b'\xb7\x00':
        raise ValueError("Invalid arm64 ELF file '%s'" % filename)

    e_entry, e_phoff = struct.unpack_from('<2Q', elf, 0x18)
    e_phentsize, e_phnum = struct.unpack_from('<2H', elf, 0x36)
    segments = []

    for index in range(e_phnum):
        offset = e_phoff + e_phentsize * index
        p_type, p_flags, p_offset = struct.unpack_from('<LLQ', elf, offset)
        if p_type == 1: # PT_LOAD
            p_paddr, p_filesz = struct.unpack_from('<2Q', elf, offset + 0x18)
            if p_filesz > 0:
                p_data = elf[p_offset:p_offset + p_filesz]
                segments.append((index, e_entry, p_paddr, p_data))
    return segments

def generate_atf_binary(bl31_file_name):
    for index, entry, paddr, data in unpack_elf(bl31_file_name):
        file_name = 'bl31_0x%08x.bin' % paddr
        with open(file_name, "wb") as atf:
            atf.write(data)

def main():
    bl31_elf="./bl31.elf"
    generate_atf_binary(bl31_elf);

if __name__ == "__main__":
    main()
