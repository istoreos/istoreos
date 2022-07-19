#ifndef __RTK_I2C_POW_H__
#define __RTK_I2C_POW_H__
#include <common.h>

#ifdef CONFIG_RTD1395
void rtk_i2c_set_pow(int BusId);
void rtk_i2c_clear_pow(int BusId);
#else
static inline void rtk_i2c_set_pow(int BusId)
{}

static inline void rtk_i2c_clear_pow(int BusId)
{}
#endif

#endif

