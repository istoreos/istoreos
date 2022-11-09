// SPDX-License-Identifier: GPL-2.0
/*
 * Rockchip PCIE3.0 phy driver
 *
 * Copyright (C) 2021 Rockchip Electronics Co., Ltd.
 */

#include <common.h>
#include <clk.h>
#include <dm.h>
#include <dm/lists.h>
#include <generic-phy.h>
#include <syscon.h>
#include <asm/io.h>
#include <asm/arch-rockchip/clock.h>
#include <regmap.h>
#include <reset-uclass.h>

/* Register for RK3568 */
#define GRF_PCIE30PHY_RK3568_CON1 0x4
#define GRF_PCIE30PHY_RK3568_CON6 0x18
#define GRF_PCIE30PHY_RK3568_CON9 0x24

/* Register for RK3588 */
#define PHP_GRF_PCIESEL_CON 0x100
#define RK3588_PCIE3PHY_GRF_CMN_CON0 0x0
#define RK3588_PCIE3PHY_GRF_PHY0_STATUS1 0x904
#define RK3588_PCIE3PHY_GRF_PHY1_STATUS1 0xa04

/*
 * pcie30_phy_mode[2:0]
 * bit2: aggregation
 * bit1: bifurcation for port 1
 * bit0: bifurcation for port 0
 */
#define PHY_MODE_PCIE_AGGREGATION 4     /* PCIe3x4 */
#define PHY_MODE_PCIE_NANBNB    0       /* P1:PCIe3x2  +  P0:PCIe3x2 */
#define PHY_MODE_PCIE_NANBBI    1       /* P1:PCIe3x2  +  P0:PCIe3x1*2 */
#define PHY_MODE_PCIE_NABINB    2       /* P1:PCIe3x1*2 + P0:PCIe3x2 */
#define PHY_MODE_PCIE_NABIBI    3       /* P1:PCIe3x1*2 + P0:PCIe3x1*2 */

struct rockchip_p3phy_ops;

struct rockchip_p3phy_priv {
	const struct rockchip_p3phy_ops *ops;
	struct clk_bulk clks;
	void __iomem *mmio;
	int mode;
	struct regmap *phy_grf;
	struct regmap *pipe_grf;
	struct reset_ctl p30phy;
	bool is_bifurcation;
	/* pcie30_phymode: Aggregation, Bifurcation */
	int pcie30_phymode;
};

struct rockchip_p3phy_ops {
	int (*phy_init)(struct rockchip_p3phy_priv *priv);
};

static int rockchip_p3phy_rk3568_init(struct rockchip_p3phy_priv *priv)
{
	/* Deassert PCIe PMA output clamp mode */
	regmap_write(priv->phy_grf, GRF_PCIE30PHY_RK3568_CON9,
		     (0x1 << 15) | (0x1 << 31));

	/* Set bifurcation if needed */
	if (priv->is_bifurcation) {
		regmap_write(priv->phy_grf, GRF_PCIE30PHY_RK3568_CON6,
			     0x1 | (0xf << 16));
		regmap_write(priv->phy_grf, GRF_PCIE30PHY_RK3568_CON1,
			     (0x1 << 15) | (0x1 << 31));
	}

	return 0;
}

static const struct rockchip_p3phy_ops rk3568_ops = {
	.phy_init = &rockchip_p3phy_rk3568_init,
};

static int rockchip_p3phy_rk3588_init(struct rockchip_p3phy_priv *priv)
{
	u32 reg;
	u32 timeout;

	/* Deassert PCIe PMA output clamp mode */
	regmap_write(priv->phy_grf, RK3588_PCIE3PHY_GRF_CMN_CON0,
		     (0x1 << 8) | (0x1 << 24));

	/* Select correct pcie30_phymode */
	if (priv->pcie30_phymode > 4)
		priv->pcie30_phymode = PHY_MODE_PCIE_AGGREGATION;

	regmap_write(priv->phy_grf, RK3588_PCIE3PHY_GRF_CMN_CON0,
		     (0x7<<16) | priv->pcie30_phymode);

	/* Set pcie1ln_sel in PHP_GRF_PCIESEL_CON */
	reg = priv->pcie30_phymode & 3;
	if (reg)
		regmap_write(priv->pipe_grf, PHP_GRF_PCIESEL_CON,
			     (reg << 16) | reg);

	timeout = 500;
	while (timeout--) {
		regmap_read(priv->phy_grf, RK3588_PCIE3PHY_GRF_PHY0_STATUS1, &reg);
		if (reg & 0x1)
			break;
		udelay(1);
	}

	if (timeout <= 0) {
		pr_err("%s: phy0 lock failed, check input refclk and power supply\n", __func__);
		return -ETIMEDOUT;
	}

	timeout = 500;
	while (timeout--) {
		regmap_read(priv->phy_grf, RK3588_PCIE3PHY_GRF_PHY1_STATUS1, &reg);
		if (reg & 0x1)
			break;
		udelay(1);
	}

	if (timeout <= 0) {
		pr_err("%s: phy1 lock failed, check input refclk and power supply\n", __func__);
		return -ETIMEDOUT;
	}

	return 0;
}

static const struct rockchip_p3phy_ops rk3588_ops = {
	.phy_init = &rockchip_p3phy_rk3588_init,
};

static int rochchip_p3phy_init(struct phy *phy)
{
	struct rockchip_p3phy_priv *priv = dev_get_priv(phy->dev);
	int ret;

	ret = clk_enable_bulk(&priv->clks);
	if (ret) {
		pr_err("failed to enable clks (ret=%d)\n", ret);
		return ret;
	}

	reset_assert(&priv->p30phy);
	udelay(1);

	if (priv->ops->phy_init) {
		ret = priv->ops->phy_init(priv);
		if (ret) {
			clk_disable_bulk(&priv->clks);
			return ret;
		}

	}

	reset_deassert(&priv->p30phy);
	udelay(5);

#ifdef CONFIG_ROCKCHIP_RK3568
	/* Updata RX VCO calibration controls */
	writel(0x2800, priv->mmio + (0x104a << 2));
	writel(0x2800, priv->mmio + (0x114a << 2));
	udelay(10);
#endif

	return 0;
}

static int rochchip_p3phy_exit(struct phy *phy)
{
	struct rockchip_p3phy_priv *priv = dev_get_priv(phy->dev);

	clk_disable_bulk(&priv->clks);
	reset_assert(&priv->p30phy);
	return 0;
}

static int rockchip_p3phy_probe(struct udevice *dev)
{
	struct rockchip_p3phy_priv *priv = dev_get_priv(dev);
	dev_get_driver_data(dev);
	struct udevice *syscon;
	int ret;

	priv->mmio = (void __iomem *)dev_read_addr(dev);
	if ((fdt_addr_t)priv->mmio == FDT_ADDR_T_NONE)
		return -EINVAL;

	priv->ops = (struct rockchip_p3phy_ops *)dev_get_driver_data(dev);
	if (!priv->ops) {
		dev_err(dev, "no of match data provided\n");
		return -EINVAL;
	}

	ret = uclass_get_device_by_phandle(UCLASS_SYSCON, dev,
					   "rockchip,phy-grf",  &syscon);
	if (ret) {
		pr_err("unable to find syscon device for rockchip,phy-grf\n");
		return ret;
	}

	priv->phy_grf = syscon_get_regmap(syscon);
	if (IS_ERR(priv->phy_grf)) {
		dev_err(dev, "failed to find rockchip,phy_grf regmap\n");
		return PTR_ERR(priv->phy_grf);
	}

	dev_dbg(priv->dev, "phy_grf is 0x%llx\n", priv->phy_grf->base);

	ret = uclass_get_device_by_phandle(UCLASS_SYSCON, dev,
					   "rockchip,pipe-grf",  &syscon);
	if (ret) {
		/* It's optional, rk3568 doesn't need it */
		priv->pipe_grf = NULL;
		pr_err("unable to get syscon device for rockchip,pipe-grf\n");
		goto skip_pipe_grf;
	}

	priv->pipe_grf = syscon_get_regmap(syscon);
	if (IS_ERR(priv->pipe_grf))
		dev_err(dev, "failed to find rockchip,pipe_grf regmap\n");


	priv->pcie30_phymode = dev_read_u32_default(dev, "rockchip,pcie30-phymode", PHY_MODE_PCIE_AGGREGATION);

skip_pipe_grf:
	ret = reset_get_by_name(dev, "phy", &priv->p30phy);
	if (ret) {
		dev_err(dev, "no phy reset control specified\n");
		return ret;
	}

	if (ret) {
		dev_err(dev, "Can't get clock: %d\n", ret);
		return ret;
	}

	return 0;
}

static int rockchip_p3phy_configure(struct phy *phy, union phy_configure_opts *opts)
{
	struct rockchip_p3phy_priv *priv = dev_get_priv(phy->dev);

	priv->is_bifurcation = opts->pcie.is_bifurcation;

	return 0;
}

static struct phy_ops rochchip_p3phy_ops = {
	.init = rochchip_p3phy_init,
	.exit = rochchip_p3phy_exit,
	.configure = rockchip_p3phy_configure,
};

static const struct udevice_id rockchip_p3phy_of_match[] = {
	{ .compatible = "rockchip,rk3568-pcie3-phy", .data = (ulong)&rk3568_ops},
	{ .compatible = "rockchip,rk3588-pcie3-phy", .data = (ulong)&rk3588_ops },
	{ },
};

U_BOOT_DRIVER(rockchip_pcie3phy) = {
	.name		= "rockchip_pcie3phy",
	.id		= UCLASS_PHY,
	.of_match	= rockchip_p3phy_of_match,
	.ops		= &rochchip_p3phy_ops,
	.probe		= rockchip_p3phy_probe,
	.priv_auto_alloc_size = sizeof(struct rockchip_p3phy_priv),
};
