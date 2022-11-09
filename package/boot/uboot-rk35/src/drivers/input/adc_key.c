/*
 * (C) Copyright 2017 Rockchip Electronics Co., Ltd
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */

#include <common.h>
#include <dm.h>
#include <key.h>

static int adc_key_ofdata_to_platdata(struct udevice *dev)
{
	struct dm_key_uclass_platdata *uc_key;
	u32 chn[2], mV;
	int vref, ret;
#ifdef CONFIG_SARADC_ROCKCHIP_V2
	int range = 4096;	/* 12-bit adc */
#else
	int range = 1024;	/* 10-bit adc */
#endif

	uc_key = dev_get_uclass_platdata(dev);
	if (!uc_key)
		return -ENXIO;

	uc_key->type = ADC_KEY;
	uc_key->name = dev_read_string(dev, "label");
	ret = dev_read_u32_array(dev_get_parent(dev),
				 "io-channels", chn, ARRAY_SIZE(chn));
	if (ret) {
		printf("%s: read 'io-channels' failed, ret=%d\n",
		       uc_key->name, ret);
		return -EINVAL;
	}

	vref = dev_read_u32_default(dev_get_parent(dev),
				    "keyup-threshold-microvolt", -ENODATA);
	if (vref < 0) {
		printf("%s: read 'keyup-threshold-microvolt' failed, ret=%d\n",
		       uc_key->name, vref);
		return -EINVAL;
	}

	uc_key->code = dev_read_u32_default(dev, "linux,code", -ENODATA);
	if (uc_key->code < 0) {
		printf("%s: read 'linux,code' failed\n", uc_key->name);
		return -EINVAL;
	}

	mV = dev_read_u32_default(dev, "press-threshold-microvolt", -ENODATA);
	if (mV < 0) {
		printf("%s: read 'press-threshold-microvolt' failed\n",
		       uc_key->name);
		return -EINVAL;
	}

	uc_key->channel = chn[1];
	uc_key->adcval = mV / (vref / range);

	return 0;
}

U_BOOT_DRIVER(adc_key) = {
	.name   = "adc_key",
	.id     = UCLASS_KEY,
	.ofdata_to_platdata = adc_key_ofdata_to_platdata,
};

/* Key Bus */
static int adc_key_bus_bind(struct udevice *dev)
{
	return key_bind_children(dev, "adc_key");
}

static const struct udevice_id adc_key_bus_match[] = {
	{ .compatible = "adc-keys" },
	{ },
};

U_BOOT_DRIVER(adc_key_bus) = {
	.name	   = "adc_key_bus",
	.id	   = UCLASS_SIMPLE_BUS,
	.of_match  = adc_key_bus_match,
	.bind	   = adc_key_bus_bind,
};
