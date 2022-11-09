/*
 * (C) Copyright 2017 Rockchip Electronics Co., Ltd
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */

#include <common.h>
#include <debug_uart.h>
#include <dm.h>
#include <ns16550.h>
#include <ram.h>
#include <spl.h>
#include <version.h>
#include <asm/io.h>
#include <asm/arch-rockchip/bootrom.h>
#include <asm/arch-rockchip/uart.h>
#include <asm/arch-rockchip/sys_proto.h>

#ifndef CONFIG_TPL_LIBCOMMON_SUPPORT
#define CONFIG_SYS_NS16550_COM1 CONFIG_DEBUG_UART_BASE
void puts(const char *str)
{
	while (*str)
		putc(*str++);
}

void putc(char c)
{
	if (c == '\n')
		NS16550_putc((NS16550_t)(CONFIG_SYS_NS16550_COM1), '\r');

	NS16550_putc((NS16550_t)(CONFIG_SYS_NS16550_COM1), c);
}
#endif /* CONFIG_TPL_LIBCOMMON_SUPPORT */

#ifndef CONFIG_TPL_LIBGENERIC_SUPPORT
int __weak timer_init(void)
{
	return 0;
}

#ifdef CONFIG_ARM64
/* for ARM64,it don't have define timer_init and __udelay except lib/timer.c */
void __weak __udelay(unsigned long usec)
{
	u64 i, j, count;

	asm volatile ("MRS %0, CNTPCT_EL0" : "=r"(count));
	i = count;
	/* usec to count,24MHz */
	j = usec * 24;
	i += j;
	while (1) {
		asm volatile ("MRS %0, CNTPCT_EL0" : "=r"(count));
		if (count > i)
			break;
	}
}
#else
void __weak __udelay(unsigned long usec)
{
	u32 nowl, nowu;
	u64 cur_count, end_count;

	asm volatile("mrrc p15, 0, %0, %1, c14" : "=r" (nowl), "=r" (nowu));
	cur_count = (u64)nowu << 32 | nowl;
	/* usec to count,24MHz */
	end_count = usec * 24 + cur_count;
	while (1) {
		asm volatile("mrrc p15, 0, %0, %1, c14" : "=r" (nowl),
			     "=r" (nowu));
		cur_count = (u64)nowu << 32 | nowl;
		if (cur_count > end_count)
			break;
	}
}
#endif /* CONFIG_ARM64 */

void udelay(unsigned long usec)
{
	__udelay(usec);
}

void hang(void)
{
        bootstage_error(BOOTSTAGE_ID_NEED_RESET);
        for (;;)
                ;
}
#endif /* CONFIG_TPL_LIBGENERIC_SUPPORT */

u32 spl_boot_device(void)
{
	return BOOT_DEVICE_BOOTROM;
}

__weak void rockchip_stimer_init(void)
{
#ifndef CONFIG_ARM64
	asm volatile("mcr p15, 0, %0, c14, c0, 0"
		     : : "r"(COUNTER_FREQUENCY));
#elif CONFIG_IS_ENABLED(TINY_FRAMEWORK)
	/*
	 * For ARM64,generally initialize CNTFRQ in start.S,
	 * but if defined CONFIG_TPL_TINY_FRAMEWORK should skip start.S.
	 * So initialize CNTFRQ to 24MHz here.
	 */
	asm volatile("msr CNTFRQ_EL0, %0"
		     : : "r" (COUNTER_FREQUENCY));
#endif
	writel(0, CONFIG_ROCKCHIP_STIMER_BASE + 0x10);
	writel(0xffffffff, CONFIG_ROCKCHIP_STIMER_BASE);
	writel(0xffffffff, CONFIG_ROCKCHIP_STIMER_BASE + 4);
	writel(1, CONFIG_ROCKCHIP_STIMER_BASE + 0x10);
}

__weak int arch_cpu_init(void)
{
	return 0;
}

void board_init_f(ulong dummy)
{
#if defined(CONFIG_SPL_FRAMEWORK) && !CONFIG_IS_ENABLED(TINY_FRAMEWORK)
	struct udevice *dev;
	int ret;
#endif

	rockchip_stimer_init();
	arch_cpu_init();
#define EARLY_DEBUG
#ifdef EARLY_DEBUG
	/*
	 * Debug UART can be used from here if required:
	 *
	 * debug_uart_init();
	 * printch('a');
	 * printhex8(0x1234);
	 * printascii("string");
	 */
	debug_uart_init();
	printascii("\nU-Boot TPL " PLAIN_VERSION " (" U_BOOT_DATE " - " \
				U_BOOT_TIME ")\n");
#endif

#if defined(CONFIG_SPL_FRAMEWORK) && !CONFIG_IS_ENABLED(TINY_FRAMEWORK)
	ret = spl_early_init();
	if (ret) {
		debug("spl_early_init() failed: %d\n", ret);
		hang();
	}
#endif

	/* Init ARM arch timer */
	timer_init();

#if defined(CONFIG_SPL_FRAMEWORK) && !CONFIG_IS_ENABLED(TINY_FRAMEWORK)
	ret = uclass_get_device(UCLASS_RAM, 0, &dev);
	if (ret) {
		printf("DRAM init failed: %d\n", ret);
		return;
	}
#else
	sdram_init();
#endif

#if defined(CONFIG_TPL_ROCKCHIP_BACK_TO_BROM) && !defined(CONFIG_TPL_BOARD_INIT)
	back_to_bootrom(BROM_BOOT_NEXTSTAGE);
#endif
}

#if !(defined(CONFIG_SPL_FRAMEWORK) && !CONFIG_IS_ENABLED(TINY_FRAMEWORK))
/* Place Holders */
void board_init_r(gd_t *id, ulong dest_addr)
{
	/*
	 * Function attribute is no-return
	 * This Function never executes
	 */
	while (1)
		;
}
#endif
