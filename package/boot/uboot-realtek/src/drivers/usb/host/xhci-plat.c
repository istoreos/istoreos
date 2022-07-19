/*
 * SAMSUNG EXYNOS5 USB HOST XHCI Controller
 *
 * Copyright (C) 2012 Samsung Electronics Co.Ltd
 *	Vivek Gautam <gautam.vivek@samsung.com>
 *	Vikas Sajjan <vikas.sajjan@samsung.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301 USA
 */

/*
 * This file is a conglomeration for DWC3-init sequence and further
 * exynos5 specific PHY-init sequence.
 */

#include <common.h>
#include <malloc.h>
#include <usb.h>
#include <watchdog.h>
#include <asm-generic/errno.h>
#include <linux/compat.h>

#include "xhci.h"
#include <usb/usb_reg.h>
#include <asm/arch/usb.h>
#include <asm/processor.h>

#include <usb-phy.h>
#include "host-rtk.h"

struct ctrl_data {
	void *dwc3_addr;
	void *wrap_addr;

	struct usb2_phy *u2phy;
	struct usb3_phy *u3phy;
};

#define RTK_DWC3_BASE		0x8100

static u32 dwc3_readl(struct ctrl_data dwc3, u32 offset)
{
	/*
	 * We requested the mem region starting from the Globals address
	 * space, see dwc3_probe in core.c.
	 * However, the offsets are given starting from xHCI address space.
	 */
	return __raw_readl((volatile u32*)(dwc3.dwc3_addr + (offset - DWC3_GLOBALS_REGS_START)));
}

static void dwc3_writel(struct ctrl_data dwc3, u32 offset, u32 value)
{
	/*
	 * We requested the mem region starting from the Globals address
	 * space, see dwc3_probe in core.c.
	 * However, the offsets are given starting from xHCI address space.
	 */
	__raw_writel(value, (volatile u32*)(dwc3.dwc3_addr + (offset - DWC3_GLOBALS_REGS_START)));
}

void dwc3_set_mode(struct ctrl_data dwc3, u32 mode)
{
	u32 reg;

	reg = dwc3_readl(dwc3, DWC3_GCTL);
	reg &= ~(DWC3_GCTL_PRTCAPDIR(DWC3_GCTL_PRTCAP_OTG));
	reg |= DWC3_GCTL_PRTCAPDIR(mode);
	dwc3_writel(dwc3, DWC3_GCTL, reg);
}

static void dwc3_core_soft_reset(struct ctrl_data dwc3)
{
	u32		reg;

	/* Before Resetting PHY, put Core in Reset */
	reg = dwc3_readl(dwc3, DWC3_GCTL);
	reg |= DWC3_GCTL_CORESOFTRESET;
	dwc3_writel(dwc3, DWC3_GCTL, reg);
	mdelay(100);

	/* Assert USB3 PHY reset */
	reg = dwc3_readl(dwc3, DWC3_GUSB3PIPECTL(0));
	reg |= DWC3_GUSB3PIPECTL_PHYSOFTRST;
	dwc3_writel(dwc3, DWC3_GUSB3PIPECTL(0), reg);
	mdelay(100);

	/* Assert USB2 PHY reset */
	reg = dwc3_readl(dwc3, DWC3_GUSB2PHYCFG(0));
	reg |= DWC3_GUSB2PHYCFG_PHYSOFTRST;
	dwc3_writel(dwc3, DWC3_GUSB2PHYCFG(0), reg);
	mdelay(100);

	usb3_phy_init(dwc3.u3phy);
	mdelay(100);

	/* Clear USB3 PHY reset */
	reg = dwc3_readl(dwc3, DWC3_GUSB3PIPECTL(0));
	reg &= ~DWC3_GUSB3PIPECTL_PHYSOFTRST;
	dwc3_writel(dwc3, DWC3_GUSB3PIPECTL(0), reg);
	mdelay(100);

	/* Clear USB2 PHY reset */
	reg = dwc3_readl(dwc3, DWC3_GUSB2PHYCFG(0));
	reg &= ~DWC3_GUSB2PHYCFG_PHYSOFTRST;
	dwc3_writel(dwc3, DWC3_GUSB2PHYCFG(0), reg);

	mdelay(100);

	/* After PHYs are stable we can take Core out of reset state */
	reg = dwc3_readl(dwc3, DWC3_GCTL);
	reg &= ~DWC3_GCTL_CORESOFTRESET;
	dwc3_writel(dwc3, DWC3_GCTL, reg);
	mdelay(100);

	usb2_phy_init(dwc3.u2phy);
	mdelay(100);

}

static int dwc3_core_init(struct ctrl_data dwc3)
{
	unsigned long		timeout= 5000;
	u32			reg, revision;
	int			ret;

	u32 hwparams1 = dwc3_readl(dwc3, DWC3_GHWPARAMS1);

	reg = dwc3_readl(dwc3, DWC3_GSNPSID);	//c120
	/* This should read as U3 followed by revision number */
	if ((reg & DWC3_GSNPSID_MASK) != 0x55330000) {
		printf("this is not a DesignWare USB3 DRD Core\n");
		ret = -ENODEV;
		goto err0;
	}
	revision = reg;

	/* issue device SoftReset too */

	dwc3_writel(dwc3, DWC3_DCTL, DWC3_DCTL_CSFTRST);
	mdelay(100);
	timeout = 5000;
	while ( ((dwc3_readl(dwc3, DWC3_DCTL)) & DWC3_DCTL_CSFTRST) && timeout-- ) 
	{
		mdelay(10);
		if (timeout <= 0) 
		{
			printf("USB3 Reset Timed Out\n");
			ret = -ETIMEDOUT;
			goto err0;
		}
//		cpu_relax();
	}

	dwc3_core_soft_reset(dwc3);
	mdelay(100);
	reg = dwc3_readl(dwc3, DWC3_GCTL);
	reg &= ~DWC3_GCTL_SCALEDOWN_MASK;
	reg &= ~DWC3_GCTL_DISSCRAMBLE;

	switch (DWC3_GHWPARAMS1_EN_PWROPT(hwparams1)) {
	case DWC3_GHWPARAMS1_EN_PWROPT_CLK:
		reg &= ~DWC3_GCTL_DSBLCLKGTNG;
		break;
	default:
		debug("No power optimization available\n");
		break;
	}

	/*
	 * WORKAROUND: DWC3 revisions <1.90a have a bug
	 * where the device can fail to connect at SuperSpeed
	 * and falls back to high-speed mode which causes
	 * the device to enter a Connect/Disconnect loop
	 */
	if (revision < DWC3_REVISION_190A)
		reg |= DWC3_GCTL_U2RSTECN;



	dwc3_writel(dwc3, DWC3_GCTL, reg);
	mdelay(100);
	/* workaround: to avoid transaction error and cause port reset
	 * we enable threshold control for TX/RX */

	dwc3_writel(dwc3, DWC3_GTXTHRCFG, 0x01010000);
	mdelay(100);
#define RX_THRESHOLD_EN		(1<<29)
#define RX_PKT_CNT(n)		(n<<24)
#define RX_MAX_BURST_SZ(n)	(n<<19)
	dwc3_writel(dwc3, DWC3_GRXTHRCFG,  RX_THRESHOLD_EN | RX_PKT_CNT(3) | RX_MAX_BURST_SZ(3));
	mdelay(100);
	dwc3_writel(dwc3, DWC3_GUCTL,dwc3_readl(dwc3, DWC3_GUCTL) | (1<<14));   // enable auto retry
	mdelay(100);


	return 0;

err0:
	return ret;
}

int xhci_hcd_init(int index, struct xhci_hccr **hccr, struct xhci_hcor **hcor)
{
	// FIXME
	// 1. set xhci usbphy
	// 2. register mapping
	// 3. irq ?
	int ret;
	struct rtk_usb *rtkusb = get_rtkusb(index);

	*hccr = (struct xhci_hccr *)(uintptr_t) rtkusb->reg_base;
	*hcor = (struct xhci_hcor *)(uintptr_t)((uint32_t)(uintptr_t) *hccr
				+ HC_LENGTH(xhci_readl(&(*hccr)->cr_capbase)));
	debug("Realtek-xhci: init hccr %x and hcor %x hc_length %d\n",
		(uint32_t)(uintptr_t)*hccr, (uint32_t)(uintptr_t)*hcor,
		(uint32_t)HC_LENGTH(xhci_readl(&(*hccr)->cr_capbase)));

	struct ctrl_data ctrl;
	ctrl.dwc3_addr = (void *)(uintptr_t) rtkusb->reg_base + RTK_DWC3_BASE;
	ctrl.u2phy = rtkusb->usb2phy;
	ctrl.u3phy = rtkusb->usb3phy;

	debug("%s dwc3 dwc3_addr=%p\n", __func__, ctrl.dwc3_addr);

	ret = dwc3_core_init(ctrl);
	if (ret) {
		printf("failed to initialize core\n");
		return -1;
	}

	usb2_phy_switch_to_host(rtkusb->usb2phy);

	dwc3_set_mode(ctrl, DWC3_GCTL_PRTCAP_HOST);
	mdelay(100);

	debug("xhci: init hccr %x and hcor %x hc_length %d\n",
		(uint32_t)(uintptr_t)*hccr, (uint32_t)(uintptr_t)*hcor,
		(uint32_t)HC_LENGTH(xhci_readl(&(*hccr)->cr_capbase)));

	return 0;
}

void xhci_hcd_stop(int index)
{
	return;
}
