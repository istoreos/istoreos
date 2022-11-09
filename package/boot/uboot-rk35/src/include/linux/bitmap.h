// SPDX-License-Identifier: GPL-2.0+
#ifndef __LINUX_BITMAP_H
#define __LINUX_BITMAP_H

#include <asm/types.h>
#include <linux/types.h>
#include <linux/bitops.h>

#define small_const_nbits(nbits) \
	(__builtin_constant_p(nbits) && (nbits) <= BITS_PER_LONG)

static inline void bitmap_zero(unsigned long *dst, int nbits)
{
	if (small_const_nbits(nbits)) {
		*dst = 0UL;
	} else {
		int len = BITS_TO_LONGS(nbits) * sizeof(unsigned long);

		memset(dst, 0, len);
	}
}

#endif /* __LINUX_BITMAP_H */
