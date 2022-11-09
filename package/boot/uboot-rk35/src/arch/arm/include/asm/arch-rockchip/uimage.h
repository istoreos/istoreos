/*
 * (C) Copyright 2019 Rockchip Electronics Co., Ltd
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */

#ifndef __ROCKCHIP_UIMAGE_H_
#define __ROCKCHIP_UIMAGE_H_

#define UIMG_I(fmt, args...)	printf("uImage: "fmt, ##args)

void *uimage_load_bootables(void);
int uimage_sysmem_free_each(image_header_t *img, u32 ramdisk_sz);
int uimage_sysmem_reserve_each(image_header_t *hdr, u32 *ramdisk_sz);
int uimage_init_resource(void);

#endif

