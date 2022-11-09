// SPDX-License-Identifier:     GPL-2.0+
/*
 * Copyright (C) 2020 Rockchip Electronics Co., Ltd
 */

#include <common.h>
#include <dm.h>
#include <dm/uclass.h>
#include <misc.h>

struct udevice *misc_otp_get_device(u32 capability)
{
	return misc_get_device_by_capability(capability);
}

int misc_otp_read(struct udevice *dev, int offset, void *buf, int size)
{
	return misc_read(dev, offset, buf, size);
}

int misc_otp_write(struct udevice *dev, int offset, const void *buf, int size)
{
	return misc_write(dev, offset, (void *)buf, size);
}
