#!/usr/bin/env python3
"""
# SPDX-License-Identifier: GPL-2.0+
#
# A script to generate FIT image source for rockchip boards
# with ARM Trusted Firmware
# and multiple device trees (given on the command line)
#
# usage: $0 <dt_name> [<dt_name> [<dt_name] ...]
"""

import os
import sys
import getopt
import logging
import struct

DT_HEADER = """
/*
 * This is a generated file.
 */
/dts-v1/;

/ {
	description = "FIT image for U-Boot with bl31 (TF-A)";
	#address-cells = <1>;

	images {
"""

DT_UBOOT = """
		uboot {
			description = "U-Boot (64-bit)";
			data = /incbin/("u-boot-nodtb.bin");
			type = "standalone";
			os = "U-Boot";
			arch = "arm64";
			compression = "none";
			load = <0x%08x>;
		};

"""

DT_IMAGES_NODE_END = """	};

"""

DT_END = "};"

def append_bl31_node(file, atf_index, phy_addr, elf_entry):
    # Append BL31 DT node to input FIT dts file.
    data = 'bl31_0x%08x.bin' % phy_addr
    file.write('\t\tatf_%d {\n' % atf_index)
    file.write('\t\t\tdescription = \"ARM Trusted Firmware\";\n')
    file.write('\t\t\tdata = /incbin/("%s");\n' % data)
    file.write('\t\t\ttype = "firmware";\n')
    file.write('\t\t\tarch = "arm64";\n')
    file.write('\t\t\tos = "arm-trusted-firmware";\n')
    file.write('\t\t\tcompression = "none";\n')
    file.write('\t\t\tload = <0x%08x>;\n' % phy_addr)
    if atf_index == 1:
        file.write('\t\t\tentry = <0x%08x>;\n' % elf_entry)
    file.write('\t\t};\n')
    file.write('\n')

def append_tee_node(file, atf_index, phy_addr, elf_entry):
    # Append TEE DT node to input FIT dts file.
    data = 'tee_0x%08x.bin' % phy_addr
    file.write('\t\tatf_%d {\n' % atf_index)
    file.write('\t\t\tdescription = \"TEE\";\n')
    file.write('\t\t\tdata = /incbin/("%s");\n' % data)
    file.write('\t\t\ttype = "tee";\n')
    file.write('\t\t\tarch = "arm64";\n')
    file.write('\t\t\tos = "tee";\n')
    file.write('\t\t\tcompression = "none";\n')
    file.write('\t\t\tload = <0x%08x>;\n' % phy_addr)
    file.write('\t\t\tentry = <0x%08x>;\n' % elf_entry)
    file.write('\t\t};\n')
    file.write('\n')

def append_fdt_node(file, dtbs):
    # Append FDT nodes.
    cnt = 1
    for dtb in dtbs:
        dtname = os.path.basename(dtb)
        file.write('\t\tfdt_%d {\n' % cnt)
        file.write('\t\t\tdescription = "%s";\n' % dtname)
        file.write('\t\t\tdata = /incbin/("%s");\n' % dtb)
        file.write('\t\t\ttype = "flat_dt";\n')
        file.write('\t\t\tcompression = "none";\n')
        file.write('\t\t};\n')
        file.write('\n')
        cnt = cnt + 1

def append_conf_section(file, cnt, dtname, segments):
    file.write('\t\tconfig_%d {\n' % cnt)
    file.write('\t\t\tdescription = "%s";\n' % dtname)
    file.write('\t\t\tfirmware = "atf_1";\n')
    file.write('\t\t\tloadables = "uboot"')
    if segments > 1:
        file.write(',')
    for i in range(1, segments):
        file.write('"atf_%d"' % (i + 1))
        if i != (segments - 1):
            file.write(',')
        else:
            file.write(';\n')
    if segments <= 1:
        file.write(';\n')
    file.write('\t\t\tfdt = "fdt_%d";\n' % cnt)
    file.write('\t\t};\n')
    file.write('\n')

def append_conf_node(file, dtbs, segments):
    # Append configeration nodes.
    cnt = 1
    file.write('\tconfigurations {\n')
    file.write('\t\tdefault = "config_1";\n')
    for dtb in dtbs:
        dtname = os.path.basename(dtb)
        append_conf_section(file, cnt, dtname, segments)
        cnt = cnt + 1
    file.write('\t};\n')
    file.write('\n')

def generate_atf_fit_dts_uboot(fit_file, uboot_file_name):
    segments = unpack_elf(uboot_file_name)
    if len(segments) != 1:
        raise ValueError("Invalid u-boot ELF image '%s'" % uboot_file_name)
    index, entry, p_paddr, data = segments[0]
    fit_file.write(DT_UBOOT % p_paddr)

def generate_atf_fit_dts_bl31(fit_file, bl31_file_name, tee_file_name, dtbs_file_name):
    segments = unpack_elf(bl31_file_name)
    for index, entry, paddr, data in segments:
        append_bl31_node(fit_file, index + 1, paddr, entry)
    num_segments = len(segments)

    if tee_file_name:
        tee_segments = unpack_tee_file(tee_file_name)
        for index, entry, paddr, data in tee_segments:
            append_tee_node(fit_file, num_segments + index + 1, paddr, entry)
        num_segments = num_segments + len(tee_segments)

    append_fdt_node(fit_file, dtbs_file_name)
    fit_file.write(DT_IMAGES_NODE_END)
    append_conf_node(fit_file, dtbs_file_name, num_segments)

def generate_atf_fit_dts(fit_file_name, bl31_file_name, tee_file_name, uboot_file_name, dtbs_file_name):
    # Generate FIT script for ATF image.
    if fit_file_name != sys.stdout:
        fit_file = open(fit_file_name, "wb")
    else:
        fit_file = sys.stdout

    fit_file.write(DT_HEADER)
    generate_atf_fit_dts_uboot(fit_file, uboot_file_name)
    generate_atf_fit_dts_bl31(fit_file, bl31_file_name, tee_file_name, dtbs_file_name)
    fit_file.write(DT_END)

    if fit_file_name != sys.stdout:
        fit_file.close()

def generate_atf_binary(bl31_file_name):
    for index, entry, paddr, data in unpack_elf(bl31_file_name):
        file_name = 'bl31_0x%08x.bin' % paddr
        with open(file_name, "wb") as atf:
            atf.write(data)

def generate_tee_binary(tee_file_name):
    if tee_file_name:
        for index, entry, paddr, data in unpack_tee_file(tee_file_name):
            file_name = 'tee_0x%08x.bin' % paddr
            with open(file_name, "wb") as atf:
                atf.write(data)

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

def unpack_tee_file(filename):
    if filename.endswith('.elf'):
        return unpack_elf(filename)
    with open(filename, 'rb') as file:
        bin = file.read()
    segments = []
    if bin[0:5] == b'OPTE\x01':
        # OP-TEE v1 format (tee.bin)
        init_sz, start_hi, start_lo, _, paged_sz = struct.unpack_from('<5I',
                                                                      bin,
                                                                      0x8)
        if paged_sz != 0:
            raise ValueError("OP-TEE paged mode not supported")
        e_entry = (start_hi << 32) + start_lo
        p_addr = e_entry
        p_data = bin[0x1c:]
        if len(p_data) != init_sz:
            raise ValueError("Invalid file '%s': size mismatch "
                             "(expected %d, have %d)" % (filename, init_sz,
                                                         len(p_data)))
        segments.append((0, e_entry, p_addr, p_data))
    else:
        raise ValueError("Unknown format for TEE file '%s'" % filename)
    return segments

def main():
    uboot_elf = "./u-boot"
    fit_its = sys.stdout
    if "BL31" in os.environ:
        bl31_elf=os.getenv("BL31");
    elif os.path.isfile("./bl31.elf"):
        bl31_elf = "./bl31.elf"
    else:
        os.system("echo 'int main(){}' > bl31.c")
        os.system("${CROSS_COMPILE}gcc -c bl31.c -o bl31.elf")
        bl31_elf = "./bl31.elf"
        logging.basicConfig(format='%(levelname)s:%(message)s', level=logging.DEBUG)
        logging.warning(' BL31 file bl31.elf NOT found, resulting binary is non-functional')
        logging.warning(' Please read Building section in doc/README.rockchip')

    if "TEE" in os.environ:
        tee_file = os.getenv("TEE")
    elif os.path.isfile("./tee.bin"):
        tee_file = "./tee.bin"
    elif os.path.isfile("./tee.elf"):
        tee_file = "./tee.elf"
    else:
        tee_file = ""

    opts, args = getopt.getopt(sys.argv[1:], "o:u:b:t:h")
    for opt, val in opts:
        if opt == "-o":
            fit_its = val
        elif opt == "-u":
            uboot_elf = val
        elif opt == "-b":
            bl31_elf = val
        elif opt == "-t":
            tee_file = val
        elif opt == "-h":
            print(__doc__)
            sys.exit(2)

    dtbs = args

    generate_atf_fit_dts(fit_its, bl31_elf, tee_file, uboot_elf, dtbs)
    generate_atf_binary(bl31_elf)
    generate_tee_binary(tee_file)

if __name__ == "__main__":
    main()
