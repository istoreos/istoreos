/*
 * (C) Copyright 2021 Rockchip Electronics Co., Ltd.
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */

#include <common.h>
#include <boot_rkimg.h>
#include <crypto.h>
#include <dm.h>
#include <sysmem.h>
#include <u-boot/sha256.h>
#ifdef CONFIG_ANDROID_AB
#include <android_avb/avb_ops_user.h>
#include <android_avb/rk_avb_ops_user.h>
#endif
#include <asm/arch-rockchip/vendor.h>

DECLARE_GLOBAL_DATA_PTR;

#define TFTPUD_I(fmt, args...)	printf("[TFTPUD]: "fmt, ##args)
#define TFTPUD_E(fmt, args...)	printf("[TFTPUD-ERROR]: "fmt, ##args)

#define UPDATE_HDR_FILE		"update.hdr"
#define GPT_ENV_FILE		"gpt_env.txt"
#define MAX_UPDATE_HEADER_SIZE	SZ_128K
#define MAX_REMAIN_TRIES	3
#define SHA256_HASH_SIZE	32

struct update_header {
	struct list_head images;
	void *shared_buf;
	u32 version;
	u32 rollback_idx;
	u32 lba_step;
	u32 mb;
	int force_update;
	const char *spec_partition;
};

struct local_information {
	u32 version;
	u32 rollback_idx;
	char current_slot[3];
};

struct image_element {
	char file_name[32];
	char part_name[32];
	void *buf;
	u32 size;	/* uint: byte */
	u32 lba_start;
	u32 lba_offset;
	u32 lba_cnt;
	u8 remain_tries;
	int hash_noffset;
	struct list_head node;
};

static struct update_header update_hdr;
static struct local_information local_info;
static const char *server_dir;

static int tftpfw_version_set(u32 version)
{
	int ret;

	ret = vendor_storage_write(FIRMWARE_VER_ID, &version, sizeof(version));

	return ret < 0 ? ret : 0;
}

static u32 tftpfw_version_get(void)
{
	u32 version;
	int ret;

	ret = vendor_storage_read(FIRMWARE_VER_ID, &version, sizeof(version));
	if (ret < 0) {
		if (ret == -EINVAL) {
			version = 0; /* first initial as 0 */
			TFTPUD_I("Initial firmware version as 0\n");
			ret = tftpfw_version_set(version);
			if (ret < 0)
				return ret;
		} else {
			return ret;
		}
	}

	return version;
}

static int tftp_download(void *addr, const char *file)
{
	char tftp_cmd[64];

	if (server_dir)
		snprintf(tftp_cmd, 64, "tftp 0x%lx %s/%s",
				(ulong)addr, server_dir, file);
	else
		snprintf(tftp_cmd, 64, "tftp 0x%lx %s", (ulong)addr, file);

	return run_command(tftp_cmd, 0);
}

static void update_cleanup(void *fit, struct update_header *hdr)
{
	struct image_element *e;
	struct list_head *node;

	list_for_each(node, &hdr->images) {
		e = list_entry(node, struct image_element, node);
		free(e);
	}

	if (hdr->shared_buf)
		free(hdr->shared_buf);
	if (fit)
		free(fit);
}

static inline int is_gpt(const char *name)
{
	if (!name)
		return 0;

	return !strcmp(name, GPT_ENV_FILE);
}

static int update_populate_image(void *fit, struct update_header *hdr)
{
	struct blk_desc *dev_desc;
	struct image_element *e;
	disk_partition_t part;
	const char *name, *dp;
	const char *noseq_name;
	char *last_part_name = NULL;
	uint last_lba_offset = 0;
	uint lba_offset;
	int images, noffset;
	int ret;

	images = fdt_path_offset(fit, FIT_IMAGES_PATH);
	if (images < 0)
		return images;

	dev_desc = rockchip_get_bootdev();
	if (!dev_desc)
		return -ENODEV;

	fdt_for_each_subnode(noffset, fit, images) {
		name = fit_get_name(fit, noffset, NULL);
		printf("# %s:\n", name);

		if (is_gpt(name))
			continue;

		e = malloc(sizeof(*e));
		if (!e)
			return -ENOMEM;

		e->remain_tries = MAX_REMAIN_TRIES;
		e->buf = hdr->shared_buf;
		e->size = fdtdec_get_uint(fit, noffset, "data-size", -ENODATA);
		if (e->size == -ENODATA)
			return -ENODATA;

		/* part name */
		strcpy(e->file_name, name);
		strcat(e->file_name, ".part.img");
		noseq_name = strstr(name, "-");
		if (!noseq_name)
			return -EINVAL;
		noseq_name++;
		dp = strstr(noseq_name, "-");
		if (!dp)
			return -EINVAL;
		dp++;
		strlcpy(e->part_name, noseq_name, strlen(noseq_name) - strlen(dp));
		ret = part_get_info_by_name_strict(dev_desc, e->part_name, &part);
		if (ret < 0) {
			TFTPUD_E("No partition '%s'\n", e->part_name);
			return -EINVAL;
		}

		/* lba */
		if (!strcmp(last_part_name, e->part_name))
			lba_offset = last_lba_offset + hdr->lba_step;
		else
			lba_offset = 0;

		e->lba_start = part.start;
		e->lba_offset = lba_offset;
		e->lba_cnt = DIV_ROUND_UP(e->size, 512);
		e->hash_noffset = fdt_subnode_offset(fit, noffset, "hash");
		if (e->hash_noffset < 0)
			return e->hash_noffset;

		list_add_tail(&e->node, &hdr->images);
		last_part_name = e->part_name;
		last_lba_offset = lba_offset;

		printf("            file: %s\n", e->file_name);
		printf("       partition: %s\n", e->part_name);
		printf("             buf: 0x%08lx\n", (ulong)e->buf);
		printf("            size: 0x%08x\n", e->size);
		printf("       lba_start: 0x%08x\n", e->lba_start);
		printf("      lba_offset: 0x%08x\n", e->lba_offset);
		printf("         lba_cnt: 0x%08x\n", e->lba_cnt);
		printf("    remain_tries: %d\n", e->remain_tries);
		printf("    hash_noffset: 0x%08x\n\n", e->hash_noffset);
	}

	return 0;
}

static void *update_download_hdr(struct update_header *hdr)
{
	u32 filesz;
	void *fit;

	fit = memalign(ARCH_DMA_MINALIGN, MAX_UPDATE_HEADER_SIZE);
	if (!fit)
		return NULL;

	if (tftp_download(fit, UPDATE_HDR_FILE)) {
		free(fit);
		return NULL;
	}

	if (fdt_check_header(fit)) {
		TFTPUD_E("invalid update hdr magic\n");
		free(fit);
		return NULL;
	}

	/* sha256 csum was appended at the end of update.hdr */
	filesz = env_get_ulong("filesize", 16, 0);
	if ((fdt_totalsize(fit) + SHA256_HASH_SIZE) != filesz) {
		TFTPUD_E("invalid sha256 hash at the tail of hdr\n");
		return NULL;
	}

	return fit;
}

#ifndef CONFIG_FIT_SIGNATURE
#ifdef CONFIG_DM_CRYPTO
static void sha256_checksum(char *input, u32 input_len, u8 *output)
{
	sha_context csha_ctx;
	struct udevice *dev;

	dev = crypto_get_device(CRYPTO_SHA256);
	if (!dev) {
		TFTPUD_E("No crypto device\n");
		return;
	}
	csha_ctx.algo = CRYPTO_SHA256;
	csha_ctx.length = input_len;
	crypto_sha_csum(dev, &csha_ctx, (char *)input, input_len, output);
}
#else
static void sha256_checksum(char *input, u32 input_len, u8 *output)
{
	sha256_csum((const uchar *)input, input_len, output);
}
#endif

static int hdr_checksum_verify(void *fit, struct update_header *hdr)
{
	u8 *hash, csum[SHA256_HASH_SIZE];
	int ret, i;

	hash = (u8 *)fit + fdt_totalsize(fit);
	sha256_checksum(fit, fdt_totalsize(fit), csum);
	ret = memcmp(hash, csum, SHA256_HASH_SIZE) ? -EINVAL : 0;
	if (ret) {
		printf(" update.hash: ");
		for (i = 0; i < SHA256_HASH_SIZE; i++)
			printf("%02x", hash[i]);
		printf("\n");

		printf(" calculate hash: ");
		for (i = 0; i < SHA256_HASH_SIZE; i++)
			printf("%02x", csum[i]);
		printf("\n");
	}

	return ret;
}
#endif

static void print_hdr_local(struct update_header *hdr,
			    struct local_information *local)
{
	printf("# Server:\n");
	printf("         version: %d\n", hdr->version);
	printf("    rollback_idx: %d\n", hdr->rollback_idx);
	printf("    force_update: %d\n", hdr->force_update);
	printf("              MB: %d\n", hdr->mb);
	printf("        lba_step: 0x%08x\n", hdr->lba_step);
	printf("      shared_buf: 0x%08lx - 0x%08lx\n",
	       (ulong)hdr->shared_buf, (ulong)hdr->shared_buf + hdr->mb * SZ_1M);
	printf("  spec_partition: %s\n\n", hdr->spec_partition);

	printf("# Local:\n");
	printf("         version: %d\n", local->version);
	printf("    rollback_idx: %d\n", local->rollback_idx);
	printf("    current_slot: %s\n", local->current_slot);
	printf("\n");
}

static int hdr_param_verify(void *fit, struct update_header *hdr,
			    struct local_information *local, int conf)
{
	u32 size;
	int ret;

	/* remote */
	hdr->version = fdtdec_get_uint(fit, 0, "version", 0);
	hdr->rollback_idx = fdtdec_get_uint(fit, conf, "rollback-index", 0);
	hdr->force_update = fdtdec_get_uint(fit, conf, "force_update", 0);
	hdr->mb = fdtdec_get_uint(fit, conf, "image-size-MB", 0);
	size = hdr->mb * SZ_1M;
	hdr->lba_step = size / 512;
	/* TODO: use sysmem alloc/free */
	hdr->shared_buf = malloc(size);
	if (!hdr->shared_buf)
		return -ENOMEM;

	/* local */
	ret = tftpfw_version_get();
	if (ret < 0) {
		TFTPUD_E("Failed to get local firmware version, ret=%d\n", ret);
		return local->version;
	}
	local->version = ret;
#ifdef CONFIG_FIT_ROLLBACK_PROTECT
	u32 remote_rollback_idx;

	ret = fit_rollback_index_verify(fit, FIT_ROLLBACK_INDEX,
					&remote_rollback_idx, &local->rollback_idx);
	if (ret) {
		TFTPUD_E("Failed to get local rollback-index, ret=%d\n", ret);
		return ret;
	}
#else
	local->rollback_idx = -1;
#endif
#ifdef CONFIG_ANDROID_AB
	ret = rk_avb_get_current_slot(local->current_slot);
	if (ret) {
		TFTPUD_E("Failed to get local current slot, ret=%d\n", ret);
		return ret;
	}
#else
	strcpy(local->current_slot, "-");
#endif

	print_hdr_local(hdr, local);

	/* verify */
	if (hdr->force_update) {
		TFTPUD_I("Remote requires force upgrade !\n");
		return 0;
	}
	if (hdr->version < local->version) {
		TFTPUD_E("Invalid firmware version: %d(remote) < %d(local)\n",
			 hdr->version, local->version);
		return -EINVAL;
	}
#ifdef CONFIG_FIT_ROLLBACK_PROTECT
	if (remote_rollback_idx < local->rollback_idx) {
		TFTPUD_E("Invalid rollback-index: %d(remote) < %d(local)\n",
			 remote_rollback_idx, local->rollback_idx);
		return -EINVAL;
	}
#endif

	return 0;
}

static int update_verify_hdr(void *fit, struct update_header *hdr,
			     struct local_information *local)
{
	const char *name;
	int noffset;
	int conf;
	int ret;

	noffset = fdt_path_offset(fit, FIT_CONFS_PATH);
	name = fdt_getprop(fit, noffset, "default", NULL);
	conf = fdt_subnode_offset(fit, noffset, name);
	if (conf < 0)
		return conf;

#ifdef CONFIG_FIT_SIGNATURE
	/* Secure: verify signature */
	ret = fit_config_verify(fit, conf);
	if (ret)
		return ret;

	TFTPUD_I("hdr signature verified\n");
#else
	/* Non-secure: verify hash */
	ret = hdr_checksum_verify(fit, hdr);
	if (ret)
		return ret;

	TFTPUD_I("hdr checksum verified\n");
#endif
	/* verify rollback index ..., etc */
	ret = hdr_param_verify(fit, hdr, local, conf);
	if (ret)
		return ret;

	TFTPUD_I("hdr param verified\n");

	return 0;
}

static int update_local_info(void *fit, struct update_header *hdr)
{
	int ret;

	TFTPUD_I("Update local information... ");

	ret = tftpfw_version_set(hdr->version);
	if (ret) {
		TFTPUD_E("Update local param FAIL, ret=%d\n", ret);
		return ret;
	}
	printf("fw_version=%d ", hdr->version);

#ifdef CONFIG_FIT_ROLLBACK_PROTECT
	ret = fit_write_trusty_rollback_index(hdr->rollback_idx);
	if (ret)
		return ret;
	printf("rollback_idx=%d ", hdr->rollback_idx);
#endif
	printf("\n");

	return 0;
}

static int update_ignore_image(void *fit, struct update_header *hdr,
			       struct image_element *e)
{
#ifdef CONFIG_ANDROID_AB
	char *slot_suffix;

	/* Android A/B skip current slot */
	slot_suffix = (char *)e->part_name + strlen(e->part_name) - 2;
	if (!strcmp(hdr->current_slot, slot_suffix))
		return 1;
#endif
	/* try to find expected target partition */
	if (hdr->spec_partition && strcmp(e->part_name, hdr->spec_partition))
		return 1;

	return 0;
}

static int download_image(void *fit, struct image_element *e)
{
	ulong fileaddr;
	ulong filesize;
	char *msg = "";
	int ret;

	/* download */
	printf("[TFTPUD-0]: download \"%s\" at 0x%lx\n",
	       e->file_name, (ulong)e->buf);

	ret = tftp_download(e->buf, e->file_name);
	if (ret)
		return ret;

	fileaddr = env_get_ulong("fileaddr", 16, 0);
	filesize = env_get_ulong("filesize", 16, 0);
	if (!fileaddr || !filesize) {
		TFTPUD_E("No fileaddr and filesize\n");
		return -ENOENT;
	}

	if (filesize != e->size) {
		TFTPUD_E("Expected filesize 0x%08lx != 0x%08x\n", filesize, e->size);
		return -EINVAL;
	}

	/* verify */
	printf("[TFTPUD-1]: verify ");
	ret = fit_image_check_hash(fit, e->hash_noffset, e->buf, e->size, &msg);
	printf("[%s]\n", ret ? "-" : "+");

	return ret;
}

static int update_flash_image(struct image_element *e)
{
	struct blk_desc *dev_desc;
	int ret;

	dev_desc = rockchip_get_bootdev();
	if (!dev_desc) {
		TFTPUD_E("No boot device\n");
		return -ENODEV;
	}

	printf("[TFTPUD-2]: Flash to \"%s\" partition at LBA offset 0x%08x, "
	       "with 0x%08x sectors ... ",
	       e->part_name, e->lba_offset, e->lba_cnt);

	if (dev_desc->if_type == IF_TYPE_MTD) {
		dev_desc->op_flag |= BLK_MTD_CONT_WRITE;
		ret = blk_dwrite(dev_desc, e->lba_start + e->lba_offset,
				 e->lba_cnt, (void *)e->buf);
		dev_desc->op_flag &= ~(BLK_MTD_CONT_WRITE);
	} else {
		ret = blk_dwrite(dev_desc, e->lba_start + e->lba_offset,
				 e->lba_cnt, (void *)e->buf);
	}

	if (ret != e->lba_cnt)
		printf("Failed(%d)\n\n\n", ret);
	else
		printf("OK\n\n\n");

	return 0;
}

static int update_download_image(void *fit, struct image_element *e)
{
	int i, ret;

	for (i = 0; i < e->remain_tries; i++) {
		ret = download_image(fit, e);
		if (!ret)
			return 0;

		TFTPUD_E("retry-%d download\n", i);
		continue;
	}

	return -ENODATA;
}

static int update_write_gpt(void *fit, struct update_header *hdr)
{
	struct image_element *e;
	char *gpt_parts, *p;
	const char *name;
	int images;
	int noffset;
	int ret = 0;

	images = fdt_path_offset(fit, FIT_IMAGES_PATH);
	if (images < 0)
		return images;

	noffset = fdt_first_subnode(fit, images);
	if (noffset < 0)
		return noffset;

	/* gpt must be the 1st node */
	name = fit_get_name(fit, noffset, NULL);
	if (!is_gpt(name))
		return 0;

	e = malloc(sizeof(*e));
	if (!e)
		return -ENOMEM;

	e->remain_tries = MAX_REMAIN_TRIES;
	e->buf = hdr->shared_buf;
	e->size = fdtdec_get_uint(fit, noffset, "data-size", -ENODATA);
	if (e->size == -ENODATA) {
		ret = -EINVAL;
		goto out;
	}

	strcpy(e->file_name, name);
	e->hash_noffset = fdt_subnode_offset(fit, noffset, "hash");
	if (e->hash_noffset < 0)
		return e->hash_noffset;

	printf("\n# %s:\n", e->file_name);
	printf("             buf: 0x%08lx\n", (ulong)e->buf);
	printf("            size: 0x%08x\n", e->size);
	printf("    remain_tries: %d\n", e->remain_tries);
	printf("    hash_noffset: 0x%08x\n\n", e->hash_noffset);

	/* download */
	ret = update_download_image(fit, e);
	if (ret) {
		TFTPUD_E("\"%s\" download fail, ret=%d\n",
			 e->file_name, ret);
		goto out;
	}

	/* terminate gpt string */
	gpt_parts = (char *)e->buf;
	p = gpt_parts + e->size - 1;
	*p = '\0';

	/* write */
	printf("[TFTPUD-2]: Write gpt ...\n");
	printf("    %s\n\n", gpt_parts);
	env_set("gpt_parts", gpt_parts);
	ret = run_command("gpt write ${devtype} ${devnum} ${gpt_parts}", 0);
	if (ret) {
		printf("Failed to write gpt\n");
		ret = -EIO;
		goto out;
	}
	ret = run_command("gpt verify ${devtype} ${devnum} ${gpt_parts}", 0);
	if (ret) {
		printf("Failed to verify gpt\n");
		ret = -EIO;
		goto out;
	}
	printf("\n");
out:
	free(e);

	return ret;
}

static int do_tftp_full_update(cmd_tbl_t *cmdtp, int flag,
			       int argc, char * const argv[])
{
	struct local_information *local = &local_info;
	struct update_header *hdr = &update_hdr;
	struct image_element *e;
	struct list_head *node;
	const char *dir_part_str;
	const char *part_str;
	const char *dir_str;
	char *dup_str = NULL;
	u32 total_success = 0;
	u32 total_traverse = 0;
	ulong start_ms;
	ulong total_ms;
	void *fit;
	int ret;

	start_ms = get_timer(0);
	memset(hdr, 0, sizeof(*hdr));
	memset(local, 0, sizeof(*local));

	/* only handle a single partititon ? */
	if (argc > 1) {
		dir_part_str = argv[1];
		part_str = strchr(dir_part_str, ':');
		if (part_str) {
			/*
			 * eg: tftpupdate image:recovery
			 *     tftpupdate image:*
			 *     tftpupdate image:
			 */
			dup_str = strdup(dir_part_str);
			dup_str[part_str - dir_part_str] = 0;
			dir_str = dup_str;
			part_str++;
			if (*part_str == '*')
				part_str = NULL;
		} else {
			/* eg: tftpupdate recovery */
			dir_str = NULL;
			part_str = argv[1];
		}
	} else {
		dir_str = NULL;
		part_str = NULL;
	}

	server_dir = dir_str;
	hdr->spec_partition = part_str;
	INIT_LIST_HEAD(&hdr->images);

	fit = update_download_hdr(hdr);
	if (!fit) {
		TFTPUD_E("download hdr fail\n");
		ret = -EINVAL;
		goto out;
	}

	ret = update_verify_hdr(fit, hdr, local);
	if (ret) {
		TFTPUD_E("verify hdr fail, ret=%d\n", ret);
		goto out;
	}

	/* flash gpt table early than any other partition */
	ret = update_write_gpt(fit, hdr);
	if (ret) {
		TFTPUD_E("write gpt fail, ret=%d\n", ret);
		goto out;
	}

	ret = update_populate_image(fit, hdr);
	if (ret) {
		TFTPUD_E("populate image fail, ret=%d\n", ret);
		goto out;
	}

	list_for_each(node, &hdr->images) {
		e = list_entry(node, struct image_element, node);
		total_traverse++;

		/* ignore ? */
		if (update_ignore_image(fit, hdr, e))
			continue;

		ret = update_download_image(fit, e);
		if (ret) {
			TFTPUD_E("\"%s\" download fail, ret=%d\n",
				 e->file_name, ret);
			goto out;
		}

		ret = update_flash_image(e);
		if (ret) {
			TFTPUD_E("\"%s\" flash fail, ret=%d\n",
				 e->file_name, ret);
			goto out;
		}

		total_success++;
	}

	if (total_success == 0) {
		if (hdr->spec_partition) {
			TFTPUD_E("No %s partition was found\n", hdr->spec_partition);
			ret = CMD_RET_FAILURE;
		}
		goto out;
	}

	/* If this is full upgrade, update local info */
	if (!hdr->spec_partition)
		update_local_info(fit, hdr);
out:
	update_cleanup(fit, hdr);
	if (!ret) {
		total_ms = get_timer(start_ms);
		TFTPUD_I("tftpupdate is OK (total time: %lds, upgrade: %d/%d), "
			 "system reboot is recommend\n",
			 total_ms / 1000, total_success, total_traverse);
	}

	return ret ? CMD_RET_FAILURE : CMD_RET_SUCCESS;
}

U_BOOT_CMD(
	tftp_full_update, 2, 1, do_tftp_full_update,
	"Update a set of images organized with FIT via network using TFTP protocol",
	"[[server-dir:][partition]"
);

