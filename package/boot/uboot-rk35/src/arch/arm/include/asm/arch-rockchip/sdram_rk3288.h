/*
 * Copyright (c) 2015 Google, Inc
 *
 * Copyright 2014 Rockchip Inc.
 *
 * SPDX-License-Identifier:	GPL-2.0
 */

#ifndef _ASM_ARCH_RK3288_SDRAM_H__
#define _ASM_ARCH_RK3288_SDRAM_H__

struct rk3288_sdram_channel {
	/*
	 * bit width in address, eg:
	 * 8 banks using 3 bit to address,
	 * 2 cs using 1 bit to address.
	 */
	u8 rank;
	u8 col;
	u8 bk;
	u8 bw;
	u8 dbw;
	u8 row_3_4;
	u8 cs0_row;
	u8 cs1_row;
#if CONFIG_IS_ENABLED(OF_PLATDATA)
	/*
	 * For of-platdata, which would otherwise convert this into two
	 * byte-swapped integers. With a size of 9 bytes, this struct will
	 * appear in of-platdata as a byte array.
	 *
	 * If OF_PLATDATA enabled, need to add a dummy byte in dts.(i.e 0xff)
	 */
	u8 dummy;
#endif
};

struct rk3288_sdram_pctl_timing {
	u32 togcnt1u;
	u32 tinit;
	u32 trsth;
	u32 togcnt100n;
	u32 trefi;
	u32 tmrd;
	u32 trfc;
	u32 trp;
	u32 trtw;
	u32 tal;
	u32 tcl;
	u32 tcwl;
	u32 tras;
	u32 trc;
	u32 trcd;
	u32 trrd;
	u32 trtp;
	u32 twr;
	u32 twtr;
	u32 texsr;
	u32 txp;
	u32 txpdll;
	u32 tzqcs;
	u32 tzqcsi;
	u32 tdqs;
	u32 tcksre;
	u32 tcksrx;
	u32 tcke;
	u32 tmod;
	u32 trstl;
	u32 tzqcl;
	u32 tmrr;
	u32 tckesr;
	u32 tdpd;
};
check_member(rk3288_sdram_pctl_timing, tdpd, 0x144 - 0xc0);

struct rk3288_sdram_phy_timing {
	u32 dtpr0;
	u32 dtpr1;
	u32 dtpr2;
	u32 mr[4];
};

struct rk3288_base_params {
	u32 noc_timing;
	u32 noc_activate;
	u32 ddrconfig;
	u32 ddr_freq;
	u32 dramtype;
	/*
	 * DDR Stride is address mapping for DRAM space
	 * Stride	Ch 0 range	Ch1 range	Total
	 * 0x00		0-256MB		256MB-512MB	512MB
	 * 0x05		0-1GB		0-1GB		1GB
	 * 0x09		0-2GB		0-2GB		2GB
	 * 0x0d		0-4GB		0-4GB		4GB
	 * 0x17		N/A		0-4GB		4GB
	 * 0x1a		0-4GB		4GB-8GB		8GB
	 */
	u32 stride;
	u32 odt;
};

#endif
