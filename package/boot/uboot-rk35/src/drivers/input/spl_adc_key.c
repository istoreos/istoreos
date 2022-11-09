/*
 * (C) Copyright 2020 Rockchip Electronics Co., Ltd
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */

#include <common.h>
#include <adc.h>
#include <fdtdec.h>

DECLARE_GLOBAL_DATA_PTR;

int key_read(int code)
{
	const void *fdt_blob = gd->fdt_blob;
	int adc_node, offset;
	int cd, channel, adc;
	int ret, vref, mv;
	int min, max;
	int margin;
	int range;
	uint val;
	u32 chn[2];
#ifdef CONFIG_SARADC_ROCKCHIP_V2
	range = 4096;	/* 12-bit adc */
	margin = 120;
#else
	range = 1024;	/* 10-bit adc */
	margin = 30;
#endif
	adc_node = fdt_node_offset_by_compatible(fdt_blob, 0, "adc-keys");
	if (adc_node < 0) {
		debug("No 'adc-keys' node, ret=%d\n", adc_node);
		return 0;
	}

	ret = fdtdec_get_int_array(fdt_blob, adc_node, "io-channels",
				   chn, ARRAY_SIZE(chn));
	if (ret) {
		debug("Can't read 'io-channels', ret=%d\n", ret);
		return 0;
	}

	vref = fdtdec_get_int(fdt_blob, adc_node,
			      "keyup-threshold-microvolt", -1);
	if (vref < 0) {
		debug("Can't read 'keyup-threshold-microvolt'\n");
		return 0;
	}

	channel = chn[1];

	for (offset = fdt_first_subnode(fdt_blob, adc_node);
	     offset >= 0;
	     offset = fdt_next_subnode(fdt_blob, offset)) {
		cd = fdtdec_get_int(fdt_blob, offset, "linux,code", -1);
		if (cd == code) {
			mv = fdtdec_get_int(fdt_blob, offset,
					    "press-threshold-microvolt", -1);
			if (mv < 0) {
				debug("Can't read 'press-threshold-microvolt'\n");
				return 0;
			}

			adc = mv / (vref / range);
			max = adc + margin;
			min = adc > margin ? adc - margin : 0;
			ret = adc_channel_single_shot("saradc", channel, &val);
			if (ret) {
				debug("Failed to read adc%d, ret=%d\n",
				      channel, ret);
				return 0;
			}

			return (val >= min && val <= max);
		}
	}

	return 0;
}
