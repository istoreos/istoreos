/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright (C) 2015-2019 Jason A. Donenfeld <Jason@zx2c4.com>. All Rights Reserved.
 */

#ifndef _WG_SIMD_H
#define _WG_SIMD_H

#include <linux/sched.h>
#include <asm/simd.h>
#if defined(CONFIG_X86_64)
#include <linux/version.h>
#include <asm/fpu/api.h>
#elif defined(CONFIG_KERNEL_MODE_NEON)
#include <asm/neon.h>
#endif

typedef enum {
	HAVE_NO_SIMD = 1 << 0,
	HAVE_FULL_SIMD = 1 << 1,
	HAVE_SIMD_IN_USE = 1 << 31
} simd_context_t;

#define DONT_USE_SIMD ((simd_context_t []){ HAVE_NO_SIMD })

static inline void simd_get(simd_context_t *ctx)
{
	*ctx = !IS_ENABLED(CONFIG_PREEMPT_RT_BASE) && may_use_simd() ? HAVE_FULL_SIMD : HAVE_NO_SIMD;
}

static inline void simd_put(simd_context_t *ctx)
{
#if defined(CONFIG_X86_64)
	if (*ctx & HAVE_SIMD_IN_USE)
		kernel_fpu_end();
#elif defined(CONFIG_KERNEL_MODE_NEON)
	if (*ctx & HAVE_SIMD_IN_USE)
		kernel_neon_end();
#endif
	*ctx = HAVE_NO_SIMD;
}

static inline bool simd_relax(simd_context_t *ctx)
{
#ifdef CONFIG_PREEMPT
	if ((*ctx & HAVE_SIMD_IN_USE) && need_resched()) {
		simd_put(ctx);
		simd_get(ctx);
		return true;
	}
#endif
	return false;
}

static __must_check inline bool simd_use(simd_context_t *ctx)
{
	if (!(*ctx & HAVE_FULL_SIMD))
		return false;
	if (*ctx & HAVE_SIMD_IN_USE)
		return true;
#if defined(CONFIG_X86_64)
	kernel_fpu_begin();
#elif defined(CONFIG_KERNEL_MODE_NEON)
	kernel_neon_begin();
#endif
	*ctx |= HAVE_SIMD_IN_USE;
	return true;
}

#endif /* _WG_SIMD_H */
