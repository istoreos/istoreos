/* SPDX-License-Identifier:	GPL-2.0+ BSD-2-Clause */
#include "fdt_host.h"
#include "../../scripts/dtc/libfdt/fdt_rw.c"

int fdt_remove_unused_strings(const void *old, void *new)
{
	const struct fdt_property *old_prop;
	struct fdt_property *new_prop;
	int size = fdt_totalsize(old);
	int next_offset, offset;
	const char *str;
	int ret;
	int tag = FDT_PROP;

	/* Make a copy and remove the strings */
	memcpy(new, old, size);
	fdt_set_size_dt_strings(new, 0);

	/* Add every property name back into the new string table */
	for (offset = 0; tag != FDT_END; offset = next_offset) {
		tag = fdt_next_tag(old, offset, &next_offset);
		if (tag != FDT_PROP)
			continue;
		old_prop = fdt_get_property_by_offset(old, offset, NULL);
		new_prop = (struct fdt_property *)(unsigned long)
			fdt_get_property_by_offset(new, offset, NULL);
		str = fdt_string(old, fdt32_to_cpu(old_prop->nameoff));
		ret = _fdt_find_add_string(new, str);
		if (ret < 0)
			return ret;
		new_prop->nameoff = cpu_to_fdt32(ret);
	}

	return 0;
}
