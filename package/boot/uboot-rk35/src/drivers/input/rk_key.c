/*
 * (C) Copyright 2017 Rockchip Electronics Co., Ltd
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */

#include <common.h>
#include <dm.h>
#include <key.h>

static int rk_key_ofdata_to_platdata(struct udevice *dev)
{
	struct dm_key_uclass_platdata *uc_key;
	u32 chn[2];

	uc_key = dev_get_uclass_platdata(dev);
	if (!uc_key)
		return -ENXIO;

	uc_key->name = dev_read_string(dev, "label");
	uc_key->code = dev_read_u32_default(dev, "linux,code", -ENODATA);

	if (dev_read_u32_array(dev_get_parent(dev), "io-channels", chn, 2)) {
		printf("%s: read 'io-channels' failed\n", uc_key->name);
		return -EINVAL;
	}

	if (dev_read_bool(dev, "rockchip,adc_value")) {
		uc_key->type = ADC_KEY;
		uc_key->channel = chn[1];
		uc_key->adcval =
			dev_read_u32_default(dev, "rockchip,adc_value", 0);
	} else {
		uc_key->type = GPIO_KEY;
		if (dev_read_u32_array(dev, "gpios",
				       uc_key->gpios,
				       ARRAY_SIZE(uc_key->gpios))) {
			printf("%s: read 'gpios' failed\n", uc_key->name);
			return -EINVAL;
		}
	}

	return 0;
}

U_BOOT_DRIVER(rk_key) = {
	.name     = "rk_key",
	.id       = UCLASS_KEY,
	.ofdata_to_platdata = rk_key_ofdata_to_platdata,
};

/* Key Bus */
static int rk_key_bus_bind(struct udevice *dev)
{
	return key_bind_children(dev, "rk_key");
}

static const struct udevice_id rk_key_bus_match[] = {
	{ .compatible = "rockchip,key" },
	{ },
};

U_BOOT_DRIVER(rk_key_bus) = {
	.name	   = "rk_key_bus",
	.id	   = UCLASS_SIMPLE_BUS,
	.of_match  = rk_key_bus_match,
	.bind	   = rk_key_bus_bind,
};
