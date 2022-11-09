/*
 * (C) Copyright 2019 Rockchip Electronics Co., Ltd
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */

#ifndef __ROCKCHIP_FIT_H_
#define __ROCKCHIP_FIT_H_

#define FIT_I(fmt, args...)	printf("FIT: "fmt, ##args)

ulong fit_image_get_bootables_size(const void *fit);
void *fit_image_load_bootables(ulong *size);

int fit_image_pre_process(const void *fit);
int fit_image_fail_process(const void *fit);
int fit_image_init_resource(void);
int fit_image_read_dtb(void *fdt_addr);

#endif
