/*
 * Copyright (c) 2016-2017, Fuzhou Rockchip Electronics Co., Ltd
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * date: 2020-09-23
 */
	.arch armv8-a
	.file	"rk_ftl_arm_v8.S"
	.section	.text.flash_read_ecc,"ax",@progbits
	.align	2
	.type	flash_read_ecc, %function
flash_read_ecc:
	ubfiz	x0, x0, 4, 8
	adrp	x1, .LANCHOR0
	add	x1, x1, :lo12:.LANCHOR0
	stp	x29, x30, [sp, -32]!
	add	x2, x1, x0
	add	x29, sp, 0
	ldr	x0, [x1, x0]
	str	x19, [sp, 16]
	ldrb	w19, [x2, 8]
	add	x19, x0, x19, lsl 8
	mov	w0, 122
	str	w0, [x19, 2056]
	mov	x0, 80
	bl	udelay
	ldr	w1, [x19, 2048]
	ldr	w0, [x19, 2048]
	and	w1, w1, 15
	and	w0, w0, 15
	cmp	w1, w0
	csel	w1, w1, w0, cs
	ldr	w0, [x19, 2048]
	ldr	w2, [x19, 2048]
	and	w0, w0, 15
	ldr	x19, [sp, 16]
	and	w2, w2, 15
	cmp	w0, w2
	csel	w0, w0, w2, cs
	cmp	w0, w1
	csel	w0, w0, w1, cs
	ldp	x29, x30, [sp], 32
	ret
	.size	flash_read_ecc, .-flash_read_ecc
	.section	.text.ftl_set_blk_mode.part.11,"ax",@progbits
	.align	2
	.type	ftl_set_blk_mode.part.11, %function
ftl_set_blk_mode.part.11:
	and	w0, w0, 65535
	adrp	x2, .LANCHOR1
	ubfx	x1, x0, 5, 11
	ldr	x3, [x2, #:lo12:.LANCHOR1]
	lsl	x1, x1, 2
	and	w0, w0, 31
	mov	w2, 1
	lsl	w2, w2, w0
	ldr	w0, [x3, x1]
	orr	w0, w0, w2
	str	w0, [x3, x1]
	ret
	.size	ftl_set_blk_mode.part.11, .-ftl_set_blk_mode.part.11
	.section	.text.FlashMemCmp8,"ax",@progbits
	.align	2
	.global	FlashMemCmp8
	.type	FlashMemCmp8, %function
FlashMemCmp8:
	adrp	x3, .LANCHOR2
	ldrb	w3, [x3, #:lo12:.LANCHOR2]
	cbz	w3, .L9
	ldrb	w4, [x0, 1]
	ldrb	w3, [x1, 1]
	cmp	w4, w3
	beq	.L10
.L9:
	mov	x3, 0
.L7:
	mov	w4, w3
	cmp	w3, w2
	bcc	.L8
.L10:
	mov	w0, 0
	ret
.L8:
	ldrb	w5, [x0, x3]
	add	x3, x3, 1
	add	x6, x1, x3
	ldrb	w6, [x6, -1]
	cmp	w6, w5
	beq	.L7
	add	w0, w4, 1
	ret
	.size	FlashMemCmp8, .-FlashMemCmp8
	.section	.text.FlashRsvdBlkChk,"ax",@progbits
	.align	2
	.global	FlashRsvdBlkChk
	.type	FlashRsvdBlkChk, %function
FlashRsvdBlkChk:
	adrp	x2, .LANCHOR3
	adrp	x3, .LANCHOR4
	and	w0, w0, 255
	ldrb	w2, [x2, #:lo12:.LANCHOR3]
	ldr	w3, [x3, #:lo12:.LANCHOR4]
	mul	w2, w2, w3
	cmp	w2, w1
	bls	.L14
	cmp	w0, 0
	cset	w0, ne
	ret
.L14:
	mov	w0, 1
	ret
	.size	FlashRsvdBlkChk, .-FlashRsvdBlkChk
	.section	.text.FlashGetRandomizer,"ax",@progbits
	.align	2
	.global	FlashGetRandomizer
	.type	FlashGetRandomizer, %function
FlashGetRandomizer:
	and	x3, x1, 127
	adrp	x2, .LANCHOR5
	add	x2, x2, :lo12:.LANCHOR5
	ldrh	w4, [x2, x3, lsl 1]
	adrp	x2, .LANCHOR6
	ldrb	w2, [x2, #:lo12:.LANCHOR6]
	cbz	w2, .L23
	stp	x29, x30, [sp, -16]!
	and	w0, w0, 255
	add	x29, sp, 0
	bl	FlashRsvdBlkChk
	cmp	w0, 0
	orr	w1, w4, -1073741824
	csel	w4, w1, w4, ne
	mov	w0, w4
	ldp	x29, x30, [sp], 16
	ret
.L23:
	mov	w0, w4
	ret
	.size	FlashGetRandomizer, .-FlashGetRandomizer
	.section	.text.FlashSetRandomizer,"ax",@progbits
	.align	2
	.global	FlashSetRandomizer
	.type	FlashSetRandomizer, %function
FlashSetRandomizer:
	and	w5, w0, 255
	and	x2, x1, 127
	adrp	x0, .LANCHOR5
	add	x0, x0, :lo12:.LANCHOR5
	ldrh	w4, [x0, x2, lsl 1]
	adrp	x0, .LANCHOR6
	ldrb	w0, [x0, #:lo12:.LANCHOR6]
	cbz	w0, .L34
	stp	x29, x30, [sp, -16]!
	mov	w0, w5
	add	x29, sp, 0
	bl	FlashRsvdBlkChk
	cmp	w0, 0
	sbfiz	x5, x5, 4, 32
	adrp	x0, .LANCHOR0
	add	x0, x0, :lo12:.LANCHOR0
	orr	w1, w4, -1073741824
	csel	w4, w1, w4, ne
	ldr	x0, [x0, x5]
	str	w4, [x0, 336]
	ldp	x29, x30, [sp], 16
	ret
.L34:
	sbfiz	x5, x5, 4, 32
	adrp	x0, .LANCHOR0
	add	x0, x0, :lo12:.LANCHOR0
	ldr	x0, [x0, x5]
	str	w4, [x0, 336]
	ret
	.size	FlashSetRandomizer, .-FlashSetRandomizer
	.section	.text.FlashBlockAlignInit,"ax",@progbits
	.align	2
	.global	FlashBlockAlignInit
	.type	FlashBlockAlignInit, %function
FlashBlockAlignInit:
	and	w0, w0, 65535
	adrp	x1, .LANCHOR4
	cmp	w0, 512
	bls	.L38
	mov	w0, 1024
.L42:
	str	w0, [x1, #:lo12:.LANCHOR4]
	ret
.L38:
	cmp	w0, 256
	bls	.L40
	mov	w0, 512
	b	.L42
.L40:
	cmp	w0, 128
	bls	.L42
	mov	w0, 256
	b	.L42
	.size	FlashBlockAlignInit, .-FlashBlockAlignInit
	.section	.text.FlashReadCmd,"ax",@progbits
	.align	2
	.global	FlashReadCmd
	.type	FlashReadCmd, %function
FlashReadCmd:
	and	w0, w0, 255
	adrp	x2, .LANCHOR0
	sbfiz	x3, x0, 4, 32
	add	x2, x2, :lo12:.LANCHOR0
	add	x4, x2, x3
	ldr	x2, [x2, x3]
	adrp	x3, .LANCHOR7
	ldrb	w4, [x4, 8]
	ldr	x3, [x3, #:lo12:.LANCHOR7]
	ldrb	w3, [x3, 7]
	cmp	w3, 1
	bne	.L44
	sxtw	x3, w4
	mov	w5, 38
	add	x3, x3, 8
	add	x3, x2, x3, lsl 8
	str	w5, [x3, 8]
.L44:
	ubfiz	x4, x4, 8, 8
	and	w3, w1, 255
	add	x2, x2, x4
	str	wzr, [x2, 2056]
	str	wzr, [x2, 2052]
	str	wzr, [x2, 2052]
	str	w3, [x2, 2052]
	lsr	w3, w1, 8
	str	w3, [x2, 2052]
	lsr	w3, w1, 16
	str	w3, [x2, 2052]
	mov	w3, 48
	str	w3, [x2, 2056]
	b	FlashSetRandomizer
	.size	FlashReadCmd, .-FlashReadCmd
	.section	.text.FlashReadDpDataOutCmd,"ax",@progbits
	.align	2
	.global	FlashReadDpDataOutCmd
	.type	FlashReadDpDataOutCmd, %function
FlashReadDpDataOutCmd:
	and	w0, w0, 255
	adrp	x2, .LANCHOR0
	sbfiz	x3, x0, 4, 32
	add	x2, x2, :lo12:.LANCHOR0
	add	x4, x2, x3
	and	w5, w1, 255
	ldr	x6, [x2, x3]
	adrp	x2, .LANCHOR8+16
	lsr	w3, w1, 16
	ldrb	w2, [x2, #:lo12:.LANCHOR8+16]
	cmp	w2, 1
	ldrb	w2, [x4, 8]
	lsr	w4, w1, 8
	add	x2, x6, x2, lsl 8
	bne	.L46
	mov	w6, 6
	str	w6, [x2, 2056]
	str	wzr, [x2, 2052]
	str	wzr, [x2, 2052]
	str	w5, [x2, 2052]
	str	w4, [x2, 2052]
	str	w3, [x2, 2052]
.L48:
	mov	w3, 224
	str	w3, [x2, 2056]
	b	FlashSetRandomizer
.L46:
	str	wzr, [x2, 2056]
	str	wzr, [x2, 2052]
	str	wzr, [x2, 2052]
	str	w5, [x2, 2052]
	str	w4, [x2, 2052]
	str	w3, [x2, 2052]
	mov	w3, 5
	str	w3, [x2, 2056]
	str	wzr, [x2, 2052]
	str	wzr, [x2, 2052]
	b	.L48
	.size	FlashReadDpDataOutCmd, .-FlashReadDpDataOutCmd
	.section	.text.FlashProgFirstCmd,"ax",@progbits
	.align	2
	.global	FlashProgFirstCmd
	.type	FlashProgFirstCmd, %function
FlashProgFirstCmd:
	and	w0, w0, 255
	adrp	x4, .LANCHOR0
	sbfiz	x5, x0, 4, 32
	add	x4, x4, :lo12:.LANCHOR0
	add	x2, x4, x5
	lsr	w3, w1, 16
	ldr	x4, [x4, x5]
	ldrb	w2, [x2, 8]
	add	x2, x4, x2, lsl 8
	mov	w4, 128
	str	w4, [x2, 2056]
	and	w4, w1, 255
	str	wzr, [x2, 2052]
	str	wzr, [x2, 2052]
	str	w4, [x2, 2052]
	lsr	w4, w1, 8
	str	w4, [x2, 2052]
	str	w3, [x2, 2052]
	b	FlashSetRandomizer
	.size	FlashProgFirstCmd, .-FlashProgFirstCmd
	.section	.text.FlashEraseCmd,"ax",@progbits
	.align	2
	.global	FlashEraseCmd
	.type	FlashEraseCmd, %function
FlashEraseCmd:
	ubfiz	x0, x0, 4, 8
	adrp	x3, .LANCHOR0
	add	x3, x3, :lo12:.LANCHOR0
	add	x4, x3, x0
	ldr	x3, [x3, x0]
	ldrb	w0, [x4, 8]
	cbz	w2, .L51
	add	x2, x3, x0, lsl 8
	mov	w4, 96
	str	w4, [x2, 2056]
	and	w4, w1, 255
	str	w4, [x2, 2052]
	lsr	w4, w1, 8
	str	w4, [x2, 2052]
	lsr	w4, w1, 16
	str	w4, [x2, 2052]
	adrp	x2, .LANCHOR4
	ldr	w2, [x2, #:lo12:.LANCHOR4]
	add	w1, w1, w2
.L51:
	add	x0, x3, x0, lsl 8
	mov	w2, 96
	str	w2, [x0, 2056]
	and	w2, w1, 255
	str	w2, [x0, 2052]
	lsr	w2, w1, 8
	str	w2, [x0, 2052]
	lsr	w1, w1, 16
	str	w1, [x0, 2052]
	mov	w1, 208
	str	w1, [x0, 2056]
	ret
	.size	FlashEraseCmd, .-FlashEraseCmd
	.section	.text.FlashProgDpSecondCmd,"ax",@progbits
	.align	2
	.global	FlashProgDpSecondCmd
	.type	FlashProgDpSecondCmd, %function
FlashProgDpSecondCmd:
	and	w0, w0, 255
	adrp	x2, .LANCHOR8+11
	sbfiz	x5, x0, 4, 32
	adrp	x4, .LANCHOR0
	add	x4, x4, :lo12:.LANCHOR0
	ldrb	w6, [x2, #:lo12:.LANCHOR8+11]
	add	x2, x4, x5
	lsr	w3, w1, 16
	ldr	x4, [x4, x5]
	ldrb	w2, [x2, 8]
	add	x2, x4, x2, lsl 8
	and	w4, w1, 255
	str	w6, [x2, 2056]
	str	wzr, [x2, 2052]
	str	wzr, [x2, 2052]
	str	w4, [x2, 2052]
	lsr	w4, w1, 8
	str	w4, [x2, 2052]
	str	w3, [x2, 2052]
	b	FlashSetRandomizer
	.size	FlashProgDpSecondCmd, .-FlashProgDpSecondCmd
	.section	.text.FlashProgSecondCmd,"ax",@progbits
	.align	2
	.global	FlashProgSecondCmd
	.type	FlashProgSecondCmd, %function
FlashProgSecondCmd:
	ubfiz	x0, x0, 4, 8
	adrp	x1, .LANCHOR0
	add	x1, x1, :lo12:.LANCHOR0
	add	x2, x1, x0
	ldr	x1, [x1, x0]
	ldrb	w0, [x2, 8]
	add	x0, x0, 8
	add	x0, x1, x0, lsl 8
	mov	w1, 16
	str	w1, [x0, 8]
	ret
	.size	FlashProgSecondCmd, .-FlashProgSecondCmd
	.section	.text.FlashProgDpFirstCmd,"ax",@progbits
	.align	2
	.global	FlashProgDpFirstCmd
	.type	FlashProgDpFirstCmd, %function
FlashProgDpFirstCmd:
	ubfiz	x0, x0, 4, 8
	adrp	x1, .LANCHOR0
	add	x1, x1, :lo12:.LANCHOR0
	add	x3, x1, x0
	ldr	x2, [x1, x0]
	adrp	x0, .LANCHOR8+10
	ldrb	w1, [x0, #:lo12:.LANCHOR8+10]
	ldrb	w0, [x3, 8]
	add	x0, x0, 8
	add	x0, x2, x0, lsl 8
	str	w1, [x0, 8]
	ret
	.size	FlashProgDpFirstCmd, .-FlashProgDpFirstCmd
	.section	.text.FlashReadStatus,"ax",@progbits
	.align	2
	.global	FlashReadStatus
	.type	FlashReadStatus, %function
FlashReadStatus:
	ubfiz	x0, x0, 4, 8
	adrp	x1, .LANCHOR0
	add	x1, x1, :lo12:.LANCHOR0
	stp	x29, x30, [sp, -32]!
	add	x2, x1, x0
	add	x29, sp, 0
	ldr	x0, [x1, x0]
	str	x19, [sp, 16]
	ldrb	w19, [x2, 8]
	add	x19, x0, x19, lsl 8
	mov	w0, 112
	str	w0, [x19, 2056]
	mov	x0, 80
	bl	udelay
	ldr	w0, [x19, 2048]
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	FlashReadStatus, .-FlashReadStatus
	.section	.text.js_hash,"ax",@progbits
	.align	2
	.global	js_hash
	.type	js_hash, %function
js_hash:
	mov	x4, x0
	mov	w0, 42982
	mov	x3, 0
	movk	w0, 0x47c6, lsl 16
.L61:
	cmp	w1, w3
	bhi	.L62
	ret
.L62:
	lsr	w2, w0, 2
	ldrb	w5, [x4, x3]
	add	w2, w2, w0, lsl 5
	add	x3, x3, 1
	add	w2, w2, w5
	eor	w0, w0, w2
	b	.L61
	.size	js_hash, .-js_hash
	.section	.text.FlashLoadIdbInfo,"ax",@progbits
	.align	2
	.global	FlashLoadIdbInfo
	.type	FlashLoadIdbInfo, %function
FlashLoadIdbInfo:
	mov	w0, 0
	ret
	.size	FlashLoadIdbInfo, .-FlashLoadIdbInfo
	.section	.text.FlashPrintInfo,"ax",@progbits
	.align	2
	.global	FlashPrintInfo
	.type	FlashPrintInfo, %function
FlashPrintInfo:
	ret
	.size	FlashPrintInfo, .-FlashPrintInfo
	.section	.text.ToshibaSetRRPara,"ax",@progbits
	.align	2
	.global	ToshibaSetRRPara
	.type	ToshibaSetRRPara, %function
ToshibaSetRRPara:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	str	x27, [sp, 80]
	and	w27, w1, 255
	add	w2, w27, 1
	stp	x21, x22, [sp, 32]
	mov	x21, x0
	mov	w0, 5
	stp	x19, x20, [sp, 16]
	adrp	x20, .LANCHOR9
	umull	x2, w2, w0
	stp	x23, x24, [sp, 48]
	adrp	x0, .LANCHOR10
	add	x20, x20, :lo12:.LANCHOR9
	add	x24, x0, :lo12:.LANCHOR10
	stp	x25, x26, [sp, 64]
	adrp	x23, .LANCHOR13
	adrp	x25, .LANCHOR11
	adrp	x26, .LANCHOR12
	add	x23, x23, :lo12:.LANCHOR13
	add	x25, x25, :lo12:.LANCHOR11
	add	x26, x26, :lo12:.LANCHOR12
	add	x20, x20, x2
	add	x24, x24, x2
	mov	x22, x0
	mov	x19, 0
.L66:
	ldrb	w0, [x23]
	cmp	w0, w19
	bhi	.L70
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldr	x27, [sp, 80]
	ldp	x29, x30, [sp], 96
	ret
.L70:
	mov	w0, 85
	str	w0, [x21, 8]
	add	x0, x22, :lo12:.LANCHOR10
	ldrsb	w0, [x19, x0]
	str	w0, [x21, 4]
	mov	x0, 200
	bl	udelay
	ldrb	w0, [x25]
	cmp	w0, 34
	bne	.L67
	ldrsb	w0, [x24, x19]
.L72:
	add	x19, x19, 1
	str	w0, [x21]
	b	.L66
.L67:
	cmp	w0, 35
	bne	.L69
	ldrsb	w0, [x20, x19]
	b	.L72
.L69:
	ldrsb	w0, [x26, w27, sxtw]
	b	.L72
	.size	ToshibaSetRRPara, .-ToshibaSetRRPara
	.section	.text.SamsungSetRRPara,"ax",@progbits
	.align	2
	.global	SamsungSetRRPara
	.type	SamsungSetRRPara, %function
SamsungSetRRPara:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x21, x22, [sp, 32]
	ubfiz	x21, x1, 2, 8
	mov	x22, x0
	add	x21, x21, 4
	adrp	x0, .LANCHOR14
	add	x0, x0, :lo12:.LANCHOR14
	stp	x19, x20, [sp, 16]
	add	x21, x0, x21
	stp	x23, x24, [sp, 48]
	mov	x19, x0
	adrp	x23, .LANCHOR13
	add	x23, x23, :lo12:.LANCHOR13
	mov	x20, 0
	mov	w24, 161
.L74:
	ldrb	w0, [x23]
	cmp	w0, w20
	bhi	.L75
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
.L75:
	str	w24, [x22, 8]
	str	wzr, [x22]
	ldrsb	w0, [x20, x19]
	str	w0, [x22]
	ldrsb	w0, [x21, x20]
	add	x20, x20, 1
	str	w0, [x22]
	mov	x0, 300
	bl	udelay
	b	.L74
	.size	SamsungSetRRPara, .-SamsungSetRRPara
	.section	.text.LogAddr2PhyAddr,"ax",@progbits
	.align	2
	.global	LogAddr2PhyAddr
	.type	LogAddr2PhyAddr, %function
LogAddr2PhyAddr:
	adrp	x6, .LANCHOR15
	add	x6, x6, :lo12:.LANCHOR15
	and	w4, w4, 255
	ldrh	w8, [x6, 12]
	ldrh	w5, [x6, 14]
	mul	w5, w5, w8
	and	w8, w5, 65535
	adrp	x5, .LANCHOR4
	ldrh	w7, [x5, #:lo12:.LANCHOR4]
	adrp	x5, .LANCHOR2
	ldrb	w6, [x5, #:lo12:.LANCHOR2]
	ubfiz	w5, w7, 1, 15
	cmp	w6, 1
	ldr	w6, [x0, 4]
	csel	w7, w5, w7, eq
	cmp	w1, 1
	ubfx	x11, x6, 10, 16
	and	w6, w6, 1023
	udiv	w5, w11, w8
	and	w10, w5, 65535
	msub	w5, w5, w8, w11
	and	w5, w5, 65535
	bne	.L79
	adrp	x1, .LANCHOR16
	ldrb	w1, [x1, #:lo12:.LANCHOR16]
	cbnz	w1, .L79
	adrp	x1, .LANCHOR17
	add	x1, x1, :lo12:.LANCHOR17
	ldrh	w6, [x1, w6, sxtw 1]
.L79:
	uxtw	x8, w10
	adrp	x1, .LANCHOR18
	add	x1, x1, :lo12:.LANCHOR18
	cmp	w4, 1
	ldr	w1, [x1, x8, lsl 2]
	madd	w5, w5, w7, w1
	add	w5, w5, w6
	str	w5, [x2]
	str	w10, [x3]
	bls	.L81
	ldr	w1, [x0, 4]
	ldr	w0, [x0, 60]
	add	w1, w1, 1024
	cmp	w1, w0
	cset	w0, eq
	ret
.L81:
	mov	w0, 0
	ret
	.size	LogAddr2PhyAddr, .-LogAddr2PhyAddr
	.section	.text.FlashReadStatusEN,"ax",@progbits
	.align	2
	.global	FlashReadStatusEN
	.type	FlashReadStatusEN, %function
FlashReadStatusEN:
	stp	x29, x30, [sp, -32]!
	ubfiz	x0, x0, 4, 8
	adrp	x3, .LANCHOR0
	add	x3, x3, :lo12:.LANCHOR0
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	add	x4, x3, x0
	ldr	x20, [x3, x0]
	adrp	x0, .LANCHOR7
	ldr	x0, [x0, #:lo12:.LANCHOR7]
	ldrb	w19, [x4, 8]
	ldrb	w0, [x0, 8]
	cmp	w0, 2
	bne	.L83
	and	w2, w2, 255
	adrp	x0, .LANCHOR8
	cbnz	w2, .L84
	add	x2, x0, :lo12:.LANCHOR8
	ldrb	w3, [x2, 13]
.L94:
	add	x2, x19, 8
	add	x0, x0, :lo12:.LANCHOR8
	add	x2, x20, x2, lsl 8
	str	w3, [x2, 8]
	ldrb	w4, [x0, 15]
	cbz	w4, .L88
	add	x3, x19, 8
	mov	w2, 0
	add	x3, x20, x3, lsl 8
.L87:
	cmp	w2, w4
	bcc	.L89
.L88:
	add	x19, x19, 8
	mov	x0, 80
	lsl	x19, x19, 8
	bl	udelay
	ldr	w0, [x20, x19]
	ldp	x19, x20, [sp, 16]
	and	w0, w0, 255
	ldp	x29, x30, [sp], 32
	ret
.L84:
	add	x2, x0, :lo12:.LANCHOR8
	ldrb	w3, [x2, 14]
	b	.L94
.L89:
	lsl	w0, w2, 3
	add	w2, w2, 1
	lsr	w0, w1, w0
	and	w0, w0, 255
	str	w0, [x3, 4]
	b	.L87
.L83:
	add	x0, x19, 8
	mov	w1, 112
	add	x0, x20, x0, lsl 8
	str	w1, [x0, 8]
	b	.L88
	.size	FlashReadStatusEN, .-FlashReadStatusEN
	.section	.text.FlashWaitReadyEN,"ax",@progbits
	.align	2
	.global	FlashWaitReadyEN
	.type	FlashWaitReadyEN, %function
FlashWaitReadyEN:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	and	w19, w0, 255
	str	x21, [sp, 32]
	mov	w20, w1
	and	w21, w2, 255
.L99:
	mov	w1, w20
	mov	w2, w21
	mov	w0, w19
	bl	FlashReadStatusEN
	mov	w1, w0
	cmp	w0, 255
	beq	.L99
	tbz	x1, 6, .L99
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	FlashWaitReadyEN, .-FlashWaitReadyEN
	.section	.text.NandcReadDontCaseBusyEn,"ax",@progbits
	.align	2
	.global	NandcReadDontCaseBusyEn
	.type	NandcReadDontCaseBusyEn, %function
NandcReadDontCaseBusyEn:
	ret
	.size	NandcReadDontCaseBusyEn, .-NandcReadDontCaseBusyEn
	.section	.text.NandcGetChipIf,"ax",@progbits
	.align	2
	.global	NandcGetChipIf
	.type	NandcGetChipIf, %function
NandcGetChipIf:
	ubfiz	x0, x0, 4, 8
	adrp	x1, .LANCHOR0
	add	x1, x1, :lo12:.LANCHOR0
	add	x2, x1, x0
	ldr	x0, [x1, x0]
	ldrb	w2, [x2, 8]
	add	x2, x2, 8
	add	x0, x0, x2, lsl 8
	ret
	.size	NandcGetChipIf, .-NandcGetChipIf
	.section	.text.NandcSetDdrPara,"ax",@progbits
	.align	2
	.global	NandcSetDdrPara
	.type	NandcSetDdrPara, %function
NandcSetDdrPara:
	adrp	x1, .LANCHOR19
	and	w0, w0, 255
	lsl	w2, w0, 8
	ldr	x1, [x1, #:lo12:.LANCHOR19]
	orr	w0, w2, w0, lsl 16
	orr	w0, w0, 1
	str	w0, [x1, 304]
	ret
	.size	NandcSetDdrPara, .-NandcSetDdrPara
	.section	.text.NandcSetDdrDiv,"ax",@progbits
	.align	2
	.global	NandcSetDdrDiv
	.type	NandcSetDdrDiv, %function
NandcSetDdrDiv:
	adrp	x1, .LANCHOR19
	and	w0, w0, 255
	mov	w2, 16640
	orr	w0, w0, w2
	ldr	x1, [x1, #:lo12:.LANCHOR19]
	str	w0, [x1, 344]
	ret
	.size	NandcSetDdrDiv, .-NandcSetDdrDiv
	.section	.text.NandcSetDdrMode,"ax",@progbits
	.align	2
	.global	NandcSetDdrMode
	.type	NandcSetDdrMode, %function
NandcSetDdrMode:
	adrp	x1, .LANCHOR19
	cmp	w0, 0
	ldr	x2, [x1, #:lo12:.LANCHOR19]
	ldr	w1, [x2]
	and	w3, w1, -8193
	orr	w1, w1, 253952
	csel	w1, w1, w3, ne
	str	w1, [x2]
	ret
	.size	NandcSetDdrMode, .-NandcSetDdrMode
	.section	.text.NandcSetMode,"ax",@progbits
	.align	2
	.global	NandcSetMode
	.type	NandcSetMode, %function
NandcSetMode:
	adrp	x1, .LANCHOR19
	and	w0, w0, 255
	tst	w0, 6
	ldr	x2, [x1, #:lo12:.LANCHOR19]
	ldr	w1, [x2]
	beq	.L111
	orr	w1, w1, 24576
	tst	x0, 4
	and	w1, w1, -32769
	mov	w0, 16641
	orr	w1, w1, 196608
	str	w0, [x2, 344]
	mov	w0, 6659
	orr	w3, w1, 32768
	movk	w0, 0x1a, lsl 16
	str	w0, [x2, 304]
	csel	w1, w3, w1, ne
	mov	w0, 38
	str	w0, [x2, 308]
	mov	w0, 39
	str	w0, [x2, 308]
.L113:
	mov	w0, 0
	str	w1, [x2]
	ret
.L111:
	and	w1, w1, -8193
	b	.L113
	.size	NandcSetMode, .-NandcSetMode
	.section	.text.NandcFlashCs,"ax",@progbits
	.align	2
	.global	NandcFlashCs
	.type	NandcFlashCs, %function
NandcFlashCs:
	ubfiz	x0, x0, 4, 8
	adrp	x1, .LANCHOR0
	add	x1, x1, :lo12:.LANCHOR0
	add	x3, x1, x0
	ldr	x2, [x1, x0]
	mov	w1, 1
	ldrb	w3, [x3, 8]
	ldr	w0, [x2]
	lsl	w1, w1, w3
	bfi	w0, w1, 0, 8
	str	w0, [x2]
	ret
	.size	NandcFlashCs, .-NandcFlashCs
	.section	.text.NandcFlashDeCs,"ax",@progbits
	.align	2
	.global	NandcFlashDeCs
	.type	NandcFlashDeCs, %function
NandcFlashDeCs:
	ubfiz	x0, x0, 4, 8
	adrp	x1, .LANCHOR0
	add	x1, x1, :lo12:.LANCHOR0
	ldr	x1, [x1, x0]
	ldr	w0, [x1]
	and	w0, w0, -256
	and	w0, w0, -131073
	str	w0, [x1]
	ret
	.size	NandcFlashDeCs, .-NandcFlashDeCs
	.section	.text.HynixSetRRPara,"ax",@progbits
	.align	2
	.global	HynixSetRRPara
	.type	HynixSetRRPara, %function
HynixSetRRPara:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x21, x22, [sp, 32]
	and	w22, w0, 255
	adrp	x0, .LANCHOR7
	stp	x19, x20, [sp, 16]
	stp	x25, x26, [sp, 64]
	mov	x20, x2
	ldr	x0, [x0, #:lo12:.LANCHOR7]
	and	w26, w1, 255
	stp	x23, x24, [sp, 48]
	and	w21, w3, 255
	adrp	x19, .LANCHOR20
	ldrb	w0, [x0, 19]
	cmp	w0, 6
	bne	.L119
	add	x0, x19, :lo12:.LANCHOR20
	ubfiz	x19, x22, 6, 8
	add	x19, x19, 20
	add	x19, x19, x21, uxtw 2
.L126:
	add	x19, x0, x19
.L120:
	sxtw	x25, w22
	adrp	x0, .LANCHOR0
	lsl	x1, x25, 4
	add	x0, x0, :lo12:.LANCHOR0
	add	x2, x0, x1
	and	x26, x26, 255
	mov	x24, 0
	ldr	x23, [x0, x1]
	mov	w0, w22
	ldrb	w5, [x2, 8]
	bl	NandcFlashCs
	ubfiz	x5, x5, 8, 8
	add	x23, x23, x5
	mov	w0, 54
	str	w0, [x23, 2056]
.L123:
	cmp	x24, x26
	bne	.L124
	mov	w0, 22
	str	w0, [x23, 2056]
	mov	w0, w22
	bl	NandcFlashDeCs
	adrp	x0, .LANCHOR21
	add	x0, x0, :lo12:.LANCHOR21
	strb	w21, [x0, x25]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
.L119:
	cmp	w0, 7
	bne	.L121
	add	x0, x19, :lo12:.LANCHOR20
	mov	x1, 28
	mov	w19, 160
	umaddl	x1, w19, w22, x1
	mov	w19, 10
	umaddl	x19, w21, w19, x1
	b	.L126
.L121:
	cmp	w0, 8
	bne	.L122
	add	x19, x19, :lo12:.LANCHOR20
	add	x0, x19, 28
	add	w19, w21, w21, lsl 2
	add	x19, x0, x19, sxtw
	b	.L120
.L122:
	add	x0, x19, :lo12:.LANCHOR20
	and	x19, x21, 255
	add	x19, x19, 2
	add	x19, x19, x22, uxtw 3
	add	x19, x0, x19, lsl 3
	add	x19, x19, 4
	b	.L120
.L124:
	ldrb	w0, [x20, x24]
	str	w0, [x23, 2052]
	mov	x0, 200
	bl	udelay
	ldrsb	w0, [x19, x24]
	add	x24, x24, 1
	str	w0, [x23, 2048]
	b	.L123
	.size	HynixSetRRPara, .-HynixSetRRPara
	.section	.text.FlashSetReadRetryDefault,"ax",@progbits
	.align	2
	.global	FlashSetReadRetryDefault
	.type	FlashSetReadRetryDefault, %function
FlashSetReadRetryDefault:
	adrp	x0, .LANCHOR7
	ldr	x0, [x0, #:lo12:.LANCHOR7]
	ldrb	w0, [x0, 19]
	sub	w0, w0, #1
	and	w0, w0, 255
	cmp	w0, 7
	bhi	.L134
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	adrp	x20, .LANCHOR20
	add	x20, x20, :lo12:.LANCHOR20
	stp	x21, x22, [sp, 32]
	adrp	x21, .LANCHOR22
	add	x22, x20, 4
	add	x21, x21, :lo12:.LANCHOR22
	mov	x19, 0
.L130:
	lsl	x1, x19, 3
	and	w0, w19, 255
	ldrb	w1, [x1, x21]
	cmp	w1, 173
	bne	.L129
	ldrb	w1, [x20, 1]
	mov	w3, 0
	mov	x2, x22
	bl	HynixSetRRPara
.L129:
	add	x19, x19, 1
	cmp	x19, 4
	bne	.L130
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
.L134:
	ret
	.size	FlashSetReadRetryDefault, .-FlashSetReadRetryDefault
	.section	.text.FlashWaitCmdDone,"ax",@progbits
	.align	2
	.global	FlashWaitCmdDone
	.type	FlashWaitCmdDone, %function
FlashWaitCmdDone:
	and	x4, x0, 255
	mov	x0, 24
	stp	x29, x30, [sp, -32]!
	adrp	x1, .LANCHOR23
	add	x1, x1, :lo12:.LANCHOR23
	mul	x0, x4, x0
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	add	x19, x1, x0
	ldr	x2, [x19, 8]
	cbz	x2, .L139
	ldrb	w20, [x1, x0]
	mov	w0, w20
	bl	NandcFlashCs
	adrp	x0, .LANCHOR18
	add	x0, x0, :lo12:.LANCHOR18
	ldr	w1, [x19, 4]
	ldr	w0, [x0, x4, lsl 2]
	cmp	w0, 0
	mov	w0, w20
	cset	w2, ne
	bl	FlashWaitReadyEN
	mov	w2, w0
	mov	w0, w20
	bl	NandcFlashDeCs
	sbfx	x0, x2, 0, 1
	ldr	x1, [x19, 8]
	str	w0, [x1]
	ldr	x1, [x19, 16]
	str	xzr, [x19, 8]
	cbz	x1, .L139
	str	w0, [x1]
	str	xzr, [x19, 16]
.L139:
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	FlashWaitCmdDone, .-FlashWaitCmdDone
	.section	.text.NandcDelayns,"ax",@progbits
	.align	2
	.global	NandcDelayns
	.type	NandcDelayns, %function
NandcDelayns:
	stp	x29, x30, [sp, -16]!
	uxtw	x0, w0
	add	x29, sp, 0
	bl	udelay
	mov	w0, 0
	ldp	x29, x30, [sp], 16
	ret
	.size	NandcDelayns, .-NandcDelayns
	.section	.text.NandcWaitFlashReadyNoDelay,"ax",@progbits
	.align	2
	.global	NandcWaitFlashReadyNoDelay
	.type	NandcWaitFlashReadyNoDelay, %function
NandcWaitFlashReadyNoDelay:
	stp	x29, x30, [sp, -48]!
	ubfiz	x0, x0, 4, 8
	adrp	x1, .LANCHOR0
	add	x1, x1, :lo12:.LANCHOR0
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w19, 34464
	ldr	x20, [x1, x0]
	movk	w19, 0x1, lsl 16
.L149:
	ldr	w0, [x20]
	str	w0, [x29, 40]
	ldr	w0, [x29, 40]
	tbnz	x0, 9, .L150
	mov	x0, 10
	bl	udelay
	subs	w19, w19, #1
	bne	.L149
	mov	w0, -1
.L147:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
.L150:
	mov	w0, 0
	b	.L147
	.size	NandcWaitFlashReadyNoDelay, .-NandcWaitFlashReadyNoDelay
	.section	.text.NandcWaitFlashReady,"ax",@progbits
	.align	2
	.global	NandcWaitFlashReady
	.type	NandcWaitFlashReady, %function
NandcWaitFlashReady:
	stp	x29, x30, [sp, -48]!
	ubfiz	x0, x0, 4, 8
	adrp	x1, .LANCHOR0
	add	x1, x1, :lo12:.LANCHOR0
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w19, 34464
	movk	w19, 0x1, lsl 16
	ldr	x20, [x1, x0]
	mov	x0, 130
	bl	udelay
.L155:
	ldr	w0, [x20]
	str	w0, [x29, 40]
	ldr	w0, [x29, 40]
	tbnz	x0, 9, .L156
	mov	x0, 10
	bl	udelay
	subs	w19, w19, #1
	bne	.L155
	mov	w0, -1
.L153:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
.L156:
	mov	w0, 0
	b	.L153
	.size	NandcWaitFlashReady, .-NandcWaitFlashReady
	.section	.text.FlashReset,"ax",@progbits
	.align	2
	.global	FlashReset
	.type	FlashReset, %function
FlashReset:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	and	w19, w0, 255
	sbfiz	x1, x19, 4, 32
	adrp	x0, .LANCHOR0
	add	x0, x0, :lo12:.LANCHOR0
	add	x2, x0, x1
	ldr	x5, [x0, x1]
	mov	w0, w19
	ldrb	w4, [x2, 8]
	bl	NandcFlashCs
	add	x4, x4, 8
	add	x4, x5, x4, lsl 8
	mov	w0, 255
	str	w0, [x4, 8]
	mov	w0, w19
	bl	NandcWaitFlashReady
	mov	w0, w19
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	b	NandcFlashDeCs
	.size	FlashReset, .-FlashReset
	.section	.text.flash_enter_slc_mode,"ax",@progbits
	.align	2
	.global	flash_enter_slc_mode
	.type	flash_enter_slc_mode, %function
flash_enter_slc_mode:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x21, x22, [sp, 32]
	and	w21, w0, 255
	adrp	x0, .LANCHOR16
	stp	x19, x20, [sp, 16]
	ldrb	w0, [x0, #:lo12:.LANCHOR16]
	cbz	w0, .L161
	mov	w0, w21
	bl	NandcFlashCs
	sxtw	x0, w21
	adrp	x1, .LANCHOR0
	lsl	x2, x0, 4
	add	x1, x1, :lo12:.LANCHOR0
	add	x3, x1, x2
	lsl	x0, x0, 3
	ldr	x22, [x1, x2]
	adrp	x1, .LANCHOR22
	add	x1, x1, :lo12:.LANCHOR22
	ldrb	w19, [x3, 8]
	ldrb	w0, [x1, x0]
	cmp	w0, 44
	bne	.L163
	ubfiz	x20, x19, 8, 8
	mov	w0, 239
	add	x20, x22, x20
	str	w0, [x20, 2056]
	mov	w0, 145
	str	w0, [x20, 2052]
	mov	x0, 50
	bl	udelay
	str	wzr, [x20, 2048]
	mov	w0, 1
	str	w0, [x20, 2048]
	str	wzr, [x20, 2048]
	mov	x0, 100
	str	wzr, [x20, 2048]
	bl	udelay
.L163:
	add	x19, x19, 8
	mov	w0, w21
	add	x19, x22, x19, lsl 8
	bl	NandcWaitFlashReadyNoDelay
	mov	w0, 218
	str	w0, [x19, 8]
	mov	w0, w21
	bl	NandcWaitFlashReady
	adrp	x0, .LANCHOR24
	mov	w1, 2
	strb	w1, [x0, #:lo12:.LANCHOR24]
.L161:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	flash_enter_slc_mode, .-flash_enter_slc_mode
	.section	.text.flash_exit_slc_mode,"ax",@progbits
	.align	2
	.global	flash_exit_slc_mode
	.type	flash_exit_slc_mode, %function
flash_exit_slc_mode:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x21, x22, [sp, 32]
	and	w21, w0, 255
	adrp	x0, .LANCHOR16
	stp	x19, x20, [sp, 16]
	ldrb	w0, [x0, #:lo12:.LANCHOR16]
	cbz	w0, .L168
	mov	w0, w21
	bl	NandcFlashCs
	sxtw	x0, w21
	adrp	x1, .LANCHOR0
	lsl	x2, x0, 4
	add	x1, x1, :lo12:.LANCHOR0
	add	x3, x1, x2
	lsl	x0, x0, 3
	ldr	x22, [x1, x2]
	adrp	x1, .LANCHOR22
	add	x1, x1, :lo12:.LANCHOR22
	ldrb	w19, [x3, 8]
	ldrb	w0, [x1, x0]
	cmp	w0, 44
	bne	.L170
	ubfiz	x20, x19, 8, 8
	mov	w0, 239
	add	x20, x22, x20
	str	w0, [x20, 2056]
	mov	w0, 145
	str	w0, [x20, 2052]
	mov	x0, 50
	bl	udelay
	mov	w0, 2
	str	w0, [x20, 2048]
	mov	w0, 1
	str	w0, [x20, 2048]
	str	wzr, [x20, 2048]
	mov	x0, 100
	str	wzr, [x20, 2048]
	bl	udelay
.L170:
	add	x19, x19, 8
	mov	w0, w21
	add	x19, x22, x19, lsl 8
	bl	NandcWaitFlashReadyNoDelay
	mov	w0, 223
	str	w0, [x19, 8]
	mov	w0, w21
	bl	NandcWaitFlashReady
	adrp	x0, .LANCHOR24
	strb	wzr, [x0, #:lo12:.LANCHOR24]
.L168:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	flash_exit_slc_mode, .-flash_exit_slc_mode
	.section	.text.FlashEraseBlock,"ax",@progbits
	.align	2
	.global	FlashEraseBlock
	.type	FlashEraseBlock, %function
FlashEraseBlock:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	and	w19, w0, 255
	mov	w20, w1
	str	x21, [sp, 32]
	mov	w0, w19
	mov	w21, w2
	bl	NandcWaitFlashReady
	mov	w0, w19
	bl	NandcFlashCs
	mov	w2, w21
	mov	w1, w20
	mov	w0, w19
	bl	FlashEraseCmd
	mov	w0, w19
	bl	NandcWaitFlashReady
	mov	w1, w20
	mov	w0, w19
	bl	FlashReadStatus
	mov	w2, w0
	mov	w0, w19
	bl	NandcFlashDeCs
	ldr	x21, [sp, 32]
	and	w0, w2, 1
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.size	FlashEraseBlock, .-FlashEraseBlock
	.section	.text.FlashSetInterfaceMode,"ax",@progbits
	.align	2
	.global	FlashSetInterfaceMode
	.type	FlashSetInterfaceMode, %function
FlashSetInterfaceMode:
	stp	x29, x30, [sp, -16]!
	adrp	x1, .LANCHOR25
	adrp	x2, .LANCHOR0
	add	x2, x2, :lo12:.LANCHOR0
	add	x29, sp, 0
	ldrb	w1, [x1, #:lo12:.LANCHOR25]
	adrp	x7, .LANCHOR22
	add	x2, x2, 8
	add	x7, x7, :lo12:.LANCHOR22
	and	w12, w1, 4
	and	w6, w1, 1
	mov	x5, 0
	mov	w13, 69
	mov	w8, 239
	mov	w10, 128
	mov	w11, 1
	mov	w14, 35
	mov	w15, 32
	mov	w16, 5
	mov	w17, 44
.L187:
	ldrb	w3, [x5, x7]
	ldrb	w4, [x2]
	cmp	w3, 152
	ccmp	w3, w13, 4, ne
	beq	.L178
	cmp	w3, 173
	ccmp	w3, w17, 4, ne
	bne	.L179
.L178:
	cmp	w0, 1
	ldr	x1, [x2, -8]
	bne	.L180
	cbz	w6, .L179
	ubfiz	x4, x4, 8, 8
	cmp	w3, 173
	add	x1, x1, x4
	str	w8, [x1, 2056]
	bne	.L181
	str	w0, [x1, 2052]
.L199:
	str	wzr, [x1, 2048]
	b	.L185
.L181:
	cmp	w3, 44
	bne	.L183
	str	w0, [x1, 2052]
	str	w16, [x1, 2048]
.L185:
	str	wzr, [x1, 2048]
	str	wzr, [x1, 2048]
	str	wzr, [x1, 2048]
.L179:
	add	x5, x5, 8
	add	x2, x2, 16
	cmp	x5, 32
	bne	.L187
	mov	w0, 0
	bl	NandcWaitFlashReady
	mov	w0, 0
	ldp	x29, x30, [sp], 16
	ret
.L183:
	str	w10, [x1, 2052]
	str	w0, [x1, 2048]
	b	.L185
.L180:
	cbz	w12, .L179
	ubfiz	x4, x4, 8, 8
	cmp	w3, 173
	add	x1, x1, x4
	str	w8, [x1, 2056]
	bne	.L184
	str	w11, [x1, 2052]
	str	w15, [x1, 2048]
	b	.L185
.L184:
	cmp	w3, 44
	bne	.L186
	str	w11, [x1, 2052]
	str	w14, [x1, 2048]
	b	.L185
.L186:
	str	w10, [x1, 2052]
	b	.L199
	.size	FlashSetInterfaceMode, .-FlashSetInterfaceMode
	.section	.text.SandiskSetRRPara,"ax",@progbits
	.align	2
	.global	SandiskSetRRPara
	.type	SandiskSetRRPara, %function
SandiskSetRRPara:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	mov	w0, 239
	and	w19, w1, 255
	str	w0, [x20, 8]
	mov	w0, 17
	str	w0, [x20, 4]
	mov	x0, 200
	bl	udelay
	adrp	x0, .LANCHOR13
	add	w1, w19, 1
	adrp	x2, .LANCHOR9
	add	x2, x2, :lo12:.LANCHOR9
	ldrb	w3, [x0, #:lo12:.LANCHOR13]
	adrp	x0, .LANCHOR11
	ldrb	w4, [x0, #:lo12:.LANCHOR11]
	mov	w0, 5
	umull	x1, w1, w0
	adrp	x0, .LANCHOR10
	add	x0, x0, :lo12:.LANCHOR10
	add	x2, x2, x1
	add	x1, x0, x1
	mov	x0, 0
.L201:
	cmp	w3, w0
	bhi	.L204
	ldp	x19, x20, [sp, 16]
	mov	w0, 0
	ldp	x29, x30, [sp], 32
	b	NandcWaitFlashReady
.L204:
	cmp	w4, 67
	bne	.L202
	ldrsb	w5, [x1, x0]
.L206:
	add	x0, x0, 1
	str	w5, [x20]
	b	.L201
.L202:
	ldrsb	w5, [x2, x0]
	b	.L206
	.size	SandiskSetRRPara, .-SandiskSetRRPara
	.section	.text.micron_auto_read_calibration_config,"ax",@progbits
	.align	2
	.global	micron_auto_read_calibration_config
	.type	micron_auto_read_calibration_config, %function
micron_auto_read_calibration_config:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	and	w19, w0, 255
	mov	w20, w1
	mov	w0, w19
	bl	NandcWaitFlashReady
	sbfiz	x0, x19, 4, 32
	adrp	x2, .LANCHOR0
	add	x2, x2, :lo12:.LANCHOR0
	add	x1, x2, x0
	ldr	x0, [x2, x0]
	ldrb	w19, [x1, 8]
	add	x19, x0, x19, lsl 8
	mov	w0, 239
	str	w0, [x19, 2056]
	mov	w0, 150
	str	w0, [x19, 2052]
	mov	x0, 200
	bl	udelay
	str	w20, [x19, 2048]
	str	wzr, [x19, 2048]
	str	wzr, [x19, 2048]
	str	wzr, [x19, 2048]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	micron_auto_read_calibration_config, .-micron_auto_read_calibration_config
	.section	.text.FlashEraseSLc2KBlocks,"ax",@progbits
	.align	2
	.global	FlashEraseSLc2KBlocks
	.type	FlashEraseSLc2KBlocks, %function
FlashEraseSLc2KBlocks:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x21, x22, [sp, 32]
	mov	w22, 56
	stp	x23, x24, [sp, 48]
	and	w21, w1, 255
	umaddl	x22, w1, w22, x0
	stp	x19, x20, [sp, 16]
	adrp	x23, .LANCHOR26
	mov	x20, x0
	add	x23, x23, :lo12:.LANCHOR26
	adrp	x24, .LANCHOR27
.L210:
	cmp	x20, x22
	bne	.L215
	ldp	x19, x20, [sp, 16]
	mov	w0, 0
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
.L215:
	mov	w1, 0
	mov	w4, w21
	add	x3, x29, 76
	add	x2, x29, 72
	mov	x0, x20
	bl	LogAddr2PhyAddr
	ldrb	w1, [x23]
	ldr	w0, [x29, 76]
	cmp	w1, w0
	bhi	.L211
	mov	w0, -1
	str	w0, [x20]
.L212:
	sub	w21, w21, #1
	add	x20, x20, 56
	and	w21, w21, 255
	b	.L210
.L211:
	uxtw	x0, w0
	add	x1, x24, :lo12:.LANCHOR27
	ldrb	w19, [x1, x0]
	mov	x1, 24
	mul	x0, x0, x1
	adrp	x1, .LANCHOR23
	add	x1, x1, :lo12:.LANCHOR23
	strb	w19, [x1, x0]
	mov	w0, w19
	bl	NandcWaitFlashReady
	mov	w0, w19
	bl	NandcFlashCs
	ldr	w1, [x29, 72]
	mov	w2, 0
	mov	w0, w19
	bl	FlashEraseCmd
	mov	w0, w19
	bl	NandcWaitFlashReady
	ldr	w1, [x29, 72]
	mov	w0, w19
	bl	FlashReadStatus
	sbfx	x0, x0, 0, 1
	str	w0, [x20]
	adrp	x0, .LANCHOR4
	ldr	w1, [x29, 72]
	mov	w2, 0
	ldr	w0, [x0, #:lo12:.LANCHOR4]
	add	w1, w1, w0
	mov	w0, w19
	bl	FlashEraseCmd
	mov	w0, w19
	bl	NandcWaitFlashReady
	ldr	w1, [x29, 72]
	mov	w0, w19
	bl	FlashReadStatus
	tbz	x0, 0, .L213
	mov	w0, -1
	str	w0, [x20]
.L213:
	ldr	w0, [x20]
	cmn	w0, #1
	bne	.L214
	ldr	w1, [x29, 72]
	adrp	x0, .LC1
	add	x0, x0, :lo12:.LC1
	bl	printf
.L214:
	mov	w0, w19
	bl	NandcFlashDeCs
	b	.L212
	.size	FlashEraseSLc2KBlocks, .-FlashEraseSLc2KBlocks
	.section	.text.FlashEraseBlocks,"ax",@progbits
	.align	2
	.global	FlashEraseBlocks
	.type	FlashEraseBlocks, %function
FlashEraseBlocks:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x23, x24, [sp, 48]
	mov	w24, w1
	adrp	x1, .LANCHOR2
	stp	x21, x22, [sp, 32]
	stp	x19, x20, [sp, 16]
	mov	w22, w2
	ldrb	w1, [x1, #:lo12:.LANCHOR2]
	stp	x25, x26, [sp, 64]
	cbnz	w1, .L221
	adrp	x25, .LANCHOR23
	mov	x23, x0
	add	x26, x25, :lo12:.LANCHOR23
	mov	w19, 0
.L222:
	cmp	w19, w22
	adrp	x13, .LANCHOR26
	bcc	.L231
	adrp	x20, .LANCHOR16
	adrp	x21, .LANCHOR23
	add	x22, x13, :lo12:.LANCHOR26
	add	x20, x20, :lo12:.LANCHOR16
	add	x21, x21, :lo12:.LANCHOR23
	mov	x19, 0
.L232:
	ldrb	w0, [x22]
	cmp	w0, w19
	bhi	.L234
	mov	w0, 0
	b	.L220
.L221:
	mov	w1, w2
	bl	FlashEraseSLc2KBlocks
.L220:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 96
	ret
.L231:
	mov	w12, 56
	mov	w1, 0
	sub	w4, w22, w19
	add	x3, x29, 92
	umull	x12, w19, w12
	add	x2, x29, 88
	add	x20, x23, x12
	mov	x0, x20
	bl	LogAddr2PhyAddr
	mov	w21, w0
	ldrb	w1, [x13, #:lo12:.LANCHOR26]
	ldr	w0, [x29, 92]
	cmp	w1, w0
	bhi	.L224
	mov	w0, -1
	str	w0, [x23, x12]
.L225:
	add	w19, w19, 1
	b	.L222
.L224:
	adrp	x1, .LANCHOR28
	add	x2, x25, :lo12:.LANCHOR23
	mov	x3, 24
	ldrb	w1, [x1, #:lo12:.LANCHOR28]
	cmp	w1, 0
	uxtw	x1, w0
	csel	w21, w21, wzr, ne
	madd	x1, x1, x3, x2
	ldr	x1, [x1, 8]
	cbz	x1, .L227
	bl	FlashWaitCmdDone
.L227:
	ldp	w2, w1, [x29, 88]
	mov	x0, 24
	madd	x0, x1, x0, x26
	str	w2, [x0, 4]
	stp	x20, xzr, [x0, 8]
	cbz	w21, .L228
	add	w2, w19, 1
	mov	w3, 56
	umaddl	x2, w2, w3, x23
	str	x2, [x0, 16]
.L228:
	adrp	x0, .LANCHOR27
	add	x0, x0, :lo12:.LANCHOR27
	ldrb	w20, [x0, x1]
	mov	x0, 24
	mul	x1, x1, x0
	mov	w0, w20
	strb	w20, [x26, x1]
	bl	NandcFlashCs
	cmp	w24, 1
	bne	.L229
	adrp	x0, .LANCHOR16
	ldrb	w0, [x0, #:lo12:.LANCHOR16]
	cbz	w0, .L229
	mov	w0, w20
	bl	flash_enter_slc_mode
.L230:
	ldr	w1, [x29, 92]
	adrp	x0, .LANCHOR18
	add	x0, x0, :lo12:.LANCHOR18
	add	w19, w19, w21
	ldr	w0, [x0, x1, lsl 2]
	ldr	w1, [x29, 88]
	cmp	w0, 0
	mov	w0, w20
	cset	w2, ne
	bl	FlashWaitReadyEN
	ldr	w1, [x29, 88]
	mov	w2, w21
	mov	w0, w20
	bl	FlashEraseCmd
	mov	w0, w20
	bl	NandcFlashDeCs
	b	.L225
.L229:
	mov	w0, w20
	bl	flash_exit_slc_mode
	b	.L230
.L234:
	mov	w0, w19
	bl	FlashWaitCmdDone
	cmp	w24, 1
	bne	.L233
	ldrb	w0, [x20]
	cbz	w0, .L233
	mov	x0, 24
	mul	x0, x19, x0
	ldrb	w0, [x0, x21]
	bl	flash_exit_slc_mode
.L233:
	add	x19, x19, 1
	b	.L232
	.size	FlashEraseBlocks, .-FlashEraseBlocks
	.section	.text.FlashReadDpCmd,"ax",@progbits
	.align	2
	.global	FlashReadDpCmd
	.type	FlashReadDpCmd, %function
FlashReadDpCmd:
	stp	x29, x30, [sp, -64]!
	adrp	x7, .LANCHOR7
	add	x29, sp, 0
	stp	x21, x22, [sp, 32]
	and	w22, w0, 255
	mov	w21, w1
	adrp	x0, .LANCHOR0
	sbfiz	x1, x22, 4, 32
	add	x0, x0, :lo12:.LANCHOR0
	add	x3, x0, x1
	stp	x19, x20, [sp, 16]
	stp	x23, x24, [sp, 48]
	lsr	w20, w2, 16
	ldr	x4, [x0, x1]
	and	w24, w2, 255
	ldrb	w19, [x3, 8]
	adrp	x3, .LANCHOR8
	add	x1, x3, :lo12:.LANCHOR8
	lsr	w23, w2, 8
	ldr	x2, [x7, #:lo12:.LANCHOR7]
	and	w6, w21, 255
	lsr	w5, w21, 8
	ldrb	w1, [x1, 16]
	ldrb	w2, [x2, 7]
	cmp	w1, 1
	lsr	w1, w21, 16
	bne	.L249
	cmp	w2, 1
	bne	.L250
	sxtw	x0, w19
	mov	w2, 38
	add	x0, x0, 8
	add	x0, x4, x0, lsl 8
	str	w2, [x0, 8]
.L250:
	add	x0, x3, :lo12:.LANCHOR8
	add	x19, x4, x19, lsl 8
	ldrb	w2, [x0, 8]
	str	w2, [x19, 2056]
	str	wzr, [x19, 2052]
	str	wzr, [x19, 2052]
	str	w6, [x19, 2052]
	str	w5, [x19, 2052]
	ldrb	w0, [x0, 9]
	str	w1, [x19, 2052]
	str	w0, [x19, 2056]
	mov	w0, w22
	bl	NandcWaitFlashReady
	str	wzr, [x19, 2056]
	str	wzr, [x19, 2052]
	str	wzr, [x19, 2052]
.L254:
	str	w24, [x19, 2052]
	mov	w0, 48
	str	w23, [x19, 2052]
	mov	w1, w21
	str	w20, [x19, 2052]
	str	w0, [x19, 2056]
	mov	w0, w22
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	b	FlashSetRandomizer
.L249:
	cmp	w2, 1
	bne	.L252
	sxtw	x0, w19
	mov	w2, 38
	add	x0, x0, 8
	add	x0, x4, x0, lsl 8
	str	w2, [x0, 8]
.L252:
	add	x0, x3, :lo12:.LANCHOR8
	add	x19, x4, x19, lsl 8
	ldrb	w2, [x0, 8]
	str	w2, [x19, 2056]
	str	w6, [x19, 2052]
	str	w5, [x19, 2052]
	ldrb	w0, [x0, 9]
	str	w1, [x19, 2052]
	str	w0, [x19, 2056]
	b	.L254
	.size	FlashReadDpCmd, .-FlashReadDpCmd
	.section	.text.ftl_flash_de_init,"ax",@progbits
	.align	2
	.global	ftl_flash_de_init
	.type	ftl_flash_de_init, %function
ftl_flash_de_init:
	stp	x29, x30, [sp, -32]!
	mov	w0, 0
	add	x29, sp, 0
	str	x19, [sp, 16]
	bl	NandcWaitFlashReady
	bl	FlashSetReadRetryDefault
	adrp	x0, .LANCHOR29
	ldr	w0, [x0, #:lo12:.LANCHOR29]
	cbz	w0, .L256
	mov	w0, 0
	bl	flash_enter_slc_mode
.L257:
	adrp	x19, .LANCHOR30
	ldrb	w0, [x19, #:lo12:.LANCHOR30]
	cbz	w0, .L258
	adrp	x0, .LANCHOR25
	ldrb	w0, [x0, #:lo12:.LANCHOR25]
	tbz	x0, 0, .L258
	mov	w0, 1
	bl	FlashSetInterfaceMode
	mov	w0, 1
	bl	NandcSetMode
	strb	wzr, [x19, #:lo12:.LANCHOR30]
.L258:
	adrp	x0, .LANCHOR0
	ldr	x0, [x0, #:lo12:.LANCHOR0]
	str	wzr, [x0, 336]
	mov	w0, 0
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L256:
	mov	w0, 0
	bl	flash_exit_slc_mode
	b	.L257
	.size	ftl_flash_de_init, .-ftl_flash_de_init
	.section	.text.NandcRandmzSel,"ax",@progbits
	.align	2
	.global	NandcRandmzSel
	.type	NandcRandmzSel, %function
NandcRandmzSel:
	ubfiz	x0, x0, 4, 8
	adrp	x2, .LANCHOR0
	add	x2, x2, :lo12:.LANCHOR0
	ldr	x0, [x2, x0]
	str	w1, [x0, 336]
	ret
	.size	NandcRandmzSel, .-NandcRandmzSel
	.section	.text.NandcTimeCfg,"ax",@progbits
	.align	2
	.global	NandcTimeCfg
	.type	NandcTimeCfg, %function
NandcTimeCfg:
	cmp	w0, 35
	adrp	x1, .LANCHOR19
	bhi	.L268
	ldr	x0, [x1, #:lo12:.LANCHOR19]
	mov	w1, 4193
.L271:
	str	w1, [x0, 4]
	ret
.L268:
	cmp	w0, 99
	ldr	x0, [x1, #:lo12:.LANCHOR19]
	bls	.L270
	mov	w1, 8322
	b	.L271
.L270:
	mov	w1, 4225
	b	.L271
	.size	NandcTimeCfg, .-NandcTimeCfg
	.section	.text.FlashTimingCfg,"ax",@progbits
	.align	2
	.global	FlashTimingCfg
	.type	FlashTimingCfg, %function
FlashTimingCfg:
	adrp	x0, .LANCHOR31+21
	ldrb	w0, [x0, #:lo12:.LANCHOR31+21]
	b	NandcTimeCfg
	.size	FlashTimingCfg, .-FlashTimingCfg
	.section	.text.NandcBchSel,"ax",@progbits
	.align	2
	.global	NandcBchSel
	.type	NandcBchSel, %function
NandcBchSel:
	adrp	x1, .LANCHOR19
	and	w0, w0, 255
	cmp	w0, 16
	ldr	x2, [x1, #:lo12:.LANCHOR19]
	mov	w1, 1
	str	w1, [x2, 8]
	adrp	x1, .LANCHOR32
	str	w0, [x1, #:lo12:.LANCHOR32]
	mov	w1, 4096
	bne	.L274
.L277:
	and	w1, w1, -17
.L275:
	orr	w1, w1, 1
	str	w1, [x2, 12]
	ret
.L274:
	cmp	w0, 24
	bne	.L276
	orr	w1, w1, 16
	b	.L275
.L276:
	orr	w1, w1, 262144
	cmp	w0, 40
	orr	w1, w1, 16
	bne	.L275
	b	.L277
	.size	NandcBchSel, .-NandcBchSel
	.section	.text.FlashBchSel,"ax",@progbits
	.align	2
	.global	FlashBchSel
	.type	FlashBchSel, %function
FlashBchSel:
	adrp	x1, .LANCHOR33
	and	w0, w0, 255
	strb	w0, [x1, #:lo12:.LANCHOR33]
	b	NandcBchSel
	.size	FlashBchSel, .-FlashBchSel
	.section	.text.ftl_nandc_get_irq_status,"ax",@progbits
	.align	2
	.global	ftl_nandc_get_irq_status
	.type	ftl_nandc_get_irq_status, %function
ftl_nandc_get_irq_status:
	ldr	w0, [x0, 372]
	ret
	.size	ftl_nandc_get_irq_status, .-ftl_nandc_get_irq_status
	.section	.text.rk_nandc_flash_ready,"ax",@progbits
	.align	2
	.global	rk_nandc_flash_ready
	.type	rk_nandc_flash_ready, %function
rk_nandc_flash_ready:
	ret
	.size	rk_nandc_flash_ready, .-rk_nandc_flash_ready
	.section	.text.NandcIqrWaitFlashReady,"ax",@progbits
	.align	2
	.global	NandcIqrWaitFlashReady
	.type	NandcIqrWaitFlashReady, %function
NandcIqrWaitFlashReady:
	ret
	.size	NandcIqrWaitFlashReady, .-NandcIqrWaitFlashReady
	.section	.text.rk_nandc_flash_xfer_completed,"ax",@progbits
	.align	2
	.global	rk_nandc_flash_xfer_completed
	.type	rk_nandc_flash_xfer_completed, %function
rk_nandc_flash_xfer_completed:
	ret
	.size	rk_nandc_flash_xfer_completed, .-rk_nandc_flash_xfer_completed
	.section	.text.NandcSendDumpDataStart,"ax",@progbits
	.align	2
	.global	NandcSendDumpDataStart
	.type	NandcSendDumpDataStart, %function
NandcSendDumpDataStart:
	sub	sp, sp, #16
	ldr	w2, [x0, 16]
	mov	w1, 1066
	movk	w1, 0x2020, lsl 16
	str	w2, [sp, 8]
	ldr	w2, [sp, 8]
	and	w2, w2, -5
	str	w2, [sp, 8]
	ldr	w2, [sp, 8]
	str	w2, [x0, 16]
	str	w1, [x0, 8]
	orr	w1, w1, 4
	str	w1, [x0, 8]
	add	sp, sp, 16
	ret
	.size	NandcSendDumpDataStart, .-NandcSendDumpDataStart
	.section	.text.NandcSendDumpDataDone,"ax",@progbits
	.align	2
	.global	NandcSendDumpDataDone
	.type	NandcSendDumpDataDone, %function
NandcSendDumpDataDone:
	sub	sp, sp, #16
.L289:
	ldr	w1, [x0, 8]
	str	w1, [sp, 8]
	ldr	w1, [sp, 8]
	tbz	x1, 20, .L289
	add	sp, sp, 16
	ret
	.size	NandcSendDumpDataDone, .-NandcSendDumpDataDone
	.section	.text.NandcXferStart,"ax",@progbits
	.align	2
	.global	NandcXferStart
	.type	NandcXferStart, %function
NandcXferStart:
	stp	x29, x30, [sp, -96]!
	ubfiz	x0, x0, 4, 8
	ubfx	x3, x3, 1, 7
	add	x29, sp, 0
	stp	x23, x24, [sp, 48]
	and	w24, w1, 255
	adrp	x1, .LANCHOR0
	add	x1, x1, :lo12:.LANCHOR0
	add	x6, x1, x0
	stp	x21, x22, [sp, 32]
	stp	x19, x20, [sp, 16]
	ubfiz	w19, w24, 1, 1
	ldr	x21, [x1, x0]
	mov	w1, 16
	ldrb	w0, [x6, 8]
	orr	w19, w19, 8
	str	x25, [sp, 64]
	ldr	w22, [x21, 12]
	bfi	w22, w1, 8, 8
	and	w22, w22, -9
	bfi	w22, w0, 5, 3
	mov	w0, 1
	bfi	w19, w0, 5, 2
	adrp	x0, .LANCHOR34
	orr	w19, w19, 536870912
	orr	w19, w19, 1024
	ldr	w0, [x0, #:lo12:.LANCHOR34]
	bfi	w19, w3, 4, 1
	cmp	w0, 3
	bls	.L294
	ldr	w0, [x21, 16]
	cmp	x5, 0
	str	w0, [x29, 88]
	ccmp	x4, 0, 0, eq
	ldr	w0, [x29, 88]
	and	w0, w0, -5
	str	w0, [x29, 88]
	beq	.L295
	and	w2, w2, 255
	adrp	x20, .LANCHOR35
	cbnz	w24, .L296
.L304:
	ldr	x0, [x20, #:lo12:.LANCHOR35]
	add	w2, w2, 1
	cmp	x4, 0
	asr	w2, w2, 1
	csel	x0, x4, x0, ne
	add	x20, x20, :lo12:.LANCHOR35
	bfi	w19, w2, 22, 6
	and	x2, x0, 4294967295
	add	x2, x2, 63
	mov	x25, x4
	and	x2, x2, -64
	ldr	x1, [x20, 8]
	ubfx	x23, x19, 22, 5
	stp	x0, x1, [x20, 16]
	stp	w0, w1, [x20, 32]
	ubfiz	x1, x23, 10, 5
	add	x1, x2, x1
	and	x0, x0, 4294967232
	bl	flush_dcache_range
	ubfiz	x23, x23, 7, 5
	ldr	w0, [x20, 36]
	add	x1, x0, 63
	and	x0, x0, 4294967232
	and	x1, x1, -64
	add	x1, x1, x23
	bl	flush_dcache_range
	mov	w0, 1
	str	w0, [x20, 40]
	ldr	w0, [x20, 32]
	mov	w1, 16
	str	w0, [x21, 20]
	tst	x25, 3
	ldr	w0, [x20, 36]
	str	w0, [x21, 24]
	str	wzr, [x29, 88]
	ldr	w0, [x29, 88]
	bfi	w0, w1, 9, 5
	str	w0, [x29, 88]
	ldr	w0, [x29, 88]
	orr	w0, w0, 448
	str	w0, [x29, 88]
	bne	.L305
	ldr	w0, [x29, 88]
	mov	w1, 2
	bfi	w0, w1, 3, 3
	str	w0, [x29, 88]
.L305:
	ldr	w0, [x29, 88]
	cmp	w24, 0
	cset	w1, eq
	orr	w0, w0, 4
	str	w0, [x29, 88]
	ldr	w0, [x29, 88]
	bfi	w0, w1, 1, 1
	str	w0, [x29, 88]
	ldr	w0, [x29, 88]
	orr	w0, w0, 1
	str	w0, [x29, 88]
.L295:
	ldr	w0, [x29, 88]
	str	w0, [x21, 16]
.L294:
	str	w22, [x21, 12]
	str	w19, [x21, 8]
	orr	w19, w19, 4
	str	w19, [x21, 8]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldr	x25, [sp, 64]
	ldp	x29, x30, [sp], 96
	ret
.L296:
	adrp	x0, .LANCHOR32
	mov	w6, 64
	lsr	w11, w2, 1
	mov	x1, x5
	ldr	w0, [x0, #:lo12:.LANCHOR32]
	mov	w7, 0
	mov	w3, 0
	mov	w12, -1
	cmp	w0, 25
	mov	w0, 128
	csel	w6, w6, w0, cc
	add	x0, x20, :lo12:.LANCHOR35
	ldr	x10, [x0, 8]
.L300:
	cmp	w3, w11
	bcs	.L304
	lsr	w0, w7, 2
	lsl	w0, w0, 2
	cbz	x5, .L301
	ldrh	w13, [x1]
	add	x1, x1, 4
	ldrh	w8, [x1, -2]
	orr	x8, x13, x8, lsl 16
	str	w8, [x10, x0]
.L302:
	add	w3, w3, 1
	add	w7, w7, w6
	b	.L300
.L301:
	str	w12, [x10, x0]
	b	.L302
	.size	NandcXferStart, .-NandcXferStart
	.section	.text.NandcXferComp,"ax",@progbits
	.align	2
	.global	NandcXferComp
	.type	NandcXferComp, %function
NandcXferComp:
	ubfiz	x0, x0, 4, 8
	adrp	x1, .LANCHOR0
	add	x1, x1, :lo12:.LANCHOR0
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	ldr	x3, [x1, x0]
	adrp	x0, .LANCHOR34
	ldr	w2, [x0, #:lo12:.LANCHOR34]
	cmp	w2, 3
	bls	.L333
	ldr	w0, [x3, 16]
	tbz	x0, 2, .L333
	ldr	w0, [x3, 16]
	tbz	x0, 1, .L321
	ldr	w0, [x3, 8]
	str	w0, [x29, 16]
.L316:
	ldr	w1, [x3, 28]
	ldr	w0, [x29, 16]
	ubfx	x1, x1, 16, 5
	ubfx	x0, x0, 22, 6
	cmp	w1, w0
	bge	.L317
	cmp	w2, 5
	bls	.L316
	ldr	w0, [x3]
	str	w0, [x29, 24]
	ldr	w0, [x29, 24]
	tbz	x0, 13, .L316
	ldr	w0, [x29, 24]
	tbz	x0, 17, .L316
.L317:
	adrp	x0, .LANCHOR35+40
	str	wzr, [x0, #:lo12:.LANCHOR35+40]
.L312:
	ldp	x29, x30, [sp], 32
	ret
.L321:
	ldr	w0, [x3, 8]
	str	w0, [x29, 16]
	ldr	w0, [x29, 16]
	tbz	x0, 20, .L321
	adrp	x0, .LANCHOR36
	mov	x4, x0
	ldr	w1, [x0, #:lo12:.LANCHOR36]
	cbz	w1, .L322
	mov	x0, x3
	bl	NandcSendDumpDataStart
.L322:
	ldr	w0, [x4, #:lo12:.LANCHOR36]
	cbz	w0, .L317
	mov	x0, x3
	bl	NandcSendDumpDataDone
	b	.L317
.L333:
	ldr	w0, [x3, 8]
	str	w0, [x29, 16]
	ldr	w0, [x29, 16]
	tbz	x0, 20, .L333
	b	.L312
	.size	NandcXferComp, .-NandcXferComp
	.section	.text.Ftl_log2,"ax",@progbits
	.align	2
	.global	Ftl_log2
	.type	Ftl_log2, %function
Ftl_log2:
	mov	w2, 1
	mov	w1, 0
.L342:
	cmp	w2, w0
	bls	.L343
	sub	w0, w1, #1
	ret
.L343:
	add	w1, w1, 1
	lsl	w2, w2, 1
	and	w1, w1, 65535
	b	.L342
	.size	Ftl_log2, .-Ftl_log2
	.section	.text.FtlPrintInfo,"ax",@progbits
	.align	2
	.global	FtlPrintInfo
	.type	FtlPrintInfo, %function
FtlPrintInfo:
	ret
	.size	FtlPrintInfo, .-FtlPrintInfo
	.section	.text.FtlSysBlkNumInit,"ax",@progbits
	.align	2
	.global	FtlSysBlkNumInit
	.type	FtlSysBlkNumInit, %function
FtlSysBlkNumInit:
	and	w0, w0, 65535
	mov	w1, 24
	cmp	w0, 24
	adrp	x2, .LANCHOR39
	csel	w0, w0, w1, cs
	adrp	x1, .LANCHOR37
	and	w0, w0, 65535
	str	w0, [x1, #:lo12:.LANCHOR37]
	adrp	x1, .LANCHOR38
	ldrh	w1, [x1, #:lo12:.LANCHOR38]
	mul	w1, w1, w0
	str	w1, [x2, #:lo12:.LANCHOR39]
	adrp	x2, .LANCHOR41
	ldrh	w2, [x2, #:lo12:.LANCHOR41]
	sub	w0, w2, w0
	adrp	x2, .LANCHOR40
	strh	w0, [x2, #:lo12:.LANCHOR40]
	adrp	x0, .LANCHOR43
	ldr	w0, [x0, #:lo12:.LANCHOR43]
	sub	w1, w0, w1
	adrp	x0, .LANCHOR42
	str	w1, [x0, #:lo12:.LANCHOR42]
	mov	w0, 0
	ret
	.size	FtlSysBlkNumInit, .-FtlSysBlkNumInit
	.section	.text.FtlConstantsInit,"ax",@progbits
	.align	2
	.global	FtlConstantsInit
	.type	FtlConstantsInit, %function
FtlConstantsInit:
	stp	x29, x30, [sp, -32]!
	mov	x5, x0
	adrp	x1, .LANCHOR46
	adrp	x4, .LANCHOR45
	add	x29, sp, 0
	ldrh	w11, [x0, 8]
	adrp	x0, .LANCHOR44
	adrp	x6, .LANCHOR41
	ldrh	w2, [x5, 10]
	strh	w11, [x0, #:lo12:.LANCHOR44]
	mov	x3, 0
	ldrh	w0, [x5, 12]
	ldrh	w8, [x5, 14]
	strh	w0, [x1, #:lo12:.LANCHOR46]
	adrp	x1, .LANCHOR47
	add	x7, x1, :lo12:.LANCHOR47
	strh	w2, [x4, #:lo12:.LANCHOR45]
	strh	w8, [x6, #:lo12:.LANCHOR41]
	str	x19, [sp, 16]
.L347:
	strb	w3, [x3, x7]
	add	x3, x3, 1
	cmp	x3, 32
	bne	.L347
	ldrh	w7, [x5, 20]
	ldrb	w3, [x5, 15]
	cmp	w7, w3
	bcs	.L348
	and	w13, w0, 255
	mul	w15, w0, w2
	ubfiz	w14, w13, 1, 7
	add	x1, x1, :lo12:.LANCHOR47
	mov	w7, 0
.L349:
	cmp	w7, w0
	bcs	.L351
	and	w3, w7, 255
	mov	w10, w7
	mov	w12, 0
	b	.L352
.L350:
	add	w16, w15, w10
	strb	w3, [x1, w10, uxtw]
	add	w17, w13, w3
	add	w3, w14, w3
	add	w12, w12, 1
	and	w3, w3, 255
	add	w10, w10, w0
	strb	w17, [x1, x16]
.L352:
	cmp	w12, w2
	bcc	.L350
	add	w7, w7, 1
	b	.L349
.L351:
	ubfiz	w2, w2, 1, 15
	lsr	w8, w8, 1
	strh	w2, [x4, #:lo12:.LANCHOR45]
	strh	w8, [x6, #:lo12:.LANCHOR41]
.L348:
	adrp	x1, .LANCHOR48
	adrp	x13, .LANCHOR49
	mov	w2, 5
	cmp	w11, 1
	strh	w2, [x1, #:lo12:.LANCHOR48]
	strh	wzr, [x13, #:lo12:.LANCHOR49]
	bne	.L353
	strh	w11, [x1, #:lo12:.LANCHOR48]
.L353:
	adrp	x8, .LANCHOR50
	mov	w1, 4352
	strh	w1, [x8, #:lo12:.LANCHOR50]
	adrp	x1, .LANCHOR2
	ldrb	w11, [x1, #:lo12:.LANCHOR2]
	cbz	w11, .L354
	mov	w1, 384
	strh	w1, [x8, #:lo12:.LANCHOR50]
.L354:
	ldrh	w4, [x4, #:lo12:.LANCHOR45]
	adrp	x1, .LANCHOR38
	ldrh	w3, [x6, #:lo12:.LANCHOR41]
	adrp	x7, .LANCHOR52
	ldrh	w19, [x5, 16]
	adrp	x15, .LANCHOR55
	ldrh	w10, [x5, 20]
	mul	w4, w0, w4
	ldrh	w14, [x5, 18]
	mul	w0, w0, w3
	strh	w19, [x7, #:lo12:.LANCHOR52]
	and	w4, w4, 65535
	strh	w4, [x1, #:lo12:.LANCHOR38]
	adrp	x1, .LANCHOR51
	strh	w10, [x15, #:lo12:.LANCHOR55]
	strh	w0, [x1, #:lo12:.LANCHOR51]
	mul	w1, w4, w19
	adrp	x0, .LANCHOR53
	strh	w14, [x0, #:lo12:.LANCHOR53]
	adrp	x0, .LANCHOR54
	strh	w1, [x0, #:lo12:.LANCHOR54]
	mov	w0, w10
	bl	Ftl_log2
	and	w12, w0, 65535
	adrp	x6, .LANCHOR56
	ubfiz	w2, w10, 9, 7
	ldrh	w1, [x5, 26]
	cmp	w3, 1024
	strh	w0, [x6, #:lo12:.LANCHOR56]
	adrp	x0, .LANCHOR57
	strh	w2, [x0, #:lo12:.LANCHOR57]
	adrp	x0, .LANCHOR58
	ubfx	w2, w2, 8, 8
	strh	w2, [x0, #:lo12:.LANCHOR58]
	adrp	x0, .LANCHOR59
	strh	w1, [x0, #:lo12:.LANCHOR59]
	adrp	x0, .LANCHOR43
	mul	w1, w4, w3
	str	w1, [x0, #:lo12:.LANCHOR43]
	bls	.L355
	and	w0, w3, 255
	strh	w0, [x13, #:lo12:.LANCHOR49]
.L355:
	ldrh	w0, [x13, #:lo12:.LANCHOR49]
	adrp	x1, .LANCHOR60
	sub	w0, w3, w0
	mul	w0, w0, w4
	mul	w0, w0, w10
	mul	w0, w0, w19
	asr	w0, w0, 11
	str	w0, [x1, #:lo12:.LANCHOR60]
	ldrh	w0, [x8, #:lo12:.LANCHOR50]
	mul	w1, w14, w10
	adrp	x10, .LANCHOR61
	lsl	w0, w0, 3
	sdiv	w0, w0, w1
	and	w0, w0, 65535
	cmp	w0, 4
	bls	.L356
.L372:
	strh	w0, [x10, #:lo12:.LANCHOR61]
	cbz	w11, .L358
	mov	w0, 640
	strh	w0, [x8, #:lo12:.LANCHOR50]
.L358:
	ldrh	w0, [x8, #:lo12:.LANCHOR50]
	adrp	x1, .LANCHOR62
	lsl	w3, w3, 6
	cmp	w4, 1
	adrp	x8, .LANCHOR37
	asr	w0, w0, w12
	add	w0, w0, 2
	strh	w0, [x1, #:lo12:.LANCHOR62]
	add	w0, w12, 9
	adrp	x1, .LANCHOR64
	asr	w3, w3, w0
	adrp	x0, .LANCHOR63
	strh	w3, [x0, #:lo12:.LANCHOR63]
	and	w3, w3, 65535
	mul	w0, w4, w3
	add	w3, w3, 8
	str	w0, [x1, #:lo12:.LANCHOR64]
	ldrh	w0, [x10, #:lo12:.LANCHOR61]
	udiv	w0, w0, w4
	mov	x4, x1
	add	w3, w0, w3
	beq	.L359
.L373:
	str	w3, [x8, #:lo12:.LANCHOR37]
	ldrh	w0, [x8, #:lo12:.LANCHOR37]
	bl	FtlSysBlkNumInit
	ldr	w1, [x8, #:lo12:.LANCHOR37]
	adrp	x0, .LANCHOR65
	mov	w2, 24
	str	w1, [x0, #:lo12:.LANCHOR65]
	adrp	x0, .LANCHOR42
	ldrh	w1, [x7, #:lo12:.LANCHOR52]
	ldr	w0, [x0, #:lo12:.LANCHOR42]
	lsl	w0, w0, 2
	mul	w0, w0, w1
	ldrh	w1, [x6, #:lo12:.LANCHOR56]
	adrp	x6, .LANCHOR16
	add	w1, w1, 9
	ldrb	w6, [x6, #:lo12:.LANCHOR16]
	lsr	w0, w0, w1
	adrp	x1, .LANCHOR66
	add	w0, w0, 2
	and	w0, w0, 65535
	strh	w0, [x1, #:lo12:.LANCHOR66]
	adrp	x1, .LANCHOR67
	strh	w2, [x1, #:lo12:.LANCHOR67]
	adrp	x1, .LANCHOR68
	ldrh	w2, [x10, #:lo12:.LANCHOR61]
	str	wzr, [x1, #:lo12:.LANCHOR68]
	add	w1, w2, 3
	strh	w1, [x10, #:lo12:.LANCHOR61]
	ldr	w1, [x4, #:lo12:.LANCHOR64]
	add	w3, w1, 3
	str	w3, [x4, #:lo12:.LANCHOR64]
	cbz	w6, .L361
	add	w1, w1, 5
	add	w2, w2, 4
	strh	w2, [x10, #:lo12:.LANCHOR61]
.L374:
	str	w1, [x4, #:lo12:.LANCHOR64]
.L362:
	adrp	x1, .LANCHOR40
	adrp	x3, .LANCHOR69
	ldrh	w1, [x1, #:lo12:.LANCHOR40]
	strh	wzr, [x3, #:lo12:.LANCHOR69]
	lsl	w2, w1, 1
	lsr	w1, w1, 3
	add	w2, w2, 48
	add	w1, w1, 4
	add	w0, w2, w0, lsl 2
	add	w0, w0, w1
	ldrh	w1, [x15, #:lo12:.LANCHOR55]
	cmp	w0, w1, lsl 9
	bcs	.L363
	mov	w0, 1
	strh	w0, [x3, #:lo12:.LANCHOR69]
.L363:
	mov	w0, 0
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L356:
	mov	w0, 4
	b	.L372
.L359:
	add	w3, w3, 4
	b	.L373
.L361:
	cmp	w3, 7
	bhi	.L362
	mov	w1, 8
	b	.L374
	.size	FtlConstantsInit, .-FtlConstantsInit
	.section	.text.IsBlkInVendorPart,"ax",@progbits
	.align	2
	.global	IsBlkInVendorPart
	.type	IsBlkInVendorPart, %function
IsBlkInVendorPart:
	adrp	x1, .LANCHOR70
	and	w0, w0, 65535
	ldrh	w1, [x1, #:lo12:.LANCHOR70]
	cbz	w1, .L379
	adrp	x1, .LANCHOR61
	ldrh	w2, [x1, #:lo12:.LANCHOR61]
	adrp	x1, .LANCHOR71
	ldr	x3, [x1, #:lo12:.LANCHOR71]
	mov	x1, 0
.L377:
	cmp	w2, w1, uxth
	bhi	.L378
.L379:
	mov	w0, 0
	ret
.L378:
	add	x1, x1, 1
	add	x4, x3, x1, lsl 1
	ldrh	w4, [x4, -2]
	cmp	w4, w0
	bne	.L377
	mov	w0, 1
	ret
	.size	IsBlkInVendorPart, .-IsBlkInVendorPart
	.section	.text.FtlCacheMetchLpa,"ax",@progbits
	.align	2
	.global	FtlCacheMetchLpa
	.type	FtlCacheMetchLpa, %function
FtlCacheMetchLpa:
	adrp	x2, .LANCHOR72
	ldr	w4, [x2, #:lo12:.LANCHOR72]
	cbz	w4, .L386
	adrp	x2, .LANCHOR73
	mov	x5, 24
	mov	w6, 56
	ldr	x2, [x2, #:lo12:.LANCHOR73]
	nop // between mem op and mult-accumulate
	umaddl	x4, w4, w6, x5
	add	x3, x2, 24
	add	x2, x2, x4
.L383:
	cmp	x3, x2
	bne	.L385
.L386:
	mov	w0, 0
	ret
.L385:
	ldr	w4, [x3]
	cmp	w4, w0
	bcc	.L384
	cmp	w4, w1
	bls	.L387
.L384:
	add	x3, x3, 56
	b	.L383
.L387:
	mov	w0, 1
	ret
	.size	FtlCacheMetchLpa, .-FtlCacheMetchLpa
	.section	.text.FtlGetCap,"ax",@progbits
	.align	2
	.global	FtlGetCap
	.type	FtlGetCap, %function
FtlGetCap:
	adrp	x0, .LANCHOR68
	ldr	w0, [x0, #:lo12:.LANCHOR68]
	ret
	.size	FtlGetCap, .-FtlGetCap
	.section	.text.FtlGetCapacity,"ax",@progbits
	.align	2
	.global	FtlGetCapacity
	.type	FtlGetCapacity, %function
FtlGetCapacity:
	adrp	x0, .LANCHOR68
	ldr	w0, [x0, #:lo12:.LANCHOR68]
	ret
	.size	FtlGetCapacity, .-FtlGetCapacity
	.section	.text.ftl_get_density,"ax",@progbits
	.align	2
	.global	ftl_get_density
	.type	ftl_get_density, %function
ftl_get_density:
	adrp	x0, .LANCHOR68
	ldr	w0, [x0, #:lo12:.LANCHOR68]
	ret
	.size	ftl_get_density, .-ftl_get_density
	.section	.text.FtlGetLpn,"ax",@progbits
	.align	2
	.global	FtlGetLpn
	.type	FtlGetLpn, %function
FtlGetLpn:
	adrp	x0, .LANCHOR74
	ldr	w0, [x0, #:lo12:.LANCHOR74]
	ret
	.size	FtlGetLpn, .-FtlGetLpn
	.section	.text.FtlGetCurEraseBlock,"ax",@progbits
	.align	2
	.global	FtlGetCurEraseBlock
	.type	FtlGetCurEraseBlock, %function
FtlGetCurEraseBlock:
	adrp	x0, .LANCHOR38
	ldrh	w1, [x0, #:lo12:.LANCHOR38]
	adrp	x0, .LANCHOR75
	ldr	w0, [x0, #:lo12:.LANCHOR75]
	mul	w0, w1, w0
	ret
	.size	FtlGetCurEraseBlock, .-FtlGetCurEraseBlock
	.section	.text.FtlGetAllBlockNum,"ax",@progbits
	.align	2
	.global	FtlGetAllBlockNum
	.type	FtlGetAllBlockNum, %function
FtlGetAllBlockNum:
	adrp	x0, .LANCHOR41
	ldrh	w1, [x0, #:lo12:.LANCHOR41]
	adrp	x0, .LANCHOR38
	ldrh	w0, [x0, #:lo12:.LANCHOR38]
	mul	w0, w1, w0
	ret
	.size	FtlGetAllBlockNum, .-FtlGetAllBlockNum
	.section	.text.FtlBbmMapBadBlock,"ax",@progbits
	.align	2
	.global	FtlBbmMapBadBlock
	.type	FtlBbmMapBadBlock, %function
FtlBbmMapBadBlock:
	stp	x29, x30, [sp, -32]!
	and	w1, w0, 65535
	adrp	x0, .LANCHOR51
	mov	w4, 1
	add	x29, sp, 0
	ldrh	w0, [x0, #:lo12:.LANCHOR51]
	str	x19, [sp, 16]
	adrp	x19, .LANCHOR76
	add	x19, x19, :lo12:.LANCHOR76
	udiv	w3, w1, w0
	and	w2, w3, 65535
	msub	w3, w3, w0, w1
	add	x0, x19, x2, uxth 3
	and	w3, w3, 65535
	and	w6, w3, 31
	ldr	x0, [x0, 32]
	ubfx	x5, x3, 5, 11
	lsl	x5, x5, 2
	lsl	w4, w4, w6
	ldr	w6, [x0, x5]
	orr	w4, w4, w6
	str	w4, [x0, x5]
	adrp	x0, .LC2
	add	x0, x0, :lo12:.LC2
	bl	printf
	ldrh	w0, [x19, 6]
	add	w0, w0, 1
	strh	w0, [x19, 6]
	mov	w0, 0
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	FtlBbmMapBadBlock, .-FtlBbmMapBadBlock
	.section	.text.FtlBbmIsBadBlock,"ax",@progbits
	.align	2
	.global	FtlBbmIsBadBlock
	.type	FtlBbmIsBadBlock, %function
FtlBbmIsBadBlock:
	adrp	x1, .LANCHOR51
	and	w0, w0, 65535
	ldrh	w1, [x1, #:lo12:.LANCHOR51]
	udiv	w2, w0, w1
	msub	w0, w2, w1, w0
	adrp	x1, .LANCHOR76
	add	x1, x1, :lo12:.LANCHOR76
	add	x2, x1, x2, uxth 3
	and	w0, w0, 65535
	ubfx	x3, x0, 5, 11
	and	w0, w0, 31
	ldr	x1, [x2, 32]
	ldr	w1, [x1, x3, lsl 2]
	lsr	w0, w1, w0
	and	w0, w0, 1
	ret
	.size	FtlBbmIsBadBlock, .-FtlBbmIsBadBlock
	.section	.text.FtlBbtInfoPrint,"ax",@progbits
	.align	2
	.global	FtlBbtInfoPrint
	.type	FtlBbtInfoPrint, %function
FtlBbtInfoPrint:
	ret
	.size	FtlBbtInfoPrint, .-FtlBbtInfoPrint
	.section	.text.V2P_block,"ax",@progbits
	.align	2
	.global	V2P_block
	.type	V2P_block, %function
V2P_block:
	adrp	x2, .LANCHOR46
	and	w0, w0, 65535
	adrp	x4, .LANCHOR51
	and	w1, w1, 65535
	ldrh	w2, [x2, #:lo12:.LANCHOR46]
	ldrh	w4, [x4, #:lo12:.LANCHOR51]
	udiv	w3, w0, w2
	msub	w0, w3, w2, w0
	madd	w2, w2, w1, w0
	madd	w0, w3, w4, w2
	ret
	.size	V2P_block, .-V2P_block
	.section	.text.P2V_plane,"ax",@progbits
	.align	2
	.global	P2V_plane
	.type	P2V_plane, %function
P2V_plane:
	and	w3, w0, 65535
	adrp	x0, .LANCHOR46
	ldrh	w1, [x0, #:lo12:.LANCHOR46]
	adrp	x0, .LANCHOR51
	ldrh	w2, [x0, #:lo12:.LANCHOR51]
	udiv	w0, w3, w1
	udiv	w2, w3, w2
	msub	w0, w0, w1, w3
	madd	w0, w1, w2, w0
	ret
	.size	P2V_plane, .-P2V_plane
	.section	.text.P2V_block_in_plane,"ax",@progbits
	.align	2
	.global	P2V_block_in_plane
	.type	P2V_block_in_plane, %function
P2V_block_in_plane:
	and	w2, w0, 65535
	adrp	x0, .LANCHOR51
	ldrh	w1, [x0, #:lo12:.LANCHOR51]
	udiv	w0, w2, w1
	msub	w0, w0, w1, w2
	adrp	x1, .LANCHOR46
	ldrh	w1, [x1, #:lo12:.LANCHOR46]
	and	w0, w0, 65535
	udiv	w0, w0, w1
	ret
	.size	P2V_block_in_plane, .-P2V_block_in_plane
	.section	.text.ftl_cmp_data_ver,"ax",@progbits
	.align	2
	.global	ftl_cmp_data_ver
	.type	ftl_cmp_data_ver, %function
ftl_cmp_data_ver:
	cmp	w0, w1
	mov	w2, -2147483648
	bls	.L402
	sub	w1, w0, w1
	cmp	w1, w2
	cset	w0, ls
	ret
.L402:
	sub	w1, w1, w0
	cmp	w1, w2
	cset	w0, hi
	ret
	.size	ftl_cmp_data_ver, .-ftl_cmp_data_ver
	.section	.text.FtlFreeSysBlkQueueEmpty,"ax",@progbits
	.align	2
	.global	FtlFreeSysBlkQueueEmpty
	.type	FtlFreeSysBlkQueueEmpty, %function
FtlFreeSysBlkQueueEmpty:
	adrp	x0, .LANCHOR77+6
	ldrh	w0, [x0, #:lo12:.LANCHOR77+6]
	cmp	w0, 0
	cset	w0, eq
	ret
	.size	FtlFreeSysBlkQueueEmpty, .-FtlFreeSysBlkQueueEmpty
	.section	.text.FtlFreeSysBlkQueueFull,"ax",@progbits
	.align	2
	.global	FtlFreeSysBlkQueueFull
	.type	FtlFreeSysBlkQueueFull, %function
FtlFreeSysBlkQueueFull:
	adrp	x0, .LANCHOR77+6
	ldrh	w0, [x0, #:lo12:.LANCHOR77+6]
	cmp	w0, 1024
	cset	w0, eq
	ret
	.size	FtlFreeSysBlkQueueFull, .-FtlFreeSysBlkQueueFull
	.section	.text.FtlFreeSysBlkQueueIn,"ax",@progbits
	.align	2
	.global	FtlFreeSysBlkQueueIn
	.type	FtlFreeSysBlkQueueIn, %function
FtlFreeSysBlkQueueIn:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	and	w20, w0, 65535
	str	x21, [sp, 32]
	sub	w2, w20, #1
	mov	w0, 65533
	cmp	w0, w2, uxth
	bcc	.L406
	adrp	x0, .LANCHOR77
	add	x2, x0, :lo12:.LANCHOR77
	mov	x19, x0
	ldrh	w2, [x2, 6]
	cmp	w2, 1024
	beq	.L406
	and	w1, w1, 65535
	cbz	w1, .L408
	adrp	x0, .LANCHOR78
	ldr	w0, [x0, #:lo12:.LANCHOR78]
	cbnz	w0, .L408
	mov	w0, w20
	bl	P2V_block_in_plane
	and	w21, w0, 65535
	adrp	x0, .LANCHOR79
	lsl	w1, w20, 10
	mov	w2, 1
	ldr	x0, [x0, #:lo12:.LANCHOR79]
	str	w1, [x0, 4]
	mov	w1, w2
	bl	FlashEraseBlocks
	adrp	x1, .LANCHOR80
	ubfiz	x0, x21, 1, 16
	ldr	x2, [x1, #:lo12:.LANCHOR80]
	ldrh	w1, [x2, x0]
	add	w1, w1, 1
	strh	w1, [x2, x0]
	adrp	x1, .LANCHOR81
	ldr	w0, [x1, #:lo12:.LANCHOR81]
	add	w0, w0, 1
	str	w0, [x1, #:lo12:.LANCHOR81]
.L408:
	add	x0, x19, :lo12:.LANCHOR77
	ldrh	w1, [x0, 6]
	add	w1, w1, 1
	strh	w1, [x0, 6]
	ldrh	w1, [x0, 4]
	add	x2, x0, x1, sxtw 1
	add	w1, w1, 1
	and	w1, w1, 1023
	strh	w1, [x0, 4]
	strh	w20, [x2, 8]
.L406:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	FtlFreeSysBlkQueueIn, .-FtlFreeSysBlkQueueIn
	.section	.text.FtlFreeSysBLkSort,"ax",@progbits
	.align	2
	.global	FtlFreeSysBLkSort
	.type	FtlFreeSysBLkSort, %function
FtlFreeSysBLkSort:
	adrp	x0, .LANCHOR77
	add	x1, x0, :lo12:.LANCHOR77
	ldrh	w2, [x1, 6]
	cbz	w2, .L416
	adrp	x2, .LANCHOR82+28
	ldrh	w3, [x1, 2]
	mov	w6, 0
	mov	w4, 0
	ldrh	w5, [x2, #:lo12:.LANCHOR82+28]
	ldrh	w2, [x1, 4]
	and	w5, w5, 31
.L418:
	cmp	w5, w4
	bgt	.L419
	cbz	w6, .L416
	add	x0, x0, :lo12:.LANCHOR77
	strh	w3, [x0, 2]
	strh	w2, [x0, 4]
.L416:
	ret
.L419:
	add	x6, x1, x3, sxtw 1
	add	w4, w4, 1
	add	w3, w3, 1
	and	w4, w4, 65535
	and	w3, w3, 1023
	ldrh	w7, [x6, 8]
	add	x6, x1, x2, sxtw 1
	strh	w7, [x6, 8]
	mov	w6, 1
	add	w2, w2, w6
	and	w2, w2, 1023
	b	.L418
	.size	FtlFreeSysBLkSort, .-FtlFreeSysBLkSort
	.section	.text.FtlFreeSysBlkQueueOut,"ax",@progbits
	.align	2
	.global	FtlFreeSysBlkQueueOut
	.type	FtlFreeSysBlkQueueOut, %function
FtlFreeSysBlkQueueOut:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	adrp	x19, .LANCHOR77
	add	x19, x19, :lo12:.LANCHOR77
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	adrp	x22, .LANCHOR78
	mov	x23, x19
	add	x22, x22, :lo12:.LANCHOR78
.L426:
	ldrh	w1, [x19, 6]
	cbz	w1, .L427
	ldrh	w0, [x19, 2]
	sub	w1, w1, #1
	strh	w1, [x19, 6]
	add	x2, x19, x0, sxtw 1
	add	w0, w0, 1
	and	w0, w0, 1023
	strh	w0, [x19, 2]
	ldr	w0, [x22]
	ldrh	w20, [x2, 8]
	cbnz	w0, .L428
	mov	w0, w20
	bl	P2V_block_in_plane
	adrp	x1, .LANCHOR79
	and	w21, w0, 65535
	lsl	w2, w20, 10
	mov	x24, x1
	ldr	x0, [x1, #:lo12:.LANCHOR79]
	str	w2, [x0, 4]
	adrp	x2, .LANCHOR16
	ldrb	w2, [x2, #:lo12:.LANCHOR16]
	cbz	w2, .L429
	mov	w2, 1
	mov	w1, 0
	bl	FlashEraseBlocks
.L429:
	ldr	x0, [x24, #:lo12:.LANCHOR79]
	mov	w2, 1
	mov	w1, w2
	bl	FlashEraseBlocks
	adrp	x1, .LANCHOR80
	ubfiz	x0, x21, 1, 16
	ldr	x2, [x1, #:lo12:.LANCHOR80]
	ldrh	w1, [x2, x0]
	add	w1, w1, 1
	strh	w1, [x2, x0]
	adrp	x1, .LANCHOR81
	ldr	w0, [x1, #:lo12:.LANCHOR81]
	add	w0, w0, 1
	str	w0, [x1, #:lo12:.LANCHOR81]
.L428:
	sub	w0, w20, #1
	mov	w1, 65533
	cmp	w1, w0, uxth
	bcs	.L431
	ldrh	w2, [x23, 6]
	mov	w1, w20
	adrp	x0, .LC4
	add	x0, x0, :lo12:.LC4
	bl	printf
	b	.L426
.L427:
	adrp	x0, .LC3
	mov	w1, 0
	add	x0, x0, :lo12:.LC3
	bl	printf
.L430:
	b	.L430
.L431:
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.size	FtlFreeSysBlkQueueOut, .-FtlFreeSysBlkQueueOut
	.section	.text.test_node_in_list,"ax",@progbits
	.align	2
	.global	test_node_in_list
	.type	test_node_in_list, %function
test_node_in_list:
	ldr	x2, [x0]
	adrp	x0, .LANCHOR83
	mov	x4, -6148914691236517206
	and	w1, w1, 65535
	ldr	x3, [x0, #:lo12:.LANCHOR83]
	movk	x4, 0xaaab, lsl 0
	mov	w5, 65535
	sub	x0, x2, x3
	asr	x0, x0, 1
	mul	x0, x0, x4
	mov	w4, 6
	and	w0, w0, 65535
.L438:
	cmp	w0, w1
	beq	.L439
	ldrh	w0, [x2]
	cmp	w0, w5
	beq	.L440
	umaddl	x2, w0, w4, x3
	b	.L438
.L439:
	mov	w0, 1
	ret
.L440:
	mov	w0, 0
	ret
	.size	test_node_in_list, .-test_node_in_list
	.section	.text.insert_data_list,"ax",@progbits
	.align	2
	.global	insert_data_list
	.type	insert_data_list, %function
insert_data_list:
	adrp	x1, .LANCHOR40
	and	w0, w0, 65535
	ldrh	w14, [x1, #:lo12:.LANCHOR40]
	cmp	w14, w0
	bls	.L457
	adrp	x1, .LANCHOR83
	mov	w3, 6
	ldr	x6, [x1, #:lo12:.LANCHOR83]
	umull	x13, w0, w3
	mov	w1, -1
	add	x5, x6, x13
	strh	w1, [x5, 2]
	strh	w1, [x6, x13]
	adrp	x1, .LANCHOR84
	mov	x15, x1
	ldr	x12, [x1, #:lo12:.LANCHOR84]
	cbnz	x12, .L444
	str	x5, [x1, #:lo12:.LANCHOR84]
.L457:
	mov	w0, 0
	ret
.L444:
	stp	x29, x30, [sp, -32]!
	adrp	x1, .LANCHOR85
	ubfiz	x2, x0, 1, 16
	mov	x4, -6148914691236517206
	add	x29, sp, 0
	ldr	x16, [x1, #:lo12:.LANCHOR85]
	movk	x4, 0xaaab, lsl 0
	ldrh	w1, [x5, 4]
	mov	w8, -1
	mov	w11, w8
	stp	x19, x20, [sp, 16]
	cmp	w1, 0
	mov	w20, 65535
	ldrh	w7, [x16, x2]
	mul	w7, w7, w1
	sub	x1, x12, x6
	asr	x1, x1, 1
	csel	w7, w7, w8, ne
	mov	w8, w3
	mul	x1, x1, x4
	adrp	x4, .LANCHOR80
	ldr	x17, [x4, #:lo12:.LANCHOR80]
	and	w1, w1, 65535
	mov	x4, x12
	add	x10, x17, x2
	mov	w2, 0
.L452:
	add	w2, w2, 1
	and	w2, w2, 65535
	cmp	w14, w2
	bcc	.L443
	cmp	w1, w0
	beq	.L443
	ubfiz	x30, x1, 1, 16
	ldrh	w19, [x4, 4]
	cmp	w19, 0
	ldrh	w3, [x16, x30]
	mul	w3, w3, w19
	csel	w3, w3, w11, ne
	cmp	w7, w3
	bne	.L448
	ldrh	w19, [x17, x30]
	ldrh	w3, [x10]
	cmp	w19, w3
	bcc	.L450
.L449:
	strh	w1, [x6, x13]
	cmp	x4, x12
	ldrh	w1, [x4, 2]
	strh	w1, [x5, 2]
	bne	.L453
	strh	w0, [x4, 2]
	str	x5, [x15, #:lo12:.LANCHOR84]
	b	.L443
.L448:
	bcc	.L449
.L450:
	ldrh	w3, [x4]
	cmp	w3, w20
	bne	.L451
	strh	w1, [x5, 2]
	strh	w0, [x4]
	adrp	x0, .LANCHOR86
	str	x5, [x0, #:lo12:.LANCHOR86]
.L443:
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L451:
	umaddl	x4, w3, w8, x6
	mov	w1, w3
	b	.L452
.L453:
	ldrh	w1, [x4, 2]
	mov	w2, 6
	umull	x1, w1, w2
	strh	w0, [x6, x1]
	strh	w0, [x4, 2]
	b	.L443
	.size	insert_data_list, .-insert_data_list
	.section	.text.INSERT_DATA_LIST,"ax",@progbits
	.align	2
	.global	INSERT_DATA_LIST
	.type	INSERT_DATA_LIST, %function
INSERT_DATA_LIST:
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
	bl	insert_data_list
	adrp	x1, .LANCHOR87
	ldrh	w0, [x1, #:lo12:.LANCHOR87]
	add	w0, w0, 1
	and	w0, w0, 65535
	strh	w0, [x1, #:lo12:.LANCHOR87]
	adrp	x1, .LANCHOR40
	ldrh	w1, [x1, #:lo12:.LANCHOR40]
	cmp	w1, w0
	bcs	.L459
	mov	w2, 245
	adrp	x1, .LANCHOR88
	adrp	x0, .LC5
	add	x1, x1, :lo12:.LANCHOR88
	add	x0, x0, :lo12:.LC5
	bl	printf
	ldp	x29, x30, [sp], 16
	adrp	x1, .LC6
	adrp	x0, .LC7
	add	x1, x1, :lo12:.LC6
	add	x0, x0, :lo12:.LC7
	b	printf
.L459:
	ldp	x29, x30, [sp], 16
	ret
	.size	INSERT_DATA_LIST, .-INSERT_DATA_LIST
	.section	.text.insert_free_list,"ax",@progbits
	.align	2
	.global	insert_free_list
	.type	insert_free_list, %function
insert_free_list:
	and	w0, w0, 65535
	mov	w7, 65535
	cmp	w0, w7
	beq	.L463
	adrp	x1, .LANCHOR83
	mov	w6, 6
	ldr	x3, [x1, #:lo12:.LANCHOR83]
	umull	x8, w0, w6
	mov	w1, -1
	add	x4, x3, x8
	strh	w1, [x4, 2]
	strh	w1, [x3, x8]
	adrp	x1, .LANCHOR89
	mov	x12, x1
	ldr	x5, [x1, #:lo12:.LANCHOR89]
	cbnz	x5, .L464
	str	x4, [x1, #:lo12:.LANCHOR89]
.L463:
	mov	w0, 0
	ret
.L464:
	adrp	x1, .LANCHOR80
	mov	x2, -6148914691236517206
	movk	x2, 0xaaab, lsl 0
	ldr	x11, [x1, #:lo12:.LANCHOR80]
	ubfiz	x1, x0, 1, 16
	ldrh	w13, [x11, x1]
	sub	x1, x5, x3
	asr	x1, x1, 1
	mul	x1, x1, x2
	mov	x2, x5
	and	w1, w1, 65535
.L467:
	ubfiz	x10, x1, 1, 16
	ldrh	w10, [x11, x10]
	cmp	w10, w13
	bcs	.L465
	ldrh	w10, [x2]
	cmp	w10, w7
	bne	.L466
	strh	w1, [x4, 2]
	strh	w0, [x2]
	b	.L463
.L466:
	umaddl	x2, w10, w6, x3
	mov	w1, w10
	b	.L467
.L465:
	ldrh	w6, [x2, 2]
	cmp	x2, x5
	strh	w6, [x4, 2]
	strh	w1, [x3, x8]
	bne	.L468
	strh	w0, [x2, 2]
	str	x4, [x12, #:lo12:.LANCHOR89]
	b	.L463
.L468:
	ldrh	w1, [x2, 2]
	mov	w4, 6
	umull	x1, w1, w4
	strh	w0, [x3, x1]
	strh	w0, [x2, 2]
	b	.L463
	.size	insert_free_list, .-insert_free_list
	.section	.text.INSERT_FREE_LIST,"ax",@progbits
	.align	2
	.global	INSERT_FREE_LIST
	.type	INSERT_FREE_LIST, %function
INSERT_FREE_LIST:
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
	bl	insert_free_list
	adrp	x1, .LANCHOR90
	ldrh	w0, [x1, #:lo12:.LANCHOR90]
	add	w0, w0, 1
	and	w0, w0, 65535
	strh	w0, [x1, #:lo12:.LANCHOR90]
	adrp	x1, .LANCHOR40
	ldrh	w1, [x1, #:lo12:.LANCHOR40]
	cmp	w1, w0
	bcs	.L469
	mov	w2, 238
	adrp	x1, .LANCHOR91
	adrp	x0, .LC5
	add	x1, x1, :lo12:.LANCHOR91
	add	x0, x0, :lo12:.LC5
	bl	printf
	ldp	x29, x30, [sp], 16
	adrp	x1, .LC6
	adrp	x0, .LC7
	add	x1, x1, :lo12:.LC6
	add	x0, x0, :lo12:.LC7
	b	printf
.L469:
	ldp	x29, x30, [sp], 16
	ret
	.size	INSERT_FREE_LIST, .-INSERT_FREE_LIST
	.section	.text.List_remove_node,"ax",@progbits
	.align	2
	.global	List_remove_node
	.type	List_remove_node, %function
List_remove_node:
	stp	x29, x30, [sp, -64]!
	and	w1, w1, 65535
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	adrp	x20, .LANCHOR83
	stp	x21, x22, [sp, 32]
	mov	x22, x0
	mov	w0, 6
	str	x23, [sp, 48]
	ldr	x23, [x20, #:lo12:.LANCHOR83]
	umull	x21, w1, w0
	mov	w0, 65535
	add	x19, x23, x21
	ldrh	w1, [x19, 2]
	cmp	w1, w0
	bne	.L473
	ldr	x0, [x22]
	cmp	x19, x0
	beq	.L473
	mov	w2, 435
	adrp	x1, .LANCHOR92
	adrp	x0, .LC5
	add	x1, x1, :lo12:.LANCHOR92
	add	x0, x0, :lo12:.LC5
	bl	printf
	adrp	x1, .LC6
	adrp	x0, .LC7
	add	x1, x1, :lo12:.LC6
	add	x0, x0, :lo12:.LC7
	bl	printf
.L473:
	ldr	x0, [x22]
	mov	w1, 65535
	cmp	x19, x0
	ldrh	w0, [x23, x21]
	bne	.L474
	cmp	w0, w1
	bne	.L475
	str	xzr, [x22]
.L476:
	mov	w0, -1
	strh	w0, [x23, x21]
	strh	w0, [x19, 2]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
.L475:
	ldr	x1, [x20, #:lo12:.LANCHOR83]
	mov	w2, 6
	umaddl	x0, w0, w2, x1
	mov	w1, -1
	str	x0, [x22]
	strh	w1, [x0, 2]
	b	.L476
.L474:
	cmp	w0, w1
	ldrh	w1, [x19, 2]
	bne	.L477
	cmp	w1, w0
	beq	.L476
	mov	w0, 6
	mov	w2, -1
	umull	x1, w1, w0
	ldr	x0, [x20, #:lo12:.LANCHOR83]
	strh	w2, [x0, x1]
	b	.L476
.L477:
	ldr	x2, [x20, #:lo12:.LANCHOR83]
	mov	w3, 6
	umaddl	x4, w0, w3, x2
	strh	w1, [x4, 2]
	ldrh	w1, [x19, 2]
	umull	x1, w1, w3
	strh	w0, [x2, x1]
	b	.L476
	.size	List_remove_node, .-List_remove_node
	.section	.text.List_pop_index_node,"ax",@progbits
	.align	2
	.global	List_pop_index_node
	.type	List_pop_index_node, %function
List_pop_index_node:
	ldr	x2, [x0]
	cbz	x2, .L485
	stp	x29, x30, [sp, -32]!
	adrp	x3, .LANCHOR83
	and	w1, w1, 65535
	mov	w4, 65535
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w5, 6
	ldr	x19, [x3, #:lo12:.LANCHOR83]
.L481:
	cbnz	w1, .L482
.L484:
	sub	x19, x2, x19
	mov	x2, -6148914691236517206
	asr	x19, x19, 1
	movk	x2, 0xaaab, lsl 0
	mul	x19, x19, x2
	and	w19, w19, 65535
	mov	w1, w19
	bl	List_remove_node
	mov	w0, w19
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L482:
	ldrh	w3, [x2]
	cmp	w3, w4
	beq	.L484
	sub	w1, w1, #1
	umaddl	x2, w3, w5, x19
	and	w1, w1, 65535
	b	.L481
.L485:
	mov	w0, 65535
	ret
	.size	List_pop_index_node, .-List_pop_index_node
	.section	.text.List_get_gc_head_node,"ax",@progbits
	.align	2
	.global	List_get_gc_head_node
	.type	List_get_gc_head_node, %function
List_get_gc_head_node:
	and	w2, w0, 65535
	adrp	x0, .LANCHOR84
	ldr	x1, [x0, #:lo12:.LANCHOR84]
	cbz	x1, .L495
	adrp	x0, .LANCHOR83
	mov	w4, 6
	ldr	x3, [x0, #:lo12:.LANCHOR83]
	mov	w0, 65535
.L492:
	cbz	w2, .L493
	ldrh	w1, [x1]
	cmp	w1, w0
	bne	.L494
	ret
.L494:
	sub	w2, w2, #1
	umaddl	x1, w1, w4, x3
	and	w2, w2, 65535
	b	.L492
.L495:
	mov	w0, 65535
	ret
.L493:
	sub	x0, x1, x3
	mov	x1, -6148914691236517206
	asr	x0, x0, 1
	movk	x1, 0xaaab, lsl 0
	mul	x0, x0, x1
	and	w0, w0, 65535
	ret
	.size	List_get_gc_head_node, .-List_get_gc_head_node
	.section	.text.List_update_data_list,"ax",@progbits
	.align	2
	.global	List_update_data_list
	.type	List_update_data_list, %function
List_update_data_list:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	and	w19, w0, 65535
	adrp	x0, .LANCHOR93
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	ldrh	w0, [x0, #:lo12:.LANCHOR93]
	stp	x25, x26, [sp, 64]
	cmp	w0, w19
	beq	.L498
	adrp	x0, .LANCHOR94
	ldrh	w0, [x0, #:lo12:.LANCHOR94]
	cmp	w0, w19
	beq	.L498
	adrp	x0, .LANCHOR95
	ldrh	w0, [x0, #:lo12:.LANCHOR95]
	cmp	w0, w19
	beq	.L498
	adrp	x0, .LANCHOR83
	mov	w21, 6
	adrp	x24, .LANCHOR84
	mov	x26, x0
	umull	x21, w19, w21
	ldr	x23, [x0, #:lo12:.LANCHOR83]
	ldr	x1, [x24, #:lo12:.LANCHOR84]
	add	x22, x23, x21
	cmp	x22, x1
	beq	.L498
	adrp	x1, .LANCHOR85
	ubfiz	x0, x19, 1, 16
	mov	x25, x1
	ldr	x2, [x1, #:lo12:.LANCHOR85]
	mov	w1, 65535
	ldrh	w20, [x2, x0]
	ldrh	w0, [x22, 4]
	cmp	w0, 0
	mul	w20, w20, w0
	ldrh	w0, [x22, 2]
	csinv	w20, w20, wzr, ne
	cmp	w0, w1
	bne	.L501
	ldrh	w1, [x23, x21]
	cmp	w1, w0
	bne	.L501
	mov	w2, 571
	adrp	x1, .LANCHOR96
	adrp	x0, .LC5
	add	x1, x1, :lo12:.LANCHOR96
	add	x0, x0, :lo12:.LC5
	bl	printf
	adrp	x1, .LC6
	adrp	x0, .LC7
	add	x1, x1, :lo12:.LC6
	add	x0, x0, :lo12:.LC7
	bl	printf
.L501:
	ldrh	w0, [x22, 2]
	mov	w1, 65535
	cmp	w0, w1
	bne	.L502
	ldrh	w1, [x23, x21]
	cmp	w1, w0
	beq	.L498
.L502:
	mov	w1, 6
	mov	x2, -6148914691236517206
	movk	x2, 0xaaab, lsl 0
	umull	x0, w0, w1
	asr	x1, x0, 1
	mul	x1, x1, x2
	ldr	x2, [x25, #:lo12:.LANCHOR85]
	ldrh	w1, [x2, x1, lsl 1]
	ldr	x2, [x26, #:lo12:.LANCHOR83]
	add	x0, x2, x0
	ldrh	w2, [x0, 4]
	cmp	w2, 0
	mul	w0, w1, w2
	csinv	w0, w0, wzr, ne
	cmp	w20, w0
	bcs	.L498
	adrp	x20, .LANCHOR87
	mov	w1, w19
	add	x0, x24, :lo12:.LANCHOR84
	bl	List_remove_node
	ldrh	w0, [x20, #:lo12:.LANCHOR87]
	cbnz	w0, .L504
	mov	w2, 585
	adrp	x1, .LANCHOR96
	adrp	x0, .LC5
	add	x1, x1, :lo12:.LANCHOR96
	add	x0, x0, :lo12:.LC5
	bl	printf
	adrp	x1, .LC6
	adrp	x0, .LC7
	add	x1, x1, :lo12:.LC6
	add	x0, x0, :lo12:.LC7
	bl	printf
.L504:
	ldrh	w0, [x20, #:lo12:.LANCHOR87]
	sub	w0, w0, #1
	strh	w0, [x20, #:lo12:.LANCHOR87]
	mov	w0, w19
	bl	INSERT_DATA_LIST
.L498:
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.size	List_update_data_list, .-List_update_data_list
	.section	.text.ftl_map_blk_alloc_new_blk,"ax",@progbits
	.align	2
	.global	ftl_map_blk_alloc_new_blk
	.type	ftl_map_blk_alloc_new_blk, %function
ftl_map_blk_alloc_new_blk:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	ldrh	w1, [x0, 10]
	mov	w20, 0
	ldr	x0, [x0, 16]
	str	x21, [sp, 32]
.L509:
	cmp	w20, w1
	beq	.L513
	mov	x21, x0
	ldrh	w2, [x0], 2
	cbnz	w2, .L510
	bl	FtlFreeSysBlkQueueOut
	and	w1, w0, 65535
	strh	w0, [x21]
	sub	w2, w1, #1
	mov	w0, 65533
	cmp	w0, w2, uxth
	bcs	.L511
	adrp	x0, .LANCHOR77+6
	ldrh	w2, [x0, #:lo12:.LANCHOR77+6]
	adrp	x0, .LC8
	add	x0, x0, :lo12:.LC8
	bl	printf
.L512:
	b	.L512
.L511:
	ldr	w0, [x19, 48]
	strh	wzr, [x19, 2]
	add	w0, w0, 1
	str	w0, [x19, 48]
	ldrh	w0, [x19, 8]
	strh	w20, [x19]
	add	w0, w0, 1
	strh	w0, [x19, 8]
.L513:
	ldrh	w0, [x19, 10]
	cmp	w0, w20
	bhi	.L515
	mov	w2, 715
	adrp	x1, .LANCHOR97
	adrp	x0, .LC5
	add	x1, x1, :lo12:.LANCHOR97
	add	x0, x0, :lo12:.LC5
	bl	printf
	adrp	x1, .LC6
	adrp	x0, .LC7
	add	x1, x1, :lo12:.LC6
	add	x0, x0, :lo12:.LC7
	bl	printf
.L515:
	mov	w0, 0
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
.L510:
	add	w20, w20, 1
	and	w20, w20, 65535
	b	.L509
	.size	ftl_map_blk_alloc_new_blk, .-ftl_map_blk_alloc_new_blk
	.section	.text.select_l2p_ram_region,"ax",@progbits
	.align	2
	.global	select_l2p_ram_region
	.type	select_l2p_ram_region, %function
select_l2p_ram_region:
	stp	x29, x30, [sp, -32]!
	adrp	x0, .LANCHOR67
	mov	x1, 0
	mov	w3, 65535
	add	x29, sp, 0
	ldrh	w2, [x0, #:lo12:.LANCHOR67]
	adrp	x0, .LANCHOR98
	str	x19, [sp, 16]
	ldr	x0, [x0, #:lo12:.LANCHOR98]
.L518:
	and	w19, w1, 65535
	cmp	w19, w2
	bcc	.L520
	add	x3, x0, 4
	mov	w19, w2
	mov	w5, -2147483648
	mov	w1, 0
.L521:
	cmp	w1, w2
	bne	.L523
	cmp	w19, w2
	bcc	.L519
	adrp	x1, .LANCHOR99
	mov	w19, w2
	mov	w3, -1
	ldrh	w4, [x1, #:lo12:.LANCHOR99]
	mov	w1, 0
.L524:
	cmp	w1, w2
	bne	.L526
	cmp	w19, w1
	bcc	.L519
	mov	w2, 977
	adrp	x1, .LANCHOR100
	adrp	x0, .LC5
	add	x1, x1, :lo12:.LANCHOR100
	add	x0, x0, :lo12:.LC5
	bl	printf
	adrp	x1, .LC6
	adrp	x0, .LC7
	add	x1, x1, :lo12:.LC6
	add	x0, x0, :lo12:.LC7
	bl	printf
	b	.L519
.L520:
	add	x1, x1, 1
	add	x4, x0, x1, lsl 4
	ldrh	w4, [x4, -16]
	cmp	w4, w3
	bne	.L518
.L519:
	mov	w0, w19
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L523:
	ldr	w4, [x3]
	tbnz	w4, #31, .L522
	cmp	w5, w4
	bls	.L522
	mov	w5, w4
	mov	w19, w1
.L522:
	add	w1, w1, 1
	add	x3, x3, 16
	and	w1, w1, 65535
	b	.L521
.L526:
	ldr	w6, [x0, 4]
	cmp	w3, w6
	bls	.L525
	ldrh	w5, [x0]
	cmp	w5, w4
	csel	w3, w3, w6, eq
	csel	w19, w19, w1, eq
.L525:
	add	w1, w1, 1
	add	x0, x0, 16
	and	w1, w1, 65535
	b	.L524
	.size	select_l2p_ram_region, .-select_l2p_ram_region
	.section	.text.FtlUpdateVaildLpn,"ax",@progbits
	.align	2
	.global	FtlUpdateVaildLpn
	.type	FtlUpdateVaildLpn, %function
FtlUpdateVaildLpn:
	adrp	x2, .LANCHOR101
	mov	x3, x2
	ldrh	w1, [x2, #:lo12:.LANCHOR101]
	cmp	w1, 4
	bhi	.L529
	cbnz	w0, .L529
	add	w1, w1, 1
	strh	w1, [x2, #:lo12:.LANCHOR101]
	ret
.L529:
	adrp	x1, .LANCHOR40
	adrp	x0, .LANCHOR102
	strh	wzr, [x3, #:lo12:.LANCHOR101]
	mov	w2, 0
	ldrh	w5, [x1, #:lo12:.LANCHOR40]
	adrp	x1, .LANCHOR85
	str	wzr, [x0, #:lo12:.LANCHOR102]
	mov	w3, 0
	ldr	x6, [x1, #:lo12:.LANCHOR85]
	mov	w7, 65535
	mov	x1, 0
.L530:
	cmp	w5, w1, uxth
	bhi	.L532
	cbz	w3, .L528
	str	w2, [x0, #:lo12:.LANCHOR102]
.L528:
	ret
.L532:
	ldrh	w4, [x6, x1, lsl 1]
	cmp	w4, w7
	beq	.L531
	add	w2, w2, w4
	mov	w3, 1
.L531:
	add	x1, x1, 1
	b	.L530
	.size	FtlUpdateVaildLpn, .-FtlUpdateVaildLpn
	.section	.text.ftl_set_blk_mode,"ax",@progbits
	.align	2
	.global	ftl_set_blk_mode
	.type	ftl_set_blk_mode, %function
ftl_set_blk_mode:
	and	w0, w0, 65535
	cbz	w1, .L539
	b	ftl_set_blk_mode.part.11
.L539:
	adrp	x1, .LANCHOR1
	ubfx	x2, x0, 5, 11
	lsl	x2, x2, 2
	ldr	x3, [x1, #:lo12:.LANCHOR1]
	and	w1, w0, 31
	mov	w0, 1
	lsl	w0, w0, w1
	ldr	w1, [x3, x2]
	bic	w0, w1, w0
	str	w0, [x3, x2]
	ret
	.size	ftl_set_blk_mode, .-ftl_set_blk_mode
	.section	.text.ftl_get_blk_mode,"ax",@progbits
	.align	2
	.global	ftl_get_blk_mode
	.type	ftl_get_blk_mode, %function
ftl_get_blk_mode:
	adrp	x1, .LANCHOR1
	and	w0, w0, 65535
	ldr	x1, [x1, #:lo12:.LANCHOR1]
	ubfx	x2, x0, 5, 11
	and	w0, w0, 31
	ldr	w1, [x1, x2, lsl 2]
	lsr	w0, w1, w0
	and	w0, w0, 1
	ret
	.size	ftl_get_blk_mode, .-ftl_get_blk_mode
	.section	.text.ftl_sb_update_avl_pages,"ax",@progbits
	.align	2
	.global	ftl_sb_update_avl_pages
	.type	ftl_sb_update_avl_pages, %function
ftl_sb_update_avl_pages:
	and	w2, w2, 65535
	and	w6, w1, 65535
	ubfiz	x4, x2, 1, 16
	adrp	x1, .LANCHOR38
	add	x4, x4, 16
	strh	wzr, [x0, 4]
	add	x4, x0, x4
	ldrh	w3, [x1, #:lo12:.LANCHOR38]
	mov	w1, 65535
.L542:
	cmp	w2, w3
	bcc	.L544
	adrp	x1, .LANCHOR52
	ubfiz	x3, x3, 1, 16
	add	x3, x3, 16
	add	x2, x0, 16
	ldrh	w1, [x1, #:lo12:.LANCHOR52]
	add	x3, x0, x3
	mov	w5, 65535
	sub	w1, w1, #1
	and	w1, w1, 65535
	sub	w1, w1, w6
.L545:
	cmp	x2, x3
	bne	.L547
	ret
.L544:
	ldrh	w5, [x4]
	cmp	w5, w1
	beq	.L543
	ldrh	w5, [x0, 4]
	add	w5, w5, 1
	strh	w5, [x0, 4]
.L543:
	add	w2, w2, 1
	add	x4, x4, 2
	and	w2, w2, 65535
	b	.L542
.L547:
	ldrh	w4, [x2]
	cmp	w4, w5
	beq	.L546
	ldrh	w4, [x0, 4]
	add	w4, w1, w4
	strh	w4, [x0, 4]
.L546:
	add	x2, x2, 2
	b	.L545
	.size	ftl_sb_update_avl_pages, .-ftl_sb_update_avl_pages
	.section	.text.make_superblock,"ax",@progbits
	.align	2
	.global	make_superblock
	.type	make_superblock, %function
make_superblock:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	ldrh	w1, [x0]
	str	x19, [sp, 16]
	mov	x19, x0
	adrp	x0, .LANCHOR40
	ldrh	w0, [x0, #:lo12:.LANCHOR40]
	cmp	w1, w0
	bcc	.L549
	mov	w2, 2819
	adrp	x1, .LANCHOR103
	adrp	x0, .LC5
	add	x1, x1, :lo12:.LANCHOR103
	add	x0, x0, :lo12:.LC5
	bl	printf
	adrp	x1, .LC6
	adrp	x0, .LC7
	add	x1, x1, :lo12:.LC6
	add	x0, x0, :lo12:.LC7
	bl	printf
.L549:
	adrp	x0, .LANCHOR38
	adrp	x7, .LANCHOR47
	add	x6, x19, 16
	add	x7, x7, :lo12:.LANCHOR47
	ldrh	w8, [x0, #:lo12:.LANCHOR38]
	mov	x5, 0
	strh	wzr, [x19, 4]
	mov	w10, -1
	strb	wzr, [x19, 7]
.L550:
	cmp	w8, w5, uxth
	bhi	.L552
	adrp	x1, .LANCHOR52
	ldrb	w0, [x19, 7]
	strb	wzr, [x19, 9]
	ldrh	w1, [x1, #:lo12:.LANCHOR52]
	mul	w0, w0, w1
	strh	w0, [x19, 4]
	adrp	x0, .LANCHOR104
	ldr	w0, [x0, #:lo12:.LANCHOR104]
	cbz	w0, .L553
	adrp	x0, .LANCHOR80
	ldrh	w1, [x19]
	ldr	x0, [x0, #:lo12:.LANCHOR80]
	ldrh	w0, [x0, x1, lsl 1]
	cmp	w0, 79
	bhi	.L553
	mov	w0, 1
	strb	w0, [x19, 9]
.L553:
	adrp	x0, .LANCHOR2
	ldrb	w0, [x0, #:lo12:.LANCHOR2]
	cbz	w0, .L554
	mov	w0, 1
	strb	w0, [x19, 9]
.L554:
	mov	w0, 0
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L552:
	ldrh	w1, [x19]
	ldrb	w0, [x7, x5]
	bl	V2P_block
	mov	w4, w0
	strh	w10, [x6]
	bl	FtlBbmIsBadBlock
	cbnz	w0, .L551
	strh	w4, [x6]
	ldrb	w0, [x19, 7]
	add	w0, w0, 1
	strb	w0, [x19, 7]
.L551:
	add	x5, x5, 1
	add	x6, x6, 2
	b	.L550
	.size	make_superblock, .-make_superblock
	.section	.text.update_multiplier_value,"ax",@progbits
	.align	2
	.global	update_multiplier_value
	.type	update_multiplier_value, %function
update_multiplier_value:
	and	w6, w0, 65535
	adrp	x0, .LANCHOR38
	mov	x7, 0
	adrp	x8, .LANCHOR47
	ldrh	w10, [x0, #:lo12:.LANCHOR38]
	adrp	x0, .LANCHOR52
	mov	w5, 0
	add	x8, x8, :lo12:.LANCHOR47
	ldrh	w11, [x0, #:lo12:.LANCHOR52]
	cmp	w10, w7, uxth
	bhi	.L574
	cbz	w5, .L572
	mov	w0, 32768
	sdiv	w5, w0, w5
.L573:
	adrp	x0, .LANCHOR83
	mov	w1, 6
	ldr	x0, [x0, #:lo12:.LANCHOR83]
	umaddl	x6, w6, w1, x0
	mov	w0, 0
	strh	w5, [x6, 4]
	ret
.L567:
	mov	w5, 0
	b	.L566
.L572:
	mov	w5, 0
	b	.L573
.L574:
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
.L565:
	ldrb	w0, [x8, x7]
	mov	w1, w6
	bl	V2P_block
	bl	FtlBbmIsBadBlock
	cbnz	w0, .L564
	add	w5, w5, w11
	and	w5, w5, 65535
.L564:
	add	x7, x7, 1
	cmp	w10, w7, uxth
	bhi	.L565
	cbz	w5, .L567
	mov	w0, 32768
	sdiv	w5, w0, w5
.L566:
	adrp	x0, .LANCHOR83
	mov	w1, 6
	ldr	x0, [x0, #:lo12:.LANCHOR83]
	umaddl	x6, w6, w1, x0
	mov	w0, 0
	strh	w5, [x6, 4]
	ldp	x29, x30, [sp], 16
	ret
	.size	update_multiplier_value, .-update_multiplier_value
	.section	.text.GetFreeBlockMinEraseCount,"ax",@progbits
	.align	2
	.global	GetFreeBlockMinEraseCount
	.type	GetFreeBlockMinEraseCount, %function
GetFreeBlockMinEraseCount:
	adrp	x0, .LANCHOR89
	ldr	x0, [x0, #:lo12:.LANCHOR89]
	cbz	x0, .L577
	adrp	x1, .LANCHOR83
	ldr	x1, [x1, #:lo12:.LANCHOR83]
	sub	x0, x0, x1
	mov	x1, -6148914691236517206
	asr	x0, x0, 1
	movk	x1, 0xaaab, lsl 0
	mul	x0, x0, x1
	adrp	x1, .LANCHOR80
	ldr	x1, [x1, #:lo12:.LANCHOR80]
	and	x0, x0, 65535
	ldrh	w0, [x1, x0, lsl 1]
	ret
.L577:
	mov	w0, 0
	ret
	.size	GetFreeBlockMinEraseCount, .-GetFreeBlockMinEraseCount
	.section	.text.GetFreeBlockMaxEraseCount,"ax",@progbits
	.align	2
	.global	GetFreeBlockMaxEraseCount
	.type	GetFreeBlockMaxEraseCount, %function
GetFreeBlockMaxEraseCount:
	adrp	x1, .LANCHOR89
	and	w0, w0, 65535
	ldr	x1, [x1, #:lo12:.LANCHOR89]
	cbz	x1, .L585
	adrp	x2, .LANCHOR90
	mov	w3, 7
	mov	w5, 6
	mov	w6, 65535
	ldrh	w2, [x2, #:lo12:.LANCHOR90]
	mul	w2, w2, w3
	asr	w2, w2, 3
	cmp	w0, w2
	csel	w0, w2, w0, gt
	adrp	x2, .LANCHOR83
	ldr	x3, [x2, #:lo12:.LANCHOR83]
	mov	x2, -6148914691236517206
	movk	x2, 0xaaab, lsl 0
	sub	x1, x1, x3
	asr	x1, x1, 1
	mul	x1, x1, x2
	mov	w2, 0
	and	w1, w1, 65535
.L581:
	cmp	w0, w2
	beq	.L584
	umull	x4, w1, w5
	ldrh	w4, [x3, x4]
	cmp	w4, w6
	bne	.L582
.L584:
	adrp	x0, .LANCHOR80
	ubfiz	x1, x1, 1, 16
	ldr	x0, [x0, #:lo12:.LANCHOR80]
	ldrh	w0, [x0, x1]
	ret
.L582:
	add	w2, w2, 1
	mov	w1, w4
	and	w2, w2, 65535
	b	.L581
.L585:
	mov	w0, 0
	ret
	.size	GetFreeBlockMaxEraseCount, .-GetFreeBlockMaxEraseCount
	.section	.text.free_data_superblock,"ax",@progbits
	.align	2
	.global	free_data_superblock
	.type	free_data_superblock, %function
free_data_superblock:
	and	w0, w0, 65535
	mov	w1, 65535
	cmp	w0, w1
	beq	.L589
	stp	x29, x30, [sp, -16]!
	adrp	x2, .LANCHOR85
	ubfiz	x1, x0, 1, 16
	add	x29, sp, 0
	ldr	x2, [x2, #:lo12:.LANCHOR85]
	strh	wzr, [x2, x1]
	bl	INSERT_FREE_LIST
	mov	w0, 0
	ldp	x29, x30, [sp], 16
	ret
.L589:
	mov	w0, 0
	ret
	.size	free_data_superblock, .-free_data_superblock
	.section	.text.FtlGcBufInit,"ax",@progbits
	.align	2
	.global	FtlGcBufInit
	.type	FtlGcBufInit, %function
FtlGcBufInit:
	adrp	x1, .LANCHOR106
	adrp	x0, .LANCHOR105
	adrp	x7, .LANCHOR107
	adrp	x6, .LANCHOR108
	ldr	x5, [x1, #:lo12:.LANCHOR106]
	adrp	x1, .LANCHOR57
	str	wzr, [x0, #:lo12:.LANCHOR105]
	adrp	x0, .LANCHOR38
	ldrh	w10, [x1, #:lo12:.LANCHOR57]
	adrp	x1, .LANCHOR58
	ldrh	w0, [x0, #:lo12:.LANCHOR38]
	mov	w8, 24
	ldrh	w11, [x1, #:lo12:.LANCHOR58]
	adrp	x1, .LANCHOR109
	ldr	x14, [x7, #:lo12:.LANCHOR107]
	mov	x3, x5
	ldr	x4, [x1, #:lo12:.LANCHOR109]
	mov	w2, 0
	ldr	x15, [x6, #:lo12:.LANCHOR108]
	nop // between mem op and mult-accumulate
	umaddl	x8, w0, w8, x5
	add	x4, x4, 8
	mov	w1, 0
	mov	w16, 1
.L593:
	add	w13, w2, w10
	add	w12, w1, w11
	cmp	x3, x8
	bne	.L594
	adrp	x1, .LANCHOR110
	ldr	x7, [x7, #:lo12:.LANCHOR107]
	ldr	x6, [x6, #:lo12:.LANCHOR108]
	mov	w8, 24
	ldr	w4, [x1, #:lo12:.LANCHOR110]
.L595:
	cmp	w0, w4
	bcc	.L596
	ret
.L594:
	asr	w2, w2, 2
	asr	w1, w1, 2
	add	x2, x14, x2, sxtw 2
	add	x1, x15, x1, sxtw 2
	str	w16, [x3, 16]
	stp	x2, x1, [x3]
	add	x3, x3, 24
	stp	x2, x1, [x4]
	add	x4, x4, 56
	mov	w1, w12
	mov	w2, w13
	b	.L593
.L596:
	umull	x3, w0, w8
	mul	w1, w10, w0
	add	x2, x5, x3
	asr	w1, w1, 2
	add	x1, x7, x1, sxtw 2
	str	wzr, [x2, 16]
	str	x1, [x5, x3]
	mul	w1, w11, w0
	add	w0, w0, 1
	and	w0, w0, 65535
	asr	w1, w1, 2
	add	x1, x6, x1, sxtw 2
	str	x1, [x2, 8]
	b	.L595
	.size	FtlGcBufInit, .-FtlGcBufInit
	.section	.text.FtlGcBufFree,"ax",@progbits
	.align	2
	.global	FtlGcBufFree
	.type	FtlGcBufFree, %function
FtlGcBufFree:
	adrp	x2, .LANCHOR110
	mov	w3, 0
	mov	w7, 56
	mov	w10, 24
	ldr	w8, [x2, #:lo12:.LANCHOR110]
	adrp	x2, .LANCHOR106
	ldr	x4, [x2, #:lo12:.LANCHOR106]
.L598:
	cmp	w3, w1
	bcs	.L597
	umaddl	x6, w3, w7, x0
	mov	w2, 0
	b	.L603
.L599:
	add	w2, w2, 1
	and	w2, w2, 65535
.L603:
	cmp	w2, w8
	bcs	.L600
	umull	x5, w2, w10
	add	x11, x4, x5
	ldr	x12, [x4, x5]
	ldr	x5, [x6, 8]
	cmp	x12, x5
	bne	.L599
	str	wzr, [x11, 16]
.L600:
	add	w3, w3, 1
	and	w3, w3, 65535
	b	.L598
.L597:
	ret
	.size	FtlGcBufFree, .-FtlGcBufFree
	.section	.text.FtlGcBufAlloc,"ax",@progbits
	.align	2
	.global	FtlGcBufAlloc
	.type	FtlGcBufAlloc, %function
FtlGcBufAlloc:
	adrp	x2, .LANCHOR110
	mov	w3, 0
	mov	w7, 24
	mov	w8, 1
	ldr	w5, [x2, #:lo12:.LANCHOR110]
	adrp	x2, .LANCHOR106
	mov	w10, 56
	ldr	x6, [x2, #:lo12:.LANCHOR106]
.L605:
	cmp	w3, w1
	bcs	.L604
	mov	w2, 0
	b	.L610
.L606:
	add	w2, w2, 1
	and	w2, w2, 65535
.L610:
	cmp	w2, w5
	bcs	.L607
	umaddl	x4, w2, w7, x6
	ldr	w11, [x4, 16]
	cbnz	w11, .L606
	umaddl	x2, w3, w10, x0
	ldr	x11, [x4]
	str	w8, [x4, 16]
	ldr	x4, [x4, 8]
	stp	x11, x4, [x2, 8]
.L607:
	add	w3, w3, 1
	and	w3, w3, 65535
	b	.L605
.L604:
	ret
	.size	FtlGcBufAlloc, .-FtlGcBufAlloc
	.section	.text.IsBlkInGcList,"ax",@progbits
	.align	2
	.global	IsBlkInGcList
	.type	IsBlkInGcList, %function
IsBlkInGcList:
	adrp	x1, .LANCHOR111
	and	w0, w0, 65535
	ldrh	w2, [x1, #:lo12:.LANCHOR111]
	adrp	x1, .LANCHOR112
	ldr	x3, [x1, #:lo12:.LANCHOR112]
	mov	x1, 0
.L612:
	cmp	w2, w1, uxth
	bhi	.L614
	mov	w0, 0
	ret
.L614:
	add	x1, x1, 1
	add	x4, x3, x1, lsl 1
	ldrh	w4, [x4, -2]
	cmp	w4, w0
	bne	.L612
	mov	w0, 1
	ret
	.size	IsBlkInGcList, .-IsBlkInGcList
	.section	.text.FtlGcUpdatePage,"ax",@progbits
	.align	2
	.global	FtlGcUpdatePage
	.type	FtlGcUpdatePage, %function
FtlGcUpdatePage:
	mov	w6, w0
	mov	w10, w1
	mov	w8, w2
	stp	x29, x30, [sp, -16]!
	lsr	w0, w0, 10
	add	x29, sp, 0
	bl	P2V_block_in_plane
	and	w7, w0, 65535
	adrp	x4, .LANCHOR111
	adrp	x2, .LANCHOR112
	mov	x3, 0
	ldrh	w1, [x4, #:lo12:.LANCHOR111]
	ldr	x5, [x2, #:lo12:.LANCHOR112]
.L617:
	and	w2, w3, 65535
	cmp	w2, w1
	bcc	.L619
	bne	.L618
	and	x3, x3, 65535
	strh	w0, [x5, x3, lsl 1]
	ldrh	w0, [x4, #:lo12:.LANCHOR111]
	add	w0, w0, 1
	strh	w0, [x4, #:lo12:.LANCHOR111]
	b	.L618
.L619:
	add	x3, x3, 1
	add	x2, x5, x3, lsl 1
	ldrh	w2, [x2, -2]
	cmp	w2, w7
	bne	.L617
.L618:
	adrp	x4, .LANCHOR113
	adrp	x1, .LANCHOR114
	mov	w3, 12
	ldrh	w0, [x4, #:lo12:.LANCHOR113]
	ldr	x5, [x1, #:lo12:.LANCHOR114]
	umull	x3, w0, w3
	add	w0, w0, 1
	add	x7, x5, x3
	stp	w10, w8, [x7, 4]
	str	w6, [x5, x3]
	strh	w0, [x4, #:lo12:.LANCHOR113]
	ldp	x29, x30, [sp], 16
	ret
	.size	FtlGcUpdatePage, .-FtlGcUpdatePage
	.section	.text.FtlGcRefreshOpenBlock,"ax",@progbits
	.align	2
	.global	FtlGcRefreshOpenBlock
	.type	FtlGcRefreshOpenBlock, %function
FtlGcRefreshOpenBlock:
	adrp	x8, .LANCHOR115
	and	w0, w0, 65535
	ldrh	w10, [x8, #:lo12:.LANCHOR115]
	cmp	w10, w0
	beq	.L622
	adrp	x6, .LANCHOR116
	ldrh	w7, [x6, #:lo12:.LANCHOR116]
	cmp	w0, w7
	beq	.L622
	adrp	x4, .LANCHOR117
	ldrh	w5, [x4, #:lo12:.LANCHOR117]
	cmp	w0, w5
	beq	.L622
	adrp	x2, .LANCHOR118
	ldrh	w3, [x2, #:lo12:.LANCHOR118]
	cmp	w0, w3
	beq	.L622
	mov	w1, 65535
	cmp	w10, w1
	bne	.L623
	strh	w0, [x8, #:lo12:.LANCHOR115]
.L622:
	mov	w0, 0
	ret
.L623:
	cmp	w7, w1
	bne	.L624
	strh	w0, [x6, #:lo12:.LANCHOR116]
	b	.L622
.L624:
	cmp	w5, w1
	bne	.L625
	strh	w0, [x4, #:lo12:.LANCHOR117]
	b	.L622
.L625:
	cmp	w3, w1
	bne	.L622
	strh	w0, [x2, #:lo12:.LANCHOR118]
	b	.L622
	.size	FtlGcRefreshOpenBlock, .-FtlGcRefreshOpenBlock
	.section	.text.FtlGcRefreshBlock,"ax",@progbits
	.align	2
	.global	FtlGcRefreshBlock
	.type	FtlGcRefreshBlock, %function
FtlGcRefreshBlock:
	adrp	x8, .LANCHOR115
	and	w0, w0, 65535
	ldrh	w10, [x8, #:lo12:.LANCHOR115]
	cmp	w10, w0
	beq	.L634
	adrp	x6, .LANCHOR116
	ldrh	w7, [x6, #:lo12:.LANCHOR116]
	cmp	w0, w7
	beq	.L634
	adrp	x4, .LANCHOR117
	ldrh	w5, [x4, #:lo12:.LANCHOR117]
	cmp	w0, w5
	beq	.L634
	adrp	x2, .LANCHOR118
	ldrh	w3, [x2, #:lo12:.LANCHOR118]
	cmp	w0, w3
	beq	.L634
	mov	w1, 65535
	cmp	w10, w1
	bne	.L628
	strh	w0, [x8, #:lo12:.LANCHOR115]
.L634:
	mov	w0, 0
	ret
.L628:
	cmp	w7, w1
	bne	.L629
	strh	w0, [x6, #:lo12:.LANCHOR116]
	b	.L634
.L629:
	cmp	w5, w1
	bne	.L630
	strh	w0, [x4, #:lo12:.LANCHOR117]
	b	.L634
.L630:
	cmp	w3, w1
	bne	.L635
	strh	w0, [x2, #:lo12:.LANCHOR118]
	b	.L634
.L635:
	mov	w0, -1
	ret
	.size	FtlGcRefreshBlock, .-FtlGcRefreshBlock
	.section	.text.FtlGcMarkBadPhyBlk,"ax",@progbits
	.align	2
	.global	FtlGcMarkBadPhyBlk
	.type	FtlGcMarkBadPhyBlk, %function
FtlGcMarkBadPhyBlk:
	and	w12, w0, 65535
	stp	x29, x30, [sp, -16]!
	mov	w0, w12
	add	x29, sp, 0
	bl	P2V_block_in_plane
	and	w11, w0, 65535
	bl	FtlGcRefreshBlock
	adrp	x0, .LANCHOR104
	ldr	w0, [x0, #:lo12:.LANCHOR104]
	cbz	w0, .L637
	adrp	x1, .LANCHOR80
	ubfiz	x0, x11, 1, 16
	ldr	x2, [x1, #:lo12:.LANCHOR80]
	ldrh	w1, [x2, x0]
	cmp	w1, 39
	bls	.L637
	sub	w1, w1, #40
	strh	w1, [x2, x0]
.L637:
	adrp	x1, .LANCHOR119
	adrp	x3, .LANCHOR120
	add	x3, x3, :lo12:.LANCHOR120
	mov	x2, 0
	ldrh	w0, [x1, #:lo12:.LANCHOR119]
.L638:
	cmp	w0, w2, uxth
	bhi	.L640
	cmp	w0, 15
	bhi	.L639
	add	w2, w0, 1
	strh	w2, [x1, #:lo12:.LANCHOR119]
	adrp	x1, .LANCHOR120
	add	x1, x1, :lo12:.LANCHOR120
	strh	w12, [x1, w0, sxtw 1]
	b	.L639
.L640:
	add	x2, x2, 1
	add	x4, x3, x2, lsl 1
	ldrh	w4, [x4, -2]
	cmp	w4, w12
	bne	.L638
.L639:
	mov	w0, 0
	ldp	x29, x30, [sp], 16
	ret
	.size	FtlGcMarkBadPhyBlk, .-FtlGcMarkBadPhyBlk
	.section	.text.FtlGcReFreshBadBlk,"ax",@progbits
	.align	2
	.global	FtlGcReFreshBadBlk
	.type	FtlGcReFreshBadBlk, %function
FtlGcReFreshBadBlk:
	adrp	x0, .LANCHOR119
	ldrh	w0, [x0, #:lo12:.LANCHOR119]
	cbz	w0, .L652
	adrp	x1, .LANCHOR115
	ldrh	w2, [x1, #:lo12:.LANCHOR115]
	mov	w1, 65535
	cmp	w2, w1
	bne	.L652
	stp	x29, x30, [sp, -16]!
	adrp	x11, .LANCHOR121
	add	x29, sp, 0
	ldrh	w1, [x11, #:lo12:.LANCHOR121]
	cmp	w1, w0
	bcc	.L647
	strh	wzr, [x11, #:lo12:.LANCHOR121]
.L647:
	ldrh	w1, [x11, #:lo12:.LANCHOR121]
	adrp	x0, .LANCHOR120
	add	x0, x0, :lo12:.LANCHOR120
	ldrh	w0, [x0, x1, lsl 1]
	bl	P2V_block_in_plane
	bl	FtlGcRefreshBlock
	ldrh	w0, [x11, #:lo12:.LANCHOR121]
	ldp	x29, x30, [sp], 16
	add	w0, w0, 1
	strh	w0, [x11, #:lo12:.LANCHOR121]
	mov	w0, 0
	ret
.L652:
	mov	w0, 0
	ret
	.size	FtlGcReFreshBadBlk, .-FtlGcReFreshBadBlk
	.section	.text.flash_boot_enter_slc_mode,"ax",@progbits
	.align	2
	.global	flash_boot_enter_slc_mode
	.type	flash_boot_enter_slc_mode, %function
flash_boot_enter_slc_mode:
	adrp	x1, .LANCHOR122
	and	w0, w0, 255
	ldr	w2, [x1, #:lo12:.LANCHOR122]
	mov	w1, 12336
	movk	w1, 0x5638, lsl 16
	cmp	w2, w1
	bne	.L655
	b	flash_enter_slc_mode
.L655:
	ret
	.size	flash_boot_enter_slc_mode, .-flash_boot_enter_slc_mode
	.section	.text.flash_boot_exit_slc_mode,"ax",@progbits
	.align	2
	.global	flash_boot_exit_slc_mode
	.type	flash_boot_exit_slc_mode, %function
flash_boot_exit_slc_mode:
	adrp	x1, .LANCHOR122
	and	w0, w0, 255
	ldr	w2, [x1, #:lo12:.LANCHOR122]
	mov	w1, 12336
	movk	w1, 0x5638, lsl 16
	cmp	w2, w1
	bne	.L657
	b	flash_exit_slc_mode
.L657:
	ret
	.size	flash_boot_exit_slc_mode, .-flash_boot_exit_slc_mode
	.section	.text.FW_FlashBlockErase.constprop.42,"ax",@progbits
	.align	2
	.type	FW_FlashBlockErase.constprop.42, %function
FW_FlashBlockErase.constprop.42:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w20, w0
	adrp	x0, .LANCHOR7
	ldr	x0, [x0, #:lo12:.LANCHOR7]
	ldrb	w19, [x0, 9]
	mov	w0, 0
	bl	flash_boot_enter_slc_mode
	mov	w2, 0
	mov	w0, 0
	udiv	w1, w20, w19
	bl	FlashEraseBlock
	mov	w19, w0
	mov	w0, 0
	bl	flash_boot_exit_slc_mode
	and	w0, w19, 255
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	FW_FlashBlockErase.constprop.42, .-FW_FlashBlockErase.constprop.42
	.section	.text.ftl_memset,"ax",@progbits
	.align	2
	.global	ftl_memset
	.type	ftl_memset, %function
ftl_memset:
	uxtw	x2, w2
	b	memset
	.size	ftl_memset, .-ftl_memset
	.section	.text.BuildFlashLsbPageTable,"ax",@progbits
	.align	2
	.global	BuildFlashLsbPageTable
	.type	BuildFlashLsbPageTable, %function
BuildFlashLsbPageTable:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w19, w1
	cbnz	w0, .L663
	adrp	x1, .LANCHOR17
	add	x1, x1, :lo12:.LANCHOR17
	mov	x0, 0
.L664:
	strh	w0, [x1, x0, lsl 1]
	add	x0, x0, 1
	cmp	x0, 512
	bne	.L664
.L670:
	adrp	x20, .LANCHOR123
	add	x20, x20, :lo12:.LANCHOR123
	mov	w1, 255
	mov	w2, 2048
	mov	x0, x20
	bl	ftl_memset
	adrp	x1, .LANCHOR17
	and	w19, w19, 65535
	add	x1, x1, :lo12:.LANCHOR17
	mov	x0, 0
.L665:
	cmp	w19, w0, uxth
	bhi	.L698
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L663:
	cmp	w0, 1
	bne	.L666
	adrp	x2, .LANCHOR17
	add	x2, x2, :lo12:.LANCHOR17
	mov	x1, 0
.L669:
	and	w0, w1, 65535
	cmp	x1, 3
	bls	.L667
	ubfiz	w3, w0, 1, 15
	and	w0, w0, 1
	add	w0, w0, 2
	sub	w0, w3, w0
	and	w0, w0, 65535
.L667:
	strh	w0, [x2, x1, lsl 1]
	add	x1, x1, 1
	cmp	x1, 512
	bne	.L669
	b	.L670
.L666:
	cmp	w0, 2
	bne	.L671
	adrp	x2, .LANCHOR17
	add	x2, x2, :lo12:.LANCHOR17
	mov	w1, 65535
	mov	x0, 0
.L673:
	cmp	x0, 2
	and	w3, w0, 65535
	csel	w3, w3, w1, cc
	strh	w3, [x2, x0, lsl 1]
	add	w1, w1, 2
	add	x0, x0, 1
	and	w1, w1, 65535
	cmp	x0, 512
	bne	.L673
	b	.L670
.L671:
	cmp	w0, 3
	bne	.L674
	adrp	x2, .LANCHOR17
	add	x2, x2, :lo12:.LANCHOR17
	mov	x1, 0
.L677:
	and	w0, w1, 65535
	cmp	x1, 5
	bls	.L675
	ubfiz	w3, w0, 1, 15
	and	w0, w0, 1
	add	w0, w0, 4
	sub	w0, w3, w0
	and	w0, w0, 65535
.L675:
	strh	w0, [x2, x1, lsl 1]
	add	x1, x1, 1
	cmp	x1, 512
	bne	.L677
	b	.L670
.L674:
	cmp	w0, 4
	bne	.L678
	adrp	x2, .LANCHOR17
	add	x1, x2, :lo12:.LANCHOR17
	add	x1, x1, 16
	strh	wzr, [x2, #:lo12:.LANCHOR17]
	mov	w2, 1
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
.L680:
	and	w3, w0, 1
	ubfiz	w2, w0, 1, 15
	add	w3, w3, 6
	add	w0, w0, 1
	sub	w2, w2, w3
	strh	w2, [x1], 2
	and	w0, w0, 65535
	cmp	w0, 512
	bne	.L680
	b	.L670
.L678:
	cmp	w0, 5
	bne	.L681
	adrp	x1, .LANCHOR17
	add	x1, x1, :lo12:.LANCHOR17
	mov	x0, 0
.L682:
	strh	w0, [x1, x0, lsl 1]
	add	x0, x0, 1
	cmp	x0, 16
	bne	.L682
	add	x1, x1, 32
.L683:
	strh	w0, [x1], 2
	add	w0, w0, 2
	and	w0, w0, 65535
	cmp	w0, 1008
	bne	.L683
	b	.L670
.L681:
	cmp	w0, 6
	bne	.L684
	adrp	x3, .LANCHOR17
	add	x3, x3, :lo12:.LANCHOR17
	mov	w1, 0
	mov	x2, 0
	mov	w4, 12
	mov	w5, 10
.L687:
	and	w0, w2, 65535
	cmp	x2, 5
	bls	.L685
	tst	x0, 1
	csel	w0, w4, w5, ne
	sub	w0, w1, w0
	and	w0, w0, 65535
.L685:
	strh	w0, [x3, x2, lsl 1]
	add	w1, w1, 3
	and	w1, w1, 65535
	add	x2, x2, 1
	cmp	w1, 1536
	bne	.L687
	b	.L670
.L684:
	cmp	w0, 9
	bne	.L688
	adrp	x1, .LANCHOR17
	add	x0, x1, :lo12:.LANCHOR17
	strh	wzr, [x1, #:lo12:.LANCHOR17]
	mov	w1, 1
	strh	w1, [x0, 2]
	mov	w1, 2
	strh	w1, [x0, 4]
	add	x1, x0, 6
	mov	w0, 3
.L689:
	strh	w0, [x1], 2
	add	w0, w0, 2
	and	w0, w0, 65535
	cmp	w0, 1021
	bne	.L689
	b	.L670
.L688:
	cmp	w0, 10
	bne	.L690
	adrp	x1, .LANCHOR17
	add	x1, x1, :lo12:.LANCHOR17
	mov	x0, 0
.L691:
	strh	w0, [x1, x0, lsl 1]
	add	x0, x0, 1
	cmp	x0, 63
	bne	.L691
	add	x1, x1, 126
.L692:
	strh	w0, [x1], 2
	add	w0, w0, 2
	and	w0, w0, 65535
	cmp	w0, 961
	bne	.L692
	b	.L670
.L690:
	cmp	w0, 11
	bne	.L693
	adrp	x1, .LANCHOR17
	add	x1, x1, :lo12:.LANCHOR17
	mov	x0, 0
.L694:
	strh	w0, [x1, x0, lsl 1]
	add	x0, x0, 1
	cmp	x0, 8
	bne	.L694
	add	x1, x1, 16
.L696:
	and	w3, w0, 1
	ubfiz	w2, w0, 1, 15
	add	w3, w3, 6
	add	w0, w0, 1
	sub	w2, w2, w3
	strh	w2, [x1], 2
	and	w0, w0, 65535
	cmp	w0, 512
	bne	.L696
	b	.L670
.L693:
	cmp	w0, 12
	bne	.L670
	adrp	x1, .LANCHOR17
	add	x0, x1, :lo12:.LANCHOR17
	strh	wzr, [x1, #:lo12:.LANCHOR17]
	mov	w1, 1
	strh	w1, [x0, 2]
	mov	w1, 2
	strh	w1, [x0, 4]
	mov	w1, 3
	strh	w1, [x0, 6]
	add	x1, x0, 8
	mov	w0, 4
.L697:
	sub	w2, w0, #1
	add	w2, w2, w0, lsr 1
	add	w0, w0, 1
	strh	w2, [x1], 2
	and	w0, w0, 65535
	cmp	w0, 512
	bne	.L697
	b	.L670
.L698:
	ldrh	w2, [x1, x0, lsl 1]
	add	x0, x0, 1
	strh	w2, [x20, w2, sxtw 1]
	b	.L665
	.size	BuildFlashLsbPageTable, .-BuildFlashLsbPageTable
	.section	.text.FlashDieInfoInit,"ax",@progbits
	.align	2
	.global	FlashDieInfoInit
	.type	FlashDieInfoInit, %function
FlashDieInfoInit:
	stp	x29, x30, [sp, -80]!
	adrp	x0, .LANCHOR31+10
	add	x29, sp, 0
	ldrh	w0, [x0, #:lo12:.LANCHOR31+10]
	stp	x19, x20, [sp, 16]
	adrp	x19, .LANCHOR124
	str	x25, [sp, 64]
	adrp	x25, .LANCHOR26
	stp	x21, x22, [sp, 32]
	mov	x22, 0
	stp	x23, x24, [sp, 48]
	adrp	x24, .LANCHOR27
	strb	wzr, [x19, #:lo12:.LANCHOR124]
	add	x21, x24, :lo12:.LANCHOR27
	strb	wzr, [x25, #:lo12:.LANCHOR26]
	bl	FlashBlockAlignInit
	mov	w2, 8
	mov	w1, 0
	adrp	x23, .LANCHOR18
	mov	x0, x21
	add	x20, x23, :lo12:.LANCHOR18
	bl	ftl_memset
	mov	w2, 32
	mov	w1, 0
	mov	x0, x20
	bl	ftl_memset
	mov	w2, 192
	mov	w1, 0
	adrp	x0, .LANCHOR23
	add	x0, x0, :lo12:.LANCHOR23
	bl	ftl_memset
	adrp	x0, .LANCHOR7
	adrp	x13, .LANCHOR22
	add	x15, x25, :lo12:.LANCHOR26
	add	x10, x13, :lo12:.LANCHOR22
	ldr	x7, [x0, #:lo12:.LANCHOR7]
	add	x11, x7, 1
	ldrb	w12, [x7]
.L722:
	mov	w2, w12
	add	x1, x10, x22, lsl 3
	mov	x0, x11
	bl	FlashMemCmp8
	cbnz	w0, .L721
	ldrb	w1, [x15]
	add	w0, w1, 1
	strb	w0, [x15]
	str	wzr, [x20, x1, lsl 2]
	strb	w22, [x21, x1]
.L721:
	add	x22, x22, 1
	cmp	x22, 4
	bne	.L722
	ldrb	w0, [x25, #:lo12:.LANCHOR26]
	strb	w0, [x19, #:lo12:.LANCHOR124]
	ldrb	w0, [x7, 8]
	cmp	w0, 2
	beq	.L723
.L727:
	ldrb	w0, [x25, #:lo12:.LANCHOR26]
	ldrh	w1, [x7, 14]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	mul	w0, w0, w1
	ldrb	w1, [x7, 13]
	ldp	x23, x24, [sp, 48]
	ldr	x25, [sp, 64]
	mul	w0, w0, w1
	adrp	x1, .LANCHOR125
	ldp	x29, x30, [sp], 80
	strh	w0, [x1, #:lo12:.LANCHOR125]
	ret
.L723:
	adrp	x0, .LANCHOR4
	add	x13, x13, :lo12:.LANCHOR22
	add	x15, x25, :lo12:.LANCHOR26
	add	x23, x23, :lo12:.LANCHOR18
	ldr	w20, [x0, #:lo12:.LANCHOR4]
	add	x14, x24, :lo12:.LANCHOR27
	mov	x19, 0
.L726:
	mov	w2, w12
	add	x1, x13, x19, lsl 3
	mov	x0, x11
	bl	FlashMemCmp8
	cbnz	w0, .L724
	ldrb	w2, [x7, 13]
	ldrh	w0, [x7, 14]
	ldrb	w1, [x15]
	and	w0, w0, 65280
	mul	w2, w2, w20
	mul	w0, w0, w2
	sxtw	x2, w1
	str	w0, [x23, x2, lsl 2]
	ldrb	w3, [x7, 23]
	cbz	w3, .L725
	lsl	w0, w0, 1
	str	w0, [x23, x2, lsl 2]
.L725:
	add	w1, w1, 1
	strb	w19, [x14, x2]
	strb	w1, [x15]
.L724:
	add	x19, x19, 1
	cmp	x19, 4
	bne	.L726
	b	.L727
	.size	FlashDieInfoInit, .-FlashDieInfoInit
	.section	.text.ftl_read_flash_info,"ax",@progbits
	.align	2
	.global	ftl_read_flash_info
	.type	ftl_read_flash_info, %function
ftl_read_flash_info:
	stp	x29, x30, [sp, -32]!
	mov	w2, 11
	mov	w1, 0
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	bl	ftl_memset
	adrp	x0, .LANCHOR7
	mov	w4, 1
	ldr	x2, [x0, #:lo12:.LANCHOR7]
	adrp	x0, .LANCHOR4
	ldr	w0, [x0, #:lo12:.LANCHOR4]
	ldrb	w3, [x2, 9]
	mul	w0, w0, w3
	and	w1, w0, 65535
	strb	w1, [x19, 4]
	ubfx	x0, x1, 8, 8
	strb	w0, [x19, 5]
	adrp	x0, .LANCHOR33
	ldrb	w0, [x0, #:lo12:.LANCHOR33]
	strb	w0, [x19, 7]
	ldrb	w0, [x2, 13]
	mul	w0, w0, w1
	ldrh	w1, [x2, 14]
	mul	w0, w0, w1
	ldrb	w1, [x2, 8]
	strb	w3, [x19, 6]
	mul	w0, w0, w1
	strb	w0, [x19]
	ubfx	x1, x0, 8, 8
	strb	w1, [x19, 1]
	ubfx	x1, x0, 16, 8
	lsr	w0, w0, 24
	strb	w1, [x19, 2]
	mov	x1, 0
	strb	w0, [x19, 3]
	mov	w0, 32
	strb	w0, [x19, 8]
	ldrb	w0, [x2, 7]
	adrp	x2, .LANCHOR27
	strb	w0, [x19, 9]
	add	x2, x2, :lo12:.LANCHOR27
	adrp	x0, .LANCHOR26
	strb	wzr, [x19, 10]
	ldrb	w3, [x0, #:lo12:.LANCHOR26]
.L736:
	cmp	w3, w1, uxtb
	bhi	.L737
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L737:
	ldrb	w0, [x1, x2]
	add	x1, x1, 1
	ldrb	w5, [x19, 10]
	lsl	w0, w4, w0
	orr	w0, w0, w5
	strb	w0, [x19, 10]
	b	.L736
	.size	ftl_read_flash_info, .-ftl_read_flash_info
	.section	.text.FtlBbt2Bitmap,"ax",@progbits
	.align	2
	.global	FtlBbt2Bitmap
	.type	FtlBbt2Bitmap, %function
FtlBbt2Bitmap:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	adrp	x0, .LANCHOR126
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	adrp	x22, .LANCHOR51
	ldrh	w2, [x0, #:lo12:.LANCHOR126]
	adrp	x23, .LANCHOR127
	add	x22, x22, :lo12:.LANCHOR51
	add	x23, x23, :lo12:.LANCHOR127
	mov	x19, 0
	mov	w24, 65535
	mov	x21, x1
	lsl	w2, w2, 2
	mov	w1, 0
	mov	x0, x21
	bl	ftl_memset
.L742:
	ldrh	w0, [x20, x19]
	cmp	w0, w24
	beq	.L739
	ldrh	w1, [x22]
	cmp	w1, w0
	bhi	.L741
	mov	w2, 92
	mov	x1, x23
	adrp	x0, .LC5
	add	x0, x0, :lo12:.LC5
	bl	printf
	adrp	x1, .LC6
	adrp	x0, .LC7
	add	x1, x1, :lo12:.LC6
	add	x0, x0, :lo12:.LC7
	bl	printf
.L741:
	ldrh	w1, [x20, x19]
	mov	w2, 1
	add	x19, x19, 2
	cmp	x19, 1024
	ubfx	x0, x1, 5, 11
	and	w1, w1, 31
	lsl	x0, x0, 2
	lsl	w2, w2, w1
	ldr	w1, [x21, x0]
	orr	w1, w1, w2
	str	w1, [x21, x0]
	adrp	x0, .LANCHOR76
	add	x0, x0, :lo12:.LANCHOR76
	ldrh	w1, [x0, 6]
	add	w1, w1, 1
	strh	w1, [x0, 6]
	bne	.L742
.L739:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
	.size	FtlBbt2Bitmap, .-FtlBbt2Bitmap
	.section	.text.FtlBbtMemInit,"ax",@progbits
	.align	2
	.global	FtlBbtMemInit
	.type	FtlBbtMemInit, %function
FtlBbtMemInit:
	adrp	x1, .LANCHOR76
	add	x0, x1, :lo12:.LANCHOR76
	mov	w2, -1
	add	x0, x0, 12
	strh	w2, [x1, #:lo12:.LANCHOR76]
	mov	w2, 16
	strh	wzr, [x0, -6]
	mov	w1, 255
	b	ftl_memset
	.size	FtlBbtMemInit, .-FtlBbtMemInit
	.section	.text.FtlFreeSysBlkQueueInit,"ax",@progbits
	.align	2
	.global	FtlFreeSysBlkQueueInit
	.type	FtlFreeSysBlkQueueInit, %function
FtlFreeSysBlkQueueInit:
	stp	x29, x30, [sp, -16]!
	adrp	x1, .LANCHOR77
	add	x3, x1, :lo12:.LANCHOR77
	mov	w2, 2048
	add	x29, sp, 0
	strh	w0, [x1, #:lo12:.LANCHOR77]
	mov	w1, 0
	strh	wzr, [x3, 2]
	add	x0, x3, 8
	strh	wzr, [x3, 4]
	strh	wzr, [x3, 6]
	bl	ftl_memset
	mov	w0, 0
	ldp	x29, x30, [sp], 16
	ret
	.size	FtlFreeSysBlkQueueInit, .-FtlFreeSysBlkQueueInit
	.section	.text.ftl_free_no_use_map_blk,"ax",@progbits
	.align	2
	.global	ftl_free_no_use_map_blk
	.type	ftl_free_no_use_map_blk, %function
ftl_free_no_use_map_blk:
	stp	x29, x30, [sp, -80]!
	mov	w1, 0
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	ldrh	w2, [x0, 10]
	stp	x21, x22, [sp, 32]
	ldp	x21, x20, [x0, 32]
	stp	x23, x24, [sp, 48]
	ldr	x22, [x0, 16]
	lsl	w2, w2, 1
	mov	x0, x21
	str	x25, [sp, 64]
	bl	ftl_memset
	mov	w0, 0
.L750:
	ldrh	w1, [x19, 6]
	cmp	w1, w0
	bhi	.L754
	adrp	x0, .LANCHOR53
	mov	w23, 0
	mov	w20, 0
	ldrh	w1, [x0, #:lo12:.LANCHOR53]
	ldrh	w0, [x19]
	strh	w1, [x21, x0, lsl 1]
	ldrh	w24, [x21]
.L755:
	ldrh	w0, [x19, 10]
	cmp	w0, w20
	bhi	.L759
	mov	w0, w23
	ldr	x25, [sp, 64]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
.L754:
	ubfiz	x1, x0, 2, 16
	ldr	w2, [x20, x1]
	mov	w1, 0
	ubfx	x2, x2, 10, 16
.L751:
	ldrh	w3, [x19, 10]
	cmp	w3, w1
	bhi	.L753
	add	w0, w0, 1
	and	w0, w0, 65535
	b	.L750
.L753:
	ubfiz	x3, x1, 1, 16
	ldrh	w4, [x22, x3]
	cmp	w4, w2
	bne	.L752
	cbz	w2, .L752
	ldrh	w4, [x21, x3]
	add	w4, w4, 1
	strh	w4, [x21, x3]
.L752:
	add	w1, w1, 1
	and	w1, w1, 65535
	b	.L751
.L759:
	ubfiz	x0, x20, 1, 16
	ldrh	w1, [x21, x0]
	cmp	w24, w1
	bls	.L756
	add	x25, x22, x0
	ldrh	w0, [x22, x0]
	cbnz	w0, .L757
.L758:
	add	w20, w20, 1
	and	w20, w20, 65535
	b	.L755
.L756:
	cbnz	w1, .L758
	add	x25, x22, x0
	ldrh	w0, [x22, x0]
	cbz	w0, .L758
.L760:
	mov	w1, 1
	bl	FtlFreeSysBlkQueueIn
	strh	wzr, [x25]
	ldrh	w0, [x19, 8]
	sub	w0, w0, #1
	strh	w0, [x19, 8]
	b	.L758
.L761:
	mov	w24, 0
	b	.L760
.L757:
	mov	w23, w20
	cbz	w1, .L761
	mov	w24, w1
	b	.L758
	.size	ftl_free_no_use_map_blk, .-ftl_free_no_use_map_blk
	.section	.text.FtlL2PDataInit,"ax",@progbits
	.align	2
	.global	FtlL2PDataInit
	.type	FtlL2PDataInit, %function
FtlL2PDataInit:
	stp	x29, x30, [sp, -64]!
	mov	w1, 0
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	adrp	x19, .LANCHOR128
	adrp	x20, .LANCHOR64
	stp	x21, x22, [sp, 32]
	ldr	x0, [x19, #:lo12:.LANCHOR128]
	adrp	x22, .LANCHOR57
	ldr	w2, [x20, #:lo12:.LANCHOR64]
	adrp	x21, .LANCHOR67
	str	x23, [sp, 48]
	adrp	x23, .LANCHOR129
	lsl	w2, w2, 1
	bl	ftl_memset
	ldrh	w0, [x21, #:lo12:.LANCHOR67]
	mov	w1, 255
	ldrh	w2, [x22, #:lo12:.LANCHOR57]
	mul	w2, w2, w0
	ldr	x0, [x23, #:lo12:.LANCHOR129]
	bl	ftl_memset
	adrp	x0, .LANCHOR98
	ldrh	w3, [x21, #:lo12:.LANCHOR67]
	ldr	x6, [x23, #:lo12:.LANCHOR129]
	mov	x1, 0
	ldr	x0, [x0, #:lo12:.LANCHOR98]
	mov	w2, -1
	ldrh	w5, [x22, #:lo12:.LANCHOR57]
	add	x3, x0, x3, lsl 4
.L771:
	add	x4, x1, x5
	cmp	x0, x3
	bne	.L772
	adrp	x1, .LANCHOR130
	add	x0, x1, :lo12:.LANCHOR130
	ldp	x21, x22, [sp, 32]
	strh	w2, [x1, #:lo12:.LANCHOR130]
	ldr	w1, [x20, #:lo12:.LANCHOR64]
	strh	w1, [x0, 10]
	mov	w1, -3902
	strh	w1, [x0, 4]
	adrp	x1, .LANCHOR131
	ldr	x23, [sp, 48]
	strh	w2, [x0, 2]
	ldrh	w1, [x1, #:lo12:.LANCHOR131]
	strh	w1, [x0, 8]
	adrp	x1, .LANCHOR66
	ldrh	w1, [x1, #:lo12:.LANCHOR66]
	strh	w1, [x0, 6]
	adrp	x1, .LANCHOR132
	ldr	x1, [x1, #:lo12:.LANCHOR132]
	str	x1, [x0, 16]
	adrp	x1, .LANCHOR133
	ldr	x1, [x1, #:lo12:.LANCHOR133]
	str	x1, [x0, 24]
	ldr	x1, [x19, #:lo12:.LANCHOR128]
	ldp	x19, x20, [sp, 16]
	str	x1, [x0, 32]
	adrp	x1, .LANCHOR134
	ldr	x1, [x1, #:lo12:.LANCHOR134]
	str	x1, [x0, 40]
	ldp	x29, x30, [sp], 64
	ret
.L772:
	and	x1, x1, -4
	strh	w2, [x0]
	add	x1, x6, x1
	str	wzr, [x0, 4]
	str	x1, [x0, 8]
	add	x0, x0, 16
	mov	x1, x4
	b	.L771
	.size	FtlL2PDataInit, .-FtlL2PDataInit
	.section	.text.FtlVariablesInit,"ax",@progbits
	.align	2
	.global	FtlVariablesInit
	.type	FtlVariablesInit, %function
FtlVariablesInit:
	stp	x29, x30, [sp, -32]!
	adrp	x0, .LANCHOR135
	mov	w1, -1
	add	x29, sp, 0
	str	xzr, [x0, #:lo12:.LANCHOR135]
	adrp	x0, .LANCHOR136
	str	x19, [sp, 16]
	adrp	x19, .LANCHOR41
	strh	w1, [x0, #:lo12:.LANCHOR136]
	adrp	x0, .LANCHOR137
	mov	w1, -1
	str	wzr, [x0, #:lo12:.LANCHOR137]
	adrp	x0, .LANCHOR138
	str	wzr, [x0, #:lo12:.LANCHOR138]
	adrp	x0, .LANCHOR139
	str	w1, [x0, #:lo12:.LANCHOR139]
	adrp	x0, .LANCHOR104
	mov	w1, 0
	str	wzr, [x0, #:lo12:.LANCHOR104]
	adrp	x0, .LANCHOR70
	strh	wzr, [x0, #:lo12:.LANCHOR70]
	adrp	x0, .LANCHOR61
	ldrh	w2, [x0, #:lo12:.LANCHOR61]
	adrp	x0, .LANCHOR71
	ldr	x0, [x0, #:lo12:.LANCHOR71]
	lsl	w2, w2, 1
	bl	ftl_memset
	adrp	x0, .LANCHOR80
	ldrh	w2, [x19, #:lo12:.LANCHOR41]
	mov	w1, 0
	ldr	x0, [x0, #:lo12:.LANCHOR80]
	lsl	w2, w2, 1
	bl	ftl_memset
	adrp	x0, .LANCHOR140
	ldrh	w2, [x19, #:lo12:.LANCHOR41]
	mov	w1, 0
	ldr	x0, [x0, #:lo12:.LANCHOR140]
	lsl	w2, w2, 1
	bl	ftl_memset
	mov	w2, 48
	mov	w1, 0
	adrp	x0, .LANCHOR82
	add	x0, x0, :lo12:.LANCHOR82
	bl	ftl_memset
	mov	w2, 512
	mov	w1, 0
	adrp	x0, .LANCHOR141
	add	x0, x0, :lo12:.LANCHOR141
	bl	ftl_memset
	bl	FtlGcBufInit
	bl	FtlL2PDataInit
	ldr	x19, [sp, 16]
	mov	w0, 0
	ldp	x29, x30, [sp], 32
	ret
	.size	FtlVariablesInit, .-FtlVariablesInit
	.section	.text.SupperBlkListInit,"ax",@progbits
	.align	2
	.global	SupperBlkListInit
	.type	SupperBlkListInit, %function
SupperBlkListInit:
	stp	x29, x30, [sp, -96]!
	adrp	x0, .LANCHOR41
	mov	w1, 0
	add	x29, sp, 0
	ldrh	w2, [x0, #:lo12:.LANCHOR41]
	mov	w0, 6
	stp	x23, x24, [sp, 48]
	adrp	x24, .LANCHOR83
	stp	x19, x20, [sp, 16]
	adrp	x23, .LANCHOR87
	stp	x21, x22, [sp, 32]
	adrp	x22, .LANCHOR90
	mul	w2, w2, w0
	ldr	x0, [x24, #:lo12:.LANCHOR83]
	stp	x25, x26, [sp, 64]
	adrp	x25, .LANCHOR40
	str	x27, [sp, 80]
	adrp	x26, .LANCHOR47
	add	x25, x25, :lo12:.LANCHOR40
	add	x26, x26, :lo12:.LANCHOR47
	bl	ftl_memset
	mov	w21, 0
	adrp	x0, .LANCHOR89
	mov	w20, 0
	mov	w19, 0
	strh	wzr, [x23, #:lo12:.LANCHOR87]
	str	xzr, [x0, #:lo12:.LANCHOR89]
	adrp	x0, .LANCHOR84
	strh	wzr, [x22, #:lo12:.LANCHOR90]
	adrp	x27, .LANCHOR38
	str	xzr, [x0, #:lo12:.LANCHOR84]
	adrp	x0, .LANCHOR86
	str	xzr, [x0, #:lo12:.LANCHOR86]
	adrp	x0, .LANCHOR142
	strh	wzr, [x0, #:lo12:.LANCHOR142]
.L777:
	ldrh	w0, [x25]
	cmp	w19, w0
	bge	.L784
	adrp	x0, .LANCHOR52
	ldrh	w8, [x27, #:lo12:.LANCHOR38]
	mov	w5, 0
	mov	w6, 0
	ldrh	w7, [x0, #:lo12:.LANCHOR52]
	b	.L785
.L779:
	ldrb	w0, [x26, w6, sxtw]
	mov	w1, w19
	bl	V2P_block
	bl	FtlBbmIsBadBlock
	cbnz	w0, .L778
	add	w5, w7, w5
	sxth	w5, w5
.L778:
	add	w6, w6, 1
	sxth	w6, w6
.L785:
	cmp	w6, w8
	blt	.L779
	cbz	w5, .L780
	mov	w0, 32768
	sdiv	w5, w0, w5
	sxth	w5, w5
.L781:
	ldr	x1, [x24, #:lo12:.LANCHOR83]
	mov	w0, 6
	smaddl	x0, w19, w0, x1
	strh	w5, [x0, 4]
	adrp	x0, .LANCHOR93
	ldrh	w0, [x0, #:lo12:.LANCHOR93]
	cmp	w19, w0
	beq	.L782
	adrp	x0, .LANCHOR94
	ldrh	w0, [x0, #:lo12:.LANCHOR94]
	cmp	w19, w0
	beq	.L782
	adrp	x0, .LANCHOR95
	ldrh	w0, [x0, #:lo12:.LANCHOR95]
	cmp	w19, w0
	beq	.L782
	adrp	x0, .LANCHOR85
	ldr	x0, [x0, #:lo12:.LANCHOR85]
	ldrh	w0, [x0, w19, sxtw 1]
	cbnz	w0, .L783
	add	w21, w21, 1
	mov	w0, w19
	and	w21, w21, 65535
	bl	INSERT_FREE_LIST
.L782:
	add	w19, w19, 1
	sxth	w19, w19
	b	.L777
.L780:
	adrp	x0, .LANCHOR85
	mov	w1, -1
	ldr	x0, [x0, #:lo12:.LANCHOR85]
	strh	w1, [x0, w19, sxtw 1]
	b	.L781
.L783:
	add	w20, w20, 1
	mov	w0, w19
	and	w20, w20, 65535
	bl	INSERT_DATA_LIST
	b	.L782
.L784:
	strh	w20, [x23, #:lo12:.LANCHOR87]
	add	w20, w20, w21
	strh	w21, [x22, #:lo12:.LANCHOR90]
	cmp	w0, w20
	bge	.L786
	mov	w2, 2899
	adrp	x1, .LANCHOR143
	adrp	x0, .LC5
	add	x1, x1, :lo12:.LANCHOR143
	add	x0, x0, :lo12:.LC5
	bl	printf
	adrp	x1, .LC6
	adrp	x0, .LC7
	add	x1, x1, :lo12:.LC6
	add	x0, x0, :lo12:.LC7
	bl	printf
.L786:
	mov	w0, 0
	ldr	x27, [sp, 80]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 96
	ret
	.size	SupperBlkListInit, .-SupperBlkListInit
	.section	.text.FtlGcPageVarInit,"ax",@progbits
	.align	2
	.global	FtlGcPageVarInit
	.type	FtlGcPageVarInit, %function
FtlGcPageVarInit:
	stp	x29, x30, [sp, -32]!
	adrp	x0, .LANCHOR111
	mov	w1, 255
	add	x29, sp, 0
	strh	wzr, [x0, #:lo12:.LANCHOR111]
	adrp	x0, .LANCHOR113
	str	x19, [sp, 16]
	adrp	x19, .LANCHOR54
	strh	wzr, [x0, #:lo12:.LANCHOR113]
	adrp	x0, .LANCHOR112
	ldrh	w2, [x19, #:lo12:.LANCHOR54]
	ldr	x0, [x0, #:lo12:.LANCHOR112]
	lsl	w2, w2, 1
	bl	ftl_memset
	ldrh	w2, [x19, #:lo12:.LANCHOR54]
	mov	w0, 12
	mov	w1, 255
	mul	w2, w2, w0
	adrp	x0, .LANCHOR114
	ldr	x0, [x0, #:lo12:.LANCHOR114]
	bl	ftl_memset
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	b	FtlGcBufInit
	.size	FtlGcPageVarInit, .-FtlGcPageVarInit
	.section	.text.idb_init,"ax",@progbits
	.align	2
	.global	idb_init
	.type	idb_init, %function
idb_init:
	stp	x29, x30, [sp, -16]!
	mov	w2, 262144
	mov	w1, 0
	adrp	x0, idb_buf
	add	x29, sp, 0
	add	x0, x0, :lo12:idb_buf
	bl	ftl_memset
	mov	w0, 0
	ldp	x29, x30, [sp], 16
	ret
	.size	idb_init, .-idb_init
	.section	.text.ftl_memcpy,"ax",@progbits
	.align	2
	.global	ftl_memcpy
	.type	ftl_memcpy, %function
ftl_memcpy:
	uxtw	x2, w2
	b	memcpy
	.size	ftl_memcpy, .-ftl_memcpy
	.section	.text.FlashReadIdbData,"ax",@progbits
	.align	2
	.global	FlashReadIdbData
	.type	FlashReadIdbData, %function
FlashReadIdbData:
	stp	x29, x30, [sp, -16]!
	mov	w2, 2048
	adrp	x1, .LANCHOR144
	add	x1, x1, :lo12:.LANCHOR144
	add	x29, sp, 0
	bl	ftl_memcpy
	mov	w0, 0
	ldp	x29, x30, [sp], 16
	ret
	.size	FlashReadIdbData, .-FlashReadIdbData
	.section	.text.FlashLoadPhyInfoInRam,"ax",@progbits
	.align	2
	.global	FlashLoadPhyInfoInRam
	.type	FlashLoadPhyInfoInRam, %function
FlashLoadPhyInfoInRam:
	stp	x29, x30, [sp, -48]!
	adrp	x0, .LANCHOR145
	add	x8, x0, :lo12:.LANCHOR145
	adrp	x11, .LANCHOR22
	add	x29, sp, 0
	add	x8, x8, 1
	mov	x7, x0
	add	x11, x11, :lo12:.LANCHOR22
	stp	x19, x20, [sp, 16]
	mov	x10, 0
	str	x21, [sp, 32]
.L798:
	ldrb	w2, [x8, -1]
	mov	w12, w10
	lsl	x21, x10, 5
	mov	x1, x11
	mov	x0, x8
	bl	FlashMemCmp8
	mov	w20, w0
	cbnz	w0, .L796
	add	x0, x7, :lo12:.LANCHOR145
	ubfiz	x12, x12, 5, 32
	add	x21, x0, x21
	add	x0, x0, x12
	adrp	x1, .LANCHOR146
	add	x4, x1, :lo12:.LANCHOR146
	ldrb	w3, [x0, 22]
	mov	x0, 0
.L797:
	lsl	x5, x0, 5
	mov	w2, w0
	ldrb	w5, [x5, x4]
	cmp	w5, w3
	beq	.L800
	add	x0, x0, 1
	cmp	x0, 4
	bne	.L797
	mov	w2, w0
.L800:
	ubfiz	x0, x2, 5, 32
	add	x1, x1, :lo12:.LANCHOR146
	adrp	x19, .LANCHOR31
	add	x19, x19, :lo12:.LANCHOR31
	add	x1, x1, x0
	mov	w2, 32
	adrp	x0, .LANCHOR8
	add	x0, x0, :lo12:.LANCHOR8
	bl	ftl_memcpy
	mov	w2, 32
	mov	x1, x21
	mov	x0, x19
	bl	ftl_memcpy
	ldrh	w0, [x19, 10]
	bl	FlashBlockAlignInit
	b	.L795
.L796:
	add	x10, x10, 1
	add	x8, x8, 32
	cmp	x10, 86
	bne	.L798
	mov	w20, -1
.L795:
	mov	w0, w20
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
	.size	FlashLoadPhyInfoInRam, .-FlashLoadPhyInfoInRam
	.section	.text.NandcCopy1KB,"ax",@progbits
	.align	2
	.global	NandcCopy1KB
	.type	NandcCopy1KB, %function
NandcCopy1KB:
	stp	x29, x30, [sp, -48]!
	and	w1, w1, 255
	cmp	w1, 1
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	and	w19, w2, 255
	str	x21, [sp, 32]
	add	x2, x0, 4096
	add	x21, x0, 512
	ubfiz	x0, x19, 9, 8
	mov	x20, x4
	add	x0, x2, x0
	bne	.L805
	cbz	x3, .L806
	mov	w2, 1024
	mov	x1, x3
	bl	ftl_memcpy
.L806:
	cbz	x20, .L804
	ldrb	w0, [x20]
	lsr	w19, w19, 1
	ldrb	w1, [x20, 1]
	orr	x1, x0, x1, lsl 8
	ldrb	w0, [x20, 2]
	orr	x1, x1, x0, lsl 16
	ldrb	w0, [x20, 3]
	orr	x0, x1, x0, lsl 24
	mov	w1, 12
	mul	w19, w19, w1
	str	w0, [x21, w19, sxtw 2]
.L804:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
.L805:
	cbz	x3, .L809
	mov	x1, x0
	mov	w2, 1024
	mov	x0, x3
	bl	ftl_memcpy
.L809:
	cbz	x20, .L804
	lsr	w19, w19, 1
	mov	w0, 12
	mul	w19, w19, w0
	ldr	w0, [x21, w19, sxtw 2]
	strb	w0, [x20]
	lsr	w1, w0, 8
	strb	w1, [x20, 1]
	lsr	w1, w0, 16
	lsr	w0, w0, 24
	strb	w1, [x20, 2]
	strb	w0, [x20, 3]
	b	.L804
	.size	NandcCopy1KB, .-NandcCopy1KB
	.section	.text.NandcXferData,"ax",@progbits
	.align	2
	.global	NandcXferData
	.type	NandcXferData, %function
NandcXferData:
	stp	x29, x30, [sp, -192]!
	tst	x3, 63
	add	x29, sp, 0
	stp	x25, x26, [sp, 64]
	and	w25, w0, 255
	stp	x19, x20, [sp, 16]
	adrp	x0, .LANCHOR0
	and	w20, w1, 255
	add	x0, x0, :lo12:.LANCHOR0
	sbfiz	x1, x25, 4, 32
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	mov	x26, x3
	stp	x27, x28, [sp, 80]
	and	w24, w2, 255
	mov	x21, x4
	ldr	x19, [x0, x1]
	bne	.L822
	cbnz	x4, .L823
	add	x21, x29, 128
	mov	w2, 64
	mov	w1, 255
	add	x0, x29, 128
	bl	ftl_memset
.L823:
	mov	x5, x21
	mov	x4, x26
	mov	w2, w24
	mov	w3, 0
	mov	w1, w20
	mov	w0, w25
	bl	NandcXferStart
	mov	w1, w20
	mov	w0, w25
	bl	NandcXferComp
	cbnz	w20, .L847
	adrp	x0, .LANCHOR32
	adrp	x4, .LANCHOR35
	mov	x1, x0
	add	x4, x4, :lo12:.LANCHOR35
	ldr	w2, [x0, #:lo12:.LANCHOR32]
	mov	w0, 128
	mov	w3, 64
	cmp	w2, 25
	ubfx	x2, x24, 1, 7
	add	x2, x21, x2, lsl 2
	csel	w3, w3, w0, cc
	mov	w0, 0
.L826:
	add	w5, w3, w0
	cmp	x21, x2
	bne	.L827
	adrp	x0, .LANCHOR34
	ldr	w4, [x1, #:lo12:.LANCHOR32]
	lsr	w24, w24, 2
	mov	w2, 0
	ldr	w3, [x0, #:lo12:.LANCHOR34]
	mov	w22, 0
.L828:
	cmp	w2, w24
	bcs	.L824
	cbnz	w4, .L834
.L824:
	str	wzr, [x19, 16]
.L835:
	adrp	x0, .LANCHOR34
	ldr	w0, [x0, #:lo12:.LANCHOR34]
	cmp	w0, 5
	bls	.L821
	cbnz	w20, .L821
	ldr	w0, [x19]
	mov	w1, 8192
	movk	w1, 0x2, lsl 16
	and	w1, w0, w1
	cmp	w1, 139264
	bne	.L821
	orr	w0, w0, 131072
	mov	w22, -1
	str	w0, [x19]
.L821:
	mov	w0, w22
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 192
	ret
.L827:
	ldr	x6, [x4, 8]
	and	x0, x0, 4294967292
	add	x21, x21, 4
	ldr	w0, [x6, x0]
	strb	w0, [x21, -4]
	lsr	w6, w0, 8
	strb	w6, [x21, -3]
	lsr	w6, w0, 16
	strb	w6, [x21, -2]
	lsr	w0, w0, 24
	strb	w0, [x21, -1]
	mov	w0, w5
	b	.L826
.L834:
	uxtw	x0, w2
	add	x0, x0, 8
	ldr	w0, [x19, x0, lsl 2]
	str	w0, [x29, 120]
	ldr	w0, [x29, 120]
	tbnz	x0, 2, .L850
	ldr	w0, [x29, 120]
	tbnz	x0, 15, .L850
	cmp	w3, 5
	bls	.L830
	ldr	w1, [x29, 120]
	ubfx	x6, x1, 3, 5
	ldr	w1, [x29, 120]
	ldr	w0, [x29, 120]
	ubfx	x1, x1, 27, 1
	ubfx	x5, x0, 16, 5
	ldr	w0, [x29, 120]
	orr	w1, w6, w1, lsl 5
	ubfx	x0, x0, 29, 1
	orr	w0, w5, w0, lsl 5
	cmp	w1, w0
	ldr	w0, [x29, 120]
	bls	.L831
	ubfx	x1, x0, 3, 5
	ldr	w0, [x29, 120]
	ubfx	x0, x0, 27, 1
.L856:
	orr	w0, w1, w0, lsl 5
.L832:
	cmp	w22, w0
	csel	w22, w22, w0, cs
.L829:
	add	w2, w2, 1
	b	.L828
.L831:
	ubfx	x1, x0, 16, 5
	ldr	w0, [x29, 120]
	ubfx	x0, x0, 29, 1
	b	.L856
.L830:
	cmp	w3, 3
	bls	.L851
	ldr	w1, [x29, 120]
	ubfx	x6, x1, 3, 5
	ldr	w1, [x29, 120]
	ldr	w0, [x29, 120]
	ubfx	x1, x1, 28, 1
	ubfx	x5, x0, 16, 5
	ldr	w0, [x29, 120]
	orr	w1, w6, w1, lsl 5
	ubfx	x0, x0, 30, 1
	orr	w0, w5, w0, lsl 5
	cmp	w1, w0
	ldr	w0, [x29, 120]
	bls	.L833
	ubfx	x1, x0, 3, 5
	ldr	w0, [x29, 120]
	ubfx	x0, x0, 28, 1
	b	.L856
.L833:
	ubfx	x1, x0, 16, 5
	ldr	w0, [x29, 120]
	ubfx	x0, x0, 30, 1
	b	.L856
.L851:
	mov	w0, 0
	b	.L832
.L850:
	mov	w22, -1
	b	.L829
.L847:
	mov	w22, 0
	b	.L824
.L822:
	cmp	w20, 1
	bne	.L836
	cmp	x4, 0
	mov	w23, 2
	csel	w23, w23, wzr, ne
	mov	w27, 0
	lsl	w23, w23, 1
	mov	w22, 0
.L837:
	cmp	w22, w24
	bcc	.L839
	mov	w22, 0
	b	.L835
.L839:
	and	w28, w22, 3
	cbz	x26, .L852
	lsl	w3, w22, 9
	add	x3, x26, x3
.L838:
	add	x4, x21, x27, uxtw
	mov	w2, w28
	mov	w1, 1
	mov	x0, x19
	bl	NandcCopy1KB
	add	w22, w22, 2
	mov	w3, w28
	mov	x5, 0
	mov	x4, 0
	mov	w2, 2
	mov	w1, 1
	mov	w0, w25
	bl	NandcXferStart
	add	w27, w27, w23
	mov	w1, 1
	mov	w0, w25
	bl	NandcXferComp
	b	.L837
.L852:
	mov	x3, 0
	b	.L838
.L836:
	mov	w0, w25
	mov	x5, 0
	mov	x4, 0
	mov	w3, 0
	mov	w2, 2
	mov	w1, 0
	bl	NandcXferStart
	mov	w27, 2
	cmp	x21, 0
	mov	w28, 0
	csel	w27, w27, wzr, ne
	mov	w23, 0
	lsl	w0, w27, 1
	mov	w22, 0
	str	w0, [x29, 108]
.L840:
	cmp	w24, w23
	bls	.L835
	mov	w0, w25
	mov	w1, w20
	bl	NandcXferComp
	add	w27, w23, 2
	ldr	w0, [x19, 32]
	cmp	w24, w27
	str	w0, [x29, 120]
	bls	.L841
	mov	x5, 0
	mov	x4, 0
	and	w3, w27, 3
	mov	w2, 2
	mov	w1, 0
	mov	w0, w25
	bl	NandcXferStart
.L841:
	ldr	w0, [x29, 120]
	tbnz	x0, 2, .L853
	ldr	w0, [x29, 120]
	ubfx	x1, x0, 3, 5
	ldr	w0, [x29, 120]
	ubfx	x0, x0, 27, 1
	orr	w0, w1, w0, lsl 5
	cmp	w22, w0
	csel	w22, w22, w0, cs
.L842:
	and	w2, w23, 3
	cbz	x26, .L854
	lsl	w3, w23, 9
	add	x3, x26, x3
.L843:
	add	x4, x21, x28, uxtw
	mov	x0, x19
	mov	w1, 0
	bl	NandcCopy1KB
	ldr	w0, [x29, 108]
	mov	w23, w27
	add	w28, w28, w0
	b	.L840
.L853:
	mov	w22, -1
	b	.L842
.L854:
	mov	x3, 0
	b	.L843
	.size	NandcXferData, .-NandcXferData
	.section	.text.FlashReadRawPage,"ax",@progbits
	.align	2
	.global	FlashReadRawPage
	.type	FlashReadRawPage, %function
FlashReadRawPage:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	ands	w19, w0, 255
	stp	x21, x22, [sp, 32]
	mov	w21, w1
	str	x23, [sp, 48]
	adrp	x1, .LANCHOR31+9
	mov	x22, x2
	mov	x23, x3
	ldrb	w20, [x1, #:lo12:.LANCHOR31+9]
	bne	.L858
	adrp	x0, .LANCHOR3
	adrp	x1, .LANCHOR4
	ldrb	w0, [x0, #:lo12:.LANCHOR3]
	ldr	w1, [x1, #:lo12:.LANCHOR4]
	mul	w0, w0, w1
	cmp	w0, w21
	mov	w0, 4
	csel	w20, w20, w0, ls
.L858:
	mov	w0, w19
	bl	NandcWaitFlashReady
	mov	w0, w19
	bl	NandcFlashCs
	mov	w1, w21
	mov	w0, w19
	bl	FlashReadCmd
	mov	w0, w19
	bl	NandcWaitFlashReady
	mov	w2, w20
	mov	x4, x23
	mov	x3, x22
	mov	w1, 0
	mov	w0, w19
	bl	NandcXferData
	mov	w2, w0
	mov	w0, w19
	bl	NandcFlashDeCs
	ldr	x23, [sp, 48]
	mov	w0, w2
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.size	FlashReadRawPage, .-FlashReadRawPage
	.section	.text.FlashDdrTunningRead,"ax",@progbits
	.align	2
	.global	FlashDdrTunningRead
	.type	FlashDdrTunningRead, %function
FlashDdrTunningRead:
	stp	x29, x30, [sp, -112]!
	add	x29, sp, 0
	stp	x23, x24, [sp, 48]
	and	w24, w0, 255
	adrp	x0, .LANCHOR19
	stp	x25, x26, [sp, 64]
	stp	x21, x22, [sp, 32]
	mov	w25, w1
	ldr	x0, [x0, #:lo12:.LANCHOR19]
	mov	w22, 6
	stp	x27, x28, [sp, 80]
	mov	x23, x2
	stp	x19, x20, [sp, 16]
	mov	x28, x3
	mov	w26, w4
	ldr	w0, [x0, 304]
	str	w0, [x29, 108]
	adrp	x0, .LANCHOR34
	ldr	w0, [x0, #:lo12:.LANCHOR34]
	cmp	w0, 8
	mov	w0, 12
	csel	w22, w22, w0, cc
	cbz	w4, .L874
	mov	w0, 1
	bl	FlashSetInterfaceMode
	mov	w0, 1
	bl	NandcSetMode
	mov	w0, w24
	adrp	x19, .LANCHOR25
	bl	FlashReset
	mov	x3, x28
	mov	x2, x23
	mov	w1, w25
	mov	w0, w24
	bl	FlashReadRawPage
	mov	w21, w0
	ldrb	w0, [x19, #:lo12:.LANCHOR25]
	bl	FlashSetInterfaceMode
	ldrb	w0, [x19, #:lo12:.LANCHOR25]
	bl	NandcSetMode
	cmn	w21, #1
	bne	.L863
.L872:
	mov	w21, -1
.L860:
	mov	w0, w21
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
.L863:
	mov	w1, w25
	mov	w2, w21
	adrp	x0, .LC9
	add	x0, x0, :lo12:.LC9
	bl	printf
	adrp	x1, .LANCHOR147
	ldr	w0, [x1, #:lo12:.LANCHOR147]
	add	w0, w0, 1
	cmp	w0, 2047
	bhi	.L865
	str	w0, [x1, #:lo12:.LANCHOR147]
	b	.L860
.L865:
	str	wzr, [x1, #:lo12:.LANCHOR147]
	mov	x28, 0
	mov	x23, 0
.L862:
	mov	w5, 0
	mov	w20, 0
	mov	w6, 0
	mov	w19, 0
	mov	w27, -1
.L870:
	stp	w5, w6, [x29, 100]
	mov	w0, w22
	bl	NandcSetDdrPara
	mov	w1, w25
	mov	x3, x28
	mov	x2, x23
	mov	w0, w24
	bl	FlashReadRawPage
	add	w1, w21, 1
	cmp	w0, w1
	ldp	w5, w6, [x29, 100]
	bhi	.L866
	cmp	w0, 2
	bhi	.L876
	add	w19, w19, 1
	cmp	w19, 9
	bls	.L876
	mov	w1, w20
	mov	w21, w0
	sub	w20, w22, w19
	mov	w27, 0
.L868:
	cmp	w19, w6
	csel	w20, w20, w1, hi
.L869:
	cbz	w20, .L871
	mov	w1, w20
	adrp	x0, .LC10
	add	x0, x0, :lo12:.LC10
	bl	printf
	mov	w0, w20
	bl	NandcSetDdrPara
.L871:
	cbz	w27, .L860
	adrp	x0, .LC11
	mov	w2, w25
	mov	w1, w24
	add	x0, x0, :lo12:.LC11
	bl	printf
	cbz	w26, .L872
	ldr	w1, [x29, 108]
	lsr	w0, w1, 8
	bl	NandcSetDdrPara
	b	.L860
.L874:
	mov	w21, 1024
	b	.L862
.L866:
	cmp	w19, w6
	bls	.L877
	sub	w20, w5, w19
	cmp	w19, 7
	bhi	.L869
	mov	w6, w19
.L877:
	mov	w19, 0
	b	.L867
.L876:
	mov	w5, w22
	mov	w21, w0
	mov	w27, 0
	mov	x28, 0
	mov	x23, 0
.L867:
	add	w22, w22, 2
	cmp	w22, 69
	bls	.L870
	mov	w1, w20
	mov	w20, w5
	b	.L868
	.size	FlashDdrTunningRead, .-FlashDdrTunningRead
	.section	.text.FlashReadPage,"ax",@progbits
	.align	2
	.global	FlashReadPage
	.type	FlashReadPage, %function
FlashReadPage:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	and	w20, w0, 255
	stp	x21, x22, [sp, 32]
	mov	w0, w20
	stp	x23, x24, [sp, 48]
	mov	w21, w1
	mov	x22, x2
	mov	x23, x3
	str	x25, [sp, 64]
	bl	FlashReadRawPage
	mov	w19, w0
	cmn	w0, #1
	bne	.L887
	adrp	x24, .LANCHOR6
	ldrb	w25, [x24, #:lo12:.LANCHOR6]
	cbnz	w25, .L888
.L890:
	adrp	x0, .LANCHOR30
	ldrb	w0, [x0, #:lo12:.LANCHOR30]
	cbz	w0, .L887
	adrp	x0, .LANCHOR19
	mov	w4, 1
	mov	x3, x23
	mov	x2, x22
	ldr	x0, [x0, #:lo12:.LANCHOR19]
	mov	w1, w21
	ldr	w24, [x0, 304]
	mov	w0, w20
	bl	FlashDdrTunningRead
	mov	w19, w0
	cmn	w0, #1
	beq	.L891
	adrp	x0, .LANCHOR33
	ldrb	w0, [x0, #:lo12:.LANCHOR33]
	cmp	w19, w0, lsr 1
	bls	.L887
.L891:
	lsr	w0, w24, 8
	bl	NandcSetDdrPara
	b	.L887
.L888:
	strb	wzr, [x24, #:lo12:.LANCHOR6]
	mov	x3, x23
	mov	x2, x22
	mov	w1, w21
	mov	w0, w20
	bl	FlashReadRawPage
	strb	w25, [x24, #:lo12:.LANCHOR6]
	cmn	w0, #1
	beq	.L890
	mov	w19, w0
.L887:
	adrp	x24, .LANCHOR148
	ldr	x4, [x24, #:lo12:.LANCHOR148]
	cbz	x4, .L886
	cmn	w19, #1
	bne	.L886
	mov	x3, x23
	mov	x2, x22
	mov	w1, w21
	mov	w0, w20
	blr	x4
	mov	w19, w0
	mov	w1, w0
	mov	w3, w21
	mov	w2, w20
	adrp	x0, .LC12
	add	x0, x0, :lo12:.LC12
	bl	printf
	cmn	w19, #1
	bne	.L886
	adrp	x0, .LANCHOR16
	ldrb	w0, [x0, #:lo12:.LANCHOR16]
	cbz	w0, .L886
	mov	w0, w20
	bl	flash_enter_slc_mode
	ldr	x4, [x24, #:lo12:.LANCHOR148]
	mov	x3, x23
	mov	x2, x22
	mov	w1, w21
	mov	w0, w20
	blr	x4
	mov	w19, w0
	mov	w0, w20
	bl	flash_exit_slc_mode
.L886:
	mov	w0, w19
	ldr	x25, [sp, 64]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
	.size	FlashReadPage, .-FlashReadPage
	.section	.text.FlashDdrParaScan,"ax",@progbits
	.align	2
	.global	FlashDdrParaScan
	.type	FlashDdrParaScan, %function
FlashDdrParaScan:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	adrp	x19, .LANCHOR25
	and	w20, w0, 255
	stp	x21, x22, [sp, 32]
	ldrb	w0, [x19, #:lo12:.LANCHOR25]
	mov	w21, w1
	bl	FlashSetInterfaceMode
	ldrb	w0, [x19, #:lo12:.LANCHOR25]
	bl	NandcSetMode
	mov	w4, 0
	mov	x3, 0
	mov	x2, 0
	mov	w1, w21
	mov	w0, w20
	bl	FlashDdrTunningRead
	mov	x3, 0
	mov	w22, w0
	mov	x2, 0
	mov	w0, w20
	mov	w1, w21
	adrp	x20, .LANCHOR30
	bl	FlashReadRawPage
	cmn	w0, #1
	beq	.L907
	cmn	w22, #1
	bne	.L908
.L907:
	ldrb	w0, [x19, #:lo12:.LANCHOR25]
	tbz	x0, 0, .L908
	mov	w0, 1
	bl	FlashSetInterfaceMode
	mov	w0, 1
	bl	NandcSetMode
	strb	wzr, [x20, #:lo12:.LANCHOR30]
.L909:
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
.L908:
	mov	w0, 1
	strb	w0, [x20, #:lo12:.LANCHOR30]
	b	.L909
	.size	FlashDdrParaScan, .-FlashDdrParaScan
	.section	.text.ToshibaReadRetrial,"ax",@progbits
	.align	2
	.global	ToshibaReadRetrial
	.type	ToshibaReadRetrial, %function
ToshibaReadRetrial:
	stp	x29, x30, [sp, -128]!
	add	x29, sp, 0
	stp	x21, x22, [sp, 32]
	and	w21, w0, 255
	stp	x25, x26, [sp, 64]
	mov	w0, w21
	stp	x19, x20, [sp, 16]
	mov	x25, x2
	stp	x27, x28, [sp, 80]
	mov	x26, x3
	str	w1, [x29, 120]
	stp	x23, x24, [sp, 48]
	bl	NandcWaitFlashReady
	sbfiz	x1, x21, 4, 32
	adrp	x0, .LANCHOR0
	add	x0, x0, :lo12:.LANCHOR0
	add	x2, x0, x1
	ldr	x22, [x0, x1]
	adrp	x1, .LANCHOR11
	ldrb	w27, [x2, 8]
	ldrb	w0, [x1, #:lo12:.LANCHOR11]
	str	x1, [x29, 112]
	add	x19, x27, 8
	sub	w0, w0, #67
	str	w27, [x29, 124]
	and	w0, w0, 255
	add	x19, x22, x19, lsl 8
	cmp	w0, 1
	bls	.L934
	adrp	x0, .LANCHOR30
	ldrb	w0, [x0, #:lo12:.LANCHOR30]
	cbz	w0, .L935
	mov	w23, 1
	mov	w0, 0
	bl	NandcSetDdrMode
.L919:
	add	x0, x22, x27, lsl 8
	mov	w1, 92
	str	w1, [x0, 2056]
	mov	w1, 197
	str	w1, [x0, 2056]
.L918:
	ldrsw	x0, [x29, 124]
	mov	w20, 1
	mov	w24, -1
	add	x0, x0, 8
	add	x0, x22, x0, lsl 8
	str	x0, [x29, 104]
.L920:
	adrp	x0, .LANCHOR149
	ldrb	w0, [x0, #:lo12:.LANCHOR149]
	add	w0, w0, 1
	cmp	w20, w0
	bcc	.L929
	mov	w28, w24
.L928:
	ldr	x0, [x29, 112]
	mov	w1, 0
	ldrb	w0, [x0, #:lo12:.LANCHOR11]
	sub	w0, w0, #67
	and	w0, w0, 255
	cmp	w0, 1
	mov	x0, x19
	bhi	.L930
	bl	SandiskSetRRPara
.L931:
	ldrsw	x0, [x29, 124]
	add	x0, x0, 8
	add	x22, x22, x0, lsl 8
	mov	w0, 255
	str	w0, [x22, 8]
	adrp	x0, .LANCHOR33
	ldrb	w0, [x0, #:lo12:.LANCHOR33]
	add	w0, w0, w0, lsl 1
	cmp	w28, w0, lsr 2
	bcc	.L932
	cmn	w28, #1
	mov	w0, 256
	csel	w28, w28, w0, eq
.L932:
	mov	w0, w21
	bl	NandcWaitFlashReady
	cbz	w23, .L917
	mov	w0, 4
	bl	NandcSetDdrMode
.L917:
	mov	w0, w28
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 128
	ret
.L935:
	mov	w23, 0
	b	.L919
.L934:
	mov	w23, 0
	b	.L918
.L929:
	ldr	x0, [x29, 112]
	mov	w1, w20
	ldrb	w0, [x0, #:lo12:.LANCHOR11]
	sub	w0, w0, #67
	and	w0, w0, 255
	cmp	w0, 1
	mov	x0, x19
	bhi	.L921
	bl	SandiskSetRRPara
.L922:
	ldr	x0, [x29, 112]
	ldrb	w0, [x0, #:lo12:.LANCHOR11]
	cmp	w0, 34
	bne	.L923
	adrp	x0, .LANCHOR149
	ldrb	w0, [x0, #:lo12:.LANCHOR149]
	sub	w0, w0, #3
	cmp	w20, w0
	bne	.L923
	ldr	x1, [x29, 104]
	mov	w0, 179
	str	w0, [x1, 8]
.L923:
	add	x0, x22, x27, lsl 8
	mov	w1, 38
	str	w1, [x0, 2056]
	mov	w1, 93
	str	w1, [x0, 2056]
	cbz	w23, .L924
	mov	w0, 4
	bl	NandcSetDdrMode
	ldr	w1, [x29, 120]
	mov	x3, x26
	mov	x2, x25
	mov	w0, w21
	bl	FlashReadRawPage
	mov	w28, w0
	mov	w0, 0
	bl	NandcSetDdrMode
.L925:
	cmn	w28, #1
	beq	.L926
	adrp	x0, .LANCHOR33
	cmn	w24, #1
	csel	w24, w24, w28, ne
	ldrb	w0, [x0, #:lo12:.LANCHOR33]
	add	w0, w0, w0, lsl 1
	cmp	w28, w0, lsr 2
	bcc	.L928
	mov	x26, 0
	mov	x25, 0
.L926:
	add	w20, w20, 1
	b	.L920
.L921:
	bl	ToshibaSetRRPara
	b	.L922
.L924:
	ldr	w1, [x29, 120]
	mov	x3, x26
	mov	x2, x25
	mov	w0, w21
	bl	FlashReadRawPage
	mov	w28, w0
	b	.L925
.L930:
	bl	ToshibaSetRRPara
	b	.L931
	.size	ToshibaReadRetrial, .-ToshibaReadRetrial
	.section	.text.SamsungReadRetrial,"ax",@progbits
	.align	2
	.global	SamsungReadRetrial
	.type	SamsungReadRetrial, %function
SamsungReadRetrial:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x21, x22, [sp, 32]
	and	w22, w0, 255
	stp	x19, x20, [sp, 16]
	mov	w0, w22
	stp	x23, x24, [sp, 48]
	mov	w23, w1
	stp	x25, x26, [sp, 64]
	mov	x24, x2
	str	x27, [sp, 80]
	mov	x25, x3
	bl	NandcWaitFlashReady
	adrp	x26, .LANCHOR149
	sbfiz	x1, x22, 4, 32
	adrp	x0, .LANCHOR0
	add	x0, x0, :lo12:.LANCHOR0
	adrp	x27, .LANCHOR33
	add	x2, x0, x1
	add	x26, x26, :lo12:.LANCHOR149
	add	x27, x27, :lo12:.LANCHOR33
	mov	w21, 1
	ldr	x0, [x0, x1]
	mov	w19, -1
	ldrb	w20, [x2, 8]
	add	x20, x20, 8
	add	x20, x0, x20, lsl 8
.L946:
	ldrb	w0, [x26]
	add	w0, w0, 1
	cmp	w21, w0
	bcc	.L950
.L949:
	mov	x0, x20
	mov	w1, 0
	bl	SamsungSetRRPara
	adrp	x0, .LANCHOR33
	ldrb	w0, [x0, #:lo12:.LANCHOR33]
	add	w0, w0, w0, lsl 1
	cmp	w19, w0, lsr 2
	bcc	.L945
	cmn	w19, #1
	mov	w0, 256
	csel	w19, w19, w0, eq
.L945:
	mov	w0, w19
	ldr	x27, [sp, 80]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 96
	ret
.L950:
	mov	w1, w21
	mov	x0, x20
	bl	SamsungSetRRPara
	mov	x3, x25
	mov	x2, x24
	mov	w1, w23
	mov	w0, w22
	bl	FlashReadRawPage
	cmn	w0, #1
	beq	.L947
	ldrb	w1, [x27]
	cmn	w19, #1
	csel	w19, w19, w0, ne
	add	w1, w1, w1, lsl 1
	cmp	w0, w1, lsr 2
	bcc	.L952
	mov	x25, 0
	mov	x24, 0
.L947:
	add	w21, w21, 1
	b	.L946
.L952:
	mov	w19, w0
	b	.L949
	.size	SamsungReadRetrial, .-SamsungReadRetrial
	.section	.text.MicronReadRetrial,"ax",@progbits
	.align	2
	.global	MicronReadRetrial
	.type	MicronReadRetrial, %function
MicronReadRetrial:
	stp	x29, x30, [sp, -144]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	and	w20, w0, 255
	adrp	x0, .LANCHOR33
	stp	x23, x24, [sp, 48]
	str	w1, [x29, 140]
	mov	x24, x2
	ldrb	w19, [x0, #:lo12:.LANCHOR33]
	adrp	x0, .LANCHOR16
	stp	x25, x26, [sp, 64]
	mov	x25, x3
	ldrb	w1, [x0, #:lo12:.LANCHOR16]
	stp	x21, x22, [sp, 32]
	stp	x27, x28, [sp, 80]
	str	x0, [x29, 128]
	cbnz	w1, .L960
	add	w19, w19, w19, lsl 1
	asr	w19, w19, 2
.L961:
	adrp	x21, .LANCHOR0
	add	x21, x21, :lo12:.LANCHOR0
	add	x21, x21, x20, sxtw 4
	mov	w23, 0
	mov	w28, 137
.L971:
	mov	w0, w20
	bl	NandcWaitFlashReady
	ldrb	w4, [x21, 8]
	adrp	x7, .LANCHOR149
	ldr	x8, [x21]
	add	x7, x7, :lo12:.LANCHOR149
	mov	w22, 0
	mov	w26, -1
	add	x27, x8, x4, lsl 8
.L962:
	ldrb	w0, [x7]
	cmp	w22, w0
	bcc	.L966
.L965:
	add	x4, x8, x4, lsl 8
	mov	w0, 239
	str	x4, [x29, 120]
	str	w0, [x4, 2056]
	mov	x0, 200
	str	w28, [x4, 2052]
	bl	udelay
	ldr	x4, [x29, 120]
	cmp	w26, w19
	str	wzr, [x4, 2048]
	str	wzr, [x4, 2048]
	str	wzr, [x4, 2048]
	str	wzr, [x4, 2048]
	bcc	.L967
	cmn	w26, #1
	mov	w0, 256
	csel	w26, w26, w0, eq
.L967:
	cmp	w26, 256
	ccmn	w26, #1, 4, ne
	bne	.L968
	ldr	w2, [x29, 140]
	adrp	x0, .LC13
	mov	w4, w26
	mov	w3, w22
	mov	w1, w22
	add	x0, x0, :lo12:.LC13
	bl	printf
	cbnz	w23, .L969
	ldr	x0, [x29, 128]
	ldrb	w0, [x0, #:lo12:.LANCHOR16]
	cbz	w0, .L959
	cmn	w26, #1
	bne	.L959
	mov	w1, 3
	mov	w0, w20
	mov	w23, 1
	bl	micron_auto_read_calibration_config
	b	.L971
.L960:
	mov	w0, 3
	sdiv	w19, w19, w0
	b	.L961
.L966:
	mov	w0, 239
	str	w0, [x27, 2056]
	str	w28, [x27, 2052]
	mov	x0, 200
	stp	x4, x7, [x29, 96]
	str	x8, [x29, 112]
	bl	udelay
	add	w10, w22, 1
	str	w10, [x27, 2048]
	str	wzr, [x27, 2048]
	mov	x3, x25
	ldr	w1, [x29, 140]
	mov	x2, x24
	str	wzr, [x27, 2048]
	mov	w0, w20
	str	wzr, [x27, 2048]
	str	w10, [x29, 120]
	bl	FlashReadRawPage
	cmn	w0, #1
	ldr	w10, [x29, 120]
	ldp	x4, x7, [x29, 96]
	ldr	x8, [x29, 112]
	beq	.L963
	cmn	w26, #1
	csel	w26, w26, w0, ne
	cmp	w0, w19
	bcc	.L973
	mov	x25, 0
	mov	x24, 0
.L963:
	mov	w22, w10
	b	.L962
.L973:
	mov	w26, w0
	mov	x25, 0
	mov	x24, 0
	b	.L965
.L969:
	mov	w0, w20
	mov	w1, 0
	bl	micron_auto_read_calibration_config
	cmn	w26, #1
	mov	w0, 256
	csel	w26, w26, w0, eq
.L959:
	mov	w0, w26
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 144
	ret
.L968:
	cbz	w23, .L959
	mov	w1, 0
	mov	w0, w20
	mov	w26, 256
	bl	micron_auto_read_calibration_config
	b	.L959
	.size	MicronReadRetrial, .-MicronReadRetrial
	.section	.text.HynixReadRetrial,"ax",@progbits
	.align	2
	.global	HynixReadRetrial
	.type	HynixReadRetrial, %function
HynixReadRetrial:
	stp	x29, x30, [sp, -128]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	adrp	x19, .LANCHOR20
	stp	x27, x28, [sp, 80]
	and	x28, x0, 255
	add	x0, x19, :lo12:.LANCHOR20
	stp	x23, x24, [sp, 48]
	stp	x21, x22, [sp, 32]
	mov	w22, w1
	stp	x25, x26, [sp, 64]
	adrp	x25, .LANCHOR7
	add	x1, x0, x28
	mov	x20, x28
	ldrb	w21, [x0, 2]
	mov	x23, x2
	ldr	x0, [x25, #:lo12:.LANCHOR7]
	mov	x24, x3
	ldrb	w26, [x1, 12]
	ldrb	w0, [x0, 19]
	sub	w0, w0, #7
	and	w0, w0, 255
	cmp	w0, 1
	bhi	.L985
	ldrb	w26, [x1, 20]
.L985:
	mov	w0, w20
	bl	NandcWaitFlashReady
	add	x6, x19, :lo12:.LANCHOR20
	adrp	x5, .LANCHOR33
	add	x7, x6, 4
	add	x5, x5, :lo12:.LANCHOR33
	mov	w4, 0
	mov	w27, -1
.L986:
	cmp	w4, w21
	bcc	.L991
.L990:
	ldr	x0, [x25, #:lo12:.LANCHOR7]
	add	x19, x19, :lo12:.LANCHOR20
	add	x19, x19, x28
	ldrb	w0, [x0, 19]
	sub	w0, w0, #7
	and	w0, w0, 255
	cmp	w0, 1
	bhi	.L992
	strb	w26, [x19, 20]
.L993:
	adrp	x0, .LANCHOR33
	ldrb	w0, [x0, #:lo12:.LANCHOR33]
	add	w0, w0, w0, lsl 1
	cmp	w27, w0, lsr 2
	bcc	.L984
	cmn	w27, #1
	mov	w0, 256
	csel	w27, w27, w0, eq
.L984:
	mov	w0, w27
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 128
	ret
.L991:
	add	w26, w26, 1
	ldrb	w1, [x6, 1]
	and	w26, w26, 255
	mov	x2, x7
	cmp	w21, w26
	str	x5, [x29, 96]
	csel	w26, w26, wzr, hi
	str	w4, [x29, 108]
	stp	x7, x6, [x29, 112]
	mov	w3, w26
	mov	w0, w20
	bl	HynixSetRRPara
	mov	x3, x24
	mov	x2, x23
	mov	w1, w22
	mov	w0, w20
	bl	FlashReadRawPage
	cmn	w0, #1
	ldr	w4, [x29, 108]
	ldr	x5, [x29, 96]
	ldp	x7, x6, [x29, 112]
	beq	.L988
	ldrb	w1, [x5]
	cmn	w27, #1
	csel	w27, w27, w0, ne
	add	w1, w1, w1, lsl 1
	cmp	w0, w1, lsr 2
	bcc	.L995
	mov	x24, 0
	mov	x23, 0
.L988:
	add	w4, w4, 1
	b	.L986
.L995:
	mov	w27, w0
	b	.L990
.L992:
	strb	w26, [x19, 12]
	b	.L993
	.size	HynixReadRetrial, .-HynixReadRetrial
	.section	.text.samsung_read_retrial,"ax",@progbits
	.align	2
	.type	samsung_read_retrial, %function
samsung_read_retrial:
	stp	x29, x30, [sp, -112]!
	add	x29, sp, 0
	stp	x21, x22, [sp, 32]
	and	w22, w0, 255
	stp	x23, x24, [sp, 48]
	mov	w0, w22
	stp	x19, x20, [sp, 16]
	mov	x23, x2
	stp	x25, x26, [sp, 64]
	mov	x24, x3
	mov	w25, w1
	stp	x27, x28, [sp, 80]
	bl	NandcWaitFlashReady
	sbfiz	x1, x22, 4, 32
	adrp	x0, .LANCHOR0
	add	x0, x0, :lo12:.LANCHOR0
	add	x2, x0, x1
	ldr	x0, [x0, x1]
	adrp	x1, .LANCHOR24
	ldrb	w19, [x2, 8]
	ldrb	w1, [x1, #:lo12:.LANCHOR24]
	cbnz	w1, .L1003
	adrp	x27, .LANCHOR150
	adrp	x28, .LANCHOR33
	add	x19, x0, x19, lsl 8
	add	x27, x27, :lo12:.LANCHOR150
	add	x28, x28, :lo12:.LANCHOR33
	mov	x21, 0
	mov	w20, -1
	mov	w4, 239
.L1007:
	str	w4, [x19, 2056]
	mov	w0, 141
	str	w0, [x19, 2052]
	add	x0, x27, x21
	str	w4, [x29, 108]
	mov	x3, x24
	mov	x2, x23
	mov	w1, w25
	ldrsb	w0, [x0, 1]
	add	w26, w21, 1
	str	w0, [x19, 2048]
	mov	w0, w22
	str	wzr, [x19, 2048]
	str	wzr, [x19, 2048]
	str	wzr, [x19, 2048]
	bl	FlashReadRawPage
	cmn	w0, #1
	ldr	w4, [x29, 108]
	beq	.L1004
	ldrb	w1, [x28]
	cmn	w20, #1
	csel	w20, w20, w0, ne
	add	w1, w1, w1, lsl 1
	cmp	w0, w1, lsr 2
	bcc	.L1015
	mov	x24, 0
	mov	x23, 0
.L1004:
	add	x21, x21, 1
	cmp	x21, 25
	bne	.L1007
	mov	w26, 26
.L1006:
	mov	w0, 239
	str	w0, [x19, 2056]
	mov	w0, 141
.L1031:
	str	w0, [x19, 2052]
	adrp	x0, .LANCHOR33
	str	wzr, [x19, 2048]
	str	wzr, [x19, 2048]
	str	wzr, [x19, 2048]
	str	wzr, [x19, 2048]
	ldrb	w0, [x0, #:lo12:.LANCHOR33]
	add	w0, w0, w0, lsl 1
	cmp	w20, w0, lsr 2
	bcc	.L1013
	cmn	w20, #1
	mov	w0, 256
	csel	w20, w20, w0, eq
.L1013:
	cmp	w20, 256
	ccmn	w20, #1, 4, ne
	bne	.L1014
	adrp	x0, .LC14
	mov	w4, w20
	mov	w3, w26
	mov	w2, w25
	mov	w1, w26
	add	x0, x0, :lo12:.LC14
	bl	printf
.L1014:
	mov	w0, w22
	bl	NandcWaitFlashReady
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
.L1015:
	mov	w20, w0
	b	.L1006
.L1003:
	adrp	x21, .LANCHOR151
	add	x21, x21, :lo12:.LANCHOR151
	adrp	x27, .LANCHOR33
	add	x21, x21, 4
	add	x19, x0, x19, lsl 8
	add	x27, x27, :lo12:.LANCHOR33
	mov	w20, -1
	mov	w26, 1
	mov	w4, 239
	mov	w28, 137
.L1012:
	str	w4, [x19, 2056]
	mov	x3, x24
	str	w28, [x19, 2052]
	mov	x2, x23
	str	w4, [x29, 108]
	mov	w1, w25
	ldrb	w0, [x21]
	str	w0, [x19, 2048]
	ldrb	w0, [x21, 1]
	str	w0, [x19, 2048]
	ldrb	w0, [x21, 2]
	str	w0, [x19, 2048]
	ldrb	w0, [x21, 3]
	str	w0, [x19, 2048]
	mov	w0, w22
	bl	FlashReadRawPage
	cmn	w0, #1
	ldr	w4, [x29, 108]
	beq	.L1009
	ldrb	w1, [x27]
	cmn	w20, #1
	csel	w20, w20, w0, ne
	add	w1, w1, w1, lsl 1
	cmp	w0, w1, lsr 2
	bcc	.L1016
	mov	x24, 0
	mov	x23, 0
.L1009:
	add	w26, w26, 1
	add	x21, x21, 4
	cmp	w26, 26
	bne	.L1012
.L1011:
	mov	w0, 239
	str	w0, [x19, 2056]
	mov	w0, 137
	b	.L1031
.L1016:
	mov	w20, w0
	b	.L1011
	.size	samsung_read_retrial, .-samsung_read_retrial
	.section	.text.FlashProgPage,"ax",@progbits
	.align	2
	.global	FlashProgPage
	.type	FlashProgPage, %function
FlashProgPage:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w20, w1
	stp	x21, x22, [sp, 32]
	adrp	x1, .LANCHOR31+9
	str	x23, [sp, 48]
	mov	x22, x2
	ldrb	w21, [x1, #:lo12:.LANCHOR31+9]
	ands	w19, w0, 255
	mov	x23, x3
	bne	.L1033
	adrp	x0, .LANCHOR3
	adrp	x1, .LANCHOR4
	ldrb	w0, [x0, #:lo12:.LANCHOR3]
	ldr	w1, [x1, #:lo12:.LANCHOR4]
	mul	w0, w0, w1
	cmp	w0, w20
	bls	.L1033
	adrp	x0, .LANCHOR2
	ldrb	w0, [x0, #:lo12:.LANCHOR2]
	cmp	w0, 0
	mov	w0, 4
	csel	w21, w21, w0, eq
.L1033:
	mov	w0, w19
	bl	NandcWaitFlashReady
	mov	w0, w19
	bl	NandcFlashCs
	mov	w1, w20
	mov	w0, w19
	bl	FlashProgFirstCmd
	mov	x4, x23
	mov	x3, x22
	mov	w2, w21
	mov	w1, 1
	mov	w0, w19
	bl	NandcXferData
	mov	w1, w20
	mov	w0, w19
	bl	FlashProgSecondCmd
	mov	w0, w19
	bl	NandcWaitFlashReady
	mov	w1, w20
	mov	w0, w19
	bl	FlashReadStatus
	mov	w2, w0
	mov	w0, w19
	bl	NandcFlashDeCs
	ldr	x23, [sp, 48]
	and	w0, w2, 1
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
	.size	FlashProgPage, .-FlashProgPage
	.section	.text.FlashPageProgMsbFFData,"ax",@progbits
	.align	2
	.global	FlashPageProgMsbFFData
	.type	FlashPageProgMsbFFData, %function
FlashPageProgMsbFFData:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x23, x24, [sp, 48]
	and	w23, w0, 255
	adrp	x0, .LANCHOR16
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	and	w19, w2, 65535
	ldrb	w0, [x0, #:lo12:.LANCHOR16]
	str	x25, [sp, 64]
	cbz	w0, .L1037
	adrp	x0, .LANCHOR29
	ldr	w0, [x0, #:lo12:.LANCHOR29]
	cbnz	w0, .L1036
.L1037:
	adrp	x2, .LANCHOR7
	mov	x20, x2
	ldr	x0, [x2, #:lo12:.LANCHOR7]
	ldrb	w0, [x0, 19]
	sub	w0, w0, #5
	and	w3, w0, 255
	cmp	w3, 63
	bhi	.L1036
	mov	x2, 16391
	movk	x2, 0x4000, lsl 16
	movk	x2, 0x2000, lsl 32
	movk	x2, 0x8000, lsl 48
	lsr	x0, x2, x3
	tbz	x0, 0, .L1036
	adrp	x21, .LANCHOR123
	mov	w22, w1
	add	x21, x21, :lo12:.LANCHOR123
	mov	w25, 65535
	adrp	x24, .LANCHOR152
.L1039:
	ldr	x0, [x20, #:lo12:.LANCHOR7]
	ldrh	w0, [x0, 10]
	cmp	w0, w19
	bhi	.L1040
.L1036:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldr	x25, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
.L1040:
	ldrh	w0, [x21, w19, sxtw 1]
	cmp	w0, w25
	bne	.L1036
	ldr	x0, [x24, #:lo12:.LANCHOR152]
	mov	w2, 32768
	mov	w1, 255
	bl	ftl_memset
	ldr	x3, [x24, #:lo12:.LANCHOR152]
	add	w1, w19, w22
	add	w19, w19, 1
	mov	w0, w23
	mov	x2, x3
	and	w19, w19, 65535
	bl	FlashProgPage
	b	.L1039
	.size	FlashPageProgMsbFFData, .-FlashPageProgMsbFFData
	.section	.text.FlashLoadPhyInfo,"ax",@progbits
	.align	2
	.global	FlashLoadPhyInfo
	.type	FlashLoadPhyInfo, %function
FlashLoadPhyInfo:
	stp	x29, x30, [sp, -128]!
	mov	w0, 60
	add	x29, sp, 0
	stp	x21, x22, [sp, 32]
	adrp	x21, .LANCHOR4
	adrp	x22, .LANCHOR154
	stp	x19, x20, [sp, 16]
	strb	w0, [x29, 120]
	mov	w0, 40
	strb	w0, [x29, 121]
	mov	w0, 24
	strb	w0, [x29, 122]
	mov	w0, 16
	strb	w0, [x29, 123]
	adrp	x20, .LANCHOR153
	ldr	w0, [x21, #:lo12:.LANCHOR4]
	mov	w19, 0
	stp	x23, x24, [sp, 48]
	adrp	x24, .LANCHOR155
	str	w0, [x29, 108]
	mov	w23, -1
	ldr	x0, [x22, #:lo12:.LANCHOR154]
	stp	x25, x26, [sp, 64]
	adrp	x25, .LANCHOR31
	str	x0, [x20, #:lo12:.LANCHOR153]
	mov	w26, 4
	stp	x27, x28, [sp, 80]
	add	x25, x25, :lo12:.LANCHOR31
	str	wzr, [x24, #:lo12:.LANCHOR155]
	mov	w0, 0
	bl	flash_enter_slc_mode
.L1046:
	add	w28, w19, 1
	mov	x27, 0
.L1048:
	add	x0, x29, 120
	ldrb	w0, [x0, x27]
	bl	FlashBchSel
	ldr	x2, [x22, #:lo12:.LANCHOR154]
	mov	x3, 0
	mov	w1, w19
	mov	w0, 0
	bl	FlashReadRawPage
	cmn	w0, #1
	bne	.L1047
	ldr	x2, [x22, #:lo12:.LANCHOR154]
	mov	x3, 0
	mov	w1, w28
	mov	w0, 0
	bl	FlashReadRawPage
	cmn	w0, #1
	bne	.L1047
	add	x27, x27, 1
	cmp	x27, 4
	bne	.L1048
.L1049:
	ldr	w0, [x29, 108]
	subs	w26, w26, #1
	add	w19, w19, w0
	bne	.L1046
	b	.L1054
.L1050:
	mov	w1, 2036
	add	x0, x6, 12
	bl	js_hash
	ldr	w1, [x6, 8]
	cmp	w1, w0
	bne	.L1056
	add	x1, x6, 160
	mov	w2, 32
	mov	x0, x25
	bl	ftl_memcpy
	ldr	x1, [x20, #:lo12:.LANCHOR153]
	mov	w2, 32
	adrp	x0, .LANCHOR8
	add	x0, x0, :lo12:.LANCHOR8
	add	x1, x1, 192
	bl	ftl_memcpy
	ldr	x1, [x20, #:lo12:.LANCHOR153]
	mov	w2, 852
	adrp	x0, .LANCHOR20
	add	x0, x0, :lo12:.LANCHOR20
	add	x1, x1, 224
	bl	ftl_memcpy
	ldrh	w0, [x25, 10]
	bl	FlashBlockAlignInit
	str	w19, [x24, #:lo12:.LANCHOR155]
	ldr	x1, [x20, #:lo12:.LANCHOR153]
	adrp	x0, .LANCHOR30
	ldr	w2, [x1, 1076]
	strb	w2, [x0, #:lo12:.LANCHOR30]
	ldr	w0, [x21, #:lo12:.LANCHOR4]
	adrp	x2, .LANCHOR156
	udiv	w0, w19, w0
	add	w0, w0, 1
	cmp	w0, 1
	bls	.L1052
.L1059:
	str	w0, [x2, #:lo12:.LANCHOR156]
	adrp	x0, .LANCHOR157
	ldrh	w1, [x1, 14]
	mov	w23, 0
	strb	w1, [x0, #:lo12:.LANCHOR157]
	b	.L1049
.L1052:
	mov	w0, 2
	b	.L1059
.L1056:
	mov	w23, -1
	b	.L1049
.L1047:
	ldr	x6, [x20, #:lo12:.LANCHOR153]
	mov	w1, 20036
	movk	w1, 0x4e41, lsl 16
	ldr	w0, [x6]
	cmp	w0, w1
	bne	.L1049
	cbnz	w23, .L1050
	ldr	w0, [x21, #:lo12:.LANCHOR4]
	udiv	w19, w19, w0
	adrp	x0, .LANCHOR156
	add	w19, w19, 1
	str	w19, [x0, #:lo12:.LANCHOR156]
.L1054:
	mov	w0, 0
	bl	flash_exit_slc_mode
	mov	w0, w23
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 128
	ret
	.size	FlashLoadPhyInfo, .-FlashLoadPhyInfo
	.section	.text.FlashSavePhyInfo,"ax",@progbits
	.align	2
	.global	FlashSavePhyInfo
	.type	FlashSavePhyInfo, %function
FlashSavePhyInfo:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x21, x22, [sp, 32]
	adrp	x21, .LANCHOR154
	stp	x19, x20, [sp, 16]
	adrp	x19, .LANCHOR153
	ldr	x0, [x21, #:lo12:.LANCHOR154]
	mov	w22, 0
	str	x0, [x19, #:lo12:.LANCHOR153]
	mov	w20, 0
	adrp	x0, .LANCHOR158
	stp	x23, x24, [sp, 48]
	stp	x27, x28, [sp, 80]
	adrp	x24, .LANCHOR152
	ldrb	w0, [x0, #:lo12:.LANCHOR158]
	adrp	x23, .LANCHOR4
	stp	x25, x26, [sp, 64]
	mov	w25, 20036
	movk	w25, 0x4e41, lsl 16
	adrp	x27, .LANCHOR16
	add	x28, x23, :lo12:.LANCHOR4
	add	x27, x27, :lo12:.LANCHOR16
	bl	FlashBchSel
	ldr	x0, [x21, #:lo12:.LANCHOR154]
	mov	w2, 2048
	mov	w1, 0
	bl	ftl_memset
	ldr	x0, [x19, #:lo12:.LANCHOR153]
	adrp	x1, .LANCHOR26
	mov	w2, 32
	add	x0, x0, 16
	str	w25, [x0, -16]
	ldrb	w1, [x1, #:lo12:.LANCHOR26]
	strh	w1, [x0, -4]
	adrp	x1, .LANCHOR3
	ldrb	w1, [x1, #:lo12:.LANCHOR3]
	strh	w1, [x0, -2]
	adrp	x1, .LANCHOR30
	ldrb	w1, [x1, #:lo12:.LANCHOR30]
	str	w1, [x0, 1060]
	adrp	x1, .LANCHOR22
	add	x1, x1, :lo12:.LANCHOR22
	bl	ftl_memcpy
	ldr	x0, [x19, #:lo12:.LANCHOR153]
	mov	w2, 8
	adrp	x1, .LANCHOR27
	add	x1, x1, :lo12:.LANCHOR27
	add	x0, x0, 80
	bl	ftl_memcpy
	ldr	x0, [x19, #:lo12:.LANCHOR153]
	mov	w2, 32
	adrp	x1, .LANCHOR18
	add	x1, x1, :lo12:.LANCHOR18
	add	x0, x0, 96
	bl	ftl_memcpy
	ldr	x0, [x19, #:lo12:.LANCHOR153]
	mov	w2, 32
	adrp	x1, .LANCHOR31
	add	x1, x1, :lo12:.LANCHOR31
	add	x0, x0, 160
	bl	ftl_memcpy
	ldr	x0, [x19, #:lo12:.LANCHOR153]
	mov	w2, 32
	adrp	x1, .LANCHOR8
	add	x1, x1, :lo12:.LANCHOR8
	add	x0, x0, 192
	bl	ftl_memcpy
	ldr	x0, [x19, #:lo12:.LANCHOR153]
	mov	w2, 852
	adrp	x1, .LANCHOR20
	add	x1, x1, :lo12:.LANCHOR20
	add	x0, x0, 224
	bl	ftl_memcpy
	ldr	x6, [x19, #:lo12:.LANCHOR153]
	mov	w1, 2036
	add	x0, x6, 12
	bl	js_hash
	str	w0, [x6, 8]
	mov	w0, 1592
	str	w0, [x6, 4]
	ldr	x0, [x24, #:lo12:.LANCHOR152]
	str	x0, [x19, #:lo12:.LANCHOR153]
	mov	w0, 0
	bl	flash_enter_slc_mode
.L1066:
	ldr	w1, [x23, #:lo12:.LANCHOR4]
	mov	w2, 0
	mov	w0, 0
	mul	w1, w20, w1
	bl	FlashEraseBlock
	ldrb	w0, [x27]
	cbz	w0, .L1061
	mov	w26, 0
.L1062:
	ldr	w1, [x28]
	mov	x3, 0
	ldr	x2, [x21, #:lo12:.LANCHOR154]
	mov	w0, 0
	madd	w1, w20, w1, w26
	add	w26, w26, 1
	bl	FlashProgPage
	cmp	w26, 10
	bne	.L1062
.L1063:
	ldr	w1, [x28]
	mov	x3, 0
	ldr	x2, [x24, #:lo12:.LANCHOR152]
	mov	w0, 0
	mul	w1, w20, w1
	bl	FlashReadRawPage
	cmn	w0, #1
	add	w7, w20, 1
	beq	.L1064
	ldr	x6, [x19, #:lo12:.LANCHOR153]
	ldr	w0, [x6]
	cmp	w0, w25
	bne	.L1064
	mov	w1, 2036
	add	x0, x6, 12
	bl	js_hash
	ldr	w1, [x6, 8]
	cmp	w1, w0
	bne	.L1064
	adrp	x0, .LANCHOR156
	cmp	w22, 1
	str	w7, [x0, #:lo12:.LANCHOR156]
	ldr	w0, [x28]
	mul	w20, w0, w20
	adrp	x0, .LANCHOR155
	str	w20, [x0, #:lo12:.LANCHOR155]
	beq	.L1067
	mov	w22, 1
.L1064:
	mov	w20, w7
	cmp	w7, 4
	bne	.L1066
.L1065:
	mov	w0, 0
	bl	flash_exit_slc_mode
	cmp	w22, 0
	csetm	w0, eq
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 96
	ret
.L1061:
	ldr	w1, [x23, #:lo12:.LANCHOR4]
	mov	x3, 0
	ldr	x2, [x21, #:lo12:.LANCHOR154]
	mov	w0, 0
	mul	w1, w20, w1
	bl	FlashProgPage
	ldr	w1, [x23, #:lo12:.LANCHOR4]
	mov	x3, 0
	ldr	x2, [x21, #:lo12:.LANCHOR154]
	mov	w0, 0
	mul	w1, w20, w1
	add	w1, w1, 1
	bl	FlashProgPage
	b	.L1063
.L1067:
	mov	w22, 2
	b	.L1065
	.size	FlashSavePhyInfo, .-FlashSavePhyInfo
	.section	.text.FlashReadIdbDataRaw,"ax",@progbits
	.align	2
	.global	FlashReadIdbDataRaw
	.type	FlashReadIdbDataRaw, %function
FlashReadIdbDataRaw:
	stp	x29, x30, [sp, -144]!
	add	x29, sp, 0
	stp	x23, x24, [sp, 48]
	mov	x23, x0
	mov	w0, 60
	stp	x25, x26, [sp, 64]
	strb	w0, [x29, 136]
	mov	w0, 40
	strb	w0, [x29, 137]
	mov	w0, 24
	strb	w0, [x29, 138]
	mov	w0, 16
	strb	w0, [x29, 139]
	adrp	x0, .LANCHOR33
	stp	x19, x20, [sp, 16]
	ldrb	w26, [x0, #:lo12:.LANCHOR33]
	adrp	x0, .LANCHOR29
	stp	x21, x22, [sp, 32]
	ldr	w1, [x0, #:lo12:.LANCHOR29]
	stp	x27, x28, [sp, 80]
	str	x0, [x29, 120]
	cbz	w1, .L1075
	mov	w0, 0
	bl	flash_enter_slc_mode
.L1075:
	adrp	x24, .LANCHOR3
	adrp	x22, .LANCHOR4
	add	x27, x29, 136
	add	x22, x22, :lo12:.LANCHOR4
	add	x28, x24, :lo12:.LANCHOR3
	mov	w20, -1
	mov	w19, 2
	mov	w2, 2048
	mov	w1, 0
	mov	x0, x23
	bl	ftl_memset
.L1076:
	ldrb	w0, [x24, #:lo12:.LANCHOR3]
	cmp	w19, w0
	bcc	.L1081
.L1080:
	mov	w0, w26
	bl	FlashBchSel
	ldr	x0, [x29, 120]
	ldr	w0, [x0, #:lo12:.LANCHOR29]
	cbz	w0, .L1074
	mov	w0, 0
	bl	flash_exit_slc_mode
.L1074:
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 144
	ret
.L1081:
	mov	x4, 0
	adrp	x25, .LANCHOR154
.L1078:
	ldrb	w5, [x4, x27]
	add	x21, x25, :lo12:.LANCHOR154
	str	w5, [x29, 116]
	mov	w0, w5
	str	x4, [x29, 104]
	bl	FlashBchSel
	ldr	w1, [x22]
	mov	x3, 0
	ldr	x2, [x25, #:lo12:.LANCHOR154]
	mov	w0, 0
	mul	w1, w19, w1
	bl	FlashReadRawPage
	cmn	w0, #1
	ldr	w5, [x29, 116]
	bne	.L1077
	ldr	x4, [x29, 104]
	add	x4, x4, 1
	cmp	x4, 4
	bne	.L1078
.L1079:
	add	w19, w19, 1
	b	.L1076
.L1084:
	mov	w20, 0
	b	.L1080
.L1077:
	ldr	x0, [x21]
	ldr	w1, [x0]
	mov	w0, 35899
	movk	w0, 0xfcdc, lsl 16
	cmp	w1, w0
	bne	.L1079
	mov	w1, w5
	adrp	x0, .LC15
	add	x0, x0, :lo12:.LC15
	bl	printf
	ldr	x1, [x21]
	mov	w2, 2048
	mov	x0, x23
	bl	ftl_memcpy
	ldr	x0, [x21]
	ldr	w0, [x0, 512]
	strb	w0, [x28]
	adrp	x0, .LANCHOR156
	ldr	w1, [x0, #:lo12:.LANCHOR156]
	cmp	w19, w1
	bcs	.L1084
	str	w19, [x0, #:lo12:.LANCHOR156]
	mov	w20, 0
	bl	FlashSavePhyInfo
	b	.L1079
	.size	FlashReadIdbDataRaw, .-FlashReadIdbDataRaw
	.section	.text.idb_write_data,"ax",@progbits
	.align	2
	.global	idb_write_data
	.type	idb_write_data, %function
idb_write_data:
	stp	x29, x30, [sp, -240]!
	add	w0, w1, w3
	mov	w4, w1
	cmp	w0, 63
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	bls	.L1094
	cmp	w1, 575
	bhi	.L1095
	adrp	x0, .LANCHOR159
	mov	x1, x2
	mov	w2, 1
	cmp	w4, 64
	str	w2, [x0, #:lo12:.LANCHOR159]
	adrp	x0, idb_buf
	bhi	.L1096
	mov	w2, 64
	sub	w4, w2, w4
	sub	w2, w3, w4
	ubfiz	x4, x4, 9, 25
	lsl	w2, w2, 9
	add	x1, x1, x4
	add	x0, x0, :lo12:idb_buf
.L1146:
	bl	ftl_memcpy
.L1129:
	ldp	x19, x20, [sp, 16]
	mov	w0, 0
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 240
	ret
.L1096:
	mov	w2, 576
	sub	w2, w2, w4
	cmp	w3, w2
	sub	w4, w4, #64
	csel	w2, w3, w2, ls
	ubfiz	x4, x4, 9, 25
	add	x0, x0, :lo12:idb_buf
	lsl	w2, w2, 9
	add	x0, x0, x4
	b	.L1146
.L1094:
	cmp	w1, 575
	bls	.L1129
.L1095:
	adrp	x0, .LANCHOR159
	str	x0, [x29, 104]
	ldr	w1, [x0, #:lo12:.LANCHOR159]
	cbz	w1, .L1129
	adrp	x21, .LANCHOR7
	adrp	x1, idb_buf+262140
	adrp	x25, idb_buf
	add	x1, x1, :lo12:idb_buf+262140
	ldr	x0, [x21, #:lo12:.LANCHOR7]
	add	x5, x25, :lo12:idb_buf
	mov	w2, 65535
	mov	w3, 4097
	ldrb	w20, [x0, 9]
	ldrh	w0, [x0, 10]
	mul	w20, w20, w0
	and	w20, w20, 65535
	add	w0, w20, 511
	udiv	w0, w0, w20
	str	w0, [x29, 172]
	mov	w0, 0
.L1100:
	ldr	w4, [x1]
	cbnz	w4, .L1098
	ldr	w4, [x5, w0, uxtw 2]
	add	w0, w0, 1
	str	w4, [x1], -4
	cmp	w0, w3
	sub	w2, w2, #1
	csel	w0, w0, wzr, cc
	cmp	w2, 4096
	bne	.L1100
.L1098:
	add	x0, x25, :lo12:idb_buf
	mov	w3, 512
	mov	w23, 0
	ldr	w1, [x0, w2, uxtw 2]
	adrp	x0, .LC16
	add	x0, x0, :lo12:.LC16
	bl	printf
	adrp	x0, .LANCHOR156
	ldr	w24, [x0, #:lo12:.LANCHOR156]
	ldr	w0, [x29, 172]
	mul	w19, w20, w24
	mul	w0, w20, w0
	str	w0, [x29, 136]
	adrp	x0, .LANCHOR17
	add	x0, x0, :lo12:.LANCHOR17
	str	x0, [x29, 160]
.L1101:
	cmp	w24, 15
	bls	.L1119
	cbnz	w23, .L1121
	adrp	x0, .LC18
	mov	w1, 0
	add	x0, x0, :lo12:.LC18
	bl	printf
.L1121:
	ldr	x0, [x29, 104]
	str	wzr, [x0, #:lo12:.LANCHOR159]
	b	.L1129
.L1119:
	adrp	x27, gp_flash_check_buf
	mov	x2, 512
	mov	w1, 0
	add	x0, x27, :lo12:gp_flash_check_buf
	bl	memset
	ldr	x0, [x21, #:lo12:.LANCHOR7]
	ldrb	w22, [x0, 9]
	ldrh	w26, [x0, 10]
	mov	w0, w19
	bl	FW_FlashBlockErase.constprop.42
	str	x27, [x29, 128]
	mul	w26, w22, w26
	and	w26, w26, 65535
	cmp	w26, 511
	bhi	.L1102
	add	w0, w26, w19
	bl	FW_FlashBlockErase.constprop.42
.L1102:
	udiv	w4, w19, w26
	adrp	x5, .LANCHOR16
	add	x5, x5, :lo12:.LANCHOR16
	mov	x28, 0
	msub	w4, w4, w26, w19
	sub	w26, w19, w4
.L1103:
	add	x2, x25, :lo12:idb_buf
	cmp	x28, 128
	add	x2, x2, x28, lsl 11
	bne	.L1107
	ldr	x0, [x21, #:lo12:.LANCHOR7]
	mov	w26, 0
	ldr	x1, [x29, 128]
	add	x27, x1, :lo12:gp_flash_check_buf
	adrp	x1, .LANCHOR16
	ldrb	w28, [x0, 9]
	add	x1, x1, :lo12:.LANCHOR16
	ldrh	w22, [x0, 10]
	str	x1, [x29, 96]
	mul	w22, w28, w22
	and	w0, w22, 65535
	udiv	w22, w19, w0
	msub	w22, w22, w0, w19
	sub	w0, w19, w22
	str	w0, [x29, 120]
	mul	w0, w22, w28
	ubfx	x0, x0, 2, 2
.L1108:
	cmp	w26, 511
	bhi	.L1115
	ldr	x3, [x29, 96]
	mov	w1, 4
	sub	w1, w1, w0
	ldr	x2, [x29, 160]
	and	w1, w1, 65535
	str	w1, [x29, 144]
	add	w1, w22, w26
	ldrb	w3, [x3]
	lsr	w1, w1, 2
	ldrh	w2, [x2, w1, sxtw 1]
	cbz	w3, .L1109
	adrp	x3, .LANCHOR122
	mov	w4, 12336
	movk	w4, 0x5638, lsl 16
	ldr	w3, [x3, #:lo12:.LANCHOR122]
	cmp	w3, w4
	csel	w2, w2, w1, ne
.L1109:
	ldr	w1, [x29, 120]
	add	w0, w0, w1
	adrp	x1, .LANCHOR4
	ldr	w1, [x1, #:lo12:.LANCHOR4]
	madd	w0, w28, w2, w0
	str	w0, [x29, 168]
	adrp	x0, .LANCHOR33
	ldrb	w0, [x0, #:lo12:.LANCHOR33]
	str	w0, [x29, 112]
	ldr	x0, [x21, #:lo12:.LANCHOR7]
	ldrb	w0, [x0, 9]
	str	w0, [x29, 140]
	adrp	x0, .LANCHOR15+26
	ldrh	w0, [x0, #:lo12:.LANCHOR15+26]
	mul	w0, w0, w1
	ldr	w1, [x29, 140]
	mul	w0, w0, w1
	ldr	w1, [x29, 168]
	cmp	w1, w0
	bcs	.L1110
	adrp	x0, .LANCHOR158
	ldrb	w0, [x0, #:lo12:.LANCHOR158]
	bl	FlashBchSel
.L1110:
	mov	w0, 0
	bl	flash_boot_enter_slc_mode
	ldr	w0, [x29, 168]
	add	x3, x29, 176
	ldr	w1, [x29, 140]
	mov	x2, x27
	udiv	w1, w0, w1
	mov	w0, 0
	str	w1, [x29, 168]
	bl	FlashReadPage
	mov	w1, w0
	cmn	w0, #1
	bne	.L1111
	adrp	x0, .LANCHOR158
	ldrb	w0, [x0, #:lo12:.LANCHOR158]
	cmp	w0, 40
	beq	.L1111
	mov	w0, 40
	bl	FlashBchSel
	ldr	w1, [x29, 168]
	add	x3, x29, 176
	mov	x2, x27
	mov	w0, 0
	bl	FlashReadPage
	mov	w1, w0
.L1111:
	str	w1, [x29, 168]
	mov	w0, 0
	bl	flash_boot_exit_slc_mode
	ldrb	w0, [x29, 112]
	bl	FlashBchSel
	ldr	w1, [x29, 168]
	cmn	w1, #1
	bne	.L1112
.L1115:
	ldr	x0, [x29, 128]
	add	x1, x25, :lo12:idb_buf
	mov	x22, 0
	add	x26, x0, :lo12:gp_flash_check_buf
.L1113:
	lsl	x0, x22, 2
	mov	w27, w22
	add	x28, x0, x1
	ldr	w2, [x0, x26]
	ldr	w0, [x0, x1]
	cmp	w2, w0
	beq	.L1116
	mov	x2, 512
	mov	w1, 0
	mov	x0, x26
	bl	memset
	ldr	w2, [x26, w27, uxtw 2]
	mov	w4, w22
	ldr	w3, [x28]
	mov	w1, w19
	adrp	x0, .LC17
	add	x0, x0, :lo12:.LC17
	bl	printf
	mov	w0, w19
	bl	FW_FlashBlockErase.constprop.42
	ldr	w0, [x29, 172]
	cmp	w0, 1
	bls	.L1117
	add	w0, w20, w19
	bl	FW_FlashBlockErase.constprop.42
.L1117:
	ldr	w0, [x29, 172]
	add	w24, w24, w0
	ldr	w0, [x29, 136]
	add	w19, w19, w0
	b	.L1101
.L1107:
	add	w1, w4, w28, lsl 2
	lsr	w1, w1, 2
	cbz	w1, .L1104
	ldr	x0, [x29, 160]
	add	w3, w1, 1
	ldrb	w6, [x5]
	ldrh	w0, [x0, w3, sxtw 1]
	cbz	w6, .L1105
	adrp	x6, .LANCHOR122
	mov	w7, 12336
	movk	w7, 0x5638, lsl 16
	ldr	w6, [x6, #:lo12:.LANCHOR122]
	cmp	w6, w7
	csel	w0, w0, w3, ne
.L1105:
	lsl	w0, w0, 2
	sub	w0, w0, #4
	str	w0, [x29, 176]
.L1104:
	mov	w0, 61424
	str	w0, [x29, 180]
	ldr	x0, [x29, 160]
	ldrh	w27, [x0, w1, sxtw 1]
	ldrb	w0, [x5]
	cbz	w0, .L1106
	adrp	x0, .LANCHOR122
	mov	w3, 12336
	movk	w3, 0x5638, lsl 16
	ldr	w0, [x0, #:lo12:.LANCHOR122]
	cmp	w0, w3
	csel	w27, w27, w1, ne
.L1106:
	adrp	x0, .LANCHOR33
	madd	w1, w22, w27, w26
	stp	x5, x2, [x29, 112]
	add	x28, x28, 1
	ldrb	w6, [x0, #:lo12:.LANCHOR33]
	adrp	x0, .LANCHOR158
	stp	w4, w6, [x29, 140]
	ldrb	w0, [x0, #:lo12:.LANCHOR158]
	str	w1, [x29, 168]
	bl	FlashBchSel
	mov	w0, 0
	bl	flash_boot_enter_slc_mode
	ldr	x0, [x21, #:lo12:.LANCHOR7]
	add	x3, x29, 176
	ldr	w1, [x29, 168]
	ldr	x2, [x29, 120]
	ldrb	w0, [x0, 9]
	udiv	w1, w1, w0
	mov	w0, 0
	bl	FlashProgPage
	mov	w0, 0
	bl	flash_boot_exit_slc_mode
	ldr	w6, [x29, 144]
	mov	w0, w6
	bl	FlashBchSel
	udiv	w1, w26, w22
	add	w2, w27, 1
	mov	w0, 0
	bl	FlashPageProgMsbFFData
	ldr	w4, [x29, 140]
	ldr	x5, [x29, 112]
	b	.L1103
.L1112:
	ldr	x0, [x29, 144]
	ubfiz	x0, x0, 9, 16
	add	x27, x27, x0
	ldr	w0, [x29, 144]
	add	w26, w0, w26
	mov	w0, 0
	and	w26, w26, 65535
	b	.L1108
.L1116:
	add	x22, x22, 1
	cmp	x22, 65536
	bne	.L1113
	add	w23, w23, 1
	cmp	w23, 5
	bls	.L1117
	b	.L1121
	.size	idb_write_data, .-idb_write_data
	.section	.text.ftl_memcpy32,"ax",@progbits
	.align	2
	.global	ftl_memcpy32
	.type	ftl_memcpy32, %function
ftl_memcpy32:
	mov	x3, 0
.L1148:
	cmp	w2, w3
	bhi	.L1149
	ret
.L1149:
	ldr	w4, [x1, x3, lsl 2]
	str	w4, [x0, x3, lsl 2]
	add	x3, x3, 1
	b	.L1148
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
	.section	.text.NandcInit,"ax",@progbits
	.align	2
	.global	NandcInit
	.type	NandcInit, %function
NandcInit:
	stp	x29, x30, [sp, -16]!
	adrp	x2, .LANCHOR0
	add	x1, x2, :lo12:.LANCHOR0
	adrp	x4, .LANCHOR122
	add	x29, sp, 0
	str	x0, [x2, #:lo12:.LANCHOR0]
	mov	w2, 1
	str	w2, [x1, 24]
	mov	w2, 2
	str	wzr, [x1, 8]
	str	w2, [x1, 40]
	mov	w2, 3
	str	x0, [x1, 16]
	str	w2, [x1, 56]
	adrp	x2, .LANCHOR160
	str	x0, [x1, 32]
	str	x0, [x1, 48]
	adrp	x1, .LANCHOR19
	str	x0, [x1, #:lo12:.LANCHOR19]
	ldr	w1, [x0]
	ubfx	x3, x1, 13, 1
	str	w3, [x2, #:lo12:.LANCHOR160]
	ldr	w2, [x0, 352]
	adrp	x3, .LANCHOR34
	and	w1, w1, 245760
	orr	w1, w1, 256
	ubfx	x2, x2, 16, 4
	str	w2, [x3, #:lo12:.LANCHOR34]
	ldr	w2, [x0, 352]
	str	w2, [x4, #:lo12:.LANCHOR122]
	cmp	w2, 2049
	bne	.L1154
	mov	w2, 8
	str	w2, [x3, #:lo12:.LANCHOR34]
.L1154:
	str	w1, [x0]
	mov	w1, 4225
	str	wzr, [x0, 336]
	str	w1, [x0, 4]
	mov	w1, 8322
	str	w1, [x0, 344]
	mov	w1, 6657
	movk	w1, 0x1a, lsl 16
	str	w1, [x0, 304]
	mov	w0, 36864
	bl	ftl_malloc
	adrp	x1, .LANCHOR161
	adrp	x2, .LANCHOR35
	str	x0, [x1, #:lo12:.LANCHOR161]
	add	x1, x2, :lo12:.LANCHOR35
	str	x0, [x2, #:lo12:.LANCHOR35]
	add	x0, x0, 32768
	str	wzr, [x1, 40]
	str	x0, [x1, 8]
	adrp	x0, .LANCHOR36
	ldp	x29, x30, [sp], 16
	str	wzr, [x0, #:lo12:.LANCHOR36]
	ret
	.size	NandcInit, .-NandcInit
	.section	.text.FtlMemInit,"ax",@progbits
	.align	2
	.global	FtlMemInit
	.type	FtlMemInit, %function
FtlMemInit:
	stp	x29, x30, [sp, -64]!
	adrp	x0, .LANCHOR142
	mov	w1, 65535
	add	x29, sp, 0
	strh	wzr, [x0, #:lo12:.LANCHOR142]
	adrp	x0, .LANCHOR162
	stp	x19, x20, [sp, 16]
	adrp	x19, .LANCHOR185
	str	wzr, [x0, #:lo12:.LANCHOR162]
	adrp	x0, .LANCHOR163
	stp	x21, x22, [sp, 32]
	adrp	x21, .LANCHOR38
	str	wzr, [x0, #:lo12:.LANCHOR163]
	adrp	x0, .LANCHOR164
	stp	x23, x24, [sp, 48]
	str	wzr, [x0, #:lo12:.LANCHOR164]
	adrp	x0, .LANCHOR165
	str	wzr, [x0, #:lo12:.LANCHOR165]
	adrp	x0, .LANCHOR166
	str	wzr, [x0, #:lo12:.LANCHOR166]
	adrp	x0, .LANCHOR167
	str	wzr, [x0, #:lo12:.LANCHOR167]
	adrp	x0, .LANCHOR168
	str	wzr, [x0, #:lo12:.LANCHOR168]
	adrp	x0, .LANCHOR169
	str	wzr, [x0, #:lo12:.LANCHOR169]
	adrp	x0, .LANCHOR170
	str	wzr, [x0, #:lo12:.LANCHOR170]
	adrp	x0, .LANCHOR171
	str	wzr, [x0, #:lo12:.LANCHOR171]
	adrp	x0, .LANCHOR172
	str	wzr, [x0, #:lo12:.LANCHOR172]
	adrp	x0, .LANCHOR173
	str	wzr, [x0, #:lo12:.LANCHOR173]
	adrp	x0, .LANCHOR81
	str	wzr, [x0, #:lo12:.LANCHOR81]
	adrp	x0, .LANCHOR174
	str	wzr, [x0, #:lo12:.LANCHOR174]
	adrp	x0, .LANCHOR175
	str	wzr, [x0, #:lo12:.LANCHOR175]
	adrp	x0, .LANCHOR176
	str	wzr, [x0, #:lo12:.LANCHOR176]
	adrp	x0, .LANCHOR177
	str	wzr, [x0, #:lo12:.LANCHOR177]
	adrp	x0, .LANCHOR178
	str	w1, [x0, #:lo12:.LANCHOR178]
	adrp	x0, .LANCHOR179
	adrp	x1, .LANCHOR115
	str	wzr, [x0, #:lo12:.LANCHOR179]
	adrp	x0, .LANCHOR180
	str	wzr, [x0, #:lo12:.LANCHOR180]
	adrp	x0, .LANCHOR75
	str	wzr, [x0, #:lo12:.LANCHOR75]
	mov	w0, -1
	strh	w0, [x1, #:lo12:.LANCHOR115]
	adrp	x1, .LANCHOR116
	strh	w0, [x1, #:lo12:.LANCHOR116]
	adrp	x1, .LANCHOR117
	strh	w0, [x1, #:lo12:.LANCHOR117]
	adrp	x1, .LANCHOR118
	strh	w0, [x1, #:lo12:.LANCHOR118]
	adrp	x0, .LANCHOR181
	mov	w1, 32
	strh	w1, [x0, #:lo12:.LANCHOR181]
	adrp	x0, .LANCHOR182
	mov	w1, 128
	strh	w1, [x0, #:lo12:.LANCHOR182]
	adrp	x0, .LANCHOR183
	mov	w1, 128
	strh	wzr, [x0, #:lo12:.LANCHOR183]
	adrp	x0, .LANCHOR119
	strh	wzr, [x0, #:lo12:.LANCHOR119]
	adrp	x0, .LANCHOR184
	strh	wzr, [x0, #:lo12:.LANCHOR184]
	adrp	x0, .LANCHOR121
	strh	wzr, [x0, #:lo12:.LANCHOR121]
	adrp	x0, .LANCHOR55
	ldrh	w0, [x0, #:lo12:.LANCHOR55]
	sdiv	w1, w1, w0
	ldrh	w0, [x21, #:lo12:.LANCHOR38]
	lsl	w0, w0, 2
	str	w1, [x19, #:lo12:.LANCHOR185]
	cmp	w1, w0
	bls	.L1157
	str	w0, [x19, #:lo12:.LANCHOR185]
.L1157:
	adrp	x20, .LANCHOR54
	adrp	x0, .LANCHOR72
	mov	w22, 56
	adrp	x24, .LANCHOR58
	str	wzr, [x0, #:lo12:.LANCHOR72]
	ldrh	w0, [x20, #:lo12:.LANCHOR54]
	lsl	w0, w0, 1
	bl	ftl_malloc
	adrp	x1, .LANCHOR112
	str	x0, [x1, #:lo12:.LANCHOR112]
	mov	w0, 12
	ldrh	w1, [x20, #:lo12:.LANCHOR54]
	mul	w0, w1, w0
	bl	ftl_malloc
	ldrh	w20, [x21, #:lo12:.LANCHOR38]
	adrp	x1, .LANCHOR114
	str	x0, [x1, #:lo12:.LANCHOR114]
	mul	w20, w20, w22
	lsl	w23, w20, 2
	mov	w0, w23
	bl	ftl_malloc
	adrp	x1, .LANCHOR186
	str	x0, [x1, #:lo12:.LANCHOR186]
	mov	w0, w20
	bl	ftl_malloc
	adrp	x1, .LANCHOR187
	str	x0, [x1, #:lo12:.LANCHOR187]
	mov	w0, w23
	bl	ftl_malloc
	adrp	x23, .LANCHOR57
	adrp	x1, .LANCHOR188
	str	x0, [x1, #:lo12:.LANCHOR188]
	mov	w0, w20
	bl	ftl_malloc
	adrp	x1, .LANCHOR79
	str	x0, [x1, #:lo12:.LANCHOR79]
	mov	w0, w20
	bl	ftl_malloc
	adrp	x1, .LANCHOR109
	str	x0, [x1, #:lo12:.LANCHOR109]
	ldr	w0, [x19, #:lo12:.LANCHOR185]
	mul	w0, w0, w22
	adrp	x22, .LANCHOR110
	bl	ftl_malloc
	ldrh	w20, [x23, #:lo12:.LANCHOR57]
	adrp	x1, .LANCHOR73
	str	x0, [x1, #:lo12:.LANCHOR73]
	ldrh	w0, [x21, #:lo12:.LANCHOR38]
	lsl	w0, w0, 1
	add	w0, w0, 1
	str	w0, [x22, #:lo12:.LANCHOR110]
	mov	w0, w20
	bl	ftl_malloc
	adrp	x1, .LANCHOR189
	str	x0, [x1, #:lo12:.LANCHOR189]
	mov	w0, w20
	bl	ftl_malloc
	adrp	x1, .LANCHOR190
	str	x0, [x1, #:lo12:.LANCHOR190]
	mov	w0, w20
	bl	ftl_malloc
	adrp	x1, .LANCHOR191
	str	x0, [x1, #:lo12:.LANCHOR191]
	ldr	w0, [x22, #:lo12:.LANCHOR110]
	mul	w0, w20, w0
	bl	ftl_malloc
	adrp	x1, .LANCHOR107
	str	x0, [x1, #:lo12:.LANCHOR107]
	ldr	w0, [x19, #:lo12:.LANCHOR185]
	mul	w0, w20, w0
	bl	ftl_malloc
	adrp	x1, .LANCHOR192
	str	x0, [x1, #:lo12:.LANCHOR192]
	mov	w0, w20
	bl	ftl_malloc
	adrp	x1, .LANCHOR193
	str	x0, [x1, #:lo12:.LANCHOR193]
	mov	w0, w20
	bl	ftl_malloc
	adrp	x1, .LANCHOR194
	str	x0, [x1, #:lo12:.LANCHOR194]
	mov	w0, 24
	ldr	w1, [x22, #:lo12:.LANCHOR110]
	mul	w0, w1, w0
	bl	ftl_malloc
	ldrh	w20, [x24, #:lo12:.LANCHOR58]
	adrp	x1, .LANCHOR106
	str	x0, [x1, #:lo12:.LANCHOR106]
	ldrh	w0, [x21, #:lo12:.LANCHOR38]
	adrp	x21, .LANCHOR64
	mul	w20, w20, w0
	mov	w0, w20
	bl	ftl_malloc
	adrp	x1, .LANCHOR195
	str	x0, [x1, #:lo12:.LANCHOR195]
	lsl	w0, w20, 2
	bl	ftl_malloc
	adrp	x20, .LANCHOR41
	adrp	x1, .LANCHOR196
	str	x0, [x1, #:lo12:.LANCHOR196]
	ldrh	w1, [x24, #:lo12:.LANCHOR58]
	ldr	w0, [x22, #:lo12:.LANCHOR110]
	mul	w0, w1, w0
	bl	ftl_malloc
	adrp	x1, .LANCHOR108
	str	x0, [x1, #:lo12:.LANCHOR108]
	ldrh	w1, [x24, #:lo12:.LANCHOR58]
	ldr	w0, [x19, #:lo12:.LANCHOR185]
	adrp	x19, .LANCHOR198
	mul	w0, w1, w0
	bl	ftl_malloc
	adrp	x1, .LANCHOR197
	str	x0, [x1, #:lo12:.LANCHOR197]
	ldrh	w0, [x20, #:lo12:.LANCHOR41]
	ubfiz	w0, w0, 1, 15
	strh	w0, [x19, #:lo12:.LANCHOR198]
	and	w0, w0, 65534
	bl	ftl_malloc
	adrp	x1, .LANCHOR140
	str	x0, [x1, #:lo12:.LANCHOR140]
	ldrh	w0, [x19, #:lo12:.LANCHOR198]
	add	x0, x0, 547
	lsr	x0, x0, 9
	strh	w0, [x19, #:lo12:.LANCHOR198]
	lsl	w0, w0, 9
	bl	ftl_malloc
	adrp	x1, .LANCHOR199
	str	x0, [x1, #:lo12:.LANCHOR199]
	adrp	x1, .LANCHOR80
	add	x0, x0, 32
	str	x0, [x1, #:lo12:.LANCHOR80]
	ldrh	w0, [x20, #:lo12:.LANCHOR41]
	lsl	w0, w0, 1
	bl	ftl_malloc
	ldr	w19, [x21, #:lo12:.LANCHOR64]
	adrp	x1, .LANCHOR85
	str	x0, [x1, #:lo12:.LANCHOR85]
	lsl	w19, w19, 1
	mov	w0, w19
	bl	ftl_malloc
	adrp	x1, .LANCHOR132
	str	x0, [x1, #:lo12:.LANCHOR132]
	mov	w0, w19
	bl	ftl_malloc
	adrp	x19, .LANCHOR61
	adrp	x1, .LANCHOR128
	str	x0, [x1, #:lo12:.LANCHOR128]
	ldrh	w0, [x20, #:lo12:.LANCHOR41]
	lsr	w0, w0, 3
	add	w0, w0, 4
	bl	ftl_malloc
	adrp	x1, .LANCHOR1
	str	x0, [x1, #:lo12:.LANCHOR1]
	ldrh	w0, [x19, #:lo12:.LANCHOR61]
	lsl	w0, w0, 1
	bl	ftl_malloc
	adrp	x1, .LANCHOR71
	str	x0, [x1, #:lo12:.LANCHOR71]
	ldrh	w0, [x19, #:lo12:.LANCHOR61]
	lsl	w0, w0, 1
	bl	ftl_malloc
	adrp	x1, .LANCHOR200
	str	x0, [x1, #:lo12:.LANCHOR200]
	ldrh	w0, [x19, #:lo12:.LANCHOR61]
	adrp	x19, .LANCHOR62
	lsl	w0, w0, 2
	bl	ftl_malloc
	adrp	x1, .LANCHOR201
	str	x0, [x1, #:lo12:.LANCHOR201]
	ldrh	w0, [x19, #:lo12:.LANCHOR62]
	lsl	w0, w0, 2
	bl	ftl_malloc
	ldrh	w2, [x19, #:lo12:.LANCHOR62]
	adrp	x1, .LANCHOR202
	str	x0, [x1, #:lo12:.LANCHOR202]
	mov	w1, 0
	lsl	w2, w2, 2
	bl	ftl_memset
	adrp	x0, .LANCHOR66
	ldrh	w19, [x0, #:lo12:.LANCHOR66]
	lsl	w19, w19, 2
	mov	w0, w19
	bl	ftl_malloc
	adrp	x1, .LANCHOR134
	str	x0, [x1, #:lo12:.LANCHOR134]
	mov	w0, w19
	bl	ftl_malloc
	adrp	x19, .LANCHOR67
	adrp	x1, .LANCHOR203
	str	x0, [x1, #:lo12:.LANCHOR203]
	ldr	w0, [x21, #:lo12:.LANCHOR64]
	lsl	w0, w0, 2
	bl	ftl_malloc
	adrp	x1, .LANCHOR133
	str	x0, [x1, #:lo12:.LANCHOR133]
	ldrh	w0, [x19, #:lo12:.LANCHOR67]
	lsl	w0, w0, 4
	bl	ftl_malloc
	adrp	x1, .LANCHOR98
	str	x0, [x1, #:lo12:.LANCHOR98]
	ldrh	w1, [x19, #:lo12:.LANCHOR67]
	adrp	x19, .LANCHOR126
	ldrh	w0, [x23, #:lo12:.LANCHOR57]
	mul	w0, w1, w0
	bl	ftl_malloc
	adrp	x1, .LANCHOR129
	str	x0, [x1, #:lo12:.LANCHOR129]
	mov	w0, 6
	ldrh	w1, [x20, #:lo12:.LANCHOR41]
	adrp	x20, .LANCHOR45
	mul	w0, w1, w0
	bl	ftl_malloc
	adrp	x1, .LANCHOR83
	str	x0, [x1, #:lo12:.LANCHOR83]
	adrp	x0, .LANCHOR51
	ldrh	w1, [x20, #:lo12:.LANCHOR45]
	ldrh	w0, [x0, #:lo12:.LANCHOR51]
	add	w0, w0, 31
	asr	w0, w0, 5
	strh	w0, [x19, #:lo12:.LANCHOR126]
	mul	w0, w1, w0
	lsl	w0, w0, 2
	bl	ftl_malloc
	adrp	x1, .LANCHOR76
	ldrh	w5, [x19, #:lo12:.LANCHOR126]
	add	x2, x1, :lo12:.LANCHOR76
	ldrh	w7, [x20, #:lo12:.LANCHOR45]
	add	x6, x2, 40
	mov	w3, w5
	str	x0, [x2, 32]
	mov	x0, 1
.L1158:
	cmp	w0, w7
	bcc	.L1159
	mov	w2, 8
	sub	w2, w2, w0
	add	x2, x2, 1
	add	x1, x1, :lo12:.LANCHOR76
	mov	x3, 0
.L1160:
	add	x3, x3, 1
	cmp	x2, x3
	bne	.L1161
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
.L1159:
	ldr	x4, [x2, 32]
	add	w0, w0, 1
	add	x4, x4, x3, uxtw 2
	add	w3, w3, w5
	str	x4, [x6], 8
	b	.L1158
.L1161:
	add	x4, x0, x3
	add	x4, x1, x4, lsl 3
	str	xzr, [x4, 24]
	b	.L1160
	.size	FtlMemInit, .-FtlMemInit
	.section	.text.ftl_free,"ax",@progbits
	.align	2
	.global	ftl_free
	.type	ftl_free, %function
ftl_free:
	b	free
	.size	ftl_free, .-ftl_free
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
	b	FlashDeInit
	.size	rk_nand_de_init, .-rk_nand_de_init
	.section	.text.rk_ftl_get_capacity,"ax",@progbits
	.align	2
	.global	rk_ftl_get_capacity
	.type	rk_ftl_get_capacity, %function
rk_ftl_get_capacity:
	adrp	x0, .LANCHOR68
	ldr	w0, [x0, #:lo12:.LANCHOR68]
	ret
	.size	rk_ftl_get_capacity, .-rk_ftl_get_capacity
	.section	.text.rknand_print_hex,"ax",@progbits
	.align	2
	.global	rknand_print_hex
	.type	rknand_print_hex, %function
rknand_print_hex:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x21, x22, [sp, 32]
	adrp	x21, .LC20
	stp	x23, x24, [sp, 48]
	mov	x22, x1
	stp	x25, x26, [sp, 64]
	adrp	x23, .LC19
	mov	x26, x0
	mov	w24, w2
	uxtw	x25, w3
	add	x23, x23, :lo12:.LC19
	add	x21, x21, :lo12:.LC20
	stp	x19, x20, [sp, 16]
	str	x27, [sp, 80]
	mov	x19, 0
	mov	w20, 0
	adrp	x27, .LC21
.L1168:
	cmp	x25, x19
	bne	.L1174
	ldp	x19, x20, [sp, 16]
	adrp	x1, .LC21
	ldp	x21, x22, [sp, 32]
	add	x1, x1, :lo12:.LC21
	ldp	x23, x24, [sp, 48]
	adrp	x0, .LC7
	ldp	x25, x26, [sp, 64]
	add	x0, x0, :lo12:.LC7
	ldr	x27, [sp, 80]
	ldp	x29, x30, [sp], 96
	b	printf
.L1174:
	cbnz	w20, .L1169
	mov	w2, w19
	mov	x1, x26
	mov	x0, x23
	bl	printf
.L1169:
	cmp	w24, 4
	bne	.L1170
	ldr	w1, [x22, x19, lsl 2]
.L1176:
	mov	x0, x21
	add	w20, w20, 1
	bl	printf
	cmp	w20, 15
	bls	.L1173
	mov	w20, 0
	add	x1, x27, :lo12:.LC21
	adrp	x0, .LC7
	add	x0, x0, :lo12:.LC7
	bl	printf
.L1173:
	add	x19, x19, 1
	b	.L1168
.L1170:
	cmp	w24, 2
	bne	.L1172
	ldrsh	w1, [x22, x19, lsl 1]
	b	.L1176
.L1172:
	ldrb	w1, [x22, x19]
	b	.L1176
	.size	rknand_print_hex, .-rknand_print_hex
	.section	.text.HynixGetReadRetryDefault,"ax",@progbits
	.align	2
	.global	HynixGetReadRetryDefault
	.type	HynixGetReadRetryDefault, %function
HynixGetReadRetryDefault:
	stp	x29, x30, [sp, -144]!
	mov	w1, -84
	mov	w4, -83
	mov	w3, -82
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	adrp	x20, .LANCHOR20
	stp	x25, x26, [sp, 64]
	mov	w26, w0
	add	x0, x20, :lo12:.LANCHOR20
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	cmp	w26, 2
	stp	x27, x28, [sp, 80]
	strb	w1, [x0, 4]
	mov	w1, -81
	strb	w26, [x20, #:lo12:.LANCHOR20]
	strb	w4, [x0, 5]
	strb	w3, [x0, 6]
	strb	w1, [x0, 7]
	bne	.L1178
	mov	w1, -89
	strb	w1, [x0, 4]
	adrp	x0, .LANCHOR204+17
	mov	w1, -9
	strb	w1, [x0, #:lo12:.LANCHOR204+17]
.L1243:
	mov	w27, 7
	b	.L1287
.L1178:
	cmp	w26, 3
	bne	.L1180
	mov	w1, -80
	strb	w1, [x0, 4]
	mov	w1, -79
	strb	w1, [x0, 5]
	mov	w1, -78
	strb	w1, [x0, 6]
	mov	w1, -77
	strb	w1, [x0, 7]
	mov	w1, -76
	strb	w1, [x0, 8]
	mov	w1, -75
	strb	w1, [x0, 9]
	mov	w1, -74
	strb	w1, [x0, 10]
	mov	w1, -73
.L1286:
	mov	w27, 8
	mov	w28, w27
	strb	w1, [x0, 11]
.L1179:
	sub	w0, w26, #1
	cmp	w0, 1
	bhi	.L1185
	adrp	x26, .LANCHOR26
	adrp	x0, .LANCHOR27
	adrp	x25, .LANCHOR0
	add	x26, x26, :lo12:.LANCHOR26
	add	x4, x0, :lo12:.LANCHOR27
	add	x25, x25, :lo12:.LANCHOR0
	mov	w24, 0
.L1186:
	ldrb	w0, [x26]
	cmp	w0, w24
	bhi	.L1192
.L1193:
	add	x20, x20, :lo12:.LANCHOR20
	ldp	x21, x22, [sp, 32]
	strb	w28, [x20, 1]
	strb	w27, [x20, 2]
	ldp	x23, x24, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 144
	ret
.L1180:
	cmp	w26, 4
	bne	.L1181
	mov	w5, -52
	strb	w5, [x0, 4]
	mov	w5, -65
	strb	w5, [x0, 5]
	mov	w5, -86
	strb	w5, [x0, 6]
	mov	w5, -85
	strb	w4, [x0, 9]
	strb	w5, [x0, 7]
	mov	w5, -51
	strb	w3, [x0, 10]
	strb	w5, [x0, 8]
	b	.L1286
.L1181:
	cmp	w26, 5
	bne	.L1182
	mov	w1, 56
	strb	w1, [x0, 4]
	mov	w1, 57
	strb	w1, [x0, 5]
	mov	w1, 58
	mov	w27, 8
	strb	w1, [x0, 6]
	mov	w1, 59
	strb	w1, [x0, 7]
.L1287:
	mov	w28, 4
	b	.L1179
.L1182:
	cmp	w26, 6
	bne	.L1183
	mov	w1, 14
	strb	w1, [x0, 4]
	mov	w1, 15
	strb	w1, [x0, 5]
	mov	w1, 16
	mov	w27, 12
	strb	w1, [x0, 6]
	mov	w1, 17
	strb	w1, [x0, 7]
	b	.L1287
.L1183:
	cmp	w26, 7
	bne	.L1184
	mov	w1, -80
	strb	w1, [x0, 4]
	mov	w1, -79
	strb	w1, [x0, 5]
	mov	w1, -78
	strb	w1, [x0, 6]
	mov	w1, -77
	strb	w1, [x0, 7]
	mov	w1, -76
	strb	w1, [x0, 8]
	mov	w1, -75
	strb	w1, [x0, 9]
	mov	w1, -74
	strb	w1, [x0, 10]
	mov	w1, -73
	strb	w1, [x0, 11]
	mov	w1, -44
	mov	w27, 12
	strb	w1, [x0, 12]
	mov	w28, 10
	mov	w1, -43
	strb	w1, [x0, 13]
	b	.L1179
.L1184:
	cmp	w26, 8
	bne	.L1243
	mov	w1, 6
	strb	w1, [x0, 4]
	mov	w1, 7
	strb	w1, [x0, 5]
	mov	w1, 9
	strb	w26, [x0, 6]
	strb	w1, [x0, 7]
	mov	w27, 50
	mov	w1, 10
	mov	w28, 5
	strb	w1, [x0, 8]
	b	.L1179
.L1192:
	ldrb	w1, [x4, w24, sxtw]
	add	x0, x20, :lo12:.LANCHOR20
	mov	x21, x0
	mov	x22, 0
	ubfiz	x19, x1, 6, 8
	sbfiz	x1, x1, 4, 32
	add	x2, x25, x1
	add	x19, x19, 20
	add	x19, x0, x19
	ldr	x1, [x25, x1]
	ldrb	w23, [x2, 8]
	add	x23, x1, x23, lsl 8
	mov	w1, 55
.L1187:
	add	x0, x21, x22
	str	w1, [x23, 2056]
	str	x4, [x29, 128]
	str	w1, [x29, 140]
	ldrb	w0, [x0, 4]
	str	w0, [x23, 2052]
	mov	x0, 80
	bl	udelay
	ldr	w0, [x23, 2048]
	strb	w0, [x19, x22]
	add	x22, x22, 1
	cmp	w28, w22, uxtb
	ldr	w1, [x29, 140]
	ldr	x4, [x29, 128]
	bhi	.L1187
	adrp	x2, .LANCHOR204
	add	x2, x2, :lo12:.LANCHOR204
	mov	x0, 0
.L1190:
	add	x7, x19, x0
	add	x6, x2, x0
	mov	x1, 1
.L1189:
	lsl	x3, x1, 2
	lsl	x8, x1, 3
	ldrb	w10, [x19, x0]
	add	x1, x1, 1
	cmp	x1, 7
	ldrb	w3, [x6, x3]
	add	w3, w3, w10
	strb	w3, [x7, x8]
	bne	.L1189
	add	x0, x0, 1
	cmp	x0, 4
	bne	.L1190
	add	w24, w24, 1
	strb	wzr, [x19, 16]
	strb	wzr, [x19, 24]
	and	w24, w24, 255
	strb	wzr, [x19, 32]
	strb	wzr, [x19, 40]
	strb	wzr, [x19, 48]
	strb	wzr, [x19, 41]
	strb	wzr, [x19, 49]
	b	.L1186
.L1185:
	sub	w0, w26, #3
	cmp	w0, 5
	bhi	.L1193
	mul	w24, w27, w28
	adrp	x25, .LANCHOR26
	sub	w22, w28, #1
	mov	w21, 0
	and	x22, x22, 255
	lsl	w0, w24, 4
	asr	w23, w24, 1
	str	w0, [x29, 128]
	lsl	w0, w23, 1
	sbfiz	x24, x23, 1, 32
	str	w0, [x29, 140]
	add	x0, x25, :lo12:.LANCHOR26
	sub	w25, w26, #5
	str	x0, [x29, 120]
	add	x0, x22, 1
	str	x0, [x29, 112]
.L1194:
	ldr	x0, [x29, 120]
	ldrb	w0, [x0]
	cmp	w0, w21
	bls	.L1193
	adrp	x0, .LANCHOR27
	add	x0, x0, :lo12:.LANCHOR27
	ldrb	w22, [x0, w21, sxtw]
	adrp	x0, .LANCHOR0
	add	x0, x0, :lo12:.LANCHOR0
	sbfiz	x1, x22, 4, 32
	add	x3, x0, x1
	ldr	x0, [x0, x1]
	ldrb	w19, [x3, 8]
	add	x19, x0, x19, lsl 8
	mov	w0, 255
	str	w0, [x19, 2056]
	mov	w0, w22
	bl	NandcWaitFlashReady
	cmp	w26, 7
	bne	.L1195
	mov	x1, 28
	mov	w0, 160
	add	x3, x20, :lo12:.LANCHOR20
	umaddl	x0, w0, w22, x1
.L1288:
	add	x3, x3, x0
	mov	w0, 54
	str	w0, [x19, 2056]
	cmp	w26, 4
	bne	.L1198
	mov	w0, 255
	str	w0, [x19, 2052]
	mov	w0, 64
	str	w0, [x19, 2048]
	mov	w0, 204
.L1289:
	str	w0, [x19, 2052]
	mov	w0, 77
	b	.L1290
.L1195:
	cmp	w26, 8
	beq	.L1197
	ubfiz	x0, x22, 6, 8
	add	x3, x20, :lo12:.LANCHOR20
	add	x0, x0, 20
	b	.L1288
.L1198:
	cmp	w25, 1
	bhi	.L1200
	add	x0, x20, :lo12:.LANCHOR20
	ldrb	w0, [x0, 4]
	str	w0, [x19, 2052]
	mov	w0, 82
.L1290:
	str	w0, [x19, 2048]
.L1199:
	mov	w0, 22
	str	w0, [x19, 2056]
	mov	w0, 23
	str	w0, [x19, 2056]
	mov	w0, 4
	str	w0, [x19, 2056]
	mov	w0, 25
	str	w0, [x19, 2056]
	str	wzr, [x19, 2056]
	cmp	w26, 6
	str	wzr, [x19, 2052]
	str	wzr, [x19, 2052]
	bne	.L1201
	mov	w0, 31
	str	w0, [x19, 2052]
.L1202:
	mov	w0, 2
	str	w0, [x19, 2052]
	str	wzr, [x19, 2052]
.L1242:
	mov	w0, 48
	str	w0, [x19, 2056]
	str	x3, [x29, 104]
	mov	w0, w22
	bl	NandcWaitFlashReady
	cmp	w25, 1
	ldr	x3, [x29, 104]
	ccmp	w26, 8, 4, hi
	beq	.L1244
	cmp	w26, 7
	mov	w0, 2
	mov	w1, 32
	csel	w1, w1, w0, eq
.L1203:
	adrp	x8, .LANCHOR154
	mov	x7, 0
	ldr	x0, [x8, #:lo12:.LANCHOR154]
.L1204:
	ldr	w10, [x19, 2048]
	strb	w10, [x0, x7]
	add	x7, x7, 1
	cmp	w1, w7, uxtb
	bhi	.L1204
	cmp	w26, 8
	bne	.L1205
	mov	w1, 0
.L1207:
	ldrb	w7, [x0]
	cmp	w7, 50
	beq	.L1206
	ldrb	w7, [x0, 1]
	cmp	w7, 5
	beq	.L1206
	add	w1, w1, 1
	add	x0, x0, 4
	and	w1, w1, 255
	cmp	w1, 8
	bne	.L1207
.L1208:
	adrp	x0, .LC22
	mov	w1, 0
	add	x0, x0, :lo12:.LC22
	bl	printf
.L1210:
	b	.L1210
.L1200:
	cmp	w26, 7
	bne	.L1199
	mov	w0, 174
	str	w0, [x19, 2052]
	str	wzr, [x19, 2048]
	mov	w0, 176
	b	.L1289
.L1201:
	str	wzr, [x19, 2052]
	b	.L1202
.L1244:
	mov	w1, 16
	b	.L1203
.L1206:
	cmp	w1, 6
	bhi	.L1208
.L1209:
	ldr	x7, [x8, #:lo12:.LANCHOR154]
	mov	x0, 0
.L1219:
	ldr	w1, [x29, 128]
	cmp	w1, w0
	bgt	.L1220
	ldr	x1, [x8, #:lo12:.LANCHOR154]
	mov	w10, 8
	add	x8, x1, x24
.L1222:
	mov	x0, 0
.L1221:
	ldrh	w11, [x8, x0, lsl 1]
	mvn	w11, w11
	strh	w11, [x8, x0, lsl 1]
	add	x0, x0, 1
	cmp	w23, w0
	bgt	.L1221
	ldr	w0, [x29, 140]
	subs	w10, w10, #1
	add	x8, x8, x0, uxtw 1
	bne	.L1222
	mov	x10, x1
	mov	w11, 0
	mov	w16, 1
.L1228:
	mov	w0, 0
	mov	w8, 0
.L1227:
	mov	x14, x10
	lsl	w15, w16, w8
	mov	w13, 16
	mov	w12, 0
.L1225:
	ldrh	w17, [x14]
	add	x14, x14, x24
	bics	wzr, w15, w17
	cinc	w12, w12, eq
	subs	w13, w13, #1
	bne	.L1225
	cmp	w12, 8
	bls	.L1226
	orr	w0, w0, w15
	and	w0, w0, 65535
.L1226:
	add	w8, w8, 1
	cmp	w8, 16
	bne	.L1227
	strh	w0, [x10], 2
	add	w11, w11, 1
	cmp	w23, w11
	bgt	.L1228
	mov	x0, 0
	mov	w8, 0
.L1231:
	ldr	w10, [x1, x0]
	add	x0, x0, 4
	cmp	w10, 0
	cinc	w8, w8, eq
	cmp	x0, 32
	bne	.L1231
	cmp	w8, 7
	ble	.L1232
	mov	w3, 1024
	mov	w2, 1
	adrp	x0, .LC23
	add	x0, x0, :lo12:.LC23
	bl	rknand_print_hex
	adrp	x0, .LC22
	mov	w1, 0
	add	x0, x0, :lo12:.LC22
	bl	printf
.L1233:
	b	.L1233
.L1205:
	cmp	w26, 7
	bne	.L1211
	mov	w1, 0
.L1213:
	ldrb	w7, [x0]
	cmp	w7, 12
	beq	.L1212
	ldrb	w7, [x0, 1]
	cmp	w7, 10
	beq	.L1212
	add	w1, w1, 1
	add	x0, x0, 4
	and	w1, w1, 255
	cmp	w1, 8
	bne	.L1213
.L1214:
	adrp	x0, .LC22
	mov	w1, 0
	add	x0, x0, :lo12:.LC22
	bl	printf
.L1215:
	b	.L1215
.L1212:
	cmp	w1, 6
	bls	.L1209
	b	.L1214
.L1211:
	cmp	w26, 6
	bne	.L1209
	mov	x1, 0
.L1216:
	ldrb	w7, [x0, x1]
	cmp	w7, 12
	beq	.L1209
	add	x7, x0, x1
	ldrb	w7, [x7, 8]
	cmp	w7, 4
	beq	.L1209
	add	x1, x1, 1
	cmp	x1, 8
	bne	.L1216
	adrp	x0, .LC22
	mov	w1, 0
	add	x0, x0, :lo12:.LC22
	bl	printf
.L1218:
	b	.L1218
.L1220:
	ldr	w1, [x19, 2048]
	strb	w1, [x7, x0]
	add	x0, x0, 1
	b	.L1219
.L1232:
	cmp	w26, 6
	beq	.L1246
	cmp	w26, 7
	beq	.L1247
	cmp	w26, 8
	mov	x1, 8
	mov	x0, 5
	csel	x0, x0, x1, eq
.L1234:
	mov	w8, 0
.L1235:
	mov	x1, 0
.L1236:
	ldrb	w10, [x7, x1]
	strb	w10, [x3, x1]
	add	x1, x1, 1
	cmp	w28, w1, uxtb
	bhi	.L1236
	ldr	x1, [x29, 112]
	add	w8, w8, 1
	add	x3, x3, x0
	cmp	w27, w8
	add	x7, x7, x1
	bgt	.L1235
	mov	w0, 255
	str	w0, [x19, 2056]
	mov	w0, w22
	bl	NandcWaitFlashReady
	cmp	w25, 1
	bhi	.L1238
	mov	w0, 54
	str	w0, [x19, 2056]
	adrp	x0, .LANCHOR20+4
	mov	w1, -1
	ldrb	w0, [x0, #:lo12:.LANCHOR20+4]
	str	w0, [x19, 2052]
	str	wzr, [x19, 2048]
	mov	w0, 22
	str	w0, [x19, 2056]
	mov	w0, w21
	bl	FlashReadCmd
.L1239:
	add	w21, w21, 1
	mov	w0, w22
	and	w21, w21, 255
	bl	NandcWaitFlashReady
	b	.L1194
.L1246:
	mov	x0, 4
	b	.L1234
.L1247:
	mov	x0, 10
	b	.L1234
.L1238:
	cmp	w26, 8
	bne	.L1240
	mov	w0, 190
.L1291:
	str	w0, [x19, 2056]
	b	.L1239
.L1240:
	mov	w0, 56
	b	.L1291
.L1197:
	mov	w0, 120
	str	w0, [x19, 2056]
	str	wzr, [x19, 2052]
	mov	w0, 23
	str	wzr, [x19, 2052]
	mov	w1, 25
	str	wzr, [x19, 2052]
	add	x3, x20, :lo12:.LANCHOR20
	str	w0, [x19, 2056]
	mov	w0, 4
	str	w0, [x19, 2056]
	add	x3, x3, 28
	str	w1, [x19, 2056]
	mov	w1, 218
	str	w1, [x19, 2056]
	mov	w1, 21
	str	wzr, [x19, 2056]
	str	wzr, [x19, 2052]
	str	wzr, [x19, 2052]
	str	w1, [x19, 2052]
	str	w0, [x19, 2052]
	str	wzr, [x19, 2052]
	b	.L1242
	.size	HynixGetReadRetryDefault, .-HynixGetReadRetryDefault
	.section	.text.FlashGetReadRetryDefault,"ax",@progbits
	.align	2
	.global	FlashGetReadRetryDefault
	.type	FlashGetReadRetryDefault, %function
FlashGetReadRetryDefault:
	mov	w1, w0
	cbz	w0, .L1292
	sub	w2, w0, #1
	cmp	w2, 7
	bhi	.L1294
	b	HynixGetReadRetryDefault
.L1294:
	cmp	w0, 49
	bne	.L1295
	adrp	x2, .LANCHOR20
	add	x0, x2, :lo12:.LANCHOR20
	strb	w1, [x2, #:lo12:.LANCHOR20]
	mov	w1, 4
	strb	w1, [x0, 1]
	mov	w1, 15
	strb	w1, [x0, 2]
	adrp	x1, .LANCHOR14
	add	x1, x1, :lo12:.LANCHOR14
	mov	w2, 64
.L1304:
	add	x0, x0, 4
	b	ftl_memcpy
.L1295:
	sub	w0, w0, #65
	cmp	w1, 33
	ccmp	w0, 1, 0, ne
	bhi	.L1296
	adrp	x2, .LANCHOR20
	add	x0, x2, :lo12:.LANCHOR20
	strb	w1, [x2, #:lo12:.LANCHOR20]
	mov	w1, 4
.L1305:
	strb	w1, [x0, 1]
	mov	w1, 7
	mov	w2, 45
	strb	w1, [x0, 2]
	adrp	x1, .LANCHOR10
	add	x1, x1, :lo12:.LANCHOR10
	b	.L1304
.L1296:
	cmp	w1, 34
	mov	w0, 67
	ccmp	w1, w0, 4, ne
	bne	.L1297
	adrp	x2, .LANCHOR20
	add	x0, x2, :lo12:.LANCHOR20
	strb	w1, [x2, #:lo12:.LANCHOR20]
	mov	w1, 5
	b	.L1305
.L1297:
	cmp	w1, 35
	mov	w0, 68
	ccmp	w1, w0, 4, ne
	bne	.L1292
	adrp	x2, .LANCHOR20
	add	x0, x2, :lo12:.LANCHOR20
	strb	w1, [x2, #:lo12:.LANCHOR20]
	mov	w1, 5
	strb	w1, [x0, 1]
	mov	w1, 17
	mov	w2, 95
	strb	w1, [x0, 2]
	adrp	x1, .LANCHOR9
	add	x1, x1, :lo12:.LANCHOR9
	b	.L1304
.L1292:
	ret
	.size	FlashGetReadRetryDefault, .-FlashGetReadRetryDefault
	.section	.text.FlashInit,"ax",@progbits
	.align	2
	.global	FlashInit
	.type	FlashInit, %function
FlashInit:
	stp	x29, x30, [sp, -128]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	stp	x21, x22, [sp, 32]
	mov	w0, 32768
	stp	x23, x24, [sp, 48]
	adrp	x20, .LANCHOR30
	stp	x25, x26, [sp, 64]
	adrp	x25, .LANCHOR3
	stp	x27, x28, [sp, 80]
	bl	ftl_malloc
	adrp	x1, .LANCHOR154
	adrp	x26, .LANCHOR208
	adrp	x21, .LANCHOR2
	adrp	x22, .LANCHOR158
	str	x0, [x1, #:lo12:.LANCHOR154]
	mov	w0, 32768
	bl	ftl_malloc
	adrp	x24, .LANCHOR0
	adrp	x1, .LANCHOR152
	add	x24, x24, :lo12:.LANCHOR0
	mov	w23, 0
	str	x0, [x1, #:lo12:.LANCHOR152]
	mov	w0, 4096
	bl	ftl_malloc
	adrp	x1, .LANCHOR205
	str	x0, [x1, #:lo12:.LANCHOR205]
	mov	w0, 32768
	bl	ftl_malloc
	adrp	x1, .LANCHOR206
	str	x0, [x1, #:lo12:.LANCHOR206]
	mov	w0, 4096
	bl	ftl_malloc
	strb	wzr, [x26, #:lo12:.LANCHOR208]
	adrp	x1, .LANCHOR207
	strb	wzr, [x20, #:lo12:.LANCHOR30]
	strb	wzr, [x21, #:lo12:.LANCHOR2]
	str	x0, [x1, #:lo12:.LANCHOR207]
	adrp	x1, .LANCHOR157
	mov	w0, 50
	strb	w0, [x25, #:lo12:.LANCHOR3]
	strb	w0, [x1, #:lo12:.LANCHOR157]
	adrp	x0, .LANCHOR156
	mov	w1, 128
	str	wzr, [x0, #:lo12:.LANCHOR156]
	adrp	x0, .LANCHOR4
	str	w1, [x0, #:lo12:.LANCHOR4]
	adrp	x0, .LANCHOR147
	str	wzr, [x0, #:lo12:.LANCHOR147]
	mov	w0, 60
	strb	w0, [x22, #:lo12:.LANCHOR158]
	mov	x0, x19
	adrp	x19, .LANCHOR22
	bl	NandcInit
	add	x28, x19, :lo12:.LANCHOR22
	str	x26, [x29, 120]
	adrp	x26, .LC24
	add	x0, x26, :lo12:.LC24
	str	x0, [x29, 112]
.L1312:
	ldrb	w2, [x24, 8]
	and	w27, w23, 255
	str	w2, [x29, 108]
	mov	w0, w27
	ldr	x26, [x24]
	bl	FlashReset
	mov	w0, w27
	bl	NandcFlashCs
	ldr	w2, [x29, 108]
	mov	w0, 144
	ubfiz	x2, x2, 8, 8
	add	x26, x26, x2
	str	w0, [x26, 2056]
	mov	x0, 200
	str	wzr, [x26, 2052]
	bl	udelay
	ldr	w0, [x26, 2048]
	and	w0, w0, 255
	strb	w0, [x28]
	cmp	w0, 44
	ldr	w2, [x26, 2048]
	strb	w2, [x28, 1]
	ldr	w2, [x26, 2048]
	strb	w2, [x28, 2]
	ldr	w2, [x26, 2048]
	strb	w2, [x28, 3]
	ldr	w2, [x26, 2048]
	strb	w2, [x28, 4]
	ldr	w2, [x26, 2048]
	strb	w2, [x28, 5]
	bne	.L1307
	mov	w0, 239
	str	w0, [x26, 2056]
	mov	w0, 1
	str	w0, [x26, 2052]
	mov	x0, 200
	bl	udelay
	mov	w0, 4
	str	w0, [x26, 2048]
	str	wzr, [x26, 2048]
	str	wzr, [x26, 2048]
	str	wzr, [x26, 2048]
.L1307:
	mov	w0, w27
	bl	NandcFlashDeCs
	ldrb	w2, [x28]
	sub	w0, w2, #1
	and	w0, w0, 255
	cmp	w0, 253
	bhi	.L1308
	ldrb	w7, [x28, 5]
	add	w1, w23, 1
	ldrb	w6, [x28, 4]
	ldrb	w5, [x28, 3]
	ldrb	w4, [x28, 2]
	ldrb	w3, [x28, 1]
	ldr	x0, [x29, 112]
	bl	printf
.L1308:
	cbnz	w23, .L1309
	ldrb	w0, [x19, #:lo12:.LANCHOR22]
	add	x1, x19, :lo12:.LANCHOR22
	sub	w0, w0, #1
	and	w0, w0, 255
	cmp	w0, 253
	bhi	.L1357
	ldrb	w0, [x1, 1]
	cmp	w0, 255
	beq	.L1357
.L1309:
	ldrb	w0, [x28]
	cmp	w0, 181
	bne	.L1311
	mov	w0, 44
	strb	w0, [x28]
.L1311:
	add	w23, w23, 1
	add	x24, x24, 16
	add	x28, x28, 8
	cmp	w23, 4
	bne	.L1312
	ldrb	w0, [x19, #:lo12:.LANCHOR22]
	cmp	w0, 173
	beq	.L1313
	adrp	x0, .LANCHOR160
	ldr	w0, [x0, #:lo12:.LANCHOR160]
	bl	NandcSetDdrMode
.L1313:
	adrp	x24, .LANCHOR7
	adrp	x27, .LANCHOR6
	adrp	x26, .LANCHOR122
	mov	w1, 0
	adrp	x23, .LANCHOR20
	mov	w2, 852
	add	x0, x23, :lo12:.LANCHOR20
	bl	ftl_memset
	adrp	x3, .LANCHOR31
	ldr	w4, [x26, #:lo12:.LANCHOR122]
	add	x0, x3, :lo12:.LANCHOR31
	strb	wzr, [x27, #:lo12:.LANCHOR6]
	str	x0, [x24, #:lo12:.LANCHOR7]
	mov	w1, 12336
	movk	w1, 0x5638, lsl 16
	cmp	w4, w1
	bne	.L1314
	ldrb	w0, [x0, 19]
	cmp	w0, 50
	beq	.L1314
	adrp	x0, .LANCHOR29
	mov	w1, 1
	str	w1, [x0, #:lo12:.LANCHOR29]
.L1314:
	add	x0, x19, :lo12:.LANCHOR22
	ldrb	w2, [x0, 1]
	add	w0, w2, 95
	and	w1, w0, 255
	mov	x0, 1
	cmp	w1, 57
	bhi	.L1315
	movk	x0, 0x205, lsl 48
	lsr	x0, x0, x1
	mvn	x0, x0
.L1315:
	cmp	w2, 241
	and	w0, w0, 1
	cset	w1, eq
	eor	w0, w0, 1
	orr	w0, w1, w0
	cbnz	w0, .L1316
	cmp	w2, 220
	bne	.L1317
	add	x0, x19, :lo12:.LANCHOR22
	ldrb	w0, [x0, 3]
	cmp	w0, 149
	bne	.L1317
.L1316:
	adrp	x28, .LANCHOR209
	add	x5, x28, :lo12:.LANCHOR209
	mov	w1, 16
	strb	w1, [x25, #:lo12:.LANCHOR3]
	strb	w1, [x22, #:lo12:.LANCHOR158]
	mov	w0, 1
	ldrb	w1, [x19, #:lo12:.LANCHOR22]
	add	x6, x19, :lo12:.LANCHOR22
	strb	w0, [x21, #:lo12:.LANCHOR2]
	strb	w1, [x5, 1]
	cmp	w1, 152
	strb	w2, [x5, 2]
	bne	.L1319
	ldrsb	w1, [x6, 4]
	tbnz	w1, #31, .L1320
	mov	w0, 24
	strb	w0, [x22, #:lo12:.LANCHOR158]
.L1319:
	cmp	w4, 2049
	mov	w0, 12336
	movk	w0, 0x5638, lsl 16
	ccmp	w4, w0, 4, ne
	bne	.L1322
	mov	w0, 16
	strb	w0, [x22, #:lo12:.LANCHOR158]
.L1322:
	cmp	w2, 218
	bne	.L1323
	add	x0, x28, :lo12:.LANCHOR209
	mov	w1, 2048
	strh	w1, [x0, 14]
	mov	w1, -38
.L1394:
	strb	w1, [x0, 2]
.L1324:
	adrp	x1, .LANCHOR146
	add	x1, x1, :lo12:.LANCHOR146
	mov	w2, 32
	add	x1, x1, 32
	str	x3, [x29, 120]
	adrp	x0, .LANCHOR8
	add	x0, x0, :lo12:.LANCHOR8
	bl	ftl_memcpy
	ldr	x3, [x29, 120]
	mov	w2, 32
	add	x1, x28, :lo12:.LANCHOR209
	add	x0, x3, :lo12:.LANCHOR31
	bl	ftl_memcpy
.L1317:
	ldrb	w0, [x21, #:lo12:.LANCHOR2]
	adrp	x22, .LANCHOR16
	cbnz	w0, .L1327
	bl	FlashLoadPhyInfoInRam
	cbnz	w0, .L1329
	ldr	x0, [x24, #:lo12:.LANCHOR7]
	adrp	x28, .LANCHOR25
	ldrb	w1, [x0, 17]
	and	w0, w1, 7
	strb	w0, [x28, #:lo12:.LANCHOR25]
	tbnz	x1, 0, .L1329
	mov	w1, 1
	strb	w1, [x20, #:lo12:.LANCHOR30]
	bl	FlashSetInterfaceMode
	ldrb	w0, [x28, #:lo12:.LANCHOR25]
	bl	NandcSetMode
.L1329:
	ldr	x0, [x24, #:lo12:.LANCHOR7]
	ldrb	w0, [x0, 26]
	strb	w0, [x22, #:lo12:.LANCHOR16]
	bl	FlashLoadPhyInfo
	cbz	w0, .L1327
	ldr	x0, [x24, #:lo12:.LANCHOR7]
	ldrh	w1, [x0, 14]
	adrp	x0, .LC25
	add	x0, x0, :lo12:.LC25
	bl	printf
	bl	FlashLoadPhyInfoInRam
	cmn	w0, #1
	beq	.L1306
	bl	FlashDieInfoInit
	ldr	x0, [x24, #:lo12:.LANCHOR7]
	ldrb	w0, [x0, 19]
	bl	FlashGetReadRetryDefault
	ldr	x0, [x24, #:lo12:.LANCHOR7]
	adrp	x1, .LANCHOR125
	ldrh	w1, [x1, #:lo12:.LANCHOR125]
	ldrb	w2, [x0, 9]
	add	w1, w1, 4095
	cmp	w2, w1, lsr 12
	blt	.L1332
	ldrh	w1, [x0, 14]
	add	w1, w1, 255
	cmp	w2, w1, lsr 8
	bge	.L1333
.L1332:
	ldrh	w1, [x0, 14]
	and	w1, w1, -256
	strh	w1, [x0, 14]
.L1333:
	adrp	x0, .LANCHOR25
	ldrb	w0, [x0, #:lo12:.LANCHOR25]
	tst	w0, 6
	beq	.L1334
	bl	FlashSavePhyInfo
	mov	w0, 0
	bl	flash_enter_slc_mode
	adrp	x0, .LANCHOR155
	ldr	w1, [x0, #:lo12:.LANCHOR155]
	mov	w0, 0
	bl	FlashDdrParaScan
	mov	w0, 0
	bl	flash_exit_slc_mode
.L1334:
	bl	FlashSavePhyInfo
.L1327:
	ldr	x2, [x24, #:lo12:.LANCHOR7]
	adrp	x28, .LANCHOR148
	str	xzr, [x28, #:lo12:.LANCHOR148]
	ldrb	w0, [x2, 26]
	strb	w0, [x22, #:lo12:.LANCHOR16]
	ldrh	w0, [x2, 16]
	ubfx	x1, x0, 7, 1
	strb	w1, [x27, #:lo12:.LANCHOR6]
	adrp	x1, .LANCHOR210
	ubfx	x3, x0, 3, 1
	adrp	x27, .LANCHOR25
	strb	w3, [x1, #:lo12:.LANCHOR210]
	adrp	x1, .LANCHOR28
	ubfx	x3, x0, 4, 1
	ubfx	x0, x0, 8, 3
	strb	w3, [x1, #:lo12:.LANCHOR28]
	strb	w0, [x27, #:lo12:.LANCHOR25]
	ldrh	w1, [x2, 10]
	ldrb	w0, [x2, 12]
	sdiv	w1, w1, w0
	ldrb	w0, [x2, 18]
	bl	BuildFlashLsbPageTable
	bl	FlashDieInfoInit
	ldr	x0, [x24, #:lo12:.LANCHOR7]
	ldrh	w1, [x0, 16]
	tbz	x1, 6, .L1336
	add	x3, x23, :lo12:.LANCHOR20
	adrp	x1, .LANCHOR11
	ldrb	w0, [x0, 19]
	adrp	x2, .LANCHOR13
	strb	w0, [x1, #:lo12:.LANCHOR11]
	mov	x4, x2
	ldrb	w1, [x3, 1]
	strb	w1, [x2, #:lo12:.LANCHOR13]
	adrp	x1, .LANCHOR149
	ldrb	w3, [x3, 2]
	strb	w3, [x1, #:lo12:.LANCHOR149]
	sub	w3, w0, #1
	and	w3, w3, 255
	cmp	w3, 7
	bhi	.L1337
	adrp	x1, HynixReadRetrial
	add	x1, x1, :lo12:HynixReadRetrial
	str	x1, [x28, #:lo12:.LANCHOR148]
	sub	w1, w0, #5
	and	w1, w1, 255
	cmp	w1, 1
	ccmp	w0, 8, 4, hi
	bne	.L1338
	adrp	x1, .LANCHOR36
	mov	w2, 1
	str	w2, [x1, #:lo12:.LANCHOR36]
.L1338:
	add	x23, x23, :lo12:.LANCHOR20
	cmp	w0, 7
	beq	.L1395
	cmp	w0, 8
	bne	.L1360
.L1395:
	add	x23, x23, 28
.L1339:
	mov	x1, 0
	mov	w2, 0
.L1341:
	ldrsb	w3, [x23, x1]
	add	x1, x1, 1
	cmp	w3, 0
	cinc	w2, w2, eq
	cmp	x1, 32
	bne	.L1341
	cmp	w2, 27
	bls	.L1336
	bl	FlashGetReadRetryDefault
	bl	FlashSavePhyInfo
.L1336:
	ldr	w1, [x26, #:lo12:.LANCHOR122]
	mov	w0, 12336
	movk	w0, 0x5638, lsl 16
	cmp	w1, w0
	bne	.L1351
	ldrb	w0, [x22, #:lo12:.LANCHOR16]
	cbz	w0, .L1351
	ldr	x0, [x24, #:lo12:.LANCHOR7]
	strb	wzr, [x0, 18]
.L1351:
	ldrb	w0, [x19, #:lo12:.LANCHOR22]
	cmp	w0, 44
	bne	.L1352
	ldrb	w0, [x20, #:lo12:.LANCHOR30]
	cbz	w0, .L1352
	strb	wzr, [x20, #:lo12:.LANCHOR30]
	mov	w0, 1
	bl	FlashSetInterfaceMode
	mov	w0, 1
	bl	NandcSetMode
.L1352:
	ldrb	w0, [x27, #:lo12:.LANCHOR25]
	tst	w0, 6
	beq	.L1353
	ldrb	w1, [x20, #:lo12:.LANCHOR30]
	cbnz	w1, .L1354
	tbnz	x0, 0, .L1353
.L1354:
	mov	w0, 0
	bl	flash_enter_slc_mode
	adrp	x0, .LANCHOR155
	ldr	w1, [x0, #:lo12:.LANCHOR155]
	mov	w0, 0
	bl	FlashDdrParaScan
	mov	w0, 0
	bl	flash_exit_slc_mode
.L1353:
	ldr	x0, [x24, #:lo12:.LANCHOR7]
	ldrb	w0, [x0, 20]
	bl	FlashBchSel
	adrp	x0, .LANCHOR144
	add	x0, x0, :lo12:.LANCHOR144
	bl	FlashReadIdbDataRaw
	ldr	x2, [x24, #:lo12:.LANCHOR7]
	mov	w0, 16
	adrp	x5, .LANCHOR15
	strb	w0, [x25, #:lo12:.LANCHOR3]
	add	x0, x5, :lo12:.LANCHOR15
	ldrb	w6, [x19, #:lo12:.LANCHOR22]
	ldrb	w3, [x2, 12]
	strh	w3, [x0, 8]
	ldrb	w1, [x2, 7]
	str	w1, [x0, 4]
	add	x1, x19, :lo12:.LANCHOR22
	ldrb	w4, [x1, 1]
	ldrb	w1, [x1, 3]
	orr	w1, w6, w1, lsl 24
	lsl	w6, w4, 16
	orr	w4, w6, w4, lsl 8
	orr	w1, w1, w4
	str	w1, [x5, #:lo12:.LANCHOR15]
	adrp	x1, .LANCHOR26
	ldrh	w4, [x2, 14]
	ldrb	w1, [x1, #:lo12:.LANCHOR26]
	strh	w1, [x0, 10]
	ldrb	w1, [x2, 13]
	strh	w1, [x0, 12]
	ldrh	w1, [x2, 10]
	strh	w1, [x0, 16]
	strh	w4, [x0, 14]
	sdiv	w3, w1, w3
	strh	w3, [x0, 18]
	ldrb	w5, [x2, 9]
	strh	w5, [x0, 20]
	mov	w3, w5
	mul	w1, w1, w5
	mov	w5, 512
	strh	w5, [x0, 24]
	mov	w5, 16
	and	w1, w1, 65535
	strh	w5, [x0, 26]
	strh	w1, [x0, 22]
	ldrb	w5, [x21, #:lo12:.LANCHOR2]
	cmp	w5, 1
	bne	.L1355
	ubfiz	w1, w1, 1, 15
	lsr	w4, w4, 1
	ubfiz	w3, w3, 1, 15
	strh	w1, [x0, 22]
	strh	w4, [x0, 14]
	mov	w1, 8
	strh	w3, [x0, 20]
	strh	w1, [x0, 26]
.L1355:
	ldrb	w0, [x2, 20]
	bl	FlashBchSel
	mov	w0, 0
.L1306:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 128
	ret
.L1323:
	cmp	w2, 220
	bne	.L1325
	add	x0, x28, :lo12:.LANCHOR209
	mov	w1, 4096
	strh	w1, [x0, 14]
	mov	w1, -36
	b	.L1394
.L1325:
	cmp	w2, 211
	bne	.L1324
	add	x0, x28, :lo12:.LANCHOR209
	mov	w1, 4096
	strh	w1, [x0, 14]
	mov	w1, 2
	strb	w1, [x0, 13]
	b	.L1324
.L1360:
	add	x23, x23, 20
	b	.L1339
.L1337:
	sub	w3, w0, #17
	and	w3, w3, 255
	cmp	w3, 2
	bhi	.L1343
	adrp	x2, MicronReadRetrial
	add	x2, x2, :lo12:MicronReadRetrial
	str	x2, [x28, #:lo12:.LANCHOR148]
	cmp	w0, 19
	beq	.L1344
.L1399:
	mov	w0, 7
	b	.L1397
.L1344:
	mov	w0, 15
.L1397:
	strb	w0, [x1, #:lo12:.LANCHOR149]
	b	.L1336
.L1343:
	sub	w3, w0, #65
	cmp	w0, 33
	and	w3, w3, 255
	ccmp	w3, 1, 0, ne
	bhi	.L1345
	adrp	x0, ToshibaReadRetrial
	add	x0, x0, :lo12:ToshibaReadRetrial
	str	x0, [x28, #:lo12:.LANCHOR148]
	mov	w0, 4
	strb	w0, [x2, #:lo12:.LANCHOR13]
	b	.L1399
.L1345:
	sub	w3, w0, #34
	sub	w2, w0, #67
	and	w3, w3, 255
	and	w2, w2, 255
	cmp	w3, 1
	ccmp	w2, 1, 0, hi
	bhi	.L1346
	adrp	x3, ToshibaReadRetrial
	add	x3, x3, :lo12:ToshibaReadRetrial
	str	x3, [x28, #:lo12:.LANCHOR148]
	cmp	w0, 35
	mov	w3, 68
	ccmp	w0, w3, 4, ne
	beq	.L1347
	mov	w0, 7
.L1396:
	strb	w0, [x1, #:lo12:.LANCHOR149]
	cmp	w2, 1
	bhi	.L1349
	mov	w0, 4
.L1398:
	strb	w0, [x4, #:lo12:.LANCHOR13]
	b	.L1336
.L1347:
	mov	w0, 17
	b	.L1396
.L1349:
	mov	w0, 5
	b	.L1398
.L1346:
	cmp	w0, 49
	bne	.L1350
	adrp	x0, SamsungReadRetrial
	add	x0, x0, :lo12:SamsungReadRetrial
	str	x0, [x28, #:lo12:.LANCHOR148]
	b	.L1336
.L1350:
	cmp	w0, 50
	bne	.L1336
	adrp	x0, samsung_read_retrial
	add	x0, x0, :lo12:samsung_read_retrial
	str	x0, [x28, #:lo12:.LANCHOR148]
	adrp	x0, .LANCHOR29
	str	wzr, [x0, #:lo12:.LANCHOR29]
	b	.L1336
.L1357:
	mov	w0, -2
	b	.L1306
.L1320:
	ldr	x1, [x29, 120]
	strb	w0, [x1, #:lo12:.LANCHOR208]
	b	.L1319
	.size	FlashInit, .-FlashInit
	.section	.text.FlashReadSlc2KPages,"ax",@progbits
	.align	2
	.global	FlashReadSlc2KPages
	.type	FlashReadSlc2KPages, %function
FlashReadSlc2KPages:
	stp	x29, x30, [sp, -144]!
	add	x29, sp, 0
	stp	x21, x22, [sp, 32]
	mov	w22, 56
	stp	x25, x26, [sp, 64]
	and	w21, w1, 255
	str	w2, [x29, 116]
	adrp	x2, .LANCHOR31+9
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	ldrb	w25, [x2, #:lo12:.LANCHOR31+9]
	nop // between mem op and mult-accumulate
	umaddl	x0, w1, w22, x0
	adrp	x26, .LANCHOR208
	str	x0, [x29, 120]
	stp	x23, x24, [sp, 48]
	add	x0, x26, :lo12:.LANCHOR208
	stp	x27, x28, [sp, 80]
	str	x0, [x29, 104]
.L1401:
	ldr	x0, [x29, 120]
	cmp	x19, x0
	bne	.L1421
	ldp	x19, x20, [sp, 16]
	mov	w0, 0
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 144
	ret
.L1421:
	ldr	w1, [x29, 116]
	mov	w4, w21
	add	x3, x29, 136
	add	x2, x29, 140
	mov	x0, x19
	bl	LogAddr2PhyAddr
	adrp	x0, .LANCHOR26
	ldr	w1, [x29, 136]
	ldrb	w0, [x0, #:lo12:.LANCHOR26]
	cmp	w0, w1
	bhi	.L1402
	mov	w0, -1
	str	w0, [x19]
.L1403:
	sub	w21, w21, #1
	add	x19, x19, 56
	and	w21, w21, 255
	b	.L1401
.L1402:
	adrp	x0, .LANCHOR27
	add	x0, x0, :lo12:.LANCHOR27
	add	x23, x26, :lo12:.LANCHOR208
	mov	w22, 0
	mov	w24, 256
	ldrb	w20, [x0, w1, uxtw]
	mov	w0, w20
	bl	NandcWaitFlashReady
	mov	w0, w20
	bl	NandcFlashCs
.L1404:
	ldr	w1, [x29, 140]
	mov	w0, w20
	bl	FlashReadCmd
	mov	w0, w20
	bl	NandcWaitFlashReady
	ldp	x3, x4, [x19, 8]
	mov	w2, w25
	mov	w1, 0
	mov	w0, w20
	bl	NandcXferData
	mov	w28, w0
	ldrb	w0, [x23]
	cbz	w0, .L1405
	mov	w0, w20
	bl	flash_read_ecc
	cmp	w0, 5
	csel	w28, w28, w24, ls
.L1405:
	cmp	w22, 9
	ccmn	w28, #1, 0, ls
	bne	.L1406
	add	w22, w22, 1
	b	.L1404
.L1406:
	cmp	w22, 0
	mov	w23, 256
	adrp	x24, .LANCHOR4
	csel	w28, w28, w23, eq
	add	x24, x24, :lo12:.LANCHOR4
	mov	w22, 0
.L1408:
	ldr	w0, [x24]
	ldr	w1, [x29, 140]
	add	w1, w1, w0
	mov	w0, w20
	bl	FlashReadCmd
	mov	w0, w20
	bl	NandcWaitFlashReady
	ldr	x0, [x19, 8]
	mov	w2, w25
	mov	w1, 0
	cmp	x0, 0
	add	x3, x0, 2048
	ldr	x0, [x19, 16]
	csel	x3, x3, xzr, ne
	cmp	x0, 0
	add	x4, x0, 8
	csel	x4, x4, xzr, ne
	mov	w0, w20
	bl	NandcXferData
	mov	w27, w0
	ldr	x0, [x29, 104]
	ldrb	w0, [x0]
	cbz	w0, .L1411
	mov	w0, w20
	bl	flash_read_ecc
	cmp	w0, 5
	csel	w27, w27, w23, ls
.L1411:
	cmp	w22, 9
	ccmn	w27, #1, 0, ls
	bne	.L1412
	add	w22, w22, 1
	b	.L1408
.L1412:
	cmp	w22, 0
	mov	w3, 256
	mov	w0, w20
	csel	w27, w27, w3, eq
	bl	NandcFlashDeCs
	adrp	x0, .LANCHOR33
	cmp	w28, w27
	csel	w5, w28, w27, cs
	ldrb	w2, [x0, #:lo12:.LANCHOR33]
	add	w0, w2, w2, lsl 1
	cmp	w5, w0, lsr 2
	bls	.L1414
	cmn	w5, #1
	csel	w5, w5, w3, eq
.L1414:
	cmp	w5, 256
	ldr	x0, [x19, 16]
	ccmn	w5, #1, 4, ne
	csel	w5, w5, wzr, eq
	str	w5, [x19]
	cbz	x0, .L1417
	ldr	w1, [x0, 12]
	cmn	w1, #1
	bne	.L1417
	ldr	w1, [x0, 8]
	cmn	w1, #1
	bne	.L1417
	ldr	w0, [x0]
	cmn	w0, #1
	beq	.L1417
	str	w1, [x19]
.L1417:
	ldr	w3, [x19]
	cmn	w3, #1
	bne	.L1403
	ldr	w1, [x19, 4]
	adrp	x0, .LC26
	add	x0, x0, :lo12:.LC26
	bl	printf
	ldr	x1, [x19, 8]
	cbz	x1, .L1419
	adrp	x0, .LC27
	mov	w3, 8
	mov	w2, 4
	add	x0, x0, :lo12:.LC27
	bl	rknand_print_hex
.L1419:
	ldr	x1, [x19, 16]
	cbz	x1, .L1403
	mov	w3, 4
	adrp	x0, .LC28
	mov	w2, w3
	add	x0, x0, :lo12:.LC28
	bl	rknand_print_hex
	b	.L1403
	.size	FlashReadSlc2KPages, .-FlashReadSlc2KPages
	.section	.text.FlashReadPages,"ax",@progbits
	.align	2
	.global	FlashReadPages
	.type	FlashReadPages, %function
FlashReadPages:
	stp	x29, x30, [sp, -176]!
	adrp	x3, .LANCHOR2
	add	x29, sp, 0
	ldrb	w3, [x3, #:lo12:.LANCHOR2]
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	stp	w2, w1, [x29, 148]
	cbnz	w3, .L1450
	mov	x25, x0
	adrp	x0, .LANCHOR31+9
	adrp	x27, .LANCHOR20
	mov	w23, 0
	ldrb	w0, [x0, #:lo12:.LANCHOR31+9]
	mov	w22, 0
	str	w0, [x29, 156]
	adrp	x0, .LANCHOR6
	str	x0, [x29, 128]
	ldrb	w1, [x0, #:lo12:.LANCHOR6]
	add	x0, x27, :lo12:.LANCHOR20
	str	w1, [x29, 144]
	str	x0, [x29, 104]
	add	x0, x0, 4
	str	x0, [x29, 96]
.L1451:
	ldr	w0, [x29, 152]
	cmp	w22, w0
	bcc	.L1485
	mov	w0, 0
	b	.L1449
.L1450:
	bl	FlashReadSlc2KPages
.L1449:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 176
	ret
.L1485:
	mov	w26, 56
	add	x3, x29, 168
	ldp	w1, w0, [x29, 148]
	umull	x26, w22, w26
	add	x2, x29, 172
	add	x21, x25, x26
	sub	w4, w0, w22
	mov	x0, x21
	ldr	w24, [x21, 4]
	bl	LogAddr2PhyAddr
	mov	w20, w0
	adrp	x0, .LANCHOR26
	ldr	w1, [x29, 168]
	ldrb	w0, [x0, #:lo12:.LANCHOR26]
	cmp	w0, w1
	bhi	.L1453
	mov	w0, -1
	str	w0, [x25, x26]
.L1454:
	add	w22, w22, 1
	b	.L1451
.L1453:
	adrp	x0, .LANCHOR27
	add	x0, x0, :lo12:.LANCHOR27
	ldrb	w19, [x0, w1, uxtw]
	adrp	x0, .LANCHOR210
	ldrb	w0, [x0, #:lo12:.LANCHOR210]
	cmp	w0, 0
	mov	w0, w19
	csel	w20, w20, wzr, ne
	bl	NandcWaitFlashReady
	adrp	x2, .LANCHOR7
	str	x2, [x29, 120]
	ldr	x0, [x2, #:lo12:.LANCHOR7]
	ldrb	w1, [x0, 19]
	sub	w0, w1, #1
	and	w0, w0, 255
	cmp	w0, 7
	bhi	.L1456
	add	x0, x27, :lo12:.LANCHOR20
	sxtw	x2, w19
	add	x0, x0, x2
	sub	w1, w1, #7
	and	w1, w1, 255
	cmp	w1, 1
	ldrb	w3, [x0, 12]
	bhi	.L1457
	ldrb	w3, [x0, 20]
.L1457:
	adrp	x0, .LANCHOR21
	add	x0, x0, :lo12:.LANCHOR21
	ldrb	w0, [x0, x2]
	cmp	w0, w3
	beq	.L1456
	ldp	x2, x0, [x29, 96]
	ldrb	w1, [x0, 1]
	mov	w0, w19
	bl	HynixSetRRPara
.L1456:
	mov	w0, w19
	bl	NandcFlashCs
	ldr	w0, [x29, 148]
	cmp	w0, 1
	cset	w0, eq
	orr	w24, w0, w24, lsr 31
	cbz	w24, .L1458
	adrp	x0, .LANCHOR16
	ldrb	w0, [x0, #:lo12:.LANCHOR16]
	cbz	w0, .L1458
	mov	w0, w19
	bl	flash_enter_slc_mode
.L1459:
	adrp	x0, .LANCHOR4
	add	x0, x0, :lo12:.LANCHOR4
	str	x0, [x29, 112]
	ldr	x0, [x29, 128]
	add	x0, x0, :lo12:.LANCHOR6
	str	x0, [x29, 136]
.L1465:
	ldr	w1, [x29, 172]
	cmn	w1, #1
	bne	.L1460
	cmp	w19, 255
	beq	.L1487
.L1460:
	cbz	w20, .L1462
	ldr	x0, [x29, 112]
	ldr	w2, [x0]
	mov	w0, w19
	add	w2, w1, w2
	bl	FlashReadDpCmd
.L1463:
	mov	w0, w19
	bl	NandcWaitFlashReady
	cbz	w20, .L1461
	ldr	w1, [x29, 172]
	mov	w0, w19
	bl	FlashReadDpDataOutCmd
.L1461:
	ldrb	w2, [x29, 156]
	mov	w1, 0
	ldp	x3, x4, [x21, 8]
	mov	w0, w19
	bl	NandcXferData
	mov	w28, w0
	ldr	x0, [x29, 136]
	ldrb	w0, [x0]
	cbz	w0, .L1464
	cmn	w28, #1
	bne	.L1464
	ldr	x0, [x29, 136]
	mov	w20, 0
	strb	wzr, [x0]
	b	.L1465
.L1458:
	mov	w0, w19
	bl	flash_exit_slc_mode
	b	.L1459
.L1462:
	mov	w0, w19
	bl	FlashReadCmd
	b	.L1463
.L1487:
	mov	w20, 0
	b	.L1461
.L1464:
	cbz	w20, .L1466
	adrp	x0, .LANCHOR4
	ldr	w1, [x29, 172]
	ldr	w0, [x0, #:lo12:.LANCHOR4]
	add	w1, w1, w0
	mov	w0, w19
	bl	FlashReadDpDataOutCmd
	add	w0, w22, 1
	mov	w1, 56
	ldrb	w2, [x29, 156]
	nop // between mem op and mult-accumulate
	umaddl	x0, w0, w1, x25
	mov	w1, 0
	ldp	x3, x4, [x0, 8]
	mov	w0, w19
	bl	NandcXferData
	cmn	w0, #1
	mov	w23, w0
	csel	w20, w20, wzr, ne
.L1466:
	mov	w0, w19
	bl	NandcFlashDeCs
	ldr	x0, [x29, 128]
	cmn	w28, #1
	ldrb	w1, [x29, 144]
	strb	w1, [x0, #:lo12:.LANCHOR6]
	bne	.L1467
	adrp	x0, .LANCHOR30
	ldrb	w0, [x0, #:lo12:.LANCHOR30]
	cbnz	w0, .L1468
.L1472:
	adrp	x20, .LANCHOR148
	ldr	x4, [x20, #:lo12:.LANCHOR148]
	cbnz	x4, .L1469
	ldr	w1, [x29, 172]
	mov	w0, w19
	ldp	x2, x3, [x21, 8]
	bl	FlashReadRawPage
	b	.L1524
.L1468:
	adrp	x0, .LANCHOR19
	ldr	w1, [x29, 172]
	ldp	x2, x3, [x21, 8]
	mov	w4, 1
	ldr	x0, [x0, #:lo12:.LANCHOR19]
	ldr	w20, [x0, 304]
	mov	w0, w19
	bl	FlashDdrTunningRead
	mov	w28, w0
	cmn	w0, #1
	beq	.L1471
	adrp	x0, .LANCHOR33
	ldrb	w0, [x0, #:lo12:.LANCHOR33]
	cmp	w28, w0, lsr 1
	bls	.L1488
.L1471:
	lsr	w0, w20, 8
	bl	NandcSetDdrPara
	cmn	w28, #1
	beq	.L1472
.L1488:
	mov	w20, 0
.L1467:
	adrp	x0, .LANCHOR33
	ldrb	w0, [x0, #:lo12:.LANCHOR33]
	add	w0, w0, w0, lsl 1
	cmp	w28, w0, lsr 2
	bls	.L1473
	adrp	x0, .LANCHOR148
	ldr	x0, [x0, #:lo12:.LANCHOR148]
	cmp	x0, 0
	mov	w0, 256
	csel	w28, w28, w0, ne
.L1473:
	cmp	w28, 256
	ccmn	w28, #1, 4, ne
	csel	w3, w28, wzr, eq
	str	w3, [x25, x26]
	cmn	w3, #1
	bne	.L1480
	adrp	x0, .LANCHOR33
	ldr	w1, [x21, 4]
	ldrb	w2, [x0, #:lo12:.LANCHOR33]
	adrp	x0, .LC26
	add	x0, x0, :lo12:.LC26
	bl	printf
	ldr	x1, [x21, 16]
	cbz	x1, .L1480
	mov	w3, 4
	adrp	x0, .LC28
	mov	w2, w3
	add	x0, x0, :lo12:.LC28
	bl	rknand_print_hex
.L1480:
	cbz	w20, .L1482
	adrp	x0, .LANCHOR33
	ldrb	w0, [x0, #:lo12:.LANCHOR33]
	add	w0, w0, w0, lsl 1
	cmp	w23, w0, lsr 2
	bls	.L1483
	adrp	x0, .LANCHOR148
	ldr	x0, [x0, #:lo12:.LANCHOR148]
	cmp	x0, 0
	mov	w0, 256
	csel	w23, w23, w0, ne
.L1483:
	add	w0, w22, 1
	mov	w1, 56
	cmp	w23, 256
	ccmn	w23, #1, 4, ne
	umull	x0, w0, w1
	csel	w1, w23, wzr, eq
	str	w1, [x25, x0]
.L1482:
	add	w22, w22, w20
	cbz	w24, .L1454
	adrp	x0, .LANCHOR16
	ldrb	w0, [x0, #:lo12:.LANCHOR16]
	cbz	w0, .L1454
	mov	w0, w19
	bl	flash_exit_slc_mode
	b	.L1454
.L1469:
	ldr	w1, [x29, 172]
	mov	w0, w19
	ldp	x2, x3, [x21, 8]
	blr	x4
	mov	w28, w0
	cmn	w0, #1
	bne	.L1491
	ldr	x0, [x29, 120]
	ldr	x0, [x0, #:lo12:.LANCHOR7]
	ldrb	w0, [x0, 19]
	sub	w0, w0, #1
	and	w0, w0, 255
	cmp	w0, 7
	bhi	.L1474
	add	x0, x27, :lo12:.LANCHOR20
	mov	w3, 0
	add	x2, x0, 4
	ldrb	w1, [x0, 1]
	mov	w0, w19
	bl	HynixSetRRPara
.L1474:
	ldp	x2, x3, [x21, 8]
	mov	w0, w19
	ldr	w1, [x29, 172]
	bl	FlashReadRawPage
	mov	w28, w0
	mov	w3, w0
	adrp	x0, .LANCHOR33
	ldr	w1, [x21, 4]
	ldrb	w2, [x0, #:lo12:.LANCHOR33]
	adrp	x0, .LC29
	add	x0, x0, :lo12:.LC29
	bl	printf
	cmn	w28, #1
	bne	.L1491
	adrp	x0, .LANCHOR16
	ldrb	w0, [x0, #:lo12:.LANCHOR16]
	cbz	w0, .L1491
	mov	w0, w19
	cbz	w24, .L1475
	bl	flash_enter_slc_mode
.L1476:
	ldr	x4, [x20, #:lo12:.LANCHOR148]
	mov	w0, w19
	ldr	w1, [x29, 172]
	ldp	x2, x3, [x21, 8]
	blr	x4
.L1524:
	mov	w28, w0
.L1491:
	mov	w20, 0
	b	.L1473
.L1475:
	bl	flash_exit_slc_mode
	b	.L1476
	.size	FlashReadPages, .-FlashReadPages
	.section	.text.FlashProgSlc2KPages,"ax",@progbits
	.align	2
	.global	FlashProgSlc2KPages
	.type	FlashProgSlc2KPages, %function
FlashProgSlc2KPages:
	stp	x29, x30, [sp, -160]!
	add	x29, sp, 0
	stp	x23, x24, [sp, 48]
	mov	w24, 56
	stp	x25, x26, [sp, 64]
	mov	w25, w2
	adrp	x2, .LANCHOR31+9
	stp	x21, x22, [sp, 32]
	nop // between mem op and mult-accumulate
	umaddl	x24, w1, w24, x0
	and	w22, w1, 255
	ldrb	w26, [x2, #:lo12:.LANCHOR31+9]
	mov	w23, w22
	stp	x27, x28, [sp, 80]
	mov	x21, x0
	stp	x19, x20, [sp, 16]
	adrp	x27, .LANCHOR4
	mov	x19, x0
	add	x28, x27, :lo12:.LANCHOR4
.L1526:
	cmp	x21, x24
	bne	.L1532
	adrp	x23, .LANCHOR206
	mov	x24, x23
.L1533:
	cmp	x19, x21
	bne	.L1540
	ldp	x19, x20, [sp, 16]
	mov	w0, 0
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 160
	ret
.L1532:
	mov	w1, w25
	mov	w4, w23
	add	x3, x29, 100
	add	x2, x29, 96
	mov	x0, x21
	bl	LogAddr2PhyAddr
	adrp	x0, .LANCHOR26
	ldr	w1, [x29, 100]
	ldrb	w0, [x0, #:lo12:.LANCHOR26]
	cmp	w0, w1
	bhi	.L1527
	mov	w0, -1
	str	w0, [x21]
.L1528:
	sub	w23, w23, #1
	add	x21, x21, 56
	and	w23, w23, 255
	b	.L1526
.L1527:
	adrp	x0, .LANCHOR27
	add	x0, x0, :lo12:.LANCHOR27
	ldrb	w20, [x0, w1, uxtw]
	mov	w0, w20
	bl	NandcWaitFlashReady
	mov	w0, w20
	bl	NandcFlashCs
	ldr	w1, [x29, 96]
	mov	w0, w20
	bl	FlashProgFirstCmd
	ldp	x3, x4, [x21, 8]
	mov	w2, w26
	mov	w1, 1
	mov	w0, w20
	bl	NandcXferData
	ldr	w1, [x29, 96]
	mov	w0, w20
	bl	FlashProgSecondCmd
	mov	w0, w20
	bl	NandcWaitFlashReady
	ldr	w1, [x29, 96]
	mov	w0, w20
	bl	FlashReadStatus
	sbfx	x0, x0, 0, 1
	str	w0, [x21]
	ldr	w1, [x29, 96]
	ldr	w0, [x27, #:lo12:.LANCHOR4]
	add	w1, w1, w0
	mov	w0, w20
	bl	FlashProgFirstCmd
	ldr	x0, [x21, 8]
	mov	w2, w26
	mov	w1, 1
	cmp	x0, 0
	add	x3, x0, 2048
	ldr	x0, [x21, 16]
	csel	x3, x3, xzr, ne
	cmp	x0, 0
	add	x4, x0, 8
	csel	x4, x4, xzr, ne
	mov	w0, w20
	bl	NandcXferData
	ldr	w0, [x28]
	ldr	w1, [x29, 96]
	add	w1, w1, w0
	mov	w0, w20
	bl	FlashProgSecondCmd
	mov	w0, w20
	bl	NandcWaitFlashReady
	ldr	w1, [x29, 96]
	mov	w0, w20
	bl	FlashReadStatus
	tbz	x0, 0, .L1531
	mov	w0, -1
	str	w0, [x21]
.L1531:
	mov	w0, w20
	bl	NandcFlashDeCs
	b	.L1528
.L1540:
	ldr	w0, [x19]
	cmn	w0, #1
	bne	.L1534
	ldr	w1, [x19, 4]
	adrp	x0, .LC30
	add	x0, x0, :lo12:.LC30
	bl	printf
.L1535:
	sub	w22, w22, #1
	add	x19, x19, 56
	and	w22, w22, 255
	b	.L1533
.L1534:
	adrp	x20, .LANCHOR207
	mov	w4, w22
	add	x3, x29, 100
	add	x2, x29, 96
	mov	w1, w25
	mov	x0, x19
	bl	LogAddr2PhyAddr
	ldr	x27, [x23, #:lo12:.LANCHOR206]
	ldr	x26, [x20, #:lo12:.LANCHOR207]
	mov	x2, 56
	mov	x1, x19
	add	x0, x29, 104
	str	wzr, [x27]
	str	wzr, [x26]
	bl	memcpy
	stp	x27, x26, [x29, 112]
	mov	w2, w25
	mov	w1, 1
	add	x0, x29, 104
	bl	FlashReadPages
	ldr	w26, [x29, 104]
	cmn	w26, #1
	bne	.L1536
	ldr	w1, [x19, 4]
	adrp	x0, .LC31
	add	x0, x0, :lo12:.LC31
	bl	printf
	str	w26, [x19]
.L1536:
	ldr	w26, [x29, 104]
	cmp	w26, 256
	bne	.L1537
	ldr	w1, [x19, 4]
	adrp	x0, .LC32
	add	x0, x0, :lo12:.LC32
	bl	printf
	str	w26, [x19]
.L1537:
	ldr	x0, [x19, 16]
	cbz	x0, .L1538
	ldr	w2, [x0]
	ldr	x0, [x20, #:lo12:.LANCHOR207]
	ldr	w3, [x0]
	cmp	w2, w3
	beq	.L1538
	ldr	w1, [x19, 4]
	adrp	x0, .LC33
	add	x0, x0, :lo12:.LC33
	bl	printf
	mov	w0, -1
	str	w0, [x19]
.L1538:
	ldr	x0, [x19, 8]
	cbz	x0, .L1535
	ldr	w2, [x0]
	ldr	x0, [x24, #:lo12:.LANCHOR206]
	ldr	w3, [x0]
	cmp	w2, w3
	beq	.L1535
	ldr	w1, [x19, 4]
	adrp	x0, .LC34
	add	x0, x0, :lo12:.LC34
	bl	printf
	mov	w0, -1
	str	w0, [x19]
	b	.L1535
	.size	FlashProgSlc2KPages, .-FlashProgSlc2KPages
	.section	.text.FlashProgPages,"ax",@progbits
	.align	2
	.global	FlashProgPages
	.type	FlashProgPages, %function
FlashProgPages:
	stp	x29, x30, [sp, -176]!
	adrp	x4, .LANCHOR7
	add	x29, sp, 0
	ldr	x4, [x4, #:lo12:.LANCHOR7]
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	ldrb	w4, [x4, 19]
	stp	w3, w4, [x29, 100]
	adrp	x4, .LANCHOR2
	ldrb	w4, [x4, #:lo12:.LANCHOR2]
	cbnz	w4, .L1554
	mov	x19, x0
	adrp	x0, .LANCHOR31+9
	adrp	x27, .LANCHOR23
	mov	w24, w1
	ldrb	w0, [x0, #:lo12:.LANCHOR31+9]
	mov	w22, w2
	add	x28, x27, :lo12:.LANCHOR23
	mov	w21, 0
	str	w0, [x29, 108]
.L1555:
	cmp	w21, w24
	adrp	x26, .LANCHOR26
	bcc	.L1568
	adrp	x21, .LANCHOR16
	adrp	x23, .LANCHOR23
	add	x25, x26, :lo12:.LANCHOR26
	add	x21, x21, :lo12:.LANCHOR16
	add	x23, x23, :lo12:.LANCHOR23
	mov	x20, 0
.L1569:
	ldrb	w0, [x25]
	cmp	w0, w20
	bhi	.L1571
	ldr	w0, [x29, 100]
	cbnz	w0, .L1572
.L1580:
	mov	w0, 0
	b	.L1553
.L1554:
	bl	FlashProgSlc2KPages
.L1553:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 176
	ret
.L1568:
	mov	w12, 56
	mov	w1, w22
	sub	w4, w24, w21
	add	x3, x29, 116
	umull	x12, w21, w12
	add	x2, x29, 112
	add	x25, x19, x12
	mov	x0, x25
	bl	LogAddr2PhyAddr
	mov	w23, w0
	ldrb	w1, [x26, #:lo12:.LANCHOR26]
	ldr	w0, [x29, 116]
	cmp	w1, w0
	bhi	.L1557
	mov	w0, -1
	str	w0, [x19, x12]
.L1558:
	add	w21, w21, 1
	b	.L1555
.L1557:
	adrp	x1, .LANCHOR28
	add	x2, x27, :lo12:.LANCHOR23
	mov	x3, 24
	ldrb	w1, [x1, #:lo12:.LANCHOR28]
	cmp	w1, 0
	uxtw	x1, w0
	csel	w23, w23, wzr, ne
	madd	x1, x1, x3, x2
	ldr	x1, [x1, 8]
	cbz	x1, .L1560
	bl	FlashWaitCmdDone
.L1560:
	ldp	w2, w1, [x29, 112]
	mov	x0, 24
	madd	x0, x1, x0, x28
	str	w2, [x0, 4]
	stp	x25, xzr, [x0, 8]
	cbz	w23, .L1561
	add	w2, w21, 1
	mov	w3, 56
	umaddl	x2, w2, w3, x19
	str	x2, [x0, 16]
.L1561:
	adrp	x0, .LANCHOR27
	add	x0, x0, :lo12:.LANCHOR27
	ldrb	w20, [x0, x1]
	mov	x0, 24
	mul	x1, x1, x0
	ldrb	w0, [x26, #:lo12:.LANCHOR26]
	cmp	w0, 1
	mov	w0, w20
	strb	w20, [x28, x1]
	bne	.L1562
	bl	NandcWaitFlashReady
.L1563:
	ldr	w0, [x29, 104]
	sub	w0, w0, #1
	cmp	w0, 7
	bhi	.L1564
	adrp	x0, .LANCHOR21
	add	x0, x0, :lo12:.LANCHOR21
	ldrb	w0, [x0, w20, sxtw]
	cbz	w0, .L1564
	adrp	x0, .LANCHOR20
	add	x0, x0, :lo12:.LANCHOR20
	add	x2, x0, 4
	mov	w3, 0
	ldrb	w1, [x0, 1]
	mov	w0, w20
	bl	HynixSetRRPara
.L1564:
	mov	w0, w20
	bl	NandcFlashCs
	cmp	w22, 1
	bne	.L1565
	adrp	x0, .LANCHOR16
	ldrb	w0, [x0, #:lo12:.LANCHOR16]
	cbz	w0, .L1565
	mov	w0, w20
	bl	flash_enter_slc_mode
.L1566:
	ldr	w1, [x29, 112]
	mov	w0, w20
	bl	FlashProgFirstCmd
	ldrb	w2, [x29, 108]
	mov	w1, 1
	ldp	x3, x4, [x25, 8]
	mov	w0, w20
	bl	NandcXferData
	cbz	w23, .L1567
	ldr	w1, [x29, 112]
	mov	w0, w20
	bl	FlashProgDpFirstCmd
	ldr	w1, [x29, 116]
	adrp	x0, .LANCHOR18
	add	x0, x0, :lo12:.LANCHOR18
	ldr	w0, [x0, x1, lsl 2]
	ldr	w1, [x29, 112]
	cmp	w0, 0
	mov	w0, w20
	cset	w2, ne
	bl	FlashWaitReadyEN
	adrp	x0, .LANCHOR4
	ldr	w1, [x29, 112]
	ldr	w0, [x0, #:lo12:.LANCHOR4]
	add	w1, w1, w0
	mov	w0, w20
	bl	FlashProgDpSecondCmd
	add	w0, w21, 1
	mov	w1, 56
	ldrb	w2, [x29, 108]
	nop // between mem op and mult-accumulate
	umaddl	x0, w0, w1, x19
	mov	w1, 1
	ldp	x3, x4, [x0, 8]
	mov	w0, w20
	bl	NandcXferData
.L1567:
	ldr	w1, [x29, 112]
	mov	w0, w20
	add	w21, w21, w23
	bl	FlashProgSecondCmd
	mov	w0, w20
	bl	NandcFlashDeCs
	b	.L1558
.L1562:
	bl	NandcFlashCs
	ldr	w1, [x29, 116]
	adrp	x0, .LANCHOR18
	add	x0, x0, :lo12:.LANCHOR18
	ldr	w0, [x0, x1, lsl 2]
	ldr	w1, [x29, 112]
	cmp	w0, 0
	mov	w0, w20
	cset	w2, ne
	bl	FlashWaitReadyEN
	mov	w0, w20
	bl	NandcFlashDeCs
	b	.L1563
.L1565:
	mov	w0, w20
	bl	flash_exit_slc_mode
	b	.L1566
.L1571:
	mov	w0, w20
	bl	FlashWaitCmdDone
	cmp	w22, 1
	bne	.L1570
	ldrb	w0, [x21]
	cbz	w0, .L1570
	mov	x0, 24
	mul	x0, x20, x0
	ldrb	w0, [x0, x23]
	bl	flash_exit_slc_mode
.L1570:
	add	x20, x20, 1
	b	.L1569
.L1572:
	mov	w0, 56
	and	w20, w24, 255
	adrp	x23, .LANCHOR206
	mov	x25, x23
	umaddl	x24, w24, w0, x19
.L1573:
	cmp	x24, x19
	beq	.L1580
	ldr	w0, [x19]
	cmn	w0, #1
	bne	.L1574
	ldr	w1, [x19, 4]
	adrp	x0, .LC30
	add	x0, x0, :lo12:.LC30
	bl	printf
.L1575:
	sub	w20, w20, #1
	add	x19, x19, 56
	and	w20, w20, 255
	b	.L1573
.L1574:
	adrp	x21, .LANCHOR207
	mov	w4, w20
	add	x3, x29, 116
	add	x2, x29, 112
	mov	w1, w22
	mov	x0, x19
	bl	LogAddr2PhyAddr
	ldr	x27, [x23, #:lo12:.LANCHOR206]
	ldr	x26, [x21, #:lo12:.LANCHOR207]
	mov	x2, 56
	mov	x1, x19
	add	x0, x29, 120
	str	wzr, [x27]
	str	wzr, [x26]
	bl	memcpy
	stp	x27, x26, [x29, 128]
	mov	w2, w22
	mov	w1, 1
	add	x0, x29, 120
	bl	FlashReadPages
	ldr	w26, [x29, 120]
	cmn	w26, #1
	bne	.L1576
	ldr	w1, [x19, 4]
	adrp	x0, .LC31
	add	x0, x0, :lo12:.LC31
	bl	printf
	str	w26, [x19]
.L1576:
	ldr	x0, [x19, 16]
	cbz	x0, .L1577
	ldr	w2, [x0]
	ldr	x0, [x21, #:lo12:.LANCHOR207]
	ldr	w3, [x0]
	cmp	w2, w3
	beq	.L1577
	ldr	w1, [x19, 4]
	adrp	x0, .LC33
	add	x0, x0, :lo12:.LC33
	bl	printf
	mov	w0, -1
	str	w0, [x19]
.L1577:
	ldr	x0, [x19, 8]
	cbz	x0, .L1575
	ldr	w2, [x0]
	ldr	x0, [x25, #:lo12:.LANCHOR206]
	ldr	w3, [x0]
	cmp	w2, w3
	beq	.L1575
	ldr	w1, [x19, 4]
	adrp	x0, .LC34
	add	x0, x0, :lo12:.LC34
	bl	printf
	mov	w0, -1
	str	w0, [x19]
	b	.L1575
	.size	FlashProgPages, .-FlashProgPages
	.section	.text.FlashTestBlk,"ax",@progbits
	.align	2
	.global	FlashTestBlk
	.type	FlashTestBlk, %function
FlashTestBlk:
	stp	x29, x30, [sp, -160]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	and	w19, w0, 65535
	adrp	x0, .LANCHOR156
	ldr	w0, [x0, #:lo12:.LANCHOR156]
	cmp	w19, w0
	bcc	.L1608
	adrp	x20, .LANCHOR152
	mov	w2, 32
	mov	w1, 165
	lsl	w19, w19, 10
	ldr	x0, [x20, #:lo12:.LANCHOR152]
	str	x0, [x29, 48]
	add	x0, x29, 96
	str	x0, [x29, 56]
	bl	ftl_memset
	ldr	x0, [x20, #:lo12:.LANCHOR152]
	mov	w2, 8
	mov	w1, 90
	bl	ftl_memset
	str	w19, [x29, 44]
	mov	w2, 1
	add	x0, x29, 40
	mov	w1, w2
	bl	FlashEraseBlocks
	mov	w3, 1
	add	x0, x29, 40
	mov	w2, w3
	mov	w1, w3
	bl	FlashProgPages
	ldr	w0, [x29, 40]
	mov	w2, 1
	mov	w1, 0
	cmp	w0, 0
	add	x0, x29, 40
	csetm	w19, ne
	bl	FlashEraseBlocks
.L1606:
	mov	w0, w19
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 160
	ret
.L1608:
	mov	w19, 0
	b	.L1606
	.size	FlashTestBlk, .-FlashTestBlk
	.section	.text.FtlLowFormatEraseBlock,"ax",@progbits
	.align	2
	.global	FtlLowFormatEraseBlock
	.type	FtlLowFormatEraseBlock, %function
FtlLowFormatEraseBlock:
	stp	x29, x30, [sp, -144]!
	add	x29, sp, 0
	stp	x25, x26, [sp, 64]
	and	w26, w0, 65535
	adrp	x0, .LANCHOR78
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	ldr	w0, [x0, #:lo12:.LANCHOR78]
	stp	x23, x24, [sp, 48]
	stp	x27, x28, [sp, 80]
	cbnz	w0, .L1633
	adrp	x23, .LANCHOR28
	and	w25, w1, 255
	adrp	x20, .LANCHOR16
	adrp	x1, .LANCHOR38
	ldrb	w0, [x23, #:lo12:.LANCHOR28]
	adrp	x21, .LANCHOR79
	str	w0, [x29, 136]
	mov	x8, 56
	adrp	x0, .LANCHOR75
	ldrb	w10, [x20, #:lo12:.LANCHOR16]
	ldrh	w11, [x1, #:lo12:.LANCHOR38]
	adrp	x7, .LANCHOR47
	str	w26, [x0, #:lo12:.LANCHOR75]
	adrp	x0, .LANCHOR196
	ldr	x6, [x21, #:lo12:.LANCHOR79]
	add	x7, x7, :lo12:.LANCHOR47
	ldr	x12, [x0, #:lo12:.LANCHOR196]
	adrp	x0, .LANCHOR58
	mov	w14, w8
	mov	x5, 0
	ldrh	w13, [x0, #:lo12:.LANCHOR58]
	mov	w24, 0
	mov	w19, 0
	str	x1, [x29, 128]
	str	x0, [x29, 120]
.L1612:
	cmp	w11, w5, uxth
	bhi	.L1616
	cbz	w24, .L1610
	cmp	w10, 0
	mov	w2, w24
	cset	w22, ne
	strb	wzr, [x23, #:lo12:.LANCHOR28]
	mov	w1, w22
	mov	x0, x6
	bl	FlashEraseBlocks
	mov	x27, 0
	ldrb	w0, [x29, 136]
	strb	w0, [x23, #:lo12:.LANCHOR28]
	mov	w0, 56
	umull	x24, w24, w0
.L1619:
	ldr	x0, [x21, #:lo12:.LANCHOR79]
	add	x1, x0, x27
	ldr	w0, [x0, x27]
	cmn	w0, #1
	bne	.L1618
	ldr	w0, [x1, 4]
	add	w19, w19, 1
	and	w19, w19, 65535
	lsr	w0, w0, 10
	bl	FtlBbmMapBadBlock
.L1618:
	add	x27, x27, 56
	cmp	x27, x24
	bne	.L1619
	cbnz	w25, .L1620
	and	w22, w22, 65535
	mov	w28, 6
	mov	w27, 1
.L1621:
	adrp	x0, .LANCHOR47
	mov	w24, 0
	add	x0, x0, :lo12:.LANCHOR47
	str	x0, [x29, 112]
.L1629:
	ldr	x0, [x29, 128]
	mov	x5, 0
	ldr	x6, [x21, #:lo12:.LANCHOR79]
	mov	w20, 0
	mov	w12, 56
	ldrh	w7, [x0, #:lo12:.LANCHOR38]
	adrp	x0, .LANCHOR193
	ldr	x8, [x0, #:lo12:.LANCHOR193]
	adrp	x0, .LANCHOR194
	ldr	x10, [x0, #:lo12:.LANCHOR194]
	ldr	x0, [x29, 120]
	ldrh	w11, [x0, #:lo12:.LANCHOR58]
.L1622:
	cmp	w7, w5, uxth
	bhi	.L1625
	cbz	w20, .L1610
	mov	w2, w22
	mov	w1, w20
	strb	wzr, [x23, #:lo12:.LANCHOR28]
	mov	w3, 1
	mov	x0, x6
	bl	FlashProgPages
	mov	w1, 56
	ldrb	w0, [x29, 136]
	strb	w0, [x23, #:lo12:.LANCHOR28]
	mov	x2, 0
	umull	x1, w20, w1
.L1628:
	ldr	x0, [x21, #:lo12:.LANCHOR79]
	add	x3, x0, x2
	ldr	w0, [x0, x2]
	cbz	w0, .L1627
	ldr	w0, [x3, 4]
	add	w19, w19, 1
	stp	x2, x1, [x29, 96]
	and	w19, w19, 65535
	lsr	w0, w0, 10
	bl	FtlBbmMapBadBlock
	ldp	x2, x1, [x29, 96]
.L1627:
	add	x2, x2, 56
	cmp	x1, x2
	bne	.L1628
	add	w24, w24, w28
	and	w24, w24, 65535
	cmp	w27, w24
	bhi	.L1629
	mov	x23, 0
.L1631:
	cbz	w25, .L1630
	ldr	x0, [x21, #:lo12:.LANCHOR79]
	add	x1, x0, x23
	ldr	w0, [x0, x23]
	cbnz	w0, .L1630
	ldr	w0, [x1, 4]
	mov	w1, 1
	str	x2, [x29, 136]
	lsr	w0, w0, 10
	bl	FtlFreeSysBlkQueueIn
	ldr	x2, [x29, 136]
.L1630:
	add	x23, x23, 56
	cmp	x23, x2
	bne	.L1631
	cmp	w26, 63
	ccmp	w25, 0, 0, hi
	beq	.L1610
	ldr	x0, [x21, #:lo12:.LANCHOR79]
	mov	w2, w20
	mov	w1, w22
	bl	FlashEraseBlocks
.L1610:
	mov	w0, w19
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 144
	ret
.L1616:
	mul	x0, x5, x8
	mov	w1, w26
	str	wzr, [x6, x0]
	ldrb	w0, [x7, x5]
	bl	V2P_block
	and	w15, w0, 65535
	mov	w22, w15
	cbz	w25, .L1613
	bl	IsBlkInVendorPart
	cbnz	w0, .L1614
.L1613:
	mov	w0, w22
	bl	FtlBbmIsBadBlock
	cbnz	w0, .L1615
	umaddl	x1, w24, w14, x6
	lsl	w15, w15, 10
	mul	w0, w24, w13
	add	w24, w24, 1
	and	w24, w24, 65535
	asr	w0, w0, 2
	str	w15, [x1, 4]
	add	x0, x12, x0, sxtw 2
	stp	xzr, x0, [x1, 8]
.L1614:
	add	x5, x5, 1
	b	.L1612
.L1615:
	add	w19, w19, 1
	and	w19, w19, 65535
	b	.L1614
.L1620:
	adrp	x0, .LANCHOR53
	ldrh	w27, [x0, #:lo12:.LANCHOR53]
	ldrb	w0, [x20, #:lo12:.LANCHOR16]
	cbnz	w0, .L1634
	lsr	w28, w27, 2
	mov	w22, 1
	b	.L1621
.L1634:
	mov	w22, 1
	mov	w28, w22
	b	.L1621
.L1625:
	mov	x0, 56
	mov	w1, w26
	mul	x0, x5, x0
	str	wzr, [x6, x0]
	ldr	x0, [x29, 112]
	ldrb	w0, [x0, x5]
	bl	V2P_block
	and	w13, w0, 65535
	mov	w14, w13
	cbz	w25, .L1623
	bl	IsBlkInVendorPart
	cbnz	w0, .L1624
.L1623:
	mov	w0, w14
	bl	FtlBbmIsBadBlock
	cbnz	w0, .L1624
	umaddl	x1, w20, w12, x6
	add	w13, w24, w13, lsl 10
	mul	w0, w20, w11
	add	w20, w20, 1
	and	w20, w20, 65535
	asr	w0, w0, 2
	str	w13, [x1, 4]
	add	x0, x10, x0, sxtw 2
	stp	x8, x0, [x1, 8]
.L1624:
	add	x5, x5, 1
	b	.L1622
.L1633:
	mov	w19, 0
	b	.L1610
	.size	FtlLowFormatEraseBlock, .-FtlLowFormatEraseBlock
	.section	.text.FtlBbmTblFlush,"ax",@progbits
	.align	2
	.global	FtlBbmTblFlush
	.type	FtlBbmTblFlush, %function
FtlBbmTblFlush:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x21, x22, [sp, 32]
	adrp	x22, .LANCHOR78
	stp	x19, x20, [sp, 16]
	ldr	w0, [x22, #:lo12:.LANCHOR78]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	cbnz	w0, .L1657
	adrp	x24, .LANCHOR195
	adrp	x23, .LANCHOR189
	adrp	x20, .LANCHOR211
	add	x19, x20, :lo12:.LANCHOR211
	ldr	x1, [x24, #:lo12:.LANCHOR195]
	adrp	x21, .LANCHOR76
	ldr	x0, [x23, #:lo12:.LANCHOR189]
	add	x26, x21, :lo12:.LANCHOR76
	stp	x0, x1, [x19, 8]
	adrp	x1, .LANCHOR57
	adrp	x27, .LANCHOR45
	adrp	x28, .LANCHOR126
	ldrh	w2, [x1, #:lo12:.LANCHOR57]
	add	x26, x26, 32
	mov	w25, 0
	add	x27, x27, :lo12:.LANCHOR45
	add	x28, x28, :lo12:.LANCHOR126
	mov	w1, 0
	bl	ftl_memset
.L1658:
	ldrh	w0, [x27]
	cmp	w25, w0
	blt	.L1659
	add	x20, x20, :lo12:.LANCHOR211
	add	x19, x21, :lo12:.LANCHOR76
	mov	w2, 16
	mov	w1, 255
	adrp	x26, .LC35
	adrp	x27, .LANCHOR53
	ldr	x28, [x20, 16]
	add	x26, x26, :lo12:.LC35
	add	x27, x27, :lo12:.LANCHOR53
	mov	w25, 0
	mov	x0, x28
	bl	ftl_memset
	mov	w0, -3887
	strh	w0, [x28]
	ldr	w0, [x19, 8]
	str	w0, [x28, 4]
	ldrh	w0, [x21, #:lo12:.LANCHOR76]
	mov	w21, 0
	strh	w0, [x28, 2]
	ldrh	w0, [x19, 4]
	strh	w0, [x28, 8]
	ldrh	w0, [x19, 6]
	strh	w0, [x28, 10]
	adrp	x0, .LANCHOR37
	ldr	w0, [x0, #:lo12:.LANCHOR37]
	strh	w0, [x28, 12]
.L1660:
	ldrh	w1, [x19]
	ldrh	w4, [x28, 10]
	ldrh	w2, [x19, 2]
	ldrh	w3, [x19, 4]
	ldr	x0, [x23, #:lo12:.LANCHOR189]
	str	x0, [x20, 8]
	ldr	x0, [x24, #:lo12:.LANCHOR195]
	str	x0, [x20, 16]
	orr	w0, w2, w1, lsl 10
	str	wzr, [x20]
	str	w0, [x20, 4]
	mov	x0, x26
	bl	printf
	ldrh	w0, [x27]
	ldrh	w1, [x19, 2]
	sub	w0, w0, #1
	cmp	w1, w0
	blt	.L1661
	ldr	w0, [x19, 8]
	mov	w2, 1
	ldrh	w1, [x19, 4]
	add	w0, w0, 1
	str	w0, [x19, 8]
	str	w0, [x28, 4]
	ldrh	w0, [x19]
	strh	w0, [x28, 8]
	strh	w0, [x19, 4]
	adrp	x0, .LANCHOR79
	strh	w1, [x19]
	lsl	w1, w1, 10
	ldr	x0, [x0, #:lo12:.LANCHOR79]
	str	w1, [x20, 4]
	strh	wzr, [x19, 2]
	str	w1, [x0, 4]
	mov	w1, w2
	bl	FlashEraseBlocks
.L1661:
	mov	w3, 1
	mov	x0, x20
	mov	w2, w3
	mov	w1, w3
	bl	FlashProgPages
	ldrh	w0, [x19, 2]
	add	w0, w0, 1
	strh	w0, [x19, 2]
	ldr	w0, [x20]
	cmn	w0, #1
	bne	.L1662
	ldr	w1, [x20, 4]
	add	w21, w21, 1
	adrp	x0, .LC36
	and	w21, w21, 65535
	add	x0, x0, :lo12:.LC36
	bl	printf
	cmp	w21, 3
	bls	.L1660
	ldr	w1, [x20, 4]
	mov	w2, w21
	adrp	x0, .LC37
	add	x0, x0, :lo12:.LC37
	bl	printf
	mov	w0, 1
	str	w0, [x22, #:lo12:.LANCHOR78]
.L1657:
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 96
	ret
.L1659:
	ldrh	w2, [x28]
	ldr	x1, [x26], 8
	ldr	x0, [x19, 8]
	mul	w3, w2, w25
	lsl	w2, w2, 2
	add	w25, w25, 1
	add	x0, x0, x3, sxtw 2
	bl	ftl_memcpy
	b	.L1658
.L1662:
	add	w25, w25, 1
	cmp	w25, 1
	beq	.L1660
	cmp	w0, 256
	beq	.L1660
	b	.L1657
	.size	FtlBbmTblFlush, .-FtlBbmTblFlush
	.section	.text.allocate_data_superblock,"ax",@progbits
	.align	2
	.global	allocate_data_superblock
	.type	allocate_data_superblock, %function
allocate_data_superblock:
	adrp	x1, .LANCHOR78
	ldr	w1, [x1, #:lo12:.LANCHOR78]
	cbnz	w1, .L1736
	stp	x29, x30, [sp, -128]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	stp	x27, x28, [sp, 80]
	adrp	x27, .LANCHOR87
	add	x0, x27, :lo12:.LANCHOR87
	stp	x23, x24, [sp, 48]
	str	x0, [x29, 120]
	adrp	x0, .LANCHOR90
	add	x23, x0, :lo12:.LANCHOR90
	stp	x21, x22, [sp, 32]
	stp	x25, x26, [sp, 64]
.L1727:
	ldr	x1, [x29, 120]
	adrp	x0, .LANCHOR90
	adrp	x24, .LANCHOR40
	ldrh	w0, [x0, #:lo12:.LANCHOR90]
	ldrh	w1, [x1]
	add	w0, w0, w1
	ldrh	w1, [x24, #:lo12:.LANCHOR40]
	cmp	w0, w1
	ble	.L1675
	mov	w2, 3507
	adrp	x1, .LANCHOR212
	adrp	x0, .LC5
	add	x1, x1, :lo12:.LANCHOR212
	add	x0, x0, :lo12:.LC5
	bl	printf
	adrp	x1, .LC6
	adrp	x0, .LC7
	add	x1, x1, :lo12:.LC6
	add	x0, x0, :lo12:.LC7
	bl	printf
.L1675:
	adrp	x0, .LANCHOR95
	add	x0, x0, :lo12:.LANCHOR95
	cmp	x19, x0
	bne	.L1676
	adrp	x1, .LANCHOR177
	ldrh	w2, [x23]
	ldr	w3, [x1, #:lo12:.LANCHOR177]
	lsr	w0, w2, 1
	add	w4, w0, 1
	mul	w1, w2, w3
	add	w1, w4, w1, lsr 2
	adrp	x4, .LANCHOR104
	and	w1, w1, 65535
	ldr	w4, [x4, #:lo12:.LANCHOR104]
	cbz	w4, .L1677
	adrp	x4, .LANCHOR175
	ldr	w4, [x4, #:lo12:.LANCHOR175]
	cmp	w4, 39
	bhi	.L1677
	cmp	w4, 2
	bls	.L1711
	tbz	x2, 0, .L1707
	cbz	w3, .L1711
.L1707:
	mov	w1, w0
	b	.L1677
.L1676:
	ldrb	w0, [x19, 8]
	cmp	w0, 1
	bne	.L1711
	adrp	x0, .LANCHOR44
	ldrh	w0, [x0, #:lo12:.LANCHOR44]
	cmp	w0, 1
	beq	.L1711
	adrp	x0, .LANCHOR16
	ldrb	w0, [x0, #:lo12:.LANCHOR16]
	cbnz	w0, .L1711
	adrp	x2, .LANCHOR104
	ldrh	w0, [x23]
	ldr	w2, [x2, #:lo12:.LANCHOR104]
	lsr	w1, w0, 3
	cbz	w2, .L1677
	adrp	x2, .LANCHOR175
	ldr	w2, [x2, #:lo12:.LANCHOR175]
	cmp	w2, 1
	bhi	.L1677
	mov	w1, 7
	mul	w1, w0, w1
	lsr	w1, w1, 3
.L1677:
	cbz	w1, .L1678
	sub	w1, w1, #1
	and	w1, w1, 65535
.L1678:
	ldrb	w2, [x19, 8]
	adrp	x0, .LANCHOR89
	add	x0, x0, :lo12:.LANCHOR89
	bl	List_pop_index_node
	and	w22, w0, 65535
	ldrh	w0, [x23]
	cbnz	w0, .L1679
	mov	w2, 3532
	adrp	x1, .LANCHOR212
	adrp	x0, .LC5
	add	x1, x1, :lo12:.LANCHOR212
	add	x0, x0, :lo12:.LC5
	bl	printf
	adrp	x1, .LC6
	adrp	x0, .LC7
	add	x1, x1, :lo12:.LC6
	add	x0, x0, :lo12:.LC7
	bl	printf
.L1679:
	ldrh	w0, [x23]
	sub	w0, w0, #1
	strh	w0, [x23]
	ldrh	w0, [x24, #:lo12:.LANCHOR40]
	cmp	w0, w22
	bls	.L1727
	adrp	x25, .LANCHOR85
	ubfiz	x21, x22, 1, 16
	ldr	x0, [x25, #:lo12:.LANCHOR85]
	ldrh	w20, [x0, x21]
	cbnz	w20, .L1727
	strh	w22, [x19]
	mov	x0, x19
	bl	make_superblock
	ldrb	w0, [x19, 7]
	cbnz	w0, .L1681
	ldr	x0, [x25, #:lo12:.LANCHOR85]
	mov	w1, -1
	strh	w1, [x0, x21]
	ldrh	w1, [x27, #:lo12:.LANCHOR87]
	ldrh	w0, [x23]
	add	w0, w0, w1
	ldrh	w1, [x24, #:lo12:.LANCHOR40]
	cmp	w0, w1
	ble	.L1727
	mov	w2, 3552
	adrp	x1, .LANCHOR212
	adrp	x0, .LC5
	add	x1, x1, :lo12:.LANCHOR212
	add	x0, x0, :lo12:.LC5
	bl	printf
	adrp	x1, .LC6
	adrp	x0, .LC7
	add	x1, x1, :lo12:.LC6
	add	x0, x0, :lo12:.LC7
	bl	printf
	b	.L1727
.L1711:
	mov	w1, 0
	b	.L1678
.L1681:
	ldrh	w1, [x27, #:lo12:.LANCHOR87]
	ldrh	w0, [x23]
	add	w0, w0, w1
	ldrh	w1, [x24, #:lo12:.LANCHOR40]
	cmp	w0, w1
	ble	.L1683
	mov	w2, 3556
	adrp	x1, .LANCHOR212
	adrp	x0, .LC5
	add	x1, x1, :lo12:.LANCHOR212
	add	x0, x0, :lo12:.LC5
	bl	printf
	adrp	x1, .LC6
	adrp	x0, .LC7
	add	x1, x1, :lo12:.LC6
	add	x0, x0, :lo12:.LC7
	bl	printf
.L1683:
	adrp	x1, .LANCHOR38
	adrp	x25, .LANCHOR79
	mov	w2, 56
	mov	x3, 8
	ldrh	w1, [x1, #:lo12:.LANCHOR38]
	add	x26, x19, 16
	ldr	x4, [x25, #:lo12:.LANCHOR79]
	mov	x5, x26
	mov	w6, 65535
	add	x0, x4, 8
	umaddl	x1, w2, w1, x3
	add	x1, x4, x1
.L1684:
	cmp	x1, x0
	bne	.L1686
	cbnz	w20, .L1687
	mov	w2, 3571
	adrp	x1, .LANCHOR212
	adrp	x0, .LC5
	add	x1, x1, :lo12:.LANCHOR212
	add	x0, x0, :lo12:.LC5
	bl	printf
	adrp	x1, .LC6
	adrp	x0, .LC7
	add	x1, x1, :lo12:.LC6
	add	x0, x0, :lo12:.LC7
	bl	printf
.L1687:
	adrp	x0, .LANCHOR104
	adrp	x28, .LANCHOR80
	ldr	w0, [x0, #:lo12:.LANCHOR104]
	cbz	w0, .L1688
	adrp	x0, .LANCHOR93
	add	x0, x0, :lo12:.LANCHOR93
	cmp	x19, x0
	bne	.L1688
	ldr	x0, [x28, #:lo12:.LANCHOR80]
	ldrh	w0, [x0, x21]
	cmp	w0, 40
	bls	.L1688
	strb	wzr, [x19, 8]
.L1688:
	adrp	x0, .LANCHOR213
	ldrh	w0, [x0, #:lo12:.LANCHOR213]
	cmp	w0, w22
	bne	.L1689
	mov	w2, 3578
	adrp	x1, .LANCHOR212
	adrp	x0, .LC5
	add	x1, x1, :lo12:.LANCHOR212
	add	x0, x0, :lo12:.LC5
	bl	printf
	adrp	x1, .LC6
	adrp	x0, .LC7
	add	x1, x1, :lo12:.LC6
	add	x0, x0, :lo12:.LC7
	bl	printf
.L1689:
	ldrb	w0, [x19, 8]
	adrp	x6, .LANCHOR48
	adrp	x5, .LANCHOR172
	adrp	x4, .LANCHOR173
	ldr	x1, [x28, #:lo12:.LANCHOR80]
	cbnz	w0, .L1690
	ldrh	w0, [x1, x21]
	cbz	w0, .L1691
	ldrh	w2, [x6, #:lo12:.LANCHOR48]
	add	w0, w0, w2
.L1739:
	strh	w0, [x1, x21]
	mov	w1, 0
	ldr	w0, [x5, #:lo12:.LANCHOR172]
	add	w0, w0, 1
	str	w0, [x5, #:lo12:.LANCHOR172]
	mov	w0, w22
	bl	ftl_set_blk_mode
.L1693:
	ldr	x0, [x28, #:lo12:.LANCHOR80]
	ldrh	w1, [x0, x21]
	adrp	x0, .LANCHOR174
	ldr	w2, [x0, #:lo12:.LANCHOR174]
	cmp	w1, w2
	bls	.L1694
	str	w1, [x0, #:lo12:.LANCHOR174]
.L1694:
	ldr	w2, [x5, #:lo12:.LANCHOR172]
	mov	x3, 4
	ldr	w1, [x4, #:lo12:.LANCHOR173]
	ldrh	w0, [x6, #:lo12:.LANCHOR48]
	madd	w0, w0, w2, w1
	ldrh	w1, [x24, #:lo12:.LANCHOR40]
	udiv	w0, w0, w1
	adrp	x1, .LANCHOR214
	str	w0, [x1, #:lo12:.LANCHOR214]
	adrp	x0, .LANCHOR199
	ldr	x1, [x0, #:lo12:.LANCHOR199]
	ldr	w0, [x1, 16]
	add	w0, w0, 1
	str	w0, [x1, 16]
	mov	w1, 56
	ldr	x0, [x25, #:lo12:.LANCHOR79]
	nop // between mem op and mult-accumulate
	umaddl	x1, w1, w20, x3
	add	x2, x0, 4
	add	x1, x0, x1
.L1695:
	cmp	x1, x2
	bne	.L1696
	adrp	x1, .LANCHOR16
	ldrb	w1, [x1, #:lo12:.LANCHOR16]
	cbz	w1, .L1697
	ldrb	w1, [x19, 8]
	mov	w2, w20
	cmp	w1, 1
	bne	.L1698
	mov	w1, 0
.L1740:
	bl	FlashEraseBlocks
.L1697:
	ldrb	w1, [x19, 8]
	mov	w2, w20
	ldr	x0, [x25, #:lo12:.LANCHOR79]
	mov	x24, 0
	bl	FlashEraseBlocks
	mov	w1, 0
	mov	x3, 56
.L1699:
	cmp	w20, w24, uxth
	bhi	.L1701
	cbz	w1, .L1702
	mov	w0, w22
	bl	update_multiplier_value
	bl	FtlBbmTblFlush
.L1702:
	ldrb	w0, [x19, 7]
	cbnz	w0, .L1703
	adrp	x0, .LANCHOR85
	mov	w1, -1
	ldr	x0, [x0, #:lo12:.LANCHOR85]
	strh	w1, [x0, x21]
	b	.L1727
.L1686:
	ldrh	w3, [x5]
	stp	xzr, xzr, [x0]
	cmp	w3, w6
	beq	.L1685
	umaddl	x7, w20, w2, x4
	add	w20, w20, 1
	and	w20, w20, 65535
	lsl	w3, w3, 10
	str	w3, [x7, 4]
.L1685:
	add	x0, x0, 56
	add	x5, x5, 2
	b	.L1684
.L1691:
	mov	w0, 2
	b	.L1739
.L1690:
	ldrh	w0, [x1, x21]
	add	w0, w0, 1
	strh	w0, [x1, x21]
	ldr	w0, [x4, #:lo12:.LANCHOR173]
	add	w0, w0, 1
	str	w0, [x4, #:lo12:.LANCHOR173]
	mov	w0, w22
	bl	ftl_set_blk_mode.part.11
	b	.L1693
.L1696:
	ldr	w3, [x2]
	and	w3, w3, -1024
	str	w3, [x2], 56
	b	.L1695
.L1698:
	mov	w1, 1
	b	.L1740
.L1701:
	mul	x0, x24, x3
	ldr	x2, [x25, #:lo12:.LANCHOR79]
	add	x4, x2, x0
	ldr	w2, [x2, x0]
	cmn	w2, #1
	bne	.L1700
	add	w1, w1, 1
	ldr	w0, [x4, 4]
	str	x3, [x29, 104]
	stp	w2, w1, [x29, 112]
	lsr	w0, w0, 10
	bl	FtlBbmMapBadBlock
	ldp	w2, w1, [x29, 112]
	strh	w2, [x26]
	ldr	x3, [x29, 104]
	ldrb	w0, [x19, 7]
	sub	w0, w0, #1
	strb	w0, [x19, 7]
.L1700:
	add	x24, x24, 1
	add	x26, x26, 2
	b	.L1699
.L1703:
	adrp	x1, .LANCHOR52
	adrp	x2, .LANCHOR164
	strh	wzr, [x19, 2]
	ldrh	w1, [x1, #:lo12:.LANCHOR52]
	strh	w22, [x19]
	strb	wzr, [x19, 6]
	mul	w0, w0, w1
	ldr	w1, [x2, #:lo12:.LANCHOR164]
	str	w1, [x19, 12]
	add	w1, w1, 1
	str	w1, [x2, #:lo12:.LANCHOR164]
	adrp	x1, .LANCHOR85
	and	w0, w0, 65535
	strh	w0, [x19, 4]
	ldr	x1, [x1, #:lo12:.LANCHOR85]
	strh	w0, [x1, x21]
	ldrh	w0, [x19, 4]
	cbz	w0, .L1704
	ldrb	w0, [x19, 7]
	cbnz	w0, .L1674
.L1704:
	mov	w2, 3642
	adrp	x1, .LANCHOR212
	adrp	x0, .LC5
	add	x1, x1, :lo12:.LANCHOR212
	add	x0, x0, :lo12:.LC5
	bl	printf
	adrp	x1, .LC6
	adrp	x0, .LC7
	add	x1, x1, :lo12:.LC6
	add	x0, x0, :lo12:.LC7
	bl	printf
.L1674:
	ldp	x19, x20, [sp, 16]
	mov	w0, 0
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 128
	ret
.L1736:
	mov	w0, 0
	ret
	.size	allocate_data_superblock, .-allocate_data_superblock
	.section	.text.FtlGcFreeBadSuperBlk,"ax",@progbits
	.align	2
	.global	FtlGcFreeBadSuperBlk
	.type	FtlGcFreeBadSuperBlk, %function
FtlGcFreeBadSuperBlk:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x21, x22, [sp, 32]
	adrp	x21, .LANCHOR119
	stp	x25, x26, [sp, 64]
	and	w25, w0, 65535
	ldrh	w0, [x21, #:lo12:.LANCHOR119]
	stp	x19, x20, [sp, 16]
	stp	x23, x24, [sp, 48]
	str	x27, [sp, 80]
	cbz	w0, .L1742
	adrp	x23, .LANCHOR120
	add	x24, x23, :lo12:.LANCHOR120
	mov	w19, 0
.L1743:
	adrp	x0, .LANCHOR38
	ldrh	w0, [x0, #:lo12:.LANCHOR38]
	cmp	w0, w19
	bhi	.L1749
	bl	FtlGcReFreshBadBlk
.L1742:
	mov	w0, 0
	ldr	x27, [sp, 80]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 96
	ret
.L1749:
	adrp	x0, .LANCHOR47
	add	x0, x0, :lo12:.LANCHOR47
	mov	w1, w25
	add	x22, x21, :lo12:.LANCHOR119
	mov	w20, 0
	ldrb	w0, [x0, w19, sxtw]
	bl	V2P_block
	and	w26, w0, 65535
.L1744:
	ldrh	w0, [x22]
	cmp	w0, w20
	bhi	.L1748
	add	w19, w19, 1
	and	w19, w19, 65535
	b	.L1743
.L1748:
	add	x0, x23, :lo12:.LANCHOR120
	add	w27, w20, 1
	ldrh	w0, [x0, w20, sxtw 1]
	cmp	w0, w26
	bne	.L1745
	mov	w0, w26
	bl	FtlBbmMapBadBlock
	bl	FtlBbmTblFlush
	ldrh	w1, [x22]
	sxtw	x3, w27
	and	x4, x20, 65535
	mov	x0, 0
.L1746:
	add	w2, w20, w0
	cmp	w1, w2, uxth
	bhi	.L1747
	sub	w1, w1, #1
	strh	w1, [x22]
.L1745:
	and	w20, w27, 65535
	b	.L1744
.L1747:
	add	x2, x3, x0
	ldrh	w5, [x24, x2, lsl 1]
	add	x2, x4, x0
	add	x0, x0, 1
	strh	w5, [x24, x2, lsl 1]
	b	.L1746
	.size	FtlGcFreeBadSuperBlk, .-FtlGcFreeBadSuperBlk
	.section	.text.update_vpc_list,"ax",@progbits
	.align	2
	.global	update_vpc_list
	.type	update_vpc_list, %function
update_vpc_list:
	stp	x29, x30, [sp, -32]!
	adrp	x1, .LANCHOR85
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	and	w19, w0, 65535
	ldr	x1, [x1, #:lo12:.LANCHOR85]
	ubfiz	x0, x19, 1, 16
	ldrh	w0, [x1, x0]
	cbnz	w0, .L1755
	adrp	x0, .LANCHOR213
	ldrh	w1, [x0, #:lo12:.LANCHOR213]
	cmp	w1, w19
	bne	.L1756
	mov	w1, -1
	strh	w1, [x0, #:lo12:.LANCHOR213]
.L1757:
	adrp	x20, .LANCHOR87
	mov	w1, w19
	adrp	x0, .LANCHOR84
	add	x0, x0, :lo12:.LANCHOR84
	bl	List_remove_node
	ldrh	w0, [x20, #:lo12:.LANCHOR87]
	cbnz	w0, .L1759
	mov	w2, 3767
	adrp	x1, .LANCHOR215
	adrp	x0, .LC5
	add	x1, x1, :lo12:.LANCHOR215
	add	x0, x0, :lo12:.LC5
	bl	printf
	adrp	x1, .LC6
	adrp	x0, .LC7
	add	x1, x1, :lo12:.LC6
	add	x0, x0, :lo12:.LC7
	bl	printf
.L1759:
	ldrh	w0, [x20, #:lo12:.LANCHOR87]
	sub	w0, w0, #1
	strh	w0, [x20, #:lo12:.LANCHOR87]
	mov	w0, w19
	bl	free_data_superblock
	mov	w0, w19
	bl	FtlGcFreeBadSuperBlk
	adrp	x0, .LANCHOR90
	ldrh	w1, [x20, #:lo12:.LANCHOR87]
	ldrh	w0, [x0, #:lo12:.LANCHOR90]
	add	w0, w0, w1
	adrp	x1, .LANCHOR40
	ldrh	w1, [x1, #:lo12:.LANCHOR40]
	cmp	w0, w1
	ble	.L1763
	mov	w2, 3770
	adrp	x1, .LANCHOR215
	adrp	x0, .LC5
	add	x1, x1, :lo12:.LANCHOR215
	add	x0, x0, :lo12:.LC5
	bl	printf
	adrp	x1, .LC6
	adrp	x0, .LC7
	add	x1, x1, :lo12:.LC6
	add	x0, x0, :lo12:.LC7
	bl	printf
.L1763:
	mov	w0, 1
	b	.L1754
.L1756:
	adrp	x0, .LANCHOR93
	ldrh	w0, [x0, #:lo12:.LANCHOR93]
	cmp	w0, w19
	beq	.L1762
	adrp	x0, .LANCHOR94
	ldrh	w0, [x0, #:lo12:.LANCHOR94]
	cmp	w0, w19
	beq	.L1762
	adrp	x0, .LANCHOR95
	ldrh	w0, [x0, #:lo12:.LANCHOR95]
	cmp	w0, w19
	bne	.L1757
.L1762:
	mov	w0, 0
.L1754:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L1755:
	mov	w0, w19
	bl	List_update_data_list
	b	.L1762
	.size	update_vpc_list, .-update_vpc_list
	.section	.text.decrement_vpc_count,"ax",@progbits
	.align	2
	.global	decrement_vpc_count
	.type	decrement_vpc_count, %function
decrement_vpc_count:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	and	w19, w0, 65535
	stp	x21, x22, [sp, 32]
	mov	w0, 65535
	cmp	w19, w0
	beq	.L1766
	adrp	x20, .LANCHOR85
	ubfiz	x21, x19, 1, 16
	ldr	x1, [x20, #:lo12:.LANCHOR85]
	ldrh	w0, [x1, x21]
	cbnz	w0, .L1767
	mov	w2, 0
	mov	w1, w19
	adrp	x0, .LC38
	add	x0, x0, :lo12:.LC38
	bl	printf
	ldr	x0, [x20, #:lo12:.LANCHOR85]
	ldrh	w0, [x0, x21]
	cbnz	w0, .L1768
	mov	w2, 3786
	adrp	x1, .LANCHOR216
	adrp	x0, .LC5
	add	x1, x1, :lo12:.LANCHOR216
	add	x0, x0, :lo12:.LC5
	bl	printf
	adrp	x1, .LC6
	adrp	x0, .LC7
	add	x1, x1, :lo12:.LC6
	add	x0, x0, :lo12:.LC7
	bl	printf
.L1768:
	ldr	x0, [x20, #:lo12:.LANCHOR85]
	adrp	x6, .LANCHOR89
	add	x6, x6, :lo12:.LANCHOR89
	mov	w1, 32
	strh	w1, [x0, x21]
	mov	w1, w19
	mov	x0, x6
	bl	test_node_in_list
	cbz	w0, .L1769
	adrp	x22, .LANCHOR90
	mov	w1, w19
	mov	x0, x6
	bl	List_remove_node
	ldrh	w0, [x22, #:lo12:.LANCHOR90]
	cbnz	w0, .L1770
	mov	w2, 3792
	adrp	x1, .LANCHOR216
	adrp	x0, .LC5
	add	x1, x1, :lo12:.LANCHOR216
	add	x0, x0, :lo12:.LC5
	bl	printf
	adrp	x1, .LC6
	adrp	x0, .LC7
	add	x1, x1, :lo12:.LC6
	add	x0, x0, :lo12:.LC7
	bl	printf
.L1770:
	ldrh	w0, [x22, #:lo12:.LANCHOR90]
	sub	w0, w0, #1
	strh	w0, [x22, #:lo12:.LANCHOR90]
	mov	w0, w19
	bl	INSERT_DATA_LIST
	ldr	x0, [x20, #:lo12:.LANCHOR85]
	mov	w1, w19
	ldrh	w2, [x0, x21]
	adrp	x0, .LC39
	add	x0, x0, :lo12:.LC39
	bl	printf
.L1769:
	mov	w0, w19
	bl	FtlGcRefreshBlock
.L1773:
	mov	w20, 0
	b	.L1765
.L1767:
	sub	w0, w0, #1
	strh	w0, [x1, x21]
.L1766:
	adrp	x21, .LANCHOR136
	mov	w1, 65535
	ldrh	w0, [x21, #:lo12:.LANCHOR136]
	cmp	w0, w1
	bne	.L1772
	strh	w19, [x21, #:lo12:.LANCHOR136]
	b	.L1773
.L1772:
	cmp	w19, w0
	beq	.L1773
	bl	update_vpc_list
	cmp	w0, 0
	adrp	x1, .LANCHOR83
	adrp	x0, .LANCHOR84
	strh	w19, [x21, #:lo12:.LANCHOR136]
	cset	w20, ne
	ldr	x1, [x1, #:lo12:.LANCHOR83]
	ldr	x0, [x0, #:lo12:.LANCHOR84]
	sub	x0, x0, x1
	mov	x1, -6148914691236517206
	asr	x0, x0, 1
	movk	x1, 0xaaab, lsl 0
	mul	x0, x0, x1
	adrp	x1, .LANCHOR85
	ldr	x1, [x1, #:lo12:.LANCHOR85]
	and	x2, x0, 65535
	ldrh	w1, [x1, x2, lsl 1]
	cbnz	w1, .L1765
	cmp	w19, w0, uxth
	beq	.L1765
	mov	w2, 3816
	adrp	x1, .LANCHOR216
	adrp	x0, .LC5
	add	x1, x1, :lo12:.LANCHOR216
	add	x0, x0, :lo12:.LC5
	bl	printf
	adrp	x1, .LC6
	adrp	x0, .LC7
	add	x1, x1, :lo12:.LC6
	add	x0, x0, :lo12:.LC7
	bl	printf
.L1765:
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	decrement_vpc_count, .-decrement_vpc_count
	.section	.text.FtlSlcSuperblockCheck,"ax",@progbits
	.align	2
	.global	FtlSlcSuperblockCheck
	.type	FtlSlcSuperblockCheck, %function
FtlSlcSuperblockCheck:
	ldrh	w1, [x0, 4]
	cbz	w1, .L1790
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w20, 65535
	ldrh	w1, [x0]
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	cmp	w1, w20
	beq	.L1778
	mov	x19, x0
	ldrb	w0, [x0, 6]
	adrp	x22, .LANCHOR16
	adrp	x21, .LANCHOR123
	add	x0, x0, 8
	add	x23, x22, :lo12:.LANCHOR16
	add	x21, x21, :lo12:.LANCHOR123
	ldrh	w0, [x19, x0, lsl 1]
.L1782:
	cmp	w0, w20
	beq	.L1784
	ldrb	w0, [x19, 8]
	cmp	w0, 1
	bne	.L1785
	ldrb	w1, [x23]
	cbnz	w1, .L1785
	ldrh	w1, [x19, 2]
	ldrh	w1, [x21, x1, lsl 1]
	cmp	w1, w20
	bne	.L1785
	ldrh	w0, [x19, 4]
	sub	w0, w0, #1
	strh	w0, [x19, 4]
	ldrh	w0, [x19]
	bl	decrement_vpc_count
	ldrh	w0, [x19, 4]
	cbnz	w0, .L1784
	ldrh	w0, [x19, 2]
	add	w0, w0, 1
.L1793:
	strh	w0, [x19, 2]
	strb	wzr, [x19, 6]
.L1778:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
.L1784:
	ldrb	w0, [x19, 6]
	adrp	x1, .LANCHOR38
	add	w0, w0, 1
	ldrh	w1, [x1, #:lo12:.LANCHOR38]
	and	w0, w0, 255
	strb	w0, [x19, 6]
	cmp	w1, w0
	bne	.L1783
	ldrh	w0, [x19, 2]
	strb	wzr, [x19, 6]
	add	w0, w0, 1
	strh	w0, [x19, 2]
.L1783:
	ldrb	w0, [x19, 6]
	add	x0, x0, 8
	ldrh	w0, [x19, x0, lsl 1]
	b	.L1782
.L1785:
	ldrb	w1, [x22, #:lo12:.LANCHOR16]
	cbz	w1, .L1778
	cmp	w0, 1
	bne	.L1778
	adrp	x0, .LANCHOR53
	ldrh	w1, [x19, 2]
	ldrh	w0, [x0, #:lo12:.LANCHOR53]
	cmp	w1, w0
	bcc	.L1778
	ldrh	w0, [x19]
	adrp	x1, .LANCHOR85
	ldrh	w3, [x19, 4]
	ldr	x2, [x1, #:lo12:.LANCHOR85]
	lsl	x0, x0, 1
	ldrh	w1, [x2, x0]
	sub	w1, w1, w3
	strh	w1, [x2, x0]
	adrp	x0, .LANCHOR52
	strh	wzr, [x19, 4]
	ldrh	w0, [x0, #:lo12:.LANCHOR52]
	b	.L1793
.L1790:
	ret
	.size	FtlSlcSuperblockCheck, .-FtlSlcSuperblockCheck
	.section	.text.get_new_active_ppa,"ax",@progbits
	.align	2
	.global	get_new_active_ppa
	.type	get_new_active_ppa, %function
get_new_active_ppa:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	ldrh	w1, [x0]
	mov	w0, 65535
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	cmp	w1, w0
	str	x25, [sp, 64]
	bne	.L1795
	mov	w2, 3700
	adrp	x1, .LANCHOR217
	adrp	x0, .LC5
	add	x1, x1, :lo12:.LANCHOR217
	add	x0, x0, :lo12:.LC5
	bl	printf
	adrp	x1, .LC6
	adrp	x0, .LC7
	add	x1, x1, :lo12:.LC6
	add	x0, x0, :lo12:.LC7
	bl	printf
.L1795:
	adrp	x20, .LANCHOR52
	ldrh	w1, [x19, 2]
	ldrh	w0, [x20, #:lo12:.LANCHOR52]
	cmp	w1, w0
	bne	.L1796
	mov	w2, 3701
	adrp	x1, .LANCHOR217
	adrp	x0, .LC5
	add	x1, x1, :lo12:.LANCHOR217
	add	x0, x0, :lo12:.LC5
	bl	printf
	adrp	x1, .LC6
	adrp	x0, .LC7
	add	x1, x1, :lo12:.LC6
	add	x0, x0, :lo12:.LC7
	bl	printf
.L1796:
	ldrh	w0, [x19, 4]
	cbnz	w0, .L1797
	mov	w2, 3702
	adrp	x1, .LANCHOR217
	adrp	x0, .LC5
	add	x1, x1, :lo12:.LANCHOR217
	add	x0, x0, :lo12:.LC5
	bl	printf
	adrp	x1, .LC6
	adrp	x0, .LC7
	add	x1, x1, :lo12:.LC6
	add	x0, x0, :lo12:.LC7
	bl	printf
.L1797:
	ldrb	w0, [x19, 6]
	adrp	x21, .LANCHOR38
	strb	wzr, [x19, 10]
	adrp	x23, .LANCHOR16
	add	x0, x0, 8
	adrp	x24, .LANCHOR123
	add	x23, x23, :lo12:.LANCHOR16
	add	x24, x24, :lo12:.LANCHOR123
	add	x25, x21, :lo12:.LANCHOR38
	ldrh	w22, [x19, x0, lsl 1]
.L1798:
	mov	w2, 65535
	cmp	w22, w2
	beq	.L1799
	ldrb	w0, [x19, 8]
	ldrh	w1, [x19, 4]
	cmp	w0, 1
	ldrh	w0, [x19, 2]
	bne	.L1801
	ldrb	w3, [x23]
	cbnz	w3, .L1801
	ldrh	w3, [x24, w0, sxtw 1]
	cmp	w3, w2
	bne	.L1801
	ldrh	w0, [x19]
	sub	w1, w1, #1
	strh	w1, [x19, 4]
	bl	decrement_vpc_count
.L1799:
	ldrb	w0, [x19, 6]
	ldrh	w1, [x25]
	add	w0, w0, 1
	and	w0, w0, 255
	strb	w0, [x19, 6]
	cmp	w1, w0
	bne	.L1800
	ldrh	w0, [x19, 2]
	strb	wzr, [x19, 6]
	add	w0, w0, 1
	strh	w0, [x19, 2]
.L1800:
	ldrb	w0, [x19, 6]
	add	x0, x0, 8
	ldrh	w22, [x19, x0, lsl 1]
	b	.L1798
.L1801:
	adrp	x23, .LANCHOR16
	adrp	x24, .LANCHOR123
	orr	w22, w0, w22, lsl 10
	add	x23, x23, :lo12:.LANCHOR16
	add	x24, x24, :lo12:.LANCHOR123
	sub	w1, w1, #1
	strh	w1, [x19, 4]
.L1802:
	ldrb	w0, [x19, 6]
	mov	w1, 65535
	ldrh	w3, [x21, #:lo12:.LANCHOR38]
.L1804:
	add	w0, w0, 1
	and	w0, w0, 255
	cmp	w0, w3
	bne	.L1803
	ldrh	w0, [x19, 2]
	add	w0, w0, 1
	strh	w0, [x19, 2]
	mov	w0, 0
.L1803:
	add	x2, x19, x0, sxtw 1
	ldrh	w2, [x2, 16]
	cmp	w2, w1
	beq	.L1804
	strb	w0, [x19, 6]
	ldrb	w0, [x19, 8]
	cmp	w0, 1
	bne	.L1805
	ldrb	w2, [x23]
	ldrh	w0, [x19, 2]
	cbnz	w2, .L1806
	ldrh	w0, [x24, w0, sxtw 1]
	cmp	w0, w1
	bne	.L1805
	ldrh	w0, [x19, 4]
	cbz	w0, .L1805
	sub	w0, w0, #1
	strh	w0, [x19, 4]
	ldrh	w0, [x19]
	bl	decrement_vpc_count
	b	.L1802
.L1806:
	adrp	x1, .LANCHOR53
	ldrh	w1, [x1, #:lo12:.LANCHOR53]
	cmp	w0, w1
	bcc	.L1805
	ldrh	w0, [x19]
	adrp	x1, .LANCHOR85
	ldrh	w3, [x19, 4]
	ldr	x2, [x1, #:lo12:.LANCHOR85]
	lsl	x0, x0, 1
	ldrh	w1, [x2, x0]
	sub	w1, w1, w3
	strh	w1, [x2, x0]
	strh	wzr, [x19, 4]
	ldrh	w0, [x20, #:lo12:.LANCHOR52]
	strh	w0, [x19, 2]
	strb	wzr, [x19, 6]
.L1805:
	ldrh	w1, [x19, 2]
	ldrh	w0, [x20, #:lo12:.LANCHOR52]
	cmp	w1, w0
	bne	.L1794
	ldrh	w0, [x19, 4]
	cbz	w0, .L1794
	mov	w2, 3752
	adrp	x1, .LANCHOR217
	adrp	x0, .LC5
	add	x1, x1, :lo12:.LANCHOR217
	add	x0, x0, :lo12:.LC5
	bl	printf
	adrp	x1, .LC6
	adrp	x0, .LC7
	add	x1, x1, :lo12:.LC6
	add	x0, x0, :lo12:.LC7
	bl	printf
.L1794:
	mov	w0, w22
	ldr	x25, [sp, 64]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
	.size	get_new_active_ppa, .-get_new_active_ppa
	.section	.text.FtlVpcTblFlush,"ax",@progbits
	.align	2
	.global	FtlVpcTblFlush
	.type	FtlVpcTblFlush, %function
FtlVpcTblFlush:
	stp	x29, x30, [sp, -128]!
	adrp	x0, .LANCHOR78
	add	x29, sp, 0
	ldr	w1, [x0, #:lo12:.LANCHOR78]
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	str	x0, [x29, 112]
	cbnz	w1, .L1819
	adrp	x25, .LANCHOR195
	adrp	x27, .LANCHOR218
	adrp	x23, .LANCHOR189
	adrp	x20, .LANCHOR211
	ldr	x19, [x25, #:lo12:.LANCHOR195]
	add	x22, x20, :lo12:.LANCHOR211
	ldr	x0, [x23, #:lo12:.LANCHOR189]
	add	x1, x27, :lo12:.LANCHOR218
	ldrh	w2, [x27, #:lo12:.LANCHOR218]
	mov	w3, 19539
	stp	x0, x19, [x22, 8]
	movk	w3, 0x4654, lsl 16
	strh	w2, [x19, 2]
	mov	w2, -3932
	strh	w2, [x19]
	adrp	x24, .LANCHOR164
	ldr	w2, [x1, 8]
	adrp	x26, .LANCHOR57
	ldrh	w1, [x1, 6]
	stp	w2, wzr, [x19, 4]
	adrp	x2, .LANCHOR82
	add	x21, x2, :lo12:.LANCHOR82
	str	wzr, [x19, 12]
	str	w3, [x2, #:lo12:.LANCHOR82]
	mov	w2, 99
	movk	w2, 0x5000, lsl 16
	strh	w1, [x21, 8]
	adrp	x1, .LANCHOR45
	str	w2, [x21, 4]
	adrp	x2, .LANCHOR93
	ldrh	w1, [x1, #:lo12:.LANCHOR45]
	strb	w1, [x21, 10]
	add	x1, x2, :lo12:.LANCHOR93
	ldrh	w2, [x2, #:lo12:.LANCHOR93]
	strh	w2, [x21, 14]
	ldrb	w3, [x1, 6]
	ldrh	w2, [x1, 2]
	ldrb	w1, [x1, 8]
	strb	w1, [x21, 11]
	orr	w2, w3, w2, lsl 6
	strh	w2, [x21, 16]
	adrp	x2, .LANCHOR94
	add	x1, x2, :lo12:.LANCHOR94
	ldrh	w2, [x2, #:lo12:.LANCHOR94]
	ldrb	w3, [x1, 6]
	strh	w2, [x21, 18]
	ldrh	w2, [x1, 2]
	ldrb	w1, [x1, 8]
	strb	w1, [x21, 12]
	orr	w2, w3, w2, lsl 6
	strh	w2, [x21, 20]
	adrp	x2, .LANCHOR95
	add	x1, x2, :lo12:.LANCHOR95
	ldrh	w2, [x2, #:lo12:.LANCHOR95]
	strh	w2, [x21, 22]
	ldrb	w3, [x1, 6]
	ldrh	w2, [x1, 2]
	ldrb	w1, [x1, 8]
	strb	w1, [x21, 13]
	adrp	x1, .LANCHOR172
	orr	w2, w3, w2, lsl 6
	strh	w2, [x21, 24]
	ldr	w1, [x1, #:lo12:.LANCHOR172]
	str	w1, [x21, 32]
	ldr	w1, [x24, #:lo12:.LANCHOR164]
	str	w1, [x21, 40]
	adrp	x1, .LANCHOR165
	ldrh	w2, [x26, #:lo12:.LANCHOR57]
	ldr	w1, [x1, #:lo12:.LANCHOR165]
	str	w1, [x21, 36]
	adrp	x1, .LANCHOR115
	ldrh	w1, [x1, #:lo12:.LANCHOR115]
	strh	w1, [x21, 44]
	adrp	x1, .LANCHOR116
	ldrh	w1, [x1, #:lo12:.LANCHOR116]
	strh	w1, [x21, 46]
	mov	w1, 255
	bl	ftl_memset
	ldr	x0, [x22, 8]
	mov	x1, x21
	mov	w2, 48
	adrp	x21, .LANCHOR40
	bl	ftl_memcpy
	adrp	x1, .LANCHOR85
	ldrh	w2, [x21, #:lo12:.LANCHOR40]
	ldr	x0, [x22, 8]
	ldr	x1, [x1, #:lo12:.LANCHOR85]
	lsl	w2, w2, 1
	add	x0, x0, 48
	bl	ftl_memcpy
	ldrh	w0, [x21, #:lo12:.LANCHOR40]
	adrp	x1, .LANCHOR1
	ldr	x3, [x22, 8]
	ldr	x1, [x1, #:lo12:.LANCHOR1]
	lsr	w2, w0, 3
	ubfiz	x0, x0, 1, 16
	add	x0, x0, 51
	add	w2, w2, 4
	and	x0, x0, -4
	add	x0, x3, x0
	bl	ftl_memcpy
	adrp	x0, .LANCHOR69
	str	x26, [x29, 104]
	ldrh	w0, [x0, #:lo12:.LANCHOR69]
	cbz	w0, .L1820
	ldrh	w0, [x21, #:lo12:.LANCHOR40]
	adrp	x1, .LANCHOR66
	ldr	x3, [x22, 8]
	ldrh	w2, [x1, #:lo12:.LANCHOR66]
	lsr	w1, w0, 3
	add	w0, w1, w0, lsl 1
	adrp	x1, .LANCHOR134
	add	w0, w0, 52
	lsl	w2, w2, 2
	ldr	x1, [x1, #:lo12:.LANCHOR134]
	and	x0, x0, 65532
	add	x0, x3, x0
	bl	ftl_memcpy
.L1820:
	mov	w0, 0
	bl	FtlUpdateVaildLpn
	adrp	x0, .LANCHOR2
	add	x22, x20, :lo12:.LANCHOR211
	add	x0, x0, :lo12:.LANCHOR2
	add	x28, x27, :lo12:.LANCHOR218
	str	x0, [x29, 120]
	adrp	x27, .LANCHOR53
	mov	w21, 0
	add	x0, x27, :lo12:.LANCHOR53
	mov	w26, 65535
	str	x0, [x29, 96]
.L1821:
	ldrh	w2, [x28, 2]
	ldrh	w1, [x28]
	ldr	x0, [x23, #:lo12:.LANCHOR189]
	str	x0, [x22, 8]
	ldr	x0, [x25, #:lo12:.LANCHOR195]
	str	x0, [x22, 16]
	orr	w0, w2, w1, lsl 10
	str	w0, [x22, 4]
	ldrh	w0, [x27, #:lo12:.LANCHOR53]
	sub	w0, w0, #1
	cmp	w2, w0
	blt	.L1822
	ldrh	w26, [x28, 4]
	strh	wzr, [x28, 2]
	strh	w1, [x28, 4]
	bl	FtlFreeSysBlkQueueOut
	ldr	w1, [x24, #:lo12:.LANCHOR164]
	str	w1, [x28, 8]
	add	w2, w1, 1
	str	w2, [x24, #:lo12:.LANCHOR164]
	ubfiz	w2, w0, 10, 16
	str	w2, [x22, 4]
	strh	w0, [x28]
	strh	w0, [x19, 2]
	str	w1, [x19, 4]
.L1822:
	ldr	x0, [x29, 120]
	ldrb	w0, [x0]
	cbz	w0, .L1823
	ldr	x0, [x29, 104]
	ldrh	w1, [x0, #:lo12:.LANCHOR57]
	ldr	x0, [x23, #:lo12:.LANCHOR189]
	bl	js_hash
	str	w0, [x19, 12]
.L1823:
	mov	w3, 1
	mov	x0, x22
	mov	w1, w3
	mov	w2, w3
	bl	FlashProgPages
	ldrh	w0, [x28, 2]
	ldr	w1, [x22]
	add	w0, w0, 1
	and	w0, w0, 65535
	strh	w0, [x28, 2]
	cmn	w1, #1
	bne	.L1824
	cmp	w0, 1
	bne	.L1825
	mov	w2, 1375
	adrp	x1, .LANCHOR219
	adrp	x0, .LC5
	add	x1, x1, :lo12:.LANCHOR219
	add	x0, x0, :lo12:.LC5
	bl	printf
	adrp	x1, .LC6
	adrp	x0, .LC7
	add	x1, x1, :lo12:.LC6
	add	x0, x0, :lo12:.LC7
	bl	printf
.L1825:
	ldrh	w0, [x28, 2]
	cmp	w0, 1
	bne	.L1826
	ldr	x0, [x29, 96]
	ldrh	w0, [x0]
	sub	w0, w0, #1
	strh	w0, [x28, 2]
.L1826:
	add	w21, w21, 1
	and	w21, w21, 65535
	cmp	w21, 3
	bls	.L1821
	add	x20, x20, :lo12:.LANCHOR211
	mov	w2, w21
	adrp	x0, .LC40
	add	x0, x0, :lo12:.LC40
	ldr	w1, [x20, 4]
	bl	printf
	ldr	x1, [x29, 112]
	mov	w0, 1
	str	w0, [x1, #:lo12:.LANCHOR78]
.L1819:
	ldp	x19, x20, [sp, 16]
	mov	w0, 0
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 128
	ret
.L1824:
	cmp	w0, 1
	beq	.L1821
	cmp	w1, 256
	beq	.L1821
	mov	w0, 65535
	cmp	w26, w0
	beq	.L1819
	mov	w1, 1
	mov	w0, w26
	bl	FtlFreeSysBlkQueueIn
	b	.L1819
	.size	FtlVpcTblFlush, .-FtlVpcTblFlush
	.section	.text.FtlSuperblockPowerLostFix,"ax",@progbits
	.align	2
	.global	FtlSuperblockPowerLostFix
	.type	FtlSuperblockPowerLostFix, %function
FtlSuperblockPowerLostFix:
	stp	x29, x30, [sp, -128]!
	adrp	x1, .LANCHOR78
	add	x29, sp, 0
	str	x23, [sp, 48]
	ldr	w23, [x1, #:lo12:.LANCHOR78]
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	cbnz	w23, .L1842
	adrp	x1, .LANCHOR16
	ldrb	w1, [x1, #:lo12:.LANCHOR16]
	cbz	w1, .L1853
	ldrb	w1, [x0, 8]
	cmp	w1, 1
	bne	.L1853
	ldrh	w21, [x0, 4]
	mov	w23, w1
.L1844:
	adrp	x1, .LANCHOR195
	mov	x19, x0
	mov	w0, -1
	str	w0, [x29, 96]
	ldr	x20, [x1, #:lo12:.LANCHOR195]
	adrp	x0, .LANCHOR189
	str	x20, [x29, 88]
	mov	w1, -3
	ldr	x0, [x0, #:lo12:.LANCHOR189]
	adrp	x22, .LANCHOR165
	str	x0, [x29, 80]
	add	x22, x22, :lo12:.LANCHOR165
	str	w1, [x20, 8]
	mov	w1, -2
	str	w1, [x20, 12]
	ldrh	w1, [x19]
	strh	w1, [x20, 2]
	strh	wzr, [x20]
	mov	w1, 61589
	str	w1, [x0]
	mov	w1, 22136
	movk	w1, 0x1234, lsl 16
	str	w1, [x0, 4]
.L1845:
	sub	w21, w21, #1
	cmn	w21, #1
	beq	.L1848
	ldrh	w0, [x19, 4]
	cbnz	w0, .L1846
.L1848:
	ldrh	w0, [x19]
	adrp	x1, .LANCHOR85
	ldrh	w3, [x19, 4]
	ldr	x2, [x1, #:lo12:.LANCHOR85]
	lsl	x0, x0, 1
	ldrh	w1, [x2, x0]
	sub	w1, w1, w3
	strh	w1, [x2, x0]
	adrp	x0, .LANCHOR52
	strb	wzr, [x19, 6]
	strh	wzr, [x19, 4]
	ldrh	w0, [x0, #:lo12:.LANCHOR52]
	strh	w0, [x19, 2]
.L1842:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 128
	ret
.L1853:
	mov	w21, 12
	b	.L1844
.L1846:
	mov	x0, x19
	bl	get_new_active_ppa
	str	w0, [x29, 76]
	cmn	w0, #1
	beq	.L1848
	ldr	w0, [x22]
	mov	w3, 0
	str	w0, [x20, 4]
	mov	w2, w23
	add	w0, w0, 1
	mov	w1, 1
	cmn	w0, #1
	csel	w0, w0, wzr, ne
	str	w0, [x22]
	add	x0, x29, 72
	bl	FlashProgPages
	ldrh	w0, [x19]
	bl	decrement_vpc_count
	b	.L1845
	.size	FtlSuperblockPowerLostFix, .-FtlSuperblockPowerLostFix
	.section	.text.FtlLoadFactoryBbt,"ax",@progbits
	.align	2
	.global	FtlLoadFactoryBbt
	.type	FtlLoadFactoryBbt, %function
FtlLoadFactoryBbt:
	stp	x29, x30, [sp, -112]!
	adrp	x2, .LANCHOR189
	adrp	x0, .LANCHOR211
	add	x1, x0, :lo12:.LANCHOR211
	add	x29, sp, 0
	ldr	x2, [x2, #:lo12:.LANCHOR189]
	stp	x21, x22, [sp, 32]
	mov	x22, x0
	stp	x25, x26, [sp, 64]
	adrp	x26, .LANCHOR51
	stp	x27, x28, [sp, 80]
	add	x28, x26, :lo12:.LANCHOR51
	stp	x19, x20, [sp, 16]
	adrp	x20, .LANCHOR76
	stp	x23, x24, [sp, 48]
	add	x20, x20, :lo12:.LANCHOR76
	str	x2, [x1, 8]
	adrp	x2, .LANCHOR195
	adrp	x23, .LANCHOR45
	add	x20, x20, 12
	ldr	x25, [x2, #:lo12:.LANCHOR195]
	add	x23, x23, :lo12:.LANCHOR45
	mov	w21, 0
	mov	w27, -1
	str	x25, [x1, 16]
.L1859:
	ldrh	w0, [x23]
	cmp	w21, w0
	bcc	.L1864
	ldp	x19, x20, [sp, 16]
	mov	w0, 0
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
.L1864:
	ldrh	w19, [x26, #:lo12:.LANCHOR51]
	add	x24, x22, :lo12:.LANCHOR211
	strh	w27, [x20]
	mov	w3, 61664
	sub	w19, w19, #1
	and	w19, w19, 65535
.L1860:
	ldrh	w0, [x28]
	sub	w1, w0, #15
	cmp	w1, w19
	bgt	.L1862
	madd	w0, w0, w21, w19
	mov	w2, 1
	str	w3, [x29, 108]
	mov	w1, w2
	lsl	w0, w0, 10
	str	w0, [x24, 4]
	mov	x0, x24
	bl	FlashReadPages
	ldr	w0, [x24]
	ldr	w3, [x29, 108]
	cmn	w0, #1
	beq	.L1861
	ldrh	w0, [x25]
	cmp	w0, w3
	bne	.L1861
	strh	w19, [x20]
.L1862:
	add	w21, w21, 1
	add	x20, x20, 2
	b	.L1859
.L1861:
	sub	w19, w19, #1
	and	w19, w19, 65535
	b	.L1860
	.size	FtlLoadFactoryBbt, .-FtlLoadFactoryBbt
	.section	.text.FtlGetLastWrittenPage,"ax",@progbits
	.align	2
	.global	FtlGetLastWrittenPage
	.type	FtlGetLastWrittenPage, %function
FtlGetLastWrittenPage:
	stp	x29, x30, [sp, -192]!
	cmp	w1, 1
	add	x29, sp, 0
	stp	x23, x24, [sp, 48]
	mov	w23, w1
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	bne	.L1870
	adrp	x1, .LANCHOR53
	ldrh	w19, [x1, #:lo12:.LANCHOR53]
.L1871:
	sub	w19, w19, #1
	lsl	w21, w0, 10
	sxth	w19, w19
	add	x1, x29, 128
	orr	w0, w19, w21
	stp	xzr, x1, [x29, 80]
	str	w0, [x29, 76]
	mov	w2, w23
	mov	w1, 1
	add	x0, x29, 72
	bl	FlashReadPages
	ldr	w0, [x29, 128]
	cmn	w0, #1
	bne	.L1872
	mov	w22, 0
	mov	w24, 2
.L1873:
	cmp	w22, w19
	ble	.L1876
.L1872:
	mov	w0, w19
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 192
	ret
.L1870:
	adrp	x1, .LANCHOR52
	ldrh	w19, [x1, #:lo12:.LANCHOR52]
	b	.L1871
.L1876:
	add	w20, w22, w19
	mov	w2, w23
	mov	w1, 1
	sdiv	w20, w20, w24
	sxth	w0, w20
	orr	w0, w0, w21
	str	w0, [x29, 76]
	add	x0, x29, 72
	bl	FlashReadPages
	ldr	w0, [x29, 128]
	cmn	w0, #1
	bne	.L1874
	ldr	w0, [x29, 132]
	cmn	w0, #1
	bne	.L1874
	ldr	w0, [x29, 72]
	cmn	w0, #1
	beq	.L1874
	sub	w19, w20, #1
	sxth	w19, w19
	b	.L1873
.L1874:
	add	w20, w20, 1
	sxth	w22, w20
	b	.L1873
	.size	FtlGetLastWrittenPage, .-FtlGetLastWrittenPage
	.section	.text.FtlLoadBbt,"ax",@progbits
	.align	2
	.global	FtlLoadBbt
	.type	FtlLoadBbt, %function
FtlLoadBbt:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x23, x24, [sp, 48]
	adrp	x23, .LANCHOR189
	stp	x19, x20, [sp, 16]
	adrp	x24, .LANCHOR51
	stp	x21, x22, [sp, 32]
	adrp	x22, .LANCHOR211
	add	x20, x22, :lo12:.LANCHOR211
	ldr	x0, [x23, #:lo12:.LANCHOR189]
	str	x25, [sp, 64]
	mov	w25, 61649
	str	x0, [x20, 8]
	adrp	x0, .LANCHOR195
	ldr	x21, [x0, #:lo12:.LANCHOR195]
	str	x21, [x20, 16]
	bl	FtlBbtMemInit
	ldrh	w19, [x24, #:lo12:.LANCHOR51]
	add	x24, x24, :lo12:.LANCHOR51
	sub	w19, w19, #1
	and	w19, w19, 65535
.L1882:
	ldrh	w0, [x24]
	sub	w0, w0, #47
	cmp	w0, w19
	bgt	.L1885
	lsl	w0, w19, 10
	mov	w2, 1
	str	w0, [x20, 4]
	mov	w1, w2
	mov	x0, x20
	bl	FlashReadPages
	ldr	w0, [x20]
	cmn	w0, #1
	bne	.L1883
	ldr	w0, [x20, 4]
	mov	w2, 1
	mov	w1, w2
	add	w0, w0, 1
	str	w0, [x20, 4]
	mov	x0, x20
	bl	FlashReadPages
.L1883:
	ldr	w0, [x20]
	cmn	w0, #1
	beq	.L1884
	ldrh	w0, [x21]
	cmp	w0, w25
	bne	.L1884
	adrp	x1, .LANCHOR76
	add	x0, x1, :lo12:.LANCHOR76
	strh	w19, [x1, #:lo12:.LANCHOR76]
	ldr	w1, [x21, 4]
	str	w1, [x0, 8]
	ldrh	w1, [x21, 8]
	strh	w1, [x0, 4]
.L1885:
	adrp	x19, .LANCHOR76
	mov	w0, 65535
	add	x20, x19, :lo12:.LANCHOR76
	ldrh	w1, [x19, #:lo12:.LANCHOR76]
	cmp	w1, w0
	beq	.L1899
	ldrh	w1, [x20, 4]
	cmp	w1, w0
	beq	.L1889
	add	x0, x22, :lo12:.LANCHOR211
	lsl	w1, w1, 10
	mov	w2, 1
	str	w1, [x0, 4]
	mov	w1, w2
	bl	FlashReadPages
	ldr	w0, [x22, #:lo12:.LANCHOR211]
	cmn	w0, #1
	beq	.L1889
	ldrh	w1, [x21]
	mov	w0, 61649
	cmp	w1, w0
	bne	.L1889
	ldr	w1, [x20, 8]
	ldr	w0, [x21, 4]
	cmp	w0, w1
	bls	.L1889
	ldrh	w1, [x20, 4]
	str	w0, [x20, 8]
	ldrh	w0, [x21, 8]
	strh	w1, [x19, #:lo12:.LANCHOR76]
	strh	w0, [x20, 4]
.L1889:
	ldrh	w0, [x19, #:lo12:.LANCHOR76]
	add	x24, x19, :lo12:.LANCHOR76
	mov	w1, 1
	mov	w25, 61649
	bl	FtlGetLastWrittenPage
	sxth	w20, w0
	add	w0, w0, 1
	strh	w0, [x24, 2]
	add	x24, x22, :lo12:.LANCHOR211
.L1891:
	tbz	w20, #31, .L1894
	mov	w2, 339
	adrp	x1, .LANCHOR220
	adrp	x0, .LC5
	add	x1, x1, :lo12:.LANCHOR220
	add	x0, x0, :lo12:.LC5
	bl	printf
	adrp	x1, .LC6
	adrp	x0, .LC7
	add	x1, x1, :lo12:.LC6
	add	x0, x0, :lo12:.LC7
	bl	printf
.L1893:
	add	x0, x19, :lo12:.LANCHOR76
	ldrh	w1, [x21, 10]
	strh	w1, [x0, 6]
	mov	w1, 65535
	ldrh	w0, [x21, 12]
	cmp	w0, w1
	beq	.L1896
	adrp	x1, .LANCHOR37
	ldr	w2, [x1, #:lo12:.LANCHOR37]
	cmp	w0, w2
	beq	.L1896
	adrp	x1, .LANCHOR41
	ldrh	w1, [x1, #:lo12:.LANCHOR41]
	lsr	w1, w1, 2
	cmp	w2, w1
	bcs	.L1896
	cmp	w0, w1
	bcs	.L1896
	bl	FtlSysBlkNumInit
.L1896:
	add	x19, x19, :lo12:.LANCHOR76
	adrp	x21, .LANCHOR45
	adrp	x23, .LANCHOR126
	add	x19, x19, 32
	add	x21, x21, :lo12:.LANCHOR45
	add	x23, x23, :lo12:.LANCHOR126
	add	x22, x22, :lo12:.LANCHOR211
	mov	w20, 0
.L1897:
	ldrh	w0, [x21]
	cmp	w20, w0
	bcc	.L1898
	mov	w0, 0
.L1881:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldr	x25, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
.L1884:
	sub	w19, w19, #1
	and	w19, w19, 65535
	b	.L1882
.L1894:
	ldrh	w0, [x19, #:lo12:.LANCHOR76]
	mov	w2, 1
	mov	w1, w2
	orr	w0, w20, w0, lsl 10
	str	w0, [x24, 4]
	ldr	x0, [x23, #:lo12:.LANCHOR189]
	str	x0, [x24, 8]
	mov	x0, x24
	bl	FlashReadPages
	ldr	w0, [x24]
	cmn	w0, #1
	beq	.L1892
	ldrh	w0, [x21]
	cmp	w0, w25
	beq	.L1893
.L1892:
	sub	w20, w20, #1
	sxth	w20, w20
	b	.L1891
.L1898:
	ldrh	w2, [x23]
	ldr	x0, [x22, 8]
	mul	w1, w2, w20
	lsl	w2, w2, 2
	add	w20, w20, 1
	add	x1, x0, x1, lsl 2
	ldr	x0, [x19], 8
	bl	ftl_memcpy
	b	.L1897
.L1899:
	mov	w0, -1
	b	.L1881
	.size	FtlLoadBbt, .-FtlLoadBbt
	.section	.text.ftl_map_blk_gc,"ax",@progbits
	.align	2
	.global	ftl_map_blk_gc
	.type	ftl_map_blk_gc, %function
ftl_map_blk_gc:
	stp	x29, x30, [sp, -112]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	stp	x25, x26, [sp, 64]
	adrp	x25, .LANCHOR53
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	stp	x27, x28, [sp, 80]
	ldr	x20, [x0, 16]
	ldr	x26, [x0, 40]
	bl	ftl_free_no_use_map_blk
	ldrh	w1, [x19, 10]
	ldrh	w2, [x19, 8]
	sub	w1, w1, #4
	cmp	w2, w1
	blt	.L1912
	ubfiz	x0, x0, 1, 16
	ldrh	w21, [x20, x0]
	cbz	w21, .L1912
	ldr	w1, [x19, 52]
	cbnz	w1, .L1912
	mov	w1, 1
	str	w1, [x19, 52]
	strh	wzr, [x20, x0]
	ldrh	w0, [x19, 8]
	ldrh	w1, [x19, 2]
	sub	w0, w0, #1
	strh	w0, [x19, 8]
	ldrh	w0, [x25, #:lo12:.LANCHOR53]
	cmp	w1, w0
	bcc	.L1913
	mov	x0, x19
	bl	ftl_map_blk_alloc_new_blk
.L1913:
	adrp	x22, .LANCHOR211
	adrp	x24, .LANCHOR221
	mov	x23, x22
	add	x27, x22, :lo12:.LANCHOR211
	add	x24, x24, :lo12:.LANCHOR221
	mov	w20, 0
.L1914:
	ldrh	w0, [x19, 6]
	cmp	w0, w20
	bhi	.L1920
	mov	w1, 1
	mov	w0, w21
	bl	FtlFreeSysBlkQueueIn
	str	wzr, [x19, 52]
.L1912:
	ldrh	w1, [x19, 2]
	ldrh	w0, [x25, #:lo12:.LANCHOR53]
	cmp	w1, w0
	bcc	.L1918
	mov	x0, x19
	bl	ftl_map_blk_alloc_new_blk
	b	.L1918
.L1920:
	ubfiz	x0, x20, 2, 16
	add	x1, x26, x0
	str	x1, [x29, 104]
	ldr	w1, [x26, x0]
	cmp	w21, w1, lsr 10
	bne	.L1915
	adrp	x2, .LANCHOR190
	add	x0, x22, :lo12:.LANCHOR211
	ldr	x2, [x2, #:lo12:.LANCHOR190]
	str	x2, [x0, 8]
	adrp	x2, .LANCHOR195
	str	w1, [x0, 4]
	ldr	x28, [x2, #:lo12:.LANCHOR195]
	mov	w2, 1
	str	x28, [x0, 16]
	mov	w1, w2
	bl	FlashReadPages
	ldrh	w0, [x28, 8]
	cmp	w0, w20
	beq	.L1916
	mov	w2, 752
	mov	x1, x24
	adrp	x0, .LC5
	add	x0, x0, :lo12:.LC5
	bl	printf
	adrp	x1, .LC6
	adrp	x0, .LC7
	add	x1, x1, :lo12:.LC6
	add	x0, x0, :lo12:.LC7
	bl	printf
.L1916:
	ldr	w0, [x27]
	ldrh	w2, [x28, 8]
	cmn	w0, #1
	bne	.L1917
.L1919:
	ldr	x0, [x29, 104]
	add	x23, x23, :lo12:.LANCHOR211
	str	wzr, [x0]
	adrp	x0, .LC41
	add	x0, x0, :lo12:.LC41
	ldr	w1, [x23, 4]
	bl	printf
	adrp	x0, .LANCHOR78
	mov	w1, 1
	str	w1, [x0, #:lo12:.LANCHOR78]
.L1918:
	ldp	x19, x20, [sp, 16]
	mov	w0, 0
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
.L1917:
	cmp	w2, w20
	bne	.L1919
	ldrh	w1, [x28]
	ldrh	w0, [x19, 4]
	cmp	w1, w0
	bne	.L1919
	ldr	x2, [x27, 8]
	mov	w1, w20
	mov	x0, x19
	bl	FtlMapWritePage
.L1915:
	add	w20, w20, 1
	and	w20, w20, 65535
	b	.L1914
	.size	ftl_map_blk_gc, .-ftl_map_blk_gc
	.section	.text.Ftl_write_map_blk_to_last_page,"ax",@progbits
	.align	2
	.global	Ftl_write_map_blk_to_last_page
	.type	Ftl_write_map_blk_to_last_page, %function
Ftl_write_map_blk_to_last_page:
	adrp	x1, .LANCHOR78
	ldr	w1, [x1, #:lo12:.LANCHOR78]
	cbnz	w1, .L1940
	stp	x29, x30, [sp, -64]!
	mov	w1, 65535
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	stp	x21, x22, [sp, 32]
	ldrh	w0, [x0]
	stp	x23, x24, [sp, 48]
	cmp	w0, w1
	ldr	x20, [x19, 16]
	bne	.L1927
	ldrh	w0, [x19, 8]
	cbz	w0, .L1928
	mov	w2, 793
	adrp	x1, .LANCHOR222
	adrp	x0, .LC5
	add	x1, x1, :lo12:.LANCHOR222
	add	x0, x0, :lo12:.LC5
	bl	printf
	adrp	x1, .LC6
	adrp	x0, .LC7
	add	x1, x1, :lo12:.LC6
	add	x0, x0, :lo12:.LC7
	bl	printf
.L1928:
	ldrh	w0, [x19, 8]
	add	w0, w0, 1
	strh	w0, [x19, 8]
	bl	FtlFreeSysBlkQueueOut
	strh	w0, [x20]
	ldr	w0, [x19, 48]
	strh	wzr, [x19, 2]
	add	w0, w0, 1
	strh	wzr, [x19]
	str	w0, [x19, 48]
.L1926:
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
.L1927:
	ubfiz	x0, x0, 1, 16
	adrp	x2, .LANCHOR195
	adrp	x21, .LANCHOR211
	add	x1, x21, :lo12:.LANCHOR211
	adrp	x24, .LANCHOR189
	ldr	x23, [x19, 40]
	ldrh	w22, [x20, x0]
	ldrh	w0, [x19, 2]
	ldr	x20, [x2, #:lo12:.LANCHOR195]
	str	x20, [x1, 16]
	orr	w0, w0, w22, lsl 10
	str	w0, [x1, 4]
	ldr	x0, [x24, #:lo12:.LANCHOR189]
	str	x0, [x1, 8]
	ldr	w1, [x19, 48]
	str	w1, [x20, 4]
	mov	w1, -1291
	strh	w1, [x20, 8]
	ldrh	w1, [x19, 4]
	strh	w1, [x20]
	adrp	x1, .LANCHOR53
	strh	w22, [x20, 2]
	ldrh	w2, [x1, #:lo12:.LANCHOR53]
	mov	w1, 255
	lsl	w2, w2, 3
	bl	ftl_memset
	ldrh	w4, [x19, 6]
	mov	x1, 0
	ldr	x3, [x24, #:lo12:.LANCHOR189]
	mov	w0, 0
.L1929:
	cmp	w4, w1, uxth
	bhi	.L1931
	adrp	x0, .LANCHOR2
	ldrb	w0, [x0, #:lo12:.LANCHOR2]
	cbz	w0, .L1932
	add	x0, x21, :lo12:.LANCHOR211
	adrp	x1, .LANCHOR57
	ldrh	w1, [x1, #:lo12:.LANCHOR57]
	ldr	x0, [x0, 8]
	bl	js_hash
	str	w0, [x20, 12]
.L1932:
	mov	w2, 1
	mov	w3, 0
	mov	w1, w2
	add	x0, x21, :lo12:.LANCHOR211
	bl	FlashProgPages
	ldrh	w0, [x19, 2]
	add	w0, w0, 1
	strh	w0, [x19, 2]
	mov	x0, x19
	bl	ftl_map_blk_gc
	b	.L1926
.L1931:
	ldr	w2, [x23, x1, lsl 2]
	cmp	w22, w2, lsr 10
	bne	.L1930
	add	w0, w0, 1
	and	w0, w0, 65535
	ubfiz	x2, x0, 1, 16
	str	w1, [x3, x2, lsl 2]
	add	x2, x2, 1
	ldr	w5, [x23, x1, lsl 2]
	str	w5, [x3, x2, lsl 2]
.L1930:
	add	x1, x1, 1
	b	.L1929
.L1940:
	mov	w0, 0
	ret
	.size	Ftl_write_map_blk_to_last_page, .-Ftl_write_map_blk_to_last_page
	.section	.text.FtlMapWritePage,"ax",@progbits
	.align	2
	.global	FtlMapWritePage
	.type	FtlMapWritePage, %function
FtlMapWritePage:
	stp	x29, x30, [sp, -112]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w19, 0
	stp	x25, x26, [sp, 64]
	adrp	x26, .LANCHOR53
	stp	x27, x28, [sp, 80]
	mov	w25, w1
	stp	x21, x22, [sp, 32]
	mov	x27, x0
	adrp	x22, .LANCHOR211
	stp	x23, x24, [sp, 48]
	mov	x20, x22
	add	x23, x22, :lo12:.LANCHOR211
	add	x28, x26, :lo12:.LANCHOR53
	str	x2, [x29, 104]
.L1944:
	adrp	x1, .LANCHOR170
	ldr	w0, [x1, #:lo12:.LANCHOR170]
	add	w0, w0, 1
	str	w0, [x1, #:lo12:.LANCHOR170]
	ldrh	w0, [x26, #:lo12:.LANCHOR53]
	ldrh	w1, [x27, 2]
	sub	w0, w0, #1
	cmp	w1, w0
	bge	.L1945
	ldrh	w1, [x27]
	mov	w0, 65535
	cmp	w1, w0
	bne	.L1946
.L1945:
	mov	x0, x27
	bl	Ftl_write_map_blk_to_last_page
.L1946:
	adrp	x21, .LANCHOR78
	ldr	w0, [x21, #:lo12:.LANCHOR78]
	cbnz	w0, .L1961
	ldrh	w1, [x27]
	ldr	x0, [x27, 16]
	ldrh	w0, [x0, x1, lsl 1]
	cbnz	w0, .L1948
	mov	w2, 865
	adrp	x1, .LANCHOR223
	adrp	x0, .LC5
	add	x1, x1, :lo12:.LANCHOR223
	add	x0, x0, :lo12:.LC5
	bl	printf
	adrp	x1, .LC6
	adrp	x0, .LC7
	add	x1, x1, :lo12:.LC6
	add	x0, x0, :lo12:.LC7
	bl	printf
.L1948:
	ldrh	w1, [x27]
	ldrh	w0, [x27, 10]
	cmp	w1, w0
	bcc	.L1949
	mov	w2, 866
	adrp	x1, .LANCHOR223
	adrp	x0, .LC5
	add	x1, x1, :lo12:.LANCHOR223
	add	x0, x0, :lo12:.LC5
	bl	printf
	adrp	x1, .LC6
	adrp	x0, .LC7
	add	x1, x1, :lo12:.LC6
	add	x0, x0, :lo12:.LC7
	bl	printf
.L1949:
	ldrh	w1, [x27]
	add	x3, x22, :lo12:.LANCHOR211
	ldr	x0, [x27, 16]
	mov	w2, 16
	str	x3, [x29, 96]
	ldrh	w24, [x0, x1, lsl 1]
	mov	w1, 0
	ldrh	w0, [x27, 2]
	orr	w0, w0, w24, lsl 10
	str	w0, [x3, 4]
	ldr	x0, [x29, 104]
	str	x0, [x3, 8]
	adrp	x0, .LANCHOR195
	ldr	x0, [x0, #:lo12:.LANCHOR195]
	str	x0, [x3, 16]
	bl	ftl_memset
	ldr	x3, [x29, 96]
	ldr	w0, [x27, 48]
	ldr	x6, [x3, 16]
	str	w0, [x6, 4]
	ldrh	w0, [x27, 4]
	strh	w0, [x6]
	adrp	x0, .LANCHOR2
	strh	w25, [x6, 8]
	strh	w24, [x6, 2]
	ldrb	w0, [x0, #:lo12:.LANCHOR2]
	cbz	w0, .L1950
	adrp	x0, .LANCHOR57
	ldrh	w1, [x0, #:lo12:.LANCHOR57]
	ldr	x0, [x3, 8]
	bl	js_hash
	str	w0, [x6, 12]
.L1950:
	mov	w3, 1
	mov	x0, x23
	mov	w1, w3
	mov	w2, w3
	bl	FlashProgPages
	ldrh	w0, [x27, 2]
	ldr	w1, [x23]
	add	w0, w0, 1
	and	w0, w0, 65535
	strh	w0, [x27, 2]
	cmn	w1, #1
	bne	.L1951
	ldr	w1, [x23, 4]
	adrp	x0, .LC42
	add	x0, x0, :lo12:.LC42
	add	w19, w19, 1
	and	w19, w19, 65535
	bl	printf
	ldrh	w0, [x27, 2]
	cmp	w0, 2
	bhi	.L1952
	ldrh	w0, [x28]
	sub	w0, w0, #1
	strh	w0, [x27, 2]
.L1952:
	cmp	w19, 3
	bls	.L1944
	add	x20, x20, :lo12:.LANCHOR211
	mov	w2, w19
	adrp	x0, .LC43
	add	x0, x0, :lo12:.LC43
	ldr	w1, [x20, 4]
	bl	printf
	mov	w0, 1
	str	w0, [x21, #:lo12:.LANCHOR78]
.L1961:
	ldp	x19, x20, [sp, 16]
	mov	w0, 0
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
.L1951:
	cbz	w1, .L1954
	strh	w24, [x27, 60]
	cmp	w0, 1
	bne	.L1955
.L1956:
	str	wzr, [x27, 56]
	b	.L1944
.L1955:
	cmp	w1, 256
.L1969:
	beq	.L1956
	ldr	w0, [x27, 56]
	cbnz	w0, .L1956
	add	x20, x20, :lo12:.LANCHOR211
	ldr	x0, [x27, 40]
	ldr	w1, [x20, 4]
	str	w1, [x0, w25, uxtw 2]
	b	.L1961
.L1954:
	cmp	w0, 1
	b	.L1969
	.size	FtlMapWritePage, .-FtlMapWritePage
	.section	.text.flush_l2p_region,"ax",@progbits
	.align	2
	.global	flush_l2p_region
	.type	flush_l2p_region, %function
flush_l2p_region:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	adrp	x20, .LANCHOR98
	ubfiz	x19, x0, 4, 16
	ldr	x0, [x20, #:lo12:.LANCHOR98]
	add	x1, x0, x19
	ldr	x2, [x1, 8]
	ldrh	w1, [x0, x19]
	adrp	x0, .LANCHOR130
	add	x0, x0, :lo12:.LANCHOR130
	bl	FtlMapWritePage
	ldr	x0, [x20, #:lo12:.LANCHOR98]
	add	x0, x0, x19
	ldp	x19, x20, [sp, 16]
	ldr	w1, [x0, 4]
	and	w1, w1, 2147483647
	str	w1, [x0, 4]
	mov	w0, 0
	ldp	x29, x30, [sp], 32
	ret
	.size	flush_l2p_region, .-flush_l2p_region
	.section	.text.l2p_flush,"ax",@progbits
	.align	2
	.global	l2p_flush
	.type	l2p_flush, %function
l2p_flush:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	adrp	x20, .LANCHOR67
	add	x20, x20, :lo12:.LANCHOR67
	str	x21, [sp, 32]
	mov	w19, 0
	adrp	x21, .LANCHOR98
.L1973:
	ldrh	w0, [x20]
	cmp	w0, w19
	bhi	.L1975
	mov	w0, 0
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
.L1975:
	ldr	x1, [x21, #:lo12:.LANCHOR98]
	ubfiz	x0, x19, 4, 16
	add	x0, x1, x0
	ldr	w0, [x0, 4]
	tbz	w0, #31, .L1974
	mov	w0, w19
	bl	flush_l2p_region
.L1974:
	add	w19, w19, 1
	and	w19, w19, 65535
	b	.L1973
	.size	l2p_flush, .-l2p_flush
	.section	.text.FtlVendorPartWrite,"ax",@progbits
	.align	2
	.global	FtlVendorPartWrite
	.type	FtlVendorPartWrite, %function
FtlVendorPartWrite:
	stp	x29, x30, [sp, -176]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w20, w1
	stp	x21, x22, [sp, 32]
	add	w1, w0, w1
	mov	w22, w0
	adrp	x0, .LANCHOR50
	stp	x23, x24, [sp, 48]
	ldrh	w0, [x0, #:lo12:.LANCHOR50]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	cmp	w1, w0
	bhi	.L1985
	adrp	x0, .LANCHOR56
	adrp	x26, .LANCHOR55
	adrp	x27, .LANCHOR57
	mov	x25, x2
	ldrh	w21, [x0, #:lo12:.LANCHOR56]
	add	x26, x26, :lo12:.LANCHOR55
	add	x27, x27, :lo12:.LANCHOR57
	mov	w24, 0
	lsr	w21, w22, w21
.L1979:
	cbnz	w20, .L1984
.L1977:
	mov	w0, w24
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 176
	ret
.L1984:
	ldrh	w1, [x26]
	adrp	x0, .LANCHOR202
	adrp	x28, .LANCHOR191
	ldr	x0, [x0, #:lo12:.LANCHOR202]
	udiv	w23, w22, w1
	ldr	w2, [x0, w21, uxtw 2]
	and	w0, w20, 65535
	msub	w23, w23, w1, w22
	sub	w19, w1, w23
	and	w19, w19, 65535
	cmp	w20, w19
	csel	w19, w0, w19, cc
	cbz	w2, .L1981
	cmp	w19, w1
	beq	.L1981
	ldr	x0, [x28, #:lo12:.LANCHOR191]
	str	w2, [x29, 124]
	mov	w2, 1
	stp	x0, xzr, [x29, 128]
	mov	w1, w2
	add	x0, x29, 120
	bl	FlashReadPages
.L1982:
	lsl	w3, w19, 9
	ldr	x0, [x28, #:lo12:.LANCHOR191]
	lsl	w23, w23, 7
	mov	w2, w3
	mov	x1, x25
	str	w3, [x29, 108]
	add	x0, x0, x23, sxtw 2
	bl	ftl_memcpy
	ldr	x2, [x28, #:lo12:.LANCHOR191]
	mov	w1, w21
	adrp	x0, .LANCHOR224
	add	x0, x0, :lo12:.LANCHOR224
	sub	w20, w20, w19
	add	w22, w22, w19
	add	w21, w21, 1
	bl	FtlMapWritePage
	cmn	w0, #1
	ldr	w3, [x29, 108]
	csinv	w24, w24, wzr, ne
	add	x25, x25, x3, sxtw
	b	.L1979
.L1981:
	ldrh	w2, [x27]
	mov	w1, 0
	ldr	x0, [x28, #:lo12:.LANCHOR191]
	bl	ftl_memset
	b	.L1982
.L1985:
	mov	w24, -1
	b	.L1977
	.size	FtlVendorPartWrite, .-FtlVendorPartWrite
	.section	.text.Ftl_save_ext_data,"ax",@progbits
	.align	2
	.global	Ftl_save_ext_data
	.type	Ftl_save_ext_data, %function
Ftl_save_ext_data:
	adrp	x0, .LANCHOR141
	add	x2, x0, :lo12:.LANCHOR141
	ldr	w1, [x0, #:lo12:.LANCHOR141]
	mov	w0, 19539
	movk	w0, 0x4654, lsl 16
	cmp	w1, w0
	bne	.L1990
	mov	w0, 99
	mov	w1, 1
	movk	w0, 0x5000, lsl 16
	str	w0, [x2, 4]
	adrp	x0, .LANCHOR225
	ldr	w0, [x0, #:lo12:.LANCHOR225]
	str	w0, [x2, 88]
	adrp	x0, .LANCHOR226
	ldr	w0, [x0, #:lo12:.LANCHOR226]
	str	w0, [x2, 92]
	adrp	x0, .LANCHOR166
	ldr	w0, [x0, #:lo12:.LANCHOR166]
	str	w0, [x2, 8]
	adrp	x0, .LANCHOR167
	ldr	w0, [x0, #:lo12:.LANCHOR167]
	str	w0, [x2, 12]
	adrp	x0, .LANCHOR171
	ldr	w0, [x0, #:lo12:.LANCHOR171]
	str	w0, [x2, 16]
	adrp	x0, .LANCHOR170
	ldr	w0, [x0, #:lo12:.LANCHOR170]
	str	w0, [x2, 20]
	adrp	x0, .LANCHOR173
	ldr	w0, [x0, #:lo12:.LANCHOR173]
	str	w0, [x2, 28]
	adrp	x0, .LANCHOR81
	ldr	w0, [x0, #:lo12:.LANCHOR81]
	str	w0, [x2, 32]
	adrp	x0, .LANCHOR168
	ldr	w0, [x0, #:lo12:.LANCHOR168]
	str	w0, [x2, 36]
	adrp	x0, .LANCHOR169
	ldr	w0, [x0, #:lo12:.LANCHOR169]
	str	w0, [x2, 40]
	adrp	x0, .LANCHOR174
	ldr	w0, [x0, #:lo12:.LANCHOR174]
	str	w0, [x2, 44]
	adrp	x0, .LANCHOR175
	ldr	w0, [x0, #:lo12:.LANCHOR175]
	str	w0, [x2, 48]
	adrp	x0, .LANCHOR163
	ldr	w0, [x0, #:lo12:.LANCHOR163]
	str	w0, [x2, 60]
	adrp	x0, .LANCHOR162
	ldr	w0, [x0, #:lo12:.LANCHOR162]
	str	w0, [x2, 64]
	mov	w0, 0
	b	FtlVendorPartWrite
.L1990:
	ret
	.size	Ftl_save_ext_data, .-Ftl_save_ext_data
	.section	.text.FtlEctTblFlush,"ax",@progbits
	.align	2
	.global	FtlEctTblFlush
	.type	FtlEctTblFlush, %function
FtlEctTblFlush:
	adrp	x1, .LANCHOR104
	ldr	w1, [x1, #:lo12:.LANCHOR104]
	cbz	w1, .L1997
	adrp	x1, .LANCHOR175
	mov	w2, 4
	ldr	w1, [x1, #:lo12:.LANCHOR175]
	cmp	w1, 39
	mov	w1, 32
	csel	w1, w1, w2, hi
.L1993:
	adrp	x3, .LANCHOR227
	ldrh	w2, [x3, #:lo12:.LANCHOR227]
	cmp	w2, 31
	bhi	.L1994
	add	w2, w2, 1
	mov	w1, 1
	strh	w2, [x3, #:lo12:.LANCHOR227]
.L1994:
	adrp	x2, .LANCHOR199
	cbnz	w0, .L1995
	ldr	x0, [x2, #:lo12:.LANCHOR199]
	ldr	w3, [x0, 20]
	ldr	w0, [x0, 16]
	add	w1, w1, w3
	cmp	w0, w1
	bcc	.L2000
.L1995:
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
	ldr	x2, [x2, #:lo12:.LANCHOR199]
	ldr	w0, [x2, 16]
	str	w0, [x2, 20]
	mov	w0, 17221
	str	wzr, [x2, 4]
	movk	w0, 0x4254, lsl 16
	str	w0, [x2]
	adrp	x0, .LANCHOR198
	ldrh	w1, [x0, #:lo12:.LANCHOR198]
	lsl	w0, w1, 9
	str	w0, [x2, 12]
	ldr	w0, [x2, 8]
	add	w0, w0, 1
	str	w0, [x2, 8]
	mov	w0, 64
	bl	FtlVendorPartWrite
	bl	Ftl_save_ext_data
	mov	w0, 0
	ldp	x29, x30, [sp], 16
	ret
.L1997:
	mov	w1, 32
	b	.L1993
.L2000:
	mov	w0, 0
	ret
	.size	FtlEctTblFlush, .-FtlEctTblFlush
	.section	.text.allocate_new_data_superblock,"ax",@progbits
	.align	2
	.global	allocate_new_data_superblock
	.type	allocate_new_data_superblock, %function
allocate_new_data_superblock:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	ldrh	w20, [x0]
	adrp	x0, .LANCHOR40
	str	x21, [sp, 32]
	ldrh	w0, [x0, #:lo12:.LANCHOR40]
	cmp	w0, w20
	bcs	.L2003
	mov	w2, 3650
	adrp	x1, .LANCHOR228
	adrp	x0, .LC5
	add	x1, x1, :lo12:.LANCHOR228
	add	x0, x0, :lo12:.LC5
	bl	printf
	adrp	x1, .LC6
	adrp	x0, .LC7
	add	x1, x1, :lo12:.LC6
	add	x0, x0, :lo12:.LC7
	bl	printf
.L2003:
	adrp	x0, .LANCHOR78
	ldr	w0, [x0, #:lo12:.LANCHOR78]
	cbnz	w0, .L2004
	mov	w0, 65535
	cmp	w20, w0
	beq	.L2005
	adrp	x1, .LANCHOR85
	ubfiz	x0, x20, 1, 16
	ldr	x1, [x1, #:lo12:.LANCHOR85]
	ldrh	w0, [x1, x0]
	cbz	w0, .L2006
	mov	w0, w20
	bl	INSERT_DATA_LIST
.L2005:
	strb	wzr, [x19, 8]
	adrp	x0, .LANCHOR94
	add	x0, x0, :lo12:.LANCHOR94
	cmp	x19, x0
	beq	.L2007
	adrp	x0, .LANCHOR44
	ldrh	w1, [x0, #:lo12:.LANCHOR44]
	cmp	w1, 1
	beq	.L2007
	adrp	x0, .LANCHOR16
	ldrb	w0, [x0, #:lo12:.LANCHOR16]
	cbz	w0, .L2008
.L2007:
	mov	w0, 1
	strb	w0, [x19, 8]
.L2009:
	adrp	x1, .LANCHOR136
	mov	w2, 65535
	mov	x21, x1
	ldrh	w0, [x1, #:lo12:.LANCHOR136]
	cmp	w0, w2
	beq	.L2014
	cmp	w20, w0
	bne	.L2015
	adrp	x2, .LANCHOR85
	ubfiz	x1, x0, 1, 16
	ldr	x2, [x2, #:lo12:.LANCHOR85]
	ldrh	w1, [x2, x1]
	cbz	w1, .L2016
.L2015:
	bl	update_vpc_list
.L2016:
	mov	w0, -1
	strh	w0, [x21, #:lo12:.LANCHOR136]
.L2014:
	mov	x0, x19
	bl	allocate_data_superblock
	bl	l2p_flush
	mov	w0, 0
	bl	FtlEctTblFlush
	bl	FtlVpcTblFlush
.L2004:
	mov	w0, 0
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
.L2006:
	mov	w0, w20
	bl	INSERT_FREE_LIST
	b	.L2005
.L2008:
	adrp	x0, .LANCHOR93
	add	x2, x0, :lo12:.LANCHOR93
	cmp	x19, x2
	bne	.L2009
	cmp	w1, 3
	beq	.L2011
	adrp	x1, .LANCHOR163
	ldr	w1, [x1, #:lo12:.LANCHOR163]
	cmp	w1, 1
	bne	.L2012
.L2011:
	add	x1, x0, :lo12:.LANCHOR93
	mov	w2, 1
	strb	w2, [x1, 8]
.L2012:
	adrp	x1, .LANCHOR104
	ldr	w1, [x1, #:lo12:.LANCHOR104]
	cbz	w1, .L2009
	adrp	x1, .LANCHOR175
	ldr	w1, [x1, #:lo12:.LANCHOR175]
	cmp	w1, 39
	bhi	.L2009
	add	x0, x0, :lo12:.LANCHOR93
	mov	w1, 1
	strb	w1, [x0, 8]
	b	.L2009
	.size	allocate_new_data_superblock, .-allocate_new_data_superblock
	.section	.text.FtlVendorPartRead,"ax",@progbits
	.align	2
	.global	FtlVendorPartRead
	.type	FtlVendorPartRead, %function
FtlVendorPartRead:
	stp	x29, x30, [sp, -176]!
	add	x29, sp, 0
	stp	x21, x22, [sp, 32]
	mov	w22, w0
	mov	w21, w1
	add	w1, w0, w1
	adrp	x0, .LANCHOR50
	stp	x19, x20, [sp, 16]
	stp	x23, x24, [sp, 48]
	ldrh	w0, [x0, #:lo12:.LANCHOR50]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	cmp	w1, w0
	bhi	.L2039
	adrp	x0, .LANCHOR56
	adrp	x26, .LANCHOR191
	mov	x25, x2
	mov	x28, x26
	ldrh	w20, [x0, #:lo12:.LANCHOR56]
	mov	w24, 0
	adrp	x0, .LANCHOR55
	add	x0, x0, :lo12:.LANCHOR55
	str	x0, [x29, 104]
	lsr	w20, w22, w20
.L2032:
	cbnz	w21, .L2038
.L2030:
	mov	w0, w24
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 176
	ret
.L2038:
	adrp	x0, .LANCHOR202
	ldr	x0, [x0, #:lo12:.LANCHOR202]
	ldr	w3, [x0, w20, uxtw 2]
	ldr	x0, [x29, 104]
	ldrh	w19, [x0]
	and	w0, w21, 65535
	udiv	w23, w22, w19
	msub	w23, w23, w19, w22
	sub	w19, w19, w23
	and	w19, w19, 65535
	cmp	w21, w19
	csel	w19, w0, w19, cc
	lsl	w27, w19, 9
	cbz	w3, .L2034
	ldr	x0, [x26, #:lo12:.LANCHOR191]
	mov	w2, 1
	str	w3, [x29, 100]
	mov	w1, w2
	str	w3, [x29, 124]
	stp	x0, xzr, [x29, 128]
	add	x0, x29, 120
	bl	FlashReadPages
	ldr	w0, [x29, 120]
	ldr	w3, [x29, 100]
	cmn	w0, #1
	adrp	x0, .LANCHOR211
	csinv	w24, w24, wzr, ne
	ldr	w0, [x0, #:lo12:.LANCHOR211]
	cmp	w0, 256
	bne	.L2036
	mov	w2, w3
	mov	w1, w20
	adrp	x0, .LC44
	add	x0, x0, :lo12:.LC44
	bl	printf
	ldr	x2, [x26, #:lo12:.LANCHOR191]
	adrp	x0, .LANCHOR224
	mov	w1, w20
	add	x0, x0, :lo12:.LANCHOR224
	bl	FtlMapWritePage
.L2036:
	ldr	x1, [x28, #:lo12:.LANCHOR191]
	lsl	w23, w23, 7
	mov	w2, w27
	mov	x0, x25
	add	x1, x1, x23, sxtw 2
	bl	ftl_memcpy
.L2037:
	add	w20, w20, 1
	sub	w21, w21, w19
	add	w22, w22, w19
	add	x25, x25, x27, sxtw
	b	.L2032
.L2034:
	mov	w2, w27
	mov	w1, 0
	mov	x0, x25
	bl	ftl_memset
	b	.L2037
.L2039:
	mov	w24, -1
	b	.L2030
	.size	FtlVendorPartRead, .-FtlVendorPartRead
	.section	.text.FtlLoadEctTbl,"ax",@progbits
	.align	2
	.global	FtlLoadEctTbl
	.type	FtlLoadEctTbl, %function
FtlLoadEctTbl:
	stp	x29, x30, [sp, -32]!
	mov	w0, 64
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	adrp	x19, .LANCHOR199
	adrp	x20, .LANCHOR198
	ldr	x2, [x19, #:lo12:.LANCHOR199]
	ldrh	w1, [x20, #:lo12:.LANCHOR198]
	bl	FtlVendorPartRead
	ldr	x0, [x19, #:lo12:.LANCHOR199]
	ldr	w1, [x0]
	mov	w0, 17221
	movk	w0, 0x4254, lsl 16
	cmp	w1, w0
	beq	.L2042
	adrp	x1, .LC45
	adrp	x0, .LC7
	add	x1, x1, :lo12:.LC45
	add	x0, x0, :lo12:.LC7
	bl	printf
	ldr	x0, [x19, #:lo12:.LANCHOR199]
	mov	w1, 0
	ldrh	w2, [x20, #:lo12:.LANCHOR198]
	lsl	w2, w2, 9
	bl	ftl_memset
.L2042:
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	FtlLoadEctTbl, .-FtlLoadEctTbl
	.section	.text.Ftl_load_ext_data,"ax",@progbits
	.align	2
	.global	Ftl_load_ext_data
	.type	Ftl_load_ext_data, %function
Ftl_load_ext_data:
	stp	x29, x30, [sp, -48]!
	mov	w1, 1
	mov	w0, 0
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	adrp	x19, .LANCHOR141
	str	x21, [sp, 32]
	add	x21, x19, :lo12:.LANCHOR141
	mov	x2, x21
	bl	FtlVendorPartRead
	ldr	w0, [x19, #:lo12:.LANCHOR141]
	mov	w20, 19539
	movk	w20, 0x4654, lsl 16
	cmp	w0, w20
	beq	.L2045
	mov	w2, 512
	mov	w1, 0
	mov	x0, x21
	bl	ftl_memset
	str	w20, [x19, #:lo12:.LANCHOR141]
.L2045:
	ldr	w1, [x19, #:lo12:.LANCHOR141]
	add	x0, x19, :lo12:.LANCHOR141
	cmp	w1, w20
	adrp	x20, .LANCHOR173
	bne	.L2046
	adrp	x1, .LANCHOR225
	ldr	w2, [x0, 88]
	str	w2, [x1, #:lo12:.LANCHOR225]
	adrp	x1, .LANCHOR226
	ldr	w2, [x0, 92]
	str	w2, [x1, #:lo12:.LANCHOR226]
	adrp	x1, .LANCHOR166
	ldr	w2, [x0, 8]
	str	w2, [x1, #:lo12:.LANCHOR166]
	adrp	x1, .LANCHOR167
	ldr	w2, [x0, 12]
	str	w2, [x1, #:lo12:.LANCHOR167]
	adrp	x1, .LANCHOR171
	ldr	w2, [x0, 16]
	str	w2, [x1, #:lo12:.LANCHOR171]
	adrp	x1, .LANCHOR170
	ldr	w2, [x0, 20]
	str	w2, [x1, #:lo12:.LANCHOR170]
	ldp	w1, w2, [x0, 28]
	str	w1, [x20, #:lo12:.LANCHOR173]
	adrp	x1, .LANCHOR81
	str	w2, [x1, #:lo12:.LANCHOR81]
	adrp	x1, .LANCHOR168
	ldr	w2, [x0, 36]
	str	w2, [x1, #:lo12:.LANCHOR168]
	adrp	x1, .LANCHOR169
	ldr	w2, [x0, 40]
	str	w2, [x1, #:lo12:.LANCHOR169]
	adrp	x1, .LANCHOR174
	ldr	w2, [x0, 44]
	str	w2, [x1, #:lo12:.LANCHOR174]
	adrp	x1, .LANCHOR175
	ldr	w2, [x0, 48]
	str	w2, [x1, #:lo12:.LANCHOR175]
	ldr	w1, [x0, 60]
	adrp	x0, .LANCHOR163
	str	w1, [x0, #:lo12:.LANCHOR163]
.L2046:
	add	x19, x19, :lo12:.LANCHOR141
	adrp	x0, .LANCHOR162
	str	wzr, [x0, #:lo12:.LANCHOR162]
	mov	w0, 34661
	ldr	w1, [x19, 68]
	movk	w0, 0x1234, lsl 16
	cmp	w1, w0
	bne	.L2047
	adrp	x0, .LANCHOR16
	ldrb	w0, [x0, #:lo12:.LANCHOR16]
	cbz	w0, .L2048
	str	wzr, [x19, 68]
	bl	Ftl_save_ext_data
.L2047:
	adrp	x1, .LANCHOR172
	adrp	x0, .LANCHOR48
	ldr	x21, [sp, 32]
	ldr	w2, [x1, #:lo12:.LANCHOR172]
	ldrh	w0, [x0, #:lo12:.LANCHOR48]
	ldr	w1, [x20, #:lo12:.LANCHOR173]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	madd	w0, w0, w2, w1
	adrp	x1, .LANCHOR40
	ldrh	w1, [x1, #:lo12:.LANCHOR40]
	udiv	w0, w0, w1
	adrp	x1, .LANCHOR214
	str	w0, [x1, #:lo12:.LANCHOR214]
	ret
.L2048:
	adrp	x0, .LANCHOR104
	mov	w1, 1
	str	w1, [x0, #:lo12:.LANCHOR104]
	adrp	x1, .LC46
	adrp	x0, .LC7
	add	x1, x1, :lo12:.LC46
	add	x0, x0, :lo12:.LC7
	bl	printf
	b	.L2047
	.size	Ftl_load_ext_data, .-Ftl_load_ext_data
	.section	.text.FtlMapBlkWriteDumpData,"ax",@progbits
	.align	2
	.global	FtlMapBlkWriteDumpData
	.type	FtlMapBlkWriteDumpData, %function
FtlMapBlkWriteDumpData:
	ldr	w1, [x0, 56]
	cbz	w1, .L2064
	stp	x29, x30, [sp, -80]!
	adrp	x1, .LANCHOR78
	add	x29, sp, 0
	ldr	w1, [x1, #:lo12:.LANCHOR78]
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	ldrh	w20, [x0, 6]
	str	x25, [sp, 64]
	str	wzr, [x0, 56]
	ldr	x25, [x0, 40]
	cbnz	w1, .L2050
	mov	x19, x0
	adrp	x0, .LANCHOR190
	adrp	x23, .LANCHOR211
	add	x21, x23, :lo12:.LANCHOR211
	ldr	x0, [x0, #:lo12:.LANCHOR190]
	mov	x22, x23
	str	x0, [x21, 8]
	adrp	x0, .LANCHOR195
	ldr	x24, [x0, #:lo12:.LANCHOR195]
	ldrh	w0, [x19, 2]
	str	x24, [x21, 16]
	cbz	w0, .L2054
	adrp	x1, .LANCHOR53
	ldrh	w1, [x1, #:lo12:.LANCHOR53]
	sub	w1, w1, #1
	cmp	w0, w1
	bge	.L2054
	ldrh	w1, [x19]
	mov	w2, 65535
	cmp	w1, w2
	beq	.L2054
	ldr	x2, [x19, 16]
	ubfiz	x1, x1, 1, 16
	sub	w0, w0, #1
	ldrh	w1, [x2, x1]
	mov	w2, 1
	orr	w0, w0, w1, lsl 10
	mov	w1, w2
	str	w0, [x21, 4]
	mov	x0, x21
	bl	FlashReadPages
	ldr	w0, [x23, #:lo12:.LANCHOR211]
	cmn	w0, #1
	beq	.L2054
	ldrh	w1, [x24, 8]
	ldr	x2, [x19, 40]
	ubfiz	x0, x1, 2, 16
	ldr	w2, [x2, x0]
	ldr	w0, [x21, 4]
	cmp	w2, w0
	bne	.L2054
	ldr	x2, [x21, 8]
.L2067:
	mov	x0, x19
	ldr	x25, [sp, 64]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 80
	b	FtlMapWritePage
.L2054:
	sub	w20, w20, #1
	and	w20, w20, 65535
	ubfiz	x0, x20, 2, 16
	ldr	w1, [x25, x0]
	add	x0, x22, :lo12:.LANCHOR211
	str	w1, [x0, 4]
	cbz	w1, .L2055
	mov	w2, 1
	mov	w1, w2
	bl	FlashReadPages
.L2056:
	add	x22, x22, :lo12:.LANCHOR211
	mov	w1, w20
	ldr	x2, [x22, 8]
	b	.L2067
.L2055:
	adrp	x1, .LANCHOR57
	ldr	x0, [x0, 8]
	ldrh	w2, [x1, #:lo12:.LANCHOR57]
	mov	w1, 255
	bl	ftl_memset
	b	.L2056
.L2050:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldr	x25, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
.L2064:
	ret
	.size	FtlMapBlkWriteDumpData, .-FtlMapBlkWriteDumpData
	.section	.text.FtlScanSysBlk,"ax",@progbits
	.align	2
	.global	FtlScanSysBlk
	.type	FtlScanSysBlk, %function
FtlScanSysBlk:
	stp	x29, x30, [sp, -176]!
	mov	w1, 0
	add	x29, sp, 0
	stp	x25, x26, [sp, 64]
	adrp	x25, .LANCHOR133
	stp	x21, x22, [sp, 32]
	adrp	x21, .LANCHOR64
	ldr	x0, [x25, #:lo12:.LANCHOR133]
	adrp	x22, .LANCHOR201
	ldr	w2, [x21, #:lo12:.LANCHOR64]
	stp	x19, x20, [sp, 16]
	adrp	x20, .LANCHOR131
	stp	x23, x24, [sp, 48]
	adrp	x23, .LANCHOR70
	stp	x27, x28, [sp, 80]
	adrp	x27, .LANCHOR132
	lsl	w2, w2, 2
	strh	wzr, [x20, #:lo12:.LANCHOR131]
	strh	wzr, [x23, #:lo12:.LANCHOR70]
	bl	ftl_memset
	ldr	x0, [x27, #:lo12:.LANCHOR132]
	mov	w1, 0
	ldr	w2, [x21, #:lo12:.LANCHOR64]
	adrp	x19, .LANCHOR61
	adrp	x28, .LANCHOR71
	adrp	x24, .LANCHOR218
	lsl	w2, w2, 1
	bl	ftl_memset
	ldr	x0, [x22, #:lo12:.LANCHOR201]
	mov	w1, 0
	ldrh	w2, [x19, #:lo12:.LANCHOR61]
	lsl	w2, w2, 2
	bl	ftl_memset
	ldr	x0, [x28, #:lo12:.LANCHOR71]
	mov	w1, 0
	ldrh	w2, [x19, #:lo12:.LANCHOR61]
	lsl	w2, w2, 1
	bl	ftl_memset
	mov	w2, 16
	mov	w1, 255
	add	x0, x24, :lo12:.LANCHOR218
	bl	ftl_memset
	adrp	x0, .LANCHOR40
	stp	x22, x25, [x29, 144]
	str	x27, [x29, 160]
	ldrh	w0, [x0, #:lo12:.LANCHOR40]
	str	w0, [x29, 172]
	adrp	x0, .LANCHOR41
	add	x0, x0, :lo12:.LANCHOR41
	str	x0, [x29, 120]
	adrp	x0, .LANCHOR164
	add	x0, x0, :lo12:.LANCHOR164
	str	x0, [x29, 112]
.L2069:
	ldr	x0, [x29, 120]
	ldr	w1, [x29, 172]
	ldrh	w0, [x0]
	cmp	w0, w1
	bls	.L2110
	adrp	x0, .LANCHOR38
	adrp	x25, .LANCHOR186
	adrp	x6, .LANCHOR47
	mov	x5, 0
	ldrh	w13, [x0, #:lo12:.LANCHOR38]
	adrp	x0, .LANCHOR107
	ldr	x7, [x25, #:lo12:.LANCHOR186]
	mov	w22, 0
	ldr	x12, [x0, #:lo12:.LANCHOR107]
	adrp	x0, .LANCHOR108
	add	x6, x6, :lo12:.LANCHOR47
	mov	w8, 56
	ldr	x11, [x0, #:lo12:.LANCHOR108]
	adrp	x0, .LANCHOR58
	ldrh	w10, [x0, #:lo12:.LANCHOR58]
	b	.L2111
.L2071:
	ldrh	w1, [x29, 172]
	ldrb	w0, [x6, x5]
	bl	V2P_block
	and	w4, w0, 65535
	bl	FtlBbmIsBadBlock
	cbnz	w0, .L2070
	umaddl	x1, w22, w8, x7
	lsl	w4, w4, 10
	mul	w0, w22, w10
	add	w22, w22, 1
	and	w22, w22, 65535
	asr	w0, w0, 2
	str	w4, [x1, 4]
	add	x0, x11, x0, sxtw 2
	stp	x12, x0, [x1, 8]
.L2070:
	add	x5, x5, 1
.L2111:
	cmp	w13, w5, uxth
	bhi	.L2071
	cbnz	w22, .L2072
.L2109:
	ldr	w0, [x29, 172]
	add	w26, w0, 1
	and	w0, w26, 65535
	str	w0, [x29, 172]
	b	.L2069
.L2072:
	mov	w1, w22
	mov	w2, 1
	mov	x0, x7
	bl	FlashReadPages
	mov	w0, 56
	umull	x0, w22, w0
	mov	x22, 0
	str	x0, [x29, 128]
	adrp	x0, .LANCHOR229
	add	x0, x0, :lo12:.LANCHOR229
	str	x0, [x29, 136]
.L2108:
	ldr	x0, [x25, #:lo12:.LANCHOR186]
	add	x1, x0, x22
	ldr	w0, [x0, x22]
	ldr	w3, [x1, 4]
	cmn	w0, #1
	ldr	x27, [x1, 16]
	ubfx	x26, x3, 10, 16
	bne	.L2075
	mov	w5, 16
	mov	w7, 65535
.L2077:
	ldr	x0, [x25, #:lo12:.LANCHOR186]
	add	x6, x25, :lo12:.LANCHOR186
	mov	w2, 1
	str	w7, [x29, 100]
	add	x0, x0, x22
	str	x6, [x29, 104]
	str	w5, [x29, 168]
	ldr	w1, [x0, 4]
	add	w1, w1, 1
	str	w1, [x0, 4]
	mov	w1, w2
	bl	FlashReadPages
	ldrh	w0, [x27]
	ldr	w7, [x29, 100]
	ldr	w5, [x29, 168]
	cmp	w0, w7
	ldr	x6, [x29, 104]
	bne	.L2074
	ldr	x0, [x6]
	mov	w1, -1
	str	w1, [x0, x22]
	ldr	x0, [x6]
	ldr	w0, [x0, x22]
	cmp	w0, w1
	beq	.L2147
.L2075:
	adrp	x0, .LANCHOR164
	ldr	w1, [x0, #:lo12:.LANCHOR164]
	ldr	w0, [x27, 4]
	cmn	w1, #1
	beq	.L2078
	cmp	w1, w0
	bhi	.L2079
.L2078:
	cmn	w0, #1
	beq	.L2079
	ldr	x2, [x29, 112]
	add	w1, w0, 1
	str	w1, [x2]
.L2079:
	ldrh	w1, [x27]
	mov	w2, 61604
	cmp	w1, w2
	beq	.L2081
	bhi	.L2082
	mov	w0, 61574
	cmp	w1, w0
	beq	.L2083
.L2080:
	ldr	x0, [x29, 128]
	add	x22, x22, 56
	cmp	x0, x22
	bne	.L2108
	b	.L2109
.L2074:
	ldr	x0, [x25, #:lo12:.LANCHOR186]
	ldr	w0, [x0, x22]
	cmn	w0, #1
	bne	.L2075
	sub	w5, w5, #1
	ands	w5, w5, 65535
	bne	.L2077
.L2147:
	mov	w1, 0
	mov	w0, w26
	bl	FtlFreeSysBlkQueueIn
	b	.L2080
.L2082:
	mov	w0, 61634
	cmp	w1, w0
	beq	.L2084
	mov	w0, 65535
	cmp	w1, w0
	beq	.L2147
	b	.L2080
.L2084:
	ldrh	w1, [x20, #:lo12:.LANCHOR131]
	ldr	w0, [x21, #:lo12:.LANCHOR64]
	cmp	w1, w0
	bls	.L2086
	ldr	x1, [x29, 136]
	mov	w2, 1469
	adrp	x0, .LC5
	add	x0, x0, :lo12:.LC5
	bl	printf
	adrp	x1, .LC6
	adrp	x0, .LC7
	add	x1, x1, :lo12:.LC6
	add	x0, x0, :lo12:.LC7
	bl	printf
.L2086:
	ldr	w6, [x21, #:lo12:.LANCHOR64]
	ldr	x3, [x29, 152]
	ldrh	w1, [x20, #:lo12:.LANCHOR131]
	and	w2, w6, 65535
	sub	w0, w2, #1
	sub	w2, w2, w1
	sxth	x0, w0
	sub	w2, w2, #1
	ldr	x5, [x3, #:lo12:.LANCHOR133]
	sxth	w2, w2
.L2087:
	cmp	w0, w2
	bgt	.L2093
	tbz	w0, #31, .L2128
	b	.L2080
.L2093:
	sxtw	x8, w0
	ldr	w11, [x27, 4]
	lsl	x7, x8, 2
	add	x10, x5, x7
	ldr	w7, [x5, x7]
	cmp	w11, w7
	bls	.L2088
	ldr	w2, [x5]
	cbnz	w2, .L2089
	cmp	w6, w1
	beq	.L2089
	add	w1, w1, 1
	strh	w1, [x20, #:lo12:.LANCHOR131]
.L2089:
	ldr	x1, [x29, 160]
	ldr	x6, [x1, #:lo12:.LANCHOR132]
	mov	w1, 0
.L2090:
	cmp	w1, w0
	bne	.L2091
	ldr	w1, [x27, 4]
	str	w1, [x10]
	strh	w26, [x6, x8, lsl 1]
	tbnz	w0, #31, .L2080
	ldrh	w1, [x20, #:lo12:.LANCHOR131]
	ldr	w2, [x21, #:lo12:.LANCHOR64]
	sub	w2, w2, w1
	sub	w2, w2, #1
	cmp	w0, w2, sxth
	bgt	.L2080
.L2128:
	add	w1, w1, 1
	strh	w1, [x20, #:lo12:.LANCHOR131]
	ldr	w1, [x27, 4]
	str	w1, [x5, x0, lsl 2]
	ldr	x1, [x29, 160]
	ldr	x1, [x1, #:lo12:.LANCHOR132]
.L2146:
	strh	w26, [x1, x0, lsl 1]
	b	.L2080
.L2091:
	sxtw	x2, w1
	add	w1, w1, 1
	lsl	x7, x2, 2
	lsl	x2, x2, 1
	add	x11, x5, x7
	sxth	w1, w1
	ldr	w11, [x11, 4]
	str	w11, [x5, x7]
	add	x7, x6, x2
	ldrh	w7, [x7, 2]
	strh	w7, [x6, x2]
	b	.L2090
.L2088:
	sub	w0, w0, #1
	sxth	x0, w0
	b	.L2087
.L2083:
	ldrh	w1, [x23, #:lo12:.LANCHOR70]
	ldrh	w0, [x19, #:lo12:.LANCHOR61]
	cmp	w1, w0
	bls	.L2096
	ldr	x1, [x29, 136]
	mov	w2, 1513
	adrp	x0, .LC5
	add	x0, x0, :lo12:.LC5
	bl	printf
	adrp	x1, .LC6
	adrp	x0, .LC7
	add	x1, x1, :lo12:.LC6
	add	x0, x0, :lo12:.LC7
	bl	printf
.L2096:
	ldrh	w6, [x19, #:lo12:.LANCHOR61]
	ldrh	w2, [x23, #:lo12:.LANCHOR70]
	sub	w1, w6, #1
	sxth	x0, w1
	sub	w5, w1, w2
	ldr	x1, [x29, 144]
	ldr	x1, [x1, #:lo12:.LANCHOR201]
.L2097:
	cmp	w0, w5
	ble	.L2102
	sxtw	x7, w0
	ldr	w11, [x27, 4]
	lsl	x8, x7, 2
	add	x10, x1, x8
	ldr	w8, [x1, x8]
	cmp	w11, w8
	bls	.L2098
	ldr	w5, [x1]
	cbnz	w5, .L2099
	cmp	w6, w2
	beq	.L2099
	add	w2, w2, 1
	strh	w2, [x23, #:lo12:.LANCHOR70]
.L2099:
	ldr	x6, [x28, #:lo12:.LANCHOR71]
	mov	w2, 0
.L2100:
	cmp	w2, w0
	bne	.L2101
	ldr	w2, [x27, 4]
	str	w2, [x10]
	strh	w26, [x6, x7, lsl 1]
.L2102:
	tbnz	w0, #31, .L2080
	ldrh	w2, [x19, #:lo12:.LANCHOR61]
	ldrh	w5, [x23, #:lo12:.LANCHOR70]
	sub	w2, w2, #1
	sub	w2, w2, w5
	cmp	w0, w2, sxth
	bgt	.L2080
	add	w5, w5, 1
	ldr	w2, [x27, 4]
	strh	w5, [x23, #:lo12:.LANCHOR70]
	str	w2, [x1, x0, lsl 2]
	ldr	x1, [x28, #:lo12:.LANCHOR71]
	b	.L2146
.L2101:
	sxtw	x5, w2
	add	w2, w2, 1
	lsl	x8, x5, 2
	lsl	x5, x5, 1
	add	x11, x1, x8
	sxth	w2, w2
	ldr	w11, [x11, 4]
	str	w11, [x1, x8]
	add	x8, x6, x5
	ldrh	w8, [x8, 2]
	strh	w8, [x6, x5]
	b	.L2100
.L2098:
	sub	w0, w0, #1
	sxth	x0, w0
	b	.L2097
.L2081:
	ldrh	w5, [x24, #:lo12:.LANCHOR218]
	mov	w1, 65535
	add	x2, x24, :lo12:.LANCHOR218
	cmp	w5, w1
	bne	.L2104
	strh	w26, [x24, #:lo12:.LANCHOR218]
	str	w0, [x2, 8]
	b	.L2080
.L2104:
	ldrh	w0, [x2, 4]
	cmp	w0, w1
	beq	.L2105
	mov	w1, 1
	bl	FtlFreeSysBlkQueueIn
.L2105:
	add	x0, x24, :lo12:.LANCHOR218
	ldr	w1, [x27, 4]
	ldr	w2, [x0, 8]
	cmp	w2, w1
	bcs	.L2106
	ldrh	w2, [x24, #:lo12:.LANCHOR218]
	strh	w2, [x0, 4]
	strh	w26, [x24, #:lo12:.LANCHOR218]
	str	w1, [x0, 8]
	b	.L2080
.L2106:
	strh	w26, [x0, 4]
	b	.L2080
.L2110:
	ldr	x0, [x29, 160]
	ldr	x2, [x0, #:lo12:.LANCHOR132]
	ldrh	w0, [x2]
	cbz	w0, .L2112
.L2115:
	ldr	x1, [x28, #:lo12:.LANCHOR71]
	ldrh	w0, [x1]
	cbz	w0, .L2113
.L2114:
	ldrh	w1, [x20, #:lo12:.LANCHOR131]
	ldr	w0, [x21, #:lo12:.LANCHOR64]
	cmp	w1, w0
	bls	.L2144
	mov	w2, 1631
	adrp	x1, .LANCHOR229
	adrp	x0, .LC5
	add	x1, x1, :lo12:.LANCHOR229
	add	x0, x0, :lo12:.LC5
	bl	printf
	adrp	x1, .LC6
	adrp	x0, .LC7
	add	x1, x1, :lo12:.LC6
	add	x0, x0, :lo12:.LC7
	bl	printf
.L2144:
	ldp	x19, x20, [sp, 16]
	mov	w0, 0
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 176
	ret
.L2112:
	ldrh	w0, [x20, #:lo12:.LANCHOR131]
	cbz	w0, .L2115
	ldr	w1, [x21, #:lo12:.LANCHOR64]
	mov	w0, 0
.L2116:
	cmp	w0, w1
	bcs	.L2115
	ldrh	w3, [x2, w0, sxtw 1]
	cbz	w3, .L2117
	ldr	x1, [x29, 152]
	add	x7, x21, :lo12:.LANCHOR64
	ldr	x4, [x1, #:lo12:.LANCHOR133]
	mov	w1, w0
.L2118:
	ldr	w3, [x7]
	cmp	w1, w3
	bcs	.L2115
	sxtw	x6, w1
	sub	w3, w1, w0
	lsl	x5, x6, 1
	sxtw	x3, w3
	add	w1, w1, 1
	ldr	w6, [x4, x6, lsl 2]
	sxth	w1, w1
	ldrh	w8, [x2, x5]
	strh	w8, [x2, x3, lsl 1]
	str	w6, [x4, x3, lsl 2]
	strh	wzr, [x2, x5]
	b	.L2118
.L2117:
	add	w0, w0, 1
	sxth	w0, w0
	b	.L2116
.L2113:
	ldrh	w0, [x23, #:lo12:.LANCHOR70]
	cbz	w0, .L2114
	ldrh	w2, [x19, #:lo12:.LANCHOR61]
	mov	w0, 0
.L2123:
	mov	w6, w0
	cmp	w0, w2
	bge	.L2114
	ldrh	w3, [x1, w0, sxtw 1]
	cbz	w3, .L2124
	ldr	x2, [x29, 144]
	add	x19, x19, :lo12:.LANCHOR61
	ldr	x3, [x2, #:lo12:.LANCHOR201]
.L2125:
	ldrh	w2, [x19]
	cmp	w0, w2
	bge	.L2114
	sxtw	x5, w0
	sub	w2, w0, w6
	lsl	x4, x5, 1
	sxtw	x2, w2
	add	w0, w0, 1
	ldr	w5, [x3, x5, lsl 2]
	sxth	w0, w0
	ldrh	w7, [x1, x4]
	strh	w7, [x1, x2, lsl 1]
	str	w5, [x3, x2, lsl 2]
	strh	wzr, [x1, x4]
	b	.L2125
.L2124:
	add	w0, w0, 1
	sxth	w0, w0
	b	.L2123
	.size	FtlScanSysBlk, .-FtlScanSysBlk
	.section	.text.FtlLoadSysInfo,"ax",@progbits
	.align	2
	.global	FtlLoadSysInfo
	.type	FtlLoadSysInfo, %function
FtlLoadSysInfo:
	sub	sp, sp, #128
	stp	x29, x30, [sp, 16]
	add	x29, sp, 16
	stp	x23, x24, [sp, 64]
	adrp	x23, .LANCHOR189
	stp	x19, x20, [sp, 32]
	adrp	x19, .LANCHOR211
	add	x0, x19, :lo12:.LANCHOR211
	stp	x25, x26, [sp, 80]
	adrp	x25, .LANCHOR195
	stp	x21, x22, [sp, 48]
	stp	x27, x28, [sp, 96]
	adrp	x24, .LANCHOR85
	ldr	x1, [x23, #:lo12:.LANCHOR189]
	adrp	x22, .LANCHOR40
	str	x1, [x0, 8]
	adrp	x21, .LANCHOR218
	ldr	x1, [x25, #:lo12:.LANCHOR195]
	str	x1, [x0, 16]
	ldr	x0, [x24, #:lo12:.LANCHOR85]
	mov	w1, 0
	ldrh	w2, [x22, #:lo12:.LANCHOR40]
	lsl	w2, w2, 1
	bl	ftl_memset
	ldrh	w0, [x21, #:lo12:.LANCHOR218]
	mov	w1, 65535
	cmp	w0, w1
	bne	.L2149
.L2161:
	mov	w0, -1
.L2148:
	ldp	x19, x20, [sp, 32]
	ldp	x21, x22, [sp, 48]
	ldp	x23, x24, [sp, 64]
	ldp	x25, x26, [sp, 80]
	ldp	x27, x28, [sp, 96]
	ldp	x29, x30, [sp, 16]
	add	sp, sp, 128
	ret
.L2149:
	add	x26, x21, :lo12:.LANCHOR218
	mov	w1, 1
	bl	FtlGetLastWrittenPage
	ldrsh	w28, [x21, #:lo12:.LANCHOR218]
	sxth	w20, w0
	adrp	x27, .LANCHOR57
	add	w0, w0, 1
	add	x27, x27, :lo12:.LANCHOR57
	strh	w0, [x26, 2]
	adrp	x26, .LANCHOR2
	add	x0, x26, :lo12:.LANCHOR2
	str	x0, [x29, 104]
.L2151:
	tbz	w20, #31, .L2157
	mov	w2, 1708
	adrp	x1, .LANCHOR230
	adrp	x0, .LC5
	add	x1, x1, :lo12:.LANCHOR230
	add	x0, x0, :lo12:.LC5
	bl	printf
	adrp	x1, .LC6
	adrp	x0, .LC7
	add	x1, x1, :lo12:.LC6
	add	x0, x0, :lo12:.LC7
	bl	printf
	b	.L2156
.L2157:
	add	x26, x19, :lo12:.LANCHOR211
	orr	w0, w20, w28, lsl 10
	mov	w2, 1
	mov	w1, w2
	str	w0, [x26, 4]
	ldr	x0, [x23, #:lo12:.LANCHOR189]
	str	x0, [x26, 8]
	mov	x0, x26
	bl	FlashReadPages
	ldr	x0, [x29, 104]
	ldrb	w0, [x0]
	cbz	w0, .L2152
	ldr	x8, [x26, 16]
	ldr	w7, [x8, 12]
	cbz	w7, .L2152
	ldr	x6, [x26, 8]
	ldrh	w1, [x27]
	mov	x0, x6
	bl	js_hash
	cmp	w7, w0
	beq	.L2152
	cbnz	w20, .L2153
	add	x10, x21, :lo12:.LANCHOR218
	str	x10, [x29, 96]
	ldrh	w0, [x10, 4]
	cmp	w28, w0
	beq	.L2153
	ldr	w0, [x6]
	str	w0, [sp]
	ldrh	w1, [x21, #:lo12:.LANCHOR218]
	adrp	x0, .LC47
	ldr	w2, [x19, #:lo12:.LANCHOR211]
	add	x0, x0, :lo12:.LC47
	ldp	w4, w5, [x8]
	ldr	w6, [x8, 8]
	ldr	w3, [x26, 4]
	bl	printf
	ldr	x10, [x29, 96]
	adrp	x0, .LANCHOR53
	ldrh	w20, [x0, #:lo12:.LANCHOR53]
	ldrsh	w28, [x10, 4]
.L2155:
	sub	w20, w20, #1
	sxth	w20, w20
	b	.L2151
.L2153:
	mov	w0, -1
	str	w0, [x19, #:lo12:.LANCHOR211]
.L2152:
	ldr	w0, [x19, #:lo12:.LANCHOR211]
	cmn	w0, #1
	beq	.L2155
	ldr	x0, [x23, #:lo12:.LANCHOR189]
	mov	w1, 19539
	movk	w1, 0x4654, lsl 16
	ldr	w0, [x0]
	cmp	w0, w1
	bne	.L2155
	ldr	x0, [x25, #:lo12:.LANCHOR195]
	ldrh	w1, [x0]
	mov	w0, 61604
	cmp	w1, w0
	bne	.L2155
.L2156:
	adrp	x1, .LANCHOR57
	ldrh	w0, [x22, #:lo12:.LANCHOR40]
	ldrh	w1, [x1, #:lo12:.LANCHOR57]
	add	x0, x0, 24
	cmp	x1, x0, lsl 1
	bcs	.L2159
	mov	w2, 1710
	adrp	x1, .LANCHOR230
	adrp	x0, .LC5
	add	x1, x1, :lo12:.LANCHOR230
	add	x0, x0, :lo12:.LC5
	bl	printf
	adrp	x1, .LC6
	adrp	x0, .LC7
	add	x1, x1, :lo12:.LC6
	add	x0, x0, :lo12:.LC7
	bl	printf
.L2159:
	add	x19, x19, :lo12:.LANCHOR211
	mov	w2, 48
	adrp	x20, .LANCHOR82
	add	x0, x20, :lo12:.LANCHOR82
	ldr	x1, [x19, 8]
	bl	ftl_memcpy
	ldr	x0, [x24, #:lo12:.LANCHOR85]
	ldrh	w2, [x22, #:lo12:.LANCHOR40]
	ldr	x1, [x19, 8]
	lsl	w2, w2, 1
	add	x1, x1, 48
	bl	ftl_memcpy
	ldrh	w1, [x22, #:lo12:.LANCHOR40]
	ldr	x0, [x19, 8]
	lsr	w2, w1, 3
	ubfiz	x1, x1, 1, 16
	add	x1, x1, 51
	add	w2, w2, 4
	and	x1, x1, -4
	add	x1, x0, x1
	adrp	x0, .LANCHOR1
	ldr	x0, [x0, #:lo12:.LANCHOR1]
	bl	ftl_memcpy
	adrp	x0, .LANCHOR69
	ldrh	w0, [x0, #:lo12:.LANCHOR69]
	cbz	w0, .L2160
	ldrh	w1, [x22, #:lo12:.LANCHOR40]
	adrp	x0, .LANCHOR66
	ldrh	w2, [x0, #:lo12:.LANCHOR66]
	lsr	w0, w1, 3
	add	w1, w0, w1, lsl 1
	ldr	x0, [x19, 8]
	add	w1, w1, 52
	lsl	w2, w2, 2
	and	x1, x1, 65532
	add	x1, x0, x1
	adrp	x0, .LANCHOR203
	ldr	x0, [x0, #:lo12:.LANCHOR203]
	bl	ftl_memcpy
.L2160:
	ldr	w2, [x20, #:lo12:.LANCHOR82]
	mov	w1, 19539
	movk	w1, 0x4654, lsl 16
	add	x0, x20, :lo12:.LANCHOR82
	cmp	w2, w1
	bne	.L2161
	add	x21, x21, :lo12:.LANCHOR218
	ldrh	w1, [x0, 8]
	ldrb	w2, [x0, 10]
	adrp	x0, .LANCHOR45
	strh	w1, [x21, 6]
	ldrh	w0, [x0, #:lo12:.LANCHOR45]
	cmp	w2, w0
	bne	.L2161
	adrp	x0, .LANCHOR231
	adrp	x2, .LANCHOR74
	adrp	x3, .LANCHOR38
	str	w1, [x0, #:lo12:.LANCHOR231]
	adrp	x0, .LANCHOR52
	ldrh	w3, [x3, #:lo12:.LANCHOR38]
	ldrh	w0, [x0, #:lo12:.LANCHOR52]
	mul	w0, w0, w1
	str	w0, [x2, #:lo12:.LANCHOR74]
	adrp	x2, .LANCHOR55
	ldrh	w2, [x2, #:lo12:.LANCHOR55]
	mul	w0, w2, w0
	adrp	x2, .LANCHOR68
	str	w0, [x2, #:lo12:.LANCHOR68]
	adrp	x0, .LANCHOR42
	ldr	w2, [x0, #:lo12:.LANCHOR42]
	adrp	x0, .LANCHOR76+6
	ldrh	w0, [x0, #:lo12:.LANCHOR76+6]
	cmp	w1, w2
	sub	w0, w2, w0
	sub	w0, w0, w1
	udiv	w0, w0, w3
	adrp	x3, .LANCHOR232
	strh	w0, [x3, #:lo12:.LANCHOR232]
	bls	.L2162
	mov	w2, 1739
	adrp	x1, .LANCHOR230
	adrp	x0, .LC5
	add	x1, x1, :lo12:.LANCHOR230
	add	x0, x0, :lo12:.LC5
	bl	printf
	adrp	x1, .LC6
	adrp	x0, .LC7
	add	x1, x1, :lo12:.LC6
	add	x0, x0, :lo12:.LC7
	bl	printf
.L2162:
	add	x4, x20, :lo12:.LANCHOR82
	adrp	x0, .LANCHOR93
	add	x2, x0, :lo12:.LANCHOR93
	adrp	x5, .LANCHOR213
	adrp	x19, .LANCHOR94
	mov	x22, x5
	ldrh	w1, [x4, 16]
	ldrh	w6, [x4, 14]
	strh	w6, [x0, #:lo12:.LANCHOR93]
	lsr	w3, w1, 6
	and	w1, w1, 63
	strb	w1, [x2, 6]
	ldrb	w1, [x4, 11]
	strb	w1, [x2, 8]
	add	x1, x5, :lo12:.LANCHOR213
	strh	w3, [x2, 2]
	mov	w2, -1
	strh	w2, [x5, #:lo12:.LANCHOR213]
	add	x2, x19, :lo12:.LANCHOR94
	strh	wzr, [x1, 2]
	strb	wzr, [x1, 6]
	strb	wzr, [x1, 8]
	ldrh	w1, [x4, 18]
	strh	w1, [x19, #:lo12:.LANCHOR94]
	ldrh	w1, [x4, 20]
	lsr	w3, w1, 6
	and	w1, w1, 63
	strb	w1, [x2, 6]
	ldrb	w1, [x4, 12]
	strh	w3, [x2, 2]
	strb	w1, [x2, 8]
	adrp	x2, .LANCHOR95
	ldrh	w1, [x4, 22]
	add	x3, x2, :lo12:.LANCHOR95
	strh	w1, [x2, #:lo12:.LANCHOR95]
	mov	x21, x2
	ldrh	w1, [x4, 24]
	lsr	w7, w1, 6
	and	w1, w1, 63
	strb	w1, [x3, 6]
	ldrb	w1, [x4, 13]
	strb	w1, [x3, 8]
	adrp	x1, .LANCHOR166
	strh	w7, [x3, 2]
	ldr	w3, [x4, 32]
	str	wzr, [x1, #:lo12:.LANCHOR166]
	adrp	x1, .LANCHOR167
	str	wzr, [x1, #:lo12:.LANCHOR167]
	adrp	x1, .LANCHOR171
	str	wzr, [x1, #:lo12:.LANCHOR171]
	adrp	x1, .LANCHOR170
	str	wzr, [x1, #:lo12:.LANCHOR170]
	adrp	x1, .LANCHOR172
	str	w3, [x1, #:lo12:.LANCHOR172]
	adrp	x1, .LANCHOR173
	str	wzr, [x1, #:lo12:.LANCHOR173]
	adrp	x1, .LANCHOR174
	str	wzr, [x1, #:lo12:.LANCHOR174]
	adrp	x1, .LANCHOR169
	ldr	w3, [x4, 40]
	str	wzr, [x1, #:lo12:.LANCHOR169]
	adrp	x1, .LANCHOR164
	ldr	w4, [x1, #:lo12:.LANCHOR164]
	cmp	w3, w4
	bls	.L2163
	str	w3, [x1, #:lo12:.LANCHOR164]
.L2163:
	add	x20, x20, :lo12:.LANCHOR82
	adrp	x1, .LANCHOR165
	ldr	w3, [x1, #:lo12:.LANCHOR165]
	ldr	w2, [x20, 36]
	cmp	w2, w3
	bls	.L2164
	str	w2, [x1, #:lo12:.LANCHOR165]
.L2164:
	mov	w1, 65535
	cmp	w6, w1
	beq	.L2165
	add	x0, x0, :lo12:.LANCHOR93
	bl	make_superblock
.L2165:
	ldrh	w2, [x19, #:lo12:.LANCHOR94]
	mov	w1, 65535
	add	x0, x19, :lo12:.LANCHOR94
	cmp	w2, w1
	beq	.L2166
	bl	make_superblock
.L2166:
	ldrh	w2, [x21, #:lo12:.LANCHOR95]
	mov	w1, 65535
	add	x0, x21, :lo12:.LANCHOR95
	cmp	w2, w1
	beq	.L2167
	bl	make_superblock
.L2167:
	ldrh	w2, [x22, #:lo12:.LANCHOR213]
	mov	w1, 65535
	add	x0, x22, :lo12:.LANCHOR213
	cmp	w2, w1
	beq	.L2168
	bl	make_superblock
.L2168:
	mov	w0, 0
	b	.L2148
	.size	FtlLoadSysInfo, .-FtlLoadSysInfo
	.section	.text.FtlDumpBlockInfo,"ax",@progbits
	.align	2
	.global	FtlDumpBlockInfo
	.type	FtlDumpBlockInfo, %function
FtlDumpBlockInfo:
	sub	sp, sp, #160
	lsr	w0, w0, 10
	stp	x29, x30, [sp, 16]
	add	x29, sp, 16
	stp	x19, x20, [sp, 32]
	adrp	x19, .LANCHOR52
	stp	x21, x22, [sp, 48]
	and	w22, w1, 255
	stp	x23, x24, [sp, 64]
	add	x23, x29, 144
	stp	x25, x26, [sp, 80]
	str	x27, [sp, 96]
	bl	P2V_block_in_plane
	ldrh	w25, [x19, #:lo12:.LANCHOR52]
	and	w21, w0, 65535
	adrp	x1, .LANCHOR233
	adrp	x0, .LC48
	add	x1, x1, :lo12:.LANCHOR233
	add	x0, x0, :lo12:.LC48
	bl	printf
	adrp	x1, .LANCHOR85
	ubfiz	x0, x21, 1, 16
	ldr	x1, [x1, #:lo12:.LANCHOR85]
	ldrh	w2, [x1, x0]
	mov	w1, w21
	adrp	x0, .LC49
	add	x0, x0, :lo12:.LC49
	bl	printf
	strh	w21, [x23, -48]!
	mov	x0, x23
	bl	make_superblock
	adrp	x0, .LANCHOR16
	ldrb	w0, [x0, #:lo12:.LANCHOR16]
	cbz	w0, .L2193
	cbnz	w22, .L2193
	mov	w0, w21
	bl	ftl_get_blk_mode
	mov	w21, w0
	cmp	w0, 1
	bne	.L2184
	adrp	x0, .LANCHOR53
	ldrh	w25, [x0, #:lo12:.LANCHOR53]
.L2184:
	ldrh	w3, [x19, #:lo12:.LANCHOR52]
	adrp	x26, .LC51
	add	x26, x26, :lo12:.LC51
	mov	w20, 0
	mov	w27, 56
	mov	w2, w25
	mov	w1, w21
	adrp	x0, .LC50
	add	x0, x0, :lo12:.LC50
	bl	printf
.L2185:
	adrp	x1, .LANCHOR107
	adrp	x0, .LANCHOR38
	adrp	x24, .LANCHOR186
	add	x3, x23, 16
	ldr	x6, [x1, #:lo12:.LANCHOR107]
	adrp	x1, .LANCHOR57
	ldrh	w5, [x0, #:lo12:.LANCHOR38]
	mov	w19, 0
	ldrh	w7, [x1, #:lo12:.LANCHOR57]
	adrp	x1, .LANCHOR108
	ldr	x0, [x24, #:lo12:.LANCHOR186]
	mov	w11, 65535
	ldr	x8, [x1, #:lo12:.LANCHOR108]
	adrp	x1, .LANCHOR58
	ldrh	w10, [x1, #:lo12:.LANCHOR58]
	mov	w1, 0
.L2186:
	cmp	w1, w5
	bne	.L2188
	mov	w1, w19
	umull	x19, w19, w27
	mov	x22, 0
	mov	w2, w21
	bl	FlashReadPages
.L2189:
	cmp	x22, x19
	bne	.L2190
	add	w20, w20, 1
	and	w20, w20, 65535
	cmp	w25, w20
	bne	.L2185
.L2191:
	ldp	x19, x20, [sp, 32]
	mov	w0, 0
	ldp	x21, x22, [sp, 48]
	ldp	x23, x24, [sp, 64]
	ldp	x25, x26, [sp, 80]
	ldp	x29, x30, [sp, 16]
	ldr	x27, [sp, 96]
	add	sp, sp, 160
	ret
.L2193:
	mov	w21, 0
	b	.L2184
.L2188:
	ldrh	w2, [x3]
	cmp	w2, w11
	beq	.L2187
	umaddl	x4, w19, w27, x0
	orr	w2, w20, w2, lsl 10
	str	w2, [x4, 4]
	mul	w2, w19, w7
	asr	w2, w2, 2
	add	x2, x6, x2, sxtw 2
	str	x2, [x4, 8]
	mul	w2, w19, w10
	add	w19, w19, 1
	and	w19, w19, 65535
	asr	w2, w2, 2
	add	x2, x8, x2, sxtw 2
	str	x2, [x4, 16]
.L2187:
	add	w1, w1, 1
	add	x3, x3, 2
	and	w1, w1, 65535
	b	.L2186
.L2190:
	ldr	x8, [x24, #:lo12:.LANCHOR186]
	ldrh	w1, [x29, 96]
	add	x2, x8, x22
	ldp	x3, x0, [x2, 8]
	ldr	w4, [x3, 4]
	str	w4, [sp, 8]
	ldr	w3, [x3]
	str	w3, [sp]
	ldp	w4, w5, [x0]
	ldp	w6, w7, [x0, 8]
	mov	x0, x26
	ldr	w3, [x2, 4]
	ldr	w2, [x8, x22]
	add	x22, x22, 56
	bl	printf
	b	.L2189
	.size	FtlDumpBlockInfo, .-FtlDumpBlockInfo
	.section	.text.FtlScanAllBlock,"ax",@progbits
	.align	2
	.global	FtlScanAllBlock
	.type	FtlScanAllBlock, %function
FtlScanAllBlock:
	sub	sp, sp, #144
	adrp	x1, .LANCHOR234
	adrp	x0, .LC48
	add	x1, x1, :lo12:.LANCHOR234
	add	x0, x0, :lo12:.LC48
	stp	x29, x30, [sp, 16]
	add	x29, sp, 16
	stp	x23, x24, [sp, 64]
	adrp	x23, .LANCHOR41
	stp	x19, x20, [sp, 32]
	adrp	x24, .LC53
	stp	x21, x22, [sp, 48]
	mov	w20, 0
	add	x23, x23, :lo12:.LANCHOR41
	add	x24, x24, :lo12:.LC53
	str	x25, [sp, 80]
	bl	printf
.L2197:
	ldrh	w0, [x23]
	cmp	w0, w20
	bhi	.L2205
	ldp	x19, x20, [sp, 32]
	mov	w0, 0
	ldp	x21, x22, [sp, 48]
	ldp	x23, x24, [sp, 64]
	ldp	x29, x30, [sp, 16]
	ldr	x25, [sp, 80]
	add	sp, sp, 144
	ret
.L2205:
	strh	w20, [x29, 80]
	mov	w0, w20
	bl	ftl_get_blk_mode
	mov	w3, w0
	adrp	x2, .LANCHOR85
	ubfiz	x1, x20, 1, 16
	adrp	x0, .LC52
	add	x0, x0, :lo12:.LC52
	ldr	x2, [x2, #:lo12:.LANCHOR85]
	adrp	x22, .LANCHOR186
	mov	w19, 0
	ldrh	w2, [x2, x1]
	mov	w1, w20
	bl	printf
	add	x0, x29, 80
	bl	make_superblock
	adrp	x1, .LANCHOR107
	adrp	x0, .LANCHOR38
	add	x3, x29, 96
	mov	w11, 65535
	ldr	x6, [x1, #:lo12:.LANCHOR107]
	adrp	x1, .LANCHOR57
	ldrh	w5, [x0, #:lo12:.LANCHOR38]
	mov	w12, 56
	ldrh	w7, [x1, #:lo12:.LANCHOR57]
	adrp	x1, .LANCHOR108
	ldr	x0, [x22, #:lo12:.LANCHOR186]
	ldr	x8, [x1, #:lo12:.LANCHOR108]
	adrp	x1, .LANCHOR58
	ldrh	w10, [x1, #:lo12:.LANCHOR58]
	mov	w1, 0
.L2198:
	cmp	w1, w5
	bne	.L2200
	mov	w25, 56
	mov	x21, 0
	mov	w2, 0
	mov	w1, w19
	umull	x25, w19, w25
	bl	FlashReadPages
.L2201:
	cmp	x21, x25
	bne	.L2202
	ldr	x0, [x22, #:lo12:.LANCHOR186]
	adrp	x25, .LC54
	add	x25, x25, :lo12:.LC54
	mov	w1, w19
	mov	x19, 0
	mov	w2, 1
	bl	FlashReadPages
.L2203:
	cmp	x21, x19
	bne	.L2204
	add	w20, w20, 1
	and	w20, w20, 65535
	b	.L2197
.L2200:
	ldrh	w2, [x3]
	cmp	w2, w11
	beq	.L2199
	umaddl	x4, w19, w12, x0
	lsl	w2, w2, 10
	str	w2, [x4, 4]
	mul	w2, w19, w7
	asr	w2, w2, 2
	add	x2, x6, x2, sxtw 2
	str	x2, [x4, 8]
	mul	w2, w19, w10
	add	w19, w19, 1
	and	w19, w19, 65535
	asr	w2, w2, 2
	add	x2, x8, x2, sxtw 2
	str	x2, [x4, 16]
.L2199:
	add	w1, w1, 1
	add	x3, x3, 2
	and	w1, w1, 65535
	b	.L2198
.L2202:
	ldr	x8, [x22, #:lo12:.LANCHOR186]
	ldrh	w1, [x29, 80]
	add	x2, x8, x21
	ldp	x3, x0, [x2, 8]
	ldr	w4, [x3, 4]
	str	w4, [sp, 8]
	ldr	w3, [x3]
	str	w3, [sp]
	ldp	w4, w5, [x0]
	ldp	w6, w7, [x0, 8]
	mov	x0, x24
	ldr	w3, [x2, 4]
	ldr	w2, [x8, x21]
	add	x21, x21, 56
	bl	printf
	b	.L2201
.L2204:
	ldr	x8, [x22, #:lo12:.LANCHOR186]
	ldrh	w1, [x29, 80]
	add	x2, x8, x19
	ldp	x3, x0, [x2, 8]
	ldr	w4, [x3, 4]
	str	w4, [sp, 8]
	ldr	w3, [x3]
	str	w3, [sp]
	ldp	w4, w5, [x0]
	ldp	w6, w7, [x0, 8]
	mov	x0, x25
	ldr	w3, [x2, 4]
	ldr	w2, [x8, x19]
	add	x19, x19, 56
	bl	printf
	b	.L2203
	.size	FtlScanAllBlock, .-FtlScanAllBlock
	.section	.text.FtlMapTblRecovery,"ax",@progbits
	.align	2
	.global	FtlMapTblRecovery
	.type	FtlMapTblRecovery, %function
FtlMapTblRecovery:
	stp	x29, x30, [sp, -160]!
	mov	w1, 0
	add	x29, sp, 0
	stp	x27, x28, [sp, 80]
	mov	x28, x0
	stp	x23, x24, [sp, 48]
	ldrh	w24, [x0, 6]
	stp	x21, x22, [sp, 32]
	adrp	x21, .LANCHOR189
	ldr	x22, [x0, 40]
	ldr	x23, [x0, 16]
	lsl	w2, w24, 2
	ldr	x0, [x0, 24]
	str	x0, [x29, 144]
	ldrh	w0, [x28, 8]
	stp	x19, x20, [sp, 16]
	mov	w19, 0
	stp	x25, x26, [sp, 64]
	adrp	x25, .LANCHOR53
	str	w0, [x29, 156]
	mov	x0, x22
	bl	ftl_memset
	stp	wzr, wzr, [x28, 48]
	adrp	x0, .LANCHOR211
	add	x4, x0, :lo12:.LANCHOR211
	ldr	x1, [x21, #:lo12:.LANCHOR189]
	mov	x27, x4
	str	x0, [x29, 128]
	str	x1, [x4, 8]
	adrp	x1, .LANCHOR195
	ldr	w0, [x29, 156]
	ldr	x20, [x1, #:lo12:.LANCHOR195]
	mov	w1, -1
	str	x20, [x4, 16]
	sub	w0, w0, #1
	strh	w1, [x28]
	strh	w1, [x28, 2]
	mov	w1, 1
	str	w0, [x29, 116]
	add	x0, x25, :lo12:.LANCHOR53
	str	w1, [x28, 56]
	str	x0, [x29, 104]
.L2208:
	ldr	w0, [x29, 156]
	cmp	w19, w0
	bge	.L2227
	ldr	w0, [x29, 116]
	sxtw	x26, w19
	cmp	w19, w0
	bne	.L2209
	lsl	x0, x26, 1
	mov	w1, 1
	add	x21, x23, x0
	adrp	x27, .LANCHOR57
	add	x27, x27, :lo12:.LANCHOR57
	mov	w25, 0
	ldrh	w0, [x23, x0]
	bl	FtlGetLastWrittenPage
	sxth	w23, w0
	add	w0, w0, 1
	strh	w0, [x28, 2]
	ldr	x0, [x29, 144]
	strh	w19, [x28]
	ldr	w0, [x0, x26, lsl 2]
	adrp	x26, .LANCHOR2
	str	w0, [x28, 48]
	add	x26, x26, :lo12:.LANCHOR2
	ldr	x0, [x29, 128]
	add	x19, x0, :lo12:.LANCHOR211
.L2210:
	cmp	w25, w23
	ble	.L2213
.L2227:
	mov	x0, x28
	bl	ftl_free_no_use_map_blk
	adrp	x0, .LANCHOR53
	ldrh	w1, [x28, 2]
	ldrh	w0, [x0, #:lo12:.LANCHOR53]
	cmp	w1, w0
	bne	.L2215
	mov	x0, x28
	bl	ftl_map_blk_alloc_new_blk
.L2215:
	mov	x0, x28
	bl	ftl_map_blk_gc
	mov	x0, x28
	bl	ftl_map_blk_gc
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 160
	ret
.L2213:
	ldrh	w0, [x21]
	mov	w2, 1
	mov	w1, w2
	orr	w0, w25, w0, lsl 10
	str	w0, [x19, 4]
	mov	x0, x19
	bl	FlashReadPages
	ldrb	w0, [x26]
	cbz	w0, .L2211
	ldr	x0, [x19, 16]
	ldr	w0, [x0, 12]
	str	w0, [x29, 156]
	uxtw	x0, w0
	cbz	w0, .L2211
	ldrh	w1, [x27]
	ldr	x0, [x19, 8]
	bl	js_hash
	ldr	w1, [x29, 156]
	cmp	w1, w0
	beq	.L2211
	mov	w0, -1
	str	w0, [x19]
.L2211:
	ldr	w0, [x19]
	cmn	w0, #1
	beq	.L2212
	ldrh	w0, [x20, 8]
	cmp	w24, w0
	bls	.L2212
	ldrh	w2, [x20]
	ldrh	w1, [x28, 4]
	cmp	w2, w1
	bne	.L2212
	ubfiz	x0, x0, 2, 16
	ldr	w1, [x19, 4]
	str	w1, [x22, x0]
.L2212:
	add	w25, w25, 1
	sxth	w25, w25
	b	.L2210
.L2209:
	lsl	x26, x26, 1
	ldr	x0, [x21, #:lo12:.LANCHOR189]
	str	x0, [x27, 8]
	add	x0, x23, x26
	ldrh	w1, [x25, #:lo12:.LANCHOR53]
	mov	w2, 1
	str	x0, [x29, 136]
	ldrh	w0, [x23, x26]
	sub	w1, w1, #1
	orr	w0, w1, w0, lsl 10
	mov	w1, w2
	str	w0, [x27, 4]
	mov	x0, x27
	bl	FlashReadPages
	ldr	w0, [x27]
	cmn	w0, #1
	beq	.L2229
	ldrh	w1, [x20]
	ldrh	w0, [x28, 4]
	cmp	w1, w0
	bne	.L2229
	ldrh	w1, [x20, 8]
	mov	w0, 64245
	cmp	w1, w0
	beq	.L2217
.L2229:
	adrp	x26, .LANCHOR57
	add	x26, x26, :lo12:.LANCHOR57
	adrp	x0, .LANCHOR2
	mov	w5, 0
	add	x0, x0, :lo12:.LANCHOR2
	str	x0, [x29, 120]
.L2218:
	ldr	x0, [x29, 104]
	ldrh	w0, [x0]
	cmp	w5, w0
	bge	.L2225
	ldr	x0, [x29, 136]
	mov	w2, 1
	str	w5, [x29, 152]
	mov	w1, w2
	ldrh	w0, [x0]
	orr	w0, w5, w0, lsl 10
	str	w0, [x27, 4]
	mov	x0, x27
	bl	FlashReadPages
	ldr	x0, [x29, 120]
	ldr	w5, [x29, 152]
	ldrb	w0, [x0]
	cbz	w0, .L2222
	ldr	x0, [x27, 16]
	ldr	w0, [x0, 12]
	str	w0, [x29, 152]
	uxtw	x0, w0
	cbz	w0, .L2222
	ldrh	w1, [x26]
	ldr	x0, [x27, 8]
	str	w5, [x29, 112]
	bl	js_hash
	ldr	w1, [x29, 152]
	ldr	w5, [x29, 112]
	cmp	w1, w0
	beq	.L2222
	mov	w0, -1
	str	w0, [x27]
.L2222:
	ldr	w0, [x27]
	cmn	w0, #1
	beq	.L2223
	ldrh	w0, [x20, 8]
	cmp	w24, w0
	bls	.L2223
	ldrh	w2, [x20]
	ldrh	w1, [x28, 4]
	cmp	w2, w1
	bne	.L2223
	ubfiz	x0, x0, 2, 16
	ldr	w1, [x27, 4]
	str	w1, [x22, x0]
.L2223:
	add	w5, w5, 1
	sxth	w5, w5
	b	.L2218
.L2217:
	ldrh	w5, [x25, #:lo12:.LANCHOR53]
	mov	w0, 0
	ldr	x6, [x21, #:lo12:.LANCHOR189]
	sub	w5, w5, #1
.L2219:
	cmp	w0, w5
	blt	.L2221
.L2225:
	add	w19, w19, 1
	sxth	w19, w19
	b	.L2208
.L2221:
	lsl	w2, w0, 1
	sxtw	x2, w2
	lsl	x1, x2, 2
	ldrh	w1, [x6, x1]
	cmp	w24, w1
	bls	.L2220
	add	x2, x2, 1
	ubfiz	x1, x1, 2, 16
	ldr	w2, [x6, x2, lsl 2]
	str	w2, [x22, x1]
.L2220:
	add	w0, w0, 1
	sxth	w0, w0
	b	.L2219
	.size	FtlMapTblRecovery, .-FtlMapTblRecovery
	.section	.text.FtlLoadVonderInfo,"ax",@progbits
	.align	2
	.global	FtlLoadVonderInfo
	.type	FtlLoadVonderInfo, %function
FtlLoadVonderInfo:
	stp	x29, x30, [sp, -16]!
	adrp	x1, .LANCHOR61
	adrp	x0, .LANCHOR224
	add	x0, x0, :lo12:.LANCHOR224
	add	x29, sp, 0
	ldrh	w1, [x1, #:lo12:.LANCHOR61]
	strh	w1, [x0, 10]
	mov	w1, -3962
	strh	w1, [x0, 4]
	adrp	x1, .LANCHOR70
	ldrh	w1, [x1, #:lo12:.LANCHOR70]
	strh	w1, [x0, 8]
	adrp	x1, .LANCHOR62
	ldrh	w1, [x1, #:lo12:.LANCHOR62]
	strh	w1, [x0, 6]
	adrp	x1, .LANCHOR71
	ldr	x1, [x1, #:lo12:.LANCHOR71]
	str	x1, [x0, 16]
	adrp	x1, .LANCHOR201
	ldr	x1, [x1, #:lo12:.LANCHOR201]
	str	x1, [x0, 24]
	adrp	x1, .LANCHOR200
	ldr	x1, [x1, #:lo12:.LANCHOR200]
	str	x1, [x0, 32]
	adrp	x1, .LANCHOR202
	ldr	x1, [x1, #:lo12:.LANCHOR202]
	str	x1, [x0, 40]
	bl	FtlMapTblRecovery
	mov	w0, 0
	ldp	x29, x30, [sp], 16
	ret
	.size	FtlLoadVonderInfo, .-FtlLoadVonderInfo
	.section	.text.FtlLoadMapInfo,"ax",@progbits
	.align	2
	.global	FtlLoadMapInfo
	.type	FtlLoadMapInfo, %function
FtlLoadMapInfo:
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
	bl	FtlL2PDataInit
	adrp	x0, .LANCHOR130
	add	x0, x0, :lo12:.LANCHOR130
	bl	FtlMapTblRecovery
	mov	w0, 0
	ldp	x29, x30, [sp], 16
	ret
	.size	FtlLoadMapInfo, .-FtlLoadMapInfo
	.section	.text.ftl_scan_all_ppa,"ax",@progbits
	.align	2
	.global	ftl_scan_all_ppa
	.type	ftl_scan_all_ppa, %function
ftl_scan_all_ppa:
	sub	sp, sp, #112
	stp	x29, x30, [sp, 16]
	add	x29, sp, 16
	stp	x21, x22, [sp, 48]
	adrp	x22, .LANCHOR51
	stp	x19, x20, [sp, 32]
	adrp	x20, .LANCHOR211
	ldrh	w19, [x22, #:lo12:.LANCHOR51]
	add	x20, x20, :lo12:.LANCHOR211
	stp	x25, x26, [sp, 80]
	adrp	x26, .LANCHOR16
	sub	w19, w19, #16
	add	x26, x26, :lo12:.LANCHOR16
	lsl	w25, w19, 10
	stp	x23, x24, [sp, 64]
	str	x27, [sp, 96]
.L2254:
	ldrh	w0, [x22, #:lo12:.LANCHOR51]
	cmp	w19, w0
	blt	.L2262
	ldp	x19, x20, [sp, 32]
	adrp	x1, .LANCHOR235
	ldp	x21, x22, [sp, 48]
	add	x1, x1, :lo12:.LANCHOR235
	ldp	x23, x24, [sp, 64]
	adrp	x0, .LC58
	ldp	x25, x26, [sp, 80]
	add	x0, x0, :lo12:.LC58
	ldp	x29, x30, [sp, 16]
	ldr	x27, [sp, 96]
	add	sp, sp, 112
	b	printf
.L2262:
	and	w24, w19, 65535
	mov	w0, w24
	bl	ftl_get_blk_mode
	ldrb	w1, [x26]
	cbz	w1, .L2255
	adrp	x1, .LANCHOR40
	ldrh	w1, [x1, #:lo12:.LANCHOR40]
	cmp	w19, w1
	bge	.L2256
	adrp	x1, .LANCHOR59
	ldrh	w1, [x1, #:lo12:.LANCHOR59]
	cmp	w19, w1
	blt	.L2256
.L2255:
	cmp	w0, 1
	bne	.L2257
.L2256:
	adrp	x0, .LANCHOR53
	mov	w21, -2147483648
	ldrh	w23, [x0, #:lo12:.LANCHOR53]
.L2258:
	mov	w3, w21
	mov	w2, w23
	mov	w1, w19
	adrp	x0, .LC55
	add	x0, x0, :lo12:.LC55
	bl	printf
	mov	w0, w24
	bl	FtlBbmIsBadBlock
	cbz	w0, .L2259
	adrp	x0, .LC56
	mov	w3, w21
	mov	w2, w23
	mov	w1, w19
	add	x0, x0, :lo12:.LC56
	bl	printf
.L2259:
	adrp	x27, .LC57
	add	w21, w21, w25
	add	x27, x27, :lo12:.LC57
	mov	w24, 0
.L2260:
	cmp	w24, w23
	bne	.L2261
	add	w19, w19, 1
	add	w25, w25, 1024
	b	.L2254
.L2257:
	adrp	x0, .LANCHOR52
	mov	w21, 0
	ldrh	w23, [x0, #:lo12:.LANCHOR52]
	b	.L2258
.L2261:
	add	w0, w21, w24
	stp	wzr, w0, [x20]
	adrp	x0, .LANCHOR189
	mov	w2, 0
	mov	w1, 1
	add	w24, w24, 1
	ldr	x0, [x0, #:lo12:.LANCHOR189]
	str	x0, [x20, 8]
	adrp	x0, .LANCHOR195
	ldr	x0, [x0, #:lo12:.LANCHOR195]
	str	x0, [x20, 16]
	mov	x0, x20
	bl	FlashReadPages
	ldp	x1, x0, [x20, 8]
	ldr	w2, [x1, 4]
	str	w2, [sp]
	ldp	w3, w4, [x0]
	ldp	w5, w6, [x0, 8]
	mov	x0, x27
	ldr	w7, [x1]
	ldp	w2, w1, [x20]
	bl	printf
	b	.L2260
	.size	ftl_scan_all_ppa, .-ftl_scan_all_ppa
	.section	.text.FlashReadFacBbtData,"ax",@progbits
	.align	2
	.global	FlashReadFacBbtData
	.type	FlashReadFacBbtData, %function
FlashReadFacBbtData:
	stp	x29, x30, [sp, -160]!
	add	x29, sp, 0
	stp	x25, x26, [sp, 64]
	mov	w25, w1
	adrp	x1, .LANCHOR15
	add	x1, x1, :lo12:.LANCHOR15
	stp	x23, x24, [sp, 48]
	mov	x23, x0
	stp	x21, x22, [sp, 32]
	adrp	x21, .LANCHOR154
	ldrh	w0, [x1, 14]
	mov	w24, w2
	ldrh	w1, [x1, 12]
	stp	x19, x20, [sp, 16]
	str	x27, [sp, 80]
	mov	w27, 61664
	mul	w0, w0, w1
	ldr	x1, [x21, #:lo12:.LANCHOR154]
	str	x1, [x29, 112]
	and	w0, w0, 65535
	adrp	x1, .LANCHOR205
	sub	w20, w0, #1
	sub	w19, w0, #15
	ldr	x2, [x1, #:lo12:.LANCHOR205]
	and	w20, w20, 65535
	mul	w26, w0, w25
	mov	x22, x1
	str	x2, [x29, 120]
.L2271:
	cmp	w19, w20
	ble	.L2278
	mov	w0, -1
.L2270:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldr	x27, [sp, 80]
	ldp	x29, x30, [sp], 160
	ret
.L2278:
	add	w0, w20, w26
	mov	w2, 1
	lsl	w0, w0, 10
	mov	w1, w2
	str	w0, [x29, 108]
	add	x0, x29, 104
	bl	FlashReadPages
	ldr	w0, [x29, 104]
	cmn	w0, #1
	beq	.L2272
	ldr	x0, [x22, #:lo12:.LANCHOR205]
	ldrh	w0, [x0]
	cmp	w0, w27
	bne	.L2272
	cbz	x23, .L2279
	cbz	w25, .L2274
.L2277:
	ldr	x1, [x21, #:lo12:.LANCHOR154]
	mov	w2, w24
	mov	x0, x23
	bl	ftl_memcpy
	mov	w3, 4
	adrp	x0, .LC59
	mov	w2, w3
	mov	x1, x23
	add	x0, x0, :lo12:.LC59
	bl	rknand_print_hex
.L2279:
	mov	w0, 0
	b	.L2270
.L2274:
	ldr	x5, [x21, #:lo12:.LANCHOR154]
	adrp	x2, .LANCHOR156
	add	x2, x2, :lo12:.LANCHOR156
	mov	w0, 0
	mov	w6, 1
.L2275:
	ldr	w1, [x2]
	cmp	w0, w1
	bcs	.L2277
	ubfx	x1, x0, 5, 11
	and	w3, w0, 31
	lsl	x1, x1, 2
	add	w0, w0, 1
	lsl	w4, w6, w3
	and	w0, w0, 65535
	ldr	w3, [x5, x1]
	orr	w3, w3, w4
	str	w3, [x5, x1]
	b	.L2275
.L2272:
	sub	w20, w20, #1
	and	w20, w20, 65535
	b	.L2271
	.size	FlashReadFacBbtData, .-FlashReadFacBbtData
	.section	.text.FlashGetBadBlockList,"ax",@progbits
	.align	2
	.global	FlashGetBadBlockList
	.type	FlashGetBadBlockList, %function
FlashGetBadBlockList:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	adrp	x0, .LANCHOR7
	ldr	x0, [x0, #:lo12:.LANCHOR7]
	ldrh	w19, [x0, 14]
	str	x21, [sp, 32]
	adrp	x21, .LANCHOR152
	ldrb	w2, [x0, 13]
	ldr	x0, [x21, #:lo12:.LANCHOR152]
	mul	w19, w19, w2
	and	w19, w19, 65535
	add	w2, w19, 7
	lsr	w2, w2, 3
	bl	FlashReadFacBbtData
	cmn	w0, #1
	bne	.L2285
.L2289:
	mov	w0, 0
.L2286:
	ubfiz	x0, x0, 1, 16
	mov	w1, -1
	ldr	x21, [sp, 32]
	strh	w1, [x20, x0]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
.L2285:
	ldr	x4, [x21, #:lo12:.LANCHOR152]
	lsr	w5, w19, 4
	sub	w19, w19, #1
	mov	w1, 0
	mov	w0, 0
	mov	w6, 1
.L2287:
	cmp	w1, w19
	bge	.L2286
	ubfx	x3, x1, 5, 11
	and	w2, w1, 31
	lsl	w2, w6, w2
	ldr	w3, [x4, x3, lsl 2]
	tst	w2, w3
	beq	.L2288
	add	w2, w0, 1
	ubfiz	x0, x0, 1, 16
	strh	w1, [x20, x0]
	and	w0, w2, 65535
.L2288:
	cmp	w0, w5
	bcs	.L2289
	add	w1, w1, 1
	and	w1, w1, 65535
	b	.L2287
	.size	FlashGetBadBlockList, .-FlashGetBadBlockList
	.section	.text.FtlMakeBbt,"ax",@progbits
	.align	2
	.global	FtlMakeBbt
	.type	FtlMakeBbt, %function
FtlMakeBbt:
	stp	x29, x30, [sp, -128]!
	adrp	x0, .LANCHOR78
	add	x29, sp, 0
	stp	x21, x22, [sp, 32]
	ldr	w21, [x0, #:lo12:.LANCHOR78]
	stp	x19, x20, [sp, 16]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	cbnz	w21, .L2296
	adrp	x20, .LANCHOR76
	add	x22, x20, :lo12:.LANCHOR76
	bl	FtlBbtMemInit
	add	x24, x22, 32
	bl	FtlLoadFactoryBbt
	adrp	x28, .LANCHOR211
	add	x22, x22, 12
	add	x25, x28, :lo12:.LANCHOR211
	adrp	x0, .LANCHOR45
	add	x0, x0, :lo12:.LANCHOR45
	str	x0, [x29, 120]
.L2297:
	ldr	x0, [x29, 120]
	ldrh	w0, [x0]
	cmp	w21, w0
	bcc	.L2303
	adrp	x21, .LANCHOR59
	add	x21, x21, :lo12:.LANCHOR59
	mov	w19, 0
.L2304:
	ldrh	w0, [x21]
	cmp	w0, w19
	bhi	.L2305
	add	x21, x20, :lo12:.LANCHOR76
	mov	w22, 65535
	ldrh	w19, [x21, 12]
	sub	w19, w19, #1
	and	w19, w19, 65535
.L2306:
	ldrh	w0, [x21, 12]
	sub	w0, w0, #47
	cmp	w0, w19
	bgt	.L2310
	mov	w0, w19
	bl	FtlBbmIsBadBlock
	cmp	w0, 1
	beq	.L2307
	mov	w0, w19
	bl	FlashTestBlk
	cbz	w0, .L2308
	mov	w0, w19
	bl	FtlBbmMapBadBlock
.L2307:
	sub	w19, w19, #1
	and	w19, w19, 65535
	b	.L2306
.L2303:
	adrp	x2, .LANCHOR195
	adrp	x0, .LANCHOR189
	add	x19, x28, :lo12:.LANCHOR211
	ldrh	w1, [x22]
	ldr	x0, [x0, #:lo12:.LANCHOR189]
	mov	w3, 65535
	ldr	x26, [x2, #:lo12:.LANCHOR195]
	cmp	w1, w3
	stp	x0, x26, [x19, 8]
	adrp	x23, .LANCHOR51
	str	x2, [x29, 112]
	beq	.L2298
	ldrh	w4, [x23, #:lo12:.LANCHOR51]
	mov	w2, 1
	madd	w27, w4, w21, w1
	mov	w1, w2
	lsl	w0, w27, 10
	str	w0, [x19, 4]
	mov	x0, x19
	bl	FlashReadPages
	ldr	x1, [x19, 8]
	ldr	x0, [x24]
	ldrh	w2, [x23, #:lo12:.LANCHOR51]
	add	w2, w2, 7
	lsr	w2, w2, 3
	bl	ftl_memcpy
.L2299:
	mov	w0, w27
	add	w21, w21, 1
	bl	FtlBbmMapBadBlock
	add	x24, x24, 8
	add	x22, x22, 2
	b	.L2297
.L2298:
	mov	w1, w21
	bl	FlashGetBadBlockList
	ldr	x0, [x19, 8]
	adrp	x27, .LANCHOR126
	ldr	x1, [x24]
	bl	FtlBbt2Bitmap
	ldrh	w19, [x23, #:lo12:.LANCHOR51]
	add	x23, x23, :lo12:.LANCHOR51
	add	x0, x27, :lo12:.LANCHOR126
	sub	w19, w19, #1
	str	x0, [x29, 104]
	and	w19, w19, 65535
.L2300:
	ldrh	w0, [x23]
	madd	w0, w21, w0, w19
	bl	FtlBbmIsBadBlock
	cmp	w0, 1
	beq	.L2301
	ldr	x0, [x29, 112]
	mov	w2, 16
	strh	w19, [x22]
	mov	w1, 0
	ldr	x0, [x0, #:lo12:.LANCHOR195]
	bl	ftl_memset
	mov	w0, -3872
	strh	w0, [x26]
	ldrh	w4, [x23]
	ldrh	w0, [x22]
	strh	w0, [x26, 2]
	ldr	x1, [x24]
	str	wzr, [x26, 4]
	madd	w27, w4, w21, w0
	lsl	w0, w27, 10
	str	w0, [x25, 4]
	ldr	x0, [x29, 104]
	ldrh	w2, [x0]
	ldr	x0, [x25, 8]
	lsl	w2, w2, 2
	bl	ftl_memcpy
	mov	w2, 1
	mov	x0, x25
	mov	w1, w2
	bl	FlashEraseBlocks
	mov	w3, 1
	mov	x0, x25
	mov	w2, w3
	mov	w1, w3
	bl	FlashProgPages
	ldr	w0, [x25]
	cmn	w0, #1
	bne	.L2299
	mov	w0, w27
	bl	FtlBbmMapBadBlock
	b	.L2300
.L2301:
	sub	w19, w19, #1
	and	w19, w19, 65535
	b	.L2300
.L2305:
	mov	w0, w19
	add	w19, w19, 1
	bl	FtlBbmMapBadBlock
	and	w19, w19, 65535
	b	.L2304
.L2308:
	ldrh	w0, [x21]
	cmp	w0, w22
	bne	.L2309
	strh	w19, [x21]
	b	.L2307
.L2309:
	strh	w19, [x21, 4]
.L2310:
	adrp	x0, .LANCHOR79
	add	x19, x20, :lo12:.LANCHOR76
	ldrh	w1, [x20, #:lo12:.LANCHOR76]
	mov	w2, 2
	ldr	x0, [x0, #:lo12:.LANCHOR79]
	str	wzr, [x19, 8]
	lsl	w1, w1, 10
	strh	wzr, [x19, 2]
	str	w1, [x0, 4]
	ldrh	w1, [x19, 4]
	lsl	w1, w1, 10
	str	w1, [x0, 60]
	mov	w1, 1
	bl	FlashEraseBlocks
	ldrh	w0, [x20, #:lo12:.LANCHOR76]
	bl	FtlBbmMapBadBlock
	ldrh	w0, [x19, 4]
	bl	FtlBbmMapBadBlock
	bl	FtlBbmTblFlush
	strh	wzr, [x19, 2]
	ldr	w0, [x19, 8]
	ldrh	w1, [x19, 4]
	add	w0, w0, 1
	str	w0, [x19, 8]
	ldrh	w0, [x20, #:lo12:.LANCHOR76]
	strh	w0, [x19, 4]
	strh	w1, [x20, #:lo12:.LANCHOR76]
	bl	FtlBbmTblFlush
.L2296:
	ldp	x19, x20, [sp, 16]
	mov	w0, 0
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 128
	ret
	.size	FtlMakeBbt, .-FtlMakeBbt
	.section	.text.log2phys,"ax",@progbits
	.align	2
	.global	log2phys
	.type	log2phys, %function
log2phys:
	stp	x29, x30, [sp, -128]!
	add	x29, sp, 0
	stp	x25, x26, [sp, 64]
	mov	w25, w0
	adrp	x0, .LANCHOR56
	stp	x23, x24, [sp, 48]
	stp	x19, x20, [sp, 16]
	mov	x26, x1
	ldrh	w24, [x0, #:lo12:.LANCHOR56]
	adrp	x0, .LANCHOR74
	stp	x21, x22, [sp, 32]
	mov	x19, x0
	ldr	w1, [x0, #:lo12:.LANCHOR74]
	stp	x27, x28, [sp, 80]
	str	w2, [x29, 116]
	cmp	w25, w1
	bcc	.L2317
	mov	w2, 1004
	adrp	x1, .LANCHOR236
	adrp	x0, .LC5
	add	x1, x1, :lo12:.LANCHOR236
	add	x0, x0, :lo12:.LC5
	bl	printf
	adrp	x1, .LC6
	adrp	x0, .LC7
	add	x1, x1, :lo12:.LC6
	add	x0, x0, :lo12:.LC7
	bl	printf
.L2317:
	ldr	w0, [x19, #:lo12:.LANCHOR74]
	cmp	w25, w0
	bcs	.L2318
	adrp	x19, .LANCHOR98
	add	w24, w24, 7
	adrp	x0, .LANCHOR67
	ldr	x2, [x19, #:lo12:.LANCHOR98]
	lsr	w23, w25, w24
	and	w22, w23, 65535
	ldrh	w1, [x0, #:lo12:.LANCHOR67]
	mov	x0, 0
.L2319:
	and	x20, x0, 65535
	cmp	w20, w1
	bcc	.L2324
	bl	select_l2p_ram_region
	and	x20, x0, 65535
	ldr	x1, [x19, #:lo12:.LANCHOR98]
	ubfiz	x21, x20, 4, 16
	add	x2, x1, x21
	ldrh	w3, [x1, x21]
	mov	w1, 65535
	cmp	w3, w1
	beq	.L2325
	ldr	w1, [x2, 4]
	tbz	w1, #31, .L2325
	bl	flush_l2p_region
.L2325:
	adrp	x0, .LANCHOR66
	str	x0, [x29, 104]
	ldrh	w1, [x0, #:lo12:.LANCHOR66]
	cmp	w1, w22
	bcs	.L2326
	mov	w2, 597
	adrp	x1, .LANCHOR237
	adrp	x0, .LC5
	add	x1, x1, :lo12:.LANCHOR237
	add	x0, x0, :lo12:.LC5
	bl	printf
	adrp	x1, .LC6
	adrp	x0, .LC7
	add	x1, x1, :lo12:.LC6
	add	x0, x0, :lo12:.LC7
	bl	printf
.L2326:
	adrp	x27, .LANCHOR134
	ubfiz	x0, x22, 2, 16
	ldr	x1, [x27, #:lo12:.LANCHOR134]
	ldr	w3, [x1, x0]
	cbnz	w3, .L2327
	ldr	x0, [x19, #:lo12:.LANCHOR98]
	adrp	x1, .LANCHOR57
	add	x0, x0, x21
	ldrh	w2, [x1, #:lo12:.LANCHOR57]
	mov	w1, 255
	ldr	x0, [x0, 8]
	bl	ftl_memset
	ldr	x0, [x19, #:lo12:.LANCHOR98]
	add	x1, x0, x21
	strh	w22, [x0, x21]
	str	wzr, [x1, 4]
	b	.L2321
.L2318:
	ldr	w1, [x29, 116]
	mov	w0, -1
	cbnz	w1, .L2316
	str	w0, [x26]
.L2316:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 128
	ret
.L2324:
	add	x0, x0, 1
	add	x3, x2, x0, lsl 4
	ldrh	w3, [x3, -16]
	cmp	w3, w22
	bne	.L2319
.L2321:
	mov	x0, 1
	lsl	x24, x0, x24
	ldr	w0, [x29, 116]
	sub	w24, w24, #1
	and	w25, w24, w25
	and	x25, x25, 65535
	cbnz	w0, .L2322
	ldr	x0, [x19, #:lo12:.LANCHOR98]
	add	x0, x0, x20, lsl 4
	ldr	x0, [x0, 8]
	ldr	w0, [x0, x25, lsl 2]
	str	w0, [x26]
.L2323:
	ldr	x0, [x19, #:lo12:.LANCHOR98]
	add	x20, x0, x20, lsl 4
	ldr	w0, [x20, 4]
	cmn	w0, #1
	beq	.L2332
	add	w0, w0, 1
	str	w0, [x20, 4]
.L2332:
	mov	w0, 0
	b	.L2316
.L2322:
	ldr	x0, [x19, #:lo12:.LANCHOR98]
	ldr	w2, [x26]
	add	x0, x0, x20, lsl 4
	ldr	x1, [x0, 8]
	str	w2, [x1, x25, lsl 2]
	ldr	w1, [x0, 4]
	orr	w1, w1, -2147483648
	str	w1, [x0, 4]
	adrp	x0, .LANCHOR99
	strh	w22, [x0, #:lo12:.LANCHOR99]
	b	.L2323
.L2327:
	ldr	x0, [x19, #:lo12:.LANCHOR98]
	adrp	x5, .LANCHOR211
	add	x28, x5, :lo12:.LANCHOR211
	mov	w2, 1
	add	x0, x0, x21
	str	x5, [x29, 96]
	str	w3, [x29, 112]
	mov	w1, w2
	str	w3, [x28, 4]
	ldr	x0, [x0, 8]
	str	x0, [x28, 8]
	adrp	x0, .LANCHOR195
	ldr	x0, [x0, #:lo12:.LANCHOR195]
	str	x0, [x28, 16]
	mov	x0, x28
	bl	FlashReadPages
	ldr	x0, [x28, 16]
	str	x0, [x29, 120]
	ldr	w3, [x29, 112]
	ldr	x5, [x29, 96]
	ldrh	w0, [x0, 8]
	cmp	w0, w22
	beq	.L2328
	mov	w2, w3
	and	w1, w23, 65535
	adrp	x0, .LC60
	add	x0, x0, :lo12:.LC60
	bl	printf
	ldr	x1, [x28, 16]
	mov	w3, 4
	adrp	x0, .LC28
	mov	w2, w3
	add	x0, x0, :lo12:.LC28
	bl	rknand_print_hex
	ldr	x0, [x29, 104]
	mov	w2, 4
	ldr	x1, [x27, #:lo12:.LANCHOR134]
	ldrh	w3, [x0, #:lo12:.LANCHOR66]
	adrp	x0, .LC61
	add	x0, x0, :lo12:.LC61
	bl	rknand_print_hex
	adrp	x0, .LANCHOR78
	mov	w1, 1
	str	w1, [x0, #:lo12:.LANCHOR78]
.L2329:
	ldr	x0, [x29, 120]
	ldrh	w0, [x0, 8]
	cmp	w0, w22
	beq	.L2330
	mov	w2, 624
	adrp	x1, .LANCHOR237
	adrp	x0, .LC5
	add	x1, x1, :lo12:.LANCHOR237
	add	x0, x0, :lo12:.LC5
	bl	printf
	adrp	x1, .LC6
	adrp	x0, .LC7
	add	x1, x1, :lo12:.LC6
	add	x0, x0, :lo12:.LC7
	bl	printf
.L2330:
	ldr	x0, [x19, #:lo12:.LANCHOR98]
	add	x1, x0, x21
	str	wzr, [x1, 4]
	strh	w22, [x0, x21]
	b	.L2321
.L2328:
	ldr	w0, [x5, #:lo12:.LANCHOR211]
	cmp	w0, 256
	bne	.L2329
	and	w23, w23, 65535
	mov	w2, w3
	mov	w1, w23
	adrp	x0, .LC62
	add	x0, x0, :lo12:.LC62
	bl	printf
	ldr	x0, [x19, #:lo12:.LANCHOR98]
	mov	w1, w23
	add	x0, x0, x21
	ldr	x2, [x0, 8]
	adrp	x0, .LANCHOR130
	add	x0, x0, :lo12:.LANCHOR130
	bl	FtlMapWritePage
	b	.L2329
	.size	log2phys, .-log2phys
	.section	.text.FtlCheckVpc,"ax",@progbits
	.align	2
	.global	FtlCheckVpc
	.type	FtlCheckVpc, %function
FtlCheckVpc:
	stp	x29, x30, [sp, -112]!
	adrp	x0, .LC48
	add	x0, x0, :lo12:.LC48
	add	x29, sp, 0
	stp	x23, x24, [sp, 48]
	adrp	x23, .LANCHOR74
	add	x23, x23, :lo12:.LANCHOR74
	stp	x21, x22, [sp, 32]
	mov	w22, 0
	stp	x19, x20, [sp, 16]
	stp	x25, x26, [sp, 64]
	adrp	x21, .LANCHOR238
	stp	x27, x28, [sp, 80]
	add	x1, x21, :lo12:.LANCHOR238
	adrp	x20, check_valid_page_count_table
	bl	printf
	add	x19, x20, :lo12:check_valid_page_count_table
	mov	x2, 8192
	mov	w1, 0
	mov	x0, x19
	bl	memset
.L2336:
	ldr	w0, [x23]
	cmp	w22, w0
	bcc	.L2338
	adrp	x23, .LANCHOR40
	adrp	x24, .LC63
	add	x23, x23, :lo12:.LANCHOR40
	add	x26, x20, :lo12:check_valid_page_count_table
	add	x24, x24, :lo12:.LC63
	mov	w22, 0
	mov	w19, 0
	adrp	x25, .LANCHOR85
.L2339:
	ldrh	w0, [x23]
	cmp	w0, w19
	bhi	.L2341
	adrp	x0, .LANCHOR89
	ldr	x19, [x0, #:lo12:.LANCHOR89]
	cbz	x19, .L2342
	adrp	x0, .LANCHOR90
	adrp	x25, .LC64
	add	x20, x20, :lo12:check_valid_page_count_table
	add	x25, x25, :lo12:.LC64
	ldrh	w26, [x0, #:lo12:.LANCHOR90]
	adrp	x0, .LANCHOR83
	mov	x24, x0
	mov	w23, 0
	ldr	x1, [x0, #:lo12:.LANCHOR83]
	adrp	x27, .LANCHOR85
	mov	w28, 6
	sub	x19, x19, x1
	mov	x1, -6148914691236517206
	asr	x19, x19, 1
	movk	x1, 0xaaab, lsl 0
	mul	x19, x19, x1
	and	w19, w19, 65535
.L2343:
	cmp	w23, w26
	bne	.L2345
.L2342:
	adrp	x0, .LC65
	mov	w1, w22
	add	x0, x0, :lo12:.LC65
	bl	printf
	cbz	w22, .L2335
	mov	w2, 1849
	add	x1, x21, :lo12:.LANCHOR238
	adrp	x0, .LC5
	add	x0, x0, :lo12:.LC5
	bl	printf
	adrp	x1, .LC6
	adrp	x0, .LC7
	add	x1, x1, :lo12:.LC6
	add	x0, x0, :lo12:.LC7
	bl	printf
.L2335:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
.L2338:
	mov	w2, 0
	add	x1, x29, 108
	mov	w0, w22
	bl	log2phys
	ldr	w0, [x29, 108]
	cmn	w0, #1
	beq	.L2337
	lsr	w0, w0, 10
	bl	P2V_block_in_plane
	and	x0, x0, 65535
	ldrh	w1, [x19, x0, lsl 1]
	add	w1, w1, 1
	strh	w1, [x19, x0, lsl 1]
.L2337:
	add	w22, w22, 1
	b	.L2336
.L2341:
	ldr	x0, [x25, #:lo12:.LANCHOR85]
	ubfiz	x28, x19, 1, 16
	sxtw	x27, w19
	ldrh	w2, [x0, x28]
	ldrh	w3, [x26, x27, lsl 1]
	cmp	w2, w3
	beq	.L2340
	mov	w1, w19
	mov	x0, x24
	bl	printf
	ldr	x0, [x25, #:lo12:.LANCHOR85]
	mov	w1, 65535
	ldrh	w0, [x0, x28]
	cmp	w0, w1
	beq	.L2340
	ldrh	w1, [x26, x27, lsl 1]
	cmp	w1, w0
	csinc	w22, w22, wzr, ls
.L2340:
	add	w19, w19, 1
	and	w19, w19, 65535
	b	.L2339
.L2345:
	ldr	x1, [x27, #:lo12:.LANCHOR85]
	ubfiz	x0, x19, 1, 16
	ldrh	w2, [x1, x0]
	cbz	w2, .L2344
	ldrh	w3, [x20, w19, sxtw 1]
	mov	w22, 1
	mov	w1, w19
	mov	x0, x25
	bl	printf
.L2344:
	ldr	x0, [x24, #:lo12:.LANCHOR83]
	umull	x19, w19, w28
	ldrh	w19, [x0, x19]
	mov	w0, 65535
	cmp	w19, w0
	beq	.L2342
	add	w23, w23, 1
	and	w23, w23, 65535
	b	.L2343
	.size	FtlCheckVpc, .-FtlCheckVpc
	.section	.text.Ftlscanalldata,"ax",@progbits
	.align	2
	.global	Ftlscanalldata
	.type	Ftlscanalldata, %function
Ftlscanalldata:
	sub	sp, sp, #96
	adrp	x0, .LC66
	mov	w1, 0
	add	x0, x0, :lo12:.LC66
	stp	x29, x30, [sp, 16]
	add	x29, sp, 16
	stp	x19, x20, [sp, 32]
	adrp	x20, .LANCHOR211
	stp	x21, x22, [sp, 48]
	mov	w19, 0
	adrp	x21, .LANCHOR74
	add	x22, x20, :lo12:.LANCHOR211
	add	x21, x21, :lo12:.LANCHOR74
	str	x23, [sp, 64]
	bl	printf
.L2361:
	ldr	w0, [x21]
	cmp	w19, w0
	bcc	.L2367
	ldp	x19, x20, [sp, 32]
	ldp	x21, x22, [sp, 48]
	ldp	x29, x30, [sp, 16]
	ldr	x23, [sp, 64]
	add	sp, sp, 96
	ret
.L2367:
	mov	w2, 0
	add	x1, x29, 76
	mov	w0, w19
	bl	log2phys
	tst	x19, 2047
	bne	.L2362
	ldr	w2, [x29, 76]
	adrp	x0, .LC67
	mov	w1, w19
	add	x0, x0, :lo12:.LC67
	bl	printf
.L2362:
	ldr	w1, [x29, 76]
	cmn	w1, #1
	beq	.L2364
	add	x0, x20, :lo12:.LANCHOR211
	str	wzr, [x20, #:lo12:.LANCHOR211]
	mov	w2, 0
	str	w1, [x0, 4]
	adrp	x1, .LANCHOR189
	str	w19, [x0, 24]
	ldr	x1, [x1, #:lo12:.LANCHOR189]
	str	x1, [x0, 8]
	adrp	x1, .LANCHOR195
	ldr	x23, [x1, #:lo12:.LANCHOR195]
	mov	w1, 1
	str	x23, [x0, 16]
	bl	FlashReadPages
	ldr	w0, [x20, #:lo12:.LANCHOR211]
	cmp	w0, 256
	ccmn	w0, #1, 4, ne
	beq	.L2365
	ldr	w0, [x23, 8]
	cmp	w19, w0
	beq	.L2364
.L2365:
	ldp	x1, x0, [x22, 8]
	ldr	w2, [x1, 4]
	str	w2, [sp]
	ldr	w2, [x22, 4]
	ldp	w3, w4, [x0]
	ldp	w5, w6, [x0, 8]
	adrp	x0, .LC68
	ldr	w7, [x1]
	add	x0, x0, :lo12:.LC68
	mov	w1, w19
	bl	printf
.L2364:
	add	w19, w19, 1
	b	.L2361
	.size	Ftlscanalldata, .-Ftlscanalldata
	.section	.text.FtlReUsePrevPpa,"ax",@progbits
	.align	2
	.global	FtlReUsePrevPpa
	.type	FtlReUsePrevPpa, %function
FtlReUsePrevPpa:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x21, x22, [sp, 32]
	adrp	x22, .LANCHOR85
	stp	x19, x20, [sp, 16]
	mov	w21, w0
	str	w1, [x29, 76]
	lsr	w0, w1, 10
	str	x23, [sp, 48]
	bl	P2V_block_in_plane
	ldr	x2, [x22, #:lo12:.LANCHOR85]
	and	w3, w0, 65535
	ubfiz	x20, x3, 1, 16
	ldrh	w1, [x2, x20]
	cbnz	w1, .L2370
	adrp	x0, .LANCHOR89
	ldr	x19, [x0, #:lo12:.LANCHOR89]
	cbz	x19, .L2371
	adrp	x2, .LANCHOR83
	mov	x5, -6148914691236517206
	movk	x5, 0xaaab, lsl 0
	adrp	x23, .LANCHOR90
	ldr	x2, [x2, #:lo12:.LANCHOR83]
	mov	w6, 65535
	ldrh	w4, [x23, #:lo12:.LANCHOR90]
	sub	x19, x19, x2
	asr	x19, x19, 1
	mul	x19, x19, x5
	mov	w5, 6
	and	w19, w19, 65535
.L2372:
	cmp	w1, w4
	beq	.L2371
	cmp	w19, w3
	bne	.L2373
	mov	w1, w19
	add	x0, x0, :lo12:.LANCHOR89
	bl	List_remove_node
	ldrh	w0, [x23, #:lo12:.LANCHOR90]
	cbnz	w0, .L2374
	mov	w2, 2271
	adrp	x1, .LANCHOR239
	adrp	x0, .LC5
	add	x1, x1, :lo12:.LANCHOR239
	add	x0, x0, :lo12:.LC5
	bl	printf
	adrp	x1, .LC6
	adrp	x0, .LC7
	add	x1, x1, :lo12:.LC6
	add	x0, x0, :lo12:.LC7
	bl	printf
.L2374:
	ldrh	w0, [x23, #:lo12:.LANCHOR90]
	sub	w0, w0, #1
	strh	w0, [x23, #:lo12:.LANCHOR90]
	mov	w0, w19
	bl	INSERT_DATA_LIST
	ldr	x1, [x22, #:lo12:.LANCHOR85]
	ldrh	w0, [x1, x20]
	add	w0, w0, 1
	strh	w0, [x1, x20]
.L2371:
	add	x1, x29, 76
	mov	w2, 1
	mov	w0, w21
	bl	log2phys
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
.L2373:
	umull	x19, w19, w5
	ldrh	w19, [x2, x19]
	cmp	w19, w6
	beq	.L2371
	add	w1, w1, 1
	and	w1, w1, 65535
	b	.L2372
.L2370:
	add	w1, w1, 1
	strh	w1, [x2, x20]
	b	.L2371
	.size	FtlReUsePrevPpa, .-FtlReUsePrevPpa
	.section	.text.FtlRecoverySuperblock,"ax",@progbits
	.align	2
	.global	FtlRecoverySuperblock
	.type	FtlRecoverySuperblock, %function
FtlRecoverySuperblock:
	stp	x29, x30, [sp, -208]!
	mov	w1, 65535
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	stp	x21, x22, [sp, 32]
	ldrh	w0, [x0]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	cmp	w0, w1
	stp	x27, x28, [sp, 80]
	beq	.L2542
	ldrb	w0, [x19, 6]
	str	w0, [x29, 180]
	adrp	x0, .LANCHOR52
	ldrh	w26, [x19, 2]
	str	x0, [x29, 144]
	ldrh	w2, [x0, #:lo12:.LANCHOR52]
	cmp	w2, w26
	bne	.L2383
	strh	wzr, [x19, 4]
.L2549:
	strb	wzr, [x19, 6]
.L2542:
	ldp	x19, x20, [sp, 16]
	mov	w0, 0
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 208
	ret
.L2383:
	ldrh	w0, [x19, 16]
	mov	w21, 0
.L2384:
	cmp	w0, w1
	beq	.L2385
	ldrb	w1, [x19, 8]
	cmp	w1, 1
	bne	.L2386
	bl	FtlGetLastWrittenPage
	mov	w20, w0
	cmn	w0, #1
	beq	.L2387
	adrp	x0, .LANCHOR16
	ldrb	w0, [x0, #:lo12:.LANCHOR16]
	cbnz	w0, .L2464
	adrp	x0, .LANCHOR17
	add	x0, x0, :lo12:.LANCHOR17
	ldrh	w23, [x0, w20, sxtw 1]
.L2388:
	adrp	x1, .LANCHOR108
	adrp	x2, .LANCHOR38
	adrp	x22, .LANCHOR186
	add	x4, x19, 16
	ldr	x6, [x1, #:lo12:.LANCHOR108]
	adrp	x1, .LANCHOR58
	ldr	x0, [x22, #:lo12:.LANCHOR186]
	mov	w27, 0
	ldrh	w7, [x1, #:lo12:.LANCHOR58]
	add	x1, x19, 16
	str	x1, [x29, 184]
	mov	w8, 65535
	ldrh	w1, [x2, #:lo12:.LANCHOR38]
	mov	w10, 56
	str	x2, [x29, 160]
	add	x1, x1, 8
	add	x1, x19, x1, lsl 1
.L2389:
	cmp	x1, x4
	bne	.L2393
	ldrb	w1, [x19, 8]
	cmp	w1, 1
	bne	.L2465
	adrp	x1, .LANCHOR16
	ldrb	w1, [x1, #:lo12:.LANCHOR16]
	cmp	w1, 0
	cset	w1, ne
	str	w1, [x29, 176]
.L2394:
	ldr	w2, [x29, 176]
	mov	w1, w27
	adrp	x24, .LC69
	adrp	x25, .LANCHOR241
	add	x24, x24, :lo12:.LC69
	add	x25, x25, :lo12:.LANCHOR241
	mov	x28, 0
	bl	FlashReadPages
	adrp	x0, .LANCHOR165
	mov	w5, 65535
	str	x0, [x29, 168]
	ldr	w21, [x0, #:lo12:.LANCHOR165]
	sub	w21, w21, #1
.L2395:
	and	w0, w28, 65535
	cmp	w27, w0
	bhi	.L2400
	bne	.L2398
	ldr	x0, [x22, #:lo12:.LANCHOR186]
	add	w20, w20, 1
	and	w20, w20, 65535
	ldr	w0, [x0, 4]
.L2544:
	lsr	w0, w0, 10
	bl	P2V_plane
	ldrb	w1, [x19, 8]
	and	w27, w0, 65535
	cmp	w1, 1
	bne	.L2402
	adrp	x0, .LANCHOR16
	ldrb	w0, [x0, #:lo12:.LANCHOR16]
	cbnz	w0, .L2402
	adrp	x0, .LANCHOR17
	add	x0, x0, :lo12:.LANCHOR17
	ldrh	w20, [x0, w20, sxtw 1]
.L2402:
	ldr	x0, [x29, 144]
	ldrh	w0, [x0, #:lo12:.LANCHOR52]
	cmp	w0, w20
	bne	.L2403
	strh	w20, [x19, 2]
	strb	wzr, [x19, 6]
	strh	wzr, [x19, 4]
.L2403:
	ldr	w0, [x29, 180]
	cmp	w20, w26
	cset	w2, eq
	cmp	w27, w0
	cset	w0, eq
	tst	w2, w0
	beq	.L2404
.L2550:
	mov	w2, w27
	mov	w1, w20
	mov	x0, x19
	bl	ftl_sb_update_avl_pages
	b	.L2542
.L2385:
	add	w21, w21, 1
	and	w21, w21, 65535
	add	x0, x19, x21, sxtw 1
	ldrh	w0, [x0, 16]
	b	.L2384
.L2386:
	mov	w1, 0
	bl	FtlGetLastWrittenPage
	mov	w20, w0
	cmn	w0, #1
	beq	.L2387
.L2464:
	mov	w23, w20
	b	.L2388
.L2387:
	cbz	w26, .L2390
	mov	w2, 2350
	adrp	x1, .LANCHOR240
	adrp	x0, .LC5
	add	x1, x1, :lo12:.LANCHOR240
	add	x0, x0, :lo12:.LC5
	bl	printf
	adrp	x1, .LC6
	adrp	x0, .LC7
	add	x1, x1, :lo12:.LC6
	add	x0, x0, :lo12:.LC7
	bl	printf
.L2390:
	ldr	w0, [x29, 180]
	cmp	w0, 0
	ccmp	w21, w0, 4, ne
	beq	.L2391
	mov	w2, 2351
	adrp	x1, .LANCHOR240
	adrp	x0, .LC5
	add	x1, x1, :lo12:.LANCHOR240
	add	x0, x0, :lo12:.LC5
	bl	printf
	adrp	x1, .LC6
	adrp	x0, .LC7
	add	x1, x1, :lo12:.LC6
	add	x0, x0, :lo12:.LC7
	bl	printf
.L2391:
	strh	wzr, [x19, 2]
	b	.L2549
.L2393:
	ldrh	w2, [x4]
	cmp	w2, w8
	beq	.L2392
	umaddl	x5, w27, w10, x0
	orr	w2, w23, w2, lsl 10
	add	w3, w27, 1
	str	w2, [x5, 4]
	mul	w2, w27, w7
	and	w27, w3, 65535
	str	xzr, [x5, 8]
	asr	w2, w2, 2
	add	x2, x6, x2, sxtw 2
	str	x2, [x5, 16]
.L2392:
	add	x4, x4, 2
	b	.L2389
.L2465:
	str	wzr, [x29, 176]
	b	.L2394
.L2400:
	mov	x0, 56
	ldr	x2, [x22, #:lo12:.LANCHOR186]
	mul	x0, x28, x0
	add	x1, x2, x0
	ldr	w0, [x2, x0]
	cbnz	w0, .L2396
	ldr	x6, [x1, 16]
	ldr	w4, [x6, 4]
	cmn	w4, #1
	beq	.L2397
	ldr	x0, [x29, 168]
	ldr	w1, [x0, #:lo12:.LANCHOR165]
	mov	w0, w4
	bl	ftl_cmp_data_ver
	cbz	w0, .L2397
	ldr	x0, [x29, 168]
	add	w4, w4, 1
	str	w4, [x0, #:lo12:.LANCHOR165]
.L2397:
	ldr	w0, [x6]
	cmn	w0, #1
	bne	.L2399
.L2398:
	ldr	x0, [x22, #:lo12:.LANCHOR186]
	and	x28, x28, 65535
	mov	x1, 56
	and	w20, w20, 65535
	madd	x28, x28, x1, x0
	ldr	w0, [x28, 4]
	b	.L2544
.L2396:
	ldr	w1, [x1, 4]
	mov	x0, x24
	bl	printf
	ldrh	w0, [x19]
	and	w5, w23, 65535
	strh	w0, [x25]
.L2399:
	add	x28, x28, 1
	b	.L2395
.L2404:
	mov	w0, 65535
	cmp	w5, w0
	bne	.L2405
	cbnz	w1, .L2406
.L2405:
	adrp	x24, .LANCHOR139
	and	w6, w23, 65535
	ldr	w0, [x24, #:lo12:.LANCHOR139]
	cmn	w0, #1
	bne	.L2407
	str	w21, [x24, #:lo12:.LANCHOR139]
.L2407:
	add	w0, w26, 7
	ldr	w7, [x24, #:lo12:.LANCHOR139]
	cmp	w0, w23, uxth
	bge	.L2466
	sub	w23, w6, #7
	and	w23, w23, 65535
.L2408:
	mov	w3, -1
	adrp	x5, .LANCHOR123
	mov	w28, w3
	add	x5, x5, :lo12:.LANCHOR123
	mov	w4, 65535
.L2409:
	cmp	w23, w6
	bhi	.L2424
	ldr	x1, [x29, 160]
	mov	w25, 0
	ldr	x0, [x22, #:lo12:.LANCHOR186]
	mov	w10, 56
	ldr	x2, [x29, 184]
	ldrh	w1, [x1, #:lo12:.LANCHOR38]
	add	x1, x1, 8
	add	x1, x19, x1, lsl 1
	b	.L2425
.L2466:
	mov	w23, w26
	b	.L2408
.L2411:
	ldrh	w8, [x2]
	cmp	w8, w4
	beq	.L2410
	umaddl	x11, w25, w10, x0
	add	w25, w25, 1
	and	w25, w25, 65535
	orr	w8, w23, w8, lsl 10
	str	w8, [x11, 4]
.L2410:
	add	x2, x2, 2
.L2425:
	cmp	x2, x1
	bne	.L2411
	ldr	w2, [x29, 176]
	mov	w1, w25
	str	x5, [x29, 112]
	str	w4, [x29, 120]
	str	w7, [x29, 128]
	str	w6, [x29, 136]
	str	w3, [x29, 152]
	bl	FlashReadPages
	adrp	x1, .LANCHOR16
	mov	w2, 56
	ldr	w0, [x24, #:lo12:.LANCHOR139]
	sxtw	x12, w23
	ldrb	w10, [x1, #:lo12:.LANCHOR16]
	mov	w11, 1
	ldr	x1, [x22, #:lo12:.LANCHOR186]
	ldr	w4, [x29, 120]
	ldr	w7, [x29, 128]
	ldr	w6, [x29, 136]
	ldr	w3, [x29, 152]
	nop // between mem op and mult-accumulate
	umaddl	x25, w25, w2, x1
	ldr	x5, [x29, 112]
	mov	w2, 0
.L2412:
	cmp	x25, x1
	bne	.L2422
	cbz	w2, .L2423
	str	w0, [x24, #:lo12:.LANCHOR139]
.L2423:
	add	w23, w23, 1
	and	w23, w23, 65535
	b	.L2409
.L2422:
	ldr	w8, [x1]
	cbnz	w8, .L2413
	ldr	x8, [x1, 16]
	ldrh	w13, [x8]
	cmp	w13, w4
	beq	.L2468
	ldr	w8, [x8, 4]
	cmn	w8, #1
	beq	.L2468
	cmn	w3, #1
	bne	.L2470
	ldrh	w2, [x5, x12, lsl 1]
	cmp	w2, w4
	bne	.L2415
	cbz	w10, .L2470
.L2415:
	cmp	w21, w0
	mov	w2, w11
	csel	w3, w3, w0, eq
.L2414:
	mov	w28, w0
	add	x1, x1, 56
	mov	w0, w8
	b	.L2412
.L2413:
	cbz	w2, .L2416
	str	w0, [x24, #:lo12:.LANCHOR139]
.L2416:
	adrp	x0, .LANCHOR241
	ldrh	w1, [x19]
	strh	w1, [x0, #:lo12:.LANCHOR241]
	ldrb	w0, [x19, 8]
	cbnz	w0, .L2406
	adrp	x0, .LANCHOR123
	add	x0, x0, :lo12:.LANCHOR123
	ldrh	w1, [x0, w23, sxtw 1]
	mov	w0, 65535
	cmp	w1, w0
	bne	.L2418
	cmn	w3, #1
	beq	.L2419
	str	w3, [x24, #:lo12:.LANCHOR139]
.L2406:
	adrp	x0, .LANCHOR242
	mov	w23, w26
	mov	w1, 1
	adrp	x28, .LANCHOR139
	strh	w1, [x0, #:lo12:.LANCHOR242]
	add	x0, x28, :lo12:.LANCHOR139
	str	x0, [x29, 112]
.L2426:
	ldr	x2, [x29, 160]
	adrp	x1, .LANCHOR16
	ldr	x0, [x22, #:lo12:.LANCHOR186]
	mov	w24, 0
	ldrb	w5, [x1, #:lo12:.LANCHOR16]
	mov	w6, 65535
	ldr	x3, [x29, 184]
	ldrh	w2, [x2, #:lo12:.LANCHOR38]
	str	x1, [x29, 128]
	add	x2, x2, 8
	add	x2, x19, x2, lsl 1
.L2427:
	cmp	x2, x3
	bne	.L2430
	ldr	w2, [x29, 176]
	mov	w1, w24
	mov	x25, 0
	bl	FlashReadPages
	mov	w0, 56
	umull	x0, w24, w0
	str	x0, [x29, 136]
	adrp	x0, .LANCHOR241
	add	x0, x0, :lo12:.LANCHOR241
	str	x0, [x29, 120]
.L2431:
	ldr	x0, [x29, 136]
	cmp	x25, x0
	bne	.L2457
	ldrb	w0, [x19, 8]
	add	w23, w23, 1
	and	w23, w23, 65535
	cmp	w0, 1
	bne	.L2458
	ldr	x0, [x29, 128]
	ldrb	w0, [x0, #:lo12:.LANCHOR16]
	cbz	w0, .L2458
	adrp	x0, .LANCHOR53
	ldrh	w0, [x0, #:lo12:.LANCHOR53]
	cmp	w0, w23
	bne	.L2458
	cmp	w20, w23
	beq	.L2433
.L2458:
	ldr	x0, [x29, 144]
	ldrh	w0, [x0, #:lo12:.LANCHOR52]
	cmp	w0, w23
	bne	.L2426
	ldr	x0, [x29, 160]
	mov	w2, 65535
	strh	w23, [x19, 2]
	strh	wzr, [x19, 4]
	ldrh	w1, [x0, #:lo12:.LANCHOR38]
	mov	w0, 0
.L2459:
	cmp	w0, w1
	beq	.L2542
	ldr	x4, [x29, 184]
	ldrh	w3, [x4], 2
	str	x4, [x29, 184]
	cmp	w3, w2
	beq	.L2460
	strb	w0, [x19, 6]
	b	.L2542
.L2419:
	cmp	w21, w7
	beq	.L2420
	str	w7, [x24, #:lo12:.LANCHOR139]
	b	.L2406
.L2420:
	ldr	w0, [x24, #:lo12:.LANCHOR139]
.L2551:
	sub	w0, w0, #1
.L2545:
	str	w0, [x24, #:lo12:.LANCHOR139]
	b	.L2406
.L2418:
	cmp	w28, w21
	beq	.L2421
	cmn	w28, #1
	beq	.L2406
	str	w28, [x24, #:lo12:.LANCHOR139]
	b	.L2406
.L2421:
	ldr	w0, [x24, #:lo12:.LANCHOR139]
	cmp	w21, w0
	bne	.L2551
	b	.L2406
.L2468:
	mov	w8, w0
	mov	w0, w28
	b	.L2414
.L2470:
	mov	w2, 1
	b	.L2414
.L2424:
	mov	w0, -1
	b	.L2545
.L2430:
	ldrh	w1, [x3]
	cmp	w1, w6
	beq	.L2428
	mov	w4, 56
	orr	w1, w23, w1, lsl 10
	umaddl	x4, w24, w4, x0
	str	w1, [x4, 4]
	ldrb	w7, [x19, 8]
	cmp	w7, 1
	bne	.L2429
	cbz	w5, .L2429
	orr	w1, w1, -2147483648
	str	w1, [x4, 4]
.L2429:
	add	w24, w24, 1
	and	w24, w24, 65535
.L2428:
	add	x3, x3, 2
	b	.L2427
.L2457:
	ldr	x4, [x22, #:lo12:.LANCHOR186]
	add	x4, x4, x25
	ldr	w5, [x4, 4]
	str	w5, [x29, 204]
	lsr	w0, w5, 10
	bl	P2V_plane
	and	w0, w0, 65535
	cmp	w23, w26
	bcc	.L2432
	ldr	w1, [x29, 180]
	ccmp	w1, w0, 0, eq
	bhi	.L2432
	cmp	w23, w20
	ccmp	w27, w0, 0, eq
	beq	.L2433
	ldr	w0, [x4]
	cmn	w0, #1
	beq	.L2434
	ldr	x3, [x4, 16]
	mov	w0, 61589
	ldrh	w1, [x3]
	cmp	w1, w0
	beq	.L2435
	ldrh	w0, [x19]
.L2547:
	bl	decrement_vpc_count
	b	.L2432
.L2435:
	ldr	w21, [x3, 4]
	cmn	w21, #1
	beq	.L2436
	ldr	x0, [x29, 168]
	ldr	w1, [x0, #:lo12:.LANCHOR165]
	mov	w0, w21
	bl	ftl_cmp_data_ver
	cbz	w0, .L2436
	ldr	x1, [x29, 168]
	add	w0, w21, 1
	str	w0, [x1, #:lo12:.LANCHOR165]
.L2436:
	ldp	w24, w0, [x3, 8]
	add	x1, x29, 200
	str	w0, [x29, 196]
	mov	w2, 0
	mov	w0, w24
	bl	log2phys
	ldr	w1, [x28, #:lo12:.LANCHOR139]
	ldr	w3, [x29, 196]
	cmn	w1, #1
	beq	.L2437
	mov	w0, w21
	bl	ftl_cmp_data_ver
	cbz	w0, .L2437
	cmn	w3, #1
	beq	.L2438
	ldr	x0, [x22, #:lo12:.LANCHOR186]
	mov	w2, 0
	mov	w1, 1
	add	x0, x0, x25
	ldr	x4, [x0, 16]
	str	w3, [x0, 4]
	str	x4, [x29, 152]
	bl	FlashReadPages
	ldr	x0, [x22, #:lo12:.LANCHOR186]
	ldr	x4, [x29, 152]
	add	x3, x0, x25
	ldr	w0, [x0, x25]
	cmn	w0, #1
	bne	.L2439
.L2440:
	mov	w0, -1
	str	w0, [x29, 196]
.L2447:
	ldr	w3, [x29, 196]
	cmn	w3, #1
	beq	.L2432
.L2463:
	lsr	w0, w3, 10
	bl	P2V_block_in_plane
	and	w24, w0, 65535
	adrp	x0, .LANCHOR40
	mov	w3, w24
	ldrh	w0, [x0, #:lo12:.LANCHOR40]
	cmp	w0, w24
	bhi	.L2453
	mov	w2, 2683
	adrp	x1, .LANCHOR240
	adrp	x0, .LC5
	add	x1, x1, :lo12:.LANCHOR240
	add	x0, x0, :lo12:.LC5
	str	w24, [x29, 152]
	bl	printf
	adrp	x1, .LC6
	adrp	x0, .LC7
	add	x1, x1, :lo12:.LC6
	add	x0, x0, :lo12:.LC7
	bl	printf
	ldr	w3, [x29, 152]
.L2453:
	adrp	x1, .LANCHOR85
	ubfiz	x0, x24, 1, 16
	ldr	x1, [x1, #:lo12:.LANCHOR85]
	ldrh	w0, [x1, x0]
	cbz	w0, .L2454
	mov	w0, w3
	b	.L2547
.L2438:
	ldp	w1, w0, [x29, 200]
	cmp	w1, w0
	bne	.L2432
	mov	w2, 1
	add	x1, x29, 196
	mov	w0, w24
	bl	log2phys
.L2432:
	add	x25, x25, 56
	b	.L2431
.L2439:
	ldr	w0, [x4, 8]
	cmp	w24, w0
	bne	.L2440
	ldr	w0, [x4, 4]
	str	w0, [x29, 152]
	str	x4, [x29, 104]
	uxtw	x1, w0
	ldr	w0, [x28, #:lo12:.LANCHOR139]
	bl	ftl_cmp_data_ver
	cbz	w0, .L2440
	ldp	w0, w1, [x29, 200]
	ldr	x4, [x29, 104]
	cmp	w0, w1
	ldr	w1, [x29, 196]
	bne	.L2442
.L2546:
	mov	w0, w24
	bl	FtlReUsePrevPpa
	b	.L2440
.L2442:
	cmp	w0, w1
	beq	.L2440
	cmn	w0, #1
	beq	.L2443
	ldr	x4, [x3, 16]
	mov	w2, 0
	str	w0, [x3, 4]
	mov	w1, 1
	str	x4, [x29, 104]
	mov	x0, x3
	bl	FlashReadPages
	ldr	x4, [x29, 104]
.L2444:
	ldr	x0, [x22, #:lo12:.LANCHOR186]
	ldr	w0, [x0, x25]
	cmn	w0, #1
	beq	.L2445
	ldr	x0, [x29, 112]
	ldr	w3, [x4, 4]
	mov	w1, w3
	ldr	w0, [x0]
	bl	ftl_cmp_data_ver
	cbz	w0, .L2445
	ldr	w0, [x29, 152]
	mov	w1, w3
	bl	ftl_cmp_data_ver
	cbz	w0, .L2440
.L2445:
	ldr	w1, [x29, 196]
	b	.L2546
.L2443:
	str	w0, [x3]
	b	.L2444
.L2437:
	ldp	w1, w0, [x29, 200]
	cmp	w1, w0
	beq	.L2447
	cmn	w3, #1
	beq	.L2449
	adrp	x0, .LANCHOR43
	ubfx	x3, x3, 10, 21
	ldr	w0, [x0, #:lo12:.LANCHOR43]
	cmp	w3, w0
	bcs	.L2432
.L2449:
	mov	w2, 1
	add	x1, x29, 204
	mov	w0, w24
	bl	log2phys
	ldr	w3, [x29, 200]
	cmn	w3, #1
	beq	.L2447
	ldr	w0, [x29, 196]
	cmp	w3, w0
	beq	.L2463
	lsr	w0, w3, 10
	bl	P2V_block_in_plane
	adrp	x1, .LANCHOR93
	and	w0, w0, 65535
	ldrh	w1, [x1, #:lo12:.LANCHOR93]
	cmp	w1, w0
	beq	.L2452
	adrp	x1, .LANCHOR94
	ldrh	w1, [x1, #:lo12:.LANCHOR94]
	cmp	w1, w0
	beq	.L2452
	adrp	x1, .LANCHOR95
	ldrh	w1, [x1, #:lo12:.LANCHOR95]
	cmp	w1, w0
	bne	.L2447
.L2452:
	ldr	x0, [x22, #:lo12:.LANCHOR186]
	mov	w2, 0
	mov	w1, 1
	ldr	x4, [x0, 16]
	str	w3, [x0, 4]
	str	x4, [x29, 152]
	bl	FlashReadPages
	ldr	x0, [x22, #:lo12:.LANCHOR186]
	ldr	w0, [x0]
	cmn	w0, #1
	beq	.L2447
	ldr	x4, [x29, 152]
	mov	w0, w21
	ldr	w1, [x4, 4]
	bl	ftl_cmp_data_ver
	cbnz	w0, .L2447
	mov	w2, 1
	add	x1, x29, 200
	mov	w0, w24
	bl	log2phys
	b	.L2447
.L2454:
	mov	w1, w24
	adrp	x0, .LC70
	add	x0, x0, :lo12:.LC70
	bl	printf
	b	.L2432
.L2434:
	ldr	x1, [x29, 120]
	mov	w2, w21
	ldrh	w0, [x19]
	strh	w0, [x1]
	mov	w1, w5
	adrp	x0, .LC71
	add	x0, x0, :lo12:.LC71
	bl	printf
	adrp	x2, .LANCHOR243
	ldr	w0, [x2, #:lo12:.LANCHOR243]
	cmp	w0, 31
	bhi	.L2455
	adrp	x1, .LANCHOR244
	add	x1, x1, :lo12:.LANCHOR244
	ldr	w3, [x29, 204]
	str	w3, [x1, w0, uxtw 2]
	add	w0, w0, 1
	str	w0, [x2, #:lo12:.LANCHOR243]
.L2455:
	ldrh	w0, [x19]
	bl	decrement_vpc_count
	ldr	w0, [x28, #:lo12:.LANCHOR139]
	cmn	w0, #1
	bne	.L2456
.L2548:
	str	w21, [x28, #:lo12:.LANCHOR139]
	b	.L2432
.L2456:
	cmp	w21, w0
	bcs	.L2432
	b	.L2548
.L2460:
	add	w0, w0, 1
	and	w0, w0, 65535
	b	.L2459
.L2433:
	strb	w27, [x19, 6]
	strh	w20, [x19, 2]
	b	.L2550
	.size	FtlRecoverySuperblock, .-FtlRecoverySuperblock
	.section	.text.FtlGcScanTempBlk,"ax",@progbits
	.align	2
	.global	FtlGcScanTempBlk
	.type	FtlGcScanTempBlk, %function
FtlGcScanTempBlk:
	stp	x29, x30, [sp, -176]!
	mov	w2, 65535
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	adrp	x0, .LANCHOR245
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	ldrh	w20, [x0, #:lo12:.LANCHOR245]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	cmp	w20, w2
	str	x0, [x29, 96]
	beq	.L2580
	cbnz	w20, .L2553
.L2554:
	bl	FtlGcPageVarInit
	b	.L2555
.L2580:
	mov	w20, 0
.L2553:
	adrp	x0, .LANCHOR52
	ldrh	w0, [x0, #:lo12:.LANCHOR52]
	cmp	w0, w1
	beq	.L2554
.L2555:
	adrp	x24, .LANCHOR74
	add	x24, x24, :lo12:.LANCHOR74
	mov	w27, -1
.L2556:
	ldrh	w1, [x19]
	mov	w0, 65535
	strb	wzr, [x19, 8]
	cmp	w1, w0
	beq	.L2581
	mov	w28, 56
.L2579:
	adrp	x1, .LANCHOR107
	adrp	x23, .LANCHOR186
	add	x3, x19, 16
	mov	w21, 0
	ldr	x5, [x1, #:lo12:.LANCHOR107]
	adrp	x1, .LANCHOR57
	ldr	x0, [x23, #:lo12:.LANCHOR186]
	mov	w10, 65535
	ldrh	w6, [x1, #:lo12:.LANCHOR57]
	adrp	x1, .LANCHOR108
	ldr	x7, [x1, #:lo12:.LANCHOR108]
	adrp	x1, .LANCHOR58
	ldrh	w8, [x1, #:lo12:.LANCHOR58]
	adrp	x1, .LANCHOR38
	ldrh	w1, [x1, #:lo12:.LANCHOR38]
	add	x1, x1, 8
	add	x1, x19, x1, lsl 1
.L2558:
	cmp	x3, x1
	bne	.L2560
	mov	w2, 0
	mov	w1, w21
	bl	FlashReadPages
	adrp	x25, .LANCHOR2
	umull	x0, w21, w28
	add	x25, x25, :lo12:.LANCHOR2
	mov	x22, 0
	str	x0, [x29, 104]
.L2561:
	ldr	x0, [x29, 104]
	cmp	x22, x0
	bne	.L2578
	adrp	x0, .LANCHOR52
	add	w20, w20, 1
	and	w20, w20, 65535
	ldrh	w0, [x0, #:lo12:.LANCHOR52]
	cmp	w0, w20
	bhi	.L2579
.L2581:
	mov	w2, 0
	b	.L2557
.L2560:
	ldrh	w2, [x3]
	cmp	w2, w10
	beq	.L2559
	umaddl	x4, w21, w28, x0
	orr	w2, w20, w2, lsl 10
	str	w2, [x4, 4]
	mul	w2, w21, w6
	asr	w2, w2, 2
	add	x2, x5, x2, sxtw 2
	str	x2, [x4, 8]
	mul	w2, w21, w8
	add	w21, w21, 1
	and	w21, w21, 65535
	asr	w2, w2, 2
	add	x2, x7, x2, sxtw 2
	str	x2, [x4, 16]
.L2559:
	add	x3, x3, 2
	b	.L2558
.L2578:
	ldr	x4, [x23, #:lo12:.LANCHOR186]
	add	x5, x4, x22
	ldr	w26, [x5, 4]
	lsr	w0, w26, 10
	bl	P2V_plane
	and	w2, w0, 65535
	ldr	w0, [x4, x22]
	ldr	x21, [x5, 16]
	cbnz	w0, .L2562
	ldrh	w1, [x21]
	mov	w0, 65535
	cmp	w1, w0
	bne	.L2563
.L2566:
	adrp	x0, .LANCHOR16
	ldrb	w0, [x0, #:lo12:.LANCHOR16]
	cbz	w0, .L2597
	adrp	x0, .LANCHOR138
	mov	w1, 1
	str	w1, [x0, #:lo12:.LANCHOR138]
.L2557:
	ldr	x1, [x29, 96]
	mov	w0, -1
	strb	w2, [x19, 6]
	strh	w20, [x19, 2]
	strh	w0, [x1, #:lo12:.LANCHOR245]
	mov	w1, w20
	mov	x0, x19
	bl	ftl_sb_update_avl_pages
	mov	w0, w27
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 176
	ret
.L2563:
	ldr	w0, [x21, 8]
	ldr	w1, [x24]
	cmp	w0, w1
	bhi	.L2566
	ldrb	w1, [x25]
	cbnz	w1, .L2569
.L2570:
	ldp	w2, w0, [x21, 8]
	mov	w1, w26
	add	x22, x22, 56
	bl	FtlGcUpdatePage
	b	.L2561
.L2569:
	add	x1, x29, 116
	mov	w2, 0
	bl	log2phys
	ldr	w0, [x21, 12]
	ldr	w1, [x29, 116]
	cmp	w0, w1
	bne	.L2570
	cmn	w0, #1
	beq	.L2570
	str	w0, [x29, 124]
	adrp	x0, .LANCHOR194
	mov	w2, 0
	mov	w1, 1
	ldr	x0, [x0, #:lo12:.LANCHOR194]
	str	x0, [x29, 128]
	adrp	x0, .LANCHOR196
	ldr	x0, [x0, #:lo12:.LANCHOR196]
	str	x0, [x29, 136]
	add	x0, x29, 120
	bl	FlashReadPages
	adrp	x0, .LANCHOR55
	ldr	x2, [x23, #:lo12:.LANCHOR186]
	ldr	x4, [x29, 128]
	ldrh	w1, [x0, #:lo12:.LANCHOR55]
	add	x2, x2, x22
	mov	x0, 0
	ubfiz	x1, x1, 9, 16
.L2571:
	cmp	x0, x1
	beq	.L2570
	ldr	x5, [x2, 8]
	ldr	w6, [x5, x0]
	add	x0, x0, 4
	add	x5, x4, x0
	ldr	w5, [x5, -4]
	cmp	w6, w5
	beq	.L2571
	ldrh	w1, [x19]
	adrp	x0, .LC72
	ldr	w2, [x29, 124]
	add	x0, x0, :lo12:.LC72
	bl	printf
.L2597:
	adrp	x0, .LANCHOR85
	ldrh	w1, [x19]
	ldr	x0, [x0, #:lo12:.LANCHOR85]
	strh	wzr, [x0, x1, lsl 1]
	ldrh	w0, [x19]
	bl	INSERT_FREE_LIST
	adrp	x1, .LANCHOR213
	mov	w0, -1
	strh	w0, [x19]
	strh	w0, [x1, #:lo12:.LANCHOR213]
.L2596:
	bl	FtlGcPageVarInit
	mov	w20, 0
	b	.L2556
.L2562:
	ldrh	w1, [x19]
	mov	w2, w26
	adrp	x0, .LC73
	add	x0, x0, :lo12:.LC73
	bl	printf
	adrp	x0, .LANCHOR104
	ldr	w1, [x0, #:lo12:.LANCHOR104]
	ldrh	w0, [x19]
	cbnz	w1, .L2574
	adrp	x1, .LANCHOR16
	ldrb	w1, [x1, #:lo12:.LANCHOR16]
	cbz	w1, .L2575
.L2574:
	adrp	x2, .LANCHOR80
	ubfiz	x1, x0, 1, 16
	ldr	x2, [x2, #:lo12:.LANCHOR80]
	ldrh	w1, [x2, x1]
	cmp	w1, 159
	bls	.L2576
.L2575:
	ldr	x1, [x23, #:lo12:.LANCHOR186]
	ldr	w1, [x1, x22]
	cmn	w1, #1
	bne	.L2577
.L2576:
	ldr	x1, [x23, #:lo12:.LANCHOR186]
	add	x22, x1, x22
	ldr	w27, [x22, 4]
.L2577:
	adrp	x1, .LANCHOR85
	ubfiz	x0, x0, 1, 16
	ldr	x1, [x1, #:lo12:.LANCHOR85]
	strh	wzr, [x1, x0]
	ldrh	w0, [x19]
	bl	INSERT_FREE_LIST
	mov	w0, -1
	strh	w0, [x19]
	b	.L2596
	.size	FtlGcScanTempBlk, .-FtlGcScanTempBlk
	.section	.text.FtlGcFreeTempBlock,"ax",@progbits
	.align	2
	.global	FtlGcFreeTempBlock
	.type	FtlGcFreeTempBlock, %function
FtlGcFreeTempBlock:
	adrp	x0, .LANCHOR78
	ldr	w0, [x0, #:lo12:.LANCHOR78]
	cbz	w0, .L2599
	mov	w0, 0
	ret
.L2599:
	stp	x29, x30, [sp, -112]!
	mov	w1, 65535
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	adrp	x19, .LANCHOR95
	stp	x21, x22, [sp, 32]
	add	x0, x19, :lo12:.LANCHOR95
	ldrh	w20, [x19, #:lo12:.LANCHOR95]
	adrp	x21, .LANCHOR138
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	cmp	w20, w1
	stp	x27, x28, [sp, 80]
	beq	.L2601
	adrp	x1, .LANCHOR52
	ldrh	w1, [x1, #:lo12:.LANCHOR52]
	bl	FtlGcScanTempBlk
	str	w0, [x29, 108]
	cmn	w0, #1
	beq	.L2601
	adrp	x0, .LANCHOR80
	ubfiz	x20, x20, 1, 16
	ldr	x1, [x0, #:lo12:.LANCHOR80]
	ldrh	w0, [x1, x20]
	cmp	w0, 4
	bls	.L2602
	sub	w0, w0, #5
	strh	w0, [x1, x20]
	mov	w0, 1
	bl	FtlEctTblFlush
.L2602:
	ldr	w0, [x21, #:lo12:.LANCHOR138]
	cbnz	w0, .L2603
	adrp	x0, .LANCHOR141
	add	x0, x0, :lo12:.LANCHOR141
	ldr	w1, [x0, 96]
	add	w1, w1, 1
	str	w1, [x0, 96]
	ldr	w0, [x29, 108]
	lsr	w0, w0, 10
	bl	FtlBbmMapBadBlock
	bl	FtlBbmTblFlush
.L2603:
	str	wzr, [x21, #:lo12:.LANCHOR138]
	mov	w0, 1
.L2598:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
.L2601:
	str	wzr, [x21, #:lo12:.LANCHOR138]
	mov	w0, 65535
	ldrh	w1, [x19, #:lo12:.LANCHOR95]
	add	x21, x19, :lo12:.LANCHOR95
	cmp	w1, w0
	beq	.L2625
	bl	FtlCacheWriteBack
	adrp	x20, .LANCHOR113
	adrp	x0, .LANCHOR52
	ldrb	w1, [x21, 7]
	ldrh	w2, [x20, #:lo12:.LANCHOR113]
	mov	x21, x0
	ldrh	w3, [x0, #:lo12:.LANCHOR52]
	mul	w1, w1, w3
	cmp	w2, w1
	beq	.L2605
	mov	w2, 193
	adrp	x1, .LANCHOR246
	adrp	x0, .LC5
	add	x1, x1, :lo12:.LANCHOR246
	add	x0, x0, :lo12:.LC5
	bl	printf
	adrp	x1, .LC6
	adrp	x0, .LC7
	add	x1, x1, :lo12:.LC6
	add	x0, x0, :lo12:.LC7
	bl	printf
.L2605:
	add	x0, x19, :lo12:.LANCHOR95
	adrp	x22, .LANCHOR85
	ldrh	w3, [x21, #:lo12:.LANCHOR52]
	adrp	x25, .LANCHOR74
	ldrh	w2, [x19, #:lo12:.LANCHOR95]
	add	x26, x20, :lo12:.LANCHOR113
	ldrb	w0, [x0, 7]
	add	x25, x25, :lo12:.LANCHOR74
	ldr	x1, [x22, #:lo12:.LANCHOR85]
	mov	w21, 0
	adrp	x27, .LANCHOR114
	mul	w0, w0, w3
	strh	w0, [x1, x2, lsl 1]
	adrp	x1, .LANCHOR166
	ldrh	w0, [x20, #:lo12:.LANCHOR113]
	ldr	w2, [x1, #:lo12:.LANCHOR166]
	add	w0, w0, w2
	str	w0, [x1, #:lo12:.LANCHOR166]
.L2606:
	ldrh	w0, [x26]
	cmp	w0, w21
	bhi	.L2610
	mov	w0, -1
	bl	decrement_vpc_count
	adrp	x0, .LANCHOR16
	ldrb	w0, [x0, #:lo12:.LANCHOR16]
	cbz	w0, .L2611
	ldrh	w1, [x19, #:lo12:.LANCHOR95]
	adrp	x0, .LC74
	add	x0, x0, :lo12:.LC74
	bl	printf
.L2611:
	ldrh	w0, [x19, #:lo12:.LANCHOR95]
	ldr	x2, [x22, #:lo12:.LANCHOR85]
	ubfiz	x1, x0, 1, 16
	ldrh	w1, [x2, x1]
	cbz	w1, .L2612
	bl	INSERT_DATA_LIST
.L2613:
	adrp	x0, .LANCHOR111
	mov	w21, -1
	strh	wzr, [x20, #:lo12:.LANCHOR113]
	strh	w21, [x19, #:lo12:.LANCHOR95]
	strh	wzr, [x0, #:lo12:.LANCHOR111]
	bl	l2p_flush
	bl	FtlVpcTblFlush
	adrp	x0, .LANCHOR213
	strh	w21, [x0, #:lo12:.LANCHOR213]
	adrp	x0, .LANCHOR90
	ldrh	w1, [x0, #:lo12:.LANCHOR90]
	adrp	x0, .LANCHOR232
	ldrh	w0, [x0, #:lo12:.LANCHOR232]
	add	w0, w0, w0, lsl 1
	cmp	w1, w0, lsr 2
	ble	.L2625
	adrp	x0, .LANCHOR181
	mov	w1, 20
	strh	w1, [x0, #:lo12:.LANCHOR181]
.L2625:
	mov	w0, 0
	b	.L2598
.L2610:
	mov	w24, 12
	ldr	x28, [x27, #:lo12:.LANCHOR114]
	ldr	w1, [x25]
	umull	x24, w21, w24
	add	x23, x28, x24
	ldr	w0, [x23, 8]
	cmp	w0, w1
	bcc	.L2607
.L2623:
	ldrh	w0, [x19, #:lo12:.LANCHOR95]
	b	.L2624
.L2607:
	add	x1, x29, 108
	mov	w2, 0
	bl	log2phys
	ldr	w0, [x28, x24]
	ldr	w1, [x29, 108]
	cmp	w0, w1
	bne	.L2609
	lsr	w0, w0, 10
	bl	P2V_block_in_plane
	mov	w24, w0
	ldr	w0, [x23, 8]
	mov	w2, 1
	add	x1, x23, 4
	bl	log2phys
	mov	w0, w24
.L2624:
	bl	decrement_vpc_count
	b	.L2608
.L2609:
	ldr	w0, [x23, 4]
	cmp	w1, w0
	bne	.L2623
.L2608:
	add	w21, w21, 1
	and	w21, w21, 65535
	b	.L2606
.L2612:
	bl	INSERT_FREE_LIST
	b	.L2613
	.size	FtlGcFreeTempBlock, .-FtlGcFreeTempBlock
	.section	.text.FtlGcPageRecovery,"ax",@progbits
	.align	2
	.global	FtlGcPageRecovery
	.type	FtlGcPageRecovery, %function
FtlGcPageRecovery:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	adrp	x20, .LANCHOR52
	adrp	x19, .LANCHOR95
	add	x19, x19, :lo12:.LANCHOR95
	ldrh	w1, [x20, #:lo12:.LANCHOR52]
	mov	x0, x19
	bl	FtlGcScanTempBlk
	ldrh	w1, [x19, 2]
	ldrh	w0, [x20, #:lo12:.LANCHOR52]
	cmp	w1, w0
	bcc	.L2626
	adrp	x0, .LANCHOR130
	add	x0, x0, :lo12:.LANCHOR130
	bl	FtlMapBlkWriteDumpData
	mov	w0, 0
	bl	FtlGcFreeTempBlock
	adrp	x0, .LANCHOR138
	str	wzr, [x0, #:lo12:.LANCHOR138]
.L2626:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	FtlGcPageRecovery, .-FtlGcPageRecovery
	.section	.text.FtlPowerLostRecovery,"ax",@progbits
	.align	2
	.global	FtlPowerLostRecovery
	.type	FtlPowerLostRecovery, %function
FtlPowerLostRecovery:
	stp	x29, x30, [sp, -32]!
	adrp	x0, .LANCHOR243
	add	x29, sp, 0
	str	x19, [sp, 16]
	adrp	x19, .LANCHOR93
	add	x19, x19, :lo12:.LANCHOR93
	str	wzr, [x0, #:lo12:.LANCHOR243]
	mov	x0, x19
	bl	FtlRecoverySuperblock
	mov	x0, x19
	adrp	x19, .LANCHOR94
	bl	FtlSlcSuperblockCheck
	add	x19, x19, :lo12:.LANCHOR94
	mov	x0, x19
	bl	FtlRecoverySuperblock
	mov	x0, x19
	bl	FtlSlcSuperblockCheck
	bl	FtlGcPageRecovery
	mov	w0, -1
	bl	decrement_vpc_count
	mov	w0, 0
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	FtlPowerLostRecovery, .-FtlPowerLostRecovery
	.section	.text.FtlSysBlkInit,"ax",@progbits
	.align	2
	.global	FtlSysBlkInit
	.type	FtlSysBlkInit, %function
FtlSysBlkInit:
	stp	x29, x30, [sp, -32]!
	adrp	x0, .LANCHOR241
	mov	w1, -1
	add	x29, sp, 0
	strh	w1, [x0, #:lo12:.LANCHOR241]
	adrp	x0, .LANCHOR39
	stp	x19, x20, [sp, 16]
	adrp	x20, .LANCHOR242
	ldrh	w0, [x0, #:lo12:.LANCHOR39]
	strh	wzr, [x20, #:lo12:.LANCHOR242]
	bl	FtlFreeSysBlkQueueInit
	bl	FtlScanSysBlk
	adrp	x0, .LANCHOR218
	ldrh	w1, [x0, #:lo12:.LANCHOR218]
	mov	w0, 65535
	cmp	w1, w0
	bne	.L2632
.L2634:
	mov	w19, -1
.L2631:
	mov	w0, w19
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L2632:
	bl	FtlLoadSysInfo
	mov	w19, w0
	cbnz	w0, .L2634
	bl	FtlLoadMapInfo
	bl	FtlLoadVonderInfo
	bl	Ftl_load_ext_data
	bl	FtlLoadEctTbl
	bl	FtlFreeSysBLkSort
	bl	SupperBlkListInit
	bl	FtlPowerLostRecovery
	mov	w0, 1
	bl	FtlUpdateVaildLpn
	adrp	x0, .LANCHOR67
	ldrh	w2, [x0, #:lo12:.LANCHOR67]
	adrp	x0, .LANCHOR98
	ldr	x1, [x0, #:lo12:.LANCHOR98]
	mov	w0, 0
	add	x1, x1, 4
.L2635:
	cmp	w0, w2
	bge	.L2640
	ldr	w3, [x1], 16
	tbz	w3, #31, .L2636
.L2640:
	adrp	x3, .LANCHOR165
	cmp	w0, w2
	ldr	w1, [x3, #:lo12:.LANCHOR165]
	add	w1, w1, 32
	str	w1, [x3, #:lo12:.LANCHOR165]
	bge	.L2642
.L2637:
	adrp	x0, .LANCHOR85
	adrp	x1, .LANCHOR93
	ldr	x2, [x0, #:lo12:.LANCHOR85]
	add	x0, x1, :lo12:.LANCHOR93
	ldrh	w1, [x1, #:lo12:.LANCHOR93]
	ldrh	w4, [x0, 4]
	lsl	x1, x1, 1
	ldrh	w3, [x2, x1]
	sub	w3, w3, w4
	adrp	x4, .LANCHOR52
	strh	w3, [x2, x1]
	strh	wzr, [x0, 4]
	ldrh	w1, [x4, #:lo12:.LANCHOR52]
	strh	w1, [x0, 2]
	adrp	x1, .LANCHOR94
	strb	wzr, [x0, 6]
	add	x0, x1, :lo12:.LANCHOR94
	ldrh	w1, [x1, #:lo12:.LANCHOR94]
	ldrh	w5, [x0, 4]
	lsl	x1, x1, 1
	ldrh	w3, [x2, x1]
	sub	w3, w3, w5
	strh	w3, [x2, x1]
	strb	wzr, [x0, 6]
	ldrh	w1, [x4, #:lo12:.LANCHOR52]
	strh	w1, [x0, 2]
	strh	wzr, [x0, 4]
	adrp	x0, .LANCHOR82
	add	x0, x0, :lo12:.LANCHOR82
	ldrh	w1, [x0, 30]
	add	w1, w1, 1
	strh	w1, [x0, 30]
	bl	l2p_flush
	bl	FtlVpcTblFlush
.L2644:
	bl	FtlVpcTblFlush
	b	.L2631
.L2636:
	add	w0, w0, 1
	b	.L2635
.L2642:
	ldrh	w0, [x20, #:lo12:.LANCHOR242]
	cbnz	w0, .L2637
	bl	l2p_flush
	b	.L2644
	.size	FtlSysBlkInit, .-FtlSysBlkInit
	.section	.text.FtlLowFormat,"ax",@progbits
	.align	2
	.global	FtlLowFormat
	.type	FtlLowFormat, %function
FtlLowFormat:
	adrp	x0, .LANCHOR78
	ldr	w0, [x0, #:lo12:.LANCHOR78]
	cbnz	w0, .L2677
	stp	x29, x30, [sp, -96]!
	adrp	x0, .LANCHOR203
	mov	w1, 0
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	adrp	x19, .LANCHOR66
	ldr	x0, [x0, #:lo12:.LANCHOR203]
	adrp	x20, .LANCHOR164
	ldrh	w2, [x19, #:lo12:.LANCHOR66]
	stp	x23, x24, [sp, 48]
	adrp	x24, .LANCHOR39
	stp	x21, x22, [sp, 32]
	stp	x25, x26, [sp, 64]
	lsl	w2, w2, 2
	str	x27, [sp, 80]
	bl	ftl_memset
	adrp	x0, .LANCHOR134
	ldrh	w2, [x19, #:lo12:.LANCHOR66]
	mov	w1, 0
	ldr	x0, [x0, #:lo12:.LANCHOR134]
	lsl	w2, w2, 2
	bl	ftl_memset
	str	wzr, [x20, #:lo12:.LANCHOR164]
	adrp	x0, .LANCHOR165
	str	wzr, [x0, #:lo12:.LANCHOR165]
	ldrh	w0, [x24, #:lo12:.LANCHOR39]
	bl	FtlFreeSysBlkQueueInit
	bl	FtlLoadBbt
	cbz	w0, .L2648
	bl	FtlMakeBbt
.L2648:
	adrp	x23, .LANCHOR55
	adrp	x0, .LANCHOR193
	mov	w6, 23752
	ldrh	w1, [x23, #:lo12:.LANCHOR55]
	movk	w6, 0xa0f, lsl 16
	ldr	x4, [x0, #:lo12:.LANCHOR193]
	adrp	x0, .LANCHOR194
	lsl	w1, w1, 7
	ldr	x5, [x0, #:lo12:.LANCHOR194]
	mov	w0, 0
.L2649:
	cmp	w0, w1
	blt	.L2650
	adrp	x21, .LANCHOR40
	adrp	x22, .LANCHOR41
	add	x26, x22, :lo12:.LANCHOR41
	mov	w19, 0
	ldrh	w25, [x21, #:lo12:.LANCHOR40]
.L2651:
	ldrh	w0, [x26]
	cmp	w0, w25
	bhi	.L2652
	adrp	x26, .LANCHOR38
	sub	w1, w19, #2
	ldrh	w0, [x26, #:lo12:.LANCHOR38]
	cmp	w1, w0, lsl 1
	ble	.L2653
	adrp	x1, .LANCHOR65
	add	x25, x22, :lo12:.LANCHOR41
	udiv	w0, w19, w0
	ldr	w19, [x1, #:lo12:.LANCHOR65]
	add	w0, w0, w19
	bl	FtlSysBlkNumInit
	ldrh	w0, [x24, #:lo12:.LANCHOR39]
	mov	w19, 0
	bl	FtlFreeSysBlkQueueInit
	ldrh	w24, [x21, #:lo12:.LANCHOR40]
.L2654:
	ldrh	w0, [x25]
	cmp	w0, w24
	bhi	.L2655
.L2653:
	add	x27, x21, :lo12:.LANCHOR40
	mov	w24, 0
	mov	w25, 0
.L2656:
	ldrh	w0, [x27]
	cmp	w0, w25
	bhi	.L2657
	adrp	x0, .LANCHOR75
	ldrh	w1, [x22, #:lo12:.LANCHOR41]
	adrp	x2, .LANCHOR232
	str	w1, [x0, #:lo12:.LANCHOR75]
	adrp	x0, .LANCHOR42
	ldrh	w1, [x26, #:lo12:.LANCHOR38]
	ldr	w3, [x0, #:lo12:.LANCHOR42]
	adrp	x0, .LANCHOR74
	udiv	w6, w3, w1
	ubfx	x5, x6, 5, 16
	str	w6, [x0, #:lo12:.LANCHOR74]
	add	w4, w5, 36
	strh	w4, [x2, #:lo12:.LANCHOR232]
	mov	w4, 24
	mul	w4, w1, w4
	cmp	w24, w4
	ble	.L2658
	sub	w3, w3, w24
	udiv	w3, w3, w1
	str	w3, [x0, #:lo12:.LANCHOR74]
	lsr	w3, w3, 5
	add	w3, w3, 24
	strh	w3, [x2, #:lo12:.LANCHOR232]
.L2658:
	adrp	x3, .LANCHOR104
	ldr	w3, [x3, #:lo12:.LANCHOR104]
	cmp	w3, 1
	bne	.L2659
	udiv	w4, w24, w1
	ldrh	w3, [x2, #:lo12:.LANCHOR232]
	add	w4, w4, w3
	add	w4, w3, w4, asr 2
	strh	w4, [x2, #:lo12:.LANCHOR232]
.L2659:
	adrp	x3, .LANCHOR16
	ldrb	w3, [x3, #:lo12:.LANCHOR16]
	cbz	w3, .L2660
	udiv	w4, w24, w1
	ldrh	w3, [x2, #:lo12:.LANCHOR232]
	add	w4, w4, w3
	add	w4, w3, w4, asr 2
	strh	w4, [x2, #:lo12:.LANCHOR232]
.L2660:
	adrp	x3, .LANCHOR49
	ldrh	w3, [x3, #:lo12:.LANCHOR49]
	cbz	w3, .L2662
	ldrh	w4, [x2, #:lo12:.LANCHOR232]
	add	w4, w4, w3, lsr 1
	strh	w4, [x2, #:lo12:.LANCHOR232]
	mul	w4, w3, w1
	cmp	w24, w4
	bge	.L2662
	add	w3, w3, 32
	str	w6, [x0, #:lo12:.LANCHOR74]
	add	w3, w5, w3
	strh	w3, [x2, #:lo12:.LANCHOR232]
.L2662:
	ldrh	w3, [x2, #:lo12:.LANCHOR232]
	adrp	x25, .LANCHOR231
	ldr	w2, [x0, #:lo12:.LANCHOR74]
	sub	w2, w2, w3
	mul	w1, w2, w1
	adrp	x2, .LANCHOR52
	str	w1, [x25, #:lo12:.LANCHOR231]
	ldrh	w2, [x2, #:lo12:.LANCHOR52]
	mul	w1, w2, w1
	str	w1, [x0, #:lo12:.LANCHOR74]
	ldrh	w0, [x23, #:lo12:.LANCHOR55]
	mul	w1, w0, w1
	adrp	x0, .LANCHOR68
	str	w1, [x0, #:lo12:.LANCHOR68]
	bl	FtlBbmTblFlush
	adrp	x0, .LANCHOR43
	add	w1, w19, w24
	ldr	w2, [x0, #:lo12:.LANCHOR43]
	adrp	x0, .LANCHOR59
	ldrh	w0, [x0, #:lo12:.LANCHOR59]
	add	w0, w0, w2, lsr 3
	cmp	w1, w0
	bls	.L2664
	adrp	x0, .LC75
	lsr	w2, w2, 5
	add	x0, x0, :lo12:.LC75
	bl	printf
.L2664:
	adrp	x24, .LANCHOR85
	ldrh	w2, [x22, #:lo12:.LANCHOR41]
	mov	w1, 0
	mov	w22, -1
	ldr	x0, [x24, #:lo12:.LANCHOR85]
	lsl	w2, w2, 1
	bl	ftl_memset
	adrp	x0, .LANCHOR102
	adrp	x1, .LANCHOR213
	ldrh	w2, [x21, #:lo12:.LANCHOR40]
	str	wzr, [x0, #:lo12:.LANCHOR102]
	add	x0, x1, :lo12:.LANCHOR213
	strh	w22, [x1, #:lo12:.LANCHOR213]
	mov	w1, 255
	lsr	w2, w2, 3
	strh	wzr, [x0, 2]
	strb	wzr, [x0, 6]
	strb	wzr, [x0, 8]
	adrp	x0, .LANCHOR93
	add	x19, x0, :lo12:.LANCHOR93
	strh	wzr, [x0, #:lo12:.LANCHOR93]
	mov	w0, 1
	strb	w0, [x19, 8]
	adrp	x0, .LANCHOR1
	strh	wzr, [x19, 2]
	ldr	x0, [x0, #:lo12:.LANCHOR1]
	strb	wzr, [x19, 6]
	bl	ftl_memset
.L2665:
	mov	x0, x19
	bl	make_superblock
	ldrb	w1, [x19, 7]
	ldrh	w0, [x19]
	cbnz	w1, .L2666
	ldr	x1, [x24, #:lo12:.LANCHOR85]
	ubfiz	x0, x0, 1, 16
	strh	w22, [x1, x0]
	ldrh	w0, [x19]
	add	w0, w0, 1
	strh	w0, [x19]
	b	.L2665
.L2650:
	ubfiz	x3, x0, 2, 16
	mvn	w2, w0
	orr	w2, w0, w2, lsl 16
	add	w0, w0, 1
	and	w0, w0, 65535
	str	w2, [x4, x3]
	str	w6, [x5, x3]
	b	.L2649
.L2652:
	mov	w0, w25
	mov	w1, 1
	add	w25, w25, 1
	bl	FtlLowFormatEraseBlock
	add	w19, w19, w0
	and	w25, w25, 65535
	and	w19, w19, 65535
	b	.L2651
.L2655:
	mov	w0, w24
	mov	w1, 1
	add	w24, w24, 1
	bl	FtlLowFormatEraseBlock
	add	w19, w19, w0
	and	w24, w24, 65535
	and	w19, w19, 65535
	b	.L2654
.L2657:
	mov	w0, w25
	mov	w1, 0
	add	w25, w25, 1
	bl	FtlLowFormatEraseBlock
	add	w24, w24, w0
	and	w25, w25, 65535
	and	w24, w24, 65535
	b	.L2656
.L2666:
	ldr	w1, [x20, #:lo12:.LANCHOR164]
	ubfiz	x0, x0, 1, 16
	str	w1, [x19, 12]
	mov	w22, -1
	add	w1, w1, 1
	str	w1, [x20, #:lo12:.LANCHOR164]
	ldr	x1, [x24, #:lo12:.LANCHOR85]
	ldrh	w2, [x19, 4]
	strh	w2, [x1, x0]
	adrp	x2, .LANCHOR94
	add	x0, x2, :lo12:.LANCHOR94
	ldrh	w1, [x19]
	mov	x19, x0
	add	w1, w1, 1
	strh	wzr, [x0, 2]
	strh	w1, [x2, #:lo12:.LANCHOR94]
	mov	w1, 1
	strb	wzr, [x0, 6]
	strb	w1, [x0, 8]
.L2667:
	mov	x0, x19
	bl	make_superblock
	ldrb	w1, [x19, 7]
	ldrh	w0, [x19]
	cbnz	w1, .L2668
	ldr	x1, [x24, #:lo12:.LANCHOR85]
	ubfiz	x0, x0, 1, 16
	strh	w22, [x1, x0]
	ldrh	w0, [x19]
	add	w0, w0, 1
	strh	w0, [x19]
	b	.L2667
.L2668:
	ldr	w1, [x20, #:lo12:.LANCHOR164]
	ubfiz	x0, x0, 1, 16
	str	w1, [x19, 12]
	add	w1, w1, 1
	str	w1, [x20, #:lo12:.LANCHOR164]
	ldr	x1, [x24, #:lo12:.LANCHOR85]
	ldrh	w2, [x19, 4]
	mov	w19, -1
	strh	w2, [x1, x0]
	adrp	x0, .LANCHOR95
	strh	w19, [x0, #:lo12:.LANCHOR95]
	bl	FtlFreeSysBlkQueueOut
	adrp	x2, .LANCHOR218
	add	x1, x2, :lo12:.LANCHOR218
	strh	w0, [x2, #:lo12:.LANCHOR218]
	ldr	w0, [x25, #:lo12:.LANCHOR231]
	strh	w0, [x1, 6]
	ldr	w0, [x20, #:lo12:.LANCHOR164]
	str	w0, [x1, 8]
	add	w0, w0, 1
	strh	wzr, [x1, 2]
	strh	w19, [x1, 4]
	str	w0, [x20, #:lo12:.LANCHOR164]
	bl	FtlVpcTblFlush
	bl	FtlSysBlkInit
	cbnz	w0, .L2647
	adrp	x0, .LANCHOR247
	mov	w1, 1
	str	w1, [x0, #:lo12:.LANCHOR247]
.L2647:
	mov	w0, 0
	ldr	x27, [sp, 80]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 96
	ret
.L2677:
	mov	w0, 0
	ret
	.size	FtlLowFormat, .-FtlLowFormat
	.section	.text.Ftl_gc_temp_data_write_back,"ax",@progbits
	.align	2
	.global	Ftl_gc_temp_data_write_back
	.type	Ftl_gc_temp_data_write_back, %function
Ftl_gc_temp_data_write_back:
	adrp	x0, .LANCHOR78
	ldr	w0, [x0, #:lo12:.LANCHOR78]
	cbz	w0, .L2681
	mov	w0, 0
	ret
.L2684:
	mov	w0, 0
.L2680:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L2681:
	stp	x29, x30, [sp, -32]!
	adrp	x0, .LANCHOR16
	add	x29, sp, 0
	ldrb	w0, [x0, #:lo12:.LANCHOR16]
	stp	x19, x20, [sp, 16]
	adrp	x19, .LANCHOR105
	cbz	w0, .L2683
	ldr	w0, [x19, #:lo12:.LANCHOR105]
	tbz	x0, 0, .L2683
	adrp	x0, .LANCHOR95+4
	ldrh	w0, [x0, #:lo12:.LANCHOR95+4]
	cbnz	w0, .L2684
.L2683:
	adrp	x20, .LANCHOR187
	ldr	w1, [x19, #:lo12:.LANCHOR105]
	mov	w3, 0
	mov	w2, 0
	ldr	x0, [x20, #:lo12:.LANCHOR187]
	add	x19, x19, :lo12:.LANCHOR105
	bl	FlashProgPages
	mov	w11, 0
	mov	w12, 56
.L2685:
	ldr	w1, [x19]
	cmp	w11, w1
	bcc	.L2687
	ldr	x0, [x20, #:lo12:.LANCHOR187]
	bl	FtlGcBufFree
	str	wzr, [x19]
	adrp	x0, .LANCHOR95+4
	ldrh	w0, [x0, #:lo12:.LANCHOR95+4]
	cbnz	w0, .L2684
	mov	w0, 1
	bl	FtlGcFreeTempBlock
	b	.L2697
.L2687:
	umull	x0, w11, w12
	ldr	x2, [x20, #:lo12:.LANCHOR187]
	add	x1, x2, x0
	ldr	w2, [x2, x0]
	ldr	x3, [x1, 16]
	cmn	w2, #1
	bne	.L2686
	adrp	x0, .LANCHOR95
	adrp	x3, .LANCHOR85
	ldrh	w4, [x0, #:lo12:.LANCHOR95]
	ldr	x3, [x3, #:lo12:.LANCHOR85]
	strh	wzr, [x3, x4, lsl 1]
	strh	w2, [x0, #:lo12:.LANCHOR95]
	adrp	x0, .LANCHOR141
	add	x0, x0, :lo12:.LANCHOR141
	ldr	w2, [x0, 96]
	add	w2, w2, 1
	str	w2, [x0, 96]
	ldr	w0, [x1, 4]
	lsr	w0, w0, 10
	bl	FtlBbmMapBadBlock
	bl	FtlBbmTblFlush
	bl	FtlGcPageVarInit
.L2697:
	mov	w0, 1
	b	.L2680
.L2686:
	ldr	w1, [x1, 4]
	ldp	w2, w0, [x3, 8]
	bl	FtlGcUpdatePage
	add	w11, w11, 1
	and	w11, w11, 65535
	b	.L2685
	.size	Ftl_gc_temp_data_write_back, .-Ftl_gc_temp_data_write_back
	.section	.text.Ftl_get_new_temp_ppa,"ax",@progbits
	.align	2
	.global	Ftl_get_new_temp_ppa
	.type	Ftl_get_new_temp_ppa, %function
Ftl_get_new_temp_ppa:
	stp	x29, x30, [sp, -32]!
	adrp	x0, .LANCHOR95
	mov	w2, 65535
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	ldrh	w3, [x0, #:lo12:.LANCHOR95]
	cmp	w3, w2
	beq	.L2699
	add	x1, x0, :lo12:.LANCHOR95
	ldrh	w0, [x1, 4]
	cbnz	w0, .L2700
.L2699:
	bl	FtlCacheWriteBack
	mov	w0, 0
	bl	FtlGcFreeTempBlock
	add	x0, x19, :lo12:.LANCHOR95
	strb	wzr, [x0, 8]
	bl	allocate_data_superblock
	adrp	x0, .LANCHOR111
	strh	wzr, [x0, #:lo12:.LANCHOR111]
	adrp	x0, .LANCHOR113
	strh	wzr, [x0, #:lo12:.LANCHOR113]
	bl	l2p_flush
	mov	w0, 0
	bl	FtlEctTblFlush
	bl	FtlVpcTblFlush
.L2700:
	add	x0, x19, :lo12:.LANCHOR95
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	b	get_new_active_ppa
	.size	Ftl_get_new_temp_ppa, .-Ftl_get_new_temp_ppa
	.section	.text.ftl_do_gc,"ax",@progbits
	.align	2
	.global	ftl_do_gc
	.type	ftl_do_gc, %function
ftl_do_gc:
	adrp	x1, .LANCHOR78
	ldr	w1, [x1, #:lo12:.LANCHOR78]
	cbnz	w1, .L2762
	adrp	x1, .LANCHOR247
	ldr	w1, [x1, #:lo12:.LANCHOR247]
	cmp	w1, 1
	bne	.L2762
	stp	x29, x30, [sp, -176]!
	add	x29, sp, 0
	stp	x21, x22, [sp, 32]
	adrp	x21, .LANCHOR176
	stp	x19, x20, [sp, 16]
	ldr	w1, [x21, #:lo12:.LANCHOR176]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	cbnz	w1, .L2764
	adrp	x1, .LANCHOR87
	ldrh	w1, [x1, #:lo12:.LANCHOR87]
	cmp	w1, 47
	bls	.L2764
	adrp	x5, .LANCHOR116
	mov	w2, 65535
	ldrh	w8, [x5, #:lo12:.LANCHOR116]
	cmp	w8, w2
	beq	.L2704
	adrp	x7, .LANCHOR115
	ldrh	w1, [x7, #:lo12:.LANCHOR115]
	cmp	w1, w2
	bne	.L2704
	adrp	x3, .LANCHOR117
	ldrh	w6, [x3, #:lo12:.LANCHOR117]
	cmp	w6, w1
	beq	.L2704
	adrp	x2, .LANCHOR118
	ldrh	w4, [x2, #:lo12:.LANCHOR118]
	cmp	w4, w1
	beq	.L2704
	mov	w1, -1
	strh	w8, [x7, #:lo12:.LANCHOR115]
	strh	w6, [x5, #:lo12:.LANCHOR116]
	strh	w4, [x3, #:lo12:.LANCHOR117]
	strh	w1, [x2, #:lo12:.LANCHOR118]
.L2704:
	cbnz	w0, .L2765
	adrp	x0, .LANCHOR90
	ldrh	w0, [x0, #:lo12:.LANCHOR90]
	cmp	w0, 24
	bhi	.L2766
	adrp	x1, .LANCHOR52
	cmp	w0, 16
	ldrh	w20, [x1, #:lo12:.LANCHOR52]
	bls	.L2707
	lsr	w20, w20, 5
.L2706:
	adrp	x2, .LANCHOR181
	mov	x3, x2
	ldrh	w1, [x2, #:lo12:.LANCHOR181]
	cmp	w1, w0
	bcs	.L2710
	adrp	x0, .LANCHOR95
	mov	w1, 65535
	ldrh	w0, [x0, #:lo12:.LANCHOR95]
	cmp	w0, w1
	bne	.L2711
	adrp	x1, .LANCHOR115
	ldrh	w1, [x1, #:lo12:.LANCHOR115]
	cmp	w1, w0
	bne	.L2711
	adrp	x0, .LANCHOR248
	ldrh	w0, [x0, #:lo12:.LANCHOR248]
	cbnz	w0, .L2712
	adrp	x1, .LANCHOR74
	adrp	x4, .LANCHOR102
	ldr	w1, [x1, #:lo12:.LANCHOR74]
	ldr	w4, [x4, #:lo12:.LANCHOR102]
	add	w1, w1, w1, lsl 1
	cmp	w4, w1, lsr 2
	bcs	.L2713
.L2712:
	adrp	x1, .LANCHOR232
	ldrh	w1, [x1, #:lo12:.LANCHOR232]
	add	w1, w1, w1, lsl 1
	asr	w1, w1, 2
	strh	w1, [x3, #:lo12:.LANCHOR181]
.L2714:
	adrp	x1, .LANCHOR177
	str	wzr, [x1, #:lo12:.LANCHOR177]
.L2702:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 176
	ret
.L2707:
	cmp	w0, 12
	bls	.L2708
	lsr	w20, w20, 4
	b	.L2706
.L2708:
	cmp	w0, 8
	bls	.L2706
	lsr	w20, w20, 2
	b	.L2706
.L2766:
	mov	w20, 1
	b	.L2706
.L2713:
	mov	w1, 18
	strh	w1, [x2, #:lo12:.LANCHOR181]
	b	.L2714
.L2711:
	adrp	x0, .LANCHOR232
	ldrh	w0, [x0, #:lo12:.LANCHOR232]
	add	w0, w0, w0, lsl 1
	asr	w0, w0, 2
	strh	w0, [x3, #:lo12:.LANCHOR181]
.L2710:
	adrp	x0, .LANCHOR119
	ldrh	w0, [x0, #:lo12:.LANCHOR119]
	cbz	w0, .L2705
	add	w20, w20, 32
	and	w20, w20, 65535
.L2705:
	adrp	x19, .LANCHOR213
	mov	w0, 65535
	ldrh	w2, [x19, #:lo12:.LANCHOR213]
	cmp	w2, w0
	bne	.L2717
	adrp	x0, .LANCHOR115
	ldrh	w1, [x0, #:lo12:.LANCHOR115]
	cmp	w1, w2
	beq	.L2718
	adrp	x2, .LANCHOR85
	ubfiz	x1, x1, 1, 16
	ldr	x2, [x2, #:lo12:.LANCHOR85]
	ldrh	w1, [x2, x1]
	cbnz	w1, .L2719
	mov	w1, -1
	strh	w1, [x0, #:lo12:.LANCHOR115]
.L2719:
	ldrh	w1, [x0, #:lo12:.LANCHOR115]
	strh	w1, [x19, #:lo12:.LANCHOR213]
	mov	w1, -1
	strh	w1, [x0, #:lo12:.LANCHOR115]
.L2718:
	add	x0, x19, :lo12:.LANCHOR213
	mov	w1, 65535
	strb	wzr, [x0, 8]
	ldrh	w0, [x19, #:lo12:.LANCHOR213]
	cmp	w0, w1
	beq	.L2717
	bl	IsBlkInGcList
	cbz	w0, .L2721
	mov	w0, -1
	strh	w0, [x19, #:lo12:.LANCHOR213]
.L2721:
	adrp	x0, .LANCHOR16
	ldrb	w0, [x0, #:lo12:.LANCHOR16]
	cbz	w0, .L2722
	ldrh	w0, [x19, #:lo12:.LANCHOR213]
	add	x3, x19, :lo12:.LANCHOR213
	bl	ftl_get_blk_mode
	strb	w0, [x3, 8]
.L2722:
	ldrh	w1, [x19, #:lo12:.LANCHOR213]
	mov	w0, 65535
	add	x22, x19, :lo12:.LANCHOR213
	cmp	w1, w0
	beq	.L2717
	mov	x0, x22
	bl	make_superblock
	adrp	x0, .LANCHOR249
	ldrh	w1, [x19, #:lo12:.LANCHOR213]
	strh	wzr, [x22, 2]
	strh	wzr, [x0, #:lo12:.LANCHOR249]
	adrp	x0, .LANCHOR85
	strb	wzr, [x22, 6]
	ldr	x0, [x0, #:lo12:.LANCHOR85]
	ldrh	w1, [x0, x1, lsl 1]
	adrp	x0, .LANCHOR250
	strh	w1, [x0, #:lo12:.LANCHOR250]
.L2717:
	adrp	x1, .LANCHOR93
	ldrh	w0, [x19, #:lo12:.LANCHOR213]
	str	x1, [x29, 128]
	ldrh	w2, [x1, #:lo12:.LANCHOR93]
	cmp	w2, w0
	beq	.L2723
	adrp	x1, .LANCHOR94
	ldrh	w1, [x1, #:lo12:.LANCHOR94]
	cmp	w1, w0
	beq	.L2723
	adrp	x1, .LANCHOR95
	ldrh	w1, [x1, #:lo12:.LANCHOR95]
	cmp	w1, w0
	bne	.L2724
.L2723:
	mov	w0, -1
	strh	w0, [x19, #:lo12:.LANCHOR213]
.L2724:
	adrp	x25, .LANCHOR183
	add	x26, x25, :lo12:.LANCHOR183
.L2760:
	ldrh	w1, [x19, #:lo12:.LANCHOR213]
	mov	w0, 65535
	cmp	w1, w0
	bne	.L2725
	adrp	x0, .LANCHOR177
	adrp	x22, .LANCHOR52
	add	x22, x22, :lo12:.LANCHOR52
	str	wzr, [x0, #:lo12:.LANCHOR177]
.L2726:
	ldrh	w5, [x25, #:lo12:.LANCHOR183]
	add	x7, x25, :lo12:.LANCHOR183
	mov	w0, w5
	bl	List_get_gc_head_node
	and	w6, w0, 65535
	strh	w6, [x19, #:lo12:.LANCHOR213]
	mov	w0, 65535
	cmp	w6, w0
	bne	.L2727
	strh	wzr, [x7]
	mov	w0, 8
	b	.L2702
.L2765:
	mov	w20, 1
	b	.L2705
.L2727:
	mov	w0, w6
	bl	IsBlkInGcList
	add	w5, w5, 1
	cbz	w0, .L2728
	strh	w5, [x25, #:lo12:.LANCHOR183]
	b	.L2726
.L2728:
	adrp	x23, .LANCHOR85
	adrp	x4, .LANCHOR38
	ldrh	w0, [x22]
	ubfiz	x1, x6, 1, 16
	ldr	x2, [x23, #:lo12:.LANCHOR85]
	and	w5, w5, 65535
	ldrh	w4, [x4, #:lo12:.LANCHOR38]
	strh	w5, [x25, #:lo12:.LANCHOR183]
	ldrh	w3, [x2, x1]
	mul	w0, w0, w4
	cmp	w3, w0, asr 1
	bgt	.L2730
	cmp	w5, 48
	bls	.L2731
	cmp	w3, 8
	bls	.L2731
	adrp	x3, .LANCHOR111
	ldrh	w3, [x3, #:lo12:.LANCHOR111]
	cmp	w3, 35
	bhi	.L2731
.L2730:
	strh	wzr, [x26]
.L2731:
	ldrh	w1, [x2, x1]
	cmp	w0, w1
	bgt	.L2732
	ldrh	w0, [x26]
	cmp	w0, 3
	bhi	.L2732
	mov	w0, -1
	strh	wzr, [x26]
	strh	w0, [x19, #:lo12:.LANCHOR213]
.L2804:
	adrp	x0, .LANCHOR248
	ldrh	w0, [x0, #:lo12:.LANCHOR248]
	b	.L2702
.L2732:
	cbnz	w1, .L2733
	mov	w0, -1
	bl	decrement_vpc_count
	ldrh	w0, [x26]
	add	w0, w0, 1
	strh	w0, [x26]
	b	.L2726
.L2733:
	adrp	x0, .LANCHOR16
	add	x3, x19, :lo12:.LANCHOR213
	ldrb	w0, [x0, #:lo12:.LANCHOR16]
	strb	wzr, [x3, 8]
	cbz	w0, .L2734
	mov	w0, w6
	bl	ftl_get_blk_mode
	strb	w0, [x3, 8]
.L2734:
	ldr	x0, [x29, 128]
	ldrh	w0, [x0, #:lo12:.LANCHOR93]
	cmp	w0, w6
	bne	.L2735
	mov	w2, 1069
	adrp	x1, .LANCHOR251
	adrp	x0, .LC5
	add	x1, x1, :lo12:.LANCHOR251
	add	x0, x0, :lo12:.LC5
	bl	printf
	adrp	x1, .LC6
	adrp	x0, .LC7
	add	x1, x1, :lo12:.LC6
	add	x0, x0, :lo12:.LC7
	bl	printf
.L2735:
	adrp	x0, .LANCHOR94
	ldrh	w1, [x19, #:lo12:.LANCHOR213]
	ldrh	w0, [x0, #:lo12:.LANCHOR94]
	cmp	w1, w0
	bne	.L2736
	mov	w2, 1070
	adrp	x1, .LANCHOR251
	adrp	x0, .LC5
	add	x1, x1, :lo12:.LANCHOR251
	add	x0, x0, :lo12:.LC5
	bl	printf
	adrp	x1, .LC6
	adrp	x0, .LC7
	add	x1, x1, :lo12:.LC6
	add	x0, x0, :lo12:.LC7
	bl	printf
.L2736:
	adrp	x0, .LANCHOR95
	ldrh	w1, [x19, #:lo12:.LANCHOR213]
	ldrh	w0, [x0, #:lo12:.LANCHOR95]
	cmp	w1, w0
	bne	.L2737
	mov	w2, 1071
	adrp	x1, .LANCHOR251
	adrp	x0, .LC5
	add	x1, x1, :lo12:.LANCHOR251
	add	x0, x0, :lo12:.LC5
	bl	printf
	adrp	x1, .LC6
	adrp	x0, .LC7
	add	x1, x1, :lo12:.LC6
	add	x0, x0, :lo12:.LC7
	bl	printf
.L2737:
	add	x22, x19, :lo12:.LANCHOR213
	mov	x0, x22
	bl	make_superblock
	adrp	x0, .LANCHOR249
	ldrh	w1, [x19, #:lo12:.LANCHOR213]
	strh	wzr, [x0, #:lo12:.LANCHOR249]
	ldr	x0, [x23, #:lo12:.LANCHOR85]
	ldrh	w1, [x0, x1, lsl 1]
	adrp	x0, .LANCHOR250
	strh	wzr, [x22, 2]
	strh	w1, [x0, #:lo12:.LANCHOR250]
	strb	wzr, [x22, 6]
.L2725:
	adrp	x1, .LANCHOR52
	mov	w0, 1
	str	w0, [x21, #:lo12:.LANCHOR176]
	ldrh	w0, [x1, #:lo12:.LANCHOR52]
	str	w0, [x29, 156]
	adrp	x0, .LANCHOR16
	str	x1, [x29, 120]
	str	x0, [x29, 112]
	ldrb	w2, [x0, #:lo12:.LANCHOR16]
	cbz	w2, .L2738
	add	x0, x19, :lo12:.LANCHOR213
	ldrb	w0, [x0, 8]
	cmp	w0, 1
	bne	.L2738
	adrp	x0, .LANCHOR53
	ldrh	w0, [x0, #:lo12:.LANCHOR53]
	str	w0, [x29, 156]
.L2738:
	add	x0, x19, :lo12:.LANCHOR213
	ldr	w2, [x29, 156]
	ldrh	w0, [x0, 2]
	add	w1, w0, w20
	cmp	w1, w2
	ble	.L2739
	sub	w20, w2, w0
	and	w20, w20, 65535
.L2739:
	adrp	x0, .LANCHOR249
	mov	w28, 0
	add	x0, x0, :lo12:.LANCHOR249
	str	x0, [x29, 144]
.L2740:
	cmp	w20, w28, uxth
	bls	.L2748
	add	x1, x19, :lo12:.LANCHOR213
	adrp	x0, .LANCHOR38
	adrp	x23, .LANCHOR109
	add	x1, x1, 16
	ldrh	w7, [x0, #:lo12:.LANCHOR38]
	mov	w22, 0
	ldrh	w4, [x1, -14]
	mov	w2, 0
	ldr	x0, [x23, #:lo12:.LANCHOR109]
	mov	w6, 65535
	add	w4, w4, w28
	mov	w5, 56
	b	.L2749
.L2742:
	ldrh	w3, [x1]
	cmp	w3, w6
	beq	.L2741
	umaddl	x8, w22, w5, x0
	add	w22, w22, 1
	and	w22, w22, 65535
	orr	w3, w4, w3, lsl 10
	str	w3, [x8, 4]
.L2741:
	add	w2, w2, 1
	add	x1, x1, 2
	and	w2, w2, 65535
.L2749:
	cmp	w2, w7
	bne	.L2742
	add	x1, x19, :lo12:.LANCHOR213
	adrp	x24, .LANCHOR105
	add	x24, x24, :lo12:.LANCHOR105
	ldrb	w2, [x1, 8]
	mov	w1, w22
	bl	FlashReadPages
	mov	w0, 56
	umull	x0, w22, w0
	mov	x22, 0
	str	x0, [x29, 136]
.L2743:
	ldr	x0, [x29, 136]
	cmp	x0, x22
	bne	.L2747
	add	w28, w28, 1
	b	.L2740
.L2747:
	ldr	x0, [x23, #:lo12:.LANCHOR109]
	add	x1, x0, x22
	ldr	w0, [x0, x22]
	cmn	w0, #1
	beq	.L2744
	ldr	x27, [x1, 16]
	mov	w0, 61589
	ldrh	w1, [x27]
	cmp	w1, w0
	bne	.L2744
	ldr	w4, [x27, 8]
	cmn	w4, #1
	bne	.L2745
	mov	w2, 1119
	str	w4, [x29, 104]
	adrp	x1, .LANCHOR251
	adrp	x0, .LC5
	add	x1, x1, :lo12:.LANCHOR251
	add	x0, x0, :lo12:.LC5
	bl	printf
	adrp	x1, .LC6
	adrp	x0, .LC7
	add	x1, x1, :lo12:.LC6
	add	x0, x0, :lo12:.LC7
	bl	printf
	ldr	w4, [x29, 104]
.L2745:
	mov	w2, 0
	add	x1, x29, 168
	mov	w0, w4
	bl	log2phys
	ldr	x0, [x23, #:lo12:.LANCHOR109]
	ldr	w1, [x29, 168]
	add	x0, x0, x22
	and	w1, w1, 2147483647
	ldr	w2, [x0, 4]
	cmp	w1, w2
	bne	.L2744
	ldr	x1, [x29, 144]
	adrp	x4, .LANCHOR187
	ldr	x2, [x29, 144]
	ldr	x5, [x4, #:lo12:.LANCHOR187]
	ldr	w0, [x0, 24]
	ldrh	w1, [x1]
	add	w1, w1, 1
	strh	w1, [x2]
	ldr	w2, [x24]
	mov	w1, 56
	str	w1, [x29, 152]
	nop // between mem op and mult-accumulate
	umaddl	x2, w2, w1, x5
	stp	x4, x2, [x29, 96]
	str	w0, [x2, 24]
	bl	Ftl_get_new_temp_ppa
	ldp	x4, x2, [x29, 96]
	ldr	w1, [x29, 152]
	str	w0, [x2, 4]
	ldr	x0, [x4, #:lo12:.LANCHOR187]
	ldr	w2, [x24]
	umaddl	x1, w2, w1, x0
	ldr	x0, [x23, #:lo12:.LANCHOR109]
	add	w2, w2, 1
	add	x0, x0, x22
	ldr	x4, [x0, 8]
	str	x4, [x1, 8]
	ldr	x4, [x0, 16]
	str	x4, [x1, 16]
	ldr	w1, [x29, 168]
	str	w1, [x27, 12]
	adrp	x1, .LANCHOR95
	add	x12, x1, :lo12:.LANCHOR95
	ldrh	w1, [x1, #:lo12:.LANCHOR95]
	strh	w1, [x27, 2]
	adrp	x1, .LANCHOR165
	str	w2, [x24]
	ldr	w1, [x1, #:lo12:.LANCHOR165]
	str	w1, [x27, 4]
	mov	w1, 1
	bl	FtlGcBufAlloc
	ldr	x0, [x29, 112]
	ldrb	w0, [x0, #:lo12:.LANCHOR16]
	cbnz	w0, .L2746
	ldrb	w1, [x12, 7]
	ldr	w0, [x24]
	cmp	w1, w0
	beq	.L2746
	ldrh	w0, [x12, 4]
	cbnz	w0, .L2744
.L2746:
	bl	Ftl_gc_temp_data_write_back
	cbz	w0, .L2744
	add	x0, x19, :lo12:.LANCHOR213
	mov	w1, -1
	str	wzr, [x21, #:lo12:.LANCHOR176]
	strh	w1, [x19, #:lo12:.LANCHOR213]
	strh	wzr, [x0, 2]
	b	.L2804
.L2744:
	add	x22, x22, 56
	b	.L2743
.L2748:
	add	x1, x19, :lo12:.LANCHOR213
	ldrh	w0, [x1, 2]
	add	w20, w20, w0
	ldr	w0, [x29, 156]
	and	w20, w20, 65535
	strh	w20, [x1, 2]
	cmp	w0, w20
	bhi	.L2750
	adrp	x0, .LANCHOR105
	ldr	w0, [x0, #:lo12:.LANCHOR105]
	cbz	w0, .L2751
	bl	Ftl_gc_temp_data_write_back
	cbz	w0, .L2751
	str	wzr, [x21, #:lo12:.LANCHOR176]
	b	.L2804
.L2751:
	adrp	x0, .LANCHOR249
	ldrh	w0, [x0, #:lo12:.LANCHOR249]
	cbnz	w0, .L2752
	adrp	x22, .LANCHOR85
	ldrh	w1, [x19, #:lo12:.LANCHOR213]
	ldr	x0, [x22, #:lo12:.LANCHOR85]
	ldrh	w0, [x0, x1, lsl 1]
	cbz	w0, .L2752
	adrp	x23, .LANCHOR74
	add	x24, x23, :lo12:.LANCHOR74
	mov	w20, 0
.L2753:
	ldr	w0, [x24]
	cmp	w20, w0
	bcs	.L2758
	mov	w2, 0
	add	x1, x29, 172
	mov	w0, w20
	bl	log2phys
	ldr	w0, [x29, 172]
	cmn	w0, #1
	beq	.L2754
	lsr	w0, w0, 10
	bl	P2V_block_in_plane
	ldrh	w1, [x19, #:lo12:.LANCHOR213]
	cmp	w1, w0, uxth
	bne	.L2754
.L2758:
	ldr	w0, [x23, #:lo12:.LANCHOR74]
	cmp	w20, w0
	bcc	.L2752
	ldrh	w1, [x19, #:lo12:.LANCHOR213]
	ldr	x0, [x22, #:lo12:.LANCHOR85]
	strh	wzr, [x0, x1, lsl 1]
	ldrh	w0, [x19, #:lo12:.LANCHOR213]
	bl	update_vpc_list
	bl	FtlCacheWriteBack
	bl	l2p_flush
	bl	FtlVpcTblFlush
.L2752:
	mov	w0, -1
	strh	w0, [x19, #:lo12:.LANCHOR213]
.L2750:
	adrp	x0, .LANCHOR90
	ldrh	w0, [x0, #:lo12:.LANCHOR90]
	cmp	w0, 2
	bhi	.L2759
	ldr	x0, [x29, 120]
	ldrh	w20, [x0, #:lo12:.LANCHOR52]
	b	.L2760
.L2754:
	add	w20, w20, 1
	b	.L2753
.L2759:
	str	wzr, [x21, #:lo12:.LANCHOR176]
	add	w0, w0, 1
	b	.L2702
.L2762:
	mov	w0, 0
	ret
.L2764:
	mov	w0, 0
	b	.L2702
	.size	ftl_do_gc, .-ftl_do_gc
	.section	.text.FtlCacheWriteBack,"ax",@progbits
	.align	2
	.global	FtlCacheWriteBack
	.type	FtlCacheWriteBack, %function
FtlCacheWriteBack:
	stp	x29, x30, [sp, -128]!
	add	x29, sp, 0
	stp	x25, x26, [sp, 64]
	adrp	x25, .LANCHOR78
	stp	x23, x24, [sp, 48]
	ldr	w23, [x25, #:lo12:.LANCHOR78]
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	stp	x27, x28, [sp, 80]
	cbnz	w23, .L2807
	adrp	x22, .LANCHOR72
	ldr	w1, [x22, #:lo12:.LANCHOR72]
	cbz	w1, .L2807
	adrp	x0, .LANCHOR252
	ldr	x19, [x0, #:lo12:.LANCHOR252]
	adrp	x0, .LANCHOR16
	ldrb	w0, [x0, #:lo12:.LANCHOR16]
	cbz	w0, .L2832
	ldrb	w0, [x19, 8]
	cmp	w0, 1
	cset	w24, eq
.L2809:
	adrp	x20, .LANCHOR73
	ldrb	w3, [x19, 9]
	adrp	x26, .LC76
	add	x27, x22, :lo12:.LANCHOR72
	ldr	x0, [x20, #:lo12:.LANCHOR73]
	add	x26, x26, :lo12:.LC76
	mov	w21, 0
	mov	w28, 56
	mov	w2, w24
	bl	FlashProgPages
.L2810:
	ldr	w0, [x27]
	cmp	w21, w0
	bcc	.L2817
.L2829:
	str	wzr, [x22, #:lo12:.LANCHOR72]
.L2807:
	ldp	x19, x20, [sp, 16]
	mov	w0, 0
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 128
	ret
.L2832:
	mov	w24, 0
	b	.L2809
.L2817:
	umull	x3, w21, w28
	ldr	x0, [x20, #:lo12:.LANCHOR73]
	add	x4, x0, x3
	ldr	w0, [x0, x3]
	cmn	w0, #1
	bne	.L2811
	adrp	x27, .LANCHOR52
	adrp	x26, .LANCHOR141
	add	x27, x27, :lo12:.LANCHOR52
	add	x26, x26, :lo12:.LANCHOR141
.L2812:
	ldr	w0, [x22, #:lo12:.LANCHOR72]
	cmp	w23, w0
	bcc	.L2827
	adrp	x19, .LANCHOR119
	add	x19, x19, :lo12:.LANCHOR119
	mov	w20, 16386
.L2830:
	ldrh	w0, [x19]
	cbz	w0, .L2829
	mov	w1, 1
	mov	w0, w1
	bl	ftl_do_gc
	subs	w20, w20, #1
	bne	.L2830
	b	.L2829
.L2811:
	ldr	w0, [x4, 4]
	cbnz	w24, .L2813
.L2846:
	str	w0, [x29, 124]
	mov	w2, 1
	ldr	w0, [x4, 24]
	add	x1, x29, 124
	str	x3, [x29, 104]
	bl	log2phys
	ldr	x0, [x20, #:lo12:.LANCHOR73]
	ldr	x3, [x29, 104]
	add	x0, x0, x3
	ldr	x0, [x0, 16]
	ldr	w0, [x0, 12]
	cmn	w0, #1
	beq	.L2815
	lsr	w0, w0, 10
	bl	P2V_block_in_plane
	adrp	x2, .LANCHOR85
	and	w1, w0, 65535
	ubfiz	x0, x1, 1, 16
	mov	w3, w1
	ldr	x2, [x2, #:lo12:.LANCHOR85]
	ldrh	w0, [x2, x0]
	cbnz	w0, .L2816
	mov	w2, 0
	mov	x0, x26
	str	w1, [x29, 104]
	bl	printf
	ldr	w3, [x29, 104]
.L2816:
	mov	w0, w3
	bl	decrement_vpc_count
.L2815:
	add	w21, w21, 1
	b	.L2810
.L2813:
	orr	w0, w0, -2147483648
	b	.L2846
.L2827:
	mov	w21, 56
	ldr	x0, [x20, #:lo12:.LANCHOR73]
	mov	w1, -1
	adrp	x28, .LANCHOR85
	umull	x21, w23, w21
	str	w1, [x0, x21]
.L2818:
	ldr	x0, [x20, #:lo12:.LANCHOR73]
	add	x3, x0, x21
	ldr	w0, [x0, x21]
	cmn	w0, #1
	ldr	w0, [x3, 4]
	beq	.L2822
	cbnz	w24, .L2823
.L2847:
	str	w0, [x29, 124]
	mov	w2, 1
	ldr	w0, [x3, 24]
	add	x1, x29, 124
	bl	log2phys
	ldr	x0, [x20, #:lo12:.LANCHOR73]
	add	x21, x0, x21
	ldr	x0, [x21, 16]
	ldr	w0, [x0, 12]
	cmn	w0, #1
	beq	.L2825
	lsr	w0, w0, 10
	bl	P2V_block_in_plane
	adrp	x2, .LANCHOR85
	and	w1, w0, 65535
	ubfiz	x0, x1, 1, 16
	mov	w21, w1
	ldr	x2, [x2, #:lo12:.LANCHOR85]
	ldrh	w0, [x2, x0]
	cbnz	w0, .L2826
	adrp	x0, .LC76
	mov	w2, 0
	add	x0, x0, :lo12:.LC76
	bl	printf
.L2826:
	mov	w0, w21
	bl	decrement_vpc_count
.L2825:
	add	w23, w23, 1
	b	.L2812
.L2822:
	lsr	w0, w0, 10
	bl	P2V_block_in_plane
	ldrh	w1, [x19]
	cmp	w1, w0, uxth
	bne	.L2819
	ldr	x2, [x28, #:lo12:.LANCHOR85]
	ubfiz	x1, x1, 1, 16
	ldrh	w3, [x19, 4]
	ldrh	w0, [x2, x1]
	sub	w0, w0, w3
	strh	w0, [x2, x1]
	strb	wzr, [x19, 6]
	ldrh	w0, [x27]
	strh	w0, [x19, 2]
	strh	wzr, [x19, 4]
.L2819:
	ldrh	w0, [x19, 4]
	cbnz	w0, .L2820
	mov	x0, x19
	bl	allocate_new_data_superblock
.L2820:
	ldr	w0, [x26, 96]
	add	w0, w0, 1
	str	w0, [x26, 96]
	ldr	x0, [x20, #:lo12:.LANCHOR73]
	add	x0, x0, x21
	ldr	w0, [x0, 4]
	lsr	w0, w0, 10
	bl	FtlGcMarkBadPhyBlk
	mov	x0, x19
	bl	get_new_active_ppa
	ldr	x1, [x20, #:lo12:.LANCHOR73]
	mov	w2, w0
	str	w2, [x29, 124]
	add	x0, x1, x21
	mov	w1, 1
	str	w2, [x0, 4]
	mov	w2, w24
	ldrb	w3, [x19, 9]
	bl	FlashProgPages
	ldr	x0, [x20, #:lo12:.LANCHOR73]
	ldr	w0, [x0, x21]
	cmn	w0, #1
	bne	.L2821
	mov	w0, 1
	str	w0, [x25, #:lo12:.LANCHOR78]
.L2821:
	ldr	w0, [x25, #:lo12:.LANCHOR78]
	cbz	w0, .L2818
	b	.L2807
.L2823:
	orr	w0, w0, -2147483648
	b	.L2847
	.size	FtlCacheWriteBack, .-FtlCacheWriteBack
	.section	.text.FtlSysFlush,"ax",@progbits
	.align	2
	.global	FtlSysFlush
	.type	FtlSysFlush, %function
FtlSysFlush:
	adrp	x0, .LANCHOR78
	ldr	w0, [x0, #:lo12:.LANCHOR78]
	cbnz	w0, .L2851
	stp	x29, x30, [sp, -32]!
	adrp	x0, .LANCHOR247
	add	x29, sp, 0
	str	x19, [sp, 16]
	ldr	w19, [x0, #:lo12:.LANCHOR247]
	cmp	w19, 1
	bne	.L2849
	bl	FtlCacheWriteBack
	bl	l2p_flush
	mov	w0, w19
	bl	FtlEctTblFlush
	bl	FtlVpcTblFlush
.L2849:
	mov	w0, 0
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L2851:
	mov	w0, 0
	ret
	.size	FtlSysFlush, .-FtlSysFlush
	.section	.text.FtlDeInit,"ax",@progbits
	.align	2
	.global	FtlDeInit
	.type	FtlDeInit, %function
FtlDeInit:
	adrp	x0, .LANCHOR247
	ldr	w0, [x0, #:lo12:.LANCHOR247]
	cmp	w0, 1
	bne	.L2857
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
	bl	FtlSysFlush
	mov	w0, 0
	ldp	x29, x30, [sp], 16
	ret
.L2857:
	mov	w0, 0
	ret
	.size	FtlDeInit, .-FtlDeInit
	.section	.text.ftl_deinit,"ax",@progbits
	.align	2
	.global	ftl_deinit
	.type	ftl_deinit, %function
ftl_deinit:
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
	bl	ftl_flash_de_init
	bl	FtlDeInit
	ldp	x29, x30, [sp], 16
	b	ftl_flash_de_init
	.size	ftl_deinit, .-ftl_deinit
	.section	.text.rk_ftl_de_init,"ax",@progbits
	.align	2
	.global	rk_ftl_de_init
	.type	rk_ftl_de_init, %function
rk_ftl_de_init:
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
	bl	FlashDeInit
	bl	FtlDeInit
	ldp	x29, x30, [sp], 16
	b	FlashDeInit
	.size	rk_ftl_de_init, .-rk_ftl_de_init
	.section	.text.ftl_cache_flush,"ax",@progbits
	.align	2
	.global	ftl_cache_flush
	.type	ftl_cache_flush, %function
ftl_cache_flush:
	b	FtlCacheWriteBack
	.size	ftl_cache_flush, .-ftl_cache_flush
	.section	.text.ftl_discard,"ax",@progbits
	.align	2
	.global	ftl_discard
	.type	ftl_discard, %function
ftl_discard:
	adrp	x0, .LANCHOR68
	ldr	w0, [x0, #:lo12:.LANCHOR68]
	cmp	w0, w1
	bls	.L2873
	stp	x29, x30, [sp, -80]!
	cmp	w0, w2
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w19, w2
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	bcc	.L2875
	mov	w20, w1
	add	w1, w1, w2
	cmp	w0, w1
	bcc	.L2875
	cmp	w2, 31
	bhi	.L2867
.L2886:
	mov	w0, 0
.L2865:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
.L2867:
	adrp	x0, .LANCHOR78
	ldr	w0, [x0, #:lo12:.LANCHOR78]
	cbnz	w0, .L2886
	adrp	x22, .LANCHOR55
	bl	FtlCacheWriteBack
	ldrh	w0, [x22, #:lo12:.LANCHOR55]
	udiv	w21, w20, w0
	msub	w20, w0, w21, w20
	ands	w20, w20, 65535
	beq	.L2869
	sub	w20, w0, w20
	add	w21, w21, 1
	cmp	w20, w19
	csel	w20, w20, w19, ls
	sub	w19, w19, w20, uxth
.L2869:
	adrp	x20, .LANCHOR253
	adrp	x23, .LANCHOR168
	add	x20, x20, :lo12:.LANCHOR253
	add	x23, x23, :lo12:.LANCHOR168
	mov	w0, -1
	str	w0, [x29, 76]
.L2870:
	ldrh	w0, [x22, #:lo12:.LANCHOR55]
	cmp	w19, w0
	bcs	.L2872
	adrp	x0, .LANCHOR253
	ldr	w1, [x0, #:lo12:.LANCHOR253]
	cmp	w1, 32
	bls	.L2886
	str	wzr, [x0, #:lo12:.LANCHOR253]
	bl	l2p_flush
	bl	FtlVpcTblFlush
	b	.L2886
.L2872:
	mov	w2, 0
	add	x1, x29, 72
	mov	w0, w21
	bl	log2phys
	ldr	w0, [x29, 72]
	cmn	w0, #1
	beq	.L2871
	ldr	w0, [x20]
	mov	w2, 1
	add	x1, x29, 76
	add	w0, w0, 1
	str	w0, [x20]
	ldr	w0, [x23]
	add	w0, w0, 1
	str	w0, [x23]
	mov	w0, w21
	bl	log2phys
	ldr	w0, [x29, 72]
	lsr	w0, w0, 10
	bl	P2V_block_in_plane
	bl	decrement_vpc_count
.L2871:
	ldrh	w0, [x22, #:lo12:.LANCHOR55]
	add	w21, w21, 1
	sub	w19, w19, w0
	b	.L2870
.L2873:
	mov	w0, -1
	ret
.L2875:
	mov	w0, -1
	b	.L2865
	.size	ftl_discard, .-ftl_discard
	.section	.text.FtlRead,"ax",@progbits
	.align	2
	.global	FtlRead
	.type	FtlRead, %function
FtlRead:
	sub	sp, sp, #208
	adrp	x4, .LANCHOR247
	stp	x29, x30, [sp, 16]
	add	x29, sp, 16
	ldr	w4, [x4, #:lo12:.LANCHOR247]
	stp	x19, x20, [sp, 32]
	stp	x21, x22, [sp, 48]
	cmp	w4, 1
	stp	x23, x24, [sp, 64]
	stp	x25, x26, [sp, 80]
	stp	x27, x28, [sp, 96]
	bne	.L2914
	mov	x21, x3
	mov	w23, w2
	mov	w19, w1
	cmp	w0, 16
	bne	.L2889
	mov	x2, x3
	mov	w1, w23
	add	w0, w19, 256
	bl	FtlVendorPartRead
	mov	w25, w0
.L2887:
	mov	w0, w25
	ldp	x19, x20, [sp, 32]
	ldp	x21, x22, [sp, 48]
	ldp	x23, x24, [sp, 64]
	ldp	x25, x26, [sp, 80]
	ldp	x27, x28, [sp, 96]
	ldp	x29, x30, [sp, 16]
	add	sp, sp, 208
	ret
.L2889:
	adrp	x0, .LANCHOR68
	ldr	w0, [x0, #:lo12:.LANCHOR68]
	cmp	w1, w0
	bcs	.L2914
	cmp	w2, w0
	bhi	.L2914
	add	w1, w1, w2
	str	w1, [x29, 148]
	cmp	w0, w1
	bcc	.L2914
	adrp	x22, .LANCHOR55
	ldrh	w0, [x22, #:lo12:.LANCHOR55]
	udiv	w1, w19, w0
	str	w1, [x29, 172]
	add	w1, w19, w2
	sub	w1, w1, #1
	udiv	w0, w1, w0
	adrp	x1, .LANCHOR226
	str	w0, [x29, 168]
	ldr	w0, [x29, 172]
	sub	w4, w4, w0
	ldr	w0, [x29, 168]
	add	w0, w4, w0
	str	w0, [x29, 164]
	ldr	w0, [x1, #:lo12:.LANCHOR226]
	add	w0, w0, w2
	str	w0, [x1, #:lo12:.LANCHOR226]
	adrp	x1, .LANCHOR171
	ldr	w2, [x29, 164]
	ldr	w0, [x1, #:lo12:.LANCHOR171]
	add	w0, w0, w2
	str	w0, [x1, #:lo12:.LANCHOR171]
	ldp	w1, w0, [x29, 168]
	bl	FtlCacheMetchLpa
	cbz	w0, .L2890
	bl	FtlCacheWriteBack
.L2890:
	ldr	w20, [x29, 172]
	adrp	x26, .LANCHOR141
	add	x26, x26, :lo12:.LANCHOR141
	mov	w24, 0
	mov	w25, 0
	adrp	x27, .LANCHOR186
	stp	wzr, wzr, [x29, 156]
.L2891:
	ldr	w0, [x29, 164]
	cbnz	w0, .L2910
	adrp	x0, .LANCHOR119
	ldrh	w0, [x0, #:lo12:.LANCHOR119]
	cbz	w0, .L2887
	mov	w1, 1
	mov	w0, 0
	bl	ftl_do_gc
	b	.L2887
.L2910:
	add	x1, x29, 188
	mov	w2, 0
	mov	w0, w20
	bl	log2phys
	ldr	w1, [x29, 188]
	cmn	w1, #1
	bne	.L2892
	add	x3, x22, :lo12:.LANCHOR55
	mov	w28, 0
.L2893:
	ldrh	w0, [x3]
	cmp	w28, w0
	bcc	.L2895
.L2896:
	ldr	w0, [x29, 164]
	add	w20, w20, 1
	subs	w0, w0, #1
	str	w0, [x29, 164]
	beq	.L2900
	adrp	x0, .LANCHOR38
	ldrh	w0, [x0, #:lo12:.LANCHOR38]
	cmp	w24, w0, lsl 2
	bne	.L2891
.L2900:
	cbz	w24, .L2891
	ldr	x0, [x27, #:lo12:.LANCHOR186]
	mov	w1, w24
	mov	w2, 0
	adrp	x28, .LANCHOR194
	bl	FlashReadPages
	ldr	w0, [x29, 156]
	lsl	w0, w0, 9
	str	w0, [x29, 132]
	ldr	w0, [x29, 152]
	lsl	w0, w0, 9
	str	x0, [x29, 136]
	ldr	w0, [x29, 160]
	lsl	w0, w0, 9
	str	w0, [x29, 144]
	mov	w0, 56
	umull	x0, w24, w0
	mov	x24, 0
	str	x0, [x29, 120]
	adrp	x0, .LC68
	add	x0, x0, :lo12:.LC68
	str	x0, [x29, 112]
.L2909:
	ldr	x0, [x27, #:lo12:.LANCHOR186]
	ldr	w2, [x29, 172]
	add	x0, x0, x24
	ldr	w1, [x0, 24]
	cmp	w2, w1
	bne	.L2902
	ldr	x1, [x0, 8]
	adrp	x0, .LANCHOR193
	ldr	x0, [x0, #:lo12:.LANCHOR193]
	cmp	x1, x0
	bne	.L2903
	ldr	x0, [x29, 136]
	ldr	w2, [x29, 144]
	add	x1, x1, x0
	mov	x0, x21
.L2931:
	bl	ftl_memcpy
.L2903:
	ldr	x0, [x27, #:lo12:.LANCHOR186]
	add	x2, x0, x24
	ldr	w1, [x0, x24]
	cmn	w1, #1
	bne	.L2904
	ldr	w0, [x26, 72]
	mov	w25, w1
	add	w0, w0, 1
	str	w0, [x26, 72]
.L2904:
	ldr	x0, [x2, 16]
	ldr	w1, [x2, 24]
	ldr	w3, [x0, 8]
	cmp	w1, w3
	beq	.L2905
	ldr	w3, [x26, 72]
	add	w3, w3, 1
	str	w3, [x26, 72]
	ldr	x3, [x2, 8]
	ldr	w4, [x3, 4]
	str	w4, [sp]
	ldp	w4, w5, [x0, 4]
	ldr	w6, [x0, 12]
	ldr	w7, [x3]
	ldr	w2, [x2, 4]
	ldr	w3, [x0]
	ldr	x0, [x29, 112]
	bl	printf
.L2905:
	ldr	x0, [x27, #:lo12:.LANCHOR186]
	add	x1, x0, x24
	ldr	w0, [x0, x24]
	cmp	w0, 256
	bne	.L2906
	ldr	w0, [x1, 4]
	lsr	w0, w0, 10
	bl	P2V_block_in_plane
	and	w1, w0, 65535
	str	w1, [x29, 128]
	bl	FtlGcRefreshBlock
	adrp	x2, .LANCHOR78
	add	x2, x2, :lo12:.LANCHOR78
	adrp	x3, .LANCHOR213
.L2908:
	mov	w1, 1
	stp	x3, x2, [x29, 96]
	mov	w0, w1
	bl	ftl_do_gc
	ldr	x2, [x29, 104]
	ldr	w0, [x2]
	cbnz	w0, .L2907
	ldr	x3, [x29, 96]
	ldr	w1, [x29, 128]
	ldrh	w0, [x3, #:lo12:.LANCHOR213]
	cmp	w0, w1
	beq	.L2908
.L2907:
	bl	FtlSysFlush
.L2906:
	ldr	x0, [x29, 120]
	add	x24, x24, 56
	cmp	x0, x24
	bne	.L2909
	mov	w24, 0
	b	.L2891
.L2895:
	madd	w0, w20, w0, w28
	cmp	w19, w0
	bhi	.L2894
	ldr	w1, [x29, 148]
	cmp	w1, w0
	bls	.L2894
	sub	w0, w0, w19
	str	x3, [x29, 136]
	lsl	w0, w0, 9
	mov	w2, 512
	mov	w1, 0
	add	x0, x21, x0
	bl	ftl_memset
	ldr	x3, [x29, 136]
.L2894:
	add	w28, w28, 1
	b	.L2893
.L2892:
	ldr	x0, [x27, #:lo12:.LANCHOR186]
	mov	w2, 56
	umaddl	x0, w24, w2, x0
	str	w1, [x0, 4]
	ldr	w1, [x29, 172]
	cmp	w20, w1
	bne	.L2897
	adrp	x1, .LANCHOR193
	ldr	x1, [x1, #:lo12:.LANCHOR193]
	str	x1, [x0, 8]
	ldrh	w1, [x22, #:lo12:.LANCHOR55]
	udiv	w2, w19, w1
	msub	w2, w2, w1, w19
	str	w2, [x29, 152]
	sub	w2, w1, w2
	cmp	w23, w2
	csel	w2, w23, w2, ls
	str	w2, [x29, 160]
	cmp	w2, w1
	bne	.L2898
	str	x21, [x0, 8]
.L2898:
	adrp	x1, .LANCHOR58
	adrp	x2, .LANCHOR196
	str	w20, [x0, 24]
	ldrh	w1, [x1, #:lo12:.LANCHOR58]
	ldr	x2, [x2, #:lo12:.LANCHOR196]
	mul	w1, w1, w24
	add	w24, w24, 1
	and	x1, x1, 4294967292
	add	x1, x2, x1
	str	x1, [x0, 16]
	b	.L2896
.L2897:
	ldr	w1, [x29, 168]
	cmp	w20, w1
	bne	.L2899
	ldrh	w2, [x22, #:lo12:.LANCHOR55]
	adrp	x1, .LANCHOR194
	ldr	w3, [x29, 148]
	ldr	x1, [x1, #:lo12:.LANCHOR194]
	str	x1, [x0, 8]
	mul	w1, w20, w2
	sub	w3, w3, w1
	str	w3, [x29, 156]
	cmp	w2, w3
	bne	.L2898
.L2930:
	sub	w1, w1, w19
	lsl	w1, w1, 9
	add	x1, x21, x1
	str	x1, [x0, 8]
	b	.L2898
.L2899:
	ldrh	w1, [x22, #:lo12:.LANCHOR55]
	mul	w1, w1, w20
	b	.L2930
.L2902:
	ldr	w2, [x29, 168]
	cmp	w2, w1
	bne	.L2903
	ldr	x1, [x0, 8]
	ldr	x0, [x28, #:lo12:.LANCHOR194]
	cmp	x1, x0
	bne	.L2903
	ldrh	w0, [x22, #:lo12:.LANCHOR55]
	mul	w0, w0, w2
	ldr	w2, [x29, 132]
	sub	w0, w0, w19
	lsl	w0, w0, 9
	add	x0, x21, x0
	b	.L2931
.L2914:
	mov	w25, -1
	b	.L2887
	.size	FtlRead, .-FtlRead
	.section	.text.ftl_vendor_read,"ax",@progbits
	.align	2
	.global	ftl_vendor_read
	.type	ftl_vendor_read, %function
ftl_vendor_read:
	mov	x3, x2
	mov	w2, w1
	mov	w1, w0
	mov	w0, 16
	b	FtlRead
	.size	ftl_vendor_read, .-ftl_vendor_read
	.section	.text.ftl_sys_read,"ax",@progbits
	.align	2
	.global	ftl_sys_read
	.type	ftl_sys_read, %function
ftl_sys_read:
	mov	x3, x2
	mov	w2, w1
	add	w1, w0, 256
	mov	w0, 16
	b	FtlRead
	.size	ftl_sys_read, .-ftl_sys_read
	.section	.text.StorageSysDataLoad,"ax",@progbits
	.align	2
	.global	StorageSysDataLoad
	.type	StorageSysDataLoad, %function
StorageSysDataLoad:
	stp	x29, x30, [sp, -32]!
	mov	x2, 512
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x1
	mov	w20, w0
	mov	w1, 0
	mov	x0, x19
	bl	memset
	mov	x3, x19
	add	w1, w20, 256
	ldp	x19, x20, [sp, 16]
	mov	w2, 1
	ldp	x29, x30, [sp], 32
	mov	w0, 16
	b	FtlRead
	.size	StorageSysDataLoad, .-StorageSysDataLoad
	.section	.text.FlashBootVendorRead,"ax",@progbits
	.align	2
	.global	FlashBootVendorRead
	.type	FlashBootVendorRead, %function
FlashBootVendorRead:
	mov	x3, x2
	mov	w1, w0
	mov	w2, 1
	mov	w0, 16
	b	FtlRead
	.size	FlashBootVendorRead, .-FlashBootVendorRead
	.section	.text.ftl_read,"ax",@progbits
	.align	2
	.global	ftl_read
	.type	ftl_read, %function
ftl_read:
	and	w0, w0, 255
	b	FtlRead
	.size	ftl_read, .-ftl_read
	.section	.text.FtlInit,"ax",@progbits
	.align	2
	.global	FtlInit
	.type	FtlInit, %function
FtlInit:
	stp	x29, x30, [sp, -64]!
	mov	w0, -1
	adrp	x1, .LC77
	add	x1, x1, :lo12:.LC77
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	adrp	x19, .LANCHOR247
	stp	x21, x22, [sp, 32]
	str	w0, [x19, #:lo12:.LANCHOR247]
	adrp	x0, .LANCHOR254
	stp	x23, x24, [sp, 48]
	str	wzr, [x0, #:lo12:.LANCHOR254]
	adrp	x0, .LANCHOR78
	str	wzr, [x0, #:lo12:.LANCHOR78]
	adrp	x0, .LC7
	add	x0, x0, :lo12:.LC7
	bl	printf
	adrp	x0, .LANCHOR15
	add	x0, x0, :lo12:.LANCHOR15
	bl	FtlConstantsInit
	bl	FtlMemInit
	bl	FtlVariablesInit
	adrp	x0, .LANCHOR39
	ldrh	w0, [x0, #:lo12:.LANCHOR39]
	bl	FtlFreeSysBlkQueueInit
	bl	FtlLoadBbt
	cbz	w0, .L2939
	adrp	x1, .LANCHOR255
	adrp	x0, .LC78
	add	x1, x1, :lo12:.LANCHOR255
	add	x0, x0, :lo12:.LC78
.L2948:
	bl	printf
.L2940:
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
.L2939:
	bl	FtlSysBlkInit
	cbz	w0, .L2941
	adrp	x1, .LANCHOR255
	adrp	x0, .LC79
	add	x1, x1, :lo12:.LANCHOR255
	add	x0, x0, :lo12:.LC79
	b	.L2948
.L2941:
	mov	w1, 1
	str	w1, [x19, #:lo12:.LANCHOR247]
	bl	ftl_do_gc
	adrp	x0, .LANCHOR90
	mov	x22, x0
	ldrh	w23, [x0, #:lo12:.LANCHOR90]
	cmp	w23, 15
	bhi	.L2940
	adrp	x20, .LANCHOR115
	add	x20, x20, :lo12:.LANCHOR115
	mov	w19, 0
	adrp	x24, .LANCHOR213
	mov	w21, 65535
.L2945:
	ldrh	w0, [x24, #:lo12:.LANCHOR213]
	cmp	w0, w21
	bne	.L2943
	ldrh	w0, [x20]
	cmp	w0, w21
	bne	.L2943
	and	w0, w19, 63
	bl	List_get_gc_head_node
	bl	FtlGcRefreshBlock
.L2943:
	mov	w1, 1
	mov	w0, w1
	bl	ftl_do_gc
	mov	w1, 1
	mov	w0, 0
	bl	ftl_do_gc
	ldrh	w1, [x22, #:lo12:.LANCHOR90]
	add	w0, w23, 2
	cmp	w1, w0
	bhi	.L2940
	add	w19, w19, 1
	cmp	w19, 4096
	bne	.L2945
	b	.L2940
	.size	FtlInit, .-FtlInit
	.section	.text.rk_ftl_init,"ax",@progbits
	.align	2
	.global	rk_ftl_init
	.type	rk_ftl_init, %function
rk_ftl_init:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	str	x19, [sp, 16]
	bl	FlashInit
	mov	w19, w0
	cbnz	w0, .L2950
	bl	FtlInit
.L2950:
	bl	idb_init
	mov	w1, w19
	adrp	x0, .LC80
	add	x0, x0, :lo12:.LC80
	bl	printf
	mov	w0, w19
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	rk_ftl_init, .-rk_ftl_init
	.section	.text.ftl_fix_nand_power_lost_error,"ax",@progbits
	.align	2
	.global	ftl_fix_nand_power_lost_error
	.type	ftl_fix_nand_power_lost_error, %function
ftl_fix_nand_power_lost_error:
	adrp	x0, .LANCHOR16
	ldrb	w0, [x0, #:lo12:.LANCHOR16]
	cbz	w0, .L2967
	stp	x29, x30, [sp, -128]!
	add	x29, sp, 0
	str	x25, [sp, 64]
	adrp	x25, .LANCHOR241
	stp	x23, x24, [sp, 48]
	stp	x21, x22, [sp, 32]
	adrp	x21, .LANCHOR85
	ldrh	w23, [x25, #:lo12:.LANCHOR241]
	ldr	x0, [x21, #:lo12:.LANCHOR85]
	mov	w1, w23
	stp	x19, x20, [sp, 16]
	ubfiz	x24, x23, 1, 16
	adrp	x19, .LC81
	ldrh	w2, [x0, x24]
	add	x0, x19, :lo12:.LC81
	bl	printf
	adrp	x0, .LANCHOR93
	add	x11, x0, :lo12:.LANCHOR93
	ldrh	w0, [x0, #:lo12:.LANCHOR93]
	bl	FtlGcRefreshOpenBlock
	adrp	x0, .LANCHOR94
	add	x20, x0, :lo12:.LANCHOR94
	ldrh	w0, [x0, #:lo12:.LANCHOR94]
	bl	FtlGcRefreshOpenBlock
	mov	x0, x11
	bl	allocate_new_data_superblock
	mov	x0, x20
	mov	w20, 4097
	bl	allocate_new_data_superblock
.L2954:
	subs	w20, w20, #1
	beq	.L2958
	mov	w1, 1
	mov	w0, w1
	bl	ftl_do_gc
	ldr	x0, [x21, #:lo12:.LANCHOR85]
	ldrh	w0, [x0, x24]
	cbnz	w0, .L2954
.L2958:
	ldr	x0, [x21, #:lo12:.LANCHOR85]
	mov	w1, w23
	ldrh	w2, [x0, x24]
	add	x0, x19, :lo12:.LC81
	bl	printf
	ldr	x0, [x21, #:lo12:.LANCHOR85]
	ldrh	w19, [x0, x24]
	cbnz	w19, .L2956
	add	x20, x29, 128
	adrp	x22, .LANCHOR79
	strh	w23, [x20, -48]!
	mov	x0, x20
	bl	make_superblock
	adrp	x0, .LANCHOR38
	ldr	x4, [x22, #:lo12:.LANCHOR79]
	add	x20, x20, 16
	mov	w5, 65535
	ldrh	w3, [x0, #:lo12:.LANCHOR38]
	mov	w6, 56
	mov	w0, 0
.L2959:
	cmp	w0, w3
	bne	.L2961
	ldr	x0, [x21, #:lo12:.LANCHOR85]
	mov	w1, w23
	ldrh	w2, [x0, x24]
	adrp	x0, .LC82
	add	x0, x0, :lo12:.LC82
	bl	printf
	ldr	x0, [x22, #:lo12:.LANCHOR79]
	mov	w2, w19
	mov	w1, 0
	bl	FlashEraseBlocks
	ldr	x0, [x22, #:lo12:.LANCHOR79]
	mov	w2, w19
	mov	w1, 1
	bl	FlashEraseBlocks
.L2956:
	mov	w0, -1
	strh	w0, [x25, #:lo12:.LANCHOR241]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldr	x25, [sp, 64]
	ldp	x29, x30, [sp], 128
	ret
.L2961:
	ldrh	w1, [x20]
	cmp	w1, w5
	beq	.L2960
	umaddl	x2, w19, w6, x4
	add	w19, w19, 1
	and	w19, w19, 65535
	lsl	w1, w1, 10
	stp	xzr, xzr, [x2, 8]
	str	w1, [x2, 4]
.L2960:
	add	w0, w0, 1
	add	x20, x20, 2
	and	w0, w0, 65535
	b	.L2959
.L2967:
	ret
	.size	ftl_fix_nand_power_lost_error, .-ftl_fix_nand_power_lost_error
	.section	.text.FtlWrite,"ax",@progbits
	.align	2
	.global	FtlWrite
	.type	FtlWrite, %function
FtlWrite:
	stp	x29, x30, [sp, -256]!
	add	x29, sp, 0
	stp	x21, x22, [sp, 32]
	mov	w22, w1
	adrp	x1, .LANCHOR78
	stp	x25, x26, [sp, 64]
	mov	w25, w2
	stp	x19, x20, [sp, 16]
	ldr	w2, [x1, #:lo12:.LANCHOR78]
	stp	x23, x24, [sp, 48]
	stp	x27, x28, [sp, 80]
	str	x1, [x29, 120]
	cbnz	w2, .L3013
	adrp	x1, .LANCHOR247
	ldr	w1, [x1, #:lo12:.LANCHOR247]
	cmp	w1, 1
	bne	.L3013
	mov	x23, x3
	cmp	w0, 16
	bne	.L2972
	mov	x2, x3
	mov	w1, w25
	add	w0, w22, 256
	bl	FtlVendorPartWrite
.L2970:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 256
	ret
.L2972:
	adrp	x0, .LANCHOR68
	ldr	w1, [x0, #:lo12:.LANCHOR68]
	cmp	w22, w1
	bcs	.L3016
	cmp	w25, w1
	bhi	.L3016
	add	w0, w22, w25
	cmp	w1, w0
	bcc	.L3016
	adrp	x1, .LANCHOR256
	adrp	x3, .LANCHOR55
	mov	w2, 2048
	sub	w0, w0, #1
	str	w2, [x1, #:lo12:.LANCHOR256]
	adrp	x2, .LANCHOR167
	ldrh	w1, [x3, #:lo12:.LANCHOR55]
	adrp	x21, .LANCHOR72
	str	x3, [x29, 184]
	cmp	w25, w1, lsl 1
	udiv	w0, w0, w1
	udiv	w26, w22, w1
	str	w0, [x29, 172]
	sub	w27, w0, w26
	ldr	w0, [x2, #:lo12:.LANCHOR167]
	add	w24, w27, 1
	add	w0, w0, w24
	str	w0, [x2, #:lo12:.LANCHOR167]
	adrp	x2, .LANCHOR225
	ldr	w0, [x2, #:lo12:.LANCHOR225]
	add	w0, w0, w25
	str	w0, [x2, #:lo12:.LANCHOR225]
	ldr	w2, [x21, #:lo12:.LANCHOR72]
	cset	w0, cs
	str	w0, [x29, 176]
	cbz	w2, .L2974
	adrp	x0, .LANCHOR73
	sub	w2, w2, #1
	mov	w3, 56
	adrp	x20, .LANCHOR257
	ldr	x0, [x0, #:lo12:.LANCHOR73]
	umaddl	x2, w2, w3, x0
	ldr	w0, [x2, 24]
	cmp	w26, w0
	bne	.L2975
	adrp	x3, .LANCHOR169
	ldr	w0, [x3, #:lo12:.LANCHOR169]
	add	w0, w0, 1
	str	w0, [x3, #:lo12:.LANCHOR169]
	ldr	w0, [x20, #:lo12:.LANCHOR257]
	ldr	x3, [x2, 8]
	add	w0, w0, 1
	str	w0, [x20, #:lo12:.LANCHOR257]
	msub	w0, w26, w1, w22
	sub	w1, w1, w0
	cmp	w25, w1
	lsl	w0, w0, 9
	csel	w19, w25, w1, ls
	add	x0, x3, x0
	lsl	w24, w19, 9
	mov	x1, x23
	mov	w2, w24
	bl	ftl_memcpy
	cbnz	w27, .L2976
	ldr	w0, [x20, #:lo12:.LANCHOR257]
	cmp	w0, 2
	bgt	.L2976
.L3013:
	mov	w0, 0
	b	.L2970
.L2976:
	add	x23, x23, x24
	sub	w25, w25, w19
	add	w22, w22, w19
	add	w26, w26, 1
	mov	w24, w27
.L2975:
	str	wzr, [x20, #:lo12:.LANCHOR257]
.L2974:
	ldr	w1, [x29, 172]
	mov	w0, w26
	bl	FtlCacheMetchLpa
	cbz	w0, .L2977
	bl	FtlCacheWriteBack
.L2977:
	adrp	x0, .LANCHOR252
	mov	w20, w26
	adrp	x27, .LANCHOR93
	str	x0, [x29, 112]
	add	x1, x27, :lo12:.LANCHOR93
	str	x1, [x0, #:lo12:.LANCHOR252]
	adrp	x0, .LANCHOR57
	add	x0, x0, :lo12:.LANCHOR57
	str	x0, [x29, 136]
.L2978:
	cbnz	w24, .L3007
	bl	FtlCacheWriteBack
	ldr	w0, [x29, 172]
	sub	w1, w0, w26
	mov	w0, 0
	bl	ftl_do_gc
	adrp	x1, .LANCHOR90
	mov	x22, x1
	ldrh	w0, [x1, #:lo12:.LANCHOR90]
	cmp	w0, 5
	bls	.L3008
	cmp	w0, 31
	bhi	.L3013
	adrp	x0, .LANCHOR2
	ldrb	w0, [x0, #:lo12:.LANCHOR2]
	cbnz	w0, .L3013
.L3008:
	adrp	x20, .LANCHOR115
	adrp	x21, .LANCHOR116
	adrp	x19, .LANCHOR182
	add	x20, x20, :lo12:.LANCHOR115
	add	x21, x21, :lo12:.LANCHOR116
	add	x19, x19, :lo12:.LANCHOR182
.L3011:
	adrp	x0, .LANCHOR213
	ldrh	w1, [x0, #:lo12:.LANCHOR213]
	mov	w0, 65535
	cmp	w1, w0
	bne	.L3010
	ldrh	w0, [x20]
	cmp	w0, w1
	bne	.L3010
	ldrh	w1, [x21]
	cmp	w1, w0
	bne	.L3010
	and	w0, w24, 7
	bl	List_get_gc_head_node
	bl	FtlGcRefreshBlock
.L3010:
	adrp	x1, .LANCHOR181
	mov	w0, 128
	strh	w0, [x19]
	strh	w0, [x1, #:lo12:.LANCHOR181]
	mov	w1, 1
	mov	w0, w1
	bl	ftl_do_gc
	mov	w1, 1
	mov	w0, 0
	bl	ftl_do_gc
	ldr	x0, [x29, 120]
	ldr	w0, [x0, #:lo12:.LANCHOR78]
	cbnz	w0, .L3013
	ldrh	w0, [x22, #:lo12:.LANCHOR90]
	cmp	w0, 2
	bhi	.L3013
	add	w24, w24, 1
	cmp	w24, 256
	bne	.L3011
	b	.L3013
.L3007:
	add	x0, x27, :lo12:.LANCHOR93
	adrp	x1, .LANCHOR38
	str	x1, [x29, 144]
	ldrb	w2, [x0, 6]
	ldrh	w0, [x1, #:lo12:.LANCHOR38]
	cmp	w2, w0
	bcc	.L2979
	mov	w2, 1472
	adrp	x1, .LANCHOR258
	adrp	x0, .LC5
	add	x1, x1, :lo12:.LANCHOR258
	add	x0, x0, :lo12:.LC5
	bl	printf
	adrp	x1, .LC6
	adrp	x0, .LC7
	add	x1, x1, :lo12:.LC6
	add	x0, x0, :lo12:.LC7
	bl	printf
.L2979:
	add	x19, x27, :lo12:.LANCHOR93
	ldrh	w0, [x19, 4]
	cbnz	w0, .L2980
	mov	x0, x19
	bl	allocate_new_data_superblock
	ldr	x0, [x29, 112]
	str	x19, [x0, #:lo12:.LANCHOR252]
.L2980:
	adrp	x1, .LANCHOR185
	ldr	w2, [x21, #:lo12:.LANCHOR72]
	str	x1, [x29, 104]
	ldr	w0, [x1, #:lo12:.LANCHOR185]
	sub	w0, w0, w2
	add	x2, x27, :lo12:.LANCHOR93
	ldrh	w3, [x2, 4]
	ldrb	w2, [x2, 6]
	cmp	w0, w3
	csel	w0, w0, w3, ls
	cmp	w0, w24
	csel	w0, w0, w24, ls
	str	w0, [x29, 132]
	ldr	x0, [x29, 144]
	ldrh	w0, [x0, #:lo12:.LANCHOR38]
	cmp	w2, w0
	bcc	.L2981
	mov	w2, 1515
	adrp	x1, .LANCHOR258
	adrp	x0, .LC5
	add	x1, x1, :lo12:.LANCHOR258
	add	x0, x0, :lo12:.LC5
	bl	printf
	adrp	x1, .LC6
	adrp	x0, .LC7
	add	x1, x1, :lo12:.LC6
	add	x0, x0, :lo12:.LC7
	bl	printf
.L2981:
	str	wzr, [x29, 180]
.L2982:
	ldr	w1, [x29, 132]
	ldr	w0, [x29, 180]
	cmp	w0, w1
	bne	.L3002
.L2983:
	ldr	w0, [x29, 180]
	cmp	w24, w0
	bcs	.L3003
	mov	w2, 1609
	adrp	x1, .LANCHOR258
	adrp	x0, .LC5
	add	x1, x1, :lo12:.LANCHOR258
	add	x0, x0, :lo12:.LC5
	bl	printf
	adrp	x1, .LC6
	adrp	x0, .LC7
	add	x1, x1, :lo12:.LC6
	add	x0, x0, :lo12:.LC7
	bl	printf
.L3003:
	ldr	w0, [x29, 180]
	ldr	w1, [x21, #:lo12:.LANCHOR72]
	sub	w24, w24, w0
	ldr	x0, [x29, 104]
	ldr	w0, [x0, #:lo12:.LANCHOR185]
	cmp	w1, w0
	bcs	.L3004
	ldr	w0, [x29, 176]
	cbnz	w0, .L3004
	add	x0, x27, :lo12:.LANCHOR93
	ldrh	w0, [x0, 4]
	cbz	w0, .L3004
.L3006:
	str	wzr, [x29, 176]
	b	.L2978
.L3002:
	add	x0, x27, :lo12:.LANCHOR93
	ldrh	w0, [x0, 4]
	cbz	w0, .L2983
	ldr	w0, [x29, 172]
	cmp	w0, w20
	ldr	w0, [x29, 176]
	cset	w3, eq
	tst	w3, w0
	beq	.L2984
	ldr	w0, [x29, 180]
	cbz	w0, .L2984
	ldr	x0, [x29, 184]
	ldrh	w1, [x0, #:lo12:.LANCHOR55]
	add	w0, w22, w25
	msub	w0, w20, w1, w0
	cmp	w1, w0
	bne	.L2983
.L2984:
	add	x1, x29, 196
	mov	w2, 0
	str	w3, [x29, 96]
	adrp	x19, .LANCHOR73
	mov	w0, w20
	bl	log2phys
	add	x0, x27, :lo12:.LANCHOR93
	bl	get_new_active_ppa
	ldr	w5, [x21, #:lo12:.LANCHOR72]
	mov	w4, 56
	ldr	x1, [x19, #:lo12:.LANCHOR73]
	str	w4, [x29, 168]
	nop // between mem op and mult-accumulate
	umaddl	x1, w5, w4, x1
	str	w0, [x1, 4]
	adrp	x0, .LANCHOR58
	str	w20, [x1, 24]
	ldrh	w2, [x0, #:lo12:.LANCHOR58]
	mul	w0, w5, w2
	and	x0, x0, 4294967292
	str	x0, [x29, 160]
	adrp	x0, .LANCHOR197
	ldr	x3, [x29, 160]
	ldr	x0, [x0, #:lo12:.LANCHOR197]
	str	x0, [x29, 152]
	add	x28, x0, x3
	adrp	x0, .LANCHOR57
	str	x28, [x1, 16]
	ldrh	w0, [x0, #:lo12:.LANCHOR57]
	mul	w0, w0, w5
	adrp	x5, .LANCHOR192
	ldr	x5, [x5, #:lo12:.LANCHOR192]
	and	x0, x0, 4294967292
	add	x0, x5, x0
	str	x0, [x1, 8]
	mov	w1, 0
	mov	x0, x28
	bl	ftl_memset
	ldr	w3, [x29, 96]
	cmp	w26, w20
	cset	w0, eq
	ldr	w4, [x29, 168]
	orr	w0, w3, w0
	mov	x3, x19
	cbz	w0, .L2985
	bne	.L2986
	ldr	x0, [x29, 184]
	ldrh	w19, [x0, #:lo12:.LANCHOR55]
	udiv	w0, w22, w19
	msub	w0, w0, w19, w22
	str	w0, [x29, 168]
	sub	w19, w19, w0
	cmp	w19, w25
	csel	w19, w19, w25, ls
.L2987:
	ldr	x0, [x29, 184]
	ldrh	w0, [x0, #:lo12:.LANCHOR55]
	cmp	w0, w19
	bne	.L2988
	cmp	w26, w20
	beq	.L3019
	mul	w1, w20, w19
	sub	w1, w1, w22
	lsl	w1, w1, 9
	add	x1, x23, x1
.L2989:
	ldr	w0, [x29, 176]
	cbz	w0, .L2990
	ldr	x2, [x3, #:lo12:.LANCHOR73]
	mov	w3, 56
	ldr	w0, [x21, #:lo12:.LANCHOR72]
	umaddl	x0, w0, w3, x2
	str	x1, [x0, 8]
.L2991:
	add	x0, x27, :lo12:.LANCHOR93
	ldrb	w1, [x0, 6]
	ldr	x0, [x29, 144]
	ldrh	w0, [x0, #:lo12:.LANCHOR38]
	cmp	w1, w0
	bcc	.L2999
	mov	w2, 1599
	adrp	x1, .LANCHOR258
	adrp	x0, .LC5
	add	x1, x1, :lo12:.LANCHOR258
	add	x0, x0, :lo12:.LC5
	bl	printf
	adrp	x1, .LC6
	adrp	x0, .LC7
	add	x1, x1, :lo12:.LC6
	add	x0, x0, :lo12:.LC7
	bl	printf
.L2999:
	ldp	x1, x2, [x29, 152]
	mov	w0, -3947
	strh	w0, [x1, x2]
	adrp	x1, .LANCHOR165
	ldr	w0, [x1, #:lo12:.LANCHOR165]
	stp	w0, w20, [x28, 4]
	add	w20, w20, 1
	add	w0, w0, 1
	cmn	w0, #1
	csel	w0, w0, wzr, ne
	str	w0, [x1, #:lo12:.LANCHOR165]
	ldr	w0, [x29, 196]
	str	w0, [x28, 12]
	ldrh	w0, [x27, #:lo12:.LANCHOR93]
	strh	w0, [x28, 2]
	ldr	w0, [x21, #:lo12:.LANCHOR72]
	add	w0, w0, 1
	str	w0, [x21, #:lo12:.LANCHOR72]
	ldr	w0, [x29, 180]
	add	w0, w0, 1
	str	w0, [x29, 180]
	b	.L2982
.L2986:
	ldr	x0, [x29, 184]
	add	w19, w22, w25
	str	wzr, [x29, 168]
	ldrh	w0, [x0, #:lo12:.LANCHOR55]
	msub	w19, w20, w0, w19
	and	w19, w19, 65535
	b	.L2987
.L3019:
	mov	x1, x23
	b	.L2989
.L2990:
	ldr	x2, [x3, #:lo12:.LANCHOR73]
	mov	w3, 56
	ldr	w0, [x21, #:lo12:.LANCHOR72]
	umaddl	x0, w0, w3, x2
	ldr	x2, [x29, 136]
	ldrh	w2, [x2]
.L3039:
	ldr	x0, [x0, 8]
	b	.L3038
.L2988:
	ldr	w0, [x29, 196]
	cmn	w0, #1
	beq	.L2992
	ldr	x1, [x3, #:lo12:.LANCHOR73]
	mov	w2, 56
	str	w0, [x29, 204]
	ldr	w0, [x21, #:lo12:.LANCHOR72]
	str	x3, [x29, 96]
	str	w20, [x29, 224]
	nop // between mem op and mult-accumulate
	umaddl	x0, w0, w2, x1
	mov	w2, 0
	ldp	x1, x0, [x0, 8]
	stp	x1, x0, [x29, 208]
	mov	w1, 1
	add	x0, x29, 200
	bl	FlashReadPages
	ldr	w0, [x29, 200]
	ldr	x3, [x29, 96]
	cmn	w0, #1
	bne	.L2993
	adrp	x0, .LANCHOR141
	add	x0, x0, :lo12:.LANCHOR141
	ldr	w1, [x0, 72]
	add	w1, w1, 1
	str	w1, [x0, 72]
.L2996:
	cmp	w26, w20
	lsl	w2, w19, 9
	bne	.L2997
	ldr	x0, [x3, #:lo12:.LANCHOR73]
	mov	w3, 56
	ldr	w1, [x21, #:lo12:.LANCHOR72]
	umaddl	x1, w1, w3, x0
	ldr	w0, [x29, 168]
	lsl	w0, w0, 9
	ldr	x3, [x1, 8]
	mov	x1, x23
	add	x0, x3, x0
.L3038:
	bl	ftl_memcpy
	b	.L2991
.L2993:
	ldr	w1, [x28, 8]
	cmp	w20, w1
	beq	.L2995
	adrp	x0, .LANCHOR141
	add	x0, x0, :lo12:.LANCHOR141
	str	x3, [x29, 96]
	ldr	w2, [x0, 72]
	add	w2, w2, 1
	str	w2, [x0, 72]
	mov	w2, w20
	adrp	x0, .LC83
	add	x0, x0, :lo12:.LC83
	bl	printf
	ldr	x3, [x29, 96]
.L2995:
	ldr	w0, [x28, 8]
	cmp	w20, w0
	beq	.L2996
	mov	w2, 1581
	adrp	x1, .LANCHOR258
	adrp	x0, .LC5
	add	x1, x1, :lo12:.LANCHOR258
	add	x0, x0, :lo12:.LC5
	str	x3, [x29, 96]
	bl	printf
	adrp	x1, .LC6
	adrp	x0, .LC7
	add	x1, x1, :lo12:.LC6
	add	x0, x0, :lo12:.LC7
	bl	printf
.L3037:
	ldr	x3, [x29, 96]
	b	.L2996
.L2992:
	ldr	x1, [x3, #:lo12:.LANCHOR73]
	mov	w2, 56
	ldr	w0, [x21, #:lo12:.LANCHOR72]
	str	x3, [x29, 96]
	nop // between mem op and mult-accumulate
	umaddl	x0, w0, w2, x1
	ldr	x1, [x29, 136]
	ldr	x0, [x0, 8]
	ldrh	w2, [x1]
	mov	w1, 0
	bl	ftl_memset
	b	.L3037
.L2997:
	ldr	x0, [x29, 184]
	mov	w4, 56
	ldr	x3, [x3, #:lo12:.LANCHOR73]
	ldrh	w1, [x0, #:lo12:.LANCHOR55]
	ldr	w0, [x21, #:lo12:.LANCHOR72]
	mul	w1, w1, w20
	umaddl	x0, w0, w4, x3
	sub	w1, w1, w22
	lsl	w1, w1, 9
	add	x1, x23, x1
	b	.L3039
.L2985:
	ldr	w0, [x29, 176]
	cbz	w0, .L2998
	ldr	w0, [x21, #:lo12:.LANCHOR72]
	ldr	x1, [x19, #:lo12:.LANCHOR73]
	umaddl	x4, w0, w4, x1
	ldr	x0, [x29, 184]
	ldrh	w0, [x0, #:lo12:.LANCHOR55]
	mul	w0, w0, w20
	sub	w0, w0, w22
	lsl	w0, w0, 9
	add	x0, x23, x0
	str	x0, [x4, 8]
	b	.L2991
.L2998:
	ldr	x0, [x29, 184]
	ldr	x2, [x19, #:lo12:.LANCHOR73]
	ldrh	w1, [x0, #:lo12:.LANCHOR55]
	ldr	w0, [x21, #:lo12:.LANCHOR72]
	mul	w1, w1, w20
	umaddl	x4, w0, w4, x2
	adrp	x0, .LANCHOR57
	sub	w1, w1, w22
	lsl	w1, w1, 9
	ldrh	w2, [x0, #:lo12:.LANCHOR57]
	add	x1, x23, x1
	ldr	x0, [x4, 8]
	b	.L3038
.L3004:
	bl	FtlCacheWriteBack
	str	wzr, [x21, #:lo12:.LANCHOR72]
	cmp	w24, 1
	bhi	.L2978
	b	.L3006
.L3016:
	mov	w0, -1
	b	.L2970
	.size	FtlWrite, .-FtlWrite
	.section	.text.ftl_vendor_write,"ax",@progbits
	.align	2
	.global	ftl_vendor_write
	.type	ftl_vendor_write, %function
ftl_vendor_write:
	mov	x3, x2
	mov	w2, w1
	mov	w1, w0
	mov	w0, 16
	b	FtlWrite
	.size	ftl_vendor_write, .-ftl_vendor_write
	.section	.text.ftl_sys_write,"ax",@progbits
	.align	2
	.global	ftl_sys_write
	.type	ftl_sys_write, %function
ftl_sys_write:
	mov	x3, x2
	mov	w2, w1
	add	w1, w0, 256
	mov	w0, 16
	b	FtlWrite
	.size	ftl_sys_write, .-ftl_sys_write
	.section	.text.StorageSysDataStore,"ax",@progbits
	.align	2
	.global	StorageSysDataStore
	.type	StorageSysDataStore, %function
StorageSysDataStore:
	mov	x3, x1
	mov	w2, 1
	add	w1, w0, 256
	mov	w0, 16
	b	FtlWrite
	.size	StorageSysDataStore, .-StorageSysDataStore
	.section	.text.FlashBootVendorWrite,"ax",@progbits
	.align	2
	.global	FlashBootVendorWrite
	.type	FlashBootVendorWrite, %function
FlashBootVendorWrite:
	mov	x3, x2
	mov	w1, w0
	mov	w2, 1
	mov	w0, 16
	b	FtlWrite
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
	bne	.L3045
	mov	w3, w2
	mov	w0, 0
	mov	x2, x20
	bl	idb_write_data
.L3045:
	mov	x3, x20
	mov	w2, w19
	mov	w1, w22
	mov	w0, w21
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 48
	b	FtlWrite
	.size	ftl_write, .-ftl_write
	.section	.text.FtlDumpSysBlock,"ax",@progbits
	.align	2
	.global	FtlDumpSysBlock
	.type	FtlDumpSysBlock, %function
FtlDumpSysBlock:
	sub	sp, sp, #112
	stp	x29, x30, [sp, 16]
	add	x29, sp, 16
	stp	x25, x26, [sp, 80]
	and	w25, w0, 65535
	adrp	x0, .LANCHOR189
	stp	x21, x22, [sp, 48]
	adrp	x21, .LANCHOR211
	add	x1, x21, :lo12:.LANCHOR211
	ldr	x2, [x0, #:lo12:.LANCHOR189]
	adrp	x22, .LANCHOR53
	stp	x23, x24, [sp, 64]
	lsl	w26, w25, 10
	stp	x19, x20, [sp, 32]
	adrp	x23, .LC84
	str	x27, [sp, 96]
	adrp	x24, .LC85
	str	x2, [x1, 8]
	adrp	x2, .LANCHOR195
	add	x22, x22, :lo12:.LANCHOR53
	add	x23, x23, :lo12:.LC84
	ldr	x2, [x2, #:lo12:.LANCHOR195]
	add	x24, x24, :lo12:.LC85
	mov	x27, x0
	mov	w19, 0
	str	x2, [x1, 16]
.L3048:
	ldrh	w0, [x22]
	cmp	w19, w0
	blt	.L3050
	ldp	x19, x20, [sp, 32]
	ldp	x21, x22, [sp, 48]
	ldp	x23, x24, [sp, 64]
	ldp	x25, x26, [sp, 80]
	ldp	x29, x30, [sp, 16]
	ldr	x27, [sp, 96]
	add	sp, sp, 112
	ret
.L3050:
	add	x20, x21, :lo12:.LANCHOR211
	orr	w0, w19, w26
	mov	w2, 1
	mov	w1, w2
	str	w0, [x20, 4]
	mov	x0, x20
	bl	FlashReadPages
	ldp	x1, x0, [x20, 8]
	ldr	w2, [x21, #:lo12:.LANCHOR211]
	ldr	w3, [x20, 4]
	ldr	w1, [x1]
	str	w1, [sp]
	mov	w1, w25
	ldp	w4, w5, [x0]
	ldp	w6, w7, [x0, 8]
	mov	x0, x23
	bl	printf
	ldr	x0, [x20, 16]
	ldr	w0, [x0]
	cmn	w0, #1
	beq	.L3049
	ldr	x1, [x27, #:lo12:.LANCHOR189]
	mov	w3, 768
	mov	w2, 4
	mov	x0, x24
	bl	rknand_print_hex
.L3049:
	add	w19, w19, 1
	sxth	w19, w19
	b	.L3048
	.size	FtlDumpSysBlock, .-FtlDumpSysBlock
	.section	.text.dump_map_info,"ax",@progbits
	.align	2
	.global	dump_map_info
	.type	dump_map_info, %function
dump_map_info:
	sub	sp, sp, #96
	adrp	x0, .LANCHOR40
	stp	x29, x30, [sp, 16]
	add	x29, sp, 16
	stp	x19, x20, [sp, 32]
	ldrh	w20, [x0, #:lo12:.LANCHOR40]
	stp	x23, x24, [sp, 64]
	adrp	x23, .LANCHOR47
	stp	x21, x22, [sp, 48]
	add	x23, x23, :lo12:.LANCHOR47
	adrp	x22, .LANCHOR41
	add	x22, x22, :lo12:.LANCHOR41
	stp	x25, x26, [sp, 80]
	adrp	x24, .LANCHOR38
.L3056:
	ldrh	w0, [x22]
	cmp	w0, w20
	bhi	.L3062
	adrp	x25, .LANCHOR131
	adrp	x19, .LANCHOR211
	add	x25, x25, :lo12:.LANCHOR131
	add	x19, x19, :lo12:.LANCHOR211
	mov	w26, 0
.L3063:
	ldrh	w0, [x25]
	cmp	w26, w0
	bge	.L3066
	adrp	x21, .LANCHOR53
	adrp	x0, .LC51
	sbfiz	x23, x26, 1, 32
	mov	w20, 0
	add	x21, x21, :lo12:.LANCHOR53
	add	x24, x0, :lo12:.LC51
	b	.L3067
.L3058:
	ldrb	w0, [x23, x5]
	mov	w1, w20
	bl	V2P_block
	and	w4, w0, 65535
	bl	FtlBbmIsBadBlock
	cbnz	w0, .L3057
	umaddl	x1, w19, w7, x6
	lsl	w4, w4, 10
	mul	w0, w19, w8
	add	w19, w19, 1
	and	w19, w19, 65535
	asr	w0, w0, 2
	str	w4, [x1, 4]
	add	x0, x10, x0, sxtw 2
	stp	x11, x0, [x1, 8]
.L3057:
	add	x5, x5, 1
.L3064:
	cmp	w12, w5, uxth
	bhi	.L3058
	cbnz	w19, .L3059
.L3061:
	add	w20, w20, 1
	and	w20, w20, 65535
	b	.L3056
.L3059:
	mov	w1, w19
	mov	w2, 1
	mov	x0, x6
	bl	FlashReadPages
	mov	w0, 56
	adrp	x26, .LC86
	add	x26, x26, :lo12:.LC86
	mov	x25, 0
	umull	x19, w19, w0
.L3060:
	ldr	x0, [x21, #:lo12:.LANCHOR186]
	add	x0, x0, x25
	add	x25, x25, 56
	ldr	x1, [x0, 16]
	ldr	w2, [x0, 4]
	ldr	x0, [x0, 8]
	ldr	w3, [x0, 4]
	str	w3, [sp]
	ldr	w7, [x0]
	mov	x0, x26
	ldp	w3, w4, [x1]
	ldp	w5, w6, [x1, 8]
	ubfx	x1, x2, 10, 16
	bl	printf
	cmp	x25, x19
	bne	.L3060
	b	.L3061
.L3062:
	adrp	x0, .LANCHOR107
	adrp	x21, .LANCHOR186
	ldrh	w12, [x24, #:lo12:.LANCHOR38]
	mov	x5, 0
	ldr	x11, [x0, #:lo12:.LANCHOR107]
	adrp	x0, .LANCHOR108
	ldr	x6, [x21, #:lo12:.LANCHOR186]
	mov	w19, 0
	ldr	x10, [x0, #:lo12:.LANCHOR108]
	adrp	x0, .LANCHOR58
	mov	w7, 56
	ldrh	w8, [x0, #:lo12:.LANCHOR58]
	b	.L3064
.L3065:
	adrp	x22, .LANCHOR132
	mov	w2, 1
	mov	w1, w2
	ldr	x0, [x22, #:lo12:.LANCHOR132]
	ldrh	w0, [x0, x23]
	orr	w0, w20, w0, lsl 10
	str	w0, [x19, 4]
	mov	x0, x19
	bl	FlashReadPages
	ldp	x2, x0, [x19, 8]
	add	w20, w20, 1
	ldr	x1, [x22, #:lo12:.LANCHOR132]
	sxth	w20, w20
	ldr	w3, [x2, 4]
	ldrh	w1, [x1, x23]
	str	w3, [sp, 8]
	ldr	w2, [x2]
	str	w2, [sp]
	ldp	w4, w5, [x0]
	ldp	w6, w7, [x0, 8]
	mov	x0, x24
	ldp	w2, w3, [x19]
	bl	printf
.L3067:
	ldrh	w0, [x21]
	cmp	w20, w0
	blt	.L3065
	add	w0, w26, 1
	sxth	w26, w0
	b	.L3063
.L3066:
	adrp	x0, .LANCHOR64
	mov	w2, 2
	adrp	x19, .LANCHOR66
	ldr	w3, [x0, #:lo12:.LANCHOR64]
	adrp	x0, .LANCHOR132
	ldr	x1, [x0, #:lo12:.LANCHOR132]
	adrp	x0, .LC87
	add	x0, x0, :lo12:.LC87
	bl	rknand_print_hex
	adrp	x0, .LANCHOR134
	ldrh	w3, [x19, #:lo12:.LANCHOR66]
	mov	w2, 4
	ldr	x1, [x0, #:lo12:.LANCHOR134]
	adrp	x0, .LC88
	add	x0, x0, :lo12:.LC88
	bl	rknand_print_hex
	adrp	x0, .LANCHOR203
	ldrh	w3, [x19, #:lo12:.LANCHOR66]
	ldp	x21, x22, [sp, 48]
	mov	w2, 4
	ldr	x1, [x0, #:lo12:.LANCHOR203]
	adrp	x0, .LC89
	ldp	x19, x20, [sp, 32]
	add	x0, x0, :lo12:.LC89
	ldp	x23, x24, [sp, 64]
	ldp	x25, x26, [sp, 80]
	ldp	x29, x30, [sp, 16]
	add	sp, sp, 96
	b	rknand_print_hex
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
	.section	.bss.DeviceCapacity,"aw",@nobits
	.align	2
	.set	.LANCHOR60,. + 0
	.type	DeviceCapacity, %object
	.size	DeviceCapacity, 4
DeviceCapacity:
	.zero	4
	.section	.bss.DieAddrs,"aw",@nobits
	.align	2
	.set	.LANCHOR18,. + 0
	.type	DieAddrs, %object
	.size	DieAddrs, 32
DieAddrs:
	.zero	32
	.section	.bss.DieCsIndex,"aw",@nobits
	.align	2
	.set	.LANCHOR27,. + 0
	.type	DieCsIndex, %object
	.size	DieCsIndex, 8
DieCsIndex:
	.zero	8
	.section	.bss.FlashDdrTunningReadCount,"aw",@nobits
	.align	2
	.set	.LANCHOR147,. + 0
	.type	FlashDdrTunningReadCount, %object
	.size	FlashDdrTunningReadCount, 4
FlashDdrTunningReadCount:
	.zero	4
	.section	.bss.FlashWaitBusyScheduleEn,"aw",@nobits
	.align	2
	.type	FlashWaitBusyScheduleEn, %object
	.size	FlashWaitBusyScheduleEn, 4
FlashWaitBusyScheduleEn:
	.zero	4
	.section	.bss.FtlMallocBuffer,"aw",@nobits
	.align	6
	.type	FtlMallocBuffer, %object
	.size	FtlMallocBuffer, 1310720
FtlMallocBuffer:
	.zero	1310720
	.section	.bss.FtlUpdateVaildLpnCount,"aw",@nobits
	.align	1
	.set	.LANCHOR101,. + 0
	.type	FtlUpdateVaildLpnCount, %object
	.size	FtlUpdateVaildLpnCount, 2
FtlUpdateVaildLpnCount:
	.zero	2
	.section	.bss.IDByte,"aw",@nobits
	.align	2
	.set	.LANCHOR22,. + 0
	.type	IDByte, %object
	.size	IDByte, 32
IDByte:
	.zero	32
	.section	.bss.c_ftl_nand_bbm_buf_size,"aw",@nobits
	.align	1
	.set	.LANCHOR126,. + 0
	.type	c_ftl_nand_bbm_buf_size, %object
	.size	c_ftl_nand_bbm_buf_size, 2
c_ftl_nand_bbm_buf_size:
	.zero	2
	.section	.bss.c_ftl_nand_blk_pre_plane,"aw",@nobits
	.align	1
	.set	.LANCHOR41,. + 0
	.type	c_ftl_nand_blk_pre_plane, %object
	.size	c_ftl_nand_blk_pre_plane, 2
c_ftl_nand_blk_pre_plane:
	.zero	2
	.section	.bss.c_ftl_nand_blks_per_die,"aw",@nobits
	.align	1
	.set	.LANCHOR51,. + 0
	.type	c_ftl_nand_blks_per_die, %object
	.size	c_ftl_nand_blks_per_die, 2
c_ftl_nand_blks_per_die:
	.zero	2
	.section	.bss.c_ftl_nand_byte_pre_oob,"aw",@nobits
	.align	1
	.set	.LANCHOR58,. + 0
	.type	c_ftl_nand_byte_pre_oob, %object
	.size	c_ftl_nand_byte_pre_oob, 2
c_ftl_nand_byte_pre_oob:
	.zero	2
	.section	.bss.c_ftl_nand_byte_pre_page,"aw",@nobits
	.align	1
	.set	.LANCHOR57,. + 0
	.type	c_ftl_nand_byte_pre_page, %object
	.size	c_ftl_nand_byte_pre_page, 2
c_ftl_nand_byte_pre_page:
	.zero	2
	.section	.bss.c_ftl_nand_data_blks_per_plane,"aw",@nobits
	.align	1
	.set	.LANCHOR40,. + 0
	.type	c_ftl_nand_data_blks_per_plane, %object
	.size	c_ftl_nand_data_blks_per_plane, 2
c_ftl_nand_data_blks_per_plane:
	.zero	2
	.section	.bss.c_ftl_nand_data_op_blks_per_plane,"aw",@nobits
	.align	1
	.set	.LANCHOR232,. + 0
	.type	c_ftl_nand_data_op_blks_per_plane, %object
	.size	c_ftl_nand_data_op_blks_per_plane, 2
c_ftl_nand_data_op_blks_per_plane:
	.zero	2
	.section	.bss.c_ftl_nand_die_num,"aw",@nobits
	.align	1
	.set	.LANCHOR45,. + 0
	.type	c_ftl_nand_die_num, %object
	.size	c_ftl_nand_die_num, 2
c_ftl_nand_die_num:
	.zero	2
	.section	.bss.c_ftl_nand_ext_blk_pre_plane,"aw",@nobits
	.align	1
	.set	.LANCHOR49,. + 0
	.type	c_ftl_nand_ext_blk_pre_plane, %object
	.size	c_ftl_nand_ext_blk_pre_plane, 2
c_ftl_nand_ext_blk_pre_plane:
	.zero	2
	.section	.bss.c_ftl_nand_init_sys_blks_per_plane,"aw",@nobits
	.align	2
	.set	.LANCHOR65,. + 0
	.type	c_ftl_nand_init_sys_blks_per_plane, %object
	.size	c_ftl_nand_init_sys_blks_per_plane, 4
c_ftl_nand_init_sys_blks_per_plane:
	.zero	4
	.section	.bss.c_ftl_nand_l2pmap_ram_region_num,"aw",@nobits
	.align	1
	.set	.LANCHOR67,. + 0
	.type	c_ftl_nand_l2pmap_ram_region_num, %object
	.size	c_ftl_nand_l2pmap_ram_region_num, 2
c_ftl_nand_l2pmap_ram_region_num:
	.zero	2
	.section	.bss.c_ftl_nand_map_blks_per_plane,"aw",@nobits
	.align	1
	.set	.LANCHOR63,. + 0
	.type	c_ftl_nand_map_blks_per_plane, %object
	.size	c_ftl_nand_map_blks_per_plane, 2
c_ftl_nand_map_blks_per_plane:
	.zero	2
	.section	.bss.c_ftl_nand_map_region_num,"aw",@nobits
	.align	1
	.set	.LANCHOR66,. + 0
	.type	c_ftl_nand_map_region_num, %object
	.size	c_ftl_nand_map_region_num, 2
c_ftl_nand_map_region_num:
	.zero	2
	.section	.bss.c_ftl_nand_max_data_blks,"aw",@nobits
	.align	2
	.set	.LANCHOR42,. + 0
	.type	c_ftl_nand_max_data_blks, %object
	.size	c_ftl_nand_max_data_blks, 4
c_ftl_nand_max_data_blks:
	.zero	4
	.section	.bss.c_ftl_nand_max_map_blks,"aw",@nobits
	.align	2
	.set	.LANCHOR64,. + 0
	.type	c_ftl_nand_max_map_blks, %object
	.size	c_ftl_nand_max_map_blks, 4
c_ftl_nand_max_map_blks:
	.zero	4
	.section	.bss.c_ftl_nand_max_sys_blks,"aw",@nobits
	.align	2
	.set	.LANCHOR39,. + 0
	.type	c_ftl_nand_max_sys_blks, %object
	.size	c_ftl_nand_max_sys_blks, 4
c_ftl_nand_max_sys_blks:
	.zero	4
	.section	.bss.c_ftl_nand_max_vendor_blks,"aw",@nobits
	.align	1
	.set	.LANCHOR61,. + 0
	.type	c_ftl_nand_max_vendor_blks, %object
	.size	c_ftl_nand_max_vendor_blks, 2
c_ftl_nand_max_vendor_blks:
	.zero	2
	.section	.bss.c_ftl_nand_page_pre_blk,"aw",@nobits
	.align	1
	.set	.LANCHOR52,. + 0
	.type	c_ftl_nand_page_pre_blk, %object
	.size	c_ftl_nand_page_pre_blk, 2
c_ftl_nand_page_pre_blk:
	.zero	2
	.section	.bss.c_ftl_nand_page_pre_slc_blk,"aw",@nobits
	.align	1
	.set	.LANCHOR53,. + 0
	.type	c_ftl_nand_page_pre_slc_blk, %object
	.size	c_ftl_nand_page_pre_slc_blk, 2
c_ftl_nand_page_pre_slc_blk:
	.zero	2
	.section	.bss.c_ftl_nand_page_pre_super_blk,"aw",@nobits
	.align	1
	.set	.LANCHOR54,. + 0
	.type	c_ftl_nand_page_pre_super_blk, %object
	.size	c_ftl_nand_page_pre_super_blk, 2
c_ftl_nand_page_pre_super_blk:
	.zero	2
	.section	.bss.c_ftl_nand_planes_num,"aw",@nobits
	.align	1
	.set	.LANCHOR38,. + 0
	.type	c_ftl_nand_planes_num, %object
	.size	c_ftl_nand_planes_num, 2
c_ftl_nand_planes_num:
	.zero	2
	.section	.bss.c_ftl_nand_planes_per_die,"aw",@nobits
	.align	1
	.set	.LANCHOR46,. + 0
	.type	c_ftl_nand_planes_per_die, %object
	.size	c_ftl_nand_planes_per_die, 2
c_ftl_nand_planes_per_die:
	.zero	2
	.section	.bss.c_ftl_nand_reserved_blks,"aw",@nobits
	.align	1
	.set	.LANCHOR59,. + 0
	.type	c_ftl_nand_reserved_blks, %object
	.size	c_ftl_nand_reserved_blks, 2
c_ftl_nand_reserved_blks:
	.zero	2
	.section	.bss.c_ftl_nand_sec_pre_page,"aw",@nobits
	.align	1
	.set	.LANCHOR55,. + 0
	.type	c_ftl_nand_sec_pre_page, %object
	.size	c_ftl_nand_sec_pre_page, 2
c_ftl_nand_sec_pre_page:
	.zero	2
	.section	.bss.c_ftl_nand_sec_pre_page_shift,"aw",@nobits
	.align	1
	.set	.LANCHOR56,. + 0
	.type	c_ftl_nand_sec_pre_page_shift, %object
	.size	c_ftl_nand_sec_pre_page_shift, 2
c_ftl_nand_sec_pre_page_shift:
	.zero	2
	.section	.bss.c_ftl_nand_sys_blks_per_plane,"aw",@nobits
	.align	2
	.set	.LANCHOR37,. + 0
	.type	c_ftl_nand_sys_blks_per_plane, %object
	.size	c_ftl_nand_sys_blks_per_plane, 4
c_ftl_nand_sys_blks_per_plane:
	.zero	4
	.section	.bss.c_ftl_nand_totle_phy_blks,"aw",@nobits
	.align	2
	.set	.LANCHOR43,. + 0
	.type	c_ftl_nand_totle_phy_blks, %object
	.size	c_ftl_nand_totle_phy_blks, 4
c_ftl_nand_totle_phy_blks:
	.zero	4
	.section	.bss.c_ftl_nand_type,"aw",@nobits
	.align	1
	.set	.LANCHOR44,. + 0
	.type	c_ftl_nand_type, %object
	.size	c_ftl_nand_type, 2
c_ftl_nand_type:
	.zero	2
	.section	.bss.c_ftl_nand_vendor_region_num,"aw",@nobits
	.align	1
	.set	.LANCHOR62,. + 0
	.type	c_ftl_nand_vendor_region_num, %object
	.size	c_ftl_nand_vendor_region_num, 2
c_ftl_nand_vendor_region_num:
	.zero	2
	.section	.bss.c_ftl_vendor_part_size,"aw",@nobits
	.align	1
	.set	.LANCHOR50,. + 0
	.type	c_ftl_vendor_part_size, %object
	.size	c_ftl_vendor_part_size, 2
c_ftl_vendor_part_size:
	.zero	2
	.section	.bss.c_gc_page_buf_num,"aw",@nobits
	.align	2
	.set	.LANCHOR110,. + 0
	.type	c_gc_page_buf_num, %object
	.size	c_gc_page_buf_num, 4
c_gc_page_buf_num:
	.zero	4
	.section	.bss.c_mlc_erase_count_value,"aw",@nobits
	.align	1
	.set	.LANCHOR48,. + 0
	.type	c_mlc_erase_count_value, %object
	.size	c_mlc_erase_count_value, 2
c_mlc_erase_count_value:
	.zero	2
	.section	.bss.c_wr_page_buf_num,"aw",@nobits
	.align	2
	.set	.LANCHOR185,. + 0
	.type	c_wr_page_buf_num, %object
	.size	c_wr_page_buf_num, 4
c_wr_page_buf_num:
	.zero	4
	.section	.bss.check_valid_page_count_table,"aw",@nobits
	.align	3
	.type	check_valid_page_count_table, %object
	.size	check_valid_page_count_table, 8192
check_valid_page_count_table:
	.zero	8192
	.section	.bss.ftl_gc_temp_power_lost_recovery_flag,"aw",@nobits
	.align	2
	.set	.LANCHOR138,. + 0
	.type	ftl_gc_temp_power_lost_recovery_flag, %object
	.size	ftl_gc_temp_power_lost_recovery_flag, 4
ftl_gc_temp_power_lost_recovery_flag:
	.zero	4
	.section	.bss.gBbtInfo,"aw",@nobits
	.align	3
	.set	.LANCHOR76,. + 0
	.type	gBbtInfo, %object
	.size	gBbtInfo, 96
gBbtInfo:
	.zero	96
	.section	.bss.gBlockPageAlignSize,"aw",@nobits
	.align	2
	.set	.LANCHOR4,. + 0
	.type	gBlockPageAlignSize, %object
	.size	gBlockPageAlignSize, 4
gBlockPageAlignSize:
	.zero	4
	.section	.bss.gBootDdrMode,"aw",@nobits
	.align	2
	.set	.LANCHOR160,. + 0
	.type	gBootDdrMode, %object
	.size	gBootDdrMode, 4
gBootDdrMode:
	.zero	4
	.section	.bss.gDieOp,"aw",@nobits
	.align	2
	.set	.LANCHOR23,. + 0
	.type	gDieOp, %object
	.size	gDieOp, 192
gDieOp:
	.zero	192
	.section	.bss.gFlashCurMode,"aw",@nobits
	.set	.LANCHOR24,. + 0
	.type	gFlashCurMode, %object
	.size	gFlashCurMode, 1
gFlashCurMode:
	.zero	1
	.section	.bss.gFlashInterfaceMode,"aw",@nobits
	.set	.LANCHOR25,. + 0
	.type	gFlashInterfaceMode, %object
	.size	gFlashInterfaceMode, 1
gFlashInterfaceMode:
	.zero	1
	.section	.bss.gFlashOnfiModeEn,"aw",@nobits
	.type	gFlashOnfiModeEn, %object
	.size	gFlashOnfiModeEn, 1
gFlashOnfiModeEn:
	.zero	1
	.section	.bss.gFlashPageBuffer0,"aw",@nobits
	.align	3
	.set	.LANCHOR154,. + 0
	.type	gFlashPageBuffer0, %object
	.size	gFlashPageBuffer0, 8
gFlashPageBuffer0:
	.zero	8
	.section	.bss.gFlashPageBuffer1,"aw",@nobits
	.align	3
	.set	.LANCHOR152,. + 0
	.type	gFlashPageBuffer1, %object
	.size	gFlashPageBuffer1, 8
gFlashPageBuffer1:
	.zero	8
	.section	.bss.gFlashProgCheckBuffer,"aw",@nobits
	.align	3
	.set	.LANCHOR206,. + 0
	.type	gFlashProgCheckBuffer, %object
	.size	gFlashProgCheckBuffer, 8
gFlashProgCheckBuffer:
	.zero	8
	.section	.bss.gFlashProgCheckSpareBuffer,"aw",@nobits
	.align	3
	.set	.LANCHOR207,. + 0
	.type	gFlashProgCheckSpareBuffer, %object
	.size	gFlashProgCheckSpareBuffer, 8
gFlashProgCheckSpareBuffer:
	.zero	8
	.section	.bss.gFlashSdrModeEn,"aw",@nobits
	.type	gFlashSdrModeEn, %object
	.size	gFlashSdrModeEn, 1
gFlashSdrModeEn:
	.zero	1
	.section	.bss.gFlashSlcMode,"aw",@nobits
	.set	.LANCHOR16,. + 0
	.type	gFlashSlcMode, %object
	.size	gFlashSlcMode, 1
gFlashSlcMode:
	.zero	1
	.section	.bss.gFlashSpareBuffer,"aw",@nobits
	.align	3
	.set	.LANCHOR205,. + 0
	.type	gFlashSpareBuffer, %object
	.size	gFlashSpareBuffer, 8
gFlashSpareBuffer:
	.zero	8
	.section	.bss.gFlashToggleModeEn,"aw",@nobits
	.set	.LANCHOR30,. + 0
	.type	gFlashToggleModeEn, %object
	.size	gFlashToggleModeEn, 1
gFlashToggleModeEn:
	.zero	1
	.section	.bss.gL2pMapInfo,"aw",@nobits
	.align	3
	.set	.LANCHOR130,. + 0
	.type	gL2pMapInfo, %object
	.size	gL2pMapInfo, 64
gL2pMapInfo:
	.zero	64
	.section	.bss.gMasterInfo,"aw",@nobits
	.align	3
	.set	.LANCHOR35,. + 0
	.type	gMasterInfo, %object
	.size	gMasterInfo, 48
gMasterInfo:
	.zero	48
	.section	.bss.gMasterTempBuf,"aw",@nobits
	.align	3
	.set	.LANCHOR161,. + 0
	.type	gMasterTempBuf, %object
	.size	gMasterTempBuf, 8
gMasterTempBuf:
	.zero	8
	.section	.bss.gMultiPageProgEn,"aw",@nobits
	.set	.LANCHOR28,. + 0
	.type	gMultiPageProgEn, %object
	.size	gMultiPageProgEn, 1
gMultiPageProgEn:
	.zero	1
	.section	.bss.gMultiPageReadEn,"aw",@nobits
	.set	.LANCHOR210,. + 0
	.type	gMultiPageReadEn, %object
	.size	gMultiPageReadEn, 1
gMultiPageReadEn:
	.zero	1
	.section	.bss.gNandChipMap,"aw",@nobits
	.align	3
	.set	.LANCHOR0,. + 0
	.type	gNandChipMap, %object
	.size	gNandChipMap, 64
gNandChipMap:
	.zero	64
	.section	.bss.gNandFlashEccBits,"aw",@nobits
	.set	.LANCHOR33,. + 0
	.type	gNandFlashEccBits, %object
	.size	gNandFlashEccBits, 1
gNandFlashEccBits:
	.zero	1
	.section	.bss.gNandFlashIDBEccBits,"aw",@nobits
	.set	.LANCHOR158,. + 0
	.type	gNandFlashIDBEccBits, %object
	.size	gNandFlashIDBEccBits, 1
gNandFlashIDBEccBits:
	.zero	1
	.section	.bss.gNandFlashIdbBlockAddr,"aw",@nobits
	.align	2
	.set	.LANCHOR156,. + 0
	.type	gNandFlashIdbBlockAddr, %object
	.size	gNandFlashIdbBlockAddr, 4
gNandFlashIdbBlockAddr:
	.zero	4
	.section	.bss.gNandFlashInfoBlockAddr,"aw",@nobits
	.align	2
	.set	.LANCHOR155,. + 0
	.type	gNandFlashInfoBlockAddr, %object
	.size	gNandFlashInfoBlockAddr, 4
gNandFlashInfoBlockAddr:
	.zero	4
	.section	.bss.gNandFlashInfoBlockEcc,"aw",@nobits
	.type	gNandFlashInfoBlockEcc, %object
	.size	gNandFlashInfoBlockEcc, 1
gNandFlashInfoBlockEcc:
	.zero	1
	.section	.bss.gNandFlashResEndPageAddr,"aw",@nobits
	.align	2
	.type	gNandFlashResEndPageAddr, %object
	.size	gNandFlashResEndPageAddr, 4
gNandFlashResEndPageAddr:
	.zero	4
	.section	.bss.gNandIDBResBlkNum,"aw",@nobits
	.set	.LANCHOR3,. + 0
	.type	gNandIDBResBlkNum, %object
	.size	gNandIDBResBlkNum, 1
gNandIDBResBlkNum:
	.zero	1
	.section	.bss.gNandIDBResBlkNumSaveInFlash,"aw",@nobits
	.set	.LANCHOR157,. + 0
	.type	gNandIDBResBlkNumSaveInFlash, %object
	.size	gNandIDBResBlkNumSaveInFlash, 1
gNandIDBResBlkNumSaveInFlash:
	.zero	1
	.section	.bss.gNandIDataBuf,"aw",@nobits
	.align	3
	.set	.LANCHOR144,. + 0
	.type	gNandIDataBuf, %object
	.size	gNandIDataBuf, 2048
gNandIDataBuf:
	.zero	2048
	.section	.bss.gNandMaxChip,"aw",@nobits
	.set	.LANCHOR124,. + 0
	.type	gNandMaxChip, %object
	.size	gNandMaxChip, 1
gNandMaxChip:
	.zero	1
	.section	.bss.gNandMaxDie,"aw",@nobits
	.set	.LANCHOR26,. + 0
	.type	gNandMaxDie, %object
	.size	gNandMaxDie, 1
gNandMaxDie:
	.zero	1
	.section	.bss.gNandOptPara,"aw",@nobits
	.align	3
	.set	.LANCHOR8,. + 0
	.type	gNandOptPara, %object
	.size	gNandOptPara, 32
gNandOptPara:
	.zero	32
	.section	.bss.gNandPhyInfo,"aw",@nobits
	.align	3
	.set	.LANCHOR15,. + 0
	.type	gNandPhyInfo, %object
	.size	gNandPhyInfo, 28
gNandPhyInfo:
	.zero	28
	.section	.bss.gNandRandomizer,"aw",@nobits
	.set	.LANCHOR6,. + 0
	.type	gNandRandomizer, %object
	.size	gNandRandomizer, 1
gNandRandomizer:
	.zero	1
	.section	.bss.gNandcDumpWriteEn,"aw",@nobits
	.align	2
	.set	.LANCHOR36,. + 0
	.type	gNandcDumpWriteEn, %object
	.size	gNandcDumpWriteEn, 4
gNandcDumpWriteEn:
	.zero	4
	.section	.bss.gNandcEccBits,"aw",@nobits
	.align	2
	.set	.LANCHOR32,. + 0
	.type	gNandcEccBits, %object
	.size	gNandcEccBits, 4
gNandcEccBits:
	.zero	4
	.section	.bss.gNandcVer,"aw",@nobits
	.align	2
	.set	.LANCHOR34,. + 0
	.type	gNandcVer, %object
	.size	gNandcVer, 4
gNandcVer:
	.zero	4
	.section	.bss.gReadRetryInfo,"aw",@nobits
	.align	3
	.set	.LANCHOR20,. + 0
	.type	gReadRetryInfo, %object
	.size	gReadRetryInfo, 852
gReadRetryInfo:
	.zero	852
	.section	.bss.gSysFreeQueue,"aw",@nobits
	.align	3
	.set	.LANCHOR77,. + 0
	.type	gSysFreeQueue, %object
	.size	gSysFreeQueue, 2056
gSysFreeQueue:
	.zero	2056
	.section	.bss.gSysInfo,"aw",@nobits
	.align	3
	.set	.LANCHOR218,. + 0
	.type	gSysInfo, %object
	.size	gSysInfo, 16
gSysInfo:
	.zero	16
	.section	.bss.gToggleModeClkDiv,"aw",@nobits
	.align	2
	.type	gToggleModeClkDiv, %object
	.size	gToggleModeClkDiv, 4
gToggleModeClkDiv:
	.zero	4
	.section	.bss.gTotleBlock,"aw",@nobits
	.align	1
	.set	.LANCHOR125,. + 0
	.type	gTotleBlock, %object
	.size	gTotleBlock, 2
gTotleBlock:
	.zero	2
	.section	.bss.gVendorBlkInfo,"aw",@nobits
	.align	3
	.set	.LANCHOR224,. + 0
	.type	gVendorBlkInfo, %object
	.size	gVendorBlkInfo, 64
gVendorBlkInfo:
	.zero	64
	.section	.bss.g_GlobalDataVersion,"aw",@nobits
	.align	2
	.set	.LANCHOR165,. + 0
	.type	g_GlobalDataVersion, %object
	.size	g_GlobalDataVersion, 4
g_GlobalDataVersion:
	.zero	4
	.section	.bss.g_GlobalSysVersion,"aw",@nobits
	.align	2
	.set	.LANCHOR164,. + 0
	.type	g_GlobalSysVersion, %object
	.size	g_GlobalSysVersion, 4
g_GlobalSysVersion:
	.zero	4
	.section	.bss.g_LowFormat,"aw",@nobits
	.align	2
	.set	.LANCHOR254,. + 0
	.type	g_LowFormat, %object
	.size	g_LowFormat, 4
g_LowFormat:
	.zero	4
	.section	.bss.g_MaxLbaSector,"aw",@nobits
	.align	2
	.set	.LANCHOR68,. + 0
	.type	g_MaxLbaSector, %object
	.size	g_MaxLbaSector, 4
g_MaxLbaSector:
	.zero	4
	.section	.bss.g_MaxLbn,"aw",@nobits
	.align	2
	.set	.LANCHOR231,. + 0
	.type	g_MaxLbn, %object
	.size	g_MaxLbn, 4
g_MaxLbn:
	.zero	4
	.section	.bss.g_MaxLpn,"aw",@nobits
	.align	2
	.set	.LANCHOR74,. + 0
	.type	g_MaxLpn, %object
	.size	g_MaxLpn, 4
g_MaxLpn:
	.zero	4
	.section	.bss.g_SlcPartLbaEndSector,"aw",@nobits
	.align	2
	.set	.LANCHOR162,. + 0
	.type	g_SlcPartLbaEndSector, %object
	.size	g_SlcPartLbaEndSector, 4
g_SlcPartLbaEndSector:
	.zero	4
	.section	.bss.g_VaildLpn,"aw",@nobits
	.align	2
	.set	.LANCHOR102,. + 0
	.type	g_VaildLpn, %object
	.size	g_VaildLpn, 4
g_VaildLpn:
	.zero	4
	.section	.bss.g_active_superblock,"aw",@nobits
	.align	3
	.set	.LANCHOR93,. + 0
	.type	g_active_superblock, %object
	.size	g_active_superblock, 48
g_active_superblock:
	.zero	48
	.section	.bss.g_all_blk_used_slc_mode,"aw",@nobits
	.align	2
	.set	.LANCHOR163,. + 0
	.type	g_all_blk_used_slc_mode, %object
	.size	g_all_blk_used_slc_mode, 4
g_all_blk_used_slc_mode:
	.zero	4
	.section	.bss.g_buffer_superblock,"aw",@nobits
	.align	3
	.set	.LANCHOR94,. + 0
	.type	g_buffer_superblock, %object
	.size	g_buffer_superblock, 48
g_buffer_superblock:
	.zero	48
	.section	.bss.g_cur_erase_blk,"aw",@nobits
	.align	2
	.set	.LANCHOR75,. + 0
	.type	g_cur_erase_blk, %object
	.size	g_cur_erase_blk, 4
g_cur_erase_blk:
	.zero	4
	.section	.bss.g_ect_tbl_info_size,"aw",@nobits
	.align	1
	.set	.LANCHOR198,. + 0
	.type	g_ect_tbl_info_size, %object
	.size	g_ect_tbl_info_size, 2
g_ect_tbl_info_size:
	.zero	2
	.section	.bss.g_ect_tbl_power_up_flush,"aw",@nobits
	.align	1
	.set	.LANCHOR227,. + 0
	.type	g_ect_tbl_power_up_flush, %object
	.size	g_ect_tbl_power_up_flush, 2
g_ect_tbl_power_up_flush:
	.zero	2
	.section	.bss.g_flash_read_only_en,"aw",@nobits
	.align	2
	.set	.LANCHOR78,. + 0
	.type	g_flash_read_only_en, %object
	.size	g_flash_read_only_en, 4
g_flash_read_only_en:
	.zero	4
	.section	.bss.g_free_slc_blk_num,"aw",@nobits
	.align	1
	.set	.LANCHOR142,. + 0
	.type	g_free_slc_blk_num, %object
	.size	g_free_slc_blk_num, 2
g_free_slc_blk_num:
	.zero	2
	.section	.bss.g_ftl_nand_free_count,"aw",@nobits
	.align	2
	.set	.LANCHOR256,. + 0
	.type	g_ftl_nand_free_count, %object
	.size	g_ftl_nand_free_count, 4
g_ftl_nand_free_count:
	.zero	4
	.section	.bss.g_gc_bad_block_gc_index,"aw",@nobits
	.align	1
	.set	.LANCHOR121,. + 0
	.type	g_gc_bad_block_gc_index, %object
	.size	g_gc_bad_block_gc_index, 2
g_gc_bad_block_gc_index:
	.zero	2
	.section	.bss.g_gc_bad_block_temp_num,"aw",@nobits
	.align	1
	.set	.LANCHOR119,. + 0
	.type	g_gc_bad_block_temp_num, %object
	.size	g_gc_bad_block_temp_num, 2
g_gc_bad_block_temp_num:
	.zero	2
	.section	.bss.g_gc_bad_block_temp_tbl,"aw",@nobits
	.align	3
	.set	.LANCHOR120,. + 0
	.type	g_gc_bad_block_temp_tbl, %object
	.size	g_gc_bad_block_temp_tbl, 34
g_gc_bad_block_temp_tbl:
	.zero	34
	.section	.bss.g_gc_blk_index,"aw",@nobits
	.align	1
	.set	.LANCHOR183,. + 0
	.type	g_gc_blk_index, %object
	.size	g_gc_blk_index, 2
g_gc_blk_index:
	.zero	2
	.section	.bss.g_gc_blk_num,"aw",@nobits
	.align	1
	.set	.LANCHOR111,. + 0
	.type	g_gc_blk_num, %object
	.size	g_gc_blk_num, 2
g_gc_blk_num:
	.zero	2
	.section	.bss.g_gc_cur_blk_max_valid_pages,"aw",@nobits
	.align	1
	.set	.LANCHOR250,. + 0
	.type	g_gc_cur_blk_max_valid_pages, %object
	.size	g_gc_cur_blk_max_valid_pages, 2
g_gc_cur_blk_max_valid_pages:
	.zero	2
	.section	.bss.g_gc_cur_blk_valid_pages,"aw",@nobits
	.align	1
	.set	.LANCHOR249,. + 0
	.type	g_gc_cur_blk_valid_pages, %object
	.size	g_gc_cur_blk_valid_pages, 2
g_gc_cur_blk_valid_pages:
	.zero	2
	.section	.bss.g_gc_free_blk_threshold,"aw",@nobits
	.align	1
	.set	.LANCHOR181,. + 0
	.type	g_gc_free_blk_threshold, %object
	.size	g_gc_free_blk_threshold, 2
g_gc_free_blk_threshold:
	.zero	2
	.section	.bss.g_gc_head_data_block,"aw",@nobits
	.align	2
	.set	.LANCHOR178,. + 0
	.type	g_gc_head_data_block, %object
	.size	g_gc_head_data_block, 4
g_gc_head_data_block:
	.zero	4
	.section	.bss.g_gc_head_data_block_count,"aw",@nobits
	.align	2
	.set	.LANCHOR179,. + 0
	.type	g_gc_head_data_block_count, %object
	.size	g_gc_head_data_block_count, 4
g_gc_head_data_block_count:
	.zero	4
	.section	.bss.g_gc_merge_free_blk_threshold,"aw",@nobits
	.align	1
	.set	.LANCHOR182,. + 0
	.type	g_gc_merge_free_blk_threshold, %object
	.size	g_gc_merge_free_blk_threshold, 2
g_gc_merge_free_blk_threshold:
	.zero	2
	.section	.bss.g_gc_next_blk,"aw",@nobits
	.align	1
	.set	.LANCHOR115,. + 0
	.type	g_gc_next_blk, %object
	.size	g_gc_next_blk, 2
g_gc_next_blk:
	.zero	2
	.section	.bss.g_gc_next_blk_1,"aw",@nobits
	.align	1
	.set	.LANCHOR116,. + 0
	.type	g_gc_next_blk_1, %object
	.size	g_gc_next_blk_1, 2
g_gc_next_blk_1:
	.zero	2
	.section	.bss.g_gc_next_blk_2,"aw",@nobits
	.align	1
	.set	.LANCHOR117,. + 0
	.type	g_gc_next_blk_2, %object
	.size	g_gc_next_blk_2, 2
g_gc_next_blk_2:
	.zero	2
	.section	.bss.g_gc_next_blk_3,"aw",@nobits
	.align	1
	.set	.LANCHOR118,. + 0
	.type	g_gc_next_blk_3, %object
	.size	g_gc_next_blk_3, 2
g_gc_next_blk_3:
	.zero	2
	.section	.bss.g_gc_num_req,"aw",@nobits
	.align	2
	.set	.LANCHOR105,. + 0
	.type	g_gc_num_req, %object
	.size	g_gc_num_req, 4
g_gc_num_req:
	.zero	4
	.section	.bss.g_gc_page_offset,"aw",@nobits
	.align	1
	.set	.LANCHOR113,. + 0
	.type	g_gc_page_offset, %object
	.size	g_gc_page_offset, 2
g_gc_page_offset:
	.zero	2
	.section	.bss.g_gc_refresh_block_temp_num,"aw",@nobits
	.align	1
	.set	.LANCHOR184,. + 0
	.type	g_gc_refresh_block_temp_num, %object
	.size	g_gc_refresh_block_temp_num, 2
g_gc_refresh_block_temp_num:
	.zero	2
	.section	.bss.g_gc_refresh_block_temp_tbl,"aw",@nobits
	.align	3
	.type	g_gc_refresh_block_temp_tbl, %object
	.size	g_gc_refresh_block_temp_tbl, 34
g_gc_refresh_block_temp_tbl:
	.zero	34
	.section	.bss.g_gc_skip_write_count,"aw",@nobits
	.align	2
	.set	.LANCHOR180,. + 0
	.type	g_gc_skip_write_count, %object
	.size	g_gc_skip_write_count, 4
g_gc_skip_write_count:
	.zero	4
	.section	.bss.g_gc_superblock,"aw",@nobits
	.align	3
	.set	.LANCHOR213,. + 0
	.type	g_gc_superblock, %object
	.size	g_gc_superblock, 48
g_gc_superblock:
	.zero	48
	.section	.bss.g_gc_temp_superblock,"aw",@nobits
	.align	3
	.set	.LANCHOR95,. + 0
	.type	g_gc_temp_superblock, %object
	.size	g_gc_temp_superblock, 48
g_gc_temp_superblock:
	.zero	48
	.section	.bss.g_in_gc_progress,"aw",@nobits
	.align	2
	.set	.LANCHOR176,. + 0
	.type	g_in_gc_progress, %object
	.size	g_in_gc_progress, 4
g_in_gc_progress:
	.zero	4
	.section	.bss.g_in_swl_replace,"aw",@nobits
	.align	2
	.set	.LANCHOR177,. + 0
	.type	g_in_swl_replace, %object
	.size	g_in_swl_replace, 4
g_in_swl_replace:
	.zero	4
	.section	.bss.g_inkDie_check_enable,"aw",@nobits
	.align	2
	.set	.LANCHOR104,. + 0
	.type	g_inkDie_check_enable, %object
	.size	g_inkDie_check_enable, 4
g_inkDie_check_enable:
	.zero	4
	.section	.bss.g_l2p_last_update_region_id,"aw",@nobits
	.align	1
	.set	.LANCHOR99,. + 0
	.type	g_l2p_last_update_region_id, %object
	.size	g_l2p_last_update_region_id, 2
g_l2p_last_update_region_id:
	.zero	2
	.section	.bss.g_maxRegNum,"aw",@nobits
	.set	.LANCHOR13,. + 0
	.type	g_maxRegNum, %object
	.size	g_maxRegNum, 1
g_maxRegNum:
	.zero	1
	.section	.bss.g_maxRetryCount,"aw",@nobits
	.set	.LANCHOR149,. + 0
	.type	g_maxRetryCount, %object
	.size	g_maxRetryCount, 1
g_maxRetryCount:
	.zero	1
	.section	.bss.g_max_erase_count,"aw",@nobits
	.align	2
	.set	.LANCHOR174,. + 0
	.type	g_max_erase_count, %object
	.size	g_max_erase_count, 4
g_max_erase_count:
	.zero	4
	.section	.bss.g_min_erase_count,"aw",@nobits
	.align	2
	.set	.LANCHOR175,. + 0
	.type	g_min_erase_count, %object
	.size	g_min_erase_count, 4
g_min_erase_count:
	.zero	4
	.section	.bss.g_nand_ecc_en,"aw",@nobits
	.set	.LANCHOR208,. + 0
	.type	g_nand_ecc_en, %object
	.size	g_nand_ecc_en, 1
g_nand_ecc_en:
	.zero	1
	.section	.bss.g_nandc_version_data,"aw",@nobits
	.align	2
	.set	.LANCHOR122,. + 0
	.type	g_nandc_version_data, %object
	.size	g_nandc_version_data, 4
g_nandc_version_data:
	.zero	4
	.section	.bss.g_num_data_superblocks,"aw",@nobits
	.align	1
	.set	.LANCHOR87,. + 0
	.type	g_num_data_superblocks, %object
	.size	g_num_data_superblocks, 2
g_num_data_superblocks:
	.zero	2
	.section	.bss.g_num_free_superblocks,"aw",@nobits
	.align	1
	.set	.LANCHOR90,. + 0
	.type	g_num_free_superblocks, %object
	.size	g_num_free_superblocks, 2
g_num_free_superblocks:
	.zero	2
	.section	.bss.g_page_map_check_enable,"aw",@nobits
	.align	1
	.set	.LANCHOR69,. + 0
	.type	g_page_map_check_enable, %object
	.size	g_page_map_check_enable, 2
g_page_map_check_enable:
	.zero	2
	.section	.bss.g_power_lost_ecc_error_blk,"aw",@nobits
	.align	1
	.set	.LANCHOR241,. + 0
	.type	g_power_lost_ecc_error_blk, %object
	.size	g_power_lost_ecc_error_blk, 2
g_power_lost_ecc_error_blk:
	.zero	2
	.section	.bss.g_power_lost_recovery_flag,"aw",@nobits
	.align	1
	.set	.LANCHOR242,. + 0
	.type	g_power_lost_recovery_flag, %object
	.size	g_power_lost_recovery_flag, 2
g_power_lost_recovery_flag:
	.zero	2
	.section	.bss.g_recovery_page_min_ver,"aw",@nobits
	.align	2
	.set	.LANCHOR139,. + 0
	.type	g_recovery_page_min_ver, %object
	.size	g_recovery_page_min_ver, 4
g_recovery_page_min_ver:
	.zero	4
	.section	.bss.g_recovery_page_num,"aw",@nobits
	.align	2
	.set	.LANCHOR243,. + 0
	.type	g_recovery_page_num, %object
	.size	g_recovery_page_num, 4
g_recovery_page_num:
	.zero	4
	.section	.bss.g_recovery_ppa_tbl,"aw",@nobits
	.align	3
	.set	.LANCHOR244,. + 0
	.type	g_recovery_ppa_tbl, %object
	.size	g_recovery_ppa_tbl, 128
g_recovery_ppa_tbl:
	.zero	128
	.section	.bss.g_req_cache,"aw",@nobits
	.align	3
	.set	.LANCHOR135,. + 0
	.type	g_req_cache, %object
	.size	g_req_cache, 8
g_req_cache:
	.zero	8
	.section	.bss.g_retryMode,"aw",@nobits
	.set	.LANCHOR11,. + 0
	.type	g_retryMode, %object
	.size	g_retryMode, 1
g_retryMode:
	.zero	1
	.section	.bss.g_slc2KBNand,"aw",@nobits
	.set	.LANCHOR2,. + 0
	.type	g_slc2KBNand, %object
	.size	g_slc2KBNand, 1
g_slc2KBNand:
	.zero	1
	.section	.bss.g_sys_ext_data,"aw",@nobits
	.align	3
	.set	.LANCHOR141,. + 0
	.type	g_sys_ext_data, %object
	.size	g_sys_ext_data, 512
g_sys_ext_data:
	.zero	512
	.section	.bss.g_sys_save_data,"aw",@nobits
	.align	3
	.set	.LANCHOR82,. + 0
	.type	g_sys_save_data, %object
	.size	g_sys_save_data, 48
g_sys_save_data:
	.zero	48
	.section	.bss.g_tmp_data_superblock_id,"aw",@nobits
	.align	1
	.set	.LANCHOR136,. + 0
	.type	g_tmp_data_superblock_id, %object
	.size	g_tmp_data_superblock_id, 2
g_tmp_data_superblock_id:
	.zero	2
	.section	.bss.g_totle_avg_erase_count,"aw",@nobits
	.align	2
	.set	.LANCHOR214,. + 0
	.type	g_totle_avg_erase_count, %object
	.size	g_totle_avg_erase_count, 4
g_totle_avg_erase_count:
	.zero	4
	.section	.bss.g_totle_cache_write_count,"aw",@nobits
	.align	2
	.set	.LANCHOR169,. + 0
	.type	g_totle_cache_write_count, %object
	.size	g_totle_cache_write_count, 4
g_totle_cache_write_count:
	.zero	4
	.section	.bss.g_totle_discard_page_count,"aw",@nobits
	.align	2
	.set	.LANCHOR168,. + 0
	.type	g_totle_discard_page_count, %object
	.size	g_totle_discard_page_count, 4
g_totle_discard_page_count:
	.zero	4
	.section	.bss.g_totle_gc_page_count,"aw",@nobits
	.align	2
	.set	.LANCHOR166,. + 0
	.type	g_totle_gc_page_count, %object
	.size	g_totle_gc_page_count, 4
g_totle_gc_page_count:
	.zero	4
	.section	.bss.g_totle_l2p_write_count,"aw",@nobits
	.align	2
	.set	.LANCHOR170,. + 0
	.type	g_totle_l2p_write_count, %object
	.size	g_totle_l2p_write_count, 4
g_totle_l2p_write_count:
	.zero	4
	.section	.bss.g_totle_map_block,"aw",@nobits
	.align	1
	.set	.LANCHOR131,. + 0
	.type	g_totle_map_block, %object
	.size	g_totle_map_block, 2
g_totle_map_block:
	.zero	2
	.section	.bss.g_totle_mlc_erase_count,"aw",@nobits
	.align	2
	.set	.LANCHOR172,. + 0
	.type	g_totle_mlc_erase_count, %object
	.size	g_totle_mlc_erase_count, 4
g_totle_mlc_erase_count:
	.zero	4
	.section	.bss.g_totle_read_page_count,"aw",@nobits
	.align	2
	.set	.LANCHOR171,. + 0
	.type	g_totle_read_page_count, %object
	.size	g_totle_read_page_count, 4
g_totle_read_page_count:
	.zero	4
	.section	.bss.g_totle_read_sector,"aw",@nobits
	.align	2
	.set	.LANCHOR226,. + 0
	.type	g_totle_read_sector, %object
	.size	g_totle_read_sector, 4
g_totle_read_sector:
	.zero	4
	.section	.bss.g_totle_slc_erase_count,"aw",@nobits
	.align	2
	.set	.LANCHOR173,. + 0
	.type	g_totle_slc_erase_count, %object
	.size	g_totle_slc_erase_count, 4
g_totle_slc_erase_count:
	.zero	4
	.section	.bss.g_totle_swl_count,"aw",@nobits
	.align	2
	.set	.LANCHOR137,. + 0
	.type	g_totle_swl_count, %object
	.size	g_totle_swl_count, 4
g_totle_swl_count:
	.zero	4
	.section	.bss.g_totle_sys_slc_erase_count,"aw",@nobits
	.align	2
	.set	.LANCHOR81,. + 0
	.type	g_totle_sys_slc_erase_count, %object
	.size	g_totle_sys_slc_erase_count, 4
g_totle_sys_slc_erase_count:
	.zero	4
	.section	.bss.g_totle_vendor_block,"aw",@nobits
	.align	1
	.set	.LANCHOR70,. + 0
	.type	g_totle_vendor_block, %object
	.size	g_totle_vendor_block, 2
g_totle_vendor_block:
	.zero	2
	.section	.bss.g_totle_write_page_count,"aw",@nobits
	.align	2
	.set	.LANCHOR167,. + 0
	.type	g_totle_write_page_count, %object
	.size	g_totle_write_page_count, 4
g_totle_write_page_count:
	.zero	4
	.section	.bss.g_totle_write_sector,"aw",@nobits
	.align	2
	.set	.LANCHOR225,. + 0
	.type	g_totle_write_sector, %object
	.size	g_totle_write_sector, 4
g_totle_write_sector:
	.zero	4
	.section	.bss.g_wr_page_num,"aw",@nobits
	.align	2
	.set	.LANCHOR72,. + 0
	.type	g_wr_page_num, %object
	.size	g_wr_page_num, 4
g_wr_page_num:
	.zero	4
	.section	.bss.gc_discard_updated,"aw",@nobits
	.align	2
	.set	.LANCHOR253,. + 0
	.type	gc_discard_updated, %object
	.size	gc_discard_updated, 4
gc_discard_updated:
	.zero	4
	.section	.bss.gc_ink_free_return_value,"aw",@nobits
	.align	1
	.set	.LANCHOR248,. + 0
	.type	gc_ink_free_return_value, %object
	.size	gc_ink_free_return_value, 2
gc_ink_free_return_value:
	.zero	2
	.section	.bss.gpFlashSaveInfo,"aw",@nobits
	.align	3
	.set	.LANCHOR153,. + 0
	.type	gpFlashSaveInfo, %object
	.size	gpFlashSaveInfo, 8
gpFlashSaveInfo:
	.zero	8
	.section	.bss.gpNandParaInfo,"aw",@nobits
	.align	3
	.set	.LANCHOR7,. + 0
	.type	gpNandParaInfo, %object
	.size	gpNandParaInfo, 8
gpNandParaInfo:
	.zero	8
	.section	.bss.gpNandc,"aw",@nobits
	.align	3
	.set	.LANCHOR19,. + 0
	.type	gpNandc, %object
	.size	gpNandc, 8
gpNandc:
	.zero	8
	.section	.bss.gpNandc1,"aw",@nobits
	.align	3
	.type	gpNandc1, %object
	.size	gpNandc1, 8
gpNandc1:
	.zero	8
	.section	.bss.gpReadRetrial,"aw",@nobits
	.align	3
	.set	.LANCHOR148,. + 0
	.type	gpReadRetrial, %object
	.size	gpReadRetrial, 8
gpReadRetrial:
	.zero	8
	.section	.bss.gp_ect_tbl_info,"aw",@nobits
	.align	3
	.set	.LANCHOR199,. + 0
	.type	gp_ect_tbl_info, %object
	.size	gp_ect_tbl_info, 8
gp_ect_tbl_info:
	.zero	8
	.section	.bss.gp_flash_check_buf,"aw",@nobits
	.align	3
	.type	gp_flash_check_buf, %object
	.size	gp_flash_check_buf, 262144
gp_flash_check_buf:
	.zero	262144
	.section	.bss.gp_gc_page_buf_info,"aw",@nobits
	.align	3
	.set	.LANCHOR106,. + 0
	.type	gp_gc_page_buf_info, %object
	.size	gp_gc_page_buf_info, 8
gp_gc_page_buf_info:
	.zero	8
	.section	.bss.gp_last_act_superblock,"aw",@nobits
	.align	3
	.set	.LANCHOR252,. + 0
	.type	gp_last_act_superblock, %object
	.size	gp_last_act_superblock, 8
gp_last_act_superblock:
	.zero	8
	.section	.bss.idb_buf,"aw",@nobits
	.align	3
	.type	idb_buf, %object
	.size	idb_buf, 262144
idb_buf:
	.zero	262144
	.section	.bss.idb_flash_slc_mode,"aw",@nobits
	.align	2
	.set	.LANCHOR29,. + 0
	.type	idb_flash_slc_mode, %object
	.size	idb_flash_slc_mode, 4
idb_flash_slc_mode:
	.zero	4
	.section	.bss.idb_need_write_back,"aw",@nobits
	.align	2
	.set	.LANCHOR159,. + 0
	.type	idb_need_write_back, %object
	.size	idb_need_write_back, 4
idb_need_write_back:
	.zero	4
	.section	.bss.last_cache_match_count,"aw",@nobits
	.align	2
	.set	.LANCHOR257,. + 0
	.type	last_cache_match_count, %object
	.size	last_cache_match_count, 4
last_cache_match_count:
	.zero	4
	.section	.bss.mlcPageToSlcPageTbl,"aw",@nobits
	.align	2
	.set	.LANCHOR123,. + 0
	.type	mlcPageToSlcPageTbl, %object
	.size	mlcPageToSlcPageTbl, 2048
mlcPageToSlcPageTbl:
	.zero	2048
	.section	.bss.p_blk_mode_table,"aw",@nobits
	.align	3
	.set	.LANCHOR1,. + 0
	.type	p_blk_mode_table, %object
	.size	p_blk_mode_table, 8
p_blk_mode_table:
	.zero	8
	.section	.bss.p_data_block_list_head,"aw",@nobits
	.align	3
	.set	.LANCHOR84,. + 0
	.type	p_data_block_list_head, %object
	.size	p_data_block_list_head, 8
p_data_block_list_head:
	.zero	8
	.section	.bss.p_data_block_list_table,"aw",@nobits
	.align	3
	.set	.LANCHOR83,. + 0
	.type	p_data_block_list_table, %object
	.size	p_data_block_list_table, 8
p_data_block_list_table:
	.zero	8
	.section	.bss.p_data_block_list_tail,"aw",@nobits
	.align	3
	.set	.LANCHOR86,. + 0
	.type	p_data_block_list_tail, %object
	.size	p_data_block_list_tail, 8
p_data_block_list_tail:
	.zero	8
	.section	.bss.p_erase_count_table,"aw",@nobits
	.align	3
	.set	.LANCHOR80,. + 0
	.type	p_erase_count_table, %object
	.size	p_erase_count_table, 8
p_erase_count_table:
	.zero	8
	.section	.bss.p_free_data_block_list_head,"aw",@nobits
	.align	3
	.set	.LANCHOR89,. + 0
	.type	p_free_data_block_list_head, %object
	.size	p_free_data_block_list_head, 8
p_free_data_block_list_head:
	.zero	8
	.section	.bss.p_gc_blk_tbl,"aw",@nobits
	.align	3
	.set	.LANCHOR112,. + 0
	.type	p_gc_blk_tbl, %object
	.size	p_gc_blk_tbl, 8
p_gc_blk_tbl:
	.zero	8
	.section	.bss.p_gc_data_buf,"aw",@nobits
	.align	3
	.set	.LANCHOR107,. + 0
	.type	p_gc_data_buf, %object
	.size	p_gc_data_buf, 8
p_gc_data_buf:
	.zero	8
	.section	.bss.p_gc_page_info,"aw",@nobits
	.align	3
	.set	.LANCHOR114,. + 0
	.type	p_gc_page_info, %object
	.size	p_gc_page_info, 8
p_gc_page_info:
	.zero	8
	.section	.bss.p_gc_spare_buf,"aw",@nobits
	.align	3
	.set	.LANCHOR108,. + 0
	.type	p_gc_spare_buf, %object
	.size	p_gc_spare_buf, 8
p_gc_spare_buf:
	.zero	8
	.section	.bss.p_io_data_buf_0,"aw",@nobits
	.align	3
	.set	.LANCHOR193,. + 0
	.type	p_io_data_buf_0, %object
	.size	p_io_data_buf_0, 8
p_io_data_buf_0:
	.zero	8
	.section	.bss.p_io_data_buf_1,"aw",@nobits
	.align	3
	.set	.LANCHOR194,. + 0
	.type	p_io_data_buf_1, %object
	.size	p_io_data_buf_1, 8
p_io_data_buf_1:
	.zero	8
	.section	.bss.p_io_spare_buf,"aw",@nobits
	.align	3
	.set	.LANCHOR196,. + 0
	.type	p_io_spare_buf, %object
	.size	p_io_spare_buf, 8
p_io_spare_buf:
	.zero	8
	.section	.bss.p_l2p_map_buf,"aw",@nobits
	.align	3
	.set	.LANCHOR129,. + 0
	.type	p_l2p_map_buf, %object
	.size	p_l2p_map_buf, 8
p_l2p_map_buf:
	.zero	8
	.section	.bss.p_l2p_ram_map,"aw",@nobits
	.align	3
	.set	.LANCHOR98,. + 0
	.type	p_l2p_ram_map, %object
	.size	p_l2p_ram_map, 8
p_l2p_ram_map:
	.zero	8
	.section	.bss.p_map_block_table,"aw",@nobits
	.align	3
	.set	.LANCHOR132,. + 0
	.type	p_map_block_table, %object
	.size	p_map_block_table, 8
p_map_block_table:
	.zero	8
	.section	.bss.p_map_block_valid_page_count,"aw",@nobits
	.align	3
	.set	.LANCHOR128,. + 0
	.type	p_map_block_valid_page_count, %object
	.size	p_map_block_valid_page_count, 8
p_map_block_valid_page_count:
	.zero	8
	.section	.bss.p_map_block_ver_table,"aw",@nobits
	.align	3
	.set	.LANCHOR133,. + 0
	.type	p_map_block_ver_table, %object
	.size	p_map_block_ver_table, 8
p_map_block_ver_table:
	.zero	8
	.section	.bss.p_map_region_ppn_check_table,"aw",@nobits
	.align	3
	.set	.LANCHOR203,. + 0
	.type	p_map_region_ppn_check_table, %object
	.size	p_map_region_ppn_check_table, 8
p_map_region_ppn_check_table:
	.zero	8
	.section	.bss.p_map_region_ppn_table,"aw",@nobits
	.align	3
	.set	.LANCHOR134,. + 0
	.type	p_map_region_ppn_table, %object
	.size	p_map_region_ppn_table, 8
p_map_region_ppn_table:
	.zero	8
	.section	.bss.p_plane_order_table,"aw",@nobits
	.align	3
	.set	.LANCHOR47,. + 0
	.type	p_plane_order_table, %object
	.size	p_plane_order_table, 32
p_plane_order_table:
	.zero	32
	.section	.bss.p_swl_mul_table,"aw",@nobits
	.align	3
	.set	.LANCHOR140,. + 0
	.type	p_swl_mul_table, %object
	.size	p_swl_mul_table, 8
p_swl_mul_table:
	.zero	8
	.section	.bss.p_sys_data_buf,"aw",@nobits
	.align	3
	.set	.LANCHOR189,. + 0
	.type	p_sys_data_buf, %object
	.size	p_sys_data_buf, 8
p_sys_data_buf:
	.zero	8
	.section	.bss.p_sys_data_buf_1,"aw",@nobits
	.align	3
	.set	.LANCHOR190,. + 0
	.type	p_sys_data_buf_1, %object
	.size	p_sys_data_buf_1, 8
p_sys_data_buf_1:
	.zero	8
	.section	.bss.p_sys_spare_buf,"aw",@nobits
	.align	3
	.set	.LANCHOR195,. + 0
	.type	p_sys_spare_buf, %object
	.size	p_sys_spare_buf, 8
p_sys_spare_buf:
	.zero	8
	.section	.bss.p_valid_page_count_table,"aw",@nobits
	.align	3
	.set	.LANCHOR85,. + 0
	.type	p_valid_page_count_table, %object
	.size	p_valid_page_count_table, 8
p_valid_page_count_table:
	.zero	8
	.section	.bss.p_vendor_block_table,"aw",@nobits
	.align	3
	.set	.LANCHOR71,. + 0
	.type	p_vendor_block_table, %object
	.size	p_vendor_block_table, 8
p_vendor_block_table:
	.zero	8
	.section	.bss.p_vendor_block_valid_page_count,"aw",@nobits
	.align	3
	.set	.LANCHOR200,. + 0
	.type	p_vendor_block_valid_page_count, %object
	.size	p_vendor_block_valid_page_count, 8
p_vendor_block_valid_page_count:
	.zero	8
	.section	.bss.p_vendor_block_ver_table,"aw",@nobits
	.align	3
	.set	.LANCHOR201,. + 0
	.type	p_vendor_block_ver_table, %object
	.size	p_vendor_block_ver_table, 8
p_vendor_block_ver_table:
	.zero	8
	.section	.bss.p_vendor_data_buf,"aw",@nobits
	.align	3
	.set	.LANCHOR191,. + 0
	.type	p_vendor_data_buf, %object
	.size	p_vendor_data_buf, 8
p_vendor_data_buf:
	.zero	8
	.section	.bss.p_vendor_region_ppn_table,"aw",@nobits
	.align	3
	.set	.LANCHOR202,. + 0
	.type	p_vendor_region_ppn_table, %object
	.size	p_vendor_region_ppn_table, 8
p_vendor_region_ppn_table:
	.zero	8
	.section	.bss.p_wr_io_data_buf,"aw",@nobits
	.align	3
	.set	.LANCHOR192,. + 0
	.type	p_wr_io_data_buf, %object
	.size	p_wr_io_data_buf, 8
p_wr_io_data_buf:
	.zero	8
	.section	.bss.p_wr_io_spare_buf,"aw",@nobits
	.align	3
	.set	.LANCHOR197,. + 0
	.type	p_wr_io_spare_buf, %object
	.size	p_wr_io_spare_buf, 8
p_wr_io_spare_buf:
	.zero	8
	.section	.bss.read_retry_cur_offset,"aw",@nobits
	.align	3
	.set	.LANCHOR21,. + 0
	.type	read_retry_cur_offset, %object
	.size	read_retry_cur_offset, 4
read_retry_cur_offset:
	.zero	4
	.section	.bss.req_erase,"aw",@nobits
	.align	3
	.set	.LANCHOR79,. + 0
	.type	req_erase, %object
	.size	req_erase, 8
req_erase:
	.zero	8
	.section	.bss.req_gc,"aw",@nobits
	.align	3
	.set	.LANCHOR109,. + 0
	.type	req_gc, %object
	.size	req_gc, 8
req_gc:
	.zero	8
	.section	.bss.req_gc_dst,"aw",@nobits
	.align	3
	.set	.LANCHOR187,. + 0
	.type	req_gc_dst, %object
	.size	req_gc_dst, 8
req_gc_dst:
	.zero	8
	.section	.bss.req_prgm,"aw",@nobits
	.align	3
	.set	.LANCHOR188,. + 0
	.type	req_prgm, %object
	.size	req_prgm, 8
req_prgm:
	.zero	8
	.section	.bss.req_read,"aw",@nobits
	.align	3
	.set	.LANCHOR186,. + 0
	.type	req_read, %object
	.size	req_read, 8
req_read:
	.zero	8
	.section	.bss.req_sys,"aw",@nobits
	.align	3
	.set	.LANCHOR211,. + 0
	.type	req_sys, %object
	.size	req_sys, 56
req_sys:
	.zero	56
	.section	.bss.req_wr_io,"aw",@nobits
	.align	3
	.set	.LANCHOR73,. + 0
	.type	req_wr_io, %object
	.size	req_wr_io, 8
req_wr_io:
	.zero	8
	.section	.bss.slcPageToMlcPageTbl,"aw",@nobits
	.align	2
	.set	.LANCHOR17,. + 0
	.type	slcPageToMlcPageTbl, %object
	.size	slcPageToMlcPageTbl, 1024
slcPageToMlcPageTbl:
	.zero	1024
	.section	.data.FtlMallocOffset,"aw",@progbits
	.align	2
	.type	FtlMallocOffset, %object
	.size	FtlMallocOffset, 4
FtlMallocOffset:
	.word	64
	.section	.data.LastWritenPbaAddr,"aw",@progbits
	.align	2
	.type	LastWritenPbaAddr, %object
	.size	LastWritenPbaAddr, 4
LastWritenPbaAddr:
	.word	-1
	.section	.data.NandFlashParaTbl,"aw",@progbits
	.align	3
	.set	.LANCHOR145,. + 0
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
	.hword	256
	.byte	2
	.byte	2
	.hword	2048
	.hword	479
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
	.zero	4
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
	.byte	0
	.byte	0
	.zero	4
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
	.hword	256
	.byte	2
	.byte	2
	.hword	2048
	.hword	287
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
	.zero	4
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
	.hword	256
	.byte	2
	.byte	2
	.hword	2048
	.hword	287
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
	.zero	4
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
	.hword	256
	.byte	2
	.byte	2
	.hword	2048
	.hword	287
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
	.zero	4
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
	.hword	256
	.byte	2
	.byte	2
	.hword	2048
	.hword	287
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
	.zero	4
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
	.hword	256
	.byte	2
	.byte	2
	.hword	1024
	.hword	287
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
	.zero	4
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
	.byte	0
	.byte	0
	.zero	4
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
	.byte	0
	.byte	0
	.zero	4
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
	.hword	128
	.byte	2
	.byte	2
	.hword	4096
	.hword	279
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
	.zero	4
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
	.hword	256
	.byte	2
	.byte	2
	.hword	1024
	.hword	287
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
	.zero	4
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
	.hword	256
	.byte	2
	.byte	2
	.hword	2048
	.hword	287
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
	.zero	4
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
	.hword	256
	.byte	2
	.byte	2
	.hword	2048
	.hword	287
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
	.zero	4
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
	.hword	128
	.byte	1
	.byte	2
	.hword	2048
	.hword	287
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
	.zero	4
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
	.byte	0
	.byte	0
	.zero	4
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
	.hword	256
	.byte	2
	.byte	2
	.hword	2048
	.hword	479
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
	.zero	4
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
	.hword	64
	.byte	1
	.byte	2
	.hword	2048
	.hword	279
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
	.zero	4
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
	.hword	64
	.byte	1
	.byte	2
	.hword	1024
	.hword	279
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
	.zero	4
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
	.hword	479
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
	.zero	4
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
	.hword	1479
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
	.zero	4
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
	.hword	1479
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
	.zero	4
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
	.hword	479
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
	.zero	4
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
	.hword	1479
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
	.zero	4
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
	.hword	1479
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
	.zero	4
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
	.hword	1479
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
	.zero	4
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
	.hword	1479
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
	.zero	4
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
	.byte	0
	.byte	0
	.zero	4
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
	.hword	1479
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
	.zero	4
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
	.hword	256
	.byte	2
	.byte	2
	.hword	2048
	.hword	473
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
	.zero	4
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
	.hword	256
	.byte	2
	.byte	2
	.hword	1024
	.hword	473
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
	.zero	4
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
	.byte	0
	.byte	0
	.zero	4
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
	.hword	256
	.byte	2
	.byte	2
	.hword	2090
	.hword	473
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
	.zero	4
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
	.byte	0
	.byte	0
	.zero	4
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
	.hword	256
	.byte	2
	.byte	2
	.hword	530
	.hword	473
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
	.zero	4
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
	.hword	256
	.byte	2
	.byte	2
	.hword	1024
	.hword	281
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
	.zero	4
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
	.byte	0
	.byte	0
	.zero	4
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
	.byte	0
	.byte	0
	.zero	4
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
	.byte	0
	.byte	0
	.zero	4
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
	.hword	473
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
	.zero	4
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
	.byte	0
	.byte	0
	.zero	4
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
	.hword	256
	.byte	2
	.byte	1
	.hword	1024
	.hword	273
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
	.zero	4
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
	.byte	0
	.byte	0
	.zero	4
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
	.byte	2
	.hword	2048
	.hword	479
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
	.zero	4
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
	.byte	2
	.hword	2048
	.hword	479
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
	.zero	4
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
	.hword	256
	.byte	2
	.byte	2
	.hword	2048
	.hword	279
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
	.zero	4
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
	.hword	256
	.byte	2
	.byte	2
	.hword	2048
	.hword	279
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
	.zero	4
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
	.hword	256
	.byte	2
	.byte	2
	.hword	2048
	.hword	279
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
	.zero	4
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
	.hword	256
	.byte	2
	.byte	2
	.hword	2048
	.hword	279
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
	.zero	4
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
	.hword	256
	.byte	2
	.byte	2
	.hword	2048
	.hword	279
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
	.zero	4
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
	.byte	0
	.byte	0
	.zero	4
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
	.byte	0
	.byte	0
	.zero	4
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
	.hword	192
	.byte	2
	.byte	2
	.hword	2048
	.hword	279
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
	.zero	4
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
	.hword	1473
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
	.zero	4
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
	.hword	1473
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
	.zero	4
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
	.hword	256
	.byte	2
	.byte	1
	.hword	2092
	.hword	1505
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
	.zero	4
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
	.hword	128
	.byte	2
	.byte	1
	.hword	2056
	.hword	1473
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
	.zero	4
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
	.hword	128
	.byte	2
	.byte	2
	.hword	2058
	.hword	1489
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
	.zero	4
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
	.hword	256
	.byte	2
	.byte	2
	.hword	2062
	.hword	1489
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
	.zero	4
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
	.hword	1497
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
	.zero	4
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
	.hword	256
	.byte	2
	.byte	2
	.hword	1066
	.hword	1497
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
	.zero	4
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
	.hword	128
	.byte	2
	.byte	2
	.hword	2050
	.hword	401
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
	.zero	4
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
	.hword	1497
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
	.zero	4
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
	.hword	1473
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
	.zero	4
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
	.hword	1497
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
	.zero	4
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
	.hword	1497
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
	.zero	4
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
	.hword	1497
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
	.zero	4
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
	.hword	1497
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
	.zero	4
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
	.hword	1497
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
	.zero	4
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
	.hword	1473
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
	.zero	4
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
	.hword	256
	.byte	2
	.byte	2
	.hword	2082
	.hword	473
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
	.zero	4
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
	.hword	1497
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
	.zero	4
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
	.hword	256
	.byte	2
	.byte	1
	.hword	1060
	.hword	1473
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
	.zero	4
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
	.hword	256
	.byte	2
	.byte	2
	.hword	2090
	.hword	1241
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
	.zero	4
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
	.hword	256
	.byte	2
	.byte	1
	.hword	2092
	.hword	1473
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
	.zero	4
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
	.hword	473
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
	.zero	4
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
	.hword	473
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
	.zero	4
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
	.hword	256
	.byte	2
	.byte	2
	.hword	2138
	.hword	1497
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
	.zero	4
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
	.hword	256
	.byte	2
	.byte	2
	.hword	2062
	.hword	473
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
	.zero	4
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
	.hword	256
	.byte	2
	.byte	2
	.hword	1058
	.hword	1497
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
	.zero	4
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
	.hword	128
	.byte	2
	.byte	2
	.hword	2048
	.hword	473
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
	.zero	4
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
	.hword	128
	.byte	2
	.byte	2
	.hword	2048
	.hword	505
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
	.zero	4
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
	.hword	128
	.byte	2
	.byte	2
	.hword	2076
	.hword	409
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
	.zero	4
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
	.hword	128
	.byte	2
	.byte	2
	.hword	2076
	.hword	441
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
	.zero	4
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
	.hword	128
	.byte	2
	.byte	2
	.hword	1038
	.hword	281
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
	.zero	4
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
	.hword	128
	.byte	2
	.byte	2
	.hword	2076
	.hword	1169
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
	.zero	4
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
	.byte	1
	.byte	0
	.zero	4
	.section	.data.NandOptPara,"aw",@progbits
	.align	3
	.set	.LANCHOR146,. + 0
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
	.section	.data.SamsungRefValue,"aw",@progbits
	.align	3
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
	.section	.data.Toshiba15RefValue,"aw",@progbits
	.align	3
	.set	.LANCHOR9,. + 0
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
	.section	.data.ToshibaA19RefValue,"aw",@progbits
	.align	3
	.set	.LANCHOR10,. + 0
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
	.section	.data.ToshibaRefValue,"aw",@progbits
	.align	3
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
	.section	.data.ftl_gc_temp_block_bops_scan_page_addr,"aw",@progbits
	.align	1
	.set	.LANCHOR245,. + 0
	.type	ftl_gc_temp_block_bops_scan_page_addr, %object
	.size	ftl_gc_temp_block_bops_scan_page_addr, 2
ftl_gc_temp_block_bops_scan_page_addr:
	.hword	-1
	.section	.data.gFtlInitStatus,"aw",@progbits
	.align	2
	.set	.LANCHOR247,. + 0
	.type	gFtlInitStatus, %object
	.size	gFtlInitStatus, 4
gFtlInitStatus:
	.word	-1
	.section	.data.gNandParaInfo,"aw",@progbits
	.align	3
	.set	.LANCHOR31,. + 0
	.type	gNandParaInfo, %object
	.size	gNandParaInfo, 32
gNandParaInfo:
	.byte	0
	.byte	0
	.zero	5
	.byte	0
	.byte	1
	.byte	8
	.hword	128
	.byte	2
	.byte	1
	.hword	2048
	.hword	0
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
	.zero	4
	.section	.data.gSlcNandParaInfo,"aw",@progbits
	.align	3
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
	.hword	64
	.byte	1
	.byte	1
	.hword	1024
	.hword	256
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
	.zero	4
	.section	.data.power_up_flag,"aw",@progbits
	.align	2
	.type	power_up_flag, %object
	.size	power_up_flag, 4
power_up_flag:
	.word	1
	.section	.data.random_seed,"aw",@progbits
	.align	3
	.set	.LANCHOR5,. + 0
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
	.section	.data.refValueDefault,"aw",@progbits
	.align	3
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
	.section	.rodata.FlashDdrTunningRead.str1.1,"aMS",@progbits,1
.LC9:
	.string	"sdr read ok %x ecc=%d\n"
.LC10:
	.string	"sync para %d\n"
.LC11:
	.string	"TOG mode Read error %x %x\n"
	.section	.rodata.FlashEraseSLc2KBlocks.str1.1,"aMS",@progbits,1
.LC1:
	.string	"FlashEraseBlocks pageAddr error %x\n"
	.section	.rodata.FlashInit.str1.1,"aMS",@progbits,1
.LC24:
	.string	"No.%d FLASH ID:%x %x %x %x %x %x\n"
.LC25:
	.string	"FlashLoadPhyInfo fail %x!!\n"
	.section	.rodata.FlashProgSlc2KPages.str1.1,"aMS",@progbits,1
.LC30:
	.string	"prog error: = %x\n"
.LC31:
	.string	"prog read error: = %x\n"
.LC32:
	.string	"prog read REFRESH: = %x\n"
.LC33:
	.string	"prog read s error: = %x %x %x\n"
.LC34:
	.string	"prog read d error: = %x %x %x\n"
	.section	.rodata.FlashReadFacBbtData.str1.1,"aMS",@progbits,1
.LC59:
	.string	"BBT:"
	.section	.rodata.FlashReadIdbDataRaw.str1.1,"aMS",@progbits,1
.LC15:
	.string	"ECC:%d\n"
	.section	.rodata.FlashReadPage.str1.1,"aMS",@progbits,1
.LC12:
	.string	"read retry status %x %x %x\n"
	.section	.rodata.FlashReadPages.str1.1,"aMS",@progbits,1
.LC29:
	.string	"ReadRetry pageadd=%x ecc=%x err=%x\n"
	.section	.rodata.FlashReadSlc2KPages.str1.1,"aMS",@progbits,1
.LC26:
	.string	"Read pageadd=%x  ecc=%x err=%x\n"
.LC27:
	.string	"data:"
.LC28:
	.string	"spare:"
	.section	.rodata.FtlBbmMapBadBlock.str1.1,"aMS",@progbits,1
.LC2:
	.string	"phyBlk = 0x%x die = %d block_in_die = 0x%x 0x%8x\n"
	.section	.rodata.FtlBbmTblFlush.str1.1,"aMS",@progbits,1
.LC35:
	.string	"FtlBbmTblFlush id=%x,page=%x,previd=%x cnt=%d\n"
.LC36:
	.string	"FtlBbmTblFlush error:%x\n"
.LC37:
	.string	"FtlBbmTblFlush error = %x error count = %d\n"
	.section	.rodata.FtlCacheWriteBack.str1.1,"aMS",@progbits,1
.LC76:
	.string	"Ftlwrite decrement_vpc_count %x = %d\n"
	.section	.rodata.FtlCheckVpc.str1.1,"aMS",@progbits,1
.LC63:
	.string	"FtlCheckVpc2 %x = %x  %x\n"
.LC64:
	.string	"free blk vpc error %x = %x  %x\n"
.LC65:
	.string	"error_flag %x\n"
	.section	.rodata.FtlDumpBlockInfo.str1.1,"aMS",@progbits,1
.LC48:
	.string	"...%s enter...\n"
.LC49:
	.string	"superBlkID = %x vpc=%x\n"
.LC50:
	.string	"flashmode = %x pagenum = %x %x\n"
.LC51:
	.string	"id = %x,%x addr= %x,spare= %x %x %x %x data=%x %x\n"
	.section	.rodata.FtlDumpSysBlock.str1.1,"aMS",@progbits,1
.LC84:
	.string	"id = %x,%x addr= %x,spare= %x %x %x %x data = %x\n"
.LC85:
	.string	":"
	.section	.rodata.FtlFreeSysBlkQueueOut.str1.1,"aMS",@progbits,1
.LC3:
	.string	"FtlFreeSysBlkQueueOut free count = %d\n"
.LC4:
	.string	"FtlFreeSysBlkQueueOut = %x, free count = %d, error\n"
	.section	.rodata.FtlGcFreeTempBlock.str1.1,"aMS",@progbits,1
.LC74:
	.string	"GC des block %x done\n"
	.section	.rodata.FtlGcScanTempBlk.str1.1,"aMS",@progbits,1
.LC72:
	.string	"FtlGcScanTempBlk Error ID %x %x!!!!!!! \n"
.LC73:
	.string	"FtlGcScanTempBlkError ID %x %x!!!!!!!\n"
	.section	.rodata.FtlInit.str1.1,"aMS",@progbits,1
.LC77:
	.string	"FTL version: 5.0.63 20200923"
.LC78:
	.string	"...%s: no bad block mapping table, format device\n"
.LC79:
	.string	"...%s FtlSysBlkInit error ,format device!\n"
	.section	.rodata.FtlLoadEctTbl.str1.1,"aMS",@progbits,1
.LC45:
	.string	"no ect"
	.section	.rodata.FtlLoadSysInfo.str1.1,"aMS",@progbits,1
.LC47:
	.string	"id = %x,%x addr= %x,spare= %x %x %x %x data= %x\n"
	.section	.rodata.FtlLowFormat.str1.1,"aMS",@progbits,1
.LC75:
	.string	"too many bad block  = %d %d\n"
	.section	.rodata.FtlMapWritePage.str1.1,"aMS",@progbits,1
.LC42:
	.string	"FtlMapWritePage error = %x\n"
.LC43:
	.string	"FtlMapWritePage error = %x error count = %d\n"
	.section	.rodata.FtlRecoverySuperblock.str1.1,"aMS",@progbits,1
.LC69:
	.string	"RSB refresh addr %x\n"
.LC70:
	.string	"spuer block %x vpn is 0\n "
.LC71:
	.string	"g_recovery_ppa %x ver %x\n "
	.section	.rodata.FtlScanAllBlock.str1.1,"aMS",@progbits,1
.LC52:
	.string	"blk = %x vpc=%x mode = %x\n"
.LC53:
	.string	"mlc id = %x,%x addr= %x,spare= %x %x %x %x data=%x %x\n"
.LC54:
	.string	"slc id = %x,%x addr= %x,spare= %x %x %x %x data=%x %x\n"
	.section	.rodata.FtlVendorPartRead.str1.1,"aMS",@progbits,1
.LC44:
	.string	"FtlVendorPartRead refresh = %x phyAddr = %x\n"
	.section	.rodata.FtlVpcTblFlush.str1.1,"aMS",@progbits,1
.LC40:
	.string	"FtlVpcTblFlush error = %x error count = %d\n"
	.section	.rodata.FtlWrite.str1.1,"aMS",@progbits,1
.LC83:
	.string	"FtlWrite: lpa error:%x %x\n"
	.section	.rodata.Ftl_load_ext_data.str1.1,"aMS",@progbits,1
.LC46:
	.string	"slc mode"
	.section	.rodata.Ftlscanalldata.str1.1,"aMS",@progbits,1
.LC66:
	.string	"Ftlscanalldata = %x\n"
.LC67:
	.string	"scan lpa = %x ppa= %x\n"
.LC68:
	.string	"lba = %x,addr= %x,spare= %x %x %x %x data=%x %x\n"
	.section	.rodata.HynixGetReadRetryDefault.str1.1,"aMS",@progbits,1
.LC22:
	.string	"otp error! %d"
.LC23:
	.string	"rr"
	.section	.rodata.INSERT_DATA_LIST.str1.1,"aMS",@progbits,1
.LC5:
	.string	"\n!!!!! error @ func:%s - line:%d\n"
.LC6:
	.string	"!!!!! FTL sys Error !!!!!"
.LC7:
	.string	"%s\n"
	.section	.rodata.MicronReadRetrial.str1.1,"aMS",@progbits,1
.LC13:
	.string	"micron RR %d row=%x,count %d,status=%d\n"
	.section	.rodata.__func__.10027,"a",@progbits
	.align	3
	.set	.LANCHOR96,. + 0
	.type	__func__.10027, %object
	.size	__func__.10027, 22
__func__.10027:
	.string	"List_update_data_list"
	.section	.rodata.__func__.10034,"a",@progbits
	.align	3
	.set	.LANCHOR237,. + 0
	.type	__func__.10034, %object
	.size	__func__.10034, 20
__func__.10034:
	.string	"ftl_load_l2p_region"
	.section	.rodata.__func__.10065,"a",@progbits
	.align	3
	.set	.LANCHOR97,. + 0
	.type	__func__.10065, %object
	.size	__func__.10065, 26
__func__.10065:
	.string	"ftl_map_blk_alloc_new_blk"
	.section	.rodata.__func__.10075,"a",@progbits
	.align	3
	.set	.LANCHOR221,. + 0
	.type	__func__.10075, %object
	.size	__func__.10075, 15
__func__.10075:
	.string	"ftl_map_blk_gc"
	.section	.rodata.__func__.10088,"a",@progbits
	.align	3
	.set	.LANCHOR222,. + 0
	.type	__func__.10088, %object
	.size	__func__.10088, 31
__func__.10088:
	.string	"Ftl_write_map_blk_to_last_page"
	.section	.rodata.__func__.10101,"a",@progbits
	.align	3
	.set	.LANCHOR223,. + 0
	.type	__func__.10101, %object
	.size	__func__.10101, 16
__func__.10101:
	.string	"FtlMapWritePage"
	.section	.rodata.__func__.10121,"a",@progbits
	.align	3
	.set	.LANCHOR100,. + 0
	.type	__func__.10121, %object
	.size	__func__.10121, 22
__func__.10121:
	.string	"select_l2p_ram_region"
	.section	.rodata.__func__.10137,"a",@progbits
	.align	3
	.set	.LANCHOR236,. + 0
	.type	__func__.10137, %object
	.size	__func__.10137, 9
__func__.10137:
	.string	"log2phys"
	.section	.rodata.__func__.10199,"a",@progbits
	.align	3
	.set	.LANCHOR219,. + 0
	.type	__func__.10199, %object
	.size	__func__.10199, 15
__func__.10199:
	.string	"FtlVpcTblFlush"
	.section	.rodata.__func__.10218,"a",@progbits
	.align	3
	.set	.LANCHOR229,. + 0
	.type	__func__.10218, %object
	.size	__func__.10218, 14
__func__.10218:
	.string	"FtlScanSysBlk"
	.section	.rodata.__func__.10273,"a",@progbits
	.align	3
	.set	.LANCHOR230,. + 0
	.type	__func__.10273, %object
	.size	__func__.10273, 15
__func__.10273:
	.string	"FtlLoadSysInfo"
	.section	.rodata.__func__.10284,"a",@progbits
	.align	3
	.set	.LANCHOR238,. + 0
	.type	__func__.10284, %object
	.size	__func__.10284, 12
__func__.10284:
	.string	"FtlCheckVpc"
	.section	.rodata.__func__.10316,"a",@progbits
	.align	3
	.set	.LANCHOR233,. + 0
	.type	__func__.10316, %object
	.size	__func__.10316, 17
__func__.10316:
	.string	"FtlDumpBlockInfo"
	.section	.rodata.__func__.10335,"a",@progbits
	.align	3
	.set	.LANCHOR234,. + 0
	.type	__func__.10335, %object
	.size	__func__.10335, 16
__func__.10335:
	.string	"FtlScanAllBlock"
	.section	.rodata.__func__.10440,"a",@progbits
	.align	3
	.set	.LANCHOR239,. + 0
	.type	__func__.10440, %object
	.size	__func__.10440, 16
__func__.10440:
	.string	"FtlReUsePrevPpa"
	.section	.rodata.__func__.10473,"a",@progbits
	.align	3
	.set	.LANCHOR240,. + 0
	.type	__func__.10473, %object
	.size	__func__.10473, 22
__func__.10473:
	.string	"FtlRecoverySuperblock"
	.section	.rodata.__func__.10527,"a",@progbits
	.align	3
	.set	.LANCHOR103,. + 0
	.type	__func__.10527, %object
	.size	__func__.10527, 16
__func__.10527:
	.string	"make_superblock"
	.section	.rodata.__func__.10547,"a",@progbits
	.align	3
	.set	.LANCHOR143,. + 0
	.type	__func__.10547, %object
	.size	__func__.10547, 18
__func__.10547:
	.string	"SupperBlkListInit"
	.section	.rodata.__func__.10593,"a",@progbits
	.align	3
	.set	.LANCHOR235,. + 0
	.type	__func__.10593, %object
	.size	__func__.10593, 17
__func__.10593:
	.string	"ftl_scan_all_ppa"
	.section	.rodata.__func__.10638,"a",@progbits
	.align	3
	.set	.LANCHOR212,. + 0
	.type	__func__.10638, %object
	.size	__func__.10638, 25
__func__.10638:
	.string	"allocate_data_superblock"
	.section	.rodata.__func__.10652,"a",@progbits
	.align	3
	.set	.LANCHOR228,. + 0
	.type	__func__.10652, %object
	.size	__func__.10652, 29
__func__.10652:
	.string	"allocate_new_data_superblock"
	.section	.rodata.__func__.10658,"a",@progbits
	.align	3
	.set	.LANCHOR217,. + 0
	.type	__func__.10658, %object
	.size	__func__.10658, 19
__func__.10658:
	.string	"get_new_active_ppa"
	.section	.rodata.__func__.10669,"a",@progbits
	.align	3
	.set	.LANCHOR215,. + 0
	.type	__func__.10669, %object
	.size	__func__.10669, 16
__func__.10669:
	.string	"update_vpc_list"
	.section	.rodata.__func__.10674,"a",@progbits
	.align	3
	.set	.LANCHOR216,. + 0
	.type	__func__.10674, %object
	.size	__func__.10674, 20
__func__.10674:
	.string	"decrement_vpc_count"
	.section	.rodata.__func__.10742,"a",@progbits
	.align	3
	.set	.LANCHOR246,. + 0
	.type	__func__.10742, %object
	.size	__func__.10742, 19
__func__.10742:
	.string	"FtlGcFreeTempBlock"
	.section	.rodata.__func__.10843,"a",@progbits
	.align	3
	.set	.LANCHOR251,. + 0
	.type	__func__.10843, %object
	.size	__func__.10843, 10
__func__.10843:
	.string	"ftl_do_gc"
	.section	.rodata.__func__.9622,"a",@progbits
	.align	3
	.set	.LANCHOR255,. + 0
	.type	__func__.9622, %object
	.size	__func__.9622, 8
__func__.9622:
	.string	"FtlInit"
	.section	.rodata.__func__.9726,"a",@progbits
	.align	3
	.set	.LANCHOR258,. + 0
	.type	__func__.9726, %object
	.size	__func__.9726, 9
__func__.9726:
	.string	"FtlWrite"
	.section	.rodata.__func__.9816,"a",@progbits
	.align	3
	.set	.LANCHOR127,. + 0
	.type	__func__.9816, %object
	.size	__func__.9816, 14
__func__.9816:
	.string	"FtlBbt2Bitmap"
	.section	.rodata.__func__.9862,"a",@progbits
	.align	3
	.set	.LANCHOR220,. + 0
	.type	__func__.9862, %object
	.size	__func__.9862, 11
__func__.9862:
	.string	"FtlLoadBbt"
	.section	.rodata.__func__.9955,"a",@progbits
	.align	3
	.set	.LANCHOR91,. + 0
	.type	__func__.9955, %object
	.size	__func__.9955, 17
__func__.9955:
	.string	"INSERT_FREE_LIST"
	.section	.rodata.__func__.9959,"a",@progbits
	.align	3
	.set	.LANCHOR88,. + 0
	.type	__func__.9959, %object
	.size	__func__.9959, 17
__func__.9959:
	.string	"INSERT_DATA_LIST"
	.section	.rodata.__func__.9997,"a",@progbits
	.align	3
	.set	.LANCHOR92,. + 0
	.type	__func__.9997, %object
	.size	__func__.9997, 17
__func__.9997:
	.string	"List_remove_node"
	.section	.rodata.decrement_vpc_count.str1.1,"aMS",@progbits,1
.LC38:
	.string	"decrement_vpc_count %x = %d\n"
.LC39:
	.string	"decrement_vpc_count %x = %d in free list\n"
	.section	.rodata.dump_map_info.str1.1,"aMS",@progbits,1
.LC86:
	.string	"phyBlk = %x,addr= %x,spare= %x %x %x %x data=%x %x\n"
.LC87:
	.string	"Mblk:"
.LC88:
	.string	"L2P:"
.LC89:
	.string	"L2PC:"
	.section	.rodata.ftl_fix_nand_power_lost_error.str1.1,"aMS",@progbits,1
.LC81:
	.string	"fix power lost blk = %x vpc=%x\n"
.LC82:
	.string	"erase power lost blk = %x vpc=%x\n"
	.section	.rodata.ftl_map_blk_alloc_new_blk.str1.1,"aMS",@progbits,1
.LC8:
	.string	"FtlFreeSysBlkQueueOut = %x, free count = %d\n"
	.section	.rodata.ftl_map_blk_gc.str1.1,"aMS",@progbits,1
.LC41:
	.string	"page map lost: %x %x\n"
	.section	.rodata.ftl_scan_all_ppa.str1.1,"aMS",@progbits,1
.LC55:
	.string	"ftl_scan_all_ppa blk %x page %x flag: %x\n"
.LC56:
	.string	"ftl_scan_all_ppa blk %x page %x flag: %x ............... is bad block\n"
.LC57:
	.string	"addr= %x, status= %d,spare= %x %x %x %x data=%x %x\n"
.LC58:
	.string	"%s finished\n"
	.section	.rodata.idb_write_data.str1.1,"aMS",@progbits,1
.LC16:
	.string	"1 write_idblock fix data %x %x %x\n"
.LC17:
	.string	"write_idblock fail! %x %x %x %x\n"
.LC18:
	.string	"write_idblock fail! %x\n"
	.section	.rodata.log2phys.str1.1,"aMS",@progbits,1
.LC60:
	.string	"region_id = %x phyAddr = %x\n"
.LC61:
	.string	"map_ppn:"
.LC62:
	.string	"load_l2p_region refresh = %x phyAddr = %x\n"
	.section	.rodata.rk_ftl_init.str1.1,"aMS",@progbits,1
.LC80:
	.string	"FtlInit %x\n"
	.section	.rodata.rknand_print_hex.str1.1,"aMS",@progbits,1
.LC19:
	.string	"%s 0x%x:"
.LC20:
	.string	"%x "
.LC21:
	.string	""
	.section	.rodata.samsung_14nm_mlc_rr,"a",@progbits
	.align	3
	.set	.LANCHOR151,. + 0
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
	.set	.LANCHOR150,. + 0
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
.LC14:
	.string	"samsung RR %d row=%x,count %d,status=%d\n"
	.hidden	free
