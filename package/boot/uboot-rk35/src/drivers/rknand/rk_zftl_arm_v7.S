/*
 * Copyright (c) 2016-2017, Fuzhou Rockchip Electronics Co., Ltd
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * date: 2021-01-07
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
	.file	"rk_zftl_arm_v7.S"
	.section	.text.flash_mem_cmp8,"ax",%progbits
	.align	1
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	flash_mem_cmp8, %function
flash_mem_cmp8:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	movs	r3, #0
	push	{r4, r5, lr}
.L2:
	cmp	r3, r2
	bne	.L5
	movs	r0, #0
	pop	{r4, r5, pc}
.L5:
	ldrb	r5, [r0, r3]	@ zero_extendqisi2
	ldrb	r4, [r1, r3]	@ zero_extendqisi2
	adds	r3, r3, #1
	cmp	r5, r4
	beq	.L2
	mov	r0, r3
	pop	{r4, r5, pc}
	.size	flash_mem_cmp8, .-flash_mem_cmp8
	.global	__aeabi_uidiv
	.global	__aeabi_uidivmod
	.section	.text.slc_phy_page_address_calc,"ax",%progbits
	.align	1
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	slc_phy_page_address_calc, %function
slc_phy_page_address_calc:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r3, r4, r5, r6, r7, lr}
	mov	r4, r0
	ldr	r3, .L16
	ldr	r7, .L16+4
	ldrb	r3, [r3]	@ zero_extendqisi2
	cbz	r3, .L7
	ldrb	r3, [r7]	@ zero_extendqisi2
	cbz	r3, .L8
.L7:
	ldr	r3, .L16+8
	mov	r0, r4
	ldrh	r5, [r3]
	mov	r1, r5
	bl	__aeabi_uidiv
	mov	r1, r5
	mul	r6, r5, r0
	mov	r0, r4
	bl	__aeabi_uidivmod
	ldrb	r3, [r7]	@ zero_extendqisi2
	cbz	r3, .L9
	add	r4, r6, r1, lsl #1
.L8:
	mov	r0, r4
	pop	{r3, r4, r5, r6, r7, pc}
.L9:
	ldr	r3, .L16+12
	ldrh	r4, [r3, r1, lsl #1]
	add	r4, r4, r6
	b	.L8
.L17:
	.align	2
.L16:
	.word	.LANCHOR0
	.word	.LANCHOR1
	.word	.LANCHOR2
	.word	.LANCHOR3
	.size	slc_phy_page_address_calc, .-slc_phy_page_address_calc
	.section	.text._list_remove_node,"ax",%progbits
	.align	1
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	_list_remove_node, %function
_list_remove_node:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r3, r4, r5, r6, r7, r8, r10, lr}
	movs	r5, #6
	ldr	r6, .L26
	muls	r5, r1, r5
	movw	r3, #65535
	mov	r8, r2
	mov	r10, r0
	ldr	r7, [r6]
	ldrh	r1, [r7, r5]
	adds	r4, r7, r5
	ldrh	r2, [r4, #2]
	cmp	r1, r3
	ldr	r3, [r0]
	bne	.L19
	cmp	r2, r1
	bne	.L19
	cmp	r4, r3
	bne	.L18
.L19:
	movw	r1, #65535
	cmp	r2, r1
	bne	.L21
	cmp	r4, r3
	beq	.L21
	movs	r2, #202
	ldr	r1, .L26+4
	ldr	r0, .L26+8
	bl	printf
.L21:
	ldr	r3, [r10]
	movw	r1, #65535
	cmp	r4, r3
	ldrh	r3, [r7, r5]
	bne	.L22
	cmp	r3, r1
	ittee	ne
	ldrne	r0, [r6]
	movne	r2, #6
	moveq	r3, #0
	streq	r3, [r10]
	ittt	ne
	mlane	r3, r2, r3, r0
	strne	r3, [r10]
	strhne	r1, [r3, #2]	@ movhi
.L24:
	movw	r3, #65535
	strh	r3, [r7, r5]	@ movhi
	strh	r3, [r4, #2]	@ movhi
	ldrh	r3, [r8]
	subs	r3, r3, #1
	strh	r3, [r8]	@ movhi
.L18:
	pop	{r3, r4, r5, r6, r7, r8, r10, pc}
.L22:
	cmp	r3, r1
	ldrh	r1, [r4, #2]
	bne	.L25
	cmp	r1, r3
	beq	.L24
	movs	r2, #6
	ldr	r0, [r6]
	muls	r1, r2, r1
	strh	r3, [r0, r1]	@ movhi
	b	.L24
.L25:
	ldr	r0, [r6]
	movs	r2, #6
	mla	r6, r2, r3, r0
	strh	r1, [r6, #2]	@ movhi
	ldrh	r1, [r4, #2]
	muls	r2, r1, r2
	strh	r3, [r0, r2]	@ movhi
	b	.L24
.L27:
	.align	2
.L26:
	.word	.LANCHOR4
	.word	.LANCHOR5
	.word	.LC0
	.size	_list_remove_node, .-_list_remove_node
	.section	.text.hynix_set_rr_para,"ax",%progbits
	.align	1
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	hynix_set_rr_para, %function
hynix_set_rr_para:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r3, r4, r5, r6, r7, r8, r10, lr}
	lsls	r7, r0, #8
	ldr	r3, .L33
	ldr	r4, .L33+4
	ldr	r6, [r3]
	ldr	r8, [r4]
	ldrb	r2, [r6, #113]	@ zero_extendqisi2
	add	r4, r6, #112
	ldrb	r5, [r6, #112]	@ zero_extendqisi2
	add	ip, r6, #128
	adds	r6, r6, #127
	muls	r1, r2, r1
	cmp	r5, #8
	it	ne
	movne	r5, #160
	add	r2, r2, #-1
	add	r10, ip, r2
	add	r1, r1, #32
	it	ne
	smlabbne	r1, r5, r0, r1
	add	r5, r8, r7
	add	r4, r4, r1
	movs	r1, #54
	subs	r4, r4, #1
	str	r1, [r5, #2056]
.L31:
	cmp	r6, r10
	bne	.L32
	add	r7, r7, r8
	movs	r3, #22
	str	r3, [r7, #2056]
	pop	{r3, r4, r5, r6, r7, r8, r10, pc}
.L32:
	ldrb	r3, [r6, #1]!	@ zero_extendqisi2
	movs	r0, #1
	str	r3, [r5, #2052]
	bl	udelay
	ldrsb	r3, [r4, #1]!
	str	r3, [r5, #2048]
	b	.L31
.L34:
	.align	2
.L33:
	.word	.LANCHOR6
	.word	.LANCHOR7
	.size	hynix_set_rr_para, .-hynix_set_rr_para
	.section	.text._insert_free_list,"ax",%progbits
	.align	1
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	_insert_free_list, %function
_insert_free_list:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 0, uses_anonymous_args = 0
	ldr	r3, .L43
	push	{r0, r1, r4, r5, r6, r7, r8, r10, fp, lr}
	ldrh	r3, [r3]
	cmp	r3, r1
	bls	.L35
	ldrh	r3, [r2]
	movw	r10, #65535
	ldr	r7, [r0]
	adds	r3, r3, #1
	strh	r3, [r2]	@ movhi
	movs	r2, #6
	ldr	r3, .L43+4
	mul	lr, r2, r1
	ldr	r5, [r3]
	add	r6, r5, lr
	strh	r10, [r6, #2]	@ movhi
	strh	r10, [r5, lr]	@ movhi
	cbnz	r7, .L37
.L42:
	str	r6, [r0]
	b	.L35
.L37:
	ldr	r3, .L43+8
	str	r2, [sp, #4]
	ldr	ip, [r3]
	ldr	r3, .L43+12
	ldrh	r4, [ip, r1, lsl #2]
	ldrh	r8, [r3]
	ldr	r3, [ip, r1, lsl #2]
	ubfx	r4, r4, #0, #11
	ubfx	r3, r3, #11, #8
	smulbb	r3, r3, r8
	add	r3, r3, r4
	uxth	r3, r3
	str	r3, [sp]
	subs	r3, r7, r5
	asrs	r4, r3, #1
	ldr	r3, .L43+16
	muls	r3, r4, r3
	mov	r4, r7
	uxth	r3, r3
.L40:
	ldr	r2, [ip, r3, lsl #2]
	ldrh	fp, [ip, r3, lsl #2]
	ubfx	r2, r2, #11, #8
	smulbb	r2, r2, r8
	ubfx	fp, fp, #0, #11
	add	r2, r2, fp
	uxth	fp, r2
	ldr	r2, [sp]
	cmp	r2, fp
	bls	.L38
	ldrh	r2, [r4]
	cmp	r2, r10
	bne	.L39
	strh	r3, [r6, #2]	@ movhi
	strh	r1, [r4]	@ movhi
.L35:
	add	sp, sp, #8
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r10, fp, pc}
.L39:
	ldr	r3, [sp, #4]
	mla	r4, r3, r2, r5
	mov	r3, r2
	b	.L40
.L38:
	ldrh	r2, [r4, #2]
	cmp	r7, r4
	strh	r2, [r6, #2]	@ movhi
	strh	r3, [r5, lr]	@ movhi
	bne	.L41
	strh	r1, [r7, #2]	@ movhi
	b	.L42
.L41:
	ldrh	r2, [r4, #2]
	movs	r3, #6
	muls	r3, r2, r3
	strh	r1, [r5, r3]	@ movhi
	strh	r1, [r4, #2]	@ movhi
	b	.L35
.L44:
	.align	2
.L43:
	.word	.LANCHOR8
	.word	.LANCHOR4
	.word	.LANCHOR9
	.word	.LANCHOR10
	.word	-1431655765
	.size	_insert_free_list, .-_insert_free_list
	.section	.text._insert_data_list,"ax",%progbits
	.align	1
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	_insert_data_list, %function
_insert_data_list:
	@ args = 0, pretend = 0, frame = 24
	@ frame_needed = 0, uses_anonymous_args = 0
	ldr	r3, .L67
	push	{r4, r5, r6, r7, r8, r10, fp, lr}
	mov	lr, r0
	sub	sp, sp, #24
	ldrh	r3, [r3]
	cmp	r3, r1
	bls	.L45
	ldrh	r3, [r2]
	ldr	r0, [r0]
	adds	r3, r3, #1
	strh	r3, [r2]	@ movhi
	ldr	r3, .L67+4
	ldr	r5, [r3]
	movs	r3, #6
	mul	r10, r3, r1
	movw	r3, #65535
	add	r6, r5, r10
	strh	r3, [r6, #2]	@ movhi
	strh	r3, [r5, r10]	@ movhi
	cbnz	r0, .L48
.L66:
	str	r6, [lr]
	b	.L45
.L48:
	ldr	r3, .L67+8
	ldrh	r7, [r6, #4]
	ldr	r3, [r3]
	ldrh	r4, [r3, r1, lsl #1]
	muls	r4, r7, r4
	str	r3, [sp, #8]
	ldr	r3, .L67+12
	str	r4, [sp]
	ldr	r8, [r3]
	ldr	r3, [r8, r1, lsl #2]
	ubfx	r2, r3, #11, #8
	ldr	r3, .L67+16
	ldrh	r3, [r3]
	str	r3, [sp, #12]
	ldrh	r3, [r8, r1, lsl #2]
	ubfx	r3, r3, #0, #11
	beq	.L49
	ldrh	r4, [sp, #12]
	smulbb	r2, r2, r4
	add	r3, r3, r2
	ldr	r2, [sp]
	uxtah	r3, r2, r3
	str	r3, [sp]
.L49:
	ldr	r3, [sp]
	cmp	r7, #0
	it	eq
	moveq	r3, #-1
	movs	r7, #0
	str	r7, [sp, #4]
	str	r3, [sp]
	subs	r3, r0, r5
	asrs	r2, r3, #1
	ldr	r3, .L67+20
	muls	r3, r2, r3
	ldr	r2, .L67
	ldrh	r2, [r2]
	uxth	r3, r3
	str	r2, [sp, #20]
	mov	r2, r0
.L55:
	ldr	r7, [sp, #4]
	adds	r7, r7, #1
	uxth	r7, r7
	mov	r4, r7
	str	r7, [sp, #4]
	ldr	r7, [sp, #20]
	cmp	r4, r7
	bhi	.L45
	cmp	r1, r3
	beq	.L45
	ldrh	r7, [r2, #4]
	ldr	r4, [r8, r3, lsl #2]
	ldrh	ip, [r8, r3, lsl #2]
	str	r7, [sp, #16]
	ldr	r7, [sp, #8]
	ubfx	fp, r4, #11, #8
	ldr	r4, [sp, #16]
	ubfx	ip, ip, #0, #11
	ldrh	r7, [r7, r3, lsl #1]
	muls	r7, r4, r7
	itt	ne
	ldrhne	r4, [sp, #12]
	smulbbne	fp, fp, r4
	ldr	r4, [sp, #16]
	itt	ne
	addne	fp, fp, ip
	uxtahne	r7, r7, fp
	cbz	r4, .L53
	ldr	r4, [sp]
	cmp	r4, r7
	bls	.L53
	ldrh	r7, [r2]
	movw	r4, #65535
	cmp	r7, r4
	bne	.L54
	strh	r3, [r6, #2]	@ movhi
	strh	r1, [r2]	@ movhi
.L45:
	add	sp, sp, #24
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r10, fp, pc}
.L54:
	movs	r3, #6
	mla	r2, r3, r7, r5
	mov	r3, r7
	b	.L55
.L53:
	ldrh	r4, [r2, #2]
	cmp	r0, r2
	strh	r4, [r6, #2]	@ movhi
	strh	r3, [r5, r10]	@ movhi
	bne	.L56
	strh	r1, [r0, #2]	@ movhi
	b	.L66
.L56:
	ldrh	r0, [r2, #2]
	movs	r3, #6
	muls	r3, r0, r3
	strh	r1, [r5, r3]	@ movhi
	strh	r1, [r2, #2]	@ movhi
	b	.L45
.L68:
	.align	2
.L67:
	.word	.LANCHOR8
	.word	.LANCHOR4
	.word	.LANCHOR11
	.word	.LANCHOR9
	.word	.LANCHOR10
	.word	-1431655765
	.size	_insert_data_list, .-_insert_data_list
	.section	.text._list_update_data_list,"ax",%progbits
	.align	1
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	_list_update_data_list, %function
_list_update_data_list:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	ldr	r3, .L79
	push	{r4, r5, r6, r7, r8, r10, fp, lr}
	mov	r6, r2
	mov	r7, r0
	mov	r4, r1
	ldr	r3, [r3]
	ldrh	r2, [r3, #16]
	cmp	r2, r1
	beq	.L69
	ldrh	r2, [r3, #48]
	cmp	r2, r1
	beq	.L69
	ldrh	r3, [r3, #80]
	cmp	r3, r1
	beq	.L69
	ldr	r3, .L79+4
	movs	r5, #6
	muls	r5, r1, r5
	ldr	r2, [r0]
	ldr	fp, [r3]
	mov	r8, r3
	add	r10, fp, r5
	cmp	r10, r2
	beq	.L69
	ldrh	r3, [r10, #2]
	movw	r2, #65535
	cmp	r3, r2
	bne	.L73
	ldrh	r2, [fp, r5]
	cmp	r2, r3
	bne	.L73
	movw	r2, #273
	ldr	r1, .L79+8
	ldr	r0, .L79+12
	bl	printf
.L73:
	ldrh	r3, [r10, #2]
	movw	r2, #65535
	cmp	r3, r2
	bne	.L74
	ldrh	r2, [fp, r5]
	cmp	r2, r3
	beq	.L69
.L74:
	ldr	r2, .L79+16
	ldr	r0, [r2]
	ldrh	r2, [r10, #4]
	ldrh	r1, [r0, r4, lsl #1]
	cbz	r2, .L77
	muls	r2, r1, r2
.L75:
	movs	r1, #6
	muls	r1, r3, r1
	ldr	r3, .L79+20
	asrs	r5, r1, #1
	muls	r3, r5, r3
	ldrh	r5, [r0, r3, lsl #1]
	ldr	r0, [r8]
	add	r1, r1, r0
	ldrh	r3, [r1, #4]
	cbz	r3, .L78
	muls	r3, r5, r3
.L76:
	cmp	r2, r3
	bcs	.L69
	mov	r2, r6
	mov	r1, r4
	mov	r0, r7
	bl	_list_remove_node
	mov	r2, r6
	mov	r1, r4
	mov	r0, r7
	pop	{r4, r5, r6, r7, r8, r10, fp, lr}
	b	_insert_data_list
.L77:
	mov	r2, #-1
	b	.L75
.L78:
	mov	r3, #-1
	b	.L76
.L69:
	pop	{r4, r5, r6, r7, r8, r10, fp, pc}
.L80:
	.align	2
.L79:
	.word	.LANCHOR12
	.word	.LANCHOR4
	.word	.LANCHOR13
	.word	.LC0
	.word	.LANCHOR11
	.word	-1431655765
	.size	_list_update_data_list, .-_list_update_data_list
	.section	.text.nandc_de_cs.constprop.32,"ax",%progbits
	.align	1
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	nandc_de_cs.constprop.32, %function
nandc_de_cs.constprop.32:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	ldr	r3, .L82
	ldr	r2, [r3]
	ldr	r3, [r2]
	bfc	r3, #0, #8
	bfc	r3, #17, #1
	str	r3, [r2]
	bx	lr
.L83:
	.align	2
.L82:
	.word	.LANCHOR7
	.size	nandc_de_cs.constprop.32, .-nandc_de_cs.constprop.32
	.section	.text.flash_read_status,"ax",%progbits
	.align	1
	.global	flash_read_status
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	flash_read_status, %function
flash_read_status:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	movs	r3, #112
	push	{r4, lr}
	mov	r4, r0
	str	r3, [r0, #8]
	movs	r0, #1
	bl	udelay
	ldr	r0, [r4]
	uxtb	r0, r0
	pop	{r4, pc}
	.size	flash_read_status, .-flash_read_status
	.section	.text.toshiba_set_rr_para,"ax",%progbits
	.align	1
	.global	toshiba_set_rr_para
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	toshiba_set_rr_para, %function
toshiba_set_rr_para:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r3, r4, r5, r6, r7, r8, r10, lr}
	add	r7, r1, r1, lsl #2
	ldr	r10, .L93+12
	mov	r5, r0
	mov	r6, r1
	movs	r4, #0
	ldr	r8, .L93+16
.L86:
	ldrb	r3, [r10]	@ zero_extendqisi2
	cmp	r4, r3
	bcc	.L90
	pop	{r3, r4, r5, r6, r7, r8, r10, pc}
.L90:
	movs	r3, #85
	movs	r0, #1
	str	r3, [r5, #8]
	ldrsb	r3, [r4, r8]
	str	r3, [r5, #4]
	bl	udelay
	ldr	r3, .L93
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, #34
	bne	.L87
	adds	r3, r4, r7
	add	r3, r3, r8
.L92:
	ldrsb	r3, [r3, #5]
.L91:
	str	r3, [r5]
	adds	r4, r4, #1
	b	.L86
.L87:
	cmp	r3, #35
	bne	.L89
	ldr	r3, .L93+4
	adds	r2, r4, r7
	add	r3, r3, r2
	b	.L92
.L89:
	ldr	r3, .L93+8
	ldrsb	r3, [r3, r6]
	b	.L91
.L94:
	.align	2
.L93:
	.word	.LANCHOR15
	.word	.LANCHOR16
	.word	.LANCHOR17
	.word	.LANCHOR18
	.word	.LANCHOR14
	.size	toshiba_set_rr_para, .-toshiba_set_rr_para
	.section	.text.hynix_reconfig_rr_para,"ax",%progbits
	.align	1
	.global	hynix_reconfig_rr_para
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	hynix_reconfig_rr_para, %function
hynix_reconfig_rr_para:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r3, r4, r5, lr}
	mov	r4, r0
	ldr	r3, .L100
	ldrb	r3, [r3]	@ zero_extendqisi2
	subs	r3, r3, #1
	cmp	r3, #7
	bhi	.L95
	ldr	r5, .L100+4
	ldr	r3, [r5]
	add	r3, r3, r0
	ldrb	r3, [r3, #120]	@ zero_extendqisi2
	cbz	r3, .L95
	movs	r1, #0
	bl	hynix_set_rr_para
	ldr	r0, [r5]
	movs	r3, #0
	add	r0, r0, r4
	strb	r3, [r0, #120]
.L95:
	pop	{r3, r4, r5, pc}
.L101:
	.align	2
.L100:
	.word	.LANCHOR15
	.word	.LANCHOR6
	.size	hynix_reconfig_rr_para, .-hynix_reconfig_rr_para
	.section	.text.nand_flash_print_info,"ax",%progbits
	.align	1
	.global	nand_flash_print_info
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	nand_flash_print_info, %function
nand_flash_print_info:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, lr}
	sub	sp, sp, #20
	ldr	r4, .L220
	ldr	r3, [r4]
	lsls	r5, r3, #19
	bpl	.L103
	ldr	r1, .L220+4
	ldr	r0, .L220+8
	bl	printf
.L103:
	ldr	r3, [r4]
	lsls	r0, r3, #19
	bpl	.L104
	ldr	r3, .L220+12
	ldr	r0, [r3]
	ldrb	r5, [r0, #6]	@ zero_extendqisi2
	ldrb	r3, [r0, #3]	@ zero_extendqisi2
	ldrb	r2, [r0, #2]	@ zero_extendqisi2
	ldrb	r1, [r0, #1]	@ zero_extendqisi2
	str	r5, [sp, #8]
	ldrb	r5, [r0, #5]	@ zero_extendqisi2
	str	r5, [sp, #4]
	ldrb	r0, [r0, #4]	@ zero_extendqisi2
	str	r0, [sp]
	ldr	r0, .L220+16
	bl	printf
.L104:
	ldr	r3, [r4]
	lsls	r1, r3, #19
	bpl	.L105
	ldr	r3, .L220+12
	ldr	r0, .L220+20
	ldr	r3, [r3]
	ldrb	r1, [r3, #8]	@ zero_extendqisi2
	bl	printf
.L105:
	ldr	r3, [r4]
	lsls	r2, r3, #19
	bpl	.L106
	ldr	r3, .L220+12
	ldr	r0, .L220+24
	ldr	r3, [r3]
	ldrb	r1, [r3, #9]	@ zero_extendqisi2
	bl	printf
.L106:
	ldr	r3, [r4]
	lsls	r3, r3, #19
	bpl	.L107
	ldr	r3, .L220+12
	ldr	r0, .L220+28
	ldr	r3, [r3]
	ldrh	r1, [r3, #10]
	bl	printf
.L107:
	ldr	r3, [r4]
	lsls	r5, r3, #19
	bpl	.L108
	ldr	r3, .L220+12
	ldr	r0, .L220+32
	ldr	r3, [r3]
	ldrb	r1, [r3, #12]	@ zero_extendqisi2
	bl	printf
.L108:
	ldr	r3, [r4]
	lsls	r0, r3, #19
	bpl	.L109
	ldr	r3, .L220+12
	ldr	r0, .L220+36
	ldr	r3, [r3]
	ldrb	r1, [r3, #13]	@ zero_extendqisi2
	bl	printf
.L109:
	ldr	r3, [r4]
	lsls	r1, r3, #19
	bpl	.L110
	ldr	r3, .L220+12
	ldr	r0, .L220+40
	ldr	r3, [r3]
	ldrh	r1, [r3, #14]
	bl	printf
.L110:
	ldr	r3, [r4]
	lsls	r2, r3, #19
	bpl	.L111
	ldr	r3, .L220+12
	ldr	r0, .L220+44
	ldr	r3, [r3]
	ldrb	r1, [r3, #23]	@ zero_extendqisi2
	bl	printf
.L111:
	ldr	r3, [r4]
	lsls	r3, r3, #19
	bpl	.L112
	ldr	r3, .L220+12
	ldr	r0, .L220+48
	ldr	r3, [r3]
	ldrb	r1, [r3, #18]	@ zero_extendqisi2
	bl	printf
.L112:
	ldr	r3, [r4]
	lsls	r5, r3, #19
	bpl	.L113
	ldr	r3, .L220+12
	ldr	r0, .L220+52
	ldr	r3, [r3]
	ldrb	r1, [r3, #19]	@ zero_extendqisi2
	bl	printf
.L113:
	ldr	r3, [r4]
	lsls	r0, r3, #19
	bpl	.L114
	ldr	r3, .L220+12
	ldr	r0, .L220+56
	ldr	r3, [r3]
	ldrb	r1, [r3, #20]	@ zero_extendqisi2
	bl	printf
.L114:
	ldr	r3, [r4]
	lsls	r1, r3, #19
	bpl	.L115
	ldr	r3, .L220+60
	ldr	r0, .L220+64
	ldrb	r1, [r3]	@ zero_extendqisi2
	bl	printf
.L115:
	ldr	r3, [r4]
	lsls	r2, r3, #19
	bpl	.L116
	ldr	r3, .L220+12
	ldr	r0, .L220+68
	ldr	r3, [r3]
	ldrb	r1, [r3, #22]	@ zero_extendqisi2
	bl	printf
.L116:
	ldr	r3, [r4]
	lsls	r3, r3, #19
	bpl	.L117
	ldr	r3, .L220+72
	ldr	r0, .L220+76
	ldrb	r1, [r3]	@ zero_extendqisi2
	bl	printf
.L117:
	ldr	r3, [r4]
	lsls	r5, r3, #19
	bpl	.L118
	ldr	r3, .L220+12
	ldr	r0, .L220+80
	ldr	r3, [r3]
	ldrb	r1, [r3, #16]	@ zero_extendqisi2
	and	r1, r1, #1
	bl	printf
.L118:
	ldr	r3, [r4]
	lsls	r0, r3, #19
	bpl	.L119
	ldr	r3, .L220+12
	ldr	r0, .L220+84
	ldr	r3, [r3]
	ldrh	r1, [r3, #16]
	ubfx	r1, r1, #1, #1
	bl	printf
.L119:
	ldr	r3, [r4]
	lsls	r1, r3, #19
	bpl	.L120
	ldr	r3, .L220+12
	ldr	r0, .L220+88
	ldr	r3, [r3]
	ldrh	r1, [r3, #16]
	ubfx	r1, r1, #2, #1
	bl	printf
.L120:
	ldr	r3, [r4]
	lsls	r2, r3, #19
	bpl	.L121
	ldr	r3, .L220+12
	ldr	r0, .L220+92
	ldr	r3, [r3]
	ldrh	r1, [r3, #16]
	ubfx	r1, r1, #3, #1
	bl	printf
.L121:
	ldr	r3, [r4]
	lsls	r3, r3, #19
	bpl	.L122
	ldr	r3, .L220+12
	ldr	r0, .L220+96
	ldr	r3, [r3]
	ldrh	r1, [r3, #16]
	ubfx	r1, r1, #4, #1
	bl	printf
.L122:
	ldr	r3, [r4]
	lsls	r5, r3, #19
	bpl	.L123
	ldr	r3, .L220+12
	ldr	r0, .L220+100
	ldr	r3, [r3]
	ldrh	r1, [r3, #16]
	ubfx	r1, r1, #5, #1
	bl	printf
.L123:
	ldr	r3, [r4]
	lsls	r0, r3, #19
	bpl	.L124
	ldr	r3, .L220+12
	ldr	r0, .L220+104
	ldr	r3, [r3]
	ldrh	r1, [r3, #16]
	ubfx	r1, r1, #6, #1
	bl	printf
.L124:
	ldr	r3, [r4]
	lsls	r1, r3, #19
	bpl	.L125
	ldr	r3, .L220+12
	ldr	r0, .L220+108
	ldr	r3, [r3]
	ldrh	r1, [r3, #16]
	ubfx	r1, r1, #7, #1
	bl	printf
.L125:
	ldr	r3, [r4]
	lsls	r2, r3, #19
	bpl	.L126
	ldr	r3, .L220+12
	ldr	r0, .L220+112
	ldr	r3, [r3]
	ldrh	r1, [r3, #16]
	ubfx	r1, r1, #8, #1
	bl	printf
.L126:
	ldr	r3, [r4]
	lsls	r3, r3, #19
	bpl	.L127
	ldr	r3, .L220+12
	ldr	r0, .L220+116
	ldr	r3, [r3]
	ldrh	r1, [r3, #16]
	ubfx	r1, r1, #9, #1
	bl	printf
.L127:
	ldr	r3, [r4]
	lsls	r5, r3, #19
	bpl	.L128
	ldr	r3, .L220+12
	ldr	r0, .L220+120
	ldr	r3, [r3]
	ldrh	r1, [r3, #16]
	ubfx	r1, r1, #10, #1
	bl	printf
.L128:
	ldr	r3, [r4]
	lsls	r0, r3, #19
	bpl	.L129
	ldr	r3, .L220+124
	ldr	r0, .L220+128
	ldrb	r2, [r3]	@ zero_extendqisi2
	ldr	r3, .L220+132
	ldrb	r1, [r3]	@ zero_extendqisi2
	bl	printf
.L129:
	ldr	r3, [r4]
	lsls	r1, r3, #19
	bpl	.L130
	ldr	r3, .L220+136
	ldr	r0, .L220+140
	ldrb	r2, [r3, #11]	@ zero_extendqisi2
	ldrb	r1, [r3, #10]	@ zero_extendqisi2
	bl	printf
.L130:
	ldr	r3, [r4]
	lsls	r2, r3, #19
	bpl	.L131
	ldr	r3, .L220+136
	ldr	r0, .L220+144
	ldrb	r2, [r3, #9]	@ zero_extendqisi2
	ldrb	r1, [r3, #8]	@ zero_extendqisi2
	bl	printf
.L131:
	ldr	r3, [r4]
	lsls	r3, r3, #19
	bpl	.L102
	ldr	r3, .L220+148
	b	.L221
.L222:
	.align	2
.L220:
	.word	.LANCHOR19
	.word	.LANCHOR20
	.word	.LC1
	.word	.LANCHOR21
	.word	.LC2
	.word	.LC3
	.word	.LC4
	.word	.LC5
	.word	.LC6
	.word	.LC7
	.word	.LC8
	.word	.LC9
	.word	.LC10
	.word	.LC11
	.word	.LC12
	.word	.LANCHOR22
	.word	.LC13
	.word	.LC14
	.word	.LANCHOR23
	.word	.LC15
	.word	.LC16
	.word	.LC17
	.word	.LC18
	.word	.LC19
	.word	.LC20
	.word	.LC21
	.word	.LC22
	.word	.LC23
	.word	.LC24
	.word	.LC25
	.word	.LC26
	.word	.LANCHOR24
	.word	.LC27
	.word	.LANCHOR0
	.word	.LANCHOR25
	.word	.LC28
	.word	.LC29
	.word	.LANCHOR26
.L221:
	ldr	r0, .L223
	ldrb	r1, [r3]	@ zero_extendqisi2
	add	sp, sp, #20
	@ sp needed
	pop	{r4, r5, lr}
	b	printf
.L102:
	add	sp, sp, #20
	@ sp needed
	pop	{r4, r5, pc}
.L224:
	.align	2
.L223:
	.word	.LC30
	.size	nand_flash_print_info, .-nand_flash_print_info
	.section	.text.timer_delay_ns,"ax",%progbits
	.align	1
	.global	timer_delay_ns
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	timer_delay_ns, %function
timer_delay_ns:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	ldr	r3, .L226
	addw	r0, r0, #999
	umull	r0, r1, r0, r3
	lsrs	r0, r1, #6
	b	udelay
.L227:
	.align	2
.L226:
	.word	274877907
	.size	timer_delay_ns, .-timer_delay_ns
	.section	.text.nandc_set_ddr_para,"ax",%progbits
	.align	1
	.global	nandc_set_ddr_para
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	nandc_set_ddr_para, %function
nandc_set_ddr_para:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	ldr	r3, .L231
	ldr	r2, .L231+4
	ldrb	r3, [r3]	@ zero_extendqisi2
	ldr	r2, [r2]
	cmp	r3, #9
	lsl	r3, r0, #16
	lsl	r0, r0, #8
	orr	r3, r3, r0
	orr	r3, r3, #3
	ite	eq
	streq	r3, [r2, #80]
	strne	r3, [r2, #304]
	bx	lr
.L232:
	.align	2
.L231:
	.word	.LANCHOR27
	.word	.LANCHOR7
	.size	nandc_set_ddr_para, .-nandc_set_ddr_para
	.section	.text.nandc_get_ddr_para,"ax",%progbits
	.align	1
	.global	nandc_get_ddr_para
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	nandc_get_ddr_para, %function
nandc_get_ddr_para:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	ldr	r3, .L237
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, #9
	ldr	r3, .L237+4
	ldr	r3, [r3]
	ite	eq
	ldreq	r0, [r3, #80]
	ldrne	r0, [r3, #304]
	ubfx	r0, r0, #8, #8
	bx	lr
.L238:
	.align	2
.L237:
	.word	.LANCHOR27
	.word	.LANCHOR7
	.size	nandc_get_ddr_para, .-nandc_get_ddr_para
	.section	.text.nandc_set_if_mode,"ax",%progbits
	.align	1
	.global	nandc_set_if_mode
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	nandc_set_if_mode, %function
nandc_set_if_mode:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	ldr	r3, .L247
	ands	r1, r0, #6
	ldr	r3, [r3]
	ldr	r2, [r3]
	beq	.L240
	lsls	r1, r0, #29
	ldr	r1, .L247+4
	orr	r2, r2, #24576
	bfc	r2, #15, #1
	ldrb	r1, [r1]	@ zero_extendqisi2
	orr	r2, r2, #196608
	it	mi
	orrmi	r2, r2, #32768
	cmp	r1, #9
	ldr	r1, .L247+8
	bne	.L242
	movw	r0, #8321
	str	r0, [r3, #8]
	str	r1, [r3, #80]
	movs	r1, #38
	str	r1, [r3, #84]
	movs	r1, #39
	str	r1, [r3, #84]
.L243:
	str	r2, [r3]
	bx	lr
.L242:
	movw	r0, #8322
	str	r0, [r3, #344]
	str	r1, [r3, #304]
	movs	r1, #38
	str	r1, [r3, #308]
	movs	r1, #39
	str	r1, [r3, #308]
	b	.L243
.L240:
	bfi	r2, r1, #13, #1
	b	.L243
.L248:
	.align	2
.L247:
	.word	.LANCHOR7
	.word	.LANCHOR27
	.word	1052675
	.size	nandc_set_if_mode, .-nandc_set_if_mode
	.section	.text.nandc_cs,"ax",%progbits
	.align	1
	.global	nandc_cs
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	nandc_cs, %function
nandc_cs:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	ldr	r3, .L250
	movs	r2, #1
	lsl	r0, r2, r0
	ldr	r1, [r3]
	ldr	r3, [r1]
	bfi	r3, r0, #0, #8
	str	r3, [r1]
	bx	lr
.L251:
	.align	2
.L250:
	.word	.LANCHOR7
	.size	nandc_cs, .-nandc_cs
	.section	.text.flash_wait_device_ready_raw,"ax",%progbits
	.align	1
	.global	flash_wait_device_ready_raw
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	flash_wait_device_ready_raw, %function
flash_wait_device_ready_raw:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	ldr	r3, .L262
	push	{r4, r5, r6, r7, r8, r10, fp, lr}
	mov	r4, r0
	mov	r5, r1
	mov	fp, r2
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, r0
	bhi	.L253
	mov	r2, #812
	ldr	r1, .L262+4
	ldr	r0, .L262+8
	bl	printf
.L253:
	ldr	r3, .L262+12
	lsrs	r7, r5, #8
	lsr	r8, r5, #16
	lsr	r10, r5, #24
	ldrb	r6, [r3, r4]	@ zero_extendqisi2
	ldr	r3, .L262+16
	ldr	r4, [r3]
	add	r4, r4, r6, lsl #8
.L259:
	mov	r0, r6
	bl	nandc_cs
	movs	r3, #120
	str	r3, [r4, #2056]
	uxtb	r3, r5
	str	r3, [r4, #2052]
	ldr	r3, .L262+20
	str	r7, [r4, #2052]
	str	r8, [r4, #2052]
	ldrb	r3, [r3]	@ zero_extendqisi2
	cbz	r3, .L254
	str	r10, [r4, #2052]
.L254:
	movs	r0, #1
	bl	udelay
	ldr	r0, [r4, #2048]
	uxtb	r0, r0
	bl	nandc_de_cs.constprop.32
	bics	r3, fp, r0
	bne	.L259
	cmp	r0, #255
	beq	.L259
	pop	{r4, r5, r6, r7, r8, r10, fp, pc}
.L263:
	.align	2
.L262:
	.word	.LANCHOR23
	.word	.LANCHOR28
	.word	.LC0
	.word	.LANCHOR29
	.word	.LANCHOR7
	.word	.LANCHOR30
	.size	flash_wait_device_ready_raw, .-flash_wait_device_ready_raw
	.section	.text.flash_wait_device_ready,"ax",%progbits
	.align	1
	.global	flash_wait_device_ready
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	flash_wait_device_ready, %function
flash_wait_device_ready:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r3, r4, r5, r6, r7, r8, r10, lr}
	tst	r0, #50331648
	ldr	r3, .L274
	mov	r7, r1
	ldrb	r5, [r3]	@ zero_extendqisi2
	mov	r3, #1
	rsb	r6, r5, #24
	lsl	r5, r3, r5
	lsl	r4, r3, r6
	asr	r6, r0, r6
	add	r5, r5, #-1
	add	r4, r4, #-1
	and	r5, r5, r6
	and	r4, r4, r0
	uxtb	r5, r5
	bne	.L265
	ldr	r3, .L274+4
	ldr	r10, .L274+16
	ldrb	r3, [r3]	@ zero_extendqisi2
	cbz	r3, .L266
	ldrb	r3, [r10]	@ zero_extendqisi2
	cbz	r3, .L265
.L266:
	ldr	r3, .L274+8
	mov	r0, r4
	ldrh	r6, [r3]
	mov	r1, r6
	bl	__aeabi_uidiv
	mov	r1, r6
	mul	r8, r6, r0
	mov	r0, r4
	bl	__aeabi_uidivmod
	ldrb	r3, [r10]	@ zero_extendqisi2
	cbz	r3, .L267
	add	r4, r8, r1, lsl #1
.L265:
	mov	r2, r7
	mov	r1, r4
	mov	r0, r5
	pop	{r3, r4, r5, r6, r7, r8, r10, lr}
	b	flash_wait_device_ready_raw
.L267:
	ldr	r3, .L274+12
	ldrh	r4, [r3, r1, lsl #1]
	add	r4, r4, r8
	b	.L265
.L275:
	.align	2
.L274:
	.word	.LANCHOR31
	.word	.LANCHOR0
	.word	.LANCHOR2
	.word	.LANCHOR3
	.word	.LANCHOR1
	.size	flash_wait_device_ready, .-flash_wait_device_ready
	.section	.text.nandc_de_cs,"ax",%progbits
	.align	1
	.global	nandc_de_cs
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	nandc_de_cs, %function
nandc_de_cs:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	ldr	r3, .L277
	ldr	r2, [r3]
	ldr	r3, [r2]
	bfc	r3, #0, #8
	bfc	r3, #17, #1
	str	r3, [r2]
	bx	lr
.L278:
	.align	2
.L277:
	.word	.LANCHOR7
	.size	nandc_de_cs, .-nandc_de_cs
	.section	.text.nandc_wait_flash_ready_no_delay,"ax",%progbits
	.align	1
	.global	nandc_wait_flash_ready_no_delay
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	nandc_wait_flash_ready_no_delay, %function
nandc_wait_flash_ready_no_delay:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r0, r1, r2, r4, r5, lr}
	ldr	r4, .L284
	ldr	r5, .L284+4
.L281:
	ldr	r3, [r5]
	ldr	r3, [r3]
	str	r3, [sp, #4]
	ldr	r3, [sp, #4]
	lsls	r3, r3, #22
	bmi	.L282
	movs	r0, #1
	bl	udelay
	subs	r4, r4, #1
	bne	.L281
	mov	r0, #-1
.L279:
	add	sp, sp, #12
	@ sp needed
	pop	{r4, r5, pc}
.L282:
	movs	r0, #0
	b	.L279
.L285:
	.align	2
.L284:
	.word	100000
	.word	.LANCHOR7
	.size	nandc_wait_flash_ready_no_delay, .-nandc_wait_flash_ready_no_delay
	.section	.text.zftl_flash_enter_slc_mode,"ax",%progbits
	.align	1
	.global	zftl_flash_enter_slc_mode
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	zftl_flash_enter_slc_mode, %function
zftl_flash_enter_slc_mode:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r3, r4, r5, r6, r7, lr}
	mov	r7, r0
	ldr	r3, .L305
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L286
	ldr	r2, .L305+4
	cmp	r3, #1
	ldr	r4, [r2]
	bne	.L289
	ldr	r3, .L305+8
	ldrb	r3, [r3, #29]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L286
.L304:
	add	r4, r4, r7, lsl #8
	str	r3, [r4, #2056]
	pop	{r3, r4, r5, r6, r7, pc}
.L289:
	cmp	r3, #2
	bne	.L291
	ldr	r3, .L305+12
	ldrb	r2, [r3, r0]	@ zero_extendqisi2
	cbz	r2, .L286
	ldr	r5, .L305+8
	movs	r2, #0
	strb	r2, [r3, r0]
	ldrb	r3, [r5, #29]	@ zero_extendqisi2
	cbz	r3, .L286
	bl	nandc_wait_flash_ready_no_delay
	ldrb	r3, [r5, #29]	@ zero_extendqisi2
	b	.L304
.L291:
	cmp	r3, #3
	bne	.L286
	ldr	r6, .L305+12
	ldrb	r3, [r6, r0]	@ zero_extendqisi2
	cbz	r3, .L286
	add	r4, r4, r7, lsl #8
	movs	r5, #0
	bl	nandc_wait_flash_ready_no_delay
	movs	r3, #239
	strb	r5, [r6, r7]
	str	r3, [r4, #2056]
	movs	r3, #145
	str	r3, [r4, #2052]
	movs	r6, #1
	movs	r0, #1
	bl	udelay
	str	r5, [r4, #2048]
	mov	r0, r6
	str	r6, [r4, #2048]
	str	r5, [r4, #2048]
	str	r5, [r4, #2048]
	bl	udelay
	bl	nandc_wait_flash_ready_no_delay
	movs	r3, #218
	mov	r0, r6
	str	r3, [r4, #2056]
	pop	{r3, r4, r5, r6, r7, lr}
	b	udelay
.L286:
	pop	{r3, r4, r5, r6, r7, pc}
.L306:
	.align	2
.L305:
	.word	.LANCHOR0
	.word	.LANCHOR7
	.word	.LANCHOR32
	.word	.LANCHOR33
	.size	zftl_flash_enter_slc_mode, .-zftl_flash_enter_slc_mode
	.section	.text.zftl_flash_exit_slc_mode,"ax",%progbits
	.align	1
	.global	zftl_flash_exit_slc_mode
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	zftl_flash_exit_slc_mode, %function
zftl_flash_exit_slc_mode:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r3, r4, r5, r6, r7, r8, r10, lr}
	mov	r4, r0
	ldr	r3, .L328
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L307
	ldr	r2, .L328+4
	cmp	r3, #1
	ldr	r6, [r2]
	bne	.L310
	ldr	r3, .L328+8
	ldrb	r3, [r3, #30]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L307
.L327:
	add	r4, r6, r4, lsl #8
	str	r3, [r4, #2056]
	pop	{r3, r4, r5, r6, r7, r8, r10, pc}
.L310:
	cmp	r3, #2
	bne	.L312
	ldr	r2, .L328+12
	ldrb	r3, [r2, r0]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L307
	ldr	r5, .L328+8
	ldrb	r3, [r5, #12]	@ zero_extendqisi2
	cmp	r3, #2
	it	ne
	movne	r3, #4
	strb	r3, [r2, r0]
	ldrb	r3, [r5, #30]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L307
	bl	nandc_wait_flash_ready_no_delay
	ldrb	r3, [r5, #30]	@ zero_extendqisi2
	b	.L327
.L312:
	cmp	r3, #3
	bne	.L307
	ldr	r7, .L328+12
	ldrb	r3, [r7, r0]	@ zero_extendqisi2
	cbnz	r3, .L307
	ldr	r10, .L328+8
	lsl	r8, r4, #8
	bl	nandc_wait_flash_ready_no_delay
	ldrb	r3, [r10, #12]	@ zero_extendqisi2
	add	r5, r6, r8
	movs	r0, #1
	add	r6, r6, r8
	cmp	r3, #2
	it	ne
	movne	r3, #4
	strb	r3, [r7, r4]
	movs	r3, #239
	str	r3, [r5, #2056]
	movs	r3, #145
	str	r3, [r5, #2052]
	bl	udelay
	ldrb	r3, [r10, #7]	@ zero_extendqisi2
	movs	r0, #1
	cmp	r3, #9
	mov	r3, #1
	itet	ne
	ldrbne	r2, [r7, r4]	@ zero_extendqisi2
	streq	r3, [r5, #2048]
	strne	r2, [r5, #2048]
	str	r3, [r5, #2048]
	movs	r3, #0
	str	r3, [r5, #2048]
	str	r3, [r5, #2048]
	bl	udelay
	bl	nandc_wait_flash_ready_no_delay
	movs	r3, #223
	movs	r0, #1
	str	r3, [r6, #2056]
	pop	{r3, r4, r5, r6, r7, r8, r10, lr}
	b	udelay
.L307:
	pop	{r3, r4, r5, r6, r7, r8, r10, pc}
.L329:
	.align	2
.L328:
	.word	.LANCHOR0
	.word	.LANCHOR7
	.word	.LANCHOR32
	.word	.LANCHOR33
	.size	zftl_flash_exit_slc_mode, .-zftl_flash_exit_slc_mode
	.section	.text.flash_start_page_read,"ax",%progbits
	.align	1
	.global	flash_start_page_read
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	flash_start_page_read, %function
flash_start_page_read:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	ldr	r3, .L344
	push	{r4, r5, r6, r7, r8, r10, fp, lr}
	mov	r5, r0
	ldr	r4, .L344+4
	mov	fp, r1
	ldrb	r2, [r3]	@ zero_extendqisi2
	movs	r3, #1
	rsb	r7, r2, #24
	lsls	r3, r3, r2
	lsr	r2, r1, r7
	subs	r3, r3, #1
	ands	r3, r3, r2
	ldrb	r2, [r4]	@ zero_extendqisi2
	uxtb	r8, r3
	cmp	r2, r8
	bhi	.L331
	movw	r2, #1013
	ldr	r1, .L344+8
	ldr	r0, .L344+12
	bl	printf
.L331:
	ldrb	r3, [r4]	@ zero_extendqisi2
	cmp	r3, r8
	bls	.L330
	ldr	r3, .L344+16
	movs	r4, #1
	lsls	r4, r4, r7
	ldr	r6, .L344+20
	ldrb	r10, [r3, r8]	@ zero_extendqisi2
	subs	r4, r4, #1
	ldr	r3, .L344+24
	and	r4, r4, fp
	ubfx	fp, fp, #24, #2
	mov	r0, r10
	ldr	r7, [r3]
	lsl	r8, r10, #8
	bl	nandc_cs
	cmp	fp, #0
	bne	.L333
	mov	r0, r4
	bl	slc_phy_page_address_calc
	ldr	r3, .L344+28
	mov	r4, r0
	ldrb	r3, [r3]	@ zero_extendqisi2
	cbz	r3, .L334
	mov	r0, r10
	bl	zftl_flash_enter_slc_mode
.L334:
	ldr	r3, [r6]
	ldrb	r2, [r3, #7]	@ zero_extendqisi2
	cmp	r2, #1
	bne	.L336
	ldrb	r3, [r3, #12]	@ zero_extendqisi2
	cmp	r3, #2
	ittt	eq
	addeq	r3, r7, r8
	moveq	r2, #38
	streq	r2, [r3, #2056]
.L336:
	add	r3, r7, r8
	movs	r2, #0
	str	r2, [r3, #2056]
	str	r2, [r3, #2052]
	str	r2, [r3, #2052]
	uxtb	r2, r4
	str	r2, [r3, #2052]
	lsrs	r2, r4, #8
	str	r2, [r3, #2052]
	lsrs	r2, r4, #16
	str	r2, [r3, #2052]
	ldr	r2, .L344+32
	ldrb	r2, [r2]	@ zero_extendqisi2
	cbz	r2, .L337
	lsrs	r4, r4, #24
	str	r4, [r3, #2052]
.L337:
	add	r3, r7, r8
	str	r5, [r3, #2056]
.L330:
	pop	{r4, r5, r6, r7, r8, r10, fp, pc}
.L333:
	ldr	r3, [r6]
	ldrb	r3, [r3, #12]	@ zero_extendqisi2
	cmp	r3, #3
	bne	.L335
	ldr	r3, .L344+36
	ldrb	r3, [r3]	@ zero_extendqisi2
	cbnz	r3, .L335
	ldr	r3, .L344+40
	ldrb	r3, [r3]	@ zero_extendqisi2
	cbnz	r3, .L335
	add	r3, r7, r8
	str	fp, [r3, #2056]
	b	.L334
.L335:
	mov	r0, r10
	bl	zftl_flash_exit_slc_mode
	b	.L334
.L345:
	.align	2
.L344:
	.word	.LANCHOR31
	.word	.LANCHOR23
	.word	.LANCHOR34
	.word	.LC0
	.word	.LANCHOR29
	.word	.LANCHOR21
	.word	.LANCHOR7
	.word	.LANCHOR0
	.word	.LANCHOR30
	.word	.LANCHOR35
	.word	.LANCHOR36
	.size	flash_start_page_read, .-flash_start_page_read
	.section	.text.nandc_wait_flash_ready,"ax",%progbits
	.align	1
	.global	nandc_wait_flash_ready
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	nandc_wait_flash_ready, %function
nandc_wait_flash_ready:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r0, r1, r2, r4, r5, lr}
	movs	r0, #1
	ldr	r4, .L351
	ldr	r5, .L351+4
	bl	udelay
.L348:
	ldr	r3, [r5]
	ldr	r3, [r3]
	str	r3, [sp, #4]
	ldr	r3, [sp, #4]
	lsls	r3, r3, #22
	bmi	.L349
	movs	r0, #1
	bl	udelay
	subs	r4, r4, #1
	bne	.L348
	mov	r0, #-1
.L346:
	add	sp, sp, #12
	@ sp needed
	pop	{r4, r5, pc}
.L349:
	movs	r0, #0
	b	.L346
.L352:
	.align	2
.L351:
	.word	100000
	.word	.LANCHOR7
	.size	nandc_wait_flash_ready, .-nandc_wait_flash_ready
	.section	.text.sandisk_set_rr_para,"ax",%progbits
	.align	1
	.global	sandisk_set_rr_para
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	sandisk_set_rr_para, %function
sandisk_set_rr_para:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r3, r4, r5, r6, r7, lr}
	movs	r3, #239
	str	r3, [r0, #8]
	movs	r3, #17
	mov	r5, r0
	mov	r4, r1
	str	r3, [r0, #4]
	movs	r0, #1
	bl	udelay
	ldr	r3, .L359
	add	r4, r4, r4, lsl #2
	ldr	r6, .L359+4
	movs	r2, #0
	ldr	r7, .L359+8
	ldrb	r1, [r3]	@ zero_extendqisi2
	ldr	r3, .L359+12
	ldrb	r0, [r3]	@ zero_extendqisi2
.L354:
	cmp	r2, r1
	bcc	.L357
	pop	{r3, r4, r5, r6, r7, lr}
	b	nandc_wait_flash_ready
.L357:
	adds	r3, r2, r4
	cmp	r0, #67
	ite	eq
	addeq	r3, r3, r7
	addne	r3, r3, r6
	ldrsb	r3, [r3, #5]
	adds	r2, r2, #1
	str	r3, [r5]
	b	.L354
.L360:
	.align	2
.L359:
	.word	.LANCHOR18
	.word	.LANCHOR16
	.word	.LANCHOR14
	.word	.LANCHOR15
	.size	sandisk_set_rr_para, .-sandisk_set_rr_para
	.section	.text.toshiba_3d_set_tlc_rr_para,"ax",%progbits
	.align	1
	.global	toshiba_3d_set_tlc_rr_para
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	toshiba_3d_set_tlc_rr_para, %function
toshiba_3d_set_tlc_rr_para:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r3, r4, r5, r6, r7, lr}
	movs	r6, #0
	movs	r7, #213
	mvn	r3, #118
	adds	r1, r1, #1
	mov	r4, r0
	str	r7, [r0, #8]
	rsb	r1, r1, r1, lsl #3
	str	r6, [r0, #4]
	str	r3, [r0, #4]
	ldr	r3, .L362
	adds	r5, r3, r1
	ldrsb	r3, [r3, r1]
	str	r3, [r0]
	ldrsb	r3, [r5, #1]
	str	r3, [r0]
	ldrsb	r3, [r5, #2]
	str	r3, [r0]
	ldrsb	r3, [r5, #3]
	str	r3, [r0]
	bl	nandc_wait_flash_ready
	mvn	r3, #117
	str	r7, [r4, #8]
	str	r6, [r4, #4]
	str	r3, [r4, #4]
	ldrsb	r3, [r5, #4]
	str	r3, [r4]
	ldrsb	r3, [r5, #5]
	str	r3, [r4]
	ldrsb	r3, [r5, #6]
	str	r3, [r4]
	str	r6, [r4]
	pop	{r3, r4, r5, r6, r7, lr}
	b	nandc_wait_flash_ready
.L363:
	.align	2
.L362:
	.word	.LANCHOR37
	.size	toshiba_3d_set_tlc_rr_para, .-toshiba_3d_set_tlc_rr_para
	.section	.text.toshiba_3d_set_slc_rr_para,"ax",%progbits
	.align	1
	.global	toshiba_3d_set_slc_rr_para
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	toshiba_3d_set_slc_rr_para, %function
toshiba_3d_set_slc_rr_para:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	movs	r3, #213
	mvn	r2, #116
	str	r3, [r0, #8]
	movs	r3, #0
	str	r3, [r0, #4]
	str	r2, [r0, #4]
	ldr	r2, .L365
	add	r1, r1, r2
	ldrsb	r2, [r1, #1]
	str	r2, [r0]
	str	r3, [r0]
	str	r3, [r0]
	str	r3, [r0]
	b	nandc_wait_flash_ready
.L366:
	.align	2
.L365:
	.word	.LANCHOR38
	.size	toshiba_3d_set_slc_rr_para, .-toshiba_3d_set_slc_rr_para
	.section	.text.toshiba_tlc_set_rr_para,"ax",%progbits
	.align	1
	.global	toshiba_tlc_set_rr_para
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	toshiba_tlc_set_rr_para, %function
toshiba_tlc_set_rr_para:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, lr}
	movs	r6, #239
	mov	r4, r0
	str	r6, [r0, #8]
	cbz	r2, .L368
	movs	r3, #18
	rsb	r1, r1, r1, lsl #3
	str	r3, [r0, #4]
	ldr	r3, .L370
	adds	r5, r3, r1
	ldrb	r3, [r3, r1]	@ zero_extendqisi2
	str	r3, [r0]
	ldrb	r3, [r5, #1]	@ zero_extendqisi2
	str	r3, [r0]
	ldrb	r3, [r5, #2]	@ zero_extendqisi2
	str	r3, [r0]
	ldrb	r3, [r5, #3]	@ zero_extendqisi2
	str	r3, [r0]
	bl	nandc_wait_flash_ready
	movs	r3, #19
	str	r6, [r4, #8]
	str	r3, [r4, #4]
	ldrb	r3, [r5, #4]	@ zero_extendqisi2
	str	r3, [r4]
	ldrb	r3, [r5, #5]	@ zero_extendqisi2
	str	r3, [r4]
	ldrb	r3, [r5, #6]	@ zero_extendqisi2
	str	r3, [r4]
	movs	r3, #0
	str	r3, [r4]
.L369:
	pop	{r4, r5, r6, lr}
	b	nandc_wait_flash_ready
.L368:
	movs	r3, #20
	str	r3, [r0, #4]
	ldr	r3, .L370+4
	ldrb	r3, [r3, r1]	@ zero_extendqisi2
	str	r3, [r0]
	str	r2, [r0]
	str	r2, [r0]
	str	r2, [r0]
	b	.L369
.L371:
	.align	2
.L370:
	.word	.LANCHOR39
	.word	.LANCHOR40
	.size	toshiba_tlc_set_rr_para, .-toshiba_tlc_set_rr_para
	.section	.text.ymtc_3d_set_tlc_rr_para,"ax",%progbits
	.align	1
	.global	ymtc_3d_set_tlc_rr_para
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	ymtc_3d_set_tlc_rr_para, %function
ymtc_3d_set_tlc_rr_para:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r3, r4, r5, r6, r7, lr}
	movs	r7, #239
	movs	r3, #160
	str	r7, [r0, #8]
	rsb	r1, r1, r1, lsl #3
	movs	r6, #0
	str	r3, [r0, #4]
	mov	r4, r0
	ldr	r3, .L373
	adds	r5, r3, r1
	ldrsb	r3, [r3, r1]
	str	r3, [r0]
	ldrsb	r3, [r5, #4]
	str	r3, [r0]
	str	r6, [r0]
	str	r6, [r0]
	bl	nandc_wait_flash_ready
	movs	r3, #161
	str	r7, [r4, #8]
	str	r3, [r4, #4]
	ldrsb	r3, [r5, #1]
	str	r3, [r4]
	ldrsb	r3, [r5, #3]
	str	r3, [r4]
	ldrsb	r3, [r5, #5]
	str	r3, [r4]
	str	r6, [r4]
	bl	nandc_wait_flash_ready
	movs	r3, #162
	str	r7, [r4, #8]
	str	r3, [r4, #4]
	ldrsb	r3, [r5, #2]
	str	r3, [r4]
	ldrsb	r3, [r5, #6]
	str	r3, [r4]
	str	r6, [r4]
	str	r6, [r4]
	pop	{r3, r4, r5, r6, r7, lr}
	b	nandc_wait_flash_ready
.L374:
	.align	2
.L373:
	.word	.LANCHOR41
	.size	ymtc_3d_set_tlc_rr_para, .-ymtc_3d_set_tlc_rr_para
	.section	.text.ymtc_3d_set_slc_rr_para,"ax",%progbits
	.align	1
	.global	ymtc_3d_set_slc_rr_para
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	ymtc_3d_set_slc_rr_para, %function
ymtc_3d_set_slc_rr_para:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	movs	r3, #239
	str	r3, [r0, #8]
	movs	r3, #163
	str	r3, [r0, #4]
	ldr	r3, .L376
	ldrsb	r3, [r3, r1]
	str	r3, [r0]
	movs	r3, #0
	str	r3, [r0]
	str	r3, [r0]
	str	r3, [r0]
	b	nandc_wait_flash_ready
.L377:
	.align	2
.L376:
	.word	.LANCHOR42
	.size	ymtc_3d_set_slc_rr_para, .-ymtc_3d_set_slc_rr_para
	.section	.text.flash_erase_duplane_block,"ax",%progbits
	.align	1
	.global	flash_erase_duplane_block
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	flash_erase_duplane_block, %function
flash_erase_duplane_block:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r0, r1, r4, r5, r6, r7, r8, r10, fp, lr}
	mov	r5, r2
	ldr	r4, .L402
	mov	r7, r0
	mov	r6, r1
	mov	r10, r3
	ldrb	r2, [r4]	@ zero_extendqisi2
	cmp	r2, r0
	bhi	.L379
	movw	r2, #695
	ldr	r1, .L402+4
	ldr	r0, .L402+8
	bl	printf
.L379:
	ldrb	r3, [r4]	@ zero_extendqisi2
	cmp	r3, r7
	bls	.L388
	ldr	r3, .L402+12
	ldrb	r4, [r3, r7]	@ zero_extendqisi2
	ldr	r3, .L402+16
	add	r7, r4, #8
	ldr	r8, [r3]
	ldr	r3, .L402+20
	ldr	r3, [r3]
	add	r7, r8, r7, lsl #8
	lsls	r3, r3, #27
	bpl	.L381
	mov	r3, r10
	mov	r2, r5
	mov	r1, r4
	ldr	r0, .L402+24
	bl	printf
.L381:
	bl	nandc_wait_flash_ready
	mov	r0, r4
	bl	nandc_cs
	mov	r0, r4
	cmp	r6, #0
	bne	.L382
	bl	zftl_flash_enter_slc_mode
.L383:
	lsls	r4, r4, #8
	movs	r3, #96
	add	r6, r8, r4
	str	r3, [r6, #2056]
	uxtb	r3, r5
	str	r3, [r6, #2052]
	lsrs	r3, r5, #8
	str	r3, [r6, #2052]
	lsrs	r3, r5, #16
	str	r3, [r6, #2052]
	ldr	r3, .L402+28
	ldrb	r2, [r3]	@ zero_extendqisi2
	cbz	r2, .L384
	lsrs	r2, r5, #24
	str	r2, [r6, #2052]
.L384:
	ldr	r2, .L402+32
	ldrb	r2, [r2]	@ zero_extendqisi2
	cmp	r2, #0
	bne	.L389
	add	r2, r8, r4
	movs	r1, #208
	str	r1, [r2, #2056]
	str	r3, [sp, #4]
	bl	nandc_wait_flash_ready
	mov	r0, r7
	bl	flash_read_status
	ldr	r3, [sp, #4]
	and	fp, r0, #5
.L385:
	add	r2, r8, r4
	movs	r1, #96
	str	r1, [r2, #2056]
	uxtb	r2, r10
	ldrb	r3, [r3]	@ zero_extendqisi2
	str	r2, [r6, #2052]
	lsr	r2, r10, #8
	str	r2, [r6, #2052]
	lsr	r2, r10, #16
	str	r2, [r6, #2052]
	cbz	r3, .L386
	lsr	r2, r10, #24
	str	r2, [r6, #2052]
.L386:
	movs	r3, #208
	add	r0, r8, r4
	str	r3, [r0, #2056]
	bl	nandc_wait_flash_ready
	mov	r0, r7
	bl	flash_read_status
	bl	nandc_de_cs.constprop.32
	and	r3, r0, #5
	orrs	fp, r3, fp
	beq	.L387
	mov	r2, r0
	mov	r1, r5
	ldr	r0, .L402+36
	bl	printf
.L387:
	mov	r0, fp
.L378:
	add	sp, sp, #8
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r10, fp, pc}
.L382:
	bl	zftl_flash_exit_slc_mode
	b	.L383
.L389:
	mov	fp, #0
	b	.L385
.L388:
	mov	r0, #-1
	b	.L378
.L403:
	.align	2
.L402:
	.word	.LANCHOR23
	.word	.LANCHOR43
	.word	.LC0
	.word	.LANCHOR29
	.word	.LANCHOR7
	.word	.LANCHOR19
	.word	.LC31
	.word	.LANCHOR30
	.word	.LANCHOR44
	.word	.LC32
	.size	flash_erase_duplane_block, .-flash_erase_duplane_block
	.section	.text.flash_erase_block_en,"ax",%progbits
	.align	1
	.global	flash_erase_block_en
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	flash_erase_block_en, %function
flash_erase_block_en:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	ldr	r3, .L422
	push	{r4, r5, r6, r7, r8, r10, fp, lr}
	mov	r7, r2
	ldr	r5, .L422+4
	mov	r6, r0
	mov	fp, r1
	ldrb	r4, [r3]	@ zero_extendqisi2
	rsb	r3, r4, #24
	movs	r4, #1
	lsls	r4, r4, r3
	subs	r4, r4, #1
	ands	r4, r4, r2
	ldrb	r2, [r5]	@ zero_extendqisi2
	cmp	r2, r0
	bhi	.L405
	movw	r2, #757
	ldr	r1, .L422+8
	ldr	r0, .L422+12
	bl	printf
.L405:
	ldrb	r3, [r5]	@ zero_extendqisi2
	cmp	r3, r6
	bls	.L412
	ldr	r3, .L422+16
	ldrb	r5, [r3, r6]	@ zero_extendqisi2
	ldr	r3, .L422+20
	add	r10, r5, #8
	ldr	r8, [r3]
	ldr	r3, .L422+24
	ldr	r3, [r3]
	add	r10, r8, r10, lsl #8
	lsls	r3, r3, #27
	bpl	.L407
	mov	r3, fp
	mov	r2, r7
	mov	r1, r5
	ldr	r0, .L422+28
	bl	printf
.L407:
	bl	nandc_wait_flash_ready
	mov	r0, r5
	bl	nandc_cs
	mov	r0, r5
	cmp	fp, #0
	bne	.L408
	bl	zftl_flash_enter_slc_mode
.L409:
	lsls	r5, r5, #8
	movs	r2, #96
	add	r3, r8, r5
	str	r2, [r3, #2056]
	uxtb	r2, r4
	str	r2, [r3, #2052]
	lsrs	r2, r4, #8
	str	r2, [r3, #2052]
	lsrs	r2, r4, #16
	str	r2, [r3, #2052]
	ldr	r2, .L422+32
	ldrb	r2, [r2]	@ zero_extendqisi2
	cbz	r2, .L410
	lsrs	r4, r4, #24
	str	r4, [r3, #2052]
.L410:
	movs	r3, #208
	add	r5, r5, r8
	str	r3, [r5, #2056]
	bl	nandc_wait_flash_ready
	mov	r0, r10
	bl	flash_read_status
	bl	nandc_de_cs.constprop.32
	ands	r4, r0, #5
	beq	.L411
	ldr	r3, .L422+36
	mov	r0, r7
	ldrh	r1, [r3]
	bl	__aeabi_uidiv
	mov	r3, r4
	mov	r4, #-1
	mov	r2, r0
	mov	r1, r6
	ldr	r0, .L422+40
	bl	printf
.L411:
	mov	r0, r4
	pop	{r4, r5, r6, r7, r8, r10, fp, pc}
.L408:
	bl	zftl_flash_exit_slc_mode
	b	.L409
.L412:
	mov	r0, #-1
	pop	{r4, r5, r6, r7, r8, r10, fp, pc}
.L423:
	.align	2
.L422:
	.word	.LANCHOR31
	.word	.LANCHOR23
	.word	.LANCHOR45
	.word	.LC0
	.word	.LANCHOR29
	.word	.LANCHOR7
	.word	.LANCHOR19
	.word	.LC33
	.word	.LANCHOR30
	.word	.LANCHOR2
	.word	.LC34
	.size	flash_erase_block_en, .-flash_erase_block_en
	.section	.text.flash_erase_block,"ax",%progbits
	.align	1
	.global	flash_erase_block
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	flash_erase_block, %function
flash_erase_block:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	mov	r2, r1
	movs	r1, #0
	b	flash_erase_block_en
	.size	flash_erase_block, .-flash_erase_block
	.section	.text.flash_erase_all,"ax",%progbits
	.align	1
	.global	flash_erase_all
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	flash_erase_all, %function
flash_erase_all:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	ldr	r3, .L430
	push	{r4, r5, r6, r7, r8, lr}
	movs	r5, #0
	ldr	r7, .L430+4
	ldrb	r4, [r3, #13]	@ zero_extendqisi2
	ldrh	r3, [r3, #14]
	smulbb	r4, r4, r3
	uxth	r4, r4
.L426:
	ldr	r3, .L430+8
	ldrb	r2, [r3]	@ zero_extendqisi2
	uxth	r3, r5
	cmp	r2, r3
	bhi	.L429
	movs	r1, #0
	ldr	r0, .L430+12
	pop	{r4, r5, r6, r7, r8, lr}
	b	printf
.L429:
	ldr	r2, .L430+16
	uxth	r3, r5
	movs	r6, #0
	ldrb	r8, [r2, r3]	@ zero_extendqisi2
.L427:
	uxth	r3, r6
	cmp	r4, r3
	bhi	.L428
	adds	r5, r5, #1
	b	.L426
.L428:
	ldrh	r1, [r7]
	mov	r0, r8
	muls	r1, r6, r1
	adds	r6, r6, #1
	bl	flash_erase_block
	b	.L427
.L431:
	.align	2
.L430:
	.word	.LANCHOR32
	.word	.LANCHOR2
	.word	.LANCHOR23
	.word	.LC35
	.word	.LANCHOR29
	.size	flash_erase_all, .-flash_erase_all
	.section	.text.flash_start_plane_read,"ax",%progbits
	.align	1
	.global	flash_start_plane_read
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	flash_start_plane_read, %function
flash_start_plane_read:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 0, uses_anonymous_args = 0
	ldr	r3, .L460
	push	{r0, r1, r4, r5, r6, r7, r8, r10, fp, lr}
	ubfx	r10, r0, #24, #2
	ldrb	r5, [r3]	@ zero_extendqisi2
	movs	r3, #1
	rsb	r2, r5, #24
	lsl	r4, r3, r2
	lsl	r5, r3, r5
	ldr	r3, .L460+4
	lsr	r2, r0, r2
	subs	r5, r5, #1
	ands	r5, r5, r2
	subs	r4, r4, #1
	ldrb	r3, [r3]	@ zero_extendqisi2
	uxtb	r5, r5
	and	r7, r4, r0
	ands	r4, r4, r1
	cmp	r3, r5
	bhi	.L433
	movw	r2, #1148
	ldr	r1, .L460+8
	ldr	r0, .L460+12
	bl	printf
.L433:
	ldr	r3, .L460+16
	ldr	fp, .L460+44
	ldrb	r5, [r3, r5]	@ zero_extendqisi2
	ldr	r3, .L460+20
	mov	r0, r5
	ldr	r6, [r3]
	lsl	r8, r5, #8
	bl	nandc_cs
	cmp	r10, #0
	bne	.L434
	mov	r0, r7
	bl	slc_phy_page_address_calc
	mov	r7, r0
	mov	r0, r4
	bl	slc_phy_page_address_calc
	ldr	r3, .L460+24
	mov	r4, r0
	ldrb	r3, [r3]	@ zero_extendqisi2
	cbz	r3, .L435
	mov	r0, r5
	bl	zftl_flash_enter_slc_mode
.L435:
	ldr	r2, .L460+28
	uxtb	ip, r7
	lsrs	r0, r7, #8
	ldrb	r3, [r2, #16]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L437
	ldrb	r3, [r2, #8]	@ zero_extendqisi2
	add	r5, r6, r8
	str	r3, [r5, #2056]
	movs	r3, #0
	str	r3, [r5, #2052]
	str	r3, [r5, #2052]
	lsrs	r3, r7, #16
	str	ip, [r5, #2052]
	str	r0, [r5, #2052]
	str	r3, [r5, #2052]
	ldr	r3, .L460+32
	ldrb	r1, [r3]	@ zero_extendqisi2
	cbz	r1, .L438
	lsrs	r7, r7, #24
	str	r7, [r5, #2052]
.L438:
	ldrb	r2, [r2, #9]	@ zero_extendqisi2
	add	r7, r6, r8
	str	r3, [sp, #4]
	str	r2, [r7, #2056]
	bl	nandc_wait_flash_ready
	ldr	r2, [fp]
	ldr	r3, [sp, #4]
	ldrb	r2, [r2, #12]	@ zero_extendqisi2
	cmp	r2, #3
	bne	.L439
	cmp	r10, #0
	beq	.L439
	str	r10, [r7, #2056]
.L439:
	movs	r2, #0
	add	r1, r6, r8
	str	r2, [r1, #2056]
	str	r2, [r5, #2052]
	str	r2, [r5, #2052]
	uxtb	r2, r4
	ldrb	r3, [r3]	@ zero_extendqisi2
	str	r2, [r5, #2052]
	lsrs	r2, r4, #8
	str	r2, [r5, #2052]
	lsrs	r2, r4, #16
	str	r2, [r5, #2052]
	cbz	r3, .L440
	lsrs	r4, r4, #24
	str	r4, [r5, #2052]
.L440:
	add	r6, r6, r8
.L459:
	movs	r3, #48
	str	r3, [r6, #2056]
	add	sp, sp, #8
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r10, fp, pc}
.L434:
	ldr	r3, [fp]
	ldrb	r3, [r3, #12]	@ zero_extendqisi2
	cmp	r3, #3
	bne	.L436
	ldr	r3, .L460+36
	ldrb	r3, [r3]	@ zero_extendqisi2
	cbnz	r3, .L436
	ldr	r3, .L460+40
	ldrb	r3, [r3]	@ zero_extendqisi2
	cbnz	r3, .L436
	add	r3, r6, r8
	str	r10, [r3, #2056]
	b	.L435
.L436:
	mov	r0, r5
	bl	zftl_flash_exit_slc_mode
	b	.L435
.L437:
	ldr	r1, [fp]
	ldrb	r3, [r1, #7]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L442
	ldrb	r3, [r1, #12]	@ zero_extendqisi2
	cmp	r3, #2
	ittt	eq
	addeq	r3, r6, r8
	moveq	r5, #38
	streq	r5, [r3, #2056]
.L442:
	ldrb	r5, [r2, #8]	@ zero_extendqisi2
	lsrs	r7, r7, #16
	add	r3, r6, r8
	str	r5, [r3, #2056]
	str	ip, [r3, #2052]
	str	r0, [r3, #2052]
	str	r7, [r3, #2052]
	ldrb	r1, [r1, #12]	@ zero_extendqisi2
	cmp	r1, #3
	bne	.L443
	cmp	r10, #0
	beq	.L443
	str	r10, [r3, #2056]
.L443:
	ldrb	r2, [r2, #9]	@ zero_extendqisi2
	add	r6, r6, r8
	str	r2, [r6, #2056]
	uxtb	r2, r4
	str	r2, [r3, #2052]
	lsrs	r2, r4, #8
	lsrs	r4, r4, #16
	str	r2, [r3, #2052]
	str	r4, [r3, #2052]
	b	.L459
.L461:
	.align	2
.L460:
	.word	.LANCHOR31
	.word	.LANCHOR23
	.word	.LANCHOR46
	.word	.LC0
	.word	.LANCHOR29
	.word	.LANCHOR7
	.word	.LANCHOR0
	.word	.LANCHOR25
	.word	.LANCHOR30
	.word	.LANCHOR35
	.word	.LANCHOR36
	.word	.LANCHOR21
	.size	flash_start_plane_read, .-flash_start_plane_read
	.section	.text.flash_set_interface_mode,"ax",%progbits
	.align	1
	.global	flash_set_interface_mode
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	flash_set_interface_mode, %function
flash_set_interface_mode:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r3, r4, r5, r6, r7, r8, r10, lr}
	mov	r6, r0
	ldr	r7, .L506
	mov	r10, #0
	ldr	r8, .L506+24
.L476:
	ldrb	r5, [r7, r10, lsl #3]	@ zero_extendqisi2
	cmp	r5, #69
	beq	.L463
	cmp	r5, #44
	beq	.L463
	add	r3, r5, #119
	uxtb	r3, r3
	cmp	r3, #18
	bhi	.L464
	ldr	r2, .L506+4
	lsr	r3, r2, r3
	lsls	r2, r3, #31
	bpl	.L464
.L463:
	ldr	r3, .L506+8
	cmp	r6, #1
	ldr	r4, [r8]
	ldrb	r1, [r3]	@ zero_extendqisi2
	bne	.L465
	lsls	r3, r1, #31
	bpl	.L464
	ldr	r3, .L506+12
	ldr	r3, [r3]
	lsls	r0, r3, #19
	bpl	.L466
	ldr	r0, .L506+16
	bl	printf
.L466:
	lsl	r3, r10, #8
	cmp	r5, #44
	mov	r1, #239
	add	r2, r4, r3
	str	r1, [r2, #2056]
	beq	.L467
	cmp	r5, #137
	bne	.L468
.L467:
	adds	r2, r4, r3
.L505:
	movs	r1, #1
	str	r1, [r2, #2052]
	movs	r1, #5
.L502:
	add	r4, r4, r3
	str	r1, [r2, #2048]
.L504:
	movs	r3, #0
	str	r3, [r4, #2048]
	str	r3, [r4, #2048]
	str	r3, [r4, #2048]
.L464:
	add	r10, r10, #1
	cmp	r10, #4
	bne	.L476
	bl	nandc_wait_flash_ready
	movs	r0, #0
	pop	{r3, r4, r5, r6, r7, r8, r10, pc}
.L468:
	cmp	r5, #155
	beq	.L505
	movs	r1, #128
	str	r1, [r2, #2052]
	movs	r1, #1
	b	.L502
.L465:
	lsls	r2, r1, #29
	bpl	.L464
	ldr	r3, .L506+12
	ldr	r3, [r3]
	lsls	r3, r3, #19
	bpl	.L471
	ldr	r0, .L506+20
	bl	printf
.L471:
	lsl	r2, r10, #8
	cmp	r5, #44
	mov	r1, #239
	add	r3, r4, r2
	str	r1, [r3, #2056]
	beq	.L472
	cmp	r5, #137
	bne	.L473
.L472:
	movs	r1, #1
	adds	r3, r4, r2
	str	r1, [r3, #2052]
	movs	r1, #35
.L503:
	str	r1, [r3, #2048]
	add	r4, r4, r2
	b	.L504
.L473:
	cmp	r5, #155
	itett	eq
	moveq	r1, #1
	movne	r1, #128
	streq	r1, [r3, #2052]
	moveq	r1, #37
	itt	ne
	strne	r1, [r3, #2052]
	movne	r1, #0
	b	.L503
.L507:
	.align	2
.L506:
	.word	.LANCHOR47
	.word	294913
	.word	.LANCHOR48
	.word	.LANCHOR19
	.word	.LC36
	.word	.LC37
	.word	.LANCHOR7
	.size	flash_set_interface_mode, .-flash_set_interface_mode
	.section	.text.mt_auto_read_calibration_config,"ax",%progbits
	.align	1
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	mt_auto_read_calibration_config, %function
mt_auto_read_calibration_config:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, lr}
	mov	r5, r1
	mov	r6, r0
	bl	nandc_wait_flash_ready
	ldr	r3, .L509
	movs	r0, #1
	ldr	r4, [r3]
	movs	r3, #239
	add	r4, r4, r6, lsl #8
	str	r3, [r4, #2056]
	movs	r3, #150
	str	r3, [r4, #2052]
	bl	udelay
	movs	r3, #0
	str	r5, [r4, #2048]
	str	r3, [r4, #2048]
	str	r3, [r4, #2048]
	str	r3, [r4, #2048]
	pop	{r4, r5, r6, pc}
.L510:
	.align	2
.L509:
	.word	.LANCHOR7
	.size	mt_auto_read_calibration_config, .-mt_auto_read_calibration_config
	.section	.text.flash_reset,"ax",%progbits
	.align	1
	.global	flash_reset
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	flash_reset, %function
flash_reset:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	ldr	r3, .L512
	ldr	r3, [r3]
	add	r0, r3, r0, lsl #8
	movs	r3, #255
	str	r3, [r0, #2056]
	b	nandc_wait_flash_ready
.L513:
	.align	2
.L512:
	.word	.LANCHOR7
	.size	flash_reset, .-flash_reset
	.section	.text.flash_read_id,"ax",%progbits
	.align	1
	.global	flash_read_id
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	flash_read_id, %function
flash_read_id:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r0, r1, r2, r3, r4, r5, r6, lr}
	mov	r6, r0
	ldr	r3, .L516
	mov	r4, r1
	ldr	r5, [r3]
	bl	flash_reset
	mov	r0, r6
	bl	nandc_cs
	add	r5, r5, r6, lsl #8
	movs	r3, #144
	movs	r0, #1
	str	r3, [r5, #2056]
	movs	r3, #0
	str	r3, [r5, #2052]
	bl	udelay
	ldr	r3, [r5, #2048]
	strb	r3, [r4]
	ldr	r3, [r5, #2048]
	strb	r3, [r4, #1]
	ldr	r3, [r5, #2048]
	strb	r3, [r4, #2]
	ldr	r3, [r5, #2048]
	strb	r3, [r4, #3]
	ldr	r3, [r5, #2048]
	strb	r3, [r4, #4]
	ldr	r3, [r5, #2048]
	strb	r3, [r4, #5]
	ldr	r3, [r5, #2048]
	strb	r3, [r4, #6]
	ldr	r3, [r5, #2048]
	strb	r3, [r4, #7]
	bl	nandc_de_cs.constprop.32
	ldrb	r2, [r4]	@ zero_extendqisi2
	subs	r3, r2, #1
	uxtb	r3, r3
	cmp	r3, #253
	bhi	.L514
	ldrb	r1, [r4, #5]	@ zero_extendqisi2
	ldrb	r3, [r4, #1]	@ zero_extendqisi2
	ldr	r0, .L516+4
	str	r1, [sp, #12]
	ldrb	r1, [r4, #4]	@ zero_extendqisi2
	str	r1, [sp, #8]
	ldrb	r1, [r4, #3]	@ zero_extendqisi2
	str	r1, [sp, #4]
	ldrb	r1, [r4, #2]	@ zero_extendqisi2
	str	r1, [sp]
	adds	r1, r6, #1
	bl	printf
.L514:
	add	sp, sp, #16
	@ sp needed
	pop	{r4, r5, r6, pc}
.L517:
	.align	2
.L516:
	.word	.LANCHOR7
	.word	.LC38
	.size	flash_read_id, .-flash_read_id
	.section	.text.flash_read_spare,"ax",%progbits
	.align	1
	.global	flash_read_spare
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	flash_read_spare, %function
flash_read_spare:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r3, r4, r5, lr}
	mov	r5, r2
	ldr	r3, .L519
	ldr	r2, .L519+4
	ldrb	r3, [r3, #9]	@ zero_extendqisi2
	ldr	r4, [r2]
	movs	r2, #0
	lsls	r3, r3, #9
	add	r4, r4, r0, lsl #8
	str	r2, [r4, #2056]
	str	r3, [r4, #2052]
	lsrs	r3, r3, #8
	str	r3, [r4, #2052]
	uxtb	r3, r1
	str	r3, [r4, #2052]
	lsrs	r3, r1, #8
	lsrs	r1, r1, #16
	str	r3, [r4, #2052]
	movs	r3, #48
	str	r1, [r4, #2052]
	str	r3, [r4, #2056]
	bl	nandc_wait_flash_ready
	ldr	r3, [r4, #2048]
	strb	r3, [r5]
	pop	{r3, r4, r5, pc}
.L520:
	.align	2
.L519:
	.word	.LANCHOR32
	.word	.LANCHOR7
	.size	flash_read_spare, .-flash_read_spare
	.section	.text.flash_read_otp_data,"ax",%progbits
	.align	1
	.global	flash_read_otp_data
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	flash_read_otp_data, %function
flash_read_otp_data:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	ldr	r3, .L524
	push	{r0, r1, r4, r5, r6, r7, r8, r10, fp, lr}
	mov	r8, r0
	lsl	r8, r8, #8
	mov	r6, r1
	mov	r5, r2
	ldr	r7, [r3]
	mov	fp, #144
	bl	nandc_cs
	movs	r3, #239
	movs	r0, #1
	add	r4, r7, r8
	mov	r10, #0
	str	r3, [r4, #2056]
	str	fp, [r4, #2052]
	bl	udelay
	movs	r3, #1
	str	r3, [r4, #2048]
	str	r10, [r4, #2048]
	str	r10, [r4, #2048]
	str	r10, [r4, #2048]
	bl	nandc_wait_flash_ready
	movs	r3, #238
	ldr	r0, .L524+4
	str	r3, [r4, #2056]
	str	fp, [r4, #2052]
	ldr	r2, [r4, #2048]
	ldr	r3, [r4, #2048]
	ldr	r1, [r4, #2048]
	str	r1, [sp]
	mov	r1, r6
	bl	printf
	bl	nandc_wait_flash_ready
	uxtb	r3, r6
	str	r10, [r4, #2056]
	str	r10, [r4, #2052]
	str	r10, [r4, #2052]
	str	r3, [r4, #2052]
	lsrs	r3, r6, #8
	lsrs	r6, r6, #16
	str	r3, [r4, #2052]
	movs	r3, #48
	str	r6, [r4, #2052]
	str	r3, [r4, #2056]
	bl	nandc_wait_flash_ready
	add	r3, r5, #16384
	mov	r2, r5
.L522:
	ldr	r1, [r4, #2048]
	strb	r1, [r2], #1
	cmp	r2, r3
	bne	.L522
	add	r7, r7, r8
	movs	r3, #239
	str	r3, [r7, #2056]
	movs	r3, #144
	str	r3, [r4, #2052]
	movs	r0, #1
	bl	udelay
	movs	r3, #0
	str	r3, [r4, #2048]
	str	r3, [r4, #2048]
	str	r3, [r4, #2048]
	str	r3, [r4, #2048]
	add	sp, sp, #8
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r10, fp, lr}
	b	nandc_de_cs.constprop.32
.L525:
	.align	2
.L524:
	.word	.LANCHOR7
	.word	.LC39
	.size	flash_read_otp_data, .-flash_read_otp_data
	.section	.text.sandisk_prog_test_bad_block,"ax",%progbits
	.align	1
	.global	sandisk_prog_test_bad_block
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	sandisk_prog_test_bad_block, %function
sandisk_prog_test_bad_block:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, r8, lr}
	mov	r8, r1
	ldr	r3, .L541
	lsls	r6, r0, #8
	ldr	r7, .L541+4
	ldr	r5, [r3]
	ldrb	r3, [r7, #29]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L527
	adds	r2, r5, r6
	str	r3, [r2, #2056]
.L528:
	adds	r4, r5, r6
	movs	r3, #128
	str	r3, [r4, #2056]
	movs	r3, #0
	str	r3, [r4, #2052]
	str	r3, [r4, #2052]
	uxtb	r3, r8
	str	r3, [r4, #2052]
	lsr	r3, r8, #8
	str	r3, [r4, #2052]
	lsr	r3, r8, #16
	str	r3, [r4, #2052]
	movs	r3, #16
	str	r3, [r4, #2056]
	bl	nandc_wait_flash_ready
	movs	r3, #112
	movs	r0, #1
	str	r3, [r4, #2056]
	bl	udelay
	ldr	r2, [r4, #2048]
	cmp	r2, #255
	it	eq
	ldreq	r2, [r4, #2048]
	ands	r4, r2, #5
	beq	.L530
	ldr	r3, .L541+8
	ldr	r3, [r3]
	lsls	r3, r3, #19
	bpl	.L530
	mov	r1, r8
	ldr	r0, .L541+12
	bl	printf
.L530:
	ldrb	r3, [r7, #30]	@ zero_extendqisi2
	cbz	r3, .L526
	add	r5, r5, r6
	str	r3, [r5, #2056]
.L526:
	mov	r0, r4
	pop	{r4, r5, r6, r7, r8, pc}
.L527:
	adds	r3, r5, r6
	movs	r2, #162
	str	r2, [r3, #2056]
	b	.L528
.L542:
	.align	2
.L541:
	.word	.LANCHOR7
	.word	.LANCHOR32
	.word	.LANCHOR19
	.word	.LC40
	.size	sandisk_prog_test_bad_block, .-sandisk_prog_test_bad_block
	.section	.text.nandc_rdy_status,"ax",%progbits
	.align	1
	.global	nandc_rdy_status
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	nandc_rdy_status, %function
nandc_rdy_status:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	ldr	r3, .L544
	sub	sp, sp, #8
	ldr	r3, [r3]
	ldr	r3, [r3]
	str	r3, [sp, #4]
	ldr	r0, [sp, #4]
	ubfx	r0, r0, #9, #1
	add	sp, sp, #8
	@ sp needed
	bx	lr
.L545:
	.align	2
.L544:
	.word	.LANCHOR7
	.size	nandc_rdy_status, .-nandc_rdy_status
	.section	.text.nandc_bch_sel,"ax",%progbits
	.align	1
	.global	nandc_bch_sel
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	nandc_bch_sel, %function
nandc_bch_sel:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 0, uses_anonymous_args = 0
	movs	r3, #0
	push	{r0, r1, r4, lr}
	str	r3, [sp, #4]
	ldr	r2, [sp, #4]
	orr	r2, r2, #1
	str	r2, [sp, #4]
	ldr	r2, .L557
	strb	r0, [r2]
	ldr	r2, .L557+4
	ldrb	r2, [r2]	@ zero_extendqisi2
	cmp	r2, #9
	ldr	r2, .L557+8
	bne	.L547
	ldr	r2, [r2]
	cmp	r0, #70
	ldr	r1, [sp, #4]
	str	r1, [r2, #16]
	beq	.L548
	cmp	r0, #60
	beq	.L554
	cmp	r0, #40
	ite	eq
	moveq	r3, #2
	movne	r3, #1
.L548:
	movs	r1, #0
	str	r1, [sp]
	ldr	r1, [sp]
	bfi	r1, r3, #25, #3
	str	r1, [sp]
	ldr	r3, [sp]
	orr	r3, r3, #1
	str	r3, [sp]
	ldr	r3, [sp]
	str	r3, [r2, #32]
.L546:
	add	sp, sp, #8
	@ sp needed
	pop	{r4, pc}
.L554:
	movs	r3, #3
	b	.L548
.L547:
	ldr	r1, [r2]
	movs	r4, #16
	ldr	r2, [sp, #4]
	cmp	r0, r4
	str	r2, [r1, #8]
	str	r3, [sp]
	ldr	r2, [sp]
	bfi	r2, r4, #8, #8
	str	r2, [sp]
	ldr	r2, [sp]
	bfi	r2, r3, #18, #1
	str	r2, [sp]
	bne	.L550
.L556:
	ldr	r2, [sp]
	bfi	r2, r3, #4, #1
	str	r2, [sp]
	b	.L551
.L550:
	cmp	r0, #24
	bne	.L552
	ldr	r3, [sp]
	orr	r3, r3, #16
	str	r3, [sp]
.L551:
	ldr	r3, [sp]
	orr	r3, r3, #1
	str	r3, [sp]
	ldr	r3, [sp]
	str	r3, [r1, #12]
	b	.L546
.L552:
	ldr	r2, [sp]
	cmp	r0, #40
	orr	r2, r2, #262144
	str	r2, [sp]
	ldr	r2, [sp]
	orr	r2, r2, #16
	str	r2, [sp]
	bne	.L551
	b	.L556
.L558:
	.align	2
.L557:
	.word	.LANCHOR49
	.word	.LANCHOR27
	.word	.LANCHOR7
	.size	nandc_bch_sel, .-nandc_bch_sel
	.section	.text.zftl_nandc_get_irq_status,"ax",%progbits
	.align	1
	.global	zftl_nandc_get_irq_status
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	zftl_nandc_get_irq_status, %function
zftl_nandc_get_irq_status:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	ldr	r3, .L562
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, #9
	ite	eq
	ldreq	r0, [r0, #296]
	ldrne	r0, [r0, #372]
	bx	lr
.L563:
	.align	2
.L562:
	.word	.LANCHOR27
	.size	zftl_nandc_get_irq_status, .-zftl_nandc_get_irq_status
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
	.section	.text.nandc_iqr_wait_flash_ready,"ax",%progbits
	.align	1
	.global	nandc_iqr_wait_flash_ready
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	nandc_iqr_wait_flash_ready, %function
nandc_iqr_wait_flash_ready:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	bx	lr
	.size	nandc_iqr_wait_flash_ready, .-nandc_iqr_wait_flash_ready
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
	.section	.text.nandc_xfer_start,"ax",%progbits
	.align	1
	.global	nandc_xfer_start
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	nandc_xfer_start, %function
nandc_xfer_start:
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r0, r1, r2, r3, r4, r5, r6, r7, r8, r10, fp, lr}
	mov	r5, r0
	ldr	r0, .L583
	and	lr, r5, #1
	ldr	r4, .L583+4
	ldrb	r0, [r0]	@ zero_extendqisi2
	ldr	r7, .L583+8
	cmp	r0, #9
	add	r0, r1, #1
	bne	.L568
	movs	r6, #0
	mov	ip, #1
	str	r6, [sp, #4]
	ubfx	r0, r0, #1, #6
	ldr	r1, [sp, #4]
	bfi	r1, lr, #1, #1
	str	r1, [sp, #4]
	ldr	r1, [sp, #4]
	orr	r1, r1, #8
	str	r1, [sp, #4]
	ldr	r1, [sp, #4]
	bfi	r1, ip, #5, #2
	str	r1, [sp, #4]
	ldr	r1, [sp, #4]
	orr	r1, r1, #536870912
	str	r1, [sp, #4]
	ldr	r1, [sp, #4]
	orr	r1, r1, #1024
	str	r1, [sp, #4]
	ldr	r1, [sp, #4]
	bfi	r1, r6, #4, #1
	str	r1, [sp, #4]
	ldr	r1, [sp, #4]
	bfi	r1, r0, #22, #6
	str	r1, [sp, #4]
	ldr	r1, [sp, #4]
	orr	r1, r1, #128
	str	r1, [sp, #4]
	ldr	r1, .L583+12
	ldrb	r1, [r1]	@ zero_extendqisi2
	cbz	r1, .L569
	ldr	r1, .L583+16
	ldrb	r1, [r1]	@ zero_extendqisi2
	cbz	r1, .L569
	ldr	r1, [sp, #4]
	orr	r1, r1, #512
	str	r1, [sp, #4]
.L569:
	ldr	r1, [sp, #4]
	bic	r0, r2, #63
	str	r3, [r4, #8]
	clz	r5, r5
	str	r3, [r4, #16]
	add	r3, r2, #63
	bic	r3, r3, #63
	ubfx	r1, r1, #22, #6
	add	r1, r3, r1, lsl #10
	str	r2, [r4, #4]
	str	r2, [r4, #12]
	lsrs	r5, r5, #5
	bl	flush_dcache_range
	ldr	r0, [r4, #8]
	add	r1, r0, #63
	bic	r0, r0, #63
	bic	r1, r1, #63
	adds	r1, r1, #64
	bl	flush_dcache_range
	movs	r3, #1
	ldr	r2, [r4, #12]
	str	r3, [r4, #20]
	movs	r1, #16
	ldr	r3, [r7]
	str	r2, [r3, #52]
	ldr	r2, [r4, #16]
	str	r2, [r3, #56]
	ldr	r2, [r3, #48]
	str	r2, [sp, #8]
	ldr	r2, [sp, #8]
	bfi	r2, r1, #9, #5
	movs	r1, #2
	str	r2, [sp, #8]
	ldr	r2, [sp, #8]
	orr	r2, r2, #448
	str	r2, [sp, #8]
	ldr	r2, [sp, #8]
	bfi	r2, r1, #3, #3
	str	r2, [sp, #8]
	ldr	r2, [sp, #8]
	orr	r2, r2, #4
	str	r2, [sp, #8]
	ldr	r2, [sp, #8]
	bfi	r2, r5, #1, #1
	str	r2, [sp, #8]
	ldr	r2, [sp, #8]
	orr	r2, r2, #1
	str	r2, [sp, #8]
	ldr	r2, .L583+20
	ldrh	r1, [r2]
	ldr	r2, [sp, #8]
	bfi	r2, r1, #16, #11
	str	r2, [sp, #8]
	ldr	r2, [sp, #8]
	str	r2, [r3, #48]
	ldr	r2, [sp, #4]
	str	r2, [r3, #16]
	ldr	r2, [sp, #4]
	orr	r2, r2, #4
	str	r2, [sp, #4]
	ldr	r2, [sp, #4]
	str	r2, [r3, #16]
.L567:
	add	sp, sp, #16
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r10, fp, pc}
.L568:
	ldr	r6, [r7]
	mov	ip, #16
	ubfx	r0, r0, #1, #6
	ldr	r6, [r6, #12]
	str	r6, [sp, #12]
	ldr	r6, [sp, #12]
	bfi	r6, ip, #8, #8
	str	r6, [sp, #12]
	ldr	r6, [sp, #12]
	bfc	r6, #3, #1
	str	r6, [sp, #12]
	ldr	r6, [sp, #12]
	bfc	r6, #5, #3
	str	r6, [sp, #12]
	movs	r6, #0
	str	r6, [sp, #4]
	ldr	ip, [sp, #4]
	bfi	ip, lr, #1, #1
	mov	lr, #1
	str	ip, [sp, #4]
	ldr	ip, [sp, #4]
	orr	ip, ip, #8
	str	ip, [sp, #4]
	ldr	ip, [sp, #4]
	bfi	ip, lr, #5, #2
	str	ip, [sp, #4]
	ldr	ip, [sp, #4]
	orr	ip, ip, #536870912
	str	ip, [sp, #4]
	ldr	ip, [sp, #4]
	orr	ip, ip, #1024
	str	ip, [sp, #4]
	ldr	ip, [sp, #4]
	bfi	ip, r6, #4, #1
	str	ip, [sp, #4]
	ldr	ip, [sp, #4]
	bfi	ip, r0, #22, #6
	str	ip, [sp, #4]
	cmp	r5, #0
	beq	.L571
	ldr	r0, .L583+24
	lsrs	r1, r1, #1
	ldr	r8, [r4]
	ldrb	r0, [r0]	@ zero_extendqisi2
	cmp	r0, #25
	mov	r0, r6
	ite	cc
	movcc	lr, #64
	movcs	lr, #128
.L573:
	cmp	r0, r1
	add	fp, r3, r0, lsl #2
	add	r10, lr, r6
	blt	.L574
.L575:
	ldr	r3, [r4]
	bic	r0, r2, #63
	ldr	r1, [sp, #4]
	clz	r5, r5
	str	r2, [r4, #4]
	lsrs	r5, r5, #5
	str	r3, [r4, #8]
	str	r3, [r4, #16]
	add	r3, r2, #63
	bic	r3, r3, #63
	ubfx	r1, r1, #22, #6
	add	r1, r3, r1, lsl #10
	str	r2, [r4, #12]
	bl	flush_dcache_range
	ldr	r0, [r4, #8]
	ldr	r1, [sp, #4]
	add	r3, r0, #63
	bic	r0, r0, #63
	bic	r3, r3, #63
	ubfx	r1, r1, #22, #6
	add	r1, r3, r1, lsl #7
	bl	flush_dcache_range
	movs	r3, #1
	ldr	r2, [r4, #12]
	str	r3, [r4, #20]
	movs	r1, #16
	ldr	r3, [r7]
	str	r2, [r3, #20]
	ldr	r2, [r4, #16]
	str	r2, [r3, #24]
	movs	r2, #0
	str	r2, [sp, #8]
	ldr	r2, [sp, #8]
	bfi	r2, r1, #9, #5
	movs	r1, #2
	str	r2, [sp, #8]
	ldr	r2, [sp, #8]
	orr	r2, r2, #448
	str	r2, [sp, #8]
	ldr	r2, [sp, #8]
	bfi	r2, r1, #3, #3
	str	r2, [sp, #8]
	ldr	r2, [sp, #8]
	orr	r2, r2, #4
	str	r2, [sp, #8]
	ldr	r2, [sp, #8]
	bfi	r2, r5, #1, #1
	str	r2, [sp, #8]
	ldr	r2, [sp, #8]
	orr	r2, r2, #1
	str	r2, [sp, #8]
	ldr	r2, [sp, #8]
	str	r2, [r3, #16]
	ldr	r2, [sp, #12]
	str	r2, [r3, #12]
	ldr	r2, [sp, #4]
	str	r2, [r3, #8]
	ldr	r2, [sp, #4]
	orr	r2, r2, #4
	str	r2, [sp, #4]
	ldr	r2, [sp, #4]
	str	r2, [r3, #8]
	b	.L567
.L574:
	ldrh	ip, [r3, r0, lsl #2]
	bic	r6, r6, #3
	ldrh	fp, [fp, #2]
	adds	r0, r0, #1
	orr	ip, ip, fp, lsl #16
	str	ip, [r8, r6]
	mov	r6, r10
	b	.L573
.L571:
	ldr	r3, [r4]
	str	lr, [r3]
	b	.L575
.L584:
	.align	2
.L583:
	.word	.LANCHOR27
	.word	.LANCHOR52
	.word	.LANCHOR7
	.word	.LANCHOR50
	.word	.LANCHOR51
	.word	.LANCHOR53
	.word	.LANCHOR49
	.size	nandc_xfer_start, .-nandc_xfer_start
	.section	.text.nandc_set_seed,"ax",%progbits
	.align	1
	.global	nandc_set_seed
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	nandc_set_seed, %function
nandc_set_seed:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	ldr	r2, .L592
	and	r0, r0, #127
	ldr	r3, .L592+4
	ldrb	r2, [r2]	@ zero_extendqisi2
	ldrh	r3, [r3, r0, lsl #1]
	cbz	r2, .L586
	orr	r3, r3, #-1073741824
.L586:
	ldr	r2, .L592+8
	ldrb	r2, [r2]	@ zero_extendqisi2
	cmp	r2, #9
	ldr	r2, .L592+12
	ldr	r2, [r2]
	ite	eq
	streq	r3, [r2, #520]
	strne	r3, [r2, #336]
	bx	lr
.L593:
	.align	2
.L592:
	.word	.LANCHOR51
	.word	.LANCHOR54
	.word	.LANCHOR27
	.word	.LANCHOR7
	.size	nandc_set_seed, .-nandc_set_seed
	.section	.text.zftl_flash_de_init,"ax",%progbits
	.align	1
	.global	zftl_flash_de_init
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	zftl_flash_de_init, %function
zftl_flash_de_init:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, lr}
	bl	nandc_wait_flash_ready
	ldr	r3, .L613
	ldrb	r3, [r3]	@ zero_extendqisi2
	cbz	r3, .L595
	ldr	r3, .L613+4
	ldrb	r0, [r3]	@ zero_extendqisi2
	cbnz	r0, .L595
	ldr	r3, .L613+8
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, #9
	beq	.L595
	bl	zftl_flash_exit_slc_mode
.L595:
	ldr	r4, .L613+12
	movs	r0, #0
	bl	hynix_reconfig_rr_para
	ldrb	r3, [r4]	@ zero_extendqisi2
	cbz	r3, .L596
	ldr	r3, .L613+16
	ldrb	r3, [r3]	@ zero_extendqisi2
	lsls	r3, r3, #31
	bpl	.L596
	movs	r0, #1
	bl	flash_set_interface_mode
	movs	r0, #1
	bl	nandc_set_if_mode
	movs	r3, #0
	strb	r3, [r4]
.L596:
	ldr	r1, .L613+20
	ldrb	r3, [r1]	@ zero_extendqisi2
	cbz	r3, .L597
	movs	r0, #0
	strb	r0, [r1]
	bl	nandc_set_seed
	movs	r3, #1
	strb	r3, [r1]
.L597:
	movs	r0, #0
	pop	{r4, pc}
.L614:
	.align	2
.L613:
	.word	.LANCHOR0
	.word	.LANCHOR24
	.word	.LANCHOR27
	.word	.LANCHOR26
	.word	.LANCHOR48
	.word	.LANCHOR51
	.size	zftl_flash_de_init, .-zftl_flash_de_init
	.section	.text.nandc_randomizer_enable,"ax",%progbits
	.align	1
	.global	nandc_randomizer_enable
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	nandc_randomizer_enable, %function
nandc_randomizer_enable:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	ldr	r3, .L616
	strb	r0, [r3]
	bx	lr
.L617:
	.align	2
.L616:
	.word	.LANCHOR51
	.size	nandc_randomizer_enable, .-nandc_randomizer_enable
	.section	.text.nandc_get_chip_if,"ax",%progbits
	.align	1
	.global	nandc_get_chip_if
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	nandc_get_chip_if, %function
nandc_get_chip_if:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	ldr	r3, .L619
	adds	r0, r0, #8
	ldr	r3, [r3]
	add	r0, r3, r0, lsl #8
	bx	lr
.L620:
	.align	2
.L619:
	.word	.LANCHOR7
	.size	nandc_get_chip_if, .-nandc_get_chip_if
	.section	.text.buf_reinit,"ax",%progbits
	.align	1
	.global	buf_reinit
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	buf_reinit, %function
buf_reinit:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	ldr	r3, .L624
	movs	r2, #0
	push	{r4, r5, lr}
	mov	r1, r2
	mov	r4, r3
.L622:
	uxtb	r0, r2
	adds	r2, r2, #1
	cmp	r2, #32
	strb	r1, [r3, #2]
	add	r5, r0, #1
	strb	r0, [r3, #1]
	strb	r5, [r3]
	add	r3, r3, #48
	str	r1, [r3, #-40]
	bne	.L622
	movs	r3, #255
	strb	r3, [r4, #1488]
	ldr	r3, .L624+4
	strb	r1, [r3]
	ldr	r3, .L624+8
	strb	r2, [r3]
	pop	{r4, r5, pc}
.L625:
	.align	2
.L624:
	.word	.LANCHOR55
	.word	.LANCHOR56
	.word	.LANCHOR57
	.size	buf_reinit, .-buf_reinit
	.section	.text.buf_add_tail,"ax",%progbits
	.align	1
	.global	buf_add_tail
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	buf_add_tail, %function
buf_add_tail:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	movs	r3, #255
	push	{r4, r5, r6, lr}
	strb	r3, [r1]
	mov	r5, r0
	mov	r4, r1
	ldrb	r3, [r0]	@ zero_extendqisi2
	cmp	r3, #255
	bne	.L627
	ldrb	r3, [r1, #1]	@ zero_extendqisi2
	cmp	r3, #255
	bne	.L628
	movs	r2, #74
	ldr	r1, .L633
	ldr	r0, .L633+4
	bl	printf
.L628:
	ldrb	r3, [r4, #1]	@ zero_extendqisi2
	strb	r3, [r5]
	pop	{r4, r5, r6, pc}
.L627:
	ldr	r2, .L633+8
	movs	r1, #48
	mov	r6, r2
.L632:
	mov	r5, r3
	muls	r3, r1, r3
	ldrb	r3, [r2, r3]	@ zero_extendqisi2
	cmp	r3, #255
	bne	.L632
	ldrb	r3, [r4, #1]	@ zero_extendqisi2
	cmp	r3, #255
	bne	.L630
	movs	r2, #81
	ldr	r1, .L633
	ldr	r0, .L633+4
	bl	printf
.L630:
	movs	r3, #48
	ldrb	r2, [r4, #1]	@ zero_extendqisi2
	muls	r3, r5, r3
	strb	r2, [r6, r3]
	pop	{r4, r5, r6, pc}
.L634:
	.align	2
.L633:
	.word	.LANCHOR58
	.word	.LC0
	.word	.LANCHOR55
	.size	buf_add_tail, .-buf_add_tail
	.section	.text.queue_read_cmd,"ax",%progbits
	.align	1
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	queue_read_cmd, %function
queue_read_cmd:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, lr}
	mov	r4, r0
	ldr	r1, [r0, #24]
	movs	r0, #48
	bl	flash_start_page_read
	movs	r3, #1
	mov	r1, r4
	strb	r3, [r4, #42]
	movs	r3, #0
	strb	r3, [r4, #43]
	movs	r3, #255
	strb	r3, [r4]
	ldr	r0, .L636
	pop	{r4, lr}
	b	buf_add_tail
.L637:
	.align	2
.L636:
	.word	.LANCHOR59
	.size	queue_read_cmd, .-queue_read_cmd
	.section	.text.zbuf_free,"ax",%progbits
	.align	1
	.global	zbuf_free
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	zbuf_free, %function
zbuf_free:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r3, lr}
	mov	r1, r0
	ldrb	r3, [r0, #2]	@ zero_extendqisi2
	and	r3, r3, #8
	strb	r3, [r0, #2]
	cbz	r3, .L639
	ldr	r3, [r0, #20]
	adds	r3, r3, #1
	beq	.L639
	ldr	r0, .L647
	bl	buf_add_tail
.L640:
	ldr	r2, .L647+4
	ldrb	r3, [r2]	@ zero_extendqisi2
	adds	r3, r3, #1
	strb	r3, [r2]
	pop	{r3, pc}
.L639:
	ldr	r3, .L647
	ldrb	r2, [r3]	@ zero_extendqisi2
	strb	r2, [r1]
	ldrb	r2, [r1, #1]	@ zero_extendqisi2
	strb	r2, [r3]
	b	.L640
.L648:
	.align	2
.L647:
	.word	.LANCHOR56
	.word	.LANCHOR57
	.size	zbuf_free, .-zbuf_free
	.section	.text.buf_alloc,"ax",%progbits
	.align	1
	.global	buf_alloc
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	buf_alloc, %function
buf_alloc:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r3, r4, r5, r6, r7, lr}
	mov	r7, r0
	ldr	r4, .L659
	ldrb	r3, [r4]	@ zero_extendqisi2
	cbz	r3, .L650
.L653:
	ldr	r5, .L659+4
	ldr	r2, .L659+8
	ldrb	r6, [r5]	@ zero_extendqisi2
	add	r0, r6, r6, lsl #1
	add	r0, r2, r0, lsl #4
	cbz	r7, .L651
.L652:
	movs	r1, #48
	muls	r1, r6, r1
	ldrb	r6, [r2, r1]	@ zero_extendqisi2
	adds	r3, r2, r1
	strb	r6, [r5]
	ldrb	r5, [r4]	@ zero_extendqisi2
	subs	r5, r5, #1
	strb	r5, [r4]
	movs	r4, #1
	strb	r4, [r3, #2]
	movs	r4, #255
	strb	r4, [r2, r1]
	mov	r2, #-1
	str	r2, [r3, #20]
	movs	r2, #0
	strh	r2, [r3, #34]	@ movhi
	str	r2, [r3, #8]
	strb	r2, [r3, #40]
	strb	r2, [r3, #41]
	pop	{r3, r4, r5, r6, r7, pc}
.L650:
	movs	r2, #121
	ldr	r1, .L659+12
	ldr	r0, .L659+16
	bl	printf
	ldrb	r3, [r4]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L653
.L655:
	movs	r0, #0
	pop	{r3, r4, r5, r6, r7, pc}
.L651:
	ldrb	r3, [r4]	@ zero_extendqisi2
	cmp	r3, #1
	bne	.L652
	b	.L655
.L660:
	.align	2
.L659:
	.word	.LANCHOR57
	.word	.LANCHOR56
	.word	.LANCHOR55
	.word	.LANCHOR60
	.word	.LC0
	.size	buf_alloc, .-buf_alloc
	.section	.text.buf_remove_buf,"ax",%progbits
	.align	1
	.global	buf_remove_buf
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	buf_remove_buf, %function
buf_remove_buf:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, lr}
	ldrb	r4, [r1, #1]	@ zero_extendqisi2
	ldrb	r3, [r0]	@ zero_extendqisi2
	cmp	r4, r3
	bne	.L662
	ldrb	r3, [r1]	@ zero_extendqisi2
	strb	r3, [r0]
.L667:
	movs	r0, #1
	pop	{r4, r5, pc}
.L665:
	mov	r5, r3
	muls	r3, r2, r3
	ldrb	r3, [r0, r3]	@ zero_extendqisi2
	cmp	r4, r3
	bne	.L664
	muls	r2, r5, r2
	ldrb	r3, [r1]	@ zero_extendqisi2
	strb	r3, [r0, r2]
	movs	r3, #255
	strb	r3, [r1]
	b	.L667
.L662:
	ldr	r0, .L668
	movs	r2, #48
.L664:
	cmp	r3, #255
	bne	.L665
	movs	r0, #0
	pop	{r4, r5, pc}
.L669:
	.align	2
.L668:
	.word	.LANCHOR55
	.size	buf_remove_buf, .-buf_remove_buf
	.section	.text.buf_remove_free,"ax",%progbits
	.align	1
	.global	buf_remove_free
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	buf_remove_free, %function
buf_remove_free:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r3, r4, r5, lr}
	mov	r5, r0
	ldr	r4, .L675
	ldrb	r3, [r4]	@ zero_extendqisi2
	cbnz	r3, .L671
	movs	r2, #172
	ldr	r1, .L675+4
	ldr	r0, .L675+8
	bl	printf
.L671:
	ldrb	r3, [r4]	@ zero_extendqisi2
	cbz	r3, .L670
	mov	r1, r5
	ldr	r0, .L675+12
	bl	buf_remove_buf
	cmp	r0, #1
	bne	.L670
	ldrb	r3, [r4]	@ zero_extendqisi2
	subs	r3, r3, #1
	strb	r3, [r4]
	ldrb	r3, [r5, #2]	@ zero_extendqisi2
	orr	r3, r3, #1
	strb	r3, [r5, #2]
.L670:
	pop	{r3, r4, r5, pc}
.L676:
	.align	2
.L675:
	.word	.LANCHOR57
	.word	.LANCHOR61
	.word	.LC0
	.word	.LANCHOR56
	.size	buf_remove_free, .-buf_remove_free
	.section	.text.dump_buf_info,"ax",%progbits
	.align	1
	.global	dump_buf_info
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	dump_buf_info, %function
dump_buf_info:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	ldr	r3, .L680
	push	{r4, r5, r6, lr}
	sub	sp, sp, #24
	ldr	r0, .L680+4
	ldrb	r1, [r3]	@ zero_extendqisi2
	bl	printf
	ldr	r3, .L680+8
	ldr	r0, .L680+12
	ldr	r4, .L680+16
	ldrb	r1, [r3]	@ zero_extendqisi2
	bl	printf
	ldr	r3, .L680+20
	add	r5, r4, #1536
	ldr	r0, .L680+24
	ldr	r6, .L680+28
	ldrb	r1, [r3]	@ zero_extendqisi2
	bl	printf
	ldr	r3, .L680+32
	ldr	r0, .L680+36
	ldrb	r1, [r3]	@ zero_extendqisi2
	bl	printf
	ldr	r3, .L680+40
	ldr	r0, .L680+44
	ldrb	r1, [r3]	@ zero_extendqisi2
	bl	printf
	ldr	r3, .L680+48
	ldr	r0, .L680+52
	ldrb	r1, [r3]	@ zero_extendqisi2
	bl	printf
.L678:
	ldr	r0, [r4, #24]
	adds	r4, r4, #48
	ldrb	r3, [r4, #-46]	@ zero_extendqisi2
	ldrb	r2, [r4, #-48]	@ zero_extendqisi2
	str	r0, [sp, #16]
	ldr	r0, [r4, #-28]
	ldrb	r1, [r4, #-47]	@ zero_extendqisi2
	str	r0, [sp, #12]
	ldr	r0, [r4, #-12]
	str	r0, [sp, #8]
	ldrb	r0, [r4, #-6]	@ zero_extendqisi2
	str	r0, [sp, #4]
	ldrh	r0, [r4, #-14]
	str	r0, [sp]
	mov	r0, r6
	bl	printf
	cmp	r4, r5
	bne	.L678
	add	sp, sp, #24
	@ sp needed
	pop	{r4, r5, r6, pc}
.L681:
	.align	2
.L680:
	.word	.LANCHOR59
	.word	.LC41
	.word	.LANCHOR62
	.word	.LC42
	.word	.LANCHOR55
	.word	.LANCHOR63
	.word	.LC43
	.word	.LC47
	.word	.LANCHOR64
	.word	.LC44
	.word	.LANCHOR56
	.word	.LC45
	.word	.LANCHOR57
	.word	.LC46
	.size	dump_buf_info, .-dump_buf_info
	.section	.text.flash_check_bad_block,"ax",%progbits
	.align	1
	.global	flash_check_bad_block
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	flash_check_bad_block, %function
flash_check_bad_block:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	ldr	r2, .L683
	push	{r4, lr}
	lsrs	r4, r1, #5
	and	r1, r1, #31
	ldrb	r3, [r2, #13]	@ zero_extendqisi2
	ldrh	r2, [r2, #14]
	smulbb	r3, r3, r2
	ldr	r2, .L683+4
	uxth	r3, r3
	ldr	r2, [r2]
	adds	r3, r3, #31
	asrs	r3, r3, #5
	add	r2, r2, r4, lsl #2
	lsls	r3, r3, #2
	uxth	r3, r3
	mla	r0, r0, r3, r2
	ldr	r0, [r0, #912]
	lsrs	r0, r0, r1
	and	r0, r0, #1
	pop	{r4, pc}
.L684:
	.align	2
.L683:
	.word	.LANCHOR32
	.word	.LANCHOR6
	.size	flash_check_bad_block, .-flash_check_bad_block
	.section	.text.flash_mask_bad_block,"ax",%progbits
	.align	1
	.global	flash_mask_bad_block
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	flash_mask_bad_block, %function
flash_mask_bad_block:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	ldr	r3, .L686
	mov	r2, r1
	push	{r4, r5, r6, lr}
	mov	r5, r0
	mov	r6, r1
	mov	r1, r0
	ldrb	r4, [r3, #13]	@ zero_extendqisi2
	ldrh	r3, [r3, #14]
	ldr	r0, .L686+4
	smulbb	r4, r4, r3
	bl	printf
	uxth	r4, r4
	ldr	r3, .L686+8
	add	r0, r4, #31
	asrs	r0, r0, #5
	ldr	r2, [r3]
	movs	r3, #1
	lsls	r0, r0, #2
	uxth	r0, r0
	muls	r0, r5, r0
	lsrs	r5, r6, #5
	and	r6, r6, #31
	lsl	r6, r3, r6
	add	r0, r0, #912
	add	r0, r0, r5, lsl #2
	ldr	r3, [r2, r0]
	orrs	r3, r3, r6
	str	r3, [r2, r0]
	pop	{r4, r5, r6, pc}
.L687:
	.align	2
.L686:
	.word	.LANCHOR32
	.word	.LC48
	.word	.LANCHOR6
	.size	flash_mask_bad_block, .-flash_mask_bad_block
	.section	.text.ftl_gc_write_buf,"ax",%progbits
	.align	1
	.global	ftl_gc_write_buf
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	ftl_gc_write_buf, %function
ftl_gc_write_buf:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r3, lr}
	mov	r1, r0
	ldrb	r3, [r0, #2]	@ zero_extendqisi2
	orr	r3, r3, #2
	strb	r3, [r0, #2]
	ldr	r0, .L689
	bl	buf_add_tail
	ldr	r3, .L689+4
	ldrb	r0, [r3]	@ zero_extendqisi2
	adds	r0, r0, #1
	uxtb	r0, r0
	strb	r0, [r3]
	pop	{r3, pc}
.L690:
	.align	2
.L689:
	.word	.LANCHOR65
	.word	.LANCHOR66
	.size	ftl_gc_write_buf, .-ftl_gc_write_buf
	.section	.text.zftl_cache_flush,"ax",%progbits
	.align	1
	.global	zftl_cache_flush
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	zftl_cache_flush, %function
zftl_cache_flush:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	bx	lr
	.size	zftl_cache_flush, .-zftl_cache_flush
	.section	.text.zftl_get_density,"ax",%progbits
	.align	1
	.global	zftl_get_density
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	zftl_get_density, %function
zftl_get_density:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	cbnz	r0, .L693
	ldr	r3, .L696
	ldr	r0, [r3]
	bx	lr
.L693:
	cmp	r0, #4
	ite	cc
	movcc	r0, #8192
	movcs	r0, #0
	bx	lr
.L697:
	.align	2
.L696:
	.word	.LANCHOR67
	.size	zftl_get_density, .-zftl_get_density
	.section	.text.gc_hook,"ax",%progbits
	.align	1
	.global	gc_hook
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	gc_hook, %function
gc_hook:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	bx	lr
	.size	gc_hook, .-gc_hook
	.section	.text.vpn_check,"ax",%progbits
	.align	1
	.global	vpn_check
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	vpn_check, %function
vpn_check:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	bx	lr
	.size	vpn_check, .-vpn_check
	.section	.text.ftl_scan_all_data,"ax",%progbits
	.align	1
	.global	ftl_scan_all_data
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	ftl_scan_all_data, %function
ftl_scan_all_data:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	bx	lr
	.size	ftl_scan_all_data, .-ftl_scan_all_data
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
	ldr	r3, .L702
	ldrh	r0, [r3]
	bx	lr
.L703:
	.align	2
.L702:
	.word	.LANCHOR68
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
	ldr	r3, .L705
	ldrh	r0, [r3]
	bx	lr
.L706:
	.align	2
.L705:
	.word	.LANCHOR8
	.size	FtlGetAllBlockNum, .-FtlGetAllBlockNum
	.section	.text.FtlLowFormat,"ax",%progbits
	.align	1
	.global	FtlLowFormat
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	FtlLowFormat, %function
FtlLowFormat:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	movs	r0, #0
	bx	lr
	.size	FtlLowFormat, .-FtlLowFormat
	.section	.text.gc_add_sblk,"ax",%progbits
	.align	1
	.global	gc_add_sblk
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	gc_add_sblk, %function
gc_add_sblk:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r0, r1, r2, r3, r4, r5, r6, r7, r8, r10, fp, lr}
	mov	r8, r2
	ldr	r3, .L743
	mov	r5, r0
	mov	r4, r1
	ldr	r2, [r3]
	mov	r10, r3
	tst	r2, #256
	beq	.L709
	ldr	r3, .L743+4
	mov	r2, r1
	mov	r1, r0
	ldrh	r3, [r3]
	str	r3, [sp, #12]
	ldr	r3, .L743+8
	ldrh	r3, [r3, #52]
	str	r3, [sp, #8]
	ldr	r3, .L743+12
	ldr	r3, [r3]
	ldrh	r3, [r3, r0, lsl #1]
	str	r3, [sp, #4]
	ldr	r3, .L743+16
	ldr	r3, [r3]
	add	r3, r3, r0, lsl #2
	ldr	r0, .L743+20
	ldrb	r3, [r3, #2]	@ zero_extendqisi2
	lsrs	r3, r3, #5
	str	r3, [sp]
	mov	r3, r8
	bl	printf
.L709:
	ldr	r6, .L743+24
	ldrh	r2, [r6]
	cmp	r2, r5
	bhi	.L710
	movw	r2, #543
	ldr	r1, .L743+28
	ldr	r0, .L743+32
	bl	printf
.L710:
	ldrh	r3, [r6]
	cmp	r3, r5
	bhi	.L711
	ldr	r0, [r10]
	ands	r0, r0, #1024
	beq	.L708
	mov	r3, r8
	mov	r2, r4
	mov	r1, r5
	ldr	r0, .L743+36
	bl	printf
.L731:
	movs	r0, #0
	b	.L708
.L711:
	ldr	r2, .L743+16
	ldr	r3, .L743+12
	ldr	r2, [r2]
	ldr	r3, [r3]
	add	r2, r2, r5, lsl #2
	ldrh	r3, [r3, r5, lsl #1]
	ldrb	r2, [r2, #2]	@ zero_extendqisi2
	ands	r6, r2, #224
	bne	.L713
	cmp	r3, #0
	beq	.L731
	movw	r2, #553
	ldr	r1, .L743+28
	ldr	r0, .L743+32
	bl	printf
	b	.L731
.L713:
	ldr	r6, .L743+8
	ldrh	r1, [r6]
	cmp	r1, r5
	beq	.L731
	ldr	r7, .L743+40
	ldr	r1, [r7]
	ldrh	r0, [r1, #48]
	cmp	r0, r5
	beq	.L731
	ldrh	r0, [r1, #16]
	cmp	r0, r5
	beq	.L731
	ldrh	r0, [r1, #80]
	cmp	r0, r5
	beq	.L731
	ldrh	ip, [r6, #52]!
	movs	r0, #0
.L714:
	cmp	r0, ip
	bcc	.L715
	cmp	r4, #0
	bne	.L719
	ldr	r0, .L743+44
	ldrh	r6, [r0]
	mov	r0, r4
	cmp	r5, r6
	beq	.L708
	ldr	lr, .L743+56
.L718:
	ldrh	fp, [lr, r0, lsl #1]
	cmp	r5, fp
	bne	.L717
	ldr	r0, [r10]
	ands	r0, r0, #256
	beq	.L708
	stm	sp, {r5, r6}
	lsrs	r2, r2, #5
	mov	r1, r5
	ldr	r0, .L743+48
	bl	printf
	b	.L731
.L715:
	ldrh	lr, [r6, #2]!
	cmp	lr, r5
	beq	.L731
	adds	r0, r0, #1
	b	.L714
.L717:
	adds	r0, r0, #1
	cmp	r0, #8
	bne	.L718
	add	r1, r1, r8, lsl #7
	add	r6, r1, #136
.L720:
	ldr	r1, [r10]
	lsls	r1, r1, #23
	bpl	.L721
	ldr	r1, .L743+4
	ldr	r0, .L743+52
	ldrh	r1, [r1]
	stm	sp, {r3, ip}
	lsrs	r3, r2, #5
	mov	r2, r4
	str	r1, [sp, #8]
	mov	r1, r5
	bl	printf
.L721:
	mov	r3, r6
	add	r1, r6, #128
	movw	r0, #65535
.L724:
	mov	r2, r3
	adds	r3, r3, #2
	ldrh	r6, [r2]
	cmp	r6, r0
	bne	.L722
	strh	r5, [r2]	@ movhi
	cbz	r4, .L723
	ldr	r2, [r7]
	ldrh	r3, [r2, #124]
	adds	r3, r3, #1
	strh	r3, [r2, #124]	@ movhi
.L742:
	movs	r0, #1
.L708:
	add	sp, sp, #16
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r10, fp, pc}
.L719:
	add	r6, r1, #392
	b	.L720
.L723:
	ldr	r3, [r7]
	add	r8, r3, r8, lsl #1
	ldrh	r3, [r8, #120]
	adds	r3, r3, #1
	strh	r3, [r8, #120]	@ movhi
	b	.L742
.L722:
	cmp	r3, r1
	bne	.L724
	b	.L742
.L744:
	.align	2
.L743:
	.word	.LANCHOR19
	.word	.LANCHOR69
	.word	.LANCHOR70
	.word	.LANCHOR11
	.word	.LANCHOR9
	.word	.LC49
	.word	.LANCHOR8
	.word	.LANCHOR71
	.word	.LC0
	.word	.LC50
	.word	.LANCHOR12
	.word	.LANCHOR72
	.word	.LC51
	.word	.LC52
	.word	.LANCHOR73
	.size	gc_add_sblk, .-gc_add_sblk
	.section	.text.gc_mark_bad_ppa,"ax",%progbits
	.align	1
	.global	gc_mark_bad_ppa
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	gc_mark_bad_ppa, %function
gc_mark_bad_ppa:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r3, r4, r5, r6, r7, r8, r10, lr}
	mov	r7, r0
	ldr	r3, .L749
	movs	r6, #1
	ldr	r2, .L749+4
	ldrh	r3, [r3]
	ldr	r8, .L749+16
	lsr	r4, r0, r3
	ldrb	r0, [r2]	@ zero_extendqisi2
	uxth	r5, r4
	rsb	r0, r0, #24
	subs	r0, r0, r3
	ldr	r3, .L749+8
	lsl	r0, r6, r0
	subs	r0, r0, #1
	ldrb	r1, [r3]	@ zero_extendqisi2
	ands	r0, r0, r4
	bl	__aeabi_uidiv
	uxth	r10, r0
	mov	r3, r7
	mov	r2, r5
	ldr	r1, [r8, #2188]
	ldr	r0, .L749+12
	bl	printf
	mov	r1, r6
	movs	r2, #0
	mov	r0, r10
	bl	gc_add_sblk
	ldr	r3, [r8, #2188]
	movs	r1, #0
.L746:
	uxth	r2, r1
	cmp	r3, r2
	bhi	.L748
	cmp	r3, #5
	itttt	ls
	addls	r2, r3, #1
	addls	r3, r3, #1096
	strls	r2, [r8, #2188]
	strhls	r5, [r8, r3, lsl #1]	@ movhi
	b	.L747
.L748:
	add	r2, r2, #1096
	adds	r1, r1, #1
	ldrh	r2, [r8, r2, lsl #1]
	cmp	r5, r2
	bne	.L746
.L747:
	movs	r0, #0
	pop	{r3, r4, r5, r6, r7, r8, r10, pc}
.L750:
	.align	2
.L749:
	.word	.LANCHOR74
	.word	.LANCHOR31
	.word	.LANCHOR75
	.word	.LC53
	.word	.LANCHOR70
	.size	gc_mark_bad_ppa, .-gc_mark_bad_ppa
	.section	.text.gc_get_src_ppa_from_index,"ax",%progbits
	.align	1
	.global	gc_get_src_ppa_from_index
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	gc_get_src_ppa_from_index, %function
gc_get_src_ppa_from_index:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	ldr	r3, .L752
	ldr	r3, [r3]
	ldr	r0, [r3, r0, lsl #2]
	bx	lr
.L753:
	.align	2
.L752:
	.word	.LANCHOR76
	.size	gc_get_src_ppa_from_index, .-gc_get_src_ppa_from_index
	.section	.text.gc_write_completed,"ax",%progbits
	.align	1
	.global	gc_write_completed
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	gc_write_completed, %function
gc_write_completed:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r0, r1, r4, r5, r6, r7, r8, r10, fp, lr}
	ldr	r5, .L781
.L755:
	ldr	r1, .L781+4
	ldrb	r8, [r1]	@ zero_extendqisi2
	cmp	r8, #255
	bne	.L768
	add	sp, sp, #8
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r10, fp, pc}
.L768:
	movs	r3, #48
	mul	r3, r3, r8
	adds	r2, r5, r3
	ldrb	r3, [r5, r3]	@ zero_extendqisi2
	ldrh	r6, [r2, #32]
	strb	r3, [r1]
	ldr	r1, [r2, #36]
	cbz	r1, .L756
	ldr	r3, .L781+8
	movs	r0, #1
	ldr	r2, [r2, #24]
	strh	r0, [r3, #2182]	@ movhi
	ldr	r0, .L781+12
	str	r2, [r3, #2184]
	bl	printf
	mov	r2, #956
	ldr	r1, .L781+16
	ldr	r0, .L781+20
	bl	printf
.L756:
	ldr	r10, .L781+56
	ldrb	r3, [r10]	@ zero_extendqisi2
	cmp	r3, #3
	bne	.L757
	ldr	r3, .L781+24
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L757
	ldr	r3, .L781+28
	ldr	r3, [r3]
	ldrb	r4, [r3, #89]	@ zero_extendqisi2
	ldr	r3, .L781+32
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, r4
	bhi	.L769
	cmp	r4, #2
	it	cs
	movcs	r4, #2
.L758:
	add	r4, r4, r4, lsl #1
.L759:
	ldr	r3, .L781+36
	movs	r2, #48
	mla	r2, r2, r8, r5
	ldr	r1, [r3]
	mov	r7, r6
	mov	fp, r3
	ldrb	r2, [r2, #1]	@ zero_extendqisi2
	ldrb	r1, [r1, r6]	@ zero_extendqisi2
	cmp	r1, r2
	beq	.L760
	mov	r2, #976
	ldr	r1, .L781+16
	ldr	r0, .L781+20
	str	r3, [sp, #4]
	bl	printf
	ldr	r3, [sp, #4]
.L760:
	movs	r2, #48
	mla	r8, r2, r8, r5
	ldrb	r2, [r8, #45]	@ zero_extendqisi2
	cmp	r2, #3
	beq	.L761
	ldrb	r2, [r10]	@ zero_extendqisi2
	cmp	r2, #3
	bne	.L761
	ldr	r2, .L781+40
	ldrb	r2, [r2]	@ zero_extendqisi2
	cbnz	r2, .L761
	ldr	r2, .L781+24
	ldrb	r2, [r2]	@ zero_extendqisi2
	cbnz	r2, .L761
	ldr	r2, .L781+44
	ldrb	r2, [r2]	@ zero_extendqisi2
	cbnz	r2, .L761
	ldr	r2, .L781+48
	ldrb	r2, [r2]	@ zero_extendqisi2
	cbz	r2, .L762
	ldr	r2, .L781+52
	ldrb	r2, [r2]	@ zero_extendqisi2
	cbnz	r2, .L761
.L762:
	ldr	r2, [r3]
	movs	r3, #0
	movs	r1, #48
	mov	r0, r3
	add	r6, r6, r2
.L763:
	uxth	r2, r3
	cmp	r4, r2
	bls	.L755
	ldrb	r2, [r6, r3]	@ zero_extendqisi2
	adds	r3, r3, #1
	mla	r2, r1, r2, r5
	strb	r0, [r2, #45]
	b	.L763
.L769:
	movs	r4, #1
	b	.L758
.L757:
	ldr	r3, .L781+48
	ldrb	r3, [r3]	@ zero_extendqisi2
	cbz	r3, .L770
	ldr	r3, .L781+52
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, #0
	ite	eq
	moveq	r4, #1
	movne	r4, #2
	b	.L759
.L770:
	movs	r4, #1
	b	.L759
.L761:
	ldr	r3, .L781+8
	mov	r10, #255
	strh	r6, [r3, #2104]	@ movhi
	mov	r8, r3
	movs	r3, #48
.L764:
	subs	r2, r7, r6
	uxth	r2, r2
	cmp	r4, r2
	bls	.L755
	ldr	r2, [fp]
	movs	r1, #0
	str	r3, [sp, #4]
	ldrb	r0, [r2, r7]	@ zero_extendqisi2
	strb	r10, [r2, r7]
	adds	r7, r7, #1
	mla	r2, r3, r0, r5
	add	r0, r0, r0, lsl #1
	strb	r1, [r2, #45]
	add	r0, r5, r0, lsl #4
	bl	zbuf_free
	ldrb	r2, [r8, #7]	@ zero_extendqisi2
	ldr	r3, [sp, #4]
	subs	r2, r2, #1
	strb	r2, [r8, #7]
	b	.L764
.L782:
	.align	2
.L781:
	.word	.LANCHOR55
	.word	.LANCHOR63
	.word	.LANCHOR70
	.word	.LC54
	.word	.LANCHOR77
	.word	.LC0
	.word	.LANCHOR35
	.word	.LANCHOR12
	.word	.LANCHOR79
	.word	.LANCHOR82
	.word	.LANCHOR83
	.word	.LANCHOR36
	.word	.LANCHOR80
	.word	.LANCHOR81
	.word	.LANCHOR78
	.size	gc_write_completed, .-gc_write_completed
	.section	.text.gc_get_src_blk,"ax",%progbits
	.align	1
	.global	gc_get_src_blk
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	gc_get_src_blk, %function
gc_get_src_blk:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	ldr	r3, .L792
	push	{r4, r5, r6, r7, lr}
	ldr	r2, [r3]
	ldr	r3, .L792+4
	ldrh	r4, [r2, #124]
	ldrb	r1, [r3]	@ zero_extendqisi2
	cbz	r4, .L784
	add	r3, r2, #392
	movs	r4, #1
.L785:
	add	r6, r3, #128
	movw	r5, #65535
.L789:
	mov	r7, r3
	ldrh	r0, [r3], #2
	cmp	r0, r5
	beq	.L787
	strh	r5, [r7]	@ movhi
	cbz	r4, .L788
	ldrh	r3, [r2, #124]
	subs	r3, r3, #1
	strh	r3, [r2, #124]	@ movhi
	pop	{r4, r5, r6, r7, pc}
.L784:
	add	r3, r1, #60
	ldrh	r3, [r2, r3, lsl #1]
	cbz	r3, .L790
	add	r3, r2, r1, lsl #7
	adds	r3, r3, #136
	b	.L785
.L788:
	add	r2, r2, r1, lsl #1
	ldrh	r3, [r2, #120]
	subs	r3, r3, #1
	strh	r3, [r2, #120]	@ movhi
	pop	{r4, r5, r6, r7, pc}
.L787:
	cmp	r3, r6
	bne	.L789
	pop	{r4, r5, r6, r7, pc}
.L790:
	movw	r0, #65535
	pop	{r4, r5, r6, r7, pc}
.L793:
	.align	2
.L792:
	.word	.LANCHOR12
	.word	.LANCHOR84
	.size	gc_get_src_blk, .-gc_get_src_blk
	.section	.text.gc_free_temp_buf,"ax",%progbits
	.align	1
	.global	gc_free_temp_buf
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	gc_free_temp_buf, %function
gc_free_temp_buf:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r3, r4, r5, r6, r7, lr}
	ldr	r5, .L808
	ldrb	r0, [r5, #7]	@ zero_extendqisi2
	cbz	r0, .L794
	ldr	r3, .L808+4
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, #1
	bhi	.L801
	ldr	r3, .L808+8
	movs	r7, #48
	ldrh	r4, [r5, #2104]
	ldr	r6, .L808+12
	ldrh	r2, [r3]
	ldr	r3, .L808+16
	add	r1, r4, #24
	ldr	r0, .L808+20
	ldrb	r3, [r3]	@ zero_extendqisi2
	muls	r2, r3, r2
	cmp	r2, r1
	it	cs
	movcs	r2, r1
	ldr	r1, [r6]
.L796:
	cmp	r4, r2
	bcc	.L799
.L801:
	movs	r0, #0
.L794:
	pop	{r3, r4, r5, r6, r7, pc}
.L799:
	ldrb	r3, [r1, r4]	@ zero_extendqisi2
	cmp	r3, #255
	beq	.L797
	mla	ip, r7, r3, r0
	ldrb	ip, [ip, #45]	@ zero_extendqisi2
	cmp	ip, #0
	bne	.L797
	add	r3, r3, r3, lsl #1
	add	r0, r0, r3, lsl #4
	bl	zbuf_free
	ldr	r3, .L808+24
	ldr	r3, [r3]
	lsls	r3, r3, #23
	bpl	.L798
	ldr	r3, [r6]
	mov	r1, r4
	ldr	r0, .L808+28
	ldrb	r2, [r3, r4]	@ zero_extendqisi2
	bl	printf
.L798:
	ldr	r3, [r6]
	movs	r2, #255
	movs	r0, #1
	strb	r2, [r3, r4]
	ldrb	r3, [r5, #7]	@ zero_extendqisi2
	subs	r3, r3, #1
	strb	r3, [r5, #7]
	pop	{r3, r4, r5, r6, r7, pc}
.L797:
	adds	r4, r4, #1
	b	.L796
.L809:
	.align	2
.L808:
	.word	.LANCHOR70
	.word	.LANCHOR57
	.word	.LANCHOR85
	.word	.LANCHOR82
	.word	.LANCHOR79
	.word	.LANCHOR55
	.word	.LANCHOR19
	.word	.LC55
	.size	gc_free_temp_buf, .-gc_free_temp_buf
	.section	.text.get_ink_scaned_blk,"ax",%progbits
	.align	1
	.global	get_ink_scaned_blk
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	get_ink_scaned_blk, %function
get_ink_scaned_blk:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	ldr	r2, .L813
	ldrh	r3, [r2, #2108]
	cbz	r3, .L812
	add	r1, r2, r3, lsl #1
	subs	r3, r3, #1
	strh	r3, [r2, #2108]	@ movhi
	ldrh	r0, [r1, #2108]
	bx	lr
.L812:
	movw	r0, #65535
	bx	lr
.L814:
	.align	2
.L813:
	.word	.LANCHOR70
	.size	get_ink_scaned_blk, .-get_ink_scaned_blk
	.section	.text.print_gc_debug_info,"ax",%progbits
	.align	1
	.global	print_gc_debug_info
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	print_gc_debug_info, %function
print_gc_debug_info:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r0, r1, r2, r3, r4, lr}
	ldr	r4, .L816
	ldr	r0, .L816+4
	ldrh	r4, [r4]
	ldrh	r3, [r0, #2102]
	ldrh	r2, [r0, #2]
	ldrh	r1, [r0]
	str	r4, [sp, #8]
	ldrb	r0, [r0, #7]	@ zero_extendqisi2
	str	r0, [sp, #4]
	ldr	r0, .L816+8
	ldrb	r0, [r0]	@ zero_extendqisi2
	str	r0, [sp]
	ldr	r0, .L816+12
	bl	printf
	add	sp, sp, #16
	@ sp needed
	pop	{r4, pc}
.L817:
	.align	2
.L816:
	.word	.LANCHOR86
	.word	.LANCHOR70
	.word	.LANCHOR57
	.word	.LC56
	.size	print_gc_debug_info, .-print_gc_debug_info
	.section	.text._list_pop_index_node,"ax",%progbits
	.align	1
	.global	_list_pop_index_node
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	_list_pop_index_node, %function
_list_pop_index_node:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r3, r4, r5, r6, r7, lr}
	ldr	r5, [r0]
	cbz	r5, .L824
	ldr	r3, .L825
	movw	r6, #65535
	movs	r7, #6
	ldr	r4, [r3]
.L820:
	cbnz	r1, .L821
.L823:
	subs	r4, r5, r4
	asrs	r3, r4, #1
	ldr	r4, .L825+4
	muls	r4, r3, r4
	uxth	r1, r4
	bl	_list_remove_node
	movw	r3, #65535
	uxth	r0, r4
	strh	r3, [r5]	@ movhi
	strh	r3, [r5, #2]	@ movhi
	pop	{r3, r4, r5, r6, r7, pc}
.L821:
	ldrh	r3, [r5]
	cmp	r3, r6
	beq	.L823
	subs	r1, r1, #1
	mla	r5, r7, r3, r4
	uxth	r1, r1
	b	.L820
.L824:
	movw	r0, #65535
	pop	{r3, r4, r5, r6, r7, pc}
.L826:
	.align	2
.L825:
	.word	.LANCHOR4
	.word	-1431655765
	.size	_list_pop_index_node, .-_list_pop_index_node
	.section	.text._list_get_gc_head_node,"ax",%progbits
	.align	1
	.global	_list_get_gc_head_node
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	_list_get_gc_head_node, %function
_list_get_gc_head_node:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	ldr	r0, [r0]
	push	{r4, lr}
	cbz	r0, .L832
	ldr	r3, .L834
	movw	r2, #65535
	movs	r4, #6
	ldr	r3, [r3]
.L829:
	cbz	r1, .L830
	ldrh	r0, [r0]
	cmp	r0, r2
	bne	.L831
	pop	{r4, pc}
.L831:
	subs	r1, r1, #1
	mla	r0, r4, r0, r3
	uxth	r1, r1
	b	.L829
.L832:
	movw	r0, #65535
	pop	{r4, pc}
.L830:
	subs	r0, r0, r3
	asrs	r3, r0, #1
	ldr	r0, .L834+4
	muls	r0, r3, r0
	uxth	r0, r0
	pop	{r4, pc}
.L835:
	.align	2
.L834:
	.word	.LANCHOR4
	.word	-1431655765
	.size	_list_get_gc_head_node, .-_list_get_gc_head_node
	.section	.text.gc_search_src_blk,"ax",%progbits
	.align	1
	.global	gc_search_src_blk
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	gc_search_src_blk, %function
gc_search_src_blk:
	@ args = 0, pretend = 0, frame = 24
	@ frame_needed = 0, uses_anonymous_args = 0
	ldr	r3, .L947
	push	{r4, r5, r6, r7, r8, r10, fp, lr}
	sub	sp, sp, #32
	str	r0, [sp, #12]
	mov	r6, r2
	ldr	r0, [r3]
	ldr	r3, [sp, #12]
	str	r1, [sp, #20]
	adds	r3, r3, #60
	ldrh	r7, [r0, r3, lsl #1]
	cbz	r7, .L837
	mov	r0, r7
.L836:
	add	sp, sp, #32
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r10, fp, pc}
.L837:
	ldr	r3, .L947+4
	ldrh	r2, [r3, #52]
	cmp	r2, #1
	bhi	.L839
	ldr	r1, .L947+8
	strh	r7, [r1]	@ movhi
	ldr	r1, .L947+12
	strh	r7, [r1]	@ movhi
	ldr	r1, .L947+16
	strh	r7, [r1]	@ movhi
.L839:
	ldr	r1, [sp, #12]
	cmp	r1, #0
	bne	.L840
	ldr	r7, .L947+12
	mov	r8, r1
	mov	r4, r1
.L841:
	uxth	r3, r8
	cmp	r6, r3
	blt	.L846
	ldrh	r10, [r7]
	ldr	r0, .L947+20
	mov	r1, r10
	bl	_list_get_gc_head_node
	add	r2, r10, #1
	movw	r3, #65535
	uxth	r2, r2
	cmp	r0, r3
	mov	r5, r0
	strh	r2, [r7]	@ movhi
	beq	.L842
	ldr	r3, .L947+24
	ldr	r10, .L947+48
	ldr	r3, [r3]
	tst	r3, #256
	beq	.L843
	ldr	r3, [r10]
	mov	r1, r0
	ldrh	r3, [r3, r0, lsl #1]
	ldr	r0, .L947+28
	bl	printf
.L843:
	ldr	r3, [r10]
	ldrh	r2, [r3, r5, lsl #1]
	ldr	r3, .L947+32
	ldrh	r3, [r3]
	cmp	r2, r3
	bcs	.L842
	movs	r2, #0
	mov	r0, r5
	mov	r1, r2
	bl	gc_add_sblk
	cmp	r0, #0
	beq	.L845
	adds	r4, r4, #1
	uxth	r4, r4
	cmp	r4, r6
	bcc	.L845
.L846:
	ldr	r3, [sp, #20]
	lsls	r0, r3, #30
	bpl	.L848
	ldr	r3, .L947+36
	ldrh	r3, [r3]
	cmp	r3, #32
	bls	.L848
	ldr	r5, .L947+40
	mov	r10, #0
	ldr	r7, .L947+16
.L849:
	uxth	r3, r10
	cmp	r6, r3
	blt	.L853
	ldrh	r8, [r7]
	ldr	r0, .L947+44
	mov	r1, r8
	add	r8, r8, #1
	bl	_list_get_gc_head_node
	movw	r2, #65535
	strh	r8, [r7]	@ movhi
	cmp	r0, r2
	beq	.L850
	ldr	r2, .L947+48
	ldrh	r3, [r5]
	ldr	r2, [r2]
	ldrh	r2, [r2, r0, lsl #1]
	cmp	r2, r3
	bcs	.L850
	movs	r2, #0
	mov	r1, r2
	bl	gc_add_sblk
	cmp	r0, #0
	beq	.L852
	adds	r4, r4, #1
	uxth	r4, r4
	cmp	r4, r6
	bcc	.L852
.L853:
	cmp	r4, r6
	ldr	r1, .L947+52
	bcs	.L855
	ldr	r3, .L947+56
	ldrh	r1, [r1]
	ldrh	r2, [r5]
	ldrh	r0, [r3]
	ldr	r3, .L947+60
	ldrb	r3, [r3]	@ zero_extendqisi2
	muls	r3, r0, r3
	sub	r3, r3, r1, lsr #2
	cmp	r2, r3
	bge	.L848
	add	r2, r2, r1, lsr #3
	strh	r2, [r5]	@ movhi
.L848:
	ldr	r3, [sp, #20]
	lsls	r1, r3, #31
	bpl	.L856
	uxth	r5, r6
	cmp	r4, r5
	bcs	.L856
	ldr	r10, .L947+8
	movs	r7, #0
	ldr	r8, .L947+68
.L861:
	ldrh	fp, [r10]
	mov	r0, r8
	mov	r1, fp
	add	fp, fp, #1
	bl	_list_get_gc_head_node
	movw	r3, #65535
	strh	fp, [r10]	@ movhi
	cmp	r0, r3
	beq	.L857
	movs	r2, #0
	mov	r1, r2
	bl	gc_add_sblk
	cmp	r0, #0
	beq	.L858
	adds	r4, r4, #1
	uxth	r4, r4
	cmp	r5, r4
	bhi	.L858
.L859:
	ldr	r3, .L947+52
	ldr	r2, .L947+32
	ldrh	r1, [r3]
	ldrh	r3, [r2]
	cmp	r3, r1, lsr #1
	bls	.L856
	sub	r3, r3, r1, lsr #3
	b	.L946
.L842:
	movs	r3, #0
	strh	r3, [r7]	@ movhi
	b	.L846
.L845:
	add	r8, r8, #1
	b	.L841
.L850:
	movs	r3, #0
	strh	r3, [r7]	@ movhi
	b	.L853
.L852:
	add	r10, r10, #1
	b	.L849
.L855:
	ldrh	r3, [r5]
	ldrh	r2, [r1]
	cmp	r3, r2
	itt	hi
	subhi	r3, r3, r2, lsr #3
	strhhi	r3, [r5]	@ movhi
	b	.L848
.L857:
	movs	r3, #0
	strh	r3, [r10]	@ movhi
.L860:
	cmp	r4, r5
	bcs	.L859
	ldr	r2, .L947+32
	ldr	r1, .L947+52
	ldrh	r3, [r2]
	ldrh	r1, [r1]
	cmp	r3, r1
	bcs	.L856
	add	r3, r3, r1, lsr #3
.L946:
	strh	r3, [r2]	@ movhi
.L856:
	ldr	r3, .L947+24
	ldr	r3, [r3]
	lsls	r3, r3, #23
	bpl	.L892
	str	r6, [sp]
	mov	r3, r4
	ldr	r2, [sp, #20]
	ldr	r1, [sp, #12]
	ldr	r0, .L947+64
	bl	printf
.L892:
	mov	r0, r4
	b	.L836
.L858:
	adds	r7, r7, #1
	uxth	r3, r7
	cmp	r5, r3
	bhi	.L861
	b	.L860
.L948:
	.align	2
.L947:
	.word	.LANCHOR12
	.word	.LANCHOR70
	.word	.LANCHOR87
	.word	.LANCHOR88
	.word	.LANCHOR89
	.word	.LANCHOR90
	.word	.LANCHOR19
	.word	.LC57
	.word	.LANCHOR69
	.word	.LANCHOR91
	.word	.LANCHOR93
	.word	.LANCHOR92
	.word	.LANCHOR11
	.word	.LANCHOR94
	.word	.LANCHOR85
	.word	.LANCHOR79
	.word	.LC58
	.word	.LANCHOR95
.L840:
	ldr	r1, .L949
	cmp	r6, #1
	ldr	r4, .L949+4
	ldrb	r1, [r1]	@ zero_extendqisi2
	ldrh	r4, [r4]
	smulbb	r1, r1, r4
	uxth	r1, r1
	str	r1, [sp, #16]
	bne	.L862
	cbz	r2, .L862
	ldrh	r0, [r0, #80]
	movw	r1, #65535
	cmp	r0, r1
	beq	.L895
	ldr	r0, [sp, #16]
	ldrh	r1, [r3, #2102]
	subs	r1, r0, r1
	uxth	r1, r1
	str	r1, [sp, #16]
.L895:
	movs	r6, #8
.L862:
	movs	r5, #0
	strh	r5, [r3, #2180]	@ movhi
	ldr	r3, .L949+8
	strh	r5, [r3]	@ movhi
	ldr	r3, [sp, #20]
	ands	r3, r3, #1
	str	r3, [sp, #24]
	beq	.L896
	ldr	r3, .L949+12
	ldr	r1, .L949+16
	ldrh	r3, [r3]
	ldrh	r1, [r1]
	cmp	r3, r1, lsr #2
	bhi	.L864
	ldr	r1, .L949+20
	ldrh	r1, [r1]
	cmp	r1, r3
	bcs	.L897
.L864:
	cmp	r2, #1
	bls	.L866
.L868:
	movs	r4, #0
.L867:
	ldr	r10, .L949+64
	movs	r5, #0
	mov	r8, #64
.L871:
	ldrh	r3, [r10]
	ldr	r0, .L949+24
	mov	r1, r3
	str	r3, [sp, #28]
	bl	_list_get_gc_head_node
	movw	r2, #65535
	mov	fp, r0
	cmp	r0, r2
	beq	.L869
	ldr	r3, [sp, #28]
	ldr	r2, [sp, #12]
	adds	r1, r3, #1
	strh	r1, [r10]	@ movhi
	movs	r1, #0
	bl	gc_add_sblk
	cmp	r0, #0
	beq	.L870
	ldr	r3, .L949+28
	adds	r4, r4, #1
	uxth	r4, r4
	ldr	r3, [r3]
	cmp	r4, r6
	ldrh	r3, [r3, fp, lsl #1]
	add	r5, r5, r3
	uxth	r5, r5
	bcs	.L865
	ldr	r3, [sp, #16]
	cmp	r3, r5
	bcc	.L865
	ldr	r3, .L949+20
	ldr	r2, .L949+12
	ldrh	r3, [r3]
	ldrh	r2, [r2]
	cmp	r3, r2, lsl #1
	ble	.L870
.L865:
	ldr	r3, .L949+20
	ldrh	r2, [r3]
	ldr	r3, .L949+16
	ldrh	r3, [r3]
	cmp	r2, r3, lsr #2
	bhi	.L893
	ldr	r3, .L949+12
	ldrh	r3, [r3]
	adds	r3, r3, #8
	cmp	r2, r3
	ble	.L863
.L893:
	ldr	r3, [sp, #16]
	cmp	r3, r5
	bls	.L863
	ldr	r10, .L949+56
	mov	r8, #64
.L874:
	ldrh	r3, [r10]
	ldr	r0, .L949+32
	mov	r1, r3
	str	r3, [sp, #28]
	bl	_list_get_gc_head_node
	movw	r2, #65535
	mov	fp, r0
	cmp	r0, r2
	ldr	r3, [sp, #28]
	beq	.L872
	adds	r3, r3, #1
	ldr	r2, [sp, #12]
	movs	r1, #0
	strh	r3, [r10]	@ movhi
	bl	gc_add_sblk
	cmp	r0, #0
	beq	.L873
	ldr	r3, .L949+28
	adds	r4, r4, #1
	uxth	r4, r4
	ldr	r3, [r3]
	cmp	r4, r6
	ldrh	r3, [r3, fp, lsl #1]
	add	r5, r5, r3
	uxth	r5, r5
	bcs	.L863
	ldr	r3, [sp, #16]
	cmp	r3, r5
	bcs	.L873
.L863:
	ldr	r3, [sp, #20]
	lsls	r2, r3, #30
	bpl	.L875
	ldr	r3, .L949+36
	ldrh	r3, [r3]
	cmp	r3, #32
	bls	.L875
	ldr	r3, [sp, #16]
	cmp	r5, r3
	bcs	.L875
	ldr	r10, .L949+68
	movs	r3, #64
.L881:
	ldrh	fp, [r10]
	ldr	r0, .L949+40
	str	r3, [sp, #28]
	mov	r1, fp
	bl	_list_get_gc_head_node
	movw	r2, #65535
	mov	r8, r0
	cmp	r0, r2
	beq	.L876
	cmp	r6, #1
	add	r1, fp, #1
	strh	r1, [r10]	@ movhi
	ldr	r3, [sp, #28]
	bne	.L877
	ldr	r2, .L949
	ldr	r1, .L949+4
	ldrb	r2, [r2]	@ zero_extendqisi2
	ldrh	r1, [r1]
	smulbb	r2, r2, r1
	ldr	r1, .L949+44
	ldrh	r1, [r1]
	sub	r2, r2, r1, lsr #3
	ldr	r1, .L949+48
	strh	r2, [r1]	@ movhi
.L877:
	ldr	fp, .L949+28
	str	r3, [sp, #28]
	ldr	r2, [fp]
	ldrh	r1, [r2, r8, lsl #1]
	ldr	r2, .L949+48
	ldrh	r2, [r2]
	cmp	r1, r2
	bcs	.L878
	ldr	r2, [sp, #12]
	movs	r1, #0
	mov	r0, r8
	bl	gc_add_sblk
	ldr	r3, [sp, #28]
	cmp	r0, #0
	beq	.L879
	ldr	r2, [fp]
	adds	r4, r4, #1
	uxth	r4, r4
	adds	r7, r7, #1
	uxth	r7, r7
	ldrh	r2, [r2, r8, lsl #1]
	cmp	r4, r6
	add	r5, r5, r2
	uxth	r5, r5
	bcs	.L880
	ldr	r2, [sp, #16]
	cmp	r2, r5
	bcs	.L879
.L880:
	cmp	r4, r6
	ldr	r0, .L949+44
	ldr	r2, .L949+48
	bcc	.L882
	cmp	r7, #0
	bne	.L883
	ldr	r3, .L949+36
	ldrh	r1, [r3]
	ldr	r3, .L949+52
	ldrh	r3, [r3]
	cmp	r1, r3
	bls	.L883
.L882:
	ldrh	r3, [r0]
	ldrh	r1, [r2]
	lsrs	r0, r3, #3
	ldr	r3, .L949+4
	ldrh	r7, [r3]
	ldr	r3, .L949
	ldrb	r3, [r3]	@ zero_extendqisi2
	muls	r3, r7, r3
	subs	r3, r3, r0
	cmp	r1, r3
	bge	.L875
	adds	r3, r1, r0
	strh	r3, [r2]	@ movhi
.L875:
	ldr	r3, [sp, #24]
	cmp	r3, #0
	beq	.L856
	uxth	fp, r6
	cmp	r4, fp
	bcs	.L856
	ldr	r3, [sp, #16]
	cmp	r5, r3
	bcs	.L856
	ldr	r3, .L949+56
	mov	r8, #64
.L891:
	ldrh	r2, [r3]
	ldr	r0, .L949+32
	str	r3, [sp, #28]
	mov	r1, r2
	str	r2, [sp, #24]
	bl	_list_get_gc_head_node
	movw	r1, #65535
	mov	r10, r0
	cmp	r0, r1
	ldr	r7, .L949+60
	ldr	r2, [sp, #24]
	ldr	r3, [sp, #28]
	beq	.L885
	adds	r2, r2, #1
	strh	r2, [r3]	@ movhi
	ldr	r2, .L949+28
	ldr	r2, [r2]
	ldrh	r1, [r2, r0, lsl #1]
	ldrh	r2, [r7]
	cmp	r1, r2
	bcs	.L886
	ldr	r2, .L949+16
	ldrh	r1, [r2]
	ldr	r2, .L949+20
	ldrh	r2, [r2]
	cmp	r2, r1, lsr #1
	bls	.L887
.L886:
	ldr	r2, [sp, #12]
	movs	r1, #0
	mov	r0, r10
	str	r3, [sp, #24]
	bl	gc_add_sblk
	ldr	r3, [sp, #24]
	cmp	r0, #0
	beq	.L888
	ldr	r2, .L949+28
	adds	r4, r4, #1
	uxth	r4, r4
	ldr	r2, [r2]
	cmp	fp, r4
	ldrh	r2, [r2, r10, lsl #1]
	add	r5, r5, r2
	uxth	r5, r5
	bls	.L889
	ldr	r2, [sp, #16]
	cmp	r2, r5
	bcs	.L888
.L890:
	ldr	r3, .L949+44
	ldrh	r2, [r3]
	ldrh	r3, [r7]
	cmp	r3, r2, lsr #1
	bls	.L856
	sub	r3, r3, r2, lsr #3
	strh	r3, [r7]	@ movhi
	b	.L856
.L950:
	.align	2
.L949:
	.word	.LANCHOR79
	.word	.LANCHOR85
	.word	.LANCHOR96
	.word	.LANCHOR97
	.word	.LANCHOR98
	.word	.LANCHOR99
	.word	.LANCHOR95
	.word	.LANCHOR11
	.word	.LANCHOR90
	.word	.LANCHOR91
	.word	.LANCHOR92
	.word	.LANCHOR94
	.word	.LANCHOR100
	.word	.LANCHOR101
	.word	.LANCHOR88
	.word	.LANCHOR102
	.word	.LANCHOR87
	.word	.LANCHOR89
.L866:
	ldr	r4, .L951
	lsrs	r3, r3, #2
	movs	r1, #0
	ldr	r0, .L951+4
	strh	r3, [r4]	@ movhi
	bl	_list_get_gc_head_node
	movw	r2, #65535
	cmp	r0, r2
	beq	.L868
	ldr	r2, .L951+8
	ldr	r1, [r2]
	ldr	r2, .L951+12
	ldrh	r3, [r1, r0, lsl #1]
	ldrh	r2, [r2]
	cmp	r3, r2, lsr #2
	bcs	.L868
	movs	r3, #1
	ldr	r2, [sp, #12]
	movs	r1, #0
	strh	r3, [r4]	@ movhi
	bl	gc_add_sblk
	adds	r4, r0, #0
	it	ne
	movne	r4, #1
	b	.L867
.L869:
	movs	r3, #0
	strh	r3, [r10]	@ movhi
	b	.L865
.L870:
	add	r8, r8, #-1
	uxth	r8, r8
	cmp	r8, #0
	bne	.L871
	b	.L865
.L872:
	cmp	r3, #64
	bls	.L863
	movs	r3, #0
	strh	r3, [r10]	@ movhi
	b	.L863
.L873:
	add	r8, r8, #-1
	uxth	r8, r8
	cmp	r8, #0
	bne	.L874
	b	.L863
.L896:
	ldr	r5, [sp, #24]
	mov	r4, r5
	b	.L863
.L878:
	ldr	r3, .L951+16
	movs	r2, #0
	strh	r2, [r3]	@ movhi
	b	.L880
.L876:
	movs	r3, #0
	strh	r3, [r10]	@ movhi
	b	.L880
.L879:
	subs	r3, r3, #1
	uxth	r3, r3
	cmp	r3, #0
	bne	.L881
	b	.L880
.L883:
	ldr	r1, .L951+20
	ldrh	r0, [r0]
	ldrh	r3, [r2]
	ldrb	r1, [r1]	@ zero_extendqisi2
	muls	r1, r0, r1
	cmp	r3, r1
	ble	.L856
	sub	r3, r3, r0, lsr #3
	b	.L946
.L885:
	cmp	r2, #64
	bls	.L887
	movs	r2, #0
	strh	r2, [r3]	@ movhi
.L887:
	cmp	r4, fp
	bcc	.L890
.L889:
	ldr	r3, .L951+12
	ldrh	r2, [r7]
	ldrh	r1, [r3]
	ldr	r3, .L951+20
	ldrb	r3, [r3]	@ zero_extendqisi2
	muls	r3, r1, r3
	subs	r3, r3, #32
	cmp	r2, r3
	itt	lt
	addlt	r2, r2, r1, lsr #3
	strhlt	r2, [r7]	@ movhi
	b	.L856
.L888:
	add	r8, r8, #-1
	uxth	r8, r8
	cmp	r8, #0
	bne	.L891
	b	.L887
.L897:
	mov	r4, r5
	b	.L865
.L952:
	.align	2
.L951:
	.word	.LANCHOR87
	.word	.LANCHOR95
	.word	.LANCHOR11
	.word	.LANCHOR94
	.word	.LANCHOR89
	.word	.LANCHOR79
	.size	gc_search_src_blk, .-gc_search_src_blk
	.section	.text.zftl_get_gc_node,"ax",%progbits
	.align	1
	.global	zftl_get_gc_node
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	zftl_get_gc_node, %function
zftl_get_gc_node:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	cmp	r1, #5
	bne	.L954
	mov	r1, r0
	ldr	r0, .L957
.L956:
	b	_list_get_gc_head_node
.L954:
	cmp	r1, #2
	mov	r1, r0
	ite	eq
	ldreq	r0, .L957+4
	ldrne	r0, .L957+8
	b	.L956
.L958:
	.align	2
.L957:
	.word	.LANCHOR92
	.word	.LANCHOR95
	.word	.LANCHOR90
	.size	zftl_get_gc_node, .-zftl_get_gc_node
	.section	.text.zftl_insert_free_list,"ax",%progbits
	.align	1
	.global	zftl_insert_free_list
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	zftl_insert_free_list, %function
zftl_insert_free_list:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	ldr	r3, .L963
	mov	r1, r0
	ldr	r3, [r3]
	add	r3, r3, r0, lsl #2
	ldrb	r3, [r3, #2]	@ zero_extendqisi2
	ands	r3, r3, #24
	bne	.L960
	ldr	r2, .L963+4
	ldr	r0, .L963+8
.L962:
	b	_insert_free_list
.L960:
	cmp	r3, #16
	ittee	eq
	ldreq	r2, .L963+12
	ldreq	r0, .L963+16
	ldrne	r2, .L963+20
	ldrne	r0, .L963+24
	b	.L962
.L964:
	.align	2
.L963:
	.word	.LANCHOR9
	.word	.LANCHOR103
	.word	.LANCHOR104
	.word	.LANCHOR105
	.word	.LANCHOR106
	.word	.LANCHOR107
	.word	.LANCHOR108
	.size	zftl_insert_free_list, .-zftl_insert_free_list
	.section	.text.zftl_insert_data_list,"ax",%progbits
	.align	1
	.global	zftl_insert_data_list
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	zftl_insert_data_list, %function
zftl_insert_data_list:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	ldr	r3, .L970
	mov	r1, r0
	ldr	r3, [r3]
	add	r3, r3, r0, lsl #2
	ldrb	r3, [r3, #2]	@ zero_extendqisi2
	and	r3, r3, #224
	cmp	r3, #64
	bne	.L966
	ldr	r2, .L970+4
	ldr	r0, .L970+8
.L969:
	b	_insert_data_list
.L966:
	cmp	r3, #96
	bne	.L967
	ldr	r2, .L970+12
	ldr	r0, .L970+16
	b	.L969
.L967:
	cmp	r3, #160
	bne	.L965
	ldr	r2, .L970+20
	ldr	r0, .L970+24
	b	.L969
.L965:
	bx	lr
.L971:
	.align	2
.L970:
	.word	.LANCHOR9
	.word	.LANCHOR97
	.word	.LANCHOR95
	.word	.LANCHOR99
	.word	.LANCHOR90
	.word	.LANCHOR91
	.word	.LANCHOR92
	.size	zftl_insert_data_list, .-zftl_insert_data_list
	.section	.text.zftl_gc_get_free_sblk,"ax",%progbits
	.align	1
	.global	zftl_gc_get_free_sblk
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	zftl_gc_get_free_sblk, %function
zftl_gc_get_free_sblk:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r0, r1, r2, r3, r4, r5, r6, r7, r8, lr}
	movw	r5, #65535
	ldr	r8, .L993+48
	mov	r4, r0
	mov	r6, r1
	ldr	r3, [r8]
	ldrh	r7, [r3, #588]
	cmp	r7, r5
	beq	.L973
	cbnz	r0, .L973
	mov	r1, r7
	ldr	r0, .L993
	bl	printf
	ldr	r3, [r8]
	strh	r5, [r3, #588]	@ movhi
.L974:
	mov	r0, r7
	add	sp, sp, #16
	@ sp needed
	pop	{r4, r5, r6, r7, r8, pc}
.L973:
	ldr	r3, .L993+4
	ldr	r5, .L993+8
	ldrh	r1, [r3]
	ldrh	r3, [r5]
	cmp	r1, r3
	bcc	.L975
	ldr	r2, .L993+12
	ldrh	r2, [r2]
	cmp	r2, r1
	bls	.L976
	cmp	r3, #0
	beq	.L976
.L975:
	cmp	r4, #0
	bne	.L977
	lsrs	r1, r3, #2
.L978:
	ldr	r2, .L993+8
	ldr	r0, .L993+16
.L992:
	bl	_list_pop_index_node
	uxth	r7, r0
	movw	r3, #65535
	cmp	r7, r3
	bne	.L981
	ldrh	r3, [r5]
	mov	r2, r6
	mov	r1, r7
	ldr	r0, .L993+20
	str	r3, [sp, #4]
	ldr	r3, .L993+12
	ldrh	r3, [r3]
	str	r3, [sp]
	ldr	r3, .L993+24
	ldr	r3, [r3]
	bl	printf
.L981:
	cmp	r4, #0
	beq	.L974
	ldr	r3, .L993+28
	ldr	r3, [r3]
	lsls	r3, r3, #23
	bpl	.L974
	ldr	r3, .L993+32
	ldr	r1, .L993+36
	ldr	r0, .L993+40
	ldr	r3, [r3]
	ldr	r1, [r1]
	ldrh	r1, [r1, r7, lsl #1]
	add	r2, r3, r7, lsl #2
	ldrb	r2, [r2, #2]	@ zero_extendqisi2
	str	r1, [sp, #8]
	ldrh	r1, [r3, r7, lsl #2]
	ubfx	r1, r1, #0, #11
	str	r1, [sp, #4]
	mov	r1, r7
	ldr	r3, [r3, r7, lsl #2]
	ubfx	r3, r3, #11, #8
	str	r3, [sp]
	ubfx	r3, r2, #3, #2
	lsrs	r2, r2, #5
	bl	printf
	b	.L974
.L977:
	rsb	r1, r1, r1, lsl #3
	ubfx	r1, r1, #3, #16
	b	.L978
.L976:
	cbz	r4, .L982
	lsrs	r1, r1, #3
.L980:
	ldr	r2, .L993+4
	ldr	r0, .L993+44
	b	.L992
.L982:
	mov	r1, r4
	b	.L980
.L994:
	.align	2
.L993:
	.word	.LC59
	.word	.LANCHOR105
	.word	.LANCHOR107
	.word	.LANCHOR103
	.word	.LANCHOR108
	.word	.LC60
	.word	.LANCHOR104
	.word	.LANCHOR19
	.word	.LANCHOR9
	.word	.LANCHOR11
	.word	.LC61
	.word	.LANCHOR106
	.word	.LANCHOR12
	.size	zftl_gc_get_free_sblk, .-zftl_gc_get_free_sblk
	.section	.text.zftl_get_free_sblk,"ax",%progbits
	.align	1
	.global	zftl_get_free_sblk
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	zftl_get_free_sblk, %function
zftl_get_free_sblk:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	cmp	r1, #5
	push	{r0, r1, r4, r5, r6, r7, r8, lr}
	mov	r5, r0
	mov	r6, r1
	bne	.L996
	ldr	r3, .L1017
	ldr	r2, .L1017+4
	ldrh	r3, [r3]
	ldrh	r1, [r2]
	cmp	r3, r1
	bcc	.L997
	ldr	r2, .L1017+8
	ldrh	r2, [r2]
	cmp	r2, r3
	bls	.L998
	cbz	r1, .L998
.L997:
	ldr	r2, .L1017+4
	lsrs	r1, r1, #1
.L1016:
	ldr	r0, .L1017+12
	b	.L1015
.L998:
	ldr	r2, .L1017
	movs	r1, #0
	ldr	r0, .L1017+16
.L1015:
	bl	_list_pop_index_node
	uxth	r4, r0
	movw	r3, #65535
	cmp	r4, r3
	bne	.L1001
	ldr	r3, .L1017+4
	mov	r2, r6
	mov	r1, r4
	ldr	r0, .L1017+20
	ldrh	r3, [r3]
	str	r3, [sp, #4]
	ldr	r3, .L1017+8
	ldrh	r3, [r3]
	str	r3, [sp]
	ldr	r3, .L1017+24
	ldr	r3, [r3]
	bl	printf
	b	.L1001
.L996:
	ldr	r8, .L1017+32
	movw	r7, #65535
	ldr	r3, [r8]
	ldrh	r4, [r3, #590]
	cmp	r4, r7
	beq	.L1000
	cmp	r1, #1
	beq	.L1000
	mov	r1, r4
	ldr	r0, .L1017+28
	bl	printf
	ldr	r3, [r8]
	strh	r7, [r3, #590]	@ movhi
.L1001:
	mov	r0, r4
	add	sp, sp, #8
	@ sp needed
	pop	{r4, r5, r6, r7, r8, pc}
.L1000:
	ldr	r3, .L1017+8
	ldr	r7, .L1017+4
	ldrh	r2, [r3]
	ldrh	r1, [r7]
	cmp	r2, r1
	bcc	.L1002
	ldr	r3, .L1017
	ldrh	r3, [r3]
	cmp	r3, r2
	bls	.L1003
	cbz	r1, .L1003
.L1002:
	bl	get_ink_scaned_blk
	movw	r3, #65535
	mov	r4, r0
	cmp	r0, r3
	bne	.L1001
	cmp	r6, #1
	ldr	r2, .L1017+4
	itt	eq
	ldrheq	r5, [r7]
	lsreq	r5, r5, #1
	mov	r1, r5
	b	.L1016
.L1003:
	cmp	r6, #1
	ldr	r0, .L1017+24
	it	eq
	lsreq	r5, r2, #1
	ldr	r2, .L1017+8
	mov	r1, r5
	b	.L1015
.L1018:
	.align	2
.L1017:
	.word	.LANCHOR105
	.word	.LANCHOR107
	.word	.LANCHOR103
	.word	.LANCHOR108
	.word	.LANCHOR106
	.word	.LC60
	.word	.LANCHOR104
	.word	.LC62
	.word	.LANCHOR12
	.size	zftl_get_free_sblk, .-zftl_get_free_sblk
	.section	.text.zftl_remove_data_node,"ax",%progbits
	.align	1
	.global	zftl_remove_data_node
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	zftl_remove_data_node, %function
zftl_remove_data_node:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	ldr	r3, .L1024
	mov	r1, r0
	ldr	r3, [r3]
	add	r3, r3, r0, lsl #2
	ldrb	r3, [r3, #2]	@ zero_extendqisi2
	and	r3, r3, #224
	cmp	r3, #64
	bne	.L1020
	ldr	r2, .L1024+4
	ldr	r0, .L1024+8
.L1023:
	b	_list_remove_node
.L1020:
	cmp	r3, #96
	bne	.L1021
	ldr	r2, .L1024+12
	ldr	r0, .L1024+16
	b	.L1023
.L1021:
	cmp	r3, #160
	bne	.L1019
	ldr	r2, .L1024+20
	ldr	r0, .L1024+24
	b	.L1023
.L1019:
	bx	lr
.L1025:
	.align	2
.L1024:
	.word	.LANCHOR9
	.word	.LANCHOR97
	.word	.LANCHOR95
	.word	.LANCHOR99
	.word	.LANCHOR90
	.word	.LANCHOR91
	.word	.LANCHOR92
	.size	zftl_remove_data_node, .-zftl_remove_data_node
	.section	.text.zftl_remove_free_node,"ax",%progbits
	.align	1
	.global	zftl_remove_free_node
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	zftl_remove_free_node, %function
zftl_remove_free_node:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	ldr	r3, .L1030
	mov	r1, r0
	ldr	r3, [r3]
	add	r3, r3, r0, lsl #2
	ldrb	r3, [r3, #2]	@ zero_extendqisi2
	ands	r3, r3, #24
	bne	.L1027
	ldr	r2, .L1030+4
	ldr	r0, .L1030+8
.L1029:
	b	_list_remove_node
.L1027:
	cmp	r3, #16
	ittee	eq
	ldreq	r2, .L1030+12
	ldreq	r0, .L1030+16
	ldrne	r2, .L1030+20
	ldrne	r0, .L1030+24
	b	.L1029
.L1031:
	.align	2
.L1030:
	.word	.LANCHOR9
	.word	.LANCHOR103
	.word	.LANCHOR104
	.word	.LANCHOR105
	.word	.LANCHOR106
	.word	.LANCHOR107
	.word	.LANCHOR108
	.size	zftl_remove_free_node, .-zftl_remove_free_node
	.section	.text.zftl_list_update_data_list,"ax",%progbits
	.align	1
	.global	zftl_list_update_data_list
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	zftl_list_update_data_list, %function
zftl_list_update_data_list:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	ldr	r3, .L1037
	mov	r1, r0
	ldr	r3, [r3]
	add	r3, r3, r0, lsl #2
	ldrb	r3, [r3, #2]	@ zero_extendqisi2
	and	r3, r3, #224
	cmp	r3, #64
	bne	.L1033
	ldr	r2, .L1037+4
	ldr	r0, .L1037+8
.L1036:
	b	_list_update_data_list
.L1033:
	cmp	r3, #96
	bne	.L1034
	ldr	r2, .L1037+12
	ldr	r0, .L1037+16
	b	.L1036
.L1034:
	cmp	r3, #160
	bne	.L1032
	ldr	r2, .L1037+20
	ldr	r0, .L1037+24
	b	.L1036
.L1032:
	bx	lr
.L1038:
	.align	2
.L1037:
	.word	.LANCHOR9
	.word	.LANCHOR97
	.word	.LANCHOR95
	.word	.LANCHOR99
	.word	.LANCHOR90
	.word	.LANCHOR91
	.word	.LANCHOR92
	.size	zftl_list_update_data_list, .-zftl_list_update_data_list
	.section	.text.print_list_info,"ax",%progbits
	.align	1
	.global	print_list_info
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	print_list_info, %function
print_list_info:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, lr}
	mov	r4, r0
	ldrh	r2, [r1]
	sub	sp, sp, #36
	ldr	r1, [r0]
	ldr	r0, .L1043
	bl	printf
	ldr	r4, [r4]
	cmp	r4, #0
	beq	.L1039
	ldr	r6, .L1043+4
	movs	r5, #0
	ldr	r7, .L1043+8
.L1042:
	ldr	r2, [r6]
	ldr	r0, .L1043+12
	ldr	r3, .L1043+16
	subs	r2, r4, r2
	asrs	r2, r2, #1
	ldr	r0, [r0]
	ldr	r1, [r3]
	muls	r2, r7, r2
	ldrh	r3, [r4]
	uxth	r2, r2
	ldrh	r0, [r0, r2, lsl #1]
	add	ip, r1, r2, lsl #2
	str	r0, [sp, #24]
	ldrh	r0, [r1, r2, lsl #2]
	ubfx	r0, r0, #0, #11
	str	r0, [sp, #20]
	ldr	r1, [r1, r2, lsl #2]
	ldr	r0, .L1043+20
	ubfx	r1, r1, #11, #8
	str	r1, [sp, #16]
	ldrb	r1, [ip, #2]	@ zero_extendqisi2
	ubfx	r1, r1, #3, #2
	str	r1, [sp, #12]
	ldrb	r1, [ip, #2]	@ zero_extendqisi2
	lsrs	r1, r1, #5
	str	r1, [sp, #8]
	ldrh	r1, [r4, #4]
	str	r1, [sp, #4]
	ldrh	r1, [r4, #2]
	str	r1, [sp]
	mov	r1, r5
	bl	printf
	ldrh	r4, [r4]
	movw	r3, #65535
	cmp	r4, r3
	beq	.L1039
	ldr	r3, [r6]
	movs	r2, #6
	adds	r5, r5, #1
	uxth	r5, r5
	mla	r4, r2, r4, r3
	ldr	r3, .L1043+24
	ldrh	r3, [r3]
	cmp	r3, r5
	bcs	.L1042
.L1039:
	add	sp, sp, #36
	@ sp needed
	pop	{r4, r5, r6, r7, pc}
.L1044:
	.align	2
.L1043:
	.word	.LC63
	.word	.LANCHOR4
	.word	-1431655765
	.word	.LANCHOR11
	.word	.LANCHOR9
	.word	.LC64
	.word	.LANCHOR109
	.size	print_list_info, .-print_list_info
	.section	.text.dump_all_list_info,"ax",%progbits
	.align	1
	.global	dump_all_list_info
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	dump_all_list_info, %function
dump_all_list_info:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r3, lr}
	ldr	r1, .L1046
	ldr	r0, .L1046+4
	bl	print_list_info
	ldr	r1, .L1046+8
	ldr	r0, .L1046+12
	bl	print_list_info
	ldr	r1, .L1046+16
	ldr	r0, .L1046+20
	bl	print_list_info
	ldr	r1, .L1046+24
	ldr	r0, .L1046+28
	bl	print_list_info
	ldr	r1, .L1046+32
	ldr	r0, .L1046+36
	bl	print_list_info
	ldr	r1, .L1046+40
	ldr	r0, .L1046+44
	pop	{r3, lr}
	b	print_list_info
.L1047:
	.align	2
.L1046:
	.word	.LANCHOR103
	.word	.LANCHOR104
	.word	.LANCHOR105
	.word	.LANCHOR106
	.word	.LANCHOR107
	.word	.LANCHOR108
	.word	.LANCHOR97
	.word	.LANCHOR95
	.word	.LANCHOR99
	.word	.LANCHOR90
	.word	.LANCHOR91
	.word	.LANCHOR92
	.size	dump_all_list_info, .-dump_all_list_info
	.section	.text.ftl_tmp_into_update,"ax",%progbits
	.align	1
	.global	ftl_tmp_into_update
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	ftl_tmp_into_update, %function
ftl_tmp_into_update:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	ldr	r3, .L1053
	ldr	r3, [r3]
	ldr	r2, [r3, #16]
	cmp	r2, #2048
	bls	.L1049
	ldr	r1, [r3, #20]
	add	r1, r1, r2, lsr #11
	ubfx	r2, r2, #0, #11
	str	r2, [r3, #16]
	str	r1, [r3, #20]
.L1049:
	ldr	r2, [r3, #24]
	cmp	r2, #2048
	bls	.L1050
	ldr	r1, [r3, #28]
	add	r1, r1, r2, lsr #11
	ubfx	r2, r2, #0, #11
	str	r2, [r3, #24]
	str	r1, [r3, #28]
.L1050:
	ldr	r2, [r3, #32]
	cmp	r2, #1024
	bls	.L1051
	ldr	r1, [r3, #36]
	add	r1, r1, r2, lsr #10
	ubfx	r2, r2, #0, #10
	str	r2, [r3, #32]
	str	r1, [r3, #36]
.L1051:
	ldr	r2, [r3, #40]
	cmp	r2, #1024
	bls	.L1048
	ldr	r1, [r3, #44]
	add	r1, r1, r2, lsr #10
	ubfx	r2, r2, #0, #10
	str	r2, [r3, #40]
	str	r1, [r3, #44]
.L1048:
	bx	lr
.L1054:
	.align	2
.L1053:
	.word	.LANCHOR110
	.size	ftl_tmp_into_update, .-ftl_tmp_into_update
	.global	__aeabi_idiv
	.section	.text.ftl_get_blk_list_in_sblk,"ax",%progbits
	.align	1
	.global	ftl_get_blk_list_in_sblk
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	ftl_get_blk_list_in_sblk, %function
ftl_get_blk_list_in_sblk:
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r0, r1, r2, r3, r4, r5, r6, r7, r8, r10, fp, lr}
	movs	r4, #0
	ldr	r3, .L1064
	mov	r8, r1
	mov	r5, r4
	ldr	r2, .L1064+4
	ldr	r3, [r3]
	ldrb	r10, [r2]	@ zero_extendqisi2
	ldr	r2, .L1064+8
	add	r3, r3, r0, lsl #2
	ldrb	r3, [r3, #3]	@ zero_extendqisi2
	uxth	r7, r10
	ldrb	fp, [r2]	@ zero_extendqisi2
	smulbb	r0, r0, r7
	ldr	r2, .L1064+12
	str	r3, [sp, #4]
	subs	r7, r7, #1
	ldr	r3, .L1064+16
	sxth	r7, r7
	uxth	r6, r0
	rsb	fp, fp, #24
	ldrb	r3, [r3]	@ zero_extendqisi2
.L1056:
	cmp	r5, r3
	blt	.L1060
	mov	r2, r4
	movw	r1, #65535
.L1061:
	cmp	r2, r3
	blt	.L1062
	mov	r0, r4
	add	sp, sp, #16
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r10, fp, pc}
.L1060:
	ldr	r1, [sp, #4]
	asrs	r1, r1, r5
	lsls	r1, r1, #31
	bmi	.L1057
	mov	r1, r10
	mov	r0, r5
	str	r2, [sp, #12]
	str	r3, [sp, #8]
	bl	__aeabi_idiv
	ldr	r2, [sp, #12]
	cmp	r10, #1
	ldr	r3, [sp, #8]
	ldrh	r1, [r2]
	sub	r1, fp, r1
	lsl	r0, r0, r1
	it	hi
	andhi	r1, r7, r5
	add	r0, r0, r6
	uxth	r0, r0
	it	hi
	addhi	r0, r0, r1
	strh	r0, [r8, r4, lsl #1]	@ movhi
	adds	r4, r4, #1
.L1057:
	adds	r5, r5, #1
	b	.L1056
.L1062:
	strh	r1, [r8, r2, lsl #1]	@ movhi
	adds	r2, r2, #1
	b	.L1061
.L1065:
	.align	2
.L1064:
	.word	.LANCHOR9
	.word	.LANCHOR75
	.word	.LANCHOR31
	.word	.LANCHOR74
	.word	.LANCHOR79
	.size	ftl_get_blk_list_in_sblk, .-ftl_get_blk_list_in_sblk
	.section	.text.ftl_erase_phy_blk,"ax",%progbits
	.align	1
	.global	ftl_erase_phy_blk
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	ftl_erase_phy_blk, %function
ftl_erase_phy_blk:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r3, r4, r5, r6, r7, lr}
	mov	r5, r1
	ldr	r3, .L1071
	ldr	r7, .L1071+4
	ldrb	r3, [r3]	@ zero_extendqisi2
	rsb	r4, r3, #24
	ldr	r3, .L1071+8
	ldrh	r3, [r3]
	subs	r3, r4, r3
	movs	r4, #1
	asr	r6, r0, r3
	lsls	r4, r4, r3
	ldr	r3, .L1071+12
	subs	r4, r4, #1
	uxtb	r6, r6
	ands	r4, r4, r0
	ldrb	r3, [r3]	@ zero_extendqisi2
	sxth	r4, r4
	cbz	r3, .L1067
	ldr	r3, .L1071+16
	ldrb	r3, [r3]	@ zero_extendqisi2
	cbnz	r3, .L1067
	ldrh	r2, [r7]
	clz	r1, r1
	lsrs	r1, r1, #5
	mov	r0, r6
	muls	r2, r4, r2
	bl	flash_erase_block_en
.L1067:
	ldrh	r2, [r7]
	uxtb	r1, r5
	mov	r0, r6
	muls	r2, r4, r2
	pop	{r3, r4, r5, r6, r7, lr}
	b	flash_erase_block_en
.L1072:
	.align	2
.L1071:
	.word	.LANCHOR31
	.word	.LANCHOR111
	.word	.LANCHOR74
	.word	.LANCHOR80
	.word	.LANCHOR81
	.size	ftl_erase_phy_blk, .-ftl_erase_phy_blk
	.section	.text.ftl_erase_sblk,"ax",%progbits
	.align	1
	.global	ftl_erase_sblk
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	ftl_erase_sblk, %function
ftl_erase_sblk:
	@ args = 0, pretend = 0, frame = 72
	@ frame_needed = 0, uses_anonymous_args = 0
	ldr	r2, .L1097
	push	{r4, r5, r6, r7, r8, r10, fp, lr}
	mov	r6, r0
	mov	r7, r1
	movs	r5, #0
	mov	r8, r2
	sub	sp, sp, #72
	ldr	r3, [r2]
	add	r3, r3, r0, lsl #2
	ldrb	r3, [r3, #3]	@ zero_extendqisi2
	str	r3, [sp, #4]
.L1074:
	ldr	r3, .L1097+4
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r5, r3
	bge	.L1085
	ldr	r3, .L1097+8
	movs	r4, #0
	ldrb	r2, [r3]	@ zero_extendqisi2
	ldr	r3, .L1097+12
	add	ip, r2, #-1
	ldrh	r0, [r3]
	mul	r10, r2, r5
	mov	r3, r4
	mul	lr, r2, r6
	b	.L1086
.L1076:
	ldr	r1, [sp, #4]
	add	fp, r3, r10
	asr	r1, r1, fp
	lsls	r1, r1, #31
	bmi	.L1075
	add	r1, sp, #72
	add	fp, r1, r4, lsl #2
	and	r1, r3, ip
	add	r1, r1, lr
	muls	r1, r0, r1
	adds	r4, r4, #1
	str	r1, [fp, #-64]
.L1075:
	adds	r3, r3, #1
.L1086:
	cmp	r3, r2
	blt	.L1076
	cmp	r2, #4
	bne	.L1077
	uxtb	fp, r7
	mov	r10, #0
.L1078:
	cmp	r10, r4
	bne	.L1079
.L1080:
	adds	r5, r5, #1
	b	.L1074
.L1079:
	add	r3, sp, #8
	mov	r1, fp
	ldr	r2, [r3, r10, lsl #2]
	uxtb	r0, r5
	add	r10, r10, #1
	bl	flash_erase_block_en
	b	.L1078
.L1077:
	cmp	r4, #2
	bne	.L1081
	ldr	r3, .L1097+16
	uxtb	r4, r5
	ldrb	r3, [r3]	@ zero_extendqisi2
	cbz	r3, .L1082
	ldr	r3, .L1097+20
	ldrb	r3, [r3]	@ zero_extendqisi2
	cbnz	r3, .L1082
	clz	r1, r7
	ldr	r3, [sp, #12]
	ldr	r2, [sp, #8]
	lsrs	r1, r1, #5
	mov	r0, r4
	bl	flash_erase_duplane_block
.L1082:
	ldr	r3, [sp, #12]
	uxtb	r1, r7
	ldr	r2, [sp, #8]
	mov	r0, r4
	bl	flash_erase_duplane_block
	b	.L1080
.L1081:
	cmp	r4, #1
	bne	.L1080
	ldr	r3, .L1097+16
	uxtb	r4, r5
	ldrb	r3, [r3]	@ zero_extendqisi2
	cbz	r3, .L1084
	ldr	r3, .L1097+20
	ldrb	r3, [r3]	@ zero_extendqisi2
	cbnz	r3, .L1084
	clz	r1, r7
	ldr	r2, [sp, #8]
	lsrs	r1, r1, #5
	mov	r0, r4
	bl	flash_erase_block_en
.L1084:
	ldr	r2, [sp, #8]
	uxtb	r1, r7
	mov	r0, r4
	bl	flash_erase_block_en
	b	.L1080
.L1085:
	ldr	r1, .L1097+24
	ldr	r0, [r8]
	cbnz	r7, .L1087
	ldrh	r2, [r0, r6, lsl #2]
	adds	r3, r2, #1
	ubfx	r3, r3, #0, #11
	bfi	r2, r3, #0, #11
	strh	r2, [r0, r6, lsl #2]	@ movhi
	ldr	r2, [r1]
	ldr	r1, [r2, #84]
	adds	r1, r1, #1
	str	r1, [r2, #84]
	ldrh	r1, [r2, #96]
	cmp	r1, r3
	bge	.L1089
	strh	r3, [r2, #96]	@ movhi
.L1089:
	movs	r0, #0
	add	sp, sp, #72
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r10, fp, pc}
.L1087:
	ldr	r2, [r0, r6, lsl #2]
	ubfx	r3, r2, #11, #8
	adds	r3, r3, #1
	uxtb	r3, r3
	bfi	r2, r3, #11, #8
	uxth	r3, r3
	str	r2, [r0, r6, lsl #2]
	ldr	r2, [r1]
	ldr	r1, [r2, #80]
	adds	r1, r1, #1
	str	r1, [r2, #80]
	ldrh	r1, [r2, #98]
	cmp	r1, r3
	it	cc
	strhcc	r3, [r2, #98]	@ movhi
	b	.L1089
.L1098:
	.align	2
.L1097:
	.word	.LANCHOR9
	.word	.LANCHOR112
	.word	.LANCHOR75
	.word	.LANCHOR111
	.word	.LANCHOR80
	.word	.LANCHOR81
	.word	.LANCHOR110
	.size	ftl_erase_sblk, .-ftl_erase_sblk
	.section	.text.ftl_alloc_sys_blk,"ax",%progbits
	.align	1
	.global	ftl_alloc_sys_blk
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	ftl_alloc_sys_blk, %function
ftl_alloc_sys_blk:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, lr}
	ldr	r4, .L1108
	ldr	r2, [r4]
	ldrh	r1, [r2, #136]
	cmp	r1, #63
	itt	hi
	movhi	r3, #0
	strhhi	r3, [r2, #136]	@ movhi
	ldrh	r3, [r2, #112]
	cbnz	r3, .L1101
	movw	r2, #1359
	ldr	r1, .L1108+4
	ldr	r0, .L1108+8
	bl	printf
.L1101:
	ldr	r3, [r4]
	movw	r4, #65535
	mov	r6, r4
	movs	r5, #0
.L1105:
	ldrh	r2, [r3, #136]
	add	r1, r3, r2, lsl #1
	adds	r1, r1, #158
.L1102:
	cmp	r2, #63
	ble	.L1104
	strh	r5, [r3, #136]	@ movhi
	b	.L1105
.L1104:
	ldrh	r0, [r1, #2]!
	cmp	r0, r4
	bne	.L1107
	adds	r2, r2, #1
	b	.L1102
.L1107:
	add	r1, r2, #80
	strh	r6, [r3, r1, lsl #1]	@ movhi
	strh	r2, [r3, #136]	@ movhi
	ldrh	r2, [r3, #112]
	subs	r2, r2, #1
	strh	r2, [r3, #112]	@ movhi
	pop	{r4, r5, r6, pc}
.L1109:
	.align	2
.L1108:
	.word	.LANCHOR110
	.word	.LANCHOR113
	.word	.LC0
	.size	ftl_alloc_sys_blk, .-ftl_alloc_sys_blk
	.section	.text.ftl_free_sys_blk,"ax",%progbits
	.align	1
	.global	ftl_free_sys_blk
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	ftl_free_sys_blk, %function
ftl_free_sys_blk:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, lr}
	mov	r5, r0
	ldr	r4, .L1118
	ldr	r2, [r4]
	ldrh	r1, [r2, #138]
	cmp	r1, #63
	itt	hi
	movhi	r3, #0
	strhhi	r3, [r2, #138]	@ movhi
	ldrh	r3, [r2, #112]
	cmp	r3, #63
	bls	.L1112
	movw	r2, #1386
	ldr	r1, .L1118+4
	ldr	r0, .L1118+8
	bl	printf
.L1112:
	ldr	r3, [r4]
	movs	r0, #0
	movw	r4, #65535
.L1116:
	ldrh	r2, [r3, #138]
	add	r1, r3, r2, lsl #1
	adds	r1, r1, #158
.L1113:
	cmp	r2, #63
	ble	.L1115
	strh	r0, [r3, #138]	@ movhi
	b	.L1116
.L1115:
	ldrh	r6, [r1, #2]!
	cmp	r6, r4
	bne	.L1114
	add	r1, r2, #80
	strh	r5, [r3, r1, lsl #1]	@ movhi
	strh	r2, [r3, #138]	@ movhi
	ldrh	r2, [r3, #112]
	adds	r2, r2, #1
	strh	r2, [r3, #112]	@ movhi
	pop	{r4, r5, r6, pc}
.L1114:
	adds	r2, r2, #1
	b	.L1113
.L1119:
	.align	2
.L1118:
	.word	.LANCHOR110
	.word	.LANCHOR114
	.word	.LC0
	.size	ftl_free_sys_blk, .-ftl_free_sys_blk
	.section	.text.ftl_info_data_recovery,"ax",%progbits
	.align	1
	.global	ftl_info_data_recovery
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	ftl_info_data_recovery, %function
ftl_info_data_recovery:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, lr}
	movw	r3, #65535
	ldrh	r4, [r0]
	cmp	r4, r3
	beq	.L1120
	ldr	r3, .L1129
	ldr	r5, [r3]
	add	r6, r5, r4, lsl #2
	ldrb	r3, [r6, #2]	@ zero_extendqisi2
	tst	r3, #224
	bne	.L1120
	ldrb	r2, [r0, #4]	@ zero_extendqisi2
	mov	r0, r4
	bfi	r3, r2, #5, #3
	strb	r3, [r6, #2]
	bl	zftl_remove_free_node
	ldrb	r3, [r6, #2]	@ zero_extendqisi2
	ldr	r2, .L1129+4
	tst	r3, #8
	ldr	r0, [r2]
	beq	.L1124
	ldrh	r1, [r0, #116]
	subs	r1, r1, #1
	strh	r1, [r0, #116]	@ movhi
.L1125:
	and	r3, r3, #224
	cmp	r3, #160
	bne	.L1127
	ldr	r3, [r5, r4, lsl #2]
	ldr	r2, [r2]
	ubfx	r1, r3, #11, #8
	adds	r1, r1, #1
	bfi	r3, r1, #11, #8
	str	r3, [r5, r4, lsl #2]
	ldrh	r3, [r2, #120]
	subs	r3, r3, #1
	strh	r3, [r2, #120]	@ movhi
	pop	{r4, r5, r6, pc}
.L1124:
	tst	r3, #24
	itete	eq
	ldrheq	r1, [r0, #114]
	ldrhne	r1, [r0, #118]
	addeq	r1, r1, #-1
	addne	r1, r1, #-1
	ite	eq
	strheq	r1, [r0, #114]	@ movhi
	strhne	r1, [r0, #118]	@ movhi
	b	.L1125
.L1127:
	ldrh	r1, [r5, r4, lsl #2]
	cmp	r3, #64
	add	r0, r1, #1
	bfi	r1, r0, #0, #11
	strh	r1, [r5, r4, lsl #2]	@ movhi
	bne	.L1128
	ldr	r2, [r2]
	ldrh	r3, [r2, #122]
	subs	r3, r3, #1
	strh	r3, [r2, #122]	@ movhi
	pop	{r4, r5, r6, pc}
.L1128:
	cmp	r3, #96
	itttt	eq
	ldreq	r2, [r2]
	ldrheq	r3, [r2, #124]
	addeq	r3, r3, #-1
	strheq	r3, [r2, #124]	@ movhi
.L1120:
	pop	{r4, r5, r6, pc}
.L1130:
	.align	2
.L1129:
	.word	.LANCHOR9
	.word	.LANCHOR110
	.size	ftl_info_data_recovery, .-ftl_info_data_recovery
	.section	.text.ftl_get_ppa_from_index,"ax",%progbits
	.align	1
	.global	ftl_get_ppa_from_index
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	ftl_get_ppa_from_index, %function
ftl_get_ppa_from_index:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r3, r4, r5, r6, r7, lr}
	mov	r4, r0
	ldr	r3, .L1135
	ldr	r5, [r3]
	ldr	r3, .L1135+4
	ldrh	r2, [r3]
	ldr	r3, .L1135+8
	ldrb	r3, [r3]	@ zero_extendqisi2
	mul	r1, r3, r2
	cmp	r0, r1
	itet	ge
	smulbbge	r3, r3, r2
	addlt	r5, r5, #16
	addge	r5, r5, #48
	ldrb	r6, [r5, #9]	@ zero_extendqisi2
	itt	ge
	subge	r4, r0, r3
	uxthge	r4, r4
	mov	r1, r6
	mov	r0, r4
	bl	__aeabi_idiv
	smulbb	r6, r0, r6
	movw	r3, #65535
	mov	r7, r0
	subs	r4, r4, r6
	uxth	r4, r4
	adds	r4, r4, #8
	ldrh	r4, [r5, r4, lsl #1]
	cmp	r4, r3
	bne	.L1134
	movw	r2, #1945
	ldr	r1, .L1135+12
	ldr	r0, .L1135+16
	bl	printf
.L1134:
	ldr	r3, .L1135+20
	ldrh	r0, [r3]
	mla	r0, r4, r0, r7
	pop	{r3, r4, r5, r6, r7, pc}
.L1136:
	.align	2
.L1135:
	.word	.LANCHOR12
	.word	.LANCHOR94
	.word	.LANCHOR79
	.word	.LANCHOR115
	.word	.LC0
	.word	.LANCHOR111
	.size	ftl_get_ppa_from_index, .-ftl_get_ppa_from_index
	.section	.text.lpa_hash_get_ppa,"ax",%progbits
	.align	1
	.global	lpa_hash_get_ppa
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	lpa_hash_get_ppa, %function
lpa_hash_get_ppa:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	ldr	r3, .L1141
	uxtb	r2, r0
	push	{r4, r5}
	ldrh	r3, [r3, r2, lsl #1]
	ldr	r2, .L1141+4
	ldr	r1, [r2]
	ldr	r2, .L1141+8
	ldr	r4, [r2]
	movw	r2, #65535
.L1138:
	cmp	r3, r2
	bne	.L1140
	mov	r0, #-1
	pop	{r4, r5}
	bx	lr
.L1140:
	ldr	r5, [r1, r3, lsl #2]
	cmp	r0, r5
	bne	.L1139
	mov	r0, r3
	pop	{r4, r5}
	b	ftl_get_ppa_from_index
.L1139:
	ldrh	r3, [r4, r3, lsl #1]
	b	.L1138
.L1142:
	.align	2
.L1141:
	.word	.LANCHOR116
	.word	.LANCHOR117
	.word	.LANCHOR118
	.size	lpa_hash_get_ppa, .-lpa_hash_get_ppa
	.section	.text.ftl_get_new_free_page,"ax",%progbits
	.align	1
	.global	ftl_get_new_free_page
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	ftl_get_new_free_page, %function
ftl_get_new_free_page:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	ldrh	r2, [r0]
	push	{r3, r4, r5, lr}
	movw	r3, #65535
	mov	r4, r0
	cmp	r2, r3
	bne	.L1144
	movw	r2, #2088
	ldr	r1, .L1151
	ldr	r0, .L1151+4
	bl	printf
.L1144:
	ldr	r3, .L1151+8
	ldrh	r2, [r4, #2]
	ldrh	r3, [r3]
	cmp	r2, r3
	bne	.L1145
	movw	r2, #2089
	ldr	r1, .L1151
	ldr	r0, .L1151+4
	bl	printf
.L1145:
	ldrh	r3, [r4, #6]
	cbnz	r3, .L1146
	movw	r2, #2090
	ldr	r1, .L1151
	ldr	r0, .L1151+4
	bl	printf
.L1146:
	ldrb	r3, [r4, #5]	@ zero_extendqisi2
	movw	r2, #65535
	movs	r1, #0
	adds	r3, r3, #8
	ldrh	r0, [r4, r3, lsl #1]
	ldr	r3, .L1151+12
	ldrb	r5, [r3]	@ zero_extendqisi2
.L1147:
	cmp	r0, r2
	ldrb	r3, [r4, #5]	@ zero_extendqisi2
	beq	.L1149
	ldr	r1, .L1151+16
	adds	r3, r3, #1
	uxtb	r3, r3
	ldrh	r2, [r4, #2]
	ldrh	r1, [r1]
	cmp	r5, r3
	strb	r3, [r4, #5]
	itttt	eq
	addeq	r3, r2, #1
	strheq	r3, [r4, #2]	@ movhi
	moveq	r3, #0
	strbeq	r3, [r4, #5]
	muls	r0, r1, r0
	ldrh	r1, [r4, #6]
	subs	r1, r1, #1
	strh	r1, [r4, #6]	@ movhi
	orrs	r0, r0, r2
	ldrh	r1, [r4, #10]
	adds	r1, r1, #1
	strh	r1, [r4, #10]	@ movhi
	pop	{r3, r4, r5, pc}
.L1149:
	adds	r3, r3, #1
	uxtb	r3, r3
	cmp	r3, r5
	strb	r3, [r4, #5]
	itttt	eq
	ldrheq	r3, [r4, #2]
	strbeq	r1, [r4, #5]
	addeq	r3, r3, #1
	strheq	r3, [r4, #2]	@ movhi
	ldrb	r3, [r4, #5]	@ zero_extendqisi2
	adds	r3, r3, #8
	ldrh	r0, [r4, r3, lsl #1]
	b	.L1147
.L1152:
	.align	2
.L1151:
	.word	.LANCHOR119
	.word	.LC0
	.word	.LANCHOR94
	.word	.LANCHOR79
	.word	.LANCHOR111
	.size	ftl_get_new_free_page, .-ftl_get_new_free_page
	.section	.text.ftl_ext_alloc_new_blk,"ax",%progbits
	.align	1
	.global	ftl_ext_alloc_new_blk
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	ftl_ext_alloc_new_blk, %function
ftl_ext_alloc_new_blk:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r3, r4, r5, lr}
	bl	ftl_alloc_sys_blk
	subs	r3, r0, #1
	movw	r2, #65533
	uxth	r3, r3
	mov	r4, r0
	cmp	r3, r2
	bls	.L1154
	movw	r2, #2125
	ldr	r1, .L1155
	ldr	r0, .L1155+4
	bl	printf
.L1154:
	ldr	r5, .L1155+8
	movs	r1, #0
	mov	r0, r4
	bl	ftl_erase_phy_blk
	ldr	r3, [r5]
	ldrh	r0, [r3, #130]
	bl	ftl_free_sys_blk
	ldr	r3, [r5]
	movs	r0, #0
	strh	r4, [r3, #130]	@ movhi
	strh	r0, [r3, #140]	@ movhi
	pop	{r3, r4, r5, pc}
.L1156:
	.align	2
.L1155:
	.word	.LANCHOR120
	.word	.LC0
	.word	.LANCHOR110
	.size	ftl_ext_alloc_new_blk, .-ftl_ext_alloc_new_blk
	.section	.text.ftl_total_vpn_update,"ax",%progbits
	.align	1
	.global	ftl_total_vpn_update
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	ftl_total_vpn_update, %function
ftl_total_vpn_update:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	ldr	r2, .L1168
	push	{r3, r4, r5, r6, r7, lr}
	mov	r1, r2
	ldrh	r3, [r2]
	cmp	r3, #4
	bhi	.L1158
	cbnz	r0, .L1158
	adds	r3, r3, #1
	strh	r3, [r2]	@ movhi
	pop	{r3, r4, r5, r6, r7, pc}
.L1158:
	ldr	r2, .L1168+4
	movs	r3, #0
	mov	r0, r3
	movw	ip, #65535
	strh	r3, [r1]	@ movhi
	ldrh	r5, [r2]
	ldr	r2, .L1168+8
	ldr	r6, [r2]
	ldr	r2, .L1168+12
	ldr	r7, [r2]
	mov	r2, r3
.L1160:
	uxth	r1, r3
	cmp	r5, r1
	bhi	.L1163
	ldr	r3, .L1168+16
	ldr	r4, [r3]
	ldr	r3, .L1168+20
	str	r2, [r4, #524]
	ldr	r3, [r3]
	str	r0, [r4, #528]
	ldrh	r1, [r3, #120]
	cbz	r1, .L1157
	bl	__aeabi_uidiv
	str	r0, [r4, #532]
.L1157:
	pop	{r3, r4, r5, r6, r7, pc}
.L1163:
	ldrh	r1, [r6, r3, lsl #1]
	cmp	r1, ip
	beq	.L1161
	add	r4, r7, r3, lsl #2
	ldrb	r4, [r4, #2]	@ zero_extendqisi2
	and	r4, r4, #224
	cmp	r4, #160
	ite	eq
	addeq	r0, r0, r1
	addne	r2, r2, r1
.L1161:
	adds	r3, r3, #1
	b	.L1160
.L1169:
	.align	2
.L1168:
	.word	.LANCHOR121
	.word	.LANCHOR8
	.word	.LANCHOR11
	.word	.LANCHOR9
	.word	.LANCHOR12
	.word	.LANCHOR110
	.size	ftl_total_vpn_update, .-ftl_total_vpn_update
	.section	.text.ftl_vpn_update,"ax",%progbits
	.align	1
	.global	ftl_vpn_update
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	ftl_vpn_update, %function
ftl_vpn_update:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, lr}
	mov	r4, r0
	bl	zftl_list_update_data_list
	ldr	r3, .L1173
	ldr	r3, [r3]
	ldrh	r3, [r3, r4, lsl #1]
	cbnz	r3, .L1172
	ldr	r3, .L1173+4
	movs	r0, #1
	str	r0, [r3]
	pop	{r4, pc}
.L1172:
	movs	r0, #0
	pop	{r4, pc}
.L1174:
	.align	2
.L1173:
	.word	.LANCHOR11
	.word	.LANCHOR122
	.size	ftl_vpn_update, .-ftl_vpn_update
	.section	.text.ftl_vpn_decrement,"ax",%progbits
	.align	1
	.global	ftl_vpn_decrement
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	ftl_vpn_decrement, %function
ftl_vpn_decrement:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r3, r4, r5, lr}
	movw	r3, #65535
	cmp	r0, r3
	mov	r5, r0
	beq	.L1176
	ldr	r3, .L1184
	ldr	r3, [r3]
	ldrh	r4, [r3, r0, lsl #1]
	cbnz	r4, .L1177
	ldr	r3, .L1184+4
	mov	r1, r0
	mov	r2, r4
	ldr	r3, [r3]
	add	r3, r3, r0, lsl #2
	ldr	r0, .L1184+8
	ldrb	r3, [r3, #2]	@ zero_extendqisi2
	lsrs	r3, r3, #5
	bl	printf
.L1182:
	movs	r0, #0
	pop	{r3, r4, r5, pc}
.L1177:
	subs	r4, r4, #1
	strh	r4, [r3, r0, lsl #1]	@ movhi
.L1176:
	ldr	r3, .L1184+12
	ldrh	r0, [r3]
	mov	r4, r3
	cmp	r5, r0
	beq	.L1182
	movw	r2, #65535
	cmp	r0, r2
	bne	.L1179
	strh	r5, [r3]	@ movhi
	b	.L1182
.L1179:
	bl	ftl_vpn_update
	ldr	r3, .L1184+16
	adds	r0, r0, #0
	it	ne
	movne	r0, #1
	ldrh	r1, [r4]
	strh	r5, [r4]	@ movhi
	ldrh	r2, [r3]
	adds	r2, r2, #1
	uxth	r2, r2
	cmp	r2, #7
	it	hi
	movhi	r2, #0
	strh	r2, [r3]	@ movhi
	ldrh	r2, [r3]
	ldr	r3, .L1184+20
	strh	r1, [r3, r2, lsl #1]	@ movhi
	pop	{r3, r4, r5, pc}
.L1185:
	.align	2
.L1184:
	.word	.LANCHOR11
	.word	.LANCHOR9
	.word	.LC65
	.word	.LANCHOR72
	.word	.LANCHOR123
	.word	.LANCHOR73
	.size	ftl_vpn_decrement, .-ftl_vpn_decrement
	.section	.text.lpa_hash_update_ppa,"ax",%progbits
	.align	1
	.global	lpa_hash_update_ppa
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	lpa_hash_update_ppa, %function
lpa_hash_update_ppa:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, r8, r10, fp, lr}
	uxtb	ip, r0
	ldr	r4, .L1197
	movw	r6, #65535
	mov	fp, r6
	ldr	r5, .L1197+4
	ldr	lr, [r4]
	ldr	r4, .L1197+8
	ldrh	r3, [r5, ip, lsl #1]
	ldr	r4, [r4]
.L1187:
	cmp	r3, fp
	beq	.L1191
	ldr	r7, [lr, r3, lsl #2]
	add	r8, lr, r3, lsl #2
	cmp	r0, r7
	bne	.L1188
	cmp	r6, fp
	mov	r10, #-1
	ite	eq
	ldrheq	r6, [r4, r3, lsl #1]
	ldrhne	r7, [r4, r3, lsl #1]
	str	r10, [r8]
	ite	eq
	strheq	r6, [r5, ip, lsl #1]	@ movhi
	strhne	r7, [r4, r6, lsl #1]	@ movhi
	movw	r6, #65535
	strh	r6, [r4, r3, lsl #1]	@ movhi
.L1191:
	ldrh	r3, [r5, ip, lsl #1]
	str	r0, [lr, r2, lsl #2]
	strh	r2, [r5, ip, lsl #1]	@ movhi
	strh	r3, [r4, r2, lsl #1]	@ movhi
	adds	r3, r1, #1
	beq	.L1193
	ldr	r3, .L1197+12
	ldrh	r2, [r3]
	ldr	r3, .L1197+16
	ldrb	r3, [r3]	@ zero_extendqisi2
	rsb	r3, r3, #24
	subs	r0, r3, r2
	movs	r3, #1
	lsls	r3, r3, r0
	lsr	r0, r1, r2
	ldr	r2, .L1197+20
	subs	r3, r3, #1
	ands	r0, r0, r3
	ldrb	r1, [r2]	@ zero_extendqisi2
	bl	__aeabi_uidiv
	uxth	r0, r0
	bl	ftl_vpn_decrement
.L1193:
	mov	r0, #-1
	pop	{r4, r5, r6, r7, r8, r10, fp, pc}
.L1188:
	mov	r6, r3
	ldrh	r3, [r4, r3, lsl #1]
	b	.L1187
.L1198:
	.align	2
.L1197:
	.word	.LANCHOR117
	.word	.LANCHOR116
	.word	.LANCHOR118
	.word	.LANCHOR74
	.word	.LANCHOR31
	.word	.LANCHOR75
	.size	lpa_hash_update_ppa, .-lpa_hash_update_ppa
	.section	.text.ftl_mask_bad_block,"ax",%progbits
	.align	1
	.global	ftl_mask_bad_block
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	ftl_mask_bad_block, %function
ftl_mask_bad_block:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	ldr	r3, .L1206
	push	{r0, r1, r2, r4, r5, r6, r7, r8, r10, lr}
	ldrb	r4, [r3]	@ zero_extendqisi2
	movs	r3, #1
	rsb	r1, r4, #24
	lsl	r4, r3, r4
	lsr	r2, r0, r1
	subs	r4, r4, #1
	ands	r4, r4, r2
	ldr	r2, .L1206+4
	uxtb	r4, r4
	ldrb	r5, [r2]	@ zero_extendqisi2
	smulbb	r2, r4, r5
	uxtb	r8, r2
	ldr	r2, .L1206+8
	ldrh	r6, [r2]
	lsr	r2, r0, r6
	subs	r0, r1, r6
	lsl	r0, r3, r0
	mov	r1, r5
	subs	r0, r0, #1
	ands	r0, r0, r2
	uxth	r10, r0
	bl	__aeabi_uidiv
	ldr	r3, .L1206+12
	cmp	r5, #1
	it	hi
	addhi	r2, r5, #-1
	mov	r6, r0
	it	hi
	andhi	r2, r2, r10
	uxth	r7, r0
	ldr	r3, [r3]
	itt	hi
	addhi	r2, r2, r8
	uxtbhi	r8, r2
	lsls	r3, r3, #17
	bpl	.L1201
	uxth	r3, r0
	str	r10, [sp]
	mov	r2, r8
	ldr	r0, .L1206+16
	mov	r1, r4
	bl	printf
.L1201:
	ldr	r3, .L1206+20
	ldrh	r3, [r3]
	cmp	r3, r7
	bls	.L1199
	ldr	r3, .L1206+24
	uxth	r6, r6
	movs	r2, #1
	lsl	r8, r2, r8
	ldr	r3, [r3]
	add	r6, r3, r6, lsl #2
	ldrb	r2, [r6, #3]	@ zero_extendqisi2
	orr	r2, r2, r8
	strb	r2, [r6, #3]
.L1199:
	add	sp, sp, #12
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r10, pc}
.L1207:
	.align	2
.L1206:
	.word	.LANCHOR31
	.word	.LANCHOR75
	.word	.LANCHOR74
	.word	.LANCHOR19
	.word	.LC66
	.word	.LANCHOR8
	.word	.LANCHOR9
	.size	ftl_mask_bad_block, .-ftl_mask_bad_block
	.section	.text.gc_free_bad_sblk,"ax",%progbits
	.align	1
	.global	gc_free_bad_sblk
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	gc_free_bad_sblk, %function
gc_free_bad_sblk:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, r8, r10, fp, lr}
	mov	r8, r0
	ldr	r4, .L1228
	ldr	r3, [r4, #2188]
	cbz	r3, .L1225
	mov	fp, #0
.L1210:
	ldr	r3, .L1228+4
	ldrb	r2, [r3]	@ zero_extendqisi2
	uxth	r3, fp
	cmp	r2, r3
	bhi	.L1220
.L1225:
	movs	r0, #0
	pop	{r4, r5, r6, r7, r8, r10, fp, pc}
.L1220:
	ldr	r3, .L1228+8
	uxth	r0, fp
	mov	r10, #0
	ldrb	r7, [r3]	@ zero_extendqisi2
	mov	r1, r7
	bl	__aeabi_idiv
	ldr	r3, .L1228+12
	uxth	r6, r7
	cmp	r7, #1
	ldrb	r5, [r3]	@ zero_extendqisi2
	ldr	r3, .L1228+16
	rsb	r5, r5, #24
	ldrh	r2, [r3]
	mov	r7, r3
	sub	r5, r5, r2
	lsl	r0, r0, r5
	smulbb	r5, r8, r6
	itt	hi
	addhi	r6, r6, #-1
	andhi	r6, r6, fp
	add	r5, r5, r0
	uxth	r5, r5
	itt	hi
	addhi	r5, r5, r6
	uxthhi	r5, r5
.L1212:
	ldr	r0, [r4, #2188]
	uxth	r6, r10
	mov	r1, r6
	cmp	r0, r6
	bhi	.L1219
	add	fp, fp, #1
	b	.L1210
.L1219:
	add	r1, r1, #1096
	ldrh	r1, [r4, r1, lsl #1]
	cmp	r1, r5
	bne	.L1213
	mov	r1, r5
	ldr	r0, .L1228+20
	bl	printf
	ldr	r1, .L1228+24
	ldrb	r1, [r1]	@ zero_extendqisi2
	cbnz	r1, .L1214
	ldr	r1, .L1228+28
	ldrb	r1, [r1]	@ zero_extendqisi2
	cbz	r1, .L1215
.L1214:
	ldr	r1, .L1228+32
	ldr	r3, .L1228+36
	ldr	r1, [r1]
	ldr	r1, [r1, #156]
	cmp	r1, r3
	beq	.L1216
.L1215:
	ldrh	r0, [r7]
	lsl	r0, r5, r0
	bl	ftl_mask_bad_block
.L1216:
	ldr	r1, [r4, #2188]
.L1217:
	cmp	r6, r1
	bcc	.L1218
	subs	r1, r1, #1
	str	r1, [r4, #2188]
.L1213:
	add	r10, r10, #1
	b	.L1212
.L1218:
	addw	r0, r6, #1097
	adds	r3, r6, #1
	ldrh	ip, [r4, r0, lsl #1]
	add	r0, r6, #1096
	uxth	r6, r3
	strh	ip, [r4, r0, lsl #1]	@ movhi
	b	.L1217
.L1229:
	.align	2
.L1228:
	.word	.LANCHOR70
	.word	.LANCHOR79
	.word	.LANCHOR75
	.word	.LANCHOR31
	.word	.LANCHOR74
	.word	.LC67
	.word	.LANCHOR124
	.word	.LANCHOR80
	.word	.LANCHOR110
	.word	1145785929
	.size	gc_free_bad_sblk, .-gc_free_bad_sblk
	.section	.text.ftl_free_sblk,"ax",%progbits
	.align	1
	.global	ftl_free_sblk
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	ftl_free_sblk, %function
ftl_free_sblk:
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r0, r1, r2, r3, r4, r5, r6, r7, r8, r10, fp, lr}
	mov	r5, r0
	ldr	r3, .L1251
	ldr	r6, [r3]
	lsls	r3, r0, #2
	adds	r7, r6, r3
	ldrb	r4, [r7, #2]	@ zero_extendqisi2
	lsls	r2, r4, #28
	lsr	r3, r4, #5
	str	r3, [sp, #4]
	bpl	.L1231
	ldr	r3, .L1251+4
	ldrh	fp, [r6, r0, lsl #2]
	ldr	r1, .L1251+8
	ldr	r3, [r3]
	ldr	r0, [r6, r0, lsl #2]
	ubfx	fp, fp, #0, #11
	ldrh	r8, [r1]
	ldrh	r2, [r3, #74]
	ldrh	r3, [r3, #72]
	ubfx	r10, r0, #11, #8
	mov	r1, r8
	add	r2, r2, fp
	uxth	r2, r2
	add	r3, r3, r10
	uxth	r3, r3
	mov	r0, r2
	str	r2, [sp, #8]
	str	r3, [sp, #12]
	bl	__aeabi_uidiv
	ldr	r3, [sp, #12]
	ldr	r1, .L1251+12
	ldr	r2, [sp, #8]
	ldrh	r1, [r1]
	uxtah	r0, r3, r0
	cmp	r0, r1
	ble	.L1232
	ldr	r3, .L1251+16
	ldr	r1, .L1251+20
	ldrh	r2, [r3]
	ldr	r3, .L1251+24
	ldrh	r1, [r1]
	adds	r2, r2, #7
	ldrh	r3, [r3]
	add	r3, r3, r1
	cmp	r2, r3
	blt	.L1233
.L1238:
	movs	r3, #2
	bfi	r4, r3, #3, #2
	b	.L1248
.L1233:
	ldr	r3, .L1251+28
	ldr	r1, .L1251+32
	ldrh	r2, [r3]
	ldr	r3, .L1251+36
	ldrh	r1, [r1]
	adds	r2, r2, #7
	ldrh	r3, [r3]
	add	r3, r3, r1
	ldr	r1, .L1251+40
	ldrh	r1, [r1]
	add	r3, r3, r1
	cmp	r2, r3
	blt	.L1238
.L1250:
	bfc	r4, #3, #2
.L1248:
	strb	r4, [r7, #2]
.L1234:
	ldrb	r3, [r7, #2]	@ zero_extendqisi2
	ands	r3, r3, #24
	bne	.L1239
	mul	r8, r8, r10
	ldrh	r3, [r6, r5, lsl #2]
	lsr	r10, r10, #3
	add	r8, r8, r8, lsl #1
	add	fp, fp, r8, asr #2
	bfi	r3, fp, #0, #11
	strh	r3, [r6, r5, lsl #2]	@ movhi
	ldr	r3, [r6, r5, lsl #2]
	bfi	r3, r10, #11, #8
	str	r3, [r6, r5, lsl #2]
.L1240:
	mov	r0, r5
	bl	zftl_remove_data_node
	ldr	r3, .L1251
	lsls	r2, r5, #2
	ldr	r3, [r3]
	add	r3, r3, r2
	ldrb	r2, [r3, #2]	@ zero_extendqisi2
	bfc	r2, #5, #3
	strb	r2, [r3, #2]
	movs	r2, #0
	ldr	r3, .L1251+44
	ldr	r3, [r3]
	strh	r2, [r3, r5, lsl #1]	@ movhi
	ldr	r3, [sp, #4]
	adds	r3, r3, #6
	and	r3, r3, #7
	cmp	r3, #4
	bhi	.L1243
	mov	r0, r5
	bl	gc_free_bad_sblk
.L1243:
	ldrb	r3, [r7, #2]	@ zero_extendqisi2
	lsls	r3, r3, #28
	bpl	.L1244
	ldr	r3, .L1251+48
	ldr	r3, [r3]
	ldrh	r2, [r3, #586]
	cmp	r2, r5
	bne	.L1244
	ldrh	r1, [r3, #590]
	movw	r2, #65535
	strh	r2, [r3, #586]	@ movhi
	cmp	r1, r2
	bne	.L1244
	strh	r5, [r3, #590]	@ movhi
	mov	r1, r5
	ldr	r0, .L1251+52
	add	sp, sp, #16
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r10, fp, lr}
	b	printf
.L1232:
	mla	r3, r3, r8, r2
	ldr	r2, .L1251+56
	ldrh	r2, [r2]
	cmp	r3, r2
	ble	.L1234
	ldr	r3, .L1251+28
	ldr	r1, .L1251+32
	ldrh	r2, [r3]
	ldr	r3, .L1251+36
	ldrh	r1, [r1]
	ldrh	r3, [r3]
	add	r3, r3, r1
	ldr	r1, .L1251+40
	ldrh	r1, [r1]
	add	r3, r3, r1
	adds	r1, r2, #7
	cmp	r1, r3
	bge	.L1250
	ldr	r1, .L1251+16
	ldr	ip, .L1251+20
	ldrh	r0, [r1]
	ldr	r1, .L1251+24
	ldrh	ip, [ip]
	adds	r0, r0, #7
	ldrh	r1, [r1]
	add	r1, r1, ip
	cmp	r0, r1
	bge	.L1238
	adds	r2, r2, #23
	cmp	r3, r2
	bgt	.L1238
	b	.L1250
.L1239:
	cmp	r3, #16
	bne	.L1240
	mov	r0, fp
	mov	r1, r8
	bl	__aeabi_idiv
	add	r0, r0, r0, lsl #1
	ldr	r3, [r6, r5, lsl #2]
	asr	fp, fp, #5
	add	r10, r10, r0, asr #2
	bfi	r3, r10, #11, #8
	str	r3, [r6, r5, lsl #2]
	bfi	r3, fp, #0, #11
.L1249:
	strh	r3, [r6, r5, lsl #2]	@ movhi
	b	.L1240
.L1231:
	tst	r4, #24
	bne	.L1240
	ldr	r3, .L1251+60
	ldrh	r3, [r3]
	cmp	r3, #0
	bne	.L1240
	ldr	r3, .L1251+20
	ldrh	r1, [r3]
	cmp	r1, #15
	bhi	.L1240
	ldr	r3, .L1251+36
	ldr	r2, .L1251+32
	ldrh	r3, [r3]
	ldrh	r2, [r2]
	add	r3, r3, r2
	ldr	r2, .L1251+40
	ldrh	r2, [r2]
	add	r3, r3, r2
	ldr	r2, .L1251+28
	ldrh	r2, [r2]
	adds	r2, r2, #16
	cmp	r3, r2
	ble	.L1240
	ldr	r3, .L1251+16
	ldrh	r2, [r3]
	ldr	r3, .L1251+24
	adds	r2, r2, #7
	ldrh	r3, [r3]
	add	r3, r3, r1
	cmp	r2, r3
	blt	.L1240
	movs	r3, #2
	bfi	r4, r3, #3, #2
	ldr	r3, .L1251+8
	strb	r4, [r7, #2]
	ldrh	r4, [r6, r0, lsl #2]
	ldrh	r1, [r3]
	ubfx	r4, r4, #0, #11
	mov	r0, r4
	asrs	r4, r4, #5
	bl	__aeabi_idiv
	ldr	r3, [r6, r5, lsl #2]
	add	r0, r0, r0, lsl #1
	ubfx	r2, r3, #11, #8
	add	r0, r2, r0, asr #2
	bfi	r3, r0, #11, #8
	str	r3, [r6, r5, lsl #2]
	bfi	r3, r4, #0, #11
	b	.L1249
.L1244:
	mov	r0, r5
	add	sp, sp, #16
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r10, fp, lr}
	b	zftl_insert_free_list
.L1252:
	.align	2
.L1251:
	.word	.LANCHOR9
	.word	.LANCHOR110
	.word	.LANCHOR10
	.word	.LANCHOR125
	.word	.LANCHOR101
	.word	.LANCHOR105
	.word	.LANCHOR91
	.word	.LANCHOR98
	.word	.LANCHOR103
	.word	.LANCHOR97
	.word	.LANCHOR99
	.word	.LANCHOR11
	.word	.LANCHOR12
	.word	.LC68
	.word	.LANCHOR126
	.word	.LANCHOR107
	.size	ftl_free_sblk, .-ftl_free_sblk
	.section	.text.gc_free_src_blk,"ax",%progbits
	.align	1
	.global	gc_free_src_blk
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	gc_free_src_blk, %function
gc_free_src_blk:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r3, r4, r5, r6, r7, lr}
	movs	r5, #0
	ldr	r6, .L1290
.L1254:
	uxth	r2, r5
	ldr	r3, .L1290+4
	ldrh	r1, [r3, #52]
	cmp	r1, r2
	bhi	.L1268
	movs	r2, #0
	strh	r2, [r3, #52]	@ movhi
	pop	{r3, r4, r5, r6, r7, pc}
.L1268:
	uxth	r2, r5
	add	r3, r3, r2, lsl #1
	ldrh	r4, [r3, #54]
	ldr	r3, [r6]
	ldrh	r2, [r3, r4, lsl #1]
	cbz	r2, .L1255
	mov	r1, r4
	ldr	r0, .L1290+8
	bl	printf
.L1255:
	ldr	r3, [r6]
	movs	r2, #0
	strh	r2, [r3, r4, lsl #1]	@ movhi
	ldr	r3, .L1290+12
	ldr	r7, [r3]
	ldr	r3, .L1290+16
	ldr	r3, [r3]
	add	r7, r7, r4, lsl #2
	lsls	r3, r3, #23
	bpl	.L1256
	ldrb	r2, [r7, #2]	@ zero_extendqisi2
	mov	r1, r4
	ldr	r0, .L1290+20
	lsrs	r2, r2, #5
	bl	printf
.L1256:
	ldrb	r3, [r7, #2]	@ zero_extendqisi2
	and	r2, r3, #224
	cmp	r2, #224
	beq	.L1257
	tst	r3, #192
	bne	.L1258
.L1257:
	movw	r2, #1363
	ldr	r1, .L1290+24
	ldr	r0, .L1290+28
	bl	printf
.L1258:
	mov	r0, r4
	bl	ftl_free_sblk
	ldr	r3, .L1290+32
	ldr	r3, [r3]
	ldrh	r1, [r3, #124]
	cbz	r1, .L1259
	add	r0, r3, #392
	movs	r2, #0
.L1261:
	ldrh	r7, [r0], #2
	cmp	r4, r7
	bne	.L1260
	adds	r2, r2, #196
	movw	r0, #65535
	subs	r1, r1, #1
	strh	r0, [r3, r2, lsl #1]	@ movhi
	strh	r1, [r3, #124]	@ movhi
.L1259:
	ldrh	r1, [r3, #120]
	cbz	r1, .L1262
	add	r0, r3, #136
	movs	r2, #0
.L1264:
	ldrh	r7, [r0], #2
	cmp	r4, r7
	bne	.L1263
	adds	r2, r2, #68
	movw	r0, #65535
	subs	r1, r1, #1
	strh	r0, [r3, r2, lsl #1]	@ movhi
	strh	r1, [r3, #120]	@ movhi
.L1262:
	ldrh	r1, [r3, #122]
	cbz	r1, .L1265
	add	r0, r3, #264
	movs	r2, #0
.L1267:
	ldrh	r7, [r0], #2
	cmp	r4, r7
	bne	.L1266
	adds	r2, r2, #132
	movw	r0, #65535
	subs	r1, r1, #1
	strh	r0, [r3, r2, lsl #1]	@ movhi
	strh	r1, [r3, #122]	@ movhi
.L1265:
	adds	r5, r5, #1
	b	.L1254
.L1260:
	adds	r2, r2, #1
	cmp	r2, #64
	bne	.L1261
	b	.L1259
.L1263:
	adds	r2, r2, #1
	cmp	r2, #64
	bne	.L1264
	b	.L1262
.L1266:
	adds	r2, r2, #1
	cmp	r2, #64
	bne	.L1267
	b	.L1265
.L1291:
	.align	2
.L1290:
	.word	.LANCHOR11
	.word	.LANCHOR70
	.word	.LC69
	.word	.LANCHOR9
	.word	.LANCHOR19
	.word	.LC70
	.word	.LANCHOR127
	.word	.LC0
	.word	.LANCHOR12
	.size	gc_free_src_blk, .-gc_free_src_blk
	.section	.text.print_ftl_debug_info,"ax",%progbits
	.align	1
	.global	print_ftl_debug_info
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	print_ftl_debug_info, %function
print_ftl_debug_info:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, lr}
	sub	sp, sp, #32
	ldr	r4, .L1293
	ldr	r5, .L1293+4
	ldr	r6, .L1293+8
	ldr	r1, [r4]
	ldr	r0, [r5]
	ldr	r6, [r6]
	ldr	r3, .L1293+12
	ldrh	r2, [r1, #146]
	ldrh	r1, [r1, #148]
	ldrh	r3, [r3]
	str	r6, [sp, #28]
	ldr	r6, [r0, #528]
	str	r6, [sp, #24]
	ldr	r0, [r0, #524]
	str	r0, [sp, #20]
	ldr	r0, .L1293+16
	ldrh	r0, [r0]
	str	r0, [sp, #16]
	ldr	r0, .L1293+20
	ldrh	r0, [r0]
	str	r0, [sp, #12]
	ldr	r0, .L1293+24
	ldrh	r0, [r0]
	str	r0, [sp, #8]
	ldr	r0, .L1293+28
	ldrh	r0, [r0]
	str	r0, [sp, #4]
	ldr	r0, .L1293+32
	ldrh	r0, [r0]
	str	r0, [sp]
	ldr	r0, .L1293+36
	bl	printf
	ldr	r1, [r4]
	ldr	r3, .L1293+40
	ldr	r0, .L1293+44
	ldr	r2, [r1, #64]
	ldrb	r3, [r3]	@ zero_extendqisi2
	str	r2, [sp, #4]
	ldr	r2, [r1, #8]
	str	r2, [sp]
	ldr	r2, [r1, #28]
	ldr	r1, [r1, #20]
	bl	printf
	ldr	r1, [r4]
	ldr	r0, .L1293+48
	ldr	r3, [r1, #16]
	ldr	r2, [r1, #60]
	ldr	r1, [r1, #52]
	lsrs	r3, r3, #11
	bl	printf
	ldr	r2, [r4]
	ldrh	r0, [r2, #98]
	ldrh	r3, [r2, #88]
	ldrh	r1, [r2, #74]
	str	r0, [sp, #24]
	ldrh	r0, [r2, #94]
	str	r0, [sp, #20]
	ldrh	r0, [r2, #90]
	str	r0, [sp, #16]
	ldr	r0, [r2, #80]
	str	r0, [sp, #12]
	ldrh	r0, [r2, #72]
	str	r0, [sp, #8]
	ldrh	r0, [r2, #96]
	str	r0, [sp, #4]
	ldrh	r0, [r2, #92]
	str	r0, [sp]
	ldr	r0, .L1293+52
	ldr	r2, [r2, #84]
	bl	printf
	ldr	r0, .L1293+56
	ldr	r3, .L1293+60
	ldr	r2, .L1293+64
	ldrh	r0, [r0]
	ldr	r1, .L1293+68
	ldrh	r3, [r3]
	ldrh	r2, [r2]
	ldrh	r1, [r1]
	str	r0, [sp, #4]
	ldr	r0, .L1293+72
	ldrh	r0, [r0]
	str	r0, [sp]
	ldr	r0, .L1293+76
	bl	printf
	ldr	r4, [r4]
	ldr	r0, [r5]
	ldrh	r5, [r4, #150]
	ldrh	r3, [r0, #588]
	ldrh	r2, [r0, #586]
	ldrh	r1, [r0, #584]
	str	r5, [sp, #8]
	ldr	r4, [r4, #156]
	str	r4, [sp, #4]
	ldrh	r0, [r0, #590]
	str	r0, [sp]
	ldr	r0, .L1293+80
	bl	printf
	add	sp, sp, #32
	@ sp needed
	pop	{r4, r5, r6, pc}
.L1294:
	.align	2
.L1293:
	.word	.LANCHOR110
	.word	.LANCHOR12
	.word	.LANCHOR128
	.word	.LANCHOR103
	.word	.LANCHOR91
	.word	.LANCHOR99
	.word	.LANCHOR97
	.word	.LANCHOR107
	.word	.LANCHOR105
	.word	.LC71
	.word	.LANCHOR129
	.word	.LC72
	.word	.LC73
	.word	.LC74
	.word	.LANCHOR86
	.word	.LANCHOR69
	.word	.LANCHOR102
	.word	.LANCHOR100
	.word	.LANCHOR93
	.word	.LC75
	.word	.LC76
	.size	print_ftl_debug_info, .-print_ftl_debug_info
	.section	.text.ftl_write_buf,"ax",%progbits
	.align	1
	.global	ftl_write_buf
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	ftl_write_buf, %function
ftl_write_buf:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, lr}
	mov	r4, r0
	cbnz	r0, .L1296
	mov	r2, #808
	ldr	r1, .L1305
	ldr	r0, .L1305+4
	bl	printf
	bl	print_ftl_debug_info
	mov	r0, #-1
	pop	{r4, r5, r6, pc}
.L1299:
	mov	r1, r4
	ldr	r0, .L1305+8
	bl	buf_add_tail
	ldr	r3, .L1305+12
	ldrb	r1, [r4, #40]	@ zero_extendqisi2
	ldrb	r0, [r6]	@ zero_extendqisi2
	ldr	r3, [r3]
	adds	r0, r0, #1
	ldr	r2, [r3, #16]
	uxtb	r0, r0
	strb	r0, [r6]
	add	r2, r2, r1
	str	r2, [r3, #16]
	ldr	r2, [r3, #32]
	adds	r2, r2, #1
	str	r2, [r3, #32]
	pop	{r4, r5, r6, pc}
.L1296:
	ldr	r5, .L1305+16
	ldrb	r1, [r0, #40]	@ zero_extendqisi2
	ldrb	r2, [r5]	@ zero_extendqisi2
	cmp	r1, r2
	bls	.L1301
	movw	r2, #815
	ldr	r1, .L1305
	ldr	r0, .L1305+4
	bl	printf
.L1301:
	ldrb	r3, [r4, #40]	@ zero_extendqisi2
	ldr	r6, .L1305+20
	cbz	r3, .L1298
	ldrb	r2, [r5]	@ zero_extendqisi2
	cmp	r2, r3
	bcs	.L1299
.L1298:
	mov	r0, r4
	bl	zbuf_free
	ldrb	r0, [r6]	@ zero_extendqisi2
	pop	{r4, r5, r6, pc}
.L1306:
	.align	2
.L1305:
	.word	.LANCHOR130
	.word	.LC0
	.word	.LANCHOR65
	.word	.LANCHOR110
	.word	.LANCHOR131
	.word	.LANCHOR66
	.size	ftl_write_buf, .-ftl_write_buf
	.section	.text.ftl_write_completed,"ax",%progbits
	.align	1
	.global	ftl_write_completed
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	ftl_write_completed, %function
ftl_write_completed:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r0, r1, r4, r5, r6, r7, r8, r10, fp, lr}
	mov	fp, #0
	ldr	r8, .L1323+36
	ldr	r10, .L1323+40
.L1308:
	ldrb	r6, [r8]	@ zero_extendqisi2
	cmp	r6, #255
	bne	.L1319
	add	sp, sp, #8
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r10, fp, pc}
.L1319:
	movs	r3, #48
	ldr	r5, .L1323
	muls	r3, r6, r3
	add	r7, r6, r6, lsl #1
	add	r7, r5, r7, lsl #4
	adds	r4, r5, r3
	ldrb	r3, [r5, r3]	@ zero_extendqisi2
	strb	r3, [r8]
	ldr	r3, [r4, #36]
	adds	r3, r3, #1
	bne	.L1309
	ldr	r3, .L1323+4
	ldrb	r3, [r3]	@ zero_extendqisi2
	cbnz	r3, .L1310
	ldr	r3, .L1323+8
	ldrb	r3, [r3]	@ zero_extendqisi2
	cbz	r3, .L1311
.L1310:
	ldr	r3, .L1323+12
	ldr	r3, [r3]
	ldr	r3, [r3, #156]
	cmp	r3, r10
	beq	.L1312
.L1311:
	ldr	r2, .L1323+16
	movs	r3, #48
	mla	r3, r3, r6, r5
	ldr	fp, .L1323+44
	ldrh	r1, [r2]
	ldr	r2, .L1323+20
	ldr	r3, [r3, #24]
	ldrb	r2, [r2]	@ zero_extendqisi2
	str	r3, [sp, #4]
	rsb	r2, r2, #24
	subs	r0, r2, r1
	movs	r2, #1
	lsls	r2, r2, r0
	lsr	r0, r3, r1
	ldr	r1, .L1323+24
	subs	r2, r2, #1
	ands	r0, r0, r2
	ldrb	r1, [r1]	@ zero_extendqisi2
	bl	__aeabi_uidiv
	ldr	r2, [fp]
	movw	r1, #65535
	uxth	r4, r0
	ldr	r0, .L1323+28
	ldr	r3, [r2, #560]
	cmp	r3, r1
	ldr	r3, [sp, #4]
	it	eq
	streq	r4, [r2, #560]
	mov	r1, r4
	it	eq
	streq	r3, [r2, #564]
	movs	r2, #48
	mla	r5, r2, r6, r5
	ldr	r2, [r5, #20]
	bl	printf
	ldr	r3, [fp]
	ldr	r2, [r3, #556]
	adds	r2, r2, #1
	str	r2, [r3, #556]
	ldrh	r2, [r3, #16]
	cmp	r2, r4
	bne	.L1314
	movs	r2, #0
	strh	r2, [r3, #22]	@ movhi
.L1312:
	mov	r0, r7
	mov	fp, #1
	bl	ftl_write_buf
	b	.L1308
.L1314:
	ldrh	r2, [r3, #48]
	cmp	r2, r4
	itt	eq
	moveq	r2, #0
	strheq	r2, [r3, #54]	@ movhi
	b	.L1312
.L1309:
	cmp	fp, #0
	beq	.L1317
	ldr	r2, [r4, #24]
	ldr	r1, [r4, #20]
	ldr	r0, .L1323+32
	bl	printf
	mov	r0, r7
	bl	ftl_write_buf
	b	.L1308
.L1317:
	ldrh	r2, [r4, #32]
	ldr	r1, [r4, #28]
	ldr	r0, [r4, #20]
	bl	lpa_hash_update_ppa
	ldrb	r3, [r4, #2]	@ zero_extendqisi2
	lsls	r2, r3, #29
	bpl	.L1318
	bic	r3, r3, #2
	strb	r3, [r4, #2]
	b	.L1308
.L1318:
	mov	r0, r7
	bl	zbuf_free
	b	.L1308
.L1324:
	.align	2
.L1323:
	.word	.LANCHOR55
	.word	.LANCHOR124
	.word	.LANCHOR80
	.word	.LANCHOR110
	.word	.LANCHOR74
	.word	.LANCHOR31
	.word	.LANCHOR75
	.word	.LC77
	.word	.LC78
	.word	.LANCHOR64
	.word	1145785929
	.word	.LANCHOR12
	.size	ftl_write_completed, .-ftl_write_completed
	.section	.text.zftl_add_read_buf,"ax",%progbits
	.align	1
	.global	zftl_add_read_buf
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	zftl_add_read_buf, %function
zftl_add_read_buf:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, lr}
	mov	r4, r0
	cbnz	r0, .L1326
	movw	r2, #1148
	ldr	r1, .L1330
	ldr	r0, .L1330+4
	bl	printf
	pop	{r4, lr}
	b	print_ftl_debug_info
.L1326:
	ldr	r3, .L1330+8
	ldrb	r2, [r0, #40]	@ zero_extendqisi2
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r2, r3
	bls	.L1328
	movw	r2, #1155
	ldr	r1, .L1330
	ldr	r0, .L1330+4
	bl	printf
.L1328:
	mov	r1, r4
	ldr	r0, .L1330+12
	bl	buf_add_tail
	ldr	r2, .L1330+16
	ldrb	r3, [r2]	@ zero_extendqisi2
	adds	r3, r3, #1
	strb	r3, [r2]
	pop	{r4, pc}
.L1331:
	.align	2
.L1330:
	.word	.LANCHOR132
	.word	.LC0
	.word	.LANCHOR131
	.word	.LANCHOR133
	.word	.LANCHOR134
	.size	zftl_add_read_buf, .-zftl_add_read_buf
	.section	.text.sblk_init,"ax",%progbits
	.align	1
	.global	sblk_init
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	sblk_init, %function
sblk_init:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	ldr	r2, .L1333
	movs	r3, #255
	movs	r0, #0
	strb	r3, [r2]
	ldr	r2, .L1333+4
	strb	r3, [r2]
	ldr	r2, .L1333+8
	strb	r3, [r2]
	ldr	r2, .L1333+12
	strb	r3, [r2]
	bx	lr
.L1334:
	.align	2
.L1333:
	.word	.LANCHOR59
	.word	.LANCHOR64
	.word	.LANCHOR62
	.word	.LANCHOR63
	.size	sblk_init, .-sblk_init
	.section	.text.dump_sblk_queue,"ax",%progbits
	.align	1
	.global	dump_sblk_queue
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	dump_sblk_queue, %function
dump_sblk_queue:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, lr}
	ldr	r4, .L1344
	ldr	r0, .L1344+4
	ldrb	r1, [r4]	@ zero_extendqisi2
	bl	printf
	ldrb	r4, [r4]	@ zero_extendqisi2
	cmp	r4, #255
	beq	.L1335
	ldr	r5, .L1344+8
	add	r4, r4, r4, lsl #1
	ldr	r6, .L1344+12
	add	r4, r5, r4, lsl #4
.L1337:
	ldr	r3, [r4, #24]
	mov	r0, r6
	ldrb	r2, [r4, #42]	@ zero_extendqisi2
	ldrb	r1, [r4, #1]	@ zero_extendqisi2
	bl	printf
	ldrb	r4, [r4]	@ zero_extendqisi2
	cmp	r4, #255
	beq	.L1335
	add	r4, r4, r4, lsl #1
	add	r4, r5, r4, lsl #4
	b	.L1337
.L1335:
	pop	{r4, r5, r6, pc}
.L1345:
	.align	2
.L1344:
	.word	.LANCHOR59
	.word	.LC79
	.word	.LANCHOR55
	.word	.LC80
	.size	dump_sblk_queue, .-dump_sblk_queue
	.section	.text.queue_lun_state,"ax",%progbits
	.align	1
	.global	queue_lun_state
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	queue_lun_state, %function
queue_lun_state:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 0, uses_anonymous_args = 0
	ldr	r3, .L1365
	push	{r0, r1, r4, r5, r6, r7, r8, r10, fp, lr}
	ldrb	r6, [r3]	@ zero_extendqisi2
	cmp	r6, #255
	beq	.L1354
	ldr	r3, .L1365+4
	movs	r2, #1
	ldr	r10, .L1365+16
	mov	r8, #48
	ldrb	r3, [r3]	@ zero_extendqisi2
	rsb	ip, r3, #24
	lsl	r3, r2, r3
	asr	r4, r0, ip
	subs	r3, r3, #1
	uxth	r3, r3
	ands	r4, r4, r3
	str	r4, [sp]
	ldr	r4, .L1365+8
	ldrh	lr, [r4]
	sub	r4, ip, lr
	lsls	r2, r2, r4
	ldr	r4, .L1365+12
	subs	r2, r2, #1
	ldrb	r7, [r4]	@ zero_extendqisi2
	asr	r4, r0, lr
	uxth	r2, r2
	subs	r7, r7, #1
	uxth	r7, r7
	ands	r4, r4, r7
	and	r0, r4, r2
	str	r0, [sp, #4]
.L1353:
	mla	fp, r8, r6, r10
	ldr	r5, [fp, #24]
	lsr	r0, r5, ip
	ands	r0, r0, r3
	mov	r4, r0
	ldr	r0, [sp]
	cmp	r0, r4
	bne	.L1348
	lsr	r5, r5, lr
	ldr	r4, [sp, #4]
	ldrb	r0, [fp, #42]	@ zero_extendqisi2
	ands	r5, r5, r7
	ands	r5, r5, r2
	cmp	r4, r5
	bne	.L1349
	cmp	r1, #1
	bne	.L1346
.L1351:
	cmp	r0, #7
	beq	.L1348
	cmp	r0, #9
.L1362:
	bne	.L1346
.L1348:
	mul	r6, r8, r6
	ldr	r0, .L1365+16
	ldrb	r6, [r0, r6]	@ zero_extendqisi2
	cmp	r6, #255
	bne	.L1353
.L1354:
	movs	r0, #0
.L1346:
	add	sp, sp, #8
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r10, fp, pc}
.L1349:
	cmp	r1, #3
	bhi	.L1348
	adr	r5, .L1350
	ldr	pc, [r5, r1, lsl #2]
	.p2align 2
.L1350:
	.word	.L1346+1
	.word	.L1351+1
	.word	.L1352+1
	.word	.L1346+1
	.p2align 1
.L1352:
	cmp	r0, #11
	b	.L1362
.L1366:
	.align	2
.L1365:
	.word	.LANCHOR59
	.word	.LANCHOR31
	.word	.LANCHOR74
	.word	.LANCHOR75
	.word	.LANCHOR55
	.size	queue_lun_state, .-queue_lun_state
	.section	.text.queue_remove_completed_req,"ax",%progbits
	.align	1
	.global	queue_remove_completed_req
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	queue_remove_completed_req, %function
queue_remove_completed_req:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r0, r1, r4, r5, r6, r7, r8, r10, fp, lr}
	mov	ip, #0
	ldr	r5, .L1392
	movs	r4, #48
	mov	fp, #255
	ldr	r6, .L1392+4
	ldrb	r3, [r5]	@ zero_extendqisi2
	ldr	r1, .L1392+8
	ldr	r7, .L1392+12
	str	r3, [sp, #4]
	ldrb	r3, [r6]	@ zero_extendqisi2
	ldrb	r2, [r1]	@ zero_extendqisi2
	ldrb	r10, [r7]	@ zero_extendqisi2
	str	r3, [sp]
	ldr	r3, .L1392+16
.L1368:
	cmp	r2, #255
	beq	.L1369
	mul	r8, r4, r2
	mov	r0, r2
	add	lr, r3, r8
	ldrb	lr, [lr, #42]	@ zero_extendqisi2
	sub	lr, lr, #12
	cmp	lr, #1
	bls	.L1370
.L1369:
	cmp	ip, #0
	beq	.L1367
	strb	r2, [r1]
	b	.L1367
.L1370:
	mul	lr, r4, r0
	ldrb	r2, [r3, r8]	@ zero_extendqisi2
	add	ip, r3, lr
	strb	fp, [r3, lr]
	ldrb	lr, [ip, #43]	@ zero_extendqisi2
	cmp	lr, #1
	bne	.L1373
	ldrh	ip, [ip, #34]
	cmp	ip, #0
	bne	.L1381
	mov	ip, r10
	mov	lr, r7
.L1374:
	cmp	ip, #255
	bne	.L1379
	strb	r2, [r1]
	movs	r2, #48
	mla	r3, r2, r0, r3
	ldrb	r3, [r3, #1]	@ zero_extendqisi2
	strb	r3, [lr]
.L1367:
	add	sp, sp, #8
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r10, fp, pc}
.L1373:
	cmp	lr, #0
	bne	.L1375
	ldr	ip, [ip, #20]
	cmp	ip, #-1
	beq	.L1375
	ldr	ip, [sp, #4]
	mov	lr, r5
	b	.L1374
.L1381:
	ldr	ip, [sp]
	mov	lr, r6
	b	.L1374
.L1379:
	mov	lr, ip
	mul	ip, r4, ip
	ldrb	ip, [r3, ip]	@ zero_extendqisi2
	cmp	ip, #255
	bne	.L1379
	mla	r0, r4, r0, r3
	mul	lr, r4, lr
	ldrb	r0, [r0, #1]	@ zero_extendqisi2
	strb	r0, [r3, lr]
.L1375:
	mov	ip, #1
	b	.L1368
.L1393:
	.align	2
.L1392:
	.word	.LANCHOR62
	.word	.LANCHOR63
	.word	.LANCHOR59
	.word	.LANCHOR64
	.word	.LANCHOR55
	.size	queue_remove_completed_req, .-queue_remove_completed_req
	.section	.text.pm_select_ram_region,"ax",%progbits
	.align	1
	.global	pm_select_ram_region
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	pm_select_ram_region, %function
pm_select_ram_region:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	ldr	r2, .L1404
	movw	r0, #65535
	push	{r3, r4, r5, r6, r7, lr}
	movs	r3, #0
	mov	r1, r2
.L1396:
	ldrh	r5, [r2, r3, lsl #3]
	uxth	r4, r3
	cmp	r5, r0
	beq	.L1395
	adds	r3, r3, #1
	cmp	r3, #32
	bne	.L1396
	movs	r2, #0
	mov	r4, r3
	mov	r0, #32768
.L1398:
	add	r3, r1, r2, lsl #3
	uxth	r5, r2
	ldrh	r3, [r3, #2]
	lsls	r6, r3, #16
	bmi	.L1397
	cmp	r3, r0
	itt	cc
	movcc	r0, r3
	movcc	r4, r5
.L1397:
	adds	r2, r2, #1
	cmp	r2, #32
	bne	.L1398
	cmp	r4, #32
	bne	.L1395
	ldr	r3, .L1404+4
	mov	r2, #-1
	ldrb	r5, [r3]	@ zero_extendqisi2
	movs	r3, #0
.L1400:
	add	r0, r1, r3, lsl #3
	uxth	r6, r3
	ldrh	r0, [r0, #2]
	cmp	r0, r2
	bcs	.L1399
	ldrh	r7, [r1, r3, lsl #3]
	cmp	r7, r5
	itt	ne
	movne	r2, r0
	movne	r4, r6
.L1399:
	adds	r3, r3, #1
	cmp	r3, #32
	bne	.L1400
	cmp	r4, #32
	bne	.L1395
	movw	r2, #377
	ldr	r1, .L1404+8
	ldr	r0, .L1404+12
	bl	printf
.L1395:
	mov	r0, r4
	pop	{r3, r4, r5, r6, r7, pc}
.L1405:
	.align	2
.L1404:
	.word	.LANCHOR135
	.word	.LANCHOR136
	.word	.LANCHOR137
	.word	.LC0
	.size	pm_select_ram_region, .-pm_select_ram_region
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
	@ link register save eliminated.
	ldr	r3, .L1407
	movs	r0, #0
	str	r0, [r3]
	ldr	r3, .L1407+4
	str	r0, [r3]
	ldr	r3, .L1407+8
	strb	r0, [r3]
	ldr	r3, .L1407+12
	str	r0, [r3]
	bx	lr
.L1408:
	.align	2
.L1407:
	.word	.LANCHOR138
	.word	.LANCHOR139
	.word	.LANCHOR140
	.word	.LANCHOR141
	.size	idb_init, .-idb_init
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
	.section	.text.flash_lsb_page_tbl_build,"ax",%progbits
	.align	1
	.global	flash_lsb_page_tbl_build
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	flash_lsb_page_tbl_build, %function
flash_lsb_page_tbl_build:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r3, r4, r5, lr}
	mov	r5, r0
	ldr	r3, .L1463
	mov	r0, #1024
	ldr	r3, [r3]
	ldrb	r1, [r3, #12]	@ zero_extendqisi2
	bl	__aeabi_idiv
	uxth	r4, r0
	cbnz	r5, .L1411
	ldr	r3, .L1463+4
.L1412:
	strh	r5, [r3, r5, lsl #1]	@ movhi
	adds	r5, r5, #1
	cmp	r5, #512
	bne	.L1412
.L1418:
	movs	r1, #255
	mov	r2, #2048
	ldr	r0, .L1463+8
	bl	ftl_memset
	ldr	r0, .L1463+4
	movs	r3, #0
	ldr	r1, .L1463+8
.L1413:
	ldrh	r2, [r0, r3, lsl #1]
	adds	r3, r3, #1
	strh	r2, [r1, r2, lsl #1]	@ movhi
	uxth	r2, r3
	cmp	r2, r4
	bcc	.L1413
	pop	{r3, r4, r5, pc}
.L1411:
	cmp	r5, #1
	bne	.L1414
	ldr	r1, .L1463+4
	movs	r3, #0
.L1417:
	cmp	r3, #3
	uxth	r2, r3
	bls	.L1415
	tst	r2, #1
	ite	ne
	movne	r0, #3
	moveq	r0, #2
	rsb	r2, r0, r2, lsl #1
	uxth	r2, r2
.L1415:
	strh	r2, [r1, r3, lsl #1]	@ movhi
	adds	r3, r3, #1
	cmp	r3, #512
	bne	.L1417
	b	.L1418
.L1414:
	cmp	r5, #2
	bne	.L1419
	ldr	r1, .L1463+4
	movs	r2, #0
.L1421:
	uxth	r3, r2
	cmp	r2, #1
	ittt	hi
	lslhi	r3, r3, #1
	addhi	r3, r3, #-1
	uxthhi	r3, r3
	strh	r3, [r1, r2, lsl #1]	@ movhi
	adds	r2, r2, #1
	cmp	r2, #512
	bne	.L1421
	b	.L1418
.L1419:
	cmp	r5, #3
	bne	.L1422
	ldr	r1, .L1463+4
	movs	r3, #0
.L1425:
	cmp	r3, #5
	uxth	r2, r3
	bls	.L1423
	tst	r2, #1
	ite	ne
	movne	r0, #5
	moveq	r0, #4
	rsb	r2, r0, r2, lsl #1
	uxth	r2, r2
.L1423:
	strh	r2, [r1, r3, lsl #1]	@ movhi
	adds	r3, r3, #1
	cmp	r3, #512
	bne	.L1425
	b	.L1418
.L1422:
	cmp	r5, #4
	mov	r3, #0
	bne	.L1426
	ldr	r2, .L1463+4
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
	strh	r5, [r2, #8]	@ movhi
	strh	r3, [r2, #14]!	@ movhi
.L1428:
	tst	r3, #1
	ite	ne
	movne	r1, #7
	moveq	r1, #6
	rsb	r1, r1, r3, lsl #1
	adds	r3, r3, #1
	uxth	r3, r3
	strh	r1, [r2, #2]!	@ movhi
	cmp	r3, #512
	bne	.L1428
	b	.L1418
.L1426:
	cmp	r5, #5
	bne	.L1429
	ldr	r2, .L1463+4
.L1430:
	strh	r3, [r2, r3, lsl #1]	@ movhi
	adds	r3, r3, #1
	cmp	r3, #16
	bne	.L1430
	ldr	r2, .L1463+12
.L1431:
	strh	r3, [r2, #2]!	@ movhi
	adds	r3, r3, #2
	uxth	r3, r3
	cmp	r3, #1008
	bne	.L1431
	b	.L1418
.L1429:
	cmp	r5, #8
	bne	.L1432
	ldr	r2, .L1463+4
.L1433:
	strh	r3, [r3, r2]	@ movhi
	adds	r3, r3, #2
	cmp	r3, #1024
	bne	.L1433
	b	.L1418
.L1432:
	cmp	r5, #9
	bne	.L1434
	ldr	r2, .L1463+4
	movw	r1, #1021
	strh	r3, [r2]	@ movhi
	movs	r3, #1
	strh	r3, [r2, #2]	@ movhi
	mov	r3, r2
	movs	r2, #2
	strh	r2, [r3, #4]!	@ movhi
	movs	r2, #3
.L1435:
	strh	r2, [r3, #2]!	@ movhi
	adds	r2, r2, #2
	uxth	r2, r2
	cmp	r2, r1
	bne	.L1435
	b	.L1418
.L1434:
	cmp	r5, #10
	bne	.L1436
	ldr	r2, .L1463+4
.L1437:
	strh	r3, [r2, r3, lsl #1]	@ movhi
	adds	r3, r3, #1
	cmp	r3, #63
	bne	.L1437
	ldr	r2, .L1463+16
	movw	r1, #961
.L1438:
	strh	r3, [r2, #2]!	@ movhi
	adds	r3, r3, #2
	uxth	r3, r3
	cmp	r3, r1
	bne	.L1438
	b	.L1418
.L1436:
	cmp	r5, #11
	bne	.L1439
	ldr	r2, .L1463+4
	movs	r3, #0
.L1440:
	strh	r3, [r2, r3, lsl #1]	@ movhi
	adds	r3, r3, #1
	cmp	r3, #8
	bne	.L1440
	ldr	r1, .L1463+20
.L1442:
	tst	r3, #1
	ite	ne
	movne	r2, #7
	moveq	r2, #6
	rsb	r2, r2, r3, lsl #1
	adds	r3, r3, #1
	uxth	r3, r3
	strh	r2, [r1, #2]!	@ movhi
	cmp	r3, #512
	bne	.L1442
	b	.L1418
.L1439:
	cmp	r5, #13
	bne	.L1418
	ldr	r2, .L1463+24
	movs	r3, #0
.L1443:
	strh	r3, [r2, #2]!	@ movhi
	adds	r3, r3, #3
	uxth	r3, r3
	cmp	r3, #1536
	bne	.L1443
	b	.L1418
.L1464:
	.align	2
.L1463:
	.word	.LANCHOR21
	.word	.LANCHOR3
	.word	.LANCHOR142
	.word	.LANCHOR3+30
	.word	.LANCHOR3+124
	.word	.LANCHOR3+14
	.word	.LANCHOR3-2
	.size	flash_lsb_page_tbl_build, .-flash_lsb_page_tbl_build
	.section	.text.flash_die_info_init,"ax",%progbits
	.align	1
	.global	flash_die_info_init
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	flash_die_info_init, %function
flash_die_info_init:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 0, uses_anonymous_args = 0
	ldr	r3, .L1482
	push	{r0, r1, r4, r5, r6, r7, r8, r10, fp, lr}
	ldr	r3, [r3]
	lsls	r3, r3, #19
	bpl	.L1466
	ldr	r1, .L1482+4
	ldr	r0, .L1482+8
	bl	printf
.L1466:
	ldr	r4, .L1482+12
	movs	r6, #0
	ldr	r5, .L1482+16
	ldr	r7, .L1482+20
	ldrh	r3, [r4, #26]
	ldrb	r1, [r4, #12]	@ zero_extendqisi2
	ldrh	r0, [r4, #10]
	strh	r3, [r7]	@ movhi
	strb	r6, [r5]
	bl	__aeabi_idiv
	ldr	r10, .L1482+48
	movs	r2, #8
	ldr	r3, .L1482+24
	mov	r1, r6
	mov	r8, r10
	strh	r0, [r3]	@ movhi
	ldr	r0, .L1482+28
	bl	ftl_memset
	movs	r2, #32
	mov	r1, r6
	ldr	r0, .L1482+32
	bl	ftl_memset
.L1468:
	ldr	r3, .L1482+36
	movs	r2, #2
	add	r1, r10, r6, lsl #3
	ldr	r0, .L1482+40
	strb	r2, [r6, r3]
	ldrb	r2, [r4]	@ zero_extendqisi2
	bl	flash_mem_cmp8
	cbnz	r0, .L1467
	ldrb	r3, [r5]	@ zero_extendqisi2
	ldr	r2, .L1482+32
	str	r0, [r2, r3, lsl #2]
	adds	r2, r3, #1
	strb	r2, [r5]
	uxtb	r0, r6
	ldr	r2, .L1482+28
	strb	r0, [r2, r3]
	bl	zftl_flash_enter_slc_mode
.L1467:
	adds	r6, r6, #1
	cmp	r6, #4
	bne	.L1468
	ldrb	r3, [r4, #8]	@ zero_extendqisi2
	cmp	r3, #2
	beq	.L1469
.L1473:
	ldrb	r2, [r4, #13]	@ zero_extendqisi2
	ldrb	r3, [r5]	@ zero_extendqisi2
	smulbb	r3, r3, r2
	ldrh	r2, [r4, #14]
	smulbb	r3, r3, r2
	ldr	r2, .L1482+44
	strh	r3, [r2]	@ movhi
	add	sp, sp, #8
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r10, fp, pc}
.L1469:
	ldrh	r6, [r7]
	movs	r7, #0
	ldrb	r3, [r4, #13]	@ zero_extendqisi2
	ldrb	r10, [r4]	@ zero_extendqisi2
	ldrb	fp, [r4, #23]	@ zero_extendqisi2
	muls	r3, r6, r3
	ldrh	r6, [r4, #14]
	and	r6, r6, #65280
	muls	r6, r3, r6
	lsls	r3, r6, #1
	str	r3, [sp]
	ldr	r3, .L1482+28
.L1472:
	mov	r2, r10
	add	r1, r8, r7, lsl #3
	ldr	r0, .L1482+40
	str	r3, [sp, #4]
	bl	flash_mem_cmp8
	ldr	r3, [sp, #4]
	cbnz	r0, .L1470
	ldr	r1, [sp]
	ldrb	r2, [r5]	@ zero_extendqisi2
	ldr	r0, .L1482+32
	cmp	fp, #0
	it	eq
	moveq	r1, r6
	strb	r7, [r3, r2]
	str	r1, [r0, r2, lsl #2]
	adds	r1, r2, #1
	strb	r1, [r5]
.L1470:
	adds	r7, r7, #1
	cmp	r7, #4
	bne	.L1472
	b	.L1473
.L1483:
	.align	2
.L1482:
	.word	.LANCHOR19
	.word	.LANCHOR143
	.word	.LC1
	.word	.LANCHOR32
	.word	.LANCHOR23
	.word	.LANCHOR2
	.word	.LANCHOR144
	.word	.LANCHOR29
	.word	.LANCHOR145
	.word	.LANCHOR33
	.word	.LANCHOR32+1
	.word	.LANCHOR146
	.word	.LANCHOR47
	.size	flash_die_info_init, .-flash_die_info_init
	.section	.text.lpa_hash_init,"ax",%progbits
	.align	1
	.global	lpa_hash_init
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	lpa_hash_init, %function
lpa_hash_init:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r3, lr}
	mov	r2, #512
	movs	r1, #255
	ldr	r0, .L1485
	bl	ftl_memset
	ldr	r3, .L1485+4
	movs	r1, #255
	ldr	r2, .L1485+8
	ldrh	r3, [r3]
	ldrb	r2, [r2]	@ zero_extendqisi2
	muls	r2, r3, r2
	ldr	r3, .L1485+12
	ldr	r0, [r3]
	lsls	r2, r2, #2
	pop	{r3, lr}
	b	ftl_memset
.L1486:
	.align	2
.L1485:
	.word	.LANCHOR116
	.word	.LANCHOR94
	.word	.LANCHOR79
	.word	.LANCHOR118
	.size	lpa_hash_init, .-lpa_hash_init
	.section	.text.lpa_rebuild_hash,"ax",%progbits
	.align	1
	.global	lpa_rebuild_hash
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	lpa_rebuild_hash, %function
lpa_rebuild_hash:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r3, r4, r5, r6, r7, lr}
	ldr	r3, .L1498
	ldr	r3, [r3]
	lsls	r3, r3, #19
	bpl	.L1488
	movs	r3, #0
	movs	r2, #239
	ldr	r1, .L1498+4
	ldr	r0, .L1498+8
	bl	printf
.L1488:
	ldr	r6, .L1498+12
	mov	r2, #512
	ldr	r4, .L1498+16
	movs	r1, #255
	ldr	r0, .L1498+20
	bl	ftl_memset
	ldrh	r3, [r4]
	movs	r1, #255
	ldrb	r2, [r6]	@ zero_extendqisi2
	ldr	r5, .L1498+24
	muls	r2, r3, r2
	ldr	r0, [r5]
	lsls	r2, r2, #2
	bl	ftl_memset
	ldr	r3, .L1498+28
	movs	r2, #0
	ldrb	r6, [r6]	@ zero_extendqisi2
	ldr	ip, [r5]
	ldr	r7, [r3]
	ldr	r0, .L1498+20
.L1489:
	ldrh	r3, [r4]
	uxth	r5, r2
	mov	r1, r5
	muls	r3, r6, r3
	cmp	r5, r3, lsl #1
	blt	.L1491
	pop	{r3, r4, r5, r6, r7, pc}
.L1491:
	ldr	r3, [r7, r1, lsl #2]
	adds	r2, r2, #1
	cmp	r3, #-1
	itttt	ne
	uxtbne	r3, r3
	ldrhne	lr, [r0, r3, lsl #1]
	strhne	r5, [r0, r3, lsl #1]	@ movhi
	strhne	lr, [ip, r1, lsl #1]	@ movhi
	b	.L1489
.L1499:
	.align	2
.L1498:
	.word	.LANCHOR19
	.word	.LANCHOR147
	.word	.LC81
	.word	.LANCHOR79
	.word	.LANCHOR94
	.word	.LANCHOR116
	.word	.LANCHOR118
	.word	.LANCHOR117
	.size	lpa_rebuild_hash, .-lpa_rebuild_hash
	.section	.text.zftl_read_flash_info,"ax",%progbits
	.align	1
	.global	zftl_read_flash_info
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	zftl_read_flash_info, %function
zftl_read_flash_info:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, lr}
	movs	r2, #11
	movs	r1, #0
	mov	r4, r0
	bl	ftl_memset
	ldr	r1, .L1503
	movs	r2, #0
	ldr	r3, .L1503+4
	strb	r2, [r4, #10]
	ldrb	r0, [r1, #9]	@ zero_extendqisi2
	ldrh	r3, [r3]
	smulbb	r3, r3, r0
	uxth	r3, r3
	strb	r3, [r4, #4]
	lsrs	r3, r3, #8
	strb	r3, [r4, #5]
	ldr	r3, .L1503+8
	ldrb	r3, [r3]	@ zero_extendqisi2
	strb	r3, [r4, #7]
	ldr	r3, .L1503+12
	ldrb	r5, [r3]	@ zero_extendqisi2
	strb	r5, [r4]
	ldrb	r5, [r3, #1]	@ zero_extendqisi2
	strb	r5, [r4, #1]
	ldrb	r5, [r3, #2]	@ zero_extendqisi2
	ldrb	r3, [r3, #3]	@ zero_extendqisi2
	strb	r0, [r4, #6]
	strb	r5, [r4, #2]
	movs	r5, #1
	strb	r3, [r4, #3]
	movs	r3, #32
	strb	r3, [r4, #8]
	ldrb	r3, [r1, #7]	@ zero_extendqisi2
	ldr	r0, .L1503+16
	strb	r3, [r4, #9]
	ldr	r3, .L1503+20
	ldrb	r1, [r3]	@ zero_extendqisi2
	mov	r3, r2
.L1501:
	uxtb	r2, r3
	cmp	r1, r2
	bhi	.L1502
	pop	{r4, r5, r6, pc}
.L1502:
	ldrb	r2, [r3, r0]	@ zero_extendqisi2
	adds	r3, r3, #1
	ldrb	r6, [r4, #10]	@ zero_extendqisi2
	lsl	r2, r5, r2
	orrs	r2, r2, r6
	strb	r2, [r4, #10]
	b	.L1501
.L1504:
	.align	2
.L1503:
	.word	.LANCHOR32
	.word	.LANCHOR2
	.word	.LANCHOR49
	.word	.LANCHOR67
	.word	.LANCHOR29
	.word	.LANCHOR23
	.size	zftl_read_flash_info, .-zftl_read_flash_info
	.section	.text.gc_static_wearleveling,"ax",%progbits
	.align	1
	.global	gc_static_wearleveling
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	gc_static_wearleveling, %function
gc_static_wearleveling:
	@ args = 0, pretend = 0, frame = 32
	@ frame_needed = 0, uses_anonymous_args = 0
	ldr	r0, .L1624
	push	{r4, r5, r6, r7, r8, r10, fp, lr}
	sub	sp, sp, #48
	ldr	r3, [r0]
	ldr	r3, [r3, #32]
	cmp	r3, #10240
	bls	.L1506
	bl	ftl_tmp_into_update
.L1506:
	ldr	r3, .L1624+4
	ldr	r3, [r3]
	ldr	r2, [r3, #568]
	ldr	r1, [r3, #12]
	add	r4, r2, #35840
	adds	r4, r4, #160
	cmp	r1, r4
	bcs	.L1507
	ldr	r5, [r0]
	ldr	r4, [r3, #572]
	ldr	r5, [r5, #36]
	add	r4, r4, #256
	cmp	r5, r4
	bcc	.L1561
.L1507:
	add	r2, r2, #860160
	add	r2, r2, #3840
	cmp	r1, r2
	bhi	.L1509
	ldr	r4, [r0]
	ldr	r2, [r3, #572]
	ldr	r4, [r4, #36]
	adds	r2, r2, #32
	cmp	r4, r2
	bls	.L1562
.L1509:
	ldr	r2, [r0]
	movw	r4, #65535
	ldr	r10, .L1624+12
	mov	fp, r4
	movs	r5, #0
	ldrh	r7, [r2, #134]
	ldr	r0, [r2, #36]
	str	r5, [sp, #24]
	str	r1, [r3, #568]
	str	r0, [r3, #572]
	str	r5, [sp, #40]
	str	r5, [sp, #44]
	str	r5, [sp, #36]
	str	r5, [sp, #32]
	str	r5, [sp, #20]
	str	r5, [sp, #28]
.L1511:
	ldr	r3, .L1624+8
	ldrh	r3, [r3]
	cmp	r3, r7
	bhi	.L1522
	ldr	r7, .L1624+4
	movs	r3, #0
	movs	r1, #255
	movs	r2, #128
	ldr	r0, [r7]
	strh	r3, [r0, #122]	@ movhi
	add	r0, r0, #264
	bl	ftl_memset
	ldr	r3, [r7]
	ldrh	r7, [r3, #586]
	ldr	r3, .L1624+12
	ldr	r8, [r3]
	ldr	r3, .L1624+16
	ldr	r3, [r3]
	add	r10, r8, r7, lsl #2
	lsls	r1, r3, #21
	bpl	.L1523
	ldr	r1, .L1624+20
	ldr	r3, [r8, r7, lsl #2]
	ldrh	r2, [r8, r7, lsl #2]
	ldr	r1, [r1]
	ubfx	r3, r3, #11, #8
	ldr	r0, .L1624+24
	ubfx	r2, r2, #0, #11
	ldrh	r1, [r1, r7, lsl #1]
	str	r1, [sp, #12]
	ldrb	r1, [r10, #3]	@ zero_extendqisi2
	str	r1, [sp, #8]
	ldrb	r1, [r10, #2]	@ zero_extendqisi2
	lsrs	r1, r1, #5
	str	r1, [sp, #4]
	ldrb	r1, [r10, #2]	@ zero_extendqisi2
	ubfx	r1, r1, #3, #2
	str	r1, [sp]
	mov	r1, r7
	bl	printf
.L1523:
	ldrb	r3, [r10, #2]	@ zero_extendqisi2
	and	r1, r3, #224
	cmp	r1, #32
	bne	.L1524
	ldr	r2, .L1624
	ldr	r2, [r2]
	ldrh	r2, [r2, #688]
	cmp	r2, #2
	ittt	hi
	ldrhi	r2, .L1624+28
	movhi	r0, #1
	strhi	r0, [r2]
.L1524:
	lsls	r2, r3, #28
	bpl	.L1525
	ldr	r2, .L1624
	ldr	r2, [r2]
	ldrh	r0, [r2, #96]
	ldr	r2, .L1624+32
	ldrh	ip, [r2]
	ldrh	r2, [r8, r7, lsl #2]
	ubfx	r2, r2, #0, #11
	add	r2, r2, ip, lsr #2
	cmp	r0, r2
	ble	.L1525
	and	r3, r3, #192
	ldr	r7, .L1624+4
	cmp	r3, #64
	bne	.L1526
	ldr	r3, [r7]
	movs	r2, #1
	movs	r1, #0
	ldrh	r0, [r3, #586]
	bl	gc_add_sblk
	ldr	r3, .L1624+36
	movs	r2, #1
	strh	r2, [r3, #2180]	@ movhi
.L1525:
	ldr	r3, .L1624+4
	ldr	r3, [r3]
	ldrh	r7, [r3, #584]
	ldr	r3, .L1624+12
	ldr	r8, [r3]
	ldr	r3, .L1624+16
	ldr	r3, [r3]
	add	r10, r8, r7, lsl #2
	lsls	r6, r3, #21
	bpl	.L1527
	ldr	r1, .L1624+20
	ldr	r3, [r8, r7, lsl #2]
	ldrh	r2, [r8, r7, lsl #2]
	ldr	r1, [r1]
	ubfx	r3, r3, #11, #8
	ldr	r0, .L1624+40
	ubfx	r2, r2, #0, #11
	ldrh	r1, [r1, r7, lsl #1]
	str	r1, [sp, #12]
	ldrb	r1, [r10, #3]	@ zero_extendqisi2
	str	r1, [sp, #8]
	ldrb	r1, [r10, #2]	@ zero_extendqisi2
	lsrs	r1, r1, #5
	str	r1, [sp, #4]
	ldrb	r1, [r10, #2]	@ zero_extendqisi2
	ubfx	r1, r1, #3, #2
	str	r1, [sp]
	mov	r1, r7
	bl	printf
.L1527:
	ldrb	r3, [r10, #2]	@ zero_extendqisi2
	lsls	r0, r3, #28
	bpl	.L1528
	ldr	r2, .L1624
	ldr	r2, [r2]
	ldrh	r1, [r2, #98]
	ldr	r2, .L1624+44
	ldrh	r0, [r2]
	ldr	r2, [r8, r7, lsl #2]
	ubfx	r2, r2, #11, #8
	add	r2, r2, r0, lsr #2
	cmp	r1, r2
	ble	.L1528
	and	r2, r3, #192
	cmp	r2, #64
	bne	.L1529
	ldr	r3, .L1624+4
	movs	r2, #1
	movs	r1, #0
	ldr	r3, [r3]
	ldrh	r0, [r3, #584]
	bl	gc_add_sblk
	ldr	r3, .L1624+36
	movs	r2, #1
	strh	r2, [r3, #2180]	@ movhi
.L1528:
	ldr	r3, .L1624+16
	ldr	r3, [r3]
	lsls	r1, r3, #21
	bpl	.L1530
	ldr	r3, .L1624+12
	ldr	r1, .L1624+20
	ldr	r2, [r3]
	ldr	r1, [r1]
	ldr	r3, [r2, r5, lsl #2]
	ldrh	r1, [r1, r5, lsl #1]
	add	r0, r2, r5, lsl #2
	ldrh	r2, [r2, r5, lsl #2]
	ubfx	r3, r3, #11, #8
	str	r1, [sp, #12]
	ldrb	r1, [r0, #3]	@ zero_extendqisi2
	ubfx	r2, r2, #0, #11
	str	r1, [sp, #8]
	ldrb	r1, [r0, #2]	@ zero_extendqisi2
	lsrs	r1, r1, #5
	str	r1, [sp, #4]
	ldrb	r1, [r0, #2]	@ zero_extendqisi2
	ldr	r0, .L1624+48
	ubfx	r1, r1, #3, #2
	str	r1, [sp]
	mov	r1, r5
	bl	printf
.L1530:
	ldr	r3, .L1624+16
	ldr	r3, [r3]
	lsls	r2, r3, #21
	bpl	.L1531
	ldr	r3, .L1624+12
	ldr	r1, [sp, #24]
	ldr	r5, [sp, #24]
	ldr	r2, [r3]
	ldr	r3, [sp, #24]
	add	r0, r2, r3, lsl #2
	ldr	r3, [r2, r3, lsl #2]
	ldrh	r2, [r2, r1, lsl #2]
	ldr	r1, .L1624+20
	ubfx	r3, r3, #11, #8
	ubfx	r2, r2, #0, #11
	ldr	r1, [r1]
	ldrh	r1, [r1, r5, lsl #1]
	str	r1, [sp, #12]
	ldrb	r1, [r0, #3]	@ zero_extendqisi2
	str	r1, [sp, #8]
	ldrb	r1, [r0, #2]	@ zero_extendqisi2
	lsrs	r1, r1, #5
	str	r1, [sp, #4]
	ldrb	r1, [r0, #2]	@ zero_extendqisi2
	ldr	r0, .L1624+52
	ubfx	r1, r1, #3, #2
	str	r1, [sp]
	mov	r1, r5
	bl	printf
.L1531:
	ldr	r6, .L1624
	ldrh	r3, [sp, #20]
	ldr	r1, [sp, #32]
	ldr	r5, [r6]
	ldr	r0, [sp, #40]
	strh	r3, [r5, #96]	@ movhi
	ldrh	r3, [sp, #28]
	strh	r4, [r5, #92]	@ movhi
	strh	fp, [r5, #94]	@ movhi
	strh	r3, [r5, #98]	@ movhi
	bl	__aeabi_uidiv
	ldr	r1, [sp, #36]
	mov	r7, r0
	strh	r0, [r5, #88]	@ movhi
	ldr	r0, [sp, #44]
	bl	__aeabi_uidiv
	strh	r0, [r5, #90]	@ movhi
	ldr	r5, .L1624+16
	ldr	r3, [r5]
	lsls	r3, r3, #21
	bpl	.L1532
	uxth	r0, r0
	uxth	r3, r7
	ldr	r2, [sp, #36]
	str	r0, [sp]
	ldr	r1, [sp, #32]
	ldr	r0, .L1624+56
	bl	printf
.L1532:
	ldr	r3, [r5]
	ldr	r5, .L1624+44
	tst	r3, #1024
	beq	.L1533
	ldrh	r3, [r5]
	mov	r2, fp
	mov	r1, r4
	ldr	r0, .L1624+60
	str	r3, [sp, #8]
	b	.L1625
.L1626:
	.align	2
.L1624:
	.word	.LANCHOR110
	.word	.LANCHOR12
	.word	.LANCHOR8
	.word	.LANCHOR9
	.word	.LANCHOR19
	.word	.LANCHOR11
	.word	.LC83
	.word	.LANCHOR148
	.word	.LANCHOR149
	.word	.LANCHOR70
	.word	.LC84
	.word	.LANCHOR150
	.word	.LC85
	.word	.LC86
	.word	.LC87
	.word	.LC88
.L1625:
	ldr	r3, .L1627
	ldrh	r3, [r3]
	str	r3, [sp, #4]
	ldr	r3, [sp, #28]
	str	r3, [sp]
	ldr	r3, [sp, #20]
	bl	printf
.L1533:
	ldr	r3, [sp, #28]
	sub	r3, r3, fp
	str	r3, [sp, #24]
	ldr	r2, [sp, #24]
	ldrh	r3, [r5]
	cmp	r2, r3
	bgt	.L1534
	ldr	r2, .L1627
	ldr	r3, [sp, #20]
	ldrh	r2, [r2]
	subs	r3, r3, r4
	cmp	r3, r2
	ble	.L1563
.L1534:
	ldr	r3, .L1627+4
	mov	r8, #0
	ldr	r3, [r3]
	ldrh	r5, [r3, #580]
	ldr	r3, [r6]
	mov	r6, r8
	ldrh	r10, [r3, #134]
.L1536:
	ldr	r3, .L1627+8
	ldrh	r3, [r3]
	cmp	r10, r3
	bcc	.L1546
.L1545:
	ldr	r3, .L1627+4
	ldr	r3, [r3]
	str	r5, [r3, #580]
.L1535:
	cmp	fp, #0
	beq	.L1548
	ldr	r3, .L1627+12
	ldr	r1, [r3]
	ldr	r3, .L1627+8
	ldrh	r2, [r1, #134]
	ldrh	r7, [r3]
	ldr	r3, .L1627+16
	ldr	r3, [r3]
	add	r3, r3, r2, lsl #2
.L1549:
	cmp	r2, r7
	bcc	.L1551
	ldrh	r3, [r1, #72]
	add	r3, r3, fp
	strh	r3, [r1, #72]	@ movhi
	ldrh	r3, [r1, #98]
	cmp	fp, r3
	itt	cc
	subcc	r3, r3, fp
	strhcc	r3, [r1, #98]	@ movhi
.L1548:
	cbz	r4, .L1554
	ldr	r3, .L1627+12
	ldr	r1, [r3]
	ldr	r3, .L1627+8
	ldrh	r2, [r1, #134]
	ldrh	ip, [r3]
	ldr	r3, .L1627+16
	ldr	r3, [r3]
	add	r3, r3, r2, lsl #2
.L1555:
	cmp	r2, ip
	bcc	.L1557
	ldrh	r3, [r1, #74]
	add	r3, r3, r4
	strh	r3, [r1, #74]	@ movhi
	ldrh	r3, [r1, #96]
	cmp	r4, r3
	itt	cc
	subcc	r4, r3, r4
	strhcc	r4, [r1, #96]	@ movhi
.L1554:
	movs	r1, #0
	ldr	r0, .L1627+20
	bl	_list_get_gc_head_node
	movw	r2, #65535
	cmp	r0, r2
	beq	.L1510
	ldr	r2, .L1627+24
	ldr	r1, [r2]
	ldr	r2, .L1627+28
	ldrh	r3, [r1, r0, lsl #1]
	ldrh	r2, [r2]
	cmp	r3, r2, lsr #1
	bhi	.L1510
	adds	r6, r6, #1
	movs	r2, #1
	movs	r1, #0
	bl	gc_add_sblk
.L1510:
	add	r0, r6, r8
.L1505:
	add	sp, sp, #48
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r10, fp, pc}
.L1522:
	ldr	r0, [r10]
	lsls	r1, r7, #2
	add	ip, r0, r1
	ldrb	r3, [ip, #2]	@ zero_extendqisi2
	and	r2, r3, #224
	cmp	r2, #224
	beq	.L1512
	ubfx	lr, r3, #3, #2
	tst	lr, #1
	beq	.L1513
	ldrh	r3, [r0, r1]
	ldr	r2, [r0, r1]
	ubfx	r3, r3, #0, #11
	ubfx	r2, r2, #11, #8
.L1514:
	ldr	r6, [sp, #32]
	cmp	r4, r3
	add	r8, r6, #1
	uxth	r6, r8
	str	r6, [sp, #32]
	ldr	r6, [sp, #40]
	add	r6, r6, r3
	str	r6, [sp, #40]
	bls	.L1560
	ldr	r4, .L1627+4
	ldr	r4, [r4]
	strh	r7, [r4, #586]	@ movhi
	mov	r4, r3
.L1560:
	ldr	r6, [sp, #20]
	movw	r8, #65535
	cmp	r6, r3
	itt	cc
	movcc	r5, r7
	strcc	r3, [sp, #20]
	cmp	r2, r8
	bne	.L1516
.L1518:
	cmp	r3, #9
	bls	.L1521
.L1512:
	adds	r7, r7, #1
	uxth	r7, r7
	b	.L1511
.L1513:
	tst	r3, #24
	bne	.L1515
	ldrh	r3, [r0, r1]
	movw	r2, #65535
	ubfx	r3, r3, #0, #11
	b	.L1514
.L1515:
	ldr	r3, [r0, r1]
	ubfx	r2, r3, #11, #8
	movw	r3, #65535
.L1516:
	ldr	r6, [sp, #36]
	cmp	fp, r2
	it	hi
	movhi	fp, r2
	add	r8, r6, #1
	uxth	r6, r8
	it	hi
	ldrhi	r8, .L1627+4
	str	r6, [sp, #36]
	ldr	r6, [sp, #44]
	it	hi
	ldrhi	r8, [r8]
	add	r6, r6, r2
	str	r6, [sp, #44]
	ldr	r6, [sp, #28]
	it	hi
	strhhi	r7, [r8, #584]	@ movhi
	cmp	r6, r2
	itt	cc
	strcc	r7, [sp, #24]
	strcc	r2, [sp, #28]
	cmp	r2, #9
	bhi	.L1518
.L1521:
	ldr	r3, .L1627+32
	ldr	r3, [r3]
	lsls	r6, r3, #23
	bpl	.L1512
	ldr	r3, [r0, r1]
	ldrh	r2, [r0, r1]
	ldr	r1, .L1627+24
	ubfx	r3, r3, #11, #8
	ldr	r0, .L1627+36
	ubfx	r2, r2, #0, #11
	ldr	r1, [r1]
	ldrh	r1, [r1, r7, lsl #1]
	str	r1, [sp, #12]
	ldrb	r1, [ip, #3]	@ zero_extendqisi2
	str	r1, [sp, #8]
	ldrb	r1, [ip, #2]	@ zero_extendqisi2
	str	lr, [sp]
	lsrs	r1, r1, #5
	str	r1, [sp, #4]
	mov	r1, r7
	bl	printf
	b	.L1512
.L1526:
	cmp	r1, #0
	bne	.L1525
	ldr	r3, [r7]
	movw	r2, #65535
	ldrh	r8, [r3, #590]
	cmp	r8, r2
	bne	.L1525
	ldrh	r0, [r3, #586]
	ldrh	r3, [r3, #588]
	cmp	r3, r0
	beq	.L1525
	bl	zftl_remove_free_node
	ldr	r3, [r7]
	ldrh	r2, [r3, #586]
	strh	r8, [r3, #586]	@ movhi
	strh	r2, [r3, #590]	@ movhi
	b	.L1525
.L1529:
	and	r3, r3, #248
	cmp	r3, #16
	bne	.L1528
	ldr	r8, .L1627+4
	movw	r2, #65535
	ldr	r3, [r8]
	ldrh	r7, [r3, #588]
	cmp	r7, r2
	bne	.L1528
	ldrh	r0, [r3, #584]
	ldrh	r3, [r3, #590]
	cmp	r3, r0
	beq	.L1528
	bl	zftl_remove_free_node
	ldr	r3, [r8]
	ldrh	r2, [r3, #584]
	strh	r7, [r3, #584]	@ movhi
	strh	r2, [r3, #588]	@ movhi
	b	.L1528
.L1628:
	.align	2
.L1627:
	.word	.LANCHOR149
	.word	.LANCHOR12
	.word	.LANCHOR8
	.word	.LANCHOR110
	.word	.LANCHOR9
	.word	.LANCHOR92
	.word	.LANCHOR11
	.word	.LANCHOR94
	.word	.LANCHOR19
	.word	.LC82
.L1546:
	adds	r5, r5, #1
	uxth	r5, r5
	cmp	r3, r5
	it	ls
	movls	r5, #0
	ldr	r3, .L1629
	lsls	r7, r5, #2
	ldr	r3, [r3]
	adds	r2, r3, r7
	ldrb	r2, [r2, #2]	@ zero_extendqisi2
	tst	r2, #192
	beq	.L1538
	and	r0, r2, #224
	cmp	r0, #224
	beq	.L1538
	ubfx	r2, r2, #3, #2
	ands	r1, r2, #1
	beq	.L1539
	cmp	r0, #160
.L1622:
	bne	.L1541
	ldr	r2, .L1629+4
	ldr	r0, [sp, #24]
	ldrh	r2, [r2]
	cmp	r0, r2
	ble	.L1542
	ldr	r2, [r3, r7]
	ubfx	r2, r2, #11, #8
	cmp	r2, fp
	bls	.L1543
	cbz	r1, .L1542
	ldrh	r2, [r3, r7]
	ubfx	r2, r2, #0, #11
	cmp	r2, r4
	bgt	.L1542
.L1543:
	movs	r2, #1
	movs	r1, #0
	mov	r0, r5
	str	r3, [sp, #28]
	bl	gc_add_sblk
	ldr	r0, .L1629+8
	movs	r2, #1
	add	r6, r6, r2
	ldr	r3, [sp, #28]
	strh	r2, [r0, #2180]	@ movhi
	ldr	r2, .L1629+12
	ldr	r2, [r2]
	tst	r2, #1024
	beq	.L1542
	ldr	r2, .L1629+16
	ldr	r1, [r3, r7]
	ldr	r2, [r2]
	ubfx	r1, r1, #11, #8
	ldrh	ip, [r2, r5, lsl #1]
	ldr	r2, .L1629
	ldr	r2, [r2]
	add	r2, r2, r7
	ldrb	r2, [r2, #2]	@ zero_extendqisi2
	str	r1, [sp, #8]
	ldrh	r1, [r3, r7]
	lsrs	r2, r2, #5
	ubfx	r1, r1, #0, #11
	str	r1, [sp, #4]
	mov	r1, r5
	ldrh	r3, [r0, #52]
	ldr	r0, .L1629+20
	str	r3, [sp]
	mov	r3, ip
.L1623:
	bl	printf
.L1542:
	cmp	r6, #4
	bhi	.L1545
	cmp	r8, #4
	bhi	.L1545
.L1538:
	add	r10, r10, #1
	uxth	r10, r10
	b	.L1536
.L1539:
	cmp	r2, #2
	b	.L1622
.L1541:
	ldr	r0, .L1629+24
	ldr	r2, [sp, #20]
	ldrh	r0, [r0]
	subs	r2, r2, r4
	cmp	r2, r0
	ble	.L1542
	ldrh	r2, [r3, r7]
	add	r0, r4, #8
	ubfx	r2, r2, #0, #11
	cmp	r2, r0
	ble	.L1544
	cmp	r1, #0
	beq	.L1542
	ldr	r2, [r3, r7]
	add	r1, fp, #4
	ubfx	r2, r2, #11, #8
	cmp	r2, r1
	bgt	.L1542
.L1544:
	movs	r2, #1
	movs	r1, #0
	mov	r0, r5
	str	r3, [sp, #28]
	bl	gc_add_sblk
	ldr	r0, .L1629+8
	movs	r2, #1
	add	r8, r8, r2
	ldr	r3, [sp, #28]
	strh	r2, [r0, #2180]	@ movhi
	ldr	r2, .L1629+12
	ldr	r2, [r2]
	tst	r2, #1024
	beq	.L1542
	ldr	r2, .L1629+16
	ldr	r1, [r3, r7]
	ldr	r2, [r2]
	ubfx	r1, r1, #11, #8
	ldrh	ip, [r2, r5, lsl #1]
	ldr	r2, .L1629
	ldr	r2, [r2]
	add	r2, r2, r7
	ldrb	r2, [r2, #2]	@ zero_extendqisi2
	str	r1, [sp, #8]
	ldrh	r1, [r3, r7]
	lsrs	r2, r2, #5
	ubfx	r1, r1, #0, #11
	str	r1, [sp, #4]
	mov	r1, r5
	ldrh	r3, [r0, #52]
	ldr	r0, .L1629+28
	str	r3, [sp]
	mov	r3, ip
	b	.L1623
.L1563:
	mov	r8, #0
	mov	r6, r8
	b	.L1535
.L1551:
	ldr	r0, [r3]
	ubfx	r5, r0, #11, #8
	cmp	fp, r5
	bhi	.L1550
	ldrb	ip, [r3, #2]	@ zero_extendqisi2
	tst	ip, #24
	ittt	ne
	subne	r5, r5, fp
	bfine	r0, r5, #11, #8
	strne	r0, [r3]
.L1550:
	adds	r2, r2, #1
	adds	r3, r3, #4
	uxth	r2, r2
	b	.L1549
.L1557:
	ldrh	r0, [r3]
	ubfx	r5, r0, #0, #11
	cmp	r5, r4
	blt	.L1556
	ldrb	r7, [r3, #2]	@ zero_extendqisi2
	and	r7, r7, #24
	cmp	r7, #16
	ittt	ne
	subne	r5, r5, r4
	bfine	r0, r5, #0, #11
	strhne	r0, [r3]	@ movhi
.L1556:
	adds	r2, r2, #1
	adds	r3, r3, #4
	uxth	r2, r2
	b	.L1555
.L1562:
	mov	r8, #0
	mov	r6, r8
	b	.L1510
.L1561:
	movs	r0, #0
	b	.L1505
.L1630:
	.align	2
.L1629:
	.word	.LANCHOR9
	.word	.LANCHOR150
	.word	.LANCHOR70
	.word	.LANCHOR19
	.word	.LANCHOR11
	.word	.LC89
	.word	.LANCHOR149
	.word	.LC90
	.size	gc_static_wearleveling, .-gc_static_wearleveling
	.section	.text.zftl_sblk_list_init,"ax",%progbits
	.align	1
	.global	zftl_sblk_list_init
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	zftl_sblk_list_init, %function
zftl_sblk_list_init:
	@ args = 0, pretend = 0, frame = 24
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, r8, r10, fp, lr}
	movs	r2, #6
	ldr	r8, .L1663+84
	sub	sp, sp, #24
	movs	r1, #0
	movs	r4, #0
	ldr	fp, .L1663+88
	ldrh	r3, [r8]
	ldr	r6, .L1663
	ldr	r0, [fp]
	ldr	r10, .L1663+80
	muls	r2, r3, r2
	ldr	r7, .L1663+4
	bl	ftl_memset
	ldr	r3, .L1663+8
	movs	r2, #32
	ldr	r1, .L1663+12
	mov	r0, #32768
	strh	r4, [r10]	@ movhi
	str	r4, [r3]
	ldr	r3, .L1663+16
	ldrh	r1, [r1]
	strh	r4, [r7]	@ movhi
	str	r4, [r3]
	ldr	r3, .L1663+20
	str	r4, [r3]
	ldr	r3, .L1663+24
	str	r4, [r3]
	ldr	r3, .L1663+28
	str	r4, [r3]
	ldr	r3, .L1663+32
	str	r4, [r3]
	ldr	r3, .L1663+36
	strh	r2, [r3]	@ movhi
	ldr	r2, .L1663+40
	ldr	r3, .L1663+44
	strh	r4, [r2]	@ movhi
	ldr	r2, .L1663+48
	strh	r4, [r3]	@ movhi
	str	r3, [sp, #4]
	strh	r4, [r2]	@ movhi
	ldr	r2, .L1663+52
	strh	r4, [r2]	@ movhi
	ldrb	r2, [r6]	@ zero_extendqisi2
	muls	r1, r2, r1
	bl	__aeabi_idiv
	ldr	r2, .L1663+56
	sxth	r3, r0
	str	fp, [sp, #12]
	mov	fp, r10
	str	r3, [sp]
	ldr	r1, [r2]
	ldr	r3, [sp, #4]
	ldr	r10, .L1663+92
	ldrsh	r5, [r1, #134]
	str	r8, [sp, #8]
	mov	r8, r3
	strh	r4, [r1, #146]	@ movhi
	str	r2, [sp, #16]
	str	r6, [sp, #20]
.L1632:
	ldr	r3, [sp, #8]
	ldrh	r3, [r3]
	cmp	r5, r3
	blt	.L1649
	ldr	r3, [sp, #16]
	ldrh	r2, [r8]
	ldr	r3, [r3]
	strh	r2, [r3, #114]	@ movhi
	ldrh	r2, [r7]
	strh	r2, [r3, #118]	@ movhi
	ldrh	r2, [fp]
	strh	r2, [r3, #116]	@ movhi
	ldr	r2, .L1663+40
	ldrh	r2, [r2]
	strh	r2, [r3, #122]	@ movhi
	ldr	r2, .L1663+48
	ldrh	r2, [r2]
	strh	r2, [r3, #120]	@ movhi
	ldr	r2, .L1663+52
	ldrh	r2, [r2]
	strh	r2, [r3, #124]	@ movhi
	add	sp, sp, #24
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r10, fp, pc}
.L1649:
	ldr	r6, [r10]
	add	r6, r6, r5, lsl #2
	ldrb	r0, [r6, #3]	@ zero_extendqisi2
	cmp	r0, #0
	beq	.L1650
	ldr	r3, [sp, #20]
	ldrb	lr, [r3]	@ zero_extendqisi2
	ldr	r3, .L1663+56
	ldr	ip, [r3]
	ldr	r3, .L1663+12
	ldrh	r3, [r3]
	str	r3, [sp, #4]
	movs	r3, #0
	mov	r1, r3
.L1634:
	cmp	r3, lr
	blt	.L1637
	cmp	r1, #0
	beq	.L1638
	mov	r0, #32768
	bl	__aeabi_idiv
	adds	r1, r0, #1
	sxth	r1, r1
.L1633:
	ldr	r3, [sp, #12]
	lsls	r0, r5, #1
	adds	r2, r0, r5
	ldr	r3, [r3]
	add	ip, r3, r2, lsl #1
	strh	r1, [ip, #4]	@ movhi
	movw	r1, #65535
	strh	r1, [ip, #2]	@ movhi
	strh	r1, [r3, r2, lsl #1]	@ movhi
	ldrb	r3, [r6, #2]	@ zero_extendqisi2
	and	r3, r3, #224
	cmp	r3, #32
	beq	.L1639
	cmp	r3, #224
	beq	.L1639
	ldr	r2, .L1663+60
	ldr	r2, [r2]
	ldrh	r1, [r2, #16]
	cmp	r5, r1
	beq	.L1639
	ldrh	r1, [r2, #48]
	cmp	r5, r1
	beq	.L1639
	ldrh	r2, [r2, #80]
	cmp	r5, r2
	beq	.L1639
	cmp	r3, #64
	bne	.L1640
	ldr	r2, .L1663+40
	uxth	r1, r5
	ldr	r0, .L1663+28
.L1661:
	bl	_insert_data_list
.L1639:
	adds	r5, r5, #1
	sxth	r5, r5
	b	.L1632
.L1637:
	asr	r2, r0, r3
	adds	r3, r3, #1
	lsls	r2, r2, #31
	itete	mi
	ldrhmi	r2, [ip, #146]
	ldrpl	r2, [sp, #4]
	addmi	r2, r2, #1
	addpl	r1, r1, r2
	ite	mi
	strhmi	r2, [ip, #146]	@ movhi
	sxthpl	r1, r1
	b	.L1634
.L1638:
	ldrb	r3, [r6, #2]	@ zero_extendqisi2
	movw	r2, #65535
	orr	r3, r3, #224
	strb	r3, [r6, #2]
	ldr	r3, .L1663+64
	ldr	r3, [r3]
	strh	r2, [r3, r5, lsl #1]	@ movhi
	b	.L1633
.L1650:
	ldr	r1, [sp]
	b	.L1633
.L1640:
	cmp	r3, #96
	bne	.L1641
	ldr	r2, .L1663+52
	uxth	r1, r5
	ldr	r0, .L1663+24
	b	.L1661
.L1641:
	cmp	r3, #160
	bne	.L1642
	ldr	r2, .L1663+48
	uxth	r1, r5
	ldr	r0, .L1663+32
	b	.L1661
.L1642:
	cmp	r3, #0
	bne	.L1639
	ldr	r3, .L1663+64
	ldr	r3, [r3]
	ldrh	r2, [r3, r0]
	cbz	r2, .L1643
	cmp	r4, #2
	bgt	.L1644
	mov	r1, r5
	ldr	r0, .L1663+68
	bl	printf
	ldrb	r3, [r6, #2]	@ zero_extendqisi2
	adds	r4, r4, #1
	movs	r1, #1
	uxth	r0, r5
	sxth	r4, r4
	lsls	r2, r3, #27
	ite	mi
	movmi	r2, #5
	movpl	r2, #2
	bfi	r3, r2, #5, #3
	movs	r2, #0
	strb	r3, [r6, #2]
	bl	gc_add_sblk
	b	.L1639
.L1644:
	mov	r2, #656
	ldr	r1, .L1663+72
	ldr	r0, .L1663+76
	bl	printf
.L1643:
	ldrb	r3, [r6, #2]	@ zero_extendqisi2
	uxth	r1, r5
	ands	r3, r3, #24
	bne	.L1647
	ldr	r2, .L1663+44
	ldr	r0, .L1663+8
.L1662:
	bl	_insert_free_list
	b	.L1639
.L1647:
	cmp	r3, #16
	ittee	eq
	ldreq	r2, .L1663+4
	ldreq	r0, .L1663+16
	ldrne	r2, .L1663+80
	ldrne	r0, .L1663+20
	b	.L1662
.L1664:
	.align	2
.L1663:
	.word	.LANCHOR79
	.word	.LANCHOR105
	.word	.LANCHOR104
	.word	.LANCHOR85
	.word	.LANCHOR106
	.word	.LANCHOR108
	.word	.LANCHOR90
	.word	.LANCHOR95
	.word	.LANCHOR92
	.word	.LANCHOR109
	.word	.LANCHOR97
	.word	.LANCHOR103
	.word	.LANCHOR91
	.word	.LANCHOR99
	.word	.LANCHOR110
	.word	.LANCHOR12
	.word	.LANCHOR11
	.word	.LC91
	.word	.LANCHOR151
	.word	.LC0
	.word	.LANCHOR107
	.word	.LANCHOR8
	.word	.LANCHOR4
	.word	.LANCHOR9
	.size	zftl_sblk_list_init, .-zftl_sblk_list_init
	.section	.text.pm_free_sblk,"ax",%progbits
	.align	1
	.global	pm_free_sblk
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	pm_free_sblk, %function
pm_free_sblk:
	@ args = 0, pretend = 0, frame = 272
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, r8, r10, fp, lr}
	sub	sp, sp, #280
	ldr	r5, .L1690
	ldrh	r2, [r5]
	cmp	r2, #128
	bls	.L1666
	movs	r2, #94
	ldr	r1, .L1690+4
	ldr	r0, .L1690+8
	bl	printf
.L1666:
	ldr	r4, .L1690+12
	movs	r2, #0
	ldrh	r5, [r5]
	mov	r3, r2
	movw	r6, #65535
	ldr	r1, [r4]
	ldrh	r0, [r1, #688]
	add	r1, r1, #416
.L1669:
	ldrh	r7, [r1], #2
	cmp	r7, r6
	itt	ne
	addne	r2, r2, #1
	uxthne	r2, r2
	cmp	r2, r0
	bcs	.L1668
	cmp	r2, r5
	bcs	.L1668
	adds	r3, r3, #1
	uxth	r3, r3
	cmp	r3, #128
	bne	.L1669
.L1668:
	adds	r3, r3, #1
	mov	r2, #256
	uxth	r3, r3
	movs	r1, #0
	add	r0, sp, #24
	cmp	r3, #129
	mov	r5, #1
	it	eq
	moveq	r3, #128
	movs	r6, #0
	str	r3, [sp, #8]
	add	fp, sp, #24
	bl	ftl_memset
	ldr	r2, .L1690+16
	ldr	r7, [r4]
	ldrh	r8, [r2]
	ldr	r2, .L1690+20
	add	r10, r7, #704
	ldrh	r3, [r7, #698]
	ldrb	r2, [r2]	@ zero_extendqisi2
	rsb	r2, r2, #24
	sub	r2, r2, r8
	lsls	r5, r5, r2
	ldr	r2, .L1690+24
	subs	r5, r5, #1
	ldrb	r2, [r2]	@ zero_extendqisi2
.L1671:
	uxth	r1, r6
	cmp	r3, r1
	bhi	.L1674
	ldr	r3, .L1690+28
	movs	r5, #0
	ldr	r2, .L1690+32
	movw	r10, #65535
	mov	r8, r5
	ldrb	r6, [r3]	@ zero_extendqisi2
	ldrh	r2, [r2]
	str	r3, [sp, #12]
	smulbb	r6, r6, r2
	uxth	r6, r6
.L1680:
	ldr	r2, [r4]
	add	r7, r5, #208
	uxth	fp, r5
	ldrh	r3, [r2, r7, lsl #1]
	ldrh	r0, [r2, #692]
	str	r2, [sp, #16]
	str	r3, [sp, #20]
	ldr	r3, .L1690+24
	ldrb	r1, [r3]	@ zero_extendqisi2
	bl	__aeabi_idiv
	ldr	r3, [sp, #20]
	ldr	r2, [sp, #16]
	cmp	r0, r3
	bne	.L1675
	ldr	r1, [sp, #12]
	ldr	r0, .L1690+32
	ldrb	r1, [r1]	@ zero_extendqisi2
	ldrh	r0, [r0]
	smulbb	r1, r1, r0
	add	r0, sp, #24
	strh	r1, [r0, r5, lsl #1]	@ movhi
.L1675:
	add	r1, sp, #24
	ldrh	r1, [r1, r5, lsl #1]
	cmp	r1, r6
	bcs	.L1676
	cmp	r1, #0
	itt	ne
	movne	r8, fp
	movne	r6, r1
.L1676:
	ldrh	r0, [r2, #74]
	cmp	r0, #2
	bls	.L1677
	movw	r0, #65535
	cmp	r3, r0
	beq	.L1677
	ldr	r0, .L1690+36
	ldrh	r2, [r2, #92]
	ldr	r0, [r0]
	adds	r2, r2, #4
	ldrh	r0, [r0, r3, lsl #2]
	ubfx	r0, r0, #0, #11
	cmp	r0, r2
	bgt	.L1677
	mov	r10, fp
	str	r0, [sp]
	mov	r2, r1
	ldr	r0, .L1690+40
	mov	r1, r5
	bl	printf
.L1677:
	add	r3, sp, #24
	ldrh	r2, [r3, r5, lsl #1]
	cbnz	r2, .L1678
	ldr	r1, [r4]
	movw	r0, #65535
	ldrh	r3, [r1, r7, lsl #1]
	cmp	r3, r0
	beq	.L1678
	ldr	r0, .L1690+44
	ldr	r0, [r0]
	lsls	r0, r0, #19
	bpl	.L1679
	ldrh	r1, [r1, #688]
	ldr	r0, .L1690+48
	str	r1, [sp]
	mov	r1, r5
	bl	printf
.L1679:
	ldr	r3, [r4]
	ldrh	r0, [r3, r7, lsl #1]
	bl	ftl_free_sblk
	ldr	r3, [r4]
	movw	r2, #65535
	strh	r2, [r3, r7, lsl #1]	@ movhi
	ldrh	r2, [r3, #688]
	subs	r2, r2, #1
	strh	r2, [r3, #688]	@ movhi
.L1678:
	adds	r5, r5, #1
	ldr	r2, [sp, #8]
	uxth	r3, r5
	cmp	r3, r2
	bcc	.L1680
	movw	r0, #65535
	cmp	r10, r0
	ite	ne
	movne	r0, r10
	moveq	r0, r8
	add	sp, sp, #280
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r10, fp, pc}
.L1674:
	ldr	r0, [r10], #4
	mov	r1, r2
	str	r3, [sp, #20]
	str	r2, [sp, #16]
	lsr	r0, r0, r8
	ands	r0, r0, r5
	bl	__aeabi_uidiv
	uxth	r3, r0
	ldr	r2, [sp, #16]
	add	lr, r7, #416
	str	r3, [sp, #12]
	movs	r1, #0
	ldr	r3, [sp, #20]
.L1673:
	ldrh	ip, [lr], #2
	ldr	r0, [sp, #12]
	cmp	r0, ip
	ldr	r0, [sp, #8]
	ittt	eq
	ldrheq	ip, [fp, r1, lsl #1]
	addeq	ip, ip, #1
	strheq	ip, [fp, r1, lsl #1]	@ movhi
	adds	r1, r1, #1
	uxth	ip, r1
	cmp	r0, ip
	bhi	.L1673
	adds	r6, r6, #1
	b	.L1671
.L1691:
	.align	2
.L1690:
	.word	.LANCHOR152
	.word	.LANCHOR153
	.word	.LC0
	.word	.LANCHOR110
	.word	.LANCHOR74
	.word	.LANCHOR31
	.word	.LANCHOR75
	.word	.LANCHOR79
	.word	.LANCHOR94
	.word	.LANCHOR9
	.word	.LC92
	.word	.LANCHOR19
	.word	.LC93
	.size	pm_free_sblk, .-pm_free_sblk
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
	.section	.text.flash_info_data_init,"ax",%progbits
	.align	1
	.global	flash_info_data_init
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	flash_info_data_init, %function
flash_info_data_init:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	ldr	r3, .L1698
	push	{r4, lr}
	ldr	r3, [r3]
	lsls	r3, r3, #19
	bpl	.L1694
	ldr	r2, .L1698+4
	movs	r1, #120
	ldr	r0, .L1698+8
	bl	printf
.L1694:
	ldr	r4, .L1698+12
	mov	r2, #2048
	movs	r1, #0
	ldr	r0, [r4]
	bl	ftl_memset
	ldr	r0, [r4]
	movs	r2, #32
	ldr	r3, .L1698+16
	ldr	r1, .L1698+20
	adds	r0, r0, #80
	str	r3, [r0, #-80]
	mov	r3, #2032
	str	r3, [r0, #-72]
	movs	r3, #1
	strh	r3, [r0, #-64]	@ movhi
	bl	ftl_memcpy
	ldr	r0, [r4]
	movs	r2, #32
	ldr	r1, .L1698+24
	pop	{r4, lr}
	adds	r0, r0, #48
	b	ftl_memcpy
.L1699:
	.align	2
.L1698:
	.word	.LANCHOR19
	.word	.LANCHOR154
	.word	.LC94
	.word	.LANCHOR6
	.word	1398362953
	.word	.LANCHOR25
	.word	.LANCHOR32
	.size	flash_info_data_init, .-flash_info_data_init
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
.L1701:
	cmp	r3, r2
	bne	.L1702
	pop	{r4, pc}
.L1702:
	ldr	r4, [r1, r3, lsl #2]
	str	r4, [r0, r3, lsl #2]
	adds	r3, r3, #1
	b	.L1701
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
	ldr	r0, .L1705
	bx	lr
.L1706:
	.align	2
.L1705:
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
	.section	.text.nandc_init,"ax",%progbits
	.align	1
	.global	nandc_init
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	nandc_init, %function
nandc_init:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, lr}
	movs	r3, #0
	ldr	r6, .L1727
	sub	sp, sp, #20
	mov	r4, r0
	str	r3, [sp, #12]
	ldr	r3, [r6]
	lsls	r0, r3, #19
	bpl	.L1709
	mov	r2, r4
	ldr	r1, .L1727+4
	ldr	r0, .L1727+8
	bl	printf
.L1709:
	ldr	r1, [r4, #352]
	movs	r3, #6
	ldr	r2, .L1727+12
	ldr	r5, .L1727+16
	ldr	r7, .L1727+20
	cmp	r1, r2
	ldr	r2, [r4, #128]
	strb	r3, [r5]
	itt	eq
	moveq	r3, #8
	strbeq	r3, [r5]
	ldr	r3, .L1727+24
	str	r4, [r7]
	cmp	r2, r3
	ldr	r2, .L1727+28
	itt	eq
	moveq	r3, #9
	strbeq	r3, [r5]
	ldrb	r3, [r5]	@ zero_extendqisi2
	cmp	r3, #9
	ldr	r3, .L1727+32
	bne	.L1712
	movs	r1, #1
	strb	r1, [r3]
	movs	r1, #2
	ldr	r3, [sp, #12]
	orr	r3, r3, #256
	str	r3, [sp, #12]
	ldr	r3, [sp, #12]
	bfi	r3, r1, #18, #3
	str	r3, [sp, #12]
	ldr	r3, [sp, #12]
	str	r3, [r4]
	movs	r3, #0
	str	r3, [r4, #520]
	movw	r3, #4161
	str	r3, [r4, #4]
	movw	r3, #8321
	str	r3, [r4, #8]
	movs	r3, #38
	str	r2, [r4, #80]
	str	r3, [r4, #84]
	movs	r3, #39
	str	r3, [r4, #84]
	ldr	r3, [r6]
	lsls	r1, r3, #19
	bpl	.L1714
	ldr	r1, [r4]
	ldr	r2, [r4, #8]
	ldr	r3, [r4, #80]
	ldr	r0, [r4, #84]
	ldr	r4, [r4, #88]
	stm	sp, {r0, r4}
.L1726:
	ldr	r0, .L1727+36
	bl	printf
.L1714:
	ldr	r3, .L1727+40
	movs	r2, #1
	strb	r2, [r3]
	movs	r3, #0
	ldr	r2, .L1727+44
	strh	r3, [r2]	@ movhi
	ldr	r2, .L1727+48
	strb	r3, [r2]
	ldr	r3, [r6]
	lsls	r3, r3, #19
	bpl	.L1708
	ldrb	r1, [r5]	@ zero_extendqisi2
	ldr	r0, .L1727+52
	bl	printf
.L1708:
	add	sp, sp, #20
	@ sp needed
	pop	{r4, r5, r6, r7, pc}
.L1712:
	movs	r1, #0
	movs	r0, #1
	strb	r1, [r3]
	ldr	r3, [sp, #12]
	orr	r3, r3, #256
	str	r3, [sp, #12]
	ldr	r3, [sp, #12]
	bfi	r3, r0, #24, #3
	mov	r0, #2048
	str	r3, [sp, #12]
	ldr	r3, [sp, #12]
	str	r3, [r4]
	movw	r3, #4193
	str	r1, [r4, #336]
	str	r3, [r4, #4]
	movw	r3, #8321
	str	r3, [r4, #344]
	movs	r3, #38
	str	r2, [r4, #304]
	str	r3, [r4, #308]
	movs	r3, #39
	str	r3, [r4, #308]
	bl	ftl_malloc
	ldr	r3, .L1727+56
	str	r0, [r3]
	ldr	r3, [r6]
	lsls	r2, r3, #19
	bpl	.L1714
	ldr	r0, [r7]
	ldr	r1, [r0]
	ldr	r2, [r0, #344]
	ldr	r3, [r0, #304]
	ldr	r4, [r0, #308]
	ldr	r0, [r0, #312]
	str	r4, [sp]
	str	r0, [sp, #4]
	b	.L1726
.L1728:
	.align	2
.L1727:
	.word	.LANCHOR19
	.word	.LANCHOR155
	.word	.LC95
	.word	1446522928
	.word	.LANCHOR27
	.word	.LANCHOR7
	.word	1446588464
	.word	1052675
	.word	.LANCHOR50
	.word	.LC96
	.word	.LANCHOR51
	.word	.LANCHOR53
	.word	.LANCHOR49
	.word	.LC97
	.word	.LANCHOR52
	.size	nandc_init, .-nandc_init
	.section	.text.zbuf_init,"ax",%progbits
	.align	1
	.global	zbuf_init
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	zbuf_init, %function
zbuf_init:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, r8, lr}
	movs	r5, #0
	ldr	r4, .L1732
	mov	r6, r5
	ldr	r8, .L1732+12
	mov	r7, r4
.L1730:
	ldrb	r0, [r8]	@ zero_extendqisi2
	uxtb	r3, r5
	strb	r6, [r4, #2]
	adds	r5, r5, #1
	adds	r2, r3, #1
	strb	r3, [r4, #1]
	strb	r2, [r4]
	adds	r4, r4, #48
	str	r6, [r4, #-40]
	lsls	r0, r0, #9
	bl	ftl_malloc
	str	r0, [r4, #-44]
	movs	r0, #64
	bl	ftl_malloc
	cmp	r5, #32
	str	r0, [r4, #-36]
	bne	.L1730
	movs	r3, #255
	strb	r3, [r7, #1488]
	ldr	r3, .L1732+4
	strb	r6, [r3]
	ldr	r3, .L1732+8
	strb	r5, [r3]
	pop	{r4, r5, r6, r7, r8, pc}
.L1733:
	.align	2
.L1732:
	.word	.LANCHOR55
	.word	.LANCHOR56
	.word	.LANCHOR57
	.word	.LANCHOR131
	.size	zbuf_init, .-zbuf_init
	.section	.text.gc_init,"ax",%progbits
	.align	1
	.global	gc_init
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	gc_init, %function
gc_init:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	ldr	r3, .L1735
	movw	r2, #2204
	push	{r4, r5, r6, lr}
	movs	r4, #0
	ldr	r5, .L1735+4
	mov	r1, r4
	strb	r4, [r3]
	ldr	r3, .L1735+8
	mov	r0, r5
	strb	r4, [r3]
	ldr	r3, .L1735+12
	str	r4, [r3]
	ldr	r3, .L1735+16
	strh	r4, [r3]	@ movhi
	bl	ftl_memset
	movw	r3, #65535
	str	r4, [r5, #8]
	strh	r3, [r5]	@ movhi
	ldr	r3, .L1735+20
	ldrh	r3, [r3]
	lsrs	r2, r3, #1
	lsrs	r1, r3, #2
	strh	r2, [r5, #34]	@ movhi
	ldr	r2, .L1735+24
	strh	r1, [r5, #32]	@ movhi
	ldr	r5, .L1735+28
	strh	r4, [r2]	@ movhi
	ldr	r2, .L1735+32
	strh	r4, [r2]	@ movhi
	ldr	r2, .L1735+36
	strh	r4, [r2]	@ movhi
	ldr	r4, .L1735+40
	ldrb	r0, [r4]	@ zero_extendqisi2
	smulbb	r2, r0, r3
	uxth	r2, r2
	sub	r6, r2, #32
	strh	r6, [r5]	@ movhi
	ldr	r5, .L1735+44
	strh	r2, [r5]	@ movhi
	ldr	r2, .L1735+48
	ldr	r5, .L1735+52
	strh	r3, [r2]	@ movhi
	movs	r2, #4
	ldr	r3, .L1735+56
	strh	r2, [r3]	@ movhi
	ldr	r3, .L1735+60
	strh	r1, [r3]	@ movhi
	ldrh	r3, [r5]
	muls	r0, r3, r0
	lsls	r0, r0, #2
	bl	ftl_malloc
	ldr	r3, .L1735+64
	str	r0, [r3]
	ldrh	r3, [r5]
	ldrb	r0, [r4]	@ zero_extendqisi2
	muls	r0, r3, r0
	lsls	r0, r0, #2
	bl	ftl_malloc
	ldr	r3, .L1735+68
	str	r0, [r3]
	ldrh	r3, [r5]
	ldrb	r0, [r4]	@ zero_extendqisi2
	muls	r0, r3, r0
	bl	ftl_malloc
	ldr	r3, .L1735+72
	str	r0, [r3]
	ldrh	r3, [r5]
	ldrb	r0, [r4]	@ zero_extendqisi2
	muls	r0, r3, r0
	lsls	r0, r0, #2
	bl	ftl_malloc
	ldr	r3, .L1735+76
	str	r0, [r3]
	ldrh	r3, [r5]
	ldrb	r0, [r4]	@ zero_extendqisi2
	muls	r0, r3, r0
	lsls	r0, r0, #2
	bl	ftl_malloc
	ldr	r3, .L1735+80
	ldr	r2, .L1735+84
	str	r0, [r3]
	ldr	r3, .L1735+88
	ldrh	r3, [r3]
	lsrs	r3, r3, #2
	strh	r3, [r2]	@ movhi
	pop	{r4, r5, r6, pc}
.L1736:
	.align	2
.L1735:
	.word	.LANCHOR84
	.word	.LANCHOR70
	.word	.LANCHOR156
	.word	.LANCHOR157
	.word	.LANCHOR96
	.word	.LANCHOR94
	.word	.LANCHOR87
	.word	.LANCHOR102
	.word	.LANCHOR88
	.word	.LANCHOR89
	.word	.LANCHOR79
	.word	.LANCHOR100
	.word	.LANCHOR93
	.word	.LANCHOR85
	.word	.LANCHOR158
	.word	.LANCHOR69
	.word	.LANCHOR159
	.word	.LANCHOR160
	.word	.LANCHOR82
	.word	.LANCHOR76
	.word	.LANCHOR161
	.word	.LANCHOR86
	.word	.LANCHOR98
	.size	gc_init, .-gc_init
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
	ldr	r3, .L1741
	add	r1, r1, r0
	push	{r4, lr}
.L1739:
	cmp	r0, r1
	bne	.L1740
	mov	r0, r3
	pop	{r4, pc}
.L1740:
	lsrs	r2, r3, #2
	ldrb	r4, [r0], #1	@ zero_extendqisi2
	add	r2, r2, r3, lsl #5
	add	r2, r2, r4
	eors	r3, r3, r2
	b	.L1739
.L1742:
	.align	2
.L1741:
	.word	1204201446
	.size	js_hash, .-js_hash
	.section	.text.ftl_debug_info_fill,"ax",%progbits
	.align	1
	.global	ftl_debug_info_fill
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	ftl_debug_info_fill, %function
ftl_debug_info_fill:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	ldr	r3, .L1749
	push	{r4, lr}
	mov	r4, r1
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, #8
	bls	.L1744
	cmp	r0, #2
	bne	.L1745
	cbz	r2, .L1745
	ldr	r3, .L1749+4
	mov	r0, r2
	str	r3, [r1]
	mov	r1, #1024
	bl	js_hash
	str	r0, [r4, #4]
.L1744:
	movs	r0, #0
	pop	{r4, pc}
.L1745:
	movs	r3, #0
	str	r3, [r4]
	str	r3, [r4, #4]
	b	.L1744
.L1750:
	.align	2
.L1749:
	.word	.LANCHOR131
	.word	1212240712
	.size	ftl_debug_info_fill, .-ftl_debug_info_fill
	.section	.text.timer_get_time,"ax",%progbits
	.align	1
	.global	timer_get_time
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	timer_get_time, %function
timer_get_time:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	movs	r0, #0
	bx	lr
	.size	timer_get_time, .-timer_get_time
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
	b	zftl_flash_de_init
	.size	rk_nand_de_init, .-rk_nand_de_init
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
	b	zftl_get_density
	.size	ftl_get_density, .-ftl_get_density
	.section	.text.ftl_get_capacity,"ax",%progbits
	.align	1
	.global	ftl_get_capacity
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	ftl_get_capacity, %function
ftl_get_capacity:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	ldr	r3, .L1756
	ldr	r0, [r3]
	bx	lr
.L1757:
	.align	2
.L1756:
	.word	.LANCHOR67
	.size	ftl_get_capacity, .-ftl_get_capacity
	.section	.text.rknand_print_hex,"ax",%progbits
	.align	1
	.global	rknand_print_hex
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	rknand_print_hex, %function
rknand_print_hex:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r0, r1, r4, r5, r6, r7, r8, r10, fp, lr}
	movs	r6, #0
	ldr	r10, .L1767+12
	mov	r7, r1
	mov	r8, r2
	mov	fp, r3
	mov	r5, r6
	mov	r4, r6
	str	r0, [sp, #4]
.L1759:
	cmp	r4, fp
	bne	.L1765
	ldr	r1, .L1767
	ldr	r0, .L1767+4
	add	sp, sp, #8
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r10, fp, lr}
	b	printf
.L1765:
	cbnz	r5, .L1760
	mov	r3, r6
	mov	r2, r7
	ldr	r1, [sp, #4]
	ldr	r0, .L1767+8
	bl	printf
.L1760:
	cmp	r8, #4
	bne	.L1761
	ldr	r1, [r7, r4, lsl #2]
.L1766:
	mov	r0, r10
	adds	r5, r5, #1
	bl	printf
	cmp	r5, #15
	bls	.L1764
	movs	r5, #0
	ldr	r1, .L1767
	ldr	r0, .L1767+4
	bl	printf
.L1764:
	adds	r4, r4, #1
	add	r6, r6, r8
	b	.L1759
.L1761:
	cmp	r8, #2
	ite	eq
	ldrsheq	r1, [r7, r4, lsl #1]
	ldrbne	r1, [r7, r4]	@ zero_extendqisi2
	b	.L1766
.L1768:
	.align	2
.L1767:
	.word	.LC100
	.word	.LC101
	.word	.LC98
	.word	.LC99
	.size	rknand_print_hex, .-rknand_print_hex
	.section	.text.hynix_get_read_retry_default,"ax",%progbits
	.align	1
	.global	hynix_get_read_retry_default
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	hynix_get_read_retry_default, %function
hynix_get_read_retry_default:
	@ args = 0, pretend = 0, frame = 56
	@ frame_needed = 0, uses_anonymous_args = 0
	ldr	r3, .L1880
	cmp	r0, #2
	push	{r4, r5, r6, r7, r8, r10, fp, lr}
	sub	sp, sp, #56
	mov	r1, #173
	mov	r2, #174
	mov	r4, r0
	ldr	fp, [r3]
	add	r3, fp, #128
	strb	r0, [fp, #112]
	str	r3, [sp]
	mov	r3, #172
	strb	r3, [fp, #128]
	mov	r3, #175
	strb	r1, [fp, #129]
	strb	r2, [fp, #130]
	strb	r3, [fp, #131]
	bne	.L1770
	movs	r3, #167
	mov	r8, #7
	strb	r3, [fp, #128]
	movs	r2, #247
	ldr	r3, .L1880+4
	strb	r2, [r3, #17]
.L1874:
	mov	r10, #4
	b	.L1771
.L1770:
	cmp	r0, #3
	bne	.L1772
	add	r2, fp, #127
	movs	r3, #176
.L1773:
	strb	r3, [r2, #1]!
	adds	r3, r3, #1
	uxtb	r3, r3
	cmp	r3, #184
	bne	.L1773
.L1875:
	mov	r8, #8
	mov	r10, r8
.L1771:
	subs	r3, r4, #1
	cmp	r3, #1
	bhi	.L1779
	movs	r6, #0
.L1780:
	ldr	r3, .L1880+8
	uxtb	r2, r6
	ldrb	r1, [r3]	@ zero_extendqisi2
	cmp	r1, r2
	bhi	.L1785
.L1786:
	strb	r10, [fp, #113]
	strb	r8, [fp, #114]
	add	sp, sp, #56
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r10, fp, pc}
.L1772:
	cmp	r0, #4
	bne	.L1774
	movs	r0, #204
	strb	r1, [fp, #133]
	strb	r0, [fp, #128]
	movs	r0, #191
	strb	r0, [fp, #129]
	movs	r0, #170
	strb	r0, [fp, #130]
	movs	r0, #171
	strb	r0, [fp, #131]
	movs	r0, #205
	strb	r0, [fp, #132]
	strb	r2, [fp, #134]
	strb	r3, [fp, #135]
	b	.L1875
.L1774:
	cmp	r0, #5
	bne	.L1775
	movs	r3, #56
	mov	r8, #8
	strb	r3, [fp, #128]
	movs	r3, #57
	strb	r3, [fp, #129]
	movs	r3, #58
	strb	r3, [fp, #130]
	movs	r3, #59
	strb	r3, [fp, #131]
	b	.L1874
.L1775:
	cmp	r0, #6
	bne	.L1776
	movs	r3, #14
	mov	r8, #12
	strb	r3, [fp, #128]
	movs	r3, #15
	strb	r3, [fp, #129]
	movs	r3, #16
	strb	r3, [fp, #130]
	movs	r3, #17
	strb	r3, [fp, #131]
	b	.L1874
.L1776:
	cmp	r0, #7
	bne	.L1777
	add	r2, fp, #127
	movs	r3, #176
.L1778:
	strb	r3, [r2, #1]!
	adds	r3, r3, #1
	uxtb	r3, r3
	cmp	r3, #184
	bne	.L1778
	movs	r3, #212
	mov	r8, #12
	strb	r3, [fp, #136]
	movs	r3, #213
	strb	r3, [fp, #137]
	mov	r10, #10
	b	.L1771
.L1777:
	cmp	r0, #8
	mov	r3, #7
	bne	.L1833
	strb	r3, [fp, #129]
	movs	r3, #9
	movs	r2, #6
	strb	r3, [fp, #131]
	movs	r3, #10
	strb	r2, [fp, #128]
	strb	r0, [fp, #130]
	mov	r8, #50
	strb	r3, [fp, #132]
	mov	r10, #5
	b	.L1771
.L1833:
	mov	r8, r3
	b	.L1874
.L1785:
	ldr	r3, .L1880+12
	movs	r4, #160
	ldr	r1, .L1880+16
	add	r7, fp, #127
	ldr	r0, [sp]
	ldrb	r2, [r3, r2]	@ zero_extendqisi2
	ldr	r5, [r1]
	add	r1, r10, #-1
	uxtab	r1, r0, r1
	mla	r4, r4, r2, fp
	str	r1, [sp, #4]
	add	r5, r5, r2, lsl #8
	movs	r1, #55
	adds	r4, r4, #144
	addw	r2, r5, #2056
	subs	r3, r4, #1
.L1781:
	str	r1, [r2]
	ldrb	r0, [r7, #1]!	@ zero_extendqisi2
	str	r3, [sp, #16]
	str	r1, [sp, #12]
	str	r0, [r5, #2052]
	movs	r0, #1
	str	r2, [sp, #8]
	bl	udelay
	ldr	r2, [sp, #4]
	ldr	r0, [r5, #2048]
	ldr	r3, [sp, #16]
	cmp	r2, r7
	ldr	r1, [sp, #12]
	ldr	r2, [sp, #8]
	strb	r0, [r3, #1]!
	bne	.L1781
	ldr	r3, .L1880+4
	mov	r0, r4
	movs	r1, #0
.L1782:
	movs	r2, #1
	adds	r7, r3, r1
.L1783:
	ldrb	r5, [r7, r2, lsl #2]	@ zero_extendqisi2
	ldrb	lr, [r0]	@ zero_extendqisi2
	add	r5, r5, lr
	strb	r5, [r0, r2, lsl #3]
	adds	r2, r2, #1
	cmp	r2, #7
	bne	.L1783
	adds	r1, r1, #1
	adds	r0, r0, #1
	cmp	r1, #4
	bne	.L1782
	movs	r2, #0
	adds	r6, r6, #1
	strb	r2, [r4, #16]
	strb	r2, [r4, #24]
	strb	r2, [r4, #32]
	strb	r2, [r4, #40]
	strb	r2, [r4, #48]
	strb	r2, [r4, #41]
	strb	r2, [r4, #49]
	b	.L1780
.L1779:
	subs	r3, r4, #3
	cmp	r3, #5
	bhi	.L1786
	smulbb	r3, r8, r10
	asrs	r2, r3, #1
	lsls	r3, r3, #4
	str	r3, [sp, #48]
	lsls	r3, r2, #2
	str	r2, [sp, #8]
	str	r3, [sp, #44]
	lsls	r3, r2, #1
	str	r3, [sp, #24]
	movs	r3, #0
.L1879:
	str	r3, [sp, #20]
	ldr	r3, .L1880+8
	ldrb	r2, [r3]	@ zero_extendqisi2
	ldrb	r3, [sp, #20]	@ zero_extendqisi2
	cmp	r2, r3
	bls	.L1786
	ldr	r2, .L1880+12
	movs	r6, #255
	ldrb	r3, [r2, r3]	@ zero_extendqisi2
	mov	r0, r3
	str	r3, [sp]
	bl	zftl_flash_exit_slc_mode
	ldr	r3, [sp]
	movs	r1, #160
	ldr	r2, [sp]
	mla	r1, r1, r3, fp
	add	r3, r1, #144
	str	r3, [sp, #40]
	ldr	r3, .L1880+16
	ldr	r3, [r3]
	str	r3, [sp, #4]
	add	r5, r3, r2, lsl #8
	str	r6, [r5, #2056]
	bl	nandc_wait_flash_ready
	cmp	r4, #8
	bne	.L1788
	add	r3, fp, #144
	movs	r2, #23
	str	r3, [sp, #40]
	movs	r3, #120
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
.L1789:
	ldm	sp, {r2, r3}
	add	r3, r3, r2, lsl #8
	movs	r2, #48
	str	r2, [r3, #2056]
	bl	nandc_wait_flash_ready
	subs	r3, r4, #5
	cmp	r3, #1
	str	r3, [sp, #28]
	bls	.L1835
	cmp	r4, #8
	beq	.L1835
	cmp	r4, #7
	ite	ne
	movne	r2, #2
	moveq	r2, #32
.L1795:
	ldr	r3, .L1880+20
	subs	r2, r2, #1
	ldr	r5, [sp, #4]
	ldr	r6, [sp]
	ldr	r3, [r3]
	add	r7, r5, r6, lsl #8
	subs	r1, r3, #1
	uxtab	r2, r3, r2
	mov	r0, r1
.L1796:
	ldr	r5, [r7, #2048]
	strb	r5, [r0, #1]!
	cmp	r2, r0
	bne	.L1796
	cmp	r4, #8
	bne	.L1797
	movs	r2, #0
.L1799:
	ldrb	r0, [r3, r2, lsl #2]	@ zero_extendqisi2
	uxtb	r1, r2
	cmp	r0, #50
	beq	.L1798
	add	r0, r3, r2, lsl #2
	ldrb	r0, [r0, #1]	@ zero_extendqisi2
	cmp	r0, #5
	beq	.L1798
	adds	r2, r2, #1
	cmp	r2, #8
	bne	.L1799
.L1800:
	movs	r1, #0
	ldr	r0, .L1880+24
	bl	printf
.L1802:
	b	.L1802
.L1788:
	cmp	r4, #4
	mov	r3, #54
	str	r3, [r5, #2056]
	bne	.L1790
	movs	r3, #64
	str	r6, [r5, #2052]
	str	r3, [r5, #2048]
	movs	r3, #204
.L1876:
	str	r3, [r5, #2052]
	movs	r3, #77
	b	.L1877
.L1881:
	.align	2
.L1880:
	.word	.LANCHOR6
	.word	.LANCHOR162
	.word	.LANCHOR23
	.word	.LANCHOR29
	.word	.LANCHOR7
	.word	.LANCHOR163
	.word	.LC102
.L1790:
	subs	r3, r4, #5
	cmp	r3, #1
	bhi	.L1792
	ldrb	r3, [fp, #128]	@ zero_extendqisi2
	str	r3, [r5, #2052]
	movs	r3, #82
.L1877:
	str	r3, [r5, #2048]
.L1791:
	ldm	sp, {r2, r3}
	cmp	r4, #6
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
	b	.L1789
.L1792:
	cmp	r4, #7
	bne	.L1791
	movs	r3, #174
	str	r3, [r5, #2052]
	movs	r3, #0
	str	r3, [r5, #2048]
	movs	r3, #176
	b	.L1876
.L1835:
	movs	r2, #16
	b	.L1795
.L1798:
	cmp	r1, #6
	bhi	.L1800
.L1801:
	ldr	r3, .L1882
	ldr	ip, [r3]
	mov	r3, ip
.L1811:
	ldr	r1, [sp, #48]
	sub	r2, r3, ip
	cmp	r1, r2
	bgt	.L1812
	ldr	r3, .L1882
	ldr	r1, [r3]
	ldr	r3, [sp, #24]
	adds	r2, r1, r3
	movs	r3, #8
.L1814:
	mov	r5, r2
	movs	r0, #0
.L1813:
	ldrh	r6, [r5]
	adds	r0, r0, #1
	mvns	r6, r6
	strh	r6, [r5], #2	@ movhi
	ldr	r6, [sp, #8]
	cmp	r6, r0
	bgt	.L1813
	ldr	r0, [sp, #44]
	subs	r3, r3, #1
	add	r2, r2, r0
	bne	.L1814
	mov	r6, r1
	str	r3, [sp, #16]
.L1815:
	movs	r0, #0
	mov	r2, r0
.L1819:
	movs	r3, #1
	mov	lr, r6
	lsl	r5, r3, r2
	movs	r3, #0
	str	r3, [sp, #12]
	str	r5, [sp, #32]
	movs	r5, #16
	str	r5, [sp, #36]
.L1817:
	ldrh	r3, [lr]
	str	r3, [sp, #52]
	ldr	r3, [sp, #32]
	mov	r5, r3
	ldr	r3, [sp, #52]
	bics	r3, r5, r3
	ittt	eq
	ldreq	r3, [sp, #12]
	addeq	r3, r3, #1
	streq	r3, [sp, #12]
	ldr	r3, [sp, #24]
	add	lr, lr, r3
	ldr	r3, [sp, #36]
	subs	r3, r3, #1
	str	r3, [sp, #36]
	bne	.L1817
	ldr	r3, [sp, #12]
	adds	r2, r2, #1
	cmp	r3, #8
	ittt	hi
	ldrhi	r3, [sp, #32]
	orrhi	r0, r0, r3
	uxthhi	r0, r0
	cmp	r2, #16
	bne	.L1819
	ldr	r3, [sp, #16]
	strh	r0, [r6], #2	@ movhi
	adds	r3, r3, #1
	str	r3, [sp, #16]
	ldr	r2, [sp, #16]
	ldr	r3, [sp, #8]
	cmp	r3, r2
	bgt	.L1815
	subs	r2, r1, #4
	add	r0, r1, #28
	movs	r3, #0
.L1822:
	ldr	r5, [r2, #4]!
	cbnz	r5, .L1821
	adds	r3, r3, #1
.L1821:
	cmp	r0, r2
	bne	.L1822
	cmp	r3, #7
	ble	.L1823
	ldr	r0, .L1882+4
	mov	r3, #1024
	movs	r2, #1
	bl	rknand_print_hex
	movs	r1, #0
	ldr	r0, .L1882+8
	bl	printf
.L1824:
	b	.L1824
.L1797:
	cmp	r4, #7
	bne	.L1803
	movs	r2, #0
.L1805:
	ldrb	r0, [r3, r2, lsl #2]	@ zero_extendqisi2
	uxtb	r1, r2
	cmp	r0, #12
	beq	.L1804
	add	r0, r3, r2, lsl #2
	ldrb	r0, [r0, #1]	@ zero_extendqisi2
	cmp	r0, #10
	beq	.L1804
	adds	r2, r2, #1
	cmp	r2, #8
	bne	.L1805
.L1806:
	movs	r1, #0
	ldr	r0, .L1882+8
	bl	printf
.L1807:
	b	.L1807
.L1804:
	cmp	r1, #6
	bls	.L1801
	b	.L1806
.L1803:
	cmp	r4, #6
	bne	.L1801
	adds	r3, r3, #7
.L1808:
	ldrb	r2, [r1, #1]!	@ zero_extendqisi2
	cmp	r2, #12
	beq	.L1801
	ldrb	r2, [r1, #8]	@ zero_extendqisi2
	cmp	r2, #4
	beq	.L1801
	cmp	r3, r1
	bne	.L1808
	movs	r1, #0
	ldr	r0, .L1882+8
	bl	printf
.L1810:
	b	.L1810
.L1812:
	ldr	r2, [r7, #2048]
	strb	r2, [r3], #1
	b	.L1811
.L1823:
	cmp	r4, #6
	beq	.L1837
	cmp	r4, #7
	beq	.L1838
	cmp	r4, #8
	ite	ne
	movne	r0, #8
	moveq	r0, #5
.L1825:
	add	r3, r10, #-1
	ldr	r1, [sp, #40]
	uxtb	r3, r3
	movs	r5, #0
	adds	r3, r3, #1
.L1826:
	mov	lr, r1
	mov	r2, ip
.L1827:
	ldrb	r6, [r2], #1	@ zero_extendqisi2
	strb	r6, [lr], #1
	sub	r6, r2, ip
	uxtb	r6, r6
	cmp	r10, r6
	bhi	.L1827
	adds	r5, r5, #1
	add	ip, ip, r3
	cmp	r8, r5
	add	r1, r1, r0
	bgt	.L1826
	ldm	sp, {r2, r3}
	movs	r6, #255
	add	r5, r3, r2, lsl #8
	str	r6, [r5, #2056]
	bl	nandc_wait_flash_ready
	ldr	r3, [sp, #28]
	cmp	r3, #1
	bhi	.L1829
	movs	r3, #54
	movs	r2, #22
	str	r3, [r5, #2056]
	ldrb	r3, [fp, #128]	@ zero_extendqisi2
	str	r3, [r7, #2052]
	movs	r3, #0
	str	r3, [r7, #2048]
	str	r2, [r5, #2056]
	str	r3, [r5, #2056]
	str	r3, [r7, #2052]
	str	r3, [r7, #2052]
	movs	r3, #48
	str	r6, [r7, #2052]
	str	r6, [r7, #2052]
	str	r6, [r7, #2052]
.L1878:
	str	r3, [r5, #2056]
	bl	nandc_wait_flash_ready
	ldr	r3, [sp, #20]
	adds	r3, r3, #1
	b	.L1879
.L1837:
	movs	r0, #4
	b	.L1825
.L1838:
	movs	r0, #10
	b	.L1825
.L1829:
	cmp	r4, #8
	ite	eq
	moveq	r3, #190
	movne	r3, #56
	b	.L1878
.L1883:
	.align	2
.L1882:
	.word	.LANCHOR163
	.word	.LC103
	.word	.LC102
	.size	hynix_get_read_retry_default, .-hynix_get_read_retry_default
	.section	.text.flash_get_read_retry_tbl,"ax",%progbits
	.align	1
	.global	flash_get_read_retry_tbl
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	flash_get_read_retry_tbl, %function
flash_get_read_retry_tbl:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	ldr	r3, .L1886
	ldrb	r0, [r3, #19]	@ zero_extendqisi2
	subs	r3, r0, #1
	cmp	r3, #7
	bhi	.L1884
	b	hynix_get_read_retry_default
.L1884:
	bx	lr
.L1887:
	.align	2
.L1886:
	.word	.LANCHOR32
	.size	flash_get_read_retry_tbl, .-flash_get_read_retry_tbl
	.section	.text.nandc_xfer_done,"ax",%progbits
	.align	1
	.global	nandc_xfer_done
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	nandc_xfer_done, %function
nandc_xfer_done:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 0, uses_anonymous_args = 0
	ldr	r3, .L1923
	push	{r0, r1, r4, r5, r6, r7, r8, lr}
	movs	r1, #0
	ldr	r4, .L1923+4
	ldrb	r3, [r3]	@ zero_extendqisi2
	ldr	r5, .L1923+8
	strb	r1, [r4]
	cmp	r3, #9
	ldr	r6, [r5]
	bne	.L1889
	ldr	r3, [r6, #16]
	str	r3, [sp]
	ldr	r3, [r6, #48]
	ubfx	r3, r3, #1, #1
	cmp	r3, #0
	bne	.L1894
	ldr	r7, .L1923+12
	mov	r4, r3
	ldr	r8, .L1923+32
.L1891:
	ldr	r3, [sp]
	lsls	r0, r3, #11
	bmi	.L1893
	ldr	r3, [r5]
	adds	r4, r4, #1
	ldr	r3, [r3, #16]
	str	r3, [sp]
	bics	r3, r4, #-16777216
	bne	.L1891
	ldr	r2, [sp]
	mov	r1, r4
	ldr	r3, [r6, #64]
	mov	r0, r7
	ubfx	r3, r3, #16, #6
	bl	printf
	movs	r3, #64
	movs	r2, #4
	ldr	r1, [r5]
	mov	r0, r8
	bl	rknand_print_hex
	b	.L1891
.L1892:
	ldr	r3, [sp]
	adds	r1, r1, #1
	ubfx	r3, r3, #22, #6
	cmp	r1, r3, lsl #12
	bne	.L1894
	ldr	r2, [r6, #64]
	ldr	r3, [sp]
	ldr	r0, .L1923+16
	ubfx	r2, r2, #16, #5
	ubfx	r3, r3, #22, #6
	bl	printf
	ldr	r3, [sp, #4]
	movs	r3, #1
	strb	r3, [r4]
.L1893:
	ldr	r3, .L1923+20
	movs	r2, #0
	str	r2, [r3, #20]
	add	sp, sp, #8
	@ sp needed
	pop	{r4, r5, r6, r7, r8, pc}
.L1894:
	ldr	r2, [r6, #64]
	ldr	r3, [sp]
	ubfx	r2, r2, #16, #6
	ubfx	r3, r3, #22, #6
	cmp	r2, r3
	bge	.L1893
	ldr	r3, [r6]
	str	r3, [sp, #4]
	ldr	r3, [sp, #4]
	lsls	r7, r3, #18
	bpl	.L1892
	ldr	r3, [sp, #4]
	lsls	r5, r3, #14
	bpl	.L1892
	ldr	r1, [sp, #4]
	ldr	r0, .L1923+24
	ubfx	r1, r1, #17, #1
.L1922:
	bl	printf
	b	.L1893
.L1889:
	ldr	r3, [r6, #8]
	str	r3, [sp]
	ldr	r4, [r6, #16]
	ubfx	r4, r4, #1, #1
	cbnz	r4, .L1899
	ldr	r7, .L1923+12
	ldr	r8, .L1923+32
.L1900:
	ldr	r3, [sp]
	lsls	r3, r3, #11
	bmi	.L1893
	ldr	r3, [r5]
	adds	r4, r4, #1
	ldr	r3, [r3, #8]
	str	r3, [sp]
	bics	r3, r4, #-16777216
	bne	.L1900
	ldr	r2, [sp]
	mov	r1, r4
	ldr	r3, [r6, #28]
	mov	r0, r7
	ubfx	r3, r3, #16, #5
	bl	printf
	movs	r3, #64
	movs	r2, #4
	ldr	r1, [r5]
	mov	r0, r8
	bl	rknand_print_hex
	b	.L1900
.L1899:
	ldr	r7, .L1923+16
	mov	r4, r1
	ldr	r8, .L1923+32
.L1901:
	ldr	r2, [r6, #28]
	ldr	r3, [sp]
	ubfx	r2, r2, #16, #5
	ubfx	r3, r3, #22, #6
	cmp	r2, r3
	bge	.L1893
	ldr	r3, [r5]
	ldr	r3, [r3]
	str	r3, [sp, #4]
	ldr	r3, [sp, #4]
	lsls	r1, r3, #18
	bpl	.L1902
	ldr	r3, [sp, #4]
	lsls	r2, r3, #14
	bpl	.L1902
	ldr	r1, [sp, #4]
	ldr	r0, .L1923+28
	b	.L1922
.L1902:
	adds	r4, r4, #1
	bics	r3, r4, #-16777216
	bne	.L1901
	ldr	r2, [r6, #28]
	mov	r1, r4
	ldr	r3, [sp]
	mov	r0, r7
	ubfx	r2, r2, #16, #5
	ubfx	r3, r3, #22, #6
	bl	printf
	movs	r3, #64
	movs	r2, #4
	ldr	r1, [r5]
	mov	r0, r8
	bl	rknand_print_hex
	b	.L1901
.L1924:
	.align	2
.L1923:
	.word	.LANCHOR27
	.word	.LANCHOR164
	.word	.LANCHOR7
	.word	.LC106
	.word	.LC105
	.word	.LANCHOR52
	.word	.LC104
	.word	.LC108
	.word	.LC107
	.size	nandc_xfer_done, .-nandc_xfer_done
	.section	.text.nandc_xfer,"ax",%progbits
	.align	1
	.global	nandc_xfer
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	nandc_xfer, %function
nandc_xfer:
	@ args = 4, pretend = 0, frame = 8
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r0, r1, r4, r5, r6, r7, r8, lr}
	mov	r4, r1
	ldr	r5, [sp, #32]
	mov	r7, r2
	mov	r6, r3
	mov	r0, r4
	mov	r2, r6
	mov	r1, r7
	mov	r3, r5
	bl	nandc_xfer_start
	mov	r0, r4
	bl	nandc_xfer_done
	cmp	r4, #0
	bne	.L1944
	ldr	r3, .L1963
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, #9
	bne	.L1927
	ldr	r3, .L1963+4
	lsrs	r7, r7, #2
	movs	r2, #1
	mov	r0, r4
	ldr	r1, [r3]
	mov	r8, r3
.L1928:
	cmp	r4, r7
	bcc	.L1932
	ldr	r4, [r1]
	cmp	r2, #0
	it	ne
	movne	r0, #512
	and	r3, r4, #139264
	cmp	r3, #139264
	bne	.L1934
	mov	r1, r4
	ldr	r0, .L1963+8
	bl	printf
	ldr	r3, [r8]
	mov	r0, #-1
	orr	r4, r4, #131072
	str	r4, [r3]
.L1934:
	lsls	r2, r4, #18
	bpl	.L1935
	ldr	r3, .L1963+12
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L1935
	mov	r1, r4
	ldr	r0, .L1963+16
	bl	printf
	ldr	r3, [r8]
	movs	r2, #1
	str	r2, [r3, #16]
.L1962:
	mov	r0, #-1
.L1926:
	add	sp, sp, #8
	@ sp needed
	pop	{r4, r5, r6, r7, r8, pc}
.L1932:
	add	r3, r4, #84
	ldr	r3, [r1, r3, lsl #2]
	str	r3, [sp, #4]
	ldr	ip, [sp, #4]
	ldr	r3, [sp, #4]
	ubfx	r3, r3, #26, #1
	and	r3, r3, ip, lsr #10
	ands	r2, r2, r3
	ldr	r3, [sp, #4]
	lsls	r3, r3, #29
	bmi	.L1946
	ldr	r3, [sp, #4]
	lsls	r3, r3, #13
	bmi	.L1946
	ldr	r3, [sp, #4]
	ubfx	ip, r3, #3, #7
	ldr	r3, [sp, #4]
	ubfx	r3, r3, #19, #7
	cmp	ip, r3
	ldr	r3, [sp, #4]
	ite	gt
	ubfxgt	r3, r3, #3, #7
	ubfxle	r3, r3, #19, #7
	cmp	r0, r3
	it	cc
	movcc	r0, r3
.L1929:
	adds	r4, r4, #1
	b	.L1928
.L1946:
	mov	r0, #-1
	b	.L1929
.L1927:
	ldr	r3, .L1963+20
	lsrs	r0, r7, #1
	ldr	r8, .L1963+28
	mov	r1, r4
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, #25
	mov	r3, r5
	ite	cc
	movcc	lr, #64
	movcs	lr, #128
.L1937:
	cmp	r1, r0
	add	ip, lr, r4
	add	r3, r3, #4
	bcc	.L1938
	lsrs	r4, r7, #2
	ldr	r7, .L1963+4
	movs	r2, #0
	mov	r0, r2
	ldr	r1, [r7]
.L1939:
	cmp	r2, r4
	bcc	.L1943
	movs	r3, #0
	str	r3, [r1, #16]
	ldr	r4, [r1]
	and	r3, r4, #139264
	cmp	r3, #139264
	bne	.L1935
	mov	r1, r4
	ldr	r0, .L1963+24
	bl	printf
	ldr	r3, [r7]
	orr	r4, r4, #131072
	str	r4, [r3]
	b	.L1962
.L1938:
	ldr	r2, [r8]
	bic	r4, r4, #3
	adds	r1, r1, #1
	ldr	r2, [r2, r4]
	strb	r2, [r3, #-4]
	lsrs	r4, r2, #8
	strb	r4, [r3, #-3]
	lsrs	r4, r2, #16
	lsrs	r2, r2, #24
	strb	r4, [r3, #-2]
	mov	r4, ip
	strb	r2, [r3, #-1]
	b	.L1937
.L1943:
	add	r3, r2, #8
	ldr	r3, [r1, r3, lsl #2]
	str	r3, [sp, #4]
	ldr	r3, [sp, #4]
	lsls	r3, r3, #29
	bmi	.L1949
	ldr	r3, [sp, #4]
	lsls	r3, r3, #16
	bmi	.L1949
	ldr	r3, [sp, #4]
	ubfx	ip, r3, #3, #5
	ldr	r3, [sp, #4]
	ubfx	r8, r3, #27, #1
	ldr	r3, [sp, #4]
	ldr	lr, [sp, #4]
	orr	ip, ip, r8, lsl #5
	ubfx	r3, r3, #16, #5
	ubfx	lr, lr, #29, #1
	orr	r3, r3, lr, lsl #5
	cmp	ip, r3
	ldr	r3, [sp, #4]
	itete	hi
	ldrhi	ip, [sp, #4]
	ldrls	ip, [sp, #4]
	ubfxhi	r3, r3, #3, #5
	ubfxls	r3, r3, #16, #5
	ite	hi
	ubfxhi	ip, ip, #27, #1
	ubfxls	ip, ip, #29, #1
	orr	r3, r3, ip, lsl #5
	cmp	r0, r3
	it	cc
	movcc	r0, r3
.L1940:
	adds	r2, r2, #1
	b	.L1939
.L1949:
	mov	r0, #-1
	b	.L1940
.L1935:
	adds	r3, r0, #1
	beq	.L1926
	ldr	r3, [r5]
	adds	r3, r3, #1
	bne	.L1926
	ldr	r3, [r5, #4]
	adds	r3, r3, #1
	bne	.L1926
	ldr	r3, [r6]
	adds	r3, r3, #1
	it	eq
	moveq	r0, #512
	b	.L1926
.L1944:
	movs	r0, #0
	b	.L1926
.L1964:
	.align	2
.L1963:
	.word	.LANCHOR27
	.word	.LANCHOR7
	.word	.LC109
	.word	.LANCHOR164
	.word	.LC110
	.word	.LANCHOR49
	.word	.LC111
	.word	.LANCHOR52
	.size	nandc_xfer, .-nandc_xfer
	.section	.text.flash_read_page,"ax",%progbits
	.align	1
	.global	flash_read_page
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	flash_read_page, %function
flash_read_page:
	@ args = 4, pretend = 0, frame = 8
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r0, r1, r2, r3, r4, r5, r6, r7, r8, r10, fp, lr}
	mov	r7, r3
	ldr	r3, .L1980
	mov	r5, r0
	ubfx	r10, r1, #24, #2
	lsl	fp, r5, #8
	str	r2, [sp, #12]
	ldr	r8, [r3]
	ldr	r3, .L1980+4
	ldr	r6, .L1980+8
	ldrb	r4, [r3]	@ zero_extendqisi2
	rsb	r3, r4, #24
	movs	r4, #1
	lsls	r4, r4, r3
	subs	r4, r4, #1
	ands	r4, r4, r1
	bl	nandc_wait_flash_ready
	mov	r0, r5
	bl	nandc_cs
	cmp	r10, #0
	bne	.L1966
	mov	r0, r5
	bl	zftl_flash_enter_slc_mode
.L1967:
	ldr	r3, [r6]
	ldrb	r2, [r3, #7]	@ zero_extendqisi2
	cmp	r2, #1
	bne	.L1969
	ldrb	r2, [r3, #12]	@ zero_extendqisi2
	cmp	r2, #2
	ittt	eq
	addeq	r2, r8, fp
	moveq	r1, #38
	streq	r1, [r2, #2056]
.L1969:
	add	r6, r8, fp
	movs	r1, #0
	str	r1, [r6, #2056]
	str	r1, [r6, #2052]
	str	r1, [r6, #2052]
	uxtb	r1, r4
	str	r1, [r6, #2052]
	lsrs	r1, r4, #8
	str	r1, [r6, #2052]
	lsrs	r1, r4, #16
	str	r1, [r6, #2052]
	ldr	r1, .L1980+12
	ldrb	r1, [r1]	@ zero_extendqisi2
	cbz	r1, .L1970
	lsrs	r1, r4, #24
	str	r1, [r6, #2052]
.L1970:
	add	r1, r8, fp
	movs	r0, #48
	str	r0, [r1, #2056]
	ldrb	r3, [r3, #12]	@ zero_extendqisi2
	cmp	r3, #3
	bne	.L1971
	cmp	r10, #0
	beq	.L1971
	ldr	r3, .L1980+16
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L1971
	ldr	r3, .L1980+20
	ldrb	r3, [r3]	@ zero_extendqisi2
	cbnz	r3, .L1971
	add	r4, r4, r4, lsl #1
	subs	r0, r4, #1
	add	r0, r0, r10
.L1979:
	bl	nandc_set_seed
	bl	nandc_wait_flash_ready
	add	r3, r8, fp
	movs	r1, #5
	str	r1, [r3, #2056]
	movs	r2, #224
	movs	r1, #0
	mov	r0, r5
	str	r1, [r6, #2052]
	str	r1, [r6, #2052]
	str	r2, [r3, #2056]
	ldr	r3, [sp, #12]
	ldrb	r2, [sp, #48]	@ zero_extendqisi2
	str	r7, [sp]
	bl	nandc_xfer
	bl	nandc_de_cs.constprop.32
	add	sp, sp, #16
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r10, fp, pc}
.L1966:
	ldr	r2, [r6]
	ldrb	r2, [r2, #12]	@ zero_extendqisi2
	cmp	r2, #3
	bne	.L1968
	ldr	r2, .L1980+16
	ldrb	r2, [r2]	@ zero_extendqisi2
	cbnz	r2, .L1968
	ldr	r2, .L1980+20
	ldrb	r2, [r2]	@ zero_extendqisi2
	cbnz	r2, .L1968
	add	r2, r8, fp
	str	r10, [r2, #2056]
	b	.L1967
.L1968:
	mov	r0, r5
	bl	zftl_flash_exit_slc_mode
	b	.L1967
.L1971:
	mov	r0, r4
	b	.L1979
.L1981:
	.align	2
.L1980:
	.word	.LANCHOR7
	.word	.LANCHOR31
	.word	.LANCHOR21
	.word	.LANCHOR30
	.word	.LANCHOR35
	.word	.LANCHOR36
	.size	flash_read_page, .-flash_read_page
	.section	.text.micron_read_retrial,"ax",%progbits
	.align	1
	.global	micron_read_retrial
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	micron_read_retrial, %function
micron_read_retrial:
	@ args = 4, pretend = 0, frame = 16
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, r8, r10, fp, lr}
	sub	sp, sp, #24
	str	r3, [sp, #20]
	mov	r6, r0
	mov	fp, r1
	mov	r10, #0
	ldr	r3, .L2006
	str	r2, [sp, #16]
	ldrb	r3, [r3]	@ zero_extendqisi2
	add	r3, r3, r3, lsl #1
	asrs	r3, r3, #2
	str	r3, [sp, #8]
	bl	nandc_wait_flash_ready
	ldr	r3, .L2006+4
	ldr	r5, [r3]
	add	r5, r5, r6, lsl #8
.L1983:
	mov	r0, r6
	mov	r8, #0
	mov	r4, #-1
	bl	zftl_flash_enter_slc_mode
	mov	r0, r6
	bl	zftl_flash_exit_slc_mode
.L1984:
	ldr	r3, .L2006+8
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r8, r3
	bcc	.L1989
.L1988:
	movs	r3, #239
	movs	r0, #1
	str	r3, [r5, #2056]
	movs	r3, #137
	str	r3, [r5, #2052]
	movs	r7, #0
	bl	udelay
	ldr	r3, [sp, #8]
	str	r7, [r5, #2048]
	str	r7, [r5, #2048]
	cmp	r4, r3
	str	r7, [r5, #2048]
	str	r7, [r5, #2048]
	bcc	.L1990
	adds	r1, r4, #1
	mov	r3, r8
	it	ne
	movne	r4, #256
	mov	r2, fp
	str	r4, [sp]
	mov	r1, r6
	ldr	r0, .L2006+12
	bl	printf
	cmp	r10, #0
	bne	.L1992
	adds	r2, r4, #1
	bne	.L1993
	movs	r1, #3
	mov	r0, r6
	bl	mt_auto_read_calibration_config
	mov	r10, #1
	b	.L1983
.L1989:
	movs	r3, #239
	movs	r0, #1
	str	r3, [r5, #2056]
	movs	r3, #137
	str	r3, [r5, #2052]
	bl	udelay
	add	r3, r8, #1
	ldr	r2, [sp, #16]
	str	r3, [r5, #2048]
	mov	r1, fp
	str	r3, [sp, #12]
	movs	r3, #0
	str	r3, [r5, #2048]
	mov	r0, r6
	str	r3, [r5, #2048]
	str	r3, [r5, #2048]
	ldr	r3, [sp, #56]
	str	r3, [sp]
	ldr	r3, [sp, #20]
	bl	flash_read_page
	ldr	r3, .L2006+16
	mov	r7, r0
	ldr	r3, [r3]
	lsls	r3, r3, #19
	bpl	.L1985
	str	r0, [sp]
	mov	r3, r4
	mov	r2, fp
	mov	r1, r8
	ldr	r0, .L2006+20
	bl	printf
.L1985:
	adds	r0, r7, #1
	beq	.L1986
	ldr	r3, .L2006+24
	cmp	r4, #-1
	it	eq
	moveq	r4, r7
	ldr	r3, [r3]
	str	r3, [sp, #16]
	ldr	r3, .L2006+28
	ldr	r3, [r3]
	str	r3, [sp, #20]
	ldr	r3, [sp, #8]
	cmp	r7, r3
	bcc	.L1995
.L1986:
	ldr	r8, [sp, #12]
	b	.L1984
.L1995:
	mov	r4, r7
	b	.L1988
.L1992:
	mov	r1, r7
	mov	r0, r6
	bl	mt_auto_read_calibration_config
	adds	r3, r4, #1
	it	ne
	movne	r4, #256
.L1993:
	bl	nandc_wait_flash_ready
	mov	r0, r4
	add	sp, sp, #24
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r10, fp, pc}
.L1990:
	cmp	r10, #0
	beq	.L1993
	mov	r1, r7
	mov	r0, r6
	bl	mt_auto_read_calibration_config
	mov	r4, #256
	b	.L1993
.L2007:
	.align	2
.L2006:
	.word	.LANCHOR49
	.word	.LANCHOR7
	.word	.LANCHOR166
	.word	.LC113
	.word	.LANCHOR19
	.word	.LC112
	.word	.LANCHOR163
	.word	.LANCHOR165
	.size	micron_read_retrial, .-micron_read_retrial
	.section	.text.toshiba_3d_read_retrial,"ax",%progbits
	.align	1
	.global	toshiba_3d_read_retrial
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	toshiba_3d_read_retrial, %function
toshiba_3d_read_retrial:
	@ args = 4, pretend = 0, frame = 16
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, r8, r10, fp, lr}
	sub	sp, sp, #24
	mov	r7, r0
	str	r2, [sp, #8]
	mov	r8, r1
	ubfx	r4, r1, #24, #2
	str	r3, [sp, #12]
	add	r6, r7, #8
	bl	nandc_wait_flash_ready
	ldr	r3, .L2051
	ldr	fp, [r3]
	ldr	r3, .L2051+4
	ldrb	r2, [r3]	@ zero_extendqisi2
	add	r6, fp, r6, lsl #8
	cmp	r2, #36
	ite	ne
	movne	r2, #56
	moveq	r2, #46
	str	r2, [sp, #20]
	ite	ne
	movne	r2, #10
	moveq	r2, #26
	str	r2, [sp, #16]
	cmp	r4, #0
	bne	.L2010
	mov	r4, #-1
	movs	r5, #1
	str	r3, [sp, #20]
.L2017:
	ldr	r3, [sp, #20]
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, #36
	bne	.L2011
	movs	r2, #0
	mov	r1, r5
	mov	r0, r6
	bl	toshiba_tlc_set_rr_para
	add	r3, fp, r7, lsl #8
	movs	r2, #93
	str	r2, [r3, #2056]
.L2012:
	ldr	r3, [sp, #56]
	mov	r1, r8
	ldr	r2, [sp, #8]
	mov	r0, r7
	str	r3, [sp]
	ldr	r3, [sp, #12]
	bl	flash_read_page
	ldr	r3, .L2051+8
	mov	r10, r0
	ldr	r3, [r3]
	lsls	r1, r3, #27
	bpl	.L2013
	mov	r3, r0
	mov	r2, r8
	mov	r1, r5
	ldr	r0, .L2051+12
	bl	printf
.L2013:
	cmp	r10, #-1
	beq	.L2014
	ldr	r3, .L2051+16
	cmp	r4, #-1
	it	eq
	moveq	r4, r10
	ldr	r3, [r3]
	str	r3, [sp, #8]
	ldr	r3, .L2051+20
	ldr	r3, [r3]
	str	r3, [sp, #12]
	ldr	r3, .L2051+24
	ldrb	r3, [r3]	@ zero_extendqisi2
	add	r3, r3, r3, lsl #1
	cmp	r10, r3, asr #2
	bcc	.L2032
.L2014:
	ldr	r3, [sp, #16]
	adds	r5, r5, #1
	cmp	r3, r5
	bne	.L2017
.L2016:
	ldr	r3, .L2051+4
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, #36
	bne	.L2018
	movs	r2, #0
.L2050:
	movs	r1, #0
	mov	r0, r6
	bl	toshiba_tlc_set_rr_para
	b	.L2019
.L2011:
	uxtb	r1, r5
	mov	r0, r6
	bl	toshiba_3d_set_slc_rr_para
	b	.L2012
.L2032:
	mov	r4, r10
	b	.L2016
.L2018:
	movs	r1, #0
	mov	r0, r6
	bl	toshiba_3d_set_slc_rr_para
.L2019:
	ldr	r3, .L2051+4
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, #36
	bne	.L2028
	add	r3, fp, r7, lsl #8
	movs	r2, #85
	str	r2, [r3, #2056]
	movs	r2, #0
	str	r2, [r3, #2052]
	str	r2, [r3, #2048]
	movs	r2, #255
	str	r2, [r3, #2056]
.L2028:
	ldr	r3, .L2051+24
	ldrb	r3, [r3]	@ zero_extendqisi2
	add	r3, r3, r3, lsl #1
	cmp	r4, r3, asr #2
	bcc	.L2029
	adds	r3, r4, #1
	mov	r2, r8
	it	ne
	movne	r4, #256
	mov	r3, r5
	str	r4, [sp]
	mov	r1, r7
	ldr	r0, .L2051+28
	bl	printf
.L2029:
	bl	nandc_wait_flash_ready
	mov	r0, r4
	add	sp, sp, #24
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r10, fp, pc}
.L2010:
	mov	r4, #-1
	movs	r5, #1
	str	r3, [sp, #16]
.L2026:
	ldr	r3, [sp, #16]
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, #36
	bne	.L2020
	movs	r2, #1
	mov	r1, r5
	mov	r0, r6
	bl	toshiba_tlc_set_rr_para
	add	r3, fp, r7, lsl #8
	movs	r2, #93
.L2049:
	str	r2, [r3, #2056]
	mov	r1, r8
	ldr	r3, [sp, #56]
	mov	r0, r7
	ldr	r2, [sp, #8]
	str	r3, [sp]
	ldr	r3, [sp, #12]
	bl	flash_read_page
	ldr	r3, .L2051+8
	mov	r10, r0
	ldr	r3, [r3]
	lsls	r2, r3, #27
	bpl	.L2022
	mov	r3, r0
	mov	r2, r8
	mov	r1, r5
	ldr	r0, .L2051+32
	bl	printf
.L2022:
	cmp	r10, #-1
	beq	.L2023
	ldr	r3, .L2051+16
	cmp	r4, #-1
	it	eq
	moveq	r4, r10
	ldr	r3, [r3]
	str	r3, [sp, #8]
	ldr	r3, .L2051+20
	ldr	r3, [r3]
	str	r3, [sp, #12]
	ldr	r3, .L2051+24
	ldrb	r3, [r3]	@ zero_extendqisi2
	add	r3, r3, r3, lsl #1
	cmp	r10, r3, asr #2
	bcc	.L2033
.L2023:
	ldr	r3, [sp, #20]
	adds	r5, r5, #1
	cmp	r3, r5
	bne	.L2026
.L2025:
	ldr	r3, .L2051+4
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, #36
	bne	.L2027
	movs	r2, #1
	b	.L2050
.L2020:
	uxtb	r1, r5
	mov	r0, r6
	bl	toshiba_3d_set_tlc_rr_para
	add	r3, fp, r7, lsl #8
	movs	r2, #38
	b	.L2049
.L2033:
	mov	r4, r10
	b	.L2025
.L2027:
	movs	r1, #0
	mov	r0, r6
	bl	toshiba_3d_set_tlc_rr_para
	b	.L2019
.L2052:
	.align	2
.L2051:
	.word	.LANCHOR7
	.word	.LANCHOR15
	.word	.LANCHOR19
	.word	.LC114
	.word	.LANCHOR163
	.word	.LANCHOR165
	.word	.LANCHOR49
	.word	.LC116
	.word	.LC115
	.size	toshiba_3d_read_retrial, .-toshiba_3d_read_retrial
	.section	.text.toshiba_read_retrial,"ax",%progbits
	.align	1
	.global	toshiba_read_retrial
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	toshiba_read_retrial, %function
toshiba_read_retrial:
	@ args = 4, pretend = 0, frame = 16
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, r8, r10, fp, lr}
	mov	r5, r0
	sub	sp, sp, #24
	add	r10, r5, #8
	str	r2, [sp, #12]
	str	r3, [sp, #16]
	str	r1, [sp, #8]
	bl	nandc_wait_flash_ready
	mov	r0, r5
	bl	zftl_flash_enter_slc_mode
	mov	r0, r5
	bl	zftl_flash_exit_slc_mode
	ldr	r3, .L2080
	ldr	r2, .L2080+4
	ldr	r7, [r3]
	ldrb	r3, [r2]	@ zero_extendqisi2
	str	r2, [sp, #20]
	subs	r3, r3, #67
	add	r10, r7, r10, lsl #8
	cmp	r3, #1
	bls	.L2071
	ldr	r3, .L2080+8
	ldrb	r6, [r3]	@ zero_extendqisi2
	cbz	r6, .L2055
	movs	r6, #1
	movs	r0, #1
	bl	nandc_set_if_mode
.L2055:
	add	r3, r7, r5, lsl #8
	movs	r2, #92
	str	r2, [r3, #2056]
	movs	r2, #197
	str	r2, [r3, #2056]
.L2054:
	mov	r8, #1
	mov	fp, #-1
.L2056:
	ldr	r3, .L2080+12
	ldrb	r3, [r3]	@ zero_extendqisi2
	adds	r3, r3, #1
	cmp	r8, r3
	bcc	.L2065
	mov	r4, fp
.L2064:
	ldr	r3, .L2080+4
	movs	r1, #0
	mov	r0, r10
	ldrb	r3, [r3]	@ zero_extendqisi2
	subs	r3, r3, #67
	cmp	r3, #1
	bhi	.L2066
	bl	sandisk_set_rr_para
.L2067:
	add	r5, r7, r5, lsl #8
	movs	r3, #255
	str	r3, [r5, #2056]
	ldr	r3, .L2080+16
	ldrb	r3, [r3]	@ zero_extendqisi2
	add	r3, r3, r3, lsl #1
	cmp	r4, r3, asr #2
	bcc	.L2068
	adds	r3, r4, #1
	ldr	r2, [sp, #8]
	it	ne
	movne	r4, #256
	mov	r3, r8
	str	r4, [sp]
	mov	r1, r8
	ldr	r0, .L2080+20
	bl	printf
.L2068:
	bl	nandc_wait_flash_ready
	cbz	r6, .L2053
	movs	r0, #4
	bl	nandc_set_if_mode
.L2053:
	mov	r0, r4
	add	sp, sp, #24
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r10, fp, pc}
.L2071:
	movs	r6, #0
	b	.L2054
.L2065:
	ldr	r3, [sp, #20]
	mov	r0, r10
	uxtb	r1, r8
	ldrb	r3, [r3]	@ zero_extendqisi2
	subs	r3, r3, #67
	cmp	r3, #1
	bhi	.L2057
	bl	sandisk_set_rr_para
.L2058:
	ldr	r3, .L2080+4
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, #34
	bne	.L2059
	ldr	r3, .L2080+12
	ldrb	r3, [r3]	@ zero_extendqisi2
	subs	r3, r3, #3
	cmp	r8, r3
	ittt	eq
	addeq	r3, r7, r5, lsl #8
	moveq	r2, #179
	streq	r2, [r3, #2056]
.L2059:
	add	r3, r7, r5, lsl #8
	movs	r2, #38
	add	r1, sp, #8
	str	r2, [r3, #2056]
	movs	r2, #93
	str	r2, [r3, #2056]
	mov	r0, r5
	ldr	r3, [sp, #56]
	str	r3, [sp]
	ldm	r1, {r1, r2, r3}
	bl	flash_read_page
	adds	r2, r0, #1
	mov	r4, r0
	beq	.L2062
	ldr	r3, .L2080+24
	cmp	fp, #-1
	it	eq
	moveq	fp, r0
	ldr	r3, [r3]
	str	r3, [sp, #12]
	ldr	r3, .L2080+28
	ldr	r3, [r3]
	str	r3, [sp, #16]
	ldr	r3, .L2080+16
	ldrb	r3, [r3]	@ zero_extendqisi2
	add	r3, r3, r3, lsl #1
	cmp	r0, r3, asr #2
	bcc	.L2064
.L2062:
	add	r8, r8, #1
	b	.L2056
.L2057:
	bl	toshiba_set_rr_para
	b	.L2058
.L2066:
	bl	toshiba_set_rr_para
	b	.L2067
.L2081:
	.align	2
.L2080:
	.word	.LANCHOR7
	.word	.LANCHOR15
	.word	.LANCHOR26
	.word	.LANCHOR166
	.word	.LANCHOR49
	.word	.LC116
	.word	.LANCHOR163
	.word	.LANCHOR165
	.size	toshiba_read_retrial, .-toshiba_read_retrial
	.section	.text.ymtc_3d_read_retrial,"ax",%progbits
	.align	1
	.global	ymtc_3d_read_retrial
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	ymtc_3d_read_retrial, %function
ymtc_3d_read_retrial:
	@ args = 4, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r0, r1, r4, r5, r6, r7, r8, r10, fp, lr}
	mov	r7, r0
	mov	r8, r1
	mov	r10, r2
	mov	fp, r3
	mov	r4, #-1
	bl	nandc_wait_flash_ready
	mov	r0, r7
	movs	r5, #1
	bl	zftl_flash_enter_slc_mode
	mov	r0, r7
	bl	zftl_flash_exit_slc_mode
	ldr	r2, .L2106
	tst	r8, #50331648
	add	r3, r7, #8
	ldr	r6, [r2]
	add	r6, r6, r3, lsl #8
	bne	.L2092
.L2087:
	uxtb	r1, r5
	mov	r0, r6
	bl	ymtc_3d_set_slc_rr_para
	ldr	r3, [sp, #40]
	mov	r1, r8
	mov	r2, r10
	mov	r0, r7
	str	r3, [sp]
	mov	r3, fp
	bl	flash_read_page
	adds	r1, r0, #1
	beq	.L2084
	ldr	r3, .L2106+4
	cmp	r4, #-1
	it	eq
	moveq	r4, r0
	ldr	r10, [r3]
	ldr	r3, .L2106+8
	ldr	fp, [r3]
	ldr	r3, .L2106+12
	ldrb	r3, [r3]	@ zero_extendqisi2
	add	r3, r3, r3, lsl #1
	cmp	r0, r3, asr #2
	bcc	.L2095
.L2084:
	adds	r5, r5, #1
	cmp	r5, #10
	bne	.L2087
.L2086:
	movs	r1, #0
	mov	r0, r6
	bl	ymtc_3d_set_slc_rr_para
.L2088:
	ldr	r3, .L2106+12
	ldrb	r3, [r3]	@ zero_extendqisi2
	add	r3, r3, r3, lsl #1
	cmp	r4, r3, asr #2
	bcc	.L2093
	adds	r3, r4, #1
	mov	r2, r8
	it	ne
	movne	r4, #256
	mov	r3, r5
	str	r4, [sp]
	mov	r1, r5
	ldr	r0, .L2106+16
	bl	printf
.L2093:
	bl	nandc_wait_flash_ready
	mov	r0, r4
	add	sp, sp, #8
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r10, fp, pc}
.L2095:
	mov	r4, r0
	b	.L2086
.L2092:
	uxtb	r1, r5
	mov	r0, r6
	bl	ymtc_3d_set_tlc_rr_para
	ldr	r3, [sp, #40]
	mov	r2, r10
	mov	r1, r8
	mov	r0, r7
	str	r3, [sp]
	mov	r3, fp
	bl	flash_read_page
	adds	r2, r0, #1
	beq	.L2089
	ldr	r3, .L2106+4
	cmp	r4, #-1
	it	eq
	moveq	r4, r0
	ldr	r10, [r3]
	ldr	r3, .L2106+8
	ldr	fp, [r3]
	ldr	r3, .L2106+12
	ldrb	r3, [r3]	@ zero_extendqisi2
	add	r3, r3, r3, lsl #1
	cmp	r0, r3, asr #2
	bcc	.L2096
.L2089:
	adds	r5, r5, #1
	cmp	r5, #51
	bne	.L2092
.L2091:
	movs	r1, #0
	mov	r0, r6
	bl	ymtc_3d_set_tlc_rr_para
	b	.L2088
.L2096:
	mov	r4, r0
	b	.L2091
.L2107:
	.align	2
.L2106:
	.word	.LANCHOR7
	.word	.LANCHOR163
	.word	.LANCHOR165
	.word	.LANCHOR49
	.word	.LC117
	.size	ymtc_3d_read_retrial, .-ymtc_3d_read_retrial
	.section	.text.samsung_read_retrial,"ax",%progbits
	.align	1
	.global	samsung_read_retrial
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	samsung_read_retrial, %function
samsung_read_retrial:
	@ args = 4, pretend = 0, frame = 16
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, r8, r10, fp, lr}
	mov	r7, r0
	sub	sp, sp, #24
	mov	r8, r1
	str	r3, [sp, #16]
	str	r2, [sp, #12]
	bl	nandc_wait_flash_ready
	mov	r0, r7
	bl	zftl_flash_enter_slc_mode
	mov	r0, r7
	bl	zftl_flash_exit_slc_mode
	ldr	r3, .L2141
	tst	r8, #50331648
	ldr	r3, [r3]
	str	r3, [sp, #8]
	bne	.L2109
	lsl	fp, r7, #8
	mov	r4, #-1
	movs	r5, #1
	add	r6, r3, fp
.L2114:
	movs	r3, #239
	str	r3, [r6, #2056]
	movs	r3, #141
	str	r3, [r6, #2052]
	ldr	r3, .L2141+4
	ldrsb	r3, [r5, r3]
	str	r3, [r6, #2048]
	movs	r3, #0
	str	r3, [r6, #2048]
	str	r3, [r6, #2048]
	str	r3, [r6, #2048]
	bl	nandc_wait_flash_ready
	ldr	r3, [sp, #56]
	mov	r1, r8
	ldr	r2, [sp, #12]
	mov	r0, r7
	str	r3, [sp]
	ldr	r3, [sp, #16]
	bl	flash_read_page
	ldr	r3, .L2141+8
	mov	r10, r0
	ldr	r3, [r3]
	lsls	r1, r3, #27
	bpl	.L2110
	mov	r3, r0
	mov	r2, r8
	mov	r1, r5
	ldr	r0, .L2141+12
	bl	printf
.L2110:
	cmp	r10, #-1
	beq	.L2111
	ldr	r3, .L2141+16
	cmp	r4, #-1
	it	eq
	moveq	r4, r10
	ldr	r3, [r3]
	str	r3, [sp, #12]
	ldr	r3, .L2141+20
	ldr	r3, [r3]
	str	r3, [sp, #16]
	ldr	r3, .L2141+24
	ldrb	r3, [r3]	@ zero_extendqisi2
	add	r3, r3, r3, lsl #1
	cmp	r10, r3, asr #2
	bcc	.L2123
.L2111:
	adds	r5, r5, #1
	cmp	r5, #26
	bne	.L2114
.L2113:
	ldr	r3, [sp, #8]
	add	r3, r3, fp
	mov	fp, r3
	movs	r3, #239
	str	r3, [fp, #2056]
	movs	r3, #141
.L2140:
	str	r3, [r6, #2052]
	movs	r3, #0
	str	r3, [r6, #2048]
	str	r3, [r6, #2048]
	str	r3, [r6, #2048]
	str	r3, [r6, #2048]
	bl	nandc_wait_flash_ready
	ldr	r3, .L2141+24
	ldrb	r3, [r3]	@ zero_extendqisi2
	add	r3, r3, r3, lsl #1
	cmp	r4, r3, asr #2
	bcc	.L2121
	adds	r3, r4, #1
	mov	r2, r8
	it	ne
	movne	r4, #256
	mov	r3, r5
	str	r4, [sp]
	mov	r1, r5
	ldr	r0, .L2141+28
	bl	printf
.L2121:
	bl	nandc_wait_flash_ready
	mov	r0, r4
	add	sp, sp, #24
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r10, fp, pc}
.L2123:
	mov	r4, r10
	b	.L2113
.L2109:
	ldr	r3, [sp, #8]
	mov	r4, #-1
	ldr	r10, .L2141+36
	movs	r5, #1
	add	r6, r3, r7, lsl #8
	addw	r3, r6, #2056
	str	r3, [sp, #20]
.L2120:
	ldr	r3, [sp, #20]
	mov	r2, r3
	movs	r3, #239
	str	r3, [r2]
	movs	r3, #137
	str	r3, [r6, #2052]
	ldrb	r3, [r10, #4]	@ zero_extendqisi2
	str	r3, [r6, #2048]
	ldrb	r3, [r10, #5]	@ zero_extendqisi2
	str	r3, [r6, #2048]
	ldrb	r3, [r10, #6]	@ zero_extendqisi2
	str	r3, [r6, #2048]
	ldrb	r3, [r10, #7]	@ zero_extendqisi2
	str	r3, [r6, #2048]
	bl	nandc_wait_flash_ready
	ldr	r3, [sp, #56]
	mov	r1, r8
	ldr	r2, [sp, #12]
	mov	r0, r7
	str	r3, [sp]
	ldr	r3, [sp, #16]
	bl	flash_read_page
	ldr	r3, .L2141+8
	mov	fp, r0
	ldr	r3, [r3]
	lsls	r2, r3, #27
	bpl	.L2116
	mov	r3, r0
	mov	r2, r8
	mov	r1, r5
	ldr	r0, .L2141+32
	bl	printf
.L2116:
	cmp	fp, #-1
	beq	.L2117
	ldr	r3, .L2141+16
	cmp	r4, #-1
	it	eq
	moveq	r4, fp
	ldr	r3, [r3]
	str	r3, [sp, #12]
	ldr	r3, .L2141+20
	ldr	r3, [r3]
	str	r3, [sp, #16]
	ldr	r3, .L2141+24
	ldrb	r3, [r3]	@ zero_extendqisi2
	add	r3, r3, r3, lsl #1
	cmp	fp, r3, asr #2
	bcc	.L2124
.L2117:
	adds	r5, r5, #1
	add	r10, r10, #4
	cmp	r5, #26
	bne	.L2120
.L2119:
	ldr	r3, [sp, #8]
	add	r7, r3, r7, lsl #8
	movs	r3, #239
	str	r3, [r7, #2056]
	movs	r3, #137
	b	.L2140
.L2124:
	mov	r4, fp
	b	.L2119
.L2142:
	.align	2
.L2141:
	.word	.LANCHOR7
	.word	.LANCHOR167
	.word	.LANCHOR19
	.word	.LC118
	.word	.LANCHOR163
	.word	.LANCHOR165
	.word	.LANCHOR49
	.word	.LC120
	.word	.LC119
	.word	.LANCHOR168
	.size	samsung_read_retrial, .-samsung_read_retrial
	.section	.text.hynix_read_retrial,"ax",%progbits
	.align	1
	.global	hynix_read_retrial
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	hynix_read_retrial, %function
hynix_read_retrial:
	@ args = 4, pretend = 0, frame = 8
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r0, r1, r2, r3, r4, r5, r6, r7, r8, r10, fp, lr}
	mov	r6, r0
	str	r3, [sp, #12]
	mov	r8, r1
	movs	r7, #0
	mov	r4, #-1
	ldr	r3, .L2157
	str	r2, [sp, #8]
	ldr	r3, [r3]
	add	r10, r3, r0
	ldrb	fp, [r3, #114]	@ zero_extendqisi2
	ldrb	r5, [r10, #120]	@ zero_extendqisi2
	bl	nandc_wait_flash_ready
	mov	r0, r6
	bl	zftl_flash_enter_slc_mode
	mov	r0, r6
	bl	zftl_flash_exit_slc_mode
.L2144:
	cmp	r7, fp
	bcc	.L2149
.L2148:
	ldr	r3, .L2157+4
	strb	r5, [r10, #120]
	ldrb	r3, [r3]	@ zero_extendqisi2
	add	r3, r3, r3, lsl #1
	cmp	r4, r3, asr #2
	bcc	.L2150
	adds	r3, r4, #1
	mov	r2, r8
	it	ne
	movne	r4, #256
	mov	r3, r7
	str	r4, [sp]
	mov	r1, r7
	ldr	r0, .L2157+8
	bl	printf
.L2150:
	bl	nandc_wait_flash_ready
	mov	r0, r4
	add	sp, sp, #16
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r10, fp, pc}
.L2149:
	adds	r5, r5, #1
	mov	r0, r6
	uxtb	r5, r5
	cmp	fp, r5
	it	ls
	movls	r5, #0
	mov	r1, r5
	bl	hynix_set_rr_para
	ldr	r3, [sp, #48]
	mov	r1, r8
	ldr	r2, [sp, #8]
	mov	r0, r6
	str	r3, [sp]
	ldr	r3, [sp, #12]
	bl	flash_read_page
	adds	r2, r0, #1
	beq	.L2146
	ldr	r3, .L2157+12
	cmp	r4, #-1
	it	eq
	moveq	r4, r0
	ldr	r3, [r3]
	str	r3, [sp, #8]
	ldr	r3, .L2157+16
	ldr	r3, [r3]
	str	r3, [sp, #12]
	ldr	r3, .L2157+4
	ldrb	r3, [r3]	@ zero_extendqisi2
	add	r3, r3, r3, lsl #1
	cmp	r0, r3, asr #2
	bcc	.L2152
.L2146:
	adds	r7, r7, #1
	b	.L2144
.L2152:
	mov	r4, r0
	b	.L2148
.L2158:
	.align	2
.L2157:
	.word	.LANCHOR6
	.word	.LANCHOR49
	.word	.LC121
	.word	.LANCHOR163
	.word	.LANCHOR165
	.size	hynix_read_retrial, .-hynix_read_retrial
	.section	.text.flash_ddr_tuning_read,"ax",%progbits
	.align	1
	.global	flash_ddr_tuning_read
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	flash_ddr_tuning_read, %function
flash_ddr_tuning_read:
	@ args = 4, pretend = 0, frame = 24
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, r8, r10, fp, lr}
	movs	r4, #0
	sub	sp, sp, #32
	mov	r5, r4
	mov	r6, #1024
	movs	r7, #6
	str	r3, [sp, #20]
	mov	r8, r0
	mov	fp, r1
	str	r2, [sp, #16]
	bl	nandc_get_ddr_para
	mov	r3, #-1
	str	r0, [sp, #28]
	str	r4, [sp, #24]
	str	r4, [sp, #12]
	str	r3, [sp, #8]
.L2165:
	uxtb	r0, r7
	bl	nandc_set_ddr_para
	ldr	r3, [sp, #64]
	mov	r1, fp
	ldr	r2, [sp, #16]
	mov	r0, r8
	str	r3, [sp]
	ldr	r3, [sp, #20]
	bl	flash_read_page
	ldr	r3, .L2185
	mov	r10, r0
	ldr	r3, [r3]
	lsls	r2, r3, #27
	bpl	.L2160
	mov	r3, r0
	mov	r2, fp
	mov	r1, r7
	ldr	r0, .L2185+4
	bl	printf
.L2160:
	adds	r3, r6, #1
	cmp	r10, r3
	bhi	.L2161
	ldr	r3, .L2185+8
	ldr	r3, [r3]
	str	r3, [sp, #16]
	ldr	r3, .L2185+12
	ldr	r3, [r3]
	str	r3, [sp, #20]
	ldr	r3, .L2185+16
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r10, r3, lsr #2
	bcs	.L2171
	adds	r5, r5, #1
	cmp	r5, #7
	bls	.L2171
	subs	r4, r7, r5
	mov	r6, r10
	movs	r3, #0
	str	r3, [sp, #8]
.L2163:
	ldr	r3, [sp, #24]
	ldr	r2, [sp, #12]
	cmp	r5, r2
	it	cc
	movcc	r4, r3
.L2164:
	cmp	r4, #0
	beq	.L2166
	ldr	r3, .L2185+16
	ldrb	r2, [r3]	@ zero_extendqisi2
	ldr	r3, .L2185+20
	umull	r2, r3, r2, r3
	ubfx	r3, r3, #1, #8
	cmp	r3, r6
	bls	.L2166
	mov	r1, r4
	ldr	r0, .L2185+24
	bl	printf
	uxtb	r0, r4
.L2184:
	bl	nandc_set_ddr_para
	ldr	r3, [sp, #8]
	cmp	r3, #0
	beq	.L2159
	ldr	r4, .L2185+28
	ldrb	r3, [r4]	@ zero_extendqisi2
	lsls	r3, r3, #31
	bpl	.L2159
	mov	r1, r8
	mov	r2, fp
	ldr	r0, .L2185+32
	bl	printf
	mov	r0, r8
	bl	flash_reset
	movs	r0, #1
	bl	flash_set_interface_mode
	movs	r0, #1
	bl	nandc_set_if_mode
	ldr	r3, .L2185+36
	movs	r2, #2
	mov	r0, r8
	strb	r2, [r3, r8]
	bl	zftl_flash_enter_slc_mode
	ldr	r3, [sp, #64]
	mov	r1, fp
	ldr	r2, [sp, #16]
	mov	r0, r8
	str	r3, [sp]
	ldr	r3, [sp, #20]
	bl	flash_read_page
	mov	r2, fp
	mov	r3, r0
	mov	r6, r0
	mov	r1, r8
	ldr	r0, .L2185+40
	bl	printf
	ldr	r3, .L2185+16
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r6, r3
	bhi	.L2173
	ldr	r2, .L2185+44
	ldr	r3, [r2]
	adds	r3, r3, #1
	cmp	r3, #100
	str	r3, [r2]
	bls	.L2169
	ldr	r3, .L2185+48
	movs	r2, #0
	strb	r2, [r3]
.L2159:
	mov	r0, r6
	add	sp, sp, #32
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r10, fp, pc}
.L2161:
	ldr	r3, [sp, #12]
	cmp	r5, r3
	bls	.L2172
	cmp	r5, #7
	sub	r3, r4, r5
	str	r3, [sp, #24]
	bhi	.L2164
	str	r5, [sp, #12]
.L2172:
	movs	r5, #0
	b	.L2162
.L2171:
	mov	r4, r7
	mov	r6, r10
	movs	r3, #0
	str	r3, [sp, #8]
.L2162:
	adds	r7, r7, #2
	cmp	r7, #50
	bne	.L2165
	b	.L2163
.L2166:
	ldrb	r0, [sp, #28]	@ zero_extendqisi2
	b	.L2184
.L2173:
	ldr	r6, [sp, #8]
.L2169:
	ldrb	r0, [r4]	@ zero_extendqisi2
	bl	flash_set_interface_mode
	ldrb	r0, [r4]	@ zero_extendqisi2
	bl	nandc_set_if_mode
	b	.L2159
.L2186:
	.align	2
.L2185:
	.word	.LANCHOR19
	.word	.LC122
	.word	.LANCHOR163
	.word	.LANCHOR165
	.word	.LANCHOR49
	.word	-1431655765
	.word	.LC123
	.word	.LANCHOR48
	.word	.LC124
	.word	.LANCHOR33
	.word	.LC125
	.word	.LANCHOR169
	.word	.LANCHOR26
	.size	flash_ddr_tuning_read, .-flash_ddr_tuning_read
	.section	.text.flash_read_page_en,"ax",%progbits
	.align	1
	.global	flash_read_page_en
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	flash_read_page_en, %function
flash_read_page_en:
	@ args = 4, pretend = 0, frame = 8
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r0, r1, r2, r3, r4, r5, r6, r7, r8, r10, fp, lr}
	mov	r8, r3
	ldr	r3, .L2214
	mov	r7, r2
	mov	r5, r0
	mov	r4, r1
	ldr	r10, [sp, #48]
	ldrb	r2, [r3]	@ zero_extendqisi2
	mov	fp, r3
	cmp	r2, r0
	bhi	.L2188
	movw	r2, #431
	ldr	r1, .L2214+4
	ldr	r0, .L2214+8
	bl	printf
.L2188:
	ldr	r3, .L2214+12
	ldrb	r6, [r3, r5]	@ zero_extendqisi2
	ldrb	r3, [fp]	@ zero_extendqisi2
	cmp	r5, r3
	bcc	.L2189
	ldr	r2, .L2214+16
	ldr	r2, [r2]
	lsls	r0, r2, #25
	bmi	.L2190
.L2213:
	mov	r0, #-1
.L2187:
	add	sp, sp, #16
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r10, fp, pc}
.L2190:
	str	r3, [sp]
	mov	r2, r5
	mov	r3, r4
	mov	r1, r6
	ldr	r0, .L2214+20
	bl	printf
	b	.L2213
.L2189:
	tst	r4, #50331648
	bne	.L2192
	ldr	r3, .L2214+24
	ldrb	r2, [r3]	@ zero_extendqisi2
	ldr	r3, .L2214+28
	cbz	r2, .L2193
	ldrb	r2, [r3]	@ zero_extendqisi2
	cbz	r2, .L2192
.L2193:
	ldr	r2, .L2214+32
	mov	r0, r4
	str	r3, [sp, #12]
	ldrh	r5, [r2]
	mov	r1, r5
	bl	__aeabi_uidiv
	mov	r1, r5
	mul	fp, r5, r0
	mov	r0, r4
	bl	__aeabi_uidivmod
	ldr	r3, [sp, #12]
	ldrb	r3, [r3]	@ zero_extendqisi2
	cbz	r3, .L2194
	add	r4, fp, r1, lsl #1
.L2192:
	mov	r1, r4
	str	r10, [sp]
	mov	r3, r8
	mov	r2, r7
	mov	r0, r6
	bl	flash_read_page
	adds	r1, r0, #1
	bne	.L2187
	ldr	r5, .L2214+36
	ldrb	fp, [r5]	@ zero_extendqisi2
	cmp	fp, #0
	bne	.L2195
.L2198:
	ldr	r3, .L2214+40
	ldr	fp, [r3]
	cmp	fp, #0
	bne	.L2196
.L2197:
	ldrb	r3, [r5]	@ zero_extendqisi2
	mov	r2, r4
	movs	r1, #0
	ldr	r0, .L2214+44
	str	r3, [sp]
	mov	r3, #-1
	bl	printf
	ldr	r3, .L2214+48
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L2213
	str	r10, [sp, #48]
	mov	r3, r8
	mov	r2, r7
	mov	r1, r4
	mov	r0, r6
	add	sp, sp, #16
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r10, fp, lr}
	b	flash_ddr_tuning_read
.L2194:
	ldr	r3, .L2214+52
	ldrh	r4, [r3, r1, lsl #1]
	add	r4, r4, fp
	b	.L2192
.L2195:
	movs	r3, #0
	mov	r2, r7
	strb	r3, [r5]
	mov	r1, r4
	str	r10, [sp]
	mov	r3, r8
	mov	r0, r6
	bl	flash_read_page
	adds	r2, r0, #1
	strb	fp, [r5]
	beq	.L2198
	b	.L2187
.L2196:
	mov	r3, r8
	str	r10, [sp]
	mov	r2, r7
	mov	r1, r4
	mov	r0, r6
	blx	fp
	adds	r3, r0, #1
	beq	.L2197
	b	.L2187
.L2215:
	.align	2
.L2214:
	.word	.LANCHOR23
	.word	.LANCHOR170
	.word	.LC0
	.word	.LANCHOR29
	.word	.LANCHOR19
	.word	.LC126
	.word	.LANCHOR0
	.word	.LANCHOR1
	.word	.LANCHOR2
	.word	.LANCHOR51
	.word	.LANCHOR171
	.word	.LC127
	.word	.LANCHOR26
	.word	.LANCHOR3
	.size	flash_read_page_en, .-flash_read_page_en
	.section	.text.flash_get_last_written_page,"ax",%progbits
	.align	1
	.global	flash_get_last_written_page
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	flash_get_last_written_page, %function
flash_get_last_written_page:
	@ args = 4, pretend = 0, frame = 8
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r0, r1, r2, r3, r4, r5, r6, r7, r8, r10, fp, lr}
	mov	r8, r1
	ldr	r1, .L2226
	mov	fp, r2
	mov	r10, r3
	str	r0, [sp, #12]
	ldrh	r4, [r1]
	ldr	r1, .L2226+4
	subs	r4, r4, #1
	ldrh	r6, [r1, #26]
	sxth	r4, r4
	ldr	r1, [sp, #48]
	mul	r6, r8, r6
	str	r1, [sp]
	adds	r1, r4, r6
	bl	flash_read_page_en
	cmp	r0, #512
	bne	.L2217
	movs	r7, #0
.L2218:
	cmp	r7, r4
	ble	.L2221
.L2217:
	ldr	r3, .L2226+8
	ldr	r3, [r3]
	lsls	r3, r3, #19
	bpl	.L2222
	ldr	r3, [r10]
	mov	r2, r4
	mov	r1, r8
	ldr	r0, .L2226+12
	bl	printf
.L2222:
	mov	r0, r4
	add	sp, sp, #16
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r10, fp, pc}
.L2221:
	adds	r5, r7, r4
	ldr	r3, [sp, #48]
	add	r5, r5, r5, lsr #31
	mov	r2, fp
	ldr	r0, [sp, #12]
	asrs	r5, r5, #1
	str	r3, [sp]
	mov	r3, r10
	sxtah	r1, r6, r5
	bl	flash_read_page_en
	cmp	r0, #512
	itete	eq
	addeq	r4, r5, #-1
	addne	r5, r5, #1
	sxtheq	r4, r4
	sxthne	r7, r5
	b	.L2218
.L2227:
	.align	2
.L2226:
	.word	.LANCHOR144
	.word	.LANCHOR32
	.word	.LANCHOR19
	.word	.LC128
	.size	flash_get_last_written_page, .-flash_get_last_written_page
	.section	.text.flash_get_last_written_page_ext,"ax",%progbits
	.align	1
	.global	flash_get_last_written_page_ext
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	flash_get_last_written_page_ext, %function
flash_get_last_written_page_ext:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r0, r1, r2, r4, r5, lr}
	ldr	r4, .L2229
	ldr	r5, .L2229+4
	ldrb	r4, [r4]	@ zero_extendqisi2
	ldrh	r5, [r5]
	rsb	r4, r4, #24
	str	r3, [sp]
	mov	r3, r2
	mov	r2, r1
	subs	r4, r4, r5
	movs	r5, #1
	lsls	r5, r5, r4
	asr	r4, r0, r4
	subs	r5, r5, #1
	and	r1, r5, r0
	uxtb	r0, r4
	bl	flash_get_last_written_page
	add	sp, sp, #12
	@ sp needed
	pop	{r4, r5, pc}
.L2230:
	.align	2
.L2229:
	.word	.LANCHOR31
	.word	.LANCHOR74
	.size	flash_get_last_written_page_ext, .-flash_get_last_written_page_ext
	.section	.text.flash_ddr_para_scan,"ax",%progbits
	.align	1
	.global	flash_ddr_para_scan
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	flash_ddr_para_scan, %function
flash_ddr_para_scan:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r0, r1, r4, r5, r6, r7, r8, r10, fp, lr}
	mov	r7, r0
	ldr	r6, .L2237
	movs	r5, #1
	mov	r8, r1
	ldr	r4, .L2237+4
	ldr	fp, .L2237+8
	ldr	r10, .L2237+12
	ldrb	r0, [r6]	@ zero_extendqisi2
	strb	r5, [r4]
	bl	flash_set_interface_mode
	ldrb	r0, [r6]	@ zero_extendqisi2
	bl	nandc_set_if_mode
	movs	r3, #4
	ldr	r2, [r10]
	str	r3, [sp]
	mov	r1, r8
	ldr	r3, [fp]
	mov	r0, r7
	bl	flash_ddr_tuning_read
	movs	r3, #4
	ldr	r2, [r10]
	str	r3, [sp]
	mov	r1, r8
	ldr	r3, [fp]
	mov	r0, r7
	bl	flash_read_page
	adds	r0, r0, #1
	mov	r3, r4
	bne	.L2232
	ldrb	r2, [r6]	@ zero_extendqisi2
	lsls	r2, r2, #31
	bpl	.L2232
	mov	r0, r5
	bl	flash_set_interface_mode
	mov	r0, r5
	bl	nandc_set_if_mode
	movs	r3, #0
	strb	r3, [r4]
.L2233:
	movs	r0, #0
	add	sp, sp, #8
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r10, fp, pc}
.L2232:
	movs	r2, #1
	strb	r2, [r3]
	b	.L2233
.L2238:
	.align	2
.L2237:
	.word	.LANCHOR48
	.word	.LANCHOR26
	.word	.LANCHOR172
	.word	.LANCHOR173
	.size	flash_ddr_para_scan, .-flash_ddr_para_scan
	.section	.text.flash_prog_page,"ax",%progbits
	.align	1
	.global	flash_prog_page
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	flash_prog_page, %function
flash_prog_page:
	@ args = 4, pretend = 0, frame = 8
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r0, r1, r2, r3, r4, r5, r6, r7, r8, r10, fp, lr}
	mov	r10, r2
	str	r3, [sp, #12]
	mov	r4, r0
	mov	r6, r1
	add	r7, r0, #8
	ldr	r3, .L2250
	ldr	r5, [r3]
	ldr	r3, .L2250+4
	ldrb	r3, [r3]	@ zero_extendqisi2
	add	r7, r5, r7, lsl #8
	rsb	r2, r3, #24
	movs	r3, #1
	lsls	r3, r3, r2
	subs	r3, r3, #1
	and	fp, r3, r1
	bl	nandc_wait_flash_ready
	mov	r0, r4
	bl	hynix_reconfig_rr_para
	mov	r0, r4
	bl	nandc_cs
	tst	r6, #50331648
	mov	r0, r4
	bne	.L2240
	bl	zftl_flash_enter_slc_mode
.L2241:
	lsl	r8, r4, #8
	movs	r1, #128
	add	r2, r5, r8
	str	r1, [r2, #2056]
	movs	r1, #0
	str	r1, [r2, #2052]
	str	r1, [r2, #2052]
	uxtb	r1, fp
	str	r1, [r2, #2052]
	lsr	r1, fp, #8
	str	r1, [r2, #2052]
	lsr	r1, fp, #16
	str	r1, [r2, #2052]
	ldr	r1, .L2250+8
	ldrb	r1, [r1]	@ zero_extendqisi2
	cbz	r1, .L2242
	lsr	r1, fp, #24
	str	r1, [r2, #2052]
.L2242:
	mov	r0, fp
	add	r5, r5, r8
	bl	nandc_set_seed
	ldr	r3, .L2250+12
	movs	r1, #1
	mov	r0, r4
	ldrb	r2, [r3, #9]	@ zero_extendqisi2
	ldr	r3, [sp, #12]
	str	r3, [sp]
	mov	r3, r10
	bl	nandc_xfer
	movs	r3, #16
	str	r3, [r5, #2056]
	bl	nandc_wait_flash_ready
	mov	r0, r7
	bl	flash_read_status
	bl	nandc_de_cs.constprop.32
	ands	r0, r0, #4
	beq	.L2239
	mov	r2, r0
	mov	r1, r6
	ldr	r0, .L2250+16
	bl	printf
	mov	r0, #-1
.L2239:
	add	sp, sp, #16
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r10, fp, pc}
.L2240:
	bl	zftl_flash_exit_slc_mode
	b	.L2241
.L2251:
	.align	2
.L2250:
	.word	.LANCHOR7
	.word	.LANCHOR31
	.word	.LANCHOR30
	.word	.LANCHOR32
	.word	.LC129
	.size	flash_prog_page, .-flash_prog_page
	.section	.text.flash_test_blk,"ax",%progbits
	.align	1
	.global	flash_test_blk
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	flash_test_blk, %function
flash_test_blk:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r0, r1, r4, r5, r6, r7, r8, lr}
	movs	r2, #32
	ldr	r7, .L2262
	mov	r6, r0
	mov	r4, r1
	movs	r1, #165
	ldr	r5, .L2262+4
	ldr	r0, [r7]
	bl	ftl_memset
	movs	r2, #8
	movs	r1, #90
	ldr	r0, [r5]
	bl	ftl_memset
	ldr	r3, .L2262+8
	mov	r0, r6
	ldrh	r3, [r3]
	muls	r4, r3, r4
	mov	r1, r4
	bl	flash_erase_block
	adds	r0, r0, #1
	bne	.L2253
.L2255:
	mov	r5, #-1
.L2254:
	mov	r1, r4
	mov	r0, r6
	bl	flash_erase_block
	mov	r0, r5
	add	sp, sp, #8
	@ sp needed
	pop	{r4, r5, r6, r7, r8, pc}
.L2253:
	ldr	r8, .L2262+12
	mov	r1, r4
	mov	r0, r6
	ldrb	r3, [r8, #9]	@ zero_extendqisi2
	str	r3, [sp]
	ldr	r2, [r7]
	ldr	r3, [r5]
	bl	flash_prog_page
	adds	r0, r0, #1
	beq	.L2255
	ldrb	r3, [r8, #9]	@ zero_extendqisi2
	mov	r1, r4
	mov	r0, r6
	str	r3, [sp]
	ldr	r2, [r7]
	ldr	r3, [r5]
	bl	flash_read_page_en
	adds	r0, r0, #1
	beq	.L2255
	ldr	r3, [r7]
	ldr	r3, [r3]
	cmp	r3, #-1515870811
	bne	.L2255
	ldr	r3, [r5]
	ldr	r5, [r3]
	subs	r5, r5, #1515870810
	it	ne
	movne	r5, #-1
	b	.L2254
.L2263:
	.align	2
.L2262:
	.word	.LANCHOR163
	.word	.LANCHOR165
	.word	.LANCHOR2
	.word	.LANCHOR32
	.size	flash_test_blk, .-flash_test_blk
	.section	.text.id_block_prog_msb_ff_data,"ax",%progbits
	.align	1
	.global	id_block_prog_msb_ff_data
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	id_block_prog_msb_ff_data, %function
id_block_prog_msb_ff_data:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	ldr	r3, .L2271
	push	{r0, r1, r2, r4, r5, r6, r7, r8, r10, lr}
	mov	r6, r0
	mov	r7, r1
	mov	r4, r2
	ldrb	r3, [r3]	@ zero_extendqisi2
	cbnz	r3, .L2264
	ldr	r5, .L2271+4
	ldrb	r2, [r5, #19]	@ zero_extendqisi2
	subs	r3, r2, #5
	uxtb	r3, r3
	cmp	r3, #30
	bhi	.L2266
	ldr	r2, .L2271+8
	lsr	r3, r2, r3
	lsls	r3, r3, #31
	bmi	.L2268
.L2264:
	add	sp, sp, #12
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r10, pc}
.L2269:
	ldrh	r2, [r10, r4, lsl #1]
	movw	r3, #65535
	cmp	r2, r3
	bne	.L2264
	mov	r2, #16384
	movs	r1, #255
	ldr	r0, [r8]
	bl	ftl_memset
	ldrb	r3, [r5, #9]	@ zero_extendqisi2
	adds	r1, r4, r7
	adds	r4, r4, #1
	mov	r0, r6
	uxth	r4, r4
	str	r3, [sp]
	ldr	r3, [r8]
	mov	r2, r3
	bl	flash_prog_page
.L2270:
	ldrh	r3, [r5, #10]
	cmp	r3, r4
	bhi	.L2269
	b	.L2264
.L2266:
	cmp	r2, #68
	bne	.L2264
.L2268:
	ldr	r10, .L2271+12
	ldr	r8, .L2271+16
	b	.L2270
.L2272:
	.align	2
.L2271:
	.word	.LANCHOR24
	.word	.LANCHOR32
	.word	1073758215
	.word	.LANCHOR142
	.word	.LANCHOR163
	.size	id_block_prog_msb_ff_data, .-id_block_prog_msb_ff_data
	.section	.text.flash_start_one_pass_page_prog,"ax",%progbits
	.align	1
	.global	flash_start_one_pass_page_prog
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	flash_start_one_pass_page_prog, %function
flash_start_one_pass_page_prog:
	@ args = 12, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r0, r1, r2, r4, r5, r6, r7, r8, r10, lr}
	mov	r7, r3
	ldr	r3, .L2282
	mov	r10, r0
	mov	r0, r7
	mov	r8, r2
	ldr	r5, [sp, #40]
	lsls	r6, r7, #8
	ldr	r4, [r3]
	bl	nandc_cs
	cmp	r10, #0
	beq	.L2274
	adds	r3, r4, r6
	str	r10, [r3, #2056]
.L2274:
	adds	r3, r4, r6
	movs	r2, #128
	str	r2, [r3, #2056]
	movs	r2, #0
	str	r2, [r3, #2052]
	str	r2, [r3, #2052]
	uxtb	r2, r5
	str	r2, [r3, #2052]
	lsrs	r2, r5, #8
	str	r2, [r3, #2052]
	lsrs	r2, r5, #16
	str	r2, [r3, #2052]
	ldr	r2, .L2282+4
	ldrb	r2, [r2]	@ zero_extendqisi2
	cbz	r2, .L2275
	lsrs	r2, r5, #24
	str	r2, [r3, #2052]
.L2275:
	mov	r0, r5
	add	r4, r4, r6
	bl	nandc_set_seed
	ldr	r3, .L2282+8
	movs	r1, #1
	mov	r0, r7
	ldrb	r2, [r3, #9]	@ zero_extendqisi2
	ldr	r3, [sp, #48]
	str	r3, [sp]
	ldr	r3, [sp, #44]
	bl	nandc_xfer
	str	r8, [r4, #2056]
	add	sp, sp, #12
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r10, pc}
.L2283:
	.align	2
.L2282:
	.word	.LANCHOR7
	.word	.LANCHOR30
	.word	.LANCHOR32
	.size	flash_start_one_pass_page_prog, .-flash_start_one_pass_page_prog
	.section	.text.flash_dual_page_prog,"ax",%progbits
	.align	1
	.global	flash_dual_page_prog
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	flash_dual_page_prog, %function
flash_dual_page_prog:
	@ args = 12, pretend = 0, frame = 8
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, r8, r10, fp, lr}
	sub	sp, sp, #24
	str	r2, [sp, #20]
	mov	fp, r3
	add	r3, r0, #8
	mov	r5, r0
	ldr	r2, .L2296
	mov	r6, r1
	ubfx	r8, r1, #24, #2
	ldr	r7, [r2]
	add	r7, r7, r3, lsl #8
	ldr	r3, .L2296+4
	ldrb	r4, [r3]	@ zero_extendqisi2
	rsb	r3, r4, #24
	movs	r4, #1
	lsls	r4, r4, r3
	ldr	r3, .L2296+8
	subs	r4, r4, #1
	ldr	r2, [r3]
	ands	r4, r4, r1
	mov	r10, r3
	tst	r2, #16
	beq	.L2285
	ldr	r3, [sp, #64]
	mov	r2, r8
	ldr	r0, .L2296+12
	bl	printf
.L2285:
	bl	nandc_wait_flash_ready
	mov	r0, r5
	bl	nandc_cs
	mov	r0, r5
	cmp	r8, #0
	bne	.L2286
	bl	zftl_flash_enter_slc_mode
.L2287:
	ldr	r3, [sp, #20]
	movs	r1, #0
	movs	r2, #16
	mov	r0, r1
	str	r4, [sp]
	adds	r4, r4, #1
	str	r3, [sp, #4]
	mov	r3, r5
	str	fp, [sp, #8]
	bl	flash_start_one_pass_page_prog
	bl	nandc_wait_flash_ready
	ldr	r3, [sp, #60]
	movs	r1, #0
	movs	r2, #16
	mov	r0, r1
	str	r4, [sp]
	str	r3, [sp, #8]
	ldr	r3, [sp, #56]
	str	r3, [sp, #4]
	mov	r3, r5
	bl	flash_start_one_pass_page_prog
	bl	nandc_wait_flash_ready
	mov	r0, r7
	bl	flash_read_status
	bl	nandc_de_cs.constprop.32
	ands	r0, r0, #4
	beq	.L2284
	ldr	r3, [r10]
	lsls	r3, r3, #19
	bpl	.L2289
	mov	r2, r0
	mov	r1, r6
	ldr	r0, .L2296+16
	bl	printf
.L2289:
	mov	r0, #-1
.L2284:
	add	sp, sp, #24
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r10, fp, pc}
.L2286:
	bl	zftl_flash_exit_slc_mode
	b	.L2287
.L2297:
	.align	2
.L2296:
	.word	.LANCHOR7
	.word	.LANCHOR31
	.word	.LANCHOR19
	.word	.LC130
	.word	.LC129
	.size	flash_dual_page_prog, .-flash_dual_page_prog
	.section	.text.ymtc_flash_tlc_page_prog,"ax",%progbits
	.align	1
	.global	ymtc_flash_tlc_page_prog
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	ymtc_flash_tlc_page_prog, %function
ymtc_flash_tlc_page_prog:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r0, r1, r2, r3, r4, r5, r6, r7, r8, r10, fp, lr}
	mov	r10, r2
	ldr	r2, .L2304
	mov	fp, r3
	add	r3, r0, #8
	movs	r6, #1
	mov	r5, r0
	mov	r8, r1
	ldr	r7, [r2]
	add	r7, r7, r3, lsl #8
	ldr	r3, .L2304+4
	ldrb	r4, [r3]	@ zero_extendqisi2
	rsb	r4, r4, #24
	lsl	r4, r6, r4
	subs	r4, r4, #1
	ands	r4, r4, r1
	bl	nandc_wait_flash_ready
	mov	r0, r5
	bl	nandc_cs
	mov	r0, r5
	bl	zftl_flash_exit_slc_mode
	mov	r3, r5
	movs	r2, #26
	mov	r1, r6
	stm	sp, {r4, r10, fp}
	movs	r0, #0
	bl	flash_start_one_pass_page_prog
	bl	nandc_wait_flash_ready
	adds	r3, r4, r6
	movs	r2, #26
	mov	r1, r6
	str	r3, [sp]
	movs	r0, #0
	mov	r3, r5
	str	fp, [sp, #8]
	adds	r4, r4, #2
	str	r10, [sp, #4]
	bl	flash_start_one_pass_page_prog
	bl	nandc_wait_flash_ready
	mov	r3, r5
	movs	r2, #16
	mov	r1, r6
	movs	r0, #0
	str	fp, [sp, #8]
	str	r10, [sp, #4]
	str	r4, [sp]
	bl	flash_start_one_pass_page_prog
	bl	nandc_wait_flash_ready
	mov	r0, r7
	bl	flash_read_status
	bl	nandc_de_cs.constprop.32
	ands	r0, r0, #4
	beq	.L2298
	ldr	r3, .L2304+8
	ldr	r3, [r3]
	lsls	r3, r3, #19
	bpl	.L2300
	mov	r2, r0
	mov	r1, r8
	ldr	r0, .L2304+12
	bl	printf
.L2300:
	mov	r0, #-1
.L2298:
	add	sp, sp, #16
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r10, fp, pc}
.L2305:
	.align	2
.L2304:
	.word	.LANCHOR7
	.word	.LANCHOR31
	.word	.LANCHOR19
	.word	.LC131
	.size	ymtc_flash_tlc_page_prog, .-ymtc_flash_tlc_page_prog
	.section	.text.fw_flash_page_prog.constprop.29,"ax",%progbits
	.align	1
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	fw_flash_page_prog.constprop.29, %function
fw_flash_page_prog.constprop.29:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, r8, r10, lr}
	mov	r5, r1
	ldr	r8, .L2311+12
	sub	sp, sp, #20
	mov	r6, r2
	ldrb	r1, [r8, #9]	@ zero_extendqisi2
	bl	__aeabi_uidiv
	ldr	r3, .L2311
	mov	r4, r0
	ldrb	r10, [r3]	@ zero_extendqisi2
	ldr	r3, .L2311+4
	ldrb	r0, [r3]	@ zero_extendqisi2
	bl	nandc_bch_sel
	ldrb	r3, [r8, #7]	@ zero_extendqisi2
	cmp	r3, #9
	bne	.L2307
	ldr	r3, .L2311+8
	ldrb	r7, [r3]	@ zero_extendqisi2
	cbnz	r7, .L2307
	ldrb	r3, [r8, #12]	@ zero_extendqisi2
	cmp	r3, #3
	bne	.L2308
	mov	r3, r6
	mov	r2, r5
	mov	r1, r4
	mov	r0, r7
	bl	ymtc_flash_tlc_page_prog
.L2310:
	mov	r4, r0
	mov	r0, r10
	bl	nandc_bch_sel
	mov	r0, r4
	add	sp, sp, #20
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r10, pc}
.L2308:
	ldr	r8, .L2311+16
	mov	r2, #16384
	movs	r1, #255
	ldr	r0, [r8]
	bl	ftl_memset
	ldr	r3, [r8]
	movs	r2, #4
	str	r2, [sp, #8]
	mov	r1, r4
	mov	r2, r5
	mov	r0, r7
	str	r3, [sp, #4]
	str	r3, [sp]
	mov	r3, r6
	bl	flash_dual_page_prog
	b	.L2310
.L2307:
	movs	r3, #4
	mov	r2, r5
	str	r3, [sp]
	mov	r1, r4
	mov	r3, r6
	movs	r0, #0
	bl	flash_prog_page
	b	.L2310
.L2312:
	.align	2
.L2311:
	.word	.LANCHOR49
	.word	.LANCHOR22
	.word	.LANCHOR24
	.word	.LANCHOR32
	.word	.LANCHOR163
	.size	fw_flash_page_prog.constprop.29, .-fw_flash_page_prog.constprop.29
	.section	.text.idb_write_data,"ax",%progbits
	.align	1
	.global	idb_write_data
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	idb_write_data, %function
idb_write_data:
	@ args = 0, pretend = 0, frame = 144
	@ frame_needed = 0, uses_anonymous_args = 0
	cmp	r1, #64
	push	{r4, r5, r6, r7, r8, r10, fp, lr}
	mov	r4, r1
	sub	sp, sp, #152
	mov	r7, r2
	mov	r5, r3
	ldr	r6, .L2442
	bne	.L2314
	ldr	r3, [r2]
	ldr	r2, .L2442+4
	cmp	r3, r2
	beq	.L2315
	ldr	r2, .L2442+8
	cmp	r3, r2
	beq	.L2315
	add	r2, r2, #327680
	cmp	r3, r2
	bne	.L2314
.L2315:
	ldr	r8, .L2442+16
	movs	r2, #1
	strb	r2, [r6]
	ldr	r3, [r8]
	cbnz	r3, .L2316
	mov	r0, #262144
	bl	ftl_malloc
	str	r0, [r8]
.L2316:
	ldr	r3, .L2442+12
	movs	r2, #64
	str	r2, [r3]
.L2314:
	ldrb	r0, [r6]	@ zero_extendqisi2
	cmp	r0, #0
	beq	.L2313
	ldr	r3, .L2442+16
	ldr	r10, [r3]
	mov	r8, r3
	cmp	r10, #0
	beq	.L2441
	adds	r3, r4, r5
	cmp	r3, #63
	str	r3, [sp, #72]
	bls	.L2318
	cmp	r4, #576
	bcs	.L2319
	ldr	r10, .L2442+24
	ldr	r3, [r10]
	cbz	r3, .L2320
.L2323:
	ldr	r3, .L2442+20
	cmp	r4, #64
	mov	r2, #1
	ldr	r0, [r8]
	str	r2, [r3]
	bhi	.L2436
	rsb	r1, r4, #64
	subs	r2, r5, r1
	add	r1, r7, r1, lsl #9
	lsls	r2, r2, #9
.L2440:
	bl	ftl_memcpy
.L2324:
	ldr	r3, .L2442+12
	ldr	r3, [r3]
	cmp	r4, r3
	itt	ne
	movne	r3, #0
	strbne	r3, [r6]
	b	.L2381
.L2320:
	mov	r0, #262144
	bl	ftl_malloc
	str	r0, [r10]
	cmp	r0, #0
	bne	.L2323
	mov	r0, #-1
	b	.L2313
.L2436:
	rsb	r2, r4, #576
	sub	r3, r4, #64
	cmp	r2, r5
	mov	r1, r7
	it	cs
	movcs	r2, r5
	add	r0, r0, r3, lsl #9
	lsls	r2, r2, #9
	b	.L2440
.L2443:
	.align	2
.L2442:
	.word	.LANCHOR140
	.word	-52655045
	.word	1397640018
	.word	.LANCHOR174
	.word	.LANCHOR138
	.word	.LANCHOR139
	.word	.LANCHOR141
.L2318:
	cmp	r4, #576
	bcc	.L2324
.L2319:
	ldr	r3, .L2444
	ldr	r3, [r3]
	cmp	r3, #0
	beq	.L2324
	ldr	r3, [r10]
	ldr	r2, .L2444+4
	cmp	r3, r2
	beq	.L2325
	ldr	r2, .L2444+8
	cmp	r3, r2
	beq	.L2325
	add	r2, r2, #327680
	cmp	r3, r2
	bne	.L2326
.L2325:
	ldr	r7, .L2444+12
	ldrb	r3, [r7]	@ zero_extendqisi2
	str	r3, [sp, #24]
	ldr	r3, .L2444+16
	ldrb	r2, [r3]	@ zero_extendqisi2
	mov	r8, r3
	ldr	r3, [sp, #24]
	str	r2, [sp, #12]
	cmp	r3, #0
	beq	.L2327
	clz	fp, r2
	ldrh	r3, [sp, #24]
	lsr	fp, fp, #5
	str	r3, [sp, #36]
.L2328:
	ldr	r6, .L2444+20
	movs	r0, #0
	ldrb	r5, [r6, #9]	@ zero_extendqisi2
	ldrh	r4, [r6, #26]
	bl	zftl_flash_exit_slc_mode
	ldrh	r0, [r6, #10]
	ldrb	r3, [r8]	@ zero_extendqisi2
	ldrb	r1, [r6, #12]	@ zero_extendqisi2
	movw	r6, #4098
	strb	r3, [r7]
	lsls	r0, r0, #2
	ldr	r7, .L2444+24
	bl	__aeabi_idiv
	cmp	r0, #512
	mov	r3, r0
	it	ge
	movge	r3, #512
	add	r1, r10, #260096
	str	r3, [sp, #32]
	movw	r2, #65023
	movs	r3, #0
.L2334:
	ldr	r0, [r1, #-4]!
	cbnz	r0, .L2330
	cmp	r3, #0
	bne	.L2331
	str	r7, [r1, #2048]
.L2332:
	adds	r3, r3, #1
	subs	r2, r2, #1
	cmp	r3, r6
	it	hi
	movhi	r3, #0
	cmp	r2, #4096
	bne	.L2334
.L2330:
	ldr	r3, [sp, #32]
	ldr	r1, [r10, r2, lsl #2]
	ldr	r0, .L2444+28
	bl	printf
	mul	r3, r5, r4
	str	r3, [sp, #84]
	movs	r3, #0
	str	r3, [sp, #16]
	str	r3, [sp, #28]
.L2376:
	ldr	r3, .L2444+32
	mov	r2, #512
	movs	r1, #0
	ldr	r0, [r3]
	bl	ftl_memset
	ldr	r3, .L2444+36
	ldr	r2, [sp, #28]
	ldr	r3, [r3]
	add	r3, r3, r2
	ldrb	r3, [r3, #32]	@ zero_extendqisi2
	cmp	r3, #255
	beq	.L2335
	ldr	r2, [sp, #84]
	muls	r3, r2, r3
	str	r3, [sp, #8]
	cmp	fp, #0
	beq	.L2336
	ldr	r3, [sp, #28]
	ldr	r5, .L2444+12
	ldr	r4, .L2444+16
	bic	r3, r3, #2
	cmp	r3, #1
	beq	.L2337
	cmp	fp, #3
	bne	.L2338
.L2337:
	ldrb	r3, [sp, #36]	@ zero_extendqisi2
.L2438:
	strb	r3, [r5]
	strb	r3, [r4]
.L2336:
	ldr	r7, .L2444+20
	movs	r5, #0
	ldr	r3, .L2444+40
	ldr	r0, [sp, #8]
	ldrb	r6, [r7, #9]	@ zero_extendqisi2
	ldrb	r3, [r3]	@ zero_extendqisi2
	ldrh	r4, [r7, #26]
	mov	r1, r6
	str	r3, [sp, #76]
	ldr	r3, .L2444+40
	muls	r4, r6, r4
	strb	r5, [r3]
	bl	__aeabi_uidiv
	mov	r1, r0
	mov	r0, r5
	bl	flash_erase_block
	mov	r1, r4
	ldr	r0, [sp, #8]
	bl	__aeabi_uidivmod
	ldrh	r0, [r7, #10]
	ldr	r3, [sp, #8]
	str	r1, [sp, #44]
	subs	r3, r3, r1
	lsls	r0, r0, #2
	ldrb	r1, [r7, #12]	@ zero_extendqisi2
	str	r3, [sp, #40]
	bl	__aeabi_idiv
	ldr	r3, [sp, #8]
	ldr	r2, [sp, #40]
	str	r0, [sp, #48]
	cmp	r3, r2
	bne	.L2391
	ldr	r3, .L2444+44
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, #9
	bne	.L2391
	ldr	r3, .L2444+32
	mov	r2, #1024
	mov	r1, r5
	ldr	r4, [r3]
	mov	r0, r4
	bl	ftl_memset
	ldr	r2, .L2444+48
	movs	r3, #12
	str	r5, [r4, #12]
	strb	r5, [r4, #16]
	stm	r4, {r2, r3}
	ldr	r3, .L2444+16
	ldrb	r3, [r3]	@ zero_extendqisi2
	cbz	r3, .L2340
	ldrb	r3, [r7, #29]	@ zero_extendqisi2
	strb	r3, [r4, #16]
.L2340:
	movs	r3, #4
	strb	r3, [r4, #17]
	ldr	r3, .L2444+20
	ldrb	r1, [r3, #12]	@ zero_extendqisi2
	ldrh	r0, [r3, #10]
	bl	__aeabi_idiv
	cmp	r6, #8
	mov	r3, #0
	ite	hi
	movhi	r2, #70
	movls	r2, #16
	movs	r1, #12
	strh	r0, [r4, #18]	@ movhi
	strb	r3, [r4, #20]
	adds	r0, r4, r1
	strh	r3, [r4, #22]	@ movhi
	strb	r2, [r4, #21]
	bl	js_hash
	ldr	r3, [sp, #32]
	str	r0, [r4, #8]
	subs	r3, r3, #4
	str	r3, [sp, #20]
.L2339:
	mov	r8, r10
	movs	r7, #0
.L2342:
	ldr	r3, [sp, #48]
	cmp	r3, r7
	bhi	.L2353
	ldr	r3, .L2444+32
	movs	r4, #0
	ldr	r0, [sp, #8]
	movs	r6, #4
	ldr	r5, [r3]
	ldr	r3, .L2444+20
	ldrb	r2, [r3, #9]	@ zero_extendqisi2
	ldrh	r1, [r3, #26]
	ldr	r3, .L2444+40
	str	r2, [sp, #64]
	strb	r4, [r3]
	muls	r1, r2, r1
	bl	__aeabi_uidivmod
	ldr	r3, [sp, #8]
	str	r1, [sp, #44]
	str	r4, [sp, #56]
	subs	r3, r3, r1
	str	r3, [sp, #68]
	and	r3, r1, #3
	str	r3, [sp, #48]
	ldr	r3, [sp, #20]
	str	r3, [sp, #60]
.L2354:
	ldr	r3, [sp, #60]
	cmp	r4, r3
	bcc	.L2370
	ldr	r3, .L2444+40
	ldrb	r2, [sp, #76]	@ zero_extendqisi2
	strb	r2, [r3]
	cmp	fp, #0
	beq	.L2371
	movs	r0, #0
	bl	zftl_flash_exit_slc_mode
	ldr	r2, .L2444+12
	movs	r3, #0
	strb	r3, [r2]
	ldr	r2, .L2444+16
	strb	r3, [r2]
.L2371:
	ldr	r3, [sp, #20]
	movs	r4, #0
	lsls	r1, r3, #7
	ldr	r3, .L2444+32
	ldr	r0, [r3]
.L2372:
	cmp	r4, r1
	bne	.L2374
	ldr	r3, [sp, #16]
	adds	r3, r3, #1
	cmp	r3, #5
	str	r3, [sp, #16]
	bls	.L2335
	b	.L2383
.L2327:
	ldr	r3, [sp, #12]
	cmp	r3, #3
	beq	.L2387
	cmp	r3, #2
	bne	.L2388
	str	r3, [sp, #36]
	mov	fp, #3
	b	.L2328
.L2387:
	ldr	r3, [sp, #12]
	mov	fp, #2
	str	r3, [sp, #36]
	b	.L2328
.L2388:
	ldr	r3, [sp, #24]
	str	r3, [sp, #36]
	mov	fp, r3
	b	.L2328
.L2331:
	ldr	r0, [r10, r3, lsl #2]
	str	r0, [r1, #2048]
	b	.L2332
.L2338:
	movs	r0, #0
	bl	zftl_flash_exit_slc_mode
	movs	r3, #0
	b	.L2438
.L2391:
	ldr	r3, [sp, #32]
	mov	r4, r5
	str	r3, [sp, #20]
	b	.L2339
.L2445:
	.align	2
.L2444:
	.word	.LANCHOR139
	.word	-52655045
	.word	1397640018
	.word	.LANCHOR0
	.word	.LANCHOR24
	.word	.LANCHOR32
	.word	1330594389
	.word	.LC132
	.word	.LANCHOR141
	.word	.LANCHOR6
	.word	.LANCHOR51
	.word	.LANCHOR27
	.word	1179535694
.L2353:
	ldr	r3, [sp, #44]
	adds	r5, r3, r7
	ldr	r3, .L2446
	ubfx	r5, r5, #2, #16
	adds	r2, r5, #1
	ldrh	r0, [r3, r2, lsl #1]
	ldr	r3, .L2446+4
	ldrb	r1, [r3]	@ zero_extendqisi2
	cmp	r1, #0
	bne	.L2343
	mov	r2, r0
.L2344:
	ldr	r0, .L2446+8
	ldr	r3, .L2446
	ldrb	r0, [r0]	@ zero_extendqisi2
	cmp	r0, #9
	itt	ne
	addne	r2, r2, #-1
	lslne	r2, r2, #2
	str	r2, [sp, #88]
	movw	r2, #61424
	str	r2, [sp, #92]
	ldrh	r2, [r3, r5, lsl #1]
	cbnz	r1, .L2348
	mov	r5, r2
.L2349:
	mul	r0, r5, r6
	add	r2, sp, #88
	cbnz	r4, .L2350
	ldr	r3, [sp, #40]
	mov	r1, r8
	add	r0, r0, r3
	bl	fw_flash_page_prog.constprop.29
	ldr	r3, .L2446+4
	ldrb	r2, [r3]	@ zero_extendqisi2
	cbnz	r2, .L2351
	adds	r5, r5, #1
	mov	r1, r6
	uxth	r5, r5
	ldr	r0, [sp, #40]
	bl	__aeabi_uidiv
	mov	r2, r5
	mov	r1, r0
	mov	r0, r4
	bl	id_block_prog_msb_ff_data
.L2351:
	ldr	r3, [sp, #20]
	add	r8, r8, #2048
	add	r2, r3, #16
	cmp	r7, r2
	bcc	.L2352
	add	r2, r3, #20
	cmp	r7, r2
	bcs	.L2352
	add	r8, r10, #2048
.L2352:
	adds	r3, r7, #4
	movs	r4, #0
	uxth	r7, r3
	b	.L2342
.L2343:
	ldr	r0, .L2446+12
	ldrb	r0, [r0]	@ zero_extendqisi2
	cmp	r0, #0
	beq	.L2344
	lsls	r2, r2, #1
	b	.L2344
.L2348:
	ldr	r2, .L2446+12
	ldrb	r2, [r2]	@ zero_extendqisi2
	cmp	r2, #0
	beq	.L2349
	lsls	r5, r5, #1
	b	.L2349
.L2350:
	ldr	r3, [sp, #40]
	mov	r1, r4
	add	r0, r0, r3
	bl	fw_flash_page_prog.constprop.29
	b	.L2352
.L2370:
	ldr	r3, [sp, #48]
	mov	r1, r6
	subs	r3, r6, r3
	uxth	r3, r3
	str	r3, [sp, #52]
	ldr	r3, [sp, #44]
	adds	r0, r3, r4
	bl	__aeabi_uidiv
	ldr	r2, .L2446+4
	uxth	r0, r0
	ldr	r3, .L2446
	ldrb	r2, [r2]	@ zero_extendqisi2
	ldrh	r3, [r3, r0, lsl #1]
	cmp	r2, #0
	bne	.L2355
	mov	r0, r3
.L2356:
	ldr	r3, .L2446+16
	ldr	r2, [sp, #68]
	ldrb	r8, [r3]	@ zero_extendqisi2
	ldr	r3, [sp, #48]
	add	r3, r3, r2
	ldr	r2, .L2446+20
	ldrb	r1, [r2, #9]	@ zero_extendqisi2
	ldr	r2, [sp, #64]
	mla	r0, r0, r2, r3
	bl	__aeabi_uidiv
	ldr	r3, .L2446+24
	str	r0, [sp, #40]
	mov	r0, r8
	ldrb	r3, [r3]	@ zero_extendqisi2
	str	r3, [sp, #80]
	bl	nandc_bch_sel
.L2357:
	str	r6, [sp]
	add	r3, sp, #88
	mov	r2, r5
	ldr	r1, [sp, #40]
	movs	r0, #0
	bl	flash_read_page
	adds	r0, r0, #1
	bne	.L2358
	ldr	r3, .L2446+28
	ldrb	r3, [r3]	@ zero_extendqisi2
	mov	r7, r3
	cmp	r3, #0
	bne	.L2359
.L2362:
	ldr	r3, .L2446+32
	ldr	r3, [r3]
	mov	r7, r3
	cmp	r3, #0
	bne	.L2360
.L2361:
	ldr	r3, .L2446+36
	ldrb	r3, [r3]	@ zero_extendqisi2
	cbz	r3, .L2364
	str	r6, [sp]
	add	r3, sp, #88
	mov	r2, r5
	ldr	r1, [sp, #40]
	movs	r0, #0
	bl	flash_ddr_tuning_read
	adds	r0, r0, #1
	bne	.L2358
.L2364:
	cmp	r8, #16
	bne	.L2365
	mov	r7, #-1
.L2366:
	ldr	r0, [sp, #80]
	bl	nandc_bch_sel
	ldr	r3, [sp, #56]
	cmp	r7, #0
	it	ne
	movne	r3, #-1
	ldr	r2, [sp, #68]
	str	r3, [sp, #56]
	ldr	r3, [sp, #8]
	cmp	r3, r2
	bne	.L2368
	cmp	r4, #0
	bne	.L2368
	ldr	r3, [sp, #56]
	cmp	r3, #0
	bne	.L2368
	ldr	r2, [r5]
	ldr	r3, .L2446+40
	cmp	r2, r3
	bne	.L2368
	ldr	r3, [sp, #60]
	ldr	r2, [sp, #52]
	ldrb	r6, [r5, #17]	@ zero_extendqisi2
	add	r3, r3, r2
	str	r3, [sp, #60]
.L2369:
	ldr	r3, [sp, #52]
	add	r3, r3, r4
	uxth	r4, r3
	b	.L2354
.L2355:
	ldr	r3, .L2446+12
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L2356
	lsls	r0, r0, #1
	b	.L2356
.L2359:
	ldr	r3, .L2446+28
	movs	r0, #0
	mov	r2, r5
	ldr	r1, [sp, #40]
	strb	r0, [r3]
	add	r3, sp, #88
	str	r6, [sp]
	bl	flash_read_page
	ldr	r3, .L2446+28
	adds	r0, r0, #1
	strb	r7, [r3]
	beq	.L2362
.L2358:
	movs	r7, #0
	b	.L2366
.L2360:
	str	r6, [sp]
	add	r3, sp, #88
	mov	r2, r5
	ldr	r1, [sp, #40]
	movs	r0, #0
	blx	r7
	adds	r0, r0, #1
	beq	.L2361
	b	.L2358
.L2365:
	movs	r0, #16
	mov	r8, #16
	bl	nandc_bch_sel
	b	.L2357
.L2368:
	ldr	r3, [sp, #52]
	add	r5, r5, r3, lsl #9
	movs	r3, #0
	str	r3, [sp, #48]
	b	.L2369
.L2374:
	ldr	r2, [r0, r4, lsl #2]
	ldr	r3, [r10, r4, lsl #2]
	cmp	r2, r3
	beq	.L2373
	mov	r2, #512
	movs	r1, #0
	bl	ftl_memset
	mov	r1, r4
	ldr	r0, .L2446+44
	bl	printf
	ldr	r1, [sp, #8]
	movs	r0, #0
	bl	flash_erase_block
.L2335:
	ldr	r3, [sp, #28]
	adds	r3, r3, #1
	cmp	r3, #4
	str	r3, [sp, #28]
	bne	.L2376
.L2383:
	movs	r0, #0
	bl	zftl_flash_exit_slc_mode
	ldr	r3, .L2446+48
	ldrb	r2, [sp, #24]	@ zero_extendqisi2
	strb	r2, [r3]
	cmp	fp, #0
	beq	.L2377
	ldr	r3, .L2446+4
	ldrb	r2, [sp, #12]	@ zero_extendqisi2
	strb	r2, [r3]
.L2377:
	ldr	r3, .L2446+52
	movs	r2, #2
	movs	r0, #0
	strb	r2, [r3]
	bl	zftl_flash_enter_slc_mode
	ldr	r3, [sp, #16]
	cbnz	r3, .L2326
	mov	r1, r3
	ldr	r0, .L2446+56
	bl	printf
.L2326:
	ldr	r5, .L2446+60
	movs	r4, #0
	ldr	r3, .L2446+64
	ldr	r0, [r5]
	str	r4, [r3]
	ldr	r3, .L2446+68
	strb	r4, [r3]
	cbz	r0, .L2379
	bl	free
	str	r4, [r5]
.L2379:
	ldr	r4, .L2446+72
	ldr	r0, [r4]
	cbz	r0, .L2381
	bl	free
	movs	r3, #0
	str	r3, [r4]
.L2381:
	ldr	r3, .L2446+76
	ldr	r2, [sp, #72]
	str	r2, [r3]
.L2441:
	movs	r0, #0
.L2313:
	add	sp, sp, #152
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r10, fp, pc}
.L2373:
	adds	r4, r4, #1
	b	.L2372
.L2447:
	.align	2
.L2446:
	.word	.LANCHOR3
	.word	.LANCHOR24
	.word	.LANCHOR27
	.word	.LANCHOR1
	.word	.LANCHOR22
	.word	.LANCHOR32
	.word	.LANCHOR49
	.word	.LANCHOR51
	.word	.LANCHOR171
	.word	.LANCHOR26
	.word	1179535694
	.word	.LC133
	.word	.LANCHOR0
	.word	.LANCHOR33
	.word	.LC134
	.word	.LANCHOR138
	.word	.LANCHOR139
	.word	.LANCHOR140
	.word	.LANCHOR141
	.word	.LANCHOR174
	.size	idb_write_data, .-idb_write_data
	.section	.text.flash_start_tlc_page_prog,"ax",%progbits
	.align	1
	.global	flash_start_tlc_page_prog
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	flash_start_tlc_page_prog, %function
flash_start_tlc_page_prog:
	@ args = 12, pretend = 0, frame = 8
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r0, r1, r2, r3, r4, r5, r6, r7, r8, r10, fp, lr}
	mov	r6, r3
	mov	r8, r2
	ldr	r3, [sp, #56]
	mov	r4, r0
	mov	r7, r1
	ldr	r2, .L2455
	str	r3, [sp, #12]
	ldr	r5, [sp, #48]
	ldrb	r3, [r2]	@ zero_extendqisi2
	mov	fp, r2
	ldr	r10, [sp, #52]
	cmp	r3, r6
	bhi	.L2449
	mov	r2, #868
	ldr	r1, .L2455+4
	ldr	r0, .L2455+8
	bl	printf
.L2449:
	ldrb	r3, [fp]	@ zero_extendqisi2
	cmp	r3, r6
	bls	.L2448
	ldr	r3, .L2455+12
	ldrb	r6, [r3, r6]	@ zero_extendqisi2
	ldr	r3, .L2455+16
	mov	r0, r6
	ldr	fp, [r3]
	bl	nandc_cs
	lsls	r3, r6, #8
	cbz	r4, .L2451
	add	r1, fp, r3
	str	r4, [r1, #2056]
.L2451:
	add	r4, fp, r3
	movs	r3, #128
	str	r7, [r4, #2056]
	str	r3, [r4, #2056]
	movs	r3, #0
	str	r3, [r4, #2052]
	str	r3, [r4, #2052]
	uxtb	r3, r5
	str	r3, [r4, #2052]
	lsrs	r3, r5, #8
	str	r3, [r4, #2052]
	lsrs	r3, r5, #16
	add	r5, r5, r5, lsl #1
	str	r3, [r4, #2052]
	subs	r0, r5, #1
	add	r0, r0, r7
	bl	nandc_set_seed
	ldr	r3, .L2455+20
	movs	r1, #1
	mov	r0, r6
	ldrb	r2, [r3, #9]	@ zero_extendqisi2
	ldr	r3, [sp, #12]
	str	r3, [sp]
	mov	r3, r10
	bl	nandc_xfer
	str	r8, [r4, #2056]
	add	sp, sp, #16
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r10, fp, lr}
	b	nandc_de_cs.constprop.32
.L2448:
	add	sp, sp, #16
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r10, fp, pc}
.L2456:
	.align	2
.L2455:
	.word	.LANCHOR23
	.word	.LANCHOR175
	.word	.LC0
	.word	.LANCHOR29
	.word	.LANCHOR7
	.word	.LANCHOR32
	.size	flash_start_tlc_page_prog, .-flash_start_tlc_page_prog
	.section	.text.queue_tlc_prog_cmd,"ax",%progbits
	.align	1
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	queue_tlc_prog_cmd, %function
queue_tlc_prog_cmd:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r0, r1, r2, r3, r4, r5, r6, r7, r8, lr}
	movs	r7, #1
	ldr	r3, .L2461
	mov	r6, r0
	mov	r8, r1
	ldr	r2, [r0]
	ldrb	r3, [r3]	@ zero_extendqisi2
	ldr	r1, [r2, #24]
	rsb	r0, r3, #24
	lsl	r4, r7, r3
	ldr	r3, .L2461+4
	lsl	r5, r7, r0
	subs	r4, r4, #1
	subs	r5, r5, #1
	ldrb	r3, [r3]	@ zero_extendqisi2
	ands	r5, r5, r1
	lsrs	r1, r1, r0
	ands	r4, r4, r1
	uxtb	r4, r4
	cmp	r3, #0
	beq	.L2458
	mov	r0, r4
	bl	zftl_flash_exit_slc_mode
	ldr	r3, [r6]
	mov	r1, r7
	movs	r0, #0
	ldr	r2, [r3, #12]
	str	r2, [sp, #8]
	movs	r2, #26
	ldr	r3, [r3, #4]
	str	r5, [sp]
	str	r3, [sp, #4]
	mov	r3, r4
	bl	flash_start_one_pass_page_prog
	bl	nandc_wait_flash_ready
	ldr	r3, [r6, #4]
	mov	r1, r7
	movs	r0, #0
	ldr	r2, [r3, #12]
	str	r2, [sp, #8]
	movs	r2, #26
	ldr	r3, [r3, #4]
	str	r3, [sp, #4]
	adds	r3, r5, r7
	str	r3, [sp]
	mov	r3, r4
	bl	flash_start_one_pass_page_prog
	bl	nandc_wait_flash_ready
	ldr	r3, [r6, #8]
	adds	r5, r5, #2
	mov	r1, r7
	movs	r0, #0
	ldr	r2, [r3, #12]
	str	r2, [sp, #8]
	movs	r2, #16
	ldr	r3, [r3, #4]
	str	r5, [sp]
	str	r3, [sp, #4]
	mov	r3, r4
	bl	flash_start_one_pass_page_prog
.L2459:
	cmp	r8, #0
	beq	.L2457
	ldr	r1, [r6]
	movs	r3, #4
	ldr	r0, .L2461+8
	strb	r3, [r1, #42]
	movs	r3, #1
	strb	r3, [r1, #43]
	movs	r3, #255
	strb	r3, [r1]
	add	sp, sp, #16
	@ sp needed
	pop	{r4, r5, r6, r7, r8, lr}
	b	buf_add_tail
.L2458:
	ldr	r3, [r2, #12]
	mov	r1, r7
	ldrb	r0, [r2, #44]	@ zero_extendqisi2
	str	r3, [sp, #8]
	ldr	r3, [r2, #4]
	movs	r2, #26
	str	r5, [sp]
	str	r3, [sp, #4]
	mov	r3, r4
	bl	flash_start_tlc_page_prog
	bl	nandc_wait_flash_ready
	ldm	r6, {r2, r3}
	movs	r1, #2
	ldrb	r0, [r2, #44]	@ zero_extendqisi2
	ldr	r2, [r3, #12]
	str	r2, [sp, #8]
	movs	r2, #26
	ldr	r3, [r3, #4]
	str	r5, [sp]
	str	r3, [sp, #4]
	mov	r3, r4
	bl	flash_start_tlc_page_prog
	bl	nandc_wait_flash_ready
	ldr	r3, [r6, #8]
	movs	r1, #3
	ldr	r2, [r6]
	ldrb	r0, [r2, #44]	@ zero_extendqisi2
	ldr	r2, [r3, #12]
	str	r2, [sp, #8]
	movs	r2, #16
	ldr	r3, [r3, #4]
	str	r5, [sp]
	str	r3, [sp, #4]
	mov	r3, r4
	bl	flash_start_tlc_page_prog
	b	.L2459
.L2457:
	add	sp, sp, #16
	@ sp needed
	pop	{r4, r5, r6, r7, r8, pc}
.L2462:
	.align	2
.L2461:
	.word	.LANCHOR31
	.word	.LANCHOR36
	.word	.LANCHOR59
	.size	queue_tlc_prog_cmd, .-queue_tlc_prog_cmd
	.section	.text.sblk_3d_tlc_dump_prog,"ax",%progbits
	.align	1
	.global	sblk_3d_tlc_dump_prog
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	sblk_3d_tlc_dump_prog, %function
sblk_3d_tlc_dump_prog:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r0, r1, r2, r3, r4, r5, r6, r7, r8, lr}
	movs	r7, #1
	ldr	r3, .L2466
	mov	r5, r0
	ldr	r2, [r0, #24]
	ldrb	r3, [r3]	@ zero_extendqisi2
	rsb	r1, r3, #24
	lsl	r4, r7, r3
	lsl	r6, r7, r1
	ldr	r3, .L2466+4
	subs	r6, r6, #1
	subs	r4, r4, #1
	ands	r6, r6, r2
	lsrs	r2, r2, r1
	ldrb	r8, [r3]	@ zero_extendqisi2
	ands	r4, r4, r2
	uxtb	r4, r4
	cmp	r8, #0
	beq	.L2464
	mov	r0, r4
	bl	zftl_flash_exit_slc_mode
	ldr	r3, [r5, #12]
	movs	r2, #26
	mov	r1, r7
	str	r6, [sp]
	movs	r0, #0
	str	r3, [sp, #8]
	ldr	r3, [r5, #4]
	str	r3, [sp, #4]
	mov	r3, r4
	bl	flash_start_one_pass_page_prog
	bl	nandc_wait_flash_ready
	ldr	r3, [r5, #12]
	movs	r2, #26
	mov	r1, r7
	movs	r0, #0
	str	r3, [sp, #8]
	ldr	r3, [r5, #4]
	str	r3, [sp, #4]
	adds	r3, r6, r7
	str	r3, [sp]
	mov	r3, r4
	bl	flash_start_one_pass_page_prog
	bl	nandc_wait_flash_ready
	ldr	r3, [r5, #12]
	adds	r6, r6, #2
	str	r6, [sp]
	movs	r2, #16
	mov	r1, r7
	movs	r0, #0
	str	r3, [sp, #8]
	ldr	r3, [r5, #4]
	str	r3, [sp, #4]
	mov	r3, r4
	bl	flash_start_one_pass_page_prog
.L2465:
	bl	nandc_wait_flash_ready
	movs	r1, #64
	ldr	r0, [r5, #24]
	add	sp, sp, #16
	@ sp needed
	pop	{r4, r5, r6, r7, r8, lr}
	b	flash_wait_device_ready
.L2464:
	ldr	r3, [r0, #12]
	mov	r1, r7
	movs	r2, #26
	str	r3, [sp, #8]
	ldr	r3, [r0, #4]
	mov	r0, r8
	str	r6, [sp]
	str	r3, [sp, #4]
	mov	r3, r4
	bl	flash_start_tlc_page_prog
	bl	nandc_wait_flash_ready
	ldr	r3, [r5, #12]
	movs	r2, #26
	movs	r1, #2
	mov	r0, r8
	str	r6, [sp]
	str	r3, [sp, #8]
	ldr	r3, [r5, #4]
	str	r3, [sp, #4]
	mov	r3, r4
	bl	flash_start_tlc_page_prog
	bl	nandc_wait_flash_ready
	ldr	r3, [r5, #12]
	movs	r2, #16
	str	r6, [sp]
	movs	r1, #3
	mov	r0, r8
	str	r3, [sp, #8]
	ldr	r3, [r5, #4]
	str	r3, [sp, #4]
	mov	r3, r4
	bl	flash_start_tlc_page_prog
	b	.L2465
.L2467:
	.align	2
.L2466:
	.word	.LANCHOR31
	.word	.LANCHOR36
	.size	sblk_3d_tlc_dump_prog, .-sblk_3d_tlc_dump_prog
	.section	.text.flash_start_3d_mlc_page_prog,"ax",%progbits
	.align	1
	.global	flash_start_3d_mlc_page_prog
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	flash_start_3d_mlc_page_prog, %function
flash_start_3d_mlc_page_prog:
	@ args = 4, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r0, r1, r4, r5, r6, r7, r8, lr}
	mov	r5, r2
	ldr	r4, .L2471
	mov	r7, r0
	mov	r6, r1
	mov	r8, r3
	ldrb	r2, [r4]	@ zero_extendqisi2
	cmp	r2, r1
	bhi	.L2469
	movw	r2, #903
	ldr	r1, .L2471+4
	ldr	r0, .L2471+8
	bl	printf
.L2469:
	ldrb	r3, [r4]	@ zero_extendqisi2
	cmp	r3, r6
	bls	.L2468
	ldr	r3, .L2471+12
	ldrb	r6, [r3, r6]	@ zero_extendqisi2
	ldr	r3, .L2471+16
	mov	r0, r6
	ldr	r4, [r3]
	bl	nandc_cs
	movs	r3, #128
	mov	r0, r5
	add	r4, r4, r6, lsl #8
	str	r3, [r4, #2056]
	movs	r3, #0
	str	r3, [r4, #2052]
	str	r3, [r4, #2052]
	uxtb	r3, r5
	str	r3, [r4, #2052]
	lsrs	r3, r5, #8
	str	r3, [r4, #2052]
	lsrs	r3, r5, #16
	str	r3, [r4, #2052]
	bl	nandc_set_seed
	ldr	r3, .L2471+20
	movs	r1, #1
	mov	r0, r6
	ldrb	r2, [r3, #9]	@ zero_extendqisi2
	ldr	r3, [sp, #32]
	str	r3, [sp]
	mov	r3, r8
	bl	nandc_xfer
	str	r7, [r4, #2056]
.L2468:
	add	sp, sp, #8
	@ sp needed
	pop	{r4, r5, r6, r7, r8, pc}
.L2472:
	.align	2
.L2471:
	.word	.LANCHOR23
	.word	.LANCHOR176
	.word	.LC0
	.word	.LANCHOR29
	.word	.LANCHOR7
	.word	.LANCHOR32
	.size	flash_start_3d_mlc_page_prog, .-flash_start_3d_mlc_page_prog
	.section	.text.sblk_mlc_dump_prog,"ax",%progbits
	.align	1
	.global	sblk_mlc_dump_prog
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	sblk_mlc_dump_prog, %function
sblk_mlc_dump_prog:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	ldr	r3, .L2478
	push	{r0, r1, r4, r5, r6, lr}
	mov	r5, r0
	ldr	r2, [r0, #24]
	ldrb	r4, [r3]	@ zero_extendqisi2
	movs	r3, #1
	rsb	r1, r4, #24
	lsl	r6, r3, r1
	lsl	r4, r3, r4
	subs	r6, r6, #1
	subs	r4, r4, #1
	ands	r6, r6, r2
	lsrs	r2, r2, r1
	ands	r4, r4, r2
	uxtb	r4, r4
	mov	r0, r4
	bl	zftl_flash_exit_slc_mode
	ldr	r3, .L2478+4
	ldr	r3, [r3]
	lsls	r3, r3, #19
	bpl	.L2474
	ldr	r2, [r5, #24]
	mov	r1, r6
	ldr	r0, .L2478+8
	adds	r3, r2, #1
	bl	printf
.L2474:
	ldr	r3, [r5, #12]
	mov	r2, r6
	mov	r1, r4
	movs	r0, #16
	str	r3, [sp]
	ldr	r3, [r5, #4]
	bl	flash_start_3d_mlc_page_prog
	bl	nandc_wait_flash_ready
	ldr	r3, [r5, #12]
	adds	r2, r6, #1
	mov	r1, r4
	movs	r0, #16
	str	r3, [sp]
	ldr	r3, [r5, #4]
	bl	flash_start_3d_mlc_page_prog
	bl	nandc_wait_flash_ready
	movs	r1, #64
	ldr	r0, [r5, #24]
	bl	flash_wait_device_ready
	bl	nandc_de_cs.constprop.32
	add	sp, sp, #8
	@ sp needed
	pop	{r4, r5, r6, pc}
.L2479:
	.align	2
.L2478:
	.word	.LANCHOR31
	.word	.LANCHOR19
	.word	.LC135
	.size	sblk_mlc_dump_prog, .-sblk_mlc_dump_prog
	.section	.text.flash_start_page_prog,"ax",%progbits
	.align	1
	.global	flash_start_page_prog
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	flash_start_page_prog, %function
flash_start_page_prog:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r0, r1, r2, r3, r4, r5, r6, r7, r8, r10, fp, lr}
	mov	fp, r2
	str	r3, [sp, #12]
	mov	r8, r1
	ldr	r3, .L2494
	ldr	r6, .L2494+4
	str	r0, [sp, #8]
	ldrb	r2, [r3]	@ zero_extendqisi2
	movs	r3, #1
	rsb	r4, r2, #24
	lsls	r3, r3, r2
	lsr	r2, r1, r4
	subs	r3, r3, #1
	ands	r3, r3, r2
	ldrb	r2, [r6]	@ zero_extendqisi2
	uxtb	r10, r3
	cmp	r2, r10
	bhi	.L2481
	mov	r2, #956
	ldr	r1, .L2494+8
	ldr	r0, .L2494+12
	bl	printf
.L2481:
	ldrb	r2, [r6]	@ zero_extendqisi2
	cmp	r2, r10
	bls	.L2480
	movs	r2, #1
	lsl	r4, r2, r4
	ldr	r2, .L2494+16
	subs	r4, r4, #1
	ldrb	r5, [r2, r10]	@ zero_extendqisi2
	and	r4, r4, r8
	ldr	r2, .L2494+20
	ldr	r7, [r2]
	bl	nandc_rdy_status
	cbnz	r0, .L2483
	ldrb	r2, [r6]	@ zero_extendqisi2
	cmp	r2, #1
	bne	.L2484
	bl	nandc_wait_flash_ready
.L2483:
	mov	r0, r5
	bl	hynix_reconfig_rr_para
	mov	r0, r5
	bl	nandc_cs
	tst	r8, #50331648
	bne	.L2485
	mov	r0, r4
	bl	slc_phy_page_address_calc
	ldr	r3, .L2494+24
	mov	r4, r0
	ldrb	r3, [r3]	@ zero_extendqisi2
	cbz	r3, .L2486
	mov	r0, r5
	bl	zftl_flash_enter_slc_mode
.L2486:
	lsls	r6, r5, #8
	movs	r2, #128
	adds	r3, r7, r6
	str	r2, [r3, #2056]
	movs	r2, #0
	str	r2, [r3, #2052]
	str	r2, [r3, #2052]
	uxtb	r2, r4
	str	r2, [r3, #2052]
	lsrs	r2, r4, #8
	str	r2, [r3, #2052]
	lsrs	r2, r4, #16
	str	r2, [r3, #2052]
	ldr	r2, .L2494+28
	ldrb	r2, [r2]	@ zero_extendqisi2
	cbz	r2, .L2487
	lsrs	r2, r4, #24
	str	r2, [r3, #2052]
.L2487:
	mov	r0, r4
	add	r7, r7, r6
	bl	nandc_set_seed
	ldr	r3, .L2494+32
	movs	r1, #1
	mov	r0, r5
	ldrb	r2, [r3, #9]	@ zero_extendqisi2
	ldr	r3, [sp, #12]
	str	r3, [sp]
	mov	r3, fp
	bl	nandc_xfer
	ldr	r3, [sp, #8]
	str	r3, [r7, #2056]
	add	sp, sp, #16
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r10, fp, lr}
	b	nandc_de_cs.constprop.32
.L2484:
	movs	r2, #64
	mov	r1, r4
	mov	r0, r10
	bl	flash_wait_device_ready_raw
	b	.L2483
.L2485:
	mov	r0, r5
	bl	zftl_flash_exit_slc_mode
	b	.L2486
.L2480:
	add	sp, sp, #16
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r10, fp, pc}
.L2495:
	.align	2
.L2494:
	.word	.LANCHOR31
	.word	.LANCHOR23
	.word	.LANCHOR177
	.word	.LC0
	.word	.LANCHOR29
	.word	.LANCHOR7
	.word	.LANCHOR0
	.word	.LANCHOR30
	.word	.LANCHOR32
	.size	flash_start_page_prog, .-flash_start_page_prog
	.section	.text.queue_prog_cmd,"ax",%progbits
	.align	1
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	queue_prog_cmd, %function
queue_prog_cmd:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r3, r4, r5, r6, r7, lr}
	mov	r4, r0
	ldr	r3, [r0, #12]
	ldr	r2, [r0, #4]
	ldr	r1, [r0, #24]
	movs	r0, #16
	bl	flash_start_page_prog
	ldr	r3, .L2504
	ldr	r2, [r4, #24]
	ldrb	r0, [r3]	@ zero_extendqisi2
	cmp	r0, #255
	beq	.L2497
	ldr	r3, .L2504+4
	movs	r7, #48
	ldr	ip, .L2504+8
	ldrb	r1, [r3]	@ zero_extendqisi2
	movs	r3, #1
	mov	lr, ip
	rsb	r6, r1, #24
	lsls	r3, r3, r1
	asrs	r2, r2, r6
	subs	r3, r3, #1
	uxth	r3, r3
	ands	r2, r2, r3
.L2499:
	mla	r5, r7, r0, ip
	ldr	r1, [r5, #24]
	lsrs	r1, r1, r6
	ands	r1, r1, r3
	cmp	r2, r1
	bne	.L2498
	add	r1, r5, #42
	ldrb	r5, [r5, #42]	@ zero_extendqisi2
	cmp	r5, #7
	bne	.L2498
	movs	r3, #3
	strb	r3, [r1]
.L2497:
	movs	r3, #3
	mov	r1, r4
	strb	r3, [r4, #42]
	movs	r3, #1
	strb	r3, [r4, #43]
	movs	r3, #255
	strb	r3, [r4]
	ldr	r0, .L2504
	pop	{r3, r4, r5, r6, r7, lr}
	b	buf_add_tail
.L2498:
	muls	r0, r7, r0
	ldrb	r0, [lr, r0]	@ zero_extendqisi2
	cmp	r0, #255
	bne	.L2499
	b	.L2497
.L2505:
	.align	2
.L2504:
	.word	.LANCHOR59
	.word	.LANCHOR31
	.word	.LANCHOR55
	.size	queue_prog_cmd, .-queue_prog_cmd
	.section	.text.flash_complete_plane_page_read,"ax",%progbits
	.align	1
	.global	flash_complete_plane_page_read
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	flash_complete_plane_page_read, %function
flash_complete_plane_page_read:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	ldr	r3, .L2536
	push	{r0, r1, r2, r4, r5, r6, r7, r8, r10, lr}
	movs	r5, #1
	mov	r8, r2
	mov	r6, r0
	mov	r7, r1
	ldrb	r3, [r3]	@ zero_extendqisi2
	rsb	r4, r3, #24
	lsls	r5, r5, r3
	lsr	r3, r0, r4
	subs	r5, r5, #1
	ands	r5, r5, r3
	ldr	r3, .L2536+4
	uxtb	r5, r5
	ldrb	r2, [r3]	@ zero_extendqisi2
	mov	r10, r3
	cmp	r2, r5
	bhi	.L2507
	movw	r2, #1070
	ldr	r1, .L2536+8
	ldr	r0, .L2536+12
	bl	printf
.L2507:
	ldrb	r3, [r10]	@ zero_extendqisi2
	cmp	r3, r5
	bls	.L2518
	ldr	r3, .L2536+16
	movs	r0, #1
	lsl	r4, r0, r4
	ldrb	r10, [r3, r5]	@ zero_extendqisi2
	subs	r4, r4, #1
	ldr	r3, .L2536+20
	ands	r4, r4, r6
	ubfx	r6, r6, #24, #2
	mov	r0, r10
	ldr	r5, [r3]
	bl	nandc_cs
	cbnz	r6, .L2509
	mov	r0, r4
	bl	slc_phy_page_address_calc
	mov	r4, r0
.L2509:
	ldr	r3, .L2536+24
	uxtb	ip, r4
	lsrs	r0, r4, #8
	lsrs	r1, r4, #16
	ldrb	r3, [r3, #16]	@ zero_extendqisi2
	cmp	r3, #1
	lsl	r3, r10, #8
	bne	.L2510
	adds	r2, r5, r3
	mov	lr, #6
.L2535:
	str	lr, [r2, #2056]
	mov	lr, #0
	str	lr, [r2, #2052]
	str	lr, [r2, #2052]
	str	ip, [r2, #2052]
	str	r0, [r2, #2052]
	str	r1, [r2, #2052]
	ldr	r1, .L2536+28
	ldrb	r1, [r1]	@ zero_extendqisi2
	cbz	r1, .L2514
	lsrs	r1, r4, #24
	str	r1, [r2, #2052]
.L2514:
	add	r3, r3, r5
.L2531:
	movs	r2, #224
	str	r2, [r3, #2056]
	ldr	r3, .L2536+32
	ldr	r3, [r3]
	ldrb	r3, [r3, #12]	@ zero_extendqisi2
	cmp	r3, #3
	bne	.L2516
	cmp	r6, #0
	beq	.L2516
	ldr	r3, .L2536+36
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L2516
	ldr	r3, .L2536+40
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L2516
	add	r4, r4, r4, lsl #1
	subs	r6, r6, #1
	adds	r0, r4, r6
.L2532:
	bl	nandc_set_seed
	ldr	r3, .L2536+44
	movs	r1, #0
	mov	r0, r10
	ldrb	r2, [r3, #9]	@ zero_extendqisi2
	mov	r3, r7
	str	r8, [sp]
	bl	nandc_xfer
	bl	nandc_de_cs.constprop.32
.L2506:
	add	sp, sp, #12
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r10, pc}
.L2510:
	ldr	r2, .L2536+32
	ldr	r2, [r2]
	ldrb	r2, [r2, #12]	@ zero_extendqisi2
	cmp	r2, #3
	add	r2, r5, r3
	bne	.L2513
	mov	lr, #5
	b	.L2535
.L2513:
	mov	lr, #0
	str	lr, [r2, #2056]
	str	lr, [r2, #2052]
	str	lr, [r2, #2052]
	str	ip, [r2, #2052]
	str	r0, [r2, #2052]
	str	r1, [r2, #2052]
	ldr	r1, .L2536+28
	ldrb	r1, [r1]	@ zero_extendqisi2
	cbz	r1, .L2515
	lsrs	r1, r4, #24
	str	r1, [r2, #2052]
.L2515:
	movs	r1, #5
	add	r3, r3, r5
	str	r1, [r3, #2056]
	movs	r1, #0
	str	r1, [r2, #2052]
	str	r1, [r2, #2052]
	b	.L2531
.L2516:
	mov	r0, r4
	b	.L2532
.L2518:
	mov	r0, #-1
	b	.L2506
.L2537:
	.align	2
.L2536:
	.word	.LANCHOR31
	.word	.LANCHOR23
	.word	.LANCHOR178
	.word	.LC0
	.word	.LANCHOR29
	.word	.LANCHOR7
	.word	.LANCHOR25
	.word	.LANCHOR30
	.word	.LANCHOR21
	.word	.LANCHOR35
	.word	.LANCHOR36
	.word	.LANCHOR32
	.size	flash_complete_plane_page_read, .-flash_complete_plane_page_read
	.section	.text.flash_complete_page_read,"ax",%progbits
	.align	1
	.global	flash_complete_page_read
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	flash_complete_page_read, %function
flash_complete_page_read:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r0, r1, r2, r3, r4, r5, r6, r7, r8, r10, fp, lr}
	mov	fp, r0
	ldr	r3, .L2569
	mov	r10, r1
	ubfx	r5, r0, #24, #2
	str	r2, [sp, #8]
	ldrb	r6, [r3]	@ zero_extendqisi2
	movs	r3, #1
	rsb	r2, r6, #24
	lsl	r4, r3, r2
	lsl	r6, r3, r6
	ldr	r3, .L2569+4
	lsr	r2, r0, r2
	subs	r6, r6, #1
	ands	r6, r6, r2
	subs	r4, r4, #1
	ldrb	r3, [r3]	@ zero_extendqisi2
	uxtb	r6, r6
	ands	r4, r4, r0
	cmp	r3, r6
	bhi	.L2539
	mov	r2, #1232
	ldr	r1, .L2569+8
	ldr	r0, .L2569+12
	bl	printf
.L2539:
	ldr	r3, .L2569+16
	ldrb	r8, [r3, r6]	@ zero_extendqisi2
	ldr	r3, .L2569+20
	mov	r0, r8
	ldr	r6, [r3]
	bl	nandc_cs
	cbnz	r5, .L2540
	mov	r0, r4
	bl	slc_phy_page_address_calc
	mov	r4, r0
.L2540:
	ldr	r7, .L2569+24
	ldrb	r3, [r7, #12]	@ zero_extendqisi2
	cmp	r3, #3
	bne	.L2541
	add	r6, r6, r8, lsl #8
	movs	r3, #5
	str	r3, [r6, #2056]
	movs	r3, #0
	str	r3, [r6, #2052]
	str	r3, [r6, #2052]
	uxtb	r3, r4
	str	r3, [r6, #2052]
	lsrs	r3, r4, #8
	str	r3, [r6, #2052]
	lsrs	r3, r4, #16
	str	r3, [r6, #2052]
	movs	r3, #224
	str	r3, [r6, #2056]
.L2541:
	ldr	r3, .L2569+28
	ldr	r3, [r3]
	ldrb	r3, [r3, #12]	@ zero_extendqisi2
	cmp	r3, #3
	bne	.L2542
	cmp	r5, #0
	beq	.L2542
	ldr	r3, .L2569+32
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L2542
	ldr	r3, .L2569+36
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L2542
	add	r3, r4, r4, lsl #1
	subs	r0, r5, #1
	add	r0, r0, r3
.L2568:
	bl	nandc_set_seed
	ldr	r3, [sp, #8]
	movs	r1, #0
	ldrb	r2, [r7, #9]	@ zero_extendqisi2
	mov	r0, r8
	str	r3, [sp]
	mov	r3, r10
	bl	nandc_xfer
	adds	r1, r0, #1
	bne	.L2544
	ldr	r6, .L2569+40
	ldrb	r3, [r6]	@ zero_extendqisi2
	str	r3, [sp, #12]
	cmp	r3, #0
	beq	.L2545
	movs	r3, #0
	mov	r2, r10
	strb	r3, [r6]
	orr	r1, r4, r5, lsl #24
	ldrb	r3, [r7, #9]	@ zero_extendqisi2
	mov	r0, r8
	str	r3, [sp]
	ldr	r3, [sp, #8]
	bl	flash_read_page
	ldrb	r3, [sp, #12]	@ zero_extendqisi2
	strb	r3, [r6]
	cbnz	r5, .L2546
.L2551:
	ldr	r3, .L2569+44
	ldrb	r3, [r3]	@ zero_extendqisi2
	cbz	r3, .L2546
	ldr	r3, .L2569+48
	ldrb	r3, [r3]	@ zero_extendqisi2
	add	r3, r3, r3, lsl #1
	cmp	r0, r3, asr #2
	blt	.L2546
	ldrb	r3, [r7, #19]	@ zero_extendqisi2
	subs	r3, r3, #4
	cmp	r3, #4
	it	ls
	movls	r0, #256
.L2538:
	add	sp, sp, #16
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r10, fp, pc}
.L2542:
	mov	r0, r4
	b	.L2568
.L2546:
	adds	r2, r0, #1
	bne	.L2538
.L2552:
	ldr	r3, .L2569+52
	ldr	r6, [r3]
	cbnz	r6, .L2548
.L2550:
	ldr	r3, .L2569+40
	mov	r2, fp
	movs	r1, #0
	ldr	r0, .L2569+56
	ldrb	r3, [r3]	@ zero_extendqisi2
	str	r3, [sp]
	mov	r3, #-1
	bl	printf
	ldr	r3, .L2569+60
	ldrb	r3, [r3]	@ zero_extendqisi2
	cbnz	r3, .L2549
	mov	r0, #-1
	b	.L2538
.L2548:
	ldrb	r3, [r7, #9]	@ zero_extendqisi2
	mov	r2, r10
	orr	r1, r4, r5, lsl #24
	mov	r0, r8
	str	r3, [sp]
	ldr	r3, [sp, #8]
	blx	r6
	adds	r3, r0, #1
	beq	.L2550
	b	.L2538
.L2549:
	ldrb	r3, [r7, #9]	@ zero_extendqisi2
	mov	r2, r10
	orr	r1, r4, r5, lsl #24
	mov	r0, r8
	str	r3, [sp]
	ldr	r3, [sp, #8]
	bl	flash_ddr_tuning_read
	b	.L2538
.L2545:
	cmp	r5, #0
	beq	.L2551
	b	.L2552
.L2544:
	cmp	r5, #0
	bne	.L2538
	b	.L2551
.L2570:
	.align	2
.L2569:
	.word	.LANCHOR31
	.word	.LANCHOR23
	.word	.LANCHOR179
	.word	.LC0
	.word	.LANCHOR29
	.word	.LANCHOR7
	.word	.LANCHOR32
	.word	.LANCHOR21
	.word	.LANCHOR35
	.word	.LANCHOR36
	.word	.LANCHOR51
	.word	.LANCHOR0
	.word	.LANCHOR49
	.word	.LANCHOR171
	.word	.LC136
	.word	.LANCHOR26
	.size	flash_complete_page_read, .-flash_complete_page_read
	.section	.text.queue_wait_first_req_completed,"ax",%progbits
	.align	1
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	queue_wait_first_req_completed, %function
queue_wait_first_req_completed:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r0, r1, r2, r3, r4, r5, r6, r7, r8, r10, fp, lr}
	ldr	r3, .L2664
	ldrb	r5, [r3]	@ zero_extendqisi2
	cmp	r5, #255
	bne	.L2572
.L2605:
	movs	r6, #0
	b	.L2571
.L2572:
	ldr	r4, .L2664+4
	movs	r7, #48
	mla	r2, r7, r5, r4
	ldrb	r3, [r2, #42]	@ zero_extendqisi2
	ldr	r6, [r2, #24]
	subs	r2, r3, #1
	cmp	r2, #10
	bhi	.L2605
	tbh	[pc, r2, lsl #1]
.L2575:
	.2byte	(.L2574-.L2575)/2
	.2byte	(.L2576-.L2575)/2
	.2byte	(.L2577-.L2575)/2
	.2byte	(.L2577-.L2575)/2
	.2byte	(.L2577-.L2575)/2
	.2byte	(.L2577-.L2575)/2
	.2byte	(.L2578-.L2575)/2
	.2byte	(.L2579-.L2575)/2
	.2byte	(.L2580-.L2575)/2
	.2byte	(.L2577-.L2575)/2
	.2byte	(.L2580-.L2575)/2
	.p2align 1
.L2574:
	mla	r7, r7, r5, r4
	bl	nandc_wait_flash_ready
	ldr	r3, [r7, #8]
	ldr	r1, [r7, #4]
	cbz	r3, .L2581
	ldr	r2, .L2664+8
	ldrb	r0, [r7, #40]	@ zero_extendqisi2
	ldrb	r2, [r2]	@ zero_extendqisi2
	cmp	r0, r2
	it	eq
	moveq	r1, r3
.L2581:
	movs	r3, #48
	mov	r0, r6
	mla	r4, r3, r5, r4
	ldr	r2, [r4, #12]
	bl	flash_complete_page_read
	str	r0, [r4, #36]
.L2663:
	movs	r3, #13
	strb	r3, [r4, #42]
	ldrb	r3, [r4, #2]	@ zero_extendqisi2
	orr	r3, r3, #8
	strb	r3, [r4, #2]
	b	.L2605
.L2576:
	bl	nandc_wait_flash_ready
	mul	r2, r7, r5
	ldrb	r6, [r4, r2]	@ zero_extendqisi2
	adds	r3, r4, r2
	ldr	r2, [r3, #8]
	ldr	fp, [r3, #4]
	mla	r7, r7, r6, r4
	ldr	r10, [r7, #4]
	cbz	r2, .L2582
	ldrb	r1, [r3, #40]	@ zero_extendqisi2
	ldr	r3, .L2664+8
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r1, r3
	it	eq
	moveq	fp, r2
.L2582:
	movs	r3, #48
	mla	r3, r3, r6, r4
	ldr	r2, [r3, #8]
	cbz	r2, .L2583
	ldrb	r1, [r3, #40]	@ zero_extendqisi2
	ldr	r3, .L2664+8
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r1, r3
	it	eq
	moveq	r10, r2
.L2583:
	movs	r3, #48
	mov	r1, fp
	mla	r7, r3, r5, r4
	str	r3, [sp, #12]
	ldr	r2, [r7, #12]
	ldr	r0, [r7, #24]
	bl	flash_complete_plane_page_read
	ldr	r3, [sp, #12]
	mov	r8, r0
	mov	r1, r10
	mla	r3, r3, r6, r4
	ldr	r2, [r3, #12]
	ldr	r0, [r3, #24]
	bl	flash_complete_plane_page_read
	cmp	r8, #-1
	str	r0, [sp, #12]
	beq	.L2584
	ldr	r3, [r7, #20]
	adds	r2, r3, #1
	beq	.L2585
	ldr	r2, [r7, #12]
	ldr	r2, [r2, #4]
	cmp	r3, r2
	beq	.L2585
.L2584:
	movs	r7, #48
	ldr	r3, .L2664+12
	mla	r7, r7, r5, r4
	ldrb	r3, [r3]	@ zero_extendqisi2
	movs	r0, #1
	ldr	r1, [r7, #24]
	rsb	r2, r3, #24
	lsls	r0, r0, r3
	subs	r3, r0, #1
	lsr	r0, r1, r2
	lsl	ip, r3, r2
	mov	r2, fp
	ands	r0, r0, r3
	ldr	r3, .L2664+8
	bic	r1, r1, ip
	uxtb	r0, r0
	ldrb	r3, [r3]	@ zero_extendqisi2
	str	r3, [sp]
	ldr	r3, [r7, #12]
	bl	flash_read_page_en
	ldr	r2, [r7, #20]
	mov	r8, r0
	adds	r3, r2, #1
	beq	.L2586
	ldr	r3, [r7, #12]
	ldr	r1, [r3, #4]
	cmp	r2, r1
	beq	.L2586
	ldr	r0, .L2664+16
	ldr	r0, [r0]
	lsls	r0, r0, #25
	bpl	.L2586
	str	r1, [sp]
	ldr	r1, [r7, #24]
	ldr	r3, [r3]
	ldr	r0, .L2664+20
	bl	printf
.L2586:
	movs	r3, #48
	mla	r3, r3, r5, r4
	ldr	r2, [r3, #20]
	adds	r0, r2, #1
	beq	.L2585
	ldr	r3, [r3, #12]
	ldr	r3, [r3, #4]
	cmp	r2, r3
	beq	.L2585
	movw	r2, #431
	ldr	r1, .L2664+24
	ldr	r0, .L2664+28
	bl	printf
.L2585:
	movs	r3, #48
	movs	r2, #13
	mla	r5, r3, r5, r4
	strb	r2, [r5, #42]
	ldrb	r2, [r5, #2]	@ zero_extendqisi2
	str	r8, [r5, #36]
	orr	r2, r2, #8
	strb	r2, [r5, #2]
	ldr	r2, [sp, #12]
	adds	r2, r2, #1
	beq	.L2587
	mla	r3, r3, r6, r4
	ldr	r2, [r3, #20]
	adds	r1, r2, #1
	beq	.L2589
	ldr	r3, [r3, #12]
	ldr	r3, [r3, #4]
	cmp	r2, r3
	beq	.L2589
.L2587:
	ldr	r3, .L2664+12
	movs	r5, #48
	mla	r5, r5, r6, r4
	ldrb	r2, [r3]	@ zero_extendqisi2
	movs	r0, #1
	ldr	r1, [r5, #24]
	rsb	r3, r2, #24
	lsls	r0, r0, r2
	mov	r2, r10
	subs	r0, r0, #1
	lsl	r7, r0, r3
	lsr	r3, r1, r3
	ands	r0, r0, r3
	ldr	r3, .L2664+8
	bic	r1, r1, r7
	uxtb	r0, r0
	ldrb	r3, [r3]	@ zero_extendqisi2
	str	r3, [sp]
	ldr	r3, [r5, #12]
	bl	flash_read_page_en
	ldr	r2, [r5, #20]
	adds	r3, r2, #1
	beq	.L2591
	ldr	r3, [r5, #12]
	ldr	r1, [r3, #4]
	cmp	r2, r1
	beq	.L2591
	ldr	r0, .L2664+16
	ldr	r0, [r0]
	lsls	r7, r0, #25
	bpl	.L2591
	str	r1, [sp]
	ldr	r0, .L2664+20
	ldr	r3, [r3]
	ldr	r1, [r5, #24]
	bl	printf
.L2591:
	movs	r3, #48
	mla	r3, r3, r6, r4
	ldr	r2, [r3, #20]
	adds	r0, r2, #1
	beq	.L2589
	ldr	r3, [r3, #12]
	ldr	r3, [r3, #4]
	cmp	r2, r3
	beq	.L2589
	mov	r2, #450
	ldr	r1, .L2664+24
	ldr	r0, .L2664+28
	bl	printf
.L2589:
	movs	r3, #48
	mla	r4, r3, r6, r4
	str	r8, [r4, #36]
	b	.L2663
.L2577:
	movs	r1, #64
	mov	r0, r6
	bl	flash_wait_device_ready
	lsls	r1, r0, #25
	mov	r6, r0
	bpl	.L2605
	ands	r2, r0, #5
	mov	r3, #48
	beq	.L2593
	mla	r4, r3, r5, r4
	movs	r3, #12
	mov	r2, r0
	ldr	r0, .L2664+32
	strb	r3, [r4, #42]
	ldrb	r1, [r4, #1]	@ zero_extendqisi2
	str	r3, [sp]
	ldr	r3, [r4, #24]
	bl	printf
.L2662:
	mov	r3, #-1
	str	r3, [r4, #36]
	b	.L2571
.L2665:
	.align	2
.L2664:
	.word	.LANCHOR59
	.word	.LANCHOR55
	.word	.LANCHOR131
	.word	.LANCHOR31
	.word	.LANCHOR19
	.word	.LC137
	.word	.LANCHOR180
	.word	.LC0
	.word	.LC138
.L2593:
	mla	r6, r3, r5, r4
	movs	r3, #13
	strb	r3, [r6, #42]
	ldr	r3, .L2666
	str	r2, [r6, #36]
	ldr	r3, [r3]
	ldr	r2, [r3, #156]
	ldr	r3, .L2666+4
	cmp	r2, r3
	bne	.L2605
	ldrh	r3, [r6, #34]
	cmp	r3, #0
	bne	.L2605
	ldr	r3, .L2666+8
	movs	r0, #1
	ldr	r1, [r6, #24]
	ldr	r7, .L2666+12
	ldrb	r2, [r3]	@ zero_extendqisi2
	rsb	r3, r2, #24
	lsls	r0, r0, r2
	ldr	r2, .L2666+16
	subs	r0, r0, #1
	lsl	ip, r0, r3
	lsr	r3, r1, r3
	ands	r0, r0, r3
	ldr	r3, .L2666+20
	bic	r1, r1, ip
	uxtb	r0, r0
	ldrb	r3, [r3]	@ zero_extendqisi2
	str	r3, [sp]
	ldr	r3, [r7]
	ldr	r2, [r2]
	bl	flash_read_page_en
	adds	r2, r0, #1
	mov	r3, r0
	beq	.L2594
	ldr	r1, [r6, #12]
	ldr	r2, [r7]
	ldr	r1, [r1]
	ldr	r2, [r2]
	cmp	r1, r2
	beq	.L2605
.L2594:
	movs	r2, #48
	ldr	r0, .L2666+24
	mla	r4, r2, r5, r4
	ldr	r2, .L2666+28
	ldrb	r2, [r2]	@ zero_extendqisi2
	ldrb	r1, [r4, #1]	@ zero_extendqisi2
	str	r2, [sp]
	ldr	r2, [r4, #24]
	bl	printf
	mov	r3, #-1
	str	r3, [r4, #36]
	b	.L2605
.L2580:
	ldr	r7, .L2666+8
	cmp	r3, #11
	mov	r3, #1
	add	r2, r5, r5, lsl #1
	it	eq
	moveq	r0, #10
	ldrb	ip, [r7]	@ zero_extendqisi2
	add	r2, r4, r2, lsl #4
	mov	r10, r7
	it	ne
	movne	r0, #3
	movs	r7, #48
	rsb	r1, ip, #24
	lsl	r3, r3, ip
	lsr	ip, r6, r1
	subs	r3, r3, #1
	and	ip, ip, r3
	uxth	ip, ip
.L2596:
	ldrb	r8, [r2]	@ zero_extendqisi2
	cmp	r8, #255
	bne	.L2603
	mov	r6, #-1
	b	.L2571
.L2603:
	mla	lr, r7, r8, r4
	add	r2, r8, r8, lsl #1
	ldrb	fp, [lr, #42]	@ zero_extendqisi2
	add	r2, r4, r2, lsl #4
	cmp	fp, r0
	bne	.L2596
	ldr	lr, [lr, #24]
	lsr	lr, lr, r1
	and	lr, lr, r3
	cmp	ip, lr
	bne	.L2596
	mov	r0, r6
	movs	r1, #64
	bl	flash_wait_device_ready
	mov	r6, r0
	lsls	r0, r6, #25
	bmi	.L2598
.L2661:
	movs	r6, #0
	b	.L2599
.L2598:
	ands	r3, r6, #15
	mul	r7, r7, r5
	beq	.L2600
	add	r7, r7, r4
	mov	r10, #12
	ldrb	r1, [r7, #1]	@ zero_extendqisi2
	mov	r2, r6
	str	r10, [sp]
	ldr	r3, [r7, #24]
	ldr	r0, .L2666+32
	bl	printf
	mov	r3, #-1
	strb	r10, [r7, #42]
	str	r3, [r7, #36]
.L2599:
	movs	r3, #48
	mla	r5, r3, r5, r4
	mla	r8, r3, r8, r4
	ldrb	r2, [r5, #42]	@ zero_extendqisi2
	ldr	r3, [r5, #36]
	strb	r2, [r8, #42]
	str	r3, [r8, #36]
.L2571:
	mov	r0, r6
	add	sp, sp, #16
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r10, fp, pc}
.L2600:
	adds	r6, r4, r7
	movs	r2, #13
	str	r3, [r6, #36]
	ldr	r3, .L2666
	strb	r2, [r6, #42]
	ldr	r3, [r3]
	ldr	r2, [r3, #156]
	ldr	r3, .L2666+4
	cmp	r2, r3
	bne	.L2661
	ldrh	r3, [r6, #34]
	cmp	r3, #0
	bne	.L2661
	ldrb	r2, [r10]	@ zero_extendqisi2
	movs	r0, #1
	ldr	r1, [r6, #24]
	ldr	r7, .L2666+12
	rsb	r3, r2, #24
	lsls	r0, r0, r2
	ldr	r2, .L2666+16
	subs	r0, r0, #1
	lsl	ip, r0, r3
	lsr	r3, r1, r3
	ands	r0, r0, r3
	ldr	r3, .L2666+20
	bic	r1, r1, ip
	uxtb	r0, r0
	ldrb	r3, [r3]	@ zero_extendqisi2
	str	r3, [sp]
	ldr	r3, [r7]
	ldr	r2, [r2]
	bl	flash_read_page_en
	adds	r1, r0, #1
	mov	r3, r0
	beq	.L2602
	ldr	r1, [r6, #12]
	ldr	r2, [r7]
	ldr	r1, [r1]
	ldr	r2, [r2]
	cmp	r1, r2
	beq	.L2661
.L2602:
	ldr	r2, .L2666+28
	movs	r6, #48
	mla	r6, r6, r5, r4
	ldr	r0, .L2666+36
	ldrb	r2, [r2]	@ zero_extendqisi2
	ldrb	r1, [r6, #1]	@ zero_extendqisi2
	str	r2, [sp]
	ldr	r2, [r6, #24]
	bl	printf
	mov	r3, #-1
	str	r3, [r6, #36]
	b	.L2661
.L2578:
	mov	r0, r6
	movs	r1, #32
	bl	flash_wait_device_ready
	lsls	r2, r0, #26
	mov	r6, r0
	bpl	.L2605
	ands	r2, r0, #15
	mov	r3, #48
	mla	r4, r3, r5, r4
	beq	.L2604
	movs	r3, #12
	strb	r3, [r4, #42]
	b	.L2662
.L2604:
	movs	r3, #13
	str	r2, [r4, #36]
	strb	r3, [r4, #42]
	b	.L2605
.L2579:
	movs	r1, #64
	mov	r0, r6
	bl	flash_wait_device_ready
	lsls	r3, r0, #25
	bpl	.L2605
	movs	r3, #48
	mla	r4, r3, r5, r4
	movs	r3, #7
	str	r0, [r4, #36]
	strb	r3, [r4, #42]
	b	.L2605
.L2667:
	.align	2
.L2666:
	.word	.LANCHOR110
	.word	1145785929
	.word	.LANCHOR31
	.word	.LANCHOR172
	.word	.LANCHOR173
	.word	.LANCHOR131
	.word	.LC139
	.word	.LANCHOR51
	.word	.LC140
	.word	.LC141
	.size	queue_wait_first_req_completed, .-queue_wait_first_req_completed
	.section	.text.sblk_prog_page,"ax",%progbits
	.align	1
	.global	sblk_prog_page
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	sblk_prog_page, %function
sblk_prog_page:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 0, uses_anonymous_args = 0
	ldrh	r3, [r0, #34]
	push	{r0, r1, r4, r5, r6, r7, r8, r10, fp, lr}
	mov	r4, r0
	mov	r5, r1
	cbz	r3, .L2669
	ldr	r3, .L2698
	ldr	r3, [r3]
	lsls	r3, r3, #23
	bpl	.L2669
	mov	r2, r1
	ldr	r1, [r0, #24]
	ldr	r0, .L2698+4
	bl	printf
.L2669:
	ldr	fp, .L2698+40
	movs	r7, #0
.L2670:
	cbnz	r5, .L2681
.L2697:
	movs	r0, #0
	add	sp, sp, #8
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r10, fp, pc}
.L2681:
	ldrb	r8, [r4]	@ zero_extendqisi2
	ldr	r6, [r4, #24]
.L2671:
	movs	r1, #1
	mov	r0, r6
	bl	queue_lun_state
	cbnz	r0, .L2672
	cmp	r5, #1
	beq	.L2673
	ldr	r3, .L2698+8
	ldrb	r3, [r3]	@ zero_extendqisi2
	cbz	r3, .L2673
	ldr	r3, .L2698+12
	ldrb	r3, [r3]	@ zero_extendqisi2
	cbz	r3, .L2674
.L2673:
	mov	r0, r4
	bl	queue_prog_cmd
.L2675:
	subs	r5, r5, #1
	beq	.L2697
	ldr	r4, .L2698+16
	add	r8, r8, r8, lsl #1
	add	r4, r4, r8, lsl #4
	b	.L2670
.L2672:
	bl	queue_wait_first_req_completed
	bl	queue_remove_completed_req
	b	.L2671
.L2674:
	ldrb	r1, [fp]	@ zero_extendqisi2
	movs	r2, #1
	rsb	r3, r1, #24
	lsls	r2, r2, r1
	lsr	r3, r6, r3
	subs	r2, r2, #1
	ands	r3, r3, r2
	uxth	r3, r3
	str	r3, [sp, #4]
	ldrb	r3, [r4]	@ zero_extendqisi2
	cmp	r3, #255
	bne	.L2676
	movw	r2, #697
	ldr	r1, .L2698+20
	ldr	r0, .L2698+24
	bl	printf
.L2676:
	ldr	r2, .L2698+16
	movs	r1, #48
	ldrb	r3, [r4]	@ zero_extendqisi2
	mov	r10, #1
	mla	r3, r1, r3, r2
	ldr	r1, [r3, #24]
	ldrb	r3, [fp]	@ zero_extendqisi2
	rsb	r2, r3, #24
	lsl	r3, r10, r3
	lsr	r0, r1, r2
	subs	r3, r3, #1
	ands	r3, r3, r0
	ldr	r0, [sp, #4]
	uxth	r3, r3
	cmp	r0, r3
	bne	.L2677
	ldr	r3, .L2698+28
	ldrh	r0, [r3]
	ldr	r3, .L2698+32
	ldrb	ip, [r3]	@ zero_extendqisi2
	subs	r3, r2, r0
	lsl	r2, r10, r0
	lsl	r3, r10, r3
	subs	r2, r2, #1
	subs	r3, r3, #1
	uxth	r2, r2
	add	ip, ip, #-1
	and	r3, r3, ip
	uxth	r3, r3
	and	lr, r2, r6
	ands	r2, r2, r1
	lsrs	r6, r6, r0
	lsrs	r1, r1, r0
	ands	r6, r6, r3
	ands	r1, r1, r3
	cmp	r6, r1
	beq	.L2677
	cmp	lr, r2
	bne	.L2677
	cmp	r7, ip
	beq	.L2677
	ldr	r3, [r4, #12]
	movs	r0, #17
	ldr	r2, [r4, #4]
	add	r7, r7, r10
	ldr	r1, [r4, #24]
	bl	flash_start_page_prog
	movs	r3, #9
	strb	r10, [r4, #43]
	strb	r3, [r4, #42]
	movs	r3, #255
	strb	r3, [r4]
	mov	r1, r4
	ldr	r0, .L2698+36
	bl	buf_add_tail
	b	.L2675
.L2677:
	mov	r0, r4
	movs	r7, #0
	bl	queue_prog_cmd
	b	.L2675
.L2699:
	.align	2
.L2698:
	.word	.LANCHOR19
	.word	.LC142
	.word	.LANCHOR44
	.word	.LANCHOR36
	.word	.LANCHOR55
	.word	.LANCHOR181
	.word	.LC0
	.word	.LANCHOR74
	.word	.LANCHOR75
	.word	.LANCHOR59
	.word	.LANCHOR31
	.size	sblk_prog_page, .-sblk_prog_page
	.section	.text.sblk_wait_write_queue_completed,"ax",%progbits
	.align	1
	.global	sblk_wait_write_queue_completed
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	sblk_wait_write_queue_completed, %function
sblk_wait_write_queue_completed:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, lr}
	ldr	r4, .L2703
.L2701:
	ldrb	r3, [r4]	@ zero_extendqisi2
	cmp	r3, #255
	bne	.L2702
	pop	{r4, pc}
.L2702:
	bl	queue_wait_first_req_completed
	bl	queue_remove_completed_req
	b	.L2701
.L2704:
	.align	2
.L2703:
	.word	.LANCHOR59
	.size	sblk_wait_write_queue_completed, .-sblk_wait_write_queue_completed
	.section	.text.ftl_flush,"ax",%progbits
	.align	1
	.global	ftl_flush
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	ftl_flush, %function
ftl_flush:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r3, r4, r5, lr}
	ldr	r4, .L2710
	ldr	r5, .L2710+4
	ldrb	r1, [r4]	@ zero_extendqisi2
	cbz	r1, .L2706
	ldrb	r0, [r5]	@ zero_extendqisi2
	ldr	r3, .L2710+8
	add	r0, r0, r0, lsl #1
	add	r0, r3, r0, lsl #4
	bl	sblk_prog_page
.L2706:
	movs	r3, #255
	strb	r3, [r5]
	movs	r3, #0
	strb	r3, [r4]
	bl	sblk_wait_write_queue_completed
	bl	ftl_write_completed
	movw	r0, #65535
	pop	{r3, r4, r5, lr}
	b	ftl_vpn_decrement
.L2711:
	.align	2
.L2710:
	.word	.LANCHOR129
	.word	.LANCHOR182
	.word	.LANCHOR55
	.size	ftl_flush, .-ftl_flush
	.section	.text.ftl_read_page,"ax",%progbits
	.align	1
	.global	ftl_read_page
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	ftl_read_page, %function
ftl_read_page:
	@ args = 4, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, r8, lr}
	mov	r4, r0
	ldr	r8, [sp, #24]
	mov	r5, r1
	mov	r6, r2
	mov	r7, r3
	bl	sblk_wait_write_queue_completed
	str	r8, [sp, #24]
	mov	r3, r7
	mov	r2, r6
	mov	r1, r5
	mov	r0, r4
	pop	{r4, r5, r6, r7, r8, lr}
	b	flash_read_page_en
	.size	ftl_read_page, .-ftl_read_page
	.section	.text.ftl_read_ppa_page,"ax",%progbits
	.align	1
	.global	ftl_read_ppa_page
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	ftl_read_ppa_page, %function
ftl_read_ppa_page:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r0, r1, r2, r4, r5, r6, r7, r8, r10, lr}
	mov	r10, r3
	ldr	r3, .L2714
	mov	r6, r0
	movs	r5, #1
	mov	r7, r1
	mov	r8, r2
	ldrb	r0, [r3]	@ zero_extendqisi2
	rsb	r4, r0, #24
	lsls	r5, r5, r0
	lsr	r4, r6, r4
	subs	r5, r5, #1
	ands	r4, r4, r5
	uxtb	r4, r4
	bl	sblk_wait_write_queue_completed
	str	r10, [sp]
	mov	r3, r8
	mov	r2, r7
	mov	r1, r6
	mov	r0, r4
	bl	flash_read_page_en
	add	sp, sp, #12
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r10, pc}
.L2715:
	.align	2
.L2714:
	.word	.LANCHOR31
	.size	ftl_read_ppa_page, .-ftl_read_ppa_page
	.section	.text.sblk_read_page,"ax",%progbits
	.align	1
	.global	sblk_read_page
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	sblk_read_page, %function
sblk_read_page:
	@ args = 0, pretend = 0, frame = 24
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, r8, r10, fp, lr}
	mov	r7, r0
	sub	sp, sp, #24
	mov	r6, r1
	mov	r4, r0
	mov	r5, r1
.L2717:
	cbnz	r5, .L2727
.L2740:
	ldr	r4, .L2741
.L2728:
	cmp	r6, #0
	bne	.L2730
	mov	r0, r6
	add	sp, sp, #24
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r10, fp, pc}
.L2727:
	ldr	fp, [r4, #24]
	ldrb	r3, [r4]	@ zero_extendqisi2
	str	r3, [sp, #8]
.L2718:
	movs	r1, #0
	mov	r0, fp
	bl	queue_lun_state
	cbnz	r0, .L2719
	cmp	r5, #1
	beq	.L2724
	ldr	r3, .L2741+4
	ldrb	r3, [r3]	@ zero_extendqisi2
	cbnz	r3, .L2721
.L2724:
	mov	r0, r4
	bl	queue_read_cmd
	b	.L2722
.L2719:
	bl	queue_wait_first_req_completed
	bl	queue_remove_completed_req
	b	.L2718
.L2721:
	ldr	r3, .L2741+8
	movs	r2, #1
	ldrb	r1, [r3]	@ zero_extendqisi2
	rsb	r3, r1, #24
	lsls	r2, r2, r1
	lsr	r3, fp, r3
	subs	r2, r2, #1
	ands	r3, r3, r2
	ldrb	r2, [r4]	@ zero_extendqisi2
	uxth	r3, r3
	cmp	r2, #255
	bne	.L2723
	movw	r2, #782
	ldr	r1, .L2741+12
	ldr	r0, .L2741+16
	str	r3, [sp, #4]
	bl	printf
	ldr	r3, [sp, #4]
.L2723:
	ldrb	r2, [r4]	@ zero_extendqisi2
	movs	r0, #1
	ldr	r8, .L2741
	str	r2, [sp, #12]
	movs	r2, #48
	ldr	r1, [sp, #12]
	muls	r2, r1, r2
	add	r10, r8, r2
	str	r2, [sp, #4]
	ldr	r2, .L2741+8
	ldr	r1, [r10, #24]
	ldrb	ip, [r2]	@ zero_extendqisi2
	rsb	r2, ip, #24
	lsl	r0, r0, ip
	lsr	r2, r1, r2
	subs	r0, r0, #1
	ands	r2, r2, r0
	uxth	r2, r2
	cmp	r3, r2
	bne	.L2724
	ldr	r3, .L2741+20
	ldrh	r3, [r3]
	add	fp, fp, r3
	cmp	r1, fp
	bne	.L2724
	ldr	r3, [sp, #4]
	mov	fp, #255
	ldr	r0, [r4, #24]
	subs	r5, r5, #1
	ldrb	r3, [r8, r3]	@ zero_extendqisi2
	str	r3, [sp, #8]
	bl	flash_start_plane_read
	movs	r2, #2
	movs	r3, #0
	strb	r2, [r4, #42]
	mov	r1, r4
	strb	r3, [r4, #43]
	ldr	r0, .L2741+24
	strb	fp, [r4]
	str	r2, [sp, #20]
	str	r3, [sp, #16]
	bl	buf_add_tail
	ldr	r3, [sp, #16]
	ldr	r2, [sp, #20]
	ldr	r0, .L2741+24
	strb	r3, [r10, #43]
	ldr	r3, [sp, #4]
	strb	r2, [r10, #42]
	strb	fp, [r8, r3]
	ldr	r3, [sp, #12]
	add	r1, r3, r3, lsl #1
	add	r1, r8, r1, lsl #4
	bl	buf_add_tail
.L2722:
	subs	r5, r5, #1
	beq	.L2740
	ldr	r3, [sp, #8]
	add	r4, r3, r3, lsl #1
	ldr	r3, .L2741
	add	r4, r3, r4, lsl #4
	b	.L2717
.L2730:
	ldrb	r3, [r7, #42]	@ zero_extendqisi2
	cmp	r3, #13
	bne	.L2729
	ldrb	r3, [r7]	@ zero_extendqisi2
	subs	r6, r6, #1
	cmp	r3, #255
	itt	ne
	addne	r3, r3, r3, lsl #1
	addne	r7, r4, r3, lsl #4
.L2729:
	bl	queue_wait_first_req_completed
	bl	queue_remove_completed_req
	b	.L2728
.L2742:
	.align	2
.L2741:
	.word	.LANCHOR55
	.word	.LANCHOR183
	.word	.LANCHOR31
	.word	.LANCHOR184
	.word	.LC0
	.word	.LANCHOR111
	.word	.LANCHOR59
	.size	sblk_read_page, .-sblk_read_page
	.section	.text.gc_check_data_one_wl,"ax",%progbits
	.align	1
	.global	gc_check_data_one_wl
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	gc_check_data_one_wl, %function
gc_check_data_one_wl:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, r8, r10, fp, lr}
	sub	sp, sp, #24
	ldr	r4, .L2776
	ldr	r3, .L2776+4
	ldr	r2, [r4, #8]
	ldr	r8, [r3]
	mov	fp, r3
	cbnz	r2, .L2744
	movs	r0, #1
	bl	buf_alloc
	str	r0, [r4, #8]
.L2744:
	ldr	r5, [r4, #8]
	cbnz	r5, .L2745
	movw	r2, #729
	ldr	r1, .L2776+8
	ldr	r0, .L2776+12
	bl	printf
.L2745:
	add	r10, r8, #96
	movs	r7, #0
.L2746:
	ldrb	r3, [r8, #89]	@ zero_extendqisi2
	cmp	r7, r3
	bge	.L2757
	movs	r6, #1
	b	.L2758
.L2756:
	ldr	r2, .L2776+16
	ldrh	r3, [r10]
	ldrh	r2, [r2]
	muls	r2, r3, r2
	ldr	r3, .L2776+20
	ldrb	r1, [r3]	@ zero_extendqisi2
	cmp	r1, #2
	beq	.L2747
	ldr	r3, .L2776+24
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L2748
.L2747:
	ldrh	r3, [r4, #12]
	subs	r3, r3, #1
	add	r3, r3, r2
	add	r3, r3, r6
	orr	r3, r3, r1, lsl #24
.L2775:
	movs	r1, #1
	str	r3, [r5, #24]
	mov	r0, r5
	bl	sblk_read_page
	ldr	r2, [r5, #36]
	ldr	r1, .L2776+28
	adds	r0, r2, #1
	beq	.L2752
	ldr	r3, [r1]
	ldrh	ip, [r4, #18]
	ldr	r0, [r5, #12]
	ldr	lr, [r3, ip, lsl #2]
	ldr	r3, [r0, #4]
	cmp	lr, r3
	bne	.L2752
	ldr	r3, .L2776+32
	ldr	r0, [r0, #8]
	ldr	r3, [r3]
	ldr	r3, [r3, ip, lsl #2]
	cmp	r3, r0
	beq	.L2753
.L2752:
	ldrh	r3, [r4, #18]
	ldr	r1, [r1]
	lsls	r0, r3, #2
	ldr	r3, [r1, r3, lsl #2]
	adds	r1, r3, #1
	beq	.L2753
	ldr	r1, .L2776+36
	ldr	r1, [r1]
	lsls	r1, r1, #21
	bpl	.L2754
	ldr	r1, [r5, #12]
	ldr	r4, [r1, #12]
	str	r4, [sp, #16]
	ldr	r4, [r1, #8]
	str	r4, [sp, #12]
	ldr	r4, [r1, #4]
	str	r4, [sp, #8]
	ldr	r1, [r1]
	str	r1, [sp, #4]
	ldr	r1, .L2776+32
	ldr	r1, [r1]
	ldr	r1, [r1, r0]
	ldr	r0, .L2776+40
	str	r1, [sp]
	ldr	r1, [r5, #24]
	bl	printf
.L2754:
	ldr	r3, .L2776+44
	movs	r0, #0
	ldrh	r2, [r8, #80]
	ldrb	r1, [r3]	@ zero_extendqisi2
	ldr	r3, .L2776+48
	ldr	r3, [r3]
	strh	r0, [r3, r2, lsl #1]	@ movhi
	ldr	r2, [fp]
	ldr	r3, [r2, #556]
	adds	r3, r3, #1
	str	r3, [r2, #556]
	ldr	r3, .L2776+52
	ldr	r3, [r3]
	ldr	r2, [r3, #156]
	ldr	r3, .L2776+56
	cmp	r2, r3
	bne	.L2761
	cbnz	r1, .L2761
	ldr	r3, .L2776+60
	ldrb	r3, [r3]	@ zero_extendqisi2
	cbnz	r3, .L2761
	ldr	r0, [r5, #24]
	bl	ftl_mask_bad_block
.L2761:
	mov	r0, #-1
	b	.L2743
.L2748:
	cmp	r1, #3
	ldrh	r3, [r4, #12]
	bne	.L2750
	ldr	r1, .L2776+64
	ldrb	r1, [r1]	@ zero_extendqisi2
	cbz	r1, .L2751
	add	r3, r3, r3, lsl #1
	subs	r3, r3, #1
	add	r3, r3, r2
	add	r3, r3, r6
	orr	r3, r3, #50331648
	b	.L2775
.L2751:
	add	r3, r3, r2
	orr	r3, r3, r6, lsl #24
	b	.L2775
.L2750:
	add	r3, r3, r2
	b	.L2775
.L2753:
	ldrh	r3, [r4, #18]
	adds	r6, r6, #1
	adds	r3, r3, #1
	strh	r3, [r4, #18]	@ movhi
.L2758:
	ldrh	r3, [r4, #16]
	cmp	r6, r3
	ble	.L2756
	adds	r7, r7, #1
	add	r10, r10, #2
	b	.L2746
.L2757:
	ldrh	r3, [r4, #12]
	adds	r2, r3, #1
	strh	r2, [r4, #12]	@ movhi
	ldr	r2, .L2776+60
	ldrb	r0, [r2]	@ zero_extendqisi2
	cbz	r0, .L2743
	movs	r0, #0
	adds	r3, r3, #2
	strh	r3, [r4, #12]	@ movhi
.L2755:
.L2743:
	add	sp, sp, #24
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r10, fp, pc}
.L2777:
	.align	2
.L2776:
	.word	.LANCHOR70
	.word	.LANCHOR12
	.word	.LANCHOR185
	.word	.LC0
	.word	.LANCHOR111
	.word	.LANCHOR78
	.word	.LANCHOR35
	.word	.LANCHOR159
	.word	.LANCHOR160
	.word	.LANCHOR19
	.word	.LC143
	.word	.LANCHOR124
	.word	.LANCHOR11
	.word	.LANCHOR110
	.word	1145785929
	.word	.LANCHOR80
	.word	.LANCHOR36
	.size	gc_check_data_one_wl, .-gc_check_data_one_wl
	.section	.text.sblk_tlc_prog_one_page,"ax",%progbits
	.align	1
	.global	sblk_tlc_prog_one_page
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	sblk_tlc_prog_one_page, %function
sblk_tlc_prog_one_page:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	ldr	r3, [r0]
	push	{r4, r5, r6, lr}
	mov	r5, r0
	ldr	r6, [r3, #24]
.L2779:
	movs	r1, #1
	mov	r0, r6
	bl	queue_lun_state
	mov	r4, r0
	cbnz	r0, .L2780
	mov	r0, r5
	movs	r1, #1
	bl	queue_tlc_prog_cmd
	mov	r0, r4
	pop	{r4, r5, r6, pc}
.L2780:
	bl	queue_wait_first_req_completed
	bl	queue_remove_completed_req
	b	.L2779
	.size	sblk_tlc_prog_one_page, .-sblk_tlc_prog_one_page
	.section	.text.sblk_xlc_prog_pages,"ax",%progbits
	.align	1
	.global	sblk_xlc_prog_pages
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	sblk_xlc_prog_pages, %function
sblk_xlc_prog_pages:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 0, uses_anonymous_args = 0
	ldr	r3, [r0]
	push	{r4, r5, r6, r7, r8, r10, fp, lr}
	mov	r5, r0
	mov	r6, r1
	sub	sp, sp, #24
	ldr	r4, [r3, #24]
	str	r2, [sp, #20]
.L2782:
	movs	r1, #1
	mov	r0, r4
	bl	queue_lun_state
	mov	r8, r0
	cmp	r0, #0
	bne	.L2783
	ldr	r3, [sp, #20]
	cmp	r3, #2
	bne	.L2784
	ldr	r3, .L2793
	ldr	ip, [r6]
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L2785
	ldr	r3, .L2793+4
	mov	r10, #1
	ldr	r2, [r5]
	ldr	fp, [ip, #24]
	ldrb	r3, [r3]	@ zero_extendqisi2
	ldr	r1, [r2, #24]
	rsb	r0, r3, #24
	lsl	r4, r10, r0
	subs	r4, r4, #1
	and	r7, r1, r4
	and	fp, r4, fp
	lsl	r4, r10, r3
	ldr	r3, .L2793+8
	lsrs	r1, r1, r0
	subs	r4, r4, #1
	ldrb	r3, [r3]	@ zero_extendqisi2
	ands	r4, r4, r1
	uxtb	r4, r4
	cmp	r3, #0
	beq	.L2786
	mov	r0, r4
	bl	zftl_flash_exit_slc_mode
	ldr	r3, [r5]
	mov	r1, r10
	mov	r0, r8
	ldr	r2, [r3, #12]
	str	r2, [sp, #8]
	movs	r2, #17
	ldr	r3, [r3, #4]
	str	r7, [sp]
	str	r3, [sp, #4]
	mov	r3, r4
	bl	flash_start_one_pass_page_prog
	bl	nandc_wait_flash_ready
	ldr	r3, [r6]
	mov	r1, r10
	mov	r0, r8
	ldr	r2, [r3, #12]
	str	r2, [sp, #8]
	movs	r2, #26
	ldr	r3, [r3, #4]
	str	fp, [sp]
	str	r3, [sp, #4]
	mov	r3, r4
	bl	flash_start_one_pass_page_prog
	bl	nandc_wait_flash_ready
	ldr	r3, [r5, #4]
	mov	r0, r8
	ldr	r1, [sp, #20]
	ldr	r2, [r3, #12]
	str	r2, [sp, #8]
	movs	r2, #17
	ldr	r3, [r3, #4]
	str	r3, [sp, #4]
	add	r3, r7, r10
	str	r3, [sp]
	mov	r3, r4
	bl	flash_start_one_pass_page_prog
	bl	nandc_wait_flash_ready
	ldr	r3, [r6, #4]
	mov	r0, r8
	ldr	r1, [sp, #20]
	adds	r7, r7, #2
	ldr	r2, [r3, #12]
	str	r2, [sp, #8]
	movs	r2, #26
	ldr	r3, [r3, #4]
	str	r3, [sp, #4]
	add	r3, fp, r10
	str	r3, [sp]
	mov	r3, r4
	bl	flash_start_one_pass_page_prog
	bl	nandc_wait_flash_ready
	ldr	r3, [r5, #8]
	movs	r1, #3
	mov	r0, r8
	ldr	r2, [r3, #12]
	str	r2, [sp, #8]
	movs	r2, #17
	ldr	r3, [r3, #4]
	str	r7, [sp]
	str	r3, [sp, #4]
	mov	r3, r4
	bl	flash_start_one_pass_page_prog
	bl	nandc_wait_flash_ready
	ldr	r3, [r6, #8]
	movs	r1, #3
	mov	r0, r8
	ldr	r2, [r3, #12]
	str	r2, [sp, #8]
	movs	r2, #16
	ldr	r3, [r3, #4]
	str	r3, [sp, #4]
	add	r3, fp, #2
	str	r3, [sp]
	mov	r3, r4
	bl	flash_start_one_pass_page_prog
.L2787:
	ldr	r1, [r5]
	movs	r3, #5
	ldr	r0, .L2793+12
	strb	r3, [r1, #42]
	movs	r3, #1
	strb	r3, [r1, #43]
	movs	r3, #255
	strb	r3, [r1]
	bl	buf_add_tail
.L2788:
	movs	r0, #0
	add	sp, sp, #24
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r10, fp, pc}
.L2783:
	bl	queue_wait_first_req_completed
	bl	queue_remove_completed_req
	b	.L2782
.L2786:
	ldr	r3, [r2, #12]
	mov	r1, r10
	ldrb	r0, [r2, #44]	@ zero_extendqisi2
	str	r3, [sp, #8]
	ldr	r3, [r2, #4]
	movs	r2, #17
	str	r7, [sp]
	str	r3, [sp, #4]
	mov	r3, r4
	bl	flash_start_tlc_page_prog
	bl	nandc_wait_flash_ready
	ldr	r3, [r6]
	mov	r1, r10
	ldr	r2, [r5]
	ldrb	r0, [r2, #44]	@ zero_extendqisi2
	ldr	r2, [r3, #12]
	str	r2, [sp, #8]
	movs	r2, #26
	ldr	r3, [r3, #4]
	str	fp, [sp]
	str	r3, [sp, #4]
	mov	r3, r4
	bl	flash_start_tlc_page_prog
	bl	nandc_wait_flash_ready
	ldm	r5, {r2, r3}
	ldr	r1, [sp, #20]
	ldrb	r0, [r2, #44]	@ zero_extendqisi2
	ldr	r2, [r3, #12]
	str	r2, [sp, #8]
	movs	r2, #17
	ldr	r3, [r3, #4]
	str	r7, [sp]
	str	r3, [sp, #4]
	mov	r3, r4
	bl	flash_start_tlc_page_prog
	bl	nandc_wait_flash_ready
	ldr	r3, [r6, #4]
	ldr	r2, [r5]
	ldr	r1, [sp, #20]
	ldrb	r0, [r2, #44]	@ zero_extendqisi2
	ldr	r2, [r3, #12]
	str	r2, [sp, #8]
	movs	r2, #26
	ldr	r3, [r3, #4]
	str	fp, [sp]
	str	r3, [sp, #4]
	mov	r3, r4
	bl	flash_start_tlc_page_prog
	bl	nandc_wait_flash_ready
	ldr	r3, [r5, #8]
	movs	r1, #3
	ldr	r2, [r5]
	ldrb	r0, [r2, #44]	@ zero_extendqisi2
	ldr	r2, [r3, #12]
	str	r2, [sp, #8]
	movs	r2, #17
	ldr	r3, [r3, #4]
	str	r7, [sp]
	str	r3, [sp, #4]
	mov	r3, r4
	bl	flash_start_tlc_page_prog
	bl	nandc_wait_flash_ready
	ldr	r3, [r6, #8]
	movs	r1, #3
	ldr	r2, [r5]
	ldrb	r0, [r2, #44]	@ zero_extendqisi2
	ldr	r2, [r3, #12]
	str	r2, [sp, #8]
	movs	r2, #16
	ldr	r3, [r3, #4]
	str	fp, [sp]
	str	r3, [sp, #4]
	mov	r3, r4
	bl	flash_start_tlc_page_prog
	b	.L2787
.L2785:
	ldr	r4, [ip, #24]
.L2789:
	movs	r1, #1
	mov	r0, r4
	bl	queue_lun_state
	mov	r7, r0
	cbnz	r0, .L2790
	movs	r1, #1
	mov	r0, r5
	bl	queue_tlc_prog_cmd
	mov	r1, r7
	mov	r0, r6
	bl	queue_tlc_prog_cmd
.L2791:
	movs	r1, #1
	mov	r0, r4
	bl	queue_lun_state
	cmp	r0, #0
	beq	.L2788
	bl	queue_wait_first_req_completed
	bl	queue_remove_completed_req
	b	.L2791
.L2790:
	bl	queue_wait_first_req_completed
	bl	queue_remove_completed_req
	b	.L2789
.L2784:
	movs	r1, #1
	mov	r0, r5
	bl	queue_tlc_prog_cmd
	b	.L2788
.L2794:
	.align	2
.L2793:
	.word	.LANCHOR44
	.word	.LANCHOR31
	.word	.LANCHOR36
	.word	.LANCHOR59
	.size	sblk_xlc_prog_pages, .-sblk_xlc_prog_pages
	.section	.text.sblk_3d_mlc_prog_pages,"ax",%progbits
	.align	1
	.global	sblk_3d_mlc_prog_pages
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	sblk_3d_mlc_prog_pages, %function
sblk_3d_mlc_prog_pages:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r0, r1, r4, r5, r6, r7, r8, r10, fp, lr}
	mov	r7, r1
	ldr	r10, .L2800
	add	r5, r0, #8
	ldr	fp, .L2800+4
.L2796:
	cbnz	r7, .L2799
	mov	r0, r7
	add	sp, sp, #8
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r10, fp, pc}
.L2799:
	ldr	r3, [r5, #-8]
	ldr	r4, [r3, #24]
.L2797:
	movs	r1, #1
	mov	r0, r4
	bl	queue_lun_state
	cmp	r0, #0
	bne	.L2798
	ldr	r3, [r5, #-8]
	mov	r8, #1
	subs	r7, r7, #1
	adds	r5, r5, #8
	ldr	r2, [r3, #24]
	ldrb	r3, [r10]	@ zero_extendqisi2
	rsb	r1, r3, #24
	lsl	r6, r8, r1
	lsl	r4, r8, r3
	subs	r6, r6, #1
	subs	r4, r4, #1
	ands	r6, r6, r2
	lsrs	r2, r2, r1
	ands	r4, r4, r2
	uxtb	r4, r4
	mov	r0, r4
	bl	zftl_flash_exit_slc_mode
	ldr	r3, [r5, #-16]
	mov	r1, r4
	movs	r0, #16
	ldr	r2, [r3, #12]
	str	r2, [sp]
	mov	r2, r6
	ldr	r3, [r3, #4]
	bl	flash_start_3d_mlc_page_prog
	bl	nandc_wait_flash_ready
	ldr	r3, [r5, #-12]
	mov	r1, r4
	movs	r0, #16
	ldr	r2, [r3, #12]
	str	r2, [sp]
	add	r2, r6, r8
	ldr	r3, [r3, #4]
	bl	flash_start_3d_mlc_page_prog
	bl	nandc_de_cs.constprop.32
	ldr	r1, [r5, #-16]
	movs	r3, #4
	mov	r0, fp
	strb	r3, [r1, #42]
	movs	r3, #255
	strb	r8, [r1, #43]
	strb	r3, [r1]
	bl	buf_add_tail
	b	.L2796
.L2798:
	bl	queue_wait_first_req_completed
	bl	queue_remove_completed_req
	b	.L2797
.L2801:
	.align	2
.L2800:
	.word	.LANCHOR31
	.word	.LANCHOR59
	.size	sblk_3d_mlc_prog_pages, .-sblk_3d_mlc_prog_pages
	.section	.text.flash_prog_page_en,"ax",%progbits
	.align	1
	.global	flash_prog_page_en
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	flash_prog_page_en, %function
flash_prog_page_en:
	@ args = 8, pretend = 0, frame = 16
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, r8, r10, fp, lr}
	mov	r8, r2
	ldr	r7, .L2837
	sub	sp, sp, #24
	mov	fp, r3
	mov	r6, r0
	ldrb	r3, [sp, #60]	@ zero_extendqisi2
	mov	r4, r1
	ldrb	r2, [r7]	@ zero_extendqisi2
	ubfx	r5, r1, #24, #2
	str	r3, [sp, #20]
	cmp	r2, r0
	bhi	.L2803
	movw	r2, #642
	ldr	r1, .L2837+4
	ldr	r0, .L2837+8
	bl	printf
.L2803:
	ldrb	r3, [r7]	@ zero_extendqisi2
	cmp	r3, r6
	bls	.L2814
	ldr	r3, .L2837+12
	ldrb	r3, [r3, r6]	@ zero_extendqisi2
	str	r3, [sp, #12]
	cmp	r5, #0
	bne	.L2816
	ldr	r3, .L2837+16
	ldr	r10, .L2837+64
	ldrb	r3, [r3]	@ zero_extendqisi2
	cbz	r3, .L2806
	ldrb	r3, [r10]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L2816
.L2806:
	ldr	r3, .L2837+20
	mov	r0, r4
	ldrh	r7, [r3]
	mov	r1, r7
	bl	__aeabi_uidiv
	mov	r1, r7
	mul	r5, r7, r0
	mov	r0, r4
	bl	__aeabi_uidivmod
	ldrb	r3, [r10]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L2807
	add	r5, r5, r1, lsl #1
.L2811:
	ldr	r3, .L2837+24
	ldr	r3, [r3]
	lsls	r1, r3, #27
	bpl	.L2808
	mov	r3, r5
	mov	r2, r4
	ldr	r1, [sp, #12]
	ldr	r0, .L2837+28
	bl	printf
.L2808:
	ldr	r3, [sp, #56]
	mov	r2, r8
	mov	r1, r5
	ldr	r0, [sp, #12]
	str	r3, [sp]
	mov	r3, fp
	bl	flash_prog_page
	ldr	r3, [sp, #20]
	str	r0, [sp, #16]
	cmp	r3, #0
	beq	.L2809
	ldr	r3, [sp, #56]
	mov	r1, r4
	ldr	r10, .L2837+44
	mov	r0, r6
	ldr	r2, .L2837+32
	str	r3, [sp]
	ldr	r3, [r10]
	ldr	r2, [r2]
	bl	flash_read_page_en
	adds	r2, r0, #1
	mov	r7, r0
	beq	.L2810
	cmp	r0, #512
	beq	.L2810
	ldr	r3, .L2837+32
	ldr	r2, [r8]
	ldr	r3, [r3]
	ldr	r3, [r3]
	cmp	r2, r3
	bne	.L2810
	ldr	r3, [r10]
	ldr	r2, [fp]
	ldr	r3, [r3]
	cmp	r2, r3
	beq	.L2809
.L2810:
	movs	r3, #4
	mov	r1, r8
	mov	r2, r3
	ldr	r0, .L2837+36
	bl	rknand_print_hex
	movs	r3, #4
	mov	r1, fp
	mov	r2, r3
	ldr	r0, .L2837+40
	bl	rknand_print_hex
	ldr	r1, .L2837+44
	movs	r3, #4
	mov	r2, r3
	ldr	r0, .L2837+48
	ldr	r1, [r1]
	bl	rknand_print_hex
	ldr	r1, .L2837+32
	movs	r3, #4
	mov	r2, r3
	ldr	r0, .L2837+52
	ldr	r1, [r1]
	bl	rknand_print_hex
	cmp	r7, #512
	beq	.L2811
.L2813:
	mov	r1, r4
	ldr	r0, .L2837+56
	bl	printf
	movw	r2, #685
	ldr	r1, .L2837+4
	ldr	r0, .L2837+8
	bl	printf
.L2814:
	mov	r0, #-1
	b	.L2802
.L2807:
	ldr	r3, .L2837+60
	ldrh	r1, [r3, r1, lsl #1]
	add	r5, r5, r1
	b	.L2811
.L2816:
.L2805:
	mov	r5, r4
	b	.L2811
.L2809:
	ldr	r0, [sp, #16]
	adds	r3, r0, #1
	beq	.L2813
.L2802:
	add	sp, sp, #24
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r10, fp, pc}
.L2838:
	.align	2
.L2837:
	.word	.LANCHOR23
	.word	.LANCHOR186
	.word	.LC0
	.word	.LANCHOR29
	.word	.LANCHOR0
	.word	.LANCHOR2
	.word	.LANCHOR19
	.word	.LC144
	.word	.LANCHOR173
	.word	.LC145
	.word	.LC146
	.word	.LANCHOR172
	.word	.LC147
	.word	.LC148
	.word	.LC149
	.word	.LANCHOR3
	.word	.LANCHOR1
	.size	flash_prog_page_en, .-flash_prog_page_en
	.section	.text.ftl_test_block,"ax",%progbits
	.align	1
	.global	ftl_test_block
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	ftl_test_block, %function
ftl_test_block:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r0, r1, r2, r3, r4, r5, r6, r7, r8, r10, fp, lr}
	movs	r5, #0
	ldr	r3, .L2866
	mov	r10, r0
	mov	r8, r5
	ldr	r2, [r3]
	str	r3, [sp, #12]
	str	r5, [r2]
	ldr	r2, .L2866+4
	str	r5, [r2]
.L2840:
	uxth	r3, r5
	str	r3, [sp, #8]
	ldr	r3, .L2866+8
	ldr	r2, [sp, #8]
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, r2
	bls	.L2850
	mov	fp, #0
	b	.L2851
.L2849:
	ldr	r3, .L2866+12
	ldr	r3, [r3]
	lsls	r3, r3, #19
	bpl	.L2841
	mov	r1, r10
	ldr	r0, .L2866+16
	bl	printf
.L2841:
	ldr	r3, .L2866+20
	ldrb	r4, [r3]	@ zero_extendqisi2
	ldr	r3, [sp, #8]
	smulbb	r4, r4, r10
	add	r4, r4, r6
	uxth	r4, r4
	cbnz	r3, .L2842
	ldr	r3, .L2866+24
	ldr	r3, [r3]
	ldrb	r3, [r3, #47]	@ zero_extendqisi2
	cmp	r3, r4
	bcs	.L2843
.L2842:
	uxtb	r6, r5
	mov	r1, r4
	mov	r0, r6
	bl	flash_check_bad_block
	cbnz	r0, .L2843
	ldr	r3, .L2866+28
	mov	r1, r8
	mov	r0, r6
	ldrh	r7, [r3]
	muls	r7, r4, r7
	mov	r2, r7
	bl	flash_erase_block_en
	cbz	r0, .L2844
	ldr	r3, .L2866+32
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, #2
	bne	.L2865
	ldr	r3, .L2866+36
	ldrb	r3, [r3]	@ zero_extendqisi2
	cbz	r3, .L2865
	mov	r2, r7
	movs	r1, #1
	mov	r0, r6
	bl	flash_erase_block_en
	cbnz	r0, .L2865
.L2848:
	ldr	r3, .L2866+32
	mov	r8, #1
	ldrb	r3, [r3]	@ zero_extendqisi2
	add	r7, r7, r3, lsl #24
.L2847:
	movs	r3, #1
	ldr	r2, [sp, #12]
	str	r3, [sp, #4]
	mov	r1, r7
	ldr	r3, .L2866+40
	mov	r0, r6
	ldrb	r3, [r3]	@ zero_extendqisi2
	str	r3, [sp]
	ldr	r3, .L2866+4
	ldr	r2, [r2]
	bl	flash_prog_page_en
	cbz	r0, .L2843
.L2865:
	mov	r1, r4
	mov	r0, r6
	bl	flash_mask_bad_block
.L2843:
	add	fp, fp, #1
.L2851:
	ldr	r3, .L2866+20
	uxth	r6, fp
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, r6
	bhi	.L2849
	adds	r5, r5, #1
	b	.L2840
.L2844:
	cmp	r8, #0
	beq	.L2847
	b	.L2848
.L2850:
	cmp	r8, #0
	beq	.L2852
	ldr	r3, .L2866+44
	movs	r2, #2
	ldr	r3, [r3]
	add	r10, r3, r10, lsl #2
	ldrb	r3, [r10, #2]	@ zero_extendqisi2
	bfi	r3, r2, #3, #2
	strb	r3, [r10, #2]
.L2852:
	movs	r0, #0
	add	sp, sp, #16
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r10, fp, pc}
.L2867:
	.align	2
.L2866:
	.word	.LANCHOR187
	.word	.LANCHOR188
	.word	.LANCHOR112
	.word	.LANCHOR19
	.word	.LC150
	.word	.LANCHOR75
	.word	.LANCHOR6
	.word	.LANCHOR111
	.word	.LANCHOR78
	.word	.LANCHOR0
	.word	.LANCHOR131
	.word	.LANCHOR9
	.size	ftl_test_block, .-ftl_test_block
	.section	.text.ftl_prog_page,"ax",%progbits
	.align	1
	.global	ftl_prog_page
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	ftl_prog_page, %function
ftl_prog_page:
	@ args = 4, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r0, r1, r2, r4, r5, r6, r7, lr}
	mov	r4, r0
	mov	r7, r3
	mov	r5, r1
	mov	r6, r2
	bl	sblk_wait_write_queue_completed
	movs	r3, #1
	mov	r0, r4
	str	r3, [sp, #4]
	mov	r2, r6
	ldr	r3, [sp, #32]
	mov	r1, r5
	str	r3, [sp]
	mov	r3, r7
	bl	flash_prog_page_en
	adds	r3, r0, #1
	mov	r4, r0
	bne	.L2868
	ldr	r1, .L2870
	movw	r2, #2678
	ldr	r0, .L2870+4
	bl	printf
	mov	r1, r5
	ldr	r0, .L2870+8
	bl	printf
.L2868:
	mov	r0, r4
	add	sp, sp, #12
	@ sp needed
	pop	{r4, r5, r6, r7, pc}
.L2871:
	.align	2
.L2870:
	.word	.LANCHOR189
	.word	.LC0
	.word	.LC149
	.size	ftl_prog_page, .-ftl_prog_page
	.section	.text.ftl_info_flush,"ax",%progbits
	.align	1
	.global	ftl_info_flush
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	ftl_info_flush, %function
ftl_info_flush:
	@ args = 0, pretend = 0, frame = 24
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, r8, r10, fp, lr}
	sub	sp, sp, #32
	ldr	r5, .L2906
	movs	r1, #0
	mov	r8, #0
	str	r0, [sp, #16]
	ldrb	r2, [r5]	@ zero_extendqisi2
	ldr	r0, .L2906+4
	ldr	r4, .L2906+8
	lsls	r2, r2, #1
	bl	ftl_memset
	ldr	r2, .L2906+12
	ldr	r3, [r2]
	str	r2, [sp, #20]
	ldrh	r1, [r3, #74]
	cmp	r1, #1
	itt	hi
	movhi	r2, #0
	strhhi	r2, [r3, #150]	@ movhi
.L2883:
	ldr	r3, .L2906+8
	ldr	r6, .L2906+16
	ldr	r1, [sp, #16]
	ldrb	fp, [r3]	@ zero_extendqisi2
	ldrh	r3, [r6]
	ldr	r7, .L2906+20
	str	r3, [sp, #12]
	ldr	r3, .L2906+8
	ldr	r0, [r7]
	ldrh	r10, [r3, #2]
	ldr	r3, [sp, #20]
	ldr	r2, [r3]
	ldr	r3, [r2, #4]
	adds	r3, r3, #1
	str	r3, [r2, #4]
	ldr	r2, .L2906+4
	str	r3, [sp, #28]
	stm	r2, {r1, r3}
	ldrb	r1, [r5]	@ zero_extendqisi2
	str	r2, [sp, #24]
	lsls	r1, r1, #9
	bl	js_hash
	ldr	r2, [sp, #24]
	ldr	r3, [sp, #28]
	str	r0, [r2, #8]
	ldr	r2, .L2906+24
	ldr	r2, [r2]
	tst	r2, #4096
	beq	.L2874
	mov	r2, r10
	mov	r1, fp
	ldr	r0, .L2906+28
	bl	printf
.L2874:
	ldr	r3, .L2906+32
	ldrh	r0, [r4, #2]
	ldrh	r3, [r3]
	cmp	r3, r0
	bhi	.L2875
	ldr	r10, .L2906+48
	ldr	fp, .L2906+44
.L2879:
	ldrb	r3, [r4, #1]	@ zero_extendqisi2
	adds	r3, r3, #1
	uxtb	r3, r3
	cmp	r3, #7
	strb	r3, [r4, #1]
	bls	.L2876
	ldr	r2, [r10]
	movs	r3, #0
	adds	r2, r2, #40
.L2892:
	ldrb	r1, [r2], #1	@ zero_extendqisi2
	uxth	r8, r3
	cmp	r1, #128
	bls	.L2877
	cmp	r1, #255
	beq	.L2878
	movw	r2, #846
	mov	r1, fp
	ldr	r0, .L2906+36
	bl	printf
.L2877:
	strb	r8, [r4, #1]
	mov	r8, #1
.L2876:
	ldr	r3, [r10]
	ldrb	r2, [r4, #1]	@ zero_extendqisi2
	add	r3, r3, r2
	ldrb	r3, [r3, #40]	@ zero_extendqisi2
	cmp	r3, #255
	strb	r3, [r4]
	beq	.L2879
	ldrh	r10, [r6]
	movs	r0, #0
	mul	r10, r3, r10
	mov	r1, r10
	bl	flash_erase_block
	ldrb	r3, [r5]	@ zero_extendqisi2
	mov	r1, r10
	movs	r0, #0
	str	r3, [sp]
	ldr	r2, [r7]
	ldr	r3, .L2906+4
	bl	ftl_prog_page
	movs	r3, #1
	add	r10, r10, r3
	strh	r3, [r4, #2]	@ movhi
.L2880:
	ldrb	r3, [r5]	@ zero_extendqisi2
	mov	r1, r10
	movs	r0, #0
	str	r3, [sp]
	ldr	r2, [r7]
	ldr	r3, .L2906+4
	bl	ftl_prog_page
	ldrh	r3, [r4, #2]
	adds	r0, r0, #1
	add	r3, r3, #1
	strh	r3, [r4, #2]	@ movhi
	ldr	r3, .L2906+40
	beq	.L2881
	ldrb	r2, [r3]	@ zero_extendqisi2
	cbz	r2, .L2882
.L2881:
	movs	r2, #0
	strb	r2, [r3]
	b	.L2883
.L2875:
	ldr	r3, [sp, #12]
	mla	r10, fp, r3, r10
	cmp	r0, #0
	bne	.L2880
	mov	r1, r10
	bl	flash_erase_block
	b	.L2880
.L2882:
	cmp	r8, #0
	bne	.L2884
.L2891:
	ldrb	r3, [r4]	@ zero_extendqisi2
	cmp	r3, #255
	bne	.L2905
	movw	r2, #890
	ldr	r1, .L2906+44
	ldr	r0, .L2906+36
	bl	printf
.L2905:
	movs	r0, #0
	add	sp, sp, #32
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r10, fp, pc}
.L2884:
	ldrb	r5, [r4, #1]	@ zero_extendqisi2
	ldr	r6, .L2906+48
	ldr	r7, .L2906+44
	adds	r5, r5, #1
.L2887:
	cmp	r5, #7
	bhi	.L2891
	ldr	r3, [r6]
	add	r3, r3, r5
	ldrb	r8, [r3, #40]	@ zero_extendqisi2
	uxth	r3, r8
	cmp	r3, #128
	bls	.L2888
	cmp	r3, #255
	beq	.L2889
	movw	r2, #881
	mov	r1, r7
	ldr	r0, .L2906+36
	bl	printf
.L2888:
	ldr	r3, .L2906+16
	movs	r0, #0
	ldrh	r1, [r3]
	mul	r1, r8, r1
	bl	flash_erase_block
.L2889:
	adds	r5, r5, #1
	uxth	r5, r5
	b	.L2887
.L2878:
	adds	r3, r3, #1
	cmp	r3, #8
	bne	.L2892
	mov	r8, r3
	b	.L2877
.L2907:
	.align	2
.L2906:
	.word	.LANCHOR131
	.word	.LANCHOR190
	.word	.LANCHOR191
	.word	.LANCHOR110
	.word	.LANCHOR111
	.word	.LANCHOR192
	.word	.LANCHOR19
	.word	.LC151
	.word	.LANCHOR94
	.word	.LC0
	.word	.LANCHOR194
	.word	.LANCHOR193
	.word	.LANCHOR6
	.size	ftl_info_flush, .-ftl_info_flush
	.section	.text.ftl_info_blk_init,"ax",%progbits
	.align	1
	.global	ftl_info_blk_init
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	ftl_info_blk_init, %function
ftl_info_blk_init:
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 0, uses_anonymous_args = 0
	ldr	r3, .L2937
	ldr	r2, .L2937+4
	push	{r4, r5, r6, r7, r8, r10, fp, lr}
	movs	r4, #0
	strb	r4, [r3]
	movs	r3, #1
	sub	sp, sp, #24
	mov	r1, r4
	strb	r3, [r2]
	ldr	r7, .L2937+8
	ldr	r2, .L2937+12
	ldr	r5, .L2937+16
	ldr	r0, [r7]
	mov	fp, r7
	strb	r3, [r2]
	mov	r2, #16384
	ldr	r3, .L2937+20
	ldr	r6, .L2937+24
	str	r0, [r3]
	ldr	r3, .L2937+28
	ldrh	r3, [r3]
	add	r3, r0, r3, lsl #2
	str	r3, [r5]
	bl	ftl_memset
	ldr	r3, .L2937+32
	mov	r2, #16384
	mov	r1, r4
	ldr	r0, [r3]
	bl	ftl_memset
	ldr	r2, [r6]
	ldr	r3, .L2937+36
	ldrb	r2, [r2, #40]	@ zero_extendqisi2
	strb	r4, [r3, #1]
	strh	r4, [r3, #2]	@ movhi
	movs	r4, #7
	strb	r2, [r3]
	str	r3, [sp, #12]
.L2910:
	ldr	r3, [r6]
	sxth	r8, r4
	add	r3, r3, r4
	ldrb	r7, [r3, #40]	@ zero_extendqisi2
	cmp	r7, #255
	bne	.L2909
.L2914:
	adds	r4, r4, #-1
	bcs	.L2910
	mov	r8, #0
.L2911:
	ldr	r3, .L2937+40
	ldr	r3, [r3]
	lsls	r1, r3, #19
	bpl	.L2915
	ldr	r3, [r5]
	mov	r2, #4800
	mov	r1, r4
	ldr	r0, .L2937+44
	ldr	r3, [r3]
	bl	printf
.L2915:
	adds	r2, r4, #1
	bne	.L2916
	mov	r2, #16384
	movs	r1, #0
	ldr	r0, [fp]
	bl	ftl_memset
	ldr	r3, [r5]
	ldr	r2, .L2937+48
	str	r2, [r3]
	ldr	r2, .L2937+52
	str	r2, [r3, #12]
.L2908:
	mov	r0, r4
	add	sp, sp, #24
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r10, fp, pc}
.L2909:
	ldr	r3, .L2937+56
	movs	r0, #0
	ldrh	r3, [r3]
	muls	r7, r3, r7
	ldr	r3, .L2937+60
	ldrb	r3, [r3]	@ zero_extendqisi2
	mov	r1, r7
	str	r3, [sp]
	ldr	r3, .L2937+64
	ldr	r2, [fp]
	bl	ftl_read_page
	cmp	r0, #-1
	mov	r10, r0
	bne	.L2912
	ldr	r3, .L2937+60
	adds	r1, r7, #1
	movs	r0, #0
	ldrb	r3, [r3]	@ zero_extendqisi2
	str	r3, [sp]
	ldr	r3, .L2937+64
	ldr	r2, [fp]
	bl	ftl_read_page
	mov	r10, r0
.L2912:
	ldr	r3, .L2937+40
	ldr	r3, [r3]
	lsls	r0, r3, #19
	bpl	.L2913
	ldr	r3, [r5]
	mov	r2, r10
	mov	r1, r4
	ldr	r0, .L2937+68
	ldr	r3, [r3]
	str	r3, [sp]
	movw	r3, #749
	bl	printf
.L2913:
	cmp	r10, #-1
	beq	.L2914
	ldr	r3, [r5]
	ldr	r2, .L2937+48
	ldr	r3, [r3]
	cmp	r3, r2
	bne	.L2914
	mov	r4, r8
	b	.L2911
.L2916:
	ldr	r3, [r6]
	movs	r0, #0
	movs	r4, #0
	add	r3, r3, r8
	ldrb	r1, [r3, #40]	@ zero_extendqisi2
	ldr	r3, [sp, #12]
	strb	r1, [r3]
	strb	r8, [r3, #1]
	movs	r3, #4
	str	r3, [sp]
	ldr	r3, .L2937+64
	ldr	r2, [fp]
	bl	flash_get_last_written_page
	uxth	r6, r0
	ldr	r2, .L2937+56
	mov	r7, r0
	adds	r3, r6, #1
	uxth	r10, r3
	ldr	r3, [sp, #12]
	ldrh	r2, [r2]
	ldrb	r3, [r3]	@ zero_extendqisi2
	muls	r3, r2, r3
	str	r3, [sp, #16]
.L2918:
	subs	r3, r6, r4
	lsls	r3, r3, #16
	bmi	.L2922
	ldr	r3, [sp, #16]
	movs	r0, #0
	ldr	r8, .L2937+60
	adds	r1, r7, r3
	ldrb	r3, [r8]	@ zero_extendqisi2
	subs	r1, r1, r4
	str	r3, [sp]
	ldr	r3, .L2937+64
	ldr	r2, [fp]
	bl	ftl_read_page
	adds	r0, r0, #1
	beq	.L2919
	ldr	r3, .L2937+16
	ldr	r2, .L2937+48
	ldr	r3, [r3]
	ldr	r3, [r3]
	cmp	r3, r2
	bne	.L2919
	ldr	r3, .L2937+64
	ldr	r3, [r3, #8]
	cbnz	r3, .L2920
.L2922:
	ldr	r3, [sp, #12]
	strh	r10, [r3, #2]	@ movhi
	bl	ftl_tmp_into_update
	ldr	r2, [r5]
	movs	r0, #0
	ldr	r3, [r2, #64]
	adds	r3, r3, #1
	str	r3, [r2, #64]
	bl	ftl_info_flush
	movs	r0, #0
	bl	ftl_info_flush
	ldr	r3, .L2937+40
	ldr	r4, [r3]
	ands	r4, r4, #16384
	beq	.L2908
	ldr	r3, [r5]
	movs	r4, #0
	ldr	r0, .L2937+72
	ldr	r1, [r3, #156]
	bl	printf
	b	.L2908
.L2920:
	ldrb	r1, [r8]	@ zero_extendqisi2
	ldr	r0, [fp]
	str	r3, [sp, #20]
	lsls	r1, r1, #9
	bl	js_hash
	ldr	r3, [sp, #20]
	cmp	r3, r0
	beq	.L2922
	mov	r1, r3
	ldr	r0, .L2937+76
	bl	printf
.L2919:
	adds	r4, r4, #1
	b	.L2918
.L2938:
	.align	2
.L2937:
	.word	.LANCHOR195
	.word	.LANCHOR194
	.word	.LANCHOR192
	.word	.LANCHOR196
	.word	.LANCHOR110
	.word	.LANCHOR9
	.word	.LANCHOR6
	.word	.LANCHOR8
	.word	.LANCHOR197
	.word	.LANCHOR191
	.word	.LANCHOR19
	.word	.LC153
	.word	1229739078
	.word	393252
	.word	.LANCHOR111
	.word	.LANCHOR131
	.word	.LANCHOR190
	.word	.LC152
	.word	.LC155
	.word	.LC154
	.size	ftl_info_blk_init, .-ftl_info_blk_init
	.section	.text.ftl_ext_info_flush,"ax",%progbits
	.align	1
	.global	ftl_ext_info_flush
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	ftl_ext_info_flush, %function
ftl_ext_info_flush:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	ldr	r3, .L2955
	push	{r0, r1, r4, r5, r6, r7, r8, r10, fp, lr}
	ldr	r3, [r3]
	ldr	r2, [r3, #520]
	cbz	r2, .L2940
	movs	r2, #0
	str	r2, [r3, #520]
.L2940:
	ldr	r6, .L2955+4
	movs	r0, #0
	bl	ftl_total_vpn_update
	mov	r5, r6
.L2944:
	ldr	r3, [r6]
	ldr	r2, [r3, #56]
	adds	r2, r2, #1
	str	r2, [r3, #56]
	ldrh	r2, [r3, #140]
	ldr	r3, .L2955+8
	ldrh	r3, [r3]
	cmp	r2, r3
	bcc	.L2942
	bl	ftl_ext_alloc_new_blk
.L2942:
	ldr	r3, [r5]
	ldrh	r2, [r3, #130]
	movw	r3, #65535
	cmp	r2, r3
	bne	.L2943
	movw	r2, #2211
	ldr	r1, .L2955+12
	ldr	r0, .L2955+16
	bl	printf
.L2943:
	ldr	r3, .L2955+20
	ldr	r2, [r5]
	ldr	fp, .L2955+40
	ldrb	r3, [r3]	@ zero_extendqisi2
	ldrh	r1, [r2, #130]
	ldr	r8, .L2955+44
	rsb	r4, r3, #24
	ldr	r3, .L2955+24
	mov	r0, r8
	ldrh	r3, [r3]
	subs	r3, r4, r3
	movs	r4, #1
	asr	r7, r1, r3
	lsls	r4, r4, r3
	ldr	r3, .L2955+28
	subs	r4, r4, #1
	ands	r4, r4, r1
	ldrh	r1, [r3]
	sxth	r4, r4
	ldrh	r3, [r2, #140]
	ldrb	r2, [fp]	@ zero_extendqisi2
	mla	r4, r1, r4, r3
	lsls	r2, r2, #1
	movs	r1, #0
	bl	ftl_memset
	movs	r3, #0
	ldrb	fp, [fp]	@ zero_extendqisi2
	str	r3, [r8]
	ldr	r3, [r5]
	lsl	r1, fp, #9
	ldr	r3, [r3, #56]
	str	r3, [r8, #4]
	ldr	r3, .L2955+32
	ldr	r10, [r3]
	mov	r0, r10
	bl	js_hash
	mov	r3, r8
	str	r0, [r8, #8]
	mov	r2, r10
	str	fp, [sp]
	mov	r1, r4
	uxtb	r0, r7
	bl	ftl_prog_page
	ldr	r2, [r5]
	ldrh	r3, [r2, #140]
	adds	r3, r3, #1
	uxth	r3, r3
	cmp	r3, #1
	strh	r3, [r2, #140]	@ movhi
	beq	.L2944
	adds	r0, r0, #1
	ldr	r3, .L2955+36
	beq	.L2945
	ldrb	r0, [r3]	@ zero_extendqisi2
	cbz	r0, .L2946
.L2945:
.L2941:
	movs	r2, #0
	strb	r2, [r3]
	b	.L2944
.L2946:
	add	sp, sp, #8
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r10, fp, pc}
.L2956:
	.align	2
.L2955:
	.word	.LANCHOR12
	.word	.LANCHOR110
	.word	.LANCHOR94
	.word	.LANCHOR198
	.word	.LC0
	.word	.LANCHOR31
	.word	.LANCHOR74
	.word	.LANCHOR111
	.word	.LANCHOR197
	.word	.LANCHOR196
	.word	.LANCHOR131
	.word	.LANCHOR190
	.size	ftl_ext_info_flush, .-ftl_ext_info_flush
	.section	.text.ftl_ext_info_init,"ax",%progbits
	.align	1
	.global	ftl_ext_info_init
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	ftl_ext_info_init, %function
ftl_ext_info_init:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r0, r1, r2, r3, r4, r5, r6, r7, r8, r10, fp, lr}
	movs	r2, #0
	ldr	r3, .L2979
	ldr	r5, .L2979+4
	strh	r2, [r3]	@ movhi
	ldr	r1, .L2979+8
	ldr	r3, [r5]
	ldrh	r4, [r1]
	ldrh	r2, [r3, #130]
	ldr	r3, .L2979+12
	ldrb	r3, [r3]	@ zero_extendqisi2
	rsb	r3, r3, #24
	subs	r3, r3, r4
	movs	r4, #1
	lsls	r4, r4, r3
	asr	r7, r2, r3
	subs	r4, r4, #1
	uxtb	r8, r7
	ands	r4, r4, r2
	ldr	r2, .L2979+16
	movs	r3, #4
	mov	r1, r4
	str	r3, [sp]
	mov	r0, r8
	ldr	r3, .L2979+20
	ldr	r2, [r2]
	bl	flash_get_last_written_page
	ldr	r3, .L2979+24
	mov	r6, r0
	ldr	r3, [r3]
	lsls	r2, r3, #19
	bpl	.L2958
	ldr	r3, [r5]
	uxth	r7, r7
	mov	r2, #2256
	ldr	r1, .L2979+28
	ldrh	r3, [r3, #130]
	str	r7, [sp]
	str	r3, [sp, #4]
	mov	r3, r0
	ldr	r0, .L2979+32
	bl	printf
.L2958:
	movs	r7, #0
.L2959:
	uxth	r10, r6
	sub	r3, r10, r7
	lsls	r0, r3, #16
	bmi	.L2964
	ldr	r3, .L2979+36
	subs	r1, r6, r7
	ldr	fp, .L2979+60
	ldr	r2, .L2979+16
	ldrh	r0, [r3]
	ldrb	r3, [fp]	@ zero_extendqisi2
	mla	r1, r4, r0, r1
	str	r3, [sp]
	ldr	r3, .L2979+20
	ldr	r2, [r2]
	mov	r0, r8
	bl	flash_read_page_en
	adds	r3, r0, #1
	beq	.L2960
	cmp	r0, #512
	beq	.L2960
	ldr	r3, .L2979+40
	ldr	r2, .L2979+44
	ldr	r3, [r3]
	ldr	r3, [r3]
	cmp	r3, r2
	bne	.L2960
	ldr	r3, .L2979+20
	ldr	r3, [r3, #8]
	cmp	r3, #0
	bne	.L2961
.L2964:
	bl	zftl_sblk_list_init
	ldr	r2, [r5]
	ldrh	r3, [r2, #140]
	cmp	r3, r6
	bgt	.L2963
	add	r3, r10, #1
	strh	r3, [r2, #140]	@ movhi
	bl	ftl_ext_info_flush
.L2963:
	ldr	r3, .L2979+40
	movw	r1, #65535
	movs	r2, #0
	ldr	r3, [r3]
	strh	r1, [r3, #584]	@ movhi
	strh	r1, [r3, #586]	@ movhi
	strh	r1, [r3, #588]	@ movhi
	strh	r1, [r3, #590]	@ movhi
	str	r1, [r3, #560]
	mov	r1, #-1
	str	r1, [r3, #564]
	ldr	r1, .L2979+24
	str	r2, [r3, #520]
	str	r2, [r3, #604]
	ldr	r1, [r1]
	str	r2, [r3, #608]
	lsls	r1, r1, #19
	bpl	.L2966
	str	r2, [sp]
	ldr	r1, .L2979+28
	ldr	r3, [r3, #12]
	ldr	r0, .L2979+48
	bl	printf
.L2966:
	ldr	r3, .L2979+52
	movw	r2, #65535
	movs	r0, #0
	strh	r2, [r3]	@ movhi
	add	sp, sp, #16
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r10, fp, pc}
.L2961:
	ldrb	r1, [fp]	@ zero_extendqisi2
	str	r3, [sp, #12]
	ldr	r3, .L2979+16
	lsls	r1, r1, #9
	ldr	r0, [r3]
	bl	js_hash
	ldr	r3, [sp, #12]
	cmp	r3, r0
	beq	.L2964
	mov	r1, r3
	ldr	r0, .L2979+56
	bl	printf
.L2960:
	adds	r7, r7, #1
	b	.L2959
.L2980:
	.align	2
.L2979:
	.word	.LANCHOR121
	.word	.LANCHOR110
	.word	.LANCHOR74
	.word	.LANCHOR31
	.word	.LANCHOR197
	.word	.LANCHOR190
	.word	.LANCHOR19
	.word	.LANCHOR199
	.word	.LC156
	.word	.LANCHOR111
	.word	.LANCHOR12
	.word	1162432070
	.word	.LC158
	.word	.LANCHOR72
	.word	.LC157
	.word	.LANCHOR131
	.size	ftl_ext_info_init, .-ftl_ext_info_init
	.section	.text.ftl_prog_ppa_page,"ax",%progbits
	.align	1
	.global	ftl_prog_ppa_page
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	ftl_prog_ppa_page, %function
ftl_prog_ppa_page:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r0, r1, r2, r4, r5, r6, r7, lr}
	ldr	r4, .L2982
	ldrb	r7, [r4]	@ zero_extendqisi2
	movs	r4, #1
	str	r3, [sp]
	mov	r3, r2
	mov	r2, r1
	rsb	r5, r7, #24
	lsl	r6, r4, r5
	lsls	r4, r4, r7
	lsr	r5, r0, r5
	subs	r4, r4, #1
	subs	r6, r6, #1
	ands	r4, r4, r5
	and	r1, r6, r0
	uxtb	r0, r4
	bl	ftl_prog_page
	add	sp, sp, #12
	@ sp needed
	pop	{r4, r5, r6, r7, pc}
.L2983:
	.align	2
.L2982:
	.word	.LANCHOR31
	.size	ftl_prog_ppa_page, .-ftl_prog_ppa_page
	.section	.text.ftl_write_last_log_page,"ax",%progbits
	.align	1
	.global	ftl_write_last_log_page
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	ftl_write_last_log_page, %function
ftl_write_last_log_page:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r3, r4, r5, r6, r7, lr}
	mov	r4, r0
	ldrh	r3, [r0, #6]
	cmp	r3, #1
	bne	.L2987
	ldr	r3, .L2989
	ldrh	r7, [r0, #12]
	ldr	r5, [r3]
	bl	ftl_get_new_free_page
	adds	r3, r0, #1
	mov	r6, r0
	beq	.L2988
	ldrh	r0, [r4]
	add	r5, r5, r7, lsl #2
	ldr	r4, .L2989+4
	bl	ftl_vpn_decrement
	ldr	r3, .L2989+8
	mov	r0, r5
	ldr	r2, .L2989+12
	str	r3, [r4]
	ldr	r3, .L2989+16
	ldrb	r1, [r2]	@ zero_extendqisi2
	ldrh	r3, [r3]
	muls	r1, r3, r1
	lsls	r1, r1, #2
	bl	js_hash
	ldr	r3, .L2989+20
	movs	r2, #0
	str	r0, [r4, #4]
	mov	r1, r5
	str	r2, [r4, #8]
	mov	r0, r6
	ldrb	r3, [r3]	@ zero_extendqisi2
	str	r2, [r4, #12]
	str	r2, [r4, #16]
	cmp	r3, #8
	it	hi
	strhi	r2, [r4, #20]
	ldr	r2, .L2989+4
	bl	ftl_prog_ppa_page
.L2988:
	movs	r0, #0
	pop	{r3, r4, r5, r6, r7, pc}
.L2987:
	mov	r0, #-1
	pop	{r3, r4, r5, r6, r7, pc}
.L2990:
	.align	2
.L2989:
	.word	.LANCHOR117
	.word	.LANCHOR188
	.word	-178307901
	.word	.LANCHOR79
	.word	.LANCHOR94
	.word	.LANCHOR131
	.size	ftl_write_last_log_page, .-ftl_write_last_log_page
	.section	.text.ftl_dump_write_open_sblk,"ax",%progbits
	.align	1
	.global	ftl_dump_write_open_sblk
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	ftl_dump_write_open_sblk, %function
ftl_dump_write_open_sblk:
	@ args = 0, pretend = 0, frame = 64
	@ frame_needed = 0, uses_anonymous_args = 0
	ldr	r3, .L3030
	push	{r4, r5, r6, r7, r8, r10, fp, lr}
	mov	r5, r0
	sub	sp, sp, #104
	ldrh	r3, [r3]
	cmp	r3, r0
	bls	.L2991
	ldr	r3, .L3030+4
	ldrb	r3, [r3]	@ zero_extendqisi2
	cbnz	r3, .L2993
	ldr	r3, .L3030+8
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L2991
.L2993:
	ldr	r3, .L3030+12
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L2991
	ldr	r7, .L3030+16
	lsls	r4, r5, #2
	add	r1, sp, #88
	strh	r5, [sp, #72]	@ movhi
	mov	r0, r5
	movs	r6, #0
	ldr	r3, [r7]
	add	r3, r3, r4
	ldrb	r3, [r3, #2]	@ zero_extendqisi2
	and	r3, r3, #224
	cmp	r3, #160
	itet	eq
	ldreq	r3, .L3030+20
	movne	fp, #1
	ldrbeq	fp, [r3]	@ zero_extendqisi2
	bl	ftl_get_blk_list_in_sblk
	ldr	r3, .L3030+24
	uxtb	r0, r0
	strb	r6, [sp, #77]
	strb	r0, [sp, #81]
	ldrh	r3, [r3]
	strh	r6, [sp, #74]	@ movhi
	strh	r6, [sp, #82]	@ movhi
	smulbb	r0, r3, r0
	ldr	r3, [r7]
	mov	r7, r6
	ldr	r1, [r3, r5, lsl #2]
	add	r4, r4, r3
	ldrb	r2, [r4, #2]	@ zero_extendqisi2
	strh	r0, [sp, #78]	@ movhi
	ubfx	r1, r1, #11, #8
	ldr	r0, .L3030+28
	str	r1, [sp, #4]
	mov	r1, r5
	ldrh	r3, [r3, r5, lsl #2]
	ubfx	r3, r3, #0, #11
	str	r3, [sp]
	ubfx	r3, r2, #3, #2
	lsrs	r2, r2, #5
	bl	printf
	movs	r0, #1
	bl	buf_alloc
	mov	r4, r0
	str	r6, [sp, #44]
.L2995:
	ldr	r3, .L3030+24
	uxth	r10, r6
	ldrh	r3, [r3]
	cmp	r3, r10
	bls	.L3004
	mov	r3, r10
	str	r10, [sp, #52]
	lsls	r3, r3, #1
	mov	r8, #0
	subs	r2, r3, #1
	add	r3, r3, r10
	subs	r3, r3, #1
	str	r2, [sp, #56]
	str	r3, [sp, #60]
	b	.L3007
.L3005:
	ldr	r3, [sp, #64]
	add	r2, sp, #104
	add	r3, r2, r3, lsl #1
	ldrh	r3, [r3, #-32]
	str	r3, [sp, #48]
	movw	r3, #65535
	ldr	r2, [sp, #48]
	cmp	r2, r3
	bne	.L2996
.L3003:
	adds	r7, r7, #1
	uxth	r7, r7
.L2997:
	cmp	fp, r7
	bcs	.L3005
	add	r8, r8, #1
.L3007:
	uxth	r3, r8
	str	r3, [sp, #44]
	ldr	r2, [sp, #44]
	ldrb	r3, [sp, #81]	@ zero_extendqisi2
	cmp	r3, r2
	bls	.L3006
	mov	r3, r2
	movs	r7, #1
	adds	r3, r3, #8
	str	r3, [sp, #64]
	b	.L2997
.L2996:
	ldr	r3, .L3030+32
	cmp	fp, #3
	ldr	r2, [sp, #48]
	ldrh	r3, [r3]
	mul	r3, r2, r3
	bne	.L2998
	ldr	r2, .L3030+36
	ldrb	r2, [r2]	@ zero_extendqisi2
	cbz	r2, .L2999
	ldr	r2, [sp, #60]
.L3029:
	add	r3, r3, r2
	ldr	r2, .L3030+20
	add	r3, r3, r7
	ldrb	r2, [r2]	@ zero_extendqisi2
	orr	r3, r3, r2, lsl #24
	b	.L3000
.L2999:
	uxtah	r3, r3, r6
	orr	r3, r3, r7, lsl #24
.L3000:
	str	r3, [r4, #24]
	movs	r1, #1
	mov	r0, r4
	str	r3, [sp, #68]
	bl	sblk_read_page
	ldr	r3, [r4, #36]
	cmp	r3, #512
	str	r3, [sp, #40]
	ldr	r3, [sp, #68]
	beq	.L3002
	ldr	r2, [sp, #40]
	adds	r2, r2, #1
	bne	.L3003
.L3002:
	ldr	r1, [r4, #12]
	ldr	r2, [r4, #4]
	ldr	r0, [r1, #12]
	str	r0, [sp, #32]
	ldr	r0, [r1, #8]
	str	r0, [sp, #28]
	ldr	r0, [r1, #4]
	str	r0, [sp, #24]
	ldr	r1, [r1]
	ldr	r0, .L3030+40
	str	r1, [sp, #20]
	ldr	r1, [r2, #12]
	str	r1, [sp, #16]
	ldr	r1, [r2, #8]
	str	r1, [sp, #12]
	ldr	r1, [r2, #4]
	str	r1, [sp, #8]
	ldr	r2, [r2]
	ldr	r1, [sp, #48]
	str	r2, [sp, #4]
	ldr	r2, [sp, #40]
	str	r2, [sp]
	ldr	r2, [sp, #52]
	bl	printf
	ldr	r3, [sp, #40]
	cmp	r3, #512
	bne	.L3003
.L3004:
	uxth	r2, r6
	ldr	r6, .L3030+44
	ldr	r3, [sp, #44]
	mov	r1, r5
	str	r7, [sp]
	ldr	r0, .L3030+48
	bl	printf
	ldrb	r2, [r6]	@ zero_extendqisi2
	movs	r1, #0
	ldr	r0, [r4, #4]
	ldr	fp, .L3030+64
	lsls	r2, r2, #9
	bl	ftl_memset
	ldrb	r2, [r6]	@ zero_extendqisi2
	movs	r1, #0
	ldr	r0, [r4, #12]
	lsls	r2, r2, #1
	bl	ftl_memset
.L3008:
	ldr	r3, .L3030+24
	ldrh	r3, [r3]
	cmp	r3, r10
	bls	.L3014
	lsl	r3, r10, #1
	movs	r7, #0
	str	r3, [sp, #40]
	b	.L3015
.L2998:
	cmp	fp, #2
	bne	.L3001
	ldr	r2, [sp, #56]
	b	.L3029
.L3001:
	uxtah	r3, r3, r6
	b	.L3000
.L3006:
	adds	r6, r6, #1
	b	.L2995
.L3013:
	ldr	r3, [fp]
	uxth	r8, r7
	tst	r3, #4096
	beq	.L3009
	mov	r2, r8
	mov	r1, r10
	ldr	r0, .L3030+52
	bl	printf
.L3009:
	ldr	r2, .L3030+4
	ldr	r0, .L3030+32
	ldrb	r2, [r2]	@ zero_extendqisi2
	cbz	r2, .L3010
	add	r3, sp, #104
	add	r3, r3, r8, lsl #1
	ldrh	r2, [r3, #-16]
	ldrh	r3, [r0]
	mov	r0, r4
	muls	r3, r2, r3
	orr	r3, r3, r10
	str	r3, [r4, #24]
	bl	sblk_3d_tlc_dump_prog
.L3011:
	adds	r7, r7, #1
.L3015:
	ldrb	r2, [sp, #81]	@ zero_extendqisi2
	uxth	r3, r7
	cmp	r2, r3
	bhi	.L3013
	add	r3, r10, #1
	uxth	r10, r3
	b	.L3008
.L3010:
	ldr	r1, .L3030+20
	add	r3, sp, #104
	add	r3, r3, r8, lsl #1
	ldrb	r1, [r1]	@ zero_extendqisi2
	cmp	r1, #2
	bne	.L3012
	ldrh	r2, [r3, #-16]
	ldrh	r3, [r0]
	mov	r0, r4
	muls	r3, r2, r3
	ldr	r2, [sp, #40]
	orrs	r3, r3, r2
	orr	r3, r3, #33554432
	str	r3, [r4, #24]
	bl	sblk_mlc_dump_prog
	b	.L3011
.L3012:
	ldrh	r3, [r3, #-16]
	ldrh	r1, [r0]
	movs	r0, #1
	muls	r1, r3, r1
	ldr	r3, .L3030+56
	ldrb	r3, [r3]	@ zero_extendqisi2
	orr	r1, r1, r10
	str	r1, [r4, #24]
	rsb	lr, r3, #24
	str	r2, [sp, #4]
	lsls	r0, r0, r3
	subs	r3, r0, #1
	lsr	r0, r1, lr
	lsl	ip, r3, lr
	ands	r0, r0, r3
	ldrb	r3, [r6]	@ zero_extendqisi2
	bic	r1, r1, ip
	uxtb	r0, r0
	str	r3, [sp]
	ldr	r3, [r4, #12]
	ldr	r2, [r4, #4]
	bl	flash_prog_page_en
	b	.L3011
.L3014:
	mov	r0, r4
	bl	zbuf_free
	mov	r1, r5
	ldr	r0, .L3030+60
	bl	printf
.L2991:
	add	sp, sp, #104
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r10, fp, pc}
.L3031:
	.align	2
.L3030:
	.word	.LANCHOR8
	.word	.LANCHOR83
	.word	.LANCHOR80
	.word	.LANCHOR35
	.word	.LANCHOR9
	.word	.LANCHOR78
	.word	.LANCHOR94
	.word	.LC159
	.word	.LANCHOR111
	.word	.LANCHOR36
	.word	.LC160
	.word	.LANCHOR131
	.word	.LC161
	.word	.LC162
	.word	.LANCHOR31
	.word	.LC163
	.word	.LANCHOR19
	.size	ftl_dump_write_open_sblk, .-ftl_dump_write_open_sblk
	.section	.text.gc_ink_check_sblk,"ax",%progbits
	.align	1
	.global	gc_ink_check_sblk
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	gc_ink_check_sblk, %function
gc_ink_check_sblk:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r0, r1, r4, r5, r6, r7, r8, r10, fp, lr}
	ldr	r4, .L3059
	ldrh	r3, [r4, #2106]
	ldr	r6, [r4, #2176]
	cmp	r3, #3
	bhi	.L3033
	tbb	[pc, r3]
.L3035:
	.byte	(.L3034-.L3035)/2
	.byte	(.L3036-.L3035)/2
	.byte	(.L3037-.L3035)/2
	.byte	(.L3038-.L3035)/2
	.p2align 1
.L3034:
	ldr	r5, .L3059+4
	ldrh	r3, [r5]
	cmp	r3, #7
	bls	.L3032
	ldr	r3, .L3059+8
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, #2
	bls	.L3032
	movs	r1, #0
	ldr	r0, .L3059+12
	movw	r8, #65535
	bl	_list_get_gc_head_node
	cmp	r0, r8
	beq	.L3032
	ldr	r7, .L3059+16
	ldr	r3, [r7]
	ldrh	r3, [r3, r0, lsl #2]
	ubfx	r3, r3, #0, #11
	cmp	r3, #2
	bgt	.L3032
	movs	r0, #1
	bl	buf_alloc
	str	r0, [r4, #2176]
	cbz	r0, .L3032
	mov	r2, r5
	movs	r1, #0
	ldr	r0, .L3059+12
	bl	_list_pop_index_node
	uxth	r6, r0
	mov	r5, r0
	cmp	r6, r8
	bne	.L3042
	ldr	r0, [r4, #2176]
	bl	zbuf_free
	movs	r3, #0
	str	r3, [r4, #2176]
.L3032:
	add	sp, sp, #8
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r10, fp, pc}
.L3042:
	ldr	r1, .L3059+20
	mov	r0, r6
	bl	ftl_get_blk_list_in_sblk
	movs	r3, #0
	uxth	r5, r5
	strh	r3, [r4, #2144]	@ movhi
	movs	r3, #1
	strh	r3, [r4, #2106]	@ movhi
	ldr	r3, [r7]
	strb	r0, [r4, #2151]
	strh	r6, [r4, #2142]	@ movhi
	ldrh	r3, [r3, r5, lsl #2]
	tst	r3, #1
	ldr	r3, .L3059+24
	ite	ne
	movne	r1, #85
	moveq	r1, #170
	ldrb	r2, [r3]	@ zero_extendqisi2
	ldr	r3, [r4, #2176]
	lsls	r2, r2, #9
	ldr	r0, [r3, #4]
	add	sp, sp, #8
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r10, fp, lr}
	b	ftl_memset
.L3036:
	movs	r1, #0
	ldrh	r0, [r4, #2142]
	bl	ftl_erase_sblk
	movs	r3, #2
.L3057:
	strh	r3, [r4, #2106]	@ movhi
	b	.L3032
.L3037:
	ldr	r8, .L3059+40
	movs	r7, #0
	ldr	r10, .L3059+44
	bl	sblk_wait_write_queue_completed
.L3044:
	ldrb	r2, [r4, #2151]	@ zero_extendqisi2
	uxth	r3, r7
	cmp	r2, r3
	bhi	.L3046
	ldrh	r3, [r4, #2144]
	ldr	r2, .L3059+28
	adds	r3, r3, #1
	ldrh	r2, [r2]
	uxth	r3, r3
	strh	r3, [r4, #2144]	@ movhi
	cmp	r2, r3
	bhi	.L3032
	movs	r3, #0
	strh	r3, [r4, #2144]	@ movhi
	movs	r3, #3
	b	.L3057
.L3046:
	uxth	r3, r7
	movw	r2, #65535
	add	r3, r4, r3, lsl #1
	ldrh	r3, [r3, #2158]
	cmp	r3, r2
	beq	.L3045
	ldrh	r2, [r8]
	mov	lr, #0
	ldrh	r1, [r4, #2144]
	ldr	r0, .L3059+32
	mla	r1, r3, r2, r1
	ldr	r2, [r6, #4]
	ldr	r3, [r6, #12]
	stm	r2, {r1, r10}
	str	lr, [r3]
	ldrb	r5, [r0]	@ zero_extendqisi2
	movs	r0, #1
	str	lr, [sp, #4]
	rsb	fp, r5, #24
	lsls	r0, r0, r5
	subs	r5, r0, #1
	lsr	r0, r1, fp
	lsl	ip, r5, fp
	ands	r0, r0, r5
	ldr	r5, .L3059+24
	bic	r1, r1, ip
	uxtb	r0, r0
	ldrb	r5, [r5]	@ zero_extendqisi2
	str	r5, [sp]
	bl	flash_prog_page_en
.L3045:
	adds	r7, r7, #1
	b	.L3044
.L3038:
	ldr	r10, .L3059+40
	mov	fp, #0
	movw	r8, #65535
	bl	sblk_wait_write_queue_completed
.L3047:
	ldrb	r2, [r4, #2151]	@ zero_extendqisi2
	uxth	r3, fp
	cmp	r2, r3
	bhi	.L3051
	ldrh	r3, [r4, #2144]
	ldr	r2, .L3059+28
	adds	r3, r3, #1
	ldrh	r2, [r2]
	uxth	r3, r3
	strh	r3, [r4, #2144]	@ movhi
	cmp	r2, r3
	bhi	.L3032
	movs	r5, #0
	ldr	r0, [r4, #2176]
	strh	r5, [r4, #2106]	@ movhi
	bl	zbuf_free
	ldrh	r3, [r4, #2108]
	str	r5, [r4, #2176]
	cmp	r3, #15
	bhi	.L3052
	adds	r2, r3, #1
	add	r3, r4, r3, lsl #1
	strh	r2, [r4, #2108]	@ movhi
	ldrh	r2, [r4, #2142]
	strh	r2, [r3, #2110]	@ movhi
.L3053:
	ldrh	r2, [r4, #2108]
	ldrh	r1, [r4, #2142]
	ldr	r0, .L3059+36
	add	sp, sp, #8
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r10, fp, lr}
	b	printf
.L3051:
	uxth	r5, fp
	adds	r5, r5, #8
	add	r5, r4, r5, lsl #1
	ldrh	r3, [r5, #2142]
	cmp	r3, r8
	beq	.L3049
	ldrh	r2, [r4, #2144]
	movs	r1, #1
	ldrh	r7, [r10]
	mov	r0, r6
	mla	r7, r3, r7, r2
	str	r7, [r6, #24]
	bl	sblk_read_page
	ldr	r3, [r6, #4]
	ldr	r3, [r3]
	cmp	r7, r3
	beq	.L3049
	mov	r0, r7
	bl	ftl_mask_bad_block
	strh	r8, [r5, #2142]	@ movhi
.L3049:
	add	fp, fp, #1
	b	.L3047
.L3052:
	ldrh	r0, [r4, #2142]
	bl	zftl_insert_free_list
	b	.L3053
.L3033:
	movs	r3, #0
	b	.L3057
.L3060:
	.align	2
.L3059:
	.word	.LANCHOR70
	.word	.LANCHOR107
	.word	.LANCHOR57
	.word	.LANCHOR108
	.word	.LANCHOR9
	.word	.LANCHOR70+2158
	.word	.LANCHOR131
	.word	.LANCHOR94
	.word	.LANCHOR31
	.word	.LC164
	.word	.LANCHOR111
	.word	1437269760
	.size	gc_ink_check_sblk, .-gc_ink_check_sblk
	.section	.text.ftl_ink_check_sblk,"ax",%progbits
	.align	1
	.global	ftl_ink_check_sblk
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	ftl_ink_check_sblk, %function
ftl_ink_check_sblk:
	@ args = 0, pretend = 0, frame = 40
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, r8, r10, fp, lr}
	mov	r1, r0
	ldr	r5, .L3079
	sub	sp, sp, #48
	mov	r4, r0
	ldr	r2, [r5]
	ldr	r3, [r2, r0, lsl #2]
	ldrh	r2, [r2, r0, lsl #2]
	ldr	r0, .L3079+4
	ubfx	r3, r3, #11, #8
	ubfx	r2, r2, #0, #11
	bl	printf
	movw	r3, #65535
	str	r5, [sp, #8]
	cmp	r4, r3
	beq	.L3061
	ldr	r3, .L3079+8
	ldrh	r3, [r3]
	cmp	r3, r4
	bls	.L3061
	movs	r1, #0
	mov	r0, r4
	bl	ftl_erase_sblk
	add	r1, sp, #32
	mov	r0, r4
	strh	r4, [sp, #16]	@ movhi
	movs	r6, #0
	bl	ftl_get_blk_list_in_sblk
	strb	r0, [sp, #25]
	movs	r0, #1
	bl	buf_alloc
	ldr	r3, [sp, #8]
	mov	r5, r0
	ldr	r7, .L3079+12
	ldr	r0, [r0, #4]
	ldr	r3, [r3]
	ldrb	r2, [r7]	@ zero_extendqisi2
	ldrh	r3, [r3, r4, lsl #2]
	lsls	r2, r2, #9
	ubfx	r3, r3, #0, #11
	cmp	r3, #1
	ite	le
	movle	r1, #85
	movgt	r1, #170
	bl	ftl_memset
	bl	sblk_wait_write_queue_completed
.L3065:
	ldr	r3, .L3079+16
	uxth	r2, r6
	mov	r8, #0
	ldrh	r1, [r3]
	str	r3, [sp, #12]
	cmp	r1, r2
	bhi	.L3069
.L3070:
	ldr	r3, [sp, #12]
	ldrh	r1, [r3]
	uxth	r3, r8
	cmp	r1, r3
	bls	.L3075
	mov	fp, #0
	movw	r10, #65535
	b	.L3076
.L3067:
	uxth	r3, r8
	add	r2, sp, #48
	add	r3, r2, r3, lsl #1
	movw	r2, #65535
	ldrh	r3, [r3, #-16]
	cmp	r3, r2
	beq	.L3066
	ldr	r2, .L3079+20
	uxth	r1, r6
	ldr	r0, .L3079+24
	mov	r10, #0
	ldrh	r2, [r2]
	mla	r1, r3, r2, r1
	ldr	r2, [r5, #4]
	ldr	r3, .L3079+28
	str	r3, [r2, #4]
	ldr	r3, [r5, #12]
	str	r1, [r2]
	str	r10, [r3]
	ldrb	ip, [r0]	@ zero_extendqisi2
	movs	r0, #1
	str	r10, [sp, #4]
	rsb	fp, ip, #24
	lsl	r0, r0, ip
	add	ip, r0, #-1
	lsr	r0, r1, fp
	lsl	lr, ip, fp
	and	r0, r0, ip
	ldrb	ip, [r7]	@ zero_extendqisi2
	bic	r1, r1, lr
	uxtb	r0, r0
	str	ip, [sp]
	bl	flash_prog_page_en
.L3066:
	add	r8, r8, #1
.L3069:
	ldrb	r2, [sp, #25]	@ zero_extendqisi2
	uxth	r3, r8
	cmp	r2, r3
	bhi	.L3067
	adds	r6, r6, #1
	b	.L3065
.L3074:
	uxth	r6, fp
	add	r3, sp, #48
	adds	r6, r6, #8
	add	r6, r3, r6, lsl #1
	ldrh	r1, [r6, #-32]
	cmp	r1, r10
	beq	.L3072
	ldr	r3, .L3079+20
	uxth	r0, r8
	ldrh	r7, [r3]
	mla	r7, r1, r7, r0
	movs	r1, #1
	mov	r0, r5
	str	r7, [r5, #24]
	bl	sblk_read_page
	ldr	r1, [r5, #4]
	ldr	r1, [r1]
	cmp	r7, r1
	beq	.L3072
	mov	r0, r7
	bl	ftl_mask_bad_block
	strh	r10, [r6, #-32]	@ movhi
.L3072:
	add	fp, fp, #1
.L3076:
	ldrb	r0, [sp, #25]	@ zero_extendqisi2
	uxth	r1, fp
	cmp	r0, r1
	bhi	.L3074
	add	r8, r8, #1
	b	.L3070
.L3075:
	mov	r0, r5
	bl	zbuf_free
	ldr	r3, [sp, #8]
	mov	r1, r4
	ldr	r0, .L3079+32
	ldr	r2, [r3]
	ldr	r3, [r2, r4, lsl #2]
	ldrh	r2, [r2, r4, lsl #2]
	ubfx	r3, r3, #11, #8
	ubfx	r2, r2, #0, #11
	bl	printf
.L3061:
	add	sp, sp, #48
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r10, fp, pc}
.L3080:
	.align	2
.L3079:
	.word	.LANCHOR9
	.word	.LC165
	.word	.LANCHOR8
	.word	.LANCHOR131
	.word	.LANCHOR94
	.word	.LANCHOR111
	.word	.LANCHOR31
	.word	1437269760
	.word	.LC166
	.size	ftl_ink_check_sblk, .-ftl_ink_check_sblk
	.section	.text.ftl_alloc_sblk,"ax",%progbits
	.align	1
	.global	ftl_alloc_sblk
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	ftl_alloc_sblk, %function
ftl_alloc_sblk:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r3, r4, r5, r6, r7, r8, r10, lr}
	uxth	r5, r0
	cmp	r0, #5
	mov	r10, r0
	mov	r1, r5
	mov	r0, #0
	ite	ne
	movne	r7, #0
	moveq	r7, #2
	bl	zftl_get_free_sblk
	movw	r3, #65535
	mov	r4, r0
	cmp	r0, r3
	beq	.L3083
	ldr	r6, .L3094
	lsl	r8, r0, #2
	ldr	r5, [r6]
	add	r5, r5, r8
	ldrb	r3, [r5, #2]	@ zero_extendqisi2
	tst	r3, #224
	beq	.L3084
	mov	r2, #1012
	ldr	r1, .L3094+4
	ldr	r0, .L3094+8
	bl	printf
.L3084:
	ldrb	r3, [r5, #2]	@ zero_extendqisi2
	bfi	r3, r10, #5, #3
	uxtb	r3, r3
	ubfx	r2, r3, #3, #2
	orrs	r2, r2, r7
	bfi	r3, r2, #3, #2
	strb	r3, [r5, #2]
	uxtb	r3, r3
	and	r2, r3, #24
	cmp	r2, #24
	bne	.L3085
	cbnz	r7, .L3085
	movs	r2, #1
	bfi	r3, r2, #3, #2
	strb	r3, [r5, #2]
.L3085:
	ldr	r3, .L3094+12
	ldr	r3, [r3]
	ldrh	r3, [r3, #150]
	cbz	r3, .L3086
	ldr	r3, [r6]
	ldrh	r3, [r3, r8]
	ubfx	r3, r3, #0, #11
	cbnz	r3, .L3086
	cbnz	r7, .L3086
	mov	r0, r4
	bl	ftl_ink_check_sblk
.L3086:
	mov	r0, r4
	pop	{r3, r4, r5, r6, r7, r8, r10, pc}
.L3083:
	bl	print_ftl_debug_info
	mov	r2, r10
	mov	r1, r4
	ldr	r0, .L3094+16
	bl	printf
	mov	r1, r5
	movs	r0, #0
	bl	zftl_get_free_sblk
	mov	r2, r10
	mov	r1, r0
	mov	r4, r0
	ldr	r0, .L3094+16
	bl	printf
	bl	dump_all_list_info
	movw	r2, #1031
	ldr	r1, .L3094+4
	ldr	r0, .L3094+8
	bl	printf
	b	.L3086
.L3095:
	.align	2
.L3094:
	.word	.LANCHOR9
	.word	.LANCHOR200
	.word	.LC0
	.word	.LANCHOR110
	.word	.LC167
	.size	ftl_alloc_sblk, .-ftl_alloc_sblk
	.section	.text.ftl_open_sblk_init,"ax",%progbits
	.align	1
	.global	ftl_open_sblk_init
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	ftl_open_sblk_init, %function
ftl_open_sblk_init:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r3, r4, r5, r6, r7, r8, r10, lr}
	mov	r4, r0
	ldr	r8, .L3103+12
	mov	r6, r1
	movs	r7, #0
.L3097:
	movw	r10, #65535
.L3098:
	mov	r0, r6
	bl	ftl_alloc_sblk
	cmp	r0, r10
	mov	r5, r0
	beq	.L3098
	movs	r1, #0
	ldr	r10, .L3103+16
	bl	ftl_erase_sblk
	add	r1, r4, #16
	mov	r0, r5
	bl	ftl_get_blk_list_in_sblk
	ldr	r1, .L3103
	cmp	r6, #2
	ldrh	r2, [r8]
	uxtb	r0, r0
	strh	r5, [r4]	@ movhi
	ite	eq
	moveq	r3, #0
	ldrbne	r3, [r1]	@ zero_extendqisi2
	ldrb	r1, [r1]	@ zero_extendqisi2
	strb	r0, [r4, #9]
	smulbb	r0, r0, r2
	strh	r7, [r4, #2]	@ movhi
	it	ne
	smulbbne	r3, r3, r2
	strb	r7, [r4, #5]
	mul	r2, r2, r1
	ldr	r1, .L3103+4
	strh	r0, [r4, #6]	@ movhi
	it	ne
	uxthne	r3, r3
	strh	r7, [r4, #10]	@ movhi
	ldr	r0, [r1]
	movs	r1, #255
	strh	r3, [r4, #12]	@ movhi
	lsls	r2, r2, #2
	strb	r6, [r4, #4]
	add	r0, r0, r3, lsl #2
	bl	ftl_memset
	ldr	r3, [r10]
	ldrh	r2, [r4, #6]
	strh	r2, [r3, r5, lsl #1]	@ movhi
	ldrb	r3, [r4, #9]	@ zero_extendqisi2
	cbnz	r3, .L3096
	mov	r1, r5
	ldr	r0, .L3103+8
	bl	printf
	ldr	r3, [r10]
	movw	r2, #65535
	strh	r2, [r3, r5, lsl #1]	@ movhi
	movs	r3, #7
	strb	r3, [r4, #4]
	b	.L3097
.L3096:
	pop	{r3, r4, r5, r6, r7, r8, r10, pc}
.L3104:
	.align	2
.L3103:
	.word	.LANCHOR79
	.word	.LANCHOR117
	.word	.LC168
	.word	.LANCHOR94
	.word	.LANCHOR11
	.size	ftl_open_sblk_init, .-ftl_open_sblk_init
	.section	.text.ftl_low_format_data_init,"ax",%progbits
	.align	1
	.global	ftl_low_format_data_init
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	ftl_low_format_data_init, %function
ftl_low_format_data_init:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r3, r4, r5, r6, r7, lr}
	mov	r2, #16384
	ldr	r3, .L3107
	movs	r1, #0
	ldr	r5, .L3107+4
	ldr	r0, [r3]
	bl	ftl_memset
	bl	zftl_sblk_list_init
	movs	r0, #1
	bl	ftl_alloc_sblk
	movs	r1, #0
	mov	r6, r0
	bl	ftl_erase_sblk
	ldr	r1, [r5]
	mov	r0, r6
	add	r1, r1, #672
	bl	ftl_get_blk_list_in_sblk
	ldr	r3, [r5]
	movs	r2, #0
	ldrh	r7, [r3, #672]
	strh	r2, [r3, #690]	@ movhi
	movw	r2, #65533
	subs	r3, r7, #1
	uxth	r3, r3
	cmp	r3, r2
	bls	.L3106
	movw	r2, #2484
	ldr	r1, .L3107+8
	ldr	r0, .L3107+12
	bl	printf
.L3106:
	ldr	r0, [r5]
	movs	r4, #0
	mov	r2, #256
	movs	r1, #255
	strh	r4, [r0, #696]	@ movhi
	add	r0, r0, #416
	bl	ftl_memset
	ldr	r0, [r5]
	mov	r1, r4
	mov	r2, #4096
	add	r0, r0, #704
	bl	ftl_memset
	ldr	r3, .L3107+16
	ldr	r1, .L3107+20
	ldr	r2, [r5]
	ldrb	r3, [r3]	@ zero_extendqisi2
	ldrh	r1, [r1]
	strh	r7, [r2, #692]	@ movhi
	rsb	r3, r3, #24
	strh	r6, [r2, #416]	@ movhi
	subs	r3, r3, r1
	asr	r3, r7, r3
	ldr	r7, .L3107+24
	strh	r3, [r2, #694]	@ movhi
	movs	r3, #1
	strh	r3, [r2, #688]	@ movhi
	ldr	r3, .L3107+28
	ldrh	r3, [r3]
	strh	r3, [r2, #698]	@ movhi
	ldr	r2, .L3107+32
	ldr	r3, [r7]
	str	r2, [r3]
	bl	ftl_alloc_sys_blk
	mov	r1, r4
	mov	r6, r0
	bl	ftl_erase_phy_blk
	ldr	r3, [r5]
	movs	r1, #2
	ldr	r0, [r7]
	strh	r6, [r3, #130]	@ movhi
	movw	r6, #65535
	strh	r4, [r3, #140]	@ movhi
	adds	r0, r0, #16
	strh	r6, [r0, #568]	@ movhi
	strh	r6, [r0, #570]	@ movhi
	strh	r6, [r0, #572]	@ movhi
	strh	r6, [r0, #574]	@ movhi
	bl	ftl_open_sblk_init
	ldr	r0, [r7]
	movs	r1, #3
	adds	r0, r0, #48
	bl	ftl_open_sblk_init
	ldr	r3, [r5]
	movs	r1, #255
	ldr	r0, [r7]
	ldrh	r2, [r3, #134]
	adds	r0, r0, #136
	strh	r4, [r0, #-12]	@ movhi
	strh	r4, [r0, #-16]	@ movhi
	strh	r2, [r0, #-10]	@ movhi
	mov	r2, #-1
	strh	r4, [r0, #-14]	@ movhi
	strh	r6, [r0, #-56]	@ movhi
	strh	r6, [r0, #-6]	@ movhi
	str	r2, [r0, #408]
	strh	r2, [r3, #126]	@ movhi
	mov	r2, #256
	str	r4, [r0, #384]
	str	r4, [r0, #388]
	str	r4, [r0, #392]
	bl	ftl_memset
	ldr	r0, [r7]
	movs	r2, #128
	movs	r1, #255
	add	r0, r0, #392
	bl	ftl_memset
	bl	ftl_ext_info_flush
	mov	r0, r4
	bl	ftl_info_flush
	bl	ftl_info_blk_init
	mov	r0, r4
	pop	{r3, r4, r5, r6, r7, pc}
.L3108:
	.align	2
.L3107:
	.word	.LANCHOR197
	.word	.LANCHOR110
	.word	.LANCHOR201
	.word	.LC0
	.word	.LANCHOR31
	.word	.LANCHOR74
	.word	.LANCHOR12
	.word	.LANCHOR202
	.word	1162432070
	.size	ftl_low_format_data_init, .-ftl_low_format_data_init
	.section	.text.ftl_low_format,"ax",%progbits
	.align	1
	.global	ftl_low_format
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	ftl_low_format, %function
ftl_low_format:
	@ args = 0, pretend = 0, frame = 32
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, r8, r10, fp, lr}
	movs	r4, #8
	ldr	r6, .L3146
	sub	sp, sp, #40
	movs	r1, #0
	ldr	r0, .L3146+4
	bl	printf
.L3112:
	ldr	r3, [r6]
	add	r3, r3, r4
	ldrb	r5, [r3, #32]	@ zero_extendqisi2
	cmp	r5, #128
	ble	.L3110
	cmp	r5, #255
	beq	.L3111
	movw	r2, #2539
	ldr	r1, .L3146+8
	ldr	r0, .L3146+12
	bl	printf
.L3110:
	ldr	r3, .L3146+16
	movs	r0, #0
	ldrh	r1, [r3]
	muls	r1, r5, r1
	bl	flash_erase_block
.L3111:
	adds	r4, r4, #1
	cmp	r4, #16
	bne	.L3112
	bl	sblk_init
	bl	ftl_info_blk_init
	ldr	r3, .L3146+20
	mov	r2, #16384
	movs	r1, #0
	ldr	r0, [r3]
	bl	ftl_memset
	ldr	r2, .L3146+24
	movs	r0, #1
	ldr	r1, .L3146+28
	ldr	r3, [r2]
	ldrh	r1, [r1]
	str	r2, [sp, #24]
	add	r1, r3, r1, lsl #2
.L3113:
	cmp	r3, r1
	bne	.L3114
	ldr	r7, .L3146+32
	movs	r4, #0
	ldr	r2, .L3146+36
	ldr	r3, [r7]
	str	r2, [r3]
	strh	r4, [r3, #148]	@ movhi
.L3115:
	ldr	r3, .L3146+28
	uxth	r0, r4
	ldrh	r3, [r3]
	cmp	r3, r0
	bhi	.L3123
	ldr	r3, .L3146+40
	mov	fp, #15
	ldrb	r5, [r3]	@ zero_extendqisi2
	ldr	r3, .L3146
	mov	r1, r5
	ldr	r3, [r3]
	ldrb	r0, [r3, #47]	@ zero_extendqisi2
	bl	__aeabi_uidiv
	ldr	r3, .L3146+24
	uxtb	r0, r0
	cmp	r5, #1
	uxth	lr, r5
	add	r4, r0, #1
	ldr	r10, [r3]
	it	eq
	moveq	r8, #1
	ldr	r3, .L3146+32
	it	ne
	movne	r8, #3
	movs	r2, #0
	ldr	r6, [r3]
	ldrh	r3, [r6, #148]
.L3126:
	add	r1, r10, r2, lsl #2
	cmp	r5, #4
	add	r2, r2, #1
	ldrb	ip, [r1, #2]	@ zero_extendqisi2
	ite	ne
	strbne	r8, [r1, #3]
	strbeq	fp, [r1, #3]
	orr	ip, ip, #224
	strb	ip, [r1, #2]
	uxth	r1, r2
	cmp	r4, r1
	bhi	.L3126
	smulbb	r0, r0, lr
	add	r3, r3, lr
	mov	r1, r5
	uxtah	r0, r0, r3
	strh	r0, [r6, #148]	@ movhi
	movs	r0, #16
	bl	__aeabi_idiv
	ldr	r3, .L3146+44
	add	r0, r0, r4
	uxth	r0, r0
	ldr	r3, [r3]
	strh	r0, [r6, #134]	@ movhi
	lsls	r3, r3, #19
	bpl	.L3127
	str	r0, [sp]
	mov	r3, r4
	movs	r2, #128
	movw	r1, #2598
	ldr	r0, .L3146+48
	bl	printf
.L3127:
	ldr	r0, [r7]
	movs	r2, #128
	movs	r1, #255
	movs	r5, #0
	adds	r0, r0, #160
	bl	ftl_memset
	ldr	r3, [sp, #24]
	ldr	r0, .L3146+52
	ldr	r1, [r7]
	ldr	r3, [r3]
	ldrh	r0, [r0]
	ldrh	fp, [r1, #134]
	str	r3, [sp, #24]
	ldr	r3, .L3146+56
	ldrb	r3, [r3]	@ zero_extendqisi2
	str	r3, [sp, #28]
	ldr	r3, .L3146+40
	ldrb	r3, [r3]	@ zero_extendqisi2
	str	r3, [sp, #12]
	ldr	r3, .L3146+60
	ldrh	r7, [sp, #12]
	ldrb	r3, [r3]	@ zero_extendqisi2
	smulbb	r2, r4, r7
	rsb	r3, r3, #24
	subs	r3, r3, r0
	movs	r0, #1
	lsl	r3, r0, r3
	uxth	r2, r2
	uxth	r3, r3
	str	r3, [sp, #20]
.L3128:
	cmp	r4, fp
	bcc	.L3134
	ldr	r3, .L3146+28
	movs	r4, #0
	strh	r5, [r1, #112]	@ movhi
	strh	r4, [r1, #114]	@ movhi
	ldrh	r3, [r3]
	strh	r4, [r1, #118]	@ movhi
	strh	fp, [r1, #132]	@ movhi
	sub	r3, r3, fp
	strh	r3, [r1, #116]	@ movhi
	bl	ftl_low_format_data_init
	mov	r0, r4
	add	sp, sp, #40
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r10, fp, pc}
.L3114:
	ldrb	r2, [r3, #2]	@ zero_extendqisi2
	adds	r3, r3, #4
	and	r2, r2, #31
	bfi	r2, r0, #3, #2
	strb	r2, [r3, #-2]
	b	.L3113
.L3123:
	ldr	r3, .L3146+64
	strh	r0, [r3]	@ movhi
	ldr	r3, .L3146+68
	ldrb	r3, [r3]	@ zero_extendqisi2
	cbnz	r3, .L3116
	bl	ftl_test_block
.L3116:
	ldr	r3, .L3146+56
	uxth	r1, r4
	ldr	r0, .L3146+24
	movs	r6, #0
	mov	fp, r6
	mov	r8, r6
	ldrb	r3, [r3]	@ zero_extendqisi2
	ldr	r5, [r0]
	str	r3, [sp, #16]
	ldr	r3, .L3146+40
	add	r5, r5, r1, lsl #2
	ldrb	r3, [r3]	@ zero_extendqisi2
	uxth	r2, r3
	str	r2, [sp, #20]
	mul	r2, r3, r1
	ldr	r1, .L3146+32
	ldr	r1, [r1]
	str	r1, [sp, #12]
.L3117:
	ldr	r0, [sp, #16]
	uxth	r1, fp
	cmp	r0, r1
	bhi	.L3135
	cmp	r8, #0
	bne	.L3122
	ldrb	r3, [r5, #2]	@ zero_extendqisi2
	orr	r3, r3, #224
	strb	r3, [r5, #2]
.L3122:
	adds	r4, r4, #1
	b	.L3115
.L3120:
	add	r1, r10, r2
	ldr	r0, [sp, #28]
	str	r3, [sp, #36]
	str	r2, [sp, #32]
	bl	flash_check_bad_block
	ldr	r2, [sp, #32]
	ldr	r3, [sp, #36]
	cbz	r0, .L3118
	ldrb	r0, [r5, #3]	@ zero_extendqisi2
	movs	r1, #1
	lsl	r1, r1, r10
	orrs	r1, r1, r0
	ldr	r0, [sp, #12]
	strb	r1, [r5, #3]
	ldr	r1, [sp, #12]
	ldrh	r1, [r1, #148]
	adds	r1, r1, #1
	strh	r1, [r0, #148]	@ movhi
.L3119:
	add	r10, r10, #1
.L3121:
	sub	r1, r10, r6
	ldr	r0, [sp, #20]
	uxth	r1, r1
	cmp	r0, r1
	bhi	.L3120
	add	fp, fp, #1
	add	r6, r6, r3
	subs	r2, r2, r3
	b	.L3117
.L3118:
	add	r8, r8, #1
	uxth	r8, r8
	b	.L3119
.L3135:
	uxtb	r1, fp
	mov	r10, r6
	str	r1, [sp, #28]
	b	.L3121
.L3134:
	ldr	r3, [sp, #24]
	movs	r0, #0
	mov	lr, r0
	mov	ip, r0
	add	r8, r3, r4, lsl #2
	ldrb	r3, [r8, #2]	@ zero_extendqisi2
	orr	r3, r3, #224
	strb	r3, [r8, #2]
.L3129:
	ldr	r6, [sp, #28]
	uxth	r3, ip
	cmp	r3, r6
	bcc	.L3137
	adds	r4, r4, #1
	add	r2, r2, r7
	uxth	r4, r4
	uxth	r2, r2
	b	.L3128
.L3132:
	ldrb	r10, [r8, #3]	@ zero_extendqisi2
	add	r3, lr, r6
	asr	r10, r10, r3
	tst	r10, #1
	bne	.L3130
	ldr	r3, [sp, #12]
	add	r10, r5, #80
	adds	r5, r5, #1
	uxth	r5, r5
	cmp	r3, #1
	itett	hi
	ldrhi	r3, [sp, #16]
	movls	r3, r2
	andhi	r3, r3, #1
	addhi	r3, r3, r2
	it	hi
	uxthhi	r3, r3
	add	r3, r3, r0
	strh	r3, [r1, r10, lsl #1]	@ movhi
.L3130:
	adds	r6, r6, #1
.L3133:
	uxth	r3, r6
	cmp	r3, r7
	str	r3, [sp, #16]
	bcc	.L3132
	ldr	r3, [sp, #12]
	add	ip, ip, #1
	add	lr, lr, r3
	ldr	r3, [sp, #20]
	add	r0, r0, r3
	uxth	r0, r0
	b	.L3129
.L3137:
	movs	r6, #0
	b	.L3133
.L3147:
	.align	2
.L3146:
	.word	.LANCHOR6
	.word	.LC169
	.word	.LANCHOR203
	.word	.LC0
	.word	.LANCHOR111
	.word	.LANCHOR192
	.word	.LANCHOR9
	.word	.LANCHOR8
	.word	.LANCHOR110
	.word	1229739078
	.word	.LANCHOR75
	.word	.LANCHOR19
	.word	.LC170
	.word	.LANCHOR74
	.word	.LANCHOR112
	.word	.LANCHOR31
	.word	.LANCHOR68
	.word	.LANCHOR81
	.size	ftl_low_format, .-ftl_low_format
	.section	.text.ftl_re_low_format,"ax",%progbits
	.align	1
	.global	ftl_re_low_format
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	ftl_re_low_format, %function
ftl_re_low_format:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r3, r4, r5, r6, r7, lr}
	movs	r1, #1
	ldr	r0, .L3154
	bl	printf
	bl	sblk_init
	bl	ftl_info_blk_init
	bl	ftl_ext_info_init
	ldr	r2, .L3154+4
	ldr	r3, .L3154+8
	ldrh	r7, [r2]
	ldr	r3, [r3]
	ldr	r2, .L3154+12
	ldrh	r1, [r3, #134]
	ldr	r0, [r2]
	movs	r2, #0
	mov	r5, r2
	mov	r6, r2
	add	r0, r0, r1, lsl #2
.L3149:
	cmp	r1, r7
	bcc	.L3153
	movs	r4, #0
	strh	r6, [r3, #114]	@ movhi
	strh	r5, [r3, #118]	@ movhi
	strh	r2, [r3, #116]	@ movhi
	strh	r4, [r3, #122]	@ movhi
	strh	r4, [r3, #120]	@ movhi
	strh	r4, [r3, #124]	@ movhi
	bl	ftl_low_format_data_init
	mov	r0, r4
	pop	{r3, r4, r5, r6, r7, pc}
.L3153:
	ldrb	r4, [r0, #2]	@ zero_extendqisi2
	bfc	r4, #5, #3
	strb	r4, [r0, #2]
	ands	r4, r4, #24
	bne	.L3150
	adds	r6, r6, #1
	uxth	r6, r6
.L3151:
	adds	r1, r1, #1
	uxth	r1, r1
	adds	r0, r0, #4
	b	.L3149
.L3150:
	cmp	r4, #16
	itete	eq
	addeq	r5, r5, #1
	addne	r2, r2, #1
	uxtheq	r5, r5
	uxthne	r2, r2
	b	.L3151
.L3155:
	.align	2
.L3154:
	.word	.LC171
	.word	.LANCHOR8
	.word	.LANCHOR110
	.word	.LANCHOR9
	.size	ftl_re_low_format, .-ftl_re_low_format
	.section	.text.pm_alloc_new_blk,"ax",%progbits
	.align	1
	.global	pm_alloc_new_blk
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	pm_alloc_new_blk, %function
pm_alloc_new_blk:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r0, r1, r4, r5, r6, r7, r8, lr}
	ldr	r5, .L3174
	ldr	r1, .L3174+4
	ldr	r2, [r5]
	ldrb	r1, [r1]	@ zero_extendqisi2
	ldrh	r3, [r2, #690]
	adds	r3, r3, #1
	uxth	r3, r3
	cmp	r1, r3
	strh	r3, [r2, #690]	@ movhi
	bls	.L3157
	add	r3, r3, #336
	ldrh	r2, [r2, r3, lsl #1]
	movw	r3, #65535
	cmp	r2, r3
	bne	.L3158
.L3157:
	ldr	r7, .L3174+8
	ldr	r4, .L3174+12
.L3172:
	movw	r8, #65535
.L3159:
	movs	r0, #1
	bl	ftl_alloc_sblk
	cmp	r0, r8
	mov	r6, r0
	beq	.L3159
	movs	r1, #0
	bl	ftl_erase_sblk
	ldr	r1, [r5]
	mov	r0, r6
	add	r1, r1, #672
	bl	ftl_get_blk_list_in_sblk
	uxth	r0, r0
	cbnz	r0, .L3160
	mov	r1, r6
	mov	r0, r7
	bl	printf
	ldr	r3, [r4]
	add	r6, r3, r6, lsl #2
	ldrb	r3, [r6, #2]	@ zero_extendqisi2
	orr	r3, r3, #224
	strb	r3, [r6, #2]
	b	.L3172
.L3160:
	ldr	r3, [r5]
	movs	r1, #1
	ldr	r2, .L3174+16
	movs	r4, #0
	strh	r4, [r3, #690]	@ movhi
	add	r3, r3, #416
	str	r1, [r2]
	movw	r1, #65535
.L3162:
	ldrh	r0, [r3], #2
	uxth	r2, r4
	cmp	r0, r1
	beq	.L3161
	adds	r4, r4, #1
	cmp	r4, #128
	bne	.L3162
	mov	r2, #264
	ldr	r1, .L3174+20
	ldr	r0, .L3174+24
	bl	printf
	mov	r2, r4
.L3161:
	ldr	r3, [r5]
	adds	r2, r2, #208
	strh	r6, [r3, r2, lsl #1]	@ movhi
	ldrh	r2, [r3, #688]
	adds	r2, r2, #1
	strh	r2, [r3, #688]	@ movhi
.L3158:
	ldr	r2, [r5]
	ldrh	r3, [r2, #690]
	add	r3, r3, #336
	ldrh	r4, [r2, r3, lsl #1]
	movw	r2, #65533
	subs	r3, r4, #1
	uxth	r3, r3
	cmp	r3, r2
	bls	.L3164
	mov	r2, #270
	ldr	r1, .L3174+20
	ldr	r0, .L3174+24
	bl	printf
.L3164:
	ldr	r1, [r5]
	movs	r3, #0
	strh	r3, [r1, #696]	@ movhi
	ldr	r3, .L3174+28
	strh	r4, [r1, #692]	@ movhi
	ldrb	r2, [r3]	@ zero_extendqisi2
	ldr	r3, .L3174+32
	rsb	r2, r2, #24
	ldrh	r3, [r3]
	subs	r2, r2, r3
	asr	r3, r4, r2
	strh	r3, [r1, #694]	@ movhi
	ldr	r1, .L3174+36
	ldr	r1, [r1]
	lsls	r1, r1, #19
	bpl	.L3168
	movs	r1, #1
	uxth	r3, r3
	lsl	r2, r1, r2
	ldr	r0, .L3174+40
	str	r3, [sp]
	mov	r1, r4
	mov	r3, r4
	subs	r2, r2, #1
	bl	printf
.L3168:
	movs	r0, #0
	add	sp, sp, #8
	@ sp needed
	pop	{r4, r5, r6, r7, r8, pc}
.L3175:
	.align	2
.L3174:
	.word	.LANCHOR110
	.word	.LANCHOR79
	.word	.LC168
	.word	.LANCHOR9
	.word	.LANCHOR204
	.word	.LANCHOR205
	.word	.LC0
	.word	.LANCHOR31
	.word	.LANCHOR74
	.word	.LANCHOR19
	.word	.LC172
	.size	pm_alloc_new_blk, .-pm_alloc_new_blk
	.section	.text.pm_write_page,"ax",%progbits
	.align	1
	.global	pm_write_page
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	pm_write_page, %function
pm_write_page:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r0, r1, r2, r3, r4, r5, r6, r7, r8, r10, fp, lr}
	mov	r4, r0
	ldr	r8, .L3189+28
	mov	r7, r1
	mov	r6, r8
.L3177:
	ldr	r3, [r8]
	ldr	r2, [r3, #48]
	ldrh	r1, [r3, #696]
	adds	r2, r2, #1
	str	r2, [r3, #48]
	ldr	r2, .L3189
	ldrh	r2, [r2]
	cmp	r1, r2
	bcs	.L3178
	ldrh	r2, [r3, #692]
	movw	r3, #65535
	cmp	r2, r3
	bne	.L3179
.L3178:
	bl	pm_alloc_new_blk
	movs	r0, #0
	bl	ftl_info_flush
.L3179:
	ldr	r3, [r6]
	ldrh	r2, [r3, #692]
	movw	r3, #65535
	cmp	r2, r3
	bne	.L3180
	movw	r2, #303
	ldr	r1, .L3189+4
	ldr	r0, .L3189+8
	bl	printf
.L3180:
	ldr	r3, [r6]
	movs	r1, #0
	ldr	r2, .L3189+12
	ldr	r10, .L3189+32
	ldrh	r5, [r3, #692]
	ldrh	r2, [r2]
	ldrh	r3, [r3, #696]
	ldr	r0, [r10]
	mla	r5, r2, r5, r3
	movs	r2, #64
	bl	ftl_memset
	ldr	r10, [r10]
	mov	r0, r7
	ldr	r3, [r6]
	str	r4, [r10]
	ldr	r2, [r3, #48]
	str	r3, [sp, #12]
	str	r2, [r10, #4]
	ldr	r2, .L3189+16
	ldrb	fp, [r2]	@ zero_extendqisi2
	lsl	r1, fp, #9
	bl	js_hash
	ldr	r3, [sp, #12]
	mov	r2, r7
	str	r0, [r10, #8]
	mov	r1, r5
	ldrb	r0, [r3, #694]	@ zero_extendqisi2
	mov	r3, r10
	str	fp, [sp]
	bl	ftl_prog_page
	ldr	r2, [r6]
	ldrh	r3, [r2, #696]
	adds	r3, r3, #1
	uxth	r3, r3
	cmp	r3, #1
	strh	r3, [r2, #696]	@ movhi
	ldr	r3, .L3189+20
	beq	.L3181
	ldrb	r1, [r3]	@ zero_extendqisi2
	cbz	r1, .L3182
.L3181:
	movs	r2, #0
	strb	r2, [r3]
	b	.L3177
.L3182:
	adds	r0, r0, #1
	bne	.L3184
	mov	r1, r5
	ldr	r0, .L3189+24
	bl	printf
	b	.L3177
.L3184:
	ldrh	r3, [r2, #698]
	movs	r0, #0
	cmp	r4, r3
	itt	cc
	addcc	r4, r4, #176
	strcc	r5, [r2, r4, lsl #2]
	add	sp, sp, #16
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r10, fp, pc}
.L3190:
	.align	2
.L3189:
	.word	.LANCHOR94
	.word	.LANCHOR206
	.word	.LC0
	.word	.LANCHOR111
	.word	.LANCHOR131
	.word	.LANCHOR208
	.word	.LC173
	.word	.LANCHOR110
	.word	.LANCHOR207
	.size	pm_write_page, .-pm_write_page
	.section	.text.flash_info_flush,"ax",%progbits
	.align	1
	.global	flash_info_flush
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	flash_info_flush, %function
flash_info_flush:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r0, r1, r2, r3, r4, r5, r6, r7, r8, r10, fp, lr}
	ldr	r3, .L3203
	ldr	r3, [r3]
	lsls	r3, r3, #19
	bpl	.L3192
	ldr	r2, .L3203+4
	movw	r1, #365
	ldr	r0, .L3203+8
	bl	printf
.L3192:
	ldr	r5, .L3203+12
	movs	r2, #64
	ldr	r6, .L3203+16
	movs	r1, #0
	movs	r7, #0
	ldr	r0, [r5]
	bl	ftl_memset
	movs	r3, #16
	movs	r2, #4
	ldr	r1, [r6]
	ldr	r0, .L3203+20
	bl	rknand_print_hex
	ldr	r4, [r6]
	ldr	r1, [r4, #8]
	add	r0, r4, #16
	bl	js_hash
	str	r5, [sp, #8]
	ldr	r5, .L3203+24
	str	r0, [r4, #12]
	mov	r8, r5
.L3193:
	ldr	fp, .L3203+44
	ldrb	r10, [r5]	@ zero_extendqisi2
	ldrh	r4, [r5, #2]
	ldrh	r3, [fp]
	mov	r1, r10
	ldr	r0, .L3203+28
	mov	r2, r4
	str	r3, [sp, #12]
	bl	printf
	ldr	r2, .L3203+32
	ldrh	r0, [r5, #2]
	ldr	r3, [sp, #12]
	ldrh	r2, [r2]
	subs	r2, r2, #1
	cmp	r0, r2
	blt	.L3194
	ldr	r4, [r6]
	mov	r10, #0
	ldrb	r2, [r5]	@ zero_extendqisi2
	strh	r10, [r5, #2]	@ movhi
	ldr	r3, [r4, #4]
	mov	r0, r4
	ldr	r1, [r4, #8]
	adds	r3, r3, #1
	str	r3, [r4, #4]
	ldrb	r3, [r5, #1]	@ zero_extendqisi2
	strb	r2, [r5, #1]
	ldrh	r2, [r4, #16]
	strb	r3, [r5]
	str	r3, [sp, #12]
	adds	r2, r2, #1
	strh	r2, [r0, #16]!	@ movhi
	bl	js_hash
	ldr	r3, [sp, #12]
	str	r0, [r4, #12]
	mov	r0, r10
	ldrh	r4, [fp]
	muls	r4, r3, r4
	mov	r1, r4
.L3202:
	bl	flash_erase_block
.L3195:
	ldr	r2, [r6]
	mov	r10, #1
	ldr	r3, [sp, #8]
	movs	r0, #0
	ldr	r1, [r2, #4]
	ldr	r3, [r3]
	str	r1, [r3]
	ldr	r1, .L3203+36
	str	r1, [r3, #4]
	movs	r1, #4
	stm	sp, {r1, r10}
	mov	r1, r4
	bl	flash_prog_page_en
	ldrh	r3, [r8, #2]
	adds	r0, r0, #1
	add	r3, r3, r10
	strh	r3, [r8, #2]	@ movhi
	bne	.L3196
	mov	r1, r4
	ldr	r0, .L3203+40
	bl	printf
	b	.L3193
.L3198:
	mov	r7, r10
	b	.L3193
.L3194:
	mla	r4, r10, r3, r4
	cmp	r0, #0
	bne	.L3195
	mov	r1, r4
	b	.L3202
.L3196:
	cmp	r7, #0
	beq	.L3198
	movs	r0, #0
	add	sp, sp, #16
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r10, fp, pc}
.L3204:
	.align	2
.L3203:
	.word	.LANCHOR19
	.word	.LANCHOR209
	.word	.LC94
	.word	.LANCHOR210
	.word	.LANCHOR6
	.word	.LC174
	.word	.LANCHOR211
	.word	.LC175
	.word	.LANCHOR144
	.word	1398362953
	.word	.LC176
	.word	.LANCHOR2
	.size	flash_info_flush, .-flash_info_flush
	.section	.text.flash_info_blk_init,"ax",%progbits
	.align	1
	.global	flash_info_blk_init
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	flash_info_blk_init, %function
flash_info_blk_init:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r0, r1, r2, r3, r4, r5, r6, r7, r8, r10, fp, lr}
	ldr	r3, .L3236
	ldr	r4, .L3236+4
	ldr	r3, [r3]
	tst	r3, #4096
	beq	.L3206
	ldr	r3, [r4]
	movs	r1, #50
	ldr	r2, .L3236+8
	ldr	r0, .L3236+12
	str	r3, [sp]
	mov	r3, #2048
	bl	printf
.L3206:
	ldr	r7, .L3236+16
	mov	r8, #4
.L3210:
	movs	r6, #0
.L3209:
	ldr	r10, .L3236+32
	mov	fp, #4
	ldr	r5, .L3236+20
	movs	r0, #0
	ldr	r2, [r4]
	ldrh	r1, [r10]
	ldr	r3, [r5]
	str	fp, [sp]
	mla	r1, r8, r1, r6
	bl	flash_read_page_en
	adds	r0, r0, #1
	beq	.L3207
	ldr	r2, [r4]
	ldr	r3, [r2]
	cmp	r3, r7
	beq	.L3208
.L3207:
	adds	r6, r6, #1
	cmp	r6, #4
	bne	.L3209
	add	r8, r8, #1
	cmp	r8, #16
	bne	.L3210
.L3235:
	mov	r0, #-1
.L3205:
	add	sp, sp, #16
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r10, fp, pc}
.L3218:
	ldr	r3, [r4]
	ldr	r2, [r3]
	cmp	r2, r7
	bne	.L3219
	ldr	r8, [r3, #4]
.L3212:
	ldrh	r0, [r10]
	movs	r3, #4
	ldrb	r1, [r6, #1]	@ zero_extendqisi2
	ldr	r2, [r4]
	str	r3, [sp]
	ldr	r3, [r5]
	muls	r1, r0, r1
	movs	r0, #0
	bl	flash_read_page_en
	adds	r0, r0, #1
	beq	.L3213
	ldr	r3, [r4]
	ldr	r2, [r3]
	cmp	r2, r7
	bne	.L3213
	ldr	r2, [r3, #4]
	cmp	r8, r2
	itttt	cc
	ldrbcc	r2, [r3, #37]	@ zero_extendqisi2
	ldrbcc	r3, [r3, #36]	@ zero_extendqisi2
	strbcc	r2, [r6]
	strbcc	r3, [r6, #1]
.L3213:
	mov	r8, #4
	ldrb	r1, [r6]	@ zero_extendqisi2
	ldr	r3, [r5]
	movs	r0, #0
	str	r8, [sp]
	ldr	r2, [r4]
	bl	flash_get_last_written_page
	uxth	fp, r0
	ldrh	r10, [r10]
	add	r3, fp, #1
	strh	r3, [r6, #2]	@ movhi
	ldrb	r3, [r6]	@ zero_extendqisi2
	movs	r6, #0
	mla	r10, r10, r3, r0
.L3214:
	sub	r0, fp, r6
	sxth	r3, r0
	cmp	r3, #0
	bge	.L3217
	adds	r2, r3, #1
	bne	.L3216
	ldr	r2, [r4]
	ldr	r0, .L3236+24
	str	r3, [sp, #12]
	ldr	r1, [r2]
	bl	printf
	b	.L3235
.L3217:
	str	r8, [sp]
	sub	r1, r10, r6
	ldr	r3, [r5]
	movs	r0, #0
	ldr	r2, [r4]
	bl	flash_read_page_en
	adds	r0, r0, #1
	beq	.L3215
	ldr	r3, [r4]
	ldr	r3, [r3]
	cmp	r3, r7
	beq	.L3216
.L3215:
	adds	r6, r6, #1
	b	.L3214
.L3216:
	cmp	r6, #1
	bls	.L3220
	bl	flash_info_flush
.L3220:
	movs	r0, #0
	b	.L3205
.L3208:
	ldrb	r1, [r2, #36]	@ zero_extendqisi2
	ldrh	r0, [r10]
	ldrb	r3, [r2, #37]	@ zero_extendqisi2
	ldr	r6, .L3236+28
	strb	r1, [r6]
	muls	r1, r0, r1
	strb	r3, [r6, #1]
	movs	r0, #0
	str	fp, [sp]
	ldr	r3, [r5]
	bl	flash_read_page_en
	adds	r0, r0, #1
	bne	.L3218
.L3219:
	mov	r8, #0
	b	.L3212
.L3237:
	.align	2
.L3236:
	.word	.LANCHOR19
	.word	.LANCHOR6
	.word	.LANCHOR212
	.word	.LC177
	.word	1398362953
	.word	.LANCHOR210
	.word	.LC178
	.word	.LANCHOR211
	.word	.LANCHOR2
	.size	flash_info_blk_init, .-flash_info_blk_init
	.section	.text.nand_flash_init,"ax",%progbits
	.align	1
	.global	nand_flash_init
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	nand_flash_init, %function
nand_flash_init:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 0, uses_anonymous_args = 0
	ldr	r3, .L3331
	push	{r0, r1, r4, r5, r6, r7, r8, r10, fp, lr}
	mov	r4, r0
	mov	r8, r3
	ldr	r2, [r3]
	tst	r2, #4096
	beq	.L3239
	ldr	r2, .L3331+4
	movw	r1, #3451
	ldr	r0, .L3331+8
	bl	printf
.L3239:
	ldr	r3, .L3331+12
	movs	r6, #0
	mov	r0, r4
	ldr	r7, .L3331+16
	ldr	r5, .L3331+20
	str	r6, [r3]
	bl	nandc_init
	ldr	r3, .L3331+24
	movs	r2, #1
	ldr	r4, .L3331+28
	mov	r1, r6
	ldr	r0, .L3331+32
	strb	r2, [r3]
	movs	r3, #3
	movs	r2, #8
	strb	r3, [r7]
	str	r4, [r5]
	bl	ftl_memset
	movs	r2, #32
	mov	r1, r6
	ldr	r0, .L3331+36
	bl	ftl_memset
	str	r7, [sp]
	ldr	r7, .L3331+40
	mov	fp, r7
.L3245:
	lsl	r10, r6, #3
	uxtb	r0, r6
	add	r1, r7, r10
	bl	flash_read_id
	cbnz	r6, .L3240
	ldrb	r3, [r7]	@ zero_extendqisi2
	subs	r3, r3, #1
	uxtb	r3, r3
	cmp	r3, #253
	bls	.L3241
.L3243:
	mvn	fp, #1
.L3238:
	mov	r0, fp
	add	sp, sp, #8
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r10, fp, pc}
.L3241:
	ldrb	r3, [r7, #1]	@ zero_extendqisi2
	cmp	r3, #255
	beq	.L3243
.L3240:
	ldrb	r3, [fp, r10]	@ zero_extendqisi2
	adds	r6, r6, #1
	cmp	r3, #181
	itt	eq
	moveq	r3, #44
	strbeq	r3, [fp, r10]
	cmp	r6, #4
	bne	.L3245
	ldr	r7, .L3331+44
	movs	r6, #0
	ldr	r3, .L3331+40
.L3248:
	mov	r1, r3
	ldrb	r2, [r7, #-1]	@ zero_extendqisi2
	mov	r0, r7
	str	r3, [sp, #4]
	lsl	r10, r6, #5
	bl	flash_mem_cmp8
	ldr	r3, [sp, #4]
	cmp	r0, #0
	bne	.L3246
	ldr	r6, .L3331+48
	ldr	r3, .L3331+52
	add	r6, r6, r10
	ldrb	r2, [r6, #22]	@ zero_extendqisi2
	mov	r1, r3
.L3247:
	lsls	r7, r0, #5
	ldrb	r7, [r7, r3]	@ zero_extendqisi2
	cmp	r7, r2
	beq	.L3249
	adds	r0, r0, #1
	cmp	r0, #4
	bne	.L3247
.L3249:
	ldr	r7, .L3331+56
	add	r1, r1, r0, lsl #5
	movs	r2, #32
	ldr	r0, .L3331+60
	bl	ftl_memcpy
	movs	r2, #32
	mov	r1, r6
	ldr	r0, .L3331+28
	bl	ftl_memcpy
	ldrb	r3, [r7]	@ zero_extendqisi2
	cmp	r3, #8
	bhi	.L3250
	ldrb	r3, [r4, #20]	@ zero_extendqisi2
	cmp	r3, #60
	bls	.L3250
	movs	r3, #60
	strb	r3, [r4, #20]
.L3250:
	ldr	r3, [r8]
	lsls	r3, r3, #19
	bpl	.L3284
	ldr	r2, .L3331+4
	movw	r1, #3478
	ldr	r0, .L3331+8
	bl	printf
.L3284:
	ldr	r3, [r5]
	mov	r0, #16384
	ldr	r6, .L3331+64
	mov	r10, #0
	ldrh	r3, [r3, #10]
	cmp	r3, #1024
	ittt	cs
	ldrcs	r2, [sp]
	movcs	r3, #2
	strbcs	r3, [r2]
	bl	ftl_malloc
	ldr	r3, .L3331+68
	str	r0, [r3]
	mov	r0, #16384
	bl	ftl_malloc
	ldr	r3, .L3331+72
	str	r0, [r3]
	mov	r0, #2048
	bl	ftl_malloc
	str	r0, [r6]
	movs	r0, #64
	bl	ftl_malloc
	ldr	r3, .L3331+76
	str	r0, [r3]
	movs	r0, #64
	bl	ftl_malloc
	ldr	r3, .L3331+80
	str	r0, [r3]
	movs	r0, #64
	bl	ftl_malloc
	ldr	r3, .L3331+84
	str	r0, [r3]
	ldr	r3, .L3331+88
	strb	r10, [r3]
	bl	flash_die_info_init
	ldrb	r0, [r4, #18]	@ zero_extendqisi2
	bl	flash_lsb_page_tbl_build
	ldrb	r0, [r4, #20]	@ zero_extendqisi2
	bl	nandc_bch_sel
	ldr	r1, [r5]
	ldr	r0, .L3331+92
	ldrh	r3, [r1, #16]
	ubfx	r2, r3, #8, #3
	ubfx	r5, r3, #3, #1
	strb	r2, [r0]
	ldr	r2, .L3331+96
	strb	r5, [r2]
	ubfx	r5, r3, #4, #1
	ldr	r2, .L3331+100
	strb	r5, [r2]
	ubfx	r5, r3, #12, #1
	ldr	r2, .L3331+104
	strb	r5, [r2]
	ubfx	r5, r3, #13, #1
	ldr	r2, .L3331+108
	strb	r5, [r2]
	ubfx	r5, r3, #11, #1
	ldr	r2, .L3331+112
	strb	r5, [r2]
	ldrb	r2, [r1, #31]	@ zero_extendqisi2
	ldr	r5, .L3331+116
	ubfx	ip, r2, #1, #1
	strb	ip, [r5]
	ubfx	ip, r2, #2, #1
	ldr	r5, .L3331+120
	strb	ip, [r5]
	ubfx	ip, r3, #14, #1
	ldr	r5, .L3331+124
	lsrs	r3, r3, #15
	strb	ip, [r5]
	ldr	r5, .L3331+128
	strb	r3, [r5]
	ubfx	r5, r2, #3, #1
	ldrb	r3, [r1, #28]	@ zero_extendqisi2
	ubfx	r2, r2, #4, #1
	ldr	r1, .L3331+132
	strb	r3, [r1]
	ldr	r1, .L3331+136
	strb	r5, [r1]
	ldr	r1, .L3331+140
	ldr	r5, .L3331+144
	strb	r2, [r1]
	movs	r2, #60
	ldr	r1, .L3331+148
	str	r10, [r5]
	mov	r10, r0
	strb	r2, [r1]
	ldrb	r2, [r7]	@ zero_extendqisi2
	ldr	r7, .L3331+152
	cmp	r2, #9
	strb	r3, [r7]
	it	eq
	moveq	r0, #70
	ldrb	r3, [r4, #31]	@ zero_extendqisi2
	it	eq
	strbeq	r0, [r1]
	lsls	r3, r3, #31
	bpl	.L3253
	ldrb	r3, [r4, #29]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L3254
	movs	r3, #2
.L3324:
	strb	r3, [r7]
.L3253:
	cmp	r2, #8
	bne	.L3255
	ldrb	r3, [fp]	@ zero_extendqisi2
	cmp	r3, #44
	beq	.L3256
	cmp	r3, #137
	bne	.L3255
.L3256:
	ldrb	r3, [r4, #28]	@ zero_extendqisi2
	cmp	r3, #3
	itt	eq
	moveq	r3, #0
	strbeq	r3, [r7]
.L3255:
	ldrh	r1, [r4, #16]
	ldr	r2, .L3331+156
	ldrb	r3, [r4, #19]	@ zero_extendqisi2
	tst	r1, #64
	str	r2, [sp]
	strb	r3, [r2]
	beq	.L3258
	sub	r2, r3, #17
	cmp	r2, #2
	bls	.L3259
	cmp	r3, #21
	bne	.L3260
.L3259:
	ldr	r2, .L3331+160
	cmp	r3, #21
	ldr	r3, .L3331+164
	str	r2, [r5]
	beq	.L3328
	movs	r2, #15
.L3326:
	strb	r2, [r3]
.L3258:
	ldr	r3, [r8]
	lsls	r0, r3, #19
	bpl	.L3272
	ldr	r2, .L3331+4
	movw	r1, #3571
	ldr	r0, .L3331+8
	bl	printf
.L3272:
	ldr	r3, .L3331+168
	movs	r2, #0
	strb	r2, [r3]
	ldrb	r2, [r10]	@ zero_extendqisi2
	str	r3, [sp, #4]
	tst	r2, #1
	beq	.L3273
	ldrb	r3, [fp]	@ zero_extendqisi2
	cmp	r3, #155
	beq	.L3274
	movs	r0, #4
	bl	flash_set_interface_mode
	movs	r0, #4
	bl	nandc_set_if_mode
.L3274:
	movs	r0, #1
	bl	flash_set_interface_mode
	movs	r0, #1
.L3327:
	bl	nandc_set_if_mode
	bl	flash_info_blk_init
	cmp	r0, #-1
	mov	fp, r0
	bne	.L3276
	ldr	r3, [r6]
	movs	r2, #17
	movs	r0, #0
	strb	r2, [r3, #32]
	ldr	r3, .L3331+172
	strb	r0, [r3]
	bl	zftl_flash_exit_slc_mode
	b	.L3238
.L3246:
	adds	r6, r6, #1
	adds	r7, r7, #32
	cmp	r6, #49
	bne	.L3248
	b	.L3243
.L3254:
	movs	r3, #3
	b	.L3324
.L3332:
	.align	2
.L3331:
	.word	.LANCHOR19
	.word	.LANCHOR213
	.word	.LC94
	.word	.LANCHOR169
	.word	.LANCHOR31
	.word	.LANCHOR21
	.word	.LANCHOR23
	.word	.LANCHOR32
	.word	.LANCHOR29
	.word	.LANCHOR145
	.word	.LANCHOR47
	.word	.LANCHOR214+1
	.word	.LANCHOR214
	.word	.LANCHOR215
	.word	.LANCHOR27
	.word	.LANCHOR25
	.word	.LANCHOR6
	.word	.LANCHOR173
	.word	.LANCHOR163
	.word	.LANCHOR172
	.word	.LANCHOR165
	.word	.LANCHOR210
	.word	.LANCHOR216
	.word	.LANCHOR48
	.word	.LANCHOR183
	.word	.LANCHOR44
	.word	.LANCHOR83
	.word	.LANCHOR80
	.word	.LANCHOR35
	.word	.LANCHOR124
	.word	.LANCHOR217
	.word	.LANCHOR1
	.word	.LANCHOR81
	.word	.LANCHOR0
	.word	.LANCHOR30
	.word	.LANCHOR36
	.word	.LANCHOR171
	.word	.LANCHOR22
	.word	.LANCHOR24
	.word	.LANCHOR15
	.word	micron_read_retrial
	.word	.LANCHOR166
	.word	.LANCHOR26
	.word	.LANCHOR33
.L3260:
	cmp	r3, #33
	beq	.L3263
	sub	r2, r3, #65
	cmp	r2, #1
	bhi	.L3264
.L3263:
	ldr	r3, .L3333
	movs	r2, #4
	str	r3, [r5]
	ldr	r3, .L3333+4
	strb	r2, [r3]
.L3330:
	movs	r2, #7
.L3329:
	ldr	r3, .L3333+8
	b	.L3326
.L3264:
	sub	r2, r3, #67
	uxtb	r2, r2
	cmp	r2, #1
	bls	.L3265
	sub	r1, r3, #34
	cmp	r1, #1
	bhi	.L3266
.L3265:
	ldr	r1, .L3333
	cmp	r3, #35
	str	r1, [r5]
	ldr	r1, .L3333+8
	beq	.L3267
	cmp	r3, #68
	beq	.L3267
	movs	r3, #7
.L3325:
	cmp	r2, #1
	strb	r3, [r1]
	ldr	r3, .L3333+4
	bhi	.L3269
.L3328:
	movs	r2, #4
	b	.L3326
.L3267:
	movs	r3, #17
	b	.L3325
.L3269:
	movs	r2, #5
	b	.L3326
.L3266:
	sub	r2, r3, #36
	cmp	r2, #1
	bhi	.L3270
	ldr	r3, .L3333+12
	str	r3, [r5]
	b	.L3330
.L3270:
	cmp	r3, #50
	bne	.L3271
	ldr	r3, .L3333+16
	movs	r2, #25
	str	r3, [r5]
	b	.L3329
.L3271:
	cmp	r3, #81
	bne	.L3258
	ldr	r3, .L3333+20
	movs	r2, #7
	str	r3, [r5]
	ldr	r3, .L3333+8
	strb	r2, [r3]
	movs	r2, #0
	ldr	r3, .L3333+24
	b	.L3326
.L3273:
	movs	r0, #4
	b	.L3327
.L3276:
	ldrb	r3, [r4, #7]	@ zero_extendqisi2
	cmp	r3, #9
	bne	.L3277
	ldr	r3, [r6]
	ldrb	r3, [r3, #20]	@ zero_extendqisi2
	cmp	r3, #1
	itt	ne
	movne	r3, #0
	strbne	r3, [r7]
.L3277:
	ldr	r3, [sp]
	ldrb	r3, [r3]	@ zero_extendqisi2
	subs	r3, r3, #1
	cmp	r3, #7
	itt	ls
	ldrls	r3, .L3333+28
	strls	r3, [r5]
	ldrb	r3, [r10]	@ zero_extendqisi2
	lsls	r1, r3, #29
	bpl	.L3280
	ldr	r3, [r6]
	ldrb	r3, [r3, #19]	@ zero_extendqisi2
	cbz	r3, .L3280
	ldr	r2, .L3333+32
	movs	r0, #0
	ldr	r3, .L3333+36
	ldrh	r1, [r2]
	ldrb	r3, [r3]	@ zero_extendqisi2
	muls	r1, r3, r1
	bl	flash_ddr_para_scan
	ldr	r3, [sp, #4]
	ldrb	r3, [r3]	@ zero_extendqisi2
	cbnz	r3, .L3280
	ldr	r2, [r6]
	strb	r3, [r2, #19]
	bl	flash_info_flush
.L3280:
	ldr	r3, [r8]
	lsls	r2, r3, #19
	bpl	.L3282
	ldr	r2, .L3333+40
	movw	r1, #3674
	ldr	r0, .L3333+44
	bl	printf
.L3282:
	bl	nand_flash_print_info
	mov	fp, #0
	b	.L3238
.L3334:
	.align	2
.L3333:
	.word	toshiba_read_retrial
	.word	.LANCHOR18
	.word	.LANCHOR166
	.word	toshiba_3d_read_retrial
	.word	samsung_read_retrial
	.word	ymtc_3d_read_retrial
	.word	.LANCHOR50
	.word	hynix_read_retrial
	.word	.LANCHOR2
	.word	.LANCHOR211
	.word	.LANCHOR213
	.word	.LC94
	.size	nand_flash_init, .-nand_flash_init
	.section	.text.ftl_sysblk_dump,"ax",%progbits
	.align	1
	.global	ftl_sysblk_dump
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	ftl_sysblk_dump, %function
ftl_sysblk_dump:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, r8, r10, fp, lr}
	mov	fp, r0
	sub	sp, sp, #48
	movs	r0, #1
	movs	r6, #0
	bl	buf_alloc
	ldr	r3, [r0, #4]
	mov	r4, r0
	mov	r5, r6
	str	r3, [sp, #44]
.L3336:
	ldr	r3, .L3345
	ldrh	r2, [r3]
	uxth	r3, r6
	cmp	r2, r3
	bhi	.L3338
	ldr	r1, [sp, #44]
	movs	r3, #32
	ldr	r0, .L3345+4
	movs	r2, #4
	add	r1, r1, #704
	bl	rknand_print_hex
	mov	r0, r4
	bl	zbuf_free
	cbz	r5, .L3339
	movw	r2, #1619
	ldr	r1, .L3345+8
	ldr	r0, .L3345+12
	bl	printf
.L3339:
	mov	r0, r5
	add	sp, sp, #48
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r10, fp, pc}
.L3338:
	ldr	r3, .L3345+16
	uxth	r7, r6
	ldr	r2, [r4, #12]
	ldr	r1, [r4, #4]
	ldrh	r8, [r3]
	ldr	r3, .L3345+20
	mla	r8, fp, r8, r7
	ldrb	r3, [r3]	@ zero_extendqisi2
	mov	r0, r8
	bl	ftl_read_ppa_page
	ldr	r2, [r4, #12]
	mov	r10, r0
	ldr	r3, [r4, #4]
	ldr	r1, [r2, #12]
	str	r1, [sp, #32]
	ldr	r1, [r2, #8]
	str	r1, [sp, #28]
	ldr	r1, [r2, #4]
	str	r1, [sp, #24]
	mov	r1, fp
	ldr	r2, [r2]
	str	r2, [sp, #20]
	ldr	r2, [r3, #12]
	str	r2, [sp, #16]
	ldr	r2, [r3, #8]
	str	r2, [sp, #12]
	ldr	r2, [r3, #4]
	str	r2, [sp, #8]
	mov	r2, r7
	ldr	r3, [r3]
	str	r0, [sp]
	ldr	r0, .L3345+24
	str	r3, [sp, #4]
	mov	r3, r8
	bl	printf
	cmp	r10, #-1
	beq	.L3340
	cmp	r10, #512
	it	eq
	moveq	r5, #1
.L3337:
	adds	r6, r6, #1
	b	.L3336
.L3340:
	movs	r5, #1
	b	.L3337
.L3346:
	.align	2
.L3345:
	.word	.LANCHOR94
	.word	.LC179
	.word	.LANCHOR218
	.word	.LC0
	.word	.LANCHOR111
	.word	.LANCHOR131
	.word	.LC160
	.size	ftl_sysblk_dump, .-ftl_sysblk_dump
	.section	.text.ftl_open_sblk_recovery,"ax",%progbits
	.align	1
	.global	ftl_open_sblk_recovery
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	ftl_open_sblk_recovery, %function
ftl_open_sblk_recovery:
	@ args = 0, pretend = 0, frame = 216
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, r8, r10, fp, lr}
	mov	r4, r0
	ldr	r5, .L3484
	sub	sp, sp, #224
	str	r1, [sp, #28]
	ldr	r3, [r5]
	lsls	r0, r3, #19
	bpl	.L3348
	ldrh	r1, [r4, #2]
	ldr	r0, .L3484+4
	bl	printf
.L3348:
	ldr	r3, [r5]
	lsls	r1, r3, #19
	bpl	.L3349
	ldrb	r1, [r4, #5]	@ zero_extendqisi2
	ldr	r0, .L3484+8
	bl	printf
.L3349:
	ldr	r3, [r5]
	lsls	r2, r3, #19
	bpl	.L3350
	ldrh	r1, [r4]
	ldr	r0, .L3484+12
	bl	printf
.L3350:
	ldr	r3, [r5]
	lsls	r3, r3, #19
	bpl	.L3351
	ldrh	r2, [r4, #18]
	ldrh	r1, [r4, #16]
	ldr	r0, .L3484+16
	bl	printf
.L3351:
	ldr	r3, [r5]
	lsls	r7, r3, #19
	bpl	.L3352
	ldrb	r1, [r4, #9]	@ zero_extendqisi2
	ldr	r0, .L3484+20
	bl	printf
.L3352:
	ldrh	r3, [r4, #10]
	ldrh	r2, [r4]
	strh	r3, [r4, #14]	@ movhi
	ldr	r3, .L3484+24
	ldrh	r3, [r3]
	cmp	r2, r3
	bcs	.L3347
	movs	r0, #1
	bl	buf_alloc
	ldr	r3, .L3484+28
	movs	r1, #255
	ldr	r2, [r0, #4]
	mov	r5, r0
	add	r0, sp, #32
	ldrb	r3, [r3]	@ zero_extendqisi2
	subs	r3, r3, #2
	add	r3, r2, r3, lsl #9
	movs	r2, #64
	str	r3, [sp, #24]
	bl	ftl_memset
	movs	r2, #64
	movs	r1, #255
	add	r0, sp, #96
	bl	ftl_memset
	movs	r2, #64
	movs	r1, #255
	add	r0, sp, #160
	bl	ftl_memset
	ldrh	r3, [r4, #2]
	ldrb	fp, [r4, #5]	@ zero_extendqisi2
	str	r3, [sp, #8]
	movs	r3, #2
	str	r3, [sp, #12]
	movs	r3, #0
	str	r3, [sp, #20]
.L3354:
	ldr	r3, .L3484+32
	ldr	r2, [sp, #8]
	ldrh	r3, [r3]
	cmp	r3, r2
	bhi	.L3369
.L3357:
	ldrh	r3, [sp, #8]
	ldr	r1, .L3484+32
	ldrh	r2, [r4, #6]
	strh	r3, [r4, #2]	@ movhi
	ldrh	r3, [r4, #10]
	ldrb	r0, [r4, #9]	@ zero_extendqisi2
	strb	fp, [r4, #5]
	add	r2, r2, r3
	ldrh	r3, [r1]
	str	r1, [sp, #8]
	muls	r3, r0, r3
	cmp	r2, r3
	beq	.L3370
	movw	r2, #1802
	ldr	r1, .L3484+36
	ldr	r0, .L3484+40
	bl	printf
.L3370:
	ldr	r3, .L3484+44
	movs	r6, #0
	ldrh	r0, [r4, #10]
	mov	r2, r6
	ldr	r7, [r3]
	str	r3, [sp, #16]
.L3371:
	cmp	r2, r0
	bcc	.L3373
	ldr	r2, [sp, #8]
	ldrb	r3, [r4, #9]	@ zero_extendqisi2
	ldr	r7, .L3484
	ldrh	r2, [r2]
	ldr	r8, .L3484+60
	smulbb	r3, r3, r2
	subs	r3, r3, r0
	add	r6, r6, r3
	ldr	r3, [r7]
	uxth	r6, r6
	tst	r3, #4096
	beq	.L3374
	ldrh	r1, [r4]
	mov	r2, r6
	ldr	r3, [r8]
	ldr	r0, .L3484+48
	ldrh	r3, [r3, r1, lsl #1]
	bl	printf
.L3374:
	ldr	r3, [r8]
	ldrh	r2, [r4]
	strh	r6, [r3, r2, lsl #1]	@ movhi
	ldr	r3, [r7]
	lsls	r7, r3, #17
	bpl	.L3375
	ldr	r3, [sp, #44]
	add	r1, sp, #32
	ldr	r0, .L3484+52
	str	r3, [sp]
	ldm	r1, {r1, r2, r3}
	bl	printf
.L3375:
	ldr	r6, .L3484+28
	movs	r7, #0
	ldr	r8, .L3484+56
	movs	r1, #0
	ldr	r0, [r5, #4]
	ldrb	r2, [r6]	@ zero_extendqisi2
	lsls	r2, r2, #9
	bl	ftl_memset
	str	r6, [sp, #24]
.L3376:
	ldrb	r3, [r8]	@ zero_extendqisi2
	ldr	r2, [sp, #12]
	muls	r3, r2, r3
	cmp	r7, r3
	bcc	.L3390
	ldr	r7, .L3484+28
	movs	r6, #0
.L3391:
	ldr	r3, .L3484+56
	ldr	r2, [sp, #12]
	ldrb	r3, [r3]	@ zero_extendqisi2
	muls	r3, r2, r3
	cmp	r6, r3
	bcc	.L3398
	mov	r0, r5
	bl	zbuf_free
	ldr	r3, [sp, #8]
	ldrh	r2, [r4, #12]
	ldrb	r1, [r4, #9]	@ zero_extendqisi2
	ldrh	r3, [r3]
	mla	r3, r1, r3, r2
	ldr	r2, [sp, #16]
	ldr	r2, [r2]
	add	r3, r3, #1073741824
	subs	r3, r3, #1
	ldr	r3, [r2, r3, lsl #2]
	adds	r3, r3, #1
	beq	.L3399
	movw	r2, #1917
	ldr	r1, .L3484+36
	ldr	r0, .L3484+40
	bl	printf
.L3399:
	ldrh	r3, [r4, #6]
	cmp	r3, #1
	bne	.L3347
	mov	r0, r4
	bl	ftl_write_last_log_page
.L3347:
	add	sp, sp, #224
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r10, fp, pc}
.L3369:
	ldrb	fp, [r4, #5]	@ zero_extendqisi2
.L3355:
	ldrb	r3, [r4, #9]	@ zero_extendqisi2
	cmp	r3, fp
	bhi	.L3368
	movs	r3, #0
	strb	r3, [r4, #5]
	ldr	r3, [sp, #8]
	adds	r3, r3, #1
	uxth	r3, r3
	str	r3, [sp, #8]
	b	.L3354
.L3485:
	.align	2
.L3484:
	.word	.LANCHOR19
	.word	.LC180
	.word	.LC181
	.word	.LC182
	.word	.LC183
	.word	.LC184
	.word	.LANCHOR8
	.word	.LANCHOR131
	.word	.LANCHOR94
	.word	.LANCHOR219
	.word	.LC0
	.word	.LANCHOR117
	.word	.LC187
	.word	.LC188
	.word	.LANCHOR79
	.word	.LANCHOR11
.L3368:
	add	r3, fp, #8
	ldrh	r7, [r4, r3, lsl #1]
	movw	r3, #65535
	cmp	r7, r3
	beq	.L3356
	ldr	r3, .L3486
	ldr	r2, [sp, #8]
	ldr	r6, .L3486+4
	ldrh	r3, [r3]
	ldr	r1, [r5, #4]
	mla	r3, r7, r3, r2
	ldr	r2, [r5, #12]
	str	r3, [sp, #16]
	ldr	r0, [sp, #16]
	ldrb	r3, [r6]	@ zero_extendqisi2
	bl	ftl_read_ppa_page
	cmp	r0, #512
	mov	r8, r0
	beq	.L3357
	cmp	r0, #-1
	beq	.L3358
	ldr	r3, [r5, #12]
	ldr	r2, [r3]
	adds	r2, r2, #1
	bne	.L3358
	ldr	r3, [r3, #4]
	adds	r3, r3, #1
	bne	.L3358
	ldr	r3, [r5, #4]
	ldr	r3, [r3]
	adds	r3, r3, #1
	beq	.L3357
.L3358:
	ldr	r3, .L3486+8
	movs	r2, #1
	ldr	r1, [sp, #8]
	strb	r2, [r3]
	ldrb	r3, [r4, #9]	@ zero_extendqisi2
	ldrh	r2, [r4, #10]
	mla	r3, r1, r3, fp
	cmp	r2, r3
	beq	.L3359
	movw	r2, #1694
	ldr	r1, .L3486+12
	ldr	r0, .L3486+16
	bl	printf
.L3359:
	ldrh	r3, [r4, #10]
	ldrh	r2, [r4, #6]
	add	r2, r2, r3
	ldr	r3, .L3486+20
	ldrh	r1, [r3]
	ldrb	r3, [r4, #9]	@ zero_extendqisi2
	muls	r3, r1, r3
	cmp	r2, r3
	beq	.L3360
	movw	r2, #1695
	ldr	r1, .L3486+12
	ldr	r0, .L3486+16
	bl	printf
.L3360:
	ldrb	r3, [r6]	@ zero_extendqisi2
	cmp	r3, #8
	bls	.L3361
	ldr	r10, [r5, #12]
	ldr	r2, .L3486+24
	ldr	r3, [r10]
	cmp	r3, r2
	beq	.L3361
	cmp	r8, #-1
	beq	.L3363
	ldr	r3, [r10, #4]
	adds	r3, r3, #1
	beq	.L3364
	ldr	r3, [r10, #16]
	add	r2, r2, #1392508928
	sub	r2, r2, #1957888
	subw	r2, r2, #2427
	cmp	r3, r2
	bne	.L3364
	mov	r1, #1024
	ldr	r0, [sp, #24]
	bl	js_hash
	ldr	r3, [r10, #20]
	cmp	r3, r0
	beq	.L3364
	str	r0, [sp, #4]
	mov	r1, r7
	ldr	r3, [sp, #16]
	ldr	r2, [sp, #8]
	str	r8, [sp]
	ldr	r0, .L3486+28
	bl	printf
	movs	r3, #16
	movs	r2, #4
	ldr	r1, [sp, #24]
	ldr	r0, .L3486+32
	bl	rknand_print_hex
	ldrb	r3, [r6]	@ zero_extendqisi2
	movs	r2, #4
	ldr	r1, [r5, #12]
	ldr	r0, .L3486+36
	lsrs	r3, r3, #1
	bl	rknand_print_hex
.L3363:
	ldrh	r3, [r4, #6]
	subs	r3, r3, #1
	strh	r3, [r4, #6]	@ movhi
	ldrh	r3, [r4, #10]
	adds	r3, r3, #1
	strh	r3, [r4, #10]	@ movhi
	movs	r3, #4
	str	r3, [sp, #12]
	movs	r3, #1
	str	r3, [sp, #20]
.L3356:
	add	r3, fp, #1
	uxth	fp, r3
	b	.L3355
.L3361:
	cmp	r8, #-1
	beq	.L3363
.L3364:
	ldr	r3, [r5, #12]
	ldr	r0, [r3, #4]
	adds	r6, r0, #1
	beq	.L3363
	ldr	r3, [r3]
	ldr	r2, .L3486+24
	cmp	r3, r2
	beq	.L3363
	bl	lpa_hash_get_ppa
	ldr	r3, [sp, #28]
	mov	r7, r0
	cmp	r3, #0
	beq	.L3366
	ldr	r10, [r5, #12]
	ldr	r3, [r10, #8]
	cmp	r0, r3
	beq	.L3366
	adds	r1, r0, #1
	beq	.L3366
	ldr	r3, .L3486+40
	movs	r6, #1
	ldr	r8, .L3486+60
	ldrh	r0, [r3]
	ldr	r3, .L3486+44
	ldrb	r1, [r8]	@ zero_extendqisi2
	ldrb	r3, [r3]	@ zero_extendqisi2
	rsb	r3, r3, #24
	subs	r3, r3, r0
	lsr	r0, r7, r0
	lsl	r3, r6, r3
	subs	r3, r3, #1
	ands	r0, r0, r3
	bl	__aeabi_uidiv
	ldr	r3, [sp, #28]
	uxth	r0, r0
	ldrh	r3, [r3]
	cmp	r3, r0
	bne	.L3366
	ldr	r3, [r10]
	mov	r0, r7
	ldr	r10, .L3486+64
	ldr	r1, [r5, #4]
	str	r3, [sp, #12]
	ldr	r3, .L3486+4
	mov	r2, r10
	ldrb	r3, [r3]	@ zero_extendqisi2
	bl	ftl_read_ppa_page
	ldr	r3, [r10]
	ldr	r2, [sp, #12]
	cmp	r2, r3
	bhi	.L3366
	ldr	r3, [r5, #12]
	ldr	r3, [r3, #8]
	adds	r2, r3, #1
	beq	.L3363
	ldr	r1, .L3486+44
	ldr	r2, .L3486+40
	ldrb	r0, [r1]	@ zero_extendqisi2
	ldrh	r2, [r2]
	ldrb	r1, [r8]	@ zero_extendqisi2
	rsb	r0, r0, #24
	subs	r0, r0, r2
	lsls	r6, r6, r0
	lsr	r0, r3, r2
	subs	r6, r6, #1
	ands	r0, r0, r6
	bl	__aeabi_uidiv
	uxth	r0, r0
	bl	ftl_vpn_decrement
	b	.L3363
.L3373:
	ldrh	r1, [r4, #12]
	add	r1, r1, r2
	adds	r2, r2, #1
	ldr	r3, [r7, r1, lsl #2]
	adds	r3, r3, #1
	itt	ne
	addne	r6, r6, #1
	uxthne	r6, r6
	b	.L3371
.L3390:
	add	fp, sp, #32
	ldr	r0, [fp, r7, lsl #2]
	adds	r6, r0, #1
	bne	.L3377
.L3383:
	ldr	r2, .L3486+48
	mov	r6, #-1
	ldr	r3, [r5, #12]
	ldr	r1, [r5, #4]
	ldr	r2, [r2]
	ldr	r2, [r2, #8]
	str	r6, [r3, #4]
	str	r6, [r3, #8]
	str	r2, [r3]
	movs	r2, #0
	str	r2, [r3, #12]
	str	r2, [r3, #16]
	str	r2, [r1]
	ldr	r1, .L3486+4
	ldrb	r1, [r1]	@ zero_extendqisi2
	cmp	r1, #8
	bhi	.L3378
.L3379:
	ldr	r3, [sp, #20]
	cmp	r3, #0
	beq	.L3385
	ldrh	r3, [r4, #6]
	cmp	r3, #1
	bls	.L3385
	ldr	fp, .L3486+56
.L3455:
	mov	r0, r4
	bl	ftl_get_new_free_page
	ldr	r3, [fp]
	mov	r10, r0
	lsls	r3, r3, #17
	bpl	.L3387
	ldrh	r2, [r4, #12]
	mov	r1, r0
	ldrh	r3, [r4, #10]
	ldr	r0, .L3486+52
	add	r3, r3, r2
	ldr	r2, [r5, #12]
	subs	r3, r3, #1
	ldr	r2, [r2, #4]
	bl	printf
.L3387:
	ldrb	r3, [r8]	@ zero_extendqisi2
	ldr	r1, [sp, #12]
	ldrh	r2, [r4, #6]
	muls	r3, r1, r3
	adds	r3, r3, #1
	subs	r3, r3, r7
	cmp	r2, r3
	bls	.L3385
	ldr	r3, .L3486+4
	mov	r0, r10
	ldr	r2, [r5, #12]
	ldr	r1, [r5, #4]
	ldrb	r3, [r3]	@ zero_extendqisi2
	bl	ftl_prog_ppa_page
	str	r0, [sp, #28]
	ldrh	r0, [r4]
	bl	ftl_vpn_decrement
	adds	r0, r6, #1
	beq	.L3388
	ldr	r3, [sp, #28]
	adds	r3, r3, #1
	beq	.L3388
	add	r3, sp, #96
	ldrh	r2, [r4, #12]
	str	r10, [r3, r7, lsl #2]
	ldrh	r3, [r4, #10]
	add	r3, r3, r2
	add	r2, sp, #160
	subs	r3, r3, #1
	str	r3, [r2, r7, lsl #2]
.L3385:
	adds	r7, r7, #1
	b	.L3376
.L3487:
	.align	2
.L3486:
	.word	.LANCHOR111
	.word	.LANCHOR131
	.word	.LANCHOR195
	.word	.LANCHOR219
	.word	.LC0
	.word	.LANCHOR94
	.word	-178307901
	.word	.LC185
	.word	.LC186
	.word	.LC147
	.word	.LANCHOR74
	.word	.LANCHOR31
	.word	.LANCHOR110
	.word	.LC190
	.word	.LANCHOR19
	.word	.LANCHOR75
	.word	.LANCHOR190
.L3377:
	ldr	r3, [sp, #24]
	ldr	r1, [r5, #4]
	ldr	r2, [r5, #12]
	ldrb	r3, [r3]	@ zero_extendqisi2
	bl	ftl_read_ppa_page
	ldr	r3, [r5, #12]
	mov	r6, r0
	ldr	r0, [r3, #4]
	bl	lpa_hash_get_ppa
	ldr	r3, .L3488
	mov	r10, r0
	ldr	r3, [r3]
	lsls	r1, r3, #17
	bpl	.L3380
	ldr	r3, [r5, #12]
	mov	r1, r0
	ldr	r2, [fp, r7, lsl #2]
	ldr	r0, .L3488+4
	ldr	r3, [r3, #4]
	bl	printf
.L3380:
	add	r3, sp, #32
	ldr	r1, .L3488+8
	ldr	r3, [r3, r7, lsl #2]
	movs	r2, #1
	ldrb	r1, [r1]	@ zero_extendqisi2
	cmp	r10, r3
	it	ne
	movne	r6, #-1
	ldr	r3, [r5, #12]
	cmp	r1, #8
	str	r2, [r3, #12]
	mov	r2, #0
	str	r2, [r3, #16]
	it	hi
	strhi	r2, [r3, #20]
	adds	r2, r6, #1
	str	r10, [r3, #8]
	bne	.L3379
	b	.L3383
.L3378:
	str	r2, [r3, #16]
	str	r2, [r3, #20]
	b	.L3379
.L3388:
	ldrh	r3, [r4, #6]
	cmp	r3, #1
	bls	.L3385
	adds	r1, r6, #1
	bne	.L3455
	b	.L3385
.L3398:
	add	r8, sp, #96
	ldr	r3, [r8, r6, lsl #2]
	adds	r3, r3, #1
	beq	.L3393
	add	r0, sp, #32
	ldr	r2, [r5, #12]
	ldrb	r3, [r7]	@ zero_extendqisi2
	ldr	r1, [r5, #4]
	ldr	r0, [r0, r6, lsl #2]
	bl	ftl_read_ppa_page
	adds	r2, r0, #1
	beq	.L3394
	cmp	r0, #256
	bne	.L3393
.L3394:
	ldr	r0, [r8, r6, lsl #2]
	ldr	r8, .L3488
	ldrb	r3, [r7]	@ zero_extendqisi2
	ldr	r2, [r5, #12]
	ldr	r1, [r5, #4]
	bl	ftl_read_ppa_page
	ldr	r3, [r8]
	mov	r10, r0
	lsls	r3, r3, #17
	bpl	.L3396
	ldr	r2, [r5, #12]
	add	r3, sp, #32
	mov	r1, r0
	ldr	r3, [r3, r6, lsl #2]
	ldr	r0, .L3488+12
	ldr	r2, [r2, #8]
	bl	printf
.L3396:
	cmp	r10, #-1
	beq	.L3393
	ldr	r1, [r5, #12]
	add	r3, sp, #32
	ldr	r2, [r3, r6, lsl #2]
	ldr	r3, [r1, #8]
	cmp	r2, r3
	bne	.L3393
	ldr	r3, [r8]
	add	r8, sp, #160
	tst	r3, #16384
	beq	.L3397
	ldr	r3, [r8, r6, lsl #2]
	ldr	r1, [r1, #4]
	ldr	r0, .L3488+16
	bl	printf
.L3397:
	ldr	r3, [r5, #12]
	ldrh	r2, [r8, r6, lsl #2]
	ldr	r1, [r3, #8]
	ldr	r0, [r3, #4]
	bl	lpa_hash_update_ppa
.L3393:
	adds	r6, r6, #1
	b	.L3391
.L3366:
	ldr	r0, [r5, #12]
	ldr	r3, .L3488+20
	ldr	r2, [r0, #4]
	ldr	r3, [r3]
	cmp	r2, r3
	bcs	.L3363
	ldr	r3, .L3488+24
	ldrb	r1, [r4, #9]	@ zero_extendqisi2
	ldrh	r2, [r4, #10]
	ldrh	r3, [r3]
	muls	r3, r1, r3
	subs	r3, r3, #1
	cmp	r2, r3
	bge	.L3363
	ldr	r3, .L3488+28
	ldr	r6, [r0]
	ldr	r3, [r3]
	ldr	r1, [r3, #8]
	cmp	r6, r1
	it	hi
	strhi	r6, [r3, #8]
	ldrh	r3, [r4, #12]
	ldr	r1, [r0, #8]
	ldr	r0, [r0, #4]
	add	r2, r2, r3
	uxth	r2, r2
	bl	lpa_hash_update_ppa
	ldr	r3, [sp, #36]
	str	r3, [sp, #32]
	ldr	r3, [sp, #40]
	str	r3, [sp, #36]
	ldr	r3, [sp, #44]
	str	r3, [sp, #40]
	ldr	r3, [sp, #16]
	str	r3, [sp, #44]
	b	.L3363
.L3489:
	.align	2
.L3488:
	.word	.LANCHOR19
	.word	.LC189
	.word	.LANCHOR131
	.word	.LC190
	.word	.LC191
	.word	.LANCHOR128
	.word	.LANCHOR94
	.word	.LANCHOR110
	.size	ftl_open_sblk_recovery, .-ftl_open_sblk_recovery
	.section	.text.dump_ftl_info,"ax",%progbits
	.align	1
	.global	dump_ftl_info
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	dump_ftl_info, %function
dump_ftl_info:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	ldr	r3, .L3491
	push	{r0, r1, r2, r4, r5, r6, r7, lr}
	ldr	r0, .L3491+4
	ldrb	r1, [r3]	@ zero_extendqisi2
	bl	printf
	ldr	r1, .L3491+8
	ldr	r5, .L3491+12
	ldr	r0, .L3491+16
	ldrh	r3, [r1, #2]
	ldrb	r2, [r1, #1]	@ zero_extendqisi2
	ldrb	r1, [r1]	@ zero_extendqisi2
	bl	printf
	ldr	r3, [r5]
	ldr	r4, .L3491+20
	ldr	r0, .L3491+24
	ldrh	r2, [r3, #140]
	ldrh	r1, [r3, #130]
	bl	printf
	ldr	r0, [r4]
	ldr	r7, .L3491+28
	ldrh	r6, [r0, #26]
	ldrb	r3, [r0, #21]	@ zero_extendqisi2
	ldrh	r2, [r0, #18]
	ldrh	r1, [r0, #16]
	str	r6, [sp, #4]
	ldrh	r0, [r0, #22]
	str	r0, [sp]
	ldr	r0, .L3491+32
	bl	printf
	ldr	r0, [r4]
	ldrh	r6, [r0, #58]
	ldrb	r3, [r0, #53]	@ zero_extendqisi2
	ldrh	r2, [r0, #50]
	ldrh	r1, [r0, #48]
	str	r6, [sp, #4]
	ldrh	r0, [r0, #54]
	ldr	r6, .L3491+36
	str	r0, [sp]
	ldr	r0, .L3491+40
	bl	printf
	ldr	r0, [r4]
	ldrh	r4, [r0, #90]
	ldrb	r3, [r0, #85]	@ zero_extendqisi2
	ldrh	r2, [r0, #82]
	ldrh	r1, [r0, #80]
	str	r4, [sp, #4]
	ldrh	r0, [r0, #86]
	ldr	r4, .L3491+44
	str	r0, [sp]
	ldr	r0, .L3491+48
	bl	printf
	ldrh	r2, [r6]
	ldrb	r3, [r4]	@ zero_extendqisi2
	ldr	r1, .L3491+52
	ldr	r0, .L3491+56
	muls	r3, r2, r3
	ldr	r1, [r1]
	movs	r2, #4
	lsls	r3, r3, #1
	bl	rknand_print_hex
	ldr	r1, .L3491+60
	movs	r2, #2
	ldrh	r3, [r7]
	ldr	r0, .L3491+64
	ldr	r1, [r1]
	bl	rknand_print_hex
	ldr	r1, [r5]
	movs	r2, #4
	ldr	r0, .L3491+68
	ldrh	r3, [r1, #698]
	add	r1, r1, #704
	bl	rknand_print_hex
	ldr	r1, .L3491+72
	movs	r2, #4
	ldrh	r3, [r7]
	ldr	r0, .L3491+76
	ldr	r1, [r1]
	bl	rknand_print_hex
	mov	r3, #256
	movs	r2, #2
	ldr	r1, .L3491+80
	ldr	r0, .L3491+84
	bl	rknand_print_hex
	ldrh	r2, [r6]
	ldrb	r3, [r4]	@ zero_extendqisi2
	ldr	r1, .L3491+88
	ldr	r0, .L3491+92
	muls	r3, r2, r3
	ldr	r1, [r1]
	movs	r2, #2
	lsls	r3, r3, #1
	add	sp, sp, #12
	@ sp needed
	pop	{r4, r5, r6, r7, lr}
	b	rknand_print_hex
.L3492:
	.align	2
.L3491:
	.word	.LANCHOR57
	.word	.LC192
	.word	.LANCHOR191
	.word	.LANCHOR110
	.word	.LC193
	.word	.LANCHOR12
	.word	.LC194
	.word	.LANCHOR8
	.word	.LC195
	.word	.LANCHOR94
	.word	.LC196
	.word	.LANCHOR79
	.word	.LC197
	.word	.LANCHOR117
	.word	.LC198
	.word	.LANCHOR11
	.word	.LC199
	.word	.LC179
	.word	.LANCHOR9
	.word	.LC200
	.word	.LANCHOR116
	.word	.LC201
	.word	.LANCHOR118
	.word	.LC202
	.size	dump_ftl_info, .-dump_ftl_info
	.section	.text.pm_ppa_update_check,"ax",%progbits
	.align	1
	.global	pm_ppa_update_check
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	pm_ppa_update_check, %function
pm_ppa_update_check:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r3, r4, r5, r6, r7, lr}
	mov	r7, r2
	ldr	r2, .L3500
	mov	r5, r0
	mov	r6, r1
	ldr	r3, .L3500+4
	ldrb	r4, [r2]	@ zero_extendqisi2
	ldrh	r3, [r3]
	rsb	r4, r4, #24
	subs	r0, r4, r3
	movs	r4, #1
	lsls	r4, r4, r0
	lsr	r0, r7, r3
	ldr	r3, .L3500+8
	subs	r4, r4, #1
	ands	r0, r0, r4
	ldrb	r1, [r3]	@ zero_extendqisi2
	bl	__aeabi_uidiv
	ldr	r3, .L3500+12
	uxth	r0, r0
	ldr	r3, [r3]
	add	r0, r3, r0, lsl #2
	ldrb	r3, [r0, #2]	@ zero_extendqisi2
	lsrs	r3, r3, #5
	cmp	r3, #1
	beq	.L3494
	cmp	r3, #7
	bne	.L3496
.L3494:
	mov	r3, r7
	mov	r2, r6
	mov	r1, r5
	ldr	r0, .L3500+16
	bl	printf
	bl	dump_ftl_info
	mov	r0, #-1
	pop	{r3, r4, r5, r6, r7, pc}
.L3496:
	movs	r0, #0
	pop	{r3, r4, r5, r6, r7, pc}
.L3501:
	.align	2
.L3500:
	.word	.LANCHOR31
	.word	.LANCHOR74
	.word	.LANCHOR75
	.word	.LANCHOR9
	.word	.LC203
	.size	pm_ppa_update_check, .-pm_ppa_update_check
	.section	.text.load_l2p_region,"ax",%progbits
	.align	1
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	load_l2p_region, %function
load_l2p_region:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	cmp	r1, #31
	push	{r0, r1, r4, r5, r6, r7, r8, r10, fp, lr}
	mov	r5, r0
	mov	r7, r1
	bls	.L3503
	movs	r2, #32
	ldr	r1, .L3526
	ldr	r0, .L3526+4
	bl	printf
.L3503:
	ldr	r6, .L3526+8
	ldr	r3, [r6]
	mov	r10, r6
	ldrh	r2, [r3, #698]
	cmp	r2, r5
	bcs	.L3504
	mov	r1, r5
	ldr	r0, .L3526+12
	bl	printf
	ldr	r3, .L3526+16
	movs	r4, #0
	movs	r1, #255
	ldr	r0, [r4, #4]
	ldrh	r2, [r3]
	bl	ftl_memset
	ldr	r3, [r6]
	ldrh	r3, [r3, #698]
	cmp	r3, r5
	bcc	.L3505
.L3524:
	movs	r0, #0
.L3502:
	add	sp, sp, #8
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r10, fp, pc}
.L3505:
	movs	r2, #37
.L3525:
	ldr	r1, .L3526
	ldr	r0, .L3526+4
	bl	printf
	b	.L3524
.L3504:
	ldr	r6, .L3526+20
	add	r2, r5, #176
	ldr	r4, [r3, r2, lsl #2]
	movs	r3, #0
	strh	r5, [r6, r7, lsl #3]	@ movhi
	lsls	r7, r7, #3
	add	fp, r6, r7
	strh	r3, [fp, #2]	@ movhi
	cbnz	r4, .L3507
	mov	r2, r4
	mov	r1, r5
	ldr	r0, .L3526+24
	bl	printf
	ldr	r3, .L3526+16
	movs	r1, #255
	ldr	r0, [fp, #4]
	ldrh	r2, [r3]
	bl	ftl_memset
	b	.L3524
.L3507:
	ldr	r8, .L3526+32
	mov	r0, r4
	ldr	r3, .L3526+28
	ldr	r1, [fp, #4]
	ldr	r2, [r8]
	ldrb	r3, [r3]	@ zero_extendqisi2
	bl	ftl_read_ppa_page
	ldr	r2, [r8]
	mov	r3, r0
	ldr	r2, [r2]
	cmp	r2, r5
	bne	.L3508
	adds	r1, r0, #1
	beq	.L3508
	cmp	r0, #512
	beq	.L3508
.L3513:
	ldr	r3, .L3526+32
	ldr	r3, [r3]
	ldr	r3, [r3]
	cmp	r5, r3
	beq	.L3524
	movs	r2, #73
	b	.L3525
.L3508:
	mov	r1, r5
	str	r4, [sp]
	ldr	r0, .L3526+36
	add	r8, r6, r7
	bl	printf
	ldr	r1, [r10]
	movs	r2, #4
	ldr	r10, .L3526+28
	ldr	r0, .L3526+40
	ldrh	r3, [r1, #698]
	add	r1, r1, #704
	bl	rknand_print_hex
	ldrb	r3, [r10]	@ zero_extendqisi2
	movs	r2, #4
	ldr	fp, .L3526+32
	ldr	r1, [r8, #4]
	ldr	r0, .L3526+44
	lsls	r3, r3, #7
	bl	rknand_print_hex
	movs	r3, #16
	movs	r2, #4
	ldr	r1, [fp]
	ldr	r0, .L3526+48
	bl	rknand_print_hex
	ldrb	r3, [r10]	@ zero_extendqisi2
	mov	r0, r4
	ldr	r2, [fp]
	ldr	r1, [r8, #4]
	bl	ftl_read_ppa_page
	adds	r3, r0, #1
	beq	.L3511
	cmp	r0, #512
	bne	.L3512
.L3511:
	ldr	r3, .L3526+16
	add	r6, r6, r7
	movs	r1, #255
	ldr	r0, [r6, #4]
	ldrh	r2, [r3]
	bl	ftl_memset
.L3514:
	mov	r0, #-1
	b	.L3502
.L3512:
	ldr	r3, [fp]
	ldr	r3, [r3]
	cmp	r5, r3
	beq	.L3513
	b	.L3514
.L3527:
	.align	2
.L3526:
	.word	.LANCHOR220
	.word	.LC0
	.word	.LANCHOR110
	.word	.LC204
	.word	.LANCHOR221
	.word	.LANCHOR135
	.word	.LC205
	.word	.LANCHOR131
	.word	.LANCHOR207
	.word	.LC206
	.word	.LC207
	.word	.LC186
	.word	.LC208
	.size	load_l2p_region, .-load_l2p_region
	.section	.text.pm_gc,"ax",%progbits
	.align	1
	.global	pm_gc
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	pm_gc, %function
pm_gc:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, r8, r10, fp, lr}
	ldr	r4, .L3545
	ldr	r5, .L3545+4
	ldr	r3, [r4]
	ldr	r6, .L3545+8
	ldrh	r2, [r5]
	ldrh	r1, [r3, #688]
	subs	r2, r2, #1
	cmp	r1, r2
	bge	.L3529
	ldr	r3, [r6]
	cmp	r3, #0
	beq	.L3530
.L3529:
	bl	pm_free_sblk
	ldr	r2, [r4]
	ldrh	r3, [r5]
	ldrh	r1, [r2, #688]
	subs	r3, r3, #1
	cmp	r1, r3
	bge	.L3531
	ldr	r3, [r6]
	cmp	r3, #0
	beq	.L3530
.L3531:
	uxth	r0, r0
	movw	r5, #65535
	movs	r3, #0
	adds	r0, r0, #208
	str	r3, [r6]
	ldrh	r8, [r2, r0, lsl #1]
	cmp	r8, r5
	bne	.L3533
	movs	r2, #182
	ldr	r1, .L3545+12
	ldr	r0, .L3545+16
	bl	printf
	bl	pm_free_sblk
	ldr	r3, [r4]
	uxth	r0, r0
	adds	r0, r0, #208
	ldrh	r8, [r3, r0, lsl #1]
	cmp	r8, r5
	beq	.L3530
.L3533:
	ldr	r5, .L3545+20
	bl	pm_select_ram_region
	mov	r6, r0
	movw	r3, #65535
	ldrh	r0, [r5, r0, lsl #3]
	cmp	r0, r3
	beq	.L3534
	add	r7, r5, r6, lsl #3
	ldr	r1, [r7, #4]
	cbz	r1, .L3534
	ldrsh	r3, [r7, #2]
	cmp	r3, #0
	bge	.L3534
	bl	pm_write_page
	ldrh	r3, [r7, #2]
	ubfx	r3, r3, #0, #15
	strh	r3, [r7, #2]	@ movhi
.L3534:
	movs	r7, #0
.L3535:
	ldr	r1, [r4]
	uxth	fp, r7
	ldrh	r3, [r1, #698]
	cmp	r3, fp
	bhi	.L3538
	bl	pm_free_sblk
.L3530:
	movs	r0, #0
	pop	{r4, r5, r6, r7, r8, r10, fp, pc}
.L3538:
	ldr	r3, .L3545+24
	uxth	r10, r7
	mov	ip, #1
	ldrh	r0, [r3]
	ldr	r3, .L3545+28
	ldrb	r3, [r3]	@ zero_extendqisi2
	rsb	r3, r3, #24
	subs	r3, r3, r0
	lsl	r3, ip, r3
	add	ip, r10, #176
	ldr	r1, [r1, ip, lsl #2]
	subs	r3, r3, #1
	lsr	r0, r1, r0
	ldr	r1, .L3545+32
	ands	r0, r0, r3
	ldrb	r1, [r1]	@ zero_extendqisi2
	bl	__aeabi_uidiv
	uxth	r0, r0
	cmp	r8, r0
	bne	.L3536
	mov	r1, r6
	mov	r0, fp
	bl	load_l2p_region
	cbnz	r0, .L3537
	add	r3, r5, r6, lsl #3
	mov	r0, r10
	ldr	r1, [r3, #4]
	bl	pm_write_page
.L3537:
	movw	r3, #65535
	strh	r3, [r5, r6, lsl #3]	@ movhi
.L3536:
	adds	r7, r7, #1
	b	.L3535
.L3546:
	.align	2
.L3545:
	.word	.LANCHOR110
	.word	.LANCHOR152
	.word	.LANCHOR148
	.word	.LANCHOR222
	.word	.LC0
	.word	.LANCHOR135
	.word	.LANCHOR74
	.word	.LANCHOR31
	.word	.LANCHOR75
	.size	pm_gc, .-pm_gc
	.section	.text.pm_flush_id,"ax",%progbits
	.align	1
	.global	pm_flush_id
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	pm_flush_id, %function
pm_flush_id:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	ldr	r3, .L3552
	push	{r4, lr}
	add	r4, r3, r0, lsl #3
	ldrh	r0, [r3, r0, lsl #3]
	ldr	r1, [r4, #4]
	bl	pm_write_page
	ldrh	r3, [r4, #2]
	ubfx	r3, r3, #0, #15
	strh	r3, [r4, #2]	@ movhi
	ldr	r4, .L3552+4
	ldr	r3, [r4]
	cbz	r3, .L3548
	bl	pm_gc
	movs	r3, #0
	str	r3, [r4]
.L3548:
	movs	r0, #0
	pop	{r4, pc}
.L3553:
	.align	2
.L3552:
	.word	.LANCHOR135
	.word	.LANCHOR204
	.size	pm_flush_id, .-pm_flush_id
	.section	.text.pm_flush,"ax",%progbits
	.align	1
	.global	pm_flush
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	pm_flush, %function
pm_flush:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r3, r4, r5, lr}
	movs	r4, #0
	ldr	r5, .L3558
.L3556:
	add	r3, r5, r4, lsl #3
	uxth	r0, r4
	ldrsh	r3, [r3, #2]
	cmp	r3, #0
	bge	.L3555
	bl	pm_flush_id
.L3555:
	adds	r4, r4, #1
	cmp	r4, #32
	bne	.L3556
	movs	r0, #0
	pop	{r3, r4, r5, pc}
.L3559:
	.align	2
.L3558:
	.word	.LANCHOR135
	.size	pm_flush, .-pm_flush
	.section	.text.flt_sys_flush,"ax",%progbits
	.align	1
	.global	flt_sys_flush
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	flt_sys_flush, %function
flt_sys_flush:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r3, lr}
	bl	ftl_flush
	bl	pm_flush
	bl	ftl_ext_info_flush
	movs	r0, #0
	pop	{r3, lr}
	b	ftl_info_flush
	.size	flt_sys_flush, .-flt_sys_flush
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
	bl	zftl_flash_de_init
	bl	flt_sys_flush
	pop	{r3, lr}
	b	zftl_flash_de_init
	.size	rk_ftl_de_init, .-rk_ftl_de_init
	.section	.text.zftl_deinit,"ax",%progbits
	.align	1
	.global	zftl_deinit
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	zftl_deinit, %function
zftl_deinit:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	b	rk_ftl_de_init
	.size	zftl_deinit, .-zftl_deinit
	.section	.text.pm_init,"ax",%progbits
	.align	1
	.global	pm_init
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	pm_init, %function
pm_init:
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 0, uses_anonymous_args = 0
	ldr	r3, .L3588
	movs	r2, #1
	push	{r4, r5, r6, r7, r8, r10, fp, lr}
	movs	r4, #0
	sub	sp, sp, #24
	mov	r8, r0
	movs	r0, #64
	str	r4, [r3]
	ldr	r3, .L3588+4
	ldr	r6, .L3588+8
	str	r4, [r3]
	ldr	r3, .L3588+12
	mov	r5, r6
	strb	r2, [r3]
	bl	ftl_malloc
	ldr	r3, .L3588+16
	mov	r10, r3
	str	r0, [r3]
.L3565:
	movw	r3, #65535
	adds	r7, r6, r4
	strh	r3, [r4, r6]	@ movhi
	movs	r3, #0
	strh	r3, [r7, #2]	@ movhi
	cmp	r8, #0
	beq	.L3564
	ldr	r3, .L3588+20
	ldrb	r0, [r3]	@ zero_extendqisi2
	lsls	r0, r0, #9
	bl	ftl_malloc
	str	r0, [r7, #4]
.L3564:
	adds	r4, r4, #8
	cmp	r4, #256
	bne	.L3565
	ldr	r4, .L3588+24
	ldr	fp, [r5, #4]
	ldr	r8, [r10]
	ldr	r3, [r4]
	mov	r2, fp
	ldrh	r1, [r3, #692]
	ldrb	r0, [r3, #694]	@ zero_extendqisi2
	movs	r3, #4
	str	r3, [sp]
	mov	r3, r8
	bl	flash_get_last_written_page
	ldr	r1, [r4]
	mov	r6, r0
	ldrh	r2, [r1, #696]
	cmp	r2, r0
	bgt	.L3566
	mov	r3, r0
	ldrh	r1, [r1, #692]
	ldr	r0, .L3588+28
	bl	printf
	ldr	r3, [r4]
	ldrsh	r7, [r3, #696]
.L3567:
	cmp	r7, r6
	ble	.L3570
	ldr	r3, .L3588+32
	movs	r2, #1
	add	r6, r6, r2
	strb	r2, [r3]
	ldr	r3, [r4]
	strh	r6, [r3, #696]	@ movhi
	bl	pm_free_sblk
.L3566:
	ldr	r3, .L3588+36
	movs	r1, #255
	ldr	r0, [r5, #4]
	ldrh	r2, [r3]
	bl	ftl_memset
	ldr	r1, [r5, #4]
	mov	r0, #-1
	bl	pm_write_page
	ldr	r3, .L3588+32
	ldrb	r3, [r3]	@ zero_extendqisi2
	cbz	r3, .L3571
	ldr	r1, [r5, #4]
	mov	r0, #-1
	bl	pm_write_page
	ldr	r1, [r5, #4]
	mov	r0, #-1
	bl	pm_write_page
	ldr	r1, [r5, #4]
	mov	r0, #-1
	bl	pm_write_page
.L3571:
	bl	pm_free_sblk
	bl	pm_gc
	movs	r0, #0
	add	sp, sp, #24
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r10, fp, pc}
.L3570:
	ldr	r3, [r4]
	ldr	r1, .L3588+40
	ldrh	r2, [r3, #692]
	ldrh	r1, [r1]
	ldrb	r0, [r3, #694]	@ zero_extendqisi2
	ldr	r3, .L3588+20
	mla	r2, r1, r2, r7
	ldrb	r3, [r3]	@ zero_extendqisi2
	str	r2, [sp, #12]
	mov	r2, fp
	str	r3, [sp]
	mov	r3, r8
	ldr	r1, [sp, #12]
	bl	flash_read_page_en
	ldr	r3, [r4]
	mov	r10, r0
	ldr	r0, .L3588+44
	ldr	r2, [r3, #48]
	adds	r2, r2, #1
	str	r2, [r3, #48]
	ldrh	r3, [r3, #694]
	ldr	r2, [sp, #12]
	ldr	r1, [r8]
	bl	printf
	cmp	r10, #-1
	beq	.L3568
	cmp	r10, #512
	beq	.L3568
	ldr	r2, [r4]
	ldr	r10, [r8]
	ldrh	r3, [r2, #698]
	cmp	r10, r3
	bcs	.L3568
	ldr	r3, [r8, #8]
	str	r3, [sp, #20]
	cbz	r3, .L3569
	ldr	r3, .L3588+20
	mov	r0, fp
	str	r2, [sp, #16]
	ldrb	r1, [r3]	@ zero_extendqisi2
	lsls	r1, r1, #9
	bl	js_hash
	ldr	r3, [sp, #20]
	ldr	r2, [sp, #16]
	cmp	r3, r0
	beq	.L3569
	mov	r1, r3
	ldr	r0, .L3588+48
	bl	printf
.L3568:
	adds	r7, r7, #1
	sxth	r7, r7
	b	.L3567
.L3569:
	ldr	r3, [sp, #12]
	add	r10, r10, #176
	str	r3, [r2, r10, lsl #2]
	b	.L3568
.L3589:
	.align	2
.L3588:
	.word	.LANCHOR148
	.word	.LANCHOR204
	.word	.LANCHOR135
	.word	.LANCHOR208
	.word	.LANCHOR207
	.word	.LANCHOR131
	.word	.LANCHOR110
	.word	.LC209
	.word	.LANCHOR195
	.word	.LANCHOR221
	.word	.LANCHOR111
	.word	.LC210
	.word	.LC211
	.size	pm_init, .-pm_init
	.section	.text.pm_log2phys,"ax",%progbits
	.align	1
	.global	pm_log2phys
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	pm_log2phys, %function
pm_log2phys:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 0, uses_anonymous_args = 0
	ldr	r3, .L3605
	push	{r0, r1, r4, r5, r6, r7, r8, r10, fp, lr}
	mov	fp, r0
	str	r2, [sp, #4]
	mov	r6, r1
	ldr	r2, [r3]
	cmp	r0, r2
	bcc	.L3591
	mov	r1, r0
	ldr	r0, .L3605+4
	bl	printf
	ldr	r3, [sp, #4]
	mov	r0, #-1
	cbnz	r3, .L3590
	str	r0, [r6]
.L3590:
	add	sp, sp, #8
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r10, fp, pc}
.L3591:
	ldr	r3, .L3605+8
	ldrb	r5, [r3]	@ zero_extendqisi2
	lsls	r1, r5, #7
	bl	__aeabi_uidiv
	ldr	r1, .L3605+12
	uxth	r7, r0
	mov	r10, r0
	movs	r2, #0
	mov	r8, r1
.L3597:
	add	r0, r1, r2, lsl #3
	uxth	r4, r2
	ldr	r0, [r0, #4]
	cmp	r0, #0
	beq	.L3593
	ldrh	r0, [r1, r2, lsl #3]
	cmp	r0, r7
	bne	.L3593
.L3594:
	lsls	r5, r5, #7
	ldr	r3, [sp, #4]
	lsls	r4, r4, #3
	smulbb	r5, r5, r7
	sub	r5, fp, r5
	uxth	r5, r5
	cbnz	r3, .L3595
	add	r2, r8, r4
	ldr	r1, .L3605+16
	ldr	r2, [r2, #4]
	ldr	r2, [r2, r5, lsl #2]
	str	r2, [r6]
	ldrb	r0, [r1]	@ zero_extendqisi2
	rsb	r1, r0, #24
	lsrs	r2, r2, r1
	movs	r1, #1
	lsls	r1, r1, r0
	subs	r1, r1, #1
	ands	r2, r2, r1
	ldr	r1, .L3605+20
	ldrb	r1, [r1]	@ zero_extendqisi2
	cmp	r2, r1
	bcc	.L3596
	mov	r2, #-1
	str	r2, [r6]
.L3596:
	add	r4, r4, r8
	movw	r2, #32767
	ldrh	r3, [r4, #2]
	ubfx	r1, r3, #0, #15
	cmp	r1, r2
	beq	.L3600
	adds	r3, r3, #1
	strh	r3, [r4, #2]	@ movhi
.L3600:
	movs	r0, #0
	b	.L3590
.L3595:
	add	r1, r8, r4
	ldr	r0, [r6]
	ldr	r2, [r1, #4]
	str	r0, [r2, r5, lsl #2]
	ldrh	r2, [r1, #2]
	mvn	r2, r2, lsl #17
	mvn	r2, r2, lsr #17
	strh	r2, [r1, #2]	@ movhi
	ldr	r2, .L3605+24
	strb	r10, [r2]
	b	.L3596
.L3593:
	adds	r2, r2, #1
	cmp	r2, #32
	bne	.L3597
	bl	pm_select_ram_region
	ldrh	r1, [r8, r0, lsl #3]
	movw	r2, #65535
	mov	r4, r0
	cmp	r1, r2
	beq	.L3598
	add	r2, r8, r0, lsl #3
	ldrsh	r2, [r2, #2]
	cmp	r2, #0
	bge	.L3598
	bl	pm_flush_id
.L3598:
	ldr	r2, .L3605+28
	mov	r1, r4
	mov	r0, r7
	strb	r4, [r2]
	bl	load_l2p_region
	b	.L3594
.L3606:
	.align	2
.L3605:
	.word	.LANCHOR128
	.word	.LC212
	.word	.LANCHOR131
	.word	.LANCHOR135
	.word	.LANCHOR31
	.word	.LANCHOR112
	.word	.LANCHOR136
	.word	.LANCHOR223
	.size	pm_log2phys, .-pm_log2phys
	.section	.text.gc_recovery,"ax",%progbits
	.align	1
	.global	gc_recovery
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	gc_recovery, %function
gc_recovery:
	@ args = 0, pretend = 0, frame = 40
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, r8, r10, fp, lr}
	movs	r5, #0
	ldr	r4, .L3717
	sub	sp, sp, #72
	ldr	r3, .L3717+4
	ldr	fp, [r4]
	strb	r5, [r3]
	ldr	r3, .L3717+8
	ldrh	r6, [fp, #80]
	strb	r5, [r3]
	movw	r3, #65535
	cmp	r6, r3
	beq	.L3608
	strh	r3, [fp, #130]	@ movhi
	movs	r0, #1
	bl	buf_alloc
	ldrb	r3, [fp, #89]	@ zero_extendqisi2
	mov	r7, r0
	ldr	r2, .L3717+12
	ldr	r5, .L3717+16
	add	r3, fp, r3, lsl #1
	ldrh	r2, [r2]
	ldrb	r1, [r5]	@ zero_extendqisi2
	ldrh	r3, [r3, #94]
	str	r5, [sp, #36]
	cmp	r1, #2
	mul	r2, r2, r3
	str	r2, [sp, #64]
	beq	.L3609
	ldr	r3, .L3717+20
	ldrb	r3, [r3]	@ zero_extendqisi2
	cbnz	r3, .L3609
	ldr	r3, .L3717+24
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L3610
.L3609:
	ldr	r3, .L3717+28
	ldrh	r3, [r3]
	subs	r3, r3, #1
	add	r3, r3, r2
	orr	r3, r3, r1, lsl #24
.L3709:
	str	r3, [r7, #24]
.L3611:
	movs	r1, #1
	mov	r0, r7
	bl	sblk_read_page
	ldr	r3, [r7, #36]
	adds	r2, r3, #1
	beq	.L3612
	cmp	r3, #512
	beq	.L3612
	ldr	r2, [r7, #12]
	ldr	r3, .L3717+32
	ldr	r2, [r2]
	str	r3, [sp, #40]
	cmp	r2, r3
	beq	.L3613
.L3612:
	mov	r0, r7
	bl	zbuf_free
	ldr	r2, [r7, #12]
	ldr	r3, [r7, #4]
	ldr	r0, .L3717+36
	ldr	r1, [r2, #12]
	str	r1, [sp, #24]
	ldr	r1, [r2, #8]
	str	r1, [sp, #20]
	ldr	r1, [r2, #4]
	str	r1, [sp, #16]
	ldr	r2, [r2]
	str	r2, [sp, #12]
	ldr	r2, [r3, #12]
	str	r2, [sp, #8]
	ldr	r2, [r3, #8]
	str	r2, [sp, #4]
	ldr	r2, [r3, #4]
	str	r2, [sp]
	ldr	r2, [r7, #36]
	ldr	r3, [r3]
	ldr	r1, [r7, #24]
	bl	printf
.L3716:
	ldr	r3, .L3717+40
	ldrh	r1, [fp, #80]
	ldr	r2, [r3]
	movs	r3, #0
	strh	r3, [r2, r1, lsl #1]	@ movhi
	ldr	r2, [r4]
	mov	r4, r3
	ldrh	r1, [fp, #80]
	strh	r1, [r2, #130]	@ movhi
.L3614:
	ldr	r3, .L3717+40
	ldrh	r0, [fp, #80]
	ldr	r3, [r3]
	ldrh	r3, [r3, r0, lsl #1]
	cbnz	r3, .L3658
	bl	ftl_dump_write_open_sblk
.L3658:
	mov	r2, r4
	ldrh	r1, [fp, #80]
	movw	r5, #65535
	ldr	r0, .L3717+44
	ldr	r4, .L3717
	bl	printf
	strh	r5, [fp, #80]	@ movhi
	bl	pm_flush
	bl	ftl_ext_info_flush
	ldr	r3, [r4]
	ldrh	r3, [r3, #130]
	cmp	r3, r5
	beq	.L3659
	ldr	r2, .L3717+48
	ldrh	r2, [r2]
	cmp	r2, r3
	bhi	.L3660
	movw	r2, #517
	ldr	r1, .L3717+52
	ldr	r0, .L3717+56
	bl	printf
.L3660:
	ldr	r3, [r4]
	ldrh	r0, [r3, #130]
	bl	ftl_free_sblk
.L3659:
	ldr	r3, .L3717+60
	movs	r0, #0
	ldr	r2, [r3]
	movw	r3, #65535
	strh	r3, [r2, #126]	@ movhi
	ldr	r2, [r4]
	strh	r3, [r2, #130]	@ movhi
	bl	ftl_info_flush
.L3607:
	add	sp, sp, #72
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r10, fp, pc}
.L3610:
	cmp	r1, #3
	bne	.L3611
	ldr	r3, .L3717+64
	ldrh	r3, [r3]
	subs	r3, r3, #1
	add	r3, r3, r2
	orr	r3, r3, #50331648
	b	.L3709
.L3613:
	ldr	r3, .L3717+68
	ldr	r5, .L3717+28
	ldr	r6, .L3717+72
	ldrb	r2, [r3]	@ zero_extendqisi2
	str	r3, [sp, #44]
	ldr	r8, .L3717+88
	cmp	r2, #2
	bne	.L3615
	ldr	r3, [sp, #36]
	ldrb	r2, [r3]	@ zero_extendqisi2
	cmp	r2, #3
	bne	.L3615
	ldrh	r2, [r5]
	ldr	r10, .L3717+80
	ldr	r0, [r8]
	lsls	r1, r2, #2
	ldrb	r2, [r6]	@ zero_extendqisi2
	ldrh	ip, [r10]
	smulbb	r2, r2, r1
	ldr	r1, [r7, #4]
	sub	r2, r2, ip
	lsr	ip, ip, #2
	uxth	r2, r2
	add	r0, r0, ip, lsl #2
	bl	ftl_memcpy
	ldr	r2, .L3717+20
	ldrb	r2, [r2]	@ zero_extendqisi2
	cbnz	r2, .L3616
	ldr	r2, .L3717+24
	ldrb	r2, [r2]	@ zero_extendqisi2
	cbz	r2, .L3617
.L3616:
	ldr	r2, [r7, #24]
	subs	r2, r2, #1
.L3710:
	str	r2, [r7, #24]
	movs	r1, #1
	mov	r0, r7
	bl	sblk_read_page
	ldr	r2, [r7, #36]
	adds	r3, r2, #1
	beq	.L3619
	cmp	r2, #512
	beq	.L3619
	ldr	r2, [r7, #12]
	ldr	r3, [sp, #40]
	ldr	r2, [r2]
	cmp	r2, r3
	beq	.L3620
.L3619:
	mov	r0, r7
	bl	zbuf_free
	b	.L3716
.L3617:
	ldr	r1, .L3717+64
	ldr	r2, [sp, #64]
	ldrh	r1, [r1]
	subs	r2, r2, #1
	add	r2, r2, r1
	orr	r2, r2, #33554432
	b	.L3710
.L3620:
	ldrh	r2, [r10]
.L3711:
	ldr	r1, [r7, #4]
	ldr	r0, [r8]
	bl	ftl_memcpy
	ldrh	r3, [r5]
	ldrb	r2, [r6]	@ zero_extendqisi2
	ldr	r10, .L3717+92
	muls	r2, r3, r2
	ldr	r3, .L3717+76
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, r2, asr #6
	lsl	r2, r2, #2
	bge	.L3622
	movs	r1, #0
	ldr	r0, [r10]
	bl	ftl_memset
	ldr	r3, [sp, #44]
	ldrb	r8, [r3]	@ zero_extendqisi2
	cmp	r8, #1
	bne	.L3663
	ldrh	r1, [r5]
	ldrb	r3, [r6]	@ zero_extendqisi2
	ldr	r2, .L3717+80
	ldr	r0, [r10]
	muls	r3, r1, r3
	ldrh	r4, [r2]
	ldr	r1, [r7, #4]
	lsls	r3, r3, #2
	subs	r4, r4, r3
	add	r1, r1, r3
	mov	r2, r4
	bl	ftl_memcpy
	str	r8, [sp, #44]
.L3623:
	ldr	r3, .L3717+64
	ldrh	r3, [r3]
	str	r3, [sp, #40]
	ldr	r3, [sp, #36]
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, #2
	str	r3, [sp, #36]
	bne	.L3624
	ldr	r3, .L3717+84
	ldrb	r3, [r3]	@ zero_extendqisi2
	cbz	r3, .L3625
.L3624:
	ldr	r3, .L3717+20
	ldrb	r3, [r3]	@ zero_extendqisi2
	cbz	r3, .L3626
.L3625:
	ldr	r3, [sp, #36]
	ldr	r2, [sp, #40]
	muls	r3, r2, r3
	str	r3, [sp, #40]
	movs	r3, #1
	str	r3, [sp, #36]
.L3626:
	movs	r5, #0
	str	r5, [sp, #48]
.L3627:
	ldr	r3, [sp, #40]
	cmp	r3, r5
	bls	.L3640
	add	r3, r5, r5, lsl #1
	mov	r10, #0
	subs	r3, r3, #1
	str	r3, [sp, #52]
	b	.L3641
.L3615:
	ldrh	r1, [r5]
	ldrb	r2, [r6]	@ zero_extendqisi2
	muls	r2, r1, r2
	lsls	r2, r2, #2
	b	.L3711
.L3622:
	ldr	r1, [r7, #4]
	ldr	r0, [r10]
	add	r1, r1, r2
	bl	ftl_memcpy
	movs	r3, #0
.L3712:
	str	r3, [sp, #44]
	movs	r4, #0
	b	.L3623
.L3663:
	movs	r3, #1
	b	.L3712
.L3718:
	.align	2
.L3717:
	.word	.LANCHOR12
	.word	.LANCHOR84
	.word	.LANCHOR156
	.word	.LANCHOR111
	.word	.LANCHOR78
	.word	.LANCHOR35
	.word	.LANCHOR36
	.word	.LANCHOR85
	.word	-178307901
	.word	.LC213
	.word	.LANCHOR11
	.word	.LC215
	.word	.LANCHOR8
	.word	.LANCHOR225
	.word	.LC0
	.word	.LANCHOR110
	.word	.LANCHOR94
	.word	.LANCHOR224
	.word	.LANCHOR79
	.word	.LANCHOR131
	.word	.LANCHOR221
	.word	.LANCHOR80
	.word	.LANCHOR159
	.word	.LANCHOR160
.L3636:
	ldr	r3, [sp, #56]
	ldr	r2, .L3719
	ldrh	r3, [r3, #96]
	ldrh	r2, [r2]
	muls	r3, r2, r3
	ldr	r2, .L3719+4
	ldrb	r1, [r2]	@ zero_extendqisi2
	str	r3, [sp, #64]
	cmp	r1, #2
	beq	.L3628
	ldr	r2, .L3719+8
	ldrb	r2, [r2]	@ zero_extendqisi2
	cmp	r2, #0
	beq	.L3629
.L3628:
	subs	r2, r5, #1
	add	r3, r3, r2
	add	r3, r3, r8
	orr	r3, r3, r1, lsl #24
.L3713:
	str	r3, [r7, #24]
	movs	r1, #1
	mov	r0, r7
	bl	sblk_read_page
	ldr	r3, [sp, #44]
	cbz	r3, .L3633
	ldr	r3, .L3719+12
	ldr	r3, [r3]
	ldr	r2, [r3, r6]
	cbnz	r2, .L3633
	ldr	r2, [r7, #12]
	ldr	r2, [r2, #8]
	str	r2, [r3, r6]
.L3633:
	ldr	r3, .L3719+16
	ldr	r2, [r7, #12]
	ldr	r3, [r3]
	ldr	r1, [r2, #4]
	ldr	r3, [r3, r6]
	cmp	r3, r1
	bne	.L3634
	ldr	r0, .L3719+12
	ldr	r0, [r0]
	ldr	ip, [r0, r6]
	ldr	r0, [r2, #8]
	cmp	ip, r0
	beq	.L3635
.L3634:
	ldr	r0, [r2, #12]
	str	r0, [sp, #16]
	ldr	r0, [r2, #8]
	str	r1, [sp, #8]
	str	r0, [sp, #12]
	ldr	r2, [r2]
	ldr	r0, .L3719+20
	str	r2, [sp, #4]
	ldr	r2, .L3719+12
	ldr	r2, [r2]
	ldr	r2, [r2, r6]
	str	r2, [sp]
	ldr	r2, [r7, #36]
	ldr	r1, [r7, #24]
	bl	printf
	ldr	r3, .L3719+16
	ldr	r3, [r3]
	ldr	r3, [r3, r6]
	adds	r3, r3, #1
	beq	.L3635
	mov	r0, r7
	bl	zbuf_free
	ldr	r3, .L3719+24
	movs	r1, #0
	ldrh	r2, [fp, #80]
	ldr	r3, [r3]
	strh	r1, [r3, r2, lsl #1]	@ movhi
	ldr	r3, .L3719+28
	ldrh	r2, [fp, #80]
	ldr	r3, [r3]
	strh	r2, [r3, #130]	@ movhi
	b	.L3614
.L3629:
	cmp	r1, #3
	bne	.L3631
	ldr	r2, .L3719+32
	ldrb	r2, [r2]	@ zero_extendqisi2
	cbz	r2, .L3632
	ldr	r2, [sp, #52]
	add	r3, r3, r2
	add	r3, r3, r8
	orr	r3, r3, #50331648
	b	.L3713
.L3632:
	add	r3, r3, r5
	orr	r3, r3, r8, lsl #24
	b	.L3713
.L3631:
	add	r3, r3, r5
	b	.L3713
.L3635:
	ldr	r3, [sp, #48]
	add	r8, r8, #1
	adds	r6, r6, #4
	adds	r3, r3, #1
	str	r3, [sp, #48]
.L3638:
	ldr	r3, [sp, #36]
	cmp	r3, r8
	bcs	.L3636
	add	r10, r10, #1
.L3641:
	ldrb	r3, [fp, #89]	@ zero_extendqisi2
	cmp	r10, r3
	bge	.L3637
	ldr	r3, [sp, #48]
	mov	r8, #1
	lsls	r6, r3, #2
	add	r3, fp, r10, lsl #1
	str	r3, [sp, #56]
	b	.L3638
.L3637:
	ldr	r3, .L3719+36
	ldrb	r3, [r3]	@ zero_extendqisi2
	cbz	r3, .L3639
	adds	r5, r5, #1
.L3639:
	adds	r5, r5, #1
	b	.L3627
.L3640:
	mov	r0, r7
	movs	r4, #0
	bl	zbuf_free
	ldr	r3, .L3719+24
	mov	r10, r4
	ldr	r0, .L3719+40
	mov	r8, r4
	ldrh	r1, [fp, #80]
	ldr	r2, [r3]
	ldrh	r0, [r0]
	ldrb	r3, [fp, #89]	@ zero_extendqisi2
	smulbb	r3, r3, r0
	strh	r3, [r2, r1, lsl #1]	@ movhi
.L3642:
	ldr	r3, [sp, #40]
	cmp	r3, r10
	bls	.L3656
	add	r2, r10, r10, lsl #1
	movs	r7, #0
	subs	r3, r2, #1
	str	r3, [sp, #52]
	b	.L3657
.L3652:
	ldr	r3, .L3719+16
	ldr	r2, [r3]
	ldr	r3, [r2, r8, lsl #2]
	str	r3, [sp, #44]
	adds	r3, r3, #1
	beq	.L3643
	ldr	r3, .L3719+12
	ldr	r0, [sp, #44]
	ldr	r2, [r3]
	ldr	r3, [r2, r8, lsl #2]
	str	r3, [sp, #48]
	bl	lpa_hash_get_ppa
	str	r0, [sp, #68]
	adds	r0, r0, #1
	bne	.L3644
	movs	r2, #0
	add	r1, sp, #68
	ldr	r0, [sp, #44]
	bl	pm_log2phys
.L3644:
	ldr	r3, [sp, #56]
	ldr	r1, .L3719
	ldrh	r2, [r3, #96]
	ldrh	r1, [r1]
	muls	r1, r2, r1
	ldr	r2, .L3719+4
	ldrb	r0, [r2]	@ zero_extendqisi2
	cmp	r0, #2
	beq	.L3645
	ldr	r2, .L3719+8
	ldrb	r2, [r2]	@ zero_extendqisi2
	cmp	r2, #0
	beq	.L3646
.L3645:
	add	r2, r10, #-1
	add	r2, r2, r1
	add	r2, r2, r5
	orr	r2, r2, r0, lsl #24
.L3715:
	str	r2, [sp, #64]
.L3647:
	ldr	r2, .L3719+44
	ldr	r3, [sp, #48]
	ldrh	r1, [r2]
	ldr	r2, .L3719+48
	ldrb	r0, [r2]	@ zero_extendqisi2
	movs	r2, #1
	lsr	r6, r3, r1
	str	r2, [sp, #60]
	rsb	r0, r0, #24
	subs	r0, r0, r1
	ldr	r1, .L3719+52
	lsl	r0, r2, r0
	subs	r0, r0, #1
	ldrb	r1, [r1]	@ zero_extendqisi2
	ands	r0, r0, r6
	bl	__aeabi_uidiv
	ldr	r1, [sp, #68]
	mov	r6, r0
	ldr	r3, [sp, #48]
	ldr	r2, [sp, #60]
	cmp	r3, r1
	bne	.L3650
	add	r1, sp, #64
	ldr	r0, [sp, #44]
	bl	pm_log2phys
	uxth	r0, r6
	adds	r4, r4, #1
	bl	ftl_vpn_decrement
.L3651:
	ldr	r2, .L3719+56
	uxth	r6, r6
	add	r8, r8, #1
	ldr	r2, [r2]
	add	r2, r2, r6, lsl #2
	ldrb	r2, [r2, #2]	@ zero_extendqisi2
	ands	r2, r2, #224
	bne	.L3643
	ldr	r1, .L3719+24
	ldr	r1, [r1]
	ldrh	r0, [r1, r6, lsl #1]
	cbz	r0, .L3643
	strh	r2, [r1, r6, lsl #1]	@ movhi
.L3643:
	adds	r5, r5, #1
.L3654:
	ldr	r3, [sp, #36]
	cmp	r3, r5
	bcs	.L3652
	adds	r7, r7, #1
.L3657:
	ldrb	r2, [fp, #89]	@ zero_extendqisi2
	cmp	r7, r2
	bge	.L3653
	add	r3, fp, r7, lsl #1
	movs	r5, #1
	str	r3, [sp, #56]
	b	.L3654
.L3646:
	cmp	r0, #3
	bne	.L3648
	ldr	r2, .L3719+32
	lsls	r0, r5, #24
	ldrb	r2, [r2]	@ zero_extendqisi2
	cbz	r2, .L3649
	ldr	r3, [sp, #52]
	adds	r2, r1, r3
	add	r2, r2, r5
.L3714:
	orrs	r2, r2, r0
	b	.L3715
.L3649:
	add	r2, r10, r1
	b	.L3714
.L3648:
	add	r1, r1, r10
	str	r1, [sp, #64]
	b	.L3647
.L3650:
	ldr	r2, [sp, #64]
	cmp	r1, r2
	it	eq
	addeq	r4, r4, #1
	b	.L3651
.L3653:
	ldr	r2, .L3719+36
	ldrb	r2, [r2]	@ zero_extendqisi2
	cbz	r2, .L3655
	add	r10, r10, #1
.L3655:
	add	r10, r10, #1
	b	.L3642
.L3656:
	ldr	r3, .L3719+24
	ldrh	r2, [fp, #80]
	ldr	r3, [r3]
	strh	r4, [r3, r2, lsl #1]	@ movhi
	ldrh	r0, [fp, #80]
	bl	zftl_insert_data_list
	b	.L3614
.L3720:
	.align	2
.L3719:
	.word	.LANCHOR111
	.word	.LANCHOR78
	.word	.LANCHOR35
	.word	.LANCHOR160
	.word	.LANCHOR159
	.word	.LC214
	.word	.LANCHOR11
	.word	.LANCHOR12
	.word	.LANCHOR36
	.word	.LANCHOR80
	.word	.LANCHOR85
	.word	.LANCHOR74
	.word	.LANCHOR31
	.word	.LANCHOR75
	.word	.LANCHOR9
.L3608:
	ldrh	r3, [fp, #130]
	cmp	r3, r6
	beq	.L3607
	ldr	r7, .L3721
	ldr	r2, [r7]
	ldrh	r2, [r2, #126]
	cmp	r2, r3
	bne	.L3662
	bl	pm_flush
	ldr	r3, [r4]
	ldrh	r0, [r3, #130]
	bl	ftl_free_sblk
	ldr	r3, [r7]
	mov	r0, r5
	strh	r6, [r3, #126]	@ movhi
	bl	ftl_info_flush
.L3662:
	ldr	r3, [r4]
	movw	r2, #65535
	strh	r2, [r3, #130]	@ movhi
	b	.L3607
.L3722:
	.align	2
.L3721:
	.word	.LANCHOR110
	.size	gc_recovery, .-gc_recovery
	.section	.text.gc_update_l2p_map_new,"ax",%progbits
	.align	1
	.global	gc_update_l2p_map_new
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	gc_update_l2p_map_new, %function
gc_update_l2p_map_new:
	@ args = 0, pretend = 0, frame = 32
	@ frame_needed = 0, uses_anonymous_args = 0
	ldr	r3, .L3757
	push	{r4, r5, r6, r7, r8, r10, fp, lr}
	sub	sp, sp, #32
	ldr	r2, .L3757+4
	ldr	r4, [r3]
	ldrh	r2, [r2]
	ldr	r7, .L3757+8
	ldrb	r1, [r4, #89]	@ zero_extendqisi2
	str	r3, [sp, #20]
	muls	r2, r1, r2
	str	r2, [sp, #4]
	ldr	r2, [r7]
	tst	r2, #256
	beq	.L3724
	ldrh	r1, [r4, #80]
	ldr	r0, .L3757+12
	bl	printf
.L3724:
	ldr	r3, .L3757+16
	movs	r6, #0
	ldr	r0, [sp, #4]
	mov	r5, r6
	ldrh	r1, [r4, #80]
	ldr	r2, [r3]
	ldr	r3, .L3757+20
	ldrb	r3, [r3]	@ zero_extendqisi2
	subs	r3, r0, r3
	strh	r3, [r2, r1, lsl #1]	@ movhi
.L3725:
	ldr	r3, [sp, #4]
	cmp	r5, r3
	bne	.L3734
	ldr	r3, [r7]
	ldr	r5, .L3757+16
	tst	r3, #256
	beq	.L3735
	ldr	r3, [sp, #20]
	ldrh	r0, [r4, #80]
	ldr	r2, [r5]
	ldr	r1, [r3]
	mov	r3, r6
	ldrh	r2, [r2, r0, lsl #1]
	ldrh	r1, [r1, #80]
	ldr	r0, .L3757+24
	bl	printf
.L3735:
	ldrh	r2, [r4, #80]
	ldr	r3, [r5]
	ldrh	r3, [r3, r2, lsl #1]
	cmp	r6, r3
	beq	.L3736
	movw	r2, #898
	ldr	r1, .L3757+28
	ldr	r0, .L3757+32
	bl	printf
.L3736:
	ldrh	r2, [r4, #80]
	ldr	r3, [r5]
	strh	r6, [r3, r2, lsl #1]	@ movhi
	ldrh	r0, [r4, #80]
	bl	zftl_insert_data_list
	add	sp, sp, #32
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r10, fp, pc}
.L3734:
	ldr	r3, .L3757+36
	lsl	r8, r5, #2
	ldr	r3, [r3]
	ldr	r10, [r3, r5, lsl #2]
	cmp	r10, #-1
	beq	.L3726
	ldr	r3, .L3757+40
	mov	r0, r10
	ldrb	r1, [r3]	@ zero_extendqisi2
	lsls	r1, r1, #7
	bl	__aeabi_uidiv
	uxth	r3, r0
	str	r3, [sp, #16]
	ldr	r3, [r7]
	lsls	r1, r3, #23
	bpl	.L3727
	mov	r3, r5
	mov	r2, r10
	ldr	r1, [sp, #16]
	ldr	r0, .L3757+44
	bl	printf
.L3727:
	ldr	fp, .L3757+36
	str	r5, [sp, #12]
.L3733:
	ldr	r3, [fp]
	ldr	r10, [r3, r8]
	cmp	r10, #-1
	beq	.L3728
	ldr	r3, .L3757+40
	mov	r0, r10
	ldrb	r1, [r3]	@ zero_extendqisi2
	lsls	r1, r1, #7
	bl	__aeabi_uidiv
	ldr	r3, [sp, #16]
	uxth	r0, r0
	cmp	r3, r0
	bne	.L3728
	ldr	r3, .L3757+48
	mov	r0, r10
	ldr	r3, [r3]
	ldr	r3, [r3, r8]
	str	r3, [sp, #8]
	bl	lpa_hash_get_ppa
	str	r0, [sp, #28]
	adds	r0, r0, #1
	bne	.L3729
	movs	r2, #0
	add	r1, sp, #28
	mov	r0, r10
	bl	pm_log2phys
.L3729:
	ldr	r3, [sp, #28]
	ldr	r2, [sp, #8]
	cmp	r2, r3
	bne	.L3730
	ldr	r3, .L3757+52
	add	r1, sp, #32
	movs	r2, #1
	mov	r0, r10
	adds	r6, r6, #1
	ldr	r3, [r3]
	ldr	r3, [r3, r8]
	str	r3, [r1, #-8]!
	bl	pm_log2phys
	ldr	r3, .L3757+56
	ldrh	r2, [r3]
	ldr	r3, .L3757+60
	ldrb	r3, [r3]	@ zero_extendqisi2
	rsb	r3, r3, #24
	subs	r0, r3, r2
	movs	r3, #1
	lsls	r3, r3, r0
	ldr	r0, [sp, #8]
	subs	r3, r3, #1
	lsrs	r0, r0, r2
	ldr	r2, .L3757+64
	ands	r0, r0, r3
	ldrb	r1, [r2]	@ zero_extendqisi2
	bl	__aeabi_uidiv
	uxth	r0, r0
.L3756:
	bl	ftl_vpn_decrement
	ldr	r3, [fp]
	mov	r2, #-1
	str	r2, [r3, r8]
.L3728:
	ldr	r3, [sp, #12]
	add	r8, r8, #4
	adds	r3, r3, #1
	str	r3, [sp, #12]
	ldr	r2, [sp, #12]
	ldr	r3, [sp, #4]
	cmp	r3, r2
	bne	.L3733
.L3726:
	adds	r5, r5, #1
	b	.L3725
.L3730:
	ldr	r2, [r7]
	lsls	r2, r2, #23
	bpl	.L3732
	ldr	r2, [sp, #8]
	mov	r1, r10
	ldr	r0, .L3757+68
	bl	printf
.L3732:
	ldrh	r0, [r4, #80]
	b	.L3756
.L3758:
	.align	2
.L3757:
	.word	.LANCHOR12
	.word	.LANCHOR85
	.word	.LANCHOR19
	.word	.LC216
	.word	.LANCHOR11
	.word	.LANCHOR224
	.word	.LC219
	.word	.LANCHOR226
	.word	.LC0
	.word	.LANCHOR159
	.word	.LANCHOR131
	.word	.LC217
	.word	.LANCHOR160
	.word	.LANCHOR161
	.word	.LANCHOR74
	.word	.LANCHOR31
	.word	.LANCHOR75
	.word	.LC218
	.size	gc_update_l2p_map_new, .-gc_update_l2p_map_new
	.section	.text.gc_scan_src_blk_one_page,"ax",%progbits
	.align	1
	.global	gc_scan_src_blk_one_page
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	gc_scan_src_blk_one_page, %function
gc_scan_src_blk_one_page:
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r0, r1, r2, r3, r4, r5, r6, r7, r8, r10, fp, lr}
	movs	r1, #0
	ldr	r4, .L3788
	mov	r0, r1
	movw	r5, #65535
	ldr	r6, .L3788+4
	ldrb	r3, [r4, #4]	@ zero_extendqisi2
	ldrb	ip, [r6]	@ zero_extendqisi2
	add	r2, r4, r3, lsl #1
	ldrh	r7, [r2, #36]
	ldrh	r2, [r4, #2]
.L3760:
	cmp	r7, r5
	beq	.L3762
	cbz	r0, .L3763
	strh	r2, [r4, #2]	@ movhi
.L3763:
	cbz	r1, .L3764
	strb	r3, [r4, #4]
.L3764:
	ldr	r8, .L3788+24
	movs	r0, #1
	ldr	r10, .L3788+28
	mov	fp, #1
	bl	buf_alloc
	mov	r5, r0
.L3765:
	ldrb	r1, [r4, #6]	@ zero_extendqisi2
	cmp	fp, r1
	ble	.L3775
	mov	r0, r5
	bl	zbuf_free
	ldrb	r3, [r4, #4]	@ zero_extendqisi2
	ldrb	r2, [r6]	@ zero_extendqisi2
	adds	r3, r3, #1
	uxtb	r3, r3
	cmp	r2, r3
	strb	r3, [r4, #4]
	bne	.L3759
	ldrh	r3, [r4, #2]
	adds	r3, r3, #1
	strh	r3, [r4, #2]	@ movhi
	movs	r3, #0
	strb	r3, [r4, #4]
.L3759:
	add	sp, sp, #16
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r10, fp, pc}
.L3762:
	adds	r3, r3, #1
	uxtb	r3, r3
	cmp	r3, ip
	itt	eq
	moveq	r3, #0
	addeq	r2, r2, #1
	add	r1, r4, r3, lsl #1
	it	eq
	uxtheq	r2, r2
	ldrh	r7, [r1, #36]
	it	eq
	moveq	r0, #1
	movs	r1, #1
	b	.L3760
.L3775:
	ldrh	r3, [r8]
	cmp	r1, #2
	mul	r2, r7, r3
	bne	.L3766
	ldrh	r3, [r4, #2]
	add	r3, r2, r3, lsl #1
	subs	r3, r3, #1
.L3787:
	ldr	r2, .L3788+8
	add	r3, r3, fp
	ldrb	r2, [r2]	@ zero_extendqisi2
	orr	r3, r3, r2, lsl #24
.L3786:
	str	r3, [r5, #24]
	movs	r1, #1
	mov	r0, r5
	bl	sblk_read_page
	ldr	r3, [r5, #36]
	adds	r2, r3, #1
	beq	.L3772
	cmp	r3, #512
	beq	.L3772
	ldr	r3, [r5, #12]
	ldr	r3, [r3, #4]
	mov	r0, r3
	str	r3, [sp, #4]
	bl	lpa_hash_get_ppa
	str	r0, [sp, #12]
	adds	r0, r0, #1
	ldr	r3, [sp, #4]
	bne	.L3774
	ldr	r2, .L3788+12
	ldr	r2, [r2]
	cmp	r3, r2
	bcs	.L3774
	movs	r2, #0
	add	r1, sp, #12
	mov	r0, r3
	bl	pm_log2phys
.L3774:
	ldr	r2, [r5, #24]
	ldr	r3, [sp, #12]
	cmp	r2, r3
	bne	.L3772
	ldr	r1, .L3788+16
	ldrh	r3, [r4, #20]
	ldr	r1, [r1]
	str	r2, [r1, r3, lsl #2]
	adds	r3, r3, #1
	strh	r3, [r4, #20]	@ movhi
.L3772:
	ldrh	r3, [r4, #22]
	add	fp, fp, #1
	adds	r3, r3, #1
	strh	r3, [r4, #22]	@ movhi
	b	.L3765
.L3766:
	cmp	r1, #3
	bne	.L3768
	ldrb	r3, [r10]	@ zero_extendqisi2
	cbnz	r3, .L3769
	ldr	r3, .L3788+20
	ldrb	r3, [r3]	@ zero_extendqisi2
	cbz	r3, .L3770
.L3769:
	ldrh	r3, [r4, #2]
	add	r3, r3, r3, lsl #1
	subs	r3, r3, #1
	add	r3, r3, r2
	b	.L3787
.L3770:
	ldrh	r3, [r4, #2]
	add	r3, r3, r2
	orr	r3, r3, fp, lsl #24
	b	.L3786
.L3768:
	ldrh	r3, [r4, #2]
	add	r3, r3, r2
	b	.L3786
.L3789:
	.align	2
.L3788:
	.word	.LANCHOR70
	.word	.LANCHOR79
	.word	.LANCHOR78
	.word	.LANCHOR128
	.word	.LANCHOR76
	.word	.LANCHOR36
	.word	.LANCHOR111
	.word	.LANCHOR35
	.size	gc_scan_src_blk_one_page, .-gc_scan_src_blk_one_page
	.section	.text.gc_scan_src_blk,"ax",%progbits
	.align	1
	.global	gc_scan_src_blk
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	gc_scan_src_blk, %function
gc_scan_src_blk:
	@ args = 0, pretend = 0, frame = 32
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, r8, r10, fp, lr}
	movw	r3, #65535
	ldr	r4, .L3855
	sub	sp, sp, #32
	ldrh	r2, [r4]
	cmp	r2, r3
	bne	.L3791
	movw	r2, #1505
	ldr	r1, .L3855+4
	ldr	r0, .L3855+8
	bl	printf
.L3791:
	ldrh	r1, [r4]
	movw	r3, #65535
	cmp	r1, r3
	beq	.L3823
	ldr	r3, .L3855+12
	ldr	r3, [r3]
	lsls	r0, r3, #23
	bpl	.L3793
	ldr	r3, .L3855+16
	ldr	r0, .L3855+20
	ldr	r3, [r3]
	ldrh	r2, [r3, r1, lsl #1]
	bl	printf
.L3793:
	ldr	r1, .L3855+24
	ldrh	r0, [r4]
	bl	ftl_get_blk_list_in_sblk
	uxtb	r0, r0
	strb	r0, [r4, #5]
	cbnz	r0, .L3794
	movw	r3, #65535
	strh	r3, [r4]	@ movhi
.L3790:
	add	sp, sp, #32
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r10, fp, pc}
.L3794:
	ldr	r5, .L3855+28
	ldrh	r3, [r4]
	ldr	r2, [r5]
	add	r2, r2, r3, lsl #2
	ldrb	r2, [r2, #2]	@ zero_extendqisi2
	and	r2, r2, #224
	cmp	r2, #32
	beq	.L3795
	cmp	r2, #224
	beq	.L3795
	cbz	r2, .L3796
	ldr	r2, .L3855+32
	ldr	r2, [r2]
	ldrh	r1, [r2, #16]
	cmp	r1, r3
	beq	.L3795
	ldrh	r1, [r2, #48]
	cmp	r1, r3
	beq	.L3795
	ldrh	r2, [r2, #80]
	cmp	r2, r3
	bne	.L3849
.L3795:
	movw	r3, #65535
	movs	r0, #0
	strh	r3, [r4]	@ movhi
	strh	r0, [r4, #20]	@ movhi
	b	.L3790
.L3796:
	ldr	r5, .L3855+16
	ldr	r1, [r5]
	ldrh	r3, [r1, r3, lsl #1]
	cbz	r3, .L3798
	movw	r2, #1530
	ldr	r1, .L3855+4
	ldr	r0, .L3855+8
	bl	printf
.L3798:
	ldrh	r2, [r4]
	movs	r1, #0
	ldr	r3, [r5]
	strh	r1, [r3, r2, lsl #1]	@ movhi
	b	.L3795
.L3849:
	add	r0, r4, r0, lsl #1
	movw	r3, #65535
	ldrh	r7, [r0, #34]
	cmp	r7, r3
	bne	.L3799
	movw	r2, #1540
	ldr	r1, .L3855+4
	ldr	r0, .L3855+8
	bl	printf
.L3799:
	ldrh	ip, [r4]
	ldr	r1, [r5]
	ldr	r6, .L3855+36
	ldr	r0, .L3855+40
	add	r1, r1, ip, lsl #2
	ldrh	r3, [r6]
	ldrh	r2, [r0]
	mov	r8, r6
	ldrb	r1, [r1, #2]	@ zero_extendqisi2
	subs	r3, r3, #1
	str	r0, [sp, #12]
	uxth	r3, r3
	and	r1, r1, #224
	muls	r2, r7, r2
	cmp	r1, #160
	bne	.L3824
	ldr	r1, .L3855+44
	ldrb	r1, [r1]	@ zero_extendqisi2
	cmp	r1, #2
	it	eq
	ldreq	r3, .L3855+48
	uxth	r10, r1
	orr	r2, r2, r1, lsl #24
	ldr	r1, .L3855+52
	it	eq
	ldrheq	r3, [r3]
	ldrb	r1, [r1]	@ zero_extendqisi2
	itt	eq
	addeq	r3, r3, #-1
	uxtheq	r3, r3
	cbnz	r1, .L3802
	ldr	r1, .L3855+56
	ldrb	r1, [r1]	@ zero_extendqisi2
	cbz	r1, .L3800
.L3802:
	ldr	r3, .L3855+48
	ldrh	r3, [r3]
	subs	r3, r3, #1
	uxth	r3, r3
.L3800:
	movs	r6, #0
	strb	r10, [r4, #6]
	orrs	r3, r3, r2
	movs	r0, #1
	str	r3, [sp, #4]
	strh	r6, [r4, #2]	@ movhi
	strb	r6, [r4, #4]
	strh	r6, [r4, #22]	@ movhi
	strh	r6, [r4, #24]	@ movhi
	bl	buf_alloc
	ldr	r3, [sp, #4]
	mov	r5, r0
	movs	r1, #1
	str	r3, [r0, #24]
	bl	sblk_read_page
	ldr	r3, [r5, #36]
	strh	r6, [r4, #20]	@ movhi
	adds	r1, r3, #1
	beq	.L3853
	cmp	r3, #512
	bne	.L3804
.L3853:
	mov	r0, r5
	bl	zbuf_free
.L3851:
	mov	r0, #-1
	b	.L3790
.L3824:
	mov	r10, #1
	b	.L3800
.L3804:
	ldr	r6, [r5, #12]
	ldr	r3, .L3855+60
	ldr	r2, [r6]
	str	r3, [sp, #16]
	cmp	r2, r3
	beq	.L3805
	movw	r2, #1578
.L3854:
	ldr	r1, .L3855+4
	ldr	r0, .L3855+8
	bl	printf
	b	.L3853
.L3805:
	ldr	r3, .L3855+64
	ldrh	r2, [r8]
	ldrb	r3, [r3]	@ zero_extendqisi2
	smulbb	r2, r2, r3
	smulbb	r2, r2, r10
	uxth	r2, r2
	str	r2, [sp, #8]
	ldr	r2, .L3855+68
	ldrb	r2, [r2]	@ zero_extendqisi2
	cmp	r2, #2
	bne	.L3806
	cmp	r10, #3
	bne	.L3806
	ldr	r2, .L3855+48
	ldr	fp, .L3855+84
	ldr	r10, .L3855+76
	ldrh	r6, [r2]
	ldrh	r0, [fp]
	ldr	r1, [r5, #4]
	lsls	r6, r6, #2
	smulbb	r6, r6, r3
	ldr	r3, [r10]
	subs	r6, r6, r0
	lsrs	r0, r0, #2
	uxth	r6, r6
	add	r0, r3, r0, lsl #2
	mov	r2, r6
	bl	ftl_memcpy
	ldr	r3, [r5, #12]
	ldr	r3, [r3, #4]
	str	r3, [sp, #20]
	cbz	r3, .L3807
	mov	r1, r6
	ldr	r0, [r5, #4]
	bl	js_hash
	ldr	r3, [sp, #20]
	cmp	r3, r0
	beq	.L3807
	mov	r0, r5
	bl	zbuf_free
	ldr	r1, [r5, #12]
	mov	r3, r6
.L3852:
	ldr	r2, [r5, #24]
	ldr	r1, [r1, #4]
	ldr	r0, .L3855+72
	bl	printf
	b	.L3851
.L3807:
	ldr	r3, .L3855+52
	ldrb	r3, [r3]	@ zero_extendqisi2
	cbnz	r3, .L3808
	ldr	r3, .L3855+56
	ldrb	r3, [r3]	@ zero_extendqisi2
	cbz	r3, .L3809
.L3808:
	ldr	r3, [sp, #4]
	subs	r3, r3, #1
	str	r3, [r5, #24]
.L3810:
	movs	r1, #1
	mov	r0, r5
	bl	sblk_read_page
	ldr	r3, [r5, #36]
	adds	r2, r3, #1
	beq	.L3853
	cmp	r3, #512
	beq	.L3853
	ldr	r3, [r5, #12]
	ldr	r2, [sp, #16]
	ldr	r3, [r3]
	cmp	r3, r2
	beq	.L3813
	movw	r2, #1619
	b	.L3854
.L3809:
	ldr	r2, [sp, #12]
	ldrh	r3, [r8]
	ldrh	r2, [r2]
	subs	r3, r3, #1
	uxth	r3, r3
	muls	r7, r2, r7
	orr	r3, r3, #33554432
	orrs	r7, r7, r3
	str	r7, [r5, #24]
	b	.L3810
.L3813:
	ldrh	r2, [fp]
	ldr	r1, [r5, #4]
	ldr	r0, [r10]
.L3850:
	ldr	r7, .L3855+76
	mov	r8, #0
	bl	ftl_memcpy
	ldr	r10, .L3855+88
	ldr	r6, [r7]
	ldr	fp, .L3855+92
	subs	r6, r6, #4
.L3816:
	ldr	r3, [sp, #8]
	cmp	r8, r3
	blt	.L3821
	mov	r0, r5
	ldr	r5, .L3855+16
	bl	zbuf_free
	ldrh	r1, [r4]
	ldr	r3, [r5]
	ldrh	r2, [r3, r1, lsl #1]
	ldrh	r3, [r4, #20]
	cmp	r2, r3
	beq	.L3822
	ldr	r0, .L3855+80
	bl	printf
.L3822:
	ldr	r3, [r5]
	ldrh	r1, [r4, #20]
	ldrh	r2, [r4]
	strh	r1, [r3, r2, lsl #1]	@ movhi
	movs	r3, #0
	strh	r3, [r4, #24]	@ movhi
	ldrh	r0, [r4, #20]
	b	.L3790
.L3856:
	.align	2
.L3855:
	.word	.LANCHOR70
	.word	.LANCHOR227
	.word	.LC0
	.word	.LANCHOR19
	.word	.LANCHOR11
	.word	.LC220
	.word	.LANCHOR70+36
	.word	.LANCHOR9
	.word	.LANCHOR12
	.word	.LANCHOR94
	.word	.LANCHOR111
	.word	.LANCHOR78
	.word	.LANCHOR85
	.word	.LANCHOR35
	.word	.LANCHOR36
	.word	-178307901
	.word	.LANCHOR79
	.word	.LANCHOR224
	.word	.LC221
	.word	.LANCHOR76
	.word	.LC222
	.word	.LANCHOR221
	.word	.LANCHOR74
	.word	.LANCHOR31
.L3806:
	ldr	r3, [sp, #8]
	ldr	r8, [r5, #4]
	lsls	r7, r3, #2
	mov	r0, r8
	mov	r1, r7
	bl	js_hash
	ldr	r3, [r6, #4]
	cmp	r3, r0
	beq	.L3815
	mov	r0, r5
	bl	zbuf_free
	ldr	r1, [r5, #12]
	mov	r3, r7
	b	.L3852
.L3815:
	ldr	r3, .L3857
	mov	r2, r7
	mov	r1, r8
	ldr	r0, [r3]
	b	.L3850
.L3821:
	ldr	r0, [r6, #4]!
	adds	r3, r0, #1
	beq	.L3818
	bl	lpa_hash_get_ppa
	str	r0, [sp, #28]
	adds	r0, r0, #1
	bne	.L3819
	movs	r2, #0
	add	r1, sp, #28
	ldr	r0, [r6]
	bl	pm_log2phys
.L3819:
	ldrb	r3, [fp]	@ zero_extendqisi2
	ldr	r2, [sp, #28]
	ldrh	r1, [r10]
	rsb	r3, r3, #24
	str	r2, [sp, #4]
	subs	r0, r3, r1
	movs	r3, #1
	lsls	r3, r3, r0
	lsr	r0, r2, r1
	ldr	r1, .L3857+4
	subs	r3, r3, #1
	ands	r0, r0, r3
	ldrb	r1, [r1]	@ zero_extendqisi2
	bl	__aeabi_uidiv
	ldrh	r3, [r4]
	ldr	r2, [sp, #4]
	cmp	r0, r3
	bne	.L3818
	ldrh	r3, [r4, #20]
	ldr	r1, [r7]
	str	r2, [r1, r3, lsl #2]
	adds	r3, r3, #1
	strh	r3, [r4, #20]	@ movhi
.L3818:
	add	r8, r8, #1
	b	.L3816
.L3823:
	movs	r0, #0
	b	.L3790
.L3858:
	.align	2
.L3857:
	.word	.LANCHOR76
	.word	.LANCHOR75
	.size	gc_scan_src_blk, .-gc_scan_src_blk
	.section	.text.gc_scan_static_data,"ax",%progbits
	.align	1
	.global	gc_scan_static_data
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	gc_scan_static_data, %function
gc_scan_static_data:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r0, r1, r4, r5, r6, r7, r8, r10, fp, lr}
	ldr	r4, .L3875
	ldr	r3, [r4]
	ldr	r2, [r3, #544]
	adds	r2, r2, #1
	beq	.L3860
	ldr	r8, .L3875+28
	movs	r6, #0
	ldr	r10, .L3875+32
.L3868:
	ldr	r3, [r4]
	movs	r2, #0
	add	r1, sp, #4
	uxth	r7, r6
	ldr	r0, [r3, #544]
	bl	pm_log2phys
	ldr	r3, [sp, #4]
	adds	r3, r3, #1
	beq	.L3861
	movs	r0, #1
	bl	buf_alloc
	ldr	r3, [sp, #4]
	mov	r5, r0
	movs	r1, #1
	str	r3, [r0, #24]
	bl	sblk_read_page
	ldr	r3, [r5, #36]
	cmp	r3, #256
	bne	.L3862
	ldr	r3, .L3875+4
	mov	fp, #1
	ldr	r2, [sp, #4]
	ldrh	r0, [r3]
	ldr	r3, .L3875+8
	ldrb	r3, [r3]	@ zero_extendqisi2
	rsb	r3, r3, #24
	subs	r3, r3, r0
	lsr	r0, r2, r0
	lsl	r3, fp, r3
	ldr	r2, .L3875+12
	subs	r3, r3, #1
	ldrb	r1, [r2]	@ zero_extendqisi2
	ands	r0, r0, r3
	bl	__aeabi_uidiv
	movs	r2, #0
	mov	r1, fp
	uxth	r0, r0
	bl	gc_add_sblk
.L3862:
	ldr	r2, [r5, #12]
	ldr	r3, [r4]
	ldr	r2, [r2, #4]
	ldr	r3, [r3, #544]
	cmp	r2, r3
	beq	.L3863
	movw	r2, #2163
	mov	r1, r8
	mov	r0, r10
	bl	printf
.L3863:
	mov	r0, r5
	bl	zbuf_free
.L3861:
	ldr	r3, [r4]
	ldr	r1, .L3875+16
	ldr	r2, [r3, #544]
	ldr	r1, [r1]
	adds	r2, r2, #1
	cmp	r2, r1
	str	r2, [r3, #544]
	bcc	.L3864
	mov	r2, #-1
	str	r2, [r3, #544]
	ldr	r2, [r3, #548]
	adds	r2, r2, #1
	str	r2, [r3, #548]
	bl	ftl_flush
	bl	pm_flush
	bl	ftl_ext_info_flush
	movs	r0, #0
	bl	ftl_info_flush
.L3859:
	add	sp, sp, #8
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r10, fp, pc}
.L3864:
	ldr	r3, [sp, #4]
	adds	r3, r3, #1
	bne	.L3859
	ldr	r3, .L3875+20
	adds	r6, r6, #1
	ldrh	r3, [r3]
	cmp	r7, r3, lsr #2
	bcc	.L3868
	b	.L3859
.L3860:
	ldr	r2, [r3, #536]
	ldr	r1, [r3, #12]
	ldr	r0, .L3875+24
	add	r2, r2, #12910592
	add	r2, r2, #49408
	cmp	r1, r2
	bhi	.L3870
	ldr	r4, [r0]
	ldr	r2, [r3, #540]
	ldr	r4, [r4, #44]
	add	r2, r2, #4992
	adds	r2, r2, #8
	cmp	r4, r2
	bls	.L3859
.L3870:
	ldr	r2, [r0]
	ldr	r2, [r2, #44]
	str	r1, [r3, #536]
	str	r2, [r3, #540]
	movs	r2, #0
	str	r2, [r3, #544]
	b	.L3859
.L3876:
	.align	2
.L3875:
	.word	.LANCHOR12
	.word	.LANCHOR74
	.word	.LANCHOR31
	.word	.LANCHOR75
	.word	.LANCHOR128
	.word	.LANCHOR221
	.word	.LANCHOR110
	.word	.LANCHOR228
	.word	.LC0
	.size	gc_scan_static_data, .-gc_scan_static_data
	.section	.text.ftl_sblk_dump,"ax",%progbits
	.align	1
	.global	ftl_sblk_dump
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	ftl_sblk_dump, %function
ftl_sblk_dump:
	@ args = 0, pretend = 0, frame = 88
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, r8, r10, fp, lr}
	lsls	r3, r0, #2
	ldr	r4, .L3920
	sub	sp, sp, #128
	lsls	r2, r0, #2
	mov	r6, r0
	str	r3, [sp, #76]
	ldr	r3, [r4]
	str	r1, [sp, #68]
	ldr	r1, [r3, r0, lsl #2]
	adds	r2, r3, r2
	ldrb	r2, [r2, #2]	@ zero_extendqisi2
	ubfx	r1, r1, #11, #8
	str	r1, [sp, #4]
	mov	r1, r0
	ldrh	r3, [r3, r0, lsl #2]
	ldr	r0, .L3920+4
	ubfx	r3, r3, #0, #11
	str	r3, [sp]
	ubfx	r3, r2, #3, #2
	lsrs	r2, r2, #5
	bl	printf
	movw	r3, #65535
	cmp	r6, r3
	beq	.L3900
	ldr	r3, .L3920+8
	ldrh	r3, [r3]
	cmp	r3, r6
	bls	.L3900
	ldr	r3, [r4]
	lsls	r2, r6, #2
	add	r1, sp, #112
	strh	r6, [sp, #96]	@ movhi
	mov	r0, r6
	movs	r5, #0
	add	r3, r3, r2
	mov	r10, r5
	ldrb	r3, [r3, #2]	@ zero_extendqisi2
	and	r3, r3, #224
	cmp	r3, #160
	itet	eq
	ldreq	r3, .L3920+12
	movne	fp, #1
	ldrbeq	fp, [r3]	@ zero_extendqisi2
	bl	ftl_get_blk_list_in_sblk
	ldr	r3, .L3920+16
	uxtb	r0, r0
	lsls	r2, r6, #2
	strb	r5, [sp, #101]
	strb	r0, [sp, #105]
	mov	r1, r6
	ldrh	r3, [r3]
	strh	r5, [sp, #98]	@ movhi
	strh	r5, [sp, #106]	@ movhi
	smulbb	r3, r3, r0
	strh	r3, [sp, #102]	@ movhi
	ldr	r3, [r4]
	add	r3, r3, r2
	ldrb	r2, [r3, #2]	@ zero_extendqisi2
	mov	r3, fp
	str	r0, [sp]
	ldr	r0, .L3920+20
	lsrs	r2, r2, #5
	bl	printf
	movs	r0, #1
	bl	buf_alloc
	mov	r7, r0
	str	r5, [sp, #48]
	str	r5, [sp, #44]
.L3880:
	ldr	r3, .L3920+16
	ldrh	r2, [r3]
	uxth	r3, r5
	cmp	r2, r3
	bls	.L3897
	str	r3, [sp, #60]
	lsls	r3, r3, #1
	subs	r2, r3, #1
	str	r2, [sp, #80]
	ldr	r2, [sp, #60]
	add	r3, r3, r2
	subs	r3, r3, #1
	str	r3, [sp, #72]
	movs	r3, #0
	b	.L3919
.L3894:
	ldr	r3, [sp, #84]
	add	r2, sp, #128
	add	r3, r2, r3, lsl #1
	ldrh	r3, [r3, #-32]
	str	r3, [sp, #56]
	movw	r3, #65535
	ldr	r2, [sp, #56]
	cmp	r2, r3
	beq	.L3881
	ldr	r3, .L3920+24
	cmp	fp, #3
	ldrh	r4, [r3]
	mov	r3, r2
	mul	r3, r3, r4
	bne	.L3882
	ldr	r2, .L3920+28
	ldrb	r2, [r2]	@ zero_extendqisi2
	cbz	r2, .L3883
	ldr	r2, [sp, #72]
.L3916:
	adds	r4, r3, r2
	ldr	r2, .L3920+12
	add	r3, r4, r8
	ldrb	r4, [r2]	@ zero_extendqisi2
	orr	r4, r3, r4, lsl #24
	b	.L3884
.L3883:
	ldr	r2, .L3920+32
	lsl	r4, r8, #24
	ldrb	r2, [r2]	@ zero_extendqisi2
	cmp	r2, #0
	beq	.L3885
	ldr	r2, [sp, #72]
	add	r3, r3, r2
	add	r3, r3, r8
.L3917:
	orrs	r4, r4, r3
.L3884:
	movs	r1, #1
	str	r4, [r7, #24]
	mov	r0, r7
	bl	sblk_read_page
	ldr	r2, [r7, #12]
	ldr	r3, [r7, #36]
	ldr	r0, .L3920+36
	ldr	r1, [r2, #12]
	str	r3, [sp, #64]
	ldr	r3, [r7, #4]
	str	r1, [sp, #32]
	ldr	r1, [r2, #8]
	str	r1, [sp, #28]
	ldr	r1, [r2, #4]
	str	r1, [sp, #24]
	ldr	r2, [r2]
	ldr	r1, [sp, #56]
	str	r2, [sp, #20]
	ldr	r2, [r3, #12]
	str	r2, [sp, #16]
	ldr	r2, [r3, #8]
	str	r2, [sp, #12]
	ldr	r2, [r3, #4]
	str	r2, [sp, #8]
	ldr	r3, [r3]
	ldr	r2, [sp, #60]
	str	r3, [sp, #4]
	ldr	r3, [sp, #64]
	str	r3, [sp]
	mov	r3, r4
	bl	printf
	ldr	r3, [sp, #64]
	adds	r2, r3, #1
	beq	.L3902
	cmp	r3, #512
	ldr	r3, [sp, #44]
	it	eq
	moveq	r3, #1
.L3918:
	str	r3, [sp, #44]
	ldr	r3, .L3920
	ldr	r2, [sp, #76]
	ldr	r3, [r3]
	add	r3, r3, r2
	ldrb	r3, [r3, #2]	@ zero_extendqisi2
	and	r3, r3, #224
	cmp	r3, #224
	beq	.L3881
	cmp	r3, #32
	beq	.L3881
	ldr	r3, [r7, #12]
	ldr	r0, [r3, #4]
	bl	lpa_hash_get_ppa
	str	r0, [sp, #92]
	adds	r0, r0, #1
	bne	.L3888
	ldr	r3, [r7, #12]
	movs	r2, #0
	add	r1, sp, #92
	ldr	r0, [r3, #4]
	bl	pm_log2phys
.L3888:
	ldr	r3, [sp, #92]
	cmp	r4, r3
	bne	.L3889
	ldr	r3, [sp, #48]
	mov	r1, r4
	ldr	r2, [r7, #12]
	ldr	r0, .L3920+40
	adds	r3, r3, #1
	ldr	r2, [r2, #4]
	str	r3, [sp, #48]
	bl	printf
.L3889:
	ldr	r3, [sp, #68]
	cbz	r3, .L3891
	ldr	r2, [r3, r10, lsl #2]
	lsl	r4, r10, #2
	ldr	r3, [r7, #12]
	ldr	r3, [r3, #4]
	cmp	r3, r2
	beq	.L3892
	ldr	r3, .L3920+44
	ldr	r3, [r3]
	lsls	r3, r3, #19
	bpl	.L3892
	mov	r1, r10
	ldr	r0, .L3920+48
	bl	printf
.L3892:
	ldr	r3, [sp, #68]
	ldr	r2, [r7, #12]
	ldr	r3, [r3, r4]
	ldr	r2, [r2, #4]
	cmp	r2, r3
	beq	.L3891
	adds	r3, r3, #1
	beq	.L3891
	movw	r2, #1575
	ldr	r1, .L3920+52
	ldr	r0, .L3920+56
	bl	printf
.L3891:
	add	r10, r10, #1
.L3881:
	add	r8, r8, #1
	uxth	r8, r8
.L3896:
	cmp	fp, r8
	bcs	.L3894
	ldr	r3, [sp, #52]
	adds	r3, r3, #1
.L3919:
	str	r3, [sp, #52]
	ldrb	r2, [sp, #105]	@ zero_extendqisi2
	ldrh	r3, [sp, #52]
	cmp	r2, r3
	bls	.L3895
	adds	r3, r3, #8
	mov	r8, #1
	str	r3, [sp, #84]
	b	.L3896
.L3885:
	uxtah	r3, r3, r5
	b	.L3917
.L3882:
	cmp	fp, #2
	bne	.L3886
	ldr	r2, [sp, #80]
	b	.L3916
.L3886:
	uxtah	r4, r3, r5
	b	.L3884
.L3902:
	movs	r3, #1
	b	.L3918
.L3895:
	adds	r5, r5, #1
	b	.L3880
.L3897:
	mov	r0, r7
	bl	zbuf_free
	ldr	r3, .L3920+60
	mov	r1, r6
	ldr	r0, .L3920+64
	ldr	r2, [r3]
	ldr	r3, [sp, #48]
	ldrh	r2, [r2, r6, lsl #1]
	bl	printf
	ldr	r0, [sp, #44]
.L3877:
	add	sp, sp, #128
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r10, fp, pc}
.L3900:
	movs	r0, #0
	b	.L3877
.L3921:
	.align	2
.L3920:
	.word	.LANCHOR9
	.word	.LC223
	.word	.LANCHOR8
	.word	.LANCHOR78
	.word	.LANCHOR94
	.word	.LC224
	.word	.LANCHOR111
	.word	.LANCHOR35
	.word	.LANCHOR36
	.word	.LC160
	.word	.LC225
	.word	.LANCHOR19
	.word	.LC226
	.word	.LANCHOR229
	.word	.LC0
	.word	.LANCHOR11
	.word	.LC227
	.size	ftl_sblk_dump, .-ftl_sblk_dump
	.section	.text.zftl_read,"ax",%progbits
	.align	1
	.global	zftl_read
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	zftl_read, %function
zftl_read:
	@ args = 0, pretend = 0, frame = 48
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, r8, r10, fp, lr}
	mov	r6, r3
	ldr	r3, .L3974
	mov	r4, r0
	sub	sp, sp, #72
	mov	r5, r1
	str	r2, [sp, #24]
	ldr	r3, [r3]
	lsls	r0, r3, #19
	bpl	.L3923
	mov	r3, r2
	ldr	r0, .L3974+4
	mov	r2, r1
	mov	r1, r4
	bl	printf
.L3923:
	cmp	r4, #0
	bne	.L3924
	ldr	r3, .L3974+8
	mov	r4, #24576
	ldr	r3, [r3]
.L3925:
	cmp	r3, r5
	bls	.L3959
	ldr	r2, [sp, #24]
	cmp	r3, r2
	bcc	.L3959
	adds	r2, r5, r2
	cmp	r3, r2
	bcc	.L3959
	adds	r3, r4, r5
	ldr	r1, [sp, #24]
	str	r3, [sp, #28]
	ldr	r3, .L3974+12
	ldr	r0, [sp, #28]
	ldr	r2, [r3]
	ldr	r3, [r2, #24]
	add	r3, r3, r1
	str	r3, [r2, #24]
	ldr	r3, .L3974+16
	ldrb	r4, [r3]	@ zero_extendqisi2
	mov	r1, r4
	bl	__aeabi_uidiv
	ldr	r2, [sp, #28]
	mov	r1, r4
	ldr	r3, [sp, #24]
	str	r0, [sp, #36]
	ldr	r4, .L3974+20
	add	r3, r3, r2
	subs	r0, r3, #1
	str	r3, [sp, #44]
	bl	__aeabi_uidiv
	ldr	r3, [sp, #36]
	ldr	r5, [sp, #36]
	str	r0, [sp, #48]
	rsb	r3, r3, #1
	add	r3, r3, r0
	str	r3, [sp, #32]
	movs	r3, #0
	str	r3, [sp, #40]
.L3927:
	ldr	r3, [sp, #32]
	cbnz	r3, .L3955
	ldr	r0, [sp, #40]
.L3922:
	add	sp, sp, #72
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r10, fp, pc}
.L3924:
	cmp	r4, #3
	bhi	.L3959
	lsls	r4, r4, #13
	mov	r3, #8192
	b	.L3925
.L3955:
	ldr	r3, .L3974+16
	ldrb	r1, [r3]	@ zero_extendqisi2
	ldr	r3, [sp, #36]
	cmp	r5, r3
	uxth	r7, r1
	bne	.L3928
	ldr	r0, [sp, #28]
	bl	__aeabi_uidivmod
	uxth	r8, r1
	ldr	r3, [sp, #24]
	sub	r7, r7, r8
	uxth	r7, r7
	cmp	r3, r7
	bcs	.L3929
	ldrh	r7, [sp, #24]
.L3929:
	ldr	r2, .L3974+20
	movs	r3, #0
.L3932:
	ldr	r1, [r2, #20]
	cmp	r5, r1
	bne	.L3930
	ldrb	r1, [r2, #2]	@ zero_extendqisi2
	lsls	r1, r1, #28
	bpl	.L3930
	movs	r2, #48
	lsls	r7, r7, #9
	mov	r0, r6
	mla	r3, r2, r3, r4
	add	r6, r6, r7
	mov	r2, r7
	ldr	r1, [r3, #4]
	add	r1, r1, r8, lsl #9
	bl	ftl_memcpy
.L3931:
	ldr	r3, [sp, #32]
	adds	r5, r5, #1
	subs	r3, r3, #1
	str	r3, [sp, #32]
.L3938:
	ldr	r3, .L3974+24
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, #2
	bls	.L3939
	ldr	r3, [sp, #32]
	cmp	r3, #0
	bne	.L3927
.L3939:
	ldr	r3, .L3974+28
	ldrb	r1, [r3]	@ zero_extendqisi2
	cmp	r1, #0
	beq	.L3927
	ldr	r3, .L3974+32
	ldrb	r0, [r3]	@ zero_extendqisi2
	add	r0, r0, r0, lsl #1
	add	r0, r4, r0, lsl #4
	bl	sblk_read_page
.L3941:
	ldr	r3, .L3974+28
	ldr	r8, .L3974+32
	ldrb	r2, [r3]	@ zero_extendqisi2
	cmp	r2, #0
	bne	.L3954
	movs	r1, #255
	strb	r2, [r3]
	strb	r1, [r8]
	b	.L3927
.L3928:
	ldr	r3, [sp, #48]
	cmp	r5, r3
	bne	.L3960
	ldr	r3, [sp, #28]
	ldr	r2, [sp, #24]
	adds	r7, r3, r2
	mls	r1, r5, r1, r7
	uxtb	r7, r1
.L3960:
	mov	r8, #0
	b	.L3929
.L3930:
	adds	r3, r3, #1
	adds	r2, r2, #48
	cmp	r3, #32
	bne	.L3932
	mov	r0, r5
	bl	lpa_hash_get_ppa
	str	r0, [sp, #68]
	adds	r0, r0, #1
	bne	.L3933
	movs	r2, #0
	add	r1, sp, #68
	mov	r0, r5
	bl	pm_log2phys
.L3933:
	ldr	r3, [sp, #68]
	adds	r3, r3, #1
	bne	.L3934
	ldr	r8, .L3974+16
	movs	r7, #0
.L3935:
	ldrb	r3, [r8]	@ zero_extendqisi2
	cmp	r7, r3
	bcs	.L3931
	mla	r3, r3, r5, r7
	ldr	r2, [sp, #28]
	cmp	r2, r3
	bhi	.L3936
	ldr	r2, [sp, #44]
	cmp	r2, r3
	bls	.L3936
	mov	r0, r6
	add	r6, r6, #512
	mov	r2, #512
	movs	r1, #0
	bl	ftl_memset
.L3936:
	adds	r7, r7, #1
	b	.L3935
.L3934:
	movs	r0, #0
	bl	buf_alloc
	cmp	r0, #0
	beq	.L3938
	ldr	r2, .L3974+12
	ldr	r1, [r2]
	ldr	r2, [r1, #40]
	adds	r2, r2, #1
	str	r2, [r1, #40]
	ldr	r2, [sp, #68]
	str	r6, [r0, #8]
	add	r6, r6, r7, lsl #9
	str	r5, [r0, #20]
	str	r2, [r0, #24]
	str	r2, [r0, #28]
	strb	r7, [r0, #40]
	strb	r8, [r0, #41]
	bl	zftl_add_read_buf
	b	.L3931
.L3975:
	.align	2
.L3974:
	.word	.LANCHOR19
	.word	.LC228
	.word	.LANCHOR67
	.word	.LANCHOR110
	.word	.LANCHOR131
	.word	.LANCHOR55
	.word	.LANCHOR57
	.word	.LANCHOR134
	.word	.LANCHOR133
.L3954:
	ldrb	r3, [r8]	@ zero_extendqisi2
	cmp	r3, #255
	bne	.L3942
	movw	r2, #1281
	ldr	r1, .L3976
	ldr	r0, .L3976+4
	bl	printf
.L3942:
	ldrb	r7, [r8]	@ zero_extendqisi2
	add	r3, r7, r7, lsl #1
	add	r3, r4, r3, lsl #4
	str	r3, [sp, #52]
	movs	r3, #48
	muls	r3, r7, r3
	adds	r2, r4, r3
	ldrb	r3, [r4, r3]	@ zero_extendqisi2
	strb	r3, [r8]
	ldr	r8, [r2, #36]
	cmp	r8, #-1
	bne	.L3943
	ldr	r3, .L3976+8
	str	r8, [sp, #40]
	ldr	r2, [r3]
	ldr	r3, [r2, #552]
	adds	r3, r3, #1
	str	r3, [r2, #552]
.L3944:
	movs	r2, #48
	mla	r2, r2, r7, r4
	ldr	r3, [r2, #12]
	ldr	r2, [r2, #20]
	ldr	r1, [r3, #4]
	cmp	r1, r2
	bne	.L3945
	cmp	r8, #-1
	bne	.L3946
.L3945:
	ldr	r0, .L3976+12
	movs	r1, #48
	mla	r1, r1, r7, r4
	ldr	r2, .L3976+16
	ldrb	ip, [r0]	@ zero_extendqisi2
	mov	fp, #1
	ldrb	r2, [r2]	@ zero_extendqisi2
	ldr	r8, [r1, #8]
	ldr	lr, [r1, #4]
	rsb	r0, ip, #24
	ldrb	r10, [r1, #40]	@ zero_extendqisi2
	lsl	fp, fp, ip
	ldr	r1, [r1, #24]
	add	fp, fp, #-1
	str	r2, [sp]
	lsl	ip, fp, r0
	cmp	r10, r2
	ite	cs
	movcs	r2, r8
	movcc	r2, lr
	lsr	r0, r1, r0
	bic	r1, r1, ip
	and	r0, r0, fp
	uxtb	r0, r0
	bl	flash_read_page_en
	mov	r8, r0
.L3946:
	movs	r3, #48
	mla	r3, r3, r7, r4
	ldr	r2, [r3, #12]
	ldr	r3, [r3, #20]
	ldr	r1, [r2, #4]
	cmp	r1, r3
	bne	.L3948
	cmp	r8, #-1
	bne	.L3949
.L3948:
	ldr	r1, .L3976+8
	mov	r10, #48
	mla	r10, r10, r7, r4
	ldr	r0, [r1]
	ldr	r1, [r0, #552]
	adds	r1, r1, #1
	str	r1, [r0, #552]
	ldr	r0, [r2, #12]
	ldrb	r1, [r10, #1]	@ zero_extendqisi2
	str	r0, [sp, #16]
	ldr	r0, [r2, #8]
	str	r0, [sp, #12]
	ldr	r0, [r2, #4]
	str	r0, [sp, #8]
	ldr	r2, [r2]
	ldr	r0, .L3976+20
	str	r2, [sp, #4]
	ldr	r2, [r10, #24]
	str	r2, [sp]
	mov	r2, r8
	bl	printf
	ldr	r3, .L3976+24
	ldrh	r2, [r3]
	ldr	r3, .L3976+12
	ldrb	r3, [r3]	@ zero_extendqisi2
	rsb	r3, r3, #24
	subs	r0, r3, r2
	movs	r3, #1
	lsls	r3, r3, r0
	ldr	r0, [r10, #24]
	subs	r3, r3, #1
	lsrs	r0, r0, r2
	ldr	r2, .L3976+28
	ands	r0, r0, r3
	ldrb	r1, [r2]	@ zero_extendqisi2
	bl	__aeabi_uidiv
	movs	r1, #0
	uxth	r0, r0
	bl	ftl_sblk_dump
.L3949:
	movs	r3, #48
	mla	r3, r3, r7, r4
	ldr	r2, [r3, #12]
	ldr	r3, [r3, #20]
	ldr	r2, [r2, #4]
	cmp	r2, r3
	bne	.L3950
	cmp	r8, #-1
	bne	.L3951
.L3950:
	movw	r2, #1317
	ldr	r1, .L3976
	ldr	r0, .L3976+4
	bl	printf
.L3951:
	movs	r3, #48
	mla	r7, r3, r7, r4
	ldr	r3, .L3976+16
	ldrb	r3, [r3]	@ zero_extendqisi2
	ldrb	r2, [r7, #40]	@ zero_extendqisi2
	cmp	r3, r2
	bls	.L3952
	ldrb	r1, [r7, #41]	@ zero_extendqisi2
	lsls	r2, r2, #9
	ldr	r3, [r7, #4]
	ldr	r0, [r7, #8]
	add	r1, r3, r1, lsl #9
	bl	ftl_memcpy
.L3953:
	ldr	r1, [sp, #52]
	ldr	r0, .L3976+32
	bl	buf_remove_buf
	ldr	r0, [sp, #52]
	bl	zbuf_free
	ldr	r2, .L3976+36
	ldrb	r3, [r2]	@ zero_extendqisi2
	subs	r3, r3, #1
	strb	r3, [r2]
	b	.L3941
.L3943:
	cmp	r8, #256
	bne	.L3944
	ldr	r1, .L3976+24
	mov	fp, #1
	ldr	r3, [r2, #24]
	str	r2, [sp, #60]
	ldrh	r0, [r1]
	ldr	r1, .L3976+12
	str	r3, [sp, #56]
	ldrb	ip, [r1]	@ zero_extendqisi2
	ldr	r1, .L3976+28
	rsb	ip, ip, #24
	sub	ip, ip, r0
	lsr	r0, r3, r0
	lsl	ip, fp, ip
	ldrb	r1, [r1]	@ zero_extendqisi2
	add	ip, ip, #-1
	and	r0, ip, r0
	bl	__aeabi_uidiv
	ldr	r2, [sp, #60]
	mov	r10, r0
	uxth	r1, r0
	ldr	r3, [sp, #56]
	ldr	r0, .L3976+40
	ldr	r2, [r2, #20]
	bl	printf
	movs	r2, #0
	mov	r1, fp
	uxth	r0, r10
	bl	gc_add_sblk
	b	.L3944
.L3952:
	ldrb	r3, [r7, #2]	@ zero_extendqisi2
	bic	r3, r3, #8
	strb	r3, [r7, #2]
	b	.L3953
.L3959:
	mov	r0, #-1
	b	.L3922
.L3977:
	.align	2
.L3976:
	.word	.LANCHOR230
	.word	.LC0
	.word	.LANCHOR12
	.word	.LANCHOR31
	.word	.LANCHOR131
	.word	.LC230
	.word	.LANCHOR74
	.word	.LANCHOR75
	.word	.LANCHOR62
	.word	.LANCHOR134
	.word	.LC229
	.size	zftl_read, .-zftl_read
	.section	.text.zftl_sys_read,"ax",%progbits
	.align	1
	.global	zftl_sys_read
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	zftl_sys_read, %function
zftl_sys_read:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	mov	r3, r2
	mov	r2, r1
	mov	r1, r0
	movs	r0, #2
	b	zftl_read
	.size	zftl_sys_read, .-zftl_sys_read
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
	bl	ftl_memset
	mov	r3, r4
	mov	r1, r5
	movs	r2, #1
	movs	r0, #2
	pop	{r4, r5, r6, lr}
	b	zftl_read
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
	mov	r2, r1
	add	r1, r0, #512
	movs	r0, #2
	b	zftl_read
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
	b	zftl_read
	.size	ftl_read, .-ftl_read
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
	add	r1, r0, #512
	movs	r0, #2
	b	zftl_read
	.size	ftl_vendor_read, .-ftl_vendor_read
	.section	.text.zftl_vendor_read,"ax",%progbits
	.align	1
	.global	zftl_vendor_read
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	zftl_vendor_read, %function
zftl_vendor_read:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	b	ftl_vendor_read
	.size	zftl_vendor_read, .-zftl_vendor_read
	.global	__aeabi_idivmod
	.section	.text.ftl_update_l2p_map,"ax",%progbits
	.align	1
	.global	ftl_update_l2p_map
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	ftl_update_l2p_map, %function
ftl_update_l2p_map:
	@ args = 0, pretend = 0, frame = 24
	@ frame_needed = 0, uses_anonymous_args = 0
	ldr	r3, .L4013
	push	{r4, r5, r6, r7, r8, r10, fp, lr}
	sub	sp, sp, #24
	ldrb	r7, [r0, #9]	@ zero_extendqisi2
	mov	r6, r0
	ldrh	r3, [r3]
	ldr	r2, .L4013+4
	muls	r7, r3, r7
	ldr	r4, [r2]
	ldrh	r3, [r0, #12]
	str	r2, [sp, #4]
	add	r4, r4, r3, lsl #2
	add	r3, r7, #1073741824
	subs	r3, r3, #1
	ldr	r3, [r4, r3, lsl #2]
	adds	r3, r3, #1
	beq	.L3985
	movw	r2, #1998
	ldr	r1, .L4013+8
	ldr	r0, .L4013+12
	bl	printf
.L3985:
	movs	r5, #0
	subs	r4, r4, #4
	mov	r10, r5
.L3986:
	cmp	r10, r7
	bne	.L3992
	ldr	r3, .L4013+16
	ldr	r4, .L4013+20
	ldr	r3, [r3]
	tst	r3, #4096
	beq	.L3993
	ldrh	r1, [r6]
	mov	r2, r5
	ldr	r3, [r4]
	ldr	r0, .L4013+24
	ldrh	r3, [r3, r1, lsl #1]
	bl	printf
.L3993:
	ldrh	r2, [r6]
	ldr	r3, [r4]
	strh	r5, [r3, r2, lsl #1]	@ movhi
	add	sp, sp, #24
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r10, fp, pc}
.L3992:
	ldr	r8, [r4, #4]!
	cmp	r8, #-1
	beq	.L3987
	ldr	r3, .L4013+28
	mov	r0, r8
	ldrb	r1, [r3]	@ zero_extendqisi2
	lsls	r1, r1, #7
	bl	__aeabi_uidiv
	uxth	r3, r0
	str	r3, [sp]
	ldr	r3, .L4013+16
	ldr	r3, [r3]
	lsls	r2, r3, #19
	bpl	.L3988
	mov	r3, r10
	mov	r2, r8
	ldr	r1, [sp]
	ldr	r0, .L4013+32
	bl	printf
.L3988:
	mov	r8, r4
	mov	fp, r10
.L3991:
	ldr	r0, [r8]
	adds	r3, r0, #1
	beq	.L3989
	ldr	r3, .L4013+28
	ldrb	r1, [r3]	@ zero_extendqisi2
	lsls	r1, r1, #7
	bl	__aeabi_uidiv
	ldr	r3, [sp]
	uxth	r0, r0
	cmp	r3, r0
	bne	.L3989
	ldrb	r3, [r6, #9]	@ zero_extendqisi2
	mov	r0, fp
	mov	r1, r3
	str	r3, [sp, #12]
	bl	__aeabi_idivmod
	ldr	r3, .L4013+36
	adds	r1, r1, #8
	ldrh	r0, [r6, r1, lsl #1]
	ldrh	r2, [r3]
	ldr	r3, [sp, #12]
	muls	r2, r0, r2
	mov	r1, r3
	mov	r0, fp
	str	r2, [sp, #8]
	bl	__aeabi_idiv
	ldr	r2, [sp, #8]
	add	r2, r2, r0
	ldr	r0, .L4013+40
	str	r2, [sp, #20]
	ldr	r1, [r8]
	bl	pm_ppa_update_check
	cbz	r0, .L3990
	ldr	r1, [sp, #4]
	mov	r3, r7
	movs	r2, #4
	ldr	r0, .L4013+44
	ldr	r1, [r1]
	bl	rknand_print_hex
.L3990:
	adds	r5, r5, #1
	movs	r2, #1
	uxth	r5, r5
	add	r1, sp, #20
	ldr	r0, [r8]
	bl	pm_log2phys
	mov	r3, #-1
	str	r3, [r8]
.L3989:
	add	fp, fp, #1
	add	r8, r8, #4
	cmp	r7, fp
	bne	.L3991
.L3987:
	add	r10, r10, #1
	b	.L3986
.L4014:
	.align	2
.L4013:
	.word	.LANCHOR94
	.word	.LANCHOR117
	.word	.LANCHOR231
	.word	.LC0
	.word	.LANCHOR19
	.word	.LANCHOR11
	.word	.LC234
	.word	.LANCHOR131
	.word	.LC231
	.word	.LANCHOR111
	.word	.LC232
	.word	.LC233
	.size	ftl_update_l2p_map, .-ftl_update_l2p_map
	.section	.text.ftl_alloc_new_data_sblk,"ax",%progbits
	.align	1
	.global	ftl_alloc_new_data_sblk
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	ftl_alloc_new_data_sblk, %function
ftl_alloc_new_data_sblk:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, lr}
	mov	r5, r0
	ldrh	r6, [r0]
	bl	ftl_update_l2p_map
	bl	pm_flush
	ldrh	r0, [r5]
	movw	r3, #65535
	cmp	r0, r3
	beq	.L4016
	bl	zftl_insert_data_list
.L4016:
	ldr	r4, .L4020
	mov	r0, r5
	ldr	r1, [r4]
	adds	r1, r1, #16
	cmp	r5, r1
	ite	eq
	moveq	r1, #2
	movne	r1, #3
	bl	ftl_open_sblk_init
	ldr	r3, [r4]
	ldr	r3, [r3, #560]
	cmp	r3, r6
	bne	.L4018
	movw	r5, #65535
	cmp	r6, r5
	beq	.L4018
	mov	r1, r6
	ldr	r0, .L4020+4
	bl	printf
	ldr	r3, [r4]
	ldr	r0, [r3, #564]
	bl	gc_mark_bad_ppa
	ldr	r3, [r4]
	mov	r2, #-1
	str	r5, [r3, #560]
	str	r2, [r3, #564]
.L4018:
	bl	ftl_ext_info_flush
	movs	r0, #0
	bl	ftl_info_flush
	bl	lpa_rebuild_hash
	movs	r0, #0
	pop	{r4, r5, r6, pc}
.L4021:
	.align	2
.L4020:
	.word	.LANCHOR12
	.word	.LC235
	.size	ftl_alloc_new_data_sblk, .-ftl_alloc_new_data_sblk
	.section	.text.ftl_write_commit,"ax",%progbits
	.align	1
	.global	ftl_write_commit
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	ftl_write_commit, %function
ftl_write_commit:
	@ args = 0, pretend = 0, frame = 24
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, r8, r10, fp, lr}
	sub	sp, sp, #32
	ldr	r8, .L4087+32
.L4023:
	ldr	r1, .L4087
	ldrb	r3, [r1]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L4025
	ldr	r0, .L4087+4
	subs	r3, r3, #1
	strb	r3, [r1]
	ldrb	r2, [r0]	@ zero_extendqisi2
	str	r2, [sp, #12]
	add	r2, r2, r2, lsl #1
	ldr	r4, [sp, #12]
	add	r2, r8, r2, lsl #4
	str	r2, [sp, #20]
	movs	r2, #48
	muls	r2, r4, r2
	ldr	r4, .L4087+8
	ldr	r3, [r4]
	add	r5, r8, r2
	ldrb	r2, [r8, r2]	@ zero_extendqisi2
	strb	r2, [r0]
	ldr	r2, [r5, #20]
	cmp	r2, r3
	bcc	.L4027
	mov	r2, #604
	ldr	r1, .L4087+12
	ldr	r0, .L4087+16
	bl	printf
.L4027:
	ldr	r2, [sp, #12]
	movs	r3, #48
	mla	r3, r3, r2, r8
	ldr	r2, [r4]
	ldr	r7, [r3, #20]
	cmp	r7, r2
	bcc	.L4028
	ldr	r0, [sp, #20]
	bl	zbuf_free
	mov	r0, #-1
.L4022:
	add	sp, sp, #32
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r10, fp, pc}
.L4028:
	ldr	r2, [r3, #12]
	ldr	fp, [r3, #4]
	ldrb	r5, [r3, #41]	@ zero_extendqisi2
	ldrb	r3, [r3, #40]	@ zero_extendqisi2
	str	r2, [sp, #8]
	str	r3, [sp, #16]
	ldr	r3, .L4087+20
	ldrb	r3, [r3]	@ zero_extendqisi2
	cbz	r3, .L4030
	ldr	r3, .L4087+24
	ldrb	r4, [r3]	@ zero_extendqisi2
	add	r4, r4, r4, lsl #1
	add	r4, r8, r4, lsl #4
.L4031:
	ldrb	r3, [r4]	@ zero_extendqisi2
	cmp	r3, #255
	bne	.L4032
	ldr	r3, [r4, #20]
	cmp	r7, r3
	bne	.L4030
	ldr	r2, [sp, #16]
	lsls	r0, r5, #9
	ldr	r3, [r4, #4]
	add	r1, fp, r0
	lsls	r2, r2, #9
	add	r0, r0, r3
	bl	ftl_memcpy
	ldr	r3, .L4087+28
	movs	r0, #2
	ldr	r2, [r4, #4]
	ldr	r1, [r4, #12]
	ldrb	r3, [r3]	@ zero_extendqisi2
	adds	r1, r1, #16
	subs	r3, r3, #2
	add	r2, r2, r3, lsl #9
	bl	ftl_debug_info_fill
	ldr	r0, [sp, #20]
	bl	zbuf_free
	b	.L4023
.L4032:
	add	r3, r3, r3, lsl #1
	add	r4, r8, r3, lsl #4
	b	.L4031
.L4030:
	mov	r0, r7
	bl	lpa_hash_get_ppa
	str	r0, [sp, #28]
	adds	r0, r0, #1
	bne	.L4034
	movs	r2, #0
	add	r1, sp, #28
	mov	r0, r7
	bl	pm_log2phys
.L4034:
	ldr	r10, .L4087+36
	movs	r2, #0
	ldr	r3, .L4087+32
	mov	r4, r2
	ldr	r0, [sp, #28]
	ldr	r6, [r10]
	add	ip, r3, #1536
	adds	r6, r6, #16
.L4036:
	ldr	r1, [r3, #20]
	cmp	r7, r1
	bne	.L4035
	ldrb	r1, [r3, #2]	@ zero_extendqisi2
	tst	r1, #8
	beq	.L4035
	ldr	r4, [r3, #4]
	movs	r2, #1
	ldr	r0, [r3, #24]
	bic	r1, r1, #8
	strb	r1, [r3, #2]
.L4035:
	adds	r3, r3, #48
	cmp	r3, ip
	bne	.L4036
	cbz	r2, .L4037
	str	r0, [sp, #28]
.L4037:
	ldr	r3, .L4087+28
	ldr	r2, [sp, #16]
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r2, r3
	bcs	.L4063
	cbz	r4, .L4039
	cbz	r5, .L4040
	lsls	r2, r5, #9
	mov	r1, r4
	mov	r0, fp
	bl	ftl_memcpy
	ldr	r6, [r10]
	adds	r6, r6, #48
.L4040:
	ldr	r3, [sp, #16]
	add	r5, r5, r3
	ldr	r3, .L4087+28
	ldrb	r2, [r3]	@ zero_extendqisi2
	cmp	r5, r2
	bcc	.L4041
	ldr	r6, [r10]
	adds	r6, r6, #16
.L4063:
	mov	r10, #0
	b	.L4038
.L4041:
	lsls	r0, r5, #9
	subs	r2, r2, r5
	lsls	r2, r2, #9
	adds	r1, r4, r0
	add	r0, r0, fp
	bl	ftl_memcpy
	b	.L4063
.L4088:
	.align	2
.L4087:
	.word	.LANCHOR66
	.word	.LANCHOR65
	.word	.LANCHOR128
	.word	.LANCHOR232
	.word	.LC0
	.word	.LANCHOR129
	.word	.LANCHOR182
	.word	.LANCHOR131
	.word	.LANCHOR55
	.word	.LANCHOR12
.L4039:
	ldr	r3, [sp, #28]
	adds	r3, r3, #1
	beq	.L4042
	movs	r0, #1
	bl	buf_alloc
	ldr	r3, [sp, #28]
	mov	r4, r0
	str	r7, [r0, #20]
	movs	r1, #1
	str	r3, [r0, #24]
	bl	sblk_read_page
	ldr	r3, [r4, #12]
	ldr	r2, [r3, #12]
	add	r10, r2, #1
	ldr	r2, [r3, #4]
	cmp	r7, r2
	bne	.L4043
	ldr	r2, [r4, #36]
	adds	r2, r2, #1
	bne	.L4044
.L4043:
	ldr	r2, .L4089
	movs	r0, #1
	ldr	r1, [r4, #24]
	ldrb	r2, [r2]	@ zero_extendqisi2
	rsb	lr, r2, #24
	lsls	r0, r0, r2
	subs	r2, r0, #1
	lsr	r0, r1, lr
	lsl	ip, r2, lr
	ands	r0, r0, r2
	ldr	r2, .L4089+4
	bic	r1, r1, ip
	uxtb	r0, r0
	ldrb	r2, [r2]	@ zero_extendqisi2
	str	r2, [sp]
	ldr	r2, [r4, #4]
	bl	flash_read_page_en
	str	r0, [r4, #36]
.L4044:
	ldr	r3, [r4, #12]
	ldr	r3, [r3, #4]
	cmp	r7, r3
	bne	.L4045
	ldr	r3, [r4, #36]
	adds	r3, r3, #1
	bne	.L4046
.L4045:
	ldr	r3, .L4089+8
	ldr	r0, .L4089+12
	ldr	r2, [r3]
	ldr	r3, [r2, #552]
	adds	r3, r3, #1
	str	r3, [r2, #552]
	ldr	r3, [r4, #36]
	ldrb	r1, [r4, #1]	@ zero_extendqisi2
	ldr	r2, [sp, #28]
	str	r3, [sp]
	mov	r3, r7
	bl	printf
	movs	r3, #4
	ldr	r1, [r4, #12]
	mov	r2, r3
	ldr	r0, .L4089+16
	bl	rknand_print_hex
.L4046:
	ldr	r3, [r4, #12]
	ldr	r3, [r3, #4]
	cmp	r7, r3
	bne	.L4047
	ldr	r3, [r4, #36]
	adds	r3, r3, #1
	bne	.L4048
.L4047:
	mov	r2, #696
	ldr	r1, .L4089+20
	ldr	r0, .L4089+24
	bl	printf
.L4048:
	cbz	r5, .L4049
	ldr	r3, [sp, #28]
	lsls	r2, r5, #9
	adds	r3, r3, #1
	beq	.L4050
	ldr	r1, [r4, #4]
	mov	r0, fp
	bl	ftl_memcpy
.L4051:
	ldr	r3, .L4089+8
	ldr	r6, [r3]
	adds	r6, r6, #48
.L4049:
	ldr	r3, [sp, #16]
	add	r5, r5, r3
	ldr	r3, .L4089+4
	ldrb	r2, [r3]	@ zero_extendqisi2
	cmp	r5, r2
	bcc	.L4052
	bls	.L4053
	ldr	r3, .L4089+8
	ldr	r6, [r3]
	adds	r6, r6, #16
.L4053:
	cbz	r4, .L4038
	ldrb	r3, [r4, #2]	@ zero_extendqisi2
	mov	r1, r4
	ldr	r0, .L4089+28
	bic	r3, r3, #8
	strb	r3, [r4, #2]
	bl	buf_remove_buf
	mov	r0, r4
	bl	zbuf_free
.L4038:
	ldrh	r3, [r6, #6]
	cbnz	r3, .L4055
	bl	ftl_flush
	mov	r0, r6
	bl	ftl_alloc_new_data_sblk
.L4055:
	mov	r0, r6
	movs	r5, #48
	bl	ftl_get_new_free_page
	ldr	r3, [sp, #12]
	str	r0, [sp, #16]
	movs	r0, #2
	muls	r5, r3, r5
	ldr	r3, [sp, #8]
	mov	r1, r3
	add	r4, r8, r5
	ldr	r2, [r4, #16]
	str	r10, [r3, #12]
	stm	r3, {r2, r7}
	movs	r7, #0
	ldr	r2, [sp, #28]
	str	r2, [r3, #8]
	ldr	r3, .L4089+4
	str	r7, [r1, #16]!
	ldrb	r2, [r3]	@ zero_extendqisi2
	subs	r2, r2, #2
	add	r2, fp, r2, lsl #9
	bl	ftl_debug_info_fill
	ldr	r3, [sp, #16]
	ldrh	r2, [r6, #12]
	ldr	r1, [sp, #20]
	str	r3, [r4, #24]
	ldr	r3, [sp, #28]
	ldr	r0, .L4089+32
	str	r3, [r4, #28]
	movs	r3, #255
	strb	r3, [r8, r5]
	ldrb	r3, [r4, #2]	@ zero_extendqisi2
	ldr	r5, .L4089+36
	orr	r3, r3, #10
	strb	r3, [r4, #2]
	ldrh	r3, [r6, #10]
	add	r3, r3, r2
	subs	r3, r3, #1
	strh	r3, [r4, #32]	@ movhi
	bl	buf_add_tail
	ldrb	r3, [r5]	@ zero_extendqisi2
	ldr	r2, .L4089+40
	adds	r3, r3, #1
	uxtb	r3, r3
	str	r7, [r2]
	ldrh	r2, [r6, #6]
	cmp	r3, #2
	strb	r3, [r5]
	bhi	.L4056
	cmp	r2, #1
	bne	.L4026
.L4056:
	ldr	r7, .L4089+32
	mov	ip, #48
	ldrb	r1, [r6, #5]	@ zero_extendqisi2
	ldrb	r0, [r7]	@ zero_extendqisi2
	cmp	r1, #0
	mov	r1, #0
	ite	ne
	movne	r4, #2
	moveq	r4, #1
	cmp	r2, #1
	it	eq
	moveq	r4, r3
	mov	r2, r0
.L4060:
	cmp	r1, r4
	bne	.L4061
	uxtb	r1, r1
	add	r0, r0, r0, lsl #1
	strb	r2, [r7]
	subs	r3, r3, r1
	add	r0, r8, r0, lsl #4
	strb	r3, [r5]
	bl	sblk_prog_page
	ldrh	r3, [r6, #6]
	cmp	r3, #1
	bne	.L4026
	bl	sblk_wait_write_queue_completed
	bl	ftl_write_completed
	mov	r0, r6
	bl	ftl_write_last_log_page
	mov	r0, r6
	bl	ftl_alloc_new_data_sblk
.L4026:
	ldr	r3, .L4089+44
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L4023
.L4025:
	bl	ftl_write_completed
	movs	r0, #0
	b	.L4022
.L4052:
	ldr	r3, [sp, #28]
	subs	r2, r2, r5
	lsls	r2, r2, #9
	lsls	r0, r5, #9
	adds	r3, r3, #1
	beq	.L4054
	ldr	r1, [r4, #4]
	add	r1, r1, r0
	add	r0, r0, fp
	bl	ftl_memcpy
	b	.L4053
.L4054:
	movs	r1, #0
	add	r0, r0, fp
	bl	ftl_memset
	b	.L4053
.L4061:
	mul	r2, ip, r2
	adds	r1, r1, #1
	ldrb	r2, [r8, r2]	@ zero_extendqisi2
	b	.L4060
.L4062:
	lsls	r2, r5, #9
	mov	r10, r4
.L4050:
	movs	r1, #0
	mov	r0, fp
	bl	ftl_memset
	b	.L4051
.L4042:
	cmp	r5, #0
	bne	.L4062
	mov	r10, r5
	mov	r4, r5
	b	.L4049
.L4090:
	.align	2
.L4089:
	.word	.LANCHOR31
	.word	.LANCHOR131
	.word	.LANCHOR12
	.word	.LC236
	.word	.LC208
	.word	.LANCHOR232
	.word	.LC0
	.word	.LANCHOR62
	.word	.LANCHOR182
	.word	.LANCHOR129
	.word	.LANCHOR233
	.word	.LANCHOR66
	.size	ftl_write_commit, .-ftl_write_commit
	.section	.text.gc_do_copy_back,"ax",%progbits
	.align	1
	.global	gc_do_copy_back
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	gc_do_copy_back, %function
gc_do_copy_back:
	@ args = 0, pretend = 0, frame = 72
	@ frame_needed = 0, uses_anonymous_args = 0
	ldr	r3, .L4234
	push	{r4, r5, r6, r7, r8, r10, fp, lr}
	sub	sp, sp, #80
	ldrb	r0, [r3]	@ zero_extendqisi2
	cmp	r0, #0
	bne	.L4092
	bl	buf_alloc
	mov	r4, r0
	cmp	r0, #0
	beq	.L4091
	ldr	r5, .L4234+4
	ldrh	r2, [r5, #22]
	mov	r0, r2
	bl	gc_get_src_ppa_from_index
	movs	r1, #1
	adds	r2, r2, #1
	str	r0, [r4, #24]
	mov	r6, r0
	mov	r0, r4
	strh	r2, [r5, #22]	@ movhi
	bl	sblk_read_page
	ldr	r3, [r4, #36]
	adds	r0, r3, #1
	beq	.L4094
	cmp	r3, #512
	bne	.L4095
.L4094:
	mov	r2, #1032
	ldr	r1, .L4234+8
	ldr	r0, .L4234+12
	bl	printf
.L4095:
	ldr	r3, [r4, #12]
	ldr	r8, [r3, #4]
	mov	r0, r8
	bl	lpa_hash_get_ppa
	str	r0, [sp, #56]
	adds	r0, r0, #1
	bne	.L4096
	movs	r2, #0
	add	r1, sp, #56
	mov	r0, r8
	bl	pm_log2phys
.L4096:
	ldr	r7, [sp, #56]
	cmp	r6, r7
	bne	.L4097
	ldr	r0, .L4234+16
	movs	r3, #0
.L4100:
	adds	r2, r0, r3
	ldr	r1, [r2, #20]
	cmp	r8, r1
	bne	.L4098
	ldrb	r2, [r2, #2]	@ zero_extendqisi2
	lsls	r1, r2, #30
	bpl	.L4098
	mov	r0, r4
	bl	zbuf_free
	ldr	r3, .L4234+20
	ldr	r3, [r3]
	lsls	r2, r3, #23
	bpl	.L4091
	ldrh	r3, [r5, #22]
	mov	r2, r6
	mov	r1, r8
	ldr	r0, .L4234+24
	bl	printf
.L4091:
	add	sp, sp, #80
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r10, fp, pc}
.L4098:
	adds	r3, r3, #48
	cmp	r3, #1536
	bne	.L4100
	ldr	r3, .L4234+28
	movs	r2, #0
	str	r8, [r4, #20]
	strb	r2, [r4, #41]
	ldrb	r3, [r3]	@ zero_extendqisi2
	strb	r3, [r4, #40]
	ldr	r3, [r4, #12]
	ldr	r1, [r3]
	str	r1, [r4, #16]
	str	r2, [r3, #16]
	ldr	r3, .L4234+20
	ldr	r3, [r3]
	lsls	r3, r3, #23
	bpl	.L4101
	mov	r0, r8
	bl	lpa_hash_get_ppa
	ldrh	r3, [r5, #22]
	mov	r2, r7
	str	r6, [sp]
	mov	r1, r8
	str	r3, [sp, #4]
	mov	r3, r0
	ldr	r0, .L4234+32
	bl	printf
.L4101:
	mov	r0, r4
	bl	ftl_gc_write_buf
	bl	ftl_write_commit
	ldr	r3, .L4234+36
	ldr	r2, [r3]
	ldr	r3, [r2, #60]
	adds	r3, r3, #1
	str	r3, [r2, #60]
	ldrh	r3, [r5, #24]
	adds	r3, r3, #1
	strh	r3, [r5, #24]	@ movhi
	b	.L4091
.L4097:
	ldr	r3, .L4234+20
	ldr	r3, [r3]
	lsls	r0, r3, #23
	bpl	.L4102
	mov	r0, r8
	bl	lpa_hash_get_ppa
	ldrh	r3, [r5, #22]
	mov	r2, r7
	str	r6, [sp]
	mov	r1, r8
	str	r3, [sp, #4]
	mov	r3, r0
	ldr	r0, .L4234+32
	bl	printf
.L4102:
	mov	r0, r4
	bl	zbuf_free
	b	.L4091
.L4092:
	ldr	r3, .L4234+40
	ldr	r3, [r3]
	ldrb	r6, [r3, #89]	@ zero_extendqisi2
	str	r3, [sp, #28]
	ldr	r3, .L4234+44
	uxth	r7, r6
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, r7
	bhi	.L4160
	cmp	r7, #2
	mov	fp, r7
	it	cs
	movcs	fp, #2
.L4103:
	ldr	r3, .L4234+48
	ldr	r5, .L4234+4
	ldrb	r8, [r3]	@ zero_extendqisi2
	cmp	r8, #3
	bne	.L4104
	ldr	r3, .L4234+52
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L4105
	ldrh	r3, [r5, #2102]
	mov	r1, r6
	mov	r0, r3
	str	r3, [sp, #12]
	bl	__aeabi_idiv
	ldr	r3, .L4234+56
	uxth	r4, r0
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L4106
	ldr	r3, .L4234+60
	ldrh	r3, [r3, r0, lsl #1]
	cmp	r3, #0
	ite	eq
	moveq	r3, #1
	movne	r3, #2
.L4226:
	str	r3, [sp, #16]
	smulbb	r7, r7, r4
	ldr	r3, [sp, #12]
	subs	r7, r3, r7
	uxth	r3, r7
	str	r3, [sp, #20]
.L4108:
	ldr	r3, [sp, #16]
	ldr	r10, .L4234+60
	mul	r3, fp, r3
	str	r3, [sp, #24]
	ldr	r3, .L4234+64
	ldrh	r1, [r3]
	ldr	r3, .L4234+68
	muls	r1, r6, r1
	ldrb	r3, [r3]	@ zero_extendqisi2
	movs	r6, #0
	subs	r1, r1, r3
	ldr	r3, .L4234+56
	ldrb	r8, [r3]	@ zero_extendqisi2
	ldr	r3, .L4234+72
	ldr	r7, [r3]
	ldrh	r3, [r5, #20]
	str	r3, [sp, #32]
	ldr	r3, .L4234+4
.L4112:
	ldr	r0, [sp, #24]
	uxth	ip, r6
	mov	r2, ip
	cmp	ip, r0
	bge	.L4168
	ldr	r0, [sp, #12]
	add	r2, r2, r0
	cmp	r2, r1
	blt	.L4113
	cmp	r8, #0
	beq	.L4168
	ldrh	r0, [r10, r4, lsl #1]
	cmp	r0, r4
	bcc	.L4114
.L4168:
	movs	r3, #1
	str	r3, [sp, #24]
	b	.L4110
.L4160:
	mov	fp, #1
	b	.L4103
.L4106:
	ldr	r3, .L4234+76
	ldrb	r3, [r3]	@ zero_extendqisi2
	cbz	r3, .L4162
	sub	r3, r4, #62
	cmp	r3, #2160
	bcs	.L4163
	mov	r1, r8
	mov	r0, r4
	bl	__aeabi_uidivmod
	uxth	r1, r1
	cmp	r1, #0
	ite	ne
	movne	r3, #1
	moveq	r3, #2
	b	.L4226
.L4162:
	movs	r3, #1
	b	.L4226
.L4163:
	movs	r3, #2
	b	.L4226
.L4105:
	ldr	r3, .L4234+80
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L4109
	ldrh	r3, [r5, #2102]
	add	r1, r6, r6, lsl #1
	mov	r0, r3
	str	r3, [sp, #12]
	bl	__aeabi_idiv
	uxth	r4, r0
	muls	r0, r6, r0
	ldr	r3, [sp, #12]
	ldr	r2, .L4234+84
	sub	r0, r0, r0, lsl #2
	add	r0, r0, r3
	smull	r2, r3, r0, r2
	sub	r0, r3, r0, asr #31
	uxth	r3, r0
	str	r3, [sp, #20]
	ldr	r3, .L4234+88
	ldrb	r3, [r3]	@ zero_extendqisi2
	cbz	r3, .L4165
	add	r4, r4, r4, lsl #1
	uxth	r4, r4
.L4165:
	str	r8, [sp, #16]
	b	.L4108
.L4235:
	.align	2
.L4234:
	.word	.LANCHOR84
	.word	.LANCHOR70
	.word	.LANCHOR234
	.word	.LC0
	.word	.LANCHOR55
	.word	.LANCHOR19
	.word	.LC237
	.word	.LANCHOR131
	.word	.LC238
	.word	.LANCHOR110
	.word	.LANCHOR12
	.word	.LANCHOR79
	.word	.LANCHOR78
	.word	.LANCHOR35
	.word	.LANCHOR124
	.word	.LANCHOR235
	.word	.LANCHOR85
	.word	.LANCHOR224
	.word	.LANCHOR160
	.word	.LANCHOR217
	.word	.LANCHOR83
	.word	1431655766
	.word	.LANCHOR36
.L4109:
	ldrh	r10, [r5, #2102]
	mov	r1, r6
	mov	r0, r10
	bl	__aeabi_idiv
	ldr	r3, .L4236
	smulbb	r7, r0, r7
	str	r8, [sp, #16]
	ldrh	r3, [r3, r0, lsl #1]
	sub	r10, r10, r7
	lsrs	r4, r3, #3
	and	r3, r3, #7
	str	r3, [sp, #24]
	uxth	r3, r10
	str	r3, [sp, #20]
	mla	r3, r6, r4, r3
	add	r3, r3, r3, lsl #1
	uxth	r3, r3
	str	r3, [sp, #12]
	ldr	r3, [sp, #24]
	cmp	r3, #1
	beq	.L4108
.L4110:
	ldr	r3, [sp, #16]
	ldrh	r2, [sp, #16]
	mul	r3, fp, r3
	str	r3, [sp, #40]
	lsl	r3, fp, #1
	uxth	r3, r3
	str	r3, [sp, #44]
	ldrh	r3, [sp, #44]
	smulbb	r3, r3, r2
	ldr	r2, [sp, #12]
	subs	r3, r2, r3
	uxth	r3, r3
	str	r3, [sp, #48]
	movs	r3, #0
.L4230:
	str	r3, [sp, #36]
	ldr	r2, [sp, #40]
	ldrh	r6, [sp, #36]
	cmp	r6, r2
	str	r6, [sp, #32]
	blt	.L4142
	ldr	r3, .L4236+4
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, #3
	bne	.L4143
	ldr	r3, .L4236+8
	ldrb	r1, [r3]	@ zero_extendqisi2
	cmp	r1, #0
	beq	.L4144
	movs	r1, #0
	subs	r2, r2, #1
.L4145:
	uxth	r3, r1
	adds	r1, r1, #1
	cmp	r3, r2
	blt	.L4146
	add	r3, sp, #80
	add	r2, r3, r2, lsl #2
	ldr	r3, [r2, #-24]
.L4231:
	movs	r2, #255
	strb	r2, [r3]
	ldrh	r3, [sp, #16]
	ldr	r0, [sp, #56]
	smulbb	r1, fp, r3
	uxtb	r1, r1
	bl	sblk_prog_page
	b	.L4147
.L4104:
	ldr	r3, .L4236+12
	ldrb	r3, [r3]	@ zero_extendqisi2
	cbnz	r3, .L4111
	ldrh	r3, [r5, #2102]
	mov	r1, r6
	mov	r0, r3
	str	r3, [sp, #12]
	bl	__aeabi_idiv
	uxth	r4, r0
	ldr	r3, [sp, #12]
	smulbb	r7, r7, r4
	subs	r7, r3, r7
	uxth	r3, r7
	str	r3, [sp, #20]
	movs	r3, #1
.L4227:
	str	r3, [sp, #16]
	b	.L4108
.L4111:
	ldrh	r3, [r5, #2102]
	mov	r1, r6
	mov	r0, r3
	str	r3, [sp, #12]
	bl	__aeabi_idiv
	uxth	r4, r0
	ldr	r3, [sp, #12]
	smulbb	r7, r7, r4
	subs	r7, r3, r7
	uxth	r3, r7
	str	r3, [sp, #20]
	movs	r3, #2
	b	.L4227
.L4114:
	tst	ip, #1
	beq	.L4168
.L4113:
	ldr	r0, [r7, r2, lsl #2]
	adds	r0, r0, #1
	bne	.L4116
	ldrh	r5, [r3, #22]
	ldr	r0, [sp, #32]
	cmp	r5, r0
	bcs	.L4091
	cmp	r8, #0
	beq	.L4117
	ldrh	r0, [r10, r4, lsl #1]
	cmp	r0, r4
	bcs	.L4117
	tst	ip, #1
	beq	.L4117
	ldr	r0, [r7, r0, lsl #2]
.L4228:
	str	r0, [r7, r2, lsl #2]
.L4116:
	adds	r6, r6, #1
	b	.L4112
.L4117:
	mov	r0, r5
	str	r3, [sp, #36]
	bl	gc_get_src_ppa_from_index
	ldr	r3, [sp, #36]
	adds	r5, r5, #1
	strh	r5, [r3, #22]	@ movhi
	b	.L4228
.L4142:
	ldr	r3, [sp, #12]
	ldr	r2, [sp, #32]
	adds	r7, r3, r2
	ldr	r3, .L4236+16
	ldr	r3, [r3]
	ldrb	r3, [r3, r7]	@ zero_extendqisi2
	cmp	r3, #255
	bne	.L4119
	movs	r0, #0
	bl	buf_alloc
	mov	r5, r0
	cbnz	r0, .L4120
	bl	sblk_wait_write_queue_completed
	bl	ftl_write_completed
	bl	gc_write_completed
	bl	gc_free_temp_buf
	mov	r0, r5
	bl	buf_alloc
	mov	r5, r0
	cmp	r0, #0
	beq	.L4091
.L4120:
	ldr	r3, .L4236+16
	ldrb	r2, [r5, #1]	@ zero_extendqisi2
	ldr	r3, [r3]
	strb	r2, [r3, r7]
	ldr	r2, .L4236+20
	ldrb	r3, [r2, #7]	@ zero_extendqisi2
	adds	r3, r3, #1
	strb	r3, [r2, #7]
	ldr	r3, [sp, #12]
	adds	r3, r6, r3
	strh	r3, [r5, #32]	@ movhi
	ldrb	r3, [sp, #24]	@ zero_extendqisi2
	strb	r3, [r5, #45]
	ldr	r3, .L4236+24
	ldrh	r2, [r3]
	ldr	r3, .L4236+28
	ldrb	r0, [r3]	@ zero_extendqisi2
	ldr	r3, [sp, #28]
	ldrb	r3, [r3, #89]	@ zero_extendqisi2
	muls	r3, r2, r3
	subs	r3, r3, r0
	cmp	r7, r3
	blt	.L4121
	ldr	r1, .L4236+32
	ldrb	r1, [r1]	@ zero_extendqisi2
	cbz	r1, .L4122
	ldr	r1, .L4236+36
	ldrh	r1, [r1, r4, lsl #1]
	cmp	r1, r4
	bcs	.L4122
	lsls	r1, r6, #31
	bmi	.L4121
.L4122:
	ldr	r1, .L4236+40
	cmp	r0, #2
	mov	ip, #-1
	ldr	r1, [r1]
	str	ip, [r1, r7, lsl #2]
	bne	.L4123
	cmp	r7, r3
	ldr	r10, .L4236+68
	bne	.L4124
	ldrh	r2, [r10]
	ldr	r0, [r5, #4]
	bl	ftl_memcpy
	ldr	r3, .L4236+44
	movs	r1, #0
	ldr	r0, [r5, #12]
	ldrb	r2, [r3]	@ zero_extendqisi2
	lsls	r2, r2, #1
	bl	ftl_memset
	ldr	r8, [r5, #12]
	ldr	r3, .L4236+48
	ldr	r0, [r5, #4]
	ldrh	r1, [r10]
	str	r3, [r8]
	bl	js_hash
	ldr	r3, .L4236+52
	str	r0, [r8, #4]
	ldr	r3, [r3]
	ldr	r3, [r3, #132]
	str	r3, [r8, #8]
	movs	r3, #0
	str	r3, [r8, #12]
.L4125:
	ldr	r3, [r5, #12]
	movs	r2, #0
	str	r2, [r3, #16]
.L4119:
	ldr	r3, .L4236+16
	add	r2, sp, #80
	ldr	r3, [r3]
	ldrb	r5, [r3, r7]	@ zero_extendqisi2
	str	r3, [sp, #52]
	ldr	r3, [sp, #32]
	add	r1, r2, r3, lsl #2
	ldr	r2, .L4236+56
	add	r3, r5, r5, lsl #1
	add	r3, r2, r3, lsl #4
	str	r3, [r1, #-24]
	movs	r1, #48
	mla	r1, r1, r5, r2
	ldrb	r3, [sp, #24]	@ zero_extendqisi2
	strb	r3, [r1, #45]
	movs	r3, #2
	strh	r3, [r1, #34]	@ movhi
	ldr	r3, .L4236+4
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, #3
	bne	.L4133
	ldr	r3, .L4236+8
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L4134
	ldr	r3, .L4236+32
	and	r2, r6, #1
	add	r10, r2, r4
	ldrb	r3, [r3]	@ zero_extendqisi2
	cbz	r3, .L4135
	ldr	r3, .L4236+36
	ldrh	r3, [r3, r4, lsl #1]
	cmp	r3, r4
	bcs	.L4135
	cmp	r2, #0
	it	ne
	movne	r10, r3
.L4135:
	ldr	r3, .L4236+56
	mov	r8, #48
	ldr	r1, [sp, #16]
	mov	r0, r6
	mla	r8, r8, r5, r3
	bl	__aeabi_uidiv
	ldr	r3, [sp, #20]
	ldr	r2, .L4236+60
	uxtah	r0, r3, r0
	ldr	r3, [sp, #28]
	ldrh	r2, [r2]
	add	r0, r3, r0, lsl #1
	ldrh	r3, [r0, #96]
	mla	r10, r2, r3, r10
	orr	r3, r10, #50331648
	str	r3, [r8, #24]
.L4140:
	ldr	r2, .L4236+56
	movs	r3, #48
	mla	r5, r3, r5, r2
	ldr	r3, .L4236+64
	ldr	r3, [r3]
	ldr	r1, [r5, #24]
	ldrh	r2, [r5, #32]
	str	r1, [r3, r2, lsl #2]
	b	.L4159
.L4237:
	.align	2
.L4236:
	.word	.LANCHOR236
	.word	.LANCHOR78
	.word	.LANCHOR35
	.word	.LANCHOR80
	.word	.LANCHOR82
	.word	.LANCHOR70
	.word	.LANCHOR85
	.word	.LANCHOR224
	.word	.LANCHOR124
	.word	.LANCHOR235
	.word	.LANCHOR159
	.word	.LANCHOR131
	.word	-178307901
	.word	.LANCHOR12
	.word	.LANCHOR55
	.word	.LANCHOR111
	.word	.LANCHOR161
	.word	.LANCHOR221
.L4124:
	ldr	r0, .L4238
	ldrh	r3, [r10]
	ldrb	r8, [r0]	@ zero_extendqisi2
	ldr	r0, [r5, #4]
	mul	r8, r2, r8
	rsb	r8, r3, r8, lsl #2
	lsrs	r3, r3, #2
	mov	r2, r8
	add	r1, r1, r3, lsl #2
	bl	ftl_memcpy
	ldr	r3, .L4238+4
	movs	r1, #0
	ldr	r0, [r5, #12]
	ldrb	r2, [r3]	@ zero_extendqisi2
	lsls	r2, r2, #1
	bl	ftl_memset
	ldr	r10, [r5, #12]
	mov	r1, r8
	ldr	r3, .L4238+8
	ldr	r0, [r5, #4]
	str	r3, [r10]
	bl	js_hash
	ldr	r3, .L4238+12
	str	r0, [r10, #4]
	ldr	r3, [r3]
	ldr	r3, [r3, #132]
	str	r3, [r10, #8]
	movs	r3, #1
	str	r3, [r10, #12]
	b	.L4125
.L4123:
	ldr	r10, .L4238
	ldr	r0, [r5, #4]
	ldrb	r8, [r10]	@ zero_extendqisi2
	mul	r2, r2, r8
	lsls	r2, r2, #2
	bl	ftl_memcpy
	ldr	r3, .L4238+16
	ldr	r1, .L4238+4
	ldrh	r2, [r3]
	ldrb	r3, [r10]	@ zero_extendqisi2
	ldrb	r1, [r1]	@ zero_extendqisi2
	muls	r3, r2, r3
	cmp	r1, r3, asr #6
	lsl	r2, r3, #2
	ldr	r1, .L4238+20
	it	lt
	ldrlt	r3, .L4238+24
	mov	r0, r2
	ldr	r1, [r1]
	itt	lt
	ldrhlt	r3, [r3]
	sublt	r2, r3, r2
	ldr	r3, [r5, #4]
	add	r0, r0, r3
	bl	ftl_memcpy
	ldr	r3, .L4238+4
	movs	r1, #0
	ldr	r0, [r5, #12]
	ldrb	r2, [r3]	@ zero_extendqisi2
	lsls	r2, r2, #1
	bl	ftl_memset
	ldr	r8, [r5, #12]
	ldr	r3, .L4238+8
	ldr	r2, .L4238
	ldr	r0, [r5, #4]
	str	r3, [r8]
	ldr	r3, .L4238+16
	ldrb	r1, [r2]	@ zero_extendqisi2
	ldrh	r3, [r3]
	muls	r1, r3, r1
	lsls	r1, r1, #2
	bl	js_hash
	ldr	r3, .L4238+12
	str	r0, [r8, #4]
	ldr	r3, [r3]
	ldr	r3, [r3, #132]
	str	r3, [r8, #8]
	b	.L4125
.L4121:
	ldr	r3, .L4238+20
	movs	r1, #1
	mov	r0, r5
	ldr	r3, [r3]
	ldr	r3, [r3, r7, lsl #2]
	str	r3, [r5, #24]
	bl	sblk_read_page
	ldr	r3, [r5, #36]
	adds	r1, r3, #1
	beq	.L4127
	cmp	r3, #512
	bne	.L4131
.L4127:
	ldr	r3, .L4238+28
	movs	r0, #1
	ldr	r2, [r5, #24]
	ldrh	r1, [r3]
	ldr	r3, .L4238+32
	ldrb	r3, [r3]	@ zero_extendqisi2
	lsrs	r2, r2, r1
	rsb	r3, r3, #24
	subs	r3, r3, r1
	ldr	r1, .L4238+36
	lsl	r3, r0, r3
	subs	r3, r3, #1
	ldrb	r1, [r1]	@ zero_extendqisi2
	and	r0, r3, r2
	bl	__aeabi_uidiv
	movs	r1, #0
	uxth	r0, r0
	bl	ftl_sblk_dump
	ldr	r3, [r5, #36]
	adds	r2, r3, #1
	beq	.L4129
	cmp	r3, #512
	bne	.L4131
.L4129:
	ldr	r3, [r5, #12]
	mov	r2, #-1
	str	r2, [r3, #4]
	ldr	r3, [r5, #36]
	cmp	r3, r2
	beq	.L4130
	cmp	r3, #512
	bne	.L4131
.L4130:
	movw	r2, #1223
	ldr	r1, .L4238+40
	ldr	r0, .L4238+44
	bl	printf
.L4131:
	ldr	r3, [r5, #12]
	ldr	r2, .L4238+48
	ldr	r1, [r3, #4]
	ldr	r2, [r2]
	cmp	r1, r2
	itt	cs
	movcs	r2, #-1
	strcs	r2, [r3, #4]
	ldr	r2, .L4238+52
	ldr	r1, [r3, #4]
	ldr	r2, [r2]
	str	r1, [r2, r7, lsl #2]
	ldr	r2, [r5, #24]
	str	r2, [r3, #8]
	b	.L4125
.L4134:
	ldr	r3, .L4238+56
	ldr	r2, .L4238+60
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L4137
	umull	r2, r3, r6, r2
	ldr	r2, [sp, #20]
	ldr	r0, [sp, #28]
	lsrs	r3, r3, #1
	uxtah	r2, r2, r3
	add	r3, r3, r3, lsl #1
	add	r2, r0, r2, lsl #1
	ldr	r0, .L4238+64
	subs	r3, r6, r3
	ldrh	r2, [r2, #96]
	ldrh	r0, [r0]
	mla	r2, r0, r2, r4
	uxtah	r3, r2, r3
.L4233:
	str	r3, [r1, #24]
	movs	r2, #48
	ldr	r3, .L4238+68
	mla	r5, r2, r5, r3
	ldr	r2, .L4238+60
	ldr	r3, .L4238+72
	ldr	r1, [r3]
	umull	r2, r3, r6, r2
	ldr	r2, [r5, #24]
	ldrh	r0, [r5, #32]
	lsrs	r3, r3, #1
	add	r3, r3, r3, lsl #1
	subs	r3, r6, r3
	lsls	r3, r3, #24
	add	r3, r3, #16777216
	orrs	r3, r3, r2
	str	r3, [r1, r0, lsl #2]
.L4159:
	ldr	r3, .L4238+76
	ldrb	r3, [r3]	@ zero_extendqisi2
	cbz	r3, .L4141
	ldr	r3, .L4238+80
	ldrh	r3, [r3, r4, lsl #1]
	cmp	r3, r4
	bcs	.L4141
	lsls	r3, r6, #31
	bpl	.L4141
	ldr	r2, [sp, #52]
	movs	r3, #255
	ldr	r1, [sp, #48]
	strb	r3, [r2, r7]
	add	r2, sp, #80
	ldr	r3, [sp, #32]
	add	r3, r2, r3, lsl #2
	ldrh	r2, [sp, #48]
	ldr	r3, [r3, #-24]
	strh	r2, [r3, #32]	@ movhi
	ldrb	r2, [r3, #1]	@ zero_extendqisi2
	ldr	r3, .L4238+84
	ldr	r3, [r3]
	strb	r2, [r3, r1]
	mov	r2, #-1
	ldr	r3, .L4238+20
	ldr	r3, [r3]
	str	r2, [r3, r7, lsl #2]
.L4141:
	ldr	r3, [sp, #36]
	adds	r3, r3, #1
	b	.L4230
.L4137:
	umull	r2, r3, r6, r2
	ldr	r2, [sp, #20]
	ubfx	r3, r3, #1, #16
	add	r3, r3, r2
	ldr	r2, [sp, #28]
	add	r3, r2, r3, lsl #1
	ldr	r2, .L4238+64
	ldrh	r3, [r3, #96]
	ldrh	r2, [r2]
	mla	r3, r2, r3, r4
	b	.L4233
.L4133:
	cmp	r3, #2
	bne	.L4140
	ldr	r3, .L4238+88
	ldrb	r3, [r3]	@ zero_extendqisi2
	cbnz	r3, .L4139
	ldr	r2, [sp, #20]
	ldr	r3, [sp, #32]
	add	r3, r3, r2
	ldr	r2, [sp, #28]
	add	r3, r2, r3, lsl #1
	ldr	r2, .L4238+64
	ldrh	r3, [r3, #96]
	ldrh	r2, [r2]
	mla	r3, r2, r3, r4
.L4229:
	orr	r3, r3, #33554432
	str	r3, [r1, #24]
	b	.L4140
.L4139:
	ldr	r3, [sp, #20]
	ldr	r2, [sp, #28]
	add	r3, r3, r6, lsr #1
	add	r3, r2, r3, lsl #1
	ldr	r2, .L4238+64
	ldrh	r3, [r3, #96]
	ldrh	r2, [r2]
	mla	r3, r2, r3, r4
	and	r2, r6, #1
	add	r3, r3, r2
	b	.L4229
.L4146:
	add	r0, sp, #80
	add	r5, sp, #80
	add	r0, r0, r3, lsl #2
	add	r3, r5, r3, lsl #2
	ldr	r3, [r3, #-20]
	ldr	r0, [r0, #-24]
	ldrb	r3, [r3, #1]	@ zero_extendqisi2
	strb	r3, [r0]
	b	.L4145
.L4239:
	.align	2
.L4238:
	.word	.LANCHOR79
	.word	.LANCHOR131
	.word	-178307901
	.word	.LANCHOR12
	.word	.LANCHOR85
	.word	.LANCHOR160
	.word	.LANCHOR221
	.word	.LANCHOR74
	.word	.LANCHOR31
	.word	.LANCHOR75
	.word	.LANCHOR234
	.word	.LC0
	.word	.LANCHOR128
	.word	.LANCHOR159
	.word	.LANCHOR36
	.word	-1431655765
	.word	.LANCHOR111
	.word	.LANCHOR55
	.word	.LANCHOR161
	.word	.LANCHOR124
	.word	.LANCHOR235
	.word	.LANCHOR82
	.word	.LANCHOR80
.L4144:
	ldr	r3, .L4240
	ldrb	r2, [r3]	@ zero_extendqisi2
	ldr	r3, [sp, #56]
	cmp	r2, #0
	beq	.L4148
	strb	r1, [r3, #44]
.L4232:
	mov	r2, fp
	add	r1, sp, #68
	add	r0, sp, #56
	bl	sblk_xlc_prog_pages
.L4147:
	ldr	r3, .L4240
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L4156
	add	r3, fp, fp, lsl #1
	uxth	fp, r3
.L4157:
	ldr	r3, .L4240+4
	ldr	r2, [r3]
	ldr	r3, [r2, #52]
	add	r3, r3, fp
	str	r3, [r2, #52]
	ldr	r2, .L4240+8
	ldrh	r3, [r2, #2102]
	add	r3, r3, fp
	uxth	r3, r3
	strh	r3, [r2, #2102]	@ movhi
	ldr	r2, .L4240+12
	ldrh	r1, [r2]
	ldr	r2, [sp, #28]
	ldrb	r2, [r2, #89]	@ zero_extendqisi2
	muls	r2, r1, r2
	cmp	r3, r2
	itttt	ge
	ldrge	r3, .L4240+16
	movge	r2, #0
	ldrge	r3, [r3]
	strhge	r2, [r3, #86]	@ movhi
	bl	gc_write_completed
	b	.L4091
.L4148:
	ldr	r1, [sp, #24]
	cmp	r1, #1
	bne	.L4149
	movs	r2, #9
.L4151:
	strb	r2, [r3, #44]
	b	.L4232
.L4149:
	ldr	r1, [sp, #24]
	cmp	r1, #2
	it	eq
	moveq	r2, #13
	b	.L4151
.L4143:
	ldr	r3, .L4240+20
	ldrb	r3, [r3]	@ zero_extendqisi2
	cbz	r3, .L4152
	ldr	r3, .L4240+24
	ldrb	r3, [r3]	@ zero_extendqisi2
	cbnz	r3, .L4153
.L4152:
	ldr	r2, [sp, #40]
	subs	r1, r2, #1
.L4154:
	uxth	r2, r3
	adds	r3, r3, #1
	cmp	r2, r1
	blt	.L4155
	add	r3, sp, #80
	add	r1, r3, r1, lsl #2
	ldr	r3, [r1, #-24]
	b	.L4231
.L4153:
	mov	r1, fp
	add	r0, sp, #56
	bl	sblk_3d_mlc_prog_pages
	b	.L4147
.L4155:
	add	r0, sp, #80
	add	r5, sp, #80
	add	r0, r0, r2, lsl #2
	add	r2, r5, r2, lsl #2
	ldr	r2, [r2, #-20]
	ldr	r0, [r0, #-24]
	ldrb	r2, [r2, #1]	@ zero_extendqisi2
	strb	r2, [r0]
	b	.L4154
.L4156:
	ldr	r3, .L4240+20
	ldrb	r3, [r3]	@ zero_extendqisi2
	cbnz	r3, .L4170
	ldr	r3, .L4240+28
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L4157
	ldrh	r3, [sp, #16]
	ldr	r2, .L4240+32
	ldrb	r2, [r2]	@ zero_extendqisi2
	smulbb	r3, fp, r3
	uxth	r3, r3
	cbz	r2, .L4171
	ldr	r2, .L4240+36
	ldrh	r2, [r2, r4, lsl #1]
	cmp	r2, r4
	it	cs
	movcs	fp, r3
	b	.L4157
.L4170:
	ldr	fp, [sp, #44]
	b	.L4157
.L4171:
	mov	fp, r3
	b	.L4157
.L4241:
	.align	2
.L4240:
	.word	.LANCHOR83
	.word	.LANCHOR110
	.word	.LANCHOR70
	.word	.LANCHOR85
	.word	.LANCHOR12
	.word	.LANCHOR80
	.word	.LANCHOR81
	.word	.LANCHOR35
	.word	.LANCHOR124
	.word	.LANCHOR235
	.size	gc_do_copy_back, .-gc_do_copy_back
	.section	.text.zftl_do_gc,"ax",%progbits
	.align	1
	.global	zftl_do_gc
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	zftl_do_gc, %function
zftl_do_gc:
	@ args = 0, pretend = 0, frame = 24
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, r8, r10, fp, lr}
	sub	sp, sp, #48
	ldr	r3, .L4447
	ldr	r7, .L4447+4
	ldr	r5, .L4447+8
	ldrh	r3, [r3]
	ldrh	r6, [r7]
	ldr	r1, .L4447+12
	ldrb	r2, [r5]	@ zero_extendqisi2
	add	r6, r6, r3
	str	r0, [sp, #32]
	ldr	r4, [r1]
	uxth	r6, r6
	mov	r8, r1
	cmp	r2, #6
	bhi	.L4359
	tbh	[pc, r2, lsl #1]
.L4245:
	.2byte	(.L4244-.L4245)/2
	.2byte	(.L4246-.L4245)/2
	.2byte	(.L4247-.L4245)/2
	.2byte	(.L4248-.L4245)/2
	.2byte	(.L4249-.L4245)/2
	.2byte	(.L4250-.L4245)/2
	.2byte	(.L4251-.L4245)/2
	.p2align 1
.L4250:
	ldr	r4, .L4447+16
	movs	r7, #0
.L4252:
	bl	gc_check_data_one_wl
	mov	r10, r0
	cmp	r0, #0
	beq	.L4355
	ldr	r3, [r8]
	movs	r6, #0
	strh	r6, [r4, #52]	@ movhi
	ldrh	r0, [r3, #80]
	bl	ftl_free_sblk
	ldr	r1, .L4447+20
	movw	r3, #65535
	ldr	r2, [r8]
	ldr	r0, [r4, #8]
	ldr	r1, [r1]
	strh	r3, [r2, #80]	@ movhi
	strh	r3, [r1, #126]	@ movhi
	strh	r3, [r2, #130]	@ movhi
	bl	zbuf_free
	str	r6, [r4, #8]
	strb	r6, [r5]
	b	.L4444
.L4244:
	ldr	r2, .L4447+24
	ldr	r1, .L4447+28
	ldr	r0, .L4447+32
	ldrh	r7, [r2]
	ldrh	r2, [r1]
	ldrh	r0, [r0]
	add	r7, r7, r3
	str	r1, [sp, #36]
	uxth	r7, r7
	add	r2, r2, r0
	ldrh	r0, [r4, #80]
	uxth	r2, r2
	str	r2, [sp, #28]
	movw	r2, #65535
	cmp	r0, r2
	beq	.L4253
	ldr	r3, [sp, #32]
	cbnz	r3, .L4254
	ldr	r3, .L4447+36
	ldrh	r3, [r3]
	cmp	r6, r3, lsl #1
	blt	.L4254
.L4359:
	movs	r4, #16
	b	.L4242
.L4254:
	ldr	r10, .L4447+80
	ldr	r0, .L4447+40
	ldr	fp, .L4447+84
	ldrh	r1, [r10]
	adds	r1, r1, #1
	uxth	r1, r1
	strh	r1, [r10]	@ movhi
	bl	_list_get_gc_head_node
	movw	r3, #65535
	mov	ip, r10
	cmp	r0, r3
	beq	.L4255
	ldr	r1, .L4447+44
	ldr	lr, .L4447+76
	ldr	r2, .L4447+48
	ldr	r1, [r1]
	ldrh	lr, [lr]
	ldr	r3, [r2]
	mov	r10, r2
	ldrh	r1, [r1, r0, lsl #1]
	adds	r3, r3, #1
	cmp	lr, r1
	str	r3, [r2]
	bcs	.L4256
	ldr	r2, .L4447+52
	ldrh	r2, [r2]
	cmp	r3, r2, lsr #4
	bls	.L4255
	ldr	r3, .L4447+56
	ldrh	r3, [r3]
	cmp	r3, r1
	bls	.L4255
.L4256:
	ldrb	r2, [fp]	@ zero_extendqisi2
	movs	r1, #0
	bl	gc_add_sblk
	cbz	r0, .L4257
	movs	r3, #1
	strb	r3, [r5]
	movs	r3, #0
	str	r3, [r10]
	b	.L4359
.L4255:
	movs	r3, #0
	strh	r3, [ip]	@ movhi
.L4257:
	cmp	r7, #15
	bls	.L4361
	ldr	r3, .L4447+60
	ldrh	r2, [r3]
	ldr	r3, .L4447+64
	ldrh	r3, [r3]
	cmp	r2, r3
	bhi	.L4361
	ldr	r3, [sp, #28]
	cmp	r3, #0
	ite	eq
	moveq	r10, #2
	movne	r10, #1
.L4258:
	ldr	r3, .L4447+68
	ldr	r3, [r3]
	lsls	r3, r3, #23
	bpl	.L4259
	ldr	r3, [r8]
	ldrh	r1, [r4, #80]
	ldrb	r2, [fp]	@ zero_extendqisi2
	ldr	r0, .L4447+72
	str	r1, [sp, #16]
	ldrh	r1, [r3, #122]
	str	r1, [sp, #12]
	ldrh	r1, [r3, #120]
	str	r1, [sp, #8]
	movw	r1, #2807
	ldrh	r3, [r3, #124]
	str	r7, [sp]
	str	r3, [sp, #4]
	mov	r3, r6
	bl	printf
.L4259:
	movs	r2, #1
	mov	r1, r10
	ldrb	r0, [fp]	@ zero_extendqisi2
	bl	gc_search_src_blk
	cmp	r0, #0
	ble	.L4260
.L4261:
	movs	r3, #1
.L4445:
	strb	r3, [r5]
	b	.L4359
.L4361:
	mov	r10, #2
	b	.L4258
.L4260:
	movs	r2, #1
	movs	r1, #3
	ldrb	r0, [fp]	@ zero_extendqisi2
	bl	gc_search_src_blk
	cmp	r0, #0
	bgt	.L4261
	b	.L4359
.L4253:
	ldr	r2, [sp, #32]
	cmp	r2, #1
	bne	.L4263
	ldr	r2, .L4447+20
	ldr	r2, [r2]
	ldrh	r2, [r2, #150]
	cbz	r2, .L4264
	cmp	r3, #8
	bls	.L4264
	bl	gc_ink_check_sblk
.L4264:
	bl	gc_scan_static_data
	ldr	r3, [r8]
	ldr	fp, .L4447+84
	ldrh	r3, [r3, #122]
	cbz	r3, .L4265
.L4266:
	movs	r3, #1
	strb	r3, [fp]
	b	.L4445
.L4448:
	.align	2
.L4447:
	.word	.LANCHOR107
	.word	.LANCHOR103
	.word	.LANCHOR156
	.word	.LANCHOR12
	.word	.LANCHOR70
	.word	.LANCHOR110
	.word	.LANCHOR105
	.word	.LANCHOR97
	.word	.LANCHOR99
	.word	.LANCHOR86
	.word	.LANCHOR92
	.word	.LANCHOR11
	.word	.LANCHOR157
	.word	.LANCHOR8
	.word	.LANCHOR100
	.word	.LANCHOR91
	.word	.LANCHOR101
	.word	.LANCHOR19
	.word	.LC239
	.word	.LANCHOR94
	.word	.LANCHOR96
	.word	.LANCHOR84
.L4265:
	bl	gc_static_wearleveling
	mov	r4, r0
	cmp	r0, #0
	bne	.L4266
	ldr	r10, .L4449+20
	cmp	r7, #0
	beq	.L4267
	ldr	r3, [sp, #28]
	ldr	r2, .L4449
	cmp	r6, r3
	bcs	.L4268
	ldrh	r3, [r2]
	cmp	r3, r6
	bhi	.L4269
.L4268:
	ldr	r3, [sp, #28]
	ldrh	r2, [r2]
	adds	r3, r6, r3
	cmp	r3, r2
	blt	.L4269
	ldr	r3, .L4449+4
	ldrh	r2, [r3]
	ldr	r3, .L4449+8
	ldrh	r3, [r3]
	cmp	r2, r3
	bcc	.L4267
.L4269:
	movs	r3, #1
	movs	r1, #16
	ldr	r0, .L4449+12
	strb	r3, [fp]
	str	r3, [sp, #40]
	bl	_list_get_gc_head_node
	movw	r1, #65535
	cmp	r0, r1
	beq	.L4270
	ldr	r1, .L4449+16
	ldr	r2, .L4449+20
	ldr	r1, [r1]
	ldrh	r2, [r2]
	ldrh	r1, [r1, r0, lsl #1]
	cmp	r1, r2
	bcs	.L4270
	cmp	r6, #2
	ldr	r3, [sp, #40]
	bls	.L4270
	ldr	r1, .L4449+24
	movs	r2, #0
	strb	r2, [fp]
	str	r2, [r1]
	mov	r1, r3
	bl	gc_add_sblk
	cmp	r0, #0
	bne	.L4261
.L4270:
	movs	r1, #0
	ldr	r0, .L4449+28
	bl	_list_get_gc_head_node
	movw	r2, #65535
	cmp	r0, r2
	beq	.L4271
	ldr	r2, .L4449+16
	ldr	r3, .L4449+20
	ldr	r2, [r2]
	ldrh	r3, [r3]
	ldrh	r2, [r2, r0, lsl #1]
	cmp	r2, r3
	bcs	.L4271
	cmp	r6, #2
	bls	.L4271
	ldr	r3, .L4449+24
	movs	r2, #0
	movs	r1, #1
	strb	r2, [fp]
	str	r2, [r3]
	bl	gc_add_sblk
	cmp	r0, #0
	bne	.L4261
.L4271:
	ldr	r2, .L4449+32
	ldrh	r3, [r10]
	ldr	r1, .L4449+36
	ldrh	fp, [r2]
	adds	r3, r3, #1
	ldr	r2, .L4449+24
	uxth	r3, r3
	cmp	r3, fp, lsr #5
	strh	r3, [r10]	@ movhi
	str	r2, [sp, #44]
	itt	hi
	movhi	r3, #4
	strhhi	r3, [r10]	@ movhi
	mov	r10, #0
	strh	r10, [r1]	@ movhi
	ldr	r1, .L4449+40
	ldr	r3, [r2]
	strh	r10, [r1]	@ movhi
	ldr	r1, .L4449+44
	adds	r3, r3, #1
	str	r3, [r2]
	strh	r10, [r1]	@ movhi
	ldr	r1, .L4449+48
	ldrh	r1, [r1]
	cmp	r3, r1, lsr #5
	ldr	r3, .L4449+52
	ldr	r1, .L4449+4
	bls	.L4273
	ldrh	r0, [r1]
	cmp	r0, r7
	bls	.L4273
	mov	r1, r10
	ldr	r0, .L4449+56
	str	r3, [sp, #40]
	bl	_list_get_gc_head_node
	movw	r1, #65535
	ldr	r3, [sp, #40]
	cmp	r0, r1
	ldr	r2, [sp, #44]
	bne	.L4274
.L4434:
	movs	r4, #16
	b	.L4275
.L4274:
	ldr	r1, .L4449+16
	ldr	r1, [r1]
	ldrh	r1, [r1, r0, lsl #1]
	ldr	r0, .L4449+60
	ldrb	r0, [r0]	@ zero_extendqisi2
	mul	fp, fp, r0
	cmp	r1, fp
	bgt	.L4434
	str	r10, [r2]
	movs	r2, #4
.L4441:
	movs	r1, #2
.L4433:
	ldrb	r0, [r3]	@ zero_extendqisi2
	bl	gc_search_src_blk
	uxth	r0, r0
	cmp	r0, #0
	beq	.L4434
	b	.L4261
.L4273:
	ldr	r2, .L4449+8
	ldrh	r1, [r1]
	ldrh	r2, [r2]
	cmp	r1, r2
	bcc	.L4278
	movs	r2, #1
	b	.L4441
.L4278:
	ldr	r2, [sp, #36]
	ldrh	r2, [r2]
	cbnz	r2, .L4279
	ldr	r2, .L4449+64
	ldrh	r2, [r2]
	cmp	r2, #8
	bls	.L4280
.L4279:
	movs	r2, #4
	movs	r1, #1
	b	.L4433
.L4280:
	ldr	r3, .L4449+68
	ldrh	r3, [r3, #2106]
	cmp	r3, #0
	bne	.L4434
.L4275:
	ldr	r3, [r8]
	movs	r1, #1
	ldr	fp, .L4449+52
	ldrh	r3, [r3, #124]
	strb	r1, [fp]
	mov	r8, fp
	cbz	r3, .L4281
	movs	r3, #0
	strb	r1, [r5]
	strb	r3, [fp]
.L4242:
	mov	r0, r4
	add	sp, sp, #48
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r10, fp, pc}
.L4267:
	ldr	r3, .L4449+32
	ldrh	r2, [r3]
	ldrh	r3, [r10]
	cmp	r3, r2, lsr #5
	itt	cs
	movcs	r3, #4
	strhcs	r3, [r10]	@ movhi
	b	.L4434
.L4263:
	ldr	r3, .L4449+72
	ldrh	r3, [r3]
	cmp	r3, r6
	bcs	.L4434
	ldrh	r3, [r4, #124]
	cmp	r3, #0
	beq	.L4359
	b	.L4434
.L4281:
	ldr	r2, .L4449+72
	ldrh	r0, [r2]
	mov	r10, r2
	cmp	r6, r0
	bcs	.L4282
	cmp	r7, #0
	beq	.L4283
	cmp	r7, #16
	bls	.L4284
	ldr	r2, .L4449+4
	ldrh	r0, [r2]
	ldr	r2, .L4449+8
	ldrh	r2, [r2]
	cmp	r0, r2
	bhi	.L4284
	movs	r2, #4
	mov	r0, r1
	str	r3, [sp, #28]
	bl	gc_search_src_blk
	uxth	r0, r0
	ldr	r3, [sp, #28]
	cbnz	r0, .L4285
.L4439:
	movs	r2, #4
	movs	r1, #3
	ldrb	r0, [fp]	@ zero_extendqisi2
	b	.L4436
.L4285:
	mov	r1, r3
	ldr	r0, .L4449+56
	bl	_list_get_gc_head_node
	movw	r3, #65535
	cmp	r0, r3
	beq	.L4288
	ldr	r1, .L4449+16
	ldr	r6, .L4449+32
	ldr	r2, .L4449+24
	ldr	r1, [r1]
	ldrh	r6, [r6]
	ldr	r3, [r2]
	ldrh	r1, [r1, r0, lsl #1]
	adds	r3, r3, #1
	cmp	r6, r1
	str	r3, [r2]
	mov	r6, r2
	bcs	.L4289
	ldr	r2, .L4449+48
	ldrh	r2, [r2]
	cmp	r3, r2, lsr #4
	bls	.L4288
	ldr	r3, .L4449+76
	ldrh	r3, [r3]
	cmp	r3, r1
	bls	.L4288
.L4289:
	ldrb	r2, [r8]	@ zero_extendqisi2
	movs	r1, #0
	bl	gc_add_sblk
	ldr	r3, .L4449+80
	movs	r2, #1
	str	r2, [r3]
	movs	r3, #0
	str	r3, [r6]
.L4288:
	movs	r3, #1
	b	.L4440
.L4284:
	movs	r2, #1
	movs	r1, #2
	mov	r0, r2
	bl	gc_search_src_blk
	uxth	r0, r0
	cmp	r0, #0
	bne	.L4288
	ldrb	r0, [r8]	@ zero_extendqisi2
	movs	r2, #4
	movs	r1, #3
.L4436:
	bl	gc_search_src_blk
	uxth	r0, r0
.L4286:
	cmp	r0, #0
	bne	.L4288
	b	.L4242
.L4283:
	cmp	r6, #16
	strb	r7, [fp]
	bls	.L4291
	movs	r2, #4
	movs	r1, #3
	mov	r0, r7
	b	.L4436
.L4291:
	mov	r2, r1
	mov	r0, r7
	bl	gc_search_src_blk
	uxth	r0, r0
	cmp	r0, #0
	bne	.L4288
	b	.L4439
.L4282:
	ldr	r3, [sp, #32]
	cmp	r3, #1
	bne	.L4242
	cmp	r6, r0, lsl #1
	bge	.L4292
	ldr	r3, [sp, #28]
	cmp	r3, r7, lsr #1
	bcs	.L4293
	ldr	r3, .L4449+4
	ldrh	r1, [r3]
	ldr	r3, .L4449+8
	ldrh	r3, [r3]
	cmp	r1, r3
	bcs	.L4293
	ldr	r3, .L4449
	ldrh	r3, [r3]
	lsrs	r3, r3, #2
	strh	r3, [r2]	@ movhi
	b	.L4242
.L4450:
	.align	2
.L4449:
	.word	.LANCHOR98
	.word	.LANCHOR91
	.word	.LANCHOR101
	.word	.LANCHOR95
	.word	.LANCHOR11
	.word	.LANCHOR158
	.word	.LANCHOR157
	.word	.LANCHOR90
	.word	.LANCHOR94
	.word	.LANCHOR87
	.word	.LANCHOR88
	.word	.LANCHOR89
	.word	.LANCHOR8
	.word	.LANCHOR84
	.word	.LANCHOR92
	.word	.LANCHOR79
	.word	.LANCHOR99
	.word	.LANCHOR70
	.word	.LANCHOR86
	.word	.LANCHOR100
	.word	.LANCHOR122
.L4293:
	movs	r1, #8
	ldr	r0, .L4451
	bl	_list_get_gc_head_node
	movw	r2, #65535
	cmp	r0, r2
	beq	.L4294
	ldr	r2, .L4451+4
	ldr	r2, [r2]
	ldrh	r3, [r2, r0, lsl #1]
	cmp	r3, #3
	bhi	.L4294
	cbz	r6, .L4294
	movs	r2, #0
	movs	r1, #1
	strb	r2, [r8]
	bl	gc_add_sblk
	cmp	r0, #0
	bne	.L4288
.L4294:
	movs	r1, #0
	ldr	r0, .L4451+8
	bl	_list_get_gc_head_node
	movw	r3, #65535
	mov	fp, r0
	cmp	r0, r3
	bne	.L4295
.L4300:
	cmp	r7, #1
	bhi	.L4296
.L4297:
	ldr	r3, [sp, #28]
	cmp	r6, r3
	ldr	r6, .L4451+12
	bcs	.L4304
	movs	r7, #0
	movs	r1, #4
	ldr	r0, .L4451
	strb	r7, [r8]
	bl	_list_get_gc_head_node
	movw	r3, #65535
	cmp	r0, r3
	beq	.L4304
	ldr	r3, .L4451+4
	ldr	r3, [r3]
	ldrh	r2, [r3, r0, lsl #1]
	ldr	r3, .L4451+16
	ldrh	r1, [r3]
	ldr	r3, .L4451+20
	ldrb	r3, [r3]	@ zero_extendqisi2
	muls	r3, r1, r3
	cmp	r2, r3, asr #1
	ble	.L4306
.L4304:
	ldrh	r3, [r6]
	lsrs	r3, r3, #2
	strh	r3, [r10]	@ movhi
	b	.L4242
.L4295:
	ldr	r2, .L4451+24
	ldr	r1, .L4451+28
	ldr	r3, [r2]
	ldrh	r1, [r1]
	adds	r3, r3, #1
	str	r3, [r2]
	cmp	r3, r1, lsr #4
	bls	.L4298
	ldr	r3, .L4451+4
	movs	r1, #0
	str	r1, [r2]
	ldr	r3, [r3]
	ldrh	r2, [r3, r0, lsl #1]
	ldr	r3, .L4451+32
	ldrh	r3, [r3]
	cmp	r2, r3
	bcs	.L4298
	movs	r3, #1
	mov	r2, r3
	strb	r3, [r8]
	str	r3, [sp, #32]
	bl	gc_add_sblk
	ldr	r3, [sp, #32]
	cbz	r0, .L4298
.L4440:
	strb	r3, [r5]
	b	.L4242
.L4298:
	ldr	r3, .L4451+4
	ldr	r3, [r3]
	ldrh	r2, [r3, fp, lsl #1]
	ldr	r3, .L4451+16
	ldrh	r3, [r3]
	cmp	r2, r3, lsr #1
	bhi	.L4299
	movs	r2, #0
	movs	r1, #1
	mov	r0, fp
	bl	gc_add_sblk
	b	.L4288
.L4299:
	ldr	r3, [sp, #36]
	ldr	r1, .L4451+36
	ldrh	r3, [r3]
	ldrh	r1, [r1]
	add	r3, r3, r1
	ldr	r1, .L4451+12
	ldrh	r1, [r1]
	cmp	r3, r1, lsl #1
	ble	.L4300
	ldr	r3, .L4451+32
	ldrh	r3, [r3]
	cmp	r3, r2
	bcc	.L4297
	b	.L4300
.L4296:
	cmp	r7, #16
	mov	r1, #1
	strb	r1, [r8]
	bls	.L4301
	ldr	r3, .L4451+40
	ldrh	r2, [r3]
	ldr	r3, .L4451+44
	ldrh	r3, [r3]
	cmp	r2, r3
	bhi	.L4301
	movs	r2, #4
	mov	r0, r1
.L4443:
	bl	gc_search_src_blk
	uxth	r0, r0
	cbnz	r0, .L4302
	movs	r2, #4
	movs	r1, #3
	ldrb	r0, [r8]	@ zero_extendqisi2
	bl	gc_search_src_blk
	uxth	r0, r0
.L4302:
	ldr	r3, [sp, #28]
	cmp	r6, r3, lsr #1
	ldr	r3, .L4451+12
	ldrh	r3, [r3]
	bls	.L4437
	lsrs	r3, r3, #2
.L4438:
	strh	r3, [r10]	@ movhi
	b	.L4286
.L4301:
	movs	r2, #1
	movs	r1, #2
	mov	r0, r2
	b	.L4443
.L4306:
	movs	r2, #4
	movs	r1, #3
	mov	r0, r7
	bl	gc_search_src_blk
	ldrh	r3, [r6]
	uxth	r0, r0
.L4437:
	lsrs	r3, r3, #1
	b	.L4438
.L4292:
	ldr	r3, .L4451+12
	ldrh	r3, [r3]
	lsrs	r3, r3, #2
	strh	r3, [r2]	@ movhi
	ldr	r3, .L4451+48
	ldrh	r3, [r3, #2106]
	cmp	r3, #0
	it	eq
	moveq	r4, #0
	b	.L4242
.L4246:
	ldr	r4, .L4451+48
	movw	r3, #65535
	ldrh	r2, [r4]
	cmp	r2, r3
	bne	.L4307
	bl	gc_get_src_blk
	strh	r0, [r4]	@ movhi
.L4307:
	ldrh	r2, [r4]
	movw	r3, #65535
	cmp	r2, r3
	beq	.L4308
	ldr	r1, .L4451+28
	ldrh	r1, [r1]
	cmp	r1, r2
	it	ls
	strhls	r3, [r4]	@ movhi
.L4308:
	ldrh	r6, [r4]
	movw	r3, #65535
	cmp	r6, r3
	beq	.L4446
	ldr	r3, .L4451+52
	ldrh	r1, [r4, #52]
	ldr	r3, [r3]
	add	r3, r3, r6, lsl #2
	cbz	r1, .L4310
	ldr	r0, .L4451+56
	movs	r2, #0
.L4311:
	uxth	r4, r2
	cmp	r1, r4
	bhi	.L4312
.L4310:
	ldrb	r3, [r3, #2]	@ zero_extendqisi2
	and	r2, r3, #224
	cmp	r2, #224
	beq	.L4313
	tst	r3, #192
	bne	.L4314
.L4313:
	ldr	r3, .L4451+4
	ldr	r3, [r3]
	ldrh	r3, [r3, r6, lsl #1]
	cbz	r3, .L4316
	movw	r2, #3306
	ldr	r1, .L4451+60
	ldr	r0, .L4451+64
	bl	printf
	b	.L4316
.L4312:
	ldrh	r4, [r0, #2]!
	adds	r2, r2, #1
	cmp	r4, r6
	bne	.L4311
.L4316:
	ldr	r3, .L4451+48
	movw	r2, #65535
	strh	r2, [r3]	@ movhi
	b	.L4359
.L4314:
	movs	r3, #2
	b	.L4445
.L4247:
	bl	gc_scan_src_blk
	adds	r0, r0, #1
	bne	.L4317
	movs	r3, #3
	b	.L4445
.L4317:
	ldr	r3, .L4451+48
	movw	r1, #65535
	ldrh	r2, [r3]
	mov	r4, r3
	cmp	r2, r1
	beq	.L4261
	ldrh	r1, [r3, #20]
	cbz	r1, .L4318
	movs	r2, #4
	strb	r2, [r5]
	movs	r2, #0
	strh	r2, [r3, #22]	@ movhi
	b	.L4359
.L4318:
	movs	r3, #1
	strb	r3, [r5]
	ldr	r5, .L4451+4
	ldr	r1, [r5]
	ldrh	r2, [r1, r2, lsl #1]
	cbz	r2, .L4319
	movw	r2, #3336
	ldr	r1, .L4451+60
	ldr	r0, .L4451+64
	bl	printf
.L4319:
	ldrh	r0, [r4]
	bl	ftl_free_sblk
	ldr	r3, [r5]
	movs	r5, #0
	ldrh	r2, [r4]
	strh	r5, [r3, r2, lsl #1]	@ movhi
	ldrh	r3, [r4, #26]
	adds	r3, r3, #1
	uxth	r3, r3
	cmp	r3, #8
	bhi	.L4320
	strh	r3, [r4, #26]	@ movhi
	b	.L4316
.L4320:
	strh	r5, [r4, #26]	@ movhi
	bl	ftl_flush
	bl	pm_flush
	bl	ftl_ext_info_flush
	mov	r0, r5
	bl	ftl_info_flush
	b	.L4316
.L4248:
	ldr	r7, .L4451+48
	mov	r4, r7
.L4408:
	bl	gc_scan_src_blk_one_page
	ldr	r3, .L4451+16
	ldrh	r2, [r7, #2]
	ldrh	r3, [r3]
	cmp	r2, r3
	bcs	.L4322
	cmp	r6, #7
	bls	.L4408
	b	.L4359
.L4452:
	.align	2
.L4451:
	.word	.LANCHOR95
	.word	.LANCHOR11
	.word	.LANCHOR92
	.word	.LANCHOR98
	.word	.LANCHOR94
	.word	.LANCHOR79
	.word	.LANCHOR157
	.word	.LANCHOR8
	.word	.LANCHOR100
	.word	.LANCHOR99
	.word	.LANCHOR91
	.word	.LANCHOR101
	.word	.LANCHOR70
	.word	.LANCHOR9
	.word	.LANCHOR70+52
	.word	.LANCHOR237
	.word	.LC0
.L4322:
	ldrh	r3, [r7, #20]
	ldrh	r1, [r7]
	cbz	r3, .L4323
	movs	r2, #4
	strb	r2, [r5]
	movs	r2, #0
	ldr	r5, .L4453
	strh	r2, [r7, #22]	@ movhi
	ldr	r2, [r5]
	ldrh	r2, [r2, r1, lsl #1]
	cmp	r3, r2
	beq	.L4324
	ldr	r0, .L4453+4
	ldr	r0, [r0]
	lsls	r6, r0, #21
	bpl	.L4324
	ldr	r0, .L4453+8
	bl	printf
.L4324:
	ldr	r3, [r5]
	ldrh	r2, [r4]
	ldrh	r2, [r3, r2, lsl #1]
	ldrh	r3, [r4, #20]
	cmp	r2, r3
	beq	.L4325
	movw	r2, #3379
	ldr	r1, .L4453+12
	ldr	r0, .L4453+16
	bl	printf
.L4325:
	ldrh	r1, [r4, #20]
	ldrh	r2, [r4]
	ldr	r3, [r5]
	strh	r1, [r3, r2, lsl #1]	@ movhi
	b	.L4359
.L4323:
	ldr	r3, .L4453+20
	ldr	r6, [r3]
	movs	r3, #1
	strb	r3, [r5]
	ldr	r3, .L4453+4
	add	r6, r6, r1, lsl #2
	ldr	r3, [r3]
	lsls	r5, r3, #23
	bpl	.L4326
	ldrb	r2, [r6, #2]	@ zero_extendqisi2
	ldr	r0, .L4453+24
	lsrs	r2, r2, #5
	bl	printf
.L4326:
	ldrb	r3, [r6, #2]	@ zero_extendqisi2
	and	r2, r3, #224
	cmp	r2, #224
	beq	.L4327
	tst	r3, #192
	bne	.L4328
.L4327:
	movw	r2, #3389
	ldr	r1, .L4453+12
	ldr	r0, .L4453+16
	bl	printf
.L4328:
	ldrh	r0, [r4]
	bl	ftl_free_sblk
	movw	r3, #65535
	strh	r3, [r4]	@ movhi
	ldrh	r3, [r4, #26]
	adds	r3, r3, #1
	uxth	r3, r3
	cmp	r3, #8
	bhi	.L4329
	strh	r3, [r4, #26]	@ movhi
	b	.L4359
.L4329:
	movs	r3, #0
	strh	r3, [r4, #26]	@ movhi
.L4444:
	bl	flt_sys_flush
	b	.L4359
.L4249:
	ldrh	r2, [r4, #80]
	movw	r3, #65535
	cmp	r2, r3
	bne	.L4330
	ldr	r3, .L4453+28
	ldrb	r10, [r3]	@ zero_extendqisi2
	cmp	r10, #1
	bne	.L4330
	ldr	r6, .L4453+32
	bl	ftl_flush
	movs	r1, #5
	ldrh	r0, [r6, #2180]
	cbz	r0, .L4331
	mov	r0, r10
.L4331:
	bl	zftl_gc_get_free_sblk
	movw	r3, #65535
	mov	r5, r0
	cmp	r0, r3
	beq	.L4333
	ldr	r3, .L4453+20
	ldr	r7, [r3]
	add	r7, r7, r0, lsl #2
	ldrb	r3, [r7, #2]	@ zero_extendqisi2
	tst	r3, #224
	beq	.L4334
	movw	r2, #3423
	ldr	r1, .L4453+12
	ldr	r0, .L4453+16
	bl	printf
.L4334:
	ldrb	r3, [r7, #2]	@ zero_extendqisi2
	and	r3, r3, #15
	orr	r3, r3, #176
	strb	r3, [r7, #2]
.L4358:
	movs	r1, #1
	mov	r0, r5
	bl	ftl_erase_sblk
	movs	r3, #5
	add	r1, r4, #96
	strb	r3, [r4, #84]
	mov	r0, r5
	bl	ftl_get_blk_list_in_sblk
	ldr	r3, .L4453+36
	uxtb	r0, r0
	movs	r7, #0
	ldr	r10, .L4453+64
	strb	r0, [r4, #89]
	movs	r1, #255
	ldrh	r3, [r3]
	strh	r5, [r4, #80]	@ movhi
	strh	r7, [r4, #82]	@ movhi
	strb	r7, [r4, #85]
	smulbb	r0, r3, r0
	strh	r7, [r4, #90]	@ movhi
	ldrh	r3, [r10]
	strh	r0, [r4, #86]	@ movhi
	ldr	r4, .L4453+40
	ldrb	r2, [r4]	@ zero_extendqisi2
	muls	r2, r3, r2
	ldr	r3, .L4453+44
	ldr	r0, [r3]
	lsls	r2, r2, #2
	bl	ftl_memset
	ldrh	r3, [r10]
	movs	r1, #255
	ldrb	r2, [r4]	@ zero_extendqisi2
	muls	r2, r3, r2
	ldr	r3, .L4453+48
	ldr	r0, [r3]
	lsls	r2, r2, #2
	bl	ftl_memset
	ldrh	r3, [r10]
	movs	r1, #255
	ldrb	r2, [r4]	@ zero_extendqisi2
	muls	r2, r3, r2
	ldr	r3, .L4453+52
	ldr	r0, [r3]
	bl	ftl_memset
	ldr	r3, [r8]
	movw	r2, #65535
	strh	r2, [r3, #128]	@ movhi
	strh	r2, [r3, #130]	@ movhi
	str	r5, [r3, #132]
	bl	pm_flush
	bl	ftl_ext_info_flush
	ldr	r3, .L4453+56
	mov	r0, r7
	strh	r7, [r6, #52]	@ movhi
	ldr	r3, [r3]
	strh	r5, [r3, #126]	@ movhi
	mov	r3, #-1
	strh	r7, [r6, #2102]	@ movhi
	strh	r7, [r6, #2104]	@ movhi
	strh	r7, [r6, #2182]	@ movhi
	str	r3, [r6, #2184]
	bl	ftl_info_flush
	b	.L4359
.L4330:
	ldr	r3, [sp, #32]
	ldr	r10, .L4453+28
	cmp	r3, #1
	ite	ne
	movne	fp, #1
	moveq	fp, #4
	cmp	r6, #15
	ldr	r6, .L4453+32
	it	ls
	addls	fp, fp, #4
.L4337:
	add	fp, fp, #-1
	uxtb	fp, fp
	cmp	fp, #255
	beq	.L4359
	bl	gc_do_copy_back
	ldrb	r3, [r10]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L4338
	ldr	r3, .L4453+60
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, #3
	bhi	.L4339
	bl	ftl_write_commit
.L4339:
	ldrh	r2, [r6, #22]
	ldrh	r3, [r6, #20]
	cmp	r2, r3
	bcc	.L4337
	ldr	r4, .L4453
	movs	r3, #1
	strb	r3, [r5]
	bl	ftl_write_commit
	bl	ftl_flush
	ldrh	r1, [r6]
	ldr	r2, [r4]
	ldrh	r2, [r2, r1, lsl #1]
	cbz	r2, .L4341
	movw	r2, #3507
	ldr	r1, .L4453+12
	ldr	r0, .L4453+16
	bl	printf
.L4341:
	ldrh	r0, [r6]
	ldr	r3, [r4]
	ldrh	r3, [r3, r0, lsl #1]
	cbnz	r3, .L4342
	bl	ftl_free_sblk
	b	.L4316
.L4342:
	movs	r2, #1
	movs	r1, #0
	bl	gc_add_sblk
	b	.L4316
.L4454:
	.align	2
.L4453:
	.word	.LANCHOR11
	.word	.LANCHOR19
	.word	.LC240
	.word	.LANCHOR237
	.word	.LC0
	.word	.LANCHOR9
	.word	.LC241
	.word	.LANCHOR84
	.word	.LANCHOR70
	.word	.LANCHOR94
	.word	.LANCHOR79
	.word	.LANCHOR159
	.word	.LANCHOR160
	.word	.LANCHOR82
	.word	.LANCHOR110
	.word	.LANCHOR57
	.word	.LANCHOR85
.L4338:
	ldrh	r3, [r6, #2182]
	cmp	r3, #0
	beq	.L4343
	movs	r3, #0
	ldr	r10, .L4455+60
	strh	r3, [r6, #2182]	@ movhi
	bl	sblk_wait_write_queue_completed
	bl	gc_write_completed
	ldr	r0, [r6, #2184]
	adds	r4, r0, #1
	beq	.L4344
	ldr	r3, .L4455
	ldrb	r3, [r3]	@ zero_extendqisi2
	cbnz	r3, .L4345
	ldr	r3, .L4455+4
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L4346
.L4345:
	ldr	r3, [r10]
	ldr	r2, [r3, #156]
	ldr	r3, .L4455+8
	cmp	r2, r3
	bne	.L4346
	ldr	r3, .L4455+12
	ldrh	r1, [r3]
	ldr	r3, .L4455+16
	ldrb	r3, [r3]	@ zero_extendqisi2
	lsrs	r0, r0, r1
	rsb	r3, r3, #24
	subs	r2, r3, r1
	movs	r3, #1
	lsls	r3, r3, r2
	ldr	r2, .L4455+20
	subs	r3, r3, #1
	ldrb	r1, [r2]	@ zero_extendqisi2
	ands	r0, r0, r3
	bl	__aeabi_uidiv
	ldr	r3, .L4455+24
	ldr	r3, [r3]
	add	r4, r3, r0, lsl #2
	ldrb	r2, [r4, #2]	@ zero_extendqisi2
	lsls	r1, r2, #28
	bpl	.L4344
	ldrh	r1, [r7]
	ldr	r7, .L4455+28
	adds	r1, r1, #8
	ldrh	r7, [r7]
	cmp	r1, r7
	bge	.L4344
	ldr	r1, .L4455+32
	bfc	r2, #3, #2
	strb	r2, [r4, #2]
	ldr	r2, [r3, r0, lsl #2]
	ldrh	r1, [r1]
	ldrh	r4, [r3, r0, lsl #2]
	ubfx	r2, r2, #11, #8
	muls	r1, r2, r1
	ubfx	r7, r4, #0, #11
	lsrs	r2, r2, #3
	add	r1, r1, r1, lsl #1
	add	r1, r7, r1, asr #2
	bfi	r4, r1, #0, #11
	strh	r4, [r3, r0, lsl #2]	@ movhi
	ldr	r1, [r3, r0, lsl #2]
	bfi	r1, r2, #11, #8
	str	r1, [r3, r0, lsl #2]
.L4344:
	ldr	r3, [r8]
	movs	r4, #0
	str	r4, [r6, #2184]
	strh	r4, [r6, #52]	@ movhi
	ldrh	r0, [r3, #80]
	bl	ftl_free_sblk
	ldr	r0, [r6, #8]
	movw	r3, #65535
	ldr	r2, [r8]
	ldr	r1, [r10]
	strh	r3, [r2, #80]	@ movhi
	strh	r3, [r1, #126]	@ movhi
	strh	r3, [r2, #130]	@ movhi
	cbz	r0, .L4347
	bl	zbuf_free
.L4347:
	str	r4, [r6, #8]
	bl	flt_sys_flush
	movw	r2, #3567
	ldr	r1, .L4455+36
	ldr	r0, .L4455+40
	strb	r4, [r5]
	bl	printf
	b	.L4359
.L4346:
	bl	ftl_mask_bad_block
	b	.L4344
.L4343:
	ldrh	r3, [r4, #86]
	ldrh	r2, [r6, #22]
	cmp	r3, #1
	ldrh	r3, [r6, #20]
	bls	.L4348
	cmp	r2, r3
	bcc	.L4337
	movs	r3, #1
	strb	r3, [r5]
	ldrh	r3, [r6, #52]
	adds	r2, r3, #1
	strh	r2, [r6, #52]	@ movhi
	add	r3, r6, r3, lsl #1
	ldrh	r2, [r6]
	strh	r2, [r3, #54]	@ movhi
	movw	r3, #65535
	strh	r3, [r6]	@ movhi
	b	.L4359
.L4348:
	cmp	r2, r3
	mov	r1, #5
	strb	r1, [r5]
	bcc	.L4349
	ldrh	r3, [r6, #52]
	adds	r2, r3, #1
	strh	r2, [r6, #52]	@ movhi
	add	r3, r6, r3, lsl #1
	ldrh	r2, [r6]
	strh	r2, [r3, #54]	@ movhi
	movw	r3, #65535
	strh	r3, [r6]	@ movhi
.L4349:
	bl	ftl_flush
	bl	sblk_wait_write_queue_completed
	bl	gc_write_completed
	ldr	r3, [r8]
	ldrh	r2, [r4, #80]
	strh	r2, [r3, #128]	@ movhi
	bl	pm_flush
	bl	ftl_ext_info_flush
	movs	r3, #0
	ldr	r2, .L4455+44
	strh	r3, [r6, #12]	@ movhi
	ldr	r3, .L4455+48
	ldrb	r2, [r2]	@ zero_extendqisi2
	ldrh	r3, [r3]
	strh	r3, [r6, #14]	@ movhi
	ldr	r3, .L4455+52
	ldrb	r3, [r3]	@ zero_extendqisi2
	strh	r3, [r6, #16]	@ movhi
	cbz	r2, .L4350
	ldr	r2, .L4455+56
	ldrh	r2, [r2]
	strh	r2, [r6, #14]	@ movhi
	movs	r2, #1
	strh	r2, [r6, #16]	@ movhi
.L4350:
	cmp	r3, #2
	bne	.L4352
	ldrh	r3, [r6, #14]
	lsls	r3, r3, #1
	strh	r3, [r6, #14]	@ movhi
	ldr	r3, .L4455+4
	ldrb	r3, [r3]	@ zero_extendqisi2
	cbnz	r3, .L4352
	movs	r3, #1
	strh	r3, [r6, #16]	@ movhi
.L4352:
	movs	r3, #0
	strh	r3, [r6, #18]	@ movhi
	b	.L4359
.L4355:
	ldrh	r2, [r4, #12]
	ldrh	r3, [r4, #14]
	cmp	r2, r3
	bcc	.L4356
	movs	r3, #6
	ldr	r0, [r4, #8]
	strb	r3, [r5]
	bl	zbuf_free
	str	r10, [r4, #8]
	b	.L4359
.L4356:
	cmp	r6, #15
	bls	.L4252
	ldr	r3, [sp, #32]
	cmp	r3, #1
	bne	.L4359
	adds	r7, r7, #1
	uxtb	r7, r7
	cmp	r7, #4
	bls	.L4252
	b	.L4359
.L4251:
	bl	gc_update_l2p_map_new
	bl	gc_free_src_blk
	bl	ftl_flush
	movw	r6, #65535
	bl	pm_flush
	strh	r6, [r4, #80]	@ movhi
	bl	ftl_ext_info_flush
	ldr	r3, .L4455+60
	movs	r0, #0
	ldr	r3, [r3]
	strh	r6, [r3, #126]	@ movhi
	bl	ftl_info_flush
.L4446:
	movs	r3, #0
	b	.L4445
.L4333:
	movw	r2, #3430
	ldr	r1, .L4455+36
	ldr	r0, .L4455+40
	bl	printf
	b	.L4358
.L4456:
	.align	2
.L4455:
	.word	.LANCHOR124
	.word	.LANCHOR80
	.word	1145785929
	.word	.LANCHOR74
	.word	.LANCHOR31
	.word	.LANCHOR75
	.word	.LANCHOR9
	.word	.LANCHOR98
	.word	.LANCHOR10
	.word	.LANCHOR237
	.word	.LC0
	.word	.LANCHOR35
	.word	.LANCHOR94
	.word	.LANCHOR78
	.word	.LANCHOR85
	.word	.LANCHOR110
	.size	zftl_do_gc, .-zftl_do_gc
	.section	.text.zftl_init,"ax",%progbits
	.align	1
	.global	zftl_init
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	zftl_init, %function
zftl_init:
	@ args = 0, pretend = 0, frame = 24
	@ frame_needed = 0, uses_anonymous_args = 0
	ldr	r2, .L4536
	movs	r3, #255
	push	{r4, r5, r6, r7, r8, r10, fp, lr}
	movs	r5, #0
	ldr	r7, .L4536+4
	sub	sp, sp, #24
	strb	r3, [r2]
	ldr	r2, .L4536+8
	ldr	r1, .L4536+12
	ldr	r0, .L4536+16
	strb	r5, [r2]
	ldr	r2, .L4536+20
	ldr	r6, .L4536+24
	strb	r3, [r2]
	ldr	r2, .L4536+28
	strb	r5, [r2]
	ldr	r2, .L4536+32
	strb	r3, [r2]
	mov	r2, #-1
	ldr	r3, .L4536+36
	strb	r5, [r3]
	ldr	r3, .L4536+40
	str	r2, [r3]
	bl	printf
	ldrb	r8, [r7, #12]	@ zero_extendqisi2
	ldr	r3, .L4536+44
	ldrb	fp, [r7, #9]	@ zero_extendqisi2
	mov	r1, r8
	strb	r8, [r3]
	ldr	r3, .L4536+48
	strb	fp, [r3]
	ldrh	r3, [r7, #10]
	str	r3, [sp]
	ldr	r3, .L4536+52
	ldrh	r2, [sp]
	ldr	r0, [sp]
	strh	r2, [r3]	@ movhi
	bl	__aeabi_idiv
	ldr	r2, .L4536+56
	mov	r3, r0
	ldr	r1, .L4536+60
	ldrh	r10, [r7, #14]
	ldrb	r4, [r2]	@ zero_extendqisi2
	ldr	r2, .L4536+64
	strh	r0, [r6]	@ movhi
	ldr	r0, .L4536+68
	strb	r4, [r2]
	ldrb	r2, [r7, #13]	@ zero_extendqisi2
	str	r6, [sp, #8]
	str	r0, [sp, #12]
	strb	r2, [r1]
	smulbb	r4, r4, r2
	ldr	r2, .L4536+72
	strh	r10, [r2]	@ movhi
	lsl	r2, fp, #9
	uxtb	r4, r4
	uxth	r2, r2
	strb	r4, [r0]
	str	r2, [sp, #4]
	ldr	r2, .L4536+76
	ldrh	r1, [sp, #4]
	strh	r1, [r2]	@ movhi
	ldr	r2, .L4536+80
	ldrh	r1, [r2]
	ldr	r2, .L4536+84
	strh	r1, [r2]	@ movhi
	movs	r2, #1
.L4458:
	cmp	r1, r2
	uxth	r0, r5
	add	r5, r5, #1
	bcs	.L4459
	ldr	r1, .L4536+88
	subs	r2, r0, #1
	movs	r6, #0
	movs	r5, #1
	strh	r2, [r1]	@ movhi
	ldr	r2, [sp]
	mul	r2, r2, fp
	mul	r0, r2, r10
	lsrs	r7, r0, #21
.L4460:
	cmp	r7, r5
	uxth	r1, r6
	add	r6, r6, #1
	bcs	.L4461
	mov	r5, #1892352
	subs	r1, r1, #1
	mul	r6, r5, r4
	uxth	r1, r1
	ldr	r7, .L4536+92
	lsr	r10, r10, #4
	muls	r0, r4, r0
	str	r2, [sp, #20]
	str	r3, [sp, #16]
	lsl	r5, r6, r1
	ldr	r1, .L4536+96
	add	r6, r5, #24576
	str	r0, [r7]
	str	r5, [r1]
	mov	r0, r6
	ldr	r1, .L4536+100
	str	r6, [r1]
	mov	r1, fp
	bl	__aeabi_uidiv
	ldr	r3, [sp, #4]
	ldr	r1, .L4536+104
	ldr	fp, .L4536+172
	add	ip, r3, #-1
	str	r0, [r1]
	add	r0, ip, r0, lsl #2
	mov	r1, r3
	bl	__aeabi_uidiv
	ldr	r3, [sp, #16]
	strh	r0, [fp]	@ movhi
	uxth	r0, r0
	lsls	r0, r0, #4
	mul	r1, r4, r3
	bl	__aeabi_idiv
	ldr	r2, [sp, #20]
	ldr	r3, .L4536+108
	mul	r1, r4, r2
	strh	r0, [r3]	@ movhi
	mov	r0, r6
	mov	r6, fp
	subs	r1, r1, #1
	bl	__aeabi_uidiv
	ldr	r3, .L4536+112
	adds	r0, r0, #8
	cmp	r10, #79
	ldr	ip, .L4536+212
	it	ls
	movls	r2, #80
	ldr	lr, .L4536+132
	strh	r0, [r3]	@ movhi
	mov	r1, #48
	ldr	r3, .L4536+116
	ldr	r0, .L4536+120
	strh	r10, [r3]	@ movhi
	it	ls
	strhls	r2, [r3]	@ movhi
	mov	r3, #2000
	strh	r3, [ip]	@ movhi
	movs	r3, #50
	strh	r3, [r0]	@ movhi
	mov	r2, #256
	ldr	r3, .L4536+124
	cmp	r8, #2
	mov	r8, r0
	strh	r2, [r3]	@ movhi
	ldr	r2, .L4536+128
	strh	r1, [r2]	@ movhi
	mov	r1, #32
	strh	r1, [lr]	@ movhi
	mov	r10, r2
	mov	lr, ip
	beq	.L4463
	ldr	fp, .L4536+216
	ldrb	fp, [fp]	@ zero_extendqisi2
	cmp	fp, #0
	beq	.L4464
.L4463:
	movs	r2, #150
	movs	r1, #12
	strh	r2, [r8]	@ movhi
	movs	r2, #64
	strh	r2, [r10]	@ movhi
	ldr	r2, .L4536+132
	strh	r1, [r2]	@ movhi
	ldr	r1, .L4536+136
	ldrb	r1, [r1]	@ zero_extendqisi2
	cbnz	r1, .L4465
	movs	r1, #4
	strh	r1, [r2]	@ movhi
	mov	r2, #600
	strh	r2, [lr]	@ movhi
	movs	r2, #128
	strh	r2, [r3]	@ movhi
.L4465:
	ldr	r3, .L4536+140
	ldrb	r3, [r3]	@ zero_extendqisi2
	cbz	r3, .L4467
	movs	r3, #200
	strh	r3, [r8]	@ movhi
	mov	r3, #2000
	strh	r3, [lr]	@ movhi
.L4467:
	ldr	r3, .L4536+144
	movs	r2, #0
	str	r2, [r3]
	movs	r2, #1
	ldr	r3, .L4536+148
	strb	r2, [r3]
	ldr	r2, [sp]
	muls	r4, r2, r4
	ldr	r2, [sp, #4]
	cmp	r2, r4, lsl #2
	ldr	r4, .L4536+152
	itt	lt
	movlt	r2, #2
	strblt	r2, [r3]
	ldr	r3, [r4]
	lsls	r3, r3, #19
	bpl	.L4470
	mov	r1, r5
	ldr	r0, .L4536+156
	bl	printf
.L4470:
	ldr	r3, [r4]
	lsls	r5, r3, #19
	bpl	.L4471
	ldr	r1, [r7]
	ldr	r0, .L4536+160
	bl	printf
.L4471:
	ldr	r3, [r4]
	lsls	r0, r3, #19
	bpl	.L4472
	ldr	r3, .L4536+104
	ldr	r0, .L4536+164
	ldr	r1, [r3]
	bl	printf
.L4472:
	ldr	r3, [r4]
	lsls	r1, r3, #19
	bpl	.L4473
	ldr	r3, .L4536+100
	ldr	r0, .L4536+168
	ldr	r1, [r3]
	bl	printf
.L4473:
	ldr	r3, [r4]
	lsls	r2, r3, #19
	bpl	.L4474
	ldr	r3, .L4536+172
	ldr	r0, .L4536+176
	ldrh	r1, [r3]
	bl	printf
.L4474:
	ldr	r3, [r4]
	ldr	r8, .L4536+76
	tst	r3, #4096
	beq	.L4475
	ldrh	r1, [r8]
	ldr	r0, .L4536+180
	bl	printf
.L4475:
	ldr	r3, [r4]
	lsls	r3, r3, #19
	bpl	.L4476
	ldr	r3, .L4536+108
	ldr	r0, .L4536+184
	ldrh	r1, [r3]
	bl	printf
.L4476:
	ldr	r3, [r4]
	lsls	r7, r3, #19
	bpl	.L4477
	ldr	r3, .L4536+116
	ldr	r0, .L4536+188
	ldrh	r1, [r3]
	bl	printf
.L4477:
	ldr	r3, [r4]
	lsls	r5, r3, #19
	bpl	.L4478
	ldr	r3, .L4536+112
	ldr	r0, .L4536+192
	ldrh	r1, [r3]
	bl	printf
.L4478:
	bl	zbuf_init
	mov	r0, #16384
	ldr	r5, .L4536+196
	bl	ftl_malloc
	ldr	r3, .L4536+200
	ldr	r7, .L4536+72
	str	r0, [r3]
	mov	r0, #16384
	bl	ftl_malloc
	str	r0, [r5]
	mov	r0, #16384
	bl	ftl_malloc
	ldr	r3, .L4536+204
	str	r0, [r3]
	movs	r0, #6
	ldrh	r3, [r7]
	muls	r0, r3, r0
	bl	ftl_malloc
	ldr	r3, .L4536+208
	ldr	r2, [sp, #12]
	b	.L4537
.L4538:
	.align	2
.L4536:
	.word	.LANCHOR65
	.word	.LANCHOR32
	.word	.LANCHOR66
	.word	.LC242
	.word	.LC101
	.word	.LANCHOR133
	.word	.LANCHOR94
	.word	.LANCHOR134
	.word	.LANCHOR182
	.word	.LANCHOR129
	.word	.LANCHOR238
	.word	.LANCHOR78
	.word	.LANCHOR131
	.word	.LANCHOR85
	.word	.LANCHOR23
	.word	.LANCHOR75
	.word	.LANCHOR112
	.word	.LANCHOR79
	.word	.LANCHOR8
	.word	.LANCHOR221
	.word	.LANCHOR2
	.word	.LANCHOR111
	.word	.LANCHOR74
	.word	.LANCHOR239
	.word	.LANCHOR67
	.word	.LANCHOR240
	.word	.LANCHOR128
	.word	.LANCHOR152
	.word	.LANCHOR101
	.word	.LANCHOR98
	.word	.LANCHOR125
	.word	.LANCHOR149
	.word	.LANCHOR150
	.word	.LANCHOR10
	.word	.LANCHOR0
	.word	.LANCHOR36
	.word	.LANCHOR122
	.word	.LANCHOR224
	.word	.LANCHOR19
	.word	.LC243
	.word	.LC244
	.word	.LC245
	.word	.LC246
	.word	.LANCHOR202
	.word	.LC247
	.word	.LC248
	.word	.LC249
	.word	.LC250
	.word	.LC251
	.word	.LANCHOR197
	.word	.LANCHOR192
	.word	.LANCHOR187
	.word	.LANCHOR4
	.word	.LANCHOR126
	.word	.LANCHOR83
.L4537:
	str	r0, [r3]
	ldr	r3, [sp, #8]
	ldrb	r0, [r2]	@ zero_extendqisi2
	ldrh	r3, [r3]
	muls	r0, r3, r0
	lsls	r0, r0, #2
	bl	ftl_malloc
	ldr	r3, .L4539
	ldr	r2, [r5]
	ldrh	r5, [r7]
	str	r0, [r3]
	ldr	r3, .L4539+4
	str	r2, [r3]
	ldr	r3, [sp, #8]
	ldrh	r1, [r3]
	ldr	r3, [sp, #12]
	ldrb	r0, [r3]	@ zero_extendqisi2
	muls	r0, r1, r0
	ldr	r1, .L4539+8
	add	r3, r2, r0, lsl #3
	str	r3, [r1]
	lsls	r1, r0, #1
	ldr	r0, [r4]
	add	r1, r1, r5, lsr #1
	ldr	r5, .L4539+12
	add	r1, r2, r1, lsl #2
	lsls	r0, r0, #19
	str	r1, [r5]
	bpl	.L4479
	ldr	r0, .L4539+16
	bl	printf
.L4479:
	ldr	r2, [sp, #8]
	ldr	r1, [sp, #12]
	ldrh	r3, [r7]
	ldrh	r2, [r2]
	ldrb	r7, [r1]	@ zero_extendqisi2
	muls	r7, r2, r7
	ldrh	r2, [r6]
	lsls	r6, r3, #2
	add	r7, r3, r7, lsl #2
	ldr	r3, [r4]
	add	r6, r6, r2, lsl #2
	lsls	r7, r7, #1
	lsls	r2, r3, #19
	add	r7, r7, #632
	add	r6, r6, #704
	bpl	.L4480
	ldrh	r3, [r8]
	mov	r2, r6
	mov	r1, r7
	ldr	r0, .L4539+20
	bl	printf
.L4480:
	ldrh	r3, [r8]
	cmp	r7, r3
	bhi	.L4481
	cmp	r6, r3
	bls	.L4482
.L4481:
.L4535:
	b	.L4535
.L4459:
	lsls	r2, r2, #1
	b	.L4458
.L4461:
	lsls	r5, r5, #1
	b	.L4460
.L4464:
	ldr	r3, .L4539+24
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L4467
	mov	r3, #1200
	strh	r1, [r0]	@ movhi
	strh	r3, [ip]	@ movhi
	strh	r1, [r2]	@ movhi
	b	.L4467
.L4482:
	bl	sblk_init
	bl	ftl_info_blk_init
	adds	r3, r0, #1
	beq	.L4457
	bl	ftl_ext_info_init
	bl	gc_init
	movs	r0, #1
	ldr	r4, .L4539+28
	bl	pm_init
	bl	lpa_rebuild_hash
	ldr	r0, [r5]
	movs	r1, #0
	adds	r0, r0, #16
	bl	ftl_open_sblk_recovery
	ldr	r0, [r5]
	add	r1, r0, #16
	adds	r0, r0, #48
	bl	ftl_open_sblk_recovery
	ldr	r2, [r4]
	ldr	r0, [r5]
	ldr	r3, [r2, #8]
	adds	r0, r0, #16
	adds	r3, r3, #16
	str	r3, [r2, #8]
	bl	ftl_info_data_recovery
	ldr	r0, [r5]
	adds	r0, r0, #48
	bl	ftl_info_data_recovery
	ldr	r0, [r5]
	adds	r0, r0, #80
	bl	ftl_info_data_recovery
	bl	gc_recovery
	bl	pm_flush
	movs	r0, #1
	bl	ftl_total_vpn_update
	ldr	r3, .L4539+32
	ldrb	r3, [r3]	@ zero_extendqisi2
	cbz	r3, .L4484
	ldr	r2, [r4]
	ldr	r3, [r2, #68]
	adds	r3, r3, #1
	str	r3, [r2, #68]
.L4484:
	bl	ftl_ext_info_flush
	movs	r0, #0
	bl	ftl_info_flush
	bl	print_ftl_debug_info
	ldr	r3, [r5]
	ldrh	r3, [r3, #124]
	cbnz	r3, .L4491
	ldr	r3, .L4539+36
	ldr	r2, .L4539+40
	ldrh	r3, [r3]
	ldrh	r2, [r2]
	add	r3, r3, r2
	cmp	r3, #7
	ble	.L4491
.L4487:
	movs	r0, #0
.L4457:
	add	sp, sp, #24
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r10, fp, pc}
.L4491:
	ldr	r6, .L4539+36
	mov	r4, #16384
.L4488:
	movs	r1, #1
	movs	r0, #0
	bl	zftl_do_gc
	movs	r1, #1
	mov	r0, r1
	bl	zftl_do_gc
	ldr	r3, [r5]
	ldrh	r2, [r3, #124]
	cbnz	r2, .L4486
	ldrh	r2, [r3, #80]
	movw	r3, #65535
	cmp	r2, r3
	bne	.L4486
	ldr	r2, .L4539+40
	ldrh	r3, [r6]
	ldrh	r2, [r2]
	add	r3, r3, r2
	cmp	r3, #7
	bgt	.L4487
.L4486:
	subs	r4, r4, #1
	bne	.L4488
	b	.L4487
.L4540:
	.align	2
.L4539:
	.word	.LANCHOR118
	.word	.LANCHOR117
	.word	.LANCHOR11
	.word	.LANCHOR12
	.word	.LC252
	.word	.LC253
	.word	.LANCHOR35
	.word	.LANCHOR110
	.word	.LANCHOR195
	.word	.LANCHOR103
	.word	.LANCHOR107
	.size	zftl_init, .-zftl_init
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
	bl	nand_flash_init
	mov	r4, r0
	cbnz	r0, .L4542
	bl	zftl_init
	mov	r4, r0
.L4542:
	bl	idb_init
	mov	r1, r4
	ldr	r0, .L4543
	bl	printf
	mov	r0, r4
	pop	{r4, pc}
.L4544:
	.align	2
.L4543:
	.word	.LC254
	.size	rk_ftl_init, .-rk_ftl_init
	.section	.text.zftl_write,"ax",%progbits
	.align	1
	.global	zftl_write
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	zftl_write, %function
zftl_write:
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, r8, r10, fp, lr}
	mov	r8, r3
	ldr	r3, .L4574
	sub	sp, sp, #24
	mov	r4, r0
	mov	r6, r1
	mov	r5, r2
	ldr	r3, [r3]
	lsls	r3, r3, #19
	bpl	.L4546
	ldr	r3, [r8]
	str	r3, [sp]
	mov	r3, r2
	mov	r2, r1
	mov	r1, r0
	ldr	r0, .L4574+4
	bl	printf
.L4546:
	cmp	r4, #0
	bne	.L4547
	ldr	r3, .L4574+8
	mov	r4, #24576
	ldr	r3, [r3]
.L4548:
	cmp	r3, r6
	bls	.L4566
	cmp	r3, r5
	bcc	.L4566
	adds	r2, r6, r5
	cmp	r3, r2
	bcc	.L4566
	ldr	fp, .L4574+36
	add	r4, r4, r6
	mov	r0, r4
	ldrb	r6, [fp]	@ zero_extendqisi2
	mov	r1, r6
	bl	__aeabi_uidiv
	mov	r10, r0
	subs	r0, r5, #1
	mov	r1, r6
	add	r0, r0, r4
	bl	__aeabi_uidiv
	sub	r6, r0, r10
	mov	r7, r10
	adds	r6, r6, #1
	str	r0, [sp, #12]
	str	fp, [sp, #16]
.L4550:
	cbnz	r6, .L4558
	bl	ftl_write_commit
	bl	ftl_flush
	movs	r1, #1
	mov	r0, r6
	bl	zftl_do_gc
	ldr	r3, .L4574+12
	ldr	r5, .L4574+16
	ldr	r4, .L4574+20
	ldr	r3, [r3]
	ldrh	r3, [r3, #124]
	cbnz	r3, .L4559
	ldrh	r3, [r5]
	ldrh	r2, [r4]
	add	r3, r3, r2
	cmp	r3, #11
	bgt	.L4561
.L4559:
	movs	r1, #1
	movs	r0, #0
.L4573:
	bl	zftl_do_gc
.L4561:
	ldrh	r3, [r5]
	ldrh	r2, [r4]
	add	r3, r3, r2
	cmp	r3, #7
	ble	.L4562
	movs	r0, #0
.L4545:
	add	sp, sp, #24
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r10, fp, pc}
.L4547:
	cmp	r4, #3
	bhi	.L4566
	lsls	r4, r4, #13
	mov	r3, #8192
	b	.L4548
.L4558:
	ldr	r3, .L4574+24
	ldrb	r3, [r3]	@ zero_extendqisi2
	cbz	r3, .L4551
	ldr	r3, .L4574+28
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, #2
	bhi	.L4551
	bl	ftl_write_commit
.L4551:
	movs	r0, #0
	bl	buf_alloc
	mov	fp, r0
	cbnz	r0, .L4552
	bl	ftl_write_commit
	b	.L4550
.L4552:
	ldr	r3, [sp, #16]
	movs	r2, #0
	strb	r2, [r0, #41]
	cmp	r7, r10
	ldrb	r2, [r3]	@ zero_extendqisi2
	strb	r2, [r0, #40]
	bne	.L4554
	mov	r1, r2
	mov	r0, r4
	str	r2, [sp, #20]
	bl	__aeabi_uidivmod
	ldr	r2, [sp, #20]
	uxtb	r1, r1
	strb	r1, [fp, #41]
	subs	r1, r2, r1
	uxtb	r1, r1
	cmp	r5, r1
	ite	cs
	strbcs	r1, [fp, #40]
	strbcc	r5, [fp, #40]
.L4556:
	ldrb	ip, [fp, #41]	@ zero_extendqisi2
	mov	r1, r8
	ldrb	r2, [fp, #40]	@ zero_extendqisi2
	subs	r6, r6, #1
	ldr	r0, [fp, #4]
	lsls	r2, r2, #9
	add	r0, r0, ip, lsl #9
	bl	ftl_memcpy
	ldr	r2, .L4574+32
	str	r7, [fp, #20]
	adds	r7, r7, #1
	ldr	r1, [r2]
	ldr	r2, [r1, #8]
	adds	r0, r2, #1
	str	r0, [r1, #8]
	mov	r0, fp
	str	r2, [fp, #16]
	bl	ftl_write_buf
	ldrb	r3, [fp, #40]	@ zero_extendqisi2
	add	r8, r8, r3, lsl #9
	b	.L4550
.L4554:
	ldr	r3, [sp, #12]
	cmp	r7, r3
	itttt	eq
	smulbbeq	r2, r7, r2
	addeq	r1, r4, r5
	subeq	r2, r1, r2
	strbeq	r2, [r0, #40]
	b	.L4556
.L4562:
	movs	r1, #1
	movs	r0, #0
	bl	zftl_do_gc
	movs	r1, #1
	mov	r0, r1
	b	.L4573
.L4566:
	mov	r0, #-1
	b	.L4545
.L4575:
	.align	2
.L4574:
	.word	.LANCHOR19
	.word	.LC255
	.word	.LANCHOR67
	.word	.LANCHOR12
	.word	.LANCHOR103
	.word	.LANCHOR107
	.word	.LANCHOR66
	.word	.LANCHOR57
	.word	.LANCHOR110
	.word	.LANCHOR131
	.size	zftl_write, .-zftl_write
	.section	.text.zftl_sys_write,"ax",%progbits
	.align	1
	.global	zftl_sys_write
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	zftl_sys_write, %function
zftl_sys_write:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	mov	r3, r2
	mov	r2, r1
	mov	r1, r0
	movs	r0, #2
	b	zftl_write
	.size	zftl_sys_write, .-zftl_sys_write
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
	mov	r1, r0
	movs	r0, #2
	b	zftl_write
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
	mov	r2, r1
	add	r1, r0, #512
	movs	r0, #2
	b	zftl_write
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
	cbnz	r0, .L4580
	mov	r3, r2
	mov	r2, r5
	bl	idb_write_data
.L4580:
	mov	r3, r5
	mov	r2, r4
	mov	r1, r7
	mov	r0, r6
	pop	{r4, r5, r6, r7, r8, lr}
	b	zftl_write
	.size	ftl_write, .-ftl_write
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
	add	r1, r0, #512
	movs	r0, #2
	b	zftl_write
	.size	ftl_vendor_write, .-ftl_vendor_write
	.section	.text.zftl_vendor_write,"ax",%progbits
	.align	1
	.global	zftl_vendor_write
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	zftl_vendor_write, %function
zftl_vendor_write:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	b	ftl_vendor_write
	.size	zftl_vendor_write, .-zftl_vendor_write
	.section	.text.zftl_discard,"ax",%progbits
	.align	1
	.global	zftl_discard
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	zftl_discard, %function
zftl_discard:
	@ args = 0, pretend = 0, frame = 24
	@ frame_needed = 0, uses_anonymous_args = 0
	ldr	r3, .L4633
	push	{r4, r5, r6, r7, r8, r10, fp, lr}
	mov	r4, r1
	sub	sp, sp, #32
	ldr	r3, [r3]
	cmp	r0, r3
	bcs	.L4606
	cmp	r1, r3
	bhi	.L4606
	adds	r2, r0, r1
	cmp	r3, r2
	bcc	.L4606
	ldr	r2, .L4633+4
	add	r7, r0, #24576
	ldr	r3, .L4633+8
	ldr	r0, [r2]
	ldr	r1, [r3]
	str	r3, [sp, #12]
	tst	r0, #4096
	str	r2, [sp, #16]
	add	r1, r1, r4
	str	r1, [r3]
	beq	.L4585
	movs	r3, #0
	mov	r2, r7
	str	r3, [sp]
	mov	r3, r4
	ldr	r0, .L4633+12
	bl	printf
.L4585:
	ldr	r8, .L4633+36
	ldr	r10, .L4633+40
	ldr	r3, [r8]
	ldr	r2, [r3, #8]
	str	r2, [sp, #8]
	adds	r2, r2, #1
	str	r2, [r3, #8]
	bl	ftl_write_commit
	bl	ftl_flush
	ldrb	r6, [r10]	@ zero_extendqisi2
	mov	r0, r7
	mov	r1, r6
	bl	__aeabi_uidiv
	mov	r1, r6
	mov	r5, r0
	mov	r0, r7
	bl	__aeabi_uidivmod
	mov	fp, r1
	cmp	r1, #0
	beq	.L4586
	subs	r6, r6, r1
	mov	r0, r5
	cmp	r6, r4
	it	cs
	movcs	r6, r4
	bl	lpa_hash_get_ppa
	str	r0, [sp, #24]
	adds	r0, r0, #1
	bne	.L4587
	movs	r2, #0
	add	r1, sp, #24
	mov	r0, r5
	bl	pm_log2phys
.L4587:
	ldr	r3, [sp, #24]
	adds	r3, r3, #1
	beq	.L4589
	movs	r0, #0
	bl	buf_alloc
	mov	r3, r0
	cbz	r0, .L4589
	ldr	r2, [sp, #8]
	movs	r1, #0
	str	r5, [r0, #20]
	strb	fp, [r0, #41]
	str	r2, [r0, #16]
	uxth	r2, r6
	strb	r6, [r0, #40]
	ldr	r0, [r0, #4]
	lsls	r2, r2, #9
	str	r3, [sp, #20]
	add	r0, r0, fp, lsl #9
	bl	ftl_memset
	ldr	r3, [sp, #20]
	mov	r0, r3
	bl	ftl_write_buf
	bl	ftl_write_commit
	ldr	r2, [r8]
	ldr	r3, [r2, #76]
	adds	r3, r3, #1
	str	r3, [r2, #76]
.L4589:
	uxth	r6, r6
	adds	r5, r5, #1
	subs	r4, r4, r6
.L4586:
	cbz	r4, .L4591
	bl	ftl_flush
.L4591:
	ldr	fp, .L4633+44
	mov	r3, #-1
	ldr	r6, .L4633+16
	str	r3, [sp, #28]
.L4592:
	ldrb	r3, [r10]	@ zero_extendqisi2
	cmp	r4, r3
	bcs	.L4597
	cmp	r4, #0
	beq	.L4599
	mov	r0, r5
	bl	lpa_hash_get_ppa
	str	r0, [sp, #24]
	adds	r0, r0, #1
	bne	.L4600
	movs	r2, #0
	add	r1, sp, #24
	mov	r0, r5
	bl	pm_log2phys
.L4600:
	ldr	r3, [sp, #24]
	adds	r3, r3, #1
	beq	.L4599
	movs	r0, #0
	bl	buf_alloc
	mov	r6, r0
	cbz	r0, .L4599
	movs	r3, #0
	str	r5, [r0, #20]
	strb	r3, [r0, #41]
	ldr	r3, [sp, #8]
	strb	r4, [r0, #40]
	str	r3, [r0, #16]
	ldrb	r3, [r10]	@ zero_extendqisi2
	cmp	r4, r3
	bcc	.L4602
	movw	r2, #1493
	ldr	r1, .L4633+20
	ldr	r0, .L4633+24
	bl	printf
.L4602:
	lsls	r2, r4, #9
	movs	r1, #0
	ldr	r0, [r6, #4]
	bl	ftl_memset
	mov	r0, r6
	bl	ftl_write_buf
	bl	ftl_write_commit
	ldr	r2, [r8]
	ldr	r3, [r2, #76]
	adds	r3, r3, #1
	str	r3, [r2, #76]
.L4599:
	ldr	r3, [sp, #12]
	ldr	r1, [r3]
	cmp	r1, #8192
	bls	.L4607
	ldr	r3, [sp, #16]
	ldr	r3, [r3]
	lsls	r3, r3, #19
	bpl	.L4603
	movs	r3, #0
	mov	r2, r7
	str	r3, [sp]
	mov	r3, r4
	ldr	r0, .L4633+12
	bl	printf
.L4603:
	ldr	r3, [sp, #12]
	movs	r4, #0
	str	r4, [r3]
	bl	flt_sys_flush
	ldr	r3, .L4633+28
	movs	r2, #1
	str	r2, [r3]
.L4607:
	movs	r0, #0
	b	.L4583
.L4597:
	mov	r0, r5
	bl	lpa_hash_get_ppa
	str	r0, [sp, #24]
	adds	r0, r0, #1
	beq	.L4593
	movs	r0, #0
	bl	buf_alloc
	mov	r3, r0
	cbz	r0, .L4595
	ldrb	r2, [r10]	@ zero_extendqisi2
	movs	r1, #0
	strb	r1, [r0, #41]
	str	r5, [r0, #20]
	strb	r2, [r0, #40]
	ldr	r0, [sp, #8]
	lsls	r2, r2, #9
	str	r3, [sp, #20]
	str	r0, [r3, #16]
	ldr	r0, [r3, #4]
	bl	ftl_memset
	ldr	r3, [sp, #20]
	mov	r0, r3
	bl	ftl_write_buf
	bl	ftl_write_commit
.L4632:
	ldr	r2, [r8]
	ldr	r3, [r2, #76]
	adds	r3, r3, #1
	str	r3, [r2, #76]
.L4595:
	ldrb	r3, [r10]	@ zero_extendqisi2
	adds	r5, r5, #1
	subs	r4, r4, r3
	b	.L4592
.L4593:
	movs	r2, #0
	add	r1, sp, #24
	mov	r0, r5
	bl	pm_log2phys
	ldr	r3, [sp, #24]
	adds	r3, r3, #1
	beq	.L4595
	add	r1, sp, #28
	movs	r2, #1
	mov	r0, r5
	bl	pm_log2phys
	ldrb	r3, [r6]	@ zero_extendqisi2
	ldrh	r2, [fp]
	rsb	r3, r3, #24
	subs	r0, r3, r2
	movs	r3, #1
	lsls	r3, r3, r0
	ldr	r0, [sp, #24]
	subs	r3, r3, #1
	lsrs	r0, r0, r2
	ldr	r2, .L4633+32
	ands	r0, r0, r3
	ldrb	r1, [r2]	@ zero_extendqisi2
	bl	__aeabi_uidiv
	uxth	r0, r0
	bl	ftl_vpn_decrement
	b	.L4632
.L4606:
	mov	r0, #-1
.L4583:
	add	sp, sp, #32
	@ sp needed
	pop	{r4, r5, r6, r7, r8, r10, fp, pc}
.L4634:
	.align	2
.L4633:
	.word	.LANCHOR67
	.word	.LANCHOR19
	.word	.LANCHOR241
	.word	.LC256
	.word	.LANCHOR31
	.word	.LANCHOR242
	.word	.LC0
	.word	.LANCHOR122
	.word	.LANCHOR75
	.word	.LANCHOR110
	.word	.LANCHOR131
	.word	.LANCHOR74
	.size	zftl_discard, .-zftl_discard
	.section	.text.ftl_discard,"ax",%progbits
	.align	1
	.global	ftl_discard
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	ftl_discard, %function
ftl_discard:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	mov	r0, r1
	mov	r1, r2
	b	zftl_discard
	.size	ftl_discard, .-ftl_discard
	.section	.text.dump_pm_blk,"ax",%progbits
	.align	1
	.global	dump_pm_blk
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	dump_pm_blk, %function
dump_pm_blk:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r3, r4, r5, r6, r7, lr}
	movs	r2, #4
	ldr	r4, .L4640
	movs	r5, #0
	movw	r7, #65535
	ldr	r0, .L4640+4
	ldr	r1, [r4]
	ldr	r6, .L4640+8
	ldrh	r3, [r1, #698]
	add	r1, r1, #704
	bl	rknand_print_hex
	ldr	r1, [r4]
	movs	r2, #2
	ldrh	r3, [r6]
	ldr	r0, .L4640+12
	add	r1, r1, #416
	bl	rknand_print_hex
.L4637:
	ldrh	r2, [r6]
	uxth	r3, r5
	cmp	r2, r3
	bhi	.L4639
	pop	{r3, r4, r5, r6, r7, pc}
.L4639:
	ldr	r2, [r4]
	uxth	r3, r5
	adds	r3, r3, #208
	ldrh	r0, [r2, r3, lsl #1]
	cmp	r0, r7
	beq	.L4638
	movs	r1, #0
	bl	ftl_sblk_dump
.L4638:
	adds	r5, r5, #1
	b	.L4637
.L4641:
	.align	2
.L4640:
	.word	.LANCHOR110
	.word	.LC257
	.word	.LANCHOR152
	.word	.LC258
	.size	dump_pm_blk, .-dump_pm_blk
	.global	g_pm_spare
	.global	pm_first_write
	.global	pm_force_gc
	.global	pm_gc_enable
	.global	pm_last_load_ram_id
	.global	pm_last_update_ram_id
	.global	pm_ram_info
	.global	sblk_gc_write_completed_queue_head
	.global	sblk_read_completed_queue_head
	.global	sblk_write_completed_queue_head
	.global	sblk_queue_head
	.global	slc_cache_sblk
	.global	xlc_data_sblk
	.global	slc_data_sblk
	.global	free_mix_sblk
	.global	free_xlc_sblk
	.global	free_slc_sblk
	.global	gp_data_xlc_data_head
	.global	gp_data_slc_data_head
	.global	gp_data_slc_cache_head
	.global	gp_free_mix_head
	.global	gp_free_xlc_head
	.global	gp_free_slc_head
	.global	gp_sblk_list_tbl
	.global	zftl_print_list_count
	.global	ftl_ext_info_first_write
	.global	ftl_sys_info_first_write
	.global	ftl_low_format_cur_blk
	.global	ftl_power_lost_flag
	.global	ftl_vpn_update_count
	.global	ftl_sblk_update_list_offset
	.global	ftl_sblk_update_list
	.global	ftl_sblk_vpn_update_id
	.global	ftl_sblk_lpa_tbl
	.global	ftl_sblk_vpn
	.global	gp_ftl_ext_info
	.global	gp_ftl_info
	.global	gp_blk_info
	.global	ftl_tmp_buffer
	.global	ftl_ext_info_data_buffer
	.global	ftl_info_data_buffer
	.global	ftl_tmp_spare
	.global	ftl_info_spare
	.global	g_ftl_info_blk
	.global	tlc_b05a_prog_tbl
	.global	tlc_prog_order
	.global	gc_des_ppa_tbl
	.global	gc_valid_page_ppa
	.global	gc_page_buf_id
	.global	gc_pre_ppa_tbl
	.global	gc_lpa_tbl
	.global	g_gc_info
	.global	gc_xlc_search_index
	.global	gc_xlc_data_index
	.global	gc_slc_cache_index
	.global	gc_slc_data_index
	.global	gc_free_slc_sblk_th
	.global	gc_slc_mode_vpn_th
	.global	gc_slc_mode_slc_vpn_th
	.global	gc_slc_mode_tlc_vpn_th
	.global	gc_tlc_mode_tlc_vpn_th
	.global	gc_tlc_mode_slc_vpn_th
	.global	gc_state
	.global	gc_mode
	.global	p_read_ahead_ext_buf
	.global	discard_sector_count
	.global	read_ahead_lpa
	.global	_ftl_gc_tag_page_num
	.global	read_buf_count
	.global	read_buf_head
	.global	write_commit_count
	.global	write_commit_head
	.global	write_buf_count
	.global	write_buf_head
	.global	ftl_flush_jiffies
	.global	lpa_hash
	.global	lpa_hash_index
	.global	_c_slc_to_xlc_ec_ratio
	.global	_c_mix_max_xlc_ec_count
	.global	_c_mix_max_slc_ec_count
	.global	_c_swl_xlc_gc_th
	.global	_c_swl_slc_gc_th
	.global	_gc_after_discard_en
	.global	_last_write_time
	.global	_last_read_time
	.global	_min_slc_super_block
	.global	_max_xlc_super_block
	.global	_c_max_pm_sblk
	.global	_c_ftl_pm_page_num
	.global	_c_totle_log_page
	.global	_c_totle_data_density
	.global	_c_user_data_density
	.global	_c_totle_phy_density
	.global	_c_ftl_block_addr_log2
	.global	_c_ftl_block_align_addr
	.global	_c_ftl_byte_pre_page
	.global	_c_ftl_nand_blks_per_die
	.global	_c_ftl_page_pre_slc_blk
	.global	_c_ftl_page_pre_blk
	.global	_c_ftl_blk_pre_plane
	.global	_c_ftl_nand_planes_num
	.global	_c_ftl_planes_per_die
	.global	_c_ftl_sec_per_page
	.global	_c_ftl_nand_die_num
	.global	_c_ftl_nand_type
	.global	zftl_debug
	.global	g_flash_blk_info
	.global	gp_flash_info
	.global	p_free_buf_head
	.global	free_buf_count
	.global	g_buf
	.global	nandc_ecc_sts
	.global	g_nandc_v6_master_info
	.global	nandc_randomizer_en
	.global	nandc_hw_seed
	.global	fill_spare_size
	.global	g_nandc_ecc_bits
	.global	g_nandc_tran_timeout
	.global	g_nandc_ver
	.global	gp_nandc
	.global	hy_f26_ref_value
	.global	sd15_tlc_rr
	.global	sd15_slc_rr
	.global	g_nand_para_info
	.global	gp_nand_para_info
	.global	g_nand_opt_para
	.global	g_msb_page_tbl
	.global	g_lsb_page_tbl
	.global	g_die_addr
	.global	g_die_cs_idx
	.global	IDByte
	.global	flash_read_retry
	.global	_c_ftl_cs_bits
	.global	g_maxRetryCount
	.global	g_maxRegNum
	.global	g_retryMode
	.global	g_flash_toggle_mode_en
	.global	g_flash_ymtc_3d_tlc_flag
	.global	g_flash_micron_3d_tlc_b16a
	.global	g_flash_micron_3d_tlc_b05a
	.global	g_flash_micron_3d_tlc_flag
	.global	g_flash_3d_mlc_flag
	.global	g_flash_3d_tlc_flag
	.global	g_flash_multi_page_prog_en
	.global	g_flash_multi_page_read_en
	.global	g_flash_interface_mode
	.global	g_idb_ecc_bits
	.global	g_idb_slc_mode_enable
	.global	g_one_pass_program
	.global	g_slc_mode_addr2
	.global	g_slc_mode_enable
	.global	g_flash_cur_mode
	.global	g_flash_six_addr
	.global	g_flash_slc_mode
	.global	g_slc_page_num
	.global	g_totle_phy_block
	.global	g_block_align_addr
	.global	g_flash_reversd_blks
	.global	g_nand_max_die
	.global	g_flash_tmp_spare_buffer
	.global	g_flash_tmp_page_buffer
	.global	g_flash_sys_spare_buffer
	.global	g_flash_spare_buffer
	.global	g_flash_page_buffer
	.section	.bss.IDByte,"aw",%nobits
	.align	2
	.set	.LANCHOR47,. + 0
	.type	IDByte, %object
	.size	IDByte, 32
IDByte:
	.space	32
	.section	.bss._c_ftl_blk_pre_plane,"aw",%nobits
	.align	1
	.set	.LANCHOR8,. + 0
	.type	_c_ftl_blk_pre_plane, %object
	.size	_c_ftl_blk_pre_plane, 2
_c_ftl_blk_pre_plane:
	.space	2
	.section	.bss._c_ftl_block_addr_log2,"aw",%nobits
	.align	1
	.set	.LANCHOR74,. + 0
	.type	_c_ftl_block_addr_log2, %object
	.size	_c_ftl_block_addr_log2, 2
_c_ftl_block_addr_log2:
	.space	2
	.section	.bss._c_ftl_block_align_addr,"aw",%nobits
	.align	1
	.set	.LANCHOR111,. + 0
	.type	_c_ftl_block_align_addr, %object
	.size	_c_ftl_block_align_addr, 2
_c_ftl_block_align_addr:
	.space	2
	.section	.bss._c_ftl_byte_pre_page,"aw",%nobits
	.align	1
	.set	.LANCHOR221,. + 0
	.type	_c_ftl_byte_pre_page, %object
	.size	_c_ftl_byte_pre_page, 2
_c_ftl_byte_pre_page:
	.space	2
	.section	.bss._c_ftl_cs_bits,"aw",%nobits
	.set	.LANCHOR31,. + 0
	.type	_c_ftl_cs_bits, %object
	.size	_c_ftl_cs_bits, 1
_c_ftl_cs_bits:
	.space	1
	.section	.bss._c_ftl_nand_blks_per_die,"aw",%nobits
	.align	1
	.type	_c_ftl_nand_blks_per_die, %object
	.size	_c_ftl_nand_blks_per_die, 2
_c_ftl_nand_blks_per_die:
	.space	2
	.section	.bss._c_ftl_nand_die_num,"aw",%nobits
	.set	.LANCHOR112,. + 0
	.type	_c_ftl_nand_die_num, %object
	.size	_c_ftl_nand_die_num, 1
_c_ftl_nand_die_num:
	.space	1
	.section	.bss._c_ftl_nand_planes_num,"aw",%nobits
	.set	.LANCHOR79,. + 0
	.type	_c_ftl_nand_planes_num, %object
	.size	_c_ftl_nand_planes_num, 1
_c_ftl_nand_planes_num:
	.space	1
	.section	.bss._c_ftl_nand_type,"aw",%nobits
	.set	.LANCHOR78,. + 0
	.type	_c_ftl_nand_type, %object
	.size	_c_ftl_nand_type, 1
_c_ftl_nand_type:
	.space	1
	.section	.bss._c_ftl_page_pre_blk,"aw",%nobits
	.align	1
	.set	.LANCHOR85,. + 0
	.type	_c_ftl_page_pre_blk, %object
	.size	_c_ftl_page_pre_blk, 2
_c_ftl_page_pre_blk:
	.space	2
	.section	.bss._c_ftl_page_pre_slc_blk,"aw",%nobits
	.align	1
	.set	.LANCHOR94,. + 0
	.type	_c_ftl_page_pre_slc_blk, %object
	.size	_c_ftl_page_pre_slc_blk, 2
_c_ftl_page_pre_slc_blk:
	.space	2
	.section	.bss._c_ftl_planes_per_die,"aw",%nobits
	.set	.LANCHOR75,. + 0
	.type	_c_ftl_planes_per_die, %object
	.size	_c_ftl_planes_per_die, 1
_c_ftl_planes_per_die:
	.space	1
	.section	.bss._c_ftl_pm_page_num,"aw",%nobits
	.align	1
	.set	.LANCHOR202,. + 0
	.type	_c_ftl_pm_page_num, %object
	.size	_c_ftl_pm_page_num, 2
_c_ftl_pm_page_num:
	.space	2
	.section	.bss._c_ftl_sec_per_page,"aw",%nobits
	.set	.LANCHOR131,. + 0
	.type	_c_ftl_sec_per_page, %object
	.size	_c_ftl_sec_per_page, 1
_c_ftl_sec_per_page:
	.space	1
	.section	.bss._c_max_pm_sblk,"aw",%nobits
	.align	1
	.set	.LANCHOR152,. + 0
	.type	_c_max_pm_sblk, %object
	.size	_c_max_pm_sblk, 2
_c_max_pm_sblk:
	.space	2
	.section	.bss._c_mix_max_slc_ec_count,"aw",%nobits
	.align	1
	.set	.LANCHOR126,. + 0
	.type	_c_mix_max_slc_ec_count, %object
	.size	_c_mix_max_slc_ec_count, 2
_c_mix_max_slc_ec_count:
	.space	2
	.section	.bss._c_mix_max_xlc_ec_count,"aw",%nobits
	.align	1
	.set	.LANCHOR125,. + 0
	.type	_c_mix_max_xlc_ec_count, %object
	.size	_c_mix_max_xlc_ec_count, 2
_c_mix_max_xlc_ec_count:
	.space	2
	.section	.bss._c_slc_to_xlc_ec_ratio,"aw",%nobits
	.align	1
	.set	.LANCHOR10,. + 0
	.type	_c_slc_to_xlc_ec_ratio, %object
	.size	_c_slc_to_xlc_ec_ratio, 2
_c_slc_to_xlc_ec_ratio:
	.space	2
	.section	.bss._c_swl_slc_gc_th,"aw",%nobits
	.align	1
	.set	.LANCHOR149,. + 0
	.type	_c_swl_slc_gc_th, %object
	.size	_c_swl_slc_gc_th, 2
_c_swl_slc_gc_th:
	.space	2
	.section	.bss._c_swl_xlc_gc_th,"aw",%nobits
	.align	1
	.set	.LANCHOR150,. + 0
	.type	_c_swl_xlc_gc_th, %object
	.size	_c_swl_xlc_gc_th, 2
_c_swl_xlc_gc_th:
	.space	2
	.section	.bss._c_totle_data_density,"aw",%nobits
	.align	2
	.set	.LANCHOR240,. + 0
	.type	_c_totle_data_density, %object
	.size	_c_totle_data_density, 4
_c_totle_data_density:
	.space	4
	.section	.bss._c_totle_log_page,"aw",%nobits
	.align	2
	.set	.LANCHOR128,. + 0
	.type	_c_totle_log_page, %object
	.size	_c_totle_log_page, 4
_c_totle_log_page:
	.space	4
	.section	.bss._c_totle_phy_density,"aw",%nobits
	.align	2
	.set	.LANCHOR239,. + 0
	.type	_c_totle_phy_density, %object
	.size	_c_totle_phy_density, 4
_c_totle_phy_density:
	.space	4
	.section	.bss._c_user_data_density,"aw",%nobits
	.align	2
	.set	.LANCHOR67,. + 0
	.type	_c_user_data_density, %object
	.size	_c_user_data_density, 4
_c_user_data_density:
	.space	4
	.section	.bss._ftl_gc_tag_page_num,"aw",%nobits
	.set	.LANCHOR224,. + 0
	.type	_ftl_gc_tag_page_num, %object
	.size	_ftl_gc_tag_page_num, 1
_ftl_gc_tag_page_num:
	.space	1
	.section	.bss._gc_after_discard_en,"aw",%nobits
	.align	2
	.set	.LANCHOR122,. + 0
	.type	_gc_after_discard_en, %object
	.size	_gc_after_discard_en, 4
_gc_after_discard_en:
	.space	4
	.section	.bss._last_read_time,"aw",%nobits
	.align	2
	.type	_last_read_time, %object
	.size	_last_read_time, 4
_last_read_time:
	.space	4
	.section	.bss._last_write_time,"aw",%nobits
	.align	2
	.type	_last_write_time, %object
	.size	_last_write_time, 4
_last_write_time:
	.space	4
	.section	.bss._max_xlc_super_block,"aw",%nobits
	.align	1
	.set	.LANCHOR101,. + 0
	.type	_max_xlc_super_block, %object
	.size	_max_xlc_super_block, 2
_max_xlc_super_block:
	.space	2
	.section	.bss._min_slc_super_block,"aw",%nobits
	.align	1
	.set	.LANCHOR98,. + 0
	.type	_min_slc_super_block, %object
	.size	_min_slc_super_block, 2
_min_slc_super_block:
	.space	2
	.section	.bss.discard_sector_count,"aw",%nobits
	.align	2
	.set	.LANCHOR241,. + 0
	.type	discard_sector_count, %object
	.size	discard_sector_count, 4
discard_sector_count:
	.space	4
	.section	.bss.fill_spare_size,"aw",%nobits
	.align	1
	.set	.LANCHOR53,. + 0
	.type	fill_spare_size, %object
	.size	fill_spare_size, 2
fill_spare_size:
	.space	2
	.section	.bss.flash_ddr_tuning_sdr_read_count,"aw",%nobits
	.align	2
	.set	.LANCHOR169,. + 0
	.type	flash_ddr_tuning_sdr_read_count, %object
	.size	flash_ddr_tuning_sdr_read_count, 4
flash_ddr_tuning_sdr_read_count:
	.space	4
	.section	.bss.flash_read_retry,"aw",%nobits
	.align	2
	.set	.LANCHOR171,. + 0
	.type	flash_read_retry, %object
	.size	flash_read_retry, 4
flash_read_retry:
	.space	4
	.section	.bss.free_buf_count,"aw",%nobits
	.set	.LANCHOR57,. + 0
	.type	free_buf_count, %object
	.size	free_buf_count, 1
free_buf_count:
	.space	1
	.section	.bss.free_mix_sblk,"aw",%nobits
	.align	1
	.set	.LANCHOR107,. + 0
	.type	free_mix_sblk, %object
	.size	free_mix_sblk, 2
free_mix_sblk:
	.space	2
	.section	.bss.free_slc_sblk,"aw",%nobits
	.align	1
	.set	.LANCHOR103,. + 0
	.type	free_slc_sblk, %object
	.size	free_slc_sblk, 2
free_slc_sblk:
	.space	2
	.section	.bss.free_xlc_sblk,"aw",%nobits
	.align	1
	.set	.LANCHOR105,. + 0
	.type	free_xlc_sblk, %object
	.size	free_xlc_sblk, 2
free_xlc_sblk:
	.space	2
	.section	.bss.ftl_ext_info_data_buffer,"aw",%nobits
	.align	2
	.set	.LANCHOR197,. + 0
	.type	ftl_ext_info_data_buffer, %object
	.size	ftl_ext_info_data_buffer, 4
ftl_ext_info_data_buffer:
	.space	4
	.section	.bss.ftl_ext_info_first_write,"aw",%nobits
	.set	.LANCHOR196,. + 0
	.type	ftl_ext_info_first_write, %object
	.size	ftl_ext_info_first_write, 1
ftl_ext_info_first_write:
	.space	1
	.section	.bss.ftl_flush_jiffies,"aw",%nobits
	.align	2
	.set	.LANCHOR233,. + 0
	.type	ftl_flush_jiffies, %object
	.size	ftl_flush_jiffies, 4
ftl_flush_jiffies:
	.space	4
	.section	.bss.ftl_info_data_buffer,"aw",%nobits
	.align	2
	.set	.LANCHOR192,. + 0
	.type	ftl_info_data_buffer, %object
	.size	ftl_info_data_buffer, 4
ftl_info_data_buffer:
	.space	4
	.section	.bss.ftl_info_spare,"aw",%nobits
	.align	6
	.set	.LANCHOR190,. + 0
	.type	ftl_info_spare, %object
	.size	ftl_info_spare, 256
ftl_info_spare:
	.space	256
	.section	.bss.ftl_low_format_cur_blk,"aw",%nobits
	.align	1
	.set	.LANCHOR68,. + 0
	.type	ftl_low_format_cur_blk, %object
	.size	ftl_low_format_cur_blk, 2
ftl_low_format_cur_blk:
	.space	2
	.section	.bss.ftl_power_lost_flag,"aw",%nobits
	.set	.LANCHOR195,. + 0
	.type	ftl_power_lost_flag, %object
	.size	ftl_power_lost_flag, 1
ftl_power_lost_flag:
	.space	1
	.section	.bss.ftl_sblk_lpa_tbl,"aw",%nobits
	.align	2
	.set	.LANCHOR117,. + 0
	.type	ftl_sblk_lpa_tbl, %object
	.size	ftl_sblk_lpa_tbl, 4
ftl_sblk_lpa_tbl:
	.space	4
	.section	.bss.ftl_sblk_update_list,"aw",%nobits
	.align	1
	.set	.LANCHOR73,. + 0
	.type	ftl_sblk_update_list, %object
	.size	ftl_sblk_update_list, 16
ftl_sblk_update_list:
	.space	16
	.section	.bss.ftl_sblk_update_list_offset,"aw",%nobits
	.align	1
	.set	.LANCHOR123,. + 0
	.type	ftl_sblk_update_list_offset, %object
	.size	ftl_sblk_update_list_offset, 2
ftl_sblk_update_list_offset:
	.space	2
	.section	.bss.ftl_sblk_vpn,"aw",%nobits
	.align	2
	.set	.LANCHOR11,. + 0
	.type	ftl_sblk_vpn, %object
	.size	ftl_sblk_vpn, 4
ftl_sblk_vpn:
	.space	4
	.section	.bss.ftl_sblk_vpn_update_id,"aw",%nobits
	.align	1
	.set	.LANCHOR72,. + 0
	.type	ftl_sblk_vpn_update_id, %object
	.size	ftl_sblk_vpn_update_id, 2
ftl_sblk_vpn_update_id:
	.space	2
	.section	.bss.ftl_sys_info_first_write,"aw",%nobits
	.set	.LANCHOR194,. + 0
	.type	ftl_sys_info_first_write, %object
	.size	ftl_sys_info_first_write, 1
ftl_sys_info_first_write:
	.space	1
	.section	.bss.ftl_tmp_buffer,"aw",%nobits
	.align	2
	.set	.LANCHOR187,. + 0
	.type	ftl_tmp_buffer, %object
	.size	ftl_tmp_buffer, 4
ftl_tmp_buffer:
	.space	4
	.section	.bss.ftl_tmp_spare,"aw",%nobits
	.align	6
	.set	.LANCHOR188,. + 0
	.type	ftl_tmp_spare, %object
	.size	ftl_tmp_spare, 256
ftl_tmp_spare:
	.space	256
	.section	.bss.ftl_vpn_update_count,"aw",%nobits
	.align	1
	.set	.LANCHOR121,. + 0
	.type	ftl_vpn_update_count, %object
	.size	ftl_vpn_update_count, 2
ftl_vpn_update_count:
	.space	2
	.section	.bss.g_block_align_addr,"aw",%nobits
	.align	1
	.set	.LANCHOR2,. + 0
	.type	g_block_align_addr, %object
	.size	g_block_align_addr, 2
g_block_align_addr:
	.space	2
	.section	.bss.g_buf,"aw",%nobits
	.align	2
	.set	.LANCHOR55,. + 0
	.type	g_buf, %object
	.size	g_buf, 1536
g_buf:
	.space	1536
	.section	.bss.g_die_addr,"aw",%nobits
	.align	2
	.set	.LANCHOR145,. + 0
	.type	g_die_addr, %object
	.size	g_die_addr, 32
g_die_addr:
	.space	32
	.section	.bss.g_die_cs_idx,"aw",%nobits
	.align	2
	.set	.LANCHOR29,. + 0
	.type	g_die_cs_idx, %object
	.size	g_die_cs_idx, 8
g_die_cs_idx:
	.space	8
	.section	.bss.g_flash_3d_mlc_flag,"aw",%nobits
	.set	.LANCHOR80,. + 0
	.type	g_flash_3d_mlc_flag, %object
	.size	g_flash_3d_mlc_flag, 1
g_flash_3d_mlc_flag:
	.space	1
	.section	.bss.g_flash_3d_tlc_flag,"aw",%nobits
	.set	.LANCHOR83,. + 0
	.type	g_flash_3d_tlc_flag, %object
	.size	g_flash_3d_tlc_flag, 1
g_flash_3d_tlc_flag:
	.space	1
	.section	.bss.g_flash_blk_info,"aw",%nobits
	.align	1
	.set	.LANCHOR211,. + 0
	.type	g_flash_blk_info, %object
	.size	g_flash_blk_info, 4
g_flash_blk_info:
	.space	4
	.section	.bss.g_flash_cur_mode,"aw",%nobits
	.set	.LANCHOR33,. + 0
	.type	g_flash_cur_mode, %object
	.size	g_flash_cur_mode, 4
g_flash_cur_mode:
	.space	4
	.section	.bss.g_flash_interface_mode,"aw",%nobits
	.set	.LANCHOR48,. + 0
	.type	g_flash_interface_mode, %object
	.size	g_flash_interface_mode, 1
g_flash_interface_mode:
	.space	1
	.section	.bss.g_flash_micron_3d_tlc_b05a,"aw",%nobits
	.set	.LANCHOR124,. + 0
	.type	g_flash_micron_3d_tlc_b05a, %object
	.size	g_flash_micron_3d_tlc_b05a, 1
g_flash_micron_3d_tlc_b05a:
	.space	1
	.section	.bss.g_flash_micron_3d_tlc_b16a,"aw",%nobits
	.set	.LANCHOR217,. + 0
	.type	g_flash_micron_3d_tlc_b16a, %object
	.size	g_flash_micron_3d_tlc_b16a, 1
g_flash_micron_3d_tlc_b16a:
	.space	1
	.section	.bss.g_flash_micron_3d_tlc_flag,"aw",%nobits
	.set	.LANCHOR35,. + 0
	.type	g_flash_micron_3d_tlc_flag, %object
	.size	g_flash_micron_3d_tlc_flag, 1
g_flash_micron_3d_tlc_flag:
	.space	1
	.section	.bss.g_flash_multi_page_prog_en,"aw",%nobits
	.set	.LANCHOR44,. + 0
	.type	g_flash_multi_page_prog_en, %object
	.size	g_flash_multi_page_prog_en, 1
g_flash_multi_page_prog_en:
	.space	1
	.section	.bss.g_flash_multi_page_read_en,"aw",%nobits
	.set	.LANCHOR183,. + 0
	.type	g_flash_multi_page_read_en, %object
	.size	g_flash_multi_page_read_en, 1
g_flash_multi_page_read_en:
	.space	1
	.section	.bss.g_flash_page_buffer,"aw",%nobits
	.align	2
	.set	.LANCHOR173,. + 0
	.type	g_flash_page_buffer, %object
	.size	g_flash_page_buffer, 4
g_flash_page_buffer:
	.space	4
	.section	.bss.g_flash_reversd_blks,"aw",%nobits
	.set	.LANCHOR216,. + 0
	.type	g_flash_reversd_blks, %object
	.size	g_flash_reversd_blks, 1
g_flash_reversd_blks:
	.space	1
	.section	.bss.g_flash_six_addr,"aw",%nobits
	.set	.LANCHOR30,. + 0
	.type	g_flash_six_addr, %object
	.size	g_flash_six_addr, 1
g_flash_six_addr:
	.space	1
	.section	.bss.g_flash_slc_mode,"aw",%nobits
	.set	.LANCHOR0,. + 0
	.type	g_flash_slc_mode, %object
	.size	g_flash_slc_mode, 1
g_flash_slc_mode:
	.space	1
	.section	.bss.g_flash_spare_buffer,"aw",%nobits
	.align	2
	.set	.LANCHOR172,. + 0
	.type	g_flash_spare_buffer, %object
	.size	g_flash_spare_buffer, 4
g_flash_spare_buffer:
	.space	4
	.section	.bss.g_flash_sys_spare_buffer,"aw",%nobits
	.align	2
	.set	.LANCHOR210,. + 0
	.type	g_flash_sys_spare_buffer, %object
	.size	g_flash_sys_spare_buffer, 4
g_flash_sys_spare_buffer:
	.space	4
	.section	.bss.g_flash_tmp_page_buffer,"aw",%nobits
	.align	2
	.set	.LANCHOR163,. + 0
	.type	g_flash_tmp_page_buffer, %object
	.size	g_flash_tmp_page_buffer, 4
g_flash_tmp_page_buffer:
	.space	4
	.section	.bss.g_flash_tmp_spare_buffer,"aw",%nobits
	.align	2
	.set	.LANCHOR165,. + 0
	.type	g_flash_tmp_spare_buffer, %object
	.size	g_flash_tmp_spare_buffer, 4
g_flash_tmp_spare_buffer:
	.space	4
	.section	.bss.g_flash_toggle_mode_en,"aw",%nobits
	.set	.LANCHOR26,. + 0
	.type	g_flash_toggle_mode_en, %object
	.size	g_flash_toggle_mode_en, 1
g_flash_toggle_mode_en:
	.space	1
	.section	.bss.g_flash_ymtc_3d_tlc_flag,"aw",%nobits
	.set	.LANCHOR36,. + 0
	.type	g_flash_ymtc_3d_tlc_flag, %object
	.size	g_flash_ymtc_3d_tlc_flag, 1
g_flash_ymtc_3d_tlc_flag:
	.space	1
	.section	.bss.g_ftl_info_blk,"aw",%nobits
	.align	6
	.set	.LANCHOR191,. + 0
	.type	g_ftl_info_blk, %object
	.size	g_ftl_info_blk, 4
g_ftl_info_blk:
	.space	4
	.section	.bss.g_gc_info,"aw",%nobits
	.align	2
	.set	.LANCHOR70,. + 0
	.type	g_gc_info, %object
	.size	g_gc_info, 2204
g_gc_info:
	.space	2204
	.section	.bss.g_idb_ecc_bits,"aw",%nobits
	.set	.LANCHOR22,. + 0
	.type	g_idb_ecc_bits, %object
	.size	g_idb_ecc_bits, 1
g_idb_ecc_bits:
	.space	1
	.section	.bss.g_idb_slc_mode_enable,"aw",%nobits
	.set	.LANCHOR24,. + 0
	.type	g_idb_slc_mode_enable, %object
	.size	g_idb_slc_mode_enable, 1
g_idb_slc_mode_enable:
	.space	1
	.section	.bss.g_lsb_page_tbl,"aw",%nobits
	.align	2
	.set	.LANCHOR3,. + 0
	.type	g_lsb_page_tbl, %object
	.size	g_lsb_page_tbl, 1024
g_lsb_page_tbl:
	.space	1024
	.section	.bss.g_maxRegNum,"aw",%nobits
	.set	.LANCHOR18,. + 0
	.type	g_maxRegNum, %object
	.size	g_maxRegNum, 1
g_maxRegNum:
	.space	1
	.section	.bss.g_maxRetryCount,"aw",%nobits
	.set	.LANCHOR166,. + 0
	.type	g_maxRetryCount, %object
	.size	g_maxRetryCount, 1
g_maxRetryCount:
	.space	1
	.section	.bss.g_msb_page_tbl,"aw",%nobits
	.align	2
	.set	.LANCHOR142,. + 0
	.type	g_msb_page_tbl, %object
	.size	g_msb_page_tbl, 2048
g_msb_page_tbl:
	.space	2048
	.section	.bss.g_nand_max_die,"aw",%nobits
	.set	.LANCHOR23,. + 0
	.type	g_nand_max_die, %object
	.size	g_nand_max_die, 1
g_nand_max_die:
	.space	1
	.section	.bss.g_nand_opt_para,"aw",%nobits
	.set	.LANCHOR25,. + 0
	.type	g_nand_opt_para, %object
	.size	g_nand_opt_para, 32
g_nand_opt_para:
	.space	32
	.section	.bss.g_nandc_ecc_bits,"aw",%nobits
	.set	.LANCHOR49,. + 0
	.type	g_nandc_ecc_bits, %object
	.size	g_nandc_ecc_bits, 1
g_nandc_ecc_bits:
	.space	1
	.section	.bss.g_nandc_tran_timeout,"aw",%nobits
	.set	.LANCHOR164,. + 0
	.type	g_nandc_tran_timeout, %object
	.size	g_nandc_tran_timeout, 1
g_nandc_tran_timeout:
	.space	1
	.section	.bss.g_nandc_v6_master_info,"aw",%nobits
	.align	2
	.set	.LANCHOR52,. + 0
	.type	g_nandc_v6_master_info, %object
	.size	g_nandc_v6_master_info, 28
g_nandc_v6_master_info:
	.space	28
	.section	.bss.g_nandc_ver,"aw",%nobits
	.set	.LANCHOR27,. + 0
	.type	g_nandc_ver, %object
	.size	g_nandc_ver, 1
g_nandc_ver:
	.space	1
	.section	.bss.g_one_pass_program,"aw",%nobits
	.set	.LANCHOR81,. + 0
	.type	g_one_pass_program, %object
	.size	g_one_pass_program, 1
g_one_pass_program:
	.space	1
	.section	.bss.g_pm_spare,"aw",%nobits
	.align	2
	.set	.LANCHOR207,. + 0
	.type	g_pm_spare, %object
	.size	g_pm_spare, 4
g_pm_spare:
	.space	4
	.section	.bss.g_retryMode,"aw",%nobits
	.set	.LANCHOR15,. + 0
	.type	g_retryMode, %object
	.size	g_retryMode, 1
g_retryMode:
	.space	1
	.section	.bss.g_slc_mode_addr2,"aw",%nobits
	.set	.LANCHOR1,. + 0
	.type	g_slc_mode_addr2, %object
	.size	g_slc_mode_addr2, 1
g_slc_mode_addr2:
	.space	1
	.section	.bss.g_slc_mode_enable,"aw",%nobits
	.type	g_slc_mode_enable, %object
	.size	g_slc_mode_enable, 1
g_slc_mode_enable:
	.space	1
	.section	.bss.g_slc_page_num,"aw",%nobits
	.align	1
	.set	.LANCHOR144,. + 0
	.type	g_slc_page_num, %object
	.size	g_slc_page_num, 2
g_slc_page_num:
	.space	2
	.section	.bss.g_totle_phy_block,"aw",%nobits
	.align	1
	.set	.LANCHOR146,. + 0
	.type	g_totle_phy_block, %object
	.size	g_totle_phy_block, 2
g_totle_phy_block:
	.space	2
	.section	.bss.gc_des_ppa_tbl,"aw",%nobits
	.align	2
	.set	.LANCHOR161,. + 0
	.type	gc_des_ppa_tbl, %object
	.size	gc_des_ppa_tbl, 4
gc_des_ppa_tbl:
	.space	4
	.section	.bss.gc_free_slc_sblk_th,"aw",%nobits
	.align	1
	.set	.LANCHOR86,. + 0
	.type	gc_free_slc_sblk_th, %object
	.size	gc_free_slc_sblk_th, 2
gc_free_slc_sblk_th:
	.space	2
	.section	.bss.gc_lpa_tbl,"aw",%nobits
	.align	2
	.set	.LANCHOR159,. + 0
	.type	gc_lpa_tbl, %object
	.size	gc_lpa_tbl, 4
gc_lpa_tbl:
	.space	4
	.section	.bss.gc_mode,"aw",%nobits
	.set	.LANCHOR84,. + 0
	.type	gc_mode, %object
	.size	gc_mode, 1
gc_mode:
	.space	1
	.section	.bss.gc_page_buf_id,"aw",%nobits
	.align	2
	.set	.LANCHOR82,. + 0
	.type	gc_page_buf_id, %object
	.size	gc_page_buf_id, 4
gc_page_buf_id:
	.space	4
	.section	.bss.gc_pre_ppa_tbl,"aw",%nobits
	.align	2
	.set	.LANCHOR160,. + 0
	.type	gc_pre_ppa_tbl, %object
	.size	gc_pre_ppa_tbl, 4
gc_pre_ppa_tbl:
	.space	4
	.section	.bss.gc_search_count,"aw",%nobits
	.align	2
	.set	.LANCHOR157,. + 0
	.type	gc_search_count, %object
	.size	gc_search_count, 4
gc_search_count:
	.space	4
	.section	.bss.gc_slc_cache_index,"aw",%nobits
	.align	1
	.set	.LANCHOR88,. + 0
	.type	gc_slc_cache_index, %object
	.size	gc_slc_cache_index, 2
gc_slc_cache_index:
	.space	2
	.section	.bss.gc_slc_data_index,"aw",%nobits
	.align	1
	.set	.LANCHOR87,. + 0
	.type	gc_slc_data_index, %object
	.size	gc_slc_data_index, 2
gc_slc_data_index:
	.space	2
	.section	.bss.gc_slc_mode_slc_vpn_th,"aw",%nobits
	.align	1
	.set	.LANCHOR158,. + 0
	.type	gc_slc_mode_slc_vpn_th, %object
	.size	gc_slc_mode_slc_vpn_th, 2
gc_slc_mode_slc_vpn_th:
	.space	2
	.section	.bss.gc_slc_mode_tlc_vpn_th,"aw",%nobits
	.align	1
	.set	.LANCHOR93,. + 0
	.type	gc_slc_mode_tlc_vpn_th, %object
	.size	gc_slc_mode_tlc_vpn_th, 2
gc_slc_mode_tlc_vpn_th:
	.space	2
	.section	.bss.gc_slc_mode_vpn_th,"aw",%nobits
	.align	1
	.set	.LANCHOR69,. + 0
	.type	gc_slc_mode_vpn_th, %object
	.size	gc_slc_mode_vpn_th, 2
gc_slc_mode_vpn_th:
	.space	2
	.section	.bss.gc_state,"aw",%nobits
	.set	.LANCHOR156,. + 0
	.type	gc_state, %object
	.size	gc_state, 1
gc_state:
	.space	1
	.section	.bss.gc_tlc_mode_slc_vpn_th,"aw",%nobits
	.align	1
	.set	.LANCHOR102,. + 0
	.type	gc_tlc_mode_slc_vpn_th, %object
	.size	gc_tlc_mode_slc_vpn_th, 2
gc_tlc_mode_slc_vpn_th:
	.space	2
	.section	.bss.gc_tlc_mode_tlc_vpn_th,"aw",%nobits
	.align	1
	.set	.LANCHOR100,. + 0
	.type	gc_tlc_mode_tlc_vpn_th, %object
	.size	gc_tlc_mode_tlc_vpn_th, 2
gc_tlc_mode_tlc_vpn_th:
	.space	2
	.section	.bss.gc_valid_page_ppa,"aw",%nobits
	.align	2
	.set	.LANCHOR76,. + 0
	.type	gc_valid_page_ppa, %object
	.size	gc_valid_page_ppa, 4
gc_valid_page_ppa:
	.space	4
	.section	.bss.gc_xlc_data_index,"aw",%nobits
	.align	1
	.set	.LANCHOR89,. + 0
	.type	gc_xlc_data_index, %object
	.size	gc_xlc_data_index, 2
gc_xlc_data_index:
	.space	2
	.section	.bss.gc_xlc_search_index,"aw",%nobits
	.align	1
	.set	.LANCHOR96,. + 0
	.type	gc_xlc_search_index, %object
	.size	gc_xlc_search_index, 2
gc_xlc_search_index:
	.space	2
	.section	.bss.gp_blk_info,"aw",%nobits
	.align	2
	.set	.LANCHOR9,. + 0
	.type	gp_blk_info, %object
	.size	gp_blk_info, 4
gp_blk_info:
	.space	4
	.section	.bss.gp_data_slc_cache_head,"aw",%nobits
	.align	2
	.set	.LANCHOR90,. + 0
	.type	gp_data_slc_cache_head, %object
	.size	gp_data_slc_cache_head, 4
gp_data_slc_cache_head:
	.space	4
	.section	.bss.gp_data_slc_data_head,"aw",%nobits
	.align	2
	.set	.LANCHOR95,. + 0
	.type	gp_data_slc_data_head, %object
	.size	gp_data_slc_data_head, 4
gp_data_slc_data_head:
	.space	4
	.section	.bss.gp_data_xlc_data_head,"aw",%nobits
	.align	2
	.set	.LANCHOR92,. + 0
	.type	gp_data_xlc_data_head, %object
	.size	gp_data_xlc_data_head, 4
gp_data_xlc_data_head:
	.space	4
	.section	.bss.gp_flash_check_buf,"aw",%nobits
	.align	2
	.set	.LANCHOR141,. + 0
	.type	gp_flash_check_buf, %object
	.size	gp_flash_check_buf, 4
gp_flash_check_buf:
	.space	4
	.section	.bss.gp_flash_info,"aw",%nobits
	.align	2
	.set	.LANCHOR6,. + 0
	.type	gp_flash_info, %object
	.size	gp_flash_info, 4
gp_flash_info:
	.space	4
	.section	.bss.gp_free_mix_head,"aw",%nobits
	.align	2
	.set	.LANCHOR108,. + 0
	.type	gp_free_mix_head, %object
	.size	gp_free_mix_head, 4
gp_free_mix_head:
	.space	4
	.section	.bss.gp_free_slc_head,"aw",%nobits
	.align	2
	.set	.LANCHOR104,. + 0
	.type	gp_free_slc_head, %object
	.size	gp_free_slc_head, 4
gp_free_slc_head:
	.space	4
	.section	.bss.gp_free_xlc_head,"aw",%nobits
	.align	2
	.set	.LANCHOR106,. + 0
	.type	gp_free_xlc_head, %object
	.size	gp_free_xlc_head, 4
gp_free_xlc_head:
	.space	4
	.section	.bss.gp_ftl_ext_info,"aw",%nobits
	.align	2
	.set	.LANCHOR12,. + 0
	.type	gp_ftl_ext_info, %object
	.size	gp_ftl_ext_info, 4
gp_ftl_ext_info:
	.space	4
	.section	.bss.gp_ftl_info,"aw",%nobits
	.align	2
	.set	.LANCHOR110,. + 0
	.type	gp_ftl_info, %object
	.size	gp_ftl_info, 4
gp_ftl_info:
	.space	4
	.section	.bss.gp_nand_para_info,"aw",%nobits
	.align	2
	.set	.LANCHOR21,. + 0
	.type	gp_nand_para_info, %object
	.size	gp_nand_para_info, 4
gp_nand_para_info:
	.space	4
	.section	.bss.gp_nandc,"aw",%nobits
	.align	2
	.set	.LANCHOR7,. + 0
	.type	gp_nandc, %object
	.size	gp_nandc, 4
gp_nandc:
	.space	4
	.section	.bss.gp_sblk_list_tbl,"aw",%nobits
	.align	2
	.set	.LANCHOR4,. + 0
	.type	gp_sblk_list_tbl, %object
	.size	gp_sblk_list_tbl, 4
gp_sblk_list_tbl:
	.space	4
	.section	.bss.idb_buf,"aw",%nobits
	.align	2
	.set	.LANCHOR138,. + 0
	.type	idb_buf, %object
	.size	idb_buf, 4
idb_buf:
	.space	4
	.section	.bss.idb_last_lba,"aw",%nobits
	.align	2
	.set	.LANCHOR174,. + 0
	.type	idb_last_lba, %object
	.size	idb_last_lba, 4
idb_last_lba:
	.space	4
	.section	.bss.idb_need_write_back,"aw",%nobits
	.align	2
	.set	.LANCHOR139,. + 0
	.type	idb_need_write_back, %object
	.size	idb_need_write_back, 4
idb_need_write_back:
	.space	4
	.section	.bss.idb_write_enable,"aw",%nobits
	.set	.LANCHOR140,. + 0
	.type	idb_write_enable, %object
	.size	idb_write_enable, 1
idb_write_enable:
	.space	1
	.section	.bss.lpa_hash,"aw",%nobits
	.align	1
	.set	.LANCHOR116,. + 0
	.type	lpa_hash, %object
	.size	lpa_hash, 512
lpa_hash:
	.space	512
	.section	.bss.lpa_hash_index,"aw",%nobits
	.align	2
	.set	.LANCHOR118,. + 0
	.type	lpa_hash_index, %object
	.size	lpa_hash_index, 4
lpa_hash_index:
	.space	4
	.section	.bss.nandc_ecc_sts,"aw",%nobits
	.type	nandc_ecc_sts, %object
	.size	nandc_ecc_sts, 16
nandc_ecc_sts:
	.space	16
	.section	.bss.nandc_hw_seed,"aw",%nobits
	.set	.LANCHOR50,. + 0
	.type	nandc_hw_seed, %object
	.size	nandc_hw_seed, 1
nandc_hw_seed:
	.space	1
	.section	.bss.nandc_randomizer_en,"aw",%nobits
	.set	.LANCHOR51,. + 0
	.type	nandc_randomizer_en, %object
	.size	nandc_randomizer_en, 1
nandc_randomizer_en:
	.space	1
	.section	.bss.p_free_buf_head,"aw",%nobits
	.set	.LANCHOR56,. + 0
	.type	p_free_buf_head, %object
	.size	p_free_buf_head, 1
p_free_buf_head:
	.space	1
	.section	.bss.p_read_ahead_ext_buf,"aw",%nobits
	.align	2
	.type	p_read_ahead_ext_buf, %object
	.size	p_read_ahead_ext_buf, 4
p_read_ahead_ext_buf:
	.space	4
	.section	.bss.pm_first_write,"aw",%nobits
	.set	.LANCHOR208,. + 0
	.type	pm_first_write, %object
	.size	pm_first_write, 1
pm_first_write:
	.space	1
	.section	.bss.pm_force_gc,"aw",%nobits
	.align	2
	.set	.LANCHOR148,. + 0
	.type	pm_force_gc, %object
	.size	pm_force_gc, 4
pm_force_gc:
	.space	4
	.section	.bss.pm_gc_enable,"aw",%nobits
	.align	2
	.set	.LANCHOR204,. + 0
	.type	pm_gc_enable, %object
	.size	pm_gc_enable, 4
pm_gc_enable:
	.space	4
	.section	.bss.pm_last_load_ram_id,"aw",%nobits
	.set	.LANCHOR223,. + 0
	.type	pm_last_load_ram_id, %object
	.size	pm_last_load_ram_id, 1
pm_last_load_ram_id:
	.space	1
	.section	.bss.pm_last_update_ram_id,"aw",%nobits
	.set	.LANCHOR136,. + 0
	.type	pm_last_update_ram_id, %object
	.size	pm_last_update_ram_id, 1
pm_last_update_ram_id:
	.space	1
	.section	.bss.pm_ram_info,"aw",%nobits
	.align	2
	.set	.LANCHOR135,. + 0
	.type	pm_ram_info, %object
	.size	pm_ram_info, 256
pm_ram_info:
	.space	256
	.section	.bss.read_ahead_lpa,"aw",%nobits
	.align	2
	.set	.LANCHOR238,. + 0
	.type	read_ahead_lpa, %object
	.size	read_ahead_lpa, 4
read_ahead_lpa:
	.space	4
	.section	.bss.read_buf_count,"aw",%nobits
	.set	.LANCHOR134,. + 0
	.type	read_buf_count, %object
	.size	read_buf_count, 1
read_buf_count:
	.space	1
	.section	.bss.read_buf_head,"aw",%nobits
	.set	.LANCHOR133,. + 0
	.type	read_buf_head, %object
	.size	read_buf_head, 1
read_buf_head:
	.space	1
	.section	.bss.sblk_gc_write_completed_queue_head,"aw",%nobits
	.set	.LANCHOR63,. + 0
	.type	sblk_gc_write_completed_queue_head, %object
	.size	sblk_gc_write_completed_queue_head, 1
sblk_gc_write_completed_queue_head:
	.space	1
	.section	.bss.sblk_queue_head,"aw",%nobits
	.set	.LANCHOR59,. + 0
	.type	sblk_queue_head, %object
	.size	sblk_queue_head, 1
sblk_queue_head:
	.space	1
	.section	.bss.sblk_read_completed_queue_head,"aw",%nobits
	.set	.LANCHOR62,. + 0
	.type	sblk_read_completed_queue_head, %object
	.size	sblk_read_completed_queue_head, 1
sblk_read_completed_queue_head:
	.space	1
	.section	.bss.sblk_write_completed_queue_head,"aw",%nobits
	.set	.LANCHOR64,. + 0
	.type	sblk_write_completed_queue_head, %object
	.size	sblk_write_completed_queue_head, 1
sblk_write_completed_queue_head:
	.space	1
	.section	.bss.slc_cache_sblk,"aw",%nobits
	.align	1
	.set	.LANCHOR99,. + 0
	.type	slc_cache_sblk, %object
	.size	slc_cache_sblk, 2
slc_cache_sblk:
	.space	2
	.section	.bss.slc_data_sblk,"aw",%nobits
	.align	1
	.set	.LANCHOR97,. + 0
	.type	slc_data_sblk, %object
	.size	slc_data_sblk, 2
slc_data_sblk:
	.space	2
	.section	.bss.write_buf_count,"aw",%nobits
	.set	.LANCHOR66,. + 0
	.type	write_buf_count, %object
	.size	write_buf_count, 1
write_buf_count:
	.space	1
	.section	.bss.write_buf_head,"aw",%nobits
	.set	.LANCHOR65,. + 0
	.type	write_buf_head, %object
	.size	write_buf_head, 1
write_buf_head:
	.space	1
	.section	.bss.write_commit_count,"aw",%nobits
	.set	.LANCHOR129,. + 0
	.type	write_commit_count, %object
	.size	write_commit_count, 1
write_commit_count:
	.space	1
	.section	.bss.write_commit_head,"aw",%nobits
	.set	.LANCHOR182,. + 0
	.type	write_commit_head, %object
	.size	write_commit_head, 1
write_commit_head:
	.space	1
	.section	.bss.xlc_data_sblk,"aw",%nobits
	.align	1
	.set	.LANCHOR91,. + 0
	.type	xlc_data_sblk, %object
	.size	xlc_data_sblk, 2
xlc_data_sblk:
	.space	2
	.section	.bss.zftl_print_list_count,"aw",%nobits
	.align	1
	.set	.LANCHOR109,. + 0
	.type	zftl_print_list_count, %object
	.size	zftl_print_list_count, 2
zftl_print_list_count:
	.space	2
	.section	.data.g_nand_para_info,"aw",%progbits
	.align	1
	.set	.LANCHOR32,. + 0
	.type	g_nand_para_info, %object
	.size	g_nand_para_info, 32
g_nand_para_info:
	.byte	6
	.byte	-104
	.byte	58
	.byte	-104
	.byte	-77
	.byte	118
	.byte	114
	.byte	1
	.byte	1
	.byte	32
	.short	768
	.byte	3
	.byte	2
	.short	758
	.short	5593
	.byte	0
	.byte	37
	.byte	60
	.byte	32
	.byte	2
	.byte	1
	.byte	4
	.byte	0
	.short	256
	.byte	1
	.byte	-94
	.byte	0
	.byte	0
	.section	.data.hy_f26_ref_value,"aw",%progbits
	.set	.LANCHOR162,. + 0
	.type	hy_f26_ref_value, %object
	.size	hy_f26_ref_value, 28
hy_f26_ref_value:
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
	.section	.data.nand_opt_para,"aw",%progbits
	.set	.LANCHOR215,. + 0
	.type	nand_opt_para, %object
	.size	nand_opt_para, 128
nand_opt_para:
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
	.section	.data.sd15_slc_rr,"aw",%progbits
	.set	.LANCHOR40,. + 0
	.type	sd15_slc_rr, %object
	.size	sd15_slc_rr, 25
sd15_slc_rr:
	.byte	0
	.byte	8
	.byte	-8
	.byte	16
	.byte	-16
	.byte	24
	.byte	-24
	.byte	32
	.byte	-32
	.byte	32
	.byte	-40
	.byte	48
	.byte	-48
	.byte	56
	.byte	-56
	.byte	64
	.byte	-64
	.byte	72
	.byte	-72
	.byte	80
	.byte	-80
	.byte	88
	.byte	96
	.byte	104
	.byte	112
	.section	.data.sd15_tlc_rr,"aw",%progbits
	.set	.LANCHOR39,. + 0
	.type	sd15_tlc_rr, %object
	.size	sd15_tlc_rr, 329
sd15_tlc_rr:
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	-8
	.byte	0
	.byte	16
	.byte	8
	.byte	8
	.byte	0
	.byte	-8
	.byte	-8
	.byte	-8
	.byte	-16
	.byte	-8
	.byte	-8
	.byte	-8
	.byte	-8
	.byte	-24
	.byte	0
	.byte	0
	.byte	0
	.byte	-8
	.byte	-16
	.byte	-32
	.byte	0
	.byte	8
	.byte	-8
	.byte	8
	.byte	8
	.byte	0
	.byte	0
	.byte	-16
	.byte	-8
	.byte	-8
	.byte	-8
	.byte	0
	.byte	-16
	.byte	-24
	.byte	-16
	.byte	8
	.byte	8
	.byte	-8
	.byte	-16
	.byte	-16
	.byte	0
	.byte	8
	.byte	8
	.byte	8
	.byte	8
	.byte	-8
	.byte	-8
	.byte	-24
	.byte	0
	.byte	-16
	.byte	0
	.byte	-8
	.byte	-16
	.byte	-8
	.byte	-8
	.byte	0
	.byte	8
	.byte	0
	.byte	0
	.byte	-8
	.byte	0
	.byte	-24
	.byte	-8
	.byte	0
	.byte	0
	.byte	-8
	.byte	-24
	.byte	-8
	.byte	8
	.byte	-8
	.byte	0
	.byte	-8
	.byte	8
	.byte	-16
	.byte	-8
	.byte	-8
	.byte	-8
	.byte	8
	.byte	8
	.byte	0
	.byte	0
	.byte	-8
	.byte	-8
	.byte	8
	.byte	-8
	.byte	-8
	.byte	0
	.byte	0
	.byte	-8
	.byte	-16
	.byte	-16
	.byte	-8
	.byte	0
	.byte	0
	.byte	-8
	.byte	0
	.byte	-16
	.byte	8
	.byte	0
	.byte	8
	.byte	0
	.byte	-16
	.byte	-8
	.byte	-16
	.byte	16
	.byte	0
	.byte	16
	.byte	0
	.byte	-8
	.byte	8
	.byte	0
	.byte	-24
	.byte	0
	.byte	-16
	.byte	-8
	.byte	-16
	.byte	-16
	.byte	-16
	.byte	-16
	.byte	0
	.byte	8
	.byte	-8
	.byte	-24
	.byte	0
	.byte	8
	.byte	8
	.byte	16
	.byte	16
	.byte	0
	.byte	8
	.byte	-8
	.byte	8
	.byte	16
	.byte	-8
	.byte	24
	.byte	0
	.byte	8
	.byte	-4
	.byte	0
	.byte	16
	.byte	8
	.byte	24
	.byte	8
	.byte	0
	.byte	-4
	.byte	-8
	.byte	24
	.byte	16
	.byte	16
	.byte	0
	.byte	0
	.byte	0
	.byte	-16
	.byte	0
	.byte	0
	.byte	4
	.byte	0
	.byte	-4
	.byte	-4
	.byte	-4
	.byte	8
	.byte	8
	.byte	16
	.byte	0
	.byte	16
	.byte	-4
	.byte	16
	.byte	0
	.byte	16
	.byte	8
	.byte	0
	.byte	16
	.byte	-4
	.byte	16
	.byte	-8
	.byte	0
	.byte	0
	.byte	-8
	.byte	16
	.byte	-4
	.byte	16
	.byte	-16
	.byte	-8
	.byte	-8
	.byte	-8
	.byte	8
	.byte	-4
	.byte	8
	.byte	-24
	.byte	4
	.byte	-16
	.byte	0
	.byte	8
	.byte	0
	.byte	0
	.byte	-24
	.byte	8
	.byte	-16
	.byte	8
	.byte	0
	.byte	8
	.byte	-24
	.byte	-32
	.byte	16
	.byte	-24
	.byte	8
	.byte	-8
	.byte	8
	.byte	-24
	.byte	-32
	.byte	8
	.byte	0
	.byte	16
	.byte	0
	.byte	16
	.byte	0
	.byte	-32
	.byte	4
	.byte	0
	.byte	-8
	.byte	-16
	.byte	-8
	.byte	0
	.byte	-32
	.byte	4
	.byte	0
	.byte	8
	.byte	-24
	.byte	8
	.byte	0
	.byte	-32
	.byte	4
	.byte	0
	.byte	0
	.byte	-32
	.byte	-4
	.byte	0
	.byte	-24
	.byte	4
	.byte	0
	.byte	16
	.byte	-24
	.byte	16
	.byte	0
	.byte	-24
	.byte	-4
	.byte	0
	.byte	8
	.byte	-32
	.byte	8
	.byte	0
	.byte	0
	.byte	-4
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	-4
	.byte	0
	.byte	0
	.byte	0
	.byte	-4
	.byte	0
	.byte	0
	.byte	-4
	.byte	0
	.byte	-8
	.byte	0
	.byte	-8
	.byte	0
	.byte	0
	.byte	-4
	.byte	0
	.byte	-16
	.byte	0
	.byte	-16
	.byte	0
	.byte	0
	.byte	-16
	.byte	0
	.byte	-16
	.byte	0
	.byte	-16
	.byte	0
	.byte	0
	.byte	-8
	.byte	0
	.byte	-16
	.byte	0
	.byte	-16
	.byte	0
	.byte	0
	.byte	-16
	.byte	0
	.byte	-24
	.byte	0
	.byte	-24
	.byte	0
	.byte	0
	.byte	-24
	.byte	0
	.byte	-24
	.byte	0
	.byte	-24
	.byte	0
	.byte	0
	.byte	-24
	.byte	0
	.byte	-16
	.byte	0
	.byte	-16
	.byte	0
	.byte	0
	.byte	-24
	.byte	0
	.byte	-32
	.byte	0
	.byte	-32
	.byte	0
	.section	.data.tlc_b05a_prog_tbl,"aw",%progbits
	.align	1
	.set	.LANCHOR235,. + 0
	.type	tlc_b05a_prog_tbl, %object
	.size	tlc_b05a_prog_tbl, 1536
tlc_b05a_prog_tbl:
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	0
	.short	9
	.short	0
	.short	11
	.short	0
	.short	13
	.short	0
	.short	15
	.short	0
	.short	17
	.short	0
	.short	19
	.short	0
	.short	21
	.short	0
	.short	23
	.short	0
	.short	25
	.short	0
	.short	27
	.short	0
	.short	29
	.short	0
	.short	31
	.short	0
	.short	33
	.short	0
	.short	35
	.short	0
	.short	37
	.short	0
	.short	39
	.short	0
	.short	41
	.short	0
	.short	43
	.short	0
	.short	45
	.short	0
	.short	47
	.short	0
	.short	49
	.short	0
	.short	51
	.short	0
	.short	53
	.short	0
	.short	55
	.short	0
	.short	25
	.short	58
	.short	0
	.short	27
	.short	61
	.short	0
	.short	29
	.short	64
	.short	0
	.short	31
	.short	67
	.short	0
	.short	33
	.short	70
	.short	0
	.short	35
	.short	73
	.short	0
	.short	37
	.short	76
	.short	0
	.short	39
	.short	79
	.short	0
	.short	41
	.short	82
	.short	0
	.short	43
	.short	85
	.short	0
	.short	45
	.short	88
	.short	0
	.short	47
	.short	91
	.short	0
	.short	49
	.short	94
	.short	0
	.short	51
	.short	97
	.short	0
	.short	53
	.short	100
	.short	0
	.short	55
	.short	103
	.short	0
	.short	58
	.short	106
	.short	0
	.short	61
	.short	109
	.short	0
	.short	64
	.short	112
	.short	0
	.short	67
	.short	115
	.short	0
	.short	70
	.short	118
	.short	0
	.short	73
	.short	121
	.short	0
	.short	76
	.short	124
	.short	0
	.short	79
	.short	127
	.short	0
	.short	82
	.short	130
	.short	0
	.short	85
	.short	133
	.short	0
	.short	88
	.short	136
	.short	0
	.short	91
	.short	139
	.short	0
	.short	94
	.short	142
	.short	0
	.short	97
	.short	145
	.short	0
	.short	100
	.short	148
	.short	0
	.short	103
	.short	151
	.short	0
	.short	106
	.short	154
	.short	0
	.short	109
	.short	157
	.short	0
	.short	112
	.short	160
	.short	0
	.short	115
	.short	163
	.short	0
	.short	118
	.short	166
	.short	0
	.short	121
	.short	169
	.short	0
	.short	124
	.short	172
	.short	0
	.short	127
	.short	175
	.short	0
	.short	130
	.short	178
	.short	0
	.short	133
	.short	181
	.short	0
	.short	136
	.short	184
	.short	0
	.short	139
	.short	187
	.short	0
	.short	142
	.short	190
	.short	0
	.short	145
	.short	193
	.short	0
	.short	148
	.short	196
	.short	0
	.short	151
	.short	199
	.short	0
	.short	154
	.short	202
	.short	0
	.short	157
	.short	205
	.short	0
	.short	160
	.short	208
	.short	0
	.short	163
	.short	211
	.short	0
	.short	166
	.short	214
	.short	0
	.short	169
	.short	217
	.short	0
	.short	172
	.short	220
	.short	0
	.short	175
	.short	223
	.short	0
	.short	178
	.short	226
	.short	0
	.short	181
	.short	229
	.short	0
	.short	184
	.short	232
	.short	0
	.short	187
	.short	235
	.short	0
	.short	190
	.short	238
	.short	0
	.short	193
	.short	241
	.short	0
	.short	196
	.short	244
	.short	0
	.short	199
	.short	247
	.short	0
	.short	202
	.short	250
	.short	0
	.short	205
	.short	253
	.short	0
	.short	208
	.short	256
	.short	0
	.short	211
	.short	259
	.short	0
	.short	214
	.short	262
	.short	0
	.short	217
	.short	265
	.short	0
	.short	220
	.short	268
	.short	0
	.short	223
	.short	271
	.short	0
	.short	226
	.short	274
	.short	0
	.short	229
	.short	277
	.short	0
	.short	232
	.short	280
	.short	0
	.short	235
	.short	283
	.short	0
	.short	238
	.short	286
	.short	0
	.short	241
	.short	289
	.short	0
	.short	244
	.short	292
	.short	0
	.short	247
	.short	295
	.short	0
	.short	250
	.short	298
	.short	0
	.short	253
	.short	301
	.short	0
	.short	256
	.short	304
	.short	0
	.short	259
	.short	307
	.short	0
	.short	262
	.short	310
	.short	0
	.short	265
	.short	313
	.short	0
	.short	268
	.short	316
	.short	0
	.short	271
	.short	319
	.short	0
	.short	274
	.short	322
	.short	0
	.short	277
	.short	325
	.short	0
	.short	280
	.short	328
	.short	0
	.short	283
	.short	331
	.short	0
	.short	286
	.short	334
	.short	0
	.short	289
	.short	337
	.short	0
	.short	292
	.short	340
	.short	0
	.short	295
	.short	343
	.short	0
	.short	298
	.short	346
	.short	0
	.short	301
	.short	349
	.short	0
	.short	304
	.short	352
	.short	0
	.short	307
	.short	355
	.short	0
	.short	310
	.short	358
	.short	0
	.short	313
	.short	361
	.short	0
	.short	316
	.short	364
	.short	0
	.short	319
	.short	367
	.short	0
	.short	322
	.short	370
	.short	0
	.short	325
	.short	373
	.short	0
	.short	328
	.short	376
	.short	0
	.short	331
	.short	379
	.short	0
	.short	334
	.short	382
	.short	0
	.short	337
	.short	385
	.short	0
	.short	340
	.short	388
	.short	0
	.short	343
	.short	391
	.short	0
	.short	346
	.short	394
	.short	0
	.short	349
	.short	397
	.short	0
	.short	352
	.short	400
	.short	0
	.short	355
	.short	403
	.short	0
	.short	358
	.short	406
	.short	0
	.short	361
	.short	409
	.short	0
	.short	364
	.short	412
	.short	0
	.short	367
	.short	415
	.short	0
	.short	370
	.short	418
	.short	0
	.short	373
	.short	421
	.short	0
	.short	376
	.short	424
	.short	0
	.short	379
	.short	427
	.short	0
	.short	382
	.short	430
	.short	0
	.short	385
	.short	433
	.short	0
	.short	388
	.short	436
	.short	0
	.short	391
	.short	439
	.short	0
	.short	394
	.short	442
	.short	0
	.short	397
	.short	445
	.short	0
	.short	400
	.short	448
	.short	0
	.short	403
	.short	451
	.short	0
	.short	406
	.short	454
	.short	0
	.short	409
	.short	457
	.short	0
	.short	412
	.short	460
	.short	0
	.short	415
	.short	463
	.short	0
	.short	418
	.short	466
	.short	0
	.short	421
	.short	469
	.short	0
	.short	424
	.short	472
	.short	0
	.short	427
	.short	475
	.short	0
	.short	430
	.short	478
	.short	0
	.short	433
	.short	481
	.short	0
	.short	436
	.short	484
	.short	0
	.short	439
	.short	487
	.short	0
	.short	442
	.short	490
	.short	0
	.short	445
	.short	493
	.short	0
	.short	448
	.short	496
	.short	0
	.short	451
	.short	499
	.short	0
	.short	454
	.short	502
	.short	0
	.short	457
	.short	505
	.short	0
	.short	460
	.short	508
	.short	0
	.short	463
	.short	511
	.short	0
	.short	466
	.short	514
	.short	0
	.short	469
	.short	517
	.short	0
	.short	472
	.short	520
	.short	0
	.short	475
	.short	523
	.short	0
	.short	478
	.short	526
	.short	0
	.short	481
	.short	529
	.short	0
	.short	484
	.short	532
	.short	0
	.short	487
	.short	535
	.short	0
	.short	490
	.short	538
	.short	0
	.short	493
	.short	541
	.short	0
	.short	496
	.short	544
	.short	0
	.short	499
	.short	547
	.short	0
	.short	502
	.short	550
	.short	0
	.short	505
	.short	553
	.short	0
	.short	508
	.short	556
	.short	0
	.short	511
	.short	559
	.short	0
	.short	514
	.short	562
	.short	0
	.short	517
	.short	565
	.short	0
	.short	520
	.short	568
	.short	0
	.short	523
	.short	571
	.short	0
	.short	526
	.short	574
	.short	0
	.short	529
	.short	577
	.short	0
	.short	532
	.short	580
	.short	0
	.short	535
	.short	583
	.short	0
	.short	538
	.short	586
	.short	0
	.short	541
	.short	589
	.short	0
	.short	544
	.short	592
	.short	0
	.short	547
	.short	595
	.short	0
	.short	550
	.short	598
	.short	0
	.short	553
	.short	601
	.short	0
	.short	556
	.short	604
	.short	0
	.short	559
	.short	607
	.short	0
	.short	562
	.short	610
	.short	0
	.short	565
	.short	613
	.short	0
	.short	568
	.short	616
	.short	0
	.short	571
	.short	619
	.short	0
	.short	574
	.short	622
	.short	0
	.short	577
	.short	625
	.short	0
	.short	580
	.short	628
	.short	0
	.short	583
	.short	631
	.short	0
	.short	586
	.short	634
	.short	0
	.short	589
	.short	637
	.short	0
	.short	592
	.short	640
	.short	0
	.short	595
	.short	643
	.short	0
	.short	598
	.short	646
	.short	0
	.short	601
	.short	649
	.short	0
	.short	604
	.short	652
	.short	0
	.short	607
	.short	655
	.short	0
	.short	610
	.short	658
	.short	0
	.short	613
	.short	661
	.short	0
	.short	616
	.short	664
	.short	0
	.short	619
	.short	667
	.short	0
	.short	622
	.short	670
	.short	0
	.short	625
	.short	673
	.short	0
	.short	628
	.short	676
	.short	0
	.short	631
	.short	679
	.short	0
	.short	634
	.short	682
	.short	0
	.short	637
	.short	685
	.short	0
	.short	640
	.short	688
	.short	0
	.short	643
	.short	691
	.short	0
	.short	646
	.short	694
	.short	0
	.short	649
	.short	697
	.short	0
	.short	652
	.short	700
	.short	0
	.short	655
	.short	703
	.short	0
	.short	658
	.short	706
	.short	0
	.short	661
	.short	709
	.short	0
	.short	664
	.short	712
	.short	0
	.short	667
	.short	715
	.short	0
	.short	670
	.short	718
	.short	0
	.short	673
	.short	721
	.short	0
	.short	676
	.short	724
	.short	0
	.short	679
	.short	727
	.short	0
	.short	682
	.short	730
	.short	0
	.short	685
	.short	733
	.short	0
	.short	688
	.short	736
	.short	0
	.short	691
	.short	739
	.short	0
	.short	694
	.short	742
	.short	0
	.short	697
	.short	745
	.short	0
	.short	700
	.short	748
	.short	0
	.short	703
	.short	751
	.short	0
	.short	706
	.short	0
	.short	709
	.short	0
	.short	712
	.short	0
	.short	715
	.short	0
	.short	718
	.short	0
	.short	721
	.short	0
	.short	724
	.short	0
	.short	727
	.short	0
	.section	.data.tlc_prog_order,"aw",%progbits
	.align	1
	.set	.LANCHOR236,. + 0
	.type	tlc_prog_order, %object
	.size	tlc_prog_order, 768
tlc_prog_order:
	.short	1
	.short	9
	.short	2
	.short	17
	.short	10
	.short	3
	.short	25
	.short	18
	.short	11
	.short	33
	.short	26
	.short	19
	.short	41
	.short	34
	.short	27
	.short	49
	.short	42
	.short	35
	.short	57
	.short	50
	.short	43
	.short	65
	.short	58
	.short	51
	.short	73
	.short	66
	.short	59
	.short	81
	.short	74
	.short	67
	.short	89
	.short	82
	.short	75
	.short	97
	.short	90
	.short	83
	.short	105
	.short	98
	.short	91
	.short	113
	.short	106
	.short	99
	.short	121
	.short	114
	.short	107
	.short	129
	.short	122
	.short	115
	.short	137
	.short	130
	.short	123
	.short	145
	.short	138
	.short	131
	.short	153
	.short	146
	.short	139
	.short	161
	.short	154
	.short	147
	.short	169
	.short	162
	.short	155
	.short	177
	.short	170
	.short	163
	.short	185
	.short	178
	.short	171
	.short	193
	.short	186
	.short	179
	.short	201
	.short	194
	.short	187
	.short	209
	.short	202
	.short	195
	.short	217
	.short	210
	.short	203
	.short	225
	.short	218
	.short	211
	.short	233
	.short	226
	.short	219
	.short	241
	.short	234
	.short	227
	.short	249
	.short	242
	.short	235
	.short	257
	.short	250
	.short	243
	.short	265
	.short	258
	.short	251
	.short	273
	.short	266
	.short	259
	.short	281
	.short	274
	.short	267
	.short	289
	.short	282
	.short	275
	.short	297
	.short	290
	.short	283
	.short	305
	.short	298
	.short	291
	.short	313
	.short	306
	.short	299
	.short	321
	.short	314
	.short	307
	.short	329
	.short	322
	.short	315
	.short	337
	.short	330
	.short	323
	.short	345
	.short	338
	.short	331
	.short	353
	.short	346
	.short	339
	.short	361
	.short	354
	.short	347
	.short	369
	.short	362
	.short	355
	.short	377
	.short	370
	.short	363
	.short	385
	.short	378
	.short	371
	.short	393
	.short	386
	.short	379
	.short	401
	.short	394
	.short	387
	.short	409
	.short	402
	.short	395
	.short	417
	.short	410
	.short	403
	.short	425
	.short	418
	.short	411
	.short	433
	.short	426
	.short	419
	.short	441
	.short	434
	.short	427
	.short	449
	.short	442
	.short	435
	.short	457
	.short	450
	.short	443
	.short	465
	.short	458
	.short	451
	.short	473
	.short	466
	.short	459
	.short	481
	.short	474
	.short	467
	.short	489
	.short	482
	.short	475
	.short	497
	.short	490
	.short	483
	.short	505
	.short	498
	.short	491
	.short	513
	.short	506
	.short	499
	.short	521
	.short	514
	.short	507
	.short	529
	.short	522
	.short	515
	.short	537
	.short	530
	.short	523
	.short	545
	.short	538
	.short	531
	.short	553
	.short	546
	.short	539
	.short	561
	.short	554
	.short	547
	.short	569
	.short	562
	.short	555
	.short	577
	.short	570
	.short	563
	.short	585
	.short	578
	.short	571
	.short	593
	.short	586
	.short	579
	.short	601
	.short	594
	.short	587
	.short	609
	.short	602
	.short	595
	.short	617
	.short	610
	.short	603
	.short	625
	.short	618
	.short	611
	.short	633
	.short	626
	.short	619
	.short	641
	.short	634
	.short	627
	.short	649
	.short	642
	.short	635
	.short	657
	.short	650
	.short	643
	.short	665
	.short	658
	.short	651
	.short	673
	.short	666
	.short	659
	.short	681
	.short	674
	.short	667
	.short	689
	.short	682
	.short	675
	.short	697
	.short	690
	.short	683
	.short	705
	.short	698
	.short	691
	.short	713
	.short	706
	.short	699
	.short	721
	.short	714
	.short	707
	.short	729
	.short	722
	.short	715
	.short	737
	.short	730
	.short	723
	.short	745
	.short	738
	.short	731
	.short	753
	.short	746
	.short	739
	.short	761
	.short	754
	.short	747
	.short	769
	.short	762
	.short	755
	.short	777
	.short	770
	.short	763
	.short	785
	.short	778
	.short	771
	.short	793
	.short	786
	.short	779
	.short	801
	.short	794
	.short	787
	.short	809
	.short	802
	.short	795
	.short	817
	.short	810
	.short	803
	.short	825
	.short	818
	.short	811
	.short	833
	.short	826
	.short	819
	.short	841
	.short	834
	.short	827
	.short	849
	.short	842
	.short	835
	.short	857
	.short	850
	.short	843
	.short	865
	.short	858
	.short	851
	.short	873
	.short	866
	.short	859
	.short	881
	.short	874
	.short	867
	.short	889
	.short	882
	.short	875
	.short	897
	.short	890
	.short	883
	.short	905
	.short	898
	.short	891
	.short	913
	.short	906
	.short	899
	.short	921
	.short	914
	.short	907
	.short	929
	.short	922
	.short	915
	.short	937
	.short	930
	.short	923
	.short	945
	.short	938
	.short	931
	.short	953
	.short	946
	.short	939
	.short	961
	.short	954
	.short	947
	.short	969
	.short	962
	.short	955
	.short	977
	.short	970
	.short	963
	.short	985
	.short	978
	.short	971
	.short	993
	.short	986
	.short	979
	.short	1001
	.short	994
	.short	987
	.short	1009
	.short	1002
	.short	995
	.short	1017
	.short	1010
	.short	1003
	.short	1018
	.short	1011
	.short	1019
	.section	.data.zftl_debug,"aw",%progbits
	.align	2
	.set	.LANCHOR19,. + 0
	.type	zftl_debug, %object
	.size	zftl_debug, 4
zftl_debug:
	.word	17476
	.section	.data.zftl_nand_flash_para_tbl,"aw",%progbits
	.align	1
	.set	.LANCHOR214,. + 0
	.type	zftl_nand_flash_para_tbl, %object
	.size	zftl_nand_flash_para_tbl, 1568
zftl_nand_flash_para_tbl:
	.byte	6
	.byte	-104
	.byte	58
	.byte	-104
	.byte	-77
	.byte	118
	.byte	114
	.byte	1
	.byte	1
	.byte	32
	.short	768
	.byte	3
	.byte	2
	.short	758
	.short	5593
	.byte	0
	.byte	37
	.byte	60
	.byte	32
	.byte	3
	.byte	1
	.byte	4
	.byte	0
	.short	256
	.byte	1
	.byte	-94
	.byte	0
	.byte	0
	.byte	6
	.byte	-104
	.byte	60
	.byte	-104
	.byte	-77
	.byte	118
	.byte	114
	.byte	1
	.byte	1
	.byte	32
	.short	768
	.byte	3
	.byte	2
	.short	1478
	.short	5593
	.byte	0
	.byte	37
	.byte	60
	.byte	32
	.byte	3
	.byte	1
	.byte	4
	.byte	0
	.short	256
	.byte	1
	.byte	-94
	.byte	0
	.byte	0
	.byte	6
	.byte	-104
	.byte	58
	.byte	-104
	.byte	-93
	.byte	118
	.byte	81
	.byte	1
	.byte	1
	.byte	32
	.short	384
	.byte	3
	.byte	2
	.short	1446
	.short	1497
	.byte	0
	.byte	36
	.byte	60
	.byte	32
	.byte	3
	.byte	1
	.byte	4
	.byte	0
	.short	256
	.byte	1
	.byte	-94
	.byte	0
	.byte	0
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
	.short	17881
	.byte	2
	.byte	35
	.byte	40
	.byte	32
	.byte	3
	.byte	1
	.byte	4
	.byte	0
	.short	256
	.byte	1
	.byte	-94
	.byte	0
	.byte	0
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
	.short	17857
	.byte	2
	.byte	33
	.byte	40
	.byte	32
	.byte	3
	.byte	1
	.byte	1
	.byte	0
	.short	256
	.byte	1
	.byte	-94
	.byte	0
	.byte	0
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
	.short	17881
	.byte	2
	.byte	35
	.byte	40
	.byte	32
	.byte	3
	.byte	1
	.byte	4
	.byte	0
	.short	256
	.byte	1
	.byte	-94
	.byte	0
	.byte	0
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
	.short	17857
	.byte	2
	.byte	35
	.byte	40
	.byte	32
	.byte	3
	.byte	1
	.byte	4
	.byte	0
	.short	256
	.byte	1
	.byte	-94
	.byte	0
	.byte	0
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
	.short	17857
	.byte	2
	.byte	34
	.byte	40
	.byte	32
	.byte	3
	.byte	1
	.byte	4
	.byte	0
	.short	256
	.byte	1
	.byte	-94
	.byte	0
	.byte	0
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
	.short	17881
	.byte	2
	.byte	34
	.byte	40
	.byte	32
	.byte	3
	.byte	1
	.byte	1
	.byte	0
	.short	256
	.byte	1
	.byte	-94
	.byte	0
	.byte	0
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
	.short	17857
	.byte	2
	.byte	33
	.byte	40
	.byte	32
	.byte	3
	.byte	1
	.byte	1
	.byte	0
	.short	256
	.byte	1
	.byte	-94
	.byte	0
	.byte	0
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
	.short	17881
	.byte	2
	.byte	33
	.byte	40
	.byte	32
	.byte	3
	.byte	1
	.byte	1
	.byte	0
	.short	256
	.byte	1
	.byte	-94
	.byte	0
	.byte	0
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
	.short	17881
	.byte	2
	.byte	35
	.byte	40
	.byte	32
	.byte	3
	.byte	1
	.byte	4
	.byte	0
	.short	256
	.byte	1
	.byte	-94
	.byte	0
	.byte	0
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
	.short	17881
	.byte	2
	.byte	68
	.byte	40
	.byte	32
	.byte	3
	.byte	1
	.byte	4
	.byte	0
	.short	256
	.byte	1
	.byte	-94
	.byte	0
	.byte	0
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
	.short	17881
	.byte	2
	.byte	68
	.byte	40
	.byte	32
	.byte	3
	.byte	1
	.byte	4
	.byte	0
	.short	256
	.byte	1
	.byte	-94
	.byte	0
	.byte	0
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
	.short	17881
	.byte	2
	.byte	66
	.byte	40
	.byte	32
	.byte	3
	.byte	1
	.byte	4
	.byte	0
	.short	256
	.byte	1
	.byte	-94
	.byte	0
	.byte	0
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
	.short	17881
	.byte	2
	.byte	67
	.byte	40
	.byte	32
	.byte	3
	.byte	1
	.byte	1
	.byte	0
	.short	256
	.byte	1
	.byte	-94
	.byte	0
	.byte	0
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
	.short	17857
	.byte	2
	.byte	66
	.byte	40
	.byte	32
	.byte	2
	.byte	1
	.byte	1
	.byte	0
	.short	256
	.byte	1
	.byte	-94
	.byte	0
	.byte	0
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
	.short	9671
	.byte	5
	.byte	19
	.byte	70
	.byte	32
	.byte	1
	.byte	0
	.byte	4
	.byte	0
	.short	512
	.byte	1
	.byte	-38
	.byte	-33
	.byte	0
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
	.short	512
	.byte	3
	.byte	0
	.byte	0
	.byte	0
	.byte	5
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
	.short	256
	.byte	3
	.byte	0
	.byte	0
	.byte	0
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
	.short	512
	.byte	0
	.byte	0
	.byte	0
	.byte	1
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
	.short	455
	.byte	4
	.byte	18
	.byte	60
	.byte	32
	.byte	1
	.byte	0
	.byte	1
	.byte	0
	.short	512
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	5
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
	.byte	4
	.short	1024
	.short	449
	.byte	3
	.byte	17
	.byte	40
	.byte	32
	.byte	1
	.byte	0
	.byte	1
	.byte	0
	.short	256
	.byte	3
	.byte	0
	.byte	0
	.byte	0
	.byte	5
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
	.short	512
	.byte	3
	.byte	0
	.byte	0
	.byte	0
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
	.short	9671
	.byte	5
	.byte	19
	.byte	70
	.byte	32
	.byte	1
	.byte	0
	.byte	4
	.byte	0
	.short	512
	.byte	1
	.byte	-38
	.byte	-33
	.byte	0
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
	.short	471
	.byte	3
	.byte	17
	.byte	40
	.byte	32
	.byte	1
	.byte	0
	.byte	1
	.byte	0
	.short	512
	.byte	3
	.byte	0
	.byte	0
	.byte	0
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
	.short	9671
	.byte	5
	.byte	19
	.byte	70
	.byte	32
	.byte	1
	.byte	0
	.byte	4
	.byte	0
	.short	512
	.byte	1
	.byte	-38
	.byte	-33
	.byte	0
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
	.short	9671
	.byte	5
	.byte	19
	.byte	70
	.byte	32
	.byte	1
	.byte	0
	.byte	4
	.byte	0
	.short	512
	.byte	1
	.byte	-38
	.byte	-33
	.byte	0
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
	.short	9671
	.byte	5
	.byte	19
	.byte	70
	.byte	32
	.byte	1
	.byte	0
	.byte	4
	.byte	0
	.short	512
	.byte	1
	.byte	-38
	.byte	-33
	.byte	0
	.byte	6
	.byte	-101
	.byte	73
	.byte	1
	.byte	0
	.byte	-101
	.byte	73
	.byte	9
	.byte	1
	.byte	32
	.short	256
	.byte	2
	.byte	1
	.short	2144
	.short	-23097
	.byte	8
	.byte	21
	.byte	70
	.byte	32
	.byte	1
	.byte	0
	.byte	8
	.byte	0
	.short	256
	.byte	3
	.byte	0
	.byte	0
	.byte	0
	.byte	5
	.byte	44
	.byte	-124
	.byte	100
	.byte	60
	.byte	-87
	.byte	4
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
	.short	512
	.byte	0
	.byte	0
	.byte	0
	.byte	1
	.byte	5
	.byte	44
	.byte	-124
	.byte	88
	.byte	50
	.byte	-95
	.byte	0
	.byte	4
	.byte	1
	.byte	32
	.short	768
	.byte	3
	.byte	1
	.short	1440
	.short	3527
	.byte	0
	.byte	19
	.byte	70
	.byte	32
	.byte	1
	.byte	0
	.byte	1
	.byte	0
	.short	1024
	.byte	3
	.byte	0
	.byte	0
	.byte	2
	.byte	6
	.byte	44
	.byte	-92
	.byte	8
	.byte	50
	.byte	-95
	.byte	0
	.byte	4
	.byte	1
	.byte	32
	.short	2304
	.byte	3
	.byte	1
	.short	1008
	.short	3521
	.byte	0
	.byte	19
	.byte	70
	.byte	32
	.byte	1
	.byte	0
	.byte	1
	.byte	0
	.short	4096
	.byte	3
	.byte	0
	.byte	0
	.byte	4
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
	.short	9671
	.byte	10
	.byte	19
	.byte	70
	.byte	32
	.byte	1
	.byte	0
	.byte	1
	.byte	0
	.short	1024
	.byte	1
	.byte	-38
	.byte	-33
	.byte	0
	.byte	6
	.byte	-101
	.byte	-61
	.byte	72
	.byte	37
	.byte	16
	.byte	0
	.byte	9
	.byte	1
	.byte	32
	.short	1152
	.byte	3
	.byte	2
	.short	1006
	.short	-27169
	.byte	13
	.byte	81
	.byte	70
	.byte	32
	.byte	1
	.byte	0
	.byte	4
	.byte	0
	.short	2048
	.byte	1
	.byte	-38
	.byte	-33
	.byte	24
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
	.short	455
	.byte	2
	.byte	6
	.byte	40
	.byte	32
	.byte	3
	.byte	1
	.byte	3
	.byte	0
	.short	256
	.byte	2
	.byte	-65
	.byte	-66
	.byte	0
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
	.short	256
	.byte	0
	.byte	0
	.byte	0
	.byte	0
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
	.short	256
	.byte	2
	.byte	-65
	.byte	-66
	.byte	0
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
	.short	256
	.byte	0
	.byte	0
	.byte	0
	.byte	0
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
	.short	256
	.byte	0
	.byte	0
	.byte	0
	.byte	0
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
	.short	256
	.byte	0
	.byte	0
	.byte	0
	.byte	0
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
	.short	512
	.byte	0
	.byte	-65
	.byte	-66
	.byte	1
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
	.short	512
	.byte	3
	.byte	0
	.byte	0
	.byte	0
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
	.short	512
	.byte	3
	.byte	0
	.byte	0
	.byte	0
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
	.byte	4
	.short	1024
	.short	449
	.byte	3
	.byte	17
	.byte	40
	.byte	32
	.byte	1
	.byte	0
	.byte	1
	.byte	0
	.short	256
	.byte	0
	.byte	0
	.byte	0
	.byte	0
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
	.byte	4
	.short	1024
	.short	449
	.byte	3
	.byte	17
	.byte	40
	.byte	32
	.byte	1
	.byte	0
	.byte	1
	.byte	0
	.short	256
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	6
	.byte	-119
	.byte	-120
	.byte	4
	.byte	75
	.byte	-87
	.byte	0
	.byte	7
	.byte	1
	.byte	16
	.short	256
	.byte	2
	.byte	4
	.short	1024
	.short	449
	.byte	1
	.byte	0
	.byte	24
	.byte	32
	.byte	1
	.byte	0
	.byte	1
	.byte	0
	.short	256
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	6
	.byte	-119
	.byte	-92
	.byte	8
	.byte	50
	.byte	-95
	.byte	0
	.byte	7
	.byte	1
	.byte	32
	.short	2304
	.byte	3
	.byte	1
	.short	1008
	.short	3521
	.byte	0
	.byte	19
	.byte	70
	.byte	32
	.byte	1
	.byte	0
	.byte	1
	.byte	0
	.short	4096
	.byte	3
	.byte	0
	.byte	0
	.byte	4
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
	.short	1024
	.byte	1
	.byte	-38
	.byte	-33
	.byte	0
	.section	.rodata.__func__.10003,"a",%progbits
	.set	.LANCHOR34,. + 0
	.type	__func__.10003, %object
	.size	__func__.10003, 22
__func__.10003:
	.ascii	"flash_start_page_read\000"
	.section	.rodata.__func__.10016,"a",%progbits
	.set	.LANCHOR178,. + 0
	.type	__func__.10016, %object
	.size	__func__.10016, 31
__func__.10016:
	.ascii	"flash_complete_plane_page_read\000"
	.section	.rodata.__func__.10028,"a",%progbits
	.set	.LANCHOR46,. + 0
	.type	__func__.10028, %object
	.size	__func__.10028, 23
__func__.10028:
	.ascii	"flash_start_plane_read\000"
	.section	.rodata.__func__.10041,"a",%progbits
	.set	.LANCHOR179,. + 0
	.type	__func__.10041, %object
	.size	__func__.10041, 25
__func__.10041:
	.ascii	"flash_complete_page_read\000"
	.section	.rodata.__func__.10456,"a",%progbits
	.set	.LANCHOR143,. + 0
	.type	__func__.10456, %object
	.size	__func__.10456, 20
__func__.10456:
	.ascii	"flash_die_info_init\000"
	.section	.rodata.__func__.10466,"a",%progbits
	.set	.LANCHOR20,. + 0
	.type	__func__.10466, %object
	.size	__func__.10466, 22
__func__.10466:
	.ascii	"nand_flash_print_info\000"
	.section	.rodata.__func__.10511,"a",%progbits
	.set	.LANCHOR213,. + 0
	.type	__func__.10511, %object
	.size	__func__.10511, 16
__func__.10511:
	.ascii	"nand_flash_init\000"
	.section	.rodata.__func__.10534,"a",%progbits
	.set	.LANCHOR155,. + 0
	.type	__func__.10534, %object
	.size	__func__.10534, 11
__func__.10534:
	.ascii	"nandc_init\000"
	.section	.rodata.__func__.10699,"a",%progbits
	.set	.LANCHOR58,. + 0
	.type	__func__.10699, %object
	.size	__func__.10699, 13
__func__.10699:
	.ascii	"buf_add_tail\000"
	.section	.rodata.__func__.10712,"a",%progbits
	.set	.LANCHOR60,. + 0
	.type	__func__.10712, %object
	.size	__func__.10712, 10
__func__.10712:
	.ascii	"buf_alloc\000"
	.section	.rodata.__func__.10726,"a",%progbits
	.set	.LANCHOR61,. + 0
	.type	__func__.10726, %object
	.size	__func__.10726, 16
__func__.10726:
	.ascii	"buf_remove_free\000"
	.section	.rodata.__func__.10747,"a",%progbits
	.set	.LANCHOR212,. + 0
	.type	__func__.10747, %object
	.size	__func__.10747, 20
__func__.10747:
	.ascii	"flash_info_blk_init\000"
	.section	.rodata.__func__.10762,"a",%progbits
	.set	.LANCHOR154,. + 0
	.type	__func__.10762, %object
	.size	__func__.10762, 21
__func__.10762:
	.ascii	"flash_info_data_init\000"
	.section	.rodata.__func__.10784,"a",%progbits
	.set	.LANCHOR209,. + 0
	.type	__func__.10784, %object
	.size	__func__.10784, 17
__func__.10784:
	.ascii	"flash_info_flush\000"
	.section	.rodata.__func__.10860,"a",%progbits
	.set	.LANCHOR147,. + 0
	.type	__func__.10860, %object
	.size	__func__.10860, 17
__func__.10860:
	.ascii	"lpa_rebuild_hash\000"
	.section	.rodata.__func__.10910,"a",%progbits
	.set	.LANCHOR232,. + 0
	.type	__func__.10910, %object
	.size	__func__.10910, 17
__func__.10910:
	.ascii	"ftl_write_commit\000"
	.section	.rodata.__func__.10928,"a",%progbits
	.set	.LANCHOR130,. + 0
	.type	__func__.10928, %object
	.size	__func__.10928, 14
__func__.10928:
	.ascii	"ftl_write_buf\000"
	.section	.rodata.__func__.10973,"a",%progbits
	.set	.LANCHOR132,. + 0
	.type	__func__.10973, %object
	.size	__func__.10973, 18
__func__.10973:
	.ascii	"zftl_add_read_buf\000"
	.section	.rodata.__func__.11006,"a",%progbits
	.set	.LANCHOR230,. + 0
	.type	__func__.11006, %object
	.size	__func__.11006, 10
__func__.11006:
	.ascii	"zftl_read\000"
	.section	.rodata.__func__.11038,"a",%progbits
	.set	.LANCHOR242,. + 0
	.type	__func__.11038, %object
	.size	__func__.11038, 13
__func__.11038:
	.ascii	"_ftl_discard\000"
	.section	.rodata.__func__.11184,"a",%progbits
	.set	.LANCHOR225,. + 0
	.type	__func__.11184, %object
	.size	__func__.11184, 12
__func__.11184:
	.ascii	"gc_recovery\000"
	.section	.rodata.__func__.11194,"a",%progbits
	.set	.LANCHOR71,. + 0
	.type	__func__.11194, %object
	.size	__func__.11194, 12
__func__.11194:
	.ascii	"gc_add_sblk\000"
	.section	.rodata.__func__.11241,"a",%progbits
	.set	.LANCHOR185,. + 0
	.type	__func__.11241, %object
	.size	__func__.11241, 21
__func__.11241:
	.ascii	"gc_check_data_one_wl\000"
	.section	.rodata.__func__.11273,"a",%progbits
	.set	.LANCHOR226,. + 0
	.type	__func__.11273, %object
	.size	__func__.11273, 22
__func__.11273:
	.ascii	"gc_update_l2p_map_new\000"
	.section	.rodata.__func__.11286,"a",%progbits
	.set	.LANCHOR77,. + 0
	.type	__func__.11286, %object
	.size	__func__.11286, 19
__func__.11286:
	.ascii	"gc_write_completed\000"
	.section	.rodata.__func__.11316,"a",%progbits
	.set	.LANCHOR234,. + 0
	.type	__func__.11316, %object
	.size	__func__.11316, 16
__func__.11316:
	.ascii	"gc_do_copy_back\000"
	.section	.rodata.__func__.11343,"a",%progbits
	.set	.LANCHOR127,. + 0
	.type	__func__.11343, %object
	.size	__func__.11343, 16
__func__.11343:
	.ascii	"gc_free_src_blk\000"
	.section	.rodata.__func__.11387,"a",%progbits
	.set	.LANCHOR227,. + 0
	.type	__func__.11387, %object
	.size	__func__.11387, 16
__func__.11387:
	.ascii	"gc_scan_src_blk\000"
	.section	.rodata.__func__.11448,"a",%progbits
	.set	.LANCHOR228,. + 0
	.type	__func__.11448, %object
	.size	__func__.11448, 20
__func__.11448:
	.ascii	"gc_scan_static_data\000"
	.section	.rodata.__func__.11542,"a",%progbits
	.set	.LANCHOR237,. + 0
	.type	__func__.11542, %object
	.size	__func__.11542, 11
__func__.11542:
	.ascii	"zftl_do_gc\000"
	.section	.rodata.__func__.11637,"a",%progbits
	.set	.LANCHOR5,. + 0
	.type	__func__.11637, %object
	.size	__func__.11637, 18
__func__.11637:
	.ascii	"_list_remove_node\000"
	.section	.rodata.__func__.11662,"a",%progbits
	.set	.LANCHOR13,. + 0
	.type	__func__.11662, %object
	.size	__func__.11662, 23
__func__.11662:
	.ascii	"_list_update_data_list\000"
	.section	.rodata.__func__.11737,"a",%progbits
	.set	.LANCHOR151,. + 0
	.type	__func__.11737, %object
	.size	__func__.11737, 20
__func__.11737:
	.ascii	"zftl_sblk_list_init\000"
	.section	.rodata.__func__.11771,"a",%progbits
	.set	.LANCHOR193,. + 0
	.type	__func__.11771, %object
	.size	__func__.11771, 15
__func__.11771:
	.ascii	"ftl_info_flush\000"
	.section	.rodata.__func__.11826,"a",%progbits
	.set	.LANCHOR200,. + 0
	.type	__func__.11826, %object
	.size	__func__.11826, 15
__func__.11826:
	.ascii	"ftl_alloc_sblk\000"
	.section	.rodata.__func__.11868,"a",%progbits
	.set	.LANCHOR113,. + 0
	.type	__func__.11868, %object
	.size	__func__.11868, 18
__func__.11868:
	.ascii	"ftl_alloc_sys_blk\000"
	.section	.rodata.__func__.11878,"a",%progbits
	.set	.LANCHOR114,. + 0
	.type	__func__.11878, %object
	.size	__func__.11878, 17
__func__.11878:
	.ascii	"ftl_free_sys_blk\000"
	.section	.rodata.__func__.11913,"a",%progbits
	.set	.LANCHOR229,. + 0
	.type	__func__.11913, %object
	.size	__func__.11913, 14
__func__.11913:
	.ascii	"ftl_sblk_dump\000"
	.section	.rodata.__func__.11937,"a",%progbits
	.set	.LANCHOR218,. + 0
	.type	__func__.11937, %object
	.size	__func__.11937, 16
__func__.11937:
	.ascii	"ftl_sysblk_dump\000"
	.section	.rodata.__func__.11962,"a",%progbits
	.set	.LANCHOR219,. + 0
	.type	__func__.11962, %object
	.size	__func__.11962, 23
__func__.11962:
	.ascii	"ftl_open_sblk_recovery\000"
	.section	.rodata.__func__.11995,"a",%progbits
	.set	.LANCHOR115,. + 0
	.type	__func__.11995, %object
	.size	__func__.11995, 23
__func__.11995:
	.ascii	"ftl_get_ppa_from_index\000"
	.section	.rodata.__func__.12016,"a",%progbits
	.set	.LANCHOR231,. + 0
	.type	__func__.12016, %object
	.size	__func__.12016, 19
__func__.12016:
	.ascii	"ftl_update_l2p_map\000"
	.section	.rodata.__func__.12035,"a",%progbits
	.set	.LANCHOR119,. + 0
	.type	__func__.12035, %object
	.size	__func__.12035, 22
__func__.12035:
	.ascii	"ftl_get_new_free_page\000"
	.section	.rodata.__func__.12046,"a",%progbits
	.set	.LANCHOR120,. + 0
	.type	__func__.12046, %object
	.size	__func__.12046, 22
__func__.12046:
	.ascii	"ftl_ext_alloc_new_blk\000"
	.section	.rodata.__func__.12072,"a",%progbits
	.set	.LANCHOR198,. + 0
	.type	__func__.12072, %object
	.size	__func__.12072, 19
__func__.12072:
	.ascii	"ftl_ext_info_flush\000"
	.section	.rodata.__func__.12084,"a",%progbits
	.set	.LANCHOR199,. + 0
	.type	__func__.12084, %object
	.size	__func__.12084, 18
__func__.12084:
	.ascii	"ftl_ext_info_init\000"
	.section	.rodata.__func__.12123,"a",%progbits
	.set	.LANCHOR201,. + 0
	.type	__func__.12123, %object
	.size	__func__.12123, 25
__func__.12123:
	.ascii	"ftl_low_format_data_init\000"
	.section	.rodata.__func__.12138,"a",%progbits
	.set	.LANCHOR203,. + 0
	.type	__func__.12138, %object
	.size	__func__.12138, 15
__func__.12138:
	.ascii	"ftl_low_format\000"
	.section	.rodata.__func__.12186,"a",%progbits
	.set	.LANCHOR189,. + 0
	.type	__func__.12186, %object
	.size	__func__.12186, 14
__func__.12186:
	.ascii	"ftl_prog_page\000"
	.section	.rodata.__func__.12309,"a",%progbits
	.set	.LANCHOR180,. + 0
	.type	__func__.12309, %object
	.size	__func__.12309, 31
__func__.12309:
	.ascii	"queue_wait_first_req_completed\000"
	.section	.rodata.__func__.12363,"a",%progbits
	.set	.LANCHOR181,. + 0
	.type	__func__.12363, %object
	.size	__func__.12363, 15
__func__.12363:
	.ascii	"sblk_prog_page\000"
	.section	.rodata.__func__.12390,"a",%progbits
	.set	.LANCHOR184,. + 0
	.type	__func__.12390, %object
	.size	__func__.12390, 15
__func__.12390:
	.ascii	"sblk_read_page\000"
	.section	.rodata.__func__.12460,"a",%progbits
	.set	.LANCHOR220,. + 0
	.type	__func__.12460, %object
	.size	__func__.12460, 16
__func__.12460:
	.ascii	"load_l2p_region\000"
	.section	.rodata.__func__.12476,"a",%progbits
	.set	.LANCHOR153,. + 0
	.type	__func__.12476, %object
	.size	__func__.12476, 13
__func__.12476:
	.ascii	"pm_free_sblk\000"
	.section	.rodata.__func__.12500,"a",%progbits
	.set	.LANCHOR222,. + 0
	.type	__func__.12500, %object
	.size	__func__.12500, 6
__func__.12500:
	.ascii	"pm_gc\000"
	.section	.rodata.__func__.12516,"a",%progbits
	.set	.LANCHOR205,. + 0
	.type	__func__.12516, %object
	.size	__func__.12516, 17
__func__.12516:
	.ascii	"pm_alloc_new_blk\000"
	.section	.rodata.__func__.12526,"a",%progbits
	.set	.LANCHOR206,. + 0
	.type	__func__.12526, %object
	.size	__func__.12526, 14
__func__.12526:
	.ascii	"pm_write_page\000"
	.section	.rodata.__func__.12544,"a",%progbits
	.set	.LANCHOR137,. + 0
	.type	__func__.12544, %object
	.size	__func__.12544, 21
__func__.12544:
	.ascii	"pm_select_ram_region\000"
	.section	.rodata.__func__.9837,"a",%progbits
	.set	.LANCHOR170,. + 0
	.type	__func__.9837, %object
	.size	__func__.9837, 19
__func__.9837:
	.ascii	"flash_read_page_en\000"
	.section	.rodata.__func__.9898,"a",%progbits
	.set	.LANCHOR186,. + 0
	.type	__func__.9898, %object
	.size	__func__.9898, 19
__func__.9898:
	.ascii	"flash_prog_page_en\000"
	.section	.rodata.__func__.9914,"a",%progbits
	.set	.LANCHOR43,. + 0
	.type	__func__.9914, %object
	.size	__func__.9914, 26
__func__.9914:
	.ascii	"flash_erase_duplane_block\000"
	.section	.rodata.__func__.9925,"a",%progbits
	.set	.LANCHOR45,. + 0
	.type	__func__.9925, %object
	.size	__func__.9925, 21
__func__.9925:
	.ascii	"flash_erase_block_en\000"
	.section	.rodata.__func__.9939,"a",%progbits
	.set	.LANCHOR28,. + 0
	.type	__func__.9939, %object
	.size	__func__.9939, 28
__func__.9939:
	.ascii	"flash_wait_device_ready_raw\000"
	.section	.rodata.__func__.9963,"a",%progbits
	.set	.LANCHOR175,. + 0
	.type	__func__.9963, %object
	.size	__func__.9963, 26
__func__.9963:
	.ascii	"flash_start_tlc_page_prog\000"
	.section	.rodata.__func__.9974,"a",%progbits
	.set	.LANCHOR176,. + 0
	.type	__func__.9974, %object
	.size	__func__.9974, 29
__func__.9974:
	.ascii	"flash_start_3d_mlc_page_prog\000"
	.section	.rodata.__func__.9992,"a",%progbits
	.set	.LANCHOR177,. + 0
	.type	__func__.9992, %object
	.size	__func__.9992, 22
__func__.9992:
	.ascii	"flash_start_page_prog\000"
	.section	.rodata._list_remove_node.str1.1,"aMS",%progbits,1
.LC0:
	.ascii	"\012!!!!! error @ func:%s - line:%d\012\000"
	.section	.rodata.dump_buf_info.str1.1,"aMS",%progbits,1
.LC41:
	.ascii	"sblk_queue_head = %d\012\000"
.LC42:
	.ascii	"sblk_read_completed_queue_head = %d\012\000"
.LC43:
	.ascii	"sblk_gc_write_completed_queue_head = %d\012\000"
.LC44:
	.ascii	"sblk_write_completed_queue_head = %d\012\000"
.LC45:
	.ascii	"p_free_buf_head = %d\012\000"
.LC46:
	.ascii	"free_buf_count = %d\012\000"
.LC47:
	.ascii	"buf = %d, next=%d, flag=%d gc_write_flag=%d, lun_st"
	.ascii	"ate=%d, op_status = %d lpa=%x, ppa=%x\012\000"
	.section	.rodata.dump_ftl_info.str1.1,"aMS",%progbits,1
.LC192:
	.ascii	"free_buf_count: %d\012\000"
.LC193:
	.ascii	"g_ftl_info_blk blk:0x%x, index:0x%x, page:0x%x\012\000"
.LC194:
	.ascii	"ftl_ext_info_blk blk:0x%x, page:0x%x\012\000"
.LC195:
	.ascii	"ac_blk:0x%x, page:0x%x, index:0x%x, free:0x%x, page"
	.ascii	"_index:0x%x\012\000"
.LC196:
	.ascii	"tmp_blk:0x%x, page:0x%x, index:0x%x, free:0x%x, pag"
	.ascii	"e_index:0x%x\012\000"
.LC197:
	.ascii	"gc_blk:0x%x, page:0x%x, index:0x%x, free:0x%x, page"
	.ascii	"_index:0x%x\012\000"
.LC198:
	.ascii	"lpa:\000"
.LC199:
	.ascii	"vpn:\000"
.LC200:
	.ascii	"sblk:\000"
.LC201:
	.ascii	"lpa_hash:\000"
.LC202:
	.ascii	"lpa_hash_index:\000"
	.section	.rodata.dump_pm_blk.str1.1,"aMS",%progbits,1
.LC257:
	.ascii	"pm l2p:\000"
.LC258:
	.ascii	"pm blk:\000"
	.section	.rodata.dump_sblk_queue.str1.1,"aMS",%progbits,1
.LC79:
	.ascii	"dump_sblk_queue: %d\012\000"
.LC80:
	.ascii	"buf id= %d state = %d ppa = %x\012\000"
	.section	.rodata.flash_complete_page_read.str1.1,"aMS",%progbits,1
.LC136:
	.ascii	"flash_complete_page_read %x %x error_ecc %d %d\012\000"
	.section	.rodata.flash_ddr_tuning_read.str1.1,"aMS",%progbits,1
.LC122:
	.ascii	"%d flash_ddr_tuning_read %x ecc=%d\012\000"
.LC123:
	.ascii	"sync para %d\012\000"
.LC124:
	.ascii	"DDR mode Read error %x %x\012\000"
.LC125:
	.ascii	"SDR mode Read %x %x ecc:%x\012\000"
	.section	.rodata.flash_dual_page_prog.str1.1,"aMS",%progbits,1
.LC130:
	.ascii	"flash_prog_page %x %x %x\012\000"
	.section	.rodata.flash_erase_all.str1.1,"aMS",%progbits,1
.LC35:
	.ascii	"erase done: %x\012\000"
	.section	.rodata.flash_erase_block_en.str1.1,"aMS",%progbits,1
.LC33:
	.ascii	"flash_erase_block %x %x %x\012\000"
.LC34:
	.ascii	"flash_erase_block %d block = %x status = %x\012\000"
	.section	.rodata.flash_erase_duplane_block.str1.1,"aMS",%progbits,1
.LC31:
	.ascii	"flash_erase_duplane_block %x %x %x\012\000"
.LC32:
	.ascii	"flash_erase_duplane_block pageadd = %x status = %x\012"
	.ascii	"\000"
	.section	.rodata.flash_get_last_written_page.str1.1,"aMS",%progbits,1
.LC128:
	.ascii	"flash_get_last_written_page: %x %x %x\012\000"
	.section	.rodata.flash_info_blk_init.str1.1,"aMS",%progbits,1
.LC177:
	.ascii	"...%d @ %s %d %p\012\000"
.LC178:
	.ascii	"no sys info %x\012\000"
	.section	.rodata.flash_info_data_init.str1.1,"aMS",%progbits,1
.LC94:
	.ascii	"...%d @ %s\012\000"
	.section	.rodata.flash_info_flush.str1.1,"aMS",%progbits,1
.LC174:
	.ascii	"finfo:\000"
.LC175:
	.ascii	"flash_info_flush id = %x, page = %x\012\000"
.LC176:
	.ascii	"sys_info_flush error:%x\012\000"
	.section	.rodata.flash_mask_bad_block.str1.1,"aMS",%progbits,1
.LC48:
	.ascii	"flash_mask_bad_block %d %d\012\000"
	.section	.rodata.flash_prog_page.str1.1,"aMS",%progbits,1
.LC129:
	.ascii	"flash_prog_page page_addr = %x status = %x\012\000"
	.section	.rodata.flash_prog_page_en.str1.1,"aMS",%progbits,1
.LC144:
	.ascii	"flash_prog_page_en:%x %x %x\012\000"
.LC145:
	.ascii	"w d:\000"
.LC146:
	.ascii	"w s:\000"
.LC147:
	.ascii	"spare\000"
.LC148:
	.ascii	"data\000"
.LC149:
	.ascii	"write error: %x\012\000"
	.section	.rodata.flash_read_id.str1.1,"aMS",%progbits,1
.LC38:
	.ascii	"No.%d FLASH ID:%x %x %x %x %x %x\012\000"
	.section	.rodata.flash_read_otp_data.str1.1,"aMS",%progbits,1
.LC39:
	.ascii	"otp:%x %x %x %x\012\000"
	.section	.rodata.flash_read_page_en.str1.1,"aMS",%progbits,1
.LC126:
	.ascii	"flash_read_page_en %x %x %x %x\012\000"
.LC127:
	.ascii	"flash_read_page_en %x %x error_ecc %d %d\012\000"
	.section	.rodata.flash_set_interface_mode.str1.1,"aMS",%progbits,1
.LC36:
	.ascii	"nand sdr mode %x\012\000"
.LC37:
	.ascii	"nand ddr mode %x\012\000"
	.section	.rodata.ftl_alloc_new_data_sblk.str1.1,"aMS",%progbits,1
.LC235:
	.ascii	"error gc_add_sblk: %x\012\000"
	.section	.rodata.ftl_alloc_sblk.str1.1,"aMS",%progbits,1
.LC167:
	.ascii	"alloc sblk %x %d\012\000"
	.section	.rodata.ftl_dump_write_open_sblk.str1.1,"aMS",%progbits,1
.LC159:
	.ascii	"ftl_sblk_dump_write = %x %d %d %d %d\012\000"
.LC160:
	.ascii	"blk= %x, page=%x, ppa = %x, status = %x, data:%x %x"
	.ascii	" %x %x, spare: %x %x %x %x\012\000"
.LC161:
	.ascii	"ftl_sblk_dump_write2 = %x %d %d %d\012\000"
.LC162:
	.ascii	"ftl_sblk_dump_write = %x %x\012\000"
.LC163:
	.ascii	"ftl_sblk_dump_write done = %x\012\000"
	.section	.rodata.ftl_ext_info_init.str1.1,"aMS",%progbits,1
.LC156:
	.ascii	"%s %d %d %x %x\012\000"
.LC157:
	.ascii	"ext info hash %x error\012\000"
.LC158:
	.ascii	"%s %x %x %x\012\000"
	.section	.rodata.ftl_free_sblk.str1.1,"aMS",%progbits,1
.LC68:
	.ascii	"swl_slc_free_mini_ec_blk sblk %x\012\000"
	.section	.rodata.ftl_info_blk_init.str1.1,"aMS",%progbits,1
.LC152:
	.ascii	"%d %x @%d %x\012\000"
.LC153:
	.ascii	"ftl_info_blk_init %d %d %x\012\000"
.LC154:
	.ascii	"ftl info hash %x error\012\000"
.LC155:
	.ascii	"ink flag: %x\012\000"
	.section	.rodata.ftl_info_flush.str1.1,"aMS",%progbits,1
.LC151:
	.ascii	"g_ftl_info_blk blk = %x, page = %x version = %d\012"
	.ascii	"\000"
	.section	.rodata.ftl_ink_check_sblk.str1.1,"aMS",%progbits,1
.LC165:
	.ascii	"ftl_ink_check_sblk = %x %d %d\012\000"
.LC166:
	.ascii	"ftl_ink_check_sblk = %x %d %d end\012\000"
	.section	.rodata.ftl_low_format.str1.1,"aMS",%progbits,1
.LC169:
	.ascii	"ftl_low_format %d\012\000"
.LC170:
	.ascii	"low format %d %d %d %d\012\000"
	.section	.rodata.ftl_mask_bad_block.str1.1,"aMS",%progbits,1
.LC66:
	.ascii	"mask bad block:cs %x %x block: %x %x\012\000"
	.section	.rodata.ftl_open_sblk_init.str1.1,"aMS",%progbits,1
.LC168:
	.ascii	"blk %x is bad block\012\000"
	.section	.rodata.ftl_open_sblk_recovery.str1.1,"aMS",%progbits,1
.LC180:
	.ascii	"saved_active_page  = %x\012\000"
.LC181:
	.ascii	"saved_active_plane = %x\012\000"
.LC182:
	.ascii	"sblk = %x\012\000"
.LC183:
	.ascii	"phy_blk = %x %x\012\000"
.LC184:
	.ascii	"num_planes = %x\012\000"
.LC185:
	.ascii	"recovery blk=%x, page=%x, ppa = %x, status = %x, ha"
	.ascii	"sh:%x\012\000"
.LC186:
	.ascii	"data:\000"
.LC187:
	.ascii	"sblk = %x, vpn0 = %d, vpn1 = %d\012\000"
.LC188:
	.ascii	"dump_write_lpa = %x %x %x %x\012\000"
.LC189:
	.ascii	"dump write new ppa = %x, last ppa = %x lpa = %x\012"
	.ascii	"\000"
.LC190:
	.ascii	"dump write = %x %x %x\012\000"
.LC191:
	.ascii	"dump write hash update = %x %x %x\012\000"
	.section	.rodata.ftl_re_low_format.str1.1,"aMS",%progbits,1
.LC171:
	.ascii	"re low format %d\012\000"
	.section	.rodata.ftl_sblk_dump.str1.1,"aMS",%progbits,1
.LC223:
	.ascii	"ftl_sblk_dump = %x %d %d %d %d\012\000"
.LC224:
	.ascii	"ftl_sblk_dump = %x %x %x %x\012\000"
.LC225:
	.ascii	"page_addr = %x, lpa=%x vpn = %d\012\000"
.LC226:
	.ascii	"index= %x, lpa=%x\012\000"
.LC227:
	.ascii	"block = %x, vpn=%x check vpn = %x\012\000"
	.section	.rodata.ftl_sysblk_dump.str1.1,"aMS",%progbits,1
.LC179:
	.ascii	"l2p:\000"
	.section	.rodata.ftl_test_block.str1.1,"aMS",%progbits,1
.LC150:
	.ascii	"low format %d\012\000"
	.section	.rodata.ftl_update_l2p_map.str1.1,"aMS",%progbits,1
.LC231:
	.ascii	"ftl_update_l2p_map: %x %x %x\012\000"
.LC232:
	.ascii	"ftl_update_l2p_map\000"
.LC233:
	.ascii	"lpa_tbl:\000"
.LC234:
	.ascii	"sblk %x vpn: %d %d\012\000"
	.section	.rodata.ftl_vpn_decrement.str1.1,"aMS",%progbits,1
.LC65:
	.ascii	"ftl_vpn_decrement %x = %d, %d\012\000"
	.section	.rodata.ftl_write_commit.str1.1,"aMS",%progbits,1
.LC236:
	.ascii	"%d read error: ppa:%x, lpa:%x, status:%x\012\000"
	.section	.rodata.ftl_write_completed.str1.1,"aMS",%progbits,1
.LC77:
	.ascii	"ftl prog error =%x, lpa = %x, ppa= %x\012\000"
.LC78:
	.ascii	"ftl re prog: lpa = %x, ppa= %x\012\000"
	.section	.rodata.gc_add_sblk.str1.1,"aMS",%progbits,1
.LC49:
	.ascii	"gc_add_sblk = %d, %d, %d, %d, %d, %d, %d\012\000"
.LC50:
	.ascii	"gc_add_sblk = %d, %d, %d\012\000"
.LC51:
	.ascii	"gc_add_sblk = %d, %d, %d,last update:%d, %d\012\000"
.LC52:
	.ascii	"gc_add_sblk = %d, %d, %d, %d, %d, %d\012\000"
	.section	.rodata.gc_check_data_one_wl.str1.1,"aMS",%progbits,1
.LC143:
	.ascii	"err: ppa = %x, status = %x, %x %x spare: %x %x %x %"
	.ascii	"x\012\000"
	.section	.rodata.gc_do_copy_back.str1.1,"aMS",%progbits,1
.LC237:
	.ascii	"gc page in buf: lpa %x ppa = %x pageindex= %x\012\000"
.LC238:
	.ascii	"gc_do_copy_back: lpa %x des_ppa = %x %x gc_ppa= %x "
	.ascii	"page_index= %d\012\000"
	.section	.rodata.gc_free_bad_sblk.str1.1,"aMS",%progbits,1
.LC67:
	.ascii	"gc_free_bad_sblk 0x%x\012\000"
	.section	.rodata.gc_free_src_blk.str1.1,"aMS",%progbits,1
.LC69:
	.ascii	"gc_free_src_blk = %x, vpn = %d\012\000"
.LC70:
	.ascii	"gc_free_src_blk %x, %d\012\000"
	.section	.rodata.gc_free_temp_buf.str1.1,"aMS",%progbits,1
.LC55:
	.ascii	"%d gc_free_temp_buf buf id= %x\012\000"
	.section	.rodata.gc_ink_check_sblk.str1.1,"aMS",%progbits,1
.LC164:
	.ascii	"%x: ink_scaned_blk_num %x\012\000"
	.section	.rodata.gc_mark_bad_ppa.str1.1,"aMS",%progbits,1
.LC53:
	.ascii	"gc_mark_bad_ppa %d %x %x\012\000"
	.section	.rodata.gc_recovery.str1.1,"aMS",%progbits,1
.LC213:
	.ascii	"ppa = %x, status = %x, data:%x %x %x %x, spare: %x "
	.ascii	"%x %x %x\012\000"
.LC214:
	.ascii	"ppa = %x, status = %x, %x %x spare: %x %x %x %x\012"
	.ascii	"\000"
.LC215:
	.ascii	"gc_recovery: %x vpn = %x\012\000"
	.section	.rodata.gc_scan_src_blk.str1.1,"aMS",%progbits,1
.LC220:
	.ascii	"gc_scan_src_blk = %x, vpn = %d\012\000"
.LC221:
	.ascii	"js hash error:%x %x %x\012\000"
.LC222:
	.ascii	"gc_scan_src_blk = %x, s vpn0 = %d, c vpn1 = %d\012\000"
	.section	.rodata.gc_search_src_blk.str1.1,"aMS",%progbits,1
.LC57:
	.ascii	"zftl_get_gc_node cache = %x index = %d vpn = %x\012"
	.ascii	"\000"
.LC58:
	.ascii	"gc_search_src_blk mode = %x, src mode = %x, count= "
	.ascii	"%d %d\012\000"
	.section	.rodata.gc_static_wearleveling.str1.1,"aMS",%progbits,1
.LC82:
	.ascii	"gc_static_wearleveling: min blk: %x,sec=%d,xec = %d"
	.ascii	" ,mode=%d, func=%x, bbt=%x vpn = %d\012\000"
.LC83:
	.ascii	"gc_static_wearleveling: min slc blk: %x,sec=%d,xec "
	.ascii	"= %d ,mode=%d, func=%x, bbt=%x vpn = %d\012\000"
.LC84:
	.ascii	"gc_static_wearleveling: min tlc blk: %x,sec=%d,xec "
	.ascii	"= %d ,mode=%d, func=%x, bbt=%x vpn = %d\012\000"
.LC85:
	.ascii	"gc_static_wearleveling: max slc blk: %x,sec=%d,xec "
	.ascii	"= %d ,mode=%d, func=%x, bbt=%x vpn = %d\012\000"
.LC86:
	.ascii	"gc_static_wearleveling: max xlc blk: %x,sec=%d,xec "
	.ascii	"= %d ,mode=%d, func=%x, bbt=%x vpn = %d\012\000"
.LC87:
	.ascii	"gc_static_wearleveling: slc blk: %x, tlc blk: %d av"
	.ascii	"g slc ec: %d, avg tlc ec: %d \012\000"
.LC88:
	.ascii	"gc_static_wearleveling: min slc ec: %x, min tlc ec:"
	.ascii	" %d max slc ec: %d, max tlc ec: %d; %d %d\012\000"
.LC89:
	.ascii	"swl add tlc gc = %x, %d, %d, %d, %d, %d\012\000"
.LC90:
	.ascii	"swl add slc gc  = %x, %d, %d, %d, %d, %d\012\000"
	.section	.rodata.gc_update_l2p_map_new.str1.1,"aMS",%progbits,1
.LC216:
	.ascii	"gc_update_l2p_map_new sblk %x\012\000"
.LC217:
	.ascii	"gc_update_l2p_map_new: %x %x %x\012\000"
.LC218:
	.ascii	"lpa: %x %x %x\012\000"
.LC219:
	.ascii	"gc_update_l2p_map_new: %x vpn = %x vpn1 = %x done\012"
	.ascii	"\000"
	.section	.rodata.gc_write_completed.str1.1,"aMS",%progbits,1
.LC54:
	.ascii	"status: %x, ppa: %x\012\000"
	.section	.rodata.hynix_get_read_retry_default.str1.1,"aMS",%progbits,1
.LC102:
	.ascii	"otp error! %d\000"
.LC103:
	.ascii	"rr\000"
	.section	.rodata.hynix_read_retrial.str1.1,"aMS",%progbits,1
.LC121:
	.ascii	"hynix RR %d row=%x, count %d, status=%d\012\000"
	.section	.rodata.idb_write_data.str1.1,"aMS",%progbits,1
.LC132:
	.ascii	"1 write_idblock fix data %x %x %x\012\000"
.LC133:
	.ascii	"write_idblock check fail! %x\012\000"
.LC134:
	.ascii	"write_idblock fail! %x\012\000"
	.section	.rodata.load_l2p_region.str1.1,"aMS",%progbits,1
.LC204:
	.ascii	"region_id = %d, pm_max_region = %d\012\000"
.LC205:
	.ascii	"load_l2p_region no ppa = %x , %x, all setting 0xff."
	.ascii	"...\012\000"
.LC206:
	.ascii	"load_l2p_region = %x,%x,%x, %x\012\000"
.LC207:
	.ascii	"pm_ppa:\000"
.LC208:
	.ascii	"spare:\000"
	.section	.rodata.lpa_rebuild_hash.str1.1,"aMS",%progbits,1
.LC81:
	.ascii	"%s %d %d\012\000"
	.section	.rodata.micron_read_retrial.str1.1,"aMS",%progbits,1
.LC112:
	.ascii	"MT %d row=%x,last status %d,status = %d\012\000"
.LC113:
	.ascii	"MT RR %d row=%x,count %d,status=%d\012\000"
	.section	.rodata.nand_flash_print_info.str1.1,"aMS",%progbits,1
.LC1:
	.ascii	"...%s enter...\012\000"
.LC2:
	.ascii	"No.0 FLASH ID: %x %x %x %x %x %x\012\000"
.LC3:
	.ascii	"DiePerChip: %x\012\000"
.LC4:
	.ascii	"SectPerPage: %x\012\000"
.LC5:
	.ascii	"PagePerBlk: %x\012\000"
.LC6:
	.ascii	"Cell: %x\012\000"
.LC7:
	.ascii	"PlanePerDie: %x\012\000"
.LC8:
	.ascii	"BlkPerPlane: %x\012\000"
.LC9:
	.ascii	"die gap: %x\012\000"
.LC10:
	.ascii	"lsbMode: %x\012\000"
.LC11:
	.ascii	"ReadRetryMode: %x\012\000"
.LC12:
	.ascii	"ecc: %x\012\000"
.LC13:
	.ascii	"idb ecc: %x\012\000"
.LC14:
	.ascii	"OptMode: %x\012\000"
.LC15:
	.ascii	"g_nand_max_die: %x\012\000"
.LC16:
	.ascii	"Cache read enable: %x\012\000"
.LC17:
	.ascii	"Cache random read enable: %x\012\000"
.LC18:
	.ascii	"Cache prog enable: %x\012\000"
.LC19:
	.ascii	"multi read enable: %x\012\000"
.LC20:
	.ascii	"multi prog enable: %x\012\000"
.LC21:
	.ascii	"interleave enable: %x\012\000"
.LC22:
	.ascii	"read retry enable: %x\012\000"
.LC23:
	.ascii	"randomizer enable: %x\012\000"
.LC24:
	.ascii	"SDR enable: %x\012\000"
.LC25:
	.ascii	"ONFI enable: %x\012\000"
.LC26:
	.ascii	"TOGGLE enable: %x\012\000"
.LC27:
	.ascii	"g_flash_slc_mode: %x %x\012\000"
.LC28:
	.ascii	"MultiPlaneProgCmd: %x %x\012\000"
.LC29:
	.ascii	"MultiPlaneReadCmd: %x %x\012\000"
.LC30:
	.ascii	"g_flash_toggle_mode_en: %x\012\000"
	.section	.rodata.nandc_init.str1.1,"aMS",%progbits,1
.LC95:
	.ascii	"...%s enter... %p\012\000"
.LC96:
	.ascii	"0:%x %x %x %x %x\012\000"
.LC97:
	.ascii	"g_nandc_ver...%d\012\000"
	.section	.rodata.nandc_xfer.str1.1,"aMS",%progbits,1
.LC109:
	.ascii	"dqs data abort %x\012\000"
.LC110:
	.ascii	"dqs data timeout %x\012\000"
.LC111:
	.ascii	"xfer error %x\012\000"
	.section	.rodata.nandc_xfer_done.str1.1,"aMS",%progbits,1
.LC104:
	.ascii	"flash_abort_clear = %d\012\000"
.LC105:
	.ascii	"%d mtrans_cnt = %d page_num = %d\012\000"
.LC106:
	.ascii	"%d flReg.d32=%x %x\012\000"
.LC107:
	.ascii	"nandc:\000"
.LC108:
	.ascii	"nandc_xfer_done read error %x\012\000"
	.section	.rodata.pm_alloc_new_blk.str1.1,"aMS",%progbits,1
.LC172:
	.ascii	"pm_alloc_new_blk: %x %x %x %x\012\000"
	.section	.rodata.pm_free_sblk.str1.1,"aMS",%progbits,1
.LC92:
	.ascii	"GC PM block %x %x %x %d\012\000"
.LC93:
	.ascii	"ftl_free_no_use_map_blk %x %x %x %d\012\000"
	.section	.rodata.pm_init.str1.1,"aMS",%progbits,1
.LC209:
	.ascii	"pm_init posr %x %x %x\012\000"
.LC210:
	.ascii	"pm_init recovery %x %x %x\012\000"
.LC211:
	.ascii	"pm_init hash %x error\012\000"
	.section	.rodata.pm_log2phys.str1.1,"aMS",%progbits,1
.LC212:
	.ascii	"pm_log2phys  lpn = %d, max lpn = %d\012\000"
	.section	.rodata.pm_ppa_update_check.str1.1,"aMS",%progbits,1
.LC203:
	.ascii	"%s w error lpn = %x, max ppa = %d\012\000"
	.section	.rodata.pm_write_page.str1.1,"aMS",%progbits,1
.LC173:
	.ascii	"pm_write_page write error: %x\012\000"
	.section	.rodata.print_ftl_debug_info.str1.1,"aMS",%progbits,1
.LC71:
	.ascii	"bad blk = %x, %x free blk: s:%x,t:%x,m:%x, data blk"
	.ascii	":s:%x,%x,t%x vpn: s:%x t:%x, max_vpn: %x\012\000"
.LC72:
	.ascii	"totle w: %d MB,r: %d MB %d dv:0x%X,poc:%d\012\000"
.LC73:
	.ascii	"gc xlc page: %d,gc slc page: %d, tmp w: %d MB\012\000"
.LC74:
	.ascii	"slc ec: %d,%d,%d,%d,%d,tlc ec: %d,%d,%d,%d,%d\012\000"
.LC75:
	.ascii	"gc th: tlc_tlc: %d tlc_slc: %d slc_slc: %d slc_tlc:"
	.ascii	"%d free_th: %d\012\000"
.LC76:
	.ascii	"swl : %x %x %x %x %x %x\012\000"
	.section	.rodata.print_gc_debug_info.str1.1,"aMS",%progbits,1
.LC56:
	.ascii	"gc: b:%x,p:%x,i:%x; free buf=%d %d free slc th: %d\012"
	.ascii	"\000"
	.section	.rodata.print_list_info.str1.1,"aMS",%progbits,1
.LC63:
	.ascii	"list count:%p %d\012\000"
.LC64:
	.ascii	"%d: node:%x %x %x %x, %d %d %d %d %d\012\000"
	.section	.rodata.queue_wait_first_req_completed.str1.1,"aMS",%progbits,1
.LC137:
	.ascii	"read: %x %x %x %x\012\000"
.LC138:
	.ascii	"0set buf %d,status = %x, ppa = %x lun state = %d\012"
	.ascii	"\000"
.LC139:
	.ascii	"prog end %x %x error_ecc %d %d\012\000"
.LC140:
	.ascii	"1set buf %d,status = %x, ppa = %x lun state = %d\012"
	.ascii	"\000"
.LC141:
	.ascii	"dp prog end %x %x error_ecc %d %d\012\000"
	.section	.rodata.random_seed,"a",%progbits
	.align	1
	.set	.LANCHOR54,. + 0
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
	.section	.rodata.rk_ftl_init.str1.1,"aMS",%progbits,1
.LC254:
	.ascii	"zftl_init %x\012\000"
	.section	.rodata.rknand_print_hex.str1.1,"aMS",%progbits,1
.LC98:
	.ascii	"%s %p + 0x%x:\000"
.LC99:
	.ascii	"%x \000"
.LC100:
	.ascii	"\000"
.LC101:
	.ascii	"%s\012\000"
	.section	.rodata.samsung_14nm_mlc_rr,"a",%progbits
	.set	.LANCHOR168,. + 0
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
	.set	.LANCHOR167,. + 0
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
.LC118:
	.ascii	"samsung SRR %d row=%x, status=%d\012\000"
.LC119:
	.ascii	"samsung TRR %d row=%x, status=%d\012\000"
.LC120:
	.ascii	"samsung RR %d row=%x,count %d,status=%d\012\000"
	.section	.rodata.sandisk_prog_test_bad_block.str1.1,"aMS",%progbits,1
.LC40:
	.ascii	"bad block test:%x %x\012\000"
	.section	.rodata.sblk_mlc_dump_prog.str1.1,"aMS",%progbits,1
.LC135:
	.ascii	"sblk_mlc_dump_prog wl_addr= %x ppa = %x ppa = %x\012"
	.ascii	"\000"
	.section	.rodata.sblk_prog_page.str1.1,"aMS",%progbits,1
.LC142:
	.ascii	"sblk_prog_page ppa = %x, count = %d\012\000"
	.section	.rodata.toshiba_15ref_value,"a",%progbits
	.set	.LANCHOR16,. + 0
	.type	toshiba_15ref_value, %object
	.size	toshiba_15ref_value, 95
toshiba_15ref_value:
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
	.section	.rodata.toshiba_3D_slc_value,"a",%progbits
	.set	.LANCHOR38,. + 0
	.type	toshiba_3D_slc_value, %object
	.size	toshiba_3D_slc_value, 11
toshiba_3D_slc_value:
	.byte	-117
	.byte	0
	.byte	-8
	.byte	8
	.byte	-16
	.byte	-24
	.byte	24
	.byte	-40
	.byte	40
	.byte	-56
	.byte	56
	.section	.rodata.toshiba_3D_tlc_value,"a",%progbits
	.set	.LANCHOR37,. + 0
	.type	toshiba_3D_tlc_value, %object
	.size	toshiba_3D_tlc_value, 399
toshiba_3D_tlc_value:
	.byte	-119
	.byte	-119
	.byte	-119
	.byte	-119
	.byte	-118
	.byte	-118
	.byte	-118
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	5
	.byte	-2
	.byte	-1
	.byte	0
	.byte	-3
	.byte	-2
	.byte	6
	.byte	-9
	.byte	-12
	.byte	-9
	.byte	-7
	.byte	-13
	.byte	-12
	.byte	-7
	.byte	-6
	.byte	-15
	.byte	-15
	.byte	-2
	.byte	-12
	.byte	-16
	.byte	-6
	.byte	-2
	.byte	-19
	.byte	-19
	.byte	-6
	.byte	-4
	.byte	-12
	.byte	-14
	.byte	-2
	.byte	-11
	.byte	-23
	.byte	-34
	.byte	-4
	.byte	-20
	.byte	-22
	.byte	-2
	.byte	-7
	.byte	-31
	.byte	-30
	.byte	-12
	.byte	-20
	.byte	-18
	.byte	2
	.byte	-15
	.byte	-19
	.byte	-36
	.byte	-12
	.byte	-28
	.byte	-34
	.byte	-6
	.byte	-15
	.byte	-11
	.byte	2
	.byte	-12
	.byte	-8
	.byte	-2
	.byte	2
	.byte	-3
	.byte	-7
	.byte	-10
	.byte	-4
	.byte	-8
	.byte	-6
	.byte	-6
	.byte	-11
	.byte	-27
	.byte	-38
	.byte	-16
	.byte	-12
	.byte	-2
	.byte	2
	.byte	-7
	.byte	-31
	.byte	-22
	.byte	-4
	.byte	-16
	.byte	-22
	.byte	-7
	.byte	-31
	.byte	-23
	.byte	-22
	.byte	-28
	.byte	-28
	.byte	-26
	.byte	2
	.byte	-7
	.byte	-11
	.byte	-14
	.byte	-8
	.byte	-12
	.byte	-10
	.byte	-10
	.byte	-27
	.byte	-25
	.byte	-22
	.byte	-20
	.byte	-28
	.byte	-22
	.byte	-7
	.byte	-23
	.byte	-29
	.byte	-34
	.byte	-24
	.byte	-32
	.byte	-22
	.byte	-10
	.byte	-11
	.byte	-29
	.byte	-18
	.byte	-12
	.byte	-24
	.byte	-22
	.byte	6
	.byte	1
	.byte	-3
	.byte	-6
	.byte	0
	.byte	-4
	.byte	-2
	.byte	10
	.byte	-3
	.byte	-7
	.byte	-6
	.byte	4
	.byte	-4
	.byte	-2
	.byte	-10
	.byte	-23
	.byte	-39
	.byte	-22
	.byte	-19
	.byte	-24
	.byte	-18
	.byte	-14
	.byte	-23
	.byte	-29
	.byte	-30
	.byte	-15
	.byte	-30
	.byte	-30
	.byte	-7
	.byte	-27
	.byte	-35
	.byte	-26
	.byte	-15
	.byte	-24
	.byte	-26
	.byte	6
	.byte	-11
	.byte	5
	.byte	-2
	.byte	-16
	.byte	-16
	.byte	-2
	.byte	-2
	.byte	-15
	.byte	-15
	.byte	-20
	.byte	-8
	.byte	-16
	.byte	-18
	.byte	6
	.byte	5
	.byte	-15
	.byte	-2
	.byte	-24
	.byte	-28
	.byte	-22
	.byte	10
	.byte	-15
	.byte	-3
	.byte	-30
	.byte	-8
	.byte	-24
	.byte	-30
	.byte	-10
	.byte	-27
	.byte	-19
	.byte	-30
	.byte	-12
	.byte	-16
	.byte	-10
	.byte	14
	.byte	-19
	.byte	-3
	.byte	-30
	.byte	4
	.byte	4
	.byte	6
	.byte	2
	.byte	1
	.byte	-3
	.byte	-10
	.byte	-8
	.byte	-4
	.byte	-6
	.byte	-2
	.byte	-15
	.byte	-11
	.byte	-26
	.byte	-8
	.byte	-20
	.byte	-30
	.byte	6
	.byte	-19
	.byte	-3
	.byte	-46
	.byte	0
	.byte	0
	.byte	2
	.byte	6
	.byte	9
	.byte	5
	.byte	2
	.byte	4
	.byte	8
	.byte	6
	.byte	8
	.byte	9
	.byte	9
	.byte	6
	.byte	8
	.byte	8
	.byte	6
	.byte	10
	.byte	13
	.byte	9
	.byte	6
	.byte	8
	.byte	12
	.byte	10
	.byte	2
	.byte	5
	.byte	1
	.byte	-2
	.byte	0
	.byte	0
	.byte	6
	.byte	12
	.byte	1
	.byte	13
	.byte	2
	.byte	12
	.byte	12
	.byte	14
	.byte	-12
	.byte	-14
	.byte	-20
	.byte	-18
	.byte	-16
	.byte	-16
	.byte	-14
	.byte	-12
	.byte	-10
	.byte	-21
	.byte	-14
	.byte	-12
	.byte	-12
	.byte	-10
	.byte	-12
	.byte	-18
	.byte	-22
	.byte	-24
	.byte	-18
	.byte	-18
	.byte	-18
	.byte	-12
	.byte	-14
	.byte	-23
	.byte	-20
	.byte	-20
	.byte	-20
	.byte	-20
	.byte	-12
	.byte	-24
	.byte	-24
	.byte	-30
	.byte	-24
	.byte	-28
	.byte	-28
	.byte	-12
	.byte	-26
	.byte	-25
	.byte	-34
	.byte	-24
	.byte	-24
	.byte	-24
	.byte	-12
	.byte	-13
	.byte	-26
	.byte	-20
	.byte	-14
	.byte	-18
	.byte	-18
	.byte	-12
	.byte	-15
	.byte	-27
	.byte	-22
	.byte	-20
	.byte	-24
	.byte	-22
	.byte	-12
	.byte	-21
	.byte	-28
	.byte	-28
	.byte	-24
	.byte	-26
	.byte	-24
	.byte	20
	.byte	16
	.byte	6
	.byte	10
	.byte	16
	.byte	12
	.byte	12
	.byte	16
	.byte	16
	.byte	8
	.byte	8
	.byte	12
	.byte	12
	.byte	12
	.byte	18
	.byte	18
	.byte	10
	.byte	8
	.byte	14
	.byte	14
	.byte	14
	.byte	16
	.byte	14
	.byte	6
	.byte	6
	.byte	12
	.byte	14
	.byte	8
	.byte	20
	.byte	18
	.byte	8
	.byte	6
	.byte	14
	.byte	14
	.byte	10
	.byte	20
	.byte	20
	.byte	6
	.byte	10
	.byte	10
	.byte	12
	.byte	12
	.byte	10
	.byte	13
	.byte	5
	.byte	2
	.byte	14
	.byte	8
	.byte	6
	.byte	6
	.byte	13
	.byte	9
	.byte	4
	.byte	14
	.byte	10
	.byte	10
	.byte	10
	.byte	13
	.byte	9
	.byte	6
	.byte	8
	.byte	12
	.byte	10
	.byte	2
	.byte	5
	.byte	1
	.byte	-2
	.byte	0
	.byte	0
	.byte	6
	.byte	12
	.byte	1
	.byte	13
	.byte	2
	.byte	12
	.byte	12
	.byte	14
	.section	.rodata.toshiba_3d_read_retrial.str1.1,"aMS",%progbits,1
.LC114:
	.ascii	"toshiba SRR %d row=%x, status=%d\012\000"
.LC115:
	.ascii	"toshiba TRR %d row=%x, status=%d\012\000"
.LC116:
	.ascii	"toshiba RR %d row=%x,count %d,status=%d\012\000"
	.section	.rodata.toshiba_A19ref_value,"a",%progbits
	.set	.LANCHOR14,. + 0
	.type	toshiba_A19ref_value, %object
	.size	toshiba_A19ref_value, 45
toshiba_A19ref_value:
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
	.section	.rodata.toshiba_ref_value,"a",%progbits
	.set	.LANCHOR17,. + 0
	.type	toshiba_ref_value, %object
	.size	toshiba_ref_value, 8
toshiba_ref_value:
	.byte	0
	.byte	4
	.byte	124
	.byte	120
	.byte	116
	.byte	8
	.byte	12
	.byte	112
	.section	.rodata.ymtc_3D_slc_value,"a",%progbits
	.set	.LANCHOR42,. + 0
	.type	ymtc_3D_slc_value, %object
	.size	ymtc_3D_slc_value, 10
ymtc_3D_slc_value:
	.byte	0
	.byte	-8
	.byte	8
	.byte	-16
	.byte	-20
	.byte	24
	.byte	-26
	.byte	40
	.byte	-12
	.byte	56
	.section	.rodata.ymtc_3D_tlc_value,"a",%progbits
	.set	.LANCHOR41,. + 0
	.type	ymtc_3D_tlc_value, %object
	.size	ymtc_3D_tlc_value, 357
ymtc_3D_tlc_value:
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	-10
	.byte	-10
	.byte	-6
	.byte	-6
	.byte	-2
	.byte	2
	.byte	2
	.byte	-6
	.byte	-6
	.byte	-4
	.byte	-4
	.byte	-4
	.byte	-6
	.byte	-8
	.byte	6
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	-2
	.byte	-2
	.byte	-2
	.byte	-4
	.byte	-4
	.byte	-6
	.byte	-6
	.byte	-6
	.byte	-6
	.byte	-6
	.byte	-6
	.byte	-6
	.byte	-6
	.byte	-11
	.byte	-2
	.byte	2
	.byte	4
	.byte	4
	.byte	6
	.byte	6
	.byte	6
	.byte	-6
	.byte	-6
	.byte	-6
	.byte	-6
	.byte	-6
	.byte	-8
	.byte	-14
	.byte	-6
	.byte	-15
	.byte	-11
	.byte	2
	.byte	-12
	.byte	-8
	.byte	-2
	.byte	2
	.byte	-3
	.byte	-7
	.byte	-10
	.byte	-4
	.byte	-8
	.byte	-6
	.byte	-18
	.byte	-18
	.byte	-14
	.byte	-14
	.byte	-10
	.byte	-5
	.byte	-5
	.byte	-14
	.byte	-14
	.byte	-12
	.byte	-12
	.byte	-12
	.byte	-13
	.byte	-15
	.byte	-2
	.byte	-8
	.byte	-8
	.byte	-8
	.byte	-8
	.byte	-7
	.byte	-7
	.byte	-10
	.byte	-10
	.byte	-10
	.byte	-12
	.byte	-12
	.byte	-13
	.byte	-13
	.byte	-14
	.byte	-14
	.byte	-14
	.byte	-14
	.byte	-14
	.byte	-13
	.byte	-18
	.byte	-10
	.byte	-6
	.byte	-4
	.byte	-4
	.byte	-2
	.byte	-1
	.byte	-1
	.byte	-14
	.byte	-14
	.byte	-14
	.byte	-14
	.byte	-14
	.byte	-15
	.byte	-21
	.byte	-12
	.byte	-11
	.byte	-7
	.byte	-7
	.byte	-3
	.byte	1
	.byte	1
	.byte	-8
	.byte	-7
	.byte	-5
	.byte	-5
	.byte	-5
	.byte	-7
	.byte	-9
	.byte	4
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-1
	.byte	-4
	.byte	-3
	.byte	-3
	.byte	-5
	.byte	-5
	.byte	-7
	.byte	-7
	.byte	-8
	.byte	-7
	.byte	-7
	.byte	-7
	.byte	-7
	.byte	-7
	.byte	-12
	.byte	-4
	.byte	1
	.byte	3
	.byte	3
	.byte	5
	.byte	5
	.byte	5
	.byte	-8
	.byte	-7
	.byte	-7
	.byte	-7
	.byte	-7
	.byte	-9
	.byte	-15
	.byte	2
	.byte	-7
	.byte	-11
	.byte	-14
	.byte	-8
	.byte	-12
	.byte	-10
	.byte	6
	.byte	1
	.byte	-3
	.byte	-6
	.byte	0
	.byte	-4
	.byte	-2
	.byte	10
	.byte	-3
	.byte	-7
	.byte	-6
	.byte	4
	.byte	-4
	.byte	-2
	.byte	-10
	.byte	-23
	.byte	-39
	.byte	-22
	.byte	-19
	.byte	-24
	.byte	-18
	.byte	-7
	.byte	-27
	.byte	-35
	.byte	-26
	.byte	-15
	.byte	-24
	.byte	-26
	.byte	6
	.byte	-11
	.byte	5
	.byte	-2
	.byte	-16
	.byte	-16
	.byte	-2
	.byte	-2
	.byte	-15
	.byte	-15
	.byte	-20
	.byte	-8
	.byte	-16
	.byte	-18
	.byte	2
	.byte	1
	.byte	-3
	.byte	-10
	.byte	-8
	.byte	-4
	.byte	-6
	.byte	-2
	.byte	-15
	.byte	-11
	.byte	-26
	.byte	-8
	.byte	-20
	.byte	-30
	.byte	6
	.byte	-19
	.byte	-3
	.byte	-46
	.byte	0
	.byte	0
	.byte	2
	.byte	6
	.byte	9
	.byte	5
	.byte	2
	.byte	4
	.byte	8
	.byte	6
	.byte	8
	.byte	9
	.byte	9
	.byte	6
	.byte	8
	.byte	8
	.byte	6
	.byte	10
	.byte	13
	.byte	9
	.byte	6
	.byte	8
	.byte	12
	.byte	10
	.byte	2
	.byte	5
	.byte	1
	.byte	-2
	.byte	0
	.byte	0
	.byte	6
	.byte	12
	.byte	1
	.byte	13
	.byte	2
	.byte	12
	.byte	12
	.byte	14
	.byte	-12
	.byte	-14
	.byte	-20
	.byte	-18
	.byte	-16
	.byte	-16
	.byte	-14
	.byte	-12
	.byte	-10
	.byte	-21
	.byte	-14
	.byte	-12
	.byte	-12
	.byte	-10
	.byte	-12
	.byte	-18
	.byte	-22
	.byte	-24
	.byte	-18
	.byte	-18
	.byte	-18
	.byte	-12
	.byte	-14
	.byte	-23
	.byte	-20
	.byte	-20
	.byte	-20
	.byte	-20
	.byte	16
	.byte	16
	.byte	8
	.byte	8
	.byte	12
	.byte	12
	.byte	12
	.byte	18
	.byte	18
	.byte	10
	.byte	8
	.byte	14
	.byte	14
	.byte	14
	.byte	16
	.byte	14
	.byte	6
	.byte	6
	.byte	12
	.byte	14
	.byte	8
	.byte	10
	.byte	13
	.byte	5
	.byte	2
	.byte	14
	.byte	8
	.byte	6
	.byte	6
	.byte	13
	.byte	9
	.byte	4
	.byte	14
	.byte	10
	.byte	10
	.byte	10
	.byte	13
	.byte	9
	.byte	6
	.byte	8
	.byte	12
	.byte	10
	.byte	2
	.byte	5
	.byte	1
	.byte	-2
	.byte	0
	.byte	0
	.byte	6
	.byte	12
	.byte	1
	.byte	13
	.byte	2
	.byte	12
	.byte	12
	.byte	14
	.section	.rodata.ymtc_3d_read_retrial.str1.1,"aMS",%progbits,1
.LC117:
	.ascii	"YMTC RR %d row=%x,count %d,status=%d\012\000"
	.section	.rodata.ymtc_flash_tlc_page_prog.str1.1,"aMS",%progbits,1
.LC131:
	.ascii	"ymtc_flash_tlc_page_prog page_addr = %x status = %x"
	.ascii	"\012\000"
	.section	.rodata.zftl_discard.str1.1,"aMS",%progbits,1
.LC256:
	.ascii	"ftl_discard:(%x, %x, %x, %x)\012\000"
	.section	.rodata.zftl_do_gc.str1.1,"aMS",%progbits,1
.LC239:
	.ascii	"gc %d: %d %d %d %d %d %d %d\012\000"
.LC240:
	.ascii	"GC_STATE_SCAN_ALL_PAGE = %x, vpn0 = %d, vpn1 = %d\012"
	.ascii	"\000"
.LC241:
	.ascii	"gc free %x, %d\012\000"
	.section	.rodata.zftl_gc_get_free_sblk.str1.1,"aMS",%progbits,1
.LC59:
	.ascii	"swl_tlc_free_mini_ec_blk alloc sblk %x\012\000"
.LC60:
	.ascii	"zftl_get_free_sblk %x %d, %p %d %d\012\000"
.LC61:
	.ascii	"zftl_gc_get_free_sblk %x %x %x, %d %d %d\012\000"
	.section	.rodata.zftl_get_free_sblk.str1.1,"aMS",%progbits,1
.LC62:
	.ascii	"swl_slc_free_mini_ec_blk alloc sblk %x\012\000"
	.section	.rodata.zftl_init.str1.1,"aMS",%progbits,1
.LC242:
	.ascii	"FTL version: 6.0.24 20210107\000"
.LC243:
	.ascii	"_c_user_data_density := %d\012\000"
.LC244:
	.ascii	"_c_totle_phy_density := %d\012\000"
.LC245:
	.ascii	"_c_totle_log_page := %d\012\000"
.LC246:
	.ascii	"_c_totle_data_density := %d\012\000"
.LC247:
	.ascii	"_c_ftl_pm_page_num := %d\012\000"
.LC248:
	.ascii	"_c_ftl_byte_pre_page := %d\012\000"
.LC249:
	.ascii	"_c_max_pm_sblk := %d\012\000"
.LC250:
	.ascii	"_min_slc_super_block := %d\012\000"
.LC251:
	.ascii	"_max_xlc_super_block := %d\012\000"
.LC252:
	.ascii	"gp_ftl_ext_info %p %p %p\012\000"
.LC253:
	.ascii	"flash info size: %d %d %d\012\000"
	.section	.rodata.zftl_read.str1.1,"aMS",%progbits,1
.LC228:
	.ascii	"ftl_read %x %x %x\012\000"
.LC229:
	.ascii	"ftl_read refresh =%x, lpa = %x, ppa= %x\012\000"
.LC230:
	.ascii	"id=%d, status = %x, lpa = %x, ppa = %x spare = %x %"
	.ascii	"x %x %x\012\000"
	.section	.rodata.zftl_sblk_list_init.str1.1,"aMS",%progbits,1
.LC91:
	.ascii	"free blk vpn error: %x %x\012\000"
	.section	.rodata.zftl_write.str1.1,"aMS",%progbits,1
.LC255:
	.ascii	"ftlwrite %x %x %x %x\012\000"
	.hidden	free
