#include <common.h>
#include <malloc.h>
#include <mmc.h>
#include <asm/arch/fw_info.h>

#include "layout.h"
#include "rtk_storage_layout.h"

#define CONFIG_FILE "config.txt"

#define EMMC_4G_SIZE 0x0E4000000
#define EMMC_8G_SIZE 0x1c8000000

#define TRACEF(str, x...) \
do { \
	printf("%s:%d: " str, __func__, __LINE__, ## x); \
} while (0)

#define LTRACEF debug

static struct fw_info *g_fw_info;

static struct fw_info g_mbr_fw_info[MAX_FW_INFO] = {
	{.index = 0, .id = FW_TYPE_RESERVED, 	.name ="reserved_1",
		.in_fwt = false, .is_use = false,
		.start_addr = 0x00630000, .bytes_size = 0x00000200}, /* 1K */
	{.index = 1, .id = FW_TYPE_GOLD_RESCUE_DT, 	.name = "GOLDrescueDT",
		.in_fwt = true, .is_use = false,
		.start_addr = 0x00630200, .bytes_size = 0x00040000}, /* 256K */
	{.index = 2, .id = FW_TYPE_GOLD_AUDIO, 		.name = "GOLDaudio",
		.in_fwt = true, .is_use = false,
		.start_addr = 0x00670200, .bytes_size = 0x00500000}, /* 5M */
	{.index = 3, .id = FW_TYPE_GOLD_KERNEL, 	.name = "GOLDKernel",
		.in_fwt = true, .is_use = false,
		.start_addr = 0x00B70200, .bytes_size = 0x01100000}, /* 17M */
	{.index = 4, .id = FW_TYPE_GOLD_RESCUE_ROOTFS, 		.name = "GOLDRootFS",
		.in_fwt = true, .is_use = false,
		.start_addr = 0x01B70200, .bytes_size = 0x00D00000}, /* 13M */
	{.index = 5, .id = FW_TYPE_RESCUE_DT, 		.name = "rescueDT",
		.in_fwt = true, .is_use = false,
		.start_addr = 0x02870200, .bytes_size = 0x00040000}, /* 256K */
	{.index = 6, .id = FW_TYPE_KERNEL_DT, 	.name = "kernelDT",
		.in_fwt = true, .is_use = false,
		.start_addr = 0x028B0200, .bytes_size = 0x00040000}, /* 256K */
	{.index = 7, .id = FW_TYPE_AUDIO, 		.name = "audioKernel",
		.in_fwt = true, .is_use = false,
		.start_addr = 0x028F0200, .bytes_size = 0x00338800}, /* 3M */
	{.index = 8, .id = FW_TYPE_KERNEL, 		.name = "linuxKernel",
		.in_fwt = true, .is_use = false,
		.start_addr = 0x02c28A00, .bytes_size = 0x01000000}, /* 16M */
	{.index = 9, .id = FW_TYPE_RESERVED, 	.name ="reserved_2",
		.in_fwt = false, .is_use = false,
		.start_addr = 0x03c28A00, .bytes_size = 0x00000200}, /* 1K */
	{.index = 10, .id = FW_TYPE_RESCUE_ROOTFS, 	.name = "rescueRootFS",
		.in_fwt = true, .is_use = false,
		.start_addr = 0x03c28c00, .bytes_size = 0x00C00000}, /* 12M */
	{.index = 11, .id = FW_TYPE_KERNEL_ROOTFS, 	.name = "kernelRootFS",
		.in_fwt = true, .is_use = false,
		.start_addr = 0x04828c00, .bytes_size = 0x00400000}, /* 4M */
	/* For Xen */
	{.index = 12, .id = FW_TYPE_HYP, .name = "XenOS",
		.in_fwt = true, .is_use = false,
		.start_addr = 0x4C28C00, .bytes_size = 0x000C0000},
	/* For LOGO */
	{.index = 13, .id = FW_TYPE_IMAGE_FILE, 		.name = "imageFile",
		.in_fwt = true, .is_use = false,
		.start_addr = 0x1a1800000, .bytes_size = 0x007e9000},
};

static struct fw_info g_gpt_fw_info[MAX_FW_INFO] = {
	{.index = 0, .id = FW_TYPE_RESERVED, 	.name ="reserved_1",
		.in_fwt = false, .is_use = false,
		.start_addr = 0x00630000, .bytes_size = 0x00000200}, /* 1K */
	{.index = 1, .id = FW_TYPE_GOLD_RESCUE_DT, 	.name = "GOLDrescueDT",
		.in_fwt = true, .is_use = false,
		.start_addr = 0x00630200, .bytes_size = 0x00040000}, /* 256K */
	{.index = 2, .id = FW_TYPE_GOLD_AUDIO, 		.name = "GOLDaudio",
		.in_fwt = true, .is_use = false,
		.start_addr = 0x00670200, .bytes_size = 0x00A00000}, /* 10M */
	{.index = 3, .id = FW_TYPE_GOLD_KERNEL, 	.name = "GOLDKernel",
		.in_fwt = true, .is_use = false,
		.start_addr = 0x01070200, .bytes_size = 0x02000000}, /* 32M */
	{.index = 4, .id = FW_TYPE_GOLD_RESCUE_ROOTFS, 	.name = "GOLDRootFS",
		.in_fwt = true, .is_use = false,
		.start_addr = 0x03070200, .bytes_size = 0x01400000}, /* 20M */
	{.index = 5, .id = FW_TYPE_RESCUE_DT, 		.name = "rescueDT",
		.in_fwt = true, .is_use = false,
		.start_addr = 0x04470200, .bytes_size = 0x00040000}, /* 256K */
	{.index = 6, .id = FW_TYPE_KERNEL_DT, 	.name = "kernelDT",
		.in_fwt = true, .is_use = false,
		.start_addr = 0x044B0200, .bytes_size = 0x00040000}, /* 256K */
	{.index = 7, .id = FW_TYPE_AUDIO, 		.name = "audioKernel",
		.in_fwt = true, .is_use = false,
		.start_addr = 0x044F0200, .bytes_size = 0x00A00000}, /* 10M */
	{.index = 8, .id = FW_TYPE_KERNEL, 		.name = "linuxKernel",
		.in_fwt = true, .is_use = false,
		.start_addr = 0x04ef0200, .bytes_size = 0x02000000}, /* 32M */
	{.index = 9, .id = FW_TYPE_RESERVED, 	.name ="reserved_2",
		.in_fwt = false, .is_use = false,
		.start_addr = 0x06ef0200, .bytes_size = 0x00000000}, /* 1K */
	{.index = 10, .id = FW_TYPE_RESCUE_ROOTFS, 	.name = "rescueRootFS",
		.in_fwt = true, .is_use = false,
		.start_addr = 0x06ef0200, .bytes_size = 0x01400000}, /* 20M */
	{.index = 11, .id = FW_TYPE_KERNEL_ROOTFS, 	.name = "kernelRootFS",
		.in_fwt = true, .is_use = false,
		.start_addr = 0x082f0200, .bytes_size = 0x00A00000}, /* 10M */
	/* For Xen */
	{.index = 12, .id = FW_TYPE_HYP, 		.name = "XenOS",
		.in_fwt = true, .is_use = false,
		.start_addr = 0x08cf0200, .bytes_size = 0x000C0000},
	/* For LOGO */
	{.index = 13, .id = FW_TYPE_IMAGE_FILE, 	.name = "imageFile",
		.in_fwt = true, .is_use = false,
		.start_addr = 0x1a1800000, .bytes_size = 0x007e9000},
};

static struct part_info *g_part_info;
/* default 4G emmc partition */
static struct part_info g_mbr_part_info[MAX_PART_INFO] = {
	{.index = 0, .id = PART_FW, 	.name = "fw_part",
		.mount = "",
		.type = PART_TYPE_FW, .fw_type = 0, .fw_count = 11,
		.in_fwt = true, .is_use = false,
		.start_addr = 0x00000000, .bytes_size = 0x00000000},
	{.index = 1, .id = PART_SYSTEM, 	.name = "system",
		.mount = "/system",
		.type = PART_TYPE_FS, .fw_type = FS_TYPE_EXT4, .fw_count = 1,
		.in_fwt = true, .is_use = false,
		.start_addr = 0x00000000, .bytes_size = 0x00000000},
	{.index = 2, .id = PART_DATA, 		.name = "data",
		.mount = "/data",
		.type = PART_TYPE_FS, .fw_type = FS_TYPE_EXT4, .fw_count = 1,
		.in_fwt = true, .is_use = false,
		.start_addr = 0x00000000, .bytes_size = 0x00000000},
	{.index = 3, .id = PART_CACHE, 		.name = "cache",
		.mount = "/cache",
		.type = PART_TYPE_FS, .fw_type = FS_TYPE_EXT4, .fw_count = 1,
		.in_fwt = true, .is_use = false,
		.start_addr = 0x00000000, .bytes_size = 0x00000000},
	{.index = 4, .id = PART_EXTEND, 	.name = "extend",
		.mount = "none",
		.type = PART_TYPE_FS, .fw_type = 0, .fw_count = 1,
		.in_fwt = false, .is_use = false,
		.start_addr = 0x00000000, .bytes_size = 0x00000000},
	{.index = 5, .id = PART_VENDOR, 	.name = "vendor",
		.mount = "/vendor",
		.type = PART_TYPE_FS, .fw_type = FS_TYPE_EXT4, .fw_count = 1,
		.in_fwt = true, .is_use = false,
		.start_addr = 0x00000000, .bytes_size = 0x00000000},
	{.index = 6, .id = PART_UBOOT, 		.name = "uboot",
		.mount = "/uboot",
		.type = PART_TYPE_FS, .fw_type = FS_TYPE_EXT4, .fw_count = 1,
		.in_fwt = true, .is_use = false,
		.start_addr = 0x00000000, .bytes_size = 0x00000000},
	{.index = 7, .id = PART_LOGO, 		.name = "logo",
		.mount = "/logo",
		.type = PART_TYPE_FS, .fw_type = FS_TYPE_EXT4, .fw_count = 1,
		.in_fwt = true, .is_use = false,
		.start_addr = 0x00000000, .bytes_size = 0x00000000},
	{.index = 8, .id = PART_BACKUP, 	.name = "backup",
		.mount = "/backup",
		.type = PART_TYPE_FS, .fw_type = FS_TYPE_EXT4, .fw_count = 1,
		.in_fwt = true, .is_use = false,
		.start_addr = 0x00000000, .bytes_size = 0x00000000},
	{.index = 9, .id = PART_VERIFY, 	.name = "verify",
		.mount = "/verify",
		.type = PART_TYPE_FS, .fw_type = FS_TYPE_EXT4, .fw_count = 1,
		.in_fwt = true, .is_use = false,
		.start_addr = 0x00000000, .bytes_size = 0x00000000},
	/* For OpenWRT */
	{.index = 10, .id = PART_ROOTFS, 	.name = "rootfs",
		.mount = "/",
		.type = PART_TYPE_FS, .fw_type = FS_TYPE_SQUASH, .fw_count = 1,
		.in_fwt = true, .is_use = false,
		.start_addr = 0x00000000, .bytes_size = 0x00000000},
	{.index = 11, .id = PART_ETC, 	.name = "etc",
		.mount = "etc",
		.type = PART_TYPE_FS, .fw_type = FS_TYPE_EXT4, .fw_count = 1,
		.in_fwt = true, .is_use = false,
		.start_addr = 0x00000000, .bytes_size = 0x00000000},
	/* For Xen */
	{.index = 12, .id = PART_XEN, 	.name = "xen",
		.mount = "/xen",
		.type = PART_TYPE_FS, .fw_type = 0, .fw_count = 1,
		.in_fwt = true, .is_use = false,
		.start_addr = 0x00000000, .bytes_size = 0x00000000},
};

static struct part_info g_gpt_part_info[MAX_PART_INFO] = {
	{.index = 0, .id = PART_SYSTEM, 	.name = "system",
		.mount = "/system",
		.type = PART_TYPE_FS, .fw_type = FS_TYPE_EXT4, .fw_count = 1,
		.in_fwt = true, .is_use = false,
		.start_addr = 0x00000000, .bytes_size = 0x00000000},
	{.index = 1, .id = PART_CACHE, 		.name = "cache",
		.mount = "/cache",
		.type = PART_TYPE_FS, .fw_type = FS_TYPE_EXT4, .fw_count = 1,
		.in_fwt = true, .is_use = false,
		.start_addr = 0x00000000, .bytes_size = 0x00000000},
	{.index = 2, .id = PART_VENDOR, 	.name = "vendor",
		.mount = "/vendor",
		.type = PART_TYPE_FS, .fw_type = FS_TYPE_EXT4, .fw_count = 1,
		.in_fwt = true, .is_use = false,
		.start_addr = 0x00000000, .bytes_size = 0x00000000},
	{.index = 3, .id = PART_UBOOT, 		.name = "uboot",
		.mount = "/uboot",
		.type = PART_TYPE_FS, .fw_type = FS_TYPE_EXT4, .fw_count = 1,
		.in_fwt = true, .is_use = false,
		.start_addr = 0x00000000, .bytes_size = 0x00000000},
	{.index = 4, .id = PART_LOGO, 		.name = "logo",
		.mount = "/logo",
		.type = PART_TYPE_FS, .fw_type = FS_TYPE_EXT4, .fw_count = 1,
		.in_fwt = true, .is_use = false,
		.start_addr = 0x00000000, .bytes_size = 0x00000000},
	{.index = 5, .id = PART_IMAGE, 		.name = "imageFile",
		.mount = "/imageFile",
		.type = PART_TYPE_FS, .fw_type = FS_TYPE_EXT4, .fw_count = 1,
		.in_fwt = true, .is_use = false,
		.start_addr = 0x00000000, .bytes_size = 0x00000000},
	{.index = 6, .id = PART_BACKUP, 	.name = "backup",
		.mount = "/backup",
		.type = PART_TYPE_FS, .fw_type = FS_TYPE_EXT4, .fw_count = 1,
		.in_fwt = true, .is_use = false,
		.start_addr = 0x00000000, .bytes_size = 0x00000000},
	{.index = 7, .id = PART_VERIFY, 	.name = "verify",
		.mount = "/verify",
		.type = PART_TYPE_FS, .fw_type = FS_TYPE_EXT4, .fw_count = 1,
		.in_fwt = true, .is_use = false,
		.start_addr = 0x00000000, .bytes_size = 0x00000000},
	{.index = 8, .id = PART_MISC, 		.name = "misc",
		.mount = "/misc",
		.type = PART_TYPE_FS, .fw_type = FS_TYPE_EXT4, .fw_count = 1,
		.in_fwt = true, .is_use = false,
		.start_addr = 0x00000000, .bytes_size = 0x00000000},
	{.index = 9, .id = PART_DATA, 		.name = "data",
		.mount = "/data",
		.type = PART_TYPE_FS, .fw_type = FS_TYPE_EXT4, .fw_count = 1,
		.in_fwt = true, .is_use = false,
		.start_addr = 0x00000000, .bytes_size = 0x00000000},
	/* For OpenWRT */
	{.index = 10, .id = PART_ROOTFS, 	.name = "rootfs",
		.mount = "/",
		.type = PART_TYPE_FS, .fw_type = FS_TYPE_SQUASH, .fw_count = 1,
		.in_fwt = true, .is_use = false,
		.start_addr = 0x00000000, .bytes_size = 0x00000000},
	{.index = 11, .id = PART_ETC, 	.name = "etc",
		.mount = "etc",
		.type = PART_TYPE_FS, .fw_type = FS_TYPE_EXT4, .fw_count = 1,
		.in_fwt = true, .is_use = false,
		.start_addr = 0x00000000, .bytes_size = 0x00000000},
	/* For Xen */
	{.index = 12, .id = PART_XEN, 	.name = "xen",
		.mount = "/xen",
		.type = PART_TYPE_FS, .fw_type = 0, .fw_count = 1,
		.in_fwt = true, .is_use = false,
		.start_addr = 0x00000000, .bytes_size = 0x00000000},
};

struct part_info *get_part_info(const char *name)
{
	int i;
	LTRACEF("Find part info for %s\n", name);
	for (i = 0; i < MAX_PART_INFO; i++) {
		if (!strncmp(name, g_part_info[i].name,
				strlen(g_part_info[i].name))) {
			LTRACEF("Get part info by name: %s\n",
				g_part_info[i].name);
			return &g_part_info[i];
		} else if (g_part_info[i].path && !strncmp(name, g_part_info[i].path,
				strlen(g_part_info[i].path))) {
			LTRACEF("Get part info by path: %s\n",
				g_part_info[i].name);
			return &g_part_info[i];
		}
	}

	return NULL;
}

struct fw_info *get_fw_info(const char *name)
{
	int i;
	LTRACEF("Find fw info for %s\n", name);
	for (i = 0; i < MAX_FW_INFO; i++) {
		if (!strncmp(name, g_fw_info[i].name,
				strlen(g_fw_info[i].name))) {
			LTRACEF("Get fw info by name: %s\n",
					g_fw_info[i].name);
			return &g_fw_info[i];
		} else if (g_fw_info[i].path && !strncmp(name, g_fw_info[i].path,
				strlen(g_fw_info[i].path))) {
			LTRACEF("Get fw info by path: %s\n",
					g_fw_info[i].name);
			return &g_fw_info[i];
		}
	}
	return NULL;
}

struct fw_info *get_fw_info_next(struct fw_info *fw)
{
	int index;

	LTRACEF("Find next fw info from %s index %d\n",
		    fw->name, fw->index);
	index = fw->index + 1;
	if (index < MAX_FW_INFO) {
		LTRACEF("Get next fw info %s index %d\n",
			    g_fw_info[index].name, index);
		return &g_fw_info[index];
	}
	return NULL;
}

struct part_info *get_part_info_by_mount(char *mount)
{
	int index;
	struct part_info *info;
	LTRACEF("Find part info by mount %s\n",
		    mount);
	for (index = 0; index < MAX_PART_INFO; index++) {
		info = &g_part_info[index];
		if (!strcmp(mount, info->mount)) {
			LTRACEF("Get part info %s by mount %s\n",
				    info->name, info->mount);
			return info;
		}
	}
	return NULL;
}

#ifdef CONFIG_RTK_MMC
extern unsigned char* ext_csd;
#endif

uint64_t get_emmc_size(void)
{
	uint64_t capacity = 0;

#ifdef CONFIG_RTK_MMC
	capacity = ext_csd[EXT_CSD_SEC_CNT] << 0
		    | ext_csd[EXT_CSD_SEC_CNT + 1] << 8
		    | ext_csd[EXT_CSD_SEC_CNT + 2] << 16
		    | ext_csd[EXT_CSD_SEC_CNT + 3] << 24;
	capacity *= 512;
	printf("%s eMMC capacity = %llx\n", __func__, capacity);
#endif
	return capacity;
}

__maybe_unused
int adjust_partition_size(void)
{
	struct part_info *pinfo = NULL;
	int i;
	size_t storage_size = EMMC_4G_SIZE;
	uint64_t emmc_size = get_emmc_size();
	uint64_t end_addr;

	if (emmc_size >= EMMC_8G_SIZE) {
		TRACEF("For 8G emmc adjust partition (size=0x%llx)\n",
			emmc_size);
		storage_size = EMMC_8G_SIZE;
	}

	end_addr = storage_size;

	for (i = MAX_PART_INFO - 1; 0 <= i; i--) {
		pinfo = &g_part_info[i];
		if (pinfo->id == PART_DATA &&
			    pinfo->bytes_size > (size_t)emmc_size) {
			TRACEF("data image size (0x%lx) > 0x%x, fix it\n",
				pinfo->bytes_size, EMMC_4G_SIZE);
			pinfo->bytes_size -= EMMC_4G_SIZE;
		}
		if (pinfo->id == PART_FW) {
			/* first fw paratition */
			pinfo->bytes_size = end_addr;
			pinfo->start_addr = 0;
			end_addr = pinfo->start_addr;
		} else if (pinfo->id == PART_EXTEND) {
			pinfo->start_addr = end_addr;
			pinfo->bytes_size = storage_size - pinfo->start_addr;
		} else {
			pinfo->start_addr = end_addr - pinfo->bytes_size;
			end_addr = pinfo->start_addr;
		}

		TRACEF("Partition %s start addr 0x%llx size 0x%lx\n",
			    pinfo->name, pinfo->start_addr, pinfo->bytes_size);
	}

	return 0;
}

__maybe_unused
int adjust_gpt_partition_size(void)
{
	struct part_info *pinfo = NULL;
	int i;
	size_t storage_size = EMMC_4G_SIZE;
	uint64_t emmc_size = get_emmc_size();
	uint64_t end_addr;
	unsigned long logo_start=0, logo_size=0;

	if (emmc_size >= EMMC_GPT_8G_MAX) {
		TRACEF("For 8G emmc adjust partition (size=0x%llx)\n", emmc_size);
		storage_size = EMMC_GPT_8G_MAX;
	}

	end_addr = storage_size;
	for (i=0; i<MAX_PART_INFO; i++) {
		pinfo = &g_part_info[i];
		if (pinfo->id == PART_DATA &&
			    pinfo->bytes_size > (size_t)emmc_size) {
			TRACEF("data image size (0x%lx) > 0x%x, fix it\n",
				pinfo->bytes_size, EMMC_4G_SIZE);
			pinfo->bytes_size -= EMMC_4G_SIZE;
		}
		if (pinfo->id == PART_SYSTEM) {
			pinfo->start_addr = 0x8cf0200;
			end_addr = pinfo->start_addr + pinfo->bytes_size;
		} else if(pinfo->id == PART_DATA) {
			pinfo->start_addr = end_addr;
			pinfo->bytes_size = EMMC_GPT_8G_SIZE - pinfo->start_addr;
			end_addr = pinfo->start_addr + pinfo->bytes_size;
		} else if(pinfo->id == PART_LOGO) {
			pinfo->start_addr = end_addr;
			end_addr = pinfo->start_addr + pinfo->bytes_size;
			logo_start = pinfo->start_addr;
			logo_size = pinfo->bytes_size;
		} else if(pinfo->id == PART_IMAGE) {
			pinfo->start_addr = logo_start;
			pinfo->bytes_size = logo_size;
			pinfo->is_use = true;
		} else {
			pinfo->start_addr = end_addr;
			end_addr = pinfo->start_addr + pinfo->bytes_size;
		}
		LTRACEF("%s start = 0x%llx, size = 0x%lx\n", pinfo->name, pinfo->start_addr, pinfo->bytes_size);
	}
	return 0;
}

__maybe_unused
static void debug_dump_partition_info(void)
{
	int i;
	struct part_info *pinfo;
	for (i = 0; i < MAX_PART_INFO; i++) {
		pinfo = &g_part_info[i];
		LTRACEF("part_info #%d: id=%d, name=%s, path=%s, mount=%s, "
				"fs_type=%s\n", i, pinfo->id, pinfo->name, pinfo->path,
				pinfo->mount, pinfo->fs_type);
		LTRACEF("part_info: mbr_addr=0x%llx mbr@%p, mbr_index=%d, "
				"is_extend=%x\n",
				pinfo->mbr_addr, pinfo->mbr, pinfo->mbr_index,
				pinfo->is_extend);
		LTRACEF("part_info: start_addr=0x%llx, start_block=0x%llx, "
				"bytes_size=0x%lx, block_size=0x%lx\n",
				pinfo->start_addr, pinfo->start_block,
				pinfo->bytes_size, pinfo->block_size);
	}
}

size_t dump_part_info(char *buf, size_t buf_sz)
{
	size_t count = 0;
	int i;

	struct part_info *pinfo;
	for (i = 0; i < MAX_PART_INFO; i++) {
		pinfo = &g_part_info[i];
		count += snprintf(buf + count, buf_sz - count,
			    "part_info #%d: id=%d, name=%s,\n path=%s,\n mount=%s, "
			    "fs_type=%s\n", i, pinfo->id, pinfo->name, pinfo->path,
			    pinfo->mount, pinfo->fs_type);
		count += snprintf(buf + count, buf_sz - count,
			    "part_info: mbr_addr=0x%llx mbr@%p,\n mbr_index=%d, "
			    "is_extend=%x\n",
			    pinfo->mbr_addr, pinfo->mbr, pinfo->mbr_index,
			    pinfo->is_extend);
		count += snprintf(buf + count, buf_sz - count,
			    "part_info: start_addr=0x%llx, start_block=0x%llx,\n "
			    "bytes_size=0x%lx, block_size=0x%lx\n",
			    pinfo->start_addr, pinfo->start_block,
			    pinfo->bytes_size, pinfo->block_size);
	}	return count;
}

__maybe_unused
static void debug_dump_fw_info(void)
{
	int i;
	struct fw_info *fw;
	for (i = 0; i < MAX_FW_INFO; i++) {
		fw = &g_fw_info[i];
		LTRACEF("fw_info #%d: id=%d, name=%s, path=%s\n",
				i, fw->id, fw->name, fw->path);
		LTRACEF("fw_info: start_addr=0x%llx, start_block=0x%llx, "
				"bytes_size=0x%lx, block_size=0x%lx, load_addr=0x%llx\n",
				fw->start_addr, fw->start_block, fw->bytes_size,
				fw->block_size, fw->load_addr);
	}
}

size_t dump_fw_info(char *buf, size_t buf_sz)
{
	size_t count = 0;

	int i;
	struct fw_info *fw;
	for (i = 0; i < MAX_FW_INFO; i++) {
		fw = &g_fw_info[i];
		count += snprintf(buf + count, buf_sz - count,
			    "fw_info #%d: id=%d, name=%s,\n path=%s\n",
			    i, fw->id, fw->name, fw->path);
		count += snprintf(buf + count, buf_sz - count,
			    "fw_info: start_addr=0x%llx, start_block=0x%llx,\n "
			    "bytes_size=0x%lx, block_size=0x%lx, load_addr=0x%llx\n",
			    fw->start_addr, fw->start_block, fw->bytes_size,
			    fw->block_size, fw->load_addr);
	}

	return count;
}

static int parse_config_file(void *file, unsigned file_size)
{
	char *config_txt = (char *)file;
	char *ptr = config_txt;
	char *next;

	LTRACEF("START ... \n");
	while (ptr) {
		char newline[256] = {0};
		char *newline_p = NULL;
		int count = 0;
		ptr++;

		next = strpbrk(ptr, "\n");
		if (next)
			count = (int) (next - ptr);
		strncpy(newline, ptr, count);

		LTRACEF("Parse new line (count %d) %s\n", count, newline);
		if (!strncmp(newline, "fw", 2)) {
			struct fw_info *fw;

			LTRACEF("Parse fw info: %s\n", newline);
			/* skip "fw = " */
			newline_p = &newline[strlen("fw = ")];
			fw = get_fw_info(newline_p);
			if (fw) {
				char *tmp;
				size_t len;
				newline_p += strlen(fw->name);
				newline_p ++;
				tmp = strchr(newline_p, ' ');
				len = tmp - newline_p;
				if (!fw->path)
					fw->path = malloc(len + 1);
				memset(fw->path, 0, len + 1);
				memcpy(fw->path, newline_p, len);
				newline_p += len;
				newline_p += 3;
				fw->load_addr = (uint64_t)simple_strtol(newline_p ,0, 16);
				fw->is_use = true;
				TRACEF("Set fw info id %d, name %s, path %s, "
						"load to load_addr 0x%llx\n",
						fw->id, fw->name, fw->path, fw->load_addr);
			}
		} else if (!strncmp(newline, "part", 4)) {
			struct part_info *part;

			LTRACEF("Parse part info: %s\n", newline);
			/* skip "part = " */
			newline_p = &newline[strlen("part = ")];
			part = get_part_info(newline_p);
			if (part) {
				char *tmp;
				size_t len;
				newline_p += strlen(part->name);
				newline_p ++;
				tmp = strchr(newline_p, ' ');
				len = tmp - newline_p;
				if (strncmp(part->mount, newline_p, len)) {
					LTRACEF("part->mount %s len %d, newline_p %s\n",
						    part->mount, (int)len, newline_p);
					memset(part->mount, '\0', 32);
					memcpy(part->mount, newline_p, len);
				}
				newline_p += len;
				newline_p ++;
				tmp = strchr(newline_p, ' ');
				len = tmp - newline_p;
				if (!part->fs_type)
					part->fs_type = malloc(len + 1);
				memset(part->fs_type, 0, len + 1);
				memcpy(part->fs_type, newline_p, len);
				if (!strcmp(part->fs_type, "ext4"))
					part->fw_type = FS_TYPE_EXT4;
				else if (!strcmp(part->fs_type, "squash"))
					part->fw_type = FS_TYPE_SQUASH;
				part->fw_count = 1;
				newline_p += len;
				newline_p ++;
				tmp = strchr(newline_p, ' ');
				len = tmp - newline_p;
				if (!part->path)
					part->path = malloc(len + 1);
				memset(part->path, 0, len + 1);
				memcpy(part->path, newline_p, len);
				newline_p += len;
				newline_p ++;

				part->bytes_size = (size_t)simple_strtol(newline_p ,0, 10);
				part->length = part->bytes_size;
				part->is_use = true;
				TRACEF("Set part info id %d, name %s, path %s, "
						"size 0x%lx bytes\n",
						part->id, part->name, part->path, part->bytes_size);
			}
		}
		ptr = next;
	}
	return 0;
}

static int build_layout_table(int type)
{
	if (type == PART_TBL_GPT)
		adjust_gpt_partition_size();
	else
		adjust_partition_size();
	build_fw_table(g_fw_info, g_part_info);

	build_part_table(type, g_fw_info, g_part_info);

	debug_dump_fw_info();
	debug_dump_partition_info();

	LTRACEF("END ...\n");
	return 0;
}

int read_storage_layout_info(int part_type)
{
	/* read fw table and part table from storage */
	LTRACEF("read_storage_layout_info\n");

	read_fw_info(g_fw_info, g_part_info);

	read_part_info(part_type, g_part_info);

	return 0;
}

/* write layout table, fw image, part image to storage */
int write_to_storage(const char *arg,  uint32_t type, uint64_t file_size, uint64_t offset,
		void *data, unsigned sz)
{
	struct part_info *part;
	struct fw_info *fw;
	int part_type;

	LTRACEF("write_to_storage arg %s "
		    "file_size=%lld, offset=0x%llx, data@%p, sz=%d\n",
		    arg, file_size, offset, data, sz);
	if(type == BUILD_GPT) {
		LTRACEF("Force GPT table\n");
		part_type = PART_TBL_GPT;
		g_part_info = g_gpt_part_info;
		g_fw_info = g_gpt_fw_info;
	} else if(type == BUILD_MBR) {
		LTRACEF("Force MBR table\n");
		part_type = PART_TBL_MBR;
		g_part_info = g_mbr_part_info;
		g_fw_info = g_mbr_fw_info;
	} else {
		part_type = check_part_table_type();
		if(part_type == PART_TBL_MBR) {
			LTRACEF("Use origin MBR table");
			g_part_info = g_mbr_part_info;
			g_fw_info = g_mbr_fw_info;
		} else {
			LTRACEF("Use origin GPT table");
			g_part_info = g_gpt_part_info;
			g_fw_info = g_gpt_fw_info;
		}
	}
	if (!strcmp(arg, CONFIG_FILE)) {
		LTRACEF("build_memory_layout_table %s size 0x%x\n",
				arg, sz);
		/* For config.txt */
		parse_config_file(data, sz);
		build_layout_table(part_type);
		LTRACEF("build_memory_layout_table OK ...\n");
		return 0;
	}

	part = get_part_info(arg);
	if (part) {
		LTRACEF("flash part image %s (data size 0x%08x "
				"@0x%08llx/0x%08llx)\n",
				part->name, sz, offset, file_size);
		read_storage_layout_info(part_type);
		if(part_type == PART_TBL_GPT &&
			(strcmp(part->name, "data")==0 || strcmp(part->name, "cache")==0)) {
			if(offset == 0)
				destroy_partition_img(part);
			LTRACEF("skip data or cache partition\n");
			return 0;
		}
		if (part->is_use)
			write_partition_img(part, file_size, offset, data, sz);
		return 0;
	}
	fw = get_fw_info(arg);
	if (fw) {
		LTRACEF("flash fw image %s (data size 0x%08x "
				"@0x%08llx/0x%08llx)\n",
				fw->name, sz, offset, file_size);
		read_storage_layout_info(part_type);
		if (fw->is_use)
			write_fw_img(fw, file_size, offset, data, sz);
		return 0;
	}

	return 0;
}

#ifdef CONFIG_RTK_MMC
extern int rtk_eMMC_read(unsigned int blk_addr,
	    unsigned int data_size, unsigned int * buffer);
extern int rtk_eMMC_write(unsigned int blk_addr,
	    unsigned int data_size, unsigned int * buffer);
#endif

/* real to real/write storage */
int storage_write(uint64_t start_addr, uint64_t data_size, void *data)
{
	uint32_t block_addr;
	int ret = 0;

	flush_cache((unsigned long)data, data_size);

#ifdef CONFIG_RTK_MMC
	block_addr = start_addr / EMMC_BLOCK_SIZE;
	ret = rtk_eMMC_write(block_addr, (uint32_t)data_size, data);

	LTRACEF("start_addr 0x%llx block_addr 0x%x data size 0x%llx "
		    "ret 0x%x (bytes_size = 0x%x)\n",
		    start_addr, block_addr, data_size,
		    ret, ret * EMMC_BLOCK_SIZE);

	/* transfer to byte size */
	ret *= EMMC_BLOCK_SIZE;
#else
	ret = -1;
	error("No emmc driver support!\n");
#endif

	return ret;

}

int storage_read(uint64_t start_addr, uint64_t data_size, void *data)
{
	uint32_t block_addr;
	int ret = 0;

#ifdef CONFIG_RTK_MMC
	block_addr = start_addr / EMMC_BLOCK_SIZE;
	ret = rtk_eMMC_read(block_addr, (uint32_t)data_size, data);

	LTRACEF("start_addr 0x%llx block_addr 0x%x data size 0x%llx "
		    "ret 0x%x ( bytes_size = 0x%x)\n",
		    start_addr, block_addr, data_size,
		    ret, ret * EMMC_BLOCK_SIZE);
	/* transfer to byte size */
	ret *= EMMC_BLOCK_SIZE;
#else
	ret = -1;
	error("No emmc driver support!\n");
#endif
	flush_cache((unsigned long)data, data_size);

	return ret;
}
