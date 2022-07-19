#include <common.h>
#include <stdlib.h>
#include <linux/string.h>

#include <usb.h>
#include <asm/arch/usb.h>
#include "ehci.h"
#include <errno.h>
//# "xhci.h"

static struct rtk_usb *rtk_usb = NULL;

#ifdef CONFIG_USB_EHCI
extern int ehci_lowlevel_init(int index, enum usb_init_type init,
	    void **controller);
extern int ehci_lowlevel_stop(int index);
extern int ehci_submit_int_msg(struct usb_device *udev,
	    unsigned long pipe, void *buffer,
	    int length, int interval);
extern int ehci_submit_bulk_msg(struct usb_device *udev,
	    unsigned long pipe, void *buffer,
	    int length);
extern int ehci_submit_control_msg(struct usb_device *udev,
	    unsigned long pipe, void *buffer,
	    int length, struct devrequest *setup);
#else
int ehci_lowlevel_init(int index, enum usb_init_type init,
	    void **controller) {return 0;}
int ehci_lowlevel_stop(int index) {return 0;}
int ehci_submit_int_msg(struct usb_device *udev,
	    unsigned long pipe, void *buffer,
	    int length, int interval) {return 0;}
int ehci_submit_bulk_msg(struct usb_device *udev,
	    unsigned long pipe, void *buffer,
	    int length) {return 0;}
int ehci_submit_control_msg(struct usb_device *udev,
	    unsigned long pipe, void *buffer,
	    int length, struct devrequest *setup) {return 0;}

#endif

#ifdef CONFIG_USB_XHCI
extern int xhci_to_lowlevel_init(int index,
	    enum usb_init_type init, void **controller);
extern int xhci_to_lowlevel_stop(int index);
extern int xhci_submit_int_msg(struct usb_device *udev,
	    unsigned long pipe, void *buffer,
	    int length, int interval);
extern int xhci_submit_bulk_msg(struct usb_device *udev,
	    unsigned long pipe, void *buffer,
	    int length);
extern int xhci_submit_control_msg(struct usb_device *udev,
	    unsigned long pipe, void *buffer,
	    int length, struct devrequest *setup);
extern int xhci_alloc_device(struct usb_device *udev);
extern void xhci_release_device(struct usb_device *udev);
#else
int xhci_to_lowlevel_init(int index, enum usb_init_type init,
	    void **controller) {return 0;}
int xhci_to_lowlevel_stop(int index) {return 0;}
int xhci_submit_int_msg(struct usb_device *udev,
	    unsigned long pipe, void *buffer,
	    int length, int interval) {return 0;}
int xhci_submit_bulk_msg(struct usb_device *udev,
	    unsigned long pipe, void *buffer,
	    int length) {return 0;}
int xhci_submit_control_msg(struct usb_device *udev,
	    unsigned long pipe, void *buffer,
	    int length, struct devrequest *setup) {return 0;}
int xhci_alloc_device(struct usb_device *udev) { return 0;}
void xhci_release_device(struct usb_device *udev) { return;}
#endif

int
submit_int_msg(struct usb_device *udev, unsigned long pipe, void *buffer,
						int length, int interval)
{
	struct controller *ctrl= udev->controller;
	int ctrl_type = ctrl->ctrl_type;
	if (ctrl_type == CTRL_TYPE_EHCI) {
		return ehci_submit_int_msg(udev, pipe, buffer, length, interval);
	} else if (ctrl_type == CTRL_TYPE_XHCI) {
		return xhci_submit_int_msg(udev, pipe, buffer, length, interval);
	} else {
		return -EINVAL;
	}
}

int
submit_bulk_msg(struct usb_device *udev, unsigned int pipe, void *buffer,
								int length)
{
	struct controller *ctrl= udev->controller;
	int ctrl_type = ctrl->ctrl_type;
	if (ctrl_type == CTRL_TYPE_EHCI) {
		return ehci_submit_bulk_msg(udev, pipe, buffer, length);
	} else if (ctrl_type == CTRL_TYPE_XHCI) {
		return xhci_submit_bulk_msg(udev, pipe, buffer, length);
	} else {
		return -EINVAL;
	}
}

int
submit_control_msg(struct usb_device *udev, unsigned int pipe, void *buffer,
					int length, struct devrequest *setup)
{
	struct controller *ctrl= udev->controller;
	int ctrl_type = ctrl->ctrl_type;
	if (ctrl_type == CTRL_TYPE_EHCI) {
		return ehci_submit_control_msg(udev, pipe, buffer, length, setup);
	} else if (ctrl_type == CTRL_TYPE_XHCI) {
		return xhci_submit_control_msg(udev, pipe, buffer, length, setup);
	} else {
		return -EINVAL;
	}
}

void usb_release_device(struct usb_device *udev) {
	struct controller *ctrl= udev->controller;
	int ctrl_type = ctrl->ctrl_type;
	if (ctrl_type == CTRL_TYPE_EHCI) {
		/*Note EHCI no use this function*/
		return;
	} else if (ctrl_type == CTRL_TYPE_XHCI) {
		xhci_release_device(udev);
	}

}

int usb_alloc_device(struct usb_device *udev) {
	struct controller *ctrl= udev->controller;
	int ctrl_type = ctrl->ctrl_type;
	if (ctrl_type == CTRL_TYPE_EHCI) {
		/*Note EHCI no use this function*/
		return 0;
	} else if (ctrl_type == CTRL_TYPE_XHCI) {
		return xhci_alloc_device(udev);
	} else {
		return -EINVAL;
	}

}

struct rtk_usb *get_rtkusb(int index)
{
	struct rtk_usb *rtkusb = &rtk_usb[0];
	int max_host_count = rtkusb->ctrl_count;

	if (index > max_host_count) {
		printf("%s index %d > max_host_count %d\n",
			    __func__, index, max_host_count);
		return NULL;
	}

	return &rtk_usb[index];
}

int usb_lowlevel_stop_all(void)
{
	/* Stop all host */
	struct rtk_usb *rtkusb = get_rtkusb(0);
	int max_count = rtkusb->ctrl_count;
	int i;
	int ret = 0;
	for (i = 0; i < max_count; i++) {
		rtkusb = get_rtkusb(i);
		if (rtkusb && rtkusb->class_type == OTG_EHCI) {
			ret = ehci_lowlevel_stop(i);
		} else if (rtkusb && rtkusb->class_type == DWC3_XHCI) {
			ret = xhci_to_lowlevel_stop(i);
		} else
			/* error case*/
			ret = -1;
	}
	return ret;
}

int usb_lowlevel_init(int index, enum usb_init_type init, void **controller)
{
	struct rtk_usb *rtkusb = get_rtkusb(index);
	int ret = 0;

	if (rtkusb && rtkusb->class_type == OTG_EHCI) {
		ret = ehci_lowlevel_init(index, init, controller);
	} else if (rtkusb && rtkusb->class_type == DWC3_XHCI) {
		ret = xhci_to_lowlevel_init(index, init, controller);
	} else {
		/* error case*/
		ret = -1;
	}
	return ret;
}

int usb_host_controller_init(void)
{
	int host_count = 0;

	rtk_usb_clock_init();

	rtk_usb_power_on();

	host_count = rtk_usb_host_init(&rtk_usb);

	return host_count;
}
