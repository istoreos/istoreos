/*
 * Copyright (C) 2017 Rockchip Electronic Co.,Ltd
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <linux/linkage.h>
#include <asm/assembler.h>

ENTRY(spl_optee_entry)
	mov lr, r1
	mov pc, r3
ENDPROC(spl_optee_entry)
