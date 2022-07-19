/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the main directory of this archive
 * for more details.
 *
 * Copyright (C) 2015 by Tom Ting <tom_ting@realtek.com>
 *
 * Time initialization.
 */

static inline void rtk_local_irq_enable(void)
{
	asm volatile(
		"msr	daifclr, #2		// arch_local_irq_enable"
		: : : "memory");
}

static inline void rtk_local_irq_disable(void)
{
	asm volatile(
		"msr	daifset, #2		// arch_local_irq_disable"
		: : : "memory");
}

extern void gic_test_init(void);
extern void cpu_sgi_test(unsigned sgi_number, unsigned cpu_mask);
extern unsigned gic_get_irq(void);
extern unsigned get_cpu_id(void);
