/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Very simple but very effective user-space memory tester.
 * Originally by Simon Kirby <sim@stormix.com> <sim@neato.org>
 * Version 2 by Charles Cazabon <charlesc-memtester@pyropus.ca>
 * Version 3 not publicly released.
 * Version 4 rewrite:
 * Copyright (C) 2004-2012 Charles Cazabon <charlesc-memtester@pyropus.ca>
 * Licensed under the terms of the GNU General Public License version 2 (only).
 * See the file COPYING for details.
 *
 * This file contains some macro definitions for handling 32/64 bit platforms.
 *
 */
#ifndef __MEMTESTER_SIZES_H
#define __MEMTESTER_SIZES_H

#include <common.h>

#define rand32() ((unsigned int)rand() | ((unsigned int)rand() << 16))

#define rand_ul() rand32()
#define UL_ONEBITS 0xffffffff
#define UL_LEN 32
#define CHECKERBOARD1 0x55555555
#define CHECKERBOARD2 0xaaaaaaaa
#define UL_BYTE(x) ((x | x << 8 | x << 16 | x << 24))

#endif /* __MEMTESTER_SIZES_H */
