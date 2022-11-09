/*
 * (C) Copyright 2021 Rockchip Electronics Co., Ltd
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */
#include <common.h>
#include <dm.h>
#include <rng.h>

unsigned int rand_r(unsigned int *seedp)
{
	struct udevice *dev;
	unsigned int rand;
	int ret;

	ret = uclass_get_device(UCLASS_RNG, 0, &dev);
	if (ret) {
		printf("No RNG device, ret=%d\n", ret);
		return ret;
	}

	ret = dm_rng_read(dev, &rand, sizeof(unsigned int));
	if (ret) {
		printf("Reading RNG failed, ret=%d\n", ret);
		return ret;
	}

	return rand;
}

unsigned int rand(void)
{
	return rand_r(0);
}

void srand(unsigned int seed)
{
	/* nothing to do */
}

