/*
 * (C) Copyright 2022 Rockchip Electronics Co., Ltd
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */

#ifndef _RK_TIMER_IRQ_H
#define _RK_TIMER_IRQ_H

#include <irq-platform.h>

#ifdef CONFIG_ROCKCHIP_RK3399
#define TIMER_CTRL		0x1c
#else
#define TIMER_CTRL		0x10
#endif

#define TIMER_LOAD_COUNT0	0x00
#define TIMER_LOAD_COUNT1	0x04
#define TIMER_INTSTATUS		0x18

#define TIMER_EN		BIT(0)
#define TIMER_INT_EN		BIT(2)
#define TIMER_CLR_INT		BIT(0)

#if defined(CONFIG_ROCKCHIP_RK3128)
#define TIMER_BASE		(0x20044000 + 0x20)	/* TIMER 1 */
#define TIMER_IRQ		IRQ_TIMER1
#elif defined(CONFIG_ROCKCHIP_RK322X)
#define TIMER_BASE		(0x110C0000 + 0x20)	/* TIMER 1 */
#define TIMER_IRQ		IRQ_TIMER1
#elif defined(CONFIG_ROCKCHIP_RK3288)
#define TIMER_BASE		(0xFF6B0000 + 0x20)	/* TIMER 1 */
#define TIMER_IRQ		IRQ_TIMER1
#elif defined(CONFIG_ROCKCHIP_RK3328)
#define TIMER_BASE		(0xFF1C0000 + 0x20)	/* TIMER 1 */
#define TIMER_IRQ		IRQ_TIMER1
#elif defined(CONFIG_ROCKCHIP_RK3368)
/*
 * Use timer0 and never change, because timer0 will be used in charge animation
 * driver to support auto wakeup when system suspend. If core poweroff, PMU only
 * support timer0(not all timer) as wakeup source.
 */
#define TIMER_BASE		(0xFF810000 + 0x00)	/* TIMER 0 */
#define TIMER_IRQ		IRQ_TIMER0
#elif defined(CONFIG_ROCKCHIP_RK3399)
#define TIMER_BASE		(0xFF850000 + 0x20)	/* TIMER 1 */
#define TIMER_IRQ		IRQ_TIMER1
#elif defined(CONFIG_ROCKCHIP_RK3308)
#define TIMER_BASE		(0xFF1a0000 + 0x20)	/* TIMER 1 */
#define TIMER_IRQ		IRQ_TIMER1
#elif defined(CONFIG_ROCKCHIP_PX30)
/*
 * Use timer0 and never change, because timer0 will be used in charge animation
 * driver to support auto wakeup when system suspend. If core poweroff, PMU only
 * support timer0(not all timer) as wakeup source.
 */
#define TIMER_BASE		(0xFF210000 + 0x00)	/* TIMER 0 */
#define TIMER_IRQ		IRQ_TIMER0
#elif defined(CONFIG_ROCKCHIP_RK1808)
#define TIMER_BASE		(0xFF700000 + 0x20)	/* TIMER 1 */
#define TIMER_IRQ		IRQ_TIMER1
#elif defined(CONFIG_ROCKCHIP_RV1106)
#define TIMER_BASE		(0xFF660000 + 0x20)	/* TIMER 1 */
#define TIMER_IRQ		IRQ_TIMER1
#elif defined(CONFIG_ROCKCHIP_RV1126)
#define TIMER_BASE		(0xFF660000 + 0x20)	/* TIMER 1 */
#define TIMER_IRQ		IRQ_TIMER1
#elif defined(CONFIG_ROCKCHIP_RK3568)
/* Only timer0 can wakeup system suspend */
#define TIMER_BASE		(0xFE5F0000 + 0x00)	/* TIMER 1 */
#define TIMER_IRQ		IRQ_TIMER0
#elif defined(CONFIG_ROCKCHIP_RK3588)
/* Only timer0 can wakeup system suspend */
#define TIMER_BASE		(0xFEAE0000 + 0x00)	/* TIMER 0 */
#define TIMER_IRQ		IRQ_TIMER0
#else
"Missing definitions of timer module test"
#endif

#endif
