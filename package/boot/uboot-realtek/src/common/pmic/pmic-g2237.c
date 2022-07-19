/*
 * pmic-g2237.c
 *
 * Copyright (C) 2017 Realtek Semiconductor Corporation
 * Copyright (C) 2017 Cheng-Yu Lee <cylee12@realtek.com>
 *
 */
#include "pmic.h"
#include "pmic-g2237.h"

static const unsigned int regfields[PMIC_G2237_MAX] = {
	[PMIC_G2237_LPOFF_TO_DO] = REG_FIELD(0x02, 7, 7),
	[PMIC_G2237_SOFTOFF] = REG_FIELD(0x04, 7, 7),
	[PMIC_G2237_DC1_ON] = REG_FIELD(0x05, 7, 7),
	[PMIC_G2237_DC2_ON] = REG_FIELD(0x05, 6, 6),
	[PMIC_G2237_DC3_ON] = REG_FIELD(0x05, 5, 5),
	[PMIC_G2237_DC4_ON] = REG_FIELD(0x05, 4, 4),
	[PMIC_G2237_DC5_ON] = REG_FIELD(0x05, 3, 3),
	[PMIC_G2237_LDO1_ON] = REG_FIELD(0x05, 0, 0),
	[PMIC_G2237_DC1_NMODE] = REG_FIELD(0x07, 6, 7),
	[PMIC_G2237_DC1_SMODE] = REG_FIELD(0x07, 4, 5),
	[PMIC_G2237_DC2_NMODE] = REG_FIELD(0x07, 2, 3),
	[PMIC_G2237_DC2_SMODE] = REG_FIELD(0x07, 0, 1),
	[PMIC_G2237_DC3_NMODE] = REG_FIELD(0x08, 6, 7),
	[PMIC_G2237_DC3_SMODE] = REG_FIELD(0x08, 4, 5),
	[PMIC_G2237_DC4_NMODE] = REG_FIELD(0x08, 2, 3),
	[PMIC_G2237_DC4_SMODE] = REG_FIELD(0x08, 0, 1),
	[PMIC_G2237_DC5_NMODE] = REG_FIELD(0x09, 6, 7),
	[PMIC_G2237_DC5_SMODE] = REG_FIELD(0x09, 4, 5),
	[PMIC_G2237_LDO1_NMODE] = REG_FIELD(0x09, 2, 3),
	[PMIC_G2237_LDO1_SMODE] = REG_FIELD(0x09, 0, 1),
	[PMIC_G2237_DC1_NVO] = REG_FIELD(0x0A, 0, 3),
	[PMIC_G2237_DC2_NVO] = REG_FIELD(0x0B, 0, 4),
	[PMIC_G2237_DC3_NVO] = REG_FIELD(0x0C, 0, 4),
	[PMIC_G2237_DC5_NVO] = REG_FIELD(0x0D, 0, 3),
	[PMIC_G2237_LDO1_NVO] = REG_FIELD(0x0E, 0, 3),
	[PMIC_G2237_DC1_SVO] = REG_FIELD(0x0F, 0, 3),
	[PMIC_G2237_DC2_SVO] = REG_FIELD(0x10, 0, 4),
	[PMIC_G2237_DC3_SVO] = REG_FIELD(0x11, 0, 4),
	[PMIC_G2237_DC5_SVO] = REG_FIELD(0x12, 0, 3),
	[PMIC_G2237_LDO1_SVO] = REG_FIELD(0x13, 0, 3),
};

static const char * const dcdc_mode[] = {
	"auto", "auto", "force_pwm", "auto,x_eco",
};

static const char * const dcdc_slpmode[] = {
	"auto,x_eco", "auto,v=nrm", "auto,v=slp", "shutdown",
};

static const char * const dcdc4_slpmode[] = {
	"auto,x_eco", "auto", "auto", "shutdown",
};

static const char * const ldo_mode[] = {
	"nrm", "nrm", "eco", "nrm",
};

static const char * const ldo_slpmode[] = {
	"nrm,v=nrm", "nrm,v=slp", "eco", "shutdown",
};

static const char * const softoff[] = {
	"on", "off",
};

static const char * const endis[] = {
	"disable", "enable",
};

static const char * const onoff[] = {
	"shutdown", "operation",
};

static const char * const lpoff_to_do[] = {
	"act1", "act2",
};

static const char * const enlpoff[] = {
	"no", "yes",
};

static const char * const time_it[] = {
	"128ms", "500ms", "1000ms", "1500ms",
};

static const char * const time_lp[] = {
	"1s", "2s", "3s", "4s",
};

static const char * const time_lpoff[] = {
	"6s", "7s", "8s", "10s",
};


static const char * const dcdc1 [] = {
	"3000000", "3100000", "3200000", "3300000",
};

static const char * const dcdc [] = {
	"800000", "812500", "825000", "837500",
	"850000", "862500", "875000", "887500",
	"900000", "912500", "925000", "937500",
	"950000", "962500", "975000", "987500",
	"1000000", "1012500", "1025000", "1037500",
	"1050000", "1062500", "1075000", "1087500",
	"1100000", "1112500", "1125000", "1137500",
	"1150000", "1162500", "1175000", "1187500",
};

static const char * const ldo [] = {
	"800000",  "850000",  "900000",  "950000",
	"1000000", "1100000", "1200000", "1300000",
	"1500000", "1600000", "1800000", "1900000",
	"2500000", "2600000", "3000000", "3100000",
};

static const char * const ldo1[] = {
	"2200000", "2300000", "2400000", "2500000",
	"2600000", "2700000", "2800000", "2900000",
	"3000000", "3000000", "3000000", "3000000",
	"3000000", "3000000", "3000000", "3000000",
};

static const char * const dc1[] = {
	"2200000", "2300000", "2400000", "2500000",
	"2600000", "2700000", "2800000", "2900000",
	"3000000", "3100000", "3200000", "3300000",
	"3400000", "3500000", "3600000", "3700000",
};

static const char * const dc5[] = {
	"800000",  "850000",  "900000",  "950000",
	"1000000", "1050000", "1100000", "1200000",
	"1300000", "1500000", "1600000", "1700000",
	"1800000", "1900000", "2000000", "2500000",
};

static struct reg_info regs[] = {
	DEF_REG("dc1_mode", PMIC_G2237_DC1_NMODE, dcdc_mode),
	DEF_REG("dc2_mode", PMIC_G2237_DC2_NMODE, dcdc_mode),
	DEF_REG("dc3_mode", PMIC_G2237_DC3_NMODE, dcdc_mode),
	DEF_REG("dc4_mode", PMIC_G2237_DC4_NMODE, dcdc_mode),
	DEF_REG("dc5_mode", PMIC_G2237_DC5_NMODE, dcdc_mode),
	DEF_REG("ldo1_mode", PMIC_G2237_LDO1_NMODE, ldo_mode),
	DEF_REG("dc1_slpmode", PMIC_G2237_DC1_SMODE, dcdc_slpmode),
	DEF_REG("dc2_slpmode", PMIC_G2237_DC2_SMODE, dcdc_slpmode),
	DEF_REG("dc3_slpmode", PMIC_G2237_DC3_SMODE, dcdc_slpmode),
	DEF_REG("dc4_slpmode", PMIC_G2237_DC4_SMODE, dcdc4_slpmode),
	DEF_REG("dc5_slpmode", PMIC_G2237_DC5_SMODE, dcdc_slpmode),
	DEF_REG("ldo1_slpmode", PMIC_G2237_LDO1_SMODE, ldo_slpmode),
	DEF_REG("dc1_volt", PMIC_G2237_DC1_NVO, dc1),
	DEF_REG("dc2_volt", PMIC_G2237_DC2_NVO, dcdc),
	DEF_REG("dc3_volt", PMIC_G2237_DC3_NVO, dcdc),
	DEF_REG("dc5_volt", PMIC_G2237_DC5_NVO, dc5),
	DEF_REG("ldo1_volt", PMIC_G2237_LDO1_NVO, ldo1),
	DEF_REG("dc1_slpvolt", PMIC_G2237_DC1_SVO, dc1),
	DEF_REG("dc2_slpvolt", PMIC_G2237_DC2_SVO, dcdc),
	DEF_REG("dc3_slpvolt", PMIC_G2237_DC3_SVO, dcdc),
	DEF_REG("dc5_slpvolt", PMIC_G2237_DC5_SVO, dc5),
	DEF_REG("ldo1_slpvolt", PMIC_G2237_LDO1_SVO, ldo1),
	DEF_REG("dc1_onoff", PMIC_G2237_DC1_ON, onoff),
	DEF_REG("dc2_onoff", PMIC_G2237_DC2_ON, onoff),
	DEF_REG("dc3_onoff", PMIC_G2237_DC3_ON, onoff),
	DEF_REG("dc4_onoff", PMIC_G2237_DC4_ON, onoff),
	DEF_REG("dc5_onoff", PMIC_G2237_DC5_ON, onoff),
	DEF_REG("ldo1_onoff", PMIC_G2237_LDO1_ON, onoff),
	DEF_REG("softoff", PMIC_G2237_SOFTOFF, softoff),
	DEF_REG("lpoff_to_do", PMIC_G2237_LPOFF_TO_DO, lpoff_to_do),
};

static const char * const row[] = {
	"dc1", "dc2", "dc3", "dc4", "dc5", "ldo1",
};

static const char * const col[] = {
	"onoff", "mode", "volt", "slpmode", "slpvolt",
};

static struct cmd_pmic_data cmd_pmic_data = {
	.regfields = regfields,
	.num_regfields = ARRAY_SIZE(regfields),
	.regs = regs,
	.num_regs = ARRAY_SIZE(regs),
	.row = row,
	.num_row = ARRAY_SIZE(row),
	.col = col,
	.num_col = ARRAY_SIZE(col),
};

const char *pmic_get_name(void)
{
	return "gmt,g2237";
}

void pmic_setup_pmic(void)
{}

const struct cmd_pmic_data *pmic_get_cmd_data(void)
{
	return &cmd_pmic_data;
}

