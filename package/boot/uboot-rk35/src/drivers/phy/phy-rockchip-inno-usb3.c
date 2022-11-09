// SPDX-License-Identifier:     GPL-2.0
/*
 * Copyright (C) 2020 Rockchip Electronics Co., Ltd
 *
 * Based on phy-rockchip-inno-usb3.c in Linux Kernel.
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
#include <asm/io.h>
#include <asm/arch-rockchip/clock.h>

#define usleep_range(a, b) udelay((b))

#define U3PHY_PORT_NUM	2
#define U3PHY_MAX_CLKS	4
#define BIT_WRITEABLE_SHIFT	16
#define SCHEDULE_DELAY	(60 * HZ)

#define U3PHY_APB_RST	BIT(0)
#define U3PHY_POR_RST	BIT(1)
#define U3PHY_MAC_RST	BIT(2)

struct rockchip_u3phy;
struct rockchip_u3phy_port;

enum rockchip_u3phy_type {
	U3PHY_TYPE_PIPE,
	U3PHY_TYPE_UTMI,
};

enum rockchip_u3phy_pipe_pwr {
	PIPE_PWR_P0	= 0,
	PIPE_PWR_P1	= 1,
	PIPE_PWR_P2	= 2,
	PIPE_PWR_P3	= 3,
	PIPE_PWR_MAX	= 4,
};

enum rockchip_u3phy_rest_req {
	U3_POR_RSTN	= 0,
	U2_POR_RSTN	= 1,
	PIPE_MAC_RSTN	= 2,
	UTMI_MAC_RSTN	= 3,
	PIPE_APB_RSTN	= 4,
	UTMI_APB_RSTN	= 5,
	U3PHY_RESET_MAX	= 6,
};

enum rockchip_u3phy_utmi_state {
	PHY_UTMI_HS_ONLINE	= 0,
	PHY_UTMI_DISCONNECT	= 1,
	PHY_UTMI_CONNECT	= 2,
	PHY_UTMI_FS_LS_ONLINE	= 4,
};

/*
 * @rvalue: reset value
 * @dvalue: desired value
 */
struct u3phy_reg {
	unsigned int	offset;
	unsigned int	bitend;
	unsigned int	bitstart;
	unsigned int	rvalue;
	unsigned int	dvalue;
};

struct rockchip_u3phy_grfcfg {
	struct u3phy_reg	um_suspend;
	struct u3phy_reg	ls_det_en;
	struct u3phy_reg	ls_det_st;
	struct u3phy_reg	um_ls;
	struct u3phy_reg	um_hstdct;
	struct u3phy_reg	u2_only_ctrl;
	struct u3phy_reg	u3_disable;
	struct u3phy_reg	pp_pwr_st;
	struct u3phy_reg	pp_pwr_en[PIPE_PWR_MAX];
};

/**
 * struct rockchip_u3phy_apbcfg: usb3-phy apb configuration.
 * @u2_pre_emp: usb2-phy pre-emphasis tuning.
 * @u2_pre_emp_sth: usb2-phy pre-emphasis strength tuning.
 * @u2_odt_tuning: usb2-phy odt 45ohm tuning.
 */
struct rockchip_u3phy_apbcfg {
	unsigned int	u2_pre_emp;
	unsigned int	u2_pre_emp_sth;
	unsigned int	u2_odt_tuning;
};

struct rockchip_u3phy_cfg {
	unsigned int reg;
	const struct rockchip_u3phy_grfcfg grfcfg;

	int (*phy_tuning)(struct rockchip_u3phy *u3phy,
			  struct rockchip_u3phy_port *u3phy_port,
			  const struct device_node *child_np);
};

struct rockchip_u3phy_port {
	void __iomem	*base;
	unsigned int	index;
	unsigned char	type;
	bool		refclk_25m_quirk;
	struct mutex	mutex; /* mutex for updating register */
};

struct rockchip_u3phy {
	struct udevice *dev;
	struct regmap *u3phy_grf;
	struct regmap *grf;
	struct udevice *vbus_supply;
	struct reset_ctl rsts[U3PHY_RESET_MAX];
	struct rockchip_u3phy_apbcfg apbcfg;
	const struct rockchip_u3phy_cfg *cfgs;
	struct rockchip_u3phy_port ports[U3PHY_PORT_NUM];
};

static inline int param_write(void __iomem *base,
			      const struct u3phy_reg *reg, bool desired)
{
	unsigned int val, mask;
	unsigned int tmp = desired ? reg->dvalue : reg->rvalue;
	int ret = 0;

	mask = GENMASK(reg->bitend, reg->bitstart);
	val = (tmp << reg->bitstart) | (mask << BIT_WRITEABLE_SHIFT);
	ret = regmap_write(base, reg->offset, val);

	return ret;
}

static inline bool param_exped(void __iomem *base,
			       const struct u3phy_reg *reg,
			       unsigned int value)
{
	int ret;
	unsigned int tmp, orig;
	unsigned int mask = GENMASK(reg->bitend, reg->bitstart);

	ret = regmap_read(base, reg->offset, &orig);
	if (ret)
		return false;

	tmp = (orig & mask) >> reg->bitstart;
	return tmp == value;
}

int rockchip_u3phy_uboot_init(void)
{
	struct udevice *udev;
	int ret;

	ret = uclass_get_device_by_name(UCLASS_PHY, "usb3-phy", &udev);
	if (ret)
		pr_err("%s: get usb3-phy node failed: %d\n", __func__, ret);

	(void)udev;

	return ret;
}

static int rockchip_u3phy_init(struct phy *phy)
{
	return 0;
}

static int rockchip_u3phy_exit(struct phy *phy)
{
	return 0;
}

static int rockchip_u3phy_power_on(struct phy *phy)
{
	struct udevice *parent = dev_get_parent(phy->dev);
	struct rockchip_u3phy *u3phy = dev_get_priv(parent);
	int ret = 0;

	/* Vbus regulator */
	if (!u3phy->vbus_supply) {
		ret = device_get_supply_regulator(parent, "vbus-supply",
						  &u3phy->vbus_supply);
		if (ret == -ENOENT) {
			pr_info("%s: Can't get VBus regulator!\n", __func__);
			return 0;
		}

		ret = regulator_set_enable(u3phy->vbus_supply, true);
		if (ret) {
			pr_err("%s: Failed to set VBus supply\n", __func__);
			return ret;
		}
	}

	return 0;
}

static int rockchip_u3phy_power_off(struct phy *phy)
{
	struct udevice *parent = dev_get_parent(phy->dev);
	struct rockchip_u3phy *u3phy = dev_get_priv(parent);
	int ret = 0;

	/* Turn off vbus regulator */
	if (u3phy->vbus_supply) {
		ret = regulator_set_enable(u3phy->vbus_supply, false);
		if (ret) {
			pr_err("%s: Failed to set VBus supply\n", __func__);
			return ret;
		}

		u3phy->vbus_supply = NULL;
	}

	return 0;
}

static int rockchip_u3phy_bind(struct udevice *parent)
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

		ret = device_bind_driver_to_node(parent, "rockchip_u3phy_port",
						 name, node, &dev);
		if (ret) {
			pr_err("%s: '%s' cannot bind 'rockchip_u3phy_port'\n",
			       __func__, name);
			return ret;
		}
	}

	return 0;
}

static const char *get_rest_name(enum rockchip_u3phy_rest_req rst)
{
	switch (rst) {
	case U2_POR_RSTN:
		return "u3phy-u2-por";
	case U3_POR_RSTN:
		return "u3phy-u3-por";
	case PIPE_MAC_RSTN:
		return "u3phy-pipe-mac";
	case UTMI_MAC_RSTN:
		return "u3phy-utmi-mac";
	case UTMI_APB_RSTN:
		return "u3phy-utmi-apb";
	case PIPE_APB_RSTN:
		return "u3phy-pipe-apb";
	default:
		return "invalid";
	}
}

static void rockchip_u3phy_rest_deassert(struct rockchip_u3phy *u3phy,
					 unsigned int flag)
{
	int rst;

	if (flag & U3PHY_APB_RST) {
		dev_dbg(u3phy->dev, "deassert APB bus interface reset\n");
		for (rst = PIPE_APB_RSTN; rst <= UTMI_APB_RSTN; rst++) {
			if (u3phy->rsts[rst].dev)
				reset_deassert(&u3phy->rsts[rst]);
		}
	}

	if (flag & U3PHY_POR_RST) {
		usleep_range(12, 15);
		dev_dbg(u3phy->dev, "deassert u2 and u3 phy power on reset\n");
		for (rst = U3_POR_RSTN; rst <= U2_POR_RSTN; rst++) {
			if (u3phy->rsts[rst].dev)
				reset_deassert(&u3phy->rsts[rst]);
		}
	}

	if (flag & U3PHY_MAC_RST) {
		usleep_range(1200, 1500);
		dev_dbg(u3phy->dev, "deassert pipe and utmi MAC reset\n");
		for (rst = PIPE_MAC_RSTN; rst <= UTMI_MAC_RSTN; rst++)
			if (u3phy->rsts[rst].dev)
				reset_deassert(&u3phy->rsts[rst]);
	}
}

static void rockchip_u3phy_rest_assert(struct rockchip_u3phy *u3phy)
{
	int rst;

	dev_dbg(u3phy->dev, "assert u3phy reset\n");
	for (rst = 0; rst < U3PHY_RESET_MAX; rst++)
		if (u3phy->rsts[rst].dev)
			reset_assert(&u3phy->rsts[rst]);
}

static int rockchip_u3phy_parse_dt(struct rockchip_u3phy *u3phy,
				   struct udevice *udev)

{
	int i, ret = 0;

	for (i = 0; i < U3PHY_RESET_MAX; i++) {
		ret = reset_get_by_name(udev, get_rest_name(i),
					&u3phy->rsts[i]);
		if (ret) {
			dev_info(udev, "no %s reset control specified\n",
				 get_rest_name(i));
		}
	}

	return ret;
}

static int rockchip_u3phy_port_init(struct rockchip_u3phy *u3phy,
				    struct rockchip_u3phy_port *u3phy_port,
				    const struct device_node *child_np)
{
	int ret;

	dev_dbg(u3phy->dev, "u3phy port initialize\n");

	mutex_init(&u3phy_port->mutex);

	u3phy_port->base = (void __iomem *)ofnode_get_addr(np_to_ofnode(child_np));
	if (IS_ERR(u3phy_port->base)) {
		dev_err(u3phy->dev, "failed to remap phy regs\n");
		return PTR_ERR(u3phy_port->base);
	}

	if (!of_node_cmp(child_np->name, "pipe")) {
		u3phy_port->type = U3PHY_TYPE_PIPE;
		u3phy_port->refclk_25m_quirk =
			ofnode_read_bool(np_to_ofnode(child_np),
					 "rockchip,refclk-25m-quirk");
	} else {
		u3phy_port->type = U3PHY_TYPE_UTMI;
	}

	if (u3phy->cfgs->phy_tuning) {
		dev_dbg(u3phy->dev, "do u3phy tuning\n");
		ret = u3phy->cfgs->phy_tuning(u3phy, u3phy_port, child_np);
		if (ret)
			return ret;
	}

	return 0;
}

static int rockchip_u3phy_probe(struct udevice *udev)
{
	const struct udevice_id *of_match = udev->driver->of_match;
	struct rockchip_u3phy *u3phy = dev_get_priv(udev);
	const struct rockchip_u3phy_cfg *phy_cfgs;
	ofnode child_np;
	u32 reg[2], index;
	int ret = 0;

	while (of_match->compatible) {
		if (device_is_compatible(udev, of_match->compatible))
			break;
		of_match++;
	}

	if (!of_match || !of_match->data) {
		dev_err(udev, "phy-cfgs are not assigned!\n");
		return -EINVAL;
	}

	if (ofnode_read_u32_array(dev_ofnode(udev), "reg", reg, 2)) {
		dev_err(udev, "could not read reg\n");
		return -EINVAL;
	}

	u3phy->dev = udev;
	phy_cfgs = (const struct rockchip_u3phy_cfg *)of_match->data;

	/* find out a proper config which can be matched with dt. */
	index = 0;
	while (phy_cfgs[index].reg) {
		if (phy_cfgs[index].reg == reg[1]) {
			u3phy->cfgs = &phy_cfgs[index];
			break;
		}
		++index;
	}

	if (!u3phy->cfgs) {
		dev_err(udev, "no phy-cfgs can be matched\n");
		return -EINVAL;
	}

	ret = rockchip_u3phy_parse_dt(u3phy, udev);
	if (ret) {
		dev_err(udev, "parse dt failed, ret(%d)\n", ret);
		return ret;
	}

	rockchip_u3phy_rest_assert(u3phy);
	rockchip_u3phy_rest_deassert(u3phy, U3PHY_APB_RST | U3PHY_POR_RST);

	index = 0;
	ofnode_for_each_subnode(child_np, udev->node) {
		struct rockchip_u3phy_port *u3phy_port = &u3phy->ports[index];

		u3phy_port->index = index;
		ret = rockchip_u3phy_port_init(u3phy, u3phy_port,
					       ofnode_to_np(child_np));
		if (ret) {
			dev_err(udev, "u3phy port init failed,ret(%d)\n", ret);
			goto put_child;
		}

		/* to prevent out of boundary */
		if (++index >= U3PHY_PORT_NUM)
			break;
	}

	rockchip_u3phy_rest_deassert(u3phy, U3PHY_MAC_RST);

	dev_info(udev, "Rockchip u3phy initialized successfully\n");
	return 0;

put_child:
	of_node_put(ofnode_to_np(child_np));
	return ret;
}

static int rk3328_u3phy_tuning(struct rockchip_u3phy *u3phy,
			       struct rockchip_u3phy_port *u3phy_port,
			       const struct device_node *child_np)
{
	if (u3phy_port->type == U3PHY_TYPE_UTMI) {
		/*
		 * For rk3328 SoC, pre-emphasis and pre-emphasis strength must
		 * be written as one fixed value as below.
		 *
		 * Dissimilarly, the odt 45ohm value should be flexibly tuninged
		 * for the different boards to adjust HS eye height, so its
		 * value can be assigned in DT in code design.
		 */

		/* {bits[2:0]=111}: always enable pre-emphasis */
		u3phy->apbcfg.u2_pre_emp = 0x0f;

		/* {bits[5:3]=000}: pre-emphasis strength as the weakest */
		u3phy->apbcfg.u2_pre_emp_sth = 0x41;

		/* {bits[4:0]=10101}: odt 45ohm tuning */
		u3phy->apbcfg.u2_odt_tuning = 0xb5;

		/* optional override of the odt 45ohm tuning */
		ofnode_read_u32(np_to_ofnode(child_np),
				"rockchip,odt-val-tuning",
				&u3phy->apbcfg.u2_odt_tuning);

		writel(u3phy->apbcfg.u2_pre_emp, u3phy_port->base + 0x030);
		writel(u3phy->apbcfg.u2_pre_emp_sth, u3phy_port->base + 0x040);
		writel(u3phy->apbcfg.u2_odt_tuning, u3phy_port->base + 0x11c);
	} else if (u3phy_port->type == U3PHY_TYPE_PIPE) {
		if (u3phy_port->refclk_25m_quirk) {
			dev_dbg(u3phy->dev, "switch to 25m refclk\n");
			/* ref clk switch to 25M */
			writel(0x64, u3phy_port->base + 0x11c);
			writel(0x64, u3phy_port->base + 0x028);
			writel(0x01, u3phy_port->base + 0x020);
			writel(0x21, u3phy_port->base + 0x030);
			writel(0x06, u3phy_port->base + 0x108);
			writel(0x00, u3phy_port->base + 0x118);
		} else {
			/* configure for 24M ref clk */
			writel(0x80, u3phy_port->base + 0x10c);
			writel(0x01, u3phy_port->base + 0x118);
			writel(0x38, u3phy_port->base + 0x11c);
			writel(0x83, u3phy_port->base + 0x020);
			writel(0x02, u3phy_port->base + 0x108);
		}

		/* Enable SSC */
		udelay(3);
		writel(0x08, u3phy_port->base + 0x000);
		writel(0x0c, u3phy_port->base + 0x120);

		/* Tuning Rx for compliance RJTL test */
		writel(0x70, u3phy_port->base + 0x150);
		writel(0x12, u3phy_port->base + 0x0c8);
		writel(0x05, u3phy_port->base + 0x148);
		writel(0x08, u3phy_port->base + 0x068);
		writel(0xf0, u3phy_port->base + 0x1c4);
		writel(0xff, u3phy_port->base + 0x070);
		writel(0x0f, u3phy_port->base + 0x06c);
		writel(0xe0, u3phy_port->base + 0x060);

		/*
		 * Tuning Tx to increase the bias current
		 * used in TX driver and RX EQ, it can
		 * also increase the voltage of LFPS.
		 */
		writel(0x08, u3phy_port->base + 0x180);
	} else {
		dev_err(u3phy->dev, "invalid u3phy port type\n");
		return -EINVAL;
	}

	return 0;
}

static struct phy_ops rockchip_u3phy_ops = {
	.init = rockchip_u3phy_init,
	.exit = rockchip_u3phy_exit,
	.power_on= rockchip_u3phy_power_on,
	.power_off= rockchip_u3phy_power_off,
};

static const struct rockchip_u3phy_cfg rk3328_u3phy_cfgs[] = {
	{
		.reg		= 0xff470000,
		.grfcfg		= {
			.um_suspend	= { 0x0004, 15, 0, 0x1452, 0x15d1 },
			.u2_only_ctrl	= { 0x0020, 15, 15, 0, 1 },
			.um_ls		= { 0x0030, 5, 4, 0, 1 },
			.um_hstdct	= { 0x0030, 7, 7, 0, 1 },
			.ls_det_en	= { 0x0040, 0, 0, 0, 1 },
			.ls_det_st	= { 0x0044, 0, 0, 0, 1 },
			.pp_pwr_st	= { 0x0034, 14, 13, 0, 0},
			.pp_pwr_en	= { {0x0020, 14, 0, 0x0014, 0x0005},
					    {0x0020, 14, 0, 0x0014, 0x000d},
					    {0x0020, 14, 0, 0x0014, 0x0015},
					    {0x0020, 14, 0, 0x0014, 0x001d} },
			.u3_disable	= { 0x04c4, 15, 0, 0x1100, 0x101},
		},
		.phy_tuning	= rk3328_u3phy_tuning,
	},
	{ /* sentinel */ }
};

static const struct udevice_id rockchip_u3phy_dt_match[] = {
	{ .compatible = "rockchip,rk3328-u3phy", .data = (ulong)&rk3328_u3phy_cfgs },
	{}
};

U_BOOT_DRIVER(rockchip_u3phy_port) = {
	.name		= "rockchip_u3phy_port",
	.id		= UCLASS_PHY,
	.ops		= &rockchip_u3phy_ops,
};

U_BOOT_DRIVER(rockchip_u3phy) = {
	.name		= "rockchip_u3phy",
	.id		= UCLASS_PHY,
	.of_match	= rockchip_u3phy_dt_match,
	.probe		= rockchip_u3phy_probe,
	.bind		= rockchip_u3phy_bind,
	.priv_auto_alloc_size = sizeof(struct rockchip_u3phy),
};
