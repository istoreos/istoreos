/*
 * Copyright (c) 2017 General Electric Company. All rights reserved.
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <bootcount.h>
#include <fs.h>
#include <mapmem.h>

#define BC_MAGIC	0xbc

void bootcount_store(ulong a)
{
	u8 *buf;
	loff_t len;
	int ret;

	if (fs_set_blk_dev(CONFIG_SYS_BOOTCOUNT_EXT_INTERFACE,
			   CONFIG_SYS_BOOTCOUNT_EXT_DEVPART, FS_TYPE_EXT)) {
		puts("Error selecting device\n");
		return;
	}

	buf = map_sysmem(CONFIG_SYS_BOOTCOUNT_ADDR, 2);
	buf[0] = BC_MAGIC;
	buf[1] = (a & 0xff);
	unmap_sysmem(buf);

	ret = fs_write(CONFIG_SYS_BOOTCOUNT_EXT_NAME,
		       CONFIG_SYS_BOOTCOUNT_ADDR, 0, 2, &len);
	if (ret != 0)
		puts("Error storing bootcount\n");
}

ulong bootcount_load(void)
{
	u8 *buf;
	loff_t len_read;
	int ret;

	if (fs_set_blk_dev(CONFIG_SYS_BOOTCOUNT_EXT_INTERFACE,
			   CONFIG_SYS_BOOTCOUNT_EXT_DEVPART, FS_TYPE_EXT)) {
		puts("Error selecting device\n");
		return 0;
	}

	ret = fs_read(CONFIG_SYS_BOOTCOUNT_EXT_NAME, CONFIG_SYS_BOOTCOUNT_ADDR,
		      0, 2, &len_read);
	if (ret != 0 || len_read != 2) {
		puts("Error loading bootcount\n");
		return 0;
	}

	buf = map_sysmem(CONFIG_SYS_BOOTCOUNT_ADDR, 2);
	if (buf[0] == BC_MAGIC)
		ret = buf[1];

	unmap_sysmem(buf);

	return ret;
}
