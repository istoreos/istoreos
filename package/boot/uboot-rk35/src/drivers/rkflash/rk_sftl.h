/*
 * Copyright (c) 2018 Fuzhou Rockchip Electronics Co., Ltd
 *
 * SPDX-License-Identifier:	GPL-2.0
 */

#ifndef __RK_SFTL_H
#define __RK_SFTL_H

u32 ftl_low_format(void);
int sftl_init(void);
int sftl_deinit(void);
int sftl_read(u32 index, u32 count, u8 *buf);
int sftl_write(u32 index, u32 count, u8 *buf);
u32 sftl_get_density(void);
s32 sftl_gc(void);
int sftl_vendor_read(u32 index, u32 count, u8 *buf);
int sftl_vendor_write(u32 index, u32 count, u8 *buf);

void *ftl_malloc(int n_size);
void ftl_free(void *p);
void *ftl_memset(void *s, int c, unsigned int n);
void *ftl_memcpy(void *pv_to,
		 const void *pv_from,
		 unsigned int size);
#endif
