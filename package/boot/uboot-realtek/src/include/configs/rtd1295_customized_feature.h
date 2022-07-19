/*
 * Configuration settings for the Realtek 1295 customized feature.
 *
 * Won't include this file.
 * Just type "make <board_name>_config" and will be included in source tree.
 */

#ifndef __CONFIG_RTK_RTD1195_CUSTOMIZED_FEATURE_H
#define __CONFIG_RTK_RTD1195_CUSTOMIZED_FEATURE_H



/* #define CONFIG_APPLY_CUSTOMIZED_FEATURE */


/* #define CONFIG_SILENT_CONSOLE */
#ifdef CONFIG_SILENT_CONSOLE
#undef	CONFIG_EXTRA_ENV_SETTINGS
#define CONFIG_EXTRA_ENV_SETTINGS	\
		"kernel_loadaddr=0x03000000\0"	\
		"fdt_loadaddr=0x01FF2000\0"	\
		"rootfs_loadaddr=0x02200000\0"	\
		"mtd_part=mtdparts=rtk_nand:\0"	\
		"silent=1\0"
#endif


#endif /* __CONFIG_RTK_RTD1295_CUSTOMIZED_FEATURE_H */

