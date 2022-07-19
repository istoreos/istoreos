/*
 * SAMSUNG EXYNOS USB HOST EHCI Controller
 *
 * Copyright (C) 2012 Samsung Electronics Co.Ltd
 *	Vivek Gautam <gautam.vivek@samsung.com>
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

#include <common.h>
#include <usb.h>
#include <usb-phy.h>
#include <asm/arch/usb.h>

#include "ehci.h"
#include "host-rtk.h"

#if 0
/* Reset the EHCI host controller. */
static void reset_usb_phy(void)
{
	/* HOST_PHY reset */
	setbits_le32(&usb->usbphyctrl0,
			HOST_CTRL0_PHYSWRST |
			HOST_CTRL0_PHYSWRSTALL |
			HOST_CTRL0_SIDDQ |
			HOST_CTRL0_FORCESUSPEND |
			HOST_CTRL0_FORCESLEEP);

	set_usbhost_phy_ctrl(POWER_USB_HOST_PHY_CTRL_DISABLE);
}
#endif

/*
 * EHCI-initialization
 * Create the appropriate control structures to manage
 * a new EHCI host controller.
 */
int ehci_hcd_init(int index, enum usb_init_type init, struct ehci_hccr **hccr, struct ehci_hcor **hcor)
{
	struct rtk_usb *rtkusb = get_rtkusb(index);

	usb2_phy_init(rtkusb->usb2phy);

	*hccr = (struct ehci_hccr *)(uintptr_t) rtkusb->reg_base;
	*hcor = (struct ehci_hcor *)(uintptr_t)((uint32_t)(uintptr_t) *hccr
				+ HC_LENGTH(ehci_readl(&(*hccr)->cr_capbase)));

	debug("Realtek-ehci: init hccr %x and hcor %x hc_length %d\n",
		(uint32_t)(uintptr_t)*hccr, (uint32_t)(uintptr_t)*hcor,
		(uint32_t)HC_LENGTH(ehci_readl(&(*hccr)->cr_capbase)));

	return 0;
}

/*
 * Destroy the appropriate control structures corresponding
 * the EHCI host controller.
 */
int ehci_hcd_stop(int index)
{

	return 0;
}
