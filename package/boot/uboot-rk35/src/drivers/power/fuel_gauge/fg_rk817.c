/*
 * (C) Copyright 2018 Rockchip Electronics Co., Ltd
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

DECLARE_GLOBAL_DATA_PTR;

static int dbg_enable = 0;
#define DBG(args...) \
	do { \
		if (dbg_enable) { \
			printf(args); \
		} \
	} while (0)

#define DIV(value)	((value) ? (value) : 1)
#define ENABLE			0x01
#define DISABLE			0x00
#define MAX_INTERPOLATE		1000
#define MAX_PERCENTAGE		100
#define MAX_INT			0x7FFF

#define ADC_CONFIG0		0x0050
#define CUR_ADC_CFG0		0x0051
#define CUR_ADC_CFG1		0x0052
#define VOL_ADC_CFG0		0x0053
#define VOL_ADC_CFG1		0x0054
#define ADC_CONFIG1		0x0055
#define GG_CON			0x0056
#define GG_STS			0x0057
#define RELAX_THRE_H		0x0058
#define RELAX_THRE_L		0x0059
#define RELAX_VOL1_H		0x005a
#define RELAX_VOL1_L		0x005b
#define RELAX_VOL2_H		0x005c
#define RELAX_VOL2_L		0x005d
#define RELAX_CUR1_H		0x005e
#define RELAX_CUR1_L		0x005f
#define RELAX_CUR2_H		0x0060
#define RELAX_CUR2_L		0x0061
#define OCV_THRE_VOL		0x0062
#define OCV_VOL_H		0x0063
#define OCV_VOL_L		0x0064
#define OCV_VOL0_H		0x0065
#define OCV_VOL0_L		0x0066
#define OCV_CUR_H		0x0067
#define OCV_CUR_L		0x0068
#define OCV_CUR0_H		0x0069
#define OCV_CUR0_L		0x006a
#define PWRON_VOL_H		0x006b
#define PWRON_VOL_L		0x006c
#define PWRON_CUR_H		0x006d
#define PWRON_CUR_L		0x006e
#define OFF_CNT			0x006f
#define Q_INIT_H3		0x0070
#define Q_INIT_H2		0x0071
#define Q_INIT_L1		0x0072
#define Q_INIT_L0		0x0073
#define Q_PRES_H3		0x0074
#define Q_PRES_H2		0x0075
#define Q_PRES_L1		0x0076
#define Q_PRES_L0		0x0077
#define BAT_VOL_H		0x0078
#define BAT_VOL_L		0x0079
#define BAT_CUR_H		0x007a
#define BAT_CUR			0x007b
#define BAT_TS_H		0x007c
#define BAT_TS_L		0x007d
#define USB_VOL_H		0x007e
#define USB_VOL_L		0x007f
#define SYS_VOL_H		0x0080
#define SYS_VOL_L		0x0081
#define Q_MAX_H3		0x0082
#define Q_MAX_H2		0x0083
#define Q_MAX_L1		0x0084
#define Q_MAX_L0		0x0085
#define Q_TERM_H3		0x0086
#define Q_TERM_H2		0x0087
#define Q_TERM_L1		0x0088
#define Q_TERM_L0		0x0089
#define Q_OCV_H3		0x008a
#define Q_OCV_H2		0x008b
#define Q_OCV_L1		0x008c
#define Q_OCV_L0		0x008d
#define OCV_CNT			0x008e
#define SLEEP_CON_SAMP_CUR_H	0x008f
#define SLEEP_CON_SAMP_CUR	0x0090
#define CAL_OFFSET_H		0x0091
#define CAL_OFFSET_L		0x0092
#define VCALIB0_H		0x0093
#define VCALIB0_L		0x0094
#define VCALIB1_H		0x0095
#define VCALIB1_L		0x0096
#define IOFFSET_H		0x0097
#define IOFFSET_L		0x0098
#define BAT_R0			0x0099
#define SOC_REG0		0x009a
#define SOC_REG1		0x009b
#define SOC_REG2		0x009c
#define REMAIN_CAP_REG0		0x9d
#define REMAIN_CAP_REG1		0x9e
#define REMAIN_CAP_REG2		0x9f
#define NEW_FCC_REG0		0x00a0
#define NEW_FCC_REG1		0x00a1
#define NEW_FCC_REG2		0x00a2
#define DATA6			0x00a3
#define DATA7			0x00a4
#define FG_INIT			0x00a5
#define HALT_CNT_REG		0x00a6
#define DATA10			0x00a7
#define DATA11			0x00a8
#define VOL_ADC_B3		0x00a9
#define VOL_ADC_B2		0x00aa
#define VOL_ADC_B1		0x00ab
#define VOL_ADC_B_7_0		0x00ac
#define CUR_ADC_K3		0x00ad
#define CUR_ADC_K2		0x00ae
#define CUR_ADC_K1		0x00af
#define CUR_ADC_K0		0x00b0
#define PMIC_CHRG_STS		0x00eb
#define BAT_DISCHRG		0x00ec
#define BAT_CON			BIT(4)

#define USB_CTRL_REG		0x00E5
#define PMIC_SYS_STS		0x00f0
#define PLUG_IN_STS		BIT(6)

#define CHRG_TERM_DSOC		90
#define CHRG_TERM_K		650
#define CHRG_FULL_K		400
#define CHARGE_FINISH		(0x04 << 4)

/* CALI PARAM */
#define FINISH_CALI_CURR	1500
#define TERM_CALI_CURR		600
#define VIRTUAL_POWER_VOL	4200
#define VIRTUAL_POWER_CUR	1000
#define VIRTUAL_POWER_SOC	66
#define SECONDS(n)		((n) * 1000)

/* CHRG_CTRL_REG */
#define ILIM_450MA		(0x00)
#define ILIM_2000MA		(0x07)
#define ILIM_1500MA		(0x03)
#define VLIM_4500MV		(0x50)

/* sample resistor and division */
#define SAMPLE_RES_10mR		10
#define SAMPLE_RES_20mR		20
#define SAMPLE_RES_DIV1		1
#define SAMPLE_RES_DIV2		2

#define CHRG_CT_EN		BIT(1)
#define MIN_FCC			500
#define CAP_INVALID		BIT(7)
#define DIS_ILIM_EN		BIT(3)

/* USB_CTRL_REG */
#define INPUT_CUR_MSK		0x0f
#define INPUT_VOL_MSK		0xf0
#define VOL_OUPUT_INSTANT_MODE	0x02

#define ADC_TO_CURRENT(adc_value, samp_res)	\
	(adc_value * 172 / 1000 / samp_res)
#define CURRENT_TO_ADC(current, samp_res)	\
	(current * 1000 * samp_res / 172)

#define ADC_TO_CAPACITY(adc_value, samp_res)	\
	(adc_value / 1000 * 172 / 3600 / samp_res)
#define CAPACITY_TO_ADC(capacity, samp_res)	\
	(capacity * samp_res * 3600 / 172 * 1000)

#define ADC_TO_CAPACITY_UAH(adc_value, samp_res)	\
	(adc_value / 3600 * 172 / samp_res)
#define ADC_TO_CAPACITY_MAH(adc_value, samp_res)	\
	(adc_value / 1000 * 172 / 3600 / samp_res)

/* charger type definition */
enum charger_type {
	NO_CHARGER = 0,
	USB_CHARGER,
	AC_CHARGER,
	DC_CHARGER,
	UNDEF_CHARGER,
};

enum power_supply_type {
	POWER_SUPPLY_TYPE_UNKNOWN = 0,
	POWER_SUPPLY_TYPE_USB,		/* Standard Downstream Port */
	POWER_SUPPLY_TYPE_USB_DCP,	/* Dedicated Charging Port */
	POWER_SUPPLY_TYPE_USB_CDP,	/* Charging Downstream Port */
	POWER_SUPPLY_TYPE_USB_FLOATING,	/* DCP without shorting D+/D- */
};

struct rk817_battery_device {
	struct udevice *dev;
	int				res_div;
	bool				is_first_power_on;
	bool				is_initialized;
	bool				bat_first_power_on;
	int				current_avg;
	int				current_pwron;
	int				voltage_usb;
	int				voltage_sys;
	int				voltage_avg;
	int				voltage_k;/* VCALIB0 VCALIB1 */
	int				voltage_b;
	u32				remain_cap;
	int				design_cap;
	int				nac;
	int				fcc;
	int				qmax;
	int				dsoc;
	int				rsoc;
	int				pwron_voltage;
	int				sm_linek;
	int				sm_old_cap;
	int				calc_dsoc;
	int				calc_rsoc;
	int				sm_chrg_dsoc;
	u8				halt_cnt;
	bool				is_halt;
	int				dbg_pwr_dsoc;
	int				dbg_pwr_rsoc;
	int				dbg_pwr_vol;
	int				dbg_meet_soc;
	int				dbg_calc_dsoc;
	int				dbg_calc_rsoc;
	int				adc_allow_update;
	int				pwroff_min;
	int				chrg_cur_input;
	u32				*ocv_table;
	int				ocv_size;
	u32				design_capacity;
	u32				max_soc_offset;
	u32				virtual_power;
	u32				chrg_type;
	ulong				finish_chrg_base;
	ulong				term_sig_base;
	int				sm_meet_soc;
	u32				bat_res_up;
	u32				bat_res_down;
	u32				variant;
};

static u32 interpolate(int value, u32 *table, int size)
{
	u8 i;
	u16 d;

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

/* (a * b) / c */
static int32_t ab_div_c(u32 a, u32 b, u32 c)
{
	bool sign;
	u32 ans = MAX_INT;
	int tmp;

	sign = ((((a ^ b) ^ c) & 0x80000000) != 0);
	if (c != 0) {
		if (sign)
			c = -c;
		tmp = (a * b + (c >> 1)) / c;
		if (tmp < MAX_INT)
			ans = tmp;
	}

	if (sign)
		ans = -ans;

	return ans;
}

static int rk817_bat_read(struct rk817_battery_device *battery, u8 reg)
{
	return pmic_reg_read(battery->dev->parent, reg);
}

static void rk817_bat_write(struct rk817_battery_device *battery,
			    u8 reg, u8 buf)
{
	pmic_reg_write(battery->dev->parent, reg, buf);
}

static int rk817_bat_get_vaclib0(struct rk817_battery_device *battery)
{
	int vcalib_value = 0;

	vcalib_value |= rk817_bat_read(battery, VCALIB0_H) << 8;
	vcalib_value |= rk817_bat_read(battery, VCALIB0_L);

	return vcalib_value;
}

static int rk817_bat_get_vaclib1(struct rk817_battery_device *battery)
{
	int vcalib_value = 0;

	vcalib_value |= rk817_bat_read(battery, VCALIB1_H) << 8;
	vcalib_value |= rk817_bat_read(battery, VCALIB1_L);

	return vcalib_value;
}

static void rk817_bat_init_voltage_kb(struct rk817_battery_device *battery)
{
	int vcalib0, vcalib1;

	vcalib0 = rk817_bat_get_vaclib0(battery);
	vcalib1 =  rk817_bat_get_vaclib1(battery);

	if (battery->variant == RK809_ID) {
		battery->voltage_k = (1050 - 600) * 1000 / DIV(vcalib1 - vcalib0);
		battery->voltage_b = 1050 - (battery->voltage_k * vcalib1) / 1000;
	} else {
		battery->voltage_k = (4025 - 2300) * 1000 / DIV(vcalib1 - vcalib0);
		battery->voltage_b = 4025 - (battery->voltage_k * vcalib1) / 1000;
	}
}

/* power on battery voltage */
static int rk817_bat_get_pwron_voltage(struct rk817_battery_device *battery)
{
	int vol, val = 0, vol_temp;

	val = rk817_bat_read(battery, PWRON_VOL_H) << 8;
	val |= rk817_bat_read(battery, PWRON_VOL_L);
	vol = battery->voltage_k * val / 1000 + battery->voltage_b;
	if (battery->variant == RK809_ID) {
		vol_temp = (vol * battery->bat_res_up / battery->bat_res_down + vol);
		vol = vol_temp;
	}

	return vol;
}

static int rk817_bat_get_USB_voltage(struct rk817_battery_device *battery)
{
	int vol, val = 0, vol_temp;

	val = rk817_bat_read(battery, USB_VOL_L) << 0;
	val |= rk817_bat_read(battery, USB_VOL_H) << 8;

	vol = (battery->voltage_k * val / 1000 + battery->voltage_b) * 60 / 46;
	if (battery->variant == RK809_ID) {
		vol_temp = vol * battery->bat_res_up / battery->bat_res_down + vol;
		vol = vol_temp;
	}

	return vol;
}

static int rk817_bat_get_sys_voltage(struct rk817_battery_device *battery)
{
	int vol, val = 0, vol_temp;

	val = rk817_bat_read(battery, SYS_VOL_H) << 8;
	val |= rk817_bat_read(battery, SYS_VOL_L) << 0;

	vol = (battery->voltage_k * val / 1000 + battery->voltage_b) * 60 / 46;
	if (battery->variant == RK809_ID) {
		vol_temp = vol * battery->bat_res_up / battery->bat_res_down + vol;
		vol = vol_temp;
	}

	return vol;
}

static int rk817_bat_get_battery_voltage(struct rk817_battery_device *battery)
{
	int vol, val = 0, vol_temp;

	val = rk817_bat_read(battery, BAT_VOL_H) << 8;
	val |= rk817_bat_read(battery, BAT_VOL_L) << 0;

	vol = battery->voltage_k * val / 1000 + battery->voltage_b;
	if (battery->variant == RK809_ID) {
		vol_temp = (vol * battery->bat_res_up / battery->bat_res_down + vol);
		vol = vol_temp;
	}
	return vol;
}

static int rk817_bat_get_avg_current(struct rk817_battery_device *battery)
{
	int cur, val = 0;

	val |= rk817_bat_read(battery, BAT_CUR);
	val |= rk817_bat_read(battery, BAT_CUR_H) << 8;

	if (val & 0x8000)
		val -= 0x10000;

	cur = ADC_TO_CURRENT(val, battery->res_div);

	return cur;
}

static int rk817_bat_get_pwron_current(struct rk817_battery_device *battery)
{
	int cur, val = 0;

	val |= rk817_bat_read(battery, PWRON_CUR_L);
	val |= rk817_bat_read(battery, PWRON_CUR_H) << 8;

	if (val & 0x8000)
		val -= 0x10000;
	cur = ADC_TO_CURRENT(val, battery->res_div);

	return cur;
}

static void rk817_bat_calibration(struct rk817_battery_device *battery)
{
	int  ioffset_value = 0;
	u8  buf = 0;

	if (rk817_bat_read(battery, ADC_CONFIG1) & 0x80) {
		ioffset_value = rk817_bat_read(battery, IOFFSET_H) << 8;
		ioffset_value |= rk817_bat_read(battery, IOFFSET_L);

		buf = (ioffset_value >> 8) & 0xff;
		rk817_bat_write(battery, CAL_OFFSET_H, buf);
		buf = (ioffset_value >> 0) & 0xff;
		rk817_bat_write(battery, CAL_OFFSET_L, buf);

		rk817_bat_init_voltage_kb(battery);
		rk817_bat_write(battery, ADC_CONFIG1, 0x80);
	}
}

static int rk817_bat_get_rsoc(struct rk817_battery_device *battery);

static void rk817_bat_init_coulomb_cap(struct rk817_battery_device *battery,
				       u32 capacity)
{
	u8 buf;
	u32 cap;
	u32 val;

	cap = CAPACITY_TO_ADC(capacity, battery->res_div);

	do {
		buf = (cap >> 24) & 0xff;
		rk817_bat_write(battery, Q_INIT_H3, buf);
		buf = (cap >> 16) & 0xff;
		rk817_bat_write(battery, Q_INIT_H2, buf);
		buf = (cap >> 8) & 0xff;
		rk817_bat_write(battery, Q_INIT_L1, buf);
		buf = (cap >> 0) & 0xff;
		rk817_bat_write(battery, Q_INIT_L0, buf);

		val = rk817_bat_read(battery, Q_INIT_H3) << 24;
		val |= rk817_bat_read(battery, Q_INIT_H2) << 16;
		val |= rk817_bat_read(battery, Q_INIT_L1) << 8;
		val |= rk817_bat_read(battery, Q_INIT_L0) << 0;
	} while (cap != val);

	battery->rsoc = rk817_bat_get_rsoc(battery);
	battery->remain_cap = capacity * 1000;
}

static bool rk817_bat_remain_cap_is_valid(struct rk817_battery_device *battery)
{
	return !(rk817_bat_read(battery, Q_PRES_H3) & CAP_INVALID);
}

static u32 rk817_bat_get_capacity_uah(struct rk817_battery_device *battery)
{
	u32 val = 0, capacity = 0;

	if (rk817_bat_remain_cap_is_valid(battery)) {
		val = rk817_bat_read(battery, Q_PRES_H3) << 24;
		val |= rk817_bat_read(battery, Q_PRES_H2) << 16;
		val |= rk817_bat_read(battery, Q_PRES_L1) << 8;
		val |= rk817_bat_read(battery, Q_PRES_L0) << 0;

		capacity = ADC_TO_CAPACITY_UAH(val, battery->res_div);
	}

	return  capacity;
}

static u32 rk817_bat_get_capacity_mah(struct rk817_battery_device *battery)
{
	u32 val, capacity = 0;

	if (rk817_bat_remain_cap_is_valid(battery)) {
		val = rk817_bat_read(battery, Q_PRES_H3) << 24;
		val |= rk817_bat_read(battery, Q_PRES_H2) << 16;
		val |= rk817_bat_read(battery, Q_PRES_L1) << 8;
		val |= rk817_bat_read(battery, Q_PRES_L0) << 0;
		capacity = ADC_TO_CAPACITY(val, battery->res_div);
	}

	return  capacity;
}

static void rk817_bat_save_cap(struct rk817_battery_device *battery,
			       int capacity)
{
	u8 buf;
	static u32 old_cap;

	if (capacity >= battery->qmax)
		capacity = battery->qmax;
	if (capacity <= 0)
		capacity = 0;
	if (old_cap == capacity)
		return;

	old_cap = capacity;
	buf = (capacity >> 16) & 0xff;
	rk817_bat_write(battery, REMAIN_CAP_REG2, buf);
	buf = (capacity >> 8) & 0xff;
	rk817_bat_write(battery, REMAIN_CAP_REG1, buf);
	buf = (capacity >> 0) & 0xff;
	rk817_bat_write(battery, REMAIN_CAP_REG0, buf);
}

static int rk817_bat_get_rsoc(struct rk817_battery_device *battery)
{
	int remain_cap;

	remain_cap = rk817_bat_get_capacity_uah(battery);

	return remain_cap * 100 / DIV(battery->fcc);
}

static int rk817_bat_vol_to_soc(struct rk817_battery_device *battery,
				int voltage)
{
	u32 *ocv_table, temp;
	int ocv_size, ocv_soc;

	ocv_table = battery->ocv_table;
	ocv_size = battery->ocv_size;
	temp = interpolate(voltage, ocv_table, ocv_size);
	ocv_soc = ab_div_c(temp, MAX_PERCENTAGE, MAX_INTERPOLATE);

	return ocv_soc;
}

static int rk817_bat_vol_to_cap(struct rk817_battery_device *battery,
				int voltage)
{
	u32 *ocv_table, temp;
	int ocv_size, capacity;

	ocv_table = battery->ocv_table;
	ocv_size = battery->ocv_size;
	temp = interpolate(voltage, ocv_table, ocv_size);
	capacity = ab_div_c(temp, battery->fcc, MAX_INTERPOLATE);

	return capacity;
}

static void rk817_bat_save_dsoc(struct rk817_battery_device *battery,
				int save_soc)
{
	static int last_soc = -1;

	if (last_soc != save_soc) {
		rk817_bat_write(battery, SOC_REG0, save_soc & 0xff);
		rk817_bat_write(battery, SOC_REG1, (save_soc >> 8) & 0xff);
		rk817_bat_write(battery, SOC_REG2, (save_soc >> 16) & 0xff);

		last_soc = save_soc;
	}
}

static int rk817_bat_get_prev_dsoc(struct rk817_battery_device *battery)
{
	int value;

	value = rk817_bat_read(battery, SOC_REG0);
	value |= rk817_bat_read(battery, SOC_REG1) << 8;
	value |= rk817_bat_read(battery, SOC_REG2) << 16;

	return value;
}

static int rk817_bat_get_prev_cap(struct rk817_battery_device *battery)
{
	int val = 0;

	val = rk817_bat_read(battery, REMAIN_CAP_REG2) << 16;
	val |= rk817_bat_read(battery, REMAIN_CAP_REG1) << 8;
	val |= rk817_bat_read(battery, REMAIN_CAP_REG0) << 0;

	return val;
}

static void rk817_bat_gas_gaugle_enable(struct rk817_battery_device *battery)
{
	int value;

	value = rk817_bat_read(battery, ADC_CONFIG0);
	rk817_bat_write(battery, ADC_CONFIG0, value | 0x80);
}

static bool is_rk817_bat_first_pwron(struct rk817_battery_device *battery)
{
	int value;

	value = rk817_bat_read(battery, GG_STS);

	if (value & BAT_CON) {
		rk817_bat_write(battery, GG_STS, value & (~BAT_CON));
		return true;
	}

	return false;
}

static int rk817_bat_get_off_count(struct rk817_battery_device *battery)
{
	int value;

	value = rk817_bat_read(battery, OFF_CNT);
	rk817_bat_write(battery, OFF_CNT, 0x00);

	return value;
}

static void rk817_bat_update_qmax(struct rk817_battery_device *battery,
				  u32 capacity)
{
	u8 buf;
	u32 cap_adc;

	cap_adc = CAPACITY_TO_ADC(capacity, battery->res_div);
	buf = (cap_adc >> 24) & 0xff;
	rk817_bat_write(battery, Q_MAX_H3, buf);
	buf = (cap_adc >> 16) & 0xff;
	rk817_bat_write(battery, Q_MAX_H2, buf);
	buf = (cap_adc >> 8) & 0xff;
	rk817_bat_write(battery, Q_MAX_L1, buf);
	buf = (cap_adc >> 0) & 0xff;
	rk817_bat_write(battery, Q_MAX_L0, buf);

	battery->qmax = capacity;
}

static void rk817_bat_save_fcc(struct rk817_battery_device *battery, int  fcc)
{
	u8 buf;

	buf = (fcc >> 16) & 0xff;
	rk817_bat_write(battery, NEW_FCC_REG2, buf);
	buf = (fcc >> 8) & 0xff;
	rk817_bat_write(battery, NEW_FCC_REG1, buf);
	buf = (fcc >> 0) & 0xff;
	rk817_bat_write(battery, NEW_FCC_REG0, buf);
}

static void rk817_bat_first_pwron(struct rk817_battery_device *battery)
{
	battery->rsoc =
		rk817_bat_vol_to_soc(battery,
				     battery->pwron_voltage) * 1000;/* uAH */
	battery->dsoc = battery->rsoc;
	battery->fcc = battery->design_cap;

	battery->nac = rk817_bat_vol_to_cap(battery,
					    battery->pwron_voltage);

	rk817_bat_update_qmax(battery, battery->qmax);
	rk817_bat_save_fcc(battery, battery->fcc);
	DBG("%s, rsoc = %d, dsoc = %d, fcc = %d, nac = %d\n",
	    __func__, battery->rsoc, battery->dsoc, battery->fcc, battery->nac);
}

static int rk817_bat_get_fcc(struct rk817_battery_device *battery)
{
	u32 fcc = 0;

	fcc = rk817_bat_read(battery, NEW_FCC_REG2) << 16;
	fcc |= rk817_bat_read(battery, NEW_FCC_REG1) << 8;
	fcc |= rk817_bat_read(battery, NEW_FCC_REG0) << 0;

	if (fcc < MIN_FCC) {
		DBG("invalid fcc(%d), use design cap", fcc);
		fcc = battery->design_capacity;
		rk817_bat_save_fcc(battery, fcc);
	} else if (fcc > battery->qmax) {
		DBG("invalid fcc(%d), use qmax", fcc);
		fcc = battery->qmax;
		rk817_bat_save_fcc(battery, fcc);
	}

	return fcc;
}

static void rk817_bat_inc_halt_cnt(struct rk817_battery_device *battery)
{
	u8 cnt;

	cnt =  rk817_bat_read(battery, HALT_CNT_REG);
	rk817_bat_write(battery, HALT_CNT_REG, ++cnt);
}

static bool is_rk817_bat_last_halt(struct rk817_battery_device *battery)
{
	int pre_cap = rk817_bat_get_prev_cap(battery);
	int now_cap = rk817_bat_get_capacity_mah(battery);

	battery->nac = rk817_bat_vol_to_cap(battery,
					    battery->pwron_voltage);

	/* over 10%: system halt last time */
	if (now_cap > pre_cap) {
		if (abs(now_cap - pre_cap) > (battery->fcc / 10)) {
			rk817_bat_inc_halt_cnt(battery);
			return true;
		} else {
			return false;
		}
	} else {
		if (abs(battery->nac - pre_cap) > (battery->fcc / 5)) {
			rk817_bat_inc_halt_cnt(battery);
			return true;
		} else {
			return false;
		}
	}
}

static u8 rk817_bat_get_halt_cnt(struct rk817_battery_device *battery)
{
	return rk817_bat_read(battery, HALT_CNT_REG);
}

static int rk817_bat_is_initialized(struct rk817_battery_device *battery)
{
	u8 val = rk817_bat_read(battery, FG_INIT);

	return (val & 0x80);
}

static void rk817_bat_set_initialized_flag(struct rk817_battery_device *battery)
{
	u8 val = rk817_bat_read(battery, FG_INIT);

	rk817_bat_write(battery, FG_INIT, val | (0x80));
}

static void rk817_bat_not_first_pwron(struct rk817_battery_device *battery)
{
	int now_cap, pre_soc, pre_cap;
	int is_charge = 0, temp_soc = 0;

	battery->fcc = rk817_bat_get_fcc(battery);
	pre_soc = rk817_bat_get_prev_dsoc(battery);
	pre_cap = rk817_bat_get_prev_cap(battery);

	now_cap = rk817_bat_get_capacity_mah(battery);
	battery->halt_cnt = rk817_bat_get_halt_cnt(battery);
	battery->nac = rk817_bat_vol_to_cap(battery,
					    battery->pwron_voltage);
	battery->remain_cap = pre_cap * 1000;
	battery->is_halt = is_rk817_bat_last_halt(battery);

	if (now_cap == 0) {
		if (battery->pwroff_min > 3) {
			battery->nac = rk817_bat_vol_to_cap(battery,
					    battery->pwron_voltage);
			now_cap = battery->nac;
			pre_cap = now_cap;
			printf("now_cap 0x%x\n", now_cap);
		} else {
			now_cap = pre_cap;
		}

		rk817_bat_init_coulomb_cap(battery, now_cap);
		goto finish;
	}

	if (now_cap > pre_cap) {
		is_charge = 1;
		if ((now_cap > battery->fcc * 2) &&
		    ((battery->pwroff_min > 0) &&
		    (battery->pwroff_min < 3))) {
			now_cap = pre_cap;
			is_charge = 0;
		}
	} else {
		is_charge = 0;
	}

	if (is_charge == 0) {
		if ((battery->pwroff_min >= 0)  && (battery->pwroff_min < 3)) {
			rk817_bat_init_coulomb_cap(battery, pre_cap);
			rk817_bat_get_capacity_mah(battery);
			goto finish;
		}

		if (battery->pwroff_min >= 3) {
			if (battery->nac > pre_cap) {
				rk817_bat_init_coulomb_cap(battery,
							   battery->nac);
				rk817_bat_get_capacity_mah(battery);
				pre_cap = battery->nac;
				goto finish;
			}

			if ((pre_cap - battery->nac) > (battery->fcc / 10)) {
				rk817_bat_inc_halt_cnt(battery);
				temp_soc = (pre_cap - battery->nac) * 1000 * 100 / battery->fcc;
				pre_soc -= temp_soc;
				pre_cap = battery->nac;
				if (pre_soc <= 0)
					pre_soc = 0;
				goto finish;
			}
		}
	} else {
		battery->remain_cap = rk817_bat_get_capacity_uah(battery);
		battery->rsoc = rk817_bat_get_rsoc(battery);

		if (pre_cap < battery->remain_cap / 1000) {
			pre_soc += (battery->remain_cap - pre_cap * 1000) * 100 / battery->fcc;
			if (pre_soc > 100000)
				pre_soc = 100000;
		}
		pre_cap = battery->remain_cap / 1000;
		goto finish;
	}
finish:
	battery->dsoc = pre_soc;
	if (battery->dsoc > 100000)
		battery->dsoc = 100000;
	battery->nac = pre_cap;
	if (battery->nac < 0)
		battery->nac = 0;

	DBG("dsoc=%d cap=%d v=%d pwron_v =%d min=%d psoc=%d pcap=%d\n",
	    battery->dsoc, battery->nac, rk817_bat_get_battery_voltage(battery),
	    rk817_bat_get_pwron_voltage(battery),
	    battery->pwroff_min, rk817_bat_get_prev_dsoc(battery),
	    rk817_bat_get_prev_cap(battery));
}

static void rk817_bat_rsoc_init(struct rk817_battery_device *battery)
{
	battery->is_first_power_on = is_rk817_bat_first_pwron(battery);
	battery->pwroff_min = rk817_bat_get_off_count(battery);
	battery->pwron_voltage = rk817_bat_get_pwron_voltage(battery);

	DBG("battery = %d\n", rk817_bat_get_battery_voltage(battery));
	DBG("%s: is_first_power_on = %d, pwroff_min = %d, pwron_voltage = %d\n",
	    __func__, battery->is_first_power_on,
	    battery->pwroff_min, battery->pwron_voltage);

	if (battery->is_first_power_on)
		rk817_bat_first_pwron(battery);
	else
		rk817_bat_not_first_pwron(battery);

	 rk817_bat_save_dsoc(battery, battery->dsoc);
	 rk817_bat_save_cap(battery, battery->nac);
}

static int rk817_bat_calc_linek(struct rk817_battery_device *battery)
{
	int linek, diff, delta;

	battery->calc_dsoc = battery->dsoc;
	battery->calc_rsoc = battery->rsoc;
	battery->sm_old_cap = battery->remain_cap;

	delta = abs(battery->dsoc - battery->rsoc);
	diff = delta * 3;
	battery->sm_meet_soc = (battery->dsoc >= battery->rsoc) ?
			   (battery->dsoc + diff) : (battery->rsoc + diff);

	if (battery->dsoc < battery->rsoc)
		linek = 1000 * (delta + diff) / DIV(diff);
	else if (battery->dsoc > battery->rsoc)
		linek = 1000 * diff / DIV(delta + diff);
	else
		linek = 1000;

	battery->sm_chrg_dsoc = battery->dsoc;

	DBG("<%s>. meet=%d, diff=%d, link=%d, calc: dsoc=%d, rsoc=%d\n",
	    __func__, battery->sm_meet_soc, diff, linek,
	    battery->calc_dsoc, battery->calc_rsoc);

	return linek;
}

static int rk817_bat_get_est_voltage(struct rk817_battery_device *battery)
{
	return rk817_bat_get_battery_voltage(battery);
}

static int rk817_bat_update_get_voltage(struct udevice *dev)
{
	struct rk817_battery_device *battery = dev_get_priv(dev);

	if (!battery->virtual_power && battery->voltage_k)
		return rk817_bat_get_est_voltage(battery);
	else
		return VIRTUAL_POWER_VOL;
}

static int rk817_bat_update_get_current(struct udevice *dev)
{
	struct rk817_battery_device *battery = dev_get_priv(dev);

	if (!battery->virtual_power && battery->voltage_k)
		return rk817_bat_get_avg_current(battery);
	else
		return VIRTUAL_POWER_CUR;
}

static int rk817_bat_dwc_otg_check_dpdm(struct rk817_battery_device *battery)
{
	if (battery->variant == RK809_ID) {
		if (rk817_bat_read(battery, PMIC_SYS_STS) & PLUG_IN_STS)
			return AC_CHARGER;
		else
			return NO_CHARGER;
	} else {
		return  rockchip_chg_get_type();
	}
}

static bool rk817_bat_update_get_chrg_online(struct udevice *dev)
{
	struct rk817_battery_device *battery = dev_get_priv(dev);

	return rk817_bat_dwc_otg_check_dpdm(battery);
}

static int rk817_bat_get_usb_state(struct rk817_battery_device *battery)
{
	int charger_type;

	switch (rk817_bat_dwc_otg_check_dpdm(battery)) {
	case POWER_SUPPLY_TYPE_UNKNOWN:
		if ((rk817_bat_read(battery, PMIC_SYS_STS) & PLUG_IN_STS) != 0)
			charger_type = DC_CHARGER;
		else
			charger_type = NO_CHARGER;
		break;
	case POWER_SUPPLY_TYPE_USB:
		charger_type = USB_CHARGER;
		break;
	case POWER_SUPPLY_TYPE_USB_DCP:
	case POWER_SUPPLY_TYPE_USB_CDP:
	case POWER_SUPPLY_TYPE_USB_FLOATING:
		charger_type = AC_CHARGER;
		break;
	default:
		charger_type = NO_CHARGER;
	}

	return charger_type;
}

static int rk817_bat_get_charger_type(struct rk817_battery_device *battery)
{
	u32 chrg_type;

	/* check by ic hardware: this check make check work safer */
	if ((rk817_bat_read(battery, PMIC_SYS_STS) & PLUG_IN_STS) == 0)
		return NO_CHARGER;

	/* virtual or bat not exist */
	if (battery->virtual_power)
		return DC_CHARGER;

	/* check USB secondly */
	chrg_type = rk817_bat_get_usb_state(battery);
	if (chrg_type != NO_CHARGER && battery->rsoc / 1000 >= 100)
		chrg_type = CHARGE_FINISH;

	return chrg_type;
}

static void rk817_bat_set_input_current(struct rk817_battery_device *battery,
					int input_current)
{
	u8 usb_ctrl;

	usb_ctrl = rk817_bat_read(battery, USB_CTRL_REG);
	usb_ctrl &= ~INPUT_CUR_MSK;
	usb_ctrl |= ((input_current) | 0x08);
	rk817_bat_write(battery, USB_CTRL_REG, usb_ctrl);
}

static void rk817_bat_set_input_voltage(struct rk817_battery_device *battery,
					int input_voltage)
{
	u8 usb_ctrl;

	usb_ctrl = rk817_bat_read(battery, USB_CTRL_REG);
	usb_ctrl &= ~INPUT_VOL_MSK;
	usb_ctrl |= ((input_voltage) | 0x80);
	rk817_bat_write(battery, USB_CTRL_REG, usb_ctrl);
}

static void rk817_bat_charger_setting(struct rk817_battery_device *battery,
				      int charger)
{
	static u8 old_charger = UNDEF_CHARGER;

	rk817_bat_set_input_voltage(battery, VLIM_4500MV);
	/* charger changed */
	if (old_charger != charger) {
		if (charger == NO_CHARGER) {
			DBG("NO_CHARGER\n");
			rk817_bat_set_input_current(battery, ILIM_450MA);
		} else if (charger == USB_CHARGER) {
			DBG("USB_CHARGER\n");
			rk817_bat_set_input_current(battery, ILIM_450MA);
		} else if (charger == DC_CHARGER || charger == AC_CHARGER) {
			DBG("DC OR AC CHARGE\n");
			rk817_bat_set_input_current(battery, ILIM_1500MA);
		} else {
			DBG("charger setting error %d\n", charger);
		}

		old_charger = charger;
	}
}

static void rk817_bat_linek_algorithm(struct rk817_battery_device *battery)
{
	int delta_cap, ydsoc, tmp;
	u8 chg_st = rk817_bat_get_charger_type(battery);

	/* slow down */
	if (battery->dsoc / 1000 == 99)
		battery->sm_linek = CHRG_FULL_K;
	else if (battery->dsoc / 1000 >= CHRG_TERM_DSOC &&
		 battery->current_avg > TERM_CALI_CURR)
		battery->sm_linek = CHRG_TERM_K;

	delta_cap = battery->remain_cap - battery->sm_old_cap;
	ydsoc = battery->sm_linek * (delta_cap  / DIV(battery->fcc)) / 10;
	battery->sm_chrg_dsoc += ydsoc;

	tmp = battery->sm_chrg_dsoc / 1000;

	if (ydsoc > 0) {
		if (battery->sm_chrg_dsoc < 0)
			battery->sm_chrg_dsoc = 0;

		tmp = battery->sm_chrg_dsoc / 1000;

		if (tmp != battery->dsoc / 1000) {
			if (battery->sm_chrg_dsoc < battery->dsoc)
				return;

			battery->dsoc = battery->sm_chrg_dsoc;
			if (battery->dsoc <= 0)
				battery->dsoc = 0;
		}

		battery->sm_old_cap = battery->remain_cap;
		if (battery->dsoc / 1000 == battery->rsoc / 1000 &&
		    battery->sm_linek != CHRG_FULL_K &&
		    battery->sm_linek != CHRG_TERM_K)
			battery->sm_linek = 1000;
	}

	if ((battery->sm_linek == 1000 || battery->dsoc >= 100 * 1000) &&
	    (chg_st != CHARGE_FINISH)) {
		if (battery->sm_linek == 1000)
			battery->dsoc = battery->rsoc;
		battery->sm_chrg_dsoc = battery->dsoc;
	}
}

static void rk817_bat_finish_chrg(struct rk817_battery_device *battery)
{
	u32 tgt_sec = 0;

	if (battery->dsoc / 1000 < 100) {
		tgt_sec = battery->fcc * 3600 / 100 / FINISH_CALI_CURR;
		if (get_timer(battery->finish_chrg_base) > SECONDS(tgt_sec)) {
			battery->finish_chrg_base = get_timer(0);
			battery->dsoc += 1000;
		}
	}
}

static void rk817_bat_debug_info(struct rk817_battery_device *battery)
{
	DBG("debug info:\n");
	DBG("CAL_OFFSET = 0x%x", rk817_bat_read(battery, CAL_OFFSET_H));
	DBG("%x\n", rk817_bat_read(battery, CAL_OFFSET_L));
	DBG("current_avg = %d\n", rk817_bat_get_avg_current(battery));
	DBG("k = %d, b = %d\n", battery->voltage_k, battery->voltage_b);
	DBG("battery: %d\n", rk817_bat_get_battery_voltage(battery));
	DBG("voltage_sys = %d\n", rk817_bat_get_sys_voltage(battery));
	DBG("voltage_usb = %d\n", rk817_bat_get_USB_voltage(battery));
	DBG("current_avg = %d\n", rk817_bat_get_avg_current(battery));
	DBG("dsoc = %d\n", battery->dsoc);
	DBG("rsoc = %d\n", rk817_bat_get_rsoc(battery));
	DBG("remain_cap = %d\n", rk817_bat_get_capacity_uah(battery));
	DBG("fcc = %d\n", battery->fcc);
	DBG("qmax = %d\n", battery->qmax);
}

static void rk817_bat_smooth_charge(struct rk817_battery_device *battery)
{
	u8 chg_st = rk817_bat_get_charger_type(battery);

	rk817_bat_debug_info(battery);
	rk817_bat_calibration(battery);
	/* set terminal charge mode */
	if (battery->term_sig_base &&
	    get_timer(battery->term_sig_base) > SECONDS(1))
		battery->term_sig_base = 0;

	/* not charge mode and not keep in uboot charge: exit */
	if ((battery->chrg_type == NO_CHARGER) ||
	    !rk817_bat_is_initialized(battery)) {
		DBG("chrg=%d\n", battery->chrg_type);
		rk817_bat_set_initialized_flag(battery);
		goto out;
	}

	/* update rsoc and remain cap */
	battery->remain_cap = rk817_bat_get_capacity_uah(battery);
	battery->rsoc = rk817_bat_get_rsoc(battery);
	if (battery->remain_cap / 1000 > battery->fcc) {
		battery->sm_old_cap -=
			(battery->remain_cap - battery->fcc * 1000);
		rk817_bat_init_coulomb_cap(battery, battery->fcc + 100);
		rk817_bat_init_coulomb_cap(battery, battery->fcc);
	}

	/* finish charge step */
	if (chg_st == CHARGE_FINISH) {
		rk817_bat_finish_chrg(battery);
		rk817_bat_init_coulomb_cap(battery, battery->fcc + 100);
		rk817_bat_init_coulomb_cap(battery, battery->fcc);
	} else {
		DBG("smooth charge step...\n");
		battery->adc_allow_update = true;
		battery->finish_chrg_base = get_timer(0);
		rk817_bat_linek_algorithm(battery);
	}

	/* dsoc limit */
	if (battery->dsoc / 1000 > 100)
		battery->dsoc = 100 * 1000;
	else if (battery->dsoc < 0)
		battery->dsoc = 0;

	rk817_bat_save_dsoc(battery, battery->dsoc);
	rk817_bat_save_cap(battery, battery->remain_cap / 1000);
out:
	return;
}

static int rk817_bat_update_get_soc(struct udevice *dev)
{
	struct rk817_battery_device *battery = dev_get_priv(dev);
	static ulong seconds;

	rk817_bat_debug_info(battery);
	/* set charge current */
	battery->chrg_type =
		rk817_bat_get_charger_type(battery);
	rk817_bat_charger_setting(battery, battery->chrg_type);

	/* fg calc every 5 seconds */
	if (!seconds)
		seconds = get_timer(0);
	if (get_timer(seconds) >= SECONDS(5)) {
		seconds = get_timer(0);
		rk817_bat_smooth_charge(battery);
	}

	/* bat exist, fg init success(dts pass) and uboot charge: report data */
	if (!battery->virtual_power && battery->voltage_k)
		return battery->dsoc / 1000;
	else
		return VIRTUAL_POWER_SOC;
}

static int rk817_is_bat_exist(struct rk817_battery_device *battery)
{
	struct rk8xx_priv *rk8xx = dev_get_priv(battery->dev->parent);

	if (rk8xx->variant == RK817_ID)
		return (rk817_bat_read(battery, PMIC_CHRG_STS) & 0x80) ? 1 : 0;

	return 1;
}

static int rk817_bat_bat_is_exist(struct udevice *dev)
{
        struct rk817_battery_device *battery = dev_get_priv(dev);

        return rk817_is_bat_exist(battery);
}


static struct dm_fuel_gauge_ops fg_ops = {
	.bat_is_exist = rk817_bat_bat_is_exist,
	.get_soc = rk817_bat_update_get_soc,
	.get_voltage = rk817_bat_update_get_voltage,
	.get_current = rk817_bat_update_get_current,
	.get_chrg_online = rk817_bat_update_get_chrg_online,
};

static int rk817_fg_ofdata_to_platdata(struct udevice *dev)
{
	struct rk8xx_priv *rk8xx = dev_get_priv(dev->parent);
	struct rk817_battery_device *battery = dev_get_priv(dev);
	const char *prop;
	int  len, value;
	int i;

	if ((rk8xx->variant != RK817_ID) && (rk8xx->variant != RK809_ID)) {
		debug("%s: Not support pmic variant: rk%x\n",
		      __func__, rk8xx->variant);
		return -EINVAL;
	}

	battery->dev = dev;
	battery->variant = rk8xx->variant;
	/* Parse ocv table */
	prop = dev_read_prop(dev, "ocv_table", &len);
	if (!prop) {
		printf("can't find ocv_table prop\n");
		return -EINVAL;
	}

	battery->ocv_table = calloc(len, 1);
	if (!battery->ocv_table) {
		printf("can't calloc ocv_table\n");
		return -ENOMEM;
	}

	battery->ocv_size = len / 4;
	if (dev_read_u32_array(dev, "ocv_table",
			       battery->ocv_table, battery->ocv_size)) {
		printf("can't read ocv_table\n");
		free(battery->ocv_table);
		return -EINVAL;
	}

	/* Parse neccessay */
	battery->design_cap = dev_read_u32_default(dev, "design_capacity", -1);
	if (battery->design_cap < 0) {
		printf("can't read design_capacity\n");
		return -EINVAL;
	}

	battery->qmax = dev_read_u32_default(dev, "design_qmax", -1);
	if (battery->qmax < 0) {
		printf("can't read design_qmax\n");
		return -EINVAL;
	}

	battery->virtual_power = dev_read_u32_default(dev, "virtual_power", 0);
	if (!rk817_is_bat_exist(battery))
		battery->virtual_power = 1;

	if (rk8xx->variant == RK809_ID) {
		battery->bat_res_up  = dev_read_u32_default(dev, "bat_res_up", -1);
		if (battery->bat_res_up < 0) {
			printf("can't read bat_res_up\n");
			return -EINVAL;
		}

		battery->bat_res_down  = dev_read_u32_default(dev, "bat_res_down", -1);
		if (battery->bat_res_down < 0) {
			printf("can't read bat_res_down\n");
			return -EINVAL;
		}
	}

	value = dev_read_u32_default(dev, "sample_res", -1);
	if (battery->res_div < 0)
		printf("read sample_res error\n");

	battery->res_div = (value == SAMPLE_RES_20mR) ?
		       SAMPLE_RES_DIV2 : SAMPLE_RES_DIV1;

	DBG("OCV Value:");
	for (i = 0; i < battery->ocv_size; i++)
		DBG("%d  ", battery->ocv_table[i]);
	DBG("ocvsize: %d\n", battery->ocv_size);
	DBG("battery->design_cap: %d\n", battery->design_cap);
	DBG("battery->qmax: %d\n", battery->qmax);
	DBG("battery->bat_res_up: %d\n", battery->bat_res_up);
	DBG("battery->bat_res_down: %d\n", battery->bat_res_down);

	return 0;
}

static int rk817_fg_init(struct rk817_battery_device *battery)
{
	int value;

	value = rk817_bat_read(battery, GG_CON);
	rk817_bat_write(battery, GG_CON, value | VOL_OUPUT_INSTANT_MODE);
	if (battery->variant == RK817_ID) {
		value =  rk817_bat_read(battery, BAT_DISCHRG);
		rk817_bat_write(battery, BAT_DISCHRG, value & (~DIS_ILIM_EN));
	}
	rk817_bat_gas_gaugle_enable(battery);
	rk817_bat_init_voltage_kb(battery);
	rk817_bat_calibration(battery);
	rk817_bat_rsoc_init(battery);
	rk817_bat_init_coulomb_cap(battery, battery->nac);
	rk817_bat_set_initialized_flag(battery);

	battery->voltage_avg = rk817_bat_get_battery_voltage(battery);
	battery->voltage_sys = rk817_bat_get_sys_voltage(battery);
	battery->voltage_usb = rk817_bat_get_USB_voltage(battery);
	battery->current_avg = rk817_bat_get_avg_current(battery);
	battery->current_pwron = rk817_bat_get_pwron_current(battery);
	battery->remain_cap = rk817_bat_get_capacity_uah(battery);
	battery->rsoc = rk817_bat_get_rsoc(battery);
	battery->sm_linek = rk817_bat_calc_linek(battery);
	battery->chrg_type = rk817_bat_get_charger_type(battery);
	battery->finish_chrg_base = get_timer(0);
	battery->term_sig_base = get_timer(0);

	battery->dbg_pwr_dsoc = battery->dsoc;
	battery->dbg_pwr_rsoc = battery->rsoc;
	battery->dbg_pwr_vol = battery->voltage_avg;

	if (battery->variant == RK817_ID)
		rk817_bat_charger_setting(battery, battery->chrg_type);

	DBG("voltage_k = %d, voltage_b = %d\n",
	    battery->voltage_k, battery->voltage_b);
	DBG("voltage_sys = %d\n", battery->voltage_sys);
	DBG("voltage usb: %d\n", battery->voltage_avg);
	DBG("battery: %d\n", battery->voltage_avg);
	DBG("current_avg = %d\n", battery->current_avg);
	DBG("current_pwron = %d\n", battery->current_pwron);
	DBG("remain_cap = %d\n", battery->remain_cap);
	DBG("fcc = %d\n", battery->fcc);
	DBG("qmax = %d\n", battery->qmax);
	DBG("dsoc = %d\n", battery->dsoc);
	DBG("rsoc = %d\n", battery->rsoc);
	DBG("charge type: %d\n", battery->chrg_type);

	return 0;
}

static int rk817_fg_probe(struct udevice *dev)
{
	struct rk8xx_priv *priv = dev_get_priv(dev->parent);
	struct rk817_battery_device *battery = dev_get_priv(dev);

	if ((priv->variant != RK817_ID) && ((priv->variant != RK809_ID))) {
		debug("Not support pmic variant: rk%x\n", priv->variant);
		return -EINVAL;
	}

	return rk817_fg_init(battery);
}

U_BOOT_DRIVER(rk817_fg) = {
	.name = "rk817_fg",
	.id = UCLASS_FG,
	.probe = rk817_fg_probe,
	.ops = &fg_ops,
	.ofdata_to_platdata = rk817_fg_ofdata_to_platdata,
	.priv_auto_alloc_size = sizeof(struct rk817_battery_device),
};
