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

#include <android_avb/avb_kernel_cmdline_descriptor.h>
#include <android_avb/avb_util.h>

bool avb_kernel_cmdline_descriptor_validate_and_byteswap(
    const AvbKernelCmdlineDescriptor* src, AvbKernelCmdlineDescriptor* dest) {
  uint64_t expected_size;

  avb_memcpy(dest, src, sizeof(AvbKernelCmdlineDescriptor));

  if (!avb_descriptor_validate_and_byteswap((const AvbDescriptor*)src,
                                            (AvbDescriptor*)dest))
    return false;

  if (dest->parent_descriptor.tag != AVB_DESCRIPTOR_TAG_KERNEL_CMDLINE) {
    avb_error("Invalid tag for kernel cmdline descriptor.\n");
    return false;
  }

  dest->flags = avb_be32toh(dest->flags);
  dest->kernel_cmdline_length = avb_be32toh(dest->kernel_cmdline_length);

  /* Check that kernel_cmdline is fully contained. */
  expected_size = sizeof(AvbKernelCmdlineDescriptor) - sizeof(AvbDescriptor);
  if (!avb_safe_add_to(&expected_size, dest->kernel_cmdline_length)) {
    avb_error("Overflow while adding up sizes.\n");
    return false;
  }
  if (expected_size > dest->parent_descriptor.num_bytes_following) {
    avb_error("Descriptor payload size overflow.\n");
    return false;
  }

  return true;
}
