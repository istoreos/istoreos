/*
 * Copyright 2017, Rockchip Electronics Co., Ltd
 * hisping lin, <hisping.lin@rock-chips.com>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <linux/linkage.h>

#ifdef CONFIG_ARM64
	.text

#define SMC_PARAM_W0_OFFS	0
#define SMC_PARAM_W2_OFFS	8
#define SMC_PARAM_W4_OFFS	16
#define SMC_PARAM_W6_OFFS	24

	/* void tee_smc_call(struct smc_param *param); */
	.globl	tee_smc_call
ENTRY(tee_smc_call)
	stp	x28, x30, [sp, #-16]!
	mov	x28, x0
	ldp	w0, w1, [x28, #SMC_PARAM_W0_OFFS]
	ldp	w2, w3, [x28, #SMC_PARAM_W2_OFFS]
	ldp	w4, w5, [x28, #SMC_PARAM_W4_OFFS]
	ldp	w6, w7, [x28, #SMC_PARAM_W6_OFFS]
	smc	#0
	stp	w0, w1, [x28, #SMC_PARAM_W0_OFFS]
	stp	w2, w3, [x28, #SMC_PARAM_W2_OFFS]
	ldp	x28, x30, [sp], #16
	ret
ENDPROC(tee_smc_call)

#else

.text
.balign 4
.code 32

	/* void tee_smc_call(struct smc_param *param); */
	.globl	tee_smc_call
ENTRY(tee_smc_call)
	push	{r4-r8, lr}
	mov	r8, r0
	ldm	r8, {r0-r7}
.arch_extension sec
	smc	#0
	stm	r8, {r0-r7}
	pop	{r4-r8, pc}
ENDPROC(tee_smc_call)
#endif
