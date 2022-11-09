/*
 * (C) Copyright 2018 Rockchip Electronics Co., Ltd
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */

#include <asm/io.h>
#include <common.h>
#include <irq-generic.h>
#include <rk_timer_irq.h>

/*
 * Currently, we support a timer timeout to generate a IRQ to dump cpu context.
 */
#define ROCKCHIP_DEBUGGER_TIMEOUT	5	/* seconds */

static void rockchip_debugger_isr(int irq, void *data)
{
	writel(TIMER_CLR_INT, TIMER_BASE + TIMER_INTSTATUS);
}

int rockchip_debugger_init(void)
{
	uint32_t load_count0, load_count1;
	uint64_t delay_c = ROCKCHIP_DEBUGGER_TIMEOUT * COUNTER_FREQUENCY;

	if (!delay_c)
		return 0;

	printf("Enable rockchip debugger\n");

	/* Disable first */
	writel(0, TIMER_BASE + TIMER_CTRL);

	/* Config */
	load_count0 = (uint32_t)(delay_c);
	load_count1 = (uint32_t)(delay_c >> 32);
	writel(load_count0, TIMER_BASE + TIMER_LOAD_COUNT0);
	writel(load_count1, TIMER_BASE + TIMER_LOAD_COUNT1);
	writel(TIMER_CLR_INT, TIMER_BASE + TIMER_INTSTATUS);
	writel(TIMER_EN | TIMER_INT_EN, TIMER_BASE + TIMER_CTRL);

	/* Request irq */
	irq_install_handler(TIMER_IRQ, rockchip_debugger_isr, NULL);
	irq_handler_enable(TIMER_IRQ);

	return 0;
}
