#!/bin/bash
#
# Copyright (c) 2021 Rockchip Electronics Co., Ltd
#
# SPDX-License-Identifier: GPL-2.0
#

set -e

function usage()
{
	echo
	echo "usage:"
	echo "    $0 -f [Android boot.img] -o [Distro(ext2) boot.img]"
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
				DISTRO_IMG=$2
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

function android2distro()
{
	rm distro/ boot/ ${DISTRO_IMG} -rf
	mkdir -p boot

	./scripts/unpack_bootimg --boot_img ${BOOT_IMG} --out distro/
	./scripts/unpack_resource.sh distro/second distro/
	BOOTARGS=`fdtget -ts distro/rk-kernel.dtb /chosen bootargs`

	cp distro/rk-kernel.dtb boot/rk-kernel.dtb
	cp distro/kernel boot/kernel
	cp distro/ramdisk boot/ramdisk
	mkdir -p boot/extlinux
	touch boot/extlinux/extlinux.conf
	echo "label rockchip-linux-kernel" >> boot/extlinux/extlinux.conf
	echo "    kernel /kernel" >> boot/extlinux/extlinux.conf
	echo "    fdt /rk-kernel.dtb" >> boot/extlinux/extlinux.conf
	echo "    initrd /ramdisk" >> boot/extlinux/extlinux.conf
	echo "    append ${BOOTARGS}" >> boot/extlinux/extlinux.conf

	SIZE_KB=`ls -lh ${BOOT_IMG} | awk '{ print $5 }' | tr -d 'M'`
	SIZE_KB=`echo "scale=0;$SIZE_KB/1"|bc -l` # for align down integer
	SIZE_KB=`expr ${SIZE_KB} + 2 + 1`
	SIZE_BYTE=$((${SIZE_KB}*1024))
	genext2fs -b ${SIZE_BYTE} -B 1024 -d boot/ -i 8192 -U ${DISTRO_IMG}

	echo
	echo "Successful: ${DISTRO_IMG} is ready."
	echo
}

args_process $*
android2distro
