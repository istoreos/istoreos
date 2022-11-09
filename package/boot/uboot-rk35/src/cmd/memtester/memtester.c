/* SPDX-License-Identifier: GPL-2.0 */
/*
 * memtester version 4
 *
 * Very simple but very effective user-space memory tester.
 * Originally by Simon Kirby <sim@stormix.com> <sim@neato.org>
 * Version 2 by Charles Cazabon <charlesc-memtester@pyropus.ca>
 * Version 3 not publicly released.
 * Version 4 rewrite:
 * Copyright (C) 2004-2012 Charles Cazabon <charlesc-memtester@pyropus.ca>
 * Licensed under the terms of the GNU General Public License version 2 (only).
 * See the file COPYING for details.
 *
 */

#define __version__ "4.3.0"

#include <common.h>
#include <console.h>
#include "sizes.h"
#include "types.h"
#include "tests.h"
#include "io_map.h"
#include "ddr_tester_common.h"

#define EXIT_FAIL_NONSTARTER    0x01
#define EXIT_FAIL_ADDRESSLINES  0x02
#define EXIT_FAIL_OTHERTEST     0x04

struct test tests[] = {
	{"Random Value", test_random_value},
	{"Compare XOR", test_xor_comparison},
	{"Compare SUB", test_sub_comparison},
	{"Compare MUL", test_mul_comparison},
	{"Compare DIV", test_div_comparison},
	{"Compare OR", test_or_comparison},
	{"Compare AND", test_and_comparison},
	{"Sequential Increment", test_seqinc_comparison},
	{"Solid Bits", test_solidbits_comparison},
	{"Block Sequential", test_blockseq_comparison},
	{"Checkerboard", test_checkerboard_comparison},
	{"Bit Spread", test_bitspread_comparison},
	{"Bit Flip", test_bitflip_comparison},
	{"Walking Ones", test_walkbits1_comparison},
	{"Walking Zeroes", test_walkbits0_comparison},
#ifdef TEST_NARROW_WRITES
	{"8-bit Writes", test_8bit_wide_random},
	{"16-bit Writes", test_16bit_wide_random},
#endif
	{NULL, NULL}
};

int use_phys;
off_t physaddrbase;

/*
 * arg[0]: test start address
 * arg[1]: test length, unit: byte
 * testenable: enable test case, if 0 enable all case
 * loops: test loops, if 0 endless loop
 * err_exit: 1: exit test when found fail.
 * return 0: success, other: fail
 */
int doing_memtester(ul *arg, ul testenable, ul loops, ul err_exit,
		    ul fix_bit, ul fix_level)
{
	ul loop, i, j;
	ul start_adr[CONFIG_NR_DRAM_BANKS], length[CONFIG_NR_DRAM_BANKS];
	u32v * bufa[CONFIG_NR_DRAM_BANKS], *bufb[CONFIG_NR_DRAM_BANKS];
	ul count[CONFIG_NR_DRAM_BANKS];
	int exit_code = 0;
	int abort = 0;
	int test_banks;

	get_print_available_addr(start_adr, length, 0);

	test_banks = judge_test_addr(arg, start_adr, length);

	if (!test_banks) {
		printf("unavailable test address\n");
		return -1;
	}

	for (i = 0; i < ARRAY_SIZE(start_adr); i++) {
		bufa[i] = (u32v *)start_adr[i];
		bufb[i] = (u32v *)(start_adr[i] + length[i] / 2);
		count[i] = length[i] / 2 / sizeof(u32);
	}

	data_cpu_2_io_init();

	for (loop = 1; ((!loops) || loop <= loops); loop++) {
		for (j = 0; j < test_banks; j++) {
			if (!count[j])
				continue;
			printf("testing:0x%lx - 0x%lx\n", (ul)bufa[j],
			       (ul)bufa[j] + count[j] * 2 * sizeof(u32));
			printf("Loop %lu", loop);
			if (loops)
				printf("/%lu", loops);
			printf(":\n");
			if (testenable && ((1 << 17) & testenable)) {
				printf("  %-20s: ", "Stuck Address");
				if (!test_stuck_address(bufa[j], count[j] * 2))
					printf("ok\n");
				else
					exit_code |= EXIT_FAIL_ADDRESSLINES;
			}
			for (i = 0;; i++) {
				if (!tests[i].name)
					break;
				/* If using a custom testenable, only run this
				 * test if the bit corresponding to this test
				 * was set by the user.
				 */
				if (testenable && (!((1 << i) & testenable)))
					continue;
				printf("  %-20s: ", tests[i].name);
				if (!tests[i].fp(bufa[j], bufb[j], count[j],
						 fix_bit, fix_level)) {
					printf("ok\n");
				} else {
					exit_code |= EXIT_FAIL_OTHERTEST;
					if (err_exit) {
						goto out;
					}
				}
				if (ctrlc()) {
					abort = 1;
					break;
				}
			}
			printf("\n");
			if (abort)
				break;
		}
		if (abort)
			break;
	}

out:
	if (exit_code & EXIT_FAIL_NONSTARTER)
		printf("Fail: EXIT_FAIL_NONSTARTER\n");
	if (exit_code & EXIT_FAIL_ADDRESSLINES)
		printf("Fail: EXIT_FAIL_ADDRESSLINES\n");
	if (exit_code & EXIT_FAIL_OTHERTEST)
		printf("Fail: EXIT_FAIL_OTHERTEST\n");

	if (exit_code)
		return -1;
	return 0;
}

static int do_memtester(cmd_tbl_t *cmdtp, int flag, int argc,
			char *const argv[])
{
	ul start_adr[CONFIG_NR_DRAM_BANKS], length[CONFIG_NR_DRAM_BANKS];
	ul arg[2];
	ul loops = 0;
	ul testenable = 0;
	ul err_exit = 0;
	ul fix_bit = 0;
	ul fix_level = 0;

	printf("memtester version " __version__ " (%d-bit)\n", UL_LEN);
	printf("Copyright (C) 2001-2012 Charles Cazabon.\n");
	printf("Licensed under the GNU General Public License version 2 (only).\n");
	printf("\n");

	get_print_available_addr(start_adr, length, 1);

	if (argc < 2)
		return CMD_RET_USAGE;

	if (strict_strtoul(argv[1], 0, &arg[0]) < 0)
		return CMD_RET_USAGE;

	if (argc > 2)
		if (strict_strtoul(argv[2], 0, &arg[1]) < 0)
			return CMD_RET_USAGE;

	if (argc > 3)
		if (strict_strtoul(argv[3], 0, &testenable) < 0)
			return CMD_RET_USAGE;

	if (argc > 4)
		if (strict_strtoul(argv[4], 0, &err_exit) < 0)
			return CMD_RET_USAGE;

	if (argc > 5)
		if (strict_strtoul(argv[5], 0, &fix_bit) < 0)
			return CMD_RET_USAGE;

	if (argc > 6)
		if (strict_strtoul(argv[6], 0, &fix_level) < 0)
			return CMD_RET_USAGE;

	if (argc > 7)
		if (strict_strtoul(argv[7], 0, &loops) < 0)
			return CMD_RET_USAGE;

	doing_memtester(arg, testenable, loops, err_exit, fix_bit, fix_level);

	printf("Done.\n");
	return 0;
}

U_BOOT_CMD(memtester, 8, 1, do_memtester,
	   "do memtester",
	   "[start length [testenable err_exit fix_bit fix_level [loop]]]\n"
	   "start: start address, should be 4k align\n"
	   "length: test length, should be 4k align, if 0 testing full space\n"
	   "testenable[option]: enable pattern by set bit to 1, null or 0"
	   " enable all pattern\n"
	   "	bit0: Random Value\n"
	   "	bit1: Compare XOR\n"
	   "	bit2: Compare SUB\n"
	   "	bit3: Compare MUL\n"
	   "	bit4: Compare DIV\n"
	   "	bit5: Compare OR\n"
	   "	bit6: Compare AND\n"
	   "	bit7: Sequential Increment\n"
	   "	bit8: Solid Bits\n"
	   "	bit9: Block Sequential\n"
	   "	bit10: Checkerboard\n"
	   "	bit11: Bit Spread\n"
	   "	bit12: Bit Flip\n"
	   "	bit13: Walking Ones\n"
	   "	bit14: Walking Zeroes\n"
	   "	bit15: 8-bit Writes\n"
	   "	bit16: 16-bit Writes\n"
	   "	bit17: test stuck address\n"
	   "	example: testenable=0x1000,enable Bit Flip only\n"
	   "err_exit: if 1 stop testing immediately when finding error\n"
	   "fix_bit: fixed bit to a exact level\n"
	   "fix_level: fix_bit's level, 0: low, 1: high\n"
	   "loop[option]: testing loop, if 0 or null endless loop\n"
	   "example:\n"
	   "	memtester 0x200000 0x1000000: start address: 0x200000 length:"
	   "0x1000000, enable all pattern, endless loop\n"
	   "	memtester 0x200000 0x1000000 0x1000 100: start address:0x200000"
	   " length:0x1000000, Bit Flip only, loop 100 times\n"
	   "	memtester 0 0: testing full space\n");
