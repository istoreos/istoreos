/*
 * Copyright (c) 2016-2017, Fuzhou Rockchip Electronics Co., Ltd
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * date: 2021-01-07
 */
	.arch armv8-a
	.file	"rk_zftl_arm_v8.S"
	.section	.text.flash_mem_cmp8,"ax",@progbits
	.align	2
	.type	flash_mem_cmp8, %function
flash_mem_cmp8:
	mov	x3, 0
.L2:
	mov	w4, w3
	cmp	w3, w2
	bcc	.L4
	mov	w0, 0
	ret
.L4:
	ldrb	w5, [x0, x3]
	add	x3, x3, 1
	add	x6, x1, x3
	ldrb	w6, [x6, -1]
	cmp	w6, w5
	beq	.L2
	add	w0, w4, 1
	ret
	.size	flash_mem_cmp8, .-flash_mem_cmp8
	.section	.text.slc_phy_page_address_calc,"ax",@progbits
	.align	2
	.type	slc_phy_page_address_calc, %function
slc_phy_page_address_calc:
	adrp	x1, .LANCHOR0
	adrp	x2, .LANCHOR1
	ldrb	w1, [x1, #:lo12:.LANCHOR0]
	cbz	w1, .L7
	ldrb	w1, [x2, #:lo12:.LANCHOR1]
	cbz	w1, .L8
.L7:
	adrp	x1, .LANCHOR2
	ldrb	w2, [x2, #:lo12:.LANCHOR1]
	ldrh	w3, [x1, #:lo12:.LANCHOR2]
	udiv	w1, w0, w3
	mul	w1, w1, w3
	sub	w0, w0, w1
	cbz	w2, .L9
	add	w0, w1, w0, lsl 1
	ret
.L9:
	adrp	x2, .LANCHOR3
	add	x2, x2, :lo12:.LANCHOR3
	ldrh	w0, [x2, w0, uxtw 1]
	add	w0, w0, w1
.L8:
	ret
	.size	slc_phy_page_address_calc, .-slc_phy_page_address_calc
	.section	.text._list_remove_node,"ax",@progbits
	.align	2
	.type	_list_remove_node, %function
_list_remove_node:
	stp	x29, x30, [sp, -64]!
	and	w1, w1, 65535
	mov	w3, 6
	add	x29, sp, 0
	stp	x21, x22, [sp, 32]
	adrp	x21, .LANCHOR4
	stp	x19, x20, [sp, 16]
	umull	x20, w1, w3
	stp	x23, x24, [sp, 48]
	mov	w1, 65535
	ldr	x24, [x21, #:lo12:.LANCHOR4]
	add	x19, x24, x20
	ldrh	w4, [x24, x20]
	ldrh	w3, [x19, 2]
	cmp	w4, w1
	ldr	x1, [x0]
	bne	.L17
	cmp	w3, w4
	bne	.L17
	cmp	x19, x1
	bne	.L16
.L17:
	mov	x22, x0
	mov	x23, x2
	mov	w0, 65535
	cmp	w3, w0
	bne	.L19
	cmp	x19, x1
	beq	.L19
	adrp	x1, .LANCHOR5
	adrp	x0, .LC0
	mov	w2, 202
	add	x1, x1, :lo12:.LANCHOR5
	add	x0, x0, :lo12:.LC0
	bl	printf
.L19:
	ldr	x0, [x22]
	ldrh	w3, [x24, x20]
	cmp	x19, x0
	mov	w0, 65535
	bne	.L20
	cmp	w3, w0
	bne	.L21
	str	xzr, [x22]
.L22:
	mov	w0, -1
	strh	w0, [x24, x20]
	strh	w0, [x19, 2]
	ldrh	w0, [x23]
	sub	w0, w0, #1
	strh	w0, [x23]
.L16:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
.L21:
	ldr	x0, [x21, #:lo12:.LANCHOR4]
	mov	w1, 6
	umaddl	x3, w3, w1, x0
	mov	w0, -1
	str	x3, [x22]
	strh	w0, [x3, 2]
	b	.L22
.L20:
	cmp	w3, w0
	ldrh	w0, [x19, 2]
	bne	.L23
	cmp	w0, w3
	beq	.L22
	mov	w1, 6
	mov	w2, -1
	umull	x0, w0, w1
	ldr	x1, [x21, #:lo12:.LANCHOR4]
	strh	w2, [x1, x0]
	b	.L22
.L23:
	ldr	x1, [x21, #:lo12:.LANCHOR4]
	mov	w2, 6
	umaddl	x4, w3, w2, x1
	strh	w0, [x4, 2]
	ldrh	w0, [x19, 2]
	umull	x0, w0, w2
	strh	w3, [x1, x0]
	b	.L22
	.size	_list_remove_node, .-_list_remove_node
	.section	.text.hynix_set_rr_para,"ax",@progbits
	.align	2
	.type	hynix_set_rr_para, %function
hynix_set_rr_para:
	stp	x29, x30, [sp, -64]!
	adrp	x2, .LANCHOR6
	and	w1, w1, 255
	adrp	x3, .LANCHOR7
	add	x29, sp, 0
	ldr	x2, [x2, #:lo12:.LANCHOR6]
	and	w0, w0, 255
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	add	x21, x2, 112
	str	x23, [sp, 48]
	add	x23, x2, 128
	ldr	x19, [x3, #:lo12:.LANCHOR7]
	ldrb	w22, [x2, 113]
	ldrb	w2, [x2, 112]
	cmp	w2, 8
	mov	x2, 32
	umaddl	x1, w1, w22, x2
	beq	.L26
	mov	w2, 160
	umaddl	x1, w2, w0, x1
.L26:
	ubfiz	x0, x0, 8, 8
	add	x21, x21, x1
	add	x19, x19, x0
	mov	x20, 0
	mov	w0, 54
	str	w0, [x19, 2056]
.L28:
	cmp	w22, w20, uxtb
	bhi	.L29
	ldp	x21, x22, [sp, 32]
	mov	w0, 22
	ldr	x23, [sp, 48]
	str	w0, [x19, 2056]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 64
	ret
.L29:
	ldrb	w0, [x23, x20]
	str	w0, [x19, 2052]
	mov	x0, 1
	bl	udelay
	ldrsb	w0, [x21, x20]
	add	x20, x20, 1
	str	w0, [x19, 2048]
	b	.L28
	.size	hynix_set_rr_para, .-hynix_set_rr_para
	.section	.text._insert_free_list,"ax",@progbits
	.align	2
	.type	_insert_free_list, %function
_insert_free_list:
	adrp	x3, .LANCHOR8
	and	w1, w1, 65535
	ldrh	w3, [x3, #:lo12:.LANCHOR8]
	cmp	w3, w1
	bls	.L31
	ldrh	w3, [x2]
	mov	w8, 6
	ldr	x7, [x0]
	add	w3, w3, 1
	strh	w3, [x2]
	adrp	x2, .LANCHOR4
	umull	x12, w1, w8
	ldr	x5, [x2, #:lo12:.LANCHOR4]
	mov	w2, -1
	add	x6, x5, x12
	strh	w2, [x6, 2]
	strh	w2, [x5, x12]
	cbnz	x7, .L33
.L38:
	str	x6, [x0]
	ret
.L33:
	adrp	x2, .LANCHOR9
	adrp	x3, .LANCHOR10
	mov	w10, w8
	mov	w15, 65535
	ldr	x11, [x2, #:lo12:.LANCHOR9]
	ubfiz	x2, x1, 2, 16
	ldrh	w14, [x3, #:lo12:.LANCHOR10]
	mov	x3, -6148914691236517206
	movk	x3, 0xaaab, lsl 0
	ldr	w4, [x11, x2]
	ldrh	w2, [x11, x2]
	ubfx	x4, x4, 11, 8
	and	w2, w2, 2047
	madd	w4, w14, w4, w2
	sub	x2, x7, x5
	asr	x2, x2, 1
	and	w4, w4, 65535
	mul	x2, x2, x3
	mov	x3, x7
	and	w2, w2, 65535
.L36:
	ubfiz	x13, x2, 2, 16
	ldr	w8, [x11, x13]
	ldrh	w13, [x11, x13]
	ubfx	x8, x8, 11, 8
	and	w13, w13, 2047
	madd	w8, w14, w8, w13
	cmp	w4, w8, uxth
	bls	.L34
	ldrh	w8, [x3]
	cmp	w8, w15
	bne	.L35
	strh	w2, [x6, 2]
	strh	w1, [x3]
	ret
.L35:
	umaddl	x3, w8, w10, x5
	mov	w2, w8
	b	.L36
.L34:
	ldrh	w4, [x3, 2]
	cmp	x7, x3
	strh	w4, [x6, 2]
	strh	w2, [x5, x12]
	bne	.L37
	strh	w1, [x7, 2]
	b	.L38
.L37:
	ldrh	w0, [x3, 2]
	mov	w2, 6
	umull	x0, w0, w2
	strh	w1, [x5, x0]
	strh	w1, [x3, 2]
.L31:
	ret
	.size	_insert_free_list, .-_insert_free_list
	.section	.text._insert_data_list,"ax",@progbits
	.align	2
	.type	_insert_data_list, %function
_insert_data_list:
	adrp	x3, .LANCHOR8
	and	w1, w1, 65535
	ldrh	w4, [x3, #:lo12:.LANCHOR8]
	cmp	w4, w1
	bls	.L61
	mov	x5, x3
	ldrh	w3, [x2]
	mov	w13, 6
	ldr	x12, [x0]
	add	w3, w3, 1
	strh	w3, [x2]
	adrp	x2, .LANCHOR4
	umull	x13, w1, w13
	ldr	x10, [x2, #:lo12:.LANCHOR4]
	mov	w2, -1
	add	x11, x10, x13
	strh	w2, [x11, 2]
	strh	w2, [x10, x13]
	cbnz	x12, .L42
	str	x11, [x0]
	ret
.L42:
	stp	x29, x30, [sp, -32]!
	adrp	x2, .LANCHOR11
	uxtw	x3, w1
	adrp	x6, .LANCHOR10
	add	x29, sp, 0
	ldr	x15, [x2, #:lo12:.LANCHOR11]
	adrp	x2, .LANCHOR9
	ldrh	w4, [x11, 4]
	ldr	x14, [x2, #:lo12:.LANCHOR9]
	stp	x19, x20, [sp, 16]
	ldrh	w8, [x15, x3, lsl 1]
	lsl	x3, x3, 2
	ldrh	w16, [x6, #:lo12:.LANCHOR10]
	ldr	w2, [x14, x3]
	mul	w8, w8, w4
	ldrh	w3, [x14, x3]
	ubfx	x2, x2, 11, 8
	and	w3, w3, 2047
	cbz	w8, .L43
	madd	w2, w16, w2, w3
	add	w8, w8, w2, uxth
.L43:
	sub	x2, x12, x10
	mov	x3, -6148914691236517206
	asr	x2, x2, 1
	movk	x3, 0xaaab, lsl 0
	cmp	w4, 0
	ldrh	w19, [x5, #:lo12:.LANCHOR8]
	csinv	w8, w8, wzr, ne
	mov	x7, x12
	mul	x2, x2, x3
	mov	w4, 0
	mov	w20, 65535
	mov	w30, 6
	and	w2, w2, 65535
.L49:
	add	w4, w4, 1
	and	w4, w4, 65535
	cmp	w4, w19
	bhi	.L39
	cmp	w1, w2
	beq	.L39
	uxtw	x6, w2
	ldrh	w17, [x7, 4]
	ldrh	w3, [x15, x6, lsl 1]
	lsl	x6, x6, 2
	ldr	w5, [x14, x6]
	mul	w3, w3, w17
	ldrh	w6, [x14, x6]
	ubfx	x5, x5, 11, 8
	and	w6, w6, 2047
	cbz	w3, .L46
	madd	w5, w16, w5, w6
	add	w3, w3, w5, uxth
.L46:
	cbz	w17, .L47
	cmp	w8, w3
	bls	.L47
	ldrh	w3, [x7]
	cmp	w3, w20
	bne	.L48
	strh	w2, [x11, 2]
	strh	w1, [x7]
.L39:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L48:
	umaddl	x7, w3, w30, x10
	mov	w2, w3
	b	.L49
.L47:
	ldrh	w3, [x7, 2]
	cmp	x12, x7
	strh	w3, [x11, 2]
	strh	w2, [x10, x13]
	bne	.L50
	strh	w1, [x12, 2]
	str	x11, [x0]
	b	.L39
.L50:
	ldrh	w0, [x7, 2]
	mov	w2, 6
	umull	x0, w0, w2
	strh	w1, [x10, x0]
	strh	w1, [x7, 2]
	b	.L39
.L61:
	ret
	.size	_insert_data_list, .-_insert_data_list
	.section	.text._list_update_data_list,"ax",@progbits
	.align	2
	.type	_list_update_data_list, %function
_list_update_data_list:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	and	w19, w1, 65535
	adrp	x1, .LANCHOR12
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	ldr	x1, [x1, #:lo12:.LANCHOR12]
	ldrh	w3, [x1, 16]
	str	x25, [sp, 64]
	cmp	w3, w19
	beq	.L63
	ldrh	w3, [x1, 48]
	cmp	w3, w19
	beq	.L63
	ldrh	w1, [x1, 80]
	cmp	w1, w19
	beq	.L63
	adrp	x1, .LANCHOR4
	mov	w22, 6
	ldr	x3, [x0]
	mov	x25, x1
	umull	x22, w19, w22
	ldr	x24, [x1, #:lo12:.LANCHOR4]
	add	x23, x24, x22
	cmp	x23, x3
	beq	.L63
	mov	x20, x0
	ldrh	w0, [x23, 2]
	mov	w1, 65535
	mov	x21, x2
	cmp	w0, w1
	bne	.L67
	ldrh	w1, [x24, x22]
	cmp	w1, w0
	bne	.L67
	adrp	x1, .LANCHOR13
	adrp	x0, .LC0
	mov	w2, 273
	add	x1, x1, :lo12:.LANCHOR13
	add	x0, x0, :lo12:.LC0
	bl	printf
.L67:
	ldrh	w1, [x23, 2]
	mov	w0, 65535
	cmp	w1, w0
	bne	.L68
	ldrh	w0, [x24, x22]
	cmp	w0, w1
	beq	.L63
.L68:
	adrp	x0, .LANCHOR11
	ubfiz	x2, x19, 1, 16
	mov	x5, -6148914691236517206
	mov	w4, -1
	ldr	x0, [x0, #:lo12:.LANCHOR11]
	movk	x5, 0xaaab, lsl 0
	ldrh	w3, [x0, x2]
	ldrh	w2, [x23, 4]
	cmp	w2, 0
	mul	w3, w3, w2
	mov	w2, 6
	umull	x1, w1, w2
	csel	w3, w3, w4, ne
	asr	x2, x1, 1
	mul	x2, x2, x5
	ldrh	w0, [x0, x2, lsl 1]
	ldr	x2, [x25, #:lo12:.LANCHOR4]
	add	x1, x2, x1
	ldrh	w1, [x1, 4]
	cmp	w1, 0
	mul	w0, w0, w1
	csel	w0, w0, w4, ne
	cmp	w3, w0
	bcs	.L63
	mov	x2, x21
	mov	w1, w19
	mov	x0, x20
	bl	_list_remove_node
	mov	x2, x21
	mov	w1, w19
	mov	x0, x20
	ldr	x25, [sp, 64]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 80
	b	_insert_data_list
.L63:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldr	x25, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.size	_list_update_data_list, .-_list_update_data_list
	.section	.text.nandc_de_cs.constprop.32,"ax",@progbits
	.align	2
	.type	nandc_de_cs.constprop.32, %function
nandc_de_cs.constprop.32:
	adrp	x0, .LANCHOR7
	ldr	x1, [x0, #:lo12:.LANCHOR7]
	ldr	w0, [x1]
	and	w0, w0, -256
	and	w0, w0, -131073
	str	w0, [x1]
	ret
	.size	nandc_de_cs.constprop.32, .-nandc_de_cs.constprop.32
	.section	.text.flash_read_status,"ax",@progbits
	.align	2
	.global	flash_read_status
	.type	flash_read_status, %function
flash_read_status:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	w0, 112
	str	w0, [x19, 8]
	mov	x0, 1
	bl	udelay
	ldr	w0, [x19]
	ldr	x19, [sp, 16]
	and	w0, w0, 255
	ldp	x29, x30, [sp], 32
	ret
	.size	flash_read_status, .-flash_read_status
	.section	.text.toshiba_set_rr_para,"ax",@progbits
	.align	2
	.global	toshiba_set_rr_para
	.type	toshiba_set_rr_para, %function
toshiba_set_rr_para:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	str	x27, [sp, 80]
	and	w27, w1, 255
	add	w2, w27, 1
	stp	x21, x22, [sp, 32]
	mov	x21, x0
	mov	w0, 5
	stp	x19, x20, [sp, 16]
	adrp	x20, .LANCHOR14
	umull	x2, w2, w0
	stp	x23, x24, [sp, 48]
	adrp	x0, .LANCHOR15
	add	x20, x20, :lo12:.LANCHOR14
	add	x24, x0, :lo12:.LANCHOR15
	stp	x25, x26, [sp, 64]
	adrp	x23, .LANCHOR18
	adrp	x25, .LANCHOR16
	adrp	x26, .LANCHOR17
	add	x23, x23, :lo12:.LANCHOR18
	add	x25, x25, :lo12:.LANCHOR16
	add	x26, x26, :lo12:.LANCHOR17
	add	x20, x20, x2
	add	x24, x24, x2
	mov	x22, x0
	mov	x19, 0
.L78:
	ldrb	w0, [x23]
	cmp	w0, w19
	bhi	.L82
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldr	x27, [sp, 80]
	ldp	x29, x30, [sp], 96
	ret
.L82:
	mov	w0, 85
	str	w0, [x21, 8]
	add	x0, x22, :lo12:.LANCHOR15
	ldrsb	w0, [x19, x0]
	str	w0, [x21, 4]
	mov	x0, 1
	bl	udelay
	ldrb	w0, [x25]
	cmp	w0, 34
	bne	.L79
	ldrsb	w0, [x24, x19]
.L84:
	add	x19, x19, 1
	str	w0, [x21]
	b	.L78
.L79:
	cmp	w0, 35
	bne	.L81
	ldrsb	w0, [x20, x19]
	b	.L84
.L81:
	ldrsb	w0, [x26, w27, sxtw]
	b	.L84
	.size	toshiba_set_rr_para, .-toshiba_set_rr_para
	.section	.text.hynix_reconfig_rr_para,"ax",@progbits
	.align	2
	.global	hynix_reconfig_rr_para
	.type	hynix_reconfig_rr_para, %function
hynix_reconfig_rr_para:
	adrp	x1, .LANCHOR16
	ldrb	w1, [x1, #:lo12:.LANCHOR16]
	sub	w1, w1, #1
	and	w1, w1, 255
	cmp	w1, 7
	bhi	.L91
	stp	x29, x30, [sp, -32]!
	and	w0, w0, 255
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	adrp	x20, .LANCHOR6
	sxtw	x19, w0
	ldr	x1, [x20, #:lo12:.LANCHOR6]
	add	x1, x1, x19
	ldrb	w1, [x1, 120]
	cbz	w1, .L85
	mov	w1, 0
	bl	hynix_set_rr_para
	ldr	x0, [x20, #:lo12:.LANCHOR6]
	add	x0, x0, x19
	strb	wzr, [x0, 120]
.L85:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L91:
	ret
	.size	hynix_reconfig_rr_para, .-hynix_reconfig_rr_para
	.section	.text.nand_flash_print_info,"ax",@progbits
	.align	2
	.global	nand_flash_print_info
	.type	nand_flash_print_info, %function
nand_flash_print_info:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	adrp	x19, .LANCHOR19
	ldr	w0, [x19, #:lo12:.LANCHOR19]
	tbz	x0, 12, .L95
	adrp	x1, .LANCHOR20
	adrp	x0, .LC1
	add	x1, x1, :lo12:.LANCHOR20
	add	x0, x0, :lo12:.LC1
	bl	printf
.L95:
	ldr	w0, [x19, #:lo12:.LANCHOR19]
	tbz	x0, 12, .L96
	adrp	x0, .LANCHOR21
	ldr	x0, [x0, #:lo12:.LANCHOR21]
	ldrb	w6, [x0, 6]
	ldrb	w5, [x0, 5]
	ldrb	w4, [x0, 4]
	ldrb	w3, [x0, 3]
	ldrb	w2, [x0, 2]
	ldrb	w1, [x0, 1]
	adrp	x0, .LC2
	add	x0, x0, :lo12:.LC2
	bl	printf
.L96:
	ldr	w0, [x19, #:lo12:.LANCHOR19]
	tbz	x0, 12, .L97
	adrp	x0, .LANCHOR21
	ldr	x0, [x0, #:lo12:.LANCHOR21]
	ldrb	w1, [x0, 8]
	adrp	x0, .LC3
	add	x0, x0, :lo12:.LC3
	bl	printf
.L97:
	ldr	w0, [x19, #:lo12:.LANCHOR19]
	tbz	x0, 12, .L98
	adrp	x0, .LANCHOR21
	ldr	x0, [x0, #:lo12:.LANCHOR21]
	ldrb	w1, [x0, 9]
	adrp	x0, .LC4
	add	x0, x0, :lo12:.LC4
	bl	printf
.L98:
	ldr	w0, [x19, #:lo12:.LANCHOR19]
	tbz	x0, 12, .L99
	adrp	x0, .LANCHOR21
	ldr	x0, [x0, #:lo12:.LANCHOR21]
	ldrh	w1, [x0, 10]
	adrp	x0, .LC5
	add	x0, x0, :lo12:.LC5
	bl	printf
.L99:
	ldr	w0, [x19, #:lo12:.LANCHOR19]
	tbz	x0, 12, .L100
	adrp	x0, .LANCHOR21
	ldr	x0, [x0, #:lo12:.LANCHOR21]
	ldrb	w1, [x0, 12]
	adrp	x0, .LC6
	add	x0, x0, :lo12:.LC6
	bl	printf
.L100:
	ldr	w0, [x19, #:lo12:.LANCHOR19]
	tbz	x0, 12, .L101
	adrp	x0, .LANCHOR21
	ldr	x0, [x0, #:lo12:.LANCHOR21]
	ldrb	w1, [x0, 13]
	adrp	x0, .LC7
	add	x0, x0, :lo12:.LC7
	bl	printf
.L101:
	ldr	w0, [x19, #:lo12:.LANCHOR19]
	tbz	x0, 12, .L102
	adrp	x0, .LANCHOR21
	ldr	x0, [x0, #:lo12:.LANCHOR21]
	ldrh	w1, [x0, 14]
	adrp	x0, .LC8
	add	x0, x0, :lo12:.LC8
	bl	printf
.L102:
	ldr	w0, [x19, #:lo12:.LANCHOR19]
	tbz	x0, 12, .L103
	adrp	x0, .LANCHOR21
	ldr	x0, [x0, #:lo12:.LANCHOR21]
	ldrb	w1, [x0, 23]
	adrp	x0, .LC9
	add	x0, x0, :lo12:.LC9
	bl	printf
.L103:
	ldr	w0, [x19, #:lo12:.LANCHOR19]
	tbz	x0, 12, .L104
	adrp	x0, .LANCHOR21
	ldr	x0, [x0, #:lo12:.LANCHOR21]
	ldrb	w1, [x0, 18]
	adrp	x0, .LC10
	add	x0, x0, :lo12:.LC10
	bl	printf
.L104:
	ldr	w0, [x19, #:lo12:.LANCHOR19]
	tbz	x0, 12, .L105
	adrp	x0, .LANCHOR21
	ldr	x0, [x0, #:lo12:.LANCHOR21]
	ldrb	w1, [x0, 19]
	adrp	x0, .LC11
	add	x0, x0, :lo12:.LC11
	bl	printf
.L105:
	ldr	w0, [x19, #:lo12:.LANCHOR19]
	tbz	x0, 12, .L106
	adrp	x0, .LANCHOR21
	ldr	x0, [x0, #:lo12:.LANCHOR21]
	ldrb	w1, [x0, 20]
	adrp	x0, .LC12
	add	x0, x0, :lo12:.LC12
	bl	printf
.L106:
	ldr	w0, [x19, #:lo12:.LANCHOR19]
	tbz	x0, 12, .L107
	adrp	x0, .LANCHOR22
	ldrb	w1, [x0, #:lo12:.LANCHOR22]
	adrp	x0, .LC13
	add	x0, x0, :lo12:.LC13
	bl	printf
.L107:
	ldr	w0, [x19, #:lo12:.LANCHOR19]
	tbz	x0, 12, .L108
	adrp	x0, .LANCHOR21
	ldr	x0, [x0, #:lo12:.LANCHOR21]
	ldrb	w1, [x0, 22]
	adrp	x0, .LC14
	add	x0, x0, :lo12:.LC14
	bl	printf
.L108:
	ldr	w0, [x19, #:lo12:.LANCHOR19]
	tbz	x0, 12, .L109
	adrp	x0, .LANCHOR23
	ldrb	w1, [x0, #:lo12:.LANCHOR23]
	adrp	x0, .LC15
	add	x0, x0, :lo12:.LC15
	bl	printf
.L109:
	ldr	w0, [x19, #:lo12:.LANCHOR19]
	tbz	x0, 12, .L110
	adrp	x0, .LANCHOR21
	ldr	x0, [x0, #:lo12:.LANCHOR21]
	ldrb	w1, [x0, 16]
	adrp	x0, .LC16
	add	x0, x0, :lo12:.LC16
	and	w1, w1, 1
	bl	printf
.L110:
	ldr	w0, [x19, #:lo12:.LANCHOR19]
	tbz	x0, 12, .L111
	adrp	x0, .LANCHOR21
	ldr	x0, [x0, #:lo12:.LANCHOR21]
	ldrh	w1, [x0, 16]
	adrp	x0, .LC17
	add	x0, x0, :lo12:.LC17
	ubfx	x1, x1, 1, 1
	bl	printf
.L111:
	ldr	w0, [x19, #:lo12:.LANCHOR19]
	tbz	x0, 12, .L112
	adrp	x0, .LANCHOR21
	ldr	x0, [x0, #:lo12:.LANCHOR21]
	ldrh	w1, [x0, 16]
	adrp	x0, .LC18
	add	x0, x0, :lo12:.LC18
	ubfx	x1, x1, 2, 1
	bl	printf
.L112:
	ldr	w0, [x19, #:lo12:.LANCHOR19]
	tbz	x0, 12, .L113
	adrp	x0, .LANCHOR21
	ldr	x0, [x0, #:lo12:.LANCHOR21]
	ldrh	w1, [x0, 16]
	adrp	x0, .LC19
	add	x0, x0, :lo12:.LC19
	ubfx	x1, x1, 3, 1
	bl	printf
.L113:
	ldr	w0, [x19, #:lo12:.LANCHOR19]
	tbz	x0, 12, .L114
	adrp	x0, .LANCHOR21
	ldr	x0, [x0, #:lo12:.LANCHOR21]
	ldrh	w1, [x0, 16]
	adrp	x0, .LC20
	add	x0, x0, :lo12:.LC20
	ubfx	x1, x1, 4, 1
	bl	printf
.L114:
	ldr	w0, [x19, #:lo12:.LANCHOR19]
	tbz	x0, 12, .L115
	adrp	x0, .LANCHOR21
	ldr	x0, [x0, #:lo12:.LANCHOR21]
	ldrh	w1, [x0, 16]
	adrp	x0, .LC21
	add	x0, x0, :lo12:.LC21
	ubfx	x1, x1, 5, 1
	bl	printf
.L115:
	ldr	w0, [x19, #:lo12:.LANCHOR19]
	tbz	x0, 12, .L116
	adrp	x0, .LANCHOR21
	ldr	x0, [x0, #:lo12:.LANCHOR21]
	ldrh	w1, [x0, 16]
	adrp	x0, .LC22
	add	x0, x0, :lo12:.LC22
	ubfx	x1, x1, 6, 1
	bl	printf
.L116:
	ldr	w0, [x19, #:lo12:.LANCHOR19]
	tbz	x0, 12, .L117
	adrp	x0, .LANCHOR21
	ldr	x0, [x0, #:lo12:.LANCHOR21]
	ldrh	w1, [x0, 16]
	adrp	x0, .LC23
	add	x0, x0, :lo12:.LC23
	ubfx	x1, x1, 7, 1
	bl	printf
.L117:
	ldr	w0, [x19, #:lo12:.LANCHOR19]
	tbz	x0, 12, .L118
	adrp	x0, .LANCHOR21
	ldr	x0, [x0, #:lo12:.LANCHOR21]
	ldrb	w1, [x0, 17]
	adrp	x0, .LC24
	add	x0, x0, :lo12:.LC24
	and	w1, w1, 1
	bl	printf
.L118:
	ldr	w0, [x19, #:lo12:.LANCHOR19]
	tbz	x0, 12, .L119
	adrp	x0, .LANCHOR21
	ldr	x0, [x0, #:lo12:.LANCHOR21]
	ldrh	w1, [x0, 16]
	adrp	x0, .LC25
	add	x0, x0, :lo12:.LC25
	ubfx	x1, x1, 9, 1
	bl	printf
.L119:
	ldr	w0, [x19, #:lo12:.LANCHOR19]
	tbz	x0, 12, .L120
	adrp	x0, .LANCHOR21
	ldr	x0, [x0, #:lo12:.LANCHOR21]
	ldrh	w1, [x0, 16]
	adrp	x0, .LC26
	add	x0, x0, :lo12:.LC26
	ubfx	x1, x1, 10, 1
	bl	printf
.L120:
	ldr	w0, [x19, #:lo12:.LANCHOR19]
	tbz	x0, 12, .L121
	adrp	x0, .LANCHOR24
	ldrb	w2, [x0, #:lo12:.LANCHOR24]
	adrp	x0, .LANCHOR0
	ldrb	w1, [x0, #:lo12:.LANCHOR0]
	adrp	x0, .LC27
	add	x0, x0, :lo12:.LC27
	bl	printf
.L121:
	ldr	w0, [x19, #:lo12:.LANCHOR19]
	tbz	x0, 12, .L122
	adrp	x0, .LANCHOR25
	add	x0, x0, :lo12:.LANCHOR25
	ldrb	w2, [x0, 11]
	ldrb	w1, [x0, 10]
	adrp	x0, .LC28
	add	x0, x0, :lo12:.LC28
	bl	printf
.L122:
	ldr	w0, [x19, #:lo12:.LANCHOR19]
	tbz	x0, 12, .L123
	adrp	x0, .LANCHOR25
	add	x0, x0, :lo12:.LANCHOR25
	ldrb	w2, [x0, 9]
	ldrb	w1, [x0, 8]
	adrp	x0, .LC29
	add	x0, x0, :lo12:.LC29
	bl	printf
.L123:
	ldr	w0, [x19, #:lo12:.LANCHOR19]
	tbz	x0, 12, .L94
	adrp	x0, .LANCHOR26
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ldrb	w1, [x0, #:lo12:.LANCHOR26]
	adrp	x0, .LC30
	add	x0, x0, :lo12:.LC30
	b	printf
.L94:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	nand_flash_print_info, .-nand_flash_print_info
	.section	.text.timer_delay_ns,"ax",@progbits
	.align	2
	.global	timer_delay_ns
	.type	timer_delay_ns, %function
timer_delay_ns:
	uxtw	x0, w0
	mov	x1, 1000
	add	x0, x0, 999
	udiv	x0, x0, x1
	b	udelay
	.size	timer_delay_ns, .-timer_delay_ns
	.section	.text.nandc_set_ddr_para,"ax",@progbits
	.align	2
	.global	nandc_set_ddr_para
	.type	nandc_set_ddr_para, %function
nandc_set_ddr_para:
	adrp	x1, .LANCHOR27
	and	w0, w0, 255
	adrp	x2, .LANCHOR7
	ldrb	w1, [x1, #:lo12:.LANCHOR27]
	ldr	x2, [x2, #:lo12:.LANCHOR7]
	cmp	w1, 9
	lsl	w1, w0, 16
	lsl	w0, w0, 8
	orr	w1, w1, w0
	orr	w1, w1, 3
	bne	.L215
	str	w1, [x2, 80]
	ret
.L215:
	str	w1, [x2, 304]
	ret
	.size	nandc_set_ddr_para, .-nandc_set_ddr_para
	.section	.text.nandc_get_ddr_para,"ax",@progbits
	.align	2
	.global	nandc_get_ddr_para
	.type	nandc_get_ddr_para, %function
nandc_get_ddr_para:
	adrp	x0, .LANCHOR27
	ldrb	w0, [x0, #:lo12:.LANCHOR27]
	cmp	w0, 9
	adrp	x0, .LANCHOR7
	ldr	x0, [x0, #:lo12:.LANCHOR7]
	bne	.L218
	ldr	w0, [x0, 80]
.L220:
	ubfx	x0, x0, 8, 8
	ret
.L218:
	ldr	w0, [x0, 304]
	b	.L220
	.size	nandc_get_ddr_para, .-nandc_get_ddr_para
	.section	.text.nandc_set_if_mode,"ax",@progbits
	.align	2
	.global	nandc_set_if_mode
	.type	nandc_set_if_mode, %function
nandc_set_if_mode:
	adrp	x1, .LANCHOR7
	and	w0, w0, 255
	tst	w0, 6
	ldr	x2, [x1, #:lo12:.LANCHOR7]
	ldr	w1, [x2]
	beq	.L222
	tst	x0, 4
	orr	w1, w1, 24576
	adrp	x0, .LANCHOR27
	and	w1, w1, -32769
	orr	w1, w1, 196608
	ldrb	w0, [x0, #:lo12:.LANCHOR27]
	orr	w3, w1, 32768
	csel	w1, w3, w1, ne
	cmp	w0, 9
	mov	w0, 4099
	movk	w0, 0x10, lsl 16
	bne	.L224
	mov	w3, 8321
	str	w3, [x2, 8]
	str	w0, [x2, 80]
	mov	w0, 38
	str	w0, [x2, 84]
	mov	w0, 39
	str	w0, [x2, 84]
.L225:
	str	w1, [x2]
	ret
.L224:
	mov	w3, 8322
	str	w3, [x2, 344]
	str	w0, [x2, 304]
	mov	w0, 38
	str	w0, [x2, 308]
	mov	w0, 39
	str	w0, [x2, 308]
	b	.L225
.L222:
	and	w1, w1, -8193
	b	.L225
	.size	nandc_set_if_mode, .-nandc_set_if_mode
	.section	.text.nandc_cs,"ax",@progbits
	.align	2
	.global	nandc_cs
	.type	nandc_cs, %function
nandc_cs:
	adrp	x1, .LANCHOR7
	mov	w2, 1
	lsl	w0, w2, w0
	ldr	x3, [x1, #:lo12:.LANCHOR7]
	ldr	w1, [x3]
	bfi	w1, w0, 0, 8
	str	w1, [x3]
	ret
	.size	nandc_cs, .-nandc_cs
	.section	.text.flash_wait_device_ready_raw,"ax",@progbits
	.align	2
	.global	flash_wait_device_ready_raw
	.type	flash_wait_device_ready_raw, %function
flash_wait_device_ready_raw:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	and	w19, w0, 255
	adrp	x0, .LANCHOR23
	stp	x25, x26, [sp, 64]
	stp	x21, x22, [sp, 32]
	mov	w20, w1
	ldrb	w0, [x0, #:lo12:.LANCHOR23]
	mov	w26, w2
	stp	x23, x24, [sp, 48]
	str	x27, [sp, 80]
	cmp	w0, w19
	bhi	.L230
	adrp	x1, .LANCHOR28
	adrp	x0, .LC0
	mov	w2, 812
	add	x1, x1, :lo12:.LANCHOR28
	add	x0, x0, :lo12:.LC0
	bl	printf
.L230:
	adrp	x0, .LANCHOR29
	add	x0, x0, :lo12:.LANCHOR29
	lsr	w23, w20, 8
	lsr	w24, w20, 16
	lsr	w25, w20, 24
	adrp	x21, .LANCHOR30
	ldrb	w22, [x0, w19, sxtw]
	adrp	x0, .LANCHOR7
	and	w20, w20, 255
	add	x21, x21, :lo12:.LANCHOR30
	ldr	x19, [x0, #:lo12:.LANCHOR7]
	mov	w27, 120
	ubfiz	x0, x22, 8, 8
	add	x19, x19, x0
.L236:
	mov	w0, w22
	bl	nandc_cs
	str	w27, [x19, 2056]
	str	w20, [x19, 2052]
	ldrb	w0, [x21]
	str	w23, [x19, 2052]
	str	w24, [x19, 2052]
	cbz	w0, .L231
	str	w25, [x19, 2052]
.L231:
	mov	x0, 1
	bl	udelay
	ldr	w2, [x19, 2048]
	and	w2, w2, 255
	bl	nandc_de_cs.constprop.32
	bics	wzr, w26, w2
	bne	.L236
	cmp	w2, 255
	beq	.L236
	mov	w0, w2
	ldr	x27, [sp, 80]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 96
	ret
	.size	flash_wait_device_ready_raw, .-flash_wait_device_ready_raw
	.section	.text.flash_wait_device_ready,"ax",@progbits
	.align	2
	.global	flash_wait_device_ready
	.type	flash_wait_device_ready, %function
flash_wait_device_ready:
	mov	w2, w1
	adrp	x1, .LANCHOR31
	mov	w5, 24
	mov	w4, 1
	ldrb	w6, [x1, #:lo12:.LANCHOR31]
	tst	x0, 50331648
	sub	w5, w5, w6
	lsl	w3, w4, w5
	sub	w3, w3, #1
	lsl	w4, w4, w6
	sub	w4, w4, #1
	asr	w5, w0, w5
	and	w4, w4, w5
	and	w1, w3, w0
	and	w4, w4, 255
	bne	.L241
	adrp	x0, .LANCHOR0
	adrp	x5, .LANCHOR1
	ldrb	w0, [x0, #:lo12:.LANCHOR0]
	cbz	w0, .L242
	ldrb	w0, [x5, #:lo12:.LANCHOR1]
	cbz	w0, .L241
.L242:
	adrp	x0, .LANCHOR2
	ldrh	w3, [x0, #:lo12:.LANCHOR2]
	udiv	w0, w1, w3
	mul	w0, w0, w3
	sub	w3, w1, w0
	ldrb	w1, [x5, #:lo12:.LANCHOR1]
	cbz	w1, .L243
	add	w1, w0, w3, lsl 1
.L241:
	mov	w0, w4
	b	flash_wait_device_ready_raw
.L243:
	adrp	x5, .LANCHOR3
	add	x5, x5, :lo12:.LANCHOR3
	ldrh	w3, [x5, w3, uxtw 1]
	add	w1, w3, w0
	b	.L241
	.size	flash_wait_device_ready, .-flash_wait_device_ready
	.section	.text.nandc_de_cs,"ax",@progbits
	.align	2
	.global	nandc_de_cs
	.type	nandc_de_cs, %function
nandc_de_cs:
	adrp	x0, .LANCHOR7
	ldr	x1, [x0, #:lo12:.LANCHOR7]
	ldr	w0, [x1]
	and	w0, w0, -256
	and	w0, w0, -131073
	str	w0, [x1]
	ret
	.size	nandc_de_cs, .-nandc_de_cs
	.section	.text.nandc_wait_flash_ready_no_delay,"ax",@progbits
	.align	2
	.global	nandc_wait_flash_ready_no_delay
	.type	nandc_wait_flash_ready_no_delay, %function
nandc_wait_flash_ready_no_delay:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w19, 34464
	movk	w19, 0x1, lsl 16
	adrp	x20, .LANCHOR7
.L253:
	ldr	x0, [x20, #:lo12:.LANCHOR7]
	ldr	w0, [x0]
	str	w0, [x29, 40]
	ldr	w0, [x29, 40]
	tbnz	x0, 9, .L254
	mov	x0, 1
	bl	udelay
	subs	w19, w19, #1
	bne	.L253
	mov	w0, -1
.L251:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
.L254:
	mov	w0, 0
	b	.L251
	.size	nandc_wait_flash_ready_no_delay, .-nandc_wait_flash_ready_no_delay
	.section	.text.zftl_flash_enter_slc_mode,"ax",@progbits
	.align	2
	.global	zftl_flash_enter_slc_mode
	.type	zftl_flash_enter_slc_mode, %function
zftl_flash_enter_slc_mode:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	and	x19, x0, 255
	adrp	x0, .LANCHOR0
	stp	x21, x22, [sp, 32]
	ldrb	w0, [x0, #:lo12:.LANCHOR0]
	cbz	w0, .L257
	adrp	x1, .LANCHOR7
	cmp	w0, 1
	ldr	x20, [x1, #:lo12:.LANCHOR7]
	bne	.L260
	adrp	x0, .LANCHOR32+29
	ldrb	w0, [x0, #:lo12:.LANCHOR32+29]
	cbz	w0, .L257
.L276:
	add	x19, x19, 8
	add	x19, x20, x19, lsl 8
	str	w0, [x19, 8]
.L257:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
.L260:
	cmp	w0, 2
	bne	.L262
	adrp	x0, .LANCHOR33
	add	x0, x0, :lo12:.LANCHOR33
	ldrb	w1, [x0, x19]
	cbz	w1, .L257
	adrp	x21, .LANCHOR32
	add	x21, x21, :lo12:.LANCHOR32
	strb	wzr, [x0, x19]
	ldrb	w0, [x21, 29]
	cbz	w0, .L257
	bl	nandc_wait_flash_ready_no_delay
	ldrb	w0, [x21, 29]
	b	.L276
.L262:
	cmp	w0, 3
	bne	.L257
	adrp	x21, .LANCHOR33
	sxtw	x22, w19
	add	x21, x21, :lo12:.LANCHOR33
	ldrb	w0, [x21, x22]
	cbz	w0, .L257
	ubfiz	x19, x19, 8, 8
	bl	nandc_wait_flash_ready_no_delay
	add	x19, x20, x19
	mov	w0, 239
	strb	wzr, [x21, x22]
	str	w0, [x19, 2056]
	mov	w0, 145
	str	w0, [x19, 2052]
	mov	x0, 1
	bl	udelay
	str	wzr, [x19, 2048]
	mov	w0, 1
	str	w0, [x19, 2048]
	str	wzr, [x19, 2048]
	mov	x0, 1
	str	wzr, [x19, 2048]
	bl	udelay
	bl	nandc_wait_flash_ready_no_delay
	mov	w0, 218
	ldp	x21, x22, [sp, 32]
	str	w0, [x19, 2056]
	ldp	x19, x20, [sp, 16]
	mov	x0, 1
	ldp	x29, x30, [sp], 48
	b	udelay
	.size	zftl_flash_enter_slc_mode, .-zftl_flash_enter_slc_mode
	.section	.text.zftl_flash_exit_slc_mode,"ax",@progbits
	.align	2
	.global	zftl_flash_exit_slc_mode
	.type	zftl_flash_exit_slc_mode, %function
zftl_flash_exit_slc_mode:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	and	x19, x0, 255
	adrp	x0, .LANCHOR0
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	ldrb	w0, [x0, #:lo12:.LANCHOR0]
	cbz	w0, .L277
	adrp	x1, .LANCHOR7
	cmp	w0, 1
	ldr	x20, [x1, #:lo12:.LANCHOR7]
	bne	.L280
	adrp	x0, .LANCHOR32+30
	ldrb	w0, [x0, #:lo12:.LANCHOR32+30]
	cbz	w0, .L277
.L298:
	add	x19, x19, 8
	add	x19, x20, x19, lsl 8
	str	w0, [x19, 8]
.L277:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
.L280:
	cmp	w0, 2
	bne	.L282
	adrp	x0, .LANCHOR33
	add	x0, x0, :lo12:.LANCHOR33
	ldrb	w1, [x0, x19]
	cbnz	w1, .L277
	adrp	x21, .LANCHOR32
	add	x21, x21, :lo12:.LANCHOR32
	mov	w2, 4
	ldrb	w1, [x21, 12]
	cmp	w1, 2
	csel	w1, w1, w2, eq
	strb	w1, [x0, x19]
	ldrb	w0, [x21, 30]
	cbz	w0, .L277
	bl	nandc_wait_flash_ready_no_delay
	ldrb	w0, [x21, 30]
	b	.L298
.L282:
	cmp	w0, 3
	bne	.L277
	adrp	x21, .LANCHOR33
	sxtw	x23, w19
	add	x21, x21, :lo12:.LANCHOR33
	ldrb	w0, [x21, x23]
	cbnz	w0, .L277
	adrp	x22, .LANCHOR32
	add	x22, x22, :lo12:.LANCHOR32
	bl	nandc_wait_flash_ready_no_delay
	ubfiz	x19, x19, 8, 8
	add	x19, x20, x19
	mov	w1, 4
	ldrb	w0, [x22, 12]
	cmp	w0, 2
	csel	w0, w0, w1, eq
	strb	w0, [x21, x23]
	mov	w0, 239
	str	w0, [x19, 2056]
	mov	w0, 145
	str	w0, [x19, 2052]
	mov	x0, 1
	bl	udelay
	ldrb	w0, [x22, 7]
	cmp	w0, 9
	mov	w0, 1
	bne	.L285
	str	w0, [x19, 2048]
.L286:
	str	w0, [x19, 2048]
	mov	x0, 1
	str	wzr, [x19, 2048]
	str	wzr, [x19, 2048]
	bl	udelay
	bl	nandc_wait_flash_ready_no_delay
	ldr	x23, [sp, 48]
	ldp	x21, x22, [sp, 32]
	mov	w0, 223
	str	w0, [x19, 2056]
	mov	x0, 1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 64
	b	udelay
.L285:
	ldrb	w1, [x21, x23]
	str	w1, [x19, 2048]
	b	.L286
	.size	zftl_flash_exit_slc_mode, .-zftl_flash_exit_slc_mode
	.section	.text.flash_start_page_read,"ax",@progbits
	.align	2
	.global	flash_start_page_read
	.type	flash_start_page_read, %function
flash_start_page_read:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x21, x22, [sp, 32]
	and	w21, w0, 255
	adrp	x0, .LANCHOR31
	stp	x19, x20, [sp, 16]
	str	x23, [sp, 48]
	mov	w19, 24
	ldrb	w0, [x0, #:lo12:.LANCHOR31]
	mov	w20, 1
	mov	w22, w1
	sub	w23, w19, w0
	lsl	w20, w20, w0
	sub	w20, w20, #1
	lsr	w0, w1, w23
	and	w20, w20, w0
	adrp	x0, .LANCHOR23
	and	w20, w20, 255
	mov	x19, x0
	ldrb	w1, [x0, #:lo12:.LANCHOR23]
	cmp	w1, w20
	bhi	.L300
	adrp	x1, .LANCHOR34
	adrp	x0, .LC0
	mov	w2, 1013
	add	x1, x1, :lo12:.LANCHOR34
	add	x0, x0, :lo12:.LC0
	bl	printf
.L300:
	ldrb	w0, [x19, #:lo12:.LANCHOR23]
	cmp	w0, w20
	bls	.L299
	adrp	x0, .LANCHOR29
	add	x0, x0, :lo12:.LANCHOR29
	mov	w19, 1
	ubfx	x4, x22, 24, 2
	lsl	w19, w19, w23
	sub	w19, w19, #1
	and	w19, w19, w22
	ldrb	w22, [x0, w20, sxtw]
	adrp	x0, .LANCHOR7
	adrp	x23, .LANCHOR21
	ldr	x20, [x0, #:lo12:.LANCHOR7]
	mov	w0, w22
	bl	nandc_cs
	cbnz	w4, .L302
	mov	w0, w19
	bl	slc_phy_page_address_calc
	mov	w19, w0
	adrp	x0, .LANCHOR0
	ldrb	w0, [x0, #:lo12:.LANCHOR0]
	cbz	w0, .L303
	mov	w0, w22
	bl	zftl_flash_enter_slc_mode
.L303:
	ldr	x0, [x23, #:lo12:.LANCHOR21]
	ldrb	w1, [x0, 7]
	cmp	w1, 1
	bne	.L305
	ldrb	w0, [x0, 12]
	cmp	w0, 2
	bne	.L305
	sxtw	x0, w22
	mov	w1, 38
	add	x0, x0, 8
	add	x0, x20, x0, lsl 8
	str	w1, [x0, 8]
.L305:
	ubfiz	x0, x22, 8, 8
	and	w1, w19, 255
	add	x0, x20, x0
	str	wzr, [x0, 2056]
	str	wzr, [x0, 2052]
	str	wzr, [x0, 2052]
	str	w1, [x0, 2052]
	lsr	w1, w19, 8
	str	w1, [x0, 2052]
	lsr	w1, w19, 16
	str	w1, [x0, 2052]
	adrp	x1, .LANCHOR30
	ldrb	w1, [x1, #:lo12:.LANCHOR30]
	cbz	w1, .L306
	lsr	w19, w19, 24
	str	w19, [x0, 2052]
.L306:
	str	w21, [x0, 2056]
.L299:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
.L302:
	ldr	x0, [x23, #:lo12:.LANCHOR21]
	ldrb	w0, [x0, 12]
	cmp	w0, 3
	bne	.L304
	adrp	x0, .LANCHOR35
	ldrb	w0, [x0, #:lo12:.LANCHOR35]
	cbnz	w0, .L304
	adrp	x0, .LANCHOR36
	ldrb	w0, [x0, #:lo12:.LANCHOR36]
	cbnz	w0, .L304
	sxtw	x0, w22
	add	x0, x0, 8
	add	x0, x20, x0, lsl 8
	str	w4, [x0, 8]
	b	.L303
.L304:
	mov	w0, w22
	bl	zftl_flash_exit_slc_mode
	b	.L303
	.size	flash_start_page_read, .-flash_start_page_read
	.section	.text.nandc_wait_flash_ready,"ax",@progbits
	.align	2
	.global	nandc_wait_flash_ready
	.type	nandc_wait_flash_ready, %function
nandc_wait_flash_ready:
	stp	x29, x30, [sp, -48]!
	mov	x0, 1
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w19, 34464
	movk	w19, 0x1, lsl 16
	adrp	x20, .LANCHOR7
	bl	udelay
.L316:
	ldr	x0, [x20, #:lo12:.LANCHOR7]
	ldr	w0, [x0]
	str	w0, [x29, 40]
	ldr	w0, [x29, 40]
	tbnz	x0, 9, .L317
	mov	x0, 1
	bl	udelay
	subs	w19, w19, #1
	bne	.L316
	mov	w0, -1
.L314:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
.L317:
	mov	w0, 0
	b	.L314
	.size	nandc_wait_flash_ready, .-nandc_wait_flash_ready
	.section	.text.sandisk_set_rr_para,"ax",@progbits
	.align	2
	.global	sandisk_set_rr_para
	.type	sandisk_set_rr_para, %function
sandisk_set_rr_para:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	mov	w0, 239
	and	w19, w1, 255
	str	w0, [x20, 8]
	mov	w0, 17
	str	w0, [x20, 4]
	mov	x0, 1
	bl	udelay
	adrp	x0, .LANCHOR18
	add	w1, w19, 1
	adrp	x2, .LANCHOR14
	add	x2, x2, :lo12:.LANCHOR14
	ldrb	w3, [x0, #:lo12:.LANCHOR18]
	adrp	x0, .LANCHOR16
	ldrb	w4, [x0, #:lo12:.LANCHOR16]
	mov	w0, 5
	umull	x1, w1, w0
	adrp	x0, .LANCHOR15
	add	x0, x0, :lo12:.LANCHOR15
	add	x2, x2, x1
	add	x1, x0, x1
	mov	x0, 0
.L321:
	cmp	w3, w0
	bhi	.L324
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	b	nandc_wait_flash_ready
.L324:
	cmp	w4, 67
	bne	.L322
	ldrsb	w5, [x1, x0]
.L326:
	add	x0, x0, 1
	str	w5, [x20]
	b	.L321
.L322:
	ldrsb	w5, [x2, x0]
	b	.L326
	.size	sandisk_set_rr_para, .-sandisk_set_rr_para
	.section	.text.toshiba_3d_set_tlc_rr_para,"ax",@progbits
	.align	2
	.global	toshiba_3d_set_tlc_rr_para
	.type	toshiba_3d_set_tlc_rr_para, %function
toshiba_3d_set_tlc_rr_para:
	stp	x29, x30, [sp, -48]!
	and	x2, x1, 255
	mov	x1, 7
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	str	x21, [sp, 32]
	mov	w21, 213
	madd	x1, x2, x1, x1
	mov	w0, -119
	str	w21, [x19, 8]
	str	wzr, [x19, 4]
	str	w0, [x19, 4]
	adrp	x0, .LANCHOR37
	add	x0, x0, :lo12:.LANCHOR37
	add	x20, x0, x1
	ldrsb	w0, [x0, x1]
	str	w0, [x19]
	ldrsb	w0, [x20, 1]
	str	w0, [x19]
	ldrsb	w0, [x20, 2]
	str	w0, [x19]
	ldrsb	w0, [x20, 3]
	str	w0, [x19]
	bl	nandc_wait_flash_ready
	str	w21, [x19, 8]
	str	wzr, [x19, 4]
	mov	w0, -118
	str	w0, [x19, 4]
	ldrsb	w0, [x20, 4]
	ldr	x21, [sp, 32]
	str	w0, [x19]
	ldrsb	w0, [x20, 5]
	str	w0, [x19]
	ldrsb	w0, [x20, 6]
	str	w0, [x19]
	str	wzr, [x19]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	b	nandc_wait_flash_ready
	.size	toshiba_3d_set_tlc_rr_para, .-toshiba_3d_set_tlc_rr_para
	.section	.text.toshiba_3d_set_slc_rr_para,"ax",@progbits
	.align	2
	.global	toshiba_3d_set_slc_rr_para
	.type	toshiba_3d_set_slc_rr_para, %function
toshiba_3d_set_slc_rr_para:
	mov	w2, 213
	str	w2, [x0, 8]
	str	wzr, [x0, 4]
	mov	w2, -117
	str	w2, [x0, 4]
	adrp	x2, .LANCHOR38
	add	x2, x2, :lo12:.LANCHOR38
	add	x1, x2, x1, uxtb
	ldrsb	w1, [x1, 1]
	str	w1, [x0]
	str	wzr, [x0]
	str	wzr, [x0]
	str	wzr, [x0]
	b	nandc_wait_flash_ready
	.size	toshiba_3d_set_slc_rr_para, .-toshiba_3d_set_slc_rr_para
	.section	.text.toshiba_tlc_set_rr_para,"ax",@progbits
	.align	2
	.global	toshiba_tlc_set_rr_para
	.type	toshiba_tlc_set_rr_para, %function
toshiba_tlc_set_rr_para:
	stp	x29, x30, [sp, -48]!
	uxtw	x1, w1
	add	x29, sp, 0
	str	x21, [sp, 32]
	mov	w21, 239
	stp	x19, x20, [sp, 16]
	cbz	w2, .L331
	mov	x19, x0
	mov	x2, 7
	mov	w0, 18
	mul	x1, x1, x2
	str	w21, [x19, 8]
	str	w0, [x19, 4]
	adrp	x0, .LANCHOR39
	add	x0, x0, :lo12:.LANCHOR39
	add	x20, x0, x1
	ldrb	w0, [x0, x1]
	str	w0, [x19]
	ldrb	w0, [x20, 1]
	str	w0, [x19]
	ldrb	w0, [x20, 2]
	str	w0, [x19]
	ldrb	w0, [x20, 3]
	str	w0, [x19]
	bl	nandc_wait_flash_ready
	str	w21, [x19, 8]
	mov	w0, 19
	str	w0, [x19, 4]
	ldrb	w0, [x20, 4]
	str	w0, [x19]
	ldrb	w0, [x20, 5]
	str	w0, [x19]
	ldrb	w0, [x20, 6]
	str	w0, [x19]
	str	wzr, [x19]
.L332:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	b	nandc_wait_flash_ready
.L331:
	str	w21, [x0, 8]
	mov	w2, 20
	str	w2, [x0, 4]
	adrp	x2, .LANCHOR40
	add	x2, x2, :lo12:.LANCHOR40
	ldrb	w1, [x2, x1]
	str	w1, [x0]
	str	wzr, [x0]
	str	wzr, [x0]
	str	wzr, [x0]
	b	.L332
	.size	toshiba_tlc_set_rr_para, .-toshiba_tlc_set_rr_para
	.section	.text.ymtc_3d_set_tlc_rr_para,"ax",@progbits
	.align	2
	.global	ymtc_3d_set_tlc_rr_para
	.type	ymtc_3d_set_tlc_rr_para, %function
ymtc_3d_set_tlc_rr_para:
	stp	x29, x30, [sp, -48]!
	and	x1, x1, 255
	mov	x2, 7
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	str	x21, [sp, 32]
	mul	x1, x1, x2
	mov	w21, 239
	mov	w0, 160
	str	w21, [x19, 8]
	str	w0, [x19, 4]
	adrp	x0, .LANCHOR41
	add	x0, x0, :lo12:.LANCHOR41
	add	x20, x0, x1
	ldrsb	w0, [x0, x1]
	str	w0, [x19]
	ldrsb	w0, [x20, 4]
	str	w0, [x19]
	str	wzr, [x19]
	str	wzr, [x19]
	bl	nandc_wait_flash_ready
	str	w21, [x19, 8]
	mov	w0, 161
	str	w0, [x19, 4]
	ldrsb	w0, [x20, 1]
	str	w0, [x19]
	ldrsb	w0, [x20, 3]
	str	w0, [x19]
	ldrsb	w0, [x20, 5]
	str	w0, [x19]
	str	wzr, [x19]
	bl	nandc_wait_flash_ready
	str	w21, [x19, 8]
	mov	w0, 162
	str	w0, [x19, 4]
	ldrsb	w0, [x20, 2]
	ldr	x21, [sp, 32]
	str	w0, [x19]
	ldrsb	w0, [x20, 6]
	str	w0, [x19]
	str	wzr, [x19]
	str	wzr, [x19]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	b	nandc_wait_flash_ready
	.size	ymtc_3d_set_tlc_rr_para, .-ymtc_3d_set_tlc_rr_para
	.section	.text.ymtc_3d_set_slc_rr_para,"ax",@progbits
	.align	2
	.global	ymtc_3d_set_slc_rr_para
	.type	ymtc_3d_set_slc_rr_para, %function
ymtc_3d_set_slc_rr_para:
	mov	w2, 239
	str	w2, [x0, 8]
	mov	w2, 163
	and	x1, x1, 255
	str	w2, [x0, 4]
	adrp	x2, .LANCHOR42
	add	x2, x2, :lo12:.LANCHOR42
	ldrsb	w1, [x2, x1]
	str	w1, [x0]
	str	wzr, [x0]
	str	wzr, [x0]
	str	wzr, [x0]
	b	nandc_wait_flash_ready
	.size	ymtc_3d_set_slc_rr_para, .-ymtc_3d_set_slc_rr_para
	.section	.text.flash_erase_duplane_block,"ax",@progbits
	.align	2
	.global	flash_erase_duplane_block
	.type	flash_erase_duplane_block, %function
flash_erase_duplane_block:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x21, x22, [sp, 32]
	and	w22, w0, 255
	adrp	x0, .LANCHOR23
	stp	x19, x20, [sp, 16]
	stp	x23, x24, [sp, 48]
	and	w24, w1, 255
	str	x25, [sp, 64]
	mov	w21, w2
	ldrb	w1, [x0, #:lo12:.LANCHOR23]
	mov	w20, w3
	mov	x19, x0
	cmp	w1, w22
	bhi	.L338
	adrp	x1, .LANCHOR43
	adrp	x0, .LC0
	mov	w2, 695
	add	x1, x1, :lo12:.LANCHOR43
	add	x0, x0, :lo12:.LC0
	bl	printf
.L338:
	ldrb	w0, [x19, #:lo12:.LANCHOR23]
	cmp	w0, w22
	bls	.L347
	adrp	x0, .LANCHOR29
	add	x0, x0, :lo12:.LANCHOR29
	ldrb	w22, [x0, w22, sxtw]
	adrp	x0, .LANCHOR7
	ldr	x25, [x0, #:lo12:.LANCHOR7]
	adrp	x0, .LANCHOR19
	and	x19, x22, 255
	ldr	w0, [x0, #:lo12:.LANCHOR19]
	add	x23, x19, 8
	add	x23, x25, x23, lsl 8
	tbz	x0, 4, .L340
	adrp	x0, .LC31
	mov	w3, w20
	mov	w2, w21
	mov	w1, w22
	add	x0, x0, :lo12:.LC31
	bl	printf
.L340:
	bl	nandc_wait_flash_ready
	mov	w0, w22
	bl	nandc_cs
	mov	w0, w22
	cbnz	w24, .L341
	bl	zftl_flash_enter_slc_mode
.L342:
	add	x19, x25, x19, lsl 8
	mov	w0, 96
	str	w0, [x19, 2056]
	and	w0, w21, 255
	str	w0, [x19, 2052]
	lsr	w0, w21, 8
	str	w0, [x19, 2052]
	lsr	w0, w21, 16
	str	w0, [x19, 2052]
	adrp	x0, .LANCHOR30
	mov	x24, x0
	ldrb	w1, [x0, #:lo12:.LANCHOR30]
	cbz	w1, .L343
	lsr	w0, w21, 24
	str	w0, [x19, 2052]
.L343:
	adrp	x0, .LANCHOR44
	ldrb	w0, [x0, #:lo12:.LANCHOR44]
	cbnz	w0, .L348
	mov	w0, 208
	str	w0, [x19, 2056]
	mov	w22, 5
	bl	nandc_wait_flash_ready
	mov	x0, x23
	bl	flash_read_status
	and	w22, w0, w22
.L344:
	mov	w0, 96
	str	w0, [x19, 2056]
	and	w0, w20, 255
	str	w0, [x19, 2052]
	lsr	w0, w20, 8
	str	w0, [x19, 2052]
	lsr	w0, w20, 16
	str	w0, [x19, 2052]
	ldrb	w0, [x24, #:lo12:.LANCHOR30]
	cbz	w0, .L345
	lsr	w20, w20, 24
	str	w20, [x19, 2052]
.L345:
	mov	w0, 208
	str	w0, [x19, 2056]
	mov	w19, 5
	bl	nandc_wait_flash_ready
	mov	x0, x23
	bl	flash_read_status
	mov	w2, w0
	bl	nandc_de_cs.constprop.32
	and	w19, w2, w19
	orr	w19, w19, w22
	cbz	w19, .L346
	adrp	x0, .LC32
	mov	w1, w21
	add	x0, x0, :lo12:.LC32
	bl	printf
.L346:
	mov	w0, w19
.L337:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldr	x25, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
.L341:
	bl	zftl_flash_exit_slc_mode
	b	.L342
.L348:
	mov	w22, 0
	b	.L344
.L347:
	mov	w0, -1
	b	.L337
	.size	flash_erase_duplane_block, .-flash_erase_duplane_block
	.section	.text.flash_erase_block_en,"ax",@progbits
	.align	2
	.global	flash_erase_block_en
	.type	flash_erase_block_en, %function
flash_erase_block_en:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x21, x22, [sp, 32]
	and	w22, w0, 255
	adrp	x0, .LANCHOR31
	stp	x19, x20, [sp, 16]
	mov	w19, 24
	stp	x23, x24, [sp, 48]
	ldrb	w0, [x0, #:lo12:.LANCHOR31]
	and	w24, w1, 255
	stp	x25, x26, [sp, 64]
	mov	w23, w2
	sub	w0, w19, w0
	mov	w19, 1
	lsl	w19, w19, w0
	adrp	x0, .LANCHOR23
	sub	w19, w19, #1
	mov	x20, x0
	ldrb	w1, [x0, #:lo12:.LANCHOR23]
	and	w19, w19, w2
	cmp	w1, w22
	bhi	.L363
	adrp	x1, .LANCHOR45
	adrp	x0, .LC0
	mov	w2, 757
	add	x1, x1, :lo12:.LANCHOR45
	add	x0, x0, :lo12:.LC0
	bl	printf
.L363:
	ldrb	w0, [x20, #:lo12:.LANCHOR23]
	cmp	w0, w22
	bls	.L370
	adrp	x0, .LANCHOR29
	add	x0, x0, :lo12:.LANCHOR29
	ldrb	w21, [x0, w22, sxtw]
	adrp	x0, .LANCHOR7
	ldr	x26, [x0, #:lo12:.LANCHOR7]
	adrp	x0, .LANCHOR19
	and	x20, x21, 255
	ldr	w0, [x0, #:lo12:.LANCHOR19]
	add	x25, x20, 8
	add	x25, x26, x25, lsl 8
	tbz	x0, 4, .L365
	adrp	x0, .LC33
	mov	w3, w24
	mov	w2, w23
	mov	w1, w21
	add	x0, x0, :lo12:.LC33
	bl	printf
.L365:
	bl	nandc_wait_flash_ready
	mov	w0, w21
	bl	nandc_cs
	mov	w0, w21
	cbnz	w24, .L366
	bl	zftl_flash_enter_slc_mode
.L367:
	add	x0, x26, x20, lsl 8
	mov	w1, 96
	str	w1, [x0, 2056]
	and	w1, w19, 255
	str	w1, [x0, 2052]
	lsr	w1, w19, 8
	str	w1, [x0, 2052]
	lsr	w1, w19, 16
	str	w1, [x0, 2052]
	adrp	x1, .LANCHOR30
	ldrb	w1, [x1, #:lo12:.LANCHOR30]
	cbz	w1, .L368
	lsr	w19, w19, 24
	str	w19, [x0, 2052]
.L368:
	mov	w1, 208
	str	w1, [x0, 2056]
	bl	nandc_wait_flash_ready
	mov	x0, x25
	bl	flash_read_status
	mov	w3, w0
	bl	nandc_de_cs.constprop.32
	mov	w0, 5
	ands	w3, w3, w0
	beq	.L369
	adrp	x0, .LANCHOR2
	mov	w1, w22
	ldrh	w2, [x0, #:lo12:.LANCHOR2]
	adrp	x0, .LC34
	add	x0, x0, :lo12:.LC34
	udiv	w2, w23, w2
	bl	printf
	mov	w3, -1
.L369:
	mov	w0, w3
.L362:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
.L366:
	bl	zftl_flash_exit_slc_mode
	b	.L367
.L370:
	mov	w0, -1
	b	.L362
	.size	flash_erase_block_en, .-flash_erase_block_en
	.section	.text.flash_erase_block,"ax",@progbits
	.align	2
	.global	flash_erase_block
	.type	flash_erase_block, %function
flash_erase_block:
	mov	w2, w1
	mov	w1, 0
	b	flash_erase_block_en
	.size	flash_erase_block, .-flash_erase_block
	.section	.text.flash_erase_all,"ax",@progbits
	.align	2
	.global	flash_erase_all
	.type	flash_erase_all, %function
flash_erase_all:
	stp	x29, x30, [sp, -80]!
	adrp	x0, .LANCHOR32
	add	x0, x0, :lo12:.LANCHOR32
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w19, 0
	stp	x23, x24, [sp, 48]
	adrp	x23, .LANCHOR2
	stp	x21, x22, [sp, 32]
	add	x23, x23, :lo12:.LANCHOR2
	ldrh	w20, [x0, 14]
	adrp	x22, .LANCHOR23
	str	x25, [sp, 64]
	add	x22, x22, :lo12:.LANCHOR23
	adrp	x24, .LANCHOR29
	ldrb	w1, [x0, 13]
	mul	w20, w20, w1
	and	w20, w20, 65535
.L383:
	ldrb	w0, [x22]
	cmp	w0, w19
	bhi	.L386
	ldp	x19, x20, [sp, 16]
	mov	w1, 0
	ldp	x21, x22, [sp, 32]
	adrp	x0, .LC35
	ldp	x23, x24, [sp, 48]
	add	x0, x0, :lo12:.LC35
	ldr	x25, [sp, 64]
	ldp	x29, x30, [sp], 80
	b	printf
.L386:
	add	x0, x24, :lo12:.LANCHOR29
	mov	w21, 0
	ldrb	w25, [x0, w19, sxtw]
.L384:
	cmp	w20, w21, uxth
	bhi	.L385
	add	w19, w19, 1
	and	w19, w19, 65535
	b	.L383
.L385:
	ldrh	w1, [x23]
	mov	w0, w25
	mul	w1, w1, w21
	add	w21, w21, 1
	bl	flash_erase_block
	b	.L384
	.size	flash_erase_all, .-flash_erase_all
	.section	.text.flash_start_plane_read,"ax",@progbits
	.align	2
	.global	flash_start_plane_read
	.type	flash_start_plane_read, %function
flash_start_plane_read:
	stp	x29, x30, [sp, -96]!
	adrp	x2, .LANCHOR31
	mov	w3, 24
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	ldrb	w19, [x2, #:lo12:.LANCHOR31]
	mov	w2, 1
	stp	x21, x22, [sp, 32]
	ubfx	x22, x0, 24, 2
	sub	w3, w3, w19
	stp	x23, x24, [sp, 48]
	lsl	w19, w2, w19
	sub	w19, w19, #1
	lsl	w20, w2, w3
	sub	w20, w20, #1
	and	w23, w20, w0
	lsr	w3, w0, w3
	adrp	x0, .LANCHOR23
	and	w19, w19, w3
	stp	x25, x26, [sp, 64]
	and	w19, w19, 255
	ldrb	w0, [x0, #:lo12:.LANCHOR23]
	and	w20, w20, w1
	stp	x27, x28, [sp, 80]
	cmp	w0, w19
	bhi	.L389
	adrp	x1, .LANCHOR46
	adrp	x0, .LC0
	mov	w2, 1148
	add	x1, x1, :lo12:.LANCHOR46
	add	x0, x0, :lo12:.LC0
	bl	printf
.L389:
	adrp	x0, .LANCHOR29
	add	x0, x0, :lo12:.LANCHOR29
	adrp	x25, .LANCHOR21
	ldrb	w21, [x0, w19, sxtw]
	adrp	x0, .LANCHOR7
	ldr	x24, [x0, #:lo12:.LANCHOR7]
	mov	w0, w21
	bl	nandc_cs
	cbnz	w22, .L390
	mov	w0, w23
	bl	slc_phy_page_address_calc
	mov	w23, w0
	mov	w0, w20
	bl	slc_phy_page_address_calc
	mov	w20, w0
	adrp	x0, .LANCHOR0
	ldrb	w0, [x0, #:lo12:.LANCHOR0]
	cbz	w0, .L391
	mov	w0, w21
	bl	zftl_flash_enter_slc_mode
.L391:
	adrp	x0, .LANCHOR25
	add	x1, x0, :lo12:.LANCHOR25
	and	x19, x21, 255
	and	w4, w23, 255
	lsr	w3, w23, 8
	and	w28, w20, 255
	ldrb	w2, [x1, 16]
	lsr	w27, w20, 8
	lsr	w26, w20, 16
	cmp	w2, 1
	lsr	w2, w23, 16
	bne	.L393
	add	x19, x24, x19, lsl 8
	ldrb	w1, [x1, 8]
	str	w1, [x19, 2056]
	adrp	x1, .LANCHOR30
	str	wzr, [x19, 2052]
	mov	x21, x1
	str	wzr, [x19, 2052]
	str	w4, [x19, 2052]
	str	w3, [x19, 2052]
	str	w2, [x19, 2052]
	ldrb	w2, [x1, #:lo12:.LANCHOR30]
	cbz	w2, .L394
	lsr	w23, w23, 24
	str	w23, [x19, 2052]
.L394:
	add	x0, x0, :lo12:.LANCHOR25
	ldrb	w0, [x0, 9]
	str	w0, [x19, 2056]
	bl	nandc_wait_flash_ready
	ldr	x0, [x25, #:lo12:.LANCHOR21]
	ldrb	w0, [x0, 12]
	cmp	w0, 3
	bne	.L395
	cbz	w22, .L395
	str	w22, [x19, 2056]
.L395:
	str	wzr, [x19, 2056]
	str	wzr, [x19, 2052]
	str	wzr, [x19, 2052]
	str	w28, [x19, 2052]
	ldrb	w0, [x21, #:lo12:.LANCHOR30]
	str	w27, [x19, 2052]
	str	w26, [x19, 2052]
	cbz	w0, .L416
	lsr	w20, w20, 24
	str	w20, [x19, 2052]
.L416:
	ldp	x21, x22, [sp, 32]
	mov	w0, 48
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	str	w0, [x19, 2056]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 96
	ret
.L390:
	ldr	x0, [x25, #:lo12:.LANCHOR21]
	ldrb	w0, [x0, 12]
	cmp	w0, 3
	bne	.L392
	adrp	x0, .LANCHOR35
	ldrb	w0, [x0, #:lo12:.LANCHOR35]
	cbnz	w0, .L392
	adrp	x0, .LANCHOR36
	ldrb	w0, [x0, #:lo12:.LANCHOR36]
	cbnz	w0, .L392
	sxtw	x0, w21
	add	x0, x0, 8
	add	x0, x24, x0, lsl 8
	str	w22, [x0, 8]
	b	.L391
.L392:
	mov	w0, w21
	bl	zftl_flash_exit_slc_mode
	b	.L391
.L393:
	ldr	x1, [x25, #:lo12:.LANCHOR21]
	ldrb	w5, [x1, 7]
	cmp	w5, 1
	bne	.L398
	ldrb	w5, [x1, 12]
	cmp	w5, 2
	bne	.L398
	add	x21, x21, 8
	mov	w5, 38
	add	x21, x24, x21, lsl 8
	str	w5, [x21, 8]
.L398:
	add	x5, x0, :lo12:.LANCHOR25
	add	x19, x24, x19, lsl 8
	ldrb	w5, [x5, 8]
	str	w5, [x19, 2056]
	str	w4, [x19, 2052]
	str	w3, [x19, 2052]
	str	w2, [x19, 2052]
	ldrb	w1, [x1, 12]
	cmp	w1, 3
	bne	.L399
	cbz	w22, .L399
	str	w22, [x19, 2056]
.L399:
	add	x0, x0, :lo12:.LANCHOR25
	ldrb	w0, [x0, 9]
	str	w0, [x19, 2056]
	str	w28, [x19, 2052]
	str	w27, [x19, 2052]
	str	w26, [x19, 2052]
	b	.L416
	.size	flash_start_plane_read, .-flash_start_plane_read
	.section	.text.flash_set_interface_mode,"ax",@progbits
	.align	2
	.global	flash_set_interface_mode
	.type	flash_set_interface_mode, %function
flash_set_interface_mode:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x21, x22, [sp, 32]
	adrp	x22, .LANCHOR47
	stp	x19, x20, [sp, 16]
	adrp	x21, .LANCHOR19
	stp	x23, x24, [sp, 48]
	adrp	x20, .LANCHOR48
	mov	w23, w0
	add	x22, x22, :lo12:.LANCHOR47
	add	x20, x20, :lo12:.LANCHOR48
	add	x21, x21, :lo12:.LANCHOR19
	str	x25, [sp, 64]
	mov	x25, 0
.L430:
	adrp	x0, .LANCHOR7
	ldr	x19, [x0, #:lo12:.LANCHOR7]
	lsl	x0, x25, 3
	ldrb	w24, [x0, x22]
	cmp	w24, 69
	beq	.L418
	add	w0, w24, 119
	cmp	w24, 44
	and	w1, w0, 255
	cset	w2, eq
	cmp	w1, 18
	bhi	.L431
	mov	x0, 32769
	movk	x0, 0x4, lsl 16
	lsr	x0, x0, x1
	mvn	x0, x0
.L419:
	and	w0, w0, 1
	eor	w0, w0, 1
	orr	w0, w2, w0
	cbz	w0, .L420
.L418:
	ldrb	w1, [x20]
	cmp	w23, 1
	bne	.L421
	tbz	x1, 0, .L420
	ldr	w0, [x21]
	tbz	x0, 12, .L422
	adrp	x0, .LC36
	add	x0, x0, :lo12:.LC36
	bl	printf
.L422:
	add	x0, x19, x25, lsl 8
	mov	w1, 239
	cmp	w24, 44
	str	w1, [x0, 2056]
	mov	w1, 137
	ccmp	w24, w1, 4, ne
	mov	w1, 1
	bne	.L423
.L454:
	str	w1, [x0, 2052]
	mov	w1, 5
.L453:
	str	w1, [x0, 2048]
.L428:
	str	wzr, [x0, 2048]
	str	wzr, [x0, 2048]
	str	wzr, [x0, 2048]
.L420:
	add	x25, x25, 1
	cmp	x25, 4
	bne	.L430
	bl	nandc_wait_flash_ready
	ldr	x25, [sp, 64]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
.L431:
	mov	x0, 1
	b	.L419
.L423:
	cmp	w24, 155
	beq	.L454
	mov	w2, 128
	str	w2, [x0, 2052]
	b	.L453
.L421:
	tbz	x1, 2, .L420
	ldr	w0, [x21]
	tbz	x0, 12, .L426
	adrp	x0, .LC37
	add	x0, x0, :lo12:.LC37
	bl	printf
.L426:
	add	x0, x19, x25, lsl 8
	mov	w1, 239
	cmp	w24, 44
	str	w1, [x0, 2056]
	mov	w1, 137
	ccmp	w24, w1, 4, ne
	bne	.L427
	mov	w1, 1
	str	w1, [x0, 2052]
	mov	w1, 35
	b	.L453
.L427:
	cmp	w24, 155
	bne	.L429
	mov	w1, 1
	str	w1, [x0, 2052]
	mov	w1, 37
	b	.L453
.L429:
	mov	w1, 128
	str	w1, [x0, 2052]
	str	wzr, [x0, 2048]
	b	.L428
	.size	flash_set_interface_mode, .-flash_set_interface_mode
	.section	.text.mt_auto_read_calibration_config,"ax",@progbits
	.align	2
	.type	mt_auto_read_calibration_config, %function
mt_auto_read_calibration_config:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w20, w1
	and	w19, w0, 255
	bl	nandc_wait_flash_ready
	adrp	x1, .LANCHOR7
	ubfiz	x0, x19, 8, 8
	ldr	x19, [x1, #:lo12:.LANCHOR7]
	add	x19, x19, x0
	mov	w0, 239
	str	w0, [x19, 2056]
	mov	w0, 150
	str	w0, [x19, 2052]
	mov	x0, 1
	bl	udelay
	str	w20, [x19, 2048]
	str	wzr, [x19, 2048]
	str	wzr, [x19, 2048]
	str	wzr, [x19, 2048]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	mt_auto_read_calibration_config, .-mt_auto_read_calibration_config
	.section	.text.flash_reset,"ax",@progbits
	.align	2
	.global	flash_reset
	.type	flash_reset, %function
flash_reset:
	adrp	x1, .LANCHOR7
	ubfiz	x0, x0, 8, 8
	add	x0, x0, 2048
	ldr	x1, [x1, #:lo12:.LANCHOR7]
	add	x1, x1, x0
	mov	w0, 255
	str	w0, [x1, 8]
	b	nandc_wait_flash_ready
	.size	flash_reset, .-flash_reset
	.section	.text.flash_read_id,"ax",@progbits
	.align	2
	.global	flash_read_id
	.type	flash_read_id, %function
flash_read_id:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	str	x21, [sp, 32]
	and	w21, w0, 255
	adrp	x0, .LANCHOR7
	stp	x19, x20, [sp, 16]
	mov	x19, x1
	ldr	x20, [x0, #:lo12:.LANCHOR7]
	mov	w0, w21
	bl	flash_reset
	mov	w0, w21
	bl	nandc_cs
	ubfiz	x0, x21, 8, 8
	add	x20, x20, x0
	mov	w0, 144
	str	w0, [x20, 2056]
	mov	x0, 1
	str	wzr, [x20, 2052]
	bl	udelay
	ldr	w0, [x20, 2048]
	strb	w0, [x19]
	ldr	w0, [x20, 2048]
	strb	w0, [x19, 1]
	ldr	w0, [x20, 2048]
	strb	w0, [x19, 2]
	ldr	w0, [x20, 2048]
	strb	w0, [x19, 3]
	ldr	w0, [x20, 2048]
	strb	w0, [x19, 4]
	ldr	w0, [x20, 2048]
	strb	w0, [x19, 5]
	ldr	w0, [x20, 2048]
	strb	w0, [x19, 6]
	ldr	w0, [x20, 2048]
	strb	w0, [x19, 7]
	bl	nandc_de_cs.constprop.32
	ldrb	w2, [x19]
	sub	w0, w2, #1
	and	w0, w0, 255
	cmp	w0, 253
	bhi	.L458
	ldrb	w7, [x19, 5]
	add	w1, w21, 1
	ldrb	w6, [x19, 4]
	adrp	x0, .LC38
	ldrb	w5, [x19, 3]
	add	x0, x0, :lo12:.LC38
	ldrb	w4, [x19, 2]
	ldrb	w3, [x19, 1]
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	b	printf
.L458:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	flash_read_id, .-flash_read_id
	.section	.text.flash_read_spare,"ax",@progbits
	.align	2
	.global	flash_read_spare
	.type	flash_read_spare, %function
flash_read_spare:
	stp	x29, x30, [sp, -32]!
	ubfiz	x0, x0, 8, 8
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x2
	adrp	x2, .LANCHOR32+9
	ldrb	w3, [x2, #:lo12:.LANCHOR32+9]
	adrp	x2, .LANCHOR7
	ldr	x19, [x2, #:lo12:.LANCHOR7]
	lsl	w3, w3, 9
	add	x19, x19, x0
	and	w0, w1, 255
	str	wzr, [x19, 2056]
	str	w3, [x19, 2052]
	lsr	w3, w3, 8
	str	w3, [x19, 2052]
	str	w0, [x19, 2052]
	lsr	w0, w1, 8
	str	w0, [x19, 2052]
	lsr	w1, w1, 16
	str	w1, [x19, 2052]
	mov	w0, 48
	str	w0, [x19, 2056]
	bl	nandc_wait_flash_ready
	ldr	w0, [x19, 2048]
	strb	w0, [x20]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	flash_read_spare, .-flash_read_spare
	.section	.text.flash_read_otp_data,"ax",@progbits
	.align	2
	.global	flash_read_otp_data
	.type	flash_read_otp_data, %function
flash_read_otp_data:
	stp	x29, x30, [sp, -48]!
	and	w4, w0, 255
	adrp	x0, .LANCHOR7
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w20, w1
	ldr	x19, [x0, #:lo12:.LANCHOR7]
	mov	w0, w4
	stp	x21, x22, [sp, 32]
	mov	x22, x2
	bl	nandc_cs
	ubfiz	x4, x4, 8, 8
	add	x19, x19, x4
	mov	w0, 239
	mov	w21, 144
	str	w0, [x19, 2056]
	mov	x0, 1
	str	w21, [x19, 2052]
	bl	udelay
	mov	w0, 1
	str	w0, [x19, 2048]
	str	wzr, [x19, 2048]
	str	wzr, [x19, 2048]
	str	wzr, [x19, 2048]
	bl	nandc_wait_flash_ready
	mov	w0, 238
	str	w0, [x19, 2056]
	str	w21, [x19, 2052]
	mov	w1, w20
	adrp	x0, .LC39
	add	x0, x0, :lo12:.LC39
	ldr	w2, [x19, 2048]
	ldr	w3, [x19, 2048]
	ldr	w4, [x19, 2048]
	bl	printf
	bl	nandc_wait_flash_ready
	str	wzr, [x19, 2056]
	str	wzr, [x19, 2052]
	and	w0, w20, 255
	str	wzr, [x19, 2052]
	str	w0, [x19, 2052]
	lsr	w0, w20, 8
	str	w0, [x19, 2052]
	lsr	w20, w20, 16
	str	w20, [x19, 2052]
	mov	w0, 48
	str	w0, [x19, 2056]
	bl	nandc_wait_flash_ready
	mov	x0, 0
.L464:
	ldr	w1, [x19, 2048]
	strb	w1, [x22, x0]
	add	x0, x0, 1
	cmp	x0, 16384
	bne	.L464
	mov	w0, 239
	str	w0, [x19, 2056]
	mov	w0, 144
	str	w0, [x19, 2052]
	mov	x0, 1
	bl	udelay
	ldp	x21, x22, [sp, 32]
	str	wzr, [x19, 2048]
	str	wzr, [x19, 2048]
	str	wzr, [x19, 2048]
	str	wzr, [x19, 2048]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	b	nandc_de_cs.constprop.32
	.size	flash_read_otp_data, .-flash_read_otp_data
	.section	.text.sandisk_prog_test_bad_block,"ax",@progbits
	.align	2
	.global	sandisk_prog_test_bad_block
	.type	sandisk_prog_test_bad_block, %function
sandisk_prog_test_bad_block:
	stp	x29, x30, [sp, -48]!
	and	x2, x0, 255
	mov	x0, x2
	add	x2, x2, 8
	add	x29, sp, 0
	stp	x21, x22, [sp, 32]
	mov	w22, w1
	adrp	x1, .LANCHOR7
	stp	x19, x20, [sp, 16]
	adrp	x20, .LANCHOR32
	ldr	x19, [x1, #:lo12:.LANCHOR7]
	add	x1, x20, :lo12:.LANCHOR32
	ldrb	w1, [x1, 29]
	add	x2, x19, x2, lsl 8
	cbz	w1, .L468
.L483:
	ubfiz	x0, x0, 8, 8
	str	w1, [x2, 8]
	add	x19, x19, x0
	mov	w0, 128
	str	w0, [x19, 2056]
	and	w0, w22, 255
	str	wzr, [x19, 2052]
	str	wzr, [x19, 2052]
	str	w0, [x19, 2052]
	lsr	w0, w22, 8
	str	w0, [x19, 2052]
	lsr	w0, w22, 16
	str	w0, [x19, 2052]
	mov	w0, 16
	str	w0, [x19, 2056]
	bl	nandc_wait_flash_ready
	mov	w0, 112
	str	w0, [x19, 2056]
	mov	x0, 1
	bl	udelay
	ldr	w2, [x19, 2048]
	cmp	w2, 255
	bne	.L470
	ldr	w2, [x19, 2048]
.L470:
	mov	w0, 5
	ands	w21, w2, w0
	beq	.L471
	adrp	x0, .LANCHOR19
	ldr	w0, [x0, #:lo12:.LANCHOR19]
	tbz	x0, 12, .L471
	adrp	x0, .LC40
	mov	w1, w22
	add	x0, x0, :lo12:.LC40
	bl	printf
.L471:
	add	x20, x20, :lo12:.LANCHOR32
	ldrb	w0, [x20, 30]
	cbz	w0, .L467
	str	w0, [x19, 2056]
.L467:
	mov	w0, w21
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
.L468:
	mov	w1, 162
	b	.L483
	.size	sandisk_prog_test_bad_block, .-sandisk_prog_test_bad_block
	.section	.text.nandc_rdy_status,"ax",@progbits
	.align	2
	.global	nandc_rdy_status
	.type	nandc_rdy_status, %function
nandc_rdy_status:
	adrp	x0, .LANCHOR7
	sub	sp, sp, #16
	ldr	x0, [x0, #:lo12:.LANCHOR7]
	ldr	w0, [x0]
	str	w0, [sp, 8]
	ldr	w0, [sp, 8]
	add	sp, sp, 16
	ubfx	x0, x0, 9, 1
	ret
	.size	nandc_rdy_status, .-nandc_rdy_status
	.section	.text.nandc_bch_sel,"ax",@progbits
	.align	2
	.global	nandc_bch_sel
	.type	nandc_bch_sel, %function
nandc_bch_sel:
	sub	sp, sp, #16
	str	wzr, [sp, 8]
	ldr	w1, [sp, 8]
	orr	w1, w1, 1
	str	w1, [sp, 8]
	adrp	x1, .LANCHOR49
	strb	w0, [x1, #:lo12:.LANCHOR49]
	adrp	x1, .LANCHOR27
	ldrb	w1, [x1, #:lo12:.LANCHOR27]
	cmp	w1, 9
	adrp	x1, .LANCHOR7
	bne	.L487
	ldr	x1, [x1, #:lo12:.LANCHOR7]
	cmp	w0, 70
	ldr	w2, [sp, 8]
	str	w2, [x1, 16]
	beq	.L493
	cmp	w0, 60
	beq	.L494
	cmp	w0, 40
	cset	w0, eq
	add	w0, w0, 1
.L488:
	str	wzr, [sp]
	ldr	w2, [sp]
	bfi	w2, w0, 25, 3
	str	w2, [sp]
	ldr	w0, [sp]
	orr	w0, w0, 1
	str	w0, [sp]
	ldr	w0, [sp]
	str	w0, [x1, 32]
.L486:
	add	sp, sp, 16
	ret
.L493:
	mov	w0, 0
	b	.L488
.L494:
	mov	w0, 3
	b	.L488
.L487:
	ldr	x2, [x1, #:lo12:.LANCHOR7]
	mov	w3, 16
	ldr	w1, [sp, 8]
	cmp	w0, w3
	str	w1, [x2, 8]
	str	wzr, [sp]
	ldr	w1, [sp]
	bfi	w1, w3, 8, 8
	str	w1, [sp]
	ldr	w1, [sp]
	and	w1, w1, -262145
	str	w1, [sp]
	bne	.L490
.L497:
	ldr	w0, [sp]
	and	w0, w0, -17
	b	.L498
.L490:
	cmp	w0, 24
	bne	.L492
	ldr	w0, [sp]
	orr	w0, w0, 16
.L498:
	str	w0, [sp]
	b	.L491
.L492:
	ldr	w1, [sp]
	cmp	w0, 40
	orr	w1, w1, 262144
	str	w1, [sp]
	ldr	w1, [sp]
	orr	w1, w1, 16
	str	w1, [sp]
	beq	.L497
.L491:
	ldr	w0, [sp]
	orr	w0, w0, 1
	str	w0, [sp]
	ldr	w0, [sp]
	str	w0, [x2, 12]
	b	.L486
	.size	nandc_bch_sel, .-nandc_bch_sel
	.section	.text.zftl_nandc_get_irq_status,"ax",@progbits
	.align	2
	.global	zftl_nandc_get_irq_status
	.type	zftl_nandc_get_irq_status, %function
zftl_nandc_get_irq_status:
	adrp	x1, .LANCHOR27
	ldrb	w1, [x1, #:lo12:.LANCHOR27]
	cmp	w1, 9
	bne	.L500
	ldr	w0, [x0, 296]
	ret
.L500:
	ldr	w0, [x0, 372]
	ret
	.size	zftl_nandc_get_irq_status, .-zftl_nandc_get_irq_status
	.section	.text.rk_nandc_flash_ready,"ax",@progbits
	.align	2
	.global	rk_nandc_flash_ready
	.type	rk_nandc_flash_ready, %function
rk_nandc_flash_ready:
	ret
	.size	rk_nandc_flash_ready, .-rk_nandc_flash_ready
	.section	.text.nandc_iqr_wait_flash_ready,"ax",@progbits
	.align	2
	.global	nandc_iqr_wait_flash_ready
	.type	nandc_iqr_wait_flash_ready, %function
nandc_iqr_wait_flash_ready:
	ret
	.size	nandc_iqr_wait_flash_ready, .-nandc_iqr_wait_flash_ready
	.section	.text.rk_nandc_flash_xfer_completed,"ax",@progbits
	.align	2
	.global	rk_nandc_flash_xfer_completed
	.type	rk_nandc_flash_xfer_completed, %function
rk_nandc_flash_xfer_completed:
	ret
	.size	rk_nandc_flash_xfer_completed, .-rk_nandc_flash_xfer_completed
	.section	.text.nandc_xfer_start,"ax",@progbits
	.align	2
	.global	nandc_xfer_start
	.type	nandc_xfer_start, %function
nandc_xfer_start:
	stp	x29, x30, [sp, -80]!
	and	w1, w1, 255
	adrp	x4, .LANCHOR52
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	and	w20, w0, 255
	adrp	x0, .LANCHOR27
	str	x21, [sp, 32]
	and	w6, w20, 1
	adrp	x21, .LANCHOR7
	ldrb	w0, [x0, #:lo12:.LANCHOR27]
	cmp	w0, 9
	add	w0, w1, 1
	bne	.L506
	str	wzr, [x29, 56]
	mov	w5, 1
	ubfx	x0, x0, 1, 6
	ldr	w1, [x29, 56]
	bfi	w1, w6, 1, 1
	str	w1, [x29, 56]
	ldr	w1, [x29, 56]
	orr	w1, w1, 8
	str	w1, [x29, 56]
	ldr	w1, [x29, 56]
	bfi	w1, w5, 5, 2
	str	w1, [x29, 56]
	ldr	w1, [x29, 56]
	orr	w1, w1, 536870912
	str	w1, [x29, 56]
	ldr	w1, [x29, 56]
	orr	w1, w1, 1024
	str	w1, [x29, 56]
	ldr	w1, [x29, 56]
	and	w1, w1, -17
	str	w1, [x29, 56]
	ldr	w1, [x29, 56]
	bfi	w1, w0, 22, 6
	str	w1, [x29, 56]
	ldr	w0, [x29, 56]
	orr	w0, w0, 128
	str	w0, [x29, 56]
	adrp	x0, .LANCHOR50
	ldrb	w0, [x0, #:lo12:.LANCHOR50]
	cbz	w0, .L507
	adrp	x0, .LANCHOR51
	ldrb	w0, [x0, #:lo12:.LANCHOR51]
	cbz	w0, .L507
	ldr	w0, [x29, 56]
	orr	w0, w0, 512
	str	w0, [x29, 56]
.L507:
	ldr	w0, [x29, 56]
	add	x19, x4, :lo12:.LANCHOR52
	add	x1, x2, 63
	and	x1, x1, -64
	ubfx	x0, x0, 22, 6
	stp	x2, x3, [x19, 8]
	ubfiz	x0, x0, 10, 6
	stp	w2, w3, [x19, 24]
	add	x1, x1, x0
	and	x0, x2, -64
	bl	flush_dcache_range
	ldr	x0, [x19, 16]
	add	x1, x0, 63
	and	x0, x0, -64
	and	x1, x1, -64
	add	x1, x1, 64
	bl	flush_dcache_range
	mov	w0, 1
	str	w0, [x19, 32]
	ldr	x0, [x21, #:lo12:.LANCHOR7]
	mov	w2, 16
	ldr	w1, [x19, 24]
	cmp	w20, 0
	str	w1, [x0, 52]
	ldr	w1, [x19, 28]
	str	w1, [x0, 56]
	ldr	w1, [x0, 48]
	str	w1, [x29, 64]
	ldr	w1, [x29, 64]
	bfi	w1, w2, 9, 5
	str	w1, [x29, 64]
	mov	w2, 2
	ldr	w1, [x29, 64]
	orr	w1, w1, 448
	str	w1, [x29, 64]
	ldr	w1, [x29, 64]
	bfi	w1, w2, 3, 3
	str	w1, [x29, 64]
	cset	w2, eq
	ldr	w1, [x29, 64]
	orr	w1, w1, 4
	str	w1, [x29, 64]
	ldr	w1, [x29, 64]
	bfi	w1, w2, 1, 1
	str	w1, [x29, 64]
	ldr	w1, [x29, 64]
	orr	w1, w1, 1
	str	w1, [x29, 64]
	adrp	x1, .LANCHOR53
	ldrh	w2, [x1, #:lo12:.LANCHOR53]
	ldr	w1, [x29, 64]
	bfi	w1, w2, 16, 11
	str	w1, [x29, 64]
	ldr	w1, [x29, 64]
	str	w1, [x0, 48]
	ldr	w1, [x29, 56]
	str	w1, [x0, 16]
	ldr	w1, [x29, 56]
	orr	w1, w1, 4
	str	w1, [x29, 56]
	ldr	w1, [x29, 56]
	str	w1, [x0, 16]
.L505:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 80
	ret
.L506:
	ldr	x5, [x21, #:lo12:.LANCHOR7]
	mov	w7, 16
	ubfx	x0, x0, 1, 6
	ldr	w5, [x5, 12]
	str	w5, [x29, 72]
	ldr	w5, [x29, 72]
	bfi	w5, w7, 8, 8
	str	w5, [x29, 72]
	ldr	w5, [x29, 72]
	and	w5, w5, -9
	str	w5, [x29, 72]
	ldr	w5, [x29, 72]
	and	w5, w5, -225
	str	w5, [x29, 72]
	str	wzr, [x29, 56]
	ldr	w5, [x29, 56]
	bfi	w5, w6, 1, 1
	str	w5, [x29, 56]
	mov	w6, 1
	ldr	w5, [x29, 56]
	orr	w5, w5, 8
	str	w5, [x29, 56]
	ldr	w5, [x29, 56]
	bfi	w5, w6, 5, 2
	str	w5, [x29, 56]
	ldr	w5, [x29, 56]
	orr	w5, w5, 536870912
	str	w5, [x29, 56]
	ldr	w5, [x29, 56]
	orr	w5, w5, 1024
	str	w5, [x29, 56]
	ldr	w5, [x29, 56]
	and	w5, w5, -17
	str	w5, [x29, 56]
	ldr	w5, [x29, 56]
	bfi	w5, w0, 22, 6
	str	w5, [x29, 56]
	cbz	w20, .L509
	adrp	x0, .LANCHOR49
	ubfx	x1, x1, 1, 7
	ldr	x8, [x4, #:lo12:.LANCHOR52]
	add	x1, x3, x1, lsl 2
	ldrb	w0, [x0, #:lo12:.LANCHOR49]
	mov	w5, 64
	cmp	w0, 25
	mov	w0, 128
	csel	w5, w5, w0, cc
	mov	w0, 0
.L511:
	add	w7, w5, w0
	cmp	x3, x1
	bne	.L512
.L513:
	add	x19, x4, :lo12:.LANCHOR52
	ldr	x0, [x4, #:lo12:.LANCHOR52]
	add	x1, x2, 63
	and	x1, x1, -64
	stp	x2, x0, [x19, 8]
	stp	w2, w0, [x19, 24]
	ldr	w0, [x29, 56]
	ubfx	x0, x0, 22, 6
	ubfiz	x0, x0, 10, 6
	add	x1, x1, x0
	and	x0, x2, -64
	bl	flush_dcache_range
	ldr	x0, [x19, 16]
	ldr	w1, [x29, 56]
	add	x2, x0, 63
	and	x0, x0, -64
	and	x2, x2, -64
	ubfx	x1, x1, 22, 6
	ubfiz	x1, x1, 7, 6
	add	x1, x2, x1
	bl	flush_dcache_range
	mov	w0, 1
	str	w0, [x19, 32]
	ldr	x0, [x21, #:lo12:.LANCHOR7]
	mov	w2, 16
	ldr	w1, [x19, 24]
	cmp	w20, 0
	str	w1, [x0, 20]
	ldr	w1, [x19, 28]
	str	w1, [x0, 24]
	str	wzr, [x29, 64]
	ldr	w1, [x29, 64]
	bfi	w1, w2, 9, 5
	str	w1, [x29, 64]
	mov	w2, 2
	ldr	w1, [x29, 64]
	orr	w1, w1, 448
	str	w1, [x29, 64]
	ldr	w1, [x29, 64]
	bfi	w1, w2, 3, 3
	str	w1, [x29, 64]
	cset	w2, eq
	ldr	w1, [x29, 64]
	orr	w1, w1, 4
	str	w1, [x29, 64]
	ldr	w1, [x29, 64]
	bfi	w1, w2, 1, 1
	str	w1, [x29, 64]
	ldr	w1, [x29, 64]
	orr	w1, w1, 1
	str	w1, [x29, 64]
	ldr	w1, [x29, 64]
	str	w1, [x0, 16]
	ldr	w1, [x29, 72]
	str	w1, [x0, 12]
	ldr	w1, [x29, 56]
	str	w1, [x0, 8]
	ldr	w1, [x29, 56]
	orr	w1, w1, 4
	str	w1, [x29, 56]
	ldr	w1, [x29, 56]
	str	w1, [x0, 8]
	b	.L505
.L512:
	ldrh	w10, [x3]
	and	x0, x0, 4294967292
	ldrh	w6, [x3, 2]
	add	x3, x3, 4
	orr	x6, x10, x6, lsl 16
	str	w6, [x8, x0]
	mov	w0, w7
	b	.L511
.L509:
	ldr	x0, [x4, #:lo12:.LANCHOR52]
	str	w6, [x0]
	b	.L513
	.size	nandc_xfer_start, .-nandc_xfer_start
	.section	.text.nandc_set_seed,"ax",@progbits
	.align	2
	.global	nandc_set_seed
	.type	nandc_set_seed, %function
nandc_set_seed:
	and	x0, x0, 127
	adrp	x1, .LANCHOR54
	add	x1, x1, :lo12:.LANCHOR54
	ldrh	w0, [x1, x0, lsl 1]
	adrp	x1, .LANCHOR51
	ldrb	w2, [x1, #:lo12:.LANCHOR51]
	orr	w1, w0, -1073741824
	cmp	w2, 0
	csel	w0, w1, w0, ne
	adrp	x1, .LANCHOR27
	ldrb	w1, [x1, #:lo12:.LANCHOR27]
	cmp	w1, 9
	adrp	x1, .LANCHOR7
	ldr	x1, [x1, #:lo12:.LANCHOR7]
	bne	.L524
	str	w0, [x1, 520]
	ret
.L524:
	str	w0, [x1, 336]
	ret
	.size	nandc_set_seed, .-nandc_set_seed
	.section	.text.zftl_flash_de_init,"ax",@progbits
	.align	2
	.global	zftl_flash_de_init
	.type	zftl_flash_de_init, %function
zftl_flash_de_init:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	bl	nandc_wait_flash_ready
	adrp	x0, .LANCHOR0
	ldrb	w0, [x0, #:lo12:.LANCHOR0]
	cbz	w0, .L529
	adrp	x0, .LANCHOR24
	ldrb	w0, [x0, #:lo12:.LANCHOR24]
	cbnz	w0, .L529
	adrp	x0, .LANCHOR27
	ldrb	w0, [x0, #:lo12:.LANCHOR27]
	cmp	w0, 9
	beq	.L529
	mov	w0, 0
	bl	zftl_flash_exit_slc_mode
.L529:
	adrp	x19, .LANCHOR26
	mov	w0, 0
	bl	hynix_reconfig_rr_para
	ldrb	w0, [x19, #:lo12:.LANCHOR26]
	cbz	w0, .L530
	adrp	x0, .LANCHOR48
	ldrb	w0, [x0, #:lo12:.LANCHOR48]
	tbz	x0, 0, .L530
	mov	w0, 1
	bl	flash_set_interface_mode
	mov	w0, 1
	bl	nandc_set_if_mode
	strb	wzr, [x19, #:lo12:.LANCHOR26]
.L530:
	adrp	x3, .LANCHOR51
	ldrb	w0, [x3, #:lo12:.LANCHOR51]
	cbz	w0, .L531
	mov	w0, 0
	strb	wzr, [x3, #:lo12:.LANCHOR51]
	bl	nandc_set_seed
	mov	w0, 1
	strb	w0, [x3, #:lo12:.LANCHOR51]
.L531:
	mov	w0, 0
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	zftl_flash_de_init, .-zftl_flash_de_init
	.section	.text.nandc_randomizer_enable,"ax",@progbits
	.align	2
	.global	nandc_randomizer_enable
	.type	nandc_randomizer_enable, %function
nandc_randomizer_enable:
	adrp	x1, .LANCHOR51
	strb	w0, [x1, #:lo12:.LANCHOR51]
	ret
	.size	nandc_randomizer_enable, .-nandc_randomizer_enable
	.section	.text.nandc_get_chip_if,"ax",@progbits
	.align	2
	.global	nandc_get_chip_if
	.type	nandc_get_chip_if, %function
nandc_get_chip_if:
	adrp	x1, .LANCHOR7
	ubfiz	x0, x0, 8, 8
	add	x0, x0, 2048
	ldr	x1, [x1, #:lo12:.LANCHOR7]
	add	x0, x1, x0
	ret
	.size	nandc_get_chip_if, .-nandc_get_chip_if
	.section	.text.buf_reinit,"ax",@progbits
	.align	2
	.global	buf_reinit
	.type	buf_reinit, %function
buf_reinit:
	adrp	x0, .LANCHOR55
	add	x1, x0, :lo12:.LANCHOR55
	mov	w2, 0
.L551:
	and	w3, w2, 255
	strb	wzr, [x1, 2]
	add	w4, w3, 1
	strb	w3, [x1, 1]
	strb	w4, [x1]
	add	w2, w2, 1
	str	xzr, [x1, 16]
	cmp	w2, 32
	add	x1, x1, 64
	bne	.L551
	add	x0, x0, :lo12:.LANCHOR55
	mov	w1, -1
	strb	w1, [x0, 1984]
	adrp	x0, .LANCHOR56
	strb	wzr, [x0, #:lo12:.LANCHOR56]
	adrp	x0, .LANCHOR57
	strb	w2, [x0, #:lo12:.LANCHOR57]
	ret
	.size	buf_reinit, .-buf_reinit
	.section	.text.buf_add_tail,"ax",@progbits
	.align	2
	.global	buf_add_tail
	.type	buf_add_tail, %function
buf_add_tail:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	str	x21, [sp, 32]
	mov	w0, -1
	strb	w0, [x1]
	mov	x20, x1
	ldrb	w1, [x19]
	cmp	w1, 255
	bne	.L559
	ldrb	w0, [x20, 1]
	cmp	w0, 255
	bne	.L555
	adrp	x1, .LANCHOR58
	adrp	x0, .LC0
	mov	w2, 74
	add	x1, x1, :lo12:.LANCHOR58
	add	x0, x0, :lo12:.LC0
	bl	printf
.L555:
	ldrb	w0, [x20, 1]
	strb	w0, [x19]
.L553:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
.L559:
	adrp	x0, .LANCHOR55
	add	x2, x0, :lo12:.LANCHOR55
	mov	x19, x0
.L560:
	sbfiz	x0, x1, 6, 32
	mov	w21, w1
	ldrb	w1, [x2, x0]
	cmp	w1, 255
	bne	.L560
	ldrb	w0, [x20, 1]
	cmp	w0, 255
	bne	.L557
	adrp	x1, .LANCHOR58
	adrp	x0, .LC0
	mov	w2, 81
	add	x1, x1, :lo12:.LANCHOR58
	add	x0, x0, :lo12:.LC0
	bl	printf
.L557:
	add	x0, x19, :lo12:.LANCHOR55
	sbfiz	x21, x21, 6, 32
	ldrb	w1, [x20, 1]
	strb	w1, [x0, x21]
	b	.L553
	.size	buf_add_tail, .-buf_add_tail
	.section	.text.queue_read_cmd,"ax",@progbits
	.align	2
	.type	queue_read_cmd, %function
queue_read_cmd:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	mov	w0, 48
	ldr	w1, [x19, 40]
	bl	flash_start_page_read
	strb	wzr, [x19, 59]
	mov	w0, 1
	strb	w0, [x19, 58]
	mov	w0, -1
	strb	w0, [x19]
	mov	x1, x19
	adrp	x0, .LANCHOR59
	ldr	x19, [sp, 16]
	add	x0, x0, :lo12:.LANCHOR59
	ldp	x29, x30, [sp], 32
	b	buf_add_tail
	.size	queue_read_cmd, .-queue_read_cmd
	.section	.text.zbuf_free,"ax",@progbits
	.align	2
	.global	zbuf_free
	.type	zbuf_free, %function
zbuf_free:
	ldrb	w1, [x0, 2]
	adrp	x2, .LANCHOR56
	and	w1, w1, 8
	strb	w1, [x0, 2]
	cbz	w1, .L565
	ldr	w1, [x0, 36]
	cmn	w1, #1
	beq	.L565
	stp	x29, x30, [sp, -16]!
	mov	x1, x0
	add	x0, x2, :lo12:.LANCHOR56
	add	x29, sp, 0
	bl	buf_add_tail
	adrp	x1, .LANCHOR57
	ldp	x29, x30, [sp], 16
	ldrb	w0, [x1, #:lo12:.LANCHOR57]
	add	w0, w0, 1
	strb	w0, [x1, #:lo12:.LANCHOR57]
	ret
.L565:
	ldrb	w1, [x2, #:lo12:.LANCHOR56]
	strb	w1, [x0]
	adrp	x1, .LANCHOR57
	ldrb	w0, [x0, 1]
	strb	w0, [x2, #:lo12:.LANCHOR56]
	ldrb	w0, [x1, #:lo12:.LANCHOR57]
	add	w0, w0, 1
	strb	w0, [x1, #:lo12:.LANCHOR57]
	ret
	.size	zbuf_free, .-zbuf_free
	.section	.text.buf_alloc,"ax",@progbits
	.align	2
	.global	buf_alloc
	.type	buf_alloc, %function
buf_alloc:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	adrp	x19, .LANCHOR57
	and	w20, w0, 255
	ldrb	w0, [x19, #:lo12:.LANCHOR57]
	cbz	w0, .L578
.L581:
	adrp	x2, .LANCHOR56
	adrp	x1, .LANCHOR55
	add	x0, x1, :lo12:.LANCHOR55
	ldrb	w3, [x2, #:lo12:.LANCHOR56]
	ubfiz	x4, x3, 6, 8
	add	x0, x0, x4
	mov	x4, x2
	cbz	w20, .L579
.L580:
	add	x1, x1, :lo12:.LANCHOR55
	sbfiz	x3, x3, 6, 32
	add	x2, x1, x3
	ldrb	w5, [x1, x3]
	strb	w5, [x4, #:lo12:.LANCHOR56]
	ldrb	w4, [x19, #:lo12:.LANCHOR57]
	strh	wzr, [x2, 50]
	sub	w4, w4, #1
	strb	w4, [x19, #:lo12:.LANCHOR57]
	mov	w4, 1
	strb	wzr, [x2, 56]
	strb	w4, [x2, 2]
	mov	w4, -1
	strb	wzr, [x2, 57]
	strb	w4, [x1, x3]
	mov	w1, -1
	str	xzr, [x2, 16]
	str	w1, [x2, 36]
	b	.L577
.L578:
	mov	w2, 121
	adrp	x1, .LANCHOR60
	adrp	x0, .LC0
	add	x1, x1, :lo12:.LANCHOR60
	add	x0, x0, :lo12:.LC0
	bl	printf
	ldrb	w0, [x19, #:lo12:.LANCHOR57]
	cbnz	w0, .L581
.L583:
	mov	x0, 0
.L577:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L579:
	ldrb	w2, [x19, #:lo12:.LANCHOR57]
	cmp	w2, 1
	bne	.L580
	b	.L583
	.size	buf_alloc, .-buf_alloc
	.section	.text.buf_remove_buf,"ax",@progbits
	.align	2
	.global	buf_remove_buf
	.type	buf_remove_buf, %function
buf_remove_buf:
	ldrb	w4, [x1, 1]
	ldrb	w2, [x0]
	cmp	w4, w2
	bne	.L591
	ldrb	w1, [x1]
	strb	w1, [x0]
.L595:
	mov	w0, 1
	ret
.L592:
	mov	w3, w2
	sbfiz	x2, x2, 6, 32
	ldrb	w2, [x0, x2]
	cmp	w4, w2
	bne	.L593
	sbfiz	x3, x3, 6, 32
	ldrb	w2, [x1]
	strb	w2, [x0, x3]
	mov	w0, -1
	strb	w0, [x1]
	b	.L595
.L591:
	adrp	x0, .LANCHOR55
	add	x0, x0, :lo12:.LANCHOR55
.L593:
	cmp	w2, 255
	bne	.L592
	mov	w0, 0
	ret
	.size	buf_remove_buf, .-buf_remove_buf
	.section	.text.buf_remove_free,"ax",@progbits
	.align	2
	.global	buf_remove_free
	.type	buf_remove_free, %function
buf_remove_free:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	adrp	x19, .LANCHOR57
	mov	x20, x0
	ldrb	w0, [x19, #:lo12:.LANCHOR57]
	cbnz	w0, .L597
	adrp	x1, .LANCHOR61
	adrp	x0, .LC0
	mov	w2, 172
	add	x1, x1, :lo12:.LANCHOR61
	add	x0, x0, :lo12:.LC0
	bl	printf
.L597:
	ldrb	w0, [x19, #:lo12:.LANCHOR57]
	cbz	w0, .L596
	mov	x1, x20
	adrp	x0, .LANCHOR56
	add	x0, x0, :lo12:.LANCHOR56
	bl	buf_remove_buf
	cmp	w0, 1
	bne	.L596
	ldrb	w0, [x19, #:lo12:.LANCHOR57]
	sub	w0, w0, #1
	strb	w0, [x19, #:lo12:.LANCHOR57]
	ldrb	w0, [x20, 2]
	orr	w0, w0, 1
	strb	w0, [x20, 2]
.L596:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	buf_remove_free, .-buf_remove_free
	.section	.text.dump_buf_info,"ax",@progbits
	.align	2
	.global	dump_buf_info
	.type	dump_buf_info, %function
dump_buf_info:
	sub	sp, sp, #64
	adrp	x0, .LANCHOR59
	stp	x29, x30, [sp, 16]
	add	x29, sp, 16
	ldrb	w1, [x0, #:lo12:.LANCHOR59]
	stp	x19, x20, [sp, 32]
	adrp	x0, .LC41
	str	x21, [sp, 48]
	add	x0, x0, :lo12:.LC41
	adrp	x19, .LANCHOR55
	add	x19, x19, :lo12:.LANCHOR55
	bl	printf
	adrp	x20, .LC47
	adrp	x0, .LANCHOR62
	add	x20, x20, :lo12:.LC47
	add	x21, x19, 2048
	ldrb	w1, [x0, #:lo12:.LANCHOR62]
	adrp	x0, .LC42
	add	x0, x0, :lo12:.LC42
	bl	printf
	adrp	x0, .LANCHOR63
	ldrb	w1, [x0, #:lo12:.LANCHOR63]
	adrp	x0, .LC43
	add	x0, x0, :lo12:.LC43
	bl	printf
	adrp	x0, .LANCHOR64
	ldrb	w1, [x0, #:lo12:.LANCHOR64]
	adrp	x0, .LC44
	add	x0, x0, :lo12:.LC44
	bl	printf
	adrp	x0, .LANCHOR56
	ldrb	w1, [x0, #:lo12:.LANCHOR56]
	adrp	x0, .LC45
	add	x0, x0, :lo12:.LC45
	bl	printf
	adrp	x0, .LANCHOR57
	ldrb	w1, [x0, #:lo12:.LANCHOR57]
	adrp	x0, .LC46
	add	x0, x0, :lo12:.LC46
	bl	printf
.L603:
	ldp	w7, w0, [x19, 36]
	str	w0, [sp]
	ldrb	w5, [x19, 58]
	mov	x0, x20
	ldrh	w4, [x19, 50]
	add	x19, x19, 64
	ldrb	w3, [x19, -62]
	ldrb	w2, [x19, -64]
	ldrb	w1, [x19, -63]
	ldr	w6, [x19, -12]
	bl	printf
	cmp	x19, x21
	bne	.L603
	ldp	x19, x20, [sp, 32]
	ldp	x29, x30, [sp, 16]
	ldr	x21, [sp, 48]
	add	sp, sp, 64
	ret
	.size	dump_buf_info, .-dump_buf_info
	.section	.text.flash_check_bad_block,"ax",@progbits
	.align	2
	.global	flash_check_bad_block
	.type	flash_check_bad_block, %function
flash_check_bad_block:
	adrp	x3, .LANCHOR32
	add	x3, x3, :lo12:.LANCHOR32
	and	w5, w0, 255
	lsr	w4, w1, 5
	and	w1, w1, 31
	ldrb	w0, [x3, 13]
	ldrh	w2, [x3, 14]
	mul	w2, w2, w0
	mov	x0, 912
	and	w2, w2, 65535
	add	w2, w2, 31
	asr	w2, w2, 5
	lsl	w2, w2, 2
	umaddl	x0, w2, w5, x0
	adrp	x2, .LANCHOR6
	ldr	x2, [x2, #:lo12:.LANCHOR6]
	add	x0, x0, x4, uxtw 2
	ldr	w0, [x2, x0]
	lsr	w0, w0, w1
	and	w0, w0, 1
	ret
	.size	flash_check_bad_block, .-flash_check_bad_block
	.section	.text.flash_mask_bad_block,"ax",@progbits
	.align	2
	.global	flash_mask_bad_block
	.type	flash_mask_bad_block, %function
flash_mask_bad_block:
	stp	x29, x30, [sp, -48]!
	mov	w2, w1
	add	x29, sp, 0
	str	x21, [sp, 32]
	and	w21, w0, 255
	adrp	x0, .LANCHOR32
	add	x0, x0, :lo12:.LANCHOR32
	stp	x19, x20, [sp, 16]
	mov	w20, w1
	ldrh	w19, [x0, 14]
	ldrb	w1, [x0, 13]
	adrp	x0, .LC48
	add	x0, x0, :lo12:.LC48
	mul	w19, w19, w1
	mov	w1, w21
	bl	printf
	and	w19, w19, 65535
	lsr	w0, w20, 5
	add	w1, w19, 31
	mov	x19, 912
	asr	w1, w1, 5
	and	w20, w20, 31
	lsl	w1, w1, 2
	umaddl	x1, w1, w21, x19
	ldr	x21, [sp, 32]
	add	x1, x1, x0, uxtw 2
	adrp	x0, .LANCHOR6
	ldr	x2, [x0, #:lo12:.LANCHOR6]
	mov	w0, 1
	lsl	w0, w0, w20
	ldr	w20, [x2, x1]
	orr	w20, w20, w0
	str	w20, [x2, x1]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.size	flash_mask_bad_block, .-flash_mask_bad_block
	.section	.text.ftl_gc_write_buf,"ax",@progbits
	.align	2
	.global	ftl_gc_write_buf
	.type	ftl_gc_write_buf, %function
ftl_gc_write_buf:
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
	ldrb	w1, [x0, 2]
	orr	w1, w1, 2
	strb	w1, [x0, 2]
	mov	x1, x0
	adrp	x0, .LANCHOR65
	add	x0, x0, :lo12:.LANCHOR65
	bl	buf_add_tail
	adrp	x1, .LANCHOR66
	ldp	x29, x30, [sp], 16
	ldrb	w0, [x1, #:lo12:.LANCHOR66]
	add	w0, w0, 1
	and	w0, w0, 255
	strb	w0, [x1, #:lo12:.LANCHOR66]
	ret
	.size	ftl_gc_write_buf, .-ftl_gc_write_buf
	.section	.text.zftl_cache_flush,"ax",@progbits
	.align	2
	.global	zftl_cache_flush
	.type	zftl_cache_flush, %function
zftl_cache_flush:
	ret
	.size	zftl_cache_flush, .-zftl_cache_flush
	.section	.text.zftl_get_density,"ax",@progbits
	.align	2
	.global	zftl_get_density
	.type	zftl_get_density, %function
zftl_get_density:
	cbnz	w0, .L613
	adrp	x0, .LANCHOR67
	ldr	w0, [x0, #:lo12:.LANCHOR67]
	ret
.L613:
	cmp	w0, 4
	cset	w0, cc
	lsl	w0, w0, 13
	ret
	.size	zftl_get_density, .-zftl_get_density
	.section	.text.gc_hook,"ax",@progbits
	.align	2
	.global	gc_hook
	.type	gc_hook, %function
gc_hook:
	ret
	.size	gc_hook, .-gc_hook
	.section	.text.vpn_check,"ax",@progbits
	.align	2
	.global	vpn_check
	.type	vpn_check, %function
vpn_check:
	ret
	.size	vpn_check, .-vpn_check
	.section	.text.ftl_scan_all_data,"ax",@progbits
	.align	2
	.global	ftl_scan_all_data
	.type	ftl_scan_all_data, %function
ftl_scan_all_data:
	ret
	.size	ftl_scan_all_data, .-ftl_scan_all_data
	.section	.text.FtlGetCurEraseBlock,"ax",@progbits
	.align	2
	.global	FtlGetCurEraseBlock
	.type	FtlGetCurEraseBlock, %function
FtlGetCurEraseBlock:
	adrp	x0, .LANCHOR68
	ldrh	w0, [x0, #:lo12:.LANCHOR68]
	ret
	.size	FtlGetCurEraseBlock, .-FtlGetCurEraseBlock
	.section	.text.FtlGetAllBlockNum,"ax",@progbits
	.align	2
	.global	FtlGetAllBlockNum
	.type	FtlGetAllBlockNum, %function
FtlGetAllBlockNum:
	adrp	x0, .LANCHOR8
	ldrh	w0, [x0, #:lo12:.LANCHOR8]
	ret
	.size	FtlGetAllBlockNum, .-FtlGetAllBlockNum
	.section	.text.FtlLowFormat,"ax",@progbits
	.align	2
	.global	FtlLowFormat
	.type	FtlLowFormat, %function
FtlLowFormat:
	mov	w0, 0
	ret
	.size	FtlLowFormat, .-FtlLowFormat
	.section	.text.gc_add_sblk,"ax",@progbits
	.align	2
	.global	gc_add_sblk
	.type	gc_add_sblk, %function
gc_add_sblk:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x21, x22, [sp, 32]
	adrp	x21, .LANCHOR19
	stp	x19, x20, [sp, 16]
	and	w19, w0, 65535
	ldr	w0, [x21, #:lo12:.LANCHOR19]
	and	w22, w1, 65535
	stp	x23, x24, [sp, 48]
	and	w23, w2, 65535
	tbz	x0, 8, .L623
	adrp	x1, .LANCHOR11
	uxtw	x0, w19
	mov	w3, w23
	ldr	x2, [x1, #:lo12:.LANCHOR11]
	adrp	x1, .LANCHOR9
	ldr	x1, [x1, #:lo12:.LANCHOR9]
	ldrh	w5, [x2, x0, lsl 1]
	mov	w2, w22
	add	x1, x1, x0, lsl 2
	adrp	x0, .LC49
	add	x0, x0, :lo12:.LC49
	ldrb	w4, [x1, 2]
	adrp	x1, .LANCHOR69
	ldrh	w7, [x1, #:lo12:.LANCHOR69]
	adrp	x1, .LANCHOR70+56
	ubfx	x4, x4, 5, 3
	ldrh	w6, [x1, #:lo12:.LANCHOR70+56]
	mov	w1, w19
	bl	printf
.L623:
	adrp	x0, .LANCHOR8
	mov	x20, x0
	ldrh	w1, [x0, #:lo12:.LANCHOR8]
	cmp	w1, w19
	bhi	.L624
	adrp	x1, .LANCHOR71
	adrp	x0, .LC0
	mov	w2, 543
	add	x1, x1, :lo12:.LANCHOR71
	add	x0, x0, :lo12:.LC0
	bl	printf
.L624:
	ldrh	w0, [x20, #:lo12:.LANCHOR8]
	cmp	w0, w19
	bhi	.L625
	ldr	w0, [x21, #:lo12:.LANCHOR19]
	tbz	x0, 10, .L647
	adrp	x0, .LC50
	mov	w3, w23
	mov	w2, w22
	mov	w1, w19
	add	x0, x0, :lo12:.LC50
	bl	printf
.L647:
	mov	w0, 0
	b	.L622
.L625:
	adrp	x1, .LANCHOR11
	uxtw	x0, w19
	ldr	x1, [x1, #:lo12:.LANCHOR11]
	ldrh	w3, [x1, x0, lsl 1]
	adrp	x1, .LANCHOR9
	ldr	x1, [x1, #:lo12:.LANCHOR9]
	add	x0, x1, x0, lsl 2
	ldrb	w2, [x0, 2]
	tst	w2, 224
	bne	.L627
	cbz	w3, .L647
	mov	w2, 553
	adrp	x1, .LANCHOR71
	adrp	x0, .LC0
	add	x1, x1, :lo12:.LANCHOR71
	add	x0, x0, :lo12:.LC0
	bl	printf
	b	.L647
.L627:
	adrp	x0, .LANCHOR70
	add	x1, x0, :lo12:.LANCHOR70
	ldrh	w0, [x0, #:lo12:.LANCHOR70]
	cmp	w0, w19
	beq	.L647
	adrp	x24, .LANCHOR12
	ldr	x0, [x24, #:lo12:.LANCHOR12]
	ldrh	w4, [x0, 48]
	cmp	w4, w19
	beq	.L647
	ldrh	w4, [x0, 16]
	cmp	w4, w19
	beq	.L647
	ldrh	w4, [x0, 80]
	cmp	w4, w19
	beq	.L647
	ldrh	w5, [x1, 56]
	add	x1, x1, 58
	mov	w4, 0
.L628:
	cmp	w4, w5
	bcc	.L629
	cbnz	w22, .L633
	adrp	x1, .LANCHOR72
	ldrh	w6, [x1, #:lo12:.LANCHOR72]
	cmp	w19, w6
	beq	.L647
	adrp	x4, .LANCHOR73
	add	x4, x4, :lo12:.LANCHOR73
	mov	x1, 0
.L632:
	ldrh	w7, [x1, x4]
	cmp	w19, w7
	bne	.L631
	ldr	w0, [x21, #:lo12:.LANCHOR19]
	tbz	x0, 8, .L647
	mov	w5, w6
	mov	w4, w19
	ubfx	x2, x2, 5, 3
	mov	w1, w19
	adrp	x0, .LC51
	add	x0, x0, :lo12:.LC51
	bl	printf
	b	.L647
.L629:
	ldrh	w6, [x1], 2
	cmp	w6, w19
	beq	.L647
	add	w4, w4, 1
	b	.L628
.L631:
	add	x1, x1, 2
	cmp	x1, 16
	bne	.L632
	ubfiz	x20, x23, 7, 16
	add	x20, x20, 136
	add	x20, x0, x20
.L634:
	ldr	w0, [x21, #:lo12:.LANCHOR19]
	tbz	x0, 8, .L635
	adrp	x0, .LANCHOR69
	mov	w4, w3
	mov	w1, w19
	ubfx	x3, x2, 5, 3
	ldrh	w6, [x0, #:lo12:.LANCHOR69]
	mov	w2, w22
	adrp	x0, .LC52
	add	x0, x0, :lo12:.LC52
	bl	printf
.L635:
	mov	x0, x20
	add	x1, x20, 128
	mov	w2, 65535
.L638:
	ldrh	w3, [x0]
	cmp	w3, w2
	bne	.L636
	strh	w19, [x0]
	cbz	w22, .L637
	ldr	x1, [x24, #:lo12:.LANCHOR12]
	ldrh	w0, [x1, 124]
	add	w0, w0, 1
	strh	w0, [x1, 124]
.L657:
	mov	w0, 1
.L622:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
.L633:
	add	x20, x0, 392
	b	.L634
.L637:
	ldr	x0, [x24, #:lo12:.LANCHOR12]
	add	x23, x0, x23, uxth 1
	ldrh	w0, [x23, 120]
	add	w0, w0, 1
	strh	w0, [x23, 120]
	b	.L657
.L636:
	add	x0, x0, 2
	cmp	x1, x0
	bne	.L638
	b	.L657
	.size	gc_add_sblk, .-gc_add_sblk
	.section	.text.gc_mark_bad_ppa,"ax",@progbits
	.align	2
	.global	gc_mark_bad_ppa
	.type	gc_mark_bad_ppa, %function
gc_mark_bad_ppa:
	stp	x29, x30, [sp, -64]!
	adrp	x1, .LANCHOR74
	adrp	x3, .LANCHOR31
	add	x29, sp, 0
	ldrh	w1, [x1, #:lo12:.LANCHOR74]
	ldrb	w3, [x3, #:lo12:.LANCHOR31]
	stp	x19, x20, [sp, 16]
	mov	w19, 24
	sub	w19, w19, w3
	lsr	w2, w0, w1
	sub	w19, w19, w1
	adrp	x1, .LANCHOR75
	str	x23, [sp, 48]
	mov	w23, 1
	ldrb	w1, [x1, #:lo12:.LANCHOR75]
	lsl	w19, w23, w19
	sub	w19, w19, #1
	stp	x21, x22, [sp, 32]
	and	w19, w19, w2
	adrp	x20, .LANCHOR70
	add	x21, x20, :lo12:.LANCHOR70
	mov	w3, w0
	and	w22, w2, 65535
	adrp	x0, .LC53
	udiv	w19, w19, w1
	mov	w2, w22
	ldr	w1, [x21, 2200]
	add	x0, x0, :lo12:.LC53
	and	w19, w19, 65535
	bl	printf
	mov	w1, w23
	mov	w2, 0
	mov	w0, w19
	bl	gc_add_sblk
	ldr	w0, [x21, 2200]
	mov	w1, 0
.L659:
	cmp	w1, w0
	bcc	.L661
	cmp	w0, 5
	bhi	.L660
	add	x20, x20, :lo12:.LANCHOR70
	add	w1, w0, 1
	str	w1, [x20, 2200]
	add	x20, x20, x0, uxtw 1
	strh	w22, [x20, 2204]
.L660:
	mov	w0, 0
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
.L661:
	add	x2, x21, x1, sxtw 1
	ldrh	w2, [x2, 2204]
	cmp	w2, w22
	beq	.L660
	add	w1, w1, 1
	and	w1, w1, 65535
	b	.L659
	.size	gc_mark_bad_ppa, .-gc_mark_bad_ppa
	.section	.text.gc_get_src_ppa_from_index,"ax",@progbits
	.align	2
	.global	gc_get_src_ppa_from_index
	.type	gc_get_src_ppa_from_index, %function
gc_get_src_ppa_from_index:
	adrp	x1, .LANCHOR76
	ubfiz	x0, x0, 2, 16
	ldr	x1, [x1, #:lo12:.LANCHOR76]
	ldr	w0, [x1, x0]
	ret
	.size	gc_get_src_ppa_from_index, .-gc_get_src_ppa_from_index
	.section	.text.gc_write_completed,"ax",@progbits
	.align	2
	.global	gc_write_completed
	.type	gc_write_completed, %function
gc_write_completed:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x21, x22, [sp, 32]
	adrp	x22, .LANCHOR63
	stp	x23, x24, [sp, 48]
	add	x22, x22, :lo12:.LANCHOR63
	stp	x25, x26, [sp, 64]
	adrp	x23, .LANCHOR55
	add	x25, x23, :lo12:.LANCHOR55
	stp	x19, x20, [sp, 16]
	str	x27, [sp, 80]
.L665:
	ldrb	w0, [x22]
	cmp	w0, 255
	bne	.L678
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldr	x27, [sp, 80]
	ldp	x29, x30, [sp], 96
	ret
.L678:
	sxtw	x20, w0
	add	x1, x23, :lo12:.LANCHOR55
	lsl	x3, x20, 6
	add	x2, x1, x3
	ldrb	w0, [x1, x3]
	ldr	w1, [x2, 52]
	strb	w0, [x22]
	ldrh	w24, [x2, 48]
	cbz	w1, .L666
	ldr	w2, [x2, 40]
	adrp	x0, .LANCHOR70
	add	x0, x0, :lo12:.LANCHOR70
	mov	w3, 1
	str	w2, [x0, 2196]
	strh	w3, [x0, 2194]
	adrp	x0, .LC54
	add	x0, x0, :lo12:.LC54
	bl	printf
	adrp	x1, .LANCHOR77
	adrp	x0, .LC0
	mov	w2, 956
	add	x1, x1, :lo12:.LANCHOR77
	add	x0, x0, :lo12:.LC0
	bl	printf
.L666:
	adrp	x0, .LANCHOR78
	mov	x26, x0
	ldrb	w1, [x0, #:lo12:.LANCHOR78]
	cmp	w1, 3
	bne	.L667
	adrp	x0, .LANCHOR35
	ldrb	w0, [x0, #:lo12:.LANCHOR35]
	cbnz	w0, .L667
	adrp	x0, .LANCHOR12
	adrp	x1, .LANCHOR79
	ldr	x0, [x0, #:lo12:.LANCHOR12]
	ldrb	w1, [x1, #:lo12:.LANCHOR79]
	ldrb	w0, [x0, 89]
	mov	w19, w0
	cmp	w1, w0
	bhi	.L679
	cmp	w0, 2
	mov	w0, 2
	csel	w19, w19, w0, ls
.L668:
	add	w19, w19, w19, lsl 1
.L669:
	adrp	x1, .LANCHOR82
	and	x21, x24, 65535
	add	x0, x25, x20, lsl 6
	mov	x27, x1
	ldr	x2, [x1, #:lo12:.LANCHOR82]
	ldrb	w0, [x0, 1]
	ldrb	w2, [x2, x21]
	cmp	w2, w0
	beq	.L670
	adrp	x1, .LANCHOR77
	adrp	x0, .LC0
	mov	w2, 976
	add	x1, x1, :lo12:.LANCHOR77
	add	x0, x0, :lo12:.LC0
	bl	printf
.L670:
	add	x0, x25, x20, lsl 6
	ldrb	w0, [x0, 61]
	cmp	w0, 3
	beq	.L671
	ldrb	w0, [x26, #:lo12:.LANCHOR78]
	cmp	w0, 3
	bne	.L671
	adrp	x0, .LANCHOR83
	ldrb	w0, [x0, #:lo12:.LANCHOR83]
	cbnz	w0, .L671
	adrp	x0, .LANCHOR35
	ldrb	w0, [x0, #:lo12:.LANCHOR35]
	cbnz	w0, .L671
	adrp	x0, .LANCHOR36
	ldrb	w0, [x0, #:lo12:.LANCHOR36]
	cbnz	w0, .L671
	adrp	x0, .LANCHOR80
	ldrb	w0, [x0, #:lo12:.LANCHOR80]
	cbz	w0, .L672
	adrp	x0, .LANCHOR81
	ldrb	w0, [x0, #:lo12:.LANCHOR81]
	cbnz	w0, .L671
.L672:
	ldr	x1, [x27, #:lo12:.LANCHOR82]
	mov	x0, 0
	add	x21, x1, x21
.L673:
	cmp	w19, w0, uxth
	bls	.L665
	ldrb	w1, [x21, x0]
	add	x0, x0, 1
	add	x1, x25, x1, lsl 6
	strb	wzr, [x1, 61]
	b	.L673
.L679:
	mov	w19, 1
	b	.L668
.L667:
	adrp	x0, .LANCHOR80
	ldrb	w0, [x0, #:lo12:.LANCHOR80]
	cbz	w0, .L680
	adrp	x0, .LANCHOR81
	ldrb	w0, [x0, #:lo12:.LANCHOR81]
	cmp	w0, 0
	cset	w19, ne
	add	w19, w19, 1
	b	.L669
.L680:
	mov	w19, 1
	b	.L669
.L671:
	adrp	x20, .LANCHOR70
	add	x20, x20, :lo12:.LANCHOR70
	add	x19, x21, x19, uxth
	strh	w24, [x20, 2108]
	mov	w24, -1
.L674:
	cmp	x21, x19
	beq	.L665
	ldr	x1, [x27, #:lo12:.LANCHOR82]
	ldrb	w0, [x1, x21]
	strb	w24, [x1, x21]
	add	x21, x21, 1
	sbfiz	x1, x0, 6, 32
	ubfiz	x0, x0, 6, 8
	add	x1, x25, x1
	add	x0, x25, x0
	strb	wzr, [x1, 61]
	bl	zbuf_free
	ldrb	w0, [x20, 7]
	sub	w0, w0, #1
	strb	w0, [x20, 7]
	b	.L674
	.size	gc_write_completed, .-gc_write_completed
	.section	.text.gc_get_src_blk,"ax",@progbits
	.align	2
	.global	gc_get_src_blk
	.type	gc_get_src_blk, %function
gc_get_src_blk:
	adrp	x0, .LANCHOR12
	ldr	x2, [x0, #:lo12:.LANCHOR12]
	adrp	x0, .LANCHOR84
	ldrb	w3, [x0, #:lo12:.LANCHOR84]
	ldrh	w0, [x2, 124]
	cbz	w0, .L693
	add	x1, x2, 392
	mov	w4, 1
.L694:
	add	x5, x1, 128
	mov	w6, 65535
.L698:
	ldrh	w0, [x1]
	cmp	w0, w6
	beq	.L696
	mov	w5, -1
	strh	w5, [x1]
	cbz	w4, .L697
	ldrh	w1, [x2, 124]
	sub	w1, w1, #1
	strh	w1, [x2, 124]
	ret
.L693:
	add	x0, x2, x3, sxtw 1
	ldrh	w0, [x0, 120]
	cbz	w0, .L699
	ubfiz	x1, x3, 7, 8
	mov	w4, 0
	add	x1, x1, 136
	add	x1, x2, x1
	b	.L694
.L697:
	add	x2, x2, x3, uxtb 1
	ldrh	w1, [x2, 120]
	sub	w1, w1, #1
	strh	w1, [x2, 120]
	ret
.L696:
	add	x1, x1, 2
	cmp	x1, x5
	bne	.L698
	ret
.L699:
	mov	w0, 65535
	ret
	.size	gc_get_src_blk, .-gc_get_src_blk
	.section	.text.gc_free_temp_buf,"ax",@progbits
	.align	2
	.global	gc_free_temp_buf
	.type	gc_free_temp_buf, %function
gc_free_temp_buf:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	adrp	x20, .LANCHOR70
	add	x0, x20, :lo12:.LANCHOR70
	stp	x21, x22, [sp, 32]
	ldrb	w1, [x0, 7]
	cbz	w1, .L708
	adrp	x1, .LANCHOR57
	ldrb	w1, [x1, #:lo12:.LANCHOR57]
	cmp	w1, 1
	bhi	.L708
	ldrh	w19, [x0, 2108]
	adrp	x2, .LANCHOR79
	adrp	x0, .LANCHOR85
	adrp	x21, .LANCHOR82
	ldrb	w2, [x2, #:lo12:.LANCHOR79]
	add	w1, w19, 24
	ldrh	w0, [x0, #:lo12:.LANCHOR85]
	ldr	x4, [x21, #:lo12:.LANCHOR82]
	mul	w0, w0, w2
	cmp	w0, w1
	csel	w1, w0, w1, ls
	adrp	x0, .LANCHOR55
	add	x0, x0, :lo12:.LANCHOR55
.L703:
	cmp	w19, w1
	bcc	.L706
.L708:
	mov	w0, 0
	b	.L701
.L706:
	uxtw	x22, w19
	ldrb	w2, [x4, x22]
	cmp	w2, 255
	beq	.L704
	sbfiz	x3, x2, 6, 32
	add	x3, x0, x3
	ldrb	w3, [x3, 61]
	cbnz	w3, .L704
	ubfiz	x2, x2, 6, 8
	add	x0, x0, x2
	bl	zbuf_free
	adrp	x0, .LANCHOR19
	ldr	w0, [x0, #:lo12:.LANCHOR19]
	tbz	x0, 8, .L705
	ldr	x0, [x21, #:lo12:.LANCHOR82]
	mov	w1, w19
	ldrb	w2, [x0, x22]
	adrp	x0, .LC55
	add	x0, x0, :lo12:.LC55
	bl	printf
.L705:
	ldr	x0, [x21, #:lo12:.LANCHOR82]
	add	x20, x20, :lo12:.LANCHOR70
	mov	w1, -1
	strb	w1, [x0, x22]
	ldrb	w0, [x20, 7]
	sub	w0, w0, #1
	strb	w0, [x20, 7]
	mov	w0, 1
.L701:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
.L704:
	add	w19, w19, 1
	b	.L703
	.size	gc_free_temp_buf, .-gc_free_temp_buf
	.section	.text.get_ink_scaned_blk,"ax",@progbits
	.align	2
	.global	get_ink_scaned_blk
	.type	get_ink_scaned_blk, %function
get_ink_scaned_blk:
	adrp	x1, .LANCHOR70
	add	x1, x1, :lo12:.LANCHOR70
	ldrh	w2, [x1, 2112]
	cbz	w2, .L718
	sub	w2, w2, #1
	strh	w2, [x1, 2112]
	add	x0, x1, x2, sxtw 1
	ldrh	w0, [x0, 2114]
	ret
.L718:
	mov	w0, 65535
	ret
	.size	get_ink_scaned_blk, .-get_ink_scaned_blk
	.section	.text.print_gc_debug_info,"ax",@progbits
	.align	2
	.global	print_gc_debug_info
	.type	print_gc_debug_info, %function
print_gc_debug_info:
	adrp	x2, .LANCHOR86
	adrp	x1, .LANCHOR70
	add	x0, x1, :lo12:.LANCHOR70
	ldrh	w6, [x2, #:lo12:.LANCHOR86]
	adrp	x2, .LANCHOR57
	ldrh	w1, [x1, #:lo12:.LANCHOR70]
	ldrb	w5, [x0, 7]
	ldrb	w4, [x2, #:lo12:.LANCHOR57]
	ldrh	w3, [x0, 2106]
	ldrh	w2, [x0, 2]
	adrp	x0, .LC56
	add	x0, x0, :lo12:.LC56
	b	printf
	.size	print_gc_debug_info, .-print_gc_debug_info
	.section	.text._list_pop_index_node,"ax",@progbits
	.align	2
	.global	_list_pop_index_node
	.type	_list_pop_index_node, %function
_list_pop_index_node:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	ldr	x20, [x0]
	cbz	x20, .L726
	adrp	x3, .LANCHOR4
	and	w1, w1, 65535
	mov	w4, 65535
	mov	w5, 6
	ldr	x19, [x3, #:lo12:.LANCHOR4]
.L722:
	cbnz	w1, .L723
.L725:
	sub	x19, x20, x19
	mov	x1, -6148914691236517206
	asr	x19, x19, 1
	movk	x1, 0xaaab, lsl 0
	mul	x19, x19, x1
	and	w19, w19, 65535
	mov	w1, w19
	bl	_list_remove_node
	mov	w0, -1
	strh	w0, [x20]
	strh	w0, [x20, 2]
	mov	w0, w19
.L720:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L723:
	ldrh	w3, [x20]
	cmp	w3, w4
	beq	.L725
	sub	w1, w1, #1
	umaddl	x20, w3, w5, x19
	and	w1, w1, 65535
	b	.L722
.L726:
	mov	w0, 65535
	b	.L720
	.size	_list_pop_index_node, .-_list_pop_index_node
	.section	.text._list_get_gc_head_node,"ax",@progbits
	.align	2
	.global	_list_get_gc_head_node
	.type	_list_get_gc_head_node, %function
_list_get_gc_head_node:
	ldr	x0, [x0]
	and	w1, w1, 65535
	cbz	x0, .L733
	adrp	x2, .LANCHOR4
	mov	w3, 65535
	mov	w4, 6
	ldr	x2, [x2, #:lo12:.LANCHOR4]
.L730:
	cbz	w1, .L731
	ldrh	w0, [x0]
	cmp	w0, w3
	bne	.L732
	ret
.L732:
	sub	w1, w1, #1
	umaddl	x0, w0, w4, x2
	and	w1, w1, 65535
	b	.L730
.L733:
	mov	w0, 65535
	ret
.L731:
	sub	x0, x0, x2
	mov	x1, -6148914691236517206
	asr	x0, x0, 1
	movk	x1, 0xaaab, lsl 0
	mul	x0, x0, x1
	and	w0, w0, 65535
	ret
	.size	_list_get_gc_head_node, .-_list_get_gc_head_node
	.section	.text.gc_search_src_blk,"ax",@progbits
	.align	2
	.global	gc_search_src_blk
	.type	gc_search_src_blk, %function
gc_search_src_blk:
	stp	x29, x30, [sp, -176]!
	add	x29, sp, 0
	stp	x21, x22, [sp, 32]
	and	w22, w0, 255
	and	w0, w1, 255
	stp	x19, x20, [sp, 16]
	str	w0, [x29, 160]
	adrp	x0, .LANCHOR12
	and	w19, w2, 255
	stp	x23, x24, [sp, 48]
	ldr	x2, [x0, #:lo12:.LANCHOR12]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	add	x0, x2, x22, sxtw 1
	ldrh	w21, [x0, 120]
	cbz	w21, .L736
	mov	w0, w21
.L735:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 176
	ret
.L736:
	adrp	x0, .LANCHOR70
	add	x1, x0, :lo12:.LANCHOR70
	ldrh	w1, [x1, 56]
	cmp	w1, 1
	bhi	.L738
	adrp	x3, .LANCHOR87
	strh	wzr, [x3, #:lo12:.LANCHOR87]
	adrp	x3, .LANCHOR88
	strh	wzr, [x3, #:lo12:.LANCHOR88]
	adrp	x3, .LANCHOR89
	strh	wzr, [x3, #:lo12:.LANCHOR89]
.L738:
	cbnz	w22, .L739
	adrp	x26, .LANCHOR88
	adrp	x25, .LANCHOR90
	add	x23, x26, :lo12:.LANCHOR88
	add	x25, x25, :lo12:.LANCHOR90
	mov	w24, 0
	mov	w20, 0
	mov	w27, 65535
.L740:
	cmp	w19, w20
	blt	.L745
	ldrh	w6, [x23]
	mov	x0, x25
	mov	w1, w6
	bl	_list_get_gc_head_node
	add	w2, w6, 1
	and	w2, w2, 65535
	strh	w2, [x23]
	and	w1, w0, 65535
	mov	w28, w1
	cmp	w1, w27
	beq	.L741
	adrp	x0, .LANCHOR19
	adrp	x6, .LANCHOR11
	uxtw	x4, w1
	ldr	w0, [x0, #:lo12:.LANCHOR19]
	tbz	x0, 8, .L742
	ldr	x0, [x6, #:lo12:.LANCHOR11]
	stp	x6, x4, [x29, 144]
	ldrh	w3, [x0, x4, lsl 1]
	adrp	x0, .LC57
	add	x0, x0, :lo12:.LC57
	bl	printf
	ldp	x6, x4, [x29, 144]
.L742:
	ldr	x0, [x6, #:lo12:.LANCHOR11]
	ldrh	w1, [x0, x4, lsl 1]
	adrp	x0, .LANCHOR69
	ldrh	w0, [x0, #:lo12:.LANCHOR69]
	cmp	w1, w0
	bcs	.L743
	mov	w2, 0
	mov	w1, 0
	mov	w0, w28
	bl	gc_add_sblk
	cbz	w0, .L744
	add	w5, w24, 1
	and	w24, w5, 65535
	cmp	w24, w19
	bcc	.L744
.L745:
	ldr	x0, [x29, 160]
	tbz	x0, 1, .L747
	adrp	x0, .LANCHOR91
	ldrh	w0, [x0, #:lo12:.LANCHOR91]
	cmp	w0, 32
	bls	.L747
	adrp	x23, .LANCHOR93
	adrp	x20, .LANCHOR89
	adrp	x26, .LANCHOR92
	add	x20, x20, :lo12:.LANCHOR89
	add	x26, x26, :lo12:.LANCHOR92
	add	x27, x23, :lo12:.LANCHOR93
	mov	w25, 0
.L748:
	cmp	w19, w25
	blt	.L752
	ldrh	w6, [x20]
	mov	x0, x26
	mov	w1, w6
	bl	_list_get_gc_head_node
	add	w6, w6, 1
	strh	w6, [x20]
	and	w1, w0, 65535
	mov	w2, 65535
	cmp	w1, w2
	beq	.L749
	adrp	x2, .LANCHOR11
	ubfiz	x1, x1, 1, 16
	ldr	x2, [x2, #:lo12:.LANCHOR11]
	ldrh	w2, [x2, x1]
	ldrh	w1, [x27]
	cmp	w2, w1
	bcs	.L749
	mov	w2, 0
	mov	w1, 0
	bl	gc_add_sblk
	cbz	w0, .L751
	add	w5, w24, 1
	and	w24, w5, 65535
	cmp	w24, w19
	bcc	.L751
.L752:
	cmp	w24, w19
	adrp	x0, .LANCHOR94
	bcs	.L754
	ldrh	w1, [x0, #:lo12:.LANCHOR94]
	adrp	x3, .LANCHOR79
	adrp	x0, .LANCHOR85
	ldrh	w2, [x23, #:lo12:.LANCHOR93]
	ldrb	w3, [x3, #:lo12:.LANCHOR79]
	ldrh	w0, [x0, #:lo12:.LANCHOR85]
	mul	w0, w0, w3
	sub	w0, w0, w1, lsr 2
	cmp	w2, w0
	bge	.L747
	add	w1, w2, w1, lsr 3
	strh	w1, [x23, #:lo12:.LANCHOR93]
.L747:
	ldr	x0, [x29, 160]
	tbz	x0, 0, .L755
	and	w23, w19, 65535
	cmp	w24, w23
	bcs	.L755
	adrp	x20, .LANCHOR87
	adrp	x25, .LANCHOR95
	add	x20, x20, :lo12:.LANCHOR87
	add	x25, x25, :lo12:.LANCHOR95
	mov	w26, 65535
.L760:
	ldrh	w6, [x20]
	mov	x0, x25
	mov	w1, w6
	bl	_list_get_gc_head_node
	add	w6, w6, 1
	strh	w6, [x20]
	cmp	w26, w0, uxth
	beq	.L756
	mov	w2, 0
	mov	w1, 0
	bl	gc_add_sblk
	cbz	w0, .L757
	add	w5, w24, 1
	and	w24, w5, 65535
	cmp	w23, w24
	bhi	.L757
.L758:
	adrp	x0, .LANCHOR94
	adrp	x1, .LANCHOR69
	ldrh	w0, [x0, #:lo12:.LANCHOR94]
	ldrh	w2, [x1, #:lo12:.LANCHOR69]
	cmp	w2, w0, lsr 1
	bls	.L755
	sub	w0, w2, w0, lsr 3
	b	.L846
.L743:
	strh	wzr, [x26, #:lo12:.LANCHOR88]
	b	.L745
.L741:
	strh	wzr, [x23]
	b	.L745
.L744:
	add	w20, w20, 1
	and	w20, w20, 65535
	b	.L740
.L749:
	strh	wzr, [x20]
	b	.L752
.L751:
	add	w25, w25, 1
	and	w25, w25, 65535
	b	.L748
.L754:
	ldrh	w1, [x23, #:lo12:.LANCHOR93]
	ldrh	w0, [x0, #:lo12:.LANCHOR94]
	cmp	w1, w0
	bls	.L747
	sub	w0, w1, w0, lsr 3
	strh	w0, [x23, #:lo12:.LANCHOR93]
	b	.L747
.L756:
	strh	wzr, [x20]
.L759:
	cmp	w24, w23
	bcs	.L758
	adrp	x1, .LANCHOR69
	adrp	x0, .LANCHOR94
	ldrh	w2, [x1, #:lo12:.LANCHOR69]
	ldrh	w0, [x0, #:lo12:.LANCHOR94]
	cmp	w2, w0
	bcs	.L755
	add	w0, w2, w0, lsr 3
.L846:
	strh	w0, [x1, #:lo12:.LANCHOR69]
.L755:
	adrp	x0, .LANCHOR19
	ldr	w0, [x0, #:lo12:.LANCHOR19]
	tbz	x0, 8, .L791
	ldr	w2, [x29, 160]
	adrp	x0, .LC58
	mov	w4, w19
	mov	w3, w24
	mov	w1, w22
	add	x0, x0, :lo12:.LC58
	bl	printf
.L791:
	mov	w0, w24
	b	.L735
.L757:
	add	w21, w21, 1
	and	w21, w21, 65535
	cmp	w23, w21
	bhi	.L760
	b	.L759
.L739:
	adrp	x23, .LANCHOR79
	adrp	x25, .LANCHOR85
	stp	x25, x23, [x29, 144]
	cmp	w19, 1
	ldrb	w20, [x23, #:lo12:.LANCHOR79]
	ldrh	w3, [x25, #:lo12:.LANCHOR85]
	mul	w20, w20, w3
	and	w20, w20, 65535
	bne	.L761
	cbz	w1, .L761
	ldrh	w3, [x2, 80]
	mov	w2, 65535
	cmp	w3, w2
	beq	.L794
	add	x2, x0, :lo12:.LANCHOR70
	ldrh	w2, [x2, 2106]
	sub	w20, w20, w2
	and	w20, w20, 65535
.L794:
	mov	w19, 8
.L761:
	add	x0, x0, :lo12:.LANCHOR70
	strh	wzr, [x0, 2192]
	adrp	x0, .LANCHOR96
	strh	wzr, [x0, #:lo12:.LANCHOR96]
	ldr	w0, [x29, 160]
	and	w0, w0, 1
	str	w0, [x29, 128]
	ldr	x0, [x29, 160]
	tbz	x0, 0, .L795
	adrp	x2, .LANCHOR98
	adrp	x26, .LANCHOR97
	str	x2, [x29, 120]
	ldrh	w0, [x26, #:lo12:.LANCHOR97]
	ldrh	w3, [x2, #:lo12:.LANCHOR98]
	cmp	w0, w3, lsr 2
	bhi	.L763
	adrp	x2, .LANCHOR99
	ldrh	w2, [x2, #:lo12:.LANCHOR99]
	cmp	w2, w0
	bcs	.L796
.L763:
	cmp	w1, 1
	adrp	x25, .LANCHOR87
	adrp	x28, .LANCHOR95
	bls	.L765
.L767:
	mov	w24, 0
.L766:
	add	x0, x28, :lo12:.LANCHOR95
	add	x25, x25, :lo12:.LANCHOR87
	adrp	x28, .LANCHOR99
	add	x28, x28, :lo12:.LANCHOR99
	mov	w23, 0
	mov	w27, 64
	str	x0, [x29, 136]
.L770:
	ldrh	w7, [x25]
	ldr	x0, [x29, 136]
	mov	w1, w7
	bl	_list_get_gc_head_node
	and	w6, w0, 65535
	str	w6, [x29, 112]
	mov	w1, 65535
	cmp	w6, w1
	beq	.L768
	add	w7, w7, 1
	mov	w2, w22
	strh	w7, [x25]
	mov	w1, 0
	bl	gc_add_sblk
	cbz	w0, .L769
	adrp	x0, .LANCHOR11
	ldr	w6, [x29, 112]
	add	w5, w24, 1
	ldr	x0, [x0, #:lo12:.LANCHOR11]
	and	w24, w5, 65535
	ubfiz	x6, x6, 1, 16
	cmp	w24, w19
	ldrh	w0, [x0, x6]
	add	w3, w23, w0
	and	w23, w3, 65535
	bcs	.L764
	cmp	w20, w23
	bcc	.L764
	ldrh	w0, [x28]
	ldrh	w1, [x26, #:lo12:.LANCHOR97]
	cmp	w0, w1, lsl 1
	ble	.L769
.L764:
	adrp	x0, .LANCHOR99
	ldrh	w1, [x0, #:lo12:.LANCHOR99]
	ldr	x0, [x29, 120]
	ldrh	w0, [x0, #:lo12:.LANCHOR98]
	cmp	w1, w0, lsr 2
	bhi	.L792
	ldrh	w0, [x26, #:lo12:.LANCHOR97]
	add	w0, w0, 8
	cmp	w1, w0
	ble	.L762
.L792:
	cmp	w20, w23
	bls	.L762
	adrp	x7, .LANCHOR88
	and	w25, w19, 65535
	add	x28, x7, :lo12:.LANCHOR88
	adrp	x0, .LANCHOR90
	mov	w26, 64
	add	x0, x0, :lo12:.LANCHOR90
	adrp	x27, .LANCHOR11
	str	x0, [x29, 136]
.L773:
	ldrh	w6, [x28]
	ldr	x0, [x29, 136]
	mov	w1, w6
	bl	_list_get_gc_head_node
	and	w4, w0, 65535
	str	w4, [x29, 120]
	mov	w1, 65535
	cmp	w4, w1
	beq	.L771
	add	w6, w6, 1
	mov	w2, w22
	strh	w6, [x28]
	mov	w1, 0
	bl	gc_add_sblk
	cbz	w0, .L772
	ldr	w4, [x29, 120]
	add	w5, w24, 1
	ldr	x0, [x27, #:lo12:.LANCHOR11]
	and	w24, w5, 65535
	cmp	w24, w25
	ubfiz	x4, x4, 1, 16
	ldrh	w0, [x0, x4]
	add	w3, w23, w0
	and	w23, w3, 65535
	bcs	.L762
	cmp	w20, w23
	bcs	.L772
.L762:
	ldr	x0, [x29, 160]
	tbz	x0, 1, .L774
	adrp	x0, .LANCHOR91
	str	x0, [x29, 112]
	ldrh	w1, [x0, #:lo12:.LANCHOR91]
	cmp	w1, 32
	bls	.L774
	cmp	w23, w20
	bcs	.L774
	adrp	x25, .LANCHOR89
	adrp	x0, .LANCHOR92
	add	x28, x25, :lo12:.LANCHOR89
	add	x0, x0, :lo12:.LANCHOR92
	adrp	x27, .LANCHOR100
	str	x0, [x29, 120]
	mov	w26, 64
	add	x0, x27, :lo12:.LANCHOR100
	str	x0, [x29, 136]
.L780:
	ldrh	w6, [x28]
	ldr	x0, [x29, 120]
	mov	w1, w6
	bl	_list_get_gc_head_node
	and	w8, w0, 65535
	mov	w1, 65535
	cmp	w8, w1
	beq	.L775
	add	w6, w6, 1
	strh	w6, [x28]
	cmp	w19, 1
	bne	.L776
	ldp	x2, x1, [x29, 144]
	ldrb	w1, [x1, #:lo12:.LANCHOR79]
	ldrh	w2, [x2, #:lo12:.LANCHOR85]
	mul	w2, w1, w2
	adrp	x1, .LANCHOR94
	ldrh	w1, [x1, #:lo12:.LANCHOR94]
	sub	w1, w2, w1, lsr 3
	ldr	x2, [x29, 136]
	strh	w1, [x2]
.L776:
	ubfiz	x6, x8, 1, 16
	adrp	x8, .LANCHOR11
	stp	x8, x6, [x29, 96]
	ldr	x1, [x8, #:lo12:.LANCHOR11]
	ldrh	w2, [x1, x6]
	ldr	x1, [x29, 136]
	ldrh	w1, [x1]
	cmp	w2, w1
	bcs	.L777
	mov	w2, w22
	mov	w1, 0
	bl	gc_add_sblk
	cbz	w0, .L778
	ldp	x8, x6, [x29, 96]
	add	w5, w24, 1
	add	w21, w21, 1
	and	w24, w5, 65535
	and	w21, w21, 65535
	cmp	w24, w19
	ldr	x0, [x8, #:lo12:.LANCHOR11]
	ldrh	w0, [x0, x6]
	add	w3, w23, w0
	and	w23, w3, 65535
	bcs	.L779
	cmp	w20, w23
	bcs	.L778
.L779:
	cmp	w24, w19
	adrp	x0, .LANCHOR94
	bcc	.L781
	cbnz	w21, .L782
	ldr	x1, [x29, 112]
	ldrh	w2, [x1, #:lo12:.LANCHOR91]
	adrp	x1, .LANCHOR101
	ldrh	w1, [x1, #:lo12:.LANCHOR101]
	cmp	w2, w1
	bls	.L782
.L781:
	ldrh	w2, [x0, #:lo12:.LANCHOR94]
	ldp	x0, x3, [x29, 144]
	ldrh	w1, [x27, #:lo12:.LANCHOR100]
	lsr	w2, w2, 3
	ldrh	w0, [x0, #:lo12:.LANCHOR85]
	ldrb	w6, [x3, #:lo12:.LANCHOR79]
	mul	w0, w0, w6
	sub	w0, w0, w2
	cmp	w1, w0
	bge	.L774
	add	w1, w1, w2
	strh	w1, [x27, #:lo12:.LANCHOR100]
.L774:
	ldr	w0, [x29, 128]
	cbz	w0, .L755
	and	w27, w19, 65535
	cmp	w24, w27
	bcs	.L755
	cmp	w23, w20
	bcs	.L755
	adrp	x26, .LANCHOR90
	adrp	x4, .LANCHOR88
	add	x0, x26, :lo12:.LANCHOR90
	add	x28, x4, :lo12:.LANCHOR88
	adrp	x21, .LANCHOR102
	str	x0, [x29, 144]
	mov	w25, 64
	add	x0, x21, :lo12:.LANCHOR102
	adrp	x26, .LANCHOR11
	str	x0, [x29, 136]
.L790:
	ldrh	w6, [x28]
	ldr	x0, [x29, 144]
	mov	w1, w6
	bl	_list_get_gc_head_node
	and	w1, w0, 65535
	mov	w2, 65535
	cmp	w1, w2
	beq	.L784
	add	w6, w6, 1
	strh	w6, [x28]
	ubfiz	x6, x1, 1, 16
	ldr	x1, [x26, #:lo12:.LANCHOR11]
	ldrh	w2, [x1, x6]
	ldr	x1, [x29, 136]
	ldrh	w1, [x1]
	cmp	w2, w1
	bcs	.L785
	adrp	x1, .LANCHOR98
	ldrh	w2, [x1, #:lo12:.LANCHOR98]
	adrp	x1, .LANCHOR99
	ldrh	w1, [x1, #:lo12:.LANCHOR99]
	cmp	w1, w2, lsr 1
	bls	.L786
.L785:
	mov	w2, w22
	mov	w1, 0
	str	x6, [x29, 128]
	bl	gc_add_sblk
	cbz	w0, .L787
	adrp	x0, .LANCHOR11
	ldr	x6, [x29, 128]
	add	w5, w24, 1
	ldr	x0, [x0, #:lo12:.LANCHOR11]
	and	w24, w5, 65535
	cmp	w27, w24
	ldrh	w0, [x0, x6]
	add	w3, w23, w0
	and	w23, w3, 65535
	bls	.L788
	cmp	w20, w23
	bcs	.L787
.L789:
	adrp	x0, .LANCHOR94
	ldrh	w1, [x21, #:lo12:.LANCHOR102]
	ldrh	w0, [x0, #:lo12:.LANCHOR94]
	cmp	w1, w0, lsr 1
	bls	.L755
	sub	w0, w1, w0, lsr 3
	strh	w0, [x21, #:lo12:.LANCHOR102]
	b	.L755
.L765:
	lsr	w0, w0, 2
	mov	w1, 0
	strh	w0, [x25, #:lo12:.LANCHOR87]
	add	x0, x28, :lo12:.LANCHOR95
	bl	_list_get_gc_head_node
	and	w1, w0, 65535
	mov	w2, 65535
	cmp	w1, w2
	beq	.L767
	adrp	x2, .LANCHOR11
	ubfiz	x1, x1, 1, 16
	ldr	x3, [x2, #:lo12:.LANCHOR11]
	adrp	x2, .LANCHOR94
	ldrh	w2, [x2, #:lo12:.LANCHOR94]
	ldrh	w1, [x3, x1]
	cmp	w1, w2, lsr 2
	bcs	.L767
	mov	w1, 1
	mov	w2, w22
	strh	w1, [x25, #:lo12:.LANCHOR87]
	mov	w1, 0
	bl	gc_add_sblk
	cmp	w0, 0
	cset	w24, ne
	b	.L766
.L768:
	strh	wzr, [x25]
	b	.L764
.L769:
	sub	w27, w27, #1
	ands	w27, w27, 65535
	bne	.L770
	b	.L764
.L771:
	cmp	w6, 64
	bls	.L762
	strh	wzr, [x28]
	b	.L762
.L772:
	sub	w26, w26, #1
	ands	w26, w26, 65535
	bne	.L773
	b	.L762
.L795:
	mov	w23, 0
	mov	w24, 0
	b	.L762
.L777:
	strh	wzr, [x25, #:lo12:.LANCHOR89]
	b	.L779
.L775:
	strh	wzr, [x28]
	b	.L779
.L778:
	sub	w26, w26, #1
	ands	w26, w26, 65535
	bne	.L780
	b	.L779
.L782:
	ldr	x1, [x29, 152]
	ldrh	w0, [x0, #:lo12:.LANCHOR94]
	ldrh	w2, [x27, #:lo12:.LANCHOR100]
	ldrb	w1, [x1, #:lo12:.LANCHOR79]
	mul	w1, w1, w0
	cmp	w2, w1
	ble	.L755
	sub	w0, w2, w0, lsr 3
	strh	w0, [x27, #:lo12:.LANCHOR100]
	b	.L755
.L784:
	cmp	w6, 64
	bls	.L786
	strh	wzr, [x28]
.L786:
	cmp	w24, w27
	bcc	.L789
.L788:
	adrp	x0, .LANCHOR94
	ldrh	w2, [x21, #:lo12:.LANCHOR102]
	ldrh	w1, [x0, #:lo12:.LANCHOR94]
	ldr	x0, [x29, 152]
	ldrb	w0, [x0, #:lo12:.LANCHOR79]
	mul	w0, w0, w1
	sub	w0, w0, #32
	cmp	w2, w0
	bge	.L755
	add	w1, w2, w1, lsr 3
	strh	w1, [x21, #:lo12:.LANCHOR102]
	b	.L755
.L787:
	sub	w25, w25, #1
	ands	w25, w25, 65535
	bne	.L790
	b	.L786
.L796:
	mov	w23, 0
	mov	w24, 0
	b	.L764
	.size	gc_search_src_blk, .-gc_search_src_blk
	.section	.text.zftl_get_gc_node,"ax",@progbits
	.align	2
	.global	zftl_get_gc_node
	.type	zftl_get_gc_node, %function
zftl_get_gc_node:
	and	w1, w1, 65535
	and	w0, w0, 65535
	cmp	w1, 5
	bne	.L848
	mov	w1, w0
	adrp	x0, .LANCHOR92
	add	x0, x0, :lo12:.LANCHOR92
.L850:
	b	_list_get_gc_head_node
.L848:
	cmp	w1, 2
	mov	w1, w0
	bne	.L849
	adrp	x0, .LANCHOR95
	add	x0, x0, :lo12:.LANCHOR95
	b	.L850
.L849:
	adrp	x0, .LANCHOR90
	add	x0, x0, :lo12:.LANCHOR90
	b	.L850
	.size	zftl_get_gc_node, .-zftl_get_gc_node
	.section	.text.zftl_insert_free_list,"ax",@progbits
	.align	2
	.global	zftl_insert_free_list
	.type	zftl_insert_free_list, %function
zftl_insert_free_list:
	and	w1, w0, 65535
	adrp	x0, .LANCHOR9
	ldr	x0, [x0, #:lo12:.LANCHOR9]
	add	x0, x0, x1, uxth 2
	ldrb	w0, [x0, 2]
	ands	w0, w0, 24
	bne	.L852
	adrp	x2, .LANCHOR103
	adrp	x0, .LANCHOR104
	add	x2, x2, :lo12:.LANCHOR103
	add	x0, x0, :lo12:.LANCHOR104
.L854:
	b	_insert_free_list
.L852:
	cmp	w0, 16
	bne	.L853
	adrp	x2, .LANCHOR105
	adrp	x0, .LANCHOR106
	add	x2, x2, :lo12:.LANCHOR105
	add	x0, x0, :lo12:.LANCHOR106
	b	.L854
.L853:
	adrp	x2, .LANCHOR107
	adrp	x0, .LANCHOR108
	add	x2, x2, :lo12:.LANCHOR107
	add	x0, x0, :lo12:.LANCHOR108
	b	.L854
	.size	zftl_insert_free_list, .-zftl_insert_free_list
	.section	.text.zftl_insert_data_list,"ax",@progbits
	.align	2
	.global	zftl_insert_data_list
	.type	zftl_insert_data_list, %function
zftl_insert_data_list:
	and	w1, w0, 65535
	adrp	x0, .LANCHOR9
	ldr	x0, [x0, #:lo12:.LANCHOR9]
	add	x0, x0, x1, uxth 2
	ldrb	w2, [x0, 2]
	and	w2, w2, 224
	cmp	w2, 64
	bne	.L856
	adrp	x2, .LANCHOR97
	adrp	x0, .LANCHOR95
	add	x2, x2, :lo12:.LANCHOR97
	add	x0, x0, :lo12:.LANCHOR95
.L859:
	b	_insert_data_list
.L856:
	cmp	w2, 96
	bne	.L857
	adrp	x2, .LANCHOR99
	adrp	x0, .LANCHOR90
	add	x2, x2, :lo12:.LANCHOR99
	add	x0, x0, :lo12:.LANCHOR90
	b	.L859
.L857:
	cmp	w2, 160
	bne	.L855
	adrp	x2, .LANCHOR91
	adrp	x0, .LANCHOR92
	add	x2, x2, :lo12:.LANCHOR91
	add	x0, x0, :lo12:.LANCHOR92
	b	.L859
.L855:
	ret
	.size	zftl_insert_data_list, .-zftl_insert_data_list
	.section	.text.zftl_gc_get_free_sblk,"ax",@progbits
	.align	2
	.global	zftl_gc_get_free_sblk
	.type	zftl_gc_get_free_sblk, %function
zftl_gc_get_free_sblk:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	adrp	x20, .LANCHOR12
	stp	x21, x22, [sp, 32]
	and	w21, w0, 65535
	ldr	x0, [x20, #:lo12:.LANCHOR12]
	and	w22, w1, 65535
	ldrh	w19, [x0, 588]
	mov	w0, 65535
	cmp	w19, w0
	beq	.L861
	cbnz	w21, .L861
	mov	w1, w19
	adrp	x0, .LC59
	add	x0, x0, :lo12:.LC59
	bl	printf
	ldr	x0, [x20, #:lo12:.LANCHOR12]
	mov	w1, -1
	strh	w1, [x0, 588]
.L862:
	mov	w0, w19
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
.L861:
	adrp	x2, .LANCHOR105
	adrp	x20, .LANCHOR107
	ldrh	w0, [x2, #:lo12:.LANCHOR105]
	ldrh	w1, [x20, #:lo12:.LANCHOR107]
	cmp	w0, w1
	bcc	.L863
	adrp	x3, .LANCHOR103
	ldrh	w3, [x3, #:lo12:.LANCHOR103]
	cmp	w3, w0
	bls	.L864
	cbz	w1, .L864
.L863:
	cbnz	w21, .L865
	lsr	w1, w1, 2
.L866:
	adrp	x0, .LANCHOR108
	add	x2, x20, :lo12:.LANCHOR107
	add	x0, x0, :lo12:.LANCHOR108
.L881:
	bl	_list_pop_index_node
	and	w19, w0, 65535
	mov	w0, 65535
	cmp	w19, w0
	bne	.L869
	adrp	x0, .LANCHOR103
	ldrh	w5, [x20, #:lo12:.LANCHOR107]
	mov	w2, w22
	mov	w1, w19
	ldrh	w4, [x0, #:lo12:.LANCHOR103]
	adrp	x0, .LANCHOR104
	ldr	x3, [x0, #:lo12:.LANCHOR104]
	adrp	x0, .LC60
	add	x0, x0, :lo12:.LC60
	bl	printf
.L869:
	cbz	w21, .L862
	adrp	x0, .LANCHOR19
	ldr	w0, [x0, #:lo12:.LANCHOR19]
	tbz	x0, 8, .L862
	adrp	x4, .LANCHOR11
	adrp	x1, .LANCHOR9
	uxtw	x3, w19
	ldr	x1, [x1, #:lo12:.LANCHOR9]
	lsl	x0, x3, 2
	ldr	x6, [x4, #:lo12:.LANCHOR11]
	add	x2, x1, x0
	ldr	w4, [x1, x0]
	ldrh	w6, [x6, x3, lsl 1]
	ldrb	w2, [x2, 2]
	ldrh	w5, [x1, x0]
	ubfx	x4, x4, 11, 8
	mov	w1, w19
	adrp	x0, .LC61
	ubfx	x3, x2, 3, 2
	and	w5, w5, 2047
	ubfx	x2, x2, 5, 3
	add	x0, x0, :lo12:.LC61
	bl	printf
	b	.L862
.L865:
	mov	w1, 7
	mul	w1, w0, w1
	lsr	w1, w1, 3
	b	.L866
.L864:
	lsr	w1, w0, 3
	cmp	w21, 0
	adrp	x0, .LANCHOR106
	csel	w1, w1, wzr, ne
	add	x2, x2, :lo12:.LANCHOR105
	add	x0, x0, :lo12:.LANCHOR106
	b	.L881
	.size	zftl_gc_get_free_sblk, .-zftl_gc_get_free_sblk
	.section	.text.zftl_get_free_sblk,"ax",@progbits
	.align	2
	.global	zftl_get_free_sblk
	.type	zftl_get_free_sblk, %function
zftl_get_free_sblk:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	and	w20, w1, 65535
	str	x21, [sp, 32]
	cmp	w20, 5
	bne	.L883
	adrp	x2, .LANCHOR105
	adrp	x0, .LANCHOR107
	ldrh	w3, [x2, #:lo12:.LANCHOR105]
	ldrh	w1, [x0, #:lo12:.LANCHOR107]
	cmp	w3, w1
	bcc	.L884
	adrp	x4, .LANCHOR103
	ldrh	w4, [x4, #:lo12:.LANCHOR103]
	cmp	w4, w3
	bls	.L885
	cbz	w1, .L885
.L884:
	add	x2, x0, :lo12:.LANCHOR107
	lsr	w1, w1, 1
.L904:
	adrp	x0, .LANCHOR108
	add	x0, x0, :lo12:.LANCHOR108
	b	.L903
.L885:
	adrp	x0, .LANCHOR106
	add	x2, x2, :lo12:.LANCHOR105
	add	x0, x0, :lo12:.LANCHOR106
	mov	w1, 0
.L903:
	bl	_list_pop_index_node
	and	w19, w0, 65535
	mov	w0, 65535
	cmp	w19, w0
	bne	.L888
	adrp	x0, .LANCHOR107
	mov	w2, w20
	mov	w1, w19
	ldrh	w5, [x0, #:lo12:.LANCHOR107]
	adrp	x0, .LANCHOR103
	ldrh	w4, [x0, #:lo12:.LANCHOR103]
	adrp	x0, .LANCHOR104
	ldr	x3, [x0, #:lo12:.LANCHOR104]
	adrp	x0, .LC60
	add	x0, x0, :lo12:.LC60
	bl	printf
	b	.L888
.L883:
	adrp	x21, .LANCHOR12
	and	w3, w0, 65535
	ldr	x0, [x21, #:lo12:.LANCHOR12]
	ldrh	w19, [x0, 590]
	mov	w0, 65535
	cmp	w19, w0
	beq	.L887
	cmp	w20, 1
	beq	.L887
	mov	w1, w19
	adrp	x0, .LC62
	add	x0, x0, :lo12:.LC62
	bl	printf
	ldr	x0, [x21, #:lo12:.LANCHOR12]
	mov	w1, -1
	strh	w1, [x0, 590]
.L888:
	mov	w0, w19
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
.L887:
	adrp	x2, .LANCHOR103
	adrp	x4, .LANCHOR107
	ldrh	w0, [x2, #:lo12:.LANCHOR103]
	ldrh	w1, [x4, #:lo12:.LANCHOR107]
	cmp	w0, w1
	bcc	.L889
	adrp	x5, .LANCHOR105
	ldrh	w5, [x5, #:lo12:.LANCHOR105]
	cmp	w5, w0
	bls	.L890
	cbz	w1, .L890
.L889:
	bl	get_ink_scaned_blk
	and	w19, w0, 65535
	mov	w0, 65535
	cmp	w19, w0
	bne	.L888
	cmp	w20, 1
	bne	.L891
	ldrh	w3, [x4, #:lo12:.LANCHOR107]
	lsr	w3, w3, 1
.L891:
	add	x2, x4, :lo12:.LANCHOR107
	mov	w1, w3
	b	.L904
.L890:
	lsr	w0, w0, 1
	cmp	w20, 1
	csel	w3, w0, w3, eq
	add	x2, x2, :lo12:.LANCHOR103
	adrp	x0, .LANCHOR104
	mov	w1, w3
	add	x0, x0, :lo12:.LANCHOR104
	b	.L903
	.size	zftl_get_free_sblk, .-zftl_get_free_sblk
	.section	.text.zftl_remove_data_node,"ax",@progbits
	.align	2
	.global	zftl_remove_data_node
	.type	zftl_remove_data_node, %function
zftl_remove_data_node:
	and	w1, w0, 65535
	adrp	x0, .LANCHOR9
	ldr	x0, [x0, #:lo12:.LANCHOR9]
	add	x0, x0, x1, uxth 2
	ldrb	w2, [x0, 2]
	and	w2, w2, 224
	cmp	w2, 64
	bne	.L906
	adrp	x2, .LANCHOR97
	adrp	x0, .LANCHOR95
	add	x2, x2, :lo12:.LANCHOR97
	add	x0, x0, :lo12:.LANCHOR95
.L909:
	b	_list_remove_node
.L906:
	cmp	w2, 96
	bne	.L907
	adrp	x2, .LANCHOR99
	adrp	x0, .LANCHOR90
	add	x2, x2, :lo12:.LANCHOR99
	add	x0, x0, :lo12:.LANCHOR90
	b	.L909
.L907:
	cmp	w2, 160
	bne	.L905
	adrp	x2, .LANCHOR91
	adrp	x0, .LANCHOR92
	add	x2, x2, :lo12:.LANCHOR91
	add	x0, x0, :lo12:.LANCHOR92
	b	.L909
.L905:
	ret
	.size	zftl_remove_data_node, .-zftl_remove_data_node
	.section	.text.zftl_remove_free_node,"ax",@progbits
	.align	2
	.global	zftl_remove_free_node
	.type	zftl_remove_free_node, %function
zftl_remove_free_node:
	and	w1, w0, 65535
	adrp	x0, .LANCHOR9
	ldr	x0, [x0, #:lo12:.LANCHOR9]
	add	x0, x0, x1, uxth 2
	ldrb	w0, [x0, 2]
	ands	w0, w0, 24
	bne	.L911
	adrp	x2, .LANCHOR103
	adrp	x0, .LANCHOR104
	add	x2, x2, :lo12:.LANCHOR103
	add	x0, x0, :lo12:.LANCHOR104
.L913:
	b	_list_remove_node
.L911:
	cmp	w0, 16
	bne	.L912
	adrp	x2, .LANCHOR105
	adrp	x0, .LANCHOR106
	add	x2, x2, :lo12:.LANCHOR105
	add	x0, x0, :lo12:.LANCHOR106
	b	.L913
.L912:
	adrp	x2, .LANCHOR107
	adrp	x0, .LANCHOR108
	add	x2, x2, :lo12:.LANCHOR107
	add	x0, x0, :lo12:.LANCHOR108
	b	.L913
	.size	zftl_remove_free_node, .-zftl_remove_free_node
	.section	.text.zftl_list_update_data_list,"ax",@progbits
	.align	2
	.global	zftl_list_update_data_list
	.type	zftl_list_update_data_list, %function
zftl_list_update_data_list:
	and	w1, w0, 65535
	adrp	x0, .LANCHOR9
	ldr	x0, [x0, #:lo12:.LANCHOR9]
	add	x0, x0, x1, uxth 2
	ldrb	w2, [x0, 2]
	and	w2, w2, 224
	cmp	w2, 64
	bne	.L915
	adrp	x2, .LANCHOR97
	adrp	x0, .LANCHOR95
	add	x2, x2, :lo12:.LANCHOR97
	add	x0, x0, :lo12:.LANCHOR95
.L918:
	b	_list_update_data_list
.L915:
	cmp	w2, 96
	bne	.L916
	adrp	x2, .LANCHOR99
	adrp	x0, .LANCHOR90
	add	x2, x2, :lo12:.LANCHOR99
	add	x0, x0, :lo12:.LANCHOR90
	b	.L918
.L916:
	cmp	w2, 160
	bne	.L914
	adrp	x2, .LANCHOR91
	adrp	x0, .LANCHOR92
	add	x2, x2, :lo12:.LANCHOR91
	add	x0, x0, :lo12:.LANCHOR92
	b	.L918
.L914:
	ret
	.size	zftl_list_update_data_list, .-zftl_list_update_data_list
	.section	.text.print_list_info,"ax",@progbits
	.align	2
	.global	print_list_info
	.type	print_list_info, %function
print_list_info:
	sub	sp, sp, #96
	stp	x29, x30, [sp, 32]
	add	x29, sp, 32
	ldrh	w2, [x1]
	ldr	x1, [x0]
	stp	x19, x20, [sp, 48]
	mov	x19, x0
	stp	x21, x22, [sp, 64]
	adrp	x0, .LC63
	stp	x23, x24, [sp, 80]
	add	x0, x0, :lo12:.LC63
	bl	printf
	ldr	x19, [x19]
	cbz	x19, .L919
	mov	x24, -6148914691236517206
	adrp	x22, .LC64
	adrp	x21, .LANCHOR109
	add	x22, x22, :lo12:.LC64
	add	x21, x21, :lo12:.LANCHOR109
	mov	w20, 0
	adrp	x23, .LANCHOR4
	movk	x24, 0xaaab, lsl 0
.L923:
	ldr	x2, [x23, #:lo12:.LANCHOR4]
	adrp	x1, .LANCHOR9
	adrp	x8, .LANCHOR11
	ldrh	w5, [x19, 4]
	sub	x2, x19, x2
	ldr	x1, [x1, #:lo12:.LANCHOR9]
	asr	x2, x2, 1
	ldr	x8, [x8, #:lo12:.LANCHOR11]
	ldrh	w4, [x19, 2]
	mul	x2, x2, x24
	and	x7, x2, 65535
	and	w2, w2, 65535
	lsl	x0, x7, 2
	add	x3, x1, x0
	ldrh	w7, [x8, x7, lsl 1]
	ldrb	w6, [x3, 2]
	ldrh	w3, [x19]
	str	w7, [sp, 16]
	ldrh	w7, [x1, x0]
	and	w7, w7, 2047
	str	w7, [sp, 8]
	ubfx	x7, x6, 3, 2
	ubfx	x6, x6, 5, 3
	ldr	w0, [x1, x0]
	mov	w1, w20
	ubfx	x0, x0, 11, 8
	str	w0, [sp]
	mov	x0, x22
	bl	printf
	ldrh	w19, [x19]
	mov	w0, 65535
	cmp	w19, w0
	beq	.L919
	ldr	x0, [x23, #:lo12:.LANCHOR4]
	mov	w1, 6
	add	w20, w20, 1
	and	w20, w20, 65535
	umaddl	x19, w19, w1, x0
	ldrh	w0, [x21]
	cmp	w0, w20
	bcs	.L923
.L919:
	ldp	x19, x20, [sp, 48]
	ldp	x21, x22, [sp, 64]
	ldp	x23, x24, [sp, 80]
	ldp	x29, x30, [sp, 32]
	add	sp, sp, 96
	ret
	.size	print_list_info, .-print_list_info
	.section	.text.dump_all_list_info,"ax",@progbits
	.align	2
	.global	dump_all_list_info
	.type	dump_all_list_info, %function
dump_all_list_info:
	stp	x29, x30, [sp, -16]!
	adrp	x1, .LANCHOR103
	adrp	x0, .LANCHOR104
	add	x1, x1, :lo12:.LANCHOR103
	add	x29, sp, 0
	add	x0, x0, :lo12:.LANCHOR104
	bl	print_list_info
	adrp	x1, .LANCHOR105
	adrp	x0, .LANCHOR106
	add	x1, x1, :lo12:.LANCHOR105
	add	x0, x0, :lo12:.LANCHOR106
	bl	print_list_info
	adrp	x1, .LANCHOR107
	adrp	x0, .LANCHOR108
	add	x1, x1, :lo12:.LANCHOR107
	add	x0, x0, :lo12:.LANCHOR108
	bl	print_list_info
	adrp	x1, .LANCHOR97
	adrp	x0, .LANCHOR95
	add	x1, x1, :lo12:.LANCHOR97
	add	x0, x0, :lo12:.LANCHOR95
	bl	print_list_info
	adrp	x1, .LANCHOR99
	adrp	x0, .LANCHOR90
	add	x1, x1, :lo12:.LANCHOR99
	add	x0, x0, :lo12:.LANCHOR90
	bl	print_list_info
	ldp	x29, x30, [sp], 16
	adrp	x1, .LANCHOR91
	adrp	x0, .LANCHOR92
	add	x1, x1, :lo12:.LANCHOR91
	add	x0, x0, :lo12:.LANCHOR92
	b	print_list_info
	.size	dump_all_list_info, .-dump_all_list_info
	.section	.text.ftl_tmp_into_update,"ax",@progbits
	.align	2
	.global	ftl_tmp_into_update
	.type	ftl_tmp_into_update, %function
ftl_tmp_into_update:
	adrp	x0, .LANCHOR110
	ldr	x0, [x0, #:lo12:.LANCHOR110]
	ldr	w1, [x0, 16]
	cmp	w1, 2048
	bls	.L928
	ldr	w2, [x0, 20]
	add	w2, w2, w1, lsr 11
	and	w1, w1, 2047
	stp	w1, w2, [x0, 16]
.L928:
	ldr	w1, [x0, 24]
	cmp	w1, 2048
	bls	.L929
	ldr	w2, [x0, 28]
	add	w2, w2, w1, lsr 11
	and	w1, w1, 2047
	stp	w1, w2, [x0, 24]
.L929:
	ldr	w1, [x0, 32]
	cmp	w1, 1024
	bls	.L930
	ldr	w2, [x0, 36]
	add	w2, w2, w1, lsr 10
	and	w1, w1, 1023
	stp	w1, w2, [x0, 32]
.L930:
	ldr	w1, [x0, 40]
	cmp	w1, 1024
	bls	.L927
	ldr	w2, [x0, 44]
	add	w2, w2, w1, lsr 10
	and	w1, w1, 1023
	stp	w1, w2, [x0, 40]
.L927:
	ret
	.size	ftl_tmp_into_update, .-ftl_tmp_into_update
	.section	.text.ftl_get_blk_list_in_sblk,"ax",@progbits
	.align	2
	.global	ftl_get_blk_list_in_sblk
	.type	ftl_get_blk_list_in_sblk, %function
ftl_get_blk_list_in_sblk:
	adrp	x2, .LANCHOR9
	and	w0, w0, 65535
	mov	w7, 24
	adrp	x8, .LANCHOR74
	ldr	x2, [x2, #:lo12:.LANCHOR9]
	add	x8, x8, :lo12:.LANCHOR74
	mov	w3, 0
	add	x2, x2, x0, uxth 2
	ldrb	w13, [x2, 3]
	adrp	x2, .LANCHOR79
	ldrb	w11, [x2, #:lo12:.LANCHOR79]
	adrp	x2, .LANCHOR75
	ldrb	w6, [x2, #:lo12:.LANCHOR75]
	adrp	x2, .LANCHOR31
	ldrb	w2, [x2, #:lo12:.LANCHOR31]
	sub	w7, w7, w2
	and	w2, w6, 65535
	mul	w0, w0, w2
	sub	w2, w2, #1
	sxth	w5, w2
	and	w4, w0, 65535
	mov	w0, 0
.L933:
	cmp	w3, w11
	blt	.L937
	sxtw	x2, w0
	mov	w3, -1
.L938:
	cmp	w11, w2
	bgt	.L939
	ret
.L937:
	asr	w2, w13, w3
	tbnz	x2, 0, .L934
	sdiv	w2, w3, w6
	ldrh	w10, [x8]
	sbfiz	x12, x0, 1, 32
	cmp	w6, 1
	sub	w10, w7, w10
	lsl	w2, w2, w10
	add	w2, w4, w2
	and	w2, w2, 65535
	bhi	.L935
.L940:
	add	w0, w0, 1
	strh	w2, [x1, x12]
.L934:
	add	w3, w3, 1
	b	.L933
.L935:
	and	w10, w5, w3
	add	w2, w2, w10
	b	.L940
.L939:
	strh	w3, [x1, x2, lsl 1]
	add	x2, x2, 1
	b	.L938
	.size	ftl_get_blk_list_in_sblk, .-ftl_get_blk_list_in_sblk
	.section	.text.ftl_erase_phy_blk,"ax",@progbits
	.align	2
	.global	ftl_erase_phy_blk
	.type	ftl_erase_phy_blk, %function
ftl_erase_phy_blk:
	stp	x29, x30, [sp, -48]!
	and	w0, w0, 65535
	add	x29, sp, 0
	stp	x21, x22, [sp, 32]
	mov	w21, w1
	adrp	x1, .LANCHOR31
	stp	x19, x20, [sp, 16]
	adrp	x22, .LANCHOR111
	ldrb	w19, [x1, #:lo12:.LANCHOR31]
	mov	w1, 24
	sub	w19, w1, w19
	adrp	x1, .LANCHOR74
	ldrh	w1, [x1, #:lo12:.LANCHOR74]
	sub	w1, w19, w1
	mov	w19, 1
	lsl	w19, w19, w1
	sub	w19, w19, #1
	and	w19, w19, w0
	asr	w20, w0, w1
	adrp	x0, .LANCHOR80
	sxth	w19, w19
	ldrb	w0, [x0, #:lo12:.LANCHOR80]
	cbz	w0, .L942
	adrp	x0, .LANCHOR81
	ldrb	w0, [x0, #:lo12:.LANCHOR81]
	cbnz	w0, .L942
	ldrh	w2, [x22, #:lo12:.LANCHOR111]
	cmp	w21, 0
	cset	w1, eq
	mov	w0, w20
	mul	w2, w2, w19
	bl	flash_erase_block_en
.L942:
	ldrh	w2, [x22, #:lo12:.LANCHOR111]
	mov	w1, w21
	mov	w0, w20
	ldp	x21, x22, [sp, 32]
	mul	w2, w2, w19
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	b	flash_erase_block_en
	.size	ftl_erase_phy_blk, .-ftl_erase_phy_blk
	.section	.text.ftl_erase_sblk,"ax",@progbits
	.align	2
	.global	ftl_erase_sblk
	.type	ftl_erase_sblk, %function
ftl_erase_sblk:
	stp	x29, x30, [sp, -176]!
	add	x29, sp, 0
	stp	x23, x24, [sp, 48]
	adrp	x23, .LANCHOR9
	stp	x25, x26, [sp, 64]
	and	w26, w0, 65535
	ldr	x0, [x23, #:lo12:.LANCHOR9]
	adrp	x25, .LANCHOR112
	stp	x21, x22, [sp, 32]
	ubfiz	x22, x26, 2, 16
	add	x0, x0, x22
	stp	x27, x28, [sp, 80]
	stp	x19, x20, [sp, 16]
	adrp	x24, .LANCHOR75
	mov	w20, w1
	add	x25, x25, :lo12:.LANCHOR112
	ldrb	w28, [x0, 3]
	add	x24, x24, :lo12:.LANCHOR75
	add	x27, x29, 112
	mov	w19, 0
.L948:
	ldrb	w0, [x25]
	cmp	w19, w0
	bge	.L959
	ldrb	w1, [x24]
	adrp	x0, .LANCHOR111
	mov	w21, 0
	ldrh	w3, [x0, #:lo12:.LANCHOR111]
	sub	w4, w1, #1
	mov	w0, 0
	mul	w6, w19, w1
	mul	w5, w26, w1
	b	.L960
.L950:
	add	w2, w0, w6
	asr	w2, w28, w2
	tbnz	x2, 0, .L949
	and	w2, w0, w4
	add	w2, w2, w5
	mul	w2, w2, w3
	str	w2, [x27, w21, sxtw 2]
	add	w21, w21, 1
.L949:
	add	w0, w0, 1
.L960:
	cmp	w0, w1
	blt	.L950
	cmp	w1, 4
	bne	.L951
	mov	x3, 0
.L952:
	cmp	w21, w3
	bgt	.L953
.L954:
	add	w19, w19, 1
	b	.L948
.L953:
	ldr	w2, [x27, x3, lsl 2]
	mov	w1, w20
	str	x3, [x29, 104]
	mov	w0, w19
	bl	flash_erase_block_en
	ldr	x3, [x29, 104]
	add	x3, x3, 1
	b	.L952
.L951:
	cmp	w21, 2
	bne	.L955
	adrp	x0, .LANCHOR80
	ldrb	w0, [x0, #:lo12:.LANCHOR80]
	cbz	w0, .L956
	adrp	x0, .LANCHOR81
	ldrb	w0, [x0, #:lo12:.LANCHOR81]
	cbnz	w0, .L956
	ldp	w2, w3, [x29, 112]
	cmp	w20, 0
	cset	w1, eq
	mov	w0, w19
	bl	flash_erase_duplane_block
.L956:
	ldp	w2, w3, [x29, 112]
	mov	w1, w20
	mov	w0, w19
	bl	flash_erase_duplane_block
	b	.L954
.L955:
	cmp	w21, 1
	bne	.L954
	adrp	x0, .LANCHOR80
	ldrb	w0, [x0, #:lo12:.LANCHOR80]
	cbz	w0, .L958
	adrp	x0, .LANCHOR81
	ldrb	w0, [x0, #:lo12:.LANCHOR81]
	cbnz	w0, .L958
	ldr	w2, [x29, 112]
	cmp	w20, 0
	cset	w1, eq
	mov	w0, w19
	bl	flash_erase_block_en
.L958:
	ldr	w2, [x29, 112]
	mov	w1, w20
	mov	w0, w19
	bl	flash_erase_block_en
	b	.L954
.L959:
	adrp	x2, .LANCHOR110
	ldr	x3, [x23, #:lo12:.LANCHOR9]
	cbnz	w20, .L961
	ldrh	w1, [x3, x22]
	add	w0, w1, 1
	and	w0, w0, 2047
	bfi	w1, w0, 0, 11
	strh	w1, [x3, x22]
	ldr	x1, [x2, #:lo12:.LANCHOR110]
	ldr	w2, [x1, 84]
	add	w2, w2, 1
	str	w2, [x1, 84]
	ldrh	w2, [x1, 96]
	cmp	w2, w0
	bge	.L963
	strh	w0, [x1, 96]
.L963:
	ldp	x19, x20, [sp, 16]
	mov	w0, 0
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 176
	ret
.L961:
	ldr	w1, [x3, x22]
	ubfx	x0, x1, 11, 8
	add	w0, w0, 1
	and	w0, w0, 255
	bfi	w1, w0, 11, 8
	str	w1, [x3, x22]
	and	w0, w0, 65535
	ldr	x1, [x2, #:lo12:.LANCHOR110]
	ldr	w2, [x1, 80]
	add	w2, w2, 1
	str	w2, [x1, 80]
	ldrh	w2, [x1, 98]
	cmp	w2, w0
	bcs	.L963
	strh	w0, [x1, 98]
	b	.L963
	.size	ftl_erase_sblk, .-ftl_erase_sblk
	.section	.text.ftl_alloc_sys_blk,"ax",@progbits
	.align	2
	.global	ftl_alloc_sys_blk
	.type	ftl_alloc_sys_blk, %function
ftl_alloc_sys_blk:
	stp	x29, x30, [sp, -32]!
	adrp	x0, .LANCHOR110
	add	x29, sp, 0
	ldr	x1, [x0, #:lo12:.LANCHOR110]
	ldrh	w2, [x1, 136]
	str	x19, [sp, 16]
	mov	x19, x0
	cmp	w2, 63
	bls	.L973
	strh	wzr, [x1, 136]
.L973:
	ldrh	w0, [x1, 112]
	cbnz	w0, .L974
	adrp	x1, .LANCHOR113
	adrp	x0, .LC0
	mov	w2, 1359
	add	x1, x1, :lo12:.LANCHOR113
	add	x0, x0, :lo12:.LC0
	bl	printf
.L974:
	ldr	x1, [x19, #:lo12:.LANCHOR110]
	mov	w5, 65535
.L977:
	ldrh	w2, [x1, 136]
.L975:
	mov	w3, w2
	cmp	w2, 63
	ble	.L976
	strh	wzr, [x1, 136]
	b	.L977
.L976:
	add	x4, x2, 1
	add	x0, x1, x4, lsl 1
	ldrh	w0, [x0, 158]
	cmp	w0, w5
	bne	.L980
	mov	x2, x4
	b	.L975
.L980:
	add	x3, x1, x3, sxtw 1
	mov	w4, -1
	ldr	x19, [sp, 16]
	strh	w4, [x3, 160]
	strh	w2, [x1, 136]
	ldrh	w2, [x1, 112]
	sub	w2, w2, #1
	strh	w2, [x1, 112]
	ldp	x29, x30, [sp], 32
	ret
	.size	ftl_alloc_sys_blk, .-ftl_alloc_sys_blk
	.section	.text.ftl_free_sys_blk,"ax",@progbits
	.align	2
	.global	ftl_free_sys_blk
	.type	ftl_free_sys_blk, %function
ftl_free_sys_blk:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	and	w20, w0, 65535
	adrp	x0, .LANCHOR110
	mov	x19, x0
	ldr	x1, [x0, #:lo12:.LANCHOR110]
	ldrh	w2, [x1, 138]
	cmp	w2, 63
	bls	.L983
	strh	wzr, [x1, 138]
.L983:
	ldrh	w0, [x1, 112]
	cmp	w0, 63
	bls	.L984
	adrp	x1, .LANCHOR114
	adrp	x0, .LC0
	mov	w2, 1386
	add	x1, x1, :lo12:.LANCHOR114
	add	x0, x0, :lo12:.LC0
	bl	printf
.L984:
	ldr	x0, [x19, #:lo12:.LANCHOR110]
	mov	w4, 65535
.L987:
	ldrh	w1, [x0, 138]
.L985:
	mov	w2, w1
	cmp	w1, 63
	ble	.L986
	strh	wzr, [x0, 138]
	b	.L987
.L986:
	add	x3, x1, 1
	add	x5, x0, x3, lsl 1
	ldrh	w5, [x5, 158]
	cmp	w5, w4
	bne	.L988
	add	x2, x0, x2, sxtw 1
	strh	w20, [x2, 160]
	strh	w1, [x0, 138]
	ldrh	w1, [x0, 112]
	ldp	x19, x20, [sp, 16]
	add	w1, w1, 1
	strh	w1, [x0, 112]
	ldp	x29, x30, [sp], 32
	ret
.L988:
	mov	x1, x3
	b	.L985
	.size	ftl_free_sys_blk, .-ftl_free_sys_blk
	.section	.text.ftl_info_data_recovery,"ax",@progbits
	.align	2
	.global	ftl_info_data_recovery
	.type	ftl_info_data_recovery, %function
ftl_info_data_recovery:
	ldrh	w2, [x0]
	mov	w1, 65535
	cmp	w2, w1
	beq	.L1001
	stp	x29, x30, [sp, -48]!
	adrp	x1, .LANCHOR9
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	ubfiz	x19, x2, 2, 16
	ldr	x20, [x1, #:lo12:.LANCHOR9]
	str	x21, [sp, 32]
	add	x21, x20, x19
	ldrb	w1, [x21, 2]
	tst	w1, 224
	bne	.L991
	ldrb	w0, [x0, 4]
	bfi	w1, w0, 5, 3
	strb	w1, [x21, 2]
	mov	w0, w2
	bl	zftl_remove_free_node
	ldrb	w0, [x21, 2]
	adrp	x1, .LANCHOR110
	ldr	x3, [x1, #:lo12:.LANCHOR110]
	tbz	x0, 3, .L995
	ldrh	w2, [x3, 116]
	sub	w2, w2, #1
	strh	w2, [x3, 116]
.L996:
	and	w0, w0, 224
	cmp	w0, 160
	bne	.L998
	ldr	w0, [x20, x19]
	ldr	x1, [x1, #:lo12:.LANCHOR110]
	ubfx	x2, x0, 11, 8
	add	w2, w2, 1
	bfi	w0, w2, 11, 8
	str	w0, [x20, x19]
	ldrh	w0, [x1, 120]
	sub	w0, w0, #1
	strh	w0, [x1, 120]
.L991:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
.L995:
	tst	w0, 24
	bne	.L997
	ldrh	w2, [x3, 114]
	sub	w2, w2, #1
	strh	w2, [x3, 114]
	b	.L996
.L997:
	ldrh	w2, [x3, 118]
	sub	w2, w2, #1
	strh	w2, [x3, 118]
	b	.L996
.L998:
	ldrh	w2, [x20, x19]
	cmp	w0, 64
	add	w3, w2, 1
	bfi	w2, w3, 0, 11
	strh	w2, [x20, x19]
	bne	.L999
	ldr	x1, [x1, #:lo12:.LANCHOR110]
	ldrh	w0, [x1, 122]
	sub	w0, w0, #1
	strh	w0, [x1, 122]
	b	.L991
.L999:
	cmp	w0, 96
	bne	.L991
	ldr	x1, [x1, #:lo12:.LANCHOR110]
	ldrh	w0, [x1, 124]
	sub	w0, w0, #1
	strh	w0, [x1, 124]
	b	.L991
.L1001:
	ret
	.size	ftl_info_data_recovery, .-ftl_info_data_recovery
	.section	.text.ftl_get_ppa_from_index,"ax",@progbits
	.align	2
	.global	ftl_get_ppa_from_index
	.type	ftl_get_ppa_from_index, %function
ftl_get_ppa_from_index:
	stp	x29, x30, [sp, -32]!
	adrp	x1, .LANCHOR12
	adrp	x3, .LANCHOR79
	and	w0, w0, 65535
	add	x29, sp, 0
	ldr	x2, [x1, #:lo12:.LANCHOR12]
	adrp	x1, .LANCHOR94
	ldrb	w3, [x3, #:lo12:.LANCHOR79]
	ldrh	w1, [x1, #:lo12:.LANCHOR94]
	stp	x19, x20, [sp, 16]
	mul	w1, w1, w3
	cmp	w0, w1
	bge	.L1005
	add	x2, x2, 16
.L1006:
	ldrb	w1, [x2, 9]
	sdiv	w19, w0, w1
	msub	w0, w19, w1, w0
	add	x0, x2, x0, uxth 1
	ldrh	w20, [x0, 16]
	mov	w0, 65535
	cmp	w20, w0
	bne	.L1007
	adrp	x1, .LANCHOR115
	adrp	x0, .LC0
	mov	w2, 1945
	add	x1, x1, :lo12:.LANCHOR115
	add	x0, x0, :lo12:.LC0
	bl	printf
.L1007:
	adrp	x0, .LANCHOR111
	ldrh	w0, [x0, #:lo12:.LANCHOR111]
	madd	w0, w0, w20, w19
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L1005:
	sub	w0, w0, w1
	add	x2, x2, 48
	and	w0, w0, 65535
	b	.L1006
	.size	ftl_get_ppa_from_index, .-ftl_get_ppa_from_index
	.section	.text.lpa_hash_get_ppa,"ax",@progbits
	.align	2
	.global	lpa_hash_get_ppa
	.type	lpa_hash_get_ppa, %function
lpa_hash_get_ppa:
	and	x2, x0, 255
	adrp	x1, .LANCHOR116
	add	x1, x1, :lo12:.LANCHOR116
	mov	w3, 65535
	ldrh	w1, [x1, x2, lsl 1]
	adrp	x2, .LANCHOR117
	ldr	x4, [x2, #:lo12:.LANCHOR117]
	adrp	x2, .LANCHOR118
	ldr	x5, [x2, #:lo12:.LANCHOR118]
.L1010:
	cmp	w1, w3
	bne	.L1012
	mov	w0, -1
	ret
.L1012:
	uxtw	x2, w1
	ldr	w6, [x4, x2, lsl 2]
	cmp	w0, w6
	bne	.L1011
	mov	w0, w1
	b	ftl_get_ppa_from_index
.L1011:
	ldrh	w1, [x5, x2, lsl 1]
	b	.L1010
	.size	lpa_hash_get_ppa, .-lpa_hash_get_ppa
	.section	.text.ftl_get_new_free_page,"ax",@progbits
	.align	2
	.global	ftl_get_new_free_page
	.type	ftl_get_new_free_page, %function
ftl_get_new_free_page:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	ldrh	w1, [x0]
	str	x19, [sp, 16]
	mov	x19, x0
	mov	w0, 65535
	cmp	w1, w0
	bne	.L1014
	adrp	x1, .LANCHOR119
	adrp	x0, .LC0
	mov	w2, 2088
	add	x1, x1, :lo12:.LANCHOR119
	add	x0, x0, :lo12:.LC0
	bl	printf
.L1014:
	adrp	x0, .LANCHOR94
	ldrh	w1, [x19, 2]
	ldrh	w0, [x0, #:lo12:.LANCHOR94]
	cmp	w1, w0
	bne	.L1015
	adrp	x1, .LANCHOR119
	adrp	x0, .LC0
	mov	w2, 2089
	add	x1, x1, :lo12:.LANCHOR119
	add	x0, x0, :lo12:.LC0
	bl	printf
.L1015:
	ldrh	w0, [x19, 6]
	cbnz	w0, .L1016
	adrp	x1, .LANCHOR119
	adrp	x0, .LC0
	mov	w2, 2090
	add	x1, x1, :lo12:.LANCHOR119
	add	x0, x0, :lo12:.LC0
	bl	printf
.L1016:
	ldrb	w0, [x19, 5]
	mov	w2, 65535
	add	x0, x0, 8
	ldrh	w3, [x19, x0, lsl 1]
	adrp	x0, .LANCHOR79
	ldrb	w4, [x0, #:lo12:.LANCHOR79]
.L1017:
	cmp	w3, w2
	ldrb	w1, [x19, 5]
	beq	.L1019
	adrp	x0, .LANCHOR111
	add	w1, w1, 1
	and	w1, w1, 255
	ldrh	w2, [x19, 2]
	ldrh	w0, [x0, #:lo12:.LANCHOR111]
	cmp	w4, w1
	strb	w1, [x19, 5]
	mul	w0, w0, w3
	ldrh	w3, [x19, 6]
	sub	w3, w3, #1
	strh	w3, [x19, 6]
	ldrh	w3, [x19, 10]
	orr	w0, w0, w2
	add	w3, w3, 1
	strh	w3, [x19, 10]
	bne	.L1013
	add	w2, w2, 1
	strb	wzr, [x19, 5]
	strh	w2, [x19, 2]
.L1013:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L1019:
	add	w1, w1, 1
	and	w1, w1, 255
	strb	w1, [x19, 5]
	cmp	w1, w4
	bne	.L1018
	ldrh	w0, [x19, 2]
	strb	wzr, [x19, 5]
	add	w0, w0, 1
	strh	w0, [x19, 2]
.L1018:
	ldrb	w0, [x19, 5]
	add	x0, x0, 8
	ldrh	w3, [x19, x0, lsl 1]
	b	.L1017
	.size	ftl_get_new_free_page, .-ftl_get_new_free_page
	.section	.text.ftl_ext_alloc_new_blk,"ax",@progbits
	.align	2
	.global	ftl_ext_alloc_new_blk
	.type	ftl_ext_alloc_new_blk, %function
ftl_ext_alloc_new_blk:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	bl	ftl_alloc_sys_blk
	and	w0, w0, 65535
	mov	w1, 65533
	mov	w19, w0
	sub	w0, w0, #1
	cmp	w1, w0, uxth
	bcs	.L1023
	adrp	x1, .LANCHOR120
	adrp	x0, .LC0
	mov	w2, 2125
	add	x1, x1, :lo12:.LANCHOR120
	add	x0, x0, :lo12:.LC0
	bl	printf
.L1023:
	adrp	x20, .LANCHOR110
	mov	w1, 0
	mov	w0, w19
	bl	ftl_erase_phy_blk
	ldr	x0, [x20, #:lo12:.LANCHOR110]
	ldrh	w0, [x0, 130]
	bl	ftl_free_sys_blk
	ldr	x0, [x20, #:lo12:.LANCHOR110]
	strh	w19, [x0, 130]
	strh	wzr, [x0, 140]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	ftl_ext_alloc_new_blk, .-ftl_ext_alloc_new_blk
	.section	.text.ftl_total_vpn_update,"ax",@progbits
	.align	2
	.global	ftl_total_vpn_update
	.type	ftl_total_vpn_update, %function
ftl_total_vpn_update:
	adrp	x2, .LANCHOR121
	mov	x3, x2
	ldrh	w1, [x2, #:lo12:.LANCHOR121]
	cmp	w1, 4
	bhi	.L1026
	cbnz	w0, .L1026
	add	w1, w1, 1
	strh	w1, [x2, #:lo12:.LANCHOR121]
	ret
.L1026:
	adrp	x0, .LANCHOR8
	strh	wzr, [x3, #:lo12:.LANCHOR121]
	mov	x1, 0
	mov	w2, 0
	ldrh	w5, [x0, #:lo12:.LANCHOR8]
	adrp	x0, .LANCHOR11
	mov	w8, 65535
	ldr	x6, [x0, #:lo12:.LANCHOR11]
	adrp	x0, .LANCHOR9
	ldr	x7, [x0, #:lo12:.LANCHOR9]
	mov	w0, 0
.L1028:
	cmp	w5, w1, uxth
	bhi	.L1031
	adrp	x1, .LANCHOR12
	ldr	x1, [x1, #:lo12:.LANCHOR12]
	str	w2, [x1, 524]
	adrp	x2, .LANCHOR110
	str	w0, [x1, 528]
	ldr	x2, [x2, #:lo12:.LANCHOR110]
	ldrh	w2, [x2, 120]
	cbz	w2, .L1025
	udiv	w0, w0, w2
	str	w0, [x1, 532]
.L1025:
	ret
.L1031:
	ldrh	w3, [x6, x1, lsl 1]
	cmp	w3, w8
	beq	.L1029
	add	x4, x7, x1, lsl 2
	ldrb	w4, [x4, 2]
	and	w4, w4, 224
	cmp	w4, 160
	bne	.L1030
	add	w0, w0, w3
.L1029:
	add	x1, x1, 1
	b	.L1028
.L1030:
	add	w2, w2, w3
	b	.L1029
	.size	ftl_total_vpn_update, .-ftl_total_vpn_update
	.section	.text.ftl_vpn_update,"ax",@progbits
	.align	2
	.global	ftl_vpn_update
	.type	ftl_vpn_update, %function
ftl_vpn_update:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	and	w19, w0, 65535
	mov	w0, w19
	bl	zftl_list_update_data_list
	adrp	x0, .LANCHOR11
	ubfiz	x19, x19, 1, 16
	ldr	x0, [x0, #:lo12:.LANCHOR11]
	ldrh	w0, [x0, x19]
	cbnz	w0, .L1038
	adrp	x1, .LANCHOR122
	mov	w0, 1
	str	w0, [x1, #:lo12:.LANCHOR122]
.L1036:
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L1038:
	mov	w0, 0
	b	.L1036
	.size	ftl_vpn_update, .-ftl_vpn_update
	.section	.text.ftl_vpn_decrement,"ax",@progbits
	.align	2
	.global	ftl_vpn_decrement
	.type	ftl_vpn_decrement, %function
ftl_vpn_decrement:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	and	w19, w0, 65535
	mov	w0, 65535
	cmp	w19, w0
	beq	.L1041
	adrp	x0, .LANCHOR11
	uxtw	x1, w19
	lsl	x2, x1, 1
	ldr	x3, [x0, #:lo12:.LANCHOR11]
	ldrh	w0, [x3, x2]
	cbnz	w0, .L1042
	adrp	x0, .LANCHOR9
	mov	w2, 0
	ldr	x0, [x0, #:lo12:.LANCHOR9]
	add	x1, x0, x1, lsl 2
	adrp	x0, .LC65
	add	x0, x0, :lo12:.LC65
	ldrb	w3, [x1, 2]
	mov	w1, w19
	ubfx	x3, x3, 5, 3
	bl	printf
.L1047:
	mov	w0, 0
	b	.L1040
.L1042:
	sub	w0, w0, #1
	strh	w0, [x3, x2]
.L1041:
	adrp	x20, .LANCHOR72
	ldrh	w0, [x20, #:lo12:.LANCHOR72]
	cmp	w19, w0
	beq	.L1047
	mov	w1, 65535
	cmp	w0, w1
	bne	.L1044
	strh	w19, [x20, #:lo12:.LANCHOR72]
	b	.L1047
.L1044:
	bl	ftl_vpn_update
	cmp	w0, 0
	adrp	x1, .LANCHOR123
	cset	w0, ne
	ldrh	w3, [x20, #:lo12:.LANCHOR72]
	ldrh	w2, [x1, #:lo12:.LANCHOR123]
	strh	w19, [x20, #:lo12:.LANCHOR72]
	add	w2, w2, 1
	and	w2, w2, 65535
	cmp	w2, 7
	csel	w2, w2, wzr, ls
	strh	w2, [x1, #:lo12:.LANCHOR123]
	and	x2, x2, 65535
	adrp	x1, .LANCHOR73
	add	x1, x1, :lo12:.LANCHOR73
	strh	w3, [x1, x2, lsl 1]
.L1040:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	ftl_vpn_decrement, .-ftl_vpn_decrement
	.section	.text.lpa_hash_update_ppa,"ax",@progbits
	.align	2
	.global	lpa_hash_update_ppa
	.type	lpa_hash_update_ppa, %function
lpa_hash_update_ppa:
	adrp	x3, .LANCHOR116
	and	x5, x0, 255
	add	x4, x3, :lo12:.LANCHOR116
	mov	w7, 65535
	and	w2, w2, 65535
	mov	w12, w7
	ldrh	w6, [x4, x5, lsl 1]
	adrp	x4, .LANCHOR117
	ldr	x8, [x4, #:lo12:.LANCHOR117]
	adrp	x4, .LANCHOR118
	ldr	x4, [x4, #:lo12:.LANCHOR118]
.L1050:
	cmp	w6, w12
	beq	.L1054
	uxtw	x11, w6
	lsl	x10, x11, 2
	add	x13, x8, x10
	ldr	w10, [x8, x10]
	cmp	w0, w10
	lsl	x10, x11, 1
	bne	.L1051
	mov	w6, -1
	str	w6, [x13]
	cmp	w7, w12
	bne	.L1052
	add	x6, x3, :lo12:.LANCHOR116
	ldrh	w7, [x4, x10]
	strh	w7, [x6, x5, lsl 1]
.L1053:
	mov	w6, -1
	strh	w6, [x4, x11, lsl 1]
.L1054:
	uxtw	x6, w2
	add	x3, x3, :lo12:.LANCHOR116
	cmn	w1, #1
	str	w0, [x8, x6, lsl 2]
	ldrh	w0, [x3, x5, lsl 1]
	strh	w2, [x3, x5, lsl 1]
	strh	w0, [x4, x6, lsl 1]
	beq	.L1061
	stp	x29, x30, [sp, -16]!
	adrp	x0, .LANCHOR74
	add	x29, sp, 0
	ldrh	w3, [x0, #:lo12:.LANCHOR74]
	adrp	x0, .LANCHOR31
	ldrb	w2, [x0, #:lo12:.LANCHOR31]
	mov	w0, 24
	lsr	w1, w1, w3
	sub	w0, w0, w2
	sub	w2, w0, w3
	mov	w0, 1
	lsl	w0, w0, w2
	sub	w0, w0, #1
	and	w1, w0, w1
	adrp	x0, .LANCHOR75
	ldrb	w0, [x0, #:lo12:.LANCHOR75]
	udiv	w0, w1, w0
	bl	ftl_vpn_decrement
	mov	w0, -1
	ldp	x29, x30, [sp], 16
	ret
.L1052:
	ldrh	w6, [x4, x10]
	strh	w6, [x4, w7, uxtw 1]
	b	.L1053
.L1051:
	mov	w7, w6
	ldrh	w6, [x4, x10]
	b	.L1050
.L1061:
	mov	w0, -1
	ret
	.size	lpa_hash_update_ppa, .-lpa_hash_update_ppa
	.section	.text.ftl_mask_bad_block,"ax",@progbits
	.align	2
	.global	ftl_mask_bad_block
	.type	ftl_mask_bad_block, %function
ftl_mask_bad_block:
	stp	x29, x30, [sp, -32]!
	adrp	x1, .LANCHOR31
	mov	w6, 24
	mov	w4, 1
	add	x29, sp, 0
	ldrb	w1, [x1, #:lo12:.LANCHOR31]
	stp	x19, x20, [sp, 16]
	sub	w6, w6, w1
	lsl	w1, w4, w1
	sub	w1, w1, #1
	lsr	w2, w0, w6
	and	w1, w1, w2
	adrp	x2, .LANCHOR75
	and	w1, w1, 255
	ldrb	w5, [x2, #:lo12:.LANCHOR75]
	cmp	w5, 1
	mul	w2, w1, w5
	and	w19, w2, 255
	adrp	x2, .LANCHOR74
	ldrh	w3, [x2, #:lo12:.LANCHOR74]
	lsr	w0, w0, w3
	sub	w3, w6, w3
	lsl	w3, w4, w3
	sub	w3, w3, #1
	and	w3, w3, w0
	and	w4, w3, 65535
	udiv	w3, w3, w5
	and	w20, w3, 65535
	bls	.L1065
	sub	w2, w5, #1
	and	w2, w2, w4
	add	w2, w19, w2
	and	w19, w2, 255
.L1065:
	adrp	x0, .LANCHOR19
	ldr	w0, [x0, #:lo12:.LANCHOR19]
	tbz	x0, 14, .L1066
	adrp	x0, .LC66
	and	w3, w3, 65535
	mov	w2, w19
	add	x0, x0, :lo12:.LC66
	bl	printf
.L1066:
	adrp	x0, .LANCHOR8
	ldrh	w0, [x0, #:lo12:.LANCHOR8]
	cmp	w0, w20
	bls	.L1064
	adrp	x0, .LANCHOR9
	mov	w2, 1
	lsl	w2, w2, w19
	ldr	x0, [x0, #:lo12:.LANCHOR9]
	add	x20, x0, x20, uxth 2
	ldrb	w19, [x20, 3]
	orr	w2, w2, w19
	strb	w2, [x20, 3]
.L1064:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	ftl_mask_bad_block, .-ftl_mask_bad_block
	.section	.text.gc_free_bad_sblk,"ax",@progbits
	.align	2
	.global	gc_free_bad_sblk
	.type	gc_free_bad_sblk, %function
gc_free_bad_sblk:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x23, x24, [sp, 48]
	and	w23, w0, 65535
	str	x27, [sp, 80]
	adrp	x27, .LANCHOR70
	add	x0, x27, :lo12:.LANCHOR70
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x25, x26, [sp, 64]
	ldr	w0, [x0, 2200]
	cbz	w0, .L1087
	adrp	x22, .LC67
	mov	w24, 20041
	add	x22, x22, :lo12:.LC67
	mov	w26, 0
	movk	w24, 0x444b, lsl 16
.L1074:
	adrp	x0, .LANCHOR79
	ldrb	w0, [x0, #:lo12:.LANCHOR79]
	cmp	w0, w26
	bhi	.L1084
.L1087:
	mov	w0, 0
	ldr	x27, [sp, 80]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 96
	ret
.L1084:
	adrp	x0, .LANCHOR75
	adrp	x1, .LANCHOR31
	adrp	x21, .LANCHOR74
	ldrb	w2, [x0, #:lo12:.LANCHOR75]
	ldrb	w3, [x1, #:lo12:.LANCHOR31]
	mov	w1, 24
	and	w0, w2, 65535
	cmp	w2, 1
	sub	w1, w1, w3
	ldrh	w3, [x21, #:lo12:.LANCHOR74]
	sdiv	w19, w26, w2
	sub	w1, w1, w3
	lsl	w19, w19, w1
	madd	w19, w23, w0, w19
	and	w19, w19, 65535
	bls	.L1075
	sub	w0, w0, #1
	and	w0, w0, w26
	add	w19, w19, w0
	and	w19, w19, 65535
.L1075:
	adrp	x25, .LANCHOR124
	add	x25, x25, :lo12:.LANCHOR124
	mov	w20, 0
.L1076:
	add	x0, x27, :lo12:.LANCHOR70
	ldr	w1, [x0, 2200]
	cmp	w20, w1
	bcc	.L1083
	add	w26, w26, 1
	and	w26, w26, 65535
	b	.L1074
.L1083:
	add	x0, x0, x20, sxtw 1
	ldrh	w0, [x0, 2204]
	cmp	w0, w19
	bne	.L1077
	mov	w1, w19
	mov	x0, x22
	bl	printf
	ldrb	w0, [x25]
	cbnz	w0, .L1078
	adrp	x0, .LANCHOR80
	ldrb	w0, [x0, #:lo12:.LANCHOR80]
	cbz	w0, .L1079
.L1078:
	adrp	x0, .LANCHOR110
	ldr	x0, [x0, #:lo12:.LANCHOR110]
	ldr	w0, [x0, 156]
	cmp	w0, w24
	beq	.L1080
.L1079:
	ldrh	w0, [x21, #:lo12:.LANCHOR74]
	lsl	w0, w19, w0
	bl	ftl_mask_bad_block
.L1080:
	add	x1, x27, :lo12:.LANCHOR70
	mov	w0, w20
	ldr	w2, [x1, 2200]
.L1081:
	cmp	w0, w2
	bcc	.L1082
	add	x0, x27, :lo12:.LANCHOR70
	sub	w2, w2, #1
	str	w2, [x0, 2200]
.L1077:
	add	w20, w20, 1
	and	w20, w20, 65535
	b	.L1076
.L1082:
	add	w3, w0, 1
	add	x0, x1, x0, sxtw 1
	add	x4, x1, x3, sxtw 1
	ldrh	w4, [x4, 2204]
	strh	w4, [x0, 2204]
	and	w0, w3, 65535
	b	.L1081
	.size	gc_free_bad_sblk, .-gc_free_bad_sblk
	.section	.text.ftl_free_sblk,"ax",@progbits
	.align	2
	.global	ftl_free_sblk
	.type	ftl_free_sblk, %function
ftl_free_sblk:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x23, x24, [sp, 48]
	adrp	x23, .LANCHOR9
	and	x24, x0, 65535
	stp	x19, x20, [sp, 16]
	ldr	x3, [x23, #:lo12:.LANCHOR9]
	lsl	x19, x24, 2
	stp	x21, x22, [sp, 32]
	mov	x21, x24
	add	x20, x3, x19
	ldrb	w0, [x20, 2]
	ubfx	x22, x0, 5, 3
	tbz	x0, 3, .L1094
	adrp	x2, .LANCHOR110
	ldrh	w1, [x3, x19]
	adrp	x8, .LANCHOR125
	ldr	x7, [x2, #:lo12:.LANCHOR110]
	and	w1, w1, 2047
	ldr	w2, [x3, x19]
	ldrh	w8, [x8, #:lo12:.LANCHOR125]
	ldrh	w4, [x7, 74]
	ubfx	x5, x2, 11, 8
	adrp	x2, .LANCHOR10
	add	w4, w1, w4
	ldrh	w2, [x2, #:lo12:.LANCHOR10]
	and	w6, w4, 65535
	ldrh	w4, [x7, 72]
	add	w4, w5, w4
	udiv	w7, w6, w2
	and	w4, w4, 65535
	add	w7, w7, w4
	cmp	w7, w8
	ble	.L1095
	adrp	x4, .LANCHOR101
	adrp	x7, .LANCHOR105
	ldrh	w6, [x4, #:lo12:.LANCHOR101]
	adrp	x4, .LANCHOR91
	ldrh	w7, [x7, #:lo12:.LANCHOR105]
	ldrh	w4, [x4, #:lo12:.LANCHOR91]
	add	w6, w6, 7
	add	w4, w4, w7
	cmp	w6, w4
	blt	.L1096
.L1101:
	mov	w4, 2
	bfi	w0, w4, 3, 2
	b	.L1112
.L1096:
	adrp	x4, .LANCHOR98
	adrp	x7, .LANCHOR103
	ldrh	w6, [x4, #:lo12:.LANCHOR98]
	adrp	x4, .LANCHOR97
	ldrh	w7, [x7, #:lo12:.LANCHOR103]
	ldrh	w4, [x4, #:lo12:.LANCHOR97]
	add	w6, w6, 7
	add	w4, w4, w7
	adrp	x7, .LANCHOR99
	ldrh	w7, [x7, #:lo12:.LANCHOR99]
	add	w4, w4, w7
	cmp	w6, w4
	blt	.L1101
.L1114:
	and	w0, w0, -25
.L1112:
	strb	w0, [x20, 2]
.L1097:
	ldrb	w0, [x20, 2]
	ands	w0, w0, 24
	bne	.L1102
	mul	w2, w5, w2
	ldrh	w0, [x3, x19]
	add	w2, w2, w2, lsl 1
	add	w1, w1, w2, lsr 2
	lsr	w2, w5, 3
	bfi	w0, w1, 0, 11
	strh	w0, [x3, x19]
	ldr	w0, [x3, x19]
	bfi	w0, w2, 11, 8
	str	w0, [x3, x19]
.L1103:
	mov	w0, w21
	bl	zftl_remove_data_node
	ldr	x0, [x23, #:lo12:.LANCHOR9]
	add	w22, w22, 6
	and	w22, w22, 7
	add	x19, x0, x19
	cmp	w22, 4
	ldrb	w0, [x19, 2]
	and	w0, w0, 31
	strb	w0, [x19, 2]
	adrp	x0, .LANCHOR11
	ldr	x0, [x0, #:lo12:.LANCHOR11]
	strh	wzr, [x0, x24, lsl 1]
	bhi	.L1106
	mov	w0, w21
	bl	gc_free_bad_sblk
.L1106:
	ldrb	w0, [x20, 2]
	tbz	x0, 3, .L1107
	adrp	x0, .LANCHOR12
	ldr	x0, [x0, #:lo12:.LANCHOR12]
	ldrh	w1, [x0, 586]
	cmp	w1, w21
	bne	.L1107
	mov	w1, -1
	ldrh	w2, [x0, 590]
	strh	w1, [x0, 586]
	mov	w1, 65535
	cmp	w2, w1
	bne	.L1107
	strh	w21, [x0, 590]
	mov	w1, w21
	ldp	x19, x20, [sp, 16]
	adrp	x0, .LC68
	ldp	x21, x22, [sp, 32]
	add	x0, x0, :lo12:.LC68
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	b	printf
.L1095:
	madd	w4, w2, w4, w6
	adrp	x6, .LANCHOR126
	ldrh	w6, [x6, #:lo12:.LANCHOR126]
	cmp	w4, w6
	ble	.L1097
	adrp	x4, .LANCHOR98
	adrp	x7, .LANCHOR103
	ldrh	w6, [x4, #:lo12:.LANCHOR98]
	adrp	x4, .LANCHOR97
	ldrh	w7, [x7, #:lo12:.LANCHOR103]
	ldrh	w4, [x4, #:lo12:.LANCHOR97]
	add	w4, w4, w7
	adrp	x7, .LANCHOR99
	ldrh	w7, [x7, #:lo12:.LANCHOR99]
	add	w4, w4, w7
	add	w7, w6, 7
	cmp	w7, w4
	bge	.L1114
	adrp	x7, .LANCHOR101
	adrp	x10, .LANCHOR105
	ldrh	w8, [x7, #:lo12:.LANCHOR101]
	adrp	x7, .LANCHOR91
	ldrh	w10, [x10, #:lo12:.LANCHOR105]
	ldrh	w7, [x7, #:lo12:.LANCHOR91]
	add	w8, w8, 7
	add	w7, w7, w10
	cmp	w8, w7
	bge	.L1101
	add	w6, w6, 23
	cmp	w4, w6
	bgt	.L1101
	b	.L1114
.L1102:
	cmp	w0, 16
	bne	.L1103
	sdiv	w2, w1, w2
	ldr	w0, [x3, x19]
	add	w2, w2, w2, lsl 1
	add	w2, w5, w2, lsr 2
.L1113:
	bfi	w0, w2, 11, 8
	asr	w1, w1, 5
	str	w0, [x3, x19]
	bfi	w0, w1, 0, 11
	strh	w0, [x3, x19]
	b	.L1103
.L1094:
	tst	w0, 24
	bne	.L1103
	adrp	x1, .LANCHOR107
	ldrh	w1, [x1, #:lo12:.LANCHOR107]
	cbnz	w1, .L1103
	adrp	x1, .LANCHOR105
	ldrh	w4, [x1, #:lo12:.LANCHOR105]
	cmp	w4, 15
	bhi	.L1103
	adrp	x1, .LANCHOR97
	adrp	x2, .LANCHOR103
	ldrh	w1, [x1, #:lo12:.LANCHOR97]
	ldrh	w2, [x2, #:lo12:.LANCHOR103]
	add	w1, w1, w2
	adrp	x2, .LANCHOR99
	ldrh	w2, [x2, #:lo12:.LANCHOR99]
	add	w1, w1, w2
	adrp	x2, .LANCHOR98
	ldrh	w2, [x2, #:lo12:.LANCHOR98]
	add	w2, w2, 16
	cmp	w1, w2
	ble	.L1103
	adrp	x1, .LANCHOR101
	ldrh	w2, [x1, #:lo12:.LANCHOR101]
	adrp	x1, .LANCHOR91
	ldrh	w1, [x1, #:lo12:.LANCHOR91]
	add	w2, w2, 7
	add	w1, w1, w4
	cmp	w2, w1
	blt	.L1103
	mov	w1, 2
	bfi	w0, w1, 3, 2
	strb	w0, [x20, 2]
	adrp	x0, .LANCHOR10
	ldrh	w1, [x3, x19]
	ldrh	w0, [x0, #:lo12:.LANCHOR10]
	and	w1, w1, 2047
	sdiv	w0, w1, w0
	add	w2, w0, w0, lsl 1
	ldr	w0, [x3, x19]
	ubfx	x4, x0, 11, 8
	add	w2, w4, w2, lsr 2
	b	.L1113
.L1107:
	mov	w0, w21
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	b	zftl_insert_free_list
	.size	ftl_free_sblk, .-ftl_free_sblk
	.section	.text.gc_free_src_blk,"ax",@progbits
	.align	2
	.global	gc_free_src_blk
	.type	gc_free_src_blk, %function
gc_free_src_blk:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x21, x22, [sp, 32]
	adrp	x21, .LANCHOR70
	stp	x23, x24, [sp, 48]
	adrp	x22, .LC69
	adrp	x23, .LANCHOR11
	add	x21, x21, :lo12:.LANCHOR70
	mov	x24, x23
	add	x22, x22, :lo12:.LC69
	stp	x19, x20, [sp, 16]
	mov	w20, 0
	stp	x25, x26, [sp, 64]
.L1116:
	ldrh	w0, [x21, 56]
	cmp	w0, w20
	bhi	.L1130
	strh	wzr, [x21, 56]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
.L1130:
	add	x0, x21, x20, sxtw 1
	ldrh	w25, [x0, 58]
	ldr	x0, [x23, #:lo12:.LANCHOR11]
	mov	x19, x25
	lsl	x26, x25, 1
	ldrh	w2, [x0, x26]
	cbz	w2, .L1117
	mov	w1, w25
	mov	x0, x22
	bl	printf
.L1117:
	ldr	x0, [x24, #:lo12:.LANCHOR11]
	strh	wzr, [x0, x26]
	adrp	x0, .LANCHOR9
	ldr	x0, [x0, #:lo12:.LANCHOR9]
	add	x25, x0, x25, lsl 2
	adrp	x0, .LANCHOR19
	ldr	w0, [x0, #:lo12:.LANCHOR19]
	tbz	x0, 8, .L1118
	ldrb	w2, [x25, 2]
	adrp	x0, .LC70
	mov	w1, w19
	add	x0, x0, :lo12:.LC70
	ubfx	x2, x2, 5, 3
	bl	printf
.L1118:
	ldrb	w0, [x25, 2]
	and	w1, w0, 224
	cmp	w1, 224
	beq	.L1119
	tst	w0, 192
	bne	.L1120
.L1119:
	adrp	x1, .LANCHOR127
	adrp	x0, .LC0
	mov	w2, 1363
	add	x1, x1, :lo12:.LANCHOR127
	add	x0, x0, :lo12:.LC0
	bl	printf
.L1120:
	mov	w0, w19
	bl	ftl_free_sblk
	adrp	x0, .LANCHOR12
	ldr	x0, [x0, #:lo12:.LANCHOR12]
	ldrh	w2, [x0, 124]
	cbz	w2, .L1121
	add	x3, x0, 392
	mov	w1, 0
.L1123:
	ldrh	w4, [x3]
	cmp	w4, w19
	bne	.L1122
	add	x1, x0, x1, sxtw 1
	mov	w3, -1
	sub	w2, w2, #1
	strh	w3, [x1, 392]
	strh	w2, [x0, 124]
.L1121:
	ldrh	w2, [x0, 120]
	cbz	w2, .L1124
	add	x3, x0, 136
	mov	w1, 0
.L1126:
	ldrh	w4, [x3]
	cmp	w4, w19
	bne	.L1125
	add	x1, x0, x1, sxtw 1
	mov	w3, -1
	sub	w2, w2, #1
	strh	w3, [x1, 136]
	strh	w2, [x0, 120]
.L1124:
	ldrh	w2, [x0, 122]
	cbz	w2, .L1127
	add	x3, x0, 264
	mov	w1, 0
.L1129:
	ldrh	w4, [x3]
	cmp	w4, w19
	bne	.L1128
	add	x1, x0, x1, sxtw 1
	mov	w3, -1
	sub	w2, w2, #1
	strh	w3, [x1, 264]
	strh	w2, [x0, 122]
.L1127:
	add	w20, w20, 1
	and	w20, w20, 65535
	b	.L1116
.L1122:
	add	w1, w1, 1
	add	x3, x3, 2
	cmp	w1, 64
	bne	.L1123
	b	.L1121
.L1125:
	add	w1, w1, 1
	add	x3, x3, 2
	cmp	w1, 64
	bne	.L1126
	b	.L1124
.L1128:
	add	w1, w1, 1
	add	x3, x3, 2
	cmp	w1, 64
	bne	.L1129
	b	.L1127
	.size	gc_free_src_blk, .-gc_free_src_blk
	.section	.text.print_ftl_debug_info,"ax",@progbits
	.align	2
	.global	print_ftl_debug_info
	.type	print_ftl_debug_info, %function
print_ftl_debug_info:
	sub	sp, sp, #64
	adrp	x2, .LANCHOR99
	adrp	x8, .LANCHOR128
	stp	x29, x30, [sp, 32]
	add	x29, sp, 32
	ldrh	w7, [x2, #:lo12:.LANCHOR99]
	adrp	x2, .LANCHOR97
	stp	x19, x20, [sp, 48]
	adrp	x19, .LANCHOR110
	adrp	x20, .LANCHOR12
	ldrh	w6, [x2, #:lo12:.LANCHOR97]
	adrp	x2, .LANCHOR107
	ldr	x1, [x19, #:lo12:.LANCHOR110]
	ldrh	w5, [x2, #:lo12:.LANCHOR107]
	adrp	x2, .LANCHOR105
	ldr	x0, [x20, #:lo12:.LANCHOR12]
	ldrh	w4, [x2, #:lo12:.LANCHOR105]
	adrp	x2, .LANCHOR103
	ldr	w8, [x8, #:lo12:.LANCHOR128]
	ldrh	w3, [x2, #:lo12:.LANCHOR103]
	ldrh	w2, [x1, 146]
	ldrh	w1, [x1, 148]
	str	w8, [sp, 24]
	ldr	w8, [x0, 528]
	str	w8, [sp, 16]
	ldr	w0, [x0, 524]
	str	w0, [sp, 8]
	adrp	x0, .LANCHOR91
	ldrh	w0, [x0, #:lo12:.LANCHOR91]
	str	w0, [sp]
	adrp	x0, .LC71
	add	x0, x0, :lo12:.LC71
	bl	printf
	ldr	x0, [x19, #:lo12:.LANCHOR110]
	adrp	x1, .LANCHOR129
	ldrb	w3, [x1, #:lo12:.LANCHOR129]
	ldr	w4, [x0, 8]
	ldr	w5, [x0, 64]
	ldr	w1, [x0, 20]
	ldr	w2, [x0, 28]
	adrp	x0, .LC72
	add	x0, x0, :lo12:.LC72
	bl	printf
	ldr	x0, [x19, #:lo12:.LANCHOR110]
	ldr	w1, [x0, 52]
	ldr	w2, [x0, 60]
	ldr	w3, [x0, 16]
	adrp	x0, .LC73
	add	x0, x0, :lo12:.LC73
	lsr	w3, w3, 11
	bl	printf
	ldr	x0, [x19, #:lo12:.LANCHOR110]
	ldrh	w2, [x0, 98]
	ldrh	w6, [x0, 72]
	ldrh	w5, [x0, 96]
	ldrh	w4, [x0, 92]
	ldrh	w3, [x0, 88]
	ldrh	w1, [x0, 74]
	str	w2, [sp, 16]
	ldrh	w2, [x0, 94]
	str	w2, [sp, 8]
	ldrh	w2, [x0, 90]
	str	w2, [sp]
	ldp	w7, w2, [x0, 80]
	adrp	x0, .LC74
	add	x0, x0, :lo12:.LC74
	bl	printf
	adrp	x0, .LANCHOR86
	ldrh	w5, [x0, #:lo12:.LANCHOR86]
	adrp	x0, .LANCHOR93
	ldrh	w4, [x0, #:lo12:.LANCHOR93]
	adrp	x0, .LANCHOR69
	ldrh	w3, [x0, #:lo12:.LANCHOR69]
	adrp	x0, .LANCHOR102
	ldrh	w2, [x0, #:lo12:.LANCHOR102]
	adrp	x0, .LANCHOR100
	ldrh	w1, [x0, #:lo12:.LANCHOR100]
	adrp	x0, .LC75
	add	x0, x0, :lo12:.LC75
	bl	printf
	ldr	x0, [x20, #:lo12:.LANCHOR12]
	ldr	x1, [x19, #:lo12:.LANCHOR110]
	ldp	x29, x30, [sp, 32]
	ldrh	w4, [x0, 590]
	ldrh	w6, [x1, 150]
	ldrh	w3, [x0, 588]
	ldrh	w2, [x0, 586]
	ldp	x19, x20, [sp, 48]
	add	sp, sp, 64
	ldr	w5, [x1, 156]
	ldrh	w1, [x0, 584]
	adrp	x0, .LC76
	add	x0, x0, :lo12:.LC76
	b	printf
	.size	print_ftl_debug_info, .-print_ftl_debug_info
	.section	.text.ftl_write_buf,"ax",@progbits
	.align	2
	.global	ftl_write_buf
	.type	ftl_write_buf, %function
ftl_write_buf:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	str	x21, [sp, 32]
	cbnz	x0, .L1156
	adrp	x1, .LANCHOR130
	add	x1, x1, :lo12:.LANCHOR130
	mov	w2, 808
	adrp	x0, .LC0
	add	x0, x0, :lo12:.LC0
	bl	printf
	bl	print_ftl_debug_info
	mov	w0, -1
.L1155:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
.L1159:
	mov	x1, x19
	adrp	x0, .LANCHOR65
	add	x0, x0, :lo12:.LANCHOR65
	bl	buf_add_tail
	adrp	x1, .LANCHOR110
	ldrb	w3, [x19, 56]
	ldrb	w0, [x21, #:lo12:.LANCHOR66]
	ldr	x1, [x1, #:lo12:.LANCHOR110]
	add	w0, w0, 1
	and	w0, w0, 255
	strb	w0, [x21, #:lo12:.LANCHOR66]
	ldr	w2, [x1, 16]
	add	w2, w2, w3
	str	w2, [x1, 16]
	ldr	w2, [x1, 32]
	add	w2, w2, 1
	str	w2, [x1, 32]
	b	.L1155
.L1156:
	mov	x19, x0
	adrp	x0, .LANCHOR131
	mov	x20, x0
	ldrb	w1, [x0, #:lo12:.LANCHOR131]
	ldrb	w2, [x19, 56]
	cmp	w2, w1
	bls	.L1161
	adrp	x1, .LANCHOR130
	adrp	x0, .LC0
	mov	w2, 815
	add	x1, x1, :lo12:.LANCHOR130
	add	x0, x0, :lo12:.LC0
	bl	printf
.L1161:
	ldrb	w0, [x19, 56]
	adrp	x21, .LANCHOR66
	cbz	w0, .L1158
	ldrb	w1, [x20, #:lo12:.LANCHOR131]
	cmp	w1, w0
	bcs	.L1159
.L1158:
	mov	x0, x19
	bl	zbuf_free
	ldrb	w0, [x21, #:lo12:.LANCHOR66]
	b	.L1155
	.size	ftl_write_buf, .-ftl_write_buf
	.section	.text.ftl_write_completed,"ax",@progbits
	.align	2
	.global	ftl_write_completed
	.type	ftl_write_completed, %function
ftl_write_completed:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x21, x22, [sp, 32]
	adrp	x21, .LANCHOR55
	stp	x19, x20, [sp, 16]
	add	x22, x21, :lo12:.LANCHOR55
	stp	x23, x24, [sp, 48]
	adrp	x20, .LANCHOR64
	mov	w23, 20041
	add	x20, x20, :lo12:.LANCHOR64
	str	x25, [sp, 64]
	movk	w23, 0x444b, lsl 16
	mov	w25, 0
.L1167:
	ldrb	w0, [x20]
	cmp	w0, 255
	bne	.L1178
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldr	x25, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
.L1178:
	add	x1, x21, :lo12:.LANCHOR55
	lsl	x2, x0, 6
	add	x24, x1, x2
	ubfiz	x19, x0, 6, 8
	add	x19, x1, x19
	ldrb	w1, [x1, x2]
	strb	w1, [x20]
	ldr	w1, [x24, 52]
	cmn	w1, #1
	bne	.L1168
	adrp	x1, .LANCHOR124
	ldrb	w1, [x1, #:lo12:.LANCHOR124]
	cbnz	w1, .L1169
	adrp	x1, .LANCHOR80
	ldrb	w1, [x1, #:lo12:.LANCHOR80]
	cbz	w1, .L1170
.L1169:
	adrp	x1, .LANCHOR110
	ldr	x1, [x1, #:lo12:.LANCHOR110]
	ldr	w1, [x1, 156]
	cmp	w1, w23
	beq	.L1171
.L1170:
	add	x1, x22, x0, lsl 6
	mov	w2, 24
	mov	w5, 65535
	ldr	w3, [x1, 40]
	adrp	x1, .LANCHOR74
	ldrh	w4, [x1, #:lo12:.LANCHOR74]
	adrp	x1, .LANCHOR31
	ldrb	w1, [x1, #:lo12:.LANCHOR31]
	sub	w1, w2, w1
	sub	w2, w1, w4
	mov	w1, 1
	lsr	w4, w3, w4
	lsl	w1, w1, w2
	adrp	x2, .LANCHOR75
	sub	w1, w1, #1
	ldrb	w2, [x2, #:lo12:.LANCHOR75]
	and	w1, w1, w4
	udiv	w1, w1, w2
	adrp	x2, .LANCHOR12
	mov	x24, x2
	ldr	x4, [x2, #:lo12:.LANCHOR12]
	and	w25, w1, 65535
	and	w1, w1, w5
	ldr	w6, [x4, 560]
	cmp	w6, w5
	bne	.L1172
	str	w1, [x4, 560]
	str	w3, [x4, 564]
.L1172:
	add	x0, x22, x0, lsl 6
	ldr	w2, [x0, 36]
	adrp	x0, .LC77
	add	x0, x0, :lo12:.LC77
	bl	printf
	ldr	x0, [x24, #:lo12:.LANCHOR12]
	ldr	w1, [x0, 556]
	add	w1, w1, 1
	str	w1, [x0, 556]
	ldrh	w1, [x0, 16]
	cmp	w1, w25
	bne	.L1173
	strh	wzr, [x0, 22]
.L1171:
	mov	x0, x19
	mov	w25, 1
	bl	ftl_write_buf
	b	.L1167
.L1173:
	ldrh	w1, [x0, 48]
	cmp	w1, w25
	bne	.L1171
	strh	wzr, [x0, 54]
	b	.L1171
.L1168:
	cbz	w25, .L1176
	ldp	w1, w2, [x24, 36]
	adrp	x0, .LC78
	add	x0, x0, :lo12:.LC78
	bl	printf
	mov	x0, x19
	bl	ftl_write_buf
	b	.L1167
.L1176:
	ldrh	w2, [x24, 48]
	ldr	w0, [x24, 36]
	ldr	w1, [x24, 44]
	bl	lpa_hash_update_ppa
	ldrb	w0, [x24, 2]
	tbz	x0, 2, .L1177
	and	w0, w0, -3
	strb	w0, [x24, 2]
	b	.L1167
.L1177:
	mov	x0, x19
	bl	zbuf_free
	b	.L1167
	.size	ftl_write_completed, .-ftl_write_completed
	.section	.text.zftl_add_read_buf,"ax",@progbits
	.align	2
	.global	zftl_add_read_buf
	.type	zftl_add_read_buf, %function
zftl_add_read_buf:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	cbnz	x0, .L1184
	mov	w2, 1148
	adrp	x1, .LANCHOR132
	adrp	x0, .LC0
	add	x1, x1, :lo12:.LANCHOR132
	add	x0, x0, :lo12:.LC0
	bl	printf
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	b	print_ftl_debug_info
.L1184:
	ldrb	w1, [x0, 56]
	mov	x19, x0
	adrp	x0, .LANCHOR131
	ldrb	w0, [x0, #:lo12:.LANCHOR131]
	cmp	w1, w0
	bls	.L1186
	adrp	x1, .LANCHOR132
	adrp	x0, .LC0
	mov	w2, 1155
	add	x1, x1, :lo12:.LANCHOR132
	add	x0, x0, :lo12:.LC0
	bl	printf
.L1186:
	mov	x1, x19
	adrp	x0, .LANCHOR133
	add	x0, x0, :lo12:.LANCHOR133
	bl	buf_add_tail
	adrp	x1, .LANCHOR134
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ldrb	w0, [x1, #:lo12:.LANCHOR134]
	add	w0, w0, 1
	strb	w0, [x1, #:lo12:.LANCHOR134]
	ret
	.size	zftl_add_read_buf, .-zftl_add_read_buf
	.section	.text.sblk_init,"ax",@progbits
	.align	2
	.global	sblk_init
	.type	sblk_init, %function
sblk_init:
	adrp	x1, .LANCHOR59
	mov	w0, -1
	strb	w0, [x1, #:lo12:.LANCHOR59]
	adrp	x1, .LANCHOR64
	strb	w0, [x1, #:lo12:.LANCHOR64]
	adrp	x1, .LANCHOR62
	strb	w0, [x1, #:lo12:.LANCHOR62]
	adrp	x1, .LANCHOR63
	strb	w0, [x1, #:lo12:.LANCHOR63]
	mov	w0, 0
	ret
	.size	sblk_init, .-sblk_init
	.section	.text.dump_sblk_queue,"ax",@progbits
	.align	2
	.global	dump_sblk_queue
	.type	dump_sblk_queue, %function
dump_sblk_queue:
	stp	x29, x30, [sp, -48]!
	adrp	x0, .LC79
	add	x0, x0, :lo12:.LC79
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	adrp	x19, .LANCHOR59
	str	x21, [sp, 32]
	ldrb	w1, [x19, #:lo12:.LANCHOR59]
	bl	printf
	ldrb	w19, [x19, #:lo12:.LANCHOR59]
	cmp	w19, 255
	beq	.L1190
	adrp	x1, .LANCHOR55
	ubfiz	x19, x19, 6, 8
	add	x1, x1, :lo12:.LANCHOR55
	adrp	x21, .LC80
	add	x19, x1, x19
	add	x21, x21, :lo12:.LC80
	mov	x20, x1
.L1192:
	ldrb	w2, [x19, 58]
	mov	x0, x21
	ldrb	w1, [x19, 1]
	ldr	w3, [x19, 40]
	bl	printf
	ldrb	w19, [x19]
	cmp	w19, 255
	beq	.L1190
	ubfiz	x19, x19, 6, 8
	add	x19, x20, x19
	b	.L1192
.L1190:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	dump_sblk_queue, .-dump_sblk_queue
	.section	.text.queue_lun_state,"ax",@progbits
	.align	2
	.global	queue_lun_state
	.type	queue_lun_state, %function
queue_lun_state:
	adrp	x2, .LANCHOR59
	ldrb	w2, [x2, #:lo12:.LANCHOR59]
	cmp	w2, 255
	beq	.L1208
	adrp	x3, .LANCHOR31
	mov	w8, 24
	adrp	x10, .LANCHOR55
	add	x10, x10, :lo12:.LANCHOR55
	ldrb	w4, [x3, #:lo12:.LANCHOR31]
	mov	w3, 1
	adrp	x13, .L1204
	mov	x15, x10
	sub	w8, w8, w4
	add	x13, x13, :lo12:.L1204
	lsl	w4, w3, w4
	sub	w4, w4, #1
	and	w6, w4, 65535
	adrp	x4, .LANCHOR74
	asr	w11, w0, w8
	and	w11, w11, w6
	ldrh	w12, [x4, #:lo12:.LANCHOR74]
	sub	w4, w8, w12
	lsl	w3, w3, w4
	sub	w3, w3, #1
	and	w7, w3, 65535
	adrp	x3, .LANCHOR75
	ldrb	w5, [x3, #:lo12:.LANCHOR75]
	asr	w3, w0, w12
	sub	w5, w5, #1
	and	w5, w5, 65535
	and	w3, w3, w5
	and	w3, w3, w7
.L1207:
	add	x14, x10, x2, lsl 6
	ldr	w4, [x14, 40]
	lsr	w0, w4, w8
	and	w0, w6, w0
	cmp	w11, w0
	bne	.L1202
	lsr	w4, w4, w12
	and	w4, w5, w4
	and	w4, w7, w4
	ldrb	w0, [x14, 58]
	cmp	w3, w4
	bne	.L1203
	cmp	w1, 1
	bne	.L1200
	cmp	w0, 7
	ccmp	w0, 9, 4, ne
	beq	.L1202
	ret
.L1203:
	cmp	w1, 3
	bhi	.L1202
	ldrb	w4, [x13,w1,uxtw]
	adr	x14, .Lrtx1204
	add	x4, x14, w4, sxtb #2
	br	x4
.Lrtx1204:
	.section	.rodata.queue_lun_state,"a",@progbits
	.align	0
	.align	2
.L1204:
	.byte	(.L1200 - .Lrtx1204) / 4
	.byte	(.L1205 - .Lrtx1204) / 4
	.byte	(.L1206 - .Lrtx1204) / 4
	.byte	(.L1200 - .Lrtx1204) / 4
	.section	.text.queue_lun_state
.L1205:
	cmp	w0, 7
	ccmp	w0, 9, 4, ne
	beq	.L1202
	ret
.L1206:
	cmp	w0, 11
	bne	.L1200
.L1202:
	lsl	x2, x2, 6
	ldrb	w2, [x15, x2]
	cmp	w2, 255
	bne	.L1207
.L1208:
	mov	w0, 0
.L1200:
	ret
	.size	queue_lun_state, .-queue_lun_state
	.section	.text.queue_remove_completed_req,"ax",@progbits
	.align	2
	.global	queue_remove_completed_req
	.type	queue_remove_completed_req, %function
queue_remove_completed_req:
	adrp	x4, .LANCHOR64
	adrp	x8, .LANCHOR63
	adrp	x1, .LANCHOR59
	adrp	x7, .LANCHOR62
	adrp	x3, .LANCHOR55
	ldrb	w14, [x4, #:lo12:.LANCHOR64]
	add	x5, x3, :lo12:.LANCHOR55
	ldrb	w2, [x1, #:lo12:.LANCHOR59]
	ldrb	w12, [x8, #:lo12:.LANCHOR63]
	mov	x11, x5
	ldrb	w13, [x7, #:lo12:.LANCHOR62]
	add	x16, x8, :lo12:.LANCHOR63
	add	x7, x7, :lo12:.LANCHOR62
	add	x10, x4, :lo12:.LANCHOR64
	mov	w6, 0
	mov	w15, -1
.L1211:
	cmp	w2, 255
	beq	.L1212
	sbfiz	x8, x2, 6, 32
	sxtw	x0, w2
	add	x4, x5, x8
	ldrb	w4, [x4, 58]
	sub	w4, w4, #12
	and	w4, w4, 255
	cmp	w4, 1
	bls	.L1213
	cbz	w6, .L1210
	strb	w2, [x1, #:lo12:.LANCHOR59]
	ret
.L1213:
	lsl	x6, x0, 6
	ldrb	w2, [x5, x8]
	add	x4, x5, x6
	strb	w15, [x5, x6]
	ldrb	w6, [x4, 59]
	cmp	w6, 1
	bne	.L1216
	ldrh	w4, [x4, 50]
	cbnz	w4, .L1224
	mov	w4, w14
	mov	x6, x10
.L1217:
	cmp	w4, 255
	bne	.L1222
	add	x3, x3, :lo12:.LANCHOR55
	strb	w2, [x1, #:lo12:.LANCHOR59]
	add	x0, x3, x0, lsl 6
	ldrb	w0, [x0, 1]
	strb	w0, [x6]
	ret
.L1216:
	cbnz	w6, .L1218
	ldr	w4, [x4, 36]
	cmn	w4, #1
	beq	.L1218
	mov	w4, w13
	mov	x6, x7
	b	.L1217
.L1224:
	mov	w4, w12
	mov	x6, x16
	b	.L1217
.L1222:
	mov	w6, w4
	sbfiz	x4, x4, 6, 32
	ldrb	w4, [x11, x4]
	cmp	w4, 255
	bne	.L1222
	add	x0, x11, x0, lsl 6
	sbfiz	x6, x6, 6, 32
	ldrb	w0, [x0, 1]
	strb	w0, [x11, x6]
.L1218:
	mov	w6, 1
	b	.L1211
.L1212:
	cbz	w6, .L1210
	mov	w0, -1
	strb	w0, [x1, #:lo12:.LANCHOR59]
.L1210:
	ret
	.size	queue_remove_completed_req, .-queue_remove_completed_req
	.section	.text.pm_select_ram_region,"ax",@progbits
	.align	2
	.global	pm_select_ram_region
	.type	pm_select_ram_region, %function
pm_select_ram_region:
	stp	x29, x30, [sp, -32]!
	adrp	x0, .LANCHOR135
	add	x0, x0, :lo12:.LANCHOR135
	mov	x1, 0
	add	x29, sp, 0
	mov	w2, 65535
	str	x19, [sp, 16]
.L1236:
	lsl	x3, x1, 4
	and	w19, w1, 65535
	ldrh	w3, [x3, x0]
	cmp	w3, w2
	beq	.L1235
	add	x1, x1, 1
	cmp	x1, 32
	bne	.L1236
	add	x0, x0, 2
	mov	w19, w1
	mov	x2, x0
	mov	w4, 32768
	mov	w1, 0
.L1238:
	ldrh	w3, [x2]
	tbnz	x3, 15, .L1237
	cmp	w3, w4
	bcs	.L1237
	mov	w4, w3
	mov	w19, w1
.L1237:
	add	w1, w1, 1
	add	x2, x2, 16
	and	w1, w1, 65535
	cmp	w1, 32
	bne	.L1238
	cmp	w19, 32
	bne	.L1235
	adrp	x1, .LANCHOR136
	mov	w2, -1
	ldrb	w3, [x1, #:lo12:.LANCHOR136]
	mov	w1, 0
.L1240:
	ldrh	w5, [x0]
	cmp	w5, w2
	bcs	.L1239
	ldrh	w4, [x0, -2]
	cmp	w4, w3
	csel	w2, w2, w5, eq
	csel	w19, w19, w1, eq
.L1239:
	add	w1, w1, 1
	add	x0, x0, 16
	and	w1, w1, 65535
	cmp	w1, 32
	bne	.L1240
	cmp	w19, 32
	bne	.L1235
	adrp	x1, .LANCHOR137
	adrp	x0, .LC0
	mov	w2, 377
	add	x1, x1, :lo12:.LANCHOR137
	add	x0, x0, :lo12:.LC0
	bl	printf
.L1235:
	mov	w0, w19
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	pm_select_ram_region, .-pm_select_ram_region
	.section	.text.idb_init,"ax",@progbits
	.align	2
	.global	idb_init
	.type	idb_init, %function
idb_init:
	adrp	x0, .LANCHOR138
	str	xzr, [x0, #:lo12:.LANCHOR138]
	adrp	x0, .LANCHOR139
	str	wzr, [x0, #:lo12:.LANCHOR139]
	adrp	x0, .LANCHOR140
	strb	wzr, [x0, #:lo12:.LANCHOR140]
	adrp	x0, .LANCHOR141
	str	xzr, [x0, #:lo12:.LANCHOR141]
	mov	w0, 0
	ret
	.size	idb_init, .-idb_init
	.section	.text.ftl_memset,"ax",@progbits
	.align	2
	.global	ftl_memset
	.type	ftl_memset, %function
ftl_memset:
	uxtw	x2, w2
	b	memset
	.size	ftl_memset, .-ftl_memset
	.section	.text.flash_lsb_page_tbl_build,"ax",@progbits
	.align	2
	.global	flash_lsb_page_tbl_build
	.type	flash_lsb_page_tbl_build, %function
flash_lsb_page_tbl_build:
	stp	x29, x30, [sp, -48]!
	adrp	x1, .LANCHOR21
	add	x29, sp, 0
	ldr	x1, [x1, #:lo12:.LANCHOR21]
	stp	x19, x20, [sp, 16]
	mov	w20, 1024
	str	x21, [sp, 32]
	adrp	x19, .LANCHOR3
	ldrb	w1, [x1, 12]
	sdiv	w20, w20, w1
	cbnz	w0, .L1248
	add	x1, x19, :lo12:.LANCHOR3
	mov	x0, 0
.L1249:
	strh	w0, [x1, x0, lsl 1]
	add	x0, x0, 1
	cmp	x0, 512
	bne	.L1249
.L1255:
	adrp	x21, .LANCHOR142
	add	x21, x21, :lo12:.LANCHOR142
	mov	w2, 2048
	mov	w1, 255
	mov	x0, x21
	add	x19, x19, :lo12:.LANCHOR3
	bl	ftl_memset
	mov	x0, 0
.L1250:
	ldrh	w1, [x19, x0, lsl 1]
	add	x0, x0, 1
	cmp	w20, w0, uxth
	strh	w1, [x21, w1, sxtw 1]
	bhi	.L1250
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
.L1248:
	cmp	w0, 1
	bne	.L1251
	add	x3, x19, :lo12:.LANCHOR3
	mov	x1, 0
.L1254:
	and	w0, w1, 65535
	cmp	x1, 3
	bls	.L1252
	ubfiz	w2, w0, 1, 15
	and	w0, w0, 1
	add	w0, w0, 2
	sub	w0, w2, w0
	and	w0, w0, 65535
.L1252:
	strh	w0, [x3, x1, lsl 1]
	add	x1, x1, 1
	cmp	x1, 512
	bne	.L1254
	b	.L1255
.L1251:
	cmp	w0, 2
	bne	.L1256
	add	x3, x19, :lo12:.LANCHOR3
	mov	w1, 65535
	mov	x0, 0
.L1258:
	cmp	x0, 2
	and	w2, w0, 65535
	csel	w2, w2, w1, cc
	strh	w2, [x3, x0, lsl 1]
	add	w1, w1, 2
	add	x0, x0, 1
	and	w1, w1, 65535
	cmp	x0, 512
	bne	.L1258
	b	.L1255
.L1256:
	cmp	w0, 3
	bne	.L1259
	add	x3, x19, :lo12:.LANCHOR3
	mov	x1, 0
.L1262:
	and	w0, w1, 65535
	cmp	x1, 5
	bls	.L1260
	ubfiz	w2, w0, 1, 15
	and	w0, w0, 1
	add	w0, w0, 4
	sub	w0, w2, w0
	and	w0, w0, 65535
.L1260:
	strh	w0, [x3, x1, lsl 1]
	add	x1, x1, 1
	cmp	x1, 512
	bne	.L1262
	b	.L1255
.L1259:
	cmp	w0, 4
	bne	.L1263
	add	x1, x19, :lo12:.LANCHOR3
	mov	w2, 1
	add	x1, x1, 16
	strh	wzr, [x19, #:lo12:.LANCHOR3]
	strh	w0, [x1, -8]
	mov	w0, 5
	strh	w2, [x1, -14]
	mov	w2, 2
	strh	w0, [x1, -6]
	mov	w0, 7
	strh	w2, [x1, -12]
	mov	w2, 3
	strh	w0, [x1, -4]
	mov	w0, 8
	strh	w2, [x1, -10]
	strh	w0, [x1, -2]
	mov	w0, 8
.L1265:
	and	w3, w0, 1
	ubfiz	w2, w0, 1, 15
	add	w3, w3, 6
	add	w0, w0, 1
	sub	w2, w2, w3
	strh	w2, [x1], 2
	and	w0, w0, 65535
	cmp	w0, 512
	bne	.L1265
	b	.L1255
.L1263:
	cmp	w0, 5
	bne	.L1266
	add	x1, x19, :lo12:.LANCHOR3
	mov	x0, 0
.L1267:
	strh	w0, [x1, x0, lsl 1]
	add	x0, x0, 1
	cmp	x0, 16
	bne	.L1267
	add	x1, x1, 32
.L1268:
	strh	w0, [x1], 2
	add	w0, w0, 2
	and	w0, w0, 65535
	cmp	w0, 1008
	bne	.L1268
	b	.L1255
.L1266:
	cmp	w0, 8
	bne	.L1269
	add	x1, x19, :lo12:.LANCHOR3
	mov	x0, 0
.L1270:
	strh	w0, [x0, x1]
	add	x0, x0, 2
	cmp	x0, 1024
	bne	.L1270
	b	.L1255
.L1269:
	cmp	w0, 9
	bne	.L1271
	add	x0, x19, :lo12:.LANCHOR3
	mov	w1, 1
	add	x0, x0, 6
	strh	wzr, [x19, #:lo12:.LANCHOR3]
	strh	w1, [x0, -4]
	mov	w1, 2
	strh	w1, [x0, -2]
	mov	w1, 3
.L1272:
	strh	w1, [x0], 2
	add	w1, w1, 2
	and	w1, w1, 65535
	cmp	w1, 1021
	bne	.L1272
	b	.L1255
.L1271:
	cmp	w0, 10
	bne	.L1273
	add	x1, x19, :lo12:.LANCHOR3
	mov	x0, 0
.L1274:
	strh	w0, [x1, x0, lsl 1]
	add	x0, x0, 1
	cmp	x0, 63
	bne	.L1274
	add	x1, x1, 126
.L1275:
	strh	w0, [x1], 2
	add	w0, w0, 2
	and	w0, w0, 65535
	cmp	w0, 961
	bne	.L1275
	b	.L1255
.L1273:
	cmp	w0, 11
	bne	.L1276
	add	x1, x19, :lo12:.LANCHOR3
	mov	x0, 0
.L1277:
	strh	w0, [x1, x0, lsl 1]
	add	x0, x0, 1
	cmp	x0, 8
	bne	.L1277
	add	x1, x1, 16
.L1279:
	and	w3, w0, 1
	ubfiz	w2, w0, 1, 15
	add	w3, w3, 6
	add	w0, w0, 1
	sub	w2, w2, w3
	strh	w2, [x1], 2
	and	w0, w0, 65535
	cmp	w0, 512
	bne	.L1279
	b	.L1255
.L1276:
	cmp	w0, 13
	bne	.L1255
	add	x2, x19, :lo12:.LANCHOR3
	mov	x1, 0
	mov	w0, 0
.L1280:
	strh	w0, [x1, x2]
	add	w0, w0, 3
	and	w0, w0, 65535
	add	x1, x1, 2
	cmp	w0, 1536
	bne	.L1280
	b	.L1255
	.size	flash_lsb_page_tbl_build, .-flash_lsb_page_tbl_build
	.section	.text.flash_die_info_init,"ax",@progbits
	.align	2
	.global	flash_die_info_init
	.type	flash_die_info_init, %function
flash_die_info_init:
	stp	x29, x30, [sp, -112]!
	adrp	x0, .LANCHOR19
	add	x29, sp, 0
	ldr	w0, [x0, #:lo12:.LANCHOR19]
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	tbz	x0, 12, .L1303
	adrp	x1, .LANCHOR143
	adrp	x0, .LC1
	add	x1, x1, :lo12:.LANCHOR143
	add	x0, x0, :lo12:.LC1
	bl	printf
.L1303:
	adrp	x19, .LANCHOR32
	add	x23, x19, :lo12:.LANCHOR32
	adrp	x25, .LANCHOR2
	adrp	x20, .LANCHOR23
	mov	w2, 8
	adrp	x22, .LANCHOR29
	ldrh	w0, [x23, 26]
	adrp	x21, .LANCHOR145
	ldrb	w1, [x23, 12]
	adrp	x26, .LANCHOR33
	strh	w0, [x25, #:lo12:.LANCHOR2]
	add	x26, x26, :lo12:.LANCHOR33
	ldrh	w0, [x23, 10]
	add	x28, x23, 1
	strb	wzr, [x20, #:lo12:.LANCHOR23]
	adrp	x24, .LANCHOR47
	mov	x27, 0
	sdiv	w0, w0, w1
	adrp	x1, .LANCHOR144
	strh	w0, [x1, #:lo12:.LANCHOR144]
	mov	w1, 0
	add	x0, x22, :lo12:.LANCHOR29
	bl	ftl_memset
	mov	w2, 32
	mov	w1, 0
	add	x0, x21, :lo12:.LANCHOR145
	bl	ftl_memset
	add	x0, x24, :lo12:.LANCHOR47
	str	x0, [x29, 104]
.L1305:
	mov	w0, 2
	ldrb	w2, [x23]
	strb	w0, [x27, x26]
	ldr	x0, [x29, 104]
	add	x1, x0, x27, lsl 3
	mov	x0, x28
	bl	flash_mem_cmp8
	cbnz	w0, .L1304
	ldrb	w2, [x20, #:lo12:.LANCHOR23]
	add	x1, x21, :lo12:.LANCHOR145
	add	w0, w2, 1
	strb	w0, [x20, #:lo12:.LANCHOR23]
	and	w0, w27, 255
	str	wzr, [x1, x2, lsl 2]
	add	x1, x22, :lo12:.LANCHOR29
	strb	w0, [x1, x2]
	bl	zftl_flash_enter_slc_mode
.L1304:
	add	x27, x27, 1
	cmp	x27, 4
	bne	.L1305
	add	x0, x19, :lo12:.LANCHOR32
	ldrb	w1, [x0, 8]
	cmp	w1, 2
	beq	.L1306
.L1310:
	add	x19, x19, :lo12:.LANCHOR32
	ldrb	w0, [x20, #:lo12:.LANCHOR23]
	ldp	x21, x22, [sp, 32]
	ldrb	w1, [x19, 13]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	mul	w0, w0, w1
	ldrh	w1, [x19, 14]
	ldp	x27, x28, [sp, 80]
	ldp	x19, x20, [sp, 16]
	mul	w0, w0, w1
	adrp	x1, .LANCHOR146
	strh	w0, [x1, #:lo12:.LANCHOR146]
	ldp	x29, x30, [sp], 112
	ret
.L1306:
	ldrh	w1, [x25, #:lo12:.LANCHOR2]
	add	x24, x24, :lo12:.LANCHOR47
	ldrb	w8, [x0, 13]
	add	x7, x0, 1
	ldrb	w12, [x19, #:lo12:.LANCHOR32]
	add	x11, x20, :lo12:.LANCHOR23
	ldrb	w13, [x0, 23]
	add	x21, x21, :lo12:.LANCHOR145
	add	x22, x22, :lo12:.LANCHOR29
	mov	x10, 0
	mul	w8, w8, w1
	ldrh	w1, [x0, 14]
	and	w1, w1, 65280
	mul	w8, w8, w1
	lsl	w14, w8, 1
.L1309:
	mov	w2, w12
	add	x1, x24, x10, lsl 3
	mov	x0, x7
	bl	flash_mem_cmp8
	cbnz	w0, .L1307
	ldrb	w1, [x11]
	cmp	w13, 0
	csel	w2, w8, w14, eq
	add	w0, w1, 1
	strb	w0, [x11]
	str	w2, [x21, x1, lsl 2]
	strb	w10, [x22, x1]
.L1307:
	add	x10, x10, 1
	cmp	x10, 4
	bne	.L1309
	b	.L1310
	.size	flash_die_info_init, .-flash_die_info_init
	.section	.text.lpa_hash_init,"ax",@progbits
	.align	2
	.global	lpa_hash_init
	.type	lpa_hash_init, %function
lpa_hash_init:
	stp	x29, x30, [sp, -16]!
	mov	w2, 512
	mov	w1, 255
	adrp	x0, .LANCHOR116
	add	x29, sp, 0
	add	x0, x0, :lo12:.LANCHOR116
	bl	ftl_memset
	adrp	x0, .LANCHOR94
	mov	w1, 255
	ldp	x29, x30, [sp], 16
	ldrh	w2, [x0, #:lo12:.LANCHOR94]
	adrp	x0, .LANCHOR79
	ldrb	w0, [x0, #:lo12:.LANCHOR79]
	mul	w2, w2, w0
	adrp	x0, .LANCHOR118
	ldr	x0, [x0, #:lo12:.LANCHOR118]
	lsl	w2, w2, 2
	b	ftl_memset
	.size	lpa_hash_init, .-lpa_hash_init
	.section	.text.lpa_rebuild_hash,"ax",@progbits
	.align	2
	.global	lpa_rebuild_hash
	.type	lpa_rebuild_hash, %function
lpa_rebuild_hash:
	stp	x29, x30, [sp, -48]!
	adrp	x0, .LANCHOR19
	add	x29, sp, 0
	ldr	w0, [x0, #:lo12:.LANCHOR19]
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	tbz	x0, 12, .L1323
	adrp	x1, .LANCHOR147
	adrp	x0, .LC81
	mov	w3, 0
	mov	w2, 239
	add	x1, x1, :lo12:.LANCHOR147
	add	x0, x0, :lo12:.LC81
	bl	printf
.L1323:
	adrp	x20, .LANCHOR94
	adrp	x22, .LANCHOR79
	adrp	x19, .LANCHOR116
	add	x19, x19, :lo12:.LANCHOR116
	mov	w2, 512
	mov	w1, 255
	mov	x0, x19
	bl	ftl_memset
	ldrh	w2, [x20, #:lo12:.LANCHOR94]
	adrp	x21, .LANCHOR118
	ldrb	w0, [x22, #:lo12:.LANCHOR79]
	mov	w1, 255
	add	x20, x20, :lo12:.LANCHOR94
	mul	w2, w2, w0
	ldr	x0, [x21, #:lo12:.LANCHOR118]
	lsl	w2, w2, 2
	bl	ftl_memset
	adrp	x0, .LANCHOR117
	ldrb	w3, [x22, #:lo12:.LANCHOR79]
	ldr	x5, [x21, #:lo12:.LANCHOR118]
	mov	w1, 0
	ldr	x4, [x0, #:lo12:.LANCHOR117]
.L1324:
	ldrh	w0, [x20]
	mul	w0, w0, w3
	cmp	w1, w0, lsl 1
	blt	.L1326
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
.L1326:
	uxtw	x2, w1
	ldr	w0, [x4, x2, lsl 2]
	cmn	w0, #1
	beq	.L1325
	and	x0, x0, 255
	ldrh	w6, [x19, x0, lsl 1]
	strh	w1, [x19, x0, lsl 1]
	strh	w6, [x5, x2, lsl 1]
.L1325:
	add	w1, w1, 1
	and	w1, w1, 65535
	b	.L1324
	.size	lpa_rebuild_hash, .-lpa_rebuild_hash
	.section	.text.zftl_read_flash_info,"ax",@progbits
	.align	2
	.global	zftl_read_flash_info
	.type	zftl_read_flash_info, %function
zftl_read_flash_info:
	stp	x29, x30, [sp, -32]!
	mov	w2, 11
	mov	w1, 0
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	bl	ftl_memset
	adrp	x1, .LANCHOR32
	add	x1, x1, :lo12:.LANCHOR32
	adrp	x0, .LANCHOR2
	adrp	x3, .LANCHOR67
	strb	wzr, [x19, 10]
	mov	w4, 1
	ldrb	w2, [x1, 9]
	ldrh	w0, [x0, #:lo12:.LANCHOR2]
	mul	w0, w2, w0
	strb	w0, [x19, 4]
	ubfx	x0, x0, 8, 8
	strb	w0, [x19, 5]
	adrp	x0, .LANCHOR49
	ldrb	w0, [x0, #:lo12:.LANCHOR49]
	strb	w0, [x19, 7]
	add	x0, x3, :lo12:.LANCHOR67
	ldrb	w3, [x3, #:lo12:.LANCHOR67]
	strb	w3, [x19]
	ldrb	w3, [x0, 1]
	strb	w3, [x19, 1]
	ldrb	w3, [x0, 2]
	ldrb	w0, [x0, 3]
	strb	w3, [x19, 2]
	strb	w0, [x19, 3]
	mov	w0, 32
	strb	w2, [x19, 6]
	adrp	x2, .LANCHOR29
	strb	w0, [x19, 8]
	add	x2, x2, :lo12:.LANCHOR29
	ldrb	w0, [x1, 7]
	mov	x1, 0
	strb	w0, [x19, 9]
	adrp	x0, .LANCHOR23
	ldrb	w3, [x0, #:lo12:.LANCHOR23]
.L1335:
	cmp	w3, w1, uxtb
	bhi	.L1336
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L1336:
	ldrb	w0, [x1, x2]
	add	x1, x1, 1
	ldrb	w5, [x19, 10]
	lsl	w0, w4, w0
	orr	w0, w0, w5
	strb	w0, [x19, 10]
	b	.L1335
	.size	zftl_read_flash_info, .-zftl_read_flash_info
	.section	.text.gc_static_wearleveling,"ax",@progbits
	.align	2
	.global	gc_static_wearleveling
	.type	gc_static_wearleveling, %function
gc_static_wearleveling:
	stp	x29, x30, [sp, -160]!
	add	x29, sp, 0
	stp	x21, x22, [sp, 32]
	adrp	x22, .LANCHOR110
	stp	x19, x20, [sp, 16]
	ldr	x0, [x22, #:lo12:.LANCHOR110]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	ldr	w1, [x0, 32]
	mov	w0, 10240
	cmp	w1, w0
	bls	.L1339
	bl	ftl_tmp_into_update
.L1339:
	adrp	x19, .LANCHOR12
	mov	w3, 36000
	ldr	x0, [x19, #:lo12:.LANCHOR12]
	ldr	w1, [x0, 568]
	ldr	w2, [x0, 12]
	add	w3, w1, w3
	cmp	w2, w3
	bcs	.L1340
	ldr	x4, [x22, #:lo12:.LANCHOR110]
	ldr	w3, [x0, 572]
	add	w3, w3, 256
	ldr	w4, [x4, 36]
	cmp	w4, w3
	bcc	.L1392
.L1340:
	add	w1, w1, 860160
	add	w1, w1, 3840
	cmp	w2, w1
	bhi	.L1342
	ldr	x3, [x22, #:lo12:.LANCHOR110]
	ldr	w1, [x0, 572]
	add	w1, w1, 32
	ldr	w3, [x3, 36]
	cmp	w3, w1
	bls	.L1393
.L1342:
	ldr	x1, [x22, #:lo12:.LANCHOR110]
	mov	w20, 65535
	adrp	x8, .LANCHOR19
	mov	w21, w20
	add	x8, x8, :lo12:.LANCHOR19
	mov	w27, 0
	mov	w25, 0
	mov	w26, 0
	ldr	w3, [x1, 36]
	mov	w23, 0
	ldrh	w28, [x1, 134]
	adrp	x24, .LANCHOR9
	str	w2, [x0, 568]
	str	w3, [x0, 572]
	adrp	x0, .LANCHOR8
	add	x10, x0, :lo12:.LANCHOR8
	str	wzr, [x29, 128]
	str	wzr, [x29, 136]
	stp	wzr, wzr, [x29, 144]
.L1344:
	ldrh	w0, [x10]
	cmp	w0, w28
	bhi	.L1353
	ldr	x0, [x19, #:lo12:.LANCHOR12]
	mov	w2, 128
	mov	w1, 255
	add	x0, x0, 264
	strh	wzr, [x0, -142]
	bl	ftl_memset
	ldr	x0, [x19, #:lo12:.LANCHOR12]
	adrp	x2, .LANCHOR19
	ldr	x8, [x24, #:lo12:.LANCHOR9]
	ldr	w3, [x2, #:lo12:.LANCHOR19]
	str	x2, [x29, 152]
	ldrh	w0, [x0, 586]
	mov	x1, x0
	lsl	x28, x0, 2
	add	x10, x8, x28
	tbz	x3, 10, .L1354
	adrp	x2, .LANCHOR11
	ldrb	w6, [x10, 3]
	ldrb	w4, [x10, 2]
	ldr	x5, [x2, #:lo12:.LANCHOR11]
	ldr	w3, [x8, x28]
	ldrh	w2, [x8, x28]
	stp	x8, x10, [x29, 112]
	ldrh	w7, [x5, x0, lsl 1]
	ubfx	x3, x3, 11, 8
	ubfx	x5, x4, 5, 3
	and	w2, w2, 2047
	ubfx	x4, x4, 3, 2
	adrp	x0, .LC83
	add	x0, x0, :lo12:.LC83
	bl	printf
	ldp	x8, x10, [x29, 112]
.L1354:
	ldrb	w0, [x10, 2]
	and	w3, w0, 224
	cmp	w3, 32
	bne	.L1355
	ldr	x1, [x22, #:lo12:.LANCHOR110]
	ldrh	w1, [x1, 688]
	cmp	w1, 2
	bls	.L1355
	adrp	x1, .LANCHOR148
	mov	w2, 1
	str	w2, [x1, #:lo12:.LANCHOR148]
.L1355:
	ldrb	w1, [x10, 2]
	tbz	x1, 3, .L1356
	ldr	x1, [x22, #:lo12:.LANCHOR110]
	ldrh	w2, [x8, x28]
	and	w2, w2, 2047
	ldrh	w4, [x1, 96]
	adrp	x1, .LANCHOR149
	ldrh	w1, [x1, #:lo12:.LANCHOR149]
	add	w1, w2, w1, lsr 2
	cmp	w4, w1
	ble	.L1356
	and	w0, w0, 192
	cmp	w0, 64
	bne	.L1357
	ldr	x0, [x19, #:lo12:.LANCHOR12]
	mov	w1, 0
	mov	w2, 1
	ldrh	w0, [x0, 586]
	bl	gc_add_sblk
	adrp	x0, .LANCHOR70+2192
	mov	w1, 1
	strh	w1, [x0, #:lo12:.LANCHOR70+2192]
.L1356:
	ldr	x0, [x19, #:lo12:.LANCHOR12]
	ldr	x2, [x29, 152]
	ldr	x11, [x24, #:lo12:.LANCHOR9]
	ldrh	w0, [x0, 584]
	ldr	w2, [x2, #:lo12:.LANCHOR19]
	mov	x1, x0
	lsl	x10, x0, 2
	add	x28, x11, x10
	tbz	x2, 10, .L1358
	adrp	x2, .LANCHOR11
	ldrb	w6, [x28, 3]
	ldrb	w4, [x28, 2]
	ldr	x5, [x2, #:lo12:.LANCHOR11]
	ldr	w3, [x11, x10]
	ldrh	w2, [x11, x10]
	stp	x10, x11, [x29, 112]
	ldrh	w7, [x5, x0, lsl 1]
	ubfx	x3, x3, 11, 8
	ubfx	x5, x4, 5, 3
	and	w2, w2, 2047
	ubfx	x4, x4, 3, 2
	adrp	x0, .LC84
	add	x0, x0, :lo12:.LC84
	bl	printf
	ldp	x10, x11, [x29, 112]
.L1358:
	ldrb	w0, [x28, 2]
	tbz	x0, 3, .L1359
	ldr	x0, [x22, #:lo12:.LANCHOR110]
	ldr	w1, [x11, x10]
	ldrh	w2, [x0, 98]
	adrp	x0, .LANCHOR150
	ubfx	x1, x1, 11, 8
	ldrh	w0, [x0, #:lo12:.LANCHOR150]
	add	w0, w1, w0, lsr 2
	cmp	w2, w0
	ble	.L1359
	ldrb	w0, [x28, 2]
	and	w1, w0, 192
	cmp	w1, 64
	bne	.L1360
	ldr	x0, [x19, #:lo12:.LANCHOR12]
	mov	w1, 0
	mov	w2, 1
	ldrh	w0, [x0, 584]
	bl	gc_add_sblk
	adrp	x0, .LANCHOR70+2192
	mov	w1, 1
	strh	w1, [x0, #:lo12:.LANCHOR70+2192]
.L1359:
	ldr	x0, [x29, 152]
	ldr	w0, [x0, #:lo12:.LANCHOR19]
	tbz	x0, 10, .L1361
	adrp	x2, .LANCHOR11
	ldr	x1, [x24, #:lo12:.LANCHOR9]
	uxtw	x6, w27
	lsl	x0, x6, 2
	ldr	x7, [x2, #:lo12:.LANCHOR11]
	add	x5, x1, x0
	ldr	w3, [x1, x0]
	ldrh	w7, [x7, x6, lsl 1]
	ldrb	w6, [x5, 3]
	ldrb	w4, [x5, 2]
	ubfx	x3, x3, 11, 8
	ldrh	w2, [x1, x0]
	adrp	x0, .LC85
	mov	w1, w27
	add	x0, x0, :lo12:.LC85
	ubfx	x5, x4, 5, 3
	and	w2, w2, 2047
	ubfx	x4, x4, 3, 2
	bl	printf
.L1361:
	ldr	x0, [x29, 152]
	ldr	w0, [x0, #:lo12:.LANCHOR19]
	tbz	x0, 10, .L1362
	ldr	w6, [x29, 128]
	adrp	x2, .LANCHOR11
	ldr	x1, [x24, #:lo12:.LANCHOR9]
	ldr	x7, [x2, #:lo12:.LANCHOR11]
	lsl	x0, x6, 2
	add	x5, x1, x0
	ldr	w3, [x1, x0]
	ldrh	w2, [x1, x0]
	adrp	x0, .LC86
	ldrh	w7, [x7, x6, lsl 1]
	add	x0, x0, :lo12:.LC86
	ldrb	w6, [x5, 3]
	ubfx	x3, x3, 11, 8
	ldr	w1, [x29, 128]
	and	w2, w2, 2047
	ldrb	w4, [x5, 2]
	ubfx	x5, x4, 5, 3
	ubfx	x4, x4, 3, 2
	bl	printf
.L1362:
	ldr	x0, [x22, #:lo12:.LANCHOR110]
	ldrh	w1, [x29, 148]
	strh	w1, [x0, 96]
	ldr	w1, [x29, 136]
	strh	w23, [x0, 98]
	strh	w20, [x0, 92]
	strh	w21, [x0, 94]
	udiv	w3, w1, w26
	ldr	w1, [x29, 144]
	udiv	w4, w1, w25
	strh	w3, [x0, 88]
	strh	w4, [x0, 90]
	ldr	x0, [x29, 152]
	ldr	w0, [x0, #:lo12:.LANCHOR19]
	tbz	x0, 10, .L1363
	adrp	x0, .LC87
	and	w4, w4, 65535
	and	w3, w3, 65535
	mov	w2, w25
	mov	w1, w26
	add	x0, x0, :lo12:.LC87
	bl	printf
.L1363:
	ldr	x0, [x29, 152]
	ldr	w0, [x0, #:lo12:.LANCHOR19]
	tbz	x0, 10, .L1364
	adrp	x0, .LANCHOR150
	ldr	w3, [x29, 148]
	mov	w4, w23
	mov	w2, w21
	ldrh	w6, [x0, #:lo12:.LANCHOR150]
	adrp	x0, .LANCHOR149
	mov	w1, w20
	ldrh	w5, [x0, #:lo12:.LANCHOR149]
	adrp	x0, .LC88
	add	x0, x0, :lo12:.LC88
	bl	printf
.L1364:
	sub	w0, w23, w21
	str	w0, [x29, 144]
	adrp	x0, .LANCHOR150
	ldr	w1, [x29, 144]
	ldrh	w0, [x0, #:lo12:.LANCHOR150]
	cmp	w1, w0
	bgt	.L1365
	adrp	x1, .LANCHOR149
	ldr	w0, [x29, 148]
	ldrh	w1, [x1, #:lo12:.LANCHOR149]
	sub	w0, w0, w20
	cmp	w0, w1
	ble	.L1394
.L1365:
	ldr	x0, [x19, #:lo12:.LANCHOR12]
	adrp	x26, .LANCHOR70
	add	x26, x26, :lo12:.LANCHOR70
	mov	w25, 0
	mov	w23, 0
	ldrh	w28, [x0, 580]
	ldr	x0, [x22, #:lo12:.LANCHOR110]
	ldrh	w27, [x0, 134]
	adrp	x0, .LANCHOR8
	add	x0, x0, :lo12:.LANCHOR8
	str	x0, [x29, 136]
	adrp	x0, .LANCHOR149
	add	x0, x0, :lo12:.LANCHOR149
	str	x0, [x29, 128]
.L1367:
	ldr	x0, [x29, 136]
	ldrh	w0, [x0]
	cmp	w27, w0
	bcc	.L1377
.L1376:
	ldr	x0, [x19, #:lo12:.LANCHOR12]
	str	w28, [x0, 580]
.L1366:
	cbz	w21, .L1379
	ldr	x2, [x22, #:lo12:.LANCHOR110]
	adrp	x0, .LANCHOR8
	ldrh	w5, [x0, #:lo12:.LANCHOR8]
	ldr	x0, [x24, #:lo12:.LANCHOR9]
	ldrh	w1, [x2, 134]
	add	x0, x0, x1, uxth 2
.L1380:
	cmp	w1, w5
	bcc	.L1382
	ldrh	w0, [x2, 72]
	add	w0, w21, w0
	strh	w0, [x2, 72]
	ldrh	w0, [x2, 98]
	cmp	w21, w0
	bcs	.L1379
	sub	w21, w0, w21
	strh	w21, [x2, 98]
.L1379:
	cbz	w20, .L1385
	ldr	x2, [x22, #:lo12:.LANCHOR110]
	adrp	x0, .LANCHOR8
	ldrh	w6, [x0, #:lo12:.LANCHOR8]
	ldr	x0, [x24, #:lo12:.LANCHOR9]
	ldrh	w1, [x2, 134]
	add	x0, x0, x1, uxth 2
.L1386:
	cmp	w1, w6
	bcc	.L1388
	ldrh	w0, [x2, 74]
	add	w0, w20, w0
	strh	w0, [x2, 74]
	ldrh	w0, [x2, 96]
	cmp	w20, w0
	bcs	.L1385
	sub	w20, w0, w20
	strh	w20, [x2, 96]
.L1385:
	mov	w1, 0
	adrp	x0, .LANCHOR92
	add	x0, x0, :lo12:.LANCHOR92
	bl	_list_get_gc_head_node
	and	w1, w0, 65535
	mov	w2, 65535
	cmp	w1, w2
	beq	.L1343
	adrp	x2, .LANCHOR11
	ubfiz	x1, x1, 1, 16
	ldr	x3, [x2, #:lo12:.LANCHOR11]
	adrp	x2, .LANCHOR94
	ldrh	w2, [x2, #:lo12:.LANCHOR94]
	ldrh	w1, [x3, x1]
	cmp	w1, w2, lsr 1
	bhi	.L1343
	add	w23, w23, 1
	mov	w2, 1
	mov	w1, 0
	bl	gc_add_sblk
.L1343:
	add	w0, w23, w25
.L1338:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 160
	ret
.L1353:
	uxtw	x7, w28
	ldr	x6, [x24, #:lo12:.LANCHOR9]
	lsl	x2, x7, 2
	add	x11, x6, x2
	ldrb	w0, [x11, 2]
	and	w1, w0, 224
	cmp	w1, 224
	beq	.L1345
	ubfx	x4, x0, 3, 2
	tbz	x4, 0, .L1346
	ldr	w0, [x6, x2]
	ldrh	w1, [x6, x2]
	ubfx	x0, x0, 11, 8
	and	w1, w1, 2047
.L1347:
	ldr	w3, [x29, 136]
	add	w26, w26, 1
	and	w26, w26, 65535
	cmp	w20, w1
	add	w3, w3, w1
	str	w3, [x29, 136]
	bls	.L1391
	ldr	x3, [x19, #:lo12:.LANCHOR12]
	mov	w20, w1
	strh	w28, [x3, 586]
.L1391:
	ldr	w3, [x29, 148]
	cmp	w3, w1
	bcs	.L1350
	mov	w27, w28
	str	w1, [x29, 148]
.L1350:
	mov	w3, 65535
	cmp	w0, w3
	bne	.L1349
.L1351:
	cmp	w0, 9
	ccmp	w1, 9, 0, hi
	bhi	.L1345
	ldr	w0, [x8]
	tbz	x0, 8, .L1345
	adrp	x0, .LANCHOR11
	ldr	w3, [x6, x2]
	ldrh	w2, [x6, x2]
	mov	w1, w28
	ldr	x0, [x0, #:lo12:.LANCHOR11]
	ldrb	w6, [x11, 3]
	ubfx	x3, x3, 11, 8
	ldrb	w5, [x11, 2]
	and	w2, w2, 2047
	str	x8, [x29, 120]
	ldrh	w7, [x0, x7, lsl 1]
	adrp	x0, .LC82
	str	x10, [x29, 152]
	ubfx	x5, x5, 5, 3
	add	x0, x0, :lo12:.LC82
	bl	printf
	ldr	x8, [x29, 120]
	ldr	x10, [x29, 152]
.L1345:
	add	w28, w28, 1
	and	w28, w28, 65535
	b	.L1344
.L1346:
	tst	w0, 24
	bne	.L1348
	ldrh	w1, [x6, x2]
	mov	w0, 65535
	and	w1, w1, 2047
	b	.L1347
.L1348:
	ldr	w0, [x6, x2]
	mov	w1, 65535
	ubfx	x0, x0, 11, 8
.L1349:
	ldr	w3, [x29, 144]
	add	w25, w25, 1
	and	w25, w25, 65535
	cmp	w21, w0
	add	w3, w3, w0
	str	w3, [x29, 144]
	bls	.L1352
	ldr	x3, [x19, #:lo12:.LANCHOR12]
	mov	w21, w0
	strh	w28, [x3, 584]
.L1352:
	cmp	w23, w0
	bcs	.L1351
	mov	w23, w0
	str	w28, [x29, 128]
	b	.L1351
.L1357:
	cbnz	w3, .L1356
	ldr	x1, [x19, #:lo12:.LANCHOR12]
	mov	w0, 65535
	ldrh	w2, [x1, 590]
	cmp	w2, w0
	bne	.L1356
	ldrh	w0, [x1, 586]
	ldrh	w1, [x1, 588]
	cmp	w1, w0
	beq	.L1356
	bl	zftl_remove_free_node
	ldr	x0, [x19, #:lo12:.LANCHOR12]
	ldrh	w1, [x0, 586]
	strh	w1, [x0, 590]
	mov	w1, -1
	strh	w1, [x0, 586]
	b	.L1356
.L1360:
	and	w0, w0, 248
	cmp	w0, 16
	bne	.L1359
	ldr	x1, [x19, #:lo12:.LANCHOR12]
	mov	w0, 65535
	ldrh	w2, [x1, 588]
	cmp	w2, w0
	bne	.L1359
	ldrh	w0, [x1, 584]
	ldrh	w1, [x1, 590]
	cmp	w1, w0
	beq	.L1359
	bl	zftl_remove_free_node
	ldr	x0, [x19, #:lo12:.LANCHOR12]
	ldrh	w1, [x0, 584]
	strh	w1, [x0, 588]
	mov	w1, -1
	strh	w1, [x0, 584]
	b	.L1359
.L1377:
	add	w7, w28, 1
	ldr	x4, [x24, #:lo12:.LANCHOR9]
	and	w28, w7, 65535
	cmp	w0, w28
	csel	w28, w28, wzr, hi
	uxtw	x8, w28
	lsl	x3, x8, 2
	add	x0, x4, x3
	ldrb	w0, [x0, 2]
	tst	w0, 192
	beq	.L1369
	and	w2, w0, 224
	cmp	w2, 224
	beq	.L1369
	ubfx	x0, x0, 3, 2
	and	w1, w0, 1
	tbz	x0, 0, .L1370
	cmp	w2, 160
.L1457:
	bne	.L1372
	adrp	x0, .LANCHOR150
	ldr	w2, [x29, 144]
	ldrh	w0, [x0, #:lo12:.LANCHOR150]
	cmp	w2, w0
	ble	.L1373
	ldr	w0, [x4, x3]
	ubfx	x0, x0, 11, 8
	cmp	w0, w21
	bls	.L1374
	cbz	w1, .L1373
	ldrh	w0, [x4, x3]
	and	w0, w0, 2047
	cmp	w0, w20
	bgt	.L1373
.L1374:
	stp	x4, x8, [x29, 104]
	mov	w2, 1
	str	x3, [x29, 120]
	mov	w1, 0
	mov	w0, w28
	bl	gc_add_sblk
	mov	w0, 1
	strh	w0, [x26, 2192]
	ldr	x0, [x29, 152]
	add	w23, w23, 1
	ldp	x4, x8, [x29, 104]
	ldr	x3, [x29, 120]
	ldr	w0, [x0, #:lo12:.LANCHOR19]
	tbz	x0, 10, .L1373
	adrp	x0, .LANCHOR11
	ldr	w6, [x4, x3]
	ldrh	w5, [x4, x3]
	ldr	x1, [x0, #:lo12:.LANCHOR11]
	ldr	x0, [x24, #:lo12:.LANCHOR9]
	ubfx	x6, x6, 11, 8
	ldrh	w4, [x26, 56]
	and	w5, w5, 2047
	add	x3, x0, x3
	adrp	x0, .LC89
	add	x0, x0, :lo12:.LC89
	ldrb	w2, [x3, 2]
	ldrh	w3, [x1, x8, lsl 1]
	mov	w1, w28
	ubfx	x2, x2, 5, 3
.L1458:
	bl	printf
.L1373:
	cmp	w23, 4
	ccmp	w25, 4, 2, ls
	bhi	.L1376
.L1369:
	add	w27, w27, 1
	and	w27, w27, 65535
	b	.L1367
.L1370:
	cmp	w0, 2
	b	.L1457
.L1372:
	ldr	x2, [x29, 128]
	ldr	w0, [x29, 148]
	sub	w0, w0, w20
	ldrh	w2, [x2]
	cmp	w0, w2
	ble	.L1373
	ldrh	w0, [x4, x3]
	add	w2, w20, 8
	and	w0, w0, 2047
	cmp	w0, w2
	ble	.L1375
	cbz	w1, .L1373
	ldr	w0, [x4, x3]
	add	w1, w21, 4
	ubfx	x0, x0, 11, 8
	cmp	w0, w1
	bgt	.L1373
.L1375:
	stp	x4, x8, [x29, 104]
	mov	w2, 1
	str	x3, [x29, 120]
	mov	w1, 0
	mov	w0, w28
	bl	gc_add_sblk
	mov	w0, 1
	strh	w0, [x26, 2192]
	ldr	x0, [x29, 152]
	add	w25, w25, 1
	ldp	x4, x8, [x29, 104]
	ldr	x3, [x29, 120]
	ldr	w0, [x0, #:lo12:.LANCHOR19]
	tbz	x0, 10, .L1373
	adrp	x0, .LANCHOR11
	ldr	w6, [x4, x3]
	ldrh	w5, [x4, x3]
	ldr	x1, [x0, #:lo12:.LANCHOR11]
	ldr	x0, [x24, #:lo12:.LANCHOR9]
	ubfx	x6, x6, 11, 8
	and	w5, w5, 2047
	ldrh	w4, [x26, 56]
	add	x3, x0, x3
	adrp	x0, .LC90
	add	x0, x0, :lo12:.LC90
	ldrb	w2, [x3, 2]
	ldrh	w3, [x1, x8, lsl 1]
	mov	w1, w28
	ubfx	x2, x2, 5, 3
	b	.L1458
.L1394:
	mov	w25, 0
	mov	w23, 0
	b	.L1366
.L1382:
	ldr	w3, [x0]
	ubfx	x4, x3, 11, 8
	cmp	w21, w4
	bhi	.L1381
	ldrb	w6, [x0, 2]
	tst	w6, 24
	beq	.L1381
	sub	w4, w4, w21
	bfi	w3, w4, 11, 8
	str	w3, [x0]
.L1381:
	add	w1, w1, 1
	add	x0, x0, 4
	and	w1, w1, 65535
	b	.L1380
.L1388:
	ldrh	w3, [x0]
	and	w4, w3, 2047
	cmp	w4, w20
	blt	.L1387
	ldrb	w5, [x0, 2]
	and	w5, w5, 24
	cmp	w5, 16
	beq	.L1387
	sub	w4, w4, w20
	bfi	w3, w4, 0, 11
	strh	w3, [x0]
.L1387:
	add	w1, w1, 1
	add	x0, x0, 4
	and	w1, w1, 65535
	b	.L1386
.L1393:
	mov	w25, 0
	mov	w23, 0
	b	.L1343
.L1392:
	mov	w0, 0
	b	.L1338
	.size	gc_static_wearleveling, .-gc_static_wearleveling
	.section	.text.zftl_sblk_list_init,"ax",@progbits
	.align	2
	.global	zftl_sblk_list_init
	.type	zftl_sblk_list_init, %function
zftl_sblk_list_init:
	stp	x29, x30, [sp, -208]!
	adrp	x8, .LANCHOR4
	mov	w0, 6
	mov	w1, 0
	add	x29, sp, 0
	stp	x27, x28, [sp, 80]
	adrp	x28, .LANCHOR8
	stp	x19, x20, [sp, 16]
	adrp	x20, .LANCHOR99
	ldrh	w2, [x28, #:lo12:.LANCHOR8]
	mov	w27, 0
	stp	x21, x22, [sp, 32]
	adrp	x22, .LANCHOR97
	stp	x23, x24, [sp, 48]
	adrp	x21, .LANCHOR91
	stp	x25, x26, [sp, 64]
	adrp	x26, .LANCHOR110
	mul	w2, w2, w0
	ldr	x0, [x8, #:lo12:.LANCHOR4]
	str	x8, [x29, 192]
	adrp	x25, .LANCHOR103
	adrp	x24, .LANCHOR105
	adrp	x23, .LANCHOR107
	bl	ftl_memset
	strh	wzr, [x25, #:lo12:.LANCHOR103]
	adrp	x0, .LANCHOR109
	adrp	x3, .LANCHOR79
	adrp	x2, .LANCHOR85
	mov	w1, 32
	strh	w1, [x0, #:lo12:.LANCHOR109]
	adrp	x11, .LANCHOR104
	ldrb	w0, [x3, #:lo12:.LANCHOR79]
	adrp	x10, .LANCHOR106
	ldrh	w1, [x2, #:lo12:.LANCHOR85]
	adrp	x7, .LANCHOR108
	adrp	x6, .LANCHOR90
	adrp	x5, .LANCHOR95
	adrp	x4, .LANCHOR92
	ldr	x8, [x29, 192]
	str	xzr, [x11, #:lo12:.LANCHOR104]
	mul	w1, w0, w1
	mov	w0, 32768
	str	xzr, [x10, #:lo12:.LANCHOR106]
	str	xzr, [x7, #:lo12:.LANCHOR108]
	str	xzr, [x6, #:lo12:.LANCHOR90]
	sdiv	w0, w0, w1
	str	xzr, [x5, #:lo12:.LANCHOR95]
	str	xzr, [x4, #:lo12:.LANCHOR92]
	strh	wzr, [x24, #:lo12:.LANCHOR105]
	strh	wzr, [x23, #:lo12:.LANCHOR107]
	sxth	w0, w0
	str	w0, [x29, 204]
	ldr	x0, [x26, #:lo12:.LANCHOR110]
	strh	wzr, [x22, #:lo12:.LANCHOR97]
	strh	wzr, [x21, #:lo12:.LANCHOR91]
	strh	wzr, [x20, #:lo12:.LANCHOR99]
	strh	wzr, [x0, 146]
	ldrsh	w19, [x0, 134]
	add	x0, x28, :lo12:.LANCHOR8
	str	x0, [x29, 192]
	adrp	x0, .LANCHOR151
	add	x0, x0, :lo12:.LANCHOR151
	adrp	x28, .LC0
	str	x0, [x29, 112]
	add	x0, x28, :lo12:.LC0
	stp	x2, x3, [x29, 120]
	stp	x4, x5, [x29, 136]
	stp	x6, x7, [x29, 152]
	stp	x10, x11, [x29, 168]
	str	x8, [x29, 184]
	str	x0, [x29, 104]
.L1460:
	ldr	x0, [x29, 192]
	ldrh	w0, [x0]
	cmp	w19, w0
	blt	.L1477
	ldr	x0, [x26, #:lo12:.LANCHOR110]
	ldrh	w1, [x25, #:lo12:.LANCHOR103]
	ldp	x27, x28, [sp, 80]
	strh	w1, [x0, 114]
	ldrh	w1, [x24, #:lo12:.LANCHOR105]
	strh	w1, [x0, 118]
	ldrh	w1, [x23, #:lo12:.LANCHOR107]
	strh	w1, [x0, 116]
	ldrh	w1, [x22, #:lo12:.LANCHOR97]
	strh	w1, [x0, 122]
	ldrh	w1, [x21, #:lo12:.LANCHOR91]
	strh	w1, [x0, 120]
	ldrh	w1, [x20, #:lo12:.LANCHOR99]
	strh	w1, [x0, 124]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 208
	ret
.L1477:
	adrp	x0, .LANCHOR9
	sxtw	x2, w19
	ldr	x3, [x0, #:lo12:.LANCHOR9]
	add	x28, x3, x2, lsl 2
	ldrb	w5, [x28, 3]
	cbz	w5, .L1478
	ldr	x0, [x29, 128]
	mov	w1, 0
	ldr	x6, [x26, #:lo12:.LANCHOR110]
	ldrb	w7, [x0, #:lo12:.LANCHOR79]
	ldr	x0, [x29, 120]
	ldrh	w8, [x0, #:lo12:.LANCHOR85]
	mov	w0, 0
.L1462:
	cmp	w1, w7
	blt	.L1465
	cbz	w0, .L1466
	mov	w1, 32768
	sdiv	w0, w1, w0
	add	w0, w0, 1
	sxth	w0, w0
.L1461:
	ldr	x3, [x29, 184]
	mov	w1, 6
	smull	x1, w19, w1
	ldr	x4, [x3, #:lo12:.LANCHOR4]
	add	x5, x4, x1
	strh	w0, [x5, 4]
	mov	w0, -1
	strh	w0, [x5, 2]
	strh	w0, [x4, x1]
	mov	w1, 224
	ldrb	w0, [x28, 2]
	and	w0, w0, 224
	cmp	w0, 32
	ccmp	w0, w1, 4, ne
	beq	.L1467
	adrp	x1, .LANCHOR12
	ldr	x1, [x1, #:lo12:.LANCHOR12]
	ldrh	w4, [x1, 16]
	cmp	w19, w4
	beq	.L1467
	ldrh	w4, [x1, 48]
	cmp	w19, w4
	beq	.L1467
	ldrh	w1, [x1, 80]
	cmp	w19, w1
	beq	.L1467
	cmp	w0, 64
	bne	.L1468
	ldr	x0, [x29, 144]
	add	x2, x22, :lo12:.LANCHOR97
	mov	w1, w19
	add	x0, x0, :lo12:.LANCHOR95
.L1484:
	bl	_insert_data_list
.L1467:
	add	w19, w19, 1
	sxth	w19, w19
	b	.L1460
.L1465:
	asr	w4, w5, w1
	tbnz	x4, 0, .L1463
	add	w0, w8, w0
	sxth	w0, w0
.L1464:
	add	w1, w1, 1
	b	.L1462
.L1463:
	ldrh	w4, [x6, 146]
	add	w4, w4, 1
	strh	w4, [x6, 146]
	b	.L1464
.L1466:
	ldrb	w1, [x28, 2]
	mov	w4, -1
	orr	w1, w1, -32
	strb	w1, [x28, 2]
	adrp	x1, .LANCHOR11
	ldr	x1, [x1, #:lo12:.LANCHOR11]
	strh	w4, [x1, x2, lsl 1]
	b	.L1461
.L1478:
	ldr	w0, [x29, 204]
	b	.L1461
.L1468:
	cmp	w0, 96
	bne	.L1469
	ldr	x0, [x29, 152]
	add	x2, x20, :lo12:.LANCHOR99
	mov	w1, w19
	add	x0, x0, :lo12:.LANCHOR90
	b	.L1484
.L1469:
	cmp	w0, 160
	bne	.L1470
	ldr	x0, [x29, 136]
	add	x2, x21, :lo12:.LANCHOR91
	mov	w1, w19
	add	x0, x0, :lo12:.LANCHOR92
	b	.L1484
.L1470:
	cbnz	w0, .L1467
	adrp	x0, .LANCHOR11
	ldr	x0, [x0, #:lo12:.LANCHOR11]
	ldrh	w2, [x0, x2, lsl 1]
	cbz	w2, .L1471
	cmp	w27, 2
	bgt	.L1472
	mov	w1, w19
	adrp	x0, .LC91
	add	x0, x0, :lo12:.LC91
	bl	printf
	ldrb	w0, [x28, 2]
	add	w27, w27, 1
	sxth	w27, w27
	tbz	x0, 4, .L1473
	mov	w1, 5
.L1483:
	bfi	w0, w1, 5, 3
	strb	w0, [x28, 2]
	mov	w2, 0
	mov	w1, 1
	mov	w0, w19
	bl	gc_add_sblk
	b	.L1467
.L1473:
	mov	w1, 2
	b	.L1483
.L1472:
	ldp	x0, x1, [x29, 104]
	mov	w2, 656
	bl	printf
.L1471:
	ldrb	w0, [x28, 2]
	ands	w0, w0, 24
	bne	.L1475
	ldr	x0, [x29, 176]
	add	x2, x25, :lo12:.LANCHOR103
	mov	w1, w19
	add	x0, x0, :lo12:.LANCHOR104
.L1485:
	bl	_insert_free_list
	b	.L1467
.L1475:
	cmp	w0, 16
	bne	.L1476
	ldr	x0, [x29, 168]
	add	x2, x24, :lo12:.LANCHOR105
	mov	w1, w19
	add	x0, x0, :lo12:.LANCHOR106
	b	.L1485
.L1476:
	ldr	x0, [x29, 160]
	add	x2, x23, :lo12:.LANCHOR107
	mov	w1, w19
	add	x0, x0, :lo12:.LANCHOR108
	b	.L1485
	.size	zftl_sblk_list_init, .-zftl_sblk_list_init
	.section	.text.pm_free_sblk,"ax",@progbits
	.align	2
	.global	pm_free_sblk
	.type	pm_free_sblk, %function
pm_free_sblk:
	stp	x29, x30, [sp, -384]!
	adrp	x0, .LANCHOR152
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	ldrh	w1, [x0, #:lo12:.LANCHOR152]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	cmp	w1, 128
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	bls	.L1487
	adrp	x1, .LANCHOR153
	adrp	x0, .LC0
	mov	w2, 94
	add	x1, x1, :lo12:.LANCHOR153
	add	x0, x0, :lo12:.LC0
	bl	printf
.L1487:
	adrp	x5, .LANCHOR110
	mov	x26, x5
	ldrh	w3, [x19, #:lo12:.LANCHOR152]
	mov	w1, 0
	ldr	x0, [x5, #:lo12:.LANCHOR110]
	mov	w19, 0
	mov	w4, 65535
	add	x0, x0, 416
	ldrh	w2, [x0, 272]
.L1490:
	ldrh	w6, [x0]
	cmp	w6, w4
	beq	.L1488
	add	w1, w1, 1
	and	w1, w1, 65535
.L1488:
	cmp	w1, w2
	bcs	.L1489
	cmp	w1, w3
	bcs	.L1489
	add	w19, w19, 1
	add	x0, x0, 2
	and	w19, w19, 65535
	cmp	w19, 128
	bne	.L1490
.L1489:
	add	w19, w19, 1
	mov	w0, 128
	and	w19, w19, 65535
	add	x22, x29, 128
	cmp	w19, 129
	mov	w2, 256
	csel	w19, w19, w0, ne
	mov	w1, 0
	mov	x0, x22
	adrp	x23, .LANCHOR75
	bl	ftl_memset
	adrp	x0, .LANCHOR74
	ldr	x6, [x26, #:lo12:.LANCHOR110]
	mov	w2, 24
	ldrb	w11, [x23, #:lo12:.LANCHOR75]
	ldrh	w10, [x0, #:lo12:.LANCHOR74]
	adrp	x0, .LANCHOR31
	add	x4, x6, 704
	ldrb	w0, [x0, #:lo12:.LANCHOR31]
	ldrh	w1, [x6, 698]
	sub	w2, w2, w0
	sub	w0, w2, w10
	add	x1, x1, 176
	mov	w2, 1
	add	x1, x6, x1, lsl 2
	lsl	w2, w2, w0
	sub	w2, w2, #1
.L1492:
	cmp	x1, x4
	bne	.L1495
	adrp	x24, .LANCHOR79
	adrp	x25, .LANCHOR94
	adrp	x27, .LC92
	adrp	x28, .LANCHOR19
	ldrb	w21, [x24, #:lo12:.LANCHOR79]
	add	x23, x23, :lo12:.LANCHOR75
	ldrh	w0, [x25, #:lo12:.LANCHOR94]
	add	x27, x27, :lo12:.LC92
	add	x28, x28, :lo12:.LANCHOR19
	mov	x20, 0
	mov	w7, 65535
	str	wzr, [x29, 124]
	mul	w21, w21, w0
	and	w21, w21, 65535
.L1501:
	ldr	x0, [x26, #:lo12:.LANCHOR110]
	and	w6, w20, 65535
	ldrb	w2, [x23]
	mov	w8, w20
	add	x1, x0, x20, sxtw 1
	ldrh	w3, [x1, 416]
	ldrh	w1, [x0, 692]
	sdiv	w1, w1, w2
	cmp	w1, w3
	bne	.L1496
	ldrb	w1, [x24, #:lo12:.LANCHOR79]
	ldrh	w2, [x25, #:lo12:.LANCHOR94]
	mul	w1, w1, w2
	strh	w1, [x22, x20, lsl 1]
.L1496:
	ldrh	w2, [x22, x20, lsl 1]
	cmp	w2, w21
	bcs	.L1497
	cmp	w2, 0
	ldr	w1, [x29, 124]
	csel	w21, w21, w2, eq
	csel	w1, w1, w6, eq
	str	w1, [x29, 124]
.L1497:
	ldrh	w1, [x0, 74]
	cmp	w1, 2
	bls	.L1498
	mov	w1, 65535
	cmp	w3, w1
	beq	.L1498
	adrp	x4, .LANCHOR9
	ubfiz	x1, x3, 2, 16
	ldrh	w0, [x0, 92]
	ldr	x4, [x4, #:lo12:.LANCHOR9]
	add	w0, w0, 4
	ldrh	w4, [x4, x1]
	and	w4, w4, 2047
	cmp	w4, w0
	bgt	.L1498
	mov	w1, w8
	str	w6, [x29, 104]
	str	w8, [x29, 112]
	mov	x0, x27
	bl	printf
	ldr	w6, [x29, 104]
	ldr	w8, [x29, 112]
	mov	w7, w6
.L1498:
	ldrh	w0, [x22, x20, lsl 1]
	cbnz	w0, .L1499
	ldr	x0, [x26, #:lo12:.LANCHOR110]
	sxtw	x6, w8
	add	x1, x6, 208
	ldrh	w3, [x0, x1, lsl 1]
	mov	w1, 65535
	cmp	w3, w1
	beq	.L1499
	ldr	w1, [x28]
	tbz	x1, 12, .L1500
	ldrh	w4, [x0, 688]
	mov	w2, 0
	str	x6, [x29, 104]
	mov	w1, w8
	str	w7, [x29, 112]
	adrp	x0, .LC93
	add	x0, x0, :lo12:.LC93
	bl	printf
	ldr	w7, [x29, 112]
	ldr	x6, [x29, 104]
.L1500:
	ldr	x0, [x26, #:lo12:.LANCHOR110]
	add	x6, x6, 208
	str	w7, [x29, 104]
	str	x6, [x29, 112]
	ldrh	w0, [x0, x6, lsl 1]
	bl	ftl_free_sblk
	ldr	x0, [x26, #:lo12:.LANCHOR110]
	mov	w1, -1
	ldr	x6, [x29, 112]
	ldr	w7, [x29, 104]
	strh	w1, [x0, x6, lsl 1]
	ldrh	w1, [x0, 688]
	sub	w1, w1, #1
	strh	w1, [x0, 688]
.L1499:
	add	x20, x20, 1
	cmp	w19, w20, uxth
	bhi	.L1501
	mov	w0, 65535
	cmp	w7, w0
	ldr	w0, [x29, 124]
	ldp	x19, x20, [sp, 16]
	csel	w0, w0, w7, eq
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 384
	ret
.L1495:
	ldr	w0, [x4]
	add	x7, x6, 416
	mov	x3, 0
	lsr	w0, w0, w10
	and	w0, w0, w2
	udiv	w0, w0, w11
	and	w0, w0, 65535
.L1494:
	ldrh	w8, [x7]
	cmp	w8, w0
	bne	.L1493
	ldrh	w8, [x22, x3, lsl 1]
	add	w8, w8, 1
	strh	w8, [x22, x3, lsl 1]
.L1493:
	add	x3, x3, 1
	add	x7, x7, 2
	cmp	w19, w3, uxth
	bhi	.L1494
	add	x4, x4, 4
	b	.L1492
	.size	pm_free_sblk, .-pm_free_sblk
	.section	.text.ftl_memcpy,"ax",@progbits
	.align	2
	.global	ftl_memcpy
	.type	ftl_memcpy, %function
ftl_memcpy:
	uxtw	x2, w2
	b	memcpy
	.size	ftl_memcpy, .-ftl_memcpy
	.section	.text.flash_info_data_init,"ax",@progbits
	.align	2
	.global	flash_info_data_init
	.type	flash_info_data_init, %function
flash_info_data_init:
	stp	x29, x30, [sp, -32]!
	adrp	x0, .LANCHOR19
	add	x29, sp, 0
	ldr	w0, [x0, #:lo12:.LANCHOR19]
	str	x19, [sp, 16]
	tbz	x0, 12, .L1514
	adrp	x2, .LANCHOR154
	adrp	x0, .LC94
	add	x2, x2, :lo12:.LANCHOR154
	mov	w1, 120
	add	x0, x0, :lo12:.LC94
	bl	printf
.L1514:
	adrp	x19, .LANCHOR6
	mov	w2, 2048
	mov	w1, 0
	ldr	x0, [x19, #:lo12:.LANCHOR6]
	bl	ftl_memset
	ldr	x0, [x19, #:lo12:.LANCHOR6]
	mov	w1, 21321
	movk	w1, 0x5359, lsl 16
	mov	w2, 32
	add	x0, x0, 80
	str	w1, [x0, -80]
	mov	w1, 2032
	str	w1, [x0, -72]
	mov	w1, 1
	strh	w1, [x0, -64]
	adrp	x1, .LANCHOR25
	add	x1, x1, :lo12:.LANCHOR25
	bl	ftl_memcpy
	ldr	x0, [x19, #:lo12:.LANCHOR6]
	mov	w2, 32
	ldr	x19, [sp, 16]
	adrp	x1, .LANCHOR32
	ldp	x29, x30, [sp], 32
	add	x1, x1, :lo12:.LANCHOR32
	add	x0, x0, 48
	b	ftl_memcpy
	.size	flash_info_data_init, .-flash_info_data_init
	.section	.text.ftl_memcpy32,"ax",@progbits
	.align	2
	.global	ftl_memcpy32
	.type	ftl_memcpy32, %function
ftl_memcpy32:
	mov	x3, 0
.L1520:
	cmp	w2, w3
	bhi	.L1521
	ret
.L1521:
	ldr	w4, [x1, x3, lsl 2]
	str	w4, [x0, x3, lsl 2]
	add	x3, x3, 1
	b	.L1520
	.size	ftl_memcpy32, .-ftl_memcpy32
	.section	.text.ftl_memcmp,"ax",@progbits
	.align	2
	.global	ftl_memcmp
	.type	ftl_memcmp, %function
ftl_memcmp:
	uxtw	x2, w2
	b	memcmp
	.size	ftl_memcmp, .-ftl_memcmp
	.section	.text.rknand_get_clk_rate,"ax",@progbits
	.align	2
	.global	rknand_get_clk_rate
	.type	rknand_get_clk_rate, %function
rknand_get_clk_rate:
	mov	w0, 19712
	movk	w0, 0x8d2, lsl 16
	ret
	.size	rknand_get_clk_rate, .-rknand_get_clk_rate
	.section	.text.ftl_malloc,"ax",@progbits
	.align	2
	.global	ftl_malloc
	.type	ftl_malloc, %function
ftl_malloc:
	mov	w1, 0
	sxtw	x0, w0
	b	kmalloc
	.size	ftl_malloc, .-ftl_malloc
	.section	.text.nandc_init,"ax",@progbits
	.align	2
	.global	nandc_init
	.type	nandc_init, %function
nandc_init:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x21, x22, [sp, 32]
	adrp	x21, .LANCHOR19
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	ldr	w0, [x21, #:lo12:.LANCHOR19]
	str	wzr, [x29, 56]
	tbz	x0, 12, .L1526
	adrp	x1, .LANCHOR155
	adrp	x0, .LC95
	mov	x2, x19
	add	x1, x1, :lo12:.LANCHOR155
	add	x0, x0, :lo12:.LC95
	bl	printf
.L1526:
	adrp	x20, .LANCHOR27
	mov	w0, 6
	ldr	w2, [x19, 352]
	mov	w1, 12336
	strb	w0, [x20, #:lo12:.LANCHOR27]
	adrp	x0, .LANCHOR7
	movk	w1, 0x5638, lsl 16
	mov	x22, x0
	str	x19, [x0, #:lo12:.LANCHOR7]
	cmp	w2, w1
	bne	.L1527
	mov	w0, 8
	strb	w0, [x20, #:lo12:.LANCHOR27]
.L1527:
	ldr	w1, [x19, 128]
	mov	w0, 12336
	movk	w0, 0x5639, lsl 16
	cmp	w1, w0
	bne	.L1528
	mov	w0, 9
	strb	w0, [x20, #:lo12:.LANCHOR27]
.L1528:
	ldrb	w0, [x20, #:lo12:.LANCHOR27]
	cmp	w0, 9
	adrp	x0, .LANCHOR50
	bne	.L1529
	mov	w1, 1
	strb	w1, [x0, #:lo12:.LANCHOR50]
	ldr	w0, [x29, 56]
	mov	w1, 2
	orr	w0, w0, 256
	str	w0, [x29, 56]
	ldr	w0, [x29, 56]
	bfi	w0, w1, 18, 3
	str	w0, [x29, 56]
	ldr	w0, [x29, 56]
	str	w0, [x19]
	str	wzr, [x19, 520]
	mov	w0, 4161
	str	w0, [x19, 4]
	mov	w0, 8321
	str	w0, [x19, 8]
	mov	w0, 4099
	movk	w0, 0x10, lsl 16
	str	w0, [x19, 80]
	mov	w0, 38
	str	w0, [x19, 84]
	mov	w0, 39
	str	w0, [x19, 84]
	ldr	w0, [x21, #:lo12:.LANCHOR19]
	tbz	x0, 12, .L1531
	ldr	w1, [x19]
	ldr	w2, [x19, 8]
	ldr	w3, [x19, 80]
	ldr	w4, [x19, 84]
	ldr	w5, [x19, 88]
.L1544:
	adrp	x0, .LC96
	add	x0, x0, :lo12:.LC96
	bl	printf
.L1531:
	adrp	x0, .LANCHOR51
	mov	w1, 1
	strb	w1, [x0, #:lo12:.LANCHOR51]
	adrp	x0, .LANCHOR53
	strh	wzr, [x0, #:lo12:.LANCHOR53]
	adrp	x0, .LANCHOR49
	strb	wzr, [x0, #:lo12:.LANCHOR49]
	ldr	w0, [x21, #:lo12:.LANCHOR19]
	tbz	x0, 12, .L1525
	ldrb	w1, [x20, #:lo12:.LANCHOR27]
	adrp	x0, .LC97
	add	x0, x0, :lo12:.LC97
	bl	printf
.L1525:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
.L1529:
	strb	wzr, [x0, #:lo12:.LANCHOR50]
	mov	w1, 1
	ldr	w0, [x29, 56]
	orr	w0, w0, 256
	str	w0, [x29, 56]
	ldr	w0, [x29, 56]
	bfi	w0, w1, 24, 3
	str	w0, [x29, 56]
	ldr	w0, [x29, 56]
	str	w0, [x19]
	str	wzr, [x19, 336]
	mov	w0, 4193
	str	w0, [x19, 4]
	mov	w0, 8321
	str	w0, [x19, 344]
	mov	w0, 4099
	movk	w0, 0x10, lsl 16
	str	w0, [x19, 304]
	mov	w0, 38
	str	w0, [x19, 308]
	mov	w0, 39
	str	w0, [x19, 308]
	mov	w0, 2048
	bl	ftl_malloc
	adrp	x1, .LANCHOR52
	str	x0, [x1, #:lo12:.LANCHOR52]
	ldr	w0, [x21, #:lo12:.LANCHOR19]
	tbz	x0, 12, .L1531
	ldr	x0, [x22, #:lo12:.LANCHOR7]
	ldr	w1, [x0]
	ldr	w2, [x0, 344]
	ldr	w3, [x0, 304]
	ldr	w4, [x0, 308]
	ldr	w5, [x0, 312]
	b	.L1544
	.size	nandc_init, .-nandc_init
	.section	.text.zbuf_init,"ax",@progbits
	.align	2
	.global	zbuf_init
	.type	zbuf_init, %function
zbuf_init:
	stp	x29, x30, [sp, -48]!
	adrp	x0, .LANCHOR55
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	add	x19, x0, :lo12:.LANCHOR55
	stp	x21, x22, [sp, 32]
	mov	x20, x0
	adrp	x22, .LANCHOR131
	add	x22, x22, :lo12:.LANCHOR131
	mov	w21, 0
.L1546:
	and	w0, w21, 255
	strb	w0, [x19, 1]
	add	w1, w0, 1
	ldrb	w0, [x22]
	strb	w1, [x19]
	add	w21, w21, 1
	strb	wzr, [x19, 2]
	add	x19, x19, 64
	str	xzr, [x19, -48]
	lsl	w0, w0, 9
	bl	ftl_malloc
	str	x0, [x19, -56]
	mov	w0, 64
	bl	ftl_malloc
	str	x0, [x19, -40]
	cmp	w21, 32
	bne	.L1546
	add	x0, x20, :lo12:.LANCHOR55
	mov	w1, -1
	strb	w1, [x0, 1984]
	adrp	x0, .LANCHOR56
	strb	wzr, [x0, #:lo12:.LANCHOR56]
	adrp	x0, .LANCHOR57
	ldp	x19, x20, [sp, 16]
	strb	w21, [x0, #:lo12:.LANCHOR57]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	zbuf_init, .-zbuf_init
	.section	.text.gc_init,"ax",@progbits
	.align	2
	.global	gc_init
	.type	gc_init, %function
gc_init:
	stp	x29, x30, [sp, -32]!
	adrp	x0, .LANCHOR84
	mov	w2, 2216
	mov	w1, 0
	add	x29, sp, 0
	strb	wzr, [x0, #:lo12:.LANCHOR84]
	adrp	x0, .LANCHOR156
	stp	x19, x20, [sp, 16]
	adrp	x20, .LANCHOR70
	strb	wzr, [x0, #:lo12:.LANCHOR156]
	adrp	x0, .LANCHOR157
	add	x19, x20, :lo12:.LANCHOR70
	str	wzr, [x0, #:lo12:.LANCHOR157]
	adrp	x0, .LANCHOR96
	strh	wzr, [x0, #:lo12:.LANCHOR96]
	mov	x0, x19
	bl	ftl_memset
	str	xzr, [x19, 8]
	mov	w0, -1
	strh	w0, [x20, #:lo12:.LANCHOR70]
	adrp	x0, .LANCHOR94
	adrp	x4, .LANCHOR102
	adrp	x20, .LANCHOR85
	ldrh	w1, [x0, #:lo12:.LANCHOR94]
	lsr	w2, w1, 1
	lsr	w0, w1, 2
	strh	w2, [x19, 38]
	adrp	x2, .LANCHOR87
	strh	w0, [x19, 36]
	adrp	x19, .LANCHOR79
	strh	wzr, [x2, #:lo12:.LANCHOR87]
	adrp	x2, .LANCHOR88
	ldrb	w3, [x19, #:lo12:.LANCHOR79]
	strh	wzr, [x2, #:lo12:.LANCHOR88]
	adrp	x2, .LANCHOR89
	strh	wzr, [x2, #:lo12:.LANCHOR89]
	mul	w2, w1, w3
	and	w2, w2, 65535
	sub	w5, w2, #32
	strh	w5, [x4, #:lo12:.LANCHOR102]
	adrp	x4, .LANCHOR100
	strh	w2, [x4, #:lo12:.LANCHOR100]
	adrp	x2, .LANCHOR93
	strh	w1, [x2, #:lo12:.LANCHOR93]
	adrp	x1, .LANCHOR158
	mov	w2, 4
	strh	w2, [x1, #:lo12:.LANCHOR158]
	adrp	x1, .LANCHOR69
	strh	w0, [x1, #:lo12:.LANCHOR69]
	ldrh	w0, [x20, #:lo12:.LANCHOR85]
	mul	w0, w0, w3
	lsl	w0, w0, 2
	bl	ftl_malloc
	adrp	x1, .LANCHOR159
	str	x0, [x1, #:lo12:.LANCHOR159]
	ldrb	w1, [x19, #:lo12:.LANCHOR79]
	ldrh	w0, [x20, #:lo12:.LANCHOR85]
	mul	w0, w0, w1
	lsl	w0, w0, 2
	bl	ftl_malloc
	adrp	x1, .LANCHOR160
	str	x0, [x1, #:lo12:.LANCHOR160]
	ldrh	w1, [x20, #:lo12:.LANCHOR85]
	ldrb	w0, [x19, #:lo12:.LANCHOR79]
	mul	w0, w1, w0
	bl	ftl_malloc
	adrp	x1, .LANCHOR82
	str	x0, [x1, #:lo12:.LANCHOR82]
	ldrb	w1, [x19, #:lo12:.LANCHOR79]
	ldrh	w0, [x20, #:lo12:.LANCHOR85]
	mul	w0, w0, w1
	lsl	w0, w0, 2
	bl	ftl_malloc
	adrp	x1, .LANCHOR76
	str	x0, [x1, #:lo12:.LANCHOR76]
	ldrb	w1, [x19, #:lo12:.LANCHOR79]
	ldrh	w0, [x20, #:lo12:.LANCHOR85]
	mul	w0, w0, w1
	lsl	w0, w0, 2
	bl	ftl_malloc
	adrp	x1, .LANCHOR161
	ldp	x19, x20, [sp, 16]
	str	x0, [x1, #:lo12:.LANCHOR161]
	adrp	x0, .LANCHOR98
	adrp	x1, .LANCHOR86
	ldp	x29, x30, [sp], 32
	ldrh	w0, [x0, #:lo12:.LANCHOR98]
	lsr	w0, w0, 2
	strh	w0, [x1, #:lo12:.LANCHOR86]
	ret
	.size	gc_init, .-gc_init
	.section	.text.ftl_free,"ax",@progbits
	.align	2
	.global	ftl_free
	.type	ftl_free, %function
ftl_free:
	b	free
	.size	ftl_free, .-ftl_free
	.section	.text.js_hash,"ax",@progbits
	.align	2
	.global	js_hash
	.type	js_hash, %function
js_hash:
	mov	x4, x0
	mov	w0, 42982
	mov	x3, 0
	movk	w0, 0x47c6, lsl 16
.L1553:
	cmp	w1, w3
	bhi	.L1554
	ret
.L1554:
	lsr	w2, w0, 2
	ldrb	w5, [x4, x3]
	add	w2, w2, w0, lsl 5
	add	x3, x3, 1
	add	w2, w2, w5
	eor	w0, w0, w2
	b	.L1553
	.size	js_hash, .-js_hash
	.section	.text.ftl_debug_info_fill,"ax",@progbits
	.align	2
	.global	ftl_debug_info_fill
	.type	ftl_debug_info_fill, %function
ftl_debug_info_fill:
	adrp	x3, .LANCHOR131
	ldrb	w3, [x3, #:lo12:.LANCHOR131]
	cmp	w3, 8
	bls	.L1559
	and	w0, w0, 255
	cmp	x2, 0
	ccmp	w0, 2, 0, ne
	bne	.L1557
	stp	x29, x30, [sp, -16]!
	mov	x6, x1
	mov	w1, 21320
	mov	x0, x2
	add	x29, sp, 0
	movk	w1, 0x4841, lsl 16
	str	w1, [x6]
	mov	w1, 1024
	bl	js_hash
	str	w0, [x6, 4]
	mov	w0, 0
	ldp	x29, x30, [sp], 16
	ret
.L1557:
	stp	wzr, wzr, [x1]
.L1559:
	mov	w0, 0
	ret
	.size	ftl_debug_info_fill, .-ftl_debug_info_fill
	.section	.text.timer_get_time,"ax",@progbits
	.align	2
	.global	timer_get_time
	.type	timer_get_time, %function
timer_get_time:
	mov	w0, 0
	ret
	.size	timer_get_time, .-timer_get_time
	.section	.text.FlashCs123Init,"ax",@progbits
	.align	2
	.global	FlashCs123Init
	.type	FlashCs123Init, %function
FlashCs123Init:
	ret
	.size	FlashCs123Init, .-FlashCs123Init
	.section	.text.rk_nand_de_init,"ax",@progbits
	.align	2
	.global	rk_nand_de_init
	.type	rk_nand_de_init, %function
rk_nand_de_init:
	b	zftl_flash_de_init
	.size	rk_nand_de_init, .-rk_nand_de_init
	.section	.text.ftl_get_density,"ax",@progbits
	.align	2
	.global	ftl_get_density
	.type	ftl_get_density, %function
ftl_get_density:
	and	w0, w0, 255
	b	zftl_get_density
	.size	ftl_get_density, .-ftl_get_density
	.section	.text.ftl_get_capacity,"ax",@progbits
	.align	2
	.global	ftl_get_capacity
	.type	ftl_get_capacity, %function
ftl_get_capacity:
	adrp	x0, .LANCHOR67
	ldr	w0, [x0, #:lo12:.LANCHOR67]
	ret
	.size	ftl_get_capacity, .-ftl_get_capacity
	.section	.text.rknand_print_hex,"ax",@progbits
	.align	2
	.global	rknand_print_hex
	.type	rknand_print_hex, %function
rknand_print_hex:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x21, x22, [sp, 32]
	adrp	x21, .LC99
	stp	x23, x24, [sp, 48]
	mov	x22, x1
	stp	x25, x26, [sp, 64]
	mov	w24, w2
	stp	x27, x28, [sp, 80]
	adrp	x25, .LC98
	mov	x27, x0
	uxtw	x26, w3
	add	x25, x25, :lo12:.LC98
	add	x21, x21, :lo12:.LC99
	stp	x19, x20, [sp, 16]
	mov	w23, 0
	mov	x19, 0
	mov	w20, 0
	adrp	x28, .LC100
.L1568:
	cmp	x26, x19
	bne	.L1574
	ldp	x19, x20, [sp, 16]
	adrp	x1, .LC100
	ldp	x21, x22, [sp, 32]
	add	x1, x1, :lo12:.LC100
	ldp	x23, x24, [sp, 48]
	adrp	x0, .LC101
	ldp	x25, x26, [sp, 64]
	add	x0, x0, :lo12:.LC101
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 96
	b	printf
.L1574:
	cbnz	w20, .L1569
	mov	w3, w23
	mov	x2, x22
	mov	x1, x27
	mov	x0, x25
	bl	printf
.L1569:
	cmp	w24, 4
	bne	.L1570
	ldr	w1, [x22, x19, lsl 2]
.L1576:
	mov	x0, x21
	add	w20, w20, 1
	bl	printf
	cmp	w20, 15
	bls	.L1573
	mov	w20, 0
	add	x1, x28, :lo12:.LC100
	adrp	x0, .LC101
	add	x0, x0, :lo12:.LC101
	bl	printf
.L1573:
	add	x19, x19, 1
	add	w23, w23, w24
	b	.L1568
.L1570:
	cmp	w24, 2
	bne	.L1572
	ldrsh	w1, [x22, x19, lsl 1]
	b	.L1576
.L1572:
	ldrb	w1, [x22, x19]
	b	.L1576
	.size	rknand_print_hex, .-rknand_print_hex
	.section	.text.hynix_get_read_retry_default,"ax",@progbits
	.align	2
	.global	hynix_get_read_retry_default
	.type	hynix_get_read_retry_default, %function
hynix_get_read_retry_default:
	stp	x29, x30, [sp, -144]!
	mov	w2, -83
	mov	w1, -82
	add	x29, sp, 0
	stp	x25, x26, [sp, 64]
	mov	w25, w0
	adrp	x0, .LANCHOR6
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	cmp	w25, 2
	ldr	x26, [x0, #:lo12:.LANCHOR6]
	mov	w0, -84
	stp	x19, x20, [sp, 16]
	stp	x27, x28, [sp, 80]
	add	x24, x26, 128
	add	x21, x26, 112
	strb	w0, [x26, 128]
	mov	w0, -81
	strb	w25, [x26, 112]
	strb	w2, [x26, 129]
	strb	w1, [x26, 130]
	strb	w0, [x26, 131]
	bne	.L1578
	mov	w0, -89
	strb	w0, [x21, 16]
	adrp	x0, .LANCHOR162+17
	mov	w1, -9
	strb	w1, [x0, #:lo12:.LANCHOR162+17]
.L1642:
	mov	w27, 7
	b	.L1685
.L1578:
	cmp	w25, 3
	bne	.L1580
	mov	x5, 0
.L1581:
	sub	w0, w5, #80
	strb	w0, [x24, x5]
	add	x5, x5, 1
	cmp	x5, 8
	bne	.L1581
	mov	w27, w5
	mov	w28, w5
.L1579:
	sub	w0, w25, #1
	cmp	w0, 1
	bhi	.L1587
	adrp	x25, .LANCHOR23
	adrp	x26, .LANCHOR29
	add	x25, x25, :lo12:.LANCHOR23
	add	x26, x26, :lo12:.LANCHOR29
	mov	w23, 0
	mov	w5, 55
.L1588:
	ldrb	w0, [x25]
	cmp	w0, w23
	bhi	.L1594
.L1595:
	strb	w28, [x21, 1]
	strb	w27, [x21, 2]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 144
	ret
.L1580:
	cmp	w25, 4
	bne	.L1582
	mov	w5, -52
	strb	w5, [x26, 128]
	mov	w5, -65
	strb	w5, [x26, 129]
	mov	w5, -86
	strb	w5, [x26, 130]
	mov	w5, -85
	mov	w27, 8
	strb	w5, [x26, 131]
	mov	w28, w27
	mov	w5, -51
	strb	w2, [x26, 133]
	strb	w5, [x26, 132]
	strb	w1, [x26, 134]
	strb	w0, [x26, 135]
	b	.L1579
.L1582:
	cmp	w25, 5
	bne	.L1583
	mov	w0, 56
	strb	w0, [x26, 128]
	mov	w0, 57
	strb	w0, [x26, 129]
	mov	w0, 58
	mov	w27, 8
	strb	w0, [x26, 130]
	mov	w0, 59
	strb	w0, [x26, 131]
.L1685:
	mov	w28, 4
	b	.L1579
.L1583:
	cmp	w25, 6
	bne	.L1584
	mov	w0, 14
	strb	w0, [x26, 128]
	mov	w0, 15
	strb	w0, [x26, 129]
	mov	w0, 16
	mov	w27, 12
	strb	w0, [x26, 130]
	mov	w0, 17
	strb	w0, [x26, 131]
	b	.L1685
.L1584:
	cmp	w25, 7
	bne	.L1585
	mov	x0, 0
.L1586:
	sub	w1, w0, #80
	strb	w1, [x24, x0]
	add	x0, x0, 1
	cmp	x0, 8
	bne	.L1586
	mov	w0, -44
	mov	w27, 12
	strb	w0, [x26, 136]
	mov	w28, 10
	mov	w0, -43
	strb	w0, [x26, 137]
	b	.L1579
.L1585:
	cmp	w25, 8
	bne	.L1642
	mov	w0, 6
	strb	w0, [x26, 128]
	mov	w0, 7
	strb	w0, [x26, 129]
	mov	w0, 9
	strb	w25, [x26, 130]
	strb	w0, [x26, 131]
	mov	w27, 50
	mov	w0, 10
	mov	w28, 5
	strb	w0, [x26, 132]
	b	.L1579
.L1594:
	ldrb	w0, [x26, w23, sxtw]
	mov	x1, 32
	mov	w19, 160
	mov	x20, 0
	umaddl	x19, w19, w0, x1
	adrp	x1, .LANCHOR7
	ubfiz	x0, x0, 8, 8
	ldr	x22, [x1, #:lo12:.LANCHOR7]
	add	x19, x21, x19
	add	x22, x22, x0
.L1589:
	str	w5, [x22, 2056]
	str	w5, [x29, 136]
	ldrb	w0, [x24, x20]
	str	w0, [x22, 2052]
	mov	x0, 1
	bl	udelay
	ldr	w0, [x22, 2048]
	strb	w0, [x19, x20]
	add	x20, x20, 1
	cmp	w28, w20, uxtb
	ldr	w5, [x29, 136]
	bhi	.L1589
	adrp	x2, .LANCHOR162
	add	x2, x2, :lo12:.LANCHOR162
	mov	x0, 0
.L1592:
	add	x7, x19, x0
	add	x4, x2, x0
	mov	x1, 1
.L1591:
	lsl	x3, x1, 2
	lsl	x8, x1, 3
	ldrb	w10, [x19, x0]
	add	x1, x1, 1
	cmp	x1, 7
	ldrb	w3, [x4, x3]
	add	w3, w3, w10
	strb	w3, [x7, x8]
	bne	.L1591
	add	x0, x0, 1
	cmp	x0, 4
	bne	.L1592
	add	w23, w23, 1
	strb	wzr, [x19, 16]
	strb	wzr, [x19, 24]
	and	w23, w23, 255
	strb	wzr, [x19, 32]
	strb	wzr, [x19, 40]
	strb	wzr, [x19, 48]
	strb	wzr, [x19, 41]
	strb	wzr, [x19, 49]
	b	.L1588
.L1587:
	sub	w0, w25, #3
	cmp	w0, 5
	bhi	.L1595
	mul	w24, w27, w28
	sub	w22, w28, #1
	and	x22, x22, 255
	mov	w20, 0
	asr	w23, w24, 1
	lsl	w0, w24, 4
	str	w0, [x29, 128]
	lsl	w0, w23, 1
	str	w0, [x29, 132]
	sbfiz	x0, x23, 1, 32
	sub	w24, w25, #5
	str	x0, [x29, 136]
	adrp	x0, .LANCHOR23
	add	x0, x0, :lo12:.LANCHOR23
	str	x0, [x29, 120]
	add	x0, x22, 1
	str	x0, [x29, 112]
.L1596:
	ldr	x0, [x29, 120]
	ldrb	w0, [x0]
	cmp	w0, w20
	bls	.L1595
	adrp	x0, .LANCHOR29
	add	x0, x0, :lo12:.LANCHOR29
	mov	w19, 160
	ldrb	w22, [x0, w20, sxtw]
	mov	w0, w22
	bl	zftl_flash_exit_slc_mode
	mov	x0, 32
	ubfiz	x2, x22, 8, 8
	mov	w1, 255
	str	w1, [x29, 108]
	nop // between mem op and mult-accumulate
	umaddl	x19, w19, w22, x0
	adrp	x0, .LANCHOR7
	ldr	x0, [x0, #:lo12:.LANCHOR7]
	add	x19, x21, x19
	add	x22, x0, x2
	str	w1, [x22, 2056]
	bl	nandc_wait_flash_ready
	cmp	w25, 8
	ldr	w1, [x29, 108]
	bne	.L1597
	mov	w0, 120
	str	w0, [x22, 2056]
	str	wzr, [x22, 2052]
	mov	w0, 23
	str	wzr, [x22, 2052]
	mov	w1, 25
	str	wzr, [x22, 2052]
	add	x19, x26, 144
	str	w0, [x22, 2056]
	mov	w0, 4
	str	w0, [x22, 2056]
	str	w1, [x22, 2056]
	mov	w1, 218
	str	w1, [x22, 2056]
	mov	w1, 21
	str	wzr, [x22, 2056]
	str	wzr, [x22, 2052]
	str	wzr, [x22, 2052]
	str	w1, [x22, 2052]
.L1688:
	str	w0, [x22, 2052]
	mov	w0, 48
	str	wzr, [x22, 2052]
	str	w0, [x22, 2056]
	bl	nandc_wait_flash_ready
	cmp	w24, 1
	ccmp	w25, 8, 4, hi
	beq	.L1643
	cmp	w25, 7
	mov	w0, 32
	mov	w1, 2
	csel	w1, w1, w0, ne
.L1604:
	adrp	x8, .LANCHOR163
	mov	x7, 0
	ldr	x0, [x8, #:lo12:.LANCHOR163]
.L1605:
	ldr	w10, [x22, 2048]
	strb	w10, [x0, x7]
	add	x7, x7, 1
	cmp	w1, w7, uxtb
	bhi	.L1605
	cmp	w25, 8
	bne	.L1606
	mov	w1, 0
.L1608:
	ldrb	w7, [x0]
	cmp	w7, 50
	beq	.L1607
	ldrb	w7, [x0, 1]
	cmp	w7, 5
	beq	.L1607
	add	w1, w1, 1
	add	x0, x0, 4
	and	w1, w1, 255
	cmp	w1, 8
	bne	.L1608
.L1609:
	adrp	x0, .LC102
	mov	w1, 0
	add	x0, x0, :lo12:.LC102
	bl	printf
.L1611:
	b	.L1611
.L1597:
	mov	w0, 54
	str	w0, [x22, 2056]
	cmp	w25, 4
	bne	.L1599
	mov	w0, 64
	str	w1, [x22, 2052]
	str	w0, [x22, 2048]
	mov	w0, 204
.L1686:
	str	w0, [x22, 2052]
	mov	w0, 77
	b	.L1687
.L1599:
	cmp	w24, 1
	bhi	.L1601
	ldrb	w0, [x26, 128]
	str	w0, [x22, 2052]
	mov	w0, 82
.L1687:
	str	w0, [x22, 2048]
.L1600:
	mov	w0, 22
	str	w0, [x22, 2056]
	mov	w0, 23
	str	w0, [x22, 2056]
	mov	w0, 4
	str	w0, [x22, 2056]
	mov	w0, 25
	str	w0, [x22, 2056]
	str	wzr, [x22, 2056]
	cmp	w25, 6
	str	wzr, [x22, 2052]
	str	wzr, [x22, 2052]
	bne	.L1602
	mov	w0, 31
	str	w0, [x22, 2052]
.L1603:
	mov	w0, 2
	b	.L1688
.L1601:
	cmp	w25, 7
	bne	.L1600
	mov	w0, 174
	str	w0, [x22, 2052]
	str	wzr, [x22, 2048]
	mov	w0, 176
	b	.L1686
.L1602:
	str	wzr, [x22, 2052]
	b	.L1603
.L1643:
	mov	w1, 16
	b	.L1604
.L1607:
	cmp	w1, 6
	bhi	.L1609
.L1610:
	ldr	x7, [x8, #:lo12:.LANCHOR163]
	mov	x0, 0
.L1620:
	ldr	w1, [x29, 128]
	cmp	w1, w0
	bgt	.L1621
	ldr	x1, [x8, #:lo12:.LANCHOR163]
	mov	w10, 8
	ldr	x0, [x29, 136]
	add	x8, x1, x0
.L1623:
	mov	x0, 0
.L1622:
	ldrh	w11, [x8, x0, lsl 1]
	mvn	w11, w11
	strh	w11, [x8, x0, lsl 1]
	add	x0, x0, 1
	cmp	w23, w0
	bgt	.L1622
	ldr	w0, [x29, 132]
	subs	w10, w10, #1
	add	x8, x8, x0, uxtw 1
	bne	.L1623
	mov	x10, x1
	mov	w11, 0
	mov	w16, 1
.L1624:
	mov	w0, 0
	mov	w8, 0
.L1628:
	mov	x14, x10
	lsl	w15, w16, w8
	mov	w13, 16
	mov	w12, 0
.L1626:
	ldrh	w17, [x14]
	ldr	x2, [x29, 136]
	bics	wzr, w15, w17
	cinc	w12, w12, eq
	add	x14, x14, x2
	subs	w13, w13, #1
	bne	.L1626
	cmp	w12, 8
	bls	.L1627
	orr	w0, w0, w15
	and	w0, w0, 65535
.L1627:
	add	w8, w8, 1
	cmp	w8, 16
	bne	.L1628
	strh	w0, [x10], 2
	add	w11, w11, 1
	cmp	w23, w11
	bgt	.L1624
	mov	x0, 0
	mov	w8, 0
.L1631:
	ldr	w10, [x1, x0]
	add	x0, x0, 4
	cmp	w10, 0
	cinc	w8, w8, eq
	cmp	x0, 32
	bne	.L1631
	cmp	w8, 7
	ble	.L1632
	mov	w3, 1024
	mov	w2, 1
	adrp	x0, .LC103
	add	x0, x0, :lo12:.LC103
	bl	rknand_print_hex
	adrp	x0, .LC102
	mov	w1, 0
	add	x0, x0, :lo12:.LC102
	bl	printf
.L1633:
	b	.L1633
.L1606:
	cmp	w25, 7
	bne	.L1612
	mov	w1, 0
.L1614:
	ldrb	w7, [x0]
	cmp	w7, 12
	beq	.L1613
	ldrb	w7, [x0, 1]
	cmp	w7, 10
	beq	.L1613
	add	w1, w1, 1
	add	x0, x0, 4
	and	w1, w1, 255
	cmp	w1, 8
	bne	.L1614
.L1615:
	adrp	x0, .LC102
	mov	w1, 0
	add	x0, x0, :lo12:.LC102
	bl	printf
.L1616:
	b	.L1616
.L1613:
	cmp	w1, 6
	bls	.L1610
	b	.L1615
.L1612:
	cmp	w25, 6
	bne	.L1610
	mov	x1, 0
.L1617:
	ldrb	w7, [x0, x1]
	cmp	w7, 12
	beq	.L1610
	add	x7, x0, x1
	ldrb	w7, [x7, 8]
	cmp	w7, 4
	beq	.L1610
	add	x1, x1, 1
	cmp	x1, 8
	bne	.L1617
	adrp	x0, .LC102
	mov	w1, 0
	add	x0, x0, :lo12:.LC102
	bl	printf
.L1619:
	b	.L1619
.L1621:
	ldr	w1, [x22, 2048]
	strb	w1, [x7, x0]
	add	x0, x0, 1
	b	.L1620
.L1632:
	cmp	w25, 6
	beq	.L1645
	cmp	w25, 7
	beq	.L1646
	cmp	w25, 8
	mov	x1, 5
	mov	x0, 8
	csel	x0, x0, x1, ne
.L1634:
	mov	w8, 0
.L1635:
	mov	x1, 0
.L1636:
	ldrb	w10, [x7, x1]
	strb	w10, [x19, x1]
	add	x1, x1, 1
	cmp	w28, w1, uxtb
	bhi	.L1636
	ldr	x1, [x29, 112]
	add	w8, w8, 1
	add	x19, x19, x0
	cmp	w27, w8
	add	x7, x7, x1
	bgt	.L1635
	mov	w19, 255
	str	w19, [x22, 2056]
	bl	nandc_wait_flash_ready
	cmp	w24, 1
	bhi	.L1638
	mov	w0, 54
	str	w0, [x22, 2056]
	ldrb	w0, [x26, 128]
	str	w0, [x22, 2052]
	str	wzr, [x22, 2048]
	mov	w0, 22
	str	w0, [x22, 2056]
	mov	w0, 48
	str	wzr, [x22, 2056]
	str	wzr, [x22, 2052]
	str	wzr, [x22, 2052]
	str	w19, [x22, 2052]
	str	w19, [x22, 2052]
	str	w19, [x22, 2052]
.L1689:
	str	w0, [x22, 2056]
	add	w20, w20, 1
	and	w20, w20, 255
	bl	nandc_wait_flash_ready
	b	.L1596
.L1645:
	mov	x0, 4
	b	.L1634
.L1646:
	mov	x0, 10
	b	.L1634
.L1638:
	cmp	w25, 8
	bne	.L1640
	mov	w0, 190
	b	.L1689
.L1640:
	mov	w0, 56
	b	.L1689
	.size	hynix_get_read_retry_default, .-hynix_get_read_retry_default
	.section	.text.flash_get_read_retry_tbl,"ax",@progbits
	.align	2
	.global	flash_get_read_retry_tbl
	.type	flash_get_read_retry_tbl, %function
flash_get_read_retry_tbl:
	adrp	x0, .LANCHOR32+19
	ldrb	w0, [x0, #:lo12:.LANCHOR32+19]
	sub	w1, w0, #1
	and	w1, w1, 255
	cmp	w1, 7
	bhi	.L1690
	b	hynix_get_read_retry_default
.L1690:
	ret
	.size	flash_get_read_retry_tbl, .-flash_get_read_retry_tbl
	.section	.text.nandc_xfer_done,"ax",@progbits
	.align	2
	.global	nandc_xfer_done
	.type	nandc_xfer_done, %function
nandc_xfer_done:
	stp	x29, x30, [sp, -80]!
	adrp	x0, .LANCHOR164
	adrp	x1, .LANCHOR27
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	adrp	x19, .LANCHOR7
	ldrb	w1, [x1, #:lo12:.LANCHOR27]
	stp	x21, x22, [sp, 32]
	strb	wzr, [x0, #:lo12:.LANCHOR164]
	cmp	w1, 9
	str	x23, [sp, 48]
	bne	.L1693
	ldr	x20, [x19, #:lo12:.LANCHOR7]
	mov	x21, x0
	ldr	w0, [x20, 16]
	str	w0, [x29, 64]
	ldr	w0, [x20, 48]
	tbnz	x0, 1, .L1694
	adrp	x22, .LC106
	adrp	x23, .LC107
	add	x22, x22, :lo12:.LC106
	add	x23, x23, :lo12:.LC107
	mov	w21, 0
.L1695:
	ldr	w0, [x29, 64]
	tbnz	x0, 20, .L1697
	ldr	x0, [x19, #:lo12:.LANCHOR7]
	add	w21, w21, 1
	tst	x21, 16777215
	ldr	w0, [x0, 16]
	str	w0, [x29, 64]
	bne	.L1695
	ldr	w2, [x29, 64]
	mov	w1, w21
	ldr	w3, [x20, 64]
	mov	x0, x22
	ubfx	x3, x3, 16, 6
	bl	printf
	ldr	x1, [x19, #:lo12:.LANCHOR7]
	mov	w3, 64
	mov	w2, 4
	mov	x0, x23
	bl	rknand_print_hex
	b	.L1695
.L1696:
	ldr	w0, [x29, 64]
	add	w1, w1, 1
	ubfx	x0, x0, 22, 6
	cmp	w1, w0, lsl 12
	bne	.L1698
	ldr	w2, [x20, 64]
	adrp	x0, .LC105
	ldr	w3, [x29, 64]
	add	x0, x0, :lo12:.LC105
	ubfx	x2, x2, 16, 5
	ubfx	x3, x3, 22, 6
	bl	printf
	ldr	w0, [x29, 72]
	mov	w0, 1
	strb	w0, [x21, #:lo12:.LANCHOR164]
.L1697:
	adrp	x0, .LANCHOR52+32
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	str	wzr, [x0, #:lo12:.LANCHOR52+32]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 80
	ret
.L1694:
	mov	w1, 0
.L1698:
	ldr	w2, [x20, 64]
	ldr	w0, [x29, 64]
	ubfx	x2, x2, 16, 6
	ubfx	x0, x0, 22, 6
	cmp	w2, w0
	bge	.L1697
	ldr	w0, [x20]
	str	w0, [x29, 72]
	ldr	w0, [x29, 72]
	tbz	x0, 13, .L1696
	ldr	w0, [x29, 72]
	tbz	x0, 17, .L1696
	ldr	w1, [x29, 72]
	adrp	x0, .LC104
	add	x0, x0, :lo12:.LC104
	ubfx	x1, x1, 17, 1
.L1727:
	bl	printf
	b	.L1697
.L1693:
	ldr	x20, [x19, #:lo12:.LANCHOR7]
	mov	w21, 0
	ldr	w0, [x20, 8]
	str	w0, [x29, 64]
	ldr	w0, [x20, 16]
	tbnz	x0, 1, .L1703
	adrp	x22, .LC106
	adrp	x23, .LC107
	add	x22, x22, :lo12:.LC106
	add	x23, x23, :lo12:.LC107
.L1704:
	ldr	w0, [x29, 64]
	tbnz	x0, 20, .L1697
	ldr	x0, [x19, #:lo12:.LANCHOR7]
	add	w21, w21, 1
	tst	x21, 16777215
	ldr	w0, [x0, 8]
	str	w0, [x29, 64]
	bne	.L1704
	ldr	w2, [x29, 64]
	mov	w1, w21
	ldr	w3, [x20, 28]
	mov	x0, x22
	ubfx	x3, x3, 16, 5
	bl	printf
	ldr	x1, [x19, #:lo12:.LANCHOR7]
	mov	w3, 64
	mov	w2, 4
	mov	x0, x23
	bl	rknand_print_hex
	b	.L1704
.L1703:
	adrp	x22, .LC105
	adrp	x23, .LC107
	add	x22, x22, :lo12:.LC105
	add	x23, x23, :lo12:.LC107
.L1705:
	ldr	w1, [x20, 28]
	ldr	w0, [x29, 64]
	ubfx	x1, x1, 16, 5
	ubfx	x0, x0, 22, 6
	cmp	w1, w0
	bge	.L1697
	ldr	x0, [x19, #:lo12:.LANCHOR7]
	ldr	w0, [x0]
	str	w0, [x29, 72]
	ldr	w0, [x29, 72]
	tbz	x0, 13, .L1706
	ldr	w0, [x29, 72]
	tbz	x0, 17, .L1706
	adrp	x0, .LC108
	ldr	w1, [x29, 72]
	add	x0, x0, :lo12:.LC108
	b	.L1727
.L1706:
	add	w21, w21, 1
	tst	x21, 16777215
	bne	.L1705
	ldr	w2, [x20, 28]
	mov	w1, w21
	ldr	w3, [x29, 64]
	mov	x0, x22
	ubfx	x2, x2, 16, 5
	ubfx	x3, x3, 22, 6
	bl	printf
	ldr	x1, [x19, #:lo12:.LANCHOR7]
	mov	w3, 64
	mov	w2, 4
	mov	x0, x23
	bl	rknand_print_hex
	b	.L1705
	.size	nandc_xfer_done, .-nandc_xfer_done
	.section	.text.nandc_xfer,"ax",@progbits
	.align	2
	.global	nandc_xfer
	.type	nandc_xfer, %function
nandc_xfer:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	and	w19, w2, 255
	mov	x20, x3
	stp	x21, x22, [sp, 32]
	mov	x3, x4
	and	w22, w1, 255
	mov	x2, x20
	mov	w1, w19
	mov	w0, w22
	mov	x21, x4
	bl	nandc_xfer_start
	mov	w0, w22
	bl	nandc_xfer_done
	cbnz	w22, .L1747
	adrp	x0, .LANCHOR27
	ldrb	w0, [x0, #:lo12:.LANCHOR27]
	cmp	w0, 9
	bne	.L1730
	adrp	x22, .LANCHOR7
	lsr	w19, w19, 2
	mov	w3, 1
	mov	w2, 0
	ldr	x5, [x22, #:lo12:.LANCHOR7]
	mov	w0, 0
.L1731:
	cmp	w2, w19
	bcc	.L1735
	ldr	w19, [x5]
	cmp	w3, 0
	mov	w1, 512
	csel	w0, w0, w1, eq
	mov	w1, 8192
	movk	w1, 0x2, lsl 16
	and	w1, w19, w1
	cmp	w1, 139264
	bne	.L1737
	mov	w1, w19
	adrp	x0, .LC109
	add	x0, x0, :lo12:.LC109
	bl	printf
	ldr	x0, [x22, #:lo12:.LANCHOR7]
	orr	w19, w19, 131072
	str	w19, [x0]
	mov	w0, -1
.L1737:
	tbz	x19, 13, .L1738
	adrp	x1, .LANCHOR164
	ldrb	w1, [x1, #:lo12:.LANCHOR164]
	cbz	w1, .L1738
	mov	w1, w19
	adrp	x0, .LC110
	add	x0, x0, :lo12:.LC110
	bl	printf
	ldr	x0, [x22, #:lo12:.LANCHOR7]
	mov	w1, 1
	str	w1, [x0, 16]
.L1766:
	mov	w0, -1
.L1729:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
.L1735:
	uxtw	x1, w2
	add	x1, x1, 84
	ldr	w1, [x5, x1, lsl 2]
	str	w1, [x29, 56]
	ldr	w1, [x29, 56]
	ldr	w4, [x29, 56]
	ubfx	x4, x4, 26, 1
	and	w1, w4, w1, lsr 10
	and	w3, w3, w1
	ldr	w1, [x29, 56]
	tbnz	x1, 2, .L1749
	ldr	w1, [x29, 56]
	tbnz	x1, 18, .L1749
	ldr	w4, [x29, 56]
	ldr	w1, [x29, 56]
	ubfx	x4, x4, 3, 7
	ubfx	x1, x1, 19, 7
	cmp	w4, w1
	ldr	w1, [x29, 56]
	ble	.L1733
	ubfx	x1, x1, 3, 7
.L1734:
	cmp	w0, w1
	csel	w0, w0, w1, cs
.L1732:
	add	w2, w2, 1
	b	.L1731
.L1733:
	ubfx	x1, x1, 19, 7
	b	.L1734
.L1749:
	mov	w0, -1
	b	.L1732
.L1730:
	adrp	x0, .LANCHOR49
	lsr	w4, w19, 1
	mov	w3, 64
	mov	w1, 1
	ldrb	w0, [x0, #:lo12:.LANCHOR49]
	mov	w2, 0
	adrp	x6, .LANCHOR52
	cmp	w0, 25
	mov	w0, 128
	csel	w3, w3, w0, cc
	mov	w0, 0
.L1740:
	add	w5, w3, w0
	cmp	w2, w4
	bcc	.L1741
	adrp	x22, .LANCHOR7
	lsr	w19, w19, 2
	mov	w3, 0
	mov	w0, 0
	ldr	x4, [x22, #:lo12:.LANCHOR7]
.L1742:
	cmp	w3, w19
	bcc	.L1746
	str	wzr, [x4, 16]
	mov	w1, 8192
	movk	w1, 0x2, lsl 16
	ldr	w19, [x4]
	and	w1, w19, w1
	cmp	w1, 139264
	bne	.L1738
	mov	w1, w19
	adrp	x0, .LC111
	add	x0, x0, :lo12:.LC111
	bl	printf
	ldr	x0, [x22, #:lo12:.LANCHOR7]
	orr	w19, w19, 131072
	str	w19, [x0]
	b	.L1766
.L1741:
	ldr	x7, [x6, #:lo12:.LANCHOR52]
	and	x0, x0, 4294967292
	ldr	w0, [x7, x0]
	lsl	w7, w2, 2
	add	w2, w2, 1
	strb	w0, [x21, x7]
	lsr	w7, w0, 8
	strb	w7, [x21, w1, uxtw]
	add	w7, w1, 1
	lsr	w8, w0, 16
	lsr	w0, w0, 24
	strb	w8, [x21, x7]
	add	w7, w1, 2
	add	w1, w1, 4
	strb	w0, [x21, x7]
	mov	w0, w5
	b	.L1740
.L1746:
	uxtw	x1, w3
	add	x1, x1, 8
	ldr	w1, [x4, x1, lsl 2]
	str	w1, [x29, 56]
	ldr	w1, [x29, 56]
	tbnz	x1, 2, .L1752
	ldr	w1, [x29, 56]
	tbnz	x1, 15, .L1752
	ldr	w2, [x29, 56]
	ubfx	x6, x2, 3, 5
	ldr	w2, [x29, 56]
	ldr	w1, [x29, 56]
	ubfx	x2, x2, 27, 1
	ubfx	x5, x1, 16, 5
	ldr	w1, [x29, 56]
	orr	w2, w6, w2, lsl 5
	ubfx	x1, x1, 29, 1
	orr	w1, w5, w1, lsl 5
	cmp	w2, w1
	ldr	w1, [x29, 56]
	bls	.L1744
	ubfx	x2, x1, 3, 5
	ldr	w1, [x29, 56]
	ubfx	x1, x1, 27, 1
.L1765:
	orr	w1, w2, w1, lsl 5
	cmp	w0, w1
	csel	w0, w0, w1, cs
.L1743:
	add	w3, w3, 1
	b	.L1742
.L1744:
	ubfx	x2, x1, 16, 5
	ldr	w1, [x29, 56]
	ubfx	x1, x1, 29, 1
	b	.L1765
.L1752:
	mov	w0, -1
	b	.L1743
.L1738:
	cmn	w0, #1
	beq	.L1729
	ldr	w1, [x21]
	cmn	w1, #1
	bne	.L1729
	ldr	w1, [x21, 4]
	cmn	w1, #1
	bne	.L1729
	ldr	w1, [x20]
	cmn	w1, #1
	mov	w1, 512
	csel	w0, w0, w1, ne
	b	.L1729
.L1747:
	mov	w0, 0
	b	.L1729
	.size	nandc_xfer, .-nandc_xfer
	.section	.text.flash_read_page,"ax",@progbits
	.align	2
	.global	flash_read_page
	.type	flash_read_page, %function
flash_read_page:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x21, x22, [sp, 32]
	and	w21, w0, 255
	adrp	x0, .LANCHOR7
	stp	x19, x20, [sp, 16]
	mov	w19, 24
	stp	x23, x24, [sp, 48]
	ldr	x20, [x0, #:lo12:.LANCHOR7]
	adrp	x0, .LANCHOR31
	stp	x25, x26, [sp, 64]
	mov	x24, x2
	ldrb	w0, [x0, #:lo12:.LANCHOR31]
	mov	x25, x3
	mov	w23, w4
	ubfx	x22, x1, 24, 2
	sub	w0, w19, w0
	mov	w19, 1
	adrp	x26, .LANCHOR21
	lsl	w19, w19, w0
	sub	w19, w19, #1
	and	w19, w19, w1
	bl	nandc_wait_flash_ready
	mov	w0, w21
	bl	nandc_cs
	cbnz	w22, .L1768
	mov	w0, w21
	bl	zftl_flash_enter_slc_mode
.L1769:
	ldr	x1, [x26, #:lo12:.LANCHOR21]
	ldrb	w0, [x1, 7]
	cmp	w0, 1
	bne	.L1771
	ldrb	w0, [x1, 12]
	cmp	w0, 2
	bne	.L1771
	sxtw	x0, w21
	mov	w2, 38
	add	x0, x0, 8
	add	x0, x20, x0, lsl 8
	str	w2, [x0, 8]
.L1771:
	ubfiz	x0, x21, 8, 8
	add	x20, x20, x0
	and	w0, w19, 255
	str	wzr, [x20, 2056]
	str	wzr, [x20, 2052]
	str	wzr, [x20, 2052]
	str	w0, [x20, 2052]
	lsr	w0, w19, 8
	str	w0, [x20, 2052]
	lsr	w0, w19, 16
	str	w0, [x20, 2052]
	adrp	x0, .LANCHOR30
	ldrb	w0, [x0, #:lo12:.LANCHOR30]
	cbz	w0, .L1772
	lsr	w0, w19, 24
	str	w0, [x20, 2052]
.L1772:
	mov	w0, 48
	str	w0, [x20, 2056]
	ldrb	w0, [x1, 12]
	cmp	w0, 3
	bne	.L1773
	cbz	w22, .L1773
	adrp	x0, .LANCHOR35
	ldrb	w0, [x0, #:lo12:.LANCHOR35]
	cbnz	w0, .L1773
	adrp	x0, .LANCHOR36
	ldrb	w0, [x0, #:lo12:.LANCHOR36]
	cbnz	w0, .L1773
	add	w19, w19, w19, lsl 1
	sub	w0, w19, #1
	add	w0, w0, w22
.L1782:
	bl	nandc_set_seed
	bl	nandc_wait_flash_ready
	mov	w0, 5
	str	w0, [x20, 2056]
	str	wzr, [x20, 2052]
	mov	w0, 224
	str	wzr, [x20, 2052]
	mov	w2, w23
	str	w0, [x20, 2056]
	mov	x4, x25
	mov	x3, x24
	mov	w1, 0
	mov	w0, w21
	bl	nandc_xfer
	mov	w2, w0
	bl	nandc_de_cs.constprop.32
	mov	w0, w2
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
.L1768:
	ldr	x0, [x26, #:lo12:.LANCHOR21]
	ldrb	w0, [x0, 12]
	cmp	w0, 3
	bne	.L1770
	adrp	x0, .LANCHOR35
	ldrb	w0, [x0, #:lo12:.LANCHOR35]
	cbnz	w0, .L1770
	adrp	x0, .LANCHOR36
	ldrb	w0, [x0, #:lo12:.LANCHOR36]
	cbnz	w0, .L1770
	sxtw	x0, w21
	add	x0, x0, 8
	add	x0, x20, x0, lsl 8
	str	w22, [x0, 8]
	b	.L1769
.L1770:
	mov	w0, w21
	bl	zftl_flash_exit_slc_mode
	b	.L1769
.L1773:
	mov	w0, w19
	b	.L1782
	.size	flash_read_page, .-flash_read_page
	.section	.text.micron_read_retrial,"ax",@progbits
	.align	2
	.global	micron_read_retrial
	.type	micron_read_retrial, %function
micron_read_retrial:
	stp	x29, x30, [sp, -128]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	and	w20, w0, 255
	adrp	x0, .LANCHOR49
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	mov	w24, w1
	stp	x21, x22, [sp, 32]
	mov	x25, x2
	ldrb	w21, [x0, #:lo12:.LANCHOR49]
	mov	x26, x3
	stp	x27, x28, [sp, 80]
	mov	w23, 0
	str	w4, [x29, 124]
	bl	nandc_wait_flash_ready
	adrp	x0, .LANCHOR7
	add	w21, w21, w21, lsl 1
	asr	w21, w21, 2
	ldr	x19, [x0, #:lo12:.LANCHOR7]
	adrp	x0, .LANCHOR166
	add	x0, x0, :lo12:.LANCHOR166
	str	x0, [x29, 112]
	ubfiz	x0, x20, 8, 8
	add	x19, x19, x0
.L1784:
	mov	w0, w20
	bl	zftl_flash_enter_slc_mode
	mov	w0, w20
	bl	zftl_flash_exit_slc_mode
	adrp	x0, .LANCHOR19
	mov	w22, 0
	add	x0, x0, :lo12:.LANCHOR19
	mov	w28, -1
	str	x0, [x29, 104]
.L1785:
	ldr	x0, [x29, 112]
	ldrb	w0, [x0]
	cmp	w22, w0
	bcc	.L1790
.L1789:
	mov	w0, 239
	str	w0, [x19, 2056]
	mov	w0, 137
	str	w0, [x19, 2052]
	mov	x0, 1
	bl	udelay
	str	wzr, [x19, 2048]
	str	wzr, [x19, 2048]
	cmp	w28, w21
	str	wzr, [x19, 2048]
	str	wzr, [x19, 2048]
	bcc	.L1791
	cmn	w28, #1
	mov	w0, 256
	csel	w28, w28, w0, eq
.L1791:
	cmn	w28, #1
	cset	w27, eq
	cmp	w28, 256
	cset	w0, eq
	orr	w0, w27, w0
	cbz	w0, .L1792
	mov	w4, w28
	mov	w3, w22
	mov	w2, w24
	mov	w1, w20
	adrp	x0, .LC113
	add	x0, x0, :lo12:.LC113
	bl	printf
	eor	w0, w23, 1
	tst	w27, w0
	beq	.L1793
	mov	w1, 3
	mov	w0, w20
	mov	w23, 1
	bl	mt_auto_read_calibration_config
	b	.L1784
.L1790:
	mov	w0, 239
	str	w0, [x19, 2056]
	mov	w0, 137
	str	w0, [x19, 2052]
	add	w27, w22, 1
	mov	x0, 1
	bl	udelay
	str	w27, [x19, 2048]
	str	wzr, [x19, 2048]
	mov	x3, x26
	ldr	w4, [x29, 124]
	mov	x2, x25
	str	wzr, [x19, 2048]
	mov	w1, w24
	str	wzr, [x19, 2048]
	mov	w0, w20
	bl	flash_read_page
	mov	w6, w0
	ldr	x0, [x29, 104]
	ldr	w0, [x0]
	tbz	x0, 12, .L1786
	mov	w4, w6
	str	w6, [x29, 120]
	mov	w3, w28
	mov	w2, w24
	mov	w1, w22
	adrp	x0, .LC112
	add	x0, x0, :lo12:.LC112
	bl	printf
	ldr	w6, [x29, 120]
.L1786:
	cmn	w6, #1
	beq	.L1787
	adrp	x0, .LANCHOR163
	cmn	w28, #1
	csel	w28, w28, w6, ne
	cmp	w6, w21
	ldr	x25, [x0, #:lo12:.LANCHOR163]
	adrp	x0, .LANCHOR165
	ldr	x26, [x0, #:lo12:.LANCHOR165]
	bcc	.L1796
.L1787:
	mov	w22, w27
	b	.L1785
.L1796:
	mov	w28, w6
	b	.L1789
.L1793:
	cbz	w23, .L1794
	mov	w0, w20
	mov	w1, 0
	bl	mt_auto_read_calibration_config
	cmn	w28, #1
	mov	w0, 256
	csel	w28, w28, w0, eq
.L1794:
	bl	nandc_wait_flash_ready
	mov	w0, w28
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 128
	ret
.L1792:
	cbz	w23, .L1794
	mov	w1, 0
	mov	w0, w20
	mov	w28, 256
	bl	mt_auto_read_calibration_config
	b	.L1794
	.size	micron_read_retrial, .-micron_read_retrial
	.section	.text.toshiba_3d_read_retrial,"ax",@progbits
	.align	2
	.global	toshiba_3d_read_retrial
	.type	toshiba_3d_read_retrial, %function
toshiba_3d_read_retrial:
	stp	x29, x30, [sp, -144]!
	add	x29, sp, 0
	stp	x21, x22, [sp, 32]
	adrp	x22, .LANCHOR16
	stp	x23, x24, [sp, 48]
	mov	w24, w1
	stp	x25, x26, [sp, 64]
	and	w23, w0, 255
	stp	x27, x28, [sp, 80]
	mov	x26, x2
	stp	x19, x20, [sp, 16]
	mov	x27, x3
	mov	w28, w4
	bl	nandc_wait_flash_ready
	adrp	x0, .LANCHOR7
	mov	w1, 46
	mov	w2, 56
	ubfx	x19, x24, 24, 2
	ldr	x25, [x0, #:lo12:.LANCHOR7]
	and	x0, x23, 255
	add	x21, x0, 8
	str	x0, [x29, 128]
	ldrb	w0, [x22, #:lo12:.LANCHOR16]
	add	x21, x25, x21, lsl 8
	cmp	w0, 36
	mov	w0, 26
	csel	w1, w2, w1, ne
	str	w1, [x29, 120]
	mov	w1, 10
	csel	w0, w1, w0, ne
	str	w0, [x29, 136]
	cbnz	w19, .L1814
	add	x0, x22, :lo12:.LANCHOR16
	str	x0, [x29, 120]
	sxtw	x0, w23
	mov	w19, -1
	add	x0, x0, 8
	mov	w20, 1
	add	x0, x25, x0, lsl 8
	str	x0, [x29, 112]
.L1821:
	ldr	x0, [x29, 120]
	ldrb	w0, [x0]
	cmp	w0, 36
	bne	.L1815
	mov	w1, w20
	mov	x0, x21
	mov	w2, 0
	bl	toshiba_tlc_set_rr_para
	ldr	x1, [x29, 112]
	mov	w0, 93
	str	w0, [x1, 8]
.L1816:
	mov	w4, w28
	mov	x3, x27
	mov	x2, x26
	mov	w1, w24
	mov	w0, w23
	bl	flash_read_page
	mov	w4, w0
	adrp	x0, .LANCHOR19
	ldr	w0, [x0, #:lo12:.LANCHOR19]
	tbz	x0, 4, .L1817
	mov	w3, w4
	str	w4, [x29, 108]
	mov	w2, w24
	mov	w1, w20
	adrp	x0, .LC114
	add	x0, x0, :lo12:.LC114
	bl	printf
	ldr	w4, [x29, 108]
.L1817:
	cmn	w4, #1
	beq	.L1818
	adrp	x0, .LANCHOR163
	cmn	w19, #1
	csel	w19, w19, w4, ne
	ldr	x26, [x0, #:lo12:.LANCHOR163]
	adrp	x0, .LANCHOR165
	ldr	x27, [x0, #:lo12:.LANCHOR165]
	adrp	x0, .LANCHOR49
	ldrb	w0, [x0, #:lo12:.LANCHOR49]
	add	w0, w0, w0, lsl 1
	cmp	w4, w0, lsr 2
	bcc	.L1836
.L1818:
	ldr	w0, [x29, 136]
	add	w20, w20, 1
	cmp	w0, w20
	bne	.L1821
.L1820:
	ldrb	w0, [x22, #:lo12:.LANCHOR16]
	cmp	w0, 36
	bne	.L1822
	mov	w2, 0
.L1859:
	mov	w1, 0
	mov	x0, x21
	bl	toshiba_tlc_set_rr_para
	b	.L1823
.L1815:
	mov	w1, w20
	mov	x0, x21
	bl	toshiba_3d_set_slc_rr_para
	b	.L1816
.L1836:
	mov	w19, w4
	b	.L1820
.L1822:
	mov	w1, 0
	mov	x0, x21
	bl	toshiba_3d_set_slc_rr_para
.L1823:
	ldrb	w0, [x22, #:lo12:.LANCHOR16]
	cmp	w0, 36
	bne	.L1832
	ldr	x0, [x29, 128]
	add	x25, x25, x0, lsl 8
	mov	w0, 85
	str	w0, [x25, 2056]
	mov	w0, 255
	str	wzr, [x25, 2052]
	str	wzr, [x25, 2048]
	str	w0, [x25, 2056]
.L1832:
	adrp	x0, .LANCHOR49
	ldrb	w0, [x0, #:lo12:.LANCHOR49]
	add	w0, w0, w0, lsl 1
	cmp	w19, w0, lsr 2
	bcc	.L1833
	cmn	w19, #1
	mov	w0, 256
	csel	w19, w19, w0, eq
.L1833:
	cmp	w19, 256
	ccmn	w19, #1, 4, ne
	bne	.L1834
	adrp	x0, .LC116
	mov	w4, w19
	mov	w3, w20
	mov	w2, w24
	mov	w1, w23
	add	x0, x0, :lo12:.LC116
	bl	printf
.L1834:
	bl	nandc_wait_flash_ready
	mov	w0, w19
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 144
	ret
.L1814:
	add	x0, x22, :lo12:.LANCHOR16
	str	x0, [x29, 112]
	sxtw	x0, w23
	mov	w19, -1
	add	x0, x0, 8
	mov	w20, 1
	add	x0, x25, x0, lsl 8
	str	x0, [x29, 136]
.L1830:
	ldr	x0, [x29, 112]
	ldrb	w0, [x0]
	cmp	w0, 36
	bne	.L1824
	mov	x0, x21
	mov	w2, 1
	mov	w1, w20
	bl	toshiba_tlc_set_rr_para
	mov	w0, 93
.L1858:
	ldr	x1, [x29, 136]
	mov	w4, w28
	mov	x3, x27
	mov	x2, x26
	str	w0, [x1, 8]
	mov	w1, w24
	mov	w0, w23
	bl	flash_read_page
	mov	w4, w0
	adrp	x0, .LANCHOR19
	ldr	w0, [x0, #:lo12:.LANCHOR19]
	tbz	x0, 4, .L1826
	mov	w3, w4
	str	w4, [x29, 108]
	mov	w2, w24
	mov	w1, w20
	adrp	x0, .LC115
	add	x0, x0, :lo12:.LC115
	bl	printf
	ldr	w4, [x29, 108]
.L1826:
	cmn	w4, #1
	beq	.L1827
	adrp	x0, .LANCHOR163
	cmn	w19, #1
	csel	w19, w19, w4, ne
	ldr	x26, [x0, #:lo12:.LANCHOR163]
	adrp	x0, .LANCHOR165
	ldr	x27, [x0, #:lo12:.LANCHOR165]
	adrp	x0, .LANCHOR49
	ldrb	w0, [x0, #:lo12:.LANCHOR49]
	add	w0, w0, w0, lsl 1
	cmp	w4, w0, lsr 2
	bcc	.L1837
.L1827:
	ldr	w0, [x29, 120]
	add	w20, w20, 1
	cmp	w0, w20
	bne	.L1830
.L1829:
	ldrb	w0, [x22, #:lo12:.LANCHOR16]
	cmp	w0, 36
	bne	.L1831
	mov	w2, 1
	b	.L1859
.L1824:
	mov	x0, x21
	mov	w1, w20
	bl	toshiba_3d_set_tlc_rr_para
	mov	w0, 38
	b	.L1858
.L1837:
	mov	w19, w4
	b	.L1829
.L1831:
	mov	w1, 0
	mov	x0, x21
	bl	toshiba_3d_set_tlc_rr_para
	b	.L1823
	.size	toshiba_3d_read_retrial, .-toshiba_3d_read_retrial
	.section	.text.toshiba_read_retrial,"ax",@progbits
	.align	2
	.global	toshiba_read_retrial
	.type	toshiba_read_retrial, %function
toshiba_read_retrial:
	stp	x29, x30, [sp, -128]!
	add	x29, sp, 0
	stp	x21, x22, [sp, 32]
	stp	x25, x26, [sp, 64]
	mov	w25, w1
	mov	x26, x2
	str	w4, [x29, 116]
	stp	x19, x20, [sp, 16]
	and	w19, w0, 255
	stp	x27, x28, [sp, 80]
	mov	x27, x3
	stp	x23, x24, [sp, 48]
	bl	nandc_wait_flash_ready
	mov	w0, w19
	bl	zftl_flash_enter_slc_mode
	mov	w0, w19
	bl	zftl_flash_exit_slc_mode
	adrp	x0, .LANCHOR7
	adrp	x1, .LANCHOR16
	str	x1, [x29, 120]
	ldr	x22, [x0, #:lo12:.LANCHOR7]
	and	x0, x19, 255
	add	x21, x0, 8
	str	x0, [x29, 104]
	ldrb	w0, [x1, #:lo12:.LANCHOR16]
	add	x21, x22, x21, lsl 8
	sub	w0, w0, #67
	and	w0, w0, 255
	cmp	w0, 1
	bls	.L1878
	adrp	x0, .LANCHOR26
	ldrb	w0, [x0, #:lo12:.LANCHOR26]
	cbz	w0, .L1879
	mov	w23, 1
	mov	w0, 1
	bl	nandc_set_if_mode
.L1862:
	and	x0, x19, 255
	mov	w1, 92
	add	x0, x22, x0, lsl 8
	str	w1, [x0, 2056]
	mov	w1, 197
	str	w1, [x0, 2056]
.L1861:
	sxtw	x0, w19
	mov	w20, 1
	add	x0, x0, 8
	mov	w24, -1
	add	x0, x22, x0, lsl 8
	str	x0, [x29, 96]
.L1863:
	adrp	x0, .LANCHOR166
	ldrb	w0, [x0, #:lo12:.LANCHOR166]
	add	w0, w0, 1
	cmp	w20, w0
	bcc	.L1872
	mov	w28, w24
.L1871:
	ldr	x0, [x29, 120]
	mov	w1, 0
	ldrb	w0, [x0, #:lo12:.LANCHOR16]
	sub	w0, w0, #67
	and	w0, w0, 255
	cmp	w0, 1
	mov	x0, x21
	bhi	.L1873
	bl	sandisk_set_rr_para
.L1874:
	sxtw	x19, w19
	mov	w0, 255
	add	x19, x19, 8
	add	x22, x22, x19, lsl 8
	str	w0, [x22, 8]
	adrp	x0, .LANCHOR49
	ldrb	w0, [x0, #:lo12:.LANCHOR49]
	add	w0, w0, w0, lsl 1
	cmp	w28, w0, lsr 2
	bcc	.L1875
	cmn	w28, #1
	mov	w0, 256
	csel	w28, w28, w0, eq
.L1875:
	cmp	w28, 256
	ccmn	w28, #1, 4, ne
	bne	.L1876
	adrp	x0, .LC116
	mov	w4, w28
	mov	w3, w20
	mov	w2, w25
	mov	w1, w20
	add	x0, x0, :lo12:.LC116
	bl	printf
.L1876:
	bl	nandc_wait_flash_ready
	cbz	w23, .L1860
	mov	w0, 4
	bl	nandc_set_if_mode
.L1860:
	mov	w0, w28
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 128
	ret
.L1879:
	mov	w23, 0
	b	.L1862
.L1878:
	mov	w23, 0
	b	.L1861
.L1872:
	ldr	x0, [x29, 120]
	mov	w1, w20
	ldrb	w0, [x0, #:lo12:.LANCHOR16]
	sub	w0, w0, #67
	and	w0, w0, 255
	cmp	w0, 1
	mov	x0, x21
	bhi	.L1864
	bl	sandisk_set_rr_para
.L1865:
	ldr	x0, [x29, 120]
	ldrb	w0, [x0, #:lo12:.LANCHOR16]
	cmp	w0, 34
	bne	.L1866
	adrp	x0, .LANCHOR166
	ldrb	w0, [x0, #:lo12:.LANCHOR166]
	sub	w0, w0, #3
	cmp	w20, w0
	bne	.L1866
	ldr	x1, [x29, 96]
	mov	w0, 179
	str	w0, [x1, 8]
.L1866:
	ldr	x0, [x29, 104]
	mov	w1, 38
	ldr	w4, [x29, 116]
	mov	x3, x27
	mov	x2, x26
	add	x0, x22, x0, lsl 8
	str	w1, [x0, 2056]
	mov	w1, 93
	str	w1, [x0, 2056]
	mov	w1, w25
	mov	w0, w19
	bl	flash_read_page
	mov	w28, w0
	cmn	w0, #1
	beq	.L1869
	cmn	w24, #1
	csel	w24, w24, w0, ne
	adrp	x0, .LANCHOR163
	ldr	x26, [x0, #:lo12:.LANCHOR163]
	adrp	x0, .LANCHOR165
	ldr	x27, [x0, #:lo12:.LANCHOR165]
	adrp	x0, .LANCHOR49
	ldrb	w0, [x0, #:lo12:.LANCHOR49]
	add	w0, w0, w0, lsl 1
	cmp	w28, w0, lsr 2
	bcc	.L1871
.L1869:
	add	w20, w20, 1
	b	.L1863
.L1864:
	bl	toshiba_set_rr_para
	b	.L1865
.L1873:
	bl	toshiba_set_rr_para
	b	.L1874
	.size	toshiba_read_retrial, .-toshiba_read_retrial
	.section	.text.ymtc_3d_read_retrial,"ax",@progbits
	.align	2
	.global	ymtc_3d_read_retrial
	.type	ymtc_3d_read_retrial, %function
ymtc_3d_read_retrial:
	stp	x29, x30, [sp, -112]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w19, -1
	stp	x21, x22, [sp, 32]
	and	w22, w0, 255
	stp	x23, x24, [sp, 48]
	mov	w23, w1
	stp	x25, x26, [sp, 64]
	mov	x24, x2
	stp	x27, x28, [sp, 80]
	mov	x25, x3
	mov	w26, w4
	bl	nandc_wait_flash_ready
	mov	w0, w22
	bl	zftl_flash_enter_slc_mode
	mov	w0, w22
	bl	zftl_flash_exit_slc_mode
	adrp	x1, .LANCHOR7
	ubfiz	x21, x22, 8, 8
	add	x0, x21, 2048
	adrp	x27, .LANCHOR49
	ldr	x21, [x1, #:lo12:.LANCHOR7]
	mov	w20, 1
	adrp	x28, .LANCHOR163
	adrp	x5, .LANCHOR165
	add	x21, x21, x0
	add	x27, x27, :lo12:.LANCHOR49
	tst	x23, 50331648
	bne	.L1902
.L1897:
	str	x5, [x29, 104]
	mov	w1, w20
	mov	x0, x21
	bl	ymtc_3d_set_slc_rr_para
	mov	w4, w26
	mov	x3, x25
	mov	x2, x24
	mov	w1, w23
	mov	w0, w22
	bl	flash_read_page
	ldr	x5, [x29, 104]
	cmn	w0, #1
	beq	.L1894
	ldrb	w1, [x27]
	cmn	w19, #1
	csel	w19, w19, w0, ne
	ldr	x24, [x28, #:lo12:.LANCHOR163]
	ldr	x25, [x5, #:lo12:.LANCHOR165]
	add	w1, w1, w1, lsl 1
	cmp	w0, w1, lsr 2
	bcc	.L1905
.L1894:
	add	w20, w20, 1
	cmp	w20, 10
	bne	.L1897
.L1896:
	mov	w1, 0
	mov	x0, x21
	bl	ymtc_3d_set_slc_rr_para
.L1898:
	adrp	x0, .LANCHOR49
	ldrb	w0, [x0, #:lo12:.LANCHOR49]
	add	w0, w0, w0, lsl 1
	cmp	w19, w0, lsr 2
	bcc	.L1903
	cmn	w19, #1
	mov	w0, 256
	csel	w19, w19, w0, eq
.L1903:
	cmp	w19, 256
	ccmn	w19, #1, 4, ne
	bne	.L1904
	adrp	x0, .LC117
	mov	w4, w19
	mov	w3, w20
	mov	w2, w23
	mov	w1, w20
	add	x0, x0, :lo12:.LC117
	bl	printf
.L1904:
	bl	nandc_wait_flash_ready
	mov	w0, w19
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
.L1905:
	mov	w19, w0
	b	.L1896
.L1902:
	str	x5, [x29, 104]
	mov	w1, w20
	mov	x0, x21
	bl	ymtc_3d_set_tlc_rr_para
	mov	w4, w26
	mov	x3, x25
	mov	x2, x24
	mov	w1, w23
	mov	w0, w22
	bl	flash_read_page
	ldr	x5, [x29, 104]
	cmn	w0, #1
	beq	.L1899
	ldrb	w1, [x27]
	cmn	w19, #1
	csel	w19, w19, w0, ne
	ldr	x24, [x28, #:lo12:.LANCHOR163]
	ldr	x25, [x5, #:lo12:.LANCHOR165]
	add	w1, w1, w1, lsl 1
	cmp	w0, w1, lsr 2
	bcc	.L1906
.L1899:
	add	w20, w20, 1
	cmp	w20, 51
	bne	.L1902
.L1901:
	mov	w1, 0
	mov	x0, x21
	bl	ymtc_3d_set_tlc_rr_para
	b	.L1898
.L1906:
	mov	w19, w0
	b	.L1901
	.size	ymtc_3d_read_retrial, .-ymtc_3d_read_retrial
	.section	.text.samsung_read_retrial,"ax",@progbits
	.align	2
	.global	samsung_read_retrial
	.type	samsung_read_retrial, %function
samsung_read_retrial:
	stp	x29, x30, [sp, -112]!
	add	x29, sp, 0
	stp	x21, x22, [sp, 32]
	and	w21, w0, 255
	mov	x22, x2
	stp	x19, x20, [sp, 16]
	str	w4, [x29, 108]
	mov	w20, w1
	stp	x23, x24, [sp, 48]
	mov	x23, x3
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	bl	nandc_wait_flash_ready
	mov	w0, w21
	bl	zftl_flash_enter_slc_mode
	mov	w0, w21
	bl	zftl_flash_exit_slc_mode
	adrp	x0, .LANCHOR7
	tst	x20, 50331648
	and	x5, x21, 255
	ldr	x0, [x0, #:lo12:.LANCHOR7]
	bne	.L1922
	adrp	x24, .LANCHOR167
	adrp	x27, .LC118
	add	x28, x0, x5, lsl 8
	add	x24, x24, :lo12:.LANCHOR167
	add	x27, x27, :lo12:.LC118
	mov	x26, 0
	mov	w25, -1
.L1927:
	mov	w0, 239
	str	w0, [x28, 2056]
	mov	w0, 141
	str	w0, [x28, 2052]
	add	x0, x24, x26
	add	w19, w26, 1
	ldrsb	w0, [x0, 1]
	str	w0, [x28, 2048]
	str	wzr, [x28, 2048]
	str	wzr, [x28, 2048]
	str	wzr, [x28, 2048]
	bl	nandc_wait_flash_ready
	ldr	w4, [x29, 108]
	mov	x3, x23
	mov	x2, x22
	mov	w1, w20
	mov	w0, w21
	bl	flash_read_page
	mov	w4, w0
	adrp	x0, .LANCHOR19
	ldr	w0, [x0, #:lo12:.LANCHOR19]
	tbz	x0, 4, .L1923
	mov	w3, w4
	str	w4, [x29, 104]
	mov	w2, w20
	mov	w1, w19
	mov	x0, x27
	bl	printf
	ldr	w4, [x29, 104]
.L1923:
	cmn	w4, #1
	beq	.L1924
	adrp	x0, .LANCHOR163
	cmn	w25, #1
	csel	w25, w25, w4, ne
	ldr	x22, [x0, #:lo12:.LANCHOR163]
	adrp	x0, .LANCHOR165
	ldr	x23, [x0, #:lo12:.LANCHOR165]
	adrp	x0, .LANCHOR49
	ldrb	w0, [x0, #:lo12:.LANCHOR49]
	add	w0, w0, w0, lsl 1
	cmp	w4, w0, lsr 2
	bcc	.L1936
.L1924:
	add	x26, x26, 1
	cmp	x26, 25
	bne	.L1927
	mov	w19, 26
.L1926:
	mov	w0, 239
	str	w0, [x28, 2056]
	mov	w0, 141
	str	w0, [x28, 2052]
	str	wzr, [x28, 2048]
	str	wzr, [x28, 2048]
	str	wzr, [x28, 2048]
	str	wzr, [x28, 2048]
.L1958:
	bl	nandc_wait_flash_ready
	adrp	x0, .LANCHOR49
	ldrb	w0, [x0, #:lo12:.LANCHOR49]
	add	w0, w0, w0, lsl 1
	cmp	w25, w0, lsr 2
	bcc	.L1934
	cmn	w25, #1
	mov	w0, 256
	csel	w25, w25, w0, eq
.L1934:
	cmp	w25, 256
	ccmn	w25, #1, 4, ne
	bne	.L1935
	adrp	x0, .LC120
	mov	w4, w25
	mov	w3, w19
	mov	w2, w20
	mov	w1, w19
	add	x0, x0, :lo12:.LC120
	bl	printf
.L1935:
	bl	nandc_wait_flash_ready
	mov	w0, w25
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
.L1936:
	mov	w25, w4
	b	.L1926
.L1922:
	adrp	x7, .LANCHOR168
	add	x7, x7, :lo12:.LANCHOR168
	adrp	x24, .LC119
	add	x28, x7, 4
	add	x27, x0, x5, lsl 8
	add	x24, x24, :lo12:.LC119
	mov	w25, -1
	mov	w19, 1
	mov	w26, 137
.L1933:
	mov	w0, 239
	str	w0, [x27, 2056]
	str	w26, [x27, 2052]
	ldrb	w0, [x28]
	str	w0, [x27, 2048]
	ldrb	w0, [x28, 1]
	str	w0, [x27, 2048]
	ldrb	w0, [x28, 2]
	str	w0, [x27, 2048]
	ldrb	w0, [x28, 3]
	str	w0, [x27, 2048]
	bl	nandc_wait_flash_ready
	ldr	w4, [x29, 108]
	mov	x3, x23
	mov	x2, x22
	mov	w1, w20
	mov	w0, w21
	bl	flash_read_page
	mov	w4, w0
	adrp	x0, .LANCHOR19
	ldr	w0, [x0, #:lo12:.LANCHOR19]
	tbz	x0, 4, .L1929
	mov	w3, w4
	str	w4, [x29, 104]
	mov	w2, w20
	mov	w1, w19
	mov	x0, x24
	bl	printf
	ldr	w4, [x29, 104]
.L1929:
	cmn	w4, #1
	beq	.L1930
	adrp	x0, .LANCHOR163
	cmn	w25, #1
	csel	w25, w25, w4, ne
	ldr	x22, [x0, #:lo12:.LANCHOR163]
	adrp	x0, .LANCHOR165
	ldr	x23, [x0, #:lo12:.LANCHOR165]
	adrp	x0, .LANCHOR49
	ldrb	w0, [x0, #:lo12:.LANCHOR49]
	add	w0, w0, w0, lsl 1
	cmp	w4, w0, lsr 2
	bcc	.L1937
.L1930:
	add	w19, w19, 1
	add	x28, x28, 4
	cmp	w19, 26
	bne	.L1933
.L1932:
	mov	w0, 239
	str	w0, [x27, 2056]
	mov	w0, 137
	str	w0, [x27, 2052]
	str	wzr, [x27, 2048]
	str	wzr, [x27, 2048]
	str	wzr, [x27, 2048]
	str	wzr, [x27, 2048]
	b	.L1958
.L1937:
	mov	w25, w4
	b	.L1932
	.size	samsung_read_retrial, .-samsung_read_retrial
	.section	.text.hynix_read_retrial,"ax",@progbits
	.align	2
	.global	hynix_read_retrial
	.type	hynix_read_retrial, %function
hynix_read_retrial:
	stp	x29, x30, [sp, -128]!
	add	x29, sp, 0
	stp	x23, x24, [sp, 48]
	and	x23, x0, 255
	adrp	x0, .LANCHOR6
	stp	x27, x28, [sp, 80]
	stp	x21, x22, [sp, 32]
	mov	w27, w4
	ldr	x28, [x0, #:lo12:.LANCHOR6]
	mov	w22, w1
	stp	x25, x26, [sp, 64]
	mov	x25, x2
	add	x28, x28, 112
	stp	x19, x20, [sp, 16]
	add	x0, x28, x23
	mov	x26, x3
	mov	x21, x23
	mov	w19, -1
	ldrb	w24, [x28, 2]
	ldrb	w20, [x0, 8]
	bl	nandc_wait_flash_ready
	mov	w0, w23
	bl	zftl_flash_enter_slc_mode
	mov	w0, w23
	bl	zftl_flash_exit_slc_mode
	adrp	x6, .LANCHOR49
	add	x6, x6, :lo12:.LANCHOR49
	mov	w5, 0
	adrp	x7, .LANCHOR163
	adrp	x8, .LANCHOR165
.L1960:
	cmp	w5, w24
	bcc	.L1965
.L1964:
	adrp	x0, .LANCHOR49
	add	x23, x28, x23
	ldrb	w0, [x0, #:lo12:.LANCHOR49]
	strb	w20, [x23, 8]
	add	w0, w0, w0, lsl 1
	cmp	w19, w0, lsr 2
	bcc	.L1966
	cmn	w19, #1
	mov	w0, 256
	csel	w19, w19, w0, eq
.L1966:
	cmp	w19, 256
	ccmn	w19, #1, 4, ne
	bne	.L1967
	adrp	x0, .LC121
	mov	w4, w19
	mov	w3, w5
	mov	w2, w22
	mov	w1, w5
	add	x0, x0, :lo12:.LC121
	bl	printf
.L1967:
	bl	nandc_wait_flash_ready
	mov	w0, w19
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 128
	ret
.L1965:
	add	w20, w20, 1
	stp	x6, x8, [x29, 96]
	and	w20, w20, 255
	str	x7, [x29, 112]
	cmp	w24, w20
	str	w5, [x29, 124]
	csel	w20, w20, wzr, hi
	mov	w0, w21
	mov	w1, w20
	bl	hynix_set_rr_para
	mov	w4, w27
	mov	x3, x26
	mov	x2, x25
	mov	w1, w22
	mov	w0, w21
	bl	flash_read_page
	ldr	w5, [x29, 124]
	cmn	w0, #1
	ldp	x6, x8, [x29, 96]
	ldr	x7, [x29, 112]
	beq	.L1962
	ldrb	w1, [x6]
	cmn	w19, #1
	csel	w19, w19, w0, ne
	ldr	x25, [x7, #:lo12:.LANCHOR163]
	ldr	x26, [x8, #:lo12:.LANCHOR165]
	add	w1, w1, w1, lsl 1
	cmp	w0, w1, lsr 2
	bcc	.L1968
.L1962:
	add	w5, w5, 1
	b	.L1960
.L1968:
	mov	w19, w0
	b	.L1964
	.size	hynix_read_retrial, .-hynix_read_retrial
	.section	.text.flash_ddr_tuning_read,"ax",@progbits
	.align	2
	.global	flash_ddr_tuning_read
	.type	flash_ddr_tuning_read, %function
flash_ddr_tuning_read:
	stp	x29, x30, [sp, -144]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	and	w20, w0, 255
	stp	x21, x22, [sp, 32]
	mov	w22, w1
	stp	x23, x24, [sp, 48]
	mov	x23, x2
	stp	x25, x26, [sp, 64]
	mov	x24, x3
	stp	x27, x28, [sp, 80]
	adrp	x25, .LANCHOR49
	str	w4, [x29, 136]
	bl	nandc_get_ddr_para
	add	x25, x25, :lo12:.LANCHOR49
	str	w0, [x29, 132]
	adrp	x0, .LANCHOR19
	add	x0, x0, :lo12:.LANCHOR19
	mov	w28, 0
	str	x0, [x29, 120]
	mov	w26, 0
	adrp	x0, .LC122
	mov	w27, 0
	add	x0, x0, :lo12:.LC122
	mov	w19, 1024
	mov	w21, -1
	mov	w7, 6
	str	wzr, [x29, 140]
	str	x0, [x29, 112]
.L1984:
	mov	w0, w7
	str	w7, [x29, 128]
	bl	nandc_set_ddr_para
	ldr	w4, [x29, 136]
	mov	x3, x24
	mov	x2, x23
	mov	w1, w22
	mov	w0, w20
	bl	flash_read_page
	mov	w4, w0
	ldr	x0, [x29, 120]
	ldr	w7, [x29, 128]
	ldr	w0, [x0]
	tbz	x0, 4, .L1979
	ldr	x0, [x29, 112]
	mov	w3, w4
	mov	w1, w7
	str	w4, [x29, 108]
	str	w7, [x29, 128]
	mov	w2, w22
	bl	printf
	ldr	w4, [x29, 108]
	ldr	w7, [x29, 128]
.L1979:
	add	w0, w19, 1
	cmp	w4, w0
	bhi	.L1980
	adrp	x0, .LANCHOR163
	ldr	x23, [x0, #:lo12:.LANCHOR163]
	adrp	x0, .LANCHOR165
	ldr	x24, [x0, #:lo12:.LANCHOR165]
	ldrb	w0, [x25]
	cmp	w4, w0, lsr 2
	bcs	.L1990
	add	w27, w27, 1
	cmp	w27, 7
	bls	.L1990
	sub	w28, w7, w27
	mov	w19, w4
	mov	w21, 0
.L1982:
	ldr	w0, [x29, 140]
	cmp	w27, w26
	csel	w28, w28, w0, cs
.L1983:
	cbz	w28, .L1985
	adrp	x0, .LANCHOR49
	mov	w1, 3
	ldrb	w0, [x0, #:lo12:.LANCHOR49]
	udiv	w0, w0, w1
	cmp	w0, w19
	bls	.L1985
	mov	w1, w28
	adrp	x0, .LC123
	add	x0, x0, :lo12:.LC123
	bl	printf
	mov	w0, w28
.L2004:
	bl	nandc_set_ddr_para
	cbz	w21, .L1978
	adrp	x25, .LANCHOR48
	ldrb	w0, [x25, #:lo12:.LANCHOR48]
	tbz	x0, 0, .L1978
	mov	w2, w22
	mov	w1, w20
	adrp	x0, .LC124
	add	x0, x0, :lo12:.LC124
	bl	printf
	mov	w0, w20
	bl	flash_reset
	mov	w0, 1
	bl	flash_set_interface_mode
	mov	w0, 1
	bl	nandc_set_if_mode
	adrp	x0, .LANCHOR33
	add	x0, x0, :lo12:.LANCHOR33
	mov	w1, 2
	strb	w1, [x0, w20, sxtw]
	mov	w0, w20
	bl	zftl_flash_enter_slc_mode
	ldr	w4, [x29, 136]
	mov	x3, x24
	mov	x2, x23
	mov	w1, w22
	mov	w0, w20
	bl	flash_read_page
	mov	w19, w0
	mov	w3, w0
	mov	w2, w22
	mov	w1, w20
	adrp	x0, .LC125
	add	x0, x0, :lo12:.LC125
	bl	printf
	adrp	x0, .LANCHOR49
	ldrb	w0, [x0, #:lo12:.LANCHOR49]
	cmp	w19, w0
	bhi	.L1992
	adrp	x1, .LANCHOR169
	ldr	w0, [x1, #:lo12:.LANCHOR169]
	add	w0, w0, 1
	str	w0, [x1, #:lo12:.LANCHOR169]
	cmp	w0, 100
	bls	.L1988
	adrp	x0, .LANCHOR26
	strb	wzr, [x0, #:lo12:.LANCHOR26]
.L1978:
	mov	w0, w19
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 144
	ret
.L1980:
	cmp	w27, w26
	bls	.L1991
	sub	w0, w28, w27
	str	w0, [x29, 140]
	cmp	w27, 7
	bhi	.L1983
	mov	w26, w27
.L1991:
	mov	w27, 0
	b	.L1981
.L1990:
	mov	w28, w7
	mov	w19, w4
	mov	w21, 0
.L1981:
	add	w7, w7, 2
	cmp	w7, 50
	bne	.L1984
	b	.L1982
.L1985:
	ldrb	w0, [x29, 132]
	b	.L2004
.L1992:
	mov	w19, w21
.L1988:
	ldrb	w0, [x25, #:lo12:.LANCHOR48]
	bl	flash_set_interface_mode
	ldrb	w0, [x25, #:lo12:.LANCHOR48]
	bl	nandc_set_if_mode
	b	.L1978
	.size	flash_ddr_tuning_read, .-flash_ddr_tuning_read
	.section	.text.flash_read_page_en,"ax",@progbits
	.align	2
	.global	flash_read_page_en
	.type	flash_read_page_en, %function
flash_read_page_en:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	and	w20, w0, 255
	adrp	x0, .LANCHOR23
	stp	x23, x24, [sp, 48]
	stp	x21, x22, [sp, 32]
	mov	w19, w1
	str	x25, [sp, 64]
	mov	x22, x2
	ldrb	w1, [x0, #:lo12:.LANCHOR23]
	mov	x23, x3
	mov	w24, w4
	mov	x25, x0
	cmp	w1, w20
	bhi	.L2006
	adrp	x1, .LANCHOR170
	adrp	x0, .LC0
	mov	w2, 431
	add	x1, x1, :lo12:.LANCHOR170
	add	x0, x0, :lo12:.LC0
	bl	printf
.L2006:
	adrp	x0, .LANCHOR29
	add	x0, x0, :lo12:.LANCHOR29
	ldrb	w4, [x25, #:lo12:.LANCHOR23]
	ldrb	w21, [x0, w20, sxtw]
	cmp	w20, w4
	bcc	.L2007
	adrp	x0, .LANCHOR19
	ldr	w0, [x0, #:lo12:.LANCHOR19]
	tbnz	x0, 6, .L2008
.L2032:
	mov	w0, -1
.L2005:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldr	x25, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
.L2008:
	mov	w3, w19
	mov	w2, w20
	mov	w1, w21
	adrp	x0, .LC126
	add	x0, x0, :lo12:.LC126
	bl	printf
	b	.L2032
.L2007:
	tst	x19, 50331648
	bne	.L2010
	adrp	x0, .LANCHOR0
	adrp	x1, .LANCHOR1
	ldrb	w0, [x0, #:lo12:.LANCHOR0]
	cbz	w0, .L2011
	ldrb	w0, [x1, #:lo12:.LANCHOR1]
	cbz	w0, .L2010
.L2011:
	adrp	x0, .LANCHOR2
	ldrb	w1, [x1, #:lo12:.LANCHOR1]
	ldrh	w2, [x0, #:lo12:.LANCHOR2]
	udiv	w0, w19, w2
	mul	w0, w0, w2
	sub	w19, w19, w0
	cbz	w1, .L2012
	add	w19, w0, w19, lsl 1
.L2010:
	mov	w4, w24
	mov	x3, x23
	mov	x2, x22
	mov	w1, w19
	mov	w0, w21
	bl	flash_read_page
	cmn	w0, #1
	bne	.L2005
	adrp	x20, .LANCHOR51
	ldrb	w25, [x20, #:lo12:.LANCHOR51]
	cbnz	w25, .L2013
.L2016:
	adrp	x0, .LANCHOR171
	ldr	x5, [x0, #:lo12:.LANCHOR171]
	cbnz	x5, .L2014
.L2015:
	ldrb	w4, [x20, #:lo12:.LANCHOR51]
	mov	w3, -1
	mov	w2, w19
	mov	w1, 0
	adrp	x0, .LC127
	add	x0, x0, :lo12:.LC127
	bl	printf
	adrp	x0, .LANCHOR26
	ldrb	w0, [x0, #:lo12:.LANCHOR26]
	cbz	w0, .L2032
	mov	w4, w24
	mov	x3, x23
	mov	x2, x22
	mov	w1, w19
	mov	w0, w21
	ldr	x25, [sp, 64]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 80
	b	flash_ddr_tuning_read
.L2012:
	adrp	x1, .LANCHOR3
	add	x1, x1, :lo12:.LANCHOR3
	ldrh	w19, [x1, w19, uxtw 1]
	add	w19, w19, w0
	b	.L2010
.L2013:
	strb	wzr, [x20, #:lo12:.LANCHOR51]
	mov	w4, w24
	mov	x3, x23
	mov	x2, x22
	mov	w1, w19
	mov	w0, w21
	bl	flash_read_page
	strb	w25, [x20, #:lo12:.LANCHOR51]
	cmn	w0, #1
	beq	.L2016
	b	.L2005
.L2014:
	mov	w4, w24
	mov	x3, x23
	mov	x2, x22
	mov	w1, w19
	mov	w0, w21
	blr	x5
	cmn	w0, #1
	beq	.L2015
	b	.L2005
	.size	flash_read_page_en, .-flash_read_page_en
	.section	.text.flash_get_last_written_page,"ax",@progbits
	.align	2
	.global	flash_get_last_written_page
	.type	flash_get_last_written_page, %function
flash_get_last_written_page:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x23, x24, [sp, 48]
	and	w23, w0, 255
	adrp	x0, .LANCHOR144
	stp	x19, x20, [sp, 16]
	stp	x25, x26, [sp, 64]
	mov	x24, x2
	ldrh	w19, [x0, #:lo12:.LANCHOR144]
	adrp	x0, .LANCHOR32+26
	stp	x21, x22, [sp, 32]
	and	w21, w1, 65535
	ldrh	w26, [x0, #:lo12:.LANCHOR32+26]
	sub	w19, w19, #1
	sxth	w19, w19
	stp	x27, x28, [sp, 80]
	mov	x22, x3
	mov	w25, w4
	mov	w0, w23
	mul	w26, w26, w21
	add	w1, w19, w26
	bl	flash_read_page_en
	cmp	w0, 512
	bne	.L2034
	mov	w27, 0
	mov	w28, 2
.L2035:
	cmp	w27, w19
	ble	.L2038
.L2034:
	adrp	x0, .LANCHOR19
	ldr	w0, [x0, #:lo12:.LANCHOR19]
	tbz	x0, 12, .L2039
	ldr	w3, [x22]
	adrp	x0, .LC128
	mov	w2, w19
	mov	w1, w21
	add	x0, x0, :lo12:.LC128
	bl	printf
.L2039:
	mov	w0, w19
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 96
	ret
.L2038:
	add	w20, w27, w19
	mov	w4, w25
	mov	x3, x22
	mov	x2, x24
	mov	w0, w23
	sdiv	w20, w20, w28
	add	w1, w26, w20, sxth
	bl	flash_read_page_en
	cmp	w0, 512
	bne	.L2036
	sub	w19, w20, #1
	sxth	w19, w19
	b	.L2035
.L2036:
	add	w20, w20, 1
	sxth	w27, w20
	b	.L2035
	.size	flash_get_last_written_page, .-flash_get_last_written_page
	.section	.text.flash_get_last_written_page_ext,"ax",@progbits
	.align	2
	.global	flash_get_last_written_page_ext
	.type	flash_get_last_written_page_ext, %function
flash_get_last_written_page_ext:
	adrp	x4, .LANCHOR31
	mov	w5, 24
	and	w0, w0, 65535
	mov	w6, 1
	ldrb	w4, [x4, #:lo12:.LANCHOR31]
	sub	w5, w5, w4
	adrp	x4, .LANCHOR74
	ldrh	w4, [x4, #:lo12:.LANCHOR74]
	sub	w5, w5, w4
	mov	w4, w3
	mov	x3, x2
	mov	x2, x1
	lsl	w6, w6, w5
	sub	w6, w6, #1
	and	w1, w6, w0
	asr	w0, w0, w5
	b	flash_get_last_written_page
	.size	flash_get_last_written_page_ext, .-flash_get_last_written_page_ext
	.section	.text.flash_ddr_para_scan,"ax",@progbits
	.align	2
	.global	flash_ddr_para_scan
	.type	flash_ddr_para_scan, %function
flash_ddr_para_scan:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	adrp	x20, .LANCHOR48
	stp	x21, x22, [sp, 32]
	and	w22, w0, 255
	ldrb	w0, [x20, #:lo12:.LANCHOR48]
	adrp	x19, .LANCHOR26
	stp	x23, x24, [sp, 48]
	mov	w21, 1
	mov	w23, w1
	str	x25, [sp, 64]
	strb	w21, [x19, #:lo12:.LANCHOR26]
	adrp	x24, .LANCHOR173
	bl	flash_set_interface_mode
	adrp	x25, .LANCHOR172
	ldrb	w0, [x20, #:lo12:.LANCHOR48]
	bl	nandc_set_if_mode
	ldr	x3, [x25, #:lo12:.LANCHOR172]
	mov	w4, 4
	ldr	x2, [x24, #:lo12:.LANCHOR173]
	mov	w1, w23
	mov	w0, w22
	bl	flash_ddr_tuning_read
	ldr	x3, [x25, #:lo12:.LANCHOR172]
	mov	w4, 4
	ldr	x2, [x24, #:lo12:.LANCHOR173]
	mov	w1, w23
	mov	w0, w22
	bl	flash_read_page
	cmn	w0, #1
	mov	x0, x19
	bne	.L2046
	ldrb	w1, [x20, #:lo12:.LANCHOR48]
	tbz	x1, 0, .L2046
	mov	w0, 1
	bl	flash_set_interface_mode
	mov	w0, w21
	bl	nandc_set_if_mode
	strb	wzr, [x19, #:lo12:.LANCHOR26]
.L2047:
	mov	w0, 0
	ldr	x25, [sp, 64]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
.L2046:
	mov	w1, 1
	strb	w1, [x0, #:lo12:.LANCHOR26]
	b	.L2047
	.size	flash_ddr_para_scan, .-flash_ddr_para_scan
	.section	.text.flash_prog_page,"ax",@progbits
	.align	2
	.global	flash_prog_page
	.type	flash_prog_page, %function
flash_prog_page:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x21, x22, [sp, 32]
	and	w21, w0, 255
	adrp	x0, .LANCHOR7
	stp	x25, x26, [sp, 64]
	stp	x19, x20, [sp, 16]
	mov	w20, 24
	ldr	x26, [x0, #:lo12:.LANCHOR7]
	adrp	x0, .LANCHOR31
	mov	w22, w1
	stp	x23, x24, [sp, 48]
	ldrb	w0, [x0, #:lo12:.LANCHOR31]
	mov	x24, x2
	mov	x25, x3
	and	x19, x21, 255
	sub	w0, w20, w0
	mov	w20, 1
	add	x23, x19, 8
	lsl	w20, w20, w0
	sub	w20, w20, #1
	and	w20, w20, w1
	bl	nandc_wait_flash_ready
	mov	w0, w21
	bl	hynix_reconfig_rr_para
	mov	w0, w21
	bl	nandc_cs
	add	x23, x26, x23, lsl 8
	mov	w0, w21
	tst	x22, 50331648
	bne	.L2053
	bl	zftl_flash_enter_slc_mode
.L2054:
	add	x19, x26, x19, lsl 8
	mov	w0, 128
	str	w0, [x19, 2056]
	and	w0, w20, 255
	str	wzr, [x19, 2052]
	str	wzr, [x19, 2052]
	str	w0, [x19, 2052]
	lsr	w0, w20, 8
	str	w0, [x19, 2052]
	lsr	w0, w20, 16
	str	w0, [x19, 2052]
	adrp	x0, .LANCHOR30
	ldrb	w0, [x0, #:lo12:.LANCHOR30]
	cbz	w0, .L2055
	lsr	w0, w20, 24
	str	w0, [x19, 2052]
.L2055:
	mov	w0, w20
	bl	nandc_set_seed
	adrp	x0, .LANCHOR32+9
	mov	x4, x25
	mov	x3, x24
	mov	w1, 1
	ldrb	w2, [x0, #:lo12:.LANCHOR32+9]
	mov	w0, w21
	bl	nandc_xfer
	mov	w0, 16
	str	w0, [x19, 2056]
	bl	nandc_wait_flash_ready
	mov	x0, x23
	bl	flash_read_status
	mov	w3, w0
	bl	nandc_de_cs.constprop.32
	and	w2, w3, 4
	tbz	x3, 2, .L2052
	mov	w1, w22
	adrp	x0, .LC129
	add	x0, x0, :lo12:.LC129
	bl	printf
	mov	w2, -1
.L2052:
	mov	w0, w2
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
.L2053:
	bl	zftl_flash_exit_slc_mode
	b	.L2054
	.size	flash_prog_page, .-flash_prog_page
	.section	.text.flash_test_blk,"ax",@progbits
	.align	2
	.global	flash_test_blk
	.type	flash_test_blk, %function
flash_test_blk:
	stp	x29, x30, [sp, -64]!
	mov	w2, 32
	add	x29, sp, 0
	stp	x21, x22, [sp, 32]
	adrp	x22, .LANCHOR163
	stp	x19, x20, [sp, 16]
	and	w20, w0, 255
	ldr	x0, [x22, #:lo12:.LANCHOR163]
	adrp	x21, .LANCHOR165
	and	w19, w1, 65535
	str	x23, [sp, 48]
	mov	w1, 165
	bl	ftl_memset
	ldr	x0, [x21, #:lo12:.LANCHOR165]
	mov	w2, 8
	mov	w1, 90
	bl	ftl_memset
	adrp	x0, .LANCHOR2
	ldrh	w0, [x0, #:lo12:.LANCHOR2]
	mul	w19, w0, w19
	mov	w0, w20
	mov	w1, w19
	bl	flash_erase_block
	cmn	w0, #1
	bne	.L2065
.L2067:
	mov	w21, -1
.L2066:
	mov	w1, w19
	mov	w0, w20
	bl	flash_erase_block
	ldr	x23, [sp, 48]
	mov	w0, w21
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
.L2065:
	adrp	x23, .LANCHOR32
	add	x23, x23, :lo12:.LANCHOR32
	ldr	x3, [x21, #:lo12:.LANCHOR165]
	mov	w1, w19
	ldr	x2, [x22, #:lo12:.LANCHOR163]
	mov	w0, w20
	ldrb	w4, [x23, 9]
	bl	flash_prog_page
	cmn	w0, #1
	beq	.L2067
	ldrb	w4, [x23, 9]
	mov	w1, w19
	ldr	x3, [x21, #:lo12:.LANCHOR165]
	mov	w0, w20
	ldr	x2, [x22, #:lo12:.LANCHOR163]
	bl	flash_read_page_en
	cmn	w0, #1
	beq	.L2067
	ldr	x0, [x22, #:lo12:.LANCHOR163]
	ldr	w1, [x0]
	mov	w0, 42405
	movk	w0, 0xa5a5, lsl 16
	cmp	w1, w0
	bne	.L2067
	ldr	x0, [x21, #:lo12:.LANCHOR165]
	ldr	w1, [x0]
	mov	w0, 23130
	movk	w0, 0x5a5a, lsl 16
	cmp	w1, w0
	csetm	w21, ne
	b	.L2066
	.size	flash_test_blk, .-flash_test_blk
	.section	.text.id_block_prog_msb_ff_data,"ax",@progbits
	.align	2
	.global	id_block_prog_msb_ff_data
	.type	id_block_prog_msb_ff_data, %function
id_block_prog_msb_ff_data:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x21, x22, [sp, 32]
	and	w22, w0, 255
	adrp	x0, .LANCHOR24
	stp	x19, x20, [sp, 16]
	stp	x23, x24, [sp, 48]
	ldrb	w0, [x0, #:lo12:.LANCHOR24]
	str	x25, [sp, 64]
	cbnz	w0, .L2075
	adrp	x20, .LANCHOR32
	add	x20, x20, :lo12:.LANCHOR32
	ldrb	w0, [x20, 19]
	sub	w0, w0, #5
	and	w3, w0, 255
	cmp	w3, 63
	bhi	.L2075
	and	w19, w2, 65535
	mov	x2, 16391
	movk	x2, 0x4000, lsl 16
	movk	x2, 0x8000, lsl 48
	lsr	x0, x2, x3
	tbz	x0, 0, .L2075
	adrp	x21, .LANCHOR142
	mov	w23, w1
	add	x21, x21, :lo12:.LANCHOR142
	mov	w25, 65535
	adrp	x24, .LANCHOR163
.L2077:
	ldrh	w0, [x20, 10]
	cmp	w0, w19
	bhi	.L2078
.L2075:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldr	x25, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
.L2078:
	ldrh	w0, [x21, w19, sxtw 1]
	cmp	w0, w25
	bne	.L2075
	ldr	x0, [x24, #:lo12:.LANCHOR163]
	mov	w2, 16384
	mov	w1, 255
	bl	ftl_memset
	ldr	x3, [x24, #:lo12:.LANCHOR163]
	add	w1, w19, w23
	ldrb	w4, [x20, 9]
	add	w19, w19, 1
	mov	x2, x3
	mov	w0, w22
	and	w19, w19, 65535
	bl	flash_prog_page
	b	.L2077
	.size	id_block_prog_msb_ff_data, .-id_block_prog_msb_ff_data
	.section	.text.flash_start_one_pass_page_prog,"ax",@progbits
	.align	2
	.global	flash_start_one_pass_page_prog
	.type	flash_start_one_pass_page_prog, %function
flash_start_one_pass_page_prog:
	stp	x29, x30, [sp, -32]!
	and	w8, w0, 255
	and	w7, w3, 255
	adrp	x0, .LANCHOR7
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	and	w20, w2, 255
	ldr	x19, [x0, #:lo12:.LANCHOR7]
	mov	w0, w7
	bl	nandc_cs
	cbz	w8, .L2081
	sxtw	x0, w7
	add	x0, x0, 8
	add	x0, x19, x0, lsl 8
	str	w8, [x0, 8]
.L2081:
	ubfiz	x0, x7, 8, 8
	add	x19, x19, x0
	mov	w0, 128
	str	w0, [x19, 2056]
	and	w0, w4, 255
	str	wzr, [x19, 2052]
	str	wzr, [x19, 2052]
	str	w0, [x19, 2052]
	lsr	w0, w4, 8
	str	w0, [x19, 2052]
	lsr	w0, w4, 16
	str	w0, [x19, 2052]
	adrp	x0, .LANCHOR30
	ldrb	w0, [x0, #:lo12:.LANCHOR30]
	cbz	w0, .L2082
	lsr	w0, w4, 24
	str	w0, [x19, 2052]
.L2082:
	mov	w0, w4
	bl	nandc_set_seed
	adrp	x0, .LANCHOR32+9
	mov	x4, x6
	mov	x3, x5
	mov	w1, 1
	ldrb	w2, [x0, #:lo12:.LANCHOR32+9]
	mov	w0, w7
	bl	nandc_xfer
	str	w20, [x19, 2056]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	flash_start_one_pass_page_prog, .-flash_start_one_pass_page_prog
	.section	.text.flash_dual_page_prog,"ax",@progbits
	.align	2
	.global	flash_dual_page_prog
	.type	flash_dual_page_prog, %function
flash_dual_page_prog:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	and	w20, w0, 255
	stp	x25, x26, [sp, 64]
	mov	x25, x2
	adrp	x2, .LANCHOR7
	stp	x21, x22, [sp, 32]
	ubfiz	x22, x20, 8, 8
	stp	x27, x28, [sp, 80]
	add	x0, x22, 2048
	ldr	x22, [x2, #:lo12:.LANCHOR7]
	mov	w19, 24
	adrp	x27, .LANCHOR19
	add	x22, x22, x0
	adrp	x0, .LANCHOR31
	stp	x23, x24, [sp, 48]
	mov	w21, w1
	ldrb	w0, [x0, #:lo12:.LANCHOR31]
	mov	x26, x3
	mov	x23, x4
	mov	x24, x5
	sub	w0, w19, w0
	mov	w19, 1
	ubfx	x28, x21, 24, 2
	lsl	w19, w19, w0
	ldr	w0, [x27, #:lo12:.LANCHOR19]
	sub	w19, w19, #1
	and	w19, w19, w1
	tbz	x0, 4, .L2091
	adrp	x0, .LC130
	mov	w3, w6
	mov	w2, w28
	add	x0, x0, :lo12:.LC130
	bl	printf
.L2091:
	bl	nandc_wait_flash_ready
	mov	w0, w20
	bl	nandc_cs
	mov	w0, w20
	cbnz	w28, .L2092
	bl	zftl_flash_enter_slc_mode
.L2093:
	mov	x6, x26
	mov	x5, x25
	mov	w4, w19
	mov	w3, w20
	mov	w2, 16
	mov	w1, 0
	mov	w0, 0
	bl	flash_start_one_pass_page_prog
	bl	nandc_wait_flash_ready
	mov	x6, x24
	mov	x5, x23
	add	w4, w19, 1
	mov	w3, w20
	mov	w2, 16
	mov	w1, 0
	mov	w0, 0
	bl	flash_start_one_pass_page_prog
	bl	nandc_wait_flash_ready
	mov	x0, x22
	bl	flash_read_status
	mov	w3, w0
	bl	nandc_de_cs.constprop.32
	and	w2, w3, 4
	tbz	x3, 2, .L2090
	ldr	w0, [x27, #:lo12:.LANCHOR19]
	tbz	x0, 12, .L2095
	adrp	x0, .LC129
	mov	w1, w21
	add	x0, x0, :lo12:.LC129
	bl	printf
.L2095:
	mov	w2, -1
.L2090:
	mov	w0, w2
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 96
	ret
.L2092:
	bl	zftl_flash_exit_slc_mode
	b	.L2093
	.size	flash_dual_page_prog, .-flash_dual_page_prog
	.section	.text.ymtc_flash_tlc_page_prog,"ax",@progbits
	.align	2
	.global	ymtc_flash_tlc_page_prog
	.type	ymtc_flash_tlc_page_prog, %function
ymtc_flash_tlc_page_prog:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	and	w20, w0, 255
	str	x25, [sp, 64]
	mov	w25, w1
	adrp	x1, .LANCHOR7
	stp	x21, x22, [sp, 32]
	ubfiz	x22, x20, 8, 8
	mov	w19, 24
	add	x0, x22, 2048
	ldr	x22, [x1, #:lo12:.LANCHOR7]
	mov	w21, 1
	stp	x23, x24, [sp, 48]
	add	x22, x22, x0
	adrp	x0, .LANCHOR31
	mov	x23, x2
	mov	x24, x3
	ldrb	w0, [x0, #:lo12:.LANCHOR31]
	sub	w19, w19, w0
	bl	nandc_wait_flash_ready
	lsl	w19, w21, w19
	mov	w0, w20
	sub	w19, w19, #1
	bl	nandc_cs
	and	w19, w19, w25
	mov	w0, w20
	bl	zftl_flash_exit_slc_mode
	mov	x6, x24
	mov	x5, x23
	mov	w4, w19
	mov	w3, w20
	mov	w1, w21
	mov	w2, 26
	mov	w0, 0
	bl	flash_start_one_pass_page_prog
	bl	nandc_wait_flash_ready
	mov	x6, x24
	mov	x5, x23
	add	w4, w19, w21
	mov	w3, w20
	mov	w1, w21
	mov	w2, 26
	mov	w0, 0
	bl	flash_start_one_pass_page_prog
	bl	nandc_wait_flash_ready
	mov	x6, x24
	mov	x5, x23
	add	w4, w19, 2
	mov	w3, w20
	mov	w1, w21
	mov	w2, 16
	mov	w0, 0
	bl	flash_start_one_pass_page_prog
	bl	nandc_wait_flash_ready
	mov	x0, x22
	bl	flash_read_status
	mov	w3, w0
	bl	nandc_de_cs.constprop.32
	and	w2, w3, 4
	tbz	x3, 2, .L2103
	adrp	x0, .LANCHOR19
	ldr	w0, [x0, #:lo12:.LANCHOR19]
	tbz	x0, 12, .L2105
	adrp	x0, .LC131
	mov	w1, w25
	add	x0, x0, :lo12:.LC131
	bl	printf
.L2105:
	mov	w2, -1
.L2103:
	mov	w0, w2
	ldr	x25, [sp, 64]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
	.size	ymtc_flash_tlc_page_prog, .-ymtc_flash_tlc_page_prog
	.section	.text.fw_flash_page_prog.constprop.29,"ax",@progbits
	.align	2
	.type	fw_flash_page_prog.constprop.29, %function
fw_flash_page_prog.constprop.29:
	stp	x29, x30, [sp, -64]!
	adrp	x4, .LANCHOR32
	add	x4, x4, :lo12:.LANCHOR32
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x1
	stp	x21, x22, [sp, 32]
	mov	x21, x2
	str	x23, [sp, 48]
	ldrb	w19, [x4, 9]
	udiv	w19, w0, w19
	adrp	x0, .LANCHOR49
	ldrb	w23, [x0, #:lo12:.LANCHOR49]
	adrp	x0, .LANCHOR22
	ldrb	w0, [x0, #:lo12:.LANCHOR22]
	bl	nandc_bch_sel
	ldrb	w0, [x4, 7]
	cmp	w0, 9
	bne	.L2111
	adrp	x0, .LANCHOR24
	ldrb	w0, [x0, #:lo12:.LANCHOR24]
	cbnz	w0, .L2111
	ldrb	w0, [x4, 12]
	cmp	w0, 3
	bne	.L2112
	mov	x3, x21
	mov	x2, x20
	mov	w1, w19
	mov	w0, 0
	bl	ymtc_flash_tlc_page_prog
.L2115:
	mov	w4, w0
	mov	w0, w23
	bl	nandc_bch_sel
	ldr	x23, [sp, 48]
	mov	w0, w4
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
.L2112:
	adrp	x22, .LANCHOR163
	mov	w2, 16384
	mov	w1, 255
	ldr	x0, [x22, #:lo12:.LANCHOR163]
	bl	ftl_memset
	ldr	x5, [x22, #:lo12:.LANCHOR163]
	mov	w6, 4
	mov	x3, x21
	mov	x2, x20
	mov	x4, x5
	mov	w1, w19
	mov	w0, 0
	bl	flash_dual_page_prog
	b	.L2115
.L2111:
	mov	w4, 4
	mov	x3, x21
	mov	x2, x20
	mov	w1, w19
	mov	w0, 0
	bl	flash_prog_page
	b	.L2115
	.size	fw_flash_page_prog.constprop.29, .-fw_flash_page_prog.constprop.29
	.section	.text.idb_write_data,"ax",@progbits
	.align	2
	.global	idb_write_data
	.type	idb_write_data, %function
idb_write_data:
	stp	x29, x30, [sp, -272]!
	cmp	w1, 64
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w19, w1
	stp	x21, x22, [sp, 32]
	mov	w20, w3
	stp	x23, x24, [sp, 48]
	adrp	x22, .LANCHOR140
	stp	x25, x26, [sp, 64]
	mov	x24, x2
	stp	x27, x28, [sp, 80]
	bne	.L2117
	ldr	w0, [x2]
	mov	w1, 35899
	movk	w1, 0xfcdc, lsl 16
	cmp	w0, w1
	mov	w1, 19282
	movk	w1, 0x534e, lsl 16
	ccmp	w0, w1, 4, ne
	beq	.L2118
	add	w1, w1, 327680
	cmp	w0, w1
	bne	.L2117
.L2118:
	adrp	x21, .LANCHOR138
	mov	w1, 1
	strb	w1, [x22, #:lo12:.LANCHOR140]
	ldr	x0, [x21, #:lo12:.LANCHOR138]
	cbnz	x0, .L2119
	mov	w0, 262144
	bl	ftl_malloc
	str	x0, [x21, #:lo12:.LANCHOR138]
.L2119:
	adrp	x0, .LANCHOR174
	mov	w1, 64
	str	w1, [x0, #:lo12:.LANCHOR174]
.L2117:
	ldrb	w0, [x22, #:lo12:.LANCHOR140]
	cbz	w0, .L2185
	adrp	x0, .LANCHOR138
	mov	x23, x0
	ldr	x21, [x0, #:lo12:.LANCHOR138]
	cbz	x21, .L2185
	add	w0, w19, w20
	str	w0, [x29, 140]
	cmp	w0, 63
	bls	.L2121
	cmp	w19, 575
	bhi	.L2122
	adrp	x21, .LANCHOR141
	ldr	x0, [x21, #:lo12:.LANCHOR141]
	cbz	x0, .L2123
.L2126:
	adrp	x1, .LANCHOR139
	mov	w2, 1
	ldr	x0, [x23, #:lo12:.LANCHOR138]
	cmp	w19, 64
	str	w2, [x1, #:lo12:.LANCHOR139]
	bhi	.L2238
	mov	w4, 64
	sub	w4, w4, w19
	sub	w2, w20, w4
	ubfiz	x4, x4, 9, 25
	lsl	w2, w2, 9
	add	x1, x24, x4
.L2244:
	bl	ftl_memcpy
.L2127:
	adrp	x0, .LANCHOR174
	ldr	w0, [x0, #:lo12:.LANCHOR174]
	cmp	w19, w0
	beq	.L2181
	strb	wzr, [x22, #:lo12:.LANCHOR140]
	b	.L2181
.L2123:
	mov	w0, 262144
	bl	ftl_malloc
	str	x0, [x21, #:lo12:.LANCHOR141]
	cbnz	x0, .L2126
	mov	w0, -1
	b	.L2116
.L2238:
	mov	w2, 576
	sub	w2, w2, w19
	cmp	w20, w2
	sub	w3, w19, #64
	csel	w2, w20, w2, ls
	ubfiz	x3, x3, 9, 25
	lsl	w2, w2, 9
	mov	x1, x24
	add	x0, x0, x3
	b	.L2244
.L2121:
	cmp	w19, 575
	bls	.L2127
.L2122:
	adrp	x0, .LANCHOR139
	ldr	w0, [x0, #:lo12:.LANCHOR139]
	cbz	w0, .L2127
	ldr	w0, [x21]
	mov	w1, 35899
	movk	w1, 0xfcdc, lsl 16
	cmp	w0, w1
	mov	w1, 19282
	movk	w1, 0x534e, lsl 16
	ccmp	w0, w1, 4, ne
	beq	.L2128
	add	w1, w1, 327680
	cmp	w0, w1
	bne	.L2129
.L2128:
	adrp	x0, .LANCHOR0
	mov	x20, x0
	ldrb	w1, [x0, #:lo12:.LANCHOR0]
	str	w1, [x29, 176]
	adrp	x1, .LANCHOR24
	mov	x24, x1
	ldr	w0, [x29, 176]
	ldrb	w2, [x1, #:lo12:.LANCHOR24]
	str	w2, [x29, 204]
	cbz	w0, .L2130
	ldrh	w0, [x29, 176]
	str	w0, [x29, 172]
	uxtw	x0, w2
	cmp	w0, 0
	cset	w0, eq
.L2241:
	adrp	x23, .LANCHOR32
	add	x23, x23, :lo12:.LANCHOR32
	str	w0, [x29, 200]
	mov	w0, 0
	ldrb	w19, [x23, 9]
	ldrh	w22, [x23, 26]
	bl	zftl_flash_exit_slc_mode
	ldrb	w0, [x24, #:lo12:.LANCHOR24]
	add	x1, x21, 258048
	strb	w0, [x20, #:lo12:.LANCHOR0]
	mov	w4, 16981
	ldrh	w20, [x23, 10]
	add	x1, x1, 2044
	ldrb	w0, [x23, 12]
	mov	w2, 65023
	movk	w4, 0x4f4f, lsl 16
	mov	w3, 4098
	lsl	w20, w20, 2
	sdiv	w20, w20, w0
	mov	w0, 512
	cmp	w20, 512
	csel	w20, w20, w0, lt
	mov	w0, 0
.L2137:
	ldr	w5, [x1]
	cbnz	w5, .L2133
	cbnz	w0, .L2134
	str	w4, [x1, 2048]
.L2135:
	add	w0, w0, 1
	sub	w2, w2, #1
	cmp	w0, w3
	sub	x1, x1, #4
	csel	w0, w0, wzr, ls
	cmp	w2, 4096
	bne	.L2137
.L2133:
	ldr	w1, [x21, w2, uxtw 2]
	mov	w3, w20
	adrp	x0, .LC132
	add	x0, x0, :lo12:.LC132
	bl	printf
	str	wzr, [x29, 180]
	mul	w0, w22, w19
	str	wzr, [x29, 192]
	str	w0, [x29, 128]
	adrp	x0, .LANCHOR51
	add	x0, x0, :lo12:.LANCHOR51
	str	x0, [x29, 184]
.L2176:
	adrp	x23, .LANCHOR141
	mov	w1, 0
	mov	w2, 512
	ldr	x0, [x23, #:lo12:.LANCHOR141]
	bl	ftl_memset
	str	x23, [x29, 160]
	adrp	x0, .LANCHOR6
	ldr	w1, [x29, 192]
	ldr	x0, [x0, #:lo12:.LANCHOR6]
	add	x0, x0, x1, uxtw
	ldrb	w19, [x0, 32]
	cmp	w19, 255
	beq	.L2138
	ldr	w0, [x29, 128]
	mul	w19, w19, w0
	ldr	w0, [x29, 200]
	cbz	w0, .L2139
	and	w0, w1, -3
	adrp	x24, .LANCHOR0
	cmp	w0, 1
	adrp	x22, .LANCHOR24
	beq	.L2140
	ldr	w0, [x29, 200]
	cmp	w0, 3
	bne	.L2141
.L2140:
	ldrb	w0, [x29, 172]
	strb	w0, [x24, #:lo12:.LANCHOR0]
	strb	w0, [x22, #:lo12:.LANCHOR24]
.L2139:
	adrp	x22, .LANCHOR32
	add	x27, x22, :lo12:.LANCHOR32
	ldr	x0, [x29, 184]
	ldrb	w24, [x27, 9]
	ldrh	w25, [x27, 26]
	ldrb	w0, [x0]
	str	w0, [x29, 136]
	udiv	w1, w19, w24
	ldr	x0, [x29, 184]
	mul	w25, w25, w24
	strb	wzr, [x0]
	mov	w0, 0
	bl	flash_erase_block
	udiv	w0, w19, w25
	ldrb	w1, [x27, 12]
	msub	w0, w0, w25, w19
	str	w0, [x29, 168]
	sub	w26, w19, w0
	ldrh	w0, [x27, 10]
	cmp	w19, w26
	lsl	w0, w0, 2
	sdiv	w0, w0, w1
	str	w0, [x29, 156]
	bne	.L2191
	adrp	x0, .LANCHOR27
	ldrb	w0, [x0, #:lo12:.LANCHOR27]
	cmp	w0, 9
	bne	.L2191
	ldr	x0, [x29, 160]
	mov	w2, 1024
	mov	w1, 0
	ldr	x25, [x0, #:lo12:.LANCHOR141]
	mov	x0, x25
	bl	ftl_memset
	mov	w0, 18766
	movk	w0, 0x464e, lsl 16
	str	w0, [x25]
	mov	w0, 12
	str	w0, [x25, 4]
	adrp	x0, .LANCHOR24
	strb	wzr, [x25, 16]
	str	wzr, [x25, 12]
	ldrb	w0, [x0, #:lo12:.LANCHOR24]
	cbz	w0, .L2143
	ldrb	w0, [x27, 29]
	strb	w0, [x25, 16]
.L2143:
	add	x1, x22, :lo12:.LANCHOR32
	mov	w0, 4
	strb	w0, [x25, 17]
	cmp	w24, 8
	strb	wzr, [x25, 20]
	ldrh	w0, [x1, 10]
	ldrb	w1, [x1, 12]
	strh	wzr, [x25, 22]
	sdiv	w0, w0, w1
	mov	w1, 16
	strh	w0, [x25, 18]
	mov	w0, 70
	csel	w0, w0, w1, hi
	strb	w0, [x25, 21]
	mov	w1, 12
	add	x0, x25, 12
	bl	js_hash
	str	w0, [x25, 8]
	sub	w0, w20, #4
	str	w0, [x29, 196]
.L2142:
	adrp	x27, .LANCHOR3
	mov	x23, x21
	add	x27, x27, :lo12:.LANCHOR3
	adrp	x0, .LANCHOR24
	mov	w28, 0
	add	x0, x0, :lo12:.LANCHOR24
	str	x0, [x29, 144]
.L2145:
	ldr	w0, [x29, 156]
	cmp	w0, w28
	bhi	.L2156
	ldr	x0, [x29, 160]
	add	x22, x22, :lo12:.LANCHOR32
	mov	w24, 4
	mov	w25, 0
	mov	w28, 0
	ldr	x23, [x0, #:lo12:.LANCHOR141]
	ldrb	w0, [x22, 9]
	str	w0, [x29, 144]
	ldrh	w0, [x22, 26]
	ldr	w1, [x29, 144]
	mul	w0, w0, w1
	adrp	x1, .LANCHOR51
	strb	wzr, [x1, #:lo12:.LANCHOR51]
	udiv	w1, w19, w0
	msub	w0, w1, w0, w19
	str	w0, [x29, 168]
	sub	w0, w19, w0
	str	w0, [x29, 152]
	ldr	w0, [x29, 168]
	and	w0, w0, 3
	str	w0, [x29, 160]
	ldr	w0, [x29, 196]
	str	w0, [x29, 156]
	adrp	x0, .LANCHOR3
	add	x0, x0, :lo12:.LANCHOR3
	str	x0, [x29, 112]
.L2157:
	ldr	w0, [x29, 156]
	cmp	w25, w0
	bcc	.L2171
	ldr	x0, [x29, 184]
	ldrb	w1, [x29, 136]
	strb	w1, [x0]
	ldr	w0, [x29, 200]
	cbz	w0, .L2172
	mov	w0, 0
	bl	zftl_flash_exit_slc_mode
	adrp	x0, .LANCHOR0
	strb	wzr, [x0, #:lo12:.LANCHOR0]
	adrp	x0, .LANCHOR24
	strb	wzr, [x0, #:lo12:.LANCHOR24]
.L2172:
	ldr	w0, [x29, 196]
	mov	x2, 0
	lsl	w1, w0, 7
	adrp	x0, .LANCHOR141
	ldr	x0, [x0, #:lo12:.LANCHOR141]
.L2173:
	mov	w22, w2
	cmp	w2, w1
	bcc	.L2174
	ldr	w0, [x29, 180]
	add	w0, w0, 1
	str	w0, [x29, 180]
	cmp	w0, 5
	bls	.L2138
	b	.L2183
.L2130:
	ldr	w0, [x29, 204]
	cmp	w0, 3
	beq	.L2187
	cmp	w0, 2
	mov	w0, 2
	csel	w0, wzr, w0, ne
	str	w0, [x29, 172]
	ldr	w0, [x29, 204]
	cmp	w0, 2
	mov	w0, 3
	csel	w0, wzr, w0, ne
	b	.L2241
.L2187:
	ldr	w0, [x29, 204]
	str	w0, [x29, 172]
	mov	w0, 2
	b	.L2241
.L2134:
	ldr	w5, [x21, w0, uxtw 2]
	str	w5, [x1, 2048]
	b	.L2135
.L2141:
	mov	w0, 0
	bl	zftl_flash_exit_slc_mode
	strb	wzr, [x24, #:lo12:.LANCHOR0]
	strb	wzr, [x22, #:lo12:.LANCHOR24]
	b	.L2139
.L2191:
	mov	x25, 0
	str	w20, [x29, 196]
	b	.L2142
.L2156:
	ldr	w0, [x29, 168]
	adrp	x2, .LANCHOR24
	add	w4, w0, w28
	ldrb	w2, [x2, #:lo12:.LANCHOR24]
	ubfx	x4, x4, 2, 16
	add	w1, w4, 1
	ldrh	w0, [x27, w1, sxtw 1]
	cbz	w2, .L2147
	adrp	x0, .LANCHOR1
	ldrb	w7, [x0, #:lo12:.LANCHOR1]
	lsl	w0, w1, 1
	cmp	w7, 0
	csel	w0, w0, w1, ne
.L2147:
	adrp	x1, .LANCHOR27
	ldrb	w1, [x1, #:lo12:.LANCHOR27]
	cmp	w1, 9
	bne	.L2149
.L2242:
	str	w0, [x29, 208]
	mov	w0, 61424
	str	w0, [x29, 212]
	ldrh	w0, [x27, w4, sxtw 1]
	cbnz	w2, .L2151
	mov	w4, w0
.L2152:
	mul	w0, w24, w4
	cbnz	x25, .L2153
	str	w4, [x29, 152]
	add	x2, x29, 208
	mov	x1, x23
	add	w0, w0, w26
	bl	fw_flash_page_prog.constprop.29
	ldr	x0, [x29, 144]
	ldr	w4, [x29, 152]
	ldrb	w0, [x0]
	cbnz	w0, .L2154
	udiv	w1, w26, w24
	add	w2, w4, 1
	bl	id_block_prog_msb_ff_data
.L2154:
	ldr	w0, [x29, 196]
	add	x23, x23, 2048
	add	w0, w0, 16
	cmp	w28, w0
	bcc	.L2155
	ldr	w0, [x29, 196]
	add	w1, w0, 20
	add	x0, x21, 2048
	cmp	w28, w1
	csel	x23, x0, x23, cc
.L2155:
	add	w5, w28, 4
	mov	x25, 0
	and	w28, w5, 65535
	b	.L2145
.L2149:
	sub	w0, w0, #1
	lsl	w0, w0, 2
	b	.L2242
.L2151:
	adrp	x0, .LANCHOR1
	ldrb	w1, [x0, #:lo12:.LANCHOR1]
	lsl	w0, w4, 1
	cmp	w1, 0
	csel	w4, w0, w4, ne
	b	.L2152
.L2153:
	add	x2, x29, 208
	mov	x1, x25
	add	w0, w0, w26
	bl	fw_flash_page_prog.constprop.29
	b	.L2155
.L2171:
	ldr	w0, [x29, 160]
	adrp	x1, .LANCHOR24
	sub	w27, w24, w0
	ldr	w0, [x29, 168]
	ldrb	w1, [x1, #:lo12:.LANCHOR24]
	and	w27, w27, 65535
	add	w22, w0, w25
	ldr	x0, [x29, 112]
	udiv	w22, w22, w24
	and	w22, w22, 65535
	ldrh	w0, [x0, w22, sxtw 1]
	cbnz	w1, .L2158
	mov	w22, w0
.L2159:
	adrp	x0, .LANCHOR22
	ldr	w1, [x29, 152]
	ldrb	w26, [x0, #:lo12:.LANCHOR22]
	ldr	w0, [x29, 160]
	add	w0, w0, w1
	ldr	w1, [x29, 144]
	madd	w22, w1, w22, w0
	adrp	x0, .LANCHOR32+9
	ldrb	w0, [x0, #:lo12:.LANCHOR32+9]
	udiv	w22, w22, w0
	adrp	x0, .LANCHOR49
	ldrb	w0, [x0, #:lo12:.LANCHOR49]
	str	w0, [x29, 132]
	mov	w0, w26
	bl	nandc_bch_sel
	adrp	x0, .LANCHOR26
	add	x0, x0, :lo12:.LANCHOR26
	str	x0, [x29, 120]
.L2160:
	mov	w4, w24
	add	x3, x29, 208
	mov	x2, x23
	mov	w1, w22
	mov	w0, 0
	bl	flash_read_page
	mov	w5, w0
	cmn	w0, #1
	bne	.L2161
	ldr	x0, [x29, 184]
	ldrb	w6, [x0]
	cbnz	w6, .L2162
.L2165:
	adrp	x0, .LANCHOR171
	ldr	x6, [x0, #:lo12:.LANCHOR171]
	cbnz	x6, .L2163
.L2164:
	ldr	x0, [x29, 120]
	ldrb	w0, [x0]
	cbz	w0, .L2161
	mov	w4, w24
	add	x3, x29, 208
	mov	x2, x23
	mov	w1, w22
	mov	w0, 0
	bl	flash_ddr_tuning_read
	b	.L2243
.L2158:
	adrp	x0, .LANCHOR1
	ldrb	w1, [x0, #:lo12:.LANCHOR1]
	lsl	w0, w22, 1
	cmp	w1, 0
	csel	w22, w0, w22, ne
	b	.L2159
.L2162:
	ldr	x0, [x29, 184]
	mov	w1, w22
	stp	w6, w5, [x29, 104]
	mov	w4, w24
	add	x3, x29, 208
	mov	x2, x23
	strb	wzr, [x0]
	mov	w0, 0
	bl	flash_read_page
	cmn	w0, #1
	ldr	x1, [x29, 184]
	ldp	w6, w5, [x29, 104]
	strb	w6, [x1]
	beq	.L2165
.L2243:
	mov	w5, w0
.L2161:
	cmn	w5, #1
	cset	w4, eq
	cmp	w26, 16
	cset	w0, ne
	tst	w4, w0
	beq	.L2167
	mov	w0, 16
	mov	w26, 16
	bl	nandc_bch_sel
	b	.L2160
.L2163:
	str	w5, [x29, 108]
	mov	w4, w24
	add	x3, x29, 208
	mov	x2, x23
	mov	w1, w22
	mov	w0, 0
	blr	x6
	cmn	w0, #1
	ldr	w5, [x29, 108]
	beq	.L2164
	b	.L2243
.L2167:
	ldr	w0, [x29, 132]
	bl	nandc_bch_sel
	cmp	w4, 0
	ldr	w0, [x29, 152]
	csinv	w28, w28, wzr, eq
	cmp	w25, 0
	ccmp	w19, w0, 0, eq
	bne	.L2169
	cbnz	w28, .L2169
	ldr	w1, [x23]
	mov	w0, 18766
	movk	w0, 0x464e, lsl 16
	cmp	w1, w0
	bne	.L2169
	ldr	w0, [x29, 156]
	ldrb	w24, [x23, 17]
	add	w0, w0, w27
	str	w0, [x29, 156]
.L2170:
	add	w25, w27, w25
	and	w25, w25, 65535
	b	.L2157
.L2169:
	ubfiz	x0, x27, 9, 16
	str	wzr, [x29, 160]
	add	x23, x23, x0
	b	.L2170
.L2174:
	ldr	w4, [x0, x2, lsl 2]
	add	x2, x2, 1
	add	x3, x21, x2, lsl 2
	ldr	w3, [x3, -4]
	cmp	w4, w3
	beq	.L2173
	mov	w2, 512
	mov	w1, 0
	bl	ftl_memset
	mov	w1, w22
	adrp	x0, .LC133
	add	x0, x0, :lo12:.LC133
	bl	printf
	mov	w1, w19
	mov	w0, 0
	bl	flash_erase_block
.L2138:
	ldr	w0, [x29, 192]
	add	w0, w0, 1
	str	w0, [x29, 192]
	cmp	w0, 4
	bne	.L2176
.L2183:
	mov	w0, 0
	bl	zftl_flash_exit_slc_mode
	adrp	x0, .LANCHOR0
	ldrb	w1, [x29, 176]
	strb	w1, [x0, #:lo12:.LANCHOR0]
	ldr	w0, [x29, 200]
	cbz	w0, .L2177
	adrp	x0, .LANCHOR24
	ldrb	w1, [x29, 204]
	strb	w1, [x0, #:lo12:.LANCHOR24]
.L2177:
	mov	w1, 2
	adrp	x0, .LANCHOR33
	strb	w1, [x0, #:lo12:.LANCHOR33]
	mov	w0, 0
	bl	zftl_flash_enter_slc_mode
	ldr	w0, [x29, 180]
	cbnz	w0, .L2129
	adrp	x0, .LC134
	mov	w1, 0
	add	x0, x0, :lo12:.LC134
	bl	printf
.L2129:
	adrp	x0, .LANCHOR139
	adrp	x19, .LANCHOR138
	str	wzr, [x0, #:lo12:.LANCHOR139]
	adrp	x0, .LANCHOR140
	strb	wzr, [x0, #:lo12:.LANCHOR140]
	ldr	x0, [x19, #:lo12:.LANCHOR138]
	cbz	x0, .L2179
	bl	free
	str	xzr, [x19, #:lo12:.LANCHOR138]
.L2179:
	adrp	x19, .LANCHOR141
	ldr	x0, [x19, #:lo12:.LANCHOR141]
	cbz	x0, .L2181
	bl	free
	str	xzr, [x19, #:lo12:.LANCHOR141]
.L2181:
	adrp	x0, .LANCHOR174
	ldr	w1, [x29, 140]
	str	w1, [x0, #:lo12:.LANCHOR174]
.L2185:
	mov	w0, 0
.L2116:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 272
	ret
	.size	idb_write_data, .-idb_write_data
	.section	.text.flash_start_tlc_page_prog,"ax",@progbits
	.align	2
	.global	flash_start_tlc_page_prog
	.type	flash_start_tlc_page_prog, %function
flash_start_tlc_page_prog:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x25, x26, [sp, 64]
	and	w25, w0, 255
	adrp	x0, .LANCHOR23
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	and	w21, w1, 255
	stp	x23, x24, [sp, 48]
	and	w26, w3, 255
	ldrb	w1, [x0, #:lo12:.LANCHOR23]
	and	w22, w2, 255
	mov	w20, w4
	mov	x23, x5
	mov	x24, x6
	cmp	w1, w26
	mov	x19, x0
	bhi	.L2246
	adrp	x1, .LANCHOR175
	adrp	x0, .LC0
	mov	w2, 868
	add	x1, x1, :lo12:.LANCHOR175
	add	x0, x0, :lo12:.LC0
	bl	printf
.L2246:
	ldrb	w0, [x19, #:lo12:.LANCHOR23]
	cmp	w0, w26
	bls	.L2245
	adrp	x0, .LANCHOR29
	add	x0, x0, :lo12:.LANCHOR29
	ldrb	w5, [x0, w26, sxtw]
	adrp	x0, .LANCHOR7
	ldr	x19, [x0, #:lo12:.LANCHOR7]
	mov	w0, w5
	bl	nandc_cs
	cbz	w25, .L2248
	sxtw	x0, w5
	add	x0, x0, 8
	add	x0, x19, x0, lsl 8
	str	w25, [x0, 8]
.L2248:
	ubfiz	x0, x5, 8, 8
	add	x19, x19, x0
	mov	w0, 128
	str	w21, [x19, 2056]
	str	w0, [x19, 2056]
	and	w0, w20, 255
	str	wzr, [x19, 2052]
	str	wzr, [x19, 2052]
	str	w0, [x19, 2052]
	lsr	w0, w20, 8
	str	w0, [x19, 2052]
	lsr	w0, w20, 16
	add	w20, w20, w20, lsl 1
	str	w0, [x19, 2052]
	sub	w0, w20, #1
	add	w0, w0, w21
	bl	nandc_set_seed
	adrp	x0, .LANCHOR32+9
	mov	x4, x24
	mov	x3, x23
	mov	w1, 1
	ldrb	w2, [x0, #:lo12:.LANCHOR32+9]
	mov	w0, w5
	bl	nandc_xfer
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	str	w22, [x19, 2056]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 80
	b	nandc_de_cs.constprop.32
.L2245:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.size	flash_start_tlc_page_prog, .-flash_start_tlc_page_prog
	.section	.text.queue_tlc_prog_cmd,"ax",@progbits
	.align	2
	.type	queue_tlc_prog_cmd, %function
queue_tlc_prog_cmd:
	stp	x29, x30, [sp, -64]!
	mov	w2, 24
	add	x29, sp, 0
	stp	x21, x22, [sp, 32]
	mov	x21, x0
	ldr	x7, [x0]
	adrp	x0, .LANCHOR31
	mov	w22, 1
	stp	x19, x20, [sp, 16]
	ldrb	w0, [x0, #:lo12:.LANCHOR31]
	str	x23, [sp, 48]
	mov	w23, w1
	sub	w2, w2, w0
	ldr	w1, [x7, 40]
	lsl	w19, w22, w0
	adrp	x0, .LANCHOR36
	lsl	w20, w22, w2
	sub	w19, w19, #1
	ldrb	w0, [x0, #:lo12:.LANCHOR36]
	sub	w20, w20, #1
	and	w20, w20, w1
	lsr	w1, w1, w2
	and	w19, w19, w1
	and	w19, w19, 255
	cbz	w0, .L2254
	mov	w0, w19
	bl	zftl_flash_exit_slc_mode
	ldr	x0, [x21]
	mov	w4, w20
	mov	w3, w19
	mov	w1, w22
	mov	w2, 26
	ldr	x5, [x0, 8]
	ldr	x6, [x0, 24]
	mov	w0, 0
	bl	flash_start_one_pass_page_prog
	bl	nandc_wait_flash_ready
	ldr	x0, [x21, 8]
	add	w4, w20, w22
	mov	w3, w19
	mov	w1, w22
	mov	w2, 26
	ldr	x5, [x0, 8]
	ldr	x6, [x0, 24]
	mov	w0, 0
	bl	flash_start_one_pass_page_prog
	bl	nandc_wait_flash_ready
	ldr	x0, [x21, 16]
	add	w4, w20, 2
	mov	w3, w19
	mov	w2, 16
	mov	w1, w22
	ldr	x5, [x0, 8]
	ldr	x6, [x0, 24]
	mov	w0, 0
	bl	flash_start_one_pass_page_prog
.L2255:
	cbz	w23, .L2253
	ldr	x1, [x21]
	mov	w0, 4
	strb	w0, [x1, 58]
	mov	w0, 1
	strb	w0, [x1, 59]
	mov	w0, -1
	strb	w0, [x1]
	adrp	x0, .LANCHOR59
	add	x0, x0, :lo12:.LANCHOR59
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	b	buf_add_tail
.L2254:
	ldr	x5, [x7, 8]
	mov	w4, w20
	ldr	x6, [x7, 24]
	mov	w3, w19
	ldrb	w0, [x7, 60]
	mov	w1, w22
	mov	w2, 26
	bl	flash_start_tlc_page_prog
	bl	nandc_wait_flash_ready
	ldp	x7, x0, [x21]
	mov	w4, w20
	mov	w3, w19
	mov	w2, 26
	mov	w1, 2
	ldr	x5, [x0, 8]
	ldr	x6, [x0, 24]
	ldrb	w0, [x7, 60]
	bl	flash_start_tlc_page_prog
	bl	nandc_wait_flash_ready
	ldr	x0, [x21, 16]
	mov	w4, w20
	ldr	x7, [x21]
	mov	w3, w19
	mov	w2, 16
	mov	w1, 3
	ldr	x5, [x0, 8]
	ldr	x6, [x0, 24]
	ldrb	w0, [x7, 60]
	bl	flash_start_tlc_page_prog
	b	.L2255
.L2253:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.size	queue_tlc_prog_cmd, .-queue_tlc_prog_cmd
	.section	.text.sblk_3d_tlc_dump_prog,"ax",@progbits
	.align	2
	.global	sblk_3d_tlc_dump_prog
	.type	sblk_3d_tlc_dump_prog, %function
sblk_3d_tlc_dump_prog:
	stp	x29, x30, [sp, -48]!
	mov	w2, 24
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	ldr	w1, [x0, 40]
	adrp	x0, .LANCHOR31
	stp	x21, x22, [sp, 32]
	mov	w22, 1
	ldrb	w0, [x0, #:lo12:.LANCHOR31]
	sub	w2, w2, w0
	lsl	w19, w22, w0
	adrp	x0, .LANCHOR36
	lsl	w21, w22, w2
	sub	w19, w19, #1
	ldrb	w0, [x0, #:lo12:.LANCHOR36]
	sub	w21, w21, #1
	and	w21, w21, w1
	lsr	w1, w1, w2
	and	w19, w19, w1
	and	w19, w19, 255
	cbz	w0, .L2259
	mov	w0, w19
	bl	zftl_flash_exit_slc_mode
	ldr	x5, [x20, 8]
	mov	w4, w21
	ldr	x6, [x20, 24]
	mov	w3, w19
	mov	w1, w22
	mov	w2, 26
	mov	w0, 0
	bl	flash_start_one_pass_page_prog
	bl	nandc_wait_flash_ready
	ldr	x5, [x20, 8]
	add	w4, w21, w22
	ldr	x6, [x20, 24]
	mov	w3, w19
	mov	w1, w22
	mov	w2, 26
	mov	w0, 0
	bl	flash_start_one_pass_page_prog
	bl	nandc_wait_flash_ready
	ldr	x5, [x20, 8]
	add	w4, w21, 2
	ldr	x6, [x20, 24]
	mov	w3, w19
	mov	w2, 16
	mov	w1, w22
	mov	w0, 0
	bl	flash_start_one_pass_page_prog
.L2260:
	bl	nandc_wait_flash_ready
	ldr	w0, [x20, 40]
	mov	w1, 64
	ldp	x21, x22, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	b	flash_wait_device_ready
.L2259:
	ldr	x5, [x20, 8]
	mov	w4, w21
	ldr	x6, [x20, 24]
	mov	w3, w19
	mov	w1, w22
	mov	w2, 26
	mov	w0, 0
	bl	flash_start_tlc_page_prog
	bl	nandc_wait_flash_ready
	ldr	x5, [x20, 8]
	mov	w4, w21
	ldr	x6, [x20, 24]
	mov	w3, w19
	mov	w2, 26
	mov	w1, 2
	mov	w0, 0
	bl	flash_start_tlc_page_prog
	bl	nandc_wait_flash_ready
	ldr	x5, [x20, 8]
	mov	w4, w21
	ldr	x6, [x20, 24]
	mov	w3, w19
	mov	w2, 16
	mov	w1, 3
	mov	w0, 0
	bl	flash_start_tlc_page_prog
	b	.L2260
	.size	sblk_3d_tlc_dump_prog, .-sblk_3d_tlc_dump_prog
	.section	.text.flash_start_3d_mlc_page_prog,"ax",@progbits
	.align	2
	.global	flash_start_3d_mlc_page_prog
	.type	flash_start_3d_mlc_page_prog, %function
flash_start_3d_mlc_page_prog:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x21, x22, [sp, 32]
	and	w21, w0, 255
	adrp	x0, .LANCHOR23
	stp	x19, x20, [sp, 16]
	stp	x23, x24, [sp, 48]
	and	w24, w1, 255
	ldrb	w1, [x0, #:lo12:.LANCHOR23]
	mov	w20, w2
	mov	x22, x3
	mov	x23, x4
	cmp	w1, w24
	mov	x19, x0
	bhi	.L2263
	adrp	x1, .LANCHOR176
	adrp	x0, .LC0
	mov	w2, 903
	add	x1, x1, :lo12:.LANCHOR176
	add	x0, x0, :lo12:.LC0
	bl	printf
.L2263:
	ldrb	w0, [x19, #:lo12:.LANCHOR23]
	cmp	w0, w24
	bls	.L2262
	adrp	x0, .LANCHOR29
	add	x0, x0, :lo12:.LANCHOR29
	ldrb	w5, [x0, w24, sxtw]
	adrp	x0, .LANCHOR7
	ldr	x19, [x0, #:lo12:.LANCHOR7]
	mov	w0, w5
	bl	nandc_cs
	ubfiz	x0, x5, 8, 8
	add	x19, x19, x0
	mov	w0, 128
	str	w0, [x19, 2056]
	and	w0, w20, 255
	str	wzr, [x19, 2052]
	str	wzr, [x19, 2052]
	str	w0, [x19, 2052]
	lsr	w0, w20, 8
	str	w0, [x19, 2052]
	lsr	w0, w20, 16
	str	w0, [x19, 2052]
	mov	w0, w20
	bl	nandc_set_seed
	adrp	x0, .LANCHOR32+9
	mov	x4, x23
	mov	x3, x22
	mov	w1, 1
	ldrb	w2, [x0, #:lo12:.LANCHOR32+9]
	mov	w0, w5
	bl	nandc_xfer
	str	w21, [x19, 2056]
.L2262:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.size	flash_start_3d_mlc_page_prog, .-flash_start_3d_mlc_page_prog
	.section	.text.sblk_mlc_dump_prog,"ax",@progbits
	.align	2
	.global	sblk_mlc_dump_prog
	.type	sblk_mlc_dump_prog, %function
sblk_mlc_dump_prog:
	stp	x29, x30, [sp, -48]!
	mov	w2, 24
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	ldr	w1, [x0, 40]
	adrp	x0, .LANCHOR31
	str	x21, [sp, 32]
	ldrb	w19, [x0, #:lo12:.LANCHOR31]
	mov	w0, 1
	sub	w2, w2, w19
	lsl	w19, w0, w19
	sub	w19, w19, #1
	lsl	w21, w0, w2
	sub	w21, w21, #1
	and	w21, w21, w1
	lsr	w1, w1, w2
	and	w19, w19, w1
	and	w19, w19, 255
	mov	w0, w19
	bl	zftl_flash_exit_slc_mode
	adrp	x0, .LANCHOR19
	ldr	w0, [x0, #:lo12:.LANCHOR19]
	tbz	x0, 12, .L2267
	ldr	w2, [x20, 40]
	adrp	x0, .LC135
	mov	w1, w21
	add	x0, x0, :lo12:.LC135
	add	w3, w2, 1
	bl	printf
.L2267:
	ldr	x3, [x20, 8]
	mov	w2, w21
	ldr	x4, [x20, 24]
	mov	w1, w19
	mov	w0, 16
	bl	flash_start_3d_mlc_page_prog
	bl	nandc_wait_flash_ready
	ldr	x3, [x20, 8]
	add	w2, w21, 1
	ldr	x4, [x20, 24]
	mov	w1, w19
	mov	w0, 16
	bl	flash_start_3d_mlc_page_prog
	bl	nandc_wait_flash_ready
	ldr	w0, [x20, 40]
	mov	w1, 64
	bl	flash_wait_device_ready
	mov	w2, w0
	bl	nandc_de_cs.constprop.32
	ldr	x21, [sp, 32]
	mov	w0, w2
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.size	sblk_mlc_dump_prog, .-sblk_mlc_dump_prog
	.section	.text.flash_start_page_prog,"ax",@progbits
	.align	2
	.global	flash_start_page_prog
	.type	flash_start_page_prog, %function
flash_start_page_prog:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x21, x22, [sp, 32]
	and	w21, w0, 255
	adrp	x0, .LANCHOR31
	stp	x19, x20, [sp, 16]
	stp	x25, x26, [sp, 64]
	mov	w19, 24
	ldrb	w0, [x0, #:lo12:.LANCHOR31]
	mov	w20, 1
	str	x27, [sp, 80]
	adrp	x27, .LANCHOR23
	sub	w25, w19, w0
	stp	x23, x24, [sp, 48]
	lsl	w20, w20, w0
	sub	w20, w20, #1
	lsr	w0, w1, w25
	and	w20, w20, w0
	ldrb	w0, [x27, #:lo12:.LANCHOR23]
	and	w20, w20, 255
	mov	w24, w1
	mov	x22, x2
	mov	x23, x3
	cmp	w0, w20
	bhi	.L2273
	adrp	x1, .LANCHOR177
	adrp	x0, .LC0
	mov	w2, 956
	add	x1, x1, :lo12:.LANCHOR177
	add	x0, x0, :lo12:.LC0
	bl	printf
.L2273:
	ldrb	w0, [x27, #:lo12:.LANCHOR23]
	cmp	w0, w20
	bls	.L2272
	adrp	x0, .LANCHOR29
	add	x0, x0, :lo12:.LANCHOR29
	mov	w19, 1
	lsl	w19, w19, w25
	sub	w19, w19, #1
	ldrb	w26, [x0, w20, sxtw]
	adrp	x0, .LANCHOR7
	and	w19, w19, w24
	ldr	x25, [x0, #:lo12:.LANCHOR7]
	bl	nandc_rdy_status
	cbnz	w0, .L2275
	ldrb	w0, [x27, #:lo12:.LANCHOR23]
	cmp	w0, 1
	bne	.L2276
	bl	nandc_wait_flash_ready
.L2275:
	mov	w0, w26
	bl	hynix_reconfig_rr_para
	mov	w0, w26
	bl	nandc_cs
	tst	x24, 50331648
	bne	.L2277
	mov	w0, w19
	bl	slc_phy_page_address_calc
	mov	w19, w0
	adrp	x0, .LANCHOR0
	ldrb	w0, [x0, #:lo12:.LANCHOR0]
	cbz	w0, .L2278
	mov	w0, w26
	bl	zftl_flash_enter_slc_mode
.L2278:
	ubfiz	x20, x26, 8, 8
	mov	w0, 128
	add	x20, x25, x20
	str	w0, [x20, 2056]
	and	w0, w19, 255
	str	wzr, [x20, 2052]
	str	wzr, [x20, 2052]
	str	w0, [x20, 2052]
	lsr	w0, w19, 8
	str	w0, [x20, 2052]
	lsr	w0, w19, 16
	str	w0, [x20, 2052]
	adrp	x0, .LANCHOR30
	ldrb	w0, [x0, #:lo12:.LANCHOR30]
	cbz	w0, .L2279
	lsr	w0, w19, 24
	str	w0, [x20, 2052]
.L2279:
	mov	w0, w19
	bl	nandc_set_seed
	adrp	x0, .LANCHOR32+9
	mov	x4, x23
	mov	x3, x22
	mov	w1, 1
	ldrb	w2, [x0, #:lo12:.LANCHOR32+9]
	mov	w0, w26
	bl	nandc_xfer
	ldr	x27, [sp, 80]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	str	w21, [x20, 2056]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 96
	b	nandc_de_cs.constprop.32
.L2276:
	mov	w2, 64
	mov	w1, w19
	mov	w0, w20
	bl	flash_wait_device_ready_raw
	b	.L2275
.L2277:
	mov	w0, w26
	bl	zftl_flash_exit_slc_mode
	b	.L2278
.L2272:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldr	x27, [sp, 80]
	ldp	x29, x30, [sp], 96
	ret
	.size	flash_start_page_prog, .-flash_start_page_prog
	.section	.text.queue_prog_cmd,"ax",@progbits
	.align	2
	.type	queue_prog_cmd, %function
queue_prog_cmd:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	ldr	w1, [x0, 40]
	ldr	x3, [x0, 24]
	ldr	x2, [x0, 8]
	str	x19, [sp, 16]
	mov	x19, x0
	mov	w0, 16
	bl	flash_start_page_prog
	adrp	x0, .LANCHOR59
	ldr	w3, [x19, 40]
	ldrb	w1, [x0, #:lo12:.LANCHOR59]
	cmp	w1, 255
	beq	.L2288
	adrp	x2, .LANCHOR31
	mov	w5, 24
	adrp	x6, .LANCHOR55
	add	x6, x6, :lo12:.LANCHOR55
	ldrb	w4, [x2, #:lo12:.LANCHOR31]
	mov	w2, 1
	mov	x8, x6
	sub	w5, w5, w4
	lsl	w2, w2, w4
	sub	w2, w2, #1
	and	w2, w2, 65535
	asr	w3, w3, w5
	and	w3, w3, w2
.L2290:
	add	x7, x6, x1, lsl 6
	ldr	w4, [x7, 40]
	lsr	w4, w4, w5
	and	w4, w2, w4
	cmp	w3, w4
	bne	.L2289
	ldrb	w4, [x7, 58]
	cmp	w4, 7
	bne	.L2289
	mov	w1, 3
	strb	w1, [x7, 58]
.L2288:
	mov	w1, 3
	strb	w1, [x19, 58]
	mov	w1, 1
	strb	w1, [x19, 59]
	mov	w1, -1
	strb	w1, [x19]
	mov	x1, x19
	add	x0, x0, :lo12:.LANCHOR59
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	b	buf_add_tail
.L2289:
	lsl	x1, x1, 6
	ldrb	w1, [x8, x1]
	cmp	w1, 255
	bne	.L2290
	b	.L2288
	.size	queue_prog_cmd, .-queue_prog_cmd
	.section	.text.flash_complete_plane_page_read,"ax",@progbits
	.align	2
	.global	flash_complete_plane_page_read
	.type	flash_complete_plane_page_read, %function
flash_complete_plane_page_read:
	stp	x29, x30, [sp, -64]!
	mov	w4, 24
	add	x29, sp, 0
	stp	x23, x24, [sp, 48]
	mov	w24, w0
	adrp	x0, .LANCHOR31
	stp	x21, x22, [sp, 32]
	stp	x19, x20, [sp, 16]
	mov	w19, 1
	ldrb	w0, [x0, #:lo12:.LANCHOR31]
	mov	x20, x1
	mov	x21, x2
	sub	w22, w4, w0
	lsl	w19, w19, w0
	sub	w19, w19, #1
	lsr	w0, w24, w22
	and	w19, w19, w0
	adrp	x0, .LANCHOR23
	and	w19, w19, 255
	mov	x23, x0
	ldrb	w1, [x0, #:lo12:.LANCHOR23]
	cmp	w1, w19
	bhi	.L2297
	adrp	x1, .LANCHOR178
	adrp	x0, .LC0
	mov	w2, 1070
	add	x1, x1, :lo12:.LANCHOR178
	add	x0, x0, :lo12:.LC0
	bl	printf
.L2297:
	ldrb	w0, [x23, #:lo12:.LANCHOR23]
	cmp	w0, w19
	bls	.L2308
	adrp	x2, .LANCHOR29
	add	x2, x2, :lo12:.LANCHOR29
	adrp	x0, .LANCHOR7
	mov	w4, 1
	lsl	w4, w4, w22
	sub	w4, w4, #1
	ldrb	w8, [x2, w19, sxtw]
	and	w4, w4, w24
	ldr	x7, [x0, #:lo12:.LANCHOR7]
	ubfx	x24, x24, 24, 2
	mov	w0, w8
	bl	nandc_cs
	cbnz	w24, .L2299
	mov	w0, w4
	bl	slc_phy_page_address_calc
	mov	w4, w0
.L2299:
	adrp	x0, .LANCHOR25+16
	and	x1, x8, 255
	and	w6, w4, 255
	lsr	w5, w4, 8
	ldrb	w0, [x0, #:lo12:.LANCHOR25+16]
	lsr	w3, w4, 16
	adrp	x2, .LANCHOR30
	cmp	w0, 1
	adrp	x0, .LANCHOR21
	bne	.L2300
	add	x1, x7, x1, lsl 8
	mov	w7, 6
.L2326:
	str	w7, [x1, 2056]
	str	wzr, [x1, 2052]
	str	wzr, [x1, 2052]
	str	w6, [x1, 2052]
	str	w5, [x1, 2052]
	str	w3, [x1, 2052]
	ldrb	w2, [x2, #:lo12:.LANCHOR30]
	cbz	w2, .L2322
	lsr	w2, w4, 24
	str	w2, [x1, 2052]
.L2322:
	ldr	x0, [x0, #:lo12:.LANCHOR21]
	mov	w2, 224
	str	w2, [x1, 2056]
	ldrb	w0, [x0, 12]
	cmp	w0, 3
	bne	.L2306
	cbz	w24, .L2306
	adrp	x0, .LANCHOR35
	ldrb	w0, [x0, #:lo12:.LANCHOR35]
	cbnz	w0, .L2306
	adrp	x0, .LANCHOR36
	ldrb	w0, [x0, #:lo12:.LANCHOR36]
	cbnz	w0, .L2306
	add	w4, w4, w4, lsl 1
	sub	w0, w24, #1
	add	w0, w4, w0
.L2323:
	bl	nandc_set_seed
	adrp	x0, .LANCHOR32+9
	mov	x4, x21
	mov	x3, x20
	mov	w1, 0
	ldrb	w2, [x0, #:lo12:.LANCHOR32+9]
	mov	w0, w8
	bl	nandc_xfer
	mov	w2, w0
	bl	nandc_de_cs.constprop.32
	mov	w0, w2
.L2296:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
.L2300:
	ldr	x10, [x0, #:lo12:.LANCHOR21]
	add	x1, x7, x1, lsl 8
	ldrb	w10, [x10, 12]
	cmp	w10, 3
	bne	.L2303
	mov	w7, 5
	b	.L2326
.L2303:
	str	wzr, [x1, 2056]
	str	wzr, [x1, 2052]
	str	wzr, [x1, 2052]
	str	w6, [x1, 2052]
	ldrb	w2, [x2, #:lo12:.LANCHOR30]
	str	w5, [x1, 2052]
	str	w3, [x1, 2052]
	cbz	w2, .L2305
	lsr	w2, w4, 24
	str	w2, [x1, 2052]
.L2305:
	mov	w2, 5
	str	w2, [x1, 2056]
	str	wzr, [x1, 2052]
	str	wzr, [x1, 2052]
	b	.L2322
.L2306:
	mov	w0, w4
	b	.L2323
.L2308:
	mov	w0, -1
	b	.L2296
	.size	flash_complete_plane_page_read, .-flash_complete_plane_page_read
	.section	.text.flash_complete_page_read,"ax",@progbits
	.align	2
	.global	flash_complete_page_read
	.type	flash_complete_page_read, %function
flash_complete_page_read:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x21, x22, [sp, 32]
	mov	w21, w0
	adrp	x0, .LANCHOR31
	stp	x19, x20, [sp, 16]
	mov	x22, x1
	mov	w1, 24
	ldrb	w20, [x0, #:lo12:.LANCHOR31]
	mov	w0, 1
	stp	x23, x24, [sp, 48]
	mov	x23, x2
	sub	w1, w1, w20
	stp	x25, x26, [sp, 64]
	lsl	w20, w0, w20
	sub	w20, w20, #1
	lsl	w19, w0, w1
	adrp	x0, .LANCHOR23
	lsr	w1, w21, w1
	stp	x27, x28, [sp, 80]
	and	w20, w20, w1
	ldrb	w0, [x0, #:lo12:.LANCHOR23]
	sub	w19, w19, #1
	and	w20, w20, 255
	and	w19, w19, w21
	ubfx	x24, x21, 24, 2
	cmp	w0, w20
	bhi	.L2328
	adrp	x1, .LANCHOR179
	adrp	x0, .LC0
	mov	w2, 1232
	add	x1, x1, :lo12:.LANCHOR179
	add	x0, x0, :lo12:.LC0
	bl	printf
.L2328:
	adrp	x0, .LANCHOR29
	add	x0, x0, :lo12:.LANCHOR29
	ldrb	w25, [x0, w20, sxtw]
	adrp	x0, .LANCHOR7
	ldr	x4, [x0, #:lo12:.LANCHOR7]
	mov	w0, w25
	bl	nandc_cs
	cbnz	w24, .L2329
	mov	w0, w19
	bl	slc_phy_page_address_calc
	mov	w19, w0
.L2329:
	adrp	x20, .LANCHOR32
	add	x0, x20, :lo12:.LANCHOR32
	ldrb	w0, [x0, 12]
	cmp	w0, 3
	bne	.L2330
	ubfiz	x0, x25, 8, 8
	mov	w1, 5
	add	x0, x4, x0
	str	w1, [x0, 2056]
	and	w1, w19, 255
	str	wzr, [x0, 2052]
	str	wzr, [x0, 2052]
	str	w1, [x0, 2052]
	lsr	w1, w19, 8
	str	w1, [x0, 2052]
	lsr	w1, w19, 16
	str	w1, [x0, 2052]
	mov	w1, 224
	str	w1, [x0, 2056]
.L2330:
	adrp	x0, .LANCHOR21
	ldr	x0, [x0, #:lo12:.LANCHOR21]
	ldrb	w0, [x0, 12]
	cmp	w0, 3
	bne	.L2331
	cbz	w24, .L2331
	adrp	x0, .LANCHOR35
	ldrb	w0, [x0, #:lo12:.LANCHOR35]
	cbnz	w0, .L2331
	adrp	x0, .LANCHOR36
	ldrb	w0, [x0, #:lo12:.LANCHOR36]
	cbnz	w0, .L2331
	sub	w0, w24, #1
	add	w1, w19, w19, lsl 1
	add	w0, w0, w1
.L2358:
	add	x28, x20, :lo12:.LANCHOR32
	bl	nandc_set_seed
	mov	x4, x23
	mov	x3, x22
	mov	w1, 0
	mov	w0, w25
	ldrb	w2, [x28, 9]
	bl	nandc_xfer
	cmn	w0, #1
	bne	.L2333
	adrp	x26, .LANCHOR51
	ldrb	w27, [x26, #:lo12:.LANCHOR51]
	cbz	w27, .L2334
	ldrb	w4, [x28, 9]
	mov	x3, x23
	strb	wzr, [x26, #:lo12:.LANCHOR51]
	mov	x2, x22
	orr	w1, w19, w24, lsl 24
	mov	w0, w25
	bl	flash_read_page
	strb	w27, [x26, #:lo12:.LANCHOR51]
	cbnz	w24, .L2335
.L2340:
	adrp	x1, .LANCHOR0
	ldrb	w1, [x1, #:lo12:.LANCHOR0]
	cbz	w1, .L2335
	adrp	x1, .LANCHOR49
	ldrb	w1, [x1, #:lo12:.LANCHOR49]
	add	w1, w1, w1, lsl 1
	cmp	w0, w1, lsr 2
	blt	.L2335
	add	x20, x20, :lo12:.LANCHOR32
	ldrb	w1, [x20, 19]
	sub	w1, w1, #4
	and	w1, w1, 255
	cmp	w1, 4
	mov	w1, 256
	csel	w0, w0, w1, hi
.L2327:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 96
	ret
.L2331:
	mov	w0, w19
	b	.L2358
.L2335:
	cmn	w0, #1
	bne	.L2327
.L2341:
	adrp	x0, .LANCHOR171
	ldr	x5, [x0, #:lo12:.LANCHOR171]
	cbnz	x5, .L2337
.L2339:
	adrp	x0, .LANCHOR51
	mov	w3, -1
	mov	w2, w21
	mov	w1, 0
	ldrb	w4, [x0, #:lo12:.LANCHOR51]
	adrp	x0, .LC136
	add	x0, x0, :lo12:.LC136
	bl	printf
	adrp	x0, .LANCHOR26
	ldrb	w0, [x0, #:lo12:.LANCHOR26]
	cbnz	w0, .L2338
	mov	w0, -1
	b	.L2327
.L2337:
	add	x0, x20, :lo12:.LANCHOR32
	mov	x3, x23
	mov	x2, x22
	orr	w1, w19, w24, lsl 24
	ldrb	w4, [x0, 9]
	mov	w0, w25
	blr	x5
	cmn	w0, #1
	beq	.L2339
	b	.L2327
.L2338:
	add	x20, x20, :lo12:.LANCHOR32
	orr	w1, w19, w24, lsl 24
	mov	x3, x23
	mov	x2, x22
	mov	w0, w25
	ldrb	w4, [x20, 9]
	ldp	x21, x22, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 96
	b	flash_ddr_tuning_read
.L2334:
	cbz	w24, .L2340
	b	.L2341
.L2333:
	cbnz	w24, .L2327
	b	.L2340
	.size	flash_complete_page_read, .-flash_complete_page_read
	.section	.text.queue_wait_first_req_completed,"ax",@progbits
	.align	2
	.type	queue_wait_first_req_completed, %function
queue_wait_first_req_completed:
	stp	x29, x30, [sp, -96]!
	adrp	x0, .LANCHOR59
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	ldrb	w0, [x0, #:lo12:.LANCHOR59]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	cmp	w0, 255
	stp	x25, x26, [sp, 64]
	str	x27, [sp, 80]
	bne	.L2360
.L2393:
	mov	w21, 0
	b	.L2359
.L2360:
	adrp	x19, .LANCHOR55
	sxtw	x20, w0
	add	x1, x19, :lo12:.LANCHOR55
	add	x1, x1, x20, lsl 6
	ldrb	w2, [x1, 58]
	ldr	w21, [x1, 40]
	sub	w3, w2, #1
	cmp	w3, 10
	bhi	.L2393
	adrp	x1, .L2363
	add	x1, x1, :lo12:.L2363
	ldrh	w1, [x1,w3,uxtw #1]
	adr	x3, .Lrtx2363
	add	x1, x3, w1, sxth #2
	br	x1
.Lrtx2363:
	.section	.rodata.queue_wait_first_req_completed,"a",@progbits
	.align	0
	.align	2
.L2363:
	.2byte	(.L2362 - .Lrtx2363) / 4
	.2byte	(.L2364 - .Lrtx2363) / 4
	.2byte	(.L2365 - .Lrtx2363) / 4
	.2byte	(.L2365 - .Lrtx2363) / 4
	.2byte	(.L2365 - .Lrtx2363) / 4
	.2byte	(.L2365 - .Lrtx2363) / 4
	.2byte	(.L2366 - .Lrtx2363) / 4
	.2byte	(.L2367 - .Lrtx2363) / 4
	.2byte	(.L2368 - .Lrtx2363) / 4
	.2byte	(.L2365 - .Lrtx2363) / 4
	.2byte	(.L2368 - .Lrtx2363) / 4
	.section	.text.queue_wait_first_req_completed
.L2362:
	bl	nandc_wait_flash_ready
	add	x0, x19, :lo12:.LANCHOR55
	add	x0, x0, x20, lsl 6
	ldp	x1, x2, [x0, 8]
	cbz	x2, .L2369
	ldrb	w3, [x0, 56]
	adrp	x0, .LANCHOR131
	ldrb	w0, [x0, #:lo12:.LANCHOR131]
	cmp	w3, w0
	csel	x1, x1, x2, ne
.L2369:
	add	x19, x19, :lo12:.LANCHOR55
	mov	w0, w21
	add	x20, x19, x20, lsl 6
	ldr	x2, [x20, 24]
	bl	flash_complete_page_read
	str	w0, [x20, 52]
	mov	w0, 13
	strb	w0, [x20, 58]
	ldrb	w0, [x20, 2]
	orr	w0, w0, 8
	strb	w0, [x20, 2]
	b	.L2393
.L2364:
	bl	nandc_wait_flash_ready
	add	x0, x19, :lo12:.LANCHOR55
	lsl	x2, x20, 6
	add	x1, x0, x2
	ldrb	w21, [x0, x2]
	add	x0, x0, x21, lsl 6
	ldr	x24, [x0, 8]
	ldp	x26, x0, [x1, 8]
	cbz	x0, .L2370
	ldrb	w2, [x1, 56]
	adrp	x1, .LANCHOR131
	ldrb	w1, [x1, #:lo12:.LANCHOR131]
	cmp	w2, w1
	csel	x26, x26, x0, ne
.L2370:
	add	x0, x19, :lo12:.LANCHOR55
	add	x0, x0, x21, lsl 6
	ldr	x1, [x0, 16]
	cbz	x1, .L2371
	ldrb	w2, [x0, 56]
	adrp	x0, .LANCHOR131
	ldrb	w0, [x0, #:lo12:.LANCHOR131]
	cmp	w2, w0
	csel	x24, x24, x1, ne
.L2371:
	add	x22, x19, :lo12:.LANCHOR55
	mov	x1, x26
	add	x27, x22, x20, lsl 6
	add	x22, x22, x21, lsl 6
	ldr	x2, [x27, 24]
	ldr	w0, [x27, 40]
	bl	flash_complete_plane_page_read
	mov	w23, w0
	ldr	x2, [x22, 24]
	mov	x1, x24
	ldr	w0, [x22, 40]
	bl	flash_complete_plane_page_read
	mov	w25, w0
	cmn	w23, #1
	beq	.L2372
	ldr	w0, [x27, 36]
	cmn	w0, #1
	beq	.L2373
	ldr	x1, [x27, 24]
	ldr	w1, [x1, 4]
	cmp	w0, w1
	beq	.L2373
.L2372:
	adrp	x0, .LANCHOR31
	add	x22, x19, :lo12:.LANCHOR55
	add	x22, x22, x20, lsl 6
	mov	w5, 1
	ldrb	w2, [x0, #:lo12:.LANCHOR31]
	mov	w0, 24
	sub	w0, w0, w2
	ldr	x3, [x22, 24]
	lsl	w5, w5, w2
	adrp	x2, .LANCHOR131
	sub	w5, w5, #1
	ldr	w1, [x22, 40]
	ldrb	w4, [x2, #:lo12:.LANCHOR131]
	mov	x2, x26
	lsl	w6, w5, w0
	lsr	w0, w1, w0
	bic	w1, w1, w6
	and	w0, w0, w5
	bl	flash_read_page_en
	mov	w23, w0
	ldr	w2, [x22, 36]
	cmn	w2, #1
	beq	.L2374
	ldr	x0, [x22, 24]
	ldr	w4, [x0, 4]
	cmp	w2, w4
	beq	.L2374
	adrp	x1, .LANCHOR19
	ldr	w1, [x1, #:lo12:.LANCHOR19]
	tbz	x1, 6, .L2374
	ldr	w3, [x0]
	adrp	x0, .LC137
	ldr	w1, [x22, 40]
	add	x0, x0, :lo12:.LC137
	bl	printf
.L2374:
	add	x0, x19, :lo12:.LANCHOR55
	add	x0, x0, x20, lsl 6
	ldr	w1, [x0, 36]
	cmn	w1, #1
	beq	.L2373
	ldr	x0, [x0, 24]
	ldr	w0, [x0, 4]
	cmp	w1, w0
	beq	.L2373
	adrp	x1, .LANCHOR180
	adrp	x0, .LC0
	mov	w2, 431
	add	x1, x1, :lo12:.LANCHOR180
	add	x0, x0, :lo12:.LC0
	bl	printf
.L2373:
	add	x0, x19, :lo12:.LANCHOR55
	mov	w1, 13
	add	x20, x0, x20, lsl 6
	cmn	w25, #1
	strb	w1, [x20, 58]
	ldrb	w1, [x20, 2]
	str	w23, [x20, 52]
	orr	w1, w1, 8
	strb	w1, [x20, 2]
	beq	.L2375
	add	x0, x0, x21, lsl 6
	ldr	w1, [x0, 36]
	cmn	w1, #1
	beq	.L2377
	ldr	x0, [x0, 24]
	ldr	w0, [x0, 4]
	cmp	w1, w0
	beq	.L2377
.L2375:
	adrp	x0, .LANCHOR31
	add	x20, x19, :lo12:.LANCHOR55
	add	x20, x20, x21, lsl 6
	mov	w5, 1
	ldrb	w2, [x0, #:lo12:.LANCHOR31]
	mov	w0, 24
	sub	w0, w0, w2
	ldr	x3, [x20, 24]
	lsl	w5, w5, w2
	adrp	x2, .LANCHOR131
	sub	w5, w5, #1
	ldr	w1, [x20, 40]
	ldrb	w4, [x2, #:lo12:.LANCHOR131]
	mov	x2, x24
	lsl	w6, w5, w0
	lsr	w0, w1, w0
	bic	w1, w1, w6
	and	w0, w0, w5
	bl	flash_read_page_en
	ldr	w2, [x20, 36]
	cmn	w2, #1
	beq	.L2379
	ldr	x0, [x20, 24]
	ldr	w4, [x0, 4]
	cmp	w2, w4
	beq	.L2379
	adrp	x1, .LANCHOR19
	ldr	w1, [x1, #:lo12:.LANCHOR19]
	tbz	x1, 6, .L2379
	ldr	w3, [x0]
	adrp	x0, .LC137
	ldr	w1, [x20, 40]
	add	x0, x0, :lo12:.LC137
	bl	printf
.L2379:
	add	x0, x19, :lo12:.LANCHOR55
	add	x0, x0, x21, lsl 6
	ldr	w1, [x0, 36]
	cmn	w1, #1
	beq	.L2377
	ldr	x0, [x0, 24]
	ldr	w0, [x0, 4]
	cmp	w1, w0
	beq	.L2377
	adrp	x1, .LANCHOR180
	adrp	x0, .LC0
	mov	w2, 450
	add	x1, x1, :lo12:.LANCHOR180
	add	x0, x0, :lo12:.LC0
	bl	printf
.L2377:
	add	x19, x19, :lo12:.LANCHOR55
	mov	w0, 13
	add	x21, x19, x21, lsl 6
	strb	w0, [x21, 58]
	ldrb	w0, [x21, 2]
	str	w23, [x21, 52]
	orr	w0, w0, 8
	strb	w0, [x21, 2]
	b	.L2393
.L2365:
	mov	w0, w21
	mov	w1, 64
	bl	flash_wait_device_ready
	mov	w21, w0
	tbz	x21, 6, .L2393
	mov	w0, 5
	tst	w21, w0
	beq	.L2381
	add	x19, x19, :lo12:.LANCHOR55
	mov	w0, 12
	add	x20, x19, x20, lsl 6
	mov	w4, 12
	mov	w2, w21
	ldrb	w1, [x20, 1]
	ldr	w3, [x20, 40]
	strb	w0, [x20, 58]
	adrp	x0, .LC138
	add	x0, x0, :lo12:.LC138
	bl	printf
.L2451:
	mov	w0, -1
	str	w0, [x20, 52]
	b	.L2359
.L2381:
	add	x21, x19, :lo12:.LANCHOR55
	mov	w0, 13
	add	x21, x21, x20, lsl 6
	strb	w0, [x21, 58]
	adrp	x0, .LANCHOR110
	ldr	x0, [x0, #:lo12:.LANCHOR110]
	ldr	w1, [x0, 156]
	mov	w0, 20041
	str	wzr, [x21, 52]
	movk	w0, 0x444b, lsl 16
	cmp	w1, w0
	bne	.L2393
	ldrh	w0, [x21, 50]
	cbnz	w0, .L2393
	adrp	x0, .LANCHOR31
	mov	w5, 1
	adrp	x22, .LANCHOR172
	ldr	w1, [x21, 40]
	ldrb	w2, [x0, #:lo12:.LANCHOR31]
	mov	w0, 24
	ldr	x3, [x22, #:lo12:.LANCHOR172]
	sub	w0, w0, w2
	lsl	w5, w5, w2
	adrp	x2, .LANCHOR131
	sub	w5, w5, #1
	ldrb	w4, [x2, #:lo12:.LANCHOR131]
	adrp	x2, .LANCHOR173
	lsl	w6, w5, w0
	ldr	x2, [x2, #:lo12:.LANCHOR173]
	lsr	w0, w1, w0
	bic	w1, w1, w6
	and	w0, w0, w5
	bl	flash_read_page_en
	cmn	w0, #1
	beq	.L2382
	ldr	x1, [x22, #:lo12:.LANCHOR172]
	ldr	x2, [x21, 24]
	ldr	w1, [x1]
	ldr	w2, [x2]
	cmp	w2, w1
	beq	.L2393
.L2382:
	add	x19, x19, :lo12:.LANCHOR55
	adrp	x1, .LANCHOR51
	add	x20, x19, x20, lsl 6
	mov	w3, w0
	ldrb	w4, [x1, #:lo12:.LANCHOR51]
	adrp	x0, .LC139
	add	x0, x0, :lo12:.LC139
	ldrb	w1, [x20, 1]
	ldr	w2, [x20, 40]
	bl	printf
	mov	w0, -1
	str	w0, [x20, 52]
	b	.L2393
.L2368:
	cmp	w2, 11
	mov	w1, 3
	mov	w5, 10
	csel	w5, w5, w1, eq
	adrp	x1, .LANCHOR31
	mov	w4, 24
	mov	w2, 1
	add	x22, x19, :lo12:.LANCHOR55
	ldrb	w3, [x1, #:lo12:.LANCHOR31]
	ubfiz	x0, x0, 6, 8
	add	x0, x22, x0
	mov	x24, x1
	sub	w4, w4, w3
	lsl	w2, w2, w3
	sub	w2, w2, #1
	lsr	w3, w21, w4
	and	w3, w3, w2
	and	w3, w3, 65535
.L2384:
	ldrb	w1, [x0]
	cmp	w1, 255
	bne	.L2391
	mov	w21, -1
	b	.L2359
.L2391:
	sxtw	x23, w1
	ubfiz	x0, x1, 6, 8
	add	x1, x22, x23, lsl 6
	add	x0, x22, x0
	ldrb	w6, [x1, 58]
	cmp	w6, w5
	bne	.L2384
	ldr	w1, [x1, 40]
	lsr	w1, w1, w4
	and	w1, w1, w2
	cmp	w3, w1
	bne	.L2384
	mov	w0, w21
	mov	w1, 64
	bl	flash_wait_device_ready
	mov	w21, w0
	tbnz	x21, 6, .L2386
.L2450:
	mov	w21, 0
	b	.L2387
.L2386:
	tst	x21, 15
	beq	.L2388
	add	x22, x22, x20, lsl 6
	mov	w2, w0
	mov	w4, 12
	adrp	x0, .LC140
	add	x0, x0, :lo12:.LC140
	ldrb	w1, [x22, 1]
	ldr	w3, [x22, 40]
	bl	printf
	mov	w0, 12
	strb	w0, [x22, 58]
	mov	w0, -1
	str	w0, [x22, 52]
.L2387:
	add	x1, x19, :lo12:.LANCHOR55
	add	x20, x1, x20, lsl 6
	add	x1, x1, x23, lsl 6
	ldrb	w0, [x20, 58]
	strb	w0, [x1, 58]
	ldr	w0, [x20, 52]
	str	w0, [x1, 52]
.L2359:
	mov	w0, w21
	ldr	x27, [sp, 80]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 96
	ret
.L2388:
	add	x21, x22, x20, lsl 6
	mov	w0, 13
	strb	w0, [x21, 58]
	adrp	x0, .LANCHOR110
	ldr	x0, [x0, #:lo12:.LANCHOR110]
	ldr	w1, [x0, 156]
	mov	w0, 20041
	str	wzr, [x21, 52]
	movk	w0, 0x444b, lsl 16
	cmp	w1, w0
	bne	.L2450
	ldrh	w0, [x21, 50]
	cbnz	w0, .L2450
	ldrb	w2, [x24, #:lo12:.LANCHOR31]
	mov	w5, 1
	mov	w0, 24
	adrp	x22, .LANCHOR172
	sub	w0, w0, w2
	ldr	w1, [x21, 40]
	lsl	w5, w5, w2
	adrp	x2, .LANCHOR131
	sub	w5, w5, #1
	ldr	x3, [x22, #:lo12:.LANCHOR172]
	ldrb	w4, [x2, #:lo12:.LANCHOR131]
	adrp	x2, .LANCHOR173
	lsl	w6, w5, w0
	ldr	x2, [x2, #:lo12:.LANCHOR173]
	lsr	w0, w1, w0
	bic	w1, w1, w6
	and	w0, w0, w5
	bl	flash_read_page_en
	cmn	w0, #1
	beq	.L2390
	ldr	x1, [x22, #:lo12:.LANCHOR172]
	ldr	x2, [x21, 24]
	ldr	w1, [x1]
	ldr	w2, [x2]
	cmp	w2, w1
	beq	.L2450
.L2390:
	add	x21, x19, :lo12:.LANCHOR55
	adrp	x1, .LANCHOR51
	add	x21, x21, x20, lsl 6
	mov	w3, w0
	ldrb	w4, [x1, #:lo12:.LANCHOR51]
	adrp	x0, .LC141
	add	x0, x0, :lo12:.LC141
	ldrb	w1, [x21, 1]
	ldr	w2, [x21, 40]
	bl	printf
	mov	w0, -1
	str	w0, [x21, 52]
	b	.L2450
.L2366:
	mov	w0, w21
	mov	w1, 32
	bl	flash_wait_device_ready
	mov	w21, w0
	tbz	x21, 5, .L2393
	add	x19, x19, :lo12:.LANCHOR55
	tst	x21, 15
	add	x20, x19, x20, lsl 6
	beq	.L2392
	mov	w0, 12
	strb	w0, [x20, 58]
	b	.L2451
.L2392:
	mov	w0, 13
	str	wzr, [x20, 52]
	strb	w0, [x20, 58]
	b	.L2393
.L2367:
	mov	w1, 64
	mov	w0, w21
	bl	flash_wait_device_ready
	tbz	x0, 6, .L2393
	add	x19, x19, :lo12:.LANCHOR55
	add	x19, x19, x20, lsl 6
	str	w0, [x19, 52]
	mov	w0, 7
	strb	w0, [x19, 58]
	b	.L2393
	.size	queue_wait_first_req_completed, .-queue_wait_first_req_completed
	.section	.text.sblk_prog_page,"ax",@progbits
	.align	2
	.global	sblk_prog_page
	.type	sblk_prog_page, %function
sblk_prog_page:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	ldrh	w0, [x0, 50]
	and	w20, w1, 255
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	cbz	w0, .L2453
	adrp	x0, .LANCHOR19
	ldr	w0, [x0, #:lo12:.LANCHOR19]
	tbz	x0, 8, .L2453
	ldr	w1, [x19, 40]
	adrp	x0, .LC142
	mov	w2, w20
	add	x0, x0, :lo12:.LC142
	bl	printf
.L2453:
	adrp	x23, .LANCHOR44
	adrp	x25, .LANCHOR31
	add	x23, x23, :lo12:.LANCHOR44
	add	x26, x25, :lo12:.LANCHOR31
	mov	w21, 0
.L2454:
	cbnz	w20, .L2465
.L2481:
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 96
	ret
.L2465:
	ldrb	w24, [x19]
	ldr	w22, [x19, 40]
.L2455:
	mov	w1, 1
	mov	w0, w22
	bl	queue_lun_state
	cbnz	w0, .L2456
	cmp	w20, 1
	beq	.L2457
	ldrb	w0, [x23]
	cbz	w0, .L2457
	adrp	x0, .LANCHOR36
	ldrb	w0, [x0, #:lo12:.LANCHOR36]
	cbz	w0, .L2458
.L2457:
	mov	x0, x19
	bl	queue_prog_cmd
.L2459:
	subs	w20, w20, #1
	beq	.L2481
	ubfiz	x24, x24, 6, 8
	adrp	x19, .LANCHOR55
	add	x19, x19, :lo12:.LANCHOR55
	add	x19, x19, x24
	b	.L2454
.L2456:
	bl	queue_wait_first_req_completed
	bl	queue_remove_completed_req
	b	.L2455
.L2458:
	ldrb	w1, [x25, #:lo12:.LANCHOR31]
	mov	w27, 24
	mov	w0, 1
	sub	w27, w27, w1
	lsl	w0, w0, w1
	sub	w0, w0, #1
	lsr	w27, w22, w27
	and	w27, w27, w0
	ldrb	w0, [x19]
	and	w27, w27, 65535
	cmp	w0, 255
	bne	.L2460
	adrp	x1, .LANCHOR181
	adrp	x0, .LC0
	mov	w2, 697
	add	x1, x1, :lo12:.LANCHOR181
	add	x0, x0, :lo12:.LC0
	bl	printf
.L2460:
	ldrb	w0, [x19]
	adrp	x1, .LANCHOR55
	add	x1, x1, :lo12:.LANCHOR55
	mov	w3, 24
	mov	w28, 1
	add	x0, x1, x0, lsl 6
	ldr	w4, [x0, 40]
	ldrb	w0, [x26]
	sub	w3, w3, w0
	lsl	w0, w28, w0
	sub	w0, w0, #1
	lsr	w1, w4, w3
	and	w0, w0, w1
	cmp	w27, w0, uxth
	bne	.L2461
	adrp	x0, .LANCHOR74
	ldrh	w2, [x0, #:lo12:.LANCHOR74]
	adrp	x0, .LANCHOR75
	ldrb	w1, [x0, #:lo12:.LANCHOR75]
	sub	w0, w3, w2
	lsr	w5, w22, w2
	sub	w3, w1, #1
	lsl	w0, w28, w0
	sub	w0, w0, #1
	lsl	w1, w28, w2
	and	w0, w0, w3
	sub	w1, w1, #1
	and	w0, w0, 65535
	and	w1, w1, 65535
	and	w5, w0, w5
	lsr	w2, w4, w2
	and	w0, w0, w2
	and	w22, w1, w22
	cmp	w5, w0
	and	w1, w1, w4
	ccmp	w22, w1, 0, ne
	bne	.L2461
	cmp	w21, w3
	beq	.L2461
	ldr	w1, [x19, 40]
	mov	w0, 17
	ldr	x2, [x19, 8]
	add	w21, w21, w28
	ldr	x3, [x19, 24]
	bl	flash_start_page_prog
	strb	w28, [x19, 59]
	mov	w0, 9
	strb	w0, [x19, 58]
	mov	w0, -1
	strb	w0, [x19]
	mov	x1, x19
	adrp	x0, .LANCHOR59
	add	x0, x0, :lo12:.LANCHOR59
	bl	buf_add_tail
	b	.L2459
.L2461:
	mov	x0, x19
	mov	w21, 0
	bl	queue_prog_cmd
	b	.L2459
	.size	sblk_prog_page, .-sblk_prog_page
	.section	.text.sblk_wait_write_queue_completed,"ax",@progbits
	.align	2
	.global	sblk_wait_write_queue_completed
	.type	sblk_wait_write_queue_completed, %function
sblk_wait_write_queue_completed:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	adrp	x19, .LANCHOR59
	add	x19, x19, :lo12:.LANCHOR59
.L2484:
	ldrb	w0, [x19]
	cmp	w0, 255
	bne	.L2485
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L2485:
	bl	queue_wait_first_req_completed
	bl	queue_remove_completed_req
	b	.L2484
	.size	sblk_wait_write_queue_completed, .-sblk_wait_write_queue_completed
	.section	.text.ftl_flush,"ax",@progbits
	.align	2
	.global	ftl_flush
	.type	ftl_flush, %function
ftl_flush:
	stp	x29, x30, [sp, -32]!
	adrp	x0, .LANCHOR129
	add	x29, sp, 0
	ldrb	w1, [x0, #:lo12:.LANCHOR129]
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	adrp	x20, .LANCHOR182
	cbz	w1, .L2488
	ldrb	w2, [x20, #:lo12:.LANCHOR182]
	adrp	x0, .LANCHOR55
	add	x0, x0, :lo12:.LANCHOR55
	add	x0, x0, x2, lsl 6
	bl	sblk_prog_page
.L2488:
	mov	w0, -1
	strb	wzr, [x19, #:lo12:.LANCHOR129]
	strb	w0, [x20, #:lo12:.LANCHOR182]
	bl	sblk_wait_write_queue_completed
	bl	ftl_write_completed
	ldp	x19, x20, [sp, 16]
	mov	w0, -1
	ldp	x29, x30, [sp], 32
	b	ftl_vpn_decrement
	.size	ftl_flush, .-ftl_flush
	.section	.text.ftl_read_page,"ax",@progbits
	.align	2
	.global	ftl_read_page
	.type	ftl_read_page, %function
ftl_read_page:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	and	w19, w0, 255
	stp	x21, x22, [sp, 32]
	mov	w20, w1
	mov	x21, x2
	mov	x22, x3
	str	x23, [sp, 48]
	mov	w23, w4
	bl	sblk_wait_write_queue_completed
	mov	w4, w23
	mov	x3, x22
	mov	x2, x21
	mov	w1, w20
	mov	w0, w19
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	b	flash_read_page_en
	.size	ftl_read_page, .-ftl_read_page
	.section	.text.ftl_read_ppa_page,"ax",@progbits
	.align	2
	.global	ftl_read_ppa_page
	.type	ftl_read_ppa_page, %function
ftl_read_ppa_page:
	stp	x29, x30, [sp, -64]!
	mov	w5, 1
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w20, w0
	adrp	x0, .LANCHOR31
	mov	w19, 24
	stp	x21, x22, [sp, 32]
	mov	x21, x1
	ldrb	w0, [x0, #:lo12:.LANCHOR31]
	mov	x22, x2
	str	x23, [sp, 48]
	mov	w23, w3
	sub	w19, w19, w0
	lsl	w5, w5, w0
	sub	w5, w5, #1
	lsr	w19, w20, w19
	and	w19, w19, w5
	and	w19, w19, 255
	bl	sblk_wait_write_queue_completed
	mov	w4, w23
	mov	x3, x22
	mov	x2, x21
	mov	w1, w20
	mov	w0, w19
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	b	flash_read_page_en
	.size	ftl_read_ppa_page, .-ftl_read_ppa_page
	.section	.text.sblk_read_page,"ax",@progbits
	.align	2
	.global	sblk_read_page
	.type	sblk_read_page, %function
sblk_read_page:
	stp	x29, x30, [sp, -128]!
	add	x29, sp, 0
	stp	x21, x22, [sp, 32]
	and	w22, w1, 255
	stp	x27, x28, [sp, 80]
	mov	w21, w22
	stp	x19, x20, [sp, 16]
	adrp	x27, .LANCHOR31
	stp	x23, x24, [sp, 48]
	mov	x19, x0
	stp	x25, x26, [sp, 64]
	mov	x23, x0
	adrp	x25, .LANCHOR183
	add	x28, x27, :lo12:.LANCHOR31
	add	x25, x25, :lo12:.LANCHOR183
.L2498:
	cbnz	w21, .L2508
.L2521:
	adrp	x19, .LANCHOR55
	add	x19, x19, :lo12:.LANCHOR55
.L2509:
	cbnz	w22, .L2511
	ldp	x19, x20, [sp, 16]
	mov	w0, 0
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 128
	ret
.L2508:
	ldrb	w24, [x19]
	ldr	w26, [x19, 40]
.L2499:
	mov	w1, 0
	mov	w0, w26
	bl	queue_lun_state
	cbnz	w0, .L2500
	cmp	w21, 1
	beq	.L2505
	ldrb	w0, [x25]
	cbnz	w0, .L2502
.L2505:
	mov	x0, x19
	bl	queue_read_cmd
	b	.L2503
.L2500:
	bl	queue_wait_first_req_completed
	bl	queue_remove_completed_req
	b	.L2499
.L2502:
	ldrb	w1, [x27, #:lo12:.LANCHOR31]
	mov	w20, 24
	mov	w0, 1
	sub	w20, w20, w1
	lsl	w0, w0, w1
	sub	w0, w0, #1
	lsr	w20, w26, w20
	and	w20, w20, w0
	ldrb	w0, [x19]
	and	w20, w20, 65535
	cmp	w0, 255
	bne	.L2504
	adrp	x1, .LANCHOR184
	adrp	x0, .LC0
	mov	w2, 782
	add	x1, x1, :lo12:.LANCHOR184
	add	x0, x0, :lo12:.LC0
	bl	printf
.L2504:
	ldrb	w4, [x19]
	adrp	x2, .LANCHOR55
	add	x2, x2, :lo12:.LANCHOR55
	ldrb	w7, [x28]
	mov	w0, 24
	mov	w3, 1
	sbfiz	x5, x4, 6, 32
	sub	w0, w0, w7
	add	x6, x2, x5
	lsl	w3, w3, w7
	sub	w3, w3, #1
	ldr	w1, [x6, 40]
	lsr	w0, w1, w0
	and	w0, w0, w3
	cmp	w20, w0, uxth
	bne	.L2505
	adrp	x0, .LANCHOR111
	ldrh	w0, [x0, #:lo12:.LANCHOR111]
	add	w26, w0, w26
	cmp	w1, w26
	bne	.L2505
	ldr	w0, [x19, 40]
	mov	w26, -1
	ldrb	w24, [x2, x5]
	adrp	x20, .LANCHOR59
	stp	x6, x5, [x29, 96]
	add	x20, x20, :lo12:.LANCHOR59
	str	x2, [x29, 112]
	sub	w21, w21, #1
	str	w4, [x29, 120]
	bl	flash_start_plane_read
	mov	w3, 2
	strb	wzr, [x19, 59]
	strb	w3, [x19, 58]
	mov	x1, x19
	strb	w26, [x19]
	mov	x0, x20
	str	w3, [x29, 124]
	bl	buf_add_tail
	ldp	x6, x5, [x29, 96]
	strb	wzr, [x6, 59]
	ldr	x2, [x29, 112]
	mov	x0, x20
	ldp	w4, w3, [x29, 120]
	strb	w3, [x6, 58]
	strb	w26, [x2, x5]
	ubfiz	x1, x4, 6, 8
	add	x1, x2, x1
	bl	buf_add_tail
.L2503:
	subs	w21, w21, #1
	beq	.L2521
	ubfiz	x24, x24, 6, 8
	adrp	x19, .LANCHOR55
	add	x19, x19, :lo12:.LANCHOR55
	add	x19, x19, x24
	b	.L2498
.L2511:
	ldrb	w0, [x23, 58]
	cmp	w0, 13
	bne	.L2510
	ldrb	w0, [x23]
	sub	w22, w22, #1
	cmp	w0, 255
	beq	.L2510
	ubfiz	x23, x0, 6, 8
	add	x23, x19, x23
.L2510:
	bl	queue_wait_first_req_completed
	bl	queue_remove_completed_req
	b	.L2509
	.size	sblk_read_page, .-sblk_read_page
	.section	.text.gc_check_data_one_wl,"ax",@progbits
	.align	2
	.global	gc_check_data_one_wl
	.type	gc_check_data_one_wl, %function
gc_check_data_one_wl:
	sub	sp, sp, #112
	stp	x29, x30, [sp, 16]
	add	x29, sp, 16
	stp	x19, x20, [sp, 32]
	adrp	x19, .LANCHOR70
	stp	x21, x22, [sp, 48]
	add	x22, x19, :lo12:.LANCHOR70
	adrp	x20, .LANCHOR12
	stp	x23, x24, [sp, 64]
	stp	x25, x26, [sp, 80]
	ldr	x0, [x22, 8]
	stp	x27, x28, [sp, 96]
	ldr	x21, [x20, #:lo12:.LANCHOR12]
	cbnz	x0, .L2524
	mov	w0, 1
	bl	buf_alloc
	str	x0, [x22, 8]
.L2524:
	add	x0, x19, :lo12:.LANCHOR70
	ldr	x22, [x0, 8]
	cbnz	x22, .L2525
	adrp	x1, .LANCHOR185
	adrp	x0, .LC0
	mov	w2, 729
	add	x1, x1, :lo12:.LANCHOR185
	add	x0, x0, :lo12:.LC0
	bl	printf
.L2525:
	adrp	x27, .LANCHOR111
	adrp	x28, .LANCHOR78
	add	x26, x21, 96
	add	x27, x27, :lo12:.LANCHOR111
	add	x28, x28, :lo12:.LANCHOR78
	mov	w25, 0
.L2526:
	ldrb	w0, [x21, 89]
	cmp	w25, w0
	bge	.L2537
	mov	w24, 1
	add	x23, x19, :lo12:.LANCHOR70
	b	.L2538
.L2536:
	ldrh	w0, [x26]
	ldrh	w2, [x27]
	ldrb	w1, [x28]
	cmp	w1, 2
	mul	w2, w0, w2
	beq	.L2527
	adrp	x0, .LANCHOR35
	ldrb	w0, [x0, #:lo12:.LANCHOR35]
	cbz	w0, .L2528
.L2527:
	ldrh	w0, [x23, 16]
	sub	w3, w0, #1
	add	w0, w24, w2
	add	w0, w3, w0
	orr	w1, w0, w1, lsl 24
	str	w1, [x22, 40]
.L2529:
	mov	w1, 1
	mov	x0, x22
	bl	sblk_read_page
	ldr	w2, [x22, 52]
	adrp	x1, .LANCHOR159
	cmn	w2, #1
	beq	.L2532
	ldrh	w0, [x23, 22]
	ldr	x4, [x1, #:lo12:.LANCHOR159]
	ldr	x3, [x22, 24]
	lsl	x0, x0, 2
	ldr	w5, [x4, x0]
	ldr	w4, [x3, 4]
	cmp	w5, w4
	bne	.L2532
	adrp	x4, .LANCHOR160
	ldr	x4, [x4, #:lo12:.LANCHOR160]
	ldr	w4, [x4, x0]
	ldr	w0, [x3, 8]
	cmp	w4, w0
	beq	.L2533
.L2532:
	ldrh	w0, [x23, 22]
	ldr	x1, [x1, #:lo12:.LANCHOR159]
	lsl	x0, x0, 2
	ldr	w3, [x1, x0]
	cmn	w3, #1
	beq	.L2533
	adrp	x1, .LANCHOR19
	ldr	w1, [x1, #:lo12:.LANCHOR19]
	tbz	x1, 10, .L2534
	ldr	x1, [x22, 24]
	adrp	x4, .LANCHOR160
	ldr	x4, [x4, #:lo12:.LANCHOR160]
	ldr	w5, [x1, 12]
	str	w5, [sp]
	ldr	w4, [x4, x0]
	adrp	x0, .LC143
	ldp	w5, w6, [x1]
	add	x0, x0, :lo12:.LC143
	ldr	w7, [x1, 8]
	ldr	w1, [x22, 40]
	bl	printf
.L2534:
	adrp	x0, .LANCHOR124
	ldrh	w1, [x21, 80]
	ldrb	w2, [x0, #:lo12:.LANCHOR124]
	adrp	x0, .LANCHOR11
	ldr	x0, [x0, #:lo12:.LANCHOR11]
	strh	wzr, [x0, x1, lsl 1]
	ldr	x1, [x20, #:lo12:.LANCHOR12]
	ldr	w0, [x1, 556]
	add	w0, w0, 1
	str	w0, [x1, 556]
	adrp	x0, .LANCHOR110
	ldr	x0, [x0, #:lo12:.LANCHOR110]
	ldr	w1, [x0, 156]
	mov	w0, 20041
	movk	w0, 0x444b, lsl 16
	cmp	w1, w0
	bne	.L2541
	cbnz	w2, .L2541
	adrp	x0, .LANCHOR80
	ldrb	w0, [x0, #:lo12:.LANCHOR80]
	cbnz	w0, .L2541
	ldr	w0, [x22, 40]
	bl	ftl_mask_bad_block
.L2541:
	mov	w0, -1
.L2523:
	ldp	x19, x20, [sp, 32]
	ldp	x21, x22, [sp, 48]
	ldp	x23, x24, [sp, 64]
	ldp	x25, x26, [sp, 80]
	ldp	x27, x28, [sp, 96]
	ldp	x29, x30, [sp, 16]
	add	sp, sp, 112
	ret
.L2528:
	cmp	w1, 3
	ldrh	w0, [x23, 16]
	bne	.L2530
	adrp	x1, .LANCHOR36
	ldrb	w1, [x1, #:lo12:.LANCHOR36]
	cbz	w1, .L2531
	add	w0, w0, w0, lsl 1
	sub	w1, w0, #1
	add	w0, w24, w2
	add	w0, w1, w0
	orr	w0, w0, 50331648
.L2556:
	str	w0, [x22, 40]
	b	.L2529
.L2531:
	add	w0, w0, w2
	orr	w0, w0, w24, lsl 24
	b	.L2556
.L2530:
	add	w0, w0, w2
	b	.L2556
.L2533:
	ldrh	w0, [x23, 22]
	add	w24, w24, 1
	add	w0, w0, 1
	strh	w0, [x23, 22]
.L2538:
	ldrh	w0, [x23, 20]
	cmp	w24, w0
	ble	.L2536
	add	w25, w25, 1
	add	x26, x26, 2
	b	.L2526
.L2537:
	add	x19, x19, :lo12:.LANCHOR70
	ldrh	w0, [x19, 16]
	add	w1, w0, 1
	strh	w1, [x19, 16]
	adrp	x1, .LANCHOR80
	ldrb	w1, [x1, #:lo12:.LANCHOR80]
	cbz	w1, .L2542
	add	w0, w0, 2
	strh	w0, [x19, 16]
.L2542:
.L2535:
	mov	w0, 0
	b	.L2523
	.size	gc_check_data_one_wl, .-gc_check_data_one_wl
	.section	.text.sblk_tlc_prog_one_page,"ax",@progbits
	.align	2
	.global	sblk_tlc_prog_one_page
	.type	sblk_tlc_prog_one_page, %function
sblk_tlc_prog_one_page:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	ldr	x0, [x0]
	ldr	w20, [x0, 40]
.L2558:
	mov	w1, 1
	mov	w0, w20
	bl	queue_lun_state
	cbnz	w0, .L2559
	mov	x0, x19
	mov	w1, 1
	bl	queue_tlc_prog_cmd
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L2559:
	bl	queue_wait_first_req_completed
	bl	queue_remove_completed_req
	b	.L2558
	.size	sblk_tlc_prog_one_page, .-sblk_tlc_prog_one_page
	.section	.text.sblk_xlc_prog_pages,"ax",@progbits
	.align	2
	.global	sblk_xlc_prog_pages
	.type	sblk_xlc_prog_pages, %function
sblk_xlc_prog_pages:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	ldr	x0, [x0]
	stp	x21, x22, [sp, 32]
	mov	x22, x1
	stp	x23, x24, [sp, 48]
	mov	w24, w2
	ldr	w19, [x0, 40]
	str	x25, [sp, 64]
.L2562:
	mov	w1, 1
	mov	w0, w19
	bl	queue_lun_state
	cbnz	w0, .L2563
	cmp	w24, 2
	bne	.L2564
	adrp	x0, .LANCHOR44
	ldr	x3, [x22]
	ldrb	w0, [x0, #:lo12:.LANCHOR44]
	cbz	w0, .L2565
	adrp	x0, .LANCHOR31
	ldr	x7, [x20]
	mov	w25, 1
	mov	w2, 24
	ldrb	w0, [x0, #:lo12:.LANCHOR31]
	ldr	w3, [x3, 40]
	sub	w2, w2, w0
	ldr	w1, [x7, 40]
	lsl	w19, w25, w0
	adrp	x0, .LANCHOR36
	lsl	w21, w25, w2
	sub	w19, w19, #1
	ldrb	w0, [x0, #:lo12:.LANCHOR36]
	sub	w21, w21, #1
	and	w23, w1, w21
	lsr	w1, w1, w2
	and	w19, w19, w1
	and	w21, w21, w3
	and	w19, w19, 255
	cbz	w0, .L2566
	mov	w0, w19
	bl	zftl_flash_exit_slc_mode
	ldr	x0, [x20]
	mov	w4, w23
	mov	w3, w19
	mov	w1, w25
	mov	w2, 17
	ldr	x5, [x0, 8]
	ldr	x6, [x0, 24]
	mov	w0, 0
	bl	flash_start_one_pass_page_prog
	bl	nandc_wait_flash_ready
	ldr	x0, [x22]
	mov	w4, w21
	mov	w3, w19
	mov	w1, w25
	mov	w2, 26
	ldr	x5, [x0, 8]
	ldr	x6, [x0, 24]
	mov	w0, 0
	bl	flash_start_one_pass_page_prog
	bl	nandc_wait_flash_ready
	ldr	x0, [x20, 8]
	add	w4, w23, w25
	mov	w3, w19
	mov	w1, w24
	mov	w2, 17
	ldr	x5, [x0, 8]
	ldr	x6, [x0, 24]
	mov	w0, 0
	bl	flash_start_one_pass_page_prog
	bl	nandc_wait_flash_ready
	ldr	x0, [x22, 8]
	add	w4, w21, w25
	mov	w3, w19
	mov	w1, w24
	mov	w2, 26
	ldr	x5, [x0, 8]
	ldr	x6, [x0, 24]
	mov	w0, 0
	bl	flash_start_one_pass_page_prog
	bl	nandc_wait_flash_ready
	ldr	x0, [x20, 16]
	add	w4, w23, 2
	mov	w3, w19
	mov	w2, 17
	mov	w1, 3
	ldr	x5, [x0, 8]
	ldr	x6, [x0, 24]
	mov	w0, 0
	bl	flash_start_one_pass_page_prog
	bl	nandc_wait_flash_ready
	ldr	x0, [x22, 16]
	add	w4, w21, 2
	mov	w3, w19
	mov	w2, 16
	mov	w1, 3
	ldr	x5, [x0, 8]
	ldr	x6, [x0, 24]
	mov	w0, 0
	bl	flash_start_one_pass_page_prog
.L2567:
	ldr	x1, [x20]
	mov	w0, 5
	strb	w0, [x1, 58]
	mov	w0, 1
	strb	w0, [x1, 59]
	mov	w0, -1
	strb	w0, [x1]
	adrp	x0, .LANCHOR59
	add	x0, x0, :lo12:.LANCHOR59
	bl	buf_add_tail
.L2568:
	mov	w0, 0
	ldr	x25, [sp, 64]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
.L2563:
	bl	queue_wait_first_req_completed
	bl	queue_remove_completed_req
	b	.L2562
.L2566:
	ldr	x5, [x7, 8]
	mov	w4, w23
	ldr	x6, [x7, 24]
	mov	w3, w19
	ldrb	w0, [x7, 60]
	mov	w1, w25
	mov	w2, 17
	bl	flash_start_tlc_page_prog
	bl	nandc_wait_flash_ready
	ldr	x7, [x20]
	mov	w4, w21
	ldr	x0, [x22]
	mov	w3, w19
	mov	w1, w25
	mov	w2, 26
	ldr	x5, [x0, 8]
	ldr	x6, [x0, 24]
	ldrb	w0, [x7, 60]
	bl	flash_start_tlc_page_prog
	bl	nandc_wait_flash_ready
	ldp	x7, x0, [x20]
	mov	w4, w23
	mov	w3, w19
	mov	w1, w24
	mov	w2, 17
	ldr	x5, [x0, 8]
	ldr	x6, [x0, 24]
	ldrb	w0, [x7, 60]
	bl	flash_start_tlc_page_prog
	bl	nandc_wait_flash_ready
	ldr	x7, [x20]
	mov	w4, w21
	ldr	x0, [x22, 8]
	mov	w3, w19
	mov	w1, w24
	mov	w2, 26
	ldr	x5, [x0, 8]
	ldr	x6, [x0, 24]
	ldrb	w0, [x7, 60]
	bl	flash_start_tlc_page_prog
	bl	nandc_wait_flash_ready
	ldr	x7, [x20]
	mov	w4, w23
	ldr	x0, [x20, 16]
	mov	w3, w19
	mov	w2, 17
	mov	w1, 3
	ldr	x5, [x0, 8]
	ldr	x6, [x0, 24]
	ldrb	w0, [x7, 60]
	bl	flash_start_tlc_page_prog
	bl	nandc_wait_flash_ready
	ldr	x0, [x22, 16]
	mov	w4, w21
	ldr	x7, [x20]
	mov	w3, w19
	mov	w2, 16
	mov	w1, 3
	ldr	x5, [x0, 8]
	ldr	x6, [x0, 24]
	ldrb	w0, [x7, 60]
	bl	flash_start_tlc_page_prog
	b	.L2567
.L2565:
	ldr	w19, [x3, 40]
.L2569:
	mov	w1, 1
	mov	w0, w19
	bl	queue_lun_state
	cbnz	w0, .L2570
	mov	w1, 1
	mov	x0, x20
	bl	queue_tlc_prog_cmd
	mov	w1, 0
	mov	x0, x22
	bl	queue_tlc_prog_cmd
.L2571:
	mov	w1, 1
	mov	w0, w19
	bl	queue_lun_state
	cbz	w0, .L2568
	bl	queue_wait_first_req_completed
	bl	queue_remove_completed_req
	b	.L2571
.L2570:
	bl	queue_wait_first_req_completed
	bl	queue_remove_completed_req
	b	.L2569
.L2564:
	mov	w1, 1
	mov	x0, x20
	bl	queue_tlc_prog_cmd
	b	.L2568
	.size	sblk_xlc_prog_pages, .-sblk_xlc_prog_pages
	.section	.text.sblk_3d_mlc_prog_pages,"ax",@progbits
	.align	2
	.global	sblk_3d_mlc_prog_pages
	.type	sblk_3d_mlc_prog_pages, %function
sblk_3d_mlc_prog_pages:
	stp	x29, x30, [sp, -80]!
	ubfiz	x1, x1, 4, 32
	add	x1, x1, 8
	add	x29, sp, 0
	stp	x21, x22, [sp, 32]
	add	x21, x0, x1
	stp	x23, x24, [sp, 48]
	adrp	x23, .LANCHOR31
	adrp	x24, .LANCHOR59
	str	x25, [sp, 64]
	add	x23, x23, :lo12:.LANCHOR31
	add	x24, x24, :lo12:.LANCHOR59
	add	x25, x0, 8
	stp	x19, x20, [sp, 16]
	mov	w22, 1
.L2575:
	cmp	x21, x25
	bne	.L2578
	mov	w0, 0
	ldr	x25, [sp, 64]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
.L2578:
	ldr	x0, [x25, -8]
	ldr	w19, [x0, 40]
.L2576:
	mov	w1, 1
	mov	w0, w19
	bl	queue_lun_state
	cbnz	w0, .L2577
	ldr	x0, [x25, -8]
	mov	w2, 24
	ldrb	w1, [x23]
	add	x25, x25, 16
	sub	w2, w2, w1
	ldr	w0, [x0, 40]
	lsl	w19, w22, w1
	lsl	w20, w22, w2
	sub	w19, w19, #1
	sub	w20, w20, #1
	and	w20, w20, w0
	lsr	w0, w0, w2
	and	w19, w19, w0
	and	w19, w19, 255
	mov	w0, w19
	bl	zftl_flash_exit_slc_mode
	ldr	x0, [x25, -24]
	mov	w2, w20
	mov	w1, w19
	ldr	x3, [x0, 8]
	ldr	x4, [x0, 24]
	mov	w0, 16
	bl	flash_start_3d_mlc_page_prog
	bl	nandc_wait_flash_ready
	ldr	x0, [x25, -16]
	add	w2, w20, 1
	mov	w1, w19
	ldr	x3, [x0, 8]
	ldr	x4, [x0, 24]
	mov	w0, 16
	bl	flash_start_3d_mlc_page_prog
	bl	nandc_de_cs.constprop.32
	ldr	x1, [x25, -24]
	mov	w0, 4
	strb	w22, [x1, 59]
	strb	w0, [x1, 58]
	mov	w0, -1
	strb	w0, [x1]
	mov	x0, x24
	bl	buf_add_tail
	b	.L2575
.L2577:
	bl	queue_wait_first_req_completed
	bl	queue_remove_completed_req
	b	.L2576
	.size	sblk_3d_mlc_prog_pages, .-sblk_3d_mlc_prog_pages
	.section	.text.flash_prog_page_en,"ax",@progbits
	.align	2
	.global	flash_prog_page_en
	.type	flash_prog_page_en, %function
flash_prog_page_en:
	stp	x29, x30, [sp, -128]!
	add	x29, sp, 0
	stp	x21, x22, [sp, 32]
	and	w21, w0, 255
	and	w0, w5, 255
	stp	x19, x20, [sp, 16]
	str	w0, [x29, 124]
	adrp	x0, .LANCHOR23
	stp	x23, x24, [sp, 48]
	mov	w20, w1
	stp	x27, x28, [sp, 80]
	mov	x23, x2
	ldrb	w1, [x0, #:lo12:.LANCHOR23]
	mov	x22, x3
	stp	x25, x26, [sp, 64]
	mov	w28, w4
	ubfx	x24, x20, 24, 2
	cmp	w1, w21
	mov	x19, x0
	bhi	.L2581
	adrp	x1, .LANCHOR186
	adrp	x0, .LC0
	mov	w2, 642
	add	x1, x1, :lo12:.LANCHOR186
	add	x0, x0, :lo12:.LC0
	bl	printf
.L2581:
	ldrb	w0, [x19, #:lo12:.LANCHOR23]
	cmp	w0, w21
	bls	.L2592
	adrp	x0, .LANCHOR29
	add	x0, x0, :lo12:.LANCHOR29
	ldrb	w27, [x0, w21, sxtw]
	cbnz	w24, .L2594
	adrp	x0, .LANCHOR0
	ldrb	w1, [x0, #:lo12:.LANCHOR0]
	adrp	x0, .LANCHOR1
	cbz	w1, .L2584
	ldrb	w1, [x0, #:lo12:.LANCHOR1]
	cbz	w1, .L2594
.L2584:
	adrp	x1, .LANCHOR2
	ldrb	w0, [x0, #:lo12:.LANCHOR1]
	ldrh	w1, [x1, #:lo12:.LANCHOR2]
	udiv	w19, w20, w1
	mul	w19, w19, w1
	sub	w1, w20, w19
	cbz	w0, .L2585
	add	w19, w19, w1, lsl 1
.L2583:
	adrp	x24, .LANCHOR19
	adrp	x25, .LC144
	add	x24, x24, :lo12:.LANCHOR19
	add	x25, x25, :lo12:.LC144
	adrp	x26, .LANCHOR172
.L2589:
	ldr	w0, [x24]
	tbz	x0, 4, .L2586
	mov	w3, w19
	mov	w2, w20
	mov	w1, w27
	mov	x0, x25
	bl	printf
.L2586:
	mov	w4, w28
	mov	x3, x22
	mov	x2, x23
	mov	w1, w19
	mov	w0, w27
	bl	flash_prog_page
	mov	w5, w0
	ldr	w0, [x29, 124]
	cbz	w0, .L2587
	adrp	x6, .LANCHOR173
	ldr	x3, [x26, #:lo12:.LANCHOR172]
	mov	w4, w28
	str	x6, [x29, 112]
	ldr	x2, [x6, #:lo12:.LANCHOR173]
	mov	w1, w20
	mov	w0, w21
	str	w5, [x29, 104]
	bl	flash_read_page_en
	cmp	w0, 512
	ldr	x6, [x29, 112]
	mov	w4, w0
	ccmn	w0, #1, 4, ne
	mov	x7, x6
	beq	.L2588
	ldr	x0, [x6, #:lo12:.LANCHOR173]
	ldr	w1, [x23]
	ldr	w5, [x29, 104]
	ldr	w0, [x0]
	cmp	w1, w0
	bne	.L2588
	ldr	x0, [x26, #:lo12:.LANCHOR172]
	ldr	w1, [x22]
	ldr	w0, [x0]
	cmp	w1, w0
	beq	.L2587
.L2588:
	str	w4, [x29, 112]
	mov	w3, 4
	str	x7, [x29, 104]
	mov	w2, w3
	mov	x1, x23
	adrp	x0, .LC145
	add	x0, x0, :lo12:.LC145
	bl	rknand_print_hex
	mov	w3, 4
	mov	x1, x22
	mov	w2, w3
	adrp	x0, .LC146
	add	x0, x0, :lo12:.LC146
	bl	rknand_print_hex
	adrp	x0, .LANCHOR172
	mov	w3, 4
	mov	w2, w3
	ldr	x1, [x0, #:lo12:.LANCHOR172]
	adrp	x0, .LC147
	add	x0, x0, :lo12:.LC147
	bl	rknand_print_hex
	ldr	x7, [x29, 104]
	mov	w3, 4
	adrp	x0, .LC148
	mov	w2, w3
	add	x0, x0, :lo12:.LC148
	ldr	x1, [x7, #:lo12:.LANCHOR173]
	bl	rknand_print_hex
	ldr	w4, [x29, 112]
	cmp	w4, 512
	beq	.L2589
.L2591:
	mov	w1, w20
	adrp	x0, .LC149
	add	x0, x0, :lo12:.LC149
	bl	printf
	adrp	x1, .LANCHOR186
	adrp	x0, .LC0
	mov	w2, 685
	add	x1, x1, :lo12:.LANCHOR186
	add	x0, x0, :lo12:.LC0
	bl	printf
.L2592:
	mov	w0, -1
	b	.L2580
.L2585:
	adrp	x0, .LANCHOR3
	add	x0, x0, :lo12:.LANCHOR3
	ldrh	w0, [x0, w1, uxtw 1]
	add	w19, w0, w19
	b	.L2583
.L2594:
	mov	w19, w20
	b	.L2583
.L2587:
	mov	w0, w5
	cmn	w5, #1
	beq	.L2591
.L2580:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 128
	ret
	.size	flash_prog_page_en, .-flash_prog_page_en
	.section	.text.ftl_test_block,"ax",@progbits
	.align	2
	.global	ftl_test_block
	.type	ftl_test_block, %function
ftl_test_block:
	stp	x29, x30, [sp, -128]!
	add	x29, sp, 0
	stp	x23, x24, [sp, 48]
	adrp	x24, .LANCHOR187
	stp	x21, x22, [sp, 32]
	and	w21, w0, 65535
	ldr	x0, [x24, #:lo12:.LANCHOR187]
	mov	w23, 0
	stp	x25, x26, [sp, 64]
	adrp	x25, .LANCHOR188
	stp	x19, x20, [sp, 16]
	adrp	x26, .LANCHOR112
	stp	x27, x28, [sp, 80]
	mov	w20, 0
	str	wzr, [x0]
	add	x0, x26, :lo12:.LANCHOR112
	adrp	x27, .LANCHOR75
	str	x0, [x29, 112]
	str	wzr, [x25, #:lo12:.LANCHOR188]
	add	x0, x27, :lo12:.LANCHOR75
	str	x0, [x29, 96]
.L2611:
	ldr	x0, [x29, 112]
	ldrb	w0, [x0]
	cmp	w0, w20
	bls	.L2621
	add	x0, x27, :lo12:.LANCHOR75
	mov	w22, 0
	str	x0, [x29, 120]
	adrp	x0, .LANCHOR19
	add	x0, x0, :lo12:.LANCHOR19
	str	x0, [x29, 104]
	b	.L2622
.L2620:
	ldr	x0, [x29, 104]
	ldr	w0, [x0]
	tbz	x0, 12, .L2612
	adrp	x0, .LC150
	mov	w1, w21
	add	x0, x0, :lo12:.LC150
	bl	printf
.L2612:
	ldr	x0, [x29, 96]
	ldrb	w19, [x0]
	madd	w19, w21, w19, w22
	and	w19, w19, 65535
	cbnz	w20, .L2613
	adrp	x0, .LANCHOR6
	ldr	x0, [x0, #:lo12:.LANCHOR6]
	ldrb	w0, [x0, 47]
	cmp	w0, w19
	bcs	.L2614
.L2613:
	and	w28, w20, 255
	mov	w1, w19
	mov	w0, w28
	bl	flash_check_bad_block
	cbnz	w0, .L2614
	adrp	x0, .LANCHOR111
	mov	w1, w23
	ldrh	w7, [x0, #:lo12:.LANCHOR111]
	mov	w0, w28
	mul	w26, w7, w19
	mov	w2, w26
	bl	flash_erase_block_en
	cbz	w0, .L2615
	adrp	x0, .LANCHOR78
	ldrb	w0, [x0, #:lo12:.LANCHOR78]
	cmp	w0, 2
	bne	.L2637
	adrp	x0, .LANCHOR0
	ldrb	w0, [x0, #:lo12:.LANCHOR0]
	cbz	w0, .L2637
	mov	w2, w26
	mov	w1, 1
	mov	w0, w28
	bl	flash_erase_block_en
	cbnz	w0, .L2637
.L2619:
	adrp	x0, .LANCHOR78
	mov	w23, 1
	ldrb	w0, [x0, #:lo12:.LANCHOR78]
	add	w26, w26, w0, lsl 24
.L2618:
	adrp	x0, .LANCHOR131
	ldr	x2, [x24, #:lo12:.LANCHOR187]
	mov	w5, 1
	add	x3, x25, :lo12:.LANCHOR188
	ldrb	w4, [x0, #:lo12:.LANCHOR131]
	mov	w1, w26
	mov	w0, w28
	bl	flash_prog_page_en
	cbz	w0, .L2614
.L2637:
	mov	w1, w19
	mov	w0, w28
	bl	flash_mask_bad_block
.L2614:
	add	w22, w22, 1
	and	w22, w22, 65535
.L2622:
	ldr	x0, [x29, 120]
	ldrb	w0, [x0]
	cmp	w0, w22
	bhi	.L2620
	add	w20, w20, 1
	and	w20, w20, 65535
	b	.L2611
.L2615:
	cbz	w23, .L2618
	b	.L2619
.L2621:
	cbz	w23, .L2623
	adrp	x0, .LANCHOR9
	mov	w1, 2
	ldr	x0, [x0, #:lo12:.LANCHOR9]
	add	x21, x0, x21, uxth 2
	ldrb	w0, [x21, 2]
	bfi	w0, w1, 3, 2
	strb	w0, [x21, 2]
.L2623:
	ldp	x19, x20, [sp, 16]
	mov	w0, 0
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 128
	ret
	.size	ftl_test_block, .-ftl_test_block
	.section	.text.ftl_prog_page,"ax",@progbits
	.align	2
	.global	ftl_prog_page
	.type	ftl_prog_page, %function
ftl_prog_page:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	and	w19, w0, 255
	stp	x21, x22, [sp, 32]
	mov	w20, w1
	mov	x21, x2
	mov	x22, x3
	str	x23, [sp, 48]
	mov	w23, w4
	bl	sblk_wait_write_queue_completed
	mov	w0, w19
	mov	w5, 1
	mov	w4, w23
	mov	x3, x22
	mov	x2, x21
	mov	w1, w20
	bl	flash_prog_page_en
	mov	w19, w0
	cmn	w0, #1
	bne	.L2638
	mov	w2, 2678
	adrp	x1, .LANCHOR189
	adrp	x0, .LC0
	add	x1, x1, :lo12:.LANCHOR189
	add	x0, x0, :lo12:.LC0
	bl	printf
	adrp	x0, .LC149
	mov	w1, w20
	add	x0, x0, :lo12:.LC149
	bl	printf
.L2638:
	mov	w0, w19
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.size	ftl_prog_page, .-ftl_prog_page
	.section	.text.ftl_info_flush,"ax",@progbits
	.align	2
	.global	ftl_info_flush
	.type	ftl_info_flush, %function
ftl_info_flush:
	stp	x29, x30, [sp, -128]!
	mov	w1, 0
	add	x29, sp, 0
	stp	x21, x22, [sp, 32]
	adrp	x21, .LANCHOR131
	stp	x23, x24, [sp, 48]
	adrp	x24, .LANCHOR110
	ldrb	w2, [x21, #:lo12:.LANCHOR131]
	stp	x19, x20, [sp, 16]
	adrp	x20, .LANCHOR190
	str	w0, [x29, 116]
	add	x0, x20, :lo12:.LANCHOR190
	stp	x25, x26, [sp, 64]
	lsl	w2, w2, 1
	stp	x27, x28, [sp, 80]
	bl	ftl_memset
	ldr	x0, [x24, #:lo12:.LANCHOR110]
	ldrh	w1, [x0, 74]
	cmp	w1, 1
	bls	.L2642
	strh	wzr, [x0, 150]
.L2642:
	adrp	x23, .LANCHOR191
	add	x19, x23, :lo12:.LANCHOR191
	adrp	x25, .LANCHOR111
	mov	w26, 0
	add	x0, x25, :lo12:.LANCHOR111
	str	x0, [x29, 104]
.L2655:
	add	x0, x23, :lo12:.LANCHOR191
	adrp	x22, .LANCHOR192
	ldrh	w1, [x25, #:lo12:.LANCHOR111]
	add	x7, x20, :lo12:.LANCHOR190
	str	w1, [x29, 120]
	ldrh	w27, [x0, 2]
	ldr	x0, [x24, #:lo12:.LANCHOR110]
	ldrb	w1, [x21, #:lo12:.LANCHOR131]
	ldrb	w28, [x23, #:lo12:.LANCHOR191]
	ldr	w6, [x0, 4]
	lsl	w1, w1, 9
	add	w6, w6, 1
	str	w6, [x0, 4]
	ldr	w0, [x29, 116]
	str	w0, [x20, #:lo12:.LANCHOR190]
	ldr	x0, [x22, #:lo12:.LANCHOR192]
	str	w6, [x7, 4]
	bl	js_hash
	str	w0, [x7, 8]
	adrp	x0, .LANCHOR19
	ldr	w0, [x0, #:lo12:.LANCHOR19]
	tbz	x0, 12, .L2643
	adrp	x0, .LC151
	mov	w3, w6
	mov	w2, w27
	mov	w1, w28
	add	x0, x0, :lo12:.LC151
	bl	printf
.L2643:
	adrp	x1, .LANCHOR94
	ldrh	w0, [x19, 2]
	ldrh	w1, [x1, #:lo12:.LANCHOR94]
	cmp	w1, w0
	bhi	.L2644
	adrp	x27, .LANCHOR193
	adrp	x3, .LC0
	add	x27, x27, :lo12:.LANCHOR193
	add	x3, x3, :lo12:.LC0
.L2651:
	ldrb	w0, [x19, 1]
	adrp	x28, .LANCHOR6
	add	w0, w0, 1
	and	w0, w0, 255
	strb	w0, [x19, 1]
	cmp	w0, 7
	bls	.L2645
	mov	x0, 0
.L2650:
	ldr	x2, [x28, #:lo12:.LANCHOR6]
	add	w1, w0, 8
	and	w26, w0, 65535
	add	x1, x2, x1, sxtw
	ldrb	w2, [x1, 32]
	add	w1, w2, 127
	and	w1, w1, 255
	cmp	w1, 125
	bhi	.L2646
	mov	x0, x3
	str	x3, [x29, 120]
	mov	w2, 846
	mov	x1, x27
	bl	printf
	ldr	x3, [x29, 120]
.L2649:
	strb	w26, [x19, 1]
	mov	w26, 1
.L2645:
	ldr	x0, [x28, #:lo12:.LANCHOR6]
	ldrb	w1, [x19, 1]
	add	x0, x0, x1
	ldrb	w28, [x0, 40]
	strb	w28, [x19]
	cmp	w28, 255
	beq	.L2651
	ldr	x0, [x29, 104]
	ldrh	w27, [x0]
	mov	w0, 0
	mul	w27, w27, w28
	mov	w1, w27
	bl	flash_erase_block
	ldrb	w4, [x21, #:lo12:.LANCHOR131]
	mov	w1, w27
	ldr	x2, [x22, #:lo12:.LANCHOR192]
	add	x3, x20, :lo12:.LANCHOR190
	mov	w0, 0
	add	w27, w27, 1
	bl	ftl_prog_page
	mov	w0, 1
	strh	w0, [x19, 2]
.L2652:
	ldrb	w4, [x21, #:lo12:.LANCHOR131]
	mov	w1, w27
	ldr	x2, [x22, #:lo12:.LANCHOR192]
	add	x3, x20, :lo12:.LANCHOR190
	mov	w0, 0
	bl	ftl_prog_page
	cmn	w0, #1
	ldrh	w1, [x19, 2]
	adrp	x0, .LANCHOR194
	add	w1, w1, 1
	strh	w1, [x19, 2]
	beq	.L2653
	ldrb	w1, [x0, #:lo12:.LANCHOR194]
	cbz	w1, .L2654
.L2653:
	strb	wzr, [x0, #:lo12:.LANCHOR194]
	b	.L2655
.L2646:
	cmp	w2, 255
	bne	.L2649
	add	x0, x0, 1
	cmp	x0, 8
	bne	.L2650
	mov	w26, w0
	b	.L2649
.L2644:
	ldr	w1, [x29, 120]
	madd	w27, w1, w28, w27
	cbnz	w0, .L2652
	mov	w1, w27
	bl	flash_erase_block
	b	.L2652
.L2654:
	cbnz	w26, .L2656
.L2664:
	adrp	x0, .LANCHOR191
	ldrb	w0, [x0, #:lo12:.LANCHOR191]
	cmp	w0, 255
	bne	.L2658
	adrp	x1, .LANCHOR193
	adrp	x0, .LC0
	mov	w2, 890
	add	x1, x1, :lo12:.LANCHOR193
	add	x0, x0, :lo12:.LC0
	bl	printf
.L2658:
	ldp	x19, x20, [sp, 16]
	mov	w0, 0
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 128
	ret
.L2656:
	ldrb	w19, [x19, 1]
	adrp	x20, .LANCHOR193
	adrp	x21, .LC0
	add	x20, x20, :lo12:.LANCHOR193
	add	w19, w19, 1
	add	x21, x21, :lo12:.LC0
	adrp	x22, .LANCHOR6
.L2659:
	cmp	w19, 7
	bhi	.L2664
	ldr	x1, [x22, #:lo12:.LANCHOR6]
	add	w0, w19, 8
	add	x0, x1, x0, sxtw
	ldrb	w23, [x0, 32]
	add	w0, w23, 127
	and	w0, w0, 255
	cmp	w0, 125
	bhi	.L2660
	mov	w2, 881
	mov	x1, x20
	mov	x0, x21
	bl	printf
.L2661:
	adrp	x0, .LANCHOR111
	ldrh	w1, [x0, #:lo12:.LANCHOR111]
	mov	w0, 0
	mul	w1, w1, w23
	bl	flash_erase_block
	b	.L2662
.L2660:
	cmp	w23, 255
	bne	.L2661
.L2662:
	add	w19, w19, 1
	and	w19, w19, 65535
	b	.L2659
	.size	ftl_info_flush, .-ftl_info_flush
	.section	.text.ftl_info_blk_init,"ax",@progbits
	.align	2
	.global	ftl_info_blk_init
	.type	ftl_info_blk_init, %function
ftl_info_blk_init:
	stp	x29, x30, [sp, -112]!
	adrp	x0, .LANCHOR195
	adrp	x1, .LANCHOR194
	mov	w2, 16384
	add	x29, sp, 0
	strb	wzr, [x0, #:lo12:.LANCHOR195]
	mov	w0, 1
	strb	w0, [x1, #:lo12:.LANCHOR194]
	adrp	x1, .LANCHOR196
	stp	x21, x22, [sp, 32]
	adrp	x21, .LANCHOR192
	strb	w0, [x1, #:lo12:.LANCHOR196]
	adrp	x1, .LANCHOR9
	ldr	x0, [x21, #:lo12:.LANCHOR192]
	mov	x22, 7
	str	x0, [x1, #:lo12:.LANCHOR9]
	adrp	x1, .LANCHOR8
	stp	x19, x20, [sp, 16]
	adrp	x19, .LANCHOR110
	ldrh	w1, [x1, #:lo12:.LANCHOR8]
	adrp	x20, .LANCHOR191
	stp	x23, x24, [sp, 48]
	adrp	x23, .LANCHOR6
	stp	x25, x26, [sp, 64]
	adrp	x24, .LANCHOR131
	add	x1, x0, x1, lsl 2
	stp	x27, x28, [sp, 80]
	str	x1, [x19, #:lo12:.LANCHOR110]
	mov	w1, 0
	bl	ftl_memset
	adrp	x26, .LANCHOR111
	adrp	x0, .LANCHOR197
	mov	w1, 0
	mov	w2, 16384
	mov	w27, 21574
	ldr	x0, [x0, #:lo12:.LANCHOR197]
	add	x26, x26, :lo12:.LANCHOR111
	add	x24, x24, :lo12:.LANCHOR131
	movk	w27, 0x494c, lsl 16
	bl	ftl_memset
	ldr	x1, [x23, #:lo12:.LANCHOR6]
	add	x0, x20, :lo12:.LANCHOR191
	strb	wzr, [x0, 1]
	ldrb	w1, [x1, 40]
	strb	w1, [x20, #:lo12:.LANCHOR191]
	strh	wzr, [x0, 2]
.L2680:
	ldr	x1, [x23, #:lo12:.LANCHOR6]
	add	w0, w22, 8
	sxth	w25, w22
	mov	w28, w22
	add	x0, x1, x0, sxtw
	ldrb	w0, [x0, 32]
	cmp	w0, 255
	bne	.L2679
.L2684:
	sub	x22, x22, #1
	cmn	x22, #1
	bne	.L2680
	mov	w25, 0
.L2681:
	adrp	x24, .LANCHOR19
	ldr	w0, [x24, #:lo12:.LANCHOR19]
	tbz	x0, 12, .L2685
	ldr	x0, [x19, #:lo12:.LANCHOR110]
	mov	w2, 4800
	mov	w1, w22
	ldr	w3, [x0]
	adrp	x0, .LC153
	add	x0, x0, :lo12:.LC153
	bl	printf
.L2685:
	cmn	w22, #1
	bne	.L2686
	ldr	x0, [x21, #:lo12:.LANCHOR192]
	mov	w1, 0
	mov	w2, 16384
	bl	ftl_memset
	ldr	x0, [x19, #:lo12:.LANCHOR110]
	mov	w1, 21574
	movk	w1, 0x494c, lsl 16
	str	w1, [x0]
	mov	w1, 36
	movk	w1, 0x6, lsl 16
	str	w1, [x0, 12]
	mov	w0, w22
.L2678:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
.L2679:
	ldrh	w6, [x26]
	adrp	x7, .LANCHOR190
	ldrb	w4, [x24]
	add	x7, x7, :lo12:.LANCHOR190
	ldr	x2, [x21, #:lo12:.LANCHOR192]
	mov	x3, x7
	str	x7, [x29, 96]
	mul	w6, w6, w0
	mov	w0, 0
	str	w6, [x29, 108]
	mov	w1, w6
	bl	ftl_read_page
	mov	w5, w0
	cmn	w0, #1
	ldr	w6, [x29, 108]
	ldr	x7, [x29, 96]
	bne	.L2682
	ldrb	w4, [x24]
	mov	x3, x7
	ldr	x2, [x21, #:lo12:.LANCHOR192]
	add	w1, w6, 1
	mov	w0, 0
	bl	ftl_read_page
	mov	w5, w0
.L2682:
	adrp	x0, .LANCHOR19
	ldr	w0, [x0, #:lo12:.LANCHOR19]
	tbz	x0, 12, .L2683
	ldr	x0, [x19, #:lo12:.LANCHOR110]
	mov	w2, w5
	str	w5, [x29, 108]
	mov	w3, 749
	mov	w1, w28
	ldr	w4, [x0]
	adrp	x0, .LC152
	add	x0, x0, :lo12:.LC152
	bl	printf
	ldr	w5, [x29, 108]
.L2683:
	cmn	w5, #1
	beq	.L2684
	ldr	x0, [x19, #:lo12:.LANCHOR110]
	ldr	w0, [x0]
	cmp	w0, w27
	bne	.L2684
	mov	w22, w25
	b	.L2681
.L2686:
	ldr	x1, [x23, #:lo12:.LANCHOR6]
	add	w0, w25, 8
	ldr	x2, [x21, #:lo12:.LANCHOR192]
	mov	w4, 4
	adrp	x26, .LANCHOR131
	mov	w28, 21574
	add	x0, x1, x0, sxtw
	adrp	x27, .LC154
	add	x26, x26, :lo12:.LANCHOR131
	add	x27, x27, :lo12:.LC154
	movk	w28, 0x494c, lsl 16
	ldrb	w1, [x0, 32]
	add	x0, x20, :lo12:.LANCHOR191
	strb	w1, [x20, #:lo12:.LANCHOR191]
	strb	w25, [x0, 1]
	adrp	x25, .LANCHOR190
	mov	w0, 0
	add	x3, x25, :lo12:.LANCHOR190
	bl	flash_get_last_written_page
	sxth	w22, w0
	add	w0, w0, 1
	ldrb	w23, [x20, #:lo12:.LANCHOR191]
	and	w0, w0, 65535
	str	w0, [x29, 108]
	adrp	x0, .LANCHOR111
	ldrh	w0, [x0, #:lo12:.LANCHOR111]
	madd	w23, w23, w0, w22
.L2688:
	tbnz	w22, #31, .L2692
	ldrb	w4, [x26]
	add	x5, x25, :lo12:.LANCHOR190
	ldr	x2, [x21, #:lo12:.LANCHOR192]
	mov	x3, x5
	mov	w1, w23
	mov	w0, 0
	str	x5, [x29, 96]
	bl	ftl_read_page
	cmn	w0, #1
	beq	.L2689
	ldr	x0, [x19, #:lo12:.LANCHOR110]
	ldr	x5, [x29, 96]
	ldr	w0, [x0]
	cmp	w0, w28
	bne	.L2689
	ldr	w6, [x5, 8]
	cbnz	w6, .L2690
.L2692:
	ldrh	w0, [x29, 108]
	add	x20, x20, :lo12:.LANCHOR191
	strh	w0, [x20, 2]
	bl	ftl_tmp_into_update
	ldr	x1, [x19, #:lo12:.LANCHOR110]
	ldr	w0, [x1, 64]
	add	w0, w0, 1
	str	w0, [x1, 64]
	mov	w0, 0
	bl	ftl_info_flush
	mov	w0, 0
	bl	ftl_info_flush
	ldr	w0, [x24, #:lo12:.LANCHOR19]
	tbnz	x0, 14, .L2691
.L2708:
	mov	w0, 0
	b	.L2678
.L2690:
	ldr	x0, [x21, #:lo12:.LANCHOR192]
	ldrb	w1, [x26]
	lsl	w1, w1, 9
	bl	js_hash
	cmp	w6, w0
	beq	.L2692
	mov	w1, w6
	mov	x0, x27
	bl	printf
.L2689:
	sub	w22, w22, #1
	sub	w23, w23, #1
	sxth	w22, w22
	b	.L2688
.L2691:
	ldr	x0, [x19, #:lo12:.LANCHOR110]
	ldr	w1, [x0, 156]
	adrp	x0, .LC155
	add	x0, x0, :lo12:.LC155
	bl	printf
	b	.L2708
	.size	ftl_info_blk_init, .-ftl_info_blk_init
	.section	.text.ftl_ext_info_flush,"ax",@progbits
	.align	2
	.global	ftl_ext_info_flush
	.type	ftl_ext_info_flush, %function
ftl_ext_info_flush:
	stp	x29, x30, [sp, -96]!
	adrp	x0, .LANCHOR12
	add	x29, sp, 0
	ldr	x0, [x0, #:lo12:.LANCHOR12]
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	ldr	w1, [x0, 520]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	cbz	w1, .L2710
	str	wzr, [x0, 520]
.L2710:
	adrp	x20, .LANCHOR94
	adrp	x22, .LANCHOR198
	adrp	x21, .LANCHOR31
	add	x20, x20, :lo12:.LANCHOR94
	add	x22, x22, :lo12:.LANCHOR198
	add	x21, x21, :lo12:.LANCHOR31
	mov	w0, 0
	bl	ftl_total_vpn_update
.L2711:
	adrp	x23, .LANCHOR110
	mov	x24, x23
.L2714:
	ldr	x0, [x23, #:lo12:.LANCHOR110]
	ldr	w1, [x0, 56]
	add	w1, w1, 1
	str	w1, [x0, 56]
	ldrh	w1, [x0, 140]
	ldrh	w0, [x20]
	cmp	w1, w0
	bcc	.L2712
	bl	ftl_ext_alloc_new_blk
.L2712:
	ldr	x0, [x24, #:lo12:.LANCHOR110]
	ldrh	w1, [x0, 130]
	mov	w0, 65535
	cmp	w1, w0
	bne	.L2713
	adrp	x0, .LC0
	mov	w2, 2211
	mov	x1, x22
	add	x0, x0, :lo12:.LC0
	bl	printf
.L2713:
	ldrb	w19, [x21]
	mov	w0, 24
	ldr	x1, [x24, #:lo12:.LANCHOR110]
	adrp	x26, .LANCHOR131
	sub	w19, w0, w19
	adrp	x0, .LANCHOR74
	adrp	x27, .LANCHOR190
	add	x25, x27, :lo12:.LANCHOR190
	ldrh	w0, [x0, #:lo12:.LANCHOR74]
	ldrh	w2, [x1, 130]
	sub	w0, w19, w0
	mov	w19, 1
	asr	w28, w2, w0
	lsl	w19, w19, w0
	adrp	x0, .LANCHOR111
	sub	w19, w19, #1
	and	w19, w19, w2
	ldrh	w2, [x0, #:lo12:.LANCHOR111]
	ldrh	w0, [x1, 140]
	sxth	w19, w19
	mov	w1, 0
	madd	w19, w19, w2, w0
	ldrb	w2, [x26, #:lo12:.LANCHOR131]
	mov	x0, x25
	lsl	w2, w2, 1
	bl	ftl_memset
	ldr	x0, [x24, #:lo12:.LANCHOR110]
	ldrb	w7, [x26, #:lo12:.LANCHOR131]
	str	wzr, [x27, #:lo12:.LANCHOR190]
	ldr	w0, [x0, 56]
	lsl	w1, w7, 9
	str	w0, [x25, 4]
	adrp	x0, .LANCHOR197
	ldr	x6, [x0, #:lo12:.LANCHOR197]
	mov	x0, x6
	bl	js_hash
	mov	x2, x6
	mov	w1, w19
	str	w0, [x25, 8]
	mov	w4, w7
	mov	x3, x25
	mov	w0, w28
	bl	ftl_prog_page
	ldr	x2, [x24, #:lo12:.LANCHOR110]
	ldrh	w1, [x2, 140]
	add	w1, w1, 1
	and	w1, w1, 65535
	strh	w1, [x2, 140]
	cmp	w1, 1
	beq	.L2714
	cmn	w0, #1
	adrp	x0, .LANCHOR196
	beq	.L2715
	ldrb	w1, [x0, #:lo12:.LANCHOR196]
	cbz	w1, .L2716
.L2715:
	strb	wzr, [x0, #:lo12:.LANCHOR196]
	b	.L2711
.L2716:
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 96
	ret
	.size	ftl_ext_info_flush, .-ftl_ext_info_flush
	.section	.text.ftl_ext_info_init,"ax",@progbits
	.align	2
	.global	ftl_ext_info_init
	.type	ftl_ext_info_init, %function
ftl_ext_info_init:
	stp	x29, x30, [sp, -128]!
	adrp	x0, .LANCHOR121
	adrp	x2, .LANCHOR74
	mov	w4, 4
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	adrp	x20, .LANCHOR110
	strh	wzr, [x0, #:lo12:.LANCHOR121]
	ldr	x0, [x20, #:lo12:.LANCHOR110]
	stp	x21, x22, [sp, 32]
	adrp	x21, .LANCHOR197
	stp	x27, x28, [sp, 80]
	stp	x23, x24, [sp, 48]
	adrp	x24, .LANCHOR190
	ldrh	w1, [x0, 130]
	adrp	x0, .LANCHOR31
	stp	x25, x26, [sp, 64]
	add	x3, x24, :lo12:.LANCHOR190
	ldrb	w19, [x0, #:lo12:.LANCHOR31]
	mov	w0, 24
	sub	w0, w0, w19
	ldrh	w19, [x2, #:lo12:.LANCHOR74]
	ldr	x2, [x21, #:lo12:.LANCHOR197]
	sub	w0, w0, w19
	mov	w19, 1
	lsl	w19, w19, w0
	sub	w19, w19, #1
	asr	w22, w1, w0
	and	w19, w19, w1
	and	w27, w22, 255
	mov	w1, w19
	mov	w0, w27
	bl	flash_get_last_written_page
	sxth	w23, w0
	adrp	x0, .LANCHOR19
	stp	x0, x24, [x29, 112]
	ldr	w1, [x0, #:lo12:.LANCHOR19]
	tbz	x1, 12, .L2727
	ldr	x0, [x20, #:lo12:.LANCHOR110]
	adrp	x1, .LANCHOR199
	and	w4, w22, 65535
	mov	w3, w23
	mov	w2, 2256
	add	x1, x1, :lo12:.LANCHOR199
	ldrh	w5, [x0, 130]
	adrp	x0, .LC156
	add	x0, x0, :lo12:.LC156
	bl	printf
.L2727:
	adrp	x25, .LANCHOR131
	adrp	x26, .LANCHOR111
	mov	w28, 20038
	add	x25, x25, :lo12:.LANCHOR131
	add	x26, x26, :lo12:.LANCHOR111
	mov	w24, 0
	movk	w28, 0x4549, lsl 16
.L2728:
	and	w22, w23, 65535
	sub	w0, w22, w24
	tbnz	x0, 15, .L2733
	ldr	x0, [x29, 120]
	sub	w1, w23, w24
	ldrb	w4, [x25]
	add	x5, x0, :lo12:.LANCHOR190
	ldrh	w0, [x26]
	ldr	x2, [x21, #:lo12:.LANCHOR197]
	mov	x3, x5
	str	x5, [x29, 104]
	madd	w1, w0, w19, w1
	mov	w0, w27
	bl	flash_read_page_en
	cmp	w0, 512
	ccmn	w0, #1, 4, ne
	beq	.L2729
	adrp	x0, .LANCHOR12
	ldr	x5, [x29, 104]
	ldr	x0, [x0, #:lo12:.LANCHOR12]
	ldr	w0, [x0]
	cmp	w0, w28
	bne	.L2729
	ldr	w6, [x5, 8]
	cbnz	w6, .L2730
.L2733:
	bl	zftl_sblk_list_init
	ldr	x0, [x20, #:lo12:.LANCHOR110]
	ldrh	w1, [x0, 140]
	cmp	w1, w23
	bgt	.L2732
	add	w22, w22, 1
	strh	w22, [x0, 140]
	bl	ftl_ext_info_flush
.L2732:
	adrp	x0, .LANCHOR12
	mov	w1, -1
	ldr	x0, [x0, #:lo12:.LANCHOR12]
	strh	w1, [x0, 584]
	strh	w1, [x0, 586]
	strh	w1, [x0, 588]
	strh	w1, [x0, 590]
	mov	w1, 65535
	str	w1, [x0, 560]
	mov	w1, -1
	str	w1, [x0, 564]
	ldr	x1, [x29, 112]
	str	wzr, [x0, 520]
	str	wzr, [x0, 604]
	str	wzr, [x0, 608]
	ldr	w1, [x1, #:lo12:.LANCHOR19]
	tbz	x1, 12, .L2735
	ldr	w3, [x0, 12]
	adrp	x1, .LANCHOR199
	adrp	x0, .LC158
	mov	w4, 0
	mov	w2, 0
	add	x1, x1, :lo12:.LANCHOR199
	add	x0, x0, :lo12:.LC158
	bl	printf
.L2735:
	adrp	x0, .LANCHOR72
	mov	w1, -1
	ldp	x19, x20, [sp, 16]
	strh	w1, [x0, #:lo12:.LANCHOR72]
	ldp	x21, x22, [sp, 32]
	mov	w0, 0
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 128
	ret
.L2730:
	ldr	x0, [x21, #:lo12:.LANCHOR197]
	ldrb	w1, [x25]
	lsl	w1, w1, 9
	bl	js_hash
	cmp	w6, w0
	beq	.L2733
	adrp	x0, .LC157
	mov	w1, w6
	add	x0, x0, :lo12:.LC157
	bl	printf
.L2729:
	add	w24, w24, 1
	b	.L2728
	.size	ftl_ext_info_init, .-ftl_ext_info_init
	.section	.text.ftl_prog_ppa_page,"ax",@progbits
	.align	2
	.global	ftl_prog_ppa_page
	.type	ftl_prog_ppa_page, %function
ftl_prog_ppa_page:
	adrp	x4, .LANCHOR31
	mov	w5, 1
	ldrb	w6, [x4, #:lo12:.LANCHOR31]
	mov	w4, 24
	sub	w4, w4, w6
	lsl	w7, w5, w4
	sub	w7, w7, #1
	lsl	w5, w5, w6
	sub	w6, w5, #1
	lsr	w5, w0, w4
	mov	w4, w3
	mov	x3, x2
	mov	x2, x1
	and	w1, w7, w0
	and	w0, w6, w5
	b	ftl_prog_page
	.size	ftl_prog_ppa_page, .-ftl_prog_ppa_page
	.section	.text.ftl_write_last_log_page,"ax",@progbits
	.align	2
	.global	ftl_write_last_log_page
	.type	ftl_write_last_log_page, %function
ftl_write_last_log_page:
	ldrh	w1, [x0, 6]
	cmp	w1, 1
	bne	.L2749
	stp	x29, x30, [sp, -48]!
	adrp	x1, .LANCHOR117
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	stp	x21, x22, [sp, 32]
	ldr	x20, [x1, #:lo12:.LANCHOR117]
	ldrh	w22, [x0, 12]
	bl	ftl_get_new_free_page
	mov	w21, w0
	cmn	w0, #1
	beq	.L2750
	ldrh	w0, [x19]
	add	x20, x20, x22, uxth 2
	bl	ftl_vpn_decrement
	adrp	x0, .LANCHOR188
	mov	w1, 15555
	add	x7, x0, :lo12:.LANCHOR188
	movk	w1, 0xf55f, lsl 16
	str	w1, [x0, #:lo12:.LANCHOR188]
	adrp	x0, .LANCHOR94
	ldrh	w1, [x0, #:lo12:.LANCHOR94]
	adrp	x0, .LANCHOR79
	ldrb	w0, [x0, #:lo12:.LANCHOR79]
	mul	w1, w1, w0
	mov	x0, x20
	lsl	w1, w1, 2
	bl	js_hash
	mov	x1, x7
	mov	x2, 0
	stp	w0, wzr, [x7, 4]
	mov	w0, 2
	str	wzr, [x7, 12]
	str	wzr, [x1, 16]!
	bl	ftl_debug_info_fill
	mov	x2, x7
	adrp	x0, .LANCHOR131
	mov	x1, x20
	ldrb	w3, [x0, #:lo12:.LANCHOR131]
	mov	w0, w21
	bl	ftl_prog_ppa_page
.L2750:
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
.L2749:
	mov	w0, -1
	ret
	.size	ftl_write_last_log_page, .-ftl_write_last_log_page
	.section	.text.ftl_dump_write_open_sblk,"ax",@progbits
	.align	2
	.global	ftl_dump_write_open_sblk
	.type	ftl_dump_write_open_sblk, %function
ftl_dump_write_open_sblk:
	sub	sp, sp, #224
	stp	x29, x30, [sp, 48]
	add	x29, sp, 48
	stp	x19, x20, [sp, 64]
	and	w20, w0, 65535
	adrp	x0, .LANCHOR8
	stp	x21, x22, [sp, 80]
	stp	x23, x24, [sp, 96]
	ldrh	w0, [x0, #:lo12:.LANCHOR8]
	stp	x25, x26, [sp, 112]
	stp	x27, x28, [sp, 128]
	cmp	w0, w20
	bls	.L2755
	adrp	x0, .LANCHOR83
	str	x0, [x29, 120]
	ldrb	w1, [x0, #:lo12:.LANCHOR83]
	cbnz	w1, .L2757
	adrp	x0, .LANCHOR80
	ldrb	w0, [x0, #:lo12:.LANCHOR80]
	cbz	w0, .L2755
.L2757:
	adrp	x0, .LANCHOR35
	ldrb	w0, [x0, #:lo12:.LANCHOR35]
	cbnz	w0, .L2755
	adrp	x0, .LANCHOR9
	ubfiz	x14, x20, 2, 16
	mov	x15, x0
	ldr	x1, [x0, #:lo12:.LANCHOR9]
	add	x1, x1, x14
	ldrb	w1, [x1, 2]
	and	w1, w1, 224
	cmp	w1, 160
	bne	.L2779
	adrp	x0, .LANCHOR78
	ldrb	w25, [x0, #:lo12:.LANCHOR78]
.L2758:
	add	x21, x29, 176
	adrp	x23, .LANCHOR94
	mov	w0, w20
	adrp	x26, .LANCHOR111
	add	x26, x26, :lo12:.LANCHOR111
	mov	w27, 0
	strh	w20, [x21, -32]!
	mov	w28, 0
	add	x1, x21, 16
	bl	ftl_get_blk_list_in_sblk
	ldrh	w1, [x23, #:lo12:.LANCHOR94]
	and	w0, w0, 255
	strb	w0, [x29, 153]
	strb	wzr, [x29, 149]
	strh	wzr, [x29, 146]
	mul	w0, w0, w1
	strh	wzr, [x29, 154]
	strh	w0, [x29, 150]
	ldr	x0, [x15, #:lo12:.LANCHOR9]
	add	x1, x0, x14
	ldr	w5, [x0, x14]
	ldrb	w2, [x1, 2]
	mov	w1, w20
	ldrh	w4, [x0, x14]
	adrp	x0, .LC159
	ubfx	x5, x5, 11, 8
	add	x0, x0, :lo12:.LC159
	ubfx	x3, x2, 3, 2
	and	w4, w4, 2047
	ubfx	x2, x2, 5, 3
	bl	printf
	mov	w0, 1
	bl	buf_alloc
	mov	x19, x0
	mov	w10, 0
	add	x0, x23, :lo12:.LANCHOR94
	str	x0, [x29, 128]
.L2759:
	ldr	x0, [x29, 128]
	ldrh	w0, [x0]
	cmp	w0, w27
	bls	.L2767
	lsl	w22, w27, 1
	mov	w28, 0
	sub	w0, w22, #1
	add	w22, w22, w27
	str	w0, [x29, 140]
	sub	w22, w22, #1
	adrp	x0, .LC160
	add	x0, x0, :lo12:.LC160
	str	x0, [x29, 112]
	b	.L2770
.L2779:
	mov	w25, 1
	b	.L2758
.L2768:
	ldrh	w12, [x21, x24]
	mov	w0, 65535
	cmp	w12, w0
	bne	.L2760
.L2766:
	add	w10, w10, 1
	and	w10, w10, 65535
.L2761:
	cmp	w25, w10
	bcs	.L2768
	add	w11, w28, 1
	and	w28, w11, 65535
.L2770:
	ldrb	w0, [x29, 153]
	cmp	w0, w28
	bls	.L2769
	sxtw	x24, w28
	mov	w10, 1
	add	x24, x24, 8
	lsl	x24, x24, 1
	b	.L2761
.L2760:
	ldrh	w3, [x26]
	cmp	w25, 3
	mul	w3, w3, w12
	add	w0, w3, w10
	bne	.L2762
	adrp	x1, .LANCHOR36
	ldrb	w1, [x1, #:lo12:.LANCHOR36]
	cbz	w1, .L2763
	adrp	x1, .LANCHOR78
	add	w0, w0, w22
	ldrb	w3, [x1, #:lo12:.LANCHOR78]
.L2793:
	orr	w3, w0, w3, lsl 24
	b	.L2764
.L2763:
	add	w3, w27, w3
	orr	w3, w3, w10, lsl 24
.L2764:
	str	w3, [x19, 40]
	mov	w1, 1
	stp	w10, w12, [x29, 104]
	mov	x0, x19
	str	w3, [x29, 136]
	bl	sblk_read_page
	ldr	w13, [x19, 52]
	ldp	w10, w12, [x29, 104]
	cmp	w13, 512
	ccmn	w13, #1, 4, ne
	ldr	w3, [x29, 136]
	bne	.L2766
	ldr	x1, [x19, 24]
	mov	w4, w13
	ldr	x0, [x19, 8]
	str	w10, [x29, 108]
	str	w13, [x29, 136]
	ldr	w2, [x1, 12]
	str	w2, [sp, 32]
	ldr	w2, [x1, 8]
	str	w2, [sp, 24]
	ldr	w2, [x1, 4]
	str	w2, [sp, 16]
	mov	w2, w27
	ldr	w1, [x1]
	str	w1, [sp, 8]
	ldr	w1, [x0, 12]
	str	w1, [sp]
	mov	w1, w12
	ldp	w5, w6, [x0]
	ldr	w7, [x0, 8]
	ldr	x0, [x29, 112]
	bl	printf
	ldr	w13, [x29, 136]
	ldr	w10, [x29, 108]
	cmp	w13, 512
	bne	.L2766
.L2767:
	mov	w4, w10
	mov	w3, w28
	mov	w2, w27
	mov	w1, w20
	adrp	x24, .LANCHOR131
	adrp	x0, .LC161
	add	x0, x0, :lo12:.LC161
	bl	printf
	ldr	x0, [x19, 8]
	mov	w1, 0
	ldrb	w2, [x24, #:lo12:.LANCHOR131]
	adrp	x25, .LANCHOR19
	adrp	x26, .LC162
	add	x25, x25, :lo12:.LANCHOR19
	add	x26, x26, :lo12:.LC162
	lsl	w2, w2, 9
	bl	ftl_memset
	ldr	x0, [x19, 24]
	mov	w1, 0
	ldrb	w2, [x24, #:lo12:.LANCHOR131]
	lsl	w2, w2, 1
	bl	ftl_memset
.L2771:
	ldrh	w0, [x23, #:lo12:.LANCHOR94]
	cmp	w0, w27
	bls	.L2777
	lsl	w0, w27, 1
	str	w0, [x29, 140]
	ldr	x0, [x29, 120]
	mov	w22, 0
	add	x28, x0, :lo12:.LANCHOR83
	b	.L2778
.L2762:
	cmp	w25, 2
	bne	.L2765
	adrp	x1, .LANCHOR78
	ldrb	w3, [x1, #:lo12:.LANCHOR78]
	ldr	w1, [x29, 140]
	add	w0, w1, w0
	b	.L2793
.L2765:
	add	w3, w27, w3
	b	.L2764
.L2769:
	add	w8, w27, 1
	and	w27, w8, 65535
	b	.L2759
.L2776:
	ldr	w0, [x25]
	tbz	x0, 12, .L2772
	mov	w2, w22
	mov	w1, w27
	mov	x0, x26
	bl	printf
.L2772:
	ldrb	w1, [x28]
	adrp	x2, .LANCHOR111
	sxtw	x0, w22
	cbz	w1, .L2773
	add	x0, x0, 8
	ldrh	w1, [x2, #:lo12:.LANCHOR111]
	ldrh	w0, [x21, x0, lsl 1]
	mul	w0, w0, w1
	orr	w0, w0, w27
	str	w0, [x19, 40]
	mov	x0, x19
	bl	sblk_3d_tlc_dump_prog
.L2774:
	add	w22, w22, 1
	and	w22, w22, 65535
.L2778:
	ldrb	w0, [x29, 153]
	cmp	w0, w22
	bhi	.L2776
	add	w8, w27, 1
	and	w27, w8, 65535
	b	.L2771
.L2773:
	adrp	x1, .LANCHOR78
	add	x0, x0, 8
	ldrb	w1, [x1, #:lo12:.LANCHOR78]
	cmp	w1, 2
	bne	.L2775
	ldrh	w1, [x2, #:lo12:.LANCHOR111]
	ldrh	w0, [x21, x0, lsl 1]
	mul	w0, w0, w1
	ldr	w1, [x29, 140]
	orr	w0, w0, w1
	orr	w0, w0, 33554432
	str	w0, [x19, 40]
	mov	x0, x19
	bl	sblk_mlc_dump_prog
	b	.L2774
.L2775:
	ldrh	w1, [x21, x0, lsl 1]
	mov	w6, 1
	ldrh	w0, [x2, #:lo12:.LANCHOR111]
	mov	w5, 0
	ldrb	w4, [x24, #:lo12:.LANCHOR131]
	ldr	x3, [x19, 24]
	mul	w1, w1, w0
	adrp	x0, .LANCHOR31
	ldrb	w2, [x0, #:lo12:.LANCHOR31]
	mov	w0, 24
	orr	w1, w1, w27
	str	w1, [x19, 40]
	sub	w0, w0, w2
	lsl	w6, w6, w2
	ldr	x2, [x19, 8]
	sub	w6, w6, #1
	lsl	w7, w6, w0
	lsr	w0, w1, w0
	bic	w1, w1, w7
	and	w0, w0, w6
	bl	flash_prog_page_en
	b	.L2774
.L2777:
	mov	x0, x19
	bl	zbuf_free
	adrp	x0, .LC163
	mov	w1, w20
	add	x0, x0, :lo12:.LC163
	bl	printf
.L2755:
	ldp	x19, x20, [sp, 64]
	ldp	x21, x22, [sp, 80]
	ldp	x23, x24, [sp, 96]
	ldp	x25, x26, [sp, 112]
	ldp	x27, x28, [sp, 128]
	ldp	x29, x30, [sp, 48]
	add	sp, sp, 224
	ret
	.size	ftl_dump_write_open_sblk, .-ftl_dump_write_open_sblk
	.section	.text.gc_ink_check_sblk,"ax",@progbits
	.align	2
	.global	gc_ink_check_sblk
	.type	gc_ink_check_sblk, %function
gc_ink_check_sblk:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	adrp	x19, .LANCHOR70
	add	x0, x19, :lo12:.LANCHOR70
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	ldrh	w1, [x0, 2110]
	ldr	x22, [x0, 2184]
	cmp	w1, 3
	bhi	.L2795
	adrp	x0, .L2797
	mov	x20, x19
	add	x0, x0, :lo12:.L2797
	ldrh	w0, [x0,w1,uxtw #1]
	adr	x1, .Lrtx2797
	add	x0, x1, w0, sxth #2
	br	x0
.Lrtx2797:
	.section	.rodata.gc_ink_check_sblk,"a",@progbits
	.align	0
	.align	2
.L2797:
	.2byte	(.L2796 - .Lrtx2797) / 4
	.2byte	(.L2798 - .Lrtx2797) / 4
	.2byte	(.L2799 - .Lrtx2797) / 4
	.2byte	(.L2800 - .Lrtx2797) / 4
	.section	.text.gc_ink_check_sblk
.L2796:
	adrp	x0, .LANCHOR107
	add	x24, x0, :lo12:.LANCHOR107
	ldrh	w0, [x0, #:lo12:.LANCHOR107]
	cmp	w0, 7
	bls	.L2794
	adrp	x0, .LANCHOR57
	ldrb	w0, [x0, #:lo12:.LANCHOR57]
	cmp	w0, 2
	bls	.L2794
	adrp	x21, .LANCHOR108
	add	x21, x21, :lo12:.LANCHOR108
	mov	w1, 0
	mov	x0, x21
	bl	_list_get_gc_head_node
	and	w0, w0, 65535
	mov	w23, 65535
	cmp	w0, w23
	beq	.L2794
	adrp	x22, .LANCHOR9
	ubfiz	x0, x0, 2, 16
	ldr	x1, [x22, #:lo12:.LANCHOR9]
	ldrh	w0, [x1, x0]
	and	w0, w0, 2047
	cmp	w0, 2
	bgt	.L2794
	add	x20, x19, :lo12:.LANCHOR70
	mov	w0, 1
	bl	buf_alloc
	str	x0, [x20, 2184]
	cbz	x0, .L2794
	mov	x2, x24
	mov	w1, 0
	mov	x0, x21
	bl	_list_pop_index_node
	and	w14, w0, 65535
	cmp	w14, w23
	bne	.L2804
	ldr	x0, [x20, 2184]
	bl	zbuf_free
	str	xzr, [x20, 2184]
.L2794:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
.L2804:
	add	x1, x20, 2162
	mov	w0, w14
	bl	ftl_get_blk_list_in_sblk
	strb	w0, [x20, 2155]
	mov	w0, 1
	strh	w0, [x20, 2110]
	ldr	x0, [x22, #:lo12:.LANCHOR9]
	strh	w14, [x20, 2146]
	ubfiz	x14, x14, 2, 16
	strh	wzr, [x20, 2148]
	ldrh	w1, [x0, x14]
	adrp	x0, .LANCHOR131
	ldrb	w2, [x0, #:lo12:.LANCHOR131]
	ldr	x0, [x20, 2184]
	lsl	w2, w2, 9
	tbz	x1, 0, .L2805
	mov	w1, 85
.L2820:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldr	x0, [x0, 8]
	ldp	x29, x30, [sp], 80
	b	ftl_memset
.L2805:
	mov	w1, 170
	b	.L2820
.L2798:
	add	x20, x19, :lo12:.LANCHOR70
	mov	w1, 0
	ldrh	w0, [x20, 2146]
	bl	ftl_erase_sblk
	mov	w0, 2
	strh	w0, [x20, 2110]
	b	.L2794
.L2799:
	adrp	x21, .LANCHOR111
	mov	w24, 65280
	adrp	x23, .LANCHOR31
	add	x21, x21, :lo12:.LANCHOR111
	add	x23, x23, :lo12:.LANCHOR31
	mov	w19, 0
	movk	w24, 0x55aa, lsl 16
	bl	sblk_wait_write_queue_completed
.L2806:
	add	x0, x20, :lo12:.LANCHOR70
	ldrb	w1, [x0, 2155]
	cmp	w1, w19
	bhi	.L2808
	ldrh	w1, [x0, 2148]
	adrp	x2, .LANCHOR94
	add	w1, w1, 1
	ldrh	w2, [x2, #:lo12:.LANCHOR94]
	and	w1, w1, 65535
	strh	w1, [x0, 2148]
	cmp	w2, w1
	bhi	.L2794
	mov	w1, 3
	strh	wzr, [x0, 2148]
	strh	w1, [x0, 2110]
	b	.L2794
.L2808:
	add	x1, x0, x19, sxtw 1
	ldrh	w2, [x1, 2162]
	mov	w1, 65535
	cmp	w2, w1
	beq	.L2807
	ldrh	w0, [x0, 2148]
	mov	w6, 1
	ldrh	w1, [x21]
	mov	w5, 0
	ldr	x3, [x22, 24]
	madd	w1, w1, w2, w0
	ldr	x2, [x22, 8]
	mov	w0, 24
	stp	w1, w24, [x2]
	str	wzr, [x3]
	ldrb	w4, [x23]
	sub	w0, w0, w4
	lsl	w6, w6, w4
	adrp	x4, .LANCHOR131
	sub	w6, w6, #1
	ldrb	w4, [x4, #:lo12:.LANCHOR131]
	lsl	w7, w6, w0
	lsr	w0, w1, w0
	bic	w1, w1, w7
	and	w0, w0, w6
	bl	flash_prog_page_en
.L2807:
	add	w19, w19, 1
	and	w19, w19, 65535
	b	.L2806
.L2800:
	adrp	x25, .LANCHOR111
	add	x19, x19, :lo12:.LANCHOR70
	add	x25, x25, :lo12:.LANCHOR111
	mov	w21, 0
	mov	w26, 65535
	bl	sblk_wait_write_queue_completed
.L2809:
	ldrb	w0, [x19, 2155]
	cmp	w0, w21
	bhi	.L2813
	ldrh	w0, [x19, 2148]
	adrp	x1, .LANCHOR94
	add	w0, w0, 1
	ldrh	w1, [x1, #:lo12:.LANCHOR94]
	and	w0, w0, 65535
	strh	w0, [x19, 2148]
	cmp	w1, w0
	bhi	.L2794
	ldr	x0, [x19, 2184]
	strh	wzr, [x19, 2110]
	bl	zbuf_free
	str	xzr, [x19, 2184]
	ldrh	w0, [x19, 2112]
	cmp	w0, 15
	bhi	.L2814
	add	w1, w0, 1
	add	x0, x19, x0, sxtw 1
	strh	w1, [x19, 2112]
	ldrh	w1, [x19, 2146]
	strh	w1, [x0, 2114]
.L2815:
	add	x19, x20, :lo12:.LANCHOR70
	adrp	x0, .LC164
	ldp	x21, x22, [sp, 32]
	add	x0, x0, :lo12:.LC164
	ldrh	w2, [x19, 2112]
	ldrh	w1, [x19, 2146]
	ldp	x23, x24, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	b	printf
.L2813:
	add	x24, x19, x21, sxtw 1
	add	x24, x24, 16
	ldrh	w0, [x24, 2146]
	cmp	w0, w26
	beq	.L2811
	ldrh	w1, [x19, 2148]
	ldrh	w23, [x25]
	madd	w23, w23, w0, w1
	mov	w1, 1
	str	w23, [x22, 40]
	mov	x0, x22
	bl	sblk_read_page
	ldr	x0, [x22, 8]
	ldr	w0, [x0]
	cmp	w23, w0
	beq	.L2811
	mov	w0, w23
	bl	ftl_mask_bad_block
	mov	w0, -1
	strh	w0, [x24, 2146]
.L2811:
	add	w21, w21, 1
	and	w21, w21, 65535
	b	.L2809
.L2814:
	ldrh	w0, [x19, 2146]
	bl	zftl_insert_free_list
	b	.L2815
.L2795:
	strh	wzr, [x0, 2110]
	b	.L2794
	.size	gc_ink_check_sblk, .-gc_ink_check_sblk
	.section	.text.ftl_ink_check_sblk,"ax",@progbits
	.align	2
	.global	ftl_ink_check_sblk
	.type	ftl_ink_check_sblk, %function
ftl_ink_check_sblk:
	stp	x29, x30, [sp, -144]!
	add	x29, sp, 0
	stp	x23, x24, [sp, 48]
	adrp	x24, .LANCHOR9
	stp	x19, x20, [sp, 16]
	and	w19, w0, 65535
	ldr	x0, [x24, #:lo12:.LANCHOR9]
	ubfiz	x23, x19, 2, 16
	stp	x21, x22, [sp, 32]
	mov	w1, w19
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	ldr	w3, [x0, x23]
	ldrh	w2, [x0, x23]
	adrp	x0, .LC165
	add	x0, x0, :lo12:.LC165
	ubfx	x3, x3, 11, 8
	and	w2, w2, 2047
	bl	printf
	mov	w0, 65535
	cmp	w19, w0
	beq	.L2821
	adrp	x0, .LANCHOR8
	ldrh	w0, [x0, #:lo12:.LANCHOR8]
	cmp	w0, w19
	bls	.L2821
	add	x21, x29, 144
	mov	w1, 0
	mov	w0, w19
	bl	ftl_erase_sblk
	mov	w0, w19
	adrp	x27, .LANCHOR131
	strh	w19, [x21, -32]!
	add	x1, x21, 16
	bl	ftl_get_blk_list_in_sblk
	strb	w0, [x29, 121]
	mov	w0, 1
	bl	buf_alloc
	mov	x20, x0
	ldr	x0, [x24, #:lo12:.LANCHOR9]
	ldrb	w2, [x27, #:lo12:.LANCHOR131]
	ldrh	w0, [x0, x23]
	lsl	w2, w2, 9
	and	w0, w0, 2047
	cmp	w0, 1
	bgt	.L2823
	mov	w1, 85
.L2839:
	ldr	x0, [x20, 8]
	adrp	x28, .LANCHOR111
	add	x28, x28, :lo12:.LANCHOR111
	mov	w26, 0
	bl	ftl_memset
	bl	sblk_wait_write_queue_completed
	mov	w7, 65280
	movk	w7, 0x55aa, lsl 16
.L2825:
	adrp	x25, .LANCHOR94
	ldrh	w0, [x25, #:lo12:.LANCHOR94]
	cmp	w0, w26
	bls	.L2828
	adrp	x25, .LANCHOR31
	mov	w22, 0
	add	x25, x25, :lo12:.LANCHOR31
	b	.L2829
.L2823:
	mov	w1, 170
	b	.L2839
.L2827:
	add	x0, x21, x22, sxtw 1
	mov	w1, 65535
	ldrh	w0, [x0, 16]
	cmp	w0, w1
	beq	.L2826
	ldrh	w1, [x28]
	mov	w6, 1
	ldr	x2, [x20, 8]
	mov	w5, 0
	ldr	x3, [x20, 24]
	str	w7, [x29, 108]
	madd	w1, w1, w0, w26
	mov	w0, 24
	stp	w1, w7, [x2]
	str	wzr, [x3]
	ldrb	w4, [x25]
	sub	w0, w0, w4
	lsl	w6, w6, w4
	ldrb	w4, [x27, #:lo12:.LANCHOR131]
	sub	w6, w6, #1
	lsl	w8, w6, w0
	lsr	w0, w1, w0
	bic	w1, w1, w8
	and	w0, w0, w6
	bl	flash_prog_page_en
	ldr	w7, [x29, 108]
.L2826:
	add	w22, w22, 1
	and	w22, w22, 65535
.L2829:
	ldrb	w0, [x29, 121]
	cmp	w0, w22
	bhi	.L2827
	add	w26, w26, 1
	and	w26, w26, 65535
	b	.L2825
.L2828:
	adrp	x26, .LANCHOR111
	add	x26, x26, :lo12:.LANCHOR111
	mov	w28, 0
.L2830:
	ldrh	w0, [x25, #:lo12:.LANCHOR94]
	cmp	w0, w28
	bls	.L2835
	mov	w27, 0
	b	.L2836
.L2834:
	sxtw	x22, w27
	mov	w1, 65535
	add	x22, x22, 8
	lsl	x22, x22, 1
	ldrh	w0, [x21, x22]
	cmp	w0, w1
	beq	.L2832
	ldrh	w4, [x26]
	mov	w1, 1
	madd	w4, w4, w0, w28
	mov	x0, x20
	str	w4, [x20, 40]
	str	w4, [x29, 108]
	bl	sblk_read_page
	ldr	x0, [x20, 8]
	ldr	w4, [x29, 108]
	ldr	w0, [x0]
	cmp	w4, w0
	beq	.L2832
	mov	w0, w4
	bl	ftl_mask_bad_block
	mov	w0, -1
	strh	w0, [x21, x22]
.L2832:
	add	w2, w27, 1
	and	w27, w2, 65535
.L2836:
	ldrb	w0, [x29, 121]
	cmp	w0, w27
	bhi	.L2834
	add	w3, w28, 1
	and	w28, w3, 65535
	b	.L2830
.L2835:
	mov	x0, x20
	bl	zbuf_free
	ldr	x0, [x24, #:lo12:.LANCHOR9]
	mov	w1, w19
	ldr	w3, [x0, x23]
	ldrh	w2, [x0, x23]
	adrp	x0, .LC166
	add	x0, x0, :lo12:.LC166
	ubfx	x3, x3, 11, 8
	and	w2, w2, 2047
	bl	printf
.L2821:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 144
	ret
	.size	ftl_ink_check_sblk, .-ftl_ink_check_sblk
	.section	.text.ftl_alloc_sblk,"ax",@progbits
	.align	2
	.global	ftl_alloc_sblk
	.type	ftl_alloc_sblk, %function
ftl_alloc_sblk:
	stp	x29, x30, [sp, -80]!
	cmp	w0, 5
	add	x29, sp, 0
	stp	x23, x24, [sp, 48]
	and	w23, w0, 65535
	stp	x21, x22, [sp, 32]
	mov	w1, w23
	stp	x19, x20, [sp, 16]
	cset	w22, eq
	mov	w21, w0
	str	x25, [sp, 64]
	mov	w0, 0
	bl	zftl_get_free_sblk
	and	w19, w0, 65535
	mov	w0, 65535
	cmp	w19, w0
	beq	.L2842
	adrp	x0, .LANCHOR9
	ubfiz	x25, x19, 2, 16
	lsl	w22, w22, 1
	mov	w24, w19
	ldr	x20, [x0, #:lo12:.LANCHOR9]
	mov	x23, x0
	add	x20, x20, x25
	ldrb	w1, [x20, 2]
	tst	w1, 224
	beq	.L2843
	adrp	x1, .LANCHOR200
	adrp	x0, .LC0
	mov	w2, 1012
	add	x1, x1, :lo12:.LANCHOR200
	add	x0, x0, :lo12:.LC0
	bl	printf
.L2843:
	ldrb	w0, [x20, 2]
	bfi	w0, w21, 5, 3
	ubfx	x1, x0, 3, 2
	orr	w1, w22, w1
	bfi	w0, w1, 3, 2
	strb	w0, [x20, 2]
	and	w1, w0, 24
	cmp	w1, 24
	bne	.L2844
	cbnz	w22, .L2844
	mov	w1, 1
	bfi	w0, w1, 3, 2
	strb	w0, [x20, 2]
.L2844:
	adrp	x0, .LANCHOR110
	ldr	x0, [x0, #:lo12:.LANCHOR110]
	ldrh	w0, [x0, 150]
	cbz	w0, .L2845
	ldr	x0, [x23, #:lo12:.LANCHOR9]
	ldrh	w0, [x0, x25]
	tst	x0, 2047
	bne	.L2845
	cbnz	w22, .L2845
	mov	w0, w24
	bl	ftl_ink_check_sblk
.L2845:
	mov	w0, w19
	ldr	x25, [sp, 64]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
.L2842:
	bl	print_ftl_debug_info
	adrp	x20, .LC167
	mov	w2, w21
	add	x20, x20, :lo12:.LC167
	mov	w1, w19
	mov	x0, x20
	bl	printf
	mov	w1, w23
	mov	w0, 0
	bl	zftl_get_free_sblk
	and	w19, w0, 65535
	mov	w2, w21
	mov	w1, w19
	mov	x0, x20
	bl	printf
	bl	dump_all_list_info
	mov	w2, 1031
	adrp	x1, .LANCHOR200
	adrp	x0, .LC0
	add	x1, x1, :lo12:.LANCHOR200
	add	x0, x0, :lo12:.LC0
	bl	printf
	b	.L2845
	.size	ftl_alloc_sblk, .-ftl_alloc_sblk
	.section	.text.ftl_open_sblk_init,"ax",@progbits
	.align	2
	.global	ftl_open_sblk_init
	.type	ftl_open_sblk_init, %function
ftl_open_sblk_init:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x21, x22, [sp, 32]
	adrp	x21, .LANCHOR79
	stp	x23, x24, [sp, 48]
	adrp	x22, .LC168
	stp	x19, x20, [sp, 16]
	adrp	x24, .LANCHOR94
	mov	x19, x0
	mov	w23, w1
	add	x24, x24, :lo12:.LANCHOR94
	add	x21, x21, :lo12:.LANCHOR79
	add	x22, x22, :lo12:.LC168
	stp	x25, x26, [sp, 64]
.L2855:
	mov	w25, 65535
.L2856:
	mov	w0, w23
	bl	ftl_alloc_sblk
	and	w20, w0, 65535
	cmp	w20, w25
	beq	.L2856
	mov	w1, 0
	mov	w0, w20
	bl	ftl_erase_sblk
	add	x1, x19, 16
	mov	w0, w20
	bl	ftl_get_blk_list_in_sblk
	and	w0, w0, 255
	ldrh	w1, [x24]
	cmp	w23, 2
	strb	w0, [x19, 9]
	strh	w20, [x19]
	strh	wzr, [x19, 2]
	mul	w0, w1, w0
	strb	wzr, [x19, 5]
	strh	w0, [x19, 6]
	strh	wzr, [x19, 10]
	strb	w23, [x19, 4]
	beq	.L2859
	ldrb	w0, [x21]
	mul	w0, w1, w0
	and	w0, w0, 65535
.L2857:
	ldrb	w2, [x21]
	adrp	x26, .LANCHOR11
	strh	w0, [x19, 12]
	ubfiz	x25, x20, 1, 16
	mul	w2, w2, w1
	adrp	x1, .LANCHOR117
	ldr	x3, [x1, #:lo12:.LANCHOR117]
	mov	w1, 255
	lsl	w2, w2, 2
	add	x0, x3, x0, uxth 2
	bl	ftl_memset
	ldr	x0, [x26, #:lo12:.LANCHOR11]
	ldrh	w1, [x19, 6]
	strh	w1, [x0, x25]
	ldrb	w0, [x19, 9]
	cbnz	w0, .L2854
	mov	w1, w20
	mov	x0, x22
	bl	printf
	ldr	x0, [x26, #:lo12:.LANCHOR11]
	mov	w1, -1
	strh	w1, [x0, x25]
	mov	w0, 7
	strb	w0, [x19, 4]
	b	.L2855
.L2859:
	mov	w0, 0
	b	.L2857
.L2854:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.size	ftl_open_sblk_init, .-ftl_open_sblk_init
	.section	.text.ftl_low_format_data_init,"ax",@progbits
	.align	2
	.global	ftl_low_format_data_init
	.type	ftl_low_format_data_init, %function
ftl_low_format_data_init:
	stp	x29, x30, [sp, -48]!
	adrp	x0, .LANCHOR197
	mov	w2, 16384
	mov	w1, 0
	add	x29, sp, 0
	ldr	x0, [x0, #:lo12:.LANCHOR197]
	stp	x19, x20, [sp, 16]
	adrp	x19, .LANCHOR110
	str	x21, [sp, 32]
	bl	ftl_memset
	bl	zftl_sblk_list_init
	mov	w0, 1
	bl	ftl_alloc_sblk
	mov	w1, 0
	mov	w21, w0
	bl	ftl_erase_sblk
	ldr	x1, [x19, #:lo12:.LANCHOR110]
	mov	w0, w21
	add	x1, x1, 672
	bl	ftl_get_blk_list_in_sblk
	ldr	x0, [x19, #:lo12:.LANCHOR110]
	ldrh	w20, [x0, 672]
	strh	wzr, [x0, 690]
	mov	w0, 65533
	sub	w1, w20, #1
	cmp	w0, w1, uxth
	bcs	.L2863
	adrp	x1, .LANCHOR201
	adrp	x0, .LC0
	mov	w2, 2484
	add	x1, x1, :lo12:.LANCHOR201
	add	x0, x0, :lo12:.LC0
	bl	printf
.L2863:
	ldr	x0, [x19, #:lo12:.LANCHOR110]
	mov	w2, 256
	mov	w1, 255
	add	x0, x0, 416
	strh	wzr, [x0, 280]
	bl	ftl_memset
	ldr	x0, [x19, #:lo12:.LANCHOR110]
	mov	w2, 4096
	mov	w1, 0
	add	x0, x0, 704
	bl	ftl_memset
	adrp	x0, .LANCHOR31
	ldr	x1, [x19, #:lo12:.LANCHOR110]
	ldrb	w2, [x0, #:lo12:.LANCHOR31]
	mov	w0, 24
	sub	w0, w0, w2
	adrp	x2, .LANCHOR74
	strh	w21, [x1, 416]
	adrp	x21, .LANCHOR12
	ldrh	w2, [x2, #:lo12:.LANCHOR74]
	strh	w20, [x1, 692]
	sub	w0, w0, w2
	asr	w0, w20, w0
	strh	w0, [x1, 694]
	mov	w0, 1
	strh	w0, [x1, 688]
	adrp	x0, .LANCHOR202
	ldrh	w0, [x0, #:lo12:.LANCHOR202]
	strh	w0, [x1, 698]
	mov	w1, 20038
	ldr	x0, [x21, #:lo12:.LANCHOR12]
	movk	w1, 0x4549, lsl 16
	str	w1, [x0]
	bl	ftl_alloc_sys_blk
	mov	w20, w0
	mov	w1, 0
	bl	ftl_erase_phy_blk
	ldr	x0, [x19, #:lo12:.LANCHOR110]
	mov	w1, 2
	strh	w20, [x0, 130]
	mov	w20, -1
	strh	wzr, [x0, 140]
	ldr	x0, [x21, #:lo12:.LANCHOR12]
	add	x0, x0, 16
	strh	w20, [x0, 568]
	strh	w20, [x0, 570]
	strh	w20, [x0, 572]
	strh	w20, [x0, 574]
	bl	ftl_open_sblk_init
	ldr	x0, [x21, #:lo12:.LANCHOR12]
	mov	w1, 3
	add	x0, x0, 48
	bl	ftl_open_sblk_init
	ldr	x1, [x19, #:lo12:.LANCHOR110]
	ldr	x0, [x21, #:lo12:.LANCHOR12]
	add	x0, x0, 136
	ldrh	w2, [x1, 134]
	strh	w2, [x0, -10]
	strh	w20, [x0, -56]
	mov	w2, -1
	strh	w20, [x0, -6]
	str	w2, [x0, 408]
	strh	wzr, [x0, -12]
	strh	wzr, [x0, -16]
	strh	wzr, [x0, -14]
	strh	w2, [x1, 126]
	mov	w2, 256
	str	wzr, [x0, 384]
	mov	w1, 255
	str	wzr, [x0, 388]
	str	wzr, [x0, 392]
	bl	ftl_memset
	mov	w2, 128
	mov	w1, 255
	ldr	x0, [x21, #:lo12:.LANCHOR12]
	add	x0, x0, 392
	bl	ftl_memset
	bl	ftl_ext_info_flush
	mov	w0, 0
	bl	ftl_info_flush
	bl	ftl_info_blk_init
	ldr	x21, [sp, 32]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.size	ftl_low_format_data_init, .-ftl_low_format_data_init
	.section	.text.ftl_low_format,"ax",@progbits
	.align	2
	.global	ftl_low_format
	.type	ftl_low_format, %function
ftl_low_format:
	stp	x29, x30, [sp, -80]!
	mov	w1, 0
	adrp	x0, .LC169
	add	x0, x0, :lo12:.LC169
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	adrp	x20, .LANCHOR203
	stp	x21, x22, [sp, 32]
	add	x20, x20, :lo12:.LANCHOR203
	stp	x25, x26, [sp, 64]
	adrp	x22, .LANCHOR6
	mov	x25, x22
	stp	x23, x24, [sp, 48]
	mov	w19, 8
	adrp	x23, .LC0
	bl	printf
.L2868:
	ldr	x0, [x22, #:lo12:.LANCHOR6]
	add	x0, x0, x19, sxtw
	ldrb	w21, [x0, 32]
	add	w0, w21, 127
	and	w0, w0, 255
	cmp	w0, 125
	bhi	.L2866
	mov	w2, 2539
	mov	x1, x20
	add	x0, x23, :lo12:.LC0
	bl	printf
.L2866:
	cmp	w21, 255
	beq	.L2867
	adrp	x0, .LANCHOR111
	ldrh	w1, [x0, #:lo12:.LANCHOR111]
	mov	w0, 0
	mul	w1, w1, w21
	bl	flash_erase_block
.L2867:
	add	w19, w19, 1
	cmp	w19, 16
	bne	.L2868
	bl	sblk_init
	adrp	x22, .LANCHOR9
	bl	ftl_info_blk_init
	adrp	x19, .LANCHOR8
	adrp	x0, .LANCHOR192
	mov	w2, 16384
	mov	w1, 0
	ldr	x0, [x0, #:lo12:.LANCHOR192]
	bl	ftl_memset
	ldr	x0, [x22, #:lo12:.LANCHOR9]
	mov	w3, 1
	ldrh	w2, [x19, #:lo12:.LANCHOR8]
	add	x2, x0, x2, lsl 2
.L2869:
	cmp	x0, x2
	bne	.L2870
	adrp	x21, .LANCHOR110
	mov	w1, 21574
	adrp	x24, .LANCHOR68
	add	x24, x24, :lo12:.LANCHOR68
	ldr	x0, [x21, #:lo12:.LANCHOR110]
	movk	w1, 0x494c, lsl 16
	mov	w20, 0
	mov	w26, 1
	strh	wzr, [x0, 148]
	str	w1, [x0]
.L2871:
	ldrh	w0, [x19, #:lo12:.LANCHOR8]
	adrp	x23, .LANCHOR75
	cmp	w0, w20
	bhi	.L2880
	ldr	x0, [x25, #:lo12:.LANCHOR6]
	mov	w4, 3
	ldrb	w2, [x23, #:lo12:.LANCHOR75]
	mov	w10, 15
	ldr	x6, [x21, #:lo12:.LANCHOR110]
	cmp	w2, 1
	ldr	x1, [x22, #:lo12:.LANCHOR9]
	ldrb	w0, [x0, 47]
	csinc	w4, w4, wzr, ne
	and	w4, w4, 255
	and	w8, w2, 65535
	ldrh	w3, [x6, 148]
	udiv	w0, w0, w2
	and	w5, w0, 65535
	ubfiz	x0, x0, 2, 8
	add	x0, x0, 4
	add	w20, w5, 1
	add	x0, x1, x0
.L2883:
	cmp	w2, 4
	add	x1, x1, 4
	csel	w7, w10, w4, eq
	strb	w7, [x1, -1]
	ldrb	w7, [x1, -2]
	orr	w7, w7, -32
	strb	w7, [x1, -2]
	cmp	x1, x0
	bne	.L2883
	mul	w5, w5, w8
	mov	w4, 16
	add	w0, w8, w3
	sdiv	w4, w4, w2
	add	w0, w5, w0, uxth
	strh	w0, [x6, 148]
	adrp	x0, .LANCHOR19
	ldr	w0, [x0, #:lo12:.LANCHOR19]
	add	w4, w20, w4
	and	w4, w4, 65535
	strh	w4, [x6, 134]
	tbz	x0, 12, .L2884
	adrp	x0, .LC170
	mov	w3, w20
	mov	w2, 128
	mov	w1, 2598
	add	x0, x0, :lo12:.LC170
	bl	printf
.L2884:
	ldr	x0, [x21, #:lo12:.LANCHOR110]
	mov	w2, 128
	mov	w1, 255
	add	x0, x0, 160
	bl	ftl_memset
	adrp	x0, .LANCHOR112
	ldrb	w10, [x23, #:lo12:.LANCHOR75]
	adrp	x3, .LANCHOR74
	ldr	x2, [x21, #:lo12:.LANCHOR110]
	ldrb	w16, [x0, #:lo12:.LANCHOR112]
	adrp	x0, .LANCHOR31
	and	w11, w10, 65535
	ldr	x15, [x22, #:lo12:.LANCHOR9]
	ldrb	w4, [x0, #:lo12:.LANCHOR31]
	mov	w0, 24
	ldrh	w8, [x2, 134]
	sub	w0, w0, w4
	ldrh	w4, [x3, #:lo12:.LANCHOR74]
	mul	w1, w20, w11
	mov	w3, 0
	sub	w0, w0, w4
	mov	w4, 1
	and	w1, w1, 65535
	lsl	w4, w4, w0
	and	w4, w4, 65535
.L2885:
	cmp	w20, w8
	bcc	.L2891
	ldrh	w0, [x19, #:lo12:.LANCHOR8]
	strh	w3, [x2, 112]
	sub	w0, w0, w8
	strh	wzr, [x2, 114]
	strh	w0, [x2, 116]
	strh	wzr, [x2, 118]
	strh	w8, [x2, 132]
	bl	ftl_low_format_data_init
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
.L2870:
	ldrb	w1, [x0, 2]
	add	x0, x0, 4
	and	w1, w1, 31
	bfi	w1, w3, 3, 2
	strb	w1, [x0, -2]
	b	.L2869
.L2880:
	adrp	x0, .LANCHOR81
	strh	w20, [x24]
	ldrb	w0, [x0, #:lo12:.LANCHOR81]
	cbnz	w0, .L2872
	mov	w0, w20
	bl	ftl_test_block
.L2872:
	ldrb	w11, [x23, #:lo12:.LANCHOR75]
	adrp	x0, .LANCHOR112
	ldr	x6, [x22, #:lo12:.LANCHOR9]
	mov	w7, 0
	ldrb	w14, [x0, #:lo12:.LANCHOR112]
	mov	w10, 0
	ldr	x13, [x21, #:lo12:.LANCHOR110]
	mov	w8, 0
	mul	w12, w20, w11
	add	x6, x6, x20, uxth 2
.L2873:
	cmp	w8, w14
	bcs	.L2877
	add	w15, w11, w7
	b	.L2878
.L2876:
	add	w1, w7, w12
	mov	w0, w8
	bl	flash_check_bad_block
	cbz	w0, .L2874
	ldrb	w1, [x6, 3]
	lsl	w0, w26, w7
	orr	w0, w0, w1
	strb	w0, [x6, 3]
	ldrh	w0, [x13, 148]
	add	w0, w0, 1
	strh	w0, [x13, 148]
.L2875:
	add	w7, w7, 1
.L2878:
	cmp	w7, w15
	bne	.L2876
	add	w8, w8, 1
	sub	w12, w12, w11
	and	w8, w8, 65535
	b	.L2873
.L2874:
	add	w10, w10, 1
	and	w10, w10, 65535
	b	.L2875
.L2877:
	cbnz	w10, .L2879
	ldrb	w0, [x6, 2]
	orr	w0, w0, -32
	strb	w0, [x6, 2]
.L2879:
	add	w20, w20, 1
	and	w20, w20, 65535
	b	.L2871
.L2891:
	add	x13, x15, x20, uxth 2
	mov	w6, 0
	mov	w12, 0
	mov	w5, 0
	ldrb	w0, [x13, 2]
	orr	w0, w0, -32
	strb	w0, [x13, 2]
.L2886:
	cmp	w5, w16
	bcc	.L2893
	add	w20, w20, 1
	add	w1, w1, w11
	and	w20, w20, 65535
	and	w1, w1, 65535
	b	.L2885
.L2889:
	ldrb	w14, [x13, 3]
	add	w17, w12, w7
	asr	w14, w14, w17
	tbnz	x14, 0, .L2887
	cmp	w10, 1
	bls	.L2892
	and	w0, w0, 1
	add	w0, w1, w0
	and	w0, w0, 65535
.L2888:
	add	x14, x2, x3, sxtw 1
	add	w3, w3, 1
	and	w3, w3, 65535
	add	w0, w0, w6
	strh	w0, [x14, 160]
.L2887:
	add	x7, x7, 1
.L2890:
	and	w0, w7, 65535
	cmp	w0, w11
	bcc	.L2889
	add	w5, w5, 1
	add	w6, w4, w6
	and	w5, w5, 65535
	add	w12, w12, w10
	and	w6, w6, 65535
	b	.L2886
.L2892:
	mov	w0, w1
	b	.L2888
.L2893:
	mov	x7, 0
	b	.L2890
	.size	ftl_low_format, .-ftl_low_format
	.section	.text.ftl_re_low_format,"ax",@progbits
	.align	2
	.global	ftl_re_low_format
	.type	ftl_re_low_format, %function
ftl_re_low_format:
	stp	x29, x30, [sp, -16]!
	mov	w1, 1
	adrp	x0, .LC171
	add	x0, x0, :lo12:.LC171
	add	x29, sp, 0
	bl	printf
	bl	sblk_init
	bl	ftl_info_blk_init
	bl	ftl_ext_info_init
	adrp	x0, .LANCHOR110
	adrp	x2, .LANCHOR8
	mov	w3, 0
	mov	w4, 0
	ldr	x0, [x0, #:lo12:.LANCHOR110]
	mov	w5, 0
	ldrh	w7, [x2, #:lo12:.LANCHOR8]
	adrp	x2, .LANCHOR9
	ldr	x2, [x2, #:lo12:.LANCHOR9]
	ldrh	w1, [x0, 134]
	add	x2, x2, x1, uxth 2
.L2904:
	cmp	w1, w7
	bcc	.L2908
	strh	w5, [x0, 114]
	strh	w4, [x0, 118]
	strh	w3, [x0, 116]
	strh	wzr, [x0, 122]
	strh	wzr, [x0, 120]
	strh	wzr, [x0, 124]
	bl	ftl_low_format_data_init
	mov	w0, 0
	ldp	x29, x30, [sp], 16
	ret
.L2908:
	ldrb	w6, [x2, 2]
	and	w8, w6, 31
	strb	w8, [x2, 2]
	ands	w6, w6, 24
	bne	.L2905
	add	w5, w5, 1
	and	w5, w5, 65535
.L2906:
	add	w1, w1, 1
	add	x2, x2, 4
	and	w1, w1, 65535
	b	.L2904
.L2905:
	cmp	w6, 16
	bne	.L2907
	add	w4, w4, 1
	and	w4, w4, 65535
	b	.L2906
.L2907:
	add	w3, w3, 1
	and	w3, w3, 65535
	b	.L2906
	.size	ftl_re_low_format, .-ftl_re_low_format
	.section	.text.pm_alloc_new_blk,"ax",@progbits
	.align	2
	.global	pm_alloc_new_blk
	.type	pm_alloc_new_blk, %function
pm_alloc_new_blk:
	stp	x29, x30, [sp, -64]!
	adrp	x2, .LANCHOR79
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	adrp	x20, .LANCHOR110
	stp	x21, x22, [sp, 32]
	ldr	x1, [x20, #:lo12:.LANCHOR110]
	ldrb	w2, [x2, #:lo12:.LANCHOR79]
	ldrh	w0, [x1, 690]
	str	x23, [sp, 48]
	add	w0, w0, 1
	and	w0, w0, 65535
	strh	w0, [x1, 690]
	cmp	w2, w0
	bls	.L2911
	add	x0, x1, x0, sxtw 1
	ldrh	w1, [x0, 672]
	mov	w0, 65535
	cmp	w1, w0
	bne	.L2912
.L2911:
	adrp	x19, .LC168
	add	x19, x19, :lo12:.LC168
	mov	w23, 65535
	adrp	x22, .LANCHOR9
.L2913:
	mov	w0, 1
	bl	ftl_alloc_sblk
	and	w21, w0, 65535
	cmp	w21, w23
	beq	.L2913
	mov	w1, 0
	mov	w0, w21
	bl	ftl_erase_sblk
	add	x14, x20, :lo12:.LANCHOR110
	ldr	x1, [x20, #:lo12:.LANCHOR110]
	mov	w0, w21
	add	x1, x1, 672
	bl	ftl_get_blk_list_in_sblk
	tst	w0, 65535
	bne	.L2914
	mov	w1, w21
	mov	x0, x19
	bl	printf
	ldr	x0, [x22, #:lo12:.LANCHOR9]
	add	x21, x0, x21, uxth 2
	ldrb	w0, [x21, 2]
	orr	w0, w0, -32
	strb	w0, [x21, 2]
	b	.L2913
.L2914:
	ldr	x0, [x14]
	adrp	x1, .LANCHOR204
	mov	w2, 1
	mov	w19, 0
	add	x0, x0, 416
	str	w2, [x1, #:lo12:.LANCHOR204]
	mov	w1, 65535
	strh	wzr, [x0, 274]
.L2916:
	ldrh	w2, [x0]
	cmp	w2, w1
	beq	.L2915
	add	w19, w19, 1
	add	x0, x0, 2
	and	w19, w19, 65535
	cmp	w19, 128
	bne	.L2916
	adrp	x1, .LANCHOR205
	adrp	x0, .LC0
	mov	w2, 264
	add	x1, x1, :lo12:.LANCHOR205
	add	x0, x0, :lo12:.LC0
	bl	printf
.L2915:
	ldr	x0, [x20, #:lo12:.LANCHOR110]
	add	x19, x0, x19, sxtw 1
	ldrh	w1, [x0, 688]
	strh	w21, [x19, 416]
	add	w1, w1, 1
	strh	w1, [x0, 688]
.L2912:
	ldr	x1, [x20, #:lo12:.LANCHOR110]
	ldrh	w0, [x1, 690]
	add	x0, x0, 336
	ldrh	w19, [x1, x0, lsl 1]
	mov	w0, 65533
	sub	w1, w19, #1
	cmp	w0, w1, uxth
	bcs	.L2918
	adrp	x1, .LANCHOR205
	adrp	x0, .LC0
	mov	w2, 270
	add	x1, x1, :lo12:.LANCHOR205
	add	x0, x0, :lo12:.LC0
	bl	printf
.L2918:
	adrp	x1, .LANCHOR31
	mov	w2, 24
	ldr	x0, [x20, #:lo12:.LANCHOR110]
	ldrb	w1, [x1, #:lo12:.LANCHOR31]
	sub	w2, w2, w1
	adrp	x1, .LANCHOR74
	strh	wzr, [x0, 696]
	ldrh	w1, [x1, #:lo12:.LANCHOR74]
	strh	w19, [x0, 692]
	sub	w2, w2, w1
	asr	w4, w19, w2
	strh	w4, [x0, 694]
	adrp	x0, .LANCHOR19
	ldr	w0, [x0, #:lo12:.LANCHOR19]
	tbz	x0, 12, .L2921
	mov	w0, 1
	and	w4, w4, 65535
	lsl	w2, w0, w2
	mov	w3, w19
	adrp	x0, .LC172
	sub	w2, w2, #1
	mov	w1, w19
	add	x0, x0, :lo12:.LC172
	bl	printf
.L2921:
	mov	w0, 0
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.size	pm_alloc_new_blk, .-pm_alloc_new_blk
	.section	.text.pm_write_page,"ax",@progbits
	.align	2
	.global	pm_write_page
	.type	pm_write_page, %function
pm_write_page:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w19, w0
	stp	x21, x22, [sp, 32]
	adrp	x21, .LANCHOR94
	stp	x23, x24, [sp, 48]
	adrp	x22, .LANCHOR111
	adrp	x24, .LANCHOR110
	mov	x23, x1
	add	x21, x21, :lo12:.LANCHOR94
	mov	x20, x24
	add	x22, x22, :lo12:.LANCHOR111
	stp	x25, x26, [sp, 64]
	str	x27, [sp, 80]
	mov	w25, 65535
.L2929:
	ldr	x0, [x24, #:lo12:.LANCHOR110]
	ldr	w1, [x0, 48]
	ldrh	w2, [x0, 696]
	add	w1, w1, 1
	str	w1, [x0, 48]
	ldrh	w1, [x21]
	cmp	w2, w1
	bcs	.L2930
	ldrh	w0, [x0, 692]
	cmp	w0, w25
	bne	.L2931
.L2930:
	bl	pm_alloc_new_blk
	mov	w0, 0
	bl	ftl_info_flush
.L2931:
	ldr	x0, [x20, #:lo12:.LANCHOR110]
	ldrh	w0, [x0, 692]
	cmp	w0, w25
	bne	.L2932
	adrp	x1, .LANCHOR206
	adrp	x0, .LC0
	mov	w2, 303
	add	x1, x1, :lo12:.LANCHOR206
	add	x0, x0, :lo12:.LC0
	bl	printf
.L2932:
	ldr	x0, [x20, #:lo12:.LANCHOR110]
	adrp	x27, .LANCHOR207
	ldrh	w1, [x22]
	mov	w2, 64
	ldrh	w26, [x0, 692]
	ldrh	w0, [x0, 696]
	madd	w26, w26, w1, w0
	ldr	x0, [x27, #:lo12:.LANCHOR207]
	mov	w1, 0
	bl	ftl_memset
	ldr	x6, [x27, #:lo12:.LANCHOR207]
	ldr	x7, [x20, #:lo12:.LANCHOR110]
	str	w19, [x6]
	ldr	w0, [x7, 48]
	str	w0, [x6, 4]
	adrp	x0, .LANCHOR131
	ldrb	w8, [x0, #:lo12:.LANCHOR131]
	mov	x0, x23
	lsl	w1, w8, 9
	bl	js_hash
	str	w0, [x6, 8]
	ldrb	w0, [x7, 694]
	mov	x2, x23
	mov	w1, w26
	mov	w4, w8
	mov	x3, x6
	bl	ftl_prog_page
	ldr	x2, [x20, #:lo12:.LANCHOR110]
	ldrh	w1, [x2, 696]
	add	w1, w1, 1
	and	w1, w1, 65535
	strh	w1, [x2, 696]
	cmp	w1, 1
	adrp	x1, .LANCHOR208
	beq	.L2933
	ldrb	w3, [x1, #:lo12:.LANCHOR208]
	cbz	w3, .L2934
.L2933:
	strb	wzr, [x1, #:lo12:.LANCHOR208]
	b	.L2929
.L2934:
	cmn	w0, #1
	bne	.L2936
	mov	w1, w26
	adrp	x0, .LC173
	add	x0, x0, :lo12:.LC173
	bl	printf
	b	.L2929
.L2936:
	ldrh	w0, [x2, 698]
	cmp	w19, w0
	bcs	.L2937
	add	x19, x2, x19, uxtw 2
	str	w26, [x19, 704]
.L2937:
	mov	w0, 0
	ldr	x27, [sp, 80]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 96
	ret
	.size	pm_write_page, .-pm_write_page
	.section	.text.flash_info_flush,"ax",@progbits
	.align	2
	.global	flash_info_flush
	.type	flash_info_flush, %function
flash_info_flush:
	stp	x29, x30, [sp, -112]!
	adrp	x0, .LANCHOR19
	add	x29, sp, 0
	ldr	w0, [x0, #:lo12:.LANCHOR19]
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	tbz	x0, 12, .L2943
	adrp	x2, .LANCHOR209
	adrp	x0, .LC94
	add	x2, x2, :lo12:.LANCHOR209
	mov	w1, 365
	add	x0, x0, :lo12:.LC94
	bl	printf
.L2943:
	adrp	x23, .LANCHOR210
	adrp	x20, .LANCHOR6
	mov	w2, 64
	mov	w1, 0
	ldr	x0, [x23, #:lo12:.LANCHOR210]
	adrp	x21, .LANCHOR211
	adrp	x22, .LANCHOR2
	adrp	x24, .LC175
	adrp	x25, .LANCHOR144
	add	x22, x22, :lo12:.LANCHOR2
	add	x24, x24, :lo12:.LC175
	add	x25, x25, :lo12:.LANCHOR144
	bl	ftl_memset
	add	x27, x21, :lo12:.LANCHOR211
	ldr	x1, [x20, #:lo12:.LANCHOR6]
	mov	w3, 16
	mov	w2, 4
	adrp	x0, .LC174
	add	x0, x0, :lo12:.LC174
	mov	w26, 0
	bl	rknand_print_hex
	ldr	x6, [x20, #:lo12:.LANCHOR6]
	add	x0, x6, 16
	ldr	w1, [x6, 8]
	bl	js_hash
	str	w0, [x6, 12]
.L2944:
	add	x28, x21, :lo12:.LANCHOR211
	ldrb	w4, [x21, #:lo12:.LANCHOR211]
	ldrh	w19, [x22]
	mov	x0, x24
	mov	w1, w4
	ldrh	w3, [x28, 2]
	stp	w3, w4, [x29, 104]
	mov	w2, w3
	bl	printf
	ldrh	w0, [x25]
	ldrh	w1, [x28, 2]
	sub	w0, w0, #1
	cmp	w1, w0
	ldp	w3, w4, [x29, 104]
	blt	.L2945
	ldr	x6, [x20, #:lo12:.LANCHOR6]
	ldrb	w7, [x28, 1]
	strh	wzr, [x28, 2]
	ldr	w0, [x6, 4]
	ldrh	w1, [x6, 16]
	add	w0, w0, 1
	str	w0, [x6, 4]
	ldrb	w0, [x21, #:lo12:.LANCHOR211]
	add	w1, w1, 1
	strb	w0, [x28, 1]
	mov	x0, x6
	strb	w7, [x21, #:lo12:.LANCHOR211]
	strh	w1, [x0, 16]!
	ldr	w1, [x6, 8]
	bl	js_hash
	ldrh	w19, [x22]
	str	w0, [x6, 12]
	mul	w19, w19, w7
.L2954:
	mov	w1, w19
	mov	w0, 0
	bl	flash_erase_block
	b	.L2946
.L2949:
	mov	w26, 1
	b	.L2944
.L2945:
	madd	w19, w19, w4, w3
	cbz	w1, .L2954
.L2946:
	ldr	x2, [x20, #:lo12:.LANCHOR6]
	mov	w1, w19
	ldr	x3, [x23, #:lo12:.LANCHOR210]
	mov	w5, 1
	mov	w4, 4
	ldr	w0, [x2, 4]
	str	w0, [x3]
	mov	w0, 21321
	movk	w0, 0x5359, lsl 16
	str	w0, [x3, 4]
	mov	w0, 0
	bl	flash_prog_page_en
	cmn	w0, #1
	ldrh	w1, [x27, 2]
	add	w1, w1, 1
	strh	w1, [x27, 2]
	bne	.L2947
	mov	w1, w19
	adrp	x0, .LC176
	add	x0, x0, :lo12:.LC176
	bl	printf
	b	.L2944
.L2947:
	cbz	w26, .L2949
	ldp	x19, x20, [sp, 16]
	mov	w0, 0
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
	.size	flash_info_flush, .-flash_info_flush
	.section	.text.flash_info_blk_init,"ax",@progbits
	.align	2
	.global	flash_info_blk_init
	.type	flash_info_blk_init, %function
flash_info_blk_init:
	stp	x29, x30, [sp, -96]!
	adrp	x0, .LANCHOR19
	add	x29, sp, 0
	ldr	w0, [x0, #:lo12:.LANCHOR19]
	stp	x19, x20, [sp, 16]
	adrp	x20, .LANCHOR6
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	str	x27, [sp, 80]
	tbz	x0, 12, .L2956
	ldr	x4, [x20, #:lo12:.LANCHOR6]
	adrp	x2, .LANCHOR212
	adrp	x0, .LC177
	mov	w3, 2048
	add	x2, x2, :lo12:.LANCHOR212
	mov	w1, 50
	add	x0, x0, :lo12:.LC177
	bl	printf
.L2956:
	adrp	x24, .LANCHOR2
	mov	w23, 21321
	add	x26, x24, :lo12:.LANCHOR2
	mov	w22, 4
	adrp	x21, .LANCHOR210
	movk	w23, 0x5359, lsl 16
.L2960:
	mov	w19, 0
.L2959:
	ldrh	w1, [x26]
	mov	w4, 4
	ldr	x3, [x21, #:lo12:.LANCHOR210]
	mov	w0, 0
	ldr	x2, [x20, #:lo12:.LANCHOR6]
	add	x27, x21, :lo12:.LANCHOR210
	add	x25, x20, :lo12:.LANCHOR6
	madd	w1, w1, w22, w19
	bl	flash_read_page_en
	cmn	w0, #1
	beq	.L2957
	ldr	x2, [x20, #:lo12:.LANCHOR6]
	ldr	w0, [x2]
	cmp	w0, w23
	beq	.L2958
.L2957:
	add	w19, w19, 1
	cmp	w19, 4
	bne	.L2959
	add	w22, w22, 1
	cmp	w22, 16
	bne	.L2960
.L2986:
	mov	w0, -1
.L2955:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldr	x27, [sp, 80]
	ldp	x29, x30, [sp], 96
	ret
.L2968:
	ldr	x0, [x25]
	ldr	w1, [x0]
	cmp	w1, w23
	bne	.L2969
	ldr	w22, [x0, 4]
.L2962:
	add	x23, x19, :lo12:.LANCHOR211
	ldrh	w0, [x24, #:lo12:.LANCHOR2]
	ldr	x3, [x21, #:lo12:.LANCHOR210]
	mov	w4, 4
	ldr	x2, [x20, #:lo12:.LANCHOR6]
	ldrb	w1, [x23, 1]
	mul	w1, w1, w0
	mov	w0, 0
	bl	flash_read_page_en
	cmn	w0, #1
	beq	.L2963
	ldr	x0, [x20, #:lo12:.LANCHOR6]
	mov	w1, 21321
	movk	w1, 0x5359, lsl 16
	ldr	w2, [x0]
	cmp	w2, w1
	bne	.L2963
	ldr	w1, [x0, 4]
	cmp	w22, w1
	bcs	.L2963
	ldrb	w1, [x0, 37]
	ldrb	w0, [x0, 36]
	strb	w1, [x19, #:lo12:.LANCHOR211]
	strb	w0, [x23, 1]
.L2963:
	ldrb	w1, [x19, #:lo12:.LANCHOR211]
	add	x22, x19, :lo12:.LANCHOR211
	ldr	x3, [x21, #:lo12:.LANCHOR210]
	mov	w4, 4
	ldr	x2, [x20, #:lo12:.LANCHOR6]
	mov	w0, 0
	bl	flash_get_last_written_page
	and	w25, w0, 65535
	add	w1, w25, 1
	ldrb	w23, [x19, #:lo12:.LANCHOR211]
	strh	w1, [x22, 2]
	mov	w22, 0
	ldrh	w1, [x24, #:lo12:.LANCHOR2]
	mov	w24, 21321
	movk	w24, 0x5359, lsl 16
	mul	w23, w23, w1
	add	w23, w23, w0, sxth
.L2964:
	sub	w0, w25, w22
	sxth	w19, w0
	tbz	w19, #31, .L2967
	cmn	w19, #1
	bne	.L2966
	ldr	x0, [x20, #:lo12:.LANCHOR6]
	ldr	w1, [x0]
	adrp	x0, .LC178
	add	x0, x0, :lo12:.LC178
	bl	printf
	b	.L2986
.L2967:
	ldr	x3, [x21, #:lo12:.LANCHOR210]
	mov	w4, 4
	ldr	x2, [x20, #:lo12:.LANCHOR6]
	sub	w1, w23, w22
	mov	w0, 0
	bl	flash_read_page_en
	cmn	w0, #1
	beq	.L2965
	ldr	x0, [x20, #:lo12:.LANCHOR6]
	ldr	w0, [x0]
	cmp	w0, w24
	beq	.L2966
.L2965:
	add	w22, w22, 1
	b	.L2964
.L2966:
	cmp	w22, 1
	bls	.L2970
	bl	flash_info_flush
.L2970:
	mov	w0, 0
	b	.L2955
.L2958:
	adrp	x19, .LANCHOR211
	add	x1, x19, :lo12:.LANCHOR211
	ldrb	w3, [x2, 37]
	mov	w4, 4
	ldrb	w0, [x2, 36]
	strb	w3, [x1, 1]
	ldrh	w1, [x26]
	ldr	x3, [x27]
	strb	w0, [x19, #:lo12:.LANCHOR211]
	mul	w1, w1, w0
	mov	w0, 0
	bl	flash_read_page_en
	cmn	w0, #1
	bne	.L2968
.L2969:
	mov	w22, 0
	b	.L2962
	.size	flash_info_blk_init, .-flash_info_blk_init
	.section	.text.nand_flash_init,"ax",@progbits
	.align	2
	.global	nand_flash_init
	.type	nand_flash_init, %function
nand_flash_init:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x21, x22, [sp, 32]
	adrp	x21, .LANCHOR19
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	ldr	w0, [x21, #:lo12:.LANCHOR19]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	str	x27, [sp, 80]
	tbz	x0, 12, .L2988
	adrp	x2, .LANCHOR213
	adrp	x0, .LC94
	add	x2, x2, :lo12:.LANCHOR213
	mov	w1, 3451
	add	x0, x0, :lo12:.LC94
	bl	printf
.L2988:
	adrp	x0, .LANCHOR169
	adrp	x24, .LANCHOR21
	adrp	x22, .LANCHOR47
	add	x25, x22, :lo12:.LANCHOR47
	str	wzr, [x0, #:lo12:.LANCHOR169]
	mov	x0, x19
	bl	nandc_init
	adrp	x19, .LANCHOR32
	add	x0, x19, :lo12:.LANCHOR32
	str	x0, [x24, #:lo12:.LANCHOR21]
	adrp	x0, .LANCHOR23
	adrp	x23, .LANCHOR31
	mov	x26, x25
	mov	w1, 1
	mov	w20, 0
	strb	w1, [x0, #:lo12:.LANCHOR23]
	mov	w27, 44
	mov	w0, 3
	mov	w2, 8
	strb	w0, [x23, #:lo12:.LANCHOR31]
	mov	w1, 0
	adrp	x0, .LANCHOR29
	add	x0, x0, :lo12:.LANCHOR29
	bl	ftl_memset
	mov	w2, 32
	mov	w1, 0
	adrp	x0, .LANCHOR145
	add	x0, x0, :lo12:.LANCHOR145
	bl	ftl_memset
.L2994:
	mov	x1, x25
	mov	w0, w20
	bl	flash_read_id
	cbnz	w20, .L2989
	ldrb	w0, [x26]
	sub	w0, w0, #1
	and	w0, w0, 255
	cmp	w0, 253
	bls	.L2990
.L2992:
	mov	w22, -2
.L2987:
	mov	w0, w22
	ldr	x27, [sp, 80]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 96
	ret
.L2990:
	ldrb	w0, [x26, 1]
	cmp	w0, 255
	beq	.L2992
.L2989:
	ldrb	w0, [x25]
	cmp	w0, 181
	bne	.L2993
	strb	w27, [x25]
.L2993:
	add	w20, w20, 1
	add	x25, x25, 8
	and	w20, w20, 255
	cmp	w20, 4
	bne	.L2994
	adrp	x0, .LANCHOR214
	add	x8, x0, :lo12:.LANCHOR214
	add	x8, x8, 1
	mov	x7, x0
	add	x12, x22, :lo12:.LANCHOR47
	mov	x10, 0
.L2997:
	ldrb	w2, [x8, -1]
	mov	w11, w10
	lsl	x25, x10, 5
	mov	x1, x12
	mov	x0, x8
	bl	flash_mem_cmp8
	cbnz	w0, .L2995
	add	x0, x7, :lo12:.LANCHOR214
	ubfiz	x11, x11, 5, 32
	add	x25, x0, x25
	add	x0, x0, x11
	adrp	x1, .LANCHOR215
	add	x4, x1, :lo12:.LANCHOR215
	ldrb	w3, [x0, 22]
	mov	x0, 0
.L2996:
	lsl	x5, x0, 5
	mov	w2, w0
	ldrb	w5, [x5, x4]
	cmp	w5, w3
	beq	.L2998
	add	x0, x0, 1
	cmp	x0, 4
	bne	.L2996
	mov	w2, w0
.L2998:
	ubfiz	x0, x2, 5, 32
	add	x1, x1, :lo12:.LANCHOR215
	add	x1, x1, x0
	mov	w2, 32
	adrp	x0, .LANCHOR25
	add	x20, x19, :lo12:.LANCHOR32
	add	x0, x0, :lo12:.LANCHOR25
	adrp	x26, .LANCHOR27
	bl	ftl_memcpy
	mov	w2, 32
	mov	x1, x25
	mov	x0, x20
	bl	ftl_memcpy
	ldrb	w0, [x26, #:lo12:.LANCHOR27]
	cmp	w0, 8
	bhi	.L2999
	ldrb	w0, [x20, 20]
	cmp	w0, 60
	bls	.L2999
	mov	w0, 60
	strb	w0, [x20, 20]
.L2999:
	ldr	w0, [x21, #:lo12:.LANCHOR19]
	tbz	x0, 12, .L3029
	adrp	x2, .LANCHOR213
	adrp	x0, .LC94
	add	x2, x2, :lo12:.LANCHOR213
	mov	w1, 3478
	add	x0, x0, :lo12:.LC94
	bl	printf
.L3029:
	ldr	x0, [x24, #:lo12:.LANCHOR21]
	ldrh	w0, [x0, 10]
	cmp	w0, 1023
	bls	.L3000
	mov	w0, 2
	strb	w0, [x23, #:lo12:.LANCHOR31]
.L3000:
	mov	w0, 16384
	bl	ftl_malloc
	adrp	x1, .LANCHOR173
	adrp	x23, .LANCHOR6
	add	x20, x19, :lo12:.LANCHOR32
	adrp	x25, .LANCHOR48
	str	x0, [x1, #:lo12:.LANCHOR173]
	mov	w0, 16384
	bl	ftl_malloc
	adrp	x1, .LANCHOR163
	str	x0, [x1, #:lo12:.LANCHOR163]
	mov	w0, 2048
	bl	ftl_malloc
	str	x0, [x23, #:lo12:.LANCHOR6]
	mov	w0, 64
	bl	ftl_malloc
	adrp	x1, .LANCHOR172
	str	x0, [x1, #:lo12:.LANCHOR172]
	mov	w0, 64
	bl	ftl_malloc
	adrp	x1, .LANCHOR165
	str	x0, [x1, #:lo12:.LANCHOR165]
	mov	w0, 64
	bl	ftl_malloc
	adrp	x1, .LANCHOR210
	str	x0, [x1, #:lo12:.LANCHOR210]
	adrp	x0, .LANCHOR216
	strb	wzr, [x0, #:lo12:.LANCHOR216]
	bl	flash_die_info_init
	ldrb	w0, [x20, 18]
	bl	flash_lsb_page_tbl_build
	ldrb	w0, [x20, 20]
	adrp	x20, .LANCHOR171
	bl	nandc_bch_sel
	str	xzr, [x20, #:lo12:.LANCHOR171]
	ldr	x2, [x24, #:lo12:.LANCHOR21]
	ldrh	w0, [x2, 16]
	ubfx	x1, x0, 8, 3
	strb	w1, [x25, #:lo12:.LANCHOR48]
	adrp	x1, .LANCHOR183
	ubfx	x3, x0, 3, 1
	strb	w3, [x1, #:lo12:.LANCHOR183]
	adrp	x1, .LANCHOR44
	ubfx	x3, x0, 4, 1
	strb	w3, [x1, #:lo12:.LANCHOR44]
	adrp	x1, .LANCHOR83
	ubfx	x3, x0, 12, 1
	strb	w3, [x1, #:lo12:.LANCHOR83]
	adrp	x1, .LANCHOR80
	ubfx	x3, x0, 13, 1
	strb	w3, [x1, #:lo12:.LANCHOR80]
	adrp	x1, .LANCHOR35
	ubfx	x3, x0, 11, 1
	strb	w3, [x1, #:lo12:.LANCHOR35]
	adrp	x3, .LANCHOR124
	ldrb	w1, [x2, 31]
	ldrb	w2, [x2, 28]
	ubfx	x4, x1, 1, 1
	strb	w4, [x3, #:lo12:.LANCHOR124]
	adrp	x3, .LANCHOR217
	ubfx	x4, x1, 2, 1
	strb	w4, [x3, #:lo12:.LANCHOR217]
	adrp	x3, .LANCHOR1
	ubfx	x4, x0, 14, 1
	lsr	w0, w0, 15
	strb	w4, [x3, #:lo12:.LANCHOR1]
	adrp	x3, .LANCHOR81
	strb	w0, [x3, #:lo12:.LANCHOR81]
	adrp	x0, .LANCHOR0
	ubfx	x3, x1, 3, 1
	ubfx	x1, x1, 4, 1
	strb	w2, [x0, #:lo12:.LANCHOR0]
	adrp	x0, .LANCHOR30
	strb	w3, [x0, #:lo12:.LANCHOR30]
	adrp	x0, .LANCHOR36
	strb	w1, [x0, #:lo12:.LANCHOR36]
	adrp	x1, .LANCHOR22
	mov	w0, 60
	strb	w0, [x1, #:lo12:.LANCHOR22]
	ldrb	w0, [x26, #:lo12:.LANCHOR27]
	cmp	w0, 9
	bne	.L3001
	mov	w3, 70
	strb	w3, [x1, #:lo12:.LANCHOR22]
.L3001:
	add	x1, x19, :lo12:.LANCHOR32
	adrp	x24, .LANCHOR24
	strb	w2, [x24, #:lo12:.LANCHOR24]
	ldrb	w2, [x1, 31]
	tbz	x2, 0, .L3002
	ldrb	w1, [x1, 29]
	cbz	w1, .L3003
	mov	w1, 2
.L3061:
	strb	w1, [x24, #:lo12:.LANCHOR24]
.L3002:
	cmp	w0, 8
	bne	.L3004
	ldrb	w0, [x22, #:lo12:.LANCHOR47]
	mov	w1, 137
	cmp	w0, 44
	ccmp	w0, w1, 4, ne
	bne	.L3004
	add	x0, x19, :lo12:.LANCHOR32
	ldrb	w0, [x0, 28]
	cmp	w0, 3
	bne	.L3004
	strb	wzr, [x24, #:lo12:.LANCHOR24]
.L3004:
	add	x1, x19, :lo12:.LANCHOR32
	adrp	x27, .LANCHOR16
	ldrb	w0, [x1, 19]
	ldrh	w1, [x1, 16]
	strb	w0, [x27, #:lo12:.LANCHOR16]
	tbz	x1, 6, .L3006
	sub	w1, w0, #17
	and	w1, w1, 255
	cmp	w1, 2
	ccmp	w0, 21, 4, hi
	bne	.L3007
	adrp	x1, micron_read_retrial
	add	x1, x1, :lo12:micron_read_retrial
	str	x1, [x20, #:lo12:.LANCHOR171]
	cmp	w0, 21
	adrp	x0, .LANCHOR166
	beq	.L3008
	mov	w1, 15
.L3063:
	strb	w1, [x0, #:lo12:.LANCHOR166]
.L3006:
	ldr	w0, [x21, #:lo12:.LANCHOR19]
	tbz	x0, 12, .L3017
	adrp	x2, .LANCHOR213
	adrp	x0, .LC94
	add	x2, x2, :lo12:.LANCHOR213
	mov	w1, 3571
	add	x0, x0, :lo12:.LC94
	bl	printf
.L3017:
	adrp	x26, .LANCHOR26
	ldrb	w0, [x25, #:lo12:.LANCHOR48]
	strb	wzr, [x26, #:lo12:.LANCHOR26]
	tbz	x0, 0, .L3018
	ldrb	w0, [x22, #:lo12:.LANCHOR47]
	cmp	w0, 155
	beq	.L3019
	mov	w0, 4
	bl	flash_set_interface_mode
	mov	w0, 4
	bl	nandc_set_if_mode
.L3019:
	mov	w0, 1
	bl	flash_set_interface_mode
	mov	w0, 1
.L3065:
	bl	nandc_set_if_mode
	bl	flash_info_blk_init
	mov	w22, w0
	cmn	w0, #1
	bne	.L3021
	ldr	x0, [x23, #:lo12:.LANCHOR6]
	mov	w1, 17
	strb	w1, [x0, 32]
	adrp	x0, .LANCHOR33
	strb	wzr, [x0, #:lo12:.LANCHOR33]
	mov	w0, 0
	bl	zftl_flash_exit_slc_mode
	b	.L2987
.L2995:
	add	x10, x10, 1
	add	x8, x8, 32
	cmp	x10, 49
	bne	.L2997
	b	.L2992
.L3003:
	mov	w1, 3
	b	.L3061
.L3008:
	mov	w1, 4
	b	.L3063
.L3007:
	sub	w1, w0, #65
	cmp	w0, 33
	and	w1, w1, 255
	ccmp	w1, 1, 0, ne
	bhi	.L3010
	adrp	x0, toshiba_read_retrial
	add	x0, x0, :lo12:toshiba_read_retrial
	str	x0, [x20, #:lo12:.LANCHOR171]
	adrp	x0, .LANCHOR18
	mov	w1, 4
	strb	w1, [x0, #:lo12:.LANCHOR18]
.L3067:
	mov	w1, 7
.L3066:
	adrp	x0, .LANCHOR166
	b	.L3063
.L3010:
	sub	w2, w0, #34
	sub	w1, w0, #67
	and	w2, w2, 255
	and	w1, w1, 255
	cmp	w2, 1
	ccmp	w1, 1, 0, hi
	bhi	.L3011
	adrp	x2, toshiba_read_retrial
	add	x2, x2, :lo12:toshiba_read_retrial
	str	x2, [x20, #:lo12:.LANCHOR171]
	cmp	w0, 35
	mov	w2, 68
	ccmp	w0, w2, 4, ne
	adrp	x0, .LANCHOR166
	beq	.L3012
	mov	w2, 7
.L3062:
	strb	w2, [x0, #:lo12:.LANCHOR166]
	cmp	w1, 1
	adrp	x0, .LANCHOR18
	bhi	.L3014
	mov	w1, 4
.L3064:
	strb	w1, [x0, #:lo12:.LANCHOR18]
	b	.L3006
.L3012:
	mov	w2, 17
	b	.L3062
.L3014:
	mov	w1, 5
	b	.L3064
.L3011:
	sub	w1, w0, #36
	and	w1, w1, 255
	cmp	w1, 1
	bhi	.L3015
	adrp	x0, toshiba_3d_read_retrial
	add	x0, x0, :lo12:toshiba_3d_read_retrial
	str	x0, [x20, #:lo12:.LANCHOR171]
	b	.L3067
.L3015:
	cmp	w0, 50
	bne	.L3016
	adrp	x0, samsung_read_retrial
	mov	w1, 25
	add	x0, x0, :lo12:samsung_read_retrial
	str	x0, [x20, #:lo12:.LANCHOR171]
	b	.L3066
.L3016:
	cmp	w0, 81
	bne	.L3006
	adrp	x0, ymtc_3d_read_retrial
	add	x0, x0, :lo12:ymtc_3d_read_retrial
	str	x0, [x20, #:lo12:.LANCHOR171]
	adrp	x0, .LANCHOR166
	mov	w1, 7
	strb	w1, [x0, #:lo12:.LANCHOR166]
	adrp	x0, .LANCHOR50
	strb	wzr, [x0, #:lo12:.LANCHOR50]
	b	.L3006
.L3018:
	mov	w0, 4
	b	.L3065
.L3021:
	add	x19, x19, :lo12:.LANCHOR32
	ldrb	w0, [x19, 7]
	cmp	w0, 9
	bne	.L3022
	ldr	x0, [x23, #:lo12:.LANCHOR6]
	ldrb	w0, [x0, 20]
	cmp	w0, 1
	beq	.L3022
	strb	wzr, [x24, #:lo12:.LANCHOR24]
.L3022:
	ldrb	w0, [x27, #:lo12:.LANCHOR16]
	sub	w0, w0, #1
	and	w0, w0, 255
	cmp	w0, 7
	bhi	.L3023
	adrp	x0, hynix_read_retrial
	add	x0, x0, :lo12:hynix_read_retrial
	str	x0, [x20, #:lo12:.LANCHOR171]
.L3023:
	ldrb	w0, [x25, #:lo12:.LANCHOR48]
	tbz	x0, 2, .L3025
	ldr	x0, [x23, #:lo12:.LANCHOR6]
	ldrb	w0, [x0, 19]
	cbz	w0, .L3025
	adrp	x0, .LANCHOR211
	ldrb	w1, [x0, #:lo12:.LANCHOR211]
	adrp	x0, .LANCHOR2
	ldrh	w0, [x0, #:lo12:.LANCHOR2]
	mul	w1, w1, w0
	mov	w0, 0
	bl	flash_ddr_para_scan
	ldrb	w0, [x26, #:lo12:.LANCHOR26]
	cbnz	w0, .L3025
	ldr	x0, [x23, #:lo12:.LANCHOR6]
	strb	wzr, [x0, 19]
	bl	flash_info_flush
.L3025:
	ldr	w0, [x21, #:lo12:.LANCHOR19]
	tbz	x0, 12, .L3027
	adrp	x2, .LANCHOR213
	adrp	x0, .LC94
	add	x2, x2, :lo12:.LANCHOR213
	mov	w1, 3674
	add	x0, x0, :lo12:.LC94
	bl	printf
.L3027:
	bl	nand_flash_print_info
	mov	w22, 0
	b	.L2987
	.size	nand_flash_init, .-nand_flash_init
	.section	.text.ftl_sysblk_dump,"ax",@progbits
	.align	2
	.global	ftl_sysblk_dump
	.type	ftl_sysblk_dump, %function
ftl_sysblk_dump:
	sub	sp, sp, #144
	stp	x29, x30, [sp, 48]
	add	x29, sp, 48
	stp	x19, x20, [sp, 64]
	mov	w20, 0
	stp	x23, x24, [sp, 96]
	and	w23, w0, 65535
	stp	x25, x26, [sp, 112]
	mov	w0, 1
	stp	x27, x28, [sp, 128]
	adrp	x25, .LANCHOR94
	stp	x21, x22, [sp, 80]
	bl	buf_alloc
	ldr	x28, [x0, 8]
	adrp	x26, .LANCHOR111
	adrp	x27, .LANCHOR131
	mov	x24, x0
	add	x25, x25, :lo12:.LANCHOR94
	add	x26, x26, :lo12:.LANCHOR111
	add	x27, x27, :lo12:.LANCHOR131
	mov	w19, 0
.L3069:
	ldrh	w0, [x25]
	cmp	w0, w19
	bhi	.L3071
	add	x1, x28, 704
	mov	w3, 32
	mov	w2, 4
	adrp	x0, .LC179
	add	x0, x0, :lo12:.LC179
	bl	rknand_print_hex
	mov	x0, x24
	bl	zbuf_free
	cbz	w20, .L3072
	adrp	x1, .LANCHOR218
	adrp	x0, .LC0
	mov	w2, 1619
	add	x1, x1, :lo12:.LANCHOR218
	add	x0, x0, :lo12:.LC0
	bl	printf
.L3072:
	mov	w0, w20
	ldp	x19, x20, [sp, 64]
	ldp	x21, x22, [sp, 80]
	ldp	x23, x24, [sp, 96]
	ldp	x25, x26, [sp, 112]
	ldp	x27, x28, [sp, 128]
	ldp	x29, x30, [sp, 48]
	add	sp, sp, 144
	ret
.L3071:
	ldrh	w21, [x26]
	ldrb	w3, [x27]
	ldr	x1, [x24, 8]
	ldr	x2, [x24, 24]
	madd	w21, w21, w23, w19
	mov	w0, w21
	bl	ftl_read_ppa_page
	mov	w22, w0
	ldr	x1, [x24, 24]
	mov	w4, w0
	ldr	x0, [x24, 8]
	mov	w3, w21
	ldr	w2, [x1, 12]
	str	w2, [sp, 32]
	ldr	w2, [x1, 8]
	str	w2, [sp, 24]
	ldr	w2, [x1, 4]
	str	w2, [sp, 16]
	mov	w2, w19
	add	w19, w19, 1
	ldr	w1, [x1]
	and	w19, w19, 65535
	str	w1, [sp, 8]
	ldr	w1, [x0, 12]
	str	w1, [sp]
	mov	w1, w23
	ldp	w5, w6, [x0]
	ldr	w7, [x0, 8]
	adrp	x0, .LC160
	add	x0, x0, :lo12:.LC160
	bl	printf
	cmp	w22, 512
	ccmn	w22, #1, 4, ne
	csinc	w20, w20, wzr, ne
	b	.L3069
	.size	ftl_sysblk_dump, .-ftl_sysblk_dump
	.section	.text.ftl_open_sblk_recovery,"ax",@progbits
	.align	2
	.global	ftl_open_sblk_recovery
	.type	ftl_open_sblk_recovery, %function
ftl_open_sblk_recovery:
	stp	x29, x30, [sp, -368]!
	add	x29, sp, 0
	stp	x21, x22, [sp, 32]
	adrp	x21, .LANCHOR19
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	ldr	w0, [x21, #:lo12:.LANCHOR19]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	str	x1, [x29, 136]
	tbz	x0, 12, .L3080
	ldrh	w1, [x19, 2]
	adrp	x0, .LC180
	add	x0, x0, :lo12:.LC180
	bl	printf
.L3080:
	ldr	w0, [x21, #:lo12:.LANCHOR19]
	tbz	x0, 12, .L3081
	ldrb	w1, [x19, 5]
	adrp	x0, .LC181
	add	x0, x0, :lo12:.LC181
	bl	printf
.L3081:
	ldr	w0, [x21, #:lo12:.LANCHOR19]
	tbz	x0, 12, .L3082
	ldrh	w1, [x19]
	adrp	x0, .LC182
	add	x0, x0, :lo12:.LC182
	bl	printf
.L3082:
	ldr	w0, [x21, #:lo12:.LANCHOR19]
	tbz	x0, 12, .L3083
	ldrh	w2, [x19, 18]
	adrp	x0, .LC183
	ldrh	w1, [x19, 16]
	add	x0, x0, :lo12:.LC183
	bl	printf
.L3083:
	ldr	w0, [x21, #:lo12:.LANCHOR19]
	tbz	x0, 12, .L3084
	ldrb	w1, [x19, 9]
	adrp	x0, .LC184
	add	x0, x0, :lo12:.LC184
	bl	printf
.L3084:
	ldrh	w0, [x19, 10]
	strh	w0, [x19, 14]
	adrp	x0, .LANCHOR8
	ldrh	w1, [x19]
	ldrh	w0, [x0, #:lo12:.LANCHOR8]
	cmp	w1, w0
	bcs	.L3079
	mov	w0, 1
	adrp	x22, .LANCHOR131
	bl	buf_alloc
	mov	x20, x0
	ldrb	w0, [x22, #:lo12:.LANCHOR131]
	add	x26, x29, 176
	mov	w2, 64
	mov	w27, 2
	ldr	x1, [x20, 8]
	sub	w0, w0, #2
	lsl	w0, w0, 7
	add	x0, x1, x0, sxtw 2
	mov	w1, 255
	str	x0, [x29, 144]
	mov	x0, x26
	bl	ftl_memset
	mov	w2, 64
	mov	w1, 255
	add	x0, x29, 240
	bl	ftl_memset
	mov	w2, 64
	mov	w1, 255
	add	x0, x29, 304
	bl	ftl_memset
	ldrb	w23, [x19, 5]
	adrp	x0, .LANCHOR111
	ldrh	w24, [x19, 2]
	add	x0, x0, :lo12:.LANCHOR111
	str	wzr, [x29, 156]
	str	x0, [x29, 120]
.L3086:
	adrp	x25, .LANCHOR94
	ldrh	w0, [x25, #:lo12:.LANCHOR94]
	cmp	w0, w24
	bhi	.L3101
.L3089:
	ldrh	w0, [x19, 10]
	ldrh	w1, [x19, 6]
	ldrh	w2, [x25, #:lo12:.LANCHOR94]
	add	w1, w1, w0
	ldrb	w0, [x19, 9]
	strh	w24, [x19, 2]
	strb	w23, [x19, 5]
	mul	w0, w0, w2
	cmp	w1, w0
	beq	.L3102
	adrp	x1, .LANCHOR219
	adrp	x0, .LC0
	mov	w2, 1802
	add	x1, x1, :lo12:.LANCHOR219
	add	x0, x0, :lo12:.LC0
	bl	printf
.L3102:
	adrp	x2, .LANCHOR117
	ldrh	w3, [x19, 10]
	mov	w0, 0
	mov	w1, 0
	ldr	x4, [x2, #:lo12:.LANCHOR117]
	str	x2, [x29, 144]
.L3103:
	cmp	w1, w3
	bcc	.L3105
	ldrb	w23, [x19, 9]
	adrp	x24, .LANCHOR11
	ldrh	w1, [x25, #:lo12:.LANCHOR94]
	madd	w23, w23, w1, w0
	ldr	w0, [x21, #:lo12:.LANCHOR19]
	sub	w23, w23, w3
	and	w23, w23, 65535
	tbz	x0, 12, .L3106
	ldrh	w1, [x19]
	ldr	x2, [x24, #:lo12:.LANCHOR11]
	ubfiz	x0, x1, 1, 16
	ldrh	w3, [x2, x0]
	adrp	x0, .LC187
	mov	w2, w23
	add	x0, x0, :lo12:.LC187
	bl	printf
.L3106:
	ldr	x0, [x24, #:lo12:.LANCHOR11]
	ldrh	w1, [x19]
	strh	w23, [x0, x1, lsl 1]
	ldr	w0, [x21, #:lo12:.LANCHOR19]
	tbz	x0, 14, .L3107
	ldp	w1, w2, [x29, 176]
	adrp	x0, .LC188
	ldp	w3, w4, [x29, 184]
	add	x0, x0, :lo12:.LC188
	bl	printf
.L3107:
	ldr	x0, [x20, 8]
	mov	w1, 0
	ldrb	w2, [x22, #:lo12:.LANCHOR131]
	adrp	x28, .LANCHOR79
	mov	x24, 0
	lsl	w2, w2, 9
	bl	ftl_memset
	adrp	x0, .LC190
	add	x0, x0, :lo12:.LC190
	str	x0, [x29, 128]
	add	x0, x28, :lo12:.LANCHOR79
	str	x0, [x29, 120]
.L3108:
	ldrb	w0, [x28, #:lo12:.LANCHOR79]
	add	x1, x28, :lo12:.LANCHOR79
	str	w24, [x29, 168]
	mul	w0, w0, w27
	cmp	w24, w0
	bcc	.L3120
	adrp	x24, .LC191
	adrp	x23, .LC190
	add	x24, x24, :lo12:.LC191
	add	x23, x23, :lo12:.LC190
	mov	x28, 0
	str	x1, [x29, 160]
.L3121:
	ldr	x0, [x29, 160]
	ldrb	w0, [x0]
	mul	w0, w0, w27
	cmp	w0, w28
	bhi	.L3127
	mov	x0, x20
	bl	zbuf_free
	ldrh	w1, [x19, 12]
	ldrh	w0, [x25, #:lo12:.LANCHOR94]
	ldrb	w2, [x19, 9]
	madd	w0, w0, w2, w1
	mov	x1, -4
	add	x0, x1, x0, sxtw 2
	ldr	x1, [x29, 144]
	ldr	x1, [x1, #:lo12:.LANCHOR117]
	ldr	w0, [x1, x0]
	cmn	w0, #1
	beq	.L3128
	adrp	x1, .LANCHOR219
	adrp	x0, .LC0
	mov	w2, 1917
	add	x1, x1, :lo12:.LANCHOR219
	add	x0, x0, :lo12:.LC0
	bl	printf
.L3128:
	ldrh	w0, [x19, 6]
	cmp	w0, 1
	bne	.L3079
	mov	x0, x19
	bl	ftl_write_last_log_page
.L3079:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 368
	ret
.L3101:
	ldrb	w23, [x19, 5]
	adrp	x0, .LANCHOR195
	add	x0, x0, :lo12:.LANCHOR195
	str	x0, [x29, 128]
.L3087:
	ldrb	w0, [x19, 9]
	cmp	w0, w23
	bhi	.L3100
	add	w24, w24, 1
	strb	wzr, [x19, 5]
	and	w24, w24, 65535
	b	.L3086
.L3100:
	add	x0, x19, x23, sxtw 1
	ldrh	w0, [x0, 16]
	str	w0, [x29, 168]
	mov	w0, 65535
	ldr	w1, [x29, 168]
	cmp	w1, w0
	beq	.L3088
	ldr	x0, [x29, 120]
	ldrb	w3, [x22, #:lo12:.LANCHOR131]
	ldr	x2, [x20, 24]
	ldrh	w0, [x0]
	madd	w0, w0, w1, w24
	ldr	x1, [x20, 8]
	str	w0, [x29, 160]
	bl	ftl_read_ppa_page
	mov	w28, w0
	cmp	w0, 512
	beq	.L3089
	cmn	w0, #1
	beq	.L3090
	ldr	x0, [x20, 24]
	ldr	w1, [x0]
	cmn	w1, #1
	bne	.L3090
	ldr	w0, [x0, 4]
	cmn	w0, #1
	bne	.L3090
	ldr	x0, [x20, 8]
	ldr	w0, [x0]
	cmn	w0, #1
	beq	.L3089
.L3090:
	ldr	x1, [x29, 128]
	mov	w0, 1
	strb	w0, [x1]
	ldrb	w0, [x19, 9]
	ldrh	w1, [x19, 10]
	madd	w0, w0, w24, w23
	cmp	w1, w0
	beq	.L3091
	adrp	x1, .LANCHOR219
	adrp	x0, .LC0
	mov	w2, 1694
	add	x1, x1, :lo12:.LANCHOR219
	add	x0, x0, :lo12:.LC0
	bl	printf
.L3091:
	ldrh	w0, [x19, 10]
	ldrh	w1, [x19, 6]
	ldrb	w2, [x19, 9]
	add	w1, w1, w0
	ldrh	w0, [x25, #:lo12:.LANCHOR94]
	mul	w0, w0, w2
	cmp	w1, w0
	beq	.L3092
	adrp	x1, .LANCHOR219
	adrp	x0, .LC0
	mov	w2, 1695
	add	x1, x1, :lo12:.LANCHOR219
	add	x0, x0, :lo12:.LC0
	bl	printf
.L3092:
	ldrb	w0, [x22, #:lo12:.LANCHOR131]
	cmp	w0, 8
	bls	.L3093
	ldr	x6, [x20, 24]
	mov	w1, 15555
	movk	w1, 0xf55f, lsl 16
	ldr	w0, [x6]
	cmp	w0, w1
	beq	.L3093
	cmn	w28, #1
	beq	.L3095
	ldr	w0, [x6, 4]
	cmn	w0, #1
	beq	.L3096
	ldr	w1, [x6, 16]
	mov	w0, 21320
	movk	w0, 0x4841, lsl 16
	cmp	w1, w0
	bne	.L3096
	ldr	x0, [x29, 144]
	mov	w1, 1024
	bl	js_hash
	ldr	w1, [x6, 20]
	cmp	w1, w0
	beq	.L3096
	ldr	w3, [x29, 160]
	mov	w5, w0
	ldr	w1, [x29, 168]
	mov	w4, w28
	mov	w2, w24
	adrp	x0, .LC185
	add	x0, x0, :lo12:.LC185
	bl	printf
	ldr	x1, [x29, 144]
	mov	w3, 16
	mov	w2, 4
	adrp	x0, .LC186
	add	x0, x0, :lo12:.LC186
	bl	rknand_print_hex
	ldr	x1, [x20, 24]
	adrp	x0, .LC147
	ldrb	w3, [x22, #:lo12:.LANCHOR131]
	mov	w2, 4
	add	x0, x0, :lo12:.LC147
	lsr	w3, w3, 1
	bl	rknand_print_hex
.L3095:
	ldrh	w0, [x19, 6]
	mov	w27, 4
	sub	w0, w0, #1
	strh	w0, [x19, 6]
	ldrh	w0, [x19, 10]
	add	w0, w0, 1
	strh	w0, [x19, 10]
	mov	w0, 1
	str	w0, [x29, 156]
.L3088:
	add	w23, w23, 1
	and	w23, w23, 65535
	b	.L3087
.L3093:
	cmn	w28, #1
	beq	.L3095
.L3096:
	ldr	x1, [x20, 24]
	ldr	w0, [x1, 4]
	cmn	w0, #1
	beq	.L3095
	ldr	w1, [x1]
	mov	w2, 15555
	movk	w2, 0xf55f, lsl 16
	cmp	w1, w2
	beq	.L3095
	bl	lpa_hash_get_ppa
	ldr	x1, [x29, 136]
	cbz	x1, .L3098
	ldr	x3, [x20, 24]
	ldr	w1, [x3, 8]
	cmp	w0, w1
	beq	.L3098
	cmn	w0, #1
	beq	.L3098
	adrp	x4, .LANCHOR31
	adrp	x5, .LANCHOR74
	mov	w28, 24
	mov	w27, 1
	ldrb	w1, [x4, #:lo12:.LANCHOR31]
	ldrh	w6, [x5, #:lo12:.LANCHOR74]
	sub	w1, w28, w1
	sub	w1, w1, w6
	lsr	w2, w0, w6
	adrp	x6, .LANCHOR75
	lsl	w1, w27, w1
	sub	w1, w1, #1
	and	w1, w1, w2
	ldrb	w2, [x6, #:lo12:.LANCHOR75]
	udiv	w1, w1, w2
	ldr	x2, [x29, 136]
	ldrh	w2, [x2]
	cmp	w2, w1, uxth
	bne	.L3098
	ldr	w8, [x3]
	adrp	x7, .LANCHOR190
	ldrb	w3, [x22, #:lo12:.LANCHOR131]
	add	x2, x7, :lo12:.LANCHOR190
	ldr	x1, [x20, 8]
	str	w8, [x29, 156]
	str	x7, [x29, 168]
	stp	x6, x4, [x29, 96]
	str	x5, [x29, 112]
	bl	ftl_read_ppa_page
	ldr	x7, [x29, 168]
	ldr	w8, [x29, 156]
	ldr	w0, [x7, #:lo12:.LANCHOR190]
	cmp	w8, w0
	bhi	.L3098
	ldr	x0, [x20, 24]
	ldr	w0, [x0, 8]
	cmn	w0, #1
	beq	.L3095
	ldp	x6, x4, [x29, 96]
	ldr	x5, [x29, 112]
	ldrb	w2, [x4, #:lo12:.LANCHOR31]
	ldrh	w1, [x5, #:lo12:.LANCHOR74]
	sub	w28, w28, w2
	sub	w28, w28, w1
	lsr	w0, w0, w1
	lsl	w27, w27, w28
	sub	w27, w27, #1
	and	w27, w27, w0
	ldrb	w0, [x6, #:lo12:.LANCHOR75]
	udiv	w0, w27, w0
	bl	ftl_vpn_decrement
	b	.L3095
.L3105:
	ldrh	w2, [x19, 12]
	add	w2, w2, w1
	ldr	w2, [x4, x2, lsl 2]
	cmn	w2, #1
	beq	.L3104
	add	w23, w0, 1
	and	w0, w23, 65535
.L3104:
	add	w1, w1, 1
	b	.L3103
.L3120:
	ldr	w0, [x26, x24, lsl 2]
	cmn	w0, #1
	bne	.L3109
.L3113:
	adrp	x0, .LANCHOR110
	ldr	x1, [x20, 24]
	mov	w23, -1
	mov	x2, 0
	ldr	x0, [x0, #:lo12:.LANCHOR110]
	ldr	w0, [x0, 8]
	stp	w0, w23, [x1]
	ldr	x0, [x20, 8]
	stp	w23, wzr, [x1, 8]
	str	wzr, [x1, 16]!
	str	wzr, [x0]
	mov	w0, 2
	bl	ftl_debug_info_fill
.L3110:
	ldr	w0, [x29, 156]
	cbz	w0, .L3115
	ldrh	w0, [x19, 6]
	cmp	w0, 1
	bls	.L3115
	add	x0, x21, :lo12:.LANCHOR19
	str	x0, [x29, 160]
	add	x0, x22, :lo12:.LANCHOR131
	str	x0, [x29, 136]
.L3180:
	mov	x0, x19
	bl	ftl_get_new_free_page
	mov	w4, w0
	ldr	x0, [x29, 160]
	ldr	w0, [x0]
	tbz	x0, 14, .L3117
	ldrh	w0, [x19, 12]
	mov	w1, w4
	ldrh	w3, [x19, 10]
	str	w4, [x29, 112]
	add	w3, w3, w0
	ldr	x0, [x20, 24]
	sub	w3, w3, #1
	ldr	w2, [x0, 4]
	ldr	x0, [x29, 128]
	bl	printf
	ldr	w4, [x29, 112]
.L3117:
	ldr	x0, [x29, 120]
	ldr	w2, [x29, 168]
	ldrh	w1, [x19, 6]
	ldrb	w0, [x0]
	mul	w0, w0, w27
	add	w0, w0, 1
	sub	w0, w0, w2
	cmp	w1, w0
	bls	.L3115
	ldr	x0, [x29, 136]
	ldr	x1, [x20, 8]
	ldr	x2, [x20, 24]
	str	w4, [x29, 104]
	ldrb	w3, [x0]
	mov	w0, w4
	bl	ftl_prog_ppa_page
	mov	w1, w0
	ldrh	w0, [x19]
	str	w1, [x29, 112]
	bl	ftl_vpn_decrement
	ldr	w1, [x29, 112]
	cmn	w23, #1
	ldr	w4, [x29, 104]
	ccmn	w1, #1, 4, ne
	beq	.L3118
	add	x0, x29, 240
	ldrh	w1, [x19, 12]
	str	w4, [x0, x24, lsl 2]
	ldrh	w0, [x19, 10]
	add	w0, w0, w1
	add	x1, x29, 304
	sub	w0, w0, #1
	str	w0, [x1, x24, lsl 2]
.L3115:
	add	x24, x24, 1
	b	.L3108
.L3109:
	ldrb	w3, [x22, #:lo12:.LANCHOR131]
	ldr	x1, [x20, 8]
	ldr	x2, [x20, 24]
	bl	ftl_read_ppa_page
	mov	w23, w0
	ldr	x0, [x20, 24]
	ldr	w0, [x0, 4]
	bl	lpa_hash_get_ppa
	mov	w4, w0
	ldr	w0, [x21, #:lo12:.LANCHOR19]
	tbz	x0, 14, .L3111
	ldr	x0, [x20, 24]
	mov	w1, w4
	ldr	w2, [x26, x24, lsl 2]
	str	w4, [x29, 160]
	ldr	w3, [x0, 4]
	adrp	x0, .LC189
	add	x0, x0, :lo12:.LC189
	bl	printf
	ldr	w4, [x29, 160]
.L3111:
	ldr	x1, [x20, 24]
	mov	x2, 0
	ldr	w0, [x26, x24, lsl 2]
	cmp	w4, w0
	mov	w0, 1
	stp	w4, w0, [x1, 8]
	csinv	w23, w23, wzr, eq
	str	wzr, [x1, 16]!
	mov	w0, 2
	bl	ftl_debug_info_fill
	cmn	w23, #1
	bne	.L3110
	b	.L3113
.L3118:
	ldrh	w0, [x19, 6]
	cmp	w0, 1
	bls	.L3115
	cmn	w23, #1
	bne	.L3180
	b	.L3115
.L3127:
	add	x0, x29, 240
	ldr	w0, [x0, x28, lsl 2]
	cmn	w0, #1
	beq	.L3123
	ldrb	w3, [x22, #:lo12:.LANCHOR131]
	ldr	w0, [x26, x28, lsl 2]
	ldr	x1, [x20, 8]
	ldr	x2, [x20, 24]
	bl	ftl_read_ppa_page
	cmp	w0, 256
	ccmn	w0, #1, 4, ne
	bne	.L3123
	add	x0, x29, 240
	ldrb	w3, [x22, #:lo12:.LANCHOR131]
	ldr	x1, [x20, 8]
	ldr	x2, [x20, 24]
	ldr	w0, [x0, x28, lsl 2]
	bl	ftl_read_ppa_page
	mov	w5, w0
	ldr	w0, [x21, #:lo12:.LANCHOR19]
	tbz	x0, 14, .L3125
	ldr	x0, [x20, 24]
	mov	w1, w5
	ldr	w3, [x26, x28, lsl 2]
	str	w5, [x29, 168]
	ldr	w2, [x0, 8]
	mov	x0, x23
	bl	printf
	ldr	w5, [x29, 168]
.L3125:
	cmn	w5, #1
	beq	.L3123
	ldr	x0, [x20, 24]
	ldr	w2, [x26, x28, lsl 2]
	ldr	w1, [x0, 8]
	cmp	w2, w1
	bne	.L3123
	ldr	w1, [x21, #:lo12:.LANCHOR19]
	tbz	x1, 14, .L3126
	add	x1, x29, 304
	ldr	w3, [x1, x28, lsl 2]
	ldr	w1, [x0, 4]
	mov	x0, x24
	bl	printf
.L3126:
	add	x1, x29, 304
	ldr	x0, [x20, 24]
	ldr	w1, [x1, x28, lsl 2]
	str	w1, [x29, 168]
	ldr	w1, [x0, 8]
	ldrh	w2, [x29, 168]
	ldr	w0, [x0, 4]
	bl	lpa_hash_update_ppa
.L3123:
	add	x28, x28, 1
	b	.L3121
.L3098:
	ldr	x3, [x20, 24]
	adrp	x0, .LANCHOR128
	ldr	w0, [x0, #:lo12:.LANCHOR128]
	ldr	w1, [x3, 4]
	cmp	w1, w0
	bcs	.L3095
	ldrb	w0, [x19, 9]
	ldrh	w1, [x25, #:lo12:.LANCHOR94]
	ldrh	w2, [x19, 10]
	mul	w0, w0, w1
	sub	w0, w0, #1
	cmp	w2, w0
	bge	.L3095
	adrp	x0, .LANCHOR110
	ldr	w1, [x3]
	ldr	x0, [x0, #:lo12:.LANCHOR110]
	ldr	w4, [x0, 8]
	cmp	w1, w4
	bls	.L3099
	str	w1, [x0, 8]
.L3099:
	ldrh	w0, [x19, 12]
	add	w2, w2, w0
	ldp	w0, w1, [x3, 4]
	bl	lpa_hash_update_ppa
	ldr	w0, [x29, 180]
	str	w0, [x29, 176]
	ldr	w0, [x29, 184]
	str	w0, [x29, 180]
	ldr	w0, [x29, 188]
	str	w0, [x29, 184]
	ldr	w0, [x29, 160]
	str	w0, [x29, 188]
	b	.L3095
	.size	ftl_open_sblk_recovery, .-ftl_open_sblk_recovery
	.section	.text.dump_ftl_info,"ax",@progbits
	.align	2
	.global	dump_ftl_info
	.type	dump_ftl_info, %function
dump_ftl_info:
	stp	x29, x30, [sp, -48]!
	adrp	x0, .LANCHOR57
	add	x29, sp, 0
	ldrb	w1, [x0, #:lo12:.LANCHOR57]
	adrp	x0, .LC192
	stp	x19, x20, [sp, 16]
	add	x0, x0, :lo12:.LC192
	stp	x21, x22, [sp, 32]
	adrp	x22, .LANCHOR110
	adrp	x19, .LANCHOR12
	adrp	x20, .LANCHOR94
	bl	printf
	adrp	x21, .LANCHOR8
	adrp	x0, .LANCHOR191
	add	x1, x0, :lo12:.LANCHOR191
	ldrh	w3, [x1, 2]
	ldrb	w2, [x1, 1]
	ldrb	w1, [x0, #:lo12:.LANCHOR191]
	adrp	x0, .LC193
	add	x0, x0, :lo12:.LC193
	bl	printf
	ldr	x0, [x22, #:lo12:.LANCHOR110]
	ldrh	w2, [x0, 140]
	ldrh	w1, [x0, 130]
	adrp	x0, .LC194
	add	x0, x0, :lo12:.LC194
	bl	printf
	ldr	x1, [x19, #:lo12:.LANCHOR12]
	adrp	x0, .LC195
	add	x0, x0, :lo12:.LC195
	ldrh	w5, [x1, 26]
	ldrh	w4, [x1, 22]
	ldrb	w3, [x1, 21]
	ldrh	w2, [x1, 18]
	ldrh	w1, [x1, 16]
	bl	printf
	ldr	x1, [x19, #:lo12:.LANCHOR12]
	adrp	x0, .LC196
	add	x0, x0, :lo12:.LC196
	ldrh	w5, [x1, 58]
	ldrh	w4, [x1, 54]
	ldrb	w3, [x1, 53]
	ldrh	w2, [x1, 50]
	ldrh	w1, [x1, 48]
	bl	printf
	ldr	x1, [x19, #:lo12:.LANCHOR12]
	adrp	x19, .LANCHOR79
	adrp	x0, .LC197
	add	x0, x0, :lo12:.LC197
	ldrh	w5, [x1, 90]
	ldrh	w4, [x1, 86]
	ldrb	w3, [x1, 85]
	ldrh	w2, [x1, 82]
	ldrh	w1, [x1, 80]
	bl	printf
	ldrb	w0, [x19, #:lo12:.LANCHOR79]
	mov	w2, 4
	ldrh	w3, [x20, #:lo12:.LANCHOR94]
	mul	w3, w3, w0
	adrp	x0, .LANCHOR117
	ldr	x1, [x0, #:lo12:.LANCHOR117]
	adrp	x0, .LC198
	lsl	w3, w3, 1
	add	x0, x0, :lo12:.LC198
	bl	rknand_print_hex
	adrp	x0, .LANCHOR11
	ldrh	w3, [x21, #:lo12:.LANCHOR8]
	mov	w2, 2
	ldr	x1, [x0, #:lo12:.LANCHOR11]
	adrp	x0, .LC199
	add	x0, x0, :lo12:.LC199
	bl	rknand_print_hex
	ldr	x1, [x22, #:lo12:.LANCHOR110]
	mov	w2, 4
	adrp	x0, .LC179
	add	x0, x0, :lo12:.LC179
	add	x1, x1, 704
	ldrh	w3, [x1, -6]
	bl	rknand_print_hex
	adrp	x0, .LANCHOR9
	ldrh	w3, [x21, #:lo12:.LANCHOR8]
	mov	w2, 4
	ldr	x1, [x0, #:lo12:.LANCHOR9]
	adrp	x0, .LC200
	add	x0, x0, :lo12:.LC200
	bl	rknand_print_hex
	mov	w3, 256
	mov	w2, 2
	adrp	x1, .LANCHOR116
	adrp	x0, .LC201
	add	x1, x1, :lo12:.LANCHOR116
	add	x0, x0, :lo12:.LC201
	bl	rknand_print_hex
	ldrb	w0, [x19, #:lo12:.LANCHOR79]
	mov	w2, 2
	ldrh	w3, [x20, #:lo12:.LANCHOR94]
	ldp	x21, x22, [sp, 32]
	ldp	x19, x20, [sp, 16]
	mul	w3, w3, w0
	adrp	x0, .LANCHOR118
	ldp	x29, x30, [sp], 48
	lsl	w3, w3, 1
	ldr	x1, [x0, #:lo12:.LANCHOR118]
	adrp	x0, .LC202
	add	x0, x0, :lo12:.LC202
	b	rknand_print_hex
	.size	dump_ftl_info, .-dump_ftl_info
	.section	.text.pm_ppa_update_check,"ax",@progbits
	.align	2
	.global	pm_ppa_update_check
	.type	pm_ppa_update_check, %function
pm_ppa_update_check:
	adrp	x4, .LANCHOR31
	adrp	x3, .LANCHOR74
	mov	w5, 24
	ldrb	w4, [x4, #:lo12:.LANCHOR31]
	ldrh	w3, [x3, #:lo12:.LANCHOR74]
	sub	w4, w5, w4
	sub	w5, w4, w3
	mov	w4, 1
	lsr	w3, w2, w3
	lsl	w4, w4, w5
	sub	w4, w4, #1
	and	w4, w4, w3
	adrp	x3, .LANCHOR75
	ldrb	w3, [x3, #:lo12:.LANCHOR75]
	udiv	w4, w4, w3
	adrp	x3, .LANCHOR9
	ldr	x3, [x3, #:lo12:.LANCHOR9]
	add	x4, x3, x4, uxth 2
	ldrb	w3, [x4, 2]
	ubfx	x3, x3, 5, 3
	cmp	w3, 1
	ccmp	w3, 7, 4, ne
	bne	.L3212
	mov	w3, w2
	mov	w2, w1
	mov	x1, x0
	stp	x29, x30, [sp, -16]!
	adrp	x0, .LC203
	add	x0, x0, :lo12:.LC203
	add	x29, sp, 0
	bl	printf
	bl	dump_ftl_info
	mov	w0, -1
	ldp	x29, x30, [sp], 16
	ret
.L3212:
	mov	w0, 0
	ret
	.size	pm_ppa_update_check, .-pm_ppa_update_check
	.section	.text.load_l2p_region,"ax",@progbits
	.align	2
	.type	load_l2p_region, %function
load_l2p_region:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	and	w19, w0, 65535
	stp	x21, x22, [sp, 32]
	and	x21, x1, 65535
	stp	x23, x24, [sp, 48]
	cmp	w21, 31
	stp	x25, x26, [sp, 64]
	bls	.L3218
	adrp	x1, .LANCHOR220
	adrp	x0, .LC0
	mov	w2, 32
	add	x1, x1, :lo12:.LANCHOR220
	add	x0, x0, :lo12:.LC0
	bl	printf
.L3218:
	adrp	x20, .LANCHOR110
	mov	x25, x20
	ldr	x0, [x20, #:lo12:.LANCHOR110]
	ldrh	w2, [x0, 698]
	cmp	w2, w19
	bcs	.L3219
	mov	w1, w19
	adrp	x0, .LC204
	add	x0, x0, :lo12:.LC204
	bl	printf
	adrp	x0, .LANCHOR221
	mov	w1, 255
	ldrh	w2, [x0, #:lo12:.LANCHOR221]
	mov	x0, 0
	ldr	x0, [x0, 8]
	bl	ftl_memset
	ldr	x0, [x20, #:lo12:.LANCHOR110]
	ldrh	w0, [x0, 698]
	cmp	w0, w19
	bcc	.L3220
.L3230:
	mov	w0, 0
.L3217:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
.L3220:
	mov	w2, 37
.L3231:
	adrp	x1, .LANCHOR220
	adrp	x0, .LC0
	add	x1, x1, :lo12:.LANCHOR220
	add	x0, x0, :lo12:.LC0
	bl	printf
	b	.L3230
.L3219:
	add	x0, x0, x19, sxtw 2
	adrp	x22, .LANCHOR135
	add	x1, x22, :lo12:.LANCHOR135
	ldr	w23, [x0, 704]
	lsl	x0, x21, 4
	add	x26, x1, x0
	strh	w19, [x1, x0]
	strh	wzr, [x26, 2]
	cbnz	w23, .L3222
	mov	w1, w19
	mov	w2, 0
	adrp	x0, .LC205
	add	x0, x0, :lo12:.LC205
	bl	printf
	adrp	x0, .LANCHOR221
	mov	w1, 255
	ldrh	w2, [x0, #:lo12:.LANCHOR221]
	ldr	x0, [x26, 8]
	bl	ftl_memset
	b	.L3230
.L3222:
	adrp	x20, .LANCHOR207
	adrp	x24, .LANCHOR131
	ldr	x1, [x26, 8]
	mov	w0, w23
	ldr	x2, [x20, #:lo12:.LANCHOR207]
	ldrb	w3, [x24, #:lo12:.LANCHOR131]
	bl	ftl_read_ppa_page
	ldr	x1, [x20, #:lo12:.LANCHOR207]
	ldr	w2, [x1]
	cmp	w2, w19
	bne	.L3223
	cmp	w0, 512
	ccmn	w0, #1, 4, ne
	beq	.L3223
.L3227:
	ldr	x0, [x20, #:lo12:.LANCHOR207]
	ldr	w0, [x0]
	cmp	w19, w0
	beq	.L3230
	mov	w2, 73
	b	.L3231
.L3223:
	mov	w4, w23
	mov	w3, w0
	mov	w1, w19
	adrp	x0, .LC206
	add	x0, x0, :lo12:.LC206
	bl	printf
	ldr	x1, [x25, #:lo12:.LANCHOR110]
	add	x22, x22, :lo12:.LANCHOR135
	add	x21, x22, x21, lsl 4
	mov	w2, 4
	add	x1, x1, 704
	adrp	x0, .LC207
	add	x0, x0, :lo12:.LC207
	ldrh	w3, [x1, -6]
	bl	rknand_print_hex
	ldr	x1, [x21, 8]
	mov	w2, 4
	ldrb	w3, [x24, #:lo12:.LANCHOR131]
	adrp	x0, .LC186
	add	x0, x0, :lo12:.LC186
	lsl	w3, w3, 7
	bl	rknand_print_hex
	ldr	x1, [x20, #:lo12:.LANCHOR207]
	mov	w3, 16
	mov	w2, 4
	adrp	x0, .LC208
	add	x0, x0, :lo12:.LC208
	bl	rknand_print_hex
	ldrb	w3, [x24, #:lo12:.LANCHOR131]
	mov	w0, w23
	ldr	x2, [x20, #:lo12:.LANCHOR207]
	ldr	x1, [x21, 8]
	bl	ftl_read_ppa_page
	cmp	w0, 512
	ccmn	w0, #1, 4, ne
	bne	.L3226
	adrp	x0, .LANCHOR221
	mov	w1, 255
	ldrh	w2, [x0, #:lo12:.LANCHOR221]
	ldr	x0, [x21, 8]
	bl	ftl_memset
.L3228:
	mov	w0, -1
	b	.L3217
.L3226:
	ldr	x0, [x20, #:lo12:.LANCHOR207]
	ldr	w0, [x0]
	cmp	w19, w0
	beq	.L3227
	b	.L3228
	.size	load_l2p_region, .-load_l2p_region
	.section	.text.pm_gc,"ax",@progbits
	.align	2
	.global	pm_gc
	.type	pm_gc, %function
pm_gc:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	adrp	x19, .LANCHOR110
	stp	x21, x22, [sp, 32]
	adrp	x21, .LANCHOR148
	ldr	x0, [x19, #:lo12:.LANCHOR110]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	ldrh	w2, [x0, 688]
	adrp	x0, .LANCHOR152
	str	x27, [sp, 80]
	mov	x20, x0
	ldrh	w1, [x0, #:lo12:.LANCHOR152]
	sub	w1, w1, #1
	cmp	w2, w1
	bge	.L3233
	ldr	w0, [x21, #:lo12:.LANCHOR148]
	cbz	w0, .L3234
.L3233:
	bl	pm_free_sblk
	ldr	x2, [x19, #:lo12:.LANCHOR110]
	ldrh	w1, [x20, #:lo12:.LANCHOR152]
	sub	w1, w1, #1
	ldrh	w3, [x2, 688]
	cmp	w3, w1
	bge	.L3235
	ldr	w1, [x21, #:lo12:.LANCHOR148]
	cbz	w1, .L3234
.L3235:
	add	x0, x2, x0, uxth 1
	str	wzr, [x21, #:lo12:.LANCHOR148]
	mov	w20, 65535
	ldrh	w21, [x0, 416]
	cmp	w21, w20
	bne	.L3237
	adrp	x1, .LANCHOR222
	add	x1, x1, :lo12:.LANCHOR222
	mov	w2, 182
	adrp	x0, .LC0
	add	x0, x0, :lo12:.LC0
	bl	printf
	bl	pm_free_sblk
	ldr	x1, [x19, #:lo12:.LANCHOR110]
	add	x0, x1, x0, uxth 1
	ldrh	w21, [x0, 416]
	cmp	w21, w20
	beq	.L3234
.L3237:
	bl	pm_select_ram_region
	and	x22, x0, 65535
	lsl	x0, x22, 4
	adrp	x20, .LANCHOR135
	add	x1, x20, :lo12:.LANCHOR135
	mov	x25, x22
	add	x23, x1, x0
	ldrh	w0, [x1, x0]
	mov	w1, 65535
	cmp	w0, w1
	beq	.L3238
	ldr	x1, [x23, 8]
	cbz	x1, .L3238
	ldrsh	w2, [x23, 2]
	tbz	w2, #31, .L3238
	bl	pm_write_page
	ldrh	w0, [x23, 2]
	and	w0, w0, 32767
	strh	w0, [x23, 2]
.L3238:
	adrp	x23, .LANCHOR74
	adrp	x24, .LANCHOR31
	add	x23, x23, :lo12:.LANCHOR74
	add	x24, x24, :lo12:.LANCHOR31
	mov	w27, 0
	mov	w26, 24
.L3239:
	ldr	x2, [x19, #:lo12:.LANCHOR110]
	ldrh	w0, [x2, 698]
	cmp	w0, w27
	bhi	.L3242
	bl	pm_free_sblk
.L3234:
	mov	w0, 0
	ldr	x27, [sp, 80]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 96
	ret
.L3242:
	ldrb	w0, [x24]
	add	x2, x2, x27, sxtw 2
	ldrh	w3, [x23]
	sub	w0, w26, w0
	sub	w1, w0, w3
	mov	w0, 1
	lsl	w0, w0, w1
	ldr	w1, [x2, 704]
	sub	w0, w0, #1
	lsr	w1, w1, w3
	and	w0, w0, w1
	adrp	x1, .LANCHOR75
	ldrb	w1, [x1, #:lo12:.LANCHOR75]
	udiv	w0, w0, w1
	cmp	w21, w0, uxth
	bne	.L3240
	mov	w1, w25
	mov	w0, w27
	bl	load_l2p_region
	cbnz	w0, .L3241
	add	x0, x20, :lo12:.LANCHOR135
	add	x0, x0, x22, lsl 4
	ldr	x1, [x0, 8]
	mov	w0, w27
	bl	pm_write_page
.L3241:
	add	x1, x20, :lo12:.LANCHOR135
	lsl	x0, x22, 4
	mov	w2, -1
	strh	w2, [x1, x0]
.L3240:
	add	w27, w27, 1
	and	w27, w27, 65535
	b	.L3239
	.size	pm_gc, .-pm_gc
	.section	.text.pm_flush_id,"ax",@progbits
	.align	2
	.global	pm_flush_id
	.type	pm_flush_id, %function
pm_flush_id:
	stp	x29, x30, [sp, -32]!
	ubfiz	x0, x0, 4, 16
	adrp	x2, .LANCHOR135
	add	x2, x2, :lo12:.LANCHOR135
	add	x29, sp, 0
	str	x19, [sp, 16]
	add	x19, x2, x0
	ldrh	w0, [x2, x0]
	ldr	x1, [x19, 8]
	bl	pm_write_page
	ldrh	w0, [x19, 2]
	and	w0, w0, 32767
	strh	w0, [x19, 2]
	adrp	x19, .LANCHOR204
	ldr	w0, [x19, #:lo12:.LANCHOR204]
	cbz	w0, .L3251
	bl	pm_gc
	str	wzr, [x19, #:lo12:.LANCHOR204]
.L3251:
	mov	w0, 0
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	pm_flush_id, .-pm_flush_id
	.section	.text.pm_flush,"ax",@progbits
	.align	2
	.global	pm_flush
	.type	pm_flush, %function
pm_flush:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	adrp	x19, .LANCHOR135
	add	x19, x19, :lo12:.LANCHOR135
	mov	w20, 0
	add	x19, x19, 2
.L3258:
	ldrsh	w0, [x19]
	tbz	w0, #31, .L3257
	mov	w0, w20
	bl	pm_flush_id
.L3257:
	add	w20, w20, 1
	add	x19, x19, 16
	and	w20, w20, 65535
	cmp	w20, 32
	bne	.L3258
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	pm_flush, .-pm_flush
	.section	.text.flt_sys_flush,"ax",@progbits
	.align	2
	.global	flt_sys_flush
	.type	flt_sys_flush, %function
flt_sys_flush:
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
	bl	ftl_flush
	bl	pm_flush
	bl	ftl_ext_info_flush
	ldp	x29, x30, [sp], 16
	mov	w0, 0
	b	ftl_info_flush
	.size	flt_sys_flush, .-flt_sys_flush
	.section	.text.rk_ftl_de_init,"ax",@progbits
	.align	2
	.global	rk_ftl_de_init
	.type	rk_ftl_de_init, %function
rk_ftl_de_init:
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
	bl	zftl_flash_de_init
	bl	flt_sys_flush
	ldp	x29, x30, [sp], 16
	b	zftl_flash_de_init
	.size	rk_ftl_de_init, .-rk_ftl_de_init
	.section	.text.zftl_deinit,"ax",@progbits
	.align	2
	.global	zftl_deinit
	.type	zftl_deinit, %function
zftl_deinit:
	b	rk_ftl_de_init
	.size	zftl_deinit, .-zftl_deinit
	.section	.text.pm_init,"ax",@progbits
	.align	2
	.global	pm_init
	.type	pm_init, %function
pm_init:
	stp	x29, x30, [sp, -112]!
	mov	w1, 1
	add	x29, sp, 0
	stp	x23, x24, [sp, 48]
	mov	w24, w0
	adrp	x0, .LANCHOR148
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	adrp	x19, .LANCHOR135
	str	wzr, [x0, #:lo12:.LANCHOR148]
	adrp	x0, .LANCHOR204
	stp	x25, x26, [sp, 64]
	add	x20, x19, :lo12:.LANCHOR135
	str	wzr, [x0, #:lo12:.LANCHOR204]
	adrp	x0, .LANCHOR208
	stp	x27, x28, [sp, 80]
	adrp	x22, .LANCHOR131
	strb	w1, [x0, #:lo12:.LANCHOR208]
	mov	w0, 64
	bl	ftl_malloc
	add	x23, x20, 512
	adrp	x1, .LANCHOR207
	add	x22, x22, :lo12:.LANCHOR131
	mov	x21, x1
	mov	w25, -1
	str	x0, [x1, #:lo12:.LANCHOR207]
.L3268:
	strh	w25, [x20]
	strh	wzr, [x20, 2]
	cbz	w24, .L3267
	ldrb	w0, [x22]
	lsl	w0, w0, 9
	bl	ftl_malloc
	str	x0, [x20, 8]
.L3267:
	add	x20, x20, 16
	cmp	x20, x23
	bne	.L3268
	add	x0, x19, :lo12:.LANCHOR135
	adrp	x20, .LANCHOR110
	ldr	x22, [x21, #:lo12:.LANCHOR207]
	mov	w4, 4
	ldr	x27, [x0, 8]
	mov	x3, x22
	ldr	x0, [x20, #:lo12:.LANCHOR110]
	mov	x2, x27
	ldrh	w1, [x0, 692]
	ldrb	w0, [x0, 694]
	bl	flash_get_last_written_page
	sxth	w26, w0
	ldr	x0, [x20, #:lo12:.LANCHOR110]
	mov	w24, w26
	ldrh	w2, [x0, 696]
	cmp	w2, w26
	bgt	.L3269
	ldrh	w1, [x0, 692]
	mov	w3, w26
	adrp	x0, .LC209
	add	x0, x0, :lo12:.LC209
	adrp	x25, .LANCHOR131
	add	x25, x25, :lo12:.LANCHOR131
	adrp	x28, .LC210
	bl	printf
	ldr	x0, [x20, #:lo12:.LANCHOR110]
	ldrsh	w21, [x0, 696]
	adrp	x0, .LANCHOR111
	add	x0, x0, :lo12:.LANCHOR111
	str	x0, [x29, 104]
.L3270:
	cmp	w21, w26
	ble	.L3273
	adrp	x0, .LANCHOR195
	mov	w1, 1
	add	w24, w24, 1
	strb	w1, [x0, #:lo12:.LANCHOR195]
	ldr	x0, [x20, #:lo12:.LANCHOR110]
	strh	w24, [x0, 696]
	bl	pm_free_sblk
.L3269:
	add	x19, x19, :lo12:.LANCHOR135
	adrp	x0, .LANCHOR221
	mov	w1, 255
	ldrh	w2, [x0, #:lo12:.LANCHOR221]
	ldr	x0, [x19, 8]
	bl	ftl_memset
	ldr	x1, [x19, 8]
	mov	w0, -1
	bl	pm_write_page
	adrp	x0, .LANCHOR195
	ldrb	w0, [x0, #:lo12:.LANCHOR195]
	cbz	w0, .L3274
	ldr	x1, [x19, 8]
	mov	w0, -1
	bl	pm_write_page
	ldr	x1, [x19, 8]
	mov	w0, -1
	bl	pm_write_page
	ldr	x1, [x19, 8]
	mov	w0, -1
	bl	pm_write_page
.L3274:
	bl	pm_free_sblk
	bl	pm_gc
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
.L3273:
	ldr	x0, [x20, #:lo12:.LANCHOR110]
	mov	x3, x22
	ldr	x1, [x29, 104]
	mov	x2, x27
	ldrb	w4, [x25]
	ldrh	w23, [x0, 692]
	ldrh	w1, [x1]
	ldrb	w0, [x0, 694]
	madd	w23, w23, w1, w21
	mov	w1, w23
	bl	flash_read_page_en
	mov	w4, w0
	ldr	x0, [x20, #:lo12:.LANCHOR110]
	str	w4, [x29, 100]
	mov	w2, w23
	ldr	w1, [x0, 48]
	ldrh	w3, [x0, 694]
	add	w1, w1, 1
	str	w1, [x0, 48]
	add	x0, x28, :lo12:.LC210
	ldr	w1, [x22]
	bl	printf
	ldr	w4, [x29, 100]
	cmp	w4, 512
	ccmn	w4, #1, 4, ne
	beq	.L3271
	ldr	x8, [x20, #:lo12:.LANCHOR110]
	ldr	w6, [x22]
	ldrh	w0, [x8, 698]
	cmp	w6, w0
	bcs	.L3271
	ldr	w7, [x22, 8]
	cbz	w7, .L3272
	ldrb	w1, [x25]
	mov	x0, x27
	lsl	w1, w1, 9
	bl	js_hash
	cmp	w7, w0
	beq	.L3272
	adrp	x0, .LC211
	mov	w1, w7
	add	x0, x0, :lo12:.LC211
	bl	printf
.L3271:
	add	w21, w21, 1
	sxth	w21, w21
	b	.L3270
.L3272:
	add	x6, x8, x6, uxtw 2
	str	w23, [x6, 704]
	b	.L3271
	.size	pm_init, .-pm_init
	.section	.text.pm_log2phys,"ax",@progbits
	.align	2
	.global	pm_log2phys
	.type	pm_log2phys, %function
pm_log2phys:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x25, x26, [sp, 64]
	mov	w25, w0
	adrp	x0, .LANCHOR128
	stp	x23, x24, [sp, 48]
	stp	x19, x20, [sp, 16]
	mov	w24, w2
	stp	x21, x22, [sp, 32]
	mov	x23, x1
	ldr	w2, [x0, #:lo12:.LANCHOR128]
	str	x27, [sp, 80]
	cmp	w25, w2
	bcc	.L3290
	mov	w1, w25
	adrp	x0, .LC212
	add	x0, x0, :lo12:.LC212
	bl	printf
	mov	w0, -1
	cbnz	w24, .L3289
	str	w0, [x23]
.L3289:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldr	x27, [sp, 80]
	ldp	x29, x30, [sp], 96
	ret
.L3290:
	adrp	x0, .LANCHOR131
	adrp	x21, .LANCHOR135
	mov	x19, 0
	ldrb	w20, [x0, #:lo12:.LANCHOR131]
	add	x0, x21, :lo12:.LANCHOR135
	add	x0, x0, 8
	lsl	w22, w20, 7
	udiv	w22, w25, w22
	and	w26, w22, 65535
.L3296:
	ldr	x1, [x0]
	cbz	x1, .L3292
	ldrh	w1, [x0, -8]
	cmp	w1, w26
	bne	.L3292
.L3293:
	ubfiz	w20, w20, 7, 9
	msub	w25, w26, w20, w25
	and	x25, x25, 65535
	cbnz	w24, .L3294
	add	x0, x21, :lo12:.LANCHOR135
	adrp	x1, .LANCHOR31
	add	x0, x0, x19, lsl 4
	mov	w2, 24
	ldr	x0, [x0, 8]
	ldr	w0, [x0, x25, lsl 2]
	str	w0, [x23]
	ldrb	w3, [x1, #:lo12:.LANCHOR31]
	mov	w1, 1
	sub	w2, w2, w3
	lsl	w1, w1, w3
	sub	w1, w1, #1
	lsr	w0, w0, w2
	and	w0, w0, w1
	adrp	x1, .LANCHOR112
	ldrb	w1, [x1, #:lo12:.LANCHOR112]
	cmp	w0, w1
	bcc	.L3295
	mov	w0, -1
	str	w0, [x23]
.L3295:
	add	x21, x21, :lo12:.LANCHOR135
	add	x19, x21, x19, lsl 4
	ldrh	w0, [x19, 2]
	mvn	x1, x0
	tst	x1, 32767
	beq	.L3299
	add	w0, w0, 1
	strh	w0, [x19, 2]
.L3299:
	mov	w0, 0
	b	.L3289
.L3294:
	add	x0, x21, :lo12:.LANCHOR135
	ldr	w2, [x23]
	add	x0, x0, x19, lsl 4
	ldr	x1, [x0, 8]
	str	w2, [x1, x25, lsl 2]
	ldrh	w1, [x0, 2]
	orr	w1, w1, -32768
	strh	w1, [x0, 2]
	adrp	x0, .LANCHOR136
	strb	w22, [x0, #:lo12:.LANCHOR136]
	b	.L3295
.L3292:
	add	w19, w19, 1
	add	x0, x0, 16
	and	x19, x19, 65535
	cmp	w19, 32
	bne	.L3296
	bl	pm_select_ram_region
	and	x19, x0, 65535
	sbfiz	x1, x19, 4, 32
	add	x2, x21, :lo12:.LANCHOR135
	add	x3, x2, x1
	mov	w27, w0
	ldrh	w2, [x2, x1]
	mov	w1, 65535
	cmp	w2, w1
	beq	.L3297
	ldrsh	w1, [x3, 2]
	tbz	w1, #31, .L3297
	bl	pm_flush_id
.L3297:
	adrp	x0, .LANCHOR223
	mov	w1, w27
	strb	w19, [x0, #:lo12:.LANCHOR223]
	mov	w0, w26
	bl	load_l2p_region
	b	.L3293
	.size	pm_log2phys, .-pm_log2phys
	.section	.text.gc_recovery,"ax",@progbits
	.align	2
	.global	gc_recovery
	.type	gc_recovery, %function
gc_recovery:
	sub	sp, sp, #240
	adrp	x0, .LANCHOR12
	adrp	x1, .LANCHOR84
	mov	w2, 65535
	stp	x29, x30, [sp, 32]
	add	x29, sp, 32
	stp	x23, x24, [sp, 80]
	ldr	x23, [x0, #:lo12:.LANCHOR12]
	strb	wzr, [x1, #:lo12:.LANCHOR84]
	adrp	x1, .LANCHOR156
	stp	x25, x26, [sp, 96]
	mov	x26, x0
	strb	wzr, [x1, #:lo12:.LANCHOR156]
	add	x1, x23, 80
	stp	x19, x20, [sp, 48]
	str	x1, [x29, 168]
	stp	x21, x22, [sp, 64]
	ldrh	w1, [x23, 80]
	stp	x27, x28, [sp, 112]
	cmp	w1, w2
	beq	.L3306
	mov	w0, -1
	strh	w0, [x23, 130]
	mov	w0, 1
	bl	buf_alloc
	mov	x27, x0
	ldrb	w0, [x23, 89]
	add	x1, x23, 80
	adrp	x3, .LANCHOR111
	str	x3, [x29, 152]
	sub	w0, w0, #1
	add	x0, x1, x0, sxtw 1
	ldrh	w1, [x3, #:lo12:.LANCHOR111]
	ldrh	w0, [x0, 16]
	mul	w1, w0, w1
	adrp	x0, .LANCHOR78
	str	w1, [x29, 200]
	ldrb	w2, [x0, #:lo12:.LANCHOR78]
	str	x0, [x29, 176]
	cmp	w2, 2
	beq	.L3307
	adrp	x0, .LANCHOR35
	ldrb	w0, [x0, #:lo12:.LANCHOR35]
	cbnz	w0, .L3307
	adrp	x0, .LANCHOR36
	ldrb	w0, [x0, #:lo12:.LANCHOR36]
	cbz	w0, .L3308
.L3307:
	adrp	x0, .LANCHOR85
	ldrh	w0, [x0, #:lo12:.LANCHOR85]
	sub	w0, w0, #1
	add	w0, w0, w1
	orr	w2, w0, w2, lsl 24
	str	w2, [x27, 40]
.L3309:
	mov	w1, 1
	mov	x0, x27
	bl	sblk_read_page
	ldr	w0, [x27, 52]
	cmp	w0, 512
	ccmn	w0, #1, 4, ne
	beq	.L3310
	ldr	x0, [x27, 24]
	ldr	w1, [x0]
	mov	w0, 15555
	movk	w0, 0xf55f, lsl 16
	cmp	w1, w0
	beq	.L3311
.L3310:
	mov	x0, x27
	bl	zbuf_free
	ldr	x1, [x27, 24]
	ldr	x0, [x27, 8]
	ldr	w2, [x1, 12]
	str	w2, [sp, 16]
	ldr	w2, [x1, 8]
	str	w2, [sp, 8]
	ldr	w2, [x1, 4]
	str	w2, [sp]
	ldp	w3, w4, [x0]
	ldp	w5, w6, [x0, 8]
	adrp	x0, .LC213
	ldr	w7, [x1]
	add	x0, x0, :lo12:.LC213
	ldr	w1, [x27, 40]
	ldr	w2, [x27, 52]
	bl	printf
.L3400:
	adrp	x0, .LANCHOR11
	ldrh	w1, [x23, 80]
	mov	w25, 0
	ldr	x0, [x0, #:lo12:.LANCHOR11]
	strh	wzr, [x0, x1, lsl 1]
	ldr	x0, [x26, #:lo12:.LANCHOR12]
	ldrh	w1, [x23, 80]
	strh	w1, [x0, 130]
.L3312:
	ldrh	w0, [x23, 80]
	adrp	x2, .LANCHOR11
	ldr	x2, [x2, #:lo12:.LANCHOR11]
	ubfiz	x1, x0, 1, 16
	ldrh	w1, [x2, x1]
	cbnz	w1, .L3356
	bl	ftl_dump_write_open_sblk
.L3356:
	ldrh	w1, [x23, 80]
	mov	w2, w25
	adrp	x0, .LC215
	add	x0, x0, :lo12:.LC215
	bl	printf
	mov	w0, -1
	strh	w0, [x23, 80]
	bl	pm_flush
	bl	ftl_ext_info_flush
	ldr	x0, [x26, #:lo12:.LANCHOR12]
	mov	w1, 65535
	ldrh	w0, [x0, 130]
	cmp	w0, w1
	beq	.L3357
	adrp	x1, .LANCHOR8
	ldrh	w1, [x1, #:lo12:.LANCHOR8]
	cmp	w1, w0
	bhi	.L3358
	adrp	x1, .LANCHOR225
	adrp	x0, .LC0
	mov	w2, 517
	add	x1, x1, :lo12:.LANCHOR225
	add	x0, x0, :lo12:.LC0
	bl	printf
.L3358:
	ldr	x0, [x26, #:lo12:.LANCHOR12]
	ldrh	w0, [x0, 130]
	bl	ftl_free_sblk
.L3357:
	adrp	x0, .LANCHOR110
	ldr	x1, [x0, #:lo12:.LANCHOR110]
	mov	w0, -1
	strh	w0, [x1, 126]
	ldr	x1, [x26, #:lo12:.LANCHOR12]
	strh	w0, [x1, 130]
	mov	w0, 0
	bl	ftl_info_flush
.L3305:
	ldp	x19, x20, [sp, 48]
	ldp	x21, x22, [sp, 64]
	ldp	x23, x24, [sp, 80]
	ldp	x25, x26, [sp, 96]
	ldp	x27, x28, [sp, 112]
	ldp	x29, x30, [sp, 32]
	add	sp, sp, 240
	ret
.L3308:
	cmp	w2, 3
	bne	.L3309
	adrp	x0, .LANCHOR94
	ldrh	w0, [x0, #:lo12:.LANCHOR94]
	sub	w0, w0, #1
	add	w0, w0, w1
	orr	w0, w0, 50331648
	str	w0, [x27, 40]
	b	.L3309
.L3311:
	adrp	x21, .LANCHOR224
	adrp	x19, .LANCHOR85
	adrp	x20, .LANCHOR79
	adrp	x24, .LANCHOR159
	ldrb	w0, [x21, #:lo12:.LANCHOR224]
	cmp	w0, 2
	bne	.L3313
	ldr	x0, [x29, 176]
	ldrb	w0, [x0, #:lo12:.LANCHOR78]
	cmp	w0, 3
	bne	.L3313
	ldrh	w2, [x19, #:lo12:.LANCHOR85]
	adrp	x22, .LANCHOR221
	ldrb	w1, [x20, #:lo12:.LANCHOR79]
	ldr	x3, [x24, #:lo12:.LANCHOR159]
	ubfiz	w2, w2, 2, 14
	ldrh	w0, [x22, #:lo12:.LANCHOR221]
	mul	w2, w2, w1
	ldr	x1, [x27, 8]
	sub	w2, w2, w0
	and	x0, x0, 65532
	and	w2, w2, 65535
	add	x0, x3, x0
	bl	ftl_memcpy
	adrp	x0, .LANCHOR35
	ldrb	w0, [x0, #:lo12:.LANCHOR35]
	cbnz	w0, .L3314
	adrp	x0, .LANCHOR36
	ldrb	w0, [x0, #:lo12:.LANCHOR36]
	cbz	w0, .L3315
.L3314:
	ldr	w0, [x27, 40]
	sub	w0, w0, #1
.L3394:
	str	w0, [x27, 40]
	mov	w1, 1
	mov	x0, x27
	bl	sblk_read_page
	ldr	w0, [x27, 52]
	cmp	w0, 512
	ccmn	w0, #1, 4, ne
	beq	.L3317
	ldr	x0, [x27, 24]
	ldr	w1, [x0]
	mov	w0, 15555
	movk	w0, 0xf55f, lsl 16
	cmp	w1, w0
	beq	.L3318
.L3317:
	mov	x0, x27
	bl	zbuf_free
	b	.L3400
.L3315:
	adrp	x1, .LANCHOR94
	ldr	w0, [x29, 200]
	ldrh	w1, [x1, #:lo12:.LANCHOR94]
	sub	w0, w0, #1
	add	w0, w0, w1
	orr	w0, w0, 33554432
	b	.L3394
.L3318:
	ldrh	w2, [x22, #:lo12:.LANCHOR221]
.L3395:
	ldr	x1, [x27, 8]
	adrp	x22, .LANCHOR160
	ldr	x0, [x24, #:lo12:.LANCHOR159]
	bl	ftl_memcpy
	ldrb	w1, [x20, #:lo12:.LANCHOR79]
	ldrh	w0, [x19, #:lo12:.LANCHOR85]
	mul	w0, w0, w1
	adrp	x1, .LANCHOR131
	ldrb	w1, [x1, #:lo12:.LANCHOR131]
	lsl	w2, w0, 2
	cmp	w1, w0, lsr 6
	bge	.L3320
	ldr	x0, [x22, #:lo12:.LANCHOR160]
	mov	w1, 0
	bl	ftl_memset
	ldrb	w21, [x21, #:lo12:.LANCHOR224]
	cmp	w21, 1
	bne	.L3361
	ldrb	w1, [x20, #:lo12:.LANCHOR79]
	ldrh	w0, [x19, #:lo12:.LANCHOR85]
	mul	w0, w0, w1
	adrp	x1, .LANCHOR221
	ldrh	w1, [x1, #:lo12:.LANCHOR221]
	sub	w25, w1, w0, lsl 2
	ldr	x1, [x27, 8]
	mov	w2, w25
	add	x1, x1, x0, sxtw 2
	ldr	x0, [x22, #:lo12:.LANCHOR160]
	bl	ftl_memcpy
.L3321:
	adrp	x0, .LANCHOR94
	ldrh	w0, [x0, #:lo12:.LANCHOR94]
	str	w0, [x29, 184]
	ldr	x0, [x29, 176]
	ldrb	w0, [x0, #:lo12:.LANCHOR78]
	str	w0, [x29, 188]
	cmp	w0, 2
	bne	.L3322
	adrp	x0, .LANCHOR80
	ldrb	w0, [x0, #:lo12:.LANCHOR80]
	cbz	w0, .L3323
.L3322:
	adrp	x0, .LANCHOR35
	ldrb	w0, [x0, #:lo12:.LANCHOR35]
	cbz	w0, .L3324
.L3323:
	ldp	w0, w1, [x29, 184]
	mul	w0, w0, w1
	str	w0, [x29, 184]
	mov	w0, 1
	str	w0, [x29, 188]
.L3324:
	adrp	x22, .LANCHOR35
	mov	w28, 0
	add	x0, x22, :lo12:.LANCHOR35
	mov	w10, 0
	str	x0, [x29, 112]
.L3325:
	sub	w0, w28, #1
	str	w0, [x29, 144]
	ldr	w0, [x29, 184]
	cmp	w0, w28
	bls	.L3338
	add	w0, w28, w28, lsl 1
	mov	x20, 0
	sub	w0, w0, #1
	str	w0, [x29, 164]
	adrp	x0, .LANCHOR36
	add	x0, x0, :lo12:.LANCHOR36
	str	x0, [x29, 120]
	b	.L3339
.L3313:
	ldrh	w2, [x19, #:lo12:.LANCHOR85]
	ldrb	w0, [x20, #:lo12:.LANCHOR79]
	mul	w2, w2, w0
	lsl	w2, w2, 2
	b	.L3395
.L3320:
	ldr	x1, [x27, 8]
	mov	w21, 0
	add	x1, x1, x0, sxtw 2
	ldr	x0, [x22, #:lo12:.LANCHOR160]
	bl	ftl_memcpy
.L3396:
	mov	w25, 0
	b	.L3321
.L3361:
	mov	w21, 1
	b	.L3396
.L3334:
	ldp	x1, x0, [x29, 128]
	ldr	x2, [x29, 176]
	ldrh	w0, [x0, 96]
	ldrh	w1, [x1]
	ldrb	w2, [x2, #:lo12:.LANCHOR78]
	cmp	w2, 2
	mul	w0, w0, w1
	str	w0, [x29, 200]
	add	w1, w22, w0
	beq	.L3326
	ldr	x3, [x29, 112]
	ldrb	w3, [x3]
	cbz	w3, .L3327
.L3326:
	ldr	w0, [x29, 144]
	add	w1, w1, w0
	orr	w1, w1, w2, lsl 24
.L3397:
	str	w1, [x27, 40]
.L3328:
	mov	w1, 1
	str	x8, [x29, 96]
	str	w10, [x29, 104]
	mov	x0, x27
	bl	sblk_read_page
	adrp	x1, .LANCHOR160
	ldr	w10, [x29, 104]
	ldr	x0, [x27, 24]
	ldr	x8, [x29, 96]
	cbz	w21, .L3331
	ldr	x2, [x1, #:lo12:.LANCHOR160]
	ldr	w3, [x2, x8]
	cbnz	w3, .L3331
	ldr	w3, [x0, 8]
	str	w3, [x2, x8]
.L3331:
	ldr	x2, [x24, #:lo12:.LANCHOR159]
	ldr	w6, [x0, 4]
	ldr	w3, [x2, x8]
	cmp	w3, w6
	bne	.L3332
	ldr	x2, [x1, #:lo12:.LANCHOR160]
	ldr	w4, [x2, x8]
	ldr	w2, [x0, 8]
	cmp	w4, w2
	beq	.L3333
.L3332:
	ldr	x1, [x1, #:lo12:.LANCHOR160]
	ldr	w2, [x0, 12]
	str	w2, [sp]
	str	w10, [x29, 96]
	ldr	w4, [x1, x8]
	ldr	w5, [x0]
	ldr	w7, [x0, 8]
	adrp	x0, .LC214
	ldr	w1, [x27, 40]
	add	x0, x0, :lo12:.LC214
	ldr	w2, [x27, 52]
	str	x8, [x29, 104]
	bl	printf
	ldr	x0, [x24, #:lo12:.LANCHOR159]
	ldr	x8, [x29, 104]
	ldr	w10, [x29, 96]
	ldr	w0, [x0, x8]
	cmn	w0, #1
	beq	.L3333
	mov	x0, x27
	bl	zbuf_free
	adrp	x0, .LANCHOR11
	ldrh	w1, [x23, 80]
	ldr	x0, [x0, #:lo12:.LANCHOR11]
	strh	wzr, [x0, x1, lsl 1]
	ldr	x0, [x26, #:lo12:.LANCHOR12]
	ldrh	w1, [x23, 80]
	strh	w1, [x0, 130]
	b	.L3312
.L3327:
	cmp	w2, 3
	bne	.L3329
	ldr	x2, [x29, 120]
	ldrb	w2, [x2]
	cbz	w2, .L3330
	ldr	w0, [x29, 164]
	add	w1, w1, w0
	orr	w1, w1, 50331648
	b	.L3397
.L3330:
	add	w0, w28, w0
	orr	w0, w0, w22, lsl 24
.L3398:
	str	w0, [x27, 40]
	b	.L3328
.L3329:
	add	w0, w28, w0
	b	.L3398
.L3333:
	add	w10, w10, 1
	add	w22, w22, 1
	add	x8, x8, 4
.L3336:
	ldr	w0, [x29, 188]
	cmp	w0, w22
	bcs	.L3334
	add	x20, x20, 1
.L3339:
	ldr	x0, [x29, 168]
	ldrb	w0, [x0, 9]
	cmp	w0, w20
	ble	.L3335
	add	x0, x23, x20, lsl 1
	str	x0, [x29, 136]
	ldr	x0, [x29, 152]
	sbfiz	x8, x10, 2, 32
	mov	w22, 1
	add	x0, x0, :lo12:.LANCHOR111
	str	x0, [x29, 128]
	b	.L3336
.L3335:
	adrp	x0, .LANCHOR80
	ldrb	w0, [x0, #:lo12:.LANCHOR80]
	cmp	w0, 0
	cinc	w28, w28, ne
	add	w28, w28, 1
	b	.L3325
.L3338:
	mov	x0, x27
	bl	zbuf_free
	ldr	x0, [x29, 168]
	adrp	x20, .LANCHOR11
	ldrh	w3, [x19, #:lo12:.LANCHOR85]
	mov	w25, 0
	ldrh	w2, [x23, 80]
	mov	w27, 0
	ldr	x1, [x20, #:lo12:.LANCHOR11]
	mov	w28, 0
	ldrb	w0, [x0, 9]
	str	x20, [x29, 144]
	mul	w0, w0, w3
	strh	w0, [x1, x2, lsl 1]
	adrp	x0, .LANCHOR74
	add	x0, x0, :lo12:.LANCHOR74
	str	x0, [x29, 104]
.L3340:
	sub	w0, w27, #1
	str	w0, [x29, 128]
	ldr	w0, [x29, 184]
	cmp	w0, w27
	bls	.L3354
	add	w22, w27, w27, lsl 1
	mov	x21, 0
	sub	w0, w22, #1
	str	w0, [x29, 120]
	b	.L3355
.L3350:
	ldr	x1, [x24, #:lo12:.LANCHOR159]
	sbfiz	x0, x28, 2, 32
	ldr	w20, [x1, x0]
	cmn	w20, #1
	beq	.L3341
	adrp	x1, .LANCHOR160
	ldr	x1, [x1, #:lo12:.LANCHOR160]
	ldr	w0, [x1, x0]
	str	w0, [x29, 164]
	mov	w0, w20
	bl	lpa_hash_get_ppa
	str	w0, [x29, 204]
	cmn	w0, #1
	bne	.L3342
	mov	w2, 0
	add	x1, x29, 204
	mov	w0, w20
	bl	pm_log2phys
.L3342:
	ldr	x0, [x29, 136]
	ldr	x1, [x29, 152]
	ldr	x2, [x29, 176]
	ldrh	w0, [x0, 96]
	ldrh	w1, [x1, #:lo12:.LANCHOR111]
	ldrb	w2, [x2, #:lo12:.LANCHOR78]
	cmp	w2, 2
	mul	w0, w0, w1
	add	w1, w22, w0
	beq	.L3343
	adrp	x6, .LANCHOR35
	ldrb	w6, [x6, #:lo12:.LANCHOR35]
	cbz	w6, .L3344
.L3343:
	ldr	w0, [x29, 128]
	add	w1, w0, w1
	orr	w1, w1, w2, lsl 24
	str	w1, [x29, 200]
.L3345:
	ldp	x0, x1, [x29, 104]
	mov	w19, 24
	mov	w2, 1
	ldrb	w1, [x1]
	ldrh	w0, [x0]
	sub	w19, w19, w1
	ldr	w1, [x29, 164]
	sub	w19, w19, w0
	lsr	w0, w1, w0
	lsl	w19, w2, w19
	sub	w19, w19, #1
	and	w19, w19, w0
	adrp	x0, .LANCHOR75
	ldrb	w0, [x0, #:lo12:.LANCHOR75]
	udiv	w19, w19, w0
	ldr	w0, [x29, 204]
	cmp	w1, w0
	and	x19, x19, 65535
	bne	.L3348
	add	x1, x29, 200
	mov	w0, w20
	bl	pm_log2phys
	add	w25, w25, 1
	mov	w0, w19
	bl	ftl_vpn_decrement
.L3349:
	adrp	x0, .LANCHOR9
	add	w28, w28, 1
	ldr	x0, [x0, #:lo12:.LANCHOR9]
	add	x0, x0, x19, lsl 2
	ldrb	w0, [x0, 2]
	tst	w0, 224
	bne	.L3341
	ldr	x0, [x29, 144]
	lsl	x19, x19, 1
	ldr	x0, [x0, #:lo12:.LANCHOR11]
	ldrh	w1, [x0, x19]
	cbz	w1, .L3341
	strh	wzr, [x0, x19]
.L3341:
	add	w22, w22, 1
.L3352:
	ldr	w0, [x29, 188]
	cmp	w0, w22
	bcs	.L3350
	add	x21, x21, 1
.L3355:
	ldr	x0, [x29, 168]
	ldrb	w0, [x0, 9]
	cmp	w0, w21
	ble	.L3351
	add	x0, x23, x21, lsl 1
	mov	w22, 1
	str	x0, [x29, 136]
	adrp	x0, .LANCHOR31
	add	x0, x0, :lo12:.LANCHOR31
	str	x0, [x29, 112]
	b	.L3352
.L3344:
	cmp	w2, 3
	bne	.L3346
	adrp	x2, .LANCHOR36
	ldrb	w6, [x2, #:lo12:.LANCHOR36]
	lsl	w2, w22, 24
	cbz	w6, .L3347
	ldr	w0, [x29, 120]
	add	w1, w0, w1
	orr	w0, w1, w2
.L3399:
	str	w0, [x29, 200]
	b	.L3345
.L3347:
	add	w0, w27, w0
	orr	w0, w0, w2
	b	.L3399
.L3346:
	add	w0, w27, w0
	b	.L3399
.L3348:
	ldr	w1, [x29, 200]
	cmp	w0, w1
	cinc	w25, w25, eq
	b	.L3349
.L3351:
	adrp	x0, .LANCHOR80
	ldrb	w0, [x0, #:lo12:.LANCHOR80]
	cmp	w0, 0
	cinc	w27, w27, ne
	add	w27, w27, 1
	b	.L3340
.L3354:
	ldr	x0, [x29, 144]
	ldrh	w1, [x23, 80]
	ldr	x0, [x0, #:lo12:.LANCHOR11]
	strh	w25, [x0, x1, lsl 1]
	ldrh	w0, [x23, 80]
	bl	zftl_insert_data_list
	b	.L3312
.L3306:
	ldrh	w0, [x23, 130]
	cmp	w0, w1
	beq	.L3305
	adrp	x19, .LANCHOR110
	ldr	x1, [x19, #:lo12:.LANCHOR110]
	ldrh	w1, [x1, 126]
	cmp	w1, w0
	bne	.L3360
	bl	pm_flush
	ldr	x0, [x26, #:lo12:.LANCHOR12]
	ldrh	w0, [x0, 130]
	bl	ftl_free_sblk
	ldr	x0, [x19, #:lo12:.LANCHOR110]
	mov	w1, -1
	strh	w1, [x0, 126]
	mov	w0, 0
	bl	ftl_info_flush
.L3360:
	ldr	x0, [x26, #:lo12:.LANCHOR12]
	mov	w1, -1
	strh	w1, [x0, 130]
	b	.L3305
	.size	gc_recovery, .-gc_recovery
	.section	.text.gc_update_l2p_map_new,"ax",@progbits
	.align	2
	.global	gc_update_l2p_map_new
	.type	gc_update_l2p_map_new, %function
gc_update_l2p_map_new:
	stp	x29, x30, [sp, -176]!
	adrp	x0, .LANCHOR12
	adrp	x1, .LANCHOR85
	add	x29, sp, 0
	stp	x21, x22, [sp, 32]
	ldr	x21, [x0, #:lo12:.LANCHOR12]
	stp	x25, x26, [sp, 64]
	ldrh	w26, [x1, #:lo12:.LANCHOR85]
	add	x1, x21, 80
	stp	x23, x24, [sp, 48]
	adrp	x24, .LANCHOR19
	stp	x19, x20, [sp, 16]
	stp	x27, x28, [sp, 80]
	stp	x0, x1, [x29, 128]
	ldrb	w1, [x1, 9]
	mul	w26, w26, w1
	ldr	w1, [x24, #:lo12:.LANCHOR19]
	tbz	x1, 8, .L3402
	ldrh	w1, [x21, 80]
	adrp	x0, .LC216
	add	x0, x0, :lo12:.LC216
	bl	printf
.L3402:
	adrp	x23, .LANCHOR11
	adrp	x0, .LANCHOR224
	ldrh	w2, [x21, 80]
	mov	x22, 0
	ldr	x1, [x23, #:lo12:.LANCHOR11]
	mov	w25, 0
	ldrb	w0, [x0, #:lo12:.LANCHOR224]
	sub	w0, w26, w0
	strh	w0, [x1, x2, lsl 1]
	adrp	x0, .LANCHOR131
	add	x0, x0, :lo12:.LANCHOR131
	str	x0, [x29, 104]
.L3403:
	mov	w28, w22
	cmp	w26, w22
	bhi	.L3413
	ldr	w0, [x24, #:lo12:.LANCHOR19]
	tbz	x0, 8, .L3414
	ldr	x0, [x29, 128]
	mov	w3, w25
	ldr	x1, [x23, #:lo12:.LANCHOR11]
	ldrh	w2, [x21, 80]
	ldr	x0, [x0, #:lo12:.LANCHOR12]
	ldrh	w2, [x1, x2, lsl 1]
	ldrh	w1, [x0, 80]
	adrp	x0, .LC219
	add	x0, x0, :lo12:.LC219
	bl	printf
.L3414:
	ldrh	w1, [x21, 80]
	ldr	x0, [x23, #:lo12:.LANCHOR11]
	ldrh	w0, [x0, x1, lsl 1]
	cmp	w25, w0
	beq	.L3415
	adrp	x1, .LANCHOR226
	adrp	x0, .LC0
	mov	w2, 898
	add	x1, x1, :lo12:.LANCHOR226
	add	x0, x0, :lo12:.LC0
	bl	printf
.L3415:
	ldrh	w1, [x21, 80]
	ldr	x0, [x23, #:lo12:.LANCHOR11]
	strh	w25, [x0, x1, lsl 1]
	ldrh	w0, [x21, 80]
	bl	zftl_insert_data_list
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 176
	ret
.L3413:
	adrp	x27, .LANCHOR159
	lsl	x19, x22, 2
	ldr	x0, [x27, #:lo12:.LANCHOR159]
	ldr	w2, [x0, x19]
	cmn	w2, #1
	beq	.L3404
	adrp	x0, .LANCHOR131
	ldrb	w20, [x0, #:lo12:.LANCHOR131]
	lsl	w20, w20, 7
	udiv	w20, w2, w20
	and	w0, w20, 65535
	str	w0, [x29, 156]
	ldr	w0, [x24, #:lo12:.LANCHOR19]
	tbz	x0, 8, .L3405
	ldr	w1, [x29, 156]
	adrp	x0, .LC217
	mov	w3, w22
	add	x0, x0, :lo12:.LC217
	bl	printf
.L3405:
	sub	w28, w26, w28
	add	x28, x28, x22
	lsl	x0, x28, 2
	str	x0, [x29, 144]
	adrp	x0, .LC218
	add	x0, x0, :lo12:.LC218
	str	x0, [x29, 120]
	adrp	x0, .LANCHOR74
	add	x0, x0, :lo12:.LANCHOR74
	str	x0, [x29, 112]
.L3406:
	ldr	x0, [x29, 144]
	cmp	x0, x19
	bne	.L3412
.L3404:
	add	x22, x22, 1
	b	.L3403
.L3412:
	ldr	x0, [x27, #:lo12:.LANCHOR159]
	ldr	w20, [x0, x19]
	cmn	w20, #1
	beq	.L3407
	ldr	x0, [x29, 104]
	ldr	w1, [x29, 156]
	ldrb	w0, [x0]
	lsl	w0, w0, 7
	udiv	w0, w20, w0
	cmp	w1, w0, uxth
	bne	.L3407
	adrp	x0, .LANCHOR160
	ldr	x0, [x0, #:lo12:.LANCHOR160]
	ldr	w28, [x0, x19]
	mov	w0, w20
	bl	lpa_hash_get_ppa
	str	w0, [x29, 172]
	cmn	w0, #1
	bne	.L3408
	mov	w2, 0
	add	x1, x29, 172
	mov	w0, w20
	bl	pm_log2phys
.L3408:
	ldr	w3, [x29, 172]
	cmp	w28, w3
	bne	.L3409
	adrp	x0, .LANCHOR161
	mov	w2, 1
	add	x1, x29, 168
	add	w25, w25, 1
	ldr	x0, [x0, #:lo12:.LANCHOR161]
	ldr	w0, [x0, x19]
	str	w0, [x29, 168]
	mov	w0, w20
	bl	pm_log2phys
	ldr	x0, [x29, 112]
	ldrh	w2, [x0]
	adrp	x0, .LANCHOR31
	ldrb	w1, [x0, #:lo12:.LANCHOR31]
	mov	w0, 24
	lsr	w28, w28, w2
	sub	w0, w0, w1
	sub	w1, w0, w2
	mov	w0, 1
	lsl	w0, w0, w1
	sub	w0, w0, #1
	and	w28, w0, w28
	adrp	x0, .LANCHOR75
	ldrb	w0, [x0, #:lo12:.LANCHOR75]
	udiv	w0, w28, w0
.L3435:
	bl	ftl_vpn_decrement
	ldr	x0, [x27, #:lo12:.LANCHOR159]
	mov	w1, -1
	str	w1, [x0, x19]
.L3407:
	add	x19, x19, 4
	b	.L3406
.L3409:
	ldr	w0, [x24, #:lo12:.LANCHOR19]
	tbz	x0, 8, .L3411
	ldr	x0, [x29, 120]
	mov	w2, w28
	mov	w1, w20
	bl	printf
.L3411:
	ldr	x0, [x29, 136]
	ldrh	w0, [x0]
	b	.L3435
	.size	gc_update_l2p_map_new, .-gc_update_l2p_map_new
	.section	.text.gc_scan_src_blk_one_page,"ax",@progbits
	.align	2
	.global	gc_scan_src_blk_one_page
	.type	gc_scan_src_blk_one_page, %function
gc_scan_src_blk_one_page:
	stp	x29, x30, [sp, -96]!
	mov	w3, 0
	mov	w4, 0
	mov	w5, 65535
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	adrp	x20, .LANCHOR70
	add	x1, x20, :lo12:.LANCHOR70
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	adrp	x21, .LANCHOR79
	stp	x25, x26, [sp, 64]
	ldrb	w6, [x21, #:lo12:.LANCHOR79]
	ldrb	w0, [x1, 4]
	add	x2, x1, x0, sxtw 1
	ldrh	w22, [x2, 40]
	ldrh	w2, [x1, 2]
.L3437:
	cmp	w22, w5
	beq	.L3439
	cbz	w4, .L3440
	add	x1, x20, :lo12:.LANCHOR70
	strh	w2, [x1, 2]
.L3440:
	cbz	w3, .L3441
	add	x1, x20, :lo12:.LANCHOR70
	strb	w0, [x1, 4]
.L3441:
	mov	w0, 1
	adrp	x23, .LANCHOR111
	bl	buf_alloc
	adrp	x24, .LANCHOR35
	mov	x25, x0
	add	x23, x23, :lo12:.LANCHOR111
	add	x24, x24, :lo12:.LANCHOR35
	mov	w26, 1
.L3442:
	add	x19, x20, :lo12:.LANCHOR70
	ldrb	w1, [x19, 6]
	cmp	w26, w1
	ble	.L3452
	mov	x0, x25
	bl	zbuf_free
	ldrb	w0, [x19, 4]
	ldrb	w1, [x21, #:lo12:.LANCHOR79]
	add	w0, w0, 1
	and	w0, w0, 255
	strb	w0, [x19, 4]
	cmp	w1, w0
	bne	.L3436
	ldrh	w0, [x19, 2]
	strb	wzr, [x19, 4]
	add	w0, w0, 1
	strh	w0, [x19, 2]
.L3436:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 96
	ret
.L3439:
	add	w0, w0, 1
	and	w0, w0, 255
	cmp	w0, w6
	bne	.L3438
	add	w2, w2, 1
	mov	w0, 0
	and	w2, w2, 65535
	mov	w4, 1
.L3438:
	add	x3, x1, x0, sxtw 1
	ldrh	w22, [x3, 40]
	mov	w3, 1
	b	.L3437
.L3452:
	ldrh	w0, [x23]
	cmp	w1, 2
	mul	w0, w0, w22
	bne	.L3443
	ldrh	w1, [x19, 2]
	lsl	w1, w1, 1
.L3462:
	sub	w1, w1, #1
	add	w0, w26, w0
	add	w0, w1, w0
	adrp	x1, .LANCHOR78
	ldrb	w1, [x1, #:lo12:.LANCHOR78]
	orr	w0, w0, w1, lsl 24
.L3461:
	str	w0, [x25, 40]
	mov	w1, 1
	mov	x0, x25
	bl	sblk_read_page
	ldr	w0, [x25, 52]
	cmp	w0, 512
	ccmn	w0, #1, 4, ne
	beq	.L3449
	ldr	x0, [x25, 24]
	ldr	w19, [x0, 4]
	mov	w0, w19
	bl	lpa_hash_get_ppa
	str	w0, [x29, 92]
	cmn	w0, #1
	bne	.L3450
	adrp	x0, .LANCHOR128
	ldr	w0, [x0, #:lo12:.LANCHOR128]
	cmp	w19, w0
	bcs	.L3450
	mov	w2, 0
	add	x1, x29, 92
	mov	w0, w19
	bl	pm_log2phys
.L3450:
	ldr	w2, [x25, 40]
	ldr	w0, [x29, 92]
	cmp	w2, w0
	bne	.L3449
	add	x1, x20, :lo12:.LANCHOR70
	adrp	x4, .LANCHOR76
	ldr	x4, [x4, #:lo12:.LANCHOR76]
	ldrh	w0, [x1, 24]
	ubfiz	x3, x0, 2, 16
	add	w0, w0, 1
	str	w2, [x4, x3]
	strh	w0, [x1, 24]
.L3449:
	add	x1, x20, :lo12:.LANCHOR70
	add	w26, w26, 1
	ldrh	w0, [x1, 26]
	add	w0, w0, 1
	strh	w0, [x1, 26]
	b	.L3442
.L3443:
	cmp	w1, 3
	bne	.L3445
	ldrb	w1, [x24]
	cbnz	w1, .L3446
	adrp	x1, .LANCHOR36
	ldrb	w1, [x1, #:lo12:.LANCHOR36]
	cbz	w1, .L3447
.L3446:
	add	x1, x20, :lo12:.LANCHOR70
	ldrh	w1, [x1, 2]
	add	w1, w1, w1, lsl 1
	b	.L3462
.L3447:
	ldrh	w1, [x19, 2]
	add	w0, w1, w0
	orr	w0, w0, w26, lsl 24
	b	.L3461
.L3445:
	ldrh	w1, [x19, 2]
	add	w0, w1, w0
	b	.L3461
	.size	gc_scan_src_blk_one_page, .-gc_scan_src_blk_one_page
	.section	.text.gc_scan_src_blk,"ax",@progbits
	.align	2
	.global	gc_scan_src_blk
	.type	gc_scan_src_blk, %function
gc_scan_src_blk:
	stp	x29, x30, [sp, -112]!
	mov	w0, 65535
	add	x29, sp, 0
	stp	x21, x22, [sp, 32]
	adrp	x21, .LANCHOR70
	stp	x19, x20, [sp, 16]
	ldrh	w1, [x21, #:lo12:.LANCHOR70]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	cmp	w1, w0
	stp	x27, x28, [sp, 80]
	bne	.L3464
	adrp	x1, .LANCHOR227
	adrp	x0, .LC0
	mov	w2, 1505
	add	x1, x1, :lo12:.LANCHOR227
	add	x0, x0, :lo12:.LC0
	bl	printf
.L3464:
	ldrh	w1, [x21, #:lo12:.LANCHOR70]
	mov	w0, 65535
	cmp	w1, w0
	beq	.L3494
	adrp	x0, .LANCHOR19
	ldr	w0, [x0, #:lo12:.LANCHOR19]
	tbz	x0, 8, .L3466
	adrp	x2, .LANCHOR11
	ubfiz	x0, x1, 1, 16
	ldr	x2, [x2, #:lo12:.LANCHOR11]
	ldrh	w2, [x2, x0]
	adrp	x0, .LC220
	add	x0, x0, :lo12:.LC220
	bl	printf
.L3466:
	ldrh	w0, [x21, #:lo12:.LANCHOR70]
	add	x14, x21, :lo12:.LANCHOR70
	add	x1, x14, 40
	bl	ftl_get_blk_list_in_sblk
	and	w1, w0, 255
	strb	w1, [x14, 5]
	cbnz	w1, .L3467
	mov	w0, -1
	strh	w0, [x21, #:lo12:.LANCHOR70]
.L3494:
	mov	w0, 0
	b	.L3463
.L3467:
	adrp	x4, .LANCHOR9
	ldrh	w3, [x21, #:lo12:.LANCHOR70]
	mov	x19, x4
	ldr	x1, [x4, #:lo12:.LANCHOR9]
	mov	x2, x3
	add	x1, x1, x3, lsl 2
	ldrb	w1, [x1, 2]
	and	w1, w1, 224
	cmp	w1, 32
	beq	.L3468
	cmp	w1, 224
	beq	.L3468
	cbz	w1, .L3469
	adrp	x1, .LANCHOR12
	ldr	x1, [x1, #:lo12:.LANCHOR12]
	ldrh	w3, [x1, 16]
	cmp	w3, w2
	beq	.L3468
	ldrh	w3, [x1, 48]
	cmp	w3, w2
	beq	.L3468
	ldrh	w1, [x1, 80]
	cmp	w1, w2
	bne	.L3514
.L3468:
	add	x0, x21, :lo12:.LANCHOR70
	mov	w1, -1
	strh	w1, [x21, #:lo12:.LANCHOR70]
	strh	wzr, [x0, 24]
	b	.L3494
.L3469:
	adrp	x0, .LANCHOR11
	mov	x19, x0
	ldr	x1, [x0, #:lo12:.LANCHOR11]
	ldrh	w1, [x1, x3, lsl 1]
	cbz	w1, .L3471
	adrp	x1, .LANCHOR227
	adrp	x0, .LC0
	mov	w2, 1530
	add	x1, x1, :lo12:.LANCHOR227
	add	x0, x0, :lo12:.LC0
	bl	printf
.L3471:
	ldrh	w1, [x21, #:lo12:.LANCHOR70]
	ldr	x0, [x19, #:lo12:.LANCHOR11]
	strh	wzr, [x0, x1, lsl 1]
	b	.L3468
.L3514:
	and	w0, w0, 255
	sub	w0, w0, #1
	add	x0, x14, x0, sxtw 1
	ldrh	w24, [x0, 40]
	mov	w0, 65535
	cmp	w24, w0
	bne	.L3472
	adrp	x1, .LANCHOR227
	adrp	x0, .LC0
	mov	w2, 1540
	add	x1, x1, :lo12:.LANCHOR227
	add	x0, x0, :lo12:.LC0
	bl	printf
.L3472:
	ldrh	w1, [x21, #:lo12:.LANCHOR70]
	adrp	x23, .LANCHOR111
	ldr	x2, [x19, #:lo12:.LANCHOR9]
	adrp	x22, .LANCHOR94
	ldrh	w20, [x23, #:lo12:.LANCHOR111]
	ldrh	w0, [x22, #:lo12:.LANCHOR94]
	add	x1, x2, x1, lsl 2
	sub	w0, w0, #1
	and	w0, w0, 65535
	mul	w20, w20, w24
	ldrb	w1, [x1, 2]
	and	w1, w1, 224
	cmp	w1, 160
	bne	.L3495
	adrp	x1, .LANCHOR78
	ldrb	w1, [x1, #:lo12:.LANCHOR78]
	and	w27, w1, 65535
	cmp	w1, 2
	orr	w20, w20, w1, lsl 24
	bne	.L3474
	adrp	x0, .LANCHOR85
	ldrh	w0, [x0, #:lo12:.LANCHOR85]
	sub	w0, w0, #1
	and	w0, w0, 65535
.L3474:
	adrp	x1, .LANCHOR35
	ldrb	w1, [x1, #:lo12:.LANCHOR35]
	cbnz	w1, .L3475
	adrp	x1, .LANCHOR36
	ldrb	w1, [x1, #:lo12:.LANCHOR36]
	cbz	w1, .L3473
.L3475:
	adrp	x0, .LANCHOR85
	ldrh	w0, [x0, #:lo12:.LANCHOR85]
	sub	w0, w0, #1
	and	w0, w0, 65535
.L3473:
	add	x25, x21, :lo12:.LANCHOR70
	orr	w20, w0, w20
	mov	w0, 1
	strb	w27, [x25, 6]
	strh	wzr, [x25, 2]
	strb	wzr, [x25, 4]
	strh	wzr, [x25, 26]
	strh	wzr, [x25, 28]
	bl	buf_alloc
	mov	x19, x0
	str	w20, [x0, 40]
	mov	w1, 1
	bl	sblk_read_page
	strh	wzr, [x25, 24]
	ldr	w0, [x19, 52]
	cmp	w0, 512
	ccmn	w0, #1, 4, ne
	bne	.L3476
.L3519:
	mov	x0, x19
	bl	zbuf_free
.L3517:
	mov	w0, -1
.L3463:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
.L3495:
	mov	w27, 1
	b	.L3473
.L3476:
	ldr	x7, [x19, 24]
	mov	w0, 15555
	movk	w0, 0xf55f, lsl 16
	ldr	w1, [x7]
	cmp	w1, w0
	beq	.L3477
	mov	w2, 1578
.L3520:
	adrp	x1, .LANCHOR227
	adrp	x0, .LC0
	add	x1, x1, :lo12:.LANCHOR227
	add	x0, x0, :lo12:.LC0
	bl	printf
	b	.L3519
.L3477:
	adrp	x0, .LANCHOR79
	ldrh	w26, [x22, #:lo12:.LANCHOR94]
	ldrb	w25, [x0, #:lo12:.LANCHOR79]
	adrp	x0, .LANCHOR224
	ldrb	w0, [x0, #:lo12:.LANCHOR224]
	mul	w26, w25, w26
	cmp	w0, 2
	mul	w26, w27, w26
	and	w26, w26, 65535
	bne	.L3478
	cmp	w27, 3
	bne	.L3478
	adrp	x1, .LANCHOR85
	adrp	x28, .LANCHOR221
	adrp	x27, .LANCHOR76
	ldrh	w1, [x1, #:lo12:.LANCHOR85]
	ldrh	w0, [x28, #:lo12:.LANCHOR221]
	ldr	x3, [x27, #:lo12:.LANCHOR76]
	ubfiz	w1, w1, 2, 14
	mul	w25, w25, w1
	ldr	x1, [x19, 8]
	sub	w25, w25, w0
	and	x0, x0, 65532
	and	w25, w25, 65535
	add	x0, x3, x0
	mov	w2, w25
	bl	ftl_memcpy
	ldr	x0, [x19, 24]
	ldr	w6, [x0, 4]
	cbz	w6, .L3479
	ldr	x0, [x19, 8]
	mov	w1, w25
	bl	js_hash
	cmp	w6, w0
	beq	.L3479
	mov	x0, x19
	bl	zbuf_free
	ldr	x0, [x19, 24]
	mov	w3, w25
.L3518:
	ldr	w1, [x0, 4]
	adrp	x0, .LC221
	ldr	w2, [x19, 40]
	add	x0, x0, :lo12:.LC221
	bl	printf
	b	.L3517
.L3479:
	adrp	x0, .LANCHOR35
	ldrb	w0, [x0, #:lo12:.LANCHOR35]
	cbnz	w0, .L3480
	adrp	x0, .LANCHOR36
	ldrb	w0, [x0, #:lo12:.LANCHOR36]
	cbz	w0, .L3481
.L3480:
	sub	w0, w20, #1
	str	w0, [x19, 40]
.L3482:
	mov	w1, 1
	mov	x0, x19
	bl	sblk_read_page
	ldr	w0, [x19, 52]
	cmp	w0, 512
	ccmn	w0, #1, 4, ne
	beq	.L3519
	ldr	x0, [x19, 24]
	ldr	w1, [x0]
	mov	w0, 15555
	movk	w0, 0xf55f, lsl 16
	cmp	w1, w0
	beq	.L3484
	mov	w2, 1619
	b	.L3520
.L3481:
	ldrh	w1, [x23, #:lo12:.LANCHOR111]
	ldrh	w0, [x22, #:lo12:.LANCHOR94]
	sub	w0, w0, #1
	and	w0, w0, 65535
	mul	w24, w1, w24
	orr	w0, w0, 33554432
	orr	w24, w0, w24
	str	w24, [x19, 40]
	b	.L3482
.L3484:
	ldrh	w2, [x28, #:lo12:.LANCHOR221]
	ldr	x0, [x27, #:lo12:.LANCHOR76]
	ldr	x1, [x19, 8]
.L3516:
	adrp	x20, .LANCHOR76
	bl	ftl_memcpy
	adrp	x22, .LANCHOR74
	adrp	x23, .LANCHOR31
	ldr	x24, [x20, #:lo12:.LANCHOR76]
	add	x22, x22, :lo12:.LANCHOR74
	add	x23, x23, :lo12:.LANCHOR31
	mov	x25, 0
.L3487:
	cmp	w26, w25
	bgt	.L3492
	mov	x0, x19
	bl	zbuf_free
	adrp	x0, .LANCHOR11
	ldrh	w1, [x21, #:lo12:.LANCHOR70]
	add	x3, x21, :lo12:.LANCHOR70
	mov	x19, x0
	ldr	x4, [x0, #:lo12:.LANCHOR11]
	ubfiz	x2, x1, 1, 16
	ldrh	w3, [x3, 24]
	ldrh	w2, [x4, x2]
	cmp	w2, w3
	beq	.L3493
	adrp	x0, .LC222
	add	x0, x0, :lo12:.LC222
	bl	printf
.L3493:
	add	x0, x21, :lo12:.LANCHOR70
	ldrh	w2, [x21, #:lo12:.LANCHOR70]
	ldr	x1, [x19, #:lo12:.LANCHOR11]
	ldrh	w3, [x0, 24]
	strh	w3, [x1, x2, lsl 1]
	strh	wzr, [x0, 28]
	ldrh	w0, [x0, 24]
	b	.L3463
.L3478:
	ldr	x6, [x19, 8]
	lsl	w20, w26, 2
	mov	w1, w20
	mov	x0, x6
	bl	js_hash
	ldr	w1, [x7, 4]
	cmp	w1, w0
	beq	.L3486
	mov	x0, x19
	bl	zbuf_free
	mov	w3, w20
	ldr	x0, [x19, 24]
	b	.L3518
.L3486:
	adrp	x0, .LANCHOR76
	mov	w2, w20
	mov	x1, x6
	ldr	x0, [x0, #:lo12:.LANCHOR76]
	b	.L3516
.L3492:
	ldr	w0, [x24, x25, lsl 2]
	cmn	w0, #1
	beq	.L3489
	bl	lpa_hash_get_ppa
	str	w0, [x29, 108]
	cmn	w0, #1
	bne	.L3490
	ldr	w0, [x24, x25, lsl 2]
	mov	w2, 0
	add	x1, x29, 108
	bl	pm_log2phys
.L3490:
	ldrb	w0, [x23]
	mov	w1, 24
	ldrh	w2, [x22]
	sub	w0, w1, w0
	ldr	w3, [x29, 108]
	sub	w1, w0, w2
	mov	w0, 1
	lsl	w0, w0, w1
	adrp	x1, .LANCHOR75
	sub	w0, w0, #1
	lsr	w2, w3, w2
	ldrb	w1, [x1, #:lo12:.LANCHOR75]
	and	w0, w0, w2
	ldrh	w2, [x21, #:lo12:.LANCHOR70]
	udiv	w0, w0, w1
	add	x1, x21, :lo12:.LANCHOR70
	cmp	w0, w2
	bne	.L3489
	ldrh	w0, [x1, 24]
	ldr	x4, [x20, #:lo12:.LANCHOR76]
	ubfiz	x2, x0, 2, 16
	add	w0, w0, 1
	str	w3, [x4, x2]
	strh	w0, [x1, 24]
.L3489:
	add	x25, x25, 1
	b	.L3487
	.size	gc_scan_src_blk, .-gc_scan_src_blk
	.section	.text.gc_scan_static_data,"ax",@progbits
	.align	2
	.global	gc_scan_static_data
	.type	gc_scan_static_data, %function
gc_scan_static_data:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	adrp	x19, .LANCHOR12
	stp	x21, x22, [sp, 32]
	ldr	x0, [x19, #:lo12:.LANCHOR12]
	ldr	w1, [x0, 544]
	str	x23, [sp, 48]
	cmn	w1, #1
	beq	.L3522
	adrp	x21, .LANCHOR228
	adrp	x22, .LC0
	add	x21, x21, :lo12:.LANCHOR228
	add	x22, x22, :lo12:.LC0
	mov	w20, 0
.L3530:
	ldr	x0, [x19, #:lo12:.LANCHOR12]
	mov	w2, 0
	add	x1, x29, 76
	ldr	w0, [x0, 544]
	bl	pm_log2phys
	ldr	w0, [x29, 76]
	cmn	w0, #1
	beq	.L3523
	mov	w0, 1
	bl	buf_alloc
	ldr	w1, [x29, 76]
	mov	x23, x0
	str	w1, [x0, 40]
	mov	w1, 1
	bl	sblk_read_page
	ldr	w0, [x23, 52]
	cmp	w0, 256
	bne	.L3524
	adrp	x0, .LANCHOR74
	ldr	w2, [x29, 76]
	ldrh	w3, [x0, #:lo12:.LANCHOR74]
	adrp	x0, .LANCHOR31
	ldrb	w1, [x0, #:lo12:.LANCHOR31]
	mov	w0, 24
	lsr	w2, w2, w3
	sub	w0, w0, w1
	mov	w1, 1
	sub	w0, w0, w3
	lsl	w0, w1, w0
	sub	w0, w0, #1
	and	w0, w0, w2
	adrp	x2, .LANCHOR75
	ldrb	w3, [x2, #:lo12:.LANCHOR75]
	mov	w2, 0
	udiv	w0, w0, w3
	bl	gc_add_sblk
.L3524:
	ldr	x0, [x19, #:lo12:.LANCHOR12]
	ldr	x1, [x23, 24]
	ldr	w0, [x0, 544]
	ldr	w1, [x1, 4]
	cmp	w1, w0
	beq	.L3525
	mov	w2, 2163
	mov	x1, x21
	mov	x0, x22
	bl	printf
.L3525:
	mov	x0, x23
	bl	zbuf_free
.L3523:
	ldr	x0, [x19, #:lo12:.LANCHOR12]
	adrp	x2, .LANCHOR128
	ldr	w2, [x2, #:lo12:.LANCHOR128]
	ldr	w1, [x0, 544]
	add	w1, w1, 1
	str	w1, [x0, 544]
	cmp	w1, w2
	bcc	.L3526
	mov	w1, -1
	str	w1, [x0, 544]
	ldr	w1, [x0, 548]
	add	w1, w1, 1
	str	w1, [x0, 548]
	bl	ftl_flush
	bl	pm_flush
	bl	ftl_ext_info_flush
	mov	w0, 0
	bl	ftl_info_flush
.L3521:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
.L3526:
	ldr	w0, [x29, 76]
	cmn	w0, #1
	bne	.L3521
	adrp	x1, .LANCHOR221
	add	w0, w20, 1
	and	w0, w0, 65535
	ldrh	w1, [x1, #:lo12:.LANCHOR221]
	cmp	w20, w1, lsr 2
	bcs	.L3521
	mov	w20, w0
	b	.L3530
.L3522:
	ldr	w1, [x0, 536]
	adrp	x3, .LANCHOR110
	ldr	w2, [x0, 12]
	add	w1, w1, 12959744
	add	w1, w1, 256
	cmp	w2, w1
	bhi	.L3532
	ldr	x4, [x3, #:lo12:.LANCHOR110]
	mov	w5, 5000
	ldr	w1, [x0, 540]
	add	w1, w1, w5
	ldr	w4, [x4, 44]
	cmp	w4, w1
	bls	.L3521
.L3532:
	ldr	x1, [x3, #:lo12:.LANCHOR110]
	ldr	w1, [x1, 44]
	str	w1, [x0, 540]
	str	w2, [x0, 536]
	str	wzr, [x0, 544]
	b	.L3521
	.size	gc_scan_static_data, .-gc_scan_static_data
	.section	.text.ftl_sblk_dump,"ax",@progbits
	.align	2
	.global	ftl_sblk_dump
	.type	ftl_sblk_dump, %function
ftl_sblk_dump:
	sub	sp, sp, #288
	and	x0, x0, 65535
	stp	x29, x30, [sp, 48]
	add	x29, sp, 48
	stp	x23, x24, [sp, 96]
	adrp	x24, .LANCHOR9
	lsl	x23, x0, 2
	stp	x19, x20, [sp, 64]
	str	x0, [x29, 144]
	mov	x20, x0
	ldr	x0, [x24, #:lo12:.LANCHOR9]
	str	x1, [x29, 160]
	add	x1, x0, x23
	stp	x21, x22, [sp, 80]
	stp	x25, x26, [sp, 112]
	ldr	w5, [x0, x23]
	ldrb	w2, [x1, 2]
	mov	w1, w20
	ldrh	w4, [x0, x23]
	adrp	x0, .LC223
	stp	x27, x28, [sp, 128]
	ubfx	x5, x5, 11, 8
	ubfx	x3, x2, 3, 2
	and	w4, w4, 2047
	ubfx	x2, x2, 5, 3
	add	x0, x0, :lo12:.LC223
	bl	printf
	mov	w0, 65535
	cmp	w20, w0
	beq	.L3561
	adrp	x0, .LANCHOR8
	ldrh	w0, [x0, #:lo12:.LANCHOR8]
	cmp	w0, w20
	bls	.L3561
	ldr	x0, [x24, #:lo12:.LANCHOR9]
	add	x0, x0, x23
	ldrb	w0, [x0, 2]
	and	w0, w0, 224
	cmp	w0, 160
	bne	.L3562
	adrp	x0, .LANCHOR78
	ldrb	w25, [x0, #:lo12:.LANCHOR78]
.L3540:
	add	x28, x29, 240
	adrp	x21, .LANCHOR94
	mov	w0, w20
	mov	w19, 0
	strh	w20, [x28, -32]!
	add	x1, x28, 16
	bl	ftl_get_blk_list_in_sblk
	ldrh	w2, [x21, #:lo12:.LANCHOR94]
	and	w1, w0, 255
	strb	w1, [x29, 217]
	and	w4, w0, 255
	strb	wzr, [x29, 213]
	mov	w3, w25
	strh	wzr, [x29, 210]
	adrp	x0, .LC224
	mul	w1, w1, w2
	strh	wzr, [x29, 218]
	strh	w1, [x29, 214]
	add	x0, x0, :lo12:.LC224
	ldr	x1, [x24, #:lo12:.LANCHOR9]
	add	x1, x1, x23
	ldrb	w2, [x1, 2]
	mov	w1, w20
	ubfx	x2, x2, 5, 3
	bl	printf
	mov	w0, 1
	bl	buf_alloc
	str	x21, [x29, 136]
	mov	x26, x0
	stp	wzr, wzr, [x29, 168]
	adrp	x0, .LANCHOR111
	str	wzr, [x29, 176]
	add	x0, x0, :lo12:.LANCHOR111
	str	x0, [x29, 112]
.L3541:
	ldr	x0, [x29, 136]
	ldrh	w0, [x0, #:lo12:.LANCHOR94]
	cmp	w0, w19
	bls	.L3558
	lsl	w0, w19, 1
	mov	w22, 0
	sub	w1, w0, #1
	add	w0, w0, w19
	sub	w0, w0, #1
	stp	w1, w0, [x29, 152]
	adrp	x0, .LC160
	add	x0, x0, :lo12:.LC160
	str	x0, [x29, 120]
	b	.L3559
.L3562:
	mov	w25, 1
	b	.L3540
.L3555:
	ldr	x0, [x29, 128]
	ldrh	w11, [x28, x0]
	mov	w0, 65535
	cmp	w11, w0
	beq	.L3542
	ldr	x0, [x29, 112]
	cmp	w25, 3
	ldrh	w8, [x0]
	mul	w1, w8, w11
	add	w0, w21, w1
	bne	.L3543
	adrp	x2, .LANCHOR35
	ldrb	w2, [x2, #:lo12:.LANCHOR35]
	cbz	w2, .L3544
	adrp	x1, .LANCHOR78
	ldrb	w8, [x1, #:lo12:.LANCHOR78]
	ldr	w1, [x29, 156]
.L3571:
	add	w0, w0, w1
	orr	w27, w0, w8, lsl 24
	b	.L3545
.L3544:
	adrp	x2, .LANCHOR36
	lsl	w8, w21, 24
	ldrb	w2, [x2, #:lo12:.LANCHOR36]
	cbz	w2, .L3546
	ldr	w1, [x29, 156]
	add	w0, w0, w1
	orr	w27, w0, w8
.L3545:
	str	w27, [x26, 40]
	mov	w1, 1
	str	w11, [x29, 100]
	mov	x0, x26
	bl	sblk_read_page
	ldr	x1, [x26, 24]
	mov	w3, w27
	ldr	x0, [x26, 8]
	ldr	w12, [x26, 52]
	ldr	w11, [x29, 100]
	ldr	w2, [x1, 12]
	mov	w4, w12
	str	w2, [sp, 32]
	str	w12, [x29, 104]
	ldr	w2, [x1, 8]
	str	w2, [sp, 24]
	ldr	w2, [x1, 4]
	str	w2, [sp, 16]
	mov	w2, w19
	ldr	w1, [x1]
	str	w1, [sp, 8]
	ldr	w1, [x0, 12]
	str	w1, [sp]
	mov	w1, w11
	ldp	w5, w6, [x0]
	ldr	w7, [x0, 8]
	ldr	x0, [x29, 120]
	bl	printf
	ldr	w12, [x29, 104]
	mov	w1, 32
	ldr	w0, [x29, 168]
	cmp	w12, 512
	ccmn	w12, #1, 4, ne
	csinc	w0, w0, wzr, ne
	str	w0, [x29, 168]
	ldr	x0, [x24, #:lo12:.LANCHOR9]
	add	x0, x0, x23
	ldrb	w0, [x0, 2]
	and	w0, w0, 224
	cmp	w0, 224
	ccmp	w0, w1, 4, ne
	beq	.L3542
	ldr	x0, [x26, 24]
	ldr	w0, [x0, 4]
	bl	lpa_hash_get_ppa
	str	w0, [x29, 204]
	cmn	w0, #1
	bne	.L3549
	ldr	x0, [x26, 24]
	mov	w2, 0
	add	x1, x29, 204
	ldr	w0, [x0, 4]
	bl	pm_log2phys
.L3549:
	ldr	w0, [x29, 204]
	cmp	w27, w0
	bne	.L3550
	ldr	w0, [x29, 172]
	mov	w1, w27
	add	w0, w0, 1
	str	w0, [x29, 172]
	ldr	x0, [x26, 24]
	ldr	w3, [x29, 172]
	ldr	w2, [x0, 4]
	adrp	x0, .LC225
	add	x0, x0, :lo12:.LC225
	bl	printf
.L3550:
	ldr	x0, [x29, 160]
	cbz	x0, .L3552
	ldr	x0, [x29, 176]
	ubfiz	x3, x0, 2, 32
	ldr	x0, [x29, 160]
	ldr	w2, [x0, x3]
	ldr	x0, [x26, 24]
	ldr	w0, [x0, 4]
	cmp	w0, w2
	beq	.L3553
	adrp	x0, .LANCHOR19
	ldr	w0, [x0, #:lo12:.LANCHOR19]
	tbz	x0, 12, .L3553
	ldr	w1, [x29, 176]
	adrp	x0, .LC226
	str	x3, [x29, 104]
	add	x0, x0, :lo12:.LC226
	bl	printf
	ldr	x3, [x29, 104]
.L3553:
	ldr	x1, [x26, 24]
	ldr	x0, [x29, 160]
	ldr	w1, [x1, 4]
	ldr	w0, [x0, x3]
	cmp	w1, w0
	beq	.L3552
	cmn	w0, #1
	beq	.L3552
	adrp	x1, .LANCHOR229
	adrp	x0, .LC0
	mov	w2, 1575
	add	x1, x1, :lo12:.LANCHOR229
	add	x0, x0, :lo12:.LC0
	bl	printf
.L3552:
	ldr	w0, [x29, 176]
	add	w0, w0, 1
	str	w0, [x29, 176]
.L3542:
	add	w21, w21, 1
	and	w21, w21, 65535
.L3557:
	cmp	w25, w21
	bcs	.L3555
	add	w22, w22, 1
	and	w22, w22, 65535
.L3559:
	ldrb	w0, [x29, 217]
	cmp	w0, w22
	bls	.L3556
	sxtw	x0, w22
	mov	w21, 1
	add	x0, x0, 8
	lsl	x0, x0, 1
	str	x0, [x29, 128]
	b	.L3557
.L3546:
	add	w1, w19, w1
	orr	w27, w8, w1
	b	.L3545
.L3543:
	cmp	w25, 2
	bne	.L3547
	adrp	x1, .LANCHOR78
	ldrb	w8, [x1, #:lo12:.LANCHOR78]
	ldr	w1, [x29, 152]
	b	.L3571
.L3547:
	add	w27, w19, w1
	b	.L3545
.L3556:
	add	w19, w19, 1
	and	w19, w19, 65535
	b	.L3541
.L3558:
	mov	x0, x26
	bl	zbuf_free
	adrp	x0, .LANCHOR11
	ldr	x1, [x29, 144]
	ldr	w3, [x29, 172]
	ldr	x0, [x0, #:lo12:.LANCHOR11]
	ldrh	w2, [x0, x1, lsl 1]
	mov	w1, w20
	adrp	x0, .LC227
	add	x0, x0, :lo12:.LC227
	bl	printf
	ldr	w0, [x29, 168]
.L3538:
	ldp	x19, x20, [sp, 64]
	ldp	x21, x22, [sp, 80]
	ldp	x23, x24, [sp, 96]
	ldp	x25, x26, [sp, 112]
	ldp	x27, x28, [sp, 128]
	ldp	x29, x30, [sp, 48]
	add	sp, sp, 288
	ret
.L3561:
	mov	w0, 0
	b	.L3538
	.size	ftl_sblk_dump, .-ftl_sblk_dump
	.section	.text.zftl_read,"ax",@progbits
	.align	2
	.global	zftl_read
	.type	zftl_read, %function
zftl_read:
	sub	sp, sp, #192
	stp	x29, x30, [sp, 16]
	add	x29, sp, 16
	stp	x19, x20, [sp, 32]
	mov	w19, w0
	adrp	x0, .LANCHOR19
	stp	x21, x22, [sp, 48]
	stp	x23, x24, [sp, 64]
	mov	w20, w1
	ldr	w0, [x0, #:lo12:.LANCHOR19]
	mov	w23, w2
	stp	x25, x26, [sp, 80]
	mov	x22, x3
	stp	x27, x28, [sp, 96]
	tbz	x0, 12, .L3573
	mov	w3, w2
	adrp	x0, .LC228
	mov	w2, w1
	add	x0, x0, :lo12:.LC228
	mov	w1, w19
	bl	printf
.L3573:
	cbnz	w19, .L3574
	adrp	x0, .LANCHOR67
	mov	w19, 24576
	ldr	w0, [x0, #:lo12:.LANCHOR67]
.L3575:
	cmp	w0, w20
	ccmp	w0, w23, 0, hi
	bcc	.L3608
	add	w1, w20, w23
	cmp	w0, w1
	bcc	.L3608
	adrp	x1, .LANCHOR110
	adrp	x24, .LANCHOR131
	add	w19, w19, w20
	str	x1, [x29, 112]
	ldr	x2, [x1, #:lo12:.LANCHOR110]
	ldr	w0, [x2, 24]
	add	w0, w0, w23
	str	w0, [x2, 24]
	ldrb	w0, [x24, #:lo12:.LANCHOR131]
	udiv	w2, w19, w0
	stp	wzr, w2, [x29, 152]
	add	w2, w23, w19
	str	w2, [x29, 148]
	sub	w2, w2, #1
	udiv	w0, w2, w0
	ldr	w2, [x29, 156]
	mov	x21, x2
	sub	w26, w0, w2
	str	w0, [x29, 144]
	add	w26, w26, 1
	adrp	x0, .LANCHOR134
	add	x28, x0, :lo12:.LANCHOR134
.L3577:
	cbnz	w26, .L3605
	ldr	w0, [x29, 152]
.L3572:
	ldp	x19, x20, [sp, 32]
	ldp	x21, x22, [sp, 48]
	ldp	x23, x24, [sp, 64]
	ldp	x25, x26, [sp, 80]
	ldp	x27, x28, [sp, 96]
	ldp	x29, x30, [sp, 16]
	add	sp, sp, 192
	ret
.L3574:
	cmp	w19, 3
	bhi	.L3608
	lsl	w19, w19, 13
	mov	w0, 8192
	b	.L3575
.L3605:
	ldr	w0, [x29, 156]
	ldrb	w1, [x24, #:lo12:.LANCHOR131]
	cmp	w21, w0
	ldr	w0, [x29, 144]
	and	w25, w1, 65535
	ccmp	w21, w0, 4, ne
	bne	.L3609
	ldr	w0, [x29, 156]
	cmp	w21, w0
	bne	.L3579
	udiv	w3, w19, w1
	and	w0, w23, 65535
	msub	w1, w3, w1, w19
	and	w27, w1, 65535
	sub	w25, w25, w27
	and	w25, w25, 65535
	cmp	w23, w25
	csel	w25, w0, w25, cc
.L3578:
	adrp	x20, .LANCHOR55
	add	x1, x20, :lo12:.LANCHOR55
	add	x1, x1, 2
	mov	w0, 0
.L3582:
	ldr	w2, [x1, 34]
	cmp	w21, w2
	bne	.L3580
	ldrb	w2, [x1]
	tbz	x2, 3, .L3580
	add	x1, x20, :lo12:.LANCHOR55
	ubfiz	x0, x0, 6, 32
	add	x0, x1, x0
	lsl	w2, w25, 9
	ubfiz	x25, x25, 9, 16
	ubfiz	x27, x27, 9, 16
	ldr	x1, [x0, 8]
	mov	x0, x22
	add	x22, x22, x25
	add	x1, x1, x27
	bl	ftl_memcpy
.L3581:
	add	w21, w21, 1
	sub	w26, w26, #1
.L3588:
	adrp	x0, .LANCHOR57
	ldrb	w0, [x0, #:lo12:.LANCHOR57]
	cmp	w0, 2
	bls	.L3589
	cbnz	w26, .L3577
.L3589:
	adrp	x0, .LANCHOR134
	ldrb	w1, [x0, #:lo12:.LANCHOR134]
	cbz	w1, .L3577
	adrp	x25, .LANCHOR133
	add	x0, x20, :lo12:.LANCHOR55
	ldrb	w2, [x25, #:lo12:.LANCHOR133]
	add	x0, x0, x2, lsl 6
	bl	sblk_read_page
	adrp	x0, .LANCHOR230
	add	x0, x0, :lo12:.LANCHOR230
	str	x0, [x29, 128]
	adrp	x0, .LC0
	add	x0, x0, :lo12:.LC0
	str	x0, [x29, 120]
.L3591:
	ldrb	w0, [x28]
	cbnz	w0, .L3604
	mov	w0, -1
	strb	wzr, [x28]
	strb	w0, [x25, #:lo12:.LANCHOR133]
	b	.L3577
.L3579:
	ldr	w0, [x29, 148]
	msub	w25, w1, w21, w0
	and	w25, w25, 255
.L3609:
	mov	w27, 0
	b	.L3578
.L3580:
	add	w0, w0, 1
	add	x1, x1, 64
	cmp	w0, 32
	bne	.L3582
	mov	w0, w21
	bl	lpa_hash_get_ppa
	str	w0, [x29, 172]
	cmn	w0, #1
	bne	.L3583
	mov	w2, 0
	add	x1, x29, 172
	mov	w0, w21
	bl	pm_log2phys
.L3583:
	ldr	w0, [x29, 172]
	cmn	w0, #1
	bne	.L3584
	add	x27, x24, :lo12:.LANCHOR131
	mov	w25, 0
.L3585:
	ldrb	w0, [x27]
	cmp	w25, w0
	bcs	.L3581
	madd	w0, w21, w0, w25
	cmp	w19, w0
	bhi	.L3586
	ldr	w1, [x29, 148]
	cmp	w1, w0
	bls	.L3586
	mov	x0, x22
	add	x22, x22, 512
	mov	w2, 512
	mov	w1, 0
	bl	ftl_memset
.L3586:
	add	w25, w25, 1
	b	.L3585
.L3584:
	mov	w0, 0
	bl	buf_alloc
	cbz	x0, .L3588
	ldr	x2, [x29, 112]
	ldr	x4, [x2, #:lo12:.LANCHOR110]
	ldr	w2, [x4, 40]
	add	w2, w2, 1
	str	w2, [x4, 40]
	ldr	w2, [x29, 172]
	strb	w25, [x0, 56]
	ubfiz	x25, x25, 9, 16
	str	x22, [x0, 16]
	add	x22, x22, x25
	strb	w27, [x0, 57]
	stp	w21, w2, [x0, 36]
	str	w2, [x0, 44]
	bl	zftl_add_read_buf
	b	.L3581
.L3604:
	ldrb	w0, [x25, #:lo12:.LANCHOR133]
	cmp	w0, 255
	bne	.L3592
	ldp	x0, x1, [x29, 120]
	mov	w2, 1281
	bl	printf
.L3592:
	ldrb	w27, [x25, #:lo12:.LANCHOR133]
	add	x0, x20, :lo12:.LANCHOR55
	ubfiz	x1, x27, 6, 8
	lsl	x2, x27, 6
	add	x1, x0, x1
	str	x1, [x29, 136]
	add	x1, x0, x2
	ldrb	w0, [x0, x2]
	strb	w0, [x25, #:lo12:.LANCHOR133]
	ldr	w10, [x1, 52]
	cmn	w10, #1
	bne	.L3593
	adrp	x0, .LANCHOR12
	str	w10, [x29, 152]
	ldr	x1, [x0, #:lo12:.LANCHOR12]
	ldr	w0, [x1, 552]
	add	w0, w0, 1
	str	w0, [x1, 552]
.L3594:
	add	x0, x20, :lo12:.LANCHOR55
	add	x0, x0, x27, lsl 6
	ldr	x3, [x0, 24]
	ldr	w0, [x0, 36]
	ldr	w1, [x3, 4]
	cmp	w1, w0
	bne	.L3595
	cmn	w10, #1
	bne	.L3596
.L3595:
	add	x0, x20, :lo12:.LANCHOR55
	ldrb	w4, [x24, #:lo12:.LANCHOR131]
	add	x0, x0, x27, lsl 6
	mov	w5, 1
	ldrb	w1, [x0, 56]
	ldp	x2, x7, [x0, 8]
	cmp	w1, w4
	ldr	w1, [x0, 40]
	adrp	x0, .LANCHOR31
	csel	x2, x7, x2, cs
	ldrb	w6, [x0, #:lo12:.LANCHOR31]
	mov	w0, 24
	sub	w0, w0, w6
	lsl	w5, w5, w6
	sub	w5, w5, #1
	lsl	w6, w5, w0
	lsr	w0, w1, w0
	bic	w1, w1, w6
	and	w0, w0, w5
	bl	flash_read_page_en
	mov	w10, w0
.L3596:
	add	x1, x20, :lo12:.LANCHOR55
	add	x1, x1, x27, lsl 6
	ldr	x0, [x1, 24]
	ldr	w3, [x1, 36]
	ldr	w1, [x0, 4]
	cmp	w1, w3
	bne	.L3598
	cmn	w10, #1
	bne	.L3599
.L3598:
	adrp	x1, .LANCHOR12
	add	x11, x20, :lo12:.LANCHOR55
	add	x11, x11, x27, lsl 6
	str	w10, [x29, 108]
	ldr	x2, [x1, #:lo12:.LANCHOR12]
	str	x11, [x29, 96]
	ldr	w1, [x2, 552]
	add	w1, w1, 1
	str	w1, [x2, 552]
	ldrb	w1, [x11, 1]
	ldr	w2, [x0, 12]
	str	w2, [sp]
	mov	w2, w10
	ldp	w5, w6, [x0]
	ldr	w7, [x0, 8]
	adrp	x0, .LC230
	ldr	w4, [x11, 40]
	add	x0, x0, :lo12:.LC230
	bl	printf
	adrp	x0, .LANCHOR74
	ldr	x11, [x29, 96]
	ldrh	w2, [x0, #:lo12:.LANCHOR74]
	adrp	x0, .LANCHOR31
	ldrb	w1, [x0, #:lo12:.LANCHOR31]
	mov	w0, 24
	sub	w0, w0, w1
	sub	w1, w0, w2
	mov	w0, 1
	lsl	w0, w0, w1
	ldr	w1, [x11, 40]
	sub	w0, w0, #1
	lsr	w1, w1, w2
	and	w0, w0, w1
	adrp	x1, .LANCHOR75
	ldrb	w2, [x1, #:lo12:.LANCHOR75]
	mov	x1, 0
	udiv	w0, w0, w2
	bl	ftl_sblk_dump
	ldr	w10, [x29, 108]
.L3599:
	add	x0, x20, :lo12:.LANCHOR55
	add	x0, x0, x27, lsl 6
	ldr	x1, [x0, 24]
	ldr	w0, [x0, 36]
	ldr	w1, [x1, 4]
	cmp	w1, w0
	bne	.L3600
	cmn	w10, #1
	bne	.L3601
.L3600:
	ldp	x0, x1, [x29, 120]
	mov	w2, 1317
	bl	printf
.L3601:
	add	x0, x20, :lo12:.LANCHOR55
	add	x8, x0, x27, lsl 6
	ldrb	w0, [x24, #:lo12:.LANCHOR131]
	ldrb	w2, [x8, 56]
	cmp	w0, w2
	bls	.L3602
	ldrb	w0, [x8, 57]
	lsl	w2, w2, 9
	ldr	x1, [x8, 8]
	ubfiz	x0, x0, 9, 8
	add	x1, x1, x0
	ldr	x0, [x8, 16]
	bl	ftl_memcpy
.L3603:
	ldr	x1, [x29, 136]
	adrp	x0, .LANCHOR62
	add	x0, x0, :lo12:.LANCHOR62
	bl	buf_remove_buf
	ldr	x0, [x29, 136]
	bl	zbuf_free
	ldrb	w0, [x28]
	sub	w0, w0, #1
	strb	w0, [x28]
	b	.L3591
.L3593:
	cmp	w10, 256
	bne	.L3594
	adrp	x2, .LANCHOR31
	adrp	x0, .LANCHOR74
	mov	w4, 24
	mov	w5, 1
	ldrb	w2, [x2, #:lo12:.LANCHOR31]
	ldrh	w0, [x0, #:lo12:.LANCHOR74]
	sub	w4, w4, w2
	str	w5, [x29, 96]
	ldp	w2, w3, [x1, 36]
	sub	w4, w4, w0
	lsl	w4, w5, w4
	sub	w4, w4, #1
	lsr	w0, w3, w0
	and	w4, w4, w0
	adrp	x0, .LANCHOR75
	ldrb	w0, [x0, #:lo12:.LANCHOR75]
	udiv	w4, w4, w0
	adrp	x0, .LC229
	add	x0, x0, :lo12:.LC229
	stp	w10, w4, [x29, 104]
	and	w1, w4, 65535
	bl	printf
	ldr	w5, [x29, 96]
	mov	w2, 0
	ldr	w4, [x29, 108]
	mov	w1, w5
	mov	w0, w4
	bl	gc_add_sblk
	ldr	w10, [x29, 104]
	b	.L3594
.L3602:
	ldrb	w0, [x8, 2]
	and	w0, w0, -9
	strb	w0, [x8, 2]
	b	.L3603
.L3608:
	mov	w0, -1
	b	.L3572
	.size	zftl_read, .-zftl_read
	.section	.text.zftl_sys_read,"ax",@progbits
	.align	2
	.global	zftl_sys_read
	.type	zftl_sys_read, %function
zftl_sys_read:
	mov	x3, x2
	mov	w2, w1
	mov	w1, w0
	mov	w0, 2
	b	zftl_read
	.size	zftl_sys_read, .-zftl_sys_read
	.section	.text.StorageSysDataLoad,"ax",@progbits
	.align	2
	.global	StorageSysDataLoad
	.type	StorageSysDataLoad, %function
StorageSysDataLoad:
	stp	x29, x30, [sp, -32]!
	mov	w2, 512
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x1
	mov	w20, w0
	mov	w1, 0
	mov	x0, x19
	bl	ftl_memset
	mov	x3, x19
	mov	w1, w20
	ldp	x19, x20, [sp, 16]
	mov	w2, 1
	ldp	x29, x30, [sp], 32
	mov	w0, 2
	b	zftl_read
	.size	StorageSysDataLoad, .-StorageSysDataLoad
	.section	.text.FlashBootVendorRead,"ax",@progbits
	.align	2
	.global	FlashBootVendorRead
	.type	FlashBootVendorRead, %function
FlashBootVendorRead:
	mov	x3, x2
	mov	w2, w1
	add	w1, w0, 512
	mov	w0, 2
	b	zftl_read
	.size	FlashBootVendorRead, .-FlashBootVendorRead
	.section	.text.ftl_read,"ax",@progbits
	.align	2
	.global	ftl_read
	.type	ftl_read, %function
ftl_read:
	and	w0, w0, 255
	b	zftl_read
	.size	ftl_read, .-ftl_read
	.section	.text.ftl_vendor_read,"ax",@progbits
	.align	2
	.global	ftl_vendor_read
	.type	ftl_vendor_read, %function
ftl_vendor_read:
	mov	x3, x2
	mov	w2, w1
	add	w1, w0, 512
	mov	w0, 2
	b	zftl_read
	.size	ftl_vendor_read, .-ftl_vendor_read
	.section	.text.zftl_vendor_read,"ax",@progbits
	.align	2
	.global	zftl_vendor_read
	.type	zftl_vendor_read, %function
zftl_vendor_read:
	b	ftl_vendor_read
	.size	zftl_vendor_read, .-zftl_vendor_read
	.section	.text.ftl_update_l2p_map,"ax",@progbits
	.align	2
	.global	ftl_update_l2p_map
	.type	ftl_update_l2p_map, %function
ftl_update_l2p_map:
	stp	x29, x30, [sp, -128]!
	add	x29, sp, 0
	stp	x21, x22, [sp, 32]
	mov	x22, x0
	stp	x19, x20, [sp, 16]
	adrp	x0, .LANCHOR94
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	ldrh	w23, [x0, #:lo12:.LANCHOR94]
	ldrb	w0, [x22, 9]
	ldrh	w19, [x22, 12]
	mul	w23, w23, w0
	adrp	x0, .LANCHOR117
	str	x0, [x29, 104]
	ldr	x1, [x0, #:lo12:.LANCHOR117]
	add	x19, x1, x19, lsl 2
	add	x1, x19, x23, sxtw 2
	ldr	w1, [x1, -4]
	cmn	w1, #1
	beq	.L3632
	adrp	x1, .LANCHOR231
	adrp	x0, .LC0
	mov	w2, 1998
	add	x1, x1, :lo12:.LANCHOR231
	add	x0, x0, :lo12:.LC0
	bl	printf
.L3632:
	adrp	x27, .LANCHOR131
	mov	x24, 0
	add	x0, x27, :lo12:.LANCHOR131
	mov	w21, 0
	str	x0, [x29, 96]
.L3633:
	cmp	w24, w23
	blt	.L3639
	adrp	x0, .LANCHOR19
	adrp	x19, .LANCHOR11
	ldr	w0, [x0, #:lo12:.LANCHOR19]
	tbz	x0, 12, .L3640
	ldrh	w1, [x22]
	ldr	x2, [x19, #:lo12:.LANCHOR11]
	ubfiz	x0, x1, 1, 16
	ldrh	w3, [x2, x0]
	adrp	x0, .LC234
	mov	w2, w21
	add	x0, x0, :lo12:.LC234
	bl	printf
.L3640:
	ldrh	w1, [x22]
	ldr	x0, [x19, #:lo12:.LANCHOR11]
	ldp	x23, x24, [sp, 48]
	ldp	x19, x20, [sp, 16]
	strh	w21, [x0, x1, lsl 1]
	ldp	x25, x26, [sp, 64]
	ldp	x21, x22, [sp, 32]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 128
	ret
.L3639:
	ldr	w2, [x19, x24, lsl 2]
	cmn	w2, #1
	beq	.L3634
	ldrb	w20, [x27, #:lo12:.LANCHOR131]
	adrp	x0, .LANCHOR19
	ldr	w0, [x0, #:lo12:.LANCHOR19]
	lsl	w20, w20, 7
	udiv	w20, w2, w20
	and	w20, w20, 65535
	tbz	x0, 12, .L3635
	adrp	x0, .LC231
	mov	w3, w24
	mov	w1, w20
	add	x0, x0, :lo12:.LC231
	bl	printf
.L3635:
	adrp	x25, .LANCHOR111
	adrp	x26, .LC232
	mov	x28, x24
	add	x25, x25, :lo12:.LANCHOR111
	add	x26, x26, :lo12:.LC232
.L3638:
	ldr	w1, [x19, x28, lsl 2]
	cmn	w1, #1
	beq	.L3636
	ldr	x0, [x29, 96]
	ldrb	w2, [x0]
	lsl	w2, w2, 7
	udiv	w1, w1, w2
	cmp	w20, w1, uxth
	bne	.L3636
	ldrb	w0, [x22, 9]
	sdiv	w1, w28, w0
	msub	w0, w1, w0, w28
	add	x0, x22, x0, sxtw 1
	ldrh	w2, [x0, 16]
	ldrh	w0, [x25]
	madd	w2, w2, w0, w1
	mov	x0, x26
	str	w2, [x29, 124]
	ldr	w1, [x19, x28, lsl 2]
	bl	pm_ppa_update_check
	cbz	w0, .L3637
	ldr	x0, [x29, 104]
	mov	w3, w23
	mov	w2, 4
	ldr	x1, [x0, #:lo12:.LANCHOR117]
	adrp	x0, .LC233
	add	x0, x0, :lo12:.LC233
	bl	rknand_print_hex
.L3637:
	ldr	w0, [x19, x28, lsl 2]
	add	w21, w21, 1
	mov	w2, 1
	add	x1, x29, 124
	and	w21, w21, 65535
	bl	pm_log2phys
	mov	w0, -1
	str	w0, [x19, x28, lsl 2]
.L3636:
	add	x28, x28, 1
	cmp	w23, w28
	bgt	.L3638
.L3634:
	add	x24, x24, 1
	b	.L3633
	.size	ftl_update_l2p_map, .-ftl_update_l2p_map
	.section	.text.ftl_alloc_new_data_sblk,"ax",@progbits
	.align	2
	.global	ftl_alloc_new_data_sblk
	.type	ftl_alloc_new_data_sblk, %function
ftl_alloc_new_data_sblk:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	str	x21, [sp, 32]
	ldrh	w21, [x0]
	bl	ftl_update_l2p_map
	bl	pm_flush
	ldrh	w0, [x20]
	mov	w1, 65535
	cmp	w0, w1
	beq	.L3662
	bl	zftl_insert_data_list
.L3662:
	adrp	x19, .LANCHOR12
	ldr	x0, [x19, #:lo12:.LANCHOR12]
	add	x0, x0, 16
	cmp	x20, x0
	mov	x0, x20
	cset	w1, ne
	add	w1, w1, 2
	bl	ftl_open_sblk_init
	ldr	x0, [x19, #:lo12:.LANCHOR12]
	ldr	w0, [x0, 560]
	cmp	w0, w21
	bne	.L3664
	mov	w20, 65535
	cmp	w21, w20
	beq	.L3664
	mov	w1, w21
	adrp	x0, .LC235
	add	x0, x0, :lo12:.LC235
	bl	printf
	ldr	x0, [x19, #:lo12:.LANCHOR12]
	ldr	w0, [x0, 564]
	bl	gc_mark_bad_ppa
	ldr	x0, [x19, #:lo12:.LANCHOR12]
	mov	w1, -1
	str	w20, [x0, 560]
	str	w1, [x0, 564]
.L3664:
	bl	ftl_ext_info_flush
	mov	w0, 0
	bl	ftl_info_flush
	bl	lpa_rebuild_hash
	ldr	x21, [sp, 32]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.size	ftl_alloc_new_data_sblk, .-ftl_alloc_new_data_sblk
	.section	.text.ftl_write_commit,"ax",@progbits
	.align	2
	.global	ftl_write_commit
	.type	ftl_write_commit, %function
ftl_write_commit:
	stp	x29, x30, [sp, -160]!
	adrp	x0, .LANCHOR55
	add	x29, sp, 0
	stp	x23, x24, [sp, 48]
	add	x24, x0, :lo12:.LANCHOR55
	add	x0, x24, 2050
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	str	x0, [x29, 104]
.L3668:
	adrp	x2, .LANCHOR66
	ldrb	w1, [x2, #:lo12:.LANCHOR66]
	cbz	w1, .L3670
	adrp	x3, .LANCHOR65
	adrp	x0, .LANCHOR55
	add	x0, x0, :lo12:.LANCHOR55
	sub	w1, w1, #1
	ldrb	w4, [x3, #:lo12:.LANCHOR65]
	strb	w1, [x2, #:lo12:.LANCHOR66]
	ubfiz	x5, x4, 6, 8
	add	x5, x0, x5
	stp	x4, x5, [x29, 120]
	lsl	x4, x4, 6
	add	x5, x0, x4
	ldrb	w0, [x0, x4]
	strb	w0, [x3, #:lo12:.LANCHOR65]
	adrp	x0, .LANCHOR128
	ldr	w2, [x5, 36]
	mov	x19, x0
	ldr	w1, [x0, #:lo12:.LANCHOR128]
	cmp	w2, w1
	bcc	.L3672
	adrp	x1, .LANCHOR232
	adrp	x0, .LC0
	mov	w2, 604
	add	x1, x1, :lo12:.LANCHOR232
	add	x0, x0, :lo12:.LC0
	bl	printf
.L3672:
	ldr	x0, [x29, 120]
	ldr	w1, [x19, #:lo12:.LANCHOR128]
	add	x0, x24, x0, lsl 6
	ldr	w22, [x0, 36]
	cmp	w22, w1
	bcc	.L3673
	ldr	x0, [x29, 128]
	bl	zbuf_free
	mov	w0, -1
.L3667:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 160
	ret
.L3673:
	ldrb	w21, [x0, 57]
	ldrb	w20, [x0, 56]
	ldr	x26, [x0, 8]
	ldr	x23, [x0, 24]
	adrp	x0, .LANCHOR129
	str	x0, [x29, 112]
	ldrb	w1, [x0, #:lo12:.LANCHOR129]
	cbz	w1, .L3675
	adrp	x0, .LANCHOR182
	ldrb	w19, [x0, #:lo12:.LANCHOR182]
	add	x19, x24, x19, lsl 6
.L3676:
	ldrb	w0, [x19]
	cmp	w0, 255
	bne	.L3677
	ldr	w0, [x19, 36]
	cmp	w22, w0
	bne	.L3675
	ldr	x0, [x19, 8]
	ubfiz	x21, x21, 9, 8
	lsl	w2, w20, 9
	add	x1, x26, x21
	add	x0, x0, x21
	bl	ftl_memcpy
	adrp	x0, .LANCHOR131
	ldr	x2, [x19, 8]
	ldr	x1, [x19, 24]
	ldrb	w0, [x0, #:lo12:.LANCHOR131]
	add	x1, x1, 16
	sub	w0, w0, #2
	lsl	w0, w0, 7
	add	x2, x2, x0, sxtw 2
	mov	w0, 2
	bl	ftl_debug_info_fill
	ldr	x0, [x29, 128]
	bl	zbuf_free
	b	.L3668
.L3677:
	ubfiz	x19, x0, 6, 8
	add	x19, x24, x19
	b	.L3676
.L3675:
	mov	w0, w22
	bl	lpa_hash_get_ppa
	str	w0, [x29, 156]
	cmn	w0, #1
	bne	.L3679
	mov	w2, 0
	add	x1, x29, 156
	mov	w0, w22
	bl	pm_log2phys
.L3679:
	adrp	x27, .LANCHOR12
	ldr	w2, [x29, 156]
	add	x0, x24, 2
	mov	w3, 0
	ldr	x19, [x27, #:lo12:.LANCHOR12]
	mov	x25, 0
	add	x19, x19, 16
.L3681:
	ldr	w1, [x0, 34]
	cmp	w22, w1
	bne	.L3680
	ldrb	w1, [x0]
	tbz	x1, 3, .L3680
	ldr	w2, [x0, 38]
	and	w1, w1, -9
	ldr	x25, [x0, 6]
	mov	w3, 1
	strb	w1, [x0]
.L3680:
	ldr	x1, [x29, 104]
	add	x0, x0, 64
	cmp	x0, x1
	bne	.L3681
	cbz	w3, .L3682
	str	w2, [x29, 156]
.L3682:
	adrp	x28, .LANCHOR131
	str	x28, [x29, 136]
	ldrb	w0, [x28, #:lo12:.LANCHOR131]
	cmp	w20, w0
	bcs	.L3708
	add	w20, w21, w20
	cbz	x25, .L3684
	cbz	w21, .L3685
	lsl	w2, w21, 9
	mov	x1, x25
	mov	x0, x26
	bl	ftl_memcpy
	ldr	x19, [x27, #:lo12:.LANCHOR12]
	add	x19, x19, 48
.L3685:
	ldr	x0, [x29, 136]
	ldrb	w2, [x0, #:lo12:.LANCHOR131]
	cmp	w20, w2
	bcc	.L3686
	ldr	x19, [x27, #:lo12:.LANCHOR12]
	add	x19, x19, 16
.L3708:
	mov	w25, 0
	b	.L3683
.L3686:
	ubfiz	x0, x20, 9, 9
	sub	w2, w2, w20
	add	x1, x25, x0
	lsl	w2, w2, 9
	add	x0, x26, x0
	bl	ftl_memcpy
	b	.L3708
.L3684:
	ldr	w0, [x29, 156]
	cmn	w0, #1
	beq	.L3687
	mov	w0, 1
	bl	buf_alloc
	ldr	w1, [x29, 156]
	mov	x28, x0
	stp	w22, w1, [x0, 36]
	mov	w1, 1
	bl	sblk_read_page
	ldr	x3, [x28, 24]
	ldr	w0, [x3, 4]
	ldr	w25, [x3, 12]
	cmp	w22, w0
	add	w25, w25, 1
	bne	.L3688
	ldr	w0, [x28, 52]
	cmn	w0, #1
	bne	.L3689
.L3688:
	adrp	x0, .LANCHOR31
	mov	w6, 1
	ldr	w1, [x28, 40]
	ldrb	w2, [x0, #:lo12:.LANCHOR31]
	mov	w0, 24
	sub	w0, w0, w2
	lsl	w6, w6, w2
	ldr	x2, [x29, 136]
	sub	w6, w6, #1
	lsl	w7, w6, w0
	ldrb	w4, [x2, #:lo12:.LANCHOR131]
	lsr	w0, w1, w0
	ldr	x2, [x28, 8]
	bic	w1, w1, w7
	and	w0, w0, w6
	bl	flash_read_page_en
	str	w0, [x28, 52]
.L3689:
	ldr	x0, [x28, 24]
	ldr	w0, [x0, 4]
	cmp	w22, w0
	bne	.L3690
	ldr	w0, [x28, 52]
	cmn	w0, #1
	bne	.L3691
.L3690:
	ldr	x1, [x27, #:lo12:.LANCHOR12]
	mov	w3, w22
	ldr	w4, [x28, 52]
	ldr	w2, [x29, 156]
	ldr	w0, [x1, 552]
	add	w0, w0, 1
	str	w0, [x1, 552]
	adrp	x0, .LC236
	add	x0, x0, :lo12:.LC236
	ldrb	w1, [x28, 1]
	bl	printf
	ldr	x1, [x28, 24]
	mov	w3, 4
	adrp	x0, .LC208
	mov	w2, w3
	add	x0, x0, :lo12:.LC208
	bl	rknand_print_hex
.L3691:
	ldr	x0, [x28, 24]
	ldr	w0, [x0, 4]
	cmp	w22, w0
	bne	.L3692
	ldr	w0, [x28, 52]
	cmn	w0, #1
	bne	.L3693
.L3692:
	adrp	x1, .LANCHOR232
	adrp	x0, .LC0
	mov	w2, 696
	add	x1, x1, :lo12:.LANCHOR232
	add	x0, x0, :lo12:.LC0
	bl	printf
.L3693:
	cbz	w21, .L3694
	ldr	w0, [x29, 156]
	lsl	w2, w21, 9
	cmn	w0, #1
	beq	.L3695
	ldr	x1, [x28, 8]
	mov	x0, x26
	bl	ftl_memcpy
.L3696:
	ldr	x19, [x27, #:lo12:.LANCHOR12]
	add	x19, x19, 48
.L3694:
	ldr	x0, [x29, 136]
	ldrb	w2, [x0, #:lo12:.LANCHOR131]
	cmp	w20, w2
	bcc	.L3697
	bls	.L3698
	ldr	x19, [x27, #:lo12:.LANCHOR12]
	add	x19, x19, 16
.L3698:
	cbz	x28, .L3683
	ldrb	w0, [x28, 2]
	mov	x1, x28
	and	w0, w0, -9
	strb	w0, [x28, 2]
	adrp	x0, .LANCHOR62
	add	x0, x0, :lo12:.LANCHOR62
	bl	buf_remove_buf
	mov	x0, x28
	bl	zbuf_free
.L3683:
	ldrh	w0, [x19, 6]
	cbnz	w0, .L3700
	bl	ftl_flush
	mov	x0, x19
	bl	ftl_alloc_new_data_sblk
.L3700:
	mov	x0, x19
	bl	ftl_get_new_free_page
	mov	w10, w0
	ldr	x0, [x29, 120]
	mov	x1, x23
	adrp	x20, .LANCHOR182
	lsl	x8, x0, 6
	add	x7, x24, x8
	ldr	w0, [x7, 32]
	stp	w0, w22, [x23]
	str	w25, [x23, 12]
	ldr	w0, [x29, 156]
	str	w0, [x23, 8]
	ldr	x0, [x29, 136]
	str	wzr, [x1, 16]!
	ldrb	w2, [x0, #:lo12:.LANCHOR131]
	mov	w0, 2
	sub	w2, w2, #2
	lsl	w2, w2, 7
	add	x2, x26, x2, sxtw 2
	bl	ftl_debug_info_fill
	ldr	w0, [x29, 156]
	mov	w1, 10
	stp	w10, w0, [x7, 40]
	mov	w0, -1
	strb	w0, [x24, x8]
	ldrb	w0, [x7, 2]
	orr	w0, w0, w1
	ldrh	w1, [x19, 12]
	strb	w0, [x7, 2]
	ldrh	w0, [x19, 10]
	add	w0, w0, w1
	ldr	x1, [x29, 128]
	sub	w0, w0, #1
	strh	w0, [x7, 48]
	add	x0, x20, :lo12:.LANCHOR182
	bl	buf_add_tail
	ldr	x0, [x29, 112]
	ldrb	w2, [x0, #:lo12:.LANCHOR129]
	add	w2, w2, 1
	and	w2, w2, 255
	strb	w2, [x0, #:lo12:.LANCHOR129]
	adrp	x0, .LANCHOR233
	cmp	w2, 2
	str	wzr, [x0, #:lo12:.LANCHOR233]
	ldrh	w0, [x19, 6]
	bhi	.L3701
	cmp	w0, 1
	bne	.L3671
.L3701:
	ldrb	w1, [x19, 5]
	cmp	w1, 0
	mov	w1, 0
	cset	w4, ne
	cmp	w0, 1
	ldrb	w0, [x20, #:lo12:.LANCHOR182]
	csinc	w4, w2, w4, eq
	mov	w3, w0
.L3705:
	cmp	w1, w4
	bne	.L3706
	strb	w3, [x20, #:lo12:.LANCHOR182]
	and	w1, w1, 255
	ldr	x3, [x29, 112]
	sub	w2, w2, w1
	ubfiz	x0, x0, 6, 8
	add	x0, x24, x0
	strb	w2, [x3, #:lo12:.LANCHOR129]
	bl	sblk_prog_page
	ldrh	w0, [x19, 6]
	cmp	w0, 1
	bne	.L3671
	bl	sblk_wait_write_queue_completed
	bl	ftl_write_completed
	mov	x0, x19
	bl	ftl_write_last_log_page
	mov	x0, x19
	bl	ftl_alloc_new_data_sblk
.L3671:
	adrp	x0, .LANCHOR66
	ldrb	w0, [x0, #:lo12:.LANCHOR66]
	cbnz	w0, .L3668
.L3670:
	bl	ftl_write_completed
	mov	w0, 0
	b	.L3667
.L3697:
	ldr	w0, [x29, 156]
	sub	w2, w2, w20
	lsl	w2, w2, 9
	cmn	w0, #1
	ubfiz	x0, x20, 7, 9
	beq	.L3699
	ldr	x1, [x28, 8]
	lsl	x0, x0, 2
	add	x1, x1, x0
	add	x0, x26, x0
	bl	ftl_memcpy
	b	.L3698
.L3699:
	mov	w1, 0
	add	x0, x26, x0, lsl 2
	bl	ftl_memset
	b	.L3698
.L3706:
	ubfiz	x3, x3, 6, 8
	add	w1, w1, 1
	ldrb	w3, [x24, x3]
	b	.L3705
.L3707:
	lsl	w2, w21, 9
	mov	x28, 0
	mov	w25, 0
.L3695:
	mov	w1, 0
	mov	x0, x26
	bl	ftl_memset
	b	.L3696
.L3687:
	cbnz	w21, .L3707
	mov	w25, 0
	mov	x28, 0
	b	.L3694
	.size	ftl_write_commit, .-ftl_write_commit
	.section	.text.gc_do_copy_back,"ax",@progbits
	.align	2
	.global	gc_do_copy_back
	.type	gc_do_copy_back, %function
gc_do_copy_back:
	stp	x29, x30, [sp, -224]!
	adrp	x0, .LANCHOR84
	add	x29, sp, 0
	ldrb	w0, [x0, #:lo12:.LANCHOR84]
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	cbnz	w0, .L3734
	bl	buf_alloc
	mov	x19, x0
	cbz	x0, .L3733
	adrp	x21, .LANCHOR70
	add	x3, x21, :lo12:.LANCHOR70
	ldrh	w2, [x3, 26]
	mov	w0, w2
	bl	gc_get_src_ppa_from_index
	add	w2, w2, 1
	mov	w22, w0
	str	w22, [x19, 40]
	strh	w2, [x3, 26]
	mov	w1, 1
	mov	x0, x19
	bl	sblk_read_page
	ldr	w0, [x19, 52]
	cmp	w0, 512
	ccmn	w0, #1, 4, ne
	bne	.L3736
	adrp	x1, .LANCHOR234
	adrp	x0, .LC0
	mov	w2, 1032
	add	x1, x1, :lo12:.LANCHOR234
	add	x0, x0, :lo12:.LC0
	bl	printf
.L3736:
	ldr	x0, [x19, 24]
	ldr	w20, [x0, 4]
	mov	w0, w20
	bl	lpa_hash_get_ppa
	str	w0, [x29, 176]
	cmn	w0, #1
	bne	.L3737
	mov	w2, 0
	add	x1, x29, 176
	mov	w0, w20
	bl	pm_log2phys
.L3737:
	ldr	w23, [x29, 176]
	cmp	w22, w23
	bne	.L3738
	adrp	x0, .LANCHOR55
	add	x0, x0, :lo12:.LANCHOR55
	add	x1, x0, 2
	add	x0, x0, 2050
.L3741:
	ldr	w2, [x1, 34]
	cmp	w20, w2
	bne	.L3739
	ldrb	w2, [x1]
	tbz	x2, 1, .L3739
	mov	x0, x19
	bl	zbuf_free
	adrp	x0, .LANCHOR19
	ldr	w0, [x0, #:lo12:.LANCHOR19]
	tbz	x0, 8, .L3733
	add	x21, x21, :lo12:.LANCHOR70
	adrp	x0, .LC237
	mov	w2, w22
	mov	w1, w20
	add	x0, x0, :lo12:.LC237
	ldrh	w3, [x21, 26]
	bl	printf
.L3733:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 224
	ret
.L3739:
	add	x1, x1, 64
	cmp	x1, x0
	bne	.L3741
	adrp	x0, .LANCHOR131
	strb	wzr, [x19, 57]
	str	w20, [x19, 36]
	ldrb	w0, [x0, #:lo12:.LANCHOR131]
	strb	w0, [x19, 56]
	ldr	x0, [x19, 24]
	ldr	w1, [x0]
	str	w1, [x19, 32]
	str	wzr, [x0, 16]
	adrp	x0, .LANCHOR19
	ldr	w0, [x0, #:lo12:.LANCHOR19]
	tbz	x0, 8, .L3742
	mov	w0, w20
	bl	lpa_hash_get_ppa
	add	x1, x21, :lo12:.LANCHOR70
	mov	w3, w0
	mov	w4, w22
	adrp	x0, .LC238
	mov	w2, w23
	add	x0, x0, :lo12:.LC238
	ldrh	w5, [x1, 26]
	mov	w1, w20
	bl	printf
.L3742:
	mov	x0, x19
	bl	ftl_gc_write_buf
	bl	ftl_write_commit
	add	x21, x21, :lo12:.LANCHOR70
	adrp	x0, .LANCHOR110
	ldr	x1, [x0, #:lo12:.LANCHOR110]
	ldr	w0, [x1, 60]
	add	w0, w0, 1
	str	w0, [x1, 60]
	ldrh	w0, [x21, 28]
	add	w0, w0, 1
	strh	w0, [x21, 28]
	b	.L3733
.L3738:
	adrp	x0, .LANCHOR19
	ldr	w0, [x0, #:lo12:.LANCHOR19]
	tbz	x0, 8, .L3743
	add	x21, x21, :lo12:.LANCHOR70
	mov	w0, w20
	bl	lpa_hash_get_ppa
	mov	w3, w0
	mov	w4, w22
	adrp	x0, .LC238
	ldrh	w5, [x21, 26]
	mov	w2, w23
	mov	w1, w20
	add	x0, x0, :lo12:.LC238
	bl	printf
.L3743:
	mov	x0, x19
	bl	zbuf_free
	b	.L3733
.L3734:
	adrp	x2, .LANCHOR12
	adrp	x1, .LANCHOR79
	stp	x1, x2, [x29, 136]
	ldr	x26, [x2, #:lo12:.LANCHOR12]
	ldrb	w3, [x1, #:lo12:.LANCHOR79]
	add	x26, x26, 80
	ldrb	w0, [x26, 9]
	and	w20, w0, 65535
	cmp	w3, w20
	bhi	.L3798
	cmp	w20, 2
	mov	w21, 2
	csel	w21, w20, w21, ls
	and	w21, w21, 65535
.L3744:
	adrp	x1, .LANCHOR78
	str	x1, [x29, 120]
	ldrb	w19, [x1, #:lo12:.LANCHOR78]
	cmp	w19, 3
	bne	.L3745
	adrp	x1, .LANCHOR35
	ldrb	w1, [x1, #:lo12:.LANCHOR35]
	cbz	w1, .L3746
	adrp	x1, .LANCHOR70
	add	x1, x1, :lo12:.LANCHOR70
	ldrh	w22, [x1, 2106]
	adrp	x1, .LANCHOR124
	ldrb	w1, [x1, #:lo12:.LANCHOR124]
	sdiv	w2, w22, w0
	and	w25, w2, 65535
	cbz	w1, .L3747
	adrp	x1, .LANCHOR235
	add	x1, x1, :lo12:.LANCHOR235
	ldrh	w1, [x1, w2, sxtw 1]
	cmp	w1, 0
	cset	w19, ne
.L3865:
	add	w19, w19, 1
.L3748:
	msub	w20, w20, w25, w22
	and	w20, w20, 65535
.L3749:
	adrp	x1, .LANCHOR85
	mul	w11, w19, w21
	adrp	x10, .LANCHOR235
	sxtw	x13, w25
	ldrh	w5, [x1, #:lo12:.LANCHOR85]
	adrp	x1, .LANCHOR224
	add	x10, x10, :lo12:.LANCHOR235
	mov	w2, 0
	mul	w0, w5, w0
	ldrb	w5, [x1, #:lo12:.LANCHOR224]
	sub	w5, w0, w5
	adrp	x0, .LANCHOR124
	ldrb	w12, [x0, #:lo12:.LANCHOR124]
	adrp	x0, .LANCHOR160
	ldr	x8, [x0, #:lo12:.LANCHOR160]
	adrp	x0, .LANCHOR70
	add	x6, x0, :lo12:.LANCHOR70
	ldrh	w14, [x6, 24]
.L3753:
	cmp	w2, w11
	bge	.L3806
	add	w4, w22, w2
	cmp	w4, w5
	blt	.L3754
	cbz	w12, .L3806
	ldrh	w0, [x10, x13, lsl 1]
	cmp	w0, w25
	bcc	.L3755
.L3806:
	mov	w23, 1
	b	.L3751
.L3798:
	mov	w21, 1
	b	.L3744
.L3747:
	adrp	x1, .LANCHOR217
	ldrb	w1, [x1, #:lo12:.LANCHOR217]
	cbz	w1, .L3800
	sub	w1, w25, #62
	and	w1, w1, 65535
	cmp	w1, 2159
	bhi	.L3801
	udiv	w19, w25, w19
	add	w19, w19, w19, lsl 1
	sub	w19, w25, w19
	and	w19, w19, 65535
	cmp	w19, 0
	cset	w19, eq
	b	.L3865
.L3800:
	mov	w19, 1
	b	.L3748
.L3801:
	mov	w19, 2
	b	.L3748
.L3746:
	adrp	x1, .LANCHOR83
	ldrb	w1, [x1, #:lo12:.LANCHOR83]
	cbz	w1, .L3750
	adrp	x1, .LANCHOR70
	add	x1, x1, :lo12:.LANCHOR70
	add	w20, w0, w0, lsl 1
	ldrh	w22, [x1, 2106]
	adrp	x1, .LANCHOR36
	ldrb	w1, [x1, #:lo12:.LANCHOR36]
	sdiv	w20, w22, w20
	and	w25, w20, 65535
	mul	w20, w0, w20
	sub	w20, w20, w20, lsl 2
	add	w20, w20, w22
	sdiv	w20, w20, w19
	and	w20, w20, 65535
	cbz	w1, .L3749
	add	w3, w25, w25, lsl 1
	and	w25, w3, 65535
	b	.L3749
.L3750:
	adrp	x1, .LANCHOR70
	add	x1, x1, :lo12:.LANCHOR70
	adrp	x2, .LANCHOR236
	add	x2, x2, :lo12:.LANCHOR236
	ldrh	w4, [x1, 2106]
	sdiv	w1, w4, w0
	ldrh	w23, [x2, w1, sxtw 1]
	msub	w20, w20, w1, w4
	and	w20, w20, 65535
	lsr	w25, w23, 3
	and	w23, w23, 7
	cmp	w23, 1
	madd	w22, w25, w0, w20
	add	w22, w22, w22, lsl 1
	and	w22, w22, 65535
	beq	.L3749
.L3751:
	mul	w0, w19, w21
	stp	wzr, w0, [x29, 152]
	ubfiz	w0, w21, 1, 15
	str	w0, [x29, 132]
	msub	w0, w0, w19, w22
	and	w0, w0, 65535
	str	w0, [x29, 128]
	ldrh	w0, [x29, 128]
	str	x0, [x29, 112]
	adrp	x0, .LANCHOR55
	add	x0, x0, :lo12:.LANCHOR55
	str	x0, [x29, 104]
.L3756:
	ldp	w0, w1, [x29, 152]
	ldrh	w24, [x29, 152]
	and	w0, w0, 65535
	str	w0, [x29, 168]
	cmp	w0, w1
	blt	.L3780
	ldr	x0, [x29, 120]
	ldrb	w0, [x0, #:lo12:.LANCHOR78]
	cmp	w0, 3
	add	x0, x29, 176
	bne	.L3781
	adrp	x1, .LANCHOR35
	ldrb	w1, [x1, #:lo12:.LANCHOR35]
	cbz	w1, .L3782
	ldr	w2, [x29, 156]
	mov	w1, 0
	sub	w2, w2, #1
.L3783:
	cmp	w1, w2
	blt	.L3784
.L3869:
	ldr	x0, [x0, w2, sxtw 3]
	mov	w1, -1
	strb	w1, [x0]
	mul	w1, w21, w19
	ldr	x0, [x29, 176]
	bl	sblk_prog_page
	b	.L3785
.L3745:
	adrp	x1, .LANCHOR80
	ldrb	w1, [x1, #:lo12:.LANCHOR80]
	cbnz	w1, .L3752
	adrp	x1, .LANCHOR70
	add	x1, x1, :lo12:.LANCHOR70
	mov	w19, 1
	ldrh	w22, [x1, 2106]
	sdiv	w25, w22, w0
	msub	w20, w20, w25, w22
	and	w20, w20, 65535
	b	.L3749
.L3752:
	adrp	x1, .LANCHOR70
	add	x1, x1, :lo12:.LANCHOR70
	mov	w19, 2
	ldrh	w22, [x1, 2106]
	sdiv	w25, w22, w0
	msub	w20, w20, w25, w22
	and	w20, w20, 65535
	b	.L3749
.L3755:
	tbz	x2, 0, .L3806
.L3754:
	sbfiz	x4, x4, 2, 32
	ldr	w0, [x8, x4]
	cmn	w0, #1
	bne	.L3757
	ldrh	w7, [x6, 26]
	cmp	w7, w14
	bcs	.L3733
	cbz	w12, .L3758
	ldrh	w0, [x10, x13, lsl 1]
	cmp	w0, w25
	bcs	.L3758
	tbz	x2, 0, .L3758
	ubfiz	x0, x0, 2, 16
	ldr	w0, [x8, x0]
.L3866:
	str	w0, [x8, x4]
.L3757:
	add	w2, w2, 1
	and	w2, w2, 65535
	b	.L3753
.L3758:
	mov	w0, w7
	bl	gc_get_src_ppa_from_index
	add	w7, w7, 1
	strh	w7, [x6, 26]
	b	.L3866
.L3780:
	ldr	w0, [x29, 168]
	add	w0, w22, w0
	str	w0, [x29, 172]
	sxtw	x0, w0
	str	x0, [x29, 160]
	adrp	x0, .LANCHOR82
	ldr	x1, [x29, 160]
	ldr	x0, [x0, #:lo12:.LANCHOR82]
	ldrb	w0, [x0, x1]
	cmp	w0, 255
	bne	.L3760
	mov	w0, 0
	bl	buf_alloc
	mov	x27, x0
	cbnz	x0, .L3761
	bl	sblk_wait_write_queue_completed
	bl	ftl_write_completed
	bl	gc_write_completed
	bl	gc_free_temp_buf
	mov	w0, 0
	bl	buf_alloc
	mov	x27, x0
	cbz	x0, .L3733
.L3761:
	adrp	x0, .LANCHOR82
	ldr	x2, [x29, 160]
	ldrb	w1, [x27, 1]
	ldr	x0, [x0, #:lo12:.LANCHOR82]
	strb	w1, [x0, x2]
	adrp	x0, .LANCHOR70
	add	x1, x0, :lo12:.LANCHOR70
	strb	w23, [x27, 61]
	ldrb	w0, [x1, 7]
	add	w0, w0, 1
	strb	w0, [x1, 7]
	add	w0, w24, w22
	strh	w0, [x27, 48]
	adrp	x0, .LANCHOR85
	ldr	w1, [x29, 172]
	ldrh	w6, [x0, #:lo12:.LANCHOR85]
	adrp	x0, .LANCHOR224
	ldrb	w5, [x0, #:lo12:.LANCHOR224]
	ldrb	w0, [x26, 9]
	mul	w0, w0, w6
	sub	w0, w0, w5
	cmp	w1, w0
	blt	.L3762
	adrp	x1, .LANCHOR124
	ldrb	w1, [x1, #:lo12:.LANCHOR124]
	cbz	w1, .L3763
	adrp	x1, .LANCHOR235
	add	x1, x1, :lo12:.LANCHOR235
	ldrh	w1, [x1, w25, sxtw 1]
	cmp	w1, w25
	bcs	.L3763
	tbnz	x24, 0, .L3762
.L3763:
	adrp	x1, .LANCHOR159
	ldr	w3, [x29, 172]
	mov	w2, -1
	cmp	w5, 2
	ldr	x1, [x1, #:lo12:.LANCHOR159]
	str	w2, [x1, w3, sxtw 2]
	bne	.L3764
	cmp	w3, w0
	adrp	x28, .LANCHOR221
	bne	.L3765
	ldrh	w2, [x28, #:lo12:.LANCHOR221]
	ldr	x0, [x27, 8]
	bl	ftl_memcpy
	adrp	x0, .LANCHOR131
	mov	w1, 0
	ldrb	w2, [x0, #:lo12:.LANCHOR131]
	ldr	x0, [x27, 24]
	lsl	w2, w2, 1
	bl	ftl_memset
	ldr	x6, [x27, 24]
	mov	w0, 15555
	movk	w0, 0xf55f, lsl 16
	ldrh	w1, [x28, #:lo12:.LANCHOR221]
	str	w0, [x6]
	ldr	x0, [x27, 8]
	bl	js_hash
	str	w0, [x6, 4]
	ldr	x0, [x29, 144]
	ldr	x0, [x0, #:lo12:.LANCHOR12]
	ldr	w0, [x0, 132]
	stp	w0, wzr, [x6, 8]
.L3766:
	ldr	x0, [x27, 24]
	str	wzr, [x0, 16]
.L3760:
	adrp	x0, .LANCHOR82
	ldrsw	x2, [x29, 168]
	add	x4, x29, 176
	ldr	x1, [x0, #:lo12:.LANCHOR82]
	ldr	x0, [x29, 160]
	ldrb	w5, [x1, x0]
	adrp	x0, .LANCHOR55
	add	x6, x0, :lo12:.LANCHOR55
	mov	x7, x5
	ubfiz	x0, x5, 6, 8
	add	x0, x6, x0
	add	x6, x6, x5, lsl 6
	str	x0, [x4, x2, lsl 3]
	mov	w0, 2
	strh	w0, [x6, 50]
	ldr	x0, [x29, 120]
	strb	w23, [x6, 61]
	ldrb	w0, [x0, #:lo12:.LANCHOR78]
	cmp	w0, 3
	bne	.L3771
	adrp	x8, .LANCHOR35
	ldrb	w8, [x8, #:lo12:.LANCHOR35]
	cbz	w8, .L3772
	adrp	x0, .LANCHOR124
	and	w8, w24, 1
	add	w10, w8, w25
	ldrb	w0, [x0, #:lo12:.LANCHOR124]
	cbz	w0, .L3773
	adrp	x6, .LANCHOR235
	add	x6, x6, :lo12:.LANCHOR235
	ldrh	w6, [x6, w25, sxtw 1]
	cmp	w6, w25
	bcs	.L3773
	cmp	w8, 0
	csel	w10, w10, w6, eq
.L3773:
	adrp	x0, .LANCHOR55
	add	x6, x0, :lo12:.LANCHOR55
	add	x5, x6, x5, lsl 6
	udiv	w6, w24, w19
	add	w6, w6, w20
	add	x6, x26, x6, sxtw 1
	ldrh	w0, [x6, 16]
	adrp	x6, .LANCHOR111
	ldrh	w6, [x6, #:lo12:.LANCHOR111]
	madd	w0, w0, w6, w10
	orr	w0, w0, 50331648
	str	w0, [x5, 40]
.L3778:
	adrp	x0, .LANCHOR55
	sbfiz	x7, x7, 6, 32
	add	x0, x0, :lo12:.LANCHOR55
	add	x0, x0, x7
	ldrh	w5, [x0, 48]
	ldr	w6, [x0, 40]
	adrp	x0, .LANCHOR161
	ldr	x0, [x0, #:lo12:.LANCHOR161]
	str	w6, [x0, x5, lsl 2]
	b	.L3797
.L3765:
	ldr	x2, [x29, 136]
	ldrh	w0, [x28, #:lo12:.LANCHOR221]
	ldrb	w28, [x2, #:lo12:.LANCHOR79]
	mul	w28, w28, w6
	lsl	w28, w28, 2
	sub	w28, w28, w0
	and	x0, x0, 65532
	add	x1, x1, x0
	ldr	x0, [x27, 8]
	mov	w2, w28
	bl	ftl_memcpy
	adrp	x0, .LANCHOR131
	mov	w1, 0
	ldrb	w2, [x0, #:lo12:.LANCHOR131]
	ldr	x0, [x27, 24]
	lsl	w2, w2, 1
	bl	ftl_memset
	ldr	x6, [x27, 24]
	mov	w0, 15555
	movk	w0, 0xf55f, lsl 16
	mov	w1, w28
	str	w0, [x6]
	ldr	x0, [x27, 8]
	bl	js_hash
	str	w0, [x6, 4]
	ldr	x0, [x29, 144]
	ldr	x0, [x0, #:lo12:.LANCHOR12]
	ldr	w0, [x0, 132]
	str	w0, [x6, 8]
	mov	w0, 1
	str	w0, [x6, 12]
	b	.L3766
.L3764:
	ldr	x0, [x29, 136]
	ldrb	w2, [x0, #:lo12:.LANCHOR79]
	ldr	x0, [x27, 8]
	mul	w2, w2, w6
	lsl	w2, w2, 2
	bl	ftl_memcpy
	ldr	x1, [x29, 136]
	adrp	x0, .LANCHOR85
	ldrh	w0, [x0, #:lo12:.LANCHOR85]
	ldrb	w1, [x1, #:lo12:.LANCHOR79]
	mul	w0, w0, w1
	adrp	x1, .LANCHOR131
	ldrb	w1, [x1, #:lo12:.LANCHOR131]
	lsl	w2, w0, 2
	cmp	w1, w0, lsr 6
	bge	.L3767
	adrp	x1, .LANCHOR221
	ldrh	w1, [x1, #:lo12:.LANCHOR221]
	sub	w2, w1, w2
.L3767:
	adrp	x1, .LANCHOR160
	ldr	x5, [x27, 8]
	ldr	x1, [x1, #:lo12:.LANCHOR160]
	add	x0, x5, x0, sxtw 2
	bl	ftl_memcpy
	adrp	x0, .LANCHOR131
	mov	w1, 0
	ldrb	w2, [x0, #:lo12:.LANCHOR131]
	ldr	x0, [x27, 24]
	lsl	w2, w2, 1
	bl	ftl_memset
	ldr	x6, [x27, 24]
	mov	w0, 15555
	movk	w0, 0xf55f, lsl 16
	str	w0, [x6]
	adrp	x0, .LANCHOR85
	ldrh	w1, [x0, #:lo12:.LANCHOR85]
	ldr	x0, [x29, 136]
	ldrb	w0, [x0, #:lo12:.LANCHOR79]
	mul	w1, w1, w0
	ldr	x0, [x27, 8]
	lsl	w1, w1, 2
	bl	js_hash
	str	w0, [x6, 4]
	ldr	x0, [x29, 144]
	ldr	x0, [x0, #:lo12:.LANCHOR12]
	ldr	w0, [x0, 132]
	str	w0, [x6, 8]
	b	.L3766
.L3762:
	ldr	x0, [x29, 160]
	mov	w1, 1
	lsl	x28, x0, 2
	adrp	x0, .LANCHOR160
	ldr	x0, [x0, #:lo12:.LANCHOR160]
	ldr	w0, [x0, x28]
	str	w0, [x27, 40]
	mov	x0, x27
	bl	sblk_read_page
	ldr	w0, [x27, 52]
	cmp	w0, 512
	ccmn	w0, #1, 4, ne
	bne	.L3769
	adrp	x0, .LANCHOR74
	ldrh	w2, [x0, #:lo12:.LANCHOR74]
	adrp	x0, .LANCHOR31
	ldrb	w1, [x0, #:lo12:.LANCHOR31]
	mov	w0, 24
	sub	w0, w0, w1
	sub	w1, w0, w2
	mov	w0, 1
	lsl	w0, w0, w1
	ldr	w1, [x27, 40]
	sub	w0, w0, #1
	lsr	w1, w1, w2
	and	w0, w0, w1
	adrp	x1, .LANCHOR75
	ldrb	w2, [x1, #:lo12:.LANCHOR75]
	mov	x1, 0
	udiv	w0, w0, w2
	bl	ftl_sblk_dump
	ldr	w0, [x27, 52]
	cmp	w0, 512
	ccmn	w0, #1, 4, ne
	bne	.L3769
	ldr	x0, [x27, 24]
	mov	w1, -1
	str	w1, [x0, 4]
	ldr	w0, [x27, 52]
	cmp	w0, 512
	ccmp	w0, w1, 4, ne
	bne	.L3769
	adrp	x1, .LANCHOR234
	adrp	x0, .LC0
	mov	w2, 1223
	add	x1, x1, :lo12:.LANCHOR234
	add	x0, x0, :lo12:.LC0
	bl	printf
.L3769:
	ldr	x0, [x27, 24]
	adrp	x1, .LANCHOR128
	ldr	w1, [x1, #:lo12:.LANCHOR128]
	ldr	w2, [x0, 4]
	cmp	w2, w1
	bcc	.L3770
	mov	w1, -1
	str	w1, [x0, 4]
.L3770:
	adrp	x1, .LANCHOR159
	ldr	w2, [x0, 4]
	ldr	x1, [x1, #:lo12:.LANCHOR159]
	str	w2, [x1, x28]
	ldr	w1, [x27, 40]
	str	w1, [x0, 8]
	b	.L3766
.L3772:
	udiv	w0, w24, w0
	adrp	x7, .LANCHOR36
	ldrb	w7, [x7, #:lo12:.LANCHOR36]
	cbz	w7, .L3775
	add	w7, w0, w20
	adrp	x8, .LANCHOR111
	add	x7, x26, x7, sxtw 1
	add	w0, w0, w0, lsl 1
	ldrh	w8, [x8, #:lo12:.LANCHOR111]
	sub	w0, w24, w0
	ldrh	w7, [x7, 16]
	madd	w7, w7, w8, w25
	add	w0, w7, w0, uxth
.L3870:
	str	w0, [x6, 40]
	ldr	x0, [x29, 104]
	add	x5, x0, x5, lsl 6
	adrp	x0, .LANCHOR161
	ldr	x6, [x0, #:lo12:.LANCHOR161]
	mov	w0, 3
	ldrh	w7, [x5, 48]
	udiv	w0, w24, w0
	ldr	w5, [x5, 40]
	add	w0, w0, w0, lsl 1
	sub	w0, w24, w0
	and	w0, w0, 65535
	add	w0, w0, 1
	orr	w0, w5, w0, lsl 24
	str	w0, [x6, x7, lsl 2]
.L3797:
	adrp	x0, .LANCHOR124
	ldrb	w0, [x0, #:lo12:.LANCHOR124]
	cbz	w0, .L3779
	adrp	x0, .LANCHOR235
	add	x0, x0, :lo12:.LANCHOR235
	ldrh	w0, [x0, w25, sxtw 1]
	cmp	w0, w25
	bcs	.L3779
	tbz	x24, 0, .L3779
	ldr	x3, [x29, 160]
	mov	w0, -1
	strb	w0, [x1, x3]
	ldrh	w1, [x29, 128]
	ldr	x0, [x4, x2, lsl 3]
	ldr	x2, [x29, 112]
	strh	w1, [x0, 48]
	ldrb	w1, [x0, 1]
	adrp	x0, .LANCHOR82
	ldr	x0, [x0, #:lo12:.LANCHOR82]
	strb	w1, [x0, x2]
	adrp	x0, .LANCHOR160
	ldr	w2, [x29, 172]
	mov	w1, -1
	ldr	x0, [x0, #:lo12:.LANCHOR160]
	str	w1, [x0, w2, sxtw 2]
.L3779:
	ldr	w0, [x29, 152]
	add	w0, w0, 1
	str	w0, [x29, 152]
	b	.L3756
.L3775:
	add	w0, w0, w20
	adrp	x7, .LANCHOR111
	add	x0, x26, x0, sxtw 1
	ldrh	w7, [x7, #:lo12:.LANCHOR111]
	ldrh	w0, [x0, 16]
	madd	w0, w0, w7, w25
	b	.L3870
.L3771:
	cmp	w0, 2
	bne	.L3778
	adrp	x0, .LANCHOR80
	adrp	x5, .LANCHOR111
	ldrb	w0, [x0, #:lo12:.LANCHOR80]
	cbnz	w0, .L3777
	ldr	w0, [x29, 168]
	ldrh	w5, [x5, #:lo12:.LANCHOR111]
	add	w27, w20, w0
	add	x27, x26, x27, sxtw 1
	ldrh	w0, [x27, 16]
	madd	w0, w0, w5, w25
.L3867:
	orr	w0, w0, 33554432
	str	w0, [x6, 40]
	b	.L3778
.L3777:
	add	w0, w20, w24, lsr 1
	ldrh	w5, [x5, #:lo12:.LANCHOR111]
	add	x0, x26, x0, sxtw 1
	ldrh	w0, [x0, 16]
	madd	w0, w0, w5, w25
	and	w5, w24, 1
	add	w0, w0, w5
	b	.L3867
.L3784:
	ldr	x4, [x0, w1, sxtw 3]
	add	w1, w1, 1
	ldr	x5, [x0, w1, sxtw 3]
	and	w1, w1, 65535
	ldrb	w5, [x5, 1]
	strb	w5, [x4]
	b	.L3783
.L3782:
	adrp	x1, .LANCHOR83
	ldrb	w2, [x1, #:lo12:.LANCHOR83]
	ldr	x1, [x29, 176]
	cbz	w2, .L3786
.L3789:
	strb	wzr, [x1, 60]
	b	.L3788
.L3786:
	cmp	w23, 1
	bne	.L3787
	mov	w2, 9
.L3868:
	strb	w2, [x1, 60]
.L3788:
	mov	w2, w21
	add	x1, x0, 24
	bl	sblk_xlc_prog_pages
.L3785:
	adrp	x0, .LANCHOR83
	ldrb	w0, [x0, #:lo12:.LANCHOR83]
	cbz	w0, .L3794
	add	w21, w21, w21, lsl 1
	and	w21, w21, 65535
.L3795:
	adrp	x0, .LANCHOR110
	ldr	x1, [x0, #:lo12:.LANCHOR110]
	ldr	w0, [x1, 52]
	add	w0, w0, w21
	str	w0, [x1, 52]
	adrp	x0, .LANCHOR70
	add	x25, x0, :lo12:.LANCHOR70
	ldrh	w0, [x25, 2106]
	add	w21, w21, w0
	adrp	x0, .LANCHOR85
	and	w21, w21, 65535
	strh	w21, [x25, 2106]
	ldrh	w0, [x0, #:lo12:.LANCHOR85]
	ldrb	w1, [x26, 9]
	mul	w0, w0, w1
	cmp	w21, w0
	blt	.L3796
	ldr	x0, [x29, 144]
	ldr	x0, [x0, #:lo12:.LANCHOR12]
	strh	wzr, [x0, 86]
.L3796:
	bl	gc_write_completed
	b	.L3733
.L3787:
	cmp	w23, 2
	bne	.L3789
	mov	w2, 13
	b	.L3868
.L3781:
	adrp	x1, .LANCHOR80
	ldrb	w1, [x1, #:lo12:.LANCHOR80]
	cbz	w1, .L3807
	adrp	x1, .LANCHOR81
	ldrb	w1, [x1, #:lo12:.LANCHOR81]
	cbnz	w1, .L3791
.L3790:
	ldr	w2, [x29, 156]
	sub	w2, w2, #1
.L3792:
	cmp	w1, w2
	bge	.L3869
	ldr	x4, [x0, w1, sxtw 3]
	add	w1, w1, 1
	ldr	x5, [x0, w1, sxtw 3]
	and	w1, w1, 65535
	ldrb	w5, [x5, 1]
	strb	w5, [x4]
	b	.L3792
.L3807:
	mov	w1, 0
	b	.L3790
.L3791:
	mov	w1, w21
	bl	sblk_3d_mlc_prog_pages
	b	.L3785
.L3794:
	adrp	x0, .LANCHOR80
	ldrb	w0, [x0, #:lo12:.LANCHOR80]
	cbnz	w0, .L3808
	adrp	x0, .LANCHOR35
	ldrb	w0, [x0, #:lo12:.LANCHOR35]
	cbz	w0, .L3795
	adrp	x0, .LANCHOR124
	ldrh	w1, [x29, 156]
	ldrb	w0, [x0, #:lo12:.LANCHOR124]
	cbz	w0, .L3809
	adrp	x0, .LANCHOR235
	add	x0, x0, :lo12:.LANCHOR235
	ldrh	w0, [x0, w25, sxtw 1]
	cmp	w0, w25
	csel	w21, w21, w1, cc
	b	.L3795
.L3808:
	ldr	w21, [x29, 132]
	b	.L3795
.L3809:
	mov	w21, w1
	b	.L3795
	.size	gc_do_copy_back, .-gc_do_copy_back
	.section	.text.zftl_do_gc,"ax",@progbits
	.align	2
	.global	zftl_do_gc
	.type	zftl_do_gc, %function
zftl_do_gc:
	sub	sp, sp, #144
	adrp	x1, .LANCHOR107
	stp	x29, x30, [sp, 16]
	add	x29, sp, 16
	ldrh	w1, [x1, #:lo12:.LANCHOR107]
	stp	x21, x22, [sp, 48]
	adrp	x22, .LANCHOR103
	stp	x19, x20, [sp, 32]
	adrp	x20, .LANCHOR156
	stp	x23, x24, [sp, 64]
	adrp	x23, .LANCHOR12
	stp	x25, x26, [sp, 80]
	ldrh	w21, [x22, #:lo12:.LANCHOR103]
	ldrb	w2, [x20, #:lo12:.LANCHOR156]
	stp	x27, x28, [sp, 96]
	add	w21, w1, w21
	ldr	x26, [x23, #:lo12:.LANCHOR12]
	cmp	w2, 6
	bhi	.L3988
	mov	w25, w0
	and	w21, w21, 65535
	adrp	x0, .L3874
	add	x0, x0, :lo12:.L3874
	ldrh	w0, [x0,w2,uxtw #1]
	adr	x2, .Lrtx3874
	add	x0, x2, w0, sxth #2
	br	x0
.Lrtx3874:
	.section	.rodata.zftl_do_gc,"a",@progbits
	.align	0
	.align	2
.L3874:
	.2byte	(.L3873 - .Lrtx3874) / 4
	.2byte	(.L3875 - .Lrtx3874) / 4
	.2byte	(.L3876 - .Lrtx3874) / 4
	.2byte	(.L3877 - .Lrtx3874) / 4
	.2byte	(.L3878 - .Lrtx3874) / 4
	.2byte	(.L3879 - .Lrtx3874) / 4
	.2byte	(.L3880 - .Lrtx3874) / 4
	.section	.text.zftl_do_gc
.L3879:
	adrp	x19, .LANCHOR70
	add	x24, x19, :lo12:.LANCHOR70
	mov	w22, 0
.L3881:
	bl	gc_check_data_one_wl
	cbz	w0, .L3984
	ldr	x0, [x23, #:lo12:.LANCHOR12]
	add	x19, x19, :lo12:.LANCHOR70
	strh	wzr, [x19, 56]
	ldrh	w0, [x0, 80]
	bl	ftl_free_sblk
	adrp	x2, .LANCHOR110
	ldr	x1, [x23, #:lo12:.LANCHOR12]
	mov	w0, -1
	ldr	x2, [x2, #:lo12:.LANCHOR110]
	strh	w0, [x1, 80]
	strh	w0, [x2, 126]
	strh	w0, [x1, 130]
	ldr	x0, [x19, 8]
	bl	zbuf_free
	strb	wzr, [x20, #:lo12:.LANCHOR156]
	str	xzr, [x19, 8]
	b	.L4074
.L3873:
	adrp	x0, .LANCHOR105
	adrp	x27, .LANCHOR97
	ldrh	w3, [x26, 80]
	ldrh	w22, [x0, #:lo12:.LANCHOR105]
	adrp	x0, .LANCHOR99
	ldrh	w24, [x27, #:lo12:.LANCHOR97]
	ldrh	w2, [x0, #:lo12:.LANCHOR99]
	add	w22, w1, w22
	stp	x0, x27, [x29, 112]
	and	w22, w22, 65535
	add	w24, w24, w2
	mov	w2, 65535
	and	w24, w24, 65535
	cmp	w3, w2
	beq	.L3882
	cbnz	w25, .L3883
	adrp	x0, .LANCHOR86
	ldrh	w0, [x0, #:lo12:.LANCHOR86]
	cmp	w21, w0, lsl 1
	blt	.L3883
.L3988:
	mov	w19, 16
	b	.L3871
.L3883:
	adrp	x5, .LANCHOR96
	adrp	x0, .LANCHOR92
	add	x0, x0, :lo12:.LANCHOR92
	adrp	x25, .LANCHOR84
	ldrh	w1, [x5, #:lo12:.LANCHOR96]
	add	w1, w1, 1
	and	w1, w1, 65535
	strh	w1, [x5, #:lo12:.LANCHOR96]
	bl	_list_get_gc_head_node
	and	w3, w0, 65535
	mov	w1, 65535
	cmp	w3, w1
	beq	.L3884
	adrp	x4, .LANCHOR11
	ubfiz	x3, x3, 1, 16
	adrp	x1, .LANCHOR157
	mov	x19, x1
	ldr	x4, [x4, #:lo12:.LANCHOR11]
	ldr	w2, [x1, #:lo12:.LANCHOR157]
	add	w2, w2, 1
	str	w2, [x1, #:lo12:.LANCHOR157]
	ldrh	w3, [x4, x3]
	adrp	x4, .LANCHOR94
	ldrh	w4, [x4, #:lo12:.LANCHOR94]
	cmp	w4, w3
	bcs	.L3885
	adrp	x1, .LANCHOR8
	ldrh	w1, [x1, #:lo12:.LANCHOR8]
	cmp	w2, w1, lsr 4
	bls	.L3884
	adrp	x1, .LANCHOR100
	ldrh	w1, [x1, #:lo12:.LANCHOR100]
	cmp	w1, w3
	bls	.L3884
.L3885:
	ldrb	w2, [x25, #:lo12:.LANCHOR84]
	mov	w1, 0
	bl	gc_add_sblk
	cbz	w0, .L3886
	mov	w0, 1
	str	wzr, [x19, #:lo12:.LANCHOR157]
	strb	w0, [x20, #:lo12:.LANCHOR156]
	b	.L3988
.L3884:
	strh	wzr, [x5, #:lo12:.LANCHOR96]
.L3886:
	cmp	w22, 15
	bls	.L3990
	adrp	x0, .LANCHOR91
	ldrh	w1, [x0, #:lo12:.LANCHOR91]
	adrp	x0, .LANCHOR101
	ldrh	w0, [x0, #:lo12:.LANCHOR101]
	cmp	w1, w0
	bhi	.L3990
	cmp	w24, 0
	cset	w19, eq
	add	w19, w19, 1
.L3887:
	adrp	x0, .LANCHOR19
	ldr	w0, [x0, #:lo12:.LANCHOR19]
	tbz	x0, 8, .L3888
	ldr	x0, [x23, #:lo12:.LANCHOR12]
	mov	w4, w22
	ldrb	w2, [x25, #:lo12:.LANCHOR84]
	mov	w3, w21
	mov	w1, 2807
	ldrh	w7, [x0, 122]
	ldrh	w6, [x0, 120]
	ldrh	w5, [x0, 124]
	ldrh	w0, [x26, 80]
	str	w0, [sp]
	adrp	x0, .LC239
	add	x0, x0, :lo12:.LC239
	bl	printf
.L3888:
	ldrb	w0, [x25, #:lo12:.LANCHOR84]
	mov	w2, 1
	mov	w1, w19
	bl	gc_search_src_blk
	cmp	w0, 0
	ble	.L3889
.L3890:
	mov	w0, 1
.L4076:
	strb	w0, [x20, #:lo12:.LANCHOR156]
	b	.L3988
.L3990:
	mov	w19, 2
	b	.L3887
.L3889:
	ldrb	w0, [x25, #:lo12:.LANCHOR84]
	mov	w2, 1
	mov	w1, 3
	bl	gc_search_src_blk
	cmp	w0, 0
	bgt	.L3890
	b	.L3988
.L3882:
	cmp	w25, 1
	bne	.L3892
	adrp	x0, .LANCHOR110
	ldr	x0, [x0, #:lo12:.LANCHOR110]
	ldrh	w0, [x0, 150]
	cbz	w0, .L3893
	cmp	w1, 8
	bls	.L3893
	bl	gc_ink_check_sblk
.L3893:
	bl	gc_scan_static_data
	adrp	x26, .LANCHOR84
	ldr	x0, [x23, #:lo12:.LANCHOR12]
	ldrh	w0, [x0, 122]
	cbz	w0, .L3894
.L3895:
	mov	w0, 1
	strb	w0, [x26, #:lo12:.LANCHOR84]
	b	.L4076
.L3894:
	bl	gc_static_wearleveling
	mov	w19, w0
	cbnz	w0, .L3895
	adrp	x27, .LANCHOR158
	cbz	w22, .L3896
	cmp	w21, w24
	adrp	x1, .LANCHOR98
	bcs	.L3897
	ldrh	w0, [x1, #:lo12:.LANCHOR98]
	cmp	w0, w21
	bhi	.L3898
.L3897:
	ldrh	w1, [x1, #:lo12:.LANCHOR98]
	add	w0, w21, w24
	cmp	w0, w1
	blt	.L3898
	adrp	x0, .LANCHOR91
	ldrh	w1, [x0, #:lo12:.LANCHOR91]
	adrp	x0, .LANCHOR101
	ldrh	w0, [x0, #:lo12:.LANCHOR101]
	cmp	w1, w0
	bcc	.L3896
.L3898:
	mov	w0, 1
	mov	w1, 16
	strb	w0, [x26, #:lo12:.LANCHOR84]
	adrp	x0, .LANCHOR95
	add	x0, x0, :lo12:.LANCHOR95
	bl	_list_get_gc_head_node
	and	w1, w0, 65535
	mov	w2, 65535
	adrp	x28, .LANCHOR157
	cmp	w1, w2
	beq	.L3899
	adrp	x2, .LANCHOR11
	ubfiz	x1, x1, 1, 16
	ldr	x2, [x2, #:lo12:.LANCHOR11]
	ldrh	w2, [x2, x1]
	ldrh	w1, [x27, #:lo12:.LANCHOR158]
	cmp	w2, w1
	bcs	.L3899
	cmp	w21, 2
	bls	.L3899
	strb	wzr, [x26, #:lo12:.LANCHOR84]
	mov	w2, 0
	str	wzr, [x28, #:lo12:.LANCHOR157]
	mov	w1, 1
	bl	gc_add_sblk
	cbnz	w0, .L3890
.L3899:
	mov	w1, 0
	adrp	x0, .LANCHOR90
	add	x0, x0, :lo12:.LANCHOR90
	bl	_list_get_gc_head_node
	and	w1, w0, 65535
	mov	w2, 65535
	cmp	w1, w2
	beq	.L3900
	adrp	x2, .LANCHOR11
	ubfiz	x1, x1, 1, 16
	ldr	x2, [x2, #:lo12:.LANCHOR11]
	ldrh	w2, [x2, x1]
	ldrh	w1, [x27, #:lo12:.LANCHOR158]
	cmp	w2, w1
	bcs	.L3900
	cmp	w21, 2
	bls	.L3900
	strb	wzr, [x26, #:lo12:.LANCHOR84]
	mov	w2, 0
	str	wzr, [x28, #:lo12:.LANCHOR157]
	mov	w1, 1
	bl	gc_add_sblk
	cbnz	w0, .L3890
.L3900:
	ldrh	w0, [x27, #:lo12:.LANCHOR158]
	adrp	x1, .LANCHOR94
	add	w0, w0, 1
	ldrh	w5, [x1, #:lo12:.LANCHOR94]
	and	w0, w0, 65535
	strh	w0, [x27, #:lo12:.LANCHOR158]
	cmp	w0, w5, lsr 5
	bls	.L3901
	mov	w0, 4
	strh	w0, [x27, #:lo12:.LANCHOR158]
.L3901:
	adrp	x1, .LANCHOR87
	ldr	w0, [x28, #:lo12:.LANCHOR157]
	strh	wzr, [x1, #:lo12:.LANCHOR87]
	adrp	x1, .LANCHOR88
	add	w0, w0, 1
	str	w0, [x28, #:lo12:.LANCHOR157]
	strh	wzr, [x1, #:lo12:.LANCHOR88]
	adrp	x1, .LANCHOR89
	strh	wzr, [x1, #:lo12:.LANCHOR89]
	adrp	x1, .LANCHOR8
	ldrh	w1, [x1, #:lo12:.LANCHOR8]
	cmp	w0, w1, lsr 5
	adrp	x0, .LANCHOR91
	bls	.L3902
	ldrh	w1, [x0, #:lo12:.LANCHOR91]
	cmp	w1, w22
	bls	.L3902
	mov	w1, 0
	adrp	x0, .LANCHOR92
	add	x0, x0, :lo12:.LANCHOR92
	bl	_list_get_gc_head_node
	and	w0, w0, 65535
	mov	w1, 65535
	cmp	w0, w1
	bne	.L3903
.L4064:
	mov	w19, 16
	b	.L3904
.L3903:
	adrp	x1, .LANCHOR11
	ubfiz	x0, x0, 1, 16
	ldr	x1, [x1, #:lo12:.LANCHOR11]
	ldrh	w1, [x1, x0]
	adrp	x0, .LANCHOR79
	ldrb	w0, [x0, #:lo12:.LANCHOR79]
	mul	w0, w0, w5
	cmp	w1, w0
	bgt	.L4064
	str	wzr, [x28, #:lo12:.LANCHOR157]
	mov	w2, 4
.L4070:
	mov	w1, 2
.L4063:
	ldrb	w0, [x26, #:lo12:.LANCHOR84]
	bl	gc_search_src_blk
	and	w0, w0, 65535
	cbz	w0, .L4064
	b	.L3890
.L3902:
	ldrh	w1, [x0, #:lo12:.LANCHOR91]
	adrp	x0, .LANCHOR101
	ldrh	w0, [x0, #:lo12:.LANCHOR101]
	cmp	w1, w0
	bcc	.L3907
	mov	w2, 1
	b	.L4070
.L3907:
	ldr	x0, [x29, 120]
	ldrh	w0, [x0, #:lo12:.LANCHOR97]
	cbnz	w0, .L3908
	ldr	x0, [x29, 112]
	ldrh	w0, [x0, #:lo12:.LANCHOR99]
	cmp	w0, 8
	bls	.L3909
.L3908:
	mov	w2, 4
	mov	w1, 1
	b	.L4063
.L3909:
	adrp	x0, .LANCHOR70+2110
	ldrh	w0, [x0, #:lo12:.LANCHOR70+2110]
	cbnz	w0, .L4064
.L3904:
	ldr	x0, [x23, #:lo12:.LANCHOR12]
	adrp	x28, .LANCHOR84
	mov	w1, 1
	mov	x23, x28
	strb	w1, [x28, #:lo12:.LANCHOR84]
	ldrh	w0, [x0, 124]
	cbz	w0, .L3910
	strb	wzr, [x28, #:lo12:.LANCHOR84]
	strb	w1, [x20, #:lo12:.LANCHOR156]
.L3871:
	mov	w0, w19
	ldp	x19, x20, [sp, 32]
	ldp	x21, x22, [sp, 48]
	ldp	x23, x24, [sp, 64]
	ldp	x25, x26, [sp, 80]
	ldp	x27, x28, [sp, 96]
	ldp	x29, x30, [sp, 16]
	add	sp, sp, 144
	ret
.L3896:
	adrp	x0, .LANCHOR94
	ldrh	w1, [x0, #:lo12:.LANCHOR94]
	ldrh	w0, [x27, #:lo12:.LANCHOR158]
	cmp	w0, w1, lsr 5
	bcc	.L4064
	mov	w0, 4
	strh	w0, [x27, #:lo12:.LANCHOR158]
	b	.L4064
.L3892:
	adrp	x0, .LANCHOR86
	ldrh	w0, [x0, #:lo12:.LANCHOR86]
	cmp	w0, w21
	bcs	.L4064
	ldrh	w0, [x26, 124]
	cbz	w0, .L3988
	b	.L4064
.L3910:
	adrp	x0, .LANCHOR86
	mov	x26, x0
	ldrh	w2, [x0, #:lo12:.LANCHOR86]
	cmp	w21, w2
	bcs	.L3911
	cbz	w22, .L3912
	cmp	w22, 16
	bls	.L3913
	adrp	x0, .LANCHOR91
	ldrh	w2, [x0, #:lo12:.LANCHOR91]
	adrp	x0, .LANCHOR101
	ldrh	w0, [x0, #:lo12:.LANCHOR101]
	cmp	w2, w0
	bhi	.L3913
	mov	w2, 4
	mov	w0, w1
	bl	gc_search_src_blk
	tst	w0, 65535
	bne	.L3914
.L4071:
	mov	w2, 4
	mov	w1, 3
	ldrb	w0, [x28, #:lo12:.LANCHOR84]
	b	.L4066
.L3914:
	mov	w1, 0
	adrp	x0, .LANCHOR92
	add	x0, x0, :lo12:.LANCHOR92
	bl	_list_get_gc_head_node
	and	w3, w0, 65535
	mov	w1, 65535
	cmp	w3, w1
	beq	.L3917
	adrp	x4, .LANCHOR11
	ubfiz	x3, x3, 1, 16
	adrp	x1, .LANCHOR157
	mov	x21, x1
	ldr	x4, [x4, #:lo12:.LANCHOR11]
	ldr	w2, [x1, #:lo12:.LANCHOR157]
	add	w2, w2, 1
	str	w2, [x1, #:lo12:.LANCHOR157]
	ldrh	w3, [x4, x3]
	adrp	x4, .LANCHOR94
	ldrh	w4, [x4, #:lo12:.LANCHOR94]
	cmp	w4, w3
	bcs	.L3918
	adrp	x1, .LANCHOR8
	ldrh	w1, [x1, #:lo12:.LANCHOR8]
	cmp	w2, w1, lsr 4
	bls	.L3917
	adrp	x1, .LANCHOR100
	ldrh	w1, [x1, #:lo12:.LANCHOR100]
	cmp	w1, w3
	bls	.L3917
.L3918:
	ldrb	w2, [x23, #:lo12:.LANCHOR84]
	mov	w1, 0
	bl	gc_add_sblk
	str	wzr, [x21, #:lo12:.LANCHOR157]
	adrp	x0, .LANCHOR122
	mov	w1, 1
	str	w1, [x0, #:lo12:.LANCHOR122]
.L3917:
	mov	w0, 1
	strb	w0, [x20, #:lo12:.LANCHOR156]
	b	.L3871
.L3913:
	mov	w2, 1
	mov	w1, 2
	mov	w0, w2
	bl	gc_search_src_blk
	tst	w0, 65535
	bne	.L3917
	ldrb	w0, [x23, #:lo12:.LANCHOR84]
	mov	w2, 4
	mov	w1, 3
.L4066:
	bl	gc_search_src_blk
	and	w0, w0, 65535
.L3915:
	cbnz	w0, .L3917
	b	.L3871
.L3912:
	strb	wzr, [x28, #:lo12:.LANCHOR84]
	cmp	w21, 16
	bls	.L3920
	mov	w2, 4
	mov	w1, 3
	mov	w0, 0
	b	.L4066
.L3920:
	mov	w2, w1
	mov	w0, 0
	bl	gc_search_src_blk
	tst	w0, 65535
	bne	.L3917
	b	.L4071
.L3911:
	cmp	w25, 1
	bne	.L3871
	cmp	w21, w2, lsl 1
	bge	.L3921
	cmp	w24, w22, lsr 1
	bcs	.L3922
	adrp	x1, .LANCHOR91
	ldrh	w2, [x1, #:lo12:.LANCHOR91]
	adrp	x1, .LANCHOR101
	ldrh	w1, [x1, #:lo12:.LANCHOR101]
	cmp	w2, w1
	bcs	.L3922
	adrp	x1, .LANCHOR98
	ldrh	w1, [x1, #:lo12:.LANCHOR98]
	lsr	w1, w1, 2
	strh	w1, [x0, #:lo12:.LANCHOR86]
	b	.L3871
.L3922:
	mov	w1, 8
	adrp	x25, .LANCHOR95
	add	x0, x25, :lo12:.LANCHOR95
	bl	_list_get_gc_head_node
	and	w1, w0, 65535
	mov	w2, 65535
	cmp	w1, w2
	beq	.L3923
	adrp	x2, .LANCHOR11
	ubfiz	x1, x1, 1, 16
	ldr	x2, [x2, #:lo12:.LANCHOR11]
	ldrh	w1, [x2, x1]
	cmp	w1, 3
	bhi	.L3923
	cbz	w21, .L3923
	strb	wzr, [x23, #:lo12:.LANCHOR84]
	mov	w2, 0
	mov	w1, 1
	bl	gc_add_sblk
	cbnz	w0, .L3917
.L3923:
	mov	w1, 0
	adrp	x0, .LANCHOR92
	add	x0, x0, :lo12:.LANCHOR92
	bl	_list_get_gc_head_node
	and	w28, w0, 65535
	mov	w1, 65535
	mov	w3, w28
	cmp	w28, w1
	bne	.L3924
.L3929:
	cmp	w22, 1
	bhi	.L3925
.L3926:
	cmp	w21, w24
	adrp	x21, .LANCHOR98
	bcs	.L3933
	mov	w1, 4
	strb	wzr, [x23, #:lo12:.LANCHOR84]
	add	x0, x25, :lo12:.LANCHOR95
	bl	_list_get_gc_head_node
	and	w0, w0, 65535
	mov	w1, 65535
	cmp	w0, w1
	beq	.L3933
	adrp	x1, .LANCHOR11
	ubfiz	x0, x0, 1, 16
	adrp	x2, .LANCHOR79
	ldr	x1, [x1, #:lo12:.LANCHOR11]
	ldrb	w2, [x2, #:lo12:.LANCHOR79]
	ldrh	w1, [x1, x0]
	adrp	x0, .LANCHOR94
	ldrh	w0, [x0, #:lo12:.LANCHOR94]
	mul	w0, w0, w2
	cmp	w1, w0, lsr 1
	ble	.L3935
.L3933:
	ldrh	w0, [x21, #:lo12:.LANCHOR98]
	lsr	w0, w0, 2
	strh	w0, [x26, #:lo12:.LANCHOR86]
	b	.L3871
.L3924:
	adrp	x2, .LANCHOR157
	adrp	x4, .LANCHOR8
	uxtw	x28, w28
	ldr	w1, [x2, #:lo12:.LANCHOR157]
	ldrh	w4, [x4, #:lo12:.LANCHOR8]
	add	w1, w1, 1
	str	w1, [x2, #:lo12:.LANCHOR157]
	cmp	w1, w4, lsr 4
	adrp	x4, .LANCHOR11
	bls	.L3927
	ldr	x1, [x4, #:lo12:.LANCHOR11]
	str	wzr, [x2, #:lo12:.LANCHOR157]
	ldrh	w2, [x1, x28, lsl 1]
	adrp	x1, .LANCHOR100
	ldrh	w1, [x1, #:lo12:.LANCHOR100]
	cmp	w2, w1
	bcs	.L3927
	mov	w5, 1
	str	x4, [x29, 96]
	strb	w5, [x23, #:lo12:.LANCHOR84]
	mov	w2, 1
	stp	w3, w5, [x29, 104]
	mov	w1, 0
	bl	gc_add_sblk
	ldp	w3, w5, [x29, 104]
	ldr	x4, [x29, 96]
	cbz	w0, .L3927
	strb	w5, [x20, #:lo12:.LANCHOR156]
	b	.L3871
.L3927:
	ldr	x0, [x4, #:lo12:.LANCHOR11]
	ldrh	w1, [x0, x28, lsl 1]
	adrp	x0, .LANCHOR94
	ldrh	w0, [x0, #:lo12:.LANCHOR94]
	cmp	w1, w0, lsr 1
	bhi	.L3928
	mov	w2, 0
	mov	w1, 1
	mov	w0, w3
	bl	gc_add_sblk
	b	.L3917
.L3928:
	ldp	x2, x0, [x29, 112]
	ldrh	w2, [x2, #:lo12:.LANCHOR99]
	ldrh	w0, [x0, #:lo12:.LANCHOR97]
	add	w0, w0, w2
	adrp	x2, .LANCHOR98
	ldrh	w2, [x2, #:lo12:.LANCHOR98]
	cmp	w0, w2, lsl 1
	ble	.L3929
	adrp	x0, .LANCHOR100
	ldrh	w0, [x0, #:lo12:.LANCHOR100]
	cmp	w0, w1
	bcc	.L3926
	b	.L3929
.L3925:
	mov	w1, 1
	strb	w1, [x23, #:lo12:.LANCHOR84]
	cmp	w22, 16
	bls	.L3930
	adrp	x0, .LANCHOR91
	ldrh	w2, [x0, #:lo12:.LANCHOR91]
	adrp	x0, .LANCHOR101
	ldrh	w0, [x0, #:lo12:.LANCHOR101]
	cmp	w2, w0
	bhi	.L3930
	mov	w0, w1
	mov	w2, 4
.L4073:
	bl	gc_search_src_blk
	ands	w0, w0, 65535
	bne	.L3931
	ldrb	w0, [x23, #:lo12:.LANCHOR84]
	mov	w2, 4
	mov	w1, 3
	bl	gc_search_src_blk
	and	w0, w0, 65535
.L3931:
	adrp	x1, .LANCHOR98
	cmp	w21, w24, lsr 1
	ldrh	w1, [x1, #:lo12:.LANCHOR98]
	bls	.L4067
	lsr	w1, w1, 2
.L4068:
	strh	w1, [x26, #:lo12:.LANCHOR86]
	b	.L3915
.L3930:
	mov	w2, 1
	mov	w1, 2
	mov	w0, w2
	b	.L4073
.L3935:
	mov	w1, 3
	mov	w2, 4
	mov	w0, 0
	bl	gc_search_src_blk
	ldrh	w1, [x21, #:lo12:.LANCHOR98]
	and	w0, w0, 65535
.L4067:
	lsr	w1, w1, 1
	b	.L4068
.L3921:
	adrp	x1, .LANCHOR98
	ldrh	w1, [x1, #:lo12:.LANCHOR98]
	lsr	w1, w1, 2
	strh	w1, [x0, #:lo12:.LANCHOR86]
	adrp	x0, .LANCHOR70+2110
	ldrh	w0, [x0, #:lo12:.LANCHOR70+2110]
	cmp	w0, 0
	csel	w19, w19, wzr, ne
	b	.L3871
.L3875:
	adrp	x7, .LANCHOR70
	mov	w0, 65535
	ldrh	w1, [x7, #:lo12:.LANCHOR70]
	cmp	w1, w0
	bne	.L3936
	bl	gc_get_src_blk
	strh	w0, [x7, #:lo12:.LANCHOR70]
.L3936:
	ldrh	w0, [x7, #:lo12:.LANCHOR70]
	mov	w1, 65535
	cmp	w0, w1
	beq	.L3937
	adrp	x1, .LANCHOR8
	ldrh	w1, [x1, #:lo12:.LANCHOR8]
	cmp	w1, w0
	bhi	.L3937
	mov	w0, -1
	strh	w0, [x7, #:lo12:.LANCHOR70]
.L3937:
	ldrh	w3, [x7, #:lo12:.LANCHOR70]
	mov	w0, 65535
	add	x1, x7, :lo12:.LANCHOR70
	cmp	w3, w0
	beq	.L4075
	adrp	x0, .LANCHOR9
	ldrh	w5, [x1, 56]
	uxtw	x4, w3
	ldr	x2, [x0, #:lo12:.LANCHOR9]
	add	x2, x2, x4, lsl 2
	cbz	w5, .L3939
	add	x1, x1, 58
	mov	w0, 0
.L3941:
	ldrh	w6, [x1], 2
	cmp	w6, w3
	bne	.L3940
.L3945:
	adrp	x0, .LANCHOR70
	mov	w1, -1
	strh	w1, [x0, #:lo12:.LANCHOR70]
	b	.L3988
.L3940:
	add	w0, w0, 1
	and	w0, w0, 65535
	cmp	w5, w0
	bne	.L3941
.L3939:
	ldrb	w0, [x2, 2]
	and	w1, w0, 224
	cmp	w1, 224
	beq	.L3942
	tst	w0, 192
	bne	.L3943
.L3942:
	adrp	x0, .LANCHOR11
	ldr	x0, [x0, #:lo12:.LANCHOR11]
	ldrh	w0, [x0, x4, lsl 1]
	cbz	w0, .L3945
	mov	w2, 3306
	adrp	x1, .LANCHOR237
	adrp	x0, .LC0
	add	x1, x1, :lo12:.LANCHOR237
	add	x0, x0, :lo12:.LC0
	bl	printf
	b	.L3945
.L3943:
	mov	w0, 2
	b	.L4076
.L3876:
	bl	gc_scan_src_blk
	cmn	w0, #1
	bne	.L3946
	mov	w0, 3
	b	.L4076
.L3946:
	adrp	x19, .LANCHOR70
	mov	w2, 65535
	add	x0, x19, :lo12:.LANCHOR70
	ldrh	w1, [x19, #:lo12:.LANCHOR70]
	cmp	w1, w2
	beq	.L3890
	ldrh	w2, [x0, 24]
	cbz	w2, .L3947
	mov	w1, 4
	strh	wzr, [x0, 26]
	strb	w1, [x20, #:lo12:.LANCHOR156]
	b	.L3988
.L3947:
	mov	w0, 1
	strb	w0, [x20, #:lo12:.LANCHOR156]
	adrp	x0, .LANCHOR11
	ubfiz	x1, x1, 1, 16
	mov	x20, x0
	ldr	x2, [x0, #:lo12:.LANCHOR11]
	ldrh	w1, [x2, x1]
	cbz	w1, .L3948
	adrp	x1, .LANCHOR237
	adrp	x0, .LC0
	mov	w2, 3336
	add	x1, x1, :lo12:.LANCHOR237
	add	x0, x0, :lo12:.LC0
	bl	printf
.L3948:
	ldrh	w0, [x19, #:lo12:.LANCHOR70]
	add	x21, x19, :lo12:.LANCHOR70
	bl	ftl_free_sblk
	ldr	x0, [x20, #:lo12:.LANCHOR11]
	ldrh	w1, [x19, #:lo12:.LANCHOR70]
	strh	wzr, [x0, x1, lsl 1]
	ldrh	w0, [x21, 30]
	add	w0, w0, 1
	and	w0, w0, 65535
	cmp	w0, 8
	bhi	.L3949
	strh	w0, [x21, 30]
	b	.L3945
.L3949:
	strh	wzr, [x21, 30]
	bl	ftl_flush
	bl	pm_flush
	bl	ftl_ext_info_flush
	mov	w0, 0
	bl	ftl_info_flush
	b	.L3945
.L3877:
	adrp	x19, .LANCHOR70
	adrp	x23, .LANCHOR94
	add	x22, x19, :lo12:.LANCHOR70
	add	x23, x23, :lo12:.LANCHOR94
.L4037:
	bl	gc_scan_src_blk_one_page
	ldrh	w1, [x22, 2]
	ldrh	w0, [x23]
	cmp	w1, w0
	bcs	.L3951
	cmp	w21, 7
	bls	.L4037
	b	.L3988
.L3951:
	ldrh	w3, [x22, 24]
	ldrh	w1, [x22]
	cbz	w3, .L3952
	mov	w0, 4
	strb	w0, [x20, #:lo12:.LANCHOR156]
	adrp	x20, .LANCHOR11
	ubfiz	x0, x1, 1, 16
	strh	wzr, [x22, 26]
	ldr	x2, [x20, #:lo12:.LANCHOR11]
	ldrh	w2, [x2, x0]
	cmp	w3, w2
	beq	.L3953
	adrp	x0, .LANCHOR19
	ldr	w0, [x0, #:lo12:.LANCHOR19]
	tbz	x0, 10, .L3953
	adrp	x0, .LC240
	add	x0, x0, :lo12:.LC240
	bl	printf
.L3953:
	ldrh	w2, [x19, #:lo12:.LANCHOR70]
	add	x0, x19, :lo12:.LANCHOR70
	ldr	x1, [x20, #:lo12:.LANCHOR11]
	ldrh	w0, [x0, 24]
	ldrh	w1, [x1, x2, lsl 1]
	cmp	w1, w0
	beq	.L3954
	adrp	x1, .LANCHOR237
	adrp	x0, .LC0
	mov	w2, 3379
	add	x1, x1, :lo12:.LANCHOR237
	add	x0, x0, :lo12:.LC0
	bl	printf
.L3954:
	add	x0, x19, :lo12:.LANCHOR70
	ldrh	w1, [x19, #:lo12:.LANCHOR70]
	ldrh	w2, [x0, 24]
	ldr	x0, [x20, #:lo12:.LANCHOR11]
	strh	w2, [x0, x1, lsl 1]
	b	.L3988
.L3952:
	adrp	x0, .LANCHOR9
	ldr	x21, [x0, #:lo12:.LANCHOR9]
	mov	w0, 1
	strb	w0, [x20, #:lo12:.LANCHOR156]
	adrp	x0, .LANCHOR19
	ldr	w0, [x0, #:lo12:.LANCHOR19]
	add	x21, x21, x1, uxth 2
	tbz	x0, 8, .L3955
	ldrb	w2, [x21, 2]
	adrp	x0, .LC241
	add	x0, x0, :lo12:.LC241
	ubfx	x2, x2, 5, 3
	bl	printf
.L3955:
	ldrb	w0, [x21, 2]
	and	w1, w0, 224
	cmp	w1, 224
	beq	.L3956
	tst	w0, 192
	bne	.L3957
.L3956:
	adrp	x1, .LANCHOR237
	adrp	x0, .LC0
	mov	w2, 3389
	add	x1, x1, :lo12:.LANCHOR237
	add	x0, x0, :lo12:.LC0
	bl	printf
.L3957:
	ldrh	w0, [x19, #:lo12:.LANCHOR70]
	add	x20, x19, :lo12:.LANCHOR70
	bl	ftl_free_sblk
	mov	w0, -1
	strh	w0, [x19, #:lo12:.LANCHOR70]
	ldrh	w0, [x20, 30]
	add	w0, w0, 1
	and	w0, w0, 65535
	cmp	w0, 8
	bhi	.L3958
	strh	w0, [x20, 30]
	b	.L3988
.L3958:
	strh	wzr, [x20, 30]
.L4074:
	bl	flt_sys_flush
	b	.L3988
.L3878:
	ldrh	w1, [x26, 80]
	mov	w0, 65535
	cmp	w1, w0
	bne	.L3959
	adrp	x0, .LANCHOR84
	ldrb	w19, [x0, #:lo12:.LANCHOR84]
	cmp	w19, 1
	bne	.L3959
	bl	ftl_flush
	adrp	x0, .LANCHOR70
	add	x1, x0, :lo12:.LANCHOR70
	mov	x20, x0
	ldrh	w1, [x1, 2192]
	cbz	w1, .L3960
	mov	w0, w19
	mov	w1, 5
.L4069:
	bl	zftl_gc_get_free_sblk
	and	w19, w0, 65535
	mov	w0, 65535
	cmp	w19, w0
	beq	.L3962
	adrp	x0, .LANCHOR9
	ldr	x21, [x0, #:lo12:.LANCHOR9]
	add	x21, x21, x19, uxth 2
	ldrb	w0, [x21, 2]
	tst	w0, 224
	beq	.L3963
	adrp	x1, .LANCHOR237
	adrp	x0, .LC0
	mov	w2, 3423
	add	x1, x1, :lo12:.LANCHOR237
	add	x0, x0, :lo12:.LC0
	bl	printf
.L3963:
	ldrb	w0, [x21, 2]
	mov	w1, 5
	bfi	w0, w1, 5, 3
	orr	w0, w0, 16
	strb	w0, [x21, 2]
.L3987:
	mov	w1, 1
	mov	w0, w19
	bl	ftl_erase_sblk
	adrp	x22, .LANCHOR85
	mov	w0, 5
	strb	w0, [x26, 84]
	add	x1, x26, 96
	mov	w0, w19
	bl	ftl_get_blk_list_in_sblk
	and	w0, w0, 255
	adrp	x1, .LANCHOR94
	adrp	x21, .LANCHOR79
	strb	w0, [x26, 89]
	ldrh	w1, [x1, #:lo12:.LANCHOR94]
	ldrh	w2, [x22, #:lo12:.LANCHOR85]
	strh	w19, [x26, 80]
	strh	wzr, [x26, 82]
	mul	w0, w0, w1
	strb	wzr, [x26, 85]
	strh	w0, [x26, 86]
	mov	w1, 255
	ldrb	w0, [x21, #:lo12:.LANCHOR79]
	strh	wzr, [x26, 90]
	mul	w2, w2, w0
	adrp	x0, .LANCHOR159
	ldr	x0, [x0, #:lo12:.LANCHOR159]
	lsl	w2, w2, 2
	bl	ftl_memset
	ldrb	w0, [x21, #:lo12:.LANCHOR79]
	mov	w1, 255
	ldrh	w2, [x22, #:lo12:.LANCHOR85]
	mul	w2, w2, w0
	adrp	x0, .LANCHOR160
	ldr	x0, [x0, #:lo12:.LANCHOR160]
	lsl	w2, w2, 2
	bl	ftl_memset
	ldrb	w0, [x21, #:lo12:.LANCHOR79]
	mov	w1, 255
	ldrh	w2, [x22, #:lo12:.LANCHOR85]
	mul	w2, w2, w0
	adrp	x0, .LANCHOR82
	ldr	x0, [x0, #:lo12:.LANCHOR82]
	bl	ftl_memset
	ldr	x0, [x23, #:lo12:.LANCHOR12]
	mov	w1, -1
	str	w19, [x0, 132]
	strh	w1, [x0, 128]
	strh	w1, [x0, 130]
	bl	pm_flush
	bl	ftl_ext_info_flush
	adrp	x0, .LANCHOR110
	mov	w1, -1
	ldr	x0, [x0, #:lo12:.LANCHOR110]
	strh	w19, [x0, 126]
	add	x0, x20, :lo12:.LANCHOR70
	str	w1, [x0, 2196]
	strh	wzr, [x0, 2106]
	strh	wzr, [x0, 56]
	strh	wzr, [x0, 2108]
	strh	wzr, [x0, 2194]
	mov	w0, 0
	bl	ftl_info_flush
	b	.L3988
.L3960:
	mov	w1, 5
	mov	w0, 0
	b	.L4069
.L3959:
	cmp	w25, 1
	mov	w24, 4
	csinc	w24, w24, wzr, eq
	cmp	w21, 15
	mov	w0, w24
	add	w24, w24, 4
	adrp	x25, .LANCHOR84
	adrp	x21, .LANCHOR70
	csel	w24, w24, w0, ls
	add	x25, x25, :lo12:.LANCHOR84
	add	x19, x21, :lo12:.LANCHOR70
	add	x27, x26, 80
.L3966:
	sub	w24, w24, #1
	and	w24, w24, 255
	cmp	w24, 255
	beq	.L3988
	bl	gc_do_copy_back
	ldrb	w0, [x25]
	cbnz	w0, .L3967
	adrp	x0, .LANCHOR57
	ldrb	w0, [x0, #:lo12:.LANCHOR57]
	cmp	w0, 3
	bhi	.L3968
	bl	ftl_write_commit
.L3968:
	ldrh	w1, [x19, 26]
	ldrh	w0, [x19, 24]
	cmp	w1, w0
	bcc	.L3966
	mov	w0, 1
	strb	w0, [x20, #:lo12:.LANCHOR156]
	bl	ftl_write_commit
	bl	ftl_flush
	adrp	x0, .LANCHOR11
	ldrh	w2, [x19]
	mov	x19, x0
	ldr	x1, [x0, #:lo12:.LANCHOR11]
	ldrh	w1, [x1, x2, lsl 1]
	cbz	w1, .L3970
	adrp	x1, .LANCHOR237
	adrp	x0, .LC0
	mov	w2, 3507
	add	x1, x1, :lo12:.LANCHOR237
	add	x0, x0, :lo12:.LC0
	bl	printf
.L3970:
	ldrh	w0, [x21, #:lo12:.LANCHOR70]
	ldr	x2, [x19, #:lo12:.LANCHOR11]
	ubfiz	x1, x0, 1, 16
	ldrh	w1, [x2, x1]
	cbnz	w1, .L3971
	bl	ftl_free_sblk
	b	.L3945
.L3971:
	mov	w2, 1
	mov	w1, 0
	bl	gc_add_sblk
	b	.L3945
.L3967:
	ldrh	w0, [x19, 2194]
	cbz	w0, .L3972
	strh	wzr, [x19, 2194]
	bl	sblk_wait_write_queue_completed
	bl	gc_write_completed
	ldr	w0, [x19, 2196]
	adrp	x19, .LANCHOR110
	cmn	w0, #1
	beq	.L3973
	adrp	x1, .LANCHOR124
	ldrb	w1, [x1, #:lo12:.LANCHOR124]
	cbnz	w1, .L3974
	adrp	x1, .LANCHOR80
	ldrb	w1, [x1, #:lo12:.LANCHOR80]
	cbz	w1, .L3975
.L3974:
	ldr	x1, [x19, #:lo12:.LANCHOR110]
	ldr	w2, [x1, 156]
	mov	w1, 20041
	movk	w1, 0x444b, lsl 16
	cmp	w2, w1
	bne	.L3975
	adrp	x1, .LANCHOR74
	ldrh	w3, [x1, #:lo12:.LANCHOR74]
	adrp	x1, .LANCHOR31
	ldrb	w2, [x1, #:lo12:.LANCHOR31]
	mov	w1, 24
	lsr	w0, w0, w3
	sub	w1, w1, w2
	sub	w2, w1, w3
	mov	w1, 1
	lsl	w1, w1, w2
	sub	w1, w1, #1
	and	w0, w1, w0
	adrp	x1, .LANCHOR75
	ldrb	w1, [x1, #:lo12:.LANCHOR75]
	udiv	w0, w0, w1
	adrp	x1, .LANCHOR9
	ldr	x2, [x1, #:lo12:.LANCHOR9]
	lsl	x0, x0, 2
	add	x4, x2, x0
	ldrb	w1, [x4, 2]
	tbz	x1, 3, .L3973
	adrp	x5, .LANCHOR98
	ldrh	w3, [x22, #:lo12:.LANCHOR103]
	ldrh	w5, [x5, #:lo12:.LANCHOR98]
	add	w3, w3, 8
	cmp	w3, w5
	bge	.L3973
	and	w1, w1, -25
	strb	w1, [x4, 2]
	adrp	x1, .LANCHOR10
	ldr	w3, [x2, x0]
	ldrh	w1, [x1, #:lo12:.LANCHOR10]
	ldrh	w4, [x2, x0]
	ubfx	x3, x3, 11, 8
	and	w5, w4, 2047
	mul	w1, w1, w3
	lsr	w3, w3, 3
	add	w1, w1, w1, lsl 1
	add	w1, w5, w1, lsr 2
	bfi	w4, w1, 0, 11
	strh	w4, [x2, x0]
	ldr	w1, [x2, x0]
	bfi	w1, w3, 11, 8
	str	w1, [x2, x0]
.L3973:
	ldr	x0, [x23, #:lo12:.LANCHOR12]
	add	x22, x21, :lo12:.LANCHOR70
	strh	wzr, [x22, 56]
	ldrh	w0, [x0, 80]
	str	wzr, [x22, 2196]
	bl	ftl_free_sblk
	ldr	x1, [x23, #:lo12:.LANCHOR12]
	mov	w0, -1
	ldr	x2, [x19, #:lo12:.LANCHOR110]
	strh	w0, [x1, 80]
	strh	w0, [x2, 126]
	strh	w0, [x1, 130]
	ldr	x0, [x22, 8]
	cbz	x0, .L3976
	bl	zbuf_free
.L3976:
	add	x21, x21, :lo12:.LANCHOR70
	str	xzr, [x21, 8]
	bl	flt_sys_flush
	mov	w2, 3567
	strb	wzr, [x20, #:lo12:.LANCHOR156]
	adrp	x1, .LANCHOR237
	adrp	x0, .LC0
	add	x1, x1, :lo12:.LANCHOR237
	add	x0, x0, :lo12:.LC0
	bl	printf
	b	.L3988
.L3975:
	bl	ftl_mask_bad_block
	b	.L3973
.L3972:
	ldrh	w0, [x27, 6]
	ldrh	w1, [x19, 26]
	cmp	w0, 1
	ldrh	w0, [x19, 24]
	bls	.L3977
	cmp	w1, w0
	bcc	.L3966
	mov	w0, 1
	strb	w0, [x20, #:lo12:.LANCHOR156]
	ldrh	w0, [x19, 56]
	add	w1, w0, 1
	strh	w1, [x19, 56]
	add	x0, x19, x0, sxtw 1
	ldrh	w1, [x19]
	strh	w1, [x0, 58]
	mov	w0, -1
	strh	w0, [x19]
	b	.L3988
.L3977:
	mov	w2, 5
	strb	w2, [x20, #:lo12:.LANCHOR156]
	cmp	w1, w0
	bcc	.L3978
	ldrh	w0, [x19, 56]
	add	w1, w0, 1
	strh	w1, [x19, 56]
	add	x0, x19, x0, sxtw 1
	ldrh	w1, [x19]
	strh	w1, [x0, 58]
	mov	w0, -1
	strh	w0, [x19]
.L3978:
	bl	ftl_flush
	bl	sblk_wait_write_queue_completed
	bl	gc_write_completed
	ldr	x0, [x23, #:lo12:.LANCHOR12]
	ldrh	w1, [x26, 80]
	strh	w1, [x0, 128]
	bl	pm_flush
	bl	ftl_ext_info_flush
	adrp	x1, .LANCHOR94
	add	x0, x21, :lo12:.LANCHOR70
	adrp	x2, .LANCHOR35
	ldrh	w1, [x1, #:lo12:.LANCHOR94]
	strh	w1, [x0, 18]
	adrp	x1, .LANCHOR78
	ldrb	w2, [x2, #:lo12:.LANCHOR35]
	strh	wzr, [x0, 16]
	ldrb	w1, [x1, #:lo12:.LANCHOR78]
	strh	w1, [x0, 20]
	cbz	w2, .L3979
	adrp	x2, .LANCHOR85
	ldrh	w2, [x2, #:lo12:.LANCHOR85]
	strh	w2, [x0, 18]
	mov	w2, 1
	strh	w2, [x0, 20]
.L3979:
	cmp	w1, 2
	bne	.L3981
	add	x0, x21, :lo12:.LANCHOR70
	ldrh	w1, [x0, 18]
	ubfiz	w1, w1, 1, 15
	strh	w1, [x0, 18]
	adrp	x1, .LANCHOR80
	ldrb	w1, [x1, #:lo12:.LANCHOR80]
	cbnz	w1, .L3981
	mov	w1, 1
	strh	w1, [x0, 20]
.L3981:
	add	x21, x21, :lo12:.LANCHOR70
	strh	wzr, [x21, 22]
	b	.L3988
.L3984:
	ldrh	w1, [x24, 16]
	ldrh	w0, [x24, 18]
	cmp	w1, w0
	bcc	.L3985
	mov	w0, 6
	strb	w0, [x20, #:lo12:.LANCHOR156]
	ldr	x0, [x24, 8]
	bl	zbuf_free
	str	xzr, [x24, 8]
	b	.L3988
.L3985:
	cmp	w21, 15
	bls	.L3881
	cmp	w25, 1
	bne	.L3988
	add	w22, w22, 1
	and	w22, w22, 255
	cmp	w22, 4
	bls	.L3881
	b	.L3988
.L3880:
	bl	gc_update_l2p_map_new
	mov	w19, -1
	bl	gc_free_src_blk
	bl	ftl_flush
	bl	pm_flush
	strh	w19, [x26, 80]
	bl	ftl_ext_info_flush
	adrp	x0, .LANCHOR110
	ldr	x0, [x0, #:lo12:.LANCHOR110]
	strh	w19, [x0, 126]
	mov	w0, 0
	bl	ftl_info_flush
.L4075:
	strb	wzr, [x20, #:lo12:.LANCHOR156]
	b	.L3988
.L3962:
	mov	w2, 3430
	adrp	x1, .LANCHOR237
	adrp	x0, .LC0
	add	x1, x1, :lo12:.LANCHOR237
	add	x0, x0, :lo12:.LC0
	bl	printf
	b	.L3987
	.size	zftl_do_gc, .-zftl_do_gc
	.section	.text.zftl_init,"ax",@progbits
	.align	2
	.global	zftl_init
	.type	zftl_init, %function
zftl_init:
	stp	x29, x30, [sp, -112]!
	adrp	x1, .LANCHOR65
	mov	w0, -1
	add	x29, sp, 0
	strb	w0, [x1, #:lo12:.LANCHOR65]
	adrp	x1, .LANCHOR66
	stp	x21, x22, [sp, 32]
	adrp	x22, .LANCHOR94
	strb	wzr, [x1, #:lo12:.LANCHOR66]
	adrp	x1, .LANCHOR133
	stp	x19, x20, [sp, 16]
	adrp	x21, .LANCHOR79
	strb	w0, [x1, #:lo12:.LANCHOR133]
	adrp	x1, .LANCHOR134
	stp	x23, x24, [sp, 48]
	adrp	x20, .LANCHOR221
	strb	wzr, [x1, #:lo12:.LANCHOR134]
	adrp	x1, .LANCHOR182
	stp	x25, x26, [sp, 64]
	adrp	x23, .LANCHOR8
	strb	w0, [x1, #:lo12:.LANCHOR182]
	adrp	x0, .LANCHOR129
	mov	w1, -1
	stp	x27, x28, [sp, 80]
	strb	wzr, [x0, #:lo12:.LANCHOR129]
	adrp	x0, .LANCHOR238
	str	w1, [x0, #:lo12:.LANCHOR238]
	adrp	x1, .LC242
	adrp	x0, .LC101
	add	x1, x1, :lo12:.LC242
	add	x0, x0, :lo12:.LC101
	bl	printf
	adrp	x1, .LANCHOR32
	add	x1, x1, :lo12:.LANCHOR32
	adrp	x0, .LANCHOR78
	adrp	x2, .LANCHOR131
	adrp	x3, .LANCHOR112
	adrp	x4, .LANCHOR75
	ldrb	w7, [x1, 12]
	strb	w7, [x0, #:lo12:.LANCHOR78]
	ldrb	w0, [x1, 9]
	strb	w0, [x2, #:lo12:.LANCHOR131]
	adrp	x2, .LANCHOR85
	ldrh	w5, [x1, 10]
	strh	w5, [x2, #:lo12:.LANCHOR85]
	adrp	x2, .LANCHOR23
	ldrh	w8, [x1, 14]
	ubfiz	w6, w0, 9, 7
	ldrb	w2, [x2, #:lo12:.LANCHOR23]
	sdiv	w11, w5, w7
	strb	w2, [x3, #:lo12:.LANCHOR112]
	ldrb	w3, [x1, 13]
	adrp	x1, .LANCHOR2
	strb	w3, [x4, #:lo12:.LANCHOR75]
	ldrh	w4, [x1, #:lo12:.LANCHOR2]
	adrp	x1, .LANCHOR111
	strh	w11, [x22, #:lo12:.LANCHOR94]
	mul	w2, w2, w3
	strh	w4, [x1, #:lo12:.LANCHOR111]
	strh	w8, [x23, #:lo12:.LANCHOR8]
	mov	w3, 1
	and	w2, w2, 255
	strh	w6, [x20, #:lo12:.LANCHOR221]
	strb	w2, [x21, #:lo12:.LANCHOR79]
	mov	w1, 0
.L4078:
	cmp	w4, w3
	bcs	.L4079
	mul	w10, w0, w5
	adrp	x3, .LANCHOR74
	sub	w1, w1, #1
	mov	w4, 0
	strh	w1, [x3, #:lo12:.LANCHOR74]
	mov	w1, 1
	mul	w3, w8, w10
	lsr	w12, w3, 21
.L4080:
	cmp	w12, w1
	bcs	.L4081
	mov	w1, 57344
	sub	w4, w4, #1
	movk	w1, 0x1c, lsl 16
	mul	w3, w3, w2
	adrp	x28, .LANCHOR128
	sub	w12, w6, #1
	mul	w1, w2, w1
	adrp	x24, .LANCHOR202
	mul	w11, w11, w2
	adrp	x27, .LANCHOR240
	mul	w10, w10, w2
	adrp	x26, .LANCHOR152
	lsl	w1, w1, w4
	adrp	x4, .LANCHOR67
	sub	w10, w10, #1
	adrp	x25, .LANCHOR98
	str	w1, [x4, #:lo12:.LANCHOR67]
	adrp	x4, .LANCHOR239
	lsr	w8, w8, 4
	strh	w8, [x25, #:lo12:.LANCHOR98]
	str	w3, [x4, #:lo12:.LANCHOR239]
	add	w3, w1, 24576
	str	w3, [x27, #:lo12:.LANCHOR240]
	cmp	w8, 79
	udiv	w0, w3, w0
	udiv	w3, w3, w10
	str	w0, [x28, #:lo12:.LANCHOR128]
	add	w0, w12, w0, lsl 2
	add	w3, w3, 8
	udiv	w0, w0, w6
	strh	w0, [x24, #:lo12:.LANCHOR202]
	ubfiz	w0, w0, 4, 16
	sdiv	w0, w0, w11
	strh	w0, [x26, #:lo12:.LANCHOR152]
	adrp	x0, .LANCHOR101
	str	x0, [x29, 104]
	strh	w3, [x0, #:lo12:.LANCHOR101]
	bhi	.L4082
	mov	w0, 80
	strh	w0, [x25, #:lo12:.LANCHOR98]
.L4082:
	adrp	x12, .LANCHOR126
	mov	w0, 2000
	adrp	x11, .LANCHOR125
	adrp	x3, .LANCHOR149
	strh	w0, [x12, #:lo12:.LANCHOR126]
	mov	w0, 50
	adrp	x8, .LANCHOR150
	strh	w0, [x11, #:lo12:.LANCHOR125]
	mov	w0, 256
	strh	w0, [x3, #:lo12:.LANCHOR149]
	mov	w0, 48
	strh	w0, [x8, #:lo12:.LANCHOR150]
	adrp	x0, .LANCHOR10
	mov	w10, 32
	cmp	w7, 2
	mov	x13, x11
	strh	w10, [x0, #:lo12:.LANCHOR10]
	mov	x7, x12
	mov	x14, x8
	beq	.L4083
	adrp	x15, .LANCHOR83
	ldrb	w15, [x15, #:lo12:.LANCHOR83]
	cbz	w15, .L4084
.L4083:
	mov	w8, 150
	strh	w8, [x13, #:lo12:.LANCHOR125]
	mov	w8, 64
	strh	w8, [x14, #:lo12:.LANCHOR150]
	mov	w8, 12
	strh	w8, [x0, #:lo12:.LANCHOR10]
	adrp	x8, .LANCHOR0
	ldrb	w8, [x8, #:lo12:.LANCHOR0]
	cbnz	w8, .L4085
	mov	w8, 4
	strh	w8, [x0, #:lo12:.LANCHOR10]
	mov	w0, 600
	strh	w0, [x7, #:lo12:.LANCHOR126]
	mov	w0, 128
	strh	w0, [x3, #:lo12:.LANCHOR149]
.L4085:
	adrp	x0, .LANCHOR36
	ldrb	w0, [x0, #:lo12:.LANCHOR36]
	cbz	w0, .L4087
	mov	w0, 200
	strh	w0, [x13, #:lo12:.LANCHOR125]
	mov	w0, 2000
	strh	w0, [x7, #:lo12:.LANCHOR126]
.L4087:
	adrp	x0, .LANCHOR122
	mul	w2, w5, w2
	mov	w3, 1
	str	wzr, [x0, #:lo12:.LANCHOR122]
	adrp	x0, .LANCHOR224
	cmp	w6, w2, lsl 2
	strb	w3, [x0, #:lo12:.LANCHOR224]
	bge	.L4089
	mov	w2, 2
	strb	w2, [x0, #:lo12:.LANCHOR224]
.L4089:
	adrp	x19, .LANCHOR19
	ldr	w0, [x19, #:lo12:.LANCHOR19]
	tbz	x0, 12, .L4090
	str	x4, [x29, 96]
	adrp	x0, .LC243
	add	x0, x0, :lo12:.LC243
	bl	printf
	ldr	x4, [x29, 96]
.L4090:
	ldr	w0, [x19, #:lo12:.LANCHOR19]
	tbz	x0, 12, .L4091
	ldr	w1, [x4, #:lo12:.LANCHOR239]
	adrp	x0, .LC244
	add	x0, x0, :lo12:.LC244
	bl	printf
.L4091:
	ldr	w0, [x19, #:lo12:.LANCHOR19]
	tbz	x0, 12, .L4092
	ldr	w1, [x28, #:lo12:.LANCHOR128]
	adrp	x0, .LC245
	add	x0, x0, :lo12:.LC245
	bl	printf
.L4092:
	ldr	w0, [x19, #:lo12:.LANCHOR19]
	tbz	x0, 12, .L4093
	ldr	w1, [x27, #:lo12:.LANCHOR240]
	adrp	x0, .LC246
	add	x0, x0, :lo12:.LC246
	bl	printf
.L4093:
	ldr	w0, [x19, #:lo12:.LANCHOR19]
	tbz	x0, 12, .L4094
	ldrh	w1, [x24, #:lo12:.LANCHOR202]
	adrp	x0, .LC247
	add	x0, x0, :lo12:.LC247
	bl	printf
.L4094:
	ldr	w0, [x19, #:lo12:.LANCHOR19]
	tbz	x0, 12, .L4095
	ldrh	w1, [x20, #:lo12:.LANCHOR221]
	adrp	x0, .LC248
	add	x0, x0, :lo12:.LC248
	bl	printf
.L4095:
	ldr	w0, [x19, #:lo12:.LANCHOR19]
	tbz	x0, 12, .L4096
	ldrh	w1, [x26, #:lo12:.LANCHOR152]
	adrp	x0, .LC249
	add	x0, x0, :lo12:.LC249
	bl	printf
.L4096:
	ldr	w0, [x19, #:lo12:.LANCHOR19]
	tbz	x0, 12, .L4097
	ldrh	w1, [x25, #:lo12:.LANCHOR98]
	adrp	x0, .LC250
	add	x0, x0, :lo12:.LC250
	bl	printf
.L4097:
	ldr	w0, [x19, #:lo12:.LANCHOR19]
	tbz	x0, 12, .L4098
	ldr	x0, [x29, 104]
	ldrh	w1, [x0, #:lo12:.LANCHOR101]
	adrp	x0, .LC251
	add	x0, x0, :lo12:.LC251
	bl	printf
.L4098:
	bl	zbuf_init
	adrp	x25, .LANCHOR197
	mov	w0, 16384
	bl	ftl_malloc
	adrp	x1, .LANCHOR192
	str	x0, [x1, #:lo12:.LANCHOR192]
	mov	w0, 16384
	bl	ftl_malloc
	str	x0, [x25, #:lo12:.LANCHOR197]
	mov	w0, 16384
	bl	ftl_malloc
	adrp	x1, .LANCHOR187
	str	x0, [x1, #:lo12:.LANCHOR187]
	mov	w0, 6
	ldrh	w1, [x23, #:lo12:.LANCHOR8]
	mul	w0, w1, w0
	bl	ftl_malloc
	adrp	x1, .LANCHOR4
	str	x0, [x1, #:lo12:.LANCHOR4]
	ldrb	w1, [x21, #:lo12:.LANCHOR79]
	ldrh	w0, [x22, #:lo12:.LANCHOR94]
	mul	w0, w0, w1
	lsl	w0, w0, 2
	bl	ftl_malloc
	adrp	x1, .LANCHOR118
	ldr	x2, [x25, #:lo12:.LANCHOR197]
	adrp	x25, .LANCHOR12
	str	x0, [x1, #:lo12:.LANCHOR118]
	adrp	x0, .LANCHOR117
	ldrh	w1, [x22, #:lo12:.LANCHOR94]
	str	x2, [x0, #:lo12:.LANCHOR117]
	ldrb	w0, [x21, #:lo12:.LANCHOR79]
	mul	w1, w1, w0
	lsl	w0, w1, 1
	adrp	x1, .LANCHOR11
	add	x3, x2, x0, sxtw 2
	str	x3, [x1, #:lo12:.LANCHOR11]
	ldrh	w1, [x23, #:lo12:.LANCHOR8]
	add	w1, w0, w1, lsr 1
	ldr	w0, [x19, #:lo12:.LANCHOR19]
	add	x1, x2, x1, sxtw 2
	str	x1, [x25, #:lo12:.LANCHOR12]
	tbz	x0, 12, .L4099
	adrp	x0, .LC252
	add	x0, x0, :lo12:.LC252
	bl	printf
.L4099:
	ldrh	w0, [x22, #:lo12:.LANCHOR94]
	ldrb	w21, [x21, #:lo12:.LANCHOR79]
	ldrh	w1, [x23, #:lo12:.LANCHOR8]
	ldrh	w22, [x24, #:lo12:.LANCHOR202]
	mul	w21, w0, w21
	ldr	w0, [x19, #:lo12:.LANCHOR19]
	add	w21, w1, w21, lsl 2
	lsl	w1, w1, 2
	lsl	w21, w21, 1
	add	w22, w1, w22, lsl 2
	add	w21, w21, 632
	add	w22, w22, 704
	tbz	x0, 12, .L4100
	ldrh	w3, [x20, #:lo12:.LANCHOR221]
	adrp	x0, .LC253
	mov	w2, w22
	mov	w1, w21
	add	x0, x0, :lo12:.LC253
	bl	printf
.L4100:
	ldrh	w0, [x20, #:lo12:.LANCHOR221]
	cmp	w21, w0
	bhi	.L4101
	cmp	w22, w0
	bls	.L4102
.L4101:
.L4155:
	b	.L4155
.L4079:
	add	w1, w1, 1
	lsl	w3, w3, 1
	and	w1, w1, 65535
	b	.L4078
.L4081:
	add	w4, w4, 1
	lsl	w1, w1, 1
	and	w4, w4, 65535
	b	.L4080
.L4084:
	adrp	x0, .LANCHOR35
	ldrb	w0, [x0, #:lo12:.LANCHOR35]
	cbz	w0, .L4087
	mov	w0, 1200
	strh	w10, [x11, #:lo12:.LANCHOR125]
	strh	w0, [x12, #:lo12:.LANCHOR126]
	strh	w10, [x8, #:lo12:.LANCHOR150]
	b	.L4087
.L4102:
	bl	sblk_init
	bl	ftl_info_blk_init
	cmn	w0, #1
	beq	.L4077
	bl	ftl_ext_info_init
	adrp	x19, .LANCHOR110
	bl	gc_init
	mov	w0, 1
	bl	pm_init
	bl	lpa_rebuild_hash
	ldr	x0, [x25, #:lo12:.LANCHOR12]
	mov	x1, 0
	add	x0, x0, 16
	bl	ftl_open_sblk_recovery
	ldr	x0, [x25, #:lo12:.LANCHOR12]
	add	x1, x0, 16
	add	x0, x0, 48
	bl	ftl_open_sblk_recovery
	ldr	x1, [x19, #:lo12:.LANCHOR110]
	ldr	w0, [x1, 8]
	add	w0, w0, 16
	str	w0, [x1, 8]
	ldr	x0, [x25, #:lo12:.LANCHOR12]
	add	x0, x0, 16
	bl	ftl_info_data_recovery
	ldr	x0, [x25, #:lo12:.LANCHOR12]
	add	x0, x0, 48
	bl	ftl_info_data_recovery
	ldr	x0, [x25, #:lo12:.LANCHOR12]
	add	x0, x0, 80
	bl	ftl_info_data_recovery
	bl	gc_recovery
	bl	pm_flush
	mov	w0, 1
	bl	ftl_total_vpn_update
	adrp	x0, .LANCHOR195
	ldrb	w0, [x0, #:lo12:.LANCHOR195]
	cbz	w0, .L4104
	ldr	x1, [x19, #:lo12:.LANCHOR110]
	ldr	w0, [x1, 68]
	add	w0, w0, 1
	str	w0, [x1, 68]
.L4104:
	bl	ftl_ext_info_flush
	mov	w0, 0
	bl	ftl_info_flush
	bl	print_ftl_debug_info
	ldr	x0, [x25, #:lo12:.LANCHOR12]
	ldrh	w0, [x0, 124]
	cbnz	w0, .L4111
	adrp	x0, .LANCHOR103
	adrp	x1, .LANCHOR107
	ldrh	w0, [x0, #:lo12:.LANCHOR103]
	ldrh	w1, [x1, #:lo12:.LANCHOR107]
	add	w0, w0, w1
	cmp	w0, 7
	ble	.L4111
.L4107:
	mov	w0, 0
.L4077:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
.L4111:
	adrp	x20, .LANCHOR103
	adrp	x21, .LANCHOR107
	add	x20, x20, :lo12:.LANCHOR103
	add	x21, x21, :lo12:.LANCHOR107
	mov	w19, 16384
.L4108:
	mov	w1, 1
	mov	w0, 0
	bl	zftl_do_gc
	mov	w1, 1
	mov	w0, w1
	bl	zftl_do_gc
	ldr	x0, [x25, #:lo12:.LANCHOR12]
	ldrh	w1, [x0, 124]
	cbnz	w1, .L4106
	ldrh	w1, [x0, 80]
	mov	w0, 65535
	cmp	w1, w0
	bne	.L4106
	ldrh	w0, [x20]
	ldrh	w1, [x21]
	add	w0, w0, w1
	cmp	w0, 7
	bgt	.L4107
.L4106:
	subs	w19, w19, #1
	bne	.L4108
	b	.L4107
	.size	zftl_init, .-zftl_init
	.section	.text.rk_ftl_init,"ax",@progbits
	.align	2
	.global	rk_ftl_init
	.type	rk_ftl_init, %function
rk_ftl_init:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	bl	nand_flash_init
	cbnz	w0, .L4159
	bl	zftl_init
.L4159:
	mov	w19, w0
	bl	idb_init
	mov	w1, w19
	adrp	x0, .LC254
	add	x0, x0, :lo12:.LC254
	bl	printf
	mov	w0, w19
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	rk_ftl_init, .-rk_ftl_init
	.section	.text.zftl_write,"ax",@progbits
	.align	2
	.global	zftl_write
	.type	zftl_write, %function
zftl_write:
	stp	x29, x30, [sp, -112]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w19, w0
	adrp	x0, .LANCHOR19
	stp	x21, x22, [sp, 32]
	stp	x25, x26, [sp, 64]
	mov	w20, w1
	ldr	w0, [x0, #:lo12:.LANCHOR19]
	mov	w21, w2
	stp	x23, x24, [sp, 48]
	mov	x25, x3
	stp	x27, x28, [sp, 80]
	tbz	x0, 12, .L4162
	ldr	w4, [x25]
	mov	w3, w2
	adrp	x0, .LC255
	mov	w2, w1
	add	x0, x0, :lo12:.LC255
	mov	w1, w19
	bl	printf
.L4162:
	cbnz	w19, .L4163
	adrp	x0, .LANCHOR67
	mov	w19, 24576
	ldr	w0, [x0, #:lo12:.LANCHOR67]
.L4164:
	cmp	w0, w20
	ccmp	w0, w21, 0, hi
	bcc	.L4182
	add	w1, w20, w21
	cmp	w0, w1
	bcc	.L4182
	adrp	x26, .LANCHOR131
	add	w19, w19, w20
	sub	w22, w21, #1
	adrp	x27, .LANCHOR66
	ldrb	w0, [x26, #:lo12:.LANCHOR131]
	add	w22, w22, w19
	adrp	x28, .LANCHOR57
	add	x27, x27, :lo12:.LANCHOR66
	add	x28, x28, :lo12:.LANCHOR57
	udiv	w24, w19, w0
	udiv	w22, w22, w0
	add	x0, x26, :lo12:.LANCHOR131
	str	x0, [x29, 104]
	mov	w20, w24
	sub	w23, w22, w24
	add	w23, w23, 1
.L4166:
	cbnz	w23, .L4175
	bl	ftl_write_commit
	adrp	x20, .LANCHOR103
	bl	ftl_flush
	adrp	x19, .LANCHOR107
	mov	w1, 1
	mov	w0, 0
	bl	zftl_do_gc
	adrp	x0, .LANCHOR12
	ldr	x0, [x0, #:lo12:.LANCHOR12]
	ldrh	w0, [x0, 124]
	cbnz	w0, .L4176
	ldrh	w0, [x20, #:lo12:.LANCHOR103]
	ldrh	w1, [x19, #:lo12:.LANCHOR107]
	add	w0, w0, w1
	cmp	w0, 11
	bgt	.L4177
.L4176:
	mov	w1, 1
	mov	w0, 0
	bl	zftl_do_gc
.L4177:
	add	x20, x20, :lo12:.LANCHOR103
	add	x19, x19, :lo12:.LANCHOR107
.L4178:
	ldrh	w0, [x20]
	ldrh	w1, [x19]
	add	w0, w0, w1
	cmp	w0, 7
	ble	.L4179
	mov	w0, 0
.L4161:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
.L4163:
	cmp	w19, 3
	bhi	.L4182
	lsl	w19, w19, 13
	mov	w0, 8192
	b	.L4164
.L4175:
	ldrb	w0, [x27]
	cbz	w0, .L4167
	ldrb	w0, [x28]
	cmp	w0, 2
	bhi	.L4167
	bl	ftl_write_commit
.L4167:
	mov	w0, 0
	bl	buf_alloc
	mov	x26, x0
	cbnz	x0, .L4168
	bl	ftl_write_commit
	b	.L4166
.L4168:
	strb	wzr, [x0, 57]
	cmp	w20, w24
	ldr	x0, [x29, 104]
	ccmp	w20, w22, 4, ne
	ldrb	w0, [x0]
	strb	w0, [x26, 56]
	bne	.L4171
	cmp	w20, w24
	bne	.L4172
	udiv	w1, w19, w0
	msub	w1, w1, w0, w19
	and	w1, w1, 255
	strb	w1, [x26, 57]
	sub	w0, w0, w1
	and	w0, w0, 255
	cmp	w21, w0
	csel	w0, w21, w0, cc
.L4190:
	strb	w0, [x26, 56]
.L4171:
	ldr	x4, [x26, 8]
	mov	x1, x25
	ldrb	w0, [x26, 57]
	sub	w23, w23, #1
	ldrb	w2, [x26, 56]
	ubfiz	x0, x0, 9, 8
	lsl	w2, w2, 9
	add	x0, x4, x0
	bl	ftl_memcpy
	adrp	x0, .LANCHOR110
	ldr	x1, [x0, #:lo12:.LANCHOR110]
	ldr	w0, [x1, 8]
	str	w20, [x26, 36]
	add	w20, w20, 1
	add	w2, w0, 1
	str	w2, [x1, 8]
	str	w0, [x26, 32]
	mov	x0, x26
	bl	ftl_write_buf
	ldrb	w0, [x26, 56]
	ubfiz	x0, x0, 9, 8
	add	x25, x25, x0
	b	.L4166
.L4172:
	add	w1, w19, w21
	msub	w0, w0, w20, w1
	b	.L4190
.L4179:
	mov	w1, 1
	mov	w0, 0
	bl	zftl_do_gc
	mov	w1, 1
	mov	w0, w1
	bl	zftl_do_gc
	b	.L4178
.L4182:
	mov	w0, -1
	b	.L4161
	.size	zftl_write, .-zftl_write
	.section	.text.zftl_sys_write,"ax",@progbits
	.align	2
	.global	zftl_sys_write
	.type	zftl_sys_write, %function
zftl_sys_write:
	mov	x3, x2
	mov	w2, w1
	mov	w1, w0
	mov	w0, 2
	b	zftl_write
	.size	zftl_sys_write, .-zftl_sys_write
	.section	.text.StorageSysDataStore,"ax",@progbits
	.align	2
	.global	StorageSysDataStore
	.type	StorageSysDataStore, %function
StorageSysDataStore:
	mov	x3, x1
	mov	w2, 1
	mov	w1, w0
	mov	w0, 2
	b	zftl_write
	.size	StorageSysDataStore, .-StorageSysDataStore
	.section	.text.FlashBootVendorWrite,"ax",@progbits
	.align	2
	.global	FlashBootVendorWrite
	.type	FlashBootVendorWrite, %function
FlashBootVendorWrite:
	mov	x3, x2
	mov	w2, w1
	add	w1, w0, 512
	mov	w0, 2
	b	zftl_write
	.size	FlashBootVendorWrite, .-FlashBootVendorWrite
	.section	.text.ftl_write,"ax",@progbits
	.align	2
	.global	ftl_write
	.type	ftl_write, %function
ftl_write:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w19, w2
	stp	x21, x22, [sp, 32]
	mov	x20, x3
	mov	w22, w1
	ands	w21, w0, 255
	bne	.L4195
	mov	w3, w2
	mov	w0, 0
	mov	x2, x20
	bl	idb_write_data
.L4195:
	mov	x3, x20
	mov	w2, w19
	mov	w1, w22
	mov	w0, w21
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	b	zftl_write
	.size	ftl_write, .-ftl_write
	.section	.text.ftl_vendor_write,"ax",@progbits
	.align	2
	.global	ftl_vendor_write
	.type	ftl_vendor_write, %function
ftl_vendor_write:
	mov	x3, x2
	mov	w2, w1
	add	w1, w0, 512
	mov	w0, 2
	b	zftl_write
	.size	ftl_vendor_write, .-ftl_vendor_write
	.section	.text.zftl_vendor_write,"ax",@progbits
	.align	2
	.global	zftl_vendor_write
	.type	zftl_vendor_write, %function
zftl_vendor_write:
	b	ftl_vendor_write
	.size	zftl_vendor_write, .-zftl_vendor_write
	.section	.text.zftl_discard,"ax",@progbits
	.align	2
	.global	zftl_discard
	.type	zftl_discard, %function
zftl_discard:
	stp	x29, x30, [sp, -128]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w19, w1
	adrp	x1, .LANCHOR67
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	ldr	w1, [x1, #:lo12:.LANCHOR67]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	cmp	w0, w1
	ccmp	w19, w1, 2, cc
	bhi	.L4221
	add	w2, w0, w19
	cmp	w1, w2
	bcc	.L4221
	adrp	x24, .LANCHOR241
	add	w22, w0, 24576
	adrp	x0, .LANCHOR19
	str	x0, [x29, 104]
	ldr	w1, [x24, #:lo12:.LANCHOR241]
	ldr	w2, [x0, #:lo12:.LANCHOR19]
	add	w1, w19, w1
	str	w1, [x24, #:lo12:.LANCHOR241]
	tbz	x2, 12, .L4201
	adrp	x0, .LC256
	mov	w4, 0
	mov	w3, w19
	mov	w2, w22
	add	x0, x0, :lo12:.LC256
	bl	printf
.L4201:
	adrp	x23, .LANCHOR110
	adrp	x26, .LANCHOR131
	ldr	x0, [x23, #:lo12:.LANCHOR110]
	ldr	w27, [x0, 8]
	add	w1, w27, 1
	str	w1, [x0, 8]
	bl	ftl_write_commit
	bl	ftl_flush
	ldrb	w21, [x26, #:lo12:.LANCHOR131]
	udiv	w20, w22, w21
	msub	w25, w20, w21, w22
	cbz	w25, .L4202
	sub	w21, w21, w25
	mov	w0, w20
	cmp	w21, w19
	csel	w21, w21, w19, ls
	bl	lpa_hash_get_ppa
	str	w0, [x29, 120]
	cmn	w0, #1
	bne	.L4203
	mov	w2, 0
	add	x1, x29, 120
	mov	w0, w20
	bl	pm_log2phys
.L4203:
	ldr	w0, [x29, 120]
	and	w28, w21, 65535
	cmn	w0, #1
	beq	.L4205
	mov	w0, 0
	bl	buf_alloc
	mov	x3, x0
	cbz	x0, .L4205
	strb	w25, [x0, 57]
	ubfiz	x25, x25, 9, 25
	strb	w21, [x0, 56]
	mov	w1, 0
	ldr	x0, [x0, 8]
	lsl	w2, w28, 9
	stp	w27, w20, [x3, 32]
	str	x3, [x29, 96]
	add	x0, x0, x25
	bl	ftl_memset
	ldr	x3, [x29, 96]
	mov	x0, x3
	bl	ftl_write_buf
	bl	ftl_write_commit
	ldr	x1, [x23, #:lo12:.LANCHOR110]
	ldr	w0, [x1, 76]
	add	w0, w0, 1
	str	w0, [x1, 76]
.L4205:
	add	w20, w20, 1
	sub	w19, w19, w28
.L4202:
	cbz	w19, .L4207
	bl	ftl_flush
.L4207:
	adrp	x25, .LANCHOR74
	add	x21, x26, :lo12:.LANCHOR131
	add	x25, x25, :lo12:.LANCHOR74
	mov	w0, -1
	str	w0, [x29, 124]
.L4208:
	ldrb	w0, [x21]
	cmp	w19, w0
	bcs	.L4213
	cbz	w19, .L4215
	mov	w0, w20
	bl	lpa_hash_get_ppa
	str	w0, [x29, 120]
	cmn	w0, #1
	bne	.L4216
	mov	w2, 0
	add	x1, x29, 120
	mov	w0, w20
	bl	pm_log2phys
.L4216:
	ldr	w0, [x29, 120]
	cmn	w0, #1
	beq	.L4215
	mov	w0, 0
	bl	buf_alloc
	mov	x21, x0
	cbz	x0, .L4215
	strb	wzr, [x0, 57]
	strb	w19, [x0, 56]
	stp	w27, w20, [x21, 32]
	ldrb	w0, [x26, #:lo12:.LANCHOR131]
	cmp	w19, w0
	bcc	.L4218
	adrp	x1, .LANCHOR242
	adrp	x0, .LC0
	mov	w2, 1493
	add	x1, x1, :lo12:.LANCHOR242
	add	x0, x0, :lo12:.LC0
	bl	printf
.L4218:
	ldr	x0, [x21, 8]
	lsl	w2, w19, 9
	mov	w1, 0
	bl	ftl_memset
	mov	x0, x21
	bl	ftl_write_buf
	bl	ftl_write_commit
	ldr	x1, [x23, #:lo12:.LANCHOR110]
	ldr	w0, [x1, 76]
	add	w0, w0, 1
	str	w0, [x1, 76]
.L4215:
	ldr	w1, [x24, #:lo12:.LANCHOR241]
	cmp	w1, 8192
	bls	.L4222
	ldr	x0, [x29, 104]
	ldr	w0, [x0, #:lo12:.LANCHOR19]
	tbz	x0, 12, .L4219
	adrp	x0, .LC256
	mov	w4, 0
	mov	w3, w19
	mov	w2, w22
	add	x0, x0, :lo12:.LC256
	bl	printf
.L4219:
	str	wzr, [x24, #:lo12:.LANCHOR241]
	bl	flt_sys_flush
	adrp	x0, .LANCHOR122
	mov	w1, 1
	str	w1, [x0, #:lo12:.LANCHOR122]
.L4222:
	mov	w0, 0
	b	.L4199
.L4213:
	mov	w0, w20
	bl	lpa_hash_get_ppa
	str	w0, [x29, 120]
	cmn	w0, #1
	beq	.L4209
	mov	w0, 0
	bl	buf_alloc
	mov	x28, x0
	cbz	x0, .L4211
	ldrb	w2, [x21]
	mov	w1, 0
	strb	w2, [x0, 56]
	strb	wzr, [x0, 57]
	ldr	x0, [x0, 8]
	lsl	w2, w2, 9
	stp	w27, w20, [x28, 32]
	bl	ftl_memset
	mov	x0, x28
	bl	ftl_write_buf
	bl	ftl_write_commit
.L4248:
	ldr	x1, [x23, #:lo12:.LANCHOR110]
	ldr	w0, [x1, 76]
	add	w0, w0, 1
	str	w0, [x1, 76]
.L4211:
	ldrb	w0, [x21]
	add	w20, w20, 1
	sub	w19, w19, w0
	b	.L4208
.L4209:
	mov	w2, 0
	add	x1, x29, 120
	mov	w0, w20
	bl	pm_log2phys
	ldr	w0, [x29, 120]
	cmn	w0, #1
	beq	.L4211
	add	x1, x29, 124
	mov	w2, 1
	mov	w0, w20
	bl	pm_log2phys
	adrp	x0, .LANCHOR31
	ldrh	w2, [x25]
	ldrb	w1, [x0, #:lo12:.LANCHOR31]
	mov	w0, 24
	sub	w0, w0, w1
	sub	w1, w0, w2
	mov	w0, 1
	lsl	w0, w0, w1
	ldr	w1, [x29, 120]
	sub	w0, w0, #1
	lsr	w1, w1, w2
	and	w0, w0, w1
	adrp	x1, .LANCHOR75
	ldrb	w1, [x1, #:lo12:.LANCHOR75]
	udiv	w0, w0, w1
	bl	ftl_vpn_decrement
	b	.L4248
.L4221:
	mov	w0, -1
.L4199:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 128
	ret
	.size	zftl_discard, .-zftl_discard
	.section	.text.ftl_discard,"ax",@progbits
	.align	2
	.global	ftl_discard
	.type	ftl_discard, %function
ftl_discard:
	mov	w0, w1
	mov	w1, w2
	b	zftl_discard
	.size	ftl_discard, .-ftl_discard
	.section	.text.dump_pm_blk,"ax",@progbits
	.align	2
	.global	dump_pm_blk
	.type	dump_pm_blk, %function
dump_pm_blk:
	stp	x29, x30, [sp, -48]!
	mov	w2, 4
	adrp	x0, .LC257
	add	x0, x0, :lo12:.LC257
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	adrp	x20, .LANCHOR110
	stp	x21, x22, [sp, 32]
	adrp	x21, .LANCHOR152
	ldr	x1, [x20, #:lo12:.LANCHOR110]
	mov	w19, 0
	mov	w22, 65535
	add	x1, x1, 704
	ldrh	w3, [x1, -6]
	bl	rknand_print_hex
	ldrh	w3, [x21, #:lo12:.LANCHOR152]
	add	x21, x21, :lo12:.LANCHOR152
	ldr	x1, [x20, #:lo12:.LANCHOR110]
	mov	w2, 2
	adrp	x0, .LC258
	add	x0, x0, :lo12:.LC258
	add	x1, x1, 416
	bl	rknand_print_hex
.L4251:
	ldrh	w0, [x21]
	cmp	w0, w19
	bhi	.L4253
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
.L4253:
	ldr	x0, [x20, #:lo12:.LANCHOR110]
	add	x0, x0, x19, sxtw 1
	ldrh	w0, [x0, 416]
	cmp	w0, w22
	beq	.L4252
	mov	x1, 0
	bl	ftl_sblk_dump
.L4252:
	add	w19, w19, 1
	and	w19, w19, 65535
	b	.L4251
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
	.section	.bss.IDByte,"aw",@nobits
	.align	2
	.set	.LANCHOR47,. + 0
	.type	IDByte, %object
	.size	IDByte, 32
IDByte:
	.zero	32
	.section	.bss._c_ftl_blk_pre_plane,"aw",@nobits
	.align	1
	.set	.LANCHOR8,. + 0
	.type	_c_ftl_blk_pre_plane, %object
	.size	_c_ftl_blk_pre_plane, 2
_c_ftl_blk_pre_plane:
	.zero	2
	.section	.bss._c_ftl_block_addr_log2,"aw",@nobits
	.align	1
	.set	.LANCHOR74,. + 0
	.type	_c_ftl_block_addr_log2, %object
	.size	_c_ftl_block_addr_log2, 2
_c_ftl_block_addr_log2:
	.zero	2
	.section	.bss._c_ftl_block_align_addr,"aw",@nobits
	.align	1
	.set	.LANCHOR111,. + 0
	.type	_c_ftl_block_align_addr, %object
	.size	_c_ftl_block_align_addr, 2
_c_ftl_block_align_addr:
	.zero	2
	.section	.bss._c_ftl_byte_pre_page,"aw",@nobits
	.align	1
	.set	.LANCHOR221,. + 0
	.type	_c_ftl_byte_pre_page, %object
	.size	_c_ftl_byte_pre_page, 2
_c_ftl_byte_pre_page:
	.zero	2
	.section	.bss._c_ftl_cs_bits,"aw",@nobits
	.set	.LANCHOR31,. + 0
	.type	_c_ftl_cs_bits, %object
	.size	_c_ftl_cs_bits, 1
_c_ftl_cs_bits:
	.zero	1
	.section	.bss._c_ftl_nand_blks_per_die,"aw",@nobits
	.align	1
	.type	_c_ftl_nand_blks_per_die, %object
	.size	_c_ftl_nand_blks_per_die, 2
_c_ftl_nand_blks_per_die:
	.zero	2
	.section	.bss._c_ftl_nand_die_num,"aw",@nobits
	.set	.LANCHOR112,. + 0
	.type	_c_ftl_nand_die_num, %object
	.size	_c_ftl_nand_die_num, 1
_c_ftl_nand_die_num:
	.zero	1
	.section	.bss._c_ftl_nand_planes_num,"aw",@nobits
	.set	.LANCHOR79,. + 0
	.type	_c_ftl_nand_planes_num, %object
	.size	_c_ftl_nand_planes_num, 1
_c_ftl_nand_planes_num:
	.zero	1
	.section	.bss._c_ftl_nand_type,"aw",@nobits
	.set	.LANCHOR78,. + 0
	.type	_c_ftl_nand_type, %object
	.size	_c_ftl_nand_type, 1
_c_ftl_nand_type:
	.zero	1
	.section	.bss._c_ftl_page_pre_blk,"aw",@nobits
	.align	1
	.set	.LANCHOR85,. + 0
	.type	_c_ftl_page_pre_blk, %object
	.size	_c_ftl_page_pre_blk, 2
_c_ftl_page_pre_blk:
	.zero	2
	.section	.bss._c_ftl_page_pre_slc_blk,"aw",@nobits
	.align	1
	.set	.LANCHOR94,. + 0
	.type	_c_ftl_page_pre_slc_blk, %object
	.size	_c_ftl_page_pre_slc_blk, 2
_c_ftl_page_pre_slc_blk:
	.zero	2
	.section	.bss._c_ftl_planes_per_die,"aw",@nobits
	.set	.LANCHOR75,. + 0
	.type	_c_ftl_planes_per_die, %object
	.size	_c_ftl_planes_per_die, 1
_c_ftl_planes_per_die:
	.zero	1
	.section	.bss._c_ftl_pm_page_num,"aw",@nobits
	.align	1
	.set	.LANCHOR202,. + 0
	.type	_c_ftl_pm_page_num, %object
	.size	_c_ftl_pm_page_num, 2
_c_ftl_pm_page_num:
	.zero	2
	.section	.bss._c_ftl_sec_per_page,"aw",@nobits
	.set	.LANCHOR131,. + 0
	.type	_c_ftl_sec_per_page, %object
	.size	_c_ftl_sec_per_page, 1
_c_ftl_sec_per_page:
	.zero	1
	.section	.bss._c_max_pm_sblk,"aw",@nobits
	.align	1
	.set	.LANCHOR152,. + 0
	.type	_c_max_pm_sblk, %object
	.size	_c_max_pm_sblk, 2
_c_max_pm_sblk:
	.zero	2
	.section	.bss._c_mix_max_slc_ec_count,"aw",@nobits
	.align	1
	.set	.LANCHOR126,. + 0
	.type	_c_mix_max_slc_ec_count, %object
	.size	_c_mix_max_slc_ec_count, 2
_c_mix_max_slc_ec_count:
	.zero	2
	.section	.bss._c_mix_max_xlc_ec_count,"aw",@nobits
	.align	1
	.set	.LANCHOR125,. + 0
	.type	_c_mix_max_xlc_ec_count, %object
	.size	_c_mix_max_xlc_ec_count, 2
_c_mix_max_xlc_ec_count:
	.zero	2
	.section	.bss._c_slc_to_xlc_ec_ratio,"aw",@nobits
	.align	1
	.set	.LANCHOR10,. + 0
	.type	_c_slc_to_xlc_ec_ratio, %object
	.size	_c_slc_to_xlc_ec_ratio, 2
_c_slc_to_xlc_ec_ratio:
	.zero	2
	.section	.bss._c_swl_slc_gc_th,"aw",@nobits
	.align	1
	.set	.LANCHOR149,. + 0
	.type	_c_swl_slc_gc_th, %object
	.size	_c_swl_slc_gc_th, 2
_c_swl_slc_gc_th:
	.zero	2
	.section	.bss._c_swl_xlc_gc_th,"aw",@nobits
	.align	1
	.set	.LANCHOR150,. + 0
	.type	_c_swl_xlc_gc_th, %object
	.size	_c_swl_xlc_gc_th, 2
_c_swl_xlc_gc_th:
	.zero	2
	.section	.bss._c_totle_data_density,"aw",@nobits
	.align	2
	.set	.LANCHOR240,. + 0
	.type	_c_totle_data_density, %object
	.size	_c_totle_data_density, 4
_c_totle_data_density:
	.zero	4
	.section	.bss._c_totle_log_page,"aw",@nobits
	.align	2
	.set	.LANCHOR128,. + 0
	.type	_c_totle_log_page, %object
	.size	_c_totle_log_page, 4
_c_totle_log_page:
	.zero	4
	.section	.bss._c_totle_phy_density,"aw",@nobits
	.align	2
	.set	.LANCHOR239,. + 0
	.type	_c_totle_phy_density, %object
	.size	_c_totle_phy_density, 4
_c_totle_phy_density:
	.zero	4
	.section	.bss._c_user_data_density,"aw",@nobits
	.align	2
	.set	.LANCHOR67,. + 0
	.type	_c_user_data_density, %object
	.size	_c_user_data_density, 4
_c_user_data_density:
	.zero	4
	.section	.bss._ftl_gc_tag_page_num,"aw",@nobits
	.set	.LANCHOR224,. + 0
	.type	_ftl_gc_tag_page_num, %object
	.size	_ftl_gc_tag_page_num, 1
_ftl_gc_tag_page_num:
	.zero	1
	.section	.bss._gc_after_discard_en,"aw",@nobits
	.align	2
	.set	.LANCHOR122,. + 0
	.type	_gc_after_discard_en, %object
	.size	_gc_after_discard_en, 4
_gc_after_discard_en:
	.zero	4
	.section	.bss._last_read_time,"aw",@nobits
	.align	2
	.type	_last_read_time, %object
	.size	_last_read_time, 4
_last_read_time:
	.zero	4
	.section	.bss._last_write_time,"aw",@nobits
	.align	2
	.type	_last_write_time, %object
	.size	_last_write_time, 4
_last_write_time:
	.zero	4
	.section	.bss._max_xlc_super_block,"aw",@nobits
	.align	1
	.set	.LANCHOR101,. + 0
	.type	_max_xlc_super_block, %object
	.size	_max_xlc_super_block, 2
_max_xlc_super_block:
	.zero	2
	.section	.bss._min_slc_super_block,"aw",@nobits
	.align	1
	.set	.LANCHOR98,. + 0
	.type	_min_slc_super_block, %object
	.size	_min_slc_super_block, 2
_min_slc_super_block:
	.zero	2
	.section	.bss.discard_sector_count,"aw",@nobits
	.align	2
	.set	.LANCHOR241,. + 0
	.type	discard_sector_count, %object
	.size	discard_sector_count, 4
discard_sector_count:
	.zero	4
	.section	.bss.fill_spare_size,"aw",@nobits
	.align	1
	.set	.LANCHOR53,. + 0
	.type	fill_spare_size, %object
	.size	fill_spare_size, 2
fill_spare_size:
	.zero	2
	.section	.bss.flash_ddr_tuning_sdr_read_count,"aw",@nobits
	.align	2
	.set	.LANCHOR169,. + 0
	.type	flash_ddr_tuning_sdr_read_count, %object
	.size	flash_ddr_tuning_sdr_read_count, 4
flash_ddr_tuning_sdr_read_count:
	.zero	4
	.section	.bss.flash_read_retry,"aw",@nobits
	.align	3
	.set	.LANCHOR171,. + 0
	.type	flash_read_retry, %object
	.size	flash_read_retry, 8
flash_read_retry:
	.zero	8
	.section	.bss.free_buf_count,"aw",@nobits
	.set	.LANCHOR57,. + 0
	.type	free_buf_count, %object
	.size	free_buf_count, 1
free_buf_count:
	.zero	1
	.section	.bss.free_mix_sblk,"aw",@nobits
	.align	1
	.set	.LANCHOR107,. + 0
	.type	free_mix_sblk, %object
	.size	free_mix_sblk, 2
free_mix_sblk:
	.zero	2
	.section	.bss.free_slc_sblk,"aw",@nobits
	.align	1
	.set	.LANCHOR103,. + 0
	.type	free_slc_sblk, %object
	.size	free_slc_sblk, 2
free_slc_sblk:
	.zero	2
	.section	.bss.free_xlc_sblk,"aw",@nobits
	.align	1
	.set	.LANCHOR105,. + 0
	.type	free_xlc_sblk, %object
	.size	free_xlc_sblk, 2
free_xlc_sblk:
	.zero	2
	.section	.bss.ftl_ext_info_data_buffer,"aw",@nobits
	.align	3
	.set	.LANCHOR197,. + 0
	.type	ftl_ext_info_data_buffer, %object
	.size	ftl_ext_info_data_buffer, 8
ftl_ext_info_data_buffer:
	.zero	8
	.section	.bss.ftl_ext_info_first_write,"aw",@nobits
	.set	.LANCHOR196,. + 0
	.type	ftl_ext_info_first_write, %object
	.size	ftl_ext_info_first_write, 1
ftl_ext_info_first_write:
	.zero	1
	.section	.bss.ftl_flush_jiffies,"aw",@nobits
	.align	2
	.set	.LANCHOR233,. + 0
	.type	ftl_flush_jiffies, %object
	.size	ftl_flush_jiffies, 4
ftl_flush_jiffies:
	.zero	4
	.section	.bss.ftl_info_data_buffer,"aw",@nobits
	.align	3
	.set	.LANCHOR192,. + 0
	.type	ftl_info_data_buffer, %object
	.size	ftl_info_data_buffer, 8
ftl_info_data_buffer:
	.zero	8
	.section	.bss.ftl_info_spare,"aw",@nobits
	.align	6
	.set	.LANCHOR190,. + 0
	.type	ftl_info_spare, %object
	.size	ftl_info_spare, 256
ftl_info_spare:
	.zero	256
	.section	.bss.ftl_low_format_cur_blk,"aw",@nobits
	.align	1
	.set	.LANCHOR68,. + 0
	.type	ftl_low_format_cur_blk, %object
	.size	ftl_low_format_cur_blk, 2
ftl_low_format_cur_blk:
	.zero	2
	.section	.bss.ftl_power_lost_flag,"aw",@nobits
	.set	.LANCHOR195,. + 0
	.type	ftl_power_lost_flag, %object
	.size	ftl_power_lost_flag, 1
ftl_power_lost_flag:
	.zero	1
	.section	.bss.ftl_sblk_lpa_tbl,"aw",@nobits
	.align	3
	.set	.LANCHOR117,. + 0
	.type	ftl_sblk_lpa_tbl, %object
	.size	ftl_sblk_lpa_tbl, 8
ftl_sblk_lpa_tbl:
	.zero	8
	.section	.bss.ftl_sblk_update_list,"aw",@nobits
	.align	3
	.set	.LANCHOR73,. + 0
	.type	ftl_sblk_update_list, %object
	.size	ftl_sblk_update_list, 16
ftl_sblk_update_list:
	.zero	16
	.section	.bss.ftl_sblk_update_list_offset,"aw",@nobits
	.align	1
	.set	.LANCHOR123,. + 0
	.type	ftl_sblk_update_list_offset, %object
	.size	ftl_sblk_update_list_offset, 2
ftl_sblk_update_list_offset:
	.zero	2
	.section	.bss.ftl_sblk_vpn,"aw",@nobits
	.align	3
	.set	.LANCHOR11,. + 0
	.type	ftl_sblk_vpn, %object
	.size	ftl_sblk_vpn, 8
ftl_sblk_vpn:
	.zero	8
	.section	.bss.ftl_sblk_vpn_update_id,"aw",@nobits
	.align	1
	.set	.LANCHOR72,. + 0
	.type	ftl_sblk_vpn_update_id, %object
	.size	ftl_sblk_vpn_update_id, 2
ftl_sblk_vpn_update_id:
	.zero	2
	.section	.bss.ftl_sys_info_first_write,"aw",@nobits
	.set	.LANCHOR194,. + 0
	.type	ftl_sys_info_first_write, %object
	.size	ftl_sys_info_first_write, 1
ftl_sys_info_first_write:
	.zero	1
	.section	.bss.ftl_tmp_buffer,"aw",@nobits
	.align	3
	.set	.LANCHOR187,. + 0
	.type	ftl_tmp_buffer, %object
	.size	ftl_tmp_buffer, 8
ftl_tmp_buffer:
	.zero	8
	.section	.bss.ftl_tmp_spare,"aw",@nobits
	.align	6
	.set	.LANCHOR188,. + 0
	.type	ftl_tmp_spare, %object
	.size	ftl_tmp_spare, 256
ftl_tmp_spare:
	.zero	256
	.section	.bss.ftl_vpn_update_count,"aw",@nobits
	.align	1
	.set	.LANCHOR121,. + 0
	.type	ftl_vpn_update_count, %object
	.size	ftl_vpn_update_count, 2
ftl_vpn_update_count:
	.zero	2
	.section	.bss.g_block_align_addr,"aw",@nobits
	.align	1
	.set	.LANCHOR2,. + 0
	.type	g_block_align_addr, %object
	.size	g_block_align_addr, 2
g_block_align_addr:
	.zero	2
	.section	.bss.g_buf,"aw",@nobits
	.align	3
	.set	.LANCHOR55,. + 0
	.type	g_buf, %object
	.size	g_buf, 2048
g_buf:
	.zero	2048
	.section	.bss.g_die_addr,"aw",@nobits
	.align	2
	.set	.LANCHOR145,. + 0
	.type	g_die_addr, %object
	.size	g_die_addr, 32
g_die_addr:
	.zero	32
	.section	.bss.g_die_cs_idx,"aw",@nobits
	.align	2
	.set	.LANCHOR29,. + 0
	.type	g_die_cs_idx, %object
	.size	g_die_cs_idx, 8
g_die_cs_idx:
	.zero	8
	.section	.bss.g_flash_3d_mlc_flag,"aw",@nobits
	.set	.LANCHOR80,. + 0
	.type	g_flash_3d_mlc_flag, %object
	.size	g_flash_3d_mlc_flag, 1
g_flash_3d_mlc_flag:
	.zero	1
	.section	.bss.g_flash_3d_tlc_flag,"aw",@nobits
	.set	.LANCHOR83,. + 0
	.type	g_flash_3d_tlc_flag, %object
	.size	g_flash_3d_tlc_flag, 1
g_flash_3d_tlc_flag:
	.zero	1
	.section	.bss.g_flash_blk_info,"aw",@nobits
	.align	3
	.set	.LANCHOR211,. + 0
	.type	g_flash_blk_info, %object
	.size	g_flash_blk_info, 4
g_flash_blk_info:
	.zero	4
	.section	.bss.g_flash_cur_mode,"aw",@nobits
	.align	3
	.set	.LANCHOR33,. + 0
	.type	g_flash_cur_mode, %object
	.size	g_flash_cur_mode, 4
g_flash_cur_mode:
	.zero	4
	.section	.bss.g_flash_interface_mode,"aw",@nobits
	.set	.LANCHOR48,. + 0
	.type	g_flash_interface_mode, %object
	.size	g_flash_interface_mode, 1
g_flash_interface_mode:
	.zero	1
	.section	.bss.g_flash_micron_3d_tlc_b05a,"aw",@nobits
	.set	.LANCHOR124,. + 0
	.type	g_flash_micron_3d_tlc_b05a, %object
	.size	g_flash_micron_3d_tlc_b05a, 1
g_flash_micron_3d_tlc_b05a:
	.zero	1
	.section	.bss.g_flash_micron_3d_tlc_b16a,"aw",@nobits
	.set	.LANCHOR217,. + 0
	.type	g_flash_micron_3d_tlc_b16a, %object
	.size	g_flash_micron_3d_tlc_b16a, 1
g_flash_micron_3d_tlc_b16a:
	.zero	1
	.section	.bss.g_flash_micron_3d_tlc_flag,"aw",@nobits
	.set	.LANCHOR35,. + 0
	.type	g_flash_micron_3d_tlc_flag, %object
	.size	g_flash_micron_3d_tlc_flag, 1
g_flash_micron_3d_tlc_flag:
	.zero	1
	.section	.bss.g_flash_multi_page_prog_en,"aw",@nobits
	.set	.LANCHOR44,. + 0
	.type	g_flash_multi_page_prog_en, %object
	.size	g_flash_multi_page_prog_en, 1
g_flash_multi_page_prog_en:
	.zero	1
	.section	.bss.g_flash_multi_page_read_en,"aw",@nobits
	.set	.LANCHOR183,. + 0
	.type	g_flash_multi_page_read_en, %object
	.size	g_flash_multi_page_read_en, 1
g_flash_multi_page_read_en:
	.zero	1
	.section	.bss.g_flash_page_buffer,"aw",@nobits
	.align	3
	.set	.LANCHOR173,. + 0
	.type	g_flash_page_buffer, %object
	.size	g_flash_page_buffer, 8
g_flash_page_buffer:
	.zero	8
	.section	.bss.g_flash_reversd_blks,"aw",@nobits
	.set	.LANCHOR216,. + 0
	.type	g_flash_reversd_blks, %object
	.size	g_flash_reversd_blks, 1
g_flash_reversd_blks:
	.zero	1
	.section	.bss.g_flash_six_addr,"aw",@nobits
	.set	.LANCHOR30,. + 0
	.type	g_flash_six_addr, %object
	.size	g_flash_six_addr, 1
g_flash_six_addr:
	.zero	1
	.section	.bss.g_flash_slc_mode,"aw",@nobits
	.set	.LANCHOR0,. + 0
	.type	g_flash_slc_mode, %object
	.size	g_flash_slc_mode, 1
g_flash_slc_mode:
	.zero	1
	.section	.bss.g_flash_spare_buffer,"aw",@nobits
	.align	3
	.set	.LANCHOR172,. + 0
	.type	g_flash_spare_buffer, %object
	.size	g_flash_spare_buffer, 8
g_flash_spare_buffer:
	.zero	8
	.section	.bss.g_flash_sys_spare_buffer,"aw",@nobits
	.align	3
	.set	.LANCHOR210,. + 0
	.type	g_flash_sys_spare_buffer, %object
	.size	g_flash_sys_spare_buffer, 8
g_flash_sys_spare_buffer:
	.zero	8
	.section	.bss.g_flash_tmp_page_buffer,"aw",@nobits
	.align	3
	.set	.LANCHOR163,. + 0
	.type	g_flash_tmp_page_buffer, %object
	.size	g_flash_tmp_page_buffer, 8
g_flash_tmp_page_buffer:
	.zero	8
	.section	.bss.g_flash_tmp_spare_buffer,"aw",@nobits
	.align	3
	.set	.LANCHOR165,. + 0
	.type	g_flash_tmp_spare_buffer, %object
	.size	g_flash_tmp_spare_buffer, 8
g_flash_tmp_spare_buffer:
	.zero	8
	.section	.bss.g_flash_toggle_mode_en,"aw",@nobits
	.set	.LANCHOR26,. + 0
	.type	g_flash_toggle_mode_en, %object
	.size	g_flash_toggle_mode_en, 1
g_flash_toggle_mode_en:
	.zero	1
	.section	.bss.g_flash_ymtc_3d_tlc_flag,"aw",@nobits
	.set	.LANCHOR36,. + 0
	.type	g_flash_ymtc_3d_tlc_flag, %object
	.size	g_flash_ymtc_3d_tlc_flag, 1
g_flash_ymtc_3d_tlc_flag:
	.zero	1
	.section	.bss.g_ftl_info_blk,"aw",@nobits
	.align	6
	.set	.LANCHOR191,. + 0
	.type	g_ftl_info_blk, %object
	.size	g_ftl_info_blk, 4
g_ftl_info_blk:
	.zero	4
	.section	.bss.g_gc_info,"aw",@nobits
	.align	3
	.set	.LANCHOR70,. + 0
	.type	g_gc_info, %object
	.size	g_gc_info, 2216
g_gc_info:
	.zero	2216
	.section	.bss.g_idb_ecc_bits,"aw",@nobits
	.set	.LANCHOR22,. + 0
	.type	g_idb_ecc_bits, %object
	.size	g_idb_ecc_bits, 1
g_idb_ecc_bits:
	.zero	1
	.section	.bss.g_idb_slc_mode_enable,"aw",@nobits
	.set	.LANCHOR24,. + 0
	.type	g_idb_slc_mode_enable, %object
	.size	g_idb_slc_mode_enable, 1
g_idb_slc_mode_enable:
	.zero	1
	.section	.bss.g_lsb_page_tbl,"aw",@nobits
	.align	2
	.set	.LANCHOR3,. + 0
	.type	g_lsb_page_tbl, %object
	.size	g_lsb_page_tbl, 1024
g_lsb_page_tbl:
	.zero	1024
	.section	.bss.g_maxRegNum,"aw",@nobits
	.set	.LANCHOR18,. + 0
	.type	g_maxRegNum, %object
	.size	g_maxRegNum, 1
g_maxRegNum:
	.zero	1
	.section	.bss.g_maxRetryCount,"aw",@nobits
	.set	.LANCHOR166,. + 0
	.type	g_maxRetryCount, %object
	.size	g_maxRetryCount, 1
g_maxRetryCount:
	.zero	1
	.section	.bss.g_msb_page_tbl,"aw",@nobits
	.align	2
	.set	.LANCHOR142,. + 0
	.type	g_msb_page_tbl, %object
	.size	g_msb_page_tbl, 2048
g_msb_page_tbl:
	.zero	2048
	.section	.bss.g_nand_max_die,"aw",@nobits
	.set	.LANCHOR23,. + 0
	.type	g_nand_max_die, %object
	.size	g_nand_max_die, 1
g_nand_max_die:
	.zero	1
	.section	.bss.g_nand_opt_para,"aw",@nobits
	.align	3
	.set	.LANCHOR25,. + 0
	.type	g_nand_opt_para, %object
	.size	g_nand_opt_para, 32
g_nand_opt_para:
	.zero	32
	.section	.bss.g_nandc_ecc_bits,"aw",@nobits
	.set	.LANCHOR49,. + 0
	.type	g_nandc_ecc_bits, %object
	.size	g_nandc_ecc_bits, 1
g_nandc_ecc_bits:
	.zero	1
	.section	.bss.g_nandc_tran_timeout,"aw",@nobits
	.set	.LANCHOR164,. + 0
	.type	g_nandc_tran_timeout, %object
	.size	g_nandc_tran_timeout, 1
g_nandc_tran_timeout:
	.zero	1
	.section	.bss.g_nandc_v6_master_info,"aw",@nobits
	.align	3
	.set	.LANCHOR52,. + 0
	.type	g_nandc_v6_master_info, %object
	.size	g_nandc_v6_master_info, 40
g_nandc_v6_master_info:
	.zero	40
	.section	.bss.g_nandc_ver,"aw",@nobits
	.set	.LANCHOR27,. + 0
	.type	g_nandc_ver, %object
	.size	g_nandc_ver, 1
g_nandc_ver:
	.zero	1
	.section	.bss.g_one_pass_program,"aw",@nobits
	.set	.LANCHOR81,. + 0
	.type	g_one_pass_program, %object
	.size	g_one_pass_program, 1
g_one_pass_program:
	.zero	1
	.section	.bss.g_pm_spare,"aw",@nobits
	.align	3
	.set	.LANCHOR207,. + 0
	.type	g_pm_spare, %object
	.size	g_pm_spare, 8
g_pm_spare:
	.zero	8
	.section	.bss.g_retryMode,"aw",@nobits
	.set	.LANCHOR16,. + 0
	.type	g_retryMode, %object
	.size	g_retryMode, 1
g_retryMode:
	.zero	1
	.section	.bss.g_slc_mode_addr2,"aw",@nobits
	.set	.LANCHOR1,. + 0
	.type	g_slc_mode_addr2, %object
	.size	g_slc_mode_addr2, 1
g_slc_mode_addr2:
	.zero	1
	.section	.bss.g_slc_mode_enable,"aw",@nobits
	.type	g_slc_mode_enable, %object
	.size	g_slc_mode_enable, 1
g_slc_mode_enable:
	.zero	1
	.section	.bss.g_slc_page_num,"aw",@nobits
	.align	1
	.set	.LANCHOR144,. + 0
	.type	g_slc_page_num, %object
	.size	g_slc_page_num, 2
g_slc_page_num:
	.zero	2
	.section	.bss.g_totle_phy_block,"aw",@nobits
	.align	1
	.set	.LANCHOR146,. + 0
	.type	g_totle_phy_block, %object
	.size	g_totle_phy_block, 2
g_totle_phy_block:
	.zero	2
	.section	.bss.gc_des_ppa_tbl,"aw",@nobits
	.align	3
	.set	.LANCHOR161,. + 0
	.type	gc_des_ppa_tbl, %object
	.size	gc_des_ppa_tbl, 8
gc_des_ppa_tbl:
	.zero	8
	.section	.bss.gc_free_slc_sblk_th,"aw",@nobits
	.align	1
	.set	.LANCHOR86,. + 0
	.type	gc_free_slc_sblk_th, %object
	.size	gc_free_slc_sblk_th, 2
gc_free_slc_sblk_th:
	.zero	2
	.section	.bss.gc_lpa_tbl,"aw",@nobits
	.align	3
	.set	.LANCHOR159,. + 0
	.type	gc_lpa_tbl, %object
	.size	gc_lpa_tbl, 8
gc_lpa_tbl:
	.zero	8
	.section	.bss.gc_mode,"aw",@nobits
	.set	.LANCHOR84,. + 0
	.type	gc_mode, %object
	.size	gc_mode, 1
gc_mode:
	.zero	1
	.section	.bss.gc_page_buf_id,"aw",@nobits
	.align	3
	.set	.LANCHOR82,. + 0
	.type	gc_page_buf_id, %object
	.size	gc_page_buf_id, 8
gc_page_buf_id:
	.zero	8
	.section	.bss.gc_pre_ppa_tbl,"aw",@nobits
	.align	3
	.set	.LANCHOR160,. + 0
	.type	gc_pre_ppa_tbl, %object
	.size	gc_pre_ppa_tbl, 8
gc_pre_ppa_tbl:
	.zero	8
	.section	.bss.gc_search_count,"aw",@nobits
	.align	2
	.set	.LANCHOR157,. + 0
	.type	gc_search_count, %object
	.size	gc_search_count, 4
gc_search_count:
	.zero	4
	.section	.bss.gc_slc_cache_index,"aw",@nobits
	.align	1
	.set	.LANCHOR88,. + 0
	.type	gc_slc_cache_index, %object
	.size	gc_slc_cache_index, 2
gc_slc_cache_index:
	.zero	2
	.section	.bss.gc_slc_data_index,"aw",@nobits
	.align	1
	.set	.LANCHOR87,. + 0
	.type	gc_slc_data_index, %object
	.size	gc_slc_data_index, 2
gc_slc_data_index:
	.zero	2
	.section	.bss.gc_slc_mode_slc_vpn_th,"aw",@nobits
	.align	1
	.set	.LANCHOR158,. + 0
	.type	gc_slc_mode_slc_vpn_th, %object
	.size	gc_slc_mode_slc_vpn_th, 2
gc_slc_mode_slc_vpn_th:
	.zero	2
	.section	.bss.gc_slc_mode_tlc_vpn_th,"aw",@nobits
	.align	1
	.set	.LANCHOR93,. + 0
	.type	gc_slc_mode_tlc_vpn_th, %object
	.size	gc_slc_mode_tlc_vpn_th, 2
gc_slc_mode_tlc_vpn_th:
	.zero	2
	.section	.bss.gc_slc_mode_vpn_th,"aw",@nobits
	.align	1
	.set	.LANCHOR69,. + 0
	.type	gc_slc_mode_vpn_th, %object
	.size	gc_slc_mode_vpn_th, 2
gc_slc_mode_vpn_th:
	.zero	2
	.section	.bss.gc_state,"aw",@nobits
	.set	.LANCHOR156,. + 0
	.type	gc_state, %object
	.size	gc_state, 1
gc_state:
	.zero	1
	.section	.bss.gc_tlc_mode_slc_vpn_th,"aw",@nobits
	.align	1
	.set	.LANCHOR102,. + 0
	.type	gc_tlc_mode_slc_vpn_th, %object
	.size	gc_tlc_mode_slc_vpn_th, 2
gc_tlc_mode_slc_vpn_th:
	.zero	2
	.section	.bss.gc_tlc_mode_tlc_vpn_th,"aw",@nobits
	.align	1
	.set	.LANCHOR100,. + 0
	.type	gc_tlc_mode_tlc_vpn_th, %object
	.size	gc_tlc_mode_tlc_vpn_th, 2
gc_tlc_mode_tlc_vpn_th:
	.zero	2
	.section	.bss.gc_valid_page_ppa,"aw",@nobits
	.align	3
	.set	.LANCHOR76,. + 0
	.type	gc_valid_page_ppa, %object
	.size	gc_valid_page_ppa, 8
gc_valid_page_ppa:
	.zero	8
	.section	.bss.gc_xlc_data_index,"aw",@nobits
	.align	1
	.set	.LANCHOR89,. + 0
	.type	gc_xlc_data_index, %object
	.size	gc_xlc_data_index, 2
gc_xlc_data_index:
	.zero	2
	.section	.bss.gc_xlc_search_index,"aw",@nobits
	.align	1
	.set	.LANCHOR96,. + 0
	.type	gc_xlc_search_index, %object
	.size	gc_xlc_search_index, 2
gc_xlc_search_index:
	.zero	2
	.section	.bss.gp_blk_info,"aw",@nobits
	.align	3
	.set	.LANCHOR9,. + 0
	.type	gp_blk_info, %object
	.size	gp_blk_info, 8
gp_blk_info:
	.zero	8
	.section	.bss.gp_data_slc_cache_head,"aw",@nobits
	.align	3
	.set	.LANCHOR90,. + 0
	.type	gp_data_slc_cache_head, %object
	.size	gp_data_slc_cache_head, 8
gp_data_slc_cache_head:
	.zero	8
	.section	.bss.gp_data_slc_data_head,"aw",@nobits
	.align	3
	.set	.LANCHOR95,. + 0
	.type	gp_data_slc_data_head, %object
	.size	gp_data_slc_data_head, 8
gp_data_slc_data_head:
	.zero	8
	.section	.bss.gp_data_xlc_data_head,"aw",@nobits
	.align	3
	.set	.LANCHOR92,. + 0
	.type	gp_data_xlc_data_head, %object
	.size	gp_data_xlc_data_head, 8
gp_data_xlc_data_head:
	.zero	8
	.section	.bss.gp_flash_check_buf,"aw",@nobits
	.align	3
	.set	.LANCHOR141,. + 0
	.type	gp_flash_check_buf, %object
	.size	gp_flash_check_buf, 8
gp_flash_check_buf:
	.zero	8
	.section	.bss.gp_flash_info,"aw",@nobits
	.align	3
	.set	.LANCHOR6,. + 0
	.type	gp_flash_info, %object
	.size	gp_flash_info, 8
gp_flash_info:
	.zero	8
	.section	.bss.gp_free_mix_head,"aw",@nobits
	.align	3
	.set	.LANCHOR108,. + 0
	.type	gp_free_mix_head, %object
	.size	gp_free_mix_head, 8
gp_free_mix_head:
	.zero	8
	.section	.bss.gp_free_slc_head,"aw",@nobits
	.align	3
	.set	.LANCHOR104,. + 0
	.type	gp_free_slc_head, %object
	.size	gp_free_slc_head, 8
gp_free_slc_head:
	.zero	8
	.section	.bss.gp_free_xlc_head,"aw",@nobits
	.align	3
	.set	.LANCHOR106,. + 0
	.type	gp_free_xlc_head, %object
	.size	gp_free_xlc_head, 8
gp_free_xlc_head:
	.zero	8
	.section	.bss.gp_ftl_ext_info,"aw",@nobits
	.align	3
	.set	.LANCHOR12,. + 0
	.type	gp_ftl_ext_info, %object
	.size	gp_ftl_ext_info, 8
gp_ftl_ext_info:
	.zero	8
	.section	.bss.gp_ftl_info,"aw",@nobits
	.align	3
	.set	.LANCHOR110,. + 0
	.type	gp_ftl_info, %object
	.size	gp_ftl_info, 8
gp_ftl_info:
	.zero	8
	.section	.bss.gp_nand_para_info,"aw",@nobits
	.align	3
	.set	.LANCHOR21,. + 0
	.type	gp_nand_para_info, %object
	.size	gp_nand_para_info, 8
gp_nand_para_info:
	.zero	8
	.section	.bss.gp_nandc,"aw",@nobits
	.align	3
	.set	.LANCHOR7,. + 0
	.type	gp_nandc, %object
	.size	gp_nandc, 8
gp_nandc:
	.zero	8
	.section	.bss.gp_sblk_list_tbl,"aw",@nobits
	.align	3
	.set	.LANCHOR4,. + 0
	.type	gp_sblk_list_tbl, %object
	.size	gp_sblk_list_tbl, 8
gp_sblk_list_tbl:
	.zero	8
	.section	.bss.idb_buf,"aw",@nobits
	.align	3
	.set	.LANCHOR138,. + 0
	.type	idb_buf, %object
	.size	idb_buf, 8
idb_buf:
	.zero	8
	.section	.bss.idb_last_lba,"aw",@nobits
	.align	2
	.set	.LANCHOR174,. + 0
	.type	idb_last_lba, %object
	.size	idb_last_lba, 4
idb_last_lba:
	.zero	4
	.section	.bss.idb_need_write_back,"aw",@nobits
	.align	2
	.set	.LANCHOR139,. + 0
	.type	idb_need_write_back, %object
	.size	idb_need_write_back, 4
idb_need_write_back:
	.zero	4
	.section	.bss.idb_write_enable,"aw",@nobits
	.set	.LANCHOR140,. + 0
	.type	idb_write_enable, %object
	.size	idb_write_enable, 1
idb_write_enable:
	.zero	1
	.section	.bss.lpa_hash,"aw",@nobits
	.align	3
	.set	.LANCHOR116,. + 0
	.type	lpa_hash, %object
	.size	lpa_hash, 512
lpa_hash:
	.zero	512
	.section	.bss.lpa_hash_index,"aw",@nobits
	.align	3
	.set	.LANCHOR118,. + 0
	.type	lpa_hash_index, %object
	.size	lpa_hash_index, 8
lpa_hash_index:
	.zero	8
	.section	.bss.nandc_ecc_sts,"aw",@nobits
	.align	3
	.type	nandc_ecc_sts, %object
	.size	nandc_ecc_sts, 16
nandc_ecc_sts:
	.zero	16
	.section	.bss.nandc_hw_seed,"aw",@nobits
	.set	.LANCHOR50,. + 0
	.type	nandc_hw_seed, %object
	.size	nandc_hw_seed, 1
nandc_hw_seed:
	.zero	1
	.section	.bss.nandc_randomizer_en,"aw",@nobits
	.set	.LANCHOR51,. + 0
	.type	nandc_randomizer_en, %object
	.size	nandc_randomizer_en, 1
nandc_randomizer_en:
	.zero	1
	.section	.bss.p_free_buf_head,"aw",@nobits
	.set	.LANCHOR56,. + 0
	.type	p_free_buf_head, %object
	.size	p_free_buf_head, 1
p_free_buf_head:
	.zero	1
	.section	.bss.p_read_ahead_ext_buf,"aw",@nobits
	.align	3
	.type	p_read_ahead_ext_buf, %object
	.size	p_read_ahead_ext_buf, 8
p_read_ahead_ext_buf:
	.zero	8
	.section	.bss.pm_first_write,"aw",@nobits
	.set	.LANCHOR208,. + 0
	.type	pm_first_write, %object
	.size	pm_first_write, 1
pm_first_write:
	.zero	1
	.section	.bss.pm_force_gc,"aw",@nobits
	.align	2
	.set	.LANCHOR148,. + 0
	.type	pm_force_gc, %object
	.size	pm_force_gc, 4
pm_force_gc:
	.zero	4
	.section	.bss.pm_gc_enable,"aw",@nobits
	.align	2
	.set	.LANCHOR204,. + 0
	.type	pm_gc_enable, %object
	.size	pm_gc_enable, 4
pm_gc_enable:
	.zero	4
	.section	.bss.pm_last_load_ram_id,"aw",@nobits
	.set	.LANCHOR223,. + 0
	.type	pm_last_load_ram_id, %object
	.size	pm_last_load_ram_id, 1
pm_last_load_ram_id:
	.zero	1
	.section	.bss.pm_last_update_ram_id,"aw",@nobits
	.set	.LANCHOR136,. + 0
	.type	pm_last_update_ram_id, %object
	.size	pm_last_update_ram_id, 1
pm_last_update_ram_id:
	.zero	1
	.section	.bss.pm_ram_info,"aw",@nobits
	.align	3
	.set	.LANCHOR135,. + 0
	.type	pm_ram_info, %object
	.size	pm_ram_info, 512
pm_ram_info:
	.zero	512
	.section	.bss.read_ahead_lpa,"aw",@nobits
	.align	2
	.set	.LANCHOR238,. + 0
	.type	read_ahead_lpa, %object
	.size	read_ahead_lpa, 4
read_ahead_lpa:
	.zero	4
	.section	.bss.read_buf_count,"aw",@nobits
	.set	.LANCHOR134,. + 0
	.type	read_buf_count, %object
	.size	read_buf_count, 1
read_buf_count:
	.zero	1
	.section	.bss.read_buf_head,"aw",@nobits
	.set	.LANCHOR133,. + 0
	.type	read_buf_head, %object
	.size	read_buf_head, 1
read_buf_head:
	.zero	1
	.section	.bss.sblk_gc_write_completed_queue_head,"aw",@nobits
	.set	.LANCHOR63,. + 0
	.type	sblk_gc_write_completed_queue_head, %object
	.size	sblk_gc_write_completed_queue_head, 1
sblk_gc_write_completed_queue_head:
	.zero	1
	.section	.bss.sblk_queue_head,"aw",@nobits
	.set	.LANCHOR59,. + 0
	.type	sblk_queue_head, %object
	.size	sblk_queue_head, 1
sblk_queue_head:
	.zero	1
	.section	.bss.sblk_read_completed_queue_head,"aw",@nobits
	.set	.LANCHOR62,. + 0
	.type	sblk_read_completed_queue_head, %object
	.size	sblk_read_completed_queue_head, 1
sblk_read_completed_queue_head:
	.zero	1
	.section	.bss.sblk_write_completed_queue_head,"aw",@nobits
	.set	.LANCHOR64,. + 0
	.type	sblk_write_completed_queue_head, %object
	.size	sblk_write_completed_queue_head, 1
sblk_write_completed_queue_head:
	.zero	1
	.section	.bss.slc_cache_sblk,"aw",@nobits
	.align	1
	.set	.LANCHOR99,. + 0
	.type	slc_cache_sblk, %object
	.size	slc_cache_sblk, 2
slc_cache_sblk:
	.zero	2
	.section	.bss.slc_data_sblk,"aw",@nobits
	.align	1
	.set	.LANCHOR97,. + 0
	.type	slc_data_sblk, %object
	.size	slc_data_sblk, 2
slc_data_sblk:
	.zero	2
	.section	.bss.write_buf_count,"aw",@nobits
	.set	.LANCHOR66,. + 0
	.type	write_buf_count, %object
	.size	write_buf_count, 1
write_buf_count:
	.zero	1
	.section	.bss.write_buf_head,"aw",@nobits
	.set	.LANCHOR65,. + 0
	.type	write_buf_head, %object
	.size	write_buf_head, 1
write_buf_head:
	.zero	1
	.section	.bss.write_commit_count,"aw",@nobits
	.set	.LANCHOR129,. + 0
	.type	write_commit_count, %object
	.size	write_commit_count, 1
write_commit_count:
	.zero	1
	.section	.bss.write_commit_head,"aw",@nobits
	.set	.LANCHOR182,. + 0
	.type	write_commit_head, %object
	.size	write_commit_head, 1
write_commit_head:
	.zero	1
	.section	.bss.xlc_data_sblk,"aw",@nobits
	.align	1
	.set	.LANCHOR91,. + 0
	.type	xlc_data_sblk, %object
	.size	xlc_data_sblk, 2
xlc_data_sblk:
	.zero	2
	.section	.bss.zftl_print_list_count,"aw",@nobits
	.align	1
	.set	.LANCHOR109,. + 0
	.type	zftl_print_list_count, %object
	.size	zftl_print_list_count, 2
zftl_print_list_count:
	.zero	2
	.section	.data.g_nand_para_info,"aw",@progbits
	.align	3
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
	.hword	768
	.byte	3
	.byte	2
	.hword	758
	.hword	5593
	.byte	0
	.byte	37
	.byte	60
	.byte	32
	.byte	2
	.byte	1
	.byte	4
	.byte	0
	.hword	256
	.byte	1
	.byte	-94
	.byte	0
	.byte	0
	.section	.data.hy_f26_ref_value,"aw",@progbits
	.align	3
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
	.section	.data.nand_opt_para,"aw",@progbits
	.align	3
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
	.zero	14
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
	.zero	14
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
	.zero	14
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
	.zero	14
	.section	.data.sd15_slc_rr,"aw",@progbits
	.align	3
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
	.section	.data.sd15_tlc_rr,"aw",@progbits
	.align	3
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
	.section	.data.tlc_b05a_prog_tbl,"aw",@progbits
	.align	3
	.set	.LANCHOR235,. + 0
	.type	tlc_b05a_prog_tbl, %object
	.size	tlc_b05a_prog_tbl, 1536
tlc_b05a_prog_tbl:
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	0
	.hword	9
	.hword	0
	.hword	11
	.hword	0
	.hword	13
	.hword	0
	.hword	15
	.hword	0
	.hword	17
	.hword	0
	.hword	19
	.hword	0
	.hword	21
	.hword	0
	.hword	23
	.hword	0
	.hword	25
	.hword	0
	.hword	27
	.hword	0
	.hword	29
	.hword	0
	.hword	31
	.hword	0
	.hword	33
	.hword	0
	.hword	35
	.hword	0
	.hword	37
	.hword	0
	.hword	39
	.hword	0
	.hword	41
	.hword	0
	.hword	43
	.hword	0
	.hword	45
	.hword	0
	.hword	47
	.hword	0
	.hword	49
	.hword	0
	.hword	51
	.hword	0
	.hword	53
	.hword	0
	.hword	55
	.hword	0
	.hword	25
	.hword	58
	.hword	0
	.hword	27
	.hword	61
	.hword	0
	.hword	29
	.hword	64
	.hword	0
	.hword	31
	.hword	67
	.hword	0
	.hword	33
	.hword	70
	.hword	0
	.hword	35
	.hword	73
	.hword	0
	.hword	37
	.hword	76
	.hword	0
	.hword	39
	.hword	79
	.hword	0
	.hword	41
	.hword	82
	.hword	0
	.hword	43
	.hword	85
	.hword	0
	.hword	45
	.hword	88
	.hword	0
	.hword	47
	.hword	91
	.hword	0
	.hword	49
	.hword	94
	.hword	0
	.hword	51
	.hword	97
	.hword	0
	.hword	53
	.hword	100
	.hword	0
	.hword	55
	.hword	103
	.hword	0
	.hword	58
	.hword	106
	.hword	0
	.hword	61
	.hword	109
	.hword	0
	.hword	64
	.hword	112
	.hword	0
	.hword	67
	.hword	115
	.hword	0
	.hword	70
	.hword	118
	.hword	0
	.hword	73
	.hword	121
	.hword	0
	.hword	76
	.hword	124
	.hword	0
	.hword	79
	.hword	127
	.hword	0
	.hword	82
	.hword	130
	.hword	0
	.hword	85
	.hword	133
	.hword	0
	.hword	88
	.hword	136
	.hword	0
	.hword	91
	.hword	139
	.hword	0
	.hword	94
	.hword	142
	.hword	0
	.hword	97
	.hword	145
	.hword	0
	.hword	100
	.hword	148
	.hword	0
	.hword	103
	.hword	151
	.hword	0
	.hword	106
	.hword	154
	.hword	0
	.hword	109
	.hword	157
	.hword	0
	.hword	112
	.hword	160
	.hword	0
	.hword	115
	.hword	163
	.hword	0
	.hword	118
	.hword	166
	.hword	0
	.hword	121
	.hword	169
	.hword	0
	.hword	124
	.hword	172
	.hword	0
	.hword	127
	.hword	175
	.hword	0
	.hword	130
	.hword	178
	.hword	0
	.hword	133
	.hword	181
	.hword	0
	.hword	136
	.hword	184
	.hword	0
	.hword	139
	.hword	187
	.hword	0
	.hword	142
	.hword	190
	.hword	0
	.hword	145
	.hword	193
	.hword	0
	.hword	148
	.hword	196
	.hword	0
	.hword	151
	.hword	199
	.hword	0
	.hword	154
	.hword	202
	.hword	0
	.hword	157
	.hword	205
	.hword	0
	.hword	160
	.hword	208
	.hword	0
	.hword	163
	.hword	211
	.hword	0
	.hword	166
	.hword	214
	.hword	0
	.hword	169
	.hword	217
	.hword	0
	.hword	172
	.hword	220
	.hword	0
	.hword	175
	.hword	223
	.hword	0
	.hword	178
	.hword	226
	.hword	0
	.hword	181
	.hword	229
	.hword	0
	.hword	184
	.hword	232
	.hword	0
	.hword	187
	.hword	235
	.hword	0
	.hword	190
	.hword	238
	.hword	0
	.hword	193
	.hword	241
	.hword	0
	.hword	196
	.hword	244
	.hword	0
	.hword	199
	.hword	247
	.hword	0
	.hword	202
	.hword	250
	.hword	0
	.hword	205
	.hword	253
	.hword	0
	.hword	208
	.hword	256
	.hword	0
	.hword	211
	.hword	259
	.hword	0
	.hword	214
	.hword	262
	.hword	0
	.hword	217
	.hword	265
	.hword	0
	.hword	220
	.hword	268
	.hword	0
	.hword	223
	.hword	271
	.hword	0
	.hword	226
	.hword	274
	.hword	0
	.hword	229
	.hword	277
	.hword	0
	.hword	232
	.hword	280
	.hword	0
	.hword	235
	.hword	283
	.hword	0
	.hword	238
	.hword	286
	.hword	0
	.hword	241
	.hword	289
	.hword	0
	.hword	244
	.hword	292
	.hword	0
	.hword	247
	.hword	295
	.hword	0
	.hword	250
	.hword	298
	.hword	0
	.hword	253
	.hword	301
	.hword	0
	.hword	256
	.hword	304
	.hword	0
	.hword	259
	.hword	307
	.hword	0
	.hword	262
	.hword	310
	.hword	0
	.hword	265
	.hword	313
	.hword	0
	.hword	268
	.hword	316
	.hword	0
	.hword	271
	.hword	319
	.hword	0
	.hword	274
	.hword	322
	.hword	0
	.hword	277
	.hword	325
	.hword	0
	.hword	280
	.hword	328
	.hword	0
	.hword	283
	.hword	331
	.hword	0
	.hword	286
	.hword	334
	.hword	0
	.hword	289
	.hword	337
	.hword	0
	.hword	292
	.hword	340
	.hword	0
	.hword	295
	.hword	343
	.hword	0
	.hword	298
	.hword	346
	.hword	0
	.hword	301
	.hword	349
	.hword	0
	.hword	304
	.hword	352
	.hword	0
	.hword	307
	.hword	355
	.hword	0
	.hword	310
	.hword	358
	.hword	0
	.hword	313
	.hword	361
	.hword	0
	.hword	316
	.hword	364
	.hword	0
	.hword	319
	.hword	367
	.hword	0
	.hword	322
	.hword	370
	.hword	0
	.hword	325
	.hword	373
	.hword	0
	.hword	328
	.hword	376
	.hword	0
	.hword	331
	.hword	379
	.hword	0
	.hword	334
	.hword	382
	.hword	0
	.hword	337
	.hword	385
	.hword	0
	.hword	340
	.hword	388
	.hword	0
	.hword	343
	.hword	391
	.hword	0
	.hword	346
	.hword	394
	.hword	0
	.hword	349
	.hword	397
	.hword	0
	.hword	352
	.hword	400
	.hword	0
	.hword	355
	.hword	403
	.hword	0
	.hword	358
	.hword	406
	.hword	0
	.hword	361
	.hword	409
	.hword	0
	.hword	364
	.hword	412
	.hword	0
	.hword	367
	.hword	415
	.hword	0
	.hword	370
	.hword	418
	.hword	0
	.hword	373
	.hword	421
	.hword	0
	.hword	376
	.hword	424
	.hword	0
	.hword	379
	.hword	427
	.hword	0
	.hword	382
	.hword	430
	.hword	0
	.hword	385
	.hword	433
	.hword	0
	.hword	388
	.hword	436
	.hword	0
	.hword	391
	.hword	439
	.hword	0
	.hword	394
	.hword	442
	.hword	0
	.hword	397
	.hword	445
	.hword	0
	.hword	400
	.hword	448
	.hword	0
	.hword	403
	.hword	451
	.hword	0
	.hword	406
	.hword	454
	.hword	0
	.hword	409
	.hword	457
	.hword	0
	.hword	412
	.hword	460
	.hword	0
	.hword	415
	.hword	463
	.hword	0
	.hword	418
	.hword	466
	.hword	0
	.hword	421
	.hword	469
	.hword	0
	.hword	424
	.hword	472
	.hword	0
	.hword	427
	.hword	475
	.hword	0
	.hword	430
	.hword	478
	.hword	0
	.hword	433
	.hword	481
	.hword	0
	.hword	436
	.hword	484
	.hword	0
	.hword	439
	.hword	487
	.hword	0
	.hword	442
	.hword	490
	.hword	0
	.hword	445
	.hword	493
	.hword	0
	.hword	448
	.hword	496
	.hword	0
	.hword	451
	.hword	499
	.hword	0
	.hword	454
	.hword	502
	.hword	0
	.hword	457
	.hword	505
	.hword	0
	.hword	460
	.hword	508
	.hword	0
	.hword	463
	.hword	511
	.hword	0
	.hword	466
	.hword	514
	.hword	0
	.hword	469
	.hword	517
	.hword	0
	.hword	472
	.hword	520
	.hword	0
	.hword	475
	.hword	523
	.hword	0
	.hword	478
	.hword	526
	.hword	0
	.hword	481
	.hword	529
	.hword	0
	.hword	484
	.hword	532
	.hword	0
	.hword	487
	.hword	535
	.hword	0
	.hword	490
	.hword	538
	.hword	0
	.hword	493
	.hword	541
	.hword	0
	.hword	496
	.hword	544
	.hword	0
	.hword	499
	.hword	547
	.hword	0
	.hword	502
	.hword	550
	.hword	0
	.hword	505
	.hword	553
	.hword	0
	.hword	508
	.hword	556
	.hword	0
	.hword	511
	.hword	559
	.hword	0
	.hword	514
	.hword	562
	.hword	0
	.hword	517
	.hword	565
	.hword	0
	.hword	520
	.hword	568
	.hword	0
	.hword	523
	.hword	571
	.hword	0
	.hword	526
	.hword	574
	.hword	0
	.hword	529
	.hword	577
	.hword	0
	.hword	532
	.hword	580
	.hword	0
	.hword	535
	.hword	583
	.hword	0
	.hword	538
	.hword	586
	.hword	0
	.hword	541
	.hword	589
	.hword	0
	.hword	544
	.hword	592
	.hword	0
	.hword	547
	.hword	595
	.hword	0
	.hword	550
	.hword	598
	.hword	0
	.hword	553
	.hword	601
	.hword	0
	.hword	556
	.hword	604
	.hword	0
	.hword	559
	.hword	607
	.hword	0
	.hword	562
	.hword	610
	.hword	0
	.hword	565
	.hword	613
	.hword	0
	.hword	568
	.hword	616
	.hword	0
	.hword	571
	.hword	619
	.hword	0
	.hword	574
	.hword	622
	.hword	0
	.hword	577
	.hword	625
	.hword	0
	.hword	580
	.hword	628
	.hword	0
	.hword	583
	.hword	631
	.hword	0
	.hword	586
	.hword	634
	.hword	0
	.hword	589
	.hword	637
	.hword	0
	.hword	592
	.hword	640
	.hword	0
	.hword	595
	.hword	643
	.hword	0
	.hword	598
	.hword	646
	.hword	0
	.hword	601
	.hword	649
	.hword	0
	.hword	604
	.hword	652
	.hword	0
	.hword	607
	.hword	655
	.hword	0
	.hword	610
	.hword	658
	.hword	0
	.hword	613
	.hword	661
	.hword	0
	.hword	616
	.hword	664
	.hword	0
	.hword	619
	.hword	667
	.hword	0
	.hword	622
	.hword	670
	.hword	0
	.hword	625
	.hword	673
	.hword	0
	.hword	628
	.hword	676
	.hword	0
	.hword	631
	.hword	679
	.hword	0
	.hword	634
	.hword	682
	.hword	0
	.hword	637
	.hword	685
	.hword	0
	.hword	640
	.hword	688
	.hword	0
	.hword	643
	.hword	691
	.hword	0
	.hword	646
	.hword	694
	.hword	0
	.hword	649
	.hword	697
	.hword	0
	.hword	652
	.hword	700
	.hword	0
	.hword	655
	.hword	703
	.hword	0
	.hword	658
	.hword	706
	.hword	0
	.hword	661
	.hword	709
	.hword	0
	.hword	664
	.hword	712
	.hword	0
	.hword	667
	.hword	715
	.hword	0
	.hword	670
	.hword	718
	.hword	0
	.hword	673
	.hword	721
	.hword	0
	.hword	676
	.hword	724
	.hword	0
	.hword	679
	.hword	727
	.hword	0
	.hword	682
	.hword	730
	.hword	0
	.hword	685
	.hword	733
	.hword	0
	.hword	688
	.hword	736
	.hword	0
	.hword	691
	.hword	739
	.hword	0
	.hword	694
	.hword	742
	.hword	0
	.hword	697
	.hword	745
	.hword	0
	.hword	700
	.hword	748
	.hword	0
	.hword	703
	.hword	751
	.hword	0
	.hword	706
	.hword	0
	.hword	709
	.hword	0
	.hword	712
	.hword	0
	.hword	715
	.hword	0
	.hword	718
	.hword	0
	.hword	721
	.hword	0
	.hword	724
	.hword	0
	.hword	727
	.hword	0
	.section	.data.tlc_prog_order,"aw",@progbits
	.align	3
	.set	.LANCHOR236,. + 0
	.type	tlc_prog_order, %object
	.size	tlc_prog_order, 768
tlc_prog_order:
	.hword	1
	.hword	9
	.hword	2
	.hword	17
	.hword	10
	.hword	3
	.hword	25
	.hword	18
	.hword	11
	.hword	33
	.hword	26
	.hword	19
	.hword	41
	.hword	34
	.hword	27
	.hword	49
	.hword	42
	.hword	35
	.hword	57
	.hword	50
	.hword	43
	.hword	65
	.hword	58
	.hword	51
	.hword	73
	.hword	66
	.hword	59
	.hword	81
	.hword	74
	.hword	67
	.hword	89
	.hword	82
	.hword	75
	.hword	97
	.hword	90
	.hword	83
	.hword	105
	.hword	98
	.hword	91
	.hword	113
	.hword	106
	.hword	99
	.hword	121
	.hword	114
	.hword	107
	.hword	129
	.hword	122
	.hword	115
	.hword	137
	.hword	130
	.hword	123
	.hword	145
	.hword	138
	.hword	131
	.hword	153
	.hword	146
	.hword	139
	.hword	161
	.hword	154
	.hword	147
	.hword	169
	.hword	162
	.hword	155
	.hword	177
	.hword	170
	.hword	163
	.hword	185
	.hword	178
	.hword	171
	.hword	193
	.hword	186
	.hword	179
	.hword	201
	.hword	194
	.hword	187
	.hword	209
	.hword	202
	.hword	195
	.hword	217
	.hword	210
	.hword	203
	.hword	225
	.hword	218
	.hword	211
	.hword	233
	.hword	226
	.hword	219
	.hword	241
	.hword	234
	.hword	227
	.hword	249
	.hword	242
	.hword	235
	.hword	257
	.hword	250
	.hword	243
	.hword	265
	.hword	258
	.hword	251
	.hword	273
	.hword	266
	.hword	259
	.hword	281
	.hword	274
	.hword	267
	.hword	289
	.hword	282
	.hword	275
	.hword	297
	.hword	290
	.hword	283
	.hword	305
	.hword	298
	.hword	291
	.hword	313
	.hword	306
	.hword	299
	.hword	321
	.hword	314
	.hword	307
	.hword	329
	.hword	322
	.hword	315
	.hword	337
	.hword	330
	.hword	323
	.hword	345
	.hword	338
	.hword	331
	.hword	353
	.hword	346
	.hword	339
	.hword	361
	.hword	354
	.hword	347
	.hword	369
	.hword	362
	.hword	355
	.hword	377
	.hword	370
	.hword	363
	.hword	385
	.hword	378
	.hword	371
	.hword	393
	.hword	386
	.hword	379
	.hword	401
	.hword	394
	.hword	387
	.hword	409
	.hword	402
	.hword	395
	.hword	417
	.hword	410
	.hword	403
	.hword	425
	.hword	418
	.hword	411
	.hword	433
	.hword	426
	.hword	419
	.hword	441
	.hword	434
	.hword	427
	.hword	449
	.hword	442
	.hword	435
	.hword	457
	.hword	450
	.hword	443
	.hword	465
	.hword	458
	.hword	451
	.hword	473
	.hword	466
	.hword	459
	.hword	481
	.hword	474
	.hword	467
	.hword	489
	.hword	482
	.hword	475
	.hword	497
	.hword	490
	.hword	483
	.hword	505
	.hword	498
	.hword	491
	.hword	513
	.hword	506
	.hword	499
	.hword	521
	.hword	514
	.hword	507
	.hword	529
	.hword	522
	.hword	515
	.hword	537
	.hword	530
	.hword	523
	.hword	545
	.hword	538
	.hword	531
	.hword	553
	.hword	546
	.hword	539
	.hword	561
	.hword	554
	.hword	547
	.hword	569
	.hword	562
	.hword	555
	.hword	577
	.hword	570
	.hword	563
	.hword	585
	.hword	578
	.hword	571
	.hword	593
	.hword	586
	.hword	579
	.hword	601
	.hword	594
	.hword	587
	.hword	609
	.hword	602
	.hword	595
	.hword	617
	.hword	610
	.hword	603
	.hword	625
	.hword	618
	.hword	611
	.hword	633
	.hword	626
	.hword	619
	.hword	641
	.hword	634
	.hword	627
	.hword	649
	.hword	642
	.hword	635
	.hword	657
	.hword	650
	.hword	643
	.hword	665
	.hword	658
	.hword	651
	.hword	673
	.hword	666
	.hword	659
	.hword	681
	.hword	674
	.hword	667
	.hword	689
	.hword	682
	.hword	675
	.hword	697
	.hword	690
	.hword	683
	.hword	705
	.hword	698
	.hword	691
	.hword	713
	.hword	706
	.hword	699
	.hword	721
	.hword	714
	.hword	707
	.hword	729
	.hword	722
	.hword	715
	.hword	737
	.hword	730
	.hword	723
	.hword	745
	.hword	738
	.hword	731
	.hword	753
	.hword	746
	.hword	739
	.hword	761
	.hword	754
	.hword	747
	.hword	769
	.hword	762
	.hword	755
	.hword	777
	.hword	770
	.hword	763
	.hword	785
	.hword	778
	.hword	771
	.hword	793
	.hword	786
	.hword	779
	.hword	801
	.hword	794
	.hword	787
	.hword	809
	.hword	802
	.hword	795
	.hword	817
	.hword	810
	.hword	803
	.hword	825
	.hword	818
	.hword	811
	.hword	833
	.hword	826
	.hword	819
	.hword	841
	.hword	834
	.hword	827
	.hword	849
	.hword	842
	.hword	835
	.hword	857
	.hword	850
	.hword	843
	.hword	865
	.hword	858
	.hword	851
	.hword	873
	.hword	866
	.hword	859
	.hword	881
	.hword	874
	.hword	867
	.hword	889
	.hword	882
	.hword	875
	.hword	897
	.hword	890
	.hword	883
	.hword	905
	.hword	898
	.hword	891
	.hword	913
	.hword	906
	.hword	899
	.hword	921
	.hword	914
	.hword	907
	.hword	929
	.hword	922
	.hword	915
	.hword	937
	.hword	930
	.hword	923
	.hword	945
	.hword	938
	.hword	931
	.hword	953
	.hword	946
	.hword	939
	.hword	961
	.hword	954
	.hword	947
	.hword	969
	.hword	962
	.hword	955
	.hword	977
	.hword	970
	.hword	963
	.hword	985
	.hword	978
	.hword	971
	.hword	993
	.hword	986
	.hword	979
	.hword	1001
	.hword	994
	.hword	987
	.hword	1009
	.hword	1002
	.hword	995
	.hword	1017
	.hword	1010
	.hword	1003
	.hword	1018
	.hword	1011
	.hword	1019
	.section	.data.zftl_debug,"aw",@progbits
	.align	2
	.set	.LANCHOR19,. + 0
	.type	zftl_debug, %object
	.size	zftl_debug, 4
zftl_debug:
	.word	17476
	.section	.data.zftl_nand_flash_para_tbl,"aw",@progbits
	.align	3
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
	.hword	768
	.byte	3
	.byte	2
	.hword	758
	.hword	5593
	.byte	0
	.byte	37
	.byte	60
	.byte	32
	.byte	3
	.byte	1
	.byte	4
	.byte	0
	.hword	256
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
	.hword	768
	.byte	3
	.byte	2
	.hword	1478
	.hword	5593
	.byte	0
	.byte	37
	.byte	60
	.byte	32
	.byte	3
	.byte	1
	.byte	4
	.byte	0
	.hword	256
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
	.hword	384
	.byte	3
	.byte	2
	.hword	1446
	.hword	1497
	.byte	0
	.byte	36
	.byte	60
	.byte	32
	.byte	3
	.byte	1
	.byte	4
	.byte	0
	.hword	256
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
	.hword	256
	.byte	2
	.byte	2
	.hword	1074
	.hword	17881
	.byte	2
	.byte	35
	.byte	40
	.byte	32
	.byte	3
	.byte	1
	.byte	4
	.byte	0
	.hword	256
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
	.hword	256
	.byte	2
	.byte	1
	.hword	2092
	.hword	17857
	.byte	2
	.byte	33
	.byte	40
	.byte	32
	.byte	3
	.byte	1
	.byte	1
	.byte	0
	.hword	256
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
	.hword	256
	.byte	2
	.byte	2
	.hword	2106
	.hword	17881
	.byte	2
	.byte	35
	.byte	40
	.byte	32
	.byte	3
	.byte	1
	.byte	4
	.byte	0
	.hword	256
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
	.hword	256
	.byte	2
	.byte	1
	.hword	1056
	.hword	17857
	.byte	2
	.byte	35
	.byte	40
	.byte	32
	.byte	3
	.byte	1
	.byte	4
	.byte	0
	.hword	256
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
	.hword	256
	.byte	2
	.byte	1
	.hword	1060
	.hword	17857
	.byte	2
	.byte	34
	.byte	40
	.byte	32
	.byte	3
	.byte	1
	.byte	4
	.byte	0
	.hword	256
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
	.hword	256
	.byte	2
	.byte	2
	.hword	1066
	.hword	17881
	.byte	2
	.byte	34
	.byte	40
	.byte	32
	.byte	3
	.byte	1
	.byte	1
	.byte	0
	.hword	256
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
	.hword	256
	.byte	2
	.byte	1
	.hword	1060
	.hword	17857
	.byte	2
	.byte	33
	.byte	40
	.byte	32
	.byte	3
	.byte	1
	.byte	1
	.byte	0
	.hword	256
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
	.hword	256
	.byte	2
	.byte	2
	.hword	1058
	.hword	17881
	.byte	2
	.byte	33
	.byte	40
	.byte	32
	.byte	3
	.byte	1
	.byte	1
	.byte	0
	.hword	256
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
	.hword	256
	.byte	2
	.byte	2
	.hword	1074
	.hword	17881
	.byte	2
	.byte	35
	.byte	40
	.byte	32
	.byte	3
	.byte	1
	.byte	4
	.byte	0
	.hword	256
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
	.hword	256
	.byte	2
	.byte	2
	.hword	2106
	.hword	17881
	.byte	2
	.byte	68
	.byte	40
	.byte	32
	.byte	3
	.byte	1
	.byte	4
	.byte	0
	.hword	256
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
	.hword	256
	.byte	2
	.byte	2
	.hword	1074
	.hword	17881
	.byte	2
	.byte	68
	.byte	40
	.byte	32
	.byte	3
	.byte	1
	.byte	4
	.byte	0
	.hword	256
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
	.hword	256
	.byte	2
	.byte	2
	.hword	1058
	.hword	17881
	.byte	2
	.byte	66
	.byte	40
	.byte	32
	.byte	3
	.byte	1
	.byte	4
	.byte	0
	.hword	256
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
	.hword	256
	.byte	2
	.byte	2
	.hword	1066
	.hword	17881
	.byte	2
	.byte	67
	.byte	40
	.byte	32
	.byte	3
	.byte	1
	.byte	1
	.byte	0
	.hword	256
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
	.hword	256
	.byte	2
	.byte	1
	.hword	1060
	.hword	17857
	.byte	2
	.byte	66
	.byte	40
	.byte	32
	.byte	2
	.byte	1
	.byte	1
	.byte	0
	.hword	256
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
	.hword	512
	.byte	2
	.byte	1
	.hword	1048
	.hword	9671
	.byte	5
	.byte	19
	.byte	70
	.byte	32
	.byte	1
	.byte	0
	.byte	4
	.byte	0
	.hword	512
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
	.hword	512
	.byte	2
	.byte	2
	.hword	700
	.hword	479
	.byte	4
	.byte	18
	.byte	60
	.byte	32
	.byte	1
	.byte	0
	.byte	1
	.byte	0
	.hword	512
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
	.hword	256
	.byte	2
	.byte	2
	.hword	1064
	.hword	479
	.byte	3
	.byte	17
	.byte	40
	.byte	32
	.byte	1
	.byte	0
	.byte	1
	.byte	0
	.hword	256
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
	.hword	512
	.byte	2
	.byte	2
	.hword	1024
	.hword	479
	.byte	4
	.byte	18
	.byte	60
	.byte	32
	.byte	1
	.byte	0
	.byte	1
	.byte	0
	.hword	512
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
	.hword	512
	.byte	2
	.byte	1
	.hword	1024
	.hword	455
	.byte	4
	.byte	18
	.byte	60
	.byte	32
	.byte	1
	.byte	0
	.byte	1
	.byte	0
	.hword	512
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
	.hword	256
	.byte	2
	.byte	4
	.hword	1024
	.hword	449
	.byte	3
	.byte	17
	.byte	40
	.byte	32
	.byte	1
	.byte	0
	.byte	1
	.byte	0
	.hword	256
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
	.hword	512
	.byte	2
	.byte	2
	.hword	1024
	.hword	479
	.byte	3
	.byte	17
	.byte	40
	.byte	32
	.byte	1
	.byte	0
	.byte	1
	.byte	0
	.hword	512
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
	.hword	512
	.byte	2
	.byte	1
	.hword	2184
	.hword	9671
	.byte	5
	.byte	19
	.byte	70
	.byte	32
	.byte	1
	.byte	0
	.byte	4
	.byte	0
	.hword	512
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
	.hword	512
	.byte	2
	.byte	1
	.hword	1044
	.hword	471
	.byte	3
	.byte	17
	.byte	40
	.byte	32
	.byte	1
	.byte	0
	.byte	1
	.byte	0
	.hword	512
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
	.hword	512
	.byte	2
	.byte	1
	.hword	2184
	.hword	9671
	.byte	5
	.byte	19
	.byte	70
	.byte	32
	.byte	1
	.byte	0
	.byte	4
	.byte	0
	.hword	512
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
	.hword	512
	.byte	2
	.byte	1
	.hword	2184
	.hword	9671
	.byte	5
	.byte	19
	.byte	70
	.byte	32
	.byte	1
	.byte	0
	.byte	4
	.byte	0
	.hword	512
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
	.hword	512
	.byte	2
	.byte	1
	.hword	2184
	.hword	9671
	.byte	5
	.byte	19
	.byte	70
	.byte	32
	.byte	1
	.byte	0
	.byte	4
	.byte	0
	.hword	512
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
	.hword	256
	.byte	2
	.byte	1
	.hword	2144
	.hword	-23097
	.byte	8
	.byte	21
	.byte	70
	.byte	32
	.byte	1
	.byte	0
	.byte	8
	.byte	0
	.hword	256
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
	.hword	512
	.byte	2
	.byte	2
	.hword	1024
	.hword	479
	.byte	3
	.byte	17
	.byte	40
	.byte	32
	.byte	1
	.byte	0
	.byte	1
	.byte	0
	.hword	512
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
	.hword	768
	.byte	3
	.byte	1
	.hword	1440
	.hword	3527
	.byte	0
	.byte	19
	.byte	70
	.byte	32
	.byte	1
	.byte	0
	.byte	1
	.byte	0
	.hword	1024
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
	.hword	2304
	.byte	3
	.byte	1
	.hword	1008
	.hword	3521
	.byte	0
	.byte	19
	.byte	70
	.byte	32
	.byte	1
	.byte	0
	.byte	1
	.byte	0
	.hword	4096
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
	.hword	1024
	.byte	2
	.byte	1
	.hword	2192
	.hword	9671
	.byte	10
	.byte	19
	.byte	70
	.byte	32
	.byte	1
	.byte	0
	.byte	1
	.byte	0
	.hword	1024
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
	.hword	1152
	.byte	3
	.byte	2
	.hword	1006
	.hword	-27169
	.byte	13
	.byte	81
	.byte	70
	.byte	32
	.byte	1
	.byte	0
	.byte	4
	.byte	0
	.hword	2048
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
	.hword	256
	.byte	2
	.byte	2
	.hword	1056
	.hword	455
	.byte	2
	.byte	6
	.byte	40
	.byte	32
	.byte	3
	.byte	1
	.byte	3
	.byte	0
	.hword	256
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
	.hword	256
	.byte	2
	.byte	2
	.hword	1066
	.hword	473
	.byte	1
	.byte	7
	.byte	40
	.byte	32
	.byte	4
	.byte	1
	.byte	3
	.byte	0
	.hword	256
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
	.hword	256
	.byte	2
	.byte	2
	.hword	1060
	.hword	473
	.byte	2
	.byte	5
	.byte	40
	.byte	32
	.byte	4
	.byte	1
	.byte	3
	.byte	0
	.hword	256
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
	.hword	256
	.byte	2
	.byte	2
	.hword	1046
	.hword	473
	.byte	1
	.byte	3
	.byte	40
	.byte	32
	.byte	4
	.byte	1
	.byte	3
	.byte	0
	.hword	256
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
	.hword	256
	.byte	2
	.byte	2
	.hword	2092
	.hword	473
	.byte	2
	.byte	5
	.byte	40
	.byte	32
	.byte	3
	.byte	1
	.byte	3
	.byte	0
	.hword	256
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
	.hword	256
	.byte	2
	.byte	2
	.hword	1056
	.hword	473
	.byte	2
	.byte	5
	.byte	40
	.byte	32
	.byte	4
	.byte	1
	.byte	3
	.byte	0
	.hword	256
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
	.hword	388
	.byte	2
	.byte	2
	.hword	1362
	.hword	473
	.byte	9
	.byte	8
	.byte	40
	.byte	32
	.byte	3
	.byte	1
	.byte	3
	.byte	0
	.hword	512
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
	.hword	512
	.byte	2
	.byte	1
	.hword	1024
	.hword	455
	.byte	4
	.byte	17
	.byte	40
	.byte	32
	.byte	1
	.byte	0
	.byte	1
	.byte	0
	.hword	512
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
	.hword	512
	.byte	2
	.byte	2
	.hword	1024
	.hword	455
	.byte	4
	.byte	17
	.byte	40
	.byte	32
	.byte	1
	.byte	0
	.byte	1
	.byte	0
	.hword	512
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
	.hword	256
	.byte	2
	.byte	4
	.hword	1024
	.hword	449
	.byte	3
	.byte	17
	.byte	40
	.byte	32
	.byte	1
	.byte	0
	.byte	1
	.byte	0
	.hword	256
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
	.hword	256
	.byte	2
	.byte	4
	.hword	1024
	.hword	449
	.byte	3
	.byte	17
	.byte	40
	.byte	32
	.byte	1
	.byte	0
	.byte	1
	.byte	0
	.hword	256
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
	.hword	256
	.byte	2
	.byte	4
	.hword	1024
	.hword	449
	.byte	1
	.byte	0
	.byte	24
	.byte	32
	.byte	1
	.byte	0
	.byte	1
	.byte	0
	.hword	256
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
	.hword	2304
	.byte	3
	.byte	1
	.hword	1008
	.hword	3521
	.byte	0
	.byte	19
	.byte	70
	.byte	32
	.byte	1
	.byte	0
	.byte	1
	.byte	0
	.hword	4096
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
	.hword	792
	.byte	2
	.byte	1
	.hword	688
	.hword	1217
	.byte	11
	.byte	50
	.byte	40
	.byte	32
	.byte	3
	.byte	1
	.byte	1
	.byte	0
	.hword	1024
	.byte	1
	.byte	-38
	.byte	-33
	.byte	0
	.section	.rodata.__func__.10004,"a",@progbits
	.align	3
	.set	.LANCHOR242,. + 0
	.type	__func__.10004, %object
	.size	__func__.10004, 13
__func__.10004:
	.string	"_ftl_discard"
	.section	.rodata.__func__.10150,"a",@progbits
	.align	3
	.set	.LANCHOR225,. + 0
	.type	__func__.10150, %object
	.size	__func__.10150, 12
__func__.10150:
	.string	"gc_recovery"
	.section	.rodata.__func__.10160,"a",@progbits
	.align	3
	.set	.LANCHOR71,. + 0
	.type	__func__.10160, %object
	.size	__func__.10160, 12
__func__.10160:
	.string	"gc_add_sblk"
	.section	.rodata.__func__.10207,"a",@progbits
	.align	3
	.set	.LANCHOR185,. + 0
	.type	__func__.10207, %object
	.size	__func__.10207, 21
__func__.10207:
	.string	"gc_check_data_one_wl"
	.section	.rodata.__func__.10239,"a",@progbits
	.align	3
	.set	.LANCHOR226,. + 0
	.type	__func__.10239, %object
	.size	__func__.10239, 22
__func__.10239:
	.string	"gc_update_l2p_map_new"
	.section	.rodata.__func__.10252,"a",@progbits
	.align	3
	.set	.LANCHOR77,. + 0
	.type	__func__.10252, %object
	.size	__func__.10252, 19
__func__.10252:
	.string	"gc_write_completed"
	.section	.rodata.__func__.10282,"a",@progbits
	.align	3
	.set	.LANCHOR234,. + 0
	.type	__func__.10282, %object
	.size	__func__.10282, 16
__func__.10282:
	.string	"gc_do_copy_back"
	.section	.rodata.__func__.10309,"a",@progbits
	.align	3
	.set	.LANCHOR127,. + 0
	.type	__func__.10309, %object
	.size	__func__.10309, 16
__func__.10309:
	.string	"gc_free_src_blk"
	.section	.rodata.__func__.10353,"a",@progbits
	.align	3
	.set	.LANCHOR227,. + 0
	.type	__func__.10353, %object
	.size	__func__.10353, 16
__func__.10353:
	.string	"gc_scan_src_blk"
	.section	.rodata.__func__.10414,"a",@progbits
	.align	3
	.set	.LANCHOR228,. + 0
	.type	__func__.10414, %object
	.size	__func__.10414, 20
__func__.10414:
	.string	"gc_scan_static_data"
	.section	.rodata.__func__.10508,"a",@progbits
	.align	3
	.set	.LANCHOR237,. + 0
	.type	__func__.10508, %object
	.size	__func__.10508, 11
__func__.10508:
	.string	"zftl_do_gc"
	.section	.rodata.__func__.10603,"a",@progbits
	.align	3
	.set	.LANCHOR5,. + 0
	.type	__func__.10603, %object
	.size	__func__.10603, 18
__func__.10603:
	.string	"_list_remove_node"
	.section	.rodata.__func__.10628,"a",@progbits
	.align	3
	.set	.LANCHOR13,. + 0
	.type	__func__.10628, %object
	.size	__func__.10628, 23
__func__.10628:
	.string	"_list_update_data_list"
	.section	.rodata.__func__.10703,"a",@progbits
	.align	3
	.set	.LANCHOR151,. + 0
	.type	__func__.10703, %object
	.size	__func__.10703, 20
__func__.10703:
	.string	"zftl_sblk_list_init"
	.section	.rodata.__func__.10737,"a",@progbits
	.align	3
	.set	.LANCHOR193,. + 0
	.type	__func__.10737, %object
	.size	__func__.10737, 15
__func__.10737:
	.string	"ftl_info_flush"
	.section	.rodata.__func__.10792,"a",@progbits
	.align	3
	.set	.LANCHOR200,. + 0
	.type	__func__.10792, %object
	.size	__func__.10792, 15
__func__.10792:
	.string	"ftl_alloc_sblk"
	.section	.rodata.__func__.10834,"a",@progbits
	.align	3
	.set	.LANCHOR113,. + 0
	.type	__func__.10834, %object
	.size	__func__.10834, 18
__func__.10834:
	.string	"ftl_alloc_sys_blk"
	.section	.rodata.__func__.10844,"a",@progbits
	.align	3
	.set	.LANCHOR114,. + 0
	.type	__func__.10844, %object
	.size	__func__.10844, 17
__func__.10844:
	.string	"ftl_free_sys_blk"
	.section	.rodata.__func__.10879,"a",@progbits
	.align	3
	.set	.LANCHOR229,. + 0
	.type	__func__.10879, %object
	.size	__func__.10879, 14
__func__.10879:
	.string	"ftl_sblk_dump"
	.section	.rodata.__func__.10903,"a",@progbits
	.align	3
	.set	.LANCHOR218,. + 0
	.type	__func__.10903, %object
	.size	__func__.10903, 16
__func__.10903:
	.string	"ftl_sysblk_dump"
	.section	.rodata.__func__.10928,"a",@progbits
	.align	3
	.set	.LANCHOR219,. + 0
	.type	__func__.10928, %object
	.size	__func__.10928, 23
__func__.10928:
	.string	"ftl_open_sblk_recovery"
	.section	.rodata.__func__.10961,"a",@progbits
	.align	3
	.set	.LANCHOR115,. + 0
	.type	__func__.10961, %object
	.size	__func__.10961, 23
__func__.10961:
	.string	"ftl_get_ppa_from_index"
	.section	.rodata.__func__.10982,"a",@progbits
	.align	3
	.set	.LANCHOR231,. + 0
	.type	__func__.10982, %object
	.size	__func__.10982, 19
__func__.10982:
	.string	"ftl_update_l2p_map"
	.section	.rodata.__func__.11001,"a",@progbits
	.align	3
	.set	.LANCHOR119,. + 0
	.type	__func__.11001, %object
	.size	__func__.11001, 22
__func__.11001:
	.string	"ftl_get_new_free_page"
	.section	.rodata.__func__.11012,"a",@progbits
	.align	3
	.set	.LANCHOR120,. + 0
	.type	__func__.11012, %object
	.size	__func__.11012, 22
__func__.11012:
	.string	"ftl_ext_alloc_new_blk"
	.section	.rodata.__func__.11038,"a",@progbits
	.align	3
	.set	.LANCHOR198,. + 0
	.type	__func__.11038, %object
	.size	__func__.11038, 19
__func__.11038:
	.string	"ftl_ext_info_flush"
	.section	.rodata.__func__.11050,"a",@progbits
	.align	3
	.set	.LANCHOR199,. + 0
	.type	__func__.11050, %object
	.size	__func__.11050, 18
__func__.11050:
	.string	"ftl_ext_info_init"
	.section	.rodata.__func__.11089,"a",@progbits
	.align	3
	.set	.LANCHOR201,. + 0
	.type	__func__.11089, %object
	.size	__func__.11089, 25
__func__.11089:
	.string	"ftl_low_format_data_init"
	.section	.rodata.__func__.11104,"a",@progbits
	.align	3
	.set	.LANCHOR203,. + 0
	.type	__func__.11104, %object
	.size	__func__.11104, 15
__func__.11104:
	.string	"ftl_low_format"
	.section	.rodata.__func__.11152,"a",@progbits
	.align	3
	.set	.LANCHOR189,. + 0
	.type	__func__.11152, %object
	.size	__func__.11152, 14
__func__.11152:
	.string	"ftl_prog_page"
	.section	.rodata.__func__.11275,"a",@progbits
	.align	3
	.set	.LANCHOR180,. + 0
	.type	__func__.11275, %object
	.size	__func__.11275, 31
__func__.11275:
	.string	"queue_wait_first_req_completed"
	.section	.rodata.__func__.11329,"a",@progbits
	.align	3
	.set	.LANCHOR181,. + 0
	.type	__func__.11329, %object
	.size	__func__.11329, 15
__func__.11329:
	.string	"sblk_prog_page"
	.section	.rodata.__func__.11356,"a",@progbits
	.align	3
	.set	.LANCHOR184,. + 0
	.type	__func__.11356, %object
	.size	__func__.11356, 15
__func__.11356:
	.string	"sblk_read_page"
	.section	.rodata.__func__.11426,"a",@progbits
	.align	3
	.set	.LANCHOR220,. + 0
	.type	__func__.11426, %object
	.size	__func__.11426, 16
__func__.11426:
	.string	"load_l2p_region"
	.section	.rodata.__func__.11442,"a",@progbits
	.align	3
	.set	.LANCHOR153,. + 0
	.type	__func__.11442, %object
	.size	__func__.11442, 13
__func__.11442:
	.string	"pm_free_sblk"
	.section	.rodata.__func__.11466,"a",@progbits
	.align	3
	.set	.LANCHOR222,. + 0
	.type	__func__.11466, %object
	.size	__func__.11466, 6
__func__.11466:
	.string	"pm_gc"
	.section	.rodata.__func__.11482,"a",@progbits
	.align	3
	.set	.LANCHOR205,. + 0
	.type	__func__.11482, %object
	.size	__func__.11482, 17
__func__.11482:
	.string	"pm_alloc_new_blk"
	.section	.rodata.__func__.11492,"a",@progbits
	.align	3
	.set	.LANCHOR206,. + 0
	.type	__func__.11492, %object
	.size	__func__.11492, 14
__func__.11492:
	.string	"pm_write_page"
	.section	.rodata.__func__.11510,"a",@progbits
	.align	3
	.set	.LANCHOR137,. + 0
	.type	__func__.11510, %object
	.size	__func__.11510, 21
__func__.11510:
	.string	"pm_select_ram_region"
	.section	.rodata.__func__.8803,"a",@progbits
	.align	3
	.set	.LANCHOR170,. + 0
	.type	__func__.8803, %object
	.size	__func__.8803, 19
__func__.8803:
	.string	"flash_read_page_en"
	.section	.rodata.__func__.8864,"a",@progbits
	.align	3
	.set	.LANCHOR186,. + 0
	.type	__func__.8864, %object
	.size	__func__.8864, 19
__func__.8864:
	.string	"flash_prog_page_en"
	.section	.rodata.__func__.8880,"a",@progbits
	.align	3
	.set	.LANCHOR43,. + 0
	.type	__func__.8880, %object
	.size	__func__.8880, 26
__func__.8880:
	.string	"flash_erase_duplane_block"
	.section	.rodata.__func__.8891,"a",@progbits
	.align	3
	.set	.LANCHOR45,. + 0
	.type	__func__.8891, %object
	.size	__func__.8891, 21
__func__.8891:
	.string	"flash_erase_block_en"
	.section	.rodata.__func__.8905,"a",@progbits
	.align	3
	.set	.LANCHOR28,. + 0
	.type	__func__.8905, %object
	.size	__func__.8905, 28
__func__.8905:
	.string	"flash_wait_device_ready_raw"
	.section	.rodata.__func__.8929,"a",@progbits
	.align	3
	.set	.LANCHOR175,. + 0
	.type	__func__.8929, %object
	.size	__func__.8929, 26
__func__.8929:
	.string	"flash_start_tlc_page_prog"
	.section	.rodata.__func__.8940,"a",@progbits
	.align	3
	.set	.LANCHOR176,. + 0
	.type	__func__.8940, %object
	.size	__func__.8940, 29
__func__.8940:
	.string	"flash_start_3d_mlc_page_prog"
	.section	.rodata.__func__.8958,"a",@progbits
	.align	3
	.set	.LANCHOR177,. + 0
	.type	__func__.8958, %object
	.size	__func__.8958, 22
__func__.8958:
	.string	"flash_start_page_prog"
	.section	.rodata.__func__.8969,"a",@progbits
	.align	3
	.set	.LANCHOR34,. + 0
	.type	__func__.8969, %object
	.size	__func__.8969, 22
__func__.8969:
	.string	"flash_start_page_read"
	.section	.rodata.__func__.8982,"a",@progbits
	.align	3
	.set	.LANCHOR178,. + 0
	.type	__func__.8982, %object
	.size	__func__.8982, 31
__func__.8982:
	.string	"flash_complete_plane_page_read"
	.section	.rodata.__func__.8994,"a",@progbits
	.align	3
	.set	.LANCHOR46,. + 0
	.type	__func__.8994, %object
	.size	__func__.8994, 23
__func__.8994:
	.string	"flash_start_plane_read"
	.section	.rodata.__func__.9007,"a",@progbits
	.align	3
	.set	.LANCHOR179,. + 0
	.type	__func__.9007, %object
	.size	__func__.9007, 25
__func__.9007:
	.string	"flash_complete_page_read"
	.section	.rodata.__func__.9422,"a",@progbits
	.align	3
	.set	.LANCHOR143,. + 0
	.type	__func__.9422, %object
	.size	__func__.9422, 20
__func__.9422:
	.string	"flash_die_info_init"
	.section	.rodata.__func__.9432,"a",@progbits
	.align	3
	.set	.LANCHOR20,. + 0
	.type	__func__.9432, %object
	.size	__func__.9432, 22
__func__.9432:
	.string	"nand_flash_print_info"
	.section	.rodata.__func__.9477,"a",@progbits
	.align	3
	.set	.LANCHOR213,. + 0
	.type	__func__.9477, %object
	.size	__func__.9477, 16
__func__.9477:
	.string	"nand_flash_init"
	.section	.rodata.__func__.9500,"a",@progbits
	.align	3
	.set	.LANCHOR155,. + 0
	.type	__func__.9500, %object
	.size	__func__.9500, 11
__func__.9500:
	.string	"nandc_init"
	.section	.rodata.__func__.9665,"a",@progbits
	.align	3
	.set	.LANCHOR58,. + 0
	.type	__func__.9665, %object
	.size	__func__.9665, 13
__func__.9665:
	.string	"buf_add_tail"
	.section	.rodata.__func__.9678,"a",@progbits
	.align	3
	.set	.LANCHOR60,. + 0
	.type	__func__.9678, %object
	.size	__func__.9678, 10
__func__.9678:
	.string	"buf_alloc"
	.section	.rodata.__func__.9692,"a",@progbits
	.align	3
	.set	.LANCHOR61,. + 0
	.type	__func__.9692, %object
	.size	__func__.9692, 16
__func__.9692:
	.string	"buf_remove_free"
	.section	.rodata.__func__.9713,"a",@progbits
	.align	3
	.set	.LANCHOR212,. + 0
	.type	__func__.9713, %object
	.size	__func__.9713, 20
__func__.9713:
	.string	"flash_info_blk_init"
	.section	.rodata.__func__.9728,"a",@progbits
	.align	3
	.set	.LANCHOR154,. + 0
	.type	__func__.9728, %object
	.size	__func__.9728, 21
__func__.9728:
	.string	"flash_info_data_init"
	.section	.rodata.__func__.9750,"a",@progbits
	.align	3
	.set	.LANCHOR209,. + 0
	.type	__func__.9750, %object
	.size	__func__.9750, 17
__func__.9750:
	.string	"flash_info_flush"
	.section	.rodata.__func__.9826,"a",@progbits
	.align	3
	.set	.LANCHOR147,. + 0
	.type	__func__.9826, %object
	.size	__func__.9826, 17
__func__.9826:
	.string	"lpa_rebuild_hash"
	.section	.rodata.__func__.9876,"a",@progbits
	.align	3
	.set	.LANCHOR232,. + 0
	.type	__func__.9876, %object
	.size	__func__.9876, 17
__func__.9876:
	.string	"ftl_write_commit"
	.section	.rodata.__func__.9894,"a",@progbits
	.align	3
	.set	.LANCHOR130,. + 0
	.type	__func__.9894, %object
	.size	__func__.9894, 14
__func__.9894:
	.string	"ftl_write_buf"
	.section	.rodata.__func__.9939,"a",@progbits
	.align	3
	.set	.LANCHOR132,. + 0
	.type	__func__.9939, %object
	.size	__func__.9939, 18
__func__.9939:
	.string	"zftl_add_read_buf"
	.section	.rodata.__func__.9972,"a",@progbits
	.align	3
	.set	.LANCHOR230,. + 0
	.type	__func__.9972, %object
	.size	__func__.9972, 10
__func__.9972:
	.string	"zftl_read"
	.section	.rodata._list_remove_node.str1.1,"aMS",@progbits,1
.LC0:
	.string	"\n!!!!! error @ func:%s - line:%d\n"
	.section	.rodata.dump_buf_info.str1.1,"aMS",@progbits,1
.LC41:
	.string	"sblk_queue_head = %d\n"
.LC42:
	.string	"sblk_read_completed_queue_head = %d\n"
.LC43:
	.string	"sblk_gc_write_completed_queue_head = %d\n"
.LC44:
	.string	"sblk_write_completed_queue_head = %d\n"
.LC45:
	.string	"p_free_buf_head = %d\n"
.LC46:
	.string	"free_buf_count = %d\n"
.LC47:
	.string	"buf = %d, next=%d, flag=%d gc_write_flag=%d, lun_state=%d, op_status = %d lpa=%x, ppa=%x\n"
	.section	.rodata.dump_ftl_info.str1.1,"aMS",@progbits,1
.LC192:
	.string	"free_buf_count: %d\n"
.LC193:
	.string	"g_ftl_info_blk blk:0x%x, index:0x%x, page:0x%x\n"
.LC194:
	.string	"ftl_ext_info_blk blk:0x%x, page:0x%x\n"
.LC195:
	.string	"ac_blk:0x%x, page:0x%x, index:0x%x, free:0x%x, page_index:0x%x\n"
.LC196:
	.string	"tmp_blk:0x%x, page:0x%x, index:0x%x, free:0x%x, page_index:0x%x\n"
.LC197:
	.string	"gc_blk:0x%x, page:0x%x, index:0x%x, free:0x%x, page_index:0x%x\n"
.LC198:
	.string	"lpa:"
.LC199:
	.string	"vpn:"
.LC200:
	.string	"sblk:"
.LC201:
	.string	"lpa_hash:"
.LC202:
	.string	"lpa_hash_index:"
	.section	.rodata.dump_pm_blk.str1.1,"aMS",@progbits,1
.LC257:
	.string	"pm l2p:"
.LC258:
	.string	"pm blk:"
	.section	.rodata.dump_sblk_queue.str1.1,"aMS",@progbits,1
.LC79:
	.string	"dump_sblk_queue: %d\n"
.LC80:
	.string	"buf id= %d state = %d ppa = %x\n"
	.section	.rodata.flash_complete_page_read.str1.1,"aMS",@progbits,1
.LC136:
	.string	"flash_complete_page_read %x %x error_ecc %d %d\n"
	.section	.rodata.flash_ddr_tuning_read.str1.1,"aMS",@progbits,1
.LC122:
	.string	"%d flash_ddr_tuning_read %x ecc=%d\n"
.LC123:
	.string	"sync para %d\n"
.LC124:
	.string	"DDR mode Read error %x %x\n"
.LC125:
	.string	"SDR mode Read %x %x ecc:%x\n"
	.section	.rodata.flash_dual_page_prog.str1.1,"aMS",@progbits,1
.LC130:
	.string	"flash_prog_page %x %x %x\n"
	.section	.rodata.flash_erase_all.str1.1,"aMS",@progbits,1
.LC35:
	.string	"erase done: %x\n"
	.section	.rodata.flash_erase_block_en.str1.1,"aMS",@progbits,1
.LC33:
	.string	"flash_erase_block %x %x %x\n"
.LC34:
	.string	"flash_erase_block %d block = %x status = %x\n"
	.section	.rodata.flash_erase_duplane_block.str1.1,"aMS",@progbits,1
.LC31:
	.string	"flash_erase_duplane_block %x %x %x\n"
.LC32:
	.string	"flash_erase_duplane_block pageadd = %x status = %x\n"
	.section	.rodata.flash_get_last_written_page.str1.1,"aMS",@progbits,1
.LC128:
	.string	"flash_get_last_written_page: %x %x %x\n"
	.section	.rodata.flash_info_blk_init.str1.1,"aMS",@progbits,1
.LC177:
	.string	"...%d @ %s %d %p\n"
.LC178:
	.string	"no sys info %x\n"
	.section	.rodata.flash_info_data_init.str1.1,"aMS",@progbits,1
.LC94:
	.string	"...%d @ %s\n"
	.section	.rodata.flash_info_flush.str1.1,"aMS",@progbits,1
.LC174:
	.string	"finfo:"
.LC175:
	.string	"flash_info_flush id = %x, page = %x\n"
.LC176:
	.string	"sys_info_flush error:%x\n"
	.section	.rodata.flash_mask_bad_block.str1.1,"aMS",@progbits,1
.LC48:
	.string	"flash_mask_bad_block %d %d\n"
	.section	.rodata.flash_prog_page.str1.1,"aMS",@progbits,1
.LC129:
	.string	"flash_prog_page page_addr = %x status = %x\n"
	.section	.rodata.flash_prog_page_en.str1.1,"aMS",@progbits,1
.LC144:
	.string	"flash_prog_page_en:%x %x %x\n"
.LC145:
	.string	"w d:"
.LC146:
	.string	"w s:"
.LC147:
	.string	"spare"
.LC148:
	.string	"data"
.LC149:
	.string	"write error: %x\n"
	.section	.rodata.flash_read_id.str1.1,"aMS",@progbits,1
.LC38:
	.string	"No.%d FLASH ID:%x %x %x %x %x %x\n"
	.section	.rodata.flash_read_otp_data.str1.1,"aMS",@progbits,1
.LC39:
	.string	"otp:%x %x %x %x\n"
	.section	.rodata.flash_read_page_en.str1.1,"aMS",@progbits,1
.LC126:
	.string	"flash_read_page_en %x %x %x %x\n"
.LC127:
	.string	"flash_read_page_en %x %x error_ecc %d %d\n"
	.section	.rodata.flash_set_interface_mode.str1.1,"aMS",@progbits,1
.LC36:
	.string	"nand sdr mode %x\n"
.LC37:
	.string	"nand ddr mode %x\n"
	.section	.rodata.ftl_alloc_new_data_sblk.str1.1,"aMS",@progbits,1
.LC235:
	.string	"error gc_add_sblk: %x\n"
	.section	.rodata.ftl_alloc_sblk.str1.1,"aMS",@progbits,1
.LC167:
	.string	"alloc sblk %x %d\n"
	.section	.rodata.ftl_dump_write_open_sblk.str1.1,"aMS",@progbits,1
.LC159:
	.string	"ftl_sblk_dump_write = %x %d %d %d %d\n"
.LC160:
	.string	"blk= %x, page=%x, ppa = %x, status = %x, data:%x %x %x %x, spare: %x %x %x %x\n"
.LC161:
	.string	"ftl_sblk_dump_write2 = %x %d %d %d\n"
.LC162:
	.string	"ftl_sblk_dump_write = %x %x\n"
.LC163:
	.string	"ftl_sblk_dump_write done = %x\n"
	.section	.rodata.ftl_ext_info_init.str1.1,"aMS",@progbits,1
.LC156:
	.string	"%s %d %d %x %x\n"
.LC157:
	.string	"ext info hash %x error\n"
.LC158:
	.string	"%s %x %x %x\n"
	.section	.rodata.ftl_free_sblk.str1.1,"aMS",@progbits,1
.LC68:
	.string	"swl_slc_free_mini_ec_blk sblk %x\n"
	.section	.rodata.ftl_info_blk_init.str1.1,"aMS",@progbits,1
.LC152:
	.string	"%d %x @%d %x\n"
.LC153:
	.string	"ftl_info_blk_init %d %d %x\n"
.LC154:
	.string	"ftl info hash %x error\n"
.LC155:
	.string	"ink flag: %x\n"
	.section	.rodata.ftl_info_flush.str1.1,"aMS",@progbits,1
.LC151:
	.string	"g_ftl_info_blk blk = %x, page = %x version = %d\n"
	.section	.rodata.ftl_ink_check_sblk.str1.1,"aMS",@progbits,1
.LC165:
	.string	"ftl_ink_check_sblk = %x %d %d\n"
.LC166:
	.string	"ftl_ink_check_sblk = %x %d %d end\n"
	.section	.rodata.ftl_low_format.str1.1,"aMS",@progbits,1
.LC169:
	.string	"ftl_low_format %d\n"
.LC170:
	.string	"low format %d %d %d %d\n"
	.section	.rodata.ftl_mask_bad_block.str1.1,"aMS",@progbits,1
.LC66:
	.string	"mask bad block:cs %x %x block: %x %x\n"
	.section	.rodata.ftl_open_sblk_init.str1.1,"aMS",@progbits,1
.LC168:
	.string	"blk %x is bad block\n"
	.section	.rodata.ftl_open_sblk_recovery.str1.1,"aMS",@progbits,1
.LC180:
	.string	"saved_active_page  = %x\n"
.LC181:
	.string	"saved_active_plane = %x\n"
.LC182:
	.string	"sblk = %x\n"
.LC183:
	.string	"phy_blk = %x %x\n"
.LC184:
	.string	"num_planes = %x\n"
.LC185:
	.string	"recovery blk=%x, page=%x, ppa = %x, status = %x, hash:%x\n"
.LC186:
	.string	"data:"
.LC187:
	.string	"sblk = %x, vpn0 = %d, vpn1 = %d\n"
.LC188:
	.string	"dump_write_lpa = %x %x %x %x\n"
.LC189:
	.string	"dump write new ppa = %x, last ppa = %x lpa = %x\n"
.LC190:
	.string	"dump write = %x %x %x\n"
.LC191:
	.string	"dump write hash update = %x %x %x\n"
	.section	.rodata.ftl_re_low_format.str1.1,"aMS",@progbits,1
.LC171:
	.string	"re low format %d\n"
	.section	.rodata.ftl_sblk_dump.str1.1,"aMS",@progbits,1
.LC223:
	.string	"ftl_sblk_dump = %x %d %d %d %d\n"
.LC224:
	.string	"ftl_sblk_dump = %x %x %x %x\n"
.LC225:
	.string	"page_addr = %x, lpa=%x vpn = %d\n"
.LC226:
	.string	"index= %x, lpa=%x\n"
.LC227:
	.string	"block = %x, vpn=%x check vpn = %x\n"
	.section	.rodata.ftl_sysblk_dump.str1.1,"aMS",@progbits,1
.LC179:
	.string	"l2p:"
	.section	.rodata.ftl_test_block.str1.1,"aMS",@progbits,1
.LC150:
	.string	"low format %d\n"
	.section	.rodata.ftl_update_l2p_map.str1.1,"aMS",@progbits,1
.LC231:
	.string	"ftl_update_l2p_map: %x %x %x\n"
.LC232:
	.string	"ftl_update_l2p_map"
.LC233:
	.string	"lpa_tbl:"
.LC234:
	.string	"sblk %x vpn: %d %d\n"
	.section	.rodata.ftl_vpn_decrement.str1.1,"aMS",@progbits,1
.LC65:
	.string	"ftl_vpn_decrement %x = %d, %d\n"
	.section	.rodata.ftl_write_commit.str1.1,"aMS",@progbits,1
.LC236:
	.string	"%d read error: ppa:%x, lpa:%x, status:%x\n"
	.section	.rodata.ftl_write_completed.str1.1,"aMS",@progbits,1
.LC77:
	.string	"ftl prog error =%x, lpa = %x, ppa= %x\n"
.LC78:
	.string	"ftl re prog: lpa = %x, ppa= %x\n"
	.section	.rodata.gc_add_sblk.str1.1,"aMS",@progbits,1
.LC49:
	.string	"gc_add_sblk = %d, %d, %d, %d, %d, %d, %d\n"
.LC50:
	.string	"gc_add_sblk = %d, %d, %d\n"
.LC51:
	.string	"gc_add_sblk = %d, %d, %d,last update:%d, %d\n"
.LC52:
	.string	"gc_add_sblk = %d, %d, %d, %d, %d, %d\n"
	.section	.rodata.gc_check_data_one_wl.str1.1,"aMS",@progbits,1
.LC143:
	.string	"err: ppa = %x, status = %x, %x %x spare: %x %x %x %x\n"
	.section	.rodata.gc_do_copy_back.str1.1,"aMS",@progbits,1
.LC237:
	.string	"gc page in buf: lpa %x ppa = %x pageindex= %x\n"
.LC238:
	.string	"gc_do_copy_back: lpa %x des_ppa = %x %x gc_ppa= %x page_index= %d\n"
	.section	.rodata.gc_free_bad_sblk.str1.1,"aMS",@progbits,1
.LC67:
	.string	"gc_free_bad_sblk 0x%x\n"
	.section	.rodata.gc_free_src_blk.str1.1,"aMS",@progbits,1
.LC69:
	.string	"gc_free_src_blk = %x, vpn = %d\n"
.LC70:
	.string	"gc_free_src_blk %x, %d\n"
	.section	.rodata.gc_free_temp_buf.str1.1,"aMS",@progbits,1
.LC55:
	.string	"%d gc_free_temp_buf buf id= %x\n"
	.section	.rodata.gc_ink_check_sblk.str1.1,"aMS",@progbits,1
.LC164:
	.string	"%x: ink_scaned_blk_num %x\n"
	.section	.rodata.gc_mark_bad_ppa.str1.1,"aMS",@progbits,1
.LC53:
	.string	"gc_mark_bad_ppa %d %x %x\n"
	.section	.rodata.gc_recovery.str1.1,"aMS",@progbits,1
.LC213:
	.string	"ppa = %x, status = %x, data:%x %x %x %x, spare: %x %x %x %x\n"
.LC214:
	.string	"ppa = %x, status = %x, %x %x spare: %x %x %x %x\n"
.LC215:
	.string	"gc_recovery: %x vpn = %x\n"
	.section	.rodata.gc_scan_src_blk.str1.1,"aMS",@progbits,1
.LC220:
	.string	"gc_scan_src_blk = %x, vpn = %d\n"
.LC221:
	.string	"js hash error:%x %x %x\n"
.LC222:
	.string	"gc_scan_src_blk = %x, s vpn0 = %d, c vpn1 = %d\n"
	.section	.rodata.gc_search_src_blk.str1.1,"aMS",@progbits,1
.LC57:
	.string	"zftl_get_gc_node cache = %x index = %d vpn = %x\n"
.LC58:
	.string	"gc_search_src_blk mode = %x, src mode = %x, count= %d %d\n"
	.section	.rodata.gc_static_wearleveling.str1.1,"aMS",@progbits,1
.LC82:
	.string	"gc_static_wearleveling: min blk: %x,sec=%d,xec = %d ,mode=%d, func=%x, bbt=%x vpn = %d\n"
.LC83:
	.string	"gc_static_wearleveling: min slc blk: %x,sec=%d,xec = %d ,mode=%d, func=%x, bbt=%x vpn = %d\n"
.LC84:
	.string	"gc_static_wearleveling: min tlc blk: %x,sec=%d,xec = %d ,mode=%d, func=%x, bbt=%x vpn = %d\n"
.LC85:
	.string	"gc_static_wearleveling: max slc blk: %x,sec=%d,xec = %d ,mode=%d, func=%x, bbt=%x vpn = %d\n"
.LC86:
	.string	"gc_static_wearleveling: max xlc blk: %x,sec=%d,xec = %d ,mode=%d, func=%x, bbt=%x vpn = %d\n"
.LC87:
	.string	"gc_static_wearleveling: slc blk: %x, tlc blk: %d avg slc ec: %d, avg tlc ec: %d \n"
.LC88:
	.string	"gc_static_wearleveling: min slc ec: %x, min tlc ec: %d max slc ec: %d, max tlc ec: %d; %d %d\n"
.LC89:
	.string	"swl add tlc gc = %x, %d, %d, %d, %d, %d\n"
.LC90:
	.string	"swl add slc gc  = %x, %d, %d, %d, %d, %d\n"
	.section	.rodata.gc_update_l2p_map_new.str1.1,"aMS",@progbits,1
.LC216:
	.string	"gc_update_l2p_map_new sblk %x\n"
.LC217:
	.string	"gc_update_l2p_map_new: %x %x %x\n"
.LC218:
	.string	"lpa: %x %x %x\n"
.LC219:
	.string	"gc_update_l2p_map_new: %x vpn = %x vpn1 = %x done\n"
	.section	.rodata.gc_write_completed.str1.1,"aMS",@progbits,1
.LC54:
	.string	"status: %x, ppa: %x\n"
	.section	.rodata.hynix_get_read_retry_default.str1.1,"aMS",@progbits,1
.LC102:
	.string	"otp error! %d"
.LC103:
	.string	"rr"
	.section	.rodata.hynix_read_retrial.str1.1,"aMS",@progbits,1
.LC121:
	.string	"hynix RR %d row=%x, count %d, status=%d\n"
	.section	.rodata.idb_write_data.str1.1,"aMS",@progbits,1
.LC132:
	.string	"1 write_idblock fix data %x %x %x\n"
.LC133:
	.string	"write_idblock check fail! %x\n"
.LC134:
	.string	"write_idblock fail! %x\n"
	.section	.rodata.load_l2p_region.str1.1,"aMS",@progbits,1
.LC204:
	.string	"region_id = %d, pm_max_region = %d\n"
.LC205:
	.string	"load_l2p_region no ppa = %x , %x, all setting 0xff....\n"
.LC206:
	.string	"load_l2p_region = %x,%x,%x, %x\n"
.LC207:
	.string	"pm_ppa:"
.LC208:
	.string	"spare:"
	.section	.rodata.lpa_rebuild_hash.str1.1,"aMS",@progbits,1
.LC81:
	.string	"%s %d %d\n"
	.section	.rodata.micron_read_retrial.str1.1,"aMS",@progbits,1
.LC112:
	.string	"MT %d row=%x,last status %d,status = %d\n"
.LC113:
	.string	"MT RR %d row=%x,count %d,status=%d\n"
	.section	.rodata.nand_flash_print_info.str1.1,"aMS",@progbits,1
.LC1:
	.string	"...%s enter...\n"
.LC2:
	.string	"No.0 FLASH ID: %x %x %x %x %x %x\n"
.LC3:
	.string	"DiePerChip: %x\n"
.LC4:
	.string	"SectPerPage: %x\n"
.LC5:
	.string	"PagePerBlk: %x\n"
.LC6:
	.string	"Cell: %x\n"
.LC7:
	.string	"PlanePerDie: %x\n"
.LC8:
	.string	"BlkPerPlane: %x\n"
.LC9:
	.string	"die gap: %x\n"
.LC10:
	.string	"lsbMode: %x\n"
.LC11:
	.string	"ReadRetryMode: %x\n"
.LC12:
	.string	"ecc: %x\n"
.LC13:
	.string	"idb ecc: %x\n"
.LC14:
	.string	"OptMode: %x\n"
.LC15:
	.string	"g_nand_max_die: %x\n"
.LC16:
	.string	"Cache read enable: %x\n"
.LC17:
	.string	"Cache random read enable: %x\n"
.LC18:
	.string	"Cache prog enable: %x\n"
.LC19:
	.string	"multi read enable: %x\n"
.LC20:
	.string	"multi prog enable: %x\n"
.LC21:
	.string	"interleave enable: %x\n"
.LC22:
	.string	"read retry enable: %x\n"
.LC23:
	.string	"randomizer enable: %x\n"
.LC24:
	.string	"SDR enable: %x\n"
.LC25:
	.string	"ONFI enable: %x\n"
.LC26:
	.string	"TOGGLE enable: %x\n"
.LC27:
	.string	"g_flash_slc_mode: %x %x\n"
.LC28:
	.string	"MultiPlaneProgCmd: %x %x\n"
.LC29:
	.string	"MultiPlaneReadCmd: %x %x\n"
.LC30:
	.string	"g_flash_toggle_mode_en: %x\n"
	.section	.rodata.nandc_init.str1.1,"aMS",@progbits,1
.LC95:
	.string	"...%s enter... %p\n"
.LC96:
	.string	"0:%x %x %x %x %x\n"
.LC97:
	.string	"g_nandc_ver...%d\n"
	.section	.rodata.nandc_xfer.str1.1,"aMS",@progbits,1
.LC109:
	.string	"dqs data abort %x\n"
.LC110:
	.string	"dqs data timeout %x\n"
.LC111:
	.string	"xfer error %x\n"
	.section	.rodata.nandc_xfer_done.str1.1,"aMS",@progbits,1
.LC104:
	.string	"flash_abort_clear = %d\n"
.LC105:
	.string	"%d mtrans_cnt = %d page_num = %d\n"
.LC106:
	.string	"%d flReg.d32=%x %x\n"
.LC107:
	.string	"nandc:"
.LC108:
	.string	"nandc_xfer_done read error %x\n"
	.section	.rodata.pm_alloc_new_blk.str1.1,"aMS",@progbits,1
.LC172:
	.string	"pm_alloc_new_blk: %x %x %x %x\n"
	.section	.rodata.pm_free_sblk.str1.1,"aMS",@progbits,1
.LC92:
	.string	"GC PM block %x %x %x %d\n"
.LC93:
	.string	"ftl_free_no_use_map_blk %x %x %x %d\n"
	.section	.rodata.pm_init.str1.1,"aMS",@progbits,1
.LC209:
	.string	"pm_init posr %x %x %x\n"
.LC210:
	.string	"pm_init recovery %x %x %x\n"
.LC211:
	.string	"pm_init hash %x error\n"
	.section	.rodata.pm_log2phys.str1.1,"aMS",@progbits,1
.LC212:
	.string	"pm_log2phys  lpn = %d, max lpn = %d\n"
	.section	.rodata.pm_ppa_update_check.str1.1,"aMS",@progbits,1
.LC203:
	.string	"%s w error lpn = %x, max ppa = %d\n"
	.section	.rodata.pm_write_page.str1.1,"aMS",@progbits,1
.LC173:
	.string	"pm_write_page write error: %x\n"
	.section	.rodata.print_ftl_debug_info.str1.1,"aMS",@progbits,1
.LC71:
	.string	"bad blk = %x, %x free blk: s:%x,t:%x,m:%x, data blk:s:%x,%x,t%x vpn: s:%x t:%x, max_vpn: %x\n"
.LC72:
	.string	"totle w: %d MB,r: %d MB %d dv:0x%X,poc:%d\n"
.LC73:
	.string	"gc xlc page: %d,gc slc page: %d, tmp w: %d MB\n"
.LC74:
	.string	"slc ec: %d,%d,%d,%d,%d,tlc ec: %d,%d,%d,%d,%d\n"
.LC75:
	.string	"gc th: tlc_tlc: %d tlc_slc: %d slc_slc: %d slc_tlc:%d free_th: %d\n"
.LC76:
	.string	"swl : %x %x %x %x %x %x\n"
	.section	.rodata.print_gc_debug_info.str1.1,"aMS",@progbits,1
.LC56:
	.string	"gc: b:%x,p:%x,i:%x; free buf=%d %d free slc th: %d\n"
	.section	.rodata.print_list_info.str1.1,"aMS",@progbits,1
.LC63:
	.string	"list count:%p %d\n"
.LC64:
	.string	"%d: node:%x %x %x %x, %d %d %d %d %d\n"
	.section	.rodata.queue_wait_first_req_completed.str1.1,"aMS",@progbits,1
.LC137:
	.string	"read: %x %x %x %x\n"
.LC138:
	.string	"0set buf %d,status = %x, ppa = %x lun state = %d\n"
.LC139:
	.string	"prog end %x %x error_ecc %d %d\n"
.LC140:
	.string	"1set buf %d,status = %x, ppa = %x lun state = %d\n"
.LC141:
	.string	"dp prog end %x %x error_ecc %d %d\n"
	.section	.rodata.random_seed,"a",@progbits
	.align	3
	.set	.LANCHOR54,. + 0
	.type	random_seed, %object
	.size	random_seed, 256
random_seed:
	.hword	22378
	.hword	1512
	.hword	25245
	.hword	17827
	.hword	25756
	.hword	19440
	.hword	9026
	.hword	10030
	.hword	29528
	.hword	20467
	.hword	29676
	.hword	24432
	.hword	31328
	.hword	6872
	.hword	13426
	.hword	13842
	.hword	8783
	.hword	1108
	.hword	782
	.hword	28837
	.hword	30729
	.hword	9505
	.hword	18676
	.hword	23085
	.hword	18730
	.hword	1085
	.hword	32609
	.hword	14697
	.hword	20858
	.hword	15170
	.hword	30365
	.hword	1607
	.hword	32298
	.hword	4995
	.hword	18905
	.hword	1976
	.hword	9592
	.hword	20204
	.hword	17443
	.hword	13615
	.hword	23330
	.hword	29369
	.hword	13947
	.hword	9398
	.hword	32398
	.hword	8984
	.hword	27600
	.hword	21785
	.hword	6019
	.hword	6311
	.hword	31598
	.hword	30210
	.hword	19327
	.hword	13896
	.hword	11347
	.hword	27545
	.hword	3107
	.hword	26575
	.hword	32270
	.hword	19852
	.hword	20601
	.hword	8349
	.hword	9290
	.hword	29819
	.hword	13579
	.hword	3661
	.hword	28676
	.hword	27331
	.hword	32574
	.hword	8693
	.hword	31253
	.hword	9081
	.hword	5399
	.hword	6842
	.hword	20087
	.hword	5537
	.hword	1274
	.hword	11617
	.hword	9530
	.hword	4866
	.hword	8035
	.hword	23219
	.hword	1178
	.hword	23272
	.hword	7383
	.hword	18944
	.hword	12488
	.hword	12871
	.hword	29340
	.hword	20532
	.hword	11022
	.hword	22514
	.hword	228
	.hword	22363
	.hword	24978
	.hword	14584
	.hword	12138
	.hword	3092
	.hword	17916
	.hword	16863
	.hword	14554
	.hword	31457
	.hword	29474
	.hword	25311
	.hword	24121
	.hword	3684
	.hword	28037
	.hword	22865
	.hword	22839
	.hword	25217
	.hword	13217
	.hword	27186
	.hword	14938
	.hword	11180
	.hword	29754
	.hword	24180
	.hword	15150
	.hword	32455
	.hword	20434
	.hword	23848
	.hword	29983
	.hword	16120
	.hword	14769
	.hword	20041
	.hword	29803
	.hword	28406
	.hword	17598
	.hword	28087
	.section	.rodata.rk_ftl_init.str1.1,"aMS",@progbits,1
.LC254:
	.string	"zftl_init %x\n"
	.section	.rodata.rknand_print_hex.str1.1,"aMS",@progbits,1
.LC98:
	.string	"%s %p + 0x%x:"
.LC99:
	.string	"%x "
.LC100:
	.string	""
.LC101:
	.string	"%s\n"
	.section	.rodata.samsung_14nm_mlc_rr,"a",@progbits
	.align	3
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
	.section	.rodata.samsung_14nm_slc_rr,"a",@progbits
	.align	3
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
	.section	.rodata.samsung_read_retrial.str1.1,"aMS",@progbits,1
.LC118:
	.string	"samsung SRR %d row=%x, status=%d\n"
.LC119:
	.string	"samsung TRR %d row=%x, status=%d\n"
.LC120:
	.string	"samsung RR %d row=%x,count %d,status=%d\n"
	.section	.rodata.sandisk_prog_test_bad_block.str1.1,"aMS",@progbits,1
.LC40:
	.string	"bad block test:%x %x\n"
	.section	.rodata.sblk_mlc_dump_prog.str1.1,"aMS",@progbits,1
.LC135:
	.string	"sblk_mlc_dump_prog wl_addr= %x ppa = %x ppa = %x\n"
	.section	.rodata.sblk_prog_page.str1.1,"aMS",@progbits,1
.LC142:
	.string	"sblk_prog_page ppa = %x, count = %d\n"
	.section	.rodata.toshiba_15ref_value,"a",@progbits
	.align	3
	.set	.LANCHOR14,. + 0
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
	.section	.rodata.toshiba_3D_slc_value,"a",@progbits
	.align	3
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
	.section	.rodata.toshiba_3D_tlc_value,"a",@progbits
	.align	3
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
	.section	.rodata.toshiba_3d_read_retrial.str1.1,"aMS",@progbits,1
.LC114:
	.string	"toshiba SRR %d row=%x, status=%d\n"
.LC115:
	.string	"toshiba TRR %d row=%x, status=%d\n"
.LC116:
	.string	"toshiba RR %d row=%x,count %d,status=%d\n"
	.section	.rodata.toshiba_A19ref_value,"a",@progbits
	.align	3
	.set	.LANCHOR15,. + 0
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
	.section	.rodata.toshiba_ref_value,"a",@progbits
	.align	3
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
	.section	.rodata.ymtc_3D_slc_value,"a",@progbits
	.align	3
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
	.section	.rodata.ymtc_3D_tlc_value,"a",@progbits
	.align	3
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
	.section	.rodata.ymtc_3d_read_retrial.str1.1,"aMS",@progbits,1
.LC117:
	.string	"YMTC RR %d row=%x,count %d,status=%d\n"
	.section	.rodata.ymtc_flash_tlc_page_prog.str1.1,"aMS",@progbits,1
.LC131:
	.string	"ymtc_flash_tlc_page_prog page_addr = %x status = %x\n"
	.section	.rodata.zftl_discard.str1.1,"aMS",@progbits,1
.LC256:
	.string	"ftl_discard:(%x, %x, %x, %x)\n"
	.section	.rodata.zftl_do_gc.str1.1,"aMS",@progbits,1
.LC239:
	.string	"gc %d: %d %d %d %d %d %d %d\n"
.LC240:
	.string	"GC_STATE_SCAN_ALL_PAGE = %x, vpn0 = %d, vpn1 = %d\n"
.LC241:
	.string	"gc free %x, %d\n"
	.section	.rodata.zftl_gc_get_free_sblk.str1.1,"aMS",@progbits,1
.LC59:
	.string	"swl_tlc_free_mini_ec_blk alloc sblk %x\n"
.LC60:
	.string	"zftl_get_free_sblk %x %d, %p %d %d\n"
.LC61:
	.string	"zftl_gc_get_free_sblk %x %x %x, %d %d %d\n"
	.section	.rodata.zftl_get_free_sblk.str1.1,"aMS",@progbits,1
.LC62:
	.string	"swl_slc_free_mini_ec_blk alloc sblk %x\n"
	.section	.rodata.zftl_init.str1.1,"aMS",@progbits,1
.LC242:
	.string	"FTL version: 6.0.24 20210107"
.LC243:
	.string	"_c_user_data_density := %d\n"
.LC244:
	.string	"_c_totle_phy_density := %d\n"
.LC245:
	.string	"_c_totle_log_page := %d\n"
.LC246:
	.string	"_c_totle_data_density := %d\n"
.LC247:
	.string	"_c_ftl_pm_page_num := %d\n"
.LC248:
	.string	"_c_ftl_byte_pre_page := %d\n"
.LC249:
	.string	"_c_max_pm_sblk := %d\n"
.LC250:
	.string	"_min_slc_super_block := %d\n"
.LC251:
	.string	"_max_xlc_super_block := %d\n"
.LC252:
	.string	"gp_ftl_ext_info %p %p %p\n"
.LC253:
	.string	"flash info size: %d %d %d\n"
	.section	.rodata.zftl_read.str1.1,"aMS",@progbits,1
.LC228:
	.string	"ftl_read %x %x %x\n"
.LC229:
	.string	"ftl_read refresh =%x, lpa = %x, ppa= %x\n"
.LC230:
	.string	"id=%d, status = %x, lpa = %x, ppa = %x spare = %x %x %x %x\n"
	.section	.rodata.zftl_sblk_list_init.str1.1,"aMS",@progbits,1
.LC91:
	.string	"free blk vpn error: %x %x\n"
	.section	.rodata.zftl_write.str1.1,"aMS",@progbits,1
.LC255:
	.string	"ftlwrite %x %x %x %x\n"
	.hidden	free
