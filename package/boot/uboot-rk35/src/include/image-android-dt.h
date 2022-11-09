/*
 * (C) Copyright 2018 Linaro Ltd.
 * Sam Protsenko <semen.protsenko@linaro.org>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef IMAGE_ANDROID_DT_H
#define IMAGE_ANDROID_DT_H

#include <linux/types.h>

bool android_dt_check_header(ulong hdr_addr);
bool android_dt_get_fdt_by_index(ulong hdr_addr, u32 index, ulong *addr,
				 u32 *size);
int android_dt_get_count(ulong hdr_addr);

#if !defined(CONFIG_SPL_BUILD)
void android_dt_print_contents(ulong hdr_addr);
#endif

/**
 * dt_for_each_entry() - iterate over all dt entry of DT image
 *
 * @entry:   struct dt_table_entry pointing to entry address
 * @hdr:     struct dt_table_header pointing to hdr address
 * @idx:     temporary index variant
 *
 * This is a wrapper around a for loop and is used like so:
 *
 *	struct dt_table_header *hdr;
 *	struct dt_table_entry *entry;
 *	int index;
 *
 *	......
 *
 *	dt_for_each_entry(entry, hdr, index) {
 *		Use entry
 *		...
 *	}
 *
 */
#define dt_for_each_entry(entry, hdr, idx) \
	for (idx = 0, android_dt_get_fdt_by_index((ulong)hdr, idx, (ulong *)&entry, NULL); \
	     idx < android_dt_get_count((ulong)hdr); \
	     idx++, android_dt_get_fdt_by_index((ulong)hdr, idx, (ulong *)&entry, NULL))

#endif /* IMAGE_ANDROID_DT_H */
