/*
 * STiH407 family DWC3 specific Glue layer
 *
 * Copyright (C) 2017, STMicroelectronics - All Rights Reserved
 * Author(s): Patrice Chotard, <patrice.chotard@st.com> for STMicroelectronics.
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <common.h>
#include <asm/io.h>
#include <dm.h>
#include <errno.h>
#include <dm/lists.h>
#include <regmap.h>
#include <reset-uclass.h>
#include <syscon.h>
#include <usb.h>

#include <linux/usb/dwc3.h>
#include <linux/usb/otg.h>
#include <dwc3-sti-glue.h>

DECLARE_GLOBAL_DATA_PTR;

/*
 * struct sti_dwc3_glue_platdata - dwc3 STi glue driver private structure
 * @syscfg_base:	addr for the glue syscfg
 * @glue_base:		addr for the glue registers
 * @syscfg_offset:	usb syscfg control offset
 * @powerdown_ctl:	rest controller for powerdown signal
 * @softreset_ctl:	reset controller for softreset signal
 * @mode:		drd static host/device config
 */
struct sti_dwc3_glue_platdata {
	phys_addr_t syscfg_base;
	phys_addr_t glue_base;
	phys_addr_t syscfg_offset;
	struct reset_ctl powerdown_ctl;
	struct reset_ctl softreset_ctl;
	enum usb_dr_mode mode;
};

static int sti_dwc3_glue_drd_init(struct sti_dwc3_glue_platdata *plat)
{
	unsigned long val;

	val = readl(plat->syscfg_base + plat->syscfg_offset);

	val &= USB3_CONTROL_MASK;

	switch (plat->mode) {
	case USB_DR_MODE_PERIPHERAL:
		val &= ~(USB3_DELAY_VBUSVALID
			| USB3_SEL_FORCE_OPMODE | USB3_FORCE_OPMODE(0x3)
			| USB3_SEL_FORCE_DPPULLDOWN2 | USB3_FORCE_DPPULLDOWN2
			| USB3_SEL_FORCE_DMPULLDOWN2 | USB3_FORCE_DMPULLDOWN2);

		val |= USB3_DEVICE_NOT_HOST | USB3_FORCE_VBUSVALID;
		break;

	case USB_DR_MODE_HOST:
		val &= ~(USB3_DEVICE_NOT_HOST | USB3_FORCE_VBUSVALID
			| USB3_SEL_FORCE_OPMODE	| USB3_FORCE_OPMODE(0x3)
			| USB3_SEL_FORCE_DPPULLDOWN2 | USB3_FORCE_DPPULLDOWN2
			| USB3_SEL_FORCE_DMPULLDOWN2 | USB3_FORCE_DMPULLDOWN2);

		val |= USB3_DELAY_VBUSVALID;
		break;

	default:
		pr_err("Unsupported mode of operation %d\n", plat->mode);
		return -EINVAL;
	}
	writel(val, plat->syscfg_base + plat->syscfg_offset);

	return 0;
}

static void sti_dwc3_glue_init(struct sti_dwc3_glue_platdata *plat)
{
	unsigned long reg;

	reg = readl(plat->glue_base + CLKRST_CTRL);

	reg |= AUX_CLK_EN | EXT_CFG_RESET_N | XHCI_REVISION;
	reg &= ~SW_PIPEW_RESET_N;

	writel(reg, plat->glue_base + CLKRST_CTRL);

	/* configure mux for vbus, powerpresent and bvalid signals */
	reg = readl(plat->glue_base + USB2_VBUS_MNGMNT_SEL1);

	reg |= SEL_OVERRIDE_VBUSVALID(USB2_VBUS_UTMIOTG) |
	       SEL_OVERRIDE_POWERPRESENT(USB2_VBUS_UTMIOTG) |
	       SEL_OVERRIDE_BVALID(USB2_VBUS_UTMIOTG);

	writel(reg, plat->glue_base + USB2_VBUS_MNGMNT_SEL1);

	setbits_le32(plat->glue_base + CLKRST_CTRL, SW_PIPEW_RESET_N);
}

static int sti_dwc3_glue_ofdata_to_platdata(struct udevice *dev)
{
	struct sti_dwc3_glue_platdata *plat = dev_get_platdata(dev);
	struct udevice *syscon;
	struct regmap *regmap;
	int ret;
	u32 reg[4];

	ret = ofnode_read_u32_array(dev->node, "reg", reg, ARRAY_SIZE(reg));
	if (ret) {
		pr_err("unable to find st,stih407-dwc3 reg property(%d)\n", ret);
		return ret;
	}

	plat->glue_base = reg[0];
	plat->syscfg_offset = reg[2];

	/* get corresponding syscon phandle */
	ret = uclass_get_device_by_phandle(UCLASS_SYSCON, dev, "st,syscfg",
					   &syscon);
	if (ret) {
		pr_err("unable to find syscon device (%d)\n", ret);
		return ret;
	}

	/* get syscfg-reg base address */
	regmap = syscon_get_regmap(syscon);
	if (!regmap) {
		pr_err("unable to find regmap\n");
		return -ENODEV;
	}
	plat->syscfg_base = regmap->base;

	/* get powerdown reset */
	ret = reset_get_by_name(dev, "powerdown", &plat->powerdown_ctl);
	if (ret) {
		pr_err("can't get powerdown reset for %s (%d)", dev->name, ret);
		return ret;
	}

	/* get softreset reset */
	ret = reset_get_by_name(dev, "softreset", &plat->softreset_ctl);
	if (ret)
		pr_err("can't get soft reset for %s (%d)", dev->name, ret);

	return ret;
};

static int sti_dwc3_glue_bind(struct udevice *dev)
{
	struct sti_dwc3_glue_platdata *plat = dev_get_platdata(dev);
	ofnode node, dwc3_node;

	/* Find snps,dwc3 node from subnode */
	ofnode_for_each_subnode(node, dev->node) {
		if (ofnode_device_is_compatible(node, "snps,dwc3"))
			dwc3_node = node;
	}

	if (!ofnode_valid(node)) {
		pr_err("Can't find dwc3 subnode for %s\n", dev->name);
		return -ENODEV;
	}

	/* retrieve the DWC3 dual role mode */
	plat->mode = usb_get_dr_mode(dwc3_node);
	if (plat->mode == USB_DR_MODE_UNKNOWN)
		/* by default set dual role mode to HOST */
		plat->mode = USB_DR_MODE_HOST;

	return dm_scan_fdt_dev(dev);
}

static int sti_dwc3_glue_probe(struct udevice *dev)
{
	struct sti_dwc3_glue_platdata *plat = dev_get_platdata(dev);
	int ret;

	/* deassert both powerdown and softreset */
	ret = reset_deassert(&plat->powerdown_ctl);
	if (ret < 0) {
		pr_err("DWC3 powerdown reset deassert failed: %d", ret);
		return ret;
	}

	ret = reset_deassert(&plat->softreset_ctl);
	if (ret < 0) {
		pr_err("DWC3 soft reset deassert failed: %d", ret);
		goto softreset_err;
	}

	ret = sti_dwc3_glue_drd_init(plat);
	if (ret)
		goto init_err;

	sti_dwc3_glue_init(plat);

	return 0;

init_err:
	ret = reset_assert(&plat->softreset_ctl);
	if (ret < 0) {
		pr_err("DWC3 soft reset deassert failed: %d", ret);
		return ret;
	}

softreset_err:
	ret = reset_assert(&plat->powerdown_ctl);
	if (ret < 0)
		pr_err("DWC3 powerdown reset deassert failed: %d", ret);

	return ret;
}

static int sti_dwc3_glue_remove(struct udevice *dev)
{
	struct sti_dwc3_glue_platdata *plat = dev_get_platdata(dev);
	int ret;

	/* assert both powerdown and softreset */
	ret = reset_assert(&plat->powerdown_ctl);
	if (ret < 0) {
		pr_err("DWC3 powerdown reset deassert failed: %d", ret);
		return ret;
	}

	ret = reset_assert(&plat->softreset_ctl);
	if (ret < 0)
		pr_err("DWC3 soft reset deassert failed: %d", ret);

	return ret;
}

static const struct udevice_id sti_dwc3_glue_ids[] = {
	{ .compatible = "st,stih407-dwc3" },
	{ }
};

U_BOOT_DRIVER(dwc3_sti_glue) = {
	.name = "dwc3_sti_glue",
	.id = UCLASS_MISC,
	.of_match = sti_dwc3_glue_ids,
	.ofdata_to_platdata = sti_dwc3_glue_ofdata_to_platdata,
	.probe = sti_dwc3_glue_probe,
	.remove = sti_dwc3_glue_remove,
	.bind = sti_dwc3_glue_bind,
	.platdata_auto_alloc_size = sizeof(struct sti_dwc3_glue_platdata),
	.flags = DM_FLAG_ALLOC_PRIV_DMA,
};
