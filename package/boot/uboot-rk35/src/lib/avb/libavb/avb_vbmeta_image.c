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

#include <android_avb/avb_vbmeta_image.h>
#include <android_avb/avb_crypto.h>
#include <android_avb/avb_rsa.h>
#include <android_avb/avb_sha.h>
#include <android_avb/avb_util.h>
#include <android_avb/avb_version.h>

AvbVBMetaVerifyResult avb_vbmeta_image_verify(
    const uint8_t* data,
    size_t length,
    const uint8_t** out_public_key_data,
    size_t* out_public_key_length) {
  AvbVBMetaVerifyResult ret;
  AvbVBMetaImageHeader h;
  uint8_t* computed_hash;
  const AvbAlgorithmData* algorithm;
  AvbSHA256Ctx sha256_ctx;
  AvbSHA512Ctx sha512_ctx;
  const uint8_t* header_block;
  const uint8_t* authentication_block;
  const uint8_t* auxiliary_block;
  int verification_result;

  ret = AVB_VBMETA_VERIFY_RESULT_INVALID_VBMETA_HEADER;

  if (out_public_key_data != NULL) {
    *out_public_key_data = NULL;
  }
  if (out_public_key_length != NULL) {
    *out_public_key_length = 0;
  }

  /* Before we byteswap or compare Magic, ensure length is long enough. */
  if (length < sizeof(AvbVBMetaImageHeader)) {
    avb_error("Length is smaller than header.\n");
    goto out;
  }

  /* Ensure magic is correct. */
  if (avb_safe_memcmp(data, AVB_MAGIC, AVB_MAGIC_LEN) != 0) {
    avb_error("Magic is incorrect.\n");
    goto out;
  }

  avb_vbmeta_image_header_to_host_byte_order((const AvbVBMetaImageHeader*)data,
                                             &h);

  /* Ensure we don't attempt to access any fields if we do not meet
   * the specified minimum version of libavb.
   */
  if ((h.required_libavb_version_major != AVB_VERSION_MAJOR) ||
      (h.required_libavb_version_minor > AVB_VERSION_MINOR)) {
    avb_error("Mismatch between image version and libavb version.\n");
    ret = AVB_VBMETA_VERIFY_RESULT_UNSUPPORTED_VERSION;
    goto out;
  }

  /* Ensure |release_string| ends with a NUL byte. */
  if (h.release_string[AVB_RELEASE_STRING_SIZE - 1] != '\0') {
    avb_error("Release string does not end with a NUL byte.\n");
    goto out;
  }

  /* Ensure inner block sizes are multiple of 64. */
  if ((h.authentication_data_block_size & 0x3f) != 0 ||
      (h.auxiliary_data_block_size & 0x3f) != 0) {
    avb_error("Block size is not a multiple of 64.\n");
    goto out;
  }

  /* Ensure block sizes all add up to at most |length|. */
  uint64_t block_total = sizeof(AvbVBMetaImageHeader);
  if (!avb_safe_add_to(&block_total, h.authentication_data_block_size) ||
      !avb_safe_add_to(&block_total, h.auxiliary_data_block_size)) {
    avb_error("Overflow while computing size of boot image.\n");
    goto out;
  }
  if (block_total > length) {
    avb_error("Block sizes add up to more than given length.\n");
    goto out;
  }

  uintptr_t data_ptr = (uintptr_t)data;
  /* Ensure passed in memory doesn't wrap. */
  if (!avb_safe_add(NULL, (uint64_t)data_ptr, length)) {
    avb_error("Boot image location and length mismatch.\n");
    goto out;
  }

  /* Ensure hash and signature are entirely in the Authentication data block. */
  uint64_t hash_end;
  if (!avb_safe_add(&hash_end, h.hash_offset, h.hash_size) ||
      hash_end > h.authentication_data_block_size) {
    avb_error("Hash is not entirely in its block.\n");
    goto out;
  }
  uint64_t signature_end;
  if (!avb_safe_add(&signature_end, h.signature_offset, h.signature_size) ||
      signature_end > h.authentication_data_block_size) {
    avb_error("Signature is not entirely in its block.\n");
    goto out;
  }

  /* Ensure public key is entirely in the Auxiliary data block. */
  uint64_t pubkey_end;
  if (!avb_safe_add(&pubkey_end, h.public_key_offset, h.public_key_size) ||
      pubkey_end > h.auxiliary_data_block_size) {
    avb_error("Public key is not entirely in its block.\n");
    goto out;
  }

  /* Ensure public key metadata (if set) is entirely in the Auxiliary
   * data block. */
  if (h.public_key_metadata_size > 0) {
    uint64_t pubkey_md_end;
    if (!avb_safe_add(&pubkey_md_end,
                      h.public_key_metadata_offset,
                      h.public_key_metadata_size) ||
        pubkey_md_end > h.auxiliary_data_block_size) {
      avb_error("Public key metadata is not entirely in its block.\n");
      goto out;
    }
  }

  /* Bail early if there's no hash or signature. */
  if (h.algorithm_type == AVB_ALGORITHM_TYPE_NONE) {
    ret = AVB_VBMETA_VERIFY_RESULT_OK_NOT_SIGNED;
    goto out;
  }

  /* Ensure algorithm field is supported. */
  algorithm = avb_get_algorithm_data(h.algorithm_type);
  if (!algorithm) {
    avb_error("Invalid or unknown algorithm.\n");
    goto out;
  }

  /* Bail if the embedded hash size doesn't match the chosen algorithm. */
  if (h.hash_size != algorithm->hash_len) {
    avb_error("Embedded hash has wrong size.\n");
    goto out;
  }

  /* No overflow checks needed from here-on after since all block
   * sizes and offsets have been verified above.
   */

  header_block = data;
  authentication_block = header_block + sizeof(AvbVBMetaImageHeader);
  auxiliary_block = authentication_block + h.authentication_data_block_size;

  switch (h.algorithm_type) {
    /* Explicit fall-through: */
    case AVB_ALGORITHM_TYPE_SHA256_RSA2048:
    case AVB_ALGORITHM_TYPE_SHA256_RSA4096:
    case AVB_ALGORITHM_TYPE_SHA256_RSA8192:

      sha256_ctx.tot_len = sizeof(AvbVBMetaImageHeader) +
                                      h.auxiliary_data_block_size;
      avb_sha256_init(&sha256_ctx);
      avb_sha256_update(
          &sha256_ctx, header_block, sizeof(AvbVBMetaImageHeader));
      avb_sha256_update(
          &sha256_ctx, auxiliary_block, h.auxiliary_data_block_size);
      computed_hash = avb_sha256_final(&sha256_ctx);
      break;
    /* Explicit fall-through: */
    case AVB_ALGORITHM_TYPE_SHA512_RSA2048:
    case AVB_ALGORITHM_TYPE_SHA512_RSA4096:
    case AVB_ALGORITHM_TYPE_SHA512_RSA8192:
      sha512_ctx.tot_len = sizeof(AvbVBMetaImageHeader) +
                                      h.auxiliary_data_block_size;
      avb_sha512_init(&sha512_ctx);
      avb_sha512_update(
          &sha512_ctx, header_block, sizeof(AvbVBMetaImageHeader));
      avb_sha512_update(
          &sha512_ctx, auxiliary_block, h.auxiliary_data_block_size);
      computed_hash = avb_sha512_final(&sha512_ctx);
      break;
    default:
      avb_error("Unknown algorithm.\n");
      goto out;
  }

  if (avb_safe_memcmp(authentication_block + h.hash_offset,
                      computed_hash,
                      h.hash_size) != 0) {
    avb_error("Hash does not match!\n");
    ret = AVB_VBMETA_VERIFY_RESULT_HASH_MISMATCH;
    goto out;
  }

  verification_result =
      avb_rsa_verify(auxiliary_block + h.public_key_offset,
                     h.public_key_size,
                     authentication_block + h.signature_offset,
                     h.signature_size,
                     authentication_block + h.hash_offset,
                     h.hash_size,
                     algorithm->padding,
                     algorithm->padding_len);

  if (verification_result == 0) {
    ret = AVB_VBMETA_VERIFY_RESULT_SIGNATURE_MISMATCH;
    goto out;
  }

  if (h.public_key_size > 0) {
    if (out_public_key_data != NULL) {
      *out_public_key_data = auxiliary_block + h.public_key_offset;
    }
    if (out_public_key_length != NULL) {
      *out_public_key_length = h.public_key_size;
    }
  }

  ret = AVB_VBMETA_VERIFY_RESULT_OK;

out:
  return ret;
}

void avb_vbmeta_image_header_to_host_byte_order(const AvbVBMetaImageHeader* src,
                                                AvbVBMetaImageHeader* dest) {
  avb_memcpy(dest, src, sizeof(AvbVBMetaImageHeader));

  dest->required_libavb_version_major =
      avb_be32toh(dest->required_libavb_version_major);
  dest->required_libavb_version_minor =
      avb_be32toh(dest->required_libavb_version_minor);

  dest->authentication_data_block_size =
      avb_be64toh(dest->authentication_data_block_size);
  dest->auxiliary_data_block_size =
      avb_be64toh(dest->auxiliary_data_block_size);

  dest->algorithm_type = avb_be32toh(dest->algorithm_type);

  dest->hash_offset = avb_be64toh(dest->hash_offset);
  dest->hash_size = avb_be64toh(dest->hash_size);

  dest->signature_offset = avb_be64toh(dest->signature_offset);
  dest->signature_size = avb_be64toh(dest->signature_size);

  dest->public_key_offset = avb_be64toh(dest->public_key_offset);
  dest->public_key_size = avb_be64toh(dest->public_key_size);

  dest->public_key_metadata_offset =
      avb_be64toh(dest->public_key_metadata_offset);
  dest->public_key_metadata_size = avb_be64toh(dest->public_key_metadata_size);

  dest->descriptors_offset = avb_be64toh(dest->descriptors_offset);
  dest->descriptors_size = avb_be64toh(dest->descriptors_size);

  dest->rollback_index = avb_be64toh(dest->rollback_index);
  dest->flags = avb_be32toh(dest->flags);
}

const char* avb_vbmeta_verify_result_to_string(AvbVBMetaVerifyResult result) {
  const char* ret = NULL;

  switch (result) {
    case AVB_VBMETA_VERIFY_RESULT_OK:
      ret = "OK";
      break;
    case AVB_VBMETA_VERIFY_RESULT_OK_NOT_SIGNED:
      ret = "OK_NOT_SIGNED";
      break;
    case AVB_VBMETA_VERIFY_RESULT_INVALID_VBMETA_HEADER:
      ret = "INVALID_VBMETA_HEADER";
      break;
    case AVB_VBMETA_VERIFY_RESULT_UNSUPPORTED_VERSION:
      ret = "UNSUPPORTED_VERSION";
      break;
    case AVB_VBMETA_VERIFY_RESULT_HASH_MISMATCH:
      ret = "HASH_MISMATCH";
      break;
    case AVB_VBMETA_VERIFY_RESULT_SIGNATURE_MISMATCH:
      ret = "SIGNATURE_MISMATCH";
      break;
      /* Do not add a 'default:' case here because of -Wswitch. */
  }

  if (ret == NULL) {
    avb_error("Unknown AvbVBMetaVerifyResult value.\n");
    ret = "(unknown)";
  }

  return ret;
}
