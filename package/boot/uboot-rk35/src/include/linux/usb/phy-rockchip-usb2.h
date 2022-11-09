/*
 * Copyright 2017 Rockchip Electronics Co., Ltd
 *
 * SPDX-License-Identifier:    GPL-2.0+
 */

#ifndef _PHY_ROCKCHIP_USB2_H
#define _PHY_ROCKCHIP_USB2_H

extern int rockchip_chg_get_type(void);

#if defined(CONFIG_PHY_ROCKCHIP_INNO_USB2) ||\
    defined(CONFIG_ROCKCHIP_USB2_PHY) ||\
    defined(CONFIG_PHY_ROCKCHIP_NANENG_USB2)

int rockchip_u2phy_vbus_detect(void);
#else
static inline int rockchip_u2phy_vbus_detect(void)
{
	return -ENOSYS;
}
#endif

#endif /* _PHY_ROCKCHIP_USB2_H */
