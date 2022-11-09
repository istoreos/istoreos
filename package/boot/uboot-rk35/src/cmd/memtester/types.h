/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Very simple but very effective user-space memory tester.
 * Originally by Simon Kirby <sim@stormix.com> <sim@neato.org>
 * Version 2 by Charles Cazabon <charlesc-memtester@pyropus.ca>
 * Version 3 not publicly released.
 * Version 4 rewrite:
 * Copyright (C) 2004-2010 Charles Cazabon <charlesc-memtester@pyropus.ca>
 * Licensed under the terms of the GNU General Public License version 2 (only).
 * See the file COPYING for details.
 *
 * This file contains typedefs, structure, and union definitions.
 *
 */
#ifndef __MEMTESTER_TYPES_H
#define __MEMTESTER_TYPES_H

typedef unsigned long ul;
typedef unsigned long long ull;
/* for all rk chip, dram bandwidth both 32bit */
typedef unsigned int volatile u32v;
typedef unsigned char volatile u8v;
typedef unsigned short volatile u16v;

struct test {
	char *name;
	int (*fp)(u32v *bufa, u32v *bufb, size_t count,
		  ul fix_bit, ul fix_level);
};

#endif /* __MEMTESTER_TYPES_H */
