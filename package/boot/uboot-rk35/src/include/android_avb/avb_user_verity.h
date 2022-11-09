/*
 * Copyright (C) 2017 The Android Open Source Project
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

#ifndef AVB_USER_VERITY_H_
#define AVB_USER_VERITY_H_

#include <android_avb/libavb.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function to enable or disable dm-verity for an entire slot. The
 * passed in |ops| should be obtained via avb_ops_user_new(). The
 * |ab_suffix| parameter should specify the slot to modify including
 * the leading underscore (e.g. "_a" or "_b"). The |enable_verity|
 * parameter should be set to |true| to enable dm-verity and |false|
 * to disable.
 *
 * Returns |true| if the operation succeeded, otherwise |false|.
 */
bool avb_user_verity_set(AvbOps* ops,
                         const char* ab_suffix,
                         bool enable_verity);

/* Gets whether dm-verity is enabled for an entire slot. The passed in
 * |ops| should be obtained via avb_ops_user_new(). The |ab_suffix|
 * parameter should specify the slot to query including the leading
 * underscore (e.g. "_a" or "_b"). The result is returned in the
 * |out_verity_enabled| parameter.
 *
 * Returns |true| if the operation succeeded, otherwise |false|.
 */
bool avb_user_verity_get(AvbOps* ops,
                         const char* ab_suffix,
                         bool* out_verity_enabled);

#ifdef __cplusplus
}
#endif

#endif /* AVB_USER_VERITY_H_ */
