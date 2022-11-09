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
#if !defined(AVB_INSIDE_LIBAVB_AB_H) && !defined(AVB_COMPILATION)
#error \
    "Never include this file directly, include libavb_ab/libavb_ab.h instead."
#endif
*/

#ifndef AVB_AB_OPS_H_
#define AVB_AB_OPS_H_

#include <android_avb/libavb.h>

#ifdef __cplusplus
extern "C" {
#endif

struct AvbABOps;
typedef struct AvbABOps AvbABOps;

struct AvbABData;

/* High-level operations/functions/methods for A/B that are platform
 * dependent.
 */
struct AvbABOps {
  /* Operations from libavb. */
  AvbOps* ops;

  /* Reads A/B metadata from persistent storage. Returned data is
   * properly byteswapped. Returns AVB_IO_RESULT_OK on success, error
   * code otherwise.
   *
   * If the data read is invalid (e.g. wrong magic or CRC checksum
   * failure), the metadata shoule be reset using avb_ab_data_init()
   * and then written to persistent storage.
   *
   * Implementations will typically want to use avb_ab_data_read()
   * here to use the 'misc' partition for persistent storage.
   */
  AvbIOResult (*read_ab_metadata)(AvbABOps* ab_ops, struct AvbABData* data);

  /* Writes A/B metadata to persistent storage. This will byteswap and
   * update the CRC as needed. Returns AVB_IO_RESULT_OK on success,
   * error code otherwise.
   *
   * Implementations will typically want to use avb_ab_data_write()
   * here to use the 'misc' partition for persistent storage.
   */
  AvbIOResult (*write_ab_metadata)(AvbABOps* ab_ops,
                                   const struct AvbABData* data);
};

#ifdef __cplusplus
}
#endif

#endif /* AVB_AB_OPS_H_ */
