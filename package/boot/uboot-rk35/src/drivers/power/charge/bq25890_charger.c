/*
 * (C) Copyright 2022 Rockchip Electronics Co., Ltd
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <common.h>
#include <dm.h>
#include <dm/device.h>
#include <dm/uclass.h>
#include <power/fuel_gauge.h>
#include <power/pmic.h>
#include <power/power_delivery/power_delivery.h>
#include <linux/usb/phy-rockchip-usb2.h>

DECLARE_GLOBAL_DATA_PTR;

#define BQ25890_CHARGE_CURRENT_1500MA		1500
#define BQ25890_SDP_INPUT_CURRENT_500MA		0x45
#define BQ25890_DCP_INPUT_CURRENT_1500MA	0x4f
#define BQ25890_DCP_INPUT_CURRENT_2000MA	0x54
#define BQ25890_DCP_INPUT_CURRENT_3000MA	0x5e

#define WATCHDOG_ENSABLE			(0x03 << 4)

#define BQ25890_CHARGEOPTION0_REG		0x07
#define BQ25890_CHARGECURREN_REG		0x04
#define BQ25890_CHARGERSTAUS_REG		0x0B
#define BQ25890_INPUTVOLTAGE_REG		0x0D
#define BQ25890_INPUTCURREN_REG			0x00
#define BQ25890_AUTO_DPDM_REG			0x02

/*
 * Most of the val -> idx conversions can be computed, given the minimum,
 * maximum and the step between values. For the rest of conversions, we use
 * lookup tables.
 */
enum bq25890_table_ids {
	/* range tables */
	TBL_ICHG,
	TBL_ITERM,
	TBL_IPRECHG,
	TBL_VREG,
	TBL_BATCMP,
	TBL_VCLAMP,
	TBL_BOOSTV,
	TBL_SYSVMIN,
	TBL_VINDPM,
	TBL_IINLIM,

	/* lookup tables */
	TBL_TREG,
	TBL_BOOSTI,
};

struct bq25890 {
	struct udevice *dev;
	u32 ichg;
	u32 chip_id;
	struct udevice *pd;
	bool pd_online;
};

/* Thermal Regulation Threshold lookup table, in degrees Celsius */
static const u32 bq25890_treg_tbl[] = { 60, 80, 100, 120 };

#define BQ25890_TREG_TBL_SIZE		ARRAY_SIZE(bq25890_treg_tbl)

/* Boost mode current limit lookup table, in uA */
static const u32 bq25890_boosti_tbl[] = {
	500000, 700000, 1100000, 1300000, 1600000, 1800000, 2100000, 2400000
};

#define BQ25890_BOOSTI_TBL_SIZE		ARRAY_SIZE(bq25890_boosti_tbl)

struct bq25890_range {
	u32 min;
	u32 max;
	u32 step;
};

struct bq25890_lookup {
	const u32 *tbl;
	u32 size;
};

static const union {
	struct bq25890_range  rt;
	struct bq25890_lookup lt;
} bq25890_tables[] = {
	/* range tables */
	[TBL_ICHG] =	{ .rt = {0,	  5056000, 64000} },	 /* uA */
	[TBL_ITERM] =	{ .rt = {64000,   1024000, 64000} },	 /* uA */
	[TBL_VREG] =	{ .rt = {3840000, 4608000, 16000} },	 /* uV */
	[TBL_BATCMP] =	{ .rt = {0,	  140,     20} },	 /* mOhm */
	[TBL_VCLAMP] =	{ .rt = {0,	  224000,  32000} },	 /* uV */
	[TBL_BOOSTV] =	{ .rt = {4550000, 5510000, 64000} },	 /* uV */
	[TBL_SYSVMIN] = { .rt = {3000000, 3700000, 100000} },	 /* uV */
	[TBL_VINDPM] = { .rt = {2600000, 15300000, 100000} }, /* uV */
	[TBL_IINLIM] = { .rt = {100, 3250000, 100000} }, /* uA */

	/* lookup tables */
	[TBL_TREG] =	{ .lt = {bq25890_treg_tbl, BQ25890_TREG_TBL_SIZE} },
	[TBL_BOOSTI] =	{ .lt = {bq25890_boosti_tbl, BQ25890_BOOSTI_TBL_SIZE} }
};

static int bq25890_read(struct bq25890 *charger, uint reg)
{
	u16 val;
	int ret;

	ret = dm_i2c_read(charger->dev, reg, (u8 *)&val, 1);
	if (ret) {
		printf("bq25890: read %#x error, ret=%d", reg, ret);
		return ret;
	}

	return val;
}

static int bq25890_write(struct bq25890 *charger, uint reg, u16 val)
{
	int ret;

	ret = dm_i2c_write(charger->dev, reg, (u8 *)&val, 1);
	if (ret) {
		printf("bq25890: write %#x error, ret=%d", reg, ret);
		return ret;
	}

	return 0;
}

static u8 bq25890_find_idx(u32 value, enum bq25890_table_ids id)
{
	u8 idx;

	if (id >= TBL_TREG) {
		const u32 *tbl = bq25890_tables[id].lt.tbl;
		u32 tbl_size = bq25890_tables[id].lt.size;

		for (idx = 1; idx < tbl_size && tbl[idx] <= value; idx++)
			;
	} else {
		const struct bq25890_range *rtbl = &bq25890_tables[id].rt;
		u8 rtbl_size;

		rtbl_size = (rtbl->max - rtbl->min) / rtbl->step + 1;

		for (idx = 1;
		     idx < rtbl_size && (idx * rtbl->step + rtbl->min <= value);
		     idx++)
			;
	}

	return idx - 1;
}

static bool bq25890_charger_status(struct bq25890 *charger)
{
	int state_of_charger;
	u16 value;
	int i = 0;

__retry:
	value = bq25890_read(charger, BQ25890_CHARGERSTAUS_REG);
	state_of_charger = value & 0x04;
	if (!state_of_charger && charger->pd_online) {
		if (i < 3) {
			i++;
			mdelay(20);
			goto __retry;
		}
	}

	return state_of_charger;
}

static bool bq257xx_charger_status(struct udevice *dev)
{
	struct bq25890 *charger = dev_get_priv(dev);

	return bq25890_charger_status(charger);
}

static int bq25890_charger_capability(struct udevice *dev)
{
	return FG_CAP_CHARGER;
}

static int bq25890_get_usb_type(void)
{
#ifdef CONFIG_PHY_ROCKCHIP_INNO_USB2
	return rockchip_chg_get_type();
#else
	return 0;
#endif
}

static int bq25890_get_pd_output_val(struct bq25890 *charger,
				     int *vol, int *cur)
{
	struct power_delivery_data pd_data;
	int ret;

	if (!charger->pd)
		return -EINVAL;

	memset(&pd_data, 0, sizeof(pd_data));
	ret = power_delivery_get_data(charger->pd, &pd_data);
	if (ret)
		return ret;
	if (!pd_data.online || !pd_data.voltage || !pd_data.current)
		return -EINVAL;

	*vol = pd_data.voltage;
	*cur = pd_data.current;
	charger->pd_online = pd_data.online;

	return 0;
}

static void bq25890_set_auto_dpdm_detect(struct bq25890 *charger, bool enable)
{
	u8 value;

	value = bq25890_read(charger, BQ25890_AUTO_DPDM_REG);
	value &= 0xfe;
	value |= enable;
	bq25890_write(charger, BQ25890_AUTO_DPDM_REG, value);
}

static void bq25890_charger_current_init(struct bq25890 *charger)
{
	u8 charge_current =  bq25890_find_idx(BQ25890_CHARGE_CURRENT_1500MA * 1000, TBL_ICHG);
	u8 sdp_inputcurrent = BQ25890_SDP_INPUT_CURRENT_500MA;
	u8 dcp_inputcurrent = BQ25890_DCP_INPUT_CURRENT_1500MA;
	int pd_inputvol,  pd_inputcurrent;
	u16 vol_idx = 0, cur_idx;
	u8 temp;

	temp = bq25890_read(charger, BQ25890_CHARGEOPTION0_REG);
	temp &= (~WATCHDOG_ENSABLE);
	bq25890_write(charger, BQ25890_CHARGEOPTION0_REG, temp);

	if (!bq25890_get_pd_output_val(charger, &pd_inputvol,
				       &pd_inputcurrent)) {
		printf("bq25890: pd charge %duV, %duA\n", pd_inputvol, pd_inputcurrent);
		if (pd_inputvol > 5000000) {
			vol_idx = bq25890_find_idx((pd_inputvol - 1280000 - 3200000),
						   TBL_VINDPM);
			vol_idx = vol_idx << 6;
		}
		cur_idx = bq25890_find_idx(pd_inputcurrent,
					   TBL_IINLIM);
		cur_idx  = cur_idx << 8;
		if (pd_inputcurrent != 0) {
			bq25890_set_auto_dpdm_detect(charger, false);
			bq25890_write(charger, BQ25890_INPUTCURREN_REG,
				      cur_idx);
			if (vol_idx)
				bq25890_write(charger, BQ25890_INPUTVOLTAGE_REG,
					      vol_idx);
			charge_current = bq25890_find_idx(charger->ichg,
							  TBL_ICHG);
		}
	} else {
		if (bq25890_get_usb_type() > 1)
			bq25890_write(charger, BQ25890_INPUTCURREN_REG,
				      dcp_inputcurrent);
		else
			bq25890_write(charger, BQ25890_INPUTCURREN_REG,
				      sdp_inputcurrent);
	}

	if (bq25890_charger_status(charger))
		bq25890_write(charger, BQ25890_CHARGECURREN_REG,
			      charge_current);
}

static int bq25890_ofdata_to_platdata(struct udevice *dev)
{
	struct bq25890 *charger = dev_get_priv(dev);

	charger->dev = dev;
	charger->ichg = dev_read_u32_default(dev, "ti,charge-current", 0);

	return 0;
}

static int bq25890_probe(struct udevice *dev)
{
	struct bq25890 *charger = dev_get_priv(dev);
	int ret;

	ret = uclass_get_device(UCLASS_PD, 0, &charger->pd);
	if (ret) {
		if (ret == -ENODEV)
			printf("Can't find PD\n");
		else
			printf("Get UCLASS PD failed: %d\n", ret);

		charger->pd = NULL;
	}

	bq25890_charger_current_init(charger);

	return 0;
}

static const struct udevice_id charger_ids[] = {
	{ .compatible = "ti,bq25890" },
	{ .compatible = "sy,sy6970" },
	{ },
};

static struct dm_fuel_gauge_ops charger_ops = {
	.get_chrg_online = bq257xx_charger_status,
	.capability = bq25890_charger_capability,
};

U_BOOT_DRIVER(bq25890_charger) = {
	.name = "bq25890_charger",
	.id = UCLASS_FG,
	.probe = bq25890_probe,
	.of_match = charger_ids,
	.ops = &charger_ops,
	.ofdata_to_platdata = bq25890_ofdata_to_platdata,
	.priv_auto_alloc_size = sizeof(struct bq25890),
};
