
#include <common.h>
//#include <string.h>
//#include <stdlib.h>
#include <asm/types.h>

#include <asm/arch/usb.h>

#define DBG debug

static struct rtk_usb *rtk_usb = NULL;

#if 0
extern void rtk_otg_init(u32 reg_base, struct usb2_phy *usb2phy);
extern void rtk_otg_stop(void);
#endif

#ifdef CONFIG_USB_DWC3_RTK
extern void rtk_dwc3_init(u32 reg_base, struct usb2_phy *usb2phy,
	    struct usb3_phy *usb3phy);
extern void rtk_dwc3_stop(void);
#endif

void udc_usb_dev_init(void) {
	int count = 0;
	int i;

	rtk_usb_clock_init();

	count = rtk_usb_device_init(&rtk_usb);

	DBG("rtk_usb %p device count %d\n", rtk_usb, count);
	for (i = 0; i < count; i++) {
		struct rtk_usb *rtkusb = &rtk_usb[i];
		DBG("%d rtk_usb %p\n", i, rtkusb);
		if (rtkusb->class_type == OTG_EHCI) {
#if 0
			DBG("call rtk_otg_init\n");
			rtk_otg_init(rtkusb->reg_base, rtkusb->usb2phy);
#else
			DBG("NO support rtk_otg gadget\n");
#endif
		} else if (rtkusb->class_type == DWC3_XHCI) {
			DBG("call rtk_dwc3_init\n");
			rtk_dwc3_init(rtkusb->reg_base, rtkusb->usb2phy, rtkusb->usb3phy);
		}
	}
}

void udc_usb_dev_stop(void) {
	struct rtk_usb *rtkusb = &rtk_usb[0];
	int count = rtkusb->ctrl_count;
	int i;

	for (i = 0; i < count; i++) {
		struct rtk_usb *rtkusb = &rtk_usb[i];
		if (rtkusb->class_type == OTG_EHCI) {
#if 0
			rtk_otg_stop();
#else
			DBG("No support rtk_otg gadget");
#endif
		} else if (rtkusb->class_type == DWC3_XHCI) {
			rtk_dwc3_stop();
		}
	}

	rtk_usb_device_stop(&rtk_usb);

	rtk_usb_clock_stop();
}
