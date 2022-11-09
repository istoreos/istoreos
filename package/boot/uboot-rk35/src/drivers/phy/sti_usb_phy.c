/*
 * Copyright (C) 2017, STMicroelectronics - All Rights Reserved
 * Author(s): Patrice Chotard, <patrice.chotard@st.com> for STMicroelectronics.
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <common.h>
#include <asm/io.h>
#include <bitfield.h>
#include <dm.h>
#include <errno.h>
#include <fdtdec.h>
#include <generic-phy.h>
#include <linux/libfdt.h>
#include <regmap.h>
#include <reset-uclass.h>
#include <syscon.h>
#include <wait_bit.h>

#include <linux/bitops.h>
#include <linux/compat.h>

DECLARE_GLOBAL_DATA_PTR;

/* Default PHY_SEL and REFCLKSEL configuration */
#define STIH407_USB_PICOPHY_CTRL_PORT_CONF	0x6

/* ports parameters overriding */
#define STIH407_USB_PICOPHY_PARAM_DEF		0x39a4dc

#define PHYPARAM_REG	1
#define PHYCTRL_REG	2
#define PHYPARAM_NB	3

struct sti_usb_phy {
	struct regmap *regmap;
	struct reset_ctl global_ctl;
	struct reset_ctl port_ctl;
	int param;
	int ctrl;
};

static int sti_usb_phy_deassert(struct sti_usb_phy *phy)
{
	int ret;

	ret = reset_deassert(&phy->global_ctl);
	if (ret < 0) {
		pr_err("PHY global deassert failed: %d", ret);
		return ret;
	}

	ret = reset_deassert(&phy->port_ctl);
	if (ret < 0)
		pr_err("PHY port deassert failed: %d", ret);

	return ret;
}

static int sti_usb_phy_init(struct phy *usb_phy)
{
	struct udevice *dev = usb_phy->dev;
	struct sti_usb_phy *phy = dev_get_priv(dev);
	void __iomem *reg;

	/* set ctrl picophy value */
	reg = (void __iomem *)phy->regmap->base + phy->ctrl;
	/* CTRL_PORT mask is 0x1f */
	clrsetbits_le32(reg, 0x1f, STIH407_USB_PICOPHY_CTRL_PORT_CONF);

	/* set ports parameters overriding */
	reg = (void __iomem *)phy->regmap->base + phy->param;
	/* PARAM_DEF mask is 0xffffffff */
	clrsetbits_le32(reg, 0xffffffff, STIH407_USB_PICOPHY_PARAM_DEF);

	return sti_usb_phy_deassert(phy);
}

static int sti_usb_phy_exit(struct phy *usb_phy)
{
	struct udevice *dev = usb_phy->dev;
	struct sti_usb_phy *phy = dev_get_priv(dev);
	int ret;

	ret = reset_assert(&phy->port_ctl);
	if (ret < 0) {
		pr_err("PHY port assert failed: %d", ret);
		return ret;
	}

	ret = reset_assert(&phy->global_ctl);
	if (ret < 0)
		pr_err("PHY global assert failed: %d", ret);

	return ret;
}

struct phy_ops sti_usb_phy_ops = {
	.init = sti_usb_phy_init,
	.exit = sti_usb_phy_exit,
};

int sti_usb_phy_probe(struct udevice *dev)
{
	struct sti_usb_phy *priv = dev_get_priv(dev);
	struct udevice *syscon;
	struct ofnode_phandle_args syscfg_phandle;
	u32 cells[PHYPARAM_NB];
	int ret, count;

	/* get corresponding syscon phandle */
	ret = dev_read_phandle_with_args(dev, "st,syscfg", NULL, 0, 0,
					 &syscfg_phandle);

	if (ret < 0) {
		pr_err("Can't get syscfg phandle: %d\n", ret);
		return ret;
	}

	ret = uclass_get_device_by_ofnode(UCLASS_SYSCON, syscfg_phandle.node,
					  &syscon);
	if (ret) {
		pr_err("unable to find syscon device (%d)\n", ret);
		return ret;
	}

	priv->regmap = syscon_get_regmap(syscon);
	if (!priv->regmap) {
		pr_err("unable to find regmap\n");
		return -ENODEV;
	}

	/* get phy param offset */
	count = fdtdec_get_int_array_count(gd->fdt_blob, dev_of_offset(dev),
					   "st,syscfg", cells,
					   ARRAY_SIZE(cells));

	if (count < 0) {
		pr_err("Bad PHY st,syscfg property %d\n", count);
		return -EINVAL;
	}

	if (count > PHYPARAM_NB) {
		pr_err("Unsupported PHY param count %d\n", count);
		return -EINVAL;
	}

	priv->param = cells[PHYPARAM_REG];
	priv->ctrl = cells[PHYCTRL_REG];

	/* get global reset control */
	ret = reset_get_by_name(dev, "global", &priv->global_ctl);
	if (ret) {
		pr_err("can't get global reset for %s (%d)", dev->name, ret);
		return ret;
	}

	/* get port reset control */
	ret = reset_get_by_name(dev, "port", &priv->port_ctl);
	if (ret) {
		pr_err("can't get port reset for %s (%d)", dev->name, ret);
		return ret;
	}

	return 0;
}

static const struct udevice_id sti_usb_phy_ids[] = {
	{ .compatible = "st,stih407-usb2-phy" },
	{ }
};

U_BOOT_DRIVER(sti_usb_phy) = {
	.name = "sti_usb_phy",
	.id = UCLASS_PHY,
	.of_match = sti_usb_phy_ids,
	.probe = sti_usb_phy_probe,
	.ops = &sti_usb_phy_ops,
	.priv_auto_alloc_size = sizeof(struct sti_usb_phy),
};
