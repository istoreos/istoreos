/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the main directory of this archive
 * for more details.
 *
 * Copyright (C) 2015 by Tom Ting <tom_ting@realtek.com>
 *
 */

#include <common.h>
#include <asm/io.h>

/*
 * Print CPU information
 */
int print_cpuinfo(void)
{
#ifdef CONFIG_TARGET_RTD1293
	printf("CPU  : Cortex-A53 Dual Core - AARCH64\n");
#else
	printf("CPU  : Cortex-A53 Quad Core - AARCH64\n");
#endif

	return 0;
}
