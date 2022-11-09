// SPDX-License-Identifier: GPL-2.0
/*
 * Rockchip PCIE3.0 phy driver
 *
 * Copyright (C) 2020 Rockchip Electronics Co., Ltd.
 */

#include <linux/clk.h>
#include <linux/delay.h>
#include <linux/io.h>
#include <linux/iopoll.h>
#include <linux/kernel.h>
#include <linux/mfd/syscon.h>
#include <linux/module.h>
#include <linux/of_device.h>
#include <linux/phy/phy.h>
#include <linux/regmap.h>
#include <linux/reset.h>
#include <dt-bindings/phy/phy.h>

#define GRF_PCIE30PHY_CON1 0x4
#define GRF_PCIE30PHY_CON4 0x10
#define GRF_PCIE30PHY_CON6 0x18
#define GRF_PCIE30PHY_CON9 0x24
#define GRF_PCIE30PHY_STATUS0 0x80
#define SRAM_INIT_DONE(reg) (reg & BIT(14))

struct rockchip_p3phy_priv {
	void __iomem *mmio;
	int mode;
	struct regmap *phy_grf;
	struct reset_control *p30phy;
	struct clk *ref_clk_m;
	struct clk *ref_clk_n;
	struct clk *pclk;
	struct phy *phy;
	bool is_bifurcation;
};

static int rockchip_p3phy_set_mode(struct phy *phy, enum phy_mode mode)
{
	struct rockchip_p3phy_priv *priv = phy_get_drvdata(phy);

	/* Acutally We don't care EP/RC mode, but just record it */
	switch (mode) {
	case PHY_MODE_PCIE_RC:
		priv->mode = PHY_MODE_PCIE_RC;
		break;
	case PHY_MODE_PCIE_EP:
		priv->mode = PHY_MODE_PCIE_EP;
		break;
	case PHY_MODE_PCIE_BIFURCATION:
		priv->is_bifurcation = true;
		break;
	default:
		pr_info("%s, invalid mode\n", __func__);
		return -EINVAL;
	}

	return 0;
}

static const u16 phy_fw[] = {
	#include "phy-rockchip-snps-pcie3.fw"
};

static int rochchip_p3phy_init(struct phy *phy)
{
	struct rockchip_p3phy_priv *priv = phy_get_drvdata(phy);
	int i;
	int ret = 0;
	u32 reg;

	ret = clk_prepare_enable(priv->ref_clk_m);
	if (ret < 0)
		return ret;

	ret = clk_prepare_enable(priv->ref_clk_n);
	if (ret < 0)
		goto err_ref;

	ret = clk_prepare_enable(priv->pclk);
	if (ret < 0)
		goto err_pclk;

	reset_control_assert(priv->p30phy);
	udelay(1);

	/* Deassert PCIe PMA output clamp mode */
	regmap_write(priv->phy_grf, GRF_PCIE30PHY_CON9,
		     (0x1 << 15) | (0x1 << 31));
	/* Set bifurcation if needed, and it doesn't care RC/EP */
	if (priv->is_bifurcation) {
		regmap_write(priv->phy_grf, GRF_PCIE30PHY_CON6,
			     0x1 | (0xf << 16));
		regmap_write(priv->phy_grf, GRF_PCIE30PHY_CON1,
			     (0x1 << 15) | (0x1 << 31));
	}

	regmap_write(priv->phy_grf, GRF_PCIE30PHY_CON4,
		     (0x0 << 14) | (0x1 << (14 + 16))); //sdram_ld_done
	regmap_write(priv->phy_grf, GRF_PCIE30PHY_CON4,
		     (0x0 << 13) | (0x1 << (13 + 16))); //sdram_bypass
	reset_control_deassert(priv->p30phy);

	ret = regmap_read_poll_timeout(priv->phy_grf,
				       GRF_PCIE30PHY_STATUS0,
				       reg, SRAM_INIT_DONE(reg),
				       0, 500);
	if (ret) {
		pr_err("%s: lock failed 0x%x, check input refclk and power supply\n",
		       __func__, reg);
		goto err_pclk;
	}

	regmap_write(priv->phy_grf, GRF_PCIE30PHY_CON9,
		     (0x3 << 8) | (0x3 << (8 + 16))); //map to access sram
	for (i = 0; i < ARRAY_SIZE(phy_fw); i++)
		writel(phy_fw[i], priv->mmio + (i<<2));
	pr_info("snps pcie3phy FW update! size %ld\n", ARRAY_SIZE(phy_fw));

	regmap_write(priv->phy_grf, GRF_PCIE30PHY_CON9,
		     (0x0 << 8) | (0x3 << (8 + 16)));
	regmap_write(priv->phy_grf, GRF_PCIE30PHY_CON4,
		     (0x1 << 14) | (0x1 << (14 + 16))); //sdram_ld_done

	return 0;
err_pclk:
	clk_disable_unprepare(priv->ref_clk_n);
err_ref:
	clk_disable_unprepare(priv->ref_clk_m);
	return ret;
}

static int rochchip_p3phy_exit(struct phy *phy)
{
	struct rockchip_p3phy_priv *priv = phy_get_drvdata(phy);
	clk_disable_unprepare(priv->ref_clk_m);
	clk_disable_unprepare(priv->ref_clk_n);
	clk_disable_unprepare(priv->pclk);
	reset_control_assert(priv->p30phy);
	return 0;
}

static const struct phy_ops rochchip_p3phy_ops = {
	.init = rochchip_p3phy_init,
	.exit = rochchip_p3phy_exit,
	.set_mode = rockchip_p3phy_set_mode,
	.owner = THIS_MODULE,
};

static int rockchip_p3phy_probe(struct platform_device *pdev)
{
	struct phy_provider *phy_provider;
	struct device *dev = &pdev->dev;
	struct rockchip_p3phy_priv *priv;
	struct device_node *np = dev->of_node;
	struct resource *res;
	int ret;

	priv = devm_kzalloc(dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	priv->mmio = devm_ioremap_resource(dev, res);
	if (IS_ERR(priv->mmio)) {
		ret = PTR_ERR(priv->mmio);
		return ret;
	}

	priv->phy_grf = syscon_regmap_lookup_by_phandle(np, "rockchip,phy-grf");
	if (IS_ERR(priv->phy_grf)) {
		dev_err(dev, "failed to find rockchip,phy_grf regmap\n");
		return PTR_ERR(priv->phy_grf);
	}

	priv->phy = devm_phy_create(dev, NULL, &rochchip_p3phy_ops);
	if (IS_ERR(priv->phy)) {
		dev_err(dev, "failed to create combphy\n");
		return PTR_ERR(priv->phy);
	}

	priv->p30phy = devm_reset_control_get(dev, "phy");
	if (IS_ERR(priv->p30phy)) {
		dev_warn(dev, "no phy reset control specified\n");
		priv->p30phy = NULL;
	}

	priv->ref_clk_m = devm_clk_get(dev, "refclk_m");
	if (IS_ERR(priv->ref_clk_m)) {
		dev_err(dev, "failed to find ref clock M\n");
		return PTR_ERR(priv->ref_clk_m);
	}

	priv->ref_clk_n = devm_clk_get(dev, "refclk_n");
	if (IS_ERR(priv->ref_clk_n)) {
		dev_err(dev, "failed to find ref clock N\n");
		return PTR_ERR(priv->ref_clk_n);
	}

	priv->pclk = devm_clk_get(dev, "pclk");
	if (IS_ERR(priv->pclk)) {
		dev_err(dev, "failed to find pclk\n");
		return PTR_ERR(priv->pclk);
	}

	dev_set_drvdata(dev, priv);
	phy_set_drvdata(priv->phy, priv);
	phy_provider = devm_of_phy_provider_register(dev, of_phy_simple_xlate);
	return PTR_ERR_OR_ZERO(phy_provider);
}

static const struct of_device_id rockchip_p3phy_of_match[] = {
	{ .compatible = "rockchip,rk3568-pcie3-phy" },
	{ },
};
MODULE_DEVICE_TABLE(of, rockchip_p3phy_of_match);

static struct platform_driver rockchip_p3phy_driver = {
	.probe	= rockchip_p3phy_probe,
	.driver = {
		.name = "rockchip-snps-pcie3-phy",
		.of_match_table = rockchip_p3phy_of_match,
	},
};
module_platform_driver(rockchip_p3phy_driver);
MODULE_DESCRIPTION("Rockchip Synopsys PCIe 3.0 PHY driver");
MODULE_LICENSE("GPL v2");
