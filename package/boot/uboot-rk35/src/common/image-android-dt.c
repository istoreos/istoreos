/*
 * (C) Copyright 2018 Linaro Ltd.
 * Sam Protsenko <semen.protsenko@linaro.org>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <image-android-dt.h>
#include <dt_table.h>
#include <common.h>
#include <linux/libfdt.h>
#include <mapmem.h>

/**
 * Check if image header is correct.
 *
 * @param hdr_addr Start address of DT image
 * @return true if header is correct or false if header is incorrect
 */
bool android_dt_check_header(ulong hdr_addr)
{
	const struct dt_table_header *hdr;
	u32 magic;

	hdr = map_sysmem(hdr_addr, sizeof(*hdr));
	magic = fdt32_to_cpu(hdr->magic);
	unmap_sysmem(hdr);

	return magic == DT_TABLE_MAGIC;
}

/**
 * Get the address of FDT (dtb or dtbo) in memory by its index in image.
 *
 * @param hdr_addr Start address of DT image
 * @param index Index of desired FDT in image (starting from 0)
 * @param[out] addr If not NULL, will contain address to specified FDT
 * @param[out] size If not NULL, will contain size of specified FDT
 *
 * @return true on success or false on error
 */
bool android_dt_get_fdt_by_index(ulong hdr_addr, u32 index, ulong *addr,
				 u32 *size)
{
	const struct dt_table_header *hdr;
	const struct dt_table_entry *e;
	u32 entry_count, entries_offset, entry_size;
	ulong e_addr;
	u32 dt_offset, dt_size;

	hdr = map_sysmem(hdr_addr, sizeof(*hdr));
	entry_count = fdt32_to_cpu(hdr->dt_entry_count);
	entries_offset = fdt32_to_cpu(hdr->dt_entries_offset);
	entry_size = fdt32_to_cpu(hdr->dt_entry_size);
	unmap_sysmem(hdr);

	if (index > entry_count) {
		printf("Error: index > dt_entry_count (%u > %u)\n", index,
		       entry_count);
		return false;
	}

	e_addr = hdr_addr + entries_offset + index * entry_size;
	e = map_sysmem(e_addr, sizeof(*e));
	dt_offset = fdt32_to_cpu(e->dt_offset);
	dt_size = fdt32_to_cpu(e->dt_size);
	unmap_sysmem(e);

	if (addr)
		*addr = hdr_addr + dt_offset;
	if (size)
		*size = dt_size;

	return true;
}

#if !defined(CONFIG_SPL_BUILD)
static void android_dt_print_fdt_info(const struct fdt_header *fdt)
{
	u32 fdt_size;
	int root_node_off;
	const char *compatible = NULL;

	fdt_size = fdt_totalsize(fdt);
	root_node_off = fdt_path_offset(fdt, "/");
	if (root_node_off < 0) {
		printf("Error: Root node not found\n");
	} else {
		compatible = fdt_getprop(fdt, root_node_off, "compatible",
					 NULL);
	}

	printf("           (FDT)size = %d\n", fdt_size);
	printf("     (FDT)compatible = %s\n",
	       compatible ? compatible : "(unknown)");
}

/**
 * Print information about DT image structure.
 *
 * @param hdr_addr Start address of DT image
 */
void android_dt_print_contents(ulong hdr_addr)
{
	const struct dt_table_header *hdr;
	u32 entry_count, entries_offset, entry_size;
	u32 i;

	hdr = map_sysmem(hdr_addr, sizeof(*hdr));
	entry_count = fdt32_to_cpu(hdr->dt_entry_count);
	entries_offset = fdt32_to_cpu(hdr->dt_entries_offset);
	entry_size = fdt32_to_cpu(hdr->dt_entry_size);

	/* Print image header info */
	printf("dt_table_header:\n");
	printf("               magic = %08x\n", fdt32_to_cpu(hdr->magic));
	printf("          total_size = %d\n", fdt32_to_cpu(hdr->total_size));
	printf("         header_size = %d\n", fdt32_to_cpu(hdr->header_size));
	printf("       dt_entry_size = %d\n", entry_size);
	printf("      dt_entry_count = %d\n", entry_count);
	printf("   dt_entries_offset = %d\n", entries_offset);
	printf("           page_size = %d\n", fdt32_to_cpu(hdr->page_size));
	printf("             version = %08x\n", fdt32_to_cpu(hdr->version));

	unmap_sysmem(hdr);

	/* Print image entries info */
	for (i = 0; i < entry_count; ++i) {
		const ulong e_addr = hdr_addr + entries_offset + i * entry_size;
		const struct dt_table_entry *e;
		const struct fdt_header *fdt;
		u32 dt_offset, dt_size;
		u32 j;

		e = map_sysmem(e_addr, sizeof(*e));
		dt_offset = fdt32_to_cpu(e->dt_offset);
		dt_size = fdt32_to_cpu(e->dt_size);

		printf("dt_table_entry[%d]:\n", i);
		printf("             dt_size = %d\n", dt_size);
		printf("           dt_offset = %d\n", dt_offset);
		printf("                  id = %08x\n", fdt32_to_cpu(e->id));
		printf("                 rev = %08x\n", fdt32_to_cpu(e->rev));
		for (j = 0; j < 4; ++j) {
			printf("           custom[%d] = %08x\n", j,
			       fdt32_to_cpu(e->custom[j]));
		}

		unmap_sysmem(e);

		/* Print FDT info for this entry */
		fdt = map_sysmem(hdr_addr + dt_offset, sizeof(*fdt));
		android_dt_print_fdt_info(fdt);
		unmap_sysmem(fdt);
	}
}
#endif

/**
 * Get dt entry count of DT image structure.
 *
 * @param hdr_addr Start address of DT image
 */
int android_dt_get_count(ulong hdr_addr)
{
	const struct dt_table_header *hdr;
	int count;

	hdr = map_sysmem(hdr_addr, sizeof(*hdr));
	count = fdt32_to_cpu(hdr->dt_entry_count);
	unmap_sysmem(hdr);

	return count;
}
