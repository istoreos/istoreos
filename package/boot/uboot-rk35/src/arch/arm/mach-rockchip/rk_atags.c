// SPDX-License-Identifier:     GPL-2.0+
/*
 * (C) Copyright 2018 Rockchip Electronics Co., Ltd.
 *
 */

#include <common.h>
#include <asm/io.h>
#include <asm/arch-rockchip/bootrom.h>
#include <asm/arch-rockchip/rk_atags.h>
#if CONFIG_IS_ENABLED(TINY_FRAMEWORK)
#include <debug_uart.h>
#endif

#define HASH_LEN	sizeof(u32)

#if defined(CONFIG_SPL_BUILD) && !defined(CONFIG_TPL_BUILD)
/*
 * The array is used to transform rom bootsource type to rk atags boot type.
 */
static int bootdev_map[] = {
	BOOT_TYPE_UNKNOWN,
	BOOT_TYPE_NAND,
	BOOT_TYPE_EMMC,
	BOOT_TYPE_SPI_NOR,
	BOOT_TYPE_SPI_NAND,
	BOOT_TYPE_SD0,
	BOOT_TYPE_UNKNOWN,
	BOOT_TYPE_UNKNOWN,
	BOOT_TYPE_UNKNOWN,
	BOOT_TYPE_UNKNOWN,
	BOOT_TYPE_UNKNOWN
};

static int spl_bootdev_map[] = {
	BOOT_TYPE_RAM,
	BOOT_TYPE_EMMC,
	BOOT_TYPE_SD0,
	BOOT_TYPE_UNKNOWN,
	BOOT_TYPE_NAND,
	BOOT_TYPE_UNKNOWN,
	BOOT_TYPE_UNKNOWN,
	BOOT_TYPE_UNKNOWN,
	BOOT_TYPE_UNKNOWN,
	BOOT_TYPE_UNKNOWN,
	BOOT_TYPE_UNKNOWN,
	BOOT_TYPE_UNKNOWN,
	BOOT_TYPE_UNKNOWN,
	BOOT_TYPE_UNKNOWN,
	BOOT_TYPE_UNKNOWN,
	BOOT_TYPE_UNKNOWN,
	BOOT_TYPE_MTD_BLK_NAND,
	BOOT_TYPE_MTD_BLK_SPI_NAND,
	BOOT_TYPE_MTD_BLK_SPI_NOR
};
#endif

#if CONFIG_IS_ENABLED(TINY_FRAMEWORK) &&		\
	!CONFIG_IS_ENABLED(LIBGENERIC_SUPPORT) &&	\
	!CONFIG_IS_ENABLED(USE_ARCH_MEMSET)
/**
 * memset - Fill a region of memory with the given value
 * @s: Pointer to the start of the area.
 * @c: The byte to fill the area with
 * @count: The size of the area.
 *
 * Do not use memset() to access IO space, use memset_io() instead.
 */
void *memset(void *s, int c, size_t count)
{
	unsigned long *sl = (unsigned long *)s;
	char *s8;

	s8 = (char *)sl;
	while (count--)
		*s8++ = c;

	return s;
}
#endif

#if CONFIG_IS_ENABLED(TINY_FRAMEWORK) &&		\
	!CONFIG_IS_ENABLED(LIBGENERIC_SUPPORT) &&	\
	!CONFIG_IS_ENABLED(USE_ARCH_MEMCPY)
/**
 * memcpy - Copy one area of memory to another
 * @dest: Where to copy to
 * @src: Where to copy from
 * @count: The size of the area.
 *
 * You should not use this function to access IO space, use memcpy_toio()
 * or memcpy_fromio() instead.
 */
void *memcpy(void *dest, const void *src, size_t count)
{
	unsigned long *dl = (unsigned long *)dest, *sl = (unsigned long *)src;
	char *d8, *s8;

	if (src == dest)
		return dest;

	/* while all data is aligned (common case), copy a word at a time */
	if ((((ulong)dest | (ulong)src) & (sizeof(*dl) - 1)) == 0) {
		while (count >= sizeof(*dl)) {
			*dl++ = *sl++;
			count -= sizeof(*dl);
		}
	}
	/* copy the reset one byte at a time */
	d8 = (char *)dl;
	s8 = (char *)sl;
	while (count--)
		*d8++ = *s8++;

	return dest;
}
#endif

static u32 js_hash(void *buf, u32 len)
{
	u32 i, hash = 0x47C6A7E6;
	char *data = buf;

	if (!buf || !len)
		return hash;

	for (i = 0; i < len; i++)
		hash ^= ((hash << 5) + data[i] + (hash >> 2));

	return hash;
}

int atags_bad_magic(u32 magic)
{
	bool bad;

	bad = ((magic != ATAG_CORE) &&
	       (magic != ATAG_NONE) &&
	       (magic < ATAG_SERIAL || magic > ATAG_MAX));
	if (bad) {
#if !CONFIG_IS_ENABLED(TINY_FRAMEWORK)
		printf("Magic(%x) is not support\n", magic);
#else
		printascii("Magic is not support\n");
#endif
	}

	return bad;
}

static int inline atags_size_overflow(struct tag *t, u32 tag_size)
{
	return (unsigned long)t + (tag_size << 2) - ATAGS_PHYS_BASE > ATAGS_SIZE;
}

int atags_overflow(struct tag *t)
{
	bool overflow;

	overflow = atags_size_overflow(t, 0) ||
		   atags_size_overflow(t, t->hdr.size);
	if (overflow) {
#if !CONFIG_IS_ENABLED(TINY_FRAMEWORK)
		printf("Tag is overflow\n");
#else
		printascii("Tag is overflow\n");
#endif
	}

	return overflow;
}

int atags_is_available(void)
{
	struct tag *t = (struct tag *)ATAGS_PHYS_BASE;

	return (t->hdr.magic == ATAG_CORE);
}

int atags_set_tag(u32 magic, void *tagdata)
{
	u32 length, size = 0, hash;
	struct tag *t = (struct tag *)ATAGS_PHYS_BASE;

#if !defined(CONFIG_TPL_BUILD) && !defined(CONFIG_FPGA_ROCKCHIP)
	if (!atags_is_available())
		return -EPERM;
#endif

	if (!tagdata)
		return -ENODATA;

	if (atags_bad_magic(magic))
		return -EINVAL;

	/* Not allowed to be set by user directly, so do nothing */
	if ((magic == ATAG_CORE) || (magic == ATAG_NONE))
		return -EPERM;

	/* If not initialized, setup now! */
	if (t->hdr.magic != ATAG_CORE) {
		t->hdr.magic = ATAG_CORE;
		t->hdr.size = tag_size(tag_core);
		t->u.core.flags = 0;
		t->u.core.pagesize = 0;
		t->u.core.rootdev = 0;

		t = tag_next(t);
	} else {
		/* Find the end, and use it as a new tag */
		for_each_tag(t, (struct tag *)ATAGS_PHYS_BASE) {
			if (atags_overflow(t))
				return -EINVAL;

			if (atags_bad_magic(t->hdr.magic))
				return -EINVAL;

			/* This is an old tag, override it */
			if (t->hdr.magic == magic)
				break;

			if (t->hdr.magic == ATAG_NONE)
				break;
		}
	}

	/* Initialize new tag */
	switch (magic) {
	case ATAG_SERIAL:
		size = tag_size(tag_serial);
		break;
	case ATAG_BOOTDEV:
		size = tag_size(tag_bootdev);
		break;
	case ATAG_TOS_MEM:
		size = tag_size(tag_tos_mem);
		break;
	case ATAG_DDR_MEM:
		size = tag_size(tag_ddr_mem);
		break;
	case ATAG_RAM_PARTITION:
		size = tag_size(tag_ram_partition);
		break;
	case ATAG_ATF_MEM:
		size = tag_size(tag_atf_mem);
		break;
	case ATAG_PUB_KEY:
		size = tag_size(tag_pub_key);
		break;
	case ATAG_SOC_INFO:
		size = tag_size(tag_soc_info);
		break;
	case ATAG_BOOT1_PARAM:
		size = tag_size(tag_boot1p);
		break;
	};

	if (!size)
		return -EINVAL;

	if (atags_size_overflow(t, size))
		return -ENOMEM;

	/* It's okay to setup a new tag */
	t->hdr.magic = magic;
	t->hdr.size = size;
	length = (t->hdr.size << 2) - sizeof(struct tag_header) - HASH_LEN;
	memcpy(&t->u, (char *)tagdata, length);
	hash = js_hash(t, (size << 2) - HASH_LEN);
	memcpy((char *)&t->u + length, &hash, HASH_LEN);

	/* Next tag */
	t = tag_next(t);

	/* Setup done */
	t->hdr.magic = ATAG_NONE;
	t->hdr.size = 0;

	return 0;
}

#ifndef CONFIG_TPL_BUILD
struct tag *atags_get_tag(u32 magic)
{
	u32 *hash, calc_hash, size;
	struct tag *t;

	if (!atags_is_available())
		return NULL;

	for_each_tag(t, (struct tag *)ATAGS_PHYS_BASE) {
		if (atags_overflow(t))
			return NULL;

		if (atags_bad_magic(t->hdr.magic))
			return NULL;

		if (t->hdr.magic != magic)
			continue;

		size = t->hdr.size;
		hash = (u32 *)((ulong)t + (size << 2) - HASH_LEN);
		if (!*hash) {
			debug("No hash, magic(%x)\n", magic);
			return t;
		} else {
			calc_hash = js_hash(t, (size << 2) - HASH_LEN);
			if (calc_hash == *hash) {
				debug("Hash okay, magic(%x)\n", magic);
				return t;
			} else {
				debug("Hash bad, magic(%x), orgHash=%x, nowHash=%x\n",
				      magic, *hash, calc_hash);
				return NULL;
			}
		}
	}

	return NULL;
}
#else
struct tag *atags_get_tag(u32 magic) { return NULL; }
#endif

#if defined(CONFIG_SPL_BUILD) && !defined(CONFIG_TPL_BUILD)
int get_bootdev_by_brom_bootsource(void)
{
	int bootsource = 0;

	bootsource = readl(BROM_BOOTSOURCE_ID_ADDR);
	if (bootsource > ARRAY_SIZE(bootdev_map) - 1 || bootsource < 0)
		return 0;
	else
		return bootdev_map[bootsource];
}

int atags_set_bootdev_by_brom_bootsource(void)
{
	struct tag_bootdev boot_dev;

	memset(&boot_dev, 0, sizeof(struct tag_bootdev));
	boot_dev.devtype = get_bootdev_by_brom_bootsource();

	return atags_set_tag(ATAG_BOOTDEV, &boot_dev);
}

int get_bootdev_by_spl_bootdevice(int bootdevice)
{
	if (bootdevice > ARRAY_SIZE(spl_bootdev_map) - 1)
		return -ENODEV;

	return spl_bootdev_map[bootdevice];
}

int atags_set_bootdev_by_spl_bootdevice(int bootdevice)
{
	struct tag_bootdev boot_dev;

	memset(&boot_dev, 0, sizeof(struct tag_bootdev));
	boot_dev.devtype = get_bootdev_by_spl_bootdevice(bootdevice);
	if (boot_dev.devtype < 0)
		boot_dev.devtype = BOOT_TYPE_UNKNOWN;

	return atags_set_tag(ATAG_BOOTDEV, &boot_dev);
}

int atags_set_pub_key(void *data, int len, int flag)
{
	struct tag_pub_key pub_key;

	if (!data)
		return -ENOMEM;

	memset(&pub_key, 0, sizeof(struct tag_pub_key));
	pub_key.len = len;
	pub_key.flag = flag;
	memcpy(pub_key.data, data, len);

	return atags_set_tag(ATAG_PUB_KEY, &pub_key);
}
#endif

void atags_destroy(void)
{
	if (atags_is_available())
		memset((char *)ATAGS_PHYS_BASE, 0, sizeof(struct tag));
}

