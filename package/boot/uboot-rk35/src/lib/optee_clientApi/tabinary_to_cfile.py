#!/usr/bin/env python
#
# Copyright 2017, Rockchip Electronics Co., Ltd
# hisping lin, <hisping.lin@rock-chips.com>
#
# SPDX-License-Identifier:	GPL-2.0+
#

def get_args():
	import argparse

	parser = argparse.ArgumentParser()
	parser.add_argument('--prefix', required=True, \
		help='Prefix for the TA array in c file')

	parser.add_argument('--out', required=True, \
		help='Name of c file for the TA')

	parser.add_argument('--TA', required=True, help='Name of TA')

	return parser.parse_args()

def main():
	import array
#	from Crypto.PublicKey import RSA
#	from Crypto.Util.number import long_to_bytes

	args = get_args();

	f = open(args.TA, 'r')
	TAdata = f.read()
	f.close

	f = open(args.out, 'w')

	f.write("#include <stdint.h>\n");
	f.write("#include <stddef.h>\n\n");

#	f.write("const uint32_t " + args.prefix + "_exponent = " +
#		str(key.publickey().e) + ";\n\n")

	f.write("const uint8_t " + args.prefix + "_data[] = {\n")
	i = 0;
	for x in array.array("B", TAdata):
		f.write("0x" + '{0:02x}'.format(x) + ",")
		i = i + 1;
		if i % 8 == 0:
			f.write("\n");
		else:
			f.write(" ");
	f.write("};\n");

	f.write("const uint32_t " + args.prefix + "_size = " + str(i) + ";\n" )

	f.close()

if __name__ == "__main__":
	main()
