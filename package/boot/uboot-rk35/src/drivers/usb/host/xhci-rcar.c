/*
 * Copyright (C) 2017 Marek Vasut <marek.vasut@gmail.com>
 *
 * Renesas RCar USB HOST xHCI Controller
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <common.h>
#include <clk.h>
#include <dm.h>
#include <fdtdec.h>
#include <usb.h>
#include <wait_bit.h>

#include <usb/xhci.h>
#include "xhci-rcar-r8a779x_usb3_v3.h"

/* Register Offset */
#define RCAR_USB3_DL_CTRL	0x250	/* FW Download Control & Status */
#define RCAR_USB3_FW_DATA0	0x258	/* FW Data0 */

/* Register Settings */
/* FW Download Control & Status */
#define RCAR_USB3_DL_CTRL_ENABLE	BIT(0)
#define RCAR_USB3_DL_CTRL_FW_SUCCESS	BIT(4)
#define RCAR_USB3_DL_CTRL_FW_SET_DATA0	BIT(8)

struct rcar_xhci_platdata {
	fdt_addr_t	hcd_base;
	struct clk	clk;
};

/**
 * Contains pointers to register base addresses
 * for the usb controller.
 */
struct rcar_xhci {
	struct xhci_ctrl ctrl;	/* Needs to come first in this struct! */
	struct usb_platdata usb_plat;
	struct xhci_hccr *hcd;
};

static int xhci_rcar_download_fw(struct rcar_xhci *ctx, const u32 *fw_data,
				 const size_t fw_array_size)
{
	void __iomem *regs = (void __iomem *)ctx->hcd;
	int i, ret;

	/* Download R-Car USB3.0 firmware */
	setbits_le32(regs + RCAR_USB3_DL_CTRL, RCAR_USB3_DL_CTRL_ENABLE);

	for (i = 0; i < fw_array_size; i++) {
		writel(fw_data[i], regs + RCAR_USB3_FW_DATA0);
		setbits_le32(regs + RCAR_USB3_DL_CTRL,
			     RCAR_USB3_DL_CTRL_FW_SET_DATA0);

<<<<<<< HEAD
		ret = wait_for_bit_le32(regs + RCAR_USB3_DL_CTRL,
					RCAR_USB3_DL_CTRL_FW_SET_DATA0, false,
					10, false);
=======
		ret = wait_for_bit("xhci-rcar", regs + RCAR_USB3_DL_CTRL,
				   RCAR_USB3_DL_CTRL_FW_SET_DATA0, false,
				   10, false);
>>>>>>> e1cc60c... usb: xhci: Add Renesas R-Car xHCI driver
		if (ret)
			break;
	}

	clrbits_le32(regs + RCAR_USB3_DL_CTRL, RCAR_USB3_DL_CTRL_ENABLE);

<<<<<<< HEAD
	ret = wait_for_bit_le32(regs + RCAR_USB3_DL_CTRL,
				RCAR_USB3_DL_CTRL_FW_SUCCESS, true,
				10, false);
=======
	ret = wait_for_bit("xhci-rcar", regs + RCAR_USB3_DL_CTRL,
			   RCAR_USB3_DL_CTRL_FW_SUCCESS, true,
			   10, false);
>>>>>>> e1cc60c... usb: xhci: Add Renesas R-Car xHCI driver

	return ret;
}

static int xhci_rcar_probe(struct udevice *dev)
{
	struct rcar_xhci_platdata *plat = dev_get_platdata(dev);
	struct rcar_xhci *ctx = dev_get_priv(dev);
	struct xhci_hcor *hcor;
	int len, ret;

	ret = clk_get_by_index(dev, 0, &plat->clk);
	if (ret < 0) {
		dev_err(dev, "Failed to get USB3 clock\n");
		return ret;
	}

	ret = clk_enable(&plat->clk);
	if (ret) {
		dev_err(dev, "Failed to enable USB3 clock\n");
		goto err_clk;
	}

	ctx->hcd = (struct xhci_hccr *)plat->hcd_base;
	len = HC_LENGTH(xhci_readl(&ctx->hcd->cr_capbase));
	hcor = (struct xhci_hcor *)((uintptr_t)ctx->hcd + len);

	ret = xhci_rcar_download_fw(ctx, firmware_r8a779x_usb3_v3,
				    ARRAY_SIZE(firmware_r8a779x_usb3_v3));
	if (ret) {
		dev_err(dev, "Failed to download firmware\n");
		goto err_fw;
	}

	ret = xhci_register(dev, ctx->hcd, hcor);
	if (ret) {
		dev_err(dev, "Failed to register xHCI\n");
		goto err_fw;
	}

	return 0;

err_fw:
	clk_disable(&plat->clk);
err_clk:
	clk_free(&plat->clk);
	return ret;
}

static int xhci_rcar_deregister(struct udevice *dev)
{
	int ret;
	struct rcar_xhci_platdata *plat = dev_get_platdata(dev);

	ret = xhci_deregister(dev);

	clk_disable(&plat->clk);
	clk_free(&plat->clk);

	return ret;
}

static int xhci_rcar_ofdata_to_platdata(struct udevice *dev)
{
	struct rcar_xhci_platdata *plat = dev_get_platdata(dev);

	plat->hcd_base = devfdt_get_addr(dev);
	if (plat->hcd_base == FDT_ADDR_T_NONE) {
		debug("Can't get the XHCI register base address\n");
		return -ENXIO;
	}

	return 0;
}

static const struct udevice_id xhci_rcar_ids[] = {
	{ .compatible = "renesas,xhci-r8a7795" },
	{ .compatible = "renesas,xhci-r8a7796" },
	{ .compatible = "renesas,xhci-r8a77965" },
	{ }
};

U_BOOT_DRIVER(usb_xhci) = {
	.name		= "xhci_rcar",
	.id		= UCLASS_USB,
	.probe		= xhci_rcar_probe,
	.remove		= xhci_rcar_deregister,
	.ops		= &xhci_usb_ops,
	.of_match	= xhci_rcar_ids,
	.ofdata_to_platdata = xhci_rcar_ofdata_to_platdata,
	.platdata_auto_alloc_size = sizeof(struct rcar_xhci_platdata),
	.priv_auto_alloc_size = sizeof(struct rcar_xhci),
	.flags		= DM_FLAG_ALLOC_PRIV_DMA,
};
