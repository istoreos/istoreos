/*
 * (C) Copyright 2017 Rockchip Electronics Co., Ltd
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */

#ifndef _CHARGE_ANIMATION_H_
#define _CHARGE_ANIMATION_H_

struct charge_animation_pdata {
	int android_charge;	/* android charge, 1: enable, 0: disable */
	int uboot_charge;	/* u-boot charge, 1: enable, 0: disable */

	int auto_exit_charge;	/* energy enough auto exit uboot charging*/
	int exit_charge_voltage;/* lowest voltage allowed to exit charging */
	int exit_charge_level;  /* lowest soc level allowed to exit charging */
	int low_power_voltage;	/* below this voltage, force system into charge mode anyway */
	int screen_on_voltage;	/* lowest voltage allowed to turn on screen */

	int system_suspend;	/* enter ATF system suspend, 1: enable, 0: disable */
	int auto_wakeup_interval;/* timeout seconds to auto wakeup system */
	int auto_wakeup_screen_invert;/* auto wakeup system, 1: enable, 0: disable */
	int auto_off_screen_interval;/* timeout seconds to auto turn off screen */
};

#endif
