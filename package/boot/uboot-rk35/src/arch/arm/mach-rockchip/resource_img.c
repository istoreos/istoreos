/*
 * (C) Copyright 2017 Rockchip Electronics Co., Ltd
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */
#include <common.h>
#include <adc.h>
#include <android_ab.h>
#include <android_bootloader.h>
#include <android_image.h>
#include <boot_rkimg.h>
#include <bmp_layout.h>
#include <malloc.h>
#include <asm/io.h>
#include <asm/unaligned.h>
#include <dm/ofnode.h>
#include <linux/list.h>
#include <asm/arch-rockchip/fit.h>
#include <asm/arch-rockchip/uimage.h>
#include <asm/arch-rockchip/resource_img.h>

DECLARE_GLOBAL_DATA_PTR;

#define PART_RESOURCE			"resource"
#define RESOURCE_MAGIC			"RSCE"
#define RESOURCE_MAGIC_SIZE		4
#define RESOURCE_VERSION		0
#define CONTENT_VERSION			0
#define ENTRY_TAG			"ENTR"
#define ENTRY_TAG_SIZE			4
#define MAX_FILE_NAME_LEN		220
#define MAX_HASH_LEN			32
#define DEFAULT_DTB_FILE		"rk-kernel.dtb"

/*
 *         resource image structure
 * ----------------------------------------------
 * |                                            |
 * |    header  (1 block)                       |
 * |                                            |
 * ---------------------------------------------|
 * |                      |                     |
 * |    entry0  (1 block) |                     |
 * |                      |                     |
 * ------------------------                     |
 * |                      |                     |
 * |    entry1  (1 block) | contents (n blocks) |
 * |                      |                     |
 * ------------------------                     |
 * |    ......            |                     |
 * ------------------------                     |
 * |                      |                     |
 * |    entryn  (1 block) |                     |
 * |                      |                     |
 * ----------------------------------------------
 * |                                            |
 * |    file0  (x blocks)                       |
 * |                                            |
 * ----------------------------------------------
 * |                                            |
 * |    file1  (y blocks)                       |
 * |                                            |
 * ----------------------------------------------
 * |                   ......                   |
 * |---------------------------------------------
 * |                                            |
 * |    filen  (z blocks)                       |
 * |                                            |
 * ----------------------------------------------
 */

/**
 * struct resource_image_header
 *
 * @magic: should be "RSCE"
 * @version: resource image version, current is 0
 * @c_version: content version, current is 0
 * @blks: the size of the header ( 1 block = 512 bytes)
 * @c_offset: contents offset(by block) in the image
 * @e_blks: the size(by block) of the entry in the contents
 * @e_num: numbers of the entrys.
 */

struct resource_img_hdr {
	char		magic[4];
	uint16_t	version;
	uint16_t	c_version;
	uint8_t		blks;
	uint8_t		c_offset;
	uint8_t		e_blks;
	uint32_t	e_nums;
};

struct resource_entry {
	char		tag[4];
	char		name[MAX_FILE_NAME_LEN];
	char		hash[MAX_HASH_LEN];
	uint32_t	hash_size;
	uint32_t	f_offset;	/* Sector offset */
	uint32_t	f_size;		/* Bytes */
};

LIST_HEAD(entrys_head);
LIST_HEAD(entrys_dtbs_head);

__weak int board_resource_dtb_accepted(char *dtb_name)
{
	return 1;
}

int resource_image_check_header(void *rsce_hdr)
{
	struct resource_img_hdr *hdr = rsce_hdr;
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

static int add_file_to_list(struct resource_entry *entry, int rsce_base, bool ram)
{
	struct resource_file *file;

	if (memcmp(entry->tag, ENTRY_TAG, ENTRY_TAG_SIZE)) {
		debug("invalid entry tag\n");
		return -ENOENT;
	}

	file = malloc(sizeof(*file));
	if (!file) {
		debug("out of memory\n");
		return -ENOMEM;
	}

	strcpy(file->name, entry->name);
	file->rsce_base = rsce_base;
	file->f_offset = entry->f_offset;
	file->f_size = entry->f_size;
	file->hash_size = entry->hash_size;
	file->ram = ram;
	memcpy(file->hash, entry->hash, entry->hash_size);
	INIT_LIST_HEAD(&file->dtbs);
	list_add_tail(&file->link, &entrys_head);
	if (strstr(file->name, DTB_SUFFIX) && board_resource_dtb_accepted(file->name))
		list_add_tail(&file->dtbs, &entrys_dtbs_head);
	debug("ENTRY: addr: %p, name: %18s, base: 0x%08x, offset: 0x%08x, size: 0x%08x\n",
	      entry, file->name, file->rsce_base, file->f_offset, file->f_size);

	return 0;
}

int resource_replace_entry(const char *f_name, uint32_t base,
			   uint32_t f_offset, uint32_t f_size)
{
	struct resource_entry *entry;
	struct resource_file *file;
	struct list_head *node;

	if (!f_name || !f_size)
		return -EINVAL;

	entry = calloc(1, sizeof(*entry));
	if (!entry)
		return -ENOMEM;

	strcpy(entry->tag, ENTRY_TAG);
	strcpy(entry->name, f_name);
	entry->f_offset = f_offset;
	entry->f_size = f_size;
	entry->hash_size = 0;

	/* Delete exist entry, then add this new */
	list_for_each(node, &entrys_head) {
		file = list_entry(node, struct resource_file, link);
		if (!strcmp(file->name, entry->name)) {
			list_del(&file->link);
			list_del(&file->dtbs);
			free(file);
			break;
		}
	}

	add_file_to_list(entry, base, false);
	free(entry);

	return 0;
}

int resource_create_ram_list(struct blk_desc *dev_desc, void *rsce_hdr)
{
	struct resource_img_hdr *hdr = rsce_hdr;
	struct resource_entry *entry;
	int e_num, size;
	void *data;
	int ret = 0;

	if (resource_image_check_header(hdr)) {
		ret = -EINVAL;
		goto out;
	}

	list_del_init(&entrys_head);
	list_del_init(&entrys_dtbs_head);
	data = (void *)((ulong)hdr + hdr->c_offset * dev_desc->blksz);
	for (e_num = 0; e_num < hdr->e_nums; e_num++) {
		size = e_num * hdr->e_blks * dev_desc->blksz;
		entry = (struct resource_entry *)(data + size);
		add_file_to_list(entry, (ulong)hdr, true);
	}
out:
	resource_read_logo_bmps();

	return ret;
}

static int resource_create_list(struct blk_desc *dev_desc, int rsce_base)
{
	struct resource_img_hdr *hdr;
	struct resource_entry *entry;
	int blknum, e_num;
	void *data = NULL;
	int ret = 0;
	int size;

	hdr = memalign(ARCH_DMA_MINALIGN, dev_desc->blksz);
	if (!hdr)
		return -ENOMEM;

	if (blk_dread(dev_desc, rsce_base, 1, hdr) != 1) {
		printf("Failed to read resource hdr\n");
		ret = -EIO;
		goto err;
	}

	if (resource_image_check_header(hdr)) {
		if (fdt_check_header(hdr)) {
			printf("No valid resource or dtb file\n");
			ret = -EINVAL;
			goto err;
		} else {
			free(hdr);
			return resource_replace_entry(DEFAULT_DTB_FILE, rsce_base,
						      0, fdt_totalsize(hdr));
		}
	}

	blknum = hdr->e_blks * hdr->e_nums;
	data = memalign(ARCH_DMA_MINALIGN, blknum * dev_desc->blksz);
	if (!data) {
		ret = -ENOMEM;
		goto err;
	}

	if (blk_dread(dev_desc, rsce_base + hdr->c_offset,
		      blknum, data) != blknum) {
		printf("Failed to read resource entries\n");
		ret = -EIO;
		goto err;
	}

	/*
	 * Add all file into resource file list, and load what we want from
	 * storage when we really need it.
	 */
	for (e_num = 0; e_num < hdr->e_nums; e_num++) {
		size = e_num * hdr->e_blks * dev_desc->blksz;
		entry = (struct resource_entry *)(data + size);
		add_file_to_list(entry, rsce_base, false);
	}

err:
	if (data)
		free(data);
	if (hdr)
		free(hdr);

	resource_read_logo_bmps();

	return ret;
}

static int read_dtb_from_android(struct blk_desc *dev_desc,
				 struct andr_img_hdr *hdr,
				 ulong rsce_base)
{
	ulong dtb_offset = 0;
	ulong dtb_size = 0;

	if (!hdr || hdr->header_version <= 1) {
		return 0;
	} else if (hdr->header_version == 2) {
		dtb_offset += hdr->page_size;
		dtb_offset += ALIGN(hdr->kernel_size, hdr->page_size);
		dtb_offset += ALIGN(hdr->ramdisk_size, hdr->page_size);
		dtb_offset += ALIGN(hdr->recovery_dtbo_size, hdr->page_size) +
			      ALIGN(hdr->second_size, hdr->page_size);
		dtb_size = hdr->dtb_size;
	} else if (hdr->header_version >= 3) {
		ulong vendor_boot_hdr_size = (hdr->header_version == 3) ?
			VENDOR_BOOT_HDRv3_SIZE : VENDOR_BOOT_HDRv4_SIZE;

		dtb_offset += ALIGN(vendor_boot_hdr_size,
				    hdr->vendor_page_size) +
			      ALIGN(hdr->vendor_ramdisk_size,
				    hdr->vendor_page_size);
		dtb_size = hdr->dtb_size;
	}

	if (!dtb_size)
		return 0;

	/*
	 * boot_img_hdr_v234 feature.
	 *
	 * If dtb position is present, replace the old with new one if
	 * we don't need to verify DTB hash from resource.img file entry.
	 */
	dtb_offset = DIV_ROUND_UP(dtb_offset, dev_desc->blksz);
	env_update("bootargs", "androidboot.dtb_idx=0");

	return 0;
}

static int get_resource_base_sector(struct blk_desc *dev_desc,
				    struct andr_img_hdr **ret_hdr)
{
	disk_partition_t part;
	int rsce_base = 0;
#ifdef CONFIG_ANDROID_BOOT_IMAGE
	struct andr_img_hdr *hdr;
	u32 os_ver = 0, os_lvl;
	const char *part_boot = PART_BOOT;

	/*
	 * Anyway, we must read android hdr firstly from boot/recovery partition
	 * to get the 'os_version' for android_bcb_msg_sector_offset(), in order
	 * to confirm BCB message offset of *MISC* partition.
	 */
#ifdef CONFIG_ANDROID_AB
	part_boot = ab_can_find_recovery_part() ? PART_RECOVERY : PART_BOOT;
#endif

	if (part_get_info_by_name(dev_desc, part_boot, &part) < 0)
		goto resource_part;

	hdr = populate_andr_img_hdr(dev_desc, &part);
	if (hdr) {
		os_ver = hdr->os_version >> 11;
		os_lvl = hdr->os_version & ((1U << 11) - 1);
		if (os_ver)
			gd->bd->bi_andr_version = hdr->os_version;
	}

#ifndef CONFIG_ANDROID_AB
	/* Get boot mode from misc and read if recovery mode */
	if (rockchip_get_boot_mode() == BOOT_MODE_RECOVERY) {
		if (hdr)
			free(hdr);

		if (part_get_info_by_name(dev_desc, PART_RECOVERY, &part) < 0)
			goto resource_part;

		hdr = populate_andr_img_hdr(dev_desc, &part);
		if (!hdr)
			goto resource_part;
	}
#endif
	/* If Android v012, getting resource from second position ! */
	if (hdr) {
		if (os_ver)
			printf("Android %u.%u, Build %u.%u, v%d\n",
			       (os_ver >> 14) & 0x7F, (os_ver >> 7) & 0x7F,
			       (os_lvl >> 4) + 2000, os_lvl & 0x0F,
			       hdr->header_version);
		*ret_hdr = hdr;
		if (hdr->header_version < 3) {
			rsce_base = part.start * dev_desc->blksz;
			rsce_base += hdr->page_size;
			rsce_base += ALIGN(hdr->kernel_size, hdr->page_size);
			rsce_base += ALIGN(hdr->ramdisk_size, hdr->page_size);
			rsce_base = DIV_ROUND_UP(rsce_base, dev_desc->blksz);
			goto finish;
		}
	}
resource_part:
#endif
	/* resource partition */
	if (part_get_info_by_name(dev_desc, PART_RESOURCE, &part) < 0) {
		printf("No resource partition\n");
		return -ENODEV;
	} else {
		rsce_base = part.start;
	}
#ifdef CONFIG_ANDROID_BOOT_IMAGE
finish:
#endif
	printf("Found DTB in %s part\n", part.name);

	return rsce_base;
}

/*
 * There are: logo/battery pictures and dtb file in the resource image by default.
 *
 * This function does:
 *
 * 1. Get resource image base sector from: boot/recovery(AOSP) > resource(RK)
 * 2. Create resource files list(addition: add logo bmps)
 * 3. Add dtb from android v2 dtb pos, override the old one from resource file
 */
int resource_init_list(void)
{
	struct andr_img_hdr *hdr = NULL;
	struct blk_desc *dev_desc;
	int rsce_base;

	dev_desc = rockchip_get_bootdev();
	if (!dev_desc) {
		printf("No dev_desc!\n");
		return -ENODEV;
	}

	rsce_base = get_resource_base_sector(dev_desc, &hdr);
	if (rsce_base > 0) {
		if (resource_create_list(dev_desc, rsce_base))
			printf("Failed to create resource list\n");
	}

	/* override the resource dtb with android dtb if need */
	return read_dtb_from_android(dev_desc, hdr, rsce_base);
}

int resource_is_empty(void)
{
	return list_empty(&entrys_head);
}

static struct resource_file *get_file_info(const char *name)
{
	struct resource_file *file;
	struct list_head *node;

	if (list_empty(&entrys_head)) {
		if (resource_init_list())
			return NULL;
	}

	list_for_each(node, &entrys_head) {
		file = list_entry(node, struct resource_file, link);
		if (!strcmp(file->name, name))
			return file;
	}

	return NULL;
}

/*
 * read file from resource partition
 * @buf: destination buf to store file data;
 * @name: file name
 * @offset: blocks offset in the file, 1 block = 512 bytes
 * @len: the size(by bytes) of file to read.
 */
int rockchip_read_resource_file(void *buf, const char *name, int offset, int len)
{
	struct resource_file *file;
	struct blk_desc *dev_desc;
	int ret = 0;
	int blks;
	ulong src;

	file = get_file_info(name);
	if (!file) {
		printf("No file: %s\n", name);
		return -ENOENT;
	}

	dev_desc = rockchip_get_bootdev();
	if (!dev_desc) {
		printf("No dev_desc!\n");
		return -ENODEV;
	}

	if (len <= 0 || len > file->f_size)
		len = file->f_size;

	if (file->ram) {
		src = file->rsce_base +
			(file->f_offset + offset) * dev_desc->blksz;
		memcpy(buf, (char *)src, len);
		ret = len;
	} else {
		blks = DIV_ROUND_UP(len, dev_desc->blksz);
		ret = blk_dread(dev_desc,
				file->rsce_base + file->f_offset + offset,
				blks, buf);
		ret = (ret != blks) ? -EIO : len;
	}

	return ret;
}

static struct resource_file *get_default_dtb(void)
{
	struct resource_file *target_file = NULL;
	struct resource_file *file;
	struct list_head *node;
	int num = 0;

	if (list_empty(&entrys_head)) {
		if (resource_init_list())
			return NULL;
	}

	list_for_each(node, &entrys_dtbs_head) {
		num++;
		file = list_entry(node, struct resource_file, dtbs);
		if (strcmp(file->name, DEFAULT_DTB_FILE))
			target_file = file;
	}

	/*
	 * two possible case:
	 *	case 1. rk-kernel.dtb only
	 *	case 2. targe_file(s) + rk-kernel.dtb(maybe they are the same),
	 *		use (last)target_file as result one.
	 */
	if (num > 2)
		printf("Error: find duplicate(%d) dtbs\n", num);

	return target_file ? : get_file_info(DEFAULT_DTB_FILE);
}

int rockchip_read_resource_dtb(void *fdt_addr, char **hash, int *hash_size)
{
	struct resource_file *file = NULL;
	int ret;

#ifdef CONFIG_ROCKCHIP_HWID_DTB
	file = resource_read_hwid_dtb();
#endif
	/* If no dtb matches hardware id(GPIO/ADC), use the default */
	if (!file)
		file = get_default_dtb();

	if (!file)
		return -ENODEV;

	ret = rockchip_read_resource_file(fdt_addr, file->name, 0, 0);
	if (ret < 0)
		return ret;

	if (fdt_check_header(fdt_addr))
		return -EBADF;

	*hash = file->hash;
	*hash_size = file->hash_size;
	printf("DTB: %s\n", file->name);

	return 0;
}

int resource_traverse_init_list(void)
{
	if (!resource_is_empty())
		return 0;

#ifdef CONFIG_ROCKCHIP_FIT_IMAGE
	if (!fit_image_init_resource())
		return 0;
#endif
#ifdef CONFIG_ROCKCHIP_UIMAGE
	if (!uimage_init_resource())
		return 0;
#endif
	/* Android image is default supported within resource core */

	return 0;
}

static int do_dump_resource(cmd_tbl_t *cmdtp, int flag,
			    int argc, char *const argv[])
{
	struct resource_file *file;
	struct list_head *node;

	printf("Resources:\n");
	list_for_each(node, &entrys_head) {
		file = list_entry(node, struct resource_file, link);
		printf("	%s: 0x%08x(sector), 0x%08x(bytes)\n",
		       file->name, file->rsce_base + file->f_offset, file->f_size);
	}

#ifdef CONFIG_ROCKCHIP_HWID_DTB
	printf("DTBs:\n");
	list_for_each(node, &entrys_dtbs_head) {
		file = list_entry(node, struct resource_file, dtbs);
		printf("	%s: 0x%08x(sector),0x%08x(bytes)\n",
		       file->name, file->rsce_base + file->f_offset, file->f_size);
	}
#endif
	return 0;
}

U_BOOT_CMD(
	dump_resource, 1, 1, do_dump_resource,
	"dump resource list",
	""
);

