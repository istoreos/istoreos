// SPDX-License-Identifier: GPL-2.0
/*
 * (C) Copyright 2020 Rockchip Electronics Co., Ltd.
 */

#include <common.h>
#include <debug_uart.h>
#include <dm.h>
#include <ram.h>
#include <syscon.h>
#include <asm/io.h>
#include <asm/arch-rockchip/clock.h>
#include <asm/arch-rockchip/hardware.h>
#include <asm/arch-rockchip/rk_atags.h>
#include <asm/arch-rockchip/cru_rk3568.h>
#include <asm/arch-rockchip/grf_rk3568.h>

#ifdef CONFIG_TPL_BUILD
#ifndef CONFIG_TPL_TINY_FRAMEWORK
#error please defined CONFIG_TPL_TINY_FRAMEWORK for RK3568 !!!
#endif
#endif

#ifdef CONFIG_TPL_BUILD

/* return: 0 = success, other = fail */
int sdram_init(void)
{
	return (-1);
}
#endif /* CONFIG_TPL_BUILD */
