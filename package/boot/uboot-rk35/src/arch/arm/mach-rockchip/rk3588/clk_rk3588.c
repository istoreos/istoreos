/*
 * (C) Copyright 2020 Rockchip Electronics Co., Ltd.
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <common.h>
#include <dm.h>
#include <syscon.h>
#include <asm/arch-rockchip/clock.h>
#include <asm/arch-rockchip/cru_rk3588.h>

int rockchip_get_clk(struct udevice **devp)
{
	return uclass_get_device_by_driver(UCLASS_CLK,
			DM_GET_DRIVER(rockchip_rk3588_cru), devp);
}

#if CONFIG_IS_ENABLED(CLK_SCMI)
int rockchip_get_scmi_clk(struct udevice **devp)
{
	return uclass_get_device_by_driver(UCLASS_CLK,
			DM_GET_DRIVER(scmi_clock), devp);
}
#endif

void *rockchip_get_cru(void)
{
	struct rk3588_clk_priv *priv;
	struct udevice *dev;
	int ret;

	ret = rockchip_get_clk(&dev);
	if (ret)
		return ERR_PTR(ret);

	priv = dev_get_priv(dev);

	return priv->cru;
}

