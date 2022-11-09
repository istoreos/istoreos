// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (C) 2018 Texas Instruments Incorporated - http://www.ti.com
 * Written by Jean-Jacques Hiblot <jjhiblot@ti.com>
 */

#include <common.h>
#include <dm.h>
#include <dm/device-internal.h>
#include <linux/usb/gadget.h>

#if CONFIG_IS_ENABLED(DM_USB_GADGET)
#define MAX_UDC_DEVICES 4
static struct udevice *dev_array[MAX_UDC_DEVICES];
int usb_gadget_initialize(int index)
{
	int ret;
	struct udevice *dev = NULL;

	if (index < 0 || index >= ARRAY_SIZE(dev_array))
		return -EINVAL;
	if (dev_array[index])
		return 0;
	ret = uclass_get_device_by_seq(UCLASS_USB_GADGET_GENERIC, index, &dev);
	if (!dev || ret) {
		ret = uclass_get_device(UCLASS_USB_GADGET_GENERIC, index, &dev);
		if (!dev || ret) {
			pr_err("No USB device found\n");
			return -ENODEV;
		}
	}
	dev_array[index] = dev;
	return 0;
}

int usb_gadget_release(int index)
{
#if CONFIG_IS_ENABLED(DM_DEVICE_REMOVE)
	int ret;
	if (index < 0 || index >= ARRAY_SIZE(dev_array))
		return -EINVAL;

	ret = device_remove(dev_array[index], DM_REMOVE_NORMAL);
	if (!ret)
		dev_array[index] = NULL;
	return ret;
#else
	return -ENOTSUPP;
#endif
}

int usb_gadget_handle_interrupts(int index)
{
	if (index < 0 || index >= ARRAY_SIZE(dev_array))
		return -EINVAL;
	return dm_usb_gadget_handle_interrupts(dev_array[index]);
}
#endif

UCLASS_DRIVER(usb_gadget_generic) = {
	.id		= UCLASS_USB_GADGET_GENERIC,
	.name		= "usb",
	.flags		= DM_UC_FLAG_SEQ_ALIAS,
};
