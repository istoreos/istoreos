/*
 * Realtek 1295 common configuration settings
 *
 * Won't include this file.
 * Just type "make <board_name>_config" and will be included in source tree.
 */

#ifndef __CONFIG_RTK_RTD1295_COMMON_MT_H
#define __CONFIG_RTK_RTD1295_COMMON_MT_H

#define CONFIG_UBOOT_DEFAULT
#define CONFIG_MODULE_TEST
/*
 * Realtek feature support
 */
#define CONFIG_BSP_REALTEK	1

/*
 * Realtek IC type
 */
#define CONFIG_RTD1295     1
/*
 * NAS
 */
//#define NAS_ENABLE			1	/* Enable NAS features */

#ifdef NAS_ENABLE
#define CONFIG_PARTITION_UUIDS
#endif

/*
 * TEE
 */
#define CONFIG_TEE_OS_ADDR     (0x10200000)
#define CONFIG_BL31_ADDR       (0x10120000)
//#define ENABLE_TEE
#ifdef ENABLE_TEE
#define CONFIG_TEE			1  /*Support TEE*/
#define CONFIG_TEE_ADDRESS			0x10100000
#endif
/*
 * High Level Configuration Options
 */
#define CONFIG_ARMV7		1	/* This is an ARM V7 CPU core */


/* Display CPU and Board Info */
#define CONFIG_DISPLAY_CPUINFO		1
#define CONFIG_DISPLAY_BOARDINFO	1

#define CONFIG_SKIP_LOWLEVEL_INIT	1

#undef CONFIG_USE_IRQ				/* no support for IRQs */

#define CONFIG_CMDLINE_TAG		1	/* enable passing of ATAGs */
#define CONFIG_SETUP_MEMORY_TAGS	1
//#define CONFIG_INITRD_TAG		1
#define CONFIG_REVISION_TAG		1

/*
 * Size of malloc() pool
 * Total Size Environment - 128k
 * Malloc - add 256k
 */
#define CONFIG_ENV_SIZE			(128 << 10)
#define CONFIG_SYS_MALLOC_LEN		(CONFIG_ENV_SIZE + (256 << 10))
#define CONFIG_SYS_NON_CACHE_LEN	(1 << 20)
/* Vector Base */
#define CONFIG_SYS_CA9_VECTOR_BASE	SRAM_ROM_VECT_BASE

/*
 *Size of RECOVERY 
 *Add factory Size - 2k
 *bootloader_message INFO
 *
 */
#define CONFIG_RECOVERY_SIZE	(2 << 10)

/*
 * Hardware drivers
 */

/*
 * serial port - NS16550 compatible
 */
#define V_NS16550_CLK				33000000

#define CONFIG_SYS_NS16550
#define CONFIG_SYS_NS16550_SERIAL
#define CONFIG_SYS_NS16550_REG_SIZE	(-4)
#define CONFIG_SYS_NS16550_CLK		V_NS16550_CLK
#define CONFIG_SYS_NS16550_UART1_CLK    432000000 


#define CONFIG_SERIAL_MULTI
#define UART1_BASE					0x9801B200
#define UART0_BASE					0x98007800
#define CONFIG_CONS_INDEX			1
#define CONFIG_SYS_NS16550_COM1     UART0_BASE
#define CONFIG_SYS_NS16550_COM2     UART1_BASE


#define CONFIG_BAUDRATE				115200
#define CONFIG_SYS_BAUDRATE_TABLE	{4800, 9600, 19200, 38400, 57600, 115200}

#define CONFIG_SYS_CONSOLE_IS_IN_ENV	1

#define UART0   0
#define UART1   1
#define UART2   2
#define UART3   3

#define MT_ACCESS_UART          UART1

/* Flash */
#define CONFIG_SYS_NO_FLASH	1

/* commands to include */
#include <config_cmd_default.h>

/* Disabled commands */
//#undef CONFIG_CMD_NET
#undef CONFIG_CMD_NFS
#undef CONFIG_CMD_FPGA		/* FPGA configuration Support   */
#undef CONFIG_CMD_IMLS		/* List all found images        */
#undef CONFIG_CMD_BOOTD
#undef CONFIG_CMD_BOOTM
#undef CONFIG_CMD_CRC32
#undef CONFIG_CMD_ECHO
#undef CONFIG_CMD_ITEST
#undef CONFIG_CMD_XIMG
#undef CONFIG_CMD_MISC
#undef CONFIG_CMD_SETGETDCR
#undef CONFIG_CMD_IMI
#undef CONFIG_CMD_IMPORTENV
#undef CONFIG_CMD_EXPORTENV
#undef CONFIG_CMD_RUN
#undef CONFIG_CMD_SOURCE
#undef CONFIG_CMD_BASE
#undef CONFIG_CMD_LOOP
#undef CONFIG_CMD_TEST
#undef CONFIG_CMD_TRUE
#undef CONFIG_CMD_FALSE
#undef CONFIG_CMD_LOADS
#undef CONFIG_CMD_VERSION
#undef CONFIG_CMD_EXIT
//#undef CONFIG_CMD_BDI
#undef CONFIG_CMD_CONSOLE
#undef CONFIG_CMD_SHOWVAR
#undef CONFIG_CMD_MM
#undef CONFIG_CMD_NM
#undef CONFIG_CMD_CMP
#undef CONFIG_CMD_CP

#define CONFIG_CMD_UNZIP
#define CONFIG_CMD_SOURCE

/*
 * Environment setup
 */

#define CONFIG_BOOTDELAY	0

#define CONFIG_ENV_OVERWRITE

#define CONFIG_BOOTARGS \
    "earlycon=uart8250,mmio32,0x98007800 console=ttyS0,115200 loglevel=4 cma=32m@576m noinitrd rootwait root=/dev/mmcblk0p1"
	//"earlycon=uart8250,mmio32,0x98007800 console=ttyS0,115200 loglevel=4 cma=64m@576m,init=/init androidboot.hardware=kylin"

#define CONFIG_BOOTCOMMAND \
	"bootr"

#define	CONFIG_CMD_BOOTM
#define CONFIG_KERNEL_LOADADDR	0x03000000
#define CONFIG_ROOTFS_LOADADDR 	0x02200000
#define CONFIG_LOGO_LOADADDR 	0x02002000	//reserved ~2M
#define CONFIG_FDT_LOADADDR		0x01F00000	//reserved ~1M
#define CONFIG_FW_LOADADDR 		0x01b00000  //reserved 4M

#define CONFIG_EXTRA_ENV_SETTINGS                   \
   "bootcode2ndtmp_loadaddr=0x01500000\0"	\
   "bootcode2nd_loadaddr=0x00021000\0"		\
   "kernel_loadaddr=0x03000000\0"                  \
   "fdt_loadaddr=0x01F00000\0"                  \
   "rootfs_loadaddr=0x02200000\0"                   \
   "mtd_part=mtdparts=rtk_nand:\0"                  \

/* Pass open firmware flat tree */
#define CONFIG_FIT 					1
#define CONFIG_OF_LIBFDT    		1
//#define CONFIG_OF_BOARD_SETUP		1
#define CONFIG_OF_STDOUT_VIA_ALIAS	1
//#define CONFIG_SYS_BOOTMAPSZ   	0x10000000       /* Initial Memory map for Linux */
//#define CONFIG_LMB 				1


/* Console */
#define CONFIG_CMDLINE_EDITING
#define CONFIG_AUTO_COMPLETE

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
#define CONFIG_TAR

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


#define CONFIG_NO_RELOCATION
//if the relocation is enabled, the address is used to be the stack at very beginning.
#define CONFIG_SYS_INIT_SP_ADDR     0x00100000


#if 0 // 1:cache disable   0:enable
	#define CONFIG_SYS_ICACHE_OFF
	#define CONFIG_SYS_DCACHE_OFF
#else
	#define CONFIG_NONCACHE_ALLOCATION
	#define CONFIG_CMD_CACHE
#endif

#define CONFIG_SYS_CACHELINE_SIZE	64

/*
 * rm include/autoconf.mk ---- prevent use old CONFIG_SYS_TEXT_BASE
 * make CONFIG_SYS_TEXT_BASE
 */
#ifndef CONFIG_SYS_TEXT_BASE
	#define CONFIG_SYS_TEXT_BASE		0x00021000
#endif
#define CONFIG_BOOT_PARAM_BASE			(0x00100000 + 0x100)
#define CONFIG_HEAP_RELOCATION

/* ENV related config options */
#define CONFIG_ENV_IS_NOWHERE

#define CONFIG_SYS_PROMPT       		"Realtek> "
#define CONFIG_SYS_MTPROMPT       		"RTKMT>"

/* Library support */
#define CONFIG_LZMA
#define CONFIG_LZO

#ifdef CONFIG_CMD_NET
	/* Eth Net */
	#define CONFIG_CMD_PING
	#define CONFIG_CMD_TFTPPUT
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
//#define CONFIG_PARTITIONS
#define CONFIG_DOS_PARTITION
#define CONFIG_EFI_PARTITION
#define CONFIG_CMD_USB
#define CONFIG_USB_STORAGE
#define CONFIG_USB_EHCI
#define CONFIG_USB_EHCI_RTK
#define CONFIG_USB_XHCI
#define CONFIG_SYS_USB_XHCI_MAX_ROOT_PORTS 5

#define CONFIG_USB_MAX_CONTROLLER_COUNT 4

/* PCB Manager */
//#define CONFIG_SYS_PCB_MANAGER

/* Factory */
#define CONFIG_SYS_FACTORY
#define PANEL_CONFIG_FROM_FACTORY_PANEL_BIN

/* Factory Read-only : depend on customer */
//#define CONFIG_SYS_FACTORY_READ_ONLY

/* Panel Parameter */
//#define CONFIG_SYS_PANEL_SUPPORT
//#define CONFIG_SYS_PANEL_PARAMETER
//#define CONFIG_CMD_PANEL

/* TCON settting from factory */
//#define CONFIG_PANEL_APPLY_TCON_SETTING

/* Pin Mux */
//#define CONFIG_SYS_PIN_MUX

/* GPIO */
#define CONFIG_REALTEK_GPIO
#define CONFIG_INSTALL_GPIO_NUM    		8
#define CONFIG_HDMITx_HPD_IGPIO_NUM		6

/* I2C */
#define CONFIG_I2C_MULTI_BUS
#define CONFIG_REALTEK_I2C

/* PWM */
//#define CONFIG_REALTEK_PWM

/* LSADC */
//#define CONFIG_REALTEK_LSADC

/* MISC Wakeup */
//#define CONFIG_MISC_MGR_WAKEUP

/* Logo Display */
//#define CONFIG_SYS_LOGO_DISP
#ifdef CONFIG_SYS_LOGO_DISP
	//#define CONFIG_SYS_LOGO_DISP_NTSC
	//#define CONFIG_SYS_LOGO_DISP_PAL
	//#define CONFIG_SYS_LOGO_DISP_1080P50
	//#define CONFIG_SYS_LOGO_DISP_1080P60
#endif

/* IR driver */
//#define CONFIG_SYS_IR_SUPPORT
#ifdef CONFIG_SYS_IR_SUPPORT
	//#define CONFIG_IR_NEC_PROTOCOL
	//#define CONFIG_IR_DELAY 110
	//#define CONFIG_IR_SONY_PROTOCOL
	//#define CONFIG_IR_RC5_PROTOCOL
	//#define CONFIG_IR_RC6_PROTOCOL
	//#define CONFIG_IR_KK_Y261_PROTOCOL
#endif

/* Auto detect sink*/
#define CONFIG_SYS_AUTO_DETECT
#define CONFIG_DEFAULT_TV_SYSTEM    	30 //1080P_59
#define CONFIG_DEFAULT_MHL_TV_SYSTEM    27 //1080I_59

/*Power Saving*/
#define CONFIG_MISC_INIT_R
#define CONFIG_RTK_POWER


#if 0
/* Bootcode Feature: Detect install.img from USB when AC on */
#define CONFIG_USB_UPDATE_WHEN_AC_ON

/* Bootcode Feature: Detect dvrboot.exe.bin from USB when AC on */
#define CONFIG_USB_UPDATE_UBOOT_WHEN_AC_ON

/* Bootcode Feature: Read rescue linux from install.img or flash */
//#define CONFIG_USB_UPDATE_READ_RESCUE_FROM_FLASH
#endif

#if 0
/* Bootcode Feature: Clear env from factory after updated bootcode */
#define CONFIG_CLEAR_ENV_AFTER_UPDATE_BOOTCODE
#endif

#if 1
/* Bootcode Feature: Display the time information to evaluate */
#define CONFIG_DISPLAY_TIME_EVALUATION
#endif

#if 0
/* Bootcode Feature: Customize function callback register */
#define CONFIG_CUSTOMIZE_FUNC_REGISTER
#endif

#if 0
/* build uboot run flash_writer directly */
#define CONFIG_RUN_FLASH_WRITER
#endif

// Config panel name and compile options
#if (0)
   // default 60Hz panel
  /* LVDS panel setting */
  #define CONFIG_PANEL_NAME "asm/arch/panel/default_panel.h"
#endif

/* enable key burn function */
//#define CONFIG_CMD_KEY_BURNING

#define CONFIG_ENV_EXPORT_ADDR 0x10000000

#endif /* __CONFIG_RTK_RTD1295_COMMON_H */

