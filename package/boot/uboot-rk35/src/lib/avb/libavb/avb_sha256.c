/* SHA-256 and SHA-512 implementation based on code by Oliver Gay
 * <olivier.gay@a3.epfl.ch> under a BSD-style license. See below.
 */

/*
 * FIPS 180-2 SHA-224/256/384/512 implementation
 * Last update: 02/02/2007
 * Issue date:  04/30/2005
 *
 * Copyright (C) 2005, 2007 Olivier Gay <olivier.gay@a3.epfl.ch>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the project nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE PROJECT AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE PROJECT OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include <android_avb/avb_sha.h>
#include <android_avb/avb_util.h>

#ifdef CONFIG_DM_CRYPTO
void avb_sha256_init(AvbSHA256Ctx* ctx) {
  ctx->crypto_ctx.algo = CRYPTO_SHA256;
  ctx->crypto_ctx.length = ctx->tot_len;
  memset(ctx->buf, 0, sizeof(ctx->buf));

  ctx->crypto_dev = crypto_get_device(ctx->crypto_ctx.algo);
  if (!ctx->crypto_dev)
    avb_error("Can't get sha256 crypto device\n");
  else
    crypto_sha_init(ctx->crypto_dev, &ctx->crypto_ctx);
}

void avb_sha256_update(AvbSHA256Ctx* ctx, const uint8_t* data, size_t len) {
  if (ctx->crypto_dev)
    crypto_sha_update(ctx->crypto_dev, (u32 *)data, len);
}

uint8_t* avb_sha256_final(AvbSHA256Ctx* ctx) {
  if (ctx->crypto_dev)
    crypto_sha_final(ctx->crypto_dev, &ctx->crypto_ctx, ctx->buf);

  return ctx->buf;
}
#else
#define SHFR(x, n) (x >> n)
#define ROTR(x, n) ((x >> n) | (x << ((sizeof(x) << 3) - n)))
#define ROTL(x, n) ((x << n) | (x >> ((sizeof(x) << 3) - n)))
#define CH(x, y, z) ((x & y) ^ (~x & z))
#define MAJ(x, y, z) ((x & y) ^ (x & z) ^ (y & z))

#define SHA256_F1(x) (ROTR(x, 2) ^ ROTR(x, 13) ^ ROTR(x, 22))
#define SHA256_F2(x) (ROTR(x, 6) ^ ROTR(x, 11) ^ ROTR(x, 25))
#define SHA256_F3(x) (ROTR(x, 7) ^ ROTR(x, 18) ^ SHFR(x, 3))
#define SHA256_F4(x) (ROTR(x, 17) ^ ROTR(x, 19) ^ SHFR(x, 10))

#define UNPACK32(x, str)                 \
  {                                      \
    *((str) + 3) = (uint8_t)((x));       \
    *((str) + 2) = (uint8_t)((x) >> 8);  \
    *((str) + 1) = (uint8_t)((x) >> 16); \
    *((str) + 0) = (uint8_t)((x) >> 24); \
  }

#define UNPACK64(x, str)                         \
  {                                              \
    *((str) + 7) = (uint8_t)x;                   \
    *((str) + 6) = (uint8_t)((uint64_t)x >> 8);  \
    *((str) + 5) = (uint8_t)((uint64_t)x >> 16); \
    *((str) + 4) = (uint8_t)((uint64_t)x >> 24); \
    *((str) + 3) = (uint8_t)((uint64_t)x >> 32); \
    *((str) + 2) = (uint8_t)((uint64_t)x >> 40); \
    *((str) + 1) = (uint8_t)((uint64_t)x >> 48); \
    *((str) + 0) = (uint8_t)((uint64_t)x >> 56); \
  }

#define PACK32(str, x)                                                    \
  {                                                                       \
    *(x) = ((uint32_t) * ((str) + 3)) | ((uint32_t) * ((str) + 2) << 8) | \
           ((uint32_t) * ((str) + 1) << 16) |                             \
           ((uint32_t) * ((str) + 0) << 24);                              \
  }

/* Macros used for loops unrolling */

#define SHA256_SCR(i) \
  { w[i] = SHA256_F4(w[i - 2]) + w[i - 7] + SHA256_F3(w[i - 15]) + w[i - 16]; }

#define SHA256_EXP(a, b, c, d, e, f, g, h, j)                               \
  {                                                                         \
    t1 = wv[h] + SHA256_F2(wv[e]) + CH(wv[e], wv[f], wv[g]) + sha256_k[j] + \
         w[j];                                                              \
    t2 = SHA256_F1(wv[a]) + MAJ(wv[a], wv[b], wv[c]);                       \
    wv[d] += t1;                                                            \
    wv[h] = t1 + t2;                                                        \
  }

static const uint32_t sha256_h0[8] = {0x6a09e667,
                                      0xbb67ae85,
                                      0x3c6ef372,
                                      0xa54ff53a,
                                      0x510e527f,
                                      0x9b05688c,
                                      0x1f83d9ab,
                                      0x5be0cd19};

static const uint32_t sha256_k[64] = {
    0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1,
    0x923f82a4, 0xab1c5ed5, 0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
    0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174, 0xe49b69c1, 0xefbe4786,
    0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
    0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147,
    0x06ca6351, 0x14292967, 0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
    0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85, 0xa2bfe8a1, 0xa81a664b,
    0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
    0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a,
    0x5b9cca4f, 0x682e6ff3, 0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
    0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2};

/* SHA-256 implementation */
void avb_sha256_init(AvbSHA256Ctx* ctx) {
#ifndef UNROLL_LOOPS
  int i;
  for (i = 0; i < 8; i++) {
    ctx->h[i] = sha256_h0[i];
  }
#else
  ctx->h[0] = sha256_h0[0];
  ctx->h[1] = sha256_h0[1];
  ctx->h[2] = sha256_h0[2];
  ctx->h[3] = sha256_h0[3];
  ctx->h[4] = sha256_h0[4];
  ctx->h[5] = sha256_h0[5];
  ctx->h[6] = sha256_h0[6];
  ctx->h[7] = sha256_h0[7];
#endif /* !UNROLL_LOOPS */

  ctx->len = 0;
  ctx->tot_len = 0;
}

static void SHA256_transform(AvbSHA256Ctx* ctx,
                             const uint8_t* message,
                             size_t block_nb) {
  uint32_t w[64];
  uint32_t wv[8];
  uint32_t t1, t2;
  const unsigned char* sub_block;
  size_t i;

#ifndef UNROLL_LOOPS
  size_t j;
#endif

  for (i = 0; i < block_nb; i++) {
    sub_block = message + (i << 6);

#ifndef UNROLL_LOOPS
    for (j = 0; j < 16; j++) {
      PACK32(&sub_block[j << 2], &w[j]);
    }

    for (j = 16; j < 64; j++) {
      SHA256_SCR(j);
    }

    for (j = 0; j < 8; j++) {
      wv[j] = ctx->h[j];
    }

    for (j = 0; j < 64; j++) {
      t1 = wv[7] + SHA256_F2(wv[4]) + CH(wv[4], wv[5], wv[6]) + sha256_k[j] +
           w[j];
      t2 = SHA256_F1(wv[0]) + MAJ(wv[0], wv[1], wv[2]);
      wv[7] = wv[6];
      wv[6] = wv[5];
      wv[5] = wv[4];
      wv[4] = wv[3] + t1;
      wv[3] = wv[2];
      wv[2] = wv[1];
      wv[1] = wv[0];
      wv[0] = t1 + t2;
    }

    for (j = 0; j < 8; j++) {
      ctx->h[j] += wv[j];
    }
#else
    PACK32(&sub_block[0], &w[0]);
    PACK32(&sub_block[4], &w[1]);
    PACK32(&sub_block[8], &w[2]);
    PACK32(&sub_block[12], &w[3]);
    PACK32(&sub_block[16], &w[4]);
    PACK32(&sub_block[20], &w[5]);
    PACK32(&sub_block[24], &w[6]);
    PACK32(&sub_block[28], &w[7]);
    PACK32(&sub_block[32], &w[8]);
    PACK32(&sub_block[36], &w[9]);
    PACK32(&sub_block[40], &w[10]);
    PACK32(&sub_block[44], &w[11]);
    PACK32(&sub_block[48], &w[12]);
    PACK32(&sub_block[52], &w[13]);
    PACK32(&sub_block[56], &w[14]);
    PACK32(&sub_block[60], &w[15]);

    SHA256_SCR(16);
    SHA256_SCR(17);
    SHA256_SCR(18);
    SHA256_SCR(19);
    SHA256_SCR(20);
    SHA256_SCR(21);
    SHA256_SCR(22);
    SHA256_SCR(23);
    SHA256_SCR(24);
    SHA256_SCR(25);
    SHA256_SCR(26);
    SHA256_SCR(27);
    SHA256_SCR(28);
    SHA256_SCR(29);
    SHA256_SCR(30);
    SHA256_SCR(31);
    SHA256_SCR(32);
    SHA256_SCR(33);
    SHA256_SCR(34);
    SHA256_SCR(35);
    SHA256_SCR(36);
    SHA256_SCR(37);
    SHA256_SCR(38);
    SHA256_SCR(39);
    SHA256_SCR(40);
    SHA256_SCR(41);
    SHA256_SCR(42);
    SHA256_SCR(43);
    SHA256_SCR(44);
    SHA256_SCR(45);
    SHA256_SCR(46);
    SHA256_SCR(47);
    SHA256_SCR(48);
    SHA256_SCR(49);
    SHA256_SCR(50);
    SHA256_SCR(51);
    SHA256_SCR(52);
    SHA256_SCR(53);
    SHA256_SCR(54);
    SHA256_SCR(55);
    SHA256_SCR(56);
    SHA256_SCR(57);
    SHA256_SCR(58);
    SHA256_SCR(59);
    SHA256_SCR(60);
    SHA256_SCR(61);
    SHA256_SCR(62);
    SHA256_SCR(63);

    wv[0] = ctx->h[0];
    wv[1] = ctx->h[1];
    wv[2] = ctx->h[2];
    wv[3] = ctx->h[3];
    wv[4] = ctx->h[4];
    wv[5] = ctx->h[5];
    wv[6] = ctx->h[6];
    wv[7] = ctx->h[7];

    SHA256_EXP(0, 1, 2, 3, 4, 5, 6, 7, 0);
    SHA256_EXP(7, 0, 1, 2, 3, 4, 5, 6, 1);
    SHA256_EXP(6, 7, 0, 1, 2, 3, 4, 5, 2);
    SHA256_EXP(5, 6, 7, 0, 1, 2, 3, 4, 3);
    SHA256_EXP(4, 5, 6, 7, 0, 1, 2, 3, 4);
    SHA256_EXP(3, 4, 5, 6, 7, 0, 1, 2, 5);
    SHA256_EXP(2, 3, 4, 5, 6, 7, 0, 1, 6);
    SHA256_EXP(1, 2, 3, 4, 5, 6, 7, 0, 7);
    SHA256_EXP(0, 1, 2, 3, 4, 5, 6, 7, 8);
    SHA256_EXP(7, 0, 1, 2, 3, 4, 5, 6, 9);
    SHA256_EXP(6, 7, 0, 1, 2, 3, 4, 5, 10);
    SHA256_EXP(5, 6, 7, 0, 1, 2, 3, 4, 11);
    SHA256_EXP(4, 5, 6, 7, 0, 1, 2, 3, 12);
    SHA256_EXP(3, 4, 5, 6, 7, 0, 1, 2, 13);
    SHA256_EXP(2, 3, 4, 5, 6, 7, 0, 1, 14);
    SHA256_EXP(1, 2, 3, 4, 5, 6, 7, 0, 15);
    SHA256_EXP(0, 1, 2, 3, 4, 5, 6, 7, 16);
    SHA256_EXP(7, 0, 1, 2, 3, 4, 5, 6, 17);
    SHA256_EXP(6, 7, 0, 1, 2, 3, 4, 5, 18);
    SHA256_EXP(5, 6, 7, 0, 1, 2, 3, 4, 19);
    SHA256_EXP(4, 5, 6, 7, 0, 1, 2, 3, 20);
    SHA256_EXP(3, 4, 5, 6, 7, 0, 1, 2, 21);
    SHA256_EXP(2, 3, 4, 5, 6, 7, 0, 1, 22);
    SHA256_EXP(1, 2, 3, 4, 5, 6, 7, 0, 23);
    SHA256_EXP(0, 1, 2, 3, 4, 5, 6, 7, 24);
    SHA256_EXP(7, 0, 1, 2, 3, 4, 5, 6, 25);
    SHA256_EXP(6, 7, 0, 1, 2, 3, 4, 5, 26);
    SHA256_EXP(5, 6, 7, 0, 1, 2, 3, 4, 27);
    SHA256_EXP(4, 5, 6, 7, 0, 1, 2, 3, 28);
    SHA256_EXP(3, 4, 5, 6, 7, 0, 1, 2, 29);
    SHA256_EXP(2, 3, 4, 5, 6, 7, 0, 1, 30);
    SHA256_EXP(1, 2, 3, 4, 5, 6, 7, 0, 31);
    SHA256_EXP(0, 1, 2, 3, 4, 5, 6, 7, 32);
    SHA256_EXP(7, 0, 1, 2, 3, 4, 5, 6, 33);
    SHA256_EXP(6, 7, 0, 1, 2, 3, 4, 5, 34);
    SHA256_EXP(5, 6, 7, 0, 1, 2, 3, 4, 35);
    SHA256_EXP(4, 5, 6, 7, 0, 1, 2, 3, 36);
    SHA256_EXP(3, 4, 5, 6, 7, 0, 1, 2, 37);
    SHA256_EXP(2, 3, 4, 5, 6, 7, 0, 1, 38);
    SHA256_EXP(1, 2, 3, 4, 5, 6, 7, 0, 39);
    SHA256_EXP(0, 1, 2, 3, 4, 5, 6, 7, 40);
    SHA256_EXP(7, 0, 1, 2, 3, 4, 5, 6, 41);
    SHA256_EXP(6, 7, 0, 1, 2, 3, 4, 5, 42);
    SHA256_EXP(5, 6, 7, 0, 1, 2, 3, 4, 43);
    SHA256_EXP(4, 5, 6, 7, 0, 1, 2, 3, 44);
    SHA256_EXP(3, 4, 5, 6, 7, 0, 1, 2, 45);
    SHA256_EXP(2, 3, 4, 5, 6, 7, 0, 1, 46);
    SHA256_EXP(1, 2, 3, 4, 5, 6, 7, 0, 47);
    SHA256_EXP(0, 1, 2, 3, 4, 5, 6, 7, 48);
    SHA256_EXP(7, 0, 1, 2, 3, 4, 5, 6, 49);
    SHA256_EXP(6, 7, 0, 1, 2, 3, 4, 5, 50);
    SHA256_EXP(5, 6, 7, 0, 1, 2, 3, 4, 51);
    SHA256_EXP(4, 5, 6, 7, 0, 1, 2, 3, 52);
    SHA256_EXP(3, 4, 5, 6, 7, 0, 1, 2, 53);
    SHA256_EXP(2, 3, 4, 5, 6, 7, 0, 1, 54);
    SHA256_EXP(1, 2, 3, 4, 5, 6, 7, 0, 55);
    SHA256_EXP(0, 1, 2, 3, 4, 5, 6, 7, 56);
    SHA256_EXP(7, 0, 1, 2, 3, 4, 5, 6, 57);
    SHA256_EXP(6, 7, 0, 1, 2, 3, 4, 5, 58);
    SHA256_EXP(5, 6, 7, 0, 1, 2, 3, 4, 59);
    SHA256_EXP(4, 5, 6, 7, 0, 1, 2, 3, 60);
    SHA256_EXP(3, 4, 5, 6, 7, 0, 1, 2, 61);
    SHA256_EXP(2, 3, 4, 5, 6, 7, 0, 1, 62);
    SHA256_EXP(1, 2, 3, 4, 5, 6, 7, 0, 63);

    ctx->h[0] += wv[0];
    ctx->h[1] += wv[1];
    ctx->h[2] += wv[2];
    ctx->h[3] += wv[3];
    ctx->h[4] += wv[4];
    ctx->h[5] += wv[5];
    ctx->h[6] += wv[6];
    ctx->h[7] += wv[7];
#endif /* !UNROLL_LOOPS */
  }
}

void avb_sha256_update(AvbSHA256Ctx* ctx, const uint8_t* data, size_t len) {
  size_t block_nb;
  size_t new_len, rem_len, tmp_len;
  const uint8_t* shifted_data;

  tmp_len = AVB_SHA256_BLOCK_SIZE - ctx->len;
  rem_len = len < tmp_len ? len : tmp_len;

  avb_memcpy(&ctx->block[ctx->len], data, rem_len);

  if (ctx->len + len < AVB_SHA256_BLOCK_SIZE) {
    ctx->len += len;
    return;
  }

  new_len = len - rem_len;
  block_nb = new_len / AVB_SHA256_BLOCK_SIZE;

  shifted_data = data + rem_len;

  SHA256_transform(ctx, ctx->block, 1);
  SHA256_transform(ctx, shifted_data, block_nb);

  rem_len = new_len % AVB_SHA256_BLOCK_SIZE;

  avb_memcpy(ctx->block, &shifted_data[block_nb << 6], rem_len);

  ctx->len = rem_len;
  ctx->tot_len += (block_nb + 1) << 6;
}

uint8_t* avb_sha256_final(AvbSHA256Ctx* ctx) {
  size_t block_nb;
  size_t pm_len;
  uint64_t len_b;
#ifndef UNROLL_LOOPS
  size_t i;
#endif

  block_nb =
      (1 + ((AVB_SHA256_BLOCK_SIZE - 9) < (ctx->len % AVB_SHA256_BLOCK_SIZE)));

  len_b = (ctx->tot_len + ctx->len) << 3;
  pm_len = block_nb << 6;

  avb_memset(ctx->block + ctx->len, 0, pm_len - ctx->len);
  ctx->block[ctx->len] = 0x80;
  UNPACK64(len_b, ctx->block + pm_len - 8);

  SHA256_transform(ctx, ctx->block, block_nb);

#ifndef UNROLL_LOOPS
  for (i = 0; i < 8; i++) {
    UNPACK32(ctx->h[i], &ctx->buf[i << 2]);
  }
#else
  UNPACK32(ctx->h[0], &ctx->buf[0]);
  UNPACK32(ctx->h[1], &ctx->buf[4]);
  UNPACK32(ctx->h[2], &ctx->buf[8]);
  UNPACK32(ctx->h[3], &ctx->buf[12]);
  UNPACK32(ctx->h[4], &ctx->buf[16]);
  UNPACK32(ctx->h[5], &ctx->buf[20]);
  UNPACK32(ctx->h[6], &ctx->buf[24]);
  UNPACK32(ctx->h[7], &ctx->buf[28]);
#endif /* !UNROLL_LOOPS */

  return ctx->buf;
}
#endif
