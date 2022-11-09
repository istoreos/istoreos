/*
 * (C) Copyright 2021 Rockchip Electronics Co., Ltd
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */

#include <common.h>
#include <boot_rkimg.h>
#include <malloc.h>
#include <asm/io.h>
#include <asm/arch-rockchip/boot_mode.h>

static int misc_require_recovery(struct blk_desc *dev_desc, u32 bcb_offset)
{
	struct bootloader_message *bmsg;
	disk_partition_t part;
	int cnt, recovery;

	if (!dev_desc)
		return 0;

	if (part_get_info_by_name(dev_desc, PART_MISC, &part) < 0) {
		printf("No misc partition\n");
		return 0;
	}

	cnt = DIV_ROUND_UP(sizeof(struct bootloader_message), dev_desc->blksz);
	bmsg = memalign(ARCH_DMA_MINALIGN, cnt * dev_desc->blksz);
	if (!bmsg)
		return 0;

	if (blk_dread(dev_desc, part.start + bcb_offset, cnt, bmsg) != cnt)
		return 0;

	recovery = !strcmp(bmsg->command, "boot-recovery");
	free(bmsg);

	return recovery;
}

int rockchip_get_boot_mode(struct blk_desc *dev_desc, u32 bcb_sector_offset)
{
	uint32_t reg_boot_mode;
	int boot_mode;

	/*
	 * Boot mode priority
	 *
	 * Anyway, we should set download boot mode as the highest priority, so:
	 * reboot loader/bootloader/fastboot > misc partition "recovery" > reboot xxx.
	 */
	reg_boot_mode = readl((void *)CONFIG_ROCKCHIP_BOOT_MODE_REG);
	if (reg_boot_mode == BOOT_LOADER) {
		printf("boot mode: loader\n");
		boot_mode = BOOT_MODE_LOADER;
	} else if (reg_boot_mode == BOOT_DFU) {
		printf("boot mode: dfu\n");
		boot_mode = BOOT_MODE_DFU;
	} else if (reg_boot_mode == BOOT_FASTBOOT) {
		printf("boot mode: bootloader\n");
		boot_mode = BOOT_MODE_BOOTLOADER;
	} else if (misc_require_recovery(dev_desc, bcb_sector_offset)) {
		printf("boot mode: recovery (misc)\n");
		boot_mode = BOOT_MODE_RECOVERY;
	} else {
		switch (reg_boot_mode) {
		case BOOT_NORMAL:
			printf("boot mode: normal\n");
			boot_mode = BOOT_MODE_NORMAL;
			break;
		case BOOT_RECOVERY:
			printf("boot mode: recovery (cmd)\n");
			boot_mode = BOOT_MODE_RECOVERY;
			break;
		case BOOT_UMS:
			printf("boot mode: ums\n");
			boot_mode = BOOT_MODE_UMS;
			break;
		case BOOT_CHARGING:
			printf("boot mode: charging\n");
			boot_mode = BOOT_MODE_CHARGING;
			break;
		case BOOT_PANIC:
			printf("boot mode: panic\n");
			boot_mode = BOOT_MODE_PANIC;
			break;
		case BOOT_WATCHDOG:
			printf("boot mode: watchdog\n");
			boot_mode = BOOT_MODE_WATCHDOG;
			break;
		default:
			printf("boot mode: None\n");
			boot_mode = BOOT_MODE_UNDEFINE;
		}
	}

	return boot_mode;
}
