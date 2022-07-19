/*
 * Realtek 1395 common configuration settings
 *
 */

#ifndef __CONFIG_RTK_RTD1395_COMMON_H
#define __CONFIG_RTK_RTD1395_COMMON_H

/* Macros to convert string from number */
#ifndef __STR
#define __STR(x) #x
#endif
#ifndef STR
#define STR(x) __STR(x)
#endif

#define CONFIG_UBOOT_DEFAULT

/* Display CPU and Board Info */
#define CONFIG_DISPLAY_CPUINFO		1
#define CONFIG_DISPLAY_BOARDINFO	1

#define CONFIG_SKIP_LOWLEVEL_INIT	1

#undef CONFIG_USE_IRQ				/* no support for IRQs */

#define CONFIG_CMDLINE_TAG		1	/* enable passing of ATAGs */
#define CONFIG_SETUP_MEMORY_TAGS	1
#define CONFIG_REVISION_TAG		1

/*
 * Realtek IC type
 */
#define CONFIG_RTD1395     1

/*
 * NAS
 */
#ifdef CONFIG_NAS_ENABLE
#define NAS_ENABLE			1	/* Enable NAS features */
//#define NAS_DUAL			1	/* Enable NAS dual boot on eMMC */
#endif

/*
 * Size of malloc() pool
 * Total Size Environment - 128k
 * Malloc - add 256k
 */
#define CONFIG_ENV_SIZE			(128 << 10)
#define CONFIG_ENV_IS_IN_REMOTE
#define CONFIG_ENV_ADDR			0x10000000
#define CONFIG_SYS_MALLOC_LEN		(CONFIG_ENV_SIZE + (256 << 10))

/*
 * Hardware drivers
 */

/*
 * serial port - NS16550 compatible
 */
#define V_NS16550_CLK				27000000

#define CONFIG_SYS_NS16550
#define CONFIG_SYS_NS16550_SERIAL
#define CONFIG_SYS_NS16550_REG_SIZE	(-4)
#define CONFIG_SYS_NS16550_CLK		V_NS16550_CLK
#define CONFIG_SYS_NS16550_UART1_CLK    432000000 

#define UART1_BASE					0x9801B200
#define UART0_BASE					0x98007800
#define CONFIG_CONS_INDEX			1
#define CONFIG_SYS_NS16550_COM1     UART0_BASE

#define CONFIG_BAUDRATE				115200
#define CONFIG_SYS_BAUDRATE_TABLE	{4800, 9600, 19200, 38400, 57600, 115200}

#define CONFIG_SYS_CONSOLE_IS_IN_ENV	1

#define UART0   0
#define UART1   1
#define UART2   2
#define UART3   3

/* Flash */
#define CONFIG_SYS_NO_FLASH	1

/*
 * Environment setup
 */

#define CONFIG_BOOTDELAY	0

#define CONFIG_ENV_OVERWRITE
	
#define CONFIG_BOOTCOMMAND \
	"bootr"

#define CONFIG_KERNEL_LOADADDR	0x03000000
#define CONFIG_ROOTFS_LOADADDR	0x02200000
#define CONFIG_RESCUE_ROOTFS_LOADADDR 	0x02200000
#define CONFIG_LOGO_LOADADDR	0x02002000      //reserved ~2M
#define CONFIG_FDT_LOADADDR	0x02100000      //reserved 64K
#define CONFIG_FW_LOADADDR	0x0f900000  //reserved 4M
#define CONFIG_BLUE_LOGO_LOADADDR 0x30000000

#define CONFIG_EXTRA_ENV_SETTINGS                   \
   "kernel_loadaddr=0x03000000\0"                  \
   "fdt_loadaddr=0x02100000\0"                  \
   "fdt_high=0xffffffffffffffff\0"                  \
   "rootfs_loadaddr=0x02200000\0"                   \
   "rescue_rootfs_loadaddr=0x02200000\0"                   \
   "audio_loadaddr=0x0f900000\0"                 \
   "mtd_part=mtdparts=rtk_nand:\0"                  \
   "blue_logo_loadaddr="STR(CONFIG_BLUE_LOGO_LOADADDR)"\0"      \
   "eth_drv_para=fephy,bypass,noacp\0"                  \

/* Pass open firmware flat tree */
#define CONFIG_CMD_BOOTI
#define CONFIG_GZIP_DECOMPRESS_KERNEL_ADDR	0x0c000000	// GZIPED kernel decompress addr
#define CONFIG_GZIP_KERNEL_MAX_LEN		0x01400000	// Set MAX size to 20M after decompressed
//#define CONFIG_ARMV8_SWITCH_TO_EL1
#define CONFIG_OF_LIBFDT    		1
#define CONFIG_OF_STDOUT_VIA_ALIAS	1

/* Console */
#define CONFIG_CMDLINE_EDITING
#define CONFIG_AUTO_COMPLETE

// 1:cache disable   0:enable
#if 0 
	#define CONFIG_SYS_ICACHE_OFF
	#define CONFIG_SYS_DCACHE_OFF
#else
	#define CONFIG_NONCACHE_ALLOCATION
	#define CONFIG_CMD_CACHE
#endif


/*
 * Miscellaneous configurable options
 */

#define CONFIG_SYS_LONGHELP		/* undef to save memory */
#define CONFIG_SYS_HUSH_PARSER	/* use "hush" command parser */
#define CONFIG_SYS_CBSIZE		640

/* Print Buffer Size */
#define CONFIG_SYS_PBSIZE		(CONFIG_SYS_CBSIZE + sizeof(CONFIG_SYS_PROMPT) + 16)
#define CONFIG_SYS_MAXARGS		16

/* Boot Argument Buffer Size */
#define CONFIG_SYS_BARGSIZE		(CONFIG_SYS_CBSIZE)

/*
 * memtest setup
 */
#define CONFIG_SYS_MEMTEST_START	0x00000000
#define CONFIG_SYS_MEMTEST_END		(CONFIG_SYS_MEMTEST_START + (32 << 20))

/* Default load address */
#define CONFIG_SYS_LOAD_ADDR		0x03000000

/* Use General purpose timer 2 */
#define CONFIG_SYS_TIMER		0     //FPGA
#define CONFIG_SYS_HZ			1000

/*
 * Stack sizes
 *
 * The stack sizes are set up in start.S using the settings below
 */
//stack size is setup in linker script 1MB
#ifdef CONFIG_USE_IRQ
	#define CONFIG_STACKSIZE_IRQ	(4 << 10)	/* IRQ stack */
	#define CONFIG_STACKSIZE_FIQ	(4 << 10)	/* FIQ stack */
#endif

/*
 * SDRAM Memory Map
 * Even though we use two CS all the memory
 * is mapped to one contiguous block
 */
#define CONFIG_NR_DRAM_BANKS		1
#define CONFIG_SYS_SDRAM_BASE		0x00000000
#define CONFIG_SYS_RAM_DCU1_SIZE	0x20000000		//512MB

/* GIC-400 setting */
#define CONFIG_GICV2
#define GICD_BASE			0xff011000      // FIXME, all these register should be reviewed
#define GICC_BASE			0xff012000      // FIXME, all these register should be reviewed



//if the relocation is enabled, the address is used to be the stack at very beginning.
#define CONFIG_SYS_INIT_SP_ADDR     0x00100000


// 1:cache disable   0:enable
#if 0
	#define CONFIG_SYS_ICACHE_OFF
	#define CONFIG_SYS_DCACHE_OFF
#else
	#define CONFIG_SYS_NONCACHED_MEMORY
	#define CONFIG_SYS_NONCACHED_START	0x20000000
	#define CONFIG_SYS_NONCACHED_SIZE	0x20000000
	#define CONFIG_CMD_CACHE
#endif

#define CONFIG_SYS_CACHELINE_SIZE	64

/*
 * rm include/autoconf.mk ---- prevent use old CONFIG_SYS_TEXT_BASE
 * make CONFIG_SYS_TEXT_BASE
 */
#ifndef CONFIG_SYS_TEXT_BASE
	#define CONFIG_SYS_TEXT_BASE		0x00030000
#endif

#define CONFIG_SYS_PROMPT       		"Realtek> "

/* Library support */
#define CONFIG_LZMA
#define CONFIG_LZO

#ifdef CONFIG_CMD_NET
	/* Eth Net */
	#define CONFIG_CMD_PING
	//#define CONFIG_CMD_TFTPPUT
	#define CONFIG_RTL8168
	#define CONFIG_TFTP_BLOCKSIZE		400

	/* Network setting */
	#define CONFIG_ETHADDR				00:10:20:30:40:50
	#define CONFIG_IPADDR				192.168.100.1
	#define CONFIG_GATEWAYIP			192.168.100.254
	#define CONFIG_SERVERIP				192.168.100.2
	#define CONFIG_NETMASK				255.255.255.0
#endif

/* USB Setting */
#define CONFIG_CMD_FAT
#define CONFIG_FAT_WRITE
#define CONFIG_CMD_RTKMKFAT
//#define CONFIG_PARTITIONS
#define CONFIG_DOS_PARTITION
#define CONFIG_EFI_PARTITION
#define CONFIG_SYS_USB_XHCI_MAX_ROOT_PORTS 5
//#define CONFIG_DM_USB

/*Total USB quantity*/
#define CONFIG_USB_MAX_CONTROLLER_COUNT 4

// for none define GPIO
/* define 1395 USB GPIO control */
/* Port 0, DRD, TYPE_C */
#define USB_PORT0_GPIO_TYPE "ISOGPIO"
#define USB_PORT0_GPIO_NUM 48
#define USB_PORT0_TYPE_C_SWITCH_GPIO_TYPE "ISOGPIO"
#define USB_PORT0_TYPE_C_SWITCH_GPIO_NUM 11
/* Port 1, xhci u2 host */
#define USB_PORT1_GPIO_TYPE "NONE"
#define USB_PORT1_GPIO_NUM  0
/* Port 2, xhci u2 host */
#define USB_PORT2_GPIO_TYPE "ISOGPIO"
#define USB_PORT2_GPIO_NUM  49

/* Fastboot */
#define CONFIG_G_DNL_VENDOR_NUM      0x18d1
#define CONFIG_G_DNL_PRODUCT_NUM   0x4e40
#define CONFIG_G_DNL_MANUFACTURER   "Realtek"

//#define CONFIG_ANDROID_BOOT_IMAGE
#define CONFIG_FASTBOOT_FLASH
#define CONFIG_USB_FASTBOOT_BUF_ADDR   0x28000000//CONFIG_SYS_LOAD_ADDR
#define CONFIG_USB_FASTBOOT_BUF_SIZE   0x6400000 //100MB
#define FASTBOOT_FW_IMG_UPDATE_ADDR    0x30000000
#define FASTBOOT_FW_IMG_UPDATE_MAX_SIZE 0x6400000 //100MB
#define FASTBOOT_SPARSE_IMAGE_ADDR     0x36400000
#define FASTBOOT_SPARSE_IMAGE_MAX_SIZE  0x6400000 //100MB
#define FASTBOOT_TAR_BUFFER_ADDR       0x3C800000
#define FASTBOOT_TAR_BUFFER_SIZE         0x400000 //4MB

/* Factory */
#define CONFIG_SYS_FACTORY
#define PANEL_CONFIG_FROM_FACTORY_PANEL_BIN

/* GPIO */
//#define CONFIG_REALTEK_GPIO
//#define CONFIG_INSTALL_GPIO_NUM    		8
#define CONFIG_HDMITx_HPD_IGPIO_NUM		7

/* I2C */
#define CONFIG_I2C_MULTI_BUS
#define CONFIG_REALTEK_I2C
#define CONFIG_SYS_I2C_SPEED		100

/* Auto detect sink*/
#define CONFIG_SYS_AUTO_DETECT
#define CONFIG_HDMITX_MODE				 1 // 0:Always OFF, 1: Always ON, 2: Auto
#define CONFIG_DEFAULT_TV_SYSTEM    	25 //1080P_60

/* If partition table */
#ifndef CONFIG_PARTITIONS
	#define CONFIG_PARTITIONS
	#define CONFIG_DOS_PARTITION
#endif

/********* RTK CONFIGS ************/
#define CONFIG_BSP_REALTEK
#define CONFIG_NO_RELOCATION
#define CONFIG_HEAP_ADDR	0x07880000

#define CONFIG_MISC_INIT_R
#endif /* __CONFIG_RTK_RTD1395_COMMON_H */

