/* SPDX-License-Identifier: GPL-2.0+ OR BSD-3-Clause */
/*
 * Copyright (C) 2019 Rockchip Electronics Co., Ltd.
 */

#ifndef _CMD_MEMTESTER_IO_MAP_H
#define _CMD_MEMTESTER_IO_MAP_H

#define CPU_2_IO_ALIGN_LEN		(16)	/* 16 byte */

int data_cpu_2_io(void *p, u32 len);
void data_cpu_2_io_init(void);

#endif /* _CMD_MEMTESTER_IO_MAP_H */
