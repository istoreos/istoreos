/*
 ---------------------------------------------------------------------------
 Copyright (c) 2002, Dr Brian Gladman <brg@gladman.me.uk>, Worcester, UK.
 All rights reserved.

 LICENSE TERMS

 The free distribution and use of this software in both source and binary
 form is allowed (with or without changes) provided that:

   1. distributions of this source code include the above copyright
      notice, this list of conditions and the following disclaimer;

   2. distributions in binary form include the above copyright
      notice, this list of conditions and the following disclaimer
      in the documentation and/or other associated materials;

   3. the copyright holder's name is not used to endorse products
      built using this software without specific written permission.

 ALTERNATIVELY, provided that this notice is retained in full, this product
 may be distributed under the terms of the GNU General Public License (GPL),
 in which case the provisions of the GPL apply INSTEAD OF those given above.

 DISCLAIMER

 This software is provided 'as is' with no explicit or implied warranties
 in respect of its properties, including, but not limited to, correctness
 and/or fitness for purpose.
 ---------------------------------------------------------------------------
 Issue Date: 30/11/2002
*/

#ifndef _SHA2_H
#define _SHA2_H

#ifdef USE_HOSTCC
#include <limits.h>
#endif

/*  Defines for suffixes to 32 and 64 bit unsigned numeric values   */

#define sfx_lo(x,y) x##y
#define sfx_hi(x,y) sfx_lo(x,y)
#define n_u32(p)    sfx_hi(0x##p,s_u32)
#define n_u64(p)    sfx_hi(0x##p,s_u64)

#ifdef USE_HOSTCC
/* define an unsigned 32-bit type */

#if UINT_MAX == 0xffffffff
typedef   unsigned int     sha2_32t;
#define s_u32    u
#elif ULONG_MAX == 0xffffffff
typedef   unsigned long    sha2_32t;
#define s_u32   ul
#else
#error Please define sha2_32t as an unsigned 32 bit type in sha2.h
#endif

/* define an unsigned 64-bit type */

#if defined( _MSC_VER )
typedef unsigned __int64   sha2_64t;
#define s_u64 ui64
#elif ULONG_MAX == 0xffffffffffffffff
typedef unsigned long      sha2_64t;
#define s_u64   ul
#elif ULONG_MAX == 0xffffffff
typedef unsigned long long sha2_64t;   /* a somewhat dangerous guess */
#define s_u64  ull
#else
#error Please define sha2_64t as an unsigned 64 bit type in sha2.h
#endif

#else
#include <common.h>

typedef uint32_t	sha2_32t;
#define s_u32	u

typedef uint64_t	sha2_64t;   /* a somewhat dangerous guess */
#define s_u64	ull
#endif /* USE_HOSTCC */

#if defined(__cplusplus)
extern "C"
{
#endif

#define SHA256_DIGEST_SIZE  32
#define SHA384_DIGEST_SIZE  48
#define SHA512_DIGEST_SIZE  64

#define SHA256_BLOCK_SIZE   64
#define SHA384_BLOCK_SIZE  128
#define SHA512_BLOCK_SIZE  128

#define SHA2_DIGEST_SIZE        SHA256_DIGEST_SIZE
#define SHA2_MAX_DIGEST_SIZE    SHA512_DIGEST_SIZE

#define SHA2_GOOD   0
#define SHA2_BAD    1

	/* type to hold the SHA256 context				*/

	typedef struct {
		sha2_32t count[2];
		sha2_32t hash[8];
		sha2_32t wbuf[16];
	} sha256_ctx;

	/* type to hold the SHA384/512 context			*/

	typedef struct {
		sha2_64t count[2];
		sha2_64t hash[8];
		sha2_64t wbuf[16];
	} sha512_ctx;

	typedef sha512_ctx  sha384_ctx;

	/* type to hold a SHA2 context (256/384/512)  */

	typedef struct {
		union {
			sha256_ctx  ctx256[1];
			sha512_ctx  ctx512[1];
		} uu[1];
		sha2_32t    sha2_len;
	} sha2_ctx;

	void sha256_compile(sha256_ctx ctx[1]);
	void sha512_compile(sha512_ctx ctx[1]);

	void sha256_begin(sha256_ctx ctx[1]);
	void sha256_hash(sha256_ctx ctx[1], const unsigned char data[], unsigned long len);
	void sha256_end(sha256_ctx ctx[1], unsigned char hval[]);
	void sha256(unsigned char hval[], const unsigned char data[], unsigned long len);

	void sha384_begin(sha384_ctx ctx[1]);
#define sha384_hash sha512_hash
	void sha384_end(sha384_ctx ctx[1], unsigned char hval[]);
	void sha384(unsigned char hval[], const unsigned char data[], unsigned long len);

	void sha512_begin(sha512_ctx ctx[1]);
	void sha512_hash(sha512_ctx ctx[1], const unsigned char data[], unsigned long len);
	void sha512_end(sha512_ctx ctx[1], unsigned char hval[]);
	void sha512(unsigned char hval[], const unsigned char data[], unsigned long len);

	int sha2_begin(sha2_ctx ctx[1], unsigned long size);
	void sha2_hash(sha2_ctx ctx[1], const unsigned char data[], unsigned long len);
	void sha2_end(sha2_ctx ctx[1], unsigned char hval[]);
	int sha2(unsigned char hval[], unsigned long size, const unsigned char data[], unsigned long len);

#if defined(__cplusplus)
}
#endif


#endif
