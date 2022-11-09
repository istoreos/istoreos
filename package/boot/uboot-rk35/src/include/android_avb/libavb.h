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

#ifndef LIBAVB_H_
#define LIBAVB_H_

/* The AVB_INSIDE_LIBAVB_H preprocessor symbol is used to enforce
 * library users to include only this file. All public interfaces, and
 * only public interfaces, must be included here.
 */

#define AVB_INSIDE_LIBAVB_H
#include <android_avb/avb_chain_partition_descriptor.h>
#include <android_avb/avb_crypto.h>
#include <android_avb/avb_descriptor.h>
#include <android_avb/avb_footer.h>
#include <android_avb/avb_hash_descriptor.h>
#include <android_avb/avb_hashtree_descriptor.h>
#include <android_avb/avb_kernel_cmdline_descriptor.h>
#include <android_avb/avb_ops.h>
#include <android_avb/avb_property_descriptor.h>
#include <android_avb/avb_slot_verify.h>
#include <android_avb/avb_sysdeps.h>
#include <android_avb/avb_util.h>
#include <android_avb/avb_vbmeta_image.h>
#include <android_avb/avb_version.h>
#undef AVB_INSIDE_LIBAVB_H

#endif /* LIBAVB_H_ */
