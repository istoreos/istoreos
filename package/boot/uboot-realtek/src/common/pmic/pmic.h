/*
 * APIs & helper macros for PMIC
 *
 * Copyright (C) 2016-2017 Realtek Semiconductor Corporation
 * Copyright (C) 2016-2017 Cheng-Yu Lee <cylee12@realtek.com>
 */
#ifndef __PMIC_H__
#define __PMIC_H__

#include "pmic-common.h"

/********************************************************************************
 * error code 
 ********************************************************************************/
#define PMIC_OK    0
#define PMIC_ERR  -1

/********************************************************************************
 * helper macros 
 ********************************************************************************/

#define PMIC_SET_REG(_v)   (((_v) & 0xff) << 0)
#define PMIC_SET_SIZE(_v)  (((_v) & 0xf) << 8)
#define PMIC_SET_SHIFT(_v) (((_v) & 0xf) << 12)
#define PMIC_GET_REG(_v)   (((_v) >> 0) & 0xff)
#define PMIC_GET_SIZE(_v)  (((_v) >> 8) & 0xf)
#define PMIC_GET_SHIFT(_v) (((_v) >> 12) & 0xf)
#define PMIC_GET_MASK(_v)  ((_BIT(PMIC_GET_SIZE(_v)) - 1) << PMIC_GET_SHIFT(_v))

#define PMIC_DEF_ITEM(_r, _s, _sh) \
	(PMIC_SET_REG(_r) | PMIC_SET_SIZE(_s) | PMIC_SET_SHIFT(_sh))

#define REG_FIELD(_r, _lsb, _msb) \
	PMIC_DEF_ITEM(_r, (_msb) - (_lsb) + 1, _lsb)

/********************************************************************************
 * value
 ********************************************************************************/
#define GMT_TESTING PMIC_DEF_ITEM(0xf1, 0, 5)

struct reg_info {
	const char *name;
	int id;
	int info;
	const char * const *tbl;
	int tbl_size;
	unsigned int flags;
};

#define DEF_REG(_name, _id, _tbl) \
{                               \
        .name = _name,          \
	.id = _id,              \
	.tbl = _tbl,            \
	.tbl_size = ARRAY_SIZE(_tbl), \
	.flags = 0,             \
}

struct cmd_pmic_data {
	const unsigned int *regfields;
	int num_regfields;
	struct reg_info *regs;
	int num_regs;
	const char * const *col;
	int num_col;
	const char * const *row;
	int num_row;
};


int pmic_init(void);
void pmic_exit(void);
int pmic_read_reg(unsigned char reg, unsigned char *val);
int pmic_write_reg(unsigned char reg, unsigned char val);
int pmic_get(unsigned int cmd, unsigned char *val);
int pmic_set(unsigned int cmd, unsigned char val);

const char *pmic_get_name(void);
void pmic_setup_pmic(void);
const struct cmd_pmic_data *pmic_get_cmd_data(void);
#endif
