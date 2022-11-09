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

#include <android_avb/avb_hashtree_descriptor.h>
#include <android_avb/avb_util.h>

bool avb_hashtree_descriptor_validate_and_byteswap(
    const AvbHashtreeDescriptor* src, AvbHashtreeDescriptor* dest) {
  uint64_t expected_size;

  avb_memcpy(dest, src, sizeof(AvbHashtreeDescriptor));

  if (!avb_descriptor_validate_and_byteswap((const AvbDescriptor*)src,
                                            (AvbDescriptor*)dest))
    return false;

  if (dest->parent_descriptor.tag != AVB_DESCRIPTOR_TAG_HASHTREE) {
    avb_error("Invalid tag for hashtree descriptor.\n");
    return false;
  }

  dest->dm_verity_version = avb_be32toh(dest->dm_verity_version);
  dest->image_size = avb_be64toh(dest->image_size);
  dest->tree_offset = avb_be64toh(dest->tree_offset);
  dest->tree_size = avb_be64toh(dest->tree_size);
  dest->data_block_size = avb_be32toh(dest->data_block_size);
  dest->hash_block_size = avb_be32toh(dest->hash_block_size);
  dest->fec_num_roots = avb_be32toh(dest->fec_num_roots);
  dest->fec_offset = avb_be64toh(dest->fec_offset);
  dest->fec_size = avb_be64toh(dest->fec_size);
  dest->partition_name_len = avb_be32toh(dest->partition_name_len);
  dest->salt_len = avb_be32toh(dest->salt_len);
  dest->root_digest_len = avb_be32toh(dest->root_digest_len);
  dest->flags = avb_be32toh(dest->flags);

  /* Check that partition_name, salt, and root_digest are fully contained. */
  expected_size = sizeof(AvbHashtreeDescriptor) - sizeof(AvbDescriptor);
  if (!avb_safe_add_to(&expected_size, dest->partition_name_len) ||
      !avb_safe_add_to(&expected_size, dest->salt_len) ||
      !avb_safe_add_to(&expected_size, dest->root_digest_len)) {
    avb_error("Overflow while adding up sizes.\n");
    return false;
  }
  if (expected_size > dest->parent_descriptor.num_bytes_following) {
    avb_error("Descriptor payload size overflow.\n");
    return false;
  }
  return true;
}
