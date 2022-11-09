/* SPDX-License-Identifier:     GPL-2.0 */
/*
 * Copyright (C) 2020 Rockchip Electronics Co., Ltd
 */

#ifndef _PHY_ROCKCHIP_INNO_USB3_H
#define _PHY_ROCKCHIP_INNO_USB3_H

#if CONFIG_IS_ENABLED(PHY_ROCKCHIP_INNO_USB3)
int rockchip_u3phy_uboot_init(void);
#else
static inline int rockchip_u3phy_uboot_init(void)
{
	return -ENOTSUPP;
}
#endif

#endif /* _PHY_ROCKCHIP_INNO_USB3_H */
