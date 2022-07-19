/*
 * Configuration settings for the Realtek 1295 fpga board.
 *
 * Won't include this file.
 * Just type "make <board_name>_config" and will be included in source tree.
 */

#ifndef __CONFIG_RTK_RTD1295_QA_SPI_64_H
#define __CONFIG_RTK_RTD1295_QA_SPI_64_H

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
	#define CONFIG_FLASH_WRITER_SETTING            "1295_force_spi_nS_nE"
	#define CONFIG_CHIP_ID            			   "rtd1295"
	#define CONFIG_CUSTOMER_ID            		   "demo"
	#define CONFIG_FLASH_TYPE					   "RTK_FLASH_SPI"	
	
	#if defined(CONFIG_TARGET_RTD1293)
		/*The specific chip type only for rtd1293*/
		#define CONFIG_CHIP_TYPE            		   "1001"		
	#else
		#define CONFIG_CHIP_TYPE            		   "0001"
	#endif

	#if defined(CONFIG_TARGET_RTD1296) && defined(CONFIG_NAS_ENABLE)
		#define CONFIG_DPTX_MODE               1
		#define CONFIG_DPTX_HPD_IGPIO_NUM      7
		#define CONFIG_DPTX_DEFAULT_RESOLUTION 2
	#endif

#ifdef CONFIG_NAS_ENABLE
#ifndef CONFIG_BOOT_FROM_SPI
	#define CONFIG_SPI_MTD_STATIC
#endif
#endif
	#ifdef CONFIG_SPI_MTD_STATIC
#ifndef CONFIG_UBOOT_SIZE
	#define CONFIG_UBOOT_SIZE                      0x80000
#endif
#ifndef CONFIG_FWIMG_ADDR
	#define CONFIG_FWIMG_ADDR                      0xa0000
#endif
#ifndef CONFIG_FWIMG_SIZE
	#define CONFIG_FWIMG_SIZE                      0x760000
#endif

	#define CONFIG_LOGO_ADDR                       CONFIG_FWIMG_ADDR
#ifndef CONFIG_LOGO_SIZE
	#define CONFIG_LOGO_SIZE                       0x00050000
#endif
	#define CONFIG_AFW_ADDR                        CONFIG_LOGO_ADDR+CONFIG_LOGO_SIZE
#ifndef CONFIG_AFW_SIZE
	#define CONFIG_AFW_SIZE                        0x00160000
#endif
	#define CONFIG_DTS_BASE                        CONFIG_AFW_ADDR+CONFIG_AFW_SIZE
#ifndef CONFIG_DTS_SIZE
	#define CONFIG_DTS_SIZE                        0x00010000
#endif
	#define CONFIG_KERNEL_ADDR                     CONFIG_DTS_BASE+CONFIG_DTS_SIZE
#ifndef CONFIG_KERNEL_SIZE
	#define CONFIG_KERNEL_SIZE                     0x00370000
#endif
	#define CONFIG_ROOTFS_ADDR                     CONFIG_KERNEL_ADDR+CONFIG_KERNEL_SIZE
#ifndef CONFIG_ROOTFS_SIZE
	#define CONFIG_ROOTFS_SIZE                     0x00230000
#endif
	#define CONFIG_INITRD_SIZE                     0x00400000

#define ENV_NAME_SETTINGS \
	"fwimgname=openwrt-rtd1295-nas_spi-rtk-spi-8M-initrd-sysupgrade.bin\0" \
	"bootcodeimgname=openwrt-rtd1295-bootcode.bin\0"
#define ENV_LAYOUT_SETTINGS \
	"fwimgaddr="STR(CONFIG_FWIMG_ADDR)"\0" \
	"fwimgsize="STR(CONFIG_FWIMG_SIZE)"\0" \
	"loadaddr=0x01500000\0" \
	"bootcodeimgaddr=0x20000\0" \
	"bootcodeimgsize="STR(CONFIG_UBOOT_SIZE)"\0"
#define ENV_UPGRADE_CMDS \
	"upgrade_img_tftp=tftp ${loadaddr} ${fwimgname} && setenv upfwtftp 1; if test -n ${upfwtftp}; then rtkspi erase ${fwimgaddr} ${fwimgsize};rtkspi write ${fwimgaddr} ${loadaddr} ${fwimgsize}; fi;\0" \
	"upgrade_img_usb=usb start;fatload usb 0:1 ${loadaddr} ${fwimgname} && setenv upfwusb 1; if test -n ${upfwusb}; then rtkspi erase ${fwimgaddr} ${fwimgsize};rtkspi write ${fwimgaddr} ${loadaddr} ${fwimgsize}; fi;\0" \
	"upgrade_bootcode_tftp=tftp ${loadaddr} ${bootcodeimgname} && setenv upfwtftp 1; if test -n ${upfwtftp}; then rtkspi erase ${bootcodeimgaddr} ${bootcodeimgsize};rtkspi write ${bootcodeimgaddr} ${loadaddr} ${bootcodeimgsize}; reset; fi;\0" \
	"upgrade_bootcode_usb=usb start;fatload usb 0:1 ${loadaddr} ${bootcodeimgname} && setenv upfwusb 1; if test -n ${upfwusb}; then rtkspi erase ${bootcodeimgaddr} ${bootcodeimgsize};rtkspi write ${bootcodeimgaddr} ${loadaddr} ${bootcodeimgsize}; reset; fi;\0"


	#undef CONFIG_EXTRA_ENV_SETTINGS
#define CONFIG_EXTRA_ENV_SETTINGS                   \
	ENV_NAME_SETTINGS \
	ENV_LAYOUT_SETTINGS \
	ENV_UPGRADE_CMDS \
   "kernel_loadaddr=0x03000000\0"                  \
   "fdt_loadaddr=0x02100000\0"                  \
   "fdt_high=0xffffffffffffffff\0"                  \
   "rootfs_loadaddr=0x02200000\0"                   \
   "rescue_rootfs_loadaddr=0x02200000\0"                   \
   "audio_loadaddr="STR(CONFIG_FW_LOADADDR)"\0"                 \
   "mtd_part=mtdparts=rtk_nand:\0"                  \

	#endif //CONFIG_SPI_MTD_STATIC

	#ifdef CONFIG_BOOT_FROM_SPI
	#define CONFIG_FACTORY_BASE                    0x00110000
	#define CONFIG_FACTORY_SIZE                    0x00020000
	#else
	#define CONFIG_FACTORY_BASE                    0x00010000
	#define CONFIG_FACTORY_SIZE                    0x00010000
	#endif
	
	#ifndef CONFIG_SPI_MTD_STATIC
	#define CONFIG_DTS_BASE                        0x000F0000
	#define CONFIG_DTS_SIZE                        0x00010000
	#define CONFIG_BOOTCODE2_BASE                  0x00080000
	#define CONFIG_AFW_ADDR                        0x000C0000
	#define CONFIG_AFW_SIZE                        0x00040000
	#define CONFIG_FW_TABLE_SIZE                   0x8000
	#endif

	#define CONFIG_RTKSPI
	#define CONFIG_CMD_RTKSPI
	
	//#define CONFIG_SYS_RTK_SATA_STORAGE
	//#define CONFIG_BOOT_FROM_SATA
	

	#undef CONFIG_ENV_IS_NOWHERE
	#ifdef CONFIG_SYS_FACTORY
		#ifndef CONFIG_SPI_MTD_STATIC
		#define CONFIG_ENV_IS_IN_FACTORY
		#endif
		//#define CONFIG_SYS_FACTORY_READ_ONLY
	#endif

	/* ENV */
	#undef CONFIG_ENV_SIZE
	#ifdef CONFIG_ENV_IS_IN_FACTORY
	#define CONFIG_ENV_SIZE (8192)
	#else
	#define CONFIG_ENV_IS_IN_SPI
	#undef CONFIG_ENV_ADDR
	#define CONFIG_SYS_FLASH_BASE                  SPI_RBUS_BASE_ADDR
	#define CONFIG_ENV_OFFSET                      0x00000
	#define CONFIG_ENV_ADDR                        (CONFIG_SYS_FLASH_BASE + CONFIG_ENV_OFFSET)
	#define CONFIG_ENV_SIZE                        0x10000
//	#define CONFIG_ENV_SECT_SIZE                   0x10000
	#define ENV_IS_EMBEDDED
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


#ifdef CONFIG_BOOT_FROM_SPI
/* Bootcode Feature: Rescue linux read from USB */
#define CONFIG_RESCUE_FROM_USB
#ifdef CONFIG_RESCUE_FROM_USB
	#define CONFIG_RESCUE_FROM_USB_VMLINUX		"spi.uImage"
	#define CONFIG_RESCUE_FROM_USB_DTB		"rescue.spi.dtb"
	#define CONFIG_RESCUE_FROM_USB_ROOTFS		"rescue.root.spi.cpio.gz_pad.img"
	#define CONFIG_RESCUE_FROM_USB_AUDIO_CORE	"bluecore.audio"
#endif /* CONFIG_RESCUE_FROM_USB */
#endif


#define COUNTER_FREQUENCY               27000000 // FIXME, need to know what impact it will cause

#define CONFIG_VERSION			"0000"

#undef CONFIG_SYS_TEXT_BASE
#define CONFIG_SYS_TEXT_BASE		0x00020000

#endif /* __CONFIG_RTK_RTD1295_QA_SPI_64_H */

