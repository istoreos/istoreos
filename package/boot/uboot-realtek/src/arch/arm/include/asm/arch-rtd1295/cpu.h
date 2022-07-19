/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the main directory of this archive
 * for more details.
 *
 * Copyright (C) 2015 by Tom Ting <tom_ting@realtek.com>
 *
 * Time initialization.
 */
#ifndef __RTK_CPU_H__
#define __RTK_CPU_H__


#define CPU_RELEASE_ADDR	0x9801aa44
#define SB2_CHIP_INFO       0x9801a204
#define BL31_ENTRY_ADDR		0x10120000
#define TEE_MEM_START_ADDR	0x10100000ULL
#define TEE_MEM_SIZE		0x00F00000ULL
#define BOOT_LOGO_ADDR		0x30000000ULL
#define BOOT_LOGO_SIZE		0x00900000ULL
#define VO_SECURE_ADDR		BOOT_LOGO_ADDR + BOOT_LOGO_SIZE - 0x100000
#define VO_SECURE_SIZE		0x00005a00ULL


#ifdef NAS_ENABLE
#define AFW_MEM_START_ADDR	0x01B00000ULL
#else
#define AFW_MEM_START_ADDR	0x0F900000ULL
#endif

#define AFW_MEM_SIZE		0x500000ULL
#define UBOOT_MEM_START_ADDR	0x20000ULL
#define UBOOT_MEM_SIZE			0xE0000ULL

#define SOC_REV_A 		(0x0)
#define SOC_REV_B 		(0x1)
#define SOC_REV_C 		(0x2)


#define RTD129x_CHIP_REVISION_A00 0x00000000
#define RTD129x_CHIP_REVISION_A01 0x00010000
#define RTD129x_CHIP_REVISION_B00 0x00020000
#define RTD129x_CHIP_REVISION_B01 0x00030000

#define RTK1295_CPU_ID  	0x00000000
#define RTK1294_CPU_ID  	0x00000001
#define RTK1296_CPU_ID  	0x00000002
#define RTK1198_CPU_ID      0x00000003
#define RTK129x_CPU_MASK 	0x00000003
#define RTK1296_CPU_MASK 	0x00000800
#define RTK1198_CPU_MASK    0x000003FF
#define RTK1198_CPU_VAL     0x201
#define EFUSE_ADDR		(0x980171d8)
#define CHIP_INFO1 		(0x98007028)

#ifndef __ASSEMBLY__

#include <asm/io.h>

static inline int get_cpu_id(void) {
	int cpu_id = RTK1295_CPU_ID;
	
	if ((__raw_readl((volatile u32*)(EFUSE_ADDR)) & RTK129x_CPU_MASK) == RTK1294_CPU_ID) {
		cpu_id = RTK1294_CPU_ID;
	} else if ((__raw_readl((volatile u32*)(CHIP_INFO1)) & RTK1296_CPU_MASK)) {
		cpu_id = RTK1296_CPU_ID;
	} else if ((__raw_readl((volatile u32*)(CHIP_INFO1)) & RTK1198_CPU_MASK) == RTK1198_CPU_VAL) {
		cpu_id = RTK1198_CPU_ID;
	}
	
	return cpu_id;
}

void bootup_slave_cpu(void);
static inline u32 get_rtd129x_cpu_revision(void) {
	u32 val = __raw_readl(SB2_CHIP_INFO);
	return val; 
}

#endif


#endif
