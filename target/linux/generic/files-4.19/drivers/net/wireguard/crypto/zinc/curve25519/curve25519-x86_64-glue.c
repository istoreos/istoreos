// SPDX-License-Identifier: GPL-2.0 OR MIT
/*
 * Copyright (C) 2015-2019 Jason A. Donenfeld <Jason@zx2c4.com>. All Rights Reserved.
 */

#include <asm/cpufeature.h>
#include <asm/processor.h>

#include "curve25519-x86_64.c"

static bool curve25519_use_bmi2_adx __ro_after_init;
static bool *const curve25519_nobs[] __initconst = {
	&curve25519_use_bmi2_adx };

static void __init curve25519_fpu_init(void)
{
	curve25519_use_bmi2_adx = IS_ENABLED(CONFIG_AS_BMI2) &&
				  IS_ENABLED(CONFIG_AS_ADX) &&
				  boot_cpu_has(X86_FEATURE_BMI2) &&
				  boot_cpu_has(X86_FEATURE_ADX);
}

static inline bool curve25519_arch(u8 mypublic[CURVE25519_KEY_SIZE],
				   const u8 secret[CURVE25519_KEY_SIZE],
				   const u8 basepoint[CURVE25519_KEY_SIZE])
{
	if (IS_ENABLED(CONFIG_AS_ADX) && IS_ENABLED(CONFIG_AS_BMI2) &&
	    curve25519_use_bmi2_adx) {
		curve25519_ever64(mypublic, secret, basepoint);
		return true;
	}
	return false;
}

static inline bool curve25519_base_arch(u8 pub[CURVE25519_KEY_SIZE],
					const u8 secret[CURVE25519_KEY_SIZE])
{
	if (IS_ENABLED(CONFIG_AS_ADX) && IS_ENABLED(CONFIG_AS_BMI2) &&
	    curve25519_use_bmi2_adx) {
		curve25519_ever64_base(pub, secret);
		return true;
	}
	return false;
}
