/* SPDX-License-Identifier: GPL-2.0 OR MIT */
/*
 * Copyright (C) 2015-2019 Jason A. Donenfeld <Jason@zx2c4.com>. All Rights Reserved.
 */

#ifndef _ZINC_CURVE25519_H
#define _ZINC_CURVE25519_H

#include <linux/types.h>

enum curve25519_lengths {
	CURVE25519_KEY_SIZE = 32
};

bool __must_check curve25519(u8 mypublic[CURVE25519_KEY_SIZE],
			     const u8 secret[CURVE25519_KEY_SIZE],
			     const u8 basepoint[CURVE25519_KEY_SIZE]);
void curve25519_generate_secret(u8 secret[CURVE25519_KEY_SIZE]);
bool __must_check curve25519_generate_public(
	u8 pub[CURVE25519_KEY_SIZE], const u8 secret[CURVE25519_KEY_SIZE]);

static inline void curve25519_clamp_secret(u8 secret[CURVE25519_KEY_SIZE])
{
	secret[0] &= 248;
	secret[31] = (secret[31] & 127) | 64;
}

#endif /* _ZINC_CURVE25519_H */
