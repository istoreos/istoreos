// SPDX-License-Identifier:     GPL-2.0
/*
 * Copyright (C) 2020 Rockchip Electronics Co., Ltd
 *
 * Based on drivers/phy/rockchip/phy-rockchip-typec.c in Linux Kernel.
 */

#include <common.h>
#include <dm.h>
#include <dm/lists.h>
#include <dm/of_access.h>
#include <generic-phy.h>
#include <power/regulator.h>
#include <regmap.h>
#include <reset.h>
#include <syscon.h>
#include <asm-generic/io.h>
#include <asm/arch-rockchip/clock.h>
#include <linux/iopoll.h>
#include <linux/usb/rockchip_phy_typec.h>

#define CMN_PLL0_VCOCAL_OVRD		(0x83 << 2)
#define CMN_PLL0_VCOCAL_INIT		(0x84 << 2)
#define CMN_PLL0_VCOCAL_ITER		(0x85 << 2)
#define CMN_PLL0_LOCK_REFCNT_START	(0x90 << 2)
#define CMN_PLL0_LOCK_PLLCNT_START	(0x92 << 2)
#define CMN_PLL0_LOCK_PLLCNT_THR	(0x93 << 2)
#define CMN_PLL0_INTDIV			(0x94 << 2)
#define CMN_PLL0_FRACDIV		(0x95 << 2)
#define CMN_PLL0_HIGH_THR		(0x96 << 2)
#define CMN_PLL0_DSM_DIAG		(0x97 << 2)
#define CMN_PLL0_SS_CTRL1		(0x98 << 2)
#define CMN_PLL0_SS_CTRL2		(0x99 << 2)
#define CMN_DIAG_PLL0_FBH_OVRD		(0x1c0 << 2)
#define CMN_DIAG_PLL0_FBL_OVRD		(0x1c1 << 2)
#define CMN_DIAG_PLL0_OVRD		(0x1c2 << 2)
#define CMN_DIAG_PLL0_V2I_TUNE		(0x1c5 << 2)
#define CMN_DIAG_PLL0_CP_TUNE		(0x1c6 << 2)
#define CMN_DIAG_PLL0_LF_PROG		(0x1c7 << 2)
#define CMN_DIAG_HSCLK_SEL		(0x1e0 << 2)

#define TX_TXCC_MGNFS_MULT_000(n)	((0x4050 | ((n) << 9)) << 2)
#define XCVR_DIAG_PLLDRC_CTRL(n)	((0x40e0 | ((n) << 9)) << 2)
#define XCVR_DIAG_BIDI_CTRL(n)		((0x40e8 | ((n) << 9)) << 2)
#define XCVR_DIAG_LANE_FCM_EN_MGN(n)	((0x40f2 | ((n) << 9)) << 2)
#define TX_PSC_A0(n)			((0x4100 | ((n) << 9)) << 2)
#define TX_PSC_A1(n)			((0x4101 | ((n) << 9)) << 2)
#define TX_PSC_A2(n)			((0x4102 | ((n) << 9)) << 2)
#define TX_PSC_A3(n)			((0x4103 | ((n) << 9)) << 2)
#define TX_RCVDET_CTRL(n)		((0x4120 | ((n) << 9)) << 2)
#define TX_RCVDET_EN_TMR(n)		((0x4122 | ((n) << 9)) << 2)
#define TX_RCVDET_ST_TMR(n)		((0x4123 | ((n) << 9)) << 2)
#define TX_DIAG_TX_DRV(n)		((0x41e1 | ((n) << 9)) << 2)
#define TX_DIAG_BGREF_PREDRV_DELAY	(0x41e7 << 2)

#define RX_PSC_A0(n)			((0x8000 | ((n) << 9)) << 2)
#define RX_PSC_A1(n)			((0x8001 | ((n) << 9)) << 2)
#define RX_PSC_A2(n)			((0x8002 | ((n) << 9)) << 2)
#define RX_PSC_A3(n)			((0x8003 | ((n) << 9)) << 2)
#define RX_PSC_CAL(n)			((0x8006 | ((n) << 9)) << 2)
#define RX_PSC_RDY(n)			((0x8007 | ((n) << 9)) << 2)
#define RX_SIGDET_HL_FILT_TMR(n)	((0x8090 | ((n) << 9)) << 2)
#define RX_REE_CTRL_DATA_MASK(n)	((0x81bb | ((n) << 9)) << 2)
#define RX_DIAG_SIGDET_TUNE(n)		((0x81dc | ((n) << 9)) << 2)
#define RX_DIAG_SC2C_DELAY		(0x81e1 << 2)

#define PHY_ISO_CMN_CTRL		(0xc010 << 2)
#define PMA_CMN_CTRL1			(0xc800 << 2)
#define PHY_PMA_ISO_CMN_CTRL		(0xc810 << 2)
#define PHY_ISOLATION_CTRL		(0xc81f << 2)
#define PHY_PMA_ISO_XCVR_CTRL(n)	((0xcc11 | ((n) << 6)) << 2)
#define PHY_PMA_ISO_LINK_MODE(n)	((0xcc12 | ((n) << 6)) << 2)
#define PHY_PMA_ISO_PWRST_CTRL(n)	((0xcc13 | ((n) << 6)) << 2)
#define PHY_PMA_ISO_TX_DATA_LO(n)	((0xcc14 | ((n) << 6)) << 2)
#define PHY_PMA_ISO_TX_DATA_HI(n)	((0xcc15 | ((n) << 6)) << 2)
#define PHY_PMA_ISO_RX_DATA_LO(n)	((0xcc16 | ((n) << 6)) << 2)
#define PHY_PMA_ISO_RX_DATA_HI(n)	((0xcc17 | ((n) << 6)) << 2)

/*
 * Selects which PLL clock will be driven on the analog high speed
 * clock 0: PLL 0 div 1
 * clock 1: PLL 1 div 2
 */
#define CLK_PLL1_DIV1			0x20
#define CLK_PLL1_DIV2			0x30
#define CLK_PLL_MASK			0x33

#define CMN_READY			BIT(0)
#define PHY_MODE_SET_TIMEOUT		100000
#define MODE_DISCONNECT			0
#define MODE_UFP_USB			BIT(0)
#define MODE_DFP_USB			BIT(1)
#define POWER_ON_TRIES			5

struct phy_reg {
	u16 value;
	u32 addr;
};

static const struct phy_reg usb3_pll_cfg[] = {
	{ 0xf0,		CMN_PLL0_VCOCAL_INIT },
	{ 0x18,		CMN_PLL0_VCOCAL_ITER },
	{ 0xd0,		CMN_PLL0_INTDIV },
	{ 0x4a4a,	CMN_PLL0_FRACDIV },
	{ 0x34,		CMN_PLL0_HIGH_THR },
	{ 0x1ee,	CMN_PLL0_SS_CTRL1 },
	{ 0x7f03,	CMN_PLL0_SS_CTRL2 },
	{ 0x20,		CMN_PLL0_DSM_DIAG },
	{ 0,		CMN_DIAG_PLL0_OVRD },
	{ 0,		CMN_DIAG_PLL0_FBH_OVRD },
	{ 0,		CMN_DIAG_PLL0_FBL_OVRD },
	{ 0x7,		CMN_DIAG_PLL0_V2I_TUNE },
	{ 0x45,		CMN_DIAG_PLL0_CP_TUNE },
	{ 0x8,		CMN_DIAG_PLL0_LF_PROG },
};

static void tcphy_cfg_24m(struct rockchip_typec_phy *tcphy)
{
	u32 i, rdata;

	/*
	 * cmn_ref_clk_sel = 3, select the 24Mhz for clk parent
	 * cmn_psm_clk_dig_div = 2, set the clk division to 2
	 */
	writel(0x830, tcphy->base + PMA_CMN_CTRL1);
	for (i = 0; i < 4; i++) {
		/*
		 * The following PHY configuration assumes a 24 MHz reference
		 * clock.
		 */
		writel(0x90, tcphy->base + XCVR_DIAG_LANE_FCM_EN_MGN(i));
		writel(0x960, tcphy->base + TX_RCVDET_EN_TMR(i));
		writel(0x30, tcphy->base + TX_RCVDET_ST_TMR(i));
	}

	rdata = readl(tcphy->base + CMN_DIAG_HSCLK_SEL);
	rdata &= ~CLK_PLL_MASK;
	rdata |= CLK_PLL1_DIV2;
	writel(rdata, tcphy->base + CMN_DIAG_HSCLK_SEL);
}

static void tcphy_cfg_usb3_pll(struct rockchip_typec_phy *tcphy)
{
	u32 i;

	/* load the configuration of PLL0 */
	for (i = 0; i < ARRAY_SIZE(usb3_pll_cfg); i++)
		writel(usb3_pll_cfg[i].value,
		       tcphy->base + usb3_pll_cfg[i].addr);
}

static void tcphy_tx_usb3_cfg_lane(struct rockchip_typec_phy *tcphy, u32 lane)
{
	writel(0x7799, tcphy->base + TX_PSC_A0(lane));
	writel(0x7798, tcphy->base + TX_PSC_A1(lane));
	writel(0x5098, tcphy->base + TX_PSC_A2(lane));
	writel(0x5098, tcphy->base + TX_PSC_A3(lane));
	writel(0, tcphy->base + TX_TXCC_MGNFS_MULT_000(lane));
	writel(0xbf, tcphy->base + XCVR_DIAG_BIDI_CTRL(lane));
}

static void tcphy_rx_usb3_cfg_lane(struct rockchip_typec_phy *tcphy, u32 lane)
{
	writel(0xa6fd, tcphy->base + RX_PSC_A0(lane));
	writel(0xa6fd, tcphy->base + RX_PSC_A1(lane));
	writel(0xa410, tcphy->base + RX_PSC_A2(lane));
	writel(0x2410, tcphy->base + RX_PSC_A3(lane));
	writel(0x23ff, tcphy->base + RX_PSC_CAL(lane));
	writel(0x13, tcphy->base + RX_SIGDET_HL_FILT_TMR(lane));
	writel(0x03e7, tcphy->base + RX_REE_CTRL_DATA_MASK(lane));
	writel(0x1004, tcphy->base + RX_DIAG_SIGDET_TUNE(lane));
	writel(0x2010, tcphy->base + RX_PSC_RDY(lane));
	writel(0xfb, tcphy->base + XCVR_DIAG_BIDI_CTRL(lane));
}

static inline int property_enable(struct rockchip_typec_phy *tcphy,
				  const struct usb3phy_reg *reg, bool en)
{
	u32 mask = 1 << reg->write_enable;
	u32 val = en << reg->enable_bit;

	return writel((val | mask), (tcphy->grf_regs + reg->offset));
}

static int tcphy_cfg_usb3_to_usb2_only(struct rockchip_typec_phy *tcphy,
				       bool value)
{
	struct rockchip_usb3phy_port_cfg *cfg = &tcphy->port_cfgs;

	property_enable(tcphy, &cfg->usb3tousb2_en, value);
	property_enable(tcphy, &cfg->usb3host_disable, value);
	property_enable(tcphy, &cfg->usb3host_port, !value);

	return 0;
}

static int tcphy_phy_init(struct rockchip_typec_phy *tcphy)
{
	struct rockchip_usb3phy_port_cfg *cfg = &tcphy->port_cfgs;
	int ret;
	u32 val;

	reset_deassert(&tcphy->tcphy_rst);

	property_enable(tcphy, &cfg->typec_conn_dir, tcphy->flip);

	tcphy_cfg_24m(tcphy);

	tcphy_cfg_usb3_pll(tcphy);
	if (tcphy->flip) {
		tcphy_tx_usb3_cfg_lane(tcphy, 3);
		tcphy_rx_usb3_cfg_lane(tcphy, 2);
	} else {
		tcphy_tx_usb3_cfg_lane(tcphy, 0);
		tcphy_rx_usb3_cfg_lane(tcphy, 1);
	}

	reset_deassert(&tcphy->uphy_rst);

	ret = readx_poll_timeout(readl, tcphy->base + PMA_CMN_CTRL1,
				 val, val & CMN_READY, PHY_MODE_SET_TIMEOUT);
	if (ret < 0) {
		dev_err(tcphy->dev, "wait pma ready timeout\n");
		ret = -ETIMEDOUT;
		goto err_wait_pma;
	}

	reset_deassert(&tcphy->pipe_rst);

	return 0;

err_wait_pma:
	reset_assert(&tcphy->uphy_rst);
	reset_assert(&tcphy->tcphy_rst);
	return ret;
}

static void tcphy_phy_deinit(struct rockchip_typec_phy *tcphy)
{
	reset_assert(&tcphy->tcphy_rst);
	reset_assert(&tcphy->uphy_rst);
	reset_assert(&tcphy->pipe_rst);
}

static int tcphy_get_mode(struct rockchip_typec_phy *tcphy)
{
	u8 mode = MODE_DFP_USB | MODE_UFP_USB;

	tcphy->flip = 0;

	return mode;
}

static int _rockchip_usb3_phy_power_on(struct rockchip_typec_phy *tcphy)
{
	struct rockchip_usb3phy_port_cfg *cfg = &tcphy->port_cfgs;
	const struct usb3phy_reg *reg = &cfg->pipe_status;
	int timeout, new_mode, ret = 0;
	u32 val;

	mutex_lock(&tcphy->lock);

	new_mode = tcphy_get_mode(tcphy);

	if (tcphy->mode == new_mode)
		goto unlock_ret;

	if (tcphy->mode == MODE_DISCONNECT) {
		ret = tcphy_phy_init(tcphy);
		if (ret)
			goto unlock_ret;
	}

	/* wait TCPHY for pipe ready */
	for (timeout = 0; timeout < 100; timeout++) {
		val = readl(tcphy->grf_regs + reg->offset);
		if (!(val & BIT(reg->enable_bit))) {
			tcphy->mode |= new_mode & (MODE_DFP_USB | MODE_UFP_USB);

			/* enable usb3 host */
			tcphy_cfg_usb3_to_usb2_only(tcphy, false);
			goto unlock_ret;
		}
		udelay(20);
	}

	if (tcphy->mode == MODE_DISCONNECT)
		tcphy_phy_deinit(tcphy);

	ret = -ETIMEDOUT;

unlock_ret:
	mutex_unlock(&tcphy->lock);
	return ret;
}

static int rockchip_usb3_phy_power_on(struct phy *phy)
{
	struct udevice *parent = dev_get_parent(phy->dev);
	struct rockchip_typec_phy *tcphy = dev_get_priv(parent);
	int ret;
	int tries;

	for (tries = 0; tries < POWER_ON_TRIES; tries++) {
		ret = _rockchip_usb3_phy_power_on(tcphy);
		if (!ret)
			break;
	}

	if (tries && !ret)
		dev_err(tcphy->dev, "Needed %d loops to turn on\n", tries);

	return ret;
}

static int rockchip_usb3_phy_power_off(struct phy *phy)
{
	struct udevice *parent = dev_get_parent(phy->dev);
	struct rockchip_typec_phy *tcphy = dev_get_priv(parent);

	mutex_lock(&tcphy->lock);

	if (tcphy->mode == MODE_DISCONNECT)
		goto unlock;

	tcphy->mode = MODE_DISCONNECT;
	tcphy_phy_deinit(tcphy);

unlock:
	mutex_unlock(&tcphy->lock);
	return 0;
}

static const struct phy_ops rockchip_usb3_phy_ops = {
	.power_on	= rockchip_usb3_phy_power_on,
	.power_off	= rockchip_usb3_phy_power_off,
};

int rockchip_u3phy_uboot_init(const char *name)
{
	struct udevice *udev;
	struct rockchip_typec_phy *tcphy;
	int tries;
	int ret;

	ret = uclass_get_device_by_name(UCLASS_PHY, name, &udev);
	if (ret) {
		pr_err("%s: get usb3-phy failed: %d\n", __func__, ret);
		return ret;
	}

	/* Initialize OTG PHY */
	tcphy = dev_get_priv(udev);
	for (tries = 0; tries < POWER_ON_TRIES; tries++) {
		ret = _rockchip_usb3_phy_power_on(tcphy);
		if (!ret)
			break;
	}

	if (tries && !ret)
		pr_err("%s: needed %d loops to turn on\n", __func__, tries);

	return ret;
}

static int tcphy_get_param(struct udevice *dev,
			   struct usb3phy_reg *reg,
			   const char *name)
{
	u32 buffer[3];
	int ret;

	ret = dev_read_u32_array(dev, name, buffer, 3);
	if (ret) {
		pr_err("%s: Can not parse %s\n", __func__, name);
		return ret;
	}

	reg->offset = buffer[0];
	reg->enable_bit = buffer[1];
	reg->write_enable = buffer[2];

	return 0;
}

static int tcphy_parse_dt(struct rockchip_typec_phy *tcphy,
			  struct udevice *dev)
{
	struct rockchip_usb3phy_port_cfg *cfg = &tcphy->port_cfgs;
	int ret;

	ret = tcphy_get_param(dev, &cfg->typec_conn_dir,
			      "rockchip,typec-conn-dir");
	if (ret)
		return ret;

	ret = tcphy_get_param(dev, &cfg->usb3tousb2_en,
			      "rockchip,usb3tousb2-en");
	if (ret)
		return ret;

	ret = tcphy_get_param(dev, &cfg->usb3host_disable,
			      "rockchip,usb3-host-disable");
	if (ret)
		return ret;

	ret = tcphy_get_param(dev, &cfg->usb3host_port,
			      "rockchip,usb3-host-port");
	if (ret)
		return ret;

	ret = tcphy_get_param(dev, &cfg->external_psm,
			      "rockchip,external-psm");
	if (ret)
		return ret;

	ret = tcphy_get_param(dev, &cfg->pipe_status,
			      "rockchip,pipe-status");
	if (ret)
		return ret;

	tcphy->grf_regs = syscon_get_first_range(ROCKCHIP_SYSCON_GRF);
	if (IS_ERR(tcphy->grf_regs)) {
		dev_err(dev, "could not find grf dt node\n");
		return PTR_ERR(tcphy->grf_regs);
	}

	ret = reset_get_by_name(dev, "uphy", &tcphy->uphy_rst);
	if (ret) {
		dev_err(dev, "no uphy_rst reset control found\n");
		return ret;
	}

	ret = reset_get_by_name(dev, "uphy-pipe", &tcphy->pipe_rst);
	if (ret) {
		dev_err(dev, "no pipe_rst reset control found\n");
		return ret;
	}

	ret = reset_get_by_name(dev, "uphy-pipe", &tcphy->tcphy_rst);
	if (ret) {
		dev_err(dev, "no tcphy_rst reset control found\n");
		return ret;
	}

	return 0;
}

static void typec_phy_pre_init(struct rockchip_typec_phy *tcphy)
{
	struct rockchip_usb3phy_port_cfg *cfg = &tcphy->port_cfgs;

	reset_assert(&tcphy->tcphy_rst);
	reset_assert(&tcphy->uphy_rst);
	reset_assert(&tcphy->pipe_rst);

	/* select external psm clock */
	property_enable(tcphy, &cfg->external_psm, 1);
	property_enable(tcphy, &cfg->usb3tousb2_en, 0);

	tcphy->mode = MODE_DISCONNECT;
}

static int rockchip_typec_phy_bind(struct udevice *parent)
{
	struct udevice *dev;
	ofnode node;
	const char *name;
	int ret;

	dev_for_each_subnode(node, parent) {
		if (!ofnode_valid(node)) {
			debug("%s: %s subnode not found", __func__, parent->name);
			return -ENXIO;
		}

		name = ofnode_get_name(node);
		debug("%s: subnode %s\n", __func__, name);

		if (!strcasecmp(name, "usb3-port")) {
			ret = device_bind_driver_to_node(parent, "rockchip_typec_phy_port",
							 name, node, &dev);
			if (ret) {
				pr_err("%s: '%s' cannot bind 'rockchip_typec_phy_port'\n",
				       __func__, name);
				return ret;
			}
		}
	}

	return 0;
}

static int rockchip_typec_phy_probe(struct udevice *udev)
{
	struct rockchip_typec_phy *tcphy = dev_get_priv(udev);
	int ret;

	tcphy->base = (void __iomem *)dev_read_addr(udev);
	if (IS_ERR(tcphy->base))
		return PTR_ERR(tcphy->base);

	ret = tcphy_parse_dt(tcphy, udev);
	if (ret)
		return ret;

	tcphy->dev = udev;
	mutex_init(&tcphy->lock);

	typec_phy_pre_init(tcphy);

	printf("Rockchip Type-C PHY is initialized\n");
	return 0;
}

static const struct udevice_id rockchip_typec_phy_dt_ids[] = {
	{ .compatible = "rockchip,rk3399-typec-phy" },
	{}
};

U_BOOT_DRIVER(rockchip_typec_phy_port) = {
	.name		= "rockchip_typec_phy_port",
	.id		= UCLASS_PHY,
	.ops		= &rockchip_usb3_phy_ops,
};

U_BOOT_DRIVER(rockchip_typec_phy) = {
	.name		= "rockchip_typec_phy",
	.id		= UCLASS_PHY,
	.of_match	= rockchip_typec_phy_dt_ids,
	.probe		= rockchip_typec_phy_probe,
	.bind		= rockchip_typec_phy_bind,
	.priv_auto_alloc_size = sizeof(struct rockchip_typec_phy),
};
