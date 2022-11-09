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
#if !defined(AVB_INSIDE_LIBAVB_ATX_H) && !defined(AVB_COMPILATION)
#error \
    "Never include this file directly, include libavb_atx/libavb_atx.h instead."
#endif
*/

#ifndef AVB_ATX_OPS_H_
#define AVB_ATX_OPS_H_

#include <android_avb/libavb.h>

#include <android_avb/avb_atx_types.h>

#ifdef __cplusplus
extern "C" {
#endif

struct AvbAtxOps;
typedef struct AvbAtxOps AvbAtxOps;

/* An extension to AvbOps required by avb_atx_validate_vbmeta_public_key(). */
struct AvbAtxOps {
  /* Operations from libavb. */
  AvbOps* ops;

  /* Reads permanent |attributes| data. There are no restrictions on where this
   * data is stored. On success, returns AVB_IO_RESULT_OK and populates
   * |attributes|.
   */
  AvbIOResult (*read_permanent_attributes)(
      AvbAtxOps* atx_ops, AvbAtxPermanentAttributes* attributes);

  /* Reads a |hash| of permanent attributes. This hash MUST be retrieved from a
   * permanently read-only location (e.g. fuses) when a device is LOCKED. On
   * success, returned AVB_IO_RESULT_OK and populates |hash|.
   */
  AvbIOResult (*read_permanent_attributes_hash)(
      AvbAtxOps* atx_ops, uint8_t hash[AVB_SHA256_DIGEST_SIZE]);

  /* Provides the key version of a key used during verification. This may be
   * useful for managing the minimum key version.
   */
  void (*set_key_version)(AvbAtxOps* atx_ops,
                          size_t rollback_index_location,
                          uint64_t key_version);

  /* Generates |num_bytes| random bytes and stores them in |output|,
   * which must point to a buffer large enough to store the bytes.
   *
   * Returns AVB_IO_RESULT_OK on success, otherwise an error code.
   */
  AvbIOResult (*get_random)(AvbAtxOps* atx_ops,
                            size_t num_bytes,
                            uint8_t* output);
};

#ifdef __cplusplus
}
#endif

#endif /* AVB_ATX_OPS_H_ */
