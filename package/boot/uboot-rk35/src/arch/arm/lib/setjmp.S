/*
 * (C) 2017 Theobroma Systems Design und Consulting GmbH
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <config.h>
#include <asm/assembler.h>
#include <linux/linkage.h>

.pushsection .text.setjmp, "ax"
ENTRY(setjmp)
	/*
	 * A subroutine must preserve the contents of the registers
	 * r4-r8, r10, r11 (v1-v5, v7 and v8) and SP (and r9 in PCS
	 * variants that designate r9 as v6).
	 */
	mov  ip, sp
	stm  a1, {v1-v8, ip, lr}
	mov  a1, #0
	bx   lr
ENDPROC(setjmp)
.popsection

.pushsection .text.longjmp, "ax"
ENTRY(longjmp)
	ldm  a1, {v1-v8, ip, lr}
	mov  sp, ip
	mov  a1, a2
	/* If we were passed a return value of zero, return one instead */
	cmp  a1, #0
	bne  1f
	mov  a1, #1
1:
	bx   lr
ENDPROC(longjmp)
.popsection
