/* SPDX-License-Identifier:     GPL-2.0+ */
/*
 * (C) Copyright 2019 Rockchip Electronics Co., Ltd
 */

#ifndef _MTD_BLK_H_
#define _MTD_BLK_H_

/**
 * mtd_part_parse() - Parse the block part info to mtd part info
 *
 * @return mtd part info. If fail, return NULL
 */
char *mtd_part_parse(struct blk_desc *dev_desc);
int mtd_blk_map_table_init(struct blk_desc *desc,
			   loff_t offset,
			   size_t length);
void mtd_blk_map_partitions(struct blk_desc *desc);
void mtd_blk_map_fit(struct blk_desc *desc, ulong sector, void *fit);

#endif
