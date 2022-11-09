// SPDX-License-Identifier: GPL-2.0+ OR BSD-3-Clause
/*
 * (C) Copyright 2019 Rockchip Electronics Co., Ltd.
 */

#include <common.h>
#include <power/regulator.h>
#include "ddr_tester_common.h"

DECLARE_GLOBAL_DATA_PTR;

void write_buf_to_ddr(u32 *buf, u32 buf_len, ulong start_adr, ulong length)
{
	ulong *buful = (ulong *)buf;
	ulong *p = (ulong *)start_adr;
	u32 i, j;

	buf_len = buf_len / sizeof(ulong) - 1;

	for (i = 0, j = 0; i < length / sizeof(p[0]); i++) {
		p[i] = buful[j];
		j++;
		j &= buf_len;
	}
}

ulong cmp_buf_data(u32 *buf, u32 buf_len, ulong start_adr, ulong length,
		   u32 prt_en)
{
	ulong *buful = (ulong *)buf;
	volatile unsigned long *p = (volatile unsigned long *)start_adr;
	u32 i, j;
	ulong reread = 0;
	ulong wr_val = 0;
	ulong val = 0;
	ulong err_adr = 0;

	buf_len = buf_len / sizeof(ulong) - 1;
	err_adr = 0;
	for (i = 0, j = 0; i < length / sizeof(p[0]); i++) {
		val = p[i];
		if (val != buful[j]) {
			flush_dcache_range((ulong)&p[i],
					   (ulong)&p[i] + sizeof(u32));
			reread = p[i];
			err_adr = (ulong)&p[i];
			wr_val = buful[j];
			break;
		}
		j++;
		j &= buf_len;
	}
	if (err_adr && prt_en)
		printf("test fail:address:0x%lx,read:0x%lx,"
		       "reread:0x%lx,expect:0x%lx\n",
		       err_adr, val, reread, wr_val);

	return err_adr;
}

void print_memory(void *addr, ulong size)
{
	u32 *p = addr;
	u32 i;

	for (i = 0; i < size / 4; i += 4) {
		printf("0x%08lx: 0x%08x, 0x%08x, 0x%08x, 0x%08x\n",
		       (ulong)&p[i], p[i], p[i + 1], p[i + 2], p[i + 3]);
	}
}

/* print available address for ddr testing in uboot */
void get_print_available_addr(ulong *start_adr, ulong *length, int print_en)
{
	u32 i, max_bank = 0;

	for (i = 0; i < CONFIG_NR_DRAM_BANKS; i++) {
		if (gd->bd->bi_dram[i].start)
			max_bank = i + 1;
		start_adr[i] = 0;
		length[i] = 0;
	}

	for (i = 0; i < max_bank; i++) {
		start_adr[i] = gd->bd->bi_dram[i].start;
		length[i] = gd->bd->bi_dram[i].size;
	}

	length[max_bank - 1] = (gd->start_addr_sp - RESERVED_SP_SIZE -
			start_adr[max_bank - 1]) & ~0xfff;
	if (print_en) {
		printf("available memory for test:\n");
		printf("	start		 end	length\n");
		for (i = 0; i < max_bank; i++)
			if (length[i])
				printf("	0x%08lx - 0x%08lx 0x%08lx\n",
				       start_adr[i], start_adr[i] + length[i],
				       length[i]);
	}
}

/*
 * judge if testing address is available
 * arg[0]:start addr, arg[1]:length, return test banks number
 */
int judge_test_addr(ulong *arg, ulong *start_adr, ulong *length)
{
	u32 i, max_bank = 0;
	u32 available = 0;

	for (i = 0; i < CONFIG_NR_DRAM_BANKS; i++)
		if (start_adr[i])
			max_bank = i + 1;

	if (!arg[1])
		return max_bank;

	for (i = 0; i < max_bank; i++)
		if (arg[0] >= start_adr[i] &&
		    arg[0] + arg[1] <= start_adr[i] + length[i])
			available |= 1;
	if (!available) {
		printf("Invalid test address\n");
	} else {
		start_adr[0] = arg[0];
		length[0] = arg[1];
		for (i = 1; i < max_bank; i++) {
			start_adr[i] = 0;
			length[i] = 0;
		}
	}

	return available;
}

int set_vdd_logic(u32 uv)
{
	struct udevice *dev;
	int ret;

	ret = regulator_get_by_platname("vdd_logic", &dev);
	if (ret) {
		printf("Cannot set regulator name\n");
		return ret;
	}

	/* Slowly raise to max CPU voltage to prevent overshoot */
	ret = regulator_set_value(dev, uv);
	udelay(100); /* Must wait for voltage to stabilize, 2mV/us */
	if (ret)
		printf("set vdd_logic fail\n");
	return ret;
}

