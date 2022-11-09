/*
 * Copyright (C) 2016 The Android Open Source Project
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/*
#if !defined(AVB_INSIDE_LIBAVB_H) && !defined(AVB_COMPILATION)
#error "Never include this file directly, include libavb.h instead."
#endif
*/

#ifndef AVB_CRYPTO_H_
#define AVB_CRYPTO_H_

#include <android_avb/avb_sysdeps.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Size of a RSA-2048 signature. */
#define AVB_RSA2048_NUM_BYTES 256

/* Size of a RSA-4096 signature. */
#define AVB_RSA4096_NUM_BYTES 512

/* Size of a RSA-8192 signature. */
#define AVB_RSA8192_NUM_BYTES 1024

/* Size in bytes of a SHA-1 digest. */
#define AVB_SHA1_DIGEST_SIZE 20

/* Size in bytes of a SHA-256 digest. */
#define AVB_SHA256_DIGEST_SIZE 32

/* Size in bytes of a SHA-512 digest. */
#define AVB_SHA512_DIGEST_SIZE 64

/* Possible digest types supported by libavb routines. */
typedef enum {
  AVB_DIGEST_TYPE_SHA256,
  AVB_DIGEST_TYPE_SHA512,
} AvbDigestType;

/* Algorithms that can be used in the vbmeta image for
 * verification. An algorithm consists of a hash type and a signature
 * type.
 *
 * The data used to calculate the hash is the three blocks mentioned
 * in the documentation for |AvbVBMetaImageHeader| except for the data
 * in the "Authentication data" block.
 *
 * For signatures with RSA keys, PKCS v1.5 padding is used. The public
 * key data is stored in the auxiliary data block, see
 * |AvbRSAPublicKeyHeader| for the serialization format.
 *
 * Each algorithm type is described below:
 *
 * AVB_ALGORITHM_TYPE_NONE: There is no hash, no signature of the
 * data, and no public key. The data cannot be verified. The fields
 * |hash_size|, |signature_size|, and |public_key_size| must be zero.
 *
 * AVB_ALGORITHM_TYPE_SHA256_RSA2048: The hash function used is
 * SHA-256, resulting in 32 bytes of hash digest data. This hash is
 * signed with a 2048-bit RSA key. The field |hash_size| must be 32,
 * |signature_size| must be 256, and the public key data must have
 * |key_num_bits| set to 2048.
 *
 * AVB_ALGORITHM_TYPE_SHA256_RSA4096: Like above, but only with
 * a 4096-bit RSA key and |signature_size| set to 512.
 *
 * AVB_ALGORITHM_TYPE_SHA256_RSA8192: Like above, but only with
 * a 8192-bit RSA key and |signature_size| set to 1024.
 *
 * AVB_ALGORITHM_TYPE_SHA512_RSA2048: The hash function used is
 * SHA-512, resulting in 64 bytes of hash digest data. This hash is
 * signed with a 2048-bit RSA key. The field |hash_size| must be 64,
 * |signature_size| must be 256, and the public key data must have
 * |key_num_bits| set to 2048.
 *
 * AVB_ALGORITHM_TYPE_SHA512_RSA4096: Like above, but only with
 * a 4096-bit RSA key and |signature_size| set to 512.
 *
 * AVB_ALGORITHM_TYPE_SHA512_RSA8192: Like above, but only with
 * a 8192-bit RSA key and |signature_size| set to 1024.
 */
typedef enum {
  AVB_ALGORITHM_TYPE_NONE,
  AVB_ALGORITHM_TYPE_SHA256_RSA2048,
  AVB_ALGORITHM_TYPE_SHA256_RSA4096,
  AVB_ALGORITHM_TYPE_SHA256_RSA8192,
  AVB_ALGORITHM_TYPE_SHA512_RSA2048,
  AVB_ALGORITHM_TYPE_SHA512_RSA4096,
  AVB_ALGORITHM_TYPE_SHA512_RSA8192,
  _AVB_ALGORITHM_NUM_TYPES
} AvbAlgorithmType;

/* Holds algorithm-specific data. The |padding| is needed by avb_rsa_verify. */
typedef struct {
  const uint8_t* padding;
  size_t padding_len;
  size_t hash_len;
} AvbAlgorithmData;

/* Provides algorithm-specific data for a given |algorithm|. Returns NULL if
 * |algorithm| is invalid.
 */
const AvbAlgorithmData* avb_get_algorithm_data(AvbAlgorithmType algorithm)
    AVB_ATTR_WARN_UNUSED_RESULT;

/* The header for a serialized RSA public key.
 *
 * The size of the key is given by |key_num_bits|, for example 2048
 * for a RSA-2048 key. By definition, a RSA public key is the pair (n,
 * e) where |n| is the modulus (which can be represented in
 * |key_num_bits| bits) and |e| is the public exponent. The exponent
 * is not stored since it's assumed to always be 65537.
 *
 * To optimize verification, the key block includes two precomputed
 * values, |n0inv| (fits in 32 bits) and |rr| and can always be
 * represented in |key_num_bits|.

 * The value |n0inv| is the value -1/n[0] (mod 2^32). The value |rr|
 * is (2^key_num_bits)^2 (mod n).
 *
 * Following this header is |key_num_bits| bits of |n|, then
 * |key_num_bits| bits of |rr|. Both values are stored with most
 * significant bit first. Each serialized number takes up
 * |key_num_bits|/8 bytes.
 *
 * All fields in this struct are stored in network byte order when
 * serialized.  To generate a copy with fields swapped to native byte
 * order, use the function avb_rsa_public_key_header_validate_and_byteswap().
 *
 * The avb_rsa_verify() function expects a key in this serialized
 * format.
 *
 * The 'avbtool extract_public_key' command can be used to generate a
 * serialized RSA public key.
 */
typedef struct AvbRSAPublicKeyHeader {
  uint32_t key_num_bits;
  uint32_t n0inv;
} AVB_ATTR_PACKED AvbRSAPublicKeyHeader;

/* Copies |src| to |dest| and validates, byte-swapping fields in the
 * process if needed. Returns true if valid, false if invalid.
 */
bool avb_rsa_public_key_header_validate_and_byteswap(
    const AvbRSAPublicKeyHeader* src,
    AvbRSAPublicKeyHeader* dest) AVB_ATTR_WARN_UNUSED_RESULT;

#ifdef __cplusplus
}
#endif

#endif /* AVB_CRYPTO_H_ */
