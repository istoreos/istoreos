/*
 * Copyright (c) 2020 Rockchip Electronics Co., Ltd
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */

#include <common.h>
#include <blk.h>
#include <boot_rkimg.h>
#include <dm.h>
#include <errno.h>
#include <image.h>
#include <malloc.h>
#include <mtd_blk.h>
#include <part.h>
#include <spl.h>
#include <spl_ab.h>
#include <spl_rkfw.h>
#include <asm/u-boot.h>
#include <dm/device-internal.h>
#include <linux/compiler.h>

static struct blk_desc *find_rknand_device(int dev_num)
{
	struct udevice *dev;
	struct blk_desc *desc;
	int ret;

	ret = blk_find_device(IF_TYPE_RKNAND, dev_num, &dev);
	if (ret)
		return NULL;

	ret = device_probe(dev);
	if (ret) {
		debug("RKNAND Device %d not found\n", dev_num);
		return NULL;
	}

	desc = dev_get_uclass_platdata(dev);
	if (!desc)
		return NULL;

	return desc;
}

static ulong h_spl_load_read(struct spl_load_info *load, ulong sector,
			     ulong count, void *buf)
{
	return blk_dread(load->dev, sector, count, buf);
}

static int spl_rknand_load_image(struct spl_image_info *spl_image,
				 struct spl_boot_device *bootdev)
{
	lbaint_t image_sector = CONFIG_RKNAND_BLK_U_BOOT_OFFS;
	struct image_header *header;
	struct spl_load_info load;
	struct blk_desc *desc;
	int ret = -1;

	desc = find_rknand_device(0);
	if (!desc)
		return -ENODEV;

	load.dev = desc;
	load.priv = NULL;
	load.filename = NULL;
	load.bl_len = desc->blksz;
	load.read = h_spl_load_read;

#ifdef CONFIG_SPL_LIBDISK_SUPPORT
	disk_partition_t info;

	ret = part_get_info_by_name(desc, PART_UBOOT, &info);
	if (ret > 0)
		image_sector = info.start;
#endif

	if (IS_ENABLED(CONFIG_SPL_LOAD_FIT)) {
		header = (struct image_header *)(CONFIG_SYS_TEXT_BASE -
					 sizeof(struct image_header));
		ret = blk_dread(desc, image_sector, 1, header);
		if (ret != 1)
			return -ENODEV;

#ifdef CONFIG_SPL_FIT_IMAGE_MULTIPLE
		if (image_get_magic(header) == FDT_MAGIC ||
		    CONFIG_SPL_FIT_IMAGE_MULTIPLE > 1) {
#else
		if (image_get_magic(header) == FDT_MAGIC) {
#endif
			ret = spl_load_simple_fit(spl_image, &load,
						  image_sector,
						  header);
		}
	}

	if (!ret)
		return 0;

#ifdef CONFIG_SPL_LOAD_RKFW
	ret = spl_load_rkfw_image(spl_image, &load);
#endif

	return ret;
}

SPL_LOAD_IMAGE_METHOD("RKNAND", 0, BOOT_DEVICE_RKNAND, spl_rknand_load_image);
