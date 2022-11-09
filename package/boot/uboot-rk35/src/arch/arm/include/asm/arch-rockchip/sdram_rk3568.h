/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * Copyright (C) 2021 Rockchip Electronics Co., Ltd.
 */

#ifndef _ASM_ARCH_SDRAM_RK3568_H
#define _ASM_ARCH_SDRAM_RK3568_H

#include <asm/arch-rockchip/sdram.h>
#include <asm/arch-rockchip/sdram_common.h>

/* store result of read and write training, for ddr_dq_eye tool in u-boot */
#define RW_TRN_RESULT_ADDR	(0x2000000 + 0x8000)	/* 32M + 32k */
#define PRINT_STEP		2

#undef FSP_NUM
#undef CS_NUM
#undef BYTE_NUM

#define FSP_NUM			4
#define CS_NUM			4
#define BYTE_NUM		5
#define RD_DESKEW_NUM		128
#define WR_DESKEW_NUM		256

#define LP4_WIDTH_REF_MHZ_H	1560
#define LP4_RD_WIDTH_REF_H	25
#define LP4_WR_WIDTH_REF_H	24

#define LP4_WIDTH_REF_MHZ_L	1184
#define LP4_RD_WIDTH_REF_L	30
#define LP4_WR_WIDTH_REF_L	29

#define DDR4_WIDTH_REF_MHZ_H	1560
#define DDR4_RD_WIDTH_REF_H	30
#define DDR4_WR_WIDTH_REF_H	22

#define DDR4_WIDTH_REF_MHZ_L	1184
#define DDR4_RD_WIDTH_REF_L	32
#define DDR4_WR_WIDTH_REF_L	26

#define LP3_WIDTH_REF_MHZ_H	1184
#define LP3_RD_WIDTH_REF_H	34
#define LP3_WR_WIDTH_REF_H	25

#define LP3_WIDTH_REF_MHZ_L	920
#define LP3_RD_WIDTH_REF_L	39
#define LP3_WR_WIDTH_REF_L	28

#define DDR3_WIDTH_REF_MHZ_H	1184
#define DDR3_RD_WIDTH_REF_H	32
#define DDR3_WR_WIDTH_REF_H	31

#define DDR3_WIDTH_REF_MHZ_L	920
#define DDR3_RD_WIDTH_REF_L	39
#define DDR3_WR_WIDTH_REF_L	34

#endif /* _ASM_ARCH_SDRAM_RK3568_H */
