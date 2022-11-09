// SPDX-License-Identifier: GPL-2.0 OR MIT
/*
 * Copyright (C) 2015-2019 Jason A. Donenfeld <Jason@zx2c4.com>. All Rights Reserved.
 */

#include <linux/simd.h>
#include <asm/cpufeature.h>
#include <asm/processor.h>
#include <asm/fpu/api.h>

asmlinkage void blake2s_compress_ssse3(struct blake2s_state *state,
				       const u8 *block, const size_t nblocks,
				       const u32 inc);
asmlinkage void blake2s_compress_avx512(struct blake2s_state *state,
					const u8 *block, const size_t nblocks,
					const u32 inc);

static bool blake2s_use_ssse3 __ro_after_init;
static bool blake2s_use_avx512 __ro_after_init;
static bool *const blake2s_nobs[] __initconst = { &blake2s_use_ssse3,
						  &blake2s_use_avx512 };

static void __init blake2s_fpu_init(void)
{
	blake2s_use_ssse3 = boot_cpu_has(X86_FEATURE_SSSE3);
#ifndef COMPAT_CANNOT_USE_AVX512
	blake2s_use_avx512 =
		boot_cpu_has(X86_FEATURE_AVX) &&
		boot_cpu_has(X86_FEATURE_AVX2) &&
		boot_cpu_has(X86_FEATURE_AVX512F) &&
		boot_cpu_has(X86_FEATURE_AVX512VL) &&
		cpu_has_xfeatures(XFEATURE_MASK_SSE | XFEATURE_MASK_YMM |
				  XFEATURE_MASK_AVX512, NULL);
#endif
}

static inline bool blake2s_compress_arch(struct blake2s_state *state,
					 const u8 *block, size_t nblocks,
					 const u32 inc)
{
	simd_context_t simd_context;
	bool used_arch = false;

	/* SIMD disables preemption, so relax after processing each page. */
	BUILD_BUG_ON(PAGE_SIZE / BLAKE2S_BLOCK_SIZE < 8);

	simd_get(&simd_context);

	if (!IS_ENABLED(CONFIG_AS_SSSE3) || !blake2s_use_ssse3 ||
	    !simd_use(&simd_context))
		goto out;
	used_arch = true;

	for (;;) {
		const size_t blocks = min_t(size_t, nblocks,
					    PAGE_SIZE / BLAKE2S_BLOCK_SIZE);

		if (IS_ENABLED(CONFIG_AS_AVX512) && blake2s_use_avx512)
			blake2s_compress_avx512(state, block, blocks, inc);
		else
			blake2s_compress_ssse3(state, block, blocks, inc);

		nblocks -= blocks;
		if (!nblocks)
			break;
		block += blocks * BLAKE2S_BLOCK_SIZE;
		simd_relax(&simd_context);
	}
out:
	simd_put(&simd_context);
	return used_arch;
}
