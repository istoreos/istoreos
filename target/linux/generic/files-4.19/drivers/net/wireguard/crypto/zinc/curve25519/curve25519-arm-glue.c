// SPDX-License-Identifier: GPL-2.0 OR MIT
/*
 * Copyright (C) 2015-2019 Jason A. Donenfeld <Jason@zx2c4.com>. All Rights Reserved.
 */

#include <linux/simd.h>
#include <asm/hwcap.h>
#include <asm/neon.h>

asmlinkage void curve25519_neon(u8 mypublic[CURVE25519_KEY_SIZE],
				const u8 secret[CURVE25519_KEY_SIZE],
				const u8 basepoint[CURVE25519_KEY_SIZE]);

static bool curve25519_use_neon __ro_after_init;
static bool *const curve25519_nobs[] __initconst = { &curve25519_use_neon };
static void __init curve25519_fpu_init(void)
{
	curve25519_use_neon = elf_hwcap & HWCAP_NEON;
}

static inline bool curve25519_arch(u8 mypublic[CURVE25519_KEY_SIZE],
				   const u8 secret[CURVE25519_KEY_SIZE],
				   const u8 basepoint[CURVE25519_KEY_SIZE])
{
	simd_context_t simd_context;
	bool used_arch = false;

	simd_get(&simd_context);
	if (IS_ENABLED(CONFIG_KERNEL_MODE_NEON) &&
	    !IS_ENABLED(CONFIG_CPU_BIG_ENDIAN) && curve25519_use_neon &&
	    simd_use(&simd_context)) {
		curve25519_neon(mypublic, secret, basepoint);
		used_arch = true;
	}
	simd_put(&simd_context);
	return used_arch;
}

static inline bool curve25519_base_arch(u8 pub[CURVE25519_KEY_SIZE],
					const u8 secret[CURVE25519_KEY_SIZE])
{
	return false;
}
