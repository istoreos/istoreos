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
#include <asm/arch/rbus/iso_reg.h>

void reset_cpu(ulong ignored)
{
	//trigger watchdog reset
	__raw_writel((unsigned long)ISO_TCWCR_reg,0xa5);
	__raw_writel((unsigned long)ISO_TCWTR_reg,0x1);
	__raw_writel((unsigned long)ISO_TCWOV_reg,1);
	__raw_writel((unsigned long)ISO_TCWCR_reg,0);
}
