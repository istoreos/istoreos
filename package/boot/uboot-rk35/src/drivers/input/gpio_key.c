/*
 * (C) Copyright 2017 Rockchip Electronics Co., Ltd
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */

#include <common.h>
#include <dm.h>
#include <key.h>

static int gpio_key_ofdata_to_platdata(struct udevice *dev)
{
	struct dm_key_uclass_platdata *uc_key;

	uc_key = dev_get_uclass_platdata(dev);
	if (!uc_key)
		return -ENXIO;

	uc_key->type = GPIO_KEY;
	uc_key->name = dev_read_string(dev, "label");
	uc_key->code = dev_read_u32_default(dev, "linux,code", -ENODATA);
	if (uc_key->code < 0) {
		printf("%s: read 'linux,code' failed\n", uc_key->name);
		return -EINVAL;
	}

	if (dev_read_u32_array(dev, "gpios",
			       uc_key->gpios, ARRAY_SIZE(uc_key->gpios))) {
		printf("%s: read 'gpios' failed\n", uc_key->name);
		return -EINVAL;
	}

	return 0;
}

U_BOOT_DRIVER(gpio_key) = {
	.name   = "gpio_key",
	.id     = UCLASS_KEY,
	.ofdata_to_platdata = gpio_key_ofdata_to_platdata,
};

/* Key Bus */
static int gpio_key_bus_bind(struct udevice *dev)
{
	return key_bind_children(dev, "gpio_key");
}

static const struct udevice_id gpio_key_bus_match[] = {
	{ .compatible = "gpio-keys" },
	{ },
};

U_BOOT_DRIVER(gpio_key_bus) = {
	.name	   = "gpio_key_bus",
	.id	   = UCLASS_SIMPLE_BUS,
	.of_match  = gpio_key_bus_match,
	.bind	   = gpio_key_bus_bind,
};
