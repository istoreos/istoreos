// SPDX-License-Identifier: GPL-2.0
/*
 * Rockchip USB3.0/PCIe Gen2/SATA/SGMII combphy driver
 *
 * Copyright (C) 2021 Rockchip Electronics Co., Ltd.
 */

#include <common.h>
#include <clk.h>
#include <dm.h>
#include <dm/lists.h>
#include <dt-bindings/phy/phy.h>
#include <generic-phy.h>
#include <syscon.h>
#include <asm/io.h>
#include <asm/arch-rockchip/clock.h>
#include <regmap.h>
#include <reset-uclass.h>

#define BIT_WRITEABLE_SHIFT		16

struct rockchip_combphy_priv;

struct combphy_reg {
	u16 offset;
	u16 bitend;
	u16 bitstart;
	u16 disable;
	u16 enable;
};

struct rockchip_combphy_grfcfg {
	struct combphy_reg pcie_mode_set;
	struct combphy_reg usb_mode_set;
	struct combphy_reg sgmii_mode_set;
	struct combphy_reg qsgmii_mode_set;
	struct combphy_reg pipe_rxterm_set;
	struct combphy_reg pipe_txelec_set;
	struct combphy_reg pipe_txcomp_set;
	struct combphy_reg pipe_clk_25m;
	struct combphy_reg pipe_clk_100m;
	struct combphy_reg pipe_phymode_sel;
	struct combphy_reg pipe_rate_sel;
	struct combphy_reg pipe_rxterm_sel;
	struct combphy_reg pipe_txelec_sel;
	struct combphy_reg pipe_txcomp_sel;
	struct combphy_reg pipe_clk_ext;
	struct combphy_reg pipe_sel_usb;
	struct combphy_reg pipe_sel_qsgmii;
	struct combphy_reg pipe_phy_status;
	struct combphy_reg con0_for_pcie;
	struct combphy_reg con1_for_pcie;
	struct combphy_reg con2_for_pcie;
	struct combphy_reg con3_for_pcie;
	struct combphy_reg con0_for_sata;
	struct combphy_reg con1_for_sata;
	struct combphy_reg con2_for_sata;
	struct combphy_reg con3_for_sata;
	struct combphy_reg pipe_con0_for_sata;
	struct combphy_reg pipe_con1_for_sata;
	struct combphy_reg pipe_sgmii_mac_sel;
	struct combphy_reg pipe_xpcs_phy_ready;
	struct combphy_reg u3otg0_port_en;
	struct combphy_reg u3otg1_port_en;
};

struct rockchip_combphy_cfg {
	const struct rockchip_combphy_grfcfg *grfcfg;
	int (*combphy_cfg)(struct rockchip_combphy_priv *priv);
};

struct rockchip_combphy_priv {
	u32 mode;
	void __iomem *mmio;
	struct udevice *dev;
	struct regmap *pipe_grf;
	struct regmap *phy_grf;
	struct phy *phy;
	struct reset_ctl phy_rst;
	struct clk ref_clk;
	const struct rockchip_combphy_cfg *cfg;
};

static int param_write(struct regmap *base,
		       const struct combphy_reg *reg, bool en)
{
	u32 val, mask, tmp;

	tmp = en ? reg->enable : reg->disable;
	mask = GENMASK(reg->bitend, reg->bitstart);
	val = (tmp << reg->bitstart) | (mask << BIT_WRITEABLE_SHIFT);

	return regmap_write(base, reg->offset, val);
}

static int rockchip_combphy_pcie_init(struct rockchip_combphy_priv *priv)
{
	int ret = 0;

	if (priv->cfg->combphy_cfg) {
		ret = priv->cfg->combphy_cfg(priv);
		if (ret) {
			dev_err(priv->dev, "failed to init phy for pcie\n");
			return ret;
		}
	}

	return ret;
}

static int rockchip_combphy_usb3_init(struct rockchip_combphy_priv *priv)
{
	int ret = 0;

	if (priv->cfg->combphy_cfg) {
		ret = priv->cfg->combphy_cfg(priv);
		if (ret) {
			dev_err(priv->dev, "failed to init phy for usb3\n");
			return ret;
		}
	}

	return ret;
}

static int rockchip_combphy_sata_init(struct rockchip_combphy_priv *priv)
{
	int ret = 0;

	if (priv->cfg->combphy_cfg) {
		ret = priv->cfg->combphy_cfg(priv);
		if (ret) {
			dev_err(priv->dev, "failed to init phy for sata\n");
			return ret;
		}
	}

	return ret;
}

static int rockchip_combphy_sgmii_init(struct rockchip_combphy_priv *priv)
{
	int ret = 0;

	if (priv->cfg->combphy_cfg) {
		ret = priv->cfg->combphy_cfg(priv);
		if (ret) {
			dev_err(priv->dev, "failed to init phy for sgmii\n");
			return ret;
		}
	}

	return ret;
}

static int rockchip_combphy_set_mode(struct rockchip_combphy_priv *priv)
{
	switch (priv->mode) {
	case PHY_TYPE_PCIE:
		rockchip_combphy_pcie_init(priv);
		break;
	case PHY_TYPE_USB3:
		rockchip_combphy_usb3_init(priv);
		break;
	case PHY_TYPE_SATA:
		rockchip_combphy_sata_init(priv);
		break;
	case PHY_TYPE_SGMII:
	case PHY_TYPE_QSGMII:
		return rockchip_combphy_sgmii_init(priv);
	default:
		dev_err(priv->dev, "incompatible PHY type\n");
		return -EINVAL;
	}

	return 0;
}

static int rockchip_combphy_init(struct phy *phy)
{
	struct rockchip_combphy_priv *priv = dev_get_priv(phy->dev);
	int ret;

	ret = clk_enable(&priv->ref_clk);
	if (ret < 0 && ret != -ENOSYS)
		return ret;

	ret = rockchip_combphy_set_mode(priv);
	if (ret)
		goto err_clk;

	reset_deassert(&priv->phy_rst);

	return 0;

err_clk:
	clk_disable(&priv->ref_clk);

	return ret;
}

static int rockchip_combphy_exit(struct phy *phy)
{
	struct rockchip_combphy_priv *priv = dev_get_priv(phy->dev);

	clk_disable(&priv->ref_clk);
	reset_assert(&priv->phy_rst);

	return 0;
}

static int rockchip_combphy_xlate(struct phy *phy, struct ofnode_phandle_args *args)
{
	struct rockchip_combphy_priv *priv = dev_get_priv(phy->dev);

	if (args->args_count != 1) {
		pr_err("invalid number of arguments\n");
		return -EINVAL;
	}

	priv->mode = args->args[0];

	return 0;
}

static const struct phy_ops rochchip_combphy_ops = {
	.init = rockchip_combphy_init,
	.exit = rockchip_combphy_exit,
	.of_xlate = rockchip_combphy_xlate,
};

static int rockchip_combphy_parse_dt(struct udevice *dev,
				     struct rockchip_combphy_priv *priv)
{
	struct udevice *syscon;
	int ret;
	u32 vals[4];

	ret = uclass_get_device_by_phandle(UCLASS_SYSCON, dev, "rockchip,pipe-grf", &syscon);
	if (ret) {
		dev_err(dev, "failed to find peri_ctrl pipe-grf regmap ret= %d\n", ret);
		return ret;
	}
	priv->pipe_grf = syscon_get_regmap(syscon);

	ret = uclass_get_device_by_phandle(UCLASS_SYSCON, dev, "rockchip,pipe-phy-grf", &syscon);
	if (ret) {
		dev_err(dev, "failed to find peri_ctrl pipe-phy-grf regmap\n");
		return ret;
	}
	priv->phy_grf = syscon_get_regmap(syscon);

	ret = clk_get_by_index(dev, 0, &priv->ref_clk);
	if (ret) {
		dev_err(dev, "failed to find ref clock\n");
		return PTR_ERR(&priv->ref_clk);
	}

	ret = reset_get_by_name(dev, "combphy", &priv->phy_rst);
	if (ret) {
		dev_err(dev, "no phy reset control specified\n");
		return ret;
	}

	if (!dev_read_u32_array(dev, "rockchip,pcie1ln-sel-bits",
				vals, ARRAY_SIZE(vals)))
		regmap_write(priv->pipe_grf, vals[0],
			     (GENMASK(vals[2], vals[1]) << 16) | vals[3]);

	return 0;
}

static int rockchip_combphy_probe(struct udevice *udev)
{
	struct rockchip_combphy_priv *priv = dev_get_priv(udev);
	const struct rockchip_combphy_cfg *phy_cfg;
	int ret;

	priv->mmio = (void __iomem *)dev_read_addr(udev);
	if (IS_ERR(priv->mmio))
		return PTR_ERR(priv->mmio);

	phy_cfg = (const struct rockchip_combphy_cfg *)dev_get_driver_data(udev);
	if (!phy_cfg) {
		dev_err(udev, "No OF match data provided\n");
		return -EINVAL;
	}

	priv->dev = udev;
	priv->mode = PHY_TYPE_SATA;
	priv->cfg = phy_cfg;

	ret = rockchip_combphy_parse_dt(udev, priv);
	if (ret)
		return ret;

	ret = rockchip_combphy_set_mode(priv);

	return ret;
}

static int rk3568_combphy_cfg(struct rockchip_combphy_priv *priv)
{
	const struct rockchip_combphy_grfcfg *cfg = priv->cfg->grfcfg;
	u32 val;

	switch (priv->mode) {
	case PHY_TYPE_PCIE:
		/* Set SSC downward spread spectrum */
		val = readl(priv->mmio + (0x1f << 2));
		val &= ~GENMASK(5, 4);
		val |= 0x01 << 4;
		writel(val, priv->mmio + 0x7c);

		param_write(priv->phy_grf, &cfg->con0_for_pcie, true);
		param_write(priv->phy_grf, &cfg->con1_for_pcie, true);
		param_write(priv->phy_grf, &cfg->con2_for_pcie, true);
		param_write(priv->phy_grf, &cfg->con3_for_pcie, true);
		break;
	case PHY_TYPE_USB3:
		/* Set SSC downward spread spectrum */
		val = readl(priv->mmio + (0x1f << 2));
		val &= ~GENMASK(5, 4);
		val |= 0x01 << 4;
		writel(val, priv->mmio + 0x7c);

		/* Enable adaptive CTLE for USB3.0 Rx */
		val = readl(priv->mmio + (0x0e << 2));
		val &= ~GENMASK(0, 0);
		val |= 0x01;
		writel(val, priv->mmio + (0x0e << 2));

		/* Set PLL KVCO fine tuning signals */
		val = readl(priv->mmio + (0x20 << 2));
		val &= ~(0x7 << 2);
		val |= 0x2 << 2;
		writel(val, priv->mmio + (0x20 << 2));

		/* Set PLL LPF R1 to su_trim[10:7]=1001 */
		writel(0x4, priv->mmio + (0xb << 2));

		/* Set PLL input clock divider 1/2 */
		val = readl(priv->mmio + (0x5 << 2));
		val &= ~(0x3 << 6);
		val |= 0x1 << 6;
		writel(val, priv->mmio + (0x5 << 2));

		/* Set PLL loop divider */
		writel(0x32, priv->mmio + (0x11 << 2));

		/* Set PLL KVCO to min and set PLL charge pump current to max */
		writel(0xf0, priv->mmio + (0xa << 2));

		param_write(priv->phy_grf, &cfg->pipe_sel_usb, true);
		param_write(priv->phy_grf, &cfg->pipe_txcomp_sel, false);
		param_write(priv->phy_grf, &cfg->pipe_txelec_sel, false);
		param_write(priv->phy_grf, &cfg->usb_mode_set, true);
		break;
	case PHY_TYPE_SATA:
		writel(0x41, priv->mmio + 0x38);
		writel(0x8F, priv->mmio + 0x18);
		param_write(priv->phy_grf, &cfg->con0_for_sata, true);
		param_write(priv->phy_grf, &cfg->con1_for_sata, true);
		param_write(priv->phy_grf, &cfg->con2_for_sata, true);
		param_write(priv->phy_grf, &cfg->con3_for_sata, true);
		param_write(priv->pipe_grf, &cfg->pipe_con0_for_sata, true);
		break;
	case PHY_TYPE_SGMII:
		param_write(priv->pipe_grf, &cfg->pipe_xpcs_phy_ready, true);
		param_write(priv->phy_grf, &cfg->pipe_phymode_sel, true);
		param_write(priv->phy_grf, &cfg->pipe_sel_qsgmii, true);
		param_write(priv->phy_grf, &cfg->sgmii_mode_set, true);
		break;
	case PHY_TYPE_QSGMII:
		param_write(priv->pipe_grf, &cfg->pipe_xpcs_phy_ready, true);
		param_write(priv->phy_grf, &cfg->pipe_phymode_sel, true);
		param_write(priv->phy_grf, &cfg->pipe_rate_sel, true);
		param_write(priv->phy_grf, &cfg->pipe_sel_qsgmii, true);
		param_write(priv->phy_grf, &cfg->qsgmii_mode_set, true);
		break;
	default:
		pr_err("%s, phy-type %d\n", __func__, priv->mode);
		return -EINVAL;
	}

	/* The default ref clock is 25Mhz */
	param_write(priv->phy_grf, &cfg->pipe_clk_25m, true);

	if (dev_read_bool(priv->dev, "rockchip,enable-ssc")) {
		val = readl(priv->mmio + (0x7 << 2));
		val |= BIT(4);
		writel(val, priv->mmio + (0x7 << 2));
	}

	return 0;
}

static const struct rockchip_combphy_grfcfg rk3568_combphy_grfcfgs = {
	/* pipe-phy-grf */
	.pcie_mode_set		= { 0x0000, 5, 0, 0x00, 0x11 },
	.usb_mode_set		= { 0x0000, 5, 0, 0x00, 0x04 },
	.sgmii_mode_set		= { 0x0000, 5, 0, 0x00, 0x01 },
	.qsgmii_mode_set	= { 0x0000, 5, 0, 0x00, 0x21 },
	.pipe_rxterm_set	= { 0x0000, 12, 12, 0x00, 0x01 },
	.pipe_txelec_set	= { 0x0004, 1, 1, 0x00, 0x01 },
	.pipe_txcomp_set	= { 0x0004, 4, 4, 0x00, 0x01 },
	.pipe_clk_25m		= { 0x0004, 14, 13, 0x00, 0x01 },
	.pipe_clk_100m		= { 0x0004, 14, 13, 0x00, 0x02 },
	.pipe_phymode_sel	= { 0x0008, 1, 1, 0x00, 0x01 },
	.pipe_rate_sel		= { 0x0008, 2, 2, 0x00, 0x01 },
	.pipe_rxterm_sel	= { 0x0008, 8, 8, 0x00, 0x01 },
	.pipe_txelec_sel	= { 0x0008, 12, 12, 0x00, 0x01 },
	.pipe_txcomp_sel	= { 0x0008, 15, 15, 0x00, 0x01 },
	.pipe_clk_ext		= { 0x000c, 9, 8, 0x02, 0x01 },
	.pipe_sel_usb		= { 0x000c, 14, 13, 0x00, 0x01 },
	.pipe_sel_qsgmii	= { 0x000c, 15, 13, 0x00, 0x07 },
	.pipe_phy_status	= { 0x0034, 6, 6, 0x01, 0x00 },
	.con0_for_pcie		= { 0x0000, 15, 0, 0x00, 0x1000 },
	.con1_for_pcie		= { 0x0004, 15, 0, 0x00, 0x0000 },
	.con2_for_pcie		= { 0x0008, 15, 0, 0x00, 0x0101 },
	.con3_for_pcie		= { 0x000c, 15, 0, 0x00, 0x0200 },
	.con0_for_sata		= { 0x0000, 15, 0, 0x00, 0x0119 },
	.con1_for_sata		= { 0x0004, 15, 0, 0x00, 0x0040 },
	.con2_for_sata		= { 0x0008, 15, 0, 0x00, 0x80c3 },
	.con3_for_sata		= { 0x000c, 15, 0, 0x00, 0x4407 },
	/* pipe-grf */
	.pipe_con0_for_sata	= { 0x0000, 15, 0, 0x00, 0x2220 },
	.pipe_sgmii_mac_sel	= { 0x0040, 1, 1, 0x00, 0x01 },
	.pipe_xpcs_phy_ready	= { 0x0040, 2, 2, 0x00, 0x01 },
	.u3otg0_port_en		= { 0x0104, 15, 0, 0x0181, 0x1100 },
	.u3otg1_port_en		= { 0x0144, 15, 0, 0x0181, 0x1100 },
};

static const struct rockchip_combphy_cfg rk3568_combphy_cfgs = {
	.grfcfg		= &rk3568_combphy_grfcfgs,
	.combphy_cfg	= rk3568_combphy_cfg,
};

static int rk3588_combphy_cfg(struct rockchip_combphy_priv *priv)
{
	const struct rockchip_combphy_grfcfg *cfg = priv->cfg->grfcfg;
	u32 val;

	switch (priv->mode) {
	case PHY_TYPE_PCIE:
		param_write(priv->phy_grf, &cfg->con0_for_pcie, true);
		param_write(priv->phy_grf, &cfg->con1_for_pcie, true);
		param_write(priv->phy_grf, &cfg->con2_for_pcie, true);
		param_write(priv->phy_grf, &cfg->con3_for_pcie, true);
		break;
	case PHY_TYPE_USB3:
		/* Set SSC downward spread spectrum */
		val = readl(priv->mmio + (0x1f << 2));
		val &= ~GENMASK(5, 4);
		val |= 0x01 << 4;
		writel(val, priv->mmio + 0x7c);

		/* Enable adaptive CTLE for USB3.0 Rx */
		val = readl(priv->mmio + (0x0e << 2));
		val &= ~GENMASK(0, 0);
		val |= 0x01;
		writel(val, priv->mmio + (0x0e << 2));

		/* Set PLL KVCO fine tuning signals */
		val = readl(priv->mmio + (0x20 << 2));
		val &= ~(0x7 << 2);
		val |= 0x2 << 2;
		writel(val, priv->mmio + (0x20 << 2));

		/* Set PLL LPF R1 to su_trim[10:7]=1001 */
		writel(0x4, priv->mmio + (0xb << 2));

		/* Set PLL input clock divider 1/2 */
		val = readl(priv->mmio + (0x5 << 2));
		val &= ~(0x3 << 6);
		val |= 0x1 << 6;
		writel(val, priv->mmio + (0x5 << 2));

		/* Set PLL loop divider */
		writel(0x32, priv->mmio + (0x11 << 2));

		/* Set PLL KVCO to min and set PLL charge pump current to max */
		writel(0xf0, priv->mmio + (0xa << 2));

		param_write(priv->phy_grf, &cfg->pipe_txcomp_sel, false);
		param_write(priv->phy_grf, &cfg->pipe_txelec_sel, false);
		param_write(priv->phy_grf, &cfg->usb_mode_set, true);
		break;
	case PHY_TYPE_SATA:
		param_write(priv->phy_grf, &cfg->con0_for_sata, true);
		param_write(priv->phy_grf, &cfg->con1_for_sata, true);
		param_write(priv->phy_grf, &cfg->con2_for_sata, true);
		param_write(priv->phy_grf, &cfg->con3_for_sata, true);
		param_write(priv->pipe_grf, &cfg->pipe_con0_for_sata, true);
		param_write(priv->pipe_grf, &cfg->pipe_con1_for_sata, true);
		break;
	case PHY_TYPE_SGMII:
	case PHY_TYPE_QSGMII:
	default:
		dev_err(priv->dev, "incompatible PHY type\n");
		return -EINVAL;
	}

	/* 100MHz refclock signal is good */
	clk_set_rate(&priv->ref_clk, 100000000);
	param_write(priv->phy_grf, &cfg->pipe_clk_100m, true);

	return 0;
}

static const struct rockchip_combphy_grfcfg rk3588_combphy_grfcfgs = {
	/* pipe-phy-grf */
	.pcie_mode_set		= { 0x0000, 5, 0, 0x00, 0x11 },
	.usb_mode_set		= { 0x0000, 5, 0, 0x00, 0x04 },
	.pipe_rxterm_set	= { 0x0000, 12, 12, 0x00, 0x01 },
	.pipe_txelec_set	= { 0x0004, 1, 1, 0x00, 0x01 },
	.pipe_txcomp_set	= { 0x0004, 4, 4, 0x00, 0x01 },
	.pipe_clk_25m		= { 0x0004, 14, 13, 0x00, 0x01 },
	.pipe_clk_100m		= { 0x0004, 14, 13, 0x00, 0x02 },
	.pipe_rxterm_sel	= { 0x0008, 8, 8, 0x00, 0x01 },
	.pipe_txelec_sel	= { 0x0008, 12, 12, 0x00, 0x01 },
	.pipe_txcomp_sel	= { 0x0008, 15, 15, 0x00, 0x01 },
	.pipe_clk_ext		= { 0x000c, 9, 8, 0x02, 0x01 },
	.pipe_phy_status	= { 0x0034, 6, 6, 0x01, 0x00 },
	.con0_for_pcie		= { 0x0000, 15, 0, 0x00, 0x1000 },
	.con1_for_pcie		= { 0x0004, 15, 0, 0x00, 0x0000 },
	.con2_for_pcie		= { 0x0008, 15, 0, 0x00, 0x0101 },
	.con3_for_pcie		= { 0x000c, 15, 0, 0x00, 0x0200 },
	.con0_for_sata		= { 0x0000, 15, 0, 0x00, 0x0129 },
	.con1_for_sata		= { 0x0004, 15, 0, 0x00, 0x0040 },
	.con2_for_sata		= { 0x0008, 15, 0, 0x00, 0x80c1 },
	.con3_for_sata		= { 0x000c, 15, 0, 0x00, 0x0407 },
	/* pipe-grf */
	.pipe_con0_for_sata	= { 0x0000, 11, 5, 0x00, 0x22 },
	.pipe_con1_for_sata	= { 0x0000, 2, 0, 0x00, 0x2 },
};

static const struct rockchip_combphy_cfg rk3588_combphy_cfgs = {
	.grfcfg		= &rk3588_combphy_grfcfgs,
	.combphy_cfg	= rk3588_combphy_cfg,
};

static const struct udevice_id rockchip_combphy_ids[] = {
	{
		.compatible = "rockchip,rk3568-naneng-combphy",
		.data = (ulong)&rk3568_combphy_cfgs
	},
	{
		.compatible = "rockchip,rk3588-naneng-combphy",
		.data = (ulong)&rk3588_combphy_cfgs
	},
	{ }
};

U_BOOT_DRIVER(rockchip_naneng_combphy) = {
	.name		= "naneng-combphy",
	.id		= UCLASS_PHY,
	.of_match	= rockchip_combphy_ids,
	.ops		= &rochchip_combphy_ops,
	.probe		= rockchip_combphy_probe,
	.priv_auto_alloc_size = sizeof(struct rockchip_combphy_priv),
};
