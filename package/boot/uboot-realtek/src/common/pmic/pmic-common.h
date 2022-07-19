/*
 * common API
 *
 * Copyright (C) 2016-2017 Realtek Semiconductor Corporation
 * Copyright (C) 2016-2017 Cheng-Yu Lee <cylee12@realtek.com>
 */
#ifndef __PMIC_COMMON_H__
#define __PMIC_COMMON_H__

/********************************************************************************
 * helper macros 
 ********************************************************************************/
#define _BIT(_n)      (1 << (_n))

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(arr)   (int) (sizeof(arr) / sizeof((arr)[0]))
#endif

#ifndef atoi
static inline int atoi(const char *str)
{
	int val = 0;
	while (*str != 0) {
		val = val * 10 + (int)(*str - '0');
		str ++;
	}
	return val;
}
#endif

//#define PMIC_DBG

#ifdef PMIC_DBG
#define PMIC_DBG_PR(fmt, ...) printf(fmt, __VA_ARGS__);
#else
#define PMIC_DBG_PR(fmt, ...)
#endif

#endif
