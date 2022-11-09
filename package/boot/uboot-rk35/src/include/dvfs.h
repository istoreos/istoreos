/* SPDX-License-Identifier:     GPL-2.0+ */
/*
 * (C) Copyright 2018 Rockchip Electronics Co., Ltd
 */

#ifndef _DVFS_H_
#define _DVFS_H_

#include <dm.h>

/**
 * dvfs_init() - init first dvfs driver
 *
 * @apply: do dvfs policy apply if true, otherwise just init.
 * @return 0 if OK, 1 on error
 */
int dvfs_init(bool apply);

/**
 * dvfs_apply() - do dvfs policy apply
 *
 * @dev: dvfs device
 * @return 0 if OK, otherwise on error
 */
int dvfs_apply(struct udevice *dev);

/**
 * dvfs_repeat_apply() - do dvfs policy repeat apply
 *
 * @dev: dvfs device
 * @return 0 if OK, otherwise on error
 */
int dvfs_repeat_apply(struct udevice *dev);

/**
 * struct dm_dvfs_ops - Driver model Thermal operations
 *
 * The uclass interface is implemented by all Thermal devices which use
 * driver model.
 */

struct dm_dvfs_ops {
	int (*apply)(struct udevice *dev);
	int (*repeat_apply)(struct udevice *dev);
};

#endif	/* _DVFS_H_ */
