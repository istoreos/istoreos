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

#ifndef AVB_PROPERTY_DESCRIPTOR_H_
#define AVB_PROPERTY_DESCRIPTOR_H_

#include <android_avb/avb_descriptor.h>

#ifdef __cplusplus
extern "C" {
#endif

/* A descriptor for properties (free-form key/value pairs).
 *
 * Following this struct are |key_num_bytes| bytes of key data,
 * followed by a NUL byte, then |value_num_bytes| bytes of value data,
 * followed by a NUL byte and then enough padding to make the combined
 * size a multiple of 8.
 */
typedef struct AvbPropertyDescriptor {
  AvbDescriptor parent_descriptor;
  uint64_t key_num_bytes;
  uint64_t value_num_bytes;
} AVB_ATTR_PACKED AvbPropertyDescriptor;

/* Copies |src| to |dest| and validates, byte-swapping fields in the
 * process if needed. Returns true if valid, false if invalid.
 *
 * Data following the struct is not validated nor copied.
 */
bool avb_property_descriptor_validate_and_byteswap(
    const AvbPropertyDescriptor* src,
    AvbPropertyDescriptor* dest) AVB_ATTR_WARN_UNUSED_RESULT;

/* Convenience function for looking up the value for a property with
 * name |key| in a vbmeta image. If |key_size| is 0, |key| must be
 * NUL-terminated.
 *
 * The |image_data| parameter must be a pointer to a vbmeta image of
 * size |image_size|.
 *
 * This function returns a pointer to the value inside the passed-in
 * image or NULL if not found. Note that the value is always
 * guaranteed to be followed by a NUL byte.
 *
 * If the value was found and |out_value_size| is not NULL, the size
 * of the value is returned there.
 *
 * This function is O(n) in number of descriptors so if you need to
 * look up a lot of values, you may want to build a more efficient
 * lookup-table by manually walking all descriptors using
 * avb_descriptor_foreach().
 *
 * Before using this function, you MUST verify |image_data| with
 * avb_vbmeta_image_verify() and reject it unless it's signed by a
 * known good public key.
 */
const char* avb_property_lookup(const uint8_t* image_data,
                                size_t image_size,
                                const char* key,
                                size_t key_size,
                                size_t* out_value_size)
    AVB_ATTR_WARN_UNUSED_RESULT;

/* Like avb_property_lookup() but parses the intial portions of the
 * value as an unsigned 64-bit integer. Both decimal and hexadecimal
 * representations (e.g. "0x2a") are supported. Returns false on
 * failure and true on success. On success, the parsed value is
 * returned in |out_value|.
 */
bool avb_property_lookup_uint64(const uint8_t* image_data,
                                size_t image_size,
                                const char* key,
                                size_t key_size,
                                uint64_t* out_value)
    AVB_ATTR_WARN_UNUSED_RESULT;

#ifdef __cplusplus
}
#endif

#endif /* AVB_PROPERTY_DESCRIPTOR_H_ */
