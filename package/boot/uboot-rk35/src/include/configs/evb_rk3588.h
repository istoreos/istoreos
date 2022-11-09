/*
 * SPDX-License-Identifier:     GPL-2.0+
 *
 * Copyright (c) 2021 Rockchip Electronics Co., Ltd
 */

#ifndef __CONFIGS_RK3588_EVB_H
#define __CONFIGS_RK3588_EVB_H

#include <configs/rk3588_common.h>

#ifndef CONFIG_SPL_BUILD

#undef ROCKCHIP_DEVICE_SETTINGS
#define ROCKCHIP_DEVICE_SETTINGS \
		"stdout=serial,vidconsole\0" \
		"stderr=serial,vidconsole\0"

#define CONFIG_SYS_MMC_ENV_DEV		0

#undef CONFIG_BOOTCOMMAND
#define CONFIG_BOOTCOMMAND RKIMG_BOOTCOMMAND

#endif
#endif