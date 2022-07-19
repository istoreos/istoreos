/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the main directory of this archive
 * for more details.
 *
 * Copyright (C) 2015 by Tom Ting <tom_ting@realtek.com>
 *
 * Time initialization.
 */

#include <common.h>
#include <command.h>
#include <asm/arch/interrupt.h>
#include <asm/io.h>

#define BIT(x) (1 << (x))
#define rtd_setbits(offset, Mask)       __raw_writel(((__raw_readl(offset) | Mask)), offset)
#define rtd_clearbits(offset, Mask)     __raw_writel(((__raw_readl(offset) & ~Mask)), offset)
#define rtd_outl(offset, val)           __raw_writel(val, offset)

int already_init = 0;

static int do_gictest(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	unsigned irqnr=0, mask=0;

	gic_test_init();
	rtk_local_irq_enable();

	switch (argc) {
		case 1:
			cpu_sgi_test(irqnr, mask);
			break;
		case 2:
			irqnr = simple_strtoul(argv[1], NULL, 10);
			if (irqnr < 16) {
				cpu_sgi_test(irqnr, mask);
			} else if (irqnr == 73) {	// uart test
				rtd_clearbits(0x98007040, BIT(2));
				rtd_outl(0x98007000, BIT(2));

				rtd_clearbits(0x98007000, BIT(2)); // ENABLE MUX UART
				rtd_setbits(0x98007040, BIT(2));
				rtd_outl(0x98007804, 0x5);
			}
			break;
		default:
			printf("Not support yet\n");
			return 1;
			break;
	}
	return 0;
}

U_BOOT_CMD(
	gictest, 3, 1, do_gictest,
	"Turn on GIC and send SGI to CPU",
	"SGI# [CPUMASK]"
);
