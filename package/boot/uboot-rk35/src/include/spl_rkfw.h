/* SPDX-License-Identifier:     GPL-2.0+ */
/*
 * (C) Copyright 2019 Rockchip Electronics Co., Ltd
 */

#ifndef _SPL_RKFW_H_
#define _SPL_RKFW_H_

#include <spl.h>

#define LOADER_HARD_STR			"LOADER"
#ifdef CONFIG_SPL_ATF
#define TBOOT_HEAD_TAG			0x58334c42 /* 'B', 'L', '3', 'X' */
#else
#define TBOOT_HEAD_TAG			"TOS   "
#endif

#define BL30_IMAGE_NAME			"bl30.bin" /* SCP Firmware BL3-0 */
#define BL31_IMAGE_NAME			"bl31.bin" /* EL3 Runtime Firmware BL31 */
#define BL32_IMAGE_NAME			"bl32.bin" /* Secure Payload BL32 (Trusted OS) */

#define UUID_SCP_FIRMWARE_BL30		0x30334c42 /* "BL30" */
#define UUID_EL3_RUNTIME_FIRMWARE_BL31	0x31334c42 /* "BL31" */
#define UUID_SECURE_PAYLOAD_BL32	0x32334c42 /* "BL32" */

/* Signature size, unit is byte */
#define SIGNATURE_SIZE			256
#define MAX_BL_CODE_NUM			6
#define LOADER_MAGIC_SIZE		8
#define LOADER_HASH_SIZE		32

/* Special value used to verify platform parameters from BL2 to BL3-1 */
#define RK_BL31_PLAT_PARAM_VAL		0x0f1e2d3c4b5a6978ULL

#ifdef CONFIG_MTD_NAND_CORE
#define RKFW_RETRY_SECTOR_SIZE		256
#define RKFW_RETRY_SECTOR_TIMES		32
#else
#define RKFW_RETRY_SECTOR_SIZE		1024
#define RKFW_RETRY_SECTOR_TIMES		8
#endif

struct s_fip_name_id {
	const char *name;
	const u32 id;
};

typedef struct tag_tboot_header_2k {
	u32 tag;
	u32 version;
	u32 flags;
	u32 size;
	u32 reserved1[4];
	u32 rsa_n[64];
	u32 rsa_e[64];
	u32 rsa_c[64];
	u32 reserved2[312];
} tboot_header_2k, *ptboot_header_2k;

typedef struct tag_tboot_header {
	u32 tag;
	u32 version;
	u32 flags;
	u32 size;
	u32 reserved[4];
	u32 rsa_n[64];
	u32 rsa_e[64];
	u32 rsa_c[64];
} tboot_header, *ptboot_header;

typedef struct tag_boot_component {
	u32 component_id;
	u32 storage_addr;
	u32 image_size;
	u32 reserved;
} boot_component, *pboot_component;

typedef struct tag_component_data {
	u32 hash_data[8];
	u32 load_addr;
	u32 reserved[3];
} component_data, *pcomponent_data;

typedef struct tag_tboot_entry {
	boot_component component;
	component_data compdata;
} tboot_entry, *ptboot_entry;

typedef struct tag_second_loader_hdr {
	unsigned char magic[LOADER_MAGIC_SIZE];
	unsigned int version;
	unsigned int reserved0;
	unsigned int loader_load_addr;		/* physical load addr ,default is 0x60000000 */
	unsigned int loader_load_size;		/* size in bytes */
	unsigned int crc32;			/* crc32 */
	unsigned int hash_len;			/* 20 or 32 , 0 is no hash */
	unsigned char hash[LOADER_HASH_SIZE];	/* sha */
	unsigned int js_hash;			/* js hsah */
	unsigned char reserved[1024-32-32-4];
	unsigned int sign_tag;			/* 0x4E474953, 'N' 'G' 'I' 'S' */
	unsigned int sign_len;			/* 256 */
	unsigned char rsa_hash[256];
	unsigned char reserved2[2048-1024-256-8];
} second_loader_hdr;				/* Size:2K */

/**
 * spl_load_rkfw_image - Load rockchip image(trust and U-Boot) and jump to bl31.
 */
int spl_load_rkfw_image(struct spl_image_info *spl_image,
			struct spl_load_info *info);
#endif
