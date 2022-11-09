/*
 * (C) Copyright 2020 Rockchip Electronics Co., Ltd
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */

#include <common.h>
#include <dm.h>
#include <syscon.h>
#include <asm/arch-rockchip/clock.h>

static const struct udevice_id rk3568_syscon_ids[] = {
	{ .compatible = "rockchip,rk3568-grf", .data = ROCKCHIP_SYSCON_GRF },
	{ .compatible = "rockchip,rk3568-pmugrf", .data = ROCKCHIP_SYSCON_PMUGRF },
	{ }
};

U_BOOT_DRIVER(syscon_rk3568) = {
	.name = "rk3568_syscon",
	.id = UCLASS_SYSCON,
	.of_match = rk3568_syscon_ids,
#if !CONFIG_IS_ENABLED(OF_PLATDATA)
	.bind = dm_scan_fdt_dev,
#endif
};
