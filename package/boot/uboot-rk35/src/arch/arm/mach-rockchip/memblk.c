// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (c) 2019 Fuzhou Rockchip Electronics Co., Ltd
 */

#include <common.h>
#include <memblk.h>

#define MEM_DEFINE(id, attr) 				\
	[MEM_##id] = {					\
		.name  = #id,				\
		.flags = attr,				\
	}

#define MEM_DEFINE_1(id, attr, alias0)			\
	[MEM_##id] = {					\
		.name     = #id,			\
		.flags    = attr,			\
		.alias[0] = alias0,			\
	}

#define MEM_DEFINE_2(id, attr, alias0, alias1)		\
	[MEM_##id] = {					\
		.name     = #id,			\
		.flags    = attr,			\
		.alias[0] = alias0, 			\
		.alias[1] = alias1,			\
	}

const static struct memblk_attr plat_mem_attr[MEM_MAX] = {
	/* Invisiable */
	MEM_DEFINE(ATF,		F_NONE),
	MEM_DEFINE(OPTEE,	F_NONE),

	/* U-Boot */
	MEM_DEFINE(UBOOT,	F_KMEM_CAN_OVERLAP),
	MEM_DEFINE(FASTBOOT,	F_KMEM_CAN_OVERLAP),
	MEM_DEFINE(STACK,	F_HOFC | F_KMEM_CAN_OVERLAP),

	/* Images */
	MEM_DEFINE(ANDROID,	F_HOFC | F_OFC | F_KMEM_CAN_OVERLAP),
	MEM_DEFINE(FDT,		F_OFC),
	MEM_DEFINE(FDT_DTBO,	F_OFC),
	MEM_DEFINE_1(SHM,	F_NONE, "ramoops"),
	MEM_DEFINE_2(RAMDISK,	F_OFC,  "boot", "recovery"),
	MEM_DEFINE(UNCOMP_KERNEL,F_IGNORE_INVISIBLE),
	MEM_DEFINE(FIT_USER,	F_OFC | F_KMEM_CAN_OVERLAP),
	MEM_DEFINE(UIMAGE_USER,	F_OFC | F_KMEM_CAN_OVERLAP),
	MEM_DEFINE(AVB_ANDROID, F_OFC | F_CACHELINE_ALIGN |
				F_KMEM_CAN_OVERLAP | F_HIGHEST_MEM),
	MEM_DEFINE(FIT,		F_OFC | F_CACHELINE_ALIGN |
				F_KMEM_CAN_OVERLAP | F_HIGHEST_MEM),
	MEM_DEFINE(UIMAGE,	F_OFC | F_CACHELINE_ALIGN |
				F_KMEM_CAN_OVERLAP | F_HIGHEST_MEM),
	MEM_DEFINE(RESOURCE, 	F_OFC),
	MEM_DEFINE(SEARCH,	F_OFC | F_CACHELINE_ALIGN | F_NO_FAIL_DUMP |
				F_KMEM_CAN_OVERLAP | F_HIGHEST_MEM),
	/*
	 * Workarund:
	 *
	 *  On aarch32 mode, ATF reserve 0~1MB memory that the same as aarch64
	 *  mode, but aarch32 mode actually occupies 0~192KB.
	 *  So that we allow kernel to alloc memory within 0~1MB.
	 */
#if defined(CONFIG_ROCKCHIP_RK3308) && defined(CONFIG_ARM64_BOOT_AARCH32)
	MEM_DEFINE(KERNEL, F_OFC | F_IGNORE_INVISIBLE),
#else
	MEM_DEFINE(KERNEL, F_OFC),
#endif
};

const struct memblk_attr *mem_attr = plat_mem_attr;
