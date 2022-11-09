/* SPDX-License-Identifier:     GPL-2.0+ */
/*
 * Copyright (C) 2019 Rockchip Electronics Co., Ltd
 */

#ifndef _ASM_ARCH_SDRAM_MSCH_H
#define _ASM_ARCH_SDRAM_MSCH_H

union noc_ddrtiminga0 {
	u32 d32;
	struct {
		unsigned acttoact : 6;
		unsigned reserved0 : 2;
		unsigned rdtomiss : 6;
		unsigned reserved1 : 2;
		unsigned wrtomiss : 6;
		unsigned reserved2 : 2;
		unsigned readlatency : 8;
	} b;
};

union noc_ddrtimingb0 {
	u32 d32;
	struct {
		unsigned rdtowr : 5;
		unsigned reserved0 : 3;
		unsigned wrtord : 5;
		unsigned reserved1 : 3;
		unsigned rrd : 4;
		unsigned reserved2 : 4;
		unsigned faw : 6;
		unsigned reserved3 : 2;
	} b;
};

union noc_ddrtimingc0 {
	u32 d32;
	struct {
		unsigned burstpenalty : 4;
		unsigned reserved0 : 4;
		unsigned wrtomwr : 6;
		unsigned reserved1 : 18;
	} b;
};

union noc_ddrtimingl {
	u32 d32;
	struct {
		unsigned ccdl : 3;
		unsigned wrtordl : 5;
		unsigned rrdl : 4;
		unsigned reserved : 20;
	} b;
};

union noc_devtodev0 {
	u32 d32;
	struct {
		unsigned busrdtord : 3;
		unsigned reserved0 : 1;
		unsigned busrdtowr : 3;
		unsigned reserved1 : 1;
		unsigned buswrtord : 3;
		unsigned reserved2 : 1;
		unsigned buswrtowr : 3;
		unsigned reserved3 : 17;
	} b;
};

union noc_devtodev_rv1126 {
	u32 d32;
	struct {
		unsigned busrdtord : 3;
		unsigned reserved0 : 1;
		unsigned busrdtowr : 4;
		unsigned buswrtord : 4;
		unsigned buswrtowr : 3;
		unsigned reserved2 : 17;
	} b;
};

union noc_ddrmode {
	u32 d32;
	struct {
		unsigned autoprecharge : 1;
		unsigned bypassfiltering : 1;
		unsigned fawbank : 1;
		unsigned burstsize : 2;
		unsigned mwrsize : 2;
		unsigned reserved2 : 1;
		unsigned forceorder : 8;
		unsigned forceorderstate : 8;
		unsigned reserved3 : 8;
	} b;
};

union noc_ddr4timing {
	u32 d32;
	struct {
		unsigned ccdl : 3;
		unsigned wrtordl : 5;
		unsigned rrdl : 4;
		unsigned reserved1 : 20;
	} b;
};

#endif
