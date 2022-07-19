#include <common.h>
#include <asm/types.h>
#include <asm/arch/usb.h>
#include <dwc3-uboot.h>
#include <linux/usb/ch9.h>
#include <linux/usb/gadget.h>
#include <usb-phy.h>

#include "linux-compat.h"
#include "core.h"

static struct dwc3_device dwc3_device_data = {
	.maximum_speed = USB_SPEED_SUPER,
	.dr_mode = USB_DR_MODE_PERIPHERAL,
	.index = 0,
};

int usb_gadget_handle_interrupts(int index)
{
	dwc3_uboot_handle_interrupt(0);
	return 0;
}

void rtk_dwc3_init(u32 reg_base, struct usb2_phy *usb2phy,
        struct usb3_phy *usb3phy)
{
	dwc3_device_data.base = reg_base;

	dwc3_device_data.u2phy = usb2phy;
	dwc3_device_data.u3phy = usb3phy;

	usb2_phy_switch_to_device(usb2phy);

	dwc3_uboot_init(&dwc3_device_data);
}

void rtk_dwc3_stop(void)
{

	dwc3_uboot_exit(dwc3_device_data.index);

}
