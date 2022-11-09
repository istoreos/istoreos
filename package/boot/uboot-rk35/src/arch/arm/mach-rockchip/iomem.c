/*
 * SPDX-License-Identifier:     GPL-2.0+
 *
 * (C) Copyright 2018 Rockchip Electronics Co., Ltd
 *
 */

#include <asm/io.h>
#include <common.h>
#include <dm.h>
#include <fdtdec.h>

enum ops {
	SEARCH_NAME,
	SEARCH_COMP,
};

void iomem_show(const char *label, unsigned long base, size_t start, size_t end)
{
	unsigned long val, offset = start, nr = 0;

	if (label)
		printf("%s:\n", label);

	printf("%08lx:  ", base + offset);
	for (offset = start; offset <= end; offset += 0x04) {
		if (nr >= 4) {
			printf("\n%08lx:  ", base + offset);
			nr = 0;
		}
		val = readl((void __iomem *)base + offset);
		printf("%08lx ", val);
		nr++;
	}
	printf("\n");
}

static int iomem_show_by_match(enum ops op, const char *search,
			       size_t start, size_t end)
{
	const void *fdt = gd->fdt_blob;
	const char *name;
	fdt_addr_t addr;
	int found = 0;
	int offset;

	for (offset = fdt_next_node(fdt, 0, NULL);
	     offset >= 0;
	     offset = fdt_next_node(fdt, offset, NULL)) {
		if (op == SEARCH_COMP)
			name = fdt_getprop(fdt, offset, "compatible", NULL);
		else if (op == SEARCH_NAME)
			name = fdt_get_name(fdt, offset, NULL);
		else
			goto out;

		if (!name)
			continue;

		if (strstr(name, search)) {
			addr = fdtdec_get_addr_size_auto_noparent(fdt, offset,
							"reg", 0, NULL, false);
			if (addr == FDT_ADDR_T_NONE)
				goto out;

			iomem_show(name, addr, start, end);
			found = 1;
			break;
		}
	}
	printf("\n");

out:
	return found;
}

void iomem_show_by_compatible(const char *compat, size_t start, size_t end)
{
	iomem_show_by_match(SEARCH_COMP, compat, start, end);
}

static int do_iomem_by_match(cmd_tbl_t *cmdtp, int flag,
			     int argc, char *const argv[])
{
	size_t start, end;
	const char *search;

	if (argc != 4)
		return CMD_RET_USAGE;

	search = argv[1];
	start = simple_strtoul(argv[2], NULL, 0);
	end = simple_strtoul(argv[3], NULL, 0);

	if (!iomem_show_by_match(SEARCH_COMP, search, start, end))
		iomem_show_by_match(SEARCH_NAME, search, start, end);

	return 0;
}

U_BOOT_CMD(
	iomem, 4, 1, do_iomem_by_match,
	"Show iomem data by device compatible(high priority) or node name",
	"iomem <compatible or node name> <start offset>  <end offset>\n"
	"  eg: iomem -grf  0x0 0x200"
	"  eg: iomem gpio3 0x0 0x200"
);
