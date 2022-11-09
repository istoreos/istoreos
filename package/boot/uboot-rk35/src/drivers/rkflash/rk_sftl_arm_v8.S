/*
 * Copyright (c) 2018 Fuzhou Rockchip Electronics Co., Ltd
 *
 * SPDX-License-Identifier:    GPL-2.0
 * date: 2021-03-29
 */
	.arch armv8-a+nosimd
	.file	"rk_sftl.c"
	.section	.text.l2p_addr_tran.isra.0,"ax",@progbits
	.align	2
	.type	l2p_addr_tran.isra.0, %function
l2p_addr_tran.isra.0:
	adrp	x4, .LANCHOR0
	add	x4, x4, :lo12:.LANCHOR0
	ldrh	w3, [x4, 8]
	ldrh	w6, [x4, 10]
	ldrh	w4, [x4, 14]
	cmp	w4, 4
	bne	.L2
	lsr	w3, w3, 1
	ubfiz	w6, w6, 1, 15
.L2:
	lsr	w5, w0, 10
	and	w0, w0, 1023
	and	w4, w5, 65535
	and	w5, w5, 65535
	udiv	w4, w4, w3
	msub	w3, w3, w4, w5
	madd	w3, w3, w6, w0
	mov	w0, 0
	str	w3, [x1]
	str	w4, [x2]
	ret
	.size	l2p_addr_tran.isra.0, .-l2p_addr_tran.isra.0
	.section	.text.Ftl_log2,"ax",@progbits
	.align	2
	.global	Ftl_log2
	.type	Ftl_log2, %function
Ftl_log2:
	mov	w2, 1
	mov	w1, 0
.L4:
	cmp	w2, w0
	bls	.L5
	sub	w0, w1, #1
	ret
.L5:
	add	w1, w1, 1
	lsl	w2, w2, 1
	and	w1, w1, 65535
	b	.L4
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
	adrp	x2, .LANCHOR3
	csel	w0, w0, w1, cs
	adrp	x1, .LANCHOR1
	and	w0, w0, 65535
	str	w0, [x1, #:lo12:.LANCHOR1]
	adrp	x1, .LANCHOR2
	ldrh	w1, [x1, #:lo12:.LANCHOR2]
	mul	w1, w1, w0
	str	w1, [x2, #:lo12:.LANCHOR3]
	adrp	x2, .LANCHOR5
	ldrh	w2, [x2, #:lo12:.LANCHOR5]
	sub	w0, w2, w0
	adrp	x2, .LANCHOR4
	strh	w0, [x2, #:lo12:.LANCHOR4]
	adrp	x0, .LANCHOR7
	ldr	w0, [x0, #:lo12:.LANCHOR7]
	sub	w1, w0, w1
	adrp	x0, .LANCHOR6
	str	w1, [x0, #:lo12:.LANCHOR6]
	mov	w0, 0
	ret
	.size	FtlSysBlkNumInit, .-FtlSysBlkNumInit
	.section	.text.FtlConstantsInit,"ax",@progbits
	.align	2
	.global	FtlConstantsInit
	.type	FtlConstantsInit, %function
FtlConstantsInit:
	stp	x29, x30, [sp, -16]!
	mov	x5, x0
	adrp	x2, .LANCHOR10
	adrp	x1, .LANCHOR5
	add	x29, sp, 0
	ldrh	w3, [x0]
	adrp	x0, .LANCHOR8
	ldrh	w4, [x5, 2]
	adrp	x6, .LANCHOR11
	strh	w3, [x0, #:lo12:.LANCHOR8]
	adrp	x0, .LANCHOR9
	ldrh	w7, [x5, 14]
	strh	w4, [x0, #:lo12:.LANCHOR9]
	ldrh	w8, [x5, 4]
	cmp	w7, 4
	ldrh	w0, [x5, 6]
	strh	w8, [x2, #:lo12:.LANCHOR10]
	strh	w0, [x1, #:lo12:.LANCHOR5]
	strh	w7, [x6, #:lo12:.LANCHOR11]
	bne	.L9
	lsr	w0, w0, 1
	strh	w0, [x1, #:lo12:.LANCHOR5]
	mov	w0, 8
	strh	w0, [x6, #:lo12:.LANCHOR11]
.L10:
	adrp	x7, .LANCHOR12
	add	x7, x7, :lo12:.LANCHOR12
	mov	x0, 0
.L11:
	strb	w0, [x0, x7]
	add	x0, x0, 1
	cmp	x0, 32
	bne	.L11
	adrp	x0, .LANCHOR13
	mov	w7, 5
	cmp	w3, 1
	strh	w7, [x0, #:lo12:.LANCHOR13]
	adrp	x7, .LANCHOR14
	strh	wzr, [x7, #:lo12:.LANCHOR14]
	bne	.L12
	strh	w3, [x0, #:lo12:.LANCHOR13]
.L12:
	adrp	x0, .LANCHOR15
	mov	w3, 640
	strh	w3, [x0, #:lo12:.LANCHOR15]
	ldrh	w0, [x2, #:lo12:.LANCHOR10]
	adrp	x2, .LANCHOR2
	ldrh	w3, [x1, #:lo12:.LANCHOR5]
	adrp	x1, .LANCHOR16
	mul	w4, w4, w0
	mul	w0, w0, w3
	and	w4, w4, 65535
	strh	w4, [x2, #:lo12:.LANCHOR2]
	and	w0, w0, 65535
	strh	w0, [x1, #:lo12:.LANCHOR16]
	bl	Ftl_log2
	ldrh	w7, [x5, 12]
	adrp	x1, .LANCHOR17
	ldrh	w6, [x6, #:lo12:.LANCHOR11]
	adrp	x8, .LANCHOR18
	strh	w0, [x1, #:lo12:.LANCHOR17]
	adrp	x0, .LANCHOR19
	mul	w1, w4, w7
	strh	w7, [x8, #:lo12:.LANCHOR18]
	strh	w7, [x0, #:lo12:.LANCHOR19]
	adrp	x0, .LANCHOR20
	strh	w1, [x0, #:lo12:.LANCHOR20]
	mov	w0, w6
	bl	Ftl_log2
	and	w10, w0, 65535
	adrp	x2, .LANCHOR21
	ubfiz	w1, w6, 9, 7
	strh	w0, [x2, #:lo12:.LANCHOR21]
	adrp	x0, .LANCHOR22
	strh	w1, [x0, #:lo12:.LANCHOR22]
	adrp	x0, .LANCHOR23
	ubfx	w1, w1, 8, 8
	strh	w1, [x0, #:lo12:.LANCHOR23]
	adrp	x0, .LANCHOR24
	ldrh	w1, [x5, 20]
	adrp	x5, .LANCHOR26
	strh	w1, [x0, #:lo12:.LANCHOR24]
	mul	w0, w4, w3
	adrp	x1, .LANCHOR7
	str	w0, [x1, #:lo12:.LANCHOR7]
	adrp	x1, .LANCHOR25
	mul	w0, w0, w6
	mul	w6, w6, w7
	mul	w0, w0, w7
	mov	x7, x2
	asr	w0, w0, 11
	str	w0, [x1, #:lo12:.LANCHOR25]
	mov	w0, 5120
	sdiv	w0, w0, w6
	and	w0, w0, 65535
	cmp	w0, 4
	bls	.L13
.L19:
	strh	w0, [x5, #:lo12:.LANCHOR26]
	adrp	x1, .LANCHOR27
	mov	w0, 640
	lsl	w3, w3, 6
	asr	w0, w0, w10
	add	w0, w0, 2
	strh	w0, [x1, #:lo12:.LANCHOR27]
	add	w0, w10, 9
	adrp	x1, .LANCHOR29
	cmp	w4, 1
	asr	w3, w3, w0
	adrp	x0, .LANCHOR28
	adrp	x6, .LANCHOR1
	strh	w3, [x0, #:lo12:.LANCHOR28]
	and	w3, w3, 65535
	mul	w0, w3, w4
	add	w3, w3, 8
	str	w0, [x1, #:lo12:.LANCHOR29]
	ldrh	w0, [x5, #:lo12:.LANCHOR26]
	udiv	w0, w0, w4
	mov	x4, x1
	add	w3, w0, w3
	beq	.L15
.L20:
	str	w3, [x6, #:lo12:.LANCHOR1]
	ldrh	w0, [x6, #:lo12:.LANCHOR1]
	bl	FtlSysBlkNumInit
	ldr	w1, [x6, #:lo12:.LANCHOR1]
	adrp	x0, .LANCHOR30
	ldp	x29, x30, [sp], 16
	str	w1, [x0, #:lo12:.LANCHOR30]
	adrp	x0, .LANCHOR6
	ldrh	w1, [x8, #:lo12:.LANCHOR18]
	ldr	w0, [x0, #:lo12:.LANCHOR6]
	lsl	w0, w0, 2
	mul	w0, w0, w1
	ldrh	w1, [x7, #:lo12:.LANCHOR21]
	add	w1, w1, 9
	lsr	w0, w0, w1
	adrp	x1, .LANCHOR31
	add	w0, w0, 2
	strh	w0, [x1, #:lo12:.LANCHOR31]
	adrp	x0, .LANCHOR32
	mov	w1, 32
	strh	w1, [x0, #:lo12:.LANCHOR32]
	adrp	x0, .LANCHOR33
	str	wzr, [x0, #:lo12:.LANCHOR33]
	ldrh	w0, [x5, #:lo12:.LANCHOR26]
	add	w0, w0, 3
	strh	w0, [x5, #:lo12:.LANCHOR26]
	ldr	w0, [x4, #:lo12:.LANCHOR29]
	add	w0, w0, 3
	str	w0, [x4, #:lo12:.LANCHOR29]
	mov	w0, 0
	ret
.L9:
	cmp	w7, 8
	bne	.L10
	cmp	w8, 1
	bne	.L10
	lsr	w0, w0, 1
	strh	w0, [x1, #:lo12:.LANCHOR5]
	mov	w0, 2
	strh	w0, [x2, #:lo12:.LANCHOR10]
	b	.L10
.L13:
	mov	w0, 4
	b	.L19
.L15:
	add	w3, w3, 4
	b	.L20
	.size	FtlConstantsInit, .-FtlConstantsInit
	.section	.text.IsBlkInVendorPart,"ax",@progbits
	.align	2
	.global	IsBlkInVendorPart
	.type	IsBlkInVendorPart, %function
IsBlkInVendorPart:
	adrp	x1, .LANCHOR34
	and	w0, w0, 65535
	ldrh	w1, [x1, #:lo12:.LANCHOR34]
	cbz	w1, .L25
	adrp	x1, .LANCHOR26
	ldrh	w2, [x1, #:lo12:.LANCHOR26]
	adrp	x1, .LANCHOR35
	ldr	x3, [x1, #:lo12:.LANCHOR35]
	mov	x1, 0
.L23:
	cmp	w2, w1, uxth
	bhi	.L24
.L25:
	mov	w0, 0
	ret
.L24:
	add	x1, x1, 1
	add	x4, x3, x1, lsl 1
	ldrh	w4, [x4, -2]
	cmp	w4, w0
	bne	.L23
	mov	w0, 1
	ret
	.size	IsBlkInVendorPart, .-IsBlkInVendorPart
	.section	.text.FtlCacheWriteBack,"ax",@progbits
	.align	2
	.global	FtlCacheWriteBack
	.type	FtlCacheWriteBack, %function
FtlCacheWriteBack:
	mov	w0, 0
	ret
	.size	FtlCacheWriteBack, .-FtlCacheWriteBack
	.section	.text.sftl_get_density,"ax",@progbits
	.align	2
	.global	sftl_get_density
	.type	sftl_get_density, %function
sftl_get_density:
	adrp	x0, .LANCHOR33
	ldr	w0, [x0, #:lo12:.LANCHOR33]
	ret
	.size	sftl_get_density, .-sftl_get_density
	.section	.text.FtlBbmMapBadBlock,"ax",@progbits
	.align	2
	.global	FtlBbmMapBadBlock
	.type	FtlBbmMapBadBlock, %function
FtlBbmMapBadBlock:
	stp	x29, x30, [sp, -32]!
	and	w1, w0, 65535
	adrp	x0, .LANCHOR16
	mov	w4, 1
	add	x29, sp, 0
	ldrh	w0, [x0, #:lo12:.LANCHOR16]
	str	x19, [sp, 16]
	adrp	x19, .LANCHOR36
	add	x19, x19, :lo12:.LANCHOR36
	udiv	w3, w1, w0
	and	w2, w3, 65535
	msub	w3, w3, w0, w1
	add	x0, x19, x2, uxth 3
	and	w3, w3, 65535
	ldr	x0, [x0, 32]
	ubfx	x5, x3, 5, 11
	lsl	x5, x5, 2
	lsl	w4, w4, w3
	ldr	w6, [x0, x5]
	orr	w4, w4, w6
	str	w4, [x0, x5]
	adrp	x0, .LC0
	add	x0, x0, :lo12:.LC0
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
	adrp	x1, .LANCHOR16
	and	w0, w0, 65535
	ldrh	w1, [x1, #:lo12:.LANCHOR16]
	udiv	w2, w0, w1
	msub	w0, w2, w1, w0
	adrp	x1, .LANCHOR36
	add	x1, x1, :lo12:.LANCHOR36
	add	x2, x1, x2, uxth 3
	and	w0, w0, 65535
	ubfx	x3, x0, 5, 11
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
	adrp	x2, .LANCHOR10
	and	w0, w0, 65535
	adrp	x4, .LANCHOR16
	and	w1, w1, 65535
	ldrh	w2, [x2, #:lo12:.LANCHOR10]
	ldrh	w4, [x4, #:lo12:.LANCHOR16]
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
	adrp	x0, .LANCHOR10
	ldrh	w1, [x0, #:lo12:.LANCHOR10]
	adrp	x0, .LANCHOR16
	ldrh	w2, [x0, #:lo12:.LANCHOR16]
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
	adrp	x0, .LANCHOR16
	ldrh	w1, [x0, #:lo12:.LANCHOR16]
	udiv	w0, w2, w1
	msub	w0, w0, w1, w2
	adrp	x1, .LANCHOR10
	ldrh	w1, [x1, #:lo12:.LANCHOR10]
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
	bls	.L37
	sub	w1, w0, w1
	cmp	w1, w2
	cset	w0, ls
	ret
.L37:
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
	adrp	x0, .LANCHOR37+6
	ldrh	w0, [x0, #:lo12:.LANCHOR37+6]
	cmp	w0, 0
	cset	w0, eq
	ret
	.size	FtlFreeSysBlkQueueEmpty, .-FtlFreeSysBlkQueueEmpty
	.section	.text.FtlFreeSysBlkQueueFull,"ax",@progbits
	.align	2
	.global	FtlFreeSysBlkQueueFull
	.type	FtlFreeSysBlkQueueFull, %function
FtlFreeSysBlkQueueFull:
	adrp	x0, .LANCHOR37+6
	ldrh	w0, [x0, #:lo12:.LANCHOR37+6]
	cmp	w0, 1024
	cset	w0, eq
	ret
	.size	FtlFreeSysBlkQueueFull, .-FtlFreeSysBlkQueueFull
	.section	.text.FtlFreeSysBLkSort,"ax",@progbits
	.align	2
	.global	FtlFreeSysBLkSort
	.type	FtlFreeSysBLkSort, %function
FtlFreeSysBLkSort:
	adrp	x0, .LANCHOR37
	add	x1, x0, :lo12:.LANCHOR37
	ldrh	w2, [x1, 6]
	cbz	w2, .L41
	adrp	x2, .LANCHOR38+28
	ldrh	w3, [x1, 2]
	mov	w6, 0
	mov	w4, 0
	ldrh	w5, [x2, #:lo12:.LANCHOR38+28]
	ldrh	w2, [x1, 4]
	and	w5, w5, 31
.L43:
	cmp	w5, w4
	bgt	.L44
	cbz	w6, .L41
	add	x0, x0, :lo12:.LANCHOR37
	strh	w3, [x0, 2]
	strh	w2, [x0, 4]
.L41:
	ret
.L44:
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
	b	.L43
	.size	FtlFreeSysBLkSort, .-FtlFreeSysBLkSort
	.section	.text.IsInFreeQueue,"ax",@progbits
	.align	2
	.global	IsInFreeQueue
	.type	IsInFreeQueue, %function
IsInFreeQueue:
	adrp	x1, .LANCHOR37
	add	x1, x1, :lo12:.LANCHOR37
	and	w0, w0, 65535
	ldrh	w4, [x1, 6]
	cmp	w4, 1024
	beq	.L54
	ldrh	w5, [x1, 2]
	mov	w3, 0
.L52:
	cmp	w3, w4
	bcc	.L53
.L54:
	mov	w0, 0
	ret
.L53:
	add	w2, w3, w5
	ubfiz	x2, x2, 1, 10
	add	x2, x1, x2
	ldrh	w2, [x2, 8]
	cmp	w2, w0
	beq	.L55
	add	w3, w3, 1
	b	.L52
.L55:
	mov	w0, 1
	ret
	.size	IsInFreeQueue, .-IsInFreeQueue
	.section	.text.insert_data_list,"ax",@progbits
	.align	2
	.global	insert_data_list
	.type	insert_data_list, %function
insert_data_list:
	adrp	x1, .LANCHOR4
	and	w0, w0, 65535
	ldrh	w12, [x1, #:lo12:.LANCHOR4]
	cmp	w12, w0
	bls	.L58
	adrp	x1, .LANCHOR39
	mov	w8, 6
	ldr	x4, [x1, #:lo12:.LANCHOR39]
	umull	x10, w0, w8
	mov	w1, -1
	add	x3, x4, x10
	strh	w1, [x3, 2]
	strh	w1, [x4, x10]
	adrp	x1, .LANCHOR40
	mov	x15, x1
	ldr	x7, [x1, #:lo12:.LANCHOR40]
	cbnz	x7, .L59
	str	x3, [x1, #:lo12:.LANCHOR40]
.L58:
	mov	w0, 0
	ret
.L59:
	adrp	x1, .LANCHOR41
	mov	x2, -6148914691236517206
	movk	x2, 0xaaab, lsl 0
	mov	w6, 0
	ldr	x13, [x1, #:lo12:.LANCHOR41]
	ubfiz	x1, x0, 1, 16
	mov	w16, 65535
	ldrh	w5, [x13, x1]
	ldrh	w1, [x3, 4]
	cmp	w1, 0
	mul	w5, w5, w1
	sub	x1, x7, x4
	asr	x1, x1, 1
	csinv	w5, w5, wzr, ne
	mul	x1, x1, x2
	mov	x2, x7
	and	w1, w1, 65535
.L64:
	add	w6, w6, 1
	and	w6, w6, 65535
	cmp	w12, w6
	bcc	.L58
	cmp	w1, w0
	beq	.L58
	ldrh	w14, [x2, 4]
	cbz	w14, .L62
	ubfiz	x11, x1, 1, 16
	ldrh	w11, [x13, x11]
	mul	w11, w11, w14
	cmp	w5, w11
	bls	.L62
	ldrh	w11, [x2]
	cmp	w11, w16
	bne	.L63
	strh	w1, [x3, 2]
	strh	w0, [x2]
	adrp	x0, .LANCHOR42
	str	x3, [x0, #:lo12:.LANCHOR42]
	b	.L58
.L63:
	umaddl	x2, w11, w8, x4
	mov	w1, w11
	b	.L64
.L62:
	strh	w1, [x4, x10]
	cmp	x2, x7
	ldrh	w1, [x2, 2]
	strh	w1, [x3, 2]
	bne	.L65
	strh	w0, [x2, 2]
	str	x3, [x15, #:lo12:.LANCHOR40]
	b	.L58
.L65:
	ldrh	w1, [x2, 2]
	mov	w3, 6
	umull	x1, w1, w3
	strh	w0, [x4, x1]
	strh	w0, [x2, 2]
	b	.L58
	.size	insert_data_list, .-insert_data_list
	.section	.text.INSERT_DATA_LIST,"ax",@progbits
	.align	2
	.global	INSERT_DATA_LIST
	.type	INSERT_DATA_LIST, %function
INSERT_DATA_LIST:
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
	bl	insert_data_list
	adrp	x1, .LANCHOR43
	ldrh	w0, [x1, #:lo12:.LANCHOR43]
	add	w0, w0, 1
	and	w0, w0, 65535
	strh	w0, [x1, #:lo12:.LANCHOR43]
	adrp	x1, .LANCHOR4
	ldrh	w1, [x1, #:lo12:.LANCHOR4]
	cmp	w1, w0
	bcs	.L70
	ldp	x29, x30, [sp], 16
	mov	w2, 214
	adrp	x1, .LANCHOR44
	adrp	x0, .LC1
	add	x1, x1, :lo12:.LANCHOR44
	add	x0, x0, :lo12:.LC1
	b	printf
.L70:
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
	beq	.L74
	adrp	x1, .LANCHOR39
	mov	w6, 6
	ldr	x3, [x1, #:lo12:.LANCHOR39]
	umull	x8, w0, w6
	mov	w1, -1
	add	x4, x3, x8
	strh	w1, [x4, 2]
	strh	w1, [x3, x8]
	adrp	x1, .LANCHOR45
	mov	x12, x1
	ldr	x5, [x1, #:lo12:.LANCHOR45]
	cbnz	x5, .L75
	str	x4, [x1, #:lo12:.LANCHOR45]
.L74:
	mov	w0, 0
	ret
.L75:
	adrp	x1, .LANCHOR46
	mov	x2, -6148914691236517206
	movk	x2, 0xaaab, lsl 0
	ldr	x11, [x1, #:lo12:.LANCHOR46]
	ubfiz	x1, x0, 1, 16
	ldrh	w13, [x11, x1]
	sub	x1, x5, x3
	asr	x1, x1, 1
	mul	x1, x1, x2
	mov	x2, x5
	and	w1, w1, 65535
.L78:
	ubfiz	x10, x1, 1, 16
	ldrh	w10, [x11, x10]
	cmp	w10, w13
	bcs	.L76
	ldrh	w10, [x2]
	cmp	w10, w7
	bne	.L77
	strh	w1, [x4, 2]
	strh	w0, [x2]
	b	.L74
.L77:
	umaddl	x2, w10, w6, x3
	mov	w1, w10
	b	.L78
.L76:
	ldrh	w6, [x2, 2]
	cmp	x2, x5
	strh	w6, [x4, 2]
	strh	w1, [x3, x8]
	bne	.L79
	strh	w0, [x2, 2]
	str	x4, [x12, #:lo12:.LANCHOR45]
	b	.L74
.L79:
	ldrh	w1, [x2, 2]
	mov	w4, 6
	umull	x1, w1, w4
	strh	w0, [x3, x1]
	strh	w0, [x2, 2]
	b	.L74
	.size	insert_free_list, .-insert_free_list
	.section	.text.INSERT_FREE_LIST,"ax",@progbits
	.align	2
	.global	INSERT_FREE_LIST
	.type	INSERT_FREE_LIST, %function
INSERT_FREE_LIST:
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
	bl	insert_free_list
	adrp	x1, .LANCHOR47
	ldrh	w0, [x1, #:lo12:.LANCHOR47]
	add	w0, w0, 1
	and	w0, w0, 65535
	strh	w0, [x1, #:lo12:.LANCHOR47]
	adrp	x1, .LANCHOR4
	ldrh	w1, [x1, #:lo12:.LANCHOR4]
	cmp	w1, w0
	bcs	.L80
	ldp	x29, x30, [sp], 16
	mov	w2, 207
	adrp	x1, .LANCHOR48
	adrp	x0, .LC1
	add	x1, x1, :lo12:.LANCHOR48
	add	x0, x0, :lo12:.LC1
	b	printf
.L80:
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
	adrp	x20, .LANCHOR39
	stp	x21, x22, [sp, 32]
	mov	x22, x0
	mov	w0, 6
	str	x23, [sp, 48]
	ldr	x23, [x20, #:lo12:.LANCHOR39]
	umull	x21, w1, w0
	mov	w0, 65535
	add	x19, x23, x21
	ldrh	w1, [x19, 2]
	cmp	w1, w0
	bne	.L84
	ldr	x0, [x22]
	cmp	x19, x0
	beq	.L84
	adrp	x1, .LANCHOR49
	adrp	x0, .LC1
	mov	w2, 372
	add	x1, x1, :lo12:.LANCHOR49
	add	x0, x0, :lo12:.LC1
	bl	printf
.L84:
	ldr	x0, [x22]
	mov	w1, 65535
	cmp	x19, x0
	ldrh	w0, [x23, x21]
	bne	.L85
	cmp	w0, w1
	bne	.L86
	str	xzr, [x22]
.L87:
	mov	w0, -1
	strh	w0, [x23, x21]
	strh	w0, [x19, 2]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
.L86:
	ldr	x1, [x20, #:lo12:.LANCHOR39]
	mov	w2, 6
	umaddl	x0, w0, w2, x1
	mov	w1, -1
	str	x0, [x22]
	strh	w1, [x0, 2]
	b	.L87
.L85:
	cmp	w0, w1
	ldrh	w1, [x19, 2]
	bne	.L88
	cmp	w1, w0
	beq	.L87
	mov	w0, 6
	mov	w2, -1
	umull	x1, w1, w0
	ldr	x0, [x20, #:lo12:.LANCHOR39]
	strh	w2, [x0, x1]
	b	.L87
.L88:
	ldr	x2, [x20, #:lo12:.LANCHOR39]
	mov	w3, 6
	umaddl	x4, w0, w3, x2
	strh	w1, [x4, 2]
	ldrh	w1, [x19, 2]
	umull	x1, w1, w3
	strh	w0, [x2, x1]
	b	.L87
	.size	List_remove_node, .-List_remove_node
	.section	.text.List_pop_index_node,"ax",@progbits
	.align	2
	.global	List_pop_index_node
	.type	List_pop_index_node, %function
List_pop_index_node:
	ldr	x2, [x0]
	cbz	x2, .L96
	stp	x29, x30, [sp, -32]!
	adrp	x3, .LANCHOR39
	and	w1, w1, 65535
	mov	w4, 65535
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	w5, 6
	ldr	x19, [x3, #:lo12:.LANCHOR39]
.L92:
	cbnz	w1, .L93
.L95:
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
.L93:
	ldrh	w3, [x2]
	cmp	w3, w4
	beq	.L95
	sub	w1, w1, #1
	umaddl	x2, w3, w5, x19
	and	w1, w1, 65535
	b	.L92
.L96:
	mov	w0, 65535
	ret
	.size	List_pop_index_node, .-List_pop_index_node
	.section	.text.List_pop_head_node,"ax",@progbits
	.align	2
	.global	List_pop_head_node
	.type	List_pop_head_node, %function
List_pop_head_node:
	mov	w1, 0
	b	List_pop_index_node
	.size	List_pop_head_node, .-List_pop_head_node
	.section	.text.List_get_gc_head_node,"ax",@progbits
	.align	2
	.global	List_get_gc_head_node
	.type	List_get_gc_head_node, %function
List_get_gc_head_node:
	and	w2, w0, 65535
	adrp	x0, .LANCHOR40
	ldr	x1, [x0, #:lo12:.LANCHOR40]
	cbz	x1, .L107
	adrp	x0, .LANCHOR39
	mov	w4, 6
	ldr	x3, [x0, #:lo12:.LANCHOR39]
	mov	w0, 65535
.L104:
	cbz	w2, .L105
	ldrh	w1, [x1]
	cmp	w1, w0
	bne	.L106
	ret
.L106:
	sub	w2, w2, #1
	umaddl	x1, w1, w4, x3
	and	w2, w2, 65535
	b	.L104
.L107:
	mov	w0, 65535
	ret
.L105:
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
	adrp	x0, .LANCHOR50
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	ldrh	w0, [x0, #:lo12:.LANCHOR50]
	stp	x25, x26, [sp, 64]
	cmp	w0, w19
	beq	.L110
	adrp	x0, .LANCHOR51
	ldrh	w0, [x0, #:lo12:.LANCHOR51]
	cmp	w0, w19
	beq	.L110
	adrp	x0, .LANCHOR52
	ldrh	w0, [x0, #:lo12:.LANCHOR52]
	cmp	w0, w19
	beq	.L110
	adrp	x0, .LANCHOR39
	mov	w21, 6
	adrp	x24, .LANCHOR40
	mov	x26, x0
	umull	x21, w19, w21
	ldr	x23, [x0, #:lo12:.LANCHOR39]
	ldr	x1, [x24, #:lo12:.LANCHOR40]
	add	x22, x23, x21
	cmp	x22, x1
	beq	.L110
	adrp	x1, .LANCHOR41
	ubfiz	x0, x19, 1, 16
	mov	x25, x1
	ldr	x2, [x1, #:lo12:.LANCHOR41]
	mov	w1, 65535
	ldrh	w20, [x2, x0]
	ldrh	w0, [x22, 4]
	cmp	w0, 0
	mul	w20, w20, w0
	ldrh	w0, [x22, 2]
	csinv	w20, w20, wzr, ne
	cmp	w0, w1
	bne	.L113
	ldrh	w1, [x23, x21]
	cmp	w1, w0
	bne	.L113
	adrp	x1, .LANCHOR53
	adrp	x0, .LC1
	mov	w2, 463
	add	x1, x1, :lo12:.LANCHOR53
	add	x0, x0, :lo12:.LC1
	bl	printf
.L113:
	ldrh	w0, [x22, 2]
	mov	w1, 65535
	cmp	w0, w1
	bne	.L114
	ldrh	w1, [x23, x21]
	cmp	w1, w0
	beq	.L110
.L114:
	mov	w1, 6
	mov	x2, -6148914691236517206
	movk	x2, 0xaaab, lsl 0
	umull	x0, w0, w1
	asr	x1, x0, 1
	mul	x1, x1, x2
	ldr	x2, [x25, #:lo12:.LANCHOR41]
	ldrh	w1, [x2, x1, lsl 1]
	ldr	x2, [x26, #:lo12:.LANCHOR39]
	add	x0, x2, x0
	ldrh	w2, [x0, 4]
	cmp	w2, 0
	mul	w0, w1, w2
	csinv	w0, w0, wzr, ne
	cmp	w20, w0
	bcs	.L110
	adrp	x20, .LANCHOR43
	mov	w1, w19
	add	x0, x24, :lo12:.LANCHOR40
	bl	List_remove_node
	ldrh	w0, [x20, #:lo12:.LANCHOR43]
	cbnz	w0, .L116
	adrp	x1, .LANCHOR53
	adrp	x0, .LC1
	mov	w2, 474
	add	x1, x1, :lo12:.LANCHOR53
	add	x0, x0, :lo12:.LC1
	bl	printf
.L116:
	ldrh	w0, [x20, #:lo12:.LANCHOR43]
	sub	w0, w0, #1
	strh	w0, [x20, #:lo12:.LANCHOR43]
	mov	w0, w19
	bl	INSERT_DATA_LIST
.L110:
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.size	List_update_data_list, .-List_update_data_list
	.section	.text.select_l2p_ram_region,"ax",@progbits
	.align	2
	.global	select_l2p_ram_region
	.type	select_l2p_ram_region, %function
select_l2p_ram_region:
	stp	x29, x30, [sp, -32]!
	adrp	x0, .LANCHOR32
	mov	x1, 0
	mov	w3, 65535
	add	x29, sp, 0
	ldrh	w2, [x0, #:lo12:.LANCHOR32]
	adrp	x0, .LANCHOR54
	str	x19, [sp, 16]
	ldr	x0, [x0, #:lo12:.LANCHOR54]
.L121:
	and	w19, w1, 65535
	cmp	w19, w2
	bcc	.L123
	add	x3, x0, 4
	mov	w19, w2
	mov	w5, -2147483648
	mov	w1, 0
.L124:
	cmp	w1, w2
	bne	.L126
	cmp	w19, w2
	bcc	.L122
	adrp	x1, .LANCHOR55
	mov	w19, w2
	mov	w3, -1
	ldrh	w4, [x1, #:lo12:.LANCHOR55]
	mov	w1, 0
.L127:
	cmp	w1, w2
	bne	.L129
	cmp	w19, w1
	bcc	.L122
	mov	w2, 796
	adrp	x1, .LANCHOR56
	adrp	x0, .LC1
	add	x1, x1, :lo12:.LANCHOR56
	add	x0, x0, :lo12:.LC1
	bl	printf
	b	.L122
.L123:
	add	x1, x1, 1
	add	x4, x0, x1, lsl 4
	ldrh	w4, [x4, -16]
	cmp	w4, w3
	bne	.L121
.L122:
	mov	w0, w19
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L126:
	ldr	w4, [x3]
	tbnz	w4, #31, .L125
	cmp	w5, w4
	bls	.L125
	mov	w5, w4
	mov	w19, w1
.L125:
	add	w1, w1, 1
	add	x3, x3, 16
	and	w1, w1, 65535
	b	.L124
.L129:
	ldr	w6, [x0, 4]
	cmp	w3, w6
	bls	.L128
	ldrh	w5, [x0]
	cmp	w5, w4
	csel	w3, w3, w6, eq
	csel	w19, w19, w1, eq
.L128:
	add	w1, w1, 1
	add	x0, x0, 16
	and	w1, w1, 65535
	b	.L127
	.size	select_l2p_ram_region, .-select_l2p_ram_region
	.section	.text.FtlUpdateVaildLpn,"ax",@progbits
	.align	2
	.global	FtlUpdateVaildLpn
	.type	FtlUpdateVaildLpn, %function
FtlUpdateVaildLpn:
	adrp	x2, .LANCHOR57
	mov	x3, x2
	ldrh	w1, [x2, #:lo12:.LANCHOR57]
	cmp	w1, 4
	bhi	.L132
	cbnz	w0, .L132
	add	w1, w1, 1
	strh	w1, [x2, #:lo12:.LANCHOR57]
	ret
.L132:
	adrp	x1, .LANCHOR4
	adrp	x0, .LANCHOR58
	strh	wzr, [x3, #:lo12:.LANCHOR57]
	mov	w2, 0
	ldrh	w5, [x1, #:lo12:.LANCHOR4]
	adrp	x1, .LANCHOR41
	str	wzr, [x0, #:lo12:.LANCHOR58]
	mov	w3, 0
	ldr	x6, [x1, #:lo12:.LANCHOR41]
	mov	w7, 65535
	mov	x1, 0
.L133:
	cmp	w5, w1, uxth
	bhi	.L135
	cbz	w3, .L131
	str	w2, [x0, #:lo12:.LANCHOR58]
.L131:
	ret
.L135:
	ldrh	w4, [x6, x1, lsl 1]
	cmp	w4, w7
	beq	.L134
	add	w2, w2, w4
	mov	w3, 1
.L134:
	add	x1, x1, 1
	b	.L133
	.size	FtlUpdateVaildLpn, .-FtlUpdateVaildLpn
	.section	.text.ftl_sb_update_avl_pages,"ax",@progbits
	.align	2
	.global	ftl_sb_update_avl_pages
	.type	ftl_sb_update_avl_pages, %function
ftl_sb_update_avl_pages:
	and	w2, w2, 65535
	and	w6, w1, 65535
	ubfiz	x4, x2, 1, 16
	adrp	x1, .LANCHOR2
	add	x4, x4, 16
	strh	wzr, [x0, 4]
	add	x4, x0, x4
	ldrh	w3, [x1, #:lo12:.LANCHOR2]
	mov	w1, 65535
.L142:
	cmp	w2, w3
	bcc	.L144
	adrp	x1, .LANCHOR18
	ubfiz	x3, x3, 1, 16
	add	x3, x3, 16
	add	x2, x0, 16
	ldrh	w1, [x1, #:lo12:.LANCHOR18]
	add	x3, x0, x3
	mov	w5, 65535
	sub	w1, w1, #1
	and	w1, w1, 65535
	sub	w1, w1, w6
.L145:
	cmp	x2, x3
	bne	.L147
	ret
.L144:
	ldrh	w5, [x4]
	cmp	w5, w1
	beq	.L143
	ldrh	w5, [x0, 4]
	add	w5, w5, 1
	strh	w5, [x0, 4]
.L143:
	add	w2, w2, 1
	add	x4, x4, 2
	and	w2, w2, 65535
	b	.L142
.L147:
	ldrh	w4, [x2]
	cmp	w4, w5
	beq	.L146
	ldrh	w4, [x0, 4]
	add	w4, w1, w4
	strh	w4, [x0, 4]
.L146:
	add	x2, x2, 2
	b	.L145
	.size	ftl_sb_update_avl_pages, .-ftl_sb_update_avl_pages
	.section	.text.FtlSlcSuperblockCheck,"ax",@progbits
	.align	2
	.global	FtlSlcSuperblockCheck
	.type	FtlSlcSuperblockCheck, %function
FtlSlcSuperblockCheck:
	ldrh	w1, [x0, 4]
	cbz	w1, .L148
	ldrh	w2, [x0]
	mov	w1, 65535
	cmp	w2, w1
	beq	.L148
	ldrb	w2, [x0, 6]
	add	x2, x2, 8
	ldrh	w3, [x0, x2, lsl 1]
	adrp	x2, .LANCHOR2
	ldrh	w4, [x2, #:lo12:.LANCHOR2]
	mov	w2, w1
.L151:
	cmp	w3, w2
	beq	.L153
.L148:
	ret
.L153:
	ldrb	w1, [x0, 6]
	add	w1, w1, 1
	and	w1, w1, 255
	strb	w1, [x0, 6]
	cmp	w1, w4
	bne	.L152
	ldrh	w1, [x0, 2]
	strb	wzr, [x0, 6]
	add	w1, w1, 1
	strh	w1, [x0, 2]
.L152:
	ldrb	w1, [x0, 6]
	add	x1, x1, 8
	ldrh	w3, [x0, x1, lsl 1]
	b	.L151
	.size	FtlSlcSuperblockCheck, .-FtlSlcSuperblockCheck
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
	adrp	x0, .LANCHOR4
	ldrh	w0, [x0, #:lo12:.LANCHOR4]
	cmp	w1, w0
	bcc	.L155
	adrp	x1, .LANCHOR59
	adrp	x0, .LC1
	mov	w2, 2157
	add	x1, x1, :lo12:.LANCHOR59
	add	x0, x0, :lo12:.LC1
	bl	printf
.L155:
	adrp	x0, .LANCHOR2
	adrp	x7, .LANCHOR12
	add	x6, x19, 16
	add	x7, x7, :lo12:.LANCHOR12
	ldrh	w8, [x0, #:lo12:.LANCHOR2]
	mov	x5, 0
	strh	wzr, [x19, 4]
	mov	w10, -1
	strb	wzr, [x19, 7]
.L156:
	cmp	w8, w5, uxth
	bhi	.L158
	adrp	x1, .LANCHOR18
	ldrb	w0, [x19, 7]
	strb	wzr, [x19, 9]
	ldrh	w1, [x1, #:lo12:.LANCHOR18]
	mul	w0, w0, w1
	ldrh	w1, [x19]
	strh	w0, [x19, 4]
	adrp	x0, .LANCHOR46
	ldr	x0, [x0, #:lo12:.LANCHOR46]
	ldrh	w1, [x0, x1, lsl 1]
	mov	w0, 10000
	cmp	w1, w0
	bls	.L159
	mov	w0, 1
	strb	w0, [x19, 9]
.L159:
	mov	w0, 0
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L158:
	ldrh	w1, [x19]
	ldrb	w0, [x7, x5]
	bl	V2P_block
	mov	w4, w0
	strh	w10, [x6]
	bl	FtlBbmIsBadBlock
	cbnz	w0, .L157
	strh	w4, [x6]
	ldrb	w0, [x19, 7]
	add	w0, w0, 1
	strb	w0, [x19, 7]
.L157:
	add	x5, x5, 1
	add	x6, x6, 2
	b	.L156
	.size	make_superblock, .-make_superblock
	.section	.text.update_multiplier_value,"ax",@progbits
	.align	2
	.global	update_multiplier_value
	.type	update_multiplier_value, %function
update_multiplier_value:
	and	w6, w0, 65535
	adrp	x0, .LANCHOR2
	mov	x7, 0
	adrp	x8, .LANCHOR12
	ldrh	w10, [x0, #:lo12:.LANCHOR2]
	adrp	x0, .LANCHOR18
	mov	w5, 0
	add	x8, x8, :lo12:.LANCHOR12
	ldrh	w11, [x0, #:lo12:.LANCHOR18]
	cmp	w10, w7, uxth
	bhi	.L173
	cbz	w5, .L171
	mov	w0, 32768
	sdiv	w5, w0, w5
.L172:
	adrp	x0, .LANCHOR39
	mov	w1, 6
	ldr	x0, [x0, #:lo12:.LANCHOR39]
	umaddl	x6, w6, w1, x0
	mov	w0, 0
	strh	w5, [x6, 4]
	ret
.L166:
	mov	w5, 0
	b	.L165
.L171:
	mov	w5, 0
	b	.L172
.L173:
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
.L164:
	ldrb	w0, [x8, x7]
	mov	w1, w6
	bl	V2P_block
	bl	FtlBbmIsBadBlock
	cbnz	w0, .L163
	add	w5, w5, w11
	and	w5, w5, 65535
.L163:
	add	x7, x7, 1
	cmp	w10, w7, uxth
	bhi	.L164
	cbz	w5, .L166
	mov	w0, 32768
	sdiv	w5, w0, w5
.L165:
	adrp	x0, .LANCHOR39
	mov	w1, 6
	ldr	x0, [x0, #:lo12:.LANCHOR39]
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
	adrp	x0, .LANCHOR45
	ldr	x0, [x0, #:lo12:.LANCHOR45]
	cbz	x0, .L176
	adrp	x1, .LANCHOR39
	ldr	x1, [x1, #:lo12:.LANCHOR39]
	sub	x0, x0, x1
	mov	x1, -6148914691236517206
	asr	x0, x0, 1
	movk	x1, 0xaaab, lsl 0
	mul	x0, x0, x1
	adrp	x1, .LANCHOR46
	ldr	x1, [x1, #:lo12:.LANCHOR46]
	and	x0, x0, 65535
	ldrh	w0, [x1, x0, lsl 1]
	ret
.L176:
	mov	w0, 0
	ret
	.size	GetFreeBlockMinEraseCount, .-GetFreeBlockMinEraseCount
	.section	.text.GetFreeBlockMaxEraseCount,"ax",@progbits
	.align	2
	.global	GetFreeBlockMaxEraseCount
	.type	GetFreeBlockMaxEraseCount, %function
GetFreeBlockMaxEraseCount:
	adrp	x1, .LANCHOR45
	and	w0, w0, 65535
	ldr	x1, [x1, #:lo12:.LANCHOR45]
	cbz	x1, .L184
	adrp	x2, .LANCHOR47
	mov	w3, 7
	mov	w5, 6
	mov	w6, 65535
	ldrh	w2, [x2, #:lo12:.LANCHOR47]
	mul	w2, w2, w3
	asr	w2, w2, 3
	cmp	w0, w2
	csel	w0, w2, w0, gt
	adrp	x2, .LANCHOR39
	ldr	x3, [x2, #:lo12:.LANCHOR39]
	mov	x2, -6148914691236517206
	movk	x2, 0xaaab, lsl 0
	sub	x1, x1, x3
	asr	x1, x1, 1
	mul	x1, x1, x2
	mov	w2, 0
	and	w1, w1, 65535
.L180:
	cmp	w0, w2
	beq	.L183
	umull	x4, w1, w5
	ldrh	w4, [x3, x4]
	cmp	w4, w6
	bne	.L181
.L183:
	adrp	x0, .LANCHOR46
	ubfiz	x1, x1, 1, 16
	ldr	x0, [x0, #:lo12:.LANCHOR46]
	ldrh	w0, [x0, x1]
	ret
.L181:
	add	w2, w2, 1
	mov	w1, w4
	and	w2, w2, 65535
	b	.L180
.L184:
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
	beq	.L188
	stp	x29, x30, [sp, -16]!
	adrp	x2, .LANCHOR41
	ubfiz	x1, x0, 1, 16
	add	x29, sp, 0
	ldr	x2, [x2, #:lo12:.LANCHOR41]
	strh	wzr, [x2, x1]
	bl	INSERT_FREE_LIST
	mov	w0, 0
	ldp	x29, x30, [sp], 16
	ret
.L188:
	mov	w0, 0
	ret
	.size	free_data_superblock, .-free_data_superblock
	.section	.text.get_new_active_ppa,"ax",@progbits
	.align	2
	.global	get_new_active_ppa
	.type	get_new_active_ppa, %function
get_new_active_ppa:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	ldrh	w1, [x0]
	mov	w0, 65535
	str	x21, [sp, 32]
	cmp	w1, w0
	bne	.L192
	adrp	x1, .LANCHOR60
	adrp	x0, .LC1
	mov	w2, 2792
	add	x1, x1, :lo12:.LANCHOR60
	add	x0, x0, :lo12:.LC1
	bl	printf
.L192:
	adrp	x21, .LANCHOR18
	ldrh	w1, [x19, 2]
	ldrh	w0, [x21, #:lo12:.LANCHOR18]
	cmp	w1, w0
	bne	.L193
	adrp	x1, .LANCHOR60
	adrp	x0, .LC1
	mov	w2, 2793
	add	x1, x1, :lo12:.LANCHOR60
	add	x0, x0, :lo12:.LC1
	bl	printf
.L193:
	ldrh	w0, [x19, 4]
	cbnz	w0, .L194
	adrp	x1, .LANCHOR60
	adrp	x0, .LC1
	mov	w2, 2794
	add	x1, x1, :lo12:.LANCHOR60
	add	x0, x0, :lo12:.LC1
	bl	printf
.L194:
	ldrb	w0, [x19, 6]
	adrp	x1, .LANCHOR2
	strb	wzr, [x19, 10]
	add	x0, x0, 8
	ldrh	w3, [x1, #:lo12:.LANCHOR2]
	mov	w1, 65535
	ldrh	w0, [x19, x0, lsl 1]
.L195:
	cmp	w0, w1
	beq	.L197
	ldrh	w20, [x19, 2]
	ldrh	w2, [x21, #:lo12:.LANCHOR18]
	cmp	w20, w2
	bcs	.L201
	ldrh	w1, [x19, 4]
	orr	w20, w20, w0, lsl 10
	ldrb	w0, [x19, 6]
	mov	w4, 65535
	sub	w1, w1, #1
	and	w1, w1, 65535
	strh	w1, [x19, 4]
.L200:
	add	w0, w0, 1
	and	w0, w0, 255
	cmp	w3, w0
	bne	.L199
	ldrh	w0, [x19, 2]
	add	w0, w0, 1
	strh	w0, [x19, 2]
	mov	w0, 0
.L199:
	add	x5, x19, x0, sxtw 1
	ldrh	w5, [x5, 16]
	cmp	w5, w4
	beq	.L200
	strb	w0, [x19, 6]
	ldrh	w0, [x19, 2]
	cmp	w0, w2
	bne	.L191
	cbz	w1, .L191
	adrp	x1, .LANCHOR60
	adrp	x0, .LC1
	mov	w2, 2817
	add	x1, x1, :lo12:.LANCHOR60
	add	x0, x0, :lo12:.LC1
	bl	printf
.L191:
	mov	w0, w20
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
.L197:
	ldrb	w0, [x19, 6]
	add	w0, w0, 1
	and	w0, w0, 255
	strb	w0, [x19, 6]
	cmp	w0, w3
	bne	.L196
	ldrh	w0, [x19, 2]
	strb	wzr, [x19, 6]
	add	w0, w0, 1
	strh	w0, [x19, 2]
.L196:
	ldrb	w0, [x19, 6]
	add	x0, x0, 8
	ldrh	w0, [x19, x0, lsl 1]
	b	.L195
.L201:
	mov	w20, 65535
	b	.L191
	.size	get_new_active_ppa, .-get_new_active_ppa
	.section	.text.FtlGcBufInit,"ax",@progbits
	.align	2
	.global	FtlGcBufInit
	.type	FtlGcBufInit, %function
FtlGcBufInit:
	adrp	x1, .LANCHOR62
	adrp	x0, .LANCHOR61
	adrp	x7, .LANCHOR63
	adrp	x6, .LANCHOR64
	ldr	x5, [x1, #:lo12:.LANCHOR62]
	adrp	x1, .LANCHOR22
	str	wzr, [x0, #:lo12:.LANCHOR61]
	adrp	x0, .LANCHOR2
	ldrh	w10, [x1, #:lo12:.LANCHOR22]
	adrp	x1, .LANCHOR23
	ldrh	w0, [x0, #:lo12:.LANCHOR2]
	mov	w8, 24
	ldrh	w11, [x1, #:lo12:.LANCHOR23]
	adrp	x1, .LANCHOR65
	ldr	x14, [x7, #:lo12:.LANCHOR63]
	mov	x3, x5
	ldr	x4, [x1, #:lo12:.LANCHOR65]
	mov	w2, 0
	ldr	x15, [x6, #:lo12:.LANCHOR64]
	nop // between mem op and mult-accumulate
	umaddl	x8, w0, w8, x5
	add	x4, x4, 8
	mov	w1, 0
	mov	w16, 1
.L208:
	add	w13, w2, w10
	add	w12, w1, w11
	cmp	x3, x8
	bne	.L209
	adrp	x1, .LANCHOR66
	ldr	x7, [x7, #:lo12:.LANCHOR63]
	ldr	x6, [x6, #:lo12:.LANCHOR64]
	mov	w8, 24
	ldr	w4, [x1, #:lo12:.LANCHOR66]
.L210:
	cmp	w0, w4
	bcc	.L211
	ret
.L209:
	asr	w2, w2, 2
	asr	w1, w1, 2
	add	x2, x14, x2, sxtw 2
	add	x1, x15, x1, sxtw 2
	str	w16, [x3, 16]
	stp	x2, x1, [x3]
	add	x3, x3, 24
	stp	x2, x1, [x4]
	add	x4, x4, 32
	mov	w1, w12
	mov	w2, w13
	b	.L208
.L211:
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
	b	.L210
	.size	FtlGcBufInit, .-FtlGcBufInit
	.section	.text.FtlGcBufFree,"ax",@progbits
	.align	2
	.global	FtlGcBufFree
	.type	FtlGcBufFree, %function
FtlGcBufFree:
	adrp	x2, .LANCHOR66
	mov	w3, 0
	mov	w8, 24
	ldr	w7, [x2, #:lo12:.LANCHOR66]
	adrp	x2, .LANCHOR62
	ldr	x5, [x2, #:lo12:.LANCHOR62]
.L213:
	cmp	w3, w1
	bcs	.L212
	ubfiz	x4, x3, 5, 16
	mov	w2, 0
	add	x4, x0, x4
	b	.L218
.L214:
	add	w2, w2, 1
	and	w2, w2, 65535
.L218:
	cmp	w2, w7
	bcs	.L215
	umull	x6, w2, w8
	add	x10, x5, x6
	ldr	x11, [x5, x6]
	ldr	x6, [x4, 8]
	cmp	x11, x6
	bne	.L214
	str	wzr, [x10, 16]
.L215:
	add	w3, w3, 1
	and	w3, w3, 65535
	b	.L213
.L212:
	ret
	.size	FtlGcBufFree, .-FtlGcBufFree
	.section	.text.FtlGcBufAlloc,"ax",@progbits
	.align	2
	.global	FtlGcBufAlloc
	.type	FtlGcBufAlloc, %function
FtlGcBufAlloc:
	adrp	x2, .LANCHOR66
	mov	w3, 0
	mov	w7, 24
	mov	w8, 1
	ldr	w5, [x2, #:lo12:.LANCHOR66]
	adrp	x2, .LANCHOR62
	ldr	x6, [x2, #:lo12:.LANCHOR62]
.L220:
	cmp	w3, w1
	bcs	.L219
	mov	w2, 0
	b	.L225
.L221:
	add	w2, w2, 1
	and	w2, w2, 65535
.L225:
	cmp	w2, w5
	bcs	.L222
	umaddl	x4, w2, w7, x6
	ldr	w10, [x4, 16]
	cbnz	w10, .L221
	ubfiz	x2, x3, 5, 16
	ldr	x10, [x4]
	add	x2, x0, x2
	str	w8, [x4, 16]
	ldr	x4, [x4, 8]
	stp	x10, x4, [x2, 8]
.L222:
	add	w3, w3, 1
	and	w3, w3, 65535
	b	.L220
.L219:
	ret
	.size	FtlGcBufAlloc, .-FtlGcBufAlloc
	.section	.text.IsBlkInGcList,"ax",@progbits
	.align	2
	.global	IsBlkInGcList
	.type	IsBlkInGcList, %function
IsBlkInGcList:
	adrp	x1, .LANCHOR67
	and	w0, w0, 65535
	ldrh	w2, [x1, #:lo12:.LANCHOR67]
	adrp	x1, .LANCHOR68
	ldr	x3, [x1, #:lo12:.LANCHOR68]
	mov	x1, 0
.L227:
	cmp	w2, w1, uxth
	bhi	.L229
	mov	w0, 0
	ret
.L229:
	add	x1, x1, 1
	add	x4, x3, x1, lsl 1
	ldrh	w4, [x4, -2]
	cmp	w4, w0
	bne	.L227
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
	adrp	x4, .LANCHOR67
	adrp	x2, .LANCHOR68
	mov	x3, 0
	ldrh	w1, [x4, #:lo12:.LANCHOR67]
	ldr	x5, [x2, #:lo12:.LANCHOR68]
.L232:
	and	w2, w3, 65535
	cmp	w2, w1
	bcc	.L234
	bne	.L233
	and	x3, x3, 65535
	strh	w0, [x5, x3, lsl 1]
	ldrh	w0, [x4, #:lo12:.LANCHOR67]
	add	w0, w0, 1
	strh	w0, [x4, #:lo12:.LANCHOR67]
	b	.L233
.L234:
	add	x3, x3, 1
	add	x2, x5, x3, lsl 1
	ldrh	w2, [x2, -2]
	cmp	w2, w7
	bne	.L232
.L233:
	adrp	x4, .LANCHOR69
	adrp	x1, .LANCHOR70
	mov	w3, 12
	ldrh	w0, [x4, #:lo12:.LANCHOR69]
	ldr	x5, [x1, #:lo12:.LANCHOR70]
	umull	x3, w0, w3
	add	w0, w0, 1
	add	x7, x5, x3
	stp	w10, w8, [x7, 4]
	str	w6, [x5, x3]
	strh	w0, [x4, #:lo12:.LANCHOR69]
	ldp	x29, x30, [sp], 16
	ret
	.size	FtlGcUpdatePage, .-FtlGcUpdatePage
	.section	.text.FtlGcRefreshBlock,"ax",@progbits
	.align	2
	.global	FtlGcRefreshBlock
	.type	FtlGcRefreshBlock, %function
FtlGcRefreshBlock:
	adrp	x4, .LANCHOR71
	and	w0, w0, 65535
	ldrh	w5, [x4, #:lo12:.LANCHOR71]
	cmp	w5, w0
	beq	.L237
	adrp	x1, .LANCHOR72
	ldrh	w3, [x1, #:lo12:.LANCHOR72]
	cmp	w0, w3
	beq	.L237
	mov	w2, 65535
	cmp	w5, w2
	bne	.L238
	strh	w0, [x4, #:lo12:.LANCHOR71]
.L237:
	mov	w0, 0
	ret
.L238:
	cmp	w3, w2
	bne	.L237
	strh	w0, [x1, #:lo12:.LANCHOR72]
	b	.L237
	.size	FtlGcRefreshBlock, .-FtlGcRefreshBlock
	.section	.text.FtlGcMarkBadPhyBlk,"ax",@progbits
	.align	2
	.global	FtlGcMarkBadPhyBlk
	.type	FtlGcMarkBadPhyBlk, %function
FtlGcMarkBadPhyBlk:
	and	w6, w0, 65535
	stp	x29, x30, [sp, -16]!
	mov	w0, w6
	add	x29, sp, 0
	bl	P2V_block_in_plane
	bl	FtlGcRefreshBlock
	adrp	x1, .LANCHOR73
	adrp	x3, .LANCHOR74
	add	x3, x3, :lo12:.LANCHOR74
	mov	x2, 0
	ldrh	w0, [x1, #:lo12:.LANCHOR73]
.L240:
	cmp	w0, w2, uxth
	bhi	.L242
	cmp	w0, 15
	bhi	.L241
	add	w2, w0, 1
	strh	w2, [x1, #:lo12:.LANCHOR73]
	adrp	x1, .LANCHOR74
	add	x1, x1, :lo12:.LANCHOR74
	strh	w6, [x1, w0, sxtw 1]
	b	.L241
.L242:
	add	x2, x2, 1
	add	x4, x3, x2, lsl 1
	ldrh	w4, [x4, -2]
	cmp	w4, w6
	bne	.L240
.L241:
	mov	w0, 0
	ldp	x29, x30, [sp], 16
	ret
	.size	FtlGcMarkBadPhyBlk, .-FtlGcMarkBadPhyBlk
	.section	.text.FtlGcReFreshBadBlk,"ax",@progbits
	.align	2
	.global	FtlGcReFreshBadBlk
	.type	FtlGcReFreshBadBlk, %function
FtlGcReFreshBadBlk:
	adrp	x0, .LANCHOR73
	ldrh	w0, [x0, #:lo12:.LANCHOR73]
	cbz	w0, .L251
	adrp	x1, .LANCHOR71
	ldrh	w2, [x1, #:lo12:.LANCHOR71]
	mov	w1, 65535
	cmp	w2, w1
	bne	.L251
	stp	x29, x30, [sp, -16]!
	adrp	x6, .LANCHOR75
	add	x29, sp, 0
	ldrh	w1, [x6, #:lo12:.LANCHOR75]
	cmp	w1, w0
	bcc	.L246
	strh	wzr, [x6, #:lo12:.LANCHOR75]
.L246:
	ldrh	w1, [x6, #:lo12:.LANCHOR75]
	adrp	x0, .LANCHOR74
	add	x0, x0, :lo12:.LANCHOR74
	ldrh	w0, [x0, x1, lsl 1]
	bl	P2V_block_in_plane
	bl	FtlGcRefreshBlock
	ldrh	w0, [x6, #:lo12:.LANCHOR75]
	ldp	x29, x30, [sp], 16
	add	w0, w0, 1
	strh	w0, [x6, #:lo12:.LANCHOR75]
	mov	w0, 0
	ret
.L251:
	mov	w0, 0
	ret
	.size	FtlGcReFreshBadBlk, .-FtlGcReFreshBadBlk
	.section	.text.ftl_malloc,"ax",@progbits
	.align	2
	.global	ftl_malloc
	.type	ftl_malloc, %function
ftl_malloc:
	mov	w1, 0
	sxtw	x0, w0
	b	kmalloc
	.size	ftl_malloc, .-ftl_malloc
	.section	.text.ftl_free,"ax",@progbits
	.align	2
	.global	ftl_free
	.type	ftl_free, %function
ftl_free:
	b	free
	.size	ftl_free, .-ftl_free
	.section	.text.rknand_print_hex,"ax",@progbits
	.align	2
	.global	rknand_print_hex
	.type	rknand_print_hex, %function
rknand_print_hex:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x21, x22, [sp, 32]
	mov	x22, x1
	stp	x23, x24, [sp, 48]
	adrp	x24, .LC2
	stp	x25, x26, [sp, 64]
	mov	w23, w2
	stp	x27, x28, [sp, 80]
	adrp	x25, .LC4
	mov	x28, x0
	mov	w27, w3
	add	x24, x24, :lo12:.LC2
	add	x25, x25, :lo12:.LC4
	stp	x19, x20, [sp, 16]
	mov	w21, 0
	mov	x19, 0
	mov	w20, 0
	adrp	x26, .LC3
.L257:
	cmp	w27, w19
	bhi	.L263
	ldp	x19, x20, [sp, 16]
	adrp	x0, .LC5
	ldp	x21, x22, [sp, 32]
	add	x0, x0, :lo12:.LC5
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 96
	b	printf
.L263:
	cbnz	w20, .L258
	mov	w2, w21
	mov	x1, x28
	mov	x0, x24
	bl	printf
.L258:
	cmp	w23, 4
	bne	.L259
	ldr	w1, [x22, x19, lsl 2]
.L266:
	add	x0, x26, :lo12:.LC3
.L265:
	bl	printf
	add	w20, w20, 1
	cmp	w20, 15
	bls	.L262
	mov	w20, 0
	adrp	x0, .LC5
	add	x0, x0, :lo12:.LC5
	bl	printf
.L262:
	add	x19, x19, 1
	add	w21, w21, w23
	b	.L257
.L259:
	cmp	w23, 2
	bne	.L261
	ldrh	w1, [x22, x19, lsl 1]
	b	.L266
.L261:
	ldrb	w1, [x22, x19]
	mov	x0, x25
	b	.L265
	.size	rknand_print_hex, .-rknand_print_hex
	.section	.text.FlashEraseBlocks,"ax",@progbits
	.align	2
	.global	FlashEraseBlocks
	.type	FlashEraseBlocks, %function
FlashEraseBlocks:
	stp	x29, x30, [sp, -112]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x0
	adrp	x0, .LANCHOR0
	add	x1, x0, :lo12:.LANCHOR0
	stp	x23, x24, [sp, 48]
	add	x19, x20, 4
	stp	x21, x22, [sp, 32]
	ubfiz	x21, x2, 5, 32
	ldrh	w24, [x1, 12]
	add	x23, x21, 4
	stp	x25, x26, [sp, 64]
	add	x23, x20, x23
	adrp	x25, .LANCHOR77
	str	x27, [sp, 80]
	lsl	w26, w24, 3
	mov	x22, x0
	add	x27, x25, :lo12:.LANCHOR77
.L268:
	cmp	x19, x23
	beq	.L282
	ldr	w0, [x19]
	add	x2, x29, 104
	add	x1, x29, 108
	bl	l2p_addr_tran.isra.0
	ldr	w0, [x29, 104]
	cbnz	w0, .L269
	ldr	w1, [x29, 108]
	cmp	w26, w1
	bls	.L269
	mov	x19, x20
	add	x21, x20, x21
	adrp	x22, .LC6
	adrp	x20, .LANCHOR76
	add	x22, x22, :lo12:.LC6
	add	x20, x20, :lo12:.LANCHOR76
	mov	w23, -1
.L270:
	cmp	x19, x21
	bne	.L271
.L282:
	ldp	x19, x20, [sp, 16]
	mov	w0, 0
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldr	x27, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
.L271:
	ldr	w2, [x29, 108]
	mov	x1, x20
	str	w23, [x19]
	mov	x0, x22
	add	x19, x19, 32
	bl	printf
	ldr	x1, [x19, -24]
	mov	w3, 16
	mov	w2, 4
	adrp	x0, .LC7
	add	x0, x0, :lo12:.LC7
	bl	rknand_print_hex
	ldr	x1, [x19, -16]
	mov	w3, 4
	adrp	x0, .LC8
	mov	w2, w3
	add	x0, x0, :lo12:.LC8
	bl	rknand_print_hex
	b	.L270
.L269:
	add	x1, x25, :lo12:.LANCHOR77
	ldr	x2, [x1, 8]
	ldr	w1, [x29, 108]
	blr	x2
	cbnz	w0, .L272
	str	wzr, [x19, -4]
.L273:
	add	x0, x22, :lo12:.LANCHOR0
	ldrh	w0, [x0, 14]
	cmp	w0, 4
	bne	.L275
	ldrb	w0, [x29, 104]
	ldr	x2, [x27, 8]
	ldr	w1, [x29, 108]
	add	w1, w24, w1
	blr	x2
	cbz	w0, .L275
	mov	w0, -1
	str	w0, [x19, -4]
.L275:
	add	x19, x19, 32
	b	.L268
.L272:
	mov	w0, -1
	str	w0, [x19, -4]
	b	.L273
	.size	FlashEraseBlocks, .-FlashEraseBlocks
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
	bcc	.L284
	adrp	x0, .LANCHOR37
	add	x2, x0, :lo12:.LANCHOR37
	mov	x19, x0
	ldrh	w2, [x2, 6]
	cmp	w2, 1024
	beq	.L284
	and	w1, w1, 65535
	cbz	w1, .L286
	mov	w0, w20
	bl	P2V_block_in_plane
	and	w21, w0, 65535
	adrp	x0, .LANCHOR78
	lsl	w1, w20, 10
	mov	w2, 1
	ldr	x0, [x0, #:lo12:.LANCHOR78]
	str	w1, [x0, 4]
	mov	w1, w2
	bl	FlashEraseBlocks
	adrp	x1, .LANCHOR46
	ubfiz	x0, x21, 1, 16
	ldr	x2, [x1, #:lo12:.LANCHOR46]
	ldrh	w1, [x2, x0]
	add	w1, w1, 1
	strh	w1, [x2, x0]
	adrp	x1, .LANCHOR79
	ldr	w0, [x1, #:lo12:.LANCHOR79]
	add	w0, w0, 1
	str	w0, [x1, #:lo12:.LANCHOR79]
.L286:
	add	x0, x19, :lo12:.LANCHOR37
	ldrh	w1, [x0, 6]
	add	w1, w1, 1
	strh	w1, [x0, 6]
	ldrh	w1, [x0, 4]
	add	x2, x0, x1, sxtw 1
	add	w1, w1, 1
	and	w1, w1, 1023
	strh	w1, [x0, 4]
	strh	w20, [x2, 8]
.L284:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	FtlFreeSysBlkQueueIn, .-FtlFreeSysBlkQueueIn
	.section	.text.FtlFreeSysBlkQueueOut,"ax",@progbits
	.align	2
	.global	FtlFreeSysBlkQueueOut
	.type	FtlFreeSysBlkQueueOut, %function
FtlFreeSysBlkQueueOut:
	adrp	x0, .LANCHOR37
	add	x1, x0, :lo12:.LANCHOR37
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	ldrh	w2, [x1, 6]
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	cbz	w2, .L298
	ldrh	w0, [x1, 2]
	sub	w2, w2, #1
	strh	w2, [x1, 6]
	mov	w2, 1
	add	x3, x1, x0, sxtw 1
	add	w0, w0, 1
	and	w0, w0, 1023
	strh	w0, [x1, 2]
	adrp	x0, .LANCHOR78
	ldrh	w20, [x3, 8]
	ldr	x0, [x0, #:lo12:.LANCHOR78]
	lsl	w1, w20, 10
	str	w1, [x0, 4]
	mov	w1, w2
	bl	FlashEraseBlocks
	adrp	x1, .LANCHOR79
	ldr	w0, [x1, #:lo12:.LANCHOR79]
	add	w0, w0, 1
	str	w0, [x1, #:lo12:.LANCHOR79]
.L295:
	sub	w0, w20, #1
	mov	w1, 65533
	cmp	w1, w0, uxth
	bcs	.L296
	add	x0, x19, :lo12:.LANCHOR37
	mov	w1, w20
	ldrh	w2, [x0, 6]
	adrp	x0, .LC9
	add	x0, x0, :lo12:.LC9
	bl	printf
.L297:
	b	.L297
.L298:
	mov	w20, 65535
	b	.L295
.L296:
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	FtlFreeSysBlkQueueOut, .-FtlFreeSysBlkQueueOut
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
.L301:
	cmp	w20, w1
	beq	.L305
	mov	x21, x0
	ldrh	w2, [x0], 2
	cbnz	w2, .L302
	bl	FtlFreeSysBlkQueueOut
	and	w1, w0, 65535
	strh	w0, [x21]
	sub	w2, w1, #1
	mov	w0, 65533
	cmp	w0, w2, uxth
	bcs	.L303
	adrp	x0, .LANCHOR37+6
	ldrh	w2, [x0, #:lo12:.LANCHOR37+6]
	adrp	x0, .LC10
	add	x0, x0, :lo12:.LC10
	bl	printf
.L304:
	b	.L304
.L303:
	ldr	w0, [x19, 48]
	strh	wzr, [x19, 2]
	add	w0, w0, 1
	str	w0, [x19, 48]
	ldrh	w0, [x19, 8]
	strh	w20, [x19]
	add	w0, w0, 1
	strh	w0, [x19, 8]
.L305:
	ldrh	w0, [x19, 10]
	cmp	w0, w20
	bhi	.L307
	adrp	x1, .LANCHOR80
	adrp	x0, .LC1
	mov	w2, 578
	add	x1, x1, :lo12:.LANCHOR80
	add	x0, x0, :lo12:.LC1
	bl	printf
.L307:
	mov	w0, 0
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
.L302:
	add	w20, w20, 1
	and	w20, w20, 65535
	b	.L301
	.size	ftl_map_blk_alloc_new_blk, .-ftl_map_blk_alloc_new_blk
	.section	.text.ftl_memset,"ax",@progbits
	.align	2
	.global	ftl_memset
	.type	ftl_memset, %function
ftl_memset:
	uxtw	x2, w2
	b	memset
	.size	ftl_memset, .-ftl_memset
	.section	.text.FtlMemInit,"ax",@progbits
	.align	2
	.global	FtlMemInit
	.type	FtlMemInit, %function
FtlMemInit:
	stp	x29, x30, [sp, -64]!
	adrp	x0, .LANCHOR81
	mov	w1, 65535
	add	x29, sp, 0
	str	wzr, [x0, #:lo12:.LANCHOR81]
	adrp	x0, .LANCHOR82
	stp	x19, x20, [sp, 16]
	adrp	x19, .LANCHOR20
	str	wzr, [x0, #:lo12:.LANCHOR82]
	adrp	x0, .LANCHOR83
	stp	x21, x22, [sp, 32]
	adrp	x21, .LANCHOR2
	str	wzr, [x0, #:lo12:.LANCHOR83]
	adrp	x0, .LANCHOR84
	str	x23, [sp, 48]
	adrp	x22, .LANCHOR22
	str	wzr, [x0, #:lo12:.LANCHOR84]
	adrp	x0, .LANCHOR85
	adrp	x23, .LANCHOR23
	str	wzr, [x0, #:lo12:.LANCHOR85]
	adrp	x0, .LANCHOR86
	str	wzr, [x0, #:lo12:.LANCHOR86]
	adrp	x0, .LANCHOR87
	str	wzr, [x0, #:lo12:.LANCHOR87]
	adrp	x0, .LANCHOR88
	str	wzr, [x0, #:lo12:.LANCHOR88]
	adrp	x0, .LANCHOR89
	str	wzr, [x0, #:lo12:.LANCHOR89]
	adrp	x0, .LANCHOR90
	str	wzr, [x0, #:lo12:.LANCHOR90]
	adrp	x0, .LANCHOR79
	str	wzr, [x0, #:lo12:.LANCHOR79]
	adrp	x0, .LANCHOR91
	str	wzr, [x0, #:lo12:.LANCHOR91]
	adrp	x0, .LANCHOR92
	str	wzr, [x0, #:lo12:.LANCHOR92]
	adrp	x0, .LANCHOR93
	str	wzr, [x0, #:lo12:.LANCHOR93]
	adrp	x0, .LANCHOR94
	str	wzr, [x0, #:lo12:.LANCHOR94]
	adrp	x0, .LANCHOR95
	str	w1, [x0, #:lo12:.LANCHOR95]
	adrp	x0, .LANCHOR96
	adrp	x1, .LANCHOR71
	str	wzr, [x0, #:lo12:.LANCHOR96]
	adrp	x0, .LANCHOR97
	str	wzr, [x0, #:lo12:.LANCHOR97]
	adrp	x0, .LANCHOR98
	str	wzr, [x0, #:lo12:.LANCHOR98]
	mov	w0, -1
	strh	w0, [x1, #:lo12:.LANCHOR71]
	adrp	x1, .LANCHOR72
	strh	w0, [x1, #:lo12:.LANCHOR72]
	adrp	x0, .LANCHOR99
	mov	w1, 32
	strh	w1, [x0, #:lo12:.LANCHOR99]
	adrp	x0, .LANCHOR100
	mov	w1, 128
	strh	w1, [x0, #:lo12:.LANCHOR100]
	adrp	x0, .LANCHOR101
	strh	wzr, [x0, #:lo12:.LANCHOR101]
	adrp	x0, .LANCHOR73
	strh	wzr, [x0, #:lo12:.LANCHOR73]
	adrp	x0, .LANCHOR75
	strh	wzr, [x0, #:lo12:.LANCHOR75]
	ldrh	w0, [x19, #:lo12:.LANCHOR20]
	lsl	w0, w0, 1
	bl	ftl_malloc
	adrp	x1, .LANCHOR68
	str	x0, [x1, #:lo12:.LANCHOR68]
	mov	w0, 12
	ldrh	w1, [x19, #:lo12:.LANCHOR20]
	mul	w0, w1, w0
	bl	ftl_malloc
	ldrh	w19, [x21, #:lo12:.LANCHOR2]
	adrp	x1, .LANCHOR70
	lsl	w20, w19, 5
	lsl	w19, w19, 7
	str	x0, [x1, #:lo12:.LANCHOR70]
	mov	w0, w19
	bl	ftl_malloc
	adrp	x1, .LANCHOR102
	str	x0, [x1, #:lo12:.LANCHOR102]
	mov	w0, w20
	bl	ftl_malloc
	adrp	x1, .LANCHOR103
	str	x0, [x1, #:lo12:.LANCHOR103]
	mov	w0, w19
	bl	ftl_malloc
	adrp	x1, .LANCHOR104
	str	x0, [x1, #:lo12:.LANCHOR104]
	mov	w0, w20
	bl	ftl_malloc
	adrp	x1, .LANCHOR78
	str	x0, [x1, #:lo12:.LANCHOR78]
	mov	w0, w20
	bl	ftl_malloc
	adrp	x20, .LANCHOR66
	adrp	x1, .LANCHOR65
	ldrh	w19, [x22, #:lo12:.LANCHOR22]
	str	x0, [x1, #:lo12:.LANCHOR65]
	ldrh	w0, [x21, #:lo12:.LANCHOR2]
	lsl	w0, w0, 1
	add	w0, w0, 1
	str	w0, [x20, #:lo12:.LANCHOR66]
	mov	w0, w19
	bl	ftl_malloc
	adrp	x1, .LANCHOR105
	str	x0, [x1, #:lo12:.LANCHOR105]
	mov	w0, w19
	bl	ftl_malloc
	adrp	x1, .LANCHOR106
	str	x0, [x1, #:lo12:.LANCHOR106]
	mov	w0, w19
	bl	ftl_malloc
	adrp	x1, .LANCHOR107
	str	x0, [x1, #:lo12:.LANCHOR107]
	ldr	w0, [x20, #:lo12:.LANCHOR66]
	mul	w0, w19, w0
	bl	ftl_malloc
	adrp	x1, .LANCHOR63
	str	x0, [x1, #:lo12:.LANCHOR63]
	mov	w0, w19
	bl	ftl_malloc
	adrp	x1, .LANCHOR108
	str	x0, [x1, #:lo12:.LANCHOR108]
	mov	w0, w19
	bl	ftl_malloc
	adrp	x1, .LANCHOR109
	str	x0, [x1, #:lo12:.LANCHOR109]
	mov	w0, 24
	ldr	w1, [x20, #:lo12:.LANCHOR66]
	mul	w0, w1, w0
	bl	ftl_malloc
	adrp	x1, .LANCHOR62
	str	x0, [x1, #:lo12:.LANCHOR62]
	mov	w0, w19
	bl	ftl_malloc
	adrp	x1, .LANCHOR110
	str	x0, [x1, #:lo12:.LANCHOR110]
	mov	w0, w19
	bl	ftl_malloc
	adrp	x1, .LANCHOR111
	str	x0, [x1, #:lo12:.LANCHOR111]
	adrp	x0, .LANCHOR11
	ldrh	w0, [x0, #:lo12:.LANCHOR11]
	lsl	w0, w0, 2
	bl	ftl_malloc
	adrp	x1, .LANCHOR112
	ldrh	w19, [x23, #:lo12:.LANCHOR23]
	str	x0, [x1, #:lo12:.LANCHOR112]
	ldrh	w0, [x21, #:lo12:.LANCHOR2]
	adrp	x21, .LANCHOR29
	mul	w19, w19, w0
	mov	w0, w19
	bl	ftl_malloc
	adrp	x1, .LANCHOR113
	str	x0, [x1, #:lo12:.LANCHOR113]
	lsl	w0, w19, 2
	bl	ftl_malloc
	adrp	x19, .LANCHOR115
	adrp	x1, .LANCHOR114
	str	x0, [x1, #:lo12:.LANCHOR114]
	ldrh	w1, [x23, #:lo12:.LANCHOR23]
	ldr	w0, [x20, #:lo12:.LANCHOR66]
	adrp	x20, .LANCHOR5
	mul	w0, w1, w0
	bl	ftl_malloc
	adrp	x1, .LANCHOR64
	str	x0, [x1, #:lo12:.LANCHOR64]
	ldrh	w0, [x20, #:lo12:.LANCHOR5]
	ubfiz	w0, w0, 1, 15
	strh	w0, [x19, #:lo12:.LANCHOR115]
	and	w0, w0, 65534
	bl	ftl_malloc
	adrp	x1, .LANCHOR116
	str	x0, [x1, #:lo12:.LANCHOR116]
	ldrh	w0, [x19, #:lo12:.LANCHOR115]
	add	x0, x0, 547
	lsr	x0, x0, 9
	strh	w0, [x19, #:lo12:.LANCHOR115]
	lsl	w0, w0, 9
	bl	ftl_malloc
	adrp	x1, .LANCHOR117
	str	x0, [x1, #:lo12:.LANCHOR117]
	adrp	x1, .LANCHOR46
	add	x0, x0, 32
	str	x0, [x1, #:lo12:.LANCHOR46]
	ldrh	w0, [x20, #:lo12:.LANCHOR5]
	lsl	w0, w0, 1
	bl	ftl_malloc
	ldr	w19, [x21, #:lo12:.LANCHOR29]
	adrp	x1, .LANCHOR41
	str	x0, [x1, #:lo12:.LANCHOR41]
	lsl	w19, w19, 1
	mov	w0, w19
	bl	ftl_malloc
	adrp	x1, .LANCHOR118
	str	x0, [x1, #:lo12:.LANCHOR118]
	mov	w0, w19
	bl	ftl_malloc
	adrp	x19, .LANCHOR26
	adrp	x1, .LANCHOR119
	str	x0, [x1, #:lo12:.LANCHOR119]
	ldrh	w0, [x19, #:lo12:.LANCHOR26]
	lsl	w0, w0, 1
	bl	ftl_malloc
	adrp	x1, .LANCHOR35
	str	x0, [x1, #:lo12:.LANCHOR35]
	ldrh	w0, [x19, #:lo12:.LANCHOR26]
	lsl	w0, w0, 1
	bl	ftl_malloc
	adrp	x1, .LANCHOR120
	str	x0, [x1, #:lo12:.LANCHOR120]
	ldrh	w0, [x19, #:lo12:.LANCHOR26]
	adrp	x19, .LANCHOR27
	lsl	w0, w0, 2
	bl	ftl_malloc
	adrp	x1, .LANCHOR121
	str	x0, [x1, #:lo12:.LANCHOR121]
	ldrh	w0, [x19, #:lo12:.LANCHOR27]
	lsl	w0, w0, 2
	bl	ftl_malloc
	ldrh	w2, [x19, #:lo12:.LANCHOR27]
	adrp	x1, .LANCHOR122
	adrp	x19, .LANCHOR32
	str	x0, [x1, #:lo12:.LANCHOR122]
	mov	w1, 0
	lsl	w2, w2, 2
	bl	ftl_memset
	adrp	x0, .LANCHOR31
	ldrh	w0, [x0, #:lo12:.LANCHOR31]
	lsl	w0, w0, 2
	bl	ftl_malloc
	adrp	x1, .LANCHOR123
	str	x0, [x1, #:lo12:.LANCHOR123]
	ldr	w0, [x21, #:lo12:.LANCHOR29]
	lsl	w0, w0, 2
	bl	ftl_malloc
	adrp	x1, .LANCHOR124
	str	x0, [x1, #:lo12:.LANCHOR124]
	ldrh	w0, [x19, #:lo12:.LANCHOR32]
	lsl	w0, w0, 4
	bl	ftl_malloc
	adrp	x1, .LANCHOR54
	str	x0, [x1, #:lo12:.LANCHOR54]
	ldrh	w1, [x19, #:lo12:.LANCHOR32]
	adrp	x19, .LANCHOR126
	ldrh	w0, [x22, #:lo12:.LANCHOR22]
	mul	w0, w1, w0
	bl	ftl_malloc
	adrp	x1, .LANCHOR125
	str	x0, [x1, #:lo12:.LANCHOR125]
	mov	w0, 6
	ldrh	w1, [x20, #:lo12:.LANCHOR5]
	adrp	x20, .LANCHOR9
	mul	w0, w1, w0
	bl	ftl_malloc
	adrp	x1, .LANCHOR39
	str	x0, [x1, #:lo12:.LANCHOR39]
	adrp	x0, .LANCHOR16
	ldrh	w1, [x20, #:lo12:.LANCHOR9]
	ldrh	w0, [x0, #:lo12:.LANCHOR16]
	add	w0, w0, 31
	asr	w0, w0, 5
	strh	w0, [x19, #:lo12:.LANCHOR126]
	mul	w0, w1, w0
	lsl	w0, w0, 2
	bl	ftl_malloc
	adrp	x1, .LANCHOR36
	ldrh	w5, [x19, #:lo12:.LANCHOR126]
	add	x2, x1, :lo12:.LANCHOR36
	ldrh	w7, [x20, #:lo12:.LANCHOR9]
	add	x6, x2, 40
	mov	w3, w5
	str	x0, [x2, 32]
	mov	x0, 1
.L311:
	cmp	w0, w7
	bcc	.L312
	mov	w2, 8
	sub	w2, w2, w0
	add	x2, x2, 1
	add	x1, x1, :lo12:.LANCHOR36
	mov	x3, 0
.L313:
	add	x3, x3, 1
	cmp	x2, x3
	bne	.L314
	mov	w0, 0
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
.L312:
	ldr	x4, [x2, 32]
	add	w0, w0, 1
	add	x4, x4, x3, uxtw 2
	add	w3, w3, w5
	str	x4, [x6], 8
	b	.L311
.L314:
	add	x4, x0, x3
	add	x4, x1, x4, lsl 3
	str	xzr, [x4, 24]
	b	.L313
	.size	FtlMemInit, .-FtlMemInit
	.section	.text.FtlBbt2Bitmap,"ax",@progbits
	.align	2
	.global	FtlBbt2Bitmap
	.type	FtlBbt2Bitmap, %function
FtlBbt2Bitmap:
	stp	x29, x30, [sp, -64]!
	add	x29, sp, 0
	stp	x21, x22, [sp, 32]
	mov	x22, x0
	adrp	x0, .LANCHOR126
	stp	x23, x24, [sp, 48]
	adrp	x21, .LANCHOR16
	adrp	x23, .LANCHOR127
	ldrh	w2, [x0, #:lo12:.LANCHOR126]
	add	x21, x21, :lo12:.LANCHOR16
	add	x23, x23, :lo12:.LANCHOR127
	stp	x19, x20, [sp, 16]
	mov	w24, 65535
	mov	x19, 0
	mov	x20, x1
	lsl	w2, w2, 2
	mov	w1, 0
	mov	x0, x20
	bl	ftl_memset
.L319:
	ldrh	w0, [x22, x19]
	cmp	w0, w24
	beq	.L316
	ldrh	w1, [x21]
	cmp	w1, w0
	bhi	.L318
	adrp	x0, .LC1
	mov	w2, 74
	mov	x1, x23
	add	x0, x0, :lo12:.LC1
	bl	printf
.L318:
	ldrh	w2, [x22, x19]
	mov	w1, 1
	add	x19, x19, 2
	cmp	x19, 1024
	ubfx	x0, x2, 5, 11
	lsl	w2, w1, w2
	lsl	x0, x0, 2
	ldr	w1, [x20, x0]
	orr	w1, w1, w2
	str	w1, [x20, x0]
	bne	.L319
.L316:
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
	adrp	x1, .LANCHOR36
	add	x0, x1, :lo12:.LANCHOR36
	mov	w2, -1
	add	x0, x0, 12
	strh	w2, [x1, #:lo12:.LANCHOR36]
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
	adrp	x1, .LANCHOR37
	add	x3, x1, :lo12:.LANCHOR37
	mov	w2, 2048
	add	x29, sp, 0
	strh	w0, [x1, #:lo12:.LANCHOR37]
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
.L327:
	ldrh	w1, [x19, 6]
	cmp	w1, w0
	bhi	.L331
	adrp	x0, .LANCHOR19
	mov	w23, 0
	mov	w20, 0
	ldrh	w1, [x0, #:lo12:.LANCHOR19]
	ldrh	w0, [x19]
	strh	w1, [x21, x0, lsl 1]
	ldrh	w24, [x21]
.L332:
	ldrh	w0, [x19, 10]
	cmp	w0, w20
	bhi	.L336
	mov	w0, w23
	ldr	x25, [sp, 64]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
.L331:
	ubfiz	x1, x0, 2, 16
	ldr	w2, [x20, x1]
	mov	w1, 0
	ubfx	x2, x2, 10, 16
.L328:
	ldrh	w3, [x19, 10]
	cmp	w3, w1
	bhi	.L330
	add	w0, w0, 1
	and	w0, w0, 65535
	b	.L327
.L330:
	ubfiz	x3, x1, 1, 16
	ldrh	w4, [x22, x3]
	cmp	w4, w2
	bne	.L329
	cbz	w2, .L329
	ldrh	w4, [x21, x3]
	add	w4, w4, 1
	strh	w4, [x21, x3]
.L329:
	add	w1, w1, 1
	and	w1, w1, 65535
	b	.L328
.L336:
	ubfiz	x0, x20, 1, 16
	ldrh	w1, [x21, x0]
	cmp	w24, w1
	bls	.L333
	add	x25, x22, x0
	ldrh	w0, [x22, x0]
	cbnz	w0, .L334
.L335:
	add	w20, w20, 1
	and	w20, w20, 65535
	b	.L332
.L333:
	cbnz	w1, .L335
	add	x25, x22, x0
	ldrh	w0, [x22, x0]
	cbz	w0, .L335
.L337:
	mov	w1, 1
	bl	FtlFreeSysBlkQueueIn
	strh	wzr, [x25]
	ldrh	w0, [x19, 8]
	sub	w0, w0, #1
	strh	w0, [x19, 8]
	b	.L335
.L338:
	mov	w24, 0
	b	.L337
.L334:
	mov	w23, w20
	cbz	w1, .L338
	mov	w24, w1
	b	.L335
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
	adrp	x19, .LANCHOR119
	adrp	x20, .LANCHOR29
	stp	x21, x22, [sp, 32]
	ldr	x0, [x19, #:lo12:.LANCHOR119]
	adrp	x22, .LANCHOR22
	ldr	w2, [x20, #:lo12:.LANCHOR29]
	adrp	x21, .LANCHOR32
	str	x23, [sp, 48]
	adrp	x23, .LANCHOR125
	lsl	w2, w2, 1
	bl	ftl_memset
	ldrh	w0, [x21, #:lo12:.LANCHOR32]
	mov	w1, 255
	ldrh	w2, [x22, #:lo12:.LANCHOR22]
	mul	w2, w2, w0
	ldr	x0, [x23, #:lo12:.LANCHOR125]
	bl	ftl_memset
	adrp	x0, .LANCHOR54
	ldrh	w3, [x21, #:lo12:.LANCHOR32]
	ldr	x6, [x23, #:lo12:.LANCHOR125]
	mov	x1, 0
	ldr	x0, [x0, #:lo12:.LANCHOR54]
	mov	w2, -1
	ldrh	w5, [x22, #:lo12:.LANCHOR22]
	add	x3, x0, x3, lsl 4
.L348:
	add	x4, x1, x5
	cmp	x0, x3
	bne	.L349
	adrp	x1, .LANCHOR128
	add	x0, x1, :lo12:.LANCHOR128
	ldp	x21, x22, [sp, 32]
	strh	w2, [x1, #:lo12:.LANCHOR128]
	ldr	w1, [x20, #:lo12:.LANCHOR29]
	strh	w1, [x0, 10]
	mov	w1, -3902
	strh	w1, [x0, 4]
	adrp	x1, .LANCHOR129
	ldr	x23, [sp, 48]
	strh	w2, [x0, 2]
	ldrh	w1, [x1, #:lo12:.LANCHOR129]
	strh	w1, [x0, 8]
	adrp	x1, .LANCHOR31
	ldrh	w1, [x1, #:lo12:.LANCHOR31]
	strh	w1, [x0, 6]
	adrp	x1, .LANCHOR118
	ldr	x1, [x1, #:lo12:.LANCHOR118]
	str	x1, [x0, 16]
	adrp	x1, .LANCHOR124
	ldr	x1, [x1, #:lo12:.LANCHOR124]
	str	x1, [x0, 24]
	ldr	x1, [x19, #:lo12:.LANCHOR119]
	ldp	x19, x20, [sp, 16]
	str	x1, [x0, 32]
	adrp	x1, .LANCHOR123
	ldr	x1, [x1, #:lo12:.LANCHOR123]
	str	x1, [x0, 40]
	ldp	x29, x30, [sp], 64
	ret
.L349:
	and	x1, x1, -4
	strh	w2, [x0]
	add	x1, x6, x1
	str	wzr, [x0, 4]
	str	x1, [x0, 8]
	add	x0, x0, 16
	mov	x1, x4
	b	.L348
	.size	FtlL2PDataInit, .-FtlL2PDataInit
	.section	.text.FtlVariablesInit,"ax",@progbits
	.align	2
	.global	FtlVariablesInit
	.type	FtlVariablesInit, %function
FtlVariablesInit:
	stp	x29, x30, [sp, -32]!
	adrp	x0, .LANCHOR130
	mov	w1, -1
	add	x29, sp, 0
	strh	w1, [x0, #:lo12:.LANCHOR130]
	adrp	x0, .LANCHOR131
	mov	w1, -1
	str	x19, [sp, 16]
	str	wzr, [x0, #:lo12:.LANCHOR131]
	adrp	x0, .LANCHOR132
	adrp	x19, .LANCHOR5
	str	wzr, [x0, #:lo12:.LANCHOR132]
	adrp	x0, .LANCHOR133
	str	w1, [x0, #:lo12:.LANCHOR133]
	adrp	x0, .LANCHOR34
	mov	w1, 0
	strh	wzr, [x0, #:lo12:.LANCHOR34]
	adrp	x0, .LANCHOR26
	ldrh	w2, [x0, #:lo12:.LANCHOR26]
	adrp	x0, .LANCHOR35
	ldr	x0, [x0, #:lo12:.LANCHOR35]
	lsl	w2, w2, 1
	bl	ftl_memset
	adrp	x0, .LANCHOR46
	ldrh	w2, [x19, #:lo12:.LANCHOR5]
	mov	w1, 0
	ldr	x0, [x0, #:lo12:.LANCHOR46]
	lsl	w2, w2, 1
	bl	ftl_memset
	adrp	x0, .LANCHOR116
	ldrh	w2, [x19, #:lo12:.LANCHOR5]
	mov	w1, 0
	ldr	x0, [x0, #:lo12:.LANCHOR116]
	lsl	w2, w2, 1
	bl	ftl_memset
	mov	w2, 48
	mov	w1, 0
	adrp	x0, .LANCHOR38
	add	x0, x0, :lo12:.LANCHOR38
	bl	ftl_memset
	mov	w2, 512
	mov	w1, 0
	adrp	x0, .LANCHOR134
	add	x0, x0, :lo12:.LANCHOR134
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
	adrp	x0, .LANCHOR5
	mov	w1, 0
	add	x29, sp, 0
	ldrh	w2, [x0, #:lo12:.LANCHOR5]
	mov	w0, 6
	stp	x23, x24, [sp, 48]
	adrp	x24, .LANCHOR39
	stp	x19, x20, [sp, 16]
	adrp	x23, .LANCHOR43
	stp	x21, x22, [sp, 32]
	adrp	x22, .LANCHOR47
	mul	w2, w2, w0
	ldr	x0, [x24, #:lo12:.LANCHOR39]
	stp	x25, x26, [sp, 64]
	adrp	x25, .LANCHOR4
	str	x27, [sp, 80]
	adrp	x26, .LANCHOR12
	add	x25, x25, :lo12:.LANCHOR4
	add	x26, x26, :lo12:.LANCHOR12
	bl	ftl_memset
	mov	w21, 0
	adrp	x0, .LANCHOR45
	mov	w20, 0
	mov	w19, 0
	strh	wzr, [x23, #:lo12:.LANCHOR43]
	str	xzr, [x0, #:lo12:.LANCHOR45]
	adrp	x0, .LANCHOR40
	strh	wzr, [x22, #:lo12:.LANCHOR47]
	adrp	x27, .LANCHOR2
	str	xzr, [x0, #:lo12:.LANCHOR40]
	adrp	x0, .LANCHOR42
	str	xzr, [x0, #:lo12:.LANCHOR42]
.L354:
	ldrh	w0, [x25]
	cmp	w19, w0
	bcs	.L361
	adrp	x0, .LANCHOR18
	ldrh	w8, [x27, #:lo12:.LANCHOR2]
	mov	x6, 0
	mov	w5, 0
	ldrh	w7, [x0, #:lo12:.LANCHOR18]
	b	.L362
.L356:
	ldrb	w0, [x26, x6]
	mov	w1, w19
	bl	V2P_block
	bl	FtlBbmIsBadBlock
	cbnz	w0, .L355
	add	w5, w5, w7
	and	w5, w5, 65535
.L355:
	add	x6, x6, 1
.L362:
	cmp	w8, w6, uxth
	bhi	.L356
	cbz	w5, .L357
	mov	w0, 32768
	sdiv	w5, w0, w5
.L358:
	ldr	x1, [x24, #:lo12:.LANCHOR39]
	mov	w0, 6
	umaddl	x0, w19, w0, x1
	strh	w5, [x0, 4]
	adrp	x0, .LANCHOR50
	ldrh	w0, [x0, #:lo12:.LANCHOR50]
	cmp	w0, w19
	beq	.L359
	adrp	x0, .LANCHOR51
	ldrh	w0, [x0, #:lo12:.LANCHOR51]
	cmp	w0, w19
	beq	.L359
	adrp	x0, .LANCHOR52
	ldrh	w0, [x0, #:lo12:.LANCHOR52]
	cmp	w0, w19
	beq	.L359
	adrp	x1, .LANCHOR41
	ubfiz	x0, x19, 1, 16
	ldr	x1, [x1, #:lo12:.LANCHOR41]
	ldrh	w0, [x1, x0]
	cbnz	w0, .L360
	add	w21, w21, 1
	mov	w0, w19
	and	w21, w21, 65535
	bl	INSERT_FREE_LIST
.L359:
	add	w19, w19, 1
	and	w19, w19, 65535
	b	.L354
.L357:
	adrp	x1, .LANCHOR41
	ubfiz	x0, x19, 1, 16
	mov	w2, -1
	ldr	x1, [x1, #:lo12:.LANCHOR41]
	strh	w2, [x1, x0]
	b	.L358
.L360:
	add	w20, w20, 1
	mov	w0, w19
	and	w20, w20, 65535
	bl	INSERT_DATA_LIST
	b	.L359
.L361:
	strh	w20, [x23, #:lo12:.LANCHOR43]
	add	w20, w20, w21
	strh	w21, [x22, #:lo12:.LANCHOR47]
	cmp	w20, w0
	ble	.L363
	adrp	x1, .LANCHOR135
	adrp	x0, .LC1
	mov	w2, 2219
	add	x1, x1, :lo12:.LANCHOR135
	add	x0, x0, :lo12:.LC1
	bl	printf
.L363:
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
	adrp	x0, .LANCHOR67
	mov	w1, 255
	add	x29, sp, 0
	strh	wzr, [x0, #:lo12:.LANCHOR67]
	adrp	x0, .LANCHOR69
	str	x19, [sp, 16]
	adrp	x19, .LANCHOR20
	strh	wzr, [x0, #:lo12:.LANCHOR69]
	adrp	x0, .LANCHOR68
	ldrh	w2, [x19, #:lo12:.LANCHOR20]
	ldr	x0, [x0, #:lo12:.LANCHOR68]
	lsl	w2, w2, 1
	bl	ftl_memset
	ldrh	w2, [x19, #:lo12:.LANCHOR20]
	mov	w0, 12
	mov	w1, 255
	mul	w2, w2, w0
	adrp	x0, .LANCHOR70
	ldr	x0, [x0, #:lo12:.LANCHOR70]
	bl	ftl_memset
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	b	FtlGcBufInit
	.size	FtlGcPageVarInit, .-FtlGcPageVarInit
	.section	.text.FlashGetBadBlockList,"ax",@progbits
	.align	2
	.global	FlashGetBadBlockList
	.type	FlashGetBadBlockList, %function
FlashGetBadBlockList:
	stp	x29, x30, [sp, -32]!
	mov	w2, 256
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	w20, w1
	mov	w1, 255
	bl	ftl_memset
	adrp	x0, .LANCHOR77
	mov	w1, w20
	ldr	x2, [x0, #:lo12:.LANCHOR77]
	mov	x0, x19
	blr	x2
	and	w0, w0, 65535
	cmp	w0, 50
	bls	.L368
	mov	w2, 256
	mov	w1, 255
	mov	x0, x19
	bl	ftl_memset
	mov	w0, 0
.L368:
	adrp	x1, .LANCHOR0+14
	ldrh	w1, [x1, #:lo12:.LANCHOR0+14]
	cmp	w1, 4
	bne	.L372
	mov	x1, 0
.L370:
	cmp	w0, w1, uxth
	bhi	.L371
.L372:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L371:
	ldrh	w2, [x19, x1, lsl 1]
	lsr	w2, w2, 1
	strh	w2, [x19, x1, lsl 1]
	add	x1, x1, 1
	b	.L370
	.size	FlashGetBadBlockList, .-FlashGetBadBlockList
	.section	.text.ftl_memcpy,"ax",@progbits
	.align	2
	.global	ftl_memcpy
	.type	ftl_memcpy, %function
ftl_memcpy:
	uxtw	x2, w2
	b	memcpy
	.size	ftl_memcpy, .-ftl_memcpy
	.section	.text.FlashReadPages,"ax",@progbits
	.align	2
	.global	FlashReadPages
	.type	FlashReadPages, %function
FlashReadPages:
	stp	x29, x30, [sp, -112]!
	ubfiz	x1, x1, 5, 32
	add	x29, sp, 0
	stp	x21, x22, [sp, 32]
	adrp	x21, .LANCHOR0
	add	x2, x21, :lo12:.LANCHOR0
	str	x27, [sp, 80]
	stp	x23, x24, [sp, 48]
	adrp	x24, .LANCHOR136
	stp	x19, x20, [sp, 16]
	add	x23, x0, x1
	ldrh	w27, [x2, 12]
	mov	x19, x0
	stp	x25, x26, [sp, 64]
	add	x24, x24, :lo12:.LANCHOR136
	adrp	x25, .LC1
	add	x25, x25, :lo12:.LC1
.L376:
	cmp	x23, x19
	bne	.L389
	ldp	x19, x20, [sp, 16]
	mov	w0, 0
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldr	x27, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
.L389:
	ldr	x0, [x19, 8]
	cbz	x0, .L377
	ldr	x0, [x19, 16]
	cbnz	x0, .L378
.L377:
	mov	w2, 90
	mov	x1, x24
	mov	x0, x25
	bl	printf
.L378:
	ldr	w0, [x19, 4]
	add	x2, x29, 104
	add	x1, x29, 108
	bl	l2p_addr_tran.isra.0
	ldr	w0, [x29, 104]
	cmp	w0, 3
	bls	.L379
	mov	w0, -1
	str	w0, [x19]
.L380:
	add	x19, x19, 32
	b	.L376
.L379:
	ldr	x20, [x19, 8]
	adrp	x26, .LANCHOR110
	tst	x20, 63
	beq	.L381
	ldr	x20, [x26, #:lo12:.LANCHOR110]
.L381:
	adrp	x22, .LANCHOR77
	add	x22, x22, :lo12:.LANCHOR77
	ldr	w1, [x29, 108]
	mov	x2, x20
	ldr	x3, [x19, 16]
	ldr	x4, [x22, 24]
	blr	x4
	str	w0, [x19]
	add	x0, x21, :lo12:.LANCHOR0
	ldrh	w0, [x0, 14]
	cmp	w0, 4
	bne	.L383
	ldrb	w0, [x29, 104]
	add	x2, x20, 2048
	ldr	x4, [x22, 24]
	ldr	w1, [x29, 108]
	ldr	x3, [x19, 16]
	add	w1, w27, w1
	add	x3, x3, 8
	blr	x4
	cmn	w0, #1
	beq	.L384
	ldr	x1, [x19, 16]
	ldr	w2, [x1, 12]
	cmn	w2, #1
	bne	.L385
	ldr	w2, [x1, 8]
	cmn	w2, #1
	bne	.L385
	ldr	w1, [x1]
	cmn	w1, #1
	beq	.L385
.L384:
	mov	w1, -1
	str	w1, [x19]
.L385:
	ldr	w1, [x19]
	cmn	w1, #1
	beq	.L386
	cmp	w0, 256
	bne	.L386
	str	w0, [x19]
.L386:
	ldr	w3, [x19]
	cmp	w3, 256
	ccmn	w3, #1, 4, ne
	bne	.L383
	ldr	w1, [x19, 4]
	adrp	x0, .LC11
	ldr	w2, [x29, 108]
	add	x0, x0, :lo12:.LC11
	bl	printf
	ldr	x1, [x19, 8]
	cbz	x1, .L388
	mov	w3, 4
	adrp	x0, .LC12
	mov	w2, w3
	add	x0, x0, :lo12:.LC12
	bl	rknand_print_hex
.L388:
	ldr	x1, [x19, 16]
	cbz	x1, .L383
	mov	w3, 4
	adrp	x0, .LC13
	mov	w2, w3
	add	x0, x0, :lo12:.LC13
	bl	rknand_print_hex
.L383:
	ldr	x0, [x26, #:lo12:.LANCHOR110]
	cmp	x20, x0
	bne	.L380
	ldr	x0, [x19, 8]
	cmp	x20, x0
	beq	.L380
	adrp	x1, .LANCHOR11
	ldrh	w2, [x1, #:lo12:.LANCHOR11]
	mov	x1, x20
	lsl	w2, w2, 9
	bl	ftl_memcpy
	b	.L380
	.size	FlashReadPages, .-FlashReadPages
	.section	.text.FtlLoadFactoryBbt,"ax",@progbits
	.align	2
	.global	FtlLoadFactoryBbt
	.type	FtlLoadFactoryBbt, %function
FtlLoadFactoryBbt:
	stp	x29, x30, [sp, -112]!
	adrp	x2, .LANCHOR105
	adrp	x0, .LANCHOR137
	add	x1, x0, :lo12:.LANCHOR137
	add	x29, sp, 0
	ldr	x2, [x2, #:lo12:.LANCHOR105]
	stp	x21, x22, [sp, 32]
	mov	x22, x0
	stp	x25, x26, [sp, 64]
	adrp	x26, .LANCHOR16
	stp	x27, x28, [sp, 80]
	add	x28, x26, :lo12:.LANCHOR16
	stp	x19, x20, [sp, 16]
	adrp	x20, .LANCHOR36
	stp	x23, x24, [sp, 48]
	add	x20, x20, :lo12:.LANCHOR36
	str	x2, [x1, 8]
	adrp	x2, .LANCHOR113
	adrp	x23, .LANCHOR9
	add	x20, x20, 12
	ldr	x25, [x2, #:lo12:.LANCHOR113]
	add	x23, x23, :lo12:.LANCHOR9
	mov	w21, 0
	mov	w27, -1
	str	x25, [x1, 16]
.L416:
	ldrh	w0, [x23]
	cmp	w21, w0
	bcc	.L421
	ldp	x19, x20, [sp, 16]
	mov	w0, 0
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
.L421:
	ldrh	w19, [x26, #:lo12:.LANCHOR16]
	add	x24, x22, :lo12:.LANCHOR137
	strh	w27, [x20]
	mov	w3, 61664
	sub	w19, w19, #1
	and	w19, w19, 65535
.L417:
	ldrh	w0, [x28]
	sub	w1, w0, #15
	cmp	w1, w19
	bgt	.L419
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
	beq	.L418
	ldrh	w0, [x25]
	cmp	w0, w3
	bne	.L418
	strh	w19, [x20]
.L419:
	add	w21, w21, 1
	add	x20, x20, 2
	b	.L416
.L418:
	sub	w19, w19, #1
	and	w19, w19, 65535
	b	.L417
	.size	FtlLoadFactoryBbt, .-FtlLoadFactoryBbt
	.section	.text.FtlGetLastWrittenPage,"ax",@progbits
	.align	2
	.global	FtlGetLastWrittenPage
	.type	FtlGetLastWrittenPage, %function
FtlGetLastWrittenPage:
	stp	x29, x30, [sp, -160]!
	cmp	w1, 1
	add	x29, sp, 0
	stp	x23, x24, [sp, 48]
	mov	w23, w1
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	bne	.L427
	adrp	x1, .LANCHOR19
	ldrh	w19, [x1, #:lo12:.LANCHOR19]
.L428:
	adrp	x1, .LANCHOR111
	sub	w19, w19, #1
	sxth	w19, w19
	lsl	w21, w0, 10
	ldr	x1, [x1, #:lo12:.LANCHOR111]
	orr	w0, w19, w21
	str	x1, [x29, 72]
	add	x1, x29, 96
	str	w0, [x29, 68]
	mov	w2, w23
	str	x1, [x29, 80]
	add	x0, x29, 64
	mov	w1, 1
	bl	FlashReadPages
	ldr	w0, [x29, 96]
	cmn	w0, #1
	bne	.L429
	mov	w22, 0
	mov	w24, 2
.L430:
	cmp	w22, w19
	ble	.L433
.L429:
	mov	w0, w19
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 160
	ret
.L427:
	adrp	x1, .LANCHOR18
	ldrh	w19, [x1, #:lo12:.LANCHOR18]
	b	.L428
.L433:
	add	w20, w22, w19
	mov	w2, w23
	mov	w1, 1
	sdiv	w20, w20, w24
	sxth	w0, w20
	orr	w0, w0, w21
	str	w0, [x29, 68]
	add	x0, x29, 64
	bl	FlashReadPages
	ldr	w0, [x29, 96]
	cmn	w0, #1
	bne	.L431
	ldr	w0, [x29, 100]
	cmn	w0, #1
	bne	.L431
	ldr	w0, [x29, 64]
	cmn	w0, #1
	beq	.L431
	sub	w19, w20, #1
	sxth	w19, w19
	b	.L430
.L431:
	add	w20, w20, 1
	sxth	w22, w20
	b	.L430
	.size	FtlGetLastWrittenPage, .-FtlGetLastWrittenPage
	.section	.text.FtlScanSysBlk,"ax",@progbits
	.align	2
	.global	FtlScanSysBlk
	.type	FtlScanSysBlk, %function
FtlScanSysBlk:
	stp	x29, x30, [sp, -176]!
	mov	w1, 0
	add	x29, sp, 0
	stp	x25, x26, [sp, 64]
	adrp	x25, .LANCHOR124
	stp	x21, x22, [sp, 32]
	adrp	x21, .LANCHOR29
	ldr	x0, [x25, #:lo12:.LANCHOR124]
	adrp	x22, .LANCHOR121
	ldr	w2, [x21, #:lo12:.LANCHOR29]
	stp	x19, x20, [sp, 16]
	adrp	x20, .LANCHOR129
	stp	x23, x24, [sp, 48]
	adrp	x23, .LANCHOR34
	stp	x27, x28, [sp, 80]
	adrp	x27, .LANCHOR118
	lsl	w2, w2, 2
	strh	wzr, [x20, #:lo12:.LANCHOR129]
	strh	wzr, [x23, #:lo12:.LANCHOR34]
	bl	ftl_memset
	ldr	x0, [x27, #:lo12:.LANCHOR118]
	mov	w1, 0
	ldr	w2, [x21, #:lo12:.LANCHOR29]
	adrp	x19, .LANCHOR26
	adrp	x28, .LANCHOR35
	adrp	x24, .LANCHOR138
	lsl	w2, w2, 1
	bl	ftl_memset
	ldr	x0, [x22, #:lo12:.LANCHOR121]
	mov	w1, 0
	ldrh	w2, [x19, #:lo12:.LANCHOR26]
	lsl	w2, w2, 2
	bl	ftl_memset
	ldr	x0, [x28, #:lo12:.LANCHOR35]
	mov	w1, 0
	ldrh	w2, [x19, #:lo12:.LANCHOR26]
	lsl	w2, w2, 1
	bl	ftl_memset
	mov	w2, 16
	mov	w1, 255
	add	x0, x24, :lo12:.LANCHOR138
	bl	ftl_memset
	adrp	x0, .LANCHOR4
	stp	x22, x25, [x29, 144]
	str	x27, [x29, 160]
	ldrh	w0, [x0, #:lo12:.LANCHOR4]
	str	w0, [x29, 172]
	adrp	x0, .LANCHOR5
	add	x0, x0, :lo12:.LANCHOR5
	str	x0, [x29, 120]
	adrp	x0, .LANCHOR81
	add	x0, x0, :lo12:.LANCHOR81
	str	x0, [x29, 112]
.L439:
	ldr	x0, [x29, 120]
	ldr	w1, [x29, 172]
	ldrh	w0, [x0]
	cmp	w0, w1
	bls	.L479
	adrp	x0, .LANCHOR2
	adrp	x25, .LANCHOR102
	adrp	x6, .LANCHOR12
	mov	x5, 0
	ldrh	w12, [x0, #:lo12:.LANCHOR2]
	adrp	x0, .LANCHOR63
	ldr	x7, [x25, #:lo12:.LANCHOR102]
	mov	w22, 0
	ldr	x11, [x0, #:lo12:.LANCHOR63]
	adrp	x0, .LANCHOR64
	add	x6, x6, :lo12:.LANCHOR12
	ldr	x10, [x0, #:lo12:.LANCHOR64]
	adrp	x0, .LANCHOR23
	ldrh	w8, [x0, #:lo12:.LANCHOR23]
	b	.L480
.L441:
	ldrh	w1, [x29, 172]
	ldrb	w0, [x6, x5]
	bl	V2P_block
	and	w4, w0, 65535
	bl	FtlBbmIsBadBlock
	cbnz	w0, .L440
	ubfiz	x0, x22, 5, 16
	mul	w1, w22, w8
	add	x0, x7, x0
	add	w22, w22, 1
	and	w22, w22, 65535
	lsl	w4, w4, 10
	asr	w1, w1, 2
	add	x1, x10, x1, sxtw 2
	str	w4, [x0, 4]
	stp	x11, x1, [x0, 8]
.L440:
	add	x5, x5, 1
.L480:
	cmp	w12, w5, uxth
	bhi	.L441
	cbnz	w22, .L442
.L478:
	ldr	w0, [x29, 172]
	add	w26, w0, 1
	and	w0, w26, 65535
	str	w0, [x29, 172]
	b	.L439
.L442:
	mov	w1, w22
	mov	w2, 1
	mov	x0, x7
	bl	FlashReadPages
	ubfiz	x0, x22, 5, 16
	mov	x22, 0
	str	x0, [x29, 128]
	adrp	x0, .LANCHOR139
	add	x0, x0, :lo12:.LANCHOR139
	str	x0, [x29, 136]
.L477:
	ldr	x0, [x25, #:lo12:.LANCHOR102]
	add	x1, x0, x22
	ldr	w0, [x0, x22]
	ldr	w3, [x1, 4]
	cmn	w0, #1
	ldr	x27, [x1, 16]
	ubfx	x26, x3, 10, 16
	bne	.L445
	mov	w5, 16
	mov	w7, 65535
.L447:
	ldr	x0, [x25, #:lo12:.LANCHOR102]
	add	x6, x25, :lo12:.LANCHOR102
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
	bne	.L444
	ldr	x0, [x6]
	mov	w1, -1
	str	w1, [x0, x22]
	ldr	x0, [x6]
	ldr	w0, [x0, x22]
	cmp	w0, w1
	bne	.L445
.L446:
	mov	w1, 1
	b	.L516
.L444:
	ldr	x0, [x25, #:lo12:.LANCHOR102]
	ldr	w0, [x0, x22]
	cmn	w0, #1
	bne	.L445
	sub	w5, w5, #1
	ands	w5, w5, 65535
	bne	.L447
	b	.L446
.L445:
	adrp	x0, .LANCHOR81
	ldr	w1, [x0, #:lo12:.LANCHOR81]
	ldr	w0, [x27, 4]
	cmn	w1, #1
	beq	.L448
	cmp	w1, w0
	bhi	.L449
.L448:
	cmn	w0, #1
	beq	.L449
	ldr	x2, [x29, 112]
	add	w1, w0, 1
	str	w1, [x2]
.L449:
	ldrh	w1, [x27]
	mov	w2, 61604
	cmp	w1, w2
	beq	.L451
	bhi	.L452
	mov	w0, 61574
	cmp	w1, w0
	beq	.L453
.L450:
	ldr	x0, [x29, 128]
	add	x22, x22, 32
	cmp	x0, x22
	bne	.L477
	b	.L478
.L452:
	mov	w0, 61634
	cmp	w1, w0
	beq	.L454
	mov	w0, 65535
	cmp	w1, w0
	bne	.L450
	mov	w1, 0
.L516:
	mov	w0, w26
	bl	FtlFreeSysBlkQueueIn
	b	.L450
.L454:
	ldrh	w1, [x20, #:lo12:.LANCHOR129]
	ldr	w0, [x21, #:lo12:.LANCHOR29]
	cmp	w1, w0
	bls	.L456
	ldr	x1, [x29, 136]
	adrp	x0, .LC1
	mov	w2, 1232
	add	x0, x0, :lo12:.LC1
	bl	printf
.L456:
	ldr	w6, [x21, #:lo12:.LANCHOR29]
	ldr	x3, [x29, 152]
	ldrh	w1, [x20, #:lo12:.LANCHOR129]
	and	w2, w6, 65535
	sub	w0, w2, #1
	sub	w2, w2, w1
	sxth	x0, w0
	sub	w2, w2, #1
	ldr	x5, [x3, #:lo12:.LANCHOR124]
	sxth	w2, w2
.L457:
	cmp	w0, w2
	bgt	.L463
	tbz	w0, #31, .L497
	b	.L450
.L463:
	sxtw	x8, w0
	ldr	w11, [x27, 4]
	lsl	x7, x8, 2
	add	x10, x5, x7
	ldr	w7, [x5, x7]
	cmp	w11, w7
	bls	.L458
	ldr	w2, [x5]
	cbnz	w2, .L459
	cmp	w6, w1
	beq	.L459
	add	w1, w1, 1
	strh	w1, [x20, #:lo12:.LANCHOR129]
.L459:
	ldr	x1, [x29, 160]
	ldr	x6, [x1, #:lo12:.LANCHOR118]
	mov	w1, 0
.L460:
	cmp	w1, w0
	bne	.L461
	ldr	w1, [x27, 4]
	str	w1, [x10]
	strh	w26, [x6, x8, lsl 1]
	tbnz	w0, #31, .L450
	ldrh	w1, [x20, #:lo12:.LANCHOR129]
	ldr	w2, [x21, #:lo12:.LANCHOR29]
	sub	w2, w2, w1
	sub	w2, w2, #1
	cmp	w0, w2, sxth
	bgt	.L450
.L497:
	add	w1, w1, 1
	strh	w1, [x20, #:lo12:.LANCHOR129]
	ldr	w1, [x27, 4]
	str	w1, [x5, x0, lsl 2]
	ldr	x1, [x29, 160]
	ldr	x1, [x1, #:lo12:.LANCHOR118]
.L515:
	strh	w26, [x1, x0, lsl 1]
	b	.L450
.L461:
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
	b	.L460
.L458:
	sub	w0, w0, #1
	sxth	x0, w0
	b	.L457
.L453:
	ldrh	w1, [x23, #:lo12:.LANCHOR34]
	ldrh	w0, [x19, #:lo12:.LANCHOR26]
	cmp	w1, w0
	bls	.L466
	ldr	x1, [x29, 136]
	adrp	x0, .LC1
	mov	w2, 1273
	add	x0, x0, :lo12:.LC1
	bl	printf
.L466:
	ldrh	w6, [x19, #:lo12:.LANCHOR26]
	ldrh	w2, [x23, #:lo12:.LANCHOR34]
	sub	w1, w6, #1
	sxth	x0, w1
	sub	w5, w1, w2
	ldr	x1, [x29, 144]
	ldr	x1, [x1, #:lo12:.LANCHOR121]
.L467:
	cmp	w0, w5
	ble	.L472
	sxtw	x7, w0
	ldr	w11, [x27, 4]
	lsl	x8, x7, 2
	add	x10, x1, x8
	ldr	w8, [x1, x8]
	cmp	w11, w8
	bls	.L468
	ldr	w5, [x1]
	cbnz	w5, .L469
	cmp	w6, w2
	beq	.L469
	add	w2, w2, 1
	strh	w2, [x23, #:lo12:.LANCHOR34]
.L469:
	ldr	x6, [x28, #:lo12:.LANCHOR35]
	mov	w2, 0
.L470:
	cmp	w2, w0
	bne	.L471
	ldr	w2, [x27, 4]
	str	w2, [x10]
	strh	w26, [x6, x7, lsl 1]
.L472:
	tbnz	w0, #31, .L450
	ldrh	w2, [x19, #:lo12:.LANCHOR26]
	ldrh	w5, [x23, #:lo12:.LANCHOR34]
	sub	w2, w2, #1
	sub	w2, w2, w5
	cmp	w0, w2, sxth
	bgt	.L450
	add	w5, w5, 1
	ldr	w2, [x27, 4]
	strh	w5, [x23, #:lo12:.LANCHOR34]
	str	w2, [x1, x0, lsl 2]
	ldr	x1, [x28, #:lo12:.LANCHOR35]
	b	.L515
.L471:
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
	b	.L470
.L468:
	sub	w0, w0, #1
	sxth	x0, w0
	b	.L467
.L451:
	ldrh	w5, [x24, #:lo12:.LANCHOR138]
	mov	w1, 65535
	add	x2, x24, :lo12:.LANCHOR138
	cmp	w5, w1
	bne	.L474
	strh	w26, [x24, #:lo12:.LANCHOR138]
	str	w0, [x2, 8]
	b	.L450
.L474:
	ldrh	w0, [x2, 4]
	cmp	w0, w1
	beq	.L475
	mov	w1, 1
	bl	FtlFreeSysBlkQueueIn
.L475:
	add	x0, x24, :lo12:.LANCHOR138
	ldr	w1, [x27, 4]
	ldr	w2, [x0, 8]
	cmp	w2, w1
	bcs	.L476
	ldrh	w2, [x24, #:lo12:.LANCHOR138]
	strh	w2, [x0, 4]
	strh	w26, [x24, #:lo12:.LANCHOR138]
	str	w1, [x0, 8]
	b	.L450
.L476:
	strh	w26, [x0, 4]
	b	.L450
.L479:
	ldr	x0, [x29, 160]
	ldr	x2, [x0, #:lo12:.LANCHOR118]
	ldrh	w0, [x2]
	cbz	w0, .L481
.L484:
	ldr	x1, [x28, #:lo12:.LANCHOR35]
	ldrh	w0, [x1]
	cbz	w0, .L482
.L483:
	ldrh	w1, [x20, #:lo12:.LANCHOR129]
	ldr	w0, [x21, #:lo12:.LANCHOR29]
	cmp	w1, w0
	bls	.L513
	adrp	x1, .LANCHOR139
	adrp	x0, .LC1
	mov	w2, 1398
	add	x1, x1, :lo12:.LANCHOR139
	add	x0, x0, :lo12:.LC1
	bl	printf
.L513:
	ldp	x19, x20, [sp, 16]
	mov	w0, 0
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 176
	ret
.L481:
	ldrh	w0, [x20, #:lo12:.LANCHOR129]
	cbz	w0, .L484
	ldr	w1, [x21, #:lo12:.LANCHOR29]
	mov	w0, 0
.L485:
	cmp	w0, w1
	bcs	.L484
	ldrh	w3, [x2, w0, sxtw 1]
	cbz	w3, .L486
	ldr	x1, [x29, 152]
	add	x7, x21, :lo12:.LANCHOR29
	ldr	x4, [x1, #:lo12:.LANCHOR124]
	mov	w1, w0
.L487:
	ldr	w3, [x7]
	cmp	w1, w3
	bcs	.L484
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
	b	.L487
.L486:
	add	w0, w0, 1
	sxth	w0, w0
	b	.L485
.L482:
	ldrh	w0, [x23, #:lo12:.LANCHOR34]
	cbz	w0, .L483
	ldrh	w2, [x19, #:lo12:.LANCHOR26]
	mov	w0, 0
.L492:
	mov	w6, w0
	cmp	w0, w2
	bge	.L483
	ldrh	w3, [x1, w0, sxtw 1]
	cbz	w3, .L493
	ldr	x2, [x29, 144]
	add	x19, x19, :lo12:.LANCHOR26
	ldr	x3, [x2, #:lo12:.LANCHOR121]
.L494:
	ldrh	w2, [x19]
	cmp	w0, w2
	bge	.L483
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
	b	.L494
.L493:
	add	w0, w0, 1
	sxth	w0, w0
	b	.L492
	.size	FtlScanSysBlk, .-FtlScanSysBlk
	.section	.text.FtlLoadBbt,"ax",@progbits
	.align	2
	.global	FtlLoadBbt
	.type	FtlLoadBbt, %function
FtlLoadBbt:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x23, x24, [sp, 48]
	adrp	x23, .LANCHOR105
	stp	x19, x20, [sp, 16]
	adrp	x24, .LANCHOR16
	stp	x21, x22, [sp, 32]
	adrp	x22, .LANCHOR137
	add	x20, x22, :lo12:.LANCHOR137
	ldr	x0, [x23, #:lo12:.LANCHOR105]
	str	x25, [sp, 64]
	mov	w25, 61649
	str	x0, [x20, 8]
	adrp	x0, .LANCHOR113
	ldr	x21, [x0, #:lo12:.LANCHOR113]
	str	x21, [x20, 16]
	bl	FtlBbtMemInit
	ldrh	w19, [x24, #:lo12:.LANCHOR16]
	add	x24, x24, :lo12:.LANCHOR16
	sub	w19, w19, #1
	and	w19, w19, 65535
.L518:
	ldrh	w0, [x24]
	sub	w0, w0, #15
	cmp	w0, w19
	bgt	.L521
	lsl	w0, w19, 10
	mov	w2, 1
	str	w0, [x20, 4]
	mov	w1, w2
	mov	x0, x20
	bl	FlashReadPages
	ldr	w0, [x20]
	cmn	w0, #1
	bne	.L519
	ldr	w0, [x20, 4]
	mov	w2, 1
	mov	w1, w2
	add	w0, w0, 1
	str	w0, [x20, 4]
	mov	x0, x20
	bl	FlashReadPages
.L519:
	ldr	w0, [x20]
	cmn	w0, #1
	beq	.L520
	ldrh	w0, [x21]
	cmp	w0, w25
	bne	.L520
	adrp	x1, .LANCHOR36
	add	x0, x1, :lo12:.LANCHOR36
	strh	w19, [x1, #:lo12:.LANCHOR36]
	ldr	w1, [x21, 4]
	str	w1, [x0, 8]
	ldrh	w1, [x21, 8]
	strh	w1, [x0, 4]
.L521:
	adrp	x19, .LANCHOR36
	mov	w0, 65535
	add	x20, x19, :lo12:.LANCHOR36
	ldrh	w1, [x19, #:lo12:.LANCHOR36]
	cmp	w1, w0
	beq	.L535
	ldrh	w1, [x20, 4]
	cmp	w1, w0
	beq	.L525
	add	x0, x22, :lo12:.LANCHOR137
	lsl	w1, w1, 10
	mov	w2, 1
	str	w1, [x0, 4]
	mov	w1, w2
	bl	FlashReadPages
	ldr	w0, [x22, #:lo12:.LANCHOR137]
	cmn	w0, #1
	beq	.L525
	ldrh	w1, [x21]
	mov	w0, 61649
	cmp	w1, w0
	bne	.L525
	ldr	w1, [x20, 8]
	ldr	w0, [x21, 4]
	cmp	w0, w1
	bls	.L525
	ldrh	w1, [x20, 4]
	str	w0, [x20, 8]
	ldrh	w0, [x21, 8]
	strh	w1, [x19, #:lo12:.LANCHOR36]
	strh	w0, [x20, 4]
.L525:
	ldrh	w0, [x19, #:lo12:.LANCHOR36]
	add	x24, x19, :lo12:.LANCHOR36
	mov	w1, 1
	mov	w25, 61649
	bl	FtlGetLastWrittenPage
	sxth	w20, w0
	add	w0, w0, 1
	strh	w0, [x24, 2]
	add	x24, x22, :lo12:.LANCHOR137
.L527:
	tbz	w20, #31, .L530
	adrp	x1, .LANCHOR140
	adrp	x0, .LC1
	mov	w2, 251
	add	x1, x1, :lo12:.LANCHOR140
	add	x0, x0, :lo12:.LC1
	bl	printf
.L529:
	add	x0, x19, :lo12:.LANCHOR36
	ldrh	w1, [x21, 10]
	strh	w1, [x0, 6]
	mov	w1, 65535
	ldrh	w0, [x21, 12]
	cmp	w0, w1
	beq	.L532
	adrp	x1, .LANCHOR1
	ldr	w2, [x1, #:lo12:.LANCHOR1]
	cmp	w0, w2
	beq	.L532
	adrp	x1, .LANCHOR5
	ldrh	w1, [x1, #:lo12:.LANCHOR5]
	lsr	w1, w1, 2
	cmp	w2, w1
	bcs	.L532
	cmp	w0, w1
	bcs	.L532
	bl	FtlSysBlkNumInit
.L532:
	add	x19, x19, :lo12:.LANCHOR36
	adrp	x21, .LANCHOR9
	adrp	x23, .LANCHOR126
	add	x19, x19, 32
	add	x21, x21, :lo12:.LANCHOR9
	add	x23, x23, :lo12:.LANCHOR126
	add	x22, x22, :lo12:.LANCHOR137
	mov	w20, 0
.L533:
	ldrh	w0, [x21]
	cmp	w20, w0
	bcc	.L534
	mov	w0, 0
.L517:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldr	x25, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
.L520:
	sub	w19, w19, #1
	and	w19, w19, 65535
	b	.L518
.L530:
	ldrh	w0, [x19, #:lo12:.LANCHOR36]
	mov	w2, 1
	mov	w1, w2
	orr	w0, w20, w0, lsl 10
	str	w0, [x24, 4]
	ldr	x0, [x23, #:lo12:.LANCHOR105]
	str	x0, [x24, 8]
	mov	x0, x24
	bl	FlashReadPages
	ldr	w0, [x24]
	cmn	w0, #1
	beq	.L528
	ldrh	w0, [x21]
	cmp	w0, w25
	beq	.L529
.L528:
	sub	w20, w20, #1
	sxth	w20, w20
	b	.L527
.L534:
	ldrh	w2, [x23]
	ldr	x0, [x22, 8]
	mul	w1, w2, w20
	lsl	w2, w2, 2
	add	w20, w20, 1
	add	x1, x0, x1, lsl 2
	ldr	x0, [x19], 8
	bl	ftl_memcpy
	b	.L533
.L535:
	mov	w0, -1
	b	.L517
	.size	FtlLoadBbt, .-FtlLoadBbt
	.section	.text.FlashProgPages,"ax",@progbits
	.align	2
	.global	FlashProgPages
	.type	FlashProgPages, %function
FlashProgPages:
	stp	x29, x30, [sp, -160]!
	ubfiz	x1, x1, 5, 32
	add	x29, sp, 0
	stp	x21, x22, [sp, 32]
	adrp	x22, .LANCHOR0
	stp	x23, x24, [sp, 48]
	add	x21, x0, x1
	str	w2, [x29, 108]
	add	x2, x22, :lo12:.LANCHOR0
	stp	x19, x20, [sp, 16]
	adrp	x23, .LANCHOR141
	stp	x27, x28, [sp, 80]
	mov	x19, x0
	ldrh	w24, [x2, 12]
	mov	x20, x0
	stp	x25, x26, [sp, 64]
	add	x23, x23, :lo12:.LANCHOR141
	adrp	x25, .LANCHOR77
	add	x28, x25, :lo12:.LANCHOR77
	lsl	w27, w24, 3
.L548:
	cmp	x20, x21
	bne	.L561
	adrp	x20, .LANCHOR110
	adrp	x22, .LANCHOR112
	mov	x23, x20
	mov	x24, x22
.L562:
	cmp	x19, x21
	beq	.L583
	ldr	x1, [x20, #:lo12:.LANCHOR110]
	ldr	x0, [x22, #:lo12:.LANCHOR112]
	str	wzr, [x1]
	str	wzr, [x0]
	stp	x1, x0, [x29, 136]
	mov	w1, 1
	ldr	w2, [x19, 4]
	add	x0, x29, 128
	str	w2, [x29, 132]
	ldr	w2, [x29, 108]
	bl	FlashReadPages
	ldr	w25, [x29, 128]
	cmn	w25, #1
	bne	.L563
	ldr	w1, [x19, 4]
	adrp	x0, .LC14
	add	x0, x0, :lo12:.LC14
	bl	printf
	str	w25, [x19]
.L563:
	ldr	w25, [x29, 128]
	cmp	w25, 256
	bne	.L564
	ldr	w1, [x19, 4]
	adrp	x0, .LC15
	add	x0, x0, :lo12:.LC15
	bl	printf
	str	w25, [x19]
.L564:
	ldr	x0, [x19, 16]
	cbz	x0, .L565
	ldr	w2, [x0]
	ldr	x0, [x24, #:lo12:.LANCHOR112]
	ldr	w3, [x0]
	cmp	w2, w3
	beq	.L565
	ldr	w1, [x19, 4]
	adrp	x0, .LC16
	add	x0, x0, :lo12:.LC16
	bl	printf
	mov	w0, -1
	str	w0, [x19]
.L565:
	ldr	x0, [x19, 8]
	cbz	x0, .L566
	ldr	w2, [x0]
	ldr	x0, [x23, #:lo12:.LANCHOR110]
	ldr	w3, [x0]
	cmp	w2, w3
	beq	.L566
	ldr	w1, [x19, 4]
	adrp	x0, .LC17
	add	x0, x0, :lo12:.LC17
	bl	printf
	mov	w0, -1
	str	w0, [x19]
.L566:
	add	x19, x19, 32
	b	.L562
.L561:
	ldr	x0, [x20, 8]
	cbz	x0, .L549
	ldr	x0, [x20, 16]
	cbnz	x0, .L550
.L549:
	adrp	x0, .LC1
	mov	w2, 142
	mov	x1, x23
	add	x0, x0, :lo12:.LC1
	bl	printf
.L550:
	ldr	w0, [x20, 4]
	add	x2, x29, 120
	add	x1, x29, 124
	bl	l2p_addr_tran.isra.0
	ldr	w0, [x29, 120]
	cmp	w0, 3
	bls	.L551
.L585:
	mov	w0, -1
	str	w0, [x20]
	b	.L552
.L551:
	cbnz	w0, .L553
	ldr	w0, [x29, 124]
	cmp	w27, w0
	bls	.L553
	adrp	x20, .LANCHOR141
	adrp	x22, .LC6
	mov	w23, -1
	add	x20, x20, :lo12:.LANCHOR141
	add	x22, x22, :lo12:.LC6
	b	.L582
.L555:
	ldr	w2, [x19, 4]
	mov	x1, x20
	str	w23, [x19]
	mov	x0, x22
	add	x19, x19, 32
	bl	printf
	ldr	x1, [x19, -24]
	mov	w3, 16
	mov	w2, 4
	adrp	x0, .LC7
	add	x0, x0, :lo12:.LC7
	bl	rknand_print_hex
	ldr	x1, [x19, -16]
	mov	w3, 4
	adrp	x0, .LC8
	mov	w2, w3
	add	x0, x0, :lo12:.LC8
	bl	rknand_print_hex
.L582:
	cmp	x19, x21
	bne	.L555
.L583:
	ldp	x19, x20, [sp, 16]
	mov	w0, 0
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 160
	ret
.L553:
	ldr	x1, [x20, 8]
	tst	x1, 63
	beq	.L569
	adrp	x0, .LANCHOR110
	ldr	x26, [x0, #:lo12:.LANCHOR110]
	cmp	x1, x26
	beq	.L556
	adrp	x0, .LANCHOR11
	ldrh	w2, [x0, #:lo12:.LANCHOR11]
	mov	x0, x26
	lsl	w2, w2, 9
	bl	ftl_memcpy
.L556:
	add	x0, x25, :lo12:.LANCHOR77
	ldr	w1, [x29, 124]
	ldr	x3, [x20, 16]
	mov	x2, x26
	ldr	x5, [x0, 16]
	ldrb	w0, [x29, 120]
	blr	x5
	cbnz	w0, .L557
	str	wzr, [x20]
.L558:
	add	x0, x22, :lo12:.LANCHOR0
	ldrh	w0, [x0, 14]
	cmp	w0, 4
	bne	.L552
	ldrb	w0, [x29, 120]
	add	x2, x26, 2048
	ldr	x5, [x28, 16]
	ldr	w1, [x29, 124]
	ldr	x3, [x20, 16]
	add	w1, w24, w1
	add	x3, x3, 8
	blr	x5
	cbnz	w0, .L585
.L552:
	add	x20, x20, 32
	b	.L548
.L569:
	mov	x26, x1
	b	.L556
.L557:
	mov	w0, -1
	str	w0, [x20]
	b	.L558
	.size	FlashProgPages, .-FlashProgPages
	.section	.text.FtlLowFormatEraseBlock,"ax",@progbits
	.align	2
	.global	FtlLowFormatEraseBlock
	.type	FtlLowFormatEraseBlock, %function
FtlLowFormatEraseBlock:
	stp	x29, x30, [sp, -128]!
	adrp	x7, .LANCHOR12
	add	x7, x7, :lo12:.LANCHOR12
	mov	x5, 0
	add	x29, sp, 0
	stp	x23, x24, [sp, 48]
	and	w23, w0, 65535
	adrp	x0, .LANCHOR98
	stp	x19, x20, [sp, 16]
	stp	x21, x22, [sp, 32]
	adrp	x20, .LANCHOR2
	stp	x25, x26, [sp, 64]
	and	w22, w1, 255
	str	w23, [x0, #:lo12:.LANCHOR98]
	adrp	x21, .LANCHOR78
	adrp	x0, .LANCHOR109
	adrp	x1, .LANCHOR114
	adrp	x25, .LANCHOR23
	ldrh	w8, [x20, #:lo12:.LANCHOR2]
	ldr	x6, [x21, #:lo12:.LANCHOR78]
	mov	w24, 0
	ldr	x10, [x0, #:lo12:.LANCHOR109]
	mov	w19, 0
	ldr	x11, [x1, #:lo12:.LANCHOR114]
	ldrh	w12, [x25, #:lo12:.LANCHOR23]
	stp	x27, x28, [sp, 80]
	str	x0, [x29, 112]
.L587:
	cmp	w8, w5, uxth
	bhi	.L591
	cbz	w24, .L586
	mov	w2, w24
	ubfiz	x24, x24, 5, 16
	mov	x26, 0
	mov	w1, 0
	mov	x0, x6
	bl	FlashEraseBlocks
.L595:
	ldr	x0, [x21, #:lo12:.LANCHOR78]
	add	x1, x0, x26
	ldr	w0, [x0, x26]
	cmn	w0, #1
	bne	.L594
	ldr	w0, [x1, 4]
	add	w19, w19, 1
	and	w19, w19, 65535
	lsr	w0, w0, 10
	bl	FtlBbmMapBadBlock
.L594:
	add	x26, x26, 32
	cmp	x26, x24
	bne	.L595
	cbz	w22, .L608
	adrp	x0, .LANCHOR19
	mov	w26, 1
	ldrh	w28, [x0, #:lo12:.LANCHOR19]
.L596:
	add	x0, x20, :lo12:.LANCHOR2
	adrp	x27, .LANCHOR12
	str	x0, [x29, 120]
	mov	w24, 0
	add	x0, x27, :lo12:.LANCHOR12
	str	x0, [x29, 104]
.L604:
	ldr	x0, [x29, 120]
	mov	x5, 0
	ldr	x6, [x21, #:lo12:.LANCHOR78]
	mov	w20, 0
	ldrh	w11, [x25, #:lo12:.LANCHOR23]
	ldrh	w7, [x0]
	adrp	x0, .LANCHOR108
	ldr	x8, [x0, #:lo12:.LANCHOR108]
	ldr	x0, [x29, 112]
	ldr	x10, [x0, #:lo12:.LANCHOR109]
.L597:
	cmp	w7, w5, uxth
	bhi	.L600
	cbz	w20, .L586
	mov	w1, w20
	mov	w3, 1
	mov	w2, w26
	mov	x0, x6
	bl	FlashProgPages
	mov	x27, 0
	ubfiz	x1, x20, 5, 16
.L603:
	ldr	x0, [x21, #:lo12:.LANCHOR78]
	add	x3, x0, x27
	ldr	w0, [x0, x27]
	cbz	w0, .L602
	ldr	w0, [x3, 4]
	add	w19, w19, 1
	str	x1, [x29, 96]
	and	w19, w19, 65535
	lsr	w0, w0, 10
	bl	FtlBbmMapBadBlock
	ldr	x1, [x29, 96]
.L602:
	add	x27, x27, 32
	cmp	x1, x27
	bne	.L603
	add	w24, w24, 1
	cmp	w28, w24, uxth
	bhi	.L604
	mov	x24, 0
.L606:
	cbz	w22, .L605
	ldr	x0, [x21, #:lo12:.LANCHOR78]
	add	x1, x0, x24
	ldr	w0, [x0, x24]
	cbnz	w0, .L605
	ldr	w0, [x1, 4]
	mov	w1, 1
	lsr	w0, w0, 10
	bl	FtlFreeSysBlkQueueIn
.L605:
	add	x24, x24, 32
	cmp	x24, x27
	bne	.L606
	cmp	w23, 63
	ccmp	w22, 0, 0, hi
	beq	.L586
	ldr	x0, [x21, #:lo12:.LANCHOR78]
	mov	w2, w20
	mov	w1, w26
	bl	FlashEraseBlocks
.L586:
	mov	w0, w19
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 128
	ret
.L591:
	lsl	x0, x5, 5
	mov	w1, w23
	str	wzr, [x6, x0]
	ldrb	w0, [x7, x5]
	bl	V2P_block
	and	w13, w0, 65535
	mov	w14, w13
	cbz	w22, .L588
	bl	IsBlkInVendorPart
	cbnz	w0, .L589
.L588:
	mov	w0, w14
	bl	FtlBbmIsBadBlock
	cbnz	w0, .L590
	ubfiz	x0, x24, 5, 16
	mul	w1, w24, w12
	add	x0, x6, x0
	add	w24, w24, 1
	and	w24, w24, 65535
	lsl	w13, w13, 10
	asr	w1, w1, 2
	add	x1, x11, x1, sxtw 2
	str	w13, [x0, 4]
	stp	x10, x1, [x0, 8]
.L589:
	add	x5, x5, 1
	b	.L587
.L590:
	add	w19, w19, 1
	and	w19, w19, 65535
	b	.L589
.L608:
	mov	w26, 0
	mov	w28, 2
	b	.L596
.L600:
	lsl	x0, x5, 5
	mov	w1, w23
	str	wzr, [x6, x0]
	ldr	x0, [x29, 104]
	ldrb	w0, [x0, x5]
	bl	V2P_block
	and	w12, w0, 65535
	mov	w13, w12
	cbz	w22, .L598
	bl	IsBlkInVendorPart
	cbnz	w0, .L599
.L598:
	mov	w0, w13
	bl	FtlBbmIsBadBlock
	cbnz	w0, .L599
	ubfiz	x0, x20, 5, 16
	mul	w1, w20, w11
	add	x0, x6, x0
	add	w20, w20, 1
	and	w20, w20, 65535
	add	w12, w24, w12, lsl 10
	asr	w1, w1, 2
	add	x1, x10, x1, sxtw 2
	str	w12, [x0, 4]
	stp	x8, x1, [x0, 8]
.L599:
	add	x5, x5, 1
	b	.L597
	.size	FtlLowFormatEraseBlock, .-FtlLowFormatEraseBlock
	.section	.text.FlashTestBlk,"ax",@progbits
	.align	2
	.global	FlashTestBlk
	.type	FlashTestBlk, %function
FlashTestBlk:
	stp	x29, x30, [sp, -128]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	and	w19, w0, 65535
	cmp	w19, 11
	bls	.L632
	adrp	x20, .LANCHOR111
	mov	w2, 32
	mov	w1, 165
	lsl	w19, w19, 10
	ldr	x0, [x20, #:lo12:.LANCHOR111]
	str	x0, [x29, 40]
	add	x0, x29, 64
	str	x0, [x29, 48]
	bl	ftl_memset
	ldr	x0, [x20, #:lo12:.LANCHOR111]
	mov	w2, 8
	mov	w1, 90
	bl	ftl_memset
	str	w19, [x29, 36]
	mov	w2, 1
	add	x0, x29, 32
	mov	w1, w2
	bl	FlashEraseBlocks
	mov	w3, 1
	add	x0, x29, 32
	mov	w2, w3
	mov	w1, w3
	bl	FlashProgPages
	ldr	w0, [x29, 32]
	cbnz	w0, .L633
	add	w0, w19, 1
	mov	w3, 1
	str	w0, [x29, 36]
	mov	w2, w3
	mov	w1, w3
	add	x0, x29, 32
	bl	FlashProgPages
	ldr	w0, [x29, 32]
	cmp	w0, 0
	csetm	w20, ne
.L631:
	mov	w2, 1
	mov	w1, 0
	add	x0, x29, 32
	str	w19, [x29, 36]
	bl	FlashEraseBlocks
.L629:
	mov	w0, w20
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 128
	ret
.L633:
	mov	w20, -1
	b	.L631
.L632:
	mov	w20, 0
	b	.L629
	.size	FlashTestBlk, .-FlashTestBlk
	.section	.text.FtlBbmTblFlush,"ax",@progbits
	.align	2
	.global	FtlBbmTblFlush
	.type	FtlBbmTblFlush, %function
FtlBbmTblFlush:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x23, x24, [sp, 48]
	adrp	x23, .LANCHOR113
	stp	x19, x20, [sp, 16]
	adrp	x20, .LANCHOR137
	stp	x21, x22, [sp, 32]
	add	x19, x20, :lo12:.LANCHOR137
	adrp	x22, .LANCHOR105
	ldr	x1, [x23, #:lo12:.LANCHOR113]
	stp	x25, x26, [sp, 64]
	adrp	x21, .LANCHOR36
	str	x27, [sp, 80]
	add	x25, x21, :lo12:.LANCHOR36
	ldr	x0, [x22, #:lo12:.LANCHOR105]
	adrp	x26, .LANCHOR9
	stp	x0, x1, [x19, 8]
	adrp	x1, .LANCHOR22
	adrp	x27, .LANCHOR126
	add	x25, x25, 32
	ldrh	w2, [x1, #:lo12:.LANCHOR22]
	mov	w24, 0
	add	x26, x26, :lo12:.LANCHOR9
	add	x27, x27, :lo12:.LANCHOR126
	mov	w1, 0
	bl	ftl_memset
.L636:
	ldrh	w0, [x26]
	cmp	w24, w0
	blt	.L637
	add	x20, x20, :lo12:.LANCHOR137
	add	x19, x21, :lo12:.LANCHOR36
	mov	w2, 16
	mov	w1, 255
	adrp	x25, .LC18
	adrp	x26, .LANCHOR19
	ldr	x27, [x20, 16]
	add	x25, x25, :lo12:.LC18
	add	x26, x26, :lo12:.LANCHOR19
	mov	w24, 0
	mov	x0, x27
	bl	ftl_memset
	mov	w0, -3887
	strh	w0, [x27]
	ldr	w0, [x19, 8]
	str	w0, [x27, 4]
	ldrh	w0, [x21, #:lo12:.LANCHOR36]
	mov	w21, 0
	strh	w0, [x27, 2]
	ldrh	w0, [x19, 4]
	strh	w0, [x27, 8]
	ldrh	w0, [x19, 6]
	strh	w0, [x27, 10]
	adrp	x0, .LANCHOR1
	ldr	w0, [x0, #:lo12:.LANCHOR1]
	strh	w0, [x27, 12]
	adrp	x0, .LANCHOR142
	ldr	w0, [x0, #:lo12:.LANCHOR142]
	strh	w0, [x27, 14]
.L638:
	ldrh	w1, [x19]
	ldrh	w4, [x27, 10]
	ldrh	w2, [x19, 2]
	ldrh	w3, [x19, 4]
	ldr	x0, [x22, #:lo12:.LANCHOR105]
	str	x0, [x20, 8]
	ldr	x0, [x23, #:lo12:.LANCHOR113]
	str	x0, [x20, 16]
	orr	w0, w2, w1, lsl 10
	str	wzr, [x20]
	str	w0, [x20, 4]
	mov	x0, x25
	bl	printf
	ldrh	w0, [x26]
	ldrh	w1, [x19, 2]
	sub	w0, w0, #1
	cmp	w1, w0
	blt	.L639
	ldr	w0, [x19, 8]
	mov	w2, 1
	ldrh	w1, [x19, 4]
	add	w0, w0, 1
	str	w0, [x19, 8]
	str	w0, [x27, 4]
	ldrh	w0, [x19]
	strh	w0, [x27, 8]
	strh	w0, [x19, 4]
	adrp	x0, .LANCHOR78
	strh	w1, [x19]
	lsl	w1, w1, 10
	ldr	x0, [x0, #:lo12:.LANCHOR78]
	str	w1, [x20, 4]
	strh	wzr, [x19, 2]
	str	w1, [x0, 4]
	mov	w1, w2
	bl	FlashEraseBlocks
.L639:
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
	bne	.L640
	ldr	w1, [x20, 4]
	add	w21, w21, 1
	adrp	x0, .LC19
	and	w21, w21, 65535
	add	x0, x0, :lo12:.LC19
	bl	printf
	cmp	w21, 3
	bls	.L638
	ldr	w1, [x20, 4]
	adrp	x0, .LC20
	mov	w2, w21
	add	x0, x0, :lo12:.LC20
	bl	printf
.L642:
	b	.L642
.L637:
	ldrh	w2, [x27]
	ldr	x1, [x25], 8
	ldr	x0, [x19, 8]
	mul	w3, w24, w2
	lsl	w2, w2, 2
	add	w24, w24, 1
	add	x0, x0, x3, sxtw 2
	bl	ftl_memcpy
	b	.L636
.L640:
	add	w24, w24, 1
	cmp	w24, 1
	beq	.L638
	cmp	w0, 256
	beq	.L638
	mov	w0, 0
	ldr	x27, [sp, 80]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 96
	ret
	.size	FtlBbmTblFlush, .-FtlBbmTblFlush
	.section	.text.allocate_data_superblock,"ax",@progbits
	.align	2
	.global	allocate_data_superblock
	.type	allocate_data_superblock, %function
allocate_data_superblock:
	stp	x29, x30, [sp, -112]!
	add	x29, sp, 0
	stp	x27, x28, [sp, 80]
	adrp	x28, .LANCHOR47
	stp	x23, x24, [sp, 48]
	add	x24, x28, :lo12:.LANCHOR47
	stp	x19, x20, [sp, 16]
	adrp	x27, .LANCHOR43
	mov	x19, x0
	stp	x21, x22, [sp, 32]
	add	x0, x27, :lo12:.LANCHOR43
	stp	x25, x26, [sp, 64]
	str	x0, [x29, 104]
.L651:
	ldr	x1, [x29, 104]
	adrp	x23, .LANCHOR4
	ldrh	w0, [x28, #:lo12:.LANCHOR47]
	ldrh	w1, [x1]
	add	w0, w0, w1
	ldrh	w1, [x23, #:lo12:.LANCHOR4]
	cmp	w0, w1
	ble	.L652
	adrp	x1, .LANCHOR143
	adrp	x0, .LC1
	mov	w2, 2667
	add	x1, x1, :lo12:.LANCHOR143
	add	x0, x0, :lo12:.LC1
	bl	printf
.L652:
	adrp	x0, .LANCHOR52
	add	x0, x0, :lo12:.LANCHOR52
	cmp	x19, x0
	bne	.L678
	adrp	x1, .LANCHOR94
	ldrh	w0, [x24]
	ldr	w1, [x1, #:lo12:.LANCHOR94]
	mul	w1, w0, w1
	lsr	w0, w0, 1
	add	w0, w0, 1
	add	w1, w0, w1, lsr 2
	ands	w1, w1, 65535
	beq	.L653
	sub	w1, w1, #1
	and	w1, w1, 65535
.L653:
	adrp	x0, .LANCHOR45
	add	x0, x0, :lo12:.LANCHOR45
	bl	List_pop_index_node
	and	w22, w0, 65535
	ldrh	w0, [x24]
	cbnz	w0, .L654
	adrp	x1, .LANCHOR143
	adrp	x0, .LC1
	mov	w2, 2676
	add	x1, x1, :lo12:.LANCHOR143
	add	x0, x0, :lo12:.LC1
	bl	printf
.L654:
	ldrh	w0, [x24]
	sub	w0, w0, #1
	strh	w0, [x24]
	ldrh	w0, [x23, #:lo12:.LANCHOR4]
	cmp	w0, w22
	bls	.L651
	adrp	x25, .LANCHOR41
	ubfiz	x20, x22, 1, 16
	ldr	x0, [x25, #:lo12:.LANCHOR41]
	ldrh	w21, [x0, x20]
	cbnz	w21, .L651
	strh	w22, [x19]
	mov	x0, x19
	bl	make_superblock
	ldrb	w0, [x19, 7]
	cbnz	w0, .L656
	ldr	x0, [x25, #:lo12:.LANCHOR41]
	mov	w1, -1
	strh	w1, [x0, x20]
	mov	w0, w22
	bl	INSERT_DATA_LIST
	ldrh	w1, [x27, #:lo12:.LANCHOR43]
	ldrh	w0, [x24]
	add	w0, w0, w1
	ldrh	w1, [x23, #:lo12:.LANCHOR4]
	cmp	w0, w1
	ble	.L651
	mov	w2, 2690
	adrp	x1, .LANCHOR143
	adrp	x0, .LC1
	add	x1, x1, :lo12:.LANCHOR143
	add	x0, x0, :lo12:.LC1
	bl	printf
	b	.L651
.L678:
	mov	w1, 0
	b	.L653
.L656:
	ldrh	w1, [x27, #:lo12:.LANCHOR43]
	ldrh	w0, [x24]
	add	w0, w0, w1
	ldrh	w1, [x23, #:lo12:.LANCHOR4]
	cmp	w0, w1
	ble	.L658
	adrp	x1, .LANCHOR143
	adrp	x0, .LC1
	mov	w2, 2693
	add	x1, x1, :lo12:.LANCHOR143
	add	x0, x0, :lo12:.LC1
	bl	printf
.L658:
	adrp	x0, .LANCHOR2
	adrp	x25, .LANCHOR78
	add	x26, x19, 16
	mov	w6, 65535
	ldrh	w0, [x0, #:lo12:.LANCHOR2]
	mov	x4, x26
	ldr	x3, [x25, #:lo12:.LANCHOR78]
	ubfiz	x0, x0, 5, 16
	add	x1, x3, 8
	add	x0, x0, 8
	add	x0, x3, x0
.L659:
	cmp	x0, x1
	bne	.L661
	cbnz	w21, .L662
	adrp	x1, .LANCHOR143
	adrp	x0, .LC1
	mov	w2, 2704
	add	x1, x1, :lo12:.LANCHOR143
	add	x0, x0, :lo12:.LC1
	bl	printf
.L662:
	adrp	x0, .LANCHOR144
	ldrh	w0, [x0, #:lo12:.LANCHOR144]
	cmp	w0, w22
	bne	.L663
	adrp	x1, .LANCHOR143
	adrp	x0, .LC1
	mov	w2, 2706
	add	x1, x1, :lo12:.LANCHOR143
	add	x0, x0, :lo12:.LC1
	bl	printf
.L663:
	ldrb	w0, [x19, 8]
	adrp	x3, .LANCHOR46
	adrp	x5, .LANCHOR13
	adrp	x2, .LANCHOR89
	adrp	x1, .LANCHOR90
	ldr	x4, [x3, #:lo12:.LANCHOR46]
	cbnz	w0, .L664
	ldrh	w0, [x4, x20]
	cbz	w0, .L665
	ldrh	w6, [x5, #:lo12:.LANCHOR13]
	add	w0, w0, w6
.L689:
	strh	w0, [x4, x20]
	ldr	w0, [x2, #:lo12:.LANCHOR89]
	add	w0, w0, 1
	str	w0, [x2, #:lo12:.LANCHOR89]
.L667:
	ldr	x0, [x3, #:lo12:.LANCHOR46]
	ldrh	w3, [x0, x20]
	adrp	x0, .LANCHOR91
	ldr	w4, [x0, #:lo12:.LANCHOR91]
	cmp	w3, w4
	bls	.L668
	str	w3, [x0, #:lo12:.LANCHOR91]
.L668:
	ldr	w2, [x2, #:lo12:.LANCHOR89]
	ldr	w1, [x1, #:lo12:.LANCHOR90]
	ldrh	w0, [x5, #:lo12:.LANCHOR13]
	madd	w0, w0, w2, w1
	ldrh	w1, [x23, #:lo12:.LANCHOR4]
	udiv	w0, w0, w1
	adrp	x1, .LANCHOR142
	str	w0, [x1, #:lo12:.LANCHOR142]
	adrp	x0, .LANCHOR117
	ldr	x1, [x0, #:lo12:.LANCHOR117]
	ldr	w0, [x1, 16]
	add	w0, w0, 1
	str	w0, [x1, 16]
	ldr	x0, [x25, #:lo12:.LANCHOR78]
	ubfiz	x1, x21, 5, 16
	add	x1, x1, 4
	add	x2, x0, 4
	add	x1, x0, x1
.L669:
	cmp	x1, x2
	bne	.L670
	ldrb	w1, [x19, 8]
	mov	w2, w21
	mov	x23, 0
	bl	FlashEraseBlocks
	mov	w1, 0
.L671:
	cmp	w21, w23, uxth
	bhi	.L673
	cbz	w1, .L674
	mov	w0, w22
	bl	update_multiplier_value
	bl	FtlBbmTblFlush
.L674:
	ldrb	w0, [x19, 7]
	cbnz	w0, .L675
	adrp	x0, .LANCHOR41
	mov	w1, -1
	ldr	x0, [x0, #:lo12:.LANCHOR41]
	strh	w1, [x0, x20]
	b	.L651
.L661:
	ldrh	w2, [x4]
	stp	xzr, xzr, [x1]
	cmp	w2, w6
	beq	.L660
	ubfiz	x5, x21, 5, 16
	add	w21, w21, 1
	add	x5, x3, x5
	and	w21, w21, 65535
	lsl	w2, w2, 10
	str	w2, [x5, 4]
.L660:
	add	x1, x1, 32
	add	x4, x4, 2
	b	.L659
.L665:
	mov	w0, 2
	b	.L689
.L664:
	ldrh	w0, [x4, x20]
	add	w0, w0, 1
	strh	w0, [x4, x20]
	ldr	w0, [x1, #:lo12:.LANCHOR90]
	add	w0, w0, 1
	str	w0, [x1, #:lo12:.LANCHOR90]
	b	.L667
.L670:
	ldr	w3, [x2]
	and	w3, w3, -1024
	str	w3, [x2], 32
	b	.L669
.L673:
	ldr	x2, [x25, #:lo12:.LANCHOR78]
	lsl	x0, x23, 5
	add	x3, x2, x0
	ldr	w2, [x2, x0]
	cmn	w2, #1
	bne	.L672
	add	w1, w1, 1
	ldr	w0, [x3, 4]
	stp	w2, w1, [x29, 96]
	lsr	w0, w0, 10
	bl	FtlBbmMapBadBlock
	ldp	w2, w1, [x29, 96]
	strh	w2, [x26]
	ldrb	w0, [x19, 7]
	sub	w0, w0, #1
	strb	w0, [x19, 7]
.L672:
	add	x23, x23, 1
	add	x26, x26, 2
	b	.L671
.L675:
	adrp	x1, .LANCHOR18
	adrp	x2, .LANCHOR81
	strh	wzr, [x19, 2]
	ldrh	w1, [x1, #:lo12:.LANCHOR18]
	strh	w22, [x19]
	strb	wzr, [x19, 6]
	mul	w0, w0, w1
	ldr	w1, [x2, #:lo12:.LANCHOR81]
	str	w1, [x19, 12]
	add	w1, w1, 1
	str	w1, [x2, #:lo12:.LANCHOR81]
	adrp	x1, .LANCHOR41
	and	w0, w0, 65535
	strh	w0, [x19, 4]
	ldr	x1, [x1, #:lo12:.LANCHOR41]
	strh	w0, [x1, x20]
	ldrh	w0, [x19, 4]
	cbz	w0, .L676
	ldrb	w0, [x19, 7]
	cbnz	w0, .L677
.L676:
	adrp	x1, .LANCHOR143
	adrp	x0, .LC1
	mov	w2, 2759
	add	x1, x1, :lo12:.LANCHOR143
	add	x0, x0, :lo12:.LC1
	bl	printf
.L677:
	ldp	x19, x20, [sp, 16]
	mov	w0, 0
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
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
	adrp	x21, .LANCHOR73
	stp	x25, x26, [sp, 64]
	and	w25, w0, 65535
	ldrh	w0, [x21, #:lo12:.LANCHOR73]
	stp	x19, x20, [sp, 16]
	stp	x23, x24, [sp, 48]
	str	x27, [sp, 80]
	cbz	w0, .L691
	adrp	x23, .LANCHOR74
	add	x24, x23, :lo12:.LANCHOR74
	mov	w19, 0
.L692:
	adrp	x0, .LANCHOR2
	ldrh	w0, [x0, #:lo12:.LANCHOR2]
	cmp	w0, w19
	bhi	.L698
	bl	FtlGcReFreshBadBlk
.L691:
	mov	w0, 0
	ldr	x27, [sp, 80]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 96
	ret
.L698:
	adrp	x0, .LANCHOR12
	add	x0, x0, :lo12:.LANCHOR12
	mov	w1, w25
	add	x22, x21, :lo12:.LANCHOR73
	mov	w20, 0
	ldrb	w0, [x0, w19, sxtw]
	bl	V2P_block
	and	w26, w0, 65535
.L693:
	ldrh	w0, [x22]
	cmp	w0, w20
	bhi	.L697
	add	w19, w19, 1
	and	w19, w19, 65535
	b	.L692
.L697:
	add	x0, x23, :lo12:.LANCHOR74
	add	w27, w20, 1
	ldrh	w0, [x0, w20, sxtw 1]
	cmp	w0, w26
	bne	.L694
	mov	w0, w26
	bl	FtlBbmMapBadBlock
	bl	FtlBbmTblFlush
	ldrh	w1, [x22]
	sxtw	x3, w27
	and	x4, x20, 65535
	mov	x0, 0
.L695:
	add	w2, w20, w0
	cmp	w1, w2, uxth
	bhi	.L696
	sub	w1, w1, #1
	strh	w1, [x22]
.L694:
	and	w20, w27, 65535
	b	.L693
.L696:
	add	x2, x3, x0
	ldrh	w5, [x24, x2, lsl 1]
	add	x2, x4, x0
	add	x0, x0, 1
	strh	w5, [x24, x2, lsl 1]
	b	.L695
	.size	FtlGcFreeBadSuperBlk, .-FtlGcFreeBadSuperBlk
	.section	.text.update_vpc_list,"ax",@progbits
	.align	2
	.global	update_vpc_list
	.type	update_vpc_list, %function
update_vpc_list:
	stp	x29, x30, [sp, -32]!
	adrp	x1, .LANCHOR41
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	and	w19, w0, 65535
	ldr	x1, [x1, #:lo12:.LANCHOR41]
	ubfiz	x0, x19, 1, 16
	ldrh	w0, [x1, x0]
	cbnz	w0, .L704
	adrp	x0, .LANCHOR71
	ldrh	w1, [x0, #:lo12:.LANCHOR71]
	cmp	w1, w19
	bne	.L705
	mov	w1, -1
	strh	w1, [x0, #:lo12:.LANCHOR71]
.L705:
	adrp	x0, .LANCHOR72
	ldrh	w1, [x0, #:lo12:.LANCHOR72]
	cmp	w1, w19
	bne	.L706
	mov	w1, -1
	strh	w1, [x0, #:lo12:.LANCHOR72]
.L706:
	adrp	x0, .LANCHOR144
	ldrh	w1, [x0, #:lo12:.LANCHOR144]
	cmp	w1, w19
	bne	.L707
	mov	w1, -1
	strh	w1, [x0, #:lo12:.LANCHOR144]
.L708:
	adrp	x20, .LANCHOR43
	mov	w1, w19
	adrp	x0, .LANCHOR40
	add	x0, x0, :lo12:.LANCHOR40
	bl	List_remove_node
	ldrh	w0, [x20, #:lo12:.LANCHOR43]
	cbnz	w0, .L710
	adrp	x1, .LANCHOR145
	adrp	x0, .LC1
	mov	w2, 2835
	add	x1, x1, :lo12:.LANCHOR145
	add	x0, x0, :lo12:.LC1
	bl	printf
.L710:
	ldrh	w0, [x20, #:lo12:.LANCHOR43]
	sub	w0, w0, #1
	strh	w0, [x20, #:lo12:.LANCHOR43]
	mov	w0, w19
	bl	free_data_superblock
	mov	w0, w19
	bl	FtlGcFreeBadSuperBlk
	adrp	x0, .LANCHOR47
	ldrh	w1, [x20, #:lo12:.LANCHOR43]
	ldrh	w0, [x0, #:lo12:.LANCHOR47]
	add	w0, w0, w1
	adrp	x1, .LANCHOR4
	ldrh	w1, [x1, #:lo12:.LANCHOR4]
	cmp	w0, w1
	ble	.L714
	adrp	x1, .LANCHOR145
	adrp	x0, .LC1
	mov	w2, 2838
	add	x1, x1, :lo12:.LANCHOR145
	add	x0, x0, :lo12:.LC1
	bl	printf
.L714:
	mov	w0, 1
	b	.L703
.L707:
	adrp	x0, .LANCHOR50
	ldrh	w0, [x0, #:lo12:.LANCHOR50]
	cmp	w0, w19
	beq	.L713
	adrp	x0, .LANCHOR51
	ldrh	w0, [x0, #:lo12:.LANCHOR51]
	cmp	w0, w19
	beq	.L713
	adrp	x0, .LANCHOR52
	ldrh	w0, [x0, #:lo12:.LANCHOR52]
	cmp	w0, w19
	bne	.L708
.L713:
	mov	w0, 0
.L703:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L704:
	mov	w0, w19
	bl	List_update_data_list
	b	.L713
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
	str	x21, [sp, 32]
	mov	w0, 65535
	cmp	w19, w0
	beq	.L717
	adrp	x21, .LANCHOR41
	ubfiz	x20, x19, 1, 16
	ldr	x1, [x21, #:lo12:.LANCHOR41]
	ldrh	w0, [x1, x20]
	cbnz	w0, .L718
	mov	w2, 0
	mov	w1, w19
	adrp	x0, .LC21
	add	x0, x0, :lo12:.LC21
	bl	printf
	ldr	x0, [x21, #:lo12:.LANCHOR41]
	ldrh	w0, [x0, x20]
	cbz	w0, .L719
.L724:
	mov	w20, 0
.L716:
	mov	w0, w20
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
.L719:
	mov	w2, 2853
	adrp	x1, .LANCHOR146
	adrp	x0, .LC1
	add	x1, x1, :lo12:.LANCHOR146
	add	x0, x0, :lo12:.LC1
	bl	printf
	b	.L724
.L718:
	sub	w0, w0, #1
	strh	w0, [x1, x20]
.L717:
	adrp	x21, .LANCHOR130
	mov	w1, 65535
	ldrh	w0, [x21, #:lo12:.LANCHOR130]
	cmp	w0, w1
	bne	.L721
	strh	w19, [x21, #:lo12:.LANCHOR130]
	b	.L724
.L721:
	cmp	w19, w0
	beq	.L724
	bl	update_vpc_list
	cmp	w0, 0
	adrp	x1, .LANCHOR39
	adrp	x0, .LANCHOR40
	strh	w19, [x21, #:lo12:.LANCHOR130]
	cset	w20, ne
	ldr	x1, [x1, #:lo12:.LANCHOR39]
	ldr	x0, [x0, #:lo12:.LANCHOR40]
	sub	x0, x0, x1
	mov	x1, -6148914691236517206
	asr	x0, x0, 1
	movk	x1, 0xaaab, lsl 0
	mul	x0, x0, x1
	adrp	x1, .LANCHOR41
	ldr	x1, [x1, #:lo12:.LANCHOR41]
	and	x2, x0, 65535
	ldrh	w1, [x1, x2, lsl 1]
	cbnz	w1, .L716
	cmp	w19, w0, uxth
	beq	.L716
	mov	w2, 2869
	adrp	x1, .LANCHOR146
	adrp	x0, .LC1
	add	x1, x1, :lo12:.LANCHOR146
	add	x0, x0, :lo12:.LC1
	bl	printf
	b	.L716
	.size	decrement_vpc_count, .-decrement_vpc_count
	.section	.text.FtlSuperblockPowerLostFix,"ax",@progbits
	.align	2
	.global	FtlSuperblockPowerLostFix
	.type	FtlSuperblockPowerLostFix, %function
FtlSuperblockPowerLostFix:
	stp	x29, x30, [sp, -80]!
	adrp	x1, .LANCHOR113
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	mov	w0, -1
	stp	x21, x22, [sp, 32]
	str	w0, [x29, 72]
	adrp	x0, .LANCHOR105
	ldr	x21, [x1, #:lo12:.LANCHOR113]
	mov	w1, -3
	ldr	x0, [x0, #:lo12:.LANCHOR105]
	adrp	x22, .LANCHOR82
	str	x21, [x29, 64]
	add	x22, x22, :lo12:.LANCHOR82
	str	x0, [x29, 56]
	ldrh	w20, [x19, 4]
	str	w1, [x21, 8]
	mov	w1, -2
	str	w1, [x21, 12]
	and	w20, w20, 1
	ldrh	w1, [x19]
	add	w20, w20, 6
	strh	w1, [x21, 2]
	strh	wzr, [x21]
	mov	w1, 61589
	str	w1, [x0]
	mov	w1, 22136
	movk	w1, 0x1234, lsl 16
	str	w1, [x0, 4]
.L731:
	ldrh	w0, [x19, 4]
	cbnz	w0, .L727
.L728:
	ldrh	w0, [x19]
	adrp	x1, .LANCHOR41
	ldrh	w3, [x19, 4]
	ldr	x2, [x1, #:lo12:.LANCHOR41]
	lsl	x0, x0, 1
	ldrh	w1, [x2, x0]
	sub	w1, w1, w3
	strh	w1, [x2, x0]
	adrp	x0, .LANCHOR18
	strb	wzr, [x19, 6]
	strh	wzr, [x19, 4]
	ldrh	w0, [x0, #:lo12:.LANCHOR18]
	strh	w0, [x19, 2]
	ldp	x21, x22, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 80
	ret
.L727:
	mov	x0, x19
	bl	get_new_active_ppa
	str	w0, [x29, 52]
	cmn	w0, #1
	beq	.L728
	ldr	w0, [x22]
	mov	w3, 0
	str	w0, [x21, 4]
	mov	w2, 0
	add	w0, w0, 1
	mov	w1, 1
	cmn	w0, #1
	csel	w0, w0, wzr, ne
	str	w0, [x22]
	add	x0, x29, 48
	bl	FlashProgPages
	ldrh	w0, [x19]
	bl	decrement_vpc_count
	subs	w20, w20, #1
	bne	.L731
	b	.L728
	.size	FtlSuperblockPowerLostFix, .-FtlSuperblockPowerLostFix
	.section	.text.FtlMakeBbt,"ax",@progbits
	.align	2
	.global	FtlMakeBbt
	.type	FtlMakeBbt, %function
FtlMakeBbt:
	stp	x29, x30, [sp, -128]!
	add	x29, sp, 0
	stp	x21, x22, [sp, 32]
	mov	w22, 0
	stp	x19, x20, [sp, 16]
	adrp	x20, .LANCHOR36
	stp	x23, x24, [sp, 48]
	add	x21, x20, :lo12:.LANCHOR36
	stp	x25, x26, [sp, 64]
	add	x24, x21, 32
	stp	x27, x28, [sp, 80]
	bl	FtlBbtMemInit
	bl	FtlLoadFactoryBbt
	adrp	x28, .LANCHOR137
	add	x21, x21, 12
	add	x25, x28, :lo12:.LANCHOR137
	adrp	x0, .LANCHOR9
	add	x0, x0, :lo12:.LANCHOR9
	str	x0, [x29, 120]
.L740:
	ldr	x0, [x29, 120]
	ldrh	w0, [x0]
	cmp	w22, w0
	bcc	.L746
	adrp	x21, .LANCHOR24
	add	x21, x21, :lo12:.LANCHOR24
	mov	w19, 0
.L747:
	ldrh	w0, [x21]
	cmp	w0, w19
	bhi	.L748
	add	x21, x20, :lo12:.LANCHOR36
	mov	w22, 65535
	ldrh	w19, [x21, 12]
	sub	w19, w19, #1
	and	w19, w19, 65535
.L749:
	ldrh	w0, [x21, 12]
	sub	w0, w0, #47
	cmp	w0, w19
	bgt	.L753
	mov	w0, w19
	bl	FtlBbmIsBadBlock
	cmp	w0, 1
	beq	.L750
	mov	w0, w19
	bl	FlashTestBlk
	cbz	w0, .L751
	mov	w0, w19
	bl	FtlBbmMapBadBlock
.L750:
	sub	w19, w19, #1
	and	w19, w19, 65535
	b	.L749
.L746:
	adrp	x2, .LANCHOR113
	adrp	x0, .LANCHOR105
	add	x19, x28, :lo12:.LANCHOR137
	ldrh	w1, [x21]
	ldr	x0, [x0, #:lo12:.LANCHOR105]
	mov	w3, 65535
	ldr	x26, [x2, #:lo12:.LANCHOR113]
	cmp	w1, w3
	stp	x0, x26, [x19, 8]
	adrp	x23, .LANCHOR16
	str	x2, [x29, 112]
	beq	.L741
	ldrh	w4, [x23, #:lo12:.LANCHOR16]
	mov	w2, 1
	madd	w27, w4, w22, w1
	mov	w1, w2
	lsl	w0, w27, 10
	str	w0, [x19, 4]
	mov	x0, x19
	bl	FlashReadPages
	ldr	x1, [x19, 8]
	ldr	x0, [x24]
	ldrh	w2, [x23, #:lo12:.LANCHOR16]
	add	w2, w2, 7
	lsr	w2, w2, 3
	bl	ftl_memcpy
.L742:
	mov	w0, w27
	add	w22, w22, 1
	bl	FtlBbmMapBadBlock
	add	x24, x24, 8
	add	x21, x21, 2
	b	.L740
.L741:
	mov	w1, w22
	bl	FlashGetBadBlockList
	ldr	x0, [x19, 8]
	ldr	x1, [x24]
	bl	FtlBbt2Bitmap
	ldrh	w19, [x23, #:lo12:.LANCHOR16]
	add	x23, x23, :lo12:.LANCHOR16
	adrp	x0, .LANCHOR126
	sub	w19, w19, #1
	add	x0, x0, :lo12:.LANCHOR126
	and	w19, w19, 65535
	str	x0, [x29, 104]
.L743:
	ldrh	w0, [x23]
	madd	w0, w22, w0, w19
	bl	FtlBbmIsBadBlock
	cmp	w0, 1
	beq	.L744
	ldr	x0, [x29, 112]
	mov	w2, 16
	strh	w19, [x21]
	mov	w1, 0
	ldr	x0, [x0, #:lo12:.LANCHOR113]
	bl	ftl_memset
	adrp	x0, .LANCHOR105
	mov	w2, 4096
	mov	w1, 0
	ldr	x0, [x0, #:lo12:.LANCHOR105]
	bl	ftl_memset
	mov	w0, -3872
	strh	w0, [x26]
	ldrh	w4, [x23]
	ldrh	w0, [x21]
	strh	w0, [x26, 2]
	ldr	x1, [x24]
	str	wzr, [x26, 4]
	madd	w27, w4, w22, w0
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
	bne	.L742
	mov	w0, w27
	bl	FtlBbmMapBadBlock
	b	.L743
.L744:
	sub	w19, w19, #1
	and	w19, w19, 65535
	b	.L743
.L748:
	mov	w0, w19
	add	w19, w19, 1
	bl	FtlBbmMapBadBlock
	and	w19, w19, 65535
	b	.L747
.L751:
	ldrh	w0, [x21]
	cmp	w0, w22
	bne	.L752
	strh	w19, [x21]
	b	.L750
.L752:
	strh	w19, [x21, 4]
.L753:
	adrp	x0, .LANCHOR78
	add	x19, x20, :lo12:.LANCHOR36
	ldrh	w1, [x20, #:lo12:.LANCHOR36]
	mov	w2, 2
	ldr	x0, [x0, #:lo12:.LANCHOR78]
	str	wzr, [x19, 8]
	lsl	w1, w1, 10
	strh	wzr, [x19, 2]
	str	w1, [x0, 4]
	ldrh	w1, [x19, 4]
	lsl	w1, w1, 10
	str	w1, [x0, 36]
	mov	w1, 1
	bl	FlashEraseBlocks
	ldrh	w0, [x20, #:lo12:.LANCHOR36]
	bl	FtlBbmMapBadBlock
	ldrh	w0, [x19, 4]
	bl	FtlBbmMapBadBlock
	bl	FtlBbmTblFlush
	strh	wzr, [x19, 2]
	ldr	w0, [x19, 8]
	ldrh	w1, [x19, 4]
	add	w0, w0, 1
	str	w0, [x19, 8]
	ldrh	w0, [x20, #:lo12:.LANCHOR36]
	strh	w0, [x19, 4]
	strh	w1, [x20, #:lo12:.LANCHOR36]
	bl	FtlBbmTblFlush
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 128
	ret
	.size	FtlMakeBbt, .-FtlMakeBbt
	.section	.text.ftl_memcmp,"ax",@progbits
	.align	2
	.global	ftl_memcmp
	.type	ftl_memcmp, %function
ftl_memcmp:
	uxtw	x2, w2
	b	memcmp
	.size	ftl_memcmp, .-ftl_memcmp
	.section	.text.js_hash,"ax",@progbits
	.align	2
	.global	js_hash
	.type	js_hash, %function
js_hash:
	mov	x4, x0
	mov	w0, 42982
	mov	x3, 0
	movk	w0, 0x47c6, lsl 16
.L761:
	cmp	w1, w3
	bhi	.L762
	ret
.L762:
	lsr	w2, w0, 2
	ldrb	w5, [x4, x3]
	add	w2, w2, w0, lsl 5
	add	x3, x3, 1
	add	w2, w2, w5
	eor	w0, w0, w2
	b	.L761
	.size	js_hash, .-js_hash
	.section	.text.Ftl_write_map_blk_to_last_page,"ax",@progbits
	.align	2
	.global	Ftl_write_map_blk_to_last_page
	.type	Ftl_write_map_blk_to_last_page, %function
Ftl_write_map_blk_to_last_page:
	stp	x29, x30, [sp, -64]!
	mov	w1, 65535
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	ldr	x20, [x0, 16]
	stp	x21, x22, [sp, 32]
	ldrh	w0, [x0]
	stp	x23, x24, [sp, 48]
	cmp	w0, w1
	bne	.L764
	ldrh	w0, [x19, 8]
	cbz	w0, .L765
	adrp	x1, .LANCHOR147
	adrp	x0, .LC1
	mov	w2, 641
	add	x1, x1, :lo12:.LANCHOR147
	add	x0, x0, :lo12:.LC1
	bl	printf
.L765:
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
.L766:
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 64
	ret
.L764:
	ubfiz	x0, x0, 1, 16
	adrp	x2, .LANCHOR113
	adrp	x24, .LANCHOR105
	ldr	x23, [x19, 40]
	ldr	x21, [x2, #:lo12:.LANCHOR113]
	ldrh	w22, [x20, x0]
	adrp	x20, .LANCHOR137
	ldrh	w0, [x19, 2]
	add	x1, x20, :lo12:.LANCHOR137
	orr	w0, w0, w22, lsl 10
	str	w0, [x1, 4]
	ldr	x0, [x24, #:lo12:.LANCHOR105]
	str	x21, [x1, 16]
	str	x0, [x1, 8]
	ldr	w1, [x19, 48]
	str	w1, [x21, 4]
	mov	w1, -1291
	strh	w1, [x21, 8]
	ldrh	w1, [x19, 4]
	strh	w1, [x21]
	adrp	x1, .LANCHOR19
	strh	w22, [x21, 2]
	ldrh	w2, [x1, #:lo12:.LANCHOR19]
	mov	w1, 255
	lsl	w2, w2, 3
	bl	ftl_memset
	ldrh	w4, [x19, 6]
	mov	x0, 0
	ldr	x3, [x24, #:lo12:.LANCHOR105]
	mov	w1, 0
.L767:
	cmp	w4, w0, uxth
	bhi	.L769
	add	x20, x20, :lo12:.LANCHOR137
	adrp	x0, .LANCHOR22
	ldrh	w1, [x0, #:lo12:.LANCHOR22]
	ldr	x0, [x20, 8]
	bl	js_hash
	str	w0, [x21, 12]
	mov	w2, 1
	mov	w3, 0
	mov	w1, w2
	mov	x0, x20
	bl	FlashProgPages
	ldrh	w0, [x19, 2]
	add	w0, w0, 1
	strh	w0, [x19, 2]
	mov	x0, x19
	bl	ftl_map_blk_gc
	b	.L766
.L769:
	ldr	w2, [x23, x0, lsl 2]
	cmp	w22, w2, lsr 10
	bne	.L768
	add	w1, w1, 1
	and	w1, w1, 65535
	ubfiz	x2, x1, 1, 16
	str	w0, [x3, x2, lsl 2]
	add	x2, x2, 1
	ldr	w5, [x23, x0, lsl 2]
	str	w5, [x3, x2, lsl 2]
.L768:
	add	x0, x0, 1
	b	.L767
	.size	Ftl_write_map_blk_to_last_page, .-Ftl_write_map_blk_to_last_page
	.section	.text.FtlMapWritePage,"ax",@progbits
	.align	2
	.global	FtlMapWritePage
	.type	FtlMapWritePage, %function
FtlMapWritePage:
	stp	x29, x30, [sp, -112]!
	add	x29, sp, 0
	stp	x23, x24, [sp, 48]
	mov	w24, w1
	stp	x21, x22, [sp, 32]
	adrp	x23, .LANCHOR148
	stp	x25, x26, [sp, 64]
	adrp	x22, .LANCHOR87
	stp	x27, x28, [sp, 80]
	adrp	x25, .LANCHOR19
	stp	x19, x20, [sp, 16]
	mov	x27, x2
	mov	x19, x0
	ubfiz	x26, x24, 2, 32
	add	x22, x22, :lo12:.LANCHOR87
	add	x23, x23, :lo12:.LANCHOR148
	add	x28, x25, :lo12:.LANCHOR19
	mov	w21, 0
.L775:
	ldr	w0, [x22]
	ldrh	w1, [x19, 2]
	add	w0, w0, 1
	str	w0, [x22]
	ldrh	w0, [x25, #:lo12:.LANCHOR19]
	sub	w0, w0, #1
	cmp	w1, w0
	bge	.L776
	ldrh	w1, [x19]
	mov	w0, 65535
	cmp	w1, w0
	bne	.L777
.L776:
	mov	x0, x19
	bl	Ftl_write_map_blk_to_last_page
.L777:
	ldrh	w1, [x19]
	ldr	x0, [x19, 16]
	ldrh	w0, [x0, x1, lsl 1]
	cbnz	w0, .L778
	adrp	x0, .LC1
	mov	w2, 700
	mov	x1, x23
	add	x0, x0, :lo12:.LC1
	bl	printf
.L778:
	ldrh	w1, [x19]
	ldrh	w0, [x19, 10]
	cmp	w1, w0
	bcc	.L779
	adrp	x0, .LC1
	mov	w2, 701
	mov	x1, x23
	add	x0, x0, :lo12:.LC1
	bl	printf
.L779:
	ldrh	w1, [x19]
	adrp	x4, .LANCHOR137
	ldr	x0, [x19, 16]
	add	x20, x4, :lo12:.LANCHOR137
	str	x4, [x29, 96]
	mov	w2, 16
	ldrh	w3, [x0, x1, lsl 1]
	mov	w1, 0
	ldrh	w0, [x19, 2]
	str	w3, [x29, 104]
	str	x27, [x20, 8]
	orr	w0, w0, w3, lsl 10
	str	w0, [x20, 4]
	adrp	x0, .LANCHOR113
	ldr	x0, [x0, #:lo12:.LANCHOR113]
	str	x0, [x20, 16]
	bl	ftl_memset
	ldr	x6, [x20, 16]
	ldr	w0, [x19, 48]
	ldr	w3, [x29, 104]
	str	w0, [x6, 4]
	ldrh	w0, [x19, 4]
	strh	w0, [x6]
	adrp	x0, .LANCHOR22
	strh	w3, [x6, 2]
	strh	w24, [x6, 8]
	ldrh	w1, [x0, #:lo12:.LANCHOR22]
	ldr	x0, [x20, 8]
	bl	js_hash
	str	w0, [x6, 12]
	mov	w3, 1
	mov	x0, x20
	mov	w1, w3
	mov	w2, w3
	bl	FlashProgPages
	ldr	x4, [x29, 96]
	ldrh	w0, [x19, 2]
	add	w0, w0, 1
	and	w0, w0, 65535
	ldr	w1, [x4, #:lo12:.LANCHOR137]
	strh	w0, [x19, 2]
	cmn	w1, #1
	bne	.L780
	ldr	w1, [x20, 4]
	adrp	x0, .LC22
	str	x4, [x29, 104]
	add	x0, x0, :lo12:.LC22
	add	w21, w21, 1
	and	w21, w21, 65535
	bl	printf
	ldrh	w0, [x19, 2]
	ldr	x2, [x29, 104]
	cmp	w0, 2
	bhi	.L781
	ldrh	w0, [x28]
	sub	w0, w0, #1
	strh	w0, [x19, 2]
.L781:
	cmp	w21, 3
	bls	.L782
	add	x0, x2, :lo12:.LANCHOR137
	mov	w2, w21
	ldr	w1, [x0, 4]
	adrp	x0, .LC23
	add	x0, x0, :lo12:.LC23
	bl	printf
.L783:
	b	.L783
.L782:
	ldr	w0, [x19, 52]
	cbz	w0, .L775
.L798:
	b	.L798
.L780:
	ldr	x1, [x19, 40]
	cmp	w0, 1
	ldr	w2, [x20, 4]
	str	w2, [x1, x26]
	beq	.L786
	ldr	w0, [x4, #:lo12:.LANCHOR137]
	cmp	w0, 256
	beq	.L786
	ldr	w1, [x19, 56]
	cbz	w1, .L787
.L786:
	str	wzr, [x19, 56]
	b	.L775
.L787:
	cmn	w0, #1
	bne	.L788
	adrp	x1, .LANCHOR148
	adrp	x0, .LC1
	mov	w2, 745
	add	x1, x1, :lo12:.LANCHOR148
	add	x0, x0, :lo12:.LC1
	bl	printf
.L788:
	ldp	x19, x20, [sp, 16]
	mov	w0, 0
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
	.size	FtlMapWritePage, .-FtlMapWritePage
	.section	.text.load_l2p_region,"ax",@progbits
	.align	2
	.global	load_l2p_region
	.type	load_l2p_region, %function
load_l2p_region:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x23, x24, [sp, 48]
	adrp	x24, .LANCHOR31
	stp	x19, x20, [sp, 16]
	and	w20, w0, 65535
	stp	x21, x22, [sp, 32]
	and	x19, x1, 65535
	ldrh	w0, [x24, #:lo12:.LANCHOR31]
	stp	x25, x26, [sp, 64]
	str	x27, [sp, 80]
	cmp	w0, w20
	bcs	.L801
	adrp	x1, .LANCHOR149
	adrp	x0, .LC1
	mov	w2, 485
	add	x1, x1, :lo12:.LANCHOR149
	add	x0, x0, :lo12:.LC1
	bl	printf
.L801:
	adrp	x27, .LANCHOR123
	ubfiz	x0, x20, 2, 16
	adrp	x22, .LANCHOR54
	ldr	x1, [x27, #:lo12:.LANCHOR123]
	ldr	w23, [x1, x0]
	cbnz	w23, .L802
	ldr	x0, [x22, #:lo12:.LANCHOR54]
	lsl	x19, x19, 4
	adrp	x1, .LANCHOR22
	add	x0, x0, x19
	ldrh	w2, [x1, #:lo12:.LANCHOR22]
	mov	w1, 255
	ldr	x0, [x0, 8]
	bl	ftl_memset
	ldr	x0, [x22, #:lo12:.LANCHOR54]
	add	x1, x0, x19
	strh	w20, [x0, x19]
	str	wzr, [x1, 4]
.L803:
	mov	w0, 0
	ldr	x27, [sp, 80]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 96
	ret
.L802:
	ldr	x0, [x22, #:lo12:.LANCHOR54]
	lsl	x19, x19, 4
	adrp	x26, .LANCHOR137
	add	x21, x26, :lo12:.LANCHOR137
	add	x0, x0, x19
	mov	w2, 1
	mov	w1, w2
	str	w23, [x21, 4]
	ldr	x0, [x0, 8]
	str	x0, [x21, 8]
	adrp	x0, .LANCHOR113
	ldr	x0, [x0, #:lo12:.LANCHOR113]
	str	x0, [x21, 16]
	mov	x0, x21
	bl	FlashReadPages
	ldr	x25, [x21, 16]
	ldrh	w0, [x25, 8]
	cmp	w0, w20
	beq	.L804
	mov	w2, w23
	mov	w1, w20
	adrp	x0, .LC24
	add	x0, x0, :lo12:.LC24
	bl	printf
	ldr	x1, [x21, 16]
	mov	w3, 4
	adrp	x0, .LC13
	mov	w2, w3
	add	x0, x0, :lo12:.LC13
	bl	rknand_print_hex
	ldrh	w3, [x24, #:lo12:.LANCHOR31]
	adrp	x0, .LC25
	ldr	x1, [x27, #:lo12:.LANCHOR123]
	mov	w2, 4
	add	x0, x0, :lo12:.LC25
	bl	rknand_print_hex
.L805:
	ldrh	w0, [x25, 8]
	cmp	w0, w20
	beq	.L806
	adrp	x1, .LANCHOR149
	adrp	x0, .LC1
	mov	w2, 508
	add	x1, x1, :lo12:.LANCHOR149
	add	x0, x0, :lo12:.LC1
	bl	printf
.L806:
	ldr	x0, [x22, #:lo12:.LANCHOR54]
	add	x1, x0, x19
	str	wzr, [x1, 4]
	strh	w20, [x0, x19]
	b	.L803
.L804:
	ldr	w0, [x26, #:lo12:.LANCHOR137]
	cmp	w0, 256
	bne	.L805
	mov	w2, w23
	mov	w1, w20
	adrp	x0, .LC26
	add	x0, x0, :lo12:.LC26
	bl	printf
	ldr	x0, [x22, #:lo12:.LANCHOR54]
	mov	w1, w20
	add	x0, x0, x19
	ldr	x2, [x0, 8]
	adrp	x0, .LANCHOR128
	add	x0, x0, :lo12:.LANCHOR128
	bl	FtlMapWritePage
	b	.L805
	.size	load_l2p_region, .-load_l2p_region
	.section	.text.ftl_map_blk_gc,"ax",@progbits
	.align	2
	.global	ftl_map_blk_gc
	.type	ftl_map_blk_gc, %function
ftl_map_blk_gc:
	stp	x29, x30, [sp, -96]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	stp	x23, x24, [sp, 48]
	adrp	x24, .LANCHOR19
	stp	x25, x26, [sp, 64]
	stp	x21, x22, [sp, 32]
	stp	x27, x28, [sp, 80]
	ldr	x20, [x0, 16]
	ldr	x25, [x0, 40]
	bl	ftl_free_no_use_map_blk
	ldrh	w1, [x19, 10]
	ldrh	w2, [x19, 8]
	sub	w1, w1, #5
	cmp	w2, w1
	blt	.L809
	ubfiz	x0, x0, 1, 16
	ldrh	w22, [x20, x0]
	cbz	w22, .L809
	ldr	w1, [x19, 52]
	cbnz	w1, .L809
	mov	w1, 1
	str	w1, [x19, 52]
	strh	wzr, [x20, x0]
	ldrh	w0, [x19, 8]
	ldrh	w1, [x19, 2]
	sub	w0, w0, #1
	strh	w0, [x19, 8]
	ldrh	w0, [x24, #:lo12:.LANCHOR19]
	cmp	w1, w0
	bcc	.L810
	mov	x0, x19
	bl	ftl_map_blk_alloc_new_blk
.L810:
	adrp	x26, .LANCHOR137
	adrp	x23, .LANCHOR150
	add	x27, x26, :lo12:.LANCHOR137
	add	x23, x23, :lo12:.LANCHOR150
	mov	w20, 0
.L811:
	ldrh	w0, [x19, 6]
	cmp	w0, w20
	bhi	.L818
	mov	w1, 1
	mov	w0, w22
	bl	FtlFreeSysBlkQueueIn
	str	wzr, [x19, 52]
.L809:
	ldrh	w1, [x19, 2]
	ldrh	w0, [x24, #:lo12:.LANCHOR19]
	cmp	w1, w0
	bcc	.L819
	mov	x0, x19
	bl	ftl_map_blk_alloc_new_blk
.L819:
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 96
	ret
.L818:
	ubfiz	x0, x20, 2, 16
	add	x28, x25, x0
	ldr	w1, [x25, x0]
	cmp	w22, w1, lsr 10
	bne	.L812
	adrp	x2, .LANCHOR106
	add	x0, x26, :lo12:.LANCHOR137
	ldr	x2, [x2, #:lo12:.LANCHOR106]
	str	x2, [x0, 8]
	adrp	x2, .LANCHOR113
	str	w1, [x0, 4]
	ldr	x21, [x2, #:lo12:.LANCHOR113]
	mov	w2, 1
	str	x21, [x0, 16]
	mov	w1, w2
	bl	FlashReadPages
	ldrh	w0, [x21, 8]
	cmp	w0, w20
	beq	.L813
	adrp	x0, .LC1
	mov	w2, 611
	mov	x1, x23
	add	x0, x0, :lo12:.LC1
	bl	printf
.L813:
	ldr	w0, [x27]
	cmn	w0, #1
	bne	.L814
.L816:
	str	wzr, [x28]
.L815:
	b	.L815
.L814:
	ldrh	w0, [x21, 8]
	cmp	w0, w20
	bne	.L816
	ldrh	w1, [x21]
	ldrh	w0, [x19, 4]
	cmp	w1, w0
	bne	.L816
	ldr	x2, [x27, 8]
	mov	w1, w20
	mov	x0, x19
	bl	FtlMapWritePage
.L812:
	add	w20, w20, 1
	and	w20, w20, 65535
	b	.L811
	.size	ftl_map_blk_gc, .-ftl_map_blk_gc
	.section	.text.flush_l2p_region,"ax",@progbits
	.align	2
	.global	flush_l2p_region
	.type	flush_l2p_region, %function
flush_l2p_region:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	adrp	x20, .LANCHOR54
	ubfiz	x19, x0, 4, 16
	ldr	x0, [x20, #:lo12:.LANCHOR54]
	add	x1, x0, x19
	ldr	x2, [x1, 8]
	ldrh	w1, [x0, x19]
	adrp	x0, .LANCHOR128
	add	x0, x0, :lo12:.LANCHOR128
	bl	FtlMapWritePage
	ldr	x0, [x20, #:lo12:.LANCHOR54]
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
	adrp	x20, .LANCHOR32
	add	x20, x20, :lo12:.LANCHOR32
	str	x21, [sp, 32]
	mov	w19, 0
	adrp	x21, .LANCHOR54
.L828:
	ldrh	w0, [x20]
	cmp	w0, w19
	bhi	.L830
	mov	w0, 0
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
.L830:
	ldr	x1, [x21, #:lo12:.LANCHOR54]
	ubfiz	x0, x19, 4, 16
	add	x0, x1, x0
	ldr	w0, [x0, 4]
	tbz	w0, #31, .L829
	mov	w0, w19
	bl	flush_l2p_region
.L829:
	add	w19, w19, 1
	and	w19, w19, 65535
	b	.L828
	.size	l2p_flush, .-l2p_flush
	.section	.text.log2phys,"ax",@progbits
	.align	2
	.global	log2phys
	.type	log2phys, %function
log2phys:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x25, x26, [sp, 64]
	mov	w25, w0
	adrp	x0, .LANCHOR21
	stp	x23, x24, [sp, 48]
	stp	x19, x20, [sp, 16]
	mov	x20, x1
	ldrh	w24, [x0, #:lo12:.LANCHOR21]
	adrp	x0, .LANCHOR151
	stp	x21, x22, [sp, 32]
	mov	x19, x0
	ldr	w1, [x0, #:lo12:.LANCHOR151]
	mov	w21, w2
	cmp	w25, w1
	bcc	.L833
	adrp	x1, .LANCHOR152
	adrp	x0, .LC1
	mov	w2, 820
	add	x1, x1, :lo12:.LANCHOR152
	add	x0, x0, :lo12:.LC1
	bl	printf
.L833:
	ldr	w0, [x19, #:lo12:.LANCHOR151]
	cmp	w25, w0
	bcs	.L834
	adrp	x23, .LANCHOR54
	add	w24, w24, 7
	adrp	x0, .LANCHOR32
	ldr	x2, [x23, #:lo12:.LANCHOR54]
	lsr	w22, w25, w24
	and	w22, w22, 65535
	ldrh	w1, [x0, #:lo12:.LANCHOR32]
	mov	x0, 0
.L835:
	and	x19, x0, 65535
	cmp	w19, w1
	bcc	.L840
	bl	select_l2p_ram_region
	and	x19, x0, 65535
	ldr	x2, [x23, #:lo12:.LANCHOR54]
	ubfiz	x1, x19, 4, 16
	mov	w26, w0
	add	x3, x2, x1
	ldrh	w2, [x2, x1]
	mov	w1, 65535
	cmp	w2, w1
	beq	.L841
	ldr	w1, [x3, 4]
	tbz	w1, #31, .L841
	bl	flush_l2p_region
.L841:
	mov	w1, w26
	mov	w0, w22
	bl	load_l2p_region
	b	.L837
.L834:
	mov	w0, -1
	cbnz	w21, .L832
	str	w0, [x20]
.L832:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
.L840:
	add	x0, x0, 1
	add	x3, x2, x0, lsl 4
	ldrh	w3, [x3, -16]
	cmp	w3, w22
	bne	.L835
.L837:
	mov	x0, 1
	ldr	x1, [x23, #:lo12:.LANCHOR54]
	lsl	x0, x0, x24
	sub	w0, w0, #1
	and	w0, w0, w25
	and	x0, x0, 65535
	add	x1, x1, x19, lsl 4
	cbnz	w21, .L838
	ldr	x1, [x1, 8]
	ldr	w0, [x1, x0, lsl 2]
	str	w0, [x20]
.L839:
	ldr	x0, [x23, #:lo12:.LANCHOR54]
	add	x19, x0, x19, lsl 4
	ldr	w0, [x19, 4]
	cmn	w0, #1
	beq	.L843
	add	w0, w0, 1
	str	w0, [x19, 4]
.L843:
	mov	w0, 0
	b	.L832
.L838:
	ldr	x2, [x1, 8]
	ldr	w3, [x20]
	str	w3, [x2, x0, lsl 2]
	ldr	w0, [x1, 4]
	orr	w0, w0, -2147483648
	str	w0, [x1, 4]
	adrp	x0, .LANCHOR55
	strh	w22, [x0, #:lo12:.LANCHOR55]
	b	.L839
	.size	log2phys, .-log2phys
	.section	.text.FtlReUsePrevPpa,"ax",@progbits
	.align	2
	.global	FtlReUsePrevPpa
	.type	FtlReUsePrevPpa, %function
FtlReUsePrevPpa:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x21, x22, [sp, 32]
	adrp	x22, .LANCHOR41
	stp	x19, x20, [sp, 16]
	mov	w21, w0
	str	w1, [x29, 76]
	lsr	w0, w1, 10
	str	x23, [sp, 48]
	bl	P2V_block_in_plane
	ldr	x2, [x22, #:lo12:.LANCHOR41]
	and	w3, w0, 65535
	ubfiz	x20, x3, 1, 16
	ldrh	w1, [x2, x20]
	cbnz	w1, .L847
	adrp	x0, .LANCHOR45
	ldr	x19, [x0, #:lo12:.LANCHOR45]
	cbz	x19, .L848
	adrp	x2, .LANCHOR39
	mov	x5, -6148914691236517206
	movk	x5, 0xaaab, lsl 0
	adrp	x23, .LANCHOR47
	ldr	x2, [x2, #:lo12:.LANCHOR39]
	mov	w6, 65535
	ldrh	w4, [x23, #:lo12:.LANCHOR47]
	sub	x19, x19, x2
	asr	x19, x19, 1
	mul	x19, x19, x5
	mov	w5, 6
	and	w19, w19, 65535
.L849:
	cmp	w1, w4
	beq	.L848
	cmp	w19, w3
	bne	.L850
	mov	w1, w19
	add	x0, x0, :lo12:.LANCHOR45
	bl	List_remove_node
	ldrh	w0, [x23, #:lo12:.LANCHOR47]
	cbnz	w0, .L851
	adrp	x1, .LANCHOR153
	adrp	x0, .LC1
	mov	w2, 1742
	add	x1, x1, :lo12:.LANCHOR153
	add	x0, x0, :lo12:.LC1
	bl	printf
.L851:
	ldrh	w0, [x23, #:lo12:.LANCHOR47]
	sub	w0, w0, #1
	strh	w0, [x23, #:lo12:.LANCHOR47]
	mov	w0, w19
	bl	INSERT_DATA_LIST
	ldr	x1, [x22, #:lo12:.LANCHOR41]
	ldrh	w0, [x1, x20]
	add	w0, w0, 1
	strh	w0, [x1, x20]
.L848:
	add	x1, x29, 76
	mov	w2, 1
	mov	w0, w21
	bl	log2phys
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
.L850:
	umull	x19, w19, w5
	ldrh	w19, [x2, x19]
	cmp	w19, w6
	beq	.L848
	add	w1, w1, 1
	and	w1, w1, 65535
	b	.L849
.L847:
	add	w1, w1, 1
	strh	w1, [x2, x20]
	b	.L848
	.size	FtlReUsePrevPpa, .-FtlReUsePrevPpa
	.section	.text.FtlRecoverySuperblock,"ax",@progbits
	.align	2
	.global	FtlRecoverySuperblock
	.type	FtlRecoverySuperblock, %function
FtlRecoverySuperblock:
	stp	x29, x30, [sp, -192]!
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
	beq	.L984
	ldrb	w0, [x19, 6]
	str	w0, [x29, 164]
	adrp	x0, .LANCHOR18
	ldrh	w26, [x19, 2]
	str	x0, [x29, 128]
	ldrh	w2, [x0, #:lo12:.LANCHOR18]
	cmp	w2, w26
	bne	.L860
	strh	wzr, [x19, 4]
.L991:
	strb	wzr, [x19, 6]
.L984:
	ldp	x19, x20, [sp, 16]
	mov	w0, 0
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 192
	ret
.L860:
	ldrh	w0, [x19, 16]
	mov	w20, 0
.L861:
	cmp	w0, w1
	beq	.L862
	mov	w1, 1
	bl	FtlGetLastWrittenPage
	mov	w23, w0
	cmn	w0, #1
	beq	.L863
	adrp	x1, .LANCHOR63
	adrp	x2, .LANCHOR2
	adrp	x20, .LANCHOR102
	add	x4, x19, 16
	ldr	x5, [x1, #:lo12:.LANCHOR63]
	adrp	x1, .LANCHOR22
	ldr	x0, [x20, #:lo12:.LANCHOR102]
	mov	w22, 0
	ldrh	w6, [x1, #:lo12:.LANCHOR22]
	adrp	x1, .LANCHOR64
	mov	w10, 65535
	str	x2, [x29, 152]
	ldr	x7, [x1, #:lo12:.LANCHOR64]
	adrp	x1, .LANCHOR23
	ldrh	w8, [x1, #:lo12:.LANCHOR23]
	add	x1, x19, 16
	str	x1, [x29, 168]
	ldrh	w1, [x2, #:lo12:.LANCHOR2]
	add	x1, x1, 8
	add	x1, x19, x1, lsl 1
.L864:
	cmp	x4, x1
	bne	.L868
	mov	w2, 0
	mov	w1, w22
	bl	FlashReadPages
	adrp	x0, .LANCHOR82
	ldr	x4, [x20, #:lo12:.LANCHOR102]
	and	w10, w23, 65535
	add	x7, x0, :lo12:.LANCHOR82
	ldr	w21, [x0, #:lo12:.LANCHOR82]
	mov	x11, x4
	mov	w6, 65535
	mov	w3, 0
	sub	w21, w21, #1
	str	x0, [x29, 144]
.L869:
	cmp	w22, w3
	bne	.L874
	add	w22, w23, 1
	ldr	w0, [x4, 4]
	and	w22, w22, 65535
.L986:
	lsr	w0, w0, 10
	bl	P2V_plane
	and	w27, w0, 65535
	ldr	x0, [x29, 128]
	ldrh	w0, [x0, #:lo12:.LANCHOR18]
	cmp	w0, w22
	bne	.L876
	strh	w22, [x19, 2]
	strb	wzr, [x19, 6]
	strh	wzr, [x19, 4]
.L876:
	ldr	w0, [x29, 164]
	cmp	w22, w26
	cset	w1, eq
	cmp	w27, w0
	cset	w0, eq
	tst	w1, w0
	beq	.L877
.L992:
	mov	w2, w27
	mov	w1, w22
	mov	x0, x19
	bl	ftl_sb_update_avl_pages
	b	.L984
.L862:
	add	w20, w20, 1
	and	w20, w20, 65535
	add	x0, x19, x20, sxtw 1
	ldrh	w0, [x0, 16]
	b	.L861
.L863:
	cbz	w26, .L865
	adrp	x1, .LANCHOR154
	adrp	x0, .LC1
	mov	w2, 1809
	add	x1, x1, :lo12:.LANCHOR154
	add	x0, x0, :lo12:.LC1
	bl	printf
.L865:
	ldr	w0, [x29, 164]
	cmp	w0, 0
	ccmp	w20, w0, 4, ne
	beq	.L866
	adrp	x1, .LANCHOR154
	adrp	x0, .LC1
	mov	w2, 1810
	add	x1, x1, :lo12:.LANCHOR154
	add	x0, x0, :lo12:.LC1
	bl	printf
.L866:
	strh	wzr, [x19, 2]
	b	.L991
.L868:
	ldrh	w3, [x4]
	cmp	w3, w10
	beq	.L867
	ubfiz	x2, x22, 5, 16
	orr	w3, w23, w3, lsl 10
	add	x2, x0, x2
	str	w3, [x2, 4]
	mul	w3, w22, w6
	asr	w3, w3, 2
	add	x3, x5, x3, sxtw 2
	str	x3, [x2, 8]
	mul	w3, w22, w8
	add	w22, w22, 1
	and	w22, w22, 65535
	asr	w3, w3, 2
	add	x3, x7, x3, sxtw 2
	str	x3, [x2, 16]
.L867:
	add	x4, x4, 2
	b	.L864
.L874:
	ldr	w0, [x11]
	cbnz	w0, .L870
	ldr	x8, [x11, 16]
	ldr	w5, [x8, 4]
	cmn	w5, #1
	beq	.L871
	ldr	w1, [x7]
	mov	w0, w5
	bl	ftl_cmp_data_ver
	cbz	w0, .L871
	add	w5, w5, 1
	str	w5, [x7]
.L871:
	ldr	w0, [x8]
	cmn	w0, #1
	bne	.L873
	ubfiz	x3, x3, 5, 16
	and	w22, w23, 65535
	add	x3, x4, x3
	ldr	w0, [x3, 4]
	b	.L986
.L870:
	mov	w6, w10
.L873:
	add	w3, w3, 1
	add	x11, x11, 32
	and	w3, w3, 65535
	b	.L869
.L877:
	mov	w0, 65535
	cmp	w6, w0
	bne	.L878
	ldrb	w0, [x19, 8]
	cbnz	w0, .L879
.L878:
	adrp	x25, .LANCHOR133
	and	w28, w23, 65535
	ldr	w0, [x25, #:lo12:.LANCHOR133]
	cmn	w0, #1
	bne	.L880
	str	w21, [x25, #:lo12:.LANCHOR133]
.L880:
	add	w0, w26, 7
	cmp	w0, w23, uxth
	bge	.L930
	sub	w24, w28, #7
	and	w24, w24, 65535
.L881:
	ldr	x0, [x29, 152]
	mov	w3, 65535
	mov	w5, 1
	add	x4, x0, :lo12:.LANCHOR2
.L882:
	cmp	w24, w28
	bhi	.L892
	ldrh	w1, [x4]
	mov	w23, 0
	ldr	x0, [x20, #:lo12:.LANCHOR102]
	add	x1, x1, 8
	ldr	x2, [x29, 168]
	add	x1, x19, x1, lsl 1
	b	.L893
.L930:
	mov	w24, w26
	b	.L881
.L884:
	ldrh	w6, [x2]
	cmp	w6, w3
	beq	.L883
	ubfiz	x7, x23, 5, 16
	add	w23, w23, 1
	add	x7, x0, x7
	and	w23, w23, 65535
	orr	w6, w24, w6, lsl 10
	str	w6, [x7, 4]
.L883:
	add	x2, x2, 2
.L893:
	cmp	x1, x2
	bne	.L884
	mov	w1, w23
	mov	w2, 0
	str	w5, [x29, 112]
	ubfiz	x23, x23, 5, 16
	str	w3, [x29, 120]
	add	x23, x23, 16
	str	x4, [x29, 136]
	bl	FlashReadPages
	ldr	x2, [x20, #:lo12:.LANCHOR102]
	ldr	w1, [x25, #:lo12:.LANCHOR133]
	ldr	w5, [x29, 112]
	add	x0, x2, 16
	ldr	w3, [x29, 120]
	add	x23, x2, x23
	ldr	x4, [x29, 136]
	mov	w2, 0
.L885:
	cmp	x23, x0
	bne	.L890
	cbz	w2, .L891
	str	w1, [x25, #:lo12:.LANCHOR133]
.L891:
	add	w24, w24, 1
	and	w24, w24, 65535
	b	.L882
.L890:
	ldr	w6, [x0, -16]
	cbz	w6, .L886
	cbz	w2, .L879
	str	w1, [x25, #:lo12:.LANCHOR133]
.L879:
	adrp	x0, .LANCHOR155
	mov	w23, w26
	mov	w1, 1
	adrp	x28, .LANCHOR133
	strh	w1, [x0, #:lo12:.LANCHOR155]
	add	x0, x28, :lo12:.LANCHOR133
	str	x0, [x29, 104]
.L894:
	ldr	x1, [x29, 152]
	mov	w24, 0
	ldr	x0, [x20, #:lo12:.LANCHOR102]
	mov	w5, 65535
	ldr	x2, [x29, 168]
	ldrh	w1, [x1, #:lo12:.LANCHOR2]
	add	x1, x1, 8
	add	x1, x19, x1, lsl 1
.L895:
	cmp	x1, x2
	bne	.L897
	mov	w2, 0
	mov	w1, w24
	bl	FlashReadPages
	mov	x25, 0
	ubfiz	x0, x24, 5, 16
	str	x0, [x29, 112]
	adrp	x0, .LANCHOR156
	add	x0, x0, :lo12:.LANCHOR156
	str	x0, [x29, 120]
.L898:
	ldr	x0, [x29, 112]
	cmp	x25, x0
	bne	.L924
	ldr	x0, [x29, 128]
	add	w23, w23, 1
	and	w23, w23, 65535
	ldrh	w0, [x0, #:lo12:.LANCHOR18]
	cmp	w0, w23
	bne	.L894
	ldr	x0, [x29, 152]
	mov	w2, 65535
	strh	w23, [x19, 2]
	strh	wzr, [x19, 4]
	ldrh	w1, [x0, #:lo12:.LANCHOR2]
	mov	w0, 0
.L925:
	cmp	w0, w1
	beq	.L984
	ldr	x4, [x29, 168]
	ldrh	w3, [x4], 2
	str	x4, [x29, 168]
	cmp	w3, w2
	beq	.L926
	strb	w0, [x19, 6]
	b	.L984
.L886:
	ldr	x6, [x0]
	ldrh	w7, [x6]
	cmp	w7, w3
	beq	.L889
	ldr	w6, [x6, 4]
	cmn	w6, #1
	csel	w1, w1, w6, eq
	csel	w2, w2, w5, eq
.L889:
	add	x0, x0, 32
	b	.L885
.L892:
	mov	w0, -1
	str	w0, [x25, #:lo12:.LANCHOR133]
	b	.L879
.L897:
	ldrh	w3, [x2]
	cmp	w3, w5
	beq	.L896
	ubfiz	x4, x24, 5, 16
	add	w24, w24, 1
	add	x4, x0, x4
	and	w24, w24, 65535
	orr	w3, w23, w3, lsl 10
	str	w3, [x4, 4]
.L896:
	add	x2, x2, 2
	b	.L895
.L924:
	ldr	x4, [x20, #:lo12:.LANCHOR102]
	add	x4, x4, x25
	ldr	w5, [x4, 4]
	str	w5, [x29, 188]
	lsr	w0, w5, 10
	bl	P2V_plane
	and	w0, w0, 65535
	cmp	w23, w26
	bcc	.L899
	ldr	w1, [x29, 164]
	ccmp	w1, w0, 0, eq
	bhi	.L899
	cmp	w23, w22
	ccmp	w27, w0, 0, eq
	beq	.L900
	ldr	w0, [x4]
	cmn	w0, #1
	beq	.L901
	ldr	x3, [x4, 16]
	mov	w0, 61589
	ldrh	w1, [x3]
	cmp	w1, w0
	beq	.L902
	ldrh	w0, [x19]
.L988:
	bl	decrement_vpc_count
	b	.L899
.L902:
	ldr	w21, [x3, 4]
	cmn	w21, #1
	beq	.L903
	ldr	x0, [x29, 144]
	ldr	w1, [x0, #:lo12:.LANCHOR82]
	mov	w0, w21
	bl	ftl_cmp_data_ver
	cbz	w0, .L903
	ldr	x1, [x29, 144]
	add	w0, w21, 1
	str	w0, [x1, #:lo12:.LANCHOR82]
.L903:
	ldp	w24, w0, [x3, 8]
	add	x1, x29, 184
	str	w0, [x29, 180]
	mov	w2, 0
	mov	w0, w24
	bl	log2phys
	ldr	w1, [x28, #:lo12:.LANCHOR133]
	ldr	w3, [x29, 180]
	cmn	w1, #1
	beq	.L904
	mov	w0, w21
	bl	ftl_cmp_data_ver
	cbz	w0, .L904
	cmn	w3, #1
	beq	.L905
	ldr	x0, [x20, #:lo12:.LANCHOR102]
	mov	w2, 0
	mov	w1, 1
	add	x0, x0, x25
	ldr	x4, [x0, 16]
	str	w3, [x0, 4]
	str	x4, [x29, 136]
	bl	FlashReadPages
	ldr	x0, [x20, #:lo12:.LANCHOR102]
	ldr	x4, [x29, 136]
	add	x3, x0, x25
	ldr	w0, [x0, x25]
	cmn	w0, #1
	bne	.L906
.L907:
	mov	w0, -1
	str	w0, [x29, 180]
.L914:
	ldr	w3, [x29, 180]
	cmn	w3, #1
	beq	.L899
.L929:
	lsr	w0, w3, 10
	bl	P2V_block_in_plane
	and	w24, w0, 65535
	adrp	x0, .LANCHOR4
	mov	w3, w24
	ldrh	w0, [x0, #:lo12:.LANCHOR4]
	cmp	w0, w24
	bhi	.L920
	mov	w2, 2066
	adrp	x1, .LANCHOR154
	adrp	x0, .LC1
	add	x1, x1, :lo12:.LANCHOR154
	add	x0, x0, :lo12:.LC1
	str	w24, [x29, 136]
	bl	printf
	ldr	w3, [x29, 136]
.L920:
	adrp	x1, .LANCHOR41
	ubfiz	x0, x24, 1, 16
	ldr	x1, [x1, #:lo12:.LANCHOR41]
	ldrh	w0, [x1, x0]
	cbz	w0, .L921
	mov	w0, w3
	b	.L988
.L905:
	ldp	w1, w0, [x29, 184]
	cmp	w1, w0
	bne	.L899
	mov	w2, 1
	add	x1, x29, 180
	mov	w0, w24
	bl	log2phys
.L899:
	add	x25, x25, 32
	b	.L898
.L906:
	ldr	w0, [x4, 8]
	cmp	w24, w0
	bne	.L907
	ldr	w0, [x4, 4]
	str	w0, [x29, 136]
	str	x4, [x29, 96]
	uxtw	x1, w0
	ldr	w0, [x28, #:lo12:.LANCHOR133]
	bl	ftl_cmp_data_ver
	cbz	w0, .L907
	ldp	w0, w1, [x29, 184]
	ldr	x4, [x29, 96]
	cmp	w0, w1
	ldr	w1, [x29, 180]
	bne	.L909
.L987:
	mov	w0, w24
	bl	FtlReUsePrevPpa
	b	.L907
.L909:
	cmp	w0, w1
	beq	.L907
	cmn	w0, #1
	beq	.L910
	ldr	x4, [x3, 16]
	mov	w2, 0
	str	w0, [x3, 4]
	mov	w1, 1
	str	x4, [x29, 96]
	mov	x0, x3
	bl	FlashReadPages
	ldr	x4, [x29, 96]
.L911:
	ldr	x0, [x20, #:lo12:.LANCHOR102]
	ldr	w0, [x0, x25]
	cmn	w0, #1
	beq	.L912
	ldr	x0, [x29, 104]
	ldr	w3, [x4, 4]
	mov	w1, w3
	ldr	w0, [x0]
	bl	ftl_cmp_data_ver
	cbz	w0, .L912
	ldr	w0, [x29, 136]
	mov	w1, w3
	bl	ftl_cmp_data_ver
	cbz	w0, .L907
.L912:
	ldr	w1, [x29, 180]
	b	.L987
.L910:
	str	w0, [x3]
	b	.L911
.L904:
	ldp	w1, w0, [x29, 184]
	cmp	w1, w0
	beq	.L914
	cmn	w3, #1
	beq	.L916
	adrp	x0, .LANCHOR7
	ldr	w0, [x0, #:lo12:.LANCHOR7]
	cmp	w0, w3, lsr 10
	bhi	.L916
	adrp	x0, .LC27
	mov	w1, w3
	add	x0, x0, :lo12:.LC27
.L990:
	bl	printf
	b	.L899
.L916:
	mov	w2, 1
	add	x1, x29, 188
	mov	w0, w24
	bl	log2phys
	ldr	w3, [x29, 184]
	cmn	w3, #1
	beq	.L914
	ldr	w0, [x29, 180]
	cmp	w3, w0
	beq	.L929
	lsr	w0, w3, 10
	bl	P2V_block_in_plane
	adrp	x1, .LANCHOR50
	and	w0, w0, 65535
	ldrh	w1, [x1, #:lo12:.LANCHOR50]
	cmp	w1, w0
	beq	.L919
	adrp	x1, .LANCHOR51
	ldrh	w1, [x1, #:lo12:.LANCHOR51]
	cmp	w1, w0
	beq	.L919
	adrp	x1, .LANCHOR52
	ldrh	w1, [x1, #:lo12:.LANCHOR52]
	cmp	w1, w0
	bne	.L914
.L919:
	ldr	x0, [x20, #:lo12:.LANCHOR102]
	mov	w2, 0
	mov	w1, 1
	ldr	x4, [x0, 16]
	str	w3, [x0, 4]
	str	x4, [x29, 136]
	bl	FlashReadPages
	ldr	x0, [x20, #:lo12:.LANCHOR102]
	ldr	w0, [x0]
	cmn	w0, #1
	beq	.L914
	ldr	x4, [x29, 136]
	mov	w0, w21
	ldr	w1, [x4, 4]
	bl	ftl_cmp_data_ver
	cbnz	w0, .L914
	mov	w2, 1
	add	x1, x29, 184
	mov	w0, w24
	bl	log2phys
	b	.L914
.L921:
	adrp	x0, .LC28
	mov	w1, w24
	add	x0, x0, :lo12:.LC28
	b	.L990
.L901:
	ldr	x0, [x29, 120]
	ldr	w0, [x0]
	cmp	w0, 31
	bhi	.L922
	adrp	x1, .LANCHOR157
	add	x1, x1, :lo12:.LANCHOR157
	str	w5, [x1, w0, uxtw 2]
	add	w0, w0, 1
	ldr	x1, [x29, 120]
	str	w0, [x1]
.L922:
	ldrh	w0, [x19]
	bl	decrement_vpc_count
	ldr	w0, [x28, #:lo12:.LANCHOR133]
	cmn	w0, #1
	bne	.L923
.L989:
	str	w21, [x28, #:lo12:.LANCHOR133]
	b	.L899
.L923:
	cmp	w21, w0
	bcs	.L899
	b	.L989
.L926:
	add	w0, w0, 1
	and	w0, w0, 65535
	b	.L925
.L900:
	strb	w27, [x19, 6]
	strh	w22, [x19, 2]
	b	.L992
	.size	FtlRecoverySuperblock, .-FtlRecoverySuperblock
	.section	.text.ftl_check_vpc,"ax",@progbits
	.align	2
	.global	ftl_check_vpc
	.type	ftl_check_vpc, %function
ftl_check_vpc:
	stp	x29, x30, [sp, -112]!
	adrp	x0, .LC29
	add	x0, x0, :lo12:.LC29
	add	x29, sp, 0
	stp	x23, x24, [sp, 48]
	adrp	x23, .LANCHOR151
	add	x23, x23, :lo12:.LANCHOR151
	stp	x21, x22, [sp, 32]
	mov	w22, 0
	stp	x19, x20, [sp, 16]
	stp	x25, x26, [sp, 64]
	adrp	x21, .LANCHOR158
	stp	x27, x28, [sp, 80]
	add	x1, x21, :lo12:.LANCHOR158
	adrp	x20, check_vpc_table
	bl	printf
	add	x19, x20, :lo12:check_vpc_table
	mov	w2, 8192
	mov	w1, 0
	mov	x0, x19
	bl	ftl_memset
.L994:
	ldr	w0, [x23]
	cmp	w22, w0
	bcc	.L996
	adrp	x22, .LANCHOR4
	adrp	x24, .LC30
	add	x22, x22, :lo12:.LANCHOR4
	add	x26, x20, :lo12:check_vpc_table
	add	x24, x24, :lo12:.LC30
	mov	w23, 0
	mov	w19, 0
	adrp	x25, .LANCHOR41
.L997:
	ldrh	w0, [x22]
	cmp	w0, w19
	bhi	.L999
	adrp	x0, .LANCHOR45
	ldr	x19, [x0, #:lo12:.LANCHOR45]
	cbz	x19, .L1000
	adrp	x0, .LANCHOR47
	adrp	x25, .LC31
	add	x20, x20, :lo12:check_vpc_table
	add	x25, x25, :lo12:.LC31
	ldrh	w26, [x0, #:lo12:.LANCHOR47]
	adrp	x0, .LANCHOR39
	mov	x24, x0
	mov	w22, 0
	ldr	x1, [x0, #:lo12:.LANCHOR39]
	adrp	x27, .LANCHOR41
	mov	w28, 6
	sub	x19, x19, x1
	mov	x1, -6148914691236517206
	asr	x19, x19, 1
	movk	x1, 0xaaab, lsl 0
	mul	x19, x19, x1
	and	w19, w19, 65535
.L1001:
	cmp	w22, w26
	bne	.L1003
.L1000:
	cbz	w23, .L993
	adrp	x0, .LC1
	mov	w2, 2394
	add	x1, x21, :lo12:.LANCHOR158
	add	x0, x0, :lo12:.LC1
	bl	printf
.L993:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
.L996:
	mov	w2, 0
	add	x1, x29, 108
	mov	w0, w22
	bl	log2phys
	ldr	w0, [x29, 108]
	cmn	w0, #1
	beq	.L995
	lsr	w0, w0, 10
	bl	P2V_block_in_plane
	and	x0, x0, 65535
	ldrh	w1, [x19, x0, lsl 1]
	add	w1, w1, 1
	strh	w1, [x19, x0, lsl 1]
.L995:
	add	w22, w22, 1
	b	.L994
.L999:
	ldr	x0, [x25, #:lo12:.LANCHOR41]
	ubfiz	x28, x19, 1, 16
	sxtw	x27, w19
	ldrh	w2, [x0, x28]
	ldrh	w3, [x26, x27, lsl 1]
	cmp	w2, w3
	beq	.L998
	mov	w1, w19
	mov	x0, x24
	bl	printf
	ldr	x0, [x25, #:lo12:.LANCHOR41]
	mov	w1, 65535
	ldrh	w0, [x0, x28]
	cmp	w0, w1
	beq	.L998
	ldrh	w1, [x26, x27, lsl 1]
	cmp	w1, w0
	csinc	w23, w23, wzr, ls
.L998:
	add	w19, w19, 1
	and	w19, w19, 65535
	b	.L997
.L1003:
	ldr	x1, [x27, #:lo12:.LANCHOR41]
	ubfiz	x0, x19, 1, 16
	ldrh	w2, [x1, x0]
	cbz	w2, .L1002
	ldrh	w3, [x20, w19, sxtw 1]
	mov	w23, 1
	mov	w1, w19
	mov	x0, x25
	bl	printf
.L1002:
	ldr	x0, [x24, #:lo12:.LANCHOR39]
	umull	x19, w19, w28
	ldrh	w19, [x0, x19]
	mov	w0, 65535
	cmp	w19, w0
	beq	.L1000
	add	w22, w22, 1
	and	w22, w22, 65535
	b	.L1001
	.size	ftl_check_vpc, .-ftl_check_vpc
	.section	.text.ftl_scan_all_data,"ax",@progbits
	.align	2
	.global	ftl_scan_all_data
	.type	ftl_scan_all_data, %function
ftl_scan_all_data:
	sub	sp, sp, #96
	adrp	x0, .LC32
	mov	w1, 0
	add	x0, x0, :lo12:.LC32
	stp	x29, x30, [sp, 16]
	add	x29, sp, 16
	stp	x19, x20, [sp, 32]
	adrp	x20, .LANCHOR137
	stp	x21, x22, [sp, 48]
	mov	w19, 0
	adrp	x21, .LANCHOR151
	add	x22, x20, :lo12:.LANCHOR137
	add	x21, x21, :lo12:.LANCHOR151
	str	x23, [sp, 64]
	bl	printf
.L1019:
	ldr	w0, [x21]
	cmp	w19, w0
	bcc	.L1025
	ldp	x19, x20, [sp, 32]
	ldp	x21, x22, [sp, 48]
	ldp	x29, x30, [sp, 16]
	ldr	x23, [sp, 64]
	add	sp, sp, 96
	ret
.L1025:
	mov	w2, 0
	add	x1, x29, 76
	mov	w0, w19
	bl	log2phys
	tst	x19, 2047
	bne	.L1020
	ldr	w2, [x29, 76]
	adrp	x0, .LC33
	mov	w1, w19
	add	x0, x0, :lo12:.LC33
	bl	printf
.L1020:
	ldr	w1, [x29, 76]
	cmn	w1, #1
	beq	.L1022
	add	x0, x20, :lo12:.LANCHOR137
	str	wzr, [x20, #:lo12:.LANCHOR137]
	mov	w2, 0
	str	w1, [x0, 4]
	adrp	x1, .LANCHOR105
	str	w19, [x0, 24]
	ldr	x1, [x1, #:lo12:.LANCHOR105]
	str	x1, [x0, 8]
	adrp	x1, .LANCHOR113
	ldr	x23, [x1, #:lo12:.LANCHOR113]
	mov	w1, 1
	str	x23, [x0, 16]
	bl	FlashReadPages
	ldr	w0, [x20, #:lo12:.LANCHOR137]
	cmp	w0, 256
	ccmn	w0, #1, 4, ne
	beq	.L1023
	ldr	w0, [x23, 8]
	cmp	w19, w0
	beq	.L1022
.L1023:
	ldp	x1, x0, [x22, 8]
	ldr	w2, [x1, 4]
	str	w2, [sp]
	ldr	w2, [x22, 4]
	ldp	w3, w4, [x0]
	ldp	w5, w6, [x0, 8]
	adrp	x0, .LC34
	ldr	w7, [x1]
	add	x0, x0, :lo12:.LC34
	mov	w1, w19
	bl	printf
.L1022:
	add	w19, w19, 1
	b	.L1019
	.size	ftl_scan_all_data, .-ftl_scan_all_data
	.section	.text.FtlGcScanTempBlk,"ax",@progbits
	.align	2
	.global	FtlGcScanTempBlk
	.type	FtlGcScanTempBlk, %function
FtlGcScanTempBlk:
	stp	x29, x30, [sp, -144]!
	add	x29, sp, 0
	stp	x25, x26, [sp, 64]
	adrp	x25, .LANCHOR159
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	ldrh	w20, [x25, #:lo12:.LANCHOR159]
	mov	w0, 65535
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	cmp	w20, w0
	str	x27, [sp, 80]
	beq	.L1048
	cbnz	w20, .L1028
.L1029:
	bl	FtlGcPageVarInit
	b	.L1030
.L1048:
	mov	w20, 0
.L1028:
	adrp	x0, .LANCHOR18
	ldrh	w0, [x0, #:lo12:.LANCHOR18]
	cmp	w0, w1
	beq	.L1029
.L1030:
	adrp	x26, .LANCHOR151
	add	x26, x26, :lo12:.LANCHOR151
.L1045:
	ldrh	w1, [x19]
	mov	w0, 65535
	strb	wzr, [x19, 8]
	cmp	w1, w0
	beq	.L1031
.L1047:
	adrp	x1, .LANCHOR63
	adrp	x24, .LANCHOR102
	add	x4, x19, 16
	mov	w21, 0
	ldr	x5, [x1, #:lo12:.LANCHOR63]
	adrp	x1, .LANCHOR22
	ldr	x0, [x24, #:lo12:.LANCHOR102]
	mov	w10, 65535
	ldrh	w6, [x1, #:lo12:.LANCHOR22]
	adrp	x1, .LANCHOR64
	ldr	x7, [x1, #:lo12:.LANCHOR64]
	adrp	x1, .LANCHOR23
	ldrh	w8, [x1, #:lo12:.LANCHOR23]
	adrp	x1, .LANCHOR2
	ldrh	w1, [x1, #:lo12:.LANCHOR2]
	add	x1, x1, 8
	add	x1, x19, x1, lsl 1
.L1032:
	cmp	x1, x4
	bne	.L1034
	mov	w1, w21
	ubfiz	x21, x21, 5, 16
	mov	x22, 0
	mov	w2, 0
	bl	FlashReadPages
.L1035:
	cmp	x21, x22
	bne	.L1046
	adrp	x0, .LANCHOR18
	add	w20, w20, 1
	and	w20, w20, 65535
	ldrh	w0, [x0, #:lo12:.LANCHOR18]
	cmp	w0, w20
	bhi	.L1047
.L1031:
	strh	w20, [x19, 2]
	mov	w0, -1
	strb	wzr, [x19, 6]
	mov	w1, w20
	strh	w0, [x25, #:lo12:.LANCHOR159]
	mov	w2, 0
	mov	x0, x19
	bl	ftl_sb_update_avl_pages
	mov	w0, -1
	ldr	x27, [sp, 80]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 144
	ret
.L1034:
	ldrh	w3, [x4]
	cmp	w3, w10
	beq	.L1033
	ubfiz	x2, x21, 5, 16
	orr	w3, w20, w3, lsl 10
	add	x2, x0, x2
	str	w3, [x2, 4]
	mul	w3, w21, w6
	asr	w3, w3, 2
	add	x3, x5, x3, sxtw 2
	str	x3, [x2, 8]
	mul	w3, w21, w8
	add	w21, w21, 1
	and	w21, w21, 65535
	asr	w3, w3, 2
	add	x3, x7, x3, sxtw 2
	str	x3, [x2, 16]
.L1033:
	add	x4, x4, 2
	b	.L1032
.L1046:
	ldr	x0, [x24, #:lo12:.LANCHOR102]
	add	x1, x0, x22
	ldr	w0, [x0, x22]
	ldr	w27, [x1, 4]
	ldr	x23, [x1, 16]
	cbnz	w0, .L1036
	ldrh	w1, [x23]
	mov	w0, 65535
	cmp	w1, w0
	beq	.L1058
	ldr	w0, [x23, 8]
	ldr	w1, [x26]
	cmp	w0, w1
	bls	.L1038
.L1058:
	adrp	x0, .LANCHOR41
	ldrh	w1, [x19]
	mov	w20, 0
	ldr	x0, [x0, #:lo12:.LANCHOR41]
	strh	wzr, [x0, x1, lsl 1]
	ldrh	w0, [x19]
	bl	INSERT_FREE_LIST
	mov	w0, -1
	adrp	x1, .LANCHOR144
	strh	w0, [x19]
	strh	w0, [x1, #:lo12:.LANCHOR144]
	bl	FtlGcPageVarInit
	b	.L1045
.L1038:
	add	x1, x29, 108
	mov	w2, 0
	bl	log2phys
	ldr	w0, [x23, 12]
	ldr	w1, [x29, 108]
	cmp	w0, w1
	beq	.L1040
.L1042:
	ldr	w2, [x23, 8]
.L1059:
	ldr	w0, [x23, 12]
	mov	w1, w27
	add	x22, x22, 32
	bl	FtlGcUpdatePage
	b	.L1035
.L1040:
	cmn	w0, #1
	beq	.L1042
	str	w0, [x29, 116]
	adrp	x0, .LANCHOR109
	mov	w2, 0
	mov	w1, 1
	ldr	x0, [x0, #:lo12:.LANCHOR109]
	str	x0, [x29, 120]
	adrp	x0, .LANCHOR114
	ldr	x0, [x0, #:lo12:.LANCHOR114]
	str	x0, [x29, 128]
	add	x0, x29, 112
	bl	FlashReadPages
	adrp	x0, .LANCHOR11
	ldr	x2, [x24, #:lo12:.LANCHOR102]
	ldr	x3, [x29, 120]
	ldrh	w1, [x0, #:lo12:.LANCHOR11]
	add	x2, x2, x22
	mov	x0, 0
	ubfiz	x1, x1, 9, 16
.L1043:
	cmp	x0, x1
	beq	.L1042
	ldr	x4, [x2, 8]
	ldr	w5, [x4, x0]
	add	x0, x0, 4
	add	x4, x3, x0
	ldr	w4, [x4, -4]
	cmp	w5, w4
	beq	.L1043
	ldrh	w1, [x19]
	adrp	x0, .LC35
	ldr	w2, [x29, 116]
	add	x0, x0, :lo12:.LC35
	bl	printf
	b	.L1058
.L1036:
	mov	w2, -1
	b	.L1059
	.size	FtlGcScanTempBlk, .-FtlGcScanTempBlk
	.section	.text.FtlVendorPartWrite,"ax",@progbits
	.align	2
	.global	FtlVendorPartWrite
	.type	FtlVendorPartWrite, %function
FtlVendorPartWrite:
	stp	x29, x30, [sp, -208]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w20, w1
	stp	x27, x28, [sp, 80]
	add	w1, w0, w1
	mov	w28, w0
	adrp	x0, .LANCHOR15
	stp	x21, x22, [sp, 32]
	ldrh	w0, [x0, #:lo12:.LANCHOR15]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	cmp	w1, w0
	bhi	.L1068
	adrp	x0, .LANCHOR21
	adrp	x25, .LANCHOR11
	adrp	x26, .LANCHOR22
	mov	x24, x2
	ldrh	w21, [x0, #:lo12:.LANCHOR21]
	add	x25, x25, :lo12:.LANCHOR11
	add	x26, x26, :lo12:.LANCHOR22
	mov	w23, 0
	lsr	w21, w28, w21
.L1062:
	cbnz	w20, .L1067
.L1060:
	mov	w0, w23
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 208
	ret
.L1067:
	ldrh	w1, [x25]
	adrp	x0, .LANCHOR122
	adrp	x27, .LANCHOR107
	ldr	x0, [x0, #:lo12:.LANCHOR122]
	udiv	w22, w28, w1
	ldr	w2, [x0, w21, uxtw 2]
	and	w0, w20, 65535
	msub	w22, w22, w1, w28
	sub	w19, w1, w22
	and	w19, w19, 65535
	cmp	w20, w19
	csel	w19, w0, w19, cc
	cbz	w2, .L1064
	cmp	w19, w1
	beq	.L1064
	ldr	x0, [x27, #:lo12:.LANCHOR107]
	str	x0, [x29, 120]
	add	x0, x29, 144
	str	w2, [x29, 116]
	mov	w2, 1
	str	x0, [x29, 128]
	mov	w1, w2
	add	x0, x29, 112
	bl	FlashReadPages
.L1065:
	lsl	w4, w19, 9
	ldr	x0, [x27, #:lo12:.LANCHOR107]
	lsl	w22, w22, 7
	mov	w2, w4
	mov	x1, x24
	str	w4, [x29, 108]
	add	x0, x0, x22, sxtw 2
	bl	ftl_memcpy
	ldr	x2, [x27, #:lo12:.LANCHOR107]
	mov	w1, w21
	adrp	x0, .LANCHOR160
	add	x0, x0, :lo12:.LANCHOR160
	sub	w20, w20, w19
	add	w28, w28, w19
	add	w21, w21, 1
	bl	FtlMapWritePage
	cmn	w0, #1
	ldr	w4, [x29, 108]
	csinv	w23, w23, wzr, ne
	add	x24, x24, x4, sxtw
	b	.L1062
.L1064:
	ldrh	w2, [x26]
	mov	w1, 0
	ldr	x0, [x27, #:lo12:.LANCHOR107]
	bl	ftl_memset
	b	.L1065
.L1068:
	mov	w23, -1
	b	.L1060
	.size	FtlVendorPartWrite, .-FtlVendorPartWrite
	.section	.text.Ftl_save_ext_data,"ax",@progbits
	.align	2
	.global	Ftl_save_ext_data
	.type	Ftl_save_ext_data, %function
Ftl_save_ext_data:
	adrp	x0, .LANCHOR134
	add	x2, x0, :lo12:.LANCHOR134
	ldr	w1, [x0, #:lo12:.LANCHOR134]
	mov	w0, 19539
	movk	w0, 0x4654, lsl 16
	cmp	w1, w0
	bne	.L1073
	mov	w0, 86
	mov	w1, 1
	movk	w0, 0x5000, lsl 16
	str	w0, [x2, 4]
	adrp	x0, .LANCHOR161
	ldr	w0, [x0, #:lo12:.LANCHOR161]
	str	w0, [x2, 88]
	adrp	x0, .LANCHOR162
	ldr	w0, [x0, #:lo12:.LANCHOR162]
	str	w0, [x2, 92]
	adrp	x0, .LANCHOR83
	ldr	w0, [x0, #:lo12:.LANCHOR83]
	str	w0, [x2, 8]
	adrp	x0, .LANCHOR84
	ldr	w0, [x0, #:lo12:.LANCHOR84]
	str	w0, [x2, 12]
	adrp	x0, .LANCHOR88
	ldr	w0, [x0, #:lo12:.LANCHOR88]
	str	w0, [x2, 16]
	adrp	x0, .LANCHOR87
	ldr	w0, [x0, #:lo12:.LANCHOR87]
	str	w0, [x2, 20]
	adrp	x0, .LANCHOR90
	ldr	w0, [x0, #:lo12:.LANCHOR90]
	str	w0, [x2, 28]
	adrp	x0, .LANCHOR79
	ldr	w0, [x0, #:lo12:.LANCHOR79]
	str	w0, [x2, 32]
	adrp	x0, .LANCHOR85
	ldr	w0, [x0, #:lo12:.LANCHOR85]
	str	w0, [x2, 36]
	adrp	x0, .LANCHOR86
	ldr	w0, [x0, #:lo12:.LANCHOR86]
	str	w0, [x2, 40]
	adrp	x0, .LANCHOR91
	ldr	w0, [x0, #:lo12:.LANCHOR91]
	str	w0, [x2, 44]
	adrp	x0, .LANCHOR92
	ldr	w0, [x0, #:lo12:.LANCHOR92]
	str	w0, [x2, 48]
	mov	w0, 0
	b	FtlVendorPartWrite
.L1073:
	ret
	.size	Ftl_save_ext_data, .-Ftl_save_ext_data
	.section	.text.FtlEctTblFlush,"ax",@progbits
	.align	2
	.global	FtlEctTblFlush
	.type	FtlEctTblFlush, %function
FtlEctTblFlush:
	adrp	x2, .LANCHOR163
	ldrh	w1, [x2, #:lo12:.LANCHOR163]
	cmp	w1, 31
	bhi	.L1079
	add	w1, w1, 1
	strh	w1, [x2, #:lo12:.LANCHOR163]
	mov	w1, 1
.L1076:
	adrp	x2, .LANCHOR117
	cbnz	w0, .L1077
	ldr	x0, [x2, #:lo12:.LANCHOR117]
	ldr	w3, [x0, 20]
	ldr	w0, [x0, 16]
	add	w1, w1, w3
	cmp	w0, w1
	bcc	.L1081
.L1077:
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
	ldr	x2, [x2, #:lo12:.LANCHOR117]
	ldr	w0, [x2, 16]
	str	w0, [x2, 20]
	mov	w0, 17221
	str	wzr, [x2, 4]
	movk	w0, 0x4254, lsl 16
	str	w0, [x2]
	adrp	x0, .LANCHOR115
	ldrh	w1, [x0, #:lo12:.LANCHOR115]
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
.L1079:
	mov	w1, 32
	b	.L1076
.L1081:
	mov	w0, 0
	ret
	.size	FtlEctTblFlush, .-FtlEctTblFlush
	.section	.text.sftl_vendor_write,"ax",@progbits
	.align	2
	.global	sftl_vendor_write
	.type	sftl_vendor_write, %function
sftl_vendor_write:
	add	w0, w0, 256
	b	FtlVendorPartWrite
	.size	sftl_vendor_write, .-sftl_vendor_write
	.section	.text.FtlVendorPartRead,"ax",@progbits
	.align	2
	.global	FtlVendorPartRead
	.type	FtlVendorPartRead, %function
FtlVendorPartRead:
	stp	x29, x30, [sp, -208]!
	add	x29, sp, 0
	stp	x21, x22, [sp, 32]
	mov	w22, w0
	mov	w21, w1
	add	w1, w0, w1
	adrp	x0, .LANCHOR15
	stp	x19, x20, [sp, 16]
	stp	x23, x24, [sp, 48]
	ldrh	w0, [x0, #:lo12:.LANCHOR15]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	cmp	w1, w0
	bhi	.L1093
	adrp	x0, .LANCHOR21
	mov	x25, x2
	mov	w24, 0
	adrp	x27, .LANCHOR122
	ldrh	w20, [x0, #:lo12:.LANCHOR21]
	adrp	x0, .LANCHOR11
	add	x0, x0, :lo12:.LANCHOR11
	str	x0, [x29, 104]
	lsr	w20, w22, w20
.L1086:
	cbnz	w21, .L1092
.L1084:
	mov	w0, w24
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 208
	ret
.L1092:
	ldr	x0, [x27, #:lo12:.LANCHOR122]
	ldr	w4, [x0, w20, uxtw 2]
	ldr	x0, [x29, 104]
	ldrh	w19, [x0]
	and	w0, w21, 65535
	udiv	w23, w22, w19
	msub	w23, w23, w19, w22
	sub	w19, w19, w23
	and	w19, w19, 65535
	cmp	w21, w19
	csel	w19, w0, w19, cc
	lsl	w26, w19, 9
	cbz	w4, .L1088
	adrp	x28, .LANCHOR107
	mov	w2, 1
	str	w4, [x29, 96]
	mov	w1, w2
	ldr	x0, [x28, #:lo12:.LANCHOR107]
	str	x0, [x29, 120]
	add	x0, x29, 144
	str	w4, [x29, 116]
	str	x0, [x29, 128]
	add	x0, x29, 112
	bl	FlashReadPages
	ldr	w0, [x29, 112]
	mov	x5, x28
	ldr	w4, [x29, 96]
	cmn	w0, #1
	adrp	x0, .LANCHOR137
	csinv	w24, w24, wzr, ne
	ldr	w0, [x0, #:lo12:.LANCHOR137]
	cmp	w0, 256
	bne	.L1090
	mov	w2, w4
	mov	w1, w20
	adrp	x0, .LC36
	str	x28, [x29, 96]
	add	x0, x0, :lo12:.LC36
	bl	printf
	ldr	x2, [x28, #:lo12:.LANCHOR107]
	mov	w1, w20
	adrp	x0, .LANCHOR160
	add	x0, x0, :lo12:.LANCHOR160
	bl	FtlMapWritePage
	ldr	x5, [x29, 96]
.L1090:
	ldr	x1, [x5, #:lo12:.LANCHOR107]
	lsl	w23, w23, 7
	mov	w2, w26
	mov	x0, x25
	add	x1, x1, x23, sxtw 2
	bl	ftl_memcpy
.L1091:
	add	w20, w20, 1
	sub	w21, w21, w19
	add	w22, w22, w19
	add	x25, x25, x26, sxtw
	b	.L1086
.L1088:
	mov	w2, w26
	mov	w1, 0
	mov	x0, x25
	bl	ftl_memset
	b	.L1091
.L1093:
	mov	w24, -1
	b	.L1084
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
	adrp	x19, .LANCHOR117
	adrp	x20, .LANCHOR115
	ldr	x2, [x19, #:lo12:.LANCHOR117]
	ldrh	w1, [x20, #:lo12:.LANCHOR115]
	bl	FtlVendorPartRead
	ldr	x0, [x19, #:lo12:.LANCHOR117]
	ldr	w1, [x0]
	mov	w0, 17221
	movk	w0, 0x4254, lsl 16
	cmp	w1, w0
	beq	.L1096
	adrp	x1, .LC37
	adrp	x0, .LC38
	add	x1, x1, :lo12:.LC37
	add	x0, x0, :lo12:.LC38
	bl	printf
	ldr	x0, [x19, #:lo12:.LANCHOR117]
	mov	w1, 0
	ldrh	w2, [x20, #:lo12:.LANCHOR115]
	lsl	w2, w2, 9
	bl	ftl_memset
.L1096:
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
	adrp	x19, .LANCHOR134
	str	x21, [sp, 32]
	add	x21, x19, :lo12:.LANCHOR134
	mov	x2, x21
	bl	FtlVendorPartRead
	ldr	w0, [x19, #:lo12:.LANCHOR134]
	mov	w20, 19539
	movk	w20, 0x4654, lsl 16
	cmp	w0, w20
	beq	.L1099
	mov	w2, 512
	mov	w1, 0
	mov	x0, x21
	bl	ftl_memset
	str	w20, [x19, #:lo12:.LANCHOR134]
.L1099:
	ldr	w1, [x19, #:lo12:.LANCHOR134]
	add	x0, x19, :lo12:.LANCHOR134
	cmp	w1, w20
	adrp	x1, .LANCHOR90
	bne	.L1100
	adrp	x2, .LANCHOR161
	ldr	w3, [x0, 88]
	str	w3, [x2, #:lo12:.LANCHOR161]
	adrp	x2, .LANCHOR162
	ldr	w3, [x0, 92]
	str	w3, [x2, #:lo12:.LANCHOR162]
	adrp	x2, .LANCHOR83
	ldr	w3, [x0, 8]
	str	w3, [x2, #:lo12:.LANCHOR83]
	adrp	x2, .LANCHOR84
	ldr	w3, [x0, 12]
	str	w3, [x2, #:lo12:.LANCHOR84]
	adrp	x2, .LANCHOR88
	ldr	w3, [x0, 16]
	str	w3, [x2, #:lo12:.LANCHOR88]
	adrp	x2, .LANCHOR87
	ldr	w3, [x0, 20]
	str	w3, [x2, #:lo12:.LANCHOR87]
	ldp	w2, w3, [x0, 28]
	str	w2, [x1, #:lo12:.LANCHOR90]
	adrp	x2, .LANCHOR79
	str	w3, [x2, #:lo12:.LANCHOR79]
	adrp	x2, .LANCHOR85
	ldr	w3, [x0, 36]
	str	w3, [x2, #:lo12:.LANCHOR85]
	adrp	x2, .LANCHOR86
	ldr	w3, [x0, 40]
	str	w3, [x2, #:lo12:.LANCHOR86]
	adrp	x2, .LANCHOR91
	ldr	w3, [x0, 44]
	str	w3, [x2, #:lo12:.LANCHOR91]
	ldr	w2, [x0, 48]
	adrp	x0, .LANCHOR92
	str	w2, [x0, #:lo12:.LANCHOR92]
.L1100:
	adrp	x0, .LANCHOR13
	adrp	x2, .LANCHOR89
	ldr	w1, [x1, #:lo12:.LANCHOR90]
	ldrh	w0, [x0, #:lo12:.LANCHOR13]
	ldr	w2, [x2, #:lo12:.LANCHOR89]
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	madd	w0, w0, w2, w1
	adrp	x1, .LANCHOR4
	ldp	x29, x30, [sp], 48
	ldrh	w1, [x1, #:lo12:.LANCHOR4]
	udiv	w0, w0, w1
	adrp	x1, .LANCHOR142
	str	w0, [x1, #:lo12:.LANCHOR142]
	ret
	.size	Ftl_load_ext_data, .-Ftl_load_ext_data
	.section	.text.sftl_vendor_read,"ax",@progbits
	.align	2
	.global	sftl_vendor_read
	.type	sftl_vendor_read, %function
sftl_vendor_read:
	add	w0, w0, 256
	b	FtlVendorPartRead
	.size	sftl_vendor_read, .-sftl_vendor_read
	.section	.text.FtlMapBlkWriteDump_data,"ax",@progbits
	.align	2
	.global	FtlMapBlkWriteDump_data
	.type	FtlMapBlkWriteDump_data, %function
FtlMapBlkWriteDump_data:
	ldr	w1, [x0, 56]
	cbz	w1, .L1103
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	ldrh	w20, [x0, 6]
	adrp	x0, .LANCHOR106
	stp	x21, x22, [sp, 32]
	stp	x23, x24, [sp, 48]
	adrp	x23, .LANCHOR137
	add	x21, x23, :lo12:.LANCHOR137
	ldr	x0, [x0, #:lo12:.LANCHOR106]
	mov	x22, x23
	str	x0, [x21, 8]
	adrp	x0, .LANCHOR113
	ldr	x24, [x0, #:lo12:.LANCHOR113]
	ldrh	w0, [x19, 2]
	str	x25, [sp, 64]
	str	x24, [x21, 16]
	str	wzr, [x19, 56]
	ldr	x25, [x19, 40]
	cbz	w0, .L1105
	adrp	x1, .LANCHOR19
	ldrh	w1, [x1, #:lo12:.LANCHOR19]
	sub	w1, w1, #1
	cmp	w0, w1
	bge	.L1105
	ldrh	w1, [x19]
	mov	w2, 65535
	cmp	w1, w2
	beq	.L1105
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
	ldr	w0, [x23, #:lo12:.LANCHOR137]
	cmn	w0, #1
	beq	.L1105
	ldrh	w1, [x24, 8]
	ldr	x2, [x19, 40]
	ubfiz	x0, x1, 2, 16
	ldr	w2, [x2, x0]
	ldr	w0, [x21, 4]
	cmp	w2, w0
	bne	.L1105
	ldr	x2, [x21, 8]
.L1117:
	mov	x0, x19
	ldr	x25, [sp, 64]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 80
	b	FtlMapWritePage
.L1105:
	sub	w20, w20, #1
	and	w20, w20, 65535
	ubfiz	x0, x20, 2, 16
	ldr	w1, [x25, x0]
	add	x0, x22, :lo12:.LANCHOR137
	str	w1, [x0, 4]
	cbz	w1, .L1106
	mov	w2, 1
	mov	w1, w2
	bl	FlashReadPages
.L1107:
	add	x22, x22, :lo12:.LANCHOR137
	mov	w1, w20
	ldr	x2, [x22, 8]
	b	.L1117
.L1106:
	adrp	x1, .LANCHOR22
	ldr	x0, [x0, 8]
	ldrh	w2, [x1, #:lo12:.LANCHOR22]
	mov	w1, 255
	bl	ftl_memset
	b	.L1107
.L1103:
	ret
	.size	FtlMapBlkWriteDump_data, .-FtlMapBlkWriteDump_data
	.section	.text.FtlVpcTblFlush,"ax",@progbits
	.align	2
	.global	FtlVpcTblFlush
	.type	FtlVpcTblFlush, %function
FtlVpcTblFlush:
	stp	x29, x30, [sp, -112]!
	adrp	x1, .LANCHOR138
	mov	w2, 19539
	add	x29, sp, 0
	stp	x25, x26, [sp, 64]
	adrp	x25, .LANCHOR113
	stp	x21, x22, [sp, 32]
	adrp	x22, .LANCHOR105
	stp	x23, x24, [sp, 48]
	adrp	x21, .LANCHOR137
	stp	x27, x28, [sp, 80]
	add	x24, x21, :lo12:.LANCHOR137
	ldr	x27, [x25, #:lo12:.LANCHOR113]
	add	x28, x1, :lo12:.LANCHOR138
	stp	x19, x20, [sp, 16]
	movk	w2, 0x4654, lsl 16
	ldr	x0, [x22, #:lo12:.LANCHOR105]
	adrp	x23, .LANCHOR81
	ldrh	w1, [x1, #:lo12:.LANCHOR138]
	adrp	x26, .LANCHOR22
	stp	x0, x27, [x24, 8]
	mov	w20, 0
	strh	w1, [x27, 2]
	mov	w1, -3932
	strh	w1, [x27]
	ldr	w1, [x28, 8]
	stp	w1, wzr, [x27, 4]
	adrp	x1, .LANCHOR38
	add	x19, x1, :lo12:.LANCHOR38
	str	wzr, [x27, 12]
	str	w2, [x1, #:lo12:.LANCHOR38]
	mov	w1, 86
	movk	w1, 0x5000, lsl 16
	str	w1, [x19, 4]
	ldrh	w1, [x28, 6]
	adrp	x2, .LANCHOR50
	strh	w1, [x19, 8]
	adrp	x1, .LANCHOR9
	ldrh	w1, [x1, #:lo12:.LANCHOR9]
	strb	w1, [x19, 10]
	add	x1, x2, :lo12:.LANCHOR50
	ldrh	w2, [x2, #:lo12:.LANCHOR50]
	strh	w2, [x19, 14]
	ldrh	w2, [x1, 2]
	ldrb	w3, [x1, 6]
	ldrb	w1, [x1, 8]
	strb	w1, [x19, 11]
	orr	w2, w3, w2, lsl 6
	strh	w2, [x19, 16]
	adrp	x2, .LANCHOR51
	add	x1, x2, :lo12:.LANCHOR51
	ldrh	w2, [x2, #:lo12:.LANCHOR51]
	ldrb	w3, [x1, 6]
	strh	w2, [x19, 18]
	ldrh	w2, [x1, 2]
	ldrb	w1, [x1, 8]
	strb	w1, [x19, 12]
	orr	w2, w3, w2, lsl 6
	strh	w2, [x19, 20]
	adrp	x2, .LANCHOR52
	add	x1, x2, :lo12:.LANCHOR52
	ldrh	w2, [x2, #:lo12:.LANCHOR52]
	ldrb	w3, [x1, 6]
	strh	w2, [x19, 22]
	ldrh	w2, [x1, 2]
	ldrb	w1, [x1, 8]
	strb	w1, [x19, 13]
	adrp	x1, .LANCHOR89
	orr	w2, w3, w2, lsl 6
	strh	w2, [x19, 24]
	ldr	w1, [x1, #:lo12:.LANCHOR89]
	str	w1, [x19, 32]
	ldr	w1, [x23, #:lo12:.LANCHOR81]
	str	w1, [x19, 40]
	ldrh	w2, [x26, #:lo12:.LANCHOR22]
	adrp	x1, .LANCHOR82
	ldr	w1, [x1, #:lo12:.LANCHOR82]
	str	w1, [x19, 36]
	mov	w1, 255
	bl	ftl_memset
	ldr	x0, [x24, 8]
	mov	x1, x19
	mov	w2, 48
	mov	x19, x24
	bl	ftl_memcpy
	adrp	x0, .LANCHOR4
	adrp	x1, .LANCHOR41
	ldrh	w2, [x0, #:lo12:.LANCHOR4]
	ldr	x1, [x1, #:lo12:.LANCHOR41]
	ldr	x0, [x24, 8]
	adrp	x24, .LANCHOR19
	lsl	w2, w2, 1
	add	x24, x24, :lo12:.LANCHOR19
	add	x0, x0, 48
	bl	ftl_memcpy
	mov	w0, 0
	bl	FtlUpdateVaildLpn
	mov	w0, 65535
	str	x24, [x29, 96]
	str	w0, [x29, 108]
.L1119:
	ldrh	w2, [x28, 2]
	ldrh	w1, [x28]
	ldr	x0, [x22, #:lo12:.LANCHOR105]
	str	x0, [x19, 8]
	ldr	x0, [x25, #:lo12:.LANCHOR113]
	str	x0, [x19, 16]
	orr	w0, w2, w1, lsl 10
	str	w0, [x19, 4]
	ldrh	w0, [x24]
	sub	w0, w0, #1
	cmp	w2, w0
	blt	.L1120
	ldrh	w0, [x28, 4]
	strh	wzr, [x28, 2]
	strh	w1, [x28, 4]
	str	w0, [x29, 108]
	bl	FtlFreeSysBlkQueueOut
	strh	w0, [x28]
	ldr	w1, [x23, #:lo12:.LANCHOR81]
	str	w1, [x28, 8]
	add	w2, w1, 1
	str	w2, [x23, #:lo12:.LANCHOR81]
	ubfiz	w2, w0, 10, 16
	str	w2, [x19, 4]
	strh	w0, [x27, 2]
	str	w1, [x27, 4]
.L1120:
	ldrh	w1, [x26, #:lo12:.LANCHOR22]
	ldr	x0, [x22, #:lo12:.LANCHOR105]
	bl	js_hash
	str	w0, [x27, 12]
	mov	w3, 1
	mov	x0, x19
	mov	w1, w3
	mov	w2, w3
	bl	FlashProgPages
	ldrh	w0, [x28, 2]
	ldr	w1, [x19]
	add	w0, w0, 1
	and	w0, w0, 65535
	strh	w0, [x28, 2]
	cmn	w1, #1
	bne	.L1121
	cmp	w0, 1
	bne	.L1122
	adrp	x1, .LANCHOR164
	adrp	x0, .LC1
	mov	w2, 1145
	add	x1, x1, :lo12:.LANCHOR164
	add	x0, x0, :lo12:.LC1
	bl	printf
.L1122:
	ldrh	w0, [x28, 2]
	cmp	w0, 1
	bne	.L1123
	ldr	x0, [x29, 96]
	ldrh	w0, [x0]
	sub	w0, w0, #1
	strh	w0, [x28, 2]
.L1123:
	add	w20, w20, 1
	and	w20, w20, 65535
	cmp	w20, 3
	bls	.L1119
	add	x21, x21, :lo12:.LANCHOR137
	adrp	x0, .LC39
	mov	w2, w20
	add	x0, x0, :lo12:.LC39
	ldr	w1, [x21, 4]
	bl	printf
.L1125:
	b	.L1125
.L1121:
	cmp	w0, 1
	beq	.L1119
	cmp	w1, 256
	beq	.L1119
	ldr	w1, [x29, 108]
	mov	w0, 65535
	cmp	w1, w0
	beq	.L1126
	ldrh	w0, [x29, 108]
	mov	w1, 1
	bl	FtlFreeSysBlkQueueIn
.L1126:
	ldp	x19, x20, [sp, 16]
	mov	w0, 0
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
	.size	FtlVpcTblFlush, .-FtlVpcTblFlush
	.section	.text.FtlSysFlush,"ax",@progbits
	.align	2
	.global	FtlSysFlush
	.type	FtlSysFlush, %function
FtlSysFlush:
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
	bl	l2p_flush
	mov	w0, 1
	bl	FtlEctTblFlush
	bl	FtlVpcTblFlush
	mov	w0, 0
	ldp	x29, x30, [sp], 16
	ret
	.size	FtlSysFlush, .-FtlSysFlush
	.section	.text.sftl_deinit,"ax",@progbits
	.align	2
	.global	sftl_deinit
	.type	sftl_deinit, %function
sftl_deinit:
	adrp	x0, .LANCHOR165
	ldr	w0, [x0, #:lo12:.LANCHOR165]
	cmp	w0, 1
	bne	.L1139
	stp	x29, x30, [sp, -16]!
	add	x29, sp, 0
	bl	FtlSysFlush
	mov	w0, 0
	ldp	x29, x30, [sp], 16
	ret
.L1139:
	mov	w0, 0
	ret
	.size	sftl_deinit, .-sftl_deinit
	.section	.text.FtlDiscard,"ax",@progbits
	.align	2
	.global	FtlDiscard
	.type	FtlDiscard, %function
FtlDiscard:
	stp	x29, x30, [sp, -80]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w19, w1
	adrp	x1, .LANCHOR33
	stp	x21, x22, [sp, 32]
	str	x23, [sp, 48]
	ldr	w1, [x1, #:lo12:.LANCHOR33]
	cmp	w1, w0
	bls	.L1152
	cmp	w1, w19
	bcc	.L1152
	add	w2, w0, w19
	cmp	w1, w2
	bcc	.L1152
	cmp	w19, 31
	bhi	.L1144
.L1160:
	mov	w0, 0
.L1142:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldr	x23, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
.L1144:
	adrp	x21, .LANCHOR11
	ldrh	w1, [x21, #:lo12:.LANCHOR11]
	udiv	w20, w0, w1
	msub	w0, w1, w20, w0
	ands	w0, w0, 65535
	beq	.L1145
	sub	w0, w1, w0
	add	w20, w20, 1
	cmp	w0, w19
	csel	w0, w0, w19, ls
	sub	w19, w19, w0, uxth
.L1145:
	adrp	x22, .LANCHOR166
	adrp	x23, .LANCHOR85
	add	x22, x22, :lo12:.LANCHOR166
	add	x23, x23, :lo12:.LANCHOR85
	mov	w0, -1
	str	w0, [x29, 76]
.L1146:
	ldrh	w0, [x21, #:lo12:.LANCHOR11]
	cmp	w19, w0
	bcs	.L1148
	adrp	x0, .LANCHOR166
	ldr	w1, [x0, #:lo12:.LANCHOR166]
	cmp	w1, 32
	bls	.L1160
	str	wzr, [x0, #:lo12:.LANCHOR166]
	bl	l2p_flush
	bl	FtlVpcTblFlush
	b	.L1160
.L1148:
	mov	w2, 0
	add	x1, x29, 72
	mov	w0, w20
	bl	log2phys
	ldr	w0, [x29, 72]
	cmn	w0, #1
	beq	.L1147
	ldr	w0, [x22]
	mov	w2, 1
	add	x1, x29, 76
	add	w0, w0, 1
	str	w0, [x22]
	ldr	w0, [x23]
	add	w0, w0, 1
	str	w0, [x23]
	mov	w0, w20
	bl	log2phys
	ldr	w0, [x29, 72]
	lsr	w0, w0, 10
	bl	P2V_block_in_plane
	bl	decrement_vpc_count
.L1147:
	ldrh	w0, [x21, #:lo12:.LANCHOR11]
	add	w20, w20, 1
	sub	w19, w19, w0
	b	.L1146
.L1152:
	mov	w0, -1
	b	.L1142
	.size	FtlDiscard, .-FtlDiscard
	.section	.text.allocate_new_data_superblock,"ax",@progbits
	.align	2
	.global	allocate_new_data_superblock
	.type	allocate_new_data_superblock, %function
allocate_new_data_superblock:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	ldrh	w19, [x0]
	str	x21, [sp, 32]
	mov	x21, x0
	adrp	x0, .LANCHOR4
	ldrh	w0, [x0, #:lo12:.LANCHOR4]
	cmp	w0, w19
	bcs	.L1162
	adrp	x1, .LANCHOR167
	adrp	x0, .LC1
	mov	w2, 2766
	add	x1, x1, :lo12:.LANCHOR167
	add	x0, x0, :lo12:.LC1
	bl	printf
.L1162:
	mov	w0, 65535
	cmp	w19, w0
	beq	.L1163
	adrp	x1, .LANCHOR41
	ubfiz	x0, x19, 1, 16
	ldr	x1, [x1, #:lo12:.LANCHOR41]
	ldrh	w0, [x1, x0]
	cbz	w0, .L1164
	mov	w0, w19
	bl	INSERT_DATA_LIST
.L1163:
	adrp	x1, .LANCHOR130
	mov	w0, 1
	strb	w0, [x21, 8]
	mov	w2, 65535
	ldrh	w0, [x1, #:lo12:.LANCHOR130]
	mov	x20, x1
	cmp	w0, w2
	beq	.L1165
	cmp	w19, w0
	bne	.L1166
	adrp	x2, .LANCHOR41
	ubfiz	x1, x0, 1, 16
	ldr	x2, [x2, #:lo12:.LANCHOR41]
	ldrh	w1, [x2, x1]
	cbz	w1, .L1167
.L1166:
	bl	update_vpc_list
.L1167:
	mov	w0, -1
	strh	w0, [x20, #:lo12:.LANCHOR130]
.L1165:
	mov	x0, x21
	bl	allocate_data_superblock
	bl	l2p_flush
	mov	w0, 0
	bl	FtlEctTblFlush
	bl	FtlVpcTblFlush
	ldr	x21, [sp, 32]
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 48
	ret
.L1164:
	mov	w0, w19
	bl	INSERT_FREE_LIST
	b	.L1163
	.size	allocate_new_data_superblock, .-allocate_new_data_superblock
	.section	.text.FtlProgPages,"ax",@progbits
	.align	2
	.global	FtlProgPages
	.type	FtlProgPages, %function
FtlProgPages:
	stp	x29, x30, [sp, -80]!
	mov	w2, 0
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x20, x3
	stp	x21, x22, [sp, 32]
	mov	w21, w1
	stp	x23, x24, [sp, 48]
	ubfiz	x21, x21, 5, 32
	mov	x22, x0
	add	x21, x21, 4
	ldrb	w3, [x3, 9]
	adrp	x23, .LC40
	adrp	x24, .LANCHOR2
	add	x19, x22, 4
	add	x21, x22, x21
	add	x23, x23, :lo12:.LC40
	add	x24, x24, :lo12:.LANCHOR2
	bl	FlashProgPages
.L1173:
	cmp	x21, x19
	beq	.L1179
	sub	x22, x19, #4
	b	.L1180
.L1175:
	ldr	w1, [x19]
	mov	x0, x23
	bl	printf
	ldr	w0, [x19]
	lsr	w0, w0, 10
	bl	P2V_block_in_plane
	bl	decrement_vpc_count
	ldrh	w0, [x20, 4]
	cbnz	w0, .L1174
	mov	x0, x20
	bl	allocate_new_data_superblock
.L1174:
	mov	x0, x20
	bl	get_new_active_ppa
	str	w0, [x19]
	mov	w2, 0
	str	w0, [x29, 76]
	mov	w1, 1
	ldrb	w3, [x20, 9]
	mov	x0, x22
	bl	FlashProgPages
.L1180:
	ldr	w2, [x19, -4]
	cmp	w2, 256
	ccmn	w2, #1, 4, ne
	beq	.L1175
	ldrb	w1, [x20, 6]
	ldrh	w0, [x24]
	cmp	w1, w0
	bcc	.L1176
	adrp	x1, .LANCHOR168
	adrp	x0, .LC1
	mov	w2, 985
	add	x1, x1, :lo12:.LANCHOR168
	add	x0, x0, :lo12:.LC1
	bl	printf
.L1176:
	add	x1, x29, 80
	ldr	w0, [x22, 4]
	mov	w2, 1
	str	w0, [x1, -4]!
	ldr	w0, [x22, 24]
	bl	log2phys
	ldr	x0, [x22, 16]
	ldr	w3, [x0, 12]
	lsr	w0, w3, 10
	bl	P2V_block_in_plane
	and	w1, w0, 65535
	mov	w22, w1
	cmn	w3, #1
	beq	.L1177
	adrp	x2, .LANCHOR41
	ubfiz	x0, x1, 1, 16
	ldr	x2, [x2, #:lo12:.LANCHOR41]
	ldrh	w0, [x2, x0]
	cbnz	w0, .L1178
	adrp	x0, .LC41
	mov	w2, 0
	add	x0, x0, :lo12:.LC41
	bl	printf
.L1178:
	mov	w0, w22
	bl	decrement_vpc_count
.L1177:
	add	x19, x19, 32
	b	.L1173
.L1179:
	adrp	x0, .LANCHOR2
	ldrb	w1, [x20, 6]
	ldrh	w0, [x0, #:lo12:.LANCHOR2]
	cmp	w1, w0
	bcc	.L1172
	adrp	x1, .LANCHOR168
	adrp	x0, .LC1
	mov	w2, 1000
	add	x1, x1, :lo12:.LANCHOR168
	add	x0, x0, :lo12:.LC1
	bl	printf
.L1172:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x29, x30, [sp], 80
	ret
	.size	FtlProgPages, .-FtlProgPages
	.section	.text.FtlGcFreeTempBlock,"ax",@progbits
	.align	2
	.global	FtlGcFreeTempBlock
	.type	FtlGcFreeTempBlock, %function
FtlGcFreeTempBlock:
	stp	x29, x30, [sp, -112]!
	mov	w1, 65535
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	adrp	x19, .LANCHOR52
	stp	x21, x22, [sp, 32]
	ldrh	w2, [x19, #:lo12:.LANCHOR52]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	cmp	w2, w1
	stp	x27, x28, [sp, 80]
	beq	.L1187
	adrp	x1, .LANCHOR18
	add	x0, x19, :lo12:.LANCHOR52
	ldrh	w1, [x1, #:lo12:.LANCHOR18]
	bl	FtlGcScanTempBlk
	str	w0, [x29, 108]
.L1187:
	adrp	x0, .LANCHOR132
	ldrh	w2, [x19, #:lo12:.LANCHOR52]
	mov	w1, 65535
	str	wzr, [x0, #:lo12:.LANCHOR132]
	cmp	w2, w1
	add	x0, x19, :lo12:.LANCHOR52
	beq	.L1189
	ldrb	w1, [x0, 7]
	adrp	x0, .LANCHOR18
	adrp	x20, .LANCHOR69
	mov	x21, x0
	ldrh	w3, [x0, #:lo12:.LANCHOR18]
	ldrh	w2, [x20, #:lo12:.LANCHOR69]
	mul	w1, w1, w3
	cmp	w2, w1
	beq	.L1190
	adrp	x1, .LANCHOR169
	adrp	x0, .LC1
	mov	w2, 164
	add	x1, x1, :lo12:.LANCHOR169
	add	x0, x0, :lo12:.LC1
	bl	printf
.L1190:
	add	x0, x19, :lo12:.LANCHOR52
	adrp	x22, .LANCHOR41
	ldrh	w3, [x21, #:lo12:.LANCHOR18]
	adrp	x25, .LANCHOR151
	ldrh	w2, [x19, #:lo12:.LANCHOR52]
	add	x26, x20, :lo12:.LANCHOR69
	ldrb	w0, [x0, 7]
	add	x25, x25, :lo12:.LANCHOR151
	ldr	x1, [x22, #:lo12:.LANCHOR41]
	mov	w21, 0
	adrp	x27, .LANCHOR70
	mul	w0, w0, w3
	strh	w0, [x1, x2, lsl 1]
	adrp	x1, .LANCHOR83
	ldrh	w0, [x20, #:lo12:.LANCHOR69]
	ldr	w2, [x1, #:lo12:.LANCHOR83]
	add	w0, w0, w2
	str	w0, [x1, #:lo12:.LANCHOR83]
.L1191:
	ldrh	w0, [x26]
	cmp	w0, w21
	bhi	.L1195
	mov	w0, -1
	bl	decrement_vpc_count
	ldrh	w0, [x19, #:lo12:.LANCHOR52]
	ldr	x2, [x22, #:lo12:.LANCHOR41]
	ubfiz	x1, x0, 1, 16
	ldrh	w1, [x2, x1]
	cbz	w1, .L1196
	bl	INSERT_DATA_LIST
.L1197:
	adrp	x0, .LANCHOR67
	mov	w21, -1
	strh	wzr, [x20, #:lo12:.LANCHOR69]
	strh	w21, [x19, #:lo12:.LANCHOR52]
	strh	wzr, [x0, #:lo12:.LANCHOR67]
	bl	l2p_flush
	bl	FtlVpcTblFlush
	adrp	x0, .LANCHOR144
	strh	w21, [x0, #:lo12:.LANCHOR144]
	adrp	x0, .LANCHOR47
	ldrh	w1, [x0, #:lo12:.LANCHOR47]
	adrp	x0, .LANCHOR170
	ldrh	w0, [x0, #:lo12:.LANCHOR170]
	add	w0, w0, w0, lsl 1
	cmp	w1, w0, lsr 2
	ble	.L1189
	adrp	x0, .LANCHOR99
	mov	w1, 20
	strh	w1, [x0, #:lo12:.LANCHOR99]
.L1189:
	ldp	x19, x20, [sp, 16]
	mov	w0, 0
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
.L1195:
	mov	w24, 12
	ldr	x28, [x27, #:lo12:.LANCHOR70]
	ldr	w1, [x25]
	umull	x24, w21, w24
	add	x23, x28, x24
	ldr	w0, [x23, 8]
	cmp	w0, w1
	bcc	.L1192
.L1200:
	ldrh	w0, [x19, #:lo12:.LANCHOR52]
	b	.L1201
.L1192:
	add	x1, x29, 108
	mov	w2, 0
	bl	log2phys
	ldr	w0, [x28, x24]
	ldr	w1, [x29, 108]
	cmp	w0, w1
	bne	.L1194
	lsr	w0, w0, 10
	bl	P2V_block_in_plane
	mov	w24, w0
	ldr	w0, [x23, 8]
	mov	w2, 1
	add	x1, x23, 4
	bl	log2phys
	mov	w0, w24
.L1201:
	bl	decrement_vpc_count
	b	.L1193
.L1194:
	ldr	w0, [x23, 4]
	cmp	w1, w0
	bne	.L1200
.L1193:
	add	w21, w21, 1
	and	w21, w21, 65535
	b	.L1191
.L1196:
	bl	INSERT_FREE_LIST
	b	.L1197
	.size	FtlGcFreeTempBlock, .-FtlGcFreeTempBlock
	.section	.text.FtlGcPageRecovery,"ax",@progbits
	.align	2
	.global	FtlGcPageRecovery
	.type	FtlGcPageRecovery, %function
FtlGcPageRecovery:
	stp	x29, x30, [sp, -32]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	adrp	x20, .LANCHOR18
	adrp	x19, .LANCHOR52
	add	x19, x19, :lo12:.LANCHOR52
	ldrh	w1, [x20, #:lo12:.LANCHOR18]
	mov	x0, x19
	bl	FtlGcScanTempBlk
	ldrh	w1, [x19, 2]
	ldrh	w0, [x20, #:lo12:.LANCHOR18]
	cmp	w1, w0
	bcc	.L1202
	adrp	x0, .LANCHOR128
	add	x0, x0, :lo12:.LANCHOR128
	bl	FtlMapBlkWriteDump_data
	mov	w0, 0
	bl	FtlGcFreeTempBlock
	adrp	x0, .LANCHOR132
	str	wzr, [x0, #:lo12:.LANCHOR132]
.L1202:
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
	adrp	x0, .LANCHOR156
	add	x29, sp, 0
	str	x19, [sp, 16]
	adrp	x19, .LANCHOR50
	add	x19, x19, :lo12:.LANCHOR50
	str	wzr, [x0, #:lo12:.LANCHOR156]
	mov	x0, x19
	bl	FtlRecoverySuperblock
	mov	x0, x19
	adrp	x19, .LANCHOR51
	bl	FtlSlcSuperblockCheck
	add	x19, x19, :lo12:.LANCHOR51
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
	.section	.text.Ftl_gc_temp_data_write_back,"ax",@progbits
	.align	2
	.global	Ftl_gc_temp_data_write_back
	.type	Ftl_gc_temp_data_write_back, %function
Ftl_gc_temp_data_write_back:
	stp	x29, x30, [sp, -32]!
	mov	w3, 0
	mov	w2, 0
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	adrp	x19, .LANCHOR61
	adrp	x20, .LANCHOR103
	ldr	w1, [x19, #:lo12:.LANCHOR61]
	add	x19, x19, :lo12:.LANCHOR61
	ldr	x0, [x20, #:lo12:.LANCHOR103]
	bl	FlashProgPages
	mov	w11, 0
.L1208:
	ldr	w1, [x19]
	cmp	w11, w1
	bcc	.L1211
	ldr	x0, [x20, #:lo12:.LANCHOR103]
	bl	FtlGcBufFree
	str	wzr, [x19]
	adrp	x0, .LANCHOR52+4
	ldrh	w0, [x0, #:lo12:.LANCHOR52+4]
	cbnz	w0, .L1213
	mov	w0, 1
	bl	FtlGcFreeTempBlock
	mov	w0, 1
.L1207:
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
.L1211:
	ldr	x2, [x20, #:lo12:.LANCHOR103]
	ubfiz	x0, x11, 5, 16
	add	x1, x2, x0
	ldr	w2, [x2, x0]
	ldr	x3, [x1, 16]
	cmn	w2, #1
	bne	.L1209
.L1215:
	ldr	w1, [x1, 4]
	ldr	w0, [x3, 12]
	bl	FtlGcUpdatePage
	add	w11, w11, 1
	and	w11, w11, 65535
	b	.L1208
.L1209:
	ldr	w2, [x3, 8]
	b	.L1215
.L1213:
	mov	w0, 0
	b	.L1207
	.size	Ftl_gc_temp_data_write_back, .-Ftl_gc_temp_data_write_back
	.section	.text.Ftl_get_new_temp_ppa,"ax",@progbits
	.align	2
	.global	Ftl_get_new_temp_ppa
	.type	Ftl_get_new_temp_ppa, %function
Ftl_get_new_temp_ppa:
	stp	x29, x30, [sp, -32]!
	adrp	x0, .LANCHOR52
	mov	w2, 65535
	add	x29, sp, 0
	str	x19, [sp, 16]
	mov	x19, x0
	ldrh	w3, [x0, #:lo12:.LANCHOR52]
	cmp	w3, w2
	beq	.L1217
	add	x1, x0, :lo12:.LANCHOR52
	ldrh	w0, [x1, 4]
	cbnz	w0, .L1218
.L1217:
	mov	w0, 0
	bl	FtlGcFreeTempBlock
	add	x0, x19, :lo12:.LANCHOR52
	strb	wzr, [x0, 8]
	bl	allocate_data_superblock
	adrp	x0, .LANCHOR67
	strh	wzr, [x0, #:lo12:.LANCHOR67]
	adrp	x0, .LANCHOR69
	strh	wzr, [x0, #:lo12:.LANCHOR69]
	bl	l2p_flush
	mov	w0, 0
	bl	FtlEctTblFlush
	bl	FtlVpcTblFlush
.L1218:
	add	x0, x19, :lo12:.LANCHOR52
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 32
	b	get_new_active_ppa
	.size	Ftl_get_new_temp_ppa, .-Ftl_get_new_temp_ppa
	.section	.text.rk_ftl_garbage_collect,"ax",@progbits
	.align	2
	.global	rk_ftl_garbage_collect
	.type	rk_ftl_garbage_collect, %function
rk_ftl_garbage_collect:
	stp	x29, x30, [sp, -176]!
	add	x29, sp, 0
	stp	x21, x22, [sp, 32]
	adrp	x21, .LANCHOR93
	stp	x19, x20, [sp, 16]
	ldr	w1, [x21, #:lo12:.LANCHOR93]
	stp	x23, x24, [sp, 48]
	stp	x25, x26, [sp, 64]
	stp	x27, x28, [sp, 80]
	cbnz	w1, .L1277
	adrp	x1, .LANCHOR43
	ldrh	w1, [x1, #:lo12:.LANCHOR43]
	cmp	w1, 47
	bls	.L1277
	adrp	x1, .LANCHOR72
	mov	w4, 65535
	ldrh	w3, [x1, #:lo12:.LANCHOR72]
	cmp	w3, w4
	beq	.L1222
	adrp	x2, .LANCHOR71
	ldrh	w5, [x2, #:lo12:.LANCHOR71]
	cmp	w5, w4
	bne	.L1222
	strh	w3, [x2, #:lo12:.LANCHOR71]
	mov	w2, -1
	strh	w2, [x1, #:lo12:.LANCHOR72]
.L1222:
	cbnz	w0, .L1278
	adrp	x1, .LANCHOR47
	ldrh	w1, [x1, #:lo12:.LANCHOR47]
	cmp	w1, 24
	bhi	.L1279
	adrp	x2, .LANCHOR18
	cmp	w1, 16
	ldrh	w20, [x2, #:lo12:.LANCHOR18]
	bls	.L1225
	lsr	w20, w20, 5
.L1224:
	adrp	x2, .LANCHOR99
	ldrh	w3, [x2, #:lo12:.LANCHOR99]
	cmp	w3, w1
	mov	x3, x2
	bcs	.L1228
	adrp	x1, .LANCHOR52
	mov	w4, 65535
	ldrh	w1, [x1, #:lo12:.LANCHOR52]
	cmp	w1, w4
	bne	.L1229
	adrp	x4, .LANCHOR71
	ldrh	w4, [x4, #:lo12:.LANCHOR71]
	cmp	w4, w1
	bne	.L1229
	adrp	x0, .LANCHOR171
	ldrh	w0, [x0, #:lo12:.LANCHOR171]
	cbnz	w0, .L1230
	adrp	x1, .LANCHOR151
	adrp	x4, .LANCHOR58
	ldr	w1, [x1, #:lo12:.LANCHOR151]
	ldr	w4, [x4, #:lo12:.LANCHOR58]
	add	w1, w1, w1, lsl 1
	cmp	w4, w1, lsr 2
	bcs	.L1231
.L1230:
	adrp	x1, .LANCHOR170
	ldrh	w1, [x1, #:lo12:.LANCHOR170]
	add	w1, w1, w1, lsl 1
	asr	w1, w1, 2
	strh	w1, [x3, #:lo12:.LANCHOR99]
.L1232:
	adrp	x1, .LANCHOR94
	str	wzr, [x1, #:lo12:.LANCHOR94]
.L1220:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 176
	ret
.L1225:
	cmp	w1, 12
	bls	.L1226
	lsr	w20, w20, 4
	b	.L1224
.L1226:
	cmp	w1, 8
	bls	.L1224
	lsr	w20, w20, 2
	b	.L1224
.L1279:
	mov	w20, 1
	b	.L1224
.L1231:
	mov	w1, 18
	strh	w1, [x2, #:lo12:.LANCHOR99]
	b	.L1232
.L1229:
	adrp	x1, .LANCHOR170
	ldrh	w1, [x1, #:lo12:.LANCHOR170]
	add	w1, w1, w1, lsl 1
	asr	w1, w1, 2
	strh	w1, [x3, #:lo12:.LANCHOR99]
.L1228:
	adrp	x1, .LANCHOR73
	ldrh	w1, [x1, #:lo12:.LANCHOR73]
	cbz	w1, .L1223
	add	w20, w20, 32
	and	w20, w20, 65535
.L1223:
	adrp	x19, .LANCHOR144
	str	w0, [x29, 152]
	mov	w0, 65535
	ldrh	w2, [x19, #:lo12:.LANCHOR144]
	cmp	w2, w0
	bne	.L1235
	adrp	x0, .LANCHOR71
	ldrh	w1, [x0, #:lo12:.LANCHOR71]
	cmp	w1, w2
	beq	.L1236
	adrp	x2, .LANCHOR41
	ubfiz	x1, x1, 1, 16
	ldr	x2, [x2, #:lo12:.LANCHOR41]
	ldrh	w1, [x2, x1]
	cbnz	w1, .L1237
	mov	w1, -1
	strh	w1, [x0, #:lo12:.LANCHOR71]
.L1237:
	ldrh	w1, [x0, #:lo12:.LANCHOR71]
	strh	w1, [x19, #:lo12:.LANCHOR144]
	mov	w1, -1
	strh	w1, [x0, #:lo12:.LANCHOR71]
.L1236:
	add	x0, x19, :lo12:.LANCHOR144
	mov	w1, 65535
	strb	wzr, [x0, 8]
	ldrh	w0, [x19, #:lo12:.LANCHOR144]
	cmp	w0, w1
	beq	.L1235
	bl	IsBlkInGcList
	cbz	w0, .L1239
	mov	w0, -1
	strh	w0, [x19, #:lo12:.LANCHOR144]
.L1239:
	ldrh	w1, [x19, #:lo12:.LANCHOR144]
	mov	w0, 65535
	add	x22, x19, :lo12:.LANCHOR144
	cmp	w1, w0
	beq	.L1235
	mov	x0, x22
	bl	make_superblock
	adrp	x0, .LANCHOR172
	ldrh	w1, [x19, #:lo12:.LANCHOR144]
	strh	wzr, [x22, 2]
	strh	wzr, [x0, #:lo12:.LANCHOR172]
	adrp	x0, .LANCHOR41
	strb	wzr, [x22, 6]
	ldr	x0, [x0, #:lo12:.LANCHOR41]
	ldrh	w1, [x0, x1, lsl 1]
	adrp	x0, .LANCHOR173
	strh	w1, [x0, #:lo12:.LANCHOR173]
.L1235:
	adrp	x1, .LANCHOR50
	ldrh	w0, [x19, #:lo12:.LANCHOR144]
	str	x1, [x29, 128]
	ldrh	w2, [x1, #:lo12:.LANCHOR50]
	cmp	w2, w0
	beq	.L1240
	adrp	x1, .LANCHOR51
	ldrh	w1, [x1, #:lo12:.LANCHOR51]
	cmp	w1, w0
	beq	.L1240
	adrp	x1, .LANCHOR52
	ldrh	w1, [x1, #:lo12:.LANCHOR52]
	cmp	w1, w0
	bne	.L1241
.L1240:
	mov	w0, -1
	strh	w0, [x19, #:lo12:.LANCHOR144]
.L1241:
	adrp	x25, .LANCHOR101
	add	x26, x25, :lo12:.LANCHOR101
.L1275:
	ldrh	w1, [x19, #:lo12:.LANCHOR144]
	mov	w0, 65535
	cmp	w1, w0
	bne	.L1242
	adrp	x0, .LANCHOR94
	adrp	x22, .LANCHOR18
	add	x22, x22, :lo12:.LANCHOR18
	str	wzr, [x0, #:lo12:.LANCHOR94]
.L1243:
	ldrh	w5, [x25, #:lo12:.LANCHOR101]
	add	x7, x25, :lo12:.LANCHOR101
	mov	w0, w5
	bl	List_get_gc_head_node
	and	w6, w0, 65535
	strh	w6, [x19, #:lo12:.LANCHOR144]
	mov	w0, 65535
	cmp	w6, w0
	bne	.L1244
	strh	wzr, [x7]
	mov	w0, 8
	b	.L1220
.L1278:
	mov	w20, 1
	b	.L1223
.L1244:
	mov	w0, w6
	bl	IsBlkInGcList
	add	w5, w5, 1
	cbz	w0, .L1245
	strh	w5, [x25, #:lo12:.LANCHOR101]
	b	.L1243
.L1245:
	adrp	x23, .LANCHOR41
	adrp	x4, .LANCHOR2
	ldrh	w0, [x22]
	ubfiz	x1, x6, 1, 16
	ldr	x2, [x23, #:lo12:.LANCHOR41]
	and	w5, w5, 65535
	ldrh	w4, [x4, #:lo12:.LANCHOR2]
	strh	w5, [x25, #:lo12:.LANCHOR101]
	ldrh	w3, [x2, x1]
	mul	w0, w0, w4
	cmp	w3, w0, asr 1
	bgt	.L1247
	cmp	w5, 48
	bls	.L1248
	cmp	w3, 8
	bls	.L1248
	adrp	x3, .LANCHOR67
	ldrh	w3, [x3, #:lo12:.LANCHOR67]
	cmp	w3, 35
	bhi	.L1248
.L1247:
	strh	wzr, [x26]
.L1248:
	ldrh	w1, [x2, x1]
	cmp	w0, w1
	bgt	.L1249
	ldrh	w0, [x26]
	cmp	w0, 3
	bhi	.L1249
	mov	w0, -1
	strh	wzr, [x26]
	strh	w0, [x19, #:lo12:.LANCHOR144]
.L1308:
	adrp	x0, .LANCHOR171
	ldrh	w0, [x0, #:lo12:.LANCHOR171]
	b	.L1220
.L1249:
	cbnz	w1, .L1250
	mov	w0, -1
	bl	decrement_vpc_count
	ldrh	w0, [x26]
	add	w0, w0, 1
	strh	w0, [x26]
	b	.L1243
.L1250:
	add	x0, x19, :lo12:.LANCHOR144
	strb	wzr, [x0, 8]
	ldr	x0, [x29, 128]
	ldrh	w0, [x0, #:lo12:.LANCHOR50]
	cmp	w0, w6
	bne	.L1251
	adrp	x1, .LANCHOR174
	adrp	x0, .LC1
	mov	w2, 717
	add	x1, x1, :lo12:.LANCHOR174
	add	x0, x0, :lo12:.LC1
	bl	printf
.L1251:
	adrp	x0, .LANCHOR51
	ldrh	w1, [x19, #:lo12:.LANCHOR144]
	ldrh	w0, [x0, #:lo12:.LANCHOR51]
	cmp	w1, w0
	bne	.L1252
	adrp	x1, .LANCHOR174
	adrp	x0, .LC1
	mov	w2, 718
	add	x1, x1, :lo12:.LANCHOR174
	add	x0, x0, :lo12:.LC1
	bl	printf
.L1252:
	adrp	x0, .LANCHOR52
	ldrh	w1, [x19, #:lo12:.LANCHOR144]
	ldrh	w0, [x0, #:lo12:.LANCHOR52]
	cmp	w1, w0
	bne	.L1253
	adrp	x1, .LANCHOR174
	adrp	x0, .LC1
	mov	w2, 719
	add	x1, x1, :lo12:.LANCHOR174
	add	x0, x0, :lo12:.LC1
	bl	printf
.L1253:
	add	x22, x19, :lo12:.LANCHOR144
	mov	x0, x22
	bl	make_superblock
	adrp	x0, .LANCHOR172
	ldrh	w1, [x19, #:lo12:.LANCHOR144]
	strh	wzr, [x0, #:lo12:.LANCHOR172]
	ldr	x0, [x23, #:lo12:.LANCHOR41]
	ldrh	w1, [x0, x1, lsl 1]
	adrp	x0, .LANCHOR173
	strh	wzr, [x22, 2]
	strh	w1, [x0, #:lo12:.LANCHOR173]
	strb	wzr, [x22, 6]
.L1242:
	mov	w0, 1
	str	w0, [x21, #:lo12:.LANCHOR93]
	adrp	x0, .LANCHOR18
	str	x0, [x29, 120]
	ldrh	w1, [x0, #:lo12:.LANCHOR18]
	ldr	w0, [x29, 152]
	str	w1, [x29, 156]
	cbz	w0, .L1254
	adrp	x0, .LANCHOR2
	ldrh	w2, [x19, #:lo12:.LANCHOR144]
	ldrh	w0, [x0, #:lo12:.LANCHOR2]
	mul	w0, w0, w1
	adrp	x1, .LANCHOR41
	ldr	x1, [x1, #:lo12:.LANCHOR41]
	ldrh	w1, [x1, x2, lsl 1]
	sub	w0, w0, w1
	mov	w1, 4
	sdiv	w0, w0, w1
	add	w20, w20, w0
	and	w20, w20, 65535
.L1254:
	add	x0, x19, :lo12:.LANCHOR144
	ldr	w2, [x29, 156]
	ldrh	w0, [x0, 2]
	add	w1, w0, w20
	cmp	w1, w2
	ble	.L1255
	sub	w20, w2, w0
	and	w20, w20, 65535
.L1255:
	adrp	x0, .LANCHOR172
	mov	w28, 0
	add	x0, x0, :lo12:.LANCHOR172
	str	x0, [x29, 144]
.L1256:
	cmp	w20, w28, uxth
	bls	.L1264
	add	x1, x19, :lo12:.LANCHOR144
	adrp	x0, .LANCHOR2
	adrp	x23, .LANCHOR65
	add	x1, x1, 16
	ldrh	w7, [x0, #:lo12:.LANCHOR2]
	mov	w22, 0
	ldrh	w4, [x1, -14]
	mov	w2, 0
	ldr	x0, [x23, #:lo12:.LANCHOR65]
	mov	w6, 65535
	add	w4, w4, w28
	b	.L1265
.L1258:
	ldrh	w3, [x1]
	cmp	w3, w6
	beq	.L1257
	ubfiz	x5, x22, 5, 16
	add	w22, w22, 1
	add	x5, x0, x5
	and	w22, w22, 65535
	orr	w3, w4, w3, lsl 10
	str	w3, [x5, 4]
.L1257:
	add	w2, w2, 1
	add	x1, x1, 2
	and	w2, w2, 65535
.L1265:
	cmp	w2, w7
	bne	.L1258
	add	x1, x19, :lo12:.LANCHOR144
	adrp	x24, .LANCHOR61
	add	x24, x24, :lo12:.LANCHOR61
	ldrb	w2, [x1, 8]
	mov	w1, w22
	bl	FlashReadPages
	ubfiz	x0, x22, 5, 16
	mov	x22, 0
	str	x0, [x29, 136]
.L1259:
	ldr	x0, [x29, 136]
	cmp	x22, x0
	bne	.L1263
	add	w28, w28, 1
	b	.L1256
.L1263:
	ldr	x0, [x23, #:lo12:.LANCHOR65]
	add	x1, x0, x22
	ldr	w0, [x0, x22]
	cmn	w0, #1
	beq	.L1260
	ldr	x27, [x1, 16]
	mov	w0, 61589
	ldrh	w1, [x27]
	cmp	w1, w0
	bne	.L1260
	ldr	w4, [x27, 8]
	cmn	w4, #1
	bne	.L1261
	str	w4, [x29, 112]
	mov	w2, 753
	adrp	x1, .LANCHOR174
	adrp	x0, .LC1
	add	x1, x1, :lo12:.LANCHOR174
	add	x0, x0, :lo12:.LC1
	bl	printf
	ldr	w4, [x29, 112]
.L1261:
	mov	w2, 0
	add	x1, x29, 168
	mov	w0, w4
	bl	log2phys
	ldr	x0, [x23, #:lo12:.LANCHOR65]
	ldr	w1, [x29, 168]
	add	x0, x0, x22
	ldr	w2, [x0, 4]
	cmp	w2, w1
	bne	.L1260
	ldr	x1, [x29, 144]
	adrp	x4, .LANCHOR103
	ldr	x2, [x29, 144]
	ldr	w0, [x0, 24]
	ldrh	w1, [x1]
	add	w1, w1, 1
	strh	w1, [x2]
	ldr	x2, [x4, #:lo12:.LANCHOR103]
	ldr	w1, [x24]
	add	x1, x2, x1, lsl 5
	stp	x4, x1, [x29, 104]
	str	w0, [x1, 24]
	bl	Ftl_get_new_temp_ppa
	ldp	x4, x1, [x29, 104]
	ldr	x2, [x4, #:lo12:.LANCHOR103]
	str	w0, [x1, 4]
	ldr	w1, [x24]
	ubfiz	x0, x1, 5, 32
	add	w1, w1, 1
	add	x2, x2, x0
	ldr	x0, [x23, #:lo12:.LANCHOR65]
	add	x0, x0, x22
	ldr	x4, [x0, 8]
	str	x4, [x2, 8]
	ldr	x4, [x0, 16]
	str	x4, [x2, 16]
	ldr	w2, [x29, 168]
	str	w2, [x27, 12]
	adrp	x2, .LANCHOR52
	add	x11, x2, :lo12:.LANCHOR52
	ldrh	w2, [x2, #:lo12:.LANCHOR52]
	strh	w2, [x27, 2]
	adrp	x2, .LANCHOR82
	str	w1, [x24]
	mov	w1, 1
	ldr	w2, [x2, #:lo12:.LANCHOR82]
	str	w2, [x27, 4]
	bl	FtlGcBufAlloc
	ldrb	w1, [x11, 7]
	ldr	w0, [x24]
	cmp	w1, w0
	beq	.L1262
	ldrh	w0, [x11, 4]
	cbnz	w0, .L1260
.L1262:
	bl	Ftl_gc_temp_data_write_back
	cbz	w0, .L1260
	add	x0, x19, :lo12:.LANCHOR144
	mov	w1, -1
	str	wzr, [x21, #:lo12:.LANCHOR93]
	strh	w1, [x19, #:lo12:.LANCHOR144]
	strh	wzr, [x0, 2]
	b	.L1308
.L1260:
	add	x22, x22, 32
	b	.L1259
.L1264:
	add	x1, x19, :lo12:.LANCHOR144
	ldrh	w0, [x1, 2]
	add	w20, w20, w0
	ldr	w0, [x29, 156]
	and	w20, w20, 65535
	strh	w20, [x1, 2]
	cmp	w0, w20
	bhi	.L1266
	adrp	x0, .LANCHOR61
	ldr	w0, [x0, #:lo12:.LANCHOR61]
	cbz	w0, .L1267
	bl	Ftl_gc_temp_data_write_back
	cbz	w0, .L1267
	str	wzr, [x21, #:lo12:.LANCHOR93]
	b	.L1308
.L1267:
	adrp	x0, .LANCHOR172
	ldrh	w0, [x0, #:lo12:.LANCHOR172]
	cbnz	w0, .L1268
	ldrh	w1, [x19, #:lo12:.LANCHOR144]
	adrp	x20, .LANCHOR41
	add	x0, x19, :lo12:.LANCHOR144
	ldr	x3, [x20, #:lo12:.LANCHOR41]
	ubfiz	x2, x1, 1, 16
	ldrh	w4, [x3, x2]
	cbz	w4, .L1268
	adrp	x2, .LANCHOR173
	adrp	x22, .LANCHOR151
	add	x23, x22, :lo12:.LANCHOR151
	mov	w24, 0
	ldrh	w5, [x2, #:lo12:.LANCHOR173]
	mov	w3, 0
	ldrh	w2, [x0, 2]
	adrp	x0, .LC42
	add	x0, x0, :lo12:.LC42
	bl	printf
.L1269:
	ldr	w0, [x23]
	cmp	w24, w0
	bcs	.L1271
	mov	w2, 0
	add	x1, x29, 172
	mov	w0, w24
	bl	log2phys
	ldr	w3, [x29, 172]
	cmn	w3, #1
	beq	.L1270
	lsr	w0, w3, 10
	bl	P2V_block_in_plane
	ldrh	w1, [x19, #:lo12:.LANCHOR144]
	cmp	w1, w0, uxth
	bne	.L1270
	adrp	x0, .LC43
	mov	w2, w3
	mov	w1, w24
	add	x0, x0, :lo12:.LC43
	bl	printf
.L1271:
	ldr	w0, [x22, #:lo12:.LANCHOR151]
	cmp	w24, w0
	bcc	.L1268
	ldrh	w1, [x19, #:lo12:.LANCHOR144]
	ldr	x0, [x20, #:lo12:.LANCHOR41]
	strh	wzr, [x0, x1, lsl 1]
	ldrh	w0, [x19, #:lo12:.LANCHOR144]
	bl	update_vpc_list
	bl	l2p_flush
	bl	FtlVpcTblFlush
.L1268:
	mov	w0, -1
	strh	w0, [x19, #:lo12:.LANCHOR144]
.L1266:
	adrp	x0, .LANCHOR47
	str	wzr, [x21, #:lo12:.LANCHOR93]
	ldrh	w0, [x0, #:lo12:.LANCHOR47]
	cmp	w0, 2
	bhi	.L1274
	ldr	x0, [x29, 120]
	ldrh	w20, [x0, #:lo12:.LANCHOR18]
	b	.L1275
.L1270:
	add	w24, w24, 1
	b	.L1269
.L1274:
	add	w0, w0, 1
	b	.L1220
.L1277:
	mov	w0, 0
	b	.L1220
	.size	rk_ftl_garbage_collect, .-rk_ftl_garbage_collect
	.section	.text.FtlRead,"ax",@progbits
	.align	2
	.global	FtlRead
	.type	FtlRead, %function
FtlRead:
	stp	x29, x30, [sp, -176]!
	and	w0, w0, 255
	cmp	w0, 16
	add	x29, sp, 0
	stp	x21, x22, [sp, 32]
	mov	x22, x3
	stp	x23, x24, [sp, 48]
	mov	w24, w2
	stp	x27, x28, [sp, 80]
	mov	w27, w1
	stp	x19, x20, [sp, 16]
	stp	x25, x26, [sp, 64]
	bne	.L1310
	mov	x2, x3
	mov	w1, w24
	add	w0, w27, 256
	bl	FtlVendorPartRead
	mov	w19, w0
.L1309:
	mov	w0, w19
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 176
	ret
.L1310:
	adrp	x0, .LANCHOR33
	ldr	w0, [x0, #:lo12:.LANCHOR33]
	cmp	w1, w0
	bcs	.L1333
	cmp	w2, w0
	bhi	.L1333
	add	w1, w1, w2
	str	w1, [x29, 136]
	cmp	w0, w1
	bcc	.L1333
	adrp	x0, .LANCHOR165
	ldr	w19, [x0, #:lo12:.LANCHOR165]
	cmn	w19, #1
	beq	.L1309
	adrp	x21, .LANCHOR11
	adrp	x25, .LANCHOR134
	add	x25, x25, :lo12:.LANCHOR134
	mov	w26, 0
	ldrh	w0, [x21, #:lo12:.LANCHOR11]
	mov	w19, 0
	adrp	x28, .LANCHOR102
	stp	wzr, wzr, [x29, 140]
	udiv	w1, w27, w0
	stp	wzr, w1, [x29, 148]
	add	w1, w27, w2
	sub	w23, w1, #1
	adrp	x1, .LANCHOR162
	ldr	w20, [x29, 152]
	udiv	w23, w23, w0
	ldr	w0, [x29, 152]
	sub	w0, w23, w0
	add	w0, w0, 1
	str	w0, [x29, 156]
	ldr	w0, [x1, #:lo12:.LANCHOR162]
	add	w0, w0, w2
	str	w0, [x1, #:lo12:.LANCHOR162]
	adrp	x1, .LANCHOR88
	ldr	w2, [x29, 156]
	ldr	w0, [x1, #:lo12:.LANCHOR88]
	add	w0, w0, w2
	str	w0, [x1, #:lo12:.LANCHOR88]
.L1312:
	ldr	w0, [x29, 156]
	cbnz	w0, .L1329
	adrp	x0, .LANCHOR73
	ldrh	w0, [x0, #:lo12:.LANCHOR73]
	cbnz	w0, .L1330
	adrp	x0, .LANCHOR47
	ldrh	w0, [x0, #:lo12:.LANCHOR47]
	cmp	w0, 31
	bhi	.L1309
.L1330:
	mov	w1, 1
	mov	w0, 0
	bl	rk_ftl_garbage_collect
	b	.L1309
.L1329:
	add	x1, x29, 172
	mov	w2, 0
	mov	w0, w20
	bl	log2phys
	ldr	w1, [x29, 172]
	cmn	w1, #1
	bne	.L1313
	add	x6, x21, :lo12:.LANCHOR11
	mov	w5, 0
.L1314:
	ldrh	w0, [x6]
	cmp	w5, w0
	bcc	.L1316
.L1317:
	ldr	w0, [x29, 156]
	add	w20, w20, 1
	subs	w0, w0, #1
	str	w0, [x29, 156]
	beq	.L1321
	adrp	x0, .LANCHOR2
	ldrh	w0, [x0, #:lo12:.LANCHOR2]
	cmp	w26, w0, lsl 2
	bne	.L1312
.L1321:
	cbz	w26, .L1312
	ldr	x0, [x28, #:lo12:.LANCHOR102]
	mov	w1, w26
	mov	w2, 0
	bl	FlashReadPages
	ldr	w0, [x29, 140]
	lsl	w0, w0, 9
	str	w0, [x29, 116]
	ldr	w0, [x29, 148]
	lsl	w0, w0, 9
	str	x0, [x29, 128]
	ldr	w0, [x29, 144]
	lsl	w0, w0, 9
	str	w0, [x29, 120]
	ubfiz	x0, x26, 5, 32
	mov	x26, 0
	str	x0, [x29, 104]
	add	x0, x21, :lo12:.LANCHOR11
	str	x0, [x29, 96]
.L1328:
	ldr	x0, [x28, #:lo12:.LANCHOR102]
	ldr	w2, [x29, 152]
	add	x0, x0, x26
	ldr	w1, [x0, 24]
	cmp	w2, w1
	bne	.L1323
	ldr	x1, [x0, 8]
	adrp	x0, .LANCHOR108
	ldr	x0, [x0, #:lo12:.LANCHOR108]
	cmp	x1, x0
	bne	.L1324
	ldr	x0, [x29, 128]
	ldr	w2, [x29, 120]
	add	x1, x1, x0
	mov	x0, x22
.L1344:
	bl	ftl_memcpy
.L1324:
	ldr	x0, [x28, #:lo12:.LANCHOR102]
	add	x0, x0, x26
	ldr	x1, [x0, 16]
	ldr	w2, [x0, 24]
	ldr	w1, [x1, 8]
	cmp	w2, w1
	beq	.L1325
	ldr	w1, [x25, 72]
	add	w1, w1, 1
	str	w1, [x25, 72]
.L1325:
	ldr	w1, [x0]
	cmn	w1, #1
	bne	.L1326
	ldr	w0, [x25, 72]
	mov	w19, w1
	add	w0, w0, 1
	str	w0, [x25, 72]
.L1327:
	ldr	x0, [x29, 104]
	add	x26, x26, 32
	cmp	x0, x26
	bne	.L1328
	mov	w26, 0
	b	.L1312
.L1316:
	madd	w0, w20, w0, w5
	cmp	w27, w0
	bhi	.L1315
	ldr	w1, [x29, 136]
	cmp	w1, w0
	bls	.L1315
	sub	w0, w0, w27
	str	x6, [x29, 120]
	lsl	w0, w0, 9
	str	w5, [x29, 128]
	mov	w2, 512
	mov	w1, 0
	add	x0, x22, x0
	bl	ftl_memset
	ldr	w5, [x29, 128]
	ldr	x6, [x29, 120]
.L1315:
	add	w5, w5, 1
	b	.L1314
.L1313:
	ldr	x2, [x28, #:lo12:.LANCHOR102]
	ubfiz	x0, x26, 5, 32
	add	x0, x2, x0
	str	w1, [x0, 4]
	ldr	w1, [x29, 152]
	cmp	w20, w1
	bne	.L1318
	adrp	x1, .LANCHOR108
	ldr	x1, [x1, #:lo12:.LANCHOR108]
	str	x1, [x0, 8]
	ldrh	w1, [x21, #:lo12:.LANCHOR11]
	udiv	w2, w27, w1
	msub	w2, w2, w1, w27
	str	w2, [x29, 148]
	sub	w2, w1, w2
	cmp	w24, w2
	csel	w2, w24, w2, ls
	str	w2, [x29, 144]
	cmp	w1, w2
	bne	.L1319
	str	x22, [x0, 8]
.L1319:
	adrp	x1, .LANCHOR23
	adrp	x2, .LANCHOR114
	str	w20, [x0, 24]
	ldrh	w1, [x1, #:lo12:.LANCHOR23]
	ldr	x2, [x2, #:lo12:.LANCHOR114]
	mul	w1, w1, w26
	add	w26, w26, 1
	and	x1, x1, 4294967292
	add	x1, x2, x1
	str	x1, [x0, 16]
	b	.L1317
.L1318:
	cmp	w20, w23
	bne	.L1320
	ldrh	w2, [x21, #:lo12:.LANCHOR11]
	adrp	x1, .LANCHOR109
	ldr	w3, [x29, 136]
	ldr	x1, [x1, #:lo12:.LANCHOR109]
	str	x1, [x0, 8]
	mul	w1, w20, w2
	sub	w3, w3, w1
	str	w3, [x29, 140]
	cmp	w2, w3
	bne	.L1319
.L1343:
	sub	w1, w1, w27
	lsl	w1, w1, 9
	add	x1, x22, x1
	str	x1, [x0, 8]
	b	.L1319
.L1320:
	ldrh	w1, [x21, #:lo12:.LANCHOR11]
	mul	w1, w1, w20
	b	.L1343
.L1323:
	cmp	w23, w1
	bne	.L1324
	ldr	x1, [x0, 8]
	adrp	x0, .LANCHOR109
	ldr	x0, [x0, #:lo12:.LANCHOR109]
	cmp	x1, x0
	bne	.L1324
	ldr	x0, [x29, 96]
	ldr	w2, [x29, 116]
	ldrh	w0, [x0]
	mul	w0, w0, w23
	sub	w0, w0, w27
	lsl	w0, w0, 9
	add	x0, x22, x0
	b	.L1344
.L1326:
	cmp	w1, 256
	bne	.L1327
	ldr	w0, [x0, 4]
	lsr	w0, w0, 10
	bl	P2V_block_in_plane
	bl	FtlGcRefreshBlock
	b	.L1327
.L1333:
	mov	w19, -1
	b	.L1309
	.size	FtlRead, .-FtlRead
	.section	.text.sftl_read,"ax",@progbits
	.align	2
	.global	sftl_read
	.type	sftl_read, %function
sftl_read:
	mov	x3, x2
	mov	w2, w1
	mov	w1, w0
	mov	w0, 0
	b	FtlRead
	.size	sftl_read, .-sftl_read
	.section	.text.FtlWrite,"ax",@progbits
	.align	2
	.global	FtlWrite
	.type	FtlWrite, %function
FtlWrite:
	stp	x29, x30, [sp, -224]!
	and	w0, w0, 255
	cmp	w0, 16
	add	x29, sp, 0
	stp	x21, x22, [sp, 32]
	mov	w22, w1
	stp	x25, x26, [sp, 64]
	mov	w26, w2
	stp	x27, x28, [sp, 80]
	mov	x27, x3
	stp	x19, x20, [sp, 16]
	stp	x23, x24, [sp, 48]
	bne	.L1347
	mov	x2, x3
	mov	w1, w26
	add	w0, w22, 256
	bl	FtlVendorPartWrite
.L1346:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 224
	ret
.L1347:
	adrp	x0, .LANCHOR33
	ldr	w0, [x0, #:lo12:.LANCHOR33]
	cmp	w1, w0
	bcs	.L1381
	cmp	w2, w0
	bhi	.L1381
	add	w1, w1, w2
	str	w1, [x29, 136]
	cmp	w0, w1
	bcc	.L1381
	adrp	x0, .LANCHOR165
	ldr	w0, [x0, #:lo12:.LANCHOR165]
	cmn	w0, #1
	beq	.L1346
	adrp	x0, .LANCHOR175
	mov	w1, 2048
	add	w2, w22, w2
	str	w1, [x0, #:lo12:.LANCHOR175]
	adrp	x1, .LANCHOR11
	sub	w2, w2, #1
	str	x1, [x29, 160]
	ldrh	w0, [x1, #:lo12:.LANCHOR11]
	udiv	w25, w22, w0
	udiv	w0, w2, w0
	adrp	x2, .LANCHOR161
	mov	w19, w25
	str	w0, [x29, 144]
	sub	w0, w0, w25
	add	w24, w0, 1
	str	w0, [x29, 140]
	ldr	w0, [x2, #:lo12:.LANCHOR161]
	add	w0, w0, w26
	str	w0, [x2, #:lo12:.LANCHOR161]
	adrp	x2, .LANCHOR84
	ldr	w0, [x2, #:lo12:.LANCHOR84]
	add	w0, w0, w24
	str	w0, [x2, #:lo12:.LANCHOR84]
	adrp	x0, .LANCHOR50
	add	x20, x0, :lo12:.LANCHOR50
.L1349:
	cbnz	w24, .L1374
	ldr	w1, [x29, 140]
	mov	w0, 0
	bl	rk_ftl_garbage_collect
	adrp	x0, .LANCHOR47
	mov	x22, x0
	ldrh	w1, [x0, #:lo12:.LANCHOR47]
	cmp	w1, 5
	bls	.L1375
.L1377:
	mov	w0, 0
	b	.L1346
.L1374:
	adrp	x0, .LANCHOR50
	add	x0, x0, :lo12:.LANCHOR50
	adrp	x1, .LANCHOR2
	str	x1, [x29, 112]
	ldrb	w2, [x0, 6]
	ldrh	w0, [x1, #:lo12:.LANCHOR2]
	cmp	w2, w0
	bcc	.L1350
	adrp	x1, .LANCHOR176
	adrp	x0, .LC1
	mov	w2, 1041
	add	x1, x1, :lo12:.LANCHOR176
	add	x0, x0, :lo12:.LC1
	bl	printf
.L1350:
	ldrh	w0, [x20, 4]
	cbnz	w0, .L1351
	mov	x0, x20
	bl	allocate_new_data_superblock
.L1351:
	ldrb	w0, [x20, 7]
	ldrh	w1, [x20, 4]
	lsl	w0, w0, 2
	cmp	w0, w1
	csel	w0, w0, w1, ls
	ldrb	w1, [x20, 6]
	cmp	w0, w24
	csel	w0, w0, w24, ls
	str	w0, [x29, 148]
	ldr	x0, [x29, 112]
	ldrh	w0, [x0, #:lo12:.LANCHOR2]
	cmp	w1, w0
	bcc	.L1352
	adrp	x1, .LANCHOR176
	adrp	x0, .LC1
	mov	w2, 1074
	add	x1, x1, :lo12:.LANCHOR176
	add	x0, x0, :lo12:.LC1
	bl	printf
.L1352:
	adrp	x0, .LANCHOR23
	add	x0, x0, :lo12:.LANCHOR23
	str	xzr, [x29, 168]
	str	x0, [x29, 104]
	adrp	x0, .LANCHOR22
	add	x0, x0, :lo12:.LANCHOR22
	str	x0, [x29, 96]
.L1353:
	ldr	w1, [x29, 148]
	adrp	x28, .LANCHOR104
	ldr	w23, [x29, 168]
	cmp	w23, w1
	bcc	.L1372
	mov	x23, x1
.L1354:
	ldr	x0, [x28, #:lo12:.LANCHOR104]
	mov	x3, x20
	mov	w2, 0
	mov	w1, w23
	bl	FtlProgPages
	cmp	w24, w23
	bcs	.L1373
	adrp	x1, .LANCHOR176
	adrp	x0, .LC1
	mov	w2, 1152
	add	x1, x1, :lo12:.LANCHOR176
	add	x0, x0, :lo12:.LC1
	bl	printf
.L1373:
	sub	w24, w24, w23
	b	.L1349
.L1372:
	ldrh	w0, [x20, 4]
	cbz	w0, .L1354
	add	x1, x29, 188
	mov	w2, 0
	mov	w0, w19
	bl	log2phys
	mov	x0, x20
	bl	get_new_active_ppa
	ldr	x1, [x29, 168]
	lsl	x21, x1, 5
	ldr	x1, [x28, #:lo12:.LANCHOR104]
	add	x1, x1, x21
	str	w0, [x1, 4]
	ldr	x0, [x29, 104]
	str	w19, [x1, 24]
	ldrh	w2, [x0]
	mul	w23, w23, w2
	and	x0, x23, 4294967292
	str	x0, [x29, 128]
	adrp	x0, .LANCHOR114
	ldr	x3, [x29, 128]
	ldr	x0, [x0, #:lo12:.LANCHOR114]
	str	x0, [x29, 120]
	add	x23, x0, x3
	str	x23, [x1, 16]
	mov	x0, x23
	mov	w1, 0
	bl	ftl_memset
	ldr	w0, [x29, 144]
	cmp	w19, w25
	ccmp	w19, w0, 4, ne
	bne	.L1355
	cmp	w19, w25
	ldr	x0, [x29, 160]
	bne	.L1356
	ldrh	w2, [x0, #:lo12:.LANCHOR11]
	udiv	w0, w22, w2
	msub	w0, w0, w2, w22
	str	w0, [x29, 152]
	sub	w2, w2, w0
	cmp	w2, w26
	csel	w0, w2, w26, ls
	str	w0, [x29, 156]
.L1357:
	ldr	x0, [x29, 160]
	ldr	w1, [x29, 156]
	ldrh	w0, [x0, #:lo12:.LANCHOR11]
	cmp	w1, w0
	ldr	x0, [x28, #:lo12:.LANCHOR104]
	bne	.L1358
	add	x21, x0, x21
	cmp	w19, w25
	bne	.L1359
	str	x27, [x21, 8]
.L1360:
	ldr	x0, [x29, 112]
	ldrb	w1, [x20, 6]
	ldrh	w0, [x0, #:lo12:.LANCHOR2]
	cmp	w1, w0
	bcc	.L1369
	adrp	x1, .LANCHOR176
	adrp	x0, .LC1
	mov	w2, 1143
	add	x1, x1, :lo12:.LANCHOR176
	add	x0, x0, :lo12:.LC1
	bl	printf
.L1369:
	ldp	x1, x2, [x29, 120]
	mov	w0, -3947
	strh	w0, [x1, x2]
	adrp	x1, .LANCHOR82
	ldr	w0, [x1, #:lo12:.LANCHOR82]
	stp	w0, w19, [x23, 4]
	add	w19, w19, 1
	add	w0, w0, 1
	cmn	w0, #1
	csel	w0, w0, wzr, ne
	str	w0, [x1, #:lo12:.LANCHOR82]
	ldr	w0, [x29, 188]
	str	w0, [x23, 12]
	ldrh	w0, [x20]
	strh	w0, [x23, 2]
	ldr	x0, [x29, 168]
	add	x0, x0, 1
	str	x0, [x29, 168]
	b	.L1353
.L1356:
	ldrh	w2, [x0, #:lo12:.LANCHOR11]
	ldr	w0, [x29, 136]
	msub	w2, w19, w2, w0
	and	w0, w2, 65535
	stp	wzr, w0, [x29, 152]
	b	.L1357
.L1359:
	ldr	w0, [x29, 156]
.L1389:
	mul	w0, w0, w19
	sub	w0, w0, w22
	lsl	w0, w0, 9
	add	x0, x27, x0
	str	x0, [x21, 8]
	b	.L1360
.L1358:
	add	x0, x0, x21
	cmp	w19, w25
	bne	.L1361
	adrp	x1, .LANCHOR108
	ldr	x1, [x1, #:lo12:.LANCHOR108]
.L1388:
	str	x1, [x0, 8]
	ldr	w0, [x29, 188]
	cmn	w0, #1
	beq	.L1363
	str	w0, [x29, 196]
	mov	w2, 0
	ldr	x0, [x28, #:lo12:.LANCHOR104]
	str	w19, [x29, 216]
	add	x0, x0, x21
	ldp	x1, x0, [x0, 8]
	stp	x1, x0, [x29, 200]
	mov	w1, 1
	add	x0, x29, 192
	bl	FlashReadPages
	ldr	w3, [x29, 192]
	cmn	w3, #1
	bne	.L1364
	adrp	x0, .LANCHOR134
	add	x0, x0, :lo12:.LANCHOR134
	mov	w2, w19
	ldr	w1, [x0, 72]
	add	w1, w1, 1
	str	w1, [x0, 72]
	ldr	w1, [x23, 8]
	adrp	x0, .LC44
	add	x0, x0, :lo12:.LC44
	bl	printf
.L1367:
	ldr	w0, [x29, 156]
	cmp	w19, w25
	lsl	w2, w0, 9
	bne	.L1368
	ldr	x0, [x28, #:lo12:.LANCHOR104]
	mov	x1, x27
	add	x21, x0, x21
	ldr	w0, [x29, 152]
	ldr	x3, [x21, 8]
	lsl	w0, w0, 9
	add	x0, x3, x0
.L1390:
	bl	ftl_memcpy
	b	.L1360
.L1361:
	adrp	x1, .LANCHOR109
	ldr	x1, [x1, #:lo12:.LANCHOR109]
	b	.L1388
.L1364:
	ldr	w1, [x23, 8]
	cmp	w19, w1
	beq	.L1366
	adrp	x0, .LANCHOR134
	add	x0, x0, :lo12:.LANCHOR134
	ldr	w2, [x0, 72]
	add	w2, w2, 1
	str	w2, [x0, 72]
	adrp	x0, .LC45
	mov	w2, w19
	add	x0, x0, :lo12:.LC45
	bl	printf
.L1366:
	ldr	w0, [x23, 8]
	cmp	w19, w0
	beq	.L1367
	mov	w2, 1128
	adrp	x1, .LANCHOR176
	adrp	x0, .LC1
	add	x1, x1, :lo12:.LANCHOR176
	add	x0, x0, :lo12:.LC1
	bl	printf
	b	.L1367
.L1363:
	ldr	x0, [x28, #:lo12:.LANCHOR104]
	ldr	x1, [x29, 96]
	add	x0, x0, x21
	ldrh	w2, [x1]
	mov	w1, 0
	ldr	x0, [x0, 8]
	bl	ftl_memset
	b	.L1367
.L1368:
	ldr	x0, [x29, 160]
	ldrh	w1, [x0, #:lo12:.LANCHOR11]
	ldr	x0, [x28, #:lo12:.LANCHOR104]
	add	x21, x0, x21
	mul	w1, w1, w19
	sub	w1, w1, w22
	ldr	x0, [x21, 8]
	lsl	w1, w1, 9
	add	x1, x27, x1
	b	.L1390
.L1355:
	ldr	x0, [x28, #:lo12:.LANCHOR104]
	add	x21, x0, x21
	ldr	x0, [x29, 160]
	ldrh	w0, [x0, #:lo12:.LANCHOR11]
	b	.L1389
.L1375:
	adrp	x23, .LANCHOR71
	adrp	x20, .LANCHOR100
	adrp	x21, .LANCHOR99
	add	x23, x23, :lo12:.LANCHOR71
	add	x20, x20, :lo12:.LANCHOR100
	add	x21, x21, :lo12:.LANCHOR99
	mov	w19, 256
.L1378:
	adrp	x0, .LANCHOR144
	mov	w1, 65535
	ldrh	w0, [x0, #:lo12:.LANCHOR144]
	cmp	w0, w1
	bne	.L1376
	ldrh	w1, [x23]
	cmp	w1, w0
	bne	.L1376
	mov	w0, 0
	bl	List_get_gc_head_node
	bl	FtlGcRefreshBlock
.L1376:
	mov	w0, 128
	mov	w1, 1
	strh	w0, [x20]
	strh	w0, [x21]
	mov	w0, w1
	bl	rk_ftl_garbage_collect
	mov	w1, 1
	mov	w0, 0
	bl	rk_ftl_garbage_collect
	ldrh	w0, [x22, #:lo12:.LANCHOR47]
	cmp	w0, 2
	bhi	.L1377
	subs	w19, w19, #1
	bne	.L1378
	b	.L1377
.L1381:
	mov	w0, -1
	b	.L1346
	.size	FtlWrite, .-FtlWrite
	.section	.text.sftl_gc,"ax",@progbits
	.align	2
	.global	sftl_gc
	.type	sftl_gc, %function
sftl_gc:
	mov	w1, 1
	mov	w0, w1
	b	rk_ftl_garbage_collect
	.size	sftl_gc, .-sftl_gc
	.section	.text.FtlLoadSysInfo,"ax",@progbits
	.align	2
	.global	FtlLoadSysInfo
	.type	FtlLoadSysInfo, %function
FtlLoadSysInfo:
	stp	x29, x30, [sp, -112]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	adrp	x19, .LANCHOR137
	stp	x21, x22, [sp, 32]
	add	x0, x19, :lo12:.LANCHOR137
	adrp	x22, .LANCHOR105
	stp	x25, x26, [sp, 64]
	adrp	x25, .LANCHOR113
	stp	x23, x24, [sp, 48]
	stp	x27, x28, [sp, 80]
	adrp	x23, .LANCHOR41
	ldr	x1, [x22, #:lo12:.LANCHOR105]
	adrp	x21, .LANCHOR4
	str	x1, [x0, 8]
	adrp	x20, .LANCHOR138
	ldr	x1, [x25, #:lo12:.LANCHOR113]
	str	x1, [x0, 16]
	ldr	x0, [x23, #:lo12:.LANCHOR41]
	mov	w1, 0
	ldrh	w2, [x21, #:lo12:.LANCHOR4]
	lsl	w2, w2, 1
	bl	ftl_memset
	ldrh	w0, [x20, #:lo12:.LANCHOR138]
	mov	w1, 65535
	cmp	w0, w1
	bne	.L1393
.L1404:
	mov	w0, -1
.L1392:
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 112
	ret
.L1393:
	add	x24, x20, :lo12:.LANCHOR138
	mov	w1, 1
	bl	FtlGetLastWrittenPage
	sxth	w28, w0
	add	w0, w0, 1
	adrp	x26, .LANCHOR22
	strh	w0, [x24, 2]
	adrp	x27, .LANCHOR177
	ldrsh	w24, [x20, #:lo12:.LANCHOR138]
	add	x26, x26, :lo12:.LANCHOR22
	add	x27, x27, :lo12:.LANCHOR177
.L1395:
	tbz	w28, #31, .L1401
	adrp	x1, .LANCHOR177
	adrp	x0, .LC1
	mov	w2, 1474
	add	x1, x1, :lo12:.LANCHOR177
	add	x0, x0, :lo12:.LC1
	bl	printf
.L1400:
	adrp	x1, .LANCHOR22
	ldrh	w0, [x21, #:lo12:.LANCHOR4]
	ldrh	w1, [x1, #:lo12:.LANCHOR22]
	add	x0, x0, 24
	cmp	x1, x0, lsl 1
	bcs	.L1403
	adrp	x1, .LANCHOR177
	adrp	x0, .LC1
	mov	w2, 1476
	add	x1, x1, :lo12:.LANCHOR177
	add	x0, x0, :lo12:.LC1
	bl	printf
.L1403:
	add	x24, x19, :lo12:.LANCHOR137
	adrp	x19, .LANCHOR38
	add	x22, x19, :lo12:.LANCHOR38
	mov	w2, 48
	mov	x0, x22
	ldr	x1, [x24, 8]
	bl	ftl_memcpy
	ldr	x0, [x23, #:lo12:.LANCHOR41]
	ldrh	w2, [x21, #:lo12:.LANCHOR4]
	ldr	x1, [x24, 8]
	lsl	w2, w2, 1
	add	x1, x1, 48
	bl	ftl_memcpy
	ldr	w1, [x19, #:lo12:.LANCHOR38]
	mov	w0, 19539
	movk	w0, 0x4654, lsl 16
	cmp	w1, w0
	bne	.L1404
	add	x20, x20, :lo12:.LANCHOR138
	adrp	x0, .LANCHOR9
	ldrh	w1, [x22, 8]
	ldrb	w2, [x22, 10]
	ldrh	w0, [x0, #:lo12:.LANCHOR9]
	strh	w1, [x20, 6]
	cmp	w2, w0
	bne	.L1404
	adrp	x0, .LANCHOR178
	adrp	x2, .LANCHOR151
	adrp	x3, .LANCHOR2
	str	w1, [x0, #:lo12:.LANCHOR178]
	adrp	x0, .LANCHOR18
	ldrh	w3, [x3, #:lo12:.LANCHOR2]
	ldrh	w0, [x0, #:lo12:.LANCHOR18]
	mul	w0, w0, w1
	str	w0, [x2, #:lo12:.LANCHOR151]
	adrp	x2, .LANCHOR11
	ldrh	w2, [x2, #:lo12:.LANCHOR11]
	mul	w0, w2, w0
	adrp	x2, .LANCHOR33
	str	w0, [x2, #:lo12:.LANCHOR33]
	adrp	x0, .LANCHOR6
	ldr	w2, [x0, #:lo12:.LANCHOR6]
	adrp	x0, .LANCHOR36+6
	ldrh	w0, [x0, #:lo12:.LANCHOR36+6]
	cmp	w1, w2
	sub	w0, w2, w0
	sub	w0, w0, w1
	udiv	w0, w0, w3
	adrp	x3, .LANCHOR170
	strh	w0, [x3, #:lo12:.LANCHOR170]
	bls	.L1405
	adrp	x1, .LANCHOR177
	adrp	x0, .LC1
	mov	w2, 1498
	add	x1, x1, :lo12:.LANCHOR177
	add	x0, x0, :lo12:.LC1
	bl	printf
.L1405:
	add	x4, x19, :lo12:.LANCHOR38
	adrp	x0, .LANCHOR50
	add	x2, x0, :lo12:.LANCHOR50
	adrp	x5, .LANCHOR144
	adrp	x20, .LANCHOR51
	mov	x22, x5
	ldrh	w1, [x4, 16]
	ldrh	w6, [x4, 14]
	strh	w6, [x0, #:lo12:.LANCHOR50]
	lsr	w3, w1, 6
	and	w1, w1, 63
	strb	w1, [x2, 6]
	ldrb	w1, [x4, 11]
	strb	w1, [x2, 8]
	add	x1, x5, :lo12:.LANCHOR144
	strh	w3, [x2, 2]
	mov	w2, -1
	strh	w2, [x5, #:lo12:.LANCHOR144]
	add	x2, x20, :lo12:.LANCHOR51
	strh	wzr, [x1, 2]
	strb	wzr, [x1, 6]
	strb	wzr, [x1, 8]
	ldrh	w1, [x4, 18]
	strh	w1, [x20, #:lo12:.LANCHOR51]
	ldrh	w1, [x4, 20]
	lsr	w3, w1, 6
	and	w1, w1, 63
	strb	w1, [x2, 6]
	ldrb	w1, [x4, 12]
	strh	w3, [x2, 2]
	strb	w1, [x2, 8]
	adrp	x2, .LANCHOR52
	ldrh	w1, [x4, 22]
	add	x3, x2, :lo12:.LANCHOR52
	strh	w1, [x2, #:lo12:.LANCHOR52]
	mov	x21, x2
	ldrh	w1, [x4, 24]
	lsr	w7, w1, 6
	and	w1, w1, 63
	strb	w1, [x3, 6]
	ldrb	w1, [x4, 13]
	strb	w1, [x3, 8]
	adrp	x1, .LANCHOR83
	strh	w7, [x3, 2]
	ldr	w3, [x4, 32]
	str	wzr, [x1, #:lo12:.LANCHOR83]
	adrp	x1, .LANCHOR84
	str	wzr, [x1, #:lo12:.LANCHOR84]
	adrp	x1, .LANCHOR88
	str	wzr, [x1, #:lo12:.LANCHOR88]
	adrp	x1, .LANCHOR87
	str	wzr, [x1, #:lo12:.LANCHOR87]
	adrp	x1, .LANCHOR89
	str	w3, [x1, #:lo12:.LANCHOR89]
	adrp	x1, .LANCHOR90
	str	wzr, [x1, #:lo12:.LANCHOR90]
	adrp	x1, .LANCHOR91
	str	wzr, [x1, #:lo12:.LANCHOR91]
	adrp	x1, .LANCHOR86
	ldr	w3, [x4, 40]
	str	wzr, [x1, #:lo12:.LANCHOR86]
	adrp	x1, .LANCHOR81
	ldr	w4, [x1, #:lo12:.LANCHOR81]
	cmp	w3, w4
	bls	.L1406
	str	w3, [x1, #:lo12:.LANCHOR81]
.L1406:
	add	x19, x19, :lo12:.LANCHOR38
	adrp	x1, .LANCHOR82
	ldr	w3, [x1, #:lo12:.LANCHOR82]
	ldr	w2, [x19, 36]
	cmp	w2, w3
	bls	.L1407
	str	w2, [x1, #:lo12:.LANCHOR82]
.L1407:
	mov	w1, 65535
	cmp	w6, w1
	beq	.L1408
	add	x0, x0, :lo12:.LANCHOR50
	bl	make_superblock
.L1408:
	ldrh	w2, [x20, #:lo12:.LANCHOR51]
	mov	w1, 65535
	add	x0, x20, :lo12:.LANCHOR51
	cmp	w2, w1
	beq	.L1409
	bl	make_superblock
.L1409:
	ldrh	w2, [x21, #:lo12:.LANCHOR52]
	mov	w1, 65535
	add	x0, x21, :lo12:.LANCHOR52
	cmp	w2, w1
	beq	.L1410
	bl	make_superblock
.L1410:
	ldrh	w2, [x22, #:lo12:.LANCHOR144]
	mov	w1, 65535
	add	x0, x22, :lo12:.LANCHOR144
	cmp	w2, w1
	beq	.L1411
	bl	make_superblock
.L1411:
	mov	w0, 0
	b	.L1392
.L1401:
	add	x3, x19, :lo12:.LANCHOR137
	orr	w0, w28, w24, lsl 10
	mov	w2, 1
	str	x3, [x29, 104]
	mov	w1, w2
	str	w0, [x3, 4]
	ldr	x0, [x22, #:lo12:.LANCHOR105]
	str	x0, [x3, 8]
	mov	x0, x3
	bl	FlashReadPages
	ldr	x3, [x29, 104]
	ldr	x0, [x3, 16]
	ldr	w8, [x0, 12]
	cbz	w8, .L1396
	ldr	w0, [x19, #:lo12:.LANCHOR137]
	cmn	w0, #1
	beq	.L1396
	ldrh	w1, [x26]
	ldr	x0, [x3, 8]
	bl	js_hash
	cmp	w8, w0
	beq	.L1396
	add	x10, x20, :lo12:.LANCHOR138
	mov	w6, w0
	mov	w5, w8
	adrp	x0, .LC46
	mov	w3, w28
	mov	w2, w24
	ldrh	w4, [x10, 4]
	mov	x1, x27
	add	x0, x0, :lo12:.LC46
	str	x10, [x29, 104]
	bl	printf
	cbnz	w28, .L1397
	ldr	x10, [x29, 104]
	ldrh	w0, [x10, 4]
	cmp	w24, w0
	beq	.L1397
	sxth	w24, w0
	adrp	x0, .LANCHOR19
	ldrh	w7, [x0, #:lo12:.LANCHOR19]
	sub	w7, w7, #1
.L1423:
	sxth	w28, w7
	b	.L1395
.L1397:
	mov	w0, -1
	str	w0, [x19, #:lo12:.LANCHOR137]
.L1396:
	ldr	w0, [x19, #:lo12:.LANCHOR137]
	cmn	w0, #1
	beq	.L1399
	ldr	x0, [x22, #:lo12:.LANCHOR105]
	mov	w1, 19539
	movk	w1, 0x4654, lsl 16
	ldr	w0, [x0]
	cmp	w0, w1
	bne	.L1399
	ldr	x0, [x25, #:lo12:.LANCHOR113]
	ldrh	w1, [x0]
	mov	w0, 61604
	cmp	w1, w0
	beq	.L1400
.L1399:
	sub	w7, w28, #1
	b	.L1423
	.size	FtlLoadSysInfo, .-FtlLoadSysInfo
	.section	.text.FtlMapTblRecovery,"ax",@progbits
	.align	2
	.global	FtlMapTblRecovery
	.type	FtlMapTblRecovery, %function
FtlMapTblRecovery:
	stp	x29, x30, [sp, -160]!
	mov	w1, 0
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	x19, x0
	stp	x25, x26, [sp, 64]
	mov	w20, 0
	ldrh	w25, [x0, 6]
	adrp	x26, .LANCHOR19
	stp	x23, x24, [sp, 48]
	ldr	x23, [x0, 40]
	ldr	x24, [x0, 16]
	lsl	w2, w25, 2
	ldr	x0, [x0, 24]
	str	x0, [x29, 144]
	ldrh	w0, [x19, 8]
	stp	x21, x22, [sp, 32]
	adrp	x22, .LANCHOR105
	stp	x27, x28, [sp, 80]
	str	w0, [x29, 152]
	mov	x0, x23
	bl	ftl_memset
	stp	wzr, wzr, [x19, 48]
	adrp	x0, .LANCHOR137
	add	x6, x0, :lo12:.LANCHOR137
	ldr	x1, [x22, #:lo12:.LANCHOR105]
	mov	x27, x6
	str	x0, [x29, 128]
	str	x1, [x6, 8]
	adrp	x1, .LANCHOR113
	ldr	w0, [x29, 152]
	ldr	x21, [x1, #:lo12:.LANCHOR113]
	mov	w1, -1
	str	x21, [x6, 16]
	sub	w0, w0, #1
	strh	w1, [x19]
	strh	w1, [x19, 2]
	mov	w1, 1
	str	w0, [x29, 108]
	add	x0, x26, :lo12:.LANCHOR19
	str	w1, [x19, 56]
	str	x0, [x29, 96]
.L1425:
	ldr	w0, [x29, 152]
	cmp	w20, w0
	bge	.L1444
	ldr	w0, [x29, 108]
	sxtw	x28, w20
	cmp	w20, w0
	bne	.L1426
	lsl	x0, x28, 1
	mov	w1, 1
	add	x26, x24, x0
	adrp	x27, .LANCHOR22
	add	x27, x27, :lo12:.LANCHOR22
	ldrh	w0, [x24, x0]
	mov	w24, 0
	bl	FtlGetLastWrittenPage
	sxth	w1, w0
	add	w0, w0, 1
	strh	w0, [x19, 2]
	ldr	x0, [x29, 144]
	strh	w20, [x19]
	str	w1, [x29, 152]
	ldr	w0, [x0, x28, lsl 2]
	adrp	x28, .LANCHOR179
	str	w0, [x19, 48]
	add	x28, x28, :lo12:.LANCHOR179
	ldr	x0, [x29, 128]
	add	x22, x0, :lo12:.LANCHOR137
.L1427:
	ldr	w0, [x29, 152]
	cmp	w24, w0
	ble	.L1430
.L1444:
	mov	x0, x19
	bl	ftl_free_no_use_map_blk
	adrp	x0, .LANCHOR19
	ldrh	w1, [x19, 2]
	ldrh	w0, [x0, #:lo12:.LANCHOR19]
	cmp	w1, w0
	bne	.L1432
	mov	x0, x19
	bl	ftl_map_blk_alloc_new_blk
.L1432:
	mov	x0, x19
	bl	ftl_map_blk_gc
	mov	x0, x19
	bl	ftl_map_blk_gc
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 160
	ret
.L1430:
	ldrh	w0, [x26]
	mov	w2, 1
	mov	w1, w2
	orr	w0, w24, w0, lsl 10
	str	w0, [x22, 4]
	mov	x0, x22
	bl	FlashReadPages
	ldr	x0, [x22, 16]
	ldr	w0, [x0, 12]
	str	w0, [x29, 156]
	uxtw	x0, w0
	cbz	w0, .L1428
	ldr	w0, [x22]
	cmn	w0, #1
	beq	.L1428
	ldrh	w1, [x27]
	ldr	x0, [x22, 8]
	bl	js_hash
	ldr	w1, [x29, 156]
	cmp	w1, w0
	beq	.L1428
	mov	w5, w0
	mov	x4, x1
	mov	w3, w24
	mov	w2, w20
	mov	x1, x28
	adrp	x0, .LC47
	add	x0, x0, :lo12:.LC47
	bl	printf
	mov	w0, -1
	str	w0, [x22]
.L1428:
	ldr	w0, [x22]
	cmn	w0, #1
	beq	.L1429
	ldrh	w0, [x21, 8]
	cmp	w25, w0
	bls	.L1429
	ldrh	w2, [x21]
	ldrh	w1, [x19, 4]
	cmp	w2, w1
	bne	.L1429
	ubfiz	x0, x0, 2, 16
	ldr	w1, [x22, 4]
	str	w1, [x23, x0]
.L1429:
	add	w6, w24, 1
	sxth	w24, w6
	b	.L1427
.L1426:
	lsl	x2, x28, 1
	ldr	x0, [x22, #:lo12:.LANCHOR105]
	str	x0, [x27, 8]
	add	x0, x24, x2
	ldrh	w1, [x26, #:lo12:.LANCHOR19]
	str	x0, [x29, 136]
	ldrh	w0, [x24, x2]
	sub	w1, w1, #1
	mov	w2, 1
	orr	w0, w1, w0, lsl 10
	mov	w1, w2
	str	w0, [x27, 4]
	mov	x0, x27
	bl	FlashReadPages
	ldr	w0, [x27]
	cmn	w0, #1
	beq	.L1446
	ldrh	w1, [x21]
	ldrh	w0, [x19, 4]
	cmp	w1, w0
	bne	.L1446
	ldrh	w1, [x21, 8]
	mov	w0, 64245
	cmp	w1, w0
	beq	.L1434
.L1446:
	adrp	x0, .LANCHOR22
	add	x0, x0, :lo12:.LANCHOR22
	mov	w28, 0
	str	x0, [x29, 120]
	adrp	x0, .LANCHOR179
	add	x0, x0, :lo12:.LANCHOR179
	str	x0, [x29, 112]
.L1435:
	ldr	x0, [x29, 96]
	ldrh	w0, [x0]
	cmp	w28, w0
	bge	.L1442
	ldr	x0, [x29, 136]
	mov	w2, 1
	mov	w1, w2
	ldrh	w0, [x0]
	orr	w0, w28, w0, lsl 10
	str	w0, [x27, 4]
	mov	x0, x27
	bl	FlashReadPages
	ldr	x0, [x27, 16]
	ldr	w0, [x0, 12]
	str	w0, [x29, 156]
	uxtw	x0, w0
	cbz	w0, .L1439
	ldr	w0, [x27]
	cmn	w0, #1
	beq	.L1439
	ldr	x0, [x29, 120]
	ldrh	w1, [x0]
	ldr	x0, [x27, 8]
	bl	js_hash
	ldr	w1, [x29, 156]
	cmp	w1, w0
	beq	.L1439
	mov	x4, x1
	ldr	x1, [x29, 112]
	mov	w5, w0
	mov	w3, w28
	mov	w2, w20
	adrp	x0, .LC48
	add	x0, x0, :lo12:.LC48
	bl	printf
	mov	w0, -1
	str	w0, [x27]
.L1439:
	ldr	w0, [x27]
	cmn	w0, #1
	beq	.L1440
	ldrh	w0, [x21, 8]
	cmp	w25, w0
	bls	.L1440
	ldrh	w2, [x21]
	ldrh	w1, [x19, 4]
	cmp	w2, w1
	bne	.L1440
	ubfiz	x0, x0, 2, 16
	ldr	w1, [x27, 4]
	str	w1, [x23, x0]
.L1440:
	add	w7, w28, 1
	sxth	w28, w7
	b	.L1435
.L1434:
	ldrh	w3, [x26, #:lo12:.LANCHOR19]
	mov	w0, 0
	ldr	x4, [x22, #:lo12:.LANCHOR105]
	sub	w3, w3, #1
.L1436:
	cmp	w0, w3
	blt	.L1438
.L1442:
	add	w20, w20, 1
	sxth	w20, w20
	b	.L1425
.L1438:
	lsl	w2, w0, 1
	sxtw	x2, w2
	lsl	x1, x2, 2
	ldrh	w1, [x4, x1]
	cmp	w25, w1
	bls	.L1437
	add	x2, x2, 1
	ubfiz	x1, x1, 2, 16
	ldr	w2, [x4, x2, lsl 2]
	str	w2, [x23, x1]
.L1437:
	add	w0, w0, 1
	sxth	w0, w0
	b	.L1436
	.size	FtlMapTblRecovery, .-FtlMapTblRecovery
	.section	.text.FtlLoadVonderInfo,"ax",@progbits
	.align	2
	.global	FtlLoadVonderInfo
	.type	FtlLoadVonderInfo, %function
FtlLoadVonderInfo:
	stp	x29, x30, [sp, -16]!
	adrp	x1, .LANCHOR26
	adrp	x0, .LANCHOR160
	add	x0, x0, :lo12:.LANCHOR160
	add	x29, sp, 0
	ldrh	w1, [x1, #:lo12:.LANCHOR26]
	strh	w1, [x0, 10]
	mov	w1, -3962
	strh	w1, [x0, 4]
	adrp	x1, .LANCHOR34
	ldrh	w1, [x1, #:lo12:.LANCHOR34]
	strh	w1, [x0, 8]
	adrp	x1, .LANCHOR27
	ldrh	w1, [x1, #:lo12:.LANCHOR27]
	strh	w1, [x0, 6]
	adrp	x1, .LANCHOR35
	ldr	x1, [x1, #:lo12:.LANCHOR35]
	str	x1, [x0, 16]
	adrp	x1, .LANCHOR121
	ldr	x1, [x1, #:lo12:.LANCHOR121]
	str	x1, [x0, 24]
	adrp	x1, .LANCHOR120
	ldr	x1, [x1, #:lo12:.LANCHOR120]
	str	x1, [x0, 32]
	adrp	x1, .LANCHOR122
	ldr	x1, [x1, #:lo12:.LANCHOR122]
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
	adrp	x0, .LANCHOR128
	add	x0, x0, :lo12:.LANCHOR128
	bl	FtlMapTblRecovery
	mov	w0, 0
	ldp	x29, x30, [sp], 16
	ret
	.size	FtlLoadMapInfo, .-FtlLoadMapInfo
	.section	.text.FtlSysBlkInit,"ax",@progbits
	.align	2
	.global	FtlSysBlkInit
	.type	FtlSysBlkInit, %function
FtlSysBlkInit:
	stp	x29, x30, [sp, -64]!
	adrp	x0, .LANCHOR3
	add	x29, sp, 0
	ldrh	w0, [x0, #:lo12:.LANCHOR3]
	stp	x19, x20, [sp, 16]
	adrp	x19, .LANCHOR155
	stp	x21, x22, [sp, 32]
	strh	wzr, [x19, #:lo12:.LANCHOR155]
	str	x23, [sp, 48]
	bl	FtlFreeSysBlkQueueInit
	bl	FtlScanSysBlk
	adrp	x0, .LANCHOR138
	ldrh	w1, [x0, #:lo12:.LANCHOR138]
	mov	w0, 65535
	cmp	w1, w0
	bne	.L1471
.L1473:
	mov	w21, -1
.L1470:
	mov	w0, w21
	ldr	x23, [sp, 48]
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 64
	ret
.L1471:
	bl	FtlLoadSysInfo
	mov	w21, w0
	cbnz	w0, .L1473
	bl	FtlLoadMapInfo
	bl	FtlLoadVonderInfo
	bl	Ftl_load_ext_data
	bl	FtlLoadEctTbl
	bl	FtlFreeSysBLkSort
	bl	SupperBlkListInit
	bl	FtlPowerLostRecovery
	mov	w0, 1
	bl	FtlUpdateVaildLpn
	adrp	x0, .LANCHOR32
	ldrh	w2, [x0, #:lo12:.LANCHOR32]
	adrp	x0, .LANCHOR54
	ldr	x1, [x0, #:lo12:.LANCHOR54]
	mov	w0, 0
	add	x1, x1, 4
.L1474:
	cmp	w0, w2
	bge	.L1479
	ldr	w3, [x1], 16
	tbz	w3, #31, .L1475
.L1479:
	adrp	x3, .LANCHOR82
	cmp	w0, w2
	ldr	w1, [x3, #:lo12:.LANCHOR82]
	add	w1, w1, 32
	str	w1, [x3, #:lo12:.LANCHOR82]
	bge	.L1481
.L1476:
	adrp	x23, .LANCHOR50
	add	x20, x23, :lo12:.LANCHOR50
	mov	x0, x20
	adrp	x22, .LANCHOR51
	bl	FtlSuperblockPowerLostFix
	add	x19, x22, :lo12:.LANCHOR51
	mov	x0, x19
	bl	FtlSuperblockPowerLostFix
	adrp	x0, .LANCHOR41
	ldrh	w3, [x20, 4]
	ldr	x1, [x0, #:lo12:.LANCHOR41]
	ldrh	w0, [x23, #:lo12:.LANCHOR50]
	lsl	x0, x0, 1
	ldrh	w2, [x1, x0]
	sub	w2, w2, w3
	adrp	x3, .LANCHOR18
	strh	w2, [x1, x0]
	strb	wzr, [x20, 6]
	ldrh	w0, [x3, #:lo12:.LANCHOR18]
	strh	w0, [x20, 2]
	ldrh	w0, [x22, #:lo12:.LANCHOR51]
	strh	wzr, [x20, 4]
	ldrh	w4, [x19, 4]
	lsl	x0, x0, 1
	ldrh	w2, [x1, x0]
	sub	w2, w2, w4
	strh	w2, [x1, x0]
	strb	wzr, [x19, 6]
	ldrh	w0, [x3, #:lo12:.LANCHOR18]
	strh	w0, [x19, 2]
	adrp	x0, .LANCHOR38
	add	x0, x0, :lo12:.LANCHOR38
	strh	wzr, [x19, 4]
	ldrh	w1, [x0, 30]
	add	w1, w1, 1
	strh	w1, [x0, 30]
	bl	l2p_flush
	bl	FtlVpcTblFlush
.L1483:
	bl	FtlVpcTblFlush
	b	.L1470
.L1475:
	add	w0, w0, 1
	b	.L1474
.L1481:
	ldrh	w0, [x19, #:lo12:.LANCHOR155]
	cbnz	w0, .L1476
	bl	l2p_flush
	b	.L1483
	.size	FtlSysBlkInit, .-FtlSysBlkInit
	.section	.text.ftl_low_format,"ax",@progbits
	.align	2
	.global	ftl_low_format
	.type	ftl_low_format, %function
ftl_low_format:
	stp	x29, x30, [sp, -80]!
	adrp	x0, .LANCHOR82
	add	x29, sp, 0
	stp	x23, x24, [sp, 48]
	adrp	x23, .LANCHOR3
	str	wzr, [x0, #:lo12:.LANCHOR82]
	adrp	x0, .LANCHOR142
	stp	x19, x20, [sp, 16]
	adrp	x20, .LANCHOR81
	str	wzr, [x0, #:lo12:.LANCHOR142]
	ldrh	w0, [x23, #:lo12:.LANCHOR3]
	stp	x21, x22, [sp, 32]
	stp	x25, x26, [sp, 64]
	str	wzr, [x20, #:lo12:.LANCHOR81]
	bl	FtlFreeSysBlkQueueInit
	bl	FtlLoadBbt
	cbz	w0, .L1485
	bl	FtlMakeBbt
.L1485:
	adrp	x22, .LANCHOR11
	adrp	x0, .LANCHOR108
	mov	w6, 23752
	ldrh	w1, [x22, #:lo12:.LANCHOR11]
	movk	w6, 0xa0f, lsl 16
	ldr	x4, [x0, #:lo12:.LANCHOR108]
	adrp	x0, .LANCHOR109
	lsl	w1, w1, 7
	ldr	x5, [x0, #:lo12:.LANCHOR109]
	mov	w0, 0
.L1486:
	cmp	w0, w1
	blt	.L1487
	adrp	x24, .LANCHOR4
	adrp	x21, .LANCHOR5
	add	x26, x21, :lo12:.LANCHOR5
	mov	w19, 0
	ldrh	w25, [x24, #:lo12:.LANCHOR4]
.L1488:
	ldrh	w0, [x26]
	cmp	w0, w25
	bhi	.L1489
	adrp	x25, .LANCHOR2
	sub	w1, w19, #2
	ldrh	w0, [x25, #:lo12:.LANCHOR2]
	cmp	w1, w0, lsl 1
	bgt	.L1490
.L1494:
	add	x24, x24, :lo12:.LANCHOR4
	mov	w19, 0
	mov	w23, 0
.L1491:
	ldrh	w0, [x24]
	cmp	w0, w23
	bhi	.L1495
	adrp	x0, .LANCHOR98
	ldrh	w1, [x21, #:lo12:.LANCHOR5]
	ldrh	w4, [x25, #:lo12:.LANCHOR2]
	adrp	x2, .LANCHOR170
	str	w1, [x0, #:lo12:.LANCHOR98]
	adrp	x0, .LANCHOR6
	adrp	x3, .LANCHOR151
	ldr	w1, [x0, #:lo12:.LANCHOR6]
	udiv	w5, w1, w4
	ubfx	x0, x5, 5, 16
	str	w5, [x3, #:lo12:.LANCHOR151]
	add	w6, w0, 36
	strh	w6, [x2, #:lo12:.LANCHOR170]
	mov	w6, 24
	mul	w6, w4, w6
	cmp	w19, w6
	ble	.L1496
	sub	w1, w1, w19
	udiv	w1, w1, w4
	str	w1, [x3, #:lo12:.LANCHOR151]
	lsr	w1, w1, 5
	add	w1, w1, 24
	strh	w1, [x2, #:lo12:.LANCHOR170]
.L1496:
	adrp	x1, .LANCHOR14
	ldrh	w1, [x1, #:lo12:.LANCHOR14]
	cbz	w1, .L1498
	ldrh	w6, [x2, #:lo12:.LANCHOR170]
	add	w6, w6, w1, lsr 1
	strh	w6, [x2, #:lo12:.LANCHOR170]
	mul	w6, w1, w4
	cmp	w19, w6
	bge	.L1498
	add	w1, w1, 32
	str	w5, [x3, #:lo12:.LANCHOR151]
	add	w1, w0, w1
	strh	w1, [x2, #:lo12:.LANCHOR170]
.L1498:
	ldrh	w1, [x2, #:lo12:.LANCHOR170]
	adrp	x23, .LANCHOR178
	ldr	w0, [x3, #:lo12:.LANCHOR151]
	sub	w0, w0, w1
	adrp	x1, .LANCHOR18
	ldrh	w1, [x1, #:lo12:.LANCHOR18]
	mul	w0, w0, w4
	str	w0, [x23, #:lo12:.LANCHOR178]
	mul	w0, w1, w0
	ldrh	w1, [x22, #:lo12:.LANCHOR11]
	str	w0, [x3, #:lo12:.LANCHOR151]
	mov	x22, x23
	mul	w0, w1, w0
	adrp	x1, .LANCHOR33
	str	w0, [x1, #:lo12:.LANCHOR33]
	bl	FtlBbmTblFlush
	ldrh	w2, [x21, #:lo12:.LANCHOR5]
	adrp	x21, .LANCHOR41
	mov	w1, 0
	ldr	x0, [x21, #:lo12:.LANCHOR41]
	lsl	w2, w2, 1
	bl	ftl_memset
	adrp	x2, .LANCHOR144
	add	x1, x2, :lo12:.LANCHOR144
	adrp	x0, .LANCHOR58
	strh	wzr, [x1, 2]
	strb	wzr, [x1, 6]
	strb	wzr, [x1, 8]
	adrp	x1, .LANCHOR50
	add	x19, x1, :lo12:.LANCHOR50
	str	wzr, [x0, #:lo12:.LANCHOR58]
	mov	w0, -1
	mov	w23, w0
	strh	wzr, [x1, #:lo12:.LANCHOR50]
	mov	w1, 1
	strh	w0, [x2, #:lo12:.LANCHOR144]
	strh	wzr, [x19, 2]
	strb	wzr, [x19, 6]
	strb	w1, [x19, 8]
.L1500:
	mov	x0, x19
	bl	make_superblock
	ldrb	w1, [x19, 7]
	ldrh	w0, [x19]
	cbnz	w1, .L1501
	ldr	x1, [x21, #:lo12:.LANCHOR41]
	ubfiz	x0, x0, 1, 16
	strh	w23, [x1, x0]
	ldrh	w0, [x19]
	add	w0, w0, 1
	strh	w0, [x19]
	b	.L1500
.L1487:
	ubfiz	x3, x0, 2, 16
	mvn	w2, w0
	orr	w2, w0, w2, lsl 16
	add	w0, w0, 1
	and	w0, w0, 65535
	str	w2, [x4, x3]
	str	w6, [x5, x3]
	b	.L1486
.L1489:
	mov	w0, w25
	mov	w1, 1
	add	w25, w25, 1
	bl	FtlLowFormatEraseBlock
	add	w19, w19, w0
	and	w25, w25, 65535
	and	w19, w19, 65535
	b	.L1488
.L1490:
	udiv	w0, w19, w0
	adrp	x1, .LANCHOR30
	ldr	w19, [x1, #:lo12:.LANCHOR30]
	add	w0, w0, w19
	bl	FtlSysBlkNumInit
	ldrh	w0, [x23, #:lo12:.LANCHOR3]
	add	x23, x21, :lo12:.LANCHOR5
	bl	FtlFreeSysBlkQueueInit
	ldrh	w19, [x24, #:lo12:.LANCHOR4]
.L1492:
	ldrh	w0, [x23]
	cmp	w0, w19
	bls	.L1494
	mov	w0, w19
	add	w19, w19, 1
	mov	w1, 1
	and	w19, w19, 65535
	bl	FtlLowFormatEraseBlock
	b	.L1492
.L1495:
	mov	w0, w23
	mov	w1, 0
	add	w23, w23, 1
	bl	FtlLowFormatEraseBlock
	add	w19, w19, w0
	and	w23, w23, 65535
	and	w19, w19, 65535
	b	.L1491
.L1501:
	ldr	w1, [x20, #:lo12:.LANCHOR81]
	ubfiz	x0, x0, 1, 16
	str	w1, [x19, 12]
	mov	w23, -1
	add	w1, w1, 1
	str	w1, [x20, #:lo12:.LANCHOR81]
	ldr	x1, [x21, #:lo12:.LANCHOR41]
	ldrh	w2, [x19, 4]
	strh	w2, [x1, x0]
	adrp	x2, .LANCHOR51
	add	x0, x2, :lo12:.LANCHOR51
	ldrh	w1, [x19]
	mov	x19, x0
	add	w1, w1, 1
	strh	wzr, [x0, 2]
	strh	w1, [x2, #:lo12:.LANCHOR51]
	mov	w1, 1
	strb	wzr, [x0, 6]
	strb	w1, [x0, 8]
.L1502:
	mov	x0, x19
	bl	make_superblock
	ldrb	w1, [x19, 7]
	ldrh	w0, [x19]
	cbnz	w1, .L1503
	ldr	x1, [x21, #:lo12:.LANCHOR41]
	ubfiz	x0, x0, 1, 16
	strh	w23, [x1, x0]
	ldrh	w0, [x19]
	add	w0, w0, 1
	strh	w0, [x19]
	b	.L1502
.L1503:
	ldr	w1, [x20, #:lo12:.LANCHOR81]
	ubfiz	x0, x0, 1, 16
	str	w1, [x19, 12]
	add	w1, w1, 1
	str	w1, [x20, #:lo12:.LANCHOR81]
	ldr	x1, [x21, #:lo12:.LANCHOR41]
	ldrh	w2, [x19, 4]
	mov	w19, -1
	strh	w2, [x1, x0]
	adrp	x0, .LANCHOR52
	strh	w19, [x0, #:lo12:.LANCHOR52]
	bl	FtlFreeSysBlkQueueOut
	adrp	x2, .LANCHOR138
	add	x1, x2, :lo12:.LANCHOR138
	strh	w0, [x2, #:lo12:.LANCHOR138]
	ldr	w0, [x22, #:lo12:.LANCHOR178]
	strh	w0, [x1, 6]
	ldr	w0, [x20, #:lo12:.LANCHOR81]
	str	w0, [x1, 8]
	add	w0, w0, 1
	strh	wzr, [x1, 2]
	strh	w19, [x1, 4]
	str	w0, [x20, #:lo12:.LANCHOR81]
	bl	FtlVpcTblFlush
	bl	FtlSysBlkInit
	cbnz	w0, .L1504
	adrp	x0, .LANCHOR165
	mov	w1, 1
	str	w1, [x0, #:lo12:.LANCHOR165]
.L1504:
	mov	w0, 0
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x29, x30, [sp], 80
	ret
	.size	ftl_low_format, .-ftl_low_format
	.section	.text.sftl_init,"ax",@progbits
	.align	2
	.global	sftl_init
	.type	sftl_init, %function
sftl_init:
	stp	x29, x30, [sp, -32]!
	adrp	x1, .LC49
	add	x1, x1, :lo12:.LC49
	mov	w0, -1
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	adrp	x20, .LANCHOR165
	adrp	x19, .LANCHOR180
	add	x19, x19, :lo12:.LANCHOR180
	str	w0, [x20, #:lo12:.LANCHOR165]
	adrp	x0, .LC38
	add	x0, x0, :lo12:.LC38
	bl	printf
	adrp	x0, .LANCHOR0
	add	x0, x0, :lo12:.LANCHOR0
	bl	FtlConstantsInit
	bl	FtlMemInit
	bl	FtlVariablesInit
	adrp	x0, .LANCHOR3
	ldrh	w0, [x0, #:lo12:.LANCHOR3]
	bl	FtlFreeSysBlkQueueInit
.L1510:
	bl	FtlLoadBbt
	cbz	w0, .L1511
.L1521:
	ldr	w0, [x19]
	cmp	w0, 1
	bne	.L1510
	str	wzr, [x19]
	bl	ftl_low_format
	b	.L1510
.L1511:
	bl	FtlSysBlkInit
	cbnz	w0, .L1521
	mov	w1, 1
	str	w1, [x20, #:lo12:.LANCHOR165]
	ldp	x19, x20, [sp, 16]
	ldp	x29, x30, [sp], 32
	ret
	.size	sftl_init, .-sftl_init
	.section	.text.FtlWriteToIDB,"ax",@progbits
	.align	2
	.global	FtlWriteToIDB
	.type	FtlWriteToIDB, %function
FtlWriteToIDB:
	stp	x29, x30, [sp, -224]!
	add	x29, sp, 0
	stp	x21, x22, [sp, 32]
	add	w22, w1, w0
	stp	x23, x24, [sp, 48]
	sub	w23, w22, #1
	stp	x27, x28, [sp, 80]
	cmp	w23, 63
	stp	x19, x20, [sp, 16]
	adrp	x27, .LANCHOR181
	stp	x25, x26, [sp, 64]
	bls	.L1523
	mov	w19, w0
	cmp	w0, 575
	bls	.L1524
.L1523:
	ldr	w0, [x27, #:lo12:.LANCHOR181]
	cbnz	w0, .L1525
.L1589:
	mov	w19, 0
	b	.L1522
.L1525:
	adrp	x0, .LANCHOR182
	str	x0, [x29, 112]
	mov	w1, 35899
	ldr	x26, [x0, #:lo12:.LANCHOR182]
	movk	w1, 0xfcdc, lsl 16
	ldr	w2, [x26]
	cmp	w2, w1
	bne	.L1527
	adrp	x22, .LANCHOR0
	add	x0, x22, :lo12:.LANCHOR0
	add	x1, x26, 258048
	mov	w19, 65023
	add	x1, x1, 2044
	mov	w3, 4097
	ldrh	w2, [x0, 10]
	mov	w0, 0
.L1531:
	ldr	w4, [x1]
	cbnz	w4, .L1528
	ldr	w4, [x26, w0, uxtw 2]
	add	w0, w0, 1
	str	w4, [x1, 2048]
	cmp	w0, w3
	sub	w19, w19, #1
	csel	w0, w0, wzr, cc
	sub	x1, x1, #4
	cmp	w19, 4096
	bne	.L1531
	mov	w19, 512
	b	.L1530
.L1528:
	add	w19, w19, 127
	lsr	w19, w19, 7
.L1530:
	ubfiz	w0, w2, 2, 14
	add	w21, w19, 4
	mov	w1, w19
	mov	w24, 0
	udiv	w21, w21, w0
	adrp	x0, .LC50
	add	x0, x0, :lo12:.LC50
	add	w21, w21, 1
	mov	w2, w21
	bl	printf
	lsl	w0, w19, 7
	str	w0, [x29, 136]
	adrp	x0, .LANCHOR77
	add	x20, x0, :lo12:.LANCHOR77
	str	wzr, [x29, 156]
.L1532:
	add	w0, w21, w24
	str	w0, [x29, 140]
	cmp	w0, 8
	bls	.L1554
	ldr	w0, [x29, 156]
	cbnz	w0, .L1555
.L1527:
	mov	w19, -1
.L1555:
	ldr	x0, [x29, 112]
	str	wzr, [x27, #:lo12:.LANCHOR181]
	ldr	x0, [x0, #:lo12:.LANCHOR182]
	bl	free
	adrp	x0, .LANCHOR183
	ldr	x0, [x0, #:lo12:.LANCHOR183]
	bl	free
.L1522:
	mov	w0, w19
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x23, x24, [sp, 48]
	ldp	x25, x26, [sp, 64]
	ldp	x27, x28, [sp, 80]
	ldp	x29, x30, [sp], 224
	ret
.L1554:
	adrp	x23, .LANCHOR183
	mov	w1, 0
	mov	x2, 512
	ldr	x0, [x23, #:lo12:.LANCHOR183]
	bl	memset
	add	x0, x22, :lo12:.LANCHOR0
	ldrh	w3, [x0, 10]
	mul	w0, w24, w3
	str	w0, [x29, 144]
	adrp	x0, .LANCHOR77
	add	x0, x0, :lo12:.LANCHOR77
	ldr	x1, [x0, 32]
	cbz	x1, .L1562
	ldr	x0, [x0, 40]
	mov	w25, 6
	cmp	x0, 0
	mov	w0, 9
	csel	w25, w25, w0, eq
.L1533:
	mul	w4, w24, w3
	mov	w28, 0
.L1534:
	ldr	x5, [x20, 8]
	mov	w1, w4
	str	w3, [x29, 128]
	mov	w0, 0
	str	w4, [x29, 152]
	add	w28, w28, 1
	blr	x5
	ldr	w3, [x29, 128]
	cmp	w21, w28
	ldr	w4, [x29, 152]
	add	w4, w4, w3
	bhi	.L1534
	cmp	w25, 9
	bne	.L1564
	ldr	x28, [x23, #:lo12:.LANCHOR183]
	mov	w2, 1024
	str	w3, [x29, 152]
	mov	w1, 0
	mov	x0, x28
	bl	ftl_memset
	mov	w0, 18766
	mov	w1, 12
	movk	w0, 0x464e, lsl 16
	stp	w0, w1, [x28]
	mov	w0, 4
	strb	w0, [x28, 17]
	add	x0, x22, :lo12:.LANCHOR0
	strb	wzr, [x28, 16]
	strb	wzr, [x28, 20]
	strh	wzr, [x28, 22]
	ldrh	w0, [x0, 10]
	strh	w0, [x28, 18]
	str	wzr, [x28, 12]
	mov	w0, 16
	strb	w0, [x28, 21]
	add	x0, x28, 12
	bl	js_hash
	str	w0, [x28, 8]
	ldr	w3, [x29, 152]
.L1535:
	mul	w0, w21, w3
	mov	x6, x26
	str	w0, [x29, 152]
	mov	x5, 0
	add	x0, x22, :lo12:.LANCHOR0
	str	x0, [x29, 128]
.L1536:
	ldr	w0, [x29, 152]
	mov	w1, w5
	cmp	w5, w0
	bcs	.L1543
	cmp	w25, 9
	bne	.L1537
	add	w0, w1, 1
.L1587:
	str	w0, [x29, 160]
	mov	w0, 61424
	str	w0, [x29, 164]
	cmp	w1, 0
	ccmp	w25, 9, 0, eq
	bne	.L1539
	ldr	x1, [x20, 32]
	mov	w0, 70
	stp	x6, x5, [x29, 96]
	blr	x1
	ldr	w1, [x29, 144]
	add	x3, x29, 160
	ldr	x7, [x20, 16]
	mov	x2, x28
	mov	w0, 0
	blr	x7
	mov	w1, w0
	ldr	x0, [x29, 128]
	ldr	x2, [x20, 32]
	str	w1, [x29, 120]
	ldrb	w0, [x0, 22]
	blr	x2
	ldr	w1, [x29, 120]
	ldp	x6, x5, [x29, 96]
	cmn	w1, #1
	bne	.L1540
.L1543:
	add	x0, x22, :lo12:.LANCHOR0
	ldr	x25, [x23, #:lo12:.LANCHOR183]
	ldrb	w1, [x0, 14]
	ldrh	w0, [x0, 10]
	str	w1, [x29, 128]
	mul	w1, w24, w0
	str	w1, [x29, 144]
	ldr	x1, [x20, 32]
	cbnz	x1, .L1541
	mov	w1, 6
.L1588:
	mul	w0, w21, w0
	mov	x28, 0
	str	w0, [x29, 120]
	str	w1, [x29, 152]
.L1545:
	ldr	w0, [x29, 120]
	mov	w1, w28
	cmp	w0, w28
	bls	.L1549
	ldr	w0, [x29, 152]
	cmp	w28, 0
	ccmp	w0, 9, 0, eq
	bne	.L1546
	ldr	x1, [x20, 32]
	mov	w0, 70
	blr	x1
	ldr	x1, [x20, 40]
	mov	w0, 2
	blr	x1
	ldr	x6, [x20, 24]
	add	x3, x29, 160
	ldr	w1, [x29, 144]
	mov	x2, x25
	mov	w0, 0
	blr	x6
	ldrb	w0, [x29, 128]
	ldr	x1, [x20, 40]
	blr	x1
	add	x0, x22, :lo12:.LANCHOR0
	ldr	x1, [x20, 32]
	ldrb	w0, [x0, 22]
	blr	x1
	ldr	w0, [x25]
	mov	w1, 18766
	movk	w1, 0x464e, lsl 16
	cmp	w0, w1
	beq	.L1547
.L1549:
	ldr	x0, [x23, #:lo12:.LANCHOR183]
	mov	x2, x26
	mov	x1, 0
.L1548:
	ldr	w3, [x29, 136]
	mov	w28, w1
	cmp	w1, w3
	bcc	.L1552
	ldr	w0, [x29, 156]
	add	w0, w0, 1
	str	w0, [x29, 156]
	cmp	w0, 5
	bls	.L1551
	b	.L1555
.L1562:
	mov	w25, 6
	b	.L1533
.L1564:
	mov	x28, 0
	b	.L1535
.L1537:
	lsl	w0, w1, 2
	b	.L1587
.L1539:
	ldr	x7, [x20, 16]
	add	x3, x29, 160
	ldr	w0, [x29, 144]
	mov	x2, x6
	str	x5, [x29, 104]
	add	w1, w1, w0
	str	x6, [x29, 120]
	mov	w0, 0
	blr	x7
	cmn	w0, #1
	beq	.L1543
	ldr	x6, [x29, 120]
	ldr	x5, [x29, 104]
	add	x6, x6, 2048
.L1540:
	add	x5, x5, 1
	b	.L1536
.L1541:
	ldr	x1, [x20, 40]
	mov	w2, 6
	cmp	x1, 0
	mov	w1, 9
	csel	w1, w2, w1, eq
	b	.L1588
.L1546:
	ldr	x6, [x20, 24]
	add	x3, x29, 160
	ldr	w0, [x29, 144]
	mov	x2, x25
	add	w1, w0, w1
	mov	w0, 0
	blr	x6
	cmn	w0, #1
	beq	.L1549
	ldr	w0, [x29, 164]
	mov	w1, 61424
	cmp	w0, w1
	bne	.L1549
	add	x25, x25, 2048
.L1547:
	add	x28, x28, 1
	b	.L1545
.L1552:
	mov	x25, x2
	ldr	w4, [x0, x1, lsl 2]
	lsl	x5, x1, 2
	add	x2, x2, 4
	add	x1, x1, 1
	ldr	w3, [x25]
	cmp	w4, w3
	beq	.L1548
	mov	x2, 512
	mov	w1, 0
	str	x5, [x29, 144]
	bl	memset
	ldr	x0, [x23, #:lo12:.LANCHOR183]
	mov	w1, w24
	ldr	x5, [x29, 144]
	mov	w4, w28
	ldr	w3, [x25]
	ldr	w2, [x0, x5]
	adrp	x0, .LC51
	add	x0, x0, :lo12:.LC51
	bl	printf
	add	x0, x22, :lo12:.LANCHOR0
	ldr	x2, [x20, 8]
	ldrh	w1, [x0, 10]
	mov	w0, 0
	mul	w1, w1, w24
	blr	x2
.L1551:
	ldr	w24, [x29, 140]
	b	.L1532
.L1524:
	mov	w20, w1
	mov	x21, x2
	cmp	w0, 64
	bne	.L1556
	adrp	x24, .LANCHOR182
	mov	w0, 262144
	bl	ftl_malloc
	str	x0, [x24, #:lo12:.LANCHOR182]
	mov	w0, 262144
	bl	ftl_malloc
	mov	x1, x0
	adrp	x0, .LANCHOR183
	str	x1, [x0, #:lo12:.LANCHOR183]
	ldr	x0, [x24, #:lo12:.LANCHOR182]
	cbz	x0, .L1557
	cbz	x1, .L1557
	mov	w1, 1
	mov	w2, 262144
	str	w1, [x27, #:lo12:.LANCHOR181]
	mov	w1, 0
	bl	ftl_memset
.L1556:
	ldr	w0, [x27, #:lo12:.LANCHOR181]
	cbz	w0, .L1589
	adrp	x0, .LANCHOR182
	cmp	w19, 63
	ldr	x0, [x0, #:lo12:.LANCHOR182]
	bhi	.L1559
	mov	w1, 64
	sub	w19, w1, w19
	sub	w20, w20, w19
	ubfiz	x19, x19, 9, 25
	add	x1, x21, x19
.L1560:
	cmp	w23, 575
	bls	.L1561
	sub	w20, w20, w22
	sub	w20, w20, #446
.L1561:
	lsl	w2, w20, 9
	bl	ftl_memcpy
	b	.L1589
.L1557:
	adrp	x1, .LANCHOR184
	adrp	x0, .LC52
	add	x1, x1, :lo12:.LANCHOR184
	add	x0, x0, :lo12:.LC52
	bl	printf
	b	.L1556
.L1559:
	lsl	w2, w19, 7
	mov	x1, x21
	sub	w2, w2, #8192
	add	x0, x0, x2, lsl 2
	b	.L1560
	.size	FtlWriteToIDB, .-FtlWriteToIDB
	.section	.text.sftl_write,"ax",@progbits
	.align	2
	.global	sftl_write
	.type	sftl_write, %function
sftl_write:
	stp	x29, x30, [sp, -48]!
	add	x29, sp, 0
	stp	x19, x20, [sp, 16]
	mov	w19, w1
	str	x21, [sp, 32]
	mov	w21, w0
	add	w21, w19, w21
	mov	x20, x2
	bl	FtlWriteToIDB
.L1591:
	sub	w1, w21, w19
	mov	x3, x20
	cmp	w19, 256
	bhi	.L1593
	mov	w2, w19
	ldr	x21, [sp, 32]
	ldp	x19, x20, [sp, 16]
	mov	w0, 0
	ldp	x29, x30, [sp], 48
	b	FtlWrite
.L1593:
	mov	w2, 256
	mov	w0, 0
	bl	FtlWrite
	cbnz	w0, .L1590
	add	x20, x20, 131072
	sub	w19, w19, #256
	b	.L1591
.L1590:
	ldp	x19, x20, [sp, 16]
	ldr	x21, [sp, 32]
	ldp	x29, x30, [sp], 48
	ret
	.size	sftl_write, .-sftl_write
	.global	g_nand_ops
	.global	g_nand_phy_info
	.global	gc_ink_free_return_value
	.global	check_vpc_table
	.global	FtlUpdateVaildLpnCount
	.global	g_ect_tbl_power_up_flush
	.global	power_up_flag
	.global	low_format_en
	.global	gFtlInitStatus
	.global	DeviceCapacity
	.global	g_power_lost_recovery_flag
	.global	c_mlc_erase_count_value
	.global	g_recovery_ppa_tbl
	.global	g_recovery_page_min_ver
	.global	g_recovery_page_num
	.global	sftl_nand_check_spare_buf
	.global	sftl_temp_buf
	.global	sftl_nand_check_buf
	.global	g_cur_erase_blk
	.global	g_gc_skip_write_count
	.global	g_gc_head_data_block_count
	.global	g_gc_head_data_block
	.global	g_ftl_nand_free_count
	.global	g_in_swl_replace
	.global	g_in_gc_progress
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
	.global	g_gc_bad_block_temp_tbl
	.global	g_gc_bad_block_gc_index
	.global	g_gc_bad_block_temp_num
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
	.global	p_map_region_ppn_table
	.global	p_map_block_ver_table
	.global	p_map_block_valid_page_count
	.global	p_map_block_table
	.global	p_valid_page_count_check_table
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
	.global	p_plane_order_table
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
	.global	c_ftl_nand_blks_per_die_shift
	.global	c_ftl_nand_blks_per_die
	.global	c_ftl_nand_planes_per_die
	.global	c_ftl_nand_die_num
	.global	c_ftl_nand_type
	.section	.bss.DeviceCapacity,"aw",@nobits
	.align	2
	.set	.LANCHOR25,. + 0
	.type	DeviceCapacity, %object
	.size	DeviceCapacity, 4
DeviceCapacity:
	.zero	4
	.section	.bss.FtlUpdateVaildLpnCount,"aw",@nobits
	.align	1
	.set	.LANCHOR57,. + 0
	.type	FtlUpdateVaildLpnCount, %object
	.size	FtlUpdateVaildLpnCount, 2
FtlUpdateVaildLpnCount:
	.zero	2
	.section	.bss.c_ftl_nand_bbm_buf_size,"aw",@nobits
	.align	1
	.set	.LANCHOR126,. + 0
	.type	c_ftl_nand_bbm_buf_size, %object
	.size	c_ftl_nand_bbm_buf_size, 2
c_ftl_nand_bbm_buf_size:
	.zero	2
	.section	.bss.c_ftl_nand_blk_pre_plane,"aw",@nobits
	.align	1
	.set	.LANCHOR5,. + 0
	.type	c_ftl_nand_blk_pre_plane, %object
	.size	c_ftl_nand_blk_pre_plane, 2
c_ftl_nand_blk_pre_plane:
	.zero	2
	.section	.bss.c_ftl_nand_blks_per_die,"aw",@nobits
	.align	1
	.set	.LANCHOR16,. + 0
	.type	c_ftl_nand_blks_per_die, %object
	.size	c_ftl_nand_blks_per_die, 2
c_ftl_nand_blks_per_die:
	.zero	2
	.section	.bss.c_ftl_nand_blks_per_die_shift,"aw",@nobits
	.align	1
	.set	.LANCHOR17,. + 0
	.type	c_ftl_nand_blks_per_die_shift, %object
	.size	c_ftl_nand_blks_per_die_shift, 2
c_ftl_nand_blks_per_die_shift:
	.zero	2
	.section	.bss.c_ftl_nand_byte_pre_oob,"aw",@nobits
	.align	1
	.set	.LANCHOR23,. + 0
	.type	c_ftl_nand_byte_pre_oob, %object
	.size	c_ftl_nand_byte_pre_oob, 2
c_ftl_nand_byte_pre_oob:
	.zero	2
	.section	.bss.c_ftl_nand_byte_pre_page,"aw",@nobits
	.align	1
	.set	.LANCHOR22,. + 0
	.type	c_ftl_nand_byte_pre_page, %object
	.size	c_ftl_nand_byte_pre_page, 2
c_ftl_nand_byte_pre_page:
	.zero	2
	.section	.bss.c_ftl_nand_data_blks_per_plane,"aw",@nobits
	.align	1
	.set	.LANCHOR4,. + 0
	.type	c_ftl_nand_data_blks_per_plane, %object
	.size	c_ftl_nand_data_blks_per_plane, 2
c_ftl_nand_data_blks_per_plane:
	.zero	2
	.section	.bss.c_ftl_nand_data_op_blks_per_plane,"aw",@nobits
	.align	1
	.set	.LANCHOR170,. + 0
	.type	c_ftl_nand_data_op_blks_per_plane, %object
	.size	c_ftl_nand_data_op_blks_per_plane, 2
c_ftl_nand_data_op_blks_per_plane:
	.zero	2
	.section	.bss.c_ftl_nand_die_num,"aw",@nobits
	.align	1
	.set	.LANCHOR9,. + 0
	.type	c_ftl_nand_die_num, %object
	.size	c_ftl_nand_die_num, 2
c_ftl_nand_die_num:
	.zero	2
	.section	.bss.c_ftl_nand_ext_blk_pre_plane,"aw",@nobits
	.align	1
	.set	.LANCHOR14,. + 0
	.type	c_ftl_nand_ext_blk_pre_plane, %object
	.size	c_ftl_nand_ext_blk_pre_plane, 2
c_ftl_nand_ext_blk_pre_plane:
	.zero	2
	.section	.bss.c_ftl_nand_init_sys_blks_per_plane,"aw",@nobits
	.align	2
	.set	.LANCHOR30,. + 0
	.type	c_ftl_nand_init_sys_blks_per_plane, %object
	.size	c_ftl_nand_init_sys_blks_per_plane, 4
c_ftl_nand_init_sys_blks_per_plane:
	.zero	4
	.section	.bss.c_ftl_nand_l2pmap_ram_region_num,"aw",@nobits
	.align	1
	.set	.LANCHOR32,. + 0
	.type	c_ftl_nand_l2pmap_ram_region_num, %object
	.size	c_ftl_nand_l2pmap_ram_region_num, 2
c_ftl_nand_l2pmap_ram_region_num:
	.zero	2
	.section	.bss.c_ftl_nand_map_blks_per_plane,"aw",@nobits
	.align	1
	.set	.LANCHOR28,. + 0
	.type	c_ftl_nand_map_blks_per_plane, %object
	.size	c_ftl_nand_map_blks_per_plane, 2
c_ftl_nand_map_blks_per_plane:
	.zero	2
	.section	.bss.c_ftl_nand_map_region_num,"aw",@nobits
	.align	1
	.set	.LANCHOR31,. + 0
	.type	c_ftl_nand_map_region_num, %object
	.size	c_ftl_nand_map_region_num, 2
c_ftl_nand_map_region_num:
	.zero	2
	.section	.bss.c_ftl_nand_max_data_blks,"aw",@nobits
	.align	2
	.set	.LANCHOR6,. + 0
	.type	c_ftl_nand_max_data_blks, %object
	.size	c_ftl_nand_max_data_blks, 4
c_ftl_nand_max_data_blks:
	.zero	4
	.section	.bss.c_ftl_nand_max_map_blks,"aw",@nobits
	.align	2
	.set	.LANCHOR29,. + 0
	.type	c_ftl_nand_max_map_blks, %object
	.size	c_ftl_nand_max_map_blks, 4
c_ftl_nand_max_map_blks:
	.zero	4
	.section	.bss.c_ftl_nand_max_sys_blks,"aw",@nobits
	.align	2
	.set	.LANCHOR3,. + 0
	.type	c_ftl_nand_max_sys_blks, %object
	.size	c_ftl_nand_max_sys_blks, 4
c_ftl_nand_max_sys_blks:
	.zero	4
	.section	.bss.c_ftl_nand_max_vendor_blks,"aw",@nobits
	.align	1
	.set	.LANCHOR26,. + 0
	.type	c_ftl_nand_max_vendor_blks, %object
	.size	c_ftl_nand_max_vendor_blks, 2
c_ftl_nand_max_vendor_blks:
	.zero	2
	.section	.bss.c_ftl_nand_page_pre_blk,"aw",@nobits
	.align	1
	.set	.LANCHOR18,. + 0
	.type	c_ftl_nand_page_pre_blk, %object
	.size	c_ftl_nand_page_pre_blk, 2
c_ftl_nand_page_pre_blk:
	.zero	2
	.section	.bss.c_ftl_nand_page_pre_slc_blk,"aw",@nobits
	.align	1
	.set	.LANCHOR19,. + 0
	.type	c_ftl_nand_page_pre_slc_blk, %object
	.size	c_ftl_nand_page_pre_slc_blk, 2
c_ftl_nand_page_pre_slc_blk:
	.zero	2
	.section	.bss.c_ftl_nand_page_pre_super_blk,"aw",@nobits
	.align	1
	.set	.LANCHOR20,. + 0
	.type	c_ftl_nand_page_pre_super_blk, %object
	.size	c_ftl_nand_page_pre_super_blk, 2
c_ftl_nand_page_pre_super_blk:
	.zero	2
	.section	.bss.c_ftl_nand_planes_num,"aw",@nobits
	.align	1
	.set	.LANCHOR2,. + 0
	.type	c_ftl_nand_planes_num, %object
	.size	c_ftl_nand_planes_num, 2
c_ftl_nand_planes_num:
	.zero	2
	.section	.bss.c_ftl_nand_planes_per_die,"aw",@nobits
	.align	1
	.set	.LANCHOR10,. + 0
	.type	c_ftl_nand_planes_per_die, %object
	.size	c_ftl_nand_planes_per_die, 2
c_ftl_nand_planes_per_die:
	.zero	2
	.section	.bss.c_ftl_nand_reserved_blks,"aw",@nobits
	.align	1
	.set	.LANCHOR24,. + 0
	.type	c_ftl_nand_reserved_blks, %object
	.size	c_ftl_nand_reserved_blks, 2
c_ftl_nand_reserved_blks:
	.zero	2
	.section	.bss.c_ftl_nand_sec_pre_page,"aw",@nobits
	.align	1
	.set	.LANCHOR11,. + 0
	.type	c_ftl_nand_sec_pre_page, %object
	.size	c_ftl_nand_sec_pre_page, 2
c_ftl_nand_sec_pre_page:
	.zero	2
	.section	.bss.c_ftl_nand_sec_pre_page_shift,"aw",@nobits
	.align	1
	.set	.LANCHOR21,. + 0
	.type	c_ftl_nand_sec_pre_page_shift, %object
	.size	c_ftl_nand_sec_pre_page_shift, 2
c_ftl_nand_sec_pre_page_shift:
	.zero	2
	.section	.bss.c_ftl_nand_sys_blks_per_plane,"aw",@nobits
	.align	2
	.set	.LANCHOR1,. + 0
	.type	c_ftl_nand_sys_blks_per_plane, %object
	.size	c_ftl_nand_sys_blks_per_plane, 4
c_ftl_nand_sys_blks_per_plane:
	.zero	4
	.section	.bss.c_ftl_nand_totle_phy_blks,"aw",@nobits
	.align	2
	.set	.LANCHOR7,. + 0
	.type	c_ftl_nand_totle_phy_blks, %object
	.size	c_ftl_nand_totle_phy_blks, 4
c_ftl_nand_totle_phy_blks:
	.zero	4
	.section	.bss.c_ftl_nand_type,"aw",@nobits
	.align	1
	.set	.LANCHOR8,. + 0
	.type	c_ftl_nand_type, %object
	.size	c_ftl_nand_type, 2
c_ftl_nand_type:
	.zero	2
	.section	.bss.c_ftl_nand_vendor_region_num,"aw",@nobits
	.align	1
	.set	.LANCHOR27,. + 0
	.type	c_ftl_nand_vendor_region_num, %object
	.size	c_ftl_nand_vendor_region_num, 2
c_ftl_nand_vendor_region_num:
	.zero	2
	.section	.bss.c_ftl_vendor_part_size,"aw",@nobits
	.align	1
	.set	.LANCHOR15,. + 0
	.type	c_ftl_vendor_part_size, %object
	.size	c_ftl_vendor_part_size, 2
c_ftl_vendor_part_size:
	.zero	2
	.section	.bss.c_gc_page_buf_num,"aw",@nobits
	.align	2
	.set	.LANCHOR66,. + 0
	.type	c_gc_page_buf_num, %object
	.size	c_gc_page_buf_num, 4
c_gc_page_buf_num:
	.zero	4
	.section	.bss.c_mlc_erase_count_value,"aw",@nobits
	.align	1
	.set	.LANCHOR13,. + 0
	.type	c_mlc_erase_count_value, %object
	.size	c_mlc_erase_count_value, 2
c_mlc_erase_count_value:
	.zero	2
	.section	.bss.check_vpc_table,"aw",@nobits
	.align	3
	.type	check_vpc_table, %object
	.size	check_vpc_table, 16384
check_vpc_table:
	.zero	16384
	.section	.bss.ftl_gc_temp_power_lost_recovery_flag,"aw",@nobits
	.align	2
	.set	.LANCHOR132,. + 0
	.type	ftl_gc_temp_power_lost_recovery_flag, %object
	.size	ftl_gc_temp_power_lost_recovery_flag, 4
ftl_gc_temp_power_lost_recovery_flag:
	.zero	4
	.section	.bss.gBbtInfo,"aw",@nobits
	.align	3
	.set	.LANCHOR36,. + 0
	.type	gBbtInfo, %object
	.size	gBbtInfo, 96
gBbtInfo:
	.zero	96
	.section	.bss.gL2pMapInfo,"aw",@nobits
	.align	3
	.set	.LANCHOR128,. + 0
	.type	gL2pMapInfo, %object
	.size	gL2pMapInfo, 64
gL2pMapInfo:
	.zero	64
	.section	.bss.gSysFreeQueue,"aw",@nobits
	.align	3
	.set	.LANCHOR37,. + 0
	.type	gSysFreeQueue, %object
	.size	gSysFreeQueue, 2056
gSysFreeQueue:
	.zero	2056
	.section	.bss.gSysInfo,"aw",@nobits
	.align	3
	.set	.LANCHOR138,. + 0
	.type	gSysInfo, %object
	.size	gSysInfo, 16
gSysInfo:
	.zero	16
	.section	.bss.gVendorBlkInfo,"aw",@nobits
	.align	3
	.set	.LANCHOR160,. + 0
	.type	gVendorBlkInfo, %object
	.size	gVendorBlkInfo, 64
gVendorBlkInfo:
	.zero	64
	.section	.bss.g_GlobalDataVersion,"aw",@nobits
	.align	2
	.set	.LANCHOR82,. + 0
	.type	g_GlobalDataVersion, %object
	.size	g_GlobalDataVersion, 4
g_GlobalDataVersion:
	.zero	4
	.section	.bss.g_GlobalSysVersion,"aw",@nobits
	.align	2
	.set	.LANCHOR81,. + 0
	.type	g_GlobalSysVersion, %object
	.size	g_GlobalSysVersion, 4
g_GlobalSysVersion:
	.zero	4
	.section	.bss.g_MaxLbaSector,"aw",@nobits
	.align	2
	.set	.LANCHOR33,. + 0
	.type	g_MaxLbaSector, %object
	.size	g_MaxLbaSector, 4
g_MaxLbaSector:
	.zero	4
	.section	.bss.g_MaxLbn,"aw",@nobits
	.align	2
	.set	.LANCHOR178,. + 0
	.type	g_MaxLbn, %object
	.size	g_MaxLbn, 4
g_MaxLbn:
	.zero	4
	.section	.bss.g_MaxLpn,"aw",@nobits
	.align	2
	.set	.LANCHOR151,. + 0
	.type	g_MaxLpn, %object
	.size	g_MaxLpn, 4
g_MaxLpn:
	.zero	4
	.section	.bss.g_VaildLpn,"aw",@nobits
	.align	2
	.set	.LANCHOR58,. + 0
	.type	g_VaildLpn, %object
	.size	g_VaildLpn, 4
g_VaildLpn:
	.zero	4
	.section	.bss.g_active_superblock,"aw",@nobits
	.align	3
	.set	.LANCHOR50,. + 0
	.type	g_active_superblock, %object
	.size	g_active_superblock, 48
g_active_superblock:
	.zero	48
	.section	.bss.g_buffer_superblock,"aw",@nobits
	.align	3
	.set	.LANCHOR51,. + 0
	.type	g_buffer_superblock, %object
	.size	g_buffer_superblock, 48
g_buffer_superblock:
	.zero	48
	.section	.bss.g_cur_erase_blk,"aw",@nobits
	.align	2
	.set	.LANCHOR98,. + 0
	.type	g_cur_erase_blk, %object
	.size	g_cur_erase_blk, 4
g_cur_erase_blk:
	.zero	4
	.section	.bss.g_ect_tbl_info_size,"aw",@nobits
	.align	1
	.set	.LANCHOR115,. + 0
	.type	g_ect_tbl_info_size, %object
	.size	g_ect_tbl_info_size, 2
g_ect_tbl_info_size:
	.zero	2
	.section	.bss.g_ect_tbl_power_up_flush,"aw",@nobits
	.align	1
	.set	.LANCHOR163,. + 0
	.type	g_ect_tbl_power_up_flush, %object
	.size	g_ect_tbl_power_up_flush, 2
g_ect_tbl_power_up_flush:
	.zero	2
	.section	.bss.g_ftl_nand_free_count,"aw",@nobits
	.align	2
	.set	.LANCHOR175,. + 0
	.type	g_ftl_nand_free_count, %object
	.size	g_ftl_nand_free_count, 4
g_ftl_nand_free_count:
	.zero	4
	.section	.bss.g_gc_bad_block_gc_index,"aw",@nobits
	.align	1
	.set	.LANCHOR75,. + 0
	.type	g_gc_bad_block_gc_index, %object
	.size	g_gc_bad_block_gc_index, 2
g_gc_bad_block_gc_index:
	.zero	2
	.section	.bss.g_gc_bad_block_temp_num,"aw",@nobits
	.align	1
	.set	.LANCHOR73,. + 0
	.type	g_gc_bad_block_temp_num, %object
	.size	g_gc_bad_block_temp_num, 2
g_gc_bad_block_temp_num:
	.zero	2
	.section	.bss.g_gc_bad_block_temp_tbl,"aw",@nobits
	.align	3
	.set	.LANCHOR74,. + 0
	.type	g_gc_bad_block_temp_tbl, %object
	.size	g_gc_bad_block_temp_tbl, 34
g_gc_bad_block_temp_tbl:
	.zero	34
	.section	.bss.g_gc_blk_index,"aw",@nobits
	.align	1
	.set	.LANCHOR101,. + 0
	.type	g_gc_blk_index, %object
	.size	g_gc_blk_index, 2
g_gc_blk_index:
	.zero	2
	.section	.bss.g_gc_blk_num,"aw",@nobits
	.align	1
	.set	.LANCHOR67,. + 0
	.type	g_gc_blk_num, %object
	.size	g_gc_blk_num, 2
g_gc_blk_num:
	.zero	2
	.section	.bss.g_gc_cur_blk_max_valid_pages,"aw",@nobits
	.align	1
	.set	.LANCHOR173,. + 0
	.type	g_gc_cur_blk_max_valid_pages, %object
	.size	g_gc_cur_blk_max_valid_pages, 2
g_gc_cur_blk_max_valid_pages:
	.zero	2
	.section	.bss.g_gc_cur_blk_valid_pages,"aw",@nobits
	.align	1
	.set	.LANCHOR172,. + 0
	.type	g_gc_cur_blk_valid_pages, %object
	.size	g_gc_cur_blk_valid_pages, 2
g_gc_cur_blk_valid_pages:
	.zero	2
	.section	.bss.g_gc_free_blk_threshold,"aw",@nobits
	.align	1
	.set	.LANCHOR99,. + 0
	.type	g_gc_free_blk_threshold, %object
	.size	g_gc_free_blk_threshold, 2
g_gc_free_blk_threshold:
	.zero	2
	.section	.bss.g_gc_head_data_block,"aw",@nobits
	.align	2
	.set	.LANCHOR95,. + 0
	.type	g_gc_head_data_block, %object
	.size	g_gc_head_data_block, 4
g_gc_head_data_block:
	.zero	4
	.section	.bss.g_gc_head_data_block_count,"aw",@nobits
	.align	2
	.set	.LANCHOR96,. + 0
	.type	g_gc_head_data_block_count, %object
	.size	g_gc_head_data_block_count, 4
g_gc_head_data_block_count:
	.zero	4
	.section	.bss.g_gc_merge_free_blk_threshold,"aw",@nobits
	.align	1
	.set	.LANCHOR100,. + 0
	.type	g_gc_merge_free_blk_threshold, %object
	.size	g_gc_merge_free_blk_threshold, 2
g_gc_merge_free_blk_threshold:
	.zero	2
	.section	.bss.g_gc_next_blk,"aw",@nobits
	.align	1
	.set	.LANCHOR71,. + 0
	.type	g_gc_next_blk, %object
	.size	g_gc_next_blk, 2
g_gc_next_blk:
	.zero	2
	.section	.bss.g_gc_next_blk_1,"aw",@nobits
	.align	1
	.set	.LANCHOR72,. + 0
	.type	g_gc_next_blk_1, %object
	.size	g_gc_next_blk_1, 2
g_gc_next_blk_1:
	.zero	2
	.section	.bss.g_gc_num_req,"aw",@nobits
	.align	2
	.set	.LANCHOR61,. + 0
	.type	g_gc_num_req, %object
	.size	g_gc_num_req, 4
g_gc_num_req:
	.zero	4
	.section	.bss.g_gc_page_offset,"aw",@nobits
	.align	1
	.set	.LANCHOR69,. + 0
	.type	g_gc_page_offset, %object
	.size	g_gc_page_offset, 2
g_gc_page_offset:
	.zero	2
	.section	.bss.g_gc_skip_write_count,"aw",@nobits
	.align	2
	.set	.LANCHOR97,. + 0
	.type	g_gc_skip_write_count, %object
	.size	g_gc_skip_write_count, 4
g_gc_skip_write_count:
	.zero	4
	.section	.bss.g_gc_superblock,"aw",@nobits
	.align	3
	.set	.LANCHOR144,. + 0
	.type	g_gc_superblock, %object
	.size	g_gc_superblock, 48
g_gc_superblock:
	.zero	48
	.section	.bss.g_gc_temp_superblock,"aw",@nobits
	.align	3
	.set	.LANCHOR52,. + 0
	.type	g_gc_temp_superblock, %object
	.size	g_gc_temp_superblock, 48
g_gc_temp_superblock:
	.zero	48
	.section	.bss.g_in_gc_progress,"aw",@nobits
	.align	2
	.set	.LANCHOR93,. + 0
	.type	g_in_gc_progress, %object
	.size	g_in_gc_progress, 4
g_in_gc_progress:
	.zero	4
	.section	.bss.g_in_swl_replace,"aw",@nobits
	.align	2
	.set	.LANCHOR94,. + 0
	.type	g_in_swl_replace, %object
	.size	g_in_swl_replace, 4
g_in_swl_replace:
	.zero	4
	.section	.bss.g_l2p_last_update_region_id,"aw",@nobits
	.align	1
	.set	.LANCHOR55,. + 0
	.type	g_l2p_last_update_region_id, %object
	.size	g_l2p_last_update_region_id, 2
g_l2p_last_update_region_id:
	.zero	2
	.section	.bss.g_max_erase_count,"aw",@nobits
	.align	2
	.set	.LANCHOR91,. + 0
	.type	g_max_erase_count, %object
	.size	g_max_erase_count, 4
g_max_erase_count:
	.zero	4
	.section	.bss.g_min_erase_count,"aw",@nobits
	.align	2
	.set	.LANCHOR92,. + 0
	.type	g_min_erase_count, %object
	.size	g_min_erase_count, 4
g_min_erase_count:
	.zero	4
	.section	.bss.g_nand_ops,"aw",@nobits
	.align	3
	.set	.LANCHOR77,. + 0
	.type	g_nand_ops, %object
	.size	g_nand_ops, 48
g_nand_ops:
	.zero	48
	.section	.bss.g_nand_phy_info,"aw",@nobits
	.align	3
	.set	.LANCHOR0,. + 0
	.type	g_nand_phy_info, %object
	.size	g_nand_phy_info, 24
g_nand_phy_info:
	.zero	24
	.section	.bss.g_num_data_superblocks,"aw",@nobits
	.align	1
	.set	.LANCHOR43,. + 0
	.type	g_num_data_superblocks, %object
	.size	g_num_data_superblocks, 2
g_num_data_superblocks:
	.zero	2
	.section	.bss.g_num_free_superblocks,"aw",@nobits
	.align	1
	.set	.LANCHOR47,. + 0
	.type	g_num_free_superblocks, %object
	.size	g_num_free_superblocks, 2
g_num_free_superblocks:
	.zero	2
	.section	.bss.g_power_lost_recovery_flag,"aw",@nobits
	.align	1
	.set	.LANCHOR155,. + 0
	.type	g_power_lost_recovery_flag, %object
	.size	g_power_lost_recovery_flag, 2
g_power_lost_recovery_flag:
	.zero	2
	.section	.bss.g_recovery_page_min_ver,"aw",@nobits
	.align	2
	.set	.LANCHOR133,. + 0
	.type	g_recovery_page_min_ver, %object
	.size	g_recovery_page_min_ver, 4
g_recovery_page_min_ver:
	.zero	4
	.section	.bss.g_recovery_page_num,"aw",@nobits
	.align	2
	.set	.LANCHOR156,. + 0
	.type	g_recovery_page_num, %object
	.size	g_recovery_page_num, 4
g_recovery_page_num:
	.zero	4
	.section	.bss.g_recovery_ppa_tbl,"aw",@nobits
	.align	3
	.set	.LANCHOR157,. + 0
	.type	g_recovery_ppa_tbl, %object
	.size	g_recovery_ppa_tbl, 128
g_recovery_ppa_tbl:
	.zero	128
	.section	.bss.g_sys_ext_data,"aw",@nobits
	.align	3
	.set	.LANCHOR134,. + 0
	.type	g_sys_ext_data, %object
	.size	g_sys_ext_data, 512
g_sys_ext_data:
	.zero	512
	.section	.bss.g_sys_save_data,"aw",@nobits
	.align	3
	.set	.LANCHOR38,. + 0
	.type	g_sys_save_data, %object
	.size	g_sys_save_data, 48
g_sys_save_data:
	.zero	48
	.section	.bss.g_tmp_data_superblock_id,"aw",@nobits
	.align	1
	.set	.LANCHOR130,. + 0
	.type	g_tmp_data_superblock_id, %object
	.size	g_tmp_data_superblock_id, 2
g_tmp_data_superblock_id:
	.zero	2
	.section	.bss.g_totle_avg_erase_count,"aw",@nobits
	.align	2
	.set	.LANCHOR142,. + 0
	.type	g_totle_avg_erase_count, %object
	.size	g_totle_avg_erase_count, 4
g_totle_avg_erase_count:
	.zero	4
	.section	.bss.g_totle_cache_write_count,"aw",@nobits
	.align	2
	.set	.LANCHOR86,. + 0
	.type	g_totle_cache_write_count, %object
	.size	g_totle_cache_write_count, 4
g_totle_cache_write_count:
	.zero	4
	.section	.bss.g_totle_discard_page_count,"aw",@nobits
	.align	2
	.set	.LANCHOR85,. + 0
	.type	g_totle_discard_page_count, %object
	.size	g_totle_discard_page_count, 4
g_totle_discard_page_count:
	.zero	4
	.section	.bss.g_totle_gc_page_count,"aw",@nobits
	.align	2
	.set	.LANCHOR83,. + 0
	.type	g_totle_gc_page_count, %object
	.size	g_totle_gc_page_count, 4
g_totle_gc_page_count:
	.zero	4
	.section	.bss.g_totle_l2p_write_count,"aw",@nobits
	.align	2
	.set	.LANCHOR87,. + 0
	.type	g_totle_l2p_write_count, %object
	.size	g_totle_l2p_write_count, 4
g_totle_l2p_write_count:
	.zero	4
	.section	.bss.g_totle_map_block,"aw",@nobits
	.align	1
	.set	.LANCHOR129,. + 0
	.type	g_totle_map_block, %object
	.size	g_totle_map_block, 2
g_totle_map_block:
	.zero	2
	.section	.bss.g_totle_mlc_erase_count,"aw",@nobits
	.align	2
	.set	.LANCHOR89,. + 0
	.type	g_totle_mlc_erase_count, %object
	.size	g_totle_mlc_erase_count, 4
g_totle_mlc_erase_count:
	.zero	4
	.section	.bss.g_totle_read_page_count,"aw",@nobits
	.align	2
	.set	.LANCHOR88,. + 0
	.type	g_totle_read_page_count, %object
	.size	g_totle_read_page_count, 4
g_totle_read_page_count:
	.zero	4
	.section	.bss.g_totle_read_sector,"aw",@nobits
	.align	2
	.set	.LANCHOR162,. + 0
	.type	g_totle_read_sector, %object
	.size	g_totle_read_sector, 4
g_totle_read_sector:
	.zero	4
	.section	.bss.g_totle_slc_erase_count,"aw",@nobits
	.align	2
	.set	.LANCHOR90,. + 0
	.type	g_totle_slc_erase_count, %object
	.size	g_totle_slc_erase_count, 4
g_totle_slc_erase_count:
	.zero	4
	.section	.bss.g_totle_swl_count,"aw",@nobits
	.align	2
	.set	.LANCHOR131,. + 0
	.type	g_totle_swl_count, %object
	.size	g_totle_swl_count, 4
g_totle_swl_count:
	.zero	4
	.section	.bss.g_totle_sys_slc_erase_count,"aw",@nobits
	.align	2
	.set	.LANCHOR79,. + 0
	.type	g_totle_sys_slc_erase_count, %object
	.size	g_totle_sys_slc_erase_count, 4
g_totle_sys_slc_erase_count:
	.zero	4
	.section	.bss.g_totle_vendor_block,"aw",@nobits
	.align	1
	.set	.LANCHOR34,. + 0
	.type	g_totle_vendor_block, %object
	.size	g_totle_vendor_block, 2
g_totle_vendor_block:
	.zero	2
	.section	.bss.g_totle_write_page_count,"aw",@nobits
	.align	2
	.set	.LANCHOR84,. + 0
	.type	g_totle_write_page_count, %object
	.size	g_totle_write_page_count, 4
g_totle_write_page_count:
	.zero	4
	.section	.bss.g_totle_write_sector,"aw",@nobits
	.align	2
	.set	.LANCHOR161,. + 0
	.type	g_totle_write_sector, %object
	.size	g_totle_write_sector, 4
g_totle_write_sector:
	.zero	4
	.section	.bss.gc_discard_updated,"aw",@nobits
	.align	2
	.set	.LANCHOR166,. + 0
	.type	gc_discard_updated, %object
	.size	gc_discard_updated, 4
gc_discard_updated:
	.zero	4
	.section	.bss.gc_ink_free_return_value,"aw",@nobits
	.align	1
	.set	.LANCHOR171,. + 0
	.type	gc_ink_free_return_value, %object
	.size	gc_ink_free_return_value, 2
gc_ink_free_return_value:
	.zero	2
	.section	.bss.gp_ect_tbl_info,"aw",@nobits
	.align	3
	.set	.LANCHOR117,. + 0
	.type	gp_ect_tbl_info, %object
	.size	gp_ect_tbl_info, 8
gp_ect_tbl_info:
	.zero	8
	.section	.bss.gp_flash_check_buf,"aw",@nobits
	.align	3
	.set	.LANCHOR183,. + 0
	.type	gp_flash_check_buf, %object
	.size	gp_flash_check_buf, 8
gp_flash_check_buf:
	.zero	8
	.section	.bss.gp_gc_page_buf_info,"aw",@nobits
	.align	3
	.set	.LANCHOR62,. + 0
	.type	gp_gc_page_buf_info, %object
	.size	gp_gc_page_buf_info, 8
gp_gc_page_buf_info:
	.zero	8
	.section	.bss.gp_last_act_superblock,"aw",@nobits
	.align	3
	.type	gp_last_act_superblock, %object
	.size	gp_last_act_superblock, 8
gp_last_act_superblock:
	.zero	8
	.section	.bss.idb_buf,"aw",@nobits
	.align	3
	.set	.LANCHOR182,. + 0
	.type	idb_buf, %object
	.size	idb_buf, 8
idb_buf:
	.zero	8
	.section	.bss.idb_need_write_back,"aw",@nobits
	.align	2
	.set	.LANCHOR181,. + 0
	.type	idb_need_write_back, %object
	.size	idb_need_write_back, 4
idb_need_write_back:
	.zero	4
	.section	.bss.low_format_en,"aw",@nobits
	.align	2
	.set	.LANCHOR180,. + 0
	.type	low_format_en, %object
	.size	low_format_en, 4
low_format_en:
	.zero	4
	.section	.bss.p_data_block_list_head,"aw",@nobits
	.align	3
	.set	.LANCHOR40,. + 0
	.type	p_data_block_list_head, %object
	.size	p_data_block_list_head, 8
p_data_block_list_head:
	.zero	8
	.section	.bss.p_data_block_list_table,"aw",@nobits
	.align	3
	.set	.LANCHOR39,. + 0
	.type	p_data_block_list_table, %object
	.size	p_data_block_list_table, 8
p_data_block_list_table:
	.zero	8
	.section	.bss.p_data_block_list_tail,"aw",@nobits
	.align	3
	.set	.LANCHOR42,. + 0
	.type	p_data_block_list_tail, %object
	.size	p_data_block_list_tail, 8
p_data_block_list_tail:
	.zero	8
	.section	.bss.p_erase_count_table,"aw",@nobits
	.align	3
	.set	.LANCHOR46,. + 0
	.type	p_erase_count_table, %object
	.size	p_erase_count_table, 8
p_erase_count_table:
	.zero	8
	.section	.bss.p_free_data_block_list_head,"aw",@nobits
	.align	3
	.set	.LANCHOR45,. + 0
	.type	p_free_data_block_list_head, %object
	.size	p_free_data_block_list_head, 8
p_free_data_block_list_head:
	.zero	8
	.section	.bss.p_gc_blk_tbl,"aw",@nobits
	.align	3
	.set	.LANCHOR68,. + 0
	.type	p_gc_blk_tbl, %object
	.size	p_gc_blk_tbl, 8
p_gc_blk_tbl:
	.zero	8
	.section	.bss.p_gc_data_buf,"aw",@nobits
	.align	3
	.set	.LANCHOR63,. + 0
	.type	p_gc_data_buf, %object
	.size	p_gc_data_buf, 8
p_gc_data_buf:
	.zero	8
	.section	.bss.p_gc_page_info,"aw",@nobits
	.align	3
	.set	.LANCHOR70,. + 0
	.type	p_gc_page_info, %object
	.size	p_gc_page_info, 8
p_gc_page_info:
	.zero	8
	.section	.bss.p_gc_spare_buf,"aw",@nobits
	.align	3
	.set	.LANCHOR64,. + 0
	.type	p_gc_spare_buf, %object
	.size	p_gc_spare_buf, 8
p_gc_spare_buf:
	.zero	8
	.section	.bss.p_io_data_buf_0,"aw",@nobits
	.align	3
	.set	.LANCHOR108,. + 0
	.type	p_io_data_buf_0, %object
	.size	p_io_data_buf_0, 8
p_io_data_buf_0:
	.zero	8
	.section	.bss.p_io_data_buf_1,"aw",@nobits
	.align	3
	.set	.LANCHOR109,. + 0
	.type	p_io_data_buf_1, %object
	.size	p_io_data_buf_1, 8
p_io_data_buf_1:
	.zero	8
	.section	.bss.p_io_spare_buf,"aw",@nobits
	.align	3
	.set	.LANCHOR114,. + 0
	.type	p_io_spare_buf, %object
	.size	p_io_spare_buf, 8
p_io_spare_buf:
	.zero	8
	.section	.bss.p_l2p_map_buf,"aw",@nobits
	.align	3
	.set	.LANCHOR125,. + 0
	.type	p_l2p_map_buf, %object
	.size	p_l2p_map_buf, 8
p_l2p_map_buf:
	.zero	8
	.section	.bss.p_l2p_ram_map,"aw",@nobits
	.align	3
	.set	.LANCHOR54,. + 0
	.type	p_l2p_ram_map, %object
	.size	p_l2p_ram_map, 8
p_l2p_ram_map:
	.zero	8
	.section	.bss.p_map_block_table,"aw",@nobits
	.align	3
	.set	.LANCHOR118,. + 0
	.type	p_map_block_table, %object
	.size	p_map_block_table, 8
p_map_block_table:
	.zero	8
	.section	.bss.p_map_block_valid_page_count,"aw",@nobits
	.align	3
	.set	.LANCHOR119,. + 0
	.type	p_map_block_valid_page_count, %object
	.size	p_map_block_valid_page_count, 8
p_map_block_valid_page_count:
	.zero	8
	.section	.bss.p_map_block_ver_table,"aw",@nobits
	.align	3
	.set	.LANCHOR124,. + 0
	.type	p_map_block_ver_table, %object
	.size	p_map_block_ver_table, 8
p_map_block_ver_table:
	.zero	8
	.section	.bss.p_map_region_ppn_table,"aw",@nobits
	.align	3
	.set	.LANCHOR123,. + 0
	.type	p_map_region_ppn_table, %object
	.size	p_map_region_ppn_table, 8
p_map_region_ppn_table:
	.zero	8
	.section	.bss.p_plane_order_table,"aw",@nobits
	.align	3
	.set	.LANCHOR12,. + 0
	.type	p_plane_order_table, %object
	.size	p_plane_order_table, 32
p_plane_order_table:
	.zero	32
	.section	.bss.p_swl_mul_table,"aw",@nobits
	.align	3
	.set	.LANCHOR116,. + 0
	.type	p_swl_mul_table, %object
	.size	p_swl_mul_table, 8
p_swl_mul_table:
	.zero	8
	.section	.bss.p_sys_data_buf,"aw",@nobits
	.align	3
	.set	.LANCHOR105,. + 0
	.type	p_sys_data_buf, %object
	.size	p_sys_data_buf, 8
p_sys_data_buf:
	.zero	8
	.section	.bss.p_sys_data_buf_1,"aw",@nobits
	.align	3
	.set	.LANCHOR106,. + 0
	.type	p_sys_data_buf_1, %object
	.size	p_sys_data_buf_1, 8
p_sys_data_buf_1:
	.zero	8
	.section	.bss.p_sys_spare_buf,"aw",@nobits
	.align	3
	.set	.LANCHOR113,. + 0
	.type	p_sys_spare_buf, %object
	.size	p_sys_spare_buf, 8
p_sys_spare_buf:
	.zero	8
	.section	.bss.p_valid_page_count_check_table,"aw",@nobits
	.align	3
	.type	p_valid_page_count_check_table, %object
	.size	p_valid_page_count_check_table, 8
p_valid_page_count_check_table:
	.zero	8
	.section	.bss.p_valid_page_count_table,"aw",@nobits
	.align	3
	.set	.LANCHOR41,. + 0
	.type	p_valid_page_count_table, %object
	.size	p_valid_page_count_table, 8
p_valid_page_count_table:
	.zero	8
	.section	.bss.p_vendor_block_table,"aw",@nobits
	.align	3
	.set	.LANCHOR35,. + 0
	.type	p_vendor_block_table, %object
	.size	p_vendor_block_table, 8
p_vendor_block_table:
	.zero	8
	.section	.bss.p_vendor_block_valid_page_count,"aw",@nobits
	.align	3
	.set	.LANCHOR120,. + 0
	.type	p_vendor_block_valid_page_count, %object
	.size	p_vendor_block_valid_page_count, 8
p_vendor_block_valid_page_count:
	.zero	8
	.section	.bss.p_vendor_block_ver_table,"aw",@nobits
	.align	3
	.set	.LANCHOR121,. + 0
	.type	p_vendor_block_ver_table, %object
	.size	p_vendor_block_ver_table, 8
p_vendor_block_ver_table:
	.zero	8
	.section	.bss.p_vendor_data_buf,"aw",@nobits
	.align	3
	.set	.LANCHOR107,. + 0
	.type	p_vendor_data_buf, %object
	.size	p_vendor_data_buf, 8
p_vendor_data_buf:
	.zero	8
	.section	.bss.p_vendor_region_ppn_table,"aw",@nobits
	.align	3
	.set	.LANCHOR122,. + 0
	.type	p_vendor_region_ppn_table, %object
	.size	p_vendor_region_ppn_table, 8
p_vendor_region_ppn_table:
	.zero	8
	.section	.bss.req_erase,"aw",@nobits
	.align	3
	.set	.LANCHOR78,. + 0
	.type	req_erase, %object
	.size	req_erase, 8
req_erase:
	.zero	8
	.section	.bss.req_gc,"aw",@nobits
	.align	3
	.set	.LANCHOR65,. + 0
	.type	req_gc, %object
	.size	req_gc, 8
req_gc:
	.zero	8
	.section	.bss.req_gc_dst,"aw",@nobits
	.align	3
	.set	.LANCHOR103,. + 0
	.type	req_gc_dst, %object
	.size	req_gc_dst, 8
req_gc_dst:
	.zero	8
	.section	.bss.req_prgm,"aw",@nobits
	.align	3
	.set	.LANCHOR104,. + 0
	.type	req_prgm, %object
	.size	req_prgm, 8
req_prgm:
	.zero	8
	.section	.bss.req_read,"aw",@nobits
	.align	3
	.set	.LANCHOR102,. + 0
	.type	req_read, %object
	.size	req_read, 8
req_read:
	.zero	8
	.section	.bss.req_sys,"aw",@nobits
	.align	3
	.set	.LANCHOR137,. + 0
	.type	req_sys, %object
	.size	req_sys, 32
req_sys:
	.zero	32
	.section	.bss.sftl_nand_check_buf,"aw",@nobits
	.align	3
	.set	.LANCHOR110,. + 0
	.type	sftl_nand_check_buf, %object
	.size	sftl_nand_check_buf, 8
sftl_nand_check_buf:
	.zero	8
	.section	.bss.sftl_nand_check_spare_buf,"aw",@nobits
	.align	3
	.set	.LANCHOR112,. + 0
	.type	sftl_nand_check_spare_buf, %object
	.size	sftl_nand_check_spare_buf, 8
sftl_nand_check_spare_buf:
	.zero	8
	.section	.bss.sftl_temp_buf,"aw",@nobits
	.align	3
	.set	.LANCHOR111,. + 0
	.type	sftl_temp_buf, %object
	.size	sftl_temp_buf, 8
sftl_temp_buf:
	.zero	8
	.section	.data.ftl_gc_temp_block_bops_scan_page_addr,"aw",@progbits
	.align	1
	.set	.LANCHOR159,. + 0
	.type	ftl_gc_temp_block_bops_scan_page_addr, %object
	.size	ftl_gc_temp_block_bops_scan_page_addr, 2
ftl_gc_temp_block_bops_scan_page_addr:
	.hword	-1
	.section	.data.gFtlInitStatus,"aw",@progbits
	.align	2
	.set	.LANCHOR165,. + 0
	.type	gFtlInitStatus, %object
	.size	gFtlInitStatus, 4
gFtlInitStatus:
	.word	-1
	.section	.data.power_up_flag,"aw",@progbits
	.align	2
	.type	power_up_flag, %object
	.size	power_up_flag, 4
power_up_flag:
	.word	1
	.section	.rodata.FlashEraseBlocks.str1.1,"aMS",@progbits,1
.LC6:
	.string	"%s: addr: %x is in id block!!!!!!!!!!\n"
.LC7:
	.string	"not free: w: d:"
.LC8:
	.string	"not free: w: s:"
	.section	.rodata.FlashProgPages.str1.1,"aMS",@progbits,1
.LC14:
	.string	"prog read error: = %x\n"
.LC15:
	.string	"prog read REFRESH: = %x\n"
.LC16:
	.string	"prog read s error: = %x %x %x\n"
.LC17:
	.string	"prog read d error: = %x %x %x\n"
	.section	.rodata.FlashReadPages.str1.1,"aMS",@progbits,1
.LC11:
	.string	"FlashReadPages %x %x error_ecc_bits %d\n"
.LC12:
	.string	"data:"
.LC13:
	.string	"spare:"
	.section	.rodata.FtlBbmMapBadBlock.str1.1,"aMS",@progbits,1
.LC0:
	.string	"phyBlk = 0x%x die = %d block_in_die = 0x%x 0x%8x\n"
	.section	.rodata.FtlBbmTblFlush.str1.1,"aMS",@progbits,1
.LC18:
	.string	"FtlBbmTblFlush id=%x,page=%x,previd=%x cnt=%d\n"
.LC19:
	.string	"FtlBbmTblFlush error:%x\n"
.LC20:
	.string	"FtlBbmTblFlush error = %x error count = %d\n"
	.section	.rodata.FtlFreeSysBlkQueueOut.str1.1,"aMS",@progbits,1
.LC9:
	.string	"FtlFreeSysBlkQueueOut = %x, free count = %d, error\n"
	.section	.rodata.FtlGcScanTempBlk.str1.1,"aMS",@progbits,1
.LC35:
	.string	"FtlGcScanTempBlk Error ID %x %x!!!!!!! \n"
	.section	.rodata.FtlLoadEctTbl.str1.1,"aMS",@progbits,1
.LC37:
	.string	"no ect"
.LC38:
	.string	"%s\n"
	.section	.rodata.FtlLoadSysInfo.str1.1,"aMS",@progbits,1
.LC46:
	.string	"%s hash error this.id =%x page =%x pre_id =%x hash =%x hash_r =%x\n"
	.section	.rodata.FtlMapTblRecovery.str1.1,"aMS",@progbits,1
.LC47:
	.string	"%s last blk_id =%x page =%x hash error hash =%x hash_r =%x\n"
.LC48:
	.string	"%s scan blk_id =%x page =%x hash error hash =%x hash_r =%x\n"
	.section	.rodata.FtlMapWritePage.str1.1,"aMS",@progbits,1
.LC22:
	.string	"FtlMapWritePage error = %x \n"
.LC23:
	.string	"FtlMapWritePage error = %x error count = %d\n"
	.section	.rodata.FtlProgPages.str1.1,"aMS",@progbits,1
.LC40:
	.string	"FtlProgPages error %x = %d\n"
.LC41:
	.string	"Ftlwrite decrement_vpc_count %x = %d\n"
	.section	.rodata.FtlRecoverySuperblock.str1.1,"aMS",@progbits,1
.LC27:
	.string	"data prev_ppa = %x error...................\n"
.LC28:
	.string	"spuer block %x vpn is 0\n "
	.section	.rodata.FtlVendorPartRead.str1.1,"aMS",@progbits,1
.LC36:
	.string	"FtlVendorPartRead refresh = %x phyAddr = %x\n"
	.section	.rodata.FtlVpcTblFlush.str1.1,"aMS",@progbits,1
.LC39:
	.string	"FtlVpcTblFlush error = %x error count = %d\n"
	.section	.rodata.FtlWrite.str1.1,"aMS",@progbits,1
.LC44:
	.string	"FtlWrite: ecc error:%x %x %x\n"
.LC45:
	.string	"FtlWrite: lpa error:%x %x\n"
	.section	.rodata.FtlWriteToIDB.str1.1,"aMS",@progbits,1
.LC50:
	.string	"write_idblock %x %x\n"
.LC51:
	.string	"write_idblock fail! %x %x %x %x\n"
.LC52:
	.string	"%s idb buffer alloc fail\n"
	.section	.rodata.INSERT_DATA_LIST.str1.1,"aMS",@progbits,1
.LC1:
	.string	"\n!!!!! error @ func:%s - line:%d\n"
	.section	.rodata.__func__.6364,"a",@progbits
	.align	3
	.set	.LANCHOR168,. + 0
	.type	__func__.6364, %object
	.size	__func__.6364, 13
__func__.6364:
	.string	"FtlProgPages"
	.section	.rodata.__func__.6392,"a",@progbits
	.align	3
	.set	.LANCHOR176,. + 0
	.type	__func__.6392, %object
	.size	__func__.6392, 9
__func__.6392:
	.string	"FtlWrite"
	.section	.rodata.__func__.6474,"a",@progbits
	.align	3
	.set	.LANCHOR127,. + 0
	.type	__func__.6474, %object
	.size	__func__.6474, 14
__func__.6474:
	.string	"FtlBbt2Bitmap"
	.section	.rodata.__func__.6509,"a",@progbits
	.align	3
	.set	.LANCHOR140,. + 0
	.type	__func__.6509, %object
	.size	__func__.6509, 11
__func__.6509:
	.string	"FtlLoadBbt"
	.section	.rodata.__func__.6624,"a",@progbits
	.align	3
	.set	.LANCHOR48,. + 0
	.type	__func__.6624, %object
	.size	__func__.6624, 17
__func__.6624:
	.string	"INSERT_FREE_LIST"
	.section	.rodata.__func__.6629,"a",@progbits
	.align	3
	.set	.LANCHOR44,. + 0
	.type	__func__.6629, %object
	.size	__func__.6629, 17
__func__.6629:
	.string	"INSERT_DATA_LIST"
	.section	.rodata.__func__.6660,"a",@progbits
	.align	3
	.set	.LANCHOR49,. + 0
	.type	__func__.6660, %object
	.size	__func__.6660, 17
__func__.6660:
	.string	"List_remove_node"
	.section	.rodata.__func__.6692,"a",@progbits
	.align	3
	.set	.LANCHOR53,. + 0
	.type	__func__.6692, %object
	.size	__func__.6692, 22
__func__.6692:
	.string	"List_update_data_list"
	.section	.rodata.__func__.6701,"a",@progbits
	.align	3
	.set	.LANCHOR149,. + 0
	.type	__func__.6701, %object
	.size	__func__.6701, 16
__func__.6701:
	.string	"load_l2p_region"
	.section	.rodata.__func__.6734,"a",@progbits
	.align	3
	.set	.LANCHOR80,. + 0
	.type	__func__.6734, %object
	.size	__func__.6734, 26
__func__.6734:
	.string	"ftl_map_blk_alloc_new_blk"
	.section	.rodata.__func__.6745,"a",@progbits
	.align	3
	.set	.LANCHOR150,. + 0
	.type	__func__.6745, %object
	.size	__func__.6745, 15
__func__.6745:
	.string	"ftl_map_blk_gc"
	.section	.rodata.__func__.6760,"a",@progbits
	.align	3
	.set	.LANCHOR147,. + 0
	.type	__func__.6760, %object
	.size	__func__.6760, 31
__func__.6760:
	.string	"Ftl_write_map_blk_to_last_page"
	.section	.rodata.__func__.6774,"a",@progbits
	.align	3
	.set	.LANCHOR148,. + 0
	.type	__func__.6774, %object
	.size	__func__.6774, 16
__func__.6774:
	.string	"FtlMapWritePage"
	.section	.rodata.__func__.6799,"a",@progbits
	.align	3
	.set	.LANCHOR56,. + 0
	.type	__func__.6799, %object
	.size	__func__.6799, 22
__func__.6799:
	.string	"select_l2p_ram_region"
	.section	.rodata.__func__.6816,"a",@progbits
	.align	3
	.set	.LANCHOR152,. + 0
	.type	__func__.6816, %object
	.size	__func__.6816, 9
__func__.6816:
	.string	"log2phys"
	.section	.rodata.__func__.6880,"a",@progbits
	.align	3
	.set	.LANCHOR164,. + 0
	.type	__func__.6880, %object
	.size	__func__.6880, 15
__func__.6880:
	.string	"FtlVpcTblFlush"
	.section	.rodata.__func__.6902,"a",@progbits
	.align	3
	.set	.LANCHOR139,. + 0
	.type	__func__.6902, %object
	.size	__func__.6902, 14
__func__.6902:
	.string	"FtlScanSysBlk"
	.section	.rodata.__func__.6951,"a",@progbits
	.align	3
	.set	.LANCHOR177,. + 0
	.type	__func__.6951, %object
	.size	__func__.6951, 15
__func__.6951:
	.string	"FtlLoadSysInfo"
	.section	.rodata.__func__.6973,"a",@progbits
	.align	3
	.set	.LANCHOR179,. + 0
	.type	__func__.6973, %object
	.size	__func__.6973, 18
__func__.6973:
	.string	"FtlMapTblRecovery"
	.section	.rodata.__func__.7019,"a",@progbits
	.align	3
	.set	.LANCHOR153,. + 0
	.type	__func__.7019, %object
	.size	__func__.7019, 16
__func__.7019:
	.string	"FtlReUsePrevPpa"
	.section	.rodata.__func__.7053,"a",@progbits
	.align	3
	.set	.LANCHOR154,. + 0
	.type	__func__.7053, %object
	.size	__func__.7053, 22
__func__.7053:
	.string	"FtlRecoverySuperblock"
	.section	.rodata.__func__.7110,"a",@progbits
	.align	3
	.set	.LANCHOR59,. + 0
	.type	__func__.7110, %object
	.size	__func__.7110, 16
__func__.7110:
	.string	"make_superblock"
	.section	.rodata.__func__.7131,"a",@progbits
	.align	3
	.set	.LANCHOR135,. + 0
	.type	__func__.7131, %object
	.size	__func__.7131, 18
__func__.7131:
	.string	"SupperBlkListInit"
	.section	.rodata.__func__.7158,"a",@progbits
	.align	3
	.set	.LANCHOR158,. + 0
	.type	__func__.7158, %object
	.size	__func__.7158, 14
__func__.7158:
	.string	"ftl_check_vpc"
	.section	.rodata.__func__.7223,"a",@progbits
	.align	3
	.set	.LANCHOR143,. + 0
	.type	__func__.7223, %object
	.size	__func__.7223, 25
__func__.7223:
	.string	"allocate_data_superblock"
	.section	.rodata.__func__.7244,"a",@progbits
	.align	3
	.set	.LANCHOR167,. + 0
	.type	__func__.7244, %object
	.size	__func__.7244, 29
__func__.7244:
	.string	"allocate_new_data_superblock"
	.section	.rodata.__func__.7251,"a",@progbits
	.align	3
	.set	.LANCHOR60,. + 0
	.type	__func__.7251, %object
	.size	__func__.7251, 19
__func__.7251:
	.string	"get_new_active_ppa"
	.section	.rodata.__func__.7264,"a",@progbits
	.align	3
	.set	.LANCHOR145,. + 0
	.type	__func__.7264, %object
	.size	__func__.7264, 16
__func__.7264:
	.string	"update_vpc_list"
	.section	.rodata.__func__.7271,"a",@progbits
	.align	3
	.set	.LANCHOR146,. + 0
	.type	__func__.7271, %object
	.size	__func__.7271, 20
__func__.7271:
	.string	"decrement_vpc_count"
	.section	.rodata.__func__.7341,"a",@progbits
	.align	3
	.set	.LANCHOR169,. + 0
	.type	__func__.7341, %object
	.size	__func__.7341, 19
__func__.7341:
	.string	"FtlGcFreeTempBlock"
	.section	.rodata.__func__.7440,"a",@progbits
	.align	3
	.set	.LANCHOR174,. + 0
	.type	__func__.7440, %object
	.size	__func__.7440, 23
__func__.7440:
	.string	"rk_ftl_garbage_collect"
	.section	.rodata.__func__.7708,"a",@progbits
	.align	3
	.set	.LANCHOR136,. + 0
	.type	__func__.7708, %object
	.size	__func__.7708, 15
__func__.7708:
	.string	"FlashReadPages"
	.section	.rodata.__func__.7727,"a",@progbits
	.align	3
	.set	.LANCHOR141,. + 0
	.type	__func__.7727, %object
	.size	__func__.7727, 15
__func__.7727:
	.string	"FlashProgPages"
	.section	.rodata.__func__.7751,"a",@progbits
	.align	3
	.set	.LANCHOR76,. + 0
	.type	__func__.7751, %object
	.size	__func__.7751, 17
__func__.7751:
	.string	"FlashEraseBlocks"
	.section	.rodata.__func__.7870,"a",@progbits
	.align	3
	.set	.LANCHOR184,. + 0
	.type	__func__.7870, %object
	.size	__func__.7870, 14
__func__.7870:
	.string	"FtlWriteToIDB"
	.section	.rodata.decrement_vpc_count.str1.1,"aMS",@progbits,1
.LC21:
	.string	"decrement_vpc_count %x = %d\n"
	.section	.rodata.ftl_check_vpc.str1.1,"aMS",@progbits,1
.LC29:
	.string	"...%s enter...\n"
.LC30:
	.string	"FtlCheckVpc2 %x = %x  %x\n"
.LC31:
	.string	"free blk vpc error %x = %x  %x\n"
	.section	.rodata.ftl_map_blk_alloc_new_blk.str1.1,"aMS",@progbits,1
.LC10:
	.string	"FtlFreeSysBlkQueueOut = %x, free count = %d\n"
	.section	.rodata.ftl_scan_all_data.str1.1,"aMS",@progbits,1
.LC32:
	.string	"ftl_scan_all_data = %x\n"
.LC33:
	.string	"scan lpa = %x ppa= %x\n"
.LC34:
	.string	"lpa = %x,addr= %x,spare= %x %x %x %x data=%x %x\n"
	.section	.rodata.load_l2p_region.str1.1,"aMS",@progbits,1
.LC24:
	.string	"region_id = %x phyAddr = %x\n"
.LC25:
	.string	"map_ppn:"
.LC26:
	.string	"load_l2p_region refresh = %x phyAddr = %x\n"
	.section	.rodata.rk_ftl_garbage_collect.str1.1,"aMS",@progbits,1
.LC42:
	.string	"g_gc_superblock_free %x %x %x %x %x\n"
.LC43:
	.string	"lpa=%x, ppa=%x\n"
	.section	.rodata.rknand_print_hex.str1.1,"aMS",@progbits,1
.LC2:
	.string	"%s 0x%x:"
.LC3:
	.string	"%x "
.LC4:
	.string	"%02x "
.LC5:
	.string	"\n"
	.section	.rodata.sftl_init.str1.1,"aMS",@progbits,1
.LC49:
	.string	"SFTL version: 5.0.56 20210329"
	.hidden	free
