/* SPDX-License-Identifier: BSD-3-Clause */
/*
 * This is from the Android Project,
 * Repository: https://android.googlesource.com/platform/system/libufdt
 * File: utils/src/dt_table.h
 * Commit: 2626d8b9e4d8e8c6cc67ceb1dc4e05a47779785c
 * Copyright (C) 2017 The Android Open Source Project
 */

#ifndef DT_TABLE_H
#define DT_TABLE_H

#include <linux/types.h>

#define DT_TABLE_MAGIC			0xd7b7ab1e
#define DT_TABLE_DEFAULT_PAGE_SIZE	2048
#define DT_TABLE_DEFAULT_VERSION	0

struct dt_table_header {
	u32 magic;		/* DT_TABLE_MAGIC */
	u32 total_size;		/* includes dt_table_header + all dt_table_entry
				 * and all dtb/dtbo
				 */
	u32 header_size;	/* sizeof(dt_table_header) */

	u32 dt_entry_size;	/* sizeof(dt_table_entry) */
	u32 dt_entry_count;	/* number of dt_table_entry */
	u32 dt_entries_offset;	/* offset to the first dt_table_entry
				 * from head of dt_table_header.
				 * The value will be equal to header_size if
				 * no padding is appended
				 */
	u32 page_size;		/* flash page size we assume */
	u32 version;            /* DTBO image version, the current version is 0.
				 * The version will be incremented when the
				 * dt_table_header struct is updated.
				 */
};

struct dt_table_entry {
	u32 dt_size;
	u32 dt_offset;		/* offset from head of dt_table_header */

	u32 id;			/* optional, must be zero if unused */
	u32 rev;		/* optional, must be zero if unused */
	u32 custom[4];		/* optional, must be zero if unused */
};

#endif
