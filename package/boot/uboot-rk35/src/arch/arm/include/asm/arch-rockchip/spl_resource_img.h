/* SPDX-License-Identifier:     GPL-2.0+ */
/*
 * (C) Copyright 2020 Rockchip Electronics Co., Ltd
 */

#ifndef _SPL_RESOURCE_IMG_H_
#define _SPL_RESOURCE_IMG_H_

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
 * @e_num: numbers of the entries.
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
	uint32_t	f_offset;
	uint32_t	f_size;
};

int spl_resource_image_check_header(const struct resource_img_hdr *hdr);

struct resource_entry *
	spl_resource_image_get_dtb_entry(const struct resource_img_hdr *hdr);

#endif
