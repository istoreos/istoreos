/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Very simple (yet, for some reason, very effective) memory tester.
 * Originally by Simon Kirby <sim@stormix.com> <sim@neato.org>
 * Version 2 by Charles Cazabon <charlesc-memtester@pyropus.ca>
 * Version 3 not publicly released.
 * Version 4 rewrite:
 * Copyright (C) 2004-2012 Charles Cazabon <charlesc-memtester@pyropus.ca>
 * Licensed under the terms of the GNU General Public License version 2 (only).
 * See the file COPYING for details.
 *
 * This file contains the declarations for external variables from the main file.
 * See other comments in that file.
 *
 */
#ifndef _CMD_MEMTESTER_H
#define _CMD_MEMTESTER_H
#include <linux/types.h>

/* extern declarations. */

extern int use_phys;
extern off_t physaddrbase;

int doing_memtester(unsigned long *arg, unsigned long testenable,
		    unsigned long loops, unsigned long err_exit,
		    unsigned long fix_bit, unsigned long fix_level);
#endif /* _CMD_MEMTESTER_H */
