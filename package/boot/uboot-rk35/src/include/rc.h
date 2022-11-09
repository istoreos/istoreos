/*
 * (C) Copyright 2017 Rockchip Electronics Co., Ltd
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */

#ifndef _RC_H_
#define _RC_H_

struct dm_rc_ops {
	int (*get_keycode)(struct udevice *dev);
	int (*get_repeat)(struct udevice *dev);
};

int rc_get_keycode(struct udevice *dev);
int rc_get_repeat(struct udevice *dev);

#endif
