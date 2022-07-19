/*
 * Configuration settings for the Realtek 1295 fpga board.
 *
 * Won't include this file.
 * Just type "make <board_name>_config" and will be included in source tree.
 */

#ifndef __CONFIG_RTK_RTD1295_FPGA_H
#define __CONFIG_RTK_RTD1295_FPGA_H

/*
 * Include the common settings of RTD1295 platform.
 */
#include <configs/rtd1295_common.h>

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
#define CONFIG_SYS_RAM_DCU1_SIZE	0x20000000

#undef  V_NS16550_CLK
#define V_NS16550_CLK			33000000

#define COUNTER_FREQUENCY               33000000 // FIXME, need to know what impact it will cause

#define CONFIG_VERSION			"0000"

#endif /* __CONFIG_RTK_RTD1295_FPGA_H */

