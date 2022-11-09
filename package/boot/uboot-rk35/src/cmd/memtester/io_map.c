// SPDX-License-Identifier: GPL-2.0+ OR BSD-3-Clause
/*
 * (C) Copyright 2019 Rockchip Electronics Co., Ltd.
 */

#include <common.h>
#include <asm/arch-rockchip/sdram.h>
#include "io_map.h"

#define IO_TYPE_1_1_16		0	/* up1 1:1 mode 16bit */
#define IO_TYPE_1_1_32		1	/* up1 1:1 mode 32bit */
#define IO_TYPE_1_2		2	/* up1 1:2 mode */
#define IO_TYPE_2		3	/* up2 */

static u32 io_type;

/* len should be 16byte align */
int data_cpu_2_io(void *p, u32 len)
{
	uchar *val = p;
	uchar buf[CPU_2_IO_ALIGN_LEN];
	u32 i, j;

	if ((len % sizeof(buf)) || !len)
		return -1;

	if (io_type == IO_TYPE_1_2) {
		len /= sizeof(buf);
		for (j = 0; j < len; j++) {
			memset(buf, 0, sizeof(buf));
			for (i = 0; i < sizeof(buf); i++)
				buf[i] = val[(i % 4) * 4 + i / 4 + j * sizeof(buf)];
			memcpy(&val[j * sizeof(buf)], buf, sizeof(buf));
		}
	} else if (io_type == IO_TYPE_1_1_32) {
		len /= 8;
		for (j = 0; j < len; j++) {
			memset(buf, 0, sizeof(buf));
			for (i = 0; i < 8; i++)
				buf[i] = val[(i % 4) * 2 + i / 4 + j * 8];
			memcpy(&val[j * 8], buf, 8);
		}
	}
	/* IO_TYPE_2 and IO_TYPE_1_1_16 do nothing*/
	return 0;
}

void data_cpu_2_io_init(void)
{
#if defined(CONFIG_ROCKCHIP_RK3036)
	io_type = IO_TYPE_1_1_16;
#elif defined(CONFIG_ROCKCHIP_RK3228) ||	\
	defined(CONFIG_ROCKCHIP_RV1108) ||	\
	defined(CONFIG_ROCKCHIP_RK3368) ||	\
	defined(CONFIG_ROCKCHIP_RK3366)
	io_type = IO_TYPE_1_2;
#elif defined(CONFIG_ROCKCHIP_RK3128) || \
	defined(CONFIG_ROCKCHIP_RK3288) ||	\
	defined(CONFIG_ROCKCHIP_RK3288)
	u32 bw;

	bw = get_ddr_bw();
	if (bw == 2)
		io_type = IO_TYPE_1_1_32;
	else
		io_type = IO_TYPE_1_1_16;
#elif defined(CONFIG_ROCKCHIP_RK3328) || \
	defined(CONFIG_ROCKCHIP_PX30) ||	\
	defined(CONFIG_ROCKCHIP_RK1808)
	io_type = IO_TYPE_2;
#else
	io_type = IO_TYPE_2;
#endif
}

