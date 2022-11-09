// SPDX-License-Identifier: GPL-2.0
/*
 * Texas Instruments da8xx "glue layer"
 *
 * Copyright (c) 2019, by Texas Instruments
 *
 * Based on the DA8xx "glue layer" code.
 * Copyright (c) 2008-2019, MontaVista Software, Inc. <source@mvista.com>
 *
 * DT support
 * Copyright (c) 2016 Petr Kulhavy <petr@barix.com>
 * This file is part of the Inventra Controller Driver for Linux.
 *
 */

#include <common.h>
#include <dm.h>
#include <dm/device-internal.h>
#include <dm/lists.h>
#include <asm/arch/hardware.h>
#include <asm/arch/da8xx-usb.h>
#include <linux/usb/otg.h>
#include <asm/omap_musb.h>
#include <generic-phy.h>
#include "linux-compat.h"
#include "musb_core.h"
#include "musb_uboot.h"

/* USB 2.0 OTG module registers */
#define DA8XX_USB_REVISION_REG	0x00
#define DA8XX_USB_CTRL_REG	0x04
#define DA8XX_USB_STAT_REG	0x08
#define DA8XX_USB_EMULATION_REG 0x0c
#define DA8XX_USB_SRP_FIX_TIME_REG 0x18
#define DA8XX_USB_INTR_SRC_REG	0x20
#define DA8XX_USB_INTR_SRC_SET_REG 0x24
#define DA8XX_USB_INTR_SRC_CLEAR_REG 0x28
#define DA8XX_USB_INTR_MASK_REG 0x2c
#define DA8XX_USB_INTR_MASK_SET_REG 0x30
#define DA8XX_USB_INTR_MASK_CLEAR_REG 0x34
#define DA8XX_USB_INTR_SRC_MASKED_REG 0x38
#define DA8XX_USB_END_OF_INTR_REG 0x3c
#define DA8XX_USB_GENERIC_RNDIS_EP_SIZE_REG(n) (0x50 + (((n) - 1) << 2))

/* Control register bits */
#define DA8XX_SOFT_RESET_MASK	1

#define DA8XX_USB_TX_EP_MASK	0x1f		/* EP0 + 4 Tx EPs */
#define DA8XX_USB_RX_EP_MASK	0x1e		/* 4 Rx EPs */

/* USB interrupt register bits */
#define DA8XX_INTR_USB_SHIFT	16
#define DA8XX_INTR_USB_MASK	(0x1ff << DA8XX_INTR_USB_SHIFT) /* 8 Mentor */
					/* interrupts and DRVVBUS interrupt */
#define DA8XX_INTR_DRVVBUS	0x100
#define DA8XX_INTR_RX_SHIFT	8
#define DA8XX_INTR_RX_MASK	(DA8XX_USB_RX_EP_MASK << DA8XX_INTR_RX_SHIFT)
#define DA8XX_INTR_TX_SHIFT	0
#define DA8XX_INTR_TX_MASK	(DA8XX_USB_TX_EP_MASK << DA8XX_INTR_TX_SHIFT)

#define DA8XX_MENTOR_CORE_OFFSET 0x400

static irqreturn_t da8xx_musb_interrupt(int irq, void *hci)
{
	struct musb		*musb = hci;
	void __iomem		*reg_base = musb->ctrl_base;
	unsigned long		flags;
	irqreturn_t		ret = IRQ_NONE;
	u32			status;

	spin_lock_irqsave(&musb->lock, flags);

	/*
	 * NOTE: DA8XX shadows the Mentor IRQs.  Don't manage them through
	 * the Mentor registers (except for setup), use the TI ones and EOI.
	 */

	/* Acknowledge and handle non-CPPI interrupts */
	status = musb_readl(reg_base, DA8XX_USB_INTR_SRC_MASKED_REG);
	if (!status)
		goto eoi;

	musb_writel(reg_base, DA8XX_USB_INTR_SRC_CLEAR_REG, status);
	dev_dbg(musb->controller, "USB IRQ %08x\n", status);

	musb->int_rx = (status & DA8XX_INTR_RX_MASK) >> DA8XX_INTR_RX_SHIFT;
	musb->int_tx = (status & DA8XX_INTR_TX_MASK) >> DA8XX_INTR_TX_SHIFT;
	musb->int_usb = (status & DA8XX_INTR_USB_MASK) >> DA8XX_INTR_USB_SHIFT;

	/*
	 * DRVVBUS IRQs are the only proxy we have (a very poor one!) for
	 * DA8xx's missing ID change IRQ.  We need an ID change IRQ to
	 * switch appropriately between halves of the OTG state machine.
	 * Managing DEVCTL.Session per Mentor docs requires that we know its
	 * value but DEVCTL.BDevice is invalid without DEVCTL.Session set.
	 * Also, DRVVBUS pulses for SRP (but not at 5 V)...
	 */
	if (status & (DA8XX_INTR_DRVVBUS << DA8XX_INTR_USB_SHIFT)) {
		int drvvbus = musb_readl(reg_base, DA8XX_USB_STAT_REG);
		void __iomem *mregs = musb->mregs;
		u8 devctl = musb_readb(mregs, MUSB_DEVCTL);
		int err;

		err = musb->int_usb & MUSB_INTR_VBUSERROR;
		if (err) {
			/*
			 * The Mentor core doesn't debounce VBUS as needed
			 * to cope with device connect current spikes. This
			 * means it's not uncommon for bus-powered devices
			 * to get VBUS errors during enumeration.
			 *
			 * This is a workaround, but newer RTL from Mentor
			 * seems to allow a better one: "re"-starting sessions
			 * without waiting for VBUS to stop registering in
			 * devctl.
			 */
			musb->int_usb &= ~MUSB_INTR_VBUSERROR;
			WARNING("VBUS error workaround (delay coming)\n");
		} else if (drvvbus) {
			MUSB_HST_MODE(musb);
			musb->port1_status |= USB_PORT_STAT_POWER;
		} else if (!(musb->int_usb & MUSB_INTR_BABBLE)) {
			/*
			 * When babble condition happens, drvvbus interrupt
			 * is also generated. Ignore this drvvbus interrupt
			 * and let babble interrupt handler recovers the
			 * controller; otherwise, the host-mode flag is lost
			 * due to the MUSB_DEV_MODE() call below and babble
			 * recovery logic will not be called.
			 */
			musb->is_active = 0;
			MUSB_DEV_MODE(musb);
			musb->port1_status &= ~USB_PORT_STAT_POWER;
		}
		ret = IRQ_HANDLED;
	}

	if (musb->int_tx || musb->int_rx || musb->int_usb)
		ret |= musb_interrupt(musb);
eoi:
	/* EOI needs to be written for the IRQ to be re-asserted. */
	if (ret == IRQ_HANDLED || status)
		musb_writel(reg_base, DA8XX_USB_END_OF_INTR_REG, 0);

	spin_unlock_irqrestore(&musb->lock, flags);

	return ret;
}

static int da8xx_musb_init(struct musb *musb)
{
	u32  revision;
	void __iomem *reg_base = musb->ctrl_base;

	int ret;

	/* reset the controller */
	writel(0x1, &da8xx_usb_regs->control);
	udelay(50);

	/* Returns zero if e.g. not clocked */
	revision = readl(&da8xx_usb_regs->revision);
	if (revision == 0)
		return -ENODEV;

	/* Disable all interrupts */
	writel((DA8XX_USB_USBINT_MASK | DA8XX_USB_TXINT_MASK |
		DA8XX_USB_RXINT_MASK), &da8xx_usb_regs->intmsk_set);

	musb->mregs += DA8XX_MENTOR_CORE_OFFSET;

	/* NOTE: IRQs are in mixed mode, not bypass to pure MUSB */
	debug("DA8xx OTG revision %08x, control %02x\n", revision,
	      musb_readb(reg_base, DA8XX_USB_CTRL_REG));

	musb->isr = da8xx_musb_interrupt;
	return 0;
}

static int da8xx_musb_exit(struct musb *musb)
{
	/* flush any interrupts */
	writel((DA8XX_USB_USBINT_MASK | DA8XX_USB_TXINT_MASK |
		DA8XX_USB_RXINT_MASK), &da8xx_usb_regs->intmsk_clr);
	writel(0, &da8xx_usb_regs->eoi);

	return 0;
}

/**
 * da8xx_musb_enable - enable interrupts
 */
static int da8xx_musb_enable(struct musb *musb)
{
	void __iomem *reg_base = musb->ctrl_base;
	u32 mask;

	/* Workaround: setup IRQs through both register sets. */
	mask = ((musb->epmask & DA8XX_USB_TX_EP_MASK) << DA8XX_INTR_TX_SHIFT) |
	       ((musb->epmask & DA8XX_USB_RX_EP_MASK) << DA8XX_INTR_RX_SHIFT) |
	       DA8XX_INTR_USB_MASK;
	musb_writel(reg_base, DA8XX_USB_INTR_MASK_SET_REG, mask);

	/* Force the DRVVBUS IRQ so we can start polling for ID change. */
	musb_writel(reg_base, DA8XX_USB_INTR_SRC_SET_REG,
		    DA8XX_INTR_DRVVBUS << DA8XX_INTR_USB_SHIFT);

	return 0;
}

/**
 * da8xx_musb_disable - disable HDRC and flush interrupts
 */
static void da8xx_musb_disable(struct musb *musb)
{
	void __iomem *reg_base = musb->ctrl_base;

	musb_writel(reg_base, DA8XX_USB_INTR_MASK_CLEAR_REG,
		    DA8XX_INTR_USB_MASK |
		    DA8XX_INTR_TX_MASK | DA8XX_INTR_RX_MASK);
	musb_writel(reg_base, DA8XX_USB_END_OF_INTR_REG, 0);
}

void da8xx_musb_reset(struct udevice *dev)
{
	void *reg_base = dev_read_addr_ptr(dev);

	/* Reset the controller */
	musb_writel(reg_base, DA8XX_USB_CTRL_REG, DA8XX_SOFT_RESET_MASK);
}

void da8xx_musb_clear_irq(struct udevice *dev)
{
	/* flush any interrupts */
	writel((DA8XX_USB_USBINT_MASK | DA8XX_USB_TXINT_MASK |
		DA8XX_USB_RXINT_MASK), &da8xx_usb_regs->intmsk_clr);
	writel(0, &da8xx_usb_regs->eoi);
}

const struct musb_platform_ops da8xx_ops = {
	.init		= da8xx_musb_init,
	.exit		= da8xx_musb_exit,
	.enable		= da8xx_musb_enable,
	.disable	= da8xx_musb_disable,
};

struct da8xx_musb_platdata {
	void *base;
	void *ctrl_mod_base;
	struct musb_hdrc_platform_data plat;
	struct musb_hdrc_config musb_config;
	struct omap_musb_board_data otg_board_data;
	struct phy phy;
};

static int da8xx_musb_ofdata_to_platdata(struct udevice *dev)
{
	struct da8xx_musb_platdata *platdata = dev_get_platdata(dev);
	const void *fdt = gd->fdt_blob;
	int node = dev_of_offset(dev);

	platdata->base = (void *)dev_read_addr_ptr(dev);
	platdata->musb_config.multipoint = 1;
	platdata->musb_config.dyn_fifo = 1;
	platdata->musb_config.num_eps = 5;
	platdata->musb_config.ram_bits = 10;
	platdata->plat.power = fdtdec_get_int(fdt, node, "power", 50);
	platdata->otg_board_data.interface_type = MUSB_INTERFACE_UTMI;
	platdata->plat.mode = MUSB_HOST;
	platdata->otg_board_data.dev = dev;
	platdata->plat.config = &platdata->musb_config;
	platdata->plat.platform_ops = &da8xx_ops;
	platdata->plat.board_data = &platdata->otg_board_data;
	platdata->otg_board_data.clear_irq = da8xx_musb_clear_irq;
	platdata->otg_board_data.reset = da8xx_musb_reset;
	return 0;
}

static int da8xx_musb_probe(struct udevice *dev)
{
	struct musb_host_data *host = dev_get_priv(dev);
	struct da8xx_musb_platdata *platdata = dev_get_platdata(dev);
	struct usb_bus_priv *priv = dev_get_uclass_priv(dev);
	struct omap_musb_board_data *otg_board_data;
	int ret;
	void *base = dev_read_addr_ptr(dev);

	/* Get the phy info from the device tree */
	ret = generic_phy_get_by_name(dev, "usb-phy", &platdata->phy);
	if (ret)
		return ret;

	/* Initialize the phy */
	ret = generic_phy_init(&platdata->phy);
	if (ret)
		return ret;

	/* enable psc for usb2.0 */
	lpsc_on(33);

	/* Enable phy */
	generic_phy_power_on(&platdata->phy);

	priv->desc_before_addr = true;
	otg_board_data = &platdata->otg_board_data;

	host->host = musb_init_controller(&platdata->plat,
					  (struct device *)otg_board_data,
					  platdata->base);
	if (!host->host) {
		ret = -ENODEV;
		goto shutdown; /* Shutdown what we started */
	}

	ret = musb_lowlevel_init(host);

	if (ret == 0)
		return 0;
shutdown:
	/* Turn off the phy if we fail */
	generic_phy_power_off(&platdata->phy);
	lpsc_disable(33);
	return ret;
}

static int da8xx_musb_remove(struct udevice *dev)
{
	struct musb_host_data *host = dev_get_priv(dev);

	musb_stop(host->host);

	return 0;
}

static const struct udevice_id da8xx_musb_ids[] = {
	{ .compatible = "ti,da830-musb" },
	{ }
};

U_BOOT_DRIVER(da8xx_musb) = {
	.name	= "da8xx-musb",
	.id		= UCLASS_USB,
	.of_match = da8xx_musb_ids,
	.ofdata_to_platdata = da8xx_musb_ofdata_to_platdata,
	.probe = da8xx_musb_probe,
	.remove = da8xx_musb_remove,
	.ops = &musb_usb_ops,
	.platdata_auto_alloc_size = sizeof(struct da8xx_musb_platdata),
	.priv_auto_alloc_size = sizeof(struct musb_host_data),
};
