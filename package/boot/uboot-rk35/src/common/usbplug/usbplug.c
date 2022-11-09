/*
 * (C) Copyright 2020 Rockchip Electronics Co., Ltd.
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */

#include <common.h>
#include <mapmem.h>
#include <malloc.h>
#include <dm/root.h>

DECLARE_GLOBAL_DATA_PTR;

static void initr_reloc(void)
{
	/* tell others: relocation done */
	gd->flags |= GD_FLG_RELOC | GD_FLG_FULL_MALLOC_INIT;
}

#ifdef CONFIG_ARM
static void initr_caches(void)
{
	icache_enable();
	dcache_enable();
}
#endif

static void initr_malloc(void)
{
	ulong malloc_start;

	/* The malloc area is immediately below the monitor copy in DRAM */
	malloc_start = gd->relocaddr - TOTAL_MALLOC_LEN;
	mem_malloc_init((ulong)map_sysmem(malloc_start, TOTAL_MALLOC_LEN),
			TOTAL_MALLOC_LEN);
}

#ifdef CONFIG_DM
static int initr_dm(void)
{
	/* Save the pre-reloc driver model and start a new one */
	gd->dm_root_f = gd->dm_root;
	gd->dm_root = NULL;

	return dm_init_and_scan(false);
}
#endif

/*
 * The below functions are all __weak declared.
 */
int dram_init(void)
{
#if CONFIG_SYS_MALLOC_LEN > SZ_64M
	"CONFIG_SYS_MALLOC_LEN is over 64MB"
#endif
	gd->ram_size = SZ_64M; /* default */

	gd->bd->bi_dram[0].start = CONFIG_SYS_SDRAM_BASE;
	gd->bd->bi_dram[0].size  = gd->ram_size;

	return 0;
}

/* Refers to common/board_r.c */
void board_init_r(gd_t *new_gd, ulong dest_addr)
{
	initr_reloc();
#ifdef CONFIG_ARM
	initr_caches();
#endif
	initr_malloc();
#ifdef CONFIG_DM
	initr_dm();
#endif
	/* Setup chipselects, entering usb-plug mode */
	board_init();

	hang();
}

