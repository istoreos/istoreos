/*
 * Configuration settings for the Realtek 1295 fpga board.
 *
 * Won't include this file.
 * Just type "make <board_name>_config" and will be included in source tree.
 */

#ifndef __CONFIG_RTK_RTD1295_QA_SPI_MONARCH_H
#define __CONFIG_RTK_RTD1295_QA_SPI_MONARCH_H

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
	#define CONFIG_FLASH_WRITER_SETTING				"1295_force_spi_nS_nE_monarch"
	#define CONFIG_CHIP_ID							"rtd1295"
	#define CONFIG_CUSTOMER_ID						"demo"
	#define CONFIG_FLASH_TYPE						"RTK_FLASH_SPI"

	#if defined(CONFIG_TARGET_RTD1293)
		/*The specific chip type only for rtd1293*/
		#define CONFIG_CHIP_TYPE					"1001"
	#else
		#define CONFIG_CHIP_TYPE					"0001"
	#endif

	#define CONFIG_FACTORY_BASE						0x00010000
	#define CONFIG_FACTORY_SIZE						0x00010000

	#define CONFIG_DTS_BASE							0x000F0000
	#define CONFIG_DTS_SIZE							0x00010000
	#define CONFIG_AFW_ADDR							0x000C0000
	#define CONFIG_AFW_SIZE							0x00040000

	#define CONFIG_FW_TABLE_SIZE					0x8000

	#define CONFIG_RTKSPI
	#define CONFIG_CMD_RTKSPI

	#define CONFIG_BOARD_WD_MONARCH
	#define CONFIG_ANDORIDBOOT_HARDWARE_NAME        "monarch"

	#define CONFIG_SYS_RTK_SATA_STORAGE
	#define CONFIG_BOOT_FROM_SATA
	#define CONFIG_CMD_GPT
	#define CONFIG_CMD_RTKGPT

	#define CONFIG_CMD_NET_LED_FOR_WD
	#define CONFIG_WAIT_AFW_1_SECOND

	#define CONFIG_CMD_RTKFDT

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

#define CONFIG_BOOT_FOR_WD  /* use cmd_boot_wd.c istead of cmd_boot.c */
#define CONFIG_CMD_WDPP
#define CONFIG_WD_AB
#define CURRENT_GPT_VER 3

#define CONFIG_RESCUE_FROM_DHCP
#ifdef CONFIG_RESCUE_FROM_DHCP
	#define CONFIG_CMD_DHCP
	//#define CONFIG_BOOTP_SERVERIP		"192.168.2.134"	/* development */
	#define CONFIG_BOOTP_SERVERIP		"192.168.137.2"	/* factory release */
#endif

/* Bootcode Feature: Rescue linux read from USB */
#define CONFIG_RESCUE_FROM_USB
#ifdef CONFIG_RESCUE_FROM_USB
	#define CONFIG_RESCUE_FROM_USB_VMLINUX		"sata.uImage"
	#define CONFIG_RESCUE_FROM_USB_DTB			"rescue.sata.dtb"
	#define CONFIG_RESCUE_FROM_USB_ROOTFS		"rescue.root.sata.cpio.gz_pad.img"
	#define CONFIG_RESCUE_FROM_USB_AUDIO_CORE	"bluecore.audio"
#endif /* CONFIG_RESCUE_FROM_USB */

#define CONFIG_CMD_SATA
#ifdef CONFIG_CMD_SATA
	#define CONFIG_RTK_AHSATA
	#define CONFIG_SYS_SATA_MAX_DEVICE      1
	#define CONFIG_DWC_AHSATA_PORT_ID       0
	#define CONFIG_DWC_AHSATA_BASE_ADDR     0x9803F000
	#define CONFIG_LBA48
	#define CONFIG_LIBATA
	#define CONFIG_PORT0_POWER_PIN			18
#endif

#define COUNTER_FREQUENCY               27000000 // FIXME, need to know what impact it will cause

#define CONFIG_CMD_RTKRNG

#define CONFIG_VERSION			"0000"

#undef CONFIG_SYS_TEXT_BASE
#define CONFIG_SYS_TEXT_BASE		0x00020000

/* PWM command interface */
//#define CONFIG_CMD_RTKPWM
/* PWM hardware driver */
#define CONFIG_RTD129X_PWM
#ifdef CONFIG_RTD129X_PWM
    //#define PWM_0_PIN_0
    //#define PWM_0_PIN_1
    //#define PWM_1_PIN_0
    //#define PWM_1_PIN_1
    //#define PWM_2_PIN_0
    //#define PWM_2_PIN_1
    #define PWM_3_PIN_0
    //#define PWM_3_PIN_1
#endif /* CONFIG_RTD129X_PWM */

/* GPIO */
#define HDD0_POWER_GPIO 18
#define FACTORY_RST_BTN 34		// igpio34 is the factory reset button for Monarch
#define SYS_LED_PWM_PORT_NUM 3  // system LED PWM Port Number is PWM3_0 for Monarch

#endif /* __CONFIG_RTK_RTD1295_QA_SPI_MONARCH_H */

