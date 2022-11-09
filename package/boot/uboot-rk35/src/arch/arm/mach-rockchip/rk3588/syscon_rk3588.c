/*
 * (C) Copyright 2021 Rockchip Electronics Co., Ltd
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */

#include <common.h>
#include <dm.h>
#include <syscon.h>
#include <asm/arch-rockchip/clock.h>

static const struct udevice_id rk3588_syscon_ids[] = {
	{ .compatible = "rockchip,rk3588-sys-grf", .data = ROCKCHIP_SYSCON_GRF },
	{ .compatible = "rockchip,rk3588-vop-grf", .data = ROCKCHIP_SYSCON_VOP_GRF },
	{ .compatible = "rockchip,rk3588-vo-grf",  .data = ROCKCHIP_SYSCON_VO_GRF },
	{ .compatible = "rockchip,pcie30-phy-grf", .data = ROCKCHIP_SYSCON_PCIE30_PHY_GRF },
	{ .compatible = "rockchip,rk3588-php-grf", .data = ROCKCHIP_SYSCON_PHP_GRF },
	{ .compatible = "rockchip,pipe-phy-grf",   .data = ROCKCHIP_SYSCON_PIPE_PHY0_GRF },
	{ .compatible = "rockchip,pipe-phy-grf",   .data = ROCKCHIP_SYSCON_PIPE_PHY1_GRF },
	{ .compatible = "rockchip,pipe-phy-grf",   .data = ROCKCHIP_SYSCON_PIPE_PHY2_GRF },
	{ .compatible = "rockchip,rk3588-pmu",     .data = ROCKCHIP_SYSCON_PMU },
	{ }
};

U_BOOT_DRIVER(syscon_rk3588) = {
	.name = "rk3588_syscon",
	.id = UCLASS_SYSCON,
	.of_match = rk3588_syscon_ids,
#if !CONFIG_IS_ENABLED(OF_PLATDATA)
	.bind = dm_scan_fdt_dev,
#endif
};
