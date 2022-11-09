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
		--spl)
			SPL_BIN=$2
			if [ ! -f ${SPL_BIN} ]; then
				echo "ERROR: No ${SPL_BIN}"
				exit 1
			fi
			shift 2
			;;
		--tpl)
			TPL_BIN=$2
			if [ ! -f ${TPL_BIN} ]; then
				echo "ERROR: No ${TPL_BIN}"
				exit 1
			fi
			shift 2
			;;
		*)
			echo "ERROR: Unknown arg: $1"
			exit 1
			;;
	esac
done

if [ ! -f ${INI} ]; then
	echo "ERROR: No ${INI}"
	exit 0
fi

if [ "${TPL_BIN}" == "" -a "${SPL_BIN}" == "" ]; then
	echo "ERROR: No SPL and TPL file"
	exit 0
fi

rm tmp -rf && mkdir tmp -p
TMP_INI="tmp/MINIALL.ini"
cp ${INI} ${TMP_INI}

# magic
MAGIC=`sed -n '/NAME=/s/NAME=//p' ${INI}`
if [ "${MAGIC}" == "RV1126" ]; then
	MAGIC="110B"
elif [ "${MAGIC}" == "RKPX30" ]; then
	MAGIC="RK33"
fi

# tpl don't need replace MAGIC
if grep -q '^NEWIDB=true' ${INI} ; then
	ARG_NEWIDB="y"
fi

# replace
if [ "${TPL_BIN}" != "" -a "${SPL_BIN}" != "" ]; then
	if [ "${ARG_NEWIDB}" == "y" ]; then
		cp ${TPL_BIN} tmp/tpl.bin
	else
		cp ${TPL_BIN} tmp/u-boot-tpl.bin
		dd if=tmp/u-boot-tpl.bin of=tmp/tpl.bin bs=1 skip=4
		sed -i "1s/^/${MAGIC:0:4}/" tmp/tpl.bin
	fi

	cp ${SPL_BIN} tmp/u-boot-spl.bin
	sed -i "s/FlashData=.*$/FlashData=.\/tmp\/tpl.bin/"        ${TMP_INI}
	sed -i "0,/Path1=.*/s/Path1=.*$/Path1=.\/tmp\/tpl.bin/"    ${TMP_INI}
	sed -i "s/FlashBoot=.*$/FlashBoot=.\/tmp\/u-boot-spl.bin/" ${TMP_INI}
	LABEL="TPL+SPL"
elif [ "${TPL_BIN}" != "" ]; then
	if [ "${ARG_NEWIDB}" == "y" ]; then
		cp ${TPL_BIN} tmp/tpl.bin
	else
		cp ${TPL_BIN} tmp/u-boot-tpl.bin
		dd if=tmp/u-boot-tpl.bin of=tmp/tpl.bin bs=1 skip=4
		sed -i "1s/^/${MAGIC:0:4}/" tmp/tpl.bin
	fi
	sed -i "s/FlashData=.*$/FlashData=.\/tmp\/tpl.bin/"        ${TMP_INI}
	sed -i "0,/Path1=.*/s/Path1=.*$/Path1=.\/tmp\/tpl.bin/"    ${TMP_INI}
	LABEL="TPL"
else
	cp ${SPL_BIN} tmp/u-boot-spl.bin
	sed -i "s/FlashBoot=.*$/FlashBoot=.\/tmp\/u-boot-spl.bin/" ${TMP_INI}
	LABEL="SPL"
fi

./tools/boot_merger ${TMP_INI}
rm tmp/ -rf

echo "pack loader(${LABEL}) okay! Input: ${INI}"
echo
