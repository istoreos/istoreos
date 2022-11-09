/*
 * Copyright (C) 2017 Rockchip Electronics Co., Ltd.
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */

#include <common.h>
#include <bidram.h>
#include <dm.h>
#include <ram.h>
#include <asm/io.h>
#include <asm/arch-rockchip/param.h>
#include <asm/arch-rockchip/rk_atags.h>
#include <asm/arch-rockchip/sdram.h>
#include <dm/uclass-internal.h>

DECLARE_GLOBAL_DATA_PTR;
#define PARAM_DRAM_INFO_OFFSET 0x2000000
#define TRUST_PARAMETER_OFFSET    (34 * 1024 * 1024)

size_t rockchip_sdram_size(phys_addr_t reg)
{
	u32 rank, cs0_col, bk, cs0_row, cs1_row, bw, row_3_4;
	size_t chipsize_mb = 0;
	size_t size_mb = 0;
	u32 ch;
	u32 cs1_col = 0;
	u32 bg = 0;
	u32 dbw, dram_type;
	u32 sys_reg = readl(reg);
	u32 sys_reg1 = readl(reg + 4);
	u32 ch_num = 1 + ((sys_reg >> SYS_REG_NUM_CH_SHIFT)
		       & SYS_REG_NUM_CH_MASK);

	dram_type = (sys_reg >> SYS_REG_DDRTYPE_SHIFT) & SYS_REG_DDRTYPE_MASK;
	debug("%s %x %x\n", __func__, (u32)reg, sys_reg);
	for (ch = 0; ch < ch_num; ch++) {
		rank = 1 + (sys_reg >> SYS_REG_RANK_SHIFT(ch) &
			SYS_REG_RANK_MASK);
		cs0_col = 9 + (sys_reg >> SYS_REG_COL_SHIFT(ch) & SYS_REG_COL_MASK);
		cs1_col = cs0_col;
		bk = 3 - ((sys_reg >> SYS_REG_BK_SHIFT(ch)) & SYS_REG_BK_MASK);
		if ((sys_reg1 >> SYS_REG1_VERSION_SHIFT &
		     SYS_REG1_VERSION_MASK) == 0x2) {
			cs1_col = 9 + (sys_reg1 >> SYS_REG1_CS1_COL_SHIFT(ch) &
				  SYS_REG1_CS1_COL_MASK);
			if (((sys_reg1 >> SYS_REG1_EXTEND_CS0_ROW_SHIFT(ch) &
			    SYS_REG1_EXTEND_CS0_ROW_MASK) << 2) + (sys_reg >>
			    SYS_REG_CS0_ROW_SHIFT(ch) &
			    SYS_REG_CS0_ROW_MASK) == 7)
				cs0_row = 12;
			else
				cs0_row = 13 + (sys_reg >>
					  SYS_REG_CS0_ROW_SHIFT(ch) &
					  SYS_REG_CS0_ROW_MASK) +
					  ((sys_reg1 >>
					  SYS_REG1_EXTEND_CS0_ROW_SHIFT(ch) &
					  SYS_REG1_EXTEND_CS0_ROW_MASK) << 2);
			if (((sys_reg1 >> SYS_REG1_EXTEND_CS1_ROW_SHIFT(ch) &
			    SYS_REG1_EXTEND_CS1_ROW_MASK) << 2) + (sys_reg >>
			    SYS_REG_CS1_ROW_SHIFT(ch) &
			    SYS_REG_CS1_ROW_MASK) == 7)
				cs1_row = 12;
			else
				cs1_row = 13 + (sys_reg >>
					  SYS_REG_CS1_ROW_SHIFT(ch) &
					  SYS_REG_CS1_ROW_MASK) +
					  ((sys_reg1 >>
					  SYS_REG1_EXTEND_CS1_ROW_SHIFT(ch) &
					  SYS_REG1_EXTEND_CS1_ROW_MASK) << 2);
		}
		else {
			cs0_row = 13 + (sys_reg >> SYS_REG_CS0_ROW_SHIFT(ch) &
				SYS_REG_CS0_ROW_MASK);
			cs1_row = 13 + (sys_reg >> SYS_REG_CS1_ROW_SHIFT(ch) &
				SYS_REG_CS1_ROW_MASK);
		}
		bw = (2 >> ((sys_reg >> SYS_REG_BW_SHIFT(ch)) &
			SYS_REG_BW_MASK));
		row_3_4 = sys_reg >> SYS_REG_ROW_3_4_SHIFT(ch) &
			SYS_REG_ROW_3_4_MASK;
		if (dram_type == DDR4) {
			dbw = (sys_reg >> SYS_REG_DBW_SHIFT(ch)) &
				SYS_REG_DBW_MASK;
			bg = (dbw == 2) ? 2 : 1;
		}
		chipsize_mb = (1 << (cs0_row + cs0_col + bk + bg + bw - 20));

		if (rank > 1)
			chipsize_mb += chipsize_mb >> ((cs0_row - cs1_row) +
				       (cs0_col - cs1_col));
		if (row_3_4)
			chipsize_mb = chipsize_mb * 3 / 4;
		size_mb += chipsize_mb;
		if (rank > 1)
			debug("rank %d cs0_col %d cs1_col %d bk %d cs0_row %d\
			       cs1_row %d bw %d row_3_4 %d\n",
			       rank, cs0_col, cs1_col, bk, cs0_row,
			       cs1_row, bw, row_3_4);
		else
			debug("rank %d cs0_col %d bk %d cs0_row %d\
                               bw %d row_3_4 %d\n",
                               rank, cs0_col, bk, cs0_row,
                               bw, row_3_4);
	}

	/* Handle 4GB size, or else size will be 0 after <<20 in 32bit system */
	if (size_mb > (SDRAM_MAX_SIZE >> 20))
		size_mb = (SDRAM_MAX_SIZE >> 20);

	return (size_t)size_mb << 20;
}

static unsigned int get_ddr_os_reg(void)
{
	u32 os_reg = 0;

#if defined(CONFIG_ROCKCHIP_PX30)
	os_reg = readl(0xff010208);
#elif defined(CONFIG_ROCKCHIP_RK3328)
	os_reg = readl(0xff1005d0);
#elif defined(CONFIG_ROCKCHIP_RK3399)
	os_reg = readl(0xff320308);
#elif defined(CONFIG_ROCKCHIP_RK322X)
	os_reg = readl(0x110005d0);
#elif defined(CONFIG_ROCKCHIP_RK3368)
	os_reg = readl(0xff738208);
#elif defined(CONFIG_ROCKCHIP_RK3288)
	os_reg = readl(0x20004048);
#elif defined(CONFIG_ROCKCHIP_RK3036)
	os_reg = readl(0x200081cc);
#elif defined(CONFIG_ROCKCHIP_RK3308)
	os_reg = readl(0xff000508);
#elif defined(CONFIG_ROCKCHIP_RK1808)
	os_reg = readl(0xfe020208);
#else
	printf("unsupported chip type, get page size fail\n");
#endif

	return os_reg;
}

unsigned int get_page_size(void)
{
	u32 os_reg;
	u32 col, bw;
	int page_size;

	os_reg = get_ddr_os_reg();
	if (!os_reg)
		return 0;

	col = 9 + (os_reg >> SYS_REG_COL_SHIFT(0) & SYS_REG_COL_MASK);
	bw = (2 >> ((os_reg >> SYS_REG_BW_SHIFT(0)) & SYS_REG_BW_MASK));
	page_size = 1u << (col + bw);

	return page_size;
}

unsigned int get_ddr_bw(void)
{
	u32 os_reg;
	u32 bw = 2;

	os_reg = get_ddr_os_reg();
	if (os_reg)
		bw = 2 >> ((os_reg >> SYS_REG_BW_SHIFT(0)) & SYS_REG_BW_MASK);
	return bw;
}

#if defined(CONFIG_SPL_FRAMEWORK) || !defined(CONFIG_SPL_OF_PLATDATA)
int dram_init_banksize(void)
{
#ifdef CONFIG_BIDRAM
	bidram_gen_gd_bi_dram();
#else
	param_simple_parse_ddr_mem(1);
#endif
	return 0;
}

int dram_init(void)
{
#ifdef CONFIG_BIDRAM
	gd->ram_size = bidram_get_ram_size();
#else
	gd->ram_size = param_simple_parse_ddr_mem(0);
#endif
	if (!gd->ram_size)
		return -ENOMEM;

	return 0;
}
#endif

ulong board_get_usable_ram_top(ulong total_size)
{
	unsigned long top = CONFIG_SYS_SDRAM_BASE + SDRAM_MAX_SIZE;

	return (gd->ram_top > top) ? top : gd->ram_top;
}

int rockchip_setup_ddr_param(struct ddr_param *info)
{
	u32 i;
	struct ddr_param *dinfo = (struct ddr_param *)(CONFIG_SYS_SDRAM_BASE +
					PARAM_DRAM_INFO_OFFSET);

	dinfo->count = info->count;
	for (i = 0; i < (info->count * 2); i++)
		dinfo->para[i] = info->para[i];

	return 0;
}
