/*
 * (C) Copyright 2017 Rockchip Electronics Co., Ltd
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */

#ifndef __RESC_IMG_H_
#define __RESC_IMG_H_

#include <linux/list.h>

#define MAX_FILE_NAME_LEN		220
#define MAX_HASH_LEN			32
#define ROOT_COMPAT_PROP_OFFSET		0x4c	/* Property: "/compatible" */
#define DTB_SUFFIX			".dtb"

struct resource_file {
	char		name[MAX_FILE_NAME_LEN];
	char		hash[MAX_HASH_LEN];
	uint32_t	hash_size;
	uint32_t	f_offset;	/* Sector offset */
	uint32_t	f_size;		/* Bytes */
	struct list_head link;
	struct list_head dtbs;
	/* Sector base of resource when ram=false, byte base when ram=true */
	uint32_t	rsce_base;
	bool		ram;
};

extern struct list_head entrys_head;
extern struct list_head entrys_dtbs_head;

/*
 * resource_image_check_header - check resource image header
 *
 * @rsce_hdr: resource file hdr
 *
 * return 0 on header okay, otherwise failed
 */
int resource_image_check_header(void *rsce_hdr);

/*
 * resource_create_ram_list - create resource file list by data from memory
 *
 * @dev_desc: blk dev descritpion
 * @rsce_hdr: resource file hdr
 *
 * return 0 on header okay, otherwise failed
 */
int resource_create_ram_list(struct blk_desc *dev_desc, void *rsce_hdr);

/*
 * rockchip_read_resource_file - read file from resource partition
 *
 * @buf: destination buf to store file data
 * @name: file name
 * @offset: blocks offset in the file, 1 block = 512 bytes
 * @len: the size(by bytes) of file to read.
 *
 * return negative num on failed, otherwise the file size
 */
int rockchip_read_resource_file(void *buf, const char *name, int offset, int len);

/*
 * rockchip_read_resource_dtb() - read dtb file
 *
 * @fdt_addr: destination buf to store dtb file
 * @hash: hash value buffer
 * @hash_size: hash value length
 */
int rockchip_read_resource_dtb(void *fdt_addr, char **hash, int *hash_size);

/*
 * resource_init_list - init resource list of android image from storage
 */
int resource_init_list(void);

/*
 * resource_replace_entry - replace resource entry, override if find exist one
 */
int resource_replace_entry(const char *f_name, uint32_t base,
			   uint32_t f_offset, uint32_t f_size);

/*
 * resource_read_logo_bmps() - read logo bmp from "logo" partition
 */
int resource_read_logo_bmps(void);

/*
 * resource_read_hwid_dtb() - read hwid dtb
 */
struct resource_file *resource_read_hwid_dtb(void);

/*
 * resource_is_empty() - return if resource is empty
 */
int resource_is_empty(void);

/*
 * resource_traverse_init_list() - traverse all image(android/fit/uimage)
 */
int resource_traverse_init_list(void);

/*
 * board_resource_dtb_accepted() - check if this dtb is accepted
 *
 * return 0 if not accepted, otherwise accepted.
 */
int board_resource_dtb_accepted(char *dtb_name);

#endif
