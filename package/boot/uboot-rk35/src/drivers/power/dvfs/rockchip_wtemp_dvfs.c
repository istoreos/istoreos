// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (c) 2018 Fuzhou Rockchip Electronics Co., Ltd
 */
#include <common.h>
#include <dm.h>
#include <clk.h>
#include <dvfs.h>
#include <thermal.h>
#include <linux/list.h>

#include <asm/arch-rockchip/clock.h>
#include <power/regulator.h>
#ifdef CONFIG_ROCKCHIP_DMC
#include <asm/arch-rockchip/rockchip_dmc.h>
#endif

/*
 * # This is a simple wide temperature(ie. wtemp) dvfs driver, the policy is:
 *
 * 1. U-Boot parse cpu/dmc opp table from kernel dtb, anyone of
 *    "rockchip,low-temp = <...>" and "rockchip,high-temp = <...>" present in
 *    cpu/dmc nodes means wtemp is enabled.
 *
 *    1.1. When temperature trigger "rockchip,low-temp", increase 50mv voltage
 *         as target voltage. If target voltage is over "rockchip,max-volt",
 *         just set "rockchip,max-volt" as target voltage and lower 2 level freq,
 *
 *    1.2. When temperature trigger "rockchip,high-temp", just apply opp table[0]
 *         voltage and freq.
 *
 * 2. U-Boot parse cpu/dmc thermal zone "trip-point-0" temperature from kernel
 *    dtb, and apply the same rules as above [1.2] policy.
 *
 *
 * # The dvfs policy apply moment is:
 *
 * 1. Appy it after clk and regulator drivers setup;
 * 2. Repeat apply it by CONFIG_PREBOOT command until achieve the target
 *    temperature. user should add: #define CONFIG_PREBOOT "dvfs repeat" and
 *    assign repeat property in dts:
 *
 *	uboot-wide-temperature {
 *		status = "okay";
 *		compatible = "rockchip,uboot-wide-temperature";
 *
 *		cpu,low-temp-repeat;
 *		cpu,high-temp-repeat;
 *		dmc,low-temp-repeat;
 *		dmc,high-temp-repeat;
 *	};
 */

#define FDT_PATH_CPUS		"/cpus"
#define FDT_PATH_DMC		"/dmc"
#define FDT_PATH_THREMAL_TRIP_POINT0	\
	"/thermal-zones/soc-thermal/trips/trip-point-0"
#define FDT_PATH_THREMAL_COOLING_MAPS	\
	"/thermal-zones/soc-thermal/cooling-maps"

#define OPP_TABLE_MAX		20
#define RATE_LOWER_LEVEL_N	2
#define DIFF_VOLTAGE_UV		50000
#define TEMP_STRING_LEN		12
#define REPEAT_PERIOD_US	1000000

static LIST_HEAD(pm_e_head);

enum pm_id {
	PM_CPU,
	PM_DMC,
};

enum pm_event {
	PM_EVT_NONE = 0x0,
	PM_EVT_LOW  = 0x1,
	PM_EVT_HIGH = 0x2,
	PM_EVT_BOTH = PM_EVT_LOW | PM_EVT_HIGH,
};

struct opp_table {
	u64 hz;
	u32 uv;
};

struct lmt_param {
	int low_temp;		/* milli degree */
	int high_temp;		/* milli degree */
	int tz_temp;		/* milli degree */
	int max_volt;		/* uV */

	bool htemp_repeat;
	bool ltemp_repeat;

	bool ltemp_limit;
	bool htemp_limit;
	bool tztemp_limit;
};

struct pm_element {
	int id;
	const char *name;
	const char *supply_name;
	int volt_diff;
	u32 opp_nr;
	struct opp_table opp[OPP_TABLE_MAX];
	struct lmt_param lmt;
	struct udevice *supply;
	struct clk clk;
	struct list_head node;
};

struct wtemp_dvfs_priv {
	struct udevice *thermal;
	struct pm_element *cpu;
	struct pm_element *dmc;
};

static struct pm_element pm_cpu = {
	.id		= PM_CPU,
	.name		= "cpu",
	.supply_name	= "cpu-supply",
	.volt_diff	= DIFF_VOLTAGE_UV,
};

static struct pm_element pm_dmc = {
	.id		= PM_DMC,
	.name		= "dmc",
	.supply_name	= "center-supply",
	.volt_diff	= DIFF_VOLTAGE_UV,
};

static void temp2string(int temp, char *data, int len)
{
	int decimal_point;
	int integer;

	integer = abs(temp) / 1000;
	decimal_point = abs(temp) % 1000;
	snprintf(data, len, "%s%d.%d",
		 temp < 0 ? "-" : "", integer, decimal_point);
}

static ulong wtemp_get_lowlevel_rate(ulong rate, u32 level,
				     struct pm_element *e)
{
	struct opp_table *opp;
	int i, count, idx = 0;

	opp = e->opp;
	count = e->opp_nr;

	for (i = 0; i < count; i++) {
		if (opp[i].hz >= rate) {
			idx = (i <= level) ? 0 : i - level;
			break;
		}
	}

	return opp[idx].hz;
}

static ulong __wtemp_clk_get_rate(struct pm_element *e)
{
#ifdef CONFIG_ROCKCHIP_DMC
	if (e->id == PM_DMC)
		return rockchip_ddrclk_sip_recalc_rate_v2();
#endif
	return clk_get_rate(&e->clk);
}

static ulong __wtemp_clk_set_rate(struct pm_element *e, ulong rate)
{
#ifdef CONFIG_ROCKCHIP_DMC
	if (e->id == PM_DMC) {
		rate = rockchip_ddrclk_sip_round_rate_v2(rate);
		rockchip_ddrclk_sip_set_rate_v2(rate);
	} else
#endif
		clk_set_rate(&e->clk, rate);

	return rate;
}

static int __wtemp_regulator_get_value(struct pm_element *e)
{
	return regulator_get_value(e->supply);
}

static int __wtemp_regulator_set_value(struct pm_element *e, int value)
{
	return regulator_set_value(e->supply, value);
}

/*
 * Policy: Increase voltage
 *
 * 1. target volt = original volt + diff volt;
 * 2. If target volt is not over max_volt, just set it;
 * 3. Otherwise set max_volt as target volt and lower the rate(front N level).
 */
static void wtemp_dvfs_low_temp_adjust(struct udevice *dev, struct pm_element *e)
{
	struct wtemp_dvfs_priv *priv = dev_get_priv(dev);
	ulong org_rate, tgt_rate, rb_rate;
	int org_volt, tgt_volt, rb_volt;

	org_rate = __wtemp_clk_get_rate(e);
	org_volt = __wtemp_regulator_get_value(e);
	tgt_volt = org_volt + e->volt_diff;
	if ((e->lmt.max_volt != -ENODATA) && (tgt_volt > e->lmt.max_volt)) {
		tgt_volt = e->lmt.max_volt;
		__wtemp_regulator_set_value(e, tgt_volt);
		tgt_rate = wtemp_get_lowlevel_rate(org_rate,
						RATE_LOWER_LEVEL_N, priv->cpu);
		tgt_rate = __wtemp_clk_set_rate(e, tgt_rate);
	} else {
		__wtemp_regulator_set_value(e, tgt_volt);
		tgt_rate = org_rate;
	}

	/* Check */
	rb_rate = __wtemp_clk_get_rate(e);
	rb_volt = __wtemp_regulator_get_value(e);
	if (tgt_rate != rb_rate)
		printf("DVFS: %s: target rate=%ld, readback rate=%ld !\n",
		       e->name, tgt_rate, rb_rate);
	if (tgt_volt != rb_volt)
		printf("DVFS: %s: target volt=%d, readback volt=%d !\n",
		       e->name, tgt_volt, rb_volt);

	printf("DVFS: %s(low): %ld->%ld Hz, %d->%d uV\n",
	       e->name, org_rate, rb_rate, org_volt, rb_volt);
}

/*
 * Policy:
 *
 * Just set opp table[0] volt and rate, i.e. the lowest performance.
 */
static void wtemp_dvfs_high_temp_adjust(struct udevice *dev, struct pm_element *e)
{
	ulong org_rate, tgt_rate, rb_rate;
	int org_volt, tgt_volt, rb_volt;

	/* Apply opp[0] */
	org_rate = __wtemp_clk_get_rate(e);
	tgt_rate = e->opp[0].hz;
	tgt_rate = __wtemp_clk_set_rate(e, tgt_rate);

	org_volt = __wtemp_regulator_get_value(e);
	tgt_volt = e->opp[0].uv;
	__wtemp_regulator_set_value(e, tgt_volt);

	/* Check */
	rb_rate = __wtemp_clk_get_rate(e);
	rb_volt = __wtemp_regulator_get_value(e);
	if (tgt_rate != rb_rate)
		printf("DVFS: %s: target rate=%ld, readback rate=%ld !\n",
		       e->name, tgt_rate, rb_rate);
	if (tgt_volt != rb_volt)
		printf("DVFS: %s: target volt=%d, readback volt=%d !\n",
		       e->name, tgt_volt, rb_volt);

	printf("DVFS: %s(high): %ld->%ld Hz, %d->%d uV\n",
	       e->name, org_rate, tgt_rate, org_volt, tgt_volt);
}

static bool wtemp_dvfs_is_effect(struct pm_element *e,
				 int temp, enum pm_event evt)
{
	if (evt & PM_EVT_LOW) {
		if (e->lmt.ltemp_limit && temp <= e->lmt.low_temp)
			return false;
	}

	if (evt & PM_EVT_HIGH) {
		if (e->lmt.tztemp_limit && temp >= e->lmt.tz_temp)
			return false;
		else if (e->lmt.htemp_limit && temp >= e->lmt.high_temp)
			return false;
	}

	return true;
}

static int __wtemp_dvfs_apply(struct udevice *dev, struct pm_element *e,
			      int temp, enum pm_event evt)
{
	enum pm_event ret = PM_EVT_NONE;

	if (evt & PM_EVT_LOW) {
		/* Over lowest temperature: increase voltage */
		if (e->lmt.ltemp_limit && temp <= e->lmt.low_temp) {
			ret |= PM_EVT_LOW;
			wtemp_dvfs_low_temp_adjust(dev, e);
		}
	}

	if (evt & PM_EVT_HIGH) {
		/* Over highest/thermal_zone temperature: decrease rate and voltage */
		if (e->lmt.tztemp_limit && temp >= e->lmt.tz_temp) {
			ret |= PM_EVT_HIGH;
			wtemp_dvfs_high_temp_adjust(dev, e);
		} else if (e->lmt.htemp_limit && temp >= e->lmt.high_temp) {
			ret |= PM_EVT_HIGH;
			wtemp_dvfs_high_temp_adjust(dev, e);
		}
	}

	return ret;
}

static int __wtemp_common_ofdata_to_platdata(ofnode node, struct pm_element *e)
{
	ofnode supply, opp_node;
	u32 phandle, uv, clock[2];
	uint64_t hz;
	int ret;

	/* Get regulator and clk */
	if (!ofnode_read_u32(node, e->supply_name, &phandle)) {
		supply = ofnode_get_by_phandle(phandle);
		ret = regulator_get_by_devname(supply.np->name, &e->supply);
		if (ret) {
			printf("DVFS: %s: Get supply(%s) failed, ret=%d",
			       e->name, supply.np->full_name, ret);
			return ret;
		}
		debug("DVFS: supply: %s\n", supply.np->full_name);
	}

	if (!ofnode_read_u32_array(node, "clocks", clock, ARRAY_SIZE(clock))) {
		e->clk.id = clock[1];
		ret = rockchip_get_clk(&e->clk.dev);
		if (ret) {
			printf("DVFS: %s: Get clk failed, ret=%d\n", e->name, ret);
			return ret;
		}
	}

	/* Get opp-table & limit param */
	if (!ofnode_read_u32(node, "operating-points-v2", &phandle)) {
		opp_node = ofnode_get_by_phandle(phandle);
		e->lmt.low_temp = ofnode_read_s32_default(opp_node,
						"rockchip,low-temp", -ENODATA);
		e->lmt.high_temp = ofnode_read_s32_default(opp_node,
						"rockchip,high-temp", -ENODATA);
		e->lmt.max_volt = ofnode_read_u32_default(opp_node,
						"rockchip,max-volt", -ENODATA);

		debug("DVFS: %s: low-temp=%d, high-temp=%d, max-volt=%d\n",
		      e->name, e->lmt.low_temp, e->lmt.high_temp,
		      e->lmt.max_volt);

		ofnode_for_each_subnode(node, opp_node) {
			if (e->opp_nr >= OPP_TABLE_MAX) {
				printf("DVFS: over max(%d) opp table items\n",
				       OPP_TABLE_MAX);
				break;
			}
			ofnode_read_u64(node, "opp-hz", &hz);
			ofnode_read_u32_array(node, "opp-microvolt", &uv, 1);
			e->opp[e->opp_nr].hz = hz;
			e->opp[e->opp_nr].uv = uv;
			e->opp_nr++;
			debug("DVFS: %s: opp[%d]: hz=%lld, uv=%d, %s\n",
			      e->name, e->opp_nr - 1,
			      hz, uv, ofnode_get_name(node));
		}
	}
	if (!e->opp_nr) {
		printf("DVFS: %s: Can't find opp table\n", e->name);
		return -EINVAL;
	}

	if (e->lmt.max_volt == -ENODATA)
		e->lmt.max_volt = e->opp[e->opp_nr - 1].uv;
	if (e->lmt.low_temp != -ENODATA)
		e->lmt.ltemp_limit = true;
	if (e->lmt.high_temp != -ENODATA)
		e->lmt.htemp_limit = true;

	return 0;
}

static int wtemp_dvfs_apply(struct udevice *dev)
{
	struct wtemp_dvfs_priv *priv = dev_get_priv(dev);
	struct list_head *node;
	struct pm_element *e;
	char s_temp[TEMP_STRING_LEN];
	int temp, ret;

	ret = thermal_get_temp(priv->thermal, &temp);
	if (ret) {
		printf("DVFS: Get temperature failed, ret=%d\n", ret);
		return ret;
	}

	temp2string(temp, s_temp, TEMP_STRING_LEN);
	printf("DVFS: %s'c\n", s_temp);

	/* Apply dvfs policy for all pm element */
	list_for_each(node, &pm_e_head) {
		e = list_entry(node, struct pm_element, node);
		__wtemp_dvfs_apply(dev, e, temp, PM_EVT_BOTH);
	}

	return 0;
}

static int wtemp_dvfs_repeat_apply(struct udevice *dev)
{
	struct wtemp_dvfs_priv *priv = dev_get_priv(dev);
	struct list_head *node;
	struct pm_element *e;
	enum pm_event applied;
	char s_temp[TEMP_STRING_LEN];
	int temp, ret;

repeat:
	ret = thermal_get_temp(priv->thermal, &temp);
	if (ret) {
		printf("DVFS: Get thermal temperature failed, ret=%d\n", ret);
		return false;
	}

	/* Apply dvfs policy for all pm element if there is repeat request */
	applied = PM_EVT_NONE;
	list_for_each(node, &pm_e_head) {
		e = list_entry(node, struct pm_element, node);
		if (e->lmt.ltemp_repeat)
			applied |= __wtemp_dvfs_apply(dev, e, temp, PM_EVT_LOW);
		if (e->lmt.htemp_repeat)
			applied |= __wtemp_dvfs_apply(dev, e, temp, PM_EVT_HIGH);
	}

	/* Everything is fine, exit */
	if (applied == PM_EVT_NONE)
		goto finish;

	/* Check repeat result */
	udelay(REPEAT_PERIOD_US);
	list_for_each(node, &pm_e_head) {
		e = list_entry(node, struct pm_element, node);
		if (e->lmt.ltemp_repeat &&
		    !wtemp_dvfs_is_effect(e, temp, PM_EVT_LOW))
			goto repeat;
		if (e->lmt.htemp_repeat &&
		    !wtemp_dvfs_is_effect(e, temp, PM_EVT_HIGH))
			goto repeat;
	}

finish:
	list_for_each(node, &pm_e_head) {
		e = list_entry(node, struct pm_element, node);
		temp2string(temp, s_temp, TEMP_STRING_LEN);
		printf("DVFS: %s %s'c, %ld Hz, %d uV\n", e->name,
		       s_temp, __wtemp_clk_get_rate(e),
		       __wtemp_regulator_get_value(e));
	}

	return 0;
}

static void print_e_state(void)
{
	struct pm_element *e;
	struct list_head *node;
	char s_low[TEMP_STRING_LEN];
	char s_high[TEMP_STRING_LEN];
	char s_tz[TEMP_STRING_LEN];

	list_for_each(node, &pm_e_head) {
		e = list_entry(node, struct pm_element, node);
		if (!e->lmt.ltemp_limit &&
		    !e->lmt.htemp_limit && !e->lmt.tztemp_limit)
			return;

		temp2string(e->lmt.tz_temp, s_tz, TEMP_STRING_LEN);
		temp2string(e->lmt.low_temp, s_low, TEMP_STRING_LEN);
		temp2string(e->lmt.high_temp, s_high, TEMP_STRING_LEN);
		printf("DVFS: %s: low=%s'c, high=%s'c, Vmax=%duV, tz_temp=%s'c, "
			  "h_repeat=%d, l_repeat=%d\n",
			  e->name, e->lmt.ltemp_limit ? s_low : NULL,
			  e->lmt.htemp_limit ? s_high : NULL,
			  e->lmt.max_volt,
			  e->lmt.tztemp_limit ? s_tz : NULL,
			  e->lmt.htemp_repeat, e->lmt.ltemp_repeat);
	}
}

static int wtemp_dvfs_ofdata_to_platdata(struct udevice *dev)
{
	struct wtemp_dvfs_priv *priv = dev_get_priv(dev);
	ofnode tz_trip0, cooling_maps, node;
	ofnode cpus, cpu, dmc;
	const char *name;
	int ret, tz_temp;
	u32 phandle;

	INIT_LIST_HEAD(&pm_e_head);

	/* 1. Parse cpu node */
	priv->cpu = &pm_cpu;
	cpus = ofnode_path(FDT_PATH_CPUS);
	if (!ofnode_valid(cpus)) {
		debug("DVFS: Can't find %s\n", FDT_PATH_CPUS);
		goto parse_dmc;
	}

	ofnode_for_each_subnode(cpu, cpus) {
		name = ofnode_get_property(cpu, "device_type", NULL);
		if (!name)
			continue;
		if (!strcmp(name, "cpu")) {
			ret = __wtemp_common_ofdata_to_platdata(cpu, priv->cpu);
			if (ret)
				return ret;
			break;
		}
	}

	priv->cpu->lmt.ltemp_repeat =
		dev_read_bool(dev, "cpu,low-temp-repeat");
	priv->cpu->lmt.htemp_repeat =
		dev_read_bool(dev, "cpu,high-temp-repeat");

	list_add_tail(&priv->cpu->node, &pm_e_head);

	/* 2. Parse dmc node */
parse_dmc:
	priv->dmc = &pm_dmc;
	dmc = ofnode_path(FDT_PATH_DMC);
	if (!ofnode_valid(dmc)) {
		debug("DVFS: Can't find %s\n", FDT_PATH_CPUS);
		goto parse_tz;
	}
	if (!IS_ENABLED(CONFIG_ROCKCHIP_DMC)) {
		debug("DVFS: CONFIG_ROCKCHIP_DMC is disabled\n");
		goto parse_tz;
	}

	ret = __wtemp_common_ofdata_to_platdata(dmc, priv->dmc);
	if (ret)
		return ret;

	priv->dmc->lmt.ltemp_repeat =
		dev_read_bool(dev, "dmc,low-temp-repeat");
	priv->dmc->lmt.htemp_repeat =
		dev_read_bool(dev, "dmc,high-temp-repeat");

	list_add_tail(&priv->dmc->node, &pm_e_head);

	/* 3. Parse thermal zone node */
parse_tz:
	tz_trip0 = ofnode_path(FDT_PATH_THREMAL_TRIP_POINT0);
	if (!ofnode_valid(tz_trip0)) {
		debug("DVFS: Can't find %s\n", FDT_PATH_THREMAL_TRIP_POINT0);
		goto finish;
	}

	tz_temp = ofnode_read_s32_default(tz_trip0, "temperature", -ENODATA);
	if (tz_temp == -ENODATA) {
		debug("DVFS: Can't get thermal zone trip0 temperature\n");
		goto finish;
	}

	cooling_maps = ofnode_path(FDT_PATH_THREMAL_COOLING_MAPS);
	if (!ofnode_valid(cooling_maps)) {
		debug("DVFS: Can't find %s\n", FDT_PATH_THREMAL_COOLING_MAPS);
		goto finish;
	}

	ofnode_for_each_subnode(node, cooling_maps) {
		ofnode_read_u32_array(node, "cooling-device", &phandle, 1);
		name = ofnode_get_name(ofnode_get_by_phandle(phandle));
		if (!name)
			continue;
		if (strstr(name, "cpu")) {
			priv->cpu->lmt.tztemp_limit = true;
			priv->cpu->lmt.tz_temp = tz_temp;
		} else if (strstr(name, "dmc")) {
			priv->dmc->lmt.tztemp_limit = true;
			priv->dmc->lmt.tz_temp = tz_temp;
		}
	}

finish:
	print_e_state();

	return 0;
}

static const struct dm_dvfs_ops wtemp_dvfs_ops = {
	.apply = wtemp_dvfs_apply,
	.repeat_apply = wtemp_dvfs_repeat_apply,
};

static int wtemp_dvfs_probe(struct udevice *dev)
{
	struct wtemp_dvfs_priv *priv = dev_get_priv(dev);
	int ret;

#ifdef CONFIG_ROCKCHIP_DMC
	struct udevice *ram_dev;

	/* Init dmc */
	ret = uclass_get_device(UCLASS_RAM, 0, &ram_dev);
	if (ret) {
		printf("DVFS: Get dmc device failed, ret=%d\n", ret);
		return ret;
	}
#endif
	/* Init thermal */
	ret = uclass_get_device(UCLASS_THERMAL, 0, &priv->thermal);
	if (ret) {
		printf("DVFS: Get thermal device failed, ret=%d\n", ret);
		return ret;
	}

	return 0;
}

static const struct udevice_id wtemp_dvfs_match[] = {
	{ .compatible = "rockchip,uboot-wide-temperature", },
	{},
};

U_BOOT_DRIVER(rockchip_wide_temp_dvfs) = {
	.name		      = "rockchip_wide_temp_dvfs",
	.id		      = UCLASS_DVFS,
	.ops		      = &wtemp_dvfs_ops,
	.of_match	      = wtemp_dvfs_match,
	.probe		      = wtemp_dvfs_probe,
	.ofdata_to_platdata   = wtemp_dvfs_ofdata_to_platdata,
	.priv_auto_alloc_size = sizeof(struct wtemp_dvfs_priv),
};
