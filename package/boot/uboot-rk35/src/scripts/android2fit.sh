#!/bin/bash
#
# Copyright (c) 2020 Rockchip Electronics Co., Ltd
#
# SPDX-License-Identifier: GPL-2.0
#
set -e

OUT="out"

function usage()
{
	echo
	echo "usage:"
	echo "    $0 -f [Android boot.img] -o [FIT boot.img]"
	echo
}

function args_process()
{
	if [ $# -ne 4 ]; then
		usage
		exit 1
	fi

	while [ $# -gt 0 ]; do
		case $1 in
			-f)
				BOOT_IMG=$2
				shift 2
				;;
			-o)
				FIT_IMG=$2
				shift 2
				;;
			*)
				usage
				exit 1
				;;
		esac
	done

	if [ ! -f ${BOOT_IMG} ]; then
		echo "ERROR: No ${ITB}"
		exit 1
	fi
}

function android2fit()
{
	if ! file ${BOOT_IMG} | grep "Android bootimg" ; then
		echo "ERROR: ${BOOT_IMG} is not an Android Image"
		file ${BOOT_IMG}
		exit 1
	fi

	rm ${OUT}/ -rf
	./scripts/unpack_bootimg --boot_img ${BOOT_IMG} --out ${OUT}/
	./scripts/unpack_resource.sh ${OUT}/second  ${OUT}/
	mv ${OUT}/second ${OUT}/resource

	rm images/ -rf && mkdir -p images/
	cp ${OUT}/kernel images/
	cp ${OUT}/resource images/
	cp ${OUT}/ramdisk images/
	cp ${OUT}/rk-kernel.dtb images/
	rm ${OUT}/ -rf

	./make.sh fit
	if [ "boot.img" != ${FIT_IMG} ]; then
		mv boot.img ${FIT_IMG}
	fi

	echo "Transform OK: Android(${BOOT_IMG}) ==> FIT(${FIT_IMG}) is ready"
	echo
}

args_process $*
android2fit
