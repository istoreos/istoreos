#!/bin/bash
#
# Copyright (c) 2020 Fuzhou Rockchip Electronics Co., Ltd
#
# SPDX-License-Identifier: GPL-2.0
#
set -e

source ./scripts/fit-core.sh
fit_process_args $*

if [ ! -z "${ARG_VALIDATE}" ]; then
	validate_arg ${ARG_VALIDATE}
else
	fit_raw_compile
	if [ ! -z "${ARG_RECOVERY_IMG}" ]; then
		fit_gen_recovery_itb
		fit_gen_recovery_img
	fi
	# "--boot_img_dir" is for U-Boot debug only
	if [ ! -z "${ARG_BOOT_IMG}" -o ! -z "${ARG_BOOT_IMG_DIR}" ]; then
		fit_gen_boot_itb
		fit_gen_boot_img
	fi
	fit_gen_uboot_itb
	fit_gen_uboot_img
	fit_gen_loader

	echo
	fit_msg_uboot
	fit_msg_recovery
	fit_msg_boot
	fit_msg_loader
fi
