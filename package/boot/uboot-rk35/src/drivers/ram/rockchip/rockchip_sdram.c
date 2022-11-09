// SPDX-License-Identifier: GPL-2.0
/*
 * (C) Copyright 2018 Rockchip Electronics Co., Ltd.
 */

#include <common.h>
#include <dm.h>
#include <ram.h>
#include <syscon.h>
#include <asm/arch-rockchip/clock.h>
#include <asm/arch-rockchip/grf_px30.h>
#include <asm/arch-rockchip/grf_rv1108.h>
#include <asm/arch-rockchip/grf_rk1808.h>
#include <asm/arch-rockchip/grf_rk3036.h>
#include <asm/arch-rockchip/grf_rk3308.h>
#include <asm/arch-rockchip/rockchip_dmc.h>
#include <asm/arch-rockchip/sdram.h>

DECLARE_GLOBAL_DATA_PTR;

#ifndef CONFIG_TPL_BUILD
struct dram_info {
	struct ram_info info;
};

static int dmc_probe(struct udevice *dev)
{
	int ret = 0;
	struct dram_info *priv = dev_get_priv(dev);

	if (!(gd->flags & GD_FLG_RELOC)) {
#if defined(CONFIG_ROCKCHIP_RV1108)
		struct rv1108_grf *grf =
			syscon_get_first_range(ROCKCHIP_SYSCON_GRF);

		priv->info.size =
			rockchip_sdram_size((phys_addr_t)&grf->os_reg2);
#elif defined(CONFIG_ROCKCHIP_RK3036)
		struct rk3036_grf *grf =
			syscon_get_first_range(ROCKCHIP_SYSCON_GRF);

		priv->info.size =
			rockchip_sdram_size((phys_addr_t)&grf->os_reg[1]);
#elif defined(CONFIG_ROCKCHIP_RK3308)
		struct rk3308_grf *grf =
			syscon_get_first_range(ROCKCHIP_SYSCON_GRF);

		priv->info.size =
			rockchip_sdram_size((phys_addr_t)&grf->os_reg2);
#elif defined(CONFIG_ROCKCHIP_PX30)
		struct px30_pmugrf *pmugrf =
			syscon_get_first_range(ROCKCHIP_SYSCON_PMUGRF);

		priv->info.size =
			rockchip_sdram_size((phys_addr_t)&pmugrf->os_reg[2]);
#elif defined(CONFIG_ROCKCHIP_RK1808)
		struct rk1808_pmugrf *pmugrf =
			syscon_get_first_range(ROCKCHIP_SYSCON_PMUGRF);

		priv->info.size =
			rockchip_sdram_size((phys_addr_t)&pmugrf->os_reg[2]);
#else
#error chip error
#endif
		priv->info.base = CONFIG_SYS_SDRAM_BASE;
	} else {
#if defined(CONFIG_ROCKCHIP_PX30)
#if !defined(CONFIG_SPL_BUILD) && defined(CONFIG_ROCKCHIP_DMC)
		ret = rockchip_dmcfreq_probe(dev);
#endif
#endif
	}

	return ret;
}

static int dmc_get_info(struct udevice *dev, struct ram_info *info)
{
	struct dram_info *priv = dev_get_priv(dev);

	*info = priv->info;

	return 0;
}

static struct ram_ops dmc_ops = {
	.get_info = dmc_get_info,
};

static const struct udevice_id dmc_ids[] = {
#if defined(CONFIG_ROCKCHIP_RV1108)
	{ .compatible = "rockchip,rv1108-dmc" },
#elif defined(CONFIG_ROCKCHIP_RK3036)
	{ .compatible = "rockchip,rk3036-dmc" },
#elif defined(CONFIG_ROCKCHIP_RK3308)
	{ .compatible = "rockchip,rk3308-dmc" },
#elif defined(CONFIG_ROCKCHIP_PX30)
	{ .compatible = "rockchip,px30-dmc" },
#elif defined(CONFIG_ROCKCHIP_RK1808)
	{ .compatible = "rockchip,rk1808-dmc" },
#endif
	{ }
};

U_BOOT_DRIVER(dmc_tiny) = {
	.name = "rockchip_dmc",
	.id = UCLASS_RAM,
	.of_match = dmc_ids,
	.ops = &dmc_ops,
	.probe = dmc_probe,
	.priv_auto_alloc_size = sizeof(struct dram_info),
};
#endif
