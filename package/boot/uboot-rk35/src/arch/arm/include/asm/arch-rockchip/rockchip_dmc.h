/* SPDX-License-Identifier:     GPL-2.0+ */
/*
 * (C) Copyright 2018 Rockchip Electronics Co., Ltd
 */

#ifndef __ROCKCHIP_DMC_H_
#define __ROCKCHIP_DMC_H_
#include <dm.h>

#ifndef MHZ
#define MHZ		(1000 * 1000)
#endif

int rockchip_ddrclk_sip_set_rate_v2(unsigned long drate);
unsigned long rockchip_ddrclk_sip_recalc_rate_v2(void);
unsigned long rockchip_ddrclk_sip_round_rate_v2(unsigned long rate);
int rockchip_dmcfreq_probe(struct udevice *dev);
int set_ddr_freq(unsigned long freq);

#endif
