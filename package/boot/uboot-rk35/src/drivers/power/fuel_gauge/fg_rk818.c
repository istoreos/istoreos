/*
 * (C) Copyright 2017 Rockchip Electronics Co., Ltd
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */

#include <dm.h>
#include <errno.h>
#include <common.h>
#include <malloc.h>
#include <fdtdec.h>
#include <asm/gpio.h>
#include <common.h>
#include <power/pmic.h>
#include <dm/uclass-internal.h>
#include <power/charge_display.h>
#include <power/charge_animation.h>
#include <power/fuel_gauge.h>
#include <power/rk8xx_pmic.h>
#include <linux/usb/phy-rockchip-usb2.h>
#include "fg_regs.h"

DECLARE_GLOBAL_DATA_PTR;

static int dbg_enable = 0;
#define DBG(args...) \
	do { \
		if (dbg_enable) { \
			printf(args); \
		} \
	} while (0)

#define BAT_INFO(fmt, args...) printf("rk818-bat: "fmt, ##args)

#define DRIVER_VERSION		"2.0"

/* THERMAL_REG */
#define TEMP_105C		(0x02 << 2)
#define FB_TEMP_MSK		0x0c

/* CHRG_CTRL_REG2 */
#define FINISH_100MA		(0x00 << 6)
#define FINISH_150MA		(0x01 << 6)
#define FINISH_200MA		(0x02 << 6)
#define FINISH_250MA		(0x03 << 6)
#define FINISH_CUR_MSK		0xc7

/* CHRG_CTRL_REG3 */
#define CHRG_TERM_DIG_SIGNAL	(1 << 5)
#define CHRG_TERM_ANA_SIGNAL	(0 << 5)
#define CHRG_TIMER_CCCV_EN	(1 << 2)
#define CHRG_TERM_SIG_MSK	(1 << 5)

/* CHRG_CTRL_REG */
#define ILIM_450MA		(0x00)
#define ILIM_80MA		(0x01)
#define ILIM_850MA		(0x02)
#define ILIM_2000MA		(0x07)
#define CHRG_CT_EN		(1 << 7)

/* USB_CTRL_REG */
#define INPUT_CUR_MSK		0x0f

/* VB_MON_REG */
#define PLUG_IN_STS		(1 << 6)

/* GGSTS */
#define BAT_CON			(1 << 4)
#define VOL_INSTANT		(1 << 0)
#define VOL_AVG			(0 << 0)

/* TS_CTRL_REG */
#define GG_EN			(1 << 7)

/* CHRG_USB_CTRL */
#define CHRG_EN			(1 << 7)

/* ADC_CTRL_REG */
#define ADC_TS2_EN		(1 << 4)
#define ADC_TS1_EN		(1 << 5)

/* TS_CTRL_REG */
#define TS2_ADC_MODE		(1 << 5)

/* SUP_STS_REG */
#define BAT_EXS			(1 << 7)
#define USB_EXIST		(1 << 1)
#define USB_EFF			(1 << 0)
#define CHARGE_OFF		(0x00 << 4)
#define DEAD_CHARGE		(0x01 << 4)
#define TRICKLE_CHARGE		(0x02 << 4)
#define CC_OR_CV		(0x03 << 4)
#define CHARGE_FINISH		(0x04 << 4)
#define USB_OVER_VOL		(0x05 << 4)
#define BAT_TMP_ERR		(0x06 << 4)
#define TIMER_ERR		(0x07 << 4)
#define USB_VLIMIT_EN		(1 << 3)
#define USB_CLIMIT_EN		(1 << 2)
#define BAT_STATUS_MSK		0x70

/* GGCON */
#define ADC_CUR_MODE		(1 << 1)

/* CALI PARAM */
#define FINISH_CALI_CURR	1500
#define TERM_CALI_CURR		600
#define	VIRTUAL_POWER_VOL	4200
#define	VIRTUAL_POWER_CUR	1000
#define	VIRTUAL_POWER_SOC	66
#define SECONDS(n)		((n) * 1000)

/* CALC PARAM */
#define MAX_PERCENTAGE		100
#define MAX_INTERPOLATE		1000
#define MAX_INT			0x7fff
#define MIN_FCC			500

/* sample resistor and division */
#define SAMPLE_RES_10mR		10
#define SAMPLE_RES_20mR		20
#define SAMPLE_RES_DIV1		1
#define SAMPLE_RES_DIV2		2

#define FG_INIT			(1 << 5)
#define FG_RESET_LATE		(1 << 4)
#define FG_RESET_NOW		(1 << 3)

#define DEFAULT_POFFSET		42
#define DEFAULT_COFFSET		0x832
#define INVALID_COFFSET_MIN	0x780
#define INVALID_COFFSET_MAX	0x980

#define CHRG_TERM_DSOC		90
#define CHRG_TERM_K		650
#define CHRG_FULL_K		400
#define ADC_CALIB_THRESHOLD	4

#define TS2_THRESHOLD_VOL	4350
#define TS2_VALID_VOL		1000
#define TS2_VOL_MULTI		0
#define TS2_CHECK_CNT		5

#define ADC_CUR_MSK		0x03
#define ADC_CUR_20UA		0x00
#define ADC_CUR_40UA		0x01
#define ADC_CUR_60UA		0x02
#define ADC_CUR_80UA		0x03

#define NTC_CALC_FACTOR_80UA	7
#define NTC_CALC_FACTOR_60UA	9
#define NTC_CALC_FACTOR_40UA	13
#define NTC_CALC_FACTOR_20UA	27
#define NTC_80UA_MAX_MEASURE	27500
#define NTC_60UA_MAX_MEASURE	36666
#define NTC_40UA_MAX_MEASURE	55000
#define NTC_20UA_MAX_MEASURE	110000

#define ZERO_MIN_VOLTAGE	3800

#define TS1_NOT_READY		0xabcdabcd

#define DIV(x)			((x) ? (x) : 1)

/***********************************************************/
struct battery_priv {
	struct udevice *dev;
	int		chrg_type;
	int		poffset;
	int		bat_res;
	int		current_avg;
	int		voltage_avg;
	int		voltage_ocv;
	int		voltage_k;
	int		voltage_b;
	int		dsoc;
	int		rsoc;
	int		fcc;
	int		qmax;
	int		remain_cap;
	int		design_cap;
	int		nac;
	u32		*ocv_table;
	u32		ocv_size;
	u32		*ntc_table;
	u32		ntc_size;
	u32		ntc_factor;
	u32		ntc_uA;
	int		ntc_degree_from;
	int		temperature;
	int		virtual_power;
	int		ts2_vol_multi;
	int		pwroff_min;
	int		sm_old_cap;
	int		sm_linek;
	int		sm_chrg_dsoc;
	int		adc_allow_update;
	int		chrg_vol_sel;
	int		chrg_cur_input;
	int		chrg_cur_sel;
	int		dts_vol_sel;
	int		dts_cur_input;
	int		dts_cur_sel;
	int		max_soc_offset;
	int		sample_res;
	int		res_div;
	struct gpio_desc dc_det;
	int		dc_det_adc;
	ulong		finish_chrg_base;
	ulong		term_sig_base;
	u8		calc_dsoc;
	u8		calc_rsoc;
	int		sm_meet_soc;
	u8		halt_cnt;
	u8		dc_active_level;
	u8		dc_is_valid;
	bool		is_halt;
	bool		is_ocv_calib;
	bool		is_max_soc_offset;
	bool		is_first_power_on;
	bool		is_sw_reset;
	int		pwr_dsoc;
	int		pwr_rsoc;
	int		pwr_vol;
};

enum charger_type {
	NO_CHARGER = 0,
	USB_CHARGER,
	AC_CHARGER,
	DC_CHARGER,
	UNDEF_CHARGER,
};

static const u32 CHRG_VOL_SEL[] = {
	4050, 4100, 4150, 4200, 4250, 4300, 4350
};

static const u32 CHRG_CUR_SEL[] = {
	1000, 1200, 1400, 1600, 1800, 2000, 2250, 2400, 2600, 2800, 3000
};

static const u32 CHRG_CUR_INPUT[] = {
	450, 800, 850, 1000, 1250, 1500, 1750, 2000, 2250, 2500, 2750, 3000
};

static int rk818_bat_read(struct battery_priv *di, u8 reg)
{
	return pmic_reg_read(di->dev->parent, reg);
}

static void rk818_bat_write(struct battery_priv *di, u8 reg, u8 buf)
{
	pmic_reg_write(di->dev->parent, reg, buf);
}

static int rk818_bat_dwc_otg_check_dpdm(void)
{
#if defined(CONFIG_PHY_ROCKCHIP_INNO_USB2) && !defined(CONFIG_SPL_BUILD)
	return rockchip_chg_get_type();
#else
	debug("rockchip_chg_get_type() is not implement\n");
	return NO_CHARGER;
#endif
}

static int rk818_bat_get_rsoc(struct battery_priv *di)
{
	return (di->remain_cap + di->fcc / 200) * 100 / DIV(di->fcc);
}

static int rk818_bat_get_dsoc(struct  battery_priv *di)
{
	return rk818_bat_read(di, SOC_REG);
}

static void rk818_bat_enable_gauge(struct battery_priv *di)
{
	u8 val;

	val = rk818_bat_read(di, TS_CTRL_REG);
	val |= GG_EN;
	rk818_bat_write(di, TS_CTRL_REG, val);
}

static int rk818_bat_get_vcalib0(struct battery_priv *di)
{
	int val = 0;

	val |= rk818_bat_read(di, VCALIB0_REGL) << 0;
	val |= rk818_bat_read(di, VCALIB0_REGH) << 8;

	return val;
}

static int rk818_bat_get_vcalib1(struct battery_priv *di)
{
	int val = 0;

	val |= rk818_bat_read(di, VCALIB1_REGL) << 0;
	val |= rk818_bat_read(di, VCALIB1_REGH) << 8;

	return val;
}

static int rk818_bat_get_ioffset(struct battery_priv *di)
{
	int val = 0;

	val |= rk818_bat_read(di, IOFFSET_REGL) << 0;
	val |= rk818_bat_read(di, IOFFSET_REGH) << 8;

	DBG("<%s>. ioffset: 0x%x\n", __func__, val);
	return val;
}

static int rk818_bat_get_coffset(struct battery_priv *di)
{
	int val = 0;

	val |= rk818_bat_read(di, CAL_OFFSET_REGL) << 0;
	val |= rk818_bat_read(di, CAL_OFFSET_REGH) << 8;

	DBG("<%s>. coffset: 0x%x\n", __func__, val);
	return val;
}

static void rk818_bat_set_coffset(struct battery_priv *di, int val)
{
	u8 buf;

	buf = (val >> 0) & 0xff;
	rk818_bat_write(di, CAL_OFFSET_REGL, buf);
	buf = (val >> 8) & 0xff;
	rk818_bat_write(di, CAL_OFFSET_REGH, buf);

	DBG("<%s>. set coffset: 0x%x\n", __func__, val);
}

static void rk818_bat_init_coffset(struct battery_priv *di)
{
	int ioffset, coffset;

	ioffset = rk818_bat_get_ioffset(di);

	di->poffset = rk818_bat_read(di, POFFSET_REG);
	if (!di->poffset)
		di->poffset = DEFAULT_POFFSET;

	coffset = di->poffset + ioffset;
	if (coffset < INVALID_COFFSET_MIN || coffset > INVALID_COFFSET_MAX)
		coffset = DEFAULT_COFFSET;

	rk818_bat_set_coffset(di, coffset);
}

static void rk818_bat_init_voltage_kb(struct battery_priv *di)
{
	int vcalib0, vcalib1;

	vcalib0 = rk818_bat_get_vcalib0(di);
	vcalib1 = rk818_bat_get_vcalib1(di);
	di->voltage_k = (4200 - 3000) * 1000 / DIV(vcalib1 - vcalib0);
	di->voltage_b = 4200 - (di->voltage_k * vcalib1) / 1000;
	DBG("%s. vk=%d, vb=%d\n", __func__, di->voltage_k, di->voltage_b);
}

static int rk818_bat_get_ocv_voltage(struct battery_priv *di)
{
	int vol, val = 0;

	val |= rk818_bat_read(di, BAT_OCV_REGL) << 0;
	val |= rk818_bat_read(di, BAT_OCV_REGH) << 8;
	vol = di->voltage_k * val / 1000 + di->voltage_b;

	return vol;
}

static int rk818_bat_get_avg_current(struct battery_priv *di)
{
	int val = 0;

	val |= rk818_bat_read(di, BAT_CUR_AVG_REGL) << 0;
	val |= rk818_bat_read(di, BAT_CUR_AVG_REGH) << 8;

	if (val & 0x800)
		val -= 4096;
	val = val * di->res_div * 1506 / 1000;

	return val;
}

static int rk818_bat_get_avg_voltage(struct battery_priv *di)
{
	int vol, val = 0;

	val |= rk818_bat_read(di, BAT_VOL_REGL) << 0;
	val |= rk818_bat_read(di, BAT_VOL_REGH) << 8;
	vol = di->voltage_k * val / 1000 + di->voltage_b;

	return vol;
}

static int rk818_bat_get_est_voltage(struct battery_priv *di)
{
	struct charge_animation_pdata *pdata = NULL;
	struct udevice *dev;
	int est_vol, vol, curr;
	int plugin, timeout = 0;
	int low_power_voltage = 0;

	uclass_find_first_device(UCLASS_CHARGE_DISPLAY, &dev);
	pdata = dev_get_platdata(dev);
	low_power_voltage = pdata->low_power_voltage;

	vol = rk818_bat_get_avg_voltage(di);
	curr = rk818_bat_get_avg_current(di);
	plugin = rk818_bat_read(di, VB_MON_REG) & PLUG_IN_STS ? 1 : 0;
	if (di->is_first_power_on || (!plugin && curr >= 0) || (plugin && curr <= 0)) {
		DBG("%s: curr=%d, plugin=%d, first_on=%d\n",
		    __func__, curr, plugin, di->is_first_power_on);
		curr = 0;
	}
	est_vol = vol - (di->bat_res * curr / 1000);

	while ((est_vol <= low_power_voltage) &&
	       (vol <= low_power_voltage)) {
		mdelay(100);

		/* Update */
		vol = rk818_bat_get_avg_voltage(di);
		curr = rk818_bat_get_avg_current(di);
		plugin = rk818_bat_read(di, VB_MON_REG) & PLUG_IN_STS;
		if (di->is_first_power_on || (!plugin && curr >= 0) || (plugin && curr <= 0)) {
			DBG("%s: while curr=%d, plugin=%d, first_on=%d\n",
			    __func__, curr, plugin, di->is_first_power_on);
			curr = 0;
		}
		est_vol = vol - (di->bat_res * curr / 1000);

		timeout++;
		if (timeout >= 5)
			break;
	}

	return (est_vol >= low_power_voltage) ? est_vol : vol;
}

static u8 rk818_bat_finish_ma(struct battery_priv *di, int fcc)
{
	u8 ma;

	if (di->res_div == 2)
		ma = FINISH_100MA;
	else if (fcc > 5000)
		ma = FINISH_250MA;
	else if (fcc >= 4000)
		ma = FINISH_200MA;
	else if (fcc >= 3000)
		ma = FINISH_150MA;
	else
		ma = FINISH_100MA;

	return ma;
}

static void rk818_bat_select_chrg_cv(struct battery_priv *di)
{
	int index, chrg_vol_sel, chrg_cur_sel, chrg_cur_input;

	chrg_vol_sel = di->dts_vol_sel;
	chrg_cur_sel = di->dts_cur_sel;
	chrg_cur_input = di->dts_cur_input;
	if (di->sample_res == SAMPLE_RES_10mR) {
		if (chrg_cur_sel > 2000)
			chrg_cur_sel /= di->res_div;
		else
			chrg_cur_sel = 1000;
	}

	for (index = 0; index < ARRAY_SIZE(CHRG_VOL_SEL); index++) {
		if (chrg_vol_sel < CHRG_VOL_SEL[index])
			break;
		di->chrg_vol_sel = (index << 4);
	}

	for (index = 0; index < ARRAY_SIZE(CHRG_CUR_INPUT); index++) {
		if (chrg_cur_input < CHRG_CUR_INPUT[index])
			break;
		di->chrg_cur_input = (index << 0);
	}

	for (index = 0; index < ARRAY_SIZE(CHRG_CUR_SEL); index++) {
		if (chrg_cur_sel < CHRG_CUR_SEL[index])
			break;
		di->chrg_cur_sel = (index << 0);
	}

	DBG("<%s>. vol=0x%x, input=0x%x, sel=0x%x\n",
	    __func__, di->chrg_vol_sel, di->chrg_cur_input, di->chrg_cur_sel);
}

static void rk818_bat_init_chrg_config(struct battery_priv *di)
{
	u8 chrg_ctrl1, usb_ctrl, chrg_ctrl2, chrg_ctrl3;
	u8 sup_sts, ggcon, thermal, finish_ma;

	rk818_bat_select_chrg_cv(di);
	finish_ma = rk818_bat_finish_ma(di, di->fcc);

	ggcon = rk818_bat_read(di, GGCON_REG);
	sup_sts = rk818_bat_read(di, SUP_STS_REG);
	usb_ctrl = rk818_bat_read(di, USB_CTRL_REG);
	thermal = rk818_bat_read(di, THERMAL_REG);
	chrg_ctrl2 = rk818_bat_read(di, CHRG_CTRL_REG2);
	chrg_ctrl3 = rk818_bat_read(di, CHRG_CTRL_REG3);

	/* set charge current and voltage */
	usb_ctrl &= ~INPUT_CUR_MSK;
	usb_ctrl |= di->chrg_cur_input;
	chrg_ctrl1 = (CHRG_EN | di->chrg_vol_sel | di->chrg_cur_sel);

	/* digital signal and finish current*/
	chrg_ctrl3 &= ~CHRG_TERM_SIG_MSK;
	chrg_ctrl3 |= CHRG_TERM_ANA_SIGNAL;
	chrg_ctrl2 &= ~FINISH_CUR_MSK;
	chrg_ctrl2 |= finish_ma;

	/* cccv mode */
	chrg_ctrl3 &= ~CHRG_TIMER_CCCV_EN;

	/* enable voltage limit and enable input current limit */
	sup_sts &= ~USB_VLIMIT_EN;
	sup_sts |= USB_CLIMIT_EN;

	/* set feedback temperature */
	usb_ctrl |= CHRG_CT_EN;
	thermal &= ~FB_TEMP_MSK;
	thermal |= TEMP_105C;

	/* adc current mode */
	ggcon |= ADC_CUR_MODE;

	rk818_bat_write(di, GGCON_REG, ggcon);
	rk818_bat_write(di, SUP_STS_REG, sup_sts);
	rk818_bat_write(di, USB_CTRL_REG, usb_ctrl);
	rk818_bat_write(di, THERMAL_REG, thermal);
	rk818_bat_write(di, CHRG_CTRL_REG1, chrg_ctrl1);
	rk818_bat_write(di, CHRG_CTRL_REG2, chrg_ctrl2);
	rk818_bat_write(di, CHRG_CTRL_REG3, chrg_ctrl3);
}

static u32 interpolate(int value, u32 *table, int size)
{
	uint8_t i;
	uint16_t d;

	for (i = 0; i < size; i++) {
		if (value < table[i])
			break;
	}

	if ((i > 0) && (i < size)) {
		d = (value - table[i - 1]) * (MAX_INTERPOLATE / (size - 1));
		d /= table[i] - table[i - 1];
		d = d + (i - 1) * (MAX_INTERPOLATE / (size - 1));
	} else {
		d = i * ((MAX_INTERPOLATE + size / 2) / size);
	}

	if (d > 1000)
		d = 1000;

	return d;
}

/* returns (a * b) / c */
static int32_t ab_div_c(u32 a, u32 b, u32 c)
{
	bool sign;
	u32 ans = MAX_INT;
	int32_t tmp;

	sign = ((((a ^ b) ^ c) & 0x80000000) != 0);

	if (c != 0) {
		if (sign)
			c = -c;
		tmp = ((int32_t)a * b + (c >> 1)) / c;
		if (tmp < MAX_INT)
			ans = tmp;
	}

	if (sign)
		ans = -ans;

	return ans;
}

static int rk818_bat_vol_to_cap(struct battery_priv *di, int voltage)
{
	u32 *ocv_table, tmp;
	int ocv_size, ocv_cap;

	ocv_table = di->ocv_table;
	ocv_size = di->ocv_size;
	tmp = interpolate(voltage, ocv_table, ocv_size);
	ocv_cap = ab_div_c(tmp, di->fcc, MAX_INTERPOLATE);

	return ocv_cap;
}

static int rk818_bat_vol_to_soc(struct battery_priv *di, int voltage)
{
	u32 *ocv_table, tmp;
	int ocv_size, ocv_soc;

	ocv_table = di->ocv_table;
	ocv_size = di->ocv_size;
	tmp = interpolate(voltage, ocv_table, ocv_size);
	ocv_soc = ab_div_c(tmp, MAX_PERCENTAGE, MAX_INTERPOLATE);

	return ocv_soc;
}

static int rk818_bat_get_prev_cap(struct battery_priv *di)
{
	int val = 0;

	val |= rk818_bat_read(di, REMAIN_CAP_REG3) << 24;
	val |= rk818_bat_read(di, REMAIN_CAP_REG2) << 16;
	val |= rk818_bat_read(di, REMAIN_CAP_REG1) << 8;
	val |= rk818_bat_read(di, REMAIN_CAP_REG0) << 0;

	return val;
}

static void rk818_bat_save_fcc(struct battery_priv *di, u32 cap)
{
	u8 buf;

	buf = (cap >> 24) & 0xff;
	rk818_bat_write(di, NEW_FCC_REG3, buf);
	buf = (cap >> 16) & 0xff;
	rk818_bat_write(di, NEW_FCC_REG2, buf);
	buf = (cap >> 8) & 0xff;
	rk818_bat_write(di, NEW_FCC_REG1, buf);
	buf = (cap >> 0) & 0xff;
	rk818_bat_write(di, NEW_FCC_REG0, buf);
}

static int rk818_bat_get_fcc(struct battery_priv *di)
{
	int val = 0;

	val |= rk818_bat_read(di, NEW_FCC_REG3) << 24;
	val |= rk818_bat_read(di, NEW_FCC_REG2) << 16;
	val |= rk818_bat_read(di, NEW_FCC_REG1) << 8;
	val |= rk818_bat_read(di, NEW_FCC_REG0) << 0;

	if (val < MIN_FCC)
		val = di->design_cap;
	else if (val > di->qmax)
		val = di->qmax;

	return val;
}

static int rk818_bat_get_pwroff_min(struct battery_priv *di)
{
	u8 cur, last;

	cur = rk818_bat_read(di, NON_ACT_TIMER_CNT_REG);
	last = rk818_bat_read(di, NON_ACT_TIMER_CNT_SAVE_REG);
	rk818_bat_write(di, NON_ACT_TIMER_CNT_SAVE_REG, cur);

	return (cur != last) ? cur : 0;
}

static int rk818_bat_get_coulomb_cap(struct battery_priv *di)
{
	int val = 0;

	val |= rk818_bat_read(di, GASCNT_REG3) << 24;
	val |= rk818_bat_read(di, GASCNT_REG2) << 16;
	val |= rk818_bat_read(di, GASCNT_REG1) << 8;
	val |= rk818_bat_read(di, GASCNT_REG0) << 0;
	val /= 2390;

	return val * di->res_div;
}

static void rk818_bat_save_cap(struct battery_priv *di, int cap)
{
	u8 buf;
	static int old_cap;

	if (old_cap == cap)
		return;

	if (cap >= di->qmax)
		cap = di->qmax;

	old_cap = cap;
	buf = (cap >> 24) & 0xff;
	rk818_bat_write(di, REMAIN_CAP_REG3, buf);
	buf = (cap >> 16) & 0xff;
	rk818_bat_write(di, REMAIN_CAP_REG2, buf);
	buf = (cap >> 8) & 0xff;
	rk818_bat_write(di, REMAIN_CAP_REG1, buf);
	buf = (cap >> 0) & 0xff;
	rk818_bat_write(di, REMAIN_CAP_REG0, buf);
}

static void rk818_bat_init_capacity(struct battery_priv *di, u32 capacity)
{
	u8 buf;
	u32 cap;
	int delta;

	delta = capacity - di->remain_cap;
	if (!delta)
		return;

	cap = capacity * 2390 / di->res_div;
	buf = (cap >> 24) & 0xff;
	rk818_bat_write(di, GASCNT_CAL_REG3, buf);
	buf = (cap >> 16) & 0xff;
	rk818_bat_write(di, GASCNT_CAL_REG2, buf);
	buf = (cap >> 8) & 0xff;
	rk818_bat_write(di, GASCNT_CAL_REG1, buf);
	buf = (cap >> 0) & 0xff;
	rk818_bat_write(di, GASCNT_CAL_REG0, buf);

	di->remain_cap = rk818_bat_get_coulomb_cap(di);
	di->rsoc = rk818_bat_get_rsoc(di);
	rk818_bat_save_cap(di, di->remain_cap);
}

static bool is_rk818_bat_ocv_valid(struct battery_priv *di)
{
	return di->pwroff_min >= 30 ? true : false;
}

static int rk818_bat_get_usb_state(struct battery_priv *di)
{
	int charger_type;

	switch (rk818_bat_dwc_otg_check_dpdm()) {
	case 0:
		if ((rk818_bat_read(di, VB_MON_REG) & PLUG_IN_STS) != 0)
			charger_type = DC_CHARGER;
		else
			charger_type = NO_CHARGER;
		break;
	case 1:
	case 3:
		charger_type = USB_CHARGER;
		break;
	case 2:
	case 4:
		charger_type = AC_CHARGER;
		break;
	default:
		charger_type = NO_CHARGER;
	}

	return charger_type;
}

static void rk818_bat_clr_initialized_state(struct battery_priv *di)
{
	u8 val;

	val = rk818_bat_read(di, MISC_MARK_REG);
	val &= ~FG_INIT;
	rk818_bat_write(di, MISC_MARK_REG, val);
}

static bool rk818_bat_is_initialized(struct battery_priv *di)
{
	return (rk818_bat_read(di, MISC_MARK_REG) & FG_INIT) ? true : false;
}

static void rk818_bat_set_initialized_state(struct battery_priv *di)
{
	u8 val;

	val = rk818_bat_read(di, MISC_MARK_REG);
	if (rk818_bat_get_usb_state(di) != NO_CHARGER) {
		val |= FG_INIT;
		rk818_bat_write(di, MISC_MARK_REG, val);
		BAT_INFO("initialized... estv=%d, ch=%d\n",
			 rk818_bat_get_est_voltage(di),
			 rk818_bat_get_usb_state(di));
	}
}

static void rk818_bat_save_dsoc(struct  battery_priv *di, u8 save_soc)
{
	static int old_soc = -1;

	if (old_soc != save_soc) {
		old_soc = save_soc;
		rk818_bat_write(di, SOC_REG, save_soc);
	}
}

static void rk818_bat_first_pwron(struct battery_priv *di)
{
	int ocv_vol, vol, curr;

	rk818_bat_save_fcc(di, di->design_cap);
	ocv_vol = rk818_bat_get_ocv_voltage(di);
	curr = rk818_bat_get_avg_current(di);
	di->fcc = rk818_bat_get_fcc(di);
	di->nac = rk818_bat_vol_to_cap(di, ocv_vol);
	di->rsoc = rk818_bat_vol_to_soc(di, ocv_vol);
	di->dsoc = di->rsoc;
	vol = rk818_bat_get_avg_voltage(di);
	if (ocv_vol < vol) {
		BAT_INFO("%s: ocv voltage %d\n", __func__, ocv_vol);
		ocv_vol = vol;
	}
	rk818_bat_save_dsoc(di, di->dsoc);
	rk818_bat_init_capacity(di, di->nac);
	rk818_bat_set_initialized_state(di);
	BAT_INFO("first power on: soc=%d, Vavg=%d, Vocv=%d, c=%d, ch=%d, fcc=%d\n",
		 di->dsoc, vol, ocv_vol, curr, rk818_bat_get_usb_state(di), di->fcc);
}

static u8 rk818_bat_get_halt_cnt(struct battery_priv *di)
{
	return rk818_bat_read(di, HALT_CNT_REG);
}

static void rk818_bat_inc_halt_cnt(struct battery_priv *di)
{
	u8 cnt;

	cnt = rk818_bat_read(di, HALT_CNT_REG);
	rk818_bat_write(di, HALT_CNT_REG, ++cnt);
}

static bool is_rk818_bat_last_halt(struct battery_priv *di)
{
	int pre_cap = rk818_bat_get_prev_cap(di);
	int now_cap = rk818_bat_get_coulomb_cap(di);

	/* over 5%: system halt last time */
	if (abs(now_cap - pre_cap) > (di->fcc / 20)) {
		rk818_bat_inc_halt_cnt(di);
		return true;
	} else {
		return false;
	}
}

static void rk818_bat_not_first_pwron(struct battery_priv *di)
{
	int pre_soc, pre_cap, ocv_cap = 0, ocv_soc = 0, ocv_vol, now_cap;
	int voltage;

	di->fcc = rk818_bat_get_fcc(di);
	pre_soc = rk818_bat_get_dsoc(di);
	pre_cap = rk818_bat_get_prev_cap(di);
	now_cap = rk818_bat_get_coulomb_cap(di);
	voltage = rk818_bat_get_est_voltage(di);
	di->pwr_dsoc = pre_soc;
	di->pwr_rsoc = (now_cap + di->fcc / 200) * 100 / DIV(di->fcc);
	di->is_halt = is_rk818_bat_last_halt(di);
	di->halt_cnt = rk818_bat_get_halt_cnt(di);
	di->is_ocv_calib = is_rk818_bat_ocv_valid(di);

	if (di->is_halt) {
		BAT_INFO("system halt last time... cap: pre=%d, now=%d\n",
			 pre_cap, now_cap);
		if (now_cap < 0)
			now_cap = 0;
		rk818_bat_init_capacity(di, now_cap);
		pre_cap = di->remain_cap;
		pre_soc = di->rsoc;
		goto finish;
	} else if (di->is_ocv_calib) {
		ocv_vol = rk818_bat_get_ocv_voltage(di);
		ocv_soc = rk818_bat_vol_to_soc(di, ocv_vol);
		ocv_cap = rk818_bat_vol_to_cap(di, ocv_vol);
		pre_cap = ocv_cap;
		BAT_INFO("do ocv calib.. rsoc=%d\n", ocv_soc);

		if (abs(ocv_soc - pre_soc) >= di->max_soc_offset) {
			BAT_INFO("trigger max soc offset, soc: %d -> %d\n",
				 pre_soc, ocv_soc);
			pre_soc = ocv_soc;
			di->is_max_soc_offset = true;
		}
		BAT_INFO("OCV calib: cap=%d, rsoc=%d\n", ocv_cap, ocv_soc);
	} else if ((pre_soc == 0) && (voltage >= ZERO_MIN_VOLTAGE)) {
		if (now_cap < 0)
			now_cap = 0;
		rk818_bat_init_capacity(di, now_cap);
		pre_cap = di->remain_cap;
		pre_soc = di->rsoc;
		BAT_INFO("zero calib: voltage=%d\n", voltage);
	}
finish:
	di->dsoc = pre_soc;
	di->nac = pre_cap;
	rk818_bat_init_capacity(di, di->nac);
	rk818_bat_save_dsoc(di, di->dsoc);
	rk818_bat_set_initialized_state(di);
	BAT_INFO("dl=%d rl=%d cap=%d m=%d v=%d ov=%d c=%d pl=%d ch=%d fcc=%d, Ver=%s\n",
		 di->dsoc, di->rsoc, di->remain_cap, di->pwroff_min,
		 rk818_bat_get_avg_voltage(di), rk818_bat_get_ocv_voltage(di),
		 rk818_bat_get_avg_current(di), rk818_bat_get_dsoc(di),
		 rk818_bat_get_usb_state(di), di->fcc, DRIVER_VERSION
		 );
}

static bool is_rk818_bat_first_poweron(struct battery_priv *di)
{
	u8 buf;

	buf = rk818_bat_read(di, GGSTS_REG);
	if (buf & BAT_CON) {
		buf &= ~BAT_CON;
		rk818_bat_write(di, GGSTS_REG, buf);
		return true;
	}

	return false;
}

static bool rk818_bat_ocv_sw_reset(struct battery_priv *di)
{
	u8 buf;

	buf = rk818_bat_read(di, MISC_MARK_REG);
	if (((buf & FG_RESET_LATE) && di->pwroff_min >= 30) ||
	    (buf & FG_RESET_NOW)) {
		buf &= ~FG_RESET_LATE;
		buf &= ~FG_RESET_NOW;
		rk818_bat_write(di, MISC_MARK_REG, buf);
		BAT_INFO("manual reset fuel gauge\n");
		return true;
	} else {
		return false;
	}
}

static void rk818_bat_init_rsoc(struct battery_priv *di)
{
	int charger, voltage, initialize = 0;
	struct charge_animation_pdata *pdata;
	struct udevice *dev;

	uclass_find_first_device(UCLASS_CHARGE_DISPLAY, &dev);
	pdata = dev_get_platdata(dev);

	charger = rk818_bat_get_usb_state(di);
	voltage = rk818_bat_get_est_voltage(di);
	di->is_first_power_on = is_rk818_bat_first_poweron(di);

	/*
	 * Do rsoc initialization only when:
	 *
	 * 1. first power on;
	 * 2. charger online + voltage lower than low_power_voltage;
	 * 3. charger online + uboot_charge enabled.
	 * 4. dsoc is 0 but voltage high, obvious wrong.
	 */
	if (di->is_first_power_on) {
		initialize = 1;
	} else if ((di->dsoc == 0) && (voltage >= ZERO_MIN_VOLTAGE)) {
		initialize = 1;
	} else if (charger != NO_CHARGER) {
		if (voltage < pdata->low_power_voltage + 50)
			initialize = 1;
		else if (pdata->uboot_charge)
			initialize = 1;
	}

	if (!initialize)
		return;

	di->pwroff_min = rk818_bat_get_pwroff_min(di);
	di->is_sw_reset = rk818_bat_ocv_sw_reset(di);

	if (di->is_first_power_on || di->is_sw_reset)
		rk818_bat_first_pwron(di);
	else
		rk818_bat_not_first_pwron(di);
}

static int rk818_bat_calc_linek(struct battery_priv *di)
{
	int linek, diff, delta;

	di->calc_dsoc = di->dsoc;
	di->calc_rsoc = di->rsoc;
	di->sm_old_cap = di->remain_cap;

	delta = abs(di->dsoc - di->rsoc);
	diff = delta * 3;
	di->sm_meet_soc = (di->dsoc >= di->rsoc) ?
			   (di->dsoc + diff) : (di->rsoc + diff);

	if (di->dsoc < di->rsoc)
		linek = 1000 * (delta + diff) / DIV(diff);
	else if (di->dsoc > di->rsoc)
		linek = 1000 * diff / DIV(delta + diff);
	else
		linek = 1000;

	di->sm_chrg_dsoc = di->dsoc * 1000;

	DBG("<%s>. meet=%d, diff=%d, link=%d, calc: dsoc=%d, rsoc=%d\n",
	    __func__, di->sm_meet_soc, diff, linek,
	    di->calc_dsoc, di->calc_rsoc);

	return linek;
}

static void rk818_bat_init_ts1(struct battery_priv *di)
{
	u8 buf;
	u32 *ntc_table = di->ntc_table;

	if (!di->ntc_size)
		return;

	/* select uA */
	buf = rk818_bat_read(di, TS_CTRL_REG);
	buf &= ~ADC_CUR_MSK;
	/* chose suitable UA for temperature detect */
	if (ntc_table[0] < NTC_80UA_MAX_MEASURE) {
		di->ntc_factor = NTC_CALC_FACTOR_80UA;
		di->ntc_uA = 80;
		buf |= ADC_CUR_80UA;
	} else if (ntc_table[0] < NTC_60UA_MAX_MEASURE) {
		di->ntc_factor = NTC_CALC_FACTOR_60UA;
		di->ntc_uA = 60;
		buf |= ADC_CUR_60UA;
	} else if (ntc_table[0] < NTC_40UA_MAX_MEASURE) {
		di->ntc_factor = NTC_CALC_FACTOR_40UA;
		di->ntc_uA = 40;
		buf |= ADC_CUR_40UA;
	} else {
		di->ntc_factor = NTC_CALC_FACTOR_20UA;
		di->ntc_uA = 20;
		buf |= ADC_CUR_20UA;
	}
	rk818_bat_write(di, TS_CTRL_REG, buf);

	/* ADC_TS1_EN */
	buf = rk818_bat_read(di, ADC_CTRL_REG);
	buf |= ADC_TS1_EN;
	rk818_bat_write(di, ADC_CTRL_REG, buf);
}

static void rk818_bat_init_ts2(struct battery_priv *di)
{
	u8 buf;

	if (!di->ts2_vol_multi)
		return;

	/* TS2 adc mode */
	buf = rk818_bat_read(di, TS_CTRL_REG);
	buf |= TS2_ADC_MODE;
	rk818_bat_write(di, TS_CTRL_REG, buf);

	/* TS2 adc enable */
	buf = rk818_bat_read(di, ADC_CTRL_REG);
	buf |= ADC_TS2_EN;
	rk818_bat_write(di, ADC_CTRL_REG, buf);
}

static int rk818_fg_init(struct battery_priv *di)
{
	int cap;

	rk818_bat_enable_gauge(di);
	rk818_bat_init_voltage_kb(di);
	rk818_bat_init_coffset(di);
	rk818_bat_init_ts1(di);
	rk818_bat_init_ts2(di);
	rk818_bat_clr_initialized_state(di);
	cap = rk818_bat_get_coulomb_cap(di);
	di->dsoc = rk818_bat_get_dsoc(di);
	di->rsoc = (cap + di->fcc / 200) * 100 / DIV(di->fcc);

	/* dsoc and rsoc maybe initialized here */
	rk818_bat_init_rsoc(di);

	rk818_bat_init_chrg_config(di);
	di->voltage_avg = rk818_bat_get_avg_voltage(di);
	di->voltage_ocv = rk818_bat_get_ocv_voltage(di);
	di->current_avg = rk818_bat_get_avg_current(di);
	di->sm_linek = rk818_bat_calc_linek(di);
	di->finish_chrg_base = get_timer(0);
	di->term_sig_base = get_timer(0);
	di->pwr_vol = di->voltage_avg;

	DBG("%s: dsoc=%d, rsoc=%d, v=%d, ov=%d, c=%d, estv=%d\n",
	    __func__, di->dsoc, di->rsoc, di->voltage_avg, di->voltage_ocv,
	    di->current_avg, rk818_bat_get_est_voltage(di));

	return 0;
}

static bool is_rk818_bat_exist(struct  battery_priv *di)
{
	return (rk818_bat_read(di, SUP_STS_REG) & BAT_EXS) ? true : false;
}

static void rk818_bat_set_current(struct battery_priv *di, int input_current)
{
	u8 usb_ctrl;

	usb_ctrl = rk818_bat_read(di, USB_CTRL_REG);
	usb_ctrl &= ~INPUT_CUR_MSK;
	usb_ctrl |= (input_current);
	rk818_bat_write(di, USB_CTRL_REG, usb_ctrl);
}

static int rk818_bat_get_ts2_voltage(struct battery_priv *di)
{
	u32 val = 0;

	val |= rk818_bat_read(di, RK818_TS2_ADC_REGL) << 0;
	val |= rk818_bat_read(di, RK818_TS2_ADC_REGH) << 8;

	/* refer voltage 2.2V, 12bit adc accuracy */
	val = val * 2200 * di->ts2_vol_multi / 4095;
	DBG("<%s>. ts2 voltage=%d\n", __func__, val);

	return val;
}

static void rk818_bat_ts2_update_current(struct battery_priv *di)
{
	int ts2_vol, input_current, invalid_cnt = 0, confirm_cnt = 0;

	rk818_bat_set_current(di, ILIM_450MA);
	input_current = ILIM_850MA;
	while (input_current < di->chrg_cur_input) {
		mdelay(100);
		ts2_vol = rk818_bat_get_ts2_voltage(di);
		DBG("******** ts2 vol=%d\n", ts2_vol);
		/* filter invalid voltage */
		if (ts2_vol <= TS2_VALID_VOL) {
			invalid_cnt++;
			DBG("%s: invalid ts2 voltage: %d\n, cnt=%d",
			    __func__, ts2_vol, invalid_cnt);
			if (invalid_cnt < TS2_CHECK_CNT)
				continue;

			/* if fail, set max input current as default */
			input_current = di->chrg_cur_input;
			rk818_bat_set_current(di, input_current);
			break;
		}

		/* update input current */
		if (ts2_vol >= TS2_THRESHOLD_VOL) {
			/* update input current */
			input_current++;
			rk818_bat_set_current(di, input_current);
			DBG("********* input=%d\n",
			    CHRG_CUR_INPUT[input_current & 0x0f]);
		} else {
			/* confirm lower threshold voltage */
			confirm_cnt++;
			if (confirm_cnt < TS2_CHECK_CNT) {
				DBG("%s: confirm ts2 voltage: %d\n, cnt=%d",
				    __func__, ts2_vol, confirm_cnt);
				continue;
			}

			/* trigger threshold, so roll back 1 step */
			input_current--;
			if (input_current == ILIM_80MA ||
			    input_current < 0)
				input_current = ILIM_450MA;
			rk818_bat_set_current(di, input_current);
			break;
		}
	}

	BAT_INFO("DC_CHARGER charge_cur_input=%d\n",
		 CHRG_CUR_INPUT[input_current]);
}

static void rk818_bat_charger_setting(struct battery_priv *di, int charger)
{
	static u8 old_charger = UNDEF_CHARGER;
	struct charge_animation_pdata *pdata;
	struct udevice *dev;
	int low_power_voltage = 0;

	uclass_find_first_device(UCLASS_CHARGE_DISPLAY, &dev);
	pdata = dev_get_platdata(dev);
	low_power_voltage = pdata->low_power_voltage;

	/* charger changed */
	if (old_charger != charger) {
		if (charger == NO_CHARGER) {
			BAT_INFO("NO_CHARGER\n");
			rk818_bat_set_current(di, ILIM_450MA);
		} else if (charger == USB_CHARGER) {
			BAT_INFO("USB_CHARGER\n");
			rk818_bat_set_current(di, ILIM_450MA);
		} else if (charger == DC_CHARGER || charger == AC_CHARGER) {
			if (pdata->uboot_charge && di->ts2_vol_multi) {
				rk818_bat_ts2_update_current(di);
			} else if ((rk818_bat_get_est_voltage(di) < low_power_voltage) &&
				   (di->ts2_vol_multi)) {
				rk818_bat_ts2_update_current(di);
			} else {
				rk818_bat_set_current(di, di->chrg_cur_input);
				BAT_INFO("DC_CHARGER\n");
			}
		} else {
			BAT_INFO("charger setting error %d\n", charger);
		}

		old_charger = charger;
	}
}

static int rk818_bat_get_dc_state(struct battery_priv *di)
{
	if (!di->dc_is_valid)
		return NO_CHARGER;

	return dm_gpio_get_value(&di->dc_det) ? DC_CHARGER : NO_CHARGER;
}

static int rk818_bat_get_charger_type(struct battery_priv *di)
{
	int charger_type = NO_CHARGER;

	/* check by ic hardware: this check make check work safer */
	if ((rk818_bat_read(di, VB_MON_REG) & PLUG_IN_STS) == 0)
		return NO_CHARGER;

	/* virtual or bat not exist */
	if (di->virtual_power)
		return DC_CHARGER;

	/* check DC firstly */
	charger_type = rk818_bat_get_dc_state(di);
	if (charger_type == DC_CHARGER)
		return charger_type;

	/* check USB secondly */
	return rk818_bat_get_usb_state(di);
}

static u8 rk818_bat_get_chrg_status(struct battery_priv *di)
{
	u8 status;

	status = rk818_bat_read(di, SUP_STS_REG) & BAT_STATUS_MSK;
	switch (status) {
	case CHARGE_OFF:
		DBG("CHARGE-OFF...\n");
		break;
	case DEAD_CHARGE:
		DBG("DEAD CHARGE...\n");
		break;
	case  TRICKLE_CHARGE:
		DBG("TRICKLE CHARGE...\n ");
		break;
	case  CC_OR_CV:
		DBG("CC or CV...\n");
		break;
	case  CHARGE_FINISH:
		DBG("CHARGE FINISH...\n");
		break;
	case  USB_OVER_VOL:
		DBG("USB OVER VOL...\n");
		break;
	case  BAT_TMP_ERR:
		DBG("BAT TMP ERROR...\n");
		break;
	case  TIMER_ERR:
		DBG("TIMER ERROR...\n");
		break;
	case  USB_EXIST:
		DBG("USB EXIST...\n");
		break;
	case  USB_EFF:
		DBG("USB EFF...\n");
		break;
	default:
		return -EINVAL;
	}

	return status;
}

static void rk818_bat_finish_chrg(struct battery_priv *di)
{
	u32 tgt_sec = 0;

	if (di->dsoc < 100) {
		tgt_sec = di->fcc * 3600 / 100 / FINISH_CALI_CURR;
		if (get_timer(di->finish_chrg_base) > SECONDS(tgt_sec)) {
			di->finish_chrg_base = get_timer(0);
			di->dsoc++;
		}
	}
	DBG("<%s>. sec=%d, finish_sec=%lu\n", __func__, SECONDS(tgt_sec),
	    get_timer(di->finish_chrg_base));
}

static void rk818_bat_debug_info(struct battery_priv *di)
{
	u8 sup_sts, ggcon, ggsts, vb_mod, rtc, thermal, misc;
	u8 usb_ctrl, chrg_ctrl1, chrg_ctrl2, chrg_ctrl3;
	static const char *name[] = {"NONE", "USB", "AC", "DC", "UNDEF"};

	if (!dbg_enable)
		return;
	ggcon = rk818_bat_read(di, GGCON_REG);
	ggsts = rk818_bat_read(di, GGSTS_REG);
	sup_sts = rk818_bat_read(di, SUP_STS_REG);
	usb_ctrl = rk818_bat_read(di, USB_CTRL_REG);
	thermal = rk818_bat_read(di, THERMAL_REG);
	vb_mod = rk818_bat_read(di, VB_MON_REG);
	misc = rk818_bat_read(di, MISC_MARK_REG);
	rtc = rk818_bat_read(di, SECONDS_REG);
	chrg_ctrl1 = rk818_bat_read(di, CHRG_CTRL_REG1);
	chrg_ctrl2 = rk818_bat_read(di, CHRG_CTRL_REG2);
	chrg_ctrl3 = rk818_bat_read(di, CHRG_CTRL_REG3);

	DBG("\n---------------------- DEBUG REGS ------------------------\n"
	    "GGCON=0x%2x, GGSTS=0x%2x, RTC=0x%2x, SUP_STS= 0x%2x\n"
	    "VB_MOD=0x%2x, USB_CTRL=0x%2x, THERMAL=0x%2x, MISC=0x%2x\n"
	    "CHRG_CTRL:REG1=0x%2x, REG2=0x%2x, REG3=0x%2x\n",
	    ggcon, ggsts, rtc, sup_sts, vb_mod, usb_ctrl,
	    thermal, misc, chrg_ctrl1, chrg_ctrl2, chrg_ctrl3
	    );
	DBG("----------------------------------------------------------\n"
	    "Dsoc=%d, Rsoc=%d, Vavg=%d, Iavg=%d, Cap=%d, Fcc=%d, d=%d\n"
	    "K=%d, old_cap=%d, charger=%s, Is=%d, Ip=%d, Vs=%d\n"
	    "min=%d, meet: soc=%d, calc: dsoc=%d, rsoc=%d, Vocv=%d\n"
	    "off: i=0x%x, c=0x%x, max=%d, ocv_c=%d, halt: st=%d, cnt=%d\n"
	    "pwr: dsoc=%d, rsoc=%d, vol=%d, Res=%d, mode=%s, T=%d'C\n",
	    di->dsoc, rk818_bat_get_rsoc(di), rk818_bat_get_avg_voltage(di),
	    rk818_bat_get_avg_current(di), di->remain_cap, di->fcc,
	    di->rsoc - di->dsoc,
	    di->sm_linek, di->sm_old_cap, name[di->chrg_type],
	    di->res_div * CHRG_CUR_SEL[chrg_ctrl1 & 0x0f],
	    CHRG_CUR_INPUT[usb_ctrl & 0x0f],
	    CHRG_VOL_SEL[(chrg_ctrl1 & 0x70) >> 4],  di->pwroff_min,
	    di->sm_meet_soc, di->calc_dsoc, di->calc_rsoc,
	    rk818_bat_get_ocv_voltage(di), rk818_bat_get_ioffset(di),
	    rk818_bat_get_coffset(di), di->is_max_soc_offset,
	    di->is_ocv_calib, di->is_halt, di->halt_cnt, di->pwr_dsoc,
	    di->pwr_rsoc, di->pwr_vol, di->sample_res,
	    di->virtual_power ? "VIRTUAL" : "BAT",
	    di->temperature
	    );
	rk818_bat_get_chrg_status(di);
	DBG("###########################################################\n");
}

static void rk818_bat_linek_algorithm(struct battery_priv *di)
{
	int delta_cap, ydsoc, tmp;
	u8 chg_st = rk818_bat_get_chrg_status(di);

	/* slow down */
	if (di->dsoc == 99)
		di->sm_linek = CHRG_FULL_K;
	else if (di->dsoc >= CHRG_TERM_DSOC && di->current_avg > TERM_CALI_CURR)
		di->sm_linek = CHRG_TERM_K;

	delta_cap = di->remain_cap - di->sm_old_cap;
	ydsoc = di->sm_linek * delta_cap * 100 / DIV(di->fcc);
	if (ydsoc > 0) {
		tmp = (di->sm_chrg_dsoc + 1) / 1000;
		if (tmp != di->dsoc)
			di->sm_chrg_dsoc = di->dsoc * 1000;
		di->sm_chrg_dsoc += ydsoc;
		di->dsoc = (di->sm_chrg_dsoc + 1) / 1000;
		di->sm_old_cap = di->remain_cap;
		if (di->dsoc == di->rsoc && di->sm_linek != CHRG_FULL_K &&
		    di->sm_linek != CHRG_TERM_K)
			di->sm_linek = 1000;
	}

	if ((di->sm_linek == 1000 || di->dsoc >= 100) &&
	    (chg_st != CHARGE_FINISH)) {
		if (di->sm_linek == 1000)
			di->dsoc = di->rsoc;
		di->sm_chrg_dsoc = di->dsoc * 1000;
	}

	DBG("linek=%d, sm_dsoc=%d, delta_cap=%d, ydsoc=%d, old_cap=%d\n"
	    "calc: dsoc=%d, rsoc=%d, meet=%d\n",
	    di->sm_linek, di->sm_chrg_dsoc, delta_cap, ydsoc, di->sm_old_cap,
	    di->calc_dsoc, di->calc_rsoc, di->sm_meet_soc);
}

static void rk818_bat_set_term_mode(struct battery_priv *di, int mode)
{
	u8 buf;

	buf = rk818_bat_read(di, CHRG_CTRL_REG3);
	buf &= ~CHRG_TERM_SIG_MSK;
	buf |= mode;
	rk818_bat_write(di, CHRG_CTRL_REG3, buf);

	DBG("set charge to %s term mode\n", mode ? "digital" : "analog");
}

static int rk818_bat_get_iadc(struct battery_priv *di)
{
	int val = 0;

	val |= rk818_bat_read(di, BAT_CUR_AVG_REGL) << 0;
	val |= rk818_bat_read(di, BAT_CUR_AVG_REGH) << 8;
	if (val > 2047)
		val -= 4096;

	return val;
}

static bool rk818_bat_adc_calib(struct battery_priv *di)
{
	int i, ioffset, coffset, adc;

	if (abs(di->current_avg) < ADC_CALIB_THRESHOLD)
		return false;

	for (i = 0; i < 5; i++) {
		adc = rk818_bat_get_iadc(di);
		coffset = rk818_bat_get_coffset(di);
		rk818_bat_set_coffset(di, coffset + adc);
		mdelay(200);
		adc = rk818_bat_get_iadc(di);
		if (abs(adc) < ADC_CALIB_THRESHOLD) {
			coffset = rk818_bat_get_coffset(di);
			ioffset = rk818_bat_get_ioffset(di);
			di->poffset = coffset - ioffset;
			rk818_bat_write(di, POFFSET_REG, di->poffset);
			BAT_INFO("new offset:c=0x%x, i=0x%x, p=0x%x\n",
				 coffset, ioffset, di->poffset);
			return true;
		} else {
			BAT_INFO("coffset calib again %d..\n", i);
			rk818_bat_set_coffset(di, coffset);
			mdelay(200);
		}
	}

	return false;
}

static void rk818_bat_smooth_charge(struct battery_priv *di)
{
	u8 chg_st = rk818_bat_get_chrg_status(di);

	/* set terminal charge mode */
	if (di->term_sig_base && get_timer(di->term_sig_base) > SECONDS(1)) {
		DBG("%s: terminal signal finish mode\n", __func__);
		rk818_bat_set_term_mode(di, CHRG_TERM_DIG_SIGNAL);
		di->term_sig_base = 0;
	}

	/* not charge mode and not keep in uboot charge: exit */
	if ((di->chrg_type == NO_CHARGER) ||
	    !rk818_bat_is_initialized(di)) {
		DBG("chrg=%d, initialized=%d\n", di->chrg_type,
		    rk818_bat_is_initialized(di));
		goto out;
	}

	/* update rsoc and remain cap */
	di->remain_cap = rk818_bat_get_coulomb_cap(di);
	di->rsoc = rk818_bat_get_rsoc(di);
	if (di->remain_cap > di->fcc) {
		di->sm_old_cap -= (di->remain_cap - di->fcc);
		rk818_bat_init_capacity(di, di->fcc);
		DBG("%s: init capacity: %d\n", __func__, di->fcc);
	}

	/* finish charge step */
	if (chg_st == CHARGE_FINISH) {
		DBG("%s: finish charge step...\n", __func__);
		if (di->adc_allow_update)
			di->adc_allow_update = !rk818_bat_adc_calib(di);
		rk818_bat_finish_chrg(di);
		rk818_bat_init_capacity(di, di->fcc);
	} else {
		DBG("%s: smooth charge step...\n", __func__);
		di->adc_allow_update = true;
		di->finish_chrg_base = get_timer(0);
		rk818_bat_linek_algorithm(di);
	}

	/* dsoc limit */
	if (di->dsoc > 100)
		di->dsoc = 100;
	else if (di->dsoc < 0)
		di->dsoc = 0;

	DBG("%s: save dsoc=%d and rsoc=%d\n",
	    __func__, di->dsoc, rk818_bat_get_rsoc(di));

	rk818_bat_save_dsoc(di, di->dsoc);
	rk818_bat_save_cap(di, di->remain_cap);
out:
	rk818_bat_debug_info(di);
}

/*
 * Due to hardware design issue, Vdelta = "(R_sample + R_other) * I_avg" will be
 * included into TS1 adc value. We must subtract it to get correct adc value.
 * The solution:
 *
 * (1) calculate Vdelta:
 *
 *   adc1 - Vdelta    ua1			  (adc2 * ua1) - (adc1 * ua2)
 *   ------------- = -----  ==> equals: Vdelta = -----------------------------
 *   adc2 - Vdelta    ua2				ua1 - ua2
 *
 *
 * (2) calculate correct ADC value:
 *
 *     charging: ADC = adc1 - abs(Vdelta);
 *  discharging: ADC = adc1 + abs(Vdelta);
 */
static int rk818_bat_get_ntc_res(struct battery_priv *di)
{
	static int adc1 = 0, adc2 = 0, ua1 = 0, ua2 = 0;
	static int adc1_update = 0, first_in = 1;
	static ulong seconds;
	int v_delta, val, res;
	u8 buf;

	/* hold adc1 and wait 1s for adc2 updated */
	if (!adc1_update) {
		/* update flag and init adc1,adc2 !! */
		adc1_update = 1;
		seconds = get_timer(0);
		adc1 = 0;
		adc2 = 0;

		/* read sample ua1 */
		buf = rk818_bat_read(di, TS_CTRL_REG);
		DBG("<%s>. read adc1, sample uA=%d\n",
		    __func__, ((buf & 0x03) + 1) * 20);

		/* read adc adc1 */
		ua1 = di->ntc_uA;
		adc1 |= rk818_bat_read(di, TS_ADC_REGL) << 0;
		adc1 |= rk818_bat_read(di, TS_ADC_REGH) << 8;

		/* chose reference UA for adc2 */
		ua2 = (ua1 != 20) ? 20 : 40;
		buf = rk818_bat_read(di, TS_CTRL_REG);
		buf &= ~ADC_CUR_MSK;
		buf |= ((ua2 - 20) / 20);
		rk818_bat_write(di, TS_CTRL_REG, buf);
	}

	/* wait 1s for adc2 updated */
	if (get_timer(seconds) < SECONDS(1)) {
		if (first_in)
			first_in = 0;
		else
			return TS1_NOT_READY;
	}

	/* update flags ! */
	adc1_update = 0;

	/* read sample ua2 */
	buf = rk818_bat_read(di, TS_CTRL_REG);
	DBG("<%s>. read adc2, sample uA=%d\n",
	    __func__, ((buf & 0x03) + 1) * 20);

	/* read adc adc2 */
	adc2 |= rk818_bat_read(di, TS_ADC_REGL) << 0;
	adc2 |= rk818_bat_read(di, TS_ADC_REGH) << 8;

	DBG("<%s>. ua1=%d, ua2=%d, adc1=%d, adc2=%d\n",
	    __func__, ua1, ua2, adc1, adc2);

	/* calculate delta voltage */
	if (adc2 != adc1)
		v_delta = abs((adc2 * ua1 - adc1 * ua2) / (ua2 - ua1));
	else
		v_delta = 0;

	/* considering current avg direction, calcuate real adc value */
	val = (di->current_avg >= 0) ? (adc1 - v_delta) : (adc1 + v_delta);

	DBG("<%s>. Iavg=%d, Vdelta=%d, Vadc=%d\n",
	    __func__, di->current_avg, v_delta, val);

	res = val * di->ntc_factor;

	DBG("<%s>. val=%d, ntc_res=%d, ntc_factor=%d\n",
	    __func__, val, res, di->ntc_factor);

	DBG("<%s>. t=[%d'C(%d) ~ %dC(%d)]\n", __func__,
	    di->ntc_degree_from, di->ntc_table[0],
	    di->ntc_degree_from + di->ntc_size - 1,
	    di->ntc_table[di->ntc_size - 1]);

	rk818_bat_init_ts1(di);

	return res;
}

static int rk818_bat_update_temperature(struct battery_priv *di)
{
	static int first_time = 1, old_temperature = 25;
	u32 ntc_size, *ntc_table;
	int i, res, temp;

	ntc_table = di->ntc_table;
	ntc_size = di->ntc_size;

	if (ntc_size) {
		res = rk818_bat_get_ntc_res(di);
		if (res == TS1_NOT_READY) {
			di->temperature = old_temperature;
			return TS1_NOT_READY;
		}

		if (res < ntc_table[ntc_size - 1]) {
			di->temperature = di->ntc_degree_from;
			old_temperature = di->ntc_degree_from;
			printf("bat ntc upper max degree: R=%d\n", res);
		} else if (res > ntc_table[0]) {
			di->temperature = di->ntc_degree_from + di->ntc_size - 1;
			old_temperature = di->ntc_degree_from + di->ntc_size - 1;
			printf("bat ntc lower min degree: R=%d\n", res);
		} else {
			for (i = 0; i < ntc_size; i++) {
				if (res >= ntc_table[i])
					break;
			}

			/* if first in, init old_temperature */
			temp = (i + di->ntc_degree_from);
			if (first_time) {
				di->temperature = temp;
				old_temperature = temp;
				first_time = 0;
			}

			old_temperature = temp;
			di->temperature = temp;
		}
	}

	DBG("temperature=%d\n", di->temperature);

	return 0;
}

static int rk818_bat_bat_is_exit(struct udevice *dev)
{
	struct battery_priv *di = dev_get_priv(dev);

	return is_rk818_bat_exist(di);
}

static int rk818_bat_update_get_soc(struct udevice *dev)
{
	struct battery_priv *di = dev_get_priv(dev);
	static ulong seconds, ts1_seconds;
	int wait;

	/* set charge current */
	di->chrg_type =
		rk818_bat_get_charger_type(di);
	rk818_bat_charger_setting(di, di->chrg_type);

	/* fg calc every 5 seconds */
	if (!seconds || !ts1_seconds) {
		seconds = get_timer(0);
		ts1_seconds = get_timer(0);
	}

	/* temperature calc every 5 seconds */
	if (get_timer(ts1_seconds) >= SECONDS(5)) {
		DBG("%s: update temperature\n", __func__);
		wait = rk818_bat_update_temperature(di);
		if (!wait)
			ts1_seconds = get_timer(0);
	}

	if (get_timer(seconds) >= SECONDS(5)) {
		DBG("%s: smooth charge\n", __func__);
		seconds = get_timer(0);
		rk818_bat_smooth_charge(di);
	}

	/* bat exist, fg init success(dts pass) and uboot charge: report data */
	if (!di->virtual_power && di->voltage_k)
		return di->dsoc;
	else
		return VIRTUAL_POWER_SOC;
}

static int rk818_bat_update_get_current(struct udevice *dev)
{
	struct battery_priv *di = dev_get_priv(dev);

	if (!di->virtual_power && di->voltage_k)
		return rk818_bat_get_avg_current(di);
	else
		return VIRTUAL_POWER_CUR;
}

static int rk818_bat_update_get_voltage(struct udevice *dev)
{
	struct battery_priv *di = dev_get_priv(dev);

	if (!di->virtual_power && di->voltage_k)
		return rk818_bat_get_est_voltage(di);
	else
		return VIRTUAL_POWER_VOL;
}

static bool rk818_bat_update_get_chrg_online(struct udevice *dev)
{
	struct battery_priv *di = dev_get_priv(dev);

	return rk818_bat_get_charger_type(di);
}

static struct dm_fuel_gauge_ops fg_ops = {
	.bat_is_exist = rk818_bat_bat_is_exit,
	.get_soc = rk818_bat_update_get_soc,
	.get_voltage = rk818_bat_update_get_voltage,
	.get_current = rk818_bat_update_get_current,
	.get_chrg_online = rk818_bat_update_get_chrg_online,
};

static int rk818_fg_ofdata_to_platdata(struct udevice *dev)
{
	struct rk8xx_priv *rk8xx = dev_get_priv(dev->parent);
	struct battery_priv *di = dev_get_priv(dev);
	u32 sign, degree_from[2];
	const char *prop;
	int len, ret;

	if (rk8xx->variant != 0x8180) {
		debug("%s: Not support pmic variant: rk%x\n",
		      __func__, rk8xx->variant);
		return -EINVAL;
	} else {
		di->dev = dev;
	}

	/* Parse ocv table */
	prop = dev_read_prop(dev, "ocv_table", &len);
	if (!prop) {
		printf("can't find ocv_table prop\n");
		return -EINVAL;
	}

	di->ocv_table = calloc(len, 1);
	if (!di->ocv_table) {
		printf("can't calloc ocv_table\n");
		return -ENOMEM;
	}

	di->ocv_size = len / 4;
	if (dev_read_u32_array(dev, "ocv_table",
			       di->ocv_table, di->ocv_size)) {
		printf("can't read ocv_table\n");
		free(di->ocv_table);
		return -EINVAL;
	}

	/* Parse neccessay */
	di->design_cap = dev_read_u32_default(dev, "design_capacity", -1);
	if (di->design_cap < 0) {
		printf("can't read design_capacity\n");
		return -EINVAL;
	}

	di->qmax = dev_read_u32_default(dev, "design_qmax", -1);
	if (di->qmax < 0) {
		printf("can't read design_qmax\n");
		return -EINVAL;
	}

	/* Parse un-neccessay */
	di->dts_vol_sel = dev_read_u32_default(dev, "max_chrg_voltage", 4200);
	if (di->dts_vol_sel < 0)
		di->dts_vol_sel = dev_read_u32_default(dev,
						"max_charge_voltagemV", 4200);

	di->dts_cur_input = dev_read_u32_default(dev, "max_input_current", 2000);
	if (di->dts_cur_input < 0)
		di->dts_cur_input = dev_read_u32_default(dev,
						"max_input_currentmA", 2000);

	di->dts_cur_sel = dev_read_u32_default(dev, "max_chrg_current", 1200);
	if (di->dts_cur_sel < 0)
		di->dts_cur_sel = dev_read_u32_default(dev,
						"max_chrg_currentmA", 1400);

	di->max_soc_offset = dev_read_u32_default(dev, "max_soc_offset", 70);
	di->virtual_power = dev_read_u32_default(dev, "virtual_power", 0);
	di->bat_res = dev_read_u32_default(dev, "bat_res", 135);
	di->sample_res = dev_read_u32_default(dev, "sample_res", SAMPLE_RES_20mR);
	di->ts2_vol_multi = dev_read_u32_default(dev, "ts2_vol_multi", 0);

	di->res_div = (di->sample_res == SAMPLE_RES_20mR) ?
				SAMPLE_RES_DIV1 : SAMPLE_RES_DIV2;

	ret = gpio_request_by_name_nodev(dev_ofnode(dev), "dc_det_gpio",
					 0, &di->dc_det, GPIOD_IS_IN);
	if (!ret) {
		di->dc_is_valid = 1;
		debug("DC is valid\n");
	} else {
		debug("DC is invalid, ret=%d\n", ret);
	}

	prop = dev_read_prop(dev, "ntc_table", &len);
	if (!prop) {
		di->ntc_size = 0;
	} else {
		ret = dev_read_u32_array(dev, "ntc_degree_from",
					 degree_from, ARRAY_SIZE(degree_from));
		if (ret < 0) {
			printf("invalid ntc_degree_from\n");
			return -EINVAL;
		}

		sign = degree_from[0];
		di->ntc_degree_from = degree_from[1];
		if (sign)
			di->ntc_degree_from = -di->ntc_degree_from;

		di->ntc_size = len / sizeof(u32);
	}

	if (di->ntc_size) {
		di->ntc_table = calloc(len, 1);
		if (!di->ntc_table) {
			printf("calloc ocv_table fail\n");
			return -ENOMEM;
		}

		ret = dev_read_u32_array(dev, "ntc_table",
					 di->ntc_table, di->ntc_size);
		if (ret < 0) {
			printf("read ntc_table array failed\n");
			return ret;
		}
	}

	/* Is battery attached */
	if (!is_rk818_bat_exist(di))
		di->virtual_power = 1;

	DBG("-------------------------------:\n");
	DBG("max_input_current:%d\n", di->dts_cur_input);
	DBG("max_chrg_current:%d\n", di->dts_cur_sel);
	DBG("max_chrg_voltage:%d\n", di->dts_vol_sel);
	DBG("design_capacity :%d\n", di->design_cap);
	DBG("design_qmax:%d\n", di->qmax);
	DBG("max_soc_offset:%d\n", di->max_soc_offset);
	DBG("sample_res:%d\n", di->sample_res);
	DBG("virtual_power:%d\n", di->virtual_power);
	DBG("ts2_vol_multi:%d\n", di->ts2_vol_multi);
	DBG("dc det: %d\n", di->dc_is_valid);
	DBG("ntc_size:%d\n", di->ntc_size);
	DBG("ntc_degree_from:%d\n", di->ntc_degree_from);
	DBG("ntc_degree_to:%d\n", di->ntc_degree_from + di->ntc_size - 1);

	return 0;
}

static int rk818_fg_probe(struct udevice *dev)
{
	struct rk8xx_priv *rk8xx = dev_get_priv(dev->parent);
	struct battery_priv *di = dev_get_priv(dev);

	if (rk8xx->variant != 0x8180) {
		printf("Not support pmic variant: rk%x\n", rk8xx->variant);
		return -EINVAL;
	}

	return rk818_fg_init(di);
}

U_BOOT_DRIVER(rk818_fg) = {
	.name = "rk818_fg",
	.id = UCLASS_FG,
	.probe = rk818_fg_probe,
	.ops = &fg_ops,
	.ofdata_to_platdata = rk818_fg_ofdata_to_platdata,
	.priv_auto_alloc_size = sizeof(struct battery_priv),
};
