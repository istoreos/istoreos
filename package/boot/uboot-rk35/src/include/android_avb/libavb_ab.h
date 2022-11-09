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

#ifndef LIBAVB_AB_H_
#define LIBAVB_AB_H_

#include <android_avb/libavb.h>

/* The libavb_ab/ and boot_control/ code has been marked for some time
 * as experimental in anticipation of being removed in the future. It
 * is now deprecated and to continue using it you must define
 * AVB_AB_I_UNDERSTAND_LIBAVB_AB_IS_DEPRECATED. It will be removed Jun
 * 1 2018.
 */

/*
#ifndef AVB_AB_I_UNDERSTAND_LIBAVB_AB_IS_DEPRECATED
#error \
    "You must define AVB_AB_I_UNDERSTAND_LIBAVB_AB_IS_DEPRECATED to use this library."
#endif
*/

/* The AVB_INSIDE_LIBAVB_AB_H preprocessor symbol is used to enforce
 * library users to include only this file. All public interfaces, and
 * only public interfaces, must be included here.
 */

#define AVB_INSIDE_LIBAVB_AB_H
#include <android_avb/avb_ab_flow.h>
#include <android_avb/avb_ab_ops.h>
#undef AVB_INSIDE_LIBAVB_AB_H

#endif /* LIBAVB_AB_H_ */
