/*
 * (C) Copyright 2021 Rockchip Electronics Co., Ltd
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */
#include <common.h>
#include <boot_rkimg.h>
#include <div64.h>
#include <dfu.h>
#include <errno.h>
#include <linux/mtd/mtd.h>
#include <malloc.h>
#include <part.h>

static int dfu_write_medium_mtd(struct dfu_entity *dfu,	u64 offset, void *buf, long *len)
{
	struct blk_desc *dev_desc;
	u64 block_start, block_len;
	int ret = -ENODEV;

	switch (dfu->layout) {
	case DFU_RAW_ADDR:
		/* if buf == NULL return total size of the area */
		if (!buf) {
			*len = dfu->data.nand.size;
			return 0;
		}

		dev_desc = rockchip_get_bootdev();
		if (!dev_desc) {
			printf("%s: dev_desc is NULL!\n", __func__);
			return -ENODEV;
		}

		/* in case of ubi partition, erase rest of the partition */
		if (dfu->data.mtd.ubi && !offset) {
			block_start = dfu->data.mtd.start >> 9;
			block_len = dfu->data.mtd.size >> 9;

			ret = blk_derase(dev_desc, block_start, block_len);
			if (ret != 0)
				printf("Failure erase: %d\n", ret);
		}

		block_start = (dfu->data.mtd.start + offset) >> 9;
		block_len = (*len) >> 9;

		ret = blk_dwrite(dev_desc, block_start, block_len, buf);
		if (ret == block_len)
			ret = 0;
		break;
	default:
		printf("%s: Layout (%s) not (yet) supported!\n", __func__,
		       dfu_get_layout(dfu->layout));
	}

	return ret;
}

static int dfu_get_medium_size_mtd(struct dfu_entity *dfu, u64 *size)
{
	*size = dfu->data.mtd.size;

	return 0;
}

static int dfu_read_medium_mtd(struct dfu_entity *dfu, u64 offset, void *buf, long *len)
{
	struct blk_desc *dev_desc;
	u64 block_start, block_len;
	int ret = -ENODEV;

	switch (dfu->layout) {
	case DFU_RAW_ADDR:
		/* if buf == NULL return total size of the area */
		if (!buf) {
			*len = dfu->data.nand.size;
			return 0;
		}

		dev_desc = rockchip_get_bootdev();
		if (!dev_desc) {
			printf("%s: dev_desc is NULL!\n", __func__);
			return -ENODEV;
		}

		block_start = (dfu->data.mtd.start + offset) >> 9;
		block_len = (*len) >> 9;

		ret = blk_dread(dev_desc, block_start, block_len, buf);
		if (ret == block_len)
			ret = 0;
		break;
	default:
		printf("%s: Layout (%s) not (yet) supported!\n", __func__,
		       dfu_get_layout(dfu->layout));
	}

	return ret;
}

static int dfu_flush_medium_mtd(struct dfu_entity *dfu)
{
	return 0;
}

unsigned int dfu_polltimeout_mtd(struct dfu_entity *dfu)
{
	/*
	 * Currently, Poll Timeout != 0 is only needed on nand
	 * ubi partition, as the not used sectors need an erase
	 */
	if (dfu->data.mtd.ubi)
		return DFU_MANIFEST_POLL_TIMEOUT;

	return DFU_DEFAULT_POLL_TIMEOUT;
}

int dfu_fill_entity_mtd(struct dfu_entity *dfu, char *devstr, char *s)
{
	struct blk_desc *dev_desc;
	disk_partition_t dfu_part;
	char *st;

	dfu->data.mtd.ubi = 0;
	dfu->dev_type = DFU_DEV_MTD;
	st = strsep(&s, " ");

	if (!strcmp(st, "raw") || !strcmp(st, "rawubi")) {
		dfu->layout = DFU_RAW_ADDR;
		dfu->data.mtd.start = simple_strtoul(s, &s, 16);
		s++;
		dfu->data.mtd.size = simple_strtoul(s, &s, 16);
		if (!strcmp(st, "rawubi"))
			dfu->data.mtd.ubi = 1;
	} else if ((!strcmp(st, "part")) || (!strcmp(st, "partubi"))) {
		dev_desc = rockchip_get_bootdev();
		if (!dev_desc) {
			printf("%s: dev_desc is NULL!\n", __func__);
			return -ENODEV;
		}
		dfu->layout = DFU_RAW_ADDR;
		if (part_get_info_by_name(dev_desc, s, &dfu_part) < 0)
			return -EIO;

		dfu->data.mtd.start = dfu_part.start << 9;
		dfu->data.mtd.size = dfu_part.size << 9;
		if (!strcmp(st, "partubi"))
			dfu->data.mtd.ubi = 1;
	} else {
		printf("%s: Memory layout (%s) not supported!\n", __func__, st);
		return -1;
	}

	dfu->get_medium_size = dfu_get_medium_size_mtd;
	dfu->read_medium = dfu_read_medium_mtd;
	dfu->write_medium = dfu_write_medium_mtd;
	dfu->flush_medium = dfu_flush_medium_mtd;
	dfu->poll_timeout = dfu_polltimeout_mtd;

	/* initial state */
	dfu->inited = 0;

	return 0;
}
