#!/bin/bash
#
# Copyright (c) 2022 Rockchip Electronics Co., Ltd
#
# SPDX-License-Identifier: GPL-2.0
#
set -e

source ./scripts/fit-core.sh
fit_process_args $*

# Sign boot/recovery.img and it inserts the RSA pubkey into u-boot.dtb by default
if [ ! -z "${ARG_VALIDATE}" ]; then
	validate_arg ${ARG_VALIDATE}
else
	fit_raw_compile
	if [ ! -z "${ARG_RECOVERY_IMG}" ]; then
		fit_gen_recovery_itb
		fit_gen_recovery_img
	fi
	if [ ! -z "${ARG_BOOT_IMG}" ]; then
		fit_gen_boot_itb
		fit_gen_boot_img
	fi
fi

# New u-boot.bin with RSA pubkey
cat u-boot-nodtb.bin u-boot.dtb > u-boot.bin

# Pack image
COMPRESS="lzma"
ADDR=`sed -n "/CONFIG_SYS_TEXT_BASE=/s/CONFIG_SYS_TEXT_BASE=//p" include/autoconf.mk|tr -d '\r'`
./scripts/lzma.sh u-boot.bin
./tools/mkimage -A arm -O u-boot -T standalone -C ${COMPRESS} -a ${ADDR} -e ${ADDR} -d u-boot.bin.${COMPRESS} u-boot.bin.${COMPRESS}.uImage
cp -f spl/u-boot-spl-nodtb.bin u-boot.bin.decomp
if ! grep -q '^CONFIG_SPL_SEPARATE_BSS=y' .config ; then
	cat spl/u-boot-spl-pad.bin >> u-boot.bin.decomp
fi
cat u-boot.bin.${COMPRESS}.uImage >> u-boot.bin.decomp
cp -f u-boot.bin.decomp spl/u-boot-spl.bin

# Pack loader
./make.sh spl

# Sign loader
fit_gen_loader

# Delelte
rm -f uboot.img trust.img

# Output msg
echo
echo "Image: $(ls *download*.bin) (with usbplug...) is ready"
fit_msg_u_boot_loader
fit_msg_recovery
fit_msg_boot
