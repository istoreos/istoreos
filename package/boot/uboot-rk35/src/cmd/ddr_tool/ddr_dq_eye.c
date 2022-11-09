// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (C) 2021 Rockchip Electronics Co., Ltd.
 */

#if defined(CONFIG_ROCKCHIP_RV1126) || defined(CONFIG_ROCKCHIP_RK3568)

#include <common.h>
#include <console.h>
#include <asm/io.h>
#include <asm/arch-rockchip/sdram_common.h>
#if defined(CONFIG_ROCKCHIP_RV1126)
#include <asm/arch-rockchip/sdram_rv1126.h>
#elif defined(CONFIG_ROCKCHIP_RK3568)
#include <asm/arch-rockchip/sdram_rk3568.h>
#endif

#define __version__	"0.0.6"

#define PRINT_LENGTH	64
#ifndef PRINT_STEP
#define PRINT_STEP	1
#endif
#define PRINT_RANGE	((PRINT_LENGTH) * (PRINT_STEP))

struct print_border {
	u16 far_left;
	u16 far_right;
};

struct rw_trn_result result;

static void calc_print_border(struct cs_rw_trn_result *result, u8 byte_en,
			      u16 deskew_num, struct print_border *print_border)
{
	u16 far_left = deskew_num;
	u16 far_right = 0;
	u16 mid;
	u8 dqs;
	u8 dq;

	if (deskew_num <= PRINT_RANGE) {
		print_border->far_left = 0;
		print_border->far_right = deskew_num - 1;

		return;
	}

	for (dqs = 0; dqs < BYTE_NUM; dqs++) {
		if ((byte_en & BIT(dqs)) == 0)
			continue;

		for (dq = 0; dq < 8; dq++) {
			if (result->dqs[dqs].dq_min[dq] < far_left)
				far_left = result->dqs[dqs].dq_min[dq];
			if (result->dqs[dqs].dq_max[dq] > far_right)
				far_right = result->dqs[dqs].dq_max[dq];
		}
	}

	if (far_right - far_left + 1 > PRINT_RANGE) {
		print_border->far_left = far_left & ~((u16)(PRINT_STEP * 4 - 1));
		print_border->far_right = far_right | (PRINT_STEP * 4 - 1);
	} else {
		mid = (far_left + far_right) / 2;
		if (mid < PRINT_RANGE / 2) {
			print_border->far_left = 0;
			print_border->far_right = PRINT_RANGE - 1;
		} else if (mid > deskew_num - PRINT_RANGE / 2) {
			print_border->far_left = deskew_num - PRINT_RANGE;
			print_border->far_right = deskew_num - 1;
		} else {
			print_border->far_left = mid - PRINT_RANGE / 2;
			print_border->far_right = mid + PRINT_RANGE / 2 - 1;
		}
	}
}

static void print_title_bar(struct print_border *print_border)
{
	int i;

	printf("     ");
	for (i = print_border->far_left; i < print_border->far_right;
	     i += PRINT_STEP * 4)
		printf("%-4d", i);
	printf("	Margin_L Sample Margin_R Width    DQS\n");
}

static void print_ddr_dq_eye(struct fsp_rw_trn_result *fsp_result, u8 cs,
			     u8 byte_en, u16 width_ref,
			     struct print_border *print_border)
{
	u16 sample;
	u16 min;
	u16 max;
	u16 dq_eye_width;
	u8 dqs;
	u8 dq;
	int i;
	struct cs_rw_trn_result *result = &fsp_result->cs[cs];

	for (dqs = 0; dqs < BYTE_NUM; dqs++) {
		if ((byte_en & BIT(dqs)) == 0)
			continue;

		for (dq = 0; dq < 8; dq++) {
			sample = fsp_result->min_val +
				 result->dqs[dqs].dq_deskew[dq];
			min = result->dqs[dqs].dq_min[dq];
			max = result->dqs[dqs].dq_max[dq];
			dq_eye_width = max >= min ? max - min + 1 : 0;

			printf("DQ%-2d ", dqs * 8 + dq);
			for (i = print_border->far_left;
			     i <= print_border->far_right; i += PRINT_STEP) {
				if (i / PRINT_STEP == sample / PRINT_STEP)
					printf("|");
				else if (i / PRINT_STEP >= min / PRINT_STEP &&
					 i / PRINT_STEP <= max / PRINT_STEP)
					printf("*");
				else
					printf("-");
			}

			printf("	%5d%8d%8d",
			       sample > min ? sample - min : 0, sample,
			       max > sample ? max - sample : 0);
			if (dq_eye_width >= width_ref)
				printf("%8d%8d\n", dq_eye_width,
				       fsp_result->min_val +
				       result->dqs[dqs].dqs_deskew);
			else
				printf("    [%3d]%7d\n", dq_eye_width,
				       fsp_result->min_val +
				       result->dqs[dqs].dqs_deskew);
		}
	}
	printf("\n");
}

static u16 cs_eye_width_min(struct cs_rw_trn_result *result, u8 byte_en,
			    u16 deskew_num)
{
	u16 min;
	u16 max;
	u16 dq_eye_width;
	u16 cs_eye_width = deskew_num;
	u8 dqs;
	u8 dq;

	for (dqs = 0; dqs < BYTE_NUM; dqs++) {
		if ((byte_en & BIT(dqs)) == 0)
			continue;

		for (dq = 0; dq < 8; dq++) {
			min = result->dqs[dqs].dq_min[dq];
			max = result->dqs[dqs].dq_max[dq];
			dq_eye_width = max >= min ? max - min + 1 : 0;
			if (cs_eye_width > dq_eye_width)
				cs_eye_width = dq_eye_width;
		}
	}

	return cs_eye_width;
}

static int do_ddr_dq_eye(cmd_tbl_t *cmdtp, int flag, int argc,
			 char * const argv[])
{
	unsigned long freq_mhz;

	u32 ddr_type;
	u16 rd_width = RD_DESKEW_NUM;
	u16 wr_width = WR_DESKEW_NUM;
	u16 cs_eye_width;
	u16 rd_width_ref;
	u16 wr_width_ref;
	u16 width_ref_mhz;
	u8 fsp = 0;
	u8 cs;
	int i;
	struct print_border print_border;

	printf("Rockchip DDR DQ Eye Tool v" __version__ "\n");

#if defined(CONFIG_ROCKCHIP_RV1126)
	ddr_type = (readl(0xfe020208) >> 13) & 0x7;
#elif defined(CONFIG_ROCKCHIP_RK3568)
	ddr_type = ((readl(0xfdc2020c)  & (0x3 << 12)) >> 9) |
		   ((readl(0xfdc20208) >> 13) & 0x7);
#else
	printf("Rockchip DDR DQ Eye Tool only support RK356x and RV1126 now.\n");
	return CMD_RET_FAILURE;
#endif

	if (readl(RW_TRN_RESULT_ADDR) == DDR_DQ_EYE_FLAG) {
		memcpy(&result, (void *)(RW_TRN_RESULT_ADDR), sizeof(result));
	} else {
		printf("Fail to get data of DDR DQ eye.\n");
		printf("Please update the Loader.\n");
		return CMD_RET_FAILURE;
	}

	if (argc == 1) {
		/* use the max freq if no arg */
		for (i = 0; i < FSP_NUM; i++) {
			if (result.fsp_mhz[i] > result.fsp_mhz[fsp])
				fsp = i;
		}
	} else if (argc > 1) {
		if (strict_strtoul(argv[1], 0, &freq_mhz) < 0)
			return CMD_RET_USAGE;

		if (freq_mhz >= 0 && freq_mhz < FSP_NUM) {
			/* when user enter the fsp rather than the freq_mhz */
			fsp = (u8)freq_mhz;
		} else {
			for (fsp = 0; fsp < FSP_NUM; fsp++)
				if (result.fsp_mhz[fsp] == freq_mhz ||
				    result.fsp_mhz[fsp] == (u16)(freq_mhz / MHZ))
					break;

			if (fsp >= FSP_NUM)
				return CMD_RET_USAGE;
		}
	} else {
		return CMD_RET_FAILURE;
	}

	printf("DDR type: ");
	switch (ddr_type) {
	case LPDDR4X:
		if (result.fsp_mhz[fsp] <
			(LP4_WIDTH_REF_MHZ_L + LP4_WIDTH_REF_MHZ_H) / 2) {
			rd_width_ref = LP4_RD_WIDTH_REF_L;
			wr_width_ref = LP4_WR_WIDTH_REF_L;
			width_ref_mhz = LP4_WIDTH_REF_MHZ_L;
		} else {
			rd_width_ref = LP4_RD_WIDTH_REF_H;
			wr_width_ref = LP4_WR_WIDTH_REF_H;
			width_ref_mhz = LP4_WIDTH_REF_MHZ_H;
		}
		printf("LPDDR4X");
		break;
	case LPDDR4:
		if (result.fsp_mhz[fsp] <
			(LP4_WIDTH_REF_MHZ_L + LP4_WIDTH_REF_MHZ_H) / 2) {
			rd_width_ref = LP4_RD_WIDTH_REF_L;
			wr_width_ref = LP4_WR_WIDTH_REF_L;
			width_ref_mhz = LP4_WIDTH_REF_MHZ_L;
		} else {
			rd_width_ref = LP4_RD_WIDTH_REF_H;
			wr_width_ref = LP4_WR_WIDTH_REF_H;
			width_ref_mhz = LP4_WIDTH_REF_MHZ_H;
		}
		printf("LPDDR4");
		break;
	case LPDDR3:
		if (result.fsp_mhz[fsp] <
			(LP4_WIDTH_REF_MHZ_L + LP4_WIDTH_REF_MHZ_H) / 2) {
			rd_width_ref = LP3_RD_WIDTH_REF_L;
			wr_width_ref = LP3_WR_WIDTH_REF_L;
			width_ref_mhz = LP3_WIDTH_REF_MHZ_L;
		} else {
			rd_width_ref = LP3_RD_WIDTH_REF_H;
			wr_width_ref = LP3_WR_WIDTH_REF_H;
			width_ref_mhz = LP3_WIDTH_REF_MHZ_H;
		}
		printf("LPDDR3");
		break;
	case DDR4:
		if (result.fsp_mhz[fsp] <
			(DDR4_WIDTH_REF_MHZ_L + DDR4_WIDTH_REF_MHZ_H) / 2) {
			rd_width_ref = DDR4_RD_WIDTH_REF_L;
			wr_width_ref = DDR4_WR_WIDTH_REF_L;
			width_ref_mhz = DDR4_WIDTH_REF_MHZ_L;
		} else {
			rd_width_ref = DDR4_RD_WIDTH_REF_H;
			wr_width_ref = DDR4_WR_WIDTH_REF_H;
			width_ref_mhz = DDR4_WIDTH_REF_MHZ_H;
		}
		printf("DDR4");
		break;
	case DDR3:
	default:
		if (result.fsp_mhz[fsp] <
			(DDR3_WIDTH_REF_MHZ_L + DDR3_WIDTH_REF_MHZ_H) / 2) {
			rd_width_ref = DDR3_RD_WIDTH_REF_L;
			wr_width_ref = DDR3_WR_WIDTH_REF_L;
			width_ref_mhz = DDR3_WIDTH_REF_MHZ_L;
		} else {
			rd_width_ref = DDR3_RD_WIDTH_REF_H;
			wr_width_ref = DDR3_WR_WIDTH_REF_H;
			width_ref_mhz = DDR3_WIDTH_REF_MHZ_H;
		}
		printf("DDR3");
		break;
	} /* switch (ddr_type) */
	printf("\n");

	for (cs = 0; cs < result.cs_num; cs++) {
		calc_print_border(&result.rd_fsp[fsp].cs[cs], result.byte_en,
				  RD_DESKEW_NUM, &print_border);
		printf("CS%d %dMHz read DQ eye:\n", cs, result.fsp_mhz[fsp]);
		print_title_bar(&print_border);
		print_ddr_dq_eye(&result.rd_fsp[fsp], cs, result.byte_en,
				 rd_width_ref, &print_border);
		cs_eye_width = cs_eye_width_min(&result.rd_fsp[fsp].cs[cs],
						result.byte_en, RD_DESKEW_NUM);
		if (rd_width > cs_eye_width)
			rd_width = cs_eye_width;

		printf("CS%d %dMHz write DQ eye:\n", cs, result.fsp_mhz[fsp]);
		calc_print_border(&result.wr_fsp[fsp].cs[cs], result.byte_en,
				  WR_DESKEW_NUM, &print_border);
		print_title_bar(&print_border);
		print_ddr_dq_eye(&result.wr_fsp[fsp], cs, result.byte_en,
				 wr_width_ref, &print_border);
		cs_eye_width = cs_eye_width_min(&result.wr_fsp[fsp].cs[cs],
						result.byte_en, WR_DESKEW_NUM);
		if (wr_width > cs_eye_width)
			wr_width = cs_eye_width;
	}
	printf("DQ eye width min: %d(read), %d(write)\n", rd_width, wr_width);
	printf("DQ eye width reference: %d(read), %d(write) in %dMHz\n",
	       rd_width_ref, wr_width_ref, width_ref_mhz);
	if (rd_width < rd_width_ref || wr_width < wr_width_ref)
		printf("ERROR: DQ eye width may be unreliable, please check!\n");

	return CMD_RET_SUCCESS;
}

U_BOOT_CMD(ddr_dq_eye,	2,	1,	do_ddr_dq_eye,
	   "Rockchip DDR DQ Eye Tool\n",
	   "arg1: DDR freq in MHz, null for the max freq.\n"
	   "example:\n"
	   "	ddr_dq_eye 1056: show the DDR DQ eye in 1056MHz."
);

#endif /* if defined(CONFIG_ROCKCHIP_RV1126) || defined(CONFIG_ROCKCHIP_RK3568) */
