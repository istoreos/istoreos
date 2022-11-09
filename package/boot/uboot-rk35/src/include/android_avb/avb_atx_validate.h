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

#ifndef AVB_ATX_VALIDATE_H_
#define AVB_ATX_VALIDATE_H_

#include <android_avb/avb_atx_ops.h>
#include <android_avb/avb_atx_types.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Rollback index locations for Android Things key versions. */
#define AVB_ATX_PIK_VERSION_LOCATION 0x1000
#define AVB_ATX_PSK_VERSION_LOCATION 0x1001

/* An implementation of validate_vbmeta_public_key for Android Things. See
 * libavb/avb_ops.h for details on validate_vbmeta_public_key in general. This
 * implementation uses the metadata expected with Android Things vbmeta images
 * to perform validation on the public key. The ATX ops must be implemented.
 * That is, |ops->atx_ops| must be valid.
 *
 * There are a multiple values that need verification:
 *   - Permanent Product Attributes: A hash of these attributes is fused into
 *                                   hardware. Consistency is checked.
 *   - Product Root Key (PRK): This key is provided in permanent attributes and
 *                             is the root authority for all Android Things
 *                             products.
 *   - Product Intermediate Key (PIK): This key is a rotated intermediary. It is
 *                                     certified by the PRK.
 *   - Product Signing Key (PSK): This key is a rotated authority for a specific
 *                                Android Things product. It is certified by a
 *                                PIK and must match |public_key_data|.
 *   - Product ID: This value is provided in permanent attributes and is unique
 *                 to a specific Android Things product. This value must match
 *                 the subject of the PSK certificate.
 */
AvbIOResult avb_atx_validate_vbmeta_public_key(
    AvbOps* ops,
    const uint8_t* public_key_data,
    size_t public_key_length,
    const uint8_t* public_key_metadata,
    size_t public_key_metadata_length,
    bool* out_is_trusted);

/* Generates a challenge which can be used to create an unlock credential. */
AvbIOResult avb_atx_generate_unlock_challenge(
    AvbAtxOps* atx_ops, AvbAtxUnlockChallenge* out_unlock_challenge);

/* Validates an unlock credential. The certificate validation is very similar to
 * the validation of public key metadata except in place of the PSK is a Product
 * Unlock Key (PUK) and the certificate usage field identifies it as such. The
 * challenge signature field is verified against this PUK.
 */
AvbIOResult avb_atx_validate_unlock_credential(
    AvbAtxOps* atx_ops,
    const AvbAtxUnlockCredential* unlock_credential,
    bool* out_is_trusted);

#ifdef __cplusplus
}
#endif

#endif /* AVB_ATX_VALIDATE_H_ */
