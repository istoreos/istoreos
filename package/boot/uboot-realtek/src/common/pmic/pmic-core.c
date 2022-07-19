/*
 * pmic-core.c
 *
 * Copyright (C) 2016-2017 Realtek Semiconductor Corporation
 * Copyright (C) 2016-2017 Cheng-Yu Lee <cylee12@realtek.com>
 */
#include <common.h>
#include "../../drivers/i2c/rtk_i2c-lib.h"
#include "pmic.h"

#define I2C_CH  0
#define PMIC_ADDR 0x12

static unsigned int i2c_ch = I2C_CH;
static unsigned int pmic_addr = PMIC_ADDR;
static volatile int i2c_init = 0;
static int __do_testing = 1;

static int pmic_test(void)
{
	unsigned char val;
	int ret;

	if (!__do_testing)
		return 0;
	
	__do_testing = 0;
	ret = pmic_get(GMT_TESTING, &val);
	if (ret) {
		printf("failed to do pmic_testing\n");
		return PMIC_ERR;
	}
		
	printf("pmic_testing returns %02x\n", val);
	return 0;
}

int pmic_init(void)
{
	I2CN_Init(i2c_ch);
	i2c_init = 1;

	return pmic_test();
}

void pmic_exit(void)
{
	i2c_init = 0;
	I2CN_UnInit(i2c_ch);
}

int pmic_write_reg(unsigned char reg, unsigned char val)
{
	unsigned char data[2] = { reg, val };
	int ret;

	if (!i2c_init)
		return PMIC_ERR;

	ret = I2C_Write_EX(i2c_ch, pmic_addr, 2, data, NO_READ);
	if (ret) {
		return PMIC_ERR;
	}
	return 0;
}

int pmic_read_reg(unsigned char reg, unsigned char *val)
{
	unsigned char out;
	int ret;

	ret = I2C_Write_EX(i2c_ch, pmic_addr, 1, &reg, NON_STOP);
	 
	ret = I2C_Read_EX(i2c_ch, pmic_addr, 1, &reg, 1, &out, NON_STOP);
	if (ret) {
		PMIC_DBG_PR("[DBG] %s: I2C_Read_EX: ret = %d\n", __func__, ret);
		return PMIC_ERR;;
	}
	*val = out;

	return 0;
}

int pmic_set(unsigned int cmd, unsigned char val)
{
	unsigned char reg   = PMIC_GET_REG(cmd);
	unsigned char size  = PMIC_GET_SIZE(cmd);
	unsigned char shift = PMIC_GET_SHIFT(cmd);
	unsigned char mask  = PMIC_GET_MASK(cmd);
	unsigned char out;
	int ret = 0;

	PMIC_DBG_PR("[DBG] %s: REG 0x%02x SIZE 0x%02x SHIFT 0x%02x MASK 0x%02x\n",
		__func__, reg, size, shift, mask);

	if (size != 8) {
		ret = pmic_read_reg(reg, &out);
		if (ret) 
			return ret;

		out = (out & ~mask) | ((val << shift) & mask);
	} else {
		out = val;
	}

	ret = pmic_write_reg(reg, out);
	return ret;
}

int pmic_get(unsigned int cmd, unsigned char *val)
{
	unsigned char reg   = PMIC_GET_REG(cmd);
	unsigned char shift = PMIC_GET_SHIFT(cmd);
	unsigned char mask  = PMIC_GET_MASK(cmd);
	unsigned char out;
	int ret = 0;
	
	ret = pmic_read_reg(reg, &out);
	if (ret)
		return ret;

	*val = (out & mask) >> shift;
	return ret;
}

