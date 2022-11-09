// SPDX-License-Identifier:     GPL-2.0+
/*
 * (C) Copyright 2018 Rockchip Electronics Co., Ltd
 */

#include <common.h>
#include <console.h>
#include <io-domain.h>

int io_domain_init(void)
{
	struct udevice *dev;
	struct uclass *uc;
	int ret;

	ret = uclass_get(UCLASS_IO_DOMAIN, &uc);
	if (ret)
		return ret;

	for (uclass_first_device(UCLASS_IO_DOMAIN, &dev);
	     dev;
	     uclass_next_device(&dev))
		;

	printf("io-domain: OK\n");

	return 0;
}

UCLASS_DRIVER(io_domain) = {
	.id		= UCLASS_IO_DOMAIN,
	.name		= "io_domain",
};
