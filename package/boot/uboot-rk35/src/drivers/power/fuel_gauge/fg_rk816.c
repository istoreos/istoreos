/*
 * (C) Copyright 2017 Rockchip Electronics Co., Ltd
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */

/* #include <adc.h> */
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

#define BAT_INFO(fmt, args...) printf("rk816-bat: "fmt, ##args)

#define DRIVER_VERSION		"2.0"

/* THERMAL_REG */
#define TEMP_115C		(0x03 << 2)
#define FB_TEMP_MSK		0x0c

/* CHRG_CTRL_REG2*/
#define FINISH_100MA		(0x00 << 6)
#define FINISH_150MA		(0x01 << 6)
#define FINISH_200MA		(0x02 << 6)
#define FINISH_250MA		(0x03 << 6)
#define FINISH_CUR_MSK		0xc7

/* CHRG_CTRL_REG3*/
#define CHRG_TERM_DIG_SIGNAL	(1 << 5)
#define CHRG_TIMER_CCCV_EN	(1 << 2)

/* CHRG_CTRL_REG */
#define ILIM_450MA		(0x00)
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
#define VOL_AVG_MASK		(1 << 0)

/* TS_CTRL_REG */
#define GG_EN			(1 << 7)

/* CHRG_USB_CTRL*/
#define CHRG_EN			(1 << 7)

/* BAT_CTRL_REG */
#define USB_SYS_EN		(1 << 6)

/*SUP_STS_REG*/
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

/* DC ADC */
#define FG_INIT			(1 << 3)
#define FG_RESET_LATE		(1 << 1)
#define FG_RESET_NOW		(1 << 0)
#define CHRG_TERM_DSOC		90
#define CHRG_TERM_K		650
#define CHRG_FULL_K		400
#define ADC_CALIB_THRESHOLD	4
#define DC_ADC_TRIGGER		150
#define DIV(x)			((x) ? (x) : 1)

#define SAMPLE_RES_20MR		20

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
	u32		qmax;
	int		remain_cap;
	u32		design_cap;
	int		nac;
	u32		*ocv_table;
	u32		ocv_size;
	int		virtual_power;
	int		sample_res;
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
	struct gpio_desc dc_det;
	int		dc_type;
	int		dc_det_adc;
	ulong		vol_mode_base;
	ulong		finish_chrg_base;
	u8		calc_dsoc;
	u8		calc_rsoc;
	int		sm_meet_soc;
	u8		halt_cnt;
	bool		is_halt;
	bool		is_ocv_calib;
	bool		is_max_soc_offset;
	bool		is_first_power_on;
	bool		is_sw_reset;
	int		pwr_dsoc;
	int		pwr_rsoc;
	int		pwr_vol;
	int		res_fac;
	int		over_20mR;
};

enum charger_type {
	NO_CHARGER = 0,
	USB_CHARGER,
	AC_CHARGER,
	DC_CHARGER,
	UNDEF_CHARGER,
};

enum dc_type {
	DC_TYPE_OF_NONE = 0,
	DC_TYPE_OF_GPIO,
	DC_TYPE_OF_ADC,
};

static const char *charger_type_to_name[] = {
	"NONE",
	"USB",
	"AC",
	"DC",
	"UNKN",
};

/*
 * If sample resistor changes, we need caculate a new CHRG_CUR_SEL[] table.
 *
 * Calculation method:
 * 1. find 20mR(default) current charge table, that is:
 *	20mR: [1000, 1200, 1400, 1600, 1800, 2000, 2250, 2400]
 *
 * 2. caculate Rfac(not care much, just using it) by sample resistor(ie. Rsam);
 *	Rsam = 20mR: Rfac = 10;
 *	Rsam > 20mR: Rfac = Rsam * 10 / 20;
 *	Rsam < 20mR: Rfac = 20 * 10 / Rsam;
 *
 * 3. from step2, we get Rfac, then we can get new charge current table by 20mR
 *    charge table:
 *	Iorg: member from 20mR charge table; Inew: new member for charge table.
 *
 *	Rsam > 20mR: Inew = Iorg * 10 / Rfac;
 *	Rsam < 20mR: Inew = Iorg * Rfac / 10;
 *
 * Notice: Inew should round up if it is not a integer!!!
 *
 * Example:
 *	10mR: [2000, 2400, 2800, 3200, 3600, 4000, 4500, 4800]
 *	20mR: [1000, 1200, 1400, 1600, 1800, 2000, 2250, 2400]
 *	40mR: [500,  600,  700,  800,  900,  1000, 1125, 1200]
 *	50mR: [400,  480,  560,  640,  720,  800,  900,  960]
 *	60mR: [334,  400,  467,  534,  600,  667,  750,  800]
 *
 * You should add property 'sample_res = <Rsam>' at battery node.
 */
static const u32 CHRG_VOL_SEL[] = {
	4050, 4100, 4150, 4200, 4250, 4300, 4350
};

static const u32 CHRG_CUR_SEL[] = {
	1000, 1200, 1400, 1600, 1800, 2000, 2250, 2400
};

static const u32 CHRG_CUR_INPUT[] = {
	450, 800, 850, 1000, 1250, 1500, 1750, 2000
};

/* 'res_fac' has been *10, so we need divide 10 */
#define RES_FAC_MUX(value, res_fac)    ((value) * res_fac / 10)

/* 'res_fac' has been *10, so we need 'value * 10' before divide 'res_fac' */
#define RES_FAC_DIV(value, res_fac)    ((value) * 10 / res_fac)

static int rk816_bat_read(struct battery_priv *di, u8 reg)
{
	return pmic_reg_read(di->dev->parent, reg);
}

static void rk816_bat_write(struct battery_priv *di, u8 reg, u8 buf)
{
	pmic_reg_write(di->dev->parent, reg, buf);
}

static int rk816_bat_dwc_otg_check_dpdm(void)
{
#if defined(CONFIG_PHY_ROCKCHIP_INNO_USB2) && !defined(CONFIG_SPL_BUILD)
	return rockchip_chg_get_type();
#else
	BAT_INFO("rockchip_chg_get_type() is not implement\n");
	return NO_CHARGER;
#endif
}

static int rk816_bat_get_rsoc(struct battery_priv *di)
{
	return (di->remain_cap + di->fcc / 200) * 100 / DIV(di->fcc);
}

static int rk816_bat_get_dsoc(struct  battery_priv *di)
{
	return rk816_bat_read(di, SOC_REG);
}

static void rk816_bat_enable_input_current(struct battery_priv *di)
{
	u8 val;

	val = rk816_bat_read(di, BAT_CTRL_REG);
	val |= USB_SYS_EN;
	rk816_bat_write(di, BAT_CTRL_REG, val);
}

static void rk816_bat_enable_gauge(struct battery_priv *di)
{
	u8 val;

	val = rk816_bat_read(di, TS_CTRL_REG);
	val |= GG_EN;
	rk816_bat_write(di, TS_CTRL_REG, val);
}

static void rk816_bat_set_vol_instant_mode(struct battery_priv *di)
{
	u8 val;

	val = rk816_bat_read(di, GGSTS_REG);
	val |= VOL_INSTANT;
	rk816_bat_write(di, GGSTS_REG, val);
}

static void rk816_bat_set_vol_avg_mode(struct battery_priv *di)
{
	u8 val;

	val = rk816_bat_read(di, GGSTS_REG);
	val &= ~VOL_AVG_MASK;
	val |= VOL_AVG;
	rk816_bat_write(di, GGSTS_REG, val);
}

static int rk816_bat_get_vcalib0(struct battery_priv *di)
{
	int val = 0;

	val |= rk816_bat_read(di, VCALIB0_REGL) << 0;
	val |= rk816_bat_read(di, VCALIB0_REGH) << 8;

	return val;
}

static int rk816_bat_get_vcalib1(struct battery_priv *di)
{
	int val = 0;

	val |= rk816_bat_read(di, VCALIB1_REGL) << 0;
	val |= rk816_bat_read(di, VCALIB1_REGH) << 8;

	return val;
}

static void rk816_bat_set_coffset(struct battery_priv *di, int val)
{
	u8 buf;

	buf = (val >> 0) & 0xff;
	rk816_bat_write(di, CAL_OFFSET_REGL, buf);
	buf = (val >> 8) & 0xff;
	rk816_bat_write(di, CAL_OFFSET_REGH, buf);
}

static int rk816_bat_get_ioffset(struct battery_priv *di)
{
	int val = 0;

	val |= rk816_bat_read(di, IOFFSET_REGL) << 0;
	val |= rk816_bat_read(di, IOFFSET_REGH) << 8;

	return val;
}

static void rk816_bat_save_dsoc(struct  battery_priv *di, u8 save_soc)
{
	static int old_soc = -1;

	if (old_soc != save_soc) {
		old_soc = save_soc;
		rk816_bat_write(di, SOC_REG, save_soc);
	}
}

static void rk816_bat_save_cap(struct battery_priv *di, int cap)
{
	u8 buf;
	static int old_cap;

	if (old_cap == cap)
		return;

	if (cap >= di->qmax)
		cap = di->qmax;

	old_cap = cap;
	buf = (cap >> 24) & 0xff;
	rk816_bat_write(di, REMAIN_CAP_REG3, buf);
	buf = (cap >> 16) & 0xff;
	rk816_bat_write(di, REMAIN_CAP_REG2, buf);
	buf = (cap >> 8) & 0xff;
	rk816_bat_write(di, REMAIN_CAP_REG1, buf);
	buf = (cap >> 0) & 0xff;
	rk816_bat_write(di, REMAIN_CAP_REG0, buf);
}

static void rk816_bat_init_voltage_kb(struct battery_priv *di)
{
	int vcalib0, vcalib1;

	vcalib0 = rk816_bat_get_vcalib0(di);
	vcalib1 = rk816_bat_get_vcalib1(di);
	di->voltage_k = (4200 - 3000) * 1000 / DIV(vcalib1 - vcalib0);
	di->voltage_b = 4200 - (di->voltage_k * vcalib1) / 1000;
	DBG("%s. vk=%d, vb=%d\n", __func__, di->voltage_k, di->voltage_b);
}

static int rk816_bat_get_ocv_voltage(struct battery_priv *di)
{
	int vol, val = 0;

	val |= rk816_bat_read(di, BAT_OCV_REGL) << 0;
	val |= rk816_bat_read(di, BAT_OCV_REGH) << 8;
	vol = di->voltage_k * val / 1000 + di->voltage_b;
	vol = vol * 1100 / 1000;

	return vol;
}

static int rk816_bat_get_avg_current(struct battery_priv *di)
{
	int cur, val = 0;

	val |= rk816_bat_read(di, BAT_CUR_AVG_REGL) << 0;
	val |= rk816_bat_read(di, BAT_CUR_AVG_REGH) << 8;

	if (val & 0x800)
		val -= 4096;
	if (!di->over_20mR)
		cur = RES_FAC_MUX(val * 1506, di->res_fac) / 1000;
	else
		cur = RES_FAC_DIV(val * 1506, di->res_fac) / 1000;

	return cur;
}

static int rk816_bat_get_avg_voltage(struct battery_priv *di)
{
	int vol, val = 0;

	val |= rk816_bat_read(di, BAT_VOL_REGL) << 0;
	val |= rk816_bat_read(di, BAT_VOL_REGH) << 8;
	vol = di->voltage_k * val / 1000 + di->voltage_b;
	vol = vol * 1100 / 1000;

	return vol;
}

static int rk816_bat_get_est_voltage(struct battery_priv *di)
{
	int est_vol, vol, curr;

	vol = rk816_bat_get_avg_voltage(di);
	curr = rk816_bat_get_avg_current(di);
	est_vol = vol - (di->bat_res * curr / 1000);

	return (est_vol > 2800) ? est_vol : vol;
}

static u8 rk816_bat_finish_ma(struct battery_priv *di, int fcc)
{
	u8 ma;

	if (fcc > 5000)
		ma = FINISH_250MA;
	else if (fcc >= 4000)
		ma = FINISH_200MA;
	else if (fcc >= 3000)
		ma = FINISH_150MA;
	else
		ma = FINISH_100MA;

	/* adjust ma according to sample resistor */
	if (di->sample_res < 20) {
		/* ma should div 2 */
		if (ma == FINISH_200MA)
			ma = FINISH_100MA;
		else if (ma == FINISH_250MA)
			ma = FINISH_150MA;
	} else if (di->sample_res > 20) {
		/* ma should mux 2 */
		if (ma == FINISH_100MA)
			ma = FINISH_200MA;
		else if (ma == FINISH_150MA)
			ma = FINISH_250MA;
	}

	return ma;
}

static void rk816_bat_select_chrg_cv(struct battery_priv *di)
{
	int index, chrg_vol_sel, chrg_cur_sel, chrg_cur_input;

	chrg_vol_sel = di->dts_vol_sel;
	chrg_cur_sel = di->dts_cur_sel;
	chrg_cur_input = di->dts_cur_input;

	if (di->sample_res < 20) {
		if (chrg_cur_sel > 2000)
			chrg_cur_sel = RES_FAC_DIV(chrg_cur_sel, di->res_fac);
		else
			chrg_cur_sel = 1000;
	} else if (di->sample_res > 20) {
		chrg_cur_sel = RES_FAC_MUX(chrg_cur_sel, di->res_fac);
		if (chrg_cur_sel > 2400)
			chrg_cur_sel = 2400;
		if (chrg_cur_sel < 1000)
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

static void rk816_bat_init_chrg_config(struct battery_priv *di)
{
	u8 chrg_ctrl1, usb_ctrl, chrg_ctrl2, chrg_ctrl3;
	u8 sup_sts, ggcon, thermal, finish_ma;

	rk816_bat_select_chrg_cv(di);
	finish_ma = rk816_bat_finish_ma(di, di->fcc);

	ggcon = rk816_bat_read(di, GGCON_REG);
	sup_sts = rk816_bat_read(di, SUP_STS_REG);
	usb_ctrl = rk816_bat_read(di, USB_CTRL_REG);
	thermal = rk816_bat_read(di, THERMAL_REG);
	chrg_ctrl2 = rk816_bat_read(di, CHRG_CTRL_REG2);
	chrg_ctrl3 = rk816_bat_read(di, CHRG_CTRL_REG3);

	/* set charge current and voltage */
	usb_ctrl &= ~INPUT_CUR_MSK;
	usb_ctrl |= di->chrg_cur_input;
	chrg_ctrl1 = (CHRG_EN | di->chrg_vol_sel | di->chrg_cur_sel);

	/* digital signal and finish current*/
	chrg_ctrl3 |= CHRG_TERM_DIG_SIGNAL;
	chrg_ctrl2 &= ~FINISH_CUR_MSK;
	chrg_ctrl2 |= finish_ma;

	/* cccv mode */
	chrg_ctrl3 &= ~CHRG_TIMER_CCCV_EN;

	/* enable voltage limit and enable input current limit */
	sup_sts |= USB_VLIMIT_EN;
	sup_sts |= USB_CLIMIT_EN;

	/* set feedback temperature */
	usb_ctrl |= CHRG_CT_EN;
	thermal &= ~FB_TEMP_MSK;
	thermal |= TEMP_115C;

	/* adc current mode */
	ggcon |= ADC_CUR_MODE;

	rk816_bat_write(di, GGCON_REG, ggcon);
	rk816_bat_write(di, SUP_STS_REG, sup_sts);
	rk816_bat_write(di, USB_CTRL_REG, usb_ctrl);
	rk816_bat_write(di, THERMAL_REG, thermal);
	rk816_bat_write(di, CHRG_CTRL_REG1, chrg_ctrl1);
	rk816_bat_write(di, CHRG_CTRL_REG2, chrg_ctrl2);
	rk816_bat_write(di, CHRG_CTRL_REG3, chrg_ctrl3);
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

static int rk816_bat_vol_to_cap(struct battery_priv *di, int voltage)
{
	u32 *ocv_table, tmp;
	int ocv_size, ocv_cap;

	ocv_table = di->ocv_table;
	ocv_size = di->ocv_size;
	tmp = interpolate(voltage, ocv_table, ocv_size);
	ocv_cap = ab_div_c(tmp, di->fcc, MAX_INTERPOLATE);

	return ocv_cap;
}

static int rk816_bat_vol_to_soc(struct battery_priv *di, int voltage)
{
	u32 *ocv_table, tmp;
	int ocv_size, ocv_soc;

	ocv_table = di->ocv_table;
	ocv_size = di->ocv_size;
	tmp = interpolate(voltage, ocv_table, ocv_size);
	ocv_soc = ab_div_c(tmp, MAX_PERCENTAGE, MAX_INTERPOLATE);

	return ocv_soc;
}

static int rk816_bat_get_prev_cap(struct battery_priv *di)
{
	int val = 0;

	val |= rk816_bat_read(di, REMAIN_CAP_REG3) << 24;
	val |= rk816_bat_read(di, REMAIN_CAP_REG2) << 16;
	val |= rk816_bat_read(di, REMAIN_CAP_REG1) << 8;
	val |= rk816_bat_read(di, REMAIN_CAP_REG0) << 0;

	return val;
}

static void rk816_bat_save_fcc(struct battery_priv *di, u32 cap)
{
	u8 buf;

	buf = (cap >> 24) & 0xff;
	rk816_bat_write(di, NEW_FCC_REG3, buf);
	buf = (cap >> 16) & 0xff;
	rk816_bat_write(di, NEW_FCC_REG2, buf);
	buf = (cap >> 8) & 0xff;
	rk816_bat_write(di, NEW_FCC_REG1, buf);
	buf = (cap >> 0) & 0xff;
	rk816_bat_write(di, NEW_FCC_REG0, buf);
}

static int rk816_bat_get_fcc(struct battery_priv *di)
{
	int val = 0;

	val |= rk816_bat_read(di, NEW_FCC_REG3) << 24;
	val |= rk816_bat_read(di, NEW_FCC_REG2) << 16;
	val |= rk816_bat_read(di, NEW_FCC_REG1) << 8;
	val |= rk816_bat_read(di, NEW_FCC_REG0) << 0;

	if (val < MIN_FCC)
		val = di->design_cap;
	else if (val > di->qmax)
		val = di->qmax;

	return val;
}

static u8 rk816_bat_get_pwroff_min(struct battery_priv *di)
{
	u8 cur, last;

	cur = rk816_bat_read(di, NON_ACT_TIMER_CNT_REG);
	last = rk816_bat_read(di, NON_ACT_TIMER_CNT_SAVE_REG);
	rk816_bat_write(di, NON_ACT_TIMER_CNT_SAVE_REG, cur);

	return (cur != last) ? cur : 0;
}

static int rk816_bat_get_coulomb_cap(struct battery_priv *di)
{
	int cap, val = 0;

	val |= rk816_bat_read(di, GASCNT_REG3) << 24;
	val |= rk816_bat_read(di, GASCNT_REG2) << 16;
	val |= rk816_bat_read(di, GASCNT_REG1) << 8;
	val |= rk816_bat_read(di, GASCNT_REG0) << 0;

	if (!di->over_20mR)
		cap = RES_FAC_MUX(val / 2390, di->res_fac);
	else
		cap = RES_FAC_DIV(val / 2390, di->res_fac);

	return cap;
}

static void rk816_bat_init_capacity(struct battery_priv *di, u32 capacity)
{
	u8 buf;
	u32 cap;
	int delta;

	delta = capacity - di->remain_cap;
	if (!delta)
		return;

	if (!di->over_20mR)
		cap = RES_FAC_DIV(capacity * 2390, di->res_fac);
	else
		cap = RES_FAC_MUX(capacity * 2390, di->res_fac);

	buf = (cap >> 24) & 0xff;
	rk816_bat_write(di, GASCNT_CAL_REG3, buf);
	buf = (cap >> 16) & 0xff;
	rk816_bat_write(di, GASCNT_CAL_REG2, buf);
	buf = (cap >> 8) & 0xff;
	rk816_bat_write(di, GASCNT_CAL_REG1, buf);
	buf = (cap >> 0) & 0xff;
	rk816_bat_write(di, GASCNT_CAL_REG0, buf);
	udelay(75);
	di->remain_cap = rk816_bat_get_coulomb_cap(di);
	di->rsoc = rk816_bat_get_rsoc(di);
}

static bool is_rk816_bat_ocv_valid(struct battery_priv *di)
{
	return di->pwroff_min >= 30 ? true : false;
}

static int rk816_bat_get_usb_state(struct battery_priv *di)
{
	int charger_type;

	switch (rk816_bat_dwc_otg_check_dpdm()) {
	case 0:
		if ((rk816_bat_read(di, VB_MON_REG) & PLUG_IN_STS) != 0)
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

static void rk816_bat_clr_initialized_state(struct battery_priv *di)
{
	u8 val;

	val = rk816_bat_read(di, MISC_MARK_REG);
	val &= ~FG_INIT;
	rk816_bat_write(di, MISC_MARK_REG, val);
}

static bool rk816_bat_is_initialized(struct battery_priv *di)
{
	return (rk816_bat_read(di, MISC_MARK_REG) & FG_INIT) ? true : false;
}

static void rk816_bat_set_initialized_state(struct battery_priv *di)
{
	u8 val;

	val = rk816_bat_read(di, MISC_MARK_REG);
	if (rk816_bat_get_usb_state(di) != NO_CHARGER) {
		val |= FG_INIT;
		rk816_bat_write(di, MISC_MARK_REG, val);
		BAT_INFO("fuel gauge initialized... estv=%d, ch=%d\n",
			 rk816_bat_get_est_voltage(di),
			 rk816_bat_get_usb_state(di));
	}
}

static void rk816_bat_first_pwron(struct battery_priv *di)
{
	int ocv_vol;

	rk816_bat_save_fcc(di, di->design_cap);
	ocv_vol = rk816_bat_get_ocv_voltage(di);
	di->fcc = rk816_bat_get_fcc(di);
	di->nac = rk816_bat_vol_to_cap(di, ocv_vol);
	di->rsoc = rk816_bat_vol_to_soc(di, ocv_vol);
	di->dsoc = di->rsoc;
	rk816_bat_init_capacity(di, di->nac);
	rk816_bat_set_initialized_state(di);

	BAT_INFO("first power on: soc=%d\n", di->dsoc);
}

static u8 rk816_bat_get_halt_cnt(struct battery_priv *di)
{
	return rk816_bat_read(di, HALT_CNT_REG);
}

static void rk816_bat_inc_halt_cnt(struct battery_priv *di)
{
	u8 cnt;

	cnt = rk816_bat_read(di, HALT_CNT_REG);
	rk816_bat_write(di, HALT_CNT_REG, ++cnt);
}

static bool is_rk816_bat_last_halt(struct battery_priv *di)
{
	int pre_cap = rk816_bat_get_prev_cap(di);
	int now_cap = rk816_bat_get_coulomb_cap(di);

	/* over 5%: system halt last time */
	if (abs(now_cap - pre_cap) > (di->fcc / 20)) {
		rk816_bat_inc_halt_cnt(di);
		return true;
	} else {
		return false;
	}
}

static void rk816_bat_not_first_pwron(struct battery_priv *di)
{
	int pre_soc, pre_cap, ocv_cap, ocv_soc, ocv_vol, now_cap;

	di->fcc = rk816_bat_get_fcc(di);
	pre_soc = rk816_bat_get_dsoc(di);
	pre_cap = rk816_bat_get_prev_cap(di);
	now_cap = rk816_bat_get_coulomb_cap(di);
	di->pwr_dsoc = pre_soc;
	di->pwr_rsoc = (now_cap + di->fcc / 200) * 100 / DIV(di->fcc);
	di->is_halt = is_rk816_bat_last_halt(di);
	di->halt_cnt = rk816_bat_get_halt_cnt(di);
	di->is_ocv_calib = is_rk816_bat_ocv_valid(di);

	if (di->is_halt) {
		BAT_INFO("system halt last time... cap: pre=%d, now=%d\n",
			 pre_cap, now_cap);
		if (now_cap < 0)
			now_cap = 0;
		rk816_bat_init_capacity(di, now_cap);
		pre_cap = di->remain_cap;
		pre_soc = di->rsoc;
		goto finish;
	} else if (di->is_ocv_calib) {
		ocv_vol = rk816_bat_get_ocv_voltage(di);
		ocv_soc = rk816_bat_vol_to_soc(di, ocv_vol);
		ocv_cap = rk816_bat_vol_to_cap(di, ocv_vol);
		pre_cap = ocv_cap;
		BAT_INFO("do ocv calib.. rsoc=%d\n", ocv_soc);

		if (abs(ocv_soc - pre_soc) >= di->max_soc_offset) {
			BAT_INFO("trigger max soc offset, soc: %d -> %d\n",
				 pre_soc, ocv_soc);
			pre_soc = ocv_soc;
			di->is_max_soc_offset = true;
		}
		BAT_INFO("OCV calib: cap=%d, rsoc=%d\n", ocv_cap, ocv_soc);
	}
finish:
	di->dsoc = pre_soc;
	di->nac = pre_cap;
	rk816_bat_init_capacity(di, di->nac);
	rk816_bat_set_initialized_state(di);
	BAT_INFO("dl=%d rl=%d cap=%d m=%d v=%d ov=%d c=%d pl=%d ch=%d Ver=%s\n",
		 di->dsoc, di->rsoc, di->remain_cap, di->pwroff_min,
		 rk816_bat_get_avg_voltage(di), rk816_bat_get_ocv_voltage(di),
		 rk816_bat_get_avg_current(di), rk816_bat_get_dsoc(di),
		 rk816_bat_get_usb_state(di), DRIVER_VERSION
		 );
}

static bool is_rk816_bat_first_poweron(struct battery_priv *di)
{
	u8 buf;

	buf = rk816_bat_read(di, GGSTS_REG);
	if (buf & BAT_CON) {
		buf &= ~BAT_CON;
		rk816_bat_write(di, GGSTS_REG, buf);
		return true;
	}

	return false;
}

static bool rk816_bat_ocv_sw_reset(struct battery_priv *di)
{
	u8 buf;

	buf = rk816_bat_read(di, MISC_MARK_REG);
	if (((buf & FG_RESET_LATE) && di->pwroff_min >= 30) ||
	    (buf & FG_RESET_NOW)) {
		buf &= ~FG_RESET_LATE;
		buf &= ~FG_RESET_NOW;
		rk816_bat_write(di, MISC_MARK_REG, buf);
		BAT_INFO("manual reset fuel gauge\n");
		return true;
	} else {
		return false;
	}
}

static int rk816_bat_calc_linek(struct battery_priv *di)
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

static int rk816_bat_get_coffset(struct battery_priv *di)
{
	int val = 0;

	val |= rk816_bat_read(di, CAL_OFFSET_REGL) << 0;
	val |= rk816_bat_read(di, CAL_OFFSET_REGH) << 8;

	return val;
}

static void rk816_bat_init_poffset(struct battery_priv *di)
{
	int coffset, ioffset;

	coffset = rk816_bat_get_coffset(di);
	ioffset = rk816_bat_get_ioffset(di);
	di->poffset = coffset - ioffset;
}

static void rk816_bat_select_sample_res(struct battery_priv *di)
{
	/* Here, res_fac is 10 times of real value for good calcuation */
	if (di->sample_res == SAMPLE_RES_20MR) {
		di->over_20mR = 0;
		di->res_fac = 10;
	} else if (di->sample_res > SAMPLE_RES_20MR) {
		di->over_20mR = 1;
		di->res_fac = di->sample_res * 10 / SAMPLE_RES_20MR;
	} else {
		di->over_20mR = 0;
		di->res_fac = SAMPLE_RES_20MR * 10 / di->sample_res;
	}
}
static bool is_rk816_bat_exist(struct  battery_priv *di)
{
	return (rk816_bat_read(di, SUP_STS_REG) & BAT_EXS) ? true : false;
}

static void rk816_bat_set_current(struct battery_priv *di, int input_current)
{
	u8 usb_ctrl;

	usb_ctrl = rk816_bat_read(di, USB_CTRL_REG);
	usb_ctrl &= ~INPUT_CUR_MSK;
	usb_ctrl |= (input_current);
	rk816_bat_write(di, USB_CTRL_REG, usb_ctrl);
}

static void rk816_bat_charger_setting(struct battery_priv *di, int charger)
{
	static u8 old_charger = UNDEF_CHARGER;

	/*charger changed*/
	if (old_charger != charger) {
		if (charger == NO_CHARGER)
			rk816_bat_set_current(di, ILIM_450MA);
		else if (charger == USB_CHARGER)
			rk816_bat_set_current(di, ILIM_450MA);
		else if (charger == DC_CHARGER || charger == AC_CHARGER)
			rk816_bat_set_current(di, di->chrg_cur_input);
		else
			BAT_INFO("charger setting error %d\n", charger);

		old_charger = charger;
	}
}

static int rk816_bat_get_dc_state(struct battery_priv *di)
{
	/* struct adc_channel val; */

	if (di->dc_type == DC_TYPE_OF_NONE) {
		return NO_CHARGER;
	} else if (di->dc_type == DC_TYPE_OF_ADC) {
		/*
		if (adc_channels_single_shot("saradc", 0, &val)) {
			printf("read saradc value failed\n");
			return NO_CHARGER;
		}

		return (val.data >= DC_ADC_TRIGGER) ? DC_CHARGER : NO_CHARGER;
		*/
		return NO_CHARGER;
	} else {
		return (dm_gpio_get_value(&di->dc_det)) ?
			DC_CHARGER : NO_CHARGER;
	}
}

static int rk816_bat_get_charger_type(struct battery_priv *di)
{
	int charger_type = NO_CHARGER;

	/* check by ic hardware: this check make check work safer */
	if ((rk816_bat_read(di, VB_MON_REG) & PLUG_IN_STS) == 0)
		return NO_CHARGER;

	/* virtual or bat not exist */
	if (di->virtual_power)
		return DC_CHARGER;

	/* check DC first */
	charger_type = rk816_bat_get_dc_state(di);
	if (charger_type == DC_CHARGER)
		return charger_type;

	/* check USB second */
	return rk816_bat_get_usb_state(di);
}

static bool rk816_bat_need_initialize(struct battery_priv *di)
{
	bool initialize = false;
#ifdef CONFIG_DM_CHARGE_DISPLAY
	struct charge_animation_pdata *pdata;
	struct udevice *dev;
	int est_voltage;

	if (!uclass_find_first_device(UCLASS_CHARGE_DISPLAY, &dev)) {
		pdata = dev_get_platdata(dev);
		est_voltage = rk816_bat_get_avg_voltage(di);
		if ((pdata->uboot_charge) ||
		    (pdata->low_power_voltage >= est_voltage))
			initialize = true;
	}
#endif

	return initialize;
}

void rk816_bat_init_rsoc(struct battery_priv *di)
{
	bool initialize = false;

	di->is_first_power_on = is_rk816_bat_first_poweron(di);
	/* If first power on, we must do initialization */
	if (di->is_first_power_on)
		initialize = true;
	/* Only charger online and under threshold, we do initialization */
	else if (rk816_bat_get_charger_type(di) != NO_CHARGER)
		initialize = rk816_bat_need_initialize(di);

	printf("Fuel gauge initialize = %d\n", initialize);

	if (!initialize)
		return;

	di->pwroff_min = rk816_bat_get_pwroff_min(di);
	di->is_sw_reset = rk816_bat_ocv_sw_reset(di);

	if (di->is_first_power_on || di->is_sw_reset)
		rk816_bat_first_pwron(di);
	else
		rk816_bat_not_first_pwron(di);

	rk816_bat_save_dsoc(di, di->dsoc);
	rk816_bat_save_cap(di, di->remain_cap);
}

static int rk816_fg_init(struct battery_priv *di)
{
	rk816_bat_enable_input_current(di);
	rk816_bat_enable_gauge(di);
	rk816_bat_set_vol_instant_mode(di);
	rk816_bat_init_voltage_kb(di);
	rk816_bat_init_poffset(di);
	rk816_bat_select_sample_res(di);
	rk816_bat_clr_initialized_state(di);
	di->dsoc = rk816_bat_get_dsoc(di);
	di->remain_cap = rk816_bat_get_prev_cap(di);

	/*
	 * It's better to init fg in kernel,
	 * so avoid init in uboot as far as possible.
	 */
	rk816_bat_init_rsoc(di);
	rk816_bat_init_chrg_config(di);
	di->chrg_type = rk816_bat_get_charger_type(di);
	di->voltage_avg = rk816_bat_get_avg_voltage(di);
	di->voltage_ocv = rk816_bat_get_ocv_voltage(di);
	di->current_avg = rk816_bat_get_avg_current(di);
	di->sm_linek = rk816_bat_calc_linek(di);
	di->finish_chrg_base = get_timer(0);
	di->pwr_vol = di->voltage_avg;
	rk816_bat_charger_setting(di, di->chrg_type);

	printf("Battery: soc=%d%%, cap=%dmAh, voltage=%dmv, Charger: %s%s\n",
	       di->dsoc, di->remain_cap, di->voltage_avg,
	       charger_type_to_name[di->chrg_type],
	       di->virtual_power ? "(virtual)" : "");

	return 0;
}

static u8 rk816_bat_get_chrg_status(struct battery_priv *di)
{
	u8 status;

	status = rk816_bat_read(di, SUP_STS_REG) & BAT_STATUS_MSK;
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
		DBG(" USB EFF...\n");
		break;
	default:
		return -EINVAL;
	}

	return status;
}

static void rk816_bat_finish_chrg(struct battery_priv *di)
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

static void rk816_bat_debug_info(struct battery_priv *di)
{
	u8 sup_sts, ggcon, ggsts, vb_mod, rtc, thermal, misc;
	u8 usb_ctrl, chrg_ctrl1, chrg_ctrl2, chrg_ctrl3;
	uint32_t chrg_cur;
	static const char *name[] = {"NONE", "USB", "AC", "DC", "UNDEF"};

	if (!dbg_enable)
		return;
	ggcon = rk816_bat_read(di, GGCON_REG);
	ggsts = rk816_bat_read(di, GGSTS_REG);
	sup_sts = rk816_bat_read(di, SUP_STS_REG);
	usb_ctrl = rk816_bat_read(di, USB_CTRL_REG);
	thermal = rk816_bat_read(di, THERMAL_REG);
	vb_mod = rk816_bat_read(di, VB_MON_REG);
	misc = rk816_bat_read(di, MISC_MARK_REG);
	rtc = rk816_bat_read(di, SECONDS_REG);
	chrg_ctrl1 = rk816_bat_read(di, CHRG_CTRL_REG1);
	chrg_ctrl2 = rk816_bat_read(di, CHRG_CTRL_REG2);
	chrg_ctrl3 = rk816_bat_read(di, CHRG_CTRL_REG3);
	if (!di->over_20mR)
		chrg_cur = RES_FAC_MUX(CHRG_CUR_SEL[chrg_ctrl1 & 0x0f],
				       di->res_fac);
	else
		chrg_cur = RES_FAC_DIV(CHRG_CUR_SEL[chrg_ctrl1 & 0x0f],
				       di->res_fac);

	DBG("\n---------------------- DEBUG REGS ------------------------\n"
	    "GGCON=0x%2x, GGSTS=0x%2x, RTC=0x%2x, SUP_STS= 0x%2x\n"
	    "VB_MOD=0x%2x, USB_CTRL=0x%2x, THERMAL=0x%2x, MISC=0x%2x\n"
	    "CHRG_CTRL:REG1=0x%2x, REG2=0x%2x, REG3=0x%2x\n",
	    ggcon, ggsts, rtc, sup_sts, vb_mod, usb_ctrl,
	    thermal, misc, chrg_ctrl1, chrg_ctrl2, chrg_ctrl3
	    );
	DBG("----------------------------------------------------------\n"
	    "Dsoc=%d, Rsoc=%d, Vavg=%d, Iavg=%d, Cap=%d, Fcc=%d, d=%d\n"
	    "K=%d, old_cap=%d, charger=%s, Is=%d, Ip=%d, Vs=%d, Rfac=%d\n"
	    "min=%d, meet: soc=%d, calc: dsoc=%d, rsoc=%d, Vocv=%d, Rsam=%d\n"
	    "off: i=0x%x, c=0x%x, max=%d, ocv_c=%d, halt: st=%d, cnt=%d\n"
	    "pwr: dsoc=%d, rsoc=%d, vol=%d, exist=%d\n",
	    di->dsoc, rk816_bat_get_rsoc(di), rk816_bat_get_avg_voltage(di),
	    rk816_bat_get_avg_current(di), di->remain_cap, di->fcc,
	    di->rsoc - di->dsoc,
	    di->sm_linek, di->sm_old_cap, name[di->chrg_type],
	    chrg_cur,
	    CHRG_CUR_INPUT[usb_ctrl & 0x0f],
	    CHRG_VOL_SEL[(chrg_ctrl1 & 0x70) >> 4], di->res_fac,
	    di->pwroff_min,
	    di->sm_meet_soc, di->calc_dsoc, di->calc_rsoc,
	    rk816_bat_get_ocv_voltage(di), di->sample_res,
	    rk816_bat_get_ioffset(di),
	    rk816_bat_get_coffset(di), di->is_max_soc_offset,
	    di->is_ocv_calib, di->is_halt, di->halt_cnt, di->pwr_dsoc,
	    di->pwr_rsoc, di->pwr_vol, is_rk816_bat_exist(di)
	    );
	rk816_bat_get_chrg_status(di);
	DBG("###########################################################\n");
}

static void rk816_bat_linek_algorithm(struct battery_priv *di)
{
	int delta_cap, ydsoc, tmp;
	u8 chg_st = rk816_bat_get_chrg_status(di);

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

static int rk816_bat_get_iadc(struct battery_priv *di)
{
	int val = 0;

	val |= rk816_bat_read(di, BAT_CUR_AVG_REGL) << 0;
	val |= rk816_bat_read(di, BAT_CUR_AVG_REGH) << 8;
	if (val > 2047)
		val -= 4096;

	return val;
}

static bool rk816_bat_adc_calib(struct battery_priv *di)
{
	int i, ioffset, coffset, adc;

	if (abs(di->current_avg) < ADC_CALIB_THRESHOLD)
		return false;

	for (i = 0; i < 5; i++) {
		adc = rk816_bat_get_iadc(di);
		coffset = rk816_bat_get_coffset(di);
		rk816_bat_set_coffset(di, coffset + adc);
		mdelay(200);
		adc = rk816_bat_get_iadc(di);
		if (abs(adc) < ADC_CALIB_THRESHOLD) {
			coffset = rk816_bat_get_coffset(di);
			ioffset = rk816_bat_get_ioffset(di);
			di->poffset = coffset - ioffset;
			rk816_bat_write(di, POFFSET_REG, di->poffset);
			BAT_INFO("new offset:c=0x%x, i=0x%x, p=0x%x\n",
				 coffset, ioffset, di->poffset);
			return true;
		} else {
			BAT_INFO("coffset calib again %d..\n", i);
			rk816_bat_set_coffset(di, coffset);
			mdelay(200);
		}
	}

	return false;
}

static void rk816_bat_smooth_charge(struct battery_priv *di)
{
	u8 chg_st = rk816_bat_get_chrg_status(di);

	if (di->vol_mode_base && get_timer(di->vol_mode_base) > SECONDS(10)) {
		rk816_bat_set_vol_avg_mode(di);
		di->vol_mode_base = 0;
	}

	/* not charge mode and not keep in uboot charge: exit */
	if ((di->chrg_type == NO_CHARGER) ||
	    !rk816_bat_is_initialized(di)) {
		DBG("chrg=%d, initialized=%d\n", di->chrg_type,
		    rk816_bat_is_initialized(di));
		goto out;
	}

	/* update rsoc and remain cap */
	di->remain_cap = rk816_bat_get_coulomb_cap(di);
	di->rsoc = rk816_bat_get_rsoc(di);
	if (di->remain_cap > di->fcc) {
		di->sm_old_cap -= (di->remain_cap - di->fcc);
		rk816_bat_init_capacity(di, di->fcc);
	}

	/* finish charge step */
	if (chg_st == CHARGE_FINISH) {
		DBG("finish charge step...\n");
		if (di->adc_allow_update)
			di->adc_allow_update = !rk816_bat_adc_calib(di);
		rk816_bat_finish_chrg(di);
		rk816_bat_init_capacity(di, di->fcc);
	} else {
		DBG("smooth charge step...\n");
		di->adc_allow_update = true;
		di->finish_chrg_base = get_timer(0);
		rk816_bat_linek_algorithm(di);
	}

	/* dsoc limit */
	if (di->dsoc > 100)
		di->dsoc = 100;
	else if (di->dsoc < 0)
		di->dsoc = 0;

	rk816_bat_save_dsoc(di, di->dsoc);
	rk816_bat_save_cap(di, di->remain_cap);
out:
	rk816_bat_debug_info(di);
}

static int rk816_bat_bat_is_exit(struct udevice *dev)
{
	struct battery_priv *di = dev_get_priv(dev);

	return is_rk816_bat_exist(di);
}

static int rk816_bat_update_get_soc(struct udevice *dev)
{
	struct battery_priv *di = dev_get_priv(dev);
	static ulong seconds;

	/* set charge current */
	di->chrg_type =
		rk816_bat_get_charger_type(di);
	rk816_bat_charger_setting(di, di->chrg_type);

	/* fg calc every 5 seconds */
	if (!seconds)
		seconds = get_timer(0);
	if (get_timer(seconds) >= SECONDS(5)) {
		seconds = get_timer(0);
		rk816_bat_smooth_charge(di);
	}

	/* bat exist, fg init success(dts pass) and uboot charge: report data */
	if (!di->virtual_power && di->voltage_k)
		return di->dsoc;
	else
		return VIRTUAL_POWER_SOC;
}

static int rk816_bat_update_get_voltage(struct udevice *dev)
{
	struct battery_priv *di = dev_get_priv(dev);

	if (!di->virtual_power && di->voltage_k)
		return rk816_bat_get_est_voltage(di);
	else
		return VIRTUAL_POWER_VOL;
}

static int rk816_bat_update_get_current(struct udevice *dev)
{
	struct battery_priv *di = dev_get_priv(dev);

	if (!di->virtual_power && di->voltage_k)
		return rk816_bat_get_avg_current(di);
	else
		return VIRTUAL_POWER_CUR;
}

static bool rk816_bat_update_get_chrg_online(struct udevice *dev)
{
	struct battery_priv *di = dev_get_priv(dev);

	return rk816_bat_get_charger_type(di);
}

static struct dm_fuel_gauge_ops fg_ops = {
	.bat_is_exist = rk816_bat_bat_is_exit,
	.get_soc = rk816_bat_update_get_soc,
	.get_voltage = rk816_bat_update_get_voltage,
	.get_current = rk816_bat_update_get_current,
	.get_chrg_online = rk816_bat_update_get_chrg_online,
};

static int rk816_fg_ofdata_to_platdata(struct udevice *dev)
{
	struct rk8xx_priv *rk8xx = dev_get_priv(dev->parent);
	struct battery_priv *di = dev_get_priv(dev);
	const char *prop;
	int len;

	if (rk8xx->variant != 0x8160) {
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
	di->dts_cur_input = dev_read_u32_default(dev, "max_input_current", 2000);
	di->dts_cur_sel = dev_read_u32_default(dev, "max_chrg_current", 1200);
	di->max_soc_offset = dev_read_u32_default(dev, "max_soc_offset", 70);
	di->virtual_power = dev_read_u32_default(dev, "virtual_power", 0);
	di->sample_res = dev_read_u32_default(dev, "sample_res", 20);
	di->bat_res = dev_read_u32_default(dev, "bat_res", 135);

	/* Parse dc type */
	di->dc_det_adc = dev_read_u32_default(dev, "dc_det_adc", 0);
	if (di->dc_det_adc <= 0) {
		if (!gpio_request_by_name_nodev(dev_ofnode(dev), "dc_det_gpio",
						0, &di->dc_det, GPIOD_IS_IN)) {
			di->dc_type = DC_TYPE_OF_GPIO;
		} else {
			di->dc_type = DC_TYPE_OF_NONE;
		}
	} else {
		di->dc_type = DC_TYPE_OF_ADC;
	}

	/* Is battery attached */
	if (!is_rk816_bat_exist(di))
		di->virtual_power = 1;

	DBG("-------------------------------:\n");
	DBG("max_input_current:%d\n", di->dts_cur_input);
	DBG("max_chrg_current:%d\n", di->dts_cur_sel);
	DBG("max_chrg_voltage:%d\n", di->dts_vol_sel);
	DBG("design_capacity :%d\n", di->design_cap);
	DBG("design_qmax:%d\n", di->qmax);
	DBG("max_soc_offset:%d\n", di->max_soc_offset);
	DBG("dc_det_adc:%d\n", di->dc_det_adc);
	DBG("res_sample:%d\n", di->sample_res);

	return 0;
}

static int rk816_fg_probe(struct udevice *dev)
{
	struct rk8xx_priv *rk8xx = dev_get_priv(dev->parent);
	struct battery_priv *di = dev_get_priv(dev);

	if (rk8xx->variant != 0x8160) {
		printf("Not support pmic variant: rk%x\n", rk8xx->variant);
		return -EINVAL;
	}

	return rk816_fg_init(di);
}

U_BOOT_DRIVER(rk816_fg) = {
	.name = "rk816_fg",
	.id = UCLASS_FG,
	.probe = rk816_fg_probe,
	.ops = &fg_ops,
	.ofdata_to_platdata = rk816_fg_ofdata_to_platdata,
	.priv_auto_alloc_size = sizeof(struct battery_priv),
};
