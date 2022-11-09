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
		--base)
			DRAM_BASE=$2
			shift 2
			;;
		--ini)
			INI=$2
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

TOS=`sed -n "/TOS=/s/TOS=//p" ${INI} | tr -d '\r'`
TOSTA=`sed -n "/TOSTA=/s/TOSTA=//p" ${INI} | tr -d '\r'`
OUTPUT=`sed -n "/OUTPUT=/s/OUTPUT=//p" ${INI} | tr -d '\r'`

if [ -z "${OUTPUT}" ]; then
	OUTPUT="./trust.img"
fi

LOAD_OFFSET=`sed -n "/ADDR=/s/ADDR=//p" ${INI} | tr -d '\r'`
if [ -z "${LOAD_OFFSET}" ]; then
	# default offset
	LOAD_OFFSET=0x8400000
fi

LOAD_ADDR=$((DRAM_BASE+LOAD_OFFSET))
LOAD_ADDR=$(echo "obase=16;${LOAD_ADDR}"|bc) # Convert Dec to Hex

rm trust*.img -f

COUNT=`cat ${INI} | wc -l`
if [ ${COUNT} -eq 1 ]; then
	IMG=`sed -n "/PATH=/p" ${INI} | tr -d '\r' | cut -d '=' -f 2`
	cp ${IMG} ./trust.img
else
	if [ ! -z "${TOSTA}" ]; then
		./tools/loaderimage --pack --trustos ${TOSTA} ${OUTPUT} ${LOAD_ADDR} ${SIZE}
	elif [ ! -z "${TOS}" ]; then
		./tools/loaderimage --pack --trustos ${TOS}   ${OUTPUT} ${LOAD_ADDR} ${SIZE}
	else
		echo "ERROR: No tee bin"
		exit 1
	fi
fi

echo "pack trust okay! Input: ${INI}"
echo
