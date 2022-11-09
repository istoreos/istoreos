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
			INI=$2
			shift 2
			;;
		*)
			echo "ERROR: Unknown arg: $1"
			exit 1
			;;
	esac
done

if [ ! -f ${INI} ]; then
	echo "pack loader failed! Can't find: ${INI}"
	exit 0
fi

COUNT=`cat ${INI} | wc -l`
if [ ${COUNT} -eq 1 ]; then
	IMG=`sed -n "/PATH=/p" ${INI} | tr -d '\r' | cut -d '=' -f 2`
	cp ${IMG} ./
else
	./tools/boot_merger ${INI}
fi

echo "pack loader okay! Input: ${INI}"
