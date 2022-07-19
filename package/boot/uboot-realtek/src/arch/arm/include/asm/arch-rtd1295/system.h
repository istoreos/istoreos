/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the main directory of this archive
 * for more details.
 *
 * Copyright (C) 2012 by Chuck Chen <ycchen@realtek.com>
 *
 *      =========================================
 *        Date           Who                    Comment
 *      =========================================
 *      20150812        Tom Ting              Change for phoenix 1295
 *
 */

#ifndef _ASM_MACH_SYSTEM_H_
#define _ASM_MACH_SYSTEM_H_

//RTD1295 support 3 MISC timers,TC0/TC1 for SCPU NWC,TC2 for SCPU SWC.
#define SYSTEM_TIMER            CONFIG_SYS_TIMER

#if defined (CONFIG_BOARD_FPGA)
#define TIMER_CLOCK             33000000        //FPGA
#else
#define TIMER_CLOCK             27000000
#endif
#define MAX_HWTIMER_NUM         3

// Mips kseq base address
#define MIPS_KSEG0BASE		0x80000000
#define MIPS_KSEG1BASE		0xa0000000
#define MIPS_KSEG_MSK		0xe0000000


#define RBUS_ADDR		0x98000000	// Used for mmu_setup
#define RBUS_SIZE		0x00050000
#define RBUS_END		(RBUS_ADDR + RBUS_SIZE)

#define ARM_REDIRECT_CODE_ADDR					(0x00000000)
#define MIPS_EXC_REDIRECT_CODE_ADDR				(0x00000080)
#define MIPS_AUDIO_EXC_VECTOR_ADDR				(0x00000094)
#define MIPS_EXC_DISPATCH_CODE_ADDR				(0x00000100)
#define MIPS_ISR_VIDEO_IMG_ADDR					(0x00001500)
#define MIPS_ROS_BOOT_VECTOR_IMG_ADDR			(0x00001900)
#define MIPS_A_ENTRY_CODE_ADDR					(0x00002000)

#define MIPS_SHARED_MEMORY_ENTRY_ADDR			(0x1F000) // 128K - 0x1000
#define MIPS_UART_REG_BASE_ADDR					(MIPS_SHARED_MEMORY_ENTRY_ADDR+0x000000c4)
#define MIPS_ONE_STEP_INFO_ADDR					(MIPS_SHARED_MEMORY_ENTRY_ADDR+0x000000c8)
#define MIPS_BOOT_AV_INFO_PTR_ADDR				(MIPS_SHARED_MEMORY_ENTRY_ADDR+0x000000cc)
#define MIPS_AUDIO_FLAG_PTR_ADDR				(MIPS_SHARED_MEMORY_ENTRY_ADDR+0x000000d0)
	
	
#define MIPS_AUDIO_FW_ENTRY_PTR_ADDR			(MIPS_SHARED_MEMORY_ENTRY_ADDR+0x000000e0)
#define MIPS_SHARED_PRINTK_BUFFER_ADDR			(MIPS_SHARED_MEMORY_ENTRY_ADDR+0x000000e8)	// 0x0000b0e8~0x0000b0ff
#define MIPS_SHARED_PRINTK_BUFFER_SIZE			(0x18)
#define MIPS_BOOT_AV_INFO_ADDR					(MIPS_SHARED_MEMORY_ENTRY_ADDR+0x00000600)
#define VO_RESOLUTION 						(MIPS_SHARED_MEMORY_ENTRY_ADDR+0x00000800)	// VO_RESOLUTION_INFO
#define POWER_SAVING 						(MIPS_SHARED_MEMORY_ENTRY_ADDR+0x00000900)	// power saving config for fw.

#define BOOTCODE_TEXT_ADDR						(CONFIG_SYS_TEXT_BASE) 		//0x00020000
#define LINUX_KERNEL_ADDR						(0x00108000)
#define DVRBOOT_EXE_BIN_ENTRY_ADDR				(0x01500000)

#ifdef NAS_ENABLE
#define MIPS_AUDIO_FW_ENTRY_ADDR				(0x01b00000)  // for old position
#else
#define MIPS_AUDIO_FW_ENTRY_ADDR				(0x0f900000)
#endif


#define FIRMWARE_DESCRIPTION_TABLE_ADDR			(0x06400000)
#define FACTORY_DATA_ADDR						(0x07000000)	// 0x07000000~0x077fffff (8M)
#define FACTORY_RO_DATA_ADDR					(0x07800000)	// 0x07800000~0x07820000 (128K)
#define UBOOT_HEAP_RELOCATION_ADDR				(0x07880000)	// 0x07880000~0x078fffff (512K)
#define UBOOT_NONCACHE_MEMORY_ADDR				(0x07900000)	// 0x07900000~0x079fffff (1M)
#define UBOOT_SECURE_MCP_MEMORY_ADDR			(0x08000000)	// 0x08000000~0x09ffffff
#define UBOOT_SECURE_MCP_MEMORY_SIZE			(0x02000000)	// 32M
#define ENCRYPTED_FW_ADDR						(0x05000000)
#define ENCRYPTED_LINUX_KERNEL_ADDR				(0x0a000000)
#define COMPRESSED_FW_IMAGE_ADDR				(0x0b000000)
#define TEMP_BUFFER_FOR_FLASH_DATA_ADDR			(0x0c000000)
#define BACKUP_DESCRIPTION_RECOVERY_ADDR        (0x01500000)  //used DVRBOOT_EXE_BIN_ENTRY_ADDR

#define ACPU_JUMP_ADDR_reg          			(0x58007080) //work around for lx5280 rom.
#define REG_CRT_SUSPEND_reg						(WDOG_DATA1)	/* register which represent suspend to ram or disk */
#define REG_AC_DC_ON_reg						(WDOG_DATA12)	/* register which represent AC or DC on */

#endif  // _ASM_MACH_SYSTEM_H_
