#!/bin/bash
#
# Copyright (c) 2020 Rockchip Electronics Co., Ltd
#
# SPDX-License-Identifier: GPL-2.0
#

set -e

if [ $# -eq 0 ]; then
	echo "ERROR: No args of $0"
	exit 1
fi

while [ $# -gt 0 ]; do
	case $1 in
		--ini)
			INI=$2	# mandory
			shift 2
			;;
		--rsa)
			RSA="$1 $2"
			shift 2
			;;
		--sha)
			SHA="$1 $2"
			shift 2
			;;
		--size)
			SIZE="$1 $2 $3"
			shift 3
			;;
		*)
			echo "ERROR: Unknown arg: $1"
			exit 1
			;;
	esac
done

if [ ! -f ${INI} ]; then
	echo "pack trust failed! Can't find: ${INI}"
	exit 0
fi

rm trust*.img -f

COUNT=`cat ${INI} | wc -l`
if [ ${COUNT} -eq 1 ]; then
	IMG=`sed -n "/PATH=/p" ${INI} | tr -d '\r' | cut -d '=' -f 2`
	cp ${IMG} ./trust.img
else
	./tools/trust_merger ${INI} ${SIZE} ${SHA} ${RSA}
fi

echo "pack trust okay! Input: ${INI}"
echo
