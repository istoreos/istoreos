/* SPDX-License-Identifier: GPL-2.0 OR MIT */
/*
 * Copyright (C) 2015-2019 Jason A. Donenfeld <Jason@zx2c4.com>. All Rights Reserved.
 */

#ifndef _ZINC_BLAKE2S_H
#define _ZINC_BLAKE2S_H

#include <linux/types.h>
#include <linux/kernel.h>
#include <asm/bug.h>

enum blake2s_lengths {
	BLAKE2S_BLOCK_SIZE = 64,
	BLAKE2S_HASH_SIZE = 32,
	BLAKE2S_KEY_SIZE = 32
};

struct blake2s_state {
	u32 h[8];
	u32 t[2];
	u32 f[2];
	u8 buf[BLAKE2S_BLOCK_SIZE];
	unsigned int buflen;
	unsigned int outlen;
};

void blake2s_init(struct blake2s_state *state, const size_t outlen);
void blake2s_init_key(struct blake2s_state *state, const size_t outlen,
		      const void *key, const size_t keylen);
void blake2s_update(struct blake2s_state *state, const u8 *in, size_t inlen);
void blake2s_final(struct blake2s_state *state, u8 *out);

static inline void blake2s(u8 *out, const u8 *in, const u8 *key,
			   const size_t outlen, const size_t inlen,
			   const size_t keylen)
{
	struct blake2s_state state;

	WARN_ON(IS_ENABLED(DEBUG) && ((!in && inlen > 0) || !out || !outlen ||
		outlen > BLAKE2S_HASH_SIZE || keylen > BLAKE2S_KEY_SIZE ||
		(!key && keylen)));

	if (keylen)
		blake2s_init_key(&state, outlen, key, keylen);
	else
		blake2s_init(&state, outlen);

	blake2s_update(&state, in, inlen);
	blake2s_final(&state, out);
}

void blake2s_hmac(u8 *out, const u8 *in, const u8 *key, const size_t outlen,
		  const size_t inlen, const size_t keylen);

#endif /* _ZINC_BLAKE2S_H */
