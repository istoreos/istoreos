// SPDX-License-Identifier: GPL-2.0 OR MIT
/*
 * Copyright (C) 2015-2019 Jason A. Donenfeld <Jason@zx2c4.com>. All Rights Reserved.
 *
 * This is an implementation of the Curve25519 ECDH algorithm, using either
 * a 32-bit implementation or a 64-bit implementation with 128-bit integers,
 * depending on what is supported by the target compiler.
 *
 * Information: https://cr.yp.to/ecdh.html
 */

#include <zinc/curve25519.h>
#include "../selftest/run.h"

#include <asm/unaligned.h>
#include <linux/version.h>
#include <linux/string.h>
#include <linux/random.h>
#include <linux/module.h>
#include <linux/init.h>
#include <crypto/algapi.h> // For crypto_memneq.

#if defined(CONFIG_ZINC_ARCH_X86_64)
#include "curve25519-x86_64-glue.c"
#elif defined(CONFIG_ZINC_ARCH_ARM)
#include "curve25519-arm-glue.c"
#else
static bool *const curve25519_nobs[] __initconst = { };
static void __init curve25519_fpu_init(void)
{
}
static inline bool curve25519_arch(u8 mypublic[CURVE25519_KEY_SIZE],
				   const u8 secret[CURVE25519_KEY_SIZE],
				   const u8 basepoint[CURVE25519_KEY_SIZE])
{
	return false;
}
static inline bool curve25519_base_arch(u8 pub[CURVE25519_KEY_SIZE],
					const u8 secret[CURVE25519_KEY_SIZE])
{
	return false;
}
#endif

#if defined(CONFIG_ARCH_SUPPORTS_INT128) && defined(__SIZEOF_INT128__)
#include "curve25519-hacl64.c"
#else
#include "curve25519-fiat32.c"
#endif

static const u8 null_point[CURVE25519_KEY_SIZE] = { 0 };

bool curve25519(u8 mypublic[CURVE25519_KEY_SIZE],
		const u8 secret[CURVE25519_KEY_SIZE],
		const u8 basepoint[CURVE25519_KEY_SIZE])
{
	if (!curve25519_arch(mypublic, secret, basepoint))
		curve25519_generic(mypublic, secret, basepoint);
	return crypto_memneq(mypublic, null_point, CURVE25519_KEY_SIZE);
}

bool curve25519_generate_public(u8 pub[CURVE25519_KEY_SIZE],
				const u8 secret[CURVE25519_KEY_SIZE])
{
	static const u8 basepoint[CURVE25519_KEY_SIZE] __aligned(32) = { 9 };

	if (unlikely(!crypto_memneq(secret, null_point, CURVE25519_KEY_SIZE)))
		return false;

	if (curve25519_base_arch(pub, secret))
		return crypto_memneq(pub, null_point, CURVE25519_KEY_SIZE);
	return curve25519(pub, secret, basepoint);
}

void curve25519_generate_secret(u8 secret[CURVE25519_KEY_SIZE])
{
	get_random_bytes_wait(secret, CURVE25519_KEY_SIZE);
	curve25519_clamp_secret(secret);
}

#include "../selftest/curve25519.c"

static bool nosimd __initdata = false;

#ifndef COMPAT_ZINC_IS_A_MODULE
int __init curve25519_mod_init(void)
#else
static int __init mod_init(void)
#endif
{
	if (!nosimd)
		curve25519_fpu_init();
	if (!selftest_run("curve25519", curve25519_selftest, curve25519_nobs,
			  ARRAY_SIZE(curve25519_nobs)))
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
MODULE_DESCRIPTION("Curve25519 scalar multiplication");
MODULE_AUTHOR("Jason A. Donenfeld <Jason@zx2c4.com>");
#endif
