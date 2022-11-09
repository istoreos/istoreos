/*
 * Copyright 2017, Rockchip Electronics Co., Ltd
 * hisping lin, <hisping.lin@rock-chips.com>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */
#ifndef _OPTEE_CLIENT_MEM_H_
#define _OPTEE_CLIENT_MEM_H_

#include <linux/types.h>

int OpteeClientMemInit(void);

void *OpteeClientMemAlloc(uint32_t length);

void  OpteeClientMemFree(void *mem);

#endif /*_OPTEE_CLIENT_MEM_H_*/
