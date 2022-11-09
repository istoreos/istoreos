// SPDX-License-Identifier: GPL-2.0+
/*
 * Rockchip USB2.0 PHY with Naneng IP block driver
 *
 * Copyright (C) 2020 Fuzhou Rockchip Electronics Co., Ltd
 */

#include <common.h>
#include <dm.h>
#include <dm/lists.h>
#include <generic-phy.h>
#include <syscon.h>
#include <asm/io.h>
#include <asm/arch-rockchip/clock.h>
#include <reset-uclass.h>
#include <power/regulator.h>

#define U2PHY_BIT_WRITEABLE_SHIFT	16

struct rockchip_usb2phy;

enum power_supply_type {
	POWER_SUPPLY_TYPE_UNKNOWN = 0,
	POWER_SUPPLY_TYPE_USB,		/* Standard Downstream Port */
	POWER_SUPPLY_TYPE_USB_DCP,	/* Dedicated Charging Port */
	POWER_SUPPLY_TYPE_USB_CDP,	/* Charging Downstream Port */
	POWER_SUPPLY_TYPE_USB_FLOATING,	/* DCP without shorting D+/D- */
};

enum rockchip_usb2phy_port_id {
	USB2PHY_PORT_OTG,
	USB2PHY_PORT_HOST,
	USB2PHY_NUM_PORTS,
};

struct usb2phy_reg {
	u32	offset;
	u32	bitend;
	u32	bitstart;
	u32	disable;
	u32	enable;
};

/**
 * struct rockchip_chg_det_reg: usb charger detect registers
 * @chg_valid: charge valid signal.
 * @phy_connect: PHY start handshake signal.
 * @chg_en: charge detector enable signal.
 * @chg_rst: charge detector reset signal, active high.
 */
struct rockchip_chg_det_reg {
	struct usb2phy_reg	chg_valid;
	struct usb2phy_reg	phy_connect;
	struct usb2phy_reg	chg_en;
	struct usb2phy_reg	chg_rst;
};

/**
 * struct rockchip_usb2phy_port_cfg: usb phy port configuration.
 * @bypass_otgsuspendm: otg-suspendm bypass control register.
 *			 0: iddig; 1: grf.
 * @bvalidfall_det_en: vbus valid fall detection enable register.
 * @bvalidfall_det_st: vbus valid fall detection status register.
 * @bvalidfall_det_clr: vbus valid fall detection clear register.
 * @bvalidrise_det_en: vbus valid rise detection enable register.
 * @bvalidrise_det_st: vbus valid rise detection status register.
 * @bvalidrise_det_clr: vbus valid rise detection clear register.
 * @disconfall_det_en: host connect detection enable register.
 * @disconfall_det_st: host connect detection status register.
 * @disconfall_det_clr: host connect detection clear register.
 * @disconrise_det_en: host disconnect detection enable register.
 * @disconrise_det_st: host disconnect detection status register.
 * @disconrise_det_clr: host disconnect detection clear register.
 * @idfall_det_en: id fall detection enable register.
 * @idfall_det_st: id fall detection state register.
 * @idfall_det_clr: id fall detection clear register.
 * @idpullup: id pin pullup or pulldown control register.
 * @idrise_det_en: id rise detection enable register.
 * @idrise_det_st: id rise detection state register.
 * @idrise_det_clr: id rise detection clear register.
 * @ls_det_en: linestate detection enable register.
 * @ls_det_st: linestate detection state register.
 * @ls_det_clr: linestate detection clear register.
 * @phy_sus: phy suspend register.
 * @utmi_bvalid: utmi vbus bvalid status register.
 * @utmi_iddig: otg port id pin status register.
 * @utmi_hostdet: utmi host disconnect status register.
 */
struct rockchip_usb2phy_port_cfg {
	struct usb2phy_reg	bypass_otgsuspendm;
	struct usb2phy_reg	bvalidfall_det_en;
	struct usb2phy_reg	bvalidfall_det_st;
	struct usb2phy_reg	bvalidfall_det_clr;
	struct usb2phy_reg	bvalidrise_det_en;
	struct usb2phy_reg	bvalidrise_det_st;
	struct usb2phy_reg	bvalidrise_det_clr;
	struct usb2phy_reg	disconfall_det_en;
	struct usb2phy_reg	disconfall_det_st;
	struct usb2phy_reg	disconfall_det_clr;
	struct usb2phy_reg	disconrise_det_en;
	struct usb2phy_reg	disconrise_det_st;
	struct usb2phy_reg	disconrise_det_clr;
	struct usb2phy_reg	idfall_det_en;
	struct usb2phy_reg	idfall_det_st;
	struct usb2phy_reg	idfall_det_clr;
	struct usb2phy_reg	idpullup;
	struct usb2phy_reg	idrise_det_en;
	struct usb2phy_reg	idrise_det_st;
	struct usb2phy_reg	idrise_det_clr;
	struct usb2phy_reg	ls_det_en;
	struct usb2phy_reg	ls_det_st;
	struct usb2phy_reg	ls_det_clr;
	struct usb2phy_reg	phy_sus;
	struct usb2phy_reg	utmi_bvalid;
	struct usb2phy_reg	utmi_iddig;
	struct usb2phy_reg	utmi_hostdet;
};

/**
 * struct rockchip_usb2phy_cfg: usb phy configuration.
 * @reg: the address offset of grf for usb-phy config.
 * @num_ports: specify how many ports that the phy has.
 * @phy_tuning: phy default parameters tuning.
 * @clkout_ctl: keep on/turn off output clk of phy.
 * @port_cfgs: ports register configuration, assigned by driver data.
 * @chg_det: charger detection registers.
 * @last: indicate the last one.
 */
struct rockchip_usb2phy_cfg {
	unsigned int	reg;
	unsigned int	num_ports;
	int		(*phy_tuning)(struct rockchip_usb2phy *rphy);
	struct		usb2phy_reg clkout_ctl;
	const struct	rockchip_usb2phy_port_cfg port_cfgs[USB2PHY_NUM_PORTS];
	const struct	rockchip_chg_det_reg chg_det;
	bool		last;
};

/**
 * struct rockchip_usb2phy: usb2.0 phy driver data.
 * @grf: General Register Files register base.
 * @reset: power reset signal for phy.
 * @vbus_supply: vbus supply for usb host.
 * @phy_cfg: phy register configuration, assigned by driver data.
 */
struct rockchip_usb2phy {
	void __iomem		*grf;
	struct reset_ctl	*reset;
	struct udevice		*vbus_supply[USB2PHY_NUM_PORTS];
	const struct rockchip_usb2phy_cfg	*phy_cfg;
};

static inline int property_enable(void __iomem *base,
				  const struct usb2phy_reg *reg, bool en)
{
	u32 val, mask, tmp;

	tmp = en ? reg->enable : reg->disable;
	mask = GENMASK(reg->bitend, reg->bitstart);
	val = (tmp << reg->bitstart) | (mask << U2PHY_BIT_WRITEABLE_SHIFT);

	writel(val, base + reg->offset);

	return 0;
}

static inline bool property_enabled(void __iomem *base,
				    const struct usb2phy_reg *reg)
{
	u32 tmp, orig;
	u32 mask = GENMASK(reg->bitend, reg->bitstart);

	orig = readl(base + reg->offset);

	tmp = (orig & mask) >> reg->bitstart;

	return tmp == reg->enable;
}

static const char *chg_to_string(enum power_supply_type chg_type)
{
	switch (chg_type) {
	case POWER_SUPPLY_TYPE_USB:
		return "USB_SDP_CHARGER";
	case POWER_SUPPLY_TYPE_USB_DCP:
		return "USB_DCP_CHARGER";
	case POWER_SUPPLY_TYPE_USB_CDP:
		return "USB_CDP_CHARGER";
	case POWER_SUPPLY_TYPE_USB_FLOATING:
		return "USB_FLOATING_CHARGER";
	default:
		return "INVALID_CHARGER";
	}
}

int rockchip_chg_get_type(void)
{
	const struct rockchip_usb2phy_port_cfg *port_cfg;
	enum power_supply_type chg_type;
	struct rockchip_usb2phy *rphy;
	struct udevice *udev;
	bool chg_valid, phy_connect;
	int cnt;
	int ret;

	ret = uclass_get_device_by_name(UCLASS_PHY, "usb2-phy", &udev);
	if (ret == -ENODEV) {
		ret = uclass_get_device_by_name(UCLASS_PHY, "usb2phy", &udev);
		if (ret) {
			pr_err("%s: get usb2 phy node failed: %d\n", __func__, ret);
			return ret;
		}
	}

	rphy = dev_get_priv(udev);
	port_cfg = &rphy->phy_cfg->port_cfgs[USB2PHY_PORT_OTG];

	/* Check USB-Vbus status first */
	if (!property_enabled(rphy->grf, &port_cfg->utmi_bvalid)) {
		pr_info("%s: no charger found\n", __func__);
		return POWER_SUPPLY_TYPE_UNKNOWN;
	}

	reset_assert(rphy->reset);

	/* CHG_RST is set to 1'b0 to start charge detection */
	property_enable(rphy->grf, &rphy->phy_cfg->chg_det.chg_en, true);
	property_enable(rphy->grf, &rphy->phy_cfg->chg_det.chg_rst, false);

	for (cnt = 0; cnt < 12; cnt++) {
		mdelay(100);

		chg_valid = property_enabled(rphy->grf,
					     &rphy->phy_cfg->chg_det.chg_valid);
		phy_connect =
			property_enabled(rphy->grf,
					 &rphy->phy_cfg->chg_det.phy_connect);
		chg_type = (chg_valid << 1) | phy_connect;

		if (chg_type)
			goto compeleted;
	}

compeleted:
	debug("charger = %s\n", chg_to_string(chg_type));

	mdelay(1);
	reset_deassert(rphy->reset);
	/* disable the chg detection module */
	property_enable(rphy->grf, &rphy->phy_cfg->chg_det.chg_rst, true);
	property_enable(rphy->grf, &rphy->phy_cfg->chg_det.chg_en, false);

	return chg_type;
}

int rockchip_u2phy_vbus_detect(void)
{
	int chg_type;

	chg_type = rockchip_chg_get_type();

	return (chg_type == POWER_SUPPLY_TYPE_USB ||
		chg_type == POWER_SUPPLY_TYPE_USB_CDP) ? 1 : 0;
}

static struct udevice *rockchip_usb2phy_check_vbus(struct phy *phy)
{
	struct udevice *parent = phy->dev->parent;
	struct rockchip_usb2phy *rphy = dev_get_priv(parent);
	const struct rockchip_usb2phy_port_cfg *port_cfg;
	void __iomem *base = rphy->grf;
	struct udevice *vbus = NULL;
	bool iddig = true;

	if (phy->id == USB2PHY_PORT_HOST) {
		vbus = rphy->vbus_supply[USB2PHY_PORT_HOST];
	} else if (phy->id == USB2PHY_PORT_OTG) {
		port_cfg = &rphy->phy_cfg->port_cfgs[USB2PHY_PORT_OTG];
		if (port_cfg->utmi_iddig.offset) {
			iddig = property_enabled(base, &port_cfg->utmi_iddig);
			if (!iddig)
				vbus = rphy->vbus_supply[USB2PHY_PORT_OTG];
		}
	}

	return vbus;
}

static int rockchip_usb2phy_init(struct phy *phy)
{
	struct udevice *parent = phy->dev->parent;
	struct rockchip_usb2phy *rphy = dev_get_priv(parent);
	const struct rockchip_usb2phy_port_cfg *port_cfg;

	if (phy->id == USB2PHY_PORT_OTG) {
		port_cfg = &rphy->phy_cfg->port_cfgs[USB2PHY_PORT_OTG];
	} else if (phy->id == USB2PHY_PORT_HOST) {
		port_cfg = &rphy->phy_cfg->port_cfgs[USB2PHY_PORT_HOST];
	} else {
		dev_err(phy->dev, "phy id %lu not support", phy->id);
		return -EINVAL;
	}

	property_enable(rphy->grf, &port_cfg->phy_sus, false);

	/* waiting for the utmi_clk to become stable */
	udelay(2000);

	return 0;
}

static int rockchip_usb2phy_exit(struct phy *phy)
{
	struct udevice *parent = phy->dev->parent;
	struct rockchip_usb2phy *rphy = dev_get_priv(parent);
	const struct rockchip_usb2phy_port_cfg *port_cfg;

	if (phy->id == USB2PHY_PORT_OTG) {
		port_cfg = &rphy->phy_cfg->port_cfgs[USB2PHY_PORT_OTG];
	} else if (phy->id == USB2PHY_PORT_HOST) {
		port_cfg = &rphy->phy_cfg->port_cfgs[USB2PHY_PORT_HOST];
	} else {
		dev_err(phy->dev, "phy id %lu not support", phy->id);
		return -EINVAL;
	}

	property_enable(rphy->grf, &port_cfg->phy_sus, true);

	return 0;
}

static int rockchip_usb2phy_power_on(struct phy *phy)
{
	struct udevice *vbus = NULL;
	int ret;

	vbus = rockchip_usb2phy_check_vbus(phy);
	if (vbus) {
		ret = regulator_set_enable(vbus, true);
		if (ret) {
			pr_err("%s: Failed to en VBus supply\n", __func__);
			return ret;
		}
	}

	return 0;
}

static int rockchip_usb2phy_power_off(struct phy *phy)
{
	struct udevice *vbus = NULL;
	int ret;

	vbus = rockchip_usb2phy_check_vbus(phy);
	if (vbus) {
		ret = regulator_set_enable(vbus, false);
		if (ret) {
			pr_err("%s: Failed to dis VBus supply\n", __func__);
			return ret;
		}
	}

	return 0;
}

static int rockchip_usb2phy_of_xlate(struct phy *phy,
				     struct ofnode_phandle_args *args)
{
	const char *dev_name = phy->dev->name;
	struct udevice *parent = phy->dev->parent;
	struct rockchip_usb2phy *rphy = dev_get_priv(parent);

	if (!strcasecmp(dev_name, "host-port")) {
		phy->id = USB2PHY_PORT_HOST;
		device_get_supply_regulator(phy->dev, "phy-supply",
					    &rphy->vbus_supply[USB2PHY_PORT_HOST]);
	} else if (!strcasecmp(dev_name, "otg-port")) {
		phy->id = USB2PHY_PORT_OTG;
		device_get_supply_regulator(phy->dev, "phy-supply",
					    &rphy->vbus_supply[USB2PHY_PORT_OTG]);
	} else {
		pr_err("%s: invalid dev name\n", __func__);
		return -EINVAL;
	}

	return 0;
}

static int rockchip_usb2phy_bind(struct udevice *dev)
{
	struct udevice *child;
	ofnode subnode;
	const char *node_name;
	int ret;

	dev_for_each_subnode(subnode, dev) {
		if (!ofnode_valid(subnode)) {
			debug("%s: %s subnode not found", __func__, dev->name);
			return -ENXIO;
		}

		node_name = ofnode_get_name(subnode);
		debug("%s: subnode %s\n", __func__, node_name);

		ret = device_bind_driver_to_node(dev, "rockchip_usb2phy_port",
						 node_name, subnode, &child);
		if (ret) {
			pr_err("%s: '%s' cannot bind 'rockchip_usb2phy_port'\n",
			       __func__, node_name);
			return ret;
		}
	}

	return 0;
}

static int rockchip_usb2phy_probe(struct udevice *dev)
{
	const struct rockchip_usb2phy_cfg *phy_cfgs;
	struct rockchip_usb2phy *rphy = dev_get_priv(dev);
	u32 reg, index;

	rphy->grf = syscon_get_first_range(ROCKCHIP_SYSCON_GRF);

	/* get phy power reset control */
	if (reset_get_by_name(dev, "u2phy", rphy->reset)) {
		pr_err("can't get phy power reset for %s", dev->name);
		return -EINVAL;
	}

	if (rphy->grf <= 0) {
		dev_err(dev, "get syscon grf failed\n");
		return -EINVAL;
	}

	if (ofnode_read_u32(dev_ofnode(dev), "reg", &reg)) {
		dev_err(dev, "could not read reg\n");
		return -EINVAL;
	}

	phy_cfgs =
		(const struct rockchip_usb2phy_cfg *)dev_get_driver_data(dev);
	if (!phy_cfgs) {
		dev_err(dev, "unable to get phy_cfgs\n");
		return -EINVAL;
	}

	/* find out a proper config which can be matched with dt. */
	index = 0;
	do {
		if (phy_cfgs[index].reg == reg) {
			rphy->phy_cfg = &phy_cfgs[index];
			break;
		}
	} while (!phy_cfgs[index++].last);

	if (!rphy->phy_cfg) {
		dev_err(dev, "no phy-config can be matched\n");
		return -EINVAL;
	}

	if (rphy->phy_cfg->phy_tuning)
		rphy->phy_cfg->phy_tuning(rphy);

	return 0;
}

static int rv1126_usb2phy_tuning(struct rockchip_usb2phy *rphy)
{
	return 0;
}

static struct phy_ops rockchip_usb2phy_ops = {
	.init = rockchip_usb2phy_init,
	.exit = rockchip_usb2phy_exit,
	.power_on = rockchip_usb2phy_power_on,
	.power_off = rockchip_usb2phy_power_off,
	.of_xlate = rockchip_usb2phy_of_xlate,
};

static const struct rockchip_usb2phy_cfg rv1126_phy_cfgs[] = {
	{
		.reg		= 0xff4c0000,
		.num_ports	= 1,
		.phy_tuning	= rv1126_usb2phy_tuning,
		.clkout_ctl	= { 0x10230, 14, 14, 0, 1 },
		.port_cfgs	= {
			[USB2PHY_PORT_OTG] = {
				.bypass_otgsuspendm = { 0x10234, 12, 12, 0, 1 },
				.bvalidfall_det_en = { 0x10300, 3, 3, 0, 1 },
				.bvalidfall_det_st = { 0x10304, 3, 3, 0, 1 },
				.bvalidfall_det_clr = { 0x10308, 3, 3, 0, 1 },
				.bvalidrise_det_en = { 0x10300, 2, 2, 0, 1 },
				.bvalidrise_det_st = { 0x10304, 2, 2, 0, 1 },
				.bvalidrise_det_clr = { 0x10308, 2, 2, 0, 1 },
				.disconfall_det_en = { 0x10300, 7, 7, 0, 1 },
				.disconfall_det_st = { 0x10304, 7, 7, 0, 1 },
				.disconfall_det_clr = { 0x10308, 7, 7, 0, 1 },
				.disconrise_det_en = { 0x10300, 6, 6, 0, 1 },
				.disconrise_det_st = { 0x10304, 6, 6, 0, 1 },
				.disconrise_det_clr = { 0x10308, 6, 6, 0, 1 },
				.idfall_det_en = { 0x10300, 5, 5, 0, 1 },
				.idfall_det_st = { 0x10304, 5, 5, 0, 1 },
				.idfall_det_clr = { 0x10308, 5, 5, 0, 1 },
				.idpullup = { 0x10230, 11, 11, 0, 1 },
				.idrise_det_en = { 0x10300, 4, 4, 0, 1 },
				.idrise_det_st = { 0x10304, 4, 4, 0, 1 },
				.idrise_det_clr = { 0x10308, 4, 4, 0, 1 },
				.ls_det_en = { 0x10300, 0, 0, 0, 1 },
				.ls_det_st = { 0x10304, 0, 0, 0, 1 },
				.ls_det_clr = { 0x10308, 0, 0, 0, 1 },
				.phy_sus = { 0x10230, 8, 0, 0x052, 0x1d9 },
				.utmi_bvalid = { 0x10248, 9, 9, 0, 1 },
				.utmi_iddig = { 0x10248, 6, 6, 0, 1 },
				.utmi_hostdet = { 0x10248, 7, 7, 0, 1 },
			}
		},
		.chg_det = {
			.chg_en		= { 0x10234, 14, 14, 0, 1 },
			.chg_rst	= { 0x10234, 15, 15, 0, 1 },
			.chg_valid	= { 0x10248, 12, 12, 0, 1 },
			.phy_connect	= { 0x10248, 13, 13, 0, 1 },
		},
	},
	{
		.reg		= 0xff4c8000,
		.num_ports	= 1,
		.phy_tuning	= rv1126_usb2phy_tuning,
		.clkout_ctl	= { 0x10238, 9, 9, 0, 1 },
		.port_cfgs	= {
			[USB2PHY_PORT_HOST] = {
				.disconfall_det_en = { 0x10300, 9, 9, 0, 1 },
				.disconfall_det_st = { 0x10304, 9, 9, 0, 1 },
				.disconfall_det_clr = { 0x10308, 9, 9, 0, 1 },
				.disconrise_det_en = { 0x10300, 8, 8, 0, 1 },
				.disconrise_det_st = { 0x10304, 8, 8, 0, 1 },
				.disconrise_det_clr = { 0x10308, 8, 8, 0, 1 },
				.ls_det_en = { 0x10300, 1, 1, 0, 1 },
				.ls_det_st = { 0x10304, 1, 1, 0, 1 },
				.ls_det_clr = { 0x10308, 1, 1, 0, 1 },
				.phy_sus = { 0x10238, 3, 0, 0x2, 0x9 },
				.utmi_hostdet = { 0x10248, 23, 23, 0, 1 },
			}
		},
		.chg_det = {
			.chg_en		= { 0x10238, 7, 7, 0, 1 },
			.chg_rst	= { 0x10238, 8, 8, 0, 1 },
			.chg_valid	= { 0x10248, 28, 28, 0, 1 },
			.phy_connect	= { 0x10248, 29, 29, 0, 1 },
		},
		.last	= true,
	},
};

static const struct udevice_id rockchip_usb2phy_ids[] = {
	{ .compatible = "rockchip,rv1126-usb2phy", .data = (ulong)&rv1126_phy_cfgs },
	{ }
};

U_BOOT_DRIVER(rockchip_usb2phy_port) = {
	.name		= "rockchip_usb2phy_port",
	.id		= UCLASS_PHY,
	.ops		= &rockchip_usb2phy_ops,
};

U_BOOT_DRIVER(rockchip_usb2phy) = {
	.name		= "rockchip_usb2phy",
	.id		= UCLASS_PHY,
	.of_match	= rockchip_usb2phy_ids,
	.probe		= rockchip_usb2phy_probe,
	.bind		= rockchip_usb2phy_bind,
	.priv_auto_alloc_size = sizeof(struct rockchip_usb2phy),
};
