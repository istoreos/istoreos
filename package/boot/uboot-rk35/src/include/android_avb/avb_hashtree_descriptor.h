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

#ifndef AVB_HASHTREE_DESCRIPTOR_H_
#define AVB_HASHTREE_DESCRIPTOR_H_

#include <android_avb/avb_descriptor.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Flags for hashtree descriptors.
 *
 * AVB_HASHTREE_DESCRIPTOR_FLAGS_DO_NOT_USE_AB: Do not apply the default A/B
 *   partition logic to this partition. This is intentionally a negative boolean
 *   because A/B should be both the default and most used in practice.
 */
typedef enum {
  AVB_HASHTREE_DESCRIPTOR_FLAGS_DO_NOT_USE_AB = (1 << 0),
} AvbHashtreeDescriptorFlags;

/* A descriptor containing information about a dm-verity hashtree.
 *
 * Hash-trees are used to verify large partitions typically containing
 * file systems. See
 * https://gitlab.com/cryptsetup/cryptsetup/wikis/DMVerity for more
 * information about dm-verity.
 *
 * Following this struct are |partition_name_len| bytes of the
 * partition name (UTF-8 encoded), |salt_len| bytes of salt, and then
 * |root_digest_len| bytes of the root digest.
 *
 * The |reserved| field is for future expansion and must be set to NUL
 * bytes.
 *
 * Changes in v1.1:
 *   - flags field is added which supports AVB_HASHTREE_DESCRIPTOR_FLAGS_USE_AB
 *   - digest_len may be zero, which indicates the use of a persistent digest
 */
typedef struct AvbHashtreeDescriptor {
  AvbDescriptor parent_descriptor;
  uint32_t dm_verity_version;
  uint64_t image_size;
  uint64_t tree_offset;
  uint64_t tree_size;
  uint32_t data_block_size;
  uint32_t hash_block_size;
  uint32_t fec_num_roots;
  uint64_t fec_offset;
  uint64_t fec_size;
  uint8_t hash_algorithm[32];
  uint32_t partition_name_len;
  uint32_t salt_len;
  uint32_t root_digest_len;
  uint32_t flags;
  uint8_t reserved[60];
} AVB_ATTR_PACKED AvbHashtreeDescriptor;

/* Copies |src| to |dest| and validates, byte-swapping fields in the
 * process if needed. Returns true if valid, false if invalid.
 *
 * Data following the struct is not validated nor copied.
 */
bool avb_hashtree_descriptor_validate_and_byteswap(
    const AvbHashtreeDescriptor* src,
    AvbHashtreeDescriptor* dest) AVB_ATTR_WARN_UNUSED_RESULT;

#ifdef __cplusplus
}
#endif

#endif /* AVB_HASHTREE_DESCRIPTOR_H_ */
