/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the main directory of this archive
 * for more details.
 *
 * Copyright (C) 2015 by Tom Ting <tom_ting@realtek.com>
 *
 * interrupt test
 */

#include <asm-offsets.h>
#include <config.h>
#include <linux/linkage.h>
#include <asm/gic.h>
#include <asm/macro.h>

ENTRY(gic_test_init)
#if defined(CONFIG_GICV2)
	stp	x4, x5, [sp,#-32]!
	stp	x9, x10, [sp,#16]

	/**** Config SGIs and PPIs as Grp1 ****/
	ldr	x4, =GICD_BASE
	mov	w9, #~0
	str	w9, [x4, GICD_IGROUPRn]

	/**** Enable All SPI interrupts ****/
	ldr	w9, [x4, GICD_TYPER]
	and	w10, w9, #0x1f          /* ITLinesNumber */
	cbz	w10, 1f                 /* No SPIs */
	mov	w9, #~0
	add	x5, x4, (GICD_ISENABLERn + 4) /* start from #32-bit, SPI */
0:	
	str	w9, [x5], #0x4
	sub	w10, w10, #0x1
	cbnz	w10, 0b
1:
	/**** Enable All SGI & PPI interrupts ****/
	str	w9, [x4, GICD_ISENABLERn]

	/**** Target All SPI to CPU0 ****/
	ldr	w9, [x4, GICD_TYPER]
	and	w10, w9, #0x1f          /* ITLinesNumber */
	cbz	w10, 4f                 /* No SPIs */
	lsl	w10, w10, #5		/* Calculate total SPI, each contains 32 line */
	mov	w9, #0x0101
	movk	w9, #0x0101, lsl #16
	add	x5, x4, (GICD_ITARGETSRn + 0x20)	/* Starts from SGI + PPI */
3:
	str	w9, [x5], #0x4
	sub	w10, w10, #0x4
	and	x2, x5, 0xfff	/* Only set until UART, temp WA since IRQ 98 keeps trigger */
	cmp	x2, 0x84c
	beq	4f
	cbnz	w10, 3b
4:

	/**** Set All Priority to 0xA0 ****/
	ldr	w9, [x4, GICD_TYPER]
	and	w10, w9, #0x1f          /* ITLinesNumber */
	cbz	w10, 6f                 /* No SPIs */
	lsl	w10, w10, #5		/* Calculate total SPI, each contains 32 line */
	mov	w9, #0xa0a0
	movk	w9, #0xa0a0, lsl #16
	add	x5, x4, (GICD_IPRIORITYRn)	/* Starts from SGI */
5:
	str	w9, [x5], #0x4
	sub	w10, w10, #0x4
	cbnz	w10, 5b
6:

	/**** Initialize Cpu Interface ****/
	ldr	x4, =GICC_BASE
	mov	w9, #0x1e7
	str	w9, [x4, GICC_CTLR]
	mov	w9, #0xf8
	str	w9, [x4, GICC_PMR]

	ldp	x9, x10, [sp,#16]
	ldp	x4, x5, [sp],#32
#endif /* CONFIG_GICV2 */
	ret
ENDPROC(gic_test_init)

ENTRY(gic_get_irq)
#if defined(CONFIG_GICV2)
	ldr	x1, =GICC_BASE
	ldr	w0, [x1, GICC_IAR]
	str	w0, [x1, GICC_EOIR]
	and	w0, w0, #0x3ff
#else
	mov	w0, #-1
#endif
	ret
ENDPROC(gic_get_irq)

ENTRY(get_cpu_id)
	mrs	x0, mpidr_el1
	and	x0, x0, #0xff
ENDPROC(get_cpu_id)

ENTRY(cpu_sgi_test)
#if defined(CONFIG_GICV2)
	stp	x4, x5, [sp,#-16]!
	ldr	x4, =GICD_BASE
	and	w5, w0, #0xf
	orr	w5, w5, #0x8000
	movk	w5, #0x200, lsl #16
	str	w5, [x4, GICD_SGIR]
	ldp	x4, x5, [sp],#16
#endif
	ret
ENDPROC(cpu_sgi_test)
