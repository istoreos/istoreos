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

/*
#if !defined(AVB_INSIDE_LIBAVB_H) && !defined(AVB_COMPILATION)
#error "Never include this file directly, include libavb.h instead."
#endif
*/

#ifndef AVB_VERSION_H_
#define AVB_VERSION_H_

#include <android_avb/avb_sysdeps.h>

#ifdef __cplusplus
extern "C" {
#endif

/* The version number of AVB - keep in sync with avbtool. */
#define AVB_VERSION_MAJOR 1
#define AVB_VERSION_MINOR 1
#define AVB_VERSION_SUB 0

/* Returns a NUL-terminated string for the libavb version in use.  The
 * returned string usually looks like "%d.%d.%d". Applications must
 * not make assumptions about the content of this string.
 *
 * Boot loaders should display this string in debug/diagnostics output
 * to aid with debugging.
 *
 * This is similar to the string put in the |release_string| string
 * field in the VBMeta struct by avbtool.
 */
const char* avb_version_string(void);

#ifdef __cplusplus
}
#endif

#endif /* AVB_VERSION_H_ */
