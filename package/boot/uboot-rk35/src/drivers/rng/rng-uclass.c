// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (c) 2019, Linaro Limited
 */

#include <common.h>
#include <dm.h>
#include <rng.h>

int dm_rng_read(struct udevice *dev, void *buffer, size_t size)
{
	const struct dm_rng_ops *ops = device_get_ops(dev);

	if (!ops->read)
		return -ENOSYS;

	return ops->read(dev, buffer, size);
}

UCLASS_DRIVER(rng) = {
	.name = "rng",
	.id = UCLASS_RNG,
};
