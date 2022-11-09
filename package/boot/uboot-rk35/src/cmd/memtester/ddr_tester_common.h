/* SPDX-License-Identifier: GPL-2.0+ OR BSD-3-Clause */
/*
 * Copyright (C) 2019 Rockchip Electronics Co., Ltd.
 */

/* Function declaration. */
#ifndef _CMD_MEMTESTER_DDR_TOOL_COMMON_H
#define _CMD_MEMTESTER_DDR_TOOL_COMMON_H

/* reserved 1MB for stack */
#define RESERVED_SP_SIZE		0x100000

void write_buf_to_ddr(u32 *buf, u32 buf_len, ulong start_adr, ulong length);
ulong cmp_buf_data(u32 *buf, u32 buf_len, ulong start_adr,
		   ulong length, u32 prt_en);
void print_memory(void *addr, ulong size);
void get_print_available_addr(ulong *start_adr, ulong *length, int print_en);
int judge_test_addr(ulong *arg, ulong *start_adr, ulong *length);
int set_vdd_logic(u32 uv);
#endif /* _CMD_MEMTESTER_DDR_TOOL_COMMON_H */
