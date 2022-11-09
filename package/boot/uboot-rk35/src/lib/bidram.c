// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (c) 2019 Fuzhou Rockchip Electronics Co., Ltd
 */

#include <common.h>
#include <lmb.h>
#include <bidram.h>
#include <malloc.h>
#include <sysmem.h>
#include <asm/io.h>
#include <asm/arch-rockchip/rk_atags.h>

DECLARE_GLOBAL_DATA_PTR;

#define MAX_BAD_MEMBLK		8

#define BIDRAM_R(fmt, args...)	printf(fmt, ##args)
#define BIDRAM_I(fmt, args...)	printf("Bidram: "fmt, ##args)
#define BIDRAM_W(fmt, args...)	printf("Bidram Warn: "fmt, ##args)
#define BIDRAM_E(fmt, args...)	printf("Bidram Error: "fmt, ##args)
#define BIDRAM_D(fmt, args...)	 debug("Bidram Debug: "fmt, ##args)

struct bidram plat_bidram __section(".data") = { .has_init = false, };

static int bidram_has_init(void)
{
	if (!plat_bidram.has_init) {
		BIDRAM_E("Framework is not initialized\n");
		return 0;
	}

	return 1;
}

void bidram_dump(void)
{
	struct bidram *bidram = &plat_bidram;
	struct lmb *lmb = &bidram->lmb;
	struct memblock *mem;
	struct list_head *node;
	ulong memory_size = 0;
	ulong reserved_size = 0;
	ulong i;

	if (!bidram_has_init())
		return;

	printf("\n\nbidram_dump_all:\n");

	/* Memory pool */
	printf("    --------------------------------------------------------------------\n");
	for (i = 0; i < lmb->memory.cnt; i++) {
		memory_size += lmb->memory.region[i].size;
		printf("    memory.rgn[%ld].addr     = 0x%08lx - 0x%08lx (size: 0x%08lx)\n", i,
		       (ulong)lmb->memory.region[i].base,
		       (ulong)lmb->memory.region[i].base +
		       (ulong)lmb->memory.region[i].size,
		       (ulong)lmb->memory.region[i].size);
	}
	printf("\n    memory.total	   = 0x%08lx (%ld MiB. %ld KiB)\n",
	       (ulong)memory_size,
	       SIZE_MB((ulong)memory_size),
	       SIZE_KB((ulong)memory_size));

	/* Reserved */
	i = 0;
	printf("    --------------------------------------------------------------------\n");
	list_for_each(node, &bidram->reserved_head) {
		mem = list_entry(node, struct memblock, node);
		reserved_size += mem->size;
		printf("    reserved.rgn[%ld].name   = \"%s\"\n", i, mem->attr.name);
		printf("		   .addr   = 0x%08lx - 0x%08lx (size: 0x%08lx)\n",
		       (ulong)mem->base, (ulong)mem->base + (ulong)mem->size,
		       (ulong)mem->size);
		i++;
	}
	printf("\n    reserved.total	   = 0x%08lx (%ld MiB. %ld KiB)\n",
	       (ulong)reserved_size,
	       SIZE_MB((ulong)reserved_size),
	       SIZE_KB((ulong)reserved_size));

	/* LMB core reserved */
	printf("    --------------------------------------------------------------------\n");
	reserved_size = 0;
	for (i = 0; i < lmb->reserved.cnt; i++) {
		reserved_size += lmb->reserved.region[i].size;
		printf("    LMB.reserved[%ld].addr   = 0x%08lx - 0x%08lx (size: 0x%08lx)\n", i,
		       (ulong)lmb->reserved.region[i].base,
		       (ulong)lmb->reserved.region[i].base +
		       (ulong)lmb->reserved.region[i].size,
		       (ulong)lmb->reserved.region[i].size);
	}

	printf("\n    reserved.core.total	   = 0x%08lx (%ld MiB. %ld KiB)\n",
	       (ulong)reserved_size,
	       SIZE_MB((ulong)reserved_size),
	       SIZE_KB((ulong)reserved_size));
	printf("    --------------------------------------------------------------------\n\n");
}

static int bidram_add(phys_addr_t base, phys_size_t size)
{
	struct bidram *bidram = &plat_bidram;
	int ret;

	if (!bidram_has_init())
		return -ENOSYS;

	if (!size)
		return -EINVAL;

	ret = lmb_add(&bidram->lmb, base, size);
	if (ret < 0)
		BIDRAM_E("Failed to add bidram at 0x%08lx - 0x%08lx\n",
			 (ulong)base, (ulong)(base + size));

	return (ret >= 0) ? 0 : ret;
}

void bidram_gen_gd_bi_dram(void)
{
	struct bidram *bidram = &plat_bidram;
	struct lmb *lmb = &plat_bidram.lmb;
	struct lmb_property *mem_rgn = lmb->memory.region;
	struct lmb_property *res_rgn = lmb->reserved.region;
	int rsv_cnt = lmb->reserved.cnt;
	int i, idx = 0;

	if (!gd || !gd->bd) {
		BIDRAM_D("Ignore bi dram bank update\n");
		return;
	}

	/*
	 * LBM default init:
	 *		lmb->reserved.cnt = 1;
	 *		lmb->reserved.region[0].base = 0;
	 *		lmb->reserved.region[0].size = 0;
	 *
	 * Here handle that: there is the only one dram bank available.
	 */
	if (rsv_cnt == 1 && !res_rgn[0].base && !res_rgn[0].size) {
		gd->bd->bi_dram[idx].start = mem_rgn[0].base;
		gd->bd->bi_dram[idx].size = mem_rgn[0].size;
		idx++;
		goto done;
	}

	/* If reserved rgn is not from sdram start */
	if (res_rgn[0].base != mem_rgn[0].base) {
		gd->bd->bi_dram[idx].start = mem_rgn[0].base;
		gd->bd->bi_dram[idx].size  = res_rgn[0].base -
					     gd->bd->bi_dram[idx].start;
		idx++;
	}

	/*
	 * Note: If reserved rgn is not from sdram start, idx=1 now, otherwise 0.
	 */
	for (i = 0; i < rsv_cnt; i++, idx++) {
		if (res_rgn[i].base + res_rgn[i].size >= gd->ram_top)
			goto done;

		gd->bd->bi_dram[idx].start = res_rgn[i].base + res_rgn[i].size;
		if (i + 1 < rsv_cnt)
			gd->bd->bi_dram[idx].size = res_rgn[i + 1].base -
					    gd->bd->bi_dram[idx].start;
		else
			gd->bd->bi_dram[idx].size = gd->ram_top -
					    gd->bd->bi_dram[idx].start;
	}
done:
	/* Append 4GB+ memory blocks and extend ram top */
	if (bidram->fixup) {
		/* extend ram top */
		if (gd->ram_top_ext_size) {
		        int pos = idx - 1;
			ulong top;

			if (gd->bd->bi_dram[pos].start +
			    gd->bd->bi_dram[pos].size == gd->ram_top) {
				top = gd->bd->bi_dram[pos].start + gd->bd->bi_dram[pos].size;
				gd->bd->bi_dram[pos].size += gd->ram_top_ext_size;
				printf("Extend top: 0x%08lx -> 0x%08lx\n",
				       top, top + (ulong)gd->ram_top_ext_size);
			}
		}

		/* append 4GB+ */
		for (i = 0; i < MEM_RESV_COUNT; i++) {
			if (!bidram->size_u64[i])
				continue;
			gd->bd->bi_dram[idx].start = bidram->base_u64[i];
			gd->bd->bi_dram[idx].size  = bidram->size_u64[i];
			BIDRAM_D("FIXUP: gd->bi_dram[%d]: start=0x%llx, size=0x%llx\n",
				 idx, bidram->base_u64[i], bidram->size_u64[i]);
			idx++;
		}
	}

	for (i = 0; i < idx; i++) {
		BIDRAM_D("GEN: gd->bi_dram[%d]: start=0x%llx, end=0x%llx\n",
			 i, (u64)gd->bd->bi_dram[i].start,
			 (u64)gd->bd->bi_dram[i].start +
			 (u64)gd->bd->bi_dram[i].size);
	}
}

int bidram_fixup(void)
{
	struct bidram *bidram = &plat_bidram;

	bidram->fixup = true;
	bidram_gen_gd_bi_dram();

	return 0;
}

u64 bidram_append_size(void)
{
	struct bidram *bidram = &plat_bidram;
	u64 size = 0;
	int i;

	/* 4GB+ */
	for (i = 0; i < MEM_RESV_COUNT; i++)
		size += bidram->size_u64[i];

	if (gd->ram_top_ext_size)
		size += gd->ram_top_ext_size;

	return size;
}

static int bidram_is_overlap(phys_addr_t base1, phys_size_t size1,
			     phys_addr_t base2, phys_size_t size2)
{
	return ((base1 < (base2 + size2)) && (base2 < (base1 + size1)));
}

struct memblock *bidram_reserved_is_overlap(phys_addr_t base, phys_size_t size)
{
	struct bidram *bidram = &plat_bidram;
	struct list_head *node;
	struct memblock *mem;

	if (!bidram_has_init())
		return false;

	list_for_each(node, &bidram->reserved_head) {
		mem = list_entry(node, struct memblock, node);
		if (bidram_is_overlap(mem->base, mem->size, base, size))
			return mem;
	}

	return NULL;
}

static int bidram_core_reserve(enum memblk_id id, const char *mem_name,
			       phys_addr_t base, phys_size_t size)
{
	struct bidram *bidram = &plat_bidram;
	struct memblk_attr attr;
	struct memblock *mem;
	struct list_head *node;
	const char *name;
	int ret;

	if (!bidram_has_init())
		return -ENOSYS;

	if (id == MEM_BY_NAME) {
		if (!mem_name) {
			BIDRAM_E("NULL name for reserve bidram\n");
			return -EINVAL;
		} else {
			name = mem_name;
		}
	} else {
		if (id > MEM_UNK && id < MEM_MAX) {
			attr = mem_attr[id];
			name = attr.name;
		} else {
			BIDRAM_E("Unsupport memblk id %d for reserve bidram\n", id);
			return -EINVAL;
		}
	}

	if (!name) {
		BIDRAM_E("NULL name for reserved bidram\n");
		return -EINVAL;
	}

	if (!size)
		return 0;

	/* Check overlap */
	list_for_each(node, &bidram->reserved_head) {
		mem = list_entry(node, struct memblock, node);
		BIDRAM_D("Has reserved: %s 0x%08lx - 0x%08lx\n",
			 mem->attr.name, (ulong)mem->base,
			 (ulong)(mem->base + mem->size));
		if (!strcmp(mem->attr.name, name)) {
			BIDRAM_E("Failed to double reserve for existence \"%s\"\n", name);
			return -EEXIST;
		} else if (bidram_is_overlap(mem->base, mem->size, base, size)) {
			BIDRAM_D("\"%s\" (0x%08lx - 0x%08lx) reserve is "
				 "overlap with existence \"%s\" (0x%08lx - "
				 "0x%08lx)\n",
				 name, (ulong)base, (ulong)(base + size), mem->attr.name,
				 (ulong)mem->base, (ulong)(mem->base + mem->size));
		}
	}

	BIDRAM_D("Reserve: \"%s\" 0x%08lx - 0x%08lx\n",
		 name, (ulong)base, (ulong)(base + size));

	ret = lmb_reserve(&bidram->lmb, base, size);
	if (ret >= 0) {
		mem = malloc(sizeof(*mem));
		if (!mem) {
			BIDRAM_E("No memory for \"%s\" reserve bidram\n", name);
			return -ENOMEM;
		}

#ifdef CONFIG_SYSMEM
		/* Sync to sysmem */
		if (sysmem_has_init()) {
			void *paddr;

			if (id == MEM_BY_NAME)
				paddr = sysmem_alloc_base_by_name(name, base, size);
			else
				paddr = sysmem_alloc_base(id, base, size);
			if (!paddr) {
				BIDRAM_E("Sync \"%s\" to sysmem failed\n", name);
				return -ENOMEM;
			}
		}
#endif
		mem->base = base;
		mem->size = size;
		if (id == MEM_BY_NAME) {
			mem->attr.name = name;
			mem->attr.flags = 0;
		} else {
			mem->attr = attr;
		}
		list_add_tail(&mem->node, &bidram->reserved_head);
	} else {
		BIDRAM_E("Failed to reserve \"%s\" 0x%08lx - 0x%08lx\n",
			 name, (ulong)base, (ulong)(base + size));
		return -EINVAL;
	}

	return 0;
}

int bidram_reserve(enum memblk_id id, phys_addr_t base, phys_size_t size)
{
	int ret;

	ret = bidram_core_reserve(id, NULL, base, size);
	if (!ret)
		bidram_gen_gd_bi_dram();
	else
		bidram_dump();

	return ret;
}

int bidram_reserve_by_name(const char *name,
			   phys_addr_t base, phys_size_t size)
{
	int ret;

	ret = bidram_core_reserve(MEM_BY_NAME, name, base, size);
	if (!ret)
		bidram_gen_gd_bi_dram();
	else
		bidram_dump();

	return ret;
}

int bidram_initr(void)
{
	return !bidram_get_ram_size();
}

phys_size_t bidram_get_ram_size(void)
{
	struct bidram *bidram = &plat_bidram;
	struct memblock bad[MAX_BAD_MEMBLK];
	struct memblock *list;
	phys_size_t ram_addr_end = CONFIG_SYS_SDRAM_BASE;
	phys_addr_t end_addr;
	parse_fn_t parse_fn;
	int i, count, ret;
	int bad_cnt = 0, n = 0;
	char bad_name[12];

	parse_fn = board_bidram_parse_fn();
	if (!parse_fn) {
		BIDRAM_E("Can't find dram parse fn\n");
		return 0;
	}

	list = parse_fn(&count);
	if (!list) {
		BIDRAM_E("Can't get dram banks\n");
		return 0;
	}

	if (count > CONFIG_NR_DRAM_BANKS) {
		BIDRAM_E("Too many dram banks, %d is over max: %d\n",
			 count, CONFIG_NR_DRAM_BANKS);
		return 0;
	}

	/* Initial plat_bidram */
	lmb_init(&bidram->lmb);
	INIT_LIST_HEAD(&bidram->reserved_head);
	bidram->has_init = true;

	/* Initial memory pool */
	for (i = 0; i < count; i++) {
		BIDRAM_D("Add bank[%d] start=0x%08lx, end=0x%08lx\n",
			 i, (ulong)list[i].base,
			 (ulong)list[i].base + (ulong)list[i].size);

		if (!list[i].size) {
			/* handle 4GB+ */
			if (list[i].size_u64 && n < MEM_RESV_COUNT) {
				bidram->base_u64[n] = list[i].base_u64;
				bidram->size_u64[n] = list[i].size_u64;
				n++;
			}
			continue;
		}

		/* We assume the last block gives the ram addr end */
		ram_addr_end = list[i].base + list[i].size;

		/* This is a bad dram bank? record it */
		if (i > 0) {
			end_addr = list[i - 1].base + list[i - 1].size;

			if (list[i].base != end_addr) {
				snprintf(bad_name, 12, "%s%d", "BAD_RAM.", i - 1);
				bad[bad_cnt].attr.name = strdup(bad_name);
				bad[bad_cnt].base = end_addr;
				bad[bad_cnt].size = list[i].base - end_addr;
				bad_cnt++;
				if (bad_cnt > MAX_BAD_MEMBLK) {
					BIDRAM_E("Too many bad memory blocks\n");
					return 0;
				}
			}
		}
	}

	ret = bidram_add(CONFIG_SYS_SDRAM_BASE,
			 ram_addr_end - CONFIG_SYS_SDRAM_BASE);
	if (ret) {
		BIDRAM_E("Failed to add bidram from bi_dram[%d]\n", i);
		return 0;
	}

	/* Reserve bad dram bank after bidram_add(), treat as reserved region */
	for (i = 0; i < bad_cnt; i++) {
		if (gd->flags & GD_FLG_RELOC)
			BIDRAM_R("Bad memblk%d: 0x%08lx - 0x%08lx\n",
				 i, (ulong)bad[i].base,
				 (ulong)bad[i].base + (ulong)bad[i].size);

		ret = bidram_reserve_by_name(bad[i].attr.name,
					     bad[i].base, bad[i].size);
		if (ret) {
			BIDRAM_E("Failed to add bad memblk[%d]\n", i);
			return 0;
		}
	}

	/* Reserved for board */
	ret = board_bidram_reserve(bidram);
	if (ret) {
		BIDRAM_E("Failed to reserve bidram for board\n");
		return 0;
	}

	BIDRAM_D("DRAM size: 0x%08lx\n",
		 (ulong)ram_addr_end - CONFIG_SYS_SDRAM_BASE);

#ifdef DEBUG
	bidram_dump();
#endif

	return (ram_addr_end - CONFIG_SYS_SDRAM_BASE);
}

__weak parse_fn_t board_bidram_parse_fn(void)
{
	/* please define platform specific board_bidram_parse_fn() */
	return NULL;
}

__weak int board_bidram_reserve(struct bidram *bidram)
{
	/* please define platform specific board_bidram_reserve() */
	return 0;
}

static int do_bidram_dump(cmd_tbl_t *cmdtp, int flag,
			  int argc, char *const argv[])
{
	bidram_dump();
	return 0;
}

U_BOOT_CMD(
	bidram_dump, 1, 1, do_bidram_dump,
	"Dump bidram layout",
	""
);
