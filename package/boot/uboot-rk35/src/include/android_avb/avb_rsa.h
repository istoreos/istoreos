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

/* Copyright (c) 2011 The Chromium OS Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

/*
#ifdef AVB_INSIDE_LIBAVB_H
#error "You can't include avb_rsa.h in the public header libavb.h."
#endif
*/

/*
#ifndef AVB_COMPILATION
#error "Never include this file, it may only be used from internal avb code."
#endif
*/

#ifndef AVB_RSA_H_
#define AVB_RSA_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <android_avb/avb_crypto.h>
#include <android_avb/avb_sysdeps.h>

/* Using the key given by |key|, verify a RSA signature |sig| of
 * length |sig_num_bytes| against an expected |hash| of length
 * |hash_num_bytes|. The padding to expect must be passed in using
 * |padding| of length |padding_num_bytes|.
 *
 * The data in |key| must match the format defined in
 * |AvbRSAPublicKeyHeader|, including the two large numbers
 * following. The |key_num_bytes| must be the size of the entire
 * serialized key.
 *
 * Returns false if verification fails, true otherwise.
 */
bool avb_rsa_verify(const uint8_t* key,
                    size_t key_num_bytes,
                    const uint8_t* sig,
                    size_t sig_num_bytes,
                    const uint8_t* hash,
                    size_t hash_num_bytes,
                    const uint8_t* padding,
                    size_t padding_num_bytes) AVB_ATTR_WARN_UNUSED_RESULT;

#ifdef __cplusplus
}
#endif

#endif /* AVB_RSA_H_ */
