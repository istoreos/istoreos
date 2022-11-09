/* SPDX-License-Identifier:     GPL-2.0+ */
/*
 * (C) Copyright 2021 Rockchip Electronics Co., Ltd
 */

#include <config.h>

#ifdef CONFIG_ARM64
/*
 * Switch from AArch64 EL2 to AArch32 EL2
 *
 * @param inputs:
 * x0: argument, zero
 * x1: machine nr
 * x2: fdt address
 * x3: input argument
 * x4: kernel entry point
 *
 * @param outputs for secure firmware:
 * x0: function id
 * x1: kernel entry point
 * x2: machine nr
 * x3: fdt address
 * x4: input argument
 */
.global armv8_el2_to_aarch32
armv8_el2_to_aarch32:
	mov x0, x3
	mov x3, x2
	mov x2, x1
	mov x1, x4
	mov x4, x0
	ldr x0, =0x82000023
	smc #0
	ret
#endif

