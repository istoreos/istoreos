// SPDX-License-Identifier: GPL-2.0
/**
 * cdns_ti-ti.c - TI specific Glue layer for Cadence USB Controller
 *
 * Copyright (C) 2019 Texas Instruments Incorporated - http://www.ti.com
 */

#include <common.h>
#include <asm-generic/io.h>
#include <clk.h>
#include <dm.h>
#include <linux/io.h>
#include <linux/usb/otg.h>
#include <malloc.h>

#include "core.h"

/* USB Wrapper register offsets */
#define USBSS_PID		0x0
#define	USBSS_W1		0x4
#define USBSS_STATIC_CONFIG	0x8
#define USBSS_PHY_TEST		0xc
#define	USBSS_DEBUG_CTRL	0x10
#define	USBSS_DEBUG_INFO	0x14
#define	USBSS_DEBUG_LINK_STATE	0x18
#define	USBSS_DEVICE_CTRL	0x1c

/* Wrapper 1 register bits */
#define USBSS_W1_PWRUP_RST		BIT(0)
#define USBSS_W1_OVERCURRENT_SEL	BIT(8)
#define USBSS_W1_MODESTRAP_SEL		BIT(9)
#define USBSS_W1_OVERCURRENT		BIT(16)
#define USBSS_W1_MODESTRAP_MASK		GENMASK(18, 17)
#define USBSS_W1_MODESTRAP_SHIFT	17
#define USBSS_W1_USB2_ONLY		BIT(19)

/* Static config register bits */
#define USBSS1_STATIC_PLL_REF_SEL_MASK	GENMASK(8, 5)
#define USBSS1_STATIC_PLL_REF_SEL_SHIFT	5
#define USBSS1_STATIC_LOOPBACK_MODE_MASK	GENMASK(4, 3)
#define USBSS1_STATIC_LOOPBACK_MODE_SHIFT	3
#define USBSS1_STATIC_VBUS_SEL_MASK	GENMASK(2, 1)
#define USBSS1_STATIC_VBUS_SEL_SHIFT	1
#define USBSS1_STATIC_LANE_REVERSE	BIT(0)

/* Modestrap modes */
enum modestrap_mode { USBSS_MODESTRAP_MODE_NONE,
		      USBSS_MODESTRAP_MODE_HOST,
		      USBSS_MODESTRAP_MODE_PERIPHERAL};

struct cdns_ti {
	struct udevice *dev;
	void __iomem *usbss;
	int usb2_only:1;
	int vbus_divider:1;
	struct clk *usb2_refclk;
	struct clk *lpm_clk;
};

static const int cdns_ti_rate_table[] = {	/* in KHZ */
	9600,
	10000,
	12000,
	19200,
	20000,
	24000,
	25000,
	26000,
	38400,
	40000,
	58000,
	50000,
	52000,
};

static inline u32 cdns_ti_readl(struct cdns_ti *data, u32 offset)
{
	return readl(data->usbss + offset);
}

static inline void cdns_ti_writel(struct cdns_ti *data, u32 offset, u32 value)
{
	writel(value, data->usbss + offset);
}

static int cdns_ti_probe(struct udevice *dev)
{
	struct cdns_ti *data = dev_get_platdata(dev);
	struct clk usb2_refclk;
	int modestrap_mode;
	unsigned long rate;
	int rate_code, i;
	u32 reg;
	int ret;

	data->dev = dev;

	data->usbss = dev_remap_addr_index(dev, 0);
	if (!data->usbss)
		return -EINVAL;

	ret = clk_get_by_name(dev, "usb2_refclk", &usb2_refclk);
	if (ret) {
		dev_err(dev, "Failed to get usb2_refclk\n");
		return ret;
	}

	rate = clk_get_rate(&usb2_refclk);
	rate /= 1000;	/* To KHz */
	for (i = 0; i < ARRAY_SIZE(cdns_ti_rate_table); i++) {
		if (cdns_ti_rate_table[i] == rate)
			break;
	}

	if (i == ARRAY_SIZE(cdns_ti_rate_table)) {
		dev_err(dev, "unsupported usb2_refclk rate: %lu KHz\n", rate);
		return -EINVAL;
	}

	rate_code = i;

	/* assert RESET */
	reg = cdns_ti_readl(data, USBSS_W1);
	reg &= ~USBSS_W1_PWRUP_RST;
	cdns_ti_writel(data, USBSS_W1, reg);

	/* set static config */
	reg = cdns_ti_readl(data, USBSS_STATIC_CONFIG);
	reg &= ~USBSS1_STATIC_PLL_REF_SEL_MASK;
	reg |= rate_code << USBSS1_STATIC_PLL_REF_SEL_SHIFT;

	reg &= ~USBSS1_STATIC_VBUS_SEL_MASK;
	data->vbus_divider = dev_read_bool(dev, "ti,vbus-divider");
	if (data->vbus_divider)
		reg |= 1 << USBSS1_STATIC_VBUS_SEL_SHIFT;

	cdns_ti_writel(data, USBSS_STATIC_CONFIG, reg);
	reg = cdns_ti_readl(data, USBSS_STATIC_CONFIG);

	/* set USB2_ONLY mode if requested */
	reg = cdns_ti_readl(data, USBSS_W1);
	data->usb2_only = dev_read_bool(dev, "ti,usb2-only");
	if (data->usb2_only)
		reg |= USBSS_W1_USB2_ONLY;

	/* set modestrap  */
	if (dev_read_bool(dev, "ti,modestrap-host"))
		modestrap_mode = USBSS_MODESTRAP_MODE_HOST;
	else if (dev_read_bool(dev, "ti,modestrap-peripheral"))
		modestrap_mode = USBSS_MODESTRAP_MODE_PERIPHERAL;
	else
		modestrap_mode = USBSS_MODESTRAP_MODE_NONE;

	reg |= USBSS_W1_MODESTRAP_SEL;
	reg &= ~USBSS_W1_MODESTRAP_MASK;
	reg |= modestrap_mode << USBSS_W1_MODESTRAP_SHIFT;
	cdns_ti_writel(data, USBSS_W1, reg);

	/* de-assert RESET */
	reg |= USBSS_W1_PWRUP_RST;
	cdns_ti_writel(data, USBSS_W1, reg);

	return 0;
}

static int cdns_ti_remove(struct udevice *dev)
{
	struct cdns_ti *data = dev_get_platdata(dev);
	u32 reg;

	/* put device back to RESET*/
	reg = cdns_ti_readl(data, USBSS_W1);
	reg &= ~USBSS_W1_PWRUP_RST;
	cdns_ti_writel(data, USBSS_W1, reg);

	return 0;
}

static const struct udevice_id cdns_ti_of_match[] = {
	{ .compatible = "ti,j721e-usb", },
	{},
};

U_BOOT_DRIVER(cdns_ti) = {
	.name = "cdns-ti",
	.id = UCLASS_NOP,
	.of_match = cdns_ti_of_match,
	.bind = cdns3_bind,
	.probe = cdns_ti_probe,
	.remove = cdns_ti_remove,
	.platdata_auto_alloc_size = sizeof(struct cdns_ti),
	.flags = DM_FLAG_OS_PREPARE,
};
