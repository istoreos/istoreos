/*
 * (C) Copyright 2017 Rockchip Electronics Co., Ltd
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */

	/* Please keep them sorted based on the CRn register */
	.macro read_midr reg
	mrc     p15, 0, \reg, c0, c0, 0
	.endm

	.macro read_ctr reg
	mrc	p15, 0, \reg, c0, c0, 1
	.endm

	.macro read_mpidr reg
	mrc	p15, 0, \reg, c0, c0, 5
	.endm

	.macro read_sctlr reg
	mrc	p15, 0, \reg, c1, c0, 0
	.endm

	.macro write_sctlr reg
	mcr	p15, 0, \reg, c1, c0, 0
	.endm

	.macro write_actlr reg
	mcr	p15, 0, \reg, c1, c0, 1
	.endm

	.macro read_actlr reg
	mrc	p15, 0, \reg, c1, c0, 1
	.endm

	.macro write_cpacr reg
	mcr	p15, 0, \reg, c1, c0, 2
	.endm

	.macro read_cpacr reg
	mrc	p15, 0, \reg, c1, c0, 2
	.endm

	.macro read_scr reg
	mrc	p15, 0, \reg, c1, c1, 0
	.endm

	.macro write_scr reg
	mcr	p15, 0, \reg, c1, c1, 0
	.endm

	.macro write_nsacr reg
	mcr	p15, 0, \reg, c1, c1, 2
	.endm

	.macro read_nsacr reg
	mrc	p15, 0, \reg, c1, c1, 2
	.endm

	.macro write_ttbr0 reg
	mcr	p15, 0, \reg, c2, c0, 0
	.endm

	.macro read_ttbr0 reg
	mrc	p15, 0, \reg, c2, c0, 0
	.endm

	.macro write_ttbr1 reg
	mcr	p15, 0, \reg, c2, c0, 1
	.endm

	.macro read_ttbr1 reg
	mrc	p15, 0, \reg, c2, c0, 1
	.endm

	.macro write_ttbcr reg
	mcr	p15, 0, \reg, c2, c0, 2
	.endm

	.macro read_ttbcr reg
	mrc	p15, 0, \reg, c2, c0, 2
	.endm


	.macro write_dacr reg
	mcr	p15, 0, \reg, c3, c0, 0
	.endm

	.macro read_dacr reg
	mrc	p15, 0, \reg, c3, c0, 0
	.endm

	.macro read_dfsr reg
	mrc	p15, 0, \reg, c5, c0, 0
	.endm

	.macro write_icialluis
	/*
	 * Invalidate all instruction caches to PoU, Inner Shareable
	 * (register ignored)
	 */
	mcr	p15, 0, r0, c7, c1, 0
	.endm

	.macro write_bpiallis
	/*
	 * Invalidate entire branch predictor array, Inner Shareable
	 * (register ignored)
	 */
	mcr	p15, 0, r0, c7, c1, 6
	.endm

	.macro write_iciallu
	/* Invalidate all instruction caches to PoU (register ignored) */
	mcr	p15, 0, r0, c7, c5, 0
	.endm

	.macro write_icimvau reg
	/* Instruction cache invalidate by MVA */
	mcr	p15, 0, \reg, c7, c5, 1
	.endm

	.macro write_bpiall
	/* Invalidate entire branch predictor array (register ignored) */
	mcr	p15, 0, r0, c7, c5, 6
	.endm

	.macro write_dcimvac reg
	/* Data cache invalidate by MVA */
	mcr	p15, 0, \reg, c7, c6, 1
	.endm

	.macro write_dcisw reg
	/* Data cache invalidate by set/way */
	mcr	p15, 0, \reg, c7, c6, 2
	.endm

	.macro write_dccmvac reg
	/* Data cache clean by MVA */
	mcr	p15, 0, \reg, c7, c10, 1
	.endm

	.macro write_dccsw reg
	/* Data cache clean by set/way */
	mcr	p15, 0, \reg, c7, c10, 2
	.endm

	.macro write_dccimvac reg
	/* Data cache invalidate by MVA */
	mcr	p15, 0, \reg, c7, c14, 1
	.endm

	.macro write_dccisw reg
	/* Data cache clean and invalidate by set/way */
	mcr	p15, 0, \reg, c7, c14, 2
	.endm

	.macro write_tlbiall
	/* Invalidate entire unified TLB (register ignored) */
	mcr	p15, 0, r0, c8, c7, 0
	.endm

	.macro write_tlbiallis
	/* Invalidate entire unified TLB Inner Sharable (register ignored) */
	mcr	p15, 0, r0, c8, c3, 0
	.endm

	.macro write_tlbiasidis reg
	/* Invalidate unified TLB by ASID Inner Sharable */
	mcr	p15, 0, \reg, c8, c3, 2
	.endm

	.macro write_tlbimvaais reg
	/* Invalidate unified TLB by MVA all ASID Inner Sharable */
	mcr	p15, 0, \reg, c8, c3, 3
	.endm

	.macro write_prrr reg
	mcr	p15, 0, \reg, c10, c2, 0
	.endm

	.macro read_prrr reg
	mrc	p15, 0, \reg, c10, c2, 0
	.endm

	.macro write_nmrr reg
	mcr	p15, 0, \reg, c10, c2, 1
	.endm

	.macro read_nmrr reg
	mrc	p15, 0, \reg, c10, c2, 1
	.endm

	.macro read_vbar reg
	mrc	p15, 0, \reg, c12, c0, 0
	.endm

	.macro write_vbar reg
	mcr	p15, 0, \reg, c12, c0, 0
	.endm

	.macro write_mvbar reg
	mcr	p15, 0, \reg, c12, c0, 1
	.endm

	.macro read_mvbar reg
	mrc	p15, 0, \reg, c12, c0, 1
	.endm

	.macro write_fcseidr reg
	mcr	p15, 0, \reg, c13, c0, 0
	.endm

	.macro read_fcseidr reg
	mrc	p15, 0, \reg, c13, c0, 0
	.endm

	.macro write_contextidr reg
	mcr	p15, 0, \reg, c13, c0, 1
	.endm

	.macro read_contextidr reg
	mrc	p15, 0, \reg, c13, c0, 1
	.endm

	.macro write_tpidruro reg
	mcr	p15, 0, \reg, c13, c0, 3
	.endm

	.macro read_tpidruro reg
	mrc	p15, 0, \reg, c13, c0, 3
	.endm

	.macro read_clidr reg
	/* Cache Level ID Register */
	mrc	p15, 1, \reg, c0, c0, 1
	.endm

	.macro read_ccsidr reg
	/* Cache Size ID Registers */
	mrc	p15, 1, \reg, c0, c0, 0
	.endm

	.macro write_csselr reg
	/* Cache Size Selection Register */
	mcr	p15, 2, \reg, c0, c0, 0
	.endm

	/* Cortex A9: pcr, diag registers */
	.macro write_pcr reg
	mcr  p15, 0, \reg, c15, c0, 0
	.endm

	.macro read_pcr reg
	mrc  p15, 0, \reg, c15, c0, 0
	.endm

	.macro write_diag reg
	mcr  p15, 0, \reg, c15, c0, 1
	.endm

	.macro read_diag reg
	mrc  p15, 0, \reg, c15, c0, 1
	.endm
