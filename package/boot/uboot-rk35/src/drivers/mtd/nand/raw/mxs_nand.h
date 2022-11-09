/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * NXP GPMI NAND flash driver
 *
 * Copyright (C) 2018 Toradex
 * Authors:
 * Stefan Agner <stefan.agner@toradex.com>
 */

#include <linux/mtd/mtd.h>
#include <asm/cache.h>
#include <nand.h>
#include <asm/mach-imx/dma.h>

/**
 * @gf_len:                   The length of Galois Field. (e.g., 13 or 14)
 * @ecc_strength:             A number that describes the strength of the ECC
 *                            algorithm.
 * @ecc_chunk_size:           The size, in bytes, of a single ECC chunk. Note
 *                            the first chunk in the page includes both data and
 *                            metadata, so it's a bit larger than this value.
 * @ecc_chunk_count:          The number of ECC chunks in the page,
 * @block_mark_byte_offset:   The byte offset in the ECC-based page view at
 *                            which the underlying physical block mark appears.
 * @block_mark_bit_offset:    The bit offset into the ECC-based page view at
 *                            which the underlying physical block mark appears.
 */
struct bch_geometry {
	unsigned int  gf_len;
	unsigned int  ecc_strength;
	unsigned int  ecc_chunk_size;
	unsigned int  ecc_chunk_count;
	unsigned int  block_mark_byte_offset;
	unsigned int  block_mark_bit_offset;
};

struct mxs_nand_info {
	struct nand_chip chip;
	struct udevice *dev;
	unsigned int	max_ecc_strength_supported;
	bool		use_minimum_ecc;
	int		cur_chip;

	uint32_t	cmd_queue_len;
	uint32_t	data_buf_size;
	struct bch_geometry bch_geometry;

	uint8_t		*cmd_buf;
	uint8_t		*data_buf;
	uint8_t		*oob_buf;

	uint8_t		marking_block_bad;
	uint8_t		raw_oob_mode;

	struct mxs_gpmi_regs *gpmi_regs;
	struct mxs_bch_regs *bch_regs;

	/* Functions with altered behaviour */
	int		(*hooked_read_oob)(struct mtd_info *mtd,
				loff_t from, struct mtd_oob_ops *ops);
	int		(*hooked_write_oob)(struct mtd_info *mtd,
				loff_t to, struct mtd_oob_ops *ops);
	int		(*hooked_block_markbad)(struct mtd_info *mtd,
				loff_t ofs);

	/* DMA descriptors */
	struct mxs_dma_desc	**desc;
	uint32_t		desc_index;
};

int mxs_nand_init_ctrl(struct mxs_nand_info *nand_info);
int mxs_nand_init_spl(struct nand_chip *nand);
int mxs_nand_setup_ecc(struct mtd_info *mtd);
