// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (c) 2020 Fuzhou Rockchip Electronics Co., Ltd
 */

#include <common.h>
#include <linux/list.h>
#include <asm/arch-rockchip/spl_resource_img.h>

int spl_resource_image_check_header(const struct resource_img_hdr *hdr)
{
	int ret;

	ret = memcmp(RESOURCE_MAGIC, hdr->magic, RESOURCE_MAGIC_SIZE);
	if (ret) {
		debug("bad resource image magic: %s\n",
		      hdr->magic ? hdr->magic : "none");
		ret = -EINVAL;
	}

	debug("resource image header:\n");
	debug("magic:%s\n", hdr->magic);
	debug("version:%d\n", hdr->version);
	debug("c_version:%d\n", hdr->c_version);
	debug("blks:%d\n", hdr->blks);
	debug("c_offset:%d\n", hdr->c_offset);
	debug("e_blks:%d\n", hdr->e_blks);
	debug("e_num:%d\n", hdr->e_nums);

	return ret;
}

struct resource_entry *spl_resource_image_get_dtb_entry(const struct
							resource_img_hdr *hdr)
{
	int i;
	struct resource_entry *entry = NULL;

	if (!hdr)
		return NULL;

	for (i = 0; i < hdr->e_nums; i++) {
		entry = (struct resource_entry *)((char *)hdr
				+ (hdr->blks + hdr->e_blks * i) * 512);
		if (!memcmp(entry->name, DEFAULT_DTB_FILE, strlen(DEFAULT_DTB_FILE)))
			break;
	}

	return entry;
}
