/* SPDX-License-Identifier: ((GPL-2.0+ WITH Linux-syscall-note) OR MIT) */

/* Copyright (c) 2018 Fuzhou Rockchip Electronics Co., Ltd */

#include <linux/ioctl.h>

#ifndef _RKFLASH_VENDOR_STORAGE
#define _RKFLASH_VENDOR_STORAGE

struct RK_VENDOR_REQ {
	__u32 tag;
	__u16 id;
	__u16 len;
	__u8 data[1024];
};

#define VENDOR_REQ_TAG		0x56524551
#define VENDOR_READ_IO		_IOW('v', 0x01, __u32)
#define VENDOR_WRITE_IO		_IOW('v', 0x02, __u32)

#endif
