// SPDX-License-Identifier:     GPL-2.0
/*
 * Generic DWC3 Glue layer
 *
 * Copyright (C) 2016 - 2018 Xilinx, Inc.
 *
 * Based on dwc3-omap.c.
 */

#include <common.h>
#include <asm-generic/io.h>
#include <dm.h>
#include <dm/device-internal.h>
#include <dm/lists.h>
#include <dwc3-uboot.h>
#include <linux/usb/ch9.h>
#include <linux/usb/gadget.h>
#include <malloc.h>
#include <usb.h>
#include "core.h"
#include "gadget.h"
#include <reset.h>
#include <clk.h>
#include <usb/xhci.h>

struct dwc3_glue_data {
	struct clk_bulk		clks;
	struct reset_ctl_bulk	resets;
	fdt_addr_t regs;
};

struct dwc3_generic_plat {
	fdt_addr_t base;
	u32 maximum_speed;
	enum usb_dr_mode dr_mode;
};

struct dwc3_generic_priv {
	void *base;
	struct dwc3 dwc3;
	struct phy *phys;
	int num_phys;
};

struct dwc3_generic_host_priv {
	struct xhci_ctrl xhci_ctrl;
	struct dwc3_generic_priv gen_priv;
};

static int dwc3_generic_probe(struct udevice *dev,
			      struct dwc3_generic_priv *priv)
{
	int rc;
	struct dwc3_generic_plat *plat = dev_get_platdata(dev);
	struct dwc3 *dwc3 = &priv->dwc3;
	struct dwc3_glue_data *glue = dev_get_platdata(dev->parent);

	dwc3->dev = dev;
	dwc3->maximum_speed = plat->maximum_speed;
	dwc3->dr_mode = plat->dr_mode;
#if CONFIG_IS_ENABLED(OF_CONTROL)
	dwc3_of_parse(dwc3);
#endif

	/*
	 * It must hold whole USB3.0 OTG controller in resetting to hold pipe
	 * power state in P2 before initializing TypeC PHY on RK3399 platform.
	 */
	if (device_is_compatible(dev->parent, "rockchip,rk3399-dwc3")) {
		reset_assert_bulk(&glue->resets);
		udelay(1);
	}

	rc = dwc3_setup_phy(dev, &priv->phys, &priv->num_phys);
	if (rc)
		return rc;

	if (device_is_compatible(dev->parent, "rockchip,rk3399-dwc3"))
		reset_deassert_bulk(&glue->resets);

	priv->base = map_physmem(plat->base, DWC3_OTG_REGS_END, MAP_NOCACHE);
	dwc3->regs = priv->base + DWC3_GLOBALS_REGS_START;


	rc =  dwc3_init(dwc3);
	if (rc) {
		unmap_physmem(priv->base, MAP_NOCACHE);
		return rc;
	}

	return 0;
}

static int dwc3_generic_remove(struct udevice *dev,
			       struct dwc3_generic_priv *priv)
{
	struct dwc3 *dwc3 = &priv->dwc3;

	dwc3_remove(dwc3);
	dwc3_shutdown_phy(dev, priv->phys, priv->num_phys);
	unmap_physmem(dwc3->regs, MAP_NOCACHE);

	return 0;
}

static int dwc3_generic_ofdata_to_platdata(struct udevice *dev)
{
	struct dwc3_generic_plat *plat = dev_get_platdata(dev);
	ofnode node = dev->node;

	plat->base = dev_read_addr(dev);

	plat->maximum_speed = usb_get_maximum_speed(node);
	if (plat->maximum_speed == USB_SPEED_UNKNOWN) {
		pr_info("No USB maximum speed specified. Using super speed\n");
		plat->maximum_speed = USB_SPEED_SUPER;
	}

	plat->dr_mode = usb_get_dr_mode(node);
	if (plat->dr_mode == USB_DR_MODE_UNKNOWN) {
		pr_err("Invalid usb mode setup\n");
		return -ENODEV;
	} else if (plat->dr_mode != USB_DR_MODE_HOST &&
		   !strcmp(dev->driver->name, "dwc3-generic-host")) {
		pr_info("Set dr_mode to HOST\n");
		plat->dr_mode = USB_DR_MODE_HOST;
	}

	return 0;
}

#if CONFIG_IS_ENABLED(DM_USB_GADGET)
int dm_usb_gadget_handle_interrupts(struct udevice *dev)
{
	struct dwc3_generic_priv *priv = dev_get_priv(dev);
	struct dwc3 *dwc3 = &priv->dwc3;

	dwc3_gadget_uboot_handle_interrupt(dwc3);

	return 0;
}

static int dwc3_generic_peripheral_probe(struct udevice *dev)
{
	struct dwc3_generic_priv *priv = dev_get_priv(dev);

	return dwc3_generic_probe(dev, priv);
}

static int dwc3_generic_peripheral_remove(struct udevice *dev)
{
	struct dwc3_generic_priv *priv = dev_get_priv(dev);

	return dwc3_generic_remove(dev, priv);
}

U_BOOT_DRIVER(dwc3_generic_peripheral) = {
	.name	= "dwc3-generic-peripheral",
	.id	= UCLASS_USB_GADGET_GENERIC,
	.ofdata_to_platdata = dwc3_generic_ofdata_to_platdata,
	.probe = dwc3_generic_peripheral_probe,
	.remove = dwc3_generic_peripheral_remove,
	.priv_auto_alloc_size = sizeof(struct dwc3_generic_priv),
	.platdata_auto_alloc_size = sizeof(struct dwc3_generic_plat),
};
#endif

#if defined(CONFIG_SPL_USB_HOST_SUPPORT) || !defined(CONFIG_SPL_BUILD)
static int dwc3_generic_host_probe(struct udevice *dev)
{
	struct xhci_hcor *hcor;
	struct xhci_hccr *hccr;
	struct dwc3_generic_host_priv *priv = dev_get_priv(dev);
	int rc;

	rc = dwc3_generic_probe(dev, &priv->gen_priv);
	if (rc)
		return rc;

	hccr = (struct xhci_hccr *)priv->gen_priv.base;
	hcor = (struct xhci_hcor *)(priv->gen_priv.base +
			HC_LENGTH(xhci_readl(&(hccr)->cr_capbase)));

	return xhci_register(dev, hccr, hcor);
}

static int dwc3_generic_host_remove(struct udevice *dev)
{
	struct dwc3_generic_host_priv *priv = dev_get_priv(dev);
	int rc;

	rc = xhci_deregister(dev);
	if (rc)
		return rc;

	return dwc3_generic_remove(dev, &priv->gen_priv);
}

U_BOOT_DRIVER(dwc3_generic_host) = {
	.name	= "dwc3-generic-host",
	.id	= UCLASS_USB,
	.ofdata_to_platdata = dwc3_generic_ofdata_to_platdata,
	.probe = dwc3_generic_host_probe,
	.remove = dwc3_generic_host_remove,
	.priv_auto_alloc_size = sizeof(struct dwc3_generic_host_priv),
	.platdata_auto_alloc_size = sizeof(struct dwc3_generic_plat),
	.ops = &xhci_usb_ops,
	.flags = DM_FLAG_ALLOC_PRIV_DMA,
};
#endif

struct dwc3_glue_ops {
	void (*select_dr_mode)(struct udevice *dev, int index,
			       enum usb_dr_mode mode);
};

void dwc3_ti_select_dr_mode(struct udevice *dev, int index,
			    enum usb_dr_mode mode)
{
#define USBOTGSS_UTMI_OTG_STATUS		0x0084
#define USBOTGSS_UTMI_OTG_OFFSET		0x0480

/* UTMI_OTG_STATUS REGISTER */
#define USBOTGSS_UTMI_OTG_STATUS_SW_MODE	BIT(31)
#define USBOTGSS_UTMI_OTG_STATUS_POWERPRESENT	BIT(9)
#define USBOTGSS_UTMI_OTG_STATUS_TXBITSTUFFENABLE BIT(8)
#define USBOTGSS_UTMI_OTG_STATUS_IDDIG		BIT(4)
#define USBOTGSS_UTMI_OTG_STATUS_SESSEND	BIT(3)
#define USBOTGSS_UTMI_OTG_STATUS_SESSVALID	BIT(2)
#define USBOTGSS_UTMI_OTG_STATUS_VBUSVALID	BIT(1)
enum dwc3_omap_utmi_mode {
	DWC3_OMAP_UTMI_MODE_UNKNOWN = 0,
	DWC3_OMAP_UTMI_MODE_HW,
	DWC3_OMAP_UTMI_MODE_SW,
};

	u32 use_id_pin;
	u32 host_mode;
	u32 reg;
	u32 utmi_mode;
	u32 utmi_status_offset = USBOTGSS_UTMI_OTG_STATUS;

	struct dwc3_glue_data *glue = dev_get_platdata(dev);
	void *base = map_physmem(glue->regs, 0x10000, MAP_NOCACHE);

	if (device_is_compatible(dev, "ti,am437x-dwc3"))
		utmi_status_offset += USBOTGSS_UTMI_OTG_OFFSET;

	utmi_mode = dev_read_u32_default(dev, "utmi-mode",
					 DWC3_OMAP_UTMI_MODE_UNKNOWN);
	if (utmi_mode != DWC3_OMAP_UTMI_MODE_HW) {
		debug("%s: OTG is not supported. defaulting to PERIPHERAL\n",
		      dev->name);
		mode = USB_DR_MODE_PERIPHERAL;
	}

	switch (mode)  {
	case USB_DR_MODE_PERIPHERAL:
		use_id_pin = 0;
		host_mode = 0;
		break;
	case USB_DR_MODE_HOST:
		use_id_pin = 0;
		host_mode = 1;
		break;
	case USB_DR_MODE_OTG:
	default:
		use_id_pin = 1;
		host_mode = 0;
		break;
	}

	reg = readl(base + utmi_status_offset);

	reg &= ~(USBOTGSS_UTMI_OTG_STATUS_SW_MODE);
	if (!use_id_pin)
		reg |= USBOTGSS_UTMI_OTG_STATUS_SW_MODE;

	writel(reg, base + utmi_status_offset);

	reg &= ~(USBOTGSS_UTMI_OTG_STATUS_SESSEND |
		USBOTGSS_UTMI_OTG_STATUS_VBUSVALID |
		USBOTGSS_UTMI_OTG_STATUS_IDDIG);

	reg |= USBOTGSS_UTMI_OTG_STATUS_SESSVALID |
		USBOTGSS_UTMI_OTG_STATUS_POWERPRESENT;

	if (!host_mode)
		reg |= USBOTGSS_UTMI_OTG_STATUS_IDDIG |
			USBOTGSS_UTMI_OTG_STATUS_VBUSVALID;

	writel(reg, base + utmi_status_offset);

	unmap_physmem(base, MAP_NOCACHE);
}

struct dwc3_glue_ops ti_ops = {
	.select_dr_mode = dwc3_ti_select_dr_mode,
};

static int dwc3_glue_bind(struct udevice *parent)
{
	ofnode node;
	int ret;

	ofnode_for_each_subnode(node, parent->node) {
		const char *name = ofnode_get_name(node);
		enum usb_dr_mode dr_mode;
		struct udevice *dev;
		const char *driver = NULL;

		debug("%s: subnode name: %s\n", __func__, name);

		dr_mode = usb_get_dr_mode(node);

		switch (dr_mode) {
		case USB_DR_MODE_OTG:
#if defined(CONFIG_ARCH_ROCKCHIP) && defined(CONFIG_USB_XHCI_HCD)
			debug("%s: dr_mode: force to HOST\n", __func__);
			driver = "dwc3-generic-host";
			break;
#endif
		case USB_DR_MODE_PERIPHERAL:
#if CONFIG_IS_ENABLED(DM_USB_GADGET)
			debug("%s: dr_mode: OTG or Peripheral\n", __func__);
			driver = "dwc3-generic-peripheral";
#endif
			break;
#if defined(CONFIG_SPL_USB_HOST_SUPPORT) || !defined(CONFIG_SPL_BUILD)
		case USB_DR_MODE_HOST:
			debug("%s: dr_mode: HOST\n", __func__);
			driver = "dwc3-generic-host";
			break;
#endif
		default:
			debug("%s: unsupported dr_mode\n", __func__);
			return -ENODEV;
		};

		if (!driver)
			continue;

		ret = device_bind_driver_to_node(parent, driver, name,
						 node, &dev);
		if (ret) {
			debug("%s: not able to bind usb device mode\n",
			      __func__);
			return ret;
		}
	}

	return 0;
}

static int dwc3_glue_reset_init(struct udevice *dev,
				struct dwc3_glue_data *glue)
{
	int ret;

	ret = reset_get_bulk(dev, &glue->resets);
	if (ret == -ENOTSUPP || ret == -ENOENT)
		return 0;
	else if (ret)
		return ret;

	ret = reset_deassert_bulk(&glue->resets);
	if (ret) {
		reset_release_bulk(&glue->resets);
		return ret;
	}

	return 0;
}

static int dwc3_glue_clk_init(struct udevice *dev,
			      struct dwc3_glue_data *glue)
{
	int ret;

	ret = clk_get_bulk(dev, &glue->clks);
	if (ret == -ENOSYS || ret == -ENOENT)
		return 0;
	if (ret)
		return ret;

#if CONFIG_IS_ENABLED(CLK)
	ret = clk_enable_bulk(&glue->clks);
	if (ret) {
		clk_release_bulk(&glue->clks);
		return ret;
	}
#endif

	return 0;
}

static int dwc3_glue_probe(struct udevice *dev)
{
	struct dwc3_glue_ops *ops = (struct dwc3_glue_ops *)dev_get_driver_data(dev);
	struct dwc3_glue_data *glue = dev_get_platdata(dev);
	struct udevice *child = NULL;
	int index = 0;
	int ret;

	glue->regs = dev_read_addr(dev);

	ret = dwc3_glue_clk_init(dev, glue);
	if (ret)
		return ret;

	ret = dwc3_glue_reset_init(dev, glue);
	if (ret)
		return ret;

	ret = device_find_first_child(dev, &child);
	if (ret)
		return ret;

	if (glue->resets.count < 1) {
		ret = dwc3_glue_reset_init(child, glue);
		if (ret)
			return ret;
	}

	while (child) {
		enum usb_dr_mode dr_mode;

		dr_mode = usb_get_dr_mode(child->node);
		device_find_next_child(&child);
		if (ops && ops->select_dr_mode)
			ops->select_dr_mode(dev, index, dr_mode);
		index++;
	}

	return 0;
}

static int dwc3_glue_remove(struct udevice *dev)
{
	struct dwc3_glue_data *glue = dev_get_platdata(dev);

	reset_release_bulk(&glue->resets);

	clk_release_bulk(&glue->clks);

	return 0;
}

static const struct udevice_id dwc3_glue_ids[] = {
	{ .compatible = "xlnx,zynqmp-dwc3" },
	{ .compatible = "ti,keystone-dwc3"},
	{ .compatible = "ti,dwc3", .data = (ulong)&ti_ops },
	{ .compatible = "ti,am437x-dwc3", .data = (ulong)&ti_ops },
	{ .compatible = "rockchip,rk3328-dwc3" },
	{ .compatible = "rockchip,rk3399-dwc3" },
	{ }
};

U_BOOT_DRIVER(dwc3_generic_wrapper) = {
	.name	= "dwc3-generic-wrapper",
	.id	= UCLASS_NOP,
	.of_match = dwc3_glue_ids,
	.bind = dwc3_glue_bind,
	.probe = dwc3_glue_probe,
	.remove = dwc3_glue_remove,
	.platdata_auto_alloc_size = sizeof(struct dwc3_glue_data),

};
