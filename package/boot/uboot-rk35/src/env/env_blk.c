// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (c) 2019 Fuzhou Rockchip Electronics Co., Ltd
 */

#include <common.h>
#include <environment.h>
#include <memalign.h>
#include <boot_rkimg.h>

#define __STR(X) #X
#define STR(X) __STR(X)

#if defined(CONFIG_ENV_SIZE_REDUND) &&  \
	(CONFIG_ENV_SIZE_REDUND != CONFIG_ENV_SIZE)
#error CONFIG_ENV_SIZE_REDUND should be the same as CONFIG_ENV_SIZE
#endif

DECLARE_GLOBAL_DATA_PTR;

int get_env_addr(struct blk_desc *blk_desc, int copy, u32 *env_addr)
{
	s64 offset = CONFIG_ENV_OFFSET;

#if defined(CONFIG_ENV_OFFSET_REDUND)
	if (copy)
		offset = CONFIG_ENV_OFFSET_REDUND;
#endif
	if (offset < 0)
		return -EINVAL;

	*env_addr = offset;

	return 0;
}

int get_env_dev(void)
{
	return CONFIG_SYS_MMC_ENV_DEV;
}

#ifdef CONFIG_SYS_MMC_ENV_PART
static unsigned char env_org_hwpart;

int get_env_part(void)
{
	return CONFIG_SYS_MMC_ENV_PART;
}

static const char *init_blk_hwpart_for_env(struct blk_desc *blk_desc)
{
	enum if_type if_type;
	const char *devtype;
	int devnum, devpart, ret;

	devtype = env_get("devtype");
	devnum = env_get_ulong("devnum", 10, 0);
	devpart = get_env_part();
	if_type = if_typename_to_iftype(devtype);

	env_org_hwpart = blk_desc->hwpart;
	ret = blk_select_hwpart_devnum(if_type, devnum, devpart);
	if (ret)
		return "!Partition switch failed";

	return NULL;
}

static void fini_blk_hwpart_for_env(void)
{
	enum if_type if_type;
	const char *devtype;
	int devnum;

	devtype = env_get("devtype");
	devnum = env_get_ulong("devnum", 10, 0);
	if_type = if_typename_to_iftype(devtype);

	blk_select_hwpart_devnum(if_type, devnum, env_org_hwpart);
}
#else
static inline const char *init_blk_hwpart_for_env(struct blk_desc *blk_desc)
{ return NULL; }
static inline void fini_blk_hwpart_for_env(void) {}
#endif

#if defined(CONFIG_CMD_SAVEENV) && !defined(CONFIG_SPL_BUILD)
static inline int write_env(struct blk_desc *blk_desc, unsigned long size,
			    unsigned long offset, const void *buffer)
{
	uint blk_start, blk_cnt, n;

	blk_start = ALIGN(offset, blk_desc->blksz) / blk_desc->blksz;
	blk_cnt	  = ALIGN(size, blk_desc->blksz) / blk_desc->blksz;

	n = blk_dwrite(blk_desc, blk_start, blk_cnt, (u_char *)buffer);

	return (n == blk_cnt) ? 0 : -1;
}

static int env_blk_save(void)
{
	ALLOC_CACHE_ALIGN_BUFFER(env_t, env_new, 1);
	struct blk_desc *blk_desc;
	const char *errmsg = NULL;
	int ret, copy = 0;
	u32 offset;

	blk_desc = rockchip_get_bootdev();
	if (!blk_desc) {
		puts("Can't find bootdev\n");
		return -EIO;
	}

	errmsg = init_blk_hwpart_for_env(blk_desc);
	if (errmsg) {
		puts(errmsg);
		return -EIO;
	}

	ret = env_export(env_new);
	if (ret)
		goto fini;

#ifdef CONFIG_ENV_OFFSET_REDUND
	if (gd->env_valid == ENV_VALID)
		copy = 1;
#endif

	if (get_env_addr(blk_desc, copy, &offset)) {
		ret = 1;
		goto fini;
	}

	printf("Writing to %s%s(%s)... ", copy ? "redundant " : "",
	       env_get("devtype"), env_get("devnum"));

	if (write_env(blk_desc, CONFIG_ENV_SIZE, offset, (u_char *)env_new)) {
		puts("failed\n");
		ret = 1;
		goto fini;
	}

	puts("done\n");
	ret = 0;

#ifdef CONFIG_ENV_OFFSET_REDUND
	gd->env_valid = gd->env_valid == ENV_REDUND ? ENV_VALID : ENV_REDUND;
#endif

fini:
	fini_blk_hwpart_for_env();

	return ret;
}
#endif /* CONFIG_CMD_SAVEENV && !CONFIG_SPL_BUILD */

static inline int read_env(struct blk_desc *blk_desc, unsigned long size,
			   unsigned long offset, const void *buffer)
{
	uint blk_start, blk_cnt, n;

	blk_start = ALIGN(offset, blk_desc->blksz) / blk_desc->blksz;
	blk_cnt	  = ALIGN(size, blk_desc->blksz) / blk_desc->blksz;

	n = blk_dread(blk_desc, blk_start, blk_cnt, (uchar *)buffer);

	return (n == blk_cnt) ? 0 : -1;
}

#ifdef CONFIG_ENV_OFFSET_REDUND
static int env_blk_load(void)
{
#if !defined(ENV_IS_EMBEDDED)
	struct blk_desc *blk_desc;
	const char *errmsg = NULL;
	int read1_fail = 0, read2_fail = 0;
	u32 offset1, offset2;
	int ret;

	ALLOC_CACHE_ALIGN_BUFFER(env_t, tmp_env1, 1);
	ALLOC_CACHE_ALIGN_BUFFER(env_t, tmp_env2, 1);

	blk_desc = rockchip_get_bootdev();
	if (!blk_desc) {
		puts("Can't find bootdev\n");
		return -EIO;
	}

	errmsg = init_blk_hwpart_for_env(blk_desc);
	if (errmsg) {
		ret = -EIO;
		goto err;
	}

	if (get_env_addr(blk_desc, 0, &offset1) ||
	    get_env_addr(blk_desc, 1, &offset2)) {
		ret = -EIO;
		goto fini;
	}

	read1_fail = read_env(blk_desc, CONFIG_ENV_SIZE, offset1, tmp_env1);
	read2_fail = read_env(blk_desc, CONFIG_ENV_SIZE, offset2, tmp_env2);

	if (read1_fail && read2_fail)
		puts("*** Error - No Valid Environment Area found\n");
	else if (read1_fail || read2_fail)
		puts("*** Warning - some problems detected "
		     "reading environment; recovered successfully\n");

	if (read1_fail && read2_fail) {
		errmsg = "!bad CRC";
		ret = -EIO;
		goto fini;
	} else if (!read1_fail && read2_fail) {
		gd->env_valid = ENV_VALID;
		env_import((char *)tmp_env1, 1);
	} else if (read1_fail && !read2_fail) {
		gd->env_valid = ENV_REDUND;
		env_import((char *)tmp_env2, 1);
	} else {
		env_import_redund((char *)tmp_env1, (char *)tmp_env2);
	}

	ret = 0;

fini:
	fini_blk_hwpart_for_env();
err:
	if (ret)
		set_default_env(errmsg);

#endif
	return ret;
}
#else /* ! CONFIG_ENV_OFFSET_REDUND */
static int env_blk_load(void)
{
#if !defined(ENV_IS_EMBEDDED)
	ALLOC_CACHE_ALIGN_BUFFER(char, buf, CONFIG_ENV_SIZE);
	struct blk_desc *blk_desc;
	const char *errmsg = NULL;
	u32 offset;
	int ret;

	blk_desc = rockchip_get_bootdev();
	if (!blk_desc) {
		puts("Can't find bootdev\n");
		return -EIO;
	}

	errmsg = init_blk_hwpart_for_env(blk_desc);
	if (errmsg) {
		ret = -EIO;
		puts(errmsg);
		goto err;
	}

	if (get_env_addr(blk_desc, 0, &offset)) {
		ret = -EIO;
		goto fini;
	}

	if (read_env(blk_desc, CONFIG_ENV_SIZE, offset, buf)) {
		errmsg = "!read failed";
		ret = -EIO;
		goto fini;
	}

	env_import(buf, 1);
	ret = 0;

fini:
	fini_blk_hwpart_for_env();
err:
	if (ret)
		set_default_env(errmsg);
#endif
	return ret;
}
#endif /* CONFIG_ENV_OFFSET_REDUND */

U_BOOT_ENV_LOCATION(env_blk) = {
	.location	= ENVL_BLK,
	ENV_NAME("ENV_BLK")
	.load		= env_blk_load,
#ifndef CONFIG_SPL_BUILD
	.save		= env_save_ptr(env_blk_save),
#endif
};
