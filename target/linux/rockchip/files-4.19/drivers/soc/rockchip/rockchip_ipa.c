// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (c) 2018 Fuzhou Rockchip Electronics Co., Ltd
 */
#include <linux/kernel.h>
#include <linux/of.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/thermal.h>
#include <soc/rockchip/rockchip_ipa.h>
#include <soc/rockchip/rockchip_opp_select.h>
#include <trace/events/thermal.h>

#define CREATE_TRACE_POINTS
#include <trace/events/thermal_ipa_power.h>

#define FALLBACK_STATIC_TEMPERATURE 55000

static void calculate_static_coefficient(struct ipa_power_model_data *data)
{
	s32 *ls = data->ls;
	u32 lkg = data->leakage;
	u32 ref_lkg = data->ref_leakage;
	u32 min = data->lkg_range[0], max = data->lkg_range[1];
	u32 static_coeff = data->static_coefficient;
	u32 lkg_scaling_factor;

	if (!lkg) {
		if (ref_lkg)
			lkg = ref_lkg;
		else
			lkg = (min + max) / 2;
	}
	if (ref_lkg) {
		data->static_coefficient = static_coeff * lkg / ref_lkg;
		return;
	}
	if (lkg < min)
		lkg = min;
	if (lkg > max)
		lkg = max;
	/* As ts have beed multiplied by 1000 in devicetree */
	lkg_scaling_factor = (ls[2] * lkg * lkg + ls[1] * lkg + ls[0]) / 1000;
	data->static_coefficient = static_coeff * lkg_scaling_factor / 100;
}

/**
 * rockchip_ipa_power_model_init() - initialise ipa power model parameter
 * @dev:	device for which we do this operation
 * @lkg_name:	nvmem cell name from nvmem-cell-names property
 *
 * Return: a valid struct ipa_power_model_data pointer on success, and the onwer
 * should use kfree to release the memory by itself. on failure, it returns a
 * corresponding ERR_PTR().
 */
struct ipa_power_model_data *rockchip_ipa_power_model_init(struct device *dev,
							   char *lkg_name)
{
	struct device_node *model_node;
	struct ipa_power_model_data *model_data;
	const char *tz_name;
	int ret;

	model_data = kzalloc(sizeof(*model_data), GFP_KERNEL);
	if (!model_data)
		return ERR_PTR(-ENOMEM);

	model_node = of_get_compatible_child(dev->of_node,
					     "simple-power-model");
	if (!model_node) {
		dev_err(dev, "failed to find power_model node\n");
		ret = -ENODEV;
		goto err;
	}

	if (of_property_read_string(model_node, "thermal-zone", &tz_name)) {
		dev_err(dev, "ts in power_model not available\n");
		ret = -EINVAL;
		goto err;
	}
	model_data->tz = thermal_zone_get_zone_by_name(tz_name);
	if (IS_ERR_OR_NULL(model_data->tz)) {
		dev_err(dev, "failed to get thermal zone\n");
		model_data->tz = NULL;
		ret = -EPROBE_DEFER;
		goto err;
	}
	if (of_property_read_u32(model_node, "static-coefficient",
				 &model_data->static_coefficient)) {
		dev_err(dev, "static-coefficient not available\n");
		ret = -EINVAL;
		goto err;
	}
	/* cpu power model node doesn't contain dynamic-coefficient */
	of_property_read_u32(model_node, "dynamic-coefficient",
			     &model_data->dynamic_coefficient);
	if (of_property_read_u32_array
	    (model_node, "ts", (u32 *)model_data->ts, 4)) {
		dev_err(dev, "ts in power_model not available\n");
		ret = -EINVAL;
		goto err;
	}
	rockchip_of_get_leakage(dev, lkg_name, &model_data->leakage);
	if (!of_property_read_u32(model_node, "ref-leakage",
				&model_data->ref_leakage))
		goto cal_static_coeff;
	if (of_property_read_u32_array(model_node, "leakage-range",
				       (u32 *)model_data->lkg_range, 2)) {
		dev_err(dev, "leakage-range isn't available\n");
		ret = -EINVAL;
		goto err;
	}
	if (of_property_read_u32_array(model_node, "ls",
				       (u32 *)model_data->ls, 3)) {
		dev_err(dev, "ls isn't available\n");
		ret = -EINVAL;
		goto err;
	}
cal_static_coeff:
	calculate_static_coefficient(model_data);

	of_node_put(model_node);

	return model_data;
err:
	of_node_put(model_node);
	kfree(model_data);

	return ERR_PTR(ret);
}
EXPORT_SYMBOL(rockchip_ipa_power_model_init);

/**
 * calculate_temp_scaling_factor() - Calculate temperature scaling coefficient
 * @ts:		Signed coefficients, in order t^0 to t^3, with units Deg^-N
 * @t:		Temperature, in mDeg C. Range: -40000 < t < 125000
 *
 * Scale the temperature according to a cubic polynomial whose coefficients are
 * provided in the device tree. The result is used to scale the static power
 * coefficient, where 1000000 means no change.
 *
 * Return: Temperature scaling factor.
 */
static u32 calculate_temp_scaling_factor(s32 ts[4], s64 t)
{
	const s64 t2 = div_s64((t * t), 1000);

	const s64 t3 = div_s64((t * t2), 1000);

	/*
	 * Sum the parts. t^[1-3] are in m(Deg^N), but the coefficients are in
	 * Deg^-N, so we need to multiply the last coefficient by 1000.
	 */
	const s64 res_big = ts[3] * t3
			  + ts[2] * t2
			  + ts[1] * t
			  + ts[0] * 1000LL;

	/* ts has beed multiplied by 10 in devicetree */
	s64 res_unclamped = div_s64(res_big, 10000);

	/* Clamp to range of 0x to 10x the static power */
	return clamp(res_unclamped, (s64)0, (s64)10000000);
}

/**
 * calculate_volt_scaling_factor() - Calculate voltage scaling coefficient
 * voltage_mv:	Voltage, in mV. Range: 750 < voltage < 1350
 *
 * Return: Voltage scaling factor.
 */
static u32 calculate_volt_scaling_factor(const u32 voltage_mv)
{
	const u32 v2 = (voltage_mv * voltage_mv) / 1000;

	const u32 v3_big = v2 * voltage_mv;

	const u32 v3 = v3_big / 1000;

	const u32 v4_big = v3 * voltage_mv;

	const u32 v4 = v4_big / 1000;

	return v4;
}

/**
 * rockchip_ipa_get_static_power() - Calculate static power
 * @data:	Pointer to IPA model
 * voltage_mv:	Voltage, in mV. Range: 750 < voltage < 1350
 *
 * Return: Static power.
 */
unsigned long
rockchip_ipa_get_static_power(struct ipa_power_model_data *data,
			      unsigned long voltage_mv)
{
	u32 temp_scaling_factor, volt_scaling_factor, static_power;
	u64 power_big;
	int temp;
	int ret;

	ret = data->tz->ops->get_temp(data->tz, &temp);
	if (ret) {
		pr_err("%s:failed to read %s temp\n",
		       __func__, data->tz->type);
		temp = FALLBACK_STATIC_TEMPERATURE;
	}

	temp_scaling_factor = calculate_temp_scaling_factor(data->ts, temp);
	volt_scaling_factor = calculate_volt_scaling_factor((u32)voltage_mv);

	power_big = (u64)data->static_coefficient * (u64)temp_scaling_factor;
	static_power = div_u64(power_big, 1000000);
	power_big = (u64)static_power * (u64)volt_scaling_factor;
	static_power = div_u64(power_big, 1000000);

	trace_thermal_ipa_get_static_power(data->leakage,
					   data->static_coefficient,
					   temp,
					   temp_scaling_factor,
					   (u32)voltage_mv,
					   volt_scaling_factor,
					   static_power);

	return static_power;
}
EXPORT_SYMBOL(rockchip_ipa_get_static_power);

MODULE_DESCRIPTION("Rockchip IPA driver");
MODULE_AUTHOR("Finley Xiao <finley.xiao@rock-chips.com>");
MODULE_LICENSE("GPL");
