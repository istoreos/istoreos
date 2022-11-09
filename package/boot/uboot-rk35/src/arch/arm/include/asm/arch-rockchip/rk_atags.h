/* SPDX-License-Identifier:     GPL-2.0+ */
/*
 * (C) Copyright 2018 Rockchip Electronics Co., Ltd
 *
 */

#ifndef __RK_ATAGS_H_
#define __RK_ATAGS_H_

/* Tag magic */
#define ATAG_CORE		0x54410001
#define ATAG_NONE		0x00000000

#define ATAG_SERIAL		0x54410050
#define ATAG_BOOTDEV		0x54410051
#define ATAG_DDR_MEM		0x54410052
#define ATAG_TOS_MEM		0x54410053
#define ATAG_RAM_PARTITION	0x54410054
#define ATAG_ATF_MEM		0x54410055
#define ATAG_PUB_KEY		0x54410056
#define ATAG_SOC_INFO		0x54410057
#define ATAG_BOOT1_PARAM	0x54410058
#define ATAG_MAX		0x544100ff

/* Tag size and offset */
#define ATAGS_SIZE		(0x2000)	/* 8K */
#define ATAGS_OFFSET		(0x200000 - ATAGS_SIZE)/* [2M-8K, 2M] */

/* Tag sdram position!! */
#define ATAGS_PHYS_BASE		(CONFIG_SYS_SDRAM_BASE + ATAGS_OFFSET)

#ifndef ATAGS_PHYS_BASE
"ERROR: ATAGS_PHYS_BASE is not defined!!"
#endif

/* tag_bootdev.devtype */
#define BOOT_TYPE_UNKNOWN	0
#define BOOT_TYPE_NAND		(1 << 0)
#define BOOT_TYPE_EMMC		(1 << 1)
#define BOOT_TYPE_SD0		(1 << 2)
#define BOOT_TYPE_SD1		(1 << 3)
#define BOOT_TYPE_SPI_NOR	(1 << 4)
#define BOOT_TYPE_SPI_NAND	(1 << 5)
#define BOOT_TYPE_RAM		(1 << 6)
#define BOOT_TYPE_MTD_BLK_NAND	(1 << 7)
#define BOOT_TYPE_MTD_BLK_SPI_NAND	(1 << 8)
#define BOOT_TYPE_MTD_BLK_SPI_NOR	(1 << 9)
#define BOOT_TYPE_SATA		(1 << 10)
#define BOOT_TYPE_PCIE		(1 << 11)

/* define sd card function */
#define SD_UNKNOWN_CARD		0
#define SD_UPDATE_CARD		1

/* tag_serial.m_mode */
#define SERIAL_M_MODE_M0	0x0
#define SERIAL_M_MODE_M1	0x1
#define SERIAL_M_MODE_M2	0x2

/* tag_soc_info.flags */
#define SOC_FLAGS_ET00		0x45543030
#define SOC_FLAGS_ET01		0x45543031
#define SOC_FLAGS_ET02		0x45543032

/* pub key programmed magic */
#define PUBKEY_FUSE_PROGRAMMED	0x4B415352

/*
 * boot1p.param[2] for ATF/OPTEE. The fields:
 *
 * [31:12]: reserved
 * [4:0]: boot cpu hwid.
 */
#define B1P2_BOOT_CPU_MASK	0x00000fff

/* tag_ddr_mem.flags */
#define DDR_MEM_FLG_EXT_TOP	1

struct tag_serial {
	u32 version;
	u32 enable;
	u64 addr;
	u32 baudrate;
	u32 m_mode;
	u32 id;
	u32 reserved[2];
	u32 hash;
} __packed;

struct tag_bootdev {
	u32 version;
	u32 devtype;
	u32 devnum;
	u32 mode;
	u32 sdupdate;
	u32 reserved[6];
	u32 hash;
} __packed;

struct tag_ddr_mem {
	u32 count;
	u32 version;
	u64 bank[20];
	u32 flags;
	u32 data[2];
	u32 hash;
} __packed;

struct tag_tos_mem {
	u32 version;
	struct {
		char name[8];
		u64 phy_addr;
		u32 size;
		u32 flags;
	} tee_mem;

	struct {
		char name[8];
		u64 phy_addr;
		u32 size;
		u32 flags;
	} drm_mem;

	u64 reserved[7];
	u32 reserved1;
	u32 hash;
} __packed;

struct tag_atf_mem {
	u32 version;
	u64 phy_addr;
	u32 size;
	u32 flags;
	u32 reserved[2];
	u32 hash;
} __packed;

struct tag_pub_key {
	u32 version;
	u32 len;
	u8  data[768];	/* u32 rsa_n[64], rsa_e[64], rsa_c[64] */
	u32 flag;
	u32 reserved[5];
	u32 hash;
} __packed;

struct tag_ram_partition {
	u32 version;
	u32 count;
	u32 reserved[4];

	struct {
		char name[16];
		u64 start;
		u64 size;
	} part[6];

	u32 reserved1[3];
	u32 hash;
} __packed;

struct tag_soc_info {
	u32 version;
	u32 name;	/* Hex: 0x3288, 0x3399... */
	u32 flags;
	u32 reserved[6];
	u32 hash;
} __packed;

struct tag_boot1p {
	u32 version;
	u32 param[8];
	u32 reserved[4];
	u32 hash;
} __packed;

struct tag_core {
	u32 flags;
	u32 pagesize;
	u32 rootdev;
} __packed;

struct tag_header {
	u32 size;	/* bytes = size * 4 */
	u32 magic;
} __packed;

/* Must be 4 bytes align */
struct tag {
	struct tag_header hdr;
	union {
		struct tag_core		core;
		struct tag_serial	serial;
		struct tag_bootdev	bootdev;
		struct tag_ddr_mem	ddr_mem;
		struct tag_tos_mem	tos_mem;
		struct tag_ram_partition ram_part;
		struct tag_atf_mem	atf_mem;
		struct tag_pub_key	pub_key;
		struct tag_soc_info	soc;
		struct tag_boot1p	boot1p;
	} u;
} __aligned(4);

#define tag_next(t)	((struct tag *)((u32 *)(t) + (t)->hdr.size))
#define tag_size(type)	((sizeof(struct tag_header) + sizeof(struct type)) >> 2)
#define for_each_tag(t, base)		\
	for (t = base; t->hdr.size; t = tag_next(t))
/*
 * Destroy atags
 *
 * first pre-loader who creates atags must call it before atags_set_tag(),
 * because atags_set_tag() may detect last valid and existence ATAG_CORE
 * tag in memory and lead a wrong setup, that is not what we expect.
 */
void atags_destroy(void);

/*
 * atags_set_tag - set tag data
 *
 * @magic: tag magic, i.e. ATAG_SERIAL, ATAG_BOOTDEV, ....
 * @tagdata: core data of struct, i.e. struct tag_serial/tag_bootdev ...
 *
 * return: 0 on success, others failed.
 */
int atags_set_tag(u32 magic, void *tagdata);

/*
 * atags_get_tag - get tag by tag magic
 *
 * @magic: tag magic, i.e. ATAG_SERIAL, ATAG_BOOTDEV, ...
 *
 * return: NULL on failed, otherwise return the tag that we want.
 */
struct tag *atags_get_tag(u32 magic);

/*
 * atags_is_available - check if atags is available, used for second or
 *			later pre-loaders.
 *
 * return: 0 is not available, otherwise available.
 */
int atags_is_available(void);

/*
 * atags_overflow - check if atags is overflow
 *
 * return: 0 if not overflow, otherwise overflow.
 */
int atags_overflow(struct tag *t);

/*
 * atags_bad_magic - check if atags magic is invalid.
 *
 * return: 1 if invalid, otherwise valid.
 */
int atags_bad_magic(u32 magic);

#ifdef CONFIG_SPL_BUILD
/*
 * get_bootdev_by_brom_bootsource
 *
 * @magic: void
 *
 * return: boootdev, else 0 fail.
 */
int get_bootdev_by_brom_bootsource(void);

/*
 * atags_set_bootdev_by_brom_bootsource
 *
 * @magic: void
 *
 * return: 0 success, others fail.
 */
int atags_set_bootdev_by_brom_bootsource(void);

/*
 * get_bootdev_by_spl_bootdevice
 *
 * @bootdevice
 *
 * return: boootdev, else -ENODEV fail.
 */
int get_bootdev_by_spl_bootdevice(int bootdevice);

/*
 * atags_set_bootdev_by_spl_bootdevice
 *
 * @bootdevice
 *
 * return: 0 success, others fail.
 */
int atags_set_bootdev_by_spl_bootdevice(int bootdevice);

/*
 * atags_set_pub_key
 *
 * @data: public key data
 * @len: public key len
 * @flag: indicate the pulic key hash is burned or not
 *
 * return: 0 success, others fail.
 */
int atags_set_pub_key(void *data, int len, int flag);
#endif

#if CONFIG_IS_ENABLED(TINY_FRAMEWORK) &&		\
	!CONFIG_IS_ENABLED(LIBGENERIC_SUPPORT) &&	\
	!CONFIG_IS_ENABLED(USE_ARCH_MEMSET)
void *memset(void *s, int c, size_t count);
#endif

#if CONFIG_IS_ENABLED(TINY_FRAMEWORK) &&		\
	!CONFIG_IS_ENABLED(LIBGENERIC_SUPPORT) &&	\
	!CONFIG_IS_ENABLED(USE_ARCH_MEMCPY)
void *memcpy(void *dest, const void *src, size_t count);
#endif

#endif
