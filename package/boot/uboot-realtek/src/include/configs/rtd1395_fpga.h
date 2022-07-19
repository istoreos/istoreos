/*
 * Configuration settings for the Realtek 1395 fpga board.
 *
 * Won't include this file.
 * Just type "make <board_name>_config" and will be included in source tree.
 */

#ifndef __CONFIG_RTK_RTD1395_FPGA_H
#define __CONFIG_RTK_RTD1395_FPGA_H

/*
 * Include the common settings of RTD1395 platform.
 */
#include <configs/rtd1395_common.h>

//==========================================================
/* Flash type is SPI or NAND or eMMC*/
#define CONFIG_SYS_RTK_EMMC_FLASH

#if defined(CONFIG_SYS_RTK_EMMC_FLASH)
	/* Flash writer setting:
	*   The corresponding setting will be located at
	*   uboot/examples/flash_writer_u/$(CONFIG_FLASH_WRITER_SETTING).inc*/
	#define CONFIG_FLASH_WRITER_SETTING            "1395_force_emmc"
	#define CONFIG_CHIP_ID            			   "rtd1395"
	#define CONFIG_CUSTOMER_ID            		   "demo" 
	#define CONFIG_CHIP_TYPE            		   "0000"

	
	/* Factory start address and size in eMMC */
	#define CONFIG_FACTORY_START	0x220000	/* For eMMC */
	#define CONFIG_FACTORY_SIZE	0x400000	/* For eMMC */
	#define CONFIG_FW_TABLE_SIZE    0x8000		/* For eMMC */
	
	#ifndef CONFIG_SYS_PANEL_PARAMETER
		#define CONFIG_SYS_PANEL_PARAMETER
	#endif
	
	/* MMC */
	#define CONFIG_MMC
	#ifndef CONFIG_PARTITIONS
		#define CONFIG_PARTITIONS
	#endif
	#define CONFIG_DOS_PARTITION
	#define CONFIG_GENERIC_MMC
	#define CONFIG_RTK_MMC
	#define CONFIG_CMD_MMC
	#define USE_SIMPLIFY_READ_WRITE
	#define CONFIG_SHA256
	
	/* ENV */
	#undef	CONFIG_ENV_IS_NOWHERE
	#ifdef CONFIG_SYS_FACTORY
		#define CONFIG_ENV_IS_IN_FACTORY
		//#define CONFIG_SYS_FACTORY_READ_ONLY
	#endif
	
	
	#ifdef CONFIG_RESCUE_FROM_USB
		#undef CONFIG_RESCUE_FROM_USB_VMLINUX
		#undef CONFIG_RESCUE_FROM_USB_DTB
		#undef CONFIG_RESCUE_FROM_USB_ROOTFS
		#define CONFIG_RESCUE_FROM_USB_VMLINUX			"emmc.uImage"
		#define CONFIG_RESCUE_FROM_USB_DTB				"rescue.emmc.dtb"
		#define CONFIG_RESCUE_FROM_USB_ROOTFS			"rescue.root.emmc.cpio.gz_pad.img"
	#endif /* CONFIG_RESCUE_FROM_USB */
#endif


/*
 * SDRAM Memory Map
 * Even though we use two CS all the memory
 * is mapped to one contiguous block
 */
#undef CONFIG_NR_DRAM_BANKS
#undef CONFIG_SYS_SDRAM_BASE
#undef CONFIG_SYS_RAM_DCU1_SIZE

#define ARM_ROMCODE_SIZE			(188*1024)
#define CONFIG_NR_DRAM_BANKS		1
#define CONFIG_SYS_SDRAM_BASE		0x0
#define CONFIG_SYS_RAM_DCU1_SIZE	0x20000000
//#define CONFIG_FT_RESCUE

#undef  V_NS16550_CLK
#define V_NS16550_CLK			33000000

#define COUNTER_FREQUENCY               33000000 // FIXME, need to know what impact it will cause

#define CONFIG_VERSION			"0000"

// Non-Cache area setting
#undef CONFIG_SYS_NONCACHED_START
#undef CONFIG_SYS_NONCACHED_SIZE
#define CONFIG_SYS_NONCACHED_START	0x18000000
#define CONFIG_SYS_NONCACHED_SIZE	0x08000000

//#undef CONFIG_SYS_FACTORY

#endif /* __CONFIG_RTK_RTD1395_FPGA_H */

