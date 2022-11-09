/*
 * (C) Copyright 2021 Rockchip Electronics Co., Ltd
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */
#include <common.h>
#include <adc.h>
#include <boot_rkimg.h>
#include <bmp_layout.h>
#include <malloc.h>
#include <asm/io.h>
#include <asm/unaligned.h>
#include <asm/arch-rockchip/resource_img.h>
#include <dm/ofnode.h>

static int read_bmp(struct blk_desc *dev_desc, const char *name,
		    disk_partition_t *part, uint32_t offset,
		    uint32_t *size)
{
	struct bmp_header *header;
	u32 blk_offset;
	u32 filesz;
	int ret;

	blk_offset = DIV_ROUND_UP(offset, dev_desc->blksz);
	header = memalign(ARCH_DMA_MINALIGN, dev_desc->blksz);
	if (!header) {
		ret = -ENOMEM;
		goto out;
	}

	if (blk_dread(dev_desc, part->start + blk_offset, 1, header) != 1) {
		ret = -EIO;
		goto out;
	}

	if (header->signature[0] != 'B' || header->signature[1] != 'M') {
		ret = -EINVAL;
		goto out;
	}

	filesz = get_unaligned_le32(&header->file_size);
	ret = resource_replace_entry(name, part->start, blk_offset, filesz);
	if (!ret) {
		printf("LOGO: %s\n", name);
		if (size)
			*size = filesz;
	}
out:
	free(header);

	return ret;
}

/*
 * Add logo.bmp and logo_kernel.bmp from "logo" parititon
 *
 * Provide a "logo" partition for user to store logo.bmp and
 * logo_kernel.bmp, so that the user can update them from
 * kernel or user-space dynamically.
 *
 * "logo" partition layout, do not change order:
 *
 *   |----------------------| 0x00
 *   | raw logo.bmp	    |
 *   |----------------------| N*512-byte aligned
 *   | raw logo_kernel.bmp  |
 *   |----------------------|
 *
 * N: the sector count of logo.bmp
 *
 * How to generate:
 * 	cat logo.bmp > logo.img && truncate -s %512 logo.img && cat logo_kernel.bmp >> logo.img
 */
int resource_read_logo_bmps(void)
{
	struct blk_desc *dev_desc;
	disk_partition_t part;
	u32 filesz;

	dev_desc = rockchip_get_bootdev();
	if (!dev_desc) {
		printf("No dev_desc!\n");
		return -ENODEV;
	}

	if (part_get_info_by_name(dev_desc, PART_LOGO, &part) < 0)
		return -ENODEV;

	if (!read_bmp(dev_desc, "logo.bmp", &part, 0, &filesz))
		read_bmp(dev_desc, "logo_kernel.bmp", &part, filesz, NULL);

	return 0;
}

