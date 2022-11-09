/* SPDX-License-Identifier: GPL-2.0 */
/*
 * USB PHY defines
 *
 * These APIs may be used between USB controllers.  USB device drivers
 * (for either host or peripheral roles) don't use these calls; they
 * continue to use just usb_device and usb_gadget.
 */

#ifndef __LINUX_USB_PHY_H
#define __LINUX_USB_PHY_H

#include <dm/ofnode.h>

enum usb_phy_interface {
	USBPHY_INTERFACE_MODE_UNKNOWN,
	USBPHY_INTERFACE_MODE_UTMI,
	USBPHY_INTERFACE_MODE_UTMIW,
};

#if CONFIG_IS_ENABLED(OF_LIVE) && CONFIG_IS_ENABLED(DM_USB)
/**
 * usb_get_phy_mode - Get phy mode for given device_node
 * @np:	Pointer to the given device_node
 *
 * The function gets phy interface string from property 'phy_type',
 * and returns the corresponding enum usb_phy_interface
 */
enum usb_phy_interface usb_get_phy_mode(ofnode node);
#else
static inline enum usb_phy_interface usb_get_phy_mode(ofnode node)
{
	return USBPHY_INTERFACE_MODE_UNKNOWN;
}
#endif

#endif /* __LINUX_USB_PHY_H */
