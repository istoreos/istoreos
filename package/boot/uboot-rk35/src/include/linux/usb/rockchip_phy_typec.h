/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright (C) 2020 Rockchip Electronics Co., Ltd
 *
 * Based on include/soc/rockchip/rockchip_phy_typec.h in Linux Kernel.
 */

#ifndef __LINUX_ROCKCHIP_PHY_TYPEC_H
#define __LINUX_ROCKCHIP_PHY_TYPEC_H

#include <reset.h>

struct usb3phy_reg {
	u32 offset;
	u32 enable_bit;
	u32 write_enable;
};

struct rockchip_usb3phy_port_cfg {
	struct usb3phy_reg typec_conn_dir;
	struct usb3phy_reg usb3tousb2_en;
	struct usb3phy_reg usb3host_disable;
	struct usb3phy_reg usb3host_port;
	struct usb3phy_reg external_psm;
	struct usb3phy_reg pipe_status;
};

struct rockchip_typec_phy {
	struct udevice *dev;
	void __iomem *base;
	void __iomem *grf_regs;
	struct reset_ctl uphy_rst;
	struct reset_ctl pipe_rst;
	struct reset_ctl tcphy_rst;
	struct rockchip_usb3phy_port_cfg port_cfgs;
	/* mutex to protect access to individual PHYs */
	struct mutex lock;

	bool flip;
	u8 mode;
};

#if CONFIG_IS_ENABLED(PHY_ROCKCHIP_TYPEC)
int rockchip_u3phy_uboot_init(const char *name);
#else
static inline int rockchip_u3phy_uboot_init(const char *name)
{
	return -ENOTSUPP;
}
#endif

#endif /* __LINUX_ROCKCHIP_PHY_TYPEC_H */
