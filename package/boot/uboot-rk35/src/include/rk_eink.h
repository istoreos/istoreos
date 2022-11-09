/*
 * (C) Copyright 2020 Rockchip Electronics Co., Ltd
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */

#ifndef RK_EINK_H
#define RK_EINK_H

enum type_logo {
	EINK_LOGO_RESET = 0,
	EINK_LOGO_UBOOT = 1 << 0,
	EINK_LOGO_KERNEL = 1 << 1,
	EINK_LOGO_CHARGING_0 = 1 << 2,
	EINK_LOGO_CHARGING_1 = 1 << 3,
	EINK_LOGO_CHARGING_2 = 1 << 4,
	EINK_LOGO_CHARGING_3 = 1 << 5,
	EINK_LOGO_CHARGING_4 = 1 << 6,
	EINK_LOGO_CHARGING_5 = 1 << 7,
	EINK_LOGO_CHARGING_LOWPOWER = 1 << 8,
	EINK_LOGO_POWEROFF = 1 << 9,
	EINK_LOGO_UNMIRROR_TEMP_BUF = 1 << 10,
};

enum update_mode {
	EINK_UPDATE_NORMAL = 0,
	EINK_UPDATE_DIFF = 1,
};

int rockchip_eink_show_uboot_logo(void);
int rockchip_eink_show_charge_logo(int logo_type);

#endif
