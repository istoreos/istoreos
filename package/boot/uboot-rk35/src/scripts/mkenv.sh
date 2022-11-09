#!/bin/bash
#
# Copyright (c) 2022 Rockchip Electronics Co., Ltd
#
# SPDX-License-Identifier: GPL-2.0
#
set -e

TXT=$1
IMG=$2
KB=$3

if [ $# -ne 3 ]; then
	echo "Usage:"
	echo "    $0 [intput txt] [output img] [size in KB]"
	echo "Example:"
	echo "    $0 env.txt env.img 32k"
	echo
	exit 1
fi

KB=`echo ${KB} | tr -d 'k' | tr -d 'K'`
BS=$((KB*1024))
BS=$(echo "obase=16;${BS}"|bc)
./tools/mkenvimage -s 0x${BS} -p 0x0 -o ${IMG} ${TXT}
echo "${IMG} is ready."
