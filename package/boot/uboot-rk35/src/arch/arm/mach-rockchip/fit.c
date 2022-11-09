/*
 * (C) Copyright 2019 Rockchip Electronics Co., Ltd
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */
#include <common.h>
#include <boot_rkimg.h>
#include <image.h>
#include <malloc.h>
#include <sysmem.h>
#include <asm/arch-rockchip/fit.h>
#include <asm/arch-rockchip/resource_img.h>

DECLARE_GLOBAL_DATA_PTR;

#define FIT_PLACEHOLDER_ADDR		0xffffff00

/*
 * Must use args '-E -p' for mkimage to generate FIT image, 4K as max assumption.
 */
#define FIT_FDT_MAX_SIZE		SZ_4K

static int fit_is_ext_type(const void *fit)
{
	return fdt_totalsize(fit) < FIT_FDT_MAX_SIZE;
}

static int fit_is_signed(const void *fit, const void *sig_blob)
{
	return fdt_subnode_offset(sig_blob, 0, FIT_SIG_NODENAME) < 0 ? 0 : 1;
}

static inline int fit_image_addr_is_placeholder(ulong addr)
{
	return (addr & 0xffffff00) == FIT_PLACEHOLDER_ADDR;
}

static int fit_sig_require_conf(const void *fit, const void *sig_blob)
{
	const char *required;
	int sig_node;
	int noffset;

	sig_node = fdt_subnode_offset(sig_blob, 0, FIT_SIG_NODENAME);
	if (sig_node < 0)
		return 0;

	fdt_for_each_subnode(noffset, sig_blob, sig_node) {
		required = fdt_getprop(sig_blob, noffset, "required", NULL);
		if (required && !strcmp(required, "conf"))
			return 1;
	}

	return 0;
}

int fit_default_conf_get_node(const void *fit, const char *prop_name)
{
	int conf_noffset;

	conf_noffset = fit_conf_get_node(fit, NULL); /* NULL for default conf */
	if (conf_noffset < 0)
		return conf_noffset;

	return fit_conf_get_prop_node(fit, conf_noffset, prop_name);
}

int fix_image_set_addr(const void *fit, const char *prop_name,
		       ulong old, ulong new)
{
	int noffset;

	/* do not fix if verified-boot */
	if (!fit_image_addr_is_placeholder(old) ||
	     fit_sig_require_conf(fit, gd_fdt_blob()))
		return 0;

	noffset = fit_default_conf_get_node(fit, prop_name);
	if (noffset < 0)
		return noffset;

	/* optional */
	fit_image_set_entry(fit, noffset, new);

	return fit_image_set_load(fit, noffset, new);
}

static int fdt_image_get_offset_size(const void *fit, const char *prop_name,
				     int *offset, int *size)
{
	int sz, offs;
	int noffset;
	int ret;

	noffset = fit_default_conf_get_node(fit, prop_name);
	if (noffset < 0)
		return noffset;

	ret = fit_image_get_data_size(fit, noffset, &sz);
	if (ret)
		return ret;

	ret = fit_image_get_data_position(fit, noffset, &offs);
	if (!ret)
		offs -= fdt_totalsize(fit);
	else
		ret = fit_image_get_data_offset(fit, noffset, &offs);

	*offset = offs;
	*size = sz;

	return ret;
}

static int fdt_image_get_load(const void *fit, const char *prop_name,
			      ulong *load)
{
	int noffset;

	noffset = fit_default_conf_get_node(fit, prop_name);
	if (noffset < 0)
		return noffset;

	return fit_image_get_load(fit, noffset, load);
}

static int fit_image_get_param(const void *fit, const char *prop_name,
			       ulong *load, int *offset, int *size)
{
	int ret;

	ret = fdt_image_get_offset_size(fit, prop_name, offset, size);
	if (ret < 0)
		return ret;

	return fdt_image_get_load(fit, prop_name, load);
}

static void *fit_get_blob(struct blk_desc *dev_desc,
			  disk_partition_t *out_part,
			  bool verify)
{
	__maybe_unused int conf_noffset;
	disk_partition_t part;
	char *part_name;
	void *fit, *fdt;
	int blk_num;

	if (rockchip_get_boot_mode() == BOOT_MODE_RECOVERY)
		part_name = PART_RECOVERY;
	else
		part_name = PART_BOOT;

	if (part_get_info_by_name(dev_desc, part_name, &part) < 0) {
		FIT_I("No %s partition\n", part_name);
		return NULL;
	}

	*out_part = part;
	blk_num = DIV_ROUND_UP(sizeof(struct fdt_header), dev_desc->blksz);
	fdt = memalign(ARCH_DMA_MINALIGN, blk_num * dev_desc->blksz);
	if (!fdt)
		return NULL;

	if (blk_dread(dev_desc, part.start, blk_num, fdt) != blk_num) {
		debug("Failed to read fdt header\n");
		goto fail;
	}

	if (fdt_check_header(fdt)) {
		debug("No fdt header\n");
		goto fail;
	}

	if (!fit_is_ext_type(fdt)) {
		debug("Not external type\n");
		goto fail;
	}

	blk_num = DIV_ROUND_UP(fdt_totalsize(fdt), dev_desc->blksz);
	fit = memalign(ARCH_DMA_MINALIGN, blk_num * dev_desc->blksz);
	if (!fit) {
		debug("No memory\n");
		goto fail;
	}

	if (blk_dread(dev_desc, part.start, blk_num, fit) != blk_num) {
		free(fit);
		debug("Failed to read fit blob\n");
		goto fail;
	}

#ifdef CONFIG_FIT_SIGNATURE
	if (!verify)
		return fit;

	conf_noffset = fit_conf_get_node(fit, NULL); /* NULL for default conf */
	if (conf_noffset < 0)
		goto fail;

	printf("%s: ", fdt_get_name(fit, conf_noffset, NULL));
	if (fit_config_verify(fit, conf_noffset)) {
		puts("\n");
		run_command("download", 0);
		hang();
	}
	puts("\n");
#endif
	return fit;

fail:
	free(fdt);
	return NULL;
}

static int fit_image_fixup_alloc(const void *fit, const char *prop_name,
				 const char *addr_name, enum memblk_id mem)
{
	ulong load, addr;
	int offset, size = 0;
	int ret;

	addr = env_get_ulong(addr_name, 16, 0);
	if (!addr)
		return -EINVAL;

	ret = fit_image_get_param(fit, prop_name, &load, &offset, &size);
	if (ret)
		return (ret == -FDT_ERR_NOTFOUND) ? 0 : ret;

	if (!size)
		return 0;

	ret = fix_image_set_addr(fit, prop_name, load, addr);
	if (ret)
		return ret;

	if (!sysmem_alloc_base(mem, (phys_addr_t)addr,
			       ALIGN(size, RK_BLK_SIZE)))
		return -ENOMEM;

	return 0;
}

int fit_image_pre_process(const void *fit)
{
	int ret;

	if ((gd->flags & GD_FLG_KDTB_READY) && !gd->fdt_blob_kern)
		sysmem_free((phys_addr_t)gd->fdt_blob);

	ret = fit_image_fixup_alloc(fit, FIT_FDT_PROP,
				    "fdt_addr_r", MEM_FDT);
	if (ret < 0)
		return ret;

	ret = fit_image_fixup_alloc(fit, FIT_KERNEL_PROP,
				    "kernel_addr_r", MEM_KERNEL);
	if (ret < 0)
		return ret;

	return fit_image_fixup_alloc(fit, FIT_RAMDISK_PROP,
				     "ramdisk_addr_r", MEM_RAMDISK);
}

int fit_image_fail_process(const void *fit)
{
	ulong raddr, kaddr, faddr;

	raddr = env_get_ulong("ramdisk_addr_r", 16, 0);
	kaddr = env_get_ulong("kernel_addr_r", 16, 0);
	faddr = env_get_ulong("fdt_addr_r", 16, 0);

	sysmem_free((phys_addr_t)fit);
	sysmem_free((phys_addr_t)raddr);
	sysmem_free((phys_addr_t)kaddr);
	sysmem_free((phys_addr_t)faddr);

	return 0;
}

static int fit_image_get_subnode(const void *fit, int noffset, const char *name)
{
	int sub_noffset;

	fdt_for_each_subnode(sub_noffset, fit, noffset) {
		if (!strncmp(fit_get_name(fit, sub_noffset, NULL),
			     name, strlen(name)))
			return sub_noffset;
	}

	return -ENOENT;
}

static int fit_image_load_one(const void *fit, struct blk_desc *dev_desc,
			      disk_partition_t *part, char *prop_name,
			      void *data, int check_hash)
{
	u32 blk_num, blk_off;
	int offset, size;
	int noffset, ret;
	char *msg = "";

	ret = fdt_image_get_offset_size(fit, prop_name, &offset, &size);
	if (ret)
		return ret;

	blk_off = (FIT_ALIGN(fdt_totalsize(fit)) + offset) / dev_desc->blksz;
	blk_num = DIV_ROUND_UP(size, dev_desc->blksz);
	if (blk_dread(dev_desc, part->start + blk_off, blk_num, data) != blk_num)
		return -EIO;

	if (check_hash) {
		int hash_noffset;

		noffset = fit_default_conf_get_node(fit, prop_name);
		if (noffset < 0)
			return noffset;

		hash_noffset = fit_image_get_subnode(fit, noffset,
						     FIT_HASH_NODENAME);
		if (hash_noffset < 0)
			return hash_noffset;

		printf("%s: ", fdt_get_name(fit, noffset, NULL));
		ret = fit_image_check_hash(fit, hash_noffset, data, size, &msg);
		if (ret)
			return ret;

		puts("+\n");
	}

	return 0;
}

/* Calculate what we really need */
ulong fit_image_get_bootables_size(const void *fit)
{
	ulong off[3] = { 0, 0, 0 };
	ulong max_off, load;
	int offset, size;

#if 0
	if (!fit_get_totalsize(fit, &size))
		return size;
#endif

	if (!fit_image_get_param(fit, FIT_FDT_PROP, &load, &offset, &size))
		off[0] = offset + FIT_ALIGN(size);

	if (!fit_image_get_param(fit, FIT_KERNEL_PROP, &load, &offset, &size))
		off[1] = offset + FIT_ALIGN(size);

	if (!fit_image_get_param(fit, FIT_RAMDISK_PROP, &load, &offset, &size))
		off[2] = offset + FIT_ALIGN(size);

	max_off = max(off[0],  off[1]);
	max_off = max(max_off, off[2]);

	return FIT_ALIGN(fdt_totalsize(fit)) + max_off;
}

void *fit_image_load_bootables(ulong *size)
{
	struct blk_desc *dev_desc;
	disk_partition_t part;
	int blk_num;
	void *fit;

	dev_desc = rockchip_get_bootdev();
	if (!dev_desc)
		return NULL;

	fit = fit_get_blob(dev_desc, &part, false);
	if (!fit) {
		FIT_I("No fit blob\n");
		return NULL;
	}

	*size = fit_image_get_bootables_size(fit);
	if (*size == 0) {
		FIT_I("No bootable image\n");
		return NULL;
	}

	blk_num = DIV_ROUND_UP(*size, dev_desc->blksz);
	fit = sysmem_alloc(MEM_FIT, blk_num * dev_desc->blksz);
	if (!fit)
		return NULL;

	if (blk_dread(dev_desc, part.start, blk_num, fit) != blk_num) {
		FIT_I("Failed to load bootable images\n");
		return NULL;
	}

	return fit;
}

static void fit_msg(const void *fit)
{
	FIT_I("%ssigned, %sconf required\n",
	      fit_is_signed(fit, gd_fdt_blob()) ? "" : "no ",
	      fit_sig_require_conf(fit, gd_fdt_blob()) ? "" : "no ");
}

#ifdef CONFIG_ROCKCHIP_RESOURCE_IMAGE
static int fit_image_load_resource(const void *fit, struct blk_desc *dev_desc,
				   disk_partition_t *part, ulong *addr)
{
	int offset, size;
	int ret;
	void *data;

	ret = fdt_image_get_offset_size(fit, FIT_MULTI_PROP, &offset, &size);
	if (ret)
		return ret;

	data = malloc(ALIGN(size, dev_desc->blksz));
	if (!data)
		return -ENOMEM;

	*addr = (ulong)data;

	return fit_image_load_one(fit, dev_desc, part, FIT_MULTI_PROP,
				  data, IS_ENABLED(CONFIG_FIT_SIGNATURE));
}

int fit_image_init_resource(void)
{
	struct blk_desc *dev_desc;
	disk_partition_t part;
	int ret = 0;
	void *fit;

	dev_desc = rockchip_get_bootdev();
	if (!dev_desc) {
		FIT_I("No dev_desc!\n");
		return -ENODEV;
	}

	fit = fit_get_blob(dev_desc, &part, true);
	if (!fit)
		return -EINVAL;

#ifdef CONFIG_ROCKCHIP_RESOURCE_IMAGE
	ulong rsce;

	ret = fit_image_load_resource(fit, dev_desc, &part, &rsce);
	if (ret) {
		FIT_I("Failed to load resource\n");
		free(fit);
		return ret;
	}

	ret = resource_create_ram_list(dev_desc, (void *)rsce);
	if (ret) {
		FIT_I("Failed to create resource list\n");
		free(fit);
		return ret;
	}
#endif
	fit_msg(fit);
	free(fit);

	return ret;
}
#else
int fit_image_read_dtb(void *fdt_addr)
{
	struct blk_desc *dev_desc;
	disk_partition_t part;
	void *fit;

	dev_desc = rockchip_get_bootdev();
	if (!dev_desc) {
		FIT_I("No dev_desc!\n");
		return -ENODEV;;
	}

	fit = fit_get_blob(dev_desc, &part, true);
	if (!fit)
		return -EINVAL;

	fit_msg(fit);

	return fit_image_load_one(fit, dev_desc, &part, FIT_FDT_PROP,
				  (void *)fdt_addr, 1);
}
#endif
