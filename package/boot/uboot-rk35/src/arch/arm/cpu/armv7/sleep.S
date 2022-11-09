/*
 * (C) Copyright 2017 Rockchip Electronics Co., Ltd.
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <asm/arm32_macros.S>
#include <asm/macro.h>
#include <asm-offsets.h>
#include <asm/psci.h>
#include <config.h>
#include <linux/linkage.h>

	.globl cpu_suspend
	.globl cpu_do_suspend
	.globl cpu_suspend_save
	.globl cpu_resume
	.globl cpu_do_resume

/*
 * int cpu_suspend(unsigned long arg, int (*fn)(unsigned long))
 * @arg will be passed to fn as argument
 * return value: 0 - cpu resumed from suspended state.
 *		 -1 - cpu not suspended.
 */
ENTRY(cpu_suspend)
	push	{r4 - r12, lr}

	mov	r5, sp
	sub	sp, sp, #PM_CTX_SIZE
	push	{r0, r1}

	/* r9 is gd, save it to __suspend_gd !!! */
	adr	r4, __suspend_gd
	str	r9, [r4]

	mov	r1, r5
	add	r0, sp, #8
	blx	cpu_suspend_save

	adr	lr, aborted
	/* Jump to arch specific suspend */
	pop	{r0, pc}

aborted:
	/* cpu not suspended */
	add	sp, sp, #PM_CTX_SIZE
	/* Return -1 to the caller */
	mov	r0, #(-1)

suspend_return:
	pop	{r4 - r12, pc}
ENDPROC(cpu_suspend)

ENTRY(cpu_do_suspend)
	push	{r4 - r11}

	read_midr r4
	ubfx	r5, r4, #4, #12

	ldr     r4, CORTEX_A7_PART_NUM
	cmp	r5, r4
	beq	a7_suspend

	ldr     r4, CORTEX_A9_PART_NUM
	cmp	r5, r4
	beq	a9_suspend

	b	other_suspend

	/* A9 needs PCR/DIAG */
a9_suspend:
	read_pcr r4
	read_diag r5
	stmia	r0!, {r4 - r5}

a7_suspend:
	read_fcseidr r4
	read_tpidruro r5
	stmia	r0!, {r4 - r5}

other_suspend:
	read_dacr  r4
	read_ttbr0 r5
	read_ttbr1 r6
	read_ttbcr r7
	read_sctlr r8
	read_actlr r9
	read_cpacr r10
	stmia	r0!, {r4 - r10}

	read_prrr r4
	read_nmrr r5
	read_vbar r6
	mrs r7, CPSR
	stmia	r0, {r4 - r7}

	pop	{r4 - r11}
	bx	lr
ENDPROC(cpu_do_suspend)

ENTRY(cpu_resume)
	/* Disable interrupt */
	cpsid	aif

	/* Load gd !! */
	adr r1, __suspend_gd
	ldr r2, [r1]

	/* Get pm_ctx */
	add r2, r2, #PM_CTX_PHYS
	ldr r0, [r2]

	/* Need to use r0!, because cpu_do_resume needs it */
	ldmia	r0!, {sp, pc}
ENDPROC(cpu_resume)

/*
 * void sm_do_cpu_do_resume(paddr suspend_regs) __noreturn;
 * Restore the registers stored when cpu_do_suspend
 * r0 points to the physical base address of the suspend_regs
 * field of struct pm_ctx.
 */
ENTRY(cpu_do_resume)
	read_midr r4
	ubfx	r5, r4, #4, #12

	ldr	r4, CORTEX_A9_PART_NUM
	cmp	r5, r4
	beq	a9_resume

	ldr     r4, CORTEX_A7_PART_NUM
	cmp	r5, r4
	beq	a7_resume

	/* v7 resume */
	mov	ip, #0
	/* Invalidate icache to PoU */
	write_iciallu
	/* set reserved context */
	write_contextidr ip
	b	other_resume

a9_resume:
	/*
	 * A9 needs PCR/DIAG
	 */
	ldmia   r0!, {r4 - r5}
	write_pcr r4
	write_diag r5

a7_resume:
	/* v7 resume */
	mov	ip, #0

	/* Invalidate icache to PoU */
	write_iciallu
	/* set reserved context */
	write_contextidr ip

	ldmia	r0!, {r4 - r5}
	write_fcseidr r4
	write_tpidruro r5

other_resume:
	ldmia	r0!, {r4 - r10}
	/* Invalidate entire TLB */
	write_tlbiall
	write_dacr r4
	write_ttbr0 r5
	write_ttbr1 r6
	write_ttbcr r7

	ldmia	r0, {r4 - r7}
	write_prrr  r4
	write_nmrr  r5
	write_vbar  r6

	write_actlr r9
	write_cpacr r10
	write_bpiall
	isb
	dsb

	/* MMU will be enabled here */
	write_sctlr r8
	isb

	/* Restore interrupt */
	msr CPSR_c, r7

	mov	r0, #0
	b	suspend_return
ENDPROC(cpu_do_resume)

.align 4
__suspend_gd:
	.word	0x0
CORTEX_A7_PART_NUM:
	.word	0xC07
CORTEX_A9_PART_NUM:
	.word	0xC09
