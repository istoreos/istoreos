/*
 * 2017 by Marek Behun <marek.behun@nic.cz>
 *
 * Derived from code in ext4/dev.c, which was based on reiserfs/dev.c
 *
 * SPDX-License-Identifier:	GPL-2.0
 */

#ifndef __U_BOOT_FS_INTERNAL_H__
#define __U_BOOT_FS_INTERNAL_H__

#include <part.h>

int fs_devread(struct blk_desc *, disk_partition_t *, lbaint_t, int, int,
	       char *);

#endif /* __U_BOOT_FS_INTERNAL_H__ */
