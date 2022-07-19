/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the main directory of this archive
 * for more details.
 *
 * Copyright (C) 2015 by Tom Ting <tom_ting@realtek.com>
 *
 */

#include <common.h>
#include <asm/io.h>
#include <rtk/rtk_type.h>

#define DC_SECURE_MISC_reg		0x98008740

DECLARE_GLOBAL_DATA_PTR;

/*
 * get_accessible_ddr_size()
 */
/*
unsigned int get_accessible_ddr_size(int unit)
{
#ifdef CONFIG_BOARD_FPGA
	return CONFIG_SYS_RAM_DCU1_SIZE;
#else
	unsigned int dc_sys_misc_regBase;
	unsigned int dc_sys_misc_regValue;
	unsigned int dc_mem_density;
	unsigned int dc_mem_density_size=0;

	dc_sys_misc_regBase = DC_SECURE_MISC_reg;

	// get dc sys setting
	dc_sys_misc_regValue = __raw_readl((unsigned long)dc_sys_misc_regBase);

	// get ddr density size
	dc_mem_density = (dc_sys_misc_regValue & 0x3F);

	switch(dc_mem_density) {
		case 0x1:
			dc_mem_density_size = 512;      // bits
			break;

		case 0x2:
			dc_mem_density_size = 1024;     // bits
			break;

		case 0x4:
			dc_mem_density_size = 2048;     // bits
			break;

		case 0x8:
			dc_mem_density_size = 4096;     // bits
			break;

		case 0x10:
			dc_mem_density_size = 8192;     // bits
			break;

		case 0x20:
			dc_mem_density_size = 8192*2;   // bits
			break;

		default:
			printf("[ERR] %s: hw setting error. (impossible value 0x%x)\n", __FUNCTION__, dc_mem_density);
			printf("[ERR] Fall back to using CONFIG_SYS_RAM_DCU1_SIZE\n");
			return CONFIG_SYS_RAM_DCU1_SIZE;
	}
	dc_mem_density_size /=8;

	if(unit == UNIT_MEGABYTE)
		return dc_mem_density_size ;
	else
		return dc_mem_density_size* 0x100000;
#endif //CONFIG_BOARD_FPGA
}
*/
/**
 * @brief dram_init_banksize
 *
 * @return 0
 */
void dram_init_banksize(void)
{
	// Bank 1
	gd->bd->bi_dram[0].start = CONFIG_SYS_SDRAM_BASE;
	gd->bd->bi_dram[0].size = CONFIG_SYS_RAM_DCU1_SIZE;

#if (CONFIG_NR_DRAM_BANKS > 1)
	// Bank 2
	gd->bd->bi_dram[1].start = CONFIG_SYS_SDRAM_DCU2_BASE;
	gd->bd->bi_dram[1].size = CONFIG_SYS_RAM_DCU2_SIZE;
#endif

#if (CONFIG_NR_DRAM_BANKS > 2)
	// Bank 3
#if defined(CONFIG_SYS_SDRAM_DCU_OPT_BASE) && defined(CONFIG_SYS_RAM_DCU_OPT_SIZE)
	gd->bd->bi_dram[2].start = CONFIG_SYS_SDRAM_DCU_OPT_BASE;
	gd->bd->bi_dram[2].size = CONFIG_SYS_RAM_DCU_OPT_SIZE;
#endif
#endif
}

int dram_init(void)
{
	gd->ram_size = get_accessible_ddr_size(UNIT_BYTE);

	return 0;
}
