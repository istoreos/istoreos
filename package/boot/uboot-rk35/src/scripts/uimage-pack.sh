#!/bin/bash
#
# Copyright (c) 2020 Fuzhou Rockchip Electronics Co., Ltd
#
# SPDX-License-Identifier: GPL-2.0
#
set -e

IMG_DIR=images
IMG_NAME=boot.img

if grep -Eq ''^CONFIG_ARM64=y'|'^CONFIG_ARM64_BOOT_AARCH32=y'' .config ; then
	ARCH=arm64
else
	ARCH=arm
fi

echo
./tools/mkimage -n 'Multi Images' -A $ARCH -O linux -T multi -C none -a 0xffffffff -e 0xffffffff -d ${IMG_DIR}/kernel.img:${IMG_DIR}/ramdisk.img:${IMG_DIR}/rk-kernel.dtb:${IMG_DIR}/resource.img $IMG_NAME
echo

