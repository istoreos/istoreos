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
		--load)
			LOAD_ADDR=$2
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

rm uboot.img -f

if [ -z "${LOAD_ADDR}" ]; then
	echo "ERROR: No load address"
	exit 1
fi

HEAD_KB=2
BIN_KB=`ls -l u-boot.bin | awk '{ print $5 }'`
if [ -z "${SIZE}" ]; then
	MAX_KB=1046528
else
	MAX_KB=`echo ${SIZE} | awk '{print strtonum($2)}'`
	MAX_KB=$(((MAX_KB-HEAD_KB)*1024))
fi

if [ ${BIN_KB} -gt ${MAX_KB} ]; then
	echo "ERROR: pack uboot failed! u-boot.bin actual: ${BIN_KB} bytes, max limit: ${MAX_KB} bytes"
	exit 1
fi

../rkbin/tools/loaderimage --pack --uboot u-boot.bin uboot.img ${LOAD_ADDR} ${SIZE}
echo "pack uboot okay! Input: u-boot.bin"
echo
