// SPDX-License-Identifier: GPL-2.0 OR MIT
/*
 * Copyright (C) 2015-2019 Jason A. Donenfeld <Jason@zx2c4.com>. All Rights Reserved.
 *
 * Implementation of the ChaCha20 stream cipher.
 *
 * Information: https://cr.yp.to/chacha.html
 */

#include <zinc/chacha20.h>
#include "../selftest/run.h"

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/vmalloc.h>
#include <crypto/algapi.h> // For crypto_xor_cpy.

#if defined(CONFIG_ZINC_ARCH_X86_64)
#include "chacha20-x86_64-glue.c"
#elif defined(CONFIG_ZINC_ARCH_ARM) || defined(CONFIG_ZINC_ARCH_ARM64)
#include "chacha20-arm-glue.c"
#elif defined(CONFIG_ZINC_ARCH_MIPS)
#include "chacha20-mips-glue.c"
#else
static bool *const chacha20_nobs[] __initconst = { };
static void __init chacha20_fpu_init(void)
{
}
static inline bool chacha20_arch(struct chacha20_ctx *ctx, u8 *dst,
				 const u8 *src, size_t len,
				 simd_context_t *simd_context)
{
	return false;
}
static inline bool hchacha20_arch(u32 derived_key[CHACHA20_KEY_WORDS],
				  const u8 nonce[HCHACHA20_NONCE_SIZE],
				  const u8 key[HCHACHA20_KEY_SIZE],
				  simd_context_t *simd_context)
{
	return false;
}
#endif

#define QUARTER_ROUND(x, a, b, c, d) ( \
	x[a] += x[b], \
	x[d] = rol32((x[d] ^ x[a]), 16), \
	x[c] += x[d], \
	x[b] = rol32((x[b] ^ x[c]), 12), \
	x[a] += x[b], \
	x[d] = rol32((x[d] ^ x[a]), 8), \
	x[c] += x[d], \
	x[b] = rol32((x[b] ^ x[c]), 7) \
)

#define C(i, j) (i * 4 + j)

#define DOUBLE_ROUND(x) ( \
	/* Column Round */ \
	QUARTER_ROUND(x, C(0, 0), C(1, 0), C(2, 0), C(3, 0)), \
	QUARTER_ROUND(x, C(0, 1), C(1, 1), C(2, 1), C(3, 1)), \
	QUARTER_ROUND(x, C(0, 2), C(1, 2), C(2, 2), C(3, 2)), \
	QUARTER_ROUND(x, C(0, 3), C(1, 3), C(2, 3), C(3, 3)), \
	/* Diagonal Round */ \
	QUARTER_ROUND(x, C(0, 0), C(1, 1), C(2, 2), C(3, 3)), \
	QUARTER_ROUND(x, C(0, 1), C(1, 2), C(2, 3), C(3, 0)), \
	QUARTER_ROUND(x, C(0, 2), C(1, 3), C(2, 0), C(3, 1)), \
	QUARTER_ROUND(x, C(0, 3), C(1, 0), C(2, 1), C(3, 2)) \
)

#define TWENTY_ROUNDS(x) ( \
	DOUBLE_ROUND(x), \
	DOUBLE_ROUND(x), \
	DOUBLE_ROUND(x), \
	DOUBLE_ROUND(x), \
	DOUBLE_ROUND(x), \
	DOUBLE_ROUND(x), \
	DOUBLE_ROUND(x), \
	DOUBLE_ROUND(x), \
	DOUBLE_ROUND(x), \
	DOUBLE_ROUND(x) \
)

static void chacha20_block_generic(struct chacha20_ctx *ctx, __le32 *stream)
{
	u32 x[CHACHA20_BLOCK_WORDS];
	int i;

	for (i = 0; i < ARRAY_SIZE(x); ++i)
		x[i] = ctx->state[i];

	TWENTY_ROUNDS(x);

	for (i = 0; i < ARRAY_SIZE(x); ++i)
		stream[i] = cpu_to_le32(x[i] + ctx->state[i]);

	ctx->counter[0] += 1;
}

static void chacha20_generic(struct chacha20_ctx *ctx, u8 *out, const u8 *in,
			     u32 len)
{
	__le32 buf[CHACHA20_BLOCK_WORDS];

	while (len >= CHACHA20_BLOCK_SIZE) {
		chacha20_block_generic(ctx, buf);
		crypto_xor_cpy(out, in, (u8 *)buf, CHACHA20_BLOCK_SIZE);
		len -= CHACHA20_BLOCK_SIZE;
		out += CHACHA20_BLOCK_SIZE;
		in += CHACHA20_BLOCK_SIZE;
	}
	if (len) {
		chacha20_block_generic(ctx, buf);
		crypto_xor_cpy(out, in, (u8 *)buf, len);
	}
}

void chacha20(struct chacha20_ctx *ctx, u8 *dst, const u8 *src, u32 len,
	      simd_context_t *simd_context)
{
	if (!chacha20_arch(ctx, dst, src, len, simd_context))
		chacha20_generic(ctx, dst, src, len);
}

static void hchacha20_generic(u32 derived_key[CHACHA20_KEY_WORDS],
			      const u8 nonce[HCHACHA20_NONCE_SIZE],
			      const u8 key[HCHACHA20_KEY_SIZE])
{
	u32 x[] = { CHACHA20_CONSTANT_EXPA,
		    CHACHA20_CONSTANT_ND_3,
		    CHACHA20_CONSTANT_2_BY,
		    CHACHA20_CONSTANT_TE_K,
		    get_unaligned_le32(key +  0),
		    get_unaligned_le32(key +  4),
		    get_unaligned_le32(key +  8),
		    get_unaligned_le32(key + 12),
		    get_unaligned_le32(key + 16),
		    get_unaligned_le32(key + 20),
		    get_unaligned_le32(key + 24),
		    get_unaligned_le32(key + 28),
		    get_unaligned_le32(nonce +  0),
		    get_unaligned_le32(nonce +  4),
		    get_unaligned_le32(nonce +  8),
		    get_unaligned_le32(nonce + 12)
	};

	TWENTY_ROUNDS(x);

	memcpy(derived_key + 0, x +  0, sizeof(u32) * 4);
	memcpy(derived_key + 4, x + 12, sizeof(u32) * 4);
}

/* Derived key should be 32-bit aligned */
void hchacha20(u32 derived_key[CHACHA20_KEY_WORDS],
	       const u8 nonce[HCHACHA20_NONCE_SIZE],
	       const u8 key[HCHACHA20_KEY_SIZE], simd_context_t *simd_context)
{
	if (!hchacha20_arch(derived_key, nonce, key, simd_context))
		hchacha20_generic(derived_key, nonce, key);
}

#include "../selftest/chacha20.c"

static bool nosimd __initdata = false;

#ifndef COMPAT_ZINC_IS_A_MODULE
int __init chacha20_mod_init(void)
#else
static int __init mod_init(void)
#endif
{
	if (!nosimd)
		chacha20_fpu_init();
	if (!selftest_run("chacha20", chacha20_selftest, chacha20_nobs,
			  ARRAY_SIZE(chacha20_nobs)))
		return -ENOTRECOVERABLE;
	return 0;
}

#ifdef COMPAT_ZINC_IS_A_MODULE
static void __exit mod_exit(void)
{
}

module_param(nosimd, bool, 0);
module_init(mod_init);
module_exit(mod_exit);
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("ChaCha20 stream cipher");
MODULE_AUTHOR("Jason A. Donenfeld <Jason@zx2c4.com>");
#endif
