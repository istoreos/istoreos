/*
 * (C) Copyright 2011 NVIDIA Corporation <www.nvidia.com>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

/* register offset */
#define COMMAND_0		0x00
#define CMD_GO			(1 << 31)
#define CMD_CLE			(1 << 30)
#define CMD_ALE			(1 << 29)
#define CMD_PIO			(1 << 28)
#define CMD_TX			(1 << 27)
#define CMD_RX			(1 << 26)
#define CMD_SEC_CMD		(1 << 25)
#define CMD_AFT_DAT_MASK	(1 << 24)
#define CMD_AFT_DAT_DISABLE	0
#define CMD_AFT_DAT_ENABLE	(1 << 24)
#define CMD_TRANS_SIZE_SHIFT	20
#define CMD_TRANS_SIZE_PAGE	8
#define CMD_A_VALID		(1 << 19)
#define CMD_B_VALID		(1 << 18)
#define CMD_RD_STATUS_CHK	(1 << 17)
#define CMD_R_BSY_CHK		(1 << 16)
#define CMD_CE7			(1 << 15)
#define CMD_CE6			(1 << 14)
#define CMD_CE5			(1 << 13)
#define CMD_CE4			(1 << 12)
#define CMD_CE3			(1 << 11)
#define CMD_CE2			(1 << 10)
#define CMD_CE1			(1 << 9)
#define CMD_CE0			(1 << 8)
#define CMD_CLE_BYTE_SIZE_SHIFT	4
enum {
	CMD_CLE_BYTES1 = 0,
	CMD_CLE_BYTES2,
	CMD_CLE_BYTES3,
	CMD_CLE_BYTES4,
};
#define CMD_ALE_BYTE_SIZE_SHIFT	0
enum {
	CMD_ALE_BYTES1 = 0,
	CMD_ALE_BYTES2,
	CMD_ALE_BYTES3,
	CMD_ALE_BYTES4,
	CMD_ALE_BYTES5,
	CMD_ALE_BYTES6,
	CMD_ALE_BYTES7,
	CMD_ALE_BYTES8
};

#define STATUS_0			0x04
#define STATUS_RBSY0			(1 << 8)

#define ISR_0				0x08
#define ISR_IS_CMD_DONE			(1 << 5)
#define ISR_IS_ECC_ERR			(1 << 4)

#define IER_0				0x0C

#define CFG_0				0x10
#define CFG_HW_ECC_MASK			(1 << 31)
#define CFG_HW_ECC_DISABLE		0
#define CFG_HW_ECC_ENABLE		(1 << 31)
#define CFG_HW_ECC_SEL_MASK		(1 << 30)
#define CFG_HW_ECC_SEL_HAMMING		0
#define CFG_HW_ECC_SEL_RS		(1 << 30)
#define CFG_HW_ECC_CORRECTION_MASK	(1 << 29)
#define CFG_HW_ECC_CORRECTION_DISABLE	0
#define CFG_HW_ECC_CORRECTION_ENABLE	(1 << 29)
#define CFG_PIPELINE_EN_MASK		(1 << 28)
#define CFG_PIPELINE_EN_DISABLE		0
#define CFG_PIPELINE_EN_ENABLE		(1 << 28)
#define CFG_ECC_EN_TAG_MASK		(1 << 27)
#define CFG_ECC_EN_TAG_DISABLE		0
#define CFG_ECC_EN_TAG_ENABLE		(1 << 27)
#define CFG_TVALUE_MASK			(3 << 24)
enum {
	CFG_TVAL4 = 0 << 24,
	CFG_TVAL6 = 1 << 24,
	CFG_TVAL8 = 2 << 24
};
#define CFG_SKIP_SPARE_MASK		(1 << 23)
#define CFG_SKIP_SPARE_DISABLE		0
#define CFG_SKIP_SPARE_ENABLE		(1 << 23)
#define CFG_COM_BSY_MASK		(1 << 22)
#define CFG_COM_BSY_DISABLE		0
#define CFG_COM_BSY_ENABLE		(1 << 22)
#define CFG_BUS_WIDTH_MASK		(1 << 21)
#define CFG_BUS_WIDTH_8BIT		0
#define CFG_BUS_WIDTH_16BIT		(1 << 21)
#define CFG_LPDDR1_MODE_MASK		(1 << 20)
#define CFG_LPDDR1_MODE_DISABLE		0
#define CFG_LPDDR1_MODE_ENABLE		(1 << 20)
#define CFG_EDO_MODE_MASK		(1 << 19)
#define CFG_EDO_MODE_DISABLE		0
#define CFG_EDO_MODE_ENABLE		(1 << 19)
#define CFG_PAGE_SIZE_SEL_MASK		(7 << 16)
enum {
	CFG_PAGE_SIZE_256	= 0 << 16,
	CFG_PAGE_SIZE_512	= 1 << 16,
	CFG_PAGE_SIZE_1024	= 2 << 16,
	CFG_PAGE_SIZE_2048	= 3 << 16,
	CFG_PAGE_SIZE_4096	= 4 << 16
};
#define CFG_SKIP_SPARE_SEL_MASK		(3 << 14)
enum {
	CFG_SKIP_SPARE_SEL_4	= 0 << 14,
	CFG_SKIP_SPARE_SEL_8	= 1 << 14,
	CFG_SKIP_SPARE_SEL_12	= 2 << 14,
	CFG_SKIP_SPARE_SEL_16	= 3 << 14
};
#define CFG_TAG_BYTE_SIZE_MASK	0x1FF

#define TIMING_0			0x14
#define TIMING_TRP_RESP_CNT_SHIFT	28
#define TIMING_TRP_RESP_CNT_MASK	(0xf << TIMING_TRP_RESP_CNT_SHIFT)
#define TIMING_TWB_CNT_SHIFT		24
#define TIMING_TWB_CNT_MASK		(0xf << TIMING_TWB_CNT_SHIFT)
#define TIMING_TCR_TAR_TRR_CNT_SHIFT	20
#define TIMING_TCR_TAR_TRR_CNT_MASK	(0xf << TIMING_TCR_TAR_TRR_CNT_SHIFT)
#define TIMING_TWHR_CNT_SHIFT		16
#define TIMING_TWHR_CNT_MASK		(0xf << TIMING_TWHR_CNT_SHIFT)
#define TIMING_TCS_CNT_SHIFT		14
#define TIMING_TCS_CNT_MASK		(3 << TIMING_TCS_CNT_SHIFT)
#define TIMING_TWH_CNT_SHIFT		12
#define TIMING_TWH_CNT_MASK		(3 << TIMING_TWH_CNT_SHIFT)
#define TIMING_TWP_CNT_SHIFT		8
#define TIMING_TWP_CNT_MASK		(0xf << TIMING_TWP_CNT_SHIFT)
#define TIMING_TRH_CNT_SHIFT		4
#define TIMING_TRH_CNT_MASK		(3 << TIMING_TRH_CNT_SHIFT)
#define TIMING_TRP_CNT_SHIFT		0
#define TIMING_TRP_CNT_MASK		(0xf << TIMING_TRP_CNT_SHIFT)

#define RESP_0				0x18

#define TIMING2_0			0x1C
#define TIMING2_TADL_CNT_SHIFT		0
#define TIMING2_TADL_CNT_MASK		(0xf << TIMING2_TADL_CNT_SHIFT)

#define CMD_REG1_0			0x20
#define CMD_REG2_0			0x24
#define ADDR_REG1_0			0x28
#define ADDR_REG2_0			0x2C

#define DMA_MST_CTRL_0			0x30
#define DMA_MST_CTRL_GO_MASK		(1 << 31)
#define DMA_MST_CTRL_GO_DISABLE		0
#define DMA_MST_CTRL_GO_ENABLE		(1 << 31)
#define DMA_MST_CTRL_DIR_MASK		(1 << 30)
#define DMA_MST_CTRL_DIR_READ		0
#define DMA_MST_CTRL_DIR_WRITE		(1 << 30)
#define DMA_MST_CTRL_PERF_EN_MASK	(1 << 29)
#define DMA_MST_CTRL_PERF_EN_DISABLE	0
#define DMA_MST_CTRL_PERF_EN_ENABLE	(1 << 29)
#define DMA_MST_CTRL_REUSE_BUFFER_MASK	(1 << 27)
#define DMA_MST_CTRL_REUSE_BUFFER_DISABLE	0
#define DMA_MST_CTRL_REUSE_BUFFER_ENABLE	(1 << 27)
#define DMA_MST_CTRL_BURST_SIZE_SHIFT	24
#define DMA_MST_CTRL_BURST_SIZE_MASK	(7 << DMA_MST_CTRL_BURST_SIZE_SHIFT)
enum {
	DMA_MST_CTRL_BURST_1WORDS	= 2 << DMA_MST_CTRL_BURST_SIZE_SHIFT,
	DMA_MST_CTRL_BURST_4WORDS	= 3 << DMA_MST_CTRL_BURST_SIZE_SHIFT,
	DMA_MST_CTRL_BURST_8WORDS	= 4 << DMA_MST_CTRL_BURST_SIZE_SHIFT,
	DMA_MST_CTRL_BURST_16WORDS	= 5 << DMA_MST_CTRL_BURST_SIZE_SHIFT
};
#define DMA_MST_CTRL_IS_DMA_DONE	(1 << 20)
#define DMA_MST_CTRL_EN_A_MASK		(1 << 2)
#define DMA_MST_CTRL_EN_A_DISABLE	0
#define DMA_MST_CTRL_EN_A_ENABLE	(1 << 2)
#define DMA_MST_CTRL_EN_B_MASK		(1 << 1)
#define DMA_MST_CTRL_EN_B_DISABLE	0
#define DMA_MST_CTRL_EN_B_ENABLE	(1 << 1)

#define DMA_CFG_A_0			0x34
#define DMA_CFG_B_0			0x38
#define FIFO_CTRL_0			0x3C
#define DATA_BLOCK_PTR_0		0x40
#define TAG_PTR_0			0x44
#define ECC_PTR_0			0x48

#define DEC_STATUS_0			0x4C
#define DEC_STATUS_A_ECC_FAIL		(1 << 1)
#define DEC_STATUS_B_ECC_FAIL		(1 << 0)

#define BCH_CONFIG_0			0xCC
#define BCH_CONFIG_BCH_TVALUE_SHIFT	4
#define BCH_CONFIG_BCH_TVALUE_MASK	(3 << BCH_CONFIG_BCH_TVALUE_SHIFT)
enum {
	BCH_CONFIG_BCH_TVAL4	= 0 << BCH_CONFIG_BCH_TVALUE_SHIFT,
	BCH_CONFIG_BCH_TVAL8	= 1 << BCH_CONFIG_BCH_TVALUE_SHIFT,
	BCH_CONFIG_BCH_TVAL14	= 2 << BCH_CONFIG_BCH_TVALUE_SHIFT,
	BCH_CONFIG_BCH_TVAL16	= 3 << BCH_CONFIG_BCH_TVALUE_SHIFT
};
#define BCH_CONFIG_BCH_ECC_MASK		(1 << 0)
#define BCH_CONFIG_BCH_ECC_DISABLE	0
#define BCH_CONFIG_BCH_ECC_ENABLE	(1 << 0)

#define BCH_DEC_RESULT_0			0xD0
#define BCH_DEC_RESULT_CORRFAIL_ERR_MASK	(1 << 8)
#define BCH_DEC_RESULT_PAGE_COUNT_MASK		0xFF

#define BCH_DEC_STATUS_BUF_0			0xD4
#define BCH_DEC_STATUS_FAIL_SEC_FLAG_MASK	0xFF000000
#define BCH_DEC_STATUS_CORR_SEC_FLAG_MASK	0x00FF0000
#define BCH_DEC_STATUS_FAIL_TAG_MASK		(1 << 14)
#define BCH_DEC_STATUS_CORR_TAG_MASK		(1 << 13)
#define BCH_DEC_STATUS_MAX_CORR_CNT_MASK	(0x1f << 8)
#define BCH_DEC_STATUS_PAGE_NUMBER_MASK		0xFF

#define LP_OPTIONS	0

struct nand_ctlr {
	u32	command;	/* offset 00h */
	u32	status;		/* offset 04h */
	u32	isr;		/* offset 08h */
	u32	ier;		/* offset 0Ch */
	u32	config;		/* offset 10h */
	u32	timing;		/* offset 14h */
	u32	resp;		/* offset 18h */
	u32	timing2;	/* offset 1Ch */
	u32	cmd_reg1;	/* offset 20h */
	u32	cmd_reg2;	/* offset 24h */
	u32	addr_reg1;	/* offset 28h */
	u32	addr_reg2;	/* offset 2Ch */
	u32	dma_mst_ctrl;	/* offset 30h */
	u32	dma_cfg_a;	/* offset 34h */
	u32	dma_cfg_b;	/* offset 38h */
	u32	fifo_ctrl;	/* offset 3Ch */
	u32	data_block_ptr;	/* offset 40h */
	u32	tag_ptr;	/* offset 44h */
	u32	resv1;		/* offset 48h */
	u32	dec_status;	/* offset 4Ch */
	u32	hwstatus_cmd;	/* offset 50h */
	u32	hwstatus_mask;	/* offset 54h */
	u32	resv2[29];
	u32	bch_config;	/* offset CCh */
	u32	bch_dec_result;	/* offset D0h */
	u32	bch_dec_status_buf;
				/* offset D4h */
};
