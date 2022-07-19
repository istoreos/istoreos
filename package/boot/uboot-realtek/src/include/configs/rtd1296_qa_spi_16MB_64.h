/*
 * Configuration settings for the Realtek 1295 fpga board.
 *
 * Won't include this file.
 * Just type "make <board_name>_config" and will be included in source tree.
 */

#ifndef __CONFIG_RTK_RTD1296_QA_SPI_64_H
#define __CONFIG_RTK_RTD1296_QA_SPI_64_H

/*
 * Include the common settings of RTD1295 platform.
 */
#include <configs/rtd1295_common.h>
#include <configs/rtd1295_customized_feature.h>



//==========================================================
/* Flash type is SPI or NAND or eMMC*/
#define CONFIG_SYS_RTK_SPI_FLASH
//#define CONFIG_SYS_RTK_NAND_FLASH
//#define CONFIG_SYS_RTK_EMMC_FLASH



#if defined(CONFIG_SYS_RTK_SPI_FLASH)
	/* Flash writer setting:
	*   The corresponding setting will be located at
	*   uboot/examples/flash_writer_u/$(CONFIG_FLASH_WRITER_SETTING).inc*/	
	#define CONFIG_FLASH_WRITER_SETTING            "1296_force_spi_nS_nE"
	#define CONFIG_CHIP_ID            			   "rtd1295"
	#define CONFIG_CUSTOMER_ID            		   "demo"
	#define CONFIG_FLASH_TYPE					   "RTK_FLASH_SPI"	
	
	#if defined(CONFIG_TARGET_RTD1293)
		/*The specific chip type only for rtd1293*/
		#define CONFIG_CHIP_TYPE            		"1001"		
	#else
		#define CONFIG_CHIP_TYPE            		"0001"
	#endif

#ifdef CONFIG_NAS_ENABLE
	#define CONFIG_BOOT_FROM_SPI
	#define CONFIG_BFS_SUPPORT_KERNEL_ROOTFS       /* BootFromSpi */
	#define CONFIG_BFS_SUPPORT_LOGO_IMG            /* BootFromSpi */
	#define CONFIG_BFS_SUPPORT_BACKUP_SPI_IMG      /* BootFromSpi */
	#define CONFIG_DPTX_MODE               1
	#define CONFIG_DPTX_HPD_IGPIO_NUM      7
	#define CONFIG_DPTX_DEFAULT_RESOLUTION 0
#endif

	#ifdef CONFIG_BOOT_FROM_SPI
		#define CONFIG_FACTORY_BASE                0x00110000
		#define CONFIG_FACTORY_SIZE                0x00020000
	#else
		#define CONFIG_FACTORY_BASE                0x00010000
		#define CONFIG_FACTORY_SIZE                0x00010000
	#endif
	
	#define CONFIG_DTS_BASE                        0x000F0000
	#define CONFIG_DTS_SIZE                        0x00010000
	#define CONFIG_BOOTCODE2_BASE                  0x00080000
	#define CONFIG_AFW_ADDR                        0x000C0000
	#define CONFIG_AFW_SIZE                        0x00040000

	#define CONFIG_FW_TABLE_SIZE                   0x8000

	#define CONFIG_BACKUP_SPI_OFFSET               0x00768000

	#define CONFIG_RTKSPI
	#define CONFIG_CMD_RTKSPI
	
	//#define CONFIG_SYS_RTK_SATA_STORAGE
	//#define CONFIG_BOOT_FROM_SATA
	
	/* ENV */
	#undef CONFIG_ENV_SIZE
	#define CONFIG_ENV_SIZE (8192)

	#undef CONFIG_ENV_IS_NOWHERE
	#ifdef CONFIG_SYS_FACTORY
		#define CONFIG_ENV_IS_IN_FACTORY
		//#define CONFIG_SYS_FACTORY_READ_ONLY
	#endif
#endif

/* Boot Revision */
#define CONFIG_COMPANY_ID 		"0000"
#define CONFIG_BOARD_ID         "0705"
#define CONFIG_VERSION          "0000"
//==========================================================
/*
 * SDRAM Memory Map
 * Even though we use two CS all the memory
 * is mapped to one contiguous block
 */
#undef CONFIG_NR_DRAM_BANKS
#undef CONFIG_SYS_SDRAM_BASE
#undef CONFIG_SYS_RAM_DCU1_SIZE

#define ARM_ROMCODE_SIZE			(124*1024)
#define CONFIG_NR_DRAM_BANKS		1
#define CONFIG_SYS_SDRAM_BASE		0x0
#define CONFIG_SYS_RAM_DCU1_SIZE	0x40000000	// FIXME
#define CONFIG_FT_RESCUE

#undef  V_NS16550_CLK
#define V_NS16550_CLK			27000000	//FIXME


/* Bootcode Feature: Rescue linux read from USB */
#define CONFIG_RESCUE_FROM_USB
#ifdef CONFIG_RESCUE_FROM_USB
	#define CONFIG_RESCUE_FROM_USB_VMLINUX		"emmc.uImage"
	#define CONFIG_RESCUE_FROM_USB_DTB		"rescue.emmc.dtb"
	#define CONFIG_RESCUE_FROM_USB_ROOTFS		"rescue.root.emmc.cpio.gz_pad.img"
	#define CONFIG_RESCUE_FROM_USB_AUDIO_CORE	"bluecore.audio"
#endif /* CONFIG_RESCUE_FROM_USB */



#define COUNTER_FREQUENCY               27000000 // FIXME, need to know what impact it will cause

#define CONFIG_VERSION			"0000"

#undef CONFIG_SYS_TEXT_BASE
#define CONFIG_SYS_TEXT_BASE		0x00020000

#endif /* __CONFIG_RTK_RTD1296_QA_SPI_64_H */

