/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright (c) 2024 Rockchip Electronics Co., Ltd.
 *
 * Author: Zorro Liu <zorro.liu@rock-chips.com>
 */

#ifndef __LINUX_EBC_H__
#define __LINUX_EBC_H__

#include <linux/notifier.h>

/*
 * ebc status notify
 */
#define EBC_OFF			(0)
#define EBC_ON			(1)
#define EBC_FB_BLANK		(2)
#define EBC_FB_UNBLANK		(3)

#if IS_REACHABLE(CONFIG_ROCKCHIP_EBC_DEV)
int ebc_register_notifier(struct notifier_block *nb);
int ebc_unregister_notifier(struct notifier_block *nb);
int ebc_notify(unsigned long event);
#else
static inline int ebc_register_notifier(struct notifier_block *nb)
{
	return 0;
}

static inline int ebc_unregister_notifier(struct notifier_block *nb)
{
	return 0;
}

static inline int ebc_notify(unsigned long event)
{
	return 0;
}
#endif

#endif
