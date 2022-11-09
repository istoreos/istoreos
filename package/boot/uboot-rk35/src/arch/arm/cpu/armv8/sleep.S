/*
 * (C) Copyright 2017 Rockchip Electronics Co., Ltd.
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

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
	/*
	 * Save x8~x30(lr is x30, sp is x29), total (23 + 1 reserved)*8=192
	 */
	stp	x29, lr, [sp, #-192]!
	/* Reserve 8-byte after x8, just for offset with 16-byte aligned */
	str	x8, [sp, #16]
	stp	x9, x10, [sp, #32]
	stp	x11, x12, [sp, #48]
	stp	x13, x14, [sp, #64]
	stp	x15, x16, [sp, #80]
	stp	x17, x18, [sp, #96]
	stp	x19, x20, [sp,#112]
	stp	x21, x22, [sp,#128]
	stp	x23, x24, [sp,#144]
	stp	x25, x26, [sp,#160]
	stp	x27, x28, [sp,#176]

	mov	x19, sp
	mov	x20, x0
	mov	x21, x1

	/* Save arch specific suspend fn and arg to stack */
	sub	sp, sp, #PM_CTX_SIZE
	stp	x0, x1, [sp, #-16]!

	/* x18 is gd, save it to _suspend_gd !! */
	adr	x0, _suspend_gd
	str	x18, [x0]

	/* x0: pm_ctx;	x1: sp where restore x8~x30 from */
	add	x0, sp, #16
	mov	x1, x19
	bl	cpu_suspend_save

	adr	lr, aborted
	/* Jump to arch specific suspend */
	mov	x0, x20
	br	x21

	/* Should never reach here, otherwise failed */
aborted:
	/* cpu not suspended */
	add	sp, sp, #(16 + PM_CTX_SIZE)
	/* Return -1 to the caller */
	mov	x0, #(-1)

suspend_return:
	ldr	x8, [sp, #16]
	ldp	x9, x10, [sp, #32]
	ldp	x11, x12, [sp, #48]
	ldp	x13, x14, [sp, #64]
	ldp	x15, x16, [sp, #80]
	ldp	x17, x18, [sp, #96]
	ldp	x19, x20, [sp,#112]
	ldp	x21, x22, [sp,#128]
	ldp	x23, x24, [sp,#144]
	ldp	x25, x26, [sp,#160]
	ldp	x27, x28, [sp,#176]
	ldp	x29, lr, [sp], #192
	ret
ENDPROC(cpu_suspend)

ENTRY(cpu_do_suspend)
	/*
	 * Save temporary x2~x12, total: 11*8=88, maybe you need not so many
	 * registers now, but I save them for future extendion.
	 */
	stp	x2,  x3, [sp, #-88]!
	stp	x4,  x5, [sp, #16]
	stp	x6,  x7, [sp, #32]
	stp	x8,  x9, [sp, #48]
	stp	x10, x11, [sp,#64]
	str	x12, [sp, #80]

	/*
	 * Save core registers.
	 *
	 * Note: If you want to add/sub the register here,
	 *	 remember update suspend_regs[] of struct pm_ctx.
	 */
	mrs	x2, vbar_el2
	mrs	x3, cptr_el2
	mrs	x4, ttbr0_el2
	mrs	x5, tcr_el2
	mrs	x6, mair_el2
	mrs	x7, cntvoff_el2
	mrs	x8, sctlr_el2
	mrs	x9, hcr_el2
	mrs	x10, daif

	stp	x2,  x3, [x0, #0]
	stp	x4,  x5, [x0, #16]
	stp	x6,  x7, [x0, #32]
	stp	x8,  x9, [x0, #48]
	str	x10, [x0, #64]

	/* Restore temporary x2~x12 */
	ldp	x4,  x5, [sp, #16]
	ldp	x6,  x7, [sp, #32]
	ldp	x8,  x9, [sp, #48]
	ldp	x10, x11, [sp,#64]
	ldr	x12, [sp, #80]
	ldp	x2,  x3, [sp], #88
	ret
ENDPROC(cpu_do_suspend)

ENTRY(cpu_resume)
	/* Disable interrupt */
	msr       daifset, #0x03

	/* Load gd !! */
	adr x1, _suspend_gd
	ldr x2, [x1]

	/* Get pm_ctx */
	add x2, x2, #PM_CTX_PHYS
	ldr x0, [x2]

	/* Need x0=x0-16, because cpu_do_resume needs it */
	ldp	x1, lr, [x0], #16
	mov	sp, x1
	ret
ENDPROC(cpu_resume)

/*
 * void sm_do_cpu_do_resume(paddr suspend_regs) __noreturn;
 * Restore the registers stored when cpu_do_suspend
 * x0 points to the physical base address of the suspend_regs
 * field of struct pm_ctx.
 */
ENTRY(cpu_do_resume)
	/*
	 * Invalidate local tlb entries before turning on MMU !!!
	 */
	tlbi	alle2
	dsb	sy
	isb

	ldp	x2, x3, [x0]
	ldp	x4, x5, [x0, #16]
	ldp	x6, x7, [x0, #32]
	ldp	x8, x9, [x0, #48]
	ldp	x10, x11, [x0, #64]
	ldr	x12, [x0, #80]

	/* Restore core register */
	msr	vbar_el2, x2
	msr	cptr_el2, x3
	msr	ttbr0_el2, x4
	msr	tcr_el2, x5
	msr	mair_el2, x6
	msr	cntvoff_el2, x7
	msr	hcr_el2, x9

	/* Enable MMU here */
	msr	sctlr_el2, x8
	dsb	sy
	isb

	/* resume interrupt */
	msr	daif, x10

	mov	x0, #0
	b	suspend_return
ENDPROC(cpu_do_resume)

.align 3
_suspend_gd:
	.long	0x0

