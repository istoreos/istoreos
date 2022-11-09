/*
 * Copyright (c) 2016-2018, Fuzhou Rockchip Electronics Co., Ltd
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * date: 2021-03-18
 */
	.arch armv7-a
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 2
	.eabi_attribute 30, 4
	.eabi_attribute 34, 0
	.eabi_attribute 18, 2
	.file	"rk_ftl_arm_v7.S"
	.section	.text.flash_read_ecc,"ax",%progbits
	.align	1
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	flash_read_ecc, %function
flash_read_ecc:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	ldr	r3, .L2
	push	{r4, lr}
	ldr	r4, [r3, r0, lsl #3]
	add	r3, r3, r0, lsl #3
	movs	r0, #80
	ldrb	r3, [r3, #4]	@ zero_extendqisi2
	add	r4, r4, r3, lsl #8
	movs	r3, #122
	str	r3, [r4, #2056]
	bl	udelay
	ldr	r3, [r4, #2048]
	ldr	r0, [r4, #2048]
	and	r3, r3, #15
	and	r0, r0, #15
	cmp	r0, r3
	it	cc
	movcc	r0, r3
	ldr	r3, [r4, #2048]
	and	r3, r3, #15
	cmp	r3, r0
	it	cc
	movcc	r3, r0
	ldr	r0, [r4, #2048]
	and	r0, r0, #15
	cmp	r0, r3
	it	cc
	movcc	r0, r3
	pop	{r4, pc}
.L3:
	.align	2
.L2:
	.word	.LANCHOR0
	.size	flash_read_ecc, .-flash_read_ecc
	.section	.text.ftl_set_blk_mode.part.11,"ax",%progbits
	.align	1
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	ftl_set_blk_mode.part.11, %function
ftl_set_blk_mode.part.11:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	ldr	r3, .L5
	lsrs	r1, r0, #5
	and	r0, r0, #31
	ldr	r2, [r3]
	movs	r3, #1
	lsl	r0, r3, r0
	ldr	r3, [r2, r1, lsl #2]
	orrs	r3, r3, r0
	str	r3, [r2, r1, lsl #2]
	bx	lr
.L6:
	.align	2
.L5:
	.word	.LANCHOR1
	.size	ftl_set_blk_mode.part.11, .-ftl_set_blk_mode.part.11
	.section	.text.FlashMemCmp8,"ax",%progbits
	.align	1
	.global	FlashMemCmp8
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	FlashMemCmp8, %function
FlashMemCmp8:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	ldr	r3, .L15
	push	{r4, r5, lr}
	ldrb	r3, [r3]	@ zero_extendqisi2
	cbz	r3, .L10
	ldrb	r4, [r0, #1]	@ zero_extendqisi2
	ldrb	r3, [r1, #1]	@ zero_extendqisi2
	cmp	r4, r3
	beq	.L14
	movs	r3, #0
.L10:
	cmp	r3, r2
	bne	.L12
.L14:
	movs	r0, #0
	pop	{r4, r5, pc}
.L12:
	ldrb	r5, [r0, r3]	@ zero_extendqisi2
	ldrb	r4, [r1, r3]	@ zero_extendqisi2
	adds	r3, r3, #1
	cmp	r5, r4
	beq	.L10
	mov	r0, r3
	pop	{r4, r5, pc}
.L16:
	.align	2
.L15:
	.word	.LANCHOR2
	.size	FlashMemCmp8, .-FlashMemCmp8
	.section	.text.FlashRsvdBlkChk,"ax",%progbits
	.align	1
	.global	FlashRsvdBlkChk
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	FlashRsvdBlkChk, %function
FlashRsvdBlkChk:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	ldr	r3, .L20
	ldrb	r2, [r3]	@ zero_extendqisi2
	ldr	r3, .L20+4
	ldr	r3, [r3]
	muls	r3, r2, r3
	cmp	r3, r1
	bls	.L19
	adds	r0, r0, #0
	it	ne
	movne	r0, #1
	bx	lr
.L19:
	movs	r0, #1
	bx	lr
.L21:
	.align	2
.L20:
	.word	.LANCHOR3
	.word	.LANCHOR4
	.size	FlashRsvdBlkChk, .-FlashRsvdBlkChk
	.section	.text.FlashGetRandomizer,"ax",%progbits
	.align	1
	.global	FlashGetRandomizer
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	FlashGetRandomizer, %function
FlashGetRandomizer:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	ldr	r3, .L30
	and	r2, r1, #127
	push	{r4, lr}
	ldrh	r4, [r3, r2, lsl #1]
	ldr	r3, .L30+4
	ldrb	r3, [r3]	@ zero_extendqisi2
	cbz	r3, .L22
	bl	FlashRsvdBlkChk
	cbz	r0, .L22
	orr	r4, r4, #-1073741824
.L22:
	mov	r0, r4
	pop	{r4, pc}
.L31:
	.align	2
.L30:
	.word	.LANCHOR5
	.word	.LANCHOR6
	.size	FlashGetRandomizer, .-FlashGetRandomizer
	.section	.text.FlashSetRandomizer,"ax",%progbits
	.align	1
	.global	FlashSetRandomizer
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	FlashSetRandomizer, %function
FlashSetRandomizer:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r3, r4, r5, lr}
	and	r2, r1, #127
	ldr	r3, .L40
	mov	r5, r0
	ldrh	r4, [r3, r2, lsl #1]
	ldr	r3, .L40+4
	ldrb	r3, [r3]	@ zero_extendqisi2
	cbz	r3, .L33
	bl	FlashRsvdBlkChk
	cbz	r0, .L33
	orr	r4, r4, #-1073741824
.L33:
	ldr	r3, .L40+8
	ldr	r3, [r3, r5, lsl #3]
	str	r4, [r3, #336]
	pop	{r3, r4, r5, pc}
.L41:
	.align	2
.L40:
	.word	.LANCHOR5
	.word	.LANCHOR6
	.word	.LANCHOR0
	.size	FlashSetRandomizer, .-FlashSetRandomizer
	.section	.text.FlashBlockAlignInit,"ax",%progbits
	.align	1
	.global	FlashBlockAlignInit
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	FlashBlockAlignInit, %function
FlashBlockAlignInit:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	cmp	r0, #512
	ldr	r3, .L48
	bls	.L43
	mov	r2, #1024
.L47:
	str	r2, [r3]
	bx	lr
.L43:
	cmp	r0, #256
	bls	.L45
	mov	r2, #512
	b	.L47
.L45:
	cmp	r0, #128
	bhi	.L46
	str	r0, [r3]
	bx	lr
.L46:
	mov	r2, #256
	b	.L47
.L49:
	.align	2
.L48:
	.word	.LANCHOR4
	.size	FlashBlockAlignInit, .-FlashBlockAlignInit
	.section	.text.FlashReadCmd,"ax",%progbits
	.align	1
	.global	FlashReadCmd
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	FlashReadCmd, %function
FlashReadCmd:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	ldr	r2, .L52
	push	{r4, r5}
	ldr	r4, .L52+4
	ldr	r3, [r2, r0, lsl #3]
	add	r2, r2, r0, lsl #3
	ldr	r4, [r4]
	ldrb	r2, [r2, #4]	@ zero_extendqisi2
	ldrb	r4, [r4, #7]	@ zero_extendqisi2
	lsls	r2, r2, #8
	cmp	r4, #1
	itt	eq
	addeq	r4, r3, r2
	moveq	r5, #38
	add	r3, r3, r2
	mov	r2, #0
	it	eq
	streq	r5, [r4, #2056]
	str	r2, [r3, #2056]
	str	r2, [r3, #2052]
	str	r2, [r3, #2052]
	uxtb	r2, r1
	str	r2, [r3, #2052]
	lsrs	r2, r1, #8
	str	r2, [r3, #2052]
	lsrs	r2, r1, #16
	str	r2, [r3, #2052]
	movs	r2, #48
	str	r2, [r3, #2056]
	pop	{r4, r5}
	b	FlashSetRandomizer
.L53:
	.align	2
.L52:
	.word	.LANCHOR0
	.word	.LANCHOR7
	.size	FlashReadCmd, .-FlashReadCmd
	.section	.text.FlashReadDpDataOutCmd,"ax",%progbits
	.align	1
	.global	FlashReadDpDataOutCmd
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	FlashReadDpDataOutCmd, %function
FlashReadDpDataOutCmd:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	ldr	r2, .L58
	push	{r4, r5, r6}
	uxtb	r6, r1
	ldr	r4, .L58+4
	lsrs	r5, r1, #8
	ldr	r3, [r2, r0, lsl #3]
	add	r2, r2, r0, lsl #3
	ldrb	r4, [r4, #16]	@ zero_extendqisi2
	ldrb	r2, [r2, #4]	@ zero_extendqisi2
	cmp	r4, #1
	lsr	r4, r1, #16
	lsl	r2, r2, #8
	add	r3, r3, r2
	bne	.L55
	movs	r2, #6
	str	r2, [r3, #2056]
	movs	r2, #0
	str	r2, [r3, #2052]
	str	r2, [r3, #2052]
	str	r6, [r3, #2052]
	str	r5, [r3, #2052]
	str	r4, [r3, #2052]
.L57:
	movs	r2, #224
	str	r2, [r3, #2056]
	pop	{r4, r5, r6}
	b	FlashSetRandomizer
.L55:
	movs	r2, #0
	str	r2, [r3, #2056]
	str	r2, [r3, #2052]
	str	r2, [r3, #2052]
	str	r6, [r3, #2052]
	str	r5, [r3, #2052]
	str	r4, [r3, #2052]
	movs	r4, #5
	str	r4, [r3, #2056]
	str	r2, [r3, #2052]
	str	r2, [r3, #2052]
	b	.L57
.L59:
	.align	2
.L58:
	.word	.LANCHOR0
	.word	.LANCHOR8
	.size	FlashReadDpDataOutCmd, .-FlashReadDpDataOutCmd
	.section	.text.FlashProgFirstCmd,"ax",%progbits
	.align	1
	.global	FlashProgFirstCmd
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	FlashProgFirstCmd, %function
FlashProgFirstCmd:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	push	{r4, r5}
	lsrs	r2, r1, #16
	ldr	r4, .L61
	ldr	r3, [r4, r0, lsl #3]
	add	r4, r4, r0, lsl #3
	ldrb	r4, [r4, #4]	@ zero_extendqisi2
	add	r3, r3, r4, lsl #8
	movs	r4, #128
	str	r4, [r3, #2056]
	movs	r4, #0
	str	r4, [r3, #2052]
	str	r4, [r3, #2052]
	uxtb	r4, r1
	str	r4, [r3, #2052]
	lsrs	r4, r1, #8
	str	r4, [r3, #2052]
	str	r2, [r3, #2052]
	pop	{r4, r5}
	b	FlashSetRandomizer
.L62:
	.align	2
.L61:
	.word	.LANCHOR0
	.size	FlashProgFirstCmd, .-FlashProgFirstCmd
	.section	.text.FlashEraseCmd,"ax",%progbits
	.align	1
	.global	FlashEraseCmd
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	FlashEraseCmd, %function
FlashEraseCmd:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, lr}
	ldr	r4, .L68
	ldr	r3, [r4, r0, lsl #3]
	add	r4, r4, r0, lsl #3
	ldrb	r0, [r4, #4]	@ zero_extendqisi2
	lsls	r0, r0, #8
	cbz	r2, .L64
	adds	r2, r3, r0
	movs	r4, #96
	str	r4, [r2, #2056]
	uxtb	r4, r1
	str	r4, [r2, #2052]
	lsrs	r4, r1, #8
	str	r4, [r2, #2052]
	lsrs	r4, r1, #16
	str	r4, [r2, #2052]
	ldr	r2, .L68+4
	ldr	r2, [r2]
	add	r1, r1, r2
.L64:
	add	r3, r3, r0
	movs	r2, #96
	str	r2, [r3, #2056]
	uxtb	r2, r1
	str	r2, [r3, #2052]
	lsrs	r2, r1, #8
	lsrs	r1, r1, #16
	str	r2, [r3, #2052]
	movs	r2, #208
	str	r1, [r3, #2052]
	str	r2, [r3, #2056]
	pop	{r4, pc}
.L69:
	.align	2
.L68:
	.word	.LANCHOR0
	.word	.LANCHOR4
	.size	FlashEraseCmd, .-FlashEraseCmd
	.section	.text.FlashProgDpSecondCmd,"ax",%progbits
	.align	1
	.global	FlashProgDpSecondCmd
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	FlashProgDpSecondCmd, %function
FlashProgDpSecondCmd:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	push	{r4, r5}
	lsrs	r2, r1, #16
	ldr	r4, .L71
	ldr	r3, [r4, r0, lsl #3]
	add	r4, r4, r0, lsl #3
	ldrb	r5, [r4, #4]	@ zero_extendqisi2
	ldr	r4, .L71+4
	ldrb	r4, [r4, #11]	@ zero_extendqisi2
	add	r3, r3, r5, lsl #8
	str	r4, [r3, #2056]
	movs	r4, #0
	str	r4, [r3, #2052]
	str	r4, [r3, #2052]
	uxtb	r4, r1
	str	r4, [r3, #2052]
	lsrs	r4, r1, #8
	str	r4, [r3, #2052]
	str	r2, [r3, #2052]
	pop	{r4, r5}
	b	FlashSetRandomizer
.L72:
	.align	2
.L71:
	.word	.LANCHOR0
	.word	.LANCHOR8
	.size	FlashProgDpSecondCmd, .-FlashProgDpSecondCmd
	.section	.text.FlashProgSecondCmd,"ax",%progbits
	.align	1
	.global	FlashProgSecondCmd
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	FlashProgSecondCmd, %function
FlashProgSecondCmd:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	ldr	r3, .L74
	ldr	r2, [r3, r0, lsl #3]
	add	r3, r3, r0, lsl #3
	ldrb	r3, [r3, #4]	@ zero_extendqisi2
	add	r3, r2, r3, lsl #8
	movs	r2, #16
	str	r2, [r3, #2056]
	bx	lr
.L75:
	.align	2
.L74:
	.word	.LANCHOR0
	.size	FlashProgSecondCmd, .-FlashProgSecondCmd
	.section	.text.FlashProgDpFirstCmd,"ax",%progbits
	.align	1
	.global	FlashProgDpFirstCmd
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	FlashProgDpFirstCmd, %function
FlashProgDpFirstCmd:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	ldr	r3, .L77
	ldr	r1, .L77+4
	ldr	r2, [r3, r0, lsl #3]
	add	r3, r3, r0, lsl #3
	ldrb	r1, [r1, #10]	@ zero_extendqisi2
	ldrb	r3, [r3, #4]	@ zero_extendqisi2
	add	r3, r2, r3, lsl #8
	str	r1, [r3, #2056]
	bx	lr
.L78:
	.align	2
.L77:
	.word	.LANCHOR0
	.word	.LANCHOR8
	.size	FlashProgDpFirstCmd, .-FlashProgDpFirstCmd
	.section	.text.FlashReadStatus,"ax",%progbits
	.align	1
	.global	FlashReadStatus
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	FlashReadStatus, %function
FlashReadStatus:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r3, r4, r5, lr}
	movs	r2, #112
	ldr	r3, .L80
	ldr	r5, [r3, r0, lsl #3]
	add	r3, r3, r0, lsl #3
	movs	r0, #80
	ldrb	r4, [r3, #4]	@ zero_extendqisi2
	add	r3, r5, r4, lsl #8
	adds	r4, r4, #8
	lsls	r4, r4, #8
	str	r2, [r3, #2056]
	bl	udelay
	ldr	r0, [r5, r4]
	pop	{r3, r4, r5, pc}
.L81:
	.align	2
.L80:
	.word	.LANCHOR0
	.size	FlashReadStatus, .-FlashReadStatus
	.section	.text.js_hash,"ax",%progbits
	.align	1
	.global	js_hash
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	js_hash, %function
js_hash:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	ldr	r3, .L85
	add	r1, r1, r0
	push	{r4, lr}
.L83:
	cmp	r0, r1
	bne	.L84
	mov	r0, r3
	pop	{r4, pc}
.L84:
	lsrs	r2, r3, #2
	ldrb	r4, [r0], #1	@ zero_extendqisi2
	add	r2, r2, r3, lsl #5
	add	r2, r2, r4
	eors	r3, r3, r2
	b	.L83
.L86:
	.align	2
.L85:
	.word	1204201446
	.size	js_hash, .-js_hash
	.section	.text.FlashLoadIdbInfo,"ax",%progbits
	.align	1
	.global	FlashLoadIdbInfo
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	FlashLoadIdbInfo, %function
FlashLoadIdbInfo:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	movs	r0, #0
	bx	lr
	.size	FlashLoadIdbInfo, .-FlashLoadIdbInfo
	.section	.text.FlashPrintInfo,"ax",%progbits
	.align	1
	.global	FlashPrintInfo
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	FlashPrintInfo, %function
FlashPrintInfo:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	bx	lr
	.size	FlashPrintInfo, .-FlashPrintInfo
	.section	.text.ToshibaSetRRPara,"ax",%progbits
	.align	1
	.global	ToshibaSetRRPara
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	ToshibaSetRRPara, %function
ToshibaSetRRPara:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r3, r4, r5, r6, r7, r8, r10, lr}
	add	r7, r1, r1, lsl #2
	ldr	r10, .L97+12
	mov	r5, r0
	mov	r6, r1
	movs	r4, #0
	ldr	r8, .L97+16
.L90:
	ldrb	r3, [r10]	@ zero_extendqisi2
	cmp	r4, r3
	bcc	.L94
	pop	{r3, r4, r5, r6, r7, r8, r10, pc}
.L94:
	movs	r3, #85
	movs	r0, #200
	str	r3, [r5, #8]
	ldrsb	r3, [r4, r8]
	str	r3, [r5, #4]
	bl	udelay
	ldr	r3, .L97
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, #34
	bne	.L91
	adds	r3, r4, r7
	add	r3, r3, r8
.L96:
	ldrsb	r3, [r3, #5]
.L95:
	str	r3, [r5]
	adds	r4, r4, #1
	b	.L90
.L91:
	cmp	r3, #35
	bne	.L93
	ldr	r3, .L97+4
	adds	r2, r4, r7
	add	r3, r3, r2
	b	.L96
.L93:
	ldr	r3, .L97+8
	ldrsb	r3, [r3, r6]
	b	.L95
.L98:
	.align	2
.L97:
	.word	.LANCHOR10
	.word	.LANCHOR11
	.word	.LANCHOR12
	.word	.LANCHOR13
	.word	.LANCHOR9
	.size	ToshibaSetRRPara, .-ToshibaSetRRPara
	.section	.text.SamsungSetRRPara,"ax",%progbits
	.align	1
	.global	SamsungSetRRPara
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	SamsungSetRRPara, %function
SamsungSetRRPara:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r3, r4, r5, r6, r7, r8, r10, lr}
	mov	r6, r0
	ldr	r7, .L102
	movs	r4, #0
	mov	r10, #161
	ldr	r8, .L102+4
	add	r1, r7, r1, lsl #2
	adds	r5, r1, #3
.L100:
	ldrb	r3, [r8]	@ zero_extendqisi2
	cmp	r4, r3
	bcc	.L101
	pop	{r3, r4, r5, r6, r7, r8, r10, pc}
.L101:
	movs	r3, #0
	str	r10, [r6, #8]
	str	r3, [r6]
	mov	r0, #300
	ldrsb	r3, [r7, r4]
	adds	r4, r4, #1
	str	r3, [r6]
	ldrsb	r3, [r5, #1]!
	str	r3, [r6]
	bl	udelay
	b	.L100
.L103:
	.align	2
.L102:
	.word	.LANCHOR14
	.word	.LANCHOR13
	.size	SamsungSetRRPara, .-SamsungSetRRPara
	.global	__aeabi_uidiv
	.global	__aeabi_uidivmod
	.section	.text.LogAddr2PhyAddr,"ax",%progbits
	.align	1
	.global	LogAddr2PhyAddr
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	LogAddr2PhyAddr, %function
LogAddr2PhyAddr:
	@ args = 4, pretend = 0, frame = 8
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r0, r1, r4, r5, r6, r7, r8, r10, fp, lr}
	mov	r6, r3
	ldr	r3, .L109
	mov	r8, r1
	mov	r7, r2
	mov	r5, r0
	ldrh	r4, [r3, #14]
	ldrh	r3, [r3, #12]
	smulbb	r4, r4, r3
	ldr	r3, .L109+4
	ldrh	fp, [r3]
	uxth	r4, r4
	ldr	r3, .L109+8
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, #1
	ldr	r3, [r0, #4]
	it	eq
	lsleq	r1, fp, #1
	ubfx	r2, r3, #10, #16
	it	eq
	uxtheq	fp, r1
	mov	r0, r2
	str	r3, [sp, #4]
	mov	r1, r4
	str	r2, [sp]
	bl	__aeabi_uidiv
	ldr	r2, [sp]
	uxth	r10, r0
	mov	r1, r4
	mov	r0, r2
	bl	__aeabi_uidivmod
	ldr	r3, [sp, #4]
	cmp	r8, #1
	uxth	r1, r1
	ubfx	r3, r3, #0, #10
	bne	.L106
	ldr	r2, .L109+12
	ldrb	r2, [r2]	@ zero_extendqisi2
	cbnz	r2, .L106
	ldr	r2, .L109+16
	ldrh	r3, [r2, r3, lsl #1]
.L106:
	ldr	r2, .L109+20
	ldr	r2, [r2, r10, lsl #2]
	mla	r1, fp, r1, r2
	add	r1, r1, r3
	ldrb	r3, [sp, #40]	@ zero_extendqisi2
	str	r1, [r7]
	str	r10, [r6]
	cmp	r3, #1
	bls	.L108
	ldr	r0, [r5, #4]
	ldr	r3, [r5, #40]
	add	r0, r0, #1024
	subs	r3, r0, r3
	rsbs	r0, r3, #0
	adcs	r0, r0, r3
.L107:
	add	sp, sp, #8
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r10, fp, pc}
.L108:
	movs	r0, #0
	b	.L107
.L110:
	.align	2
.L109:
	.word	.LANCHOR15
	.word	.LANCHOR4
	.word	.LANCHOR2
	.word	.LANCHOR16
	.word	.LANCHOR17
	.word	.LANCHOR18
	.size	LogAddr2PhyAddr, .-LogAddr2PhyAddr
	.section	.text.FlashReadStatusEN,"ax",%progbits
	.align	1
	.global	FlashReadStatusEN
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	FlashReadStatusEN, %function
FlashReadStatusEN:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	ldr	r3, .L123
	push	{r4, r5, r6, lr}
	ldr	r5, [r3, r0, lsl #3]
	add	r3, r3, r0, lsl #3
	ldrb	r4, [r3, #4]	@ zero_extendqisi2
	ldr	r3, .L123+4
	ldr	r3, [r3]
	ldrb	r3, [r3, #8]	@ zero_extendqisi2
	cmp	r3, #2
	lsl	r3, r4, #8
	add	r4, r4, #8
	bne	.L112
	ldr	r0, .L123+8
	cbnz	r2, .L113
	ldrb	r2, [r0, #13]	@ zero_extendqisi2
.L122:
	add	r3, r3, r5
	str	r2, [r3, #2056]
	ldrb	r0, [r0, #15]	@ zero_extendqisi2
	cbz	r0, .L117
	add	r6, r5, r4, lsl #8
	movs	r2, #0
.L116:
	cmp	r2, r0
	bcc	.L118
.L117:
	lsls	r4, r4, #8
	movs	r0, #80
	bl	udelay
	ldr	r0, [r5, r4]
	uxtb	r0, r0
	pop	{r4, r5, r6, pc}
.L113:
	ldrb	r2, [r0, #14]	@ zero_extendqisi2
	b	.L122
.L118:
	lsls	r3, r2, #3
	adds	r2, r2, #1
	lsr	r3, r1, r3
	uxtb	r3, r3
	str	r3, [r6, #4]
	b	.L116
.L112:
	add	r3, r3, r5
	movs	r2, #112
	str	r2, [r3, #2056]
	b	.L117
.L124:
	.align	2
.L123:
	.word	.LANCHOR0
	.word	.LANCHOR7
	.word	.LANCHOR8
	.size	FlashReadStatusEN, .-FlashReadStatusEN
	.section	.text.FlashWaitReadyEN,"ax",%progbits
	.align	1
	.global	FlashWaitReadyEN
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	FlashWaitReadyEN, %function
FlashWaitReadyEN:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, lr}
	mov	r4, r0
	mov	r5, r1
	mov	r6, r2
.L129:
	mov	r2, r6
	mov	r1, r5
	mov	r0, r4
	bl	FlashReadStatusEN
	cmp	r0, #255
	mov	r3, r0
	beq	.L129
	lsls	r3, r3, #25
	bpl	.L129
	pop	{r4, r5, r6, pc}
	.size	FlashWaitReadyEN, .-FlashWaitReadyEN
	.section	.text.NandcReadDontCaseBusyEn,"ax",%progbits
	.align	1
	.global	NandcReadDontCaseBusyEn
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	NandcReadDontCaseBusyEn, %function
NandcReadDontCaseBusyEn:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	bx	lr
	.size	NandcReadDontCaseBusyEn, .-NandcReadDontCaseBusyEn
	.section	.text.NandcGetChipIf,"ax",%progbits
	.align	1
	.global	NandcGetChipIf
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	NandcGetChipIf, %function
NandcGetChipIf:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	ldr	r2, .L134
	add	r3, r2, r0, lsl #3
	ldr	r0, [r2, r0, lsl #3]
	ldrb	r3, [r3, #4]	@ zero_extendqisi2
	adds	r3, r3, #8
	add	r0, r0, r3, lsl #8
	bx	lr
.L135:
	.align	2
.L134:
	.word	.LANCHOR0
	.size	NandcGetChipIf, .-NandcGetChipIf
	.section	.text.NandcSetDdrPara,"ax",%progbits
	.align	1
	.global	NandcSetDdrPara
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	NandcSetDdrPara, %function
NandcSetDdrPara:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	ldr	r3, .L137
	ldr	r2, [r3]
	lsls	r3, r0, #8
	orr	r0, r3, r0, lsl #16
	orr	r0, r0, #1
	str	r0, [r2, #304]
	bx	lr
.L138:
	.align	2
.L137:
	.word	.LANCHOR19
	.size	NandcSetDdrPara, .-NandcSetDdrPara
	.section	.text.NandcSetDdrDiv,"ax",%progbits
	.align	1
	.global	NandcSetDdrDiv
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	NandcSetDdrDiv, %function
NandcSetDdrDiv:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	ldr	r3, .L140
	orr	r0, r0, #16640
	ldr	r3, [r3]
	str	r0, [r3, #344]
	bx	lr
.L141:
	.align	2
.L140:
	.word	.LANCHOR19
	.size	NandcSetDdrDiv, .-NandcSetDdrDiv
	.section	.text.NandcSetDdrMode,"ax",%progbits
	.align	1
	.global	NandcSetDdrMode
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	NandcSetDdrMode, %function
NandcSetDdrMode:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	ldr	r3, .L145
	ldr	r2, [r3]
	ldr	r3, [r2]
	cbnz	r0, .L143
	bfi	r3, r0, #13, #1
.L144:
	str	r3, [r2]
	bx	lr
.L143:
	orr	r3, r3, #253952
	b	.L144
.L146:
	.align	2
.L145:
	.word	.LANCHOR19
	.size	NandcSetDdrMode, .-NandcSetDdrMode
	.section	.text.NandcSetMode,"ax",%progbits
	.align	1
	.global	NandcSetMode
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	NandcSetMode, %function
NandcSetMode:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	ldr	r3, .L154
	ands	r1, r0, #6
	ldr	r2, [r3]
	ldr	r3, [r2]
	beq	.L148
	lsls	r1, r0, #29
	movw	r1, #16641
	str	r1, [r2, #344]
	orr	r3, r3, #24576
	ldr	r1, .L154+4
	bfc	r3, #15, #1
	orr	r3, r3, #196608
	it	mi
	orrmi	r3, r3, #32768
	str	r1, [r2, #304]
	movs	r1, #38
	str	r1, [r2, #308]
	movs	r1, #39
	str	r1, [r2, #308]
.L150:
	str	r3, [r2]
	movs	r0, #0
	bx	lr
.L148:
	bfi	r3, r1, #13, #1
	b	.L150
.L155:
	.align	2
.L154:
	.word	.LANCHOR19
	.word	1710595
	.size	NandcSetMode, .-NandcSetMode
	.section	.text.NandcFlashCs,"ax",%progbits
	.align	1
	.global	NandcFlashCs
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	NandcFlashCs, %function
NandcFlashCs:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	ldr	r3, .L157
	movs	r2, #1
	ldr	r1, [r3, r0, lsl #3]
	add	r0, r3, r0, lsl #3
	ldrb	r0, [r0, #4]	@ zero_extendqisi2
	ldr	r3, [r1]
	lsls	r2, r2, r0
	bfi	r3, r2, #0, #8
	str	r3, [r1]
	bx	lr
.L158:
	.align	2
.L157:
	.word	.LANCHOR0
	.size	NandcFlashCs, .-NandcFlashCs
	.section	.text.NandcFlashDeCs,"ax",%progbits
	.align	1
	.global	NandcFlashDeCs
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	NandcFlashDeCs, %function
NandcFlashDeCs:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	ldr	r3, .L160
	ldr	r2, [r3, r0, lsl #3]
	ldr	r3, [r2]
	bfc	r3, #0, #8
	bfc	r3, #17, #1
	str	r3, [r2]
	bx	lr
.L161:
	.align	2
.L160:
	.word	.LANCHOR0
	.size	NandcFlashDeCs, .-NandcFlashDeCs
	.section	.text.HynixSetRRPara,"ax",%progbits
	.align	1
	.global	HynixSetRRPara
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	HynixSetRRPara, %function
HynixSetRRPara:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r0, r1, r4, r5, r6, r7, r8, r10, fp, lr}
	mov	r6, r3
	ldr	r3, .L171
	mov	r5, r0
	mov	r7, r1
	mov	r10, r2
	ldr	r3, [r3]
	ldrb	r3, [r3, #19]	@ zero_extendqisi2
	cmp	r3, #6
	bne	.L163
	movs	r4, #20
	add	r4, r4, r0, lsl #6
	add	r3, r4, r6, lsl #2
.L169:
	ldr	r4, .L171+4
.L170:
	add	r4, r4, r3
.L164:
	ldr	r3, .L171+8
	mov	r0, r5
	subs	r7, r7, #1
	subs	r4, r4, #1
	add	r7, r7, r10
	ldr	r8, [r3, r5, lsl #3]
	add	r3, r3, r5, lsl #3
	ldrb	fp, [r3, #4]	@ zero_extendqisi2
	bl	NandcFlashCs
	movs	r3, #54
	lsl	fp, fp, #8
	add	r0, r8, fp
	str	r3, [r0, #2056]
	add	r3, r10, #-1
	mov	r10, r0
.L167:
	cmp	r3, r7
	bne	.L168
	movs	r3, #22
	add	r8, r8, fp
	str	r3, [r8, #2056]
	mov	r0, r5
	bl	NandcFlashDeCs
	ldr	r3, .L171+12
	strb	r6, [r3, r5]
	add	sp, sp, #8
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r10, fp, pc}
.L163:
	cmp	r3, #7
	bne	.L165
	movs	r4, #28
	movs	r3, #160
	smlabb	r3, r3, r0, r4
	movs	r4, #10
	smlabb	r3, r4, r6, r3
	b	.L169
.L165:
	cmp	r3, #8
	bne	.L166
	add	r4, r6, r6, lsl #2
	ldr	r3, .L171+16
	b	.L170
.L166:
	adds	r4, r6, #2
	add	r3, r4, r0, lsl #3
	ldr	r4, .L171+4
	add	r4, r4, r3, lsl #3
	adds	r4, r4, #4
	b	.L164
.L168:
	ldrb	r2, [r3, #1]!	@ zero_extendqisi2
	movs	r0, #200
	str	r2, [r10, #2052]
	str	r3, [sp, #4]
	bl	udelay
	ldrsb	r2, [r4, #1]!
	ldr	r3, [sp, #4]
	str	r2, [r10, #2048]
	b	.L167
.L172:
	.align	2
.L171:
	.word	.LANCHOR7
	.word	.LANCHOR20
	.word	.LANCHOR0
	.word	.LANCHOR21
	.word	.LANCHOR20+28
	.size	HynixSetRRPara, .-HynixSetRRPara
	.section	.text.FlashSetReadRetryDefault,"ax",%progbits
	.align	1
	.global	FlashSetReadRetryDefault
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	FlashSetReadRetryDefault, %function
FlashSetReadRetryDefault:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	ldr	r3, .L179
	push	{r4, r5, r6, lr}
	ldr	r3, [r3]
	ldrb	r3, [r3, #19]	@ zero_extendqisi2
	subs	r3, r3, #1
	cmp	r3, #7
	bhi	.L173
	ldr	r5, .L179+4
	movs	r4, #0
	adds	r6, r5, #4
.L176:
	ldr	r3, .L179+8
	uxtb	r0, r4
	ldrb	r3, [r3, r4, lsl #3]	@ zero_extendqisi2
	cmp	r3, #173
	bne	.L175
	movs	r3, #0
	mov	r2, r6
	ldrb	r1, [r5, #1]	@ zero_extendqisi2
	bl	HynixSetRRPara
.L175:
	adds	r4, r4, #1
	cmp	r4, #4
	bne	.L176
.L173:
	pop	{r4, r5, r6, pc}
.L180:
	.align	2
.L179:
	.word	.LANCHOR7
	.word	.LANCHOR20
	.word	.LANCHOR22
	.size	FlashSetReadRetryDefault, .-FlashSetReadRetryDefault
	.section	.text.FlashWaitCmdDone,"ax",%progbits
	.align	1
	.global	FlashWaitCmdDone
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	FlashWaitCmdDone, %function
FlashWaitCmdDone:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	ldr	r2, .L188
	lsls	r3, r0, #4
	push	{r4, r5, r6, lr}
	mov	r6, r0
	adds	r4, r2, r3
	ldr	r1, [r4, #8]
	cbz	r1, .L183
	ldrb	r5, [r2, r3]	@ zero_extendqisi2
	mov	r0, r5
	bl	NandcFlashCs
	ldr	r3, .L188+4
	mov	r0, r5
	ldr	r1, [r4, #4]
	ldr	r2, [r3, r6, lsl #2]
	adds	r2, r2, #0
	it	ne
	movne	r2, #1
	bl	FlashWaitReadyEN
	mov	r1, r0
	mov	r0, r5
	bl	NandcFlashDeCs
	ldr	r3, [r4, #8]
	sbfx	r1, r1, #0, #1
	ldr	r2, [r4, #12]
	str	r1, [r3]
	movs	r3, #0
	str	r3, [r4, #8]
	cbz	r2, .L183
	str	r1, [r2]
	str	r3, [r4, #12]
.L183:
	movs	r0, #0
	pop	{r4, r5, r6, pc}
.L189:
	.align	2
.L188:
	.word	.LANCHOR23
	.word	.LANCHOR18
	.size	FlashWaitCmdDone, .-FlashWaitCmdDone
	.section	.text.NandcDelayns,"ax",%progbits
	.align	1
	.global	NandcDelayns
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	NandcDelayns, %function
NandcDelayns:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r3, lr}
	bl	udelay
	movs	r0, #0
	pop	{r3, pc}
	.size	NandcDelayns, .-NandcDelayns
	.section	.text.NandcWaitFlashReadyNoDelay,"ax",%progbits
	.align	1
	.global	NandcWaitFlashReadyNoDelay
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	NandcWaitFlashReadyNoDelay, %function
NandcWaitFlashReadyNoDelay:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 0, uses_anonymous_args = 0
	ldr	r3, .L196
	push	{r0, r1, r2, r4, r5, lr}
	ldr	r4, .L196+4
	ldr	r5, [r3, r0, lsl #3]
.L193:
	ldr	r3, [r5]
	str	r3, [sp, #4]
	ldr	r3, [sp, #4]
	lsls	r3, r3, #22
	bmi	.L194
	movs	r0, #10
	bl	udelay
	subs	r4, r4, #1
	bne	.L193
	mov	r0, #-1
.L191:
	add	sp, sp, #12
	@ sp needed
	pop	{r4, r5, pc}
.L194:
	movs	r0, #0
	b	.L191
.L197:
	.align	2
.L196:
	.word	.LANCHOR0
	.word	100000
	.size	NandcWaitFlashReadyNoDelay, .-NandcWaitFlashReadyNoDelay
	.section	.text.NandcWaitFlashReady,"ax",%progbits
	.align	1
	.global	NandcWaitFlashReady
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	NandcWaitFlashReady, %function
NandcWaitFlashReady:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r0, r1, r2, r4, r5, lr}
	ldr	r3, .L203
	ldr	r4, .L203+4
	ldr	r5, [r3, r0, lsl #3]
	movs	r0, #130
	bl	udelay
.L200:
	ldr	r3, [r5]
	str	r3, [sp, #4]
	ldr	r3, [sp, #4]
	lsls	r3, r3, #22
	bmi	.L201
	movs	r0, #10
	bl	udelay
	subs	r4, r4, #1
	bne	.L200
	mov	r0, #-1
.L198:
	add	sp, sp, #12
	@ sp needed
	pop	{r4, r5, pc}
.L201:
	movs	r0, #0
	b	.L198
.L204:
	.align	2
.L203:
	.word	.LANCHOR0
	.word	100000
	.size	NandcWaitFlashReady, .-NandcWaitFlashReady
	.section	.text.FlashReset,"ax",%progbits
	.align	1
	.global	FlashReset
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	FlashReset, %function
FlashReset:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	ldr	r3, .L206
	push	{r4, r5, r6, lr}
	mov	r4, r0
	ldr	r5, [r3, r0, lsl #3]
	add	r3, r3, r0, lsl #3
	ldrb	r6, [r3, #4]	@ zero_extendqisi2
	bl	NandcFlashCs
	movs	r3, #255
	mov	r0, r4
	add	r5, r5, r6, lsl #8
	str	r3, [r5, #2056]
	bl	NandcWaitFlashReady
	mov	r0, r4
	pop	{r4, r5, r6, lr}
	b	NandcFlashDeCs
.L207:
	.align	2
.L206:
	.word	.LANCHOR0
	.size	FlashReset, .-FlashReset
	.section	.text.flash_enter_slc_mode,"ax",%progbits
	.align	1
	.global	flash_enter_slc_mode
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	flash_enter_slc_mode, %function
flash_enter_slc_mode:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r3, r4, r5, r6, r7, lr}
	mov	r5, r0
	ldr	r3, .L214
	ldrb	r3, [r3]	@ zero_extendqisi2
	cbz	r3, .L208
	bl	NandcFlashCs
	ldr	r3, .L214+4
	ldr	r6, [r3, r5, lsl #3]
	add	r3, r3, r5, lsl #3
	ldrb	r7, [r3, #4]	@ zero_extendqisi2
	ldr	r3, .L214+8
	ldrb	r3, [r3, r5, lsl #3]	@ zero_extendqisi2
	lsls	r7, r7, #8
	cmp	r3, #44
	bne	.L210
	adds	r4, r6, r7
	movs	r3, #239
	str	r3, [r4, #2056]
	movs	r3, #145
	str	r3, [r4, #2052]
	movs	r0, #50
	bl	udelay
	movs	r3, #0
	movs	r2, #1
	str	r3, [r4, #2048]
	movs	r0, #100
	str	r2, [r4, #2048]
	str	r3, [r4, #2048]
	str	r3, [r4, #2048]
	bl	udelay
.L210:
	mov	r0, r5
	add	r6, r6, r7
	bl	NandcWaitFlashReadyNoDelay
	movs	r3, #218
	mov	r0, r5
	str	r3, [r6, #2056]
	bl	NandcWaitFlashReady
	ldr	r3, .L214+12
	movs	r2, #2
	strb	r2, [r3]
.L208:
	pop	{r3, r4, r5, r6, r7, pc}
.L215:
	.align	2
.L214:
	.word	.LANCHOR16
	.word	.LANCHOR0
	.word	.LANCHOR22
	.word	.LANCHOR24
	.size	flash_enter_slc_mode, .-flash_enter_slc_mode
	.section	.text.flash_exit_slc_mode,"ax",%progbits
	.align	1
	.global	flash_exit_slc_mode
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	flash_exit_slc_mode, %function
flash_exit_slc_mode:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r3, r4, r5, r6, r7, lr}
	mov	r5, r0
	ldr	r3, .L222
	ldrb	r3, [r3]	@ zero_extendqisi2
	cbz	r3, .L216
	bl	NandcFlashCs
	ldr	r3, .L222+4
	ldr	r6, [r3, r5, lsl #3]
	add	r3, r3, r5, lsl #3
	ldrb	r7, [r3, #4]	@ zero_extendqisi2
	ldr	r3, .L222+8
	ldrb	r3, [r3, r5, lsl #3]	@ zero_extendqisi2
	lsls	r7, r7, #8
	cmp	r3, #44
	bne	.L218
	adds	r4, r6, r7
	movs	r3, #239
	str	r3, [r4, #2056]
	movs	r3, #145
	str	r3, [r4, #2052]
	movs	r0, #50
	bl	udelay
	movs	r3, #2
	movs	r0, #100
	str	r3, [r4, #2048]
	movs	r3, #1
	str	r3, [r4, #2048]
	movs	r3, #0
	str	r3, [r4, #2048]
	str	r3, [r4, #2048]
	bl	udelay
.L218:
	mov	r0, r5
	add	r6, r6, r7
	bl	NandcWaitFlashReadyNoDelay
	movs	r3, #223
	mov	r0, r5
	str	r3, [r6, #2056]
	bl	NandcWaitFlashReady
	ldr	r3, .L222+12
	movs	r2, #0
	strb	r2, [r3]
.L216:
	pop	{r3, r4, r5, r6, r7, pc}
.L223:
	.align	2
.L222:
	.word	.LANCHOR16
	.word	.LANCHOR0
	.word	.LANCHOR22
	.word	.LANCHOR24
	.size	flash_exit_slc_mode, .-flash_exit_slc_mode
	.section	.text.FlashEraseBlock,"ax",%progbits
	.align	1
	.global	FlashEraseBlock
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	FlashEraseBlock, %function
FlashEraseBlock:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, lr}
	mov	r4, r0
	mov	r5, r1
	mov	r6, r2
	bl	NandcWaitFlashReady
	mov	r0, r4
	bl	NandcFlashCs
	mov	r2, r6
	mov	r1, r5
	mov	r0, r4
	bl	FlashEraseCmd
	mov	r0, r4
	bl	NandcWaitFlashReady
	mov	r1, r5
	mov	r0, r4
	bl	FlashReadStatus
	mov	r1, r0
	mov	r0, r4
	bl	NandcFlashDeCs
	and	r0, r1, #1
	pop	{r4, r5, r6, pc}
	.size	FlashEraseBlock, .-FlashEraseBlock
	.section	.text.FlashSetInterfaceMode,"ax",%progbits
	.align	1
	.global	FlashSetInterfaceMode
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	FlashSetInterfaceMode, %function
FlashSetInterfaceMode:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 0, uses_anonymous_args = 0
	ldr	r3, .L253
	mov	ip, #128
	push	{r0, r1, r4, r5, r6, r7, r8, r10, fp, lr}
	movs	r5, #0
	movs	r7, #239
	mov	lr, #1
	mov	r8, #35
	mov	r10, #32
	ldrb	r3, [r3]	@ zero_extendqisi2
	and	r2, r3, #4
	and	r3, r3, #1
	str	r2, [sp, #4]
	mov	r2, r5
	str	r3, [sp]
.L235:
	ldr	r3, .L253+4
	ldrb	r4, [r5, r3]	@ zero_extendqisi2
	cmp	r4, #152
	beq	.L226
	cmp	r4, #69
	beq	.L226
	cmp	r4, #173
	beq	.L226
	cmp	r4, #44
	bne	.L227
.L226:
	ldr	r3, .L253+8
	cmp	r0, #1
	ldr	r1, [r5, r3]
	add	r3, r3, r5
	ldrb	r3, [r3, #4]	@ zero_extendqisi2
	bne	.L228
	ldr	r6, [sp]
	cbz	r6, .L227
	lsls	r3, r3, #8
	cmp	r4, #173
	add	fp, r1, r3
	str	r7, [fp, #2056]
	bne	.L229
	str	r0, [fp, #2052]
.L252:
	str	r2, [fp, #2048]
	b	.L233
.L229:
	cmp	r4, #44
	ittet	eq
	moveq	r4, #5
	streq	r0, [fp, #2052]
	strne	ip, [fp, #2052]
	streq	r4, [fp, #2048]
	it	ne
	strne	r0, [fp, #2048]
.L233:
	add	r3, r3, r1
	str	r2, [r3, #2048]
	str	r2, [r3, #2048]
	str	r2, [r3, #2048]
.L227:
	adds	r5, r5, #8
	cmp	r5, #32
	bne	.L235
	movs	r0, #0
	bl	NandcWaitFlashReady
	movs	r0, #0
	add	sp, sp, #8
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r10, fp, pc}
.L228:
	ldr	r6, [sp, #4]
	cmp	r6, #0
	beq	.L227
	lsls	r3, r3, #8
	cmp	r4, #173
	add	fp, r1, r3
	str	r7, [fp, #2056]
	bne	.L232
	str	lr, [fp, #2052]
	str	r10, [fp, #2048]
	b	.L233
.L232:
	cmp	r4, #44
	bne	.L234
	str	lr, [fp, #2052]
	str	r8, [fp, #2048]
	b	.L233
.L234:
	str	ip, [fp, #2052]
	b	.L252
.L254:
	.align	2
.L253:
	.word	.LANCHOR25
	.word	.LANCHOR22
	.word	.LANCHOR0
	.size	FlashSetInterfaceMode, .-FlashSetInterfaceMode
	.section	.text.SandiskSetRRPara,"ax",%progbits
	.align	1
	.global	SandiskSetRRPara
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	SandiskSetRRPara, %function
SandiskSetRRPara:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r3, r4, r5, r6, r7, lr}
	movs	r3, #239
	str	r3, [r0, #8]
	movs	r3, #17
	mov	r5, r0
	mov	r4, r1
	str	r3, [r0, #4]
	movs	r0, #200
	bl	udelay
	ldr	r3, .L261
	add	r4, r4, r4, lsl #2
	ldr	r6, .L261+4
	movs	r2, #0
	ldr	r7, .L261+8
	ldrb	r1, [r3]	@ zero_extendqisi2
	ldr	r3, .L261+12
	ldrb	r0, [r3]	@ zero_extendqisi2
.L256:
	cmp	r2, r1
	bcc	.L259
	movs	r0, #0
	pop	{r3, r4, r5, r6, r7, lr}
	b	NandcWaitFlashReady
.L259:
	adds	r3, r2, r4
	cmp	r0, #67
	ite	eq
	addeq	r3, r3, r7
	addne	r3, r3, r6
	ldrsb	r3, [r3, #5]
	adds	r2, r2, #1
	str	r3, [r5]
	b	.L256
.L262:
	.align	2
.L261:
	.word	.LANCHOR13
	.word	.LANCHOR11
	.word	.LANCHOR9
	.word	.LANCHOR10
	.size	SandiskSetRRPara, .-SandiskSetRRPara
	.section	.text.micron_auto_read_calibration_config,"ax",%progbits
	.align	1
	.global	micron_auto_read_calibration_config
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	micron_auto_read_calibration_config, %function
micron_auto_read_calibration_config:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, lr}
	mov	r5, r0
	mov	r6, r1
	bl	NandcWaitFlashReady
	ldr	r0, .L264
	ldr	r4, [r0, r5, lsl #3]
	add	r0, r0, r5, lsl #3
	ldrb	r3, [r0, #4]	@ zero_extendqisi2
	movs	r0, #200
	add	r4, r4, r3, lsl #8
	movs	r3, #239
	str	r3, [r4, #2056]
	movs	r3, #150
	str	r3, [r4, #2052]
	bl	udelay
	movs	r3, #0
	str	r6, [r4, #2048]
	str	r3, [r4, #2048]
	str	r3, [r4, #2048]
	str	r3, [r4, #2048]
	pop	{r4, r5, r6, pc}
.L265:
	.align	2
.L264:
	.word	.LANCHOR0
	.size	micron_auto_read_calibration_config, .-micron_auto_read_calibration_config
	.section	.text.FlashEraseSLc2KBlocks,"ax",%progbits
	.align	1
	.global	FlashEraseSLc2KBlocks
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	FlashEraseSLc2KBlocks, %function
FlashEraseSLc2KBlocks:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, r8, r10, lr}
	mov	r7, r1
	ldr	r8, .L276+12
	sub	sp, sp, #20
	mov	r5, r0
	movs	r6, #0
	ldr	r10, .L276+16
.L267:
	cmp	r6, r7
	bne	.L272
	movs	r0, #0
	add	sp, sp, #20
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r10, pc}
.L272:
	subs	r3, r7, r6
	add	r2, sp, #8
	uxtb	r3, r3
	movs	r1, #0
	mov	r0, r5
	str	r3, [sp]
	add	r3, sp, #12
	bl	LogAddr2PhyAddr
	ldr	r3, [sp, #12]
	ldrb	r2, [r8]	@ zero_extendqisi2
	cmp	r2, r3
	bhi	.L268
	mov	r3, #-1
	str	r3, [r5]
.L269:
	adds	r6, r6, #1
	adds	r5, r5, #36
	b	.L267
.L268:
	ldrb	r4, [r10, r3]	@ zero_extendqisi2
	lsls	r3, r3, #4
	ldr	r2, .L276
	mov	r0, r4
	strb	r4, [r2, r3]
	bl	NandcWaitFlashReady
	mov	r0, r4
	bl	NandcFlashCs
	movs	r2, #0
	ldr	r1, [sp, #8]
	mov	r0, r4
	bl	FlashEraseCmd
	mov	r0, r4
	bl	NandcWaitFlashReady
	ldr	r1, [sp, #8]
	mov	r0, r4
	bl	FlashReadStatus
	ldr	r3, .L276+4
	sbfx	r0, r0, #0, #1
	str	r0, [r5]
	movs	r2, #0
	ldr	r1, [sp, #8]
	mov	r0, r4
	ldr	r3, [r3]
	add	r1, r1, r3
	bl	FlashEraseCmd
	mov	r0, r4
	bl	NandcWaitFlashReady
	ldr	r1, [sp, #8]
	mov	r0, r4
	bl	FlashReadStatus
	lsls	r3, r0, #31
	itt	mi
	movmi	r3, #-1
	strmi	r3, [r5]
	ldr	r3, [r5]
	adds	r3, r3, #1
	bne	.L271
	ldr	r1, [sp, #8]
	ldr	r0, .L276+8
	bl	printf
.L271:
	mov	r0, r4
	bl	NandcFlashDeCs
	b	.L269
.L277:
	.align	2
.L276:
	.word	.LANCHOR23
	.word	.LANCHOR4
	.word	.LC1
	.word	.LANCHOR26
	.word	.LANCHOR27
	.size	FlashEraseSLc2KBlocks, .-FlashEraseSLc2KBlocks
	.section	.text.FlashEraseBlocks,"ax",%progbits
	.align	1
	.global	FlashEraseBlocks
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	FlashEraseBlocks, %function
FlashEraseBlocks:
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 0, uses_anonymous_args = 0
	ldr	r3, .L305
	push	{r4, r5, r6, r7, r8, r10, fp, lr}
	mov	r8, r0
	sub	sp, sp, #24
	mov	fp, r1
	mov	r7, r2
	ldrb	r4, [r3]	@ zero_extendqisi2
	cbnz	r4, .L279
	ldr	r10, .L305+8
.L280:
	cmp	r4, r7
	bcc	.L289
	ldr	r5, .L305+4
	movs	r4, #0
	ldr	r6, .L305+8
.L290:
	ldr	r3, .L305+12
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r4, r3
	bcc	.L292
	movs	r0, #0
	b	.L278
.L279:
	mov	r1, r2
	bl	FlashEraseSLc2KBlocks
.L278:
	add	sp, sp, #24
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r10, fp, pc}
.L289:
	movs	r5, #36
	add	r2, sp, #16
	muls	r5, r4, r5
	movs	r1, #0
	add	r3, r8, r5
	str	r3, [sp, #12]
	subs	r3, r7, r4
	uxtb	r3, r3
	ldr	r0, [sp, #12]
	str	r3, [sp]
	add	r3, sp, #20
	bl	LogAddr2PhyAddr
	ldr	r3, .L305+12
	mov	r6, r0
	ldr	r0, [sp, #20]
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, r0
	bhi	.L282
	mov	r3, #-1
	str	r3, [r8, r5]
.L283:
	adds	r4, r4, #1
	b	.L280
.L282:
	ldr	r3, .L305+16
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, #0
	add	r3, r10, r0, lsl #4
	it	eq
	moveq	r6, #0
	ldr	r3, [r3, #8]
	cbz	r3, .L285
	uxtb	r0, r0
	bl	FlashWaitCmdDone
.L285:
	ldr	r1, [sp, #20]
	ldr	r0, [sp, #12]
	lsls	r2, r1, #4
	add	r3, r10, r2
	str	r0, [r3, #8]
	movs	r0, #0
	str	r0, [r3, #12]
	ldr	r0, [sp, #16]
	str	r0, [r3, #4]
	cbz	r6, .L286
	adds	r5, r5, #36
	add	r5, r5, r8
	str	r5, [r3, #12]
.L286:
	ldr	r3, .L305+20
	ldrb	r5, [r3, r1]	@ zero_extendqisi2
	mov	r0, r5
	strb	r5, [r10, r2]
	bl	NandcFlashCs
	cmp	fp, #1
	mov	r0, r5
	bne	.L287
	ldr	r3, .L305+4
	ldrb	r3, [r3]	@ zero_extendqisi2
	cbz	r3, .L287
	bl	flash_enter_slc_mode
.L288:
	ldr	r3, .L305+24
	mov	r0, r5
	ldr	r2, [sp, #20]
	add	r4, r4, r6
	ldr	r1, [sp, #16]
	ldr	r2, [r3, r2, lsl #2]
	adds	r2, r2, #0
	it	ne
	movne	r2, #1
	bl	FlashWaitReadyEN
	mov	r2, r6
	ldr	r1, [sp, #16]
	mov	r0, r5
	bl	FlashEraseCmd
	mov	r0, r5
	bl	NandcFlashDeCs
	b	.L283
.L287:
	bl	flash_exit_slc_mode
	b	.L288
.L292:
	uxtb	r0, r4
	bl	FlashWaitCmdDone
	cmp	fp, #1
	bne	.L291
	ldrb	r3, [r5]	@ zero_extendqisi2
	cbz	r3, .L291
	lsls	r3, r4, #4
	ldrb	r0, [r6, r3]	@ zero_extendqisi2
	bl	flash_exit_slc_mode
.L291:
	adds	r4, r4, #1
	b	.L290
.L306:
	.align	2
.L305:
	.word	.LANCHOR2
	.word	.LANCHOR16
	.word	.LANCHOR23
	.word	.LANCHOR26
	.word	.LANCHOR28
	.word	.LANCHOR27
	.word	.LANCHOR18
	.size	FlashEraseBlocks, .-FlashEraseBlocks
	.section	.text.FlashReadDpCmd,"ax",%progbits
	.align	1
	.global	FlashReadDpCmd
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	FlashReadDpCmd, %function
FlashReadDpCmd:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	ldr	r3, .L313
	push	{r4, r5, r6, r7, r8, r10, fp, lr}
	mov	r8, r1
	ldr	lr, .L313+8
	uxtb	fp, r2
	lsr	r10, r2, #8
	lsrs	r5, r2, #16
	ldr	r4, [r3, r0, lsl #3]
	add	r3, r3, r0, lsl #3
	ldr	r2, [lr]
	mov	r7, r0
	ldrb	r6, [r3, #4]	@ zero_extendqisi2
	uxtb	ip, r8
	ldr	r3, .L313+4
	lsr	r0, r8, #8
	ldrb	r2, [r2, #7]	@ zero_extendqisi2
	ldrb	r1, [r3, #16]	@ zero_extendqisi2
	lsls	r6, r6, #8
	cmp	r1, #1
	lsr	r1, r8, #16
	bne	.L308
	cmp	r2, #1
	ittt	eq
	addeq	r2, r4, r6
	moveq	lr, #38
	streq	lr, [r2, #2056]
	add	r4, r4, r6
	ldrb	r2, [r3, #8]	@ zero_extendqisi2
	movs	r6, #0
	str	r2, [r4, #2056]
	ldrb	r3, [r3, #9]	@ zero_extendqisi2
	str	r6, [r4, #2052]
	str	r6, [r4, #2052]
	str	ip, [r4, #2052]
	str	r0, [r4, #2052]
	mov	r0, r7
	str	r1, [r4, #2052]
	str	r3, [r4, #2056]
	bl	NandcWaitFlashReady
	str	r6, [r4, #2056]
	str	r6, [r4, #2052]
	str	r6, [r4, #2052]
.L312:
	movs	r3, #48
	str	fp, [r4, #2052]
	mov	r1, r8
	str	r10, [r4, #2052]
	mov	r0, r7
	str	r5, [r4, #2052]
	str	r3, [r4, #2056]
	pop	{r4, r5, r6, r7, r8, r10, fp, lr}
	b	FlashSetRandomizer
.L308:
	cmp	r2, #1
	ittt	eq
	addeq	r2, r4, r6
	moveq	lr, #38
	streq	lr, [r2, #2056]
	add	r4, r4, r6
	ldrb	r2, [r3, #8]	@ zero_extendqisi2
	str	r2, [r4, #2056]
	ldrb	r3, [r3, #9]	@ zero_extendqisi2
	str	ip, [r4, #2052]
	str	r0, [r4, #2052]
	str	r1, [r4, #2052]
	str	r3, [r4, #2056]
	b	.L312
.L314:
	.align	2
.L313:
	.word	.LANCHOR0
	.word	.LANCHOR8
	.word	.LANCHOR7
	.size	FlashReadDpCmd, .-FlashReadDpCmd
	.section	.text.ftl_flash_de_init,"ax",%progbits
	.align	1
	.global	ftl_flash_de_init
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	ftl_flash_de_init, %function
ftl_flash_de_init:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, lr}
	movs	r0, #0
	bl	NandcWaitFlashReady
	bl	FlashSetReadRetryDefault
	ldr	r3, .L325
	ldr	r0, [r3]
	cbz	r0, .L316
	movs	r0, #0
	bl	flash_enter_slc_mode
.L317:
	ldr	r4, .L325+4
	ldrb	r3, [r4]	@ zero_extendqisi2
	cbz	r3, .L318
	ldr	r3, .L325+8
	ldrb	r3, [r3]	@ zero_extendqisi2
	lsls	r3, r3, #31
	bpl	.L318
	movs	r0, #1
	bl	FlashSetInterfaceMode
	movs	r0, #1
	bl	NandcSetMode
	movs	r3, #0
	strb	r3, [r4]
.L318:
	ldr	r3, .L325+12
	movs	r0, #0
	ldr	r3, [r3]
	str	r0, [r3, #336]
	pop	{r4, pc}
.L316:
	bl	flash_exit_slc_mode
	b	.L317
.L326:
	.align	2
.L325:
	.word	.LANCHOR29
	.word	.LANCHOR30
	.word	.LANCHOR25
	.word	.LANCHOR0
	.size	ftl_flash_de_init, .-ftl_flash_de_init
	.section	.text.NandcRandmzSel,"ax",%progbits
	.align	1
	.global	NandcRandmzSel
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	NandcRandmzSel, %function
NandcRandmzSel:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	ldr	r3, .L328
	ldr	r3, [r3, r0, lsl #3]
	str	r1, [r3, #336]
	bx	lr
.L329:
	.align	2
.L328:
	.word	.LANCHOR0
	.size	NandcRandmzSel, .-NandcRandmzSel
	.section	.text.NandcTimeCfg,"ax",%progbits
	.align	1
	.global	NandcTimeCfg
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	NandcTimeCfg, %function
NandcTimeCfg:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	ldr	r3, .L335
	cmp	r0, #35
	ldr	r3, [r3]
	bhi	.L331
	movw	r2, #4193
.L334:
	str	r2, [r3, #4]
	bx	lr
.L331:
	cmp	r0, #99
	ite	hi
	movwhi	r2, #8322
	movwls	r2, #4225
	b	.L334
.L336:
	.align	2
.L335:
	.word	.LANCHOR19
	.size	NandcTimeCfg, .-NandcTimeCfg
	.section	.text.FlashTimingCfg,"ax",%progbits
	.align	1
	.global	FlashTimingCfg
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	FlashTimingCfg, %function
FlashTimingCfg:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	ldr	r3, .L338
	ldrb	r0, [r3, #21]	@ zero_extendqisi2
	b	NandcTimeCfg
.L339:
	.align	2
.L338:
	.word	.LANCHOR31
	.size	FlashTimingCfg, .-FlashTimingCfg
	.section	.text.NandcBchSel,"ax",%progbits
	.align	1
	.global	NandcBchSel
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	NandcBchSel, %function
NandcBchSel:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	ldr	r3, .L348
	movs	r1, #0
	push	{r4, lr}
	movs	r4, #16
	cmp	r0, r4
	ldr	r2, [r3]
	mov	r3, #1
	str	r3, [r2, #8]
	ldr	r3, .L348+4
	str	r0, [r3]
	mov	r3, r1
	bfi	r3, r4, #8, #8
	bfi	r3, r1, #18, #1
	bne	.L341
.L344:
	bfc	r3, #4, #1
.L342:
	orr	r3, r3, #1
	str	r3, [r2, #12]
	pop	{r4, pc}
.L341:
	cmp	r0, #24
	bne	.L343
	orr	r3, r3, #16
	b	.L342
.L343:
	cmp	r0, #40
	orr	r3, r3, #262144
	orr	r3, r3, #16
	bne	.L342
	b	.L344
.L349:
	.align	2
.L348:
	.word	.LANCHOR19
	.word	.LANCHOR32
	.size	NandcBchSel, .-NandcBchSel
	.section	.text.FlashBchSel,"ax",%progbits
	.align	1
	.global	FlashBchSel
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	FlashBchSel, %function
FlashBchSel:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	ldr	r3, .L351
	strb	r0, [r3]
	b	NandcBchSel
.L352:
	.align	2
.L351:
	.word	.LANCHOR33
	.size	FlashBchSel, .-FlashBchSel
	.section	.text.ftl_nandc_get_irq_status,"ax",%progbits
	.align	1
	.global	ftl_nandc_get_irq_status
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	ftl_nandc_get_irq_status, %function
ftl_nandc_get_irq_status:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	ldr	r0, [r0, #372]
	bx	lr
	.size	ftl_nandc_get_irq_status, .-ftl_nandc_get_irq_status
	.section	.text.rk_nandc_flash_ready,"ax",%progbits
	.align	1
	.global	rk_nandc_flash_ready
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	rk_nandc_flash_ready, %function
rk_nandc_flash_ready:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	bx	lr
	.size	rk_nandc_flash_ready, .-rk_nandc_flash_ready
	.section	.text.NandcIqrWaitFlashReady,"ax",%progbits
	.align	1
	.global	NandcIqrWaitFlashReady
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	NandcIqrWaitFlashReady, %function
NandcIqrWaitFlashReady:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	bx	lr
	.size	NandcIqrWaitFlashReady, .-NandcIqrWaitFlashReady
	.section	.text.rk_nandc_flash_xfer_completed,"ax",%progbits
	.align	1
	.global	rk_nandc_flash_xfer_completed
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	rk_nandc_flash_xfer_completed, %function
rk_nandc_flash_xfer_completed:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	bx	lr
	.size	rk_nandc_flash_xfer_completed, .-rk_nandc_flash_xfer_completed
	.section	.text.NandcSendDumpDataStart,"ax",%progbits
	.align	1
	.global	NandcSendDumpDataStart
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	NandcSendDumpDataStart, %function
NandcSendDumpDataStart:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	ldr	r2, [r0, #16]
	sub	sp, sp, #8
	ldr	r3, .L358
	str	r2, [sp, #4]
	ldr	r2, [sp, #4]
	bfc	r2, #2, #1
	str	r2, [sp, #4]
	ldr	r2, [sp, #4]
	str	r2, [r0, #16]
	str	r3, [r0, #8]
	orr	r3, r3, #4
	str	r3, [r0, #8]
	add	sp, sp, #8
	@ sp needed
	bx	lr
.L359:
	.align	2
.L358:
	.word	538969130
	.size	NandcSendDumpDataStart, .-NandcSendDumpDataStart
	.section	.text.NandcSendDumpDataDone,"ax",%progbits
	.align	1
	.global	NandcSendDumpDataDone
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	NandcSendDumpDataDone, %function
NandcSendDumpDataDone:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	sub	sp, sp, #8
.L361:
	ldr	r3, [r0, #8]
	str	r3, [sp, #4]
	ldr	r3, [sp, #4]
	lsls	r3, r3, #11
	bpl	.L361
	add	sp, sp, #8
	@ sp needed
	bx	lr
	.size	NandcSendDumpDataDone, .-NandcSendDumpDataDone
	.section	.text.NandcXferStart,"ax",%progbits
	.align	1
	.global	NandcXferStart
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	NandcXferStart, %function
NandcXferStart:
	@ args = 8, pretend = 0, frame = 24
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, r8, r10, fp, lr}
	sub	sp, sp, #24
	mov	r7, r1
	ldr	r1, [sp, #60]
	str	r2, [sp, #4]
	ldr	fp, [sp, #56]
	cmp	r1, #0
	bne	.L378
	adds	r5, fp, #0
	it	ne
	movne	r5, #1
.L365:
	ldr	r1, .L383
	movs	r4, #0
	ldr	r6, [r1, r0, lsl #3]
	add	r1, r1, r0, lsl #3
	movs	r0, #16
	ldr	r8, [r6, #12]
	ldrb	r1, [r1, #4]	@ zero_extendqisi2
	bfi	r8, r0, #8, #8
	bfi	r8, r4, #3, #1
	bfi	r4, r7, #1, #1
	bfi	r8, r1, #5, #3
	orr	r4, r4, #8
	movs	r1, #1
	bfi	r4, r1, #5, #2
	lsrs	r3, r3, r1
	orr	r4, r4, #536870912
	orr	r4, r4, #1024
	bfi	r4, r3, #4, #1
	ldr	r3, .L383+4
	ldr	r3, [r3]
	cmp	r3, #3
	bls	.L366
	ldr	r3, [r6, #16]
	str	r3, [sp, #20]
	ldr	r3, [sp, #20]
	bfc	r3, #2, #1
	str	r3, [sp, #20]
	cmp	r5, #0
	beq	.L367
	ldr	r5, .L383+8
	cmp	r7, #0
	bne	.L368
.L376:
	ldr	r2, [sp, #4]
	adds	r2, r2, #1
	asrs	r2, r2, #1
	bfi	r4, r2, #22, #6
	cmp	fp, #0
	beq	.L369
	mov	r0, fp
.L370:
	ldr	r3, [r5, #4]
	add	r1, r0, #63
	ubfx	r10, r4, #22, #5
	bic	r1, r1, #63
	str	r0, [r5, #8]
	add	r1, r1, r10, lsl #10
	str	r0, [r5, #16]
	bic	r0, r0, #63
	str	r3, [r5, #12]
	clz	r7, r7
	str	r3, [r5, #20]
	lsrs	r7, r7, #5
	bl	flush_dcache_range
	ldr	r0, [r5, #20]
	add	r1, r0, #63
	bic	r0, r0, #63
	bic	r1, r1, #63
	add	r1, r1, r10, lsl #7
	bl	flush_dcache_range
	movs	r3, #1
	movs	r2, #16
	str	r3, [r5, #24]
	tst	fp, #3
	ldr	r3, [r5, #16]
	str	r3, [r6, #20]
	ldr	r3, [r5, #20]
	str	r3, [r6, #24]
	mov	r3, #0
	str	r3, [sp, #20]
	ldr	r3, [sp, #20]
	bfi	r3, r2, #9, #5
	it	eq
	moveq	r2, #2
	str	r3, [sp, #20]
	ldr	r3, [sp, #20]
	orr	r3, r3, #448
	str	r3, [sp, #20]
	ittt	eq
	ldreq	r3, [sp, #20]
	bfieq	r3, r2, #3, #3
	streq	r3, [sp, #20]
	ldr	r3, [sp, #20]
	orr	r3, r3, #4
	str	r3, [sp, #20]
	ldr	r3, [sp, #20]
	bfi	r3, r7, #1, #1
	str	r3, [sp, #20]
	ldr	r3, [sp, #20]
	orr	r3, r3, #1
	str	r3, [sp, #20]
.L367:
	ldr	r3, [sp, #20]
	str	r3, [r6, #16]
.L366:
	str	r8, [r6, #12]
	str	r4, [r6, #8]
	orr	r4, r4, #4
	str	r4, [r6, #8]
	add	sp, sp, #24
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r10, fp, pc}
.L378:
	movs	r5, #1
	b	.L365
.L368:
	ldr	r3, .L383+12
	movs	r1, #0
	ldr	lr, [r5, #4]
	mov	r0, r1
	ldr	r3, [r3]
	cmp	r3, #25
	ite	cc
	movcc	r3, #64
	movcs	r3, #128
	str	r3, [sp, #8]
	ldr	r3, [sp, #4]
	lsrs	r3, r3, #1
	str	r3, [sp, #12]
	ldr	r3, [sp, #60]
.L372:
	ldr	r2, [sp, #12]
	cmp	r0, r2
	bcs	.L376
	ldr	r2, [sp, #60]
	bic	r10, r1, #3
	cbz	r2, .L373
	ldrh	ip, [r3]
	adds	r3, r3, #4
	ldrh	r2, [r3, #-2]
	orr	ip, ip, r2, lsl #16
	str	ip, [lr, r10]
.L374:
	ldr	r2, [sp, #8]
	adds	r0, r0, #1
	add	r1, r1, r2
	b	.L372
.L373:
	mov	r2, #-1
	str	r2, [lr, r10]
	b	.L374
.L369:
	ldr	r3, .L383+8
	ldr	r0, [r3]
	b	.L370
.L384:
	.align	2
.L383:
	.word	.LANCHOR0
	.word	.LANCHOR34
	.word	.LANCHOR35
	.word	.LANCHOR32
	.size	NandcXferStart, .-NandcXferStart
	.section	.text.NandcXferComp,"ax",%progbits
	.align	1
	.global	NandcXferComp
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	NandcXferComp, %function
NandcXferComp:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 0, uses_anonymous_args = 0
	ldr	r3, .L413
	push	{r0, r1, r4, lr}
	ldr	r1, [r3, r0, lsl #3]
	ldr	r3, .L413+4
	ldr	r0, [r3]
	cmp	r0, #3
	bls	.L406
	ldr	r3, [r1, #16]
	lsls	r2, r3, #29
	bpl	.L406
	ldr	r3, [r1, #16]
	tst	r3, #2
	ldr	r3, [r1, #8]
	str	r3, [sp]
	beq	.L393
.L389:
	ldr	r2, [r1, #28]
	ldr	r3, [sp]
	ubfx	r2, r2, #16, #5
	ubfx	r3, r3, #22, #6
	cmp	r2, r3
	bge	.L390
	cmp	r0, #5
	bls	.L389
	ldr	r3, [r1]
	str	r3, [sp, #4]
	ldr	r3, [sp, #4]
	lsls	r3, r3, #18
	bpl	.L389
	ldr	r3, [sp, #4]
	lsls	r4, r3, #14
	bpl	.L389
.L390:
	ldr	r3, .L413+8
	movs	r2, #0
	str	r2, [r3, #24]
.L385:
	add	sp, sp, #8
	@ sp needed
	pop	{r4, pc}
.L394:
	ldr	r3, [r1, #8]
	str	r3, [sp]
.L393:
	ldr	r3, [sp]
	lsls	r2, r3, #11
	bpl	.L394
	ldr	r4, .L413+12
	ldr	r2, [r4]
	cbz	r2, .L395
	mov	r0, r1
	bl	NandcSendDumpDataStart
.L395:
	ldr	r3, [r4]
	cmp	r3, #0
	beq	.L390
	mov	r0, r1
	bl	NandcSendDumpDataDone
	b	.L390
.L406:
	ldr	r3, [r1, #8]
	str	r3, [sp]
	ldr	r3, [sp]
	lsls	r3, r3, #11
	bpl	.L406
	b	.L385
.L414:
	.align	2
.L413:
	.word	.LANCHOR0
	.word	.LANCHOR34
	.word	.LANCHOR35
	.word	.LANCHOR36
	.size	NandcXferComp, .-NandcXferComp
	.section	.text.Ftl_log2,"ax",%progbits
	.align	1
	.global	Ftl_log2
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	Ftl_log2, %function
Ftl_log2:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	movs	r1, #0
	movs	r2, #1
.L416:
	cmp	r2, r0
	uxth	r3, r1
	add	r1, r1, #1
	bls	.L417
	subs	r0, r3, #1
	uxth	r0, r0
	bx	lr
.L417:
	lsls	r2, r2, #1
	b	.L416
	.size	Ftl_log2, .-Ftl_log2
	.section	.text.FtlPrintInfo,"ax",%progbits
	.align	1
	.global	FtlPrintInfo
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	FtlPrintInfo, %function
FtlPrintInfo:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	bx	lr
	.size	FtlPrintInfo, .-FtlPrintInfo
	.section	.text.FtlSysBlkNumInit,"ax",%progbits
	.align	1
	.global	FtlSysBlkNumInit
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	FtlSysBlkNumInit, %function
FtlSysBlkNumInit:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	ldr	r3, .L420
	cmp	r0, #24
	it	cc
	movcc	r0, #24
	ldr	r2, .L420+4
	str	r0, [r3]
	ldr	r3, .L420+8
	ldrh	r3, [r3]
	muls	r3, r0, r3
	str	r3, [r2]
	ldr	r2, .L420+12
	ldrh	r2, [r2]
	subs	r0, r2, r0
	ldr	r2, .L420+16
	strh	r0, [r2]	@ movhi
	movs	r0, #0
	ldr	r2, .L420+20
	ldr	r2, [r2]
	subs	r3, r2, r3
	ldr	r2, .L420+24
	str	r3, [r2]
	bx	lr
.L421:
	.align	2
.L420:
	.word	.LANCHOR37
	.word	.LANCHOR39
	.word	.LANCHOR38
	.word	.LANCHOR41
	.word	.LANCHOR40
	.word	.LANCHOR43
	.word	.LANCHOR42
	.size	FtlSysBlkNumInit, .-FtlSysBlkNumInit
	.global	__aeabi_idiv
	.section	.text.FtlConstantsInit,"ax",%progbits
	.align	1
	.global	FtlConstantsInit
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	FtlConstantsInit, %function
FtlConstantsInit:
	@ args = 0, pretend = 0, frame = 24
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, r8, r10, fp, lr}
	mov	r10, r0
	ldrh	r7, [r0, #8]
	sub	sp, sp, #24
	ldr	r3, .L449
	ldrh	r2, [r0, #10]
	ldrh	r6, [r0, #14]
	strh	r7, [r3]	@ movhi
	ldrh	r3, [r0, #12]
	ldr	r0, .L449+4
	ldr	r1, .L449+8
	ldr	r4, .L449+12
	strh	r6, [r0]	@ movhi
	str	r0, [sp, #20]
	ldr	r0, .L449+16
	strh	r3, [r1]	@ movhi
	movs	r1, #0
	strh	r2, [r4]	@ movhi
	str	r4, [sp, #8]
.L423:
	strb	r1, [r1, r0]
	adds	r1, r1, #1
	cmp	r1, #32
	bne	.L423
	ldrh	r0, [r10, #14]
	ldrh	r1, [r10, #20]
	cmp	r1, r0, lsr #8
	bcs	.L424
	uxtb	r8, r3
	lsl	r1, r8, #1
	uxtb	r1, r1
	str	r1, [sp, #4]
	subs	r1, r2, #1
	muls	r1, r3, r1
	str	r1, [sp, #12]
	movs	r1, #0
.L425:
	cmp	r1, r3
	bcs	.L427
	ldr	r4, [sp, #12]
	sub	fp, r1, r3
	uxtb	r0, r1
	adds	r5, r1, r4
	ldr	r4, .L449+16
	add	r4, r4, r5
	movs	r5, #0
	mov	lr, r4
	ldr	r4, .L449+16
	mov	ip, r5
	add	fp, fp, r4
	b	.L428
.L426:
	add	r4, r8, r0
	strb	r0, [fp, r5]
	str	r4, [sp, #16]
	add	ip, ip, #1
	ldrb	r4, [sp, #16]	@ zero_extendqisi2
	strb	r4, [lr, r5]
	ldr	r4, [sp, #4]
	add	r0, r0, r4
	uxtb	r0, r0
.L428:
	cmp	ip, r2
	add	r5, r5, r3
	bcc	.L426
	adds	r1, r1, #1
	b	.L425
.L427:
	ldr	r1, [sp, #8]
	lsls	r2, r2, #1
	lsrs	r6, r6, #1
	strh	r2, [r1]	@ movhi
	ldr	r2, .L449+4
	strh	r6, [r2]	@ movhi
.L424:
	ldr	r1, .L449+20
	movs	r2, #5
	cmp	r7, #1
	mov	r0, #0
	strh	r2, [r1]	@ movhi
	ldr	r2, .L449+24
	it	eq
	strheq	r7, [r1]	@ movhi
	ldr	r1, .L449+28
	strh	r0, [r2]	@ movhi
	mov	r0, #4352
	strh	r0, [r1]	@ movhi
	ldr	r0, .L449+32
	ldrb	r0, [r0]	@ zero_extendqisi2
	str	r0, [sp, #4]
	cbz	r0, .L430
	mov	r0, #384
	strh	r0, [r1]	@ movhi
.L430:
	str	r2, [sp, #16]
	ldr	r2, [sp, #8]
	ldr	r1, .L449+36
	ldrh	r6, [r10, #16]
	ldrh	r5, [r2]
	ldr	r2, [sp, #20]
	ldr	fp, .L449+116
	ldr	r8, .L449+120
	smulbb	r5, r5, r3
	ldrh	r4, [r2]
	strh	r6, [fp]	@ movhi
	uxth	r5, r5
	smulbb	r3, r3, r4
	strh	r5, [r1]	@ movhi
	smulbb	r0, r5, r6
	ldr	r1, .L449+40
	strh	r3, [r1]	@ movhi
	ldrh	r1, [r10, #18]
	ldr	r3, .L449+44
	str	r1, [sp, #12]
	strh	r1, [r3]	@ movhi
	ldr	r3, .L449+48
	strh	r0, [r3]	@ movhi
	ldrh	r3, [r10, #20]
	mov	r0, r3
	strh	r3, [r8]	@ movhi
	str	r3, [sp, #8]
	bl	Ftl_log2
	ldr	r3, [sp, #8]
	mov	r7, r0
	ldr	ip, .L449+124
	cmp	r4, #1024
	ldr	lr, .L449+128
	ldr	r2, [sp, #16]
	strh	r0, [ip]	@ movhi
	lsl	r0, r3, #9
	ldr	r1, [sp, #12]
	uxth	r0, r0
	strh	r0, [lr]	@ movhi
	lsr	r0, r0, #8
	ldr	lr, .L449+132
	mul	r1, r3, r1
	strh	r0, [lr]	@ movhi
	ldrh	lr, [r10, #26]
	mov	r10, ip
	ldr	r0, .L449+52
	strh	lr, [r0]	@ movhi
	mul	lr, r4, r5
	ldr	r0, .L449+56
	str	lr, [r0]
	itt	hi
	uxtbhi	r0, r4
	strhhi	r0, [r2]	@ movhi
	ldrh	r2, [r2]
	subs	r2, r4, r2
	muls	r2, r5, r2
	muls	r2, r3, r2
	muls	r6, r2, r6
	ldr	r2, .L449+60
	asrs	r6, r6, #11
	str	r6, [r2]
	ldr	r6, .L449+28
	ldrh	r0, [r6]
	lsls	r0, r0, #3
	bl	__aeabi_idiv
	uxth	r0, r0
	mov	r3, r6
	ldr	r6, .L449+64
	cmp	r0, #4
	itt	ls
	movls	r2, #4
	strhls	r2, [r6]	@ movhi
	ldr	r2, [sp, #4]
	it	hi
	strhhi	r0, [r6]	@ movhi
	cbz	r2, .L434
	mov	r2, #640
	strh	r2, [r3]	@ movhi
.L434:
	ldrh	r3, [r3]
	lsls	r4, r4, #6
	ldr	r2, .L449+68
	mov	r1, r5
	ldrh	r0, [r6]
	asrs	r3, r3, r7
	adds	r7, r7, #9
	asrs	r4, r4, r7
	ldr	r7, .L449+72
	adds	r3, r3, #2
	strh	r3, [r2]	@ movhi
	ldr	r3, .L449+76
	strh	r4, [r3]	@ movhi
	uxth	r4, r4
	mul	r3, r4, r5
	adds	r4, r4, #8
	str	r3, [r7]
	bl	__aeabi_uidiv
	uxtah	r0, r4, r0
	ldr	r4, .L449+80
	cmp	r5, #1
	ldr	r5, .L449+84
	it	eq
	addeq	r0, r0, #4
	str	r0, [r4]
	ldrh	r0, [r4]
	bl	FtlSysBlkNumInit
	ldr	r2, [r4]
	movs	r0, #24
	ldr	r3, .L449+88
	ldrb	r5, [r5]	@ zero_extendqisi2
	str	r2, [r3]
	ldr	r3, .L449+92
	ldr	r2, [r3]
	ldrh	r3, [fp]
	lsls	r2, r2, #2
	muls	r3, r2, r3
	ldrh	r2, [r10]
	adds	r2, r2, #9
	lsrs	r3, r3, r2
	ldr	r2, .L449+96
	adds	r3, r3, #2
	uxth	r3, r3
	strh	r3, [r2]	@ movhi
	ldr	r2, .L449+100
	strh	r0, [r2]	@ movhi
	movs	r0, #0
	ldr	r2, .L449+104
	str	r0, [r2]
	ldrh	r0, [r6]
	adds	r2, r0, #3
	strh	r2, [r6]	@ movhi
	ldr	r2, [r7]
	adds	r4, r2, #3
	str	r4, [r7]
	cbz	r5, .L437
	adds	r2, r2, #5
	adds	r0, r0, #4
	strh	r0, [r6]	@ movhi
.L448:
	str	r2, [r7]
.L438:
	ldr	r1, .L449+108
	movs	r2, #0
	strh	r2, [r1]	@ movhi
	ldr	r2, .L449+112
	ldrh	r0, [r2]
	lsrs	r2, r0, #3
	add	r2, r2, r0, lsl #1
	movs	r0, #0
	adds	r2, r2, #52
	add	r3, r2, r3, lsl #2
	ldrh	r2, [r8]
	cmp	r3, r2, lsl #9
	itt	cc
	movcc	r3, #1
	strhcc	r3, [r1]	@ movhi
	add	sp, sp, #24
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r10, fp, pc}
.L437:
	cmp	r4, #7
	bhi	.L438
	movs	r2, #8
	b	.L448
.L450:
	.align	2
.L449:
	.word	.LANCHOR44
	.word	.LANCHOR41
	.word	.LANCHOR46
	.word	.LANCHOR45
	.word	.LANCHOR47
	.word	.LANCHOR48
	.word	.LANCHOR49
	.word	.LANCHOR50
	.word	.LANCHOR2
	.word	.LANCHOR38
	.word	.LANCHOR51
	.word	.LANCHOR53
	.word	.LANCHOR54
	.word	.LANCHOR59
	.word	.LANCHOR43
	.word	.LANCHOR60
	.word	.LANCHOR61
	.word	.LANCHOR62
	.word	.LANCHOR64
	.word	.LANCHOR63
	.word	.LANCHOR37
	.word	.LANCHOR16
	.word	.LANCHOR65
	.word	.LANCHOR42
	.word	.LANCHOR66
	.word	.LANCHOR67
	.word	.LANCHOR68
	.word	.LANCHOR69
	.word	.LANCHOR40
	.word	.LANCHOR52
	.word	.LANCHOR55
	.word	.LANCHOR56
	.word	.LANCHOR57
	.word	.LANCHOR58
	.size	FtlConstantsInit, .-FtlConstantsInit
	.section	.text.IsBlkInVendorPart,"ax",%progbits
	.align	1
	.global	IsBlkInVendorPart
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	IsBlkInVendorPart, %function
IsBlkInVendorPart:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	ldr	r3, .L458
	ldrh	r3, [r3]
	cbz	r3, .L457
	ldr	r3, .L458+4
	ldr	r2, .L458+8
	ldr	r3, [r3]
	ldrh	r2, [r2]
	add	r2, r3, r2, lsl #1
.L453:
	cmp	r3, r2
	bne	.L454
.L457:
	movs	r0, #0
	bx	lr
.L454:
	ldrh	r1, [r3], #2
	cmp	r0, r1
	bne	.L453
	movs	r0, #1
	bx	lr
.L459:
	.align	2
.L458:
	.word	.LANCHOR70
	.word	.LANCHOR71
	.word	.LANCHOR61
	.size	IsBlkInVendorPart, .-IsBlkInVendorPart
	.section	.text.FtlCacheMetchLpa,"ax",%progbits
	.align	1
	.global	FtlCacheMetchLpa
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	FtlCacheMetchLpa, %function
FtlCacheMetchLpa:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	ldr	r3, .L468
	push	{r4, r5, r6, lr}
	ldr	r3, [r3]
	cbz	r3, .L467
	ldr	r2, .L468+4
	movs	r6, #36
	ldr	r5, [r2]
	movs	r2, #0
.L463:
	mla	r4, r6, r2, r5
	ldr	r4, [r4, #16]
	cmp	r4, r0
	bcc	.L462
	cmp	r4, r1
	bls	.L465
.L462:
	adds	r2, r2, #1
	cmp	r3, r2
	bne	.L463
.L467:
	movs	r0, #0
	pop	{r4, r5, r6, pc}
.L465:
	movs	r0, #1
	pop	{r4, r5, r6, pc}
.L469:
	.align	2
.L468:
	.word	.LANCHOR72
	.word	.LANCHOR73
	.size	FtlCacheMetchLpa, .-FtlCacheMetchLpa
	.section	.text.FtlGetCap,"ax",%progbits
	.align	1
	.global	FtlGetCap
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	FtlGetCap, %function
FtlGetCap:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	ldr	r3, .L471
	ldr	r0, [r3]
	bx	lr
.L472:
	.align	2
.L471:
	.word	.LANCHOR68
	.size	FtlGetCap, .-FtlGetCap
	.section	.text.FtlGetCapacity,"ax",%progbits
	.align	1
	.global	FtlGetCapacity
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	FtlGetCapacity, %function
FtlGetCapacity:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	ldr	r3, .L474
	ldr	r0, [r3]
	bx	lr
.L475:
	.align	2
.L474:
	.word	.LANCHOR68
	.size	FtlGetCapacity, .-FtlGetCapacity
	.section	.text.ftl_get_density,"ax",%progbits
	.align	1
	.global	ftl_get_density
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	ftl_get_density, %function
ftl_get_density:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	ldr	r3, .L477
	ldr	r0, [r3]
	bx	lr
.L478:
	.align	2
.L477:
	.word	.LANCHOR68
	.size	ftl_get_density, .-ftl_get_density
	.section	.text.FtlGetLpn,"ax",%progbits
	.align	1
	.global	FtlGetLpn
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	FtlGetLpn, %function
FtlGetLpn:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	ldr	r3, .L480
	ldr	r0, [r3]
	bx	lr
.L481:
	.align	2
.L480:
	.word	.LANCHOR74
	.size	FtlGetLpn, .-FtlGetLpn
	.section	.text.FtlGetCurEraseBlock,"ax",%progbits
	.align	1
	.global	FtlGetCurEraseBlock
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	FtlGetCurEraseBlock, %function
FtlGetCurEraseBlock:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	ldr	r2, .L483
	ldr	r3, .L483+4
	ldr	r0, [r2]
	ldrh	r3, [r3]
	muls	r0, r3, r0
	bx	lr
.L484:
	.align	2
.L483:
	.word	.LANCHOR75
	.word	.LANCHOR38
	.size	FtlGetCurEraseBlock, .-FtlGetCurEraseBlock
	.section	.text.FtlGetAllBlockNum,"ax",%progbits
	.align	1
	.global	FtlGetAllBlockNum
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	FtlGetAllBlockNum, %function
FtlGetAllBlockNum:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	ldr	r2, .L486
	ldr	r3, .L486+4
	ldrh	r0, [r2]
	ldrh	r3, [r3]
	muls	r0, r3, r0
	bx	lr
.L487:
	.align	2
.L486:
	.word	.LANCHOR38
	.word	.LANCHOR41
	.size	FtlGetAllBlockNum, .-FtlGetAllBlockNum
	.section	.text.FtlBbmMapBadBlock,"ax",%progbits
	.align	1
	.global	FtlBbmMapBadBlock
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	FtlBbmMapBadBlock, %function
FtlBbmMapBadBlock:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	ldr	r3, .L489
	push	{r0, r1, r2, r4, r5, r6, r7, lr}
	mov	r5, r0
	ldrh	r4, [r3]
	mov	r1, r4
	bl	__aeabi_uidiv
	mov	r1, r4
	ldr	r4, .L489+4
	uxth	r6, r0
	mov	r0, r5
	bl	__aeabi_uidivmod
	add	r2, r4, r6, lsl #2
	uxth	r3, r1
	ldr	r2, [r2, #28]
	lsrs	r1, r3, #5
	and	r7, r3, #31
	movs	r0, #1
	lsls	r0, r0, r7
	ldr	r7, [r2, r1, lsl #2]
	orrs	r0, r0, r7
	str	r0, [r2, r1, lsl #2]
	mov	r2, r6
	str	r0, [sp]
	mov	r1, r5
	ldr	r0, .L489+8
	bl	printf
	ldrh	r3, [r4, #6]
	movs	r0, #0
	adds	r3, r3, #1
	strh	r3, [r4, #6]	@ movhi
	add	sp, sp, #12
	@ sp needed
	pop	{r4, r5, r6, r7, pc}
.L490:
	.align	2
.L489:
	.word	.LANCHOR51
	.word	.LANCHOR76
	.word	.LC2
	.size	FtlBbmMapBadBlock, .-FtlBbmMapBadBlock
	.section	.text.FtlBbmIsBadBlock,"ax",%progbits
	.align	1
	.global	FtlBbmIsBadBlock
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	FtlBbmIsBadBlock, %function
FtlBbmIsBadBlock:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	ldr	r3, .L492
	push	{r4, r5, r6, lr}
	mov	r6, r0
	ldrh	r5, [r3]
	mov	r1, r5
	bl	__aeabi_uidivmod
	mov	r0, r6
	uxth	r4, r1
	mov	r1, r5
	bl	__aeabi_uidiv
	ldr	r3, .L492+4
	uxth	r0, r0
	lsrs	r2, r4, #5
	and	r4, r4, #31
	add	r0, r3, r0, lsl #2
	ldr	r3, [r0, #28]
	ldr	r0, [r3, r2, lsl #2]
	lsrs	r0, r0, r4
	and	r0, r0, #1
	pop	{r4, r5, r6, pc}
.L493:
	.align	2
.L492:
	.word	.LANCHOR51
	.word	.LANCHOR76
	.size	FtlBbmIsBadBlock, .-FtlBbmIsBadBlock
	.section	.text.FtlBbtInfoPrint,"ax",%progbits
	.align	1
	.global	FtlBbtInfoPrint
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	FtlBbtInfoPrint, %function
FtlBbtInfoPrint:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	bx	lr
	.size	FtlBbtInfoPrint, .-FtlBbtInfoPrint
	.section	.text.V2P_block,"ax",%progbits
	.align	1
	.global	V2P_block
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	V2P_block, %function
V2P_block:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r3, r4, r5, r6, r7, lr}
	mov	r5, r1
	ldr	r3, .L496
	mov	r7, r0
	ldrh	r6, [r3]
	mov	r1, r6
	bl	__aeabi_uidiv
	ldr	r3, .L496+4
	smulbb	r5, r6, r5
	mov	r1, r6
	ldrh	r4, [r3]
	smulbb	r4, r4, r0
	mov	r0, r7
	bl	__aeabi_uidivmod
	adds	r0, r5, r1
	add	r0, r0, r4
	uxth	r0, r0
	pop	{r3, r4, r5, r6, r7, pc}
.L497:
	.align	2
.L496:
	.word	.LANCHOR46
	.word	.LANCHOR51
	.size	V2P_block, .-V2P_block
	.section	.text.P2V_plane,"ax",%progbits
	.align	1
	.global	P2V_plane
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	P2V_plane, %function
P2V_plane:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	ldr	r3, .L499
	push	{r4, r5, r6, lr}
	mov	r6, r0
	ldrh	r5, [r3]
	ldr	r3, .L499+4
	ldrh	r1, [r3]
	bl	__aeabi_uidiv
	smulbb	r4, r0, r5
	mov	r1, r5
	mov	r0, r6
	bl	__aeabi_uidivmod
	add	r1, r1, r4
	uxth	r0, r1
	pop	{r4, r5, r6, pc}
.L500:
	.align	2
.L499:
	.word	.LANCHOR46
	.word	.LANCHOR51
	.size	P2V_plane, .-P2V_plane
	.section	.text.P2V_block_in_plane,"ax",%progbits
	.align	1
	.global	P2V_block_in_plane
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	P2V_block_in_plane, %function
P2V_block_in_plane:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r3, lr}
	ldr	r3, .L502
	ldrh	r1, [r3]
	bl	__aeabi_uidivmod
	ldr	r3, .L502+4
	uxth	r0, r1
	ldrh	r1, [r3]
	bl	__aeabi_uidiv
	uxth	r0, r0
	pop	{r3, pc}
.L503:
	.align	2
.L502:
	.word	.LANCHOR51
	.word	.LANCHOR46
	.size	P2V_block_in_plane, .-P2V_block_in_plane
	.section	.text.ftl_cmp_data_ver,"ax",%progbits
	.align	1
	.global	ftl_cmp_data_ver
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	ftl_cmp_data_ver, %function
ftl_cmp_data_ver:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	cmp	r0, r1
	bls	.L505
	subs	r0, r0, r1
	cmp	r0, #-2147483648
	ite	hi
	movhi	r0, #0
	movls	r0, #1
	bx	lr
.L505:
	subs	r0, r1, r0
	cmp	r0, #-2147483648
	ite	ls
	movls	r0, #0
	movhi	r0, #1
	bx	lr
	.size	ftl_cmp_data_ver, .-ftl_cmp_data_ver
	.section	.text.FtlFreeSysBlkQueueEmpty,"ax",%progbits
	.align	1
	.global	FtlFreeSysBlkQueueEmpty
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	FtlFreeSysBlkQueueEmpty, %function
FtlFreeSysBlkQueueEmpty:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	ldr	r3, .L508
	ldrh	r0, [r3, #6]
	clz	r0, r0
	lsrs	r0, r0, #5
	bx	lr
.L509:
	.align	2
.L508:
	.word	.LANCHOR77
	.size	FtlFreeSysBlkQueueEmpty, .-FtlFreeSysBlkQueueEmpty
	.section	.text.FtlFreeSysBlkQueueFull,"ax",%progbits
	.align	1
	.global	FtlFreeSysBlkQueueFull
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	FtlFreeSysBlkQueueFull, %function
FtlFreeSysBlkQueueFull:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	ldr	r3, .L511
	ldrh	r0, [r3, #6]
	sub	r3, r0, #1024
	rsbs	r0, r3, #0
	adcs	r0, r0, r3
	bx	lr
.L512:
	.align	2
.L511:
	.word	.LANCHOR77
	.size	FtlFreeSysBlkQueueFull, .-FtlFreeSysBlkQueueFull
	.section	.text.FtlFreeSysBlkQueueIn,"ax",%progbits
	.align	1
	.global	FtlFreeSysBlkQueueIn
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	FtlFreeSysBlkQueueIn, %function
FtlFreeSysBlkQueueIn:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	subs	r3, r0, #1
	movw	r2, #65533
	uxth	r3, r3
	push	{r4, r5, r6, lr}
	mov	r5, r0
	cmp	r3, r2
	bhi	.L513
	ldr	r4, .L522
	ldrh	r3, [r4, #6]
	cmp	r3, #1024
	beq	.L513
	cbz	r1, .L515
	ldr	r3, .L522+4
	ldr	r3, [r3]
	cbnz	r3, .L515
	bl	P2V_block_in_plane
	ldr	r3, .L522+8
	mov	r6, r0
	movs	r2, #1
	mov	r1, r2
	ldr	r0, [r3]
	lsls	r3, r5, #10
	str	r3, [r0, #4]
	bl	FlashEraseBlocks
	ldr	r3, .L522+12
	ldr	r2, [r3]
	ldrh	r3, [r2, r6, lsl #1]
	adds	r3, r3, #1
	strh	r3, [r2, r6, lsl #1]	@ movhi
	ldr	r2, .L522+16
	ldr	r3, [r2]
	adds	r3, r3, #1
	str	r3, [r2]
.L515:
	ldrh	r3, [r4, #6]
	adds	r3, r3, #1
	strh	r3, [r4, #6]	@ movhi
	ldrh	r3, [r4, #4]
	adds	r2, r3, #4
	adds	r3, r3, #1
	ubfx	r3, r3, #0, #10
	strh	r5, [r4, r2, lsl #1]	@ movhi
	strh	r3, [r4, #4]	@ movhi
.L513:
	pop	{r4, r5, r6, pc}
.L523:
	.align	2
.L522:
	.word	.LANCHOR77
	.word	.LANCHOR78
	.word	.LANCHOR79
	.word	.LANCHOR80
	.word	.LANCHOR81
	.size	FtlFreeSysBlkQueueIn, .-FtlFreeSysBlkQueueIn
	.section	.text.FtlFreeSysBLkSort,"ax",%progbits
	.align	1
	.global	FtlFreeSysBLkSort
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	FtlFreeSysBLkSort, %function
FtlFreeSysBLkSort:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	ldr	r3, .L533
	push	{r4, r5, r6, lr}
	ldrh	r2, [r3, #6]
	cbz	r2, .L524
	ldr	r2, .L533+4
	movs	r6, #0
	ldrh	r1, [r3, #2]
	mov	r5, r6
	ldrh	r4, [r2, #28]
	ldrh	r2, [r3, #4]
	and	r4, r4, #31
.L526:
	uxth	r0, r6
	adds	r6, r6, #1
	cmp	r4, r0
	bgt	.L527
	cbz	r5, .L524
	strh	r1, [r3, #2]	@ movhi
	strh	r2, [r3, #4]	@ movhi
.L524:
	pop	{r4, r5, r6, pc}
.L527:
	adds	r0, r1, #4
	adds	r1, r1, #1
	ldrh	r5, [r3, r0, lsl #1]
	adds	r0, r2, #4
	ubfx	r1, r1, #0, #10
	strh	r5, [r3, r0, lsl #1]	@ movhi
	movs	r5, #1
	add	r2, r2, r5
	ubfx	r2, r2, #0, #10
	b	.L526
.L534:
	.align	2
.L533:
	.word	.LANCHOR77
	.word	.LANCHOR82
	.size	FtlFreeSysBLkSort, .-FtlFreeSysBLkSort
	.section	.text.FtlFreeSysBlkQueueOut,"ax",%progbits
	.align	1
	.global	FtlFreeSysBlkQueueOut
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	FtlFreeSysBlkQueueOut, %function
FtlFreeSysBlkQueueOut:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r3, r4, r5, r6, r7, r8, r10, lr}
	ldr	r4, .L545
	mov	r6, r4
.L536:
	ldrh	r1, [r4, #6]
	cmp	r1, #0
	beq	.L537
	ldrh	r3, [r4, #2]
	subs	r1, r1, #1
	strh	r1, [r4, #6]	@ movhi
	adds	r2, r3, #4
	adds	r3, r3, #1
	ubfx	r3, r3, #0, #10
	ldrh	r5, [r4, r2, lsl #1]
	strh	r3, [r4, #2]	@ movhi
	ldr	r3, .L545+4
	ldr	r10, [r3]
	cmp	r10, #0
	bne	.L538
	ldr	r8, .L545+28
	mov	r0, r5
	bl	P2V_block_in_plane
	mov	r7, r0
	lsls	r3, r5, #10
	ldr	r0, [r8]
	str	r3, [r0, #4]
	ldr	r3, .L545+8
	ldrb	r3, [r3]	@ zero_extendqisi2
	cbz	r3, .L539
	movs	r2, #1
	mov	r1, r10
	bl	FlashEraseBlocks
.L539:
	movs	r2, #1
	ldr	r0, [r8]
	mov	r1, r2
	bl	FlashEraseBlocks
	ldr	r3, .L545+12
	ldr	r2, [r3]
	ldrh	r3, [r2, r7, lsl #1]
	adds	r3, r3, #1
	strh	r3, [r2, r7, lsl #1]	@ movhi
	ldr	r2, .L545+16
	ldr	r3, [r2]
	adds	r3, r3, #1
	str	r3, [r2]
.L538:
	subs	r3, r5, #1
	movw	r2, #65533
	uxth	r3, r3
	cmp	r3, r2
	bls	.L541
	ldrh	r2, [r6, #6]
	mov	r1, r5
	ldr	r0, .L545+20
	bl	printf
	b	.L536
.L537:
	ldr	r0, .L545+24
	bl	printf
.L540:
	b	.L540
.L541:
	mov	r0, r5
	pop	{r3, r4, r5, r6, r7, r8, r10, pc}
.L546:
	.align	2
.L545:
	.word	.LANCHOR77
	.word	.LANCHOR78
	.word	.LANCHOR16
	.word	.LANCHOR80
	.word	.LANCHOR81
	.word	.LC4
	.word	.LC3
	.word	.LANCHOR79
	.size	FtlFreeSysBlkQueueOut, .-FtlFreeSysBlkQueueOut
	.section	.text.test_node_in_list,"ax",%progbits
	.align	1
	.global	test_node_in_list
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	test_node_in_list, %function
test_node_in_list:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	ldr	r3, .L552
	push	{r4, r5, lr}
	movw	r5, #65535
	ldr	r2, [r0]
	ldr	r4, [r3]
	subs	r3, r2, r4
	asrs	r0, r3, #1
	ldr	r3, .L552+4
	muls	r3, r0, r3
	movs	r0, #6
	uxth	r3, r3
.L549:
	cmp	r3, r1
	beq	.L550
	ldrh	r3, [r2]
	cmp	r3, r5
	beq	.L551
	mla	r2, r0, r3, r4
	b	.L549
.L550:
	movs	r0, #1
	pop	{r4, r5, pc}
.L551:
	movs	r0, #0
	pop	{r4, r5, pc}
.L553:
	.align	2
.L552:
	.word	.LANCHOR83
	.word	-1431655765
	.size	test_node_in_list, .-test_node_in_list
	.section	.text.insert_data_list,"ax",%progbits
	.align	1
	.global	insert_data_list
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	insert_data_list, %function
insert_data_list:
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r0, r1, r2, r3, r4, r5, r6, r7, r8, r10, fp, lr}
	ldr	r3, .L570
	ldrh	lr, [r3]
	cmp	lr, r0
	bls	.L556
	ldr	r3, .L570+4
	movs	r5, #6
	ldr	r4, [r3]
	mul	r3, r5, r0
	str	r3, [sp, #4]
	adds	r1, r4, r3
	ldr	r2, [sp, #4]
	movw	r3, #65535
	strh	r3, [r1, #2]	@ movhi
	strh	r3, [r4, r2]	@ movhi
	ldr	r3, .L570+8
	ldr	ip, [r3]
	cmp	ip, #0
	bne	.L557
.L569:
	str	r1, [r3]
.L556:
	movs	r0, #0
	add	sp, sp, #16
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r10, fp, pc}
.L557:
	ldr	r3, .L570+12
	lsls	r2, r0, #1
	ldr	r3, [r3]
	str	r3, [sp, #8]
	ldrh	r6, [r3, r0, lsl #1]
	ldrh	r3, [r1, #4]
	cbz	r3, .L567
	mul	fp, r3, r6
.L558:
	sub	r3, ip, r4
	asrs	r6, r3, #1
	ldr	r3, .L570+16
	muls	r3, r6, r3
	ldr	r6, .L570+20
	ldr	r8, [r6]
	movs	r6, #0
	uxth	r3, r3
	add	r2, r8, r2
	str	r2, [sp, #12]
	mov	r2, ip
.L565:
	adds	r6, r6, #1
	uxth	r6, r6
	cmp	lr, r6
	bcc	.L556
	cmp	r3, r0
	beq	.L556
	ldr	r7, [sp, #8]
	lsl	r10, r3, #1
	ldrh	r7, [r7, r3, lsl #1]
	mov	r5, r7
	ldrh	r7, [r2, #4]
	cbz	r7, .L568
	muls	r7, r5, r7
.L560:
	cmp	fp, r7
	bne	.L561
	ldr	r5, [sp, #12]
	ldrh	r10, [r8, r10]
	ldrh	r7, [r5]
	cmp	r10, r7
	bcc	.L563
.L562:
	ldr	r5, [sp, #4]
	cmp	r2, ip
	strh	r3, [r4, r5]	@ movhi
	ldrh	r3, [r2, #2]
	strh	r3, [r1, #2]	@ movhi
	bne	.L566
	strh	r0, [r2, #2]	@ movhi
	ldr	r3, .L570+8
	b	.L569
.L567:
	mov	fp, #-1
	b	.L558
.L568:
	mov	r7, #-1
	b	.L560
.L561:
	bcc	.L562
.L563:
	ldrh	r7, [r2]
	movw	r5, #65535
	cmp	r7, r5
	bne	.L564
	strh	r3, [r1, #2]	@ movhi
	strh	r0, [r2]	@ movhi
	ldr	r3, .L570+24
	b	.L569
.L564:
	movs	r3, #6
	mla	r2, r3, r7, r4
	mov	r3, r7
	b	.L565
.L566:
	ldrh	r1, [r2, #2]
	movs	r3, #6
	muls	r3, r1, r3
	strh	r0, [r4, r3]	@ movhi
	strh	r0, [r2, #2]	@ movhi
	b	.L556
.L571:
	.align	2
.L570:
	.word	.LANCHOR40
	.word	.LANCHOR83
	.word	.LANCHOR84
	.word	.LANCHOR85
	.word	-1431655765
	.word	.LANCHOR80
	.word	.LANCHOR86
	.size	insert_data_list, .-insert_data_list
	.section	.text.INSERT_DATA_LIST,"ax",%progbits
	.align	1
	.global	INSERT_DATA_LIST
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	INSERT_DATA_LIST, %function
INSERT_DATA_LIST:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r3, lr}
	bl	insert_data_list
	ldr	r2, .L574
	ldrh	r3, [r2]
	adds	r3, r3, #1
	uxth	r3, r3
	strh	r3, [r2]	@ movhi
	ldr	r2, .L574+4
	ldrh	r2, [r2]
	cmp	r2, r3
	bcs	.L572
	ldr	r1, .L574+8
	movs	r2, #245
	ldr	r0, .L574+12
	bl	printf
	ldr	r1, .L574+16
	ldr	r0, .L574+20
	pop	{r3, lr}
	b	printf
.L572:
	pop	{r3, pc}
.L575:
	.align	2
.L574:
	.word	.LANCHOR87
	.word	.LANCHOR40
	.word	.LANCHOR88
	.word	.LC5
	.word	.LC6
	.word	.LC7
	.size	INSERT_DATA_LIST, .-INSERT_DATA_LIST
	.section	.text.insert_free_list,"ax",%progbits
	.align	1
	.global	insert_free_list
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	insert_free_list, %function
insert_free_list:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	movw	r1, #65535
	push	{r4, r5, r6, r7, r8, r10, fp, lr}
	cmp	r0, r1
	beq	.L577
	ldr	r3, .L583
	mov	r10, #6
	mul	r7, r10, r0
	ldr	r4, [r3]
	ldr	r3, .L583+4
	adds	r5, r4, r7
	ldr	r6, [r3]
	mov	lr, r3
	strh	r1, [r5, #2]	@ movhi
	strh	r1, [r4, r7]	@ movhi
	cbnz	r6, .L578
	str	r5, [r3]
.L577:
	movs	r0, #0
	pop	{r4, r5, r6, r7, r8, r10, fp, pc}
.L578:
	ldr	r3, .L583+8
	subs	r2, r6, r4
	mov	fp, r1
	ldr	ip, [r3]
	asrs	r3, r2, #1
	ldr	r2, .L583+12
	ldrh	r8, [ip, r0, lsl #1]
	muls	r2, r3, r2
	mov	r3, r6
	uxth	r2, r2
.L581:
	ldrh	r1, [ip, r2, lsl #1]
	cmp	r1, r8
	bcs	.L579
	ldrh	r1, [r3]
	cmp	r1, fp
	bne	.L580
	strh	r2, [r5, #2]	@ movhi
	strh	r0, [r3]	@ movhi
	b	.L577
.L580:
	mla	r3, r10, r1, r4
	mov	r2, r1
	b	.L581
.L579:
	ldrh	r1, [r3, #2]
	cmp	r3, r6
	strh	r1, [r5, #2]	@ movhi
	it	ne
	ldrhne	r1, [r3, #2]
	strh	r2, [r4, r7]	@ movhi
	iteet	ne
	movne	r2, #6
	strheq	r0, [r3, #2]	@ movhi
	streq	r5, [lr]
	mulne	r2, r2, r1
	itt	ne
	strhne	r0, [r4, r2]	@ movhi
	strhne	r0, [r3, #2]	@ movhi
	b	.L577
.L584:
	.align	2
.L583:
	.word	.LANCHOR83
	.word	.LANCHOR89
	.word	.LANCHOR80
	.word	-1431655765
	.size	insert_free_list, .-insert_free_list
	.section	.text.INSERT_FREE_LIST,"ax",%progbits
	.align	1
	.global	INSERT_FREE_LIST
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	INSERT_FREE_LIST, %function
INSERT_FREE_LIST:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r3, lr}
	bl	insert_free_list
	ldr	r2, .L587
	ldrh	r3, [r2]
	adds	r3, r3, #1
	uxth	r3, r3
	strh	r3, [r2]	@ movhi
	ldr	r2, .L587+4
	ldrh	r2, [r2]
	cmp	r2, r3
	bcs	.L585
	ldr	r1, .L587+8
	movs	r2, #238
	ldr	r0, .L587+12
	bl	printf
	ldr	r1, .L587+16
	ldr	r0, .L587+20
	pop	{r3, lr}
	b	printf
.L585:
	pop	{r3, pc}
.L588:
	.align	2
.L587:
	.word	.LANCHOR90
	.word	.LANCHOR40
	.word	.LANCHOR91
	.word	.LC5
	.word	.LC6
	.word	.LC7
	.size	INSERT_FREE_LIST, .-INSERT_FREE_LIST
	.section	.text.List_remove_node,"ax",%progbits
	.align	1
	.global	List_remove_node
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	List_remove_node, %function
List_remove_node:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, r8, lr}
	movs	r6, #6
	ldr	r5, .L595
	muls	r6, r1, r6
	movw	r3, #65535
	mov	r8, r0
	ldr	r7, [r5]
	adds	r4, r7, r6
	ldrh	r2, [r4, #2]
	cmp	r2, r3
	bne	.L590
	ldr	r3, [r0]
	cmp	r4, r3
	beq	.L590
	ldr	r1, .L595+4
	movw	r2, #435
	ldr	r0, .L595+8
	bl	printf
	ldr	r1, .L595+12
	ldr	r0, .L595+16
	bl	printf
.L590:
	ldr	r3, [r8]
	movw	r1, #65535
	cmp	r4, r3
	ldrh	r3, [r7, r6]
	bne	.L591
	cmp	r3, r1
	ittee	ne
	ldrne	r0, [r5]
	movne	r2, #6
	moveq	r3, #0
	streq	r3, [r8]
	ittt	ne
	mlane	r3, r2, r3, r0
	strne	r3, [r8]
	strhne	r1, [r3, #2]	@ movhi
.L593:
	movw	r3, #65535
	movs	r0, #0
	strh	r3, [r7, r6]	@ movhi
	strh	r3, [r4, #2]	@ movhi
	pop	{r4, r5, r6, r7, r8, pc}
.L591:
	cmp	r3, r1
	ldrh	r1, [r4, #2]
	bne	.L594
	cmp	r1, r3
	beq	.L593
	movs	r2, #6
	ldr	r0, [r5]
	muls	r1, r2, r1
	strh	r3, [r0, r1]	@ movhi
	b	.L593
.L594:
	ldr	r0, [r5]
	movs	r2, #6
	mla	r5, r2, r3, r0
	strh	r1, [r5, #2]	@ movhi
	ldrh	r1, [r4, #2]
	muls	r2, r1, r2
	strh	r3, [r0, r2]	@ movhi
	b	.L593
.L596:
	.align	2
.L595:
	.word	.LANCHOR83
	.word	.LANCHOR92
	.word	.LC5
	.word	.LC6
	.word	.LC7
	.size	List_remove_node, .-List_remove_node
	.section	.text.List_pop_index_node,"ax",%progbits
	.align	1
	.global	List_pop_index_node
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	List_pop_index_node, %function
List_pop_index_node:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	ldr	r3, [r0]
	push	{r4, r5, r6, lr}
	cbz	r3, .L603
	ldr	r2, .L604
	movw	r5, #65535
	movs	r6, #6
	ldr	r2, [r2]
.L599:
	cbnz	r1, .L600
.L602:
	ldr	r4, .L604+4
	subs	r3, r3, r2
	asrs	r3, r3, #1
	muls	r4, r3, r4
	uxth	r1, r4
	bl	List_remove_node
	uxth	r0, r4
	pop	{r4, r5, r6, pc}
.L600:
	ldrh	r4, [r3]
	cmp	r4, r5
	beq	.L602
	subs	r1, r1, #1
	mla	r3, r6, r4, r2
	uxth	r1, r1
	b	.L599
.L603:
	movw	r0, #65535
	pop	{r4, r5, r6, pc}
.L605:
	.align	2
.L604:
	.word	.LANCHOR83
	.word	-1431655765
	.size	List_pop_index_node, .-List_pop_index_node
	.section	.text.List_get_gc_head_node,"ax",%progbits
	.align	1
	.global	List_get_gc_head_node
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	List_get_gc_head_node, %function
List_get_gc_head_node:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	ldr	r3, .L612
	push	{r4, lr}
	ldr	r3, [r3]
	cbz	r3, .L611
	ldr	r2, .L612+4
	movs	r4, #6
	ldr	r1, [r2]
	movw	r2, #65535
.L608:
	cbz	r0, .L609
	ldrh	r3, [r3]
	cmp	r3, r2
	bne	.L610
.L611:
	movw	r0, #65535
	pop	{r4, pc}
.L610:
	subs	r0, r0, #1
	mla	r3, r4, r3, r1
	uxth	r0, r0
	b	.L608
.L609:
	ldr	r0, .L612+8
	subs	r3, r3, r1
	asrs	r3, r3, #1
	muls	r3, r0, r3
	uxth	r0, r3
	pop	{r4, pc}
.L613:
	.align	2
.L612:
	.word	.LANCHOR84
	.word	.LANCHOR83
	.word	-1431655765
	.size	List_get_gc_head_node, .-List_get_gc_head_node
	.section	.text.List_update_data_list,"ax",%progbits
	.align	1
	.global	List_update_data_list
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	List_update_data_list, %function
List_update_data_list:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	ldr	r3, .L625
	push	{r4, r5, r6, r7, r8, r10, fp, lr}
	mov	r4, r0
	ldrh	r3, [r3]
	cmp	r3, r0
	beq	.L616
	ldr	r3, .L625+4
	ldrh	r3, [r3]
	cmp	r3, r0
	beq	.L616
	ldr	r3, .L625+8
	ldrh	r3, [r3]
	cmp	r3, r0
	beq	.L616
	ldr	r7, .L625+12
	movs	r6, #6
	ldr	r3, .L625+16
	muls	r6, r0, r6
	ldr	fp, [r7]
	ldr	r3, [r3]
	add	r10, fp, r6
	cmp	r10, r3
	beq	.L616
	ldr	r3, .L625+20
	ldrh	r5, [r10, #4]
	ldr	r2, [r3]
	mov	r8, r3
	ldrh	r2, [r2, r0, lsl #1]
	cmp	r5, #0
	beq	.L623
	muls	r5, r2, r5
.L618:
	ldrh	r3, [r10, #2]
	movw	r2, #65535
	cmp	r3, r2
	bne	.L619
	ldrh	r2, [fp, r6]
	cmp	r2, r3
	bne	.L619
	ldr	r1, .L625+24
	movw	r2, #571
	ldr	r0, .L625+28
	bl	printf
	ldr	r1, .L625+32
	ldr	r0, .L625+36
	bl	printf
.L619:
	ldrh	r3, [r10, #2]
	movw	r2, #65535
	cmp	r3, r2
	bne	.L620
	ldrh	r2, [fp, r6]
	cmp	r2, r3
	beq	.L616
.L620:
	movs	r2, #6
	muls	r2, r3, r2
	ldr	r3, .L625+40
	asrs	r1, r2, #1
	muls	r3, r1, r3
	ldr	r1, [r8]
	ldrh	r0, [r1, r3, lsl #1]
	ldr	r1, [r7]
	add	r2, r2, r1
	ldrh	r3, [r2, #4]
	cbz	r3, .L624
	muls	r3, r0, r3
.L621:
	cmp	r5, r3
	bcs	.L616
	ldr	r5, .L625+44
	mov	r1, r4
	ldr	r0, .L625+16
	bl	List_remove_node
	ldrh	r3, [r5]
	cbnz	r3, .L622
	ldr	r1, .L625+24
	movw	r2, #585
	ldr	r0, .L625+28
	bl	printf
	ldr	r1, .L625+32
	ldr	r0, .L625+36
	bl	printf
.L622:
	ldrh	r3, [r5]
	mov	r0, r4
	subs	r3, r3, #1
	strh	r3, [r5]	@ movhi
	bl	INSERT_DATA_LIST
.L616:
	movs	r0, #0
	pop	{r4, r5, r6, r7, r8, r10, fp, pc}
.L623:
	mov	r5, #-1
	b	.L618
.L624:
	mov	r3, #-1
	b	.L621
.L626:
	.align	2
.L625:
	.word	.LANCHOR93
	.word	.LANCHOR94
	.word	.LANCHOR95
	.word	.LANCHOR83
	.word	.LANCHOR84
	.word	.LANCHOR85
	.word	.LANCHOR96
	.word	.LC5
	.word	.LC6
	.word	.LC7
	.word	-1431655765
	.word	.LANCHOR87
	.size	List_update_data_list, .-List_update_data_list
	.section	.text.ftl_map_blk_alloc_new_blk,"ax",%progbits
	.align	1
	.global	ftl_map_blk_alloc_new_blk
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	ftl_map_blk_alloc_new_blk, %function
ftl_map_blk_alloc_new_blk:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	ldrh	r1, [r0, #10]
	ldr	r2, [r0, #12]
	push	{r3, r4, r5, r6, r7, lr}
	mov	r4, r0
	movs	r3, #0
.L628:
	uxth	r5, r3
	cmp	r5, r1
	bcs	.L631
	mov	r7, r2
	adds	r3, r3, #1
	ldrh	r6, [r7]
	adds	r2, r2, #2
	cmp	r6, #0
	bne	.L628
	bl	FtlFreeSysBlkQueueOut
	subs	r3, r0, #1
	movw	r2, #65533
	uxth	r3, r3
	mov	r1, r0
	strh	r0, [r7]	@ movhi
	cmp	r3, r2
	bls	.L629
	ldr	r3, .L635
	ldr	r0, .L635+4
	ldrh	r2, [r3, #6]
	bl	printf
.L630:
	b	.L630
.L629:
	ldr	r3, [r4, #28]
	strh	r6, [r4, #2]	@ movhi
	strh	r5, [r4]	@ movhi
	adds	r3, r3, #1
	str	r3, [r4, #28]
	ldrh	r3, [r4, #8]
	adds	r3, r3, #1
	strh	r3, [r4, #8]	@ movhi
.L631:
	ldrh	r3, [r4, #10]
	cmp	r3, r5
	bhi	.L633
	ldr	r1, .L635+8
	movw	r2, #715
	ldr	r0, .L635+12
	bl	printf
	ldr	r1, .L635+16
	ldr	r0, .L635+20
	bl	printf
.L633:
	movs	r0, #0
	pop	{r3, r4, r5, r6, r7, pc}
.L636:
	.align	2
.L635:
	.word	.LANCHOR77
	.word	.LC8
	.word	.LANCHOR97
	.word	.LC5
	.word	.LC6
	.word	.LC7
	.size	ftl_map_blk_alloc_new_blk, .-ftl_map_blk_alloc_new_blk
	.section	.text.select_l2p_ram_region,"ax",%progbits
	.align	1
	.global	select_l2p_ram_region
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	select_l2p_ram_region, %function
select_l2p_ram_region:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r3, r4, r5, r6, r7, lr}
	movs	r1, #0
	ldr	r3, .L647
	movs	r0, #12
	movw	r5, #65535
	ldrh	r2, [r3]
	ldr	r3, .L647+4
	ldr	r3, [r3]
.L638:
	uxth	r4, r1
	cmp	r4, r2
	bcc	.L640
	mov	r4, r2
	movs	r1, #0
	mov	r6, #-2147483648
	movs	r7, #12
.L641:
	uxth	r5, r1
	cmp	r5, r2
	bcc	.L643
	cmp	r4, r2
	bcc	.L639
	ldr	r1, .L647+8
	mov	r4, r2
	mov	r0, #-1
	ldrh	r7, [r1]
	movs	r1, #0
.L644:
	uxth	r5, r1
	cmp	r5, r2
	bcc	.L646
	cmp	r4, r2
	bcc	.L639
	movw	r2, #977
	ldr	r1, .L647+12
	ldr	r0, .L647+16
	bl	printf
	ldr	r1, .L647+20
	ldr	r0, .L647+24
	bl	printf
	b	.L639
.L640:
	adds	r1, r1, #1
	mla	r6, r0, r1, r3
	ldrh	r6, [r6, #-12]
	cmp	r6, r5
	bne	.L638
.L639:
	mov	r0, r4
	pop	{r3, r4, r5, r6, r7, pc}
.L643:
	mla	r0, r7, r1, r3
	ldr	r0, [r0, #4]
	cmp	r0, #0
	blt	.L642
	cmp	r6, r0
	itt	hi
	movhi	r6, r0
	movhi	r4, r5
.L642:
	adds	r1, r1, #1
	b	.L641
.L646:
	ldr	r6, [r3, #4]
	cmp	r0, r6
	bls	.L645
	ldrh	ip, [r3]
	cmp	ip, r7
	itt	ne
	movne	r0, r6
	movne	r4, r5
.L645:
	adds	r1, r1, #1
	adds	r3, r3, #12
	b	.L644
.L648:
	.align	2
.L647:
	.word	.LANCHOR67
	.word	.LANCHOR98
	.word	.LANCHOR99
	.word	.LANCHOR100
	.word	.LC5
	.word	.LC6
	.word	.LC7
	.size	select_l2p_ram_region, .-select_l2p_ram_region
	.section	.text.FtlUpdateVaildLpn,"ax",%progbits
	.align	1
	.global	FtlUpdateVaildLpn
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	FtlUpdateVaildLpn, %function
FtlUpdateVaildLpn:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	ldr	r2, .L659
	push	{r4, r5, r6, lr}
	mov	r1, r2
	ldrh	r3, [r2]
	cmp	r3, #4
	bhi	.L650
	cbnz	r0, .L650
	adds	r3, r3, #1
	strh	r3, [r2]	@ movhi
	pop	{r4, r5, r6, pc}
.L650:
	movs	r3, #0
	ldr	r0, .L659+4
	strh	r3, [r1]	@ movhi
	movw	r6, #65535
	ldr	r1, .L659+8
	ldrh	r4, [r0]
	mov	r0, r3
	ldr	r2, .L659+12
	ldr	r1, [r1]
	str	r3, [r2]
	add	r4, r1, r4, lsl #1
.L651:
	cmp	r1, r4
	bne	.L653
	cbz	r3, .L649
	str	r0, [r2]
.L649:
	pop	{r4, r5, r6, pc}
.L653:
	ldrh	r5, [r1], #2
	cmp	r5, r6
	itt	ne
	addne	r0, r0, r5
	movne	r3, #1
	b	.L651
.L660:
	.align	2
.L659:
	.word	.LANCHOR101
	.word	.LANCHOR40
	.word	.LANCHOR85
	.word	.LANCHOR102
	.size	FtlUpdateVaildLpn, .-FtlUpdateVaildLpn
	.section	.text.ftl_set_blk_mode,"ax",%progbits
	.align	1
	.global	ftl_set_blk_mode
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	ftl_set_blk_mode, %function
ftl_set_blk_mode:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	mov	r3, r0
	cbz	r1, .L662
	b	ftl_set_blk_mode.part.11
.L662:
	ldr	r2, .L663
	lsrs	r0, r0, #5
	and	r3, r3, #31
	ldr	r1, [r2]
	movs	r2, #1
	lsl	r3, r2, r3
	ldr	r2, [r1, r0, lsl #2]
	bic	r2, r2, r3
	str	r2, [r1, r0, lsl #2]
	bx	lr
.L664:
	.align	2
.L663:
	.word	.LANCHOR1
	.size	ftl_set_blk_mode, .-ftl_set_blk_mode
	.section	.text.ftl_get_blk_mode,"ax",%progbits
	.align	1
	.global	ftl_get_blk_mode
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	ftl_get_blk_mode, %function
ftl_get_blk_mode:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	ldr	r3, .L666
	lsrs	r2, r0, #5
	and	r0, r0, #31
	ldr	r3, [r3]
	ldr	r3, [r3, r2, lsl #2]
	lsr	r0, r3, r0
	and	r0, r0, #1
	bx	lr
.L667:
	.align	2
.L666:
	.word	.LANCHOR1
	.size	ftl_get_blk_mode, .-ftl_get_blk_mode
	.section	.text.ftl_sb_update_avl_pages,"ax",%progbits
	.align	1
	.global	ftl_sb_update_avl_pages
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	ftl_sb_update_avl_pages, %function
ftl_sb_update_avl_pages:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	movs	r3, #0
	push	{r4, r5, r6, lr}
	strh	r3, [r0, #4]	@ movhi
	movw	r6, #65535
	ldr	r3, .L675
	ldrh	r4, [r3]
	add	r3, r0, r2, lsl #1
	adds	r3, r3, #14
.L669:
	cmp	r2, r4
	bcc	.L671
	ldr	r3, .L675+4
	add	r5, r0, #16
	movw	r6, #65535
	ldrh	r3, [r3]
	subs	r3, r3, #1
	subs	r1, r3, r1
	movs	r3, #0
	uxth	r1, r1
.L672:
	uxth	r2, r3
	cmp	r4, r2
	bhi	.L674
	pop	{r4, r5, r6, pc}
.L671:
	ldrh	r5, [r3, #2]!
	adds	r2, r2, #1
	uxth	r2, r2
	cmp	r5, r6
	ittt	ne
	ldrhne	r5, [r0, #4]
	addne	r5, r5, #1
	strhne	r5, [r0, #4]	@ movhi
	b	.L669
.L674:
	ldrh	r2, [r5], #2
	adds	r3, r3, #1
	cmp	r2, r6
	ittt	ne
	ldrhne	r2, [r0, #4]
	addne	r2, r2, r1
	strhne	r2, [r0, #4]	@ movhi
	b	.L672
.L676:
	.align	2
.L675:
	.word	.LANCHOR38
	.word	.LANCHOR52
	.size	ftl_sb_update_avl_pages, .-ftl_sb_update_avl_pages
	.section	.text.make_superblock,"ax",%progbits
	.align	1
	.global	make_superblock
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	make_superblock, %function
make_superblock:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	ldr	r3, .L690
	ldrh	r2, [r0]
	push	{r4, r5, r6, r7, r8, r10, fp, lr}
	mov	r4, r0
	ldrh	r3, [r3]
	cmp	r2, r3
	bcc	.L678
	ldr	r1, .L690+4
	movw	r2, #2819
	ldr	r0, .L690+8
	bl	printf
	ldr	r1, .L690+12
	ldr	r0, .L690+16
	bl	printf
.L678:
	ldr	r3, .L690+20
	add	r6, r4, #16
	ldr	r10, .L690+40
	movw	r7, #65535
	movs	r5, #0
	ldrh	r8, [r3]
	strh	r5, [r4, #4]	@ movhi
	strb	r5, [r4, #7]
.L679:
	uxth	r3, r5
	cmp	r8, r3
	bhi	.L681
	ldr	r2, .L690+24
	ldrb	r3, [r4, #7]	@ zero_extendqisi2
	ldrh	r2, [r2]
	smulbb	r3, r3, r2
	strh	r3, [r4, #4]	@ movhi
	movs	r3, #0
	strb	r3, [r4, #9]
	ldr	r3, .L690+28
	ldr	r3, [r3]
	cbz	r3, .L682
	ldr	r3, .L690+32
	ldrh	r2, [r4]
	ldr	r3, [r3]
	ldrh	r3, [r3, r2, lsl #1]
	cmp	r3, #79
	itt	ls
	movls	r3, #1
	strbls	r3, [r4, #9]
.L682:
	ldr	r3, .L690+36
	ldrb	r3, [r3]	@ zero_extendqisi2
	cbz	r3, .L683
	movs	r3, #1
	strb	r3, [r4, #9]
.L683:
	movs	r0, #0
	pop	{r4, r5, r6, r7, r8, r10, fp, pc}
.L681:
	ldrh	r1, [r4]
	ldrb	r0, [r10, r5]	@ zero_extendqisi2
	bl	V2P_block
	strh	r7, [r6]	@ movhi
	mov	fp, r0
	bl	FtlBbmIsBadBlock
	cbnz	r0, .L680
	strh	fp, [r6]	@ movhi
	ldrb	r3, [r4, #7]	@ zero_extendqisi2
	adds	r3, r3, #1
	strb	r3, [r4, #7]
.L680:
	adds	r5, r5, #1
	adds	r6, r6, #2
	b	.L679
.L691:
	.align	2
.L690:
	.word	.LANCHOR40
	.word	.LANCHOR103
	.word	.LC5
	.word	.LC6
	.word	.LC7
	.word	.LANCHOR38
	.word	.LANCHOR52
	.word	.LANCHOR104
	.word	.LANCHOR80
	.word	.LANCHOR2
	.word	.LANCHOR47
	.size	make_superblock, .-make_superblock
	.section	.text.update_multiplier_value,"ax",%progbits
	.align	1
	.global	update_multiplier_value
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	update_multiplier_value, %function
update_multiplier_value:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r3, r4, r5, r6, r7, r8, r10, lr}
	movs	r5, #0
	ldr	r3, .L698
	mov	r6, r0
	mov	r4, r5
	ldr	r10, .L698+12
	ldrh	r7, [r3]
	ldr	r3, .L698+4
	ldrh	r8, [r3]
.L693:
	uxth	r3, r5
	cmp	r7, r3
	bhi	.L695
	cbz	r4, .L697
	mov	r1, r4
	mov	r0, #32768
	bl	__aeabi_idiv
.L696:
	ldr	r3, .L698+8
	movs	r2, #6
	ldr	r3, [r3]
	mla	r6, r2, r6, r3
	strh	r0, [r6, #4]	@ movhi
	movs	r0, #0
	pop	{r3, r4, r5, r6, r7, r8, r10, pc}
.L695:
	mov	r1, r6
	ldrb	r0, [r10, r5]	@ zero_extendqisi2
	bl	V2P_block
	bl	FtlBbmIsBadBlock
	cbnz	r0, .L694
	add	r4, r4, r8
	uxth	r4, r4
.L694:
	adds	r5, r5, #1
	b	.L693
.L697:
	mov	r0, r4
	b	.L696
.L699:
	.align	2
.L698:
	.word	.LANCHOR38
	.word	.LANCHOR52
	.word	.LANCHOR83
	.word	.LANCHOR47
	.size	update_multiplier_value, .-update_multiplier_value
	.section	.text.GetFreeBlockMinEraseCount,"ax",%progbits
	.align	1
	.global	GetFreeBlockMinEraseCount
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	GetFreeBlockMinEraseCount, %function
GetFreeBlockMinEraseCount:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	ldr	r3, .L703
	ldr	r0, [r3]
	cbz	r0, .L701
	ldr	r3, .L703+4
	ldr	r3, [r3]
	subs	r0, r0, r3
	ldr	r3, .L703+8
	asrs	r0, r0, #1
	muls	r0, r3, r0
	ldr	r3, .L703+12
	ldr	r3, [r3]
	uxth	r0, r0
	ldrh	r0, [r3, r0, lsl #1]
.L701:
	bx	lr
.L704:
	.align	2
.L703:
	.word	.LANCHOR89
	.word	.LANCHOR83
	.word	-1431655765
	.word	.LANCHOR80
	.size	GetFreeBlockMinEraseCount, .-GetFreeBlockMinEraseCount
	.section	.text.GetFreeBlockMaxEraseCount,"ax",%progbits
	.align	1
	.global	GetFreeBlockMaxEraseCount
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	GetFreeBlockMaxEraseCount, %function
GetFreeBlockMaxEraseCount:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	ldr	r3, .L713
	push	{r4, r5, r6, lr}
	ldr	r3, [r3]
	cbz	r3, .L711
	ldr	r2, .L713+4
	movs	r5, #6
	movw	r6, #65535
	ldrh	r2, [r2]
	rsb	r2, r2, r2, lsl #3
	asrs	r2, r2, #3
	cmp	r0, r2
	it	gt
	uxthgt	r0, r2
	ldr	r2, .L713+8
	ldr	r1, [r2]
	ldr	r2, .L713+12
	subs	r3, r3, r1
	asrs	r3, r3, #1
	muls	r3, r2, r3
	movs	r2, #0
	uxth	r3, r3
.L708:
	uxth	r4, r2
	cmp	r0, r4
	bls	.L710
	mul	r4, r5, r3
	adds	r2, r2, #1
	ldrh	r4, [r1, r4]
	cmp	r4, r6
	bne	.L712
.L710:
	ldr	r2, .L713+16
	ldr	r2, [r2]
	ldrh	r0, [r2, r3, lsl #1]
	pop	{r4, r5, r6, pc}
.L712:
	mov	r3, r4
	b	.L708
.L711:
	mov	r0, r3
	pop	{r4, r5, r6, pc}
.L714:
	.align	2
.L713:
	.word	.LANCHOR89
	.word	.LANCHOR90
	.word	.LANCHOR83
	.word	-1431655765
	.word	.LANCHOR80
	.size	GetFreeBlockMaxEraseCount, .-GetFreeBlockMaxEraseCount
	.section	.text.free_data_superblock,"ax",%progbits
	.align	1
	.global	free_data_superblock
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	free_data_superblock, %function
free_data_superblock:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	movw	r2, #65535
	push	{r3, lr}
	cmp	r0, r2
	beq	.L716
	ldr	r2, .L717
	movs	r1, #0
	ldr	r2, [r2]
	strh	r1, [r2, r0, lsl #1]	@ movhi
	bl	INSERT_FREE_LIST
.L716:
	movs	r0, #0
	pop	{r3, pc}
.L718:
	.align	2
.L717:
	.word	.LANCHOR85
	.size	free_data_superblock, .-free_data_superblock
	.section	.text.FtlGcBufInit,"ax",%progbits
	.align	1
	.global	FtlGcBufInit
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	FtlGcBufInit, %function
FtlGcBufInit:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r0, r1, r4, r5, r6, r7, r8, r10, fp, lr}
	movs	r3, #0
	ldr	r1, .L724
	mov	fp, #1
	ldr	r2, .L724+4
	ldr	r5, [r1]
	ldr	r1, .L724+8
	str	r3, [r2]
	ldr	r2, .L724+12
	mov	r0, r5
	ldr	r1, [r1]
	ldrh	r2, [r2]
	str	r1, [sp, #4]
	ldr	r1, .L724+16
	ldrh	r1, [r1]
	str	r1, [sp]
	ldr	r1, .L724+20
	ldr	r10, [r1]
	ldr	r1, .L724+24
	ldrh	r7, [r1]
	ldr	r1, .L724+28
	ldr	r4, [r1]
	movs	r1, #12
	mla	r1, r2, r1, r1
	adds	r4, r4, #8
	add	r8, r5, r1
	mov	r1, r3
.L720:
	adds	r0, r0, #12
	ldr	r6, [sp]
	cmp	r0, r8
	add	ip, r3, r7
	add	r4, r4, #36
	add	lr, r1, r6
	bne	.L721
	ldr	r3, .L724+32
	mov	lr, #12
	mov	r8, #0
	ldr	r0, [r3]
	ldr	r3, .L724+8
	ldr	r4, [r3]
	ldr	r3, .L724+20
	ldr	ip, [r3]
.L722:
	cmp	r2, r0
	bcc	.L723
	add	sp, sp, #8
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r10, fp, pc}
.L721:
	bic	r1, r1, #3
	bic	r3, r3, #3
	mov	r6, r1
	ldr	r1, [sp, #4]
	add	r3, r3, r10
	str	fp, [r0, #-4]
	str	r3, [r0, #-8]
	add	r6, r6, r1
	mov	r1, lr
	str	r6, [r0, #-12]
	str	r3, [r4, #-32]
	mov	r3, ip
	str	r6, [r4, #-36]
	b	.L720
.L723:
	ldr	r3, [sp]
	mul	r10, lr, r2
	muls	r3, r2, r3
	add	r1, r5, r10
	str	r8, [r1, #8]
	bic	r3, r3, #3
	add	r3, r3, r4
	str	r3, [r5, r10]
	mul	r3, r2, r7
	adds	r2, r2, #1
	uxth	r2, r2
	bic	r3, r3, #3
	add	r3, r3, ip
	str	r3, [r1, #4]
	b	.L722
.L725:
	.align	2
.L724:
	.word	.LANCHOR106
	.word	.LANCHOR105
	.word	.LANCHOR107
	.word	.LANCHOR38
	.word	.LANCHOR57
	.word	.LANCHOR108
	.word	.LANCHOR58
	.word	.LANCHOR109
	.word	.LANCHOR110
	.size	FtlGcBufInit, .-FtlGcBufInit
	.section	.text.FtlGcBufFree,"ax",%progbits
	.align	1
	.global	FtlGcBufFree
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	FtlGcBufFree, %function
FtlGcBufFree:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	ldr	r3, .L733
	mov	ip, #12
	push	{r4, r5, r6, r7, r8, r10, fp, lr}
	movs	r4, #0
	mov	fp, #36
	mov	lr, r4
	ldr	r7, [r3]
	ldr	r3, .L733+4
	ldr	r5, [r3]
.L727:
	uxth	r3, r4
	cmp	r1, r3
	bls	.L726
	mla	r8, fp, r3, r0
	movs	r2, #0
.L728:
	uxth	r3, r2
	cmp	r7, r3
	bls	.L729
	mul	r3, ip, r3
	ldr	r6, [r8, #8]
	adds	r2, r2, #1
	add	r10, r5, r3
	ldr	r3, [r5, r3]
	cmp	r3, r6
	bne	.L728
	str	lr, [r10, #8]
.L729:
	adds	r4, r4, #1
	b	.L727
.L726:
	pop	{r4, r5, r6, r7, r8, r10, fp, pc}
.L734:
	.align	2
.L733:
	.word	.LANCHOR110
	.word	.LANCHOR106
	.size	FtlGcBufFree, .-FtlGcBufFree
	.section	.text.FtlGcBufAlloc,"ax",%progbits
	.align	1
	.global	FtlGcBufAlloc
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	FtlGcBufAlloc, %function
FtlGcBufAlloc:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	ldr	r3, .L742
	movs	r2, #0
	push	{r4, r5, r6, r7, r8, r10, lr}
	mov	ip, #12
	movs	r7, #1
	mov	lr, #36
	ldr	r4, [r3]
	ldr	r3, .L742+4
	ldr	r5, [r3]
.L736:
	uxth	r8, r2
	cmp	r1, r8
	bhi	.L740
	pop	{r4, r5, r6, r7, r8, r10, pc}
.L740:
	mov	r10, #0
.L737:
	uxth	r3, r10
	cmp	r4, r3
	bls	.L738
	mla	r3, ip, r3, r5
	add	r10, r10, #1
	ldr	r6, [r3, #8]
	cmp	r6, #0
	bne	.L737
	mla	r8, lr, r8, r0
	str	r7, [r3, #8]
	ldr	r6, [r3]
	ldr	r3, [r3, #4]
	str	r6, [r8, #8]
	str	r3, [r8, #12]
.L738:
	adds	r2, r2, #1
	b	.L736
.L743:
	.align	2
.L742:
	.word	.LANCHOR110
	.word	.LANCHOR106
	.size	FtlGcBufAlloc, .-FtlGcBufAlloc
	.section	.text.IsBlkInGcList,"ax",%progbits
	.align	1
	.global	IsBlkInGcList
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	IsBlkInGcList, %function
IsBlkInGcList:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	ldr	r3, .L749
	ldr	r2, .L749+4
	ldr	r3, [r3]
	ldrh	r2, [r2]
	add	r2, r3, r2, lsl #1
.L745:
	cmp	r3, r2
	bne	.L747
	movs	r0, #0
	bx	lr
.L747:
	ldrh	r1, [r3], #2
	cmp	r1, r0
	bne	.L745
	movs	r0, #1
	bx	lr
.L750:
	.align	2
.L749:
	.word	.LANCHOR111
	.word	.LANCHOR112
	.size	IsBlkInGcList, .-IsBlkInGcList
	.section	.text.FtlGcUpdatePage,"ax",%progbits
	.align	1
	.global	FtlGcUpdatePage
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	FtlGcUpdatePage, %function
FtlGcUpdatePage:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r3, r4, r5, r6, r7, lr}
	mov	r5, r0
	ldr	r4, .L755
	ubfx	r0, r0, #10, #16
	mov	r6, r1
	mov	r7, r2
	bl	P2V_block_in_plane
	ldr	r3, .L755+4
	ldrh	r1, [r4]
	ldr	r2, [r3]
	movs	r3, #0
.L752:
	uxth	ip, r3
	cmp	ip, r1
	bcc	.L754
	bne	.L753
	strh	r0, [r2, ip, lsl #1]	@ movhi
	ldrh	r3, [r4]
	adds	r3, r3, #1
	strh	r3, [r4]	@ movhi
	b	.L753
.L754:
	adds	r3, r3, #1
	add	ip, r2, r3, lsl #1
	ldrh	ip, [ip, #-2]
	cmp	ip, r0
	bne	.L752
.L753:
	ldr	r2, .L755+8
	movs	r0, #12
	ldr	r1, .L755+12
	ldrh	r3, [r2]
	ldr	r1, [r1]
	muls	r0, r3, r0
	adds	r3, r3, #1
	adds	r4, r1, r0
	str	r6, [r4, #4]
	str	r7, [r4, #8]
	str	r5, [r1, r0]
	strh	r3, [r2]	@ movhi
	pop	{r3, r4, r5, r6, r7, pc}
.L756:
	.align	2
.L755:
	.word	.LANCHOR112
	.word	.LANCHOR111
	.word	.LANCHOR113
	.word	.LANCHOR114
	.size	FtlGcUpdatePage, .-FtlGcUpdatePage
	.section	.text.FtlGcRefreshOpenBlock,"ax",%progbits
	.align	1
	.global	FtlGcRefreshOpenBlock
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	FtlGcRefreshOpenBlock, %function
FtlGcRefreshOpenBlock:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	ldr	ip, .L762+12
	push	{r4, r5, r6, r7, lr}
	ldrh	lr, [ip]
	cmp	lr, r0
	beq	.L758
	ldr	r6, .L762
	ldrh	r7, [r6]
	cmp	r0, r7
	beq	.L758
	ldr	r4, .L762+4
	ldrh	r5, [r4]
	cmp	r0, r5
	beq	.L758
	ldr	r2, .L762+8
	ldrh	r1, [r2]
	cmp	r0, r1
	beq	.L758
	movw	r3, #65535
	cmp	lr, r3
	bne	.L759
	strh	r0, [ip]	@ movhi
.L758:
	movs	r0, #0
	pop	{r4, r5, r6, r7, pc}
.L759:
	cmp	r7, r3
	bne	.L760
	strh	r0, [r6]	@ movhi
	b	.L758
.L760:
	cmp	r5, r3
	bne	.L761
	strh	r0, [r4]	@ movhi
	b	.L758
.L761:
	cmp	r1, r3
	it	eq
	strheq	r0, [r2]	@ movhi
	b	.L758
.L763:
	.align	2
.L762:
	.word	.LANCHOR116
	.word	.LANCHOR117
	.word	.LANCHOR118
	.word	.LANCHOR115
	.size	FtlGcRefreshOpenBlock, .-FtlGcRefreshOpenBlock
	.section	.text.FtlGcRefreshBlock,"ax",%progbits
	.align	1
	.global	FtlGcRefreshBlock
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	FtlGcRefreshBlock, %function
FtlGcRefreshBlock:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	ldr	ip, .L774+12
	push	{r4, r5, r6, r7, lr}
	ldrh	lr, [ip]
	cmp	lr, r0
	beq	.L772
	ldr	r6, .L774
	ldrh	r7, [r6]
	cmp	r0, r7
	beq	.L772
	ldr	r4, .L774+4
	ldrh	r5, [r4]
	cmp	r0, r5
	beq	.L772
	ldr	r2, .L774+8
	ldrh	r1, [r2]
	cmp	r0, r1
	beq	.L772
	movw	r3, #65535
	cmp	lr, r3
	bne	.L766
	strh	r0, [ip]	@ movhi
.L772:
	movs	r0, #0
	pop	{r4, r5, r6, r7, pc}
.L766:
	cmp	r7, r3
	bne	.L767
	strh	r0, [r6]	@ movhi
	b	.L772
.L767:
	cmp	r5, r3
	bne	.L768
	strh	r0, [r4]	@ movhi
	b	.L772
.L768:
	cmp	r1, r3
	bne	.L773
	strh	r0, [r2]	@ movhi
	b	.L772
.L773:
	mov	r0, #-1
	pop	{r4, r5, r6, r7, pc}
.L775:
	.align	2
.L774:
	.word	.LANCHOR116
	.word	.LANCHOR117
	.word	.LANCHOR118
	.word	.LANCHOR115
	.size	FtlGcRefreshBlock, .-FtlGcRefreshBlock
	.section	.text.FtlGcMarkBadPhyBlk,"ax",%progbits
	.align	1
	.global	FtlGcMarkBadPhyBlk
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	FtlGcMarkBadPhyBlk, %function
FtlGcMarkBadPhyBlk:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r3, r4, r5, lr}
	mov	r4, r0
	bl	P2V_block_in_plane
	mov	r5, r0
	bl	FtlGcRefreshBlock
	ldr	r3, .L784
	ldr	r3, [r3]
	cbz	r3, .L777
	ldr	r3, .L784+4
	ldr	r2, [r3]
	ldrh	r3, [r2, r5, lsl #1]
	cmp	r3, #39
	itt	hi
	subhi	r3, r3, #40
	strhhi	r3, [r2, r5, lsl #1]	@ movhi
.L777:
	ldr	r2, .L784+8
	movs	r1, #0
	ldr	r5, .L784+12
	ldrh	r3, [r2]
.L778:
	uxth	r0, r1
	cmp	r3, r0
	bhi	.L780
	cmp	r3, #15
	itttt	ls
	addls	r1, r3, #1
	strhls	r1, [r2]	@ movhi
	ldrls	r2, .L784+12
	strhls	r4, [r2, r3, lsl #1]	@ movhi
	b	.L779
.L780:
	adds	r1, r1, #1
	add	r0, r5, r1, lsl #1
	ldrh	r0, [r0, #-2]
	cmp	r0, r4
	bne	.L778
.L779:
	movs	r0, #0
	pop	{r3, r4, r5, pc}
.L785:
	.align	2
.L784:
	.word	.LANCHOR104
	.word	.LANCHOR80
	.word	.LANCHOR119
	.word	.LANCHOR120
	.size	FtlGcMarkBadPhyBlk, .-FtlGcMarkBadPhyBlk
	.section	.text.FtlGcReFreshBadBlk,"ax",%progbits
	.align	1
	.global	FtlGcReFreshBadBlk
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	FtlGcReFreshBadBlk, %function
FtlGcReFreshBadBlk:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	ldr	r3, .L792
	push	{r4, lr}
	ldrh	r3, [r3]
	cbz	r3, .L787
	ldr	r2, .L792+4
	ldrh	r1, [r2]
	movw	r2, #65535
	cmp	r1, r2
	bne	.L787
	ldr	r4, .L792+8
	ldrh	r2, [r4]
	cmp	r2, r3
	itt	cs
	movcs	r3, #0
	strhcs	r3, [r4]	@ movhi
	ldr	r3, .L792+12
	ldrh	r2, [r4]
	ldrh	r0, [r3, r2, lsl #1]
	bl	P2V_block_in_plane
	bl	FtlGcRefreshBlock
	ldrh	r3, [r4]
	adds	r3, r3, #1
	strh	r3, [r4]	@ movhi
.L787:
	movs	r0, #0
	pop	{r4, pc}
.L793:
	.align	2
.L792:
	.word	.LANCHOR119
	.word	.LANCHOR115
	.word	.LANCHOR121
	.word	.LANCHOR120
	.size	FtlGcReFreshBadBlk, .-FtlGcReFreshBadBlk
	.section	.text.flash_boot_enter_slc_mode,"ax",%progbits
	.align	1
	.global	flash_boot_enter_slc_mode
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	flash_boot_enter_slc_mode, %function
flash_boot_enter_slc_mode:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	ldr	r3, .L796
	ldr	r2, [r3]
	ldr	r3, .L796+4
	cmp	r2, r3
	bne	.L794
	b	flash_enter_slc_mode
.L794:
	bx	lr
.L797:
	.align	2
.L796:
	.word	.LANCHOR122
	.word	1446522928
	.size	flash_boot_enter_slc_mode, .-flash_boot_enter_slc_mode
	.section	.text.flash_boot_exit_slc_mode,"ax",%progbits
	.align	1
	.global	flash_boot_exit_slc_mode
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	flash_boot_exit_slc_mode, %function
flash_boot_exit_slc_mode:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	ldr	r3, .L800
	ldr	r2, [r3]
	ldr	r3, .L800+4
	cmp	r2, r3
	bne	.L798
	b	flash_exit_slc_mode
.L798:
	bx	lr
.L801:
	.align	2
.L800:
	.word	.LANCHOR122
	.word	1446522928
	.size	flash_boot_exit_slc_mode, .-flash_boot_exit_slc_mode
	.section	.text.FW_FlashBlockErase.constprop.41,"ax",%progbits
	.align	1
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	FW_FlashBlockErase.constprop.41, %function
FW_FlashBlockErase.constprop.41:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r3, r4, r5, lr}
	mov	r4, r0
	ldr	r3, .L803
	movs	r0, #0
	ldr	r3, [r3]
	ldrb	r5, [r3, #9]	@ zero_extendqisi2
	bl	flash_boot_enter_slc_mode
	mov	r0, r4
	mov	r1, r5
	bl	__aeabi_uidiv
	movs	r2, #0
	mov	r1, r0
	mov	r0, r2
	bl	FlashEraseBlock
	mov	r4, r0
	movs	r0, #0
	bl	flash_boot_exit_slc_mode
	uxtb	r0, r4
	pop	{r3, r4, r5, pc}
.L804:
	.align	2
.L803:
	.word	.LANCHOR7
	.size	FW_FlashBlockErase.constprop.41, .-FW_FlashBlockErase.constprop.41
	.section	.text.ftl_memset,"ax",%progbits
	.align	1
	.global	ftl_memset
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	ftl_memset, %function
ftl_memset:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	b	memset
	.size	ftl_memset, .-ftl_memset
	.section	.text.BuildFlashLsbPageTable,"ax",%progbits
	.align	1
	.global	BuildFlashLsbPageTable
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	BuildFlashLsbPageTable, %function
BuildFlashLsbPageTable:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, lr}
	mov	r4, r1
	cbnz	r0, .L807
	ldr	r3, .L862
.L808:
	strh	r0, [r3, r0, lsl #1]	@ movhi
	adds	r0, r0, #1
	cmp	r0, #512
	bne	.L808
.L814:
	movs	r1, #255
	mov	r2, #2048
	ldr	r0, .L862+4
	uxth	r4, r4
	bl	ftl_memset
	ldr	r1, .L862
	movs	r3, #0
	ldr	r0, .L862+4
.L809:
	uxth	r2, r3
	cmp	r4, r2
	bhi	.L842
	pop	{r4, pc}
.L807:
	cmp	r0, #1
	bne	.L810
	ldr	r1, .L862
	movs	r3, #0
.L813:
	cmp	r3, #3
	uxth	r2, r3
	bls	.L811
	tst	r2, #1
	ite	ne
	movne	r0, #3
	moveq	r0, #2
	rsb	r2, r0, r2, lsl #1
	uxth	r2, r2
.L811:
	strh	r2, [r1, r3, lsl #1]	@ movhi
	adds	r3, r3, #1
	cmp	r3, #512
	bne	.L813
	b	.L814
.L810:
	cmp	r0, #2
	bne	.L815
	ldr	r1, .L862
	movs	r2, #0
.L817:
	uxth	r3, r2
	cmp	r2, #1
	ittt	hi
	lslhi	r3, r3, #1
	addhi	r3, r3, #-1
	uxthhi	r3, r3
	strh	r3, [r1, r2, lsl #1]	@ movhi
	adds	r2, r2, #1
	cmp	r2, #512
	bne	.L817
	b	.L814
.L815:
	cmp	r0, #3
	bne	.L818
	ldr	r1, .L862
	movs	r3, #0
.L821:
	cmp	r3, #5
	uxth	r2, r3
	bls	.L819
	tst	r2, #1
	ite	ne
	movne	r0, #5
	moveq	r0, #4
	rsb	r2, r0, r2, lsl #1
	uxth	r2, r2
.L819:
	strh	r2, [r1, r3, lsl #1]	@ movhi
	adds	r3, r3, #1
	cmp	r3, #512
	bne	.L821
	b	.L814
.L818:
	cmp	r0, #4
	mov	r3, #0
	bne	.L822
	ldr	r2, .L862
	strh	r3, [r2]	@ movhi
	movs	r3, #1
	strh	r3, [r2, #2]	@ movhi
	movs	r3, #2
	strh	r3, [r2, #4]	@ movhi
	movs	r3, #3
	strh	r3, [r2, #6]	@ movhi
	movs	r3, #5
	strh	r3, [r2, #10]	@ movhi
	movs	r3, #7
	strh	r3, [r2, #12]	@ movhi
	movs	r3, #8
	strh	r0, [r2, #8]	@ movhi
	strh	r3, [r2, #14]!	@ movhi
.L824:
	tst	r3, #1
	ite	ne
	movne	r1, #7
	moveq	r1, #6
	rsb	r1, r1, r3, lsl #1
	adds	r3, r3, #1
	uxth	r3, r3
	strh	r1, [r2, #2]!	@ movhi
	cmp	r3, #512
	bne	.L824
	b	.L814
.L822:
	cmp	r0, #5
	bne	.L825
	ldr	r2, .L862
.L826:
	strh	r3, [r2, r3, lsl #1]	@ movhi
	adds	r3, r3, #1
	cmp	r3, #16
	bne	.L826
	ldr	r2, .L862+8
.L827:
	strh	r3, [r2, #2]!	@ movhi
	adds	r3, r3, #2
	uxth	r3, r3
	cmp	r3, #1008
	bne	.L827
	b	.L814
.L825:
	cmp	r0, #6
	bne	.L828
	ldr	r0, .L862
	mov	r1, r3
.L831:
	cmp	r1, #5
	uxth	r2, r1
	bls	.L829
	tst	r2, #1
	ite	ne
	movne	r2, #12
	moveq	r2, #10
	subs	r2, r3, r2
	uxth	r2, r2
.L829:
	strh	r2, [r0, r1, lsl #1]	@ movhi
	adds	r1, r1, #1
	cmp	r1, #512
	add	r3, r3, #3
	uxth	r3, r3
	bne	.L831
	b	.L814
.L828:
	cmp	r0, #9
	bne	.L832
	ldr	r2, .L862
	movw	r1, #1021
	strh	r3, [r2]	@ movhi
	movs	r3, #1
	strh	r3, [r2, #2]	@ movhi
	mov	r3, r2
	movs	r2, #2
	strh	r2, [r3, #4]!	@ movhi
	movs	r2, #3
.L833:
	strh	r2, [r3, #2]!	@ movhi
	adds	r2, r2, #2
	uxth	r2, r2
	cmp	r2, r1
	bne	.L833
	b	.L814
.L832:
	cmp	r0, #10
	bne	.L834
	ldr	r2, .L862
.L835:
	strh	r3, [r2, r3, lsl #1]	@ movhi
	adds	r3, r3, #1
	cmp	r3, #63
	bne	.L835
	ldr	r2, .L862+12
	movw	r1, #961
.L836:
	strh	r3, [r2, #2]!	@ movhi
	adds	r3, r3, #2
	uxth	r3, r3
	cmp	r3, r1
	bne	.L836
	b	.L814
.L834:
	cmp	r0, #11
	bne	.L837
	ldr	r2, .L862
	movs	r3, #0
.L838:
	strh	r3, [r2, r3, lsl #1]	@ movhi
	adds	r3, r3, #1
	cmp	r3, #8
	bne	.L838
	ldr	r1, .L862+16
.L840:
	tst	r3, #1
	ite	ne
	movne	r2, #7
	moveq	r2, #6
	rsb	r2, r2, r3, lsl #1
	adds	r3, r3, #1
	uxth	r3, r3
	strh	r2, [r1, #2]!	@ movhi
	cmp	r3, #512
	bne	.L840
	b	.L814
.L837:
	cmp	r0, #12
	bne	.L814
	ldr	r3, .L862
	movs	r2, #0
	strh	r2, [r3]	@ movhi
	movs	r2, #1
	strh	r2, [r3, #2]	@ movhi
	movs	r2, #2
	strh	r2, [r3, #4]	@ movhi
	movs	r2, #3
	strh	r2, [r3, #6]!	@ movhi
	movs	r2, #4
.L841:
	subs	r1, r2, #1
	add	r1, r1, r2, lsr #1
	adds	r2, r2, #1
	uxth	r2, r2
	strh	r1, [r3, #2]!	@ movhi
	cmp	r2, #512
	bne	.L841
	b	.L814
.L842:
	ldrh	r2, [r1, r3, lsl #1]
	adds	r3, r3, #1
	strh	r2, [r0, r2, lsl #1]	@ movhi
	b	.L809
.L863:
	.align	2
.L862:
	.word	.LANCHOR17
	.word	.LANCHOR123
	.word	.LANCHOR17+30
	.word	.LANCHOR17+124
	.word	.LANCHOR17+14
	.size	BuildFlashLsbPageTable, .-BuildFlashLsbPageTable
	.section	.text.FlashDieInfoInit,"ax",%progbits
	.align	1
	.global	FlashDieInfoInit
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	FlashDieInfoInit, %function
FlashDieInfoInit:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 0, uses_anonymous_args = 0
	ldr	r3, .L878
	push	{r0, r1, r4, r5, r6, r7, r8, r10, fp, lr}
	movs	r4, #0
	ldr	r5, .L878+4
	ldr	fp, .L878+36
	ldrh	r0, [r3, #10]
	strb	r4, [r5]
	strb	r4, [fp]
	bl	FlashBlockAlignInit
	movs	r2, #8
	mov	r1, r4
	ldr	r0, .L878+8
	bl	ftl_memset
	movs	r2, #32
	mov	r1, r4
	ldr	r0, .L878+12
	bl	ftl_memset
	movs	r2, #128
	mov	r1, r4
	ldr	r0, .L878+16
	bl	ftl_memset
	ldr	r3, .L878+20
	ldr	r10, .L878+32
	ldr	r6, [r3]
	ldr	r3, .L878+8
	ldrb	r8, [r6]	@ zero_extendqisi2
	adds	r7, r6, #1
.L866:
	mov	r2, r8
	add	r1, r10, r4, lsl #3
	mov	r0, r7
	str	r3, [sp, #4]
	bl	FlashMemCmp8
	ldr	r3, [sp, #4]
	cbnz	r0, .L865
	ldrb	r2, [r5]	@ zero_extendqisi2
	ldr	r1, .L878+12
	strb	r4, [r3, r2]
	str	r0, [r1, r2, lsl #2]
	adds	r1, r2, #1
	strb	r1, [r5]
.L865:
	adds	r4, r4, #1
	cmp	r4, #4
	bne	.L866
	ldrb	r3, [r5]	@ zero_extendqisi2
	strb	r3, [fp]
	ldrb	r3, [r6, #8]	@ zero_extendqisi2
	cmp	r3, #2
	beq	.L867
.L871:
	ldrh	r2, [r6, #14]
	ldrb	r3, [r5]	@ zero_extendqisi2
	smulbb	r3, r3, r2
	ldrb	r2, [r6, #13]	@ zero_extendqisi2
	smulbb	r3, r3, r2
	ldr	r2, .L878+24
	strh	r3, [r2]	@ movhi
	add	sp, sp, #8
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r10, fp, pc}
.L867:
	ldr	r3, .L878+28
	movs	r4, #0
	ldr	r10, .L878+12
	ldr	fp, [r3]
	ldr	r3, .L878+8
.L870:
	str	r3, [sp, #4]
	mov	r2, r8
	ldr	r3, .L878+32
	mov	r0, r7
	add	r1, r3, r4, lsl #3
	bl	FlashMemCmp8
	ldr	r3, [sp, #4]
	cbnz	r0, .L868
	ldrh	r2, [r6, #14]
	ldrb	r1, [r5]	@ zero_extendqisi2
	and	r0, r2, #65280
	ldrb	r2, [r6, #13]	@ zero_extendqisi2
	mul	r2, fp, r2
	muls	r2, r0, r2
	str	r2, [r10, r1, lsl #2]
	ldrb	r0, [r6, #23]	@ zero_extendqisi2
	cbz	r0, .L869
	lsls	r2, r2, #1
	str	r2, [r10, r1, lsl #2]
.L869:
	adds	r2, r1, #1
	strb	r4, [r3, r1]
	strb	r2, [r5]
.L868:
	adds	r4, r4, #1
	cmp	r4, #4
	bne	.L870
	b	.L871
.L879:
	.align	2
.L878:
	.word	.LANCHOR31
	.word	.LANCHOR26
	.word	.LANCHOR27
	.word	.LANCHOR18
	.word	.LANCHOR23
	.word	.LANCHOR7
	.word	.LANCHOR125
	.word	.LANCHOR4
	.word	.LANCHOR22
	.word	.LANCHOR124
	.size	FlashDieInfoInit, .-FlashDieInfoInit
	.section	.text.ftl_read_flash_info,"ax",%progbits
	.align	1
	.global	ftl_read_flash_info
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	ftl_read_flash_info, %function
ftl_read_flash_info:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, lr}
	movs	r2, #11
	movs	r1, #0
	mov	r4, r0
	bl	ftl_memset
	ldr	r3, .L883
	movs	r2, #0
	ldr	r1, [r3]
	ldr	r3, .L883+4
	ldrb	r5, [r1, #9]	@ zero_extendqisi2
	ldr	r3, [r3]
	smulbb	r3, r3, r5
	uxth	r3, r3
	lsrs	r0, r3, #8
	strb	r3, [r4, #4]
	strb	r0, [r4, #5]
	ldr	r0, .L883+8
	ldrb	r0, [r0]	@ zero_extendqisi2
	strb	r0, [r4, #7]
	ldrb	r0, [r1, #13]	@ zero_extendqisi2
	muls	r3, r0, r3
	ldrh	r0, [r1, #14]
	muls	r0, r3, r0
	ldrb	r3, [r1, #8]	@ zero_extendqisi2
	strb	r5, [r4, #6]
	movs	r5, #1
	muls	r3, r0, r3
	ubfx	r0, r3, #8, #8
	strb	r3, [r4]
	strb	r0, [r4, #1]
	ubfx	r0, r3, #16, #8
	lsrs	r3, r3, #24
	strb	r0, [r4, #2]
	ldr	r0, .L883+12
	strb	r3, [r4, #3]
	movs	r3, #32
	strb	r3, [r4, #8]
	ldrb	r3, [r1, #7]	@ zero_extendqisi2
	strb	r2, [r4, #10]
	strb	r3, [r4, #9]
	ldr	r3, .L883+16
	ldrb	r1, [r3]	@ zero_extendqisi2
	mov	r3, r2
.L881:
	uxtb	r2, r3
	cmp	r1, r2
	bhi	.L882
	pop	{r4, r5, r6, pc}
.L882:
	ldrb	r2, [r3, r0]	@ zero_extendqisi2
	adds	r3, r3, #1
	ldrb	r6, [r4, #10]	@ zero_extendqisi2
	lsl	r2, r5, r2
	orrs	r2, r2, r6
	strb	r2, [r4, #10]
	b	.L881
.L884:
	.align	2
.L883:
	.word	.LANCHOR7
	.word	.LANCHOR4
	.word	.LANCHOR33
	.word	.LANCHOR27
	.word	.LANCHOR26
	.size	ftl_read_flash_info, .-ftl_read_flash_info
	.section	.text.FtlBbt2Bitmap,"ax",%progbits
	.align	1
	.global	FtlBbt2Bitmap
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	FtlBbt2Bitmap, %function
FtlBbt2Bitmap:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	ldr	r3, .L891
	push	{r4, r5, r6, r7, r8, lr}
	mov	r5, r0
	ldr	r7, .L891+4
	mov	r6, r1
	subs	r4, r5, #2
	addw	r5, r5, #1022
	ldrh	r2, [r3]
	movs	r1, #0
	ldr	r8, .L891+24
	mov	r0, r6
	lsls	r2, r2, #2
	bl	ftl_memset
.L888:
	ldrh	r3, [r4, #2]
	movw	r2, #65535
	cmp	r3, r2
	beq	.L885
	ldrh	r2, [r7]
	cmp	r2, r3
	bhi	.L887
	mov	r1, r8
	movs	r2, #92
	ldr	r0, .L891+8
	bl	printf
	ldr	r1, .L891+12
	ldr	r0, .L891+16
	bl	printf
.L887:
	ldrh	r3, [r4, #2]!
	movs	r2, #1
	cmp	r5, r4
	lsr	r1, r3, #5
	and	r3, r3, #31
	lsl	r3, r2, r3
	ldr	r2, [r6, r1, lsl #2]
	orr	r2, r2, r3
	str	r2, [r6, r1, lsl #2]
	ldr	r2, .L891+20
	ldrh	r3, [r2, #6]
	add	r3, r3, #1
	strh	r3, [r2, #6]	@ movhi
	bne	.L888
.L885:
	pop	{r4, r5, r6, r7, r8, pc}
.L892:
	.align	2
.L891:
	.word	.LANCHOR126
	.word	.LANCHOR51
	.word	.LC5
	.word	.LC6
	.word	.LC7
	.word	.LANCHOR76
	.word	.LANCHOR127
	.size	FtlBbt2Bitmap, .-FtlBbt2Bitmap
	.section	.text.FtlBbtMemInit,"ax",%progbits
	.align	1
	.global	FtlBbtMemInit
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	FtlBbtMemInit, %function
FtlBbtMemInit:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	ldr	r0, .L894
	movw	r3, #65535
	movs	r2, #16
	movs	r1, #255
	strh	r3, [r0]	@ movhi
	movs	r3, #0
	strh	r3, [r0, #6]	@ movhi
	adds	r0, r0, #12
	b	ftl_memset
.L895:
	.align	2
.L894:
	.word	.LANCHOR76
	.size	FtlBbtMemInit, .-FtlBbtMemInit
	.section	.text.FtlFreeSysBlkQueueInit,"ax",%progbits
	.align	1
	.global	FtlFreeSysBlkQueueInit
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	FtlFreeSysBlkQueueInit, %function
FtlFreeSysBlkQueueInit:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	ldr	r3, .L897
	mov	r2, #2048
	push	{r4, lr}
	movs	r4, #0
	mov	r1, r4
	strh	r4, [r3, #2]	@ movhi
	strh	r4, [r3, #4]	@ movhi
	strh	r4, [r3, #6]	@ movhi
	strh	r0, [r3], #8	@ movhi
	mov	r0, r3
	bl	ftl_memset
	mov	r0, r4
	pop	{r4, pc}
.L898:
	.align	2
.L897:
	.word	.LANCHOR77
	.size	FtlFreeSysBlkQueueInit, .-FtlFreeSysBlkQueueInit
	.section	.text.ftl_free_no_use_map_blk,"ax",%progbits
	.align	1
	.global	ftl_free_no_use_map_blk
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	ftl_free_no_use_map_blk, %function
ftl_free_no_use_map_blk:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 0, uses_anonymous_args = 0
	ldrh	r2, [r0, #10]
	push	{r0, r1, r4, r5, r6, r7, r8, r10, fp, lr}
	mov	r4, r0
	ldr	r5, [r0, #20]
	movs	r1, #0
	ldr	r7, [r0, #12]
	lsls	r2, r2, #1
	ldr	r6, [r0, #24]
	mov	r0, r5
	bl	ftl_memset
	movs	r3, #0
.L900:
	ldrh	r1, [r4, #6]
	uxth	r2, r3
	cmp	r1, r2
	bhi	.L904
	ldr	r3, .L919
	movs	r6, #0
	mov	r10, r6
	ldrh	r2, [r3]
	ldrh	r3, [r4]
	strh	r2, [r5, r3, lsl #1]	@ movhi
	mov	r2, r6
	ldrh	fp, [r5]
.L905:
	ldrh	r3, [r4, #10]
	uxth	ip, r6
	cmp	r3, ip
	bhi	.L909
	mov	r0, r10
	add	sp, sp, #8
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r10, fp, pc}
.L904:
	uxth	r2, r3
	ldr	r1, [r6, r2, lsl #2]
	movs	r2, #0
	ubfx	r1, r1, #10, #16
.L901:
	ldrh	ip, [r4, #10]
	uxth	r0, r2
	cmp	ip, r0
	bhi	.L903
	adds	r3, r3, #1
	b	.L900
.L903:
	uxth	r0, r2
	ldrh	ip, [r7, r0, lsl #1]
	cmp	ip, r1
	bne	.L902
	cbz	r1, .L902
	ldrh	ip, [r5, r0, lsl #1]
	add	ip, ip, #1
	strh	ip, [r5, r0, lsl #1]	@ movhi
.L902:
	adds	r2, r2, #1
	b	.L901
.L909:
	uxth	r1, r6
	ldrh	r3, [r5, r1, lsl #1]
	lsl	r8, r1, #1
	cmp	fp, r3
	bls	.L906
	ldrh	r0, [r7, r1, lsl #1]
	add	r8, r8, r7
	cbnz	r0, .L907
.L908:
	adds	r6, r6, #1
	b	.L905
.L906:
	cmp	r3, #0
	bne	.L908
	ldrh	r0, [r7, r1, lsl #1]
	add	r8, r8, r7
	cmp	r0, #0
	beq	.L908
.L910:
	movs	r1, #1
	str	r2, [sp, #4]
	bl	FtlFreeSysBlkQueueIn
	ldr	r2, [sp, #4]
	strh	r2, [r8]	@ movhi
	ldrh	r3, [r4, #8]
	subs	r3, r3, #1
	strh	r3, [r4, #8]	@ movhi
	b	.L908
.L907:
	mov	r10, ip
	mov	fp, r3
	cmp	r3, #0
	beq	.L910
	b	.L908
.L920:
	.align	2
.L919:
	.word	.LANCHOR53
	.size	ftl_free_no_use_map_blk, .-ftl_free_no_use_map_blk
	.section	.text.FtlL2PDataInit,"ax",%progbits
	.align	1
	.global	FtlL2PDataInit
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	FtlL2PDataInit, %function
FtlL2PDataInit:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, r8, lr}
	movs	r1, #0
	ldr	r5, .L924
	ldr	r4, .L924+4
	ldr	r2, [r5]
	ldr	r7, .L924+8
	ldr	r6, .L924+12
	ldr	r0, [r4]
	lsls	r2, r2, #1
	ldr	r8, .L924+44
	bl	ftl_memset
	ldrh	r3, [r7]
	movs	r1, #255
	ldrh	r2, [r6]
	ldr	r0, [r8]
	muls	r2, r3, r2
	bl	ftl_memset
	ldr	r3, .L924+16
	movw	r0, #65535
	ldrh	r1, [r6]
	ldr	ip, [r8]
	ldr	r2, [r3]
	movs	r3, #12
	ldrh	r7, [r7]
	mla	r3, r1, r3, r3
	adds	r1, r2, r3
	movs	r3, #0
	mov	lr, r3
.L922:
	adds	r2, r2, #12
	adds	r6, r3, r7
	cmp	r2, r1
	bne	.L923
	ldr	r3, .L924+20
	ldr	r2, [r5]
	strh	r0, [r3, #2]	@ movhi
	strh	r2, [r3, #10]	@ movhi
	movw	r2, #61634
	strh	r2, [r3, #4]	@ movhi
	ldr	r2, .L924+24
	strh	r0, [r3]	@ movhi
	ldrh	r2, [r2]
	strh	r2, [r3, #8]	@ movhi
	ldr	r2, .L924+28
	ldrh	r2, [r2]
	strh	r2, [r3, #6]	@ movhi
	ldr	r2, .L924+32
	ldr	r2, [r2]
	str	r2, [r3, #12]
	ldr	r2, .L924+36
	ldr	r2, [r2]
	str	r2, [r3, #16]
	ldr	r2, [r4]
	str	r2, [r3, #20]
	ldr	r2, .L924+40
	ldr	r2, [r2]
	str	r2, [r3, #24]
	pop	{r4, r5, r6, r7, r8, pc}
.L923:
	bic	r3, r3, #3
	str	lr, [r2, #-8]
	add	r3, r3, ip
	strh	r0, [r2, #-12]	@ movhi
	str	r3, [r2, #-4]
	mov	r3, r6
	b	.L922
.L925:
	.align	2
.L924:
	.word	.LANCHOR64
	.word	.LANCHOR128
	.word	.LANCHOR57
	.word	.LANCHOR67
	.word	.LANCHOR98
	.word	.LANCHOR130
	.word	.LANCHOR131
	.word	.LANCHOR66
	.word	.LANCHOR132
	.word	.LANCHOR133
	.word	.LANCHOR134
	.word	.LANCHOR129
	.size	FtlL2PDataInit, .-FtlL2PDataInit
	.section	.text.FtlVariablesInit,"ax",%progbits
	.align	1
	.global	FtlVariablesInit
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	FtlVariablesInit, %function
FtlVariablesInit:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r3, r4, r5, lr}
	movs	r4, #0
	ldr	r3, .L927
	movw	r2, #65535
	mov	r1, r4
	ldr	r5, .L927+4
	str	r4, [r3]
	ldr	r3, .L927+8
	strh	r2, [r3]	@ movhi
	mov	r2, #-1
	ldr	r3, .L927+12
	str	r4, [r3]
	ldr	r3, .L927+16
	str	r4, [r3]
	ldr	r3, .L927+20
	str	r2, [r3]
	ldr	r3, .L927+24
	str	r4, [r3]
	ldr	r3, .L927+28
	strh	r4, [r3]	@ movhi
	ldr	r3, .L927+32
	ldrh	r2, [r3]
	ldr	r3, .L927+36
	lsls	r2, r2, #1
	ldr	r0, [r3]
	bl	ftl_memset
	ldrh	r2, [r5]
	mov	r1, r4
	ldr	r3, .L927+40
	lsls	r2, r2, #1
	ldr	r0, [r3]
	bl	ftl_memset
	ldrh	r2, [r5]
	mov	r1, r4
	ldr	r3, .L927+44
	lsls	r2, r2, #1
	ldr	r0, [r3]
	bl	ftl_memset
	mov	r1, r4
	movs	r2, #48
	ldr	r0, .L927+48
	bl	ftl_memset
	mov	r2, #512
	mov	r1, r4
	ldr	r0, .L927+52
	bl	ftl_memset
	bl	FtlGcBufInit
	bl	FtlL2PDataInit
	mov	r0, r4
	pop	{r3, r4, r5, pc}
.L928:
	.align	2
.L927:
	.word	.LANCHOR135
	.word	.LANCHOR41
	.word	.LANCHOR136
	.word	.LANCHOR137
	.word	.LANCHOR138
	.word	.LANCHOR139
	.word	.LANCHOR104
	.word	.LANCHOR70
	.word	.LANCHOR61
	.word	.LANCHOR71
	.word	.LANCHOR80
	.word	.LANCHOR140
	.word	.LANCHOR82
	.word	.LANCHOR141
	.size	FtlVariablesInit, .-FtlVariablesInit
	.section	.text.SupperBlkListInit,"ax",%progbits
	.align	1
	.global	SupperBlkListInit
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	SupperBlkListInit, %function
SupperBlkListInit:
	@ args = 0, pretend = 0, frame = 24
	@ frame_needed = 0, uses_anonymous_args = 0
	ldr	r3, .L940
	movs	r2, #6
	push	{r4, r5, r6, r7, r8, r10, fp, lr}
	movs	r1, #0
	ldr	r6, .L940+4
	sub	sp, sp, #24
	movs	r4, #0
	ldrh	r3, [r3]
	mov	r8, r4
	ldr	r0, [r6]
	mov	r5, r4
	mov	r10, r6
	muls	r2, r3, r2
	bl	ftl_memset
	ldr	r3, .L940+8
	ldr	r2, .L940+12
	ldr	r1, .L940+16
	str	r4, [r3]
	ldr	r3, .L940+20
	strh	r4, [r2]	@ movhi
	strh	r4, [r1]	@ movhi
	str	r4, [r3]
	ldr	r3, .L940+24
	str	r2, [sp, #8]
	str	r4, [r3]
	ldr	r3, .L940+28
	mov	fp, r3
	strh	r4, [r3]	@ movhi
.L930:
	ldr	r3, .L940+32
	sxth	r7, r4
	ldrh	r3, [r3]
	cmp	r7, r3
	bge	.L937
	ldr	r3, .L940+36
	uxth	r1, r4
	str	r1, [sp, #12]
	ldrh	r2, [r3]
	ldr	r3, .L940+40
	ldrh	r3, [r3]
	str	r3, [sp, #4]
	movs	r3, #0
	mov	r6, r3
	b	.L938
.L932:
	str	r3, [sp, #20]
	ldr	r3, .L940+44
	ldr	r1, [sp, #12]
	str	r2, [sp, #16]
	ldrb	r0, [r3, r0]	@ zero_extendqisi2
	bl	V2P_block
	bl	FtlBbmIsBadBlock
	ldr	r2, [sp, #16]
	ldr	r3, [sp, #20]
	cbnz	r0, .L931
	ldr	r1, [sp, #4]
	add	r6, r6, r1
	sxth	r6, r6
.L931:
	adds	r3, r3, #1
.L938:
	sxth	r0, r3
	cmp	r0, r2
	blt	.L932
	lsls	r3, r7, #1
	cbz	r6, .L933
	mov	r1, r6
	str	r3, [sp, #4]
	mov	r0, #32768
	bl	__aeabi_idiv
	ldr	r3, [sp, #4]
	sxth	r6, r0
.L934:
	ldr	r2, [r10]
	add	r3, r3, r7
	add	r2, r2, r3, lsl #1
	ldr	r3, .L940+48
	strh	r6, [r2, #4]	@ movhi
	ldrh	r3, [r3]
	cmp	r7, r3
	beq	.L935
	ldr	r3, .L940+52
	ldrh	r3, [r3]
	cmp	r7, r3
	beq	.L935
	ldr	r3, .L940+56
	ldrh	r3, [r3]
	cmp	r7, r3
	beq	.L935
	ldr	r3, .L940+60
	uxth	r0, r4
	ldr	r3, [r3]
	ldrh	r3, [r3, r7, lsl #1]
	cbnz	r3, .L936
	add	r8, r8, #1
	uxth	r8, r8
	bl	INSERT_FREE_LIST
.L935:
	adds	r4, r4, #1
	b	.L930
.L933:
	ldr	r2, .L940+60
	movw	r1, #65535
	ldr	r2, [r2]
	strh	r1, [r2, r7, lsl #1]	@ movhi
	b	.L934
.L936:
	adds	r5, r5, #1
	uxth	r5, r5
	bl	INSERT_DATA_LIST
	b	.L935
.L937:
	ldr	r2, [sp, #8]
	strh	r8, [fp]	@ movhi
	strh	r5, [r2]	@ movhi
	add	r5, r5, r8
	cmp	r3, r5
	bge	.L939
	ldr	r1, .L940+64
	movw	r2, #2899
	ldr	r0, .L940+68
	bl	printf
	ldr	r1, .L940+72
	ldr	r0, .L940+76
	bl	printf
.L939:
	movs	r0, #0
	add	sp, sp, #24
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r10, fp, pc}
.L941:
	.align	2
.L940:
	.word	.LANCHOR41
	.word	.LANCHOR83
	.word	.LANCHOR89
	.word	.LANCHOR87
	.word	.LANCHOR142
	.word	.LANCHOR84
	.word	.LANCHOR86
	.word	.LANCHOR90
	.word	.LANCHOR40
	.word	.LANCHOR38
	.word	.LANCHOR52
	.word	.LANCHOR47
	.word	.LANCHOR93
	.word	.LANCHOR94
	.word	.LANCHOR95
	.word	.LANCHOR85
	.word	.LANCHOR143
	.word	.LC5
	.word	.LC6
	.word	.LC7
	.size	SupperBlkListInit, .-SupperBlkListInit
	.section	.text.FtlGcPageVarInit,"ax",%progbits
	.align	1
	.global	FtlGcPageVarInit
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	FtlGcPageVarInit, %function
FtlGcPageVarInit:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	ldr	r2, .L943
	movs	r3, #0
	push	{r4, lr}
	movs	r1, #255
	ldr	r4, .L943+4
	strh	r3, [r2]	@ movhi
	ldr	r2, .L943+8
	strh	r3, [r2]	@ movhi
	ldrh	r2, [r4]
	ldr	r3, .L943+12
	lsls	r2, r2, #1
	ldr	r0, [r3]
	bl	ftl_memset
	ldrh	r3, [r4]
	movs	r2, #12
	movs	r1, #255
	muls	r2, r3, r2
	ldr	r3, .L943+16
	ldr	r0, [r3]
	bl	ftl_memset
	pop	{r4, lr}
	b	FtlGcBufInit
.L944:
	.align	2
.L943:
	.word	.LANCHOR112
	.word	.LANCHOR54
	.word	.LANCHOR113
	.word	.LANCHOR111
	.word	.LANCHOR114
	.size	FtlGcPageVarInit, .-FtlGcPageVarInit
	.section	.text.idb_init,"ax",%progbits
	.align	1
	.global	idb_init
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	idb_init, %function
idb_init:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r3, lr}
	mov	r2, #262144
	movs	r1, #0
	ldr	r0, .L946
	bl	ftl_memset
	movs	r0, #0
	pop	{r3, pc}
.L947:
	.align	2
.L946:
	.word	idb_buf
	.size	idb_init, .-idb_init
	.section	.text.NandcXferData,"ax",%progbits
	.align	1
	.global	NandcXferData
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	NandcXferData, %function
NandcXferData:
	@ args = 4, pretend = 0, frame = 72
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, r8, r10, lr}
	sub	sp, sp, #84
	ldr	r6, [sp, #112]
	mov	r10, r3
	mov	r8, r0
	mov	r4, r1
	ldr	r3, .L970
	mov	r7, r2
	ldr	r5, [r3, r0, lsl #3]
	cbnz	r6, .L949
	add	r6, sp, #16
	movs	r2, #64
	movs	r1, #255
	add	r0, sp, #16
	bl	ftl_memset
.L949:
	mov	r1, r4
	mov	r0, r8
	str	r6, [sp, #4]
	movs	r3, #0
	str	r10, [sp]
	mov	r2, r7
	bl	NandcXferStart
	mov	r1, r4
	mov	r0, r8
	bl	NandcXferComp
	cmp	r4, #0
	bne	.L963
	ldr	r1, .L970+4
	lsr	ip, r7, #1
	ldr	r8, .L970+12
	mov	r2, r4
	mov	r0, r4
	ldr	r3, [r1]
	cmp	r3, #25
	mov	r3, r6
	ite	cc
	movcc	lr, #64
	movcs	lr, #128
.L952:
	cmp	r0, ip
	add	r3, r3, #4
	add	r6, lr, r2
	bcc	.L953
	ldr	r3, .L970+8
	lsrs	r2, r7, #2
	ldr	r7, [r1]
	movs	r1, #0
	mov	r0, r1
	ldr	r6, [r3]
.L954:
	cmp	r1, r2
	bcs	.L950
	cbnz	r7, .L960
.L950:
	movs	r3, #0
	str	r3, [r5, #16]
	ldr	r3, .L970+8
	ldr	r3, [r3]
	cmp	r3, #5
	bls	.L948
	cbnz	r4, .L948
	ldr	r3, [r5]
	and	r2, r3, #139264
	cmp	r2, #139264
	ittt	eq
	moveq	r0, #-1
	orreq	r3, r3, #131072
	streq	r3, [r5]
.L948:
	add	sp, sp, #84
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r10, pc}
.L953:
	bic	r10, r2, #3
	ldr	r2, [r8, #4]
	adds	r0, r0, #1
	ldr	r2, [r2, r10]
	strb	r2, [r3, #-4]
	lsr	r10, r2, #8
	strb	r10, [r3, #-3]
	lsr	r10, r2, #16
	lsrs	r2, r2, #24
	strb	r10, [r3, #-2]
	strb	r2, [r3, #-1]
	mov	r2, r6
	b	.L952
.L960:
	add	r3, r1, #8
	ldr	r3, [r5, r3, lsl #2]
	str	r3, [sp, #12]
	ldr	r3, [sp, #12]
	lsls	r3, r3, #29
	bmi	.L966
	ldr	r3, [sp, #12]
	ubfx	r3, r3, #15, #1
	cmp	r3, #0
	bne	.L966
	cmp	r6, #5
	bls	.L956
	ldr	r3, [sp, #12]
	ubfx	ip, r3, #3, #5
	ldr	r3, [sp, #12]
	ubfx	r8, r3, #27, #1
	ldr	r3, [sp, #12]
	ldr	lr, [sp, #12]
	orr	ip, ip, r8, lsl #5
	ubfx	r3, r3, #16, #5
	ubfx	lr, lr, #29, #1
	orr	r3, r3, lr, lsl #5
	cmp	ip, r3
	ldr	r3, [sp, #12]
	itete	hi
	ldrhi	ip, [sp, #12]
	ldrls	ip, [sp, #12]
	ubfxhi	r3, r3, #3, #5
	ubfxls	r3, r3, #16, #5
	ite	hi
	ubfxhi	ip, ip, #27, #1
	ubfxls	ip, ip, #29, #1
.L969:
	orr	r3, r3, ip, lsl #5
.L958:
	cmp	r0, r3
	it	cc
	movcc	r0, r3
.L955:
	adds	r1, r1, #1
	b	.L954
.L956:
	cmp	r6, #3
	bls	.L958
	ldr	r3, [sp, #12]
	ubfx	ip, r3, #3, #5
	ldr	r3, [sp, #12]
	ubfx	r8, r3, #28, #1
	ldr	r3, [sp, #12]
	ldr	lr, [sp, #12]
	orr	ip, ip, r8, lsl #5
	ubfx	r3, r3, #16, #5
	ubfx	lr, lr, #30, #1
	orr	r3, r3, lr, lsl #5
	cmp	ip, r3
	ldr	r3, [sp, #12]
	itete	hi
	ldrhi	ip, [sp, #12]
	ldrls	ip, [sp, #12]
	ubfxhi	r3, r3, #3, #5
	ubfxls	r3, r3, #16, #5
	ite	hi
	ubfxhi	ip, ip, #28, #1
	ubfxls	ip, ip, #30, #1
	b	.L969
.L966:
	mov	r0, #-1
	b	.L955
.L963:
	movs	r0, #0
	b	.L950
.L971:
	.align	2
.L970:
	.word	.LANCHOR0
	.word	.LANCHOR32
	.word	.LANCHOR34
	.word	.LANCHOR35
	.size	NandcXferData, .-NandcXferData
	.section	.text.FlashReadRawPage,"ax",%progbits
	.align	1
	.global	FlashReadRawPage
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	FlashReadRawPage, %function
FlashReadRawPage:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r0, r1, r4, r5, r6, r7, r8, lr}
	mov	r8, r3
	ldr	r3, .L974
	mov	r6, r1
	mov	r7, r2
	mov	r4, r0
	ldrb	r5, [r3, #9]	@ zero_extendqisi2
	cbnz	r0, .L973
	ldr	r3, .L974+4
	ldr	r2, .L974+8
	ldrb	r3, [r3]	@ zero_extendqisi2
	ldr	r0, [r2]
	muls	r0, r3, r0
	cmp	r0, r1
	it	hi
	movhi	r5, #4
.L973:
	mov	r0, r4
	bl	NandcWaitFlashReady
	mov	r0, r4
	bl	NandcFlashCs
	mov	r1, r6
	mov	r0, r4
	bl	FlashReadCmd
	mov	r0, r4
	bl	NandcWaitFlashReady
	mov	r3, r7
	mov	r2, r5
	str	r8, [sp]
	movs	r1, #0
	mov	r0, r4
	bl	NandcXferData
	mov	r1, r0
	mov	r0, r4
	bl	NandcFlashDeCs
	mov	r0, r1
	add	sp, sp, #8
	@ sp needed
	pop	{r4, r5, r6, r7, r8, pc}
.L975:
	.align	2
.L974:
	.word	.LANCHOR31
	.word	.LANCHOR3
	.word	.LANCHOR4
	.size	FlashReadRawPage, .-FlashReadRawPage
	.section	.text.FlashDdrTunningRead,"ax",%progbits
	.align	1
	.global	FlashDdrTunningRead
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	FlashDdrTunningRead, %function
FlashDdrTunningRead:
	@ args = 4, pretend = 0, frame = 24
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, r8, r10, fp, lr}
	mov	r7, r3
	ldr	r3, .L1001
	sub	sp, sp, #24
	str	r0, [sp, #8]
	ldr	r3, [r3]
	str	r1, [sp, #12]
	str	r2, [sp, #4]
	ldr	r3, [r3, #304]
	str	r3, [sp, #20]
	ldr	r3, .L1001+4
	ldr	r3, [r3]
	cmp	r3, #8
	ldr	r3, [sp, #56]
	ite	cc
	movcc	fp, #6
	movcs	fp, #12
	cmp	r3, #0
	beq	.L990
	movs	r0, #1
	ldr	r4, .L1001+8
	bl	FlashSetInterfaceMode
	movs	r0, #1
	bl	NandcSetMode
	ldr	r0, [sp, #8]
	bl	FlashReset
	mov	r3, r7
	ldr	r2, [sp, #4]
	ldr	r1, [sp, #12]
	ldr	r0, [sp, #8]
	bl	FlashReadRawPage
	mov	r6, r0
	ldrb	r0, [r4]	@ zero_extendqisi2
	bl	FlashSetInterfaceMode
	ldrb	r0, [r4]	@ zero_extendqisi2
	bl	NandcSetMode
	adds	r3, r6, #1
	bne	.L979
.L988:
	mov	r6, #-1
.L976:
	mov	r0, r6
	add	sp, sp, #24
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r10, fp, pc}
.L979:
	mov	r2, r6
	ldr	r1, [sp, #12]
	ldr	r0, .L1001+12
	bl	printf
	ldr	r2, .L1001+16
	ldr	r3, [r2]
	adds	r3, r3, #1
	cmp	r3, #2048
	bcs	.L981
	str	r3, [r2]
	b	.L976
.L981:
	movs	r7, #0
	str	r7, [r2]
	str	r7, [sp, #4]
.L978:
	mov	r10, #0
	mov	r8, #-1
	mov	r5, r10
	mov	r4, r10
	str	r10, [sp, #16]
.L986:
	uxtb	r0, fp
	bl	NandcSetDdrPara
	mov	r3, r7
	ldr	r2, [sp, #4]
	ldr	r1, [sp, #12]
	ldr	r0, [sp, #8]
	bl	FlashReadRawPage
	adds	r3, r6, #1
	cmp	r0, r3
	bhi	.L982
	cmp	r0, #2
	bhi	.L992
	adds	r4, r4, #1
	cmp	r4, #9
	bls	.L992
	mov	r3, r5
	mov	r6, r0
	sub	r5, fp, r4
	mov	r8, #0
.L984:
	ldr	r2, [sp, #16]
	cmp	r4, r2
	it	ls
	movls	r5, r3
.L985:
	cbz	r5, .L987
	mov	r1, r5
	ldr	r0, .L1001+20
	bl	printf
	uxtb	r0, r5
	bl	NandcSetDdrPara
.L987:
	cmp	r8, #0
	beq	.L976
	ldr	r2, [sp, #12]
	ldr	r1, [sp, #8]
	ldr	r0, .L1001+24
	bl	printf
	ldr	r3, [sp, #56]
	cmp	r3, #0
	beq	.L988
	ldr	r3, [sp, #20]
	ubfx	r0, r3, #8, #8
	bl	NandcSetDdrPara
	b	.L976
.L990:
	mov	r6, #1024
	b	.L978
.L982:
	ldr	r3, [sp, #16]
	cmp	r4, r3
	bls	.L993
	cmp	r4, #7
	sub	r5, r10, r4
	bhi	.L985
	str	r4, [sp, #16]
.L993:
	movs	r4, #0
	b	.L983
.L992:
	mov	r8, #0
	mov	r10, fp
	mov	r6, r0
	mov	r7, r8
	str	r8, [sp, #4]
.L983:
	add	fp, fp, #2
	cmp	fp, #69
	bls	.L986
	mov	r3, r5
	mov	r5, r10
	b	.L984
.L1002:
	.align	2
.L1001:
	.word	.LANCHOR19
	.word	.LANCHOR34
	.word	.LANCHOR25
	.word	.LC9
	.word	.LANCHOR144
	.word	.LC10
	.word	.LC11
	.size	FlashDdrTunningRead, .-FlashDdrTunningRead
	.section	.text.FlashReadPage,"ax",%progbits
	.align	1
	.global	FlashReadPage
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	FlashReadPage, %function
FlashReadPage:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r0, r1, r4, r5, r6, r7, r8, r10, fp, lr}
	mov	r7, r2
	mov	r5, r0
	mov	r6, r1
	mov	r8, r3
	bl	FlashReadRawPage
	adds	r2, r0, #1
	mov	r4, r0
	bne	.L1004
	ldr	r10, .L1022+20
	ldrb	fp, [r10]	@ zero_extendqisi2
	cmp	fp, #0
	bne	.L1005
.L1007:
	ldr	r3, .L1022
	ldrb	r3, [r3]	@ zero_extendqisi2
	cbz	r3, .L1004
	ldr	r3, .L1022+4
	mov	r1, r6
	mov	r2, r7
	mov	r0, r5
	ldr	r3, [r3]
	ldr	r10, [r3, #304]
	movs	r3, #1
	str	r3, [sp]
	mov	r3, r8
	bl	FlashDdrTunningRead
	adds	r1, r0, #1
	mov	r4, r0
	beq	.L1008
	ldr	r3, .L1022+8
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r0, r3, lsr #1
	bls	.L1004
.L1008:
	ubfx	r0, r10, #8, #8
	bl	NandcSetDdrPara
	b	.L1004
.L1005:
	movs	r3, #0
	mov	r2, r7
	strb	r3, [r10]
	mov	r1, r6
	mov	r3, r8
	mov	r0, r5
	bl	FlashReadRawPage
	adds	r3, r0, #1
	strb	fp, [r10]
	beq	.L1007
	mov	r4, r0
.L1004:
	ldr	r10, .L1022+24
	ldr	fp, [r10]
	cmp	fp, #0
	beq	.L1003
	adds	r2, r4, #1
	bne	.L1003
	mov	r3, r8
	mov	r2, r7
	mov	r1, r6
	mov	r0, r5
	blx	fp
	mov	r3, r6
	mov	r4, r0
	mov	r1, r0
	mov	r2, r5
	ldr	r0, .L1022+12
	bl	printf
	adds	r3, r4, #1
	bne	.L1003
	ldr	r3, .L1022+16
	ldrb	r3, [r3]	@ zero_extendqisi2
	cbz	r3, .L1003
	mov	r0, r5
	bl	flash_enter_slc_mode
	ldr	r4, [r10]
	mov	r3, r8
	mov	r2, r7
	mov	r1, r6
	mov	r0, r5
	blx	r4
	mov	r4, r0
	mov	r0, r5
	bl	flash_exit_slc_mode
.L1003:
	mov	r0, r4
	add	sp, sp, #8
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r10, fp, pc}
.L1023:
	.align	2
.L1022:
	.word	.LANCHOR30
	.word	.LANCHOR19
	.word	.LANCHOR33
	.word	.LC12
	.word	.LANCHOR16
	.word	.LANCHOR6
	.word	.LANCHOR145
	.size	FlashReadPage, .-FlashReadPage
	.section	.text.FlashDdrParaScan,"ax",%progbits
	.align	1
	.global	FlashDdrParaScan
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	FlashDdrParaScan, %function
FlashDdrParaScan:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r0, r1, r4, r5, r6, r7, r8, lr}
	mov	r6, r0
	ldr	r4, .L1035
	movs	r5, #0
	mov	r7, r1
	ldrb	r0, [r4]	@ zero_extendqisi2
	bl	FlashSetInterfaceMode
	ldrb	r0, [r4]	@ zero_extendqisi2
	bl	NandcSetMode
	mov	r3, r5
	mov	r2, r5
	str	r5, [sp]
	mov	r1, r7
	mov	r0, r6
	bl	FlashDdrTunningRead
	mov	r3, r5
	mov	r2, r5
	mov	r8, r0
	mov	r1, r7
	mov	r0, r6
	ldr	r5, .L1035+4
	bl	FlashReadRawPage
	adds	r0, r0, #1
	beq	.L1025
	cmp	r8, #-1
	bne	.L1026
.L1025:
	ldrb	r3, [r4]	@ zero_extendqisi2
	lsls	r3, r3, #31
	bpl	.L1026
	movs	r0, #1
	bl	FlashSetInterfaceMode
	movs	r0, #1
	bl	NandcSetMode
	movs	r3, #0
.L1034:
	movs	r0, #0
	strb	r3, [r5]
	add	sp, sp, #8
	@ sp needed
	pop	{r4, r5, r6, r7, r8, pc}
.L1026:
	movs	r3, #1
	b	.L1034
.L1036:
	.align	2
.L1035:
	.word	.LANCHOR25
	.word	.LANCHOR30
	.size	FlashDdrParaScan, .-FlashDdrParaScan
	.section	.text.ToshibaReadRetrial,"ax",%progbits
	.align	1
	.global	ToshibaReadRetrial
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	ToshibaReadRetrial, %function
ToshibaReadRetrial:
	@ args = 0, pretend = 0, frame = 24
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, r8, r10, fp, lr}
	sub	sp, sp, #24
	mov	r6, r0
	str	r2, [sp, #12]
	mov	fp, r3
	str	r1, [sp, #20]
	bl	NandcWaitFlashReady
	ldr	r3, .L1064
	ldr	r2, .L1064+4
	ldr	r4, [r3, r6, lsl #3]
	add	r3, r3, r6, lsl #3
	str	r2, [sp, #16]
	ldrb	r7, [r3, #4]	@ zero_extendqisi2
	ldrb	r3, [r2]	@ zero_extendqisi2
	add	r5, r7, #8
	subs	r3, r3, #67
	add	r5, r4, r5, lsl #8
	cmp	r3, #1
	bls	.L1054
	ldr	r3, .L1064+8
	ldrb	r3, [r3]	@ zero_extendqisi2
	cbz	r3, .L1055
	movs	r0, #0
	bl	NandcSetDdrMode
	movs	r3, #1
.L1055:
	str	r3, [sp, #8]
	add	r3, r4, r7, lsl #8
	movs	r2, #92
	str	r2, [r3, #2056]
	movs	r2, #197
	str	r2, [r3, #2056]
.L1038:
	mov	r8, #1
	mov	r3, #-1
	str	r3, [sp, #4]
.L1040:
	ldr	r3, .L1064+12
	ldrb	r3, [r3]	@ zero_extendqisi2
	adds	r3, r3, #1
	cmp	r8, r3
	bcc	.L1049
	ldr	r10, [sp, #4]
.L1048:
	ldr	r3, [sp, #16]
	movs	r1, #0
	mov	r0, r5
	ldrb	r2, [r3]	@ zero_extendqisi2
	subs	r2, r2, #67
	cmp	r2, #1
	bhi	.L1050
	bl	SandiskSetRRPara
.L1051:
	add	r4, r4, r7, lsl #8
	movs	r2, #255
	str	r2, [r4, #2056]
	ldr	r2, .L1064+16
	ldrb	r2, [r2]	@ zero_extendqisi2
	add	r2, r2, r2, lsl #1
	cmp	r10, r2, asr #2
	bcc	.L1052
	cmp	r10, #-1
	it	ne
	movne	r10, #256
.L1052:
	mov	r0, r6
	bl	NandcWaitFlashReady
	ldr	r3, [sp, #8]
	cbz	r3, .L1037
	movs	r0, #4
	bl	NandcSetDdrMode
.L1037:
	mov	r0, r10
	add	sp, sp, #24
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r10, fp, pc}
.L1054:
	movs	r3, #0
	str	r3, [sp, #8]
	b	.L1038
.L1049:
	ldr	r3, [sp, #16]
	mov	r0, r5
	uxtb	r1, r8
	ldrb	r3, [r3]	@ zero_extendqisi2
	subs	r3, r3, #67
	cmp	r3, #1
	bhi	.L1041
	bl	SandiskSetRRPara
.L1042:
	ldr	r3, [sp, #16]
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, #34
	bne	.L1043
	ldr	r3, .L1064+12
	ldrb	r3, [r3]	@ zero_extendqisi2
	subs	r3, r3, #3
	cmp	r8, r3
	ittt	eq
	addeq	r3, r4, r7, lsl #8
	moveq	r2, #179
	streq	r2, [r3, #2056]
.L1043:
	add	r3, r4, r7, lsl #8
	movs	r2, #38
	str	r2, [r3, #2056]
	movs	r2, #93
	str	r2, [r3, #2056]
	ldr	r3, [sp, #8]
	cbz	r3, .L1044
	movs	r0, #4
	bl	NandcSetDdrMode
	mov	r3, fp
	ldr	r2, [sp, #12]
	ldr	r1, [sp, #20]
	mov	r0, r6
	bl	FlashReadRawPage
	mov	r10, r0
	movs	r0, #0
	bl	NandcSetDdrMode
.L1045:
	cmp	r10, #-1
	beq	.L1046
	ldr	r2, .L1064+16
	ldr	r3, [sp, #4]
	ldrb	r2, [r2]	@ zero_extendqisi2
	cmp	r3, #-1
	it	eq
	moveq	r3, r10
	str	r3, [sp, #4]
	add	r2, r2, r2, lsl #1
	cmp	r10, r2, asr #2
	bcc	.L1048
	mov	fp, #0
	str	fp, [sp, #12]
.L1046:
	add	r8, r8, #1
	b	.L1040
.L1041:
	bl	ToshibaSetRRPara
	b	.L1042
.L1044:
	mov	r3, fp
	ldr	r2, [sp, #12]
	ldr	r1, [sp, #20]
	mov	r0, r6
	bl	FlashReadRawPage
	mov	r10, r0
	b	.L1045
.L1050:
	bl	ToshibaSetRRPara
	b	.L1051
.L1065:
	.align	2
.L1064:
	.word	.LANCHOR0
	.word	.LANCHOR10
	.word	.LANCHOR30
	.word	.LANCHOR146
	.word	.LANCHOR33
	.size	ToshibaReadRetrial, .-ToshibaReadRetrial
	.section	.text.SamsungReadRetrial,"ax",%progbits
	.align	1
	.global	SamsungReadRetrial
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	SamsungReadRetrial, %function
SamsungReadRetrial:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, r8, r10, fp, lr}
	mov	r7, r0
	mov	r10, r2
	mov	r8, r3
	mov	fp, r1
	movs	r6, #1
	bl	NandcWaitFlashReady
	ldr	r2, .L1079
	mov	r4, #-1
	add	r3, r2, r7, lsl #3
	ldrb	r5, [r3, #4]	@ zero_extendqisi2
	add	r3, r5, #8
	ldr	r5, [r2, r7, lsl #3]
	add	r5, r5, r3, lsl #8
.L1067:
	ldr	r3, .L1079+4
	ldrb	r3, [r3]	@ zero_extendqisi2
	adds	r3, r3, #1
	cmp	r6, r3
	bcc	.L1071
.L1070:
	movs	r1, #0
	mov	r0, r5
	bl	SamsungSetRRPara
	ldr	r3, .L1079+8
	ldrb	r3, [r3]	@ zero_extendqisi2
	add	r3, r3, r3, lsl #1
	cmp	r4, r3, asr #2
	bcc	.L1066
	adds	r3, r4, #1
	it	ne
	movne	r4, #256
.L1066:
	mov	r0, r4
	pop	{r4, r5, r6, r7, r8, r10, fp, pc}
.L1071:
	uxtb	r1, r6
	mov	r0, r5
	bl	SamsungSetRRPara
	mov	r2, r10
	mov	r3, r8
	mov	r1, fp
	mov	r0, r7
	bl	FlashReadRawPage
	adds	r2, r0, #1
	beq	.L1068
	ldr	r3, .L1079+8
	cmp	r4, #-1
	it	eq
	moveq	r4, r0
	ldrb	r3, [r3]	@ zero_extendqisi2
	add	r3, r3, r3, lsl #1
	cmp	r0, r3, asr #2
	bcc	.L1074
	mov	r8, #0
	mov	r10, r8
.L1068:
	adds	r6, r6, #1
	b	.L1067
.L1074:
	mov	r4, r0
	b	.L1070
.L1080:
	.align	2
.L1079:
	.word	.LANCHOR0
	.word	.LANCHOR146
	.word	.LANCHOR33
	.size	SamsungReadRetrial, .-SamsungReadRetrial
	.section	.text.MicronReadRetrial,"ax",%progbits
	.align	1
	.global	MicronReadRetrial
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	MicronReadRetrial, %function
MicronReadRetrial:
	@ args = 0, pretend = 0, frame = 32
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, r8, r10, fp, lr}
	mov	r7, r3
	ldr	r3, .L1106
	sub	sp, sp, #40
	mov	r5, r0
	str	r2, [sp, #16]
	ldrb	r2, [r3]	@ zero_extendqisi2
	ldr	r3, .L1106+4
	str	r1, [sp, #28]
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1082
	add	r2, r2, r2, lsl #1
	asrs	r3, r2, #2
.L1105:
.L1083:
	mov	r8, #0
	str	r3, [sp, #12]
	mov	r6, r8
.L1093:
	mov	r0, r5
	mov	r10, #0
	bl	NandcWaitFlashReady
	ldr	r3, .L1106+8
	mov	r4, #-1
	ldr	r2, [r3, r5, lsl #3]
	add	r3, r3, r5, lsl #3
	ldrb	fp, [r3, #4]	@ zero_extendqisi2
	str	r2, [sp, #24]
	lsl	r3, fp, #8
	str	r3, [sp, #32]
.L1084:
	ldr	r3, .L1106+12
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r10, r3
	bcc	.L1088
.L1087:
	ldr	r3, [sp, #24]
	movs	r0, #200
	add	fp, r3, fp, lsl #8
	movs	r3, #239
	str	r3, [fp, #2056]
	movs	r3, #137
	str	r3, [fp, #2052]
	bl	udelay
	ldr	r3, [sp, #12]
	str	r6, [fp, #2048]
	str	r6, [fp, #2048]
	cmp	r4, r3
	str	r6, [fp, #2048]
	str	r6, [fp, #2048]
	bcc	.L1089
	adds	r1, r4, #1
	mov	r3, r10
	it	ne
	movne	r4, #256
	ldr	r2, [sp, #28]
	str	r4, [sp]
	mov	r1, r10
	ldr	r0, .L1106+16
	bl	printf
	cmp	r8, #0
	bne	.L1091
	ldr	r3, .L1106+4
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1081
	adds	r2, r4, #1
	bne	.L1081
	movs	r1, #3
	mov	r0, r5
	bl	micron_auto_read_calibration_config
	mov	r8, #1
	b	.L1093
.L1082:
	ldr	r3, .L1106+20
	smull	r2, r3, r2, r3
	b	.L1105
.L1088:
	ldr	r2, [sp, #32]
	movs	r0, #200
	ldr	r3, [sp, #24]
	add	r3, r3, r2
	movs	r2, #239
	str	r2, [r3, #2056]
	movs	r2, #137
	str	r2, [r3, #2052]
	str	r3, [sp, #36]
	bl	udelay
	add	r3, r10, #1
	ldr	r1, [sp, #28]
	mov	r2, r3
	str	r3, [sp, #20]
	ldr	r3, [sp, #36]
	mov	r0, r5
	str	r2, [r3, #2048]
	str	r6, [r3, #2048]
	ldr	r2, [sp, #16]
	str	r6, [r3, #2048]
	str	r6, [r3, #2048]
	mov	r3, r7
	bl	FlashReadRawPage
	adds	r3, r0, #1
	beq	.L1085
	ldr	r3, [sp, #12]
	cmp	r4, #-1
	it	eq
	moveq	r4, r0
	cmp	r0, r3
	bcc	.L1095
	movs	r7, #0
	str	r7, [sp, #16]
.L1085:
	ldr	r10, [sp, #20]
	b	.L1084
.L1095:
	movs	r7, #0
	mov	r4, r0
	str	r7, [sp, #16]
	b	.L1087
.L1091:
	movs	r1, #0
	mov	r0, r5
	bl	micron_auto_read_calibration_config
	adds	r3, r4, #1
	it	ne
	movne	r4, #256
.L1081:
	mov	r0, r4
	add	sp, sp, #40
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r10, fp, pc}
.L1089:
	cmp	r8, #0
	beq	.L1081
	movs	r1, #0
	mov	r0, r5
	bl	micron_auto_read_calibration_config
	mov	r4, #256
	b	.L1081
.L1107:
	.align	2
.L1106:
	.word	.LANCHOR33
	.word	.LANCHOR16
	.word	.LANCHOR0
	.word	.LANCHOR146
	.word	.LC13
	.word	1431655766
	.size	MicronReadRetrial, .-MicronReadRetrial
	.section	.text.HynixReadRetrial,"ax",%progbits
	.align	1
	.global	HynixReadRetrial
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	HynixReadRetrial, %function
HynixReadRetrial:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r0, r1, r4, r5, r6, r7, r8, r10, fp, lr}
	mov	r10, r3
	ldr	r4, .L1125
	mov	r8, #0
	mov	r6, #-1
	mov	fp, r2
	mov	r7, r0
	str	r1, [sp, #4]
	ldrb	r3, [r4, #2]	@ zero_extendqisi2
	adds	r2, r4, r0
	ldrb	r5, [r2, #12]	@ zero_extendqisi2
	str	r3, [sp]
	ldr	r3, .L1125+4
	ldr	r3, [r3]
	ldrb	r3, [r3, #19]	@ zero_extendqisi2
	subs	r3, r3, #7
	cmp	r3, #1
	it	ls
	ldrbls	r5, [r2, #20]	@ zero_extendqisi2
	bl	NandcWaitFlashReady
.L1110:
	ldr	r3, [sp]
	cmp	r8, r3
	bcc	.L1115
.L1114:
	ldr	r3, .L1125+4
	add	r4, r4, r7
	ldr	r3, [r3]
	ldrb	r3, [r3, #19]	@ zero_extendqisi2
	subs	r3, r3, #7
	cmp	r3, #1
	ldr	r3, .L1125+8
	ite	ls
	strbls	r5, [r4, #20]
	strbhi	r5, [r4, #12]
	ldrb	r3, [r3]	@ zero_extendqisi2
	add	r3, r3, r3, lsl #1
	cmp	r6, r3, asr #2
	bcc	.L1108
	adds	r3, r6, #1
	it	ne
	movne	r6, #256
.L1108:
	mov	r0, r6
	add	sp, sp, #8
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r10, fp, pc}
.L1115:
	ldr	r3, [sp]
	adds	r5, r5, #1
	uxtb	r5, r5
	ldr	r2, .L1125+12
	ldrb	r1, [r4, #1]	@ zero_extendqisi2
	mov	r0, r7
	cmp	r3, r5
	it	ls
	movls	r5, #0
	mov	r3, r5
	bl	HynixSetRRPara
	mov	r2, fp
	mov	r3, r10
	ldr	r1, [sp, #4]
	mov	r0, r7
	bl	FlashReadRawPage
	adds	r2, r0, #1
	beq	.L1112
	ldr	r3, .L1125+8
	cmp	r6, #-1
	it	eq
	moveq	r6, r0
	ldrb	r3, [r3]	@ zero_extendqisi2
	add	r3, r3, r3, lsl #1
	cmp	r0, r3, asr #2
	bcc	.L1119
	mov	r10, #0
	mov	fp, r10
.L1112:
	add	r8, r8, #1
	b	.L1110
.L1119:
	mov	r6, r0
	b	.L1114
.L1126:
	.align	2
.L1125:
	.word	.LANCHOR20
	.word	.LANCHOR7
	.word	.LANCHOR33
	.word	.LANCHOR20+4
	.size	HynixReadRetrial, .-HynixReadRetrial
	.section	.text.samsung_read_retrial,"ax",%progbits
	.align	1
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	samsung_read_retrial, %function
samsung_read_retrial:
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, r8, r10, fp, lr}
	sub	sp, sp, #24
	mov	r8, r0
	mov	r10, r2
	mov	r7, r3
	str	r1, [sp, #16]
	bl	NandcWaitFlashReady
	ldr	r3, .L1152
	ldr	r2, [r3, r8, lsl #3]
	add	r3, r3, r8, lsl #3
	str	r2, [sp, #12]
	ldr	r2, .L1152+4
	ldrb	r3, [r3, #4]	@ zero_extendqisi2
	ldrb	r2, [r2]	@ zero_extendqisi2
	cmp	r2, #0
	bne	.L1128
	lsls	r3, r3, #8
	mov	r4, #-1
	movs	r6, #1
	str	r3, [sp, #20]
	ldr	r2, [sp, #20]
	ldr	r3, [sp, #12]
	adds	r5, r3, r2
.L1132:
	movs	r3, #239
	mov	fp, #0
	str	r3, [r5, #2056]
	movs	r3, #141
	str	r3, [r5, #2052]
	mov	r2, r10
	ldr	r3, .L1152+8
	mov	r0, r8
	ldr	r1, [sp, #16]
	ldrsb	r3, [r6, r3]
	str	r3, [r5, #2048]
	mov	r3, r7
	str	fp, [r5, #2048]
	str	fp, [r5, #2048]
	str	fp, [r5, #2048]
	bl	FlashReadRawPage
	adds	r1, r0, #1
	beq	.L1129
	ldr	r3, .L1152+12
	cmp	r4, #-1
	it	eq
	moveq	r4, r0
	ldrb	r3, [r3]	@ zero_extendqisi2
	add	r3, r3, r3, lsl #1
	cmp	r0, r3, asr #2
	bcc	.L1140
	mov	r7, fp
	mov	r10, fp
.L1129:
	adds	r6, r6, #1
	cmp	r6, #26
	bne	.L1132
.L1131:
	ldr	r2, [sp, #20]
	ldr	r3, [sp, #12]
	add	r3, r3, r2
	movs	r2, #239
	str	r2, [r3, #2056]
	movs	r3, #141
.L1151:
	str	r3, [r5, #2052]
	movs	r3, #0
	str	r3, [r5, #2048]
	str	r3, [r5, #2048]
	str	r3, [r5, #2048]
	str	r3, [r5, #2048]
	ldr	r3, .L1152+12
	ldrb	r3, [r3]	@ zero_extendqisi2
	add	r3, r3, r3, lsl #1
	cmp	r4, r3, asr #2
	bcc	.L1138
	adds	r3, r4, #1
	ldr	r2, [sp, #16]
	it	ne
	movne	r4, #256
	mov	r3, r6
	str	r4, [sp]
	mov	r1, r6
	ldr	r0, .L1152+16
	bl	printf
.L1138:
	mov	r0, r8
	bl	NandcWaitFlashReady
	mov	r0, r4
	add	sp, sp, #24
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r10, fp, pc}
.L1140:
	mov	r4, r0
	b	.L1131
.L1128:
	lsls	r3, r3, #8
	ldr	fp, .L1152+20
	mov	r4, #-1
	str	r3, [sp, #20]
	movs	r6, #1
	ldr	r3, [sp, #12]
	ldr	r2, [sp, #20]
	adds	r5, r3, r2
.L1137:
	movs	r3, #239
	mov	r2, r10
	str	r3, [r5, #2056]
	movs	r3, #137
	str	r3, [r5, #2052]
	mov	r0, r8
	ldrb	r3, [fp, #4]	@ zero_extendqisi2
	ldr	r1, [sp, #16]
	str	r3, [r5, #2048]
	ldrb	r3, [fp, #5]	@ zero_extendqisi2
	str	r3, [r5, #2048]
	ldrb	r3, [fp, #6]	@ zero_extendqisi2
	str	r3, [r5, #2048]
	ldrb	r3, [fp, #7]	@ zero_extendqisi2
	str	r3, [r5, #2048]
	mov	r3, r7
	bl	FlashReadRawPage
	adds	r2, r0, #1
	beq	.L1134
	ldr	r3, .L1152+12
	cmp	r4, #-1
	it	eq
	moveq	r4, r0
	ldrb	r3, [r3]	@ zero_extendqisi2
	add	r3, r3, r3, lsl #1
	cmp	r0, r3, asr #2
	bcc	.L1141
	movs	r7, #0
	mov	r10, r7
.L1134:
	adds	r6, r6, #1
	add	fp, fp, #4
	cmp	r6, #26
	bne	.L1137
.L1136:
	ldr	r2, [sp, #20]
	ldr	r3, [sp, #12]
	add	r3, r3, r2
	movs	r2, #239
	str	r2, [r3, #2056]
	movs	r3, #137
	b	.L1151
.L1141:
	mov	r4, r0
	b	.L1136
.L1153:
	.align	2
.L1152:
	.word	.LANCHOR0
	.word	.LANCHOR24
	.word	.LANCHOR147
	.word	.LANCHOR33
	.word	.LC14
	.word	.LANCHOR148
	.size	samsung_read_retrial, .-samsung_read_retrial
	.section	.text.FlashProgPage,"ax",%progbits
	.align	1
	.global	FlashProgPage
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	FlashProgPage, %function
FlashProgPage:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r0, r1, r4, r5, r6, r7, r8, lr}
	mov	r8, r3
	ldr	r3, .L1157
	mov	r5, r1
	mov	r7, r2
	mov	r4, r0
	ldrb	r6, [r3, #9]	@ zero_extendqisi2
	cbnz	r0, .L1155
	ldr	r3, .L1157+4
	ldr	r2, .L1157+8
	ldrb	r3, [r3]	@ zero_extendqisi2
	ldr	r1, [r2]
	muls	r1, r3, r1
	cmp	r1, r5
	bls	.L1155
	ldr	r3, .L1157+12
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, #0
	it	ne
	movne	r6, #4
.L1155:
	mov	r0, r4
	bl	NandcWaitFlashReady
	mov	r0, r4
	bl	NandcFlashCs
	mov	r1, r5
	mov	r0, r4
	bl	FlashProgFirstCmd
	mov	r3, r7
	mov	r2, r6
	str	r8, [sp]
	movs	r1, #1
	mov	r0, r4
	bl	NandcXferData
	mov	r1, r5
	mov	r0, r4
	bl	FlashProgSecondCmd
	mov	r0, r4
	bl	NandcWaitFlashReady
	mov	r1, r5
	mov	r0, r4
	bl	FlashReadStatus
	mov	r1, r0
	mov	r0, r4
	bl	NandcFlashDeCs
	and	r0, r1, #1
	add	sp, sp, #8
	@ sp needed
	pop	{r4, r5, r6, r7, r8, pc}
.L1158:
	.align	2
.L1157:
	.word	.LANCHOR31
	.word	.LANCHOR3
	.word	.LANCHOR4
	.word	.LANCHOR2
	.size	FlashProgPage, .-FlashProgPage
	.section	.text.FlashPageProgMsbFFData,"ax",%progbits
	.align	1
	.global	FlashPageProgMsbFFData
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	FlashPageProgMsbFFData, %function
FlashPageProgMsbFFData:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r3, r4, r5, r6, r7, r8, r10, lr}
	mov	r6, r0
	ldr	r3, .L1179
	mov	r7, r1
	mov	r4, r2
	ldrb	r3, [r3]	@ zero_extendqisi2
	cbz	r3, .L1160
	ldr	r3, .L1179+4
	ldr	r3, [r3]
	cbnz	r3, .L1159
.L1160:
	ldr	r5, .L1179+8
	ldr	r3, [r5]
	ldrb	r2, [r3, #19]	@ zero_extendqisi2
	subs	r3, r2, #5
	uxtb	r3, r3
	cmp	r3, #30
	bhi	.L1161
	ldr	r1, .L1179+12
	lsr	r3, r1, r3
	lsls	r3, r3, #31
	bmi	.L1162
.L1166:
	cmp	r2, #68
	bne	.L1159
.L1162:
	ldr	r10, .L1179+16
	ldr	r8, .L1179+20
.L1164:
	ldr	r3, [r5]
	ldrh	r3, [r3, #10]
	cmp	r3, r4
	bhi	.L1165
	pop	{r3, r4, r5, r6, r7, r8, r10, pc}
.L1165:
	ldrh	r2, [r10, r4, lsl #1]
	movw	r3, #65535
	cmp	r2, r3
	bne	.L1159
	mov	r2, #32768
	movs	r1, #255
	ldr	r0, [r8]
	bl	ftl_memset
	ldr	r3, [r8]
	adds	r1, r4, r7
	mov	r0, r6
	adds	r4, r4, #1
	uxth	r4, r4
	mov	r2, r3
	bl	FlashProgPage
	b	.L1164
.L1161:
	cmp	r2, #50
	bne	.L1166
	b	.L1162
.L1159:
	pop	{r3, r4, r5, r6, r7, r8, r10, pc}
.L1180:
	.align	2
.L1179:
	.word	.LANCHOR16
	.word	.LANCHOR29
	.word	.LANCHOR7
	.word	1073758215
	.word	.LANCHOR123
	.word	.LANCHOR149
	.size	FlashPageProgMsbFFData, .-FlashPageProgMsbFFData
	.section	.text.ftl_memcpy,"ax",%progbits
	.align	1
	.global	ftl_memcpy
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	ftl_memcpy, %function
ftl_memcpy:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	b	memcpy
	.size	ftl_memcpy, .-ftl_memcpy
	.section	.text.FlashReadIdbData,"ax",%progbits
	.align	1
	.global	FlashReadIdbData
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	FlashReadIdbData, %function
FlashReadIdbData:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r3, lr}
	mov	r2, #2048
	ldr	r1, .L1183
	bl	ftl_memcpy
	movs	r0, #0
	pop	{r3, pc}
.L1184:
	.align	2
.L1183:
	.word	.LANCHOR150
	.size	FlashReadIdbData, .-FlashReadIdbData
	.section	.text.FlashLoadPhyInfoInRam,"ax",%progbits
	.align	1
	.global	FlashLoadPhyInfoInRam
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	FlashLoadPhyInfoInRam, %function
FlashLoadPhyInfoInRam:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, r8, lr}
	movs	r6, #0
	ldr	r7, .L1193
	ldr	r5, .L1193+4
.L1188:
	ldrb	r2, [r7, #-1]	@ zero_extendqisi2
	mov	r1, r5
	mov	r0, r7
	lsl	r8, r6, #5
	bl	FlashMemCmp8
	mov	r4, r0
	cbnz	r0, .L1186
	ldr	r5, .L1193+8
	mov	r3, r4
	ldr	r2, .L1193+12
	add	r5, r5, r8
	ldrb	r0, [r5, #22]	@ zero_extendqisi2
	mov	r1, r2
.L1187:
	lsls	r6, r3, #5
	ldrb	r6, [r6, r2]	@ zero_extendqisi2
	cmp	r6, r0
	beq	.L1190
	adds	r3, r3, #1
	cmp	r3, #4
	bne	.L1187
.L1190:
	ldr	r6, .L1193+16
	add	r1, r1, r3, lsl #5
	movs	r2, #32
	ldr	r0, .L1193+20
	bl	ftl_memcpy
	movs	r2, #32
	mov	r1, r5
	mov	r0, r6
	bl	ftl_memcpy
	ldrh	r0, [r6, #10]
	bl	FlashBlockAlignInit
	b	.L1185
.L1186:
	adds	r6, r6, #1
	adds	r7, r7, #32
	cmp	r6, #86
	bne	.L1188
	mov	r4, #-1
.L1185:
	mov	r0, r4
	pop	{r4, r5, r6, r7, r8, pc}
.L1194:
	.align	2
.L1193:
	.word	.LANCHOR151+1
	.word	.LANCHOR22
	.word	.LANCHOR151
	.word	.LANCHOR152
	.word	.LANCHOR31
	.word	.LANCHOR8
	.size	FlashLoadPhyInfoInRam, .-FlashLoadPhyInfoInRam
	.section	.text.NandcCopy1KB,"ax",%progbits
	.align	1
	.global	NandcCopy1KB
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	NandcCopy1KB, %function
NandcCopy1KB:
	@ args = 4, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	cmp	r1, #1
	push	{r4, r5, r6, lr}
	mov	r4, r2
	add	r2, r0, #4096
	add	r6, r0, #512
	add	r0, r2, r4, lsl #9
	ldr	r5, [sp, #16]
	bne	.L1196
	cbz	r3, .L1197
	mov	r2, #1024
	mov	r1, r3
	bl	ftl_memcpy
.L1197:
	cbz	r5, .L1195
	ldrb	r2, [r5, #1]	@ zero_extendqisi2
	lsrs	r4, r4, #1
	ldrb	r3, [r5]	@ zero_extendqisi2
	add	r4, r4, r4, lsl #1
	lsls	r4, r4, #4
	orr	r3, r3, r2, lsl #8
	ldrb	r2, [r5, #2]	@ zero_extendqisi2
	orr	r3, r3, r2, lsl #16
	ldrb	r2, [r5, #3]	@ zero_extendqisi2
	orr	r3, r3, r2, lsl #24
	str	r3, [r6, r4]
	pop	{r4, r5, r6, pc}
.L1196:
	cbz	r3, .L1200
	mov	r1, r0
	mov	r2, #1024
	mov	r0, r3
	bl	ftl_memcpy
.L1200:
	cbz	r5, .L1195
	lsrs	r4, r4, #1
	add	r4, r4, r4, lsl #1
	lsls	r4, r4, #4
	ldr	r3, [r6, r4]
	strb	r3, [r5]
	lsrs	r2, r3, #8
	strb	r2, [r5, #1]
	lsrs	r2, r3, #16
	lsrs	r3, r3, #24
	strb	r2, [r5, #2]
	strb	r3, [r5, #3]
.L1195:
	pop	{r4, r5, r6, pc}
	.size	NandcCopy1KB, .-NandcCopy1KB
	.section	.text.FlashLoadPhyInfo,"ax",%progbits
	.align	1
	.global	FlashLoadPhyInfo
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	FlashLoadPhyInfo, %function
FlashLoadPhyInfo:
	@ args = 0, pretend = 0, frame = 24
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, r8, r10, fp, lr}
	movs	r3, #60
	sub	sp, sp, #24
	ldr	fp, .L1225+32
	movs	r4, #0
	movs	r7, #4
	strb	r3, [sp, #20]
	movs	r3, #40
	strb	r3, [sp, #21]
	movs	r3, #24
	strb	r3, [sp, #22]
	movs	r3, #16
	strb	r3, [sp, #23]
	mov	r0, r4
	ldr	r3, [fp]
	mov	r6, #-1
	ldr	r8, .L1225+36
	ldr	r10, .L1225+40
	str	r3, [sp, #4]
	ldr	r5, .L1225
	ldr	r3, [r8]
	str	r4, [r10]
	str	r3, [r5]
	bl	flash_enter_slc_mode
	str	r10, [sp, #12]
	mov	r10, r8
.L1212:
	mov	r8, #0
	adds	r3, r4, #1
	str	r3, [sp, #8]
.L1214:
	add	r3, sp, #20
	ldrb	r0, [r3, r8]	@ zero_extendqisi2
	bl	FlashBchSel
	movs	r3, #0
	ldr	r2, [r10]
	mov	r1, r4
	mov	r0, r3
	bl	FlashReadRawPage
	adds	r0, r0, #1
	bne	.L1213
	movs	r3, #0
	ldr	r2, [r10]
	ldr	r1, [sp, #8]
	mov	r0, r3
	bl	FlashReadRawPage
	adds	r0, r0, #1
	bne	.L1213
	add	r8, r8, #1
	cmp	r8, #4
	bne	.L1214
.L1215:
	ldr	r3, [sp, #4]
	subs	r7, r7, #1
	add	r4, r4, r3
	bne	.L1212
	mov	r0, r7
	b	.L1224
.L1216:
	movw	r1, #2036
	add	r0, r8, #12
	bl	js_hash
	ldr	r3, [r8, #8]
	cmp	r3, r0
	bne	.L1222
	ldr	r6, .L1225+4
	movs	r2, #32
	add	r1, r8, #160
	mov	r0, r6
	bl	ftl_memcpy
	ldr	r1, [r5]
	movs	r2, #32
	ldr	r0, .L1225+8
	adds	r1, r1, #192
	bl	ftl_memcpy
	ldr	r1, [r5]
	mov	r2, #852
	ldr	r0, .L1225+12
	adds	r1, r1, #224
	bl	ftl_memcpy
	ldrh	r0, [r6, #10]
	bl	FlashBlockAlignInit
	ldr	r6, [r5]
	mov	r0, r4
	ldr	r3, .L1225+16
	ldr	r1, [fp]
	ldr	r2, [r6, #1076]
	strb	r2, [r3]
	ldr	r3, [sp, #12]
	str	r4, [r3]
	bl	__aeabi_uidiv
	ldr	r3, .L1225+20
	adds	r0, r0, #1
	cmp	r0, #1
	itte	ls
	movls	r2, #2
	strls	r2, [r3]
	strhi	r0, [r3]
	ldrh	r2, [r6, #14]
	movs	r6, #0
	ldr	r3, .L1225+24
	strb	r2, [r3]
	b	.L1215
.L1222:
	mov	r6, #-1
	b	.L1215
.L1213:
	ldr	r8, [r5]
	ldr	r2, .L1225+28
	ldr	r3, [r8]
	cmp	r3, r2
	bne	.L1215
	cmp	r6, #0
	bne	.L1216
	ldr	r1, [fp]
	mov	r0, r4
	bl	__aeabi_uidiv
	ldr	r3, .L1225+20
	adds	r0, r0, #1
	str	r0, [r3]
	mov	r0, r6
.L1224:
	bl	flash_exit_slc_mode
	mov	r0, r6
	add	sp, sp, #24
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r10, fp, pc}
.L1226:
	.align	2
.L1225:
	.word	.LANCHOR153
	.word	.LANCHOR31
	.word	.LANCHOR8
	.word	.LANCHOR20
	.word	.LANCHOR30
	.word	.LANCHOR156
	.word	.LANCHOR157
	.word	1312902724
	.word	.LANCHOR4
	.word	.LANCHOR154
	.word	.LANCHOR155
	.size	FlashLoadPhyInfo, .-FlashLoadPhyInfo
	.section	.text.FlashSavePhyInfo,"ax",%progbits
	.align	1
	.global	FlashSavePhyInfo
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	FlashSavePhyInfo, %function
FlashSavePhyInfo:
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r0, r1, r2, r3, r4, r5, r6, r7, r8, r10, fp, lr}
	ldr	r6, .L1240
	ldr	r7, .L1240+4
	ldr	r3, [r6]
	ldr	r10, .L1240+64
	ldr	r8, .L1240+68
	str	r3, [r7]
	ldr	r3, .L1240+8
	ldrb	r0, [r3]	@ zero_extendqisi2
	bl	FlashBchSel
	mov	r2, #2048
	movs	r1, #0
	ldr	r0, [r6]
	bl	ftl_memset
	ldr	r0, [r7]
	movs	r2, #32
	ldr	r3, .L1240+12
	ldr	r1, .L1240+16
	str	r10, [r0]
	adds	r0, r0, #16
	ldrb	r3, [r3]	@ zero_extendqisi2
	strh	r3, [r0, #-4]	@ movhi
	ldr	r3, .L1240+20
	ldrb	r3, [r3]	@ zero_extendqisi2
	strh	r3, [r0, #-2]	@ movhi
	ldr	r3, .L1240+24
	ldrb	r3, [r3]	@ zero_extendqisi2
	str	r3, [r0, #1060]
	bl	ftl_memcpy
	ldr	r0, [r7]
	movs	r2, #8
	ldr	r1, .L1240+28
	adds	r0, r0, #80
	bl	ftl_memcpy
	ldr	r0, [r7]
	movs	r2, #32
	ldr	r1, .L1240+32
	adds	r0, r0, #96
	bl	ftl_memcpy
	ldr	r0, [r7]
	movs	r2, #32
	ldr	r1, .L1240+36
	adds	r0, r0, #160
	bl	ftl_memcpy
	ldr	r0, [r7]
	movs	r2, #32
	ldr	r1, .L1240+40
	adds	r0, r0, #192
	bl	ftl_memcpy
	ldr	r0, [r7]
	mov	r2, #852
	ldr	r1, .L1240+44
	adds	r0, r0, #224
	bl	ftl_memcpy
	ldr	r4, [r7]
	movw	r1, #2036
	add	r0, r4, #12
	bl	js_hash
	mov	r3, #1592
	str	r0, [r4, #8]
	str	r3, [r4, #4]
	movs	r0, #0
	ldr	r3, [r8]
	movs	r4, #0
	mov	r5, r4
	str	r3, [r7]
	bl	flash_enter_slc_mode
	str	r7, [sp, #4]
	ldr	r7, .L1240+48
	str	r10, [sp, #8]
	mov	fp, r7
.L1233:
	ldr	r1, [r7]
	movs	r2, #0
	mov	r0, r2
	muls	r1, r5, r1
	bl	FlashEraseBlock
	ldr	r3, .L1240+52
	ldrb	r10, [r3]	@ zero_extendqisi2
	cmp	r10, #0
	beq	.L1228
	mov	r10, #0
.L1229:
	ldr	r1, [fp]
	movs	r3, #0
	ldr	r2, [r6]
	mov	r0, r3
	mla	r1, r1, r5, r10
	add	r10, r10, #1
	bl	FlashProgPage
	cmp	r10, #10
	bne	.L1229
.L1230:
	ldr	r1, [fp]
	movs	r3, #0
	ldr	r2, [r8]
	mov	r0, r3
	add	r10, r5, #1
	muls	r1, r5, r1
	bl	FlashReadRawPage
	adds	r0, r0, #1
	beq	.L1231
	ldr	r3, [sp, #4]
	ldr	r1, [sp, #8]
	ldr	r3, [r3]
	ldr	r2, [r3]
	cmp	r2, r1
	bne	.L1231
	add	r0, r3, #12
	movw	r1, #2036
	str	r3, [sp, #12]
	bl	js_hash
	ldr	r3, [sp, #12]
	ldr	r3, [r3, #8]
	cmp	r3, r0
	bne	.L1231
	ldr	r3, .L1240+56
	cmp	r4, #1
	str	r10, [r3]
	ldr	r3, [fp]
	mul	r5, r5, r3
	ldr	r3, .L1240+60
	str	r5, [r3]
	beq	.L1234
	movs	r4, #1
.L1231:
	mov	r5, r10
	cmp	r5, #4
	bne	.L1233
.L1232:
	movs	r0, #0
	bl	flash_exit_slc_mode
	clz	r0, r4
	lsrs	r0, r0, #5
	negs	r0, r0
	add	sp, sp, #16
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r10, fp, pc}
.L1228:
	ldr	r1, [r7]
	mov	r3, r10
	ldr	r2, [r6]
	mov	r0, r10
	muls	r1, r5, r1
	bl	FlashProgPage
	ldr	r1, [r7]
	mov	r3, r10
	ldr	r2, [r6]
	mov	r0, r10
	muls	r1, r5, r1
	adds	r1, r1, #1
	bl	FlashProgPage
	b	.L1230
.L1234:
	movs	r4, #2
	b	.L1232
.L1241:
	.align	2
.L1240:
	.word	.LANCHOR154
	.word	.LANCHOR153
	.word	.LANCHOR158
	.word	.LANCHOR26
	.word	.LANCHOR22
	.word	.LANCHOR3
	.word	.LANCHOR30
	.word	.LANCHOR27
	.word	.LANCHOR18
	.word	.LANCHOR31
	.word	.LANCHOR8
	.word	.LANCHOR20
	.word	.LANCHOR4
	.word	.LANCHOR16
	.word	.LANCHOR156
	.word	.LANCHOR155
	.word	1312902724
	.word	.LANCHOR149
	.size	FlashSavePhyInfo, .-FlashSavePhyInfo
	.section	.text.FlashReadIdbDataRaw,"ax",%progbits
	.align	1
	.global	FlashReadIdbDataRaw
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	FlashReadIdbDataRaw, %function
FlashReadIdbDataRaw:
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r0, r1, r2, r3, r4, r5, r6, r7, r8, r10, fp, lr}
	movs	r3, #60
	strb	r3, [sp, #12]
	movs	r3, #40
	mov	r10, r0
	strb	r3, [sp, #13]
	movs	r3, #24
	strb	r3, [sp, #14]
	movs	r3, #16
	strb	r3, [sp, #15]
	ldr	r3, .L1260
	ldrb	r3, [r3]	@ zero_extendqisi2
	str	r3, [sp]
	ldr	r3, .L1260+4
	ldr	r2, [r3]
	str	r3, [sp, #4]
	cbz	r2, .L1243
	movs	r0, #0
	bl	flash_enter_slc_mode
.L1243:
	mov	r7, #-1
	movs	r4, #2
	mov	r2, #2048
	movs	r1, #0
	mov	r0, r10
	bl	ftl_memset
.L1244:
	ldr	r3, .L1260+8
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r4, r3
	bcc	.L1249
.L1248:
	ldr	r0, [sp]
	bl	FlashBchSel
	ldr	r3, [sp, #4]
	ldr	r3, [r3]
	cbz	r3, .L1242
	movs	r0, #0
	bl	flash_exit_slc_mode
.L1242:
	mov	r0, r7
	add	sp, sp, #16
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r10, fp, pc}
.L1249:
	ldr	r5, .L1260+12
	movs	r6, #0
	ldr	fp, .L1260+28
.L1246:
	add	r3, sp, #12
	ldrb	r8, [r6, r3]	@ zero_extendqisi2
	mov	r0, r8
	bl	FlashBchSel
	ldr	r1, [fp]
	movs	r3, #0
	ldr	r2, [r5]
	mov	r0, r3
	muls	r1, r4, r1
	bl	FlashReadRawPage
	adds	r0, r0, #1
	bne	.L1245
	adds	r6, r6, #1
	cmp	r6, #4
	bne	.L1246
.L1247:
	adds	r4, r4, #1
	b	.L1244
.L1252:
	movs	r7, #0
	b	.L1248
.L1245:
	ldr	r3, [r5]
	ldr	r2, [r3]
	ldr	r3, .L1260+16
	cmp	r2, r3
	bne	.L1247
	mov	r1, r8
	ldr	r0, .L1260+20
	bl	printf
	mov	r2, #2048
	ldr	r1, [r5]
	mov	r0, r10
	bl	ftl_memcpy
	ldr	r3, [r5]
	ldr	r2, .L1260+8
	ldr	r3, [r3, #512]
	strb	r3, [r2]
	ldr	r3, .L1260+24
	ldr	r2, [r3]
	cmp	r4, r2
	bcs	.L1252
	str	r4, [r3]
	movs	r7, #0
	bl	FlashSavePhyInfo
	b	.L1247
.L1261:
	.align	2
.L1260:
	.word	.LANCHOR33
	.word	.LANCHOR29
	.word	.LANCHOR3
	.word	.LANCHOR154
	.word	-52655045
	.word	.LC15
	.word	.LANCHOR156
	.word	.LANCHOR4
	.size	FlashReadIdbDataRaw, .-FlashReadIdbDataRaw
	.section	.text.idb_write_data,"ax",%progbits
	.align	1
	.global	idb_write_data
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	idb_write_data, %function
idb_write_data:
	@ args = 0, pretend = 0, frame = 96
	@ frame_needed = 0, uses_anonymous_args = 0
	mov	r0, r1
	mov	r1, r2
	adds	r2, r0, r3
	push	{r4, r5, r6, r7, r8, r10, fp, lr}
	cmp	r2, #63
	sub	sp, sp, #104
	bls	.L1263
	cmp	r0, #576
	bcs	.L1264
	ldr	r2, .L1315
	cmp	r0, #64
	mov	r4, #1
	str	r4, [r2]
	bhi	.L1265
	rsb	r0, r0, #64
	subs	r2, r3, r0
	add	r1, r1, r0, lsl #9
	ldr	r0, .L1315+4
	lsls	r2, r2, #9
.L1314:
	bl	ftl_memcpy
.L1303:
	movs	r0, #0
	add	sp, sp, #104
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r10, fp, pc}
.L1265:
	rsb	r2, r0, #576
	subs	r0, r0, #64
	cmp	r2, r3
	it	cs
	movcs	r2, r3
	ldr	r3, .L1315+4
	lsls	r2, r2, #9
	add	r0, r3, r0, lsl #9
	b	.L1314
.L1263:
	cmp	r0, #576
	bcc	.L1303
.L1264:
	ldr	r3, .L1315
	ldr	r3, [r3]
	cmp	r3, #0
	beq	.L1303
	ldr	r3, .L1315+8
	ldr	r2, [r3]
	ldrb	r3, [r2, #9]	@ zero_extendqisi2
	ldrh	r2, [r2, #10]
	smulbb	r3, r3, r2
	uxth	r3, r3
	mov	r1, r3
	addw	r0, r3, #511
	str	r3, [sp, #8]
	bl	__aeabi_uidiv
	ldr	r1, .L1315+4
	movs	r3, #0
	str	r0, [sp, #20]
	movw	r2, #65535
	mov	r0, r1
.L1269:
	ldr	r4, [r1, r2, lsl #2]
	cbnz	r4, .L1267
	ldr	r4, [r1, r3, lsl #2]
	adds	r3, r3, #1
	cmp	r3, #4096
	it	hi
	movhi	r3, #0
	str	r4, [r1, r2, lsl #2]
	subs	r2, r2, #1
	cmp	r2, #4096
	bne	.L1269
.L1267:
	ldr	r1, [r0, r2, lsl #2]
	mov	r3, #512
	ldr	r0, .L1315+12
	bl	printf
	ldr	r3, .L1315+16
	ldr	r2, [sp, #8]
	ldr	r3, [r3]
	str	r3, [sp, #16]
	ldr	r3, [sp, #20]
	muls	r3, r2, r3
	str	r3, [sp, #36]
	ldr	r3, [sp, #16]
	mul	r4, r3, r2
	movs	r3, #0
	str	r3, [sp, #12]
.L1270:
	ldr	r3, [sp, #16]
	cmp	r3, #15
	bls	.L1287
	ldr	r3, [sp, #12]
	cbnz	r3, .L1289
	mov	r1, r3
	ldr	r0, .L1315+20
	bl	printf
.L1289:
	ldr	r3, .L1315
	movs	r2, #0
	str	r2, [r3]
	b	.L1303
.L1316:
	.align	2
.L1315:
	.word	.LANCHOR159
	.word	idb_buf
	.word	.LANCHOR7
	.word	.LC16
	.word	.LANCHOR156
	.word	.LC18
.L1287:
	mov	r2, #512
	movs	r1, #0
	ldr	r0, .L1317
	bl	memset
	ldr	r3, .L1317+4
	mov	r0, r4
	ldr	r3, [r3]
	ldrb	fp, [r3, #9]	@ zero_extendqisi2
	ldrh	r5, [r3, #10]
	bl	FW_FlashBlockErase.constprop.41
	smulbb	r5, r5, fp
	uxth	r5, r5
	cmp	r5, #512
	bcs	.L1271
	adds	r0, r5, r4
	bl	FW_FlashBlockErase.constprop.41
.L1271:
	ldr	r7, .L1317+8
	mov	r1, r5
	ldr	r10, .L1317+36
	mov	r0, r4
	bl	__aeabi_uidivmod
	mov	r6, r1
	subs	r3, r4, r1
	str	r3, [sp, #24]
.L1275:
	lsrs	r2, r6, #2
	beq	.L1272
	ldr	r0, .L1317+12
	adds	r1, r2, #1
	ldr	r3, .L1317+16
	ldrb	r0, [r0]	@ zero_extendqisi2
	ldrh	r3, [r3, r1, lsl #1]
	cbz	r0, .L1273
	ldr	r0, [r10]
	ldr	r5, .L1317+20
	cmp	r0, r5
	it	eq
	moveq	r3, r1
.L1273:
	add	r3, r3, #1073741824
	subs	r3, r3, #1
	lsls	r3, r3, #2
	str	r3, [sp, #40]
.L1272:
	movw	r3, #61424
	str	r3, [sp, #44]
	ldr	r3, .L1317+16
	ldrh	r5, [r3, r2, lsl #1]
	ldr	r3, .L1317+12
	ldrb	r3, [r3]	@ zero_extendqisi2
	cbz	r3, .L1274
	ldr	r3, [r10]
	ldr	r1, .L1317+20
	cmp	r3, r1
	it	eq
	moveq	r5, r2
.L1274:
	ldr	r3, [sp, #24]
	adds	r6, r6, #4
	ldr	r2, .L1317+24
	ldr	r8, .L1317+4
	mla	r3, r5, fp, r3
	adds	r5, r5, #1
	uxth	r5, r5
	str	r3, [sp, #32]
	ldrb	r3, [r2]	@ zero_extendqisi2
	ldr	r2, .L1317+28
	str	r3, [sp, #28]
	ldrb	r0, [r2]	@ zero_extendqisi2
	bl	FlashBchSel
	movs	r0, #0
	bl	flash_boot_enter_slc_mode
	ldr	r2, [r8]
	ldr	r3, [sp, #32]
	ldrb	r1, [r2, #9]	@ zero_extendqisi2
	mov	r0, r3
	bl	__aeabi_uidiv
	add	r3, sp, #40
	mov	r2, r7
	mov	r1, r0
	movs	r0, #0
	bl	FlashProgPage
	movs	r0, #0
	add	r7, r7, #2048
	bl	flash_boot_exit_slc_mode
	ldr	r0, [sp, #28]
	bl	FlashBchSel
	mov	r1, fp
	ldr	r0, [sp, #24]
	bl	__aeabi_uidiv
	mov	r2, r5
	mov	r1, r0
	movs	r0, #0
	bl	FlashPageProgMsbFFData
	ldr	r3, .L1317+32
	cmp	r7, r3
	bne	.L1275
	ldr	r3, [r8]
	mov	r0, r4
	ldr	r7, .L1317
	movs	r6, #0
	ldrb	r8, [r3, #9]	@ zero_extendqisi2
	ldrh	r1, [r3, #10]
	smulbb	r1, r1, r8
	uxth	r1, r1
	bl	__aeabi_uidivmod
	mul	r5, r8, r1
	mov	r10, r1
	subs	r3, r4, r1
	str	r3, [sp, #28]
	ubfx	r5, r5, #2, #2
.L1276:
	cmp	r6, #512
	bcs	.L1283
	ldr	r1, .L1317+12
	rsb	r3, r5, #4
	uxth	r3, r3
	ldr	r2, .L1317+16
	ldrb	r1, [r1]	@ zero_extendqisi2
	str	r3, [sp, #24]
	add	r3, r10, r6
	lsrs	r3, r3, #2
	ldrh	r2, [r2, r3, lsl #1]
	cbz	r1, .L1277
	ldr	r1, .L1317+36
	ldr	r0, .L1317+20
	ldr	r1, [r1]
	cmp	r1, r0
	it	eq
	moveq	r2, r3
.L1277:
	ldr	r3, [sp, #28]
	add	r5, r5, r3
	ldr	r3, .L1317+24
	mla	r5, r2, r8, r5
	ldrb	r3, [r3]	@ zero_extendqisi2
	str	r3, [sp, #32]
	ldr	r3, .L1317+4
	ldr	r3, [r3]
	ldrb	fp, [r3, #9]	@ zero_extendqisi2
	ldr	r3, .L1317+40
	ldrh	r2, [r3, #26]
	ldr	r3, .L1317+44
	ldr	r3, [r3]
	muls	r3, r2, r3
	mul	r3, fp, r3
	cmp	r5, r3
	bcs	.L1278
	ldr	r3, .L1317+28
	ldrb	r0, [r3]	@ zero_extendqisi2
	bl	FlashBchSel
.L1278:
	movs	r0, #0
	bl	flash_boot_enter_slc_mode
	mov	r1, fp
	mov	r0, r5
	bl	__aeabi_uidiv
	add	r3, sp, #40
	mov	r1, r0
	mov	fp, r0
	mov	r2, r7
	movs	r0, #0
	bl	FlashReadPage
	adds	r3, r0, #1
	mov	r5, r0
	bne	.L1279
	ldr	r3, .L1317+28
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, #40
	beq	.L1279
	movs	r0, #40
	bl	FlashBchSel
	add	r3, sp, #40
	mov	r2, r7
	mov	r1, fp
	movs	r0, #0
	bl	FlashReadPage
	mov	r5, r0
.L1279:
	movs	r0, #0
	bl	flash_boot_exit_slc_mode
	ldr	r0, [sp, #32]
	bl	FlashBchSel
	adds	r5, r5, #1
	mov	r5, #-1
	it	ne
	movne	r5, #0
	cbz	r5, .L1280
.L1283:
	ldr	r3, .L1317+8
	movs	r5, #0
	ldr	r6, .L1317
.L1281:
	mov	r7, r3
	ldr	r1, [r6, r5, lsl #2]
	ldr	r2, [r7]
	adds	r3, r3, #4
	cmp	r1, r2
	beq	.L1284
	mov	r2, #512
	movs	r1, #0
	ldr	r0, .L1317
	bl	memset
	str	r5, [sp]
	mov	r1, r4
	ldr	r3, [r7]
	ldr	r2, [r6, r5, lsl #2]
	ldr	r0, .L1317+48
	bl	printf
	mov	r0, r4
	bl	FW_FlashBlockErase.constprop.41
	ldr	r3, [sp, #20]
	cmp	r3, #1
	bls	.L1285
	ldr	r3, [sp, #8]
	adds	r0, r3, r4
	bl	FW_FlashBlockErase.constprop.41
.L1285:
	ldr	r3, [sp, #16]
	ldr	r2, [sp, #20]
	add	r3, r3, r2
	str	r3, [sp, #16]
	ldr	r3, [sp, #36]
	add	r4, r4, r3
	b	.L1270
.L1280:
	ldr	r3, [sp, #24]
	add	r6, r6, r3
	add	r7, r7, r3, lsl #9
	uxth	r6, r6
	b	.L1276
.L1284:
	adds	r5, r5, #1
	cmp	r5, #65536
	bne	.L1281
	ldr	r3, [sp, #12]
	adds	r3, r3, #1
	cmp	r3, #5
	str	r3, [sp, #12]
	bls	.L1285
	b	.L1289
.L1318:
	.align	2
.L1317:
	.word	gp_flash_check_buf
	.word	.LANCHOR7
	.word	idb_buf
	.word	.LANCHOR16
	.word	.LANCHOR17
	.word	1446522928
	.word	.LANCHOR33
	.word	.LANCHOR158
	.word	idb_buf+262144
	.word	.LANCHOR122
	.word	.LANCHOR15
	.word	.LANCHOR4
	.word	.LC17
	.size	idb_write_data, .-idb_write_data
	.section	.text.ftl_memcpy32,"ax",%progbits
	.align	1
	.global	ftl_memcpy32
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	ftl_memcpy32, %function
ftl_memcpy32:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	movs	r3, #0
	push	{r4, lr}
.L1320:
	cmp	r3, r2
	bne	.L1321
	pop	{r4, pc}
.L1321:
	ldr	r4, [r1, r3, lsl #2]
	str	r4, [r0, r3, lsl #2]
	adds	r3, r3, #1
	b	.L1320
	.size	ftl_memcpy32, .-ftl_memcpy32
	.section	.text.ftl_memcmp,"ax",%progbits
	.align	1
	.global	ftl_memcmp
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	ftl_memcmp, %function
ftl_memcmp:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	b	memcmp
	.size	ftl_memcmp, .-ftl_memcmp
	.section	.text.rknand_get_clk_rate,"ax",%progbits
	.align	1
	.global	rknand_get_clk_rate
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	rknand_get_clk_rate, %function
rknand_get_clk_rate:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	ldr	r0, .L1324
	bx	lr
.L1325:
	.align	2
.L1324:
	.word	148000000
	.size	rknand_get_clk_rate, .-rknand_get_clk_rate
	.section	.text.ftl_malloc,"ax",%progbits
	.align	1
	.global	ftl_malloc
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	ftl_malloc, %function
ftl_malloc:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	movs	r1, #0
	b	kmalloc
	.size	ftl_malloc, .-ftl_malloc
	.section	.text.NandcInit,"ax",%progbits
	.align	1
	.global	NandcInit
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	NandcInit, %function
NandcInit:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r3, r4, r5, lr}
	movs	r2, #1
	ldr	r3, .L1329
	movs	r4, #0
	ldr	r5, .L1329+4
	str	r2, [r3, #12]
	movs	r2, #2
	str	r2, [r3, #20]
	movs	r2, #3
	stm	r3, {r0, r4}
	str	r0, [r3, #8]
	str	r0, [r3, #16]
	str	r2, [r3, #28]
	str	r0, [r3, #24]
	ldr	r3, .L1329+8
	ldr	r2, .L1329+12
	str	r0, [r3]
	ldr	r3, [r0]
	and	r3, r3, #253952
	ubfx	r1, r3, #13, #1
	bfi	r3, r4, #13, #1
	str	r1, [r2]
	orr	r3, r3, #256
	ldr	r2, [r0, #352]
	ldr	r1, .L1329+16
	ubfx	r2, r2, #16, #4
	str	r2, [r1]
	ldr	r2, [r0, #352]
	str	r2, [r5]
	movw	r5, #2049
	cmp	r2, r5
	itt	eq
	moveq	r2, #8
	streq	r2, [r1]
	str	r3, [r0]
	movw	r3, #4225
	str	r4, [r0, #336]
	str	r3, [r0, #4]
	movw	r3, #8322
	str	r3, [r0, #344]
	ldr	r3, .L1329+20
	str	r3, [r0, #304]
	mov	r0, #36864
	bl	ftl_malloc
	ldr	r3, .L1329+24
	str	r0, [r3]
	ldr	r3, .L1329+28
	str	r0, [r3]
	add	r0, r0, #32768
	str	r0, [r3, #4]
	str	r4, [r3, #24]
	ldr	r3, .L1329+32
	str	r4, [r3]
	pop	{r3, r4, r5, pc}
.L1330:
	.align	2
.L1329:
	.word	.LANCHOR0
	.word	.LANCHOR122
	.word	.LANCHOR19
	.word	.LANCHOR160
	.word	.LANCHOR34
	.word	1710593
	.word	.LANCHOR161
	.word	.LANCHOR35
	.word	.LANCHOR36
	.size	NandcInit, .-NandcInit
	.section	.text.FtlMemInit,"ax",%progbits
	.align	1
	.global	FtlMemInit
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	FtlMemInit, %function
FtlMemInit:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	ldr	r3, .L1337
	movs	r0, #128
	push	{r4, r5, r6, r7, r8, r10, fp, lr}
	movs	r4, #0
	ldr	r2, .L1337+4
	movs	r6, #12
	movs	r7, #36
	strh	r4, [r3]	@ movhi
	ldr	r3, .L1337+8
	ldr	r5, .L1337+12
	ldr	fp, .L1337+320
	str	r4, [r3]
	ldr	r3, .L1337+16
	str	r4, [r3]
	ldr	r3, .L1337+20
	str	r4, [r3]
	ldr	r3, .L1337+24
	str	r4, [r3]
	ldr	r3, .L1337+28
	str	r4, [r3]
	ldr	r3, .L1337+32
	str	r4, [r3]
	ldr	r3, .L1337+36
	str	r4, [r3]
	ldr	r3, .L1337+40
	str	r4, [r3]
	ldr	r3, .L1337+44
	str	r4, [r3]
	ldr	r3, .L1337+48
	str	r4, [r3]
	ldr	r3, .L1337+52
	str	r4, [r3]
	ldr	r3, .L1337+56
	str	r4, [r3]
	ldr	r3, .L1337+60
	str	r4, [r3]
	ldr	r3, .L1337+64
	str	r4, [r3]
	ldr	r3, .L1337+68
	str	r4, [r3]
	ldr	r3, .L1337+72
	str	r4, [r3]
	ldr	r3, .L1337+76
	str	r4, [r3]
	movw	r3, #65535
	str	r3, [r2]
	ldr	r2, .L1337+80
	str	r4, [r2]
	ldr	r2, .L1337+84
	str	r4, [r2]
	ldr	r2, .L1337+88
	str	r4, [r2]
	ldr	r2, .L1337+92
	strh	r3, [r2]	@ movhi
	ldr	r2, .L1337+96
	strh	r3, [r2]	@ movhi
	ldr	r2, .L1337+100
	strh	r3, [r2]	@ movhi
	ldr	r2, .L1337+104
	strh	r3, [r2]	@ movhi
	movs	r2, #32
	ldr	r3, .L1337+108
	strh	r2, [r3]	@ movhi
	ldr	r3, .L1337+112
	strh	r0, [r3]	@ movhi
	ldr	r3, .L1337+116
	strh	r4, [r3]	@ movhi
	ldr	r3, .L1337+120
	strh	r4, [r3]	@ movhi
	ldr	r3, .L1337+124
	strh	r4, [r3]	@ movhi
	ldr	r3, .L1337+128
	strh	r4, [r3]	@ movhi
	ldr	r3, .L1337+132
	ldrh	r1, [r3]
	bl	__aeabi_idiv
	ldr	r2, .L1337+136
	str	r0, [r5]
	ldrh	r3, [r2]
	mov	r8, r2
	lsls	r3, r3, #2
	cmp	r0, r3
	it	hi
	strhi	r3, [r5]
	ldr	r3, .L1337+140
	str	r4, [r3]
	ldr	r4, .L1337+144
	ldrh	r0, [r4]
	lsls	r0, r0, #1
	bl	ftl_malloc
	ldr	r3, .L1337+148
	str	r0, [r3]
	ldrh	r0, [r4]
	muls	r0, r6, r0
	bl	ftl_malloc
	ldrh	r4, [r8]
	ldr	r3, .L1337+152
	muls	r4, r7, r4
	str	r0, [r3]
	lsl	r10, r4, #2
	mov	r0, r10
	bl	ftl_malloc
	ldr	r3, .L1337+156
	str	r0, [r3]
	mov	r0, r4
	bl	ftl_malloc
	ldr	r3, .L1337+160
	str	r0, [r3]
	mov	r0, r10
	bl	ftl_malloc
	ldr	r3, .L1337+164
	ldr	r10, .L1337+324
	str	r0, [r3]
	mov	r0, r4
	bl	ftl_malloc
	ldr	r3, .L1337+168
	str	r0, [r3]
	mov	r0, r4
	bl	ftl_malloc
	ldr	r3, .L1337+172
	str	r0, [r3]
	ldr	r0, [r5]
	muls	r0, r7, r0
	ldr	r7, .L1337+176
	bl	ftl_malloc
	ldr	r3, .L1337+180
	ldrh	r4, [r7]
	str	r0, [r3]
	ldrh	r3, [r8]
	mov	r0, r4
	lsls	r3, r3, #1
	adds	r3, r3, #1
	str	r3, [r10]
	bl	ftl_malloc
	ldr	r3, .L1337+184
	str	r0, [r3]
	mov	r0, r4
	bl	ftl_malloc
	ldr	r3, .L1337+188
	str	r0, [r3]
	mov	r0, r4
	bl	ftl_malloc
	ldr	r3, .L1337+192
	str	r0, [r3]
	ldr	r0, [r10]
	muls	r0, r4, r0
	bl	ftl_malloc
	ldr	r3, .L1337+196
	str	r0, [r3]
	ldr	r0, [r5]
	muls	r0, r4, r0
	bl	ftl_malloc
	ldr	r3, .L1337+200
	str	r0, [r3]
	mov	r0, r4
	bl	ftl_malloc
	ldr	r3, .L1337+204
	str	r0, [r3]
	mov	r0, r4
	bl	ftl_malloc
	ldr	r3, .L1337+208
	str	r0, [r3]
	ldr	r0, [r10]
	muls	r0, r6, r0
	bl	ftl_malloc
	ldr	r3, .L1337+212
	ldrh	r4, [r8]
	ldr	r8, .L1337+328
	str	r0, [r3]
	ldrh	r3, [fp]
	muls	r4, r3, r4
	mov	r0, r4
	bl	ftl_malloc
	ldr	r3, .L1337+216
	str	r0, [r3]
	lsls	r0, r4, #2
	ldr	r4, .L1337+220
	bl	ftl_malloc
	ldr	r3, .L1337+224
	str	r0, [r3]
	ldrh	r3, [fp]
	ldr	r0, [r10]
	muls	r0, r3, r0
	bl	ftl_malloc
	ldr	r3, .L1337+228
	str	r0, [r3]
	ldrh	r3, [fp]
	ldr	r0, [r5]
	ldr	r5, .L1337+232
	muls	r0, r3, r0
	bl	ftl_malloc
	ldr	r3, .L1337+236
	str	r0, [r3]
	ldrh	r0, [r4]
	lsls	r0, r0, #1
	uxth	r0, r0
	strh	r0, [r5]	@ movhi
	bl	ftl_malloc
	ldr	r3, .L1337+240
	str	r0, [r3]
	ldrh	r3, [r5]
	ldr	r0, .L1337+244
	addw	r3, r3, #547
	lsrs	r3, r3, #9
	and	r0, r0, r3, lsl #9
	strh	r3, [r5]	@ movhi
	bl	ftl_malloc
	ldr	r3, .L1337+248
	str	r0, [r3]
	adds	r0, r0, #32
	ldr	r3, .L1337+252
	str	r0, [r3]
	ldrh	r0, [r4]
	lsls	r0, r0, #1
	bl	ftl_malloc
	ldr	r5, [r8]
	ldr	r3, .L1337+256
	lsls	r5, r5, #1
	str	r0, [r3]
	mov	r0, r5
	bl	ftl_malloc
	ldr	r3, .L1337+260
	str	r0, [r3]
	mov	r0, r5
	bl	ftl_malloc
	ldr	r3, .L1337+264
	ldr	r5, .L1337+268
	str	r0, [r3]
	ldrh	r0, [r4]
	lsrs	r0, r0, #3
	adds	r0, r0, #4
	bl	ftl_malloc
	ldr	r3, .L1337+272
	str	r0, [r3]
	ldrh	r0, [r5]
	lsls	r0, r0, #1
	bl	ftl_malloc
	ldr	r3, .L1337+276
	str	r0, [r3]
	ldrh	r0, [r5]
	lsls	r0, r0, #1
	bl	ftl_malloc
	ldr	r3, .L1337+280
	str	r0, [r3]
	ldrh	r0, [r5]
	ldr	r5, .L1337+284
	lsls	r0, r0, #2
	bl	ftl_malloc
	ldr	r3, .L1337+288
	str	r0, [r3]
	ldrh	r0, [r5]
	lsls	r0, r0, #2
	bl	ftl_malloc
	ldrh	r2, [r5]
	movs	r1, #0
	ldr	r3, .L1337+292
	lsls	r2, r2, #2
	str	r0, [r3]
	bl	ftl_memset
	ldr	r3, .L1337+296
	ldrh	r5, [r3]
	lsls	r5, r5, #2
	mov	r0, r5
	bl	ftl_malloc
	ldr	r3, .L1337+300
	str	r0, [r3]
	mov	r0, r5
	bl	ftl_malloc
	ldr	r3, .L1337+304
	ldr	r5, .L1337+308
	str	r0, [r3]
	ldr	r0, [r8]
	lsls	r0, r0, #2
	bl	ftl_malloc
	ldr	r3, .L1337+312
	str	r0, [r3]
	ldrh	r0, [r5]
	muls	r0, r6, r0
	ldr	r6, .L1337+316
	bl	ftl_malloc
	b	.L1338
.L1339:
	.align	2
.L1337:
	.word	.LANCHOR142
	.word	.LANCHOR178
	.word	.LANCHOR162
	.word	.LANCHOR185
	.word	.LANCHOR163
	.word	.LANCHOR164
	.word	.LANCHOR165
	.word	.LANCHOR166
	.word	.LANCHOR167
	.word	.LANCHOR168
	.word	.LANCHOR169
	.word	.LANCHOR170
	.word	.LANCHOR171
	.word	.LANCHOR172
	.word	.LANCHOR173
	.word	.LANCHOR81
	.word	.LANCHOR174
	.word	.LANCHOR175
	.word	.LANCHOR176
	.word	.LANCHOR177
	.word	.LANCHOR179
	.word	.LANCHOR180
	.word	.LANCHOR75
	.word	.LANCHOR115
	.word	.LANCHOR116
	.word	.LANCHOR117
	.word	.LANCHOR118
	.word	.LANCHOR181
	.word	.LANCHOR182
	.word	.LANCHOR183
	.word	.LANCHOR119
	.word	.LANCHOR184
	.word	.LANCHOR121
	.word	.LANCHOR55
	.word	.LANCHOR38
	.word	.LANCHOR72
	.word	.LANCHOR54
	.word	.LANCHOR111
	.word	.LANCHOR114
	.word	.LANCHOR186
	.word	.LANCHOR187
	.word	.LANCHOR188
	.word	.LANCHOR79
	.word	.LANCHOR109
	.word	.LANCHOR57
	.word	.LANCHOR73
	.word	.LANCHOR189
	.word	.LANCHOR190
	.word	.LANCHOR191
	.word	.LANCHOR107
	.word	.LANCHOR192
	.word	.LANCHOR193
	.word	.LANCHOR194
	.word	.LANCHOR106
	.word	.LANCHOR195
	.word	.LANCHOR41
	.word	.LANCHOR196
	.word	.LANCHOR108
	.word	.LANCHOR198
	.word	.LANCHOR197
	.word	.LANCHOR140
	.word	33553920
	.word	.LANCHOR199
	.word	.LANCHOR80
	.word	.LANCHOR85
	.word	.LANCHOR132
	.word	.LANCHOR128
	.word	.LANCHOR61
	.word	.LANCHOR1
	.word	.LANCHOR71
	.word	.LANCHOR200
	.word	.LANCHOR62
	.word	.LANCHOR201
	.word	.LANCHOR202
	.word	.LANCHOR66
	.word	.LANCHOR134
	.word	.LANCHOR203
	.word	.LANCHOR67
	.word	.LANCHOR133
	.word	.LANCHOR45
	.word	.LANCHOR58
	.word	.LANCHOR110
	.word	.LANCHOR64
.L1338:
	ldr	r3, .L1340
	str	r0, [r3]
	ldrh	r3, [r5]
	ldrh	r0, [r7]
	ldr	r5, .L1340+4
	muls	r0, r3, r0
	bl	ftl_malloc
	ldr	r3, .L1340+8
	str	r0, [r3]
	movs	r0, #6
	ldrh	r3, [r4]
	muls	r0, r3, r0
	bl	ftl_malloc
	ldr	r3, .L1340+12
	str	r0, [r3]
	ldr	r3, .L1340+16
	ldrh	r0, [r3]
	ldrh	r3, [r6]
	adds	r0, r0, #31
	asrs	r0, r0, #5
	strh	r0, [r5]	@ movhi
	muls	r0, r3, r0
	lsls	r0, r0, #2
	bl	ftl_malloc
	ldrh	r1, [r5]
	movs	r2, #1
	ldr	r3, .L1340+20
	ldrh	r6, [r6]
	lsls	r1, r1, #2
	mov	r4, r3
	str	r0, [r4, #28]!
	mov	r0, r1
.L1333:
	cmp	r2, r6
	bcc	.L1334
	add	r3, r3, r2, lsl #2
	ldr	r2, .L1340+24
	movs	r1, #0
	adds	r3, r3, #24
.L1335:
	cmp	r3, r2
	bne	.L1336
	movs	r0, #0
	pop	{r4, r5, r6, r7, r8, r10, fp, pc}
.L1334:
	ldr	r5, [r3, #28]
	adds	r2, r2, #1
	add	r5, r5, r0
	add	r0, r0, r1
	str	r5, [r4, #4]!
	b	.L1333
.L1336:
	str	r1, [r3, #4]!
	b	.L1335
.L1341:
	.align	2
.L1340:
	.word	.LANCHOR98
	.word	.LANCHOR126
	.word	.LANCHOR129
	.word	.LANCHOR83
	.word	.LANCHOR51
	.word	.LANCHOR76
	.word	.LANCHOR76+56
	.size	FtlMemInit, .-FtlMemInit
	.section	.text.ftl_free,"ax",%progbits
	.align	1
	.global	ftl_free
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	ftl_free, %function
ftl_free:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	b	free
	.size	ftl_free, .-ftl_free
	.section	.text.FlashCs123Init,"ax",%progbits
	.align	1
	.global	FlashCs123Init
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	FlashCs123Init, %function
FlashCs123Init:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	bx	lr
	.size	FlashCs123Init, .-FlashCs123Init
	.section	.text.rk_nand_de_init,"ax",%progbits
	.align	1
	.global	rk_nand_de_init
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	rk_nand_de_init, %function
rk_nand_de_init:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	b	FlashDeInit
	.size	rk_nand_de_init, .-rk_nand_de_init
	.section	.text.rk_ftl_get_capacity,"ax",%progbits
	.align	1
	.global	rk_ftl_get_capacity
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	rk_ftl_get_capacity, %function
rk_ftl_get_capacity:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	ldr	r3, .L1346
	ldr	r0, [r3]
	bx	lr
.L1347:
	.align	2
.L1346:
	.word	.LANCHOR68
	.size	rk_ftl_get_capacity, .-rk_ftl_get_capacity
	.section	.text.rknand_print_hex,"ax",%progbits
	.align	1
	.global	rknand_print_hex
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	rknand_print_hex, %function
rknand_print_hex:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, r8, r10, fp, lr}
	movs	r5, #0
	ldr	r7, .L1357
	mov	fp, r0
	mov	r6, r1
	mov	r8, r2
	mov	r10, r3
	mov	r4, r5
.L1349:
	cmp	r4, r10
	bne	.L1355
	ldr	r1, .L1357+4
	ldr	r0, .L1357+8
	pop	{r4, r5, r6, r7, r8, r10, fp, lr}
	b	printf
.L1355:
	cbnz	r5, .L1350
	mov	r2, r4
	mov	r1, fp
	ldr	r0, .L1357+12
	bl	printf
.L1350:
	cmp	r8, #4
	bne	.L1351
	ldr	r1, [r6, r4, lsl #2]
.L1356:
	mov	r0, r7
	adds	r5, r5, #1
	bl	printf
	cmp	r5, #15
	bls	.L1354
	movs	r5, #0
	ldr	r1, .L1357+4
	ldr	r0, .L1357+8
	bl	printf
.L1354:
	adds	r4, r4, #1
	b	.L1349
.L1351:
	cmp	r8, #2
	ite	eq
	ldrsheq	r1, [r6, r4, lsl #1]
	ldrbne	r1, [r6, r4]	@ zero_extendqisi2
	b	.L1356
.L1358:
	.align	2
.L1357:
	.word	.LC20
	.word	.LC21
	.word	.LC7
	.word	.LC19
	.size	rknand_print_hex, .-rknand_print_hex
	.section	.text.HynixGetReadRetryDefault,"ax",%progbits
	.align	1
	.global	HynixGetReadRetryDefault
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	HynixGetReadRetryDefault, %function
HynixGetReadRetryDefault:
	@ args = 0, pretend = 0, frame = 56
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, r8, r10, fp, lr}
	movs	r3, #172
	ldr	r5, .L1477
	cmp	r0, #2
	mov	r1, #173
	mov	r2, #174
	sub	sp, sp, #56
	mov	r4, r0
	strb	r3, [r5, #4]
	mov	r3, #175
	strb	r0, [r5]
	strb	r1, [r5, #5]
	strb	r2, [r5, #6]
	strb	r3, [r5, #7]
	bne	.L1360
	movs	r3, #167
	mov	fp, #7
	strb	r3, [r5, #4]
	movs	r2, #247
	ldr	r3, .L1477+4
	strb	r2, [r3, #17]
.L1470:
	mov	r10, #4
	b	.L1361
.L1360:
	cmp	r0, #3
	bne	.L1362
	movs	r3, #176
	strb	r3, [r5, #4]
	movs	r3, #177
	strb	r3, [r5, #5]
	movs	r3, #178
	strb	r3, [r5, #6]
	movs	r3, #179
	strb	r3, [r5, #7]
	movs	r3, #180
	strb	r3, [r5, #8]
	movs	r3, #181
	strb	r3, [r5, #9]
	movs	r3, #182
	strb	r3, [r5, #10]
	movs	r3, #183
.L1471:
	mov	fp, #8
	strb	r3, [r5, #11]
	mov	r10, fp
.L1361:
	subs	r3, r4, #1
	cmp	r3, #1
	bhi	.L1367
	mov	r8, #0
.L1368:
	ldr	r3, .L1477+8
	ldrb	r2, [r3]	@ zero_extendqisi2
	uxtb	r3, r8
	cmp	r2, r3
	bhi	.L1374
.L1375:
	ldr	r3, .L1477
	strb	r10, [r3, #1]
	strb	fp, [r3, #2]
	add	sp, sp, #56
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r10, fp, pc}
.L1362:
	cmp	r0, #4
	bne	.L1363
	movs	r0, #204
	strb	r1, [r5, #9]
	strb	r0, [r5, #4]
	movs	r0, #191
	strb	r0, [r5, #5]
	movs	r0, #170
	strb	r0, [r5, #6]
	movs	r0, #171
	strb	r0, [r5, #7]
	movs	r0, #205
	strb	r0, [r5, #8]
	strb	r2, [r5, #10]
	b	.L1471
.L1363:
	cmp	r0, #5
	bne	.L1364
	movs	r3, #56
	mov	fp, #8
	strb	r3, [r5, #4]
	movs	r3, #57
	strb	r3, [r5, #5]
	movs	r3, #58
	strb	r3, [r5, #6]
	movs	r3, #59
	strb	r3, [r5, #7]
	b	.L1470
.L1364:
	cmp	r0, #6
	bne	.L1365
	movs	r3, #14
	mov	fp, #12
	strb	r3, [r5, #4]
	movs	r3, #15
	strb	r3, [r5, #5]
	movs	r3, #16
	strb	r3, [r5, #6]
	movs	r3, #17
	strb	r3, [r5, #7]
	b	.L1470
.L1365:
	cmp	r0, #7
	bne	.L1366
	movs	r3, #176
	mov	fp, #12
	strb	r3, [r5, #4]
	movs	r3, #177
	strb	r3, [r5, #5]
	movs	r3, #178
	strb	r3, [r5, #6]
	movs	r3, #179
	strb	r3, [r5, #7]
	movs	r3, #180
	strb	r3, [r5, #8]
	movs	r3, #181
	strb	r3, [r5, #9]
	movs	r3, #182
	strb	r3, [r5, #10]
	movs	r3, #183
	strb	r3, [r5, #11]
	movs	r3, #212
	strb	r3, [r5, #12]
	movs	r3, #213
	strb	r3, [r5, #13]
	mov	r10, #10
	b	.L1361
.L1366:
	cmp	r0, #8
	mov	r3, #7
	bne	.L1425
	strb	r3, [r5, #5]
	movs	r3, #9
	movs	r2, #6
	strb	r3, [r5, #7]
	movs	r3, #10
	strb	r2, [r5, #4]
	strb	r0, [r5, #6]
	mov	fp, #50
	strb	r3, [r5, #8]
	mov	r10, #5
	b	.L1361
.L1425:
	mov	fp, r3
	b	.L1470
.L1374:
	ldr	r2, .L1477+12
	movs	r6, #0
	ldrb	r2, [r2, r3]	@ zero_extendqisi2
	ldr	r3, .L1477+16
	ldr	r7, [r3, r2, lsl #3]
	add	r4, r5, r2, lsl #6
	add	r3, r3, r2, lsl #3
	movs	r2, #55
	adds	r4, r4, #20
	ldrb	r3, [r3, #4]	@ zero_extendqisi2
	add	r7, r7, r3, lsl #8
	addw	r3, r7, #2056
.L1369:
	adds	r1, r5, r6
	str	r2, [r3]
	ldrb	r1, [r1, #4]	@ zero_extendqisi2
	movs	r0, #80
	str	r2, [sp, #4]
	str	r3, [sp]
	str	r1, [r7, #2052]
	bl	udelay
	ldr	r1, [r7, #2048]
	ldr	r3, [sp]
	ldr	r2, [sp, #4]
	strb	r1, [r4, r6]
	adds	r6, r6, #1
	uxtb	r1, r6
	cmp	r10, r1
	bhi	.L1369
	ldr	r7, .L1477+4
	mov	r1, r4
	movs	r2, #0
.L1372:
	movs	r3, #1
	adds	r6, r7, r2
.L1371:
	ldrb	r0, [r6, r3, lsl #2]	@ zero_extendqisi2
	ldrb	ip, [r1]	@ zero_extendqisi2
	add	r0, r0, ip
	strb	r0, [r1, r3, lsl #3]
	adds	r3, r3, #1
	cmp	r3, #7
	bne	.L1371
	adds	r2, r2, #1
	adds	r1, r1, #1
	cmp	r2, #4
	bne	.L1372
	movs	r3, #0
	add	r8, r8, #1
	strb	r3, [r4, #16]
	strb	r3, [r4, #24]
	strb	r3, [r4, #32]
	strb	r3, [r4, #40]
	strb	r3, [r4, #48]
	strb	r3, [r4, #41]
	strb	r3, [r4, #49]
	b	.L1368
.L1367:
	subs	r3, r4, #3
	cmp	r3, #5
	bhi	.L1375
	smulbb	r3, fp, r10
	asrs	r2, r3, #1
	lsls	r3, r3, #4
	str	r3, [sp, #48]
	lsls	r3, r2, #2
	str	r2, [sp, #12]
	str	r3, [sp, #44]
	lsls	r3, r2, #1
	str	r3, [sp, #32]
	movs	r3, #0
.L1476:
	str	r3, [sp, #28]
	ldrb	r3, [sp, #28]	@ zero_extendqisi2
	str	r3, [sp, #16]
	ldr	r3, .L1477+8
	ldr	r2, [sp, #16]
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, r2
	bls	.L1375
	ldr	r2, [sp, #16]
	ldr	r3, .L1477+12
	ldrb	r8, [r3, r2]	@ zero_extendqisi2
	ldr	r3, .L1477+16
	mov	r0, r8
	ldr	r2, [r3, r8, lsl #3]
	add	r3, r3, r8, lsl #3
	ldrb	r3, [r3, #4]	@ zero_extendqisi2
	str	r2, [sp]
	str	r3, [sp, #4]
	mov	r3, r2
	ldr	r2, [sp, #4]
	add	r5, r3, r2, lsl #8
	movs	r3, #255
	str	r3, [r5, #2056]
	bl	NandcWaitFlashReady
	cmp	r4, #7
	bne	.L1377
	ldr	r3, .L1477
	movs	r0, #160
	mla	r0, r0, r8, r3
	add	r3, r0, #28
.L1472:
	ldr	r2, [sp, #4]
	cmp	r4, #4
	str	r3, [sp, #20]
	ldr	r3, [sp]
	add	r3, r3, r2, lsl #8
	mov	r2, #54
	str	r2, [r3, #2056]
	bne	.L1380
	movs	r2, #255
	str	r2, [r3, #2052]
	movs	r2, #64
	str	r2, [r3, #2048]
	movs	r2, #204
.L1473:
	str	r2, [r3, #2052]
	movs	r2, #77
	b	.L1474
.L1377:
	cmp	r4, #8
	beq	.L1379
	ldr	r0, .L1477
	add	r0, r0, r8, lsl #6
	add	r3, r0, #20
	b	.L1472
.L1478:
	.align	2
.L1477:
	.word	.LANCHOR20
	.word	.LANCHOR204
	.word	.LANCHOR26
	.word	.LANCHOR27
	.word	.LANCHOR0
.L1380:
	subs	r2, r4, #5
	cmp	r2, #1
	bhi	.L1382
	ldr	r2, .L1479
	ldrb	r2, [r2, #4]	@ zero_extendqisi2
	str	r2, [r3, #2052]
	movs	r2, #82
.L1474:
	str	r2, [r3, #2048]
.L1381:
	ldr	r2, [sp, #4]
	cmp	r4, #6
	ldr	r3, [sp]
	add	r3, r3, r2, lsl #8
	mov	r2, #22
	str	r2, [r3, #2056]
	mov	r2, #23
	str	r2, [r3, #2056]
	mov	r2, #4
	str	r2, [r3, #2056]
	mov	r2, #25
	str	r2, [r3, #2056]
	mov	r2, #0
	str	r2, [r3, #2056]
	str	r2, [r3, #2052]
	str	r2, [r3, #2052]
	it	eq
	moveq	r2, #31
	str	r2, [r3, #2052]
	movs	r2, #2
	str	r2, [r3, #2052]
	movs	r2, #0
	str	r2, [r3, #2052]
.L1424:
	ldr	r2, [sp, #4]
	mov	r0, r8
	ldr	r3, [sp]
	add	r3, r3, r2, lsl #8
	movs	r2, #48
	str	r2, [r3, #2056]
	bl	NandcWaitFlashReady
	subs	r3, r4, #5
	cmp	r3, #1
	str	r3, [sp, #36]
	bls	.L1427
	cmp	r4, #8
	beq	.L1427
	cmp	r4, #7
	ite	eq
	moveq	r2, #32
	movne	r2, #2
.L1385:
	ldr	r3, .L1479+4
	subs	r2, r2, #1
	ldm	sp, {r5, r6}
	ldr	r3, [r3]
	add	r5, r5, r6, lsl #8
	subs	r1, r3, #1
	uxtab	r2, r3, r2
	mov	r0, r1
	str	r5, [sp, #8]
.L1386:
	ldr	r5, [sp, #8]
	ldr	r5, [r5, #2048]
	strb	r5, [r0, #1]!
	cmp	r0, r2
	bne	.L1386
	cmp	r4, #8
	bne	.L1387
	movs	r2, #0
.L1389:
	ldrb	r0, [r3, r2, lsl #2]	@ zero_extendqisi2
	uxtb	r1, r2
	cmp	r0, #50
	beq	.L1388
	add	r0, r3, r2, lsl #2
	ldrb	r0, [r0, #1]	@ zero_extendqisi2
	cmp	r0, #5
	beq	.L1388
	adds	r2, r2, #1
	cmp	r2, #8
	bne	.L1389
.L1390:
	movs	r1, #0
	ldr	r0, .L1479+8
	bl	printf
.L1392:
	b	.L1392
.L1382:
	cmp	r4, #7
	bne	.L1381
	movs	r2, #174
	str	r2, [r3, #2052]
	movs	r2, #0
	str	r2, [r3, #2048]
	movs	r2, #176
	b	.L1473
.L1427:
	movs	r2, #16
	b	.L1385
.L1388:
	cmp	r1, #6
	bhi	.L1390
.L1391:
	ldr	r3, .L1479+4
	ldr	r2, [r3]
	mov	r3, r2
.L1401:
	ldr	r0, [sp, #48]
	subs	r1, r3, r2
	cmp	r1, r0
	blt	.L1402
	ldr	r3, .L1479+4
	ldr	r1, [r3]
	ldr	r3, [sp, #32]
	adds	r0, r1, r3
	movs	r3, #8
.L1404:
	mov	r6, r0
	movs	r5, #0
.L1403:
	ldrh	r7, [r6]
	adds	r5, r5, #1
	mvns	r7, r7
	strh	r7, [r6], #2	@ movhi
	ldr	r7, [sp, #12]
	cmp	r7, r5
	bgt	.L1403
	ldr	r5, [sp, #44]
	subs	r3, r3, #1
	add	r0, r0, r5
	bne	.L1404
	mov	r7, r1
	str	r3, [sp, #24]
.L1410:
	movs	r5, #0
	mov	r0, r5
.L1409:
	movs	r3, #1
	mov	ip, #0
	lsl	r6, r3, r0
	movs	r3, #16
	str	r3, [sp, #40]
	mov	lr, r6
	mov	r6, r7
.L1407:
	ldrh	r3, [r6]
	str	r3, [sp, #52]
	ldr	r3, [sp, #52]
	bics	r3, lr, r3
	ldr	r3, [sp, #32]
	it	eq
	addeq	ip, ip, #1
	add	r6, r6, r3
	ldr	r3, [sp, #40]
	subs	r3, r3, #1
	str	r3, [sp, #40]
	bne	.L1407
	cmp	ip, #8
	add	r0, r0, #1
	ittt	hi
	movhi	r3, lr
	orrhi	r5, r5, r3
	uxthhi	r5, r5
	cmp	r0, #16
	bne	.L1409
	ldr	r3, [sp, #24]
	strh	r5, [r7], #2	@ movhi
	adds	r3, r3, #1
	str	r3, [sp, #24]
	ldr	r0, [sp, #24]
	ldr	r3, [sp, #12]
	cmp	r3, r0
	bgt	.L1410
	subs	r0, r1, #4
	add	r5, r1, #28
	movs	r3, #0
.L1413:
	ldr	r6, [r0, #4]!
	cbnz	r6, .L1412
	adds	r3, r3, #1
.L1412:
	cmp	r5, r0
	bne	.L1413
	cmp	r3, #7
	ble	.L1414
	ldr	r0, .L1479+12
	mov	r3, #1024
	movs	r2, #1
	bl	rknand_print_hex
	movs	r1, #0
	ldr	r0, .L1479+8
	bl	printf
.L1415:
	b	.L1415
.L1387:
	cmp	r4, #7
	bne	.L1393
	movs	r2, #0
.L1395:
	ldrb	r0, [r3, r2, lsl #2]	@ zero_extendqisi2
	uxtb	r1, r2
	cmp	r0, #12
	beq	.L1394
	add	r0, r3, r2, lsl #2
	ldrb	r0, [r0, #1]	@ zero_extendqisi2
	cmp	r0, #10
	beq	.L1394
	adds	r2, r2, #1
	cmp	r2, #8
	bne	.L1395
.L1396:
	movs	r1, #0
	ldr	r0, .L1479+8
	bl	printf
.L1397:
	b	.L1397
.L1394:
	cmp	r1, #6
	bls	.L1391
	b	.L1396
.L1393:
	cmp	r4, #6
	bne	.L1391
	adds	r3, r3, #7
.L1398:
	ldrb	r2, [r1, #1]!	@ zero_extendqisi2
	cmp	r2, #12
	beq	.L1391
	ldrb	r2, [r1, #8]	@ zero_extendqisi2
	cmp	r2, #4
	beq	.L1391
	cmp	r1, r3
	bne	.L1398
	movs	r1, #0
	ldr	r0, .L1479+8
	bl	printf
.L1400:
	b	.L1400
.L1402:
	ldr	r1, [sp, #8]
	ldr	r1, [r1, #2048]
	strb	r1, [r3], #1
	b	.L1401
.L1414:
	cmp	r4, #6
	beq	.L1429
	cmp	r4, #7
	beq	.L1430
	cmp	r4, #8
	ite	eq
	moveq	r6, #5
	movne	r6, #8
.L1416:
	add	r3, r10, #-1
	ldr	r0, [sp, #20]
	uxtb	r3, r3
	movs	r5, #0
	adds	r3, r3, #1
.L1417:
	mov	ip, r0
	mov	r1, r2
.L1418:
	ldrb	r7, [r1], #1	@ zero_extendqisi2
	strb	r7, [ip], #1
	subs	r7, r1, r2
	uxtb	r7, r7
	cmp	r10, r7
	bhi	.L1418
	adds	r5, r5, #1
	add	r2, r2, r3
	cmp	fp, r5
	add	r0, r0, r6
	bgt	.L1417
	ldr	r3, [sp]
	mov	r0, r8
	ldr	r2, [sp, #4]
	add	r5, r3, r2, lsl #8
	movs	r3, #255
	str	r3, [r5, #2056]
	bl	NandcWaitFlashReady
	ldr	r3, [sp, #36]
	cmp	r3, #1
	bhi	.L1420
	movs	r3, #54
	ldr	r2, [sp, #8]
	str	r3, [r5, #2056]
	mov	r1, #-1
	ldr	r3, .L1479
	ldr	r0, [sp, #16]
	ldrb	r3, [r3, #4]	@ zero_extendqisi2
	str	r3, [r2, #2052]
	movs	r3, #0
	str	r3, [r2, #2048]
	movs	r3, #22
	str	r3, [r5, #2056]
	bl	FlashReadCmd
.L1421:
	mov	r0, r8
	bl	NandcWaitFlashReady
	ldr	r3, [sp, #28]
	adds	r3, r3, #1
	b	.L1476
.L1429:
	movs	r6, #4
	b	.L1416
.L1430:
	movs	r6, #10
	b	.L1416
.L1420:
	cmp	r4, #8
	ite	eq
	moveq	r3, #190
	movne	r3, #56
	str	r3, [r5, #2056]
	b	.L1421
.L1379:
	movs	r3, #120
	movs	r2, #23
	str	r3, [r5, #2056]
	movs	r3, #0
	str	r3, [r5, #2052]
	movs	r1, #25
	str	r3, [r5, #2052]
	str	r3, [r5, #2052]
	str	r2, [r5, #2056]
	movs	r2, #4
	str	r2, [r5, #2056]
	str	r1, [r5, #2056]
	movs	r1, #218
	str	r1, [r5, #2056]
	movs	r1, #21
	str	r3, [r5, #2056]
	str	r3, [r5, #2052]
	str	r3, [r5, #2052]
	str	r1, [r5, #2052]
	str	r2, [r5, #2052]
	str	r3, [r5, #2052]
	ldr	r3, .L1479+16
	str	r3, [sp, #20]
	b	.L1424
.L1480:
	.align	2
.L1479:
	.word	.LANCHOR20
	.word	.LANCHOR154
	.word	.LC22
	.word	.LC23
	.word	.LANCHOR20+28
	.size	HynixGetReadRetryDefault, .-HynixGetReadRetryDefault
	.section	.text.FlashGetReadRetryDefault,"ax",%progbits
	.align	1
	.global	FlashGetReadRetryDefault
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	FlashGetReadRetryDefault, %function
FlashGetReadRetryDefault:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	mov	r3, r0
	cbz	r0, .L1481
	subs	r2, r0, #1
	cmp	r2, #7
	bhi	.L1483
	b	HynixGetReadRetryDefault
.L1483:
	cmp	r0, #49
	bne	.L1484
	ldr	r0, .L1504
	movs	r2, #64
	ldr	r1, .L1504+4
	strb	r3, [r0]
	movs	r3, #4
	strb	r3, [r0, #1]
	movs	r3, #15
	strb	r3, [r0, #2]
.L1502:
	adds	r0, r0, #4
	b	ftl_memcpy
.L1484:
	cmp	r0, #33
	beq	.L1485
	sub	r2, r0, #65
	cmp	r2, #1
	bhi	.L1486
.L1485:
	ldr	r0, .L1504
	strb	r3, [r0]
	movs	r3, #4
.L1503:
	strb	r3, [r0, #1]
	movs	r3, #7
	strb	r3, [r0, #2]
	movs	r2, #45
	ldr	r1, .L1504+8
	b	.L1502
.L1486:
	cmp	r0, #34
	beq	.L1487
	cmp	r0, #67
	bne	.L1488
.L1487:
	ldr	r0, .L1504
	strb	r3, [r0]
	movs	r3, #5
	b	.L1503
.L1488:
	cmp	r0, #35
	beq	.L1489
	cmp	r0, #68
	bne	.L1481
.L1489:
	ldr	r0, .L1504
	movs	r2, #95
	ldr	r1, .L1504+12
	strb	r3, [r0]
	movs	r3, #5
	strb	r3, [r0, #1]
	movs	r3, #17
	strb	r3, [r0, #2]
	b	.L1502
.L1481:
	bx	lr
.L1505:
	.align	2
.L1504:
	.word	.LANCHOR20
	.word	.LANCHOR14
	.word	.LANCHOR9
	.word	.LANCHOR11
	.size	FlashGetReadRetryDefault, .-FlashGetReadRetryDefault
	.section	.text.FlashInit,"ax",%progbits
	.align	1
	.global	FlashInit
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	FlashInit, %function
FlashInit:
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, r8, r10, fp, lr}
	mov	r4, r0
	sub	sp, sp, #32
	mov	r0, #32768
	movs	r5, #0
	bl	ftl_malloc
	ldr	r3, .L1614
	ldr	fp, .L1614+124
	ldr	r10, .L1614+128
	str	r0, [r3]
	mov	r0, #32768
	bl	ftl_malloc
	ldr	r3, .L1614+4
	ldr	r8, .L1614+132
	ldr	r6, .L1614+8
	str	r0, [r3]
	mov	r0, #4096
	bl	ftl_malloc
	ldr	r3, .L1614+12
	ldr	r7, .L1614+16
	str	r0, [r3]
	mov	r0, #32768
	bl	ftl_malloc
	ldr	r3, .L1614+20
	str	r0, [r3]
	mov	r0, #4096
	bl	ftl_malloc
	ldr	r3, .L1614+24
	ldr	r2, .L1614+28
	strb	r5, [r6]
	str	r0, [r3]
	movs	r3, #50
	strb	r3, [r2]
	movs	r2, #128
	strb	r3, [fp]
	mov	r0, r4
	ldr	r3, .L1614+32
	ldr	r4, .L1614+36
	strb	r5, [r10]
	str	r5, [r3]
	ldr	r3, .L1614+40
	strb	r5, [r8]
	str	r2, [r3]
	ldr	r3, .L1614+44
	str	r5, [r3]
	movs	r3, #60
	strb	r3, [r7]
	bl	NandcInit
	str	fp, [sp, #24]
	str	r10, [sp, #20]
	str	r8, [sp, #28]
.L1512:
	ldr	r3, .L1614+48
	uxtb	r8, r5
	mov	r0, r8
	ldr	fp, [r3, r5, lsl #3]
	add	r2, r3, r5, lsl #3
	ldrb	r10, [r2, #4]	@ zero_extendqisi2
	bl	FlashReset
	mov	r0, r8
	bl	NandcFlashCs
	add	fp, fp, r10, lsl #8
	movs	r2, #144
	mov	r10, #0
	str	r2, [fp, #2056]
	movs	r0, #200
	str	r10, [fp, #2052]
	bl	udelay
	ldr	r1, [fp, #2048]
	uxtb	r1, r1
	strb	r1, [r4]
	cmp	r1, #44
	ldr	r0, [fp, #2048]
	strb	r0, [r4, #1]
	ldr	r0, [fp, #2048]
	strb	r0, [r4, #2]
	ldr	r0, [fp, #2048]
	strb	r0, [r4, #3]
	ldr	r0, [fp, #2048]
	strb	r0, [r4, #4]
	ldr	r0, [fp, #2048]
	strb	r0, [r4, #5]
	bne	.L1507
	movs	r1, #239
	movs	r0, #200
	str	r1, [fp, #2056]
	movs	r1, #1
	str	r1, [fp, #2052]
	bl	udelay
	movs	r1, #4
	str	r1, [fp, #2048]
	str	r10, [fp, #2048]
	str	r10, [fp, #2048]
	str	r10, [fp, #2048]
.L1507:
	mov	r0, r8
	bl	NandcFlashDeCs
	ldrb	r2, [r4]	@ zero_extendqisi2
	subs	r3, r2, #1
	uxtb	r3, r3
	cmp	r3, #253
	bhi	.L1508
	ldrb	r1, [r4, #5]	@ zero_extendqisi2
	ldrb	r3, [r4, #1]	@ zero_extendqisi2
	ldr	r0, .L1614+52
	str	r1, [sp, #12]
	ldrb	r1, [r4, #4]	@ zero_extendqisi2
	str	r1, [sp, #8]
	ldrb	r1, [r4, #3]	@ zero_extendqisi2
	str	r1, [sp, #4]
	ldrb	r1, [r4, #2]	@ zero_extendqisi2
	str	r1, [sp]
	adds	r1, r5, #1
	bl	printf
.L1508:
	cbnz	r5, .L1509
	ldr	r2, .L1614+36
	ldrb	r3, [r2]	@ zero_extendqisi2
	subs	r3, r3, #1
	uxtb	r3, r3
	cmp	r3, #253
	bhi	.L1560
	ldrb	r3, [r2, #1]	@ zero_extendqisi2
	cmp	r3, #255
	beq	.L1560
.L1509:
	ldrb	r3, [r4]	@ zero_extendqisi2
	adds	r5, r5, #1
	adds	r4, r4, #8
	cmp	r3, #181
	itt	eq
	moveq	r3, #44
	strbeq	r3, [r4, #-8]
	cmp	r5, #4
	bne	.L1512
	ldr	r3, .L1614+36
	ldrb	r2, [r3]	@ zero_extendqisi2
	mov	r10, r3
	cmp	r2, #173
	beq	.L1513
	ldr	r3, .L1614+56
	ldr	r0, [r3]
	bl	NandcSetDdrMode
.L1513:
	ldr	r5, .L1614+60
	mov	r2, #852
	movs	r1, #0
	ldr	r0, .L1614+64
	bl	ftl_memset
	movs	r2, #0
	ldr	r4, .L1614+68
	strb	r2, [r5]
	mov	fp, r5
	ldr	r2, .L1614+72
	ldr	r3, .L1614+76
	ldr	r1, [r2]
	ldr	r2, .L1614+80
	str	r3, [r4]
	cmp	r1, r2
	mov	r8, r2
	bne	.L1514
	ldrb	r3, [r3, #19]	@ zero_extendqisi2
	cmp	r3, #50
	ittt	ne
	ldrne	r3, .L1614+84
	movne	r2, #1
	strne	r2, [r3]
.L1514:
	ldrb	r3, [r10, #1]	@ zero_extendqisi2
	cmp	r3, #161
	beq	.L1515
	cmp	r3, #241
	beq	.L1515
	cmp	r3, #218
	beq	.L1515
	and	r2, r3, #253
	cmp	r2, #209
	beq	.L1515
	cmp	r3, #220
	bne	.L1516
	ldrb	r2, [r10, #3]	@ zero_extendqisi2
	cmp	r2, #149
	bne	.L1516
.L1515:
	ldr	ip, .L1614+36
	movs	r0, #1
	ldr	r2, [sp, #20]
	ldr	r5, [sp, #24]
	ldrb	lr, [ip]	@ zero_extendqisi2
	strb	r0, [r2]
	movs	r2, #16
	strb	r2, [r5]
	strb	r2, [r7]
	cmp	lr, #152
	ldr	r2, .L1614+88
	strb	lr, [r2, #1]
	strb	r3, [r2, #2]
	bne	.L1518
	ldrsb	ip, [ip, #4]
	cmp	ip, #0
	blt	.L1519
	movs	r0, #24
	strb	r0, [r7]
.L1518:
	cmp	r1, r8
	beq	.L1521
	movw	r0, #2049
	cmp	r1, r0
	bne	.L1522
.L1521:
	movs	r1, #16
	strb	r1, [r7]
.L1522:
	cmp	r3, #218
	bne	.L1523
	mov	r1, #2048
.L1610:
	strh	r1, [r2, #14]	@ movhi
	strb	r3, [r2, #2]
.L1524:
	movs	r2, #32
	ldr	r1, .L1614+92
	ldr	r0, .L1614+96
	bl	ftl_memcpy
	movs	r2, #32
	ldr	r1, .L1614+88
	ldr	r0, .L1614+76
	bl	ftl_memcpy
.L1516:
	ldr	r3, [sp, #20]
	ldr	r10, .L1614+136
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1527
	bl	FlashLoadPhyInfoInRam
	cbnz	r0, .L1529
	ldr	r3, [r4]
	ldr	r7, .L1614+100
	ldrh	r3, [r3, #16]
	lsrs	r3, r3, #8
	lsls	r1, r3, #31
	and	r0, r3, #7
	strb	r0, [r7]
	bmi	.L1529
	movs	r3, #1
	strb	r3, [r6]
	bl	FlashSetInterfaceMode
	ldrb	r0, [r7]	@ zero_extendqisi2
	bl	NandcSetMode
.L1529:
	ldr	r3, [r4]
	ldrb	r3, [r3, #26]	@ zero_extendqisi2
	strb	r3, [r10]
	bl	FlashLoadPhyInfo
	cmp	r0, #0
	beq	.L1527
	ldr	r3, [r4]
	ldr	r0, .L1614+104
	ldrh	r1, [r3, #14]
	bl	printf
	bl	FlashLoadPhyInfoInRam
	adds	r2, r0, #1
	beq	.L1506
	bl	FlashDieInfoInit
	ldr	r3, [r4]
	ldrb	r0, [r3, #19]	@ zero_extendqisi2
	bl	FlashGetReadRetryDefault
	ldr	r3, [r4]
	ldr	r2, .L1614+108
	ldrb	r1, [r3, #9]	@ zero_extendqisi2
	ldrh	r2, [r2]
	addw	r2, r2, #4095
	cmp	r1, r2, asr #12
	blt	.L1532
	ldrh	r2, [r3, #14]
	adds	r2, r2, #255
	cmp	r1, r2, asr #8
	bge	.L1533
.L1532:
	ldrh	r2, [r3, #14]
	bic	r2, r2, #255
	strh	r2, [r3, #14]	@ movhi
.L1533:
	ldr	r3, .L1614+100
	ldrb	r3, [r3]	@ zero_extendqisi2
	tst	r3, #6
	beq	.L1534
	bl	FlashSavePhyInfo
	movs	r0, #0
	bl	flash_enter_slc_mode
	ldr	r3, .L1614+112
	movs	r0, #0
	ldr	r1, [r3]
	bl	FlashDdrParaScan
	movs	r0, #0
	bl	flash_exit_slc_mode
.L1534:
	bl	FlashSavePhyInfo
.L1527:
	ldr	r7, [r4]
	ldr	r5, .L1614+116
	ldrh	r2, [r7, #16]
	ldrb	r3, [r7, #26]	@ zero_extendqisi2
	ldrh	r0, [r7, #10]
	ubfx	r1, r2, #3, #1
	strb	r3, [r10]
	ubfx	r3, r2, #7, #1
	strb	r3, [fp]
	mov	fp, #0
	ldr	r3, .L1614+120
	str	fp, [r5]
	strb	r1, [r3]
	b	.L1615
.L1616:
	.align	2
.L1614:
	.word	.LANCHOR154
	.word	.LANCHOR149
	.word	.LANCHOR30
	.word	.LANCHOR205
	.word	.LANCHOR158
	.word	.LANCHOR206
	.word	.LANCHOR207
	.word	.LANCHOR157
	.word	.LANCHOR156
	.word	.LANCHOR22
	.word	.LANCHOR4
	.word	.LANCHOR144
	.word	.LANCHOR0
	.word	.LC24
	.word	.LANCHOR160
	.word	.LANCHOR6
	.word	.LANCHOR20
	.word	.LANCHOR7
	.word	.LANCHOR122
	.word	.LANCHOR31
	.word	1446522928
	.word	.LANCHOR29
	.word	.LANCHOR209
	.word	.LANCHOR152+32
	.word	.LANCHOR8
	.word	.LANCHOR25
	.word	.LC25
	.word	.LANCHOR125
	.word	.LANCHOR155
	.word	.LANCHOR145
	.word	.LANCHOR210
	.word	.LANCHOR3
	.word	.LANCHOR2
	.word	.LANCHOR208
	.word	.LANCHOR16
.L1615:
	ubfx	r1, r2, #4, #1
	ldr	r3, .L1617
	ubfx	r2, r2, #8, #3
	strb	r1, [r3]
	ldr	r3, .L1617+4
	ldrb	r1, [r7, #12]	@ zero_extendqisi2
	strb	r2, [r3]
	str	r3, [sp, #28]
	bl	__aeabi_idiv
	mov	r1, r0
	ldrb	r0, [r7, #18]	@ zero_extendqisi2
	bl	BuildFlashLsbPageTable
	bl	FlashDieInfoInit
	ldr	r2, [r4]
	mov	ip, r5
	ldr	r3, [sp, #28]
	ldrh	r1, [r2, #16]
	mov	r7, r3
	tst	r1, #64
	beq	.L1536
	ldrb	r0, [r2, #19]	@ zero_extendqisi2
	ldr	r3, .L1617+8
	ldr	r1, .L1617+12
	strb	r0, [r3]
	ldrb	r2, [r1, #1]	@ zero_extendqisi2
	ldr	r3, .L1617+16
	ldrb	r1, [r1, #2]	@ zero_extendqisi2
	strb	r2, [r3]
	ldr	r2, .L1617+20
	strb	r1, [r2]
	subs	r1, r0, #1
	cmp	r1, #7
	mov	r1, r2
	bhi	.L1537
	ldr	r3, .L1617+24
	str	r3, [r5]
	subs	r3, r0, #5
	cmp	r3, #1
	bls	.L1538
	cmp	r0, #8
	bne	.L1539
.L1538:
	ldr	r3, .L1617+28
	movs	r2, #1
	str	r2, [r3]
.L1539:
	cmp	r0, #7
	ldr	r3, .L1617+32
	beq	.L1540
	sub	r2, r3, #8
	cmp	r0, #8
	it	ne
	movne	r3, r2
.L1540:
	subs	r1, r3, #1
	movs	r2, #0
	adds	r3, r3, #31
.L1542:
	ldrsb	r5, [r1, #1]!
	cbnz	r5, .L1541
	adds	r2, r2, #1
.L1541:
	cmp	r3, r1
	bne	.L1542
	cmp	r2, #27
	bls	.L1536
	bl	FlashGetReadRetryDefault
	bl	FlashSavePhyInfo
.L1536:
	ldr	r3, .L1617+36
	ldr	r3, [r3]
	cmp	r3, r8
	bne	.L1554
	ldrb	r3, [r10]	@ zero_extendqisi2
	cbz	r3, .L1554
	ldr	r3, .L1617+40
	movs	r2, #0
	ldr	r3, [r3]
	strb	r2, [r3, #18]
.L1554:
	ldr	r3, .L1617+44
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, #44
	bne	.L1555
	ldrb	r3, [r6]	@ zero_extendqisi2
	cbz	r3, .L1555
	movs	r3, #0
	movs	r0, #1
	strb	r3, [r6]
	bl	FlashSetInterfaceMode
	movs	r0, #1
	bl	NandcSetMode
.L1555:
	ldrb	r3, [r7]	@ zero_extendqisi2
	tst	r3, #6
	beq	.L1556
	ldrb	r2, [r6]	@ zero_extendqisi2
	cbnz	r2, .L1557
	lsls	r3, r3, #31
	bmi	.L1556
.L1557:
	movs	r0, #0
	bl	flash_enter_slc_mode
	ldr	r3, .L1617+48
	movs	r0, #0
	ldr	r1, [r3]
	bl	FlashDdrParaScan
	movs	r0, #0
	bl	flash_exit_slc_mode
.L1556:
	ldr	r3, [r4]
	movs	r6, #16
	ldrb	r0, [r3, #20]	@ zero_extendqisi2
	bl	FlashBchSel
	ldr	r0, .L1617+52
	bl	FlashReadIdbDataRaw
	ldr	r7, [r4]
	ldr	r3, [sp, #24]
	ldr	r4, .L1617+56
	ldrb	r1, [r7, #12]	@ zero_extendqisi2
	strb	r6, [r3]
	ldrh	r5, [r7, #10]
	strh	r1, [r4, #8]	@ movhi
	ldrb	r3, [r7, #7]	@ zero_extendqisi2
	ldrh	r8, [r7, #14]
	mov	r0, r5
	str	r3, [r4, #4]
	ldr	r3, .L1617+44
	ldrb	r2, [r3, #1]	@ zero_extendqisi2
	lsl	r3, r2, r6
	orr	r3, r3, r2, lsl #8
	ldr	r2, .L1617+44
	ldrb	r2, [r2]	@ zero_extendqisi2
	orrs	r3, r3, r2
	ldr	r2, .L1617+44
	ldrb	r2, [r2, #3]	@ zero_extendqisi2
	orr	r3, r3, r2, lsl #24
	str	r3, [r4]
	ldr	r3, .L1617+60
	ldrb	r3, [r3]	@ zero_extendqisi2
	strh	r3, [r4, #10]	@ movhi
	ldrb	r3, [r7, #13]	@ zero_extendqisi2
	strh	r5, [r4, #16]	@ movhi
	strh	r8, [r4, #14]	@ movhi
	strh	r3, [r4, #12]	@ movhi
	bl	__aeabi_idiv
	mov	r2, #512
	strh	r0, [r4, #18]	@ movhi
	ldrb	r3, [r7, #9]	@ zero_extendqisi2
	strh	r2, [r4, #24]	@ movhi
	ldr	r2, [sp, #20]
	strh	r3, [r4, #20]	@ movhi
	smulbb	r5, r5, r3
	strh	r6, [r4, #26]	@ movhi
	ldrb	r2, [r2]	@ zero_extendqisi2
	uxth	r5, r5
	cmp	r2, #1
	strh	r5, [r4, #22]	@ movhi
	bne	.L1558
	lsls	r3, r3, #1
	lsr	r2, r8, #1
	lsls	r5, r5, #1
	strh	r3, [r4, #20]	@ movhi
	movs	r3, #8
	strh	r2, [r4, #14]	@ movhi
	strh	r5, [r4, #22]	@ movhi
	strh	r3, [r4, #26]	@ movhi
.L1558:
	ldrb	r0, [r7, #20]	@ zero_extendqisi2
	bl	FlashBchSel
	movs	r0, #0
.L1506:
	add	sp, sp, #32
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r10, fp, pc}
.L1523:
	cmp	r3, #220
	bne	.L1525
	mov	r1, #4096
	b	.L1610
.L1525:
	cmp	r3, #211
	itttt	eq
	moveq	r3, #4096
	strheq	r3, [r2, #14]	@ movhi
	moveq	r3, #2
	strbeq	r3, [r2, #13]
	b	.L1524
.L1537:
	sub	lr, r0, #17
	cmp	lr, #2
	bhi	.L1544
	ldr	r3, .L1617+64
	cmp	r0, #19
	str	r3, [r5]
	ite	ne
	movne	r3, #7
	moveq	r3, #15
	strb	r3, [r2]
	b	.L1536
.L1544:
	cmp	r0, #33
	beq	.L1546
	sub	r2, r0, #65
	cmp	r2, #1
	bhi	.L1547
.L1546:
	ldr	r2, .L1617+68
	str	r2, [ip]
	movs	r2, #4
	strb	r2, [r3]
	movs	r3, #7
	strb	r3, [r1]
	b	.L1536
.L1547:
	sub	r2, r0, #67
	uxtb	r2, r2
	cmp	r2, #1
	bls	.L1548
	sub	r1, r0, #34
	cmp	r1, #1
	bhi	.L1549
.L1548:
	ldr	r1, .L1617+72
	cmp	r0, #35
	ldr	r5, .L1617+68
	str	r5, [r1]
	ldr	r1, .L1617+20
	beq	.L1550
	cmp	r0, #68
	beq	.L1550
	movs	r0, #7
.L1611:
	cmp	r2, #1
	strb	r0, [r1]
	ite	ls
	movls	r2, #4
	movhi	r2, #5
	strb	r2, [r3]
	b	.L1536
.L1550:
	movs	r0, #17
	b	.L1611
.L1549:
	cmp	r0, #49
	bne	.L1553
	ldr	r3, .L1617+76
	str	r3, [r5]
	b	.L1536
.L1553:
	cmp	r0, #50
	itttt	eq
	ldreq	r3, .L1617+80
	streq	r3, [r5]
	ldreq	r3, .L1617+84
	streq	fp, [r3]
	b	.L1536
.L1560:
	mvn	r0, #1
	b	.L1506
.L1519:
	ldr	r5, [sp, #28]
	strb	r0, [r5]
	b	.L1518
.L1618:
	.align	2
.L1617:
	.word	.LANCHOR28
	.word	.LANCHOR25
	.word	.LANCHOR10
	.word	.LANCHOR20
	.word	.LANCHOR13
	.word	.LANCHOR146
	.word	HynixReadRetrial
	.word	.LANCHOR36
	.word	.LANCHOR20+28
	.word	.LANCHOR122
	.word	.LANCHOR7
	.word	.LANCHOR22
	.word	.LANCHOR155
	.word	.LANCHOR150
	.word	.LANCHOR15
	.word	.LANCHOR26
	.word	MicronReadRetrial
	.word	ToshibaReadRetrial
	.word	.LANCHOR145
	.word	SamsungReadRetrial
	.word	samsung_read_retrial
	.word	.LANCHOR29
	.size	FlashInit, .-FlashInit
	.section	.text.FlashReadSlc2KPages,"ax",%progbits
	.align	1
	.global	FlashReadSlc2KPages
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	FlashReadSlc2KPages, %function
FlashReadSlc2KPages:
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 0, uses_anonymous_args = 0
	ldr	r3, .L1676
	push	{r4, r5, r6, r7, r8, r10, fp, lr}
	mov	r4, r0
	movs	r7, #0
	sub	sp, sp, #24
	ldrb	fp, [r3, #9]	@ zero_extendqisi2
	str	r1, [sp, #8]
	str	r2, [sp, #12]
.L1620:
	ldr	r3, [sp, #8]
	cmp	r7, r3
	bne	.L1644
	movs	r0, #0
	add	sp, sp, #24
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r10, fp, pc}
.L1644:
	ldr	r3, [sp, #8]
	add	r2, sp, #20
	ldr	r1, [sp, #12]
	mov	r0, r4
	subs	r3, r3, r7
	uxtb	r3, r3
	str	r3, [sp]
	add	r3, sp, #16
	bl	LogAddr2PhyAddr
	ldr	r2, .L1676+4
	ldr	r3, [sp, #16]
	ldrb	r2, [r2]	@ zero_extendqisi2
	cmp	r2, r3
	bhi	.L1621
	mov	r3, #-1
	str	r3, [r4]
.L1622:
	adds	r7, r7, #1
	adds	r4, r4, #36
	b	.L1620
.L1621:
	ldr	r2, .L1676+8
	mov	r8, #0
	ldrb	r5, [r2, r3]	@ zero_extendqisi2
	mov	r0, r5
	bl	NandcWaitFlashReady
	mov	r0, r5
	bl	NandcFlashCs
.L1623:
	ldr	r1, [sp, #20]
	mov	r0, r5
	bl	FlashReadCmd
	mov	r0, r5
	bl	NandcWaitFlashReady
	ldr	r3, [r4, #12]
	mov	r2, fp
	movs	r1, #0
	mov	r0, r5
	str	r3, [sp]
	ldr	r3, [r4, #8]
	bl	NandcXferData
	ldr	r3, .L1676+12
	mov	r6, r0
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1624
.L1627:
	adds	r3, r6, #1
	beq	.L1625
.L1626:
	cmp	r8, #0
	beq	.L1629
.L1628:
	mov	r6, #256
.L1629:
	mov	r8, #0
.L1630:
	ldr	r3, .L1676+16
	mov	r0, r5
	ldr	r1, [sp, #20]
	ldr	r3, [r3]
	add	r1, r1, r3
	bl	FlashReadCmd
	mov	r0, r5
	bl	NandcWaitFlashReady
	ldr	r3, [r4, #8]
	cbz	r3, .L1631
	add	r3, r3, #2048
.L1631:
	ldr	r2, [r4, #12]
	cbz	r2, .L1632
	adds	r2, r2, #8
.L1632:
	str	r2, [sp]
	movs	r1, #0
	mov	r2, fp
	mov	r0, r5
	bl	NandcXferData
	ldr	r3, .L1676+12
	mov	r10, r0
	ldrb	r2, [r3]	@ zero_extendqisi2
	cmp	r2, #0
	bne	.L1633
.L1636:
	cmp	r10, #-1
	beq	.L1634
.L1635:
	cmp	r8, #0
	beq	.L1638
.L1637:
	mov	r10, #256
.L1638:
	mov	r0, r5
	bl	NandcFlashDeCs
	ldr	r2, .L1676+20
	cmp	r6, r10
	it	cc
	movcc	r6, r10
	ldrb	r2, [r2]	@ zero_extendqisi2
	add	r3, r2, r2, lsl #1
	cmp	r6, r3, asr #2
	bhi	.L1639
	movs	r3, #0
.L1675:
	str	r3, [r4]
	ldr	r3, [r4, #12]
	cbz	r3, .L1640
	ldr	r1, [r3, #12]
	adds	r1, r1, #1
	bne	.L1640
	ldr	r1, [r3, #8]
	adds	r0, r1, #1
	bne	.L1640
	ldr	r3, [r3]
	adds	r3, r3, #1
	it	ne
	strne	r1, [r4]
.L1640:
	ldr	r3, [r4]
	adds	r1, r3, #1
	bne	.L1622
	ldr	r1, [r4, #4]
	ldr	r0, .L1676+24
	bl	printf
	ldr	r1, [r4, #8]
	cbz	r1, .L1642
	movs	r3, #8
	movs	r2, #4
	ldr	r0, .L1676+28
	bl	rknand_print_hex
.L1642:
	ldr	r1, [r4, #12]
	cmp	r1, #0
	beq	.L1622
	movs	r3, #4
	ldr	r0, .L1676+32
	mov	r2, r3
	bl	rknand_print_hex
	b	.L1622
.L1624:
	mov	r0, r5
	bl	flash_read_ecc
	cmp	r0, #5
	bls	.L1627
	mov	r6, #256
	b	.L1626
.L1625:
	cmp	r8, #10
	beq	.L1628
	add	r8, r8, #1
	b	.L1623
.L1633:
	mov	r0, r5
	bl	flash_read_ecc
	cmp	r0, #5
	bls	.L1636
	mov	r10, #256
	b	.L1635
.L1634:
	cmp	r8, #10
	beq	.L1637
	add	r8, r8, #1
	b	.L1630
.L1639:
	mov	r3, #256
	b	.L1675
.L1677:
	.align	2
.L1676:
	.word	.LANCHOR31
	.word	.LANCHOR26
	.word	.LANCHOR27
	.word	.LANCHOR208
	.word	.LANCHOR4
	.word	.LANCHOR33
	.word	.LC26
	.word	.LC27
	.word	.LC28
	.size	FlashReadSlc2KPages, .-FlashReadSlc2KPages
	.section	.text.FlashReadPages,"ax",%progbits
	.align	1
	.global	FlashReadPages
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	FlashReadPages, %function
FlashReadPages:
	@ args = 0, pretend = 0, frame = 32
	@ frame_needed = 0, uses_anonymous_args = 0
	ldr	r3, .L1769
	push	{r4, r5, r6, r7, r8, r10, fp, lr}
	sub	sp, sp, #40
	mov	r10, r0
	str	r1, [sp, #24]
	ldrb	r3, [r3]	@ zero_extendqisi2
	str	r2, [sp, #12]
	cbnz	r3, .L1679
	ldr	r2, .L1769+4
	mov	r8, r3
	str	r3, [sp, #8]
	ldrb	r2, [r2, #9]	@ zero_extendqisi2
	str	r2, [sp, #20]
	ldr	r2, .L1769+8
	ldrb	r2, [r2]	@ zero_extendqisi2
	str	r2, [sp, #28]
.L1680:
	ldr	r3, [sp, #8]
	ldr	r2, [sp, #24]
	cmp	r3, r2
	bcc	.L1718
	movs	r0, #0
	b	.L1678
.L1679:
	bl	FlashReadSlc2KPages
.L1678:
	add	sp, sp, #40
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r10, fp, pc}
.L1718:
	ldr	r2, [sp, #8]
	movs	r3, #36
	ldr	r1, [sp, #12]
	mul	fp, r3, r2
	add	r7, r10, fp
	ldr	r3, [r7, #4]
	mov	r0, r7
	str	r3, [sp, #16]
	ldr	r3, [sp, #24]
	subs	r3, r3, r2
	add	r2, sp, #36
	uxtb	r3, r3
	str	r3, [sp]
	add	r3, sp, #32
	bl	LogAddr2PhyAddr
	ldr	r2, .L1769+12
	mov	r5, r0
	ldr	r3, [sp, #32]
	ldrb	r2, [r2]	@ zero_extendqisi2
	cmp	r2, r3
	bhi	.L1682
	mov	r3, #-1
	str	r3, [r10, fp]
.L1683:
	ldr	r3, [sp, #8]
	adds	r3, r3, #1
	str	r3, [sp, #8]
	b	.L1680
.L1682:
	ldr	r2, .L1769+16
	ldrb	r4, [r2, r3]	@ zero_extendqisi2
	ldr	r3, .L1769+20
	mov	r0, r4
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, #0
	it	eq
	moveq	r5, #0
	bl	NandcWaitFlashReady
	ldr	r3, .L1769+24
	ldr	r3, [r3]
	ldrb	r2, [r3, #19]	@ zero_extendqisi2
	subs	r3, r2, #1
	cmp	r3, #7
	bhi	.L1685
	ldr	r3, .L1769+28
	subs	r2, r2, #7
	cmp	r2, #1
	ldr	r2, .L1769+32
	add	r1, r3, r4
	ldrb	r3, [r1, #12]	@ zero_extendqisi2
	ldrb	r2, [r2, r4]	@ zero_extendqisi2
	it	ls
	ldrbls	r3, [r1, #20]	@ zero_extendqisi2
	cmp	r2, r3
	beq	.L1685
	ldr	r2, .L1769+36
	mov	r0, r4
	ldrb	r1, [r2, #-3]	@ zero_extendqisi2
	bl	HynixSetRRPara
.L1685:
	mov	r0, r4
	bl	NandcFlashCs
	ldr	r3, [sp, #12]
	cmp	r3, #1
	beq	.L1687
	ldr	r3, [sp, #16]
	cmp	r3, #0
	bge	.L1688
.L1687:
	ldr	r3, .L1769+40
	ldrb	r3, [r3]	@ zero_extendqisi2
	cbz	r3, .L1688
	mov	r0, r4
	bl	flash_enter_slc_mode
.L1695:
	ldr	r1, [sp, #36]
	adds	r6, r1, #1
	bne	.L1690
	cmp	r4, #255
	beq	.L1720
.L1690:
	cbz	r5, .L1692
	ldr	r3, .L1769+44
	mov	r0, r4
	ldr	r2, [r3]
	add	r2, r2, r1
	bl	FlashReadDpCmd
.L1693:
	mov	r0, r4
	bl	NandcWaitFlashReady
	cbz	r5, .L1691
	ldr	r1, [sp, #36]
	mov	r0, r4
	bl	FlashReadDpDataOutCmd
.L1691:
	ldr	r3, [r7, #12]
	movs	r1, #0
	ldr	r2, [sp, #20]
	mov	r0, r4
	str	r3, [sp]
	ldr	r3, [r7, #8]
	bl	NandcXferData
	ldr	r3, .L1769+8
	mov	r6, r0
	ldrb	r3, [r3]	@ zero_extendqisi2
	cbz	r3, .L1694
	adds	r0, r0, #1
	bne	.L1694
	ldr	r3, .L1769+8
	movs	r5, #0
	strb	r5, [r3]
	b	.L1695
.L1688:
	mov	r0, r4
	bl	flash_exit_slc_mode
	b	.L1695
.L1692:
	mov	r0, r4
	bl	FlashReadCmd
	b	.L1693
.L1720:
	movs	r5, #0
	b	.L1691
.L1694:
	cbz	r5, .L1696
	ldr	r3, .L1769+44
	mov	r0, r4
	ldr	r1, [sp, #36]
	ldr	r3, [r3]
	add	r1, r1, r3
	bl	FlashReadDpDataOutCmd
	add	r3, fp, #36
	movs	r1, #0
	add	r3, r3, r10
	mov	r0, r4
	ldr	r2, [r3, #12]
	str	r2, [sp]
	ldr	r2, [sp, #20]
	ldr	r3, [r3, #8]
	bl	NandcXferData
	cmp	r0, #-1
	mov	r8, r0
	it	eq
	moveq	r5, #0
.L1696:
	mov	r0, r4
	bl	NandcFlashDeCs
	ldr	r3, .L1769+8
	adds	r1, r6, #1
	ldrb	r2, [sp, #28]	@ zero_extendqisi2
	strb	r2, [r3]
	bne	.L1697
	ldr	r3, .L1769+48
	ldrb	r3, [r3]	@ zero_extendqisi2
	cbnz	r3, .L1698
.L1702:
	ldr	r3, .L1769+52
	ldr	r5, [r3]
	cmp	r5, #0
	bne	.L1699
	ldr	r3, [r7, #12]
	mov	r0, r4
	ldr	r2, [r7, #8]
	ldr	r1, [sp, #36]
	bl	FlashReadRawPage
	b	.L1768
.L1698:
	ldr	r3, .L1769+56
	mov	r0, r4
	ldr	r1, [sp, #36]
	ldr	r3, [r3]
	ldr	r5, [r3, #304]
	movs	r3, #1
	str	r3, [sp]
	ldr	r2, [r7, #8]
	ldr	r3, [r7, #12]
	bl	FlashDdrTunningRead
	adds	r2, r0, #1
	mov	r6, r0
	beq	.L1701
	ldr	r3, .L1769+60
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r0, r3, lsr #1
	bls	.L1721
.L1701:
	ubfx	r0, r5, #8, #8
	bl	NandcSetDdrPara
	adds	r3, r6, #1
	beq	.L1702
.L1721:
	movs	r5, #0
.L1697:
	ldr	r3, .L1769+60
	ldrb	r3, [r3]	@ zero_extendqisi2
	add	r3, r3, r3, lsl #1
	cmp	r6, r3, asr #2
	bls	.L1710
	ldr	r3, .L1769+52
	ldr	r3, [r3]
	cmp	r3, #0
	bne	.L1710
	mov	r6, #256
	b	.L1705
.L1770:
	.align	2
.L1769:
	.word	.LANCHOR2
	.word	.LANCHOR31
	.word	.LANCHOR6
	.word	.LANCHOR26
	.word	.LANCHOR27
	.word	.LANCHOR210
	.word	.LANCHOR7
	.word	.LANCHOR20
	.word	.LANCHOR21
	.word	.LANCHOR20+4
	.word	.LANCHOR16
	.word	.LANCHOR4
	.word	.LANCHOR30
	.word	.LANCHOR145
	.word	.LANCHOR19
	.word	.LANCHOR33
.L1699:
	ldr	r3, [r7, #12]
	mov	r0, r4
	ldr	r2, [r7, #8]
	ldr	r1, [sp, #36]
	blx	r5
	adds	r5, r0, #1
	mov	r6, r0
	bne	.L1703
	ldr	r3, .L1771
	ldr	r3, [r3]
	ldrb	r3, [r3, #19]	@ zero_extendqisi2
	subs	r3, r3, #1
	cmp	r3, #7
	bhi	.L1704
	ldr	r2, .L1771+4
	movs	r3, #0
	mov	r0, r4
	ldrb	r1, [r2, #-3]	@ zero_extendqisi2
	bl	HynixSetRRPara
.L1704:
	ldr	r3, [r7, #12]
	mov	r0, r4
	ldr	r2, [r7, #8]
	ldr	r1, [sp, #36]
	bl	FlashReadRawPage
	ldr	r2, .L1771+8
	mov	r6, r0
	mov	r3, r0
	ldr	r1, [r7, #4]
	ldr	r0, .L1771+12
	ldrb	r2, [r2]	@ zero_extendqisi2
	bl	printf
	adds	r0, r6, #1
	bne	.L1703
	ldr	r3, .L1771+16
	ldrb	r5, [r3]	@ zero_extendqisi2
	cbz	r5, .L1705
	ldr	r3, [sp, #12]
	mov	r0, r4
	cmp	r3, #1
	beq	.L1706
	ldr	r3, [sp, #16]
	cmp	r3, #0
	bge	.L1707
.L1706:
	bl	flash_enter_slc_mode
.L1708:
	ldr	r3, .L1771+20
	mov	r0, r4
	ldr	r2, [r7, #8]
	ldr	r1, [sp, #36]
	ldr	r5, [r3]
	ldr	r3, [r7, #12]
	blx	r5
.L1768:
	adds	r1, r0, #1
	mov	r6, r0
	mov	r5, #0
	bne	.L1710
.L1705:
	str	r6, [r10, fp]
.L1711:
	ldr	r3, [r10, fp]
	adds	r2, r3, #1
	bne	.L1713
	ldr	r2, .L1771+8
	ldr	r1, [r7, #4]
	ldr	r0, .L1771+24
	ldrb	r2, [r2]	@ zero_extendqisi2
	bl	printf
	ldr	r1, [r7, #12]
	cbz	r1, .L1713
	movs	r3, #4
	ldr	r0, .L1771+28
	mov	r2, r3
	bl	rknand_print_hex
.L1713:
	cbz	r5, .L1715
	ldr	r3, .L1771+8
	ldrb	r3, [r3]	@ zero_extendqisi2
	add	r3, r3, r3, lsl #1
	cmp	r8, r3, asr #2
	bls	.L1716
	ldr	r3, .L1771+20
	ldr	r3, [r3]
	cmp	r3, #0
	it	eq
	moveq	r8, #256
.L1716:
	cmp	r8, #-1
	add	r3, fp, #36
	str	r8, [r10, r3]
	beq	.L1715
	cmp	r8, #256
	itt	ne
	movne	r2, #0
	strne	r2, [r10, r3]
.L1715:
	ldr	r3, [sp, #8]
	add	r3, r3, r5
	str	r3, [sp, #8]
	ldr	r3, [sp, #12]
	cmp	r3, #1
	beq	.L1717
	ldr	r3, [sp, #16]
	cmp	r3, #0
	bge	.L1683
.L1717:
	ldr	r3, .L1771+16
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1683
	mov	r0, r4
	bl	flash_exit_slc_mode
	b	.L1683
.L1707:
	bl	flash_exit_slc_mode
	b	.L1708
.L1703:
	movs	r5, #0
.L1710:
	cmp	r6, #256
	beq	.L1705
	movs	r3, #0
	str	r3, [r10, fp]
	b	.L1711
.L1772:
	.align	2
.L1771:
	.word	.LANCHOR7
	.word	.LANCHOR20+4
	.word	.LANCHOR33
	.word	.LC29
	.word	.LANCHOR16
	.word	.LANCHOR145
	.word	.LC26
	.word	.LC28
	.size	FlashReadPages, .-FlashReadPages
	.section	.text.FlashProgSlc2KPages,"ax",%progbits
	.align	1
	.global	FlashProgSlc2KPages
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	FlashProgSlc2KPages, %function
FlashProgSlc2KPages:
	@ args = 0, pretend = 0, frame = 56
	@ frame_needed = 0, uses_anonymous_args = 0
	ldr	r3, .L1800
	push	{r4, r5, r6, r7, r8, r10, fp, lr}
	mov	r8, r1
	ldr	fp, .L1800+32
	mov	r4, r0
	mov	r6, r0
	movs	r7, #0
	ldrb	r10, [r3, #9]	@ zero_extendqisi2
	sub	sp, sp, #64
	str	r2, [sp, #12]
.L1774:
	cmp	r7, r8
	bne	.L1780
	ldr	r10, .L1800+36
	mov	r8, #0
.L1781:
	cmp	r7, r8
	bne	.L1788
	movs	r0, #0
	add	sp, sp, #64
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r10, fp, pc}
.L1780:
	sub	r3, r8, r7
	add	r2, sp, #20
	uxtb	r3, r3
	ldr	r1, [sp, #12]
	mov	r0, r6
	str	r3, [sp]
	add	r3, sp, #24
	bl	LogAddr2PhyAddr
	ldr	r2, .L1800+4
	ldr	r3, [sp, #24]
	ldrb	r2, [r2]	@ zero_extendqisi2
	cmp	r2, r3
	bhi	.L1775
	mov	r3, #-1
	str	r3, [r6]
.L1776:
	adds	r7, r7, #1
	adds	r6, r6, #36
	b	.L1774
.L1775:
	ldr	r2, .L1800+8
	ldrb	r5, [r2, r3]	@ zero_extendqisi2
	mov	r0, r5
	bl	NandcWaitFlashReady
	mov	r0, r5
	bl	NandcFlashCs
	ldr	r1, [sp, #20]
	mov	r0, r5
	bl	FlashProgFirstCmd
	ldr	r3, [r6, #12]
	mov	r2, r10
	movs	r1, #1
	mov	r0, r5
	str	r3, [sp]
	ldr	r3, [r6, #8]
	bl	NandcXferData
	ldr	r1, [sp, #20]
	mov	r0, r5
	bl	FlashProgSecondCmd
	mov	r0, r5
	bl	NandcWaitFlashReady
	ldr	r1, [sp, #20]
	mov	r0, r5
	bl	FlashReadStatus
	sbfx	r0, r0, #0, #1
	ldr	r1, [sp, #20]
	str	r0, [r6]
	mov	r0, r5
	ldr	r3, [fp]
	add	r1, r1, r3
	bl	FlashProgFirstCmd
	ldr	r3, [r6, #8]
	cbz	r3, .L1777
	add	r3, r3, #2048
.L1777:
	ldr	r2, [r6, #12]
	cbz	r2, .L1778
	adds	r2, r2, #8
.L1778:
	str	r2, [sp]
	movs	r1, #1
	mov	r2, r10
	mov	r0, r5
	bl	NandcXferData
	ldr	r3, [fp]
	mov	r0, r5
	ldr	r1, [sp, #20]
	add	r1, r1, r3
	bl	FlashProgSecondCmd
	mov	r0, r5
	bl	NandcWaitFlashReady
	ldr	r1, [sp, #20]
	mov	r0, r5
	bl	FlashReadStatus
	lsls	r2, r0, #31
	mov	r0, r5
	itt	mi
	movmi	r3, #-1
	strmi	r3, [r6]
	bl	NandcFlashDeCs
	b	.L1776
.L1788:
	ldr	r3, [r4]
	adds	r3, r3, #1
	bne	.L1782
	ldr	r1, [r4, #4]
	ldr	r0, .L1800+12
	bl	printf
.L1783:
	add	r8, r8, #1
	adds	r4, r4, #36
	b	.L1781
.L1782:
	sub	r3, r7, r8
	ldr	fp, .L1800+40
	uxtb	r3, r3
	add	r2, sp, #20
	ldr	r1, [sp, #12]
	mov	r0, r4
	str	r3, [sp]
	add	r3, sp, #24
	bl	LogAddr2PhyAddr
	ldr	lr, [r10]
	movs	r3, #0
	ldr	ip, [fp]
	mov	r6, r4
	add	r5, sp, #28
	str	r3, [lr]
	str	r3, [ip]
	ldmia	r6!, {r0, r1, r2, r3}
	stmia	r5!, {r0, r1, r2, r3}
	str	lr, [sp, #36]
	ldmia	r6!, {r0, r1, r2, r3}
	str	ip, [sp, #40]
	stmia	r5!, {r0, r1, r2, r3}
	movs	r1, #1
	ldr	r3, [r6]
	add	r0, sp, #28
	ldr	r2, [sp, #12]
	str	r3, [r5]
	bl	FlashReadPages
	ldr	r5, [sp, #28]
	adds	r3, r5, #1
	bne	.L1784
	ldr	r1, [r4, #4]
	ldr	r0, .L1800+16
	bl	printf
	str	r5, [r4]
.L1784:
	ldr	r5, [sp, #28]
	cmp	r5, #256
	bne	.L1785
	ldr	r1, [r4, #4]
	ldr	r0, .L1800+20
	bl	printf
	str	r5, [r4]
.L1785:
	ldr	r3, [r4, #12]
	cbz	r3, .L1786
	ldr	r2, [r3]
	ldr	r3, [fp]
	ldr	r3, [r3]
	cmp	r2, r3
	beq	.L1786
	ldr	r1, [r4, #4]
	ldr	r0, .L1800+24
	bl	printf
	mov	r3, #-1
	str	r3, [r4]
.L1786:
	ldr	r3, [r4, #8]
	cmp	r3, #0
	beq	.L1783
	ldr	r2, [r3]
	ldr	r3, [r10]
	ldr	r3, [r3]
	cmp	r2, r3
	beq	.L1783
	ldr	r1, [r4, #4]
	ldr	r0, .L1800+28
	bl	printf
	mov	r3, #-1
	str	r3, [r4]
	b	.L1783
.L1801:
	.align	2
.L1800:
	.word	.LANCHOR31
	.word	.LANCHOR26
	.word	.LANCHOR27
	.word	.LC30
	.word	.LC31
	.word	.LC32
	.word	.LC33
	.word	.LC34
	.word	.LANCHOR4
	.word	.LANCHOR206
	.word	.LANCHOR207
	.size	FlashProgSlc2KPages, .-FlashProgSlc2KPages
	.section	.text.FlashProgPages,"ax",%progbits
	.align	1
	.global	FlashProgPages
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	FlashProgPages, %function
FlashProgPages:
	@ args = 0, pretend = 0, frame = 64
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, r8, r10, fp, lr}
	sub	sp, sp, #72
	ldr	r5, .L1854
	mov	r4, r0
	mov	r8, r2
	str	r1, [sp, #8]
	ldr	r5, [r5]
	str	r3, [sp, #20]
	ldrb	r5, [r5, #19]	@ zero_extendqisi2
	str	r5, [sp, #16]
	ldr	r5, .L1854+4
	ldrb	r7, [r5]	@ zero_extendqisi2
	cbnz	r7, .L1803
	ldr	r3, .L1854+8
	ldrb	r3, [r3, #9]	@ zero_extendqisi2
	str	r3, [sp, #12]
.L1804:
	ldr	r3, [sp, #8]
	cmp	r7, r3
	bcc	.L1817
	ldr	r6, .L1854+12
	movs	r5, #0
	ldr	r7, .L1854+16
.L1818:
	ldrb	r3, [r6]	@ zero_extendqisi2
	cmp	r5, r3
	bcc	.L1820
	ldr	r3, [sp, #20]
	cmp	r3, #0
	bne	.L1821
.L1829:
	movs	r0, #0
	b	.L1802
.L1803:
	bl	FlashProgSlc2KPages
.L1802:
	add	sp, sp, #72
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r10, fp, pc}
.L1817:
	ldr	r3, [sp, #8]
	movs	r6, #36
	muls	r6, r7, r6
	add	r2, sp, #28
	mov	r1, r8
	subs	r3, r3, r7
	uxtb	r3, r3
	add	fp, r4, r6
	str	r3, [sp]
	mov	r0, fp
	add	r3, sp, #32
	bl	LogAddr2PhyAddr
	ldr	r3, .L1854+12
	mov	r10, r0
	ldr	r0, [sp, #32]
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, r0
	bhi	.L1806
	mov	r3, #-1
	str	r3, [r4, r6]
.L1807:
	adds	r7, r7, #1
	b	.L1804
.L1806:
	ldr	r3, .L1854+20
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, #0
	ldr	r3, .L1854+24
	it	eq
	moveq	r10, #0
	add	r3, r3, r0, lsl #4
	ldr	r3, [r3, #8]
	cbz	r3, .L1809
	uxtb	r0, r0
	bl	FlashWaitCmdDone
.L1809:
	ldr	r3, [sp, #32]
	movs	r1, #0
	ldr	r2, .L1854+24
	add	r2, r2, r3, lsl #4
	str	r1, [r2, #12]
	ldr	r1, [sp, #28]
	str	fp, [r2, #8]
	str	r1, [r2, #4]
	cmp	r10, #0
	beq	.L1810
	add	r1, r6, #36
	add	r1, r1, r4
	str	r1, [r2, #12]
.L1810:
	ldr	r2, .L1854+28
	ldrb	r5, [r2, r3]	@ zero_extendqisi2
	lsls	r3, r3, #4
	ldr	r2, .L1854+24
	mov	r0, r5
	strb	r5, [r2, r3]
	ldr	r3, .L1854+12
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L1811
	bl	NandcWaitFlashReady
.L1812:
	ldr	r3, [sp, #16]
	subs	r3, r3, #1
	cmp	r3, #7
	bhi	.L1813
	ldr	r3, .L1854+32
	ldrb	r3, [r3, r5]	@ zero_extendqisi2
	cbz	r3, .L1813
	ldr	r1, .L1854+36
	movs	r3, #0
	mov	r0, r5
	adds	r2, r1, #4
	ldrb	r1, [r1, #1]	@ zero_extendqisi2
	bl	HynixSetRRPara
.L1813:
	mov	r0, r5
	bl	NandcFlashCs
	cmp	r8, #1
	mov	r0, r5
	bne	.L1814
	ldr	r3, .L1854+16
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1814
	bl	flash_enter_slc_mode
.L1815:
	ldr	r1, [sp, #28]
	mov	r0, r5
	bl	FlashProgFirstCmd
	ldr	r3, [fp, #12]
	movs	r1, #1
	ldr	r2, [sp, #12]
	mov	r0, r5
	str	r3, [sp]
	ldr	r3, [fp, #8]
	bl	NandcXferData
	cmp	r10, #0
	beq	.L1816
	ldr	r1, [sp, #28]
	mov	r0, r5
	bl	FlashProgDpFirstCmd
	ldr	r3, .L1854+40
	mov	r0, r5
	ldr	r2, [sp, #32]
	adds	r6, r6, #36
	ldr	r1, [sp, #28]
	add	r6, r6, r4
	ldr	r2, [r3, r2, lsl #2]
	adds	r2, r2, #0
	it	ne
	movne	r2, #1
	bl	FlashWaitReadyEN
	ldr	r3, .L1854+44
	mov	r0, r5
	ldr	r1, [sp, #28]
	ldr	r3, [r3]
	add	r1, r1, r3
	bl	FlashProgDpSecondCmd
	ldr	r3, [r6, #12]
	movs	r1, #1
	ldr	r2, [sp, #12]
	mov	r0, r5
	str	r3, [sp]
	ldr	r3, [r6, #8]
	bl	NandcXferData
.L1816:
	ldr	r1, [sp, #28]
	mov	r0, r5
	bl	FlashProgSecondCmd
	mov	r0, r5
	add	r7, r7, r10
	bl	NandcFlashDeCs
	b	.L1807
.L1811:
	bl	NandcFlashCs
	ldr	r2, [sp, #32]
	mov	r0, r5
	ldr	r3, .L1854+40
	ldr	r1, [sp, #28]
	ldr	r2, [r3, r2, lsl #2]
	adds	r2, r2, #0
	it	ne
	movne	r2, #1
	bl	FlashWaitReadyEN
	mov	r0, r5
	bl	NandcFlashDeCs
	b	.L1812
.L1814:
	bl	flash_exit_slc_mode
	b	.L1815
.L1820:
	uxtb	r0, r5
	bl	FlashWaitCmdDone
	cmp	r8, #1
	bne	.L1819
	ldrb	r3, [r7]	@ zero_extendqisi2
	cbz	r3, .L1819
	ldr	r2, .L1854+24
	lsls	r3, r5, #4
	ldrb	r0, [r2, r3]	@ zero_extendqisi2
	bl	flash_exit_slc_mode
.L1819:
	adds	r5, r5, #1
	b	.L1818
.L1821:
	ldr	r10, .L1854+64
	movs	r7, #0
.L1822:
	ldr	r3, [sp, #8]
	cmp	r7, r3
	beq	.L1829
	ldr	r3, [r4]
	adds	r3, r3, #1
	bne	.L1823
	ldr	r1, [r4, #4]
	ldr	r0, .L1854+48
	bl	printf
.L1824:
	adds	r7, r7, #1
	adds	r4, r4, #36
	b	.L1822
.L1823:
	ldr	r3, [sp, #8]
	add	r2, sp, #28
	ldr	fp, .L1854+68
	mov	r1, r8
	mov	r0, r4
	mov	r6, r4
	subs	r3, r3, r7
	add	r5, sp, #36
	uxtb	r3, r3
	str	r3, [sp]
	add	r3, sp, #32
	bl	LogAddr2PhyAddr
	ldr	lr, [r10]
	movs	r3, #0
	ldr	ip, [fp]
	str	r3, [lr]
	str	r3, [ip]
	ldmia	r6!, {r0, r1, r2, r3}
	stmia	r5!, {r0, r1, r2, r3}
	str	lr, [sp, #44]
	ldmia	r6!, {r0, r1, r2, r3}
	str	ip, [sp, #48]
	stmia	r5!, {r0, r1, r2, r3}
	mov	r2, r8
	ldr	r3, [r6]
	movs	r1, #1
	add	r0, sp, #36
	str	r3, [r5]
	bl	FlashReadPages
	ldr	r5, [sp, #36]
	adds	r3, r5, #1
	bne	.L1825
	ldr	r1, [r4, #4]
	ldr	r0, .L1854+52
	bl	printf
	str	r5, [r4]
.L1825:
	ldr	r3, [r4, #12]
	cbz	r3, .L1826
	ldr	r2, [r3]
	ldr	r3, [fp]
	ldr	r3, [r3]
	cmp	r2, r3
	beq	.L1826
	ldr	r1, [r4, #4]
	ldr	r0, .L1854+56
	bl	printf
	mov	r3, #-1
	str	r3, [r4]
.L1826:
	ldr	r3, [r4, #8]
	cmp	r3, #0
	beq	.L1824
	ldr	r2, [r3]
	ldr	r3, [r10]
	ldr	r3, [r3]
	cmp	r2, r3
	beq	.L1824
	ldr	r1, [r4, #4]
	ldr	r0, .L1854+60
	bl	printf
	mov	r3, #-1
	str	r3, [r4]
	b	.L1824
.L1855:
	.align	2
.L1854:
	.word	.LANCHOR7
	.word	.LANCHOR2
	.word	.LANCHOR31
	.word	.LANCHOR26
	.word	.LANCHOR16
	.word	.LANCHOR28
	.word	.LANCHOR23
	.word	.LANCHOR27
	.word	.LANCHOR21
	.word	.LANCHOR20
	.word	.LANCHOR18
	.word	.LANCHOR4
	.word	.LC30
	.word	.LC31
	.word	.LC33
	.word	.LC34
	.word	.LANCHOR206
	.word	.LANCHOR207
	.size	FlashProgPages, .-FlashProgPages
	.section	.text.FlashTestBlk,"ax",%progbits
	.align	1
	.global	FlashTestBlk
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	FlashTestBlk, %function
FlashTestBlk:
	@ args = 0, pretend = 0, frame = 104
	@ frame_needed = 0, uses_anonymous_args = 0
	ldr	r3, .L1859
	push	{r4, r5, lr}
	mov	r4, r0
	sub	sp, sp, #108
	ldr	r3, [r3]
	cmp	r0, r3
	bcc	.L1858
	ldr	r5, .L1859+4
	add	r0, sp, #40
	movs	r2, #32
	movs	r1, #165
	str	r0, [sp, #16]
	lsls	r4, r4, #10
	ldr	r3, [r5]
	str	r3, [sp, #12]
	bl	ftl_memset
	movs	r2, #8
	movs	r1, #90
	ldr	r0, [r5]
	bl	ftl_memset
	movs	r2, #1
	add	r0, sp, #4
	mov	r1, r2
	str	r4, [sp, #8]
	bl	FlashEraseBlocks
	movs	r3, #1
	add	r0, sp, #4
	mov	r2, r3
	mov	r1, r3
	bl	FlashProgPages
	ldr	r4, [sp, #4]
	movs	r2, #1
	movs	r1, #0
	add	r0, sp, #4
	adds	r4, r4, #0
	it	ne
	movne	r4, #1
	negs	r4, r4
	bl	FlashEraseBlocks
.L1856:
	mov	r0, r4
	add	sp, sp, #108
	@ sp needed
	pop	{r4, r5, pc}
.L1858:
	movs	r4, #0
	b	.L1856
.L1860:
	.align	2
.L1859:
	.word	.LANCHOR156
	.word	.LANCHOR149
	.size	FlashTestBlk, .-FlashTestBlk
	.section	.text.FtlLowFormatEraseBlock,"ax",%progbits
	.align	1
	.global	FtlLowFormatEraseBlock
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	FtlLowFormatEraseBlock, %function
FtlLowFormatEraseBlock:
	@ args = 0, pretend = 0, frame = 40
	@ frame_needed = 0, uses_anonymous_args = 0
	ldr	r3, .L1906
	push	{r4, r5, r6, r7, r8, r10, fp, lr}
	sub	sp, sp, #40
	str	r0, [sp, #8]
	ldr	r3, [r3]
	str	r1, [sp, #4]
	cmp	r3, #0
	bne	.L1888
	ldr	r2, .L1906+4
	mov	r10, r3
	mov	r5, r3
	mov	r4, r3
	mov	r8, #36
	ldrb	r2, [r2]	@ zero_extendqisi2
	str	r2, [sp, #20]
	ldr	r2, .L1906+8
	ldrb	r2, [r2]	@ zero_extendqisi2
	str	r2, [sp, #12]
	ldr	r2, .L1906+12
	str	r0, [r2]
	ldr	r2, .L1906+16
	ldrh	fp, [r2]
	ldr	r2, .L1906+20
	ldr	r7, [r2]
	ldr	r2, .L1906+24
	ldr	r2, [r2]
	str	r2, [sp, #16]
	ldr	r2, .L1906+28
	ldrh	r2, [r2]
	str	r2, [sp, #24]
.L1863:
	uxth	r2, r10
	cmp	fp, r2
	bhi	.L1867
	cmp	r5, #0
	beq	.L1861
	ldr	r3, [sp, #12]
	mov	r0, r7
	ldr	r10, .L1906+4
	mov	r8, #0
	mov	r2, r5
	ldr	r7, .L1906+20
	adds	r6, r3, #0
	it	ne
	movne	r6, #1
	strb	r8, [r10]
	mov	r1, r6
	bl	FlashEraseBlocks
	ldrb	r3, [sp, #20]	@ zero_extendqisi2
	strb	r3, [r10]
	mov	r10, #36
.L1869:
	uxth	r3, r8
	cmp	r5, r3
	bhi	.L1871
	ldr	r3, [sp, #4]
	cmp	r3, #0
	bne	.L1872
	uxth	r6, r6
	movs	r3, #6
	str	r3, [sp, #16]
	movs	r3, #1
	str	r3, [sp, #12]
.L1873:
	mov	r8, #0
.L1882:
	ldr	r3, .L1906+16
	mov	fp, #0
	mov	r5, fp
	ldrh	r3, [r3]
	str	r3, [sp, #24]
	ldr	r3, .L1906+20
	ldr	r10, [r3]
	ldr	r3, .L1906+32
	ldr	r3, [r3]
	str	r3, [sp, #28]
	ldr	r3, .L1906+36
	ldr	r3, [r3]
	str	r3, [sp, #32]
	ldr	r3, .L1906+28
	ldrh	r3, [r3]
	str	r3, [sp, #36]
.L1874:
	ldr	r3, [sp, #24]
	uxth	r2, fp
	cmp	r3, r2
	bhi	.L1877
	cbz	r5, .L1861
	ldr	fp, .L1906+4
	movs	r3, #1
	mov	r0, r10
	movs	r7, #0
	mov	r2, r6
	mov	r1, r5
	strb	r7, [fp]
	bl	FlashProgPages
	ldrb	r3, [sp, #20]	@ zero_extendqisi2
	ldr	r10, .L1906+20
	strb	r3, [fp]
	mov	fp, #36
.L1879:
	uxth	r3, r7
	cmp	r5, r3
	bhi	.L1881
	ldr	r3, [sp, #16]
	add	r8, r8, r3
	ldr	r3, [sp, #12]
	uxth	r8, r8
	cmp	r3, r8
	bhi	.L1882
	ldr	r8, .L1906+20
	movs	r7, #0
	mov	r10, #36
.L1883:
	uxth	r3, r7
	cmp	r5, r3
	bhi	.L1885
	ldr	r3, [sp, #8]
	cmp	r3, #63
	bls	.L1886
	ldr	r3, [sp, #4]
	cbz	r3, .L1861
.L1886:
	ldr	r3, .L1906+20
	mov	r2, r5
	mov	r1, r6
	ldr	r0, [r3]
	bl	FlashEraseBlocks
.L1861:
	mov	r0, r4
	add	sp, sp, #40
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r10, fp, pc}
.L1867:
	mul	r2, r8, r10
	movs	r3, #0
	ldr	r1, [sp, #8]
	str	r3, [r7, r2]
	ldr	r3, .L1906+40
	ldrb	r0, [r3, r10]	@ zero_extendqisi2
	bl	V2P_block
	ldr	r3, [sp, #4]
	mov	r6, r0
	cbz	r3, .L1864
	bl	IsBlkInVendorPart
	cbnz	r0, .L1865
.L1864:
	mov	r0, r6
	bl	FtlBbmIsBadBlock
	cbnz	r0, .L1866
	ldr	r3, [sp, #24]
	mla	r1, r8, r5, r7
	lsls	r6, r6, #10
	mul	r2, r3, r5
	ldr	r3, [sp, #16]
	adds	r5, r5, #1
	str	r6, [r1, #4]
	uxth	r5, r5
	str	r0, [r1, #8]
	bic	r2, r2, #3
	add	r2, r2, r3
	str	r2, [r1, #12]
.L1865:
	add	r10, r10, #1
	b	.L1863
.L1866:
	adds	r4, r4, #1
	uxth	r4, r4
	b	.L1865
.L1871:
	mul	r3, r10, r8
	ldr	r2, [r7]
	adds	r1, r2, r3
	ldr	r3, [r2, r3]
	adds	r3, r3, #1
	bne	.L1870
	ldr	r0, [r1, #4]
	adds	r4, r4, #1
	uxth	r4, r4
	ubfx	r0, r0, #10, #16
	bl	FtlBbmMapBadBlock
.L1870:
	add	r8, r8, #1
	b	.L1869
.L1872:
	ldr	r3, .L1906+44
	ldrh	r3, [r3]
	str	r3, [sp, #12]
	ldr	r3, .L1906+8
	ldrb	r3, [r3]	@ zero_extendqisi2
	cbnz	r3, .L1889
	ldr	r3, [sp, #12]
	movs	r6, #1
	lsrs	r3, r3, #2
	str	r3, [sp, #16]
	b	.L1873
.L1889:
	movs	r6, #1
	str	r6, [sp, #16]
	b	.L1873
.L1877:
	movs	r3, #36
	ldr	r1, [sp, #8]
	mul	r2, r3, fp
	movs	r3, #0
	str	r3, [r10, r2]
	ldr	r3, .L1906+40
	ldrb	r0, [r3, fp]	@ zero_extendqisi2
	bl	V2P_block
	ldr	r3, [sp, #4]
	mov	r7, r0
	cbz	r3, .L1875
	bl	IsBlkInVendorPart
	cbnz	r0, .L1876
.L1875:
	mov	r0, r7
	bl	FtlBbmIsBadBlock
	cbnz	r0, .L1876
	movs	r3, #36
	add	r7, r8, r7, lsl #10
	mla	r1, r3, r5, r10
	ldr	r3, [sp, #28]
	str	r3, [r1, #8]
	ldr	r3, [sp, #36]
	str	r7, [r1, #4]
	mul	r2, r3, r5
	ldr	r3, [sp, #32]
	adds	r5, r5, #1
	uxth	r5, r5
	bic	r2, r2, #3
	add	r2, r2, r3
	str	r2, [r1, #12]
.L1876:
	add	fp, fp, #1
	b	.L1874
.L1881:
	mul	r3, fp, r7
	ldr	r2, [r10]
	adds	r1, r2, r3
	ldr	r3, [r2, r3]
	cbz	r3, .L1880
	ldr	r0, [r1, #4]
	adds	r4, r4, #1
	uxth	r4, r4
	ubfx	r0, r0, #10, #16
	bl	FtlBbmMapBadBlock
.L1880:
	adds	r7, r7, #1
	b	.L1879
.L1885:
	ldr	r3, [sp, #4]
	cbz	r3, .L1884
	mul	r3, r10, r7
	ldr	r2, [r8]
	adds	r1, r2, r3
	ldr	r3, [r2, r3]
	cbnz	r3, .L1884
	ldr	r0, [r1, #4]
	movs	r1, #1
	ubfx	r0, r0, #10, #16
	bl	FtlFreeSysBlkQueueIn
.L1884:
	adds	r7, r7, #1
	b	.L1883
.L1888:
	movs	r4, #0
	b	.L1861
.L1907:
	.align	2
.L1906:
	.word	.LANCHOR78
	.word	.LANCHOR28
	.word	.LANCHOR16
	.word	.LANCHOR75
	.word	.LANCHOR38
	.word	.LANCHOR79
	.word	.LANCHOR196
	.word	.LANCHOR58
	.word	.LANCHOR193
	.word	.LANCHOR194
	.word	.LANCHOR47
	.word	.LANCHOR53
	.size	FtlLowFormatEraseBlock, .-FtlLowFormatEraseBlock
	.section	.text.FtlBbmTblFlush,"ax",%progbits
	.align	1
	.global	FtlBbmTblFlush
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	FtlBbmTblFlush, %function
FtlBbmTblFlush:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r0, r1, r2, r3, r4, r5, r6, r7, r8, r10, fp, lr}
	ldr	r3, .L1924
	ldr	r4, [r3]
	str	r3, [sp, #12]
	cmp	r4, #0
	bne	.L1910
	ldr	r3, .L1924+4
	mov	r1, r4
	ldr	r7, .L1924+8
	ldr	r5, .L1924+12
	ldr	r3, [r3]
	ldr	r0, [r7]
	mov	fp, r7
	ldr	r6, .L1924+16
	str	r3, [r5, #12]
	ldr	r7, .L1924+20
	ldr	r3, .L1924+24
	ldr	r8, .L1924+56
	str	r0, [r5, #8]
	ldrh	r2, [r3]
	bl	ftl_memset
.L1911:
	ldrh	r3, [r7]
	cmp	r4, r3
	blt	.L1912
	ldr	r6, [r5, #12]
	movs	r2, #16
	ldr	r4, .L1924+28
	movs	r1, #255
	movs	r7, #0
	mov	r0, r6
	mov	r8, r7
	bl	ftl_memset
	movw	r3, #61649
	mov	r10, r4
	strh	r3, [r6]	@ movhi
	ldr	r3, [r4, #8]
	str	r3, [r6, #4]
	ldrh	r3, [r4]
	strh	r3, [r6, #2]	@ movhi
	ldrh	r3, [r4, #4]
	strh	r3, [r6, #8]	@ movhi
	ldrh	r3, [r4, #6]
	strh	r3, [r6, #10]	@ movhi
	ldr	r3, .L1924+32
	ldr	r3, [r3]
	strh	r3, [r6, #12]	@ movhi
.L1913:
	ldr	r3, [fp]
	ldrh	r2, [r4, #2]
	ldrh	r1, [r4]
	str	r3, [r5, #8]
	ldr	r3, .L1924+4
	ldrh	r0, [r6, #10]
	ldr	r3, [r3]
	str	r3, [r5, #12]
	movs	r3, #0
	str	r3, [r5]
	orr	r3, r2, r1, lsl #10
	str	r3, [r5, #4]
	ldrh	r3, [r4, #4]
	str	r0, [sp]
	ldr	r0, .L1924+36
	bl	printf
	ldr	r3, .L1924+40
	ldrh	r2, [r4, #2]
	ldrh	r3, [r3]
	subs	r3, r3, #1
	cmp	r2, r3
	blt	.L1914
	ldr	r3, [r4, #8]
	mov	r1, #0	@ movhi
	ldrh	r2, [r4]
	strh	r1, [r4, #2]	@ movhi
	adds	r3, r3, #1
	str	r3, [r4, #8]
	str	r3, [r6, #4]
	strh	r2, [r6, #8]	@ movhi
	ldrh	r3, [r4, #4]
	strh	r2, [r4, #4]	@ movhi
	ldr	r2, .L1924+44
	strh	r3, [r4]	@ movhi
	lsls	r3, r3, #10
	ldr	r0, [r2]
	movs	r2, #1
	str	r3, [r5, #4]
	mov	r1, r2
	str	r3, [r0, #4]
	bl	FlashEraseBlocks
.L1914:
	movs	r3, #1
	ldr	r0, .L1924+12
	mov	r2, r3
	mov	r1, r3
	bl	FlashProgPages
	ldrh	r3, [r10, #2]
	adds	r3, r3, #1
	strh	r3, [r10, #2]	@ movhi
	ldr	r3, [r5]
	adds	r2, r3, #1
	bne	.L1915
	adds	r7, r7, #1
	ldr	r1, [r5, #4]
	uxth	r7, r7
	ldr	r0, .L1924+48
	bl	printf
	cmp	r7, #3
	bls	.L1913
	mov	r2, r7
	ldr	r1, [r5, #4]
	ldr	r0, .L1924+52
	bl	printf
	ldr	r2, [sp, #12]
	movs	r3, #1
	str	r3, [r2]
.L1910:
	movs	r0, #0
	add	sp, sp, #16
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r10, fp, pc}
.L1912:
	ldrh	r2, [r8]
	ldr	r3, [r5, #8]
	ldr	r1, [r6, #4]!
	mul	r0, r4, r2
	lsls	r2, r2, #2
	adds	r4, r4, #1
	add	r0, r3, r0, lsl #2
	bl	ftl_memcpy
	b	.L1911
.L1915:
	add	r8, r8, #1
	cmp	r8, #1
	beq	.L1913
	cmp	r3, #256
	beq	.L1913
	b	.L1910
.L1925:
	.align	2
.L1924:
	.word	.LANCHOR78
	.word	.LANCHOR195
	.word	.LANCHOR189
	.word	.LANCHOR211
	.word	.LANCHOR76+24
	.word	.LANCHOR45
	.word	.LANCHOR57
	.word	.LANCHOR76
	.word	.LANCHOR37
	.word	.LC35
	.word	.LANCHOR53
	.word	.LANCHOR79
	.word	.LC36
	.word	.LC37
	.word	.LANCHOR126
	.size	FtlBbmTblFlush, .-FtlBbmTblFlush
	.section	.text.allocate_data_superblock,"ax",%progbits
	.align	1
	.global	allocate_data_superblock
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	allocate_data_superblock, %function
allocate_data_superblock:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 0, uses_anonymous_args = 0
	ldr	r3, .L1991
	push	{r0, r1, r4, r5, r6, r7, r8, r10, fp, lr}
	mov	r4, r0
	ldr	r3, [r3]
	cmp	r3, #0
	bne	.L1928
.L1927:
	ldr	r3, .L1991+4
	ldr	r8, .L1991+60
	ldr	r7, .L1991+8
	ldrh	r3, [r3]
	ldrh	r2, [r8]
	add	r3, r3, r2
	ldrh	r2, [r7]
	cmp	r3, r2
	ble	.L1929
	ldr	r1, .L1991+12
	movw	r2, #3507
	ldr	r0, .L1991+16
	bl	printf
	ldr	r1, .L1991+20
	ldr	r0, .L1991+24
	bl	printf
.L1929:
	ldr	r3, .L1991+28
	ldrb	r2, [r4, #8]	@ zero_extendqisi2
	cmp	r4, r3
	bne	.L1930
	ldr	r3, .L1991+4
	ldrh	r5, [r3]
	ldr	r3, .L1991+32
	ldr	r3, [r3]
	lsrs	r0, r5, #1
	adds	r1, r0, #1
	mul	r6, r3, r5
	add	r1, r1, r6, lsr #2
	ldr	r6, .L1991+36
	uxth	r1, r1
	ldr	r6, [r6]
	cbz	r6, .L1931
	ldr	r6, .L1991+40
	ldr	r6, [r6]
	cmp	r6, #39
	bhi	.L1931
	cmp	r6, #2
	bls	.L1965
	lsls	r1, r5, #31
	bpl	.L1961
	cmp	r3, #0
	beq	.L1965
.L1961:
	mov	r1, r0
	b	.L1931
.L1930:
	cmp	r2, #1
	bne	.L1965
	ldr	r3, .L1991+44
	ldrh	r3, [r3]
	cmp	r3, #1
	beq	.L1965
	ldr	r3, .L1991+48
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1965
	ldr	r3, .L1991+4
	ldr	r0, .L1991+36
	ldrh	r3, [r3]
	ldr	r0, [r0]
	lsrs	r1, r3, #3
	cbz	r0, .L1931
	ldr	r0, .L1991+40
	ldr	r0, [r0]
	cmp	r0, #1
	bhi	.L1931
	rsb	r3, r3, r3, lsl #3
	ubfx	r1, r3, #3, #16
.L1931:
	cbz	r1, .L1932
	subs	r1, r1, #1
	uxth	r1, r1
.L1932:
	ldr	r0, .L1991+52
	bl	List_pop_index_node
	ldr	r3, .L1991+4
	mov	r5, r0
	uxth	r10, r0
	ldrh	r3, [r3]
	cbnz	r3, .L1933
	ldr	r1, .L1991+12
	movw	r2, #3532
	ldr	r0, .L1991+16
	bl	printf
	ldr	r1, .L1991+20
	ldr	r0, .L1991+24
	bl	printf
.L1933:
	ldr	r3, .L1991+4
	ldr	r2, .L1991+4
	ldrh	r3, [r3]
	subs	r3, r3, #1
	strh	r3, [r2]	@ movhi
	ldrh	r3, [r7]
	cmp	r3, r10
	bls	.L1927
	uxth	r5, r5
	lsls	r3, r5, #1
	str	r3, [sp]
	ldr	r3, .L1991+56
	ldr	r3, [r3]
	ldrh	r6, [r3, r5, lsl #1]
	cmp	r6, #0
	bne	.L1927
	strh	r10, [r4]	@ movhi
	mov	r0, r4
	bl	make_superblock
	ldrb	r3, [r4, #7]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1935
	ldr	r3, .L1991+56
	movw	r2, #65535
	ldr	r3, [r3]
	strh	r2, [r3, r5, lsl #1]	@ movhi
	ldr	r3, .L1991+4
	ldrh	r2, [r8]
	ldrh	r3, [r3]
	add	r3, r3, r2
	ldrh	r2, [r7]
	cmp	r3, r2
	ble	.L1927
	mov	r2, #3552
	ldr	r1, .L1991+12
	ldr	r0, .L1991+16
	bl	printf
	ldr	r1, .L1991+20
	ldr	r0, .L1991+24
	bl	printf
	b	.L1927
.L1965:
	movs	r1, #0
	b	.L1932
.L1992:
	.align	2
.L1991:
	.word	.LANCHOR78
	.word	.LANCHOR90
	.word	.LANCHOR40
	.word	.LANCHOR212
	.word	.LC5
	.word	.LC6
	.word	.LC7
	.word	.LANCHOR95
	.word	.LANCHOR177
	.word	.LANCHOR104
	.word	.LANCHOR175
	.word	.LANCHOR44
	.word	.LANCHOR16
	.word	.LANCHOR89
	.word	.LANCHOR85
	.word	.LANCHOR87
.L1935:
	ldr	r3, .L1993
	ldrh	r2, [r8]
	ldrh	r3, [r3]
	add	r3, r3, r2
	ldrh	r2, [r7]
	cmp	r3, r2
	ble	.L1937
	ldr	r1, .L1993+4
	movw	r2, #3556
	ldr	r0, .L1993+8
	bl	printf
	ldr	r1, .L1993+12
	ldr	r0, .L1993+16
	bl	printf
.L1937:
	ldr	r3, .L1993+20
	add	lr, r4, #16
	ldr	r2, .L1993+24
	mov	r8, #0
	ldr	ip, [r3]
	ldrh	r0, [r2]
	movs	r2, #36
	mov	r3, ip
	mla	r0, r2, r0, ip
.L1938:
	cmp	r0, r3
	bne	.L1940
	cbnz	r6, .L1941
	ldr	r1, .L1993+4
	movw	r2, #3571
	ldr	r0, .L1993+8
	bl	printf
	ldr	r1, .L1993+12
	ldr	r0, .L1993+16
	bl	printf
.L1941:
	ldr	r3, .L1993+28
	ldr	r8, .L1993+80
	ldr	r3, [r3]
	cbz	r3, .L1942
	ldr	r3, .L1993+32
	cmp	r4, r3
	bne	.L1942
	ldr	r3, [r8]
	ldrh	r3, [r3, r5, lsl #1]
	cmp	r3, #40
	itt	hi
	movhi	r3, #0
	strbhi	r3, [r4, #8]
.L1942:
	ldr	r3, .L1993+36
	ldrh	r3, [r3]
	cmp	r3, r10
	bne	.L1943
	ldr	r1, .L1993+4
	movw	r2, #3578
	ldr	r0, .L1993+8
	bl	printf
	ldr	r1, .L1993+12
	ldr	r0, .L1993+16
	bl	printf
.L1943:
	ldrb	r2, [r4, #8]	@ zero_extendqisi2
	ldr	r3, .L1993+40
	ldr	fp, .L1993+84
	cmp	r2, #0
	bne	.L1944
	ldr	r1, [r8]
	ldrh	r2, [r1, r5, lsl #1]
	cmp	r2, #0
	beq	.L1945
	ldr	r0, .L1993+44
	ldrh	r0, [r0]
	add	r2, r2, r0
.L1988:
	strh	r2, [r1, r5, lsl #1]	@ movhi
	mov	r0, r10
	ldr	r2, [r3]
	movs	r1, #0
	str	r3, [sp, #4]
	adds	r2, r2, #1
	str	r2, [r3]
	bl	ftl_set_blk_mode
.L1989:
	ldr	r2, [r8]
	ldr	r3, [sp, #4]
	ldrh	r0, [r2, r5, lsl #1]
	ldr	r2, .L1993+48
	ldr	r1, [r2]
	cmp	r0, r1
	ldrh	r1, [r7]
	it	hi
	strhi	r0, [r2]
	ldr	r2, .L1993+44
	ldr	r0, [r3]
	ldr	r3, [fp]
	ldrh	r2, [r2]
	ldr	r7, .L1993+52
	mla	r0, r0, r2, r3
	bl	__aeabi_uidiv
	ldr	r3, .L1993+56
	str	r0, [r3]
	ldr	r3, .L1993+60
	ldr	r2, [r3]
	ldr	r3, [r2, #16]
	adds	r3, r3, #1
	str	r3, [r2, #16]
	ldr	r3, .L1993+20
	ldr	r0, [r3]
	movs	r3, #36
	adds	r1, r0, #4
	mla	r3, r3, r6, r0
	adds	r3, r3, #40
.L1949:
	adds	r1, r1, #36
	cmp	r3, r1
	bne	.L1950
	ldr	r3, .L1993+64
	ldrb	r3, [r3]	@ zero_extendqisi2
	cbz	r3, .L1951
	ldrb	r3, [r4, #8]	@ zero_extendqisi2
	mov	r2, r6
	cmp	r3, #1
	ite	eq
	moveq	r1, #0
	movne	r1, #1
	bl	FlashEraseBlocks
.L1951:
	ldr	r3, .L1993+20
	movs	r7, #0
	mov	r8, r7
	mov	fp, #36
	mov	r2, r6
	ldrb	r1, [r4, #8]	@ zero_extendqisi2
	ldr	r0, [r3]
	bl	FlashEraseBlocks
.L1953:
	uxth	r3, r7
	cmp	r6, r3
	bhi	.L1955
	cmp	r8, #0
	beq	.L1956
	mov	r0, r10
	bl	update_multiplier_value
	bl	FtlBbmTblFlush
.L1956:
	ldrb	r2, [r4, #7]	@ zero_extendqisi2
	cmp	r2, #0
	bne	.L1957
	ldr	r3, .L1993+68
	movw	r2, #65535
	ldr	r3, [r3]
	strh	r2, [r3, r5, lsl #1]	@ movhi
	b	.L1927
.L1940:
	ldrh	r1, [lr], #2
	movw	fp, #65535
	str	r8, [r3, #8]
	str	r8, [r3, #12]
	cmp	r1, fp
	beq	.L1939
	mla	fp, r2, r6, ip
	adds	r6, r6, #1
	lsls	r1, r1, #10
	uxth	r6, r6
	str	r1, [fp, #4]
.L1939:
	adds	r3, r3, #36
	b	.L1938
.L1945:
	movs	r2, #2
	b	.L1988
.L1944:
	ldr	r1, [r8]
	mov	r0, r10
	str	r3, [sp, #4]
	ldrh	r2, [r1, r5, lsl #1]
	adds	r2, r2, #1
	strh	r2, [r1, r5, lsl #1]	@ movhi
	ldr	r2, [fp]
	adds	r2, r2, #1
	str	r2, [fp]
	bl	ftl_set_blk_mode.part.11
	b	.L1989
.L1950:
	ldr	r2, [r1, #-36]
	ands	r2, r2, r7
	str	r2, [r1, #-36]
	b	.L1949
.L1955:
	ldr	r2, .L1993+20
	mul	r3, fp, r7
	ldr	r2, [r2]
	adds	r1, r2, r3
	ldr	r2, [r2, r3]
	adds	r3, r2, #1
	bne	.L1954
	ldr	r0, [r1, #4]
	add	r8, r8, #1
	str	r2, [sp, #4]
	ubfx	r0, r0, #10, #16
	bl	FtlBbmMapBadBlock
	ldr	r2, [sp, #4]
	add	r3, r4, r7, lsl #1
	strh	r2, [r3, #16]	@ movhi
	ldrb	r3, [r4, #7]	@ zero_extendqisi2
	subs	r3, r3, #1
	strb	r3, [r4, #7]
.L1954:
	adds	r7, r7, #1
	b	.L1953
.L1957:
	ldr	r3, .L1993+72
	ldr	r1, .L1993+76
	ldrh	r3, [r3]
	strh	r10, [r4]	@ movhi
	smulbb	r3, r3, r2
	movs	r2, #0
	strh	r2, [r4, #2]	@ movhi
	strb	r2, [r4, #6]
	ldr	r2, [r1]
	uxth	r3, r3
	strh	r3, [r4, #4]	@ movhi
	str	r2, [r4, #12]
	adds	r2, r2, #1
	str	r2, [r1]
	ldr	r2, .L1993+68
	ldr	r1, [sp]
	ldr	r2, [r2]
	strh	r3, [r2, r1]	@ movhi
	ldrh	r3, [r4, #4]
	cbz	r3, .L1958
	ldrb	r3, [r4, #7]	@ zero_extendqisi2
	cbnz	r3, .L1928
.L1958:
	ldr	r1, .L1993+4
	movw	r2, #3642
	ldr	r0, .L1993+8
	bl	printf
	ldr	r1, .L1993+12
	ldr	r0, .L1993+16
	bl	printf
.L1928:
	movs	r0, #0
	add	sp, sp, #8
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r10, fp, pc}
.L1994:
	.align	2
.L1993:
	.word	.LANCHOR90
	.word	.LANCHOR212
	.word	.LC5
	.word	.LC6
	.word	.LC7
	.word	.LANCHOR79
	.word	.LANCHOR38
	.word	.LANCHOR104
	.word	.LANCHOR93
	.word	.LANCHOR213
	.word	.LANCHOR172
	.word	.LANCHOR48
	.word	.LANCHOR174
	.word	-1024
	.word	.LANCHOR214
	.word	.LANCHOR199
	.word	.LANCHOR16
	.word	.LANCHOR85
	.word	.LANCHOR52
	.word	.LANCHOR164
	.word	.LANCHOR80
	.word	.LANCHOR173
	.size	allocate_data_superblock, .-allocate_data_superblock
	.section	.text.FtlGcFreeBadSuperBlk,"ax",%progbits
	.align	1
	.global	FtlGcFreeBadSuperBlk
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	FtlGcFreeBadSuperBlk, %function
FtlGcFreeBadSuperBlk:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r0, r1, r4, r5, r6, r7, r8, r10, fp, lr}
	mov	r10, r0
	ldr	r4, .L2007
	ldrh	r3, [r4]
	cbz	r3, .L1996
	ldr	r8, .L2007+12
	movs	r7, #0
.L1997:
	ldr	r3, .L2007+4
	ldrh	r2, [r3]
	uxth	r3, r7
	cmp	r2, r3
	bhi	.L2003
	bl	FtlGcReFreshBadBlk
.L1996:
	movs	r0, #0
	add	sp, sp, #8
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r10, fp, pc}
.L2003:
	ldr	r2, .L2007+8
	uxth	r3, r7
	mov	r1, r10
	mov	fp, #0
	ldrb	r0, [r2, r3]	@ zero_extendqisi2
	bl	V2P_block
	mov	r1, r0
.L1998:
	ldrh	r3, [r4]
	uxth	r5, fp
	cmp	r3, r5
	bhi	.L2002
	adds	r7, r7, #1
	b	.L1997
.L2002:
	uxth	r6, fp
	ldrh	r3, [r8, r6, lsl #1]
	cmp	r3, r1
	bne	.L1999
	mov	r0, r1
	str	r1, [sp, #4]
	bl	FtlBbmMapBadBlock
	bl	FtlBbmTblFlush
	ldrh	r2, [r4]
	add	r3, r8, r6, lsl #1
	ldr	r1, [sp, #4]
.L2000:
	cmp	r5, r2
	bcc	.L2001
	subs	r2, r2, #1
	strh	r2, [r4]	@ movhi
.L1999:
	add	fp, fp, #1
	b	.L1998
.L2001:
	ldrh	r0, [r3, #2]!
	adds	r5, r5, #1
	uxth	r5, r5
	strh	r0, [r3, #-2]	@ movhi
	b	.L2000
.L2008:
	.align	2
.L2007:
	.word	.LANCHOR119
	.word	.LANCHOR38
	.word	.LANCHOR47
	.word	.LANCHOR120
	.size	FtlGcFreeBadSuperBlk, .-FtlGcFreeBadSuperBlk
	.section	.text.update_vpc_list,"ax",%progbits
	.align	1
	.global	update_vpc_list
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	update_vpc_list, %function
update_vpc_list:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r3, r4, r5, lr}
	mov	r4, r0
	ldr	r3, .L2019
	ldr	r3, [r3]
	ldrh	r3, [r3, r0, lsl #1]
	cmp	r3, #0
	bne	.L2010
	ldr	r2, .L2019+4
	ldrh	r1, [r2]
	cmp	r1, r0
	bne	.L2011
	movw	r3, #65535
	strh	r3, [r2]	@ movhi
.L2012:
	ldr	r5, .L2019+8
	mov	r1, r4
	ldr	r0, .L2019+12
	bl	List_remove_node
	ldrh	r3, [r5]
	cbnz	r3, .L2014
	ldr	r1, .L2019+16
	movw	r2, #3767
	ldr	r0, .L2019+20
	bl	printf
	ldr	r1, .L2019+24
	ldr	r0, .L2019+28
	bl	printf
.L2014:
	ldrh	r3, [r5]
	mov	r0, r4
	subs	r3, r3, #1
	strh	r3, [r5]	@ movhi
	bl	free_data_superblock
	mov	r0, r4
	bl	FtlGcFreeBadSuperBlk
	ldr	r3, .L2019+32
	ldrh	r2, [r5]
	ldrh	r3, [r3]
	add	r3, r3, r2
	ldr	r2, .L2019+36
	ldrh	r2, [r2]
	cmp	r3, r2
	ble	.L2018
	ldr	r1, .L2019+16
	movw	r2, #3770
	ldr	r0, .L2019+20
	bl	printf
	ldr	r1, .L2019+24
	ldr	r0, .L2019+28
	bl	printf
.L2018:
	movs	r3, #1
	b	.L2009
.L2011:
	ldr	r2, .L2019+40
	ldrh	r2, [r2]
	cmp	r2, r0
	beq	.L2009
	ldr	r2, .L2019+44
	ldrh	r2, [r2]
	cmp	r2, r0
	beq	.L2009
	ldr	r2, .L2019+48
	ldrh	r2, [r2]
	cmp	r2, r0
	bne	.L2012
.L2009:
	mov	r0, r3
	pop	{r3, r4, r5, pc}
.L2010:
	bl	List_update_data_list
	movs	r3, #0
	b	.L2009
.L2020:
	.align	2
.L2019:
	.word	.LANCHOR85
	.word	.LANCHOR213
	.word	.LANCHOR87
	.word	.LANCHOR84
	.word	.LANCHOR215
	.word	.LC5
	.word	.LC6
	.word	.LC7
	.word	.LANCHOR90
	.word	.LANCHOR40
	.word	.LANCHOR93
	.word	.LANCHOR94
	.word	.LANCHOR95
	.size	update_vpc_list, .-update_vpc_list
	.section	.text.decrement_vpc_count,"ax",%progbits
	.align	1
	.global	decrement_vpc_count
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	decrement_vpc_count, %function
decrement_vpc_count:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	movw	r3, #65535
	push	{r4, r5, r6, lr}
	cmp	r0, r3
	mov	r4, r0
	beq	.L2022
	ldr	r5, .L2033
	ldr	r3, [r5]
	ldrh	r2, [r3, r0, lsl #1]
	cmp	r2, #0
	bne	.L2023
	mov	r1, r0
	ldr	r0, .L2033+4
	bl	printf
	ldr	r3, [r5]
	ldrh	r3, [r3, r4, lsl #1]
	cbnz	r3, .L2024
	ldr	r1, .L2033+8
	movw	r2, #3786
	ldr	r0, .L2033+12
	bl	printf
	ldr	r1, .L2033+16
	ldr	r0, .L2033+20
	bl	printf
.L2024:
	ldr	r3, [r5]
	movs	r2, #32
	mov	r1, r4
	ldr	r0, .L2033+24
	strh	r2, [r3, r4, lsl #1]	@ movhi
	bl	test_node_in_list
	cbz	r0, .L2025
	ldr	r6, .L2033+28
	mov	r1, r4
	ldr	r0, .L2033+24
	bl	List_remove_node
	ldrh	r3, [r6]
	cbnz	r3, .L2026
	ldr	r1, .L2033+8
	mov	r2, #3792
	ldr	r0, .L2033+12
	bl	printf
	ldr	r1, .L2033+16
	ldr	r0, .L2033+20
	bl	printf
.L2026:
	ldrh	r3, [r6]
	mov	r0, r4
	subs	r3, r3, #1
	strh	r3, [r6]	@ movhi
	bl	INSERT_DATA_LIST
	ldr	r3, [r5]
	mov	r1, r4
	ldr	r0, .L2033+32
	ldrh	r2, [r3, r4, lsl #1]
	bl	printf
.L2025:
	mov	r0, r4
	bl	FtlGcRefreshBlock
.L2029:
	movs	r5, #0
	b	.L2021
.L2023:
	subs	r2, r2, #1
	strh	r2, [r3, r0, lsl #1]	@ movhi
.L2022:
	ldr	r6, .L2033+36
	movw	r3, #65535
	ldrh	r0, [r6]
	cmp	r0, r3
	bne	.L2028
	strh	r4, [r6]	@ movhi
	b	.L2029
.L2028:
	cmp	r4, r0
	beq	.L2029
	bl	update_vpc_list
	ldr	r3, .L2033+40
	adds	r5, r0, #0
	ldr	r2, .L2033+44
	it	ne
	movne	r5, #1
	strh	r4, [r6]	@ movhi
	ldr	r3, [r3]
	ldr	r2, [r2]
	subs	r3, r3, r2
	asrs	r2, r3, #1
	ldr	r3, .L2033+48
	muls	r3, r2, r3
	ldr	r2, .L2033
	ldr	r2, [r2]
	uxth	r1, r3
	ldrh	r2, [r2, r1, lsl #1]
	cbnz	r2, .L2021
	cmp	r4, r1
	beq	.L2021
	ldr	r1, .L2033+8
	movw	r2, #3816
	ldr	r0, .L2033+12
	bl	printf
	ldr	r1, .L2033+16
	ldr	r0, .L2033+20
	bl	printf
.L2021:
	mov	r0, r5
	pop	{r4, r5, r6, pc}
.L2034:
	.align	2
.L2033:
	.word	.LANCHOR85
	.word	.LC38
	.word	.LANCHOR216
	.word	.LC5
	.word	.LC6
	.word	.LC7
	.word	.LANCHOR89
	.word	.LANCHOR90
	.word	.LC39
	.word	.LANCHOR136
	.word	.LANCHOR84
	.word	.LANCHOR83
	.word	-1431655765
	.size	decrement_vpc_count, .-decrement_vpc_count
	.section	.text.FtlSlcSuperblockCheck,"ax",%progbits
	.align	1
	.global	FtlSlcSuperblockCheck
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	FtlSlcSuperblockCheck, %function
FtlSlcSuperblockCheck:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	ldrh	r3, [r0, #4]
	push	{r4, r5, r6, lr}
	mov	r4, r0
	cmp	r3, #0
	beq	.L2035
	ldrh	r2, [r0]
	movw	r3, #65535
	cmp	r2, r3
	beq	.L2035
	ldrb	r3, [r0, #6]	@ zero_extendqisi2
	ldr	r5, .L2046
	ldr	r6, .L2046+4
	adds	r3, r3, #8
	ldrh	r3, [r0, r3, lsl #1]
.L2039:
	movw	r2, #65535
	cmp	r3, r2
	beq	.L2041
	ldrb	r3, [r4, #8]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L2042
	ldrb	r1, [r5]	@ zero_extendqisi2
	cbnz	r1, .L2042
	ldrh	r1, [r4, #2]
	ldrh	r1, [r6, r1, lsl #1]
	cmp	r1, r2
	bne	.L2042
	ldrh	r3, [r4, #4]
	ldrh	r0, [r4]
	subs	r3, r3, #1
	strh	r3, [r4, #4]	@ movhi
	bl	decrement_vpc_count
	ldrh	r2, [r4, #4]
	cbnz	r2, .L2041
	ldrh	r3, [r4, #2]
	strb	r2, [r4, #6]
	adds	r3, r3, #1
	strh	r3, [r4, #2]	@ movhi
	pop	{r4, r5, r6, pc}
.L2041:
	ldrb	r3, [r4, #6]	@ zero_extendqisi2
	ldr	r2, .L2046+8
	adds	r3, r3, #1
	ldrh	r2, [r2]
	uxtb	r3, r3
	strb	r3, [r4, #6]
	cmp	r2, r3
	bne	.L2040
	ldrh	r3, [r4, #2]
	adds	r3, r3, #1
	strh	r3, [r4, #2]	@ movhi
	movs	r3, #0
	strb	r3, [r4, #6]
.L2040:
	ldrb	r3, [r4, #6]	@ zero_extendqisi2
	adds	r3, r3, #8
	ldrh	r3, [r4, r3, lsl #1]
	b	.L2039
.L2042:
	ldrb	r2, [r5]	@ zero_extendqisi2
	cbz	r2, .L2035
	cmp	r3, #1
	bne	.L2035
	ldr	r3, .L2046+12
	ldrh	r2, [r4, #2]
	ldrh	r3, [r3]
	cmp	r2, r3
	bcc	.L2035
	ldr	r3, .L2046+16
	ldrh	r1, [r4]
	ldrh	r0, [r4, #4]
	ldr	r2, [r3]
	ldrh	r3, [r2, r1, lsl #1]
	subs	r3, r3, r0
	strh	r3, [r2, r1, lsl #1]	@ movhi
	movs	r3, #0
	ldr	r2, .L2046+20
	strh	r3, [r4, #4]	@ movhi
	strb	r3, [r4, #6]
	ldrh	r2, [r2]
	strh	r2, [r4, #2]	@ movhi
.L2035:
	pop	{r4, r5, r6, pc}
.L2047:
	.align	2
.L2046:
	.word	.LANCHOR16
	.word	.LANCHOR123
	.word	.LANCHOR38
	.word	.LANCHOR53
	.word	.LANCHOR85
	.word	.LANCHOR52
	.size	FtlSlcSuperblockCheck, .-FtlSlcSuperblockCheck
	.section	.text.get_new_active_ppa,"ax",%progbits
	.align	1
	.global	get_new_active_ppa
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	get_new_active_ppa, %function
get_new_active_ppa:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	ldrh	r2, [r0]
	movw	r3, #65535
	push	{r4, r5, r6, r7, r8, lr}
	mov	r4, r0
	cmp	r2, r3
	bne	.L2049
	ldr	r1, .L2070
	movw	r2, #3700
	ldr	r0, .L2070+4
	bl	printf
	ldr	r1, .L2070+8
	ldr	r0, .L2070+12
	bl	printf
.L2049:
	ldr	r5, .L2070+16
	ldrh	r2, [r4, #2]
	ldrh	r3, [r5]
	cmp	r2, r3
	bne	.L2050
	ldr	r1, .L2070
	movw	r2, #3701
	ldr	r0, .L2070+4
	bl	printf
	ldr	r1, .L2070+8
	ldr	r0, .L2070+12
	bl	printf
.L2050:
	ldrh	r3, [r4, #4]
	cbnz	r3, .L2051
	ldr	r1, .L2070
	movw	r2, #3702
	ldr	r0, .L2070+4
	bl	printf
	ldr	r1, .L2070+8
	ldr	r0, .L2070+12
	bl	printf
.L2051:
	movs	r3, #0
	ldr	r7, .L2070+20
	strb	r3, [r4, #10]
	ldrb	r3, [r4, #6]	@ zero_extendqisi2
	ldr	r6, .L2070+24
	adds	r3, r3, #8
	ldrh	r2, [r4, r3, lsl #1]
.L2052:
	movw	r0, #65535
	cmp	r2, r0
	beq	.L2053
	ldrb	r3, [r4, #8]	@ zero_extendqisi2
	ldrh	r1, [r4, #2]
	cmp	r3, #1
	ldrh	r3, [r4, #4]
	bne	.L2055
	ldrb	ip, [r6]	@ zero_extendqisi2
	cmp	ip, #0
	bne	.L2055
	ldr	ip, .L2070+28
	ldrh	ip, [ip, r1, lsl #1]
	cmp	ip, r0
	bne	.L2055
	subs	r3, r3, #1
	ldrh	r0, [r4]
	strh	r3, [r4, #4]	@ movhi
	bl	decrement_vpc_count
.L2053:
	ldrb	r3, [r4, #6]	@ zero_extendqisi2
	ldrh	r2, [r7]
	adds	r3, r3, #1
	uxtb	r3, r3
	cmp	r2, r3
	strb	r3, [r4, #6]
	bne	.L2054
	ldrh	r3, [r4, #2]
	adds	r3, r3, #1
	strh	r3, [r4, #2]	@ movhi
	movs	r3, #0
	strb	r3, [r4, #6]
.L2054:
	ldrb	r3, [r4, #6]	@ zero_extendqisi2
	adds	r3, r3, #8
	ldrh	r2, [r4, r3, lsl #1]
	b	.L2052
.L2055:
	ldr	r8, .L2070+24
	orr	r6, r1, r2, lsl #10
	subs	r3, r3, #1
	strh	r3, [r4, #4]	@ movhi
.L2056:
	ldrb	r3, [r4, #6]	@ zero_extendqisi2
	movw	r2, #65535
	ldrh	r0, [r7]
.L2058:
	adds	r3, r3, #1
	uxtb	r3, r3
	cmp	r3, r0
	itttt	eq
	ldrheq	r3, [r4, #2]
	addeq	r3, r3, #1
	strheq	r3, [r4, #2]	@ movhi
	moveq	r3, #0
	add	r1, r3, #8
	ldrh	r1, [r4, r1, lsl #1]
	cmp	r1, r2
	beq	.L2058
	strb	r3, [r4, #6]
	ldrb	r3, [r4, #8]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L2059
	ldrb	r1, [r8]	@ zero_extendqisi2
	ldrh	r3, [r4, #2]
	cbnz	r1, .L2060
	ldr	r1, .L2070+28
	ldrh	r3, [r1, r3, lsl #1]
	cmp	r3, r2
	bne	.L2059
	ldrh	r3, [r4, #4]
	cbz	r3, .L2059
	subs	r3, r3, #1
	ldrh	r0, [r4]
	strh	r3, [r4, #4]	@ movhi
	bl	decrement_vpc_count
	b	.L2056
.L2060:
	ldr	r2, .L2070+32
	ldrh	r2, [r2]
	cmp	r3, r2
	bcc	.L2059
	ldr	r3, .L2070+36
	ldrh	r1, [r4]
	ldrh	r0, [r4, #4]
	ldr	r2, [r3]
	ldrh	r3, [r2, r1, lsl #1]
	subs	r3, r3, r0
	strh	r3, [r2, r1, lsl #1]	@ movhi
	movs	r3, #0
	ldrh	r2, [r5]
	strh	r3, [r4, #4]	@ movhi
	strb	r3, [r4, #6]
	strh	r2, [r4, #2]	@ movhi
.L2059:
	ldrh	r2, [r4, #2]
	ldrh	r3, [r5]
	cmp	r2, r3
	bne	.L2048
	ldrh	r3, [r4, #4]
	cbz	r3, .L2048
	ldr	r1, .L2070
	movw	r2, #3752
	ldr	r0, .L2070+4
	bl	printf
	ldr	r1, .L2070+8
	ldr	r0, .L2070+12
	bl	printf
.L2048:
	mov	r0, r6
	pop	{r4, r5, r6, r7, r8, pc}
.L2071:
	.align	2
.L2070:
	.word	.LANCHOR217
	.word	.LC5
	.word	.LC6
	.word	.LC7
	.word	.LANCHOR52
	.word	.LANCHOR38
	.word	.LANCHOR16
	.word	.LANCHOR123
	.word	.LANCHOR53
	.word	.LANCHOR85
	.size	get_new_active_ppa, .-get_new_active_ppa
	.section	.text.FtlVpcTblFlush,"ax",%progbits
	.align	1
	.global	FtlVpcTblFlush
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	FtlVpcTblFlush, %function
FtlVpcTblFlush:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 0, uses_anonymous_args = 0
	ldr	r2, .L2096
	push	{r0, r1, r4, r5, r6, r7, r8, r10, fp, lr}
	ldr	r3, [r2]
	str	r2, [sp, #4]
	cmp	r3, #0
	bne	.L2074
	ldr	r4, .L2096+4
	ldr	r8, .L2096+112
	ldr	fp, .L2096+116
	ldr	r5, .L2096+8
	ldr	r0, [r8]
	ldr	r6, [fp]
	ldrh	r2, [r4]
	str	r0, [r5, #8]
	str	r6, [r5, #12]
	strh	r2, [r6, #2]	@ movhi
	movw	r2, #61604
	ldr	r7, .L2096+12
	strh	r2, [r6]	@ movhi
	str	r3, [r6, #12]
	ldr	ip, .L2096+120
	ldr	r2, [r4, #8]
	str	r3, [r6, #8]
	ldr	r3, .L2096+16
	str	r2, [r6, #4]
	stm	r7, {r3, ip}
	ldrh	r3, [r4, #6]
	strh	r3, [r7, #8]	@ movhi
	ldr	r3, .L2096+20
	ldrh	r3, [r3]
	strb	r3, [r7, #10]
	ldr	r3, .L2096+24
	ldrh	r2, [r3]
	ldrh	r1, [r3, #2]
	strh	r2, [r7, #14]	@ movhi
	ldrb	r2, [r3, #6]	@ zero_extendqisi2
	ldrb	r3, [r3, #8]	@ zero_extendqisi2
	strb	r3, [r7, #11]
	orr	r2, r2, r1, lsl #6
	ldr	r3, .L2096+28
	strh	r2, [r7, #16]	@ movhi
	ldrh	r2, [r3]
	ldrh	r1, [r3, #2]
	strh	r2, [r7, #18]	@ movhi
	ldrb	r2, [r3, #6]	@ zero_extendqisi2
	ldrb	r3, [r3, #8]	@ zero_extendqisi2
	strb	r3, [r7, #12]
	orr	r2, r2, r1, lsl #6
	ldr	r3, .L2096+32
	strh	r2, [r7, #20]	@ movhi
	ldrh	r2, [r3]
	strh	r2, [r7, #22]	@ movhi
	ldrh	r1, [r3, #2]
	ldrb	r2, [r3, #6]	@ zero_extendqisi2
	ldrb	r3, [r3, #8]	@ zero_extendqisi2
	strb	r3, [r7, #13]
	orr	r2, r2, r1, lsl #6
	ldr	r3, .L2096+36
	movs	r1, #255
	strh	r2, [r7, #24]	@ movhi
	ldr	r3, [r3]
	str	r3, [r7, #32]
	ldr	r3, .L2096+40
	ldr	r3, [r3]
	str	r3, [r7, #40]
	ldr	r3, .L2096+44
	ldr	r3, [r3]
	str	r3, [r7, #36]
	ldr	r3, .L2096+48
	ldrh	r3, [r3]
	strh	r3, [r7, #44]	@ movhi
	ldr	r3, .L2096+52
	ldrh	r3, [r3]
	strh	r3, [r7, #46]	@ movhi
	ldr	r3, .L2096+56
	ldrh	r2, [r3]
	bl	ftl_memset
	mov	r1, r7
	ldr	r7, .L2096+60
	movs	r2, #48
	ldr	r0, [r5, #8]
	bl	ftl_memcpy
	ldrh	r2, [r7]
	ldr	r3, .L2096+64
	ldr	r0, [r5, #8]
	ldr	r1, [r3]
	lsls	r2, r2, #1
	adds	r0, r0, #48
	bl	ftl_memcpy
	ldrh	r0, [r7]
	ldr	r3, [r5, #8]
	ldr	r1, .L2096+68
	lsrs	r2, r0, #3
	lsls	r0, r0, #1
	ldr	r1, [r1]
	adds	r0, r0, #51
	adds	r2, r2, #4
	bic	r0, r0, #3
	add	r0, r0, r3
	bl	ftl_memcpy
	ldr	r3, .L2096+72
	ldrh	r3, [r3]
	cbz	r3, .L2075
	ldrh	r0, [r7]
	ldr	r3, .L2096+76
	ldr	r1, .L2096+80
	ldrh	r2, [r3]
	lsrs	r3, r0, #3
	ldr	r1, [r1]
	add	r3, r3, r0, lsl #1
	ldr	r0, [r5, #8]
	adds	r3, r3, #52
	lsls	r2, r2, #2
	ubfx	r3, r3, #2, #14
	add	r0, r0, r3, lsl #2
	bl	ftl_memcpy
.L2075:
	movs	r7, #0
	movw	r10, #65535
	movs	r0, #0
	bl	FtlUpdateVaildLpn
.L2076:
	ldr	r3, [r8]
	ldrh	r1, [r4, #2]
	ldrh	r2, [r4]
	str	r3, [r5, #8]
	ldr	r3, [fp]
	str	r3, [r5, #12]
	orr	r3, r1, r2, lsl #10
	str	r3, [r5, #4]
	ldr	r3, .L2096+84
	ldrh	r3, [r3]
	subs	r3, r3, #1
	cmp	r1, r3
	blt	.L2077
	movs	r3, #0
	ldrh	r10, [r4, #4]
	strh	r3, [r4, #2]	@ movhi
	strh	r2, [r4, #4]	@ movhi
	bl	FtlFreeSysBlkQueueOut
	ldr	r3, .L2096+40
	ldr	r1, .L2096+40
	strh	r0, [r4]	@ movhi
	ldr	r3, [r3]
	adds	r2, r3, #1
	str	r3, [r4, #8]
	str	r2, [r1]
	lsls	r2, r0, #10
	str	r2, [r5, #4]
	str	r3, [r6, #4]
	strh	r0, [r6, #2]	@ movhi
.L2077:
	ldr	r3, .L2096+88
	ldrb	r3, [r3]	@ zero_extendqisi2
	cbz	r3, .L2078
	ldr	r3, .L2096+56
	ldr	r0, [r8]
	ldrh	r1, [r3]
	bl	js_hash
	str	r0, [r6, #12]
.L2078:
	movs	r3, #1
	ldr	r0, .L2096+8
	mov	r2, r3
	mov	r1, r3
	bl	FlashProgPages
	ldrh	r3, [r4, #2]
	ldr	r2, [r5]
	adds	r3, r3, #1
	uxth	r3, r3
	adds	r1, r2, #1
	strh	r3, [r4, #2]	@ movhi
	bne	.L2079
	cmp	r3, #1
	bne	.L2080
	ldr	r1, .L2096+92
	movw	r2, #1375
	ldr	r0, .L2096+96
	bl	printf
	ldr	r1, .L2096+100
	ldr	r0, .L2096+104
	bl	printf
.L2080:
	ldrh	r3, [r4, #2]
	adds	r7, r7, #1
	uxth	r7, r7
	cmp	r3, #1
	itttt	eq
	ldreq	r3, .L2096+84
	ldrheq	r3, [r3]
	addeq	r3, r3, #-1
	strheq	r3, [r4, #2]	@ movhi
	cmp	r7, #3
	bls	.L2076
	mov	r2, r7
	ldr	r1, [r5, #4]
	ldr	r0, .L2096+108
	bl	printf
	ldr	r2, [sp, #4]
	movs	r3, #1
	str	r3, [r2]
.L2074:
	movs	r0, #0
	add	sp, sp, #8
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r10, fp, pc}
.L2079:
	cmp	r3, #1
	beq	.L2076
	cmp	r2, #256
	beq	.L2076
	movw	r3, #65535
	cmp	r10, r3
	beq	.L2074
	movs	r1, #1
	mov	r0, r10
	bl	FtlFreeSysBlkQueueIn
	b	.L2074
.L2097:
	.align	2
.L2096:
	.word	.LANCHOR78
	.word	.LANCHOR218
	.word	.LANCHOR211
	.word	.LANCHOR82
	.word	1179929683
	.word	.LANCHOR45
	.word	.LANCHOR93
	.word	.LANCHOR94
	.word	.LANCHOR95
	.word	.LANCHOR172
	.word	.LANCHOR164
	.word	.LANCHOR165
	.word	.LANCHOR115
	.word	.LANCHOR116
	.word	.LANCHOR57
	.word	.LANCHOR40
	.word	.LANCHOR85
	.word	.LANCHOR1
	.word	.LANCHOR69
	.word	.LANCHOR66
	.word	.LANCHOR134
	.word	.LANCHOR53
	.word	.LANCHOR2
	.word	.LANCHOR219
	.word	.LC5
	.word	.LC6
	.word	.LC7
	.word	.LC40
	.word	.LANCHOR189
	.word	.LANCHOR195
	.word	1342177379
	.size	FtlVpcTblFlush, .-FtlVpcTblFlush
	.section	.text.FtlSuperblockPowerLostFix,"ax",%progbits
	.align	1
	.global	FtlSuperblockPowerLostFix
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	FtlSuperblockPowerLostFix, %function
FtlSuperblockPowerLostFix:
	@ args = 0, pretend = 0, frame = 40
	@ frame_needed = 0, uses_anonymous_args = 0
	ldr	r3, .L2113
	push	{r4, r5, r6, r7, r8, r10, lr}
	mov	r4, r0
	sub	sp, sp, #44
	ldr	r8, [r3]
	cmp	r8, #0
	bne	.L2098
	ldr	r3, .L2113+4
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L2109
	ldrb	r3, [r0, #8]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L2109
	ldrh	r6, [r0, #4]
	mov	r8, r3
.L2100:
	mov	r3, #-1
	ldr	r2, .L2113+8
	str	r3, [sp, #20]
	movs	r7, #0
	ldr	r3, .L2113+12
	ldr	r5, [r2]
	mvn	r2, #2
	ldr	r10, .L2113+24
	ldr	r3, [r3]
	str	r5, [sp, #16]
	str	r3, [sp, #12]
	str	r2, [r5, #8]
	mvn	r2, #1
	str	r2, [r5, #12]
	ldrh	r2, [r4]
	strh	r7, [r5]	@ movhi
	strh	r2, [r5, #2]	@ movhi
	movw	r2, #61589
	str	r2, [r3]
	add	r2, r2, #304087040
	add	r2, r2, #1269760
	addw	r2, r2, #1507
	str	r2, [r3, #4]
.L2101:
	adds	r6, r6, #-1
	bcc	.L2104
	ldrh	r3, [r4, #4]
	cbnz	r3, .L2102
.L2104:
	ldr	r3, .L2113+16
	ldrh	r1, [r4]
	ldrh	r0, [r4, #4]
	ldr	r2, [r3]
	ldrh	r3, [r2, r1, lsl #1]
	subs	r3, r3, r0
	strh	r3, [r2, r1, lsl #1]	@ movhi
	ldr	r3, .L2113+20
	ldrh	r3, [r3]
	strh	r3, [r4, #2]	@ movhi
	movs	r3, #0
	strb	r3, [r4, #6]
	strh	r3, [r4, #4]	@ movhi
.L2098:
	add	sp, sp, #44
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r10, pc}
.L2109:
	movs	r6, #12
	b	.L2100
.L2102:
	mov	r0, r4
	bl	get_new_active_ppa
	str	r0, [sp, #8]
	adds	r0, r0, #1
	beq	.L2104
	ldr	r3, [r10]
	movs	r1, #1
	add	r0, sp, #4
	str	r3, [r5, #4]
	adds	r3, r3, #1
	adds	r2, r3, #1
	mov	r2, r8
	it	eq
	moveq	r3, r7
	str	r3, [r10]
	movs	r3, #0
	bl	FlashProgPages
	ldrh	r0, [r4]
	bl	decrement_vpc_count
	b	.L2101
.L2114:
	.align	2
.L2113:
	.word	.LANCHOR78
	.word	.LANCHOR16
	.word	.LANCHOR195
	.word	.LANCHOR189
	.word	.LANCHOR85
	.word	.LANCHOR52
	.word	.LANCHOR165
	.size	FtlSuperblockPowerLostFix, .-FtlSuperblockPowerLostFix
	.section	.text.FtlLoadFactoryBbt,"ax",%progbits
	.align	1
	.global	FtlLoadFactoryBbt
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	FtlLoadFactoryBbt, %function
FtlLoadFactoryBbt:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	ldr	r3, .L2125
	push	{r4, r5, r6, r7, r8, r10, fp, lr}
	movs	r6, #0
	ldr	r5, .L2125+4
	ldr	r3, [r3]
	ldr	r7, .L2125+8
	ldr	r10, .L2125+20
	str	r3, [r5, #8]
	ldr	r3, .L2125+12
	ldr	r8, [r3]
	str	r8, [r5, #12]
.L2116:
	ldr	r3, .L2125+16
	ldrh	r3, [r3]
	cmp	r6, r3
	bcc	.L2121
	movs	r0, #0
	pop	{r4, r5, r6, r7, r8, r10, fp, pc}
.L2121:
	ldrh	r4, [r10]
	movw	r3, #65535
	ldr	fp, .L2125+4
	strh	r3, [r7, #2]!	@ movhi
	subs	r4, r4, #1
	uxth	r4, r4
.L2117:
	ldrh	r3, [r10]
	sub	r2, r3, #15
	cmp	r2, r4
	bgt	.L2119
	mla	r3, r6, r3, r4
	movs	r2, #1
	mov	r1, r2
	mov	r0, fp
	lsls	r3, r3, #10
	str	r3, [r5, #4]
	bl	FlashReadPages
	ldr	r3, [r5]
	adds	r3, r3, #1
	beq	.L2118
	ldrh	r2, [r8]
	movw	r3, #61664
	cmp	r2, r3
	bne	.L2118
	strh	r4, [r7]	@ movhi
.L2119:
	adds	r6, r6, #1
	b	.L2116
.L2118:
	subs	r4, r4, #1
	uxth	r4, r4
	b	.L2117
.L2126:
	.align	2
.L2125:
	.word	.LANCHOR189
	.word	.LANCHOR211
	.word	.LANCHOR76+10
	.word	.LANCHOR195
	.word	.LANCHOR45
	.word	.LANCHOR51
	.size	FtlLoadFactoryBbt, .-FtlLoadFactoryBbt
	.section	.text.FtlGetLastWrittenPage,"ax",%progbits
	.align	1
	.global	FtlGetLastWrittenPage
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	FtlGetLastWrittenPage, %function
FtlGetLastWrittenPage:
	@ args = 0, pretend = 0, frame = 104
	@ frame_needed = 0, uses_anonymous_args = 0
	cmp	r1, #1
	push	{r4, r5, r6, r7, r8, lr}
	it	eq
	ldreq	r3, .L2139
	sub	sp, sp, #104
	lsl	r7, r0, #10
	mov	r2, r1
	it	ne
	ldrne	r3, .L2139+4
	mov	r8, r1
	movs	r6, #0
	movs	r1, #1
	add	r0, sp, #4
	ldrh	r5, [r3]
	add	r3, sp, #40
	str	r3, [sp, #16]
	str	r6, [sp, #12]
	subs	r5, r5, #1
	sxth	r5, r5
	orr	r3, r5, r7
	str	r3, [sp, #8]
	bl	FlashReadPages
	ldr	r3, [sp, #40]
	adds	r3, r3, #1
	bne	.L2130
.L2131:
	cmp	r6, r5
	ble	.L2134
.L2130:
	mov	r0, r5
	add	sp, sp, #104
	@ sp needed
	pop	{r4, r5, r6, r7, r8, pc}
.L2134:
	adds	r3, r6, r5
	mov	r2, r8
	add	r3, r3, r3, lsr #31
	movs	r1, #1
	add	r0, sp, #4
	asrs	r4, r3, #1
	sxth	r3, r4
	orrs	r3, r3, r7
	str	r3, [sp, #8]
	bl	FlashReadPages
	ldr	r3, [sp, #40]
	adds	r3, r3, #1
	bne	.L2132
	ldr	r3, [sp, #44]
	adds	r3, r3, #1
	bne	.L2132
	ldr	r3, [sp, #4]
	adds	r3, r3, #1
	beq	.L2132
	subs	r4, r4, #1
	sxth	r5, r4
	b	.L2131
.L2132:
	adds	r4, r4, #1
	sxth	r6, r4
	b	.L2131
.L2140:
	.align	2
.L2139:
	.word	.LANCHOR53
	.word	.LANCHOR52
	.size	FtlGetLastWrittenPage, .-FtlGetLastWrittenPage
	.section	.text.FtlLoadBbt,"ax",%progbits
	.align	1
	.global	FtlLoadBbt
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	FtlLoadBbt, %function
FtlLoadBbt:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r3, r4, r5, r6, r7, r8, r10, lr}
	ldr	r8, .L2170+48
	ldr	r4, .L2170
	ldr	r3, [r8]
	ldr	r7, .L2170+4
	mov	r10, r4
	str	r3, [r4, #8]
	ldr	r3, .L2170+8
	ldr	r6, [r3]
	str	r6, [r4, #12]
	bl	FtlBbtMemInit
	ldrh	r5, [r7]
	subs	r5, r5, #1
	uxth	r5, r5
.L2142:
	ldrh	r3, [r7]
	subs	r3, r3, #47
	cmp	r3, r5
	bgt	.L2145
	lsls	r3, r5, #10
	movs	r2, #1
	mov	r1, r2
	mov	r0, r10
	str	r3, [r4, #4]
	bl	FlashReadPages
	ldr	r3, [r4]
	adds	r3, r3, #1
	bne	.L2143
	ldr	r3, [r4, #4]
	movs	r2, #1
	mov	r1, r2
	mov	r0, r10
	adds	r3, r3, #1
	str	r3, [r4, #4]
	bl	FlashReadPages
.L2143:
	ldr	r3, [r4]
	adds	r3, r3, #1
	beq	.L2144
	ldrh	r2, [r6]
	movw	r3, #61649
	cmp	r2, r3
	bne	.L2144
	ldr	r3, .L2170+12
	ldr	r2, [r6, #4]
	strh	r5, [r3]	@ movhi
	str	r2, [r3, #8]
	ldrh	r2, [r6, #8]
	strh	r2, [r3, #4]	@ movhi
.L2145:
	ldr	r5, .L2170+12
	movw	r2, #65535
	ldrh	r3, [r5]
	cmp	r3, r2
	beq	.L2159
	ldrh	r3, [r5, #4]
	cmp	r3, r2
	beq	.L2149
	lsls	r3, r3, #10
	movs	r2, #1
	mov	r1, r2
	ldr	r0, .L2170
	str	r3, [r4, #4]
	bl	FlashReadPages
	ldr	r3, [r4]
	adds	r3, r3, #1
	beq	.L2149
	ldrh	r2, [r6]
	movw	r3, #61649
	cmp	r2, r3
	bne	.L2149
	ldr	r3, [r6, #4]
	ldr	r2, [r5, #8]
	cmp	r3, r2
	bls	.L2149
	ldrh	r2, [r5, #4]
	str	r3, [r5, #8]
	ldrh	r3, [r6, #8]
	strh	r2, [r5]	@ movhi
	strh	r3, [r5, #4]	@ movhi
.L2149:
	ldr	r10, .L2170
	movs	r1, #1
	ldrh	r0, [r5]
	bl	FtlGetLastWrittenPage
	sxth	r7, r0
	adds	r0, r0, #1
	strh	r0, [r5, #2]	@ movhi
.L2151:
	cmp	r7, #0
	bge	.L2154
	ldr	r1, .L2170+16
	movw	r2, #339
	ldr	r0, .L2170+20
	bl	printf
	ldr	r1, .L2170+24
	ldr	r0, .L2170+28
	bl	printf
.L2153:
	ldrh	r3, [r6, #10]
	ldrh	r0, [r6, #12]
	strh	r3, [r5, #6]	@ movhi
	movw	r3, #65535
	cmp	r0, r3
	beq	.L2156
	ldr	r3, .L2170+32
	ldr	r2, [r3]
	cmp	r0, r2
	beq	.L2156
	ldr	r3, .L2170+36
	ldrh	r3, [r3]
	lsrs	r3, r3, #2
	cmp	r2, r3
	bcs	.L2156
	cmp	r0, r3
	bcs	.L2156
	bl	FtlSysBlkNumInit
.L2156:
	ldr	r6, .L2170+40
	movs	r5, #0
	ldr	r7, .L2170+44
	ldr	r8, .L2170+52
.L2157:
	ldrh	r3, [r7]
	cmp	r5, r3
	bcc	.L2158
	movs	r0, #0
	pop	{r3, r4, r5, r6, r7, r8, r10, pc}
.L2144:
	subs	r5, r5, #1
	uxth	r5, r5
	b	.L2142
.L2154:
	ldrh	r3, [r5]
	movs	r2, #1
	mov	r1, r2
	mov	r0, r10
	orr	r3, r7, r3, lsl #10
	str	r3, [r4, #4]
	ldr	r3, [r8]
	str	r3, [r4, #8]
	bl	FlashReadPages
	ldr	r3, [r4]
	adds	r3, r3, #1
	beq	.L2152
	ldrh	r2, [r6]
	movw	r3, #61649
	cmp	r2, r3
	beq	.L2153
.L2152:
	subs	r7, r7, #1
	sxth	r7, r7
	b	.L2151
.L2158:
	ldrh	r2, [r8]
	ldr	r1, [r4, #8]
	ldr	r0, [r6, #4]!
	lsls	r2, r2, #2
	mla	r1, r5, r2, r1
	adds	r5, r5, #1
	bl	ftl_memcpy
	b	.L2157
.L2159:
	mov	r0, #-1
	pop	{r3, r4, r5, r6, r7, r8, r10, pc}
.L2171:
	.align	2
.L2170:
	.word	.LANCHOR211
	.word	.LANCHOR51
	.word	.LANCHOR195
	.word	.LANCHOR76
	.word	.LANCHOR220
	.word	.LC5
	.word	.LC6
	.word	.LC7
	.word	.LANCHOR37
	.word	.LANCHOR41
	.word	.LANCHOR76+24
	.word	.LANCHOR45
	.word	.LANCHOR189
	.word	.LANCHOR126
	.size	FtlLoadBbt, .-FtlLoadBbt
	.section	.text.ftl_map_blk_gc,"ax",%progbits
	.align	1
	.global	ftl_map_blk_gc
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	ftl_map_blk_gc, %function
ftl_map_blk_gc:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 0, uses_anonymous_args = 0
	ldr	r3, [r0, #24]
	push	{r0, r1, r4, r5, r6, r7, r8, r10, fp, lr}
	mov	r4, r0
	ldr	r5, [r0, #12]
	str	r3, [sp]
	bl	ftl_free_no_use_map_blk
	ldrh	r3, [r4, #10]
	ldrh	r2, [r4, #8]
	subs	r3, r3, #4
	cmp	r2, r3
	blt	.L2173
	uxth	r0, r0
	ldrh	r8, [r5, r0, lsl #1]
	cmp	r8, #0
	beq	.L2173
	ldr	r3, [r4, #32]
	cbnz	r3, .L2173
	movs	r2, #1
	str	r2, [r4, #32]
	strh	r3, [r5, r0, lsl #1]	@ movhi
	ldrh	r3, [r4, #8]
	ldrh	r2, [r4, #2]
	subs	r3, r3, #1
	strh	r3, [r4, #8]	@ movhi
	ldr	r3, .L2185
	ldrh	r3, [r3]
	cmp	r2, r3
	bcc	.L2174
	mov	r0, r4
	bl	ftl_map_blk_alloc_new_blk
.L2174:
	ldr	r5, .L2185+4
	movs	r6, #0
.L2175:
	ldrh	r3, [r4, #6]
	uxth	r10, r6
	cmp	r3, r10
	bhi	.L2181
	movs	r1, #1
	mov	r0, r8
	bl	FtlFreeSysBlkQueueIn
	movs	r3, #0
	str	r3, [r4, #32]
.L2173:
	ldr	r3, .L2185
	ldrh	r2, [r4, #2]
	ldrh	r3, [r3]
	cmp	r2, r3
	bcc	.L2179
	mov	r0, r4
	bl	ftl_map_blk_alloc_new_blk
	b	.L2179
.L2181:
	ldr	r3, [sp]
	uxth	fp, r6
	add	r3, r3, fp, lsl #2
	str	r3, [sp, #4]
	ldr	r3, [sp]
	ldr	r2, [r3, fp, lsl #2]
	cmp	r8, r2, lsr #10
	bne	.L2176
	ldr	r3, .L2185+8
	str	r2, [r5, #4]
	movs	r2, #1
	ldr	r0, .L2185+4
	ldr	r1, [r3]
	str	r1, [r5, #8]
	ldr	r1, .L2185+12
	ldr	r7, [r1]
	mov	r1, r2
	str	r7, [r5, #12]
	bl	FlashReadPages
	ldrh	r2, [r7, #8]
	cmp	r2, r10
	beq	.L2177
	ldr	r1, .L2185+16
	mov	r2, #752
	ldr	r0, .L2185+20
	bl	printf
	ldr	r1, .L2185+24
	ldr	r0, .L2185+28
	bl	printf
.L2177:
	ldr	r2, [r5]
	adds	r2, r2, #1
	ldrh	r2, [r7, #8]
	bne	.L2178
.L2180:
	ldr	r1, [sp, #4]
	movs	r3, #0
	ldr	r0, .L2185+32
	str	r3, [r1]
	ldr	r1, [r5, #4]
	bl	printf
	ldr	r3, .L2185+36
	movs	r2, #1
	str	r2, [r3]
.L2179:
	movs	r0, #0
	add	sp, sp, #8
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r10, fp, pc}
.L2178:
	cmp	r2, r10
	bne	.L2180
	ldrh	r0, [r7]
	ldrh	r1, [r4, #4]
	cmp	r0, r1
	bne	.L2180
	ldr	r2, [r5, #8]
	mov	r1, fp
	mov	r0, r4
	bl	FtlMapWritePage
.L2176:
	adds	r6, r6, #1
	b	.L2175
.L2186:
	.align	2
.L2185:
	.word	.LANCHOR53
	.word	.LANCHOR211
	.word	.LANCHOR190
	.word	.LANCHOR195
	.word	.LANCHOR221
	.word	.LC5
	.word	.LC6
	.word	.LC7
	.word	.LC41
	.word	.LANCHOR78
	.size	ftl_map_blk_gc, .-ftl_map_blk_gc
	.section	.text.Ftl_write_map_blk_to_last_page,"ax",%progbits
	.align	1
	.global	Ftl_write_map_blk_to_last_page
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	Ftl_write_map_blk_to_last_page, %function
Ftl_write_map_blk_to_last_page:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	ldr	r3, .L2201
	push	{r4, r5, r6, r7, r8, r10, fp, lr}
	mov	r4, r0
	ldr	r5, [r3]
	cbnz	r5, .L2188
	ldrh	r3, [r0]
	movw	r2, #65535
	ldr	r6, [r0, #12]
	cmp	r3, r2
	bne	.L2189
	ldrh	r3, [r0, #8]
	cbz	r3, .L2190
	ldr	r1, .L2201+4
	movw	r2, #793
	ldr	r0, .L2201+8
	bl	printf
	ldr	r1, .L2201+12
	ldr	r0, .L2201+16
	bl	printf
.L2190:
	ldrh	r3, [r4, #8]
	adds	r3, r3, #1
	strh	r3, [r4, #8]	@ movhi
	bl	FtlFreeSysBlkQueueOut
	movs	r3, #0
	strh	r0, [r6]	@ movhi
	strh	r3, [r4, #2]	@ movhi
	strh	r3, [r4]	@ movhi
	ldr	r3, [r4, #28]
	adds	r3, r3, #1
	str	r3, [r4, #28]
.L2188:
	movs	r0, #0
	pop	{r4, r5, r6, r7, r8, r10, fp, pc}
.L2189:
	ldrh	r8, [r6, r3, lsl #1]
	movs	r1, #255
	ldrh	r3, [r0, #2]
	ldr	r7, .L2201+20
	ldr	fp, .L2201+40
	ldr	r10, [r0, #24]
	orr	r3, r3, r8, lsl #10
	ldr	r0, [fp]
	str	r3, [r7, #4]
	ldr	r3, .L2201+24
	str	r0, [r7, #8]
	ldr	r6, [r3]
	ldr	r3, [r4, #28]
	str	r6, [r7, #12]
	str	r3, [r6, #4]
	movw	r3, #64245
	strh	r3, [r6, #8]	@ movhi
	ldrh	r3, [r4, #4]
	strh	r8, [r6, #2]	@ movhi
	strh	r3, [r6]	@ movhi
	ldr	r3, .L2201+28
	ldrh	r2, [r3]
	lsls	r2, r2, #3
	bl	ftl_memset
	ldrh	ip, [r4, #6]
	mov	r3, r5
	ldr	r1, [fp]
	mov	r2, r5
.L2191:
	uxth	r0, r3
	cmp	ip, r0
	bhi	.L2193
	ldr	r3, .L2201+32
	ldrb	r3, [r3]	@ zero_extendqisi2
	cbz	r3, .L2194
	ldr	r3, .L2201+36
	ldr	r0, [r7, #8]
	ldrh	r1, [r3]
	bl	js_hash
	str	r0, [r6, #12]
.L2194:
	movs	r2, #1
	movs	r3, #0
	mov	r1, r2
	ldr	r0, .L2201+20
	bl	FlashProgPages
	ldrh	r3, [r4, #2]
	mov	r0, r4
	adds	r3, r3, #1
	strh	r3, [r4, #2]	@ movhi
	bl	ftl_map_blk_gc
	b	.L2188
.L2193:
	ldr	r0, [r10, r3, lsl #2]
	cmp	r8, r0, lsr #10
	bne	.L2192
	adds	r2, r2, #1
	uxth	r2, r2
	str	r3, [r1, r2, lsl #3]
	add	r5, r1, r2, lsl #3
	ldr	r0, [r10, r3, lsl #2]
	str	r0, [r5, #4]
.L2192:
	adds	r3, r3, #1
	b	.L2191
.L2202:
	.align	2
.L2201:
	.word	.LANCHOR78
	.word	.LANCHOR222
	.word	.LC5
	.word	.LC6
	.word	.LC7
	.word	.LANCHOR211
	.word	.LANCHOR195
	.word	.LANCHOR53
	.word	.LANCHOR2
	.word	.LANCHOR57
	.word	.LANCHOR189
	.size	Ftl_write_map_blk_to_last_page, .-Ftl_write_map_blk_to_last_page
	.section	.text.FtlMapWritePage,"ax",%progbits
	.align	1
	.global	FtlMapWritePage
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	FtlMapWritePage, %function
FtlMapWritePage:
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r0, r1, r2, r3, r4, r5, r6, r7, r8, r10, fp, lr}
	mov	r4, r0
	ldr	r10, .L2229+44
	mov	r8, r1
	movs	r6, #0
	str	r2, [sp, #4]
.L2204:
	ldr	r2, .L2229
	ldr	r3, [r2]
	adds	r3, r3, #1
	str	r3, [r2]
	ldrh	r3, [r10]
	ldrh	r2, [r4, #2]
	subs	r3, r3, #1
	cmp	r2, r3
	bge	.L2205
	ldrh	r2, [r4]
	movw	r3, #65535
	cmp	r2, r3
	bne	.L2206
.L2205:
	mov	r0, r4
	bl	Ftl_write_map_blk_to_last_page
.L2206:
	ldr	r3, .L2229+4
	ldr	r2, [r3]
	str	r3, [sp, #8]
	cmp	r2, #0
	bne	.L2224
	ldrh	r2, [r4]
	ldr	r3, [r4, #12]
	ldrh	r3, [r3, r2, lsl #1]
	cbnz	r3, .L2208
	ldr	r1, .L2229+8
	movw	r2, #865
	ldr	r0, .L2229+12
	bl	printf
	ldr	r1, .L2229+16
	ldr	r0, .L2229+20
	bl	printf
.L2208:
	ldrh	r2, [r4]
	ldrh	r3, [r4, #10]
	cmp	r2, r3
	bcc	.L2209
	ldr	r1, .L2229+8
	movw	r2, #866
	ldr	r0, .L2229+12
	bl	printf
	ldr	r1, .L2229+16
	ldr	r0, .L2229+20
	bl	printf
.L2209:
	ldrh	r2, [r4]
	movs	r1, #0
	ldr	r3, [r4, #12]
	ldr	r5, .L2229+24
	ldrh	r7, [r3, r2, lsl #1]
	movs	r2, #16
	ldrh	r3, [r4, #2]
	mov	fp, r5
	orr	r3, r3, r7, lsl #10
	str	r3, [r5, #4]
	ldr	r3, [sp, #4]
	str	r3, [r5, #8]
	ldr	r3, .L2229+28
	ldr	r0, [r3]
	str	r0, [r5, #12]
	bl	ftl_memset
	ldr	r3, [r5, #12]
	ldr	r2, [r4, #28]
	str	r3, [sp, #12]
	str	r2, [r3, #4]
	ldrh	r2, [r4, #4]
	strh	r8, [r3, #8]	@ movhi
	strh	r7, [r3, #2]	@ movhi
	strh	r2, [r3]	@ movhi
	ldr	r2, .L2229+32
	ldrb	r2, [r2]	@ zero_extendqisi2
	cbz	r2, .L2210
	ldr	r2, .L2229+36
	ldr	r0, [r5, #8]
	ldrh	r1, [r2]
	bl	js_hash
	ldr	r3, [sp, #12]
	str	r0, [r3, #12]
.L2210:
	movs	r3, #1
	ldr	r0, .L2229+24
	mov	r2, r3
	mov	r1, r3
	bl	FlashProgPages
	ldrh	r3, [r4, #2]
	ldr	r2, [r5]
	adds	r3, r3, #1
	uxth	r3, r3
	adds	r1, r2, #1
	strh	r3, [r4, #2]	@ movhi
	bne	.L2211
	ldr	r1, [r5, #4]
	adds	r6, r6, #1
	ldr	r0, .L2229+40
	uxth	r6, r6
	bl	printf
	ldrh	r3, [r4, #2]
	cmp	r3, #2
	itttt	ls
	ldrls	r3, .L2229+44
	ldrhls	r3, [r3]
	addls	r3, r3, #-1
	strhls	r3, [r4, #2]	@ movhi
	cmp	r6, #3
	bls	.L2204
	mov	r2, r6
	ldr	r1, [fp, #4]
	ldr	r0, .L2229+48
	bl	printf
	ldr	r2, [sp, #8]
	movs	r3, #1
	str	r3, [r2]
.L2224:
	movs	r0, #0
	add	sp, sp, #16
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r10, fp, pc}
.L2211:
	cbz	r2, .L2214
	cmp	r3, #1
	strh	r7, [r4, #40]	@ movhi
	bne	.L2215
.L2216:
	movs	r3, #0
	str	r3, [r4, #36]
	b	.L2204
.L2215:
	cmp	r2, #256
.L2228:
	beq	.L2216
	ldr	r3, [r4, #36]
	cmp	r3, #0
	bne	.L2216
	ldr	r2, [fp, #4]
	ldr	r3, [r4, #24]
	str	r2, [r3, r8, lsl #2]
	b	.L2224
.L2214:
	cmp	r3, #1
	b	.L2228
.L2230:
	.align	2
.L2229:
	.word	.LANCHOR170
	.word	.LANCHOR78
	.word	.LANCHOR223
	.word	.LC5
	.word	.LC6
	.word	.LC7
	.word	.LANCHOR211
	.word	.LANCHOR195
	.word	.LANCHOR2
	.word	.LANCHOR57
	.word	.LC42
	.word	.LANCHOR53
	.word	.LC43
	.size	FtlMapWritePage, .-FtlMapWritePage
	.section	.text.flush_l2p_region,"ax",%progbits
	.align	1
	.global	flush_l2p_region
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	flush_l2p_region, %function
flush_l2p_region:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r3, r4, r5, lr}
	movs	r4, #12
	ldr	r5, .L2232
	muls	r4, r0, r4
	ldr	r0, .L2232+4
	ldr	r3, [r5]
	adds	r2, r3, r4
	ldrh	r1, [r3, r4]
	ldr	r2, [r2, #8]
	bl	FtlMapWritePage
	ldr	r3, [r5]
	movs	r0, #0
	add	r4, r4, r3
	ldr	r3, [r4, #4]
	bic	r3, r3, #-2147483648
	str	r3, [r4, #4]
	pop	{r3, r4, r5, pc}
.L2233:
	.align	2
.L2232:
	.word	.LANCHOR98
	.word	.LANCHOR130
	.size	flush_l2p_region, .-flush_l2p_region
	.section	.text.l2p_flush,"ax",%progbits
	.align	1
	.global	l2p_flush
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	l2p_flush, %function
l2p_flush:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, lr}
	movs	r4, #0
	ldr	r5, .L2238
	ldr	r6, .L2238+4
.L2235:
	ldrh	r3, [r5]
	uxth	r0, r4
	cmp	r3, r0
	bhi	.L2237
	movs	r0, #0
	pop	{r4, r5, r6, pc}
.L2237:
	ldr	r2, [r6]
	uxth	r3, r4
	movs	r1, #12
	mla	r3, r1, r3, r2
	ldr	r3, [r3, #4]
	cmp	r3, #0
	bge	.L2236
	bl	flush_l2p_region
.L2236:
	adds	r4, r4, #1
	b	.L2235
.L2239:
	.align	2
.L2238:
	.word	.LANCHOR67
	.word	.LANCHOR98
	.size	l2p_flush, .-l2p_flush
	.section	.text.FtlVendorPartWrite,"ax",%progbits
	.align	1
	.global	FtlVendorPartWrite
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	FtlVendorPartWrite, %function
FtlVendorPartWrite:
	@ args = 0, pretend = 0, frame = 56
	@ frame_needed = 0, uses_anonymous_args = 0
	ldr	r3, .L2252
	push	{r4, r5, r6, r7, r8, r10, fp, lr}
	sub	sp, sp, #56
	str	r2, [sp]
	adds	r2, r0, r1
	mov	r7, r0
	mov	r5, r1
	ldrh	r3, [r3]
	cmp	r2, r3
	bhi	.L2248
	ldr	r3, .L2252+4
	mov	r8, #0
	ldrh	r6, [r3]
	lsr	r6, r0, r6
	lsl	fp, r6, #2
.L2242:
	cbnz	r5, .L2247
.L2240:
	mov	r0, r8
	add	sp, sp, #56
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r10, fp, pc}
.L2247:
	ldr	r3, .L2252+8
	mov	r0, r7
	ldr	r10, .L2252+24
	ldr	r3, [r3]
	ldr	r2, [r3, fp]
	ldr	r3, .L2252+12
	str	r2, [sp, #12]
	ldrh	r3, [r3]
	mov	r1, r3
	str	r3, [sp, #8]
	bl	__aeabi_uidivmod
	ldr	r3, [sp, #8]
	ldr	r2, [sp, #12]
	str	r1, [sp, #4]
	subs	r4, r3, r1
	uxth	r4, r4
	cmp	r5, r4
	it	cc
	uxthcc	r4, r5
	cbz	r2, .L2244
	cmp	r4, r3
	beq	.L2244
	ldr	r3, [r10]
	add	r0, sp, #20
	str	r2, [sp, #24]
	movs	r2, #1
	mov	r1, r2
	str	r3, [sp, #28]
	movs	r3, #0
	str	r3, [sp, #32]
	bl	FlashReadPages
.L2245:
	lsls	r3, r4, #9
	ldr	r0, [r10]
	subs	r5, r5, r4
	mov	r2, r3
	str	r3, [sp, #8]
	ldm	sp, {r1, r3}
	add	r7, r7, r4
	add	fp, fp, #4
	add	r0, r0, r3, lsl #9
	bl	ftl_memcpy
	ldr	r2, [r10]
	mov	r1, r6
	ldr	r0, .L2252+16
	adds	r6, r6, #1
	bl	FtlMapWritePage
	ldr	r3, [sp]
	adds	r0, r0, #1
	it	eq
	moveq	r8, #-1
	mov	r2, r3
	ldr	r3, [sp, #8]
	add	r2, r2, r3
	str	r2, [sp]
	b	.L2242
.L2244:
	ldr	r3, .L2252+20
	movs	r1, #0
	ldr	r0, [r10]
	ldrh	r2, [r3]
	bl	ftl_memset
	b	.L2245
.L2248:
	mov	r8, #-1
	b	.L2240
.L2253:
	.align	2
.L2252:
	.word	.LANCHOR50
	.word	.LANCHOR56
	.word	.LANCHOR202
	.word	.LANCHOR55
	.word	.LANCHOR224
	.word	.LANCHOR57
	.word	.LANCHOR191
	.size	FtlVendorPartWrite, .-FtlVendorPartWrite
	.section	.text.Ftl_save_ext_data,"ax",%progbits
	.align	1
	.global	Ftl_save_ext_data
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	Ftl_save_ext_data, %function
Ftl_save_ext_data:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	ldr	r2, .L2256
	ldr	r3, .L2256+4
	ldr	r1, [r2]
	cmp	r1, r3
	bne	.L2254
	ldr	r3, .L2256+8
	movs	r1, #1
	movs	r0, #0
	str	r3, [r2, #4]
	ldr	r3, .L2256+12
	ldr	r3, [r3]
	str	r3, [r2, #88]
	ldr	r3, .L2256+16
	ldr	r3, [r3]
	str	r3, [r2, #92]
	ldr	r3, .L2256+20
	ldr	r3, [r3]
	str	r3, [r2, #8]
	ldr	r3, .L2256+24
	ldr	r3, [r3]
	str	r3, [r2, #12]
	ldr	r3, .L2256+28
	ldr	r3, [r3]
	str	r3, [r2, #16]
	ldr	r3, .L2256+32
	ldr	r3, [r3]
	str	r3, [r2, #20]
	ldr	r3, .L2256+36
	ldr	r3, [r3]
	str	r3, [r2, #28]
	ldr	r3, .L2256+40
	ldr	r3, [r3]
	str	r3, [r2, #32]
	ldr	r3, .L2256+44
	ldr	r3, [r3]
	str	r3, [r2, #36]
	ldr	r3, .L2256+48
	ldr	r3, [r3]
	str	r3, [r2, #40]
	ldr	r3, .L2256+52
	ldr	r3, [r3]
	str	r3, [r2, #44]
	ldr	r3, .L2256+56
	ldr	r3, [r3]
	str	r3, [r2, #48]
	ldr	r3, .L2256+60
	ldr	r3, [r3]
	str	r3, [r2, #60]
	ldr	r3, .L2256+64
	ldr	r3, [r3]
	str	r3, [r2, #64]
	b	FtlVendorPartWrite
.L2254:
	bx	lr
.L2257:
	.align	2
.L2256:
	.word	.LANCHOR141
	.word	1179929683
	.word	1342177379
	.word	.LANCHOR225
	.word	.LANCHOR226
	.word	.LANCHOR166
	.word	.LANCHOR167
	.word	.LANCHOR171
	.word	.LANCHOR170
	.word	.LANCHOR173
	.word	.LANCHOR81
	.word	.LANCHOR168
	.word	.LANCHOR169
	.word	.LANCHOR174
	.word	.LANCHOR175
	.word	.LANCHOR163
	.word	.LANCHOR162
	.size	Ftl_save_ext_data, .-Ftl_save_ext_data
	.section	.text.FtlEctTblFlush,"ax",%progbits
	.align	1
	.global	FtlEctTblFlush
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	FtlEctTblFlush, %function
FtlEctTblFlush:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r3, lr}
	ldr	r3, .L2265
	ldr	r3, [r3]
	cmp	r3, #0
	beq	.L2263
	ldr	r3, .L2265+4
	ldr	r3, [r3]
	cmp	r3, #39
	ite	hi
	movhi	r3, #32
	movls	r3, #4
.L2259:
	ldr	r1, .L2265+8
	ldrh	r2, [r1]
	cmp	r2, #31
	ittt	ls
	addls	r2, r2, #1
	movls	r3, #1
	strhls	r2, [r1]	@ movhi
	ldr	r2, .L2265+12
	cbnz	r0, .L2261
	ldr	r1, [r2]
	ldr	r0, [r1, #20]
	ldr	r1, [r1, #16]
	add	r3, r3, r0
	cmp	r1, r3
	bcc	.L2262
.L2261:
	ldr	r2, [r2]
	movs	r0, #64
	ldr	r3, [r2, #16]
	str	r3, [r2, #20]
	ldr	r3, .L2265+16
	str	r3, [r2]
	ldr	r3, .L2265+20
	ldrh	r1, [r3]
	lsls	r3, r1, #9
	str	r3, [r2, #12]
	ldr	r3, [r2, #8]
	adds	r3, r3, #1
	str	r3, [r2, #8]
	movs	r3, #0
	str	r3, [r2, #4]
	bl	FtlVendorPartWrite
	bl	Ftl_save_ext_data
.L2262:
	movs	r0, #0
	pop	{r3, pc}
.L2263:
	movs	r3, #32
	b	.L2259
.L2266:
	.align	2
.L2265:
	.word	.LANCHOR104
	.word	.LANCHOR175
	.word	.LANCHOR227
	.word	.LANCHOR199
	.word	1112818501
	.word	.LANCHOR198
	.size	FtlEctTblFlush, .-FtlEctTblFlush
	.section	.text.allocate_new_data_superblock,"ax",%progbits
	.align	1
	.global	allocate_new_data_superblock
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	allocate_new_data_superblock, %function
allocate_new_data_superblock:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	ldr	r3, .L2294
	push	{r4, r5, r6, lr}
	mov	r4, r0
	ldrh	r5, [r0]
	ldrh	r3, [r3]
	cmp	r3, r5
	bcs	.L2268
	ldr	r1, .L2294+4
	movw	r2, #3650
	ldr	r0, .L2294+8
	bl	printf
	ldr	r1, .L2294+12
	ldr	r0, .L2294+16
	bl	printf
.L2268:
	ldr	r3, .L2294+20
	ldr	r3, [r3]
	cmp	r3, #0
	bne	.L2269
	movw	r3, #65535
	cmp	r5, r3
	beq	.L2270
	ldr	r3, .L2294+24
	mov	r0, r5
	ldr	r3, [r3]
	ldrh	r3, [r3, r5, lsl #1]
	cbz	r3, .L2271
	bl	INSERT_DATA_LIST
.L2270:
	movs	r3, #0
	strb	r3, [r4, #8]
	ldr	r3, .L2294+28
	cmp	r4, r3
	beq	.L2272
	ldr	r3, .L2294+32
	ldrh	r2, [r3]
	cmp	r2, #1
	beq	.L2272
	ldr	r3, .L2294+36
	ldrb	r3, [r3]	@ zero_extendqisi2
	cbz	r3, .L2273
.L2272:
	movs	r3, #1
	strb	r3, [r4, #8]
.L2274:
	ldr	r6, .L2294+40
	movw	r2, #65535
	ldrh	r0, [r6]
	cmp	r0, r2
	beq	.L2279
	cmp	r5, r0
	bne	.L2280
	ldr	r3, .L2294+24
	ldr	r3, [r3]
	ldrh	r3, [r3, r0, lsl #1]
	cbz	r3, .L2281
.L2280:
	bl	update_vpc_list
.L2281:
	movw	r3, #65535
	strh	r3, [r6]	@ movhi
.L2279:
	mov	r0, r4
	bl	allocate_data_superblock
	bl	l2p_flush
	movs	r0, #0
	bl	FtlEctTblFlush
	bl	FtlVpcTblFlush
.L2269:
	movs	r0, #0
	pop	{r4, r5, r6, pc}
.L2271:
	bl	INSERT_FREE_LIST
	b	.L2270
.L2273:
	ldr	r3, .L2294+44
	cmp	r4, r3
	bne	.L2274
	cmp	r2, #3
	beq	.L2276
	ldr	r2, .L2294+48
	ldr	r2, [r2]
	cmp	r2, #1
	bne	.L2277
.L2276:
	movs	r2, #1
	strb	r2, [r3, #8]
.L2277:
	ldr	r2, .L2294+52
	ldr	r2, [r2]
	cmp	r2, #0
	beq	.L2274
	ldr	r2, .L2294+56
	ldr	r2, [r2]
	cmp	r2, #39
	itt	ls
	movls	r2, #1
	strbls	r2, [r3, #8]
	b	.L2274
.L2295:
	.align	2
.L2294:
	.word	.LANCHOR40
	.word	.LANCHOR228
	.word	.LC5
	.word	.LC6
	.word	.LC7
	.word	.LANCHOR78
	.word	.LANCHOR85
	.word	.LANCHOR94
	.word	.LANCHOR44
	.word	.LANCHOR16
	.word	.LANCHOR136
	.word	.LANCHOR93
	.word	.LANCHOR163
	.word	.LANCHOR104
	.word	.LANCHOR175
	.size	allocate_new_data_superblock, .-allocate_new_data_superblock
	.section	.text.FtlVendorPartRead,"ax",%progbits
	.align	1
	.global	FtlVendorPartRead
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	FtlVendorPartRead, %function
FtlVendorPartRead:
	@ args = 0, pretend = 0, frame = 56
	@ frame_needed = 0, uses_anonymous_args = 0
	ldr	r3, .L2306
	push	{r4, r5, r6, r7, r8, r10, fp, lr}
	mov	r10, r2
	adds	r2, r0, r1
	sub	sp, sp, #56
	mov	r7, r0
	mov	r6, r1
	ldrh	r3, [r3]
	cmp	r2, r3
	bhi	.L2305
	ldr	r3, .L2306+4
	mov	r8, #0
	ldr	fp, .L2306+28
	ldrh	r5, [r3]
	lsr	r5, r0, r5
	lsls	r3, r5, #2
	str	r3, [sp]
.L2298:
	cbnz	r6, .L2304
.L2296:
	mov	r0, r8
	add	sp, sp, #56
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r10, fp, pc}
.L2304:
	ldr	r3, .L2306+8
	mov	r0, r7
	ldr	r2, [sp]
	ldr	r3, [r3]
	ldr	r3, [r3, r2]
	ldr	r2, .L2306+12
	str	r3, [sp, #8]
	ldrh	r4, [r2]
	mov	r1, r4
	bl	__aeabi_uidivmod
	subs	r4, r4, r1
	ldr	r3, [sp, #8]
	uxth	r4, r4
	str	r1, [sp, #4]
	cmp	r6, r4
	it	cc
	uxthcc	r4, r6
	lsls	r2, r4, #9
	str	r2, [sp, #8]
	cmp	r3, #0
	beq	.L2300
	ldr	r2, [fp]
	add	r0, sp, #20
	str	r3, [sp, #24]
	str	r3, [sp, #12]
	str	r2, [sp, #28]
	movs	r2, #0
	str	r2, [sp, #32]
	movs	r2, #1
	mov	r1, r2
	bl	FlashReadPages
	ldr	r2, [sp, #20]
	ldr	r3, [sp, #12]
	adds	r2, r2, #1
	ldr	r2, .L2306+16
	it	eq
	moveq	r8, #-1
	ldr	r2, [r2]
	cmp	r2, #256
	bne	.L2302
	mov	r2, r3
	mov	r1, r5
	ldr	r0, .L2306+20
	bl	printf
	ldr	r2, [fp]
	mov	r1, r5
	ldr	r0, .L2306+24
	bl	FtlMapWritePage
.L2302:
	ldr	r1, [fp]
	lsls	r2, r4, #9
	ldr	r3, [sp, #4]
	mov	r0, r10
	add	r1, r1, r3, lsl #9
	bl	ftl_memcpy
.L2303:
	ldr	r3, [sp, #8]
	adds	r5, r5, #1
	subs	r6, r6, r4
	add	r7, r7, r4
	add	r10, r10, r3
	ldr	r3, [sp]
	adds	r3, r3, #4
	str	r3, [sp]
	b	.L2298
.L2300:
	lsls	r2, r4, #9
	mov	r1, r3
	mov	r0, r10
	bl	ftl_memset
	b	.L2303
.L2305:
	mov	r8, #-1
	b	.L2296
.L2307:
	.align	2
.L2306:
	.word	.LANCHOR50
	.word	.LANCHOR56
	.word	.LANCHOR202
	.word	.LANCHOR55
	.word	.LANCHOR211
	.word	.LC44
	.word	.LANCHOR224
	.word	.LANCHOR191
	.size	FtlVendorPartRead, .-FtlVendorPartRead
	.section	.text.FtlLoadEctTbl,"ax",%progbits
	.align	1
	.global	FtlLoadEctTbl
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	FtlLoadEctTbl, %function
FtlLoadEctTbl:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r3, r4, r5, lr}
	movs	r0, #64
	ldr	r4, .L2310
	ldr	r5, .L2310+4
	ldr	r2, [r4]
	ldrh	r1, [r5]
	bl	FtlVendorPartRead
	ldr	r3, [r4]
	ldr	r2, [r3]
	ldr	r3, .L2310+8
	cmp	r2, r3
	beq	.L2309
	ldr	r1, .L2310+12
	ldr	r0, .L2310+16
	bl	printf
	ldrh	r2, [r5]
	movs	r1, #0
	ldr	r0, [r4]
	lsls	r2, r2, #9
	bl	ftl_memset
.L2309:
	movs	r0, #0
	pop	{r3, r4, r5, pc}
.L2311:
	.align	2
.L2310:
	.word	.LANCHOR199
	.word	.LANCHOR198
	.word	1112818501
	.word	.LC45
	.word	.LC7
	.size	FtlLoadEctTbl, .-FtlLoadEctTbl
	.section	.text.Ftl_load_ext_data,"ax",%progbits
	.align	1
	.global	Ftl_load_ext_data
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	Ftl_load_ext_data, %function
Ftl_load_ext_data:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r3, r4, r5, lr}
	movs	r1, #1
	ldr	r4, .L2317
	movs	r0, #0
	ldr	r5, .L2317+4
	mov	r2, r4
	bl	FtlVendorPartRead
	ldr	r3, [r4]
	cmp	r3, r5
	beq	.L2313
	mov	r2, #512
	movs	r1, #0
	mov	r0, r4
	bl	ftl_memset
	str	r5, [r4]
.L2313:
	ldr	r3, [r4]
	cmp	r3, r5
	ldr	r5, .L2317+8
	bne	.L2314
	ldr	r2, [r4, #88]
	ldr	r3, .L2317+12
	str	r2, [r3]
	ldr	r2, [r4, #92]
	ldr	r3, .L2317+16
	str	r2, [r3]
	ldr	r2, [r4, #8]
	ldr	r3, .L2317+20
	str	r2, [r3]
	ldr	r2, [r4, #12]
	ldr	r3, .L2317+24
	str	r2, [r3]
	ldr	r2, [r4, #16]
	ldr	r3, .L2317+28
	str	r2, [r3]
	ldr	r2, [r4, #20]
	ldr	r3, .L2317+32
	str	r2, [r3]
	ldr	r3, [r4, #28]
	ldr	r2, [r4, #32]
	str	r3, [r5]
	ldr	r3, .L2317+36
	str	r2, [r3]
	ldr	r2, [r4, #36]
	ldr	r3, .L2317+40
	str	r2, [r3]
	ldr	r2, [r4, #40]
	ldr	r3, .L2317+44
	str	r2, [r3]
	ldr	r2, [r4, #44]
	ldr	r3, .L2317+48
	str	r2, [r3]
	ldr	r2, [r4, #48]
	ldr	r3, .L2317+52
	str	r2, [r3]
	ldr	r2, [r4, #60]
	ldr	r3, .L2317+56
	str	r2, [r3]
.L2314:
	ldr	r2, .L2317+60
	movs	r3, #0
	ldr	r1, [r4, #68]
	str	r3, [r2]
	ldr	r2, .L2317+64
	cmp	r1, r2
	bne	.L2315
	ldr	r2, .L2317+68
	ldrb	r2, [r2]	@ zero_extendqisi2
	cbz	r2, .L2316
	str	r3, [r4, #68]
	bl	Ftl_save_ext_data
.L2315:
	ldr	r3, .L2317+72
	ldr	r1, .L2317+76
	ldrh	r2, [r3]
	ldr	r3, .L2317+80
	ldrh	r1, [r1]
	ldr	r0, [r3]
	ldr	r3, [r5]
	mla	r0, r0, r2, r3
	bl	__aeabi_uidiv
	ldr	r3, .L2317+84
	str	r0, [r3]
	pop	{r3, r4, r5, pc}
.L2316:
	ldr	r3, .L2317+88
	movs	r2, #1
	ldr	r1, .L2317+92
	ldr	r0, .L2317+96
	str	r2, [r3]
	bl	printf
	b	.L2315
.L2318:
	.align	2
.L2317:
	.word	.LANCHOR141
	.word	1179929683
	.word	.LANCHOR173
	.word	.LANCHOR225
	.word	.LANCHOR226
	.word	.LANCHOR166
	.word	.LANCHOR167
	.word	.LANCHOR171
	.word	.LANCHOR170
	.word	.LANCHOR81
	.word	.LANCHOR168
	.word	.LANCHOR169
	.word	.LANCHOR174
	.word	.LANCHOR175
	.word	.LANCHOR163
	.word	.LANCHOR162
	.word	305432421
	.word	.LANCHOR16
	.word	.LANCHOR48
	.word	.LANCHOR40
	.word	.LANCHOR172
	.word	.LANCHOR214
	.word	.LANCHOR104
	.word	.LC46
	.word	.LC7
	.size	Ftl_load_ext_data, .-Ftl_load_ext_data
	.section	.text.FtlMapBlkWriteDumpData,"ax",%progbits
	.align	1
	.global	FtlMapBlkWriteDumpData
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	FtlMapBlkWriteDumpData, %function
FtlMapBlkWriteDumpData:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r3, r4, r5, r6, r7, r8, r10, lr}
	mov	r4, r0
	ldr	r3, [r0, #36]
	cmp	r3, #0
	beq	.L2319
	movs	r3, #0
	ldrh	r6, [r0, #6]
	str	r3, [r0, #36]
	ldr	r3, .L2333
	ldr	r10, [r0, #24]
	ldr	r3, [r3]
	cmp	r3, #0
	bne	.L2319
	ldr	r3, .L2333+4
	ldr	r5, .L2333+8
	ldr	r3, [r3]
	mov	r7, r5
	str	r3, [r5, #8]
	ldr	r3, .L2333+12
	ldr	r8, [r3]
	ldrh	r3, [r0, #2]
	str	r8, [r5, #12]
	cbz	r3, .L2323
	ldr	r2, .L2333+16
	ldrh	r2, [r2]
	subs	r2, r2, #1
	cmp	r3, r2
	bge	.L2323
	ldrh	r2, [r0]
	movw	r1, #65535
	cmp	r2, r1
	beq	.L2323
	ldr	r1, [r0, #12]
	subs	r3, r3, #1
	mov	r0, r5
	ldrh	r2, [r1, r2, lsl #1]
	orr	r3, r3, r2, lsl #10
	movs	r2, #1
	mov	r1, r2
	str	r3, [r5, #4]
	bl	FlashReadPages
	ldr	r3, [r5]
	adds	r3, r3, #1
	beq	.L2323
	ldr	r3, [r4, #24]
	ldrh	r1, [r8, #8]
	ldr	r2, [r3, r1, lsl #2]
	ldr	r3, [r5, #4]
	cmp	r2, r3
	bne	.L2323
	ldr	r2, [r5, #8]
.L2332:
	mov	r0, r4
	pop	{r3, r4, r5, r6, r7, r8, r10, lr}
	b	FtlMapWritePage
.L2323:
	subs	r6, r6, #1
	uxth	r6, r6
	ldr	r3, [r10, r6, lsl #2]
	str	r3, [r7, #4]
	cbz	r3, .L2324
	movs	r2, #1
	ldr	r0, .L2333+8
	mov	r1, r2
	bl	FlashReadPages
.L2325:
	ldr	r2, [r7, #8]
	mov	r1, r6
	b	.L2332
.L2324:
	ldr	r3, .L2333+20
	movs	r1, #255
	ldr	r0, [r7, #8]
	ldrh	r2, [r3]
	bl	ftl_memset
	b	.L2325
.L2319:
	pop	{r3, r4, r5, r6, r7, r8, r10, pc}
.L2334:
	.align	2
.L2333:
	.word	.LANCHOR78
	.word	.LANCHOR190
	.word	.LANCHOR211
	.word	.LANCHOR195
	.word	.LANCHOR53
	.word	.LANCHOR57
	.size	FtlMapBlkWriteDumpData, .-FtlMapBlkWriteDumpData
	.section	.text.FtlScanSysBlk,"ax",%progbits
	.align	1
	.global	FtlScanSysBlk
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	FtlScanSysBlk, %function
FtlScanSysBlk:
	@ args = 0, pretend = 0, frame = 32
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, r8, r10, fp, lr}
	movs	r4, #0
	ldr	r5, .L2417
	sub	sp, sp, #32
	mov	r1, r4
	ldr	r3, .L2417+4
	ldr	r2, [r5]
	ldr	r6, .L2417+8
	strh	r4, [r3]	@ movhi
	ldr	r3, .L2417+12
	lsls	r2, r2, #2
	strh	r4, [r6]	@ movhi
	ldr	r7, .L2417+16
	ldr	r0, [r3]
	bl	ftl_memset
	ldr	r2, [r5]
	mov	r1, r4
	ldr	r3, .L2417+20
	lsls	r2, r2, #1
	ldr	r0, [r3]
	bl	ftl_memset
	ldrh	r2, [r7]
	mov	r1, r4
	ldr	r3, .L2417+24
	lsls	r2, r2, #2
	ldr	r0, [r3]
	bl	ftl_memset
	ldrh	r2, [r7]
	mov	r1, r4
	ldr	r3, .L2417+28
	lsls	r2, r2, #1
	ldr	r0, [r3]
	bl	ftl_memset
	movs	r2, #16
	movs	r1, #255
	ldr	r0, .L2417+32
	bl	ftl_memset
	ldr	r3, .L2417+36
	str	r6, [sp, #12]
	str	r5, [sp, #16]
	ldrh	r3, [r3]
	str	r3, [sp, #4]
.L2336:
	ldr	r3, .L2417+40
	ldr	r2, [sp, #4]
	ldrh	r3, [r3]
	cmp	r3, r2
	bls	.L2378
	ldr	r3, .L2417+44
	movs	r5, #0
	ldr	r1, .L2417+48
	mov	fp, r5
	movs	r7, #36
	ldrh	r8, [r3]
	ldr	r3, .L2417+52
	ldr	r2, [r1]
	ldr	r1, .L2417+56
	ldr	r6, [r3]
	ldr	r3, .L2417+60
	str	r2, [sp, #8]
	ldrh	r10, [r1]
	ldr	r3, [r3]
	ldr	r2, .L2417+64
	b	.L2379
.L2338:
	ldrb	r0, [r2, r5]	@ zero_extendqisi2
	ldr	r1, [sp, #4]
	str	r3, [sp, #28]
	str	r2, [sp, #24]
	bl	V2P_block
	str	r0, [sp, #20]
	bl	FtlBbmIsBadBlock
	ldr	r2, [sp, #24]
	ldr	r3, [sp, #28]
	cbnz	r0, .L2337
	ldr	r1, [sp, #20]
	mla	r0, r7, fp, r6
	ldr	r4, [sp, #8]
	lsls	r1, r1, #10
	str	r3, [r0, #8]
	str	r1, [r0, #4]
	mul	r1, r10, fp
	bic	r1, r1, #3
	add	r1, r1, r4
	str	r1, [r0, #12]
	add	r1, fp, #1
	uxth	fp, r1
.L2337:
	adds	r5, r5, #1
.L2379:
	uxth	r1, r5
	cmp	r8, r1
	bhi	.L2338
	cmp	fp, #0
	bne	.L2339
.L2377:
	ldr	r3, [sp, #4]
	adds	r3, r3, #1
	uxth	r3, r3
	str	r3, [sp, #4]
	b	.L2336
.L2339:
	movs	r7, #0
	movs	r2, #1
	mov	r1, fp
	mov	r0, r6
	bl	FlashReadPages
.L2340:
	uxth	r3, r7
	cmp	fp, r3
	bls	.L2377
	ldr	r3, .L2417+52
	mov	r8, #36
	mul	r8, r8, r7
	ldr	r3, [r3]
	add	r2, r3, r8
	ldr	r3, [r3, r8]
	ldr	r5, [r2, #4]
	ldr	r6, [r2, #12]
	adds	r3, r3, #1
	ubfx	r5, r5, #10, #16
	bne	.L2343
	mov	r10, #16
.L2345:
	ldr	r3, .L2417+52
	movs	r2, #1
	mov	r1, r2
	ldr	r0, [r3]
	add	r0, r0, r8
	ldr	r3, [r0, #4]
	adds	r3, r3, #1
	str	r3, [r0, #4]
	bl	FlashReadPages
	ldrh	r2, [r6]
	movw	r3, #65535
	cmp	r2, r3
	ldr	r3, .L2417+52
	ldr	r3, [r3]
	bne	.L2342
	mov	r2, #-1
	str	r2, [r3, r8]
	ldr	r3, .L2417+52
	ldr	r3, [r3]
	ldr	r3, [r3, r8]
	cmp	r3, r2
	beq	.L2344
.L2343:
	ldr	r3, .L2417+68
	ldr	r2, [r3]
	ldr	r3, [r6, #4]
	adds	r1, r2, #1
	beq	.L2346
	cmp	r2, r3
	bhi	.L2347
.L2346:
	adds	r2, r3, #1
	ittt	ne
	ldrne	r1, .L2417+68
	addne	r2, r3, #1
	strne	r2, [r1]
.L2347:
	ldrh	r2, [r6]
	movw	r1, #61604
	cmp	r2, r1
	beq	.L2349
	bhi	.L2350
	movw	r3, #61574
	cmp	r2, r3
	beq	.L2351
.L2348:
	adds	r7, r7, #1
	b	.L2340
.L2342:
	ldr	r3, [r3, r8]
	adds	r3, r3, #1
	bne	.L2343
	add	r10, r10, #-1
	uxth	r10, r10
	cmp	r10, #0
	bne	.L2345
.L2344:
	ldr	r3, .L2417+72
	ldrb	r1, [r3]	@ zero_extendqisi2
	cbnz	r1, .L2416
.L2375:
	mov	r0, r5
	bl	FtlFreeSysBlkQueueIn
	b	.L2348
.L2350:
	movw	r3, #61634
	cmp	r2, r3
	beq	.L2352
	movw	r3, #65535
	cmp	r2, r3
	bne	.L2348
.L2416:
	movs	r1, #0
	b	.L2375
.L2352:
	ldr	r3, .L2417+8
	ldrh	r2, [r3]
	ldr	r3, .L2417
	ldr	r3, [r3]
	cmp	r2, r3
	bls	.L2354
	ldr	r1, .L2417+76
	movw	r2, #1469
	ldr	r0, .L2417+80
	bl	printf
	ldr	r1, .L2417+84
	ldr	r0, .L2417+88
	bl	printf
.L2354:
	ldr	r3, [sp, #16]
	ldr	r2, [sp, #12]
	ldr	r1, [r3]
	ldrh	r0, [r2]
	ldr	r2, .L2417+12
	uxth	r10, r1
	ldr	ip, [r2]
	add	r3, r10, #-1
	sub	r10, r10, r0
	add	r10, r10, #-1
	sxth	r3, r3
	sxth	r10, r10
.L2355:
	cmp	r3, r10
	bgt	.L2361
	cmp	r3, #0
	bge	.L2394
	b	.L2348
.L2361:
	ldr	r2, [ip, r3, lsl #2]
	add	r8, ip, r3, lsl #2
	ldr	r4, [r6, #4]
	cmp	r4, r2
	bls	.L2356
	ldr	r2, [ip]
	cbnz	r2, .L2357
	cmp	r1, r0
	ittt	ne
	ldrne	r2, .L2417+8
	addne	r0, r0, #1
	strhne	r0, [r2]	@ movhi
.L2357:
	ldr	r2, .L2417+20
	uxth	r10, r3
	ldr	r0, [r2]
	movs	r2, #0
.L2358:
	uxth	lr, r2
	sxth	r1, r2
	cmp	r10, lr
	bhi	.L2359
	ldr	r2, [r6, #4]
	cmp	r3, #0
	str	r2, [r8]
	strh	r5, [r0, r3, lsl #1]	@ movhi
	blt	.L2348
	ldr	r2, .L2417+8
	ldrh	r0, [r2]
	ldr	r2, .L2417
	ldr	r2, [r2]
	subs	r2, r2, r0
	subs	r2, r2, #1
	sxth	r2, r2
	cmp	r3, r2
	bgt	.L2348
.L2394:
	ldr	r2, .L2417+8
	adds	r0, r0, #1
	strh	r0, [r2]	@ movhi
	ldr	r2, [r6, #4]
	str	r2, [ip, r3, lsl #2]
	ldr	r2, .L2417+20
.L2414:
	ldr	r2, [r2]
	strh	r5, [r2, r3, lsl #1]	@ movhi
	b	.L2348
.L2359:
	add	lr, ip, r1, lsl #2
	adds	r2, r2, #1
	ldr	r4, [lr, #4]
	add	lr, r0, r1, lsl #1
	ldrh	lr, [lr, #2]
	str	r4, [ip, r1, lsl #2]
	strh	lr, [r0, r1, lsl #1]	@ movhi
	b	.L2358
.L2356:
	subs	r3, r3, #1
	sxth	r3, r3
	b	.L2355
.L2418:
	.align	2
.L2417:
	.word	.LANCHOR64
	.word	.LANCHOR70
	.word	.LANCHOR131
	.word	.LANCHOR133
	.word	.LANCHOR61
	.word	.LANCHOR132
	.word	.LANCHOR201
	.word	.LANCHOR71
	.word	.LANCHOR218
	.word	.LANCHOR40
	.word	.LANCHOR41
	.word	.LANCHOR38
	.word	.LANCHOR108
	.word	.LANCHOR186
	.word	.LANCHOR58
	.word	.LANCHOR107
	.word	.LANCHOR47
	.word	.LANCHOR164
	.word	.LANCHOR16
	.word	.LANCHOR229
	.word	.LC5
	.word	.LC6
	.word	.LC7
.L2351:
	ldr	r8, .L2419+20
	ldr	r10, .L2419+28
	ldrh	r2, [r8]
	ldrh	r3, [r10]
	cmp	r2, r3
	bls	.L2364
	ldr	r1, .L2419
	movw	r2, #1513
	ldr	r0, .L2419+4
	bl	printf
	ldr	r1, .L2419+8
	ldr	r0, .L2419+12
	bl	printf
.L2364:
	ldr	r2, .L2419+16
	ldrh	lr, [r10]
	ldrh	ip, [r8]
	ldr	r0, [r2]
	add	r10, lr, #-1
	sxth	r3, r10
	sub	r10, r10, ip
.L2365:
	cmp	r3, r10
	ble	.L2370
	ldr	r1, [r6, #4]
	add	r8, r0, r3, lsl #2
	ldr	r2, [r0, r3, lsl #2]
	cmp	r1, r2
	bls	.L2366
	ldr	r2, [r0]
	cbnz	r2, .L2367
	cmp	lr, ip
	ittt	ne
	ldrne	r2, .L2419+20
	addne	ip, ip, #1
	strhne	ip, [r2]	@ movhi
.L2367:
	ldr	r2, .L2419+24
	uxth	r10, r3
	ldr	ip, [r2]
	movs	r2, #0
.L2368:
	uxth	lr, r2
	sxth	r1, r2
	cmp	r10, lr
	bhi	.L2369
	ldr	r2, [r6, #4]
	str	r2, [r8]
	strh	r5, [ip, r3, lsl #1]	@ movhi
.L2370:
	cmp	r3, #0
	blt	.L2348
	ldr	r2, .L2419+28
	ldr	ip, .L2419+20
	ldrh	r2, [r2]
	ldrh	r1, [ip]
	subs	r2, r2, #1
	subs	r2, r2, r1
	sxth	r2, r2
	cmp	r3, r2
	bgt	.L2348
	ldr	r2, [r6, #4]
	adds	r1, r1, #1
	strh	r1, [ip]	@ movhi
	str	r2, [r0, r3, lsl #2]
	ldr	r2, .L2419+24
	b	.L2414
.L2369:
	add	lr, r0, r1, lsl #2
	adds	r2, r2, #1
	ldr	r4, [lr, #4]
	add	lr, ip, r1, lsl #1
	ldrh	lr, [lr, #2]
	str	r4, [r0, r1, lsl #2]
	strh	lr, [ip, r1, lsl #1]	@ movhi
	b	.L2368
.L2366:
	subs	r3, r3, #1
	sxth	r3, r3
	b	.L2365
.L2349:
	ldr	r8, .L2419+48
	movw	r2, #65535
	ldrh	r1, [r8]
	cmp	r1, r2
	bne	.L2372
.L2415:
	strh	r5, [r8]	@ movhi
	str	r3, [r8, #8]
	b	.L2348
.L2372:
	ldrh	r0, [r8, #4]
	cmp	r0, r2
	beq	.L2373
	movs	r1, #1
	bl	FtlFreeSysBlkQueueIn
.L2373:
	ldr	r3, [r6, #4]
	ldr	r2, [r8, #8]
	cmp	r2, r3
	bcs	.L2374
	ldrh	r2, [r8]
	strh	r2, [r8, #4]	@ movhi
	b	.L2415
.L2374:
	strh	r5, [r8, #4]	@ movhi
	b	.L2348
.L2378:
	ldr	r3, .L2419+32
	ldr	r2, [r3]
	ldrh	r3, [r2]
	cbz	r3, .L2380
.L2383:
	ldr	r3, .L2419+24
	ldr	r4, [r3]
	ldrh	r2, [r4]
	cmp	r2, #0
	beq	.L2381
.L2382:
	ldr	r3, .L2419+36
	ldrh	r2, [r3]
	ldr	r3, .L2419+40
	ldr	r3, [r3]
	cmp	r2, r3
	bls	.L2413
	ldr	r1, .L2419
	movw	r2, #1631
	ldr	r0, .L2419+4
	bl	printf
	ldr	r1, .L2419+8
	ldr	r0, .L2419+12
	bl	printf
.L2413:
	movs	r0, #0
	add	sp, sp, #32
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r10, fp, pc}
.L2380:
	ldr	r1, .L2419+36
	ldrh	r1, [r1]
	cmp	r1, #0
	beq	.L2383
	ldr	r5, .L2419+40
	ldr	r0, [r5]
.L2384:
	sxth	r1, r3
	cmp	r1, r0
	bcs	.L2383
	ldrh	r4, [r2, r1, lsl #1]
	adds	r3, r3, #1
	cmp	r4, #0
	beq	.L2384
	ldr	r3, .L2419+44
	movs	r6, #0
	ldr	r0, [r3]
	mov	r3, r1
.L2385:
	ldr	r4, [r5]
	cmp	r3, r4
	bcs	.L2383
	ldrh	r7, [r2, r3, lsl #1]
	subs	r4, r3, r1
	strh	r7, [r2, r4, lsl #1]	@ movhi
	ldr	r7, [r0, r3, lsl #2]
	str	r7, [r0, r4, lsl #2]
	strh	r6, [r2, r3, lsl #1]	@ movhi
	adds	r3, r3, #1
	sxth	r3, r3
	b	.L2385
.L2381:
	ldr	r3, .L2419+20
	ldrh	r3, [r3]
	cmp	r3, #0
	beq	.L2382
	ldr	r5, .L2419+28
	ldrh	r1, [r5]
.L2390:
	sxth	r3, r2
	cmp	r3, r1
	mov	r6, r3
	bge	.L2382
	ldrh	r0, [r4, r3, lsl #1]
	adds	r2, r2, #1
	cmp	r0, #0
	beq	.L2390
	ldr	r2, .L2419+16
	movs	r0, #0
	ldr	r2, [r2]
.L2391:
	ldrh	r1, [r5]
	cmp	r3, r1
	bge	.L2382
	ldrh	r7, [r4, r3, lsl #1]
	subs	r1, r3, r6
	strh	r7, [r4, r1, lsl #1]	@ movhi
	ldr	r7, [r2, r3, lsl #2]
	str	r7, [r2, r1, lsl #2]
	adds	r1, r3, #1
	strh	r0, [r4, r3, lsl #1]	@ movhi
	sxth	r3, r1
	b	.L2391
.L2420:
	.align	2
.L2419:
	.word	.LANCHOR229
	.word	.LC5
	.word	.LC6
	.word	.LC7
	.word	.LANCHOR201
	.word	.LANCHOR70
	.word	.LANCHOR71
	.word	.LANCHOR61
	.word	.LANCHOR132
	.word	.LANCHOR131
	.word	.LANCHOR64
	.word	.LANCHOR133
	.word	.LANCHOR218
	.size	FtlScanSysBlk, .-FtlScanSysBlk
	.section	.text.FtlLoadSysInfo,"ax",%progbits
	.align	1
	.global	FtlLoadSysInfo
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	FtlLoadSysInfo, %function
FtlLoadSysInfo:
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, r8, r10, fp, lr}
	movs	r1, #0
	ldr	r7, .L2455
	sub	sp, sp, #40
	ldr	r6, .L2455+4
	ldr	r3, [r7]
	ldr	r4, .L2455+8
	ldr	r8, .L2455+52
	ldrh	r2, [r6]
	ldr	r5, .L2455+12
	str	r3, [r4, #8]
	ldr	r3, [r8]
	lsls	r2, r2, #1
	ldr	r0, [r5]
	str	r3, [r4, #12]
	bl	ftl_memset
	ldr	r3, .L2455+16
	movw	r2, #65535
	str	r8, [sp, #24]
	str	r5, [sp, #28]
	ldrh	r0, [r3]
	mov	fp, r3
	cmp	r0, r2
	bne	.L2422
.L2434:
	mov	r0, #-1
.L2421:
	add	sp, sp, #40
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r10, fp, pc}
.L2422:
	movs	r1, #1
	bl	FtlGetLastWrittenPage
	ldrsh	r10, [fp]
	sxth	r5, r0
	adds	r0, r0, #1
	strh	r0, [fp, #2]	@ movhi
.L2424:
	cmp	r5, #0
	bge	.L2430
	movw	r2, #1708
	ldr	r1, .L2455+20
	ldr	r0, .L2455+24
	bl	printf
	ldr	r1, .L2455+28
	ldr	r0, .L2455+32
	bl	printf
	b	.L2429
.L2430:
	orr	r3, r5, r10, lsl #10
	movs	r2, #1
	mov	r1, r2
	ldr	r0, .L2455+8
	str	r3, [r4, #4]
	ldr	r3, [r7]
	str	r3, [r4, #8]
	bl	FlashReadPages
	ldr	r3, .L2455+36
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L2425
	ldr	r8, [r4, #12]
	ldr	r3, [r8, #12]
	str	r3, [sp, #36]
	cmp	r3, #0
	beq	.L2425
	ldr	r2, [r4, #8]
	ldr	r1, .L2455+40
	mov	r0, r2
	str	r2, [sp, #32]
	ldrh	r1, [r1]
	bl	js_hash
	ldr	r3, [sp, #36]
	cmp	r3, r0
	beq	.L2425
	cmp	r5, #0
	bne	.L2426
	ldr	r2, .L2455+16
	ldrh	r1, [r2, #4]
	cmp	r10, r1
	beq	.L2426
	ldrh	r1, [r2]
	ldr	r2, [sp, #32]
	ldr	r0, .L2455+44
	ldr	r2, [r2]
	str	r3, [sp, #12]
	str	r2, [sp, #16]
	ldr	r3, [r8, #8]
	str	r3, [sp, #8]
	ldr	r3, [r8, #4]
	str	r3, [sp, #4]
	ldr	r3, [r8]
	str	r3, [sp]
	ldm	r4, {r2, r3}
	bl	printf
	ldr	r3, .L2455+16
	ldrsh	r10, [r3, #4]
	ldr	r3, .L2455+48
	ldrh	r5, [r3]
.L2428:
	subs	r5, r5, #1
	sxth	r5, r5
	b	.L2424
.L2456:
	.align	2
.L2455:
	.word	.LANCHOR189
	.word	.LANCHOR40
	.word	.LANCHOR211
	.word	.LANCHOR85
	.word	.LANCHOR218
	.word	.LANCHOR230
	.word	.LC5
	.word	.LC6
	.word	.LC7
	.word	.LANCHOR2
	.word	.LANCHOR57
	.word	.LC47
	.word	.LANCHOR53
	.word	.LANCHOR195
.L2426:
	mov	r3, #-1
	str	r3, [r4]
.L2425:
	ldr	r3, [r4]
	adds	r3, r3, #1
	beq	.L2428
	ldr	r3, [r7]
	ldr	r2, .L2457
	ldr	r3, [r3]
	cmp	r3, r2
	bne	.L2428
	ldr	r3, [sp, #24]
	ldr	r3, [r3]
	ldrh	r2, [r3]
	movw	r3, #61604
	cmp	r2, r3
	bne	.L2428
.L2429:
	ldr	r2, .L2457+4
	ldrh	r3, [r6]
	ldrh	r2, [r2]
	adds	r3, r3, #24
	cmp	r2, r3, lsl #1
	bcs	.L2432
	ldr	r1, .L2457+8
	movw	r2, #1710
	ldr	r0, .L2457+12
	bl	printf
	ldr	r1, .L2457+16
	ldr	r0, .L2457+20
	bl	printf
.L2432:
	movs	r2, #48
	ldr	r1, [r4, #8]
	ldr	r0, .L2457+24
	bl	ftl_memcpy
	ldrh	r2, [r6]
	ldr	r3, [sp, #28]
	ldr	r1, [r4, #8]
	lsls	r2, r2, #1
	ldr	r0, [r3]
	adds	r1, r1, #48
	bl	ftl_memcpy
	ldrh	r1, [r6]
	ldr	r3, [r4, #8]
	lsrs	r2, r1, #3
	lsls	r1, r1, #1
	adds	r1, r1, #51
	adds	r2, r2, #4
	bic	r1, r1, #3
	add	r1, r1, r3
	ldr	r3, .L2457+28
	ldr	r0, [r3]
	bl	ftl_memcpy
	ldr	r3, .L2457+32
	ldrh	r3, [r3]
	cbz	r3, .L2433
	ldrh	r1, [r6]
	ldr	r3, .L2457+36
	ldrh	r2, [r3]
	lsrs	r3, r1, #3
	add	r3, r3, r1, lsl #1
	ldr	r1, [r4, #8]
	adds	r3, r3, #52
	lsls	r2, r2, #2
	ubfx	r3, r3, #2, #14
	add	r1, r1, r3, lsl #2
	ldr	r3, .L2457+40
	ldr	r0, [r3]
	bl	ftl_memcpy
.L2433:
	ldr	r4, .L2457+24
	ldr	r3, .L2457
	ldr	r2, [r4]
	cmp	r2, r3
	bne	.L2434
	ldr	r3, .L2457+44
	ldrb	r2, [r4, #10]	@ zero_extendqisi2
	ldrh	r5, [r4, #8]
	ldrh	r3, [r3]
	strh	r5, [fp, #6]	@ movhi
	cmp	r2, r3
	bne	.L2434
	ldr	r3, .L2457+48
	ldr	r2, .L2457+52
	str	r5, [r3]
	ldr	r3, .L2457+56
	ldrh	r3, [r3]
	muls	r3, r5, r3
	str	r3, [r2]
	ldr	r2, .L2457+60
	ldrh	r2, [r2]
	muls	r3, r2, r3
	ldr	r2, .L2457+64
	str	r3, [r2]
	ldr	r3, .L2457+68
	ldr	r6, [r3]
	ldr	r3, .L2457+72
	ldrh	r0, [r3, #6]
	ldr	r3, .L2457+76
	subs	r0, r6, r0
	ldrh	r1, [r3]
	subs	r0, r0, r5
	bl	__aeabi_uidiv
	ldr	r3, .L2457+80
	cmp	r5, r6
	strh	r0, [r3]	@ movhi
	bls	.L2435
	ldr	r1, .L2457+8
	movw	r2, #1739
	ldr	r0, .L2457+12
	bl	printf
	ldr	r1, .L2457+16
	ldr	r0, .L2457+20
	bl	printf
.L2435:
	ldrh	r2, [r4, #16]
	ldr	r3, .L2457+84
	ldrh	ip, [r4, #14]
	ldr	r7, .L2457+88
	lsrs	r1, r2, #6
	and	r2, r2, #63
	strb	r2, [r3, #6]
	ldrb	r2, [r4, #11]	@ zero_extendqisi2
	strh	r1, [r3, #2]	@ movhi
	ldr	r1, .L2457+92
	strb	r2, [r3, #8]
	ldrh	r2, [r4, #18]
	strh	ip, [r3]	@ movhi
	movw	r3, #65535
	strh	r3, [r7]	@ movhi
	movs	r3, #0
	strh	r2, [r1]	@ movhi
	ldrh	r2, [r4, #20]
	strh	r3, [r7, #2]	@ movhi
	strb	r3, [r7, #6]
	strb	r3, [r7, #8]
	lsrs	r5, r2, #6
	and	r2, r2, #63
	strb	r2, [r1, #6]
	ldrb	r2, [r4, #12]	@ zero_extendqisi2
	strh	r5, [r1, #2]	@ movhi
	ldrh	r5, [r4, #22]
	strb	r2, [r1, #8]
	ldr	r2, .L2457+96
	strh	r5, [r2]	@ movhi
	ldrh	r5, [r4, #24]
	lsrs	r6, r5, #6
	and	r5, r5, #63
	strb	r5, [r2, #6]
	ldrb	r5, [r4, #13]	@ zero_extendqisi2
	strh	r6, [r2, #2]	@ movhi
	ldr	r6, [r4, #32]
	strb	r5, [r2, #8]
	ldr	r5, .L2457+100
	str	r3, [r5]
	ldr	r5, .L2457+104
	str	r3, [r5]
	ldr	r5, .L2457+108
	str	r3, [r5]
	ldr	r5, .L2457+112
	str	r3, [r5]
	ldr	r5, .L2457+116
	str	r6, [r5]
	mov	r6, r1
	ldr	r5, .L2457+120
	str	r3, [r5]
	ldr	r5, .L2457+124
	str	r3, [r5]
	ldr	r5, .L2457+128
	ldr	lr, [r4, #40]
	str	r3, [r5]
	ldr	r3, .L2457+132
	ldr	r5, [r3]
	cmp	lr, r5
	mov	r5, r2
	it	hi
	strhi	lr, [r3]
	ldr	r3, .L2457+136
	ldr	r2, [r4, #36]
	ldr	r1, [r3]
	cmp	r2, r1
	it	hi
	strhi	r2, [r3]
	movw	r3, #65535
	cmp	ip, r3
	beq	.L2438
	ldr	r0, .L2457+84
	bl	make_superblock
.L2438:
	ldrh	r2, [r6]
	movw	r3, #65535
	cmp	r2, r3
	beq	.L2439
	ldr	r0, .L2457+92
	bl	make_superblock
.L2439:
	ldrh	r2, [r5]
	movw	r3, #65535
	cmp	r2, r3
	beq	.L2440
	ldr	r0, .L2457+96
	bl	make_superblock
.L2440:
	ldrh	r2, [r7]
	movw	r3, #65535
	cmp	r2, r3
	beq	.L2441
	ldr	r0, .L2457+88
	bl	make_superblock
.L2441:
	movs	r0, #0
	b	.L2421
.L2458:
	.align	2
.L2457:
	.word	1179929683
	.word	.LANCHOR57
	.word	.LANCHOR230
	.word	.LC5
	.word	.LC6
	.word	.LC7
	.word	.LANCHOR82
	.word	.LANCHOR1
	.word	.LANCHOR69
	.word	.LANCHOR66
	.word	.LANCHOR203
	.word	.LANCHOR45
	.word	.LANCHOR231
	.word	.LANCHOR74
	.word	.LANCHOR52
	.word	.LANCHOR55
	.word	.LANCHOR68
	.word	.LANCHOR42
	.word	.LANCHOR76
	.word	.LANCHOR38
	.word	.LANCHOR232
	.word	.LANCHOR93
	.word	.LANCHOR213
	.word	.LANCHOR94
	.word	.LANCHOR95
	.word	.LANCHOR166
	.word	.LANCHOR167
	.word	.LANCHOR171
	.word	.LANCHOR170
	.word	.LANCHOR172
	.word	.LANCHOR173
	.word	.LANCHOR174
	.word	.LANCHOR169
	.word	.LANCHOR164
	.word	.LANCHOR165
	.size	FtlLoadSysInfo, .-FtlLoadSysInfo
	.section	.text.FtlDumpBlockInfo,"ax",%progbits
	.align	1
	.global	FtlDumpBlockInfo
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	FtlDumpBlockInfo, %function
FtlDumpBlockInfo:
	@ args = 0, pretend = 0, frame = 64
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, r8, r10, fp, lr}
	ubfx	r0, r0, #10, #16
	ldr	r4, .L2471
	sub	sp, sp, #88
	mov	r8, r1
	ldrh	r3, [r4]
	str	r3, [sp, #24]
	bl	P2V_block_in_plane
	ldr	r1, .L2471+4
	mov	r6, r0
	ldr	r0, .L2471+8
	bl	printf
	ldr	r3, .L2471+12
	mov	r1, r6
	ldr	r0, .L2471+16
	ldr	r3, [r3]
	ldrh	r2, [r3, r6, lsl #1]
	bl	printf
	add	r0, sp, #88
	strh	r6, [r0, #-48]!	@ movhi
	bl	make_superblock
	ldr	r3, .L2471+20
	ldrb	r5, [r3]	@ zero_extendqisi2
	cbz	r5, .L2460
	cmp	r8, #0
	bne	.L2469
	mov	r0, r6
	bl	ftl_get_blk_mode
	cmp	r0, #1
	mov	r5, r0
	bne	.L2460
	ldr	r3, .L2471+24
	ldrh	r3, [r3]
	str	r3, [sp, #24]
.L2460:
	movs	r6, #0
	ldrh	r3, [r4]
	ldr	r2, [sp, #24]
	mov	r1, r5
	ldr	r0, .L2471+28
	bl	printf
.L2461:
	ldr	r3, .L2471+32
	movs	r2, #0
	add	ip, sp, #54
	mov	r4, r2
	movw	r10, #65535
	mov	fp, #36
	ldrh	lr, [r3]
	ldr	r3, .L2471+36
	ldr	r0, [r3]
	ldr	r3, .L2471+40
	ldr	r3, [r3]
	str	r3, [sp, #28]
	ldr	r3, .L2471+44
	ldrh	r3, [r3]
	str	r3, [sp, #32]
	ldr	r3, .L2471+48
	ldr	r3, [r3]
	str	r3, [sp, #36]
	ldr	r3, .L2471+52
	ldrh	r8, [r3]
.L2462:
	uxth	r3, r2
	cmp	lr, r3
	bhi	.L2464
	ldr	fp, .L2471+56
	mov	r8, #0
	mov	r10, #36
	mov	r2, r5
	mov	r1, r4
	bl	FlashReadPages
.L2465:
	uxth	r3, r8
	cmp	r4, r3
	bhi	.L2466
	adds	r6, r6, #1
	ldr	r3, [sp, #24]
	uxth	r6, r6
	cmp	r3, r6
	bne	.L2461
.L2467:
	movs	r0, #0
	add	sp, sp, #88
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r10, fp, pc}
.L2469:
	movs	r5, #0
	b	.L2460
.L2464:
	ldrh	r3, [ip, #2]!
	cmp	r3, r10
	beq	.L2463
	mla	r1, fp, r4, r0
	ldr	r7, [sp, #28]
	orr	r3, r6, r3, lsl #10
	str	r3, [r1, #4]
	ldr	r3, [sp, #32]
	muls	r3, r4, r3
	bic	r3, r3, #3
	add	r3, r3, r7
	ldr	r7, [sp, #36]
	str	r3, [r1, #8]
	mul	r3, r8, r4
	adds	r4, r4, #1
	uxth	r4, r4
	bic	r3, r3, #3
	add	r3, r3, r7
	str	r3, [r1, #12]
.L2463:
	adds	r2, r2, #1
	b	.L2462
.L2466:
	ldr	r3, .L2471+36
	mul	r0, r10, r8
	ldrh	r1, [sp, #40]
	add	r8, r8, #1
	ldr	ip, [r3]
	add	r2, ip, r0
	ldr	lr, [r2, #8]
	ldr	r3, [r2, #12]
	ldr	r7, [lr, #4]
	str	r7, [sp, #20]
	ldr	r7, [lr]
	str	r7, [sp, #16]
	ldr	r7, [r3, #12]
	str	r7, [sp, #12]
	ldr	r7, [r3, #8]
	str	r7, [sp, #8]
	ldr	r7, [r3, #4]
	str	r7, [sp, #4]
	ldr	r3, [r3]
	str	r3, [sp]
	ldr	r3, [r2, #4]
	ldr	r2, [ip, r0]
	mov	r0, fp
	bl	printf
	b	.L2465
.L2472:
	.align	2
.L2471:
	.word	.LANCHOR52
	.word	.LANCHOR233
	.word	.LC48
	.word	.LANCHOR85
	.word	.LC49
	.word	.LANCHOR16
	.word	.LANCHOR53
	.word	.LC50
	.word	.LANCHOR38
	.word	.LANCHOR186
	.word	.LANCHOR107
	.word	.LANCHOR57
	.word	.LANCHOR108
	.word	.LANCHOR58
	.word	.LC51
	.size	FtlDumpBlockInfo, .-FtlDumpBlockInfo
	.section	.text.FtlScanAllBlock,"ax",%progbits
	.align	1
	.global	FtlScanAllBlock
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	FtlScanAllBlock, %function
FtlScanAllBlock:
	@ args = 0, pretend = 0, frame = 64
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, r8, r10, fp, lr}
	sub	sp, sp, #88
	ldr	r6, .L2483
	ldr	r1, .L2483+4
	ldr	r0, .L2483+8
	bl	printf
	movs	r3, #0
	str	r3, [sp, #28]
.L2474:
	ldr	r3, .L2483+12
	ldrh	r0, [sp, #28]
	ldrh	r3, [r3]
	cmp	r3, r0
	bhi	.L2482
	movs	r0, #0
	add	sp, sp, #88
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r10, fp, pc}
.L2482:
	add	r4, sp, #88
	add	r7, sp, #54
	strh	r0, [r4, #-48]!	@ movhi
	movw	r10, #65535
	bl	ftl_get_blk_mode
	ldr	r3, .L2483+16
	mov	fp, #36
	ldrh	r1, [sp, #28]
	ldr	r2, [r3]
	mov	r3, r0
	ldr	r0, .L2483+20
	ldrh	r2, [r2, r1, lsl #1]
	bl	printf
	mov	r0, r4
	bl	make_superblock
	ldr	r3, .L2483+24
	movs	r2, #0
	ldr	r0, [r6]
	mov	r4, r2
	ldrh	lr, [r3]
	ldr	r3, .L2483+28
	ldr	r3, [r3]
	str	r3, [sp, #32]
	ldr	r3, .L2483+32
	ldrh	ip, [r3]
	ldr	r3, .L2483+36
	ldr	r3, [r3]
	str	r3, [sp, #36]
	ldr	r3, .L2483+40
	ldrh	r8, [r3]
.L2475:
	uxth	r3, r2
	cmp	lr, r3
	bhi	.L2477
	ldr	r10, .L2483+44
	movs	r7, #0
	mov	r8, #36
	movs	r2, #0
	mov	r1, r4
	bl	FlashReadPages
.L2478:
	uxth	r3, r7
	cmp	r4, r3
	bhi	.L2479
	ldr	r10, .L2483+48
	movs	r7, #0
	mov	r8, #36
	movs	r2, #1
	mov	r1, r4
	ldr	r0, [r6]
	bl	FlashReadPages
.L2480:
	uxth	r3, r7
	cmp	r4, r3
	bhi	.L2481
	ldr	r3, [sp, #28]
	adds	r3, r3, #1
	str	r3, [sp, #28]
	b	.L2474
.L2477:
	ldrh	r3, [r7, #2]!
	cmp	r3, r10
	beq	.L2476
	mla	r1, fp, r4, r0
	ldr	r5, [sp, #32]
	lsls	r3, r3, #10
	str	r3, [r1, #4]
	mul	r3, ip, r4
	bic	r3, r3, #3
	add	r3, r3, r5
	ldr	r5, [sp, #36]
	str	r3, [r1, #8]
	mul	r3, r8, r4
	adds	r4, r4, #1
	uxth	r4, r4
	bic	r3, r3, #3
	add	r3, r3, r5
	str	r3, [r1, #12]
.L2476:
	adds	r2, r2, #1
	b	.L2475
.L2479:
	mul	r2, r8, r7
	ldr	r0, [r6]
	ldrh	r1, [sp, #40]
	adds	r7, r7, #1
	add	lr, r0, r2
	ldr	fp, [lr, #8]
	ldr	r3, [lr, #12]
	ldr	r5, [fp, #4]
	str	r5, [sp, #20]
	ldr	r5, [fp]
	str	r5, [sp, #16]
	ldr	r5, [r3, #12]
	str	r5, [sp, #12]
	ldr	r5, [r3, #8]
	str	r5, [sp, #8]
	ldr	r5, [r3, #4]
	str	r5, [sp, #4]
	ldr	r3, [r3]
	str	r3, [sp]
	ldr	r2, [r0, r2]
	mov	r0, r10
	ldr	r3, [lr, #4]
	bl	printf
	b	.L2478
.L2481:
	mul	r2, r8, r7
	ldr	r0, [r6]
	ldrh	r1, [sp, #40]
	adds	r7, r7, #1
	add	lr, r0, r2
	ldr	fp, [lr, #8]
	ldr	r3, [lr, #12]
	ldr	r5, [fp, #4]
	str	r5, [sp, #20]
	ldr	r5, [fp]
	str	r5, [sp, #16]
	ldr	r5, [r3, #12]
	str	r5, [sp, #12]
	ldr	r5, [r3, #8]
	str	r5, [sp, #8]
	ldr	r5, [r3, #4]
	str	r5, [sp, #4]
	ldr	r3, [r3]
	str	r3, [sp]
	ldr	r2, [r0, r2]
	mov	r0, r10
	ldr	r3, [lr, #4]
	bl	printf
	b	.L2480
.L2484:
	.align	2
.L2483:
	.word	.LANCHOR186
	.word	.LANCHOR234
	.word	.LC48
	.word	.LANCHOR41
	.word	.LANCHOR85
	.word	.LC52
	.word	.LANCHOR38
	.word	.LANCHOR107
	.word	.LANCHOR57
	.word	.LANCHOR108
	.word	.LANCHOR58
	.word	.LC53
	.word	.LC54
	.size	FtlScanAllBlock, .-FtlScanAllBlock
	.section	.text.FtlMapTblRecovery,"ax",%progbits
	.align	1
	.global	FtlMapTblRecovery
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	FtlMapTblRecovery, %function
FtlMapTblRecovery:
	@ args = 0, pretend = 0, frame = 24
	@ frame_needed = 0, uses_anonymous_args = 0
	ldr	r3, [r0, #24]
	movs	r1, #0
	push	{r4, r5, r6, r7, r8, r10, fp, lr}
	sub	sp, sp, #24
	ldrh	r7, [r0, #6]
	mov	r4, r0
	movs	r6, #0
	str	r3, [sp]
	ldr	r3, [r0, #16]
	ldr	r10, [r0, #12]
	lsls	r2, r7, #2
	str	r3, [sp, #12]
	ldrh	r3, [r0, #8]
	ldr	r0, [sp]
	str	r3, [sp, #4]
	bl	ftl_memset
	ldr	r2, .L2526
	ldr	r3, .L2526+4
	str	r6, [r4, #32]
	ldr	r1, [r2]
	mov	fp, r3
	str	r6, [r4, #28]
	str	r2, [sp, #8]
	str	r1, [r3, #8]
	ldr	r1, .L2526+8
	ldr	r5, [r1]
	movw	r1, #65535
	str	r5, [r3, #12]
	strh	r1, [r4]	@ movhi
	strh	r1, [r4, #2]	@ movhi
	movs	r1, #1
	str	r1, [r4, #36]
.L2486:
	ldr	r2, [sp, #4]
	sxth	r3, r6
	cmp	r3, r2
	bge	.L2505
	ldr	r2, [sp, #4]
	lsl	r8, r3, #1
	subs	r2, r2, #1
	cmp	r3, r2
	bne	.L2487
	ldrh	r0, [r10, r3, lsl #1]
	movs	r1, #1
	str	r3, [sp, #4]
	mov	fp, #0
	bl	FtlGetLastWrittenPage
	ldr	r3, [sp, #12]
	add	r8, r8, r10
	strh	r6, [r4]	@ movhi
	sxth	r10, r0
	ldr	r6, .L2526+4
	adds	r0, r0, #1
	mov	r2, r3
	ldr	r3, [sp, #4]
	strh	r0, [r4, #2]	@ movhi
	ldr	r3, [r2, r3, lsl #2]
	str	r3, [r4, #28]
.L2488:
	sxth	r2, fp
	cmp	r2, r10
	ble	.L2491
.L2505:
	mov	r0, r4
	bl	ftl_free_no_use_map_blk
	ldr	r3, .L2526+12
	ldrh	r2, [r4, #2]
	ldrh	r3, [r3]
	cmp	r2, r3
	bne	.L2493
	mov	r0, r4
	bl	ftl_map_blk_alloc_new_blk
.L2493:
	mov	r0, r4
	bl	ftl_map_blk_gc
	mov	r0, r4
	bl	ftl_map_blk_gc
	movs	r0, #0
	add	sp, sp, #24
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r10, fp, pc}
.L2491:
	ldrh	r1, [r8]
	ldr	r0, .L2526+4
	orr	r2, r2, r1, lsl #10
	str	r2, [r6, #4]
	movs	r2, #1
	mov	r1, r2
	bl	FlashReadPages
	ldr	r3, .L2526+16
	ldrb	r2, [r3]	@ zero_extendqisi2
	cbz	r2, .L2489
	ldr	r2, [r6, #12]
	ldr	r2, [r2, #12]
	str	r2, [sp, #4]
	cbz	r2, .L2489
	ldr	r1, .L2526+20
	ldr	r0, [r6, #8]
	ldrh	r1, [r1]
	bl	js_hash
	ldr	r2, [sp, #4]
	cmp	r2, r0
	itt	ne
	movne	r2, #-1
	strne	r2, [r6]
.L2489:
	ldr	r2, [r6]
	adds	r2, r2, #1
	beq	.L2490
	ldrh	r2, [r5, #8]
	cmp	r7, r2
	bls	.L2490
	ldrh	r1, [r4, #4]
	ldrh	r0, [r5]
	cmp	r0, r1
	ittt	eq
	ldreq	r1, [r6, #4]
	ldreq	r3, [sp]
	streq	r1, [r3, r2, lsl #2]
.L2490:
	add	fp, fp, #1
	b	.L2488
.L2487:
	ldr	r2, [sp, #8]
	ldr	r0, .L2526+4
	ldr	r2, [r2]
	str	r2, [fp, #8]
	add	r2, r10, r8
	ldr	r8, .L2526+12
	str	r2, [sp, #16]
	ldrh	r2, [r10, r3, lsl #1]
	ldrh	r3, [r8]
	subs	r3, r3, #1
	orr	r3, r3, r2, lsl #10
	movs	r2, #1
	mov	r1, r2
	str	r3, [fp, #4]
	bl	FlashReadPages
	ldr	r3, [fp]
	adds	r3, r3, #1
	beq	.L2507
	ldrh	r2, [r5]
	ldrh	r3, [r4, #4]
	cmp	r2, r3
	bne	.L2507
	ldrh	r2, [r5, #8]
	movw	r3, #64245
	cmp	r2, r3
	beq	.L2495
.L2507:
	mov	r8, #0
.L2496:
	ldr	r2, .L2526+12
	sxth	r3, r8
	ldrh	r2, [r2]
	cmp	r3, r2
	bge	.L2503
	ldr	r2, [sp, #16]
	ldr	r0, .L2526+4
	ldrh	r2, [r2]
	orr	r3, r3, r2, lsl #10
	movs	r2, #1
	mov	r1, r2
	str	r3, [fp, #4]
	bl	FlashReadPages
	ldr	r3, .L2526+16
	ldrb	r3, [r3]	@ zero_extendqisi2
	cbz	r3, .L2500
	ldr	r3, [fp, #12]
	ldr	r3, [r3, #12]
	str	r3, [sp, #20]
	cbz	r3, .L2500
	ldr	r2, .L2526+20
	ldr	r0, [fp, #8]
	ldrh	r1, [r2]
	bl	js_hash
	ldr	r3, [sp, #20]
	cmp	r3, r0
	itt	ne
	movne	r3, #-1
	strne	r3, [fp]
.L2500:
	ldr	r3, [fp]
	adds	r3, r3, #1
	beq	.L2501
	ldrh	r3, [r5, #8]
	cmp	r7, r3
	bls	.L2501
	ldrh	r1, [r5]
	ldrh	r2, [r4, #4]
	cmp	r1, r2
	ittt	eq
	ldreq	r2, [fp, #4]
	ldreq	r1, [sp]
	streq	r2, [r1, r3, lsl #2]
.L2501:
	add	r8, r8, #1
	b	.L2496
.L2495:
	ldr	r3, [sp, #8]
	movs	r1, #0
	ldrh	r2, [r8]
	ldr	ip, [r3]
	subs	r2, r2, #1
.L2497:
	sxth	r3, r1
	cmp	r3, r2
	blt	.L2499
.L2503:
	adds	r6, r6, #1
	b	.L2486
.L2499:
	lsls	r0, r3, #3
	ldr	r3, [ip, r3, lsl #3]
	adds	r1, r1, #1
	uxth	lr, r3
	cmp	r7, lr
	itttt	hi
	addhi	r0, r0, ip
	ldrhi	r3, [sp]
	ldrhi	r0, [r0, #4]
	strhi	r0, [r3, lr, lsl #2]
	b	.L2497
.L2527:
	.align	2
.L2526:
	.word	.LANCHOR189
	.word	.LANCHOR211
	.word	.LANCHOR195
	.word	.LANCHOR53
	.word	.LANCHOR2
	.word	.LANCHOR57
	.size	FtlMapTblRecovery, .-FtlMapTblRecovery
	.section	.text.FtlLoadVonderInfo,"ax",%progbits
	.align	1
	.global	FtlLoadVonderInfo
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	FtlLoadVonderInfo, %function
FtlLoadVonderInfo:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r3, lr}
	ldr	r3, .L2529
	ldr	r0, .L2529+4
	ldrh	r3, [r3]
	strh	r3, [r0, #10]	@ movhi
	movw	r3, #61574
	strh	r3, [r0, #4]	@ movhi
	ldr	r3, .L2529+8
	ldrh	r3, [r3]
	strh	r3, [r0, #8]	@ movhi
	ldr	r3, .L2529+12
	ldrh	r3, [r3]
	strh	r3, [r0, #6]	@ movhi
	ldr	r3, .L2529+16
	ldr	r3, [r3]
	str	r3, [r0, #12]
	ldr	r3, .L2529+20
	ldr	r3, [r3]
	str	r3, [r0, #16]
	ldr	r3, .L2529+24
	ldr	r3, [r3]
	str	r3, [r0, #20]
	ldr	r3, .L2529+28
	ldr	r3, [r3]
	str	r3, [r0, #24]
	bl	FtlMapTblRecovery
	movs	r0, #0
	pop	{r3, pc}
.L2530:
	.align	2
.L2529:
	.word	.LANCHOR61
	.word	.LANCHOR224
	.word	.LANCHOR70
	.word	.LANCHOR62
	.word	.LANCHOR71
	.word	.LANCHOR201
	.word	.LANCHOR200
	.word	.LANCHOR202
	.size	FtlLoadVonderInfo, .-FtlLoadVonderInfo
	.section	.text.FtlLoadMapInfo,"ax",%progbits
	.align	1
	.global	FtlLoadMapInfo
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	FtlLoadMapInfo, %function
FtlLoadMapInfo:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r3, lr}
	bl	FtlL2PDataInit
	ldr	r0, .L2532
	bl	FtlMapTblRecovery
	movs	r0, #0
	pop	{r3, pc}
.L2533:
	.align	2
.L2532:
	.word	.LANCHOR130
	.size	FtlLoadMapInfo, .-FtlLoadMapInfo
	.section	.text.ftl_scan_all_ppa,"ax",%progbits
	.align	1
	.global	ftl_scan_all_ppa
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	ftl_scan_all_ppa, %function
ftl_scan_all_ppa:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 0, uses_anonymous_args = 0
	ldr	r3, .L2550
	push	{r4, r5, r6, r7, r8, r10, fp, lr}
	sub	sp, sp, #32
	ldr	r5, .L2550+4
	ldrh	r4, [r3]
	str	r3, [sp, #28]
	subs	r4, r4, #16
	lsl	r10, r4, #10
.L2535:
	ldr	r3, [sp, #28]
	ldrh	r3, [r3]
	cmp	r4, r3
	blt	.L2543
	ldr	r1, .L2550+8
	ldr	r0, .L2550+12
	add	sp, sp, #32
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r10, fp, lr}
	b	printf
.L2543:
	uxth	r7, r4
	mov	r0, r7
	bl	ftl_get_blk_mode
	ldr	r3, .L2550+16
	ldrb	r3, [r3]	@ zero_extendqisi2
	cbz	r3, .L2536
	ldr	r3, .L2550+20
	ldrh	r3, [r3]
	cmp	r4, r3
	bge	.L2537
	ldr	r3, .L2550+24
	ldrh	r3, [r3]
	cmp	r4, r3
	blt	.L2537
.L2536:
	cmp	r0, #1
	bne	.L2538
.L2537:
	ldr	r3, .L2550+28
	mov	r8, #-2147483648
	ldrh	r6, [r3]
.L2539:
	mov	r3, r8
	mov	r2, r6
	mov	r1, r4
	ldr	r0, .L2550+32
	bl	printf
	mov	r0, r7
	bl	FtlBbmIsBadBlock
	cbz	r0, .L2540
	mov	r3, r8
	mov	r2, r6
	mov	r1, r4
	ldr	r0, .L2550+36
	bl	printf
.L2540:
	ldr	fp, .L2550+52
	movs	r7, #0
.L2541:
	cmp	r7, r6
	bne	.L2542
	adds	r4, r4, #1
	add	r10, r10, #1024
	b	.L2535
.L2538:
	ldr	r3, .L2550+40
	mov	r8, #0
	ldrh	r6, [r3]
	b	.L2539
.L2542:
	add	r3, r8, r10
	movs	r2, #0
	add	r3, r3, r7
	movs	r1, #1
	str	r3, [r5, #4]
	mov	r0, r5
	ldr	r3, [fp]
	adds	r7, r7, #1
	str	r2, [r5]
	str	r3, [r5, #8]
	ldr	r3, .L2550+44
	ldr	r3, [r3]
	str	r3, [r5, #12]
	bl	FlashReadPages
	ldr	r2, [r5, #8]
	ldr	r3, [r5, #12]
	ldr	r0, .L2550+48
	ldr	r1, [r2, #4]
	str	r1, [sp, #16]
	ldr	r2, [r2]
	ldr	r1, [r5, #4]
	str	r2, [sp, #12]
	ldr	r2, [r3, #12]
	str	r2, [sp, #8]
	ldr	r2, [r3, #8]
	str	r2, [sp, #4]
	ldr	r2, [r3, #4]
	str	r2, [sp]
	ldr	r2, [r5]
	ldr	r3, [r3]
	bl	printf
	b	.L2541
.L2551:
	.align	2
.L2550:
	.word	.LANCHOR51
	.word	.LANCHOR211
	.word	.LANCHOR235
	.word	.LC58
	.word	.LANCHOR16
	.word	.LANCHOR40
	.word	.LANCHOR59
	.word	.LANCHOR53
	.word	.LC55
	.word	.LC56
	.word	.LANCHOR52
	.word	.LANCHOR195
	.word	.LC57
	.word	.LANCHOR189
	.size	ftl_scan_all_ppa, .-ftl_scan_all_ppa
	.section	.text.FlashReadFacBbtData,"ax",%progbits
	.align	1
	.global	FlashReadFacBbtData
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	FlashReadFacBbtData, %function
FlashReadFacBbtData:
	@ args = 0, pretend = 0, frame = 48
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, r8, r10, fp, lr}
	mov	fp, r2
	ldr	r2, .L2565
	sub	sp, sp, #48
	mov	r6, r1
	mov	r4, r0
	ldr	r7, .L2565+4
	ldrh	r3, [r2, #14]
	ldrh	r2, [r2, #12]
	smulbb	r3, r3, r2
	ldr	r2, [r7]
	uxth	r3, r3
	str	r2, [sp, #20]
	ldr	r2, .L2565+8
	subs	r5, r3, #1
	mul	r10, r6, r3
	uxth	r5, r5
	subs	r3, r3, #15
	ldr	r1, [r2]
	mov	r8, r2
	str	r1, [sp, #24]
.L2553:
	cmp	r3, r5
	ble	.L2560
	mov	r0, #-1
	b	.L2552
.L2560:
	add	r2, r5, r10
	add	r0, sp, #12
	lsls	r2, r2, #10
	str	r3, [sp, #4]
	str	r2, [sp, #16]
	movs	r2, #1
	mov	r1, r2
	bl	FlashReadPages
	ldr	r2, [sp, #12]
	ldr	r3, [sp, #4]
	adds	r2, r2, #1
	beq	.L2554
	ldr	r2, [r8]
	ldrh	r1, [r2]
	movw	r2, #61664
	cmp	r1, r2
	bne	.L2554
	cbz	r4, .L2561
	cbz	r6, .L2556
.L2559:
	mov	r2, fp
	ldr	r1, [r7]
	mov	r0, r4
	bl	ftl_memcpy
	movs	r3, #4
	ldr	r0, .L2565+12
	mov	r2, r3
	mov	r1, r4
	bl	rknand_print_hex
	movs	r0, #0
.L2552:
	add	sp, sp, #48
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r10, fp, pc}
.L2556:
	ldr	r1, [r7]
	mov	ip, #1
	ldr	r5, .L2565+16
.L2557:
	ldr	r0, [r5]
	uxth	r3, r6
	adds	r6, r6, #1
	cmp	r3, r0
	bcs	.L2559
	lsrs	r0, r3, #5
	and	r3, r3, #31
	lsl	r3, ip, r3
	ldr	r2, [r1, r0, lsl #2]
	orrs	r3, r3, r2
	str	r3, [r1, r0, lsl #2]
	b	.L2557
.L2554:
	subs	r5, r5, #1
	uxth	r5, r5
	b	.L2553
.L2561:
	mov	r0, r4
	b	.L2552
.L2566:
	.align	2
.L2565:
	.word	.LANCHOR15
	.word	.LANCHOR154
	.word	.LANCHOR205
	.word	.LC59
	.word	.LANCHOR156
	.size	FlashReadFacBbtData, .-FlashReadFacBbtData
	.section	.text.FlashGetBadBlockList,"ax",%progbits
	.align	1
	.global	FlashGetBadBlockList
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	FlashGetBadBlockList, %function
FlashGetBadBlockList:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r3, r4, r5, r6, r7, lr}
	mov	r5, r0
	ldr	r3, .L2577
	ldr	r6, .L2577+4
	ldr	r3, [r3]
	ldr	r0, [r6]
	ldrb	r4, [r3, #13]	@ zero_extendqisi2
	ldrh	r3, [r3, #14]
	smulbb	r4, r4, r3
	uxth	r4, r4
	adds	r2, r4, #7
	asrs	r2, r2, #3
	bl	FlashReadFacBbtData
	adds	r0, r0, #1
	bne	.L2568
.L2572:
	movs	r3, #0
.L2569:
	movw	r2, #65535
	movs	r0, #0
	strh	r2, [r5, r3, lsl #1]	@ movhi
	pop	{r3, r4, r5, r6, r7, pc}
.L2568:
	ldr	r7, [r6]
	movs	r2, #0
	lsr	ip, r4, #4
	mov	r3, r2
	subs	r4, r4, #1
	mov	lr, #1
.L2570:
	uxth	r1, r2
	cmp	r1, r4
	bge	.L2569
	lsrs	r6, r1, #5
	and	r0, r1, #31
	lsl	r0, lr, r0
	adds	r2, r2, #1
	ldr	r6, [r7, r6, lsl #2]
	tst	r0, r6
	ittt	ne
	addne	r0, r3, #1
	strhne	r1, [r5, r3, lsl #1]	@ movhi
	uxthne	r3, r0
	cmp	r3, ip
	bcc	.L2570
	b	.L2572
.L2578:
	.align	2
.L2577:
	.word	.LANCHOR7
	.word	.LANCHOR149
	.size	FlashGetBadBlockList, .-FlashGetBadBlockList
	.section	.text.FtlMakeBbt,"ax",%progbits
	.align	1
	.global	FtlMakeBbt
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	FtlMakeBbt, %function
FtlMakeBbt:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 0, uses_anonymous_args = 0
	ldr	r3, .L2599
	push	{r0, r1, r4, r5, r6, r7, r8, r10, fp, lr}
	ldr	r7, [r3]
	cmp	r7, #0
	bne	.L2580
	ldr	r8, .L2599+40
	ldr	r4, .L2599+4
	bl	FtlBbtMemInit
	sub	r10, r8, #18
	bl	FtlLoadFactoryBbt
.L2581:
	ldr	r3, .L2599+8
	ldrh	r3, [r3]
	cmp	r7, r3
	bcc	.L2587
	ldr	r5, .L2599+12
	movs	r4, #0
.L2588:
	ldrh	r3, [r5]
	uxth	r0, r4
	adds	r4, r4, #1
	cmp	r3, r0
	bhi	.L2589
	ldr	r4, .L2599+16
	movw	r6, #65535
	ldrh	r5, [r4, #12]
	subs	r5, r5, #1
	uxth	r5, r5
.L2590:
	ldrh	r3, [r4, #12]
	subs	r3, r3, #47
	cmp	r3, r5
	bgt	.L2594
	mov	r0, r5
	bl	FtlBbmIsBadBlock
	cmp	r0, #1
	beq	.L2591
	mov	r0, r5
	bl	FlashTestBlk
	cmp	r0, #0
	beq	.L2592
	mov	r0, r5
	bl	FtlBbmMapBadBlock
.L2591:
	subs	r5, r5, #1
	uxth	r5, r5
	b	.L2590
.L2587:
	ldr	r3, .L2599+20
	movw	r1, #65535
	ldrh	r2, [r10, #2]!
	ldr	r0, [r3]
	ldr	r3, .L2599+24
	cmp	r2, r1
	str	r0, [r4, #8]
	ldr	fp, [r3]
	str	r3, [sp, #4]
	ldr	r3, .L2599+28
	str	fp, [r4, #12]
	beq	.L2582
	ldrh	r6, [r3]
	mov	r0, r4
	str	r3, [sp]
	mla	r6, r7, r6, r2
	lsls	r2, r6, #10
	str	r2, [r4, #4]
	movs	r2, #1
	mov	r1, r2
	bl	FlashReadPages
	ldr	r3, [sp]
	ldr	r1, [r4, #8]
	ldr	r0, [r8]
	ldrh	r2, [r3]
	adds	r2, r2, #7
	asrs	r2, r2, #3
	bl	ftl_memcpy
.L2583:
	uxth	r0, r6
	adds	r7, r7, #1
	add	r8, r8, #4
	bl	FtlBbmMapBadBlock
	b	.L2581
.L2582:
	mov	r1, r7
	str	r3, [sp]
	bl	FlashGetBadBlockList
	ldr	r1, [r8]
	ldr	r0, [r4, #8]
	bl	FtlBbt2Bitmap
	ldr	r3, [sp]
	ldrh	r5, [r3]
.L2585:
	subs	r5, r5, #1
	uxth	r5, r5
.L2584:
	ldr	r3, [sp]
	ldrh	r0, [r3]
	smlabb	r0, r0, r7, r5
	uxth	r0, r0
	bl	FtlBbmIsBadBlock
	cmp	r0, #1
	beq	.L2585
	ldr	r3, [sp, #4]
	movs	r2, #16
	movs	r1, #0
	strh	r5, [r10]	@ movhi
	ldr	r0, [r3]
	bl	ftl_memset
	ldr	r2, [sp]
	movw	r3, #61664
	strh	r3, [fp]	@ movhi
	movs	r3, #0
	str	r3, [fp, #4]
	ldrh	r6, [r2]
	ldrh	r3, [r10]
	ldr	r1, [r8]
	ldr	r0, [r4, #8]
	strh	r3, [fp, #2]	@ movhi
	mla	r6, r7, r6, r3
	lsls	r3, r6, #10
	str	r3, [r4, #4]
	ldr	r3, .L2599+32
	ldrh	r2, [r3]
	lsls	r2, r2, #2
	bl	ftl_memcpy
	movs	r2, #1
	mov	r0, r4
	mov	r1, r2
	bl	FlashEraseBlocks
	movs	r3, #1
	mov	r0, r4
	mov	r2, r3
	mov	r1, r3
	bl	FlashProgPages
	ldr	r3, [r4]
	adds	r3, r3, #1
	bne	.L2583
	uxth	r0, r6
	bl	FtlBbmMapBadBlock
	b	.L2584
.L2589:
	bl	FtlBbmMapBadBlock
	b	.L2588
.L2592:
	ldrh	r3, [r4]
	cmp	r3, r6
	bne	.L2593
	strh	r5, [r4]	@ movhi
	b	.L2591
.L2593:
	strh	r5, [r4, #4]	@ movhi
.L2594:
	ldr	r3, .L2599+36
	movs	r5, #0
	str	r5, [r4, #8]
	movs	r2, #2
	movs	r1, #1
	strh	r5, [r4, #2]	@ movhi
	ldr	r0, [r3]
	ldrh	r3, [r4]
	lsls	r3, r3, #10
	str	r3, [r0, #4]
	ldrh	r3, [r4, #4]
	lsls	r3, r3, #10
	str	r3, [r0, #40]
	bl	FlashEraseBlocks
	ldrh	r0, [r4]
	bl	FtlBbmMapBadBlock
	ldrh	r0, [r4, #4]
	bl	FtlBbmMapBadBlock
	bl	FtlBbmTblFlush
	ldr	r3, [r4, #8]
	ldrh	r2, [r4, #4]
	strh	r5, [r4, #2]	@ movhi
	adds	r3, r3, #1
	str	r3, [r4, #8]
	ldrh	r3, [r4]
	strh	r2, [r4]	@ movhi
	strh	r3, [r4, #4]	@ movhi
	bl	FtlBbmTblFlush
.L2580:
	movs	r0, #0
	add	sp, sp, #8
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r10, fp, pc}
.L2600:
	.align	2
.L2599:
	.word	.LANCHOR78
	.word	.LANCHOR211
	.word	.LANCHOR45
	.word	.LANCHOR59
	.word	.LANCHOR76
	.word	.LANCHOR189
	.word	.LANCHOR195
	.word	.LANCHOR51
	.word	.LANCHOR126
	.word	.LANCHOR79
	.word	.LANCHOR76+28
	.size	FtlMakeBbt, .-FtlMakeBbt
	.section	.text.log2phys,"ax",%progbits
	.align	1
	.global	log2phys
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	log2phys, %function
log2phys:
	@ args = 0, pretend = 0, frame = 24
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, r8, r10, fp, lr}
	sub	sp, sp, #24
	ldr	r4, .L2619
	mov	fp, r0
	str	r2, [sp, #16]
	ldr	r2, [r4]
	ldr	r3, .L2619+4
	str	r1, [sp, #4]
	cmp	r0, r2
	ldrh	r5, [r3]
	bcc	.L2602
	ldr	r1, .L2619+8
	mov	r2, #1004
	ldr	r0, .L2619+12
	bl	printf
	ldr	r1, .L2619+16
	ldr	r0, .L2619+20
	bl	printf
.L2602:
	ldr	r3, [r4]
	cmp	fp, r3
	bcs	.L2603
	adds	r3, r5, #7
	ldr	r5, .L2619+24
	lsr	r7, fp, r3
	str	r3, [sp, #8]
	ldr	r3, .L2619+28
	movs	r4, #12
	ldr	r1, [r5]
	uxth	r6, r7
	ldrh	r2, [r3]
	movs	r3, #0
.L2604:
	uxth	r10, r3
	cmp	r10, r2
	bcc	.L2609
	bl	select_l2p_ram_region
	muls	r4, r0, r4
	ldr	r3, [r5]
	mov	r10, r0
	ldrh	r1, [r3, r4]
	adds	r2, r3, r4
	movw	r3, #65535
	cmp	r1, r3
	beq	.L2610
	ldr	r3, [r2, #4]
	cmp	r3, #0
	bge	.L2610
	bl	flush_l2p_region
.L2610:
	ldr	r3, .L2619+32
	ldrh	r3, [r3]
	cmp	r3, r6
	bcs	.L2611
	ldr	r1, .L2619+36
	movw	r2, #597
	ldr	r0, .L2619+12
	bl	printf
	ldr	r1, .L2619+16
	ldr	r0, .L2619+20
	bl	printf
.L2611:
	ldr	r3, .L2619+40
	uxth	r7, r7
	ldr	r3, [r3]
	ldr	r3, [r3, r7, lsl #2]
	cmp	r3, #0
	bne	.L2612
	ldr	r2, [r5]
	movs	r1, #255
	str	r3, [sp, #12]
	adds	r0, r2, r4
	ldr	r2, .L2619+44
	ldr	r0, [r0, #8]
	ldrh	r2, [r2]
	bl	ftl_memset
	ldr	r2, [r5]
	ldr	r3, [sp, #12]
	adds	r1, r2, r4
	strh	r6, [r2, r4]	@ movhi
	str	r3, [r1, #4]
	b	.L2606
.L2603:
	ldr	r3, [sp, #16]
	mov	r0, #-1
	cbnz	r3, .L2601
	ldr	r3, [sp, #4]
	str	r0, [r3]
.L2601:
	add	sp, sp, #24
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r10, fp, pc}
.L2609:
	adds	r3, r3, #1
	mla	r0, r4, r3, r1
	ldrh	r0, [r0, #-12]
	cmp	r0, r6
	bne	.L2604
.L2606:
	ldr	r2, [sp, #8]
	movs	r3, #1
	ldr	r0, [sp, #16]
	ldr	r1, .L2619+24
	lsls	r3, r3, r2
	movs	r2, #12
	subs	r3, r3, #1
	and	r3, r3, fp
	uxth	r3, r3
	cbnz	r0, .L2607
	ldr	r0, [r1]
	mla	r2, r2, r10, r0
	ldr	r2, [r2, #8]
	ldr	r3, [r2, r3, lsl #2]
	ldr	r2, [sp, #4]
	str	r3, [r2]
.L2608:
	ldr	r2, [r1]
	movs	r3, #12
	mla	r10, r3, r10, r2
	ldr	r3, [r10, #4]
	adds	r2, r3, #1
	beq	.L2617
	adds	r3, r3, #1
	str	r3, [r10, #4]
.L2617:
	movs	r0, #0
	b	.L2601
.L2607:
	ldr	r0, [r1]
	mla	r2, r2, r10, r0
	ldr	r0, [sp, #4]
	ldr	r4, [r0]
	ldr	r0, [r2, #8]
	str	r4, [r0, r3, lsl #2]
	ldr	r3, [r2, #4]
	orr	r3, r3, #-2147483648
	str	r3, [r2, #4]
	ldr	r3, .L2619+48
	strh	r6, [r3]	@ movhi
	b	.L2608
.L2612:
	ldr	r2, [r5]
	ldr	r8, .L2619+80
	str	r3, [sp, #20]
	add	r2, r2, r4
	ldr	r2, [r2, #8]
	mov	r0, r8
	str	r3, [r8, #4]
	str	r2, [r8, #8]
	ldr	r2, .L2619+52
	ldr	r2, [r2]
	str	r2, [r8, #12]
	movs	r2, #1
	mov	r1, r2
	bl	FlashReadPages
	ldr	r3, [r8, #12]
	ldrh	r2, [r3, #8]
	str	r3, [sp, #12]
	ldr	r3, [sp, #20]
	cmp	r2, r6
	beq	.L2613
	mov	r2, r3
	mov	r1, r7
	ldr	r0, .L2619+56
	bl	printf
	movs	r3, #4
	ldr	r1, [r8, #12]
	mov	r2, r3
	ldr	r0, .L2619+60
	bl	rknand_print_hex
	ldr	r3, .L2619+32
	movs	r2, #4
	ldr	r1, .L2619+40
	ldr	r0, .L2619+64
	ldrh	r3, [r3]
	ldr	r1, [r1]
	bl	rknand_print_hex
	ldr	r3, .L2619+68
	movs	r2, #1
	str	r2, [r3]
.L2614:
	ldr	r3, [sp, #12]
	ldrh	r3, [r3, #8]
	cmp	r3, r6
	beq	.L2615
	ldr	r1, .L2619+36
	mov	r2, #624
	ldr	r0, .L2619+12
	bl	printf
	ldr	r1, .L2619+16
	ldr	r0, .L2619+20
	bl	printf
.L2615:
	ldr	r3, .L2619+24
	movs	r1, #0
	ldr	r3, [r3]
	adds	r2, r3, r4
	str	r1, [r2, #4]
	strh	r6, [r3, r4]	@ movhi
	b	.L2606
.L2613:
	ldr	r2, [r8]
	cmp	r2, #256
	bne	.L2614
	mov	r2, r3
	mov	r1, r7
	ldr	r0, .L2619+72
	bl	printf
	ldr	r3, [r5]
	mov	r1, r7
	ldr	r0, .L2619+76
	add	r3, r3, r4
	ldr	r2, [r3, #8]
	bl	FtlMapWritePage
	b	.L2614
.L2620:
	.align	2
.L2619:
	.word	.LANCHOR74
	.word	.LANCHOR56
	.word	.LANCHOR236
	.word	.LC5
	.word	.LC6
	.word	.LC7
	.word	.LANCHOR98
	.word	.LANCHOR67
	.word	.LANCHOR66
	.word	.LANCHOR237
	.word	.LANCHOR134
	.word	.LANCHOR57
	.word	.LANCHOR99
	.word	.LANCHOR195
	.word	.LC60
	.word	.LC28
	.word	.LC61
	.word	.LANCHOR78
	.word	.LC62
	.word	.LANCHOR130
	.word	.LANCHOR211
	.size	log2phys, .-log2phys
	.section	.text.FtlCheckVpc,"ax",%progbits
	.align	1
	.global	FtlCheckVpc
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	FtlCheckVpc, %function
FtlCheckVpc:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r0, r1, r4, r5, r6, r7, r8, r10, fp, lr}
	movs	r4, #0
	ldr	r6, .L2645
	ldr	r5, .L2645+4
	ldr	r1, .L2645+8
	ldr	r0, .L2645+12
	bl	printf
	mov	r2, #8192
	movs	r1, #0
	ldr	r0, .L2645+4
	bl	memset
.L2622:
	ldr	r3, [r6]
	cmp	r4, r3
	bcc	.L2624
	ldr	r10, .L2645+60
	movs	r4, #0
	ldr	r7, .L2645+16
	mov	r5, r4
.L2625:
	ldrh	r2, [r10]
	uxth	r3, r4
	cmp	r2, r3
	bhi	.L2627
	ldr	r3, .L2645+20
	ldr	r4, [r3]
	cbz	r4, .L2628
	ldr	r3, .L2645+24
	mov	r8, #0
	ldr	r6, .L2645+28
	ldr	r10, .L2645+16
	ldrh	r7, [r3]
	ldr	r3, [r6]
	ldr	fp, .L2645+4
	subs	r4, r4, r3
	ldr	r3, .L2645+32
	asrs	r4, r4, #1
	muls	r4, r3, r4
	uxth	r4, r4
.L2629:
	uxth	r3, r8
	cmp	r7, r3
	bls	.L2628
	ldr	r3, [r10]
	ldrh	r2, [r3, r4, lsl #1]
	cbz	r2, .L2630
	movs	r5, #1
	ldrh	r3, [fp, r4, lsl #1]
	mov	r1, r4
	ldr	r0, .L2645+36
	bl	printf
.L2630:
	movs	r3, #6
	ldr	r2, [r6]
	muls	r4, r3, r4
	movw	r3, #65535
	add	r8, r8, #1
	ldrh	r4, [r2, r4]
	cmp	r4, r3
	bne	.L2629
.L2628:
	mov	r1, r5
	ldr	r0, .L2645+40
	bl	printf
	cbz	r5, .L2621
	ldr	r1, .L2645+8
	movw	r2, #1849
	ldr	r0, .L2645+44
	bl	printf
	ldr	r1, .L2645+48
	ldr	r0, .L2645+52
	bl	printf
.L2621:
	add	sp, sp, #8
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r10, fp, pc}
.L2624:
	movs	r2, #0
	add	r1, sp, #4
	mov	r0, r4
	bl	log2phys
	ldr	r0, [sp, #4]
	adds	r3, r0, #1
	beq	.L2623
	ubfx	r0, r0, #10, #16
	bl	P2V_block_in_plane
	ldrh	r3, [r5, r0, lsl #1]
	adds	r3, r3, #1
	strh	r3, [r5, r0, lsl #1]	@ movhi
.L2623:
	adds	r4, r4, #1
	b	.L2622
.L2627:
	ldr	r3, [r7]
	uxth	r6, r4
	ldr	r8, .L2645+4
	ldrh	r2, [r3, r6, lsl #1]
	ldrh	r3, [r8, r6, lsl #1]
	cmp	r2, r3
	beq	.L2626
	mov	r1, r6
	ldr	r0, .L2645+56
	bl	printf
	ldr	r3, [r7]
	movw	r2, #65535
	ldrh	r3, [r3, r6, lsl #1]
	cmp	r3, r2
	beq	.L2626
	ldrh	r2, [r8, r6, lsl #1]
	cmp	r2, r3
	it	hi
	movhi	r5, #1
.L2626:
	adds	r4, r4, #1
	b	.L2625
.L2646:
	.align	2
.L2645:
	.word	.LANCHOR74
	.word	check_valid_page_count_table
	.word	.LANCHOR238
	.word	.LC48
	.word	.LANCHOR85
	.word	.LANCHOR89
	.word	.LANCHOR90
	.word	.LANCHOR83
	.word	-1431655765
	.word	.LC64
	.word	.LC65
	.word	.LC5
	.word	.LC6
	.word	.LC7
	.word	.LC63
	.word	.LANCHOR40
	.size	FtlCheckVpc, .-FtlCheckVpc
	.section	.text.Ftlscanalldata,"ax",%progbits
	.align	1
	.global	Ftlscanalldata
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	Ftlscanalldata, %function
Ftlscanalldata:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, r8, lr}
	movs	r5, #0
	ldr	r7, .L2661
	sub	sp, sp, #32
	movs	r1, #0
	ldr	r8, .L2661+24
	ldr	r0, .L2661+4
	bl	printf
.L2648:
	ldr	r3, [r7]
	cmp	r5, r3
	bcc	.L2654
	add	sp, sp, #32
	@ sp needed
	pop	{r4, r5, r6, r7, r8, pc}
.L2654:
	movs	r2, #0
	add	r1, sp, #28
	mov	r0, r5
	bl	log2phys
	ubfx	r3, r5, #0, #11
	cbnz	r3, .L2649
	ldr	r2, [sp, #28]
	mov	r1, r5
	mov	r0, r8
	bl	printf
.L2649:
	ldr	r3, [sp, #28]
	adds	r2, r3, #1
	beq	.L2651
	ldr	r4, .L2661+8
	movs	r2, #0
	movs	r1, #1
	str	r3, [r4, #4]
	mov	r0, r4
	ldr	r3, .L2661+12
	str	r5, [r4, #16]
	str	r2, [r4]
	ldr	r3, [r3]
	str	r3, [r4, #8]
	ldr	r3, .L2661+16
	ldr	r6, [r3]
	str	r6, [r4, #12]
	bl	FlashReadPages
	ldr	r3, [r4]
	cmp	r3, #256
	beq	.L2652
	adds	r3, r3, #1
	beq	.L2652
	ldr	r3, [r6, #8]
	cmp	r5, r3
	beq	.L2651
.L2652:
	ldr	r2, [r4, #8]
	ldr	r3, [r4, #12]
	ldr	r0, .L2661+20
	ldr	r1, [r2, #4]
	str	r1, [sp, #16]
	mov	r1, r5
	ldr	r2, [r2]
	str	r2, [sp, #12]
	ldr	r2, [r3, #12]
	str	r2, [sp, #8]
	ldr	r2, [r3, #8]
	str	r2, [sp, #4]
	ldr	r2, [r3, #4]
	str	r2, [sp]
	ldr	r2, [r4, #4]
	ldr	r3, [r3]
	bl	printf
.L2651:
	adds	r5, r5, #1
	b	.L2648
.L2662:
	.align	2
.L2661:
	.word	.LANCHOR74
	.word	.LC66
	.word	.LANCHOR211
	.word	.LANCHOR189
	.word	.LANCHOR195
	.word	.LC68
	.word	.LC67
	.size	Ftlscanalldata, .-Ftlscanalldata
	.section	.text.FtlReUsePrevPpa,"ax",%progbits
	.align	1
	.global	FtlReUsePrevPpa
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	FtlReUsePrevPpa, %function
FtlReUsePrevPpa:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r0, r1, r4, r5, r6, r7, r8, lr}
	mov	r6, r0
	ldr	r5, .L2673
	ubfx	r0, r1, #10, #16
	str	r1, [sp, #4]
	bl	P2V_block_in_plane
	ldr	r2, [r5]
	mov	r7, r0
	ldrh	r3, [r2, r0, lsl #1]
	cmp	r3, #0
	bne	.L2664
	ldr	r2, .L2673+4
	ldr	r4, [r2]
	cmp	r4, #0
	beq	.L2665
	ldr	r2, .L2673+8
	movw	lr, #65535
	ldr	ip, .L2673+32
	ldr	r0, .L2673+12
	ldr	r2, [r2]
	ldrh	r1, [r0]
	mov	r8, r0
	subs	r4, r4, r2
	asrs	r4, r4, #1
	mul	r4, ip, r4
	mov	ip, #6
	uxth	r4, r4
.L2666:
	uxth	r0, r3
	cmp	r1, r0
	bls	.L2665
	cmp	r4, r7
	bne	.L2667
	mov	r1, r4
	ldr	r0, .L2673+4
	bl	List_remove_node
	ldrh	r3, [r8]
	cbnz	r3, .L2668
	ldr	r1, .L2673+16
	movw	r2, #2271
	ldr	r0, .L2673+20
	bl	printf
	ldr	r1, .L2673+24
	ldr	r0, .L2673+28
	bl	printf
.L2668:
	ldrh	r3, [r8]
	mov	r0, r4
	subs	r3, r3, #1
	strh	r3, [r8]	@ movhi
	bl	INSERT_DATA_LIST
	ldr	r2, [r5]
	ldrh	r3, [r2, r7, lsl #1]
.L2664:
	adds	r3, r3, #1
	strh	r3, [r2, r7, lsl #1]	@ movhi
	b	.L2665
.L2667:
	mul	r4, ip, r4
	adds	r3, r3, #1
	ldrh	r4, [r2, r4]
	cmp	r4, lr
	bne	.L2666
.L2665:
	movs	r2, #1
	add	r1, sp, #4
	mov	r0, r6
	bl	log2phys
	add	sp, sp, #8
	@ sp needed
	pop	{r4, r5, r6, r7, r8, pc}
.L2674:
	.align	2
.L2673:
	.word	.LANCHOR85
	.word	.LANCHOR89
	.word	.LANCHOR83
	.word	.LANCHOR90
	.word	.LANCHOR239
	.word	.LC5
	.word	.LC6
	.word	.LC7
	.word	-1431655765
	.size	FtlReUsePrevPpa, .-FtlReUsePrevPpa
	.section	.text.FtlRecoverySuperblock,"ax",%progbits
	.align	1
	.global	FtlRecoverySuperblock
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	FtlRecoverySuperblock, %function
FtlRecoverySuperblock:
	@ args = 0, pretend = 0, frame = 56
	@ frame_needed = 0, uses_anonymous_args = 0
	ldrh	r3, [r0]
	movw	r2, #65535
	push	{r4, r5, r6, r7, r8, r10, fp, lr}
	mov	r10, r0
	sub	sp, sp, #56
	cmp	r3, r2
	beq	.L2839
	ldrh	r3, [r0, #2]
	str	r3, [sp, #12]
	ldrb	r3, [r0, #6]	@ zero_extendqisi2
	ldr	r1, [sp, #12]
	str	r3, [sp, #28]
	ldr	r3, .L2848
	ldrh	r3, [r3]
	cmp	r3, r1
	mov	r3, #0
	bne	.L2678
	strh	r3, [r0, #4]	@ movhi
.L2846:
	strb	r3, [r10, #6]
.L2839:
	movs	r0, #0
	add	sp, sp, #56
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r10, fp, pc}
.L2678:
	ldrh	r0, [r0, #16]
.L2679:
	cmp	r0, r2
	uxth	r5, r3
	add	r3, r3, #1
	beq	.L2680
	ldrb	r1, [r10, #8]	@ zero_extendqisi2
	cmp	r1, #1
	bne	.L2681
	bl	FtlGetLastWrittenPage
	adds	r6, r0, #1
	mov	r4, r0
	beq	.L2682
	ldr	r3, .L2848+4
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L2760
	ldr	r3, .L2848+8
	ldrh	r5, [r3, r0, lsl #1]
.L2683:
	ldr	r3, .L2848+12
	movw	r8, #65535
	mov	fp, #36
	ldrh	ip, [r3]
	ldr	r3, .L2848+16
	ldr	r0, [r3]
	ldr	r3, .L2848+20
	ldr	r3, [r3]
	str	r3, [sp, #8]
	ldr	r3, .L2848+24
	ldrh	lr, [r3]
	add	r3, r10, #16
	str	r3, [sp, #20]
	str	r3, [sp, #4]
	movs	r3, #0
	mov	r6, r3
.L2684:
	uxth	r2, r3
	cmp	ip, r2
	bhi	.L2688
	ldrb	r3, [r10, #8]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L2761
	ldr	r3, .L2848+4
	ldrb	r3, [r3]	@ zero_extendqisi2
	adds	r3, r3, #0
	it	ne
	movne	r3, #1
.L2840:
	str	r3, [sp, #36]
	mov	r1, r6
	ldr	r2, [sp, #36]
	movs	r7, #0
	bl	FlashReadPages
	ldr	r3, .L2848+28
	movw	fp, #65535
	ldr	r8, .L2848+16
	ldr	r3, [r3]
	subs	r3, r3, #1
	str	r3, [sp, #4]
.L2690:
	uxth	r3, r7
	cmp	r6, r3
	bhi	.L2695
	bne	.L2693
	adds	r4, r4, #1
	uxth	r3, r4
	str	r3, [sp, #8]
	ldr	r3, [r8]
	ldr	r0, [r3, #4]
.L2841:
	ubfx	r0, r0, #10, #16
	bl	P2V_plane
	ldrb	r3, [r10, #8]	@ zero_extendqisi2
	str	r0, [sp, #16]
	cmp	r3, #1
	bne	.L2697
	ldr	r2, .L2848+4
	ldrb	r2, [r2]	@ zero_extendqisi2
	cbnz	r2, .L2697
	ldr	r1, [sp, #8]
	ldr	r2, .L2848+8
	ldrh	r2, [r2, r1, lsl #1]
	str	r2, [sp, #8]
.L2697:
	ldr	r2, .L2848
	ldr	r1, [sp, #8]
	ldrh	r2, [r2]
	cmp	r2, r1
	bne	.L2698
	ldrh	r2, [sp, #8]
	strh	r2, [r10, #2]	@ movhi
	movs	r2, #0
	strb	r2, [r10, #6]
	strh	r2, [r10, #4]	@ movhi
.L2698:
	ldr	r2, [sp, #8]
	ldr	r1, [sp, #12]
	cmp	r2, r1
	bne	.L2699
	ldr	r2, [sp, #16]
	ldr	r1, [sp, #28]
	cmp	r2, r1
	bne	.L2699
.L2847:
	ldr	r1, [sp, #8]
	mov	r0, r10
	bl	ftl_sb_update_avl_pages
	b	.L2839
.L2680:
	uxth	r1, r3
	adds	r1, r1, #8
	ldrh	r0, [r10, r1, lsl #1]
	b	.L2679
.L2681:
	movs	r1, #0
	bl	FtlGetLastWrittenPage
	mov	r4, r0
	adds	r0, r0, #1
	beq	.L2682
.L2760:
	mov	r5, r4
	b	.L2683
.L2682:
	ldr	r3, [sp, #12]
	cbz	r3, .L2685
	ldr	r1, .L2848+32
	movw	r2, #2350
	ldr	r0, .L2848+36
	bl	printf
	ldr	r1, .L2848+40
	ldr	r0, .L2848+44
	bl	printf
.L2685:
	ldr	r3, [sp, #28]
	cbz	r3, .L2686
	cmp	r5, r3
	beq	.L2686
	ldr	r1, .L2848+32
	movw	r2, #2351
	ldr	r0, .L2848+36
	bl	printf
	ldr	r1, .L2848+40
	ldr	r0, .L2848+44
	bl	printf
.L2686:
	movs	r3, #0
	strh	r3, [r10, #2]	@ movhi
	b	.L2846
.L2688:
	ldr	r1, [sp, #4]
	ldrh	r2, [r1], #2
	cmp	r2, r8
	str	r1, [sp, #4]
	beq	.L2687
	mla	r1, fp, r6, r0
	orr	r2, r5, r2, lsl #10
	str	r2, [r1, #4]
	movs	r2, #0
	str	r2, [r1, #8]
	mul	r2, lr, r6
	adds	r6, r6, #1
	uxth	r6, r6
	bic	r2, r2, #3
	mov	r7, r2
	ldr	r2, [sp, #8]
	add	r7, r7, r2
	str	r7, [r1, #12]
.L2687:
	adds	r3, r3, #1
	b	.L2684
.L2761:
	movs	r3, #0
	b	.L2840
.L2695:
	movs	r3, #36
	ldr	r1, [r8]
	muls	r3, r7, r3
	adds	r2, r1, r3
	ldr	r3, [r1, r3]
	cbnz	r3, .L2691
	ldr	r2, [r2, #12]
	ldr	r3, [r2, #4]
	adds	r1, r3, #1
	beq	.L2692
	ldr	r1, .L2848+28
	mov	r0, r3
	ldr	r1, [r1]
	bl	ftl_cmp_data_ver
	cbz	r0, .L2692
	ldr	r1, .L2848+28
	adds	r3, r3, #1
	str	r3, [r1]
.L2692:
	ldr	r3, [r2]
	adds	r3, r3, #1
	bne	.L2694
.L2693:
	uxth	r3, r4
	uxth	r7, r7
	str	r3, [sp, #8]
	movs	r2, #36
	ldr	r3, [r8]
	mla	r7, r2, r7, r3
	ldr	r0, [r7, #4]
	b	.L2841
.L2691:
	ldr	r1, [r2, #4]
	uxth	fp, r5
	ldr	r0, .L2848+48
	bl	printf
	ldrh	r2, [r10]
	ldr	r3, .L2848+52
	strh	r2, [r3]	@ movhi
.L2694:
	adds	r7, r7, #1
	b	.L2690
.L2699:
	movw	r2, #65535
	cmp	fp, r2
	bne	.L2700
	cmp	r3, #0
	bne	.L2701
.L2700:
	ldr	r3, .L2848+56
	uxth	fp, r5
	uxth	r5, r5
	mov	r7, #-1
	mov	r6, r7
	ldr	r2, [r3]
	adds	r2, r2, #1
	itt	eq
	ldreq	r2, [sp, #4]
	streq	r2, [r3]
	ldr	r3, [r3]
	str	r3, [sp, #24]
	ldr	r3, [sp, #12]
	adds	r3, r3, #7
	cmp	r5, r3
	itet	gt
	subgt	r4, fp, #7
	ldrle	r4, [sp, #12]
	uxthgt	r4, r4
.L2704:
	cmp	r4, fp
	bhi	.L2719
	ldr	r3, .L2848+12
	movw	lr, #65535
	mov	ip, #36
	ldrh	r8, [r3]
	ldr	r3, .L2848+16
	ldr	r0, [r3]
	ldr	r3, [sp, #20]
	str	r3, [sp, #32]
	movs	r3, #0
	mov	r5, r3
	b	.L2720
.L2706:
	ldr	r1, [sp, #32]
	ldrh	r2, [r1], #2
	cmp	r2, lr
	str	r1, [sp, #32]
	beq	.L2705
	mla	r1, ip, r5, r0
	adds	r5, r5, #1
	orr	r2, r4, r2, lsl #10
	uxth	r5, r5
	str	r2, [r1, #4]
.L2705:
	adds	r3, r3, #1
.L2720:
	uxth	r2, r3
	cmp	r8, r2
	bhi	.L2706
	mov	r1, r5
	ldr	r2, [sp, #36]
	bl	FlashReadPages
	ldr	r2, .L2848+4
	movs	r1, #36
	ldr	r3, .L2848+56
	movs	r0, #0
	movw	ip, #65535
	ldrb	lr, [r2]	@ zero_extendqisi2
	ldr	r2, .L2848+16
	ldr	r3, [r3]
	ldr	r2, [r2]
	mla	r5, r1, r5, r2
.L2707:
	cmp	r5, r2
	bne	.L2717
	cbz	r0, .L2718
	ldr	r2, .L2848+56
	str	r3, [r2]
.L2718:
	adds	r4, r4, #1
	uxth	r4, r4
	b	.L2704
.L2849:
	.align	2
.L2848:
	.word	.LANCHOR52
	.word	.LANCHOR16
	.word	.LANCHOR17
	.word	.LANCHOR38
	.word	.LANCHOR186
	.word	.LANCHOR108
	.word	.LANCHOR58
	.word	.LANCHOR165
	.word	.LANCHOR240
	.word	.LC5
	.word	.LC6
	.word	.LC7
	.word	.LC69
	.word	.LANCHOR241
	.word	.LANCHOR139
.L2717:
	ldr	r1, [r2]
	cbnz	r1, .L2708
	ldr	r1, [r2, #12]
	ldrh	r8, [r1]
	cmp	r8, ip
	beq	.L2764
	ldr	r1, [r1, #4]
	cmp	r1, #-1
	beq	.L2764
	adds	r0, r7, #1
	bne	.L2766
	ldr	r0, .L2850
	ldrh	r0, [r0, r4, lsl #1]
	cmp	r0, ip
	bne	.L2710
	cmp	lr, #0
	beq	.L2766
.L2710:
	ldr	r0, [sp, #4]
	cmp	r0, r3
	it	ne
	movne	r7, r3
.L2766:
	movs	r0, #1
	b	.L2709
.L2708:
	cbz	r0, .L2711
	ldr	r2, .L2850+4
	str	r3, [r2]
.L2711:
	ldr	r3, .L2850+8
	ldrh	r2, [r10]
	strh	r2, [r3]	@ movhi
	ldrb	r3, [r10, #8]	@ zero_extendqisi2
	cbnz	r3, .L2701
	ldr	r3, .L2850
	ldrh	r2, [r3, r4, lsl #1]
	movw	r3, #65535
	cmp	r2, r3
	bne	.L2713
	adds	r1, r7, #1
	ldr	r3, .L2850+4
	beq	.L2714
	str	r7, [r3]
.L2701:
	ldr	fp, [sp, #12]
	movs	r2, #1
	ldr	r6, .L2850+12
	ldr	r3, .L2850+16
	strh	r2, [r3]	@ movhi
.L2721:
	ldr	r3, .L2850+20
	movw	ip, #65535
	ldr	r0, [r6]
	mov	lr, #36
	ldr	r1, [sp, #20]
	movs	r2, #0
	ldrh	r5, [r3]
	ldr	r3, .L2850+24
	str	r2, [sp, #24]
	ldrb	r7, [r3]	@ zero_extendqisi2
.L2722:
	uxth	r3, r2
	cmp	r3, r5
	bcc	.L2725
	ldr	r2, [sp, #36]
	ldr	r1, [sp, #24]
	bl	FlashReadPages
	movs	r3, #0
.L2845:
	str	r3, [sp, #32]
	ldr	r2, [sp, #24]
	ldrh	r3, [sp, #32]
	cmp	r2, r3
	bhi	.L2754
	ldrb	r3, [r10, #8]	@ zero_extendqisi2
	add	fp, fp, #1
	uxth	fp, fp
	cmp	r3, #1
	bne	.L2755
	ldr	r3, .L2850+24
	ldrb	r3, [r3]	@ zero_extendqisi2
	cbz	r3, .L2755
	ldr	r3, .L2850+28
	ldrh	r3, [r3]
	cmp	r3, fp
	bne	.L2755
	ldr	r3, [sp, #8]
	cmp	r3, fp
	beq	.L2730
.L2755:
	ldr	r3, .L2850+32
	ldrh	r3, [r3]
	cmp	r3, fp
	bne	.L2721
	ldr	r2, .L2850+20
	movw	r0, #65535
	movs	r3, #0
	strh	fp, [r10, #2]	@ movhi
	strh	r3, [r10, #4]	@ movhi
	ldrh	r2, [r2]
.L2756:
	uxth	r1, r3
	cmp	r1, r2
	bcs	.L2839
	ldr	r1, [sp, #20]
	ldrh	r4, [r1], #2
	cmp	r4, r0
	str	r1, [sp, #20]
	add	r1, r3, #1
	bne	.L2846
	mov	r3, r1
	b	.L2756
.L2714:
	ldr	r2, [sp, #4]
	ldr	r1, [sp, #24]
	cmp	r2, r1
	itet	eq
	ldreq	r2, [r3]
	movne	r2, r1
	addeq	r2, r2, #-1
.L2842:
	str	r2, [r3]
	b	.L2701
.L2713:
	ldr	r3, [sp, #4]
	cmp	r6, r3
	beq	.L2716
	adds	r2, r6, #1
	beq	.L2701
	ldr	r3, .L2850+4
	str	r6, [r3]
	b	.L2701
.L2716:
	ldr	r2, .L2850+4
	ldr	r1, [sp, #4]
	ldr	r3, [r2]
	cmp	r1, r3
	beq	.L2701
	subs	r3, r3, #1
	str	r3, [r2]
	b	.L2701
.L2764:
	mov	r1, r3
	mov	r3, r6
.L2709:
	mov	r6, r3
	adds	r2, r2, #36
	mov	r3, r1
	b	.L2707
.L2719:
	mov	r2, #-1
	ldr	r3, .L2850+4
	b	.L2842
.L2725:
	ldrh	r3, [r1], #2
	cmp	r3, ip
	beq	.L2723
	ldr	r4, [sp, #24]
	orr	r3, fp, r3, lsl #10
	mla	r4, lr, r4, r0
	str	r3, [r4, #4]
	ldrb	r8, [r10, #8]	@ zero_extendqisi2
	cmp	r8, #1
	bne	.L2724
	cbz	r7, .L2724
	orr	r3, r3, #-2147483648
	str	r3, [r4, #4]
.L2724:
	ldr	r3, [sp, #24]
	adds	r3, r3, #1
	uxth	r3, r3
	str	r3, [sp, #24]
.L2723:
	adds	r2, r2, #1
	b	.L2722
.L2754:
	ldr	r3, [sp, #32]
	movs	r5, #36
	ldr	r8, [r6]
	muls	r5, r3, r5
	add	r7, r8, r5
	ldr	r4, [r7, #4]
	ubfx	r0, r4, #10, #16
	str	r4, [sp, #52]
	bl	P2V_plane
	ldr	r3, [sp, #12]
	cmp	fp, r3
	bcc	.L2727
	bne	.L2728
	ldr	r3, [sp, #28]
	cmp	r3, r0
	bhi	.L2727
.L2728:
	ldr	r3, [sp, #8]
	cmp	fp, r3
	bne	.L2729
	ldr	r3, [sp, #16]
	cmp	r3, r0
	beq	.L2730
.L2729:
	ldr	r3, [r8, r5]
	adds	r3, r3, #1
	beq	.L2731
	ldr	r3, [r7, #12]
	movw	r2, #61589
	ldrh	r1, [r3]
	cmp	r1, r2
	beq	.L2732
	ldrh	r0, [r10]
.L2843:
	bl	decrement_vpc_count
	b	.L2727
.L2732:
	ldr	r2, [r3, #4]
	str	r2, [sp, #4]
	adds	r2, r2, #1
	beq	.L2733
	ldr	r2, .L2850+36
	ldr	r0, [sp, #4]
	ldr	r1, [r2]
	bl	ftl_cmp_data_ver
	cbz	r0, .L2733
	ldr	r1, [sp, #4]
	adds	r1, r1, #1
	str	r1, [r2]
.L2733:
	ldr	r4, [r3, #8]
	add	r1, sp, #48
	ldr	r3, [r3, #12]
	movs	r2, #0
	mov	r0, r4
	str	r3, [sp, #44]
	bl	log2phys
	ldr	r3, .L2850+4
	ldr	r1, [r3]
	adds	r3, r1, #1
	beq	.L2734
	ldr	r0, [sp, #4]
	bl	ftl_cmp_data_ver
	cmp	r0, #0
	beq	.L2734
	ldr	r3, [sp, #44]
	adds	r7, r3, #1
	beq	.L2735
	ldr	r0, [r6]
	movs	r2, #0
	movs	r1, #1
	add	r0, r0, r5
	str	r3, [r0, #4]
	ldr	r7, [r0, #12]
	bl	FlashReadPages
	ldr	r2, [r6]
	ldr	r1, [r2, r5]
	adds	r3, r2, r5
	adds	r1, r1, #1
	bne	.L2736
.L2737:
	mov	r3, #-1
	str	r3, [sp, #44]
.L2744:
	ldr	r7, [sp, #44]
	adds	r0, r7, #1
	beq	.L2727
.L2759:
	ubfx	r0, r7, #10, #16
	bl	P2V_block_in_plane
	ldr	r3, .L2850+40
	mov	r4, r0
	ldrh	r3, [r3]
	cmp	r3, r0
	bhi	.L2750
	ldr	r1, .L2850+44
	movw	r2, #2683
	ldr	r0, .L2850+48
	bl	printf
	ldr	r1, .L2850+52
	ldr	r0, .L2850+56
	bl	printf
.L2750:
	ldr	r3, .L2850+60
	ldr	r3, [r3]
	ldrh	r3, [r3, r4, lsl #1]
	cmp	r3, #0
	beq	.L2751
	mov	r0, r4
	b	.L2843
.L2735:
	ldr	r3, [sp, #52]
	ldr	r2, [sp, #48]
	cmp	r2, r3
	bne	.L2727
	movs	r2, #1
	add	r1, sp, #44
	mov	r0, r4
	bl	log2phys
.L2727:
	ldr	r3, [sp, #32]
	adds	r3, r3, #1
	b	.L2845
.L2736:
	ldr	r1, [r7, #8]
	cmp	r4, r1
	bne	.L2737
	ldr	r8, [r7, #4]
	ldr	r0, .L2850+4
	mov	r1, r8
	ldr	r0, [r0]
	bl	ftl_cmp_data_ver
	cmp	r0, #0
	beq	.L2737
	ldr	r1, [sp, #48]
	ldr	r0, [sp, #52]
	cmp	r1, r0
	bne	.L2739
.L2742:
	ldr	r1, [sp, #44]
	mov	r0, r4
	bl	FtlReUsePrevPpa
	b	.L2737
.L2851:
	.align	2
.L2850:
	.word	.LANCHOR123
	.word	.LANCHOR139
	.word	.LANCHOR241
	.word	.LANCHOR186
	.word	.LANCHOR242
	.word	.LANCHOR38
	.word	.LANCHOR16
	.word	.LANCHOR53
	.word	.LANCHOR52
	.word	.LANCHOR165
	.word	.LANCHOR40
	.word	.LANCHOR240
	.word	.LC5
	.word	.LC6
	.word	.LC7
	.word	.LANCHOR85
.L2739:
	ldr	r0, [sp, #44]
	cmp	r1, r0
	beq	.L2737
	adds	r0, r1, #1
	beq	.L2740
	str	r1, [r3, #4]
	movs	r2, #0
	movs	r1, #1
	mov	r0, r3
	ldr	r7, [r3, #12]
	bl	FlashReadPages
.L2741:
	ldr	r3, [r6]
	ldr	r3, [r3, r5]
	adds	r3, r3, #1
	beq	.L2742
	ldr	r3, [r7, #4]
	ldr	r2, .L2852
	mov	r1, r3
	ldr	r0, [r2]
	bl	ftl_cmp_data_ver
	cmp	r0, #0
	beq	.L2742
	mov	r1, r3
	mov	r0, r8
	bl	ftl_cmp_data_ver
	cmp	r0, #0
	beq	.L2737
	b	.L2742
.L2740:
	str	r1, [r2, r5]
	b	.L2741
.L2734:
	ldr	r3, [sp, #52]
	ldr	r2, [sp, #48]
	cmp	r2, r3
	beq	.L2744
	ldr	r3, [sp, #44]
	adds	r7, r3, #1
	beq	.L2746
	ldr	r2, .L2852+4
	ubfx	r3, r3, #10, #21
	ldr	r2, [r2]
	cmp	r3, r2
	bcs	.L2727
.L2746:
	movs	r2, #1
	add	r1, sp, #52
	mov	r0, r4
	bl	log2phys
	ldr	r7, [sp, #48]
	adds	r5, r7, #1
	beq	.L2744
	ldr	r3, [sp, #44]
	cmp	r7, r3
	beq	.L2759
	ubfx	r0, r7, #10, #16
	bl	P2V_block_in_plane
	ldr	r3, .L2852+8
	ldrh	r3, [r3]
	cmp	r3, r0
	beq	.L2749
	ldr	r3, .L2852+12
	ldrh	r3, [r3]
	cmp	r3, r0
	beq	.L2749
	ldr	r3, .L2852+16
	ldrh	r3, [r3]
	cmp	r3, r0
	bne	.L2744
.L2749:
	ldr	r0, [r6]
	movs	r2, #0
	movs	r1, #1
	str	r7, [r0, #4]
	ldr	r5, [r0, #12]
	bl	FlashReadPages
	ldr	r3, [r6]
	ldr	r3, [r3]
	adds	r3, r3, #1
	beq	.L2744
	ldr	r1, [r5, #4]
	ldr	r0, [sp, #4]
	bl	ftl_cmp_data_ver
	cmp	r0, #0
	bne	.L2744
	movs	r2, #1
	add	r1, sp, #48
	mov	r0, r4
	bl	log2phys
	b	.L2744
.L2751:
	mov	r1, r4
	ldr	r0, .L2852+20
	bl	printf
	b	.L2727
.L2731:
	ldrh	r3, [r10]
	mov	r1, r4
	ldr	r2, .L2852+24
	ldr	r0, .L2852+28
	strh	r3, [r2]	@ movhi
	ldr	r2, [sp, #4]
	bl	printf
	ldr	r2, .L2852+32
	ldr	r3, [r2]
	cmp	r3, #31
	bhi	.L2752
	ldr	r0, [sp, #52]
	ldr	r1, .L2852+36
	str	r0, [r1, r3, lsl #2]
	adds	r3, r3, #1
	str	r3, [r2]
.L2752:
	ldrh	r0, [r10]
	bl	decrement_vpc_count
	ldr	r3, .L2852
	ldr	r2, [r3]
	adds	r1, r2, #1
	bne	.L2753
	ldr	r2, [sp, #4]
.L2844:
	str	r2, [r3]
	b	.L2727
.L2753:
	ldr	r1, [sp, #4]
	cmp	r1, r2
	bcs	.L2727
	mov	r2, r1
	b	.L2844
.L2730:
	ldrb	r3, [sp, #16]	@ zero_extendqisi2
	ldr	r2, [sp, #16]
	strb	r3, [r10, #6]
	ldrh	r3, [sp, #8]
	strh	r3, [r10, #2]	@ movhi
	b	.L2847
.L2853:
	.align	2
.L2852:
	.word	.LANCHOR139
	.word	.LANCHOR43
	.word	.LANCHOR93
	.word	.LANCHOR94
	.word	.LANCHOR95
	.word	.LC70
	.word	.LANCHOR241
	.word	.LC71
	.word	.LANCHOR243
	.word	.LANCHOR244
	.size	FtlRecoverySuperblock, .-FtlRecoverySuperblock
	.section	.text.FtlGcScanTempBlk,"ax",%progbits
	.align	1
	.global	FtlGcScanTempBlk
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	FtlGcScanTempBlk, %function
FtlGcScanTempBlk:
	@ args = 0, pretend = 0, frame = 64
	@ frame_needed = 0, uses_anonymous_args = 0
	ldr	r3, .L2899
	push	{r4, r5, r6, r7, r8, r10, fp, lr}
	mov	r4, r0
	sub	sp, sp, #64
	ldrh	r5, [r3]
	movw	r3, #65535
	cmp	r5, r3
	beq	.L2883
	cbnz	r5, .L2855
.L2856:
	bl	FtlGcPageVarInit
	b	.L2857
.L2883:
	movs	r5, #0
.L2855:
	ldr	r3, .L2899+4
	ldrh	r3, [r3]
	cmp	r3, r1
	beq	.L2856
.L2857:
	ldr	r8, .L2899+80
	mov	r3, #-1
	str	r3, [sp, #8]
.L2858:
	ldrh	r1, [r4]
	movw	r3, #65535
	movs	r2, #0
	strb	r2, [r4, #8]
	cmp	r1, r3
	beq	.L2859
.L2882:
	ldr	r3, .L2899+8
	movs	r2, #0
	ldr	r0, [r8]
	mov	fp, r2
	movw	lr, #65535
	mov	r10, #36
	ldrh	r3, [r3]
	str	r3, [sp, #12]
	ldr	r3, .L2899+12
	ldr	r3, [r3]
	str	r3, [sp, #16]
	ldr	r3, .L2899+16
	ldrh	r3, [r3]
	str	r3, [sp, #20]
	ldr	r3, .L2899+20
	ldr	r7, [r3]
	ldr	r3, .L2899+24
	ldrh	ip, [r3]
	add	r3, r4, #16
	str	r3, [sp, #4]
.L2860:
	ldr	r1, [sp, #12]
	uxth	r3, r2
	cmp	r1, r3
	bhi	.L2862
	mov	r10, #0
	movs	r2, #0
	mov	r1, fp
	bl	FlashReadPages
.L2863:
	uxth	r3, r10
	cmp	fp, r3
	bhi	.L2881
	ldr	r3, .L2899+4
	adds	r5, r5, #1
	uxth	r5, r5
	ldrh	r3, [r3]
	cmp	r3, r5
	bhi	.L2882
	movs	r2, #0
	b	.L2859
.L2862:
	ldr	r1, [sp, #4]
	ldrh	r3, [r1], #2
	cmp	r3, lr
	str	r1, [sp, #4]
	beq	.L2861
	mla	r1, r10, fp, r0
	orr	r3, r5, r3, lsl #10
	str	r3, [r1, #4]
	ldr	r3, [sp, #20]
	mul	r3, r3, fp
	bic	r3, r3, #3
	mov	r6, r3
	ldr	r3, [sp, #16]
	add	r6, r6, r3
	mul	r3, ip, fp
	str	r6, [r1, #8]
	bic	r3, r3, #3
	add	r3, r3, r7
	str	r3, [r1, #12]
	add	r3, fp, #1
	uxth	fp, r3
.L2861:
	adds	r2, r2, #1
	b	.L2860
.L2881:
	movs	r7, #36
	ldr	r6, [r8]
	mul	r7, r7, r10
	adds	r3, r6, r7
	ldr	r2, [r3, #4]
	str	r3, [sp, #12]
	ubfx	r0, r2, #10, #16
	str	r2, [sp, #4]
	bl	P2V_plane
	ldr	r6, [r6, r7]
	mov	r2, r0
	ldr	r3, [sp, #12]
	ldr	r3, [r3, #12]
	cmp	r6, #0
	bne	.L2864
	ldrh	r0, [r3]
	movw	r1, #65535
	cmp	r0, r1
	bne	.L2865
.L2868:
	ldr	r3, .L2899+28
	ldrb	r3, [r3]	@ zero_extendqisi2
	cbz	r3, .L2895
	ldr	r3, .L2899+32
	movs	r1, #1
	str	r1, [r3]
.L2859:
	ldr	r3, .L2899
	movw	r1, #65535
	mov	r0, r4
	strh	r5, [r4, #2]	@ movhi
	strb	r2, [r4, #6]
	strh	r1, [r3]	@ movhi
	mov	r1, r5
	bl	ftl_sb_update_avl_pages
	ldr	r0, [sp, #8]
	add	sp, sp, #64
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r10, fp, pc}
.L2865:
	ldr	r1, .L2899+36
	ldr	r0, [r3, #8]
	ldr	r1, [r1]
	cmp	r0, r1
	bhi	.L2868
	ldr	r2, .L2899+40
	ldrb	r2, [r2]	@ zero_extendqisi2
	cbnz	r2, .L2871
.L2872:
	ldr	r2, [r3, #8]
	add	r10, r10, #1
	ldr	r1, [sp, #4]
	ldr	r0, [r3, #12]
	bl	FtlGcUpdatePage
	b	.L2863
.L2895:
	ldr	r2, .L2899+44
	ldrh	r1, [r4]
	ldr	r2, [r2]
	strh	r3, [r2, r1, lsl #1]	@ movhi
.L2898:
	ldrh	r0, [r4]
	bl	INSERT_FREE_LIST
	ldr	r2, .L2899+48
	movw	r3, #65535
	strh	r3, [r4]	@ movhi
	strh	r3, [r2]	@ movhi
.L2897:
	bl	FtlGcPageVarInit
	movs	r5, #0
	b	.L2858
.L2871:
	mov	r2, r6
	add	r1, sp, #24
	str	r3, [sp, #12]
	bl	log2phys
	ldr	r3, [sp, #12]
	ldr	r1, [sp, #24]
	ldr	r2, [r3, #12]
	cmp	r2, r1
	bne	.L2872
	adds	r1, r2, #1
	beq	.L2872
	str	r2, [sp, #32]
	movs	r1, #1
	ldr	r2, .L2899+52
	add	r0, sp, #28
	ldr	r2, [r2]
	str	r2, [sp, #36]
	ldr	r2, .L2899+56
	ldr	r2, [r2]
	str	r2, [sp, #40]
	mov	r2, r6
	bl	FlashReadPages
	ldr	r2, .L2899+60
	ldr	r1, [r8]
	ldr	r0, [sp, #36]
	ldrh	r2, [r2]
	ldr	r3, [sp, #12]
	add	r7, r7, r1
	lsl	ip, r2, #7
.L2873:
	cmp	r6, ip
	beq	.L2872
	ldr	r1, [r7, #8]
	ldr	r2, [r0, r6, lsl #2]
	ldr	r1, [r1, r6, lsl #2]
	cmp	r1, r2
	beq	.L2874
	ldr	r2, [sp, #32]
	ldrh	r1, [r4]
	ldr	r0, .L2899+64
	bl	printf
	ldr	r3, .L2899+44
	movs	r1, #0
	ldrh	r2, [r4]
	ldr	r3, [r3]
	strh	r1, [r3, r2, lsl #1]	@ movhi
	b	.L2898
.L2874:
	adds	r6, r6, #1
	b	.L2873
.L2864:
	ldr	r2, [sp, #4]
	ldrh	r1, [r4]
	ldr	r0, .L2899+68
	bl	printf
	ldr	r3, .L2899+72
	ldrh	r2, [r4]
	ldr	r3, [r3]
	cbnz	r3, .L2877
	ldr	r3, .L2899+28
	ldrb	r3, [r3]	@ zero_extendqisi2
	cbz	r3, .L2878
.L2877:
	ldr	r3, .L2899+76
	ldr	r3, [r3]
	ldrh	r3, [r3, r2, lsl #1]
	cmp	r3, #159
	bls	.L2879
.L2878:
	ldr	r3, [r8]
	ldr	r3, [r3, r7]
	adds	r3, r3, #1
	bne	.L2880
.L2879:
	ldr	r3, [r8]
	add	r7, r7, r3
	ldr	r3, [r7, #4]
	str	r3, [sp, #8]
.L2880:
	ldr	r3, .L2899+44
	movs	r1, #0
	ldr	r3, [r3]
	strh	r1, [r3, r2, lsl #1]	@ movhi
	ldrh	r0, [r4]
	bl	INSERT_FREE_LIST
	movw	r3, #65535
	strh	r3, [r4]	@ movhi
	b	.L2897
.L2900:
	.align	2
.L2899:
	.word	.LANCHOR245
	.word	.LANCHOR52
	.word	.LANCHOR38
	.word	.LANCHOR107
	.word	.LANCHOR57
	.word	.LANCHOR108
	.word	.LANCHOR58
	.word	.LANCHOR16
	.word	.LANCHOR138
	.word	.LANCHOR74
	.word	.LANCHOR2
	.word	.LANCHOR85
	.word	.LANCHOR213
	.word	.LANCHOR194
	.word	.LANCHOR196
	.word	.LANCHOR55
	.word	.LC72
	.word	.LC73
	.word	.LANCHOR104
	.word	.LANCHOR80
	.word	.LANCHOR186
	.size	FtlGcScanTempBlk, .-FtlGcScanTempBlk
	.section	.text.FtlGcFreeTempBlock,"ax",%progbits
	.align	1
	.global	FtlGcFreeTempBlock
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	FtlGcFreeTempBlock, %function
FtlGcFreeTempBlock:
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r0, r1, r2, r3, r4, r5, r6, r7, r8, r10, fp, lr}
	ldr	r3, .L2925
	ldr	r3, [r3]
	cbz	r3, .L2902
.L2907:
	movs	r0, #0
.L2901:
	add	sp, sp, #16
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r10, fp, pc}
.L2902:
	ldr	r0, .L2925+4
	movw	r3, #65535
	ldr	r5, .L2925+8
	ldrh	r6, [r0]
	mov	r4, r0
	cmp	r6, r3
	beq	.L2904
	ldr	r3, .L2925+12
	ldrh	r1, [r3]
	bl	FtlGcScanTempBlk
	str	r0, [sp, #12]
	adds	r0, r0, #1
	beq	.L2904
	ldr	r3, .L2925+16
	ldr	r2, [r3]
	ldrh	r3, [r2, r6, lsl #1]
	cmp	r3, #4
	bls	.L2905
	subs	r3, r3, #5
	movs	r0, #1
	strh	r3, [r2, r6, lsl #1]	@ movhi
	bl	FtlEctTblFlush
.L2905:
	ldr	r3, [r5]
	cbnz	r3, .L2906
	ldr	r2, .L2925+20
	ldr	r0, [sp, #12]
	ldr	r3, [r2, #96]
	ubfx	r0, r0, #10, #16
	adds	r3, r3, #1
	str	r3, [r2, #96]
	bl	FtlBbmMapBadBlock
	bl	FtlBbmTblFlush
.L2906:
	movs	r3, #0
	movs	r0, #1
	str	r3, [r5]
	b	.L2901
.L2904:
	ldrh	r2, [r4]
	movs	r3, #0
	str	r3, [r5]
	movw	r3, #65535
	cmp	r2, r3
	beq	.L2907
	ldr	r6, .L2925+12
	bl	FtlCacheWriteBack
	ldrb	r0, [r4, #7]	@ zero_extendqisi2
	ldrh	r2, [r6]
	ldr	r5, .L2925+24
	muls	r2, r0, r2
	ldrh	r1, [r5]
	cmp	r1, r2
	beq	.L2908
	ldr	r1, .L2925+28
	movs	r2, #193
	ldr	r0, .L2925+32
	bl	printf
	ldr	r1, .L2925+36
	ldr	r0, .L2925+40
	bl	printf
.L2908:
	ldrh	r6, [r6]
	ldrb	r3, [r4, #7]	@ zero_extendqisi2
	ldr	r2, .L2925+44
	ldrh	r0, [r4]
	ldr	fp, .L2925+84
	smulbb	r3, r3, r6
	ldr	r1, [r2]
	movs	r6, #0
	mov	r10, r2
	strh	r3, [r1, r0, lsl #1]	@ movhi
	ldr	r1, .L2925+48
	ldrh	r3, [r5]
	ldr	r0, [r1]
	add	r3, r3, r0
	str	r3, [r1]
.L2909:
	ldrh	r2, [r5]
	uxth	r3, r6
	cmp	r2, r3
	bhi	.L2913
	movw	r0, #65535
	bl	decrement_vpc_count
	ldr	r3, .L2925+52
	ldrb	r3, [r3]	@ zero_extendqisi2
	cbz	r3, .L2914
	ldrh	r1, [r4]
	ldr	r0, .L2925+56
	bl	printf
.L2914:
	ldrh	r0, [r4]
	ldr	r3, [r10]
	ldrh	r3, [r3, r0, lsl #1]
	cmp	r3, #0
	beq	.L2915
	bl	INSERT_DATA_LIST
.L2916:
	ldr	r3, .L2925+60
	movw	r6, #65535
	strh	r6, [r4]	@ movhi
	movs	r4, #0
	strh	r4, [r5]	@ movhi
	strh	r4, [r3]	@ movhi
	bl	l2p_flush
	bl	FtlVpcTblFlush
	ldr	r3, .L2925+64
	strh	r6, [r3]	@ movhi
	ldr	r3, .L2925+68
	ldrh	r2, [r3]
	ldr	r3, .L2925+72
	ldrh	r3, [r3]
	add	r3, r3, r3, lsl #1
	cmp	r2, r3, asr #2
	ble	.L2907
	ldr	r3, .L2925+76
	movs	r2, #20
	mov	r0, r4
	strh	r2, [r3]	@ movhi
	b	.L2901
.L2913:
	uxth	r3, r6
	mov	r8, #12
	ldr	r2, [fp]
	mul	r8, r8, r3
	ldr	r3, .L2925+80
	ldr	r3, [r3]
	add	r7, r3, r8
	ldr	r0, [r7, #8]
	cmp	r0, r2
	bcc	.L2910
.L2923:
	ldrh	r0, [r4]
	b	.L2924
.L2910:
	movs	r2, #0
	add	r1, sp, #12
	str	r3, [sp, #4]
	bl	log2phys
	ldr	r3, [sp, #4]
	ldr	r2, [sp, #12]
	ldr	r0, [r3, r8]
	cmp	r0, r2
	bne	.L2912
	ubfx	r0, r0, #10, #16
	bl	P2V_block_in_plane
	movs	r2, #1
	mov	r8, r0
	adds	r1, r7, #4
	ldr	r0, [r7, #8]
	bl	log2phys
	mov	r0, r8
.L2924:
	bl	decrement_vpc_count
	b	.L2911
.L2912:
	ldr	r3, [r7, #4]
	cmp	r2, r3
	bne	.L2923
.L2911:
	adds	r6, r6, #1
	b	.L2909
.L2915:
	bl	INSERT_FREE_LIST
	b	.L2916
.L2926:
	.align	2
.L2925:
	.word	.LANCHOR78
	.word	.LANCHOR95
	.word	.LANCHOR138
	.word	.LANCHOR52
	.word	.LANCHOR80
	.word	.LANCHOR141
	.word	.LANCHOR113
	.word	.LANCHOR246
	.word	.LC5
	.word	.LC6
	.word	.LC7
	.word	.LANCHOR85
	.word	.LANCHOR166
	.word	.LANCHOR16
	.word	.LC74
	.word	.LANCHOR112
	.word	.LANCHOR213
	.word	.LANCHOR90
	.word	.LANCHOR232
	.word	.LANCHOR181
	.word	.LANCHOR114
	.word	.LANCHOR74
	.size	FtlGcFreeTempBlock, .-FtlGcFreeTempBlock
	.section	.text.FtlGcPageRecovery,"ax",%progbits
	.align	1
	.global	FtlGcPageRecovery
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	FtlGcPageRecovery, %function
FtlGcPageRecovery:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r3, r4, r5, lr}
	ldr	r4, .L2929
	ldr	r5, .L2929+4
	ldrh	r1, [r4]
	mov	r0, r5
	bl	FtlGcScanTempBlk
	ldrh	r2, [r5, #2]
	ldrh	r3, [r4]
	cmp	r2, r3
	bcc	.L2927
	ldr	r0, .L2929+8
	bl	FtlMapBlkWriteDumpData
	movs	r0, #0
	bl	FtlGcFreeTempBlock
	ldr	r3, .L2929+12
	movs	r2, #0
	str	r2, [r3]
.L2927:
	pop	{r3, r4, r5, pc}
.L2930:
	.align	2
.L2929:
	.word	.LANCHOR52
	.word	.LANCHOR95
	.word	.LANCHOR130
	.word	.LANCHOR138
	.size	FtlGcPageRecovery, .-FtlGcPageRecovery
	.section	.text.FtlPowerLostRecovery,"ax",%progbits
	.align	1
	.global	FtlPowerLostRecovery
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	FtlPowerLostRecovery, %function
FtlPowerLostRecovery:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r3, r4, r5, lr}
	movs	r4, #0
	ldr	r5, .L2932
	ldr	r3, .L2932+4
	mov	r0, r5
	str	r4, [r3]
	bl	FtlRecoverySuperblock
	mov	r0, r5
	ldr	r5, .L2932+8
	bl	FtlSlcSuperblockCheck
	mov	r0, r5
	bl	FtlRecoverySuperblock
	mov	r0, r5
	bl	FtlSlcSuperblockCheck
	bl	FtlGcPageRecovery
	movw	r0, #65535
	bl	decrement_vpc_count
	mov	r0, r4
	pop	{r3, r4, r5, pc}
.L2933:
	.align	2
.L2932:
	.word	.LANCHOR93
	.word	.LANCHOR243
	.word	.LANCHOR94
	.size	FtlPowerLostRecovery, .-FtlPowerLostRecovery
	.section	.text.FtlSysBlkInit,"ax",%progbits
	.align	1
	.global	FtlSysBlkInit
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	FtlSysBlkInit, %function
FtlSysBlkInit:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r3, r4, r5, r6, r7, lr}
	movs	r3, #0
	ldr	r4, .L2947
	movw	r5, #65535
	strh	r3, [r4]	@ movhi
	ldr	r3, .L2947+4
	strh	r5, [r3]	@ movhi
	ldr	r3, .L2947+8
	ldrh	r0, [r3]
	bl	FtlFreeSysBlkQueueInit
	bl	FtlScanSysBlk
	ldr	r3, .L2947+12
	ldrh	r3, [r3]
	cmp	r3, r5
	mov	r5, r4
	bne	.L2935
.L2937:
	mov	r4, #-1
.L2934:
	mov	r0, r4
	pop	{r3, r4, r5, r6, r7, pc}
.L2935:
	bl	FtlLoadSysInfo
	mov	r4, r0
	cmp	r0, #0
	bne	.L2937
	bl	FtlLoadMapInfo
	bl	FtlLoadVonderInfo
	bl	Ftl_load_ext_data
	bl	FtlLoadEctTbl
	bl	FtlFreeSysBLkSort
	bl	SupperBlkListInit
	bl	FtlPowerLostRecovery
	movs	r0, #1
	bl	FtlUpdateVaildLpn
	ldr	r3, .L2947+16
	movs	r0, #12
	ldrh	r1, [r3]
	ldr	r3, .L2947+20
	ldr	r2, [r3]
	mov	r3, r4
.L2938:
	cmp	r3, r1
	bge	.L2943
	mla	r6, r0, r3, r2
	ldr	r6, [r6, #4]
	cmp	r6, #0
	bge	.L2939
.L2943:
	ldr	r0, .L2947+24
	cmp	r3, r1
	ldr	r2, [r0]
	add	r2, r2, #32
	str	r2, [r0]
	bge	.L2945
.L2940:
	ldr	r3, .L2947+28
	ldr	r1, [r3]
	ldr	r3, .L2947+32
	ldrh	r0, [r3]
	ldrh	r5, [r3, #4]
	ldrh	r2, [r1, r0, lsl #1]
	subs	r2, r2, r5
	ldr	r5, .L2947+36
	strh	r2, [r1, r0, lsl #1]	@ movhi
	ldrh	r2, [r5]
	strh	r2, [r3, #2]	@ movhi
	movs	r2, #0
	strh	r2, [r3, #4]	@ movhi
	strb	r2, [r3, #6]
	ldr	r3, .L2947+40
	ldrh	r6, [r3]
	ldrh	r7, [r3, #4]
	ldrh	r0, [r1, r6, lsl #1]
	subs	r0, r0, r7
	strh	r0, [r1, r6, lsl #1]	@ movhi
	strb	r2, [r3, #6]
	ldrh	r1, [r5]
	strh	r2, [r3, #4]	@ movhi
	ldr	r2, .L2947+44
	strh	r1, [r3, #2]	@ movhi
	ldrh	r3, [r2, #30]
	adds	r3, r3, #1
	strh	r3, [r2, #30]	@ movhi
	bl	l2p_flush
	bl	FtlVpcTblFlush
.L2946:
	bl	FtlVpcTblFlush
	b	.L2934
.L2939:
	adds	r3, r3, #1
	b	.L2938
.L2945:
	ldrh	r3, [r5]
	cmp	r3, #0
	bne	.L2940
	bl	l2p_flush
	b	.L2946
.L2948:
	.align	2
.L2947:
	.word	.LANCHOR242
	.word	.LANCHOR241
	.word	.LANCHOR39
	.word	.LANCHOR218
	.word	.LANCHOR67
	.word	.LANCHOR98
	.word	.LANCHOR165
	.word	.LANCHOR85
	.word	.LANCHOR93
	.word	.LANCHOR52
	.word	.LANCHOR94
	.word	.LANCHOR82
	.size	FtlSysBlkInit, .-FtlSysBlkInit
	.section	.text.FtlLowFormat,"ax",%progbits
	.align	1
	.global	FtlLowFormat
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	FtlLowFormat, %function
FtlLowFormat:
	@ args = 0, pretend = 0, frame = 24
	@ frame_needed = 0, uses_anonymous_args = 0
	ldr	r3, .L2980
	push	{r4, r5, r6, r7, r8, r10, fp, lr}
	sub	sp, sp, #24
	ldr	r4, [r3]
	cmp	r4, #0
	bne	.L2951
	ldr	r5, .L2980+4
	mov	r1, r4
	ldr	r3, .L2980+8
	ldr	r6, .L2980+12
	ldrh	r2, [r5]
	ldr	r0, [r3]
	ldr	r7, .L2980+16
	lsls	r2, r2, #2
	bl	ftl_memset
	ldrh	r2, [r5]
	mov	r1, r4
	ldr	r3, .L2980+20
	lsls	r2, r2, #2
	ldr	r0, [r3]
	bl	ftl_memset
	ldr	r3, .L2980+24
	ldrh	r0, [r6]
	str	r4, [r7]
	str	r4, [r3]
	bl	FtlFreeSysBlkQueueInit
	bl	FtlLoadBbt
	cbz	r0, .L2952
	bl	FtlMakeBbt
.L2952:
	ldr	r3, .L2980+28
	ldr	r2, .L2980+32
	ldr	ip, .L2980+124
	ldrh	r1, [r3]
	ldr	r4, [r2]
	ldr	r2, .L2980+36
	str	r3, [sp, #12]
	lsls	r1, r1, #7
	ldr	r5, [r2]
	movs	r2, #0
.L2953:
	uxth	r3, r2
	adds	r2, r2, #1
	cmp	r3, r1
	blt	.L2954
	ldr	r3, .L2980+40
	movs	r4, #0
	ldr	r8, .L2980+128
	ldrh	r5, [r3]
	mov	r10, r8
	str	r3, [sp]
.L2955:
	ldrh	r3, [r8]
	cmp	r3, r5
	bhi	.L2956
	ldr	r5, .L2980+44
	subs	r3, r4, #2
	ldrh	r1, [r5]
	cmp	r3, r1, lsl #1
	ble	.L2957
	mov	r0, r4
	movs	r4, #0
	bl	__aeabi_uidiv
	ldr	r3, .L2980+48
	ldr	r3, [r3]
	add	r0, r0, r3
	uxth	r0, r0
	bl	FtlSysBlkNumInit
	ldrh	r0, [r6]
	bl	FtlFreeSysBlkQueueInit
	ldr	r3, [sp]
	ldrh	r6, [r3]
.L2958:
	ldrh	r3, [r10]
	cmp	r3, r6
	bhi	.L2959
.L2957:
	mov	r8, #0
	mov	r6, r8
.L2960:
	ldr	r3, [sp]
	uxth	r0, r8
	add	r8, r8, #1
	ldrh	r3, [r3]
	cmp	r3, r0
	bhi	.L2961
	ldrh	r2, [r10]
	ldr	r3, .L2980+52
	ldrh	r5, [r5]
	str	r2, [r3]
	ldr	r3, .L2980+56
	mov	r1, r5
	ldr	r3, [r3]
	mov	r0, r3
	str	r3, [sp, #16]
	bl	__aeabi_uidiv
	ldr	r1, .L2980+60
	mov	fp, r0
	ubfx	r3, fp, #5, #16
	ldr	r0, .L2980+64
	add	r2, r3, #36
	str	r3, [sp, #4]
	strh	r2, [r1]	@ movhi
	movs	r2, #24
	muls	r2, r5, r2
	str	fp, [r0]
	mov	r8, r0
	str	r1, [sp, #8]
	cmp	r6, r2
	ble	.L2962
	ldr	r3, [sp, #16]
	mov	r1, r5
	subs	r0, r3, r6
	bl	__aeabi_uidiv
	ldr	r3, [sp, #8]
	str	r0, [r8]
	lsrs	r0, r0, #5
	adds	r0, r0, #24
	strh	r0, [r3]	@ movhi
.L2962:
	ldr	r3, .L2980+68
	ldr	r3, [r3]
	cmp	r3, #1
	bne	.L2963
	ldr	r2, .L2980+60
	mov	r1, r5
	mov	r0, r6
	ldrh	r3, [r2]
	str	r2, [sp, #20]
	str	r3, [sp, #16]
	bl	__aeabi_uidiv
	ldr	r3, [sp, #16]
	ldr	r2, [sp, #20]
	uxtah	r0, r3, r0
	add	r3, r3, r0, asr #2
	strh	r3, [r2]	@ movhi
.L2963:
	ldr	r3, .L2980+72
	ldrb	r3, [r3]	@ zero_extendqisi2
	cbz	r3, .L2964
	ldr	r2, .L2980+60
	mov	r1, r5
	mov	r0, r6
	ldrh	r3, [r2]
	str	r2, [sp, #20]
	str	r3, [sp, #16]
	bl	__aeabi_uidiv
	ldr	r3, [sp, #16]
	ldr	r2, [sp, #20]
	uxtah	r0, r3, r0
	add	r3, r3, r0, asr #2
	strh	r3, [r2]	@ movhi
.L2964:
	ldr	r3, .L2980+76
	ldrh	r3, [r3]
	cbz	r3, .L2966
	ldr	r2, .L2980+60
	ldrh	r1, [r2]
	add	r1, r1, r3, lsr #1
	strh	r1, [r2]	@ movhi
	mul	r1, r5, r3
	cmp	r6, r1
	bge	.L2966
	ldr	r1, .L2980+64
	adds	r3, r3, #32
	str	fp, [r1]
	ldr	r1, [sp, #4]
	add	r1, r1, r3
	strh	r1, [r2]	@ movhi
.L2966:
	ldr	r3, [sp, #8]
	ldr	fp, .L2980+132
	ldrh	r2, [r3]
	ldr	r3, [r8]
	subs	r3, r3, r2
	muls	r5, r3, r5
	ldr	r3, .L2980+80
	ldrh	r3, [r3]
	str	r5, [fp]
	muls	r5, r3, r5
	ldr	r3, [sp, #12]
	ldrh	r3, [r3]
	str	r5, [r8]
	muls	r5, r3, r5
	ldr	r3, .L2980+84
	str	r5, [r3]
	bl	FtlBbmTblFlush
	ldr	r3, .L2980+88
	adds	r1, r4, r6
	ldr	r2, [r3]
	ldr	r3, .L2980+92
	ldrh	r3, [r3]
	add	r3, r3, r2, lsr #3
	cmp	r1, r3
	bls	.L2968
	lsrs	r2, r2, #5
	ldr	r0, .L2980+96
	bl	printf
.L2968:
	ldrh	r2, [r10]
	movs	r1, #0
	ldr	r5, .L2980+100
	movw	r6, #65535
	ldr	r4, .L2980+104
	lsls	r2, r2, #1
	ldr	r0, [r5]
	mov	r8, r4
	bl	ftl_memset
	ldr	r2, .L2980+108
	movs	r3, #0
	strh	r3, [r4, #2]	@ movhi
	movs	r1, #255
	strb	r3, [r4, #6]
	str	r3, [r2]
	ldr	r2, .L2980+112
	strh	r3, [r4]	@ movhi
	strh	r3, [r2, #2]	@ movhi
	strb	r3, [r2, #6]
	strb	r3, [r2, #8]
	movs	r3, #1
	strb	r3, [r4, #8]
	ldr	r3, [sp]
	strh	r6, [r2]	@ movhi
	ldrh	r2, [r3]
	ldr	r3, .L2980+116
	lsrs	r2, r2, #3
	ldr	r0, [r3]
	bl	ftl_memset
.L2969:
	mov	r0, r8
	bl	make_superblock
	ldrb	r3, [r4, #7]	@ zero_extendqisi2
	ldrh	r2, [r4]
	cbnz	r3, .L2970
	ldr	r3, [r5]
	strh	r6, [r3, r2, lsl #1]	@ movhi
	ldrh	r3, [r4]
	adds	r3, r3, #1
	strh	r3, [r4]	@ movhi
	b	.L2969
.L2954:
	mvns	r0, r3
	orr	r0, r3, r0, lsl #16
	str	r0, [r4, r3, lsl #2]
	str	ip, [r5, r3, lsl #2]
	b	.L2953
.L2956:
	mov	r0, r5
	movs	r1, #1
	bl	FtlLowFormatEraseBlock
	adds	r5, r5, #1
	add	r4, r4, r0
	uxth	r4, r4
	uxth	r5, r5
	b	.L2955
.L2959:
	mov	r0, r6
	movs	r1, #1
	bl	FtlLowFormatEraseBlock
	adds	r6, r6, #1
	add	r4, r4, r0
	uxth	r4, r4
	uxth	r6, r6
	b	.L2958
.L2961:
	movs	r1, #0
	bl	FtlLowFormatEraseBlock
	add	r6, r6, r0
	uxth	r6, r6
	b	.L2960
.L2970:
	ldr	r3, [r7]
	movw	r6, #65535
	ldrh	r1, [r4, #4]
	str	r3, [r4, #12]
	adds	r3, r3, #1
	str	r3, [r7]
	ldr	r3, [r5]
	strh	r1, [r3, r2, lsl #1]	@ movhi
	movs	r2, #0
	ldr	r3, .L2980+120
	strh	r2, [r3, #2]	@ movhi
	mov	r8, r3
	strb	r2, [r3, #6]
	ldrh	r2, [r4]
	mov	r4, r3
	adds	r2, r2, #1
	strh	r2, [r3]	@ movhi
	movs	r2, #1
	strb	r2, [r3, #8]
.L2971:
	mov	r0, r8
	bl	make_superblock
	ldrb	r3, [r4, #7]	@ zero_extendqisi2
	ldrh	r2, [r4]
	cmp	r3, #0
	bne	.L2972
	ldr	r3, [r5]
	strh	r6, [r3, r2, lsl #1]	@ movhi
	ldrh	r3, [r4]
	adds	r3, r3, #1
	strh	r3, [r4]	@ movhi
	b	.L2971
.L2981:
	.align	2
.L2980:
	.word	.LANCHOR78
	.word	.LANCHOR66
	.word	.LANCHOR203
	.word	.LANCHOR39
	.word	.LANCHOR164
	.word	.LANCHOR134
	.word	.LANCHOR165
	.word	.LANCHOR55
	.word	.LANCHOR193
	.word	.LANCHOR194
	.word	.LANCHOR40
	.word	.LANCHOR38
	.word	.LANCHOR65
	.word	.LANCHOR75
	.word	.LANCHOR42
	.word	.LANCHOR232
	.word	.LANCHOR74
	.word	.LANCHOR104
	.word	.LANCHOR16
	.word	.LANCHOR49
	.word	.LANCHOR52
	.word	.LANCHOR68
	.word	.LANCHOR43
	.word	.LANCHOR59
	.word	.LC75
	.word	.LANCHOR85
	.word	.LANCHOR93
	.word	.LANCHOR102
	.word	.LANCHOR213
	.word	.LANCHOR1
	.word	.LANCHOR94
	.word	168778952
	.word	.LANCHOR41
	.word	.LANCHOR231
.L2972:
	ldr	r3, [r7]
	ldrh	r1, [r4, #4]
	str	r3, [r4, #12]
	adds	r3, r3, #1
	str	r3, [r7]
	movw	r4, #65535
	ldr	r3, [r5]
	strh	r1, [r3, r2, lsl #1]	@ movhi
	ldr	r3, .L2982
	strh	r4, [r3]	@ movhi
	bl	FtlFreeSysBlkQueueOut
	ldr	r3, .L2982+4
	movs	r2, #0
	strh	r2, [r3, #2]	@ movhi
	ldr	r2, [fp]
	strh	r0, [r3]	@ movhi
	strh	r4, [r3, #4]	@ movhi
	strh	r2, [r3, #6]	@ movhi
	ldr	r2, [r7]
	str	r2, [r3, #8]
	adds	r2, r2, #1
	str	r2, [r7]
	bl	FtlVpcTblFlush
	bl	FtlSysBlkInit
	cbnz	r0, .L2951
	ldr	r3, .L2982+8
	movs	r2, #1
	str	r2, [r3]
.L2951:
	movs	r0, #0
	add	sp, sp, #24
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r10, fp, pc}
.L2983:
	.align	2
.L2982:
	.word	.LANCHOR95
	.word	.LANCHOR218
	.word	.LANCHOR247
	.size	FtlLowFormat, .-FtlLowFormat
	.section	.text.Ftl_gc_temp_data_write_back,"ax",%progbits
	.align	1
	.global	Ftl_gc_temp_data_write_back
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	Ftl_gc_temp_data_write_back, %function
Ftl_gc_temp_data_write_back:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r3, r4, r5, r6, r7, lr}
	ldr	r3, .L2999
	ldr	r3, [r3]
	cbz	r3, .L2985
.L2988:
	movs	r0, #0
	pop	{r3, r4, r5, r6, r7, pc}
.L2985:
	ldr	r3, .L2999+4
	ldr	r5, .L2999+8
	ldrb	r3, [r3]	@ zero_extendqisi2
	cbz	r3, .L2987
	ldr	r3, [r5]
	lsls	r2, r3, #31
	bpl	.L2987
	ldr	r3, .L2999+12
	ldrh	r3, [r3, #4]
	cmp	r3, #0
	bne	.L2988
.L2987:
	ldr	r4, .L2999+16
	movs	r3, #0
	movs	r6, #0
	movs	r7, #36
	mov	r2, r3
	ldr	r1, [r5]
	ldr	r0, [r4]
	bl	FlashProgPages
.L2989:
	ldr	r1, [r5]
	uxth	r3, r6
	cmp	r3, r1
	bcc	.L2991
	ldr	r0, [r4]
	bl	FtlGcBufFree
	movs	r3, #0
	str	r3, [r5]
	ldr	r3, .L2999+12
	ldrh	r3, [r3, #4]
	cmp	r3, #0
	bne	.L2988
	movs	r0, #1
	bl	FtlGcFreeTempBlock
	b	.L2998
.L2991:
	muls	r3, r7, r3
	ldr	r2, [r4]
	adds	r6, r6, #1
	adds	r1, r2, r3
	ldr	r2, [r2, r3]
	ldr	r0, [r1, #12]
	adds	r3, r2, #1
	bne	.L2990
	ldr	r3, .L2999+12
	movs	r5, #0
	ldr	r0, .L2999+20
	ldrh	r4, [r3]
	ldr	r0, [r0]
	strh	r5, [r0, r4, lsl #1]	@ movhi
	strh	r2, [r3]	@ movhi
	ldr	r2, .L2999+24
	ldr	r0, [r1, #4]
	ldr	r3, [r2, #96]
	ubfx	r0, r0, #10, #16
	adds	r3, r3, #1
	str	r3, [r2, #96]
	bl	FtlBbmMapBadBlock
	bl	FtlBbmTblFlush
	bl	FtlGcPageVarInit
.L2998:
	movs	r0, #1
	pop	{r3, r4, r5, r6, r7, pc}
.L2990:
	ldr	r2, [r0, #8]
	ldr	r1, [r1, #4]
	ldr	r0, [r0, #12]
	bl	FtlGcUpdatePage
	b	.L2989
.L3000:
	.align	2
.L2999:
	.word	.LANCHOR78
	.word	.LANCHOR16
	.word	.LANCHOR105
	.word	.LANCHOR95
	.word	.LANCHOR187
	.word	.LANCHOR85
	.word	.LANCHOR141
	.size	Ftl_gc_temp_data_write_back, .-Ftl_gc_temp_data_write_back
	.section	.text.Ftl_get_new_temp_ppa,"ax",%progbits
	.align	1
	.global	Ftl_get_new_temp_ppa
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	Ftl_get_new_temp_ppa, %function
Ftl_get_new_temp_ppa:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r3, r4, r5, lr}
	movw	r3, #65535
	ldr	r4, .L3004
	ldrh	r2, [r4]
	cmp	r2, r3
	beq	.L3002
	ldrh	r3, [r4, #4]
	cbnz	r3, .L3003
.L3002:
	bl	FtlCacheWriteBack
	movs	r0, #0
	movs	r5, #0
	bl	FtlGcFreeTempBlock
	ldr	r0, .L3004
	strb	r5, [r4, #8]
	bl	allocate_data_superblock
	ldr	r3, .L3004+4
	strh	r5, [r3]	@ movhi
	ldr	r3, .L3004+8
	strh	r5, [r3]	@ movhi
	bl	l2p_flush
	mov	r0, r5
	bl	FtlEctTblFlush
	bl	FtlVpcTblFlush
.L3003:
	ldr	r0, .L3004
	pop	{r3, r4, r5, lr}
	b	get_new_active_ppa
.L3005:
	.align	2
.L3004:
	.word	.LANCHOR95
	.word	.LANCHOR112
	.word	.LANCHOR113
	.size	Ftl_get_new_temp_ppa, .-Ftl_get_new_temp_ppa
	.section	.text.ftl_do_gc,"ax",%progbits
	.align	1
	.global	ftl_do_gc
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	ftl_do_gc, %function
ftl_do_gc:
	@ args = 0, pretend = 0, frame = 32
	@ frame_needed = 0, uses_anonymous_args = 0
	ldr	r3, .L3106
	push	{r4, r5, r6, r7, r8, r10, fp, lr}
	mov	lr, r0
	sub	sp, sp, #32
	ldr	r0, [r3]
	cmp	r0, #0
	bne	.L3065
	ldr	r3, .L3106+4
	ldr	r3, [r3]
	cmp	r3, #1
	bne	.L3006
	ldr	r3, .L3106+8
	ldr	r3, [r3]
	cmp	r3, #0
	bne	.L3006
	ldr	r2, .L3106+12
	ldrh	r2, [r2]
	cmp	r2, #47
	bls	.L3068
	ldr	r5, .L3106+16
	movw	r2, #65535
	ldrh	ip, [r5]
	cmp	ip, r2
	beq	.L3008
	ldr	r7, .L3106+20
	ldrh	r3, [r7]
	cmp	r3, r2
	bne	.L3008
	ldr	r1, .L3106+24
	ldrh	r6, [r1]
	cmp	r6, r3
	beq	.L3008
	ldr	r2, .L3106+28
	ldrh	r4, [r2]
	cmp	r4, r3
	itttt	ne
	strhne	ip, [r7]	@ movhi
	strhne	r6, [r5]	@ movhi
	strhne	r4, [r1]	@ movhi
	strhne	r3, [r2]	@ movhi
.L3008:
	cmp	lr, #0
	bne	.L3069
	ldr	r3, .L3106+32
	ldrh	r3, [r3]
	cmp	r3, #24
	bhi	.L3070
	ldr	r2, .L3106+36
	cmp	r3, #16
	ldrh	r4, [r2]
	bls	.L3011
	lsrs	r4, r4, #5
.L3010:
	ldr	r2, .L3106+40
	ldrh	r1, [r2]
	cmp	r1, r3
	mov	r1, r2
	bcs	.L3014
	ldr	r3, .L3106+44
	movw	r0, #65535
	ldrh	r3, [r3]
	cmp	r3, r0
	bne	.L3015
	ldr	r0, .L3106+20
	ldrh	r0, [r0]
	cmp	r0, r3
	bne	.L3015
	ldr	r3, .L3106+48
	ldrh	r0, [r3]
	cbnz	r0, .L3016
	ldr	r3, .L3106+52
	ldr	r4, .L3106+56
	ldr	r3, [r3]
	ldr	r4, [r4]
	add	r3, r3, r3, lsl #1
	cmp	r4, r3, lsr #2
	bcs	.L3017
.L3016:
	ldr	r3, .L3106+60
	ldrh	r3, [r3]
	add	r3, r3, r3, lsl #1
	asrs	r3, r3, #2
	strh	r3, [r1]	@ movhi
.L3018:
	ldr	r3, .L3106+64
	movs	r2, #0
	str	r2, [r3]
.L3006:
	add	sp, sp, #32
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r10, fp, pc}
.L3011:
	cmp	r3, #12
	bls	.L3012
	lsrs	r4, r4, #4
	b	.L3010
.L3012:
	cmp	r3, #8
	bls	.L3010
	lsrs	r4, r4, #2
	b	.L3010
.L3070:
	movs	r4, #1
	b	.L3010
.L3017:
	movs	r3, #18
	strh	r3, [r2]	@ movhi
	b	.L3018
.L3015:
	ldr	r3, .L3106+60
	ldrh	r3, [r3]
	add	r3, r3, r3, lsl #1
	asrs	r3, r3, #2
	strh	r3, [r1]	@ movhi
.L3014:
	ldr	r3, .L3106+68
	ldrh	r3, [r3]
	cbz	r3, .L3009
	adds	r4, r4, #32
	uxth	r4, r4
.L3009:
	ldr	r5, .L3106+72
	movw	r3, #65535
	ldrh	r2, [r5]
	cmp	r2, r3
	bne	.L3021
	ldr	r3, .L3106+20
	ldrh	r1, [r3]
	cmp	r1, r2
	beq	.L3022
	ldr	r0, .L3106+76
	ldr	r0, [r0]
	ldrh	r1, [r0, r1, lsl #1]
	cbnz	r1, .L3023
	strh	r2, [r3]	@ movhi
.L3023:
	ldrh	r2, [r3]
	strh	r2, [r5]	@ movhi
	movw	r2, #65535
	strh	r2, [r3]	@ movhi
.L3022:
	ldrh	r0, [r5]
	movw	r6, #65535
	movs	r3, #0
	strb	r3, [r5, #8]
	cmp	r0, r6
	beq	.L3021
	bl	IsBlkInGcList
	cbz	r0, .L3025
	strh	r6, [r5]	@ movhi
.L3025:
	ldr	r3, .L3106+80
	ldrb	r3, [r3]	@ zero_extendqisi2
	cbz	r3, .L3026
	ldrh	r0, [r5]
	bl	ftl_get_blk_mode
	strb	r0, [r5, #8]
.L3026:
	ldrh	r2, [r5]
	movw	r3, #65535
	cmp	r2, r3
	beq	.L3021
	ldr	r0, .L3106+72
	bl	make_superblock
	ldr	r2, .L3106+84
	movs	r3, #0
	strh	r3, [r5, #2]	@ movhi
	strb	r3, [r5, #6]
	strh	r3, [r2]	@ movhi
	ldr	r3, .L3106+76
	ldrh	r2, [r5]
	ldr	r3, [r3]
	ldrh	r2, [r3, r2, lsl #1]
	ldr	r3, .L3106+88
	strh	r2, [r3]	@ movhi
.L3021:
	ldr	r2, .L3106+92
	ldrh	r3, [r5]
	ldrh	r2, [r2]
	cmp	r2, r3
	beq	.L3027
	ldr	r2, .L3106+96
	ldrh	r2, [r2]
	cmp	r2, r3
	beq	.L3027
	ldr	r2, .L3106+44
	ldrh	r2, [r2]
	cmp	r2, r3
	bne	.L3028
.L3027:
	movw	r3, #65535
	strh	r3, [r5]	@ movhi
.L3028:
	ldr	r5, .L3106+72
	mov	r6, r5
.L3064:
	ldrh	r2, [r5]
	movw	r3, #65535
	cmp	r2, r3
	bne	.L3029
	ldr	r10, .L3106+104
	movs	r2, #0
	ldr	r3, .L3106+64
	mov	r7, r10
	str	r2, [r3]
.L3030:
	ldrh	r8, [r10]
	mov	r0, r8
	bl	List_get_gc_head_node
	uxth	fp, r0
	movw	r3, #65535
	cmp	fp, r3
	strh	fp, [r6]	@ movhi
	bne	.L3031
	movs	r3, #0
	movs	r0, #8
	strh	r3, [r10]	@ movhi
	b	.L3006
.L3069:
	movs	r4, #1
	b	.L3009
.L3031:
	str	r0, [sp]
	mov	r0, fp
	bl	IsBlkInGcList
	add	r3, r8, #1
	ldr	r2, [sp]
	cbz	r0, .L3032
	strh	r3, [r10]	@ movhi
	b	.L3030
.L3032:
	ldr	r1, .L3106+36
	uxth	r3, r3
	ldr	lr, .L3106+108
	uxth	r2, r2
	ldr	r8, .L3106+76
	ldrh	r1, [r1]
	ldrh	lr, [lr]
	ldr	r0, [r8]
	strh	r3, [r10]	@ movhi
	mul	r1, lr, r1
	ldrh	ip, [r0, r2, lsl #1]
	cmp	ip, r1, asr #1
	bgt	.L3034
	cmp	r3, #48
	bls	.L3035
	cmp	ip, #8
	bls	.L3035
	ldr	r3, .L3106+100
	ldrh	r3, [r3]
	cmp	r3, #35
	bhi	.L3035
.L3034:
	movs	r3, #0
	strh	r3, [r7]	@ movhi
.L3035:
	ldrh	r3, [r0, r2, lsl #1]
	cmp	r1, r3
	bgt	.L3036
	ldrh	r2, [r7]
	cmp	r2, #3
	bhi	.L3036
	movw	r3, #65535
	strh	r3, [r6]	@ movhi
	movs	r3, #0
	strh	r3, [r7]	@ movhi
.L3105:
	ldr	r3, .L3106+48
	ldrh	r0, [r3]
	b	.L3006
.L3036:
	cmp	r3, #0
	bne	.L3037
	movw	r0, #65535
	bl	decrement_vpc_count
	ldrh	r3, [r7]
	adds	r3, r3, #1
	strh	r3, [r7]	@ movhi
	b	.L3030
.L3107:
	.align	2
.L3106:
	.word	.LANCHOR78
	.word	.LANCHOR247
	.word	.LANCHOR176
	.word	.LANCHOR87
	.word	.LANCHOR116
	.word	.LANCHOR115
	.word	.LANCHOR117
	.word	.LANCHOR118
	.word	.LANCHOR90
	.word	.LANCHOR52
	.word	.LANCHOR181
	.word	.LANCHOR95
	.word	.LANCHOR248
	.word	.LANCHOR74
	.word	.LANCHOR102
	.word	.LANCHOR232
	.word	.LANCHOR177
	.word	.LANCHOR119
	.word	.LANCHOR213
	.word	.LANCHOR85
	.word	.LANCHOR16
	.word	.LANCHOR249
	.word	.LANCHOR250
	.word	.LANCHOR93
	.word	.LANCHOR94
	.word	.LANCHOR112
	.word	.LANCHOR183
	.word	.LANCHOR38
.L3037:
	movs	r3, #0
	strb	r3, [r6, #8]
	ldr	r3, .L3108
	ldrb	r3, [r3]	@ zero_extendqisi2
	cbz	r3, .L3038
	mov	r0, fp
	bl	ftl_get_blk_mode
	strb	r0, [r6, #8]
.L3038:
	ldr	r3, .L3108+4
	ldrh	r3, [r3]
	cmp	r3, fp
	bne	.L3039
	ldr	r1, .L3108+8
	movw	r2, #1069
	ldr	r0, .L3108+12
	bl	printf
	ldr	r1, .L3108+16
	ldr	r0, .L3108+20
	bl	printf
.L3039:
	ldr	r3, .L3108+24
	ldrh	r2, [r6]
	ldrh	r3, [r3]
	cmp	r2, r3
	bne	.L3040
	ldr	r1, .L3108+8
	movw	r2, #1070
	ldr	r0, .L3108+12
	bl	printf
	ldr	r1, .L3108+16
	ldr	r0, .L3108+20
	bl	printf
.L3040:
	ldr	r3, .L3108+28
	ldrh	r2, [r6]
	ldrh	r3, [r3]
	cmp	r2, r3
	bne	.L3041
	ldr	r1, .L3108+8
	movw	r2, #1071
	ldr	r0, .L3108+12
	bl	printf
	ldr	r1, .L3108+16
	ldr	r0, .L3108+20
	bl	printf
.L3041:
	mov	r0, r5
	bl	make_superblock
	ldr	r2, .L3108+32
	movs	r3, #0
	ldrh	r1, [r6]
	strh	r3, [r2]	@ movhi
	ldr	r2, [r8]
	ldrh	r1, [r2, r1, lsl #1]
	ldr	r2, .L3108+36
	strh	r3, [r6, #2]	@ movhi
	strb	r3, [r6, #6]
	strh	r1, [r2]	@ movhi
.L3029:
	ldr	r3, .L3108+40
	movs	r2, #1
	str	r2, [r3]
	ldr	r3, .L3108+44
	ldrh	r3, [r3]
	str	r3, [sp, #4]
	ldr	r3, .L3108
	ldrb	r3, [r3]	@ zero_extendqisi2
	cbz	r3, .L3042
	ldrb	r3, [r6, #8]	@ zero_extendqisi2
	cmp	r3, r2
	ittt	eq
	ldreq	r3, .L3108+48
	ldrheq	r3, [r3]
	streq	r3, [sp, #4]
.L3042:
	ldrh	r3, [r6, #2]
	ldr	r1, [sp, #4]
	ldr	fp, .L3108+76
	adds	r2, r3, r4
	cmp	r2, r1
	itt	gt
	movgt	r2, r1
	subgt	r4, r2, r3
	mov	r3, #0
	it	gt
	uxthgt	r4, r4
	str	r3, [sp, #12]
.L3044:
	ldrh	r3, [sp, #12]
	cmp	r4, r3
	bls	.L3052
	ldr	r3, .L3108+52
	movw	r8, #65535
	ldrh	lr, [r5, #2]
	mov	r10, #36
	ldr	r0, [fp]
	ldrh	r7, [r3]
	ldr	r3, [sp, #12]
	add	lr, lr, r3
	ldr	r3, .L3108+56
	str	r3, [sp, #8]
	movs	r3, #0
	str	r3, [sp]
	b	.L3053
.L3046:
	ldr	r1, [sp, #8]
	ldrh	r2, [r1, #2]!
	cmp	r2, r8
	str	r1, [sp, #8]
	beq	.L3045
	ldr	r1, [sp]
	orr	r2, lr, r2, lsl #10
	mla	ip, r10, r1, r0
	str	r2, [ip, #4]
	mov	r2, r1
	adds	r2, r2, #1
	uxth	r2, r2
	str	r2, [sp]
.L3045:
	adds	r3, r3, #1
.L3053:
	uxth	r2, r3
	cmp	r7, r2
	bhi	.L3046
	ldrb	r2, [r5, #8]	@ zero_extendqisi2
	ldr	r1, [sp]
	bl	FlashReadPages
	movs	r3, #0
.L3104:
	str	r3, [sp, #8]
	ldr	r2, [sp]
	ldrh	r3, [sp, #8]
	cmp	r2, r3
	bhi	.L3051
	ldr	r3, [sp, #12]
	adds	r3, r3, #1
	str	r3, [sp, #12]
	b	.L3044
.L3051:
	ldr	r3, [sp, #8]
	movs	r7, #36
	muls	r7, r3, r7
	ldr	r3, [fp]
	adds	r2, r3, r7
	ldr	r3, [r3, r7]
	adds	r3, r3, #1
	beq	.L3048
	ldr	r8, [r2, #12]
	movw	r3, #61589
	ldrh	r2, [r8]
	cmp	r2, r3
	bne	.L3048
	ldr	r10, [r8, #8]
	cmp	r10, #-1
	bne	.L3049
	ldr	r1, .L3108+8
	movw	r2, #1119
	ldr	r0, .L3108+12
	bl	printf
	ldr	r1, .L3108+16
	ldr	r0, .L3108+20
	bl	printf
.L3049:
	movs	r2, #0
	add	r1, sp, #24
	mov	r0, r10
	bl	log2phys
	ldr	r0, [fp]
	ldr	r3, [sp, #24]
	add	r0, r0, r7
	ldr	r2, [r0, #4]
	bic	r3, r3, #-2147483648
	cmp	r3, r2
	bne	.L3048
	ldr	r2, .L3108+32
	ldr	r1, .L3108+60
	ldr	r10, .L3108+72
	ldrh	r3, [r2]
	str	r1, [sp, #20]
	adds	r3, r3, #1
	strh	r3, [r2]	@ movhi
	ldr	r2, [r1]
	movs	r1, #36
	ldr	r3, [r10]
	mla	r3, r1, r3, r2
	ldr	r2, [r0, #16]
	str	r2, [r3, #16]
	str	r3, [sp, #16]
	bl	Ftl_get_new_temp_ppa
	ldr	r3, [sp, #16]
	ldr	r1, [sp, #20]
	str	r0, [r3, #4]
	ldr	r2, [r1]
	movs	r1, #36
	ldr	r3, [r10]
	ldr	r0, [fp]
	mla	r2, r1, r3, r2
	add	r0, r0, r7
	ldr	r7, .L3108+28
	ldr	r1, [r0, #8]
	adds	r3, r3, #1
	str	r1, [r2, #8]
	ldr	r1, [r0, #12]
	str	r1, [r2, #12]
	movs	r1, #1
	ldr	r2, [sp, #24]
	str	r2, [r8, #12]
	ldrh	r2, [r7]
	strh	r2, [r8, #2]	@ movhi
	ldr	r2, .L3108+64
	str	r3, [r10]
	ldr	r2, [r2]
	str	r2, [r8, #4]
	bl	FtlGcBufAlloc
	ldr	r3, .L3108
	ldrb	r3, [r3]	@ zero_extendqisi2
	cbnz	r3, .L3050
	ldrb	r2, [r7, #7]	@ zero_extendqisi2
	ldr	r3, [r10]
	cmp	r2, r3
	beq	.L3050
	ldrh	r3, [r7, #4]
	cbnz	r3, .L3048
.L3050:
	bl	Ftl_gc_temp_data_write_back
	cbz	r0, .L3048
	ldr	r3, .L3108+40
	movs	r2, #0
	movw	r1, #65535
	str	r2, [r3]
	ldr	r3, .L3108+68
	strh	r1, [r3]	@ movhi
	strh	r2, [r3, #2]	@ movhi
	b	.L3105
.L3048:
	ldr	r3, [sp, #8]
	adds	r3, r3, #1
	b	.L3104
.L3052:
	ldrh	r3, [r5, #2]
	add	r4, r4, r3
	ldr	r3, [sp, #4]
	uxth	r4, r4
	cmp	r3, r4
	strh	r4, [r5, #2]	@ movhi
	bhi	.L3054
	ldr	r3, .L3108+72
	ldr	r3, [r3]
	cbz	r3, .L3055
	bl	Ftl_gc_temp_data_write_back
	cbz	r0, .L3055
	ldr	r3, .L3108+40
	movs	r2, #0
	str	r2, [r3]
	b	.L3105
.L3109:
	.align	2
.L3108:
	.word	.LANCHOR16
	.word	.LANCHOR93
	.word	.LANCHOR251
	.word	.LC5
	.word	.LC6
	.word	.LC7
	.word	.LANCHOR94
	.word	.LANCHOR95
	.word	.LANCHOR249
	.word	.LANCHOR250
	.word	.LANCHOR176
	.word	.LANCHOR52
	.word	.LANCHOR53
	.word	.LANCHOR38
	.word	.LANCHOR213+14
	.word	.LANCHOR187
	.word	.LANCHOR165
	.word	.LANCHOR213
	.word	.LANCHOR105
	.word	.LANCHOR109
.L3055:
	ldr	r3, .L3110
	ldrh	r7, [r3]
	cbnz	r7, .L3056
	ldr	r8, .L3110+20
	ldrh	r2, [r5]
	ldr	r3, [r8]
	ldrh	r3, [r3, r2, lsl #1]
	cbz	r3, .L3056
	ldr	r4, .L3110+4
.L3057:
	ldr	r3, [r4]
	cmp	r7, r3
	bcs	.L3062
	movs	r2, #0
	add	r1, sp, #28
	mov	r0, r7
	bl	log2phys
	ldr	r0, [sp, #28]
	adds	r3, r0, #1
	beq	.L3058
	ubfx	r0, r0, #10, #16
	bl	P2V_block_in_plane
	ldrh	r3, [r5]
	cmp	r3, r0
	bne	.L3058
.L3062:
	ldr	r3, [r4]
	cmp	r7, r3
	bcc	.L3056
	ldrh	r2, [r5]
	movs	r1, #0
	ldr	r3, [r8]
	strh	r1, [r3, r2, lsl #1]	@ movhi
	ldrh	r0, [r5]
	bl	update_vpc_list
	bl	FtlCacheWriteBack
	bl	l2p_flush
	bl	FtlVpcTblFlush
.L3056:
	movw	r3, #65535
	strh	r3, [r5]	@ movhi
.L3054:
	ldr	r3, .L3110+8
	ldrh	r0, [r3]
	cmp	r0, #2
	bhi	.L3063
	ldr	r3, .L3110+12
	ldrh	r4, [r3]
	b	.L3064
.L3058:
	adds	r7, r7, #1
	b	.L3057
.L3063:
	ldr	r3, .L3110+16
	movs	r2, #0
	adds	r0, r0, #1
	str	r2, [r3]
	b	.L3006
.L3065:
	movs	r0, #0
	b	.L3006
.L3068:
	mov	r0, r3
	b	.L3006
.L3111:
	.align	2
.L3110:
	.word	.LANCHOR249
	.word	.LANCHOR74
	.word	.LANCHOR90
	.word	.LANCHOR52
	.word	.LANCHOR176
	.word	.LANCHOR85
	.size	ftl_do_gc, .-ftl_do_gc
	.section	.text.FtlCacheWriteBack,"ax",%progbits
	.align	1
	.global	FtlCacheWriteBack
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	FtlCacheWriteBack, %function
FtlCacheWriteBack:
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r0, r1, r2, r3, r4, r5, r6, r7, r8, r10, fp, lr}
	ldr	r3, .L3154
	ldr	r10, [r3]
	str	r3, [sp]
	cmp	r10, #0
	bne	.L3114
	ldr	r3, .L3154+4
	ldr	r1, [r3]
	mov	r8, r3
	cbz	r1, .L3114
	ldr	r3, .L3154+8
	ldr	r4, [r3]
	ldr	r3, .L3154+12
	ldrb	r3, [r3]	@ zero_extendqisi2
	cbz	r3, .L3139
	ldrb	r7, [r4, #8]	@ zero_extendqisi2
	subs	r0, r7, #1
	rsbs	r7, r0, #0
	adcs	r7, r7, r0
.L3116:
	ldr	r5, .L3154+16
	movs	r6, #0
	ldr	fp, .L3154+36
	mov	r2, r7
	ldrb	r3, [r4, #9]	@ zero_extendqisi2
	ldr	r0, [r5]
	bl	FlashProgPages
.L3117:
	ldr	r3, [r8]
	cmp	r6, r3
	bcc	.L3124
.L3136:
	movs	r3, #0
	str	r3, [r8]
.L3114:
	movs	r0, #0
	add	sp, sp, #16
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r10, fp, pc}
.L3139:
	mov	r7, r10
	b	.L3116
.L3124:
	movs	r3, #36
	ldr	r2, [r5]
	muls	r3, r6, r3
	adds	r0, r2, r3
	ldr	r2, [r2, r3]
	adds	r2, r2, #1
	bne	.L3118
	ldr	fp, .L3154+36
.L3119:
	ldr	r3, [r8]
	cmp	r10, r3
	bcc	.L3134
	ldr	r5, .L3154+20
	movw	r4, #16386
.L3137:
	ldrh	r3, [r5]
	cmp	r3, #0
	beq	.L3136
	movs	r1, #1
	mov	r0, r1
	bl	ftl_do_gc
	subs	r4, r4, #1
	bne	.L3137
	b	.L3136
.L3118:
	ldr	r2, [r0, #4]
	cbnz	r7, .L3120
.L3152:
	str	r2, [sp, #12]
	add	r1, sp, #12
	movs	r2, #1
	ldr	r0, [r0, #16]
	str	r3, [sp, #4]
	bl	log2phys
	ldr	r2, [r5]
	ldr	r3, [sp, #4]
	add	r3, r3, r2
	ldr	r3, [r3, #12]
	ldr	r0, [r3, #12]
	adds	r2, r0, #1
	beq	.L3122
	ubfx	r0, r0, #10, #16
	bl	P2V_block_in_plane
	ldr	r2, [fp]
	mov	r3, r0
	ldrh	r2, [r2, r0, lsl #1]
	cbnz	r2, .L3123
	mov	r1, r0
	str	r0, [sp, #4]
	ldr	r0, .L3154+24
	bl	printf
	ldr	r3, [sp, #4]
.L3123:
	mov	r0, r3
	bl	decrement_vpc_count
.L3122:
	adds	r6, r6, #1
	b	.L3117
.L3120:
	orr	r2, r2, #-2147483648
	b	.L3152
.L3134:
	movs	r6, #36
	ldr	r3, [r5]
	mul	r6, r6, r10
	mov	r2, #-1
	str	r2, [r3, r6]
.L3125:
	ldr	r2, [r5]
	adds	r3, r2, r6
	ldr	r2, [r2, r6]
	ldr	r0, [r3, #4]
	adds	r2, r2, #1
	beq	.L3129
	cmp	r7, #0
	bne	.L3130
.L3153:
	str	r0, [sp, #12]
	movs	r2, #1
	ldr	r0, [r3, #16]
	add	r1, sp, #12
	bl	log2phys
	ldr	r3, [r5]
	add	r6, r6, r3
	ldr	r3, [r6, #12]
	ldr	r0, [r3, #12]
	adds	r3, r0, #1
	beq	.L3132
	ubfx	r0, r0, #10, #16
	bl	P2V_block_in_plane
	ldr	r3, [fp]
	mov	r6, r0
	ldrh	r2, [r3, r0, lsl #1]
	cbnz	r2, .L3133
	mov	r1, r0
	ldr	r0, .L3154+24
	bl	printf
.L3133:
	mov	r0, r6
	bl	decrement_vpc_count
.L3132:
	add	r10, r10, #1
	b	.L3119
.L3129:
	ubfx	r0, r0, #10, #16
	bl	P2V_block_in_plane
	ldrh	r3, [r4]
	cmp	r3, r0
	bne	.L3126
	ldr	r1, [fp]
	ldrh	r0, [r4, #4]
	ldrh	r2, [r1, r3, lsl #1]
	subs	r2, r2, r0
	strh	r2, [r1, r3, lsl #1]	@ movhi
	ldr	r3, .L3154+28
	ldrh	r3, [r3]
	strh	r3, [r4, #2]	@ movhi
	movs	r3, #0
	strb	r3, [r4, #6]
	strh	r3, [r4, #4]	@ movhi
.L3126:
	ldrh	r3, [r4, #4]
	cbnz	r3, .L3127
	mov	r0, r4
	bl	allocate_new_data_superblock
.L3127:
	ldr	r2, .L3154+32
	ldr	r3, [r2, #96]
	adds	r3, r3, #1
	str	r3, [r2, #96]
	ldr	r3, [r5]
	add	r3, r3, r6
	ldr	r0, [r3, #4]
	ubfx	r0, r0, #10, #16
	bl	FtlGcMarkBadPhyBlk
	mov	r0, r4
	bl	get_new_active_ppa
	ldr	r3, [r5]
	mov	r2, r0
	str	r0, [sp, #12]
	movs	r1, #1
	adds	r0, r3, r6
	str	r2, [r0, #4]
	mov	r2, r7
	ldrb	r3, [r4, #9]	@ zero_extendqisi2
	bl	FlashProgPages
	ldr	r3, [r5]
	ldr	r3, [r3, r6]
	adds	r3, r3, #1
	ittt	eq
	ldreq	r2, [sp]
	moveq	r3, #1
	streq	r3, [r2]
	ldr	r3, [sp]
	ldr	r3, [r3]
	cmp	r3, #0
	beq	.L3125
	b	.L3114
.L3130:
	orr	r0, r0, #-2147483648
	b	.L3153
.L3155:
	.align	2
.L3154:
	.word	.LANCHOR78
	.word	.LANCHOR72
	.word	.LANCHOR252
	.word	.LANCHOR16
	.word	.LANCHOR73
	.word	.LANCHOR119
	.word	.LC76
	.word	.LANCHOR52
	.word	.LANCHOR141
	.word	.LANCHOR85
	.size	FtlCacheWriteBack, .-FtlCacheWriteBack
	.section	.text.FtlSysFlush,"ax",%progbits
	.align	1
	.global	FtlSysFlush
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	FtlSysFlush, %function
FtlSysFlush:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	ldr	r3, .L3158
	push	{r4, lr}
	ldr	r3, [r3]
	cbnz	r3, .L3157
	ldr	r3, .L3158+4
	ldr	r4, [r3]
	cmp	r4, #1
	bne	.L3157
	bl	FtlCacheWriteBack
	bl	l2p_flush
	mov	r0, r4
	bl	FtlEctTblFlush
	bl	FtlVpcTblFlush
.L3157:
	movs	r0, #0
	pop	{r4, pc}
.L3159:
	.align	2
.L3158:
	.word	.LANCHOR78
	.word	.LANCHOR247
	.size	FtlSysFlush, .-FtlSysFlush
	.section	.text.FtlDeInit,"ax",%progbits
	.align	1
	.global	FtlDeInit
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	FtlDeInit, %function
FtlDeInit:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r3, lr}
	ldr	r3, .L3162
	ldr	r3, [r3]
	cmp	r3, #1
	bne	.L3161
	bl	FtlSysFlush
.L3161:
	movs	r0, #0
	pop	{r3, pc}
.L3163:
	.align	2
.L3162:
	.word	.LANCHOR247
	.size	FtlDeInit, .-FtlDeInit
	.section	.text.ftl_deinit,"ax",%progbits
	.align	1
	.global	ftl_deinit
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	ftl_deinit, %function
ftl_deinit:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r3, lr}
	bl	ftl_flash_de_init
	bl	FtlDeInit
	pop	{r3, lr}
	b	ftl_flash_de_init
	.size	ftl_deinit, .-ftl_deinit
	.section	.text.rk_ftl_de_init,"ax",%progbits
	.align	1
	.global	rk_ftl_de_init
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	rk_ftl_de_init, %function
rk_ftl_de_init:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r3, lr}
	bl	FlashDeInit
	bl	FtlDeInit
	pop	{r3, lr}
	b	FlashDeInit
	.size	rk_ftl_de_init, .-rk_ftl_de_init
	.section	.text.ftl_cache_flush,"ax",%progbits
	.align	1
	.global	ftl_cache_flush
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	ftl_cache_flush, %function
ftl_cache_flush:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	b	FtlCacheWriteBack
	.size	ftl_cache_flush, .-ftl_cache_flush
	.section	.text.ftl_discard,"ax",%progbits
	.align	1
	.global	ftl_discard
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	ftl_discard, %function
ftl_discard:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 0, uses_anonymous_args = 0
	ldr	r3, .L3184
	push	{r0, r1, r4, r5, r6, r7, r8, lr}
	mov	r6, r1
	mov	r4, r2
	ldr	r3, [r3]
	cmp	r3, r1
	bls	.L3177
	cmp	r3, r2
	bcc	.L3177
	adds	r2, r1, r2
	cmp	r3, r2
	bcc	.L3177
	cmp	r4, #31
	bhi	.L3169
.L3170:
	movs	r0, #0
.L3167:
	add	sp, sp, #8
	@ sp needed
	pop	{r4, r5, r6, r7, r8, pc}
.L3169:
	ldr	r3, .L3184+4
	ldr	r3, [r3]
	cmp	r3, #0
	bne	.L3170
	ldr	r8, .L3184+16
	bl	FtlCacheWriteBack
	mov	r0, r6
	ldrh	r5, [r8]
	mov	r1, r5
	bl	__aeabi_uidiv
	smulbb	r3, r0, r5
	mov	r7, r0
	subs	r6, r6, r3
	uxth	r6, r6
	cbz	r6, .L3171
	subs	r5, r5, r6
	adds	r7, r7, #1
	cmp	r5, r4
	it	cs
	movcs	r5, r4
	uxth	r5, r5
	subs	r4, r4, r5
.L3171:
	ldr	r5, .L3184+8
	mov	r3, #-1
	ldr	r6, .L3184+12
	str	r3, [sp, #4]
.L3172:
	ldrh	r3, [r8]
	cmp	r4, r3
	bcs	.L3174
	ldr	r3, .L3184+8
	ldr	r2, [r3]
	cmp	r2, #32
	bls	.L3170
	movs	r4, #0
	str	r4, [r3]
	bl	l2p_flush
	bl	FtlVpcTblFlush
	b	.L3170
.L3174:
	movs	r2, #0
	mov	r1, sp
	mov	r0, r7
	bl	log2phys
	ldr	r3, [sp]
	adds	r3, r3, #1
	beq	.L3173
	ldr	r3, [r5]
	movs	r2, #1
	add	r1, sp, #4
	mov	r0, r7
	adds	r3, r3, #1
	str	r3, [r5]
	ldr	r3, [r6]
	adds	r3, r3, #1
	str	r3, [r6]
	bl	log2phys
	ldr	r0, [sp]
	ubfx	r0, r0, #10, #16
	bl	P2V_block_in_plane
	bl	decrement_vpc_count
.L3173:
	ldrh	r3, [r8]
	adds	r7, r7, #1
	subs	r4, r4, r3
	b	.L3172
.L3177:
	mov	r0, #-1
	b	.L3167
.L3185:
	.align	2
.L3184:
	.word	.LANCHOR68
	.word	.LANCHOR78
	.word	.LANCHOR253
	.word	.LANCHOR168
	.word	.LANCHOR55
	.size	ftl_discard, .-ftl_discard
	.section	.text.FtlRead,"ax",%progbits
	.align	1
	.global	FtlRead
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	FtlRead, %function
FtlRead:
	@ args = 0, pretend = 0, frame = 64
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, r8, r10, fp, lr}
	sub	sp, sp, #88
	str	r3, [sp, #24]
	mov	r4, r1
	ldr	r3, .L3231
	str	r2, [sp, #44]
	ldr	r3, [r3]
	cmp	r3, #1
	bne	.L3213
	cmp	r0, #16
	bne	.L3188
	ldr	r2, [sp, #24]
	add	r0, r4, #256
	ldr	r1, [sp, #44]
	bl	FtlVendorPartRead
	mov	r7, r0
.L3186:
	mov	r0, r7
	add	sp, sp, #88
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r10, fp, pc}
.L3188:
	ldr	r3, .L3231+4
	ldr	r3, [r3]
	cmp	r1, r3
	bcs	.L3213
	ldr	r2, [sp, #44]
	cmp	r2, r3
	bhi	.L3213
	adds	r2, r1, r2
	cmp	r3, r2
	str	r2, [sp, #48]
	bcc	.L3213
	ldr	r3, .L3231+8
	mov	r0, r4
	ldrh	r5, [r3]
	mov	r1, r5
	bl	__aeabi_uidiv
	ldr	r3, [sp, #48]
	mov	r1, r5
	str	r0, [sp, #36]
	subs	r0, r3, #1
	bl	__aeabi_uidiv
	ldr	r3, [sp, #36]
	ldr	r2, .L3231+12
	ldr	r1, [sp, #44]
	rsb	r3, r3, #1
	str	r0, [sp, #40]
	add	r3, r3, r0
	str	r3, [sp, #32]
	ldr	r3, [r2]
	add	r3, r3, r1
	ldr	r1, [sp, #32]
	str	r3, [r2]
	ldr	r2, .L3231+16
	ldr	r3, [r2]
	add	r3, r3, r1
	mov	r1, r0
	ldr	r0, [sp, #36]
	str	r3, [r2]
	bl	FtlCacheMetchLpa
	cbz	r0, .L3189
	bl	FtlCacheWriteBack
.L3189:
	ldr	r5, [sp, #36]
	movs	r3, #0
	ldr	r10, .L3231+60
	mov	r6, r3
	mov	r7, r3
	str	r3, [sp, #28]
	str	r3, [sp, #52]
.L3190:
	ldr	r3, [sp, #32]
	cbnz	r3, .L3209
	ldr	r3, .L3231+20
	ldrh	r3, [r3]
	cmp	r3, #0
	beq	.L3186
	movs	r1, #1
	ldr	r0, [sp, #32]
	bl	ftl_do_gc
	b	.L3186
.L3209:
	movs	r2, #0
	add	r1, sp, #84
	mov	r0, r5
	bl	log2phys
	ldr	r3, [sp, #84]
	adds	r2, r3, #1
	bne	.L3191
	ldr	fp, .L3231+8
	mov	r8, #0
.L3192:
	ldrh	r0, [fp]
	cmp	r8, r0
	bcc	.L3194
.L3195:
	ldr	r3, [sp, #32]
	adds	r5, r5, #1
	subs	r3, r3, #1
	str	r3, [sp, #32]
	beq	.L3199
	ldr	r3, .L3231+24
	ldrh	r3, [r3]
	cmp	r6, r3, lsl #2
	bne	.L3190
.L3199:
	cmp	r6, #0
	beq	.L3190
	movs	r2, #0
	mov	r1, r6
	ldr	r0, [r10]
	mov	fp, #0
	bl	FlashReadPages
	ldr	r3, [sp, #28]
	lsls	r3, r3, #9
	str	r3, [sp, #68]
	ldr	r3, [sp, #56]
	lsls	r3, r3, #9
	str	r3, [sp, #60]
	ldr	r3, [sp, #52]
	lsls	r3, r3, #9
	str	r3, [sp, #64]
.L3208:
	mov	r8, #36
	ldr	r3, [r10]
	mul	r8, r8, fp
	ldr	r1, [sp, #36]
	add	r3, r3, r8
	ldr	r2, [r3, #16]
	cmp	r1, r2
	bne	.L3201
	ldr	r1, [r3, #8]
	ldr	r3, .L3231+28
	ldr	r3, [r3]
	cmp	r1, r3
	bne	.L3202
	ldr	r3, [sp, #60]
	ldr	r2, [sp, #64]
	ldr	r0, [sp, #24]
	add	r1, r1, r3
.L3230:
	bl	ftl_memcpy
.L3202:
	ldr	r3, [r10]
	ldr	r1, [r3, r8]
	add	r2, r3, r8
	adds	r3, r1, #1
	bne	.L3203
	ldr	r0, .L3231+32
	mov	r7, r1
	ldr	r3, [r0, #72]
	adds	r3, r3, #1
	str	r3, [r0, #72]
.L3203:
	ldr	r3, [r2, #12]
	ldr	lr, [r2, #16]
	ldr	r0, [r3, #8]
	cmp	lr, r0
	beq	.L3204
	ldr	ip, .L3231+32
	ldr	r0, [ip, #72]
	adds	r0, r0, #1
	str	r0, [ip, #72]
	ldr	r0, [r2, #8]
	ldr	r1, [r0, #4]
	str	r1, [sp, #16]
	mov	r1, lr
	ldr	r0, [r0]
	str	r0, [sp, #12]
	ldr	r0, [r3, #12]
	str	r0, [sp, #8]
	ldr	r0, [r3, #8]
	str	r0, [sp, #4]
	ldr	r0, [r3, #4]
	str	r0, [sp]
	ldr	r0, .L3231+36
	ldr	r3, [r3]
	ldr	r2, [r2, #4]
	bl	printf
.L3204:
	ldr	r3, [r10]
	add	r2, r3, r8
	ldr	r3, [r3, r8]
	cmp	r3, #256
	bne	.L3205
	ldr	r0, [r2, #4]
	ubfx	r0, r0, #10, #16
	bl	P2V_block_in_plane
	mov	r8, r0
	bl	FtlGcRefreshBlock
	ldr	r2, .L3231+40
	ldr	r3, .L3231+44
.L3207:
	movs	r1, #1
	str	r2, [sp, #72]
	mov	r0, r1
	str	r3, [sp, #76]
	bl	ftl_do_gc
	ldr	r2, [sp, #72]
	ldr	r1, [r2]
	cbnz	r1, .L3206
	ldr	r3, [sp, #76]
	ldrh	r1, [r3]
	cmp	r1, r8
	beq	.L3207
.L3206:
	bl	FtlSysFlush
.L3205:
	add	fp, fp, #1
	cmp	r6, fp
	bne	.L3208
	movs	r6, #0
	b	.L3190
.L3194:
	mla	r0, r0, r5, r8
	cmp	r4, r0
	bhi	.L3193
	ldr	r3, [sp, #48]
	cmp	r3, r0
	bls	.L3193
	ldr	r3, [sp, #24]
	subs	r0, r0, r4
	mov	r2, #512
	movs	r1, #0
	add	r0, r3, r0, lsl #9
	bl	ftl_memset
.L3193:
	add	r8, r8, #1
	b	.L3192
.L3191:
	ldr	r2, [r10]
	mov	r8, #36
	mla	r8, r8, r6, r2
	str	r3, [r8, #4]
	ldr	r3, [sp, #36]
	cmp	r5, r3
	ldr	r3, .L3231+8
	bne	.L3196
	ldr	r2, .L3231+28
	mov	r0, r4
	ldrh	fp, [r3]
	ldr	r2, [r2]
	mov	r1, fp
	str	r2, [r8, #8]
	bl	__aeabi_uidivmod
	ldr	r2, [sp, #44]
	sub	r3, fp, r1
	str	r1, [sp, #56]
	cmp	r3, r2
	it	cs
	movcs	r3, r2
	cmp	r3, fp
	str	r3, [sp, #52]
	bne	.L3197
	ldr	r3, [sp, #24]
.L3228:
	str	r3, [r8, #8]
.L3197:
	ldr	r3, .L3231+48
	ldr	r2, .L3231+52
	str	r5, [r8, #16]
	ldrh	r3, [r3]
	ldr	r2, [r2]
	muls	r3, r6, r3
	adds	r6, r6, #1
	bic	r3, r3, #3
	add	r3, r3, r2
	str	r3, [r8, #12]
	b	.L3195
.L3196:
	ldr	r2, [sp, #40]
	cmp	r5, r2
	bne	.L3198
	ldr	r2, .L3231+56
	ldr	r1, [sp, #48]
	ldr	r2, [r2]
	str	r2, [r8, #8]
	ldrh	r2, [r3]
	mul	r3, r2, r5
	subs	r1, r1, r3
	cmp	r2, r1
	str	r1, [sp, #28]
	bne	.L3197
.L3229:
	ldr	r2, [sp, #24]
	subs	r3, r3, r4
	add	r3, r2, r3, lsl #9
	b	.L3228
.L3198:
	ldrh	r3, [r3]
	muls	r3, r5, r3
	b	.L3229
.L3201:
	ldr	r1, [sp, #40]
	cmp	r1, r2
	bne	.L3202
	ldr	r1, [r3, #8]
	ldr	r3, .L3231+56
	ldr	r3, [r3]
	cmp	r1, r3
	bne	.L3202
	ldr	r3, .L3231+8
	ldr	r2, [sp, #68]
	ldrh	r0, [r3]
	ldr	r3, [sp, #40]
	muls	r0, r3, r0
	ldr	r3, [sp, #24]
	subs	r0, r0, r4
	add	r0, r3, r0, lsl #9
	b	.L3230
.L3213:
	mov	r7, #-1
	b	.L3186
.L3232:
	.align	2
.L3231:
	.word	.LANCHOR247
	.word	.LANCHOR68
	.word	.LANCHOR55
	.word	.LANCHOR226
	.word	.LANCHOR171
	.word	.LANCHOR119
	.word	.LANCHOR38
	.word	.LANCHOR193
	.word	.LANCHOR141
	.word	.LC68
	.word	.LANCHOR78
	.word	.LANCHOR213
	.word	.LANCHOR58
	.word	.LANCHOR196
	.word	.LANCHOR194
	.word	.LANCHOR186
	.size	FtlRead, .-FtlRead
	.section	.text.ftl_vendor_read,"ax",%progbits
	.align	1
	.global	ftl_vendor_read
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	ftl_vendor_read, %function
ftl_vendor_read:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	mov	r3, r2
	mov	r2, r1
	mov	r1, r0
	movs	r0, #16
	b	FtlRead
	.size	ftl_vendor_read, .-ftl_vendor_read
	.section	.text.ftl_sys_read,"ax",%progbits
	.align	1
	.global	ftl_sys_read
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	ftl_sys_read, %function
ftl_sys_read:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	mov	r3, r2
	mov	r2, r1
	add	r1, r0, #256
	movs	r0, #16
	b	FtlRead
	.size	ftl_sys_read, .-ftl_sys_read
	.section	.text.StorageSysDataLoad,"ax",%progbits
	.align	1
	.global	StorageSysDataLoad
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	StorageSysDataLoad, %function
StorageSysDataLoad:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, lr}
	mov	r4, r1
	mov	r5, r0
	mov	r2, #512
	movs	r1, #0
	mov	r0, r4
	bl	memset
	mov	r3, r4
	add	r1, r5, #256
	movs	r2, #1
	movs	r0, #16
	pop	{r4, r5, r6, lr}
	b	FtlRead
	.size	StorageSysDataLoad, .-StorageSysDataLoad
	.section	.text.FlashBootVendorRead,"ax",%progbits
	.align	1
	.global	FlashBootVendorRead
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	FlashBootVendorRead, %function
FlashBootVendorRead:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	mov	r3, r2
	mov	r1, r0
	movs	r2, #1
	movs	r0, #16
	b	FtlRead
	.size	FlashBootVendorRead, .-FlashBootVendorRead
	.section	.text.ftl_read,"ax",%progbits
	.align	1
	.global	ftl_read
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	ftl_read, %function
ftl_read:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	b	FtlRead
	.size	ftl_read, .-ftl_read
	.section	.text.FtlInit,"ax",%progbits
	.align	1
	.global	FtlInit
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	FtlInit, %function
FtlInit:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, r8, lr}
	mov	r3, #-1
	ldr	r5, .L3248
	ldr	r2, .L3248+4
	str	r3, [r5]
	movs	r3, #0
	ldr	r1, .L3248+8
	str	r3, [r2]
	ldr	r2, .L3248+12
	ldr	r0, .L3248+16
	str	r3, [r2]
	bl	printf
	ldr	r0, .L3248+20
	bl	FtlConstantsInit
	bl	FtlMemInit
	bl	FtlVariablesInit
	ldr	r3, .L3248+24
	ldrh	r0, [r3]
	bl	FtlFreeSysBlkQueueInit
	bl	FtlLoadBbt
	cbz	r0, .L3239
	ldr	r1, .L3248+28
	ldr	r0, .L3248+32
.L3247:
	bl	printf
.L3240:
	movs	r0, #0
	pop	{r4, r5, r6, r7, r8, pc}
.L3239:
	bl	FtlSysBlkInit
	mov	r4, r0
	cbz	r0, .L3241
	ldr	r1, .L3248+28
	ldr	r0, .L3248+36
	b	.L3247
.L3241:
	movs	r1, #1
	str	r1, [r5]
	ldr	r5, .L3248+40
	bl	ftl_do_gc
	ldrh	r6, [r5]
	cmp	r6, #15
	bhi	.L3240
	ldr	r7, .L3248+44
	ldr	r8, .L3248+48
.L3245:
	ldrh	r3, [r7]
	movw	r2, #65535
	cmp	r3, r2
	bne	.L3243
	ldrh	r2, [r8]
	cmp	r2, r3
	bne	.L3243
	and	r0, r4, #63
	bl	List_get_gc_head_node
	uxth	r0, r0
	bl	FtlGcRefreshBlock
.L3243:
	movs	r1, #1
	mov	r0, r1
	bl	ftl_do_gc
	movs	r1, #1
	movs	r0, #0
	bl	ftl_do_gc
	ldrh	r2, [r5]
	adds	r3, r6, #2
	cmp	r2, r3
	bhi	.L3240
	adds	r4, r4, #1
	cmp	r4, #4096
	bne	.L3245
	b	.L3240
.L3249:
	.align	2
.L3248:
	.word	.LANCHOR247
	.word	.LANCHOR254
	.word	.LC77
	.word	.LANCHOR78
	.word	.LC7
	.word	.LANCHOR15
	.word	.LANCHOR39
	.word	.LANCHOR255
	.word	.LC78
	.word	.LC79
	.word	.LANCHOR90
	.word	.LANCHOR213
	.word	.LANCHOR115
	.size	FtlInit, .-FtlInit
	.section	.text.rk_ftl_init,"ax",%progbits
	.align	1
	.global	rk_ftl_init
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	rk_ftl_init, %function
rk_ftl_init:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, lr}
	bl	FlashInit
	mov	r4, r0
	cbnz	r0, .L3251
	bl	FtlInit
.L3251:
	bl	idb_init
	mov	r1, r4
	ldr	r0, .L3252
	bl	printf
	mov	r0, r4
	pop	{r4, pc}
.L3253:
	.align	2
.L3252:
	.word	.LC80
	.size	rk_ftl_init, .-rk_ftl_init
	.section	.text.ftl_fix_nand_power_lost_error,"ax",%progbits
	.align	1
	.global	ftl_fix_nand_power_lost_error
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	ftl_fix_nand_power_lost_error, %function
ftl_fix_nand_power_lost_error:
	@ args = 0, pretend = 0, frame = 56
	@ frame_needed = 0, uses_anonymous_args = 0
	ldr	r3, .L3268
	push	{r4, r5, r6, r7, r8, r10, fp, lr}
	sub	sp, sp, #56
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L3254
	ldr	r7, .L3268+4
	ldr	r6, .L3268+8
	ldr	r10, .L3268+32
	ldrh	r5, [r7]
	ldr	r3, [r6]
	ldr	r4, .L3268+12
	mov	r1, r5
	ldr	r0, .L3268+16
	ldrh	r2, [r3, r5, lsl #1]
	lsl	r8, r5, #1
	bl	printf
	ldrh	r0, [r10]
	bl	FtlGcRefreshOpenBlock
	ldrh	r0, [r4]
	bl	FtlGcRefreshOpenBlock
	mov	r0, r10
	bl	allocate_new_data_superblock
	mov	r0, r4
	movw	r4, #4097
	bl	allocate_new_data_superblock
	str	r7, [sp, #4]
.L3256:
	subs	r4, r4, #1
	beq	.L3260
	movs	r1, #1
	mov	r0, r1
	bl	ftl_do_gc
	ldr	r3, [r6]
	ldrh	r3, [r3, r8]
	cmp	r3, #0
	bne	.L3256
.L3260:
	ldr	r3, [r6]
	mov	r1, r5
	ldr	r0, .L3268+16
	ldrh	r2, [r3, r5, lsl #1]
	bl	printf
	ldr	r3, [r6]
	ldrh	r4, [r3, r5, lsl #1]
	cbnz	r4, .L3258
	add	r0, sp, #56
	ldr	r7, .L3268+20
	strh	r5, [r0, #-48]!	@ movhi
	movw	r10, #65535
	bl	make_superblock
	ldr	r3, .L3268+24
	add	r0, sp, #22
	ldr	r8, [r7]
	mov	r2, r4
	mov	fp, #36
	mov	ip, r4
	ldrh	lr, [r3]
.L3261:
	uxth	r3, r2
	cmp	lr, r3
	bhi	.L3263
	ldr	r3, [r6]
	mov	r1, r5
	ldr	r0, .L3268+28
	ldrh	r2, [r3, r5, lsl #1]
	bl	printf
	mov	r2, r4
	movs	r1, #0
	ldr	r0, [r7]
	bl	FlashEraseBlocks
	mov	r2, r4
	movs	r1, #1
	ldr	r0, [r7]
	bl	FlashEraseBlocks
.L3258:
	ldr	r2, [sp, #4]
	movw	r3, #65535
	strh	r3, [r2]	@ movhi
.L3254:
	add	sp, sp, #56
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r10, fp, pc}
.L3263:
	ldrh	r3, [r0, #2]!
	cmp	r3, r10
	beq	.L3262
	mla	r1, fp, r4, r8
	adds	r4, r4, #1
	lsls	r3, r3, #10
	uxth	r4, r4
	str	r3, [r1, #4]
	str	ip, [r1, #8]
	str	ip, [r1, #12]
.L3262:
	adds	r2, r2, #1
	b	.L3261
.L3269:
	.align	2
.L3268:
	.word	.LANCHOR16
	.word	.LANCHOR241
	.word	.LANCHOR85
	.word	.LANCHOR94
	.word	.LC81
	.word	.LANCHOR79
	.word	.LANCHOR38
	.word	.LC82
	.word	.LANCHOR93
	.size	ftl_fix_nand_power_lost_error, .-ftl_fix_nand_power_lost_error
	.section	.text.FtlWrite,"ax",%progbits
	.align	1
	.global	FtlWrite
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	FtlWrite, %function
FtlWrite:
	@ args = 0, pretend = 0, frame = 72
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, r8, r10, fp, lr}
	mov	r8, r3
	ldr	r3, .L3342
	sub	sp, sp, #72
	mov	r5, r1
	mov	r7, r2
	ldr	r3, [r3]
	cmp	r3, #0
	bne	.L3313
	ldr	r2, .L3342+4
	ldr	r2, [r2]
	cmp	r2, #1
	bne	.L3314
	cmp	r0, #16
	bne	.L3272
	mov	r2, r8
	mov	r1, r7
	add	r0, r5, #256
	bl	FtlVendorPartWrite
.L3270:
	add	sp, sp, #72
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r10, fp, pc}
.L3272:
	ldr	r3, .L3342+8
	ldr	r3, [r3]
	cmp	r1, r3
	bcs	.L3317
	cmp	r7, r3
	bhi	.L3317
	adds	r6, r1, r7
	cmp	r3, r6
	bcc	.L3317
	ldr	r3, .L3342+12
	mov	r2, #2048
	mov	r0, r5
	str	r2, [r3]
	ldr	r3, .L3342+16
	ldrh	r4, [r3]
	mov	r1, r4
	bl	__aeabi_uidiv
	mov	r1, r4
	mov	fp, r0
	subs	r0, r6, #1
	bl	__aeabi_uidiv
	ldr	r2, .L3342+20
	sub	r10, r0, fp
	add	r6, r10, #1
	cmp	r7, r4, lsl #1
	str	r0, [sp, #4]
	ldr	r3, [r2]
	add	r3, r3, r6
	str	r3, [r2]
	ldr	r2, .L3342+24
	ldr	r3, [r2]
	add	r3, r3, r7
	str	r3, [r2]
	ite	cs
	movcs	r3, #1
	movcc	r3, #0
	str	r3, [sp, #12]
	ldr	r3, .L3342+28
	ldr	r2, [r3]
	cmp	r2, #0
	beq	.L3318
	movs	r3, #36
	muls	r3, r2, r3
	ldr	r2, .L3342+32
	ldr	r2, [r2]
	subs	r3, r3, #36
	add	r3, r3, r2
	ldr	r2, [r3, #16]
	cmp	fp, r2
	bne	.L3319
	ldr	r1, .L3342+36
	mov	r0, r5
	ldr	r6, .L3342+40
	str	r3, [sp, #8]
	ldr	r2, [r1]
	adds	r2, r2, #1
	str	r2, [r1]
	mov	r1, r4
	ldr	r2, [r6]
	adds	r2, r2, #1
	str	r2, [r6]
	bl	__aeabi_uidivmod
	subs	r4, r4, r1
	mov	r0, r1
	cmp	r4, r7
	mov	r1, r8
	it	cs
	movcs	r4, r7
	lsls	r3, r4, #9
	lsls	r2, r4, #9
	str	r3, [sp]
	ldr	r3, [sp, #8]
	ldr	r3, [r3, #8]
	add	r0, r3, r0, lsl #9
	bl	ftl_memcpy
	cmp	r10, #0
	bne	.L3276
	ldr	r3, [r6]
	cmp	r3, #2
	bgt	.L3276
.L3313:
	movs	r0, #0
	b	.L3270
.L3276:
	ldr	r3, [sp]
	subs	r7, r7, r4
	add	r5, r5, r4
	add	fp, fp, #1
	mov	r6, r10
	add	r3, r3, r8
	str	r3, [sp]
.L3275:
	ldr	r3, .L3342+40
	movs	r2, #0
	str	r2, [r3]
.L3274:
	ldr	r1, [sp, #4]
	mov	r0, fp
	bl	FtlCacheMetchLpa
	cbz	r0, .L3277
	bl	FtlCacheWriteBack
.L3277:
	ldr	r3, .L3342+44
	mov	r4, fp
	ldr	r2, .L3342+48
	str	r2, [r3]
.L3278:
	cmp	r6, #0
	bne	.L3308
	bl	FtlCacheWriteBack
	ldr	r3, [sp, #4]
	mov	r0, r6
	ldr	r4, .L3342+52
	sub	r1, r3, fp
	bl	ftl_do_gc
	ldrh	r3, [r4]
	cmp	r3, #5
	bls	.L3309
	cmp	r3, #31
	bhi	.L3313
	ldr	r3, .L3342+56
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L3313
.L3309:
	ldr	r5, .L3342+60
	ldr	r7, .L3342+64
.L3312:
	ldrh	r2, [r5]
	movw	r3, #65535
	cmp	r2, r3
	bne	.L3311
	ldrh	r3, [r7]
	cmp	r3, r2
	bne	.L3311
	ldr	r2, .L3342+68
	ldrh	r2, [r2]
	cmp	r2, r3
	bne	.L3311
	and	r0, r6, #7
	bl	List_get_gc_head_node
	uxth	r0, r0
	bl	FtlGcRefreshBlock
.L3311:
	ldr	r2, .L3342+72
	movs	r3, #128
	movs	r1, #1
	mov	r0, r1
	strh	r3, [r2]	@ movhi
	ldr	r2, .L3342+76
	strh	r3, [r2]	@ movhi
	bl	ftl_do_gc
	movs	r1, #1
	movs	r0, #0
	bl	ftl_do_gc
	ldr	r3, .L3342
	ldr	r3, [r3]
	cmp	r3, #0
	bne	.L3313
	ldrh	r3, [r4]
	cmp	r3, #2
	bhi	.L3313
	adds	r6, r6, #1
	cmp	r6, #256
	bne	.L3312
	b	.L3313
.L3319:
	str	r8, [sp]
	b	.L3275
.L3318:
	str	r8, [sp]
	b	.L3274
.L3308:
	ldr	r3, .L3342+48
	ldr	r8, .L3342+100
	ldrb	r2, [r3, #6]	@ zero_extendqisi2
	ldrh	r3, [r8]
	cmp	r2, r3
	bcc	.L3279
	ldr	r1, .L3342+80
	mov	r2, #1472
	ldr	r0, .L3342+84
	bl	printf
	ldr	r1, .L3342+88
	ldr	r0, .L3342+92
	bl	printf
.L3279:
	ldr	r3, .L3342+48
	ldrh	r3, [r3, #4]
	cbnz	r3, .L3280
	ldr	r0, .L3342+48
	bl	allocate_new_data_superblock
	ldr	r3, .L3342+44
	ldr	r2, .L3342+48
	str	r2, [r3]
.L3280:
	ldr	r3, .L3342+96
	ldr	r2, .L3342+28
	ldr	r3, [r3]
	ldr	r2, [r2]
	subs	r3, r3, r2
	ldr	r2, .L3342+48
	ldrh	r2, [r2, #4]
	cmp	r3, r2
	it	cs
	movcs	r3, r2
	cmp	r3, r6
	it	cs
	movcs	r3, r6
	str	r3, [sp, #28]
	ldr	r3, .L3342+48
	ldrb	r2, [r3, #6]	@ zero_extendqisi2
	ldrh	r3, [r8]
	cmp	r2, r3
	bcc	.L3281
	ldr	r1, .L3342+80
	movw	r2, #1515
	ldr	r0, .L3342+84
	bl	printf
	ldr	r1, .L3342+88
	ldr	r0, .L3342+92
	bl	printf
.L3281:
	movs	r3, #0
.L3340:
	str	r3, [sp, #8]
	ldr	r3, [sp, #8]
	ldr	r2, [sp, #28]
	cmp	r3, r2
	bne	.L3303
.L3283:
	ldr	r3, [sp, #8]
	cmp	r6, r3
	bcs	.L3304
	ldr	r1, .L3342+80
	movw	r2, #1609
	ldr	r0, .L3342+84
	bl	printf
	ldr	r1, .L3342+88
	ldr	r0, .L3342+92
	bl	printf
.L3304:
	ldr	r3, [sp, #8]
	ldr	r8, .L3342+28
	subs	r6, r6, r3
	ldr	r3, .L3342+96
	ldr	r2, [r8]
	ldr	r3, [r3]
	cmp	r2, r3
	bcs	.L3305
	ldr	r3, [sp, #12]
	cmp	r3, #0
	bne	.L3305
	ldr	r3, .L3342+48
	ldrh	r3, [r3, #4]
	cmp	r3, #0
	beq	.L3305
.L3307:
	movs	r3, #0
	str	r3, [sp, #12]
	b	.L3278
.L3343:
	.align	2
.L3342:
	.word	.LANCHOR78
	.word	.LANCHOR247
	.word	.LANCHOR68
	.word	.LANCHOR256
	.word	.LANCHOR55
	.word	.LANCHOR167
	.word	.LANCHOR225
	.word	.LANCHOR72
	.word	.LANCHOR73
	.word	.LANCHOR169
	.word	.LANCHOR257
	.word	.LANCHOR252
	.word	.LANCHOR93
	.word	.LANCHOR90
	.word	.LANCHOR2
	.word	.LANCHOR213
	.word	.LANCHOR115
	.word	.LANCHOR116
	.word	.LANCHOR182
	.word	.LANCHOR181
	.word	.LANCHOR258
	.word	.LC5
	.word	.LC6
	.word	.LC7
	.word	.LANCHOR185
	.word	.LANCHOR38
.L3303:
	ldr	r3, .L3344
	ldrh	r3, [r3, #4]
	cmp	r3, #0
	beq	.L3283
	ldr	r3, [sp, #12]
	cbz	r3, .L3284
	ldr	r3, [sp, #4]
	cmp	r3, r4
	bne	.L3284
	ldr	r3, [sp, #8]
	cbz	r3, .L3284
	ldr	r3, .L3344+4
	ldr	r1, [sp, #4]
	ldrh	r2, [r3]
	adds	r3, r5, r7
	mls	r3, r2, r1, r3
	cmp	r2, r3
	bne	.L3283
.L3284:
	movs	r2, #0
	add	r1, sp, #32
	mov	r0, r4
	ldr	r8, .L3344+28
	bl	log2phys
	ldr	r0, .L3344
	bl	get_new_active_ppa
	ldr	r3, .L3344+8
	movs	r2, #36
	ldr	r1, [r3]
	ldr	r3, [r8]
	mla	ip, r2, r1, r3
	ldr	r3, .L3344+12
	ldrh	r2, [r3]
	str	r0, [ip, #4]
	str	r4, [ip, #16]
	mul	r3, r2, r1
	bic	r3, r3, #3
	str	r3, [sp, #20]
	ldr	r3, .L3344+16
	ldr	r0, [sp, #20]
	ldr	r3, [r3]
	add	r10, r3, r0
	str	r3, [sp, #24]
	ldr	r3, .L3344+20
	str	r10, [ip, #12]
	ldrh	r0, [r3]
	str	r3, [sp, #16]
	muls	r1, r0, r1
	ldr	r0, .L3344+24
	ldr	r0, [r0]
	bic	r1, r1, #3
	add	r1, r1, r0
	mov	r0, r10
	str	r1, [ip, #8]
	movs	r1, #0
	bl	ftl_memset
	cmp	fp, r4
	ldr	r2, .L3344+4
	beq	.L3285
	ldr	r3, [sp, #4]
	cmp	r3, r4
	ldr	r3, [sp, #16]
	bne	.L3337
	ldrh	r3, [sp, #4]
	add	r8, r5, r7
	ldrh	r2, [r2]
	smulbb	r2, r2, r3
	movs	r3, #0
	str	r3, [sp, #16]
	sub	r8, r8, r2
	uxth	r8, r8
	b	.L3288
.L3285:
	ldrh	r8, [r2]
	mov	r0, r5
	mov	r1, r8
	bl	__aeabi_uidivmod
	sub	r8, r8, r1
	str	r1, [sp, #16]
	cmp	r8, r7
	it	cs
	movcs	r8, r7
.L3288:
	ldr	r3, .L3344+4
	ldr	r0, .L3344+28
	ldrh	r3, [r3]
	cmp	r3, r8
	ldr	r3, .L3344+8
	bne	.L3289
	cmp	fp, r4
	ldr	r3, [r3]
	ittet	ne
	mulne	r1, r8, r4
	ldrne	r2, [sp]
	ldreq	r1, [sp]
	subne	r1, r1, r5
	it	ne
	addne	r1, r2, r1, lsl #9
	ldr	r2, [sp, #12]
	cmp	r2, #0
	beq	.L3291
	ldr	r2, [r0]
	movs	r0, #36
	mla	r3, r0, r3, r2
	str	r1, [r3, #8]
.L3292:
	ldr	r3, .L3344
	ldrb	r2, [r3, #6]	@ zero_extendqisi2
	ldr	r3, .L3344+32
	ldrh	r3, [r3]
	cmp	r2, r3
	bcc	.L3300
	ldr	r1, .L3344+36
	movw	r2, #1599
	ldr	r0, .L3344+40
	bl	printf
	ldr	r1, .L3344+44
	ldr	r0, .L3344+48
	bl	printf
.L3300:
	ldr	r2, [sp, #24]
	movw	r3, #61589
	ldr	r1, [sp, #20]
	strh	r3, [r2, r1]	@ movhi
	ldr	r2, .L3344+52
	str	r4, [r10, #8]
	adds	r4, r4, #1
	ldr	r3, [r2]
	str	r3, [r10, #4]
	adds	r3, r3, #1
	adds	r1, r3, #1
	it	eq
	moveq	r3, #0
	str	r3, [r2]
	ldr	r3, [sp, #32]
	ldr	r2, .L3344+8
	str	r3, [r10, #12]
	ldr	r3, .L3344
	ldrh	r3, [r3]
	strh	r3, [r10, #2]	@ movhi
	ldr	r3, [r2]
	adds	r3, r3, #1
	str	r3, [r2]
	ldr	r3, [sp, #8]
	adds	r3, r3, #1
	b	.L3340
.L3291:
	ldr	r2, .L3344+28
	movs	r0, #36
	ldr	r2, [r2]
	mla	r3, r0, r3, r2
	ldr	r2, .L3344+20
	ldrh	r2, [r2]
.L3341:
	ldr	r0, [r3, #8]
	b	.L3338
.L3289:
	ldr	r2, [sp, #32]
	adds	r1, r2, #1
	beq	.L3293
	str	r2, [sp, #40]
	movs	r1, #36
	ldr	r2, [r0]
	add	r0, sp, #36
	ldr	r3, [r3]
	str	r4, [sp, #52]
	mla	r3, r1, r3, r2
	movs	r1, #1
	ldr	r2, [r3, #8]
	ldr	r3, [r3, #12]
	str	r2, [sp, #44]
	movs	r2, #0
	str	r3, [sp, #48]
	bl	FlashReadPages
	ldr	r3, [sp, #36]
	adds	r3, r3, #1
	bne	.L3294
	ldr	r2, .L3344+56
	ldr	r3, [r2, #72]
	adds	r3, r3, #1
	str	r3, [r2, #72]
.L3297:
	cmp	fp, r4
	ldr	r0, .L3344+28
	lsl	r2, r8, #9
	bne	.L3298
	ldr	r3, .L3344+8
	ldr	r1, [r0]
	movs	r0, #36
	ldr	r3, [r3]
	mla	r3, r0, r3, r1
	ldr	r1, [sp]
	ldr	r0, [r3, #8]
	ldr	r3, [sp, #16]
	add	r0, r0, r3, lsl #9
.L3338:
	bl	ftl_memcpy
	b	.L3292
.L3294:
	ldr	r1, [r10, #8]
	cmp	r4, r1
	beq	.L3296
	ldr	r2, .L3344+56
	ldr	r0, .L3344+60
	ldr	r3, [r2, #72]
	adds	r3, r3, #1
	str	r3, [r2, #72]
	mov	r2, r4
	bl	printf
.L3296:
	ldr	r3, [r10, #8]
	cmp	r4, r3
	beq	.L3297
	movw	r2, #1581
	ldr	r1, .L3344+36
	ldr	r0, .L3344+40
	bl	printf
	ldr	r1, .L3344+44
	ldr	r0, .L3344+48
	bl	printf
	b	.L3297
.L3293:
	ldr	r2, [r0]
	movs	r1, #36
	ldr	r3, [r3]
	mla	r3, r1, r3, r2
	ldr	r2, .L3344+20
	movs	r1, #0
	ldrh	r2, [r2]
	ldr	r0, [r3, #8]
	bl	ftl_memset
	b	.L3297
.L3298:
	ldr	r3, .L3344+4
	mov	ip, #36
	ldr	r0, [r0]
	ldrh	r1, [r3]
	ldr	r3, .L3344+8
	ldr	r3, [r3]
	muls	r1, r4, r1
	mla	r3, ip, r3, r0
	ldr	r0, [sp]
	subs	r1, r1, r5
	add	r1, r0, r1, lsl #9
	b	.L3341
.L3337:
	ldr	r1, [sp, #12]
	cbz	r1, .L3299
	ldr	r3, .L3344+8
	movs	r0, #36
	ldr	r1, [r8]
	ldr	r3, [r3]
	mla	r8, r0, r3, r1
	ldrh	r3, [r2]
	ldr	r2, [sp]
	muls	r3, r4, r3
	subs	r3, r3, r5
	add	r3, r2, r3, lsl #9
	str	r3, [r8, #8]
	b	.L3292
.L3299:
	ldrh	r1, [r2]
	mov	ip, #36
	ldr	r2, .L3344+8
	ldr	r0, [r8]
	ldr	r2, [r2]
	muls	r1, r4, r1
	mla	r8, ip, r2, r0
	ldrh	r2, [r3]
	ldr	r3, [sp]
	subs	r1, r1, r5
	ldr	r0, [r8, #8]
	add	r1, r3, r1, lsl #9
	b	.L3338
.L3305:
	bl	FtlCacheWriteBack
	cmp	r6, #1
	mov	r3, #0
	str	r3, [r8]
	bhi	.L3278
	b	.L3307
.L3317:
	mov	r0, #-1
	b	.L3270
.L3314:
	mov	r0, r3
	b	.L3270
.L3345:
	.align	2
.L3344:
	.word	.LANCHOR93
	.word	.LANCHOR55
	.word	.LANCHOR72
	.word	.LANCHOR58
	.word	.LANCHOR197
	.word	.LANCHOR57
	.word	.LANCHOR192
	.word	.LANCHOR73
	.word	.LANCHOR38
	.word	.LANCHOR258
	.word	.LC5
	.word	.LC6
	.word	.LC7
	.word	.LANCHOR165
	.word	.LANCHOR141
	.word	.LC83
	.size	FtlWrite, .-FtlWrite
	.section	.text.ftl_vendor_write,"ax",%progbits
	.align	1
	.global	ftl_vendor_write
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	ftl_vendor_write, %function
ftl_vendor_write:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	mov	r3, r2
	mov	r2, r1
	mov	r1, r0
	movs	r0, #16
	b	FtlWrite
	.size	ftl_vendor_write, .-ftl_vendor_write
	.section	.text.ftl_sys_write,"ax",%progbits
	.align	1
	.global	ftl_sys_write
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	ftl_sys_write, %function
ftl_sys_write:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	mov	r3, r2
	mov	r2, r1
	add	r1, r0, #256
	movs	r0, #16
	b	FtlWrite
	.size	ftl_sys_write, .-ftl_sys_write
	.section	.text.StorageSysDataStore,"ax",%progbits
	.align	1
	.global	StorageSysDataStore
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	StorageSysDataStore, %function
StorageSysDataStore:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	mov	r3, r1
	movs	r2, #1
	add	r1, r0, #256
	movs	r0, #16
	b	FtlWrite
	.size	StorageSysDataStore, .-StorageSysDataStore
	.section	.text.FlashBootVendorWrite,"ax",%progbits
	.align	1
	.global	FlashBootVendorWrite
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	FlashBootVendorWrite, %function
FlashBootVendorWrite:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	mov	r3, r2
	mov	r1, r0
	movs	r2, #1
	movs	r0, #16
	b	FtlWrite
	.size	FlashBootVendorWrite, .-FlashBootVendorWrite
	.section	.text.ftl_write,"ax",%progbits
	.align	1
	.global	ftl_write
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	ftl_write, %function
ftl_write:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, r8, lr}
	mov	r7, r1
	mov	r4, r2
	mov	r5, r3
	mov	r6, r0
	cbnz	r0, .L3351
	mov	r3, r2
	mov	r2, r5
	bl	idb_write_data
.L3351:
	mov	r3, r5
	mov	r2, r4
	mov	r1, r7
	mov	r0, r6
	pop	{r4, r5, r6, r7, r8, lr}
	b	FtlWrite
	.size	ftl_write, .-ftl_write
	.section	.text.FtlDumpSysBlock,"ax",%progbits
	.align	1
	.global	FtlDumpSysBlock
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	FtlDumpSysBlock, %function
FtlDumpSysBlock:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, r8, r10, fp, lr}
	lsl	r10, r0, #10
	ldr	r5, .L3359
	sub	sp, sp, #24
	mov	r7, r0
	movs	r6, #0
	ldr	r4, .L3359+4
	ldr	r3, [r5]
	ldr	r8, .L3359+20
	mov	fp, r4
	str	r3, [r4, #8]
	ldr	r3, .L3359+8
	ldr	r3, [r3]
	str	r3, [r4, #12]
.L3353:
	ldrh	r2, [r8]
	sxth	r3, r6
	cmp	r3, r2
	blt	.L3355
	add	sp, sp, #24
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r10, fp, pc}
.L3355:
	movs	r2, #1
	orr	r3, r3, r10
	mov	r1, r2
	mov	r0, fp
	str	r3, [r4, #4]
	bl	FlashReadPages
	ldr	r2, [r4, #8]
	mov	r1, r7
	ldr	r3, [r4, #12]
	ldr	r0, .L3359+12
	ldr	r2, [r2]
	str	r2, [sp, #16]
	ldr	r2, [r3, #12]
	str	r2, [sp, #12]
	ldr	r2, [r3, #8]
	str	r2, [sp, #8]
	ldr	r2, [r3, #4]
	str	r2, [sp, #4]
	ldr	r3, [r3]
	str	r3, [sp]
	ldm	r4, {r2, r3}
	bl	printf
	ldr	r3, [r4, #12]
	ldr	r3, [r3]
	adds	r3, r3, #1
	beq	.L3354
	mov	r3, #768
	movs	r2, #4
	ldr	r1, [r5]
	ldr	r0, .L3359+16
	bl	rknand_print_hex
.L3354:
	adds	r6, r6, #1
	b	.L3353
.L3360:
	.align	2
.L3359:
	.word	.LANCHOR189
	.word	.LANCHOR211
	.word	.LANCHOR195
	.word	.LC84
	.word	.LC85
	.word	.LANCHOR53
	.size	FtlDumpSysBlock, .-FtlDumpSysBlock
	.section	.text.dump_map_info,"ax",%progbits
	.align	1
	.global	dump_map_info
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	dump_map_info, %function
dump_map_info:
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 0, uses_anonymous_args = 0
	ldr	r3, .L3375
	push	{r4, r5, r6, r7, r8, r10, fp, lr}
	sub	sp, sp, #40
	ldr	r8, .L3375+72
	ldrh	r5, [r3]
.L3362:
	ldr	r3, .L3375+4
	ldrh	r3, [r3]
	cmp	r3, r5
	bhi	.L3369
	ldr	r4, .L3375+8
	movs	r7, #0
.L3370:
	ldr	r3, .L3375+12
	sxth	r5, r7
	ldrh	r3, [r3]
	cmp	r5, r3
	bge	.L3373
	lsls	r5, r5, #1
	movs	r6, #0
	ldr	r8, .L3375+76
	b	.L3374
.L3364:
	str	r3, [sp, #36]
	mov	r1, r5
	ldr	r3, .L3375+16
	str	r2, [sp, #32]
	ldrb	r0, [r3, r6]	@ zero_extendqisi2
	bl	V2P_block
	str	r0, [sp, #28]
	bl	FtlBbmIsBadBlock
	ldr	r2, [sp, #32]
	ldr	r3, [sp, #36]
	cbnz	r0, .L3363
	ldr	r1, [sp, #28]
	mla	r0, fp, r4, r7
	lsls	r1, r1, #10
	str	r3, [r0, #8]
	str	r1, [r0, #4]
	mul	r1, r10, r4
	adds	r4, r4, #1
	uxth	r4, r4
	bic	ip, r1, #3
	ldr	r1, [sp, #24]
	add	r1, r1, ip
	str	r1, [r0, #12]
.L3363:
	adds	r6, r6, #1
.L3371:
	uxth	r1, r6
	cmp	r2, r1
	bhi	.L3364
	cbnz	r4, .L3365
.L3368:
	adds	r5, r5, #1
	uxth	r5, r5
	b	.L3362
.L3365:
	ldr	r10, .L3375+80
	mov	r0, r7
	movs	r6, #0
	movs	r7, #36
	movs	r2, #1
	mov	r1, r4
	bl	FlashReadPages
.L3366:
	uxth	r3, r6
	cmp	r4, r3
	bls	.L3368
	ldr	r3, [r8]
	mla	r3, r7, r6, r3
	adds	r6, r6, #1
	ldr	r1, [r3, #12]
	ldr	r2, [r3, #4]
	ldr	r3, [r3, #8]
	ldr	r0, [r3, #4]
	str	r0, [sp, #16]
	mov	r0, r10
	ldr	r3, [r3]
	str	r3, [sp, #12]
	ldr	r3, [r1, #12]
	str	r3, [sp, #8]
	ldr	r3, [r1, #8]
	str	r3, [sp, #4]
	ldr	r3, [r1, #4]
	str	r3, [sp]
	ldr	r3, [r1]
	ubfx	r1, r2, #10, #16
	bl	printf
	b	.L3366
.L3369:
	ldr	r1, .L3375+20
	movs	r6, #0
	ldr	r3, .L3375+24
	mov	r4, r6
	ldr	r7, [r8]
	mov	fp, #36
	ldr	r1, [r1]
	ldrh	r2, [r3]
	ldr	r3, .L3375+28
	str	r1, [sp, #24]
	ldr	r1, .L3375+32
	ldr	r3, [r3]
	ldrh	r10, [r1]
	b	.L3371
.L3372:
	ldr	r10, .L3375+44
	mov	r0, r4
	ldr	r2, [r10]
	ldrh	r2, [r2, r5]
	orr	r3, r3, r2, lsl #10
	movs	r2, #1
	mov	r1, r2
	str	r3, [r4, #4]
	bl	FlashReadPages
	ldr	r2, [r4, #8]
	ldr	r1, [r10]
	ldr	r3, [r4, #12]
	ldr	r0, [r2, #4]
	ldrh	r1, [r1, r5]
	str	r0, [sp, #20]
	ldr	r2, [r2]
	ldr	r0, .L3375+36
	str	r2, [sp, #16]
	ldr	r2, [r3, #12]
	str	r2, [sp, #12]
	ldr	r2, [r3, #8]
	str	r2, [sp, #8]
	ldr	r2, [r3, #4]
	str	r2, [sp, #4]
	ldr	r3, [r3]
	str	r3, [sp]
	ldm	r4, {r2, r3}
	bl	printf
.L3374:
	ldrh	r2, [r8]
	sxth	r3, r6
	adds	r6, r6, #1
	cmp	r3, r2
	blt	.L3372
	adds	r7, r7, #1
	b	.L3370
.L3373:
	ldr	r3, .L3375+40
	movs	r2, #2
	ldr	r1, .L3375+44
	ldr	r0, .L3375+48
	ldr	r3, [r3]
	ldr	r1, [r1]
	bl	rknand_print_hex
	ldr	r4, .L3375+52
	movs	r2, #4
	ldr	r1, .L3375+56
	ldr	r0, .L3375+60
	ldrh	r3, [r4]
	ldr	r1, [r1]
	bl	rknand_print_hex
	ldr	r1, .L3375+64
	movs	r2, #4
	ldrh	r3, [r4]
	ldr	r0, .L3375+68
	ldr	r1, [r1]
	add	sp, sp, #40
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r10, fp, lr}
	b	rknand_print_hex
.L3376:
	.align	2
.L3375:
	.word	.LANCHOR40
	.word	.LANCHOR41
	.word	.LANCHOR211
	.word	.LANCHOR131
	.word	.LANCHOR47
	.word	.LANCHOR108
	.word	.LANCHOR38
	.word	.LANCHOR107
	.word	.LANCHOR58
	.word	.LC51
	.word	.LANCHOR64
	.word	.LANCHOR132
	.word	.LC87
	.word	.LANCHOR66
	.word	.LANCHOR134
	.word	.LC88
	.word	.LANCHOR203
	.word	.LC89
	.word	.LANCHOR186
	.word	.LANCHOR53
	.word	.LC86
	.size	dump_map_info, .-dump_map_info
	.global	FtlMallocOffset
	.global	FtlMallocBuffer
	.global	LastWritenPbaAddr
	.global	gc_ink_free_return_value
	.global	check_valid_page_count_table
	.global	FtlUpdateVaildLpnCount
	.global	g_ect_tbl_power_up_flush
	.global	last_cache_match_count
	.global	power_up_flag
	.global	g_LowFormat
	.global	gFtlInitStatus
	.global	DeviceCapacity
	.global	ToshibaRefValue
	.global	Toshiba15RefValue
	.global	ToshibaA19RefValue
	.global	SamsungRefValue
	.global	refValueDefault
	.global	random_seed
	.global	gSlcNandParaInfo
	.global	gNandParaInfo
	.global	g_page_map_check_enable
	.global	g_power_lost_ecc_error_blk
	.global	g_power_lost_recovery_flag
	.global	c_mlc_erase_count_value
	.global	g_recovery_ppa_tbl
	.global	g_recovery_page_min_ver
	.global	g_recovery_page_num
	.global	g_cur_erase_blk
	.global	g_gc_skip_write_count
	.global	g_gc_head_data_block_count
	.global	g_gc_head_data_block
	.global	g_ftl_nand_free_count
	.global	g_in_swl_replace
	.global	g_in_gc_progress
	.global	g_all_blk_used_slc_mode
	.global	g_max_erase_count
	.global	g_totle_sys_slc_erase_count
	.global	g_totle_slc_erase_count
	.global	g_min_erase_count
	.global	g_totle_avg_erase_count
	.global	g_totle_mlc_erase_count
	.global	g_totle_l2p_write_count
	.global	g_totle_cache_write_count
	.global	g_tmp_data_superblock_id
	.global	g_totle_read_page_count
	.global	g_totle_discard_page_count
	.global	g_totle_read_sector
	.global	g_totle_write_sector
	.global	g_totle_write_page_count
	.global	g_totle_gc_page_count
	.global	g_gc_blk_index
	.global	g_gc_merge_free_blk_threshold
	.global	g_gc_free_blk_threshold
	.global	g_gc_refresh_block_temp_tbl
	.global	g_free_slc_blk_num
	.global	g_gc_refresh_block_temp_num
	.global	g_gc_bad_block_temp_tbl
	.global	g_gc_bad_block_gc_index
	.global	g_gc_bad_block_temp_num
	.global	g_gc_next_blk_3
	.global	g_gc_next_blk_2
	.global	g_gc_next_blk_1
	.global	g_gc_next_blk
	.global	g_gc_cur_blk_max_valid_pages
	.global	g_gc_cur_blk_valid_pages
	.global	g_gc_page_offset
	.global	g_gc_blk_num
	.global	p_gc_blk_tbl
	.global	p_gc_page_info
	.global	g_sys_ext_data
	.global	g_sys_save_data
	.global	gp_last_act_superblock
	.global	g_gc_superblock
	.global	g_gc_temp_superblock
	.global	g_buffer_superblock
	.global	g_active_superblock
	.global	g_num_data_superblocks
	.global	g_num_free_superblocks
	.global	p_data_block_list_tail
	.global	p_data_block_list_head
	.global	p_free_data_block_list_head
	.global	p_data_block_list_table
	.global	g_l2p_last_update_region_id
	.global	p_l2p_map_buf
	.global	p_l2p_ram_map
	.global	g_totle_vendor_block
	.global	p_vendor_region_ppn_table
	.global	p_vendor_block_ver_table
	.global	p_vendor_block_valid_page_count
	.global	p_vendor_block_table
	.global	g_totle_map_block
	.global	p_map_region_ppn_check_table
	.global	p_map_region_ppn_table
	.global	p_map_block_ver_table
	.global	p_map_block_valid_page_count
	.global	p_map_block_table
	.global	p_blk_mode_table
	.global	p_valid_page_count_table
	.global	g_totle_swl_count
	.global	p_swl_mul_table
	.global	p_erase_count_table
	.global	g_ect_tbl_info_size
	.global	gp_ect_tbl_info
	.global	g_gc_num_req
	.global	c_gc_page_buf_num
	.global	gp_gc_page_buf_info
	.global	p_gc_data_buf
	.global	p_gc_spare_buf
	.global	p_io_spare_buf
	.global	p_io_data_buf_1
	.global	p_io_data_buf_0
	.global	p_sys_spare_buf
	.global	p_vendor_data_buf
	.global	p_sys_data_buf_1
	.global	p_sys_data_buf
	.global	g_wr_page_num
	.global	req_wr_io
	.global	c_wr_page_buf_num
	.global	p_wr_io_data_buf
	.global	p_wr_io_spare_buf
	.global	p_plane_order_table
	.global	g_req_cache
	.global	req_gc_dst
	.global	req_gc
	.global	req_erase
	.global	req_prgm
	.global	req_read
	.global	req_sys
	.global	gVendorBlkInfo
	.global	gL2pMapInfo
	.global	gSysFreeQueue
	.global	gSysInfo
	.global	gBbtInfo
	.global	g_flash_read_only_en
	.global	g_inkDie_check_enable
	.global	g_SlcPartLbaEndSector
	.global	g_MaxLbn
	.global	g_VaildLpn
	.global	g_MaxLpn
	.global	g_MaxLbaSector
	.global	g_GlobalDataVersion
	.global	g_GlobalSysVersion
	.global	ftl_gc_temp_power_lost_recovery_flag
	.global	c_ftl_nand_max_data_blks
	.global	c_ftl_nand_data_op_blks_per_plane
	.global	c_ftl_nand_data_blks_per_plane
	.global	c_ftl_nand_max_sys_blks
	.global	c_ftl_nand_init_sys_blks_per_plane
	.global	c_ftl_nand_sys_blks_per_plane
	.global	c_ftl_vendor_part_size
	.global	c_ftl_nand_max_vendor_blks
	.global	c_ftl_nand_max_map_blks
	.global	c_ftl_nand_map_blks_per_plane
	.global	c_ftl_nand_vendor_region_num
	.global	c_ftl_nand_l2pmap_ram_region_num
	.global	c_ftl_nand_map_region_num
	.global	c_ftl_nand_totle_phy_blks
	.global	c_ftl_nand_reserved_blks
	.global	c_ftl_nand_byte_pre_oob
	.global	c_ftl_nand_byte_pre_page
	.global	c_ftl_nand_sec_pre_page_shift
	.global	c_ftl_nand_sec_pre_page
	.global	c_ftl_nand_page_pre_super_blk
	.global	c_ftl_nand_page_pre_slc_blk
	.global	c_ftl_nand_page_pre_blk
	.global	c_ftl_nand_bbm_buf_size
	.global	c_ftl_nand_ext_blk_pre_plane
	.global	c_ftl_nand_blk_pre_plane
	.global	c_ftl_nand_planes_num
	.global	c_ftl_nand_blks_per_die
	.global	c_ftl_nand_planes_per_die
	.global	c_ftl_nand_die_num
	.global	c_ftl_nand_type
	.global	gMasterTempBuf
	.global	gMasterInfo
	.global	gNandcDumpWriteEn
	.global	gToggleModeClkDiv
	.global	gBootDdrMode
	.global	gNandcEccBits
	.global	gpNandc1
	.global	gpNandc
	.global	g_nandc_version_data
	.global	gNandcVer
	.global	gNandChipMap
	.global	gNandIDataBuf
	.global	idb_flash_slc_mode
	.global	FlashDdrTunningReadCount
	.global	FlashWaitBusyScheduleEn
	.global	gNandPhyInfo
	.global	gFlashProgCheckSpareBuffer
	.global	gFlashProgCheckBuffer
	.global	gFlashSpareBuffer
	.global	gFlashPageBuffer1
	.global	gFlashPageBuffer0
	.global	gpFlashSaveInfo
	.global	gReadRetryInfo
	.global	gpNandParaInfo
	.global	gNandOptPara
	.global	g_nand_ecc_en
	.global	g_slc2KBNand
	.global	g_maxRetryCount
	.global	g_maxRegNum
	.global	g_retryMode
	.global	gNandIDBResBlkNumSaveInFlash
	.global	gNandIDBResBlkNum
	.global	gNandFlashResEndPageAddr
	.global	gNandFlashInfoBlockAddr
	.global	gNandFlashIdbBlockAddr
	.global	gNandFlashInfoBlockEcc
	.global	gNandFlashIDBEccBits
	.global	gNandFlashEccBits
	.global	gNandRandomizer
	.global	gBlockPageAlignSize
	.global	gTotleBlock
	.global	gNandMaxChip
	.global	gNandMaxDie
	.global	gFlashInterfaceMode
	.global	gFlashCurMode
	.global	gFlashSlcMode
	.global	gFlashOnfiModeEn
	.global	gFlashToggleModeEn
	.global	gFlashSdrModeEn
	.global	gMultiPageProgEn
	.global	gMultiPageReadEn
	.global	gpReadRetrial
	.global	mlcPageToSlcPageTbl
	.global	slcPageToMlcPageTbl
	.global	DieAddrs
	.global	gDieOp
	.global	DieCsIndex
	.global	IDByte
	.global	read_retry_cur_offset
	.section	.bss.DeviceCapacity,"aw",%nobits
	.align	2
	.set	.LANCHOR60,. + 0
	.type	DeviceCapacity, %object
	.size	DeviceCapacity, 4
DeviceCapacity:
	.space	4
	.section	.bss.DieAddrs,"aw",%nobits
	.align	2
	.set	.LANCHOR18,. + 0
	.type	DieAddrs, %object
	.size	DieAddrs, 32
DieAddrs:
	.space	32
	.section	.bss.DieCsIndex,"aw",%nobits
	.align	2
	.set	.LANCHOR27,. + 0
	.type	DieCsIndex, %object
	.size	DieCsIndex, 8
DieCsIndex:
	.space	8
	.section	.bss.FlashDdrTunningReadCount,"aw",%nobits
	.align	2
	.set	.LANCHOR144,. + 0
	.type	FlashDdrTunningReadCount, %object
	.size	FlashDdrTunningReadCount, 4
FlashDdrTunningReadCount:
	.space	4
	.section	.bss.FlashWaitBusyScheduleEn,"aw",%nobits
	.align	2
	.type	FlashWaitBusyScheduleEn, %object
	.size	FlashWaitBusyScheduleEn, 4
FlashWaitBusyScheduleEn:
	.space	4
	.section	.bss.FtlMallocBuffer,"aw",%nobits
	.align	6
	.type	FtlMallocBuffer, %object
	.size	FtlMallocBuffer, 1310720
FtlMallocBuffer:
	.space	1310720
	.section	.bss.FtlUpdateVaildLpnCount,"aw",%nobits
	.align	1
	.set	.LANCHOR101,. + 0
	.type	FtlUpdateVaildLpnCount, %object
	.size	FtlUpdateVaildLpnCount, 2
FtlUpdateVaildLpnCount:
	.space	2
	.section	.bss.IDByte,"aw",%nobits
	.align	2
	.set	.LANCHOR22,. + 0
	.type	IDByte, %object
	.size	IDByte, 32
IDByte:
	.space	32
	.section	.bss.c_ftl_nand_bbm_buf_size,"aw",%nobits
	.align	1
	.set	.LANCHOR126,. + 0
	.type	c_ftl_nand_bbm_buf_size, %object
	.size	c_ftl_nand_bbm_buf_size, 2
c_ftl_nand_bbm_buf_size:
	.space	2
	.section	.bss.c_ftl_nand_blk_pre_plane,"aw",%nobits
	.align	1
	.set	.LANCHOR41,. + 0
	.type	c_ftl_nand_blk_pre_plane, %object
	.size	c_ftl_nand_blk_pre_plane, 2
c_ftl_nand_blk_pre_plane:
	.space	2
	.section	.bss.c_ftl_nand_blks_per_die,"aw",%nobits
	.align	1
	.set	.LANCHOR51,. + 0
	.type	c_ftl_nand_blks_per_die, %object
	.size	c_ftl_nand_blks_per_die, 2
c_ftl_nand_blks_per_die:
	.space	2
	.section	.bss.c_ftl_nand_byte_pre_oob,"aw",%nobits
	.align	1
	.set	.LANCHOR58,. + 0
	.type	c_ftl_nand_byte_pre_oob, %object
	.size	c_ftl_nand_byte_pre_oob, 2
c_ftl_nand_byte_pre_oob:
	.space	2
	.section	.bss.c_ftl_nand_byte_pre_page,"aw",%nobits
	.align	1
	.set	.LANCHOR57,. + 0
	.type	c_ftl_nand_byte_pre_page, %object
	.size	c_ftl_nand_byte_pre_page, 2
c_ftl_nand_byte_pre_page:
	.space	2
	.section	.bss.c_ftl_nand_data_blks_per_plane,"aw",%nobits
	.align	1
	.set	.LANCHOR40,. + 0
	.type	c_ftl_nand_data_blks_per_plane, %object
	.size	c_ftl_nand_data_blks_per_plane, 2
c_ftl_nand_data_blks_per_plane:
	.space	2
	.section	.bss.c_ftl_nand_data_op_blks_per_plane,"aw",%nobits
	.align	1
	.set	.LANCHOR232,. + 0
	.type	c_ftl_nand_data_op_blks_per_plane, %object
	.size	c_ftl_nand_data_op_blks_per_plane, 2
c_ftl_nand_data_op_blks_per_plane:
	.space	2
	.section	.bss.c_ftl_nand_die_num,"aw",%nobits
	.align	1
	.set	.LANCHOR45,. + 0
	.type	c_ftl_nand_die_num, %object
	.size	c_ftl_nand_die_num, 2
c_ftl_nand_die_num:
	.space	2
	.section	.bss.c_ftl_nand_ext_blk_pre_plane,"aw",%nobits
	.align	1
	.set	.LANCHOR49,. + 0
	.type	c_ftl_nand_ext_blk_pre_plane, %object
	.size	c_ftl_nand_ext_blk_pre_plane, 2
c_ftl_nand_ext_blk_pre_plane:
	.space	2
	.section	.bss.c_ftl_nand_init_sys_blks_per_plane,"aw",%nobits
	.align	2
	.set	.LANCHOR65,. + 0
	.type	c_ftl_nand_init_sys_blks_per_plane, %object
	.size	c_ftl_nand_init_sys_blks_per_plane, 4
c_ftl_nand_init_sys_blks_per_plane:
	.space	4
	.section	.bss.c_ftl_nand_l2pmap_ram_region_num,"aw",%nobits
	.align	1
	.set	.LANCHOR67,. + 0
	.type	c_ftl_nand_l2pmap_ram_region_num, %object
	.size	c_ftl_nand_l2pmap_ram_region_num, 2
c_ftl_nand_l2pmap_ram_region_num:
	.space	2
	.section	.bss.c_ftl_nand_map_blks_per_plane,"aw",%nobits
	.align	1
	.set	.LANCHOR63,. + 0
	.type	c_ftl_nand_map_blks_per_plane, %object
	.size	c_ftl_nand_map_blks_per_plane, 2
c_ftl_nand_map_blks_per_plane:
	.space	2
	.section	.bss.c_ftl_nand_map_region_num,"aw",%nobits
	.align	1
	.set	.LANCHOR66,. + 0
	.type	c_ftl_nand_map_region_num, %object
	.size	c_ftl_nand_map_region_num, 2
c_ftl_nand_map_region_num:
	.space	2
	.section	.bss.c_ftl_nand_max_data_blks,"aw",%nobits
	.align	2
	.set	.LANCHOR42,. + 0
	.type	c_ftl_nand_max_data_blks, %object
	.size	c_ftl_nand_max_data_blks, 4
c_ftl_nand_max_data_blks:
	.space	4
	.section	.bss.c_ftl_nand_max_map_blks,"aw",%nobits
	.align	2
	.set	.LANCHOR64,. + 0
	.type	c_ftl_nand_max_map_blks, %object
	.size	c_ftl_nand_max_map_blks, 4
c_ftl_nand_max_map_blks:
	.space	4
	.section	.bss.c_ftl_nand_max_sys_blks,"aw",%nobits
	.align	2
	.set	.LANCHOR39,. + 0
	.type	c_ftl_nand_max_sys_blks, %object
	.size	c_ftl_nand_max_sys_blks, 4
c_ftl_nand_max_sys_blks:
	.space	4
	.section	.bss.c_ftl_nand_max_vendor_blks,"aw",%nobits
	.align	1
	.set	.LANCHOR61,. + 0
	.type	c_ftl_nand_max_vendor_blks, %object
	.size	c_ftl_nand_max_vendor_blks, 2
c_ftl_nand_max_vendor_blks:
	.space	2
	.section	.bss.c_ftl_nand_page_pre_blk,"aw",%nobits
	.align	1
	.set	.LANCHOR52,. + 0
	.type	c_ftl_nand_page_pre_blk, %object
	.size	c_ftl_nand_page_pre_blk, 2
c_ftl_nand_page_pre_blk:
	.space	2
	.section	.bss.c_ftl_nand_page_pre_slc_blk,"aw",%nobits
	.align	1
	.set	.LANCHOR53,. + 0
	.type	c_ftl_nand_page_pre_slc_blk, %object
	.size	c_ftl_nand_page_pre_slc_blk, 2
c_ftl_nand_page_pre_slc_blk:
	.space	2
	.section	.bss.c_ftl_nand_page_pre_super_blk,"aw",%nobits
	.align	1
	.set	.LANCHOR54,. + 0
	.type	c_ftl_nand_page_pre_super_blk, %object
	.size	c_ftl_nand_page_pre_super_blk, 2
c_ftl_nand_page_pre_super_blk:
	.space	2
	.section	.bss.c_ftl_nand_planes_num,"aw",%nobits
	.align	1
	.set	.LANCHOR38,. + 0
	.type	c_ftl_nand_planes_num, %object
	.size	c_ftl_nand_planes_num, 2
c_ftl_nand_planes_num:
	.space	2
	.section	.bss.c_ftl_nand_planes_per_die,"aw",%nobits
	.align	1
	.set	.LANCHOR46,. + 0
	.type	c_ftl_nand_planes_per_die, %object
	.size	c_ftl_nand_planes_per_die, 2
c_ftl_nand_planes_per_die:
	.space	2
	.section	.bss.c_ftl_nand_reserved_blks,"aw",%nobits
	.align	1
	.set	.LANCHOR59,. + 0
	.type	c_ftl_nand_reserved_blks, %object
	.size	c_ftl_nand_reserved_blks, 2
c_ftl_nand_reserved_blks:
	.space	2
	.section	.bss.c_ftl_nand_sec_pre_page,"aw",%nobits
	.align	1
	.set	.LANCHOR55,. + 0
	.type	c_ftl_nand_sec_pre_page, %object
	.size	c_ftl_nand_sec_pre_page, 2
c_ftl_nand_sec_pre_page:
	.space	2
	.section	.bss.c_ftl_nand_sec_pre_page_shift,"aw",%nobits
	.align	1
	.set	.LANCHOR56,. + 0
	.type	c_ftl_nand_sec_pre_page_shift, %object
	.size	c_ftl_nand_sec_pre_page_shift, 2
c_ftl_nand_sec_pre_page_shift:
	.space	2
	.section	.bss.c_ftl_nand_sys_blks_per_plane,"aw",%nobits
	.align	2
	.set	.LANCHOR37,. + 0
	.type	c_ftl_nand_sys_blks_per_plane, %object
	.size	c_ftl_nand_sys_blks_per_plane, 4
c_ftl_nand_sys_blks_per_plane:
	.space	4
	.section	.bss.c_ftl_nand_totle_phy_blks,"aw",%nobits
	.align	2
	.set	.LANCHOR43,. + 0
	.type	c_ftl_nand_totle_phy_blks, %object
	.size	c_ftl_nand_totle_phy_blks, 4
c_ftl_nand_totle_phy_blks:
	.space	4
	.section	.bss.c_ftl_nand_type,"aw",%nobits
	.align	1
	.set	.LANCHOR44,. + 0
	.type	c_ftl_nand_type, %object
	.size	c_ftl_nand_type, 2
c_ftl_nand_type:
	.space	2
	.section	.bss.c_ftl_nand_vendor_region_num,"aw",%nobits
	.align	1
	.set	.LANCHOR62,. + 0
	.type	c_ftl_nand_vendor_region_num, %object
	.size	c_ftl_nand_vendor_region_num, 2
c_ftl_nand_vendor_region_num:
	.space	2
	.section	.bss.c_ftl_vendor_part_size,"aw",%nobits
	.align	1
	.set	.LANCHOR50,. + 0
	.type	c_ftl_vendor_part_size, %object
	.size	c_ftl_vendor_part_size, 2
c_ftl_vendor_part_size:
	.space	2
	.section	.bss.c_gc_page_buf_num,"aw",%nobits
	.align	2
	.set	.LANCHOR110,. + 0
	.type	c_gc_page_buf_num, %object
	.size	c_gc_page_buf_num, 4
c_gc_page_buf_num:
	.space	4
	.section	.bss.c_mlc_erase_count_value,"aw",%nobits
	.align	1
	.set	.LANCHOR48,. + 0
	.type	c_mlc_erase_count_value, %object
	.size	c_mlc_erase_count_value, 2
c_mlc_erase_count_value:
	.space	2
	.section	.bss.c_wr_page_buf_num,"aw",%nobits
	.align	2
	.set	.LANCHOR185,. + 0
	.type	c_wr_page_buf_num, %object
	.size	c_wr_page_buf_num, 4
c_wr_page_buf_num:
	.space	4
	.section	.bss.check_valid_page_count_table,"aw",%nobits
	.align	1
	.type	check_valid_page_count_table, %object
	.size	check_valid_page_count_table, 8192
check_valid_page_count_table:
	.space	8192
	.section	.bss.ftl_gc_temp_power_lost_recovery_flag,"aw",%nobits
	.align	2
	.set	.LANCHOR138,. + 0
	.type	ftl_gc_temp_power_lost_recovery_flag, %object
	.size	ftl_gc_temp_power_lost_recovery_flag, 4
ftl_gc_temp_power_lost_recovery_flag:
	.space	4
	.section	.bss.gBbtInfo,"aw",%nobits
	.align	2
	.set	.LANCHOR76,. + 0
	.type	gBbtInfo, %object
	.size	gBbtInfo, 60
gBbtInfo:
	.space	60
	.section	.bss.gBlockPageAlignSize,"aw",%nobits
	.align	2
	.set	.LANCHOR4,. + 0
	.type	gBlockPageAlignSize, %object
	.size	gBlockPageAlignSize, 4
gBlockPageAlignSize:
	.space	4
	.section	.bss.gBootDdrMode,"aw",%nobits
	.align	2
	.set	.LANCHOR160,. + 0
	.type	gBootDdrMode, %object
	.size	gBootDdrMode, 4
gBootDdrMode:
	.space	4
	.section	.bss.gDieOp,"aw",%nobits
	.align	2
	.set	.LANCHOR23,. + 0
	.type	gDieOp, %object
	.size	gDieOp, 128
gDieOp:
	.space	128
	.section	.bss.gFlashCurMode,"aw",%nobits
	.set	.LANCHOR24,. + 0
	.type	gFlashCurMode, %object
	.size	gFlashCurMode, 1
gFlashCurMode:
	.space	1
	.section	.bss.gFlashInterfaceMode,"aw",%nobits
	.set	.LANCHOR25,. + 0
	.type	gFlashInterfaceMode, %object
	.size	gFlashInterfaceMode, 1
gFlashInterfaceMode:
	.space	1
	.section	.bss.gFlashOnfiModeEn,"aw",%nobits
	.type	gFlashOnfiModeEn, %object
	.size	gFlashOnfiModeEn, 1
gFlashOnfiModeEn:
	.space	1
	.section	.bss.gFlashPageBuffer0,"aw",%nobits
	.align	2
	.set	.LANCHOR154,. + 0
	.type	gFlashPageBuffer0, %object
	.size	gFlashPageBuffer0, 4
gFlashPageBuffer0:
	.space	4
	.section	.bss.gFlashPageBuffer1,"aw",%nobits
	.align	2
	.set	.LANCHOR149,. + 0
	.type	gFlashPageBuffer1, %object
	.size	gFlashPageBuffer1, 4
gFlashPageBuffer1:
	.space	4
	.section	.bss.gFlashProgCheckBuffer,"aw",%nobits
	.align	2
	.set	.LANCHOR206,. + 0
	.type	gFlashProgCheckBuffer, %object
	.size	gFlashProgCheckBuffer, 4
gFlashProgCheckBuffer:
	.space	4
	.section	.bss.gFlashProgCheckSpareBuffer,"aw",%nobits
	.align	2
	.set	.LANCHOR207,. + 0
	.type	gFlashProgCheckSpareBuffer, %object
	.size	gFlashProgCheckSpareBuffer, 4
gFlashProgCheckSpareBuffer:
	.space	4
	.section	.bss.gFlashSdrModeEn,"aw",%nobits
	.type	gFlashSdrModeEn, %object
	.size	gFlashSdrModeEn, 1
gFlashSdrModeEn:
	.space	1
	.section	.bss.gFlashSlcMode,"aw",%nobits
	.set	.LANCHOR16,. + 0
	.type	gFlashSlcMode, %object
	.size	gFlashSlcMode, 1
gFlashSlcMode:
	.space	1
	.section	.bss.gFlashSpareBuffer,"aw",%nobits
	.align	2
	.set	.LANCHOR205,. + 0
	.type	gFlashSpareBuffer, %object
	.size	gFlashSpareBuffer, 4
gFlashSpareBuffer:
	.space	4
	.section	.bss.gFlashToggleModeEn,"aw",%nobits
	.set	.LANCHOR30,. + 0
	.type	gFlashToggleModeEn, %object
	.size	gFlashToggleModeEn, 1
gFlashToggleModeEn:
	.space	1
	.section	.bss.gL2pMapInfo,"aw",%nobits
	.align	2
	.set	.LANCHOR130,. + 0
	.type	gL2pMapInfo, %object
	.size	gL2pMapInfo, 44
gL2pMapInfo:
	.space	44
	.section	.bss.gMasterInfo,"aw",%nobits
	.align	2
	.set	.LANCHOR35,. + 0
	.type	gMasterInfo, %object
	.size	gMasterInfo, 32
gMasterInfo:
	.space	32
	.section	.bss.gMasterTempBuf,"aw",%nobits
	.align	2
	.set	.LANCHOR161,. + 0
	.type	gMasterTempBuf, %object
	.size	gMasterTempBuf, 4
gMasterTempBuf:
	.space	4
	.section	.bss.gMultiPageProgEn,"aw",%nobits
	.set	.LANCHOR28,. + 0
	.type	gMultiPageProgEn, %object
	.size	gMultiPageProgEn, 1
gMultiPageProgEn:
	.space	1
	.section	.bss.gMultiPageReadEn,"aw",%nobits
	.set	.LANCHOR210,. + 0
	.type	gMultiPageReadEn, %object
	.size	gMultiPageReadEn, 1
gMultiPageReadEn:
	.space	1
	.section	.bss.gNandChipMap,"aw",%nobits
	.align	2
	.set	.LANCHOR0,. + 0
	.type	gNandChipMap, %object
	.size	gNandChipMap, 32
gNandChipMap:
	.space	32
	.section	.bss.gNandFlashEccBits,"aw",%nobits
	.set	.LANCHOR33,. + 0
	.type	gNandFlashEccBits, %object
	.size	gNandFlashEccBits, 1
gNandFlashEccBits:
	.space	1
	.section	.bss.gNandFlashIDBEccBits,"aw",%nobits
	.set	.LANCHOR158,. + 0
	.type	gNandFlashIDBEccBits, %object
	.size	gNandFlashIDBEccBits, 1
gNandFlashIDBEccBits:
	.space	1
	.section	.bss.gNandFlashIdbBlockAddr,"aw",%nobits
	.align	2
	.set	.LANCHOR156,. + 0
	.type	gNandFlashIdbBlockAddr, %object
	.size	gNandFlashIdbBlockAddr, 4
gNandFlashIdbBlockAddr:
	.space	4
	.section	.bss.gNandFlashInfoBlockAddr,"aw",%nobits
	.align	2
	.set	.LANCHOR155,. + 0
	.type	gNandFlashInfoBlockAddr, %object
	.size	gNandFlashInfoBlockAddr, 4
gNandFlashInfoBlockAddr:
	.space	4
	.section	.bss.gNandFlashInfoBlockEcc,"aw",%nobits
	.type	gNandFlashInfoBlockEcc, %object
	.size	gNandFlashInfoBlockEcc, 1
gNandFlashInfoBlockEcc:
	.space	1
	.section	.bss.gNandFlashResEndPageAddr,"aw",%nobits
	.align	2
	.type	gNandFlashResEndPageAddr, %object
	.size	gNandFlashResEndPageAddr, 4
gNandFlashResEndPageAddr:
	.space	4
	.section	.bss.gNandIDBResBlkNum,"aw",%nobits
	.set	.LANCHOR3,. + 0
	.type	gNandIDBResBlkNum, %object
	.size	gNandIDBResBlkNum, 1
gNandIDBResBlkNum:
	.space	1
	.section	.bss.gNandIDBResBlkNumSaveInFlash,"aw",%nobits
	.set	.LANCHOR157,. + 0
	.type	gNandIDBResBlkNumSaveInFlash, %object
	.size	gNandIDBResBlkNumSaveInFlash, 1
gNandIDBResBlkNumSaveInFlash:
	.space	1
	.section	.bss.gNandIDataBuf,"aw",%nobits
	.align	2
	.set	.LANCHOR150,. + 0
	.type	gNandIDataBuf, %object
	.size	gNandIDataBuf, 2048
gNandIDataBuf:
	.space	2048
	.section	.bss.gNandMaxChip,"aw",%nobits
	.set	.LANCHOR124,. + 0
	.type	gNandMaxChip, %object
	.size	gNandMaxChip, 1
gNandMaxChip:
	.space	1
	.section	.bss.gNandMaxDie,"aw",%nobits
	.set	.LANCHOR26,. + 0
	.type	gNandMaxDie, %object
	.size	gNandMaxDie, 1
gNandMaxDie:
	.space	1
	.section	.bss.gNandOptPara,"aw",%nobits
	.set	.LANCHOR8,. + 0
	.type	gNandOptPara, %object
	.size	gNandOptPara, 32
gNandOptPara:
	.space	32
	.section	.bss.gNandPhyInfo,"aw",%nobits
	.align	2
	.set	.LANCHOR15,. + 0
	.type	gNandPhyInfo, %object
	.size	gNandPhyInfo, 28
gNandPhyInfo:
	.space	28
	.section	.bss.gNandRandomizer,"aw",%nobits
	.set	.LANCHOR6,. + 0
	.type	gNandRandomizer, %object
	.size	gNandRandomizer, 1
gNandRandomizer:
	.space	1
	.section	.bss.gNandcDumpWriteEn,"aw",%nobits
	.align	2
	.set	.LANCHOR36,. + 0
	.type	gNandcDumpWriteEn, %object
	.size	gNandcDumpWriteEn, 4
gNandcDumpWriteEn:
	.space	4
	.section	.bss.gNandcEccBits,"aw",%nobits
	.align	2
	.set	.LANCHOR32,. + 0
	.type	gNandcEccBits, %object
	.size	gNandcEccBits, 4
gNandcEccBits:
	.space	4
	.section	.bss.gNandcVer,"aw",%nobits
	.align	2
	.set	.LANCHOR34,. + 0
	.type	gNandcVer, %object
	.size	gNandcVer, 4
gNandcVer:
	.space	4
	.section	.bss.gReadRetryInfo,"aw",%nobits
	.set	.LANCHOR20,. + 0
	.type	gReadRetryInfo, %object
	.size	gReadRetryInfo, 852
gReadRetryInfo:
	.space	852
	.section	.bss.gSysFreeQueue,"aw",%nobits
	.align	1
	.set	.LANCHOR77,. + 0
	.type	gSysFreeQueue, %object
	.size	gSysFreeQueue, 2056
gSysFreeQueue:
	.space	2056
	.section	.bss.gSysInfo,"aw",%nobits
	.align	2
	.set	.LANCHOR218,. + 0
	.type	gSysInfo, %object
	.size	gSysInfo, 16
gSysInfo:
	.space	16
	.section	.bss.gToggleModeClkDiv,"aw",%nobits
	.align	2
	.type	gToggleModeClkDiv, %object
	.size	gToggleModeClkDiv, 4
gToggleModeClkDiv:
	.space	4
	.section	.bss.gTotleBlock,"aw",%nobits
	.align	1
	.set	.LANCHOR125,. + 0
	.type	gTotleBlock, %object
	.size	gTotleBlock, 2
gTotleBlock:
	.space	2
	.section	.bss.gVendorBlkInfo,"aw",%nobits
	.align	2
	.set	.LANCHOR224,. + 0
	.type	gVendorBlkInfo, %object
	.size	gVendorBlkInfo, 44
gVendorBlkInfo:
	.space	44
	.section	.bss.g_GlobalDataVersion,"aw",%nobits
	.align	2
	.set	.LANCHOR165,. + 0
	.type	g_GlobalDataVersion, %object
	.size	g_GlobalDataVersion, 4
g_GlobalDataVersion:
	.space	4
	.section	.bss.g_GlobalSysVersion,"aw",%nobits
	.align	2
	.set	.LANCHOR164,. + 0
	.type	g_GlobalSysVersion, %object
	.size	g_GlobalSysVersion, 4
g_GlobalSysVersion:
	.space	4
	.section	.bss.g_LowFormat,"aw",%nobits
	.align	2
	.set	.LANCHOR254,. + 0
	.type	g_LowFormat, %object
	.size	g_LowFormat, 4
g_LowFormat:
	.space	4
	.section	.bss.g_MaxLbaSector,"aw",%nobits
	.align	2
	.set	.LANCHOR68,. + 0
	.type	g_MaxLbaSector, %object
	.size	g_MaxLbaSector, 4
g_MaxLbaSector:
	.space	4
	.section	.bss.g_MaxLbn,"aw",%nobits
	.align	2
	.set	.LANCHOR231,. + 0
	.type	g_MaxLbn, %object
	.size	g_MaxLbn, 4
g_MaxLbn:
	.space	4
	.section	.bss.g_MaxLpn,"aw",%nobits
	.align	2
	.set	.LANCHOR74,. + 0
	.type	g_MaxLpn, %object
	.size	g_MaxLpn, 4
g_MaxLpn:
	.space	4
	.section	.bss.g_SlcPartLbaEndSector,"aw",%nobits
	.align	2
	.set	.LANCHOR162,. + 0
	.type	g_SlcPartLbaEndSector, %object
	.size	g_SlcPartLbaEndSector, 4
g_SlcPartLbaEndSector:
	.space	4
	.section	.bss.g_VaildLpn,"aw",%nobits
	.align	2
	.set	.LANCHOR102,. + 0
	.type	g_VaildLpn, %object
	.size	g_VaildLpn, 4
g_VaildLpn:
	.space	4
	.section	.bss.g_active_superblock,"aw",%nobits
	.align	2
	.set	.LANCHOR93,. + 0
	.type	g_active_superblock, %object
	.size	g_active_superblock, 48
g_active_superblock:
	.space	48
	.section	.bss.g_all_blk_used_slc_mode,"aw",%nobits
	.align	2
	.set	.LANCHOR163,. + 0
	.type	g_all_blk_used_slc_mode, %object
	.size	g_all_blk_used_slc_mode, 4
g_all_blk_used_slc_mode:
	.space	4
	.section	.bss.g_buffer_superblock,"aw",%nobits
	.align	2
	.set	.LANCHOR94,. + 0
	.type	g_buffer_superblock, %object
	.size	g_buffer_superblock, 48
g_buffer_superblock:
	.space	48
	.section	.bss.g_cur_erase_blk,"aw",%nobits
	.align	2
	.set	.LANCHOR75,. + 0
	.type	g_cur_erase_blk, %object
	.size	g_cur_erase_blk, 4
g_cur_erase_blk:
	.space	4
	.section	.bss.g_ect_tbl_info_size,"aw",%nobits
	.align	1
	.set	.LANCHOR198,. + 0
	.type	g_ect_tbl_info_size, %object
	.size	g_ect_tbl_info_size, 2
g_ect_tbl_info_size:
	.space	2
	.section	.bss.g_ect_tbl_power_up_flush,"aw",%nobits
	.align	1
	.set	.LANCHOR227,. + 0
	.type	g_ect_tbl_power_up_flush, %object
	.size	g_ect_tbl_power_up_flush, 2
g_ect_tbl_power_up_flush:
	.space	2
	.section	.bss.g_flash_read_only_en,"aw",%nobits
	.align	2
	.set	.LANCHOR78,. + 0
	.type	g_flash_read_only_en, %object
	.size	g_flash_read_only_en, 4
g_flash_read_only_en:
	.space	4
	.section	.bss.g_free_slc_blk_num,"aw",%nobits
	.align	1
	.set	.LANCHOR142,. + 0
	.type	g_free_slc_blk_num, %object
	.size	g_free_slc_blk_num, 2
g_free_slc_blk_num:
	.space	2
	.section	.bss.g_ftl_nand_free_count,"aw",%nobits
	.align	2
	.set	.LANCHOR256,. + 0
	.type	g_ftl_nand_free_count, %object
	.size	g_ftl_nand_free_count, 4
g_ftl_nand_free_count:
	.space	4
	.section	.bss.g_gc_bad_block_gc_index,"aw",%nobits
	.align	1
	.set	.LANCHOR121,. + 0
	.type	g_gc_bad_block_gc_index, %object
	.size	g_gc_bad_block_gc_index, 2
g_gc_bad_block_gc_index:
	.space	2
	.section	.bss.g_gc_bad_block_temp_num,"aw",%nobits
	.align	1
	.set	.LANCHOR119,. + 0
	.type	g_gc_bad_block_temp_num, %object
	.size	g_gc_bad_block_temp_num, 2
g_gc_bad_block_temp_num:
	.space	2
	.section	.bss.g_gc_bad_block_temp_tbl,"aw",%nobits
	.align	1
	.set	.LANCHOR120,. + 0
	.type	g_gc_bad_block_temp_tbl, %object
	.size	g_gc_bad_block_temp_tbl, 34
g_gc_bad_block_temp_tbl:
	.space	34
	.section	.bss.g_gc_blk_index,"aw",%nobits
	.align	1
	.set	.LANCHOR183,. + 0
	.type	g_gc_blk_index, %object
	.size	g_gc_blk_index, 2
g_gc_blk_index:
	.space	2
	.section	.bss.g_gc_blk_num,"aw",%nobits
	.align	1
	.set	.LANCHOR112,. + 0
	.type	g_gc_blk_num, %object
	.size	g_gc_blk_num, 2
g_gc_blk_num:
	.space	2
	.section	.bss.g_gc_cur_blk_max_valid_pages,"aw",%nobits
	.align	1
	.set	.LANCHOR250,. + 0
	.type	g_gc_cur_blk_max_valid_pages, %object
	.size	g_gc_cur_blk_max_valid_pages, 2
g_gc_cur_blk_max_valid_pages:
	.space	2
	.section	.bss.g_gc_cur_blk_valid_pages,"aw",%nobits
	.align	1
	.set	.LANCHOR249,. + 0
	.type	g_gc_cur_blk_valid_pages, %object
	.size	g_gc_cur_blk_valid_pages, 2
g_gc_cur_blk_valid_pages:
	.space	2
	.section	.bss.g_gc_free_blk_threshold,"aw",%nobits
	.align	1
	.set	.LANCHOR181,. + 0
	.type	g_gc_free_blk_threshold, %object
	.size	g_gc_free_blk_threshold, 2
g_gc_free_blk_threshold:
	.space	2
	.section	.bss.g_gc_head_data_block,"aw",%nobits
	.align	2
	.set	.LANCHOR178,. + 0
	.type	g_gc_head_data_block, %object
	.size	g_gc_head_data_block, 4
g_gc_head_data_block:
	.space	4
	.section	.bss.g_gc_head_data_block_count,"aw",%nobits
	.align	2
	.set	.LANCHOR179,. + 0
	.type	g_gc_head_data_block_count, %object
	.size	g_gc_head_data_block_count, 4
g_gc_head_data_block_count:
	.space	4
	.section	.bss.g_gc_merge_free_blk_threshold,"aw",%nobits
	.align	1
	.set	.LANCHOR182,. + 0
	.type	g_gc_merge_free_blk_threshold, %object
	.size	g_gc_merge_free_blk_threshold, 2
g_gc_merge_free_blk_threshold:
	.space	2
	.section	.bss.g_gc_next_blk,"aw",%nobits
	.align	1
	.set	.LANCHOR115,. + 0
	.type	g_gc_next_blk, %object
	.size	g_gc_next_blk, 2
g_gc_next_blk:
	.space	2
	.section	.bss.g_gc_next_blk_1,"aw",%nobits
	.align	1
	.set	.LANCHOR116,. + 0
	.type	g_gc_next_blk_1, %object
	.size	g_gc_next_blk_1, 2
g_gc_next_blk_1:
	.space	2
	.section	.bss.g_gc_next_blk_2,"aw",%nobits
	.align	1
	.set	.LANCHOR117,. + 0
	.type	g_gc_next_blk_2, %object
	.size	g_gc_next_blk_2, 2
g_gc_next_blk_2:
	.space	2
	.section	.bss.g_gc_next_blk_3,"aw",%nobits
	.align	1
	.set	.LANCHOR118,. + 0
	.type	g_gc_next_blk_3, %object
	.size	g_gc_next_blk_3, 2
g_gc_next_blk_3:
	.space	2
	.section	.bss.g_gc_num_req,"aw",%nobits
	.align	2
	.set	.LANCHOR105,. + 0
	.type	g_gc_num_req, %object
	.size	g_gc_num_req, 4
g_gc_num_req:
	.space	4
	.section	.bss.g_gc_page_offset,"aw",%nobits
	.align	1
	.set	.LANCHOR113,. + 0
	.type	g_gc_page_offset, %object
	.size	g_gc_page_offset, 2
g_gc_page_offset:
	.space	2
	.section	.bss.g_gc_refresh_block_temp_num,"aw",%nobits
	.align	1
	.set	.LANCHOR184,. + 0
	.type	g_gc_refresh_block_temp_num, %object
	.size	g_gc_refresh_block_temp_num, 2
g_gc_refresh_block_temp_num:
	.space	2
	.section	.bss.g_gc_refresh_block_temp_tbl,"aw",%nobits
	.align	1
	.type	g_gc_refresh_block_temp_tbl, %object
	.size	g_gc_refresh_block_temp_tbl, 34
g_gc_refresh_block_temp_tbl:
	.space	34
	.section	.bss.g_gc_skip_write_count,"aw",%nobits
	.align	2
	.set	.LANCHOR180,. + 0
	.type	g_gc_skip_write_count, %object
	.size	g_gc_skip_write_count, 4
g_gc_skip_write_count:
	.space	4
	.section	.bss.g_gc_superblock,"aw",%nobits
	.align	2
	.set	.LANCHOR213,. + 0
	.type	g_gc_superblock, %object
	.size	g_gc_superblock, 48
g_gc_superblock:
	.space	48
	.section	.bss.g_gc_temp_superblock,"aw",%nobits
	.align	2
	.set	.LANCHOR95,. + 0
	.type	g_gc_temp_superblock, %object
	.size	g_gc_temp_superblock, 48
g_gc_temp_superblock:
	.space	48
	.section	.bss.g_in_gc_progress,"aw",%nobits
	.align	2
	.set	.LANCHOR176,. + 0
	.type	g_in_gc_progress, %object
	.size	g_in_gc_progress, 4
g_in_gc_progress:
	.space	4
	.section	.bss.g_in_swl_replace,"aw",%nobits
	.align	2
	.set	.LANCHOR177,. + 0
	.type	g_in_swl_replace, %object
	.size	g_in_swl_replace, 4
g_in_swl_replace:
	.space	4
	.section	.bss.g_inkDie_check_enable,"aw",%nobits
	.align	2
	.set	.LANCHOR104,. + 0
	.type	g_inkDie_check_enable, %object
	.size	g_inkDie_check_enable, 4
g_inkDie_check_enable:
	.space	4
	.section	.bss.g_l2p_last_update_region_id,"aw",%nobits
	.align	1
	.set	.LANCHOR99,. + 0
	.type	g_l2p_last_update_region_id, %object
	.size	g_l2p_last_update_region_id, 2
g_l2p_last_update_region_id:
	.space	2
	.section	.bss.g_maxRegNum,"aw",%nobits
	.set	.LANCHOR13,. + 0
	.type	g_maxRegNum, %object
	.size	g_maxRegNum, 1
g_maxRegNum:
	.space	1
	.section	.bss.g_maxRetryCount,"aw",%nobits
	.set	.LANCHOR146,. + 0
	.type	g_maxRetryCount, %object
	.size	g_maxRetryCount, 1
g_maxRetryCount:
	.space	1
	.section	.bss.g_max_erase_count,"aw",%nobits
	.align	2
	.set	.LANCHOR174,. + 0
	.type	g_max_erase_count, %object
	.size	g_max_erase_count, 4
g_max_erase_count:
	.space	4
	.section	.bss.g_min_erase_count,"aw",%nobits
	.align	2
	.set	.LANCHOR175,. + 0
	.type	g_min_erase_count, %object
	.size	g_min_erase_count, 4
g_min_erase_count:
	.space	4
	.section	.bss.g_nand_ecc_en,"aw",%nobits
	.set	.LANCHOR208,. + 0
	.type	g_nand_ecc_en, %object
	.size	g_nand_ecc_en, 1
g_nand_ecc_en:
	.space	1
	.section	.bss.g_nandc_version_data,"aw",%nobits
	.align	2
	.set	.LANCHOR122,. + 0
	.type	g_nandc_version_data, %object
	.size	g_nandc_version_data, 4
g_nandc_version_data:
	.space	4
	.section	.bss.g_num_data_superblocks,"aw",%nobits
	.align	1
	.set	.LANCHOR87,. + 0
	.type	g_num_data_superblocks, %object
	.size	g_num_data_superblocks, 2
g_num_data_superblocks:
	.space	2
	.section	.bss.g_num_free_superblocks,"aw",%nobits
	.align	1
	.set	.LANCHOR90,. + 0
	.type	g_num_free_superblocks, %object
	.size	g_num_free_superblocks, 2
g_num_free_superblocks:
	.space	2
	.section	.bss.g_page_map_check_enable,"aw",%nobits
	.align	1
	.set	.LANCHOR69,. + 0
	.type	g_page_map_check_enable, %object
	.size	g_page_map_check_enable, 2
g_page_map_check_enable:
	.space	2
	.section	.bss.g_power_lost_ecc_error_blk,"aw",%nobits
	.align	1
	.set	.LANCHOR241,. + 0
	.type	g_power_lost_ecc_error_blk, %object
	.size	g_power_lost_ecc_error_blk, 2
g_power_lost_ecc_error_blk:
	.space	2
	.section	.bss.g_power_lost_recovery_flag,"aw",%nobits
	.align	1
	.set	.LANCHOR242,. + 0
	.type	g_power_lost_recovery_flag, %object
	.size	g_power_lost_recovery_flag, 2
g_power_lost_recovery_flag:
	.space	2
	.section	.bss.g_recovery_page_min_ver,"aw",%nobits
	.align	2
	.set	.LANCHOR139,. + 0
	.type	g_recovery_page_min_ver, %object
	.size	g_recovery_page_min_ver, 4
g_recovery_page_min_ver:
	.space	4
	.section	.bss.g_recovery_page_num,"aw",%nobits
	.align	2
	.set	.LANCHOR243,. + 0
	.type	g_recovery_page_num, %object
	.size	g_recovery_page_num, 4
g_recovery_page_num:
	.space	4
	.section	.bss.g_recovery_ppa_tbl,"aw",%nobits
	.align	2
	.set	.LANCHOR244,. + 0
	.type	g_recovery_ppa_tbl, %object
	.size	g_recovery_ppa_tbl, 128
g_recovery_ppa_tbl:
	.space	128
	.section	.bss.g_req_cache,"aw",%nobits
	.align	2
	.set	.LANCHOR135,. + 0
	.type	g_req_cache, %object
	.size	g_req_cache, 4
g_req_cache:
	.space	4
	.section	.bss.g_retryMode,"aw",%nobits
	.set	.LANCHOR10,. + 0
	.type	g_retryMode, %object
	.size	g_retryMode, 1
g_retryMode:
	.space	1
	.section	.bss.g_slc2KBNand,"aw",%nobits
	.set	.LANCHOR2,. + 0
	.type	g_slc2KBNand, %object
	.size	g_slc2KBNand, 1
g_slc2KBNand:
	.space	1
	.section	.bss.g_sys_ext_data,"aw",%nobits
	.align	2
	.set	.LANCHOR141,. + 0
	.type	g_sys_ext_data, %object
	.size	g_sys_ext_data, 512
g_sys_ext_data:
	.space	512
	.section	.bss.g_sys_save_data,"aw",%nobits
	.align	2
	.set	.LANCHOR82,. + 0
	.type	g_sys_save_data, %object
	.size	g_sys_save_data, 48
g_sys_save_data:
	.space	48
	.section	.bss.g_tmp_data_superblock_id,"aw",%nobits
	.align	1
	.set	.LANCHOR136,. + 0
	.type	g_tmp_data_superblock_id, %object
	.size	g_tmp_data_superblock_id, 2
g_tmp_data_superblock_id:
	.space	2
	.section	.bss.g_totle_avg_erase_count,"aw",%nobits
	.align	2
	.set	.LANCHOR214,. + 0
	.type	g_totle_avg_erase_count, %object
	.size	g_totle_avg_erase_count, 4
g_totle_avg_erase_count:
	.space	4
	.section	.bss.g_totle_cache_write_count,"aw",%nobits
	.align	2
	.set	.LANCHOR169,. + 0
	.type	g_totle_cache_write_count, %object
	.size	g_totle_cache_write_count, 4
g_totle_cache_write_count:
	.space	4
	.section	.bss.g_totle_discard_page_count,"aw",%nobits
	.align	2
	.set	.LANCHOR168,. + 0
	.type	g_totle_discard_page_count, %object
	.size	g_totle_discard_page_count, 4
g_totle_discard_page_count:
	.space	4
	.section	.bss.g_totle_gc_page_count,"aw",%nobits
	.align	2
	.set	.LANCHOR166,. + 0
	.type	g_totle_gc_page_count, %object
	.size	g_totle_gc_page_count, 4
g_totle_gc_page_count:
	.space	4
	.section	.bss.g_totle_l2p_write_count,"aw",%nobits
	.align	2
	.set	.LANCHOR170,. + 0
	.type	g_totle_l2p_write_count, %object
	.size	g_totle_l2p_write_count, 4
g_totle_l2p_write_count:
	.space	4
	.section	.bss.g_totle_map_block,"aw",%nobits
	.align	1
	.set	.LANCHOR131,. + 0
	.type	g_totle_map_block, %object
	.size	g_totle_map_block, 2
g_totle_map_block:
	.space	2
	.section	.bss.g_totle_mlc_erase_count,"aw",%nobits
	.align	2
	.set	.LANCHOR172,. + 0
	.type	g_totle_mlc_erase_count, %object
	.size	g_totle_mlc_erase_count, 4
g_totle_mlc_erase_count:
	.space	4
	.section	.bss.g_totle_read_page_count,"aw",%nobits
	.align	2
	.set	.LANCHOR171,. + 0
	.type	g_totle_read_page_count, %object
	.size	g_totle_read_page_count, 4
g_totle_read_page_count:
	.space	4
	.section	.bss.g_totle_read_sector,"aw",%nobits
	.align	2
	.set	.LANCHOR226,. + 0
	.type	g_totle_read_sector, %object
	.size	g_totle_read_sector, 4
g_totle_read_sector:
	.space	4
	.section	.bss.g_totle_slc_erase_count,"aw",%nobits
	.align	2
	.set	.LANCHOR173,. + 0
	.type	g_totle_slc_erase_count, %object
	.size	g_totle_slc_erase_count, 4
g_totle_slc_erase_count:
	.space	4
	.section	.bss.g_totle_swl_count,"aw",%nobits
	.align	2
	.set	.LANCHOR137,. + 0
	.type	g_totle_swl_count, %object
	.size	g_totle_swl_count, 4
g_totle_swl_count:
	.space	4
	.section	.bss.g_totle_sys_slc_erase_count,"aw",%nobits
	.align	2
	.set	.LANCHOR81,. + 0
	.type	g_totle_sys_slc_erase_count, %object
	.size	g_totle_sys_slc_erase_count, 4
g_totle_sys_slc_erase_count:
	.space	4
	.section	.bss.g_totle_vendor_block,"aw",%nobits
	.align	1
	.set	.LANCHOR70,. + 0
	.type	g_totle_vendor_block, %object
	.size	g_totle_vendor_block, 2
g_totle_vendor_block:
	.space	2
	.section	.bss.g_totle_write_page_count,"aw",%nobits
	.align	2
	.set	.LANCHOR167,. + 0
	.type	g_totle_write_page_count, %object
	.size	g_totle_write_page_count, 4
g_totle_write_page_count:
	.space	4
	.section	.bss.g_totle_write_sector,"aw",%nobits
	.align	2
	.set	.LANCHOR225,. + 0
	.type	g_totle_write_sector, %object
	.size	g_totle_write_sector, 4
g_totle_write_sector:
	.space	4
	.section	.bss.g_wr_page_num,"aw",%nobits
	.align	2
	.set	.LANCHOR72,. + 0
	.type	g_wr_page_num, %object
	.size	g_wr_page_num, 4
g_wr_page_num:
	.space	4
	.section	.bss.gc_discard_updated,"aw",%nobits
	.align	2
	.set	.LANCHOR253,. + 0
	.type	gc_discard_updated, %object
	.size	gc_discard_updated, 4
gc_discard_updated:
	.space	4
	.section	.bss.gc_ink_free_return_value,"aw",%nobits
	.align	1
	.set	.LANCHOR248,. + 0
	.type	gc_ink_free_return_value, %object
	.size	gc_ink_free_return_value, 2
gc_ink_free_return_value:
	.space	2
	.section	.bss.gpFlashSaveInfo,"aw",%nobits
	.align	2
	.set	.LANCHOR153,. + 0
	.type	gpFlashSaveInfo, %object
	.size	gpFlashSaveInfo, 4
gpFlashSaveInfo:
	.space	4
	.section	.bss.gpNandParaInfo,"aw",%nobits
	.align	2
	.set	.LANCHOR7,. + 0
	.type	gpNandParaInfo, %object
	.size	gpNandParaInfo, 4
gpNandParaInfo:
	.space	4
	.section	.bss.gpNandc,"aw",%nobits
	.align	2
	.set	.LANCHOR19,. + 0
	.type	gpNandc, %object
	.size	gpNandc, 4
gpNandc:
	.space	4
	.section	.bss.gpNandc1,"aw",%nobits
	.align	2
	.type	gpNandc1, %object
	.size	gpNandc1, 4
gpNandc1:
	.space	4
	.section	.bss.gpReadRetrial,"aw",%nobits
	.align	2
	.set	.LANCHOR145,. + 0
	.type	gpReadRetrial, %object
	.size	gpReadRetrial, 4
gpReadRetrial:
	.space	4
	.section	.bss.gp_ect_tbl_info,"aw",%nobits
	.align	2
	.set	.LANCHOR199,. + 0
	.type	gp_ect_tbl_info, %object
	.size	gp_ect_tbl_info, 4
gp_ect_tbl_info:
	.space	4
	.section	.bss.gp_flash_check_buf,"aw",%nobits
	.align	2
	.type	gp_flash_check_buf, %object
	.size	gp_flash_check_buf, 262144
gp_flash_check_buf:
	.space	262144
	.section	.bss.gp_gc_page_buf_info,"aw",%nobits
	.align	2
	.set	.LANCHOR106,. + 0
	.type	gp_gc_page_buf_info, %object
	.size	gp_gc_page_buf_info, 4
gp_gc_page_buf_info:
	.space	4
	.section	.bss.gp_last_act_superblock,"aw",%nobits
	.align	2
	.set	.LANCHOR252,. + 0
	.type	gp_last_act_superblock, %object
	.size	gp_last_act_superblock, 4
gp_last_act_superblock:
	.space	4
	.section	.bss.idb_buf,"aw",%nobits
	.align	2
	.type	idb_buf, %object
	.size	idb_buf, 262144
idb_buf:
	.space	262144
	.section	.bss.idb_flash_slc_mode,"aw",%nobits
	.align	2
	.set	.LANCHOR29,. + 0
	.type	idb_flash_slc_mode, %object
	.size	idb_flash_slc_mode, 4
idb_flash_slc_mode:
	.space	4
	.section	.bss.idb_need_write_back,"aw",%nobits
	.align	2
	.set	.LANCHOR159,. + 0
	.type	idb_need_write_back, %object
	.size	idb_need_write_back, 4
idb_need_write_back:
	.space	4
	.section	.bss.last_cache_match_count,"aw",%nobits
	.align	2
	.set	.LANCHOR257,. + 0
	.type	last_cache_match_count, %object
	.size	last_cache_match_count, 4
last_cache_match_count:
	.space	4
	.section	.bss.mlcPageToSlcPageTbl,"aw",%nobits
	.align	2
	.set	.LANCHOR123,. + 0
	.type	mlcPageToSlcPageTbl, %object
	.size	mlcPageToSlcPageTbl, 2048
mlcPageToSlcPageTbl:
	.space	2048
	.section	.bss.p_blk_mode_table,"aw",%nobits
	.align	2
	.set	.LANCHOR1,. + 0
	.type	p_blk_mode_table, %object
	.size	p_blk_mode_table, 4
p_blk_mode_table:
	.space	4
	.section	.bss.p_data_block_list_head,"aw",%nobits
	.align	2
	.set	.LANCHOR84,. + 0
	.type	p_data_block_list_head, %object
	.size	p_data_block_list_head, 4
p_data_block_list_head:
	.space	4
	.section	.bss.p_data_block_list_table,"aw",%nobits
	.align	2
	.set	.LANCHOR83,. + 0
	.type	p_data_block_list_table, %object
	.size	p_data_block_list_table, 4
p_data_block_list_table:
	.space	4
	.section	.bss.p_data_block_list_tail,"aw",%nobits
	.align	2
	.set	.LANCHOR86,. + 0
	.type	p_data_block_list_tail, %object
	.size	p_data_block_list_tail, 4
p_data_block_list_tail:
	.space	4
	.section	.bss.p_erase_count_table,"aw",%nobits
	.align	2
	.set	.LANCHOR80,. + 0
	.type	p_erase_count_table, %object
	.size	p_erase_count_table, 4
p_erase_count_table:
	.space	4
	.section	.bss.p_free_data_block_list_head,"aw",%nobits
	.align	2
	.set	.LANCHOR89,. + 0
	.type	p_free_data_block_list_head, %object
	.size	p_free_data_block_list_head, 4
p_free_data_block_list_head:
	.space	4
	.section	.bss.p_gc_blk_tbl,"aw",%nobits
	.align	2
	.set	.LANCHOR111,. + 0
	.type	p_gc_blk_tbl, %object
	.size	p_gc_blk_tbl, 4
p_gc_blk_tbl:
	.space	4
	.section	.bss.p_gc_data_buf,"aw",%nobits
	.align	2
	.set	.LANCHOR107,. + 0
	.type	p_gc_data_buf, %object
	.size	p_gc_data_buf, 4
p_gc_data_buf:
	.space	4
	.section	.bss.p_gc_page_info,"aw",%nobits
	.align	2
	.set	.LANCHOR114,. + 0
	.type	p_gc_page_info, %object
	.size	p_gc_page_info, 4
p_gc_page_info:
	.space	4
	.section	.bss.p_gc_spare_buf,"aw",%nobits
	.align	2
	.set	.LANCHOR108,. + 0
	.type	p_gc_spare_buf, %object
	.size	p_gc_spare_buf, 4
p_gc_spare_buf:
	.space	4
	.section	.bss.p_io_data_buf_0,"aw",%nobits
	.align	2
	.set	.LANCHOR193,. + 0
	.type	p_io_data_buf_0, %object
	.size	p_io_data_buf_0, 4
p_io_data_buf_0:
	.space	4
	.section	.bss.p_io_data_buf_1,"aw",%nobits
	.align	2
	.set	.LANCHOR194,. + 0
	.type	p_io_data_buf_1, %object
	.size	p_io_data_buf_1, 4
p_io_data_buf_1:
	.space	4
	.section	.bss.p_io_spare_buf,"aw",%nobits
	.align	2
	.set	.LANCHOR196,. + 0
	.type	p_io_spare_buf, %object
	.size	p_io_spare_buf, 4
p_io_spare_buf:
	.space	4
	.section	.bss.p_l2p_map_buf,"aw",%nobits
	.align	2
	.set	.LANCHOR129,. + 0
	.type	p_l2p_map_buf, %object
	.size	p_l2p_map_buf, 4
p_l2p_map_buf:
	.space	4
	.section	.bss.p_l2p_ram_map,"aw",%nobits
	.align	2
	.set	.LANCHOR98,. + 0
	.type	p_l2p_ram_map, %object
	.size	p_l2p_ram_map, 4
p_l2p_ram_map:
	.space	4
	.section	.bss.p_map_block_table,"aw",%nobits
	.align	2
	.set	.LANCHOR132,. + 0
	.type	p_map_block_table, %object
	.size	p_map_block_table, 4
p_map_block_table:
	.space	4
	.section	.bss.p_map_block_valid_page_count,"aw",%nobits
	.align	2
	.set	.LANCHOR128,. + 0
	.type	p_map_block_valid_page_count, %object
	.size	p_map_block_valid_page_count, 4
p_map_block_valid_page_count:
	.space	4
	.section	.bss.p_map_block_ver_table,"aw",%nobits
	.align	2
	.set	.LANCHOR133,. + 0
	.type	p_map_block_ver_table, %object
	.size	p_map_block_ver_table, 4
p_map_block_ver_table:
	.space	4
	.section	.bss.p_map_region_ppn_check_table,"aw",%nobits
	.align	2
	.set	.LANCHOR203,. + 0
	.type	p_map_region_ppn_check_table, %object
	.size	p_map_region_ppn_check_table, 4
p_map_region_ppn_check_table:
	.space	4
	.section	.bss.p_map_region_ppn_table,"aw",%nobits
	.align	2
	.set	.LANCHOR134,. + 0
	.type	p_map_region_ppn_table, %object
	.size	p_map_region_ppn_table, 4
p_map_region_ppn_table:
	.space	4
	.section	.bss.p_plane_order_table,"aw",%nobits
	.set	.LANCHOR47,. + 0
	.type	p_plane_order_table, %object
	.size	p_plane_order_table, 32
p_plane_order_table:
	.space	32
	.section	.bss.p_swl_mul_table,"aw",%nobits
	.align	2
	.set	.LANCHOR140,. + 0
	.type	p_swl_mul_table, %object
	.size	p_swl_mul_table, 4
p_swl_mul_table:
	.space	4
	.section	.bss.p_sys_data_buf,"aw",%nobits
	.align	2
	.set	.LANCHOR189,. + 0
	.type	p_sys_data_buf, %object
	.size	p_sys_data_buf, 4
p_sys_data_buf:
	.space	4
	.section	.bss.p_sys_data_buf_1,"aw",%nobits
	.align	2
	.set	.LANCHOR190,. + 0
	.type	p_sys_data_buf_1, %object
	.size	p_sys_data_buf_1, 4
p_sys_data_buf_1:
	.space	4
	.section	.bss.p_sys_spare_buf,"aw",%nobits
	.align	2
	.set	.LANCHOR195,. + 0
	.type	p_sys_spare_buf, %object
	.size	p_sys_spare_buf, 4
p_sys_spare_buf:
	.space	4
	.section	.bss.p_valid_page_count_table,"aw",%nobits
	.align	2
	.set	.LANCHOR85,. + 0
	.type	p_valid_page_count_table, %object
	.size	p_valid_page_count_table, 4
p_valid_page_count_table:
	.space	4
	.section	.bss.p_vendor_block_table,"aw",%nobits
	.align	2
	.set	.LANCHOR71,. + 0
	.type	p_vendor_block_table, %object
	.size	p_vendor_block_table, 4
p_vendor_block_table:
	.space	4
	.section	.bss.p_vendor_block_valid_page_count,"aw",%nobits
	.align	2
	.set	.LANCHOR200,. + 0
	.type	p_vendor_block_valid_page_count, %object
	.size	p_vendor_block_valid_page_count, 4
p_vendor_block_valid_page_count:
	.space	4
	.section	.bss.p_vendor_block_ver_table,"aw",%nobits
	.align	2
	.set	.LANCHOR201,. + 0
	.type	p_vendor_block_ver_table, %object
	.size	p_vendor_block_ver_table, 4
p_vendor_block_ver_table:
	.space	4
	.section	.bss.p_vendor_data_buf,"aw",%nobits
	.align	2
	.set	.LANCHOR191,. + 0
	.type	p_vendor_data_buf, %object
	.size	p_vendor_data_buf, 4
p_vendor_data_buf:
	.space	4
	.section	.bss.p_vendor_region_ppn_table,"aw",%nobits
	.align	2
	.set	.LANCHOR202,. + 0
	.type	p_vendor_region_ppn_table, %object
	.size	p_vendor_region_ppn_table, 4
p_vendor_region_ppn_table:
	.space	4
	.section	.bss.p_wr_io_data_buf,"aw",%nobits
	.align	2
	.set	.LANCHOR192,. + 0
	.type	p_wr_io_data_buf, %object
	.size	p_wr_io_data_buf, 4
p_wr_io_data_buf:
	.space	4
	.section	.bss.p_wr_io_spare_buf,"aw",%nobits
	.align	2
	.set	.LANCHOR197,. + 0
	.type	p_wr_io_spare_buf, %object
	.size	p_wr_io_spare_buf, 4
p_wr_io_spare_buf:
	.space	4
	.section	.bss.read_retry_cur_offset,"aw",%nobits
	.set	.LANCHOR21,. + 0
	.type	read_retry_cur_offset, %object
	.size	read_retry_cur_offset, 4
read_retry_cur_offset:
	.space	4
	.section	.bss.req_erase,"aw",%nobits
	.align	2
	.set	.LANCHOR79,. + 0
	.type	req_erase, %object
	.size	req_erase, 4
req_erase:
	.space	4
	.section	.bss.req_gc,"aw",%nobits
	.align	2
	.set	.LANCHOR109,. + 0
	.type	req_gc, %object
	.size	req_gc, 4
req_gc:
	.space	4
	.section	.bss.req_gc_dst,"aw",%nobits
	.align	2
	.set	.LANCHOR187,. + 0
	.type	req_gc_dst, %object
	.size	req_gc_dst, 4
req_gc_dst:
	.space	4
	.section	.bss.req_prgm,"aw",%nobits
	.align	2
	.set	.LANCHOR188,. + 0
	.type	req_prgm, %object
	.size	req_prgm, 4
req_prgm:
	.space	4
	.section	.bss.req_read,"aw",%nobits
	.align	2
	.set	.LANCHOR186,. + 0
	.type	req_read, %object
	.size	req_read, 4
req_read:
	.space	4
	.section	.bss.req_sys,"aw",%nobits
	.align	2
	.set	.LANCHOR211,. + 0
	.type	req_sys, %object
	.size	req_sys, 36
req_sys:
	.space	36
	.section	.bss.req_wr_io,"aw",%nobits
	.align	2
	.set	.LANCHOR73,. + 0
	.type	req_wr_io, %object
	.size	req_wr_io, 4
req_wr_io:
	.space	4
	.section	.bss.slcPageToMlcPageTbl,"aw",%nobits
	.align	2
	.set	.LANCHOR17,. + 0
	.type	slcPageToMlcPageTbl, %object
	.size	slcPageToMlcPageTbl, 1024
slcPageToMlcPageTbl:
	.space	1024
	.section	.data.FtlMallocOffset,"aw",%progbits
	.align	2
	.type	FtlMallocOffset, %object
	.size	FtlMallocOffset, 4
FtlMallocOffset:
	.word	64
	.section	.data.LastWritenPbaAddr,"aw",%progbits
	.align	2
	.type	LastWritenPbaAddr, %object
	.size	LastWritenPbaAddr, 4
LastWritenPbaAddr:
	.word	-1
	.section	.data.NandFlashParaTbl,"aw",%progbits
	.align	1
	.set	.LANCHOR151,. + 0
	.type	NandFlashParaTbl, %object
	.size	NandFlashParaTbl, 2752
NandFlashParaTbl:
	.byte	6
	.byte	44
	.byte	100
	.byte	68
	.byte	75
	.byte	-87
	.byte	0
	.byte	4
	.byte	1
	.byte	16
	.short	256
	.byte	2
	.byte	2
	.short	2048
	.short	479
	.byte	3
	.byte	17
	.byte	40
	.byte	32
	.byte	1
	.byte	0
	.byte	1
	.byte	0
	.byte	0
	.byte	0
	.space	4
	.byte	6
	.byte	44
	.byte	68
	.byte	68
	.byte	75
	.byte	-87
	.byte	0
	.byte	4
	.byte	1
	.byte	16
	.short	256
	.byte	2
	.byte	2
	.short	1064
	.short	479
	.byte	3
	.byte	17
	.byte	40
	.byte	32
	.byte	1
	.byte	0
	.byte	1
	.byte	0
	.byte	0
	.byte	0
	.space	4
	.byte	6
	.byte	44
	.byte	104
	.byte	4
	.byte	74
	.byte	-87
	.byte	0
	.byte	4
	.byte	1
	.byte	8
	.short	256
	.byte	2
	.byte	2
	.short	2048
	.short	287
	.byte	1
	.byte	0
	.byte	24
	.byte	32
	.byte	1
	.byte	0
	.byte	1
	.byte	0
	.byte	0
	.byte	0
	.space	4
	.byte	5
	.byte	44
	.byte	-120
	.byte	4
	.byte	75
	.byte	-87
	.byte	0
	.byte	4
	.byte	1
	.byte	16
	.short	256
	.byte	2
	.byte	2
	.short	2048
	.short	287
	.byte	1
	.byte	0
	.byte	24
	.byte	32
	.byte	1
	.byte	0
	.byte	1
	.byte	0
	.byte	0
	.byte	0
	.space	4
	.byte	6
	.byte	44
	.byte	-88
	.byte	5
	.byte	-53
	.byte	-87
	.byte	0
	.byte	4
	.byte	2
	.byte	16
	.short	256
	.byte	2
	.byte	2
	.short	2048
	.short	287
	.byte	1
	.byte	0
	.byte	24
	.byte	32
	.byte	1
	.byte	0
	.byte	1
	.byte	0
	.byte	0
	.byte	0
	.space	4
	.byte	6
	.byte	44
	.byte	104
	.byte	4
	.byte	70
	.byte	-119
	.byte	0
	.byte	4
	.byte	1
	.byte	8
	.short	256
	.byte	2
	.byte	2
	.short	2048
	.short	287
	.byte	1
	.byte	0
	.byte	24
	.byte	32
	.byte	1
	.byte	0
	.byte	1
	.byte	0
	.byte	0
	.byte	0
	.space	4
	.byte	6
	.byte	44
	.byte	72
	.byte	4
	.byte	74
	.byte	-91
	.byte	0
	.byte	4
	.byte	1
	.byte	8
	.short	256
	.byte	2
	.byte	2
	.short	1024
	.short	287
	.byte	1
	.byte	0
	.byte	24
	.byte	32
	.byte	1
	.byte	0
	.byte	1
	.byte	0
	.byte	0
	.byte	0
	.space	4
	.byte	6
	.byte	44
	.byte	-124
	.byte	100
	.byte	60
	.byte	-91
	.byte	0
	.byte	4
	.byte	1
	.byte	32
	.short	512
	.byte	2
	.byte	2
	.short	1024
	.short	479
	.byte	3
	.byte	17
	.byte	40
	.byte	32
	.byte	1
	.byte	0
	.byte	1
	.byte	0
	.byte	0
	.byte	0
	.space	4
	.byte	5
	.byte	44
	.byte	-124
	.byte	100
	.byte	84
	.byte	-87
	.byte	0
	.byte	4
	.byte	1
	.byte	32
	.short	512
	.byte	2
	.byte	2
	.short	1024
	.short	479
	.byte	4
	.byte	18
	.byte	60
	.byte	32
	.byte	1
	.byte	0
	.byte	1
	.byte	0
	.byte	0
	.byte	0
	.space	4
	.byte	6
	.byte	44
	.byte	-41
	.byte	-108
	.byte	62
	.byte	-124
	.byte	0
	.byte	4
	.byte	1
	.byte	8
	.short	128
	.byte	2
	.byte	2
	.short	4096
	.short	279
	.byte	1
	.byte	0
	.byte	24
	.byte	32
	.byte	1
	.byte	0
	.byte	1
	.byte	0
	.byte	0
	.byte	0
	.space	4
	.byte	6
	.byte	44
	.byte	72
	.byte	4
	.byte	70
	.byte	-123
	.byte	0
	.byte	4
	.byte	1
	.byte	8
	.short	256
	.byte	2
	.byte	2
	.short	1024
	.short	287
	.byte	1
	.byte	0
	.byte	24
	.byte	32
	.byte	1
	.byte	0
	.byte	1
	.byte	0
	.byte	0
	.byte	0
	.space	4
	.byte	6
	.byte	44
	.byte	-120
	.byte	5
	.byte	-58
	.byte	-119
	.byte	0
	.byte	4
	.byte	2
	.byte	8
	.short	256
	.byte	2
	.byte	2
	.short	2048
	.short	287
	.byte	1
	.byte	0
	.byte	24
	.byte	32
	.byte	1
	.byte	0
	.byte	1
	.byte	0
	.byte	0
	.byte	0
	.space	4
	.byte	5
	.byte	44
	.byte	-120
	.byte	36
	.byte	75
	.byte	-87
	.byte	0
	.byte	4
	.byte	1
	.byte	16
	.short	256
	.byte	2
	.byte	2
	.short	2048
	.short	287
	.byte	1
	.byte	0
	.byte	24
	.byte	32
	.byte	1
	.byte	0
	.byte	1
	.byte	0
	.byte	0
	.byte	0
	.space	4
	.byte	6
	.byte	44
	.byte	104
	.byte	0
	.byte	39
	.byte	-87
	.byte	0
	.byte	4
	.byte	1
	.byte	16
	.short	128
	.byte	1
	.byte	2
	.short	2048
	.short	287
	.byte	0
	.byte	0
	.byte	24
	.byte	32
	.byte	1
	.byte	0
	.byte	1
	.byte	0
	.byte	0
	.byte	0
	.space	4
	.byte	5
	.byte	44
	.byte	100
	.byte	100
	.byte	86
	.byte	-91
	.byte	0
	.byte	4
	.byte	1
	.byte	24
	.short	512
	.byte	2
	.byte	2
	.short	700
	.short	479
	.byte	4
	.byte	18
	.byte	60
	.byte	32
	.byte	1
	.byte	0
	.byte	1
	.byte	0
	.byte	0
	.byte	0
	.space	4
	.byte	6
	.byte	44
	.byte	-124
	.byte	-59
	.byte	75
	.byte	-87
	.byte	0
	.byte	4
	.byte	2
	.byte	16
	.short	256
	.byte	2
	.byte	2
	.short	2048
	.short	479
	.byte	3
	.byte	17
	.byte	40
	.byte	32
	.byte	1
	.byte	0
	.byte	1
	.byte	0
	.byte	0
	.byte	0
	.space	4
	.byte	6
	.byte	44
	.byte	-43
	.byte	-47
	.byte	-90
	.byte	104
	.byte	0
	.byte	4
	.byte	2
	.byte	8
	.short	64
	.byte	1
	.byte	2
	.short	2048
	.short	279
	.byte	0
	.byte	0
	.byte	24
	.byte	32
	.byte	1
	.byte	0
	.byte	1
	.byte	0
	.byte	0
	.byte	0
	.space	4
	.byte	6
	.byte	44
	.byte	-36
	.byte	-112
	.byte	-90
	.byte	84
	.byte	0
	.byte	4
	.byte	1
	.byte	8
	.short	64
	.byte	1
	.byte	2
	.short	1024
	.short	279
	.byte	0
	.byte	0
	.byte	24
	.byte	32
	.byte	1
	.byte	0
	.byte	1
	.byte	0
	.byte	0
	.byte	0
	.space	4
	.byte	5
	.byte	44
	.byte	100
	.byte	100
	.byte	84
	.byte	-92
	.byte	0
	.byte	4
	.byte	1
	.byte	32
	.short	512
	.byte	2
	.byte	1
	.short	1024
	.short	479
	.byte	4
	.byte	18
	.byte	60
	.byte	32
	.byte	1
	.byte	0
	.byte	1
	.byte	0
	.byte	0
	.byte	0
	.space	4
	.byte	5
	.byte	44
	.byte	-124
	.byte	68
	.byte	50
	.byte	-86
	.byte	0
	.byte	4
	.byte	1
	.byte	32
	.short	512
	.byte	2
	.byte	1
	.short	2184
	.short	1479
	.byte	5
	.byte	19
	.byte	60
	.byte	32
	.byte	1
	.byte	0
	.byte	1
	.byte	0
	.byte	1
	.byte	0
	.space	4
	.byte	5
	.byte	44
	.byte	100
	.byte	68
	.byte	50
	.byte	-91
	.byte	0
	.byte	4
	.byte	1
	.byte	32
	.short	512
	.byte	2
	.byte	1
	.short	1048
	.short	1479
	.byte	5
	.byte	19
	.byte	60
	.byte	32
	.byte	1
	.byte	0
	.byte	1
	.byte	0
	.byte	1
	.byte	0
	.space	4
	.byte	5
	.byte	44
	.byte	100
	.byte	100
	.byte	60
	.byte	-91
	.byte	0
	.byte	4
	.byte	1
	.byte	32
	.short	512
	.byte	2
	.byte	1
	.short	1044
	.short	479
	.byte	3
	.byte	17
	.byte	40
	.byte	32
	.byte	1
	.byte	0
	.byte	1
	.byte	0
	.byte	0
	.byte	0
	.space	4
	.byte	5
	.byte	44
	.byte	-124
	.byte	68
	.byte	50
	.byte	-86
	.byte	0
	.byte	4
	.byte	1
	.byte	32
	.short	512
	.byte	2
	.byte	1
	.short	2184
	.short	1479
	.byte	5
	.byte	19
	.byte	60
	.byte	32
	.byte	1
	.byte	0
	.byte	4
	.byte	0
	.byte	1
	.byte	0
	.space	4
	.byte	5
	.byte	44
	.byte	-124
	.byte	68
	.byte	52
	.byte	-86
	.byte	0
	.byte	4
	.byte	1
	.byte	32
	.short	512
	.byte	2
	.byte	1
	.short	2184
	.short	1479
	.byte	5
	.byte	19
	.byte	60
	.byte	32
	.byte	1
	.byte	0
	.byte	4
	.byte	0
	.byte	1
	.byte	0
	.space	4
	.byte	5
	.byte	44
	.byte	-124
	.byte	-60
	.byte	52
	.byte	-86
	.byte	0
	.byte	4
	.byte	1
	.byte	32
	.short	512
	.byte	2
	.byte	1
	.short	2184
	.short	1479
	.byte	5
	.byte	19
	.byte	60
	.byte	32
	.byte	1
	.byte	0
	.byte	1
	.byte	0
	.byte	1
	.byte	0
	.space	4
	.byte	5
	.byte	44
	.byte	-124
	.byte	68
	.byte	52
	.byte	-92
	.byte	0
	.byte	4
	.byte	1
	.byte	32
	.short	512
	.byte	2
	.byte	1
	.short	2184
	.short	1479
	.byte	5
	.byte	19
	.byte	60
	.byte	32
	.byte	1
	.byte	0
	.byte	1
	.byte	0
	.byte	1
	.byte	0
	.space	4
	.byte	5
	.byte	44
	.byte	-124
	.byte	100
	.byte	60
	.byte	-87
	.byte	0
	.byte	4
	.byte	1
	.byte	32
	.short	512
	.byte	2
	.byte	2
	.short	1024
	.short	479
	.byte	3
	.byte	17
	.byte	40
	.byte	32
	.byte	1
	.byte	0
	.byte	1
	.byte	0
	.byte	0
	.byte	0
	.space	4
	.byte	6
	.byte	44
	.byte	-92
	.byte	100
	.byte	50
	.byte	-86
	.byte	4
	.byte	4
	.byte	1
	.byte	32
	.short	1024
	.byte	2
	.byte	1
	.short	2192
	.short	1479
	.byte	10
	.byte	19
	.byte	60
	.byte	32
	.byte	1
	.byte	0
	.byte	4
	.byte	0
	.byte	1
	.byte	0
	.space	4
	.byte	6
	.byte	-83
	.byte	-34
	.byte	-108
	.byte	-46
	.byte	4
	.byte	67
	.byte	2
	.byte	1
	.byte	16
	.short	256
	.byte	2
	.byte	2
	.short	2048
	.short	473
	.byte	1
	.byte	1
	.byte	24
	.byte	32
	.byte	4
	.byte	0
	.byte	3
	.byte	0
	.byte	0
	.byte	0
	.space	4
	.byte	6
	.byte	-83
	.byte	-41
	.byte	-108
	.byte	-38
	.byte	116
	.byte	-61
	.byte	2
	.byte	1
	.byte	16
	.short	256
	.byte	2
	.byte	2
	.short	1024
	.short	473
	.byte	1
	.byte	2
	.byte	40
	.byte	32
	.byte	4
	.byte	0
	.byte	3
	.byte	0
	.byte	0
	.byte	0
	.space	4
	.byte	6
	.byte	-83
	.byte	-41
	.byte	-108
	.byte	-111
	.byte	96
	.byte	68
	.byte	2
	.byte	1
	.byte	16
	.short	256
	.byte	2
	.byte	2
	.short	1046
	.short	473
	.byte	1
	.byte	3
	.byte	40
	.byte	32
	.byte	4
	.byte	1
	.byte	3
	.byte	0
	.byte	0
	.byte	0
	.space	4
	.byte	6
	.byte	-83
	.byte	-34
	.byte	-108
	.byte	-38
	.byte	116
	.byte	-60
	.byte	2
	.byte	1
	.byte	16
	.short	256
	.byte	2
	.byte	2
	.short	2090
	.short	473
	.byte	1
	.byte	4
	.byte	40
	.byte	32
	.byte	4
	.byte	1
	.byte	3
	.byte	0
	.byte	0
	.byte	0
	.space	4
	.byte	6
	.byte	-83
	.byte	-34
	.byte	-108
	.byte	-21
	.byte	116
	.byte	68
	.byte	2
	.byte	1
	.byte	32
	.short	256
	.byte	2
	.byte	2
	.short	1066
	.short	473
	.byte	1
	.byte	7
	.byte	40
	.byte	32
	.byte	4
	.byte	1
	.byte	3
	.byte	0
	.byte	0
	.byte	0
	.space	4
	.byte	6
	.byte	-83
	.byte	-43
	.byte	-108
	.byte	-38
	.byte	116
	.byte	-60
	.byte	2
	.byte	1
	.byte	16
	.short	256
	.byte	2
	.byte	2
	.short	530
	.short	473
	.byte	1
	.byte	3
	.byte	40
	.byte	32
	.byte	4
	.byte	1
	.byte	3
	.byte	0
	.byte	0
	.byte	0
	.space	4
	.byte	6
	.byte	-83
	.byte	-41
	.byte	-108
	.byte	-102
	.byte	116
	.byte	66
	.byte	2
	.byte	1
	.byte	16
	.short	256
	.byte	2
	.byte	2
	.short	1024
	.short	281
	.byte	1
	.byte	0
	.byte	24
	.byte	32
	.byte	4
	.byte	0
	.byte	3
	.byte	0
	.byte	0
	.byte	0
	.space	4
	.byte	6
	.byte	-83
	.byte	-34
	.byte	20
	.byte	-89
	.byte	66
	.byte	74
	.byte	2
	.byte	1
	.byte	32
	.short	256
	.byte	2
	.byte	2
	.short	1060
	.short	473
	.byte	2
	.byte	5
	.byte	40
	.byte	32
	.byte	4
	.byte	1
	.byte	3
	.byte	0
	.byte	0
	.byte	0
	.space	4
	.byte	6
	.byte	-83
	.byte	-41
	.byte	20
	.byte	-98
	.byte	52
	.byte	74
	.byte	2
	.byte	1
	.byte	16
	.short	256
	.byte	2
	.byte	2
	.short	1056
	.short	473
	.byte	2
	.byte	5
	.byte	40
	.byte	32
	.byte	4
	.byte	1
	.byte	3
	.byte	0
	.byte	0
	.byte	0
	.space	4
	.byte	6
	.byte	-83
	.byte	-34
	.byte	-108
	.byte	-89
	.byte	66
	.byte	72
	.byte	2
	.byte	1
	.byte	32
	.short	256
	.byte	2
	.byte	2
	.short	1060
	.short	473
	.byte	2
	.byte	5
	.byte	40
	.byte	32
	.byte	4
	.byte	1
	.byte	3
	.byte	0
	.byte	0
	.byte	0
	.space	4
	.byte	6
	.byte	-83
	.byte	-34
	.byte	20
	.byte	-85
	.byte	66
	.byte	74
	.byte	2
	.byte	1
	.byte	32
	.short	256
	.byte	2
	.byte	2
	.short	1056
	.short	473
	.byte	2
	.byte	6
	.byte	40
	.byte	32
	.byte	3
	.byte	1
	.byte	3
	.byte	0
	.byte	0
	.byte	0
	.space	4
	.byte	6
	.byte	-83
	.byte	58
	.byte	20
	.byte	-85
	.byte	66
	.byte	74
	.byte	2
	.byte	1
	.byte	32
	.short	256
	.byte	2
	.byte	2
	.short	2092
	.short	473
	.byte	2
	.byte	5
	.byte	40
	.byte	32
	.byte	3
	.byte	1
	.byte	3
	.byte	0
	.byte	0
	.byte	0
	.space	4
	.byte	6
	.byte	-83
	.byte	-43
	.byte	-108
	.byte	-102
	.byte	116
	.byte	66
	.byte	2
	.byte	1
	.byte	16
	.short	256
	.byte	2
	.byte	1
	.short	1024
	.short	273
	.byte	1
	.byte	0
	.byte	24
	.byte	32
	.byte	4
	.byte	1
	.byte	3
	.byte	0
	.byte	0
	.byte	0
	.space	4
	.byte	6
	.byte	-83
	.byte	58
	.byte	20
	.byte	3
	.byte	8
	.byte	80
	.byte	2
	.byte	1
	.byte	32
	.short	388
	.byte	2
	.byte	2
	.short	1362
	.short	473
	.byte	9
	.byte	8
	.byte	40
	.byte	32
	.byte	3
	.byte	1
	.byte	3
	.byte	0
	.byte	0
	.byte	0
	.space	4
	.byte	6
	.byte	-119
	.byte	100
	.byte	68
	.byte	75
	.byte	-87
	.byte	0
	.byte	7
	.byte	1
	.byte	16
	.short	256
	.byte	2
	.byte	2
	.short	2048
	.short	479
	.byte	3
	.byte	17
	.byte	40
	.byte	32
	.byte	1
	.byte	0
	.byte	1
	.byte	0
	.byte	0
	.byte	0
	.space	4
	.byte	6
	.byte	-119
	.byte	-120
	.byte	36
	.byte	75
	.byte	-87
	.byte	-124
	.byte	7
	.byte	1
	.byte	16
	.short	256
	.byte	2
	.byte	2
	.short	2048
	.short	479
	.byte	3
	.byte	17
	.byte	40
	.byte	32
	.byte	1
	.byte	0
	.byte	1
	.byte	0
	.byte	0
	.byte	0
	.space	4
	.byte	6
	.byte	-119
	.byte	-120
	.byte	36
	.byte	75
	.byte	-87
	.byte	0
	.byte	7
	.byte	1
	.byte	16
	.short	256
	.byte	2
	.byte	2
	.short	2048
	.short	279
	.byte	1
	.byte	0
	.byte	24
	.byte	32
	.byte	1
	.byte	0
	.byte	1
	.byte	0
	.byte	0
	.byte	0
	.space	4
	.byte	6
	.byte	-119
	.byte	104
	.byte	36
	.byte	74
	.byte	-87
	.byte	0
	.byte	7
	.byte	1
	.byte	8
	.short	256
	.byte	2
	.byte	2
	.short	2048
	.short	279
	.byte	1
	.byte	0
	.byte	24
	.byte	32
	.byte	1
	.byte	0
	.byte	1
	.byte	0
	.byte	0
	.byte	0
	.space	4
	.byte	6
	.byte	-119
	.byte	104
	.byte	4
	.byte	74
	.byte	-87
	.byte	0
	.byte	7
	.byte	1
	.byte	8
	.short	256
	.byte	2
	.byte	2
	.short	2048
	.short	279
	.byte	1
	.byte	0
	.byte	24
	.byte	32
	.byte	1
	.byte	0
	.byte	1
	.byte	0
	.byte	0
	.byte	0
	.space	4
	.byte	6
	.byte	-119
	.byte	-41
	.byte	-108
	.byte	62
	.byte	-124
	.byte	0
	.byte	7
	.byte	1
	.byte	8
	.short	256
	.byte	2
	.byte	2
	.short	2048
	.short	279
	.byte	1
	.byte	0
	.byte	24
	.byte	32
	.byte	1
	.byte	0
	.byte	1
	.byte	0
	.byte	0
	.byte	0
	.space	4
	.byte	6
	.byte	-119
	.byte	104
	.byte	4
	.byte	70
	.byte	-87
	.byte	0
	.byte	7
	.byte	1
	.byte	8
	.short	256
	.byte	2
	.byte	2
	.short	2048
	.short	279
	.byte	1
	.byte	0
	.byte	24
	.byte	32
	.byte	1
	.byte	0
	.byte	1
	.byte	0
	.byte	0
	.byte	0
	.space	4
	.byte	5
	.byte	-119
	.byte	100
	.byte	100
	.byte	60
	.byte	-95
	.byte	0
	.byte	7
	.byte	1
	.byte	32
	.short	512
	.byte	2
	.byte	1
	.short	1024
	.short	455
	.byte	4
	.byte	17
	.byte	40
	.byte	32
	.byte	1
	.byte	0
	.byte	1
	.byte	0
	.byte	0
	.byte	0
	.space	4
	.byte	5
	.byte	-119
	.byte	-124
	.byte	100
	.byte	60
	.byte	-91
	.byte	0
	.byte	7
	.byte	1
	.byte	32
	.short	512
	.byte	2
	.byte	2
	.short	1024
	.short	455
	.byte	4
	.byte	17
	.byte	40
	.byte	32
	.byte	1
	.byte	0
	.byte	1
	.byte	0
	.byte	0
	.byte	0
	.space	4
	.byte	6
	.byte	-119
	.byte	-120
	.byte	36
	.byte	59
	.byte	-87
	.byte	0
	.byte	7
	.byte	1
	.byte	16
	.short	192
	.byte	2
	.byte	2
	.short	2048
	.short	279
	.byte	12
	.byte	0
	.byte	24
	.byte	32
	.byte	1
	.byte	0
	.byte	1
	.byte	0
	.byte	0
	.byte	0
	.space	4
	.byte	6
	.byte	-104
	.byte	-41
	.byte	-124
	.byte	-109
	.byte	114
	.byte	87
	.byte	1
	.byte	1
	.byte	32
	.short	256
	.byte	2
	.byte	1
	.short	1060
	.short	1473
	.byte	2
	.byte	33
	.byte	40
	.byte	32
	.byte	2
	.byte	1
	.byte	1
	.byte	0
	.byte	0
	.byte	0
	.space	4
	.byte	6
	.byte	-104
	.byte	-34
	.byte	-124
	.byte	-109
	.byte	114
	.byte	87
	.byte	1
	.byte	1
	.byte	32
	.short	256
	.byte	2
	.byte	1
	.short	2092
	.short	1473
	.byte	2
	.byte	33
	.byte	40
	.byte	32
	.byte	2
	.byte	1
	.byte	1
	.byte	0
	.byte	0
	.byte	0
	.space	4
	.byte	6
	.byte	-104
	.byte	58
	.byte	-123
	.byte	-109
	.byte	118
	.byte	87
	.byte	1
	.byte	2
	.byte	32
	.short	256
	.byte	2
	.byte	1
	.short	2092
	.short	1505
	.byte	2
	.byte	33
	.byte	40
	.byte	32
	.byte	2
	.byte	1
	.byte	1
	.byte	0
	.byte	0
	.byte	0
	.space	4
	.byte	6
	.byte	-104
	.byte	-43
	.byte	-124
	.byte	50
	.byte	114
	.byte	86
	.byte	1
	.byte	1
	.byte	16
	.short	128
	.byte	2
	.byte	1
	.short	2056
	.short	1473
	.byte	2
	.byte	33
	.byte	40
	.byte	32
	.byte	2
	.byte	1
	.byte	1
	.byte	0
	.byte	0
	.byte	0
	.space	4
	.byte	6
	.byte	-104
	.byte	-41
	.byte	-108
	.byte	50
	.byte	118
	.byte	86
	.byte	1
	.byte	1
	.byte	16
	.short	128
	.byte	2
	.byte	2
	.short	2058
	.short	1489
	.byte	2
	.byte	33
	.byte	40
	.byte	32
	.byte	2
	.byte	1
	.byte	1
	.byte	0
	.byte	0
	.byte	0
	.space	4
	.byte	6
	.byte	-104
	.byte	-34
	.byte	-108
	.byte	-126
	.byte	118
	.byte	86
	.byte	1
	.byte	1
	.byte	16
	.short	256
	.byte	2
	.byte	2
	.short	2062
	.short	1489
	.byte	1
	.byte	33
	.byte	40
	.byte	32
	.byte	2
	.byte	1
	.byte	1
	.byte	0
	.byte	0
	.byte	0
	.space	4
	.byte	6
	.byte	-104
	.byte	-34
	.byte	-108
	.byte	-109
	.byte	118
	.byte	80
	.byte	1
	.byte	1
	.byte	32
	.short	256
	.byte	2
	.byte	2
	.short	1066
	.short	1497
	.byte	2
	.byte	34
	.byte	40
	.byte	32
	.byte	3
	.byte	1
	.byte	1
	.byte	0
	.byte	0
	.byte	0
	.space	4
	.byte	6
	.byte	-104
	.byte	58
	.byte	-107
	.byte	-109
	.byte	122
	.byte	80
	.byte	1
	.byte	2
	.byte	32
	.short	256
	.byte	2
	.byte	2
	.short	1066
	.short	1497
	.byte	2
	.byte	34
	.byte	40
	.byte	32
	.byte	3
	.byte	1
	.byte	1
	.byte	0
	.byte	0
	.byte	0
	.space	4
	.byte	6
	.byte	-104
	.byte	-41
	.byte	-108
	.byte	50
	.byte	118
	.byte	85
	.byte	1
	.byte	1
	.byte	16
	.short	128
	.byte	2
	.byte	2
	.short	2050
	.short	401
	.byte	2
	.byte	0
	.byte	24
	.byte	32
	.byte	1
	.byte	1
	.byte	1
	.byte	0
	.byte	0
	.byte	0
	.space	4
	.byte	6
	.byte	-104
	.byte	-34
	.byte	-108
	.byte	-109
	.byte	118
	.byte	87
	.byte	1
	.byte	1
	.byte	32
	.short	256
	.byte	2
	.byte	2
	.short	1058
	.short	1497
	.byte	2
	.byte	33
	.byte	40
	.byte	32
	.byte	3
	.byte	1
	.byte	1
	.byte	0
	.byte	0
	.byte	0
	.space	4
	.byte	6
	.byte	-104
	.byte	-41
	.byte	-124
	.byte	-109
	.byte	114
	.byte	80
	.byte	1
	.byte	1
	.byte	32
	.short	256
	.byte	2
	.byte	1
	.short	1060
	.short	1473
	.byte	2
	.byte	34
	.byte	40
	.byte	32
	.byte	3
	.byte	1
	.byte	1
	.byte	0
	.byte	0
	.byte	0
	.space	4
	.byte	6
	.byte	-104
	.byte	-34
	.byte	-108
	.byte	-109
	.byte	118
	.byte	81
	.byte	1
	.byte	1
	.byte	32
	.short	256
	.byte	2
	.byte	2
	.short	1074
	.short	1497
	.byte	2
	.byte	35
	.byte	40
	.byte	32
	.byte	3
	.byte	1
	.byte	4
	.byte	0
	.byte	0
	.byte	0
	.space	4
	.byte	6
	.byte	-104
	.byte	58
	.byte	-108
	.byte	-109
	.byte	118
	.byte	81
	.byte	1
	.byte	1
	.byte	32
	.short	256
	.byte	2
	.byte	2
	.short	2106
	.short	1497
	.byte	2
	.byte	35
	.byte	40
	.byte	32
	.byte	3
	.byte	1
	.byte	4
	.byte	0
	.byte	0
	.byte	0
	.space	4
	.byte	6
	.byte	-104
	.byte	-41
	.byte	-124
	.byte	-109
	.byte	114
	.byte	81
	.byte	1
	.byte	1
	.byte	32
	.short	256
	.byte	2
	.byte	1
	.short	1056
	.short	1497
	.byte	2
	.byte	35
	.byte	40
	.byte	32
	.byte	3
	.byte	1
	.byte	4
	.byte	0
	.byte	0
	.byte	0
	.space	4
	.byte	6
	.byte	-104
	.byte	-34
	.byte	-108
	.byte	-109
	.byte	118
	.byte	-47
	.byte	1
	.byte	1
	.byte	32
	.short	256
	.byte	2
	.byte	2
	.short	1074
	.short	1497
	.byte	2
	.byte	35
	.byte	40
	.byte	32
	.byte	3
	.byte	1
	.byte	4
	.byte	0
	.byte	0
	.byte	0
	.space	4
	.byte	6
	.byte	69
	.byte	-34
	.byte	-108
	.byte	-109
	.byte	118
	.byte	87
	.byte	8
	.byte	1
	.byte	32
	.short	256
	.byte	2
	.byte	2
	.short	1058
	.short	1497
	.byte	2
	.byte	66
	.byte	40
	.byte	32
	.byte	3
	.byte	1
	.byte	1
	.byte	0
	.byte	0
	.byte	0
	.space	4
	.byte	6
	.byte	69
	.byte	-41
	.byte	-124
	.byte	-109
	.byte	114
	.byte	87
	.byte	8
	.byte	1
	.byte	32
	.short	256
	.byte	2
	.byte	1
	.short	1060
	.short	1473
	.byte	2
	.byte	66
	.byte	40
	.byte	32
	.byte	2
	.byte	1
	.byte	1
	.byte	0
	.byte	0
	.byte	0
	.space	4
	.byte	6
	.byte	69
	.byte	-34
	.byte	-92
	.byte	-126
	.byte	118
	.byte	86
	.byte	8
	.byte	1
	.byte	16
	.short	256
	.byte	2
	.byte	2
	.short	2082
	.short	473
	.byte	1
	.byte	65
	.byte	40
	.byte	32
	.byte	3
	.byte	1
	.byte	1
	.byte	0
	.byte	0
	.byte	0
	.space	4
	.byte	6
	.byte	69
	.byte	-34
	.byte	-108
	.byte	-109
	.byte	118
	.byte	80
	.byte	8
	.byte	1
	.byte	32
	.short	256
	.byte	2
	.byte	2
	.short	1066
	.short	1497
	.byte	2
	.byte	67
	.byte	40
	.byte	32
	.byte	3
	.byte	1
	.byte	1
	.byte	0
	.byte	0
	.byte	0
	.space	4
	.byte	6
	.byte	69
	.byte	-41
	.byte	-124
	.byte	-109
	.byte	114
	.byte	80
	.byte	8
	.byte	1
	.byte	32
	.short	256
	.byte	2
	.byte	1
	.short	1060
	.short	1473
	.byte	2
	.byte	67
	.byte	40
	.byte	32
	.byte	3
	.byte	1
	.byte	1
	.byte	0
	.byte	0
	.byte	0
	.space	4
	.byte	6
	.byte	69
	.byte	-34
	.byte	-92
	.byte	-126
	.byte	118
	.byte	-41
	.byte	8
	.byte	1
	.byte	16
	.short	256
	.byte	2
	.byte	2
	.short	2090
	.short	1241
	.byte	1
	.byte	66
	.byte	40
	.byte	32
	.byte	3
	.byte	1
	.byte	1
	.byte	0
	.byte	0
	.byte	0
	.space	4
	.byte	6
	.byte	69
	.byte	-34
	.byte	-124
	.byte	-109
	.byte	114
	.byte	87
	.byte	8
	.byte	1
	.byte	32
	.short	256
	.byte	2
	.byte	1
	.short	2092
	.short	1473
	.byte	2
	.byte	66
	.byte	40
	.byte	32
	.byte	3
	.byte	1
	.byte	1
	.byte	0
	.byte	0
	.byte	0
	.space	4
	.byte	6
	.byte	69
	.byte	58
	.byte	-108
	.byte	-109
	.byte	118
	.byte	81
	.byte	8
	.byte	1
	.byte	32
	.short	256
	.byte	2
	.byte	2
	.short	2106
	.short	473
	.byte	2
	.byte	68
	.byte	40
	.byte	32
	.byte	3
	.byte	1
	.byte	4
	.byte	0
	.byte	0
	.byte	0
	.space	4
	.byte	6
	.byte	69
	.byte	-34
	.byte	-108
	.byte	-109
	.byte	118
	.byte	81
	.byte	8
	.byte	1
	.byte	32
	.short	256
	.byte	2
	.byte	2
	.short	1074
	.short	473
	.byte	2
	.byte	68
	.byte	40
	.byte	32
	.byte	3
	.byte	1
	.byte	4
	.byte	0
	.byte	0
	.byte	0
	.space	4
	.byte	6
	.byte	69
	.byte	58
	.byte	-92
	.byte	-109
	.byte	122
	.byte	80
	.byte	8
	.byte	1
	.byte	32
	.short	256
	.byte	2
	.byte	2
	.short	2138
	.short	1497
	.byte	2
	.byte	0
	.byte	40
	.byte	32
	.byte	3
	.byte	1
	.byte	1
	.byte	0
	.byte	0
	.byte	0
	.space	4
	.byte	6
	.byte	69
	.byte	-34
	.byte	-108
	.byte	-126
	.byte	118
	.byte	86
	.byte	8
	.byte	1
	.byte	16
	.short	256
	.byte	2
	.byte	2
	.short	2062
	.short	473
	.byte	1
	.byte	0
	.byte	40
	.byte	32
	.byte	3
	.byte	1
	.byte	1
	.byte	0
	.byte	0
	.byte	0
	.space	4
	.byte	6
	.byte	69
	.byte	-34
	.byte	-108
	.byte	-109
	.byte	118
	.byte	-41
	.byte	8
	.byte	1
	.byte	32
	.short	256
	.byte	2
	.byte	2
	.short	1058
	.short	1497
	.byte	2
	.byte	66
	.byte	40
	.byte	32
	.byte	3
	.byte	1
	.byte	1
	.byte	0
	.byte	0
	.byte	0
	.space	4
	.byte	5
	.byte	-20
	.byte	-41
	.byte	-108
	.byte	126
	.byte	100
	.byte	68
	.byte	0
	.byte	1
	.byte	16
	.short	128
	.byte	2
	.byte	2
	.short	2048
	.short	473
	.byte	2
	.byte	49
	.byte	60
	.byte	36
	.byte	3
	.byte	0
	.byte	3
	.byte	0
	.byte	0
	.byte	0
	.space	4
	.byte	6
	.byte	-20
	.byte	-34
	.byte	-43
	.byte	126
	.byte	104
	.byte	68
	.byte	0
	.byte	2
	.byte	16
	.short	128
	.byte	2
	.byte	2
	.short	2048
	.short	505
	.byte	2
	.byte	49
	.byte	60
	.byte	36
	.byte	3
	.byte	0
	.byte	3
	.byte	0
	.byte	0
	.byte	0
	.space	4
	.byte	6
	.byte	-20
	.byte	-41
	.byte	-108
	.byte	122
	.byte	84
	.byte	67
	.byte	0
	.byte	1
	.byte	16
	.short	128
	.byte	2
	.byte	2
	.short	2076
	.short	409
	.byte	2
	.byte	0
	.byte	40
	.byte	36
	.byte	3
	.byte	1
	.byte	3
	.byte	0
	.byte	0
	.byte	0
	.space	4
	.byte	6
	.byte	-20
	.byte	-34
	.byte	-43
	.byte	122
	.byte	88
	.byte	67
	.byte	0
	.byte	2
	.byte	16
	.short	128
	.byte	2
	.byte	2
	.short	2076
	.short	441
	.byte	2
	.byte	0
	.byte	40
	.byte	36
	.byte	3
	.byte	1
	.byte	3
	.byte	0
	.byte	0
	.byte	0
	.space	4
	.byte	6
	.byte	-20
	.byte	-43
	.byte	-108
	.byte	118
	.byte	84
	.byte	67
	.byte	0
	.byte	1
	.byte	16
	.short	128
	.byte	2
	.byte	2
	.short	1038
	.short	281
	.byte	2
	.byte	0
	.byte	24
	.byte	36
	.byte	3
	.byte	1
	.byte	3
	.byte	0
	.byte	0
	.byte	0
	.space	4
	.byte	6
	.byte	-20
	.byte	-41
	.byte	20
	.byte	118
	.byte	84
	.byte	-62
	.byte	0
	.byte	1
	.byte	16
	.short	128
	.byte	2
	.byte	2
	.short	2076
	.short	1169
	.byte	2
	.byte	0
	.byte	24
	.byte	40
	.byte	3
	.byte	1
	.byte	3
	.byte	0
	.byte	0
	.byte	0
	.space	4
	.byte	6
	.byte	-20
	.byte	-34
	.byte	-108
	.byte	-61
	.byte	-92
	.byte	-54
	.byte	0
	.byte	1
	.byte	32
	.short	792
	.byte	2
	.byte	1
	.short	688
	.short	1217
	.byte	11
	.byte	50
	.byte	40
	.byte	32
	.byte	3
	.byte	1
	.byte	1
	.byte	0
	.byte	1
	.byte	0
	.space	4
	.section	.data.NandOptPara,"aw",%progbits
	.set	.LANCHOR152,. + 0
	.type	NandOptPara, %object
	.size	NandOptPara, 128
NandOptPara:
	.byte	1
	.byte	0
	.byte	49
	.byte	63
	.byte	0
	.byte	49
	.byte	-128
	.byte	21
	.byte	0
	.byte	50
	.byte	17
	.byte	-128
	.byte	112
	.byte	120
	.byte	120
	.byte	3
	.byte	1
	.byte	0
	.space	14
	.byte	2
	.byte	0
	.byte	49
	.byte	63
	.byte	0
	.byte	49
	.byte	-128
	.byte	21
	.byte	0
	.byte	0
	.byte	17
	.byte	-127
	.byte	112
	.byte	-15
	.byte	-14
	.byte	0
	.byte	0
	.byte	0
	.space	14
	.byte	3
	.byte	0
	.byte	49
	.byte	63
	.byte	0
	.byte	49
	.byte	-128
	.byte	21
	.byte	96
	.byte	96
	.byte	17
	.byte	-127
	.byte	112
	.byte	-15
	.byte	-14
	.byte	0
	.byte	0
	.byte	0
	.space	14
	.byte	4
	.byte	0
	.byte	49
	.byte	63
	.byte	0
	.byte	49
	.byte	-128
	.byte	21
	.byte	96
	.byte	96
	.byte	17
	.byte	-127
	.byte	112
	.byte	112
	.byte	112
	.byte	0
	.byte	0
	.byte	0
	.space	14
	.section	.data.SamsungRefValue,"aw",%progbits
	.set	.LANCHOR14,. + 0
	.type	SamsungRefValue, %object
	.size	SamsungRefValue, 64
SamsungRefValue:
	.byte	-89
	.byte	-92
	.byte	-91
	.byte	-90
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	5
	.byte	10
	.byte	0
	.byte	0
	.byte	40
	.byte	0
	.byte	-20
	.byte	-40
	.byte	-19
	.byte	-11
	.byte	-19
	.byte	-26
	.byte	10
	.byte	15
	.byte	5
	.byte	0
	.byte	15
	.byte	10
	.byte	-5
	.byte	-20
	.byte	-24
	.byte	-17
	.byte	-24
	.byte	-36
	.byte	-15
	.byte	-5
	.byte	-2
	.byte	-16
	.byte	10
	.byte	0
	.byte	-5
	.byte	-20
	.byte	-48
	.byte	-30
	.byte	-48
	.byte	-62
	.byte	20
	.byte	15
	.byte	-5
	.byte	-20
	.byte	-24
	.byte	-5
	.byte	-24
	.byte	-36
	.byte	30
	.byte	20
	.byte	-5
	.byte	-20
	.byte	-5
	.byte	-1
	.byte	-5
	.byte	-8
	.byte	7
	.byte	12
	.byte	2
	.byte	0
	.section	.data.Toshiba15RefValue,"aw",%progbits
	.set	.LANCHOR11,. + 0
	.type	Toshiba15RefValue, %object
	.size	Toshiba15RefValue, 95
Toshiba15RefValue:
	.byte	4
	.byte	5
	.byte	6
	.byte	7
	.byte	13
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	2
	.byte	4
	.byte	2
	.byte	0
	.byte	0
	.byte	8
	.byte	8
	.byte	0
	.byte	0
	.byte	0
	.byte	124
	.byte	0
	.byte	124
	.byte	124
	.byte	0
	.byte	122
	.byte	0
	.byte	122
	.byte	122
	.byte	0
	.byte	11
	.byte	126
	.byte	118
	.byte	116
	.byte	0
	.byte	120
	.byte	2
	.byte	120
	.byte	122
	.byte	0
	.byte	126
	.byte	4
	.byte	126
	.byte	122
	.byte	0
	.byte	16
	.byte	118
	.byte	114
	.byte	112
	.byte	0
	.byte	118
	.byte	4
	.byte	118
	.byte	120
	.byte	0
	.byte	4
	.byte	4
	.byte	4
	.byte	118
	.byte	0
	.byte	2
	.byte	0
	.byte	126
	.byte	124
	.byte	0
	.byte	6
	.byte	10
	.byte	6
	.byte	2
	.byte	0
	.byte	116
	.byte	124
	.byte	116
	.byte	118
	.byte	0
	.byte	4
	.byte	4
	.byte	124
	.byte	126
	.byte	0
	.byte	0
	.byte	124
	.byte	120
	.byte	120
	.byte	0
	.byte	124
	.byte	118
	.byte	116
	.byte	114
	.byte	0
	.section	.data.ToshibaA19RefValue,"aw",%progbits
	.set	.LANCHOR9,. + 0
	.type	ToshibaA19RefValue, %object
	.size	ToshibaA19RefValue, 45
ToshibaA19RefValue:
	.byte	4
	.byte	5
	.byte	6
	.byte	7
	.byte	13
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	4
	.byte	4
	.byte	124
	.byte	126
	.byte	0
	.byte	0
	.byte	124
	.byte	120
	.byte	120
	.byte	0
	.byte	124
	.byte	118
	.byte	116
	.byte	114
	.byte	0
	.byte	8
	.byte	8
	.byte	0
	.byte	0
	.byte	0
	.byte	11
	.byte	126
	.byte	118
	.byte	116
	.byte	0
	.byte	16
	.byte	118
	.byte	114
	.byte	112
	.byte	0
	.byte	2
	.byte	0
	.byte	126
	.byte	124
	.byte	0
	.section	.data.ToshibaRefValue,"aw",%progbits
	.set	.LANCHOR12,. + 0
	.type	ToshibaRefValue, %object
	.size	ToshibaRefValue, 8
ToshibaRefValue:
	.byte	0
	.byte	4
	.byte	124
	.byte	120
	.byte	116
	.byte	8
	.byte	12
	.byte	112
	.section	.data.ftl_gc_temp_block_bops_scan_page_addr,"aw",%progbits
	.align	1
	.set	.LANCHOR245,. + 0
	.type	ftl_gc_temp_block_bops_scan_page_addr, %object
	.size	ftl_gc_temp_block_bops_scan_page_addr, 2
ftl_gc_temp_block_bops_scan_page_addr:
	.short	-1
	.section	.data.gFtlInitStatus,"aw",%progbits
	.align	2
	.set	.LANCHOR247,. + 0
	.type	gFtlInitStatus, %object
	.size	gFtlInitStatus, 4
gFtlInitStatus:
	.word	-1
	.section	.data.gNandParaInfo,"aw",%progbits
	.align	1
	.set	.LANCHOR31,. + 0
	.type	gNandParaInfo, %object
	.size	gNandParaInfo, 32
gNandParaInfo:
	.byte	0
	.byte	0
	.space	5
	.byte	0
	.byte	1
	.byte	8
	.short	128
	.byte	2
	.byte	1
	.short	2048
	.short	0
	.byte	1
	.byte	0
	.byte	24
	.byte	32
	.byte	1
	.byte	0
	.byte	1
	.byte	0
	.byte	0
	.byte	0
	.space	4
	.section	.data.gSlcNandParaInfo,"aw",%progbits
	.align	1
	.set	.LANCHOR209,. + 0
	.type	gSlcNandParaInfo, %object
	.size	gSlcNandParaInfo, 32
gSlcNandParaInfo:
	.byte	2
	.byte	-104
	.byte	-15
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	1
	.byte	1
	.byte	4
	.short	64
	.byte	1
	.byte	1
	.short	1024
	.short	256
	.byte	0
	.byte	0
	.byte	16
	.byte	40
	.byte	1
	.byte	0
	.byte	1
	.byte	0
	.byte	0
	.byte	0
	.space	4
	.section	.data.power_up_flag,"aw",%progbits
	.align	2
	.type	power_up_flag, %object
	.size	power_up_flag, 4
power_up_flag:
	.word	1
	.section	.data.random_seed,"aw",%progbits
	.align	1
	.set	.LANCHOR5,. + 0
	.type	random_seed, %object
	.size	random_seed, 256
random_seed:
	.short	22378
	.short	1512
	.short	25245
	.short	17827
	.short	25756
	.short	19440
	.short	9026
	.short	10030
	.short	29528
	.short	20467
	.short	29676
	.short	24432
	.short	31328
	.short	6872
	.short	13426
	.short	13842
	.short	8783
	.short	1108
	.short	782
	.short	28837
	.short	30729
	.short	9505
	.short	18676
	.short	23085
	.short	18730
	.short	1085
	.short	32609
	.short	14697
	.short	20858
	.short	15170
	.short	30365
	.short	1607
	.short	32298
	.short	4995
	.short	18905
	.short	1976
	.short	9592
	.short	20204
	.short	17443
	.short	13615
	.short	23330
	.short	29369
	.short	13947
	.short	9398
	.short	32398
	.short	8984
	.short	27600
	.short	21785
	.short	6019
	.short	6311
	.short	31598
	.short	30210
	.short	19327
	.short	13896
	.short	11347
	.short	27545
	.short	3107
	.short	26575
	.short	32270
	.short	19852
	.short	20601
	.short	8349
	.short	9290
	.short	29819
	.short	13579
	.short	3661
	.short	28676
	.short	27331
	.short	32574
	.short	8693
	.short	31253
	.short	9081
	.short	5399
	.short	6842
	.short	20087
	.short	5537
	.short	1274
	.short	11617
	.short	9530
	.short	4866
	.short	8035
	.short	23219
	.short	1178
	.short	23272
	.short	7383
	.short	18944
	.short	12488
	.short	12871
	.short	29340
	.short	20532
	.short	11022
	.short	22514
	.short	228
	.short	22363
	.short	24978
	.short	14584
	.short	12138
	.short	3092
	.short	17916
	.short	16863
	.short	14554
	.short	31457
	.short	29474
	.short	25311
	.short	24121
	.short	3684
	.short	28037
	.short	22865
	.short	22839
	.short	25217
	.short	13217
	.short	27186
	.short	14938
	.short	11180
	.short	29754
	.short	24180
	.short	15150
	.short	32455
	.short	20434
	.short	23848
	.short	29983
	.short	16120
	.short	14769
	.short	20041
	.short	29803
	.short	28406
	.short	17598
	.short	28087
	.section	.data.refValueDefault,"aw",%progbits
	.set	.LANCHOR204,. + 0
	.type	refValueDefault, %object
	.size	refValueDefault, 28
refValueDefault:
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	6
	.byte	10
	.byte	6
	.byte	0
	.byte	-3
	.byte	-7
	.byte	-8
	.byte	0
	.byte	-6
	.byte	-13
	.byte	-15
	.byte	0
	.byte	-11
	.byte	-20
	.byte	-23
	.byte	0
	.byte	0
	.byte	-26
	.byte	-30
	.byte	0
	.byte	0
	.byte	-32
	.byte	-37
	.section	.rodata.FlashDdrTunningRead.str1.1,"aMS",%progbits,1
.LC9:
	.ascii	"sdr read ok %x ecc=%d\012\000"
.LC10:
	.ascii	"sync para %d\012\000"
.LC11:
	.ascii	"TOG mode Read error %x %x\012\000"
	.section	.rodata.FlashEraseSLc2KBlocks.str1.1,"aMS",%progbits,1
.LC1:
	.ascii	"FlashEraseBlocks pageAddr error %x\012\000"
	.section	.rodata.FlashInit.str1.1,"aMS",%progbits,1
.LC24:
	.ascii	"No.%d FLASH ID:%x %x %x %x %x %x\012\000"
.LC25:
	.ascii	"FlashLoadPhyInfo fail %x!!\012\000"
	.section	.rodata.FlashProgSlc2KPages.str1.1,"aMS",%progbits,1
.LC30:
	.ascii	"prog error: = %x\012\000"
.LC31:
	.ascii	"prog read error: = %x\012\000"
.LC32:
	.ascii	"prog read REFRESH: = %x\012\000"
.LC33:
	.ascii	"prog read s error: = %x %x %x\012\000"
.LC34:
	.ascii	"prog read d error: = %x %x %x\012\000"
	.section	.rodata.FlashReadFacBbtData.str1.1,"aMS",%progbits,1
.LC59:
	.ascii	"BBT:\000"
	.section	.rodata.FlashReadIdbDataRaw.str1.1,"aMS",%progbits,1
.LC15:
	.ascii	"ECC:%d\012\000"
	.section	.rodata.FlashReadPage.str1.1,"aMS",%progbits,1
.LC12:
	.ascii	"read retry status %x %x %x\012\000"
	.section	.rodata.FlashReadPages.str1.1,"aMS",%progbits,1
.LC29:
	.ascii	"ReadRetry pageadd=%x ecc=%x err=%x\012\000"
	.section	.rodata.FlashReadSlc2KPages.str1.1,"aMS",%progbits,1
.LC26:
	.ascii	"Read pageadd=%x  ecc=%x err=%x\012\000"
.LC27:
	.ascii	"data:\000"
.LC28:
	.ascii	"spare:\000"
	.section	.rodata.FtlBbmMapBadBlock.str1.1,"aMS",%progbits,1
.LC2:
	.ascii	"phyBlk = 0x%x die = %d block_in_die = 0x%x 0x%8x\012"
	.ascii	"\000"
	.section	.rodata.FtlBbmTblFlush.str1.1,"aMS",%progbits,1
.LC35:
	.ascii	"FtlBbmTblFlush id=%x,page=%x,previd=%x cnt=%d\012\000"
.LC36:
	.ascii	"FtlBbmTblFlush error:%x\012\000"
.LC37:
	.ascii	"FtlBbmTblFlush error = %x error count = %d\012\000"
	.section	.rodata.FtlCacheWriteBack.str1.1,"aMS",%progbits,1
.LC76:
	.ascii	"Ftlwrite decrement_vpc_count %x = %d\012\000"
	.section	.rodata.FtlCheckVpc.str1.1,"aMS",%progbits,1
.LC63:
	.ascii	"FtlCheckVpc2 %x = %x  %x\012\000"
.LC64:
	.ascii	"free blk vpc error %x = %x  %x\012\000"
.LC65:
	.ascii	"error_flag %x\012\000"
	.section	.rodata.FtlDumpBlockInfo.str1.1,"aMS",%progbits,1
.LC48:
	.ascii	"...%s enter...\012\000"
.LC49:
	.ascii	"superBlkID = %x vpc=%x\012\000"
.LC50:
	.ascii	"flashmode = %x pagenum = %x %x\012\000"
.LC51:
	.ascii	"id = %x,%x addr= %x,spare= %x %x %x %x data=%x %x\012"
	.ascii	"\000"
	.section	.rodata.FtlDumpSysBlock.str1.1,"aMS",%progbits,1
.LC84:
	.ascii	"id = %x,%x addr= %x,spare= %x %x %x %x data = %x\012"
	.ascii	"\000"
.LC85:
	.ascii	":\000"
	.section	.rodata.FtlFreeSysBlkQueueOut.str1.1,"aMS",%progbits,1
.LC3:
	.ascii	"FtlFreeSysBlkQueueOut free count = %d\012\000"
.LC4:
	.ascii	"FtlFreeSysBlkQueueOut = %x, free count = %d, error\012"
	.ascii	"\000"
	.section	.rodata.FtlGcFreeTempBlock.str1.1,"aMS",%progbits,1
.LC74:
	.ascii	"GC des block %x done\012\000"
	.section	.rodata.FtlGcScanTempBlk.str1.1,"aMS",%progbits,1
.LC72:
	.ascii	"FtlGcScanTempBlk Error ID %x %x!!!!!!! \012\000"
.LC73:
	.ascii	"FtlGcScanTempBlkError ID %x %x!!!!!!!\012\000"
	.section	.rodata.FtlInit.str1.1,"aMS",%progbits,1
.LC77:
	.ascii	"FTL version: 5.0.63 20210318\000"
.LC78:
	.ascii	"...%s: no bad block mapping table, format device\012"
	.ascii	"\000"
.LC79:
	.ascii	"...%s FtlSysBlkInit error ,format device!\012\000"
	.section	.rodata.FtlLoadEctTbl.str1.1,"aMS",%progbits,1
.LC45:
	.ascii	"no ect\000"
	.section	.rodata.FtlLoadSysInfo.str1.1,"aMS",%progbits,1
.LC47:
	.ascii	"id = %x,%x addr= %x,spare= %x %x %x %x data= %x\012"
	.ascii	"\000"
	.section	.rodata.FtlLowFormat.str1.1,"aMS",%progbits,1
.LC75:
	.ascii	"too many bad block  = %d %d\012\000"
	.section	.rodata.FtlMapWritePage.str1.1,"aMS",%progbits,1
.LC42:
	.ascii	"FtlMapWritePage error = %x\012\000"
.LC43:
	.ascii	"FtlMapWritePage error = %x error count = %d\012\000"
	.section	.rodata.FtlRecoverySuperblock.str1.1,"aMS",%progbits,1
.LC69:
	.ascii	"RSB refresh addr %x\012\000"
.LC70:
	.ascii	"spuer block %x vpn is 0\012 \000"
.LC71:
	.ascii	"g_recovery_ppa %x ver %x\012 \000"
	.section	.rodata.FtlScanAllBlock.str1.1,"aMS",%progbits,1
.LC52:
	.ascii	"blk = %x vpc=%x mode = %x\012\000"
.LC53:
	.ascii	"mlc id = %x,%x addr= %x,spare= %x %x %x %x data=%x "
	.ascii	"%x\012\000"
.LC54:
	.ascii	"slc id = %x,%x addr= %x,spare= %x %x %x %x data=%x "
	.ascii	"%x\012\000"
	.section	.rodata.FtlVendorPartRead.str1.1,"aMS",%progbits,1
.LC44:
	.ascii	"FtlVendorPartRead refresh = %x phyAddr = %x\012\000"
	.section	.rodata.FtlVpcTblFlush.str1.1,"aMS",%progbits,1
.LC40:
	.ascii	"FtlVpcTblFlush error = %x error count = %d\012\000"
	.section	.rodata.FtlWrite.str1.1,"aMS",%progbits,1
.LC83:
	.ascii	"FtlWrite: lpa error:%x %x\012\000"
	.section	.rodata.Ftl_load_ext_data.str1.1,"aMS",%progbits,1
.LC46:
	.ascii	"slc mode\000"
	.section	.rodata.Ftlscanalldata.str1.1,"aMS",%progbits,1
.LC66:
	.ascii	"Ftlscanalldata = %x\012\000"
.LC67:
	.ascii	"scan lpa = %x ppa= %x\012\000"
.LC68:
	.ascii	"lba = %x,addr= %x,spare= %x %x %x %x data=%x %x\012"
	.ascii	"\000"
	.section	.rodata.HynixGetReadRetryDefault.str1.1,"aMS",%progbits,1
.LC22:
	.ascii	"otp error! %d\000"
.LC23:
	.ascii	"rr\000"
	.section	.rodata.INSERT_DATA_LIST.str1.1,"aMS",%progbits,1
.LC5:
	.ascii	"\012!!!!! error @ func:%s - line:%d\012\000"
.LC6:
	.ascii	"!!!!! FTL sys Error !!!!!\000"
.LC7:
	.ascii	"%s\012\000"
	.section	.rodata.MicronReadRetrial.str1.1,"aMS",%progbits,1
.LC13:
	.ascii	"micron RR %d row=%x,count %d,status=%d\012\000"
	.section	.rodata.__func__.10661,"a",%progbits
	.set	.LANCHOR255,. + 0
	.type	__func__.10661, %object
	.size	__func__.10661, 8
__func__.10661:
	.ascii	"FtlInit\000"
	.section	.rodata.__func__.10765,"a",%progbits
	.set	.LANCHOR258,. + 0
	.type	__func__.10765, %object
	.size	__func__.10765, 9
__func__.10765:
	.ascii	"FtlWrite\000"
	.section	.rodata.__func__.10855,"a",%progbits
	.set	.LANCHOR127,. + 0
	.type	__func__.10855, %object
	.size	__func__.10855, 14
__func__.10855:
	.ascii	"FtlBbt2Bitmap\000"
	.section	.rodata.__func__.10901,"a",%progbits
	.set	.LANCHOR220,. + 0
	.type	__func__.10901, %object
	.size	__func__.10901, 11
__func__.10901:
	.ascii	"FtlLoadBbt\000"
	.section	.rodata.__func__.10994,"a",%progbits
	.set	.LANCHOR91,. + 0
	.type	__func__.10994, %object
	.size	__func__.10994, 17
__func__.10994:
	.ascii	"INSERT_FREE_LIST\000"
	.section	.rodata.__func__.10998,"a",%progbits
	.set	.LANCHOR88,. + 0
	.type	__func__.10998, %object
	.size	__func__.10998, 17
__func__.10998:
	.ascii	"INSERT_DATA_LIST\000"
	.section	.rodata.__func__.11036,"a",%progbits
	.set	.LANCHOR92,. + 0
	.type	__func__.11036, %object
	.size	__func__.11036, 17
__func__.11036:
	.ascii	"List_remove_node\000"
	.section	.rodata.__func__.11066,"a",%progbits
	.set	.LANCHOR96,. + 0
	.type	__func__.11066, %object
	.size	__func__.11066, 22
__func__.11066:
	.ascii	"List_update_data_list\000"
	.section	.rodata.__func__.11073,"a",%progbits
	.set	.LANCHOR237,. + 0
	.type	__func__.11073, %object
	.size	__func__.11073, 20
__func__.11073:
	.ascii	"ftl_load_l2p_region\000"
	.section	.rodata.__func__.11104,"a",%progbits
	.set	.LANCHOR97,. + 0
	.type	__func__.11104, %object
	.size	__func__.11104, 26
__func__.11104:
	.ascii	"ftl_map_blk_alloc_new_blk\000"
	.section	.rodata.__func__.11114,"a",%progbits
	.set	.LANCHOR221,. + 0
	.type	__func__.11114, %object
	.size	__func__.11114, 15
__func__.11114:
	.ascii	"ftl_map_blk_gc\000"
	.section	.rodata.__func__.11127,"a",%progbits
	.set	.LANCHOR222,. + 0
	.type	__func__.11127, %object
	.size	__func__.11127, 31
__func__.11127:
	.ascii	"Ftl_write_map_blk_to_last_page\000"
	.section	.rodata.__func__.11140,"a",%progbits
	.set	.LANCHOR223,. + 0
	.type	__func__.11140, %object
	.size	__func__.11140, 16
__func__.11140:
	.ascii	"FtlMapWritePage\000"
	.section	.rodata.__func__.11160,"a",%progbits
	.set	.LANCHOR100,. + 0
	.type	__func__.11160, %object
	.size	__func__.11160, 22
__func__.11160:
	.ascii	"select_l2p_ram_region\000"
	.section	.rodata.__func__.11176,"a",%progbits
	.set	.LANCHOR236,. + 0
	.type	__func__.11176, %object
	.size	__func__.11176, 9
__func__.11176:
	.ascii	"log2phys\000"
	.section	.rodata.__func__.11238,"a",%progbits
	.set	.LANCHOR219,. + 0
	.type	__func__.11238, %object
	.size	__func__.11238, 15
__func__.11238:
	.ascii	"FtlVpcTblFlush\000"
	.section	.rodata.__func__.11257,"a",%progbits
	.set	.LANCHOR229,. + 0
	.type	__func__.11257, %object
	.size	__func__.11257, 14
__func__.11257:
	.ascii	"FtlScanSysBlk\000"
	.section	.rodata.__func__.11312,"a",%progbits
	.set	.LANCHOR230,. + 0
	.type	__func__.11312, %object
	.size	__func__.11312, 15
__func__.11312:
	.ascii	"FtlLoadSysInfo\000"
	.section	.rodata.__func__.11323,"a",%progbits
	.set	.LANCHOR238,. + 0
	.type	__func__.11323, %object
	.size	__func__.11323, 12
__func__.11323:
	.ascii	"FtlCheckVpc\000"
	.section	.rodata.__func__.11355,"a",%progbits
	.set	.LANCHOR233,. + 0
	.type	__func__.11355, %object
	.size	__func__.11355, 17
__func__.11355:
	.ascii	"FtlDumpBlockInfo\000"
	.section	.rodata.__func__.11374,"a",%progbits
	.set	.LANCHOR234,. + 0
	.type	__func__.11374, %object
	.size	__func__.11374, 16
__func__.11374:
	.ascii	"FtlScanAllBlock\000"
	.section	.rodata.__func__.11479,"a",%progbits
	.set	.LANCHOR239,. + 0
	.type	__func__.11479, %object
	.size	__func__.11479, 16
__func__.11479:
	.ascii	"FtlReUsePrevPpa\000"
	.section	.rodata.__func__.11512,"a",%progbits
	.set	.LANCHOR240,. + 0
	.type	__func__.11512, %object
	.size	__func__.11512, 22
__func__.11512:
	.ascii	"FtlRecoverySuperblock\000"
	.section	.rodata.__func__.11566,"a",%progbits
	.set	.LANCHOR103,. + 0
	.type	__func__.11566, %object
	.size	__func__.11566, 16
__func__.11566:
	.ascii	"make_superblock\000"
	.section	.rodata.__func__.11586,"a",%progbits
	.set	.LANCHOR143,. + 0
	.type	__func__.11586, %object
	.size	__func__.11586, 18
__func__.11586:
	.ascii	"SupperBlkListInit\000"
	.section	.rodata.__func__.11632,"a",%progbits
	.set	.LANCHOR235,. + 0
	.type	__func__.11632, %object
	.size	__func__.11632, 17
__func__.11632:
	.ascii	"ftl_scan_all_ppa\000"
	.section	.rodata.__func__.11677,"a",%progbits
	.set	.LANCHOR212,. + 0
	.type	__func__.11677, %object
	.size	__func__.11677, 25
__func__.11677:
	.ascii	"allocate_data_superblock\000"
	.section	.rodata.__func__.11691,"a",%progbits
	.set	.LANCHOR228,. + 0
	.type	__func__.11691, %object
	.size	__func__.11691, 29
__func__.11691:
	.ascii	"allocate_new_data_superblock\000"
	.section	.rodata.__func__.11697,"a",%progbits
	.set	.LANCHOR217,. + 0
	.type	__func__.11697, %object
	.size	__func__.11697, 19
__func__.11697:
	.ascii	"get_new_active_ppa\000"
	.section	.rodata.__func__.11708,"a",%progbits
	.set	.LANCHOR215,. + 0
	.type	__func__.11708, %object
	.size	__func__.11708, 16
__func__.11708:
	.ascii	"update_vpc_list\000"
	.section	.rodata.__func__.11713,"a",%progbits
	.set	.LANCHOR216,. + 0
	.type	__func__.11713, %object
	.size	__func__.11713, 20
__func__.11713:
	.ascii	"decrement_vpc_count\000"
	.section	.rodata.__func__.11781,"a",%progbits
	.set	.LANCHOR246,. + 0
	.type	__func__.11781, %object
	.size	__func__.11781, 19
__func__.11781:
	.ascii	"FtlGcFreeTempBlock\000"
	.section	.rodata.__func__.11882,"a",%progbits
	.set	.LANCHOR251,. + 0
	.type	__func__.11882, %object
	.size	__func__.11882, 10
__func__.11882:
	.ascii	"ftl_do_gc\000"
	.section	.rodata.decrement_vpc_count.str1.1,"aMS",%progbits,1
.LC38:
	.ascii	"decrement_vpc_count %x = %d\012\000"
.LC39:
	.ascii	"decrement_vpc_count %x = %d in free list\012\000"
	.section	.rodata.dump_map_info.str1.1,"aMS",%progbits,1
.LC86:
	.ascii	"phyBlk = %x,addr= %x,spare= %x %x %x %x data=%x %x\012"
	.ascii	"\000"
.LC87:
	.ascii	"Mblk:\000"
.LC88:
	.ascii	"L2P:\000"
.LC89:
	.ascii	"L2PC:\000"
	.section	.rodata.ftl_fix_nand_power_lost_error.str1.1,"aMS",%progbits,1
.LC81:
	.ascii	"fix power lost blk = %x vpc=%x\012\000"
.LC82:
	.ascii	"erase power lost blk = %x vpc=%x\012\000"
	.section	.rodata.ftl_map_blk_alloc_new_blk.str1.1,"aMS",%progbits,1
.LC8:
	.ascii	"FtlFreeSysBlkQueueOut = %x, free count = %d\012\000"
	.section	.rodata.ftl_map_blk_gc.str1.1,"aMS",%progbits,1
.LC41:
	.ascii	"page map lost: %x %x\012\000"
	.section	.rodata.ftl_scan_all_ppa.str1.1,"aMS",%progbits,1
.LC55:
	.ascii	"ftl_scan_all_ppa blk %x page %x flag: %x\012\000"
.LC56:
	.ascii	"ftl_scan_all_ppa blk %x page %x flag: %x .........."
	.ascii	"..... is bad block\012\000"
.LC57:
	.ascii	"addr= %x, status= %d,spare= %x %x %x %x data=%x %x\012"
	.ascii	"\000"
.LC58:
	.ascii	"%s finished\012\000"
	.section	.rodata.idb_write_data.str1.1,"aMS",%progbits,1
.LC16:
	.ascii	"1 write_idblock fix data %x %x %x\012\000"
.LC17:
	.ascii	"write_idblock fail! %x %x %x %x\012\000"
.LC18:
	.ascii	"write_idblock fail! %x\012\000"
	.section	.rodata.log2phys.str1.1,"aMS",%progbits,1
.LC60:
	.ascii	"region_id = %x phyAddr = %x\012\000"
.LC61:
	.ascii	"map_ppn:\000"
.LC62:
	.ascii	"load_l2p_region refresh = %x phyAddr = %x\012\000"
	.section	.rodata.rk_ftl_init.str1.1,"aMS",%progbits,1
.LC80:
	.ascii	"FtlInit %x\012\000"
	.section	.rodata.rknand_print_hex.str1.1,"aMS",%progbits,1
.LC19:
	.ascii	"%s 0x%x:\000"
.LC20:
	.ascii	"%x \000"
.LC21:
	.ascii	"\000"
	.section	.rodata.samsung_14nm_mlc_rr,"a",%progbits
	.set	.LANCHOR148,. + 0
	.type	samsung_14nm_mlc_rr, %object
	.size	samsung_14nm_mlc_rr, 104
samsung_14nm_mlc_rr:
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	-4
	.byte	3
	.byte	-4
	.byte	-6
	.byte	6
	.byte	0
	.byte	6
	.byte	-10
	.byte	-10
	.byte	4
	.byte	-10
	.byte	16
	.byte	12
	.byte	-4
	.byte	12
	.byte	8
	.byte	-16
	.byte	10
	.byte	-16
	.byte	24
	.byte	18
	.byte	-14
	.byte	18
	.byte	-4
	.byte	-22
	.byte	-16
	.byte	-22
	.byte	-8
	.byte	24
	.byte	-9
	.byte	24
	.byte	8
	.byte	-28
	.byte	-4
	.byte	-28
	.byte	16
	.byte	30
	.byte	10
	.byte	30
	.byte	10
	.byte	-34
	.byte	6
	.byte	-34
	.byte	0
	.byte	36
	.byte	-8
	.byte	36
	.byte	-8
	.byte	-40
	.byte	-2
	.byte	-40
	.byte	-20
	.byte	-46
	.byte	-4
	.byte	-46
	.byte	-30
	.byte	3
	.byte	0
	.byte	3
	.byte	-3
	.byte	-2
	.byte	-4
	.byte	-2
	.byte	-6
	.byte	-4
	.byte	-4
	.byte	-4
	.byte	-10
	.byte	-6
	.byte	-8
	.byte	-6
	.byte	-14
	.byte	-9
	.byte	-8
	.byte	-9
	.byte	-18
	.byte	-52
	.byte	22
	.byte	-52
	.byte	10
	.byte	42
	.byte	4
	.byte	42
	.byte	4
	.byte	48
	.byte	-9
	.byte	48
	.byte	4
	.byte	-58
	.byte	12
	.byte	-58
	.byte	0
	.byte	-64
	.byte	-24
	.byte	-64
	.byte	-6
	.byte	9
	.byte	18
	.byte	9
	.byte	8
	.section	.rodata.samsung_14nm_slc_rr,"a",%progbits
	.set	.LANCHOR147,. + 0
	.type	samsung_14nm_slc_rr, %object
	.size	samsung_14nm_slc_rr, 26
samsung_14nm_slc_rr:
	.byte	0
	.byte	10
	.byte	-10
	.byte	20
	.byte	-20
	.byte	30
	.byte	-30
	.byte	40
	.byte	-40
	.byte	50
	.byte	-50
	.byte	60
	.byte	-60
	.byte	-70
	.byte	-80
	.byte	-90
	.byte	-100
	.byte	-110
	.byte	-120
	.byte	-9
	.byte	70
	.byte	80
	.byte	90
	.byte	-125
	.byte	-115
	.byte	100
	.section	.rodata.samsung_read_retrial.str1.1,"aMS",%progbits,1
.LC14:
	.ascii	"samsung RR %d row=%x,count %d,status=%d\012\000"
	.hidden	free
