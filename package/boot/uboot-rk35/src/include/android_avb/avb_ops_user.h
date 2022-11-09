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

#ifndef AVB_OPS_USER_H_
#define AVB_OPS_USER_H_

#include <android_avb/libavb.h>
#include <android_avb/avb_ab_flow.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Allocates an AvbOps instance suitable for use in Android userspace
 * on the device. Returns NULL on OOM.
 *
 * The returned AvbOps has the following characteristics:
 *
 * - The read_from_partition(), write_to_partition(), and
 *   get_size_of_partition() operations are implemented, however for
 *   these operations to work the fstab file on the device must have a
 *   /misc entry using a by-name device file scheme and the containing
 *   by-name/ subdirectory must have files for other partitions.
 *
 * - The remaining operations are implemented and never fails and
 *   return the following values:
 *   - validate_vbmeta_public_key(): always returns |true|.
 *   - read_rollback_index(): returns 0 for any roolback index.
 *   - write_rollback_index(): no-op.
 *   - read_is_device_unlocked(): always returns |true|.
 *   - get_unique_guid_for_partition(): always returns the empty string.
 *
 * - The |ab_ops| member will point to a valid AvbABOps instance
 *   implemented via libavb_ab/. This should only be used if the AVB
 *   A/B stack is used on the device. This is what is used in
 *   bootctrl.avb boot control implementation.
 *
 * Free with avb_ops_user_free().
 */
AvbOps* avb_ops_user_new(void);

/* Frees an AvbOps instance previously allocated with avb_ops_device_new(). */
void avb_ops_user_free(AvbOps* ops);

#ifdef __cplusplus
}
#endif

#endif /* AVB_OPS_USER_H_ */
