// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (c) 2020 Rockchip Electronics Co., Ltd
 */

#include <common.h>
#include <dm.h>
#include <ram.h>
#include <asm/io.h>
#include <asm/arch-rockchip/param.h>
#include <asm/arch-rockchip/rk_atags.h>

DECLARE_GLOBAL_DATA_PTR;

static void fpga_init_atags(void)
{
#ifdef CONFIG_FPGA_RAM
	struct tag_ram_partition t_ram_part;
#endif
	struct tag_bootdev t_bootdev;
	struct tag_ddr_mem t_ddrmem;
	struct tag_serial t_serial;
	struct tag_tos_mem t_tos;
#if defined(CONFIG_ARM64) || defined(CONFIG_ARM64_BOOT_AARCH32)
	struct tag_atf_mem t_atf;
#endif
	/* destroy ! */
	atags_destroy();

	/* serial */
	memset(&t_serial, 0, sizeof(t_serial));
	t_serial.version = 0;
	t_serial.enable = 1;
	t_serial.addr = CONFIG_DEBUG_UART_BASE;
	t_serial.baudrate = CONFIG_BAUDRATE;
	t_serial.m_mode = 0;
	t_serial.id = 2;
	atags_set_tag(ATAG_SERIAL, &t_serial);

	/* ddr memory */
	memset(&t_ddrmem, 0, sizeof(t_ddrmem));
	t_ddrmem.version = 0;
	t_ddrmem.count = 1;
	t_ddrmem.bank[0] = CONFIG_SYS_SDRAM_BASE;
	t_ddrmem.bank[1] = SZ_1G;
	atags_set_tag(ATAG_DDR_MEM, &t_ddrmem);

	/* bootdev */
	memset(&t_bootdev, 0, sizeof(t_bootdev));
	t_bootdev.version = 0;
#ifdef CONFIG_FPGA_RAM
	t_bootdev.devtype = BOOT_TYPE_RAM;
#else
	t_bootdev.devtype = BOOT_TYPE_EMMC;
#endif
	t_bootdev.devnum = 0;
	t_bootdev.sdupdate = 0;
	atags_set_tag(ATAG_BOOTDEV, &t_bootdev);

	/* atf */
#if defined(CONFIG_ARM64) || defined(CONFIG_ARM64_BOOT_AARCH32)
	memset(&t_atf, 0, sizeof(t_atf));
	t_atf.version = 0;
	t_atf.phy_addr = CONFIG_SYS_SDRAM_BASE;
	t_atf.size = SZ_1M;
	t_atf.flags = 0;
	atags_set_tag(ATAG_ATF_MEM, &t_atf);
#endif

	/* op-tee */
	memset(&t_tos, 0, sizeof(t_tos));
	t_tos.version = 0;
	strcpy(t_tos.tee_mem.name, "op-tee");
#ifdef CONFIG_ARM64
	t_tos.tee_mem.phy_addr = SZ_2M;
	t_tos.tee_mem.size = SZ_4M;
#else
	t_tos.tee_mem.phy_addr = 0x8400000; /* 132M offset */
	t_tos.tee_mem.size = 0x1e00000;     /* 30M size */
#endif
	t_tos.tee_mem.flags = 1;
	atags_set_tag(ATAG_TOS_MEM, &t_tos);

#ifdef CONFIG_FPGA_RAM
	/* ram part */
	memset(&t_ram_part, 0, sizeof(t_ram_part));
	t_ram_part.version = 0;
	t_ram_part.count = 1;
	strcpy(t_ram_part.part[0].name, "boot");
	t_ram_part.part[0].start = 0x4000000;	/* 64M offset */
	t_ram_part.part[0].size  = 0x2000000;	/* 32M size */
	atags_set_tag(ATAG_RAM_PARTITION, &t_ram_part);
#endif
}

int arch_fpga_init(void)
{
	fpga_init_atags();

	return 0;
}
