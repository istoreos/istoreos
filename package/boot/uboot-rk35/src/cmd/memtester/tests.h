/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Very simple yet very effective memory tester.
 * Originally by Simon Kirby <sim@stormix.com> <sim@neato.org>
 * Version 2 by Charles Cazabon <charlesc-memtester@pyropus.ca>
 * Version 3 not publicly released.
 * Version 4 rewrite:
 * Copyright (C) 2004-2012 Charles Cazabon <charlesc-memtester@pyropus.ca>
 * Licensed under the terms of the GNU General Public License version 2 (only).
 * See the file COPYING for details.
 *
 * This file contains the declarations for the functions for the actual tests,
 * called from the main routine in memtester.c.  See other comments in that
 * file.
 *
 */

/* Function declaration. */

int test_stuck_address(u32v *bufa, size_t count);
int test_random_value(u32v *bufa,
		      u32v *bufb, size_t count, ul fix_bit, ul fix_level);
int test_xor_comparison(u32v *bufa,
			u32v *bufb, size_t count, ul fix_bit, ul fix_level);
int test_sub_comparison(u32v *bufa,
			u32v *bufb, size_t count, ul fix_bit, ul fix_level);
int test_mul_comparison(u32v *bufa,
			u32v *bufb, size_t count, ul fix_bit, ul fix_level);
int test_div_comparison(u32v *bufa,
			u32v *bufb, size_t count, ul fix_bit, ul fix_level);
int test_or_comparison(u32v *bufa,
		       u32v *bufb, size_t count, ul fix_bit, ul fix_level);
int test_and_comparison(u32v *bufa,
			u32v *bufb, size_t count, ul fix_bit, ul fix_level);
int test_seqinc_comparison(u32v *bufa, u32v *bufb, size_t count,
			   ul fix_bit, ul fix_level);
int test_solidbits_comparison(u32v *bufa, u32v *bufb, size_t count,
			      ul fix_bit, ul fix_level);
int test_checkerboard_comparison(u32v *bufa, u32v *bufb, size_t count,
				 ul fix_bit, ul fix_level);
int test_blockseq_comparison(u32v *bufa, u32v *bufb, size_t count,
			     ul fix_bit, ul fix_level);
int test_walkbits0_comparison(u32v *bufa, u32v *bufb, size_t count,
			      ul fix_bit, ul fix_level);
int test_walkbits1_comparison(u32v *bufa, u32v *bufb, size_t count,
			      ul fix_bit, ul fix_level);
int test_bitspread_comparison(u32v *bufa, u32v *bufb, size_t count,
			      ul fix_bit, ul fix_level);
int test_bitflip_comparison(u32v *bufa, u32v *bufb, size_t count,
			    ul fix_bit, ul fix_level);
#ifdef TEST_NARROW_WRITES
int test_8bit_wide_random(u32v *bufa, u32v *bufb, size_t count,
			  ul fix_bit, ul fix_level);
int test_16bit_wide_random(u32v *bufa, u32v *bufb, size_t count,
			   ul fix_bit, ul fix_level);
#endif
