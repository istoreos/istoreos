#include <common.h>
#include <malloc.h>
#include <errno.h>

#include <asm/arch/mcp.h>
#include <asm/arch/fw_info.h>

#include "layout.h"

#define MAX_TMP_BUF_SIZE 1024

#define TRACEF(str, x...) \
do { \
	printf("%s:%d: " str, __func__, __LINE__, ## x); \
} while (0)

#define LTRACEF debug

#define CACHE_LINE CONFIG_SYS_CACHELINE_SIZE

#define EMMC_BOOTCODE_AREA_SIZE 0x220000
#define FACTORY_SIZE CONFIG_FACTORY_SIZE
#define FW_TABLE_SIZE CONFIG_FW_TABLE_SIZE
#define flash_blk_size EMMC_BLOCK_SIZE

extern BOOT_MODE boot_mode;

static uint64_t fw_desc_table_start = 0; // Start address in block device
static void *fw_desc_table_ddr_base = 0; // load address in DDR
static size_t fw_desc_table_max_size = 32*1024; // 32kB

static int get_fwtbl_start_address(uint64_t *fwtb_start_addr)
{
	*fwtb_start_addr = 0;

	if (boot_flash_type == BOOT_EMMC) {
		if (boot_mode == BOOT_GOLD_MODE)
			*fwtb_start_addr = EMMC_BOOTCODE_AREA_SIZE + FACTORY_SIZE
					+ FW_TABLE_SIZE;
		else
			*fwtb_start_addr = EMMC_BOOTCODE_AREA_SIZE + FACTORY_SIZE;
	} else {
		TRACEF("boot_flash_type %d not support!!\n",
				boot_flash_type);
		return -1;
	}

	// Allocate size that is align to NAND page.
	if (!fw_desc_table_ddr_base) {
		fw_desc_table_ddr_base = memalign(CACHE_LINE,
				fw_desc_table_max_size);
	}
	if (!fw_desc_table_ddr_base) {
		TRACEF("ERROR! %s NO memory!!\n", __func__);
		return -ENOMEM;
	}

	return 0;
}

static const char *get_fw_type_str(int type)
{
	static const char *default_str = "";
	static const char *str;

	str = default_str;

	switch (type) {
	case FW_TYPE_RESERVED:
		str = "FW_TYPE_RESERVED";
		break;
	case FW_TYPE_BOOTCODE:
		str = "FW_TYPE_BOOTCODE";
		break;
	case FW_TYPE_KERNEL:
		str = "FW_TYPE_KERNEL";
		break;
	case FW_TYPE_RESCUE_DT:
		str = "FW_TYPE_RESCUE_DT";
		break;
	case FW_TYPE_KERNEL_DT:
		str = "FW_TYPE_KERNEL_DT";
		break;
	case FW_TYPE_RESCUE_ROOTFS:   //5
		str = "FW_TYPE_RESCUE_ROOTFS";
		break;
	case FW_TYPE_KERNEL_ROOTFS:
		str = "FW_TYPE_KERNEL_ROOTFS";
		break;
	case FW_TYPE_AUDIO:
		str = "FW_TYPE_AUDIO";
		break;
	case FW_TYPE_AUDIO_FILE: break;
	case FW_TYPE_VIDEO_FILE: break;
	case FW_TYPE_EXT4: break;        //10
	case FW_TYPE_UBIFS: break;
	case FW_TYPE_SQUASH: break;
	case FW_TYPE_EXT3: break;
	case FW_TYPE_ODD: break;
	case FW_TYPE_YAFFS2: break;      //15
	case FW_TYPE_ISO: break;
	case FW_TYPE_SWAP: break;
	case FW_TYPE_NTFS: break;
	case FW_TYPE_JFFS2: break;
	case FW_TYPE_IMAGE_FILE:     //20
		str = "FW_TYPE_IMAGE_FILE";
		break;
	case FW_TYPE_IMAGE_FILE1: break;
	case FW_TYPE_IMAGE_FILE2: break;
	case FW_TYPE_AUDIO_FILE1: break;
	case FW_TYPE_AUDIO_FILE2: break;
	case FW_TYPE_VIDEO_FILE1: break;     //25
	case FW_TYPE_VIDEO_FILE2: break;
	case FW_TYPE_VIDEO: break;
	case FW_TYPE_VIDEO2: break;
	case FW_TYPE_ECPU: break;
	case FW_TYPE_TEE: break;         //30
	case FW_TYPE_GOLD_KERNEL:
		str = "FW_TYPE_GOLD_KERNEL";
		break;
	case FW_TYPE_GOLD_RESCUE_DT:
		str = "FW_TYPE_GOLD_RESCUE_DT";
		break;
	case FW_TYPE_GOLD_RESCUE_ROOTFS:
		str = "FW_TYPE_GOLD_RESCUE_ROOTFS";
		break;
	case FW_TYPE_GOLD_AUDIO:
		str = "FW_TYPE_GOLD_AUDIO";
		break;
	case FW_TYPE_GOLD_TEE: break;        //35
	case FW_TYPE_CONFIG: break;
	case FW_TYPE_UBOOT: break;
	case FW_TYPE_BL31: break;
	case FW_TYPE_HYP: break;
	case FW_TYPE_GOLD_BL31: break;
	case FW_TYPE_RSA_KEY_FW: break;
	case FW_TYPE_RSA_KEY_TEE: break;
/*
	case FW_TYPE_LK: break; //43
	case FW_TYPE_RESCUE_LK:
		str = "FW_TYPE_RESCUE_LK";
		break;
	case FW_TYPE_RESCUE_AUDIO:
		str = "FW_TYPE_RESCUE_AUDIO";
		break;
	case FW_TYPE_RESCUE_TEE:
		str = "FW_TYPE_RESCUE_TEE";
		break;
	case FW_TYPE_RESCUE_BL31: break;
	case FW_TYPE_RESCUE_KERNEL:
		str = "FW_TYPE_RESCUE_KERNEL";
		break;
*/
	default:
		str = default_str;
		break;
	}

	return str;
}

size_t dump_fw_desc_table_v1(char *_buf, size_t _buf_sz,
	    fw_desc_table_v1_t *fw_desc_table_v1)
{
	size_t buf_sz, count = 0;
	char *buf;

	if (_buf) {
		buf = _buf;
		buf_sz = _buf_sz;
	} else {
		buf_sz = MAX_TMP_BUF_SIZE;
		buf = malloc(buf_sz);
		if (!buf) {
			TRACEF("ERROR! %s NO memory!!\n", __func__);
			return -ENOMEM;
		}
		memset(buf, '\0', buf_sz);
	}

	if (fw_desc_table_v1 != NULL) {
		count += snprintf(buf + count, buf_sz - count,
			    "## Fw Desc Table ##############################\n");
		count += snprintf(buf + count, buf_sz - count,
			    "## fw_desc_table_v1                = %8p\n",
			    fw_desc_table_v1);
		count += snprintf(buf + count, buf_sz - count,
			    "## fw_desc_table_v1->signature     = %s\n",
				 fw_desc_table_v1->signature);
		count += snprintf(buf + count, buf_sz - count,
			    "## fw_desc_table_v1->checksum      = 0x%08x\n",
			    fw_desc_table_v1->checksum);
		count += snprintf(buf + count, buf_sz - count,
			    "## fw_desc_table_v1->version       = 0x%08x\n",
			    fw_desc_table_v1->version);
		count += snprintf(buf + count, buf_sz - count,
			    "## fw_desc_table_v1->paddings      = 0x%08x\n",
			    fw_desc_table_v1->paddings);
		count += snprintf(buf + count, buf_sz - count,
			    "## fw_desc_table_v1->part_list_len = 0x%08x\n",
			    fw_desc_table_v1->part_list_len);
		count += snprintf(buf + count, buf_sz - count,
			    "## fw_desc_table_v1->fw_list_len   = 0x%08x\n",
			    fw_desc_table_v1->fw_list_len);
		count += snprintf(buf + count, buf_sz - count,
			    "###############################################\n\n");
	} else {
		count += snprintf(buf + count, buf_sz - count,
			    "## fw_desc_table_v1 is NULL.\n");
	}

	if (count >= buf_sz)
		TRACEF("[ERR] count %d >= buf_sz %d\n",
			    (int)count, (int)buf_sz);

	if (!_buf) {
		char *print_buf = malloc(++count);
		if (!print_buf) {
			TRACEF("ERROR! %s NO memory!!\n", __func__);
			return -ENOMEM;
		}
		memset(print_buf, '\0', count);
		memcpy(print_buf, buf, count);
		LTRACEF("\n%s", print_buf);
		free(print_buf);
		free(buf);
	}

	return count;
}

size_t dump_part_desc_entry_v1(char *_buf, size_t _buf_sz,
	    part_desc_entry_v1_t *part_entry)
{
	size_t buf_sz, count = 0;
	char *buf;

	if (_buf) {
		buf = _buf;
		buf_sz = _buf_sz;
	} else {
		buf_sz = MAX_TMP_BUF_SIZE;
		buf = malloc(buf_sz);
		if (!buf) {
			TRACEF("ERROR! %s NO memory!!\n", __func__);
			return -ENOMEM;
		}

		memset(buf, '\0', buf_sz);
	}

	if (part_entry != NULL) {
		count += snprintf(buf + count, buf_sz - count,
			    "## Part Desc Entry ############################\n");
		count += snprintf(buf + count, buf_sz - count,
			    "## part_entry                      = %8p\n",
			    part_entry);
		count += snprintf(buf + count, buf_sz - count,
			    "## part_entry->type (1:fw, 2:fs)   = 0x%08x\n",
			    part_entry->type);
		count += snprintf(buf + count, buf_sz - count,
			    "## part_entry->ro                  = 0x%08x\n",
			    part_entry->ro);
		count += snprintf(buf + count, buf_sz - count,
			    "## part_entry->length              = 0x%08llx\n",
			    part_entry->length);
		count += snprintf(buf + count, buf_sz - count,
			    "## part_entry->fw_count            = 0x%08x\n",
			    part_entry->fw_count);
		count += snprintf(buf + count, buf_sz - count,
			    "## part_entry->fw_type             = 0x%08x\n",
			    part_entry->fw_type);
#ifdef CONFIG_SYS_RTK_EMMC_FLASH
		count += snprintf(buf + count, buf_sz - count,
			    "## part_entry->emmc_partIdx        = 0x%08x\n",
			    part_entry->emmc_partIdx);
#endif
		count += snprintf(buf + count, buf_sz - count,
			    "## part_entry->mount_point         = %s\n",
			    part_entry->mount_point);
		count += snprintf(buf + count, buf_sz - count,
			    "###############################################\n\n");
	} else {
		count += snprintf(buf + count, buf_sz - count,
			    "## part_entry is NULL.\n");
	}

	if (count >= buf_sz)
		TRACEF("[ERR] count %d >= buf_sz %d\n",
			    (int)count, (int)buf_sz);

	if (!_buf) {
		char *print_buf = malloc(++count);
		if (!print_buf) {
			TRACEF("ERROR! %s NO memory!!\n", __func__);
			return -ENOMEM;
		}
		memset(print_buf, '\0', count);
		memcpy(print_buf, buf, count);
		LTRACEF("\n%s", print_buf);
		free(print_buf);
		free(buf);
	}

	return count;
}

size_t dump_fw_desc_entry_v1(char *_buf, size_t _buf_sz,
	    fw_desc_entry_v1_t *fw_entry)
{
	size_t buf_sz, count = 0;
	char *buf;

	if (_buf) {
		buf = _buf;
		buf_sz = _buf_sz;
	} else {
		buf_sz = MAX_TMP_BUF_SIZE;
		buf = malloc(buf_sz);
		if (!buf) {
			TRACEF("ERROR! %s NO memory!!\n", __func__);
			return -ENOMEM;
		}
		memset(buf, '\0', buf_sz);
	}

	if (fw_entry != NULL) {
		count += snprintf(buf + count, buf_sz - count,
			    "## Fw Desc Entry ##############################\n");
		count += snprintf(buf + count, buf_sz - count,
			    "## Fw type %s\n", get_fw_type_str(fw_entry->type));
		count += snprintf(buf + count, buf_sz - count,
			    "## fw_entry                        = %8p\n", fw_entry);
		count += snprintf(buf + count, buf_sz - count,
			    "## fw_entry->type                  = 0x%08x\n",
			    fw_entry->type);
		count += snprintf(buf + count, buf_sz - count,
			    "## fw_entry->lzma                  = 0x%08x\n",
			    fw_entry->lzma);
		count += snprintf(buf + count, buf_sz - count,
			    "## fw_entry->ro                    = 0x%08x\n",
			    fw_entry->ro);
		count += snprintf(buf + count, buf_sz - count,
			    "## fw_entry->version               = 0x%08x\n",
			    fw_entry->version);
		count += snprintf(buf + count, buf_sz - count,
			    "## fw_entry->target_addr (in DDR)  = 0x%08x\n",
			    (int)fw_entry->target_addr);
		count += snprintf(buf + count, buf_sz - count,
			    "## fw_entry->offset (in storage)   = 0x%08x\n",
			    fw_entry->offset);
		count += snprintf(buf + count, buf_sz - count,
			    "## fw_entry->length (in storage)   = 0x%08x\n",
			    fw_entry->length);
		count += snprintf(buf + count, buf_sz - count,
			    "## fw_entry->paddings (in storage) = 0x%08x\n",
			    fw_entry->paddings);
		count += snprintf(buf + count, buf_sz - count,
			    "## fw_entry->checksum              = 0x%08x\n",
				 fw_entry->checksum);
		count += snprintf(buf + count, buf_sz - count,
			    "###############################################\n\n");
	} else {
		count += snprintf(buf + count, buf_sz - count,
			    "## fw_entry is NULL.\n");
	}

	if (count >= buf_sz)
		TRACEF("[ERR] count %d >= buf_sz %d\n",
			    (int)count, (int)buf_sz);

	if (!_buf) {
		char *print_buf = malloc(++count);
		if (!print_buf) {
			TRACEF("ERROR! %s NO memory!!\n", __func__);
			return -ENOMEM;
		}
		memset(print_buf, '\0', count);
		memcpy(print_buf, buf, count);
		LTRACEF("\n%s", print_buf);
		free(print_buf);
		free(buf);
	}

	return count;
}

size_t dump_fw_desc_entry_v2(char *_buf, size_t _buf_sz,
	    fw_desc_entry_v2_t *fw_entry)
{
	size_t buf_sz, count = 0;
	char *buf;
	int i;

	if (_buf) {
		buf = _buf;
		buf_sz = _buf_sz;
	} else {
		buf_sz = MAX_TMP_BUF_SIZE;
		buf = malloc(buf_sz);
		if (!buf) {
			TRACEF("ERROR! %s NO memory!!\n", __func__);
			return -ENOMEM;
		}
		memset(buf, '\0', buf_sz);
	}

	if (fw_entry != NULL) {
		count += snprintf(buf + count, buf_sz - count,
			    "## Fw Desc Entry ##############################\n");
		count += snprintf(buf + count, buf_sz - count,
			    "## Fw type %s\n", get_fw_type_str(fw_entry->type));
		count += snprintf(buf + count, buf_sz - count,
			    "## fw_entry                        = %8p\n",
			    fw_entry);
		count += snprintf(buf + count, buf_sz - count,
			    "## fw_entry->type                  = 0x%08x\n",
			    fw_entry->type);
		count += snprintf(buf + count, buf_sz - count,
			    "## fw_entry->lzma                  = 0x%08x\n",
			    fw_entry->lzma);
		count += snprintf(buf + count, buf_sz - count,
			    "## fw_entry->ro                    = 0x%08x\n",
			    fw_entry->ro);
		count += snprintf(buf + count, buf_sz - count,
			    "## fw_entry->version               = 0x%08x\n",
			    fw_entry->version);
		count += snprintf(buf + count, buf_sz - count,
			    "## fw_entry->target_addr (in DDR)  = 0x%08x\n",
			    fw_entry->target_addr);
		count += snprintf(buf + count, buf_sz - count,
			    "## fw_entry->offset (in storage)   = 0x%08lx\n",
			    (unsigned long)fw_entry->offset);
		count += snprintf(buf + count, buf_sz - count,
			    "## fw_entry->length (in storage)   = 0x%08x\n",
			    fw_entry->length);
		count += snprintf(buf + count, buf_sz - count,
			    "## fw_entry->paddings (in storage) = 0x%08x\n",
			    fw_entry->paddings);
		count += snprintf(buf + count, buf_sz - count,
			    "## fw_entry->sha_hash              = ");
		for (i = 0 ; i < 32 ; i++)
			count += snprintf(buf + count, buf_sz - count,
				    "%02x", fw_entry->sha_hash[i]);
		count += snprintf(buf + count, buf_sz - count, "\n");
		count += snprintf(buf + count, buf_sz - count,
			    "###############################################\n\n");
	} else {
		count += snprintf(buf + count, buf_sz - count,
			    "## fw_entry is NULL.\n");
	}

	if (count >= buf_sz)
		TRACEF("[ERR] count %d >= buf_sz %d\n",
			    (int)count, (int)buf_sz);

	if (!_buf) {
		char *print_buf = malloc(++count);
		if (!print_buf) {
			TRACEF("ERROR! %s NO memory!!\n", __func__);
			return -ENOMEM;
		}
		memset(print_buf, '\0', count);
		memcpy(print_buf, buf, count);
		LTRACEF("\n%s", print_buf);
		free(print_buf);
		free(buf);
	}

	return count;
}

static int read_fw_table(void);
static size_t get_fw_entry_size(fw_desc_table_v1_t *fw_desc_table_v1);

size_t dump_fw_layout(char *buf, size_t buf_sz)
{
	fw_desc_table_v1_t *fw_desc_table_v1;
	size_t count = 0;

	read_fw_table();

	/* copy Firmware Description Table Header */
	fw_desc_table_v1 = (fw_desc_table_v1_t *)fw_desc_table_ddr_base;

	count += dump_fw_desc_table_v1(buf + count, buf_sz - count,
		    fw_desc_table_v1);

	if (fw_desc_table_v1->part_list_len) {
		part_desc_entry_v1_t *part_entry = NULL;
		int part_count = 0;
		int i;

		part_count = fw_desc_table_v1->part_list_len
			    / sizeof(part_desc_entry_v1_t);
		part_entry = (part_desc_entry_v1_t *)(fw_desc_table_ddr_base
			    + sizeof(fw_desc_table_v1_t));

		LTRACEF("[DEBUG] part_entry start: %8p size: 0x%x count: %d\n",
			    part_entry, (int)sizeof(part_desc_entry_v1_t), part_count);

		for (i = 0 ; i < part_count ; i++) {
			count += snprintf(buf + count, buf_sz - count,
				    "## part_entry index %d/%d ##\n", i + 1, part_count);
			count += dump_part_desc_entry_v1(buf + count, buf_sz - count,
				    &(part_entry[i]));
		}
	}

	if (fw_desc_table_v1->fw_list_len) {
		fw_desc_entry_v1_t *fw_entry;
		unsigned int fw_entry_size;
		int fw_entry_num = 0;
		void *fw_desc_ptr = NULL;
		int i;

		fw_entry = (fw_desc_entry_v1_t *)(fw_desc_table_ddr_base +
			sizeof(fw_desc_table_v1_t) +
			fw_desc_table_v1->part_list_len);
		fw_entry_size = get_fw_entry_size(fw_desc_table_v1);
		fw_entry_num = fw_desc_table_v1->fw_list_len / fw_entry_size;

		LTRACEF("[DEBUG] fw_entry start: %8p size: 0x%x count: %d\n",
			    fw_entry, (int)fw_entry_size, fw_entry_num);

		fw_desc_ptr = fw_entry;

		for (i = 0 ; i < fw_entry_num ; i++) {
			count += snprintf(buf + count, buf_sz - count,
				    "## fw_entry index %d/%d ##\n", i + 1, fw_entry_num);
			if (FW_DESC_BASE_VERSION(fw_desc_table_v1->version)
				    == FW_DESC_TABLE_V1_T_VERSION_1)
				count += dump_fw_desc_entry_v1(buf + count, buf_sz - count,
					    (fw_desc_entry_v1_t*)fw_desc_ptr);
			else if (FW_DESC_BASE_VERSION(fw_desc_table_v1->version)
				    == FW_DESC_TABLE_V2_T_VERSION_2)
				count += dump_fw_desc_entry_v2(buf + count, buf_sz - count,
					    (fw_desc_entry_v2_t*)fw_desc_ptr);
			fw_desc_ptr += fw_entry_size;
		}
	}

	return count;
}

void dump_fw_table(void)
{
	fw_desc_table_v1_t *fw_desc_table_v1;

	if (!fw_desc_table_ddr_base) {
		TRACEF("[ERROR] No init fw_desc_table_ddr_base!\n");
		return;
	}
	fw_desc_table_v1 = fw_desc_table_ddr_base;

	if (true)
		dump_fw_desc_table_v1(NULL, 0, fw_desc_table_v1);

	if (true) {
		part_desc_entry_v1_t *part_entry = NULL;
		int part_count = 0;
		int i;

		/* Check partition existence */
		if (fw_desc_table_v1->part_list_len == 0) {
			TRACEF("[ERROR] No partition found!\n");
			//return RTK_PLAT_ERR_PARSE_FW_DESC;
		} else {
			part_count = fw_desc_table_v1->part_list_len
					 / sizeof(part_desc_entry_v1_t);
			part_entry = (part_desc_entry_v1_t *)(fw_desc_table_ddr_base
					 + sizeof(fw_desc_table_v1_t));
		}

		for (i = 0 ; i < part_count ; i++) {
			dump_part_desc_entry_v1(NULL, 0, &(part_entry[i]));
		}
	}

	if (true) {
		fw_desc_entry_v1_t *fw_entry;
		unsigned int fw_entry_size;
		int fw_entry_num = 0;
		void *fw_desc_ptr = NULL;
		int i;

		fw_entry = (fw_desc_entry_v1_t *)(fw_desc_table_ddr_base +
			sizeof(fw_desc_table_v1_t) +
			fw_desc_table_v1->part_list_len);
		fw_entry_size = get_fw_entry_size(fw_desc_table_v1);
		fw_entry_num = fw_desc_table_v1->fw_list_len / fw_entry_size;

		fw_desc_ptr = fw_entry;

		for (i = 0 ; i < fw_entry_num ; i++) {
			if (FW_DESC_BASE_VERSION(fw_desc_table_v1->version)
					== FW_DESC_TABLE_V1_T_VERSION_1)
				dump_fw_desc_entry_v1(NULL, 0,
					    (fw_desc_entry_v1_t*)fw_desc_ptr);
			else if (FW_DESC_BASE_VERSION(fw_desc_table_v1->version)
					== FW_DESC_TABLE_V2_T_VERSION_2)
				dump_fw_desc_entry_v2(NULL, 0,
					    (fw_desc_entry_v2_t*)fw_desc_ptr);
			fw_desc_ptr += fw_entry_size;
		}
	}

}

static size_t get_fw_entry_size(fw_desc_table_v1_t *fw_desc_table_v1)
{
	size_t fw_entry_size = 0;

	switch (fw_desc_table_v1->version) {
		case FW_DESC_TABLE_V1_T_VERSION_1:
			fw_entry_size = sizeof(fw_desc_entry_v1_t);
			break;
		case FW_DESC_TABLE_V1_T_VERSION_11:
			fw_entry_size = sizeof(fw_desc_entry_v11_t);
			break;
		case FW_DESC_TABLE_V1_T_VERSION_21:
			fw_entry_size = sizeof(fw_desc_entry_v21_t);
			break;
		case FW_DESC_TABLE_V2_T_VERSION_2:
			fw_entry_size = sizeof(fw_desc_entry_v2_t);
			break;
		case FW_DESC_TABLE_V2_T_VERSION_12:
			fw_entry_size = sizeof(fw_desc_entry_v12_t);
			break;
		case FW_DESC_TABLE_V2_T_VERSION_22:
			fw_entry_size = sizeof(fw_desc_entry_v22_t);
			break;
		default:
			TRACEF("unsupport FW DESC TBL version 0x%x\n",
					fw_desc_table_v1->version);
			return RTK_PLAT_ERR_PARSE_FW_DESC;
			break;
	}

	return fw_entry_size;
}

static unsigned int get_checksum(unsigned char *p, unsigned int len) {
	unsigned int checksum = 0;
	unsigned int i;
	for(i = 0; i < len; i++) {
		checksum += *(p+i);
	}
	return checksum;
}

static int read_fw_table(void)
{
	fw_desc_table_v1_t fw_desc_table_v1;
	unsigned int checksum;
	int ret = 0;

	LTRACEF("[DEBUG] read_fw_table\n");

	if (get_fwtbl_start_address(&fw_desc_table_start))
		return RTK_PLAT_ERR_READ_FW_IMG;

	LTRACEF("[DEBUG] fw_desc_table_start = 0x%llx "
			"fw_desc_table_ddr_base = %p\n",
			 fw_desc_table_start, fw_desc_table_ddr_base);

	/* Firmware Description Table is right behind bootcode blocks */
	ret = storage_read(fw_desc_table_start, sizeof(fw_desc_table_v1_t),
		    fw_desc_table_ddr_base);

	if (ret < (int)sizeof(fw_desc_table_v1_t)) {
		TRACEF("[ERROR] Read fw_desc_table_v1_t error! "
			    "(0x%llx, 0x%lx, 0x%p)\n",
			    fw_desc_table_start, sizeof(fw_desc_table_v1_t),
			    fw_desc_table_ddr_base);
		return RTK_PLAT_ERR_PARSE_FW_DESC;
	}

	/* copy Firmware Description Table Header from flash */
	memcpy(&fw_desc_table_v1, fw_desc_table_ddr_base,
			sizeof(fw_desc_table_v1_t));

	/* Check signature first! */
	if (strncmp((const char *)fw_desc_table_v1.signature,
			FIRMWARE_DESCRIPTION_TABLE_SIGNATURE,
					 sizeof(fw_desc_table_v1.signature)) != 0) {
		TRACEF("[ERROR] Signature(%s) error!\n",
				 fw_desc_table_v1.signature);
		return RTK_PLAT_ERR_PARSE_FW_DESC;
	}

	/* copy Firmware Description/Partition/Fw_entry Tables from flash */
	ret = storage_read(fw_desc_table_start, fw_desc_table_v1.paddings,
		    fw_desc_table_ddr_base);

	if (ret < (int)fw_desc_table_v1.paddings) {
		TRACEF("[ERROR] Read all fw tables error! "
			    "(0x%llx, 0x%x, 0x%p)\n",
			    fw_desc_table_start, fw_desc_table_v1.paddings,
			    fw_desc_table_ddr_base);
		return RTK_PLAT_ERR_PARSE_FW_DESC;
	}

	/* Check checksum */
	checksum = get_checksum(fw_desc_table_ddr_base +
				offsetof(fw_desc_table_v1_t, version),
				sizeof(fw_desc_table_v1_t) -
				offsetof(fw_desc_table_v1_t, version) +
				fw_desc_table_v1.part_list_len +
				fw_desc_table_v1.fw_list_len);

	if (fw_desc_table_v1.checksum != checksum) {
		TRACEF("[ERROR] Checksum not match(0x%x != 0x%x)\n",
				fw_desc_table_v1.checksum, checksum);
		return RTK_PLAT_ERR_PARSE_FW_DESC;
	}

	dump_fw_table();

	return ret;
}

static size_t write_fw_table(void)
{
	int ret = 0;

	LTRACEF("[DEBUG] write_fw_table\n");

	if (get_fwtbl_start_address(&fw_desc_table_start))
		return RTK_PLAT_ERR_READ_FW_IMG;

	LTRACEF("[DEBUG] fw_desc_table_start = 0x%llx "
			"fw_desc_table_ddr_base = %p\n",
			 fw_desc_table_start, fw_desc_table_ddr_base);

	/* Firmware Description Table is right behind bootcode blocks */
	ret = storage_write(fw_desc_table_start, fw_desc_table_max_size,
		    fw_desc_table_ddr_base);

	if (ret < (int)fw_desc_table_max_size) {
		TRACEF("[ERROR] Write fw table error! "
			    "(0x%llx, 0x%lx, 0x%p)\n",
			    fw_desc_table_start, fw_desc_table_max_size,
			    fw_desc_table_ddr_base);
		return RTK_PLAT_ERR_PARSE_FW_DESC;
	}

	dump_fw_table();

	return ret;
}

int build_fw_table(struct fw_info *fw_infos, struct part_info *p_infos)
{
	fw_desc_table_v1_t *fw_desc_table_v1;
	fw_desc_entry_v2_t *fw_desc_entry_v2;
	part_desc_entry_v1_t *part_desc_entry_v1;
	void *ptr;
	int i;

	LTRACEF("[DEBUG] build_fw_table\n");
	if (get_fwtbl_start_address(&fw_desc_table_start))
		return RTK_PLAT_ERR_READ_FW_IMG;

	memset(fw_desc_table_ddr_base, 0, fw_desc_table_max_size);

	ptr = fw_desc_table_ddr_base;

	fw_desc_table_v1 = ptr;
	LTRACEF("[DEBUG] fw_desc_table_v1 @%p\n", fw_desc_table_v1);

	ptr += sizeof(fw_desc_table_v1_t);
	for (i = 0; i < MAX_PART_INFO; i++) {
		struct part_info *pinfo = &p_infos[i];
		if (pinfo->bytes_size == 0 || !pinfo->in_fwt) {
			LTRACEF("#%d, SKIP pinfo@%p name %s bytes_size=0x%llx in_fwt=%s "
				    "is_use=%s\n",
				    i, pinfo, pinfo->name, (int64_t)pinfo->bytes_size,
				    pinfo->in_fwt?"true":"false",
				    pinfo->is_use?"true":"false");
			continue;
		}
		part_desc_entry_v1 = ptr;

		LTRACEF("#%d, pinfo@%p name %s part_desc_entry_v1@%p\n",
			i, pinfo, pinfo->name, part_desc_entry_v1);

		part_desc_entry_v1->type = pinfo->type; /* 1:FW 2:FS */
		part_desc_entry_v1->ro = 1;
		part_desc_entry_v1->length = pinfo->length;
		part_desc_entry_v1->fw_count = pinfo->fw_count;
		part_desc_entry_v1->fw_type = pinfo->fw_type; //ext4
#ifdef CONFIG_SYS_RTK_EMMC_FLASH
		part_desc_entry_v1->emmc_partIdx = pinfo->id;
#endif
		memset(part_desc_entry_v1->mount_point, '\0', 32);
		if (pinfo->mount)
			strncpy((char *)part_desc_entry_v1->mount_point, pinfo->mount,
				strlen(pinfo->mount));
		pinfo->part_desc_entry = ptr;

		ptr += sizeof(part_desc_entry_v1_t);
		fw_desc_table_v1->part_list_len += sizeof(part_desc_entry_v1_t);
	}

	fw_desc_table_v1->version = FW_DESC_TABLE_V2_T_VERSION_2;
	for (i = 0; i< MAX_FW_INFO; i++) {
		struct fw_info *fw = &fw_infos[i];
		fw_desc_entry_v2 = ptr;

		if (!fw->is_use) {
			LTRACEF("#%d, SKIP fw_info@%p name %s is_use=%s in_fwt=%s "
				    "fw_desc_entry_v2@%p\n",
				    i, fw, fw->name, fw->is_use?"true":"false",
				    fw->in_fwt?"true":"false", fw_desc_entry_v2);
			continue; /* skip FW_TYPE_RESERVED */
		}
		if (fw->id == FW_TYPE_IMAGE_FILE) {
			struct part_info *part = get_part_info("logo");

			fw->start_addr = part->start_addr + 0x2000;
		}
		LTRACEF("#%d, fw_info@%p name %s is_use=%s in_fwt=%s "
			    "fw_desc_entry_v2@%p\n",
			    i, fw, fw->name, fw->is_use?"true":"false",
			    fw->in_fwt?"true":"false", fw_desc_entry_v2);

		fw->start_block = fw->start_addr / flash_blk_size;
		fw->block_size = fw->bytes_size / flash_blk_size;
		fw_desc_entry_v2->type = fw->id;
		fw_desc_entry_v2->version = FW_DESC_TABLE_V2_T_VERSION_2;
		fw_desc_entry_v2->target_addr = fw->load_addr;
		fw_desc_entry_v2->offset = fw->start_addr;
		fw_desc_entry_v2->length = fw->length;
		fw_desc_entry_v2->paddings = fw->bytes_size;
		fw->fw_desc_entry = fw_desc_entry_v2;

		LTRACEF("Build fw_desc %s offset=0x%x, "
			    "paddings=0x%x, length=0x%x\n",
			    get_fw_type_str(fw_desc_entry_v2->type),
			    (int)fw_desc_entry_v2->offset,
			    (int)fw_desc_entry_v2->paddings,
			    (int)fw_desc_entry_v2->length);

		ptr += get_fw_entry_size(fw_desc_table_v1);
		fw_desc_table_v1->fw_list_len += get_fw_entry_size(fw_desc_table_v1);
	}

	/* build fw table */
	strncpy((char *)fw_desc_table_v1->signature,
			FIRMWARE_DESCRIPTION_TABLE_SIGNATURE,
			strlen(FIRMWARE_DESCRIPTION_TABLE_SIGNATURE));

	fw_desc_table_v1->paddings = sizeof(fw_desc_table_v1_t)
			+ fw_desc_table_v1->part_list_len + fw_desc_table_v1->fw_list_len;

	fw_desc_table_v1->checksum = get_checksum(fw_desc_table_ddr_base +
				offsetof(fw_desc_table_v1_t, version),
				sizeof(fw_desc_table_v1_t) -
				offsetof(fw_desc_table_v1_t, version) +
				fw_desc_table_v1->part_list_len +
				fw_desc_table_v1->fw_list_len);

	dump_fw_table();

	write_fw_table();
	return 0;
}

int update_fw_table(struct fw_info *fw)
{
	fw_desc_table_v1_t *fw_desc_table_v1 =
		    (fw_desc_table_v1_t *)fw_desc_table_ddr_base;
	struct fw_info *info = fw;
	int ret;

	LTRACEF("[DEBUG] update_fw_table\n");

	LTRACEF("fw_info name %s\n", fw->name);
	while (info) {
		fw_desc_entry_v2_t *fw_entry =
			    (fw_desc_entry_v2_t *)info->fw_desc_entry;
		if (fw_entry) {
			fw_entry->offset = info->start_addr;
			fw_entry->paddings = info->bytes_size;
			fw_entry->length = info->length;
			memcpy(&fw_entry->sha_hash, info->sha_hash, 32);
		}
		info = get_fw_info_next(info);
	}

	fw_desc_table_v1->checksum = get_checksum(fw_desc_table_ddr_base +
		    offsetof(fw_desc_table_v1_t, version),
		    sizeof(fw_desc_table_v1_t) -
		    offsetof(fw_desc_table_v1_t, version) +
		    fw_desc_table_v1->part_list_len +
		    fw_desc_table_v1->fw_list_len);

	LTRACEF("[DEBUG] update fw table fw_desc_table_start 0x%llx "
		    "fw_desc_table_size 0x%x fw_desc_table_ddr_base %p\n",
		    fw_desc_table_start, (int)fw_desc_table_v1->paddings,
		    fw_desc_table_ddr_base);

	ret = storage_write(fw_desc_table_start, fw_desc_table_v1->paddings,
		    fw_desc_table_ddr_base);
	if (ret < 0) {
		TRACEF("[ERROR] update fw table "
		    "fw_desc_table_start %llx "
		    "fw_desc_table_size 0x%x fw_desc_table_ddr_base %p\n",
		    fw_desc_table_start, (int) fw_desc_table_v1->paddings,
		    fw_desc_table_ddr_base);
	}

	/* For Golden fw table */
	LTRACEF("[DEBUG] update golden fw table fw_desc_table_start 0x%llx "
		    "fw_desc_table_size 0x%x fw_desc_table_ddr_base %p\n",
		    fw_desc_table_start + FW_TABLE_SIZE,
		    (int)fw_desc_table_v1->paddings,
		    fw_desc_table_ddr_base);

	ret = storage_write(fw_desc_table_start + FW_TABLE_SIZE,
		    fw_desc_table_v1->paddings,
		    fw_desc_table_ddr_base);
	if (ret < 0) {
		TRACEF("[ERROR] update golden fw table "
		    "fw_desc_table_start %llx "
		    "fw_desc_table_size 0x%x fw_desc_table_ddr_base %p\n",
		    fw_desc_table_start + FW_TABLE_SIZE,
		    (int) fw_desc_table_v1->paddings,
		    fw_desc_table_ddr_base);
	}

	dump_fw_table();

	return 0;
}

int read_fw_info(struct fw_info *fw_infos, struct part_info *part_infos)
{
	fw_desc_table_v1_t *fw_desc_table_v1;
	part_desc_entry_v1_t *part_entry = NULL;
	int part_count = 0;
	int i;

	read_fw_table();

		/* copy Firmware Description Table Header */
	fw_desc_table_v1 = (fw_desc_table_v1_t *)fw_desc_table_ddr_base;

	/* Check partition existence */
	if (fw_desc_table_v1->part_list_len == 0) {
		TRACEF("[ERROR] No partition found!\n");
		//return RTK_PLAT_ERR_PARSE_FW_DESC;
	} else {
		part_count = fw_desc_table_v1->part_list_len
			    / sizeof(part_desc_entry_v1_t);
		part_entry = (part_desc_entry_v1_t *)(fw_desc_table_ddr_base
			    + sizeof(fw_desc_table_v1_t));
	}

	for (i = 0 ; i < part_count; i++) {
		part_desc_entry_v1_t *p_entry;
		struct part_info *pinfo;

		p_entry = &(part_entry[i]);
		LTRACEF("#%d p_entry@%p Find pinfo for mount %s\n",
			    i, p_entry, p_entry->mount_point);
		pinfo = get_part_info_by_mount((char *)p_entry->mount_point);
		if (pinfo) {
			pinfo->is_use = true;
			pinfo->type = p_entry->type;
			pinfo->ro = p_entry->ro;
			pinfo->length = p_entry->length;
			pinfo->fw_count = p_entry->fw_count;
			pinfo->fw_type = p_entry->fw_type;
			pinfo->part_desc_entry = part_entry;
			LTRACEF("From fw read pinfo %s length 0x%llx mount_point %s\n",
				    pinfo->name, (int64_t)pinfo->bytes_size, pinfo->mount);
		}
	}

	if (fw_desc_table_v1->fw_list_len) {
		fw_desc_entry_v2_t *fw_entry;
		unsigned int fw_entry_size;
		int fw_entry_num = 0;
		void *fw_desc_ptr = NULL;
		int i, j;

		fw_entry = (fw_desc_entry_v2_t *)(fw_desc_table_ddr_base +
			sizeof(fw_desc_table_v1_t) +
			fw_desc_table_v1->part_list_len);
		fw_entry_size = get_fw_entry_size(fw_desc_table_v1);
		fw_entry_num = fw_desc_table_v1->fw_list_len / fw_entry_size;

		LTRACEF("[DEBUG] fw_entry start: %8p size: 0x%x count: %d\n",
			    fw_entry, (int)fw_entry_size, fw_entry_num);

		fw_desc_ptr = fw_entry;

		for (i = 0; i < fw_entry_num; i++) {
			for (j = 0; j < MAX_FW_INFO; j ++) {
				struct fw_info *info= &fw_infos[j];
				fw_desc_entry_v2_t *fw_desc;

				fw_desc = (fw_desc_entry_v2_t *)fw_desc_ptr;
				if (!info->in_fwt || info->id != fw_desc->type)
					continue;
				info->is_use = true;
				info->ro = fw_desc->ro;
				info->version = fw_desc->version;
				info->load_addr = fw_desc->target_addr;
				info->start_addr = fw_desc->offset;
				info->bytes_size = fw_desc->paddings;
				info->length = fw_desc->length;
				memcpy(&info->sha_hash, fw_desc->sha_hash, 32);
				info->fw_desc_entry = fw_desc_ptr;
				LTRACEF("From fw read fw_desc %s offset=0x%x, "
					    "paddings=0x%x, length=0x%x\n",
					    get_fw_type_str(fw_desc->type),
						(int)fw_desc->offset,
					    (int)fw_desc->paddings,
					    (int)fw_desc->length);
				LTRACEF("From fw read fw_info %s i=%d, start_addr=0x%x, "
					    "bytes_size=0x%x, length=0x%x\n",
					    info->name, i, (int)info->start_addr,
					    (int)info->bytes_size,
					    (int)info->length);
			}
			fw_desc_ptr += fw_entry_size;
		}
	}

	return 0;
}

static size_t relayout_fw_img(struct fw_info *fw,
	    void *img_ddr_base, uint64_t img_offset)
{
	int ret;
	size_t update_size = 0;
	uint64_t offset = img_offset;
	struct fw_info *info = get_fw_info_next(fw);

	LTRACEF("To relayout_fw_img due to %s (type 0x%x)\n",
		    get_fw_type_str(fw->id), fw->id);
	while (info) {
		if (info->id == FW_TYPE_RESERVED) {
			LTRACEF("SKIP fw name %s\n", info->name);
			offset += flash_blk_size;
			update_size += flash_blk_size;
			info = get_fw_info_next(info);
			continue;
		} else if (info->id == FW_TYPE_IMAGE_FILE) {
			LTRACEF("SKIP fw name %s\n", info->name);
			info = get_fw_info_next(info);
			continue;
		}
		LTRACEF("[DEBUG] relayout image %s (type 0x%x)\n",
			    get_fw_type_str(info->id), info->id);

		/* copy Firmware Description/Partition/Fw_entry Tables from flash */
		ret = storage_read(info->start_addr, info->bytes_size,
			    img_ddr_base + update_size);

		if (ret < (int)info->bytes_size) {
			TRACEF("[ERR] Read fw_desc_table_v1_t error! "
				    "(0x%llx, 0x%lx, 0x%p)\n",
				    info->start_addr, info->bytes_size,
				    fw_desc_table_ddr_base);
			return update_size;
		}

		LTRACEF("[DEBUG] Read emmc from start_addr 0x%x, "
			    "bytes_size 0x%x \n",
			    (int) info->start_addr, (int) info->bytes_size);
		LTRACEF("       to DDR %p (img_ddr_base %p + update_size 0x%lx)\n",
					 img_ddr_base + update_size, img_ddr_base, update_size);

		info->start_addr = offset;
		update_size += info->bytes_size;
		offset += info->bytes_size;

		LTRACEF("[DEBUG] New start_addr 0x%x, "
			    "bytes_size 0x%x (all update_size 0x%lx)\n",
			    (int)info->start_addr, (int) info->bytes_size,
			    update_size);

		info = get_fw_info_next(info);
	}

	return update_size;
}

#ifdef FASTBOOT_FW_IMG_UPDATE_ADDR
#define FW_IMG_UPDATE_BASE FASTBOOT_FW_IMG_UPDATE_ADDR
#else
#define FW_IMG_UPDATE_BASE 0x30000000
#endif
#ifdef FASTBOOT_FW_IMG_UPDATE_MAX_SIZE
#define FW_IMG_UPDATE_SIZE_MAX FASTBOOT_FW_IMG_UPDATE_MAX_SIZE
#else
#define FW_IMG_UPDATE_SIZE_MAX 100*1024*1024
#endif

int write_fw_img(struct fw_info* fw, uint64_t file_size, uint64_t offset,
		void *buffer, size_t size)
{
	int ret = 0;
	uint64_t fw_update_start = 0;
	size_t fw_update_size = 0;
	bool do_relayout = false;
	void *fw_update_ddr_base = (void *)FW_IMG_UPDATE_BASE;
//	void *fw_update_ddr_base = memalign(CACHE_LINE, FW_IMG_UPDATE_SIZE_MAX);

	if (!fw_update_ddr_base) {
		TRACEF("[ERROR] fw_update_ddr_base is NULL ==> NO memory??\n");
		return -1;
	}
	LTRACEF("[DEBUG] fw_update_ddr_base@%p "
		    "(FW_IMG_UPDATE_BASE=0x%x, FW_IMG_UPDATE_SIZE_MAX 0x%x)\n",
		    fw_update_ddr_base, FW_IMG_UPDATE_BASE, FW_IMG_UPDATE_SIZE_MAX);

	memset(fw_update_ddr_base, '\0', FW_IMG_UPDATE_SIZE_MAX);

	if (!file_size)
		file_size = size;

	LTRACEF("[DEBUG] write fw %s (type=%x) file_size 0x%llx offset 0x%llx "
			"buffer %p size 0x%lx\n",
			fw->name, fw->id, file_size, offset, buffer, size);

	fw_update_start = fw->start_addr;
	fw->length = file_size;

	if (fw->bytes_size < file_size) {
		LTRACEF("[DEBUG] Check bytes_size 0x%x file_size 0x%x "
			    "need to relayout\n",
				(int)fw->bytes_size, (int)file_size);

			fw->bytes_size =
					(file_size + flash_blk_size - 1) & 0xFFFFFFE00;
			do_relayout = true;
	}

	fw_update_size = fw->bytes_size;

	/* read from emmc */
	ret = storage_read(fw_update_start, fw_update_size,
		    fw_update_ddr_base);

	if (ret < (int)fw_update_size) {
		TRACEF("[ERR] Read from storage! ret=0x%x "
			    "(fw_update_start 0x%llx, fw_update_size 0x%lx,"
			    "fw_update_ddr_base 0x%p)\n", ret,
			    fw_update_start, fw_update_size,
			    fw_update_ddr_base);
		return ret;
	}

	memcpy(fw_update_ddr_base + offset, buffer, size);

	flush_cache((unsigned long) fw_update_ddr_base, file_size);

	SHA256_hash((uchar *)(uintptr_t)fw_update_ddr_base, file_size,
		    fw->sha_hash, NULL);

	LTRACEF("[DEBUG] fw_update_start 0x%x fw_update_size 0x%x\n",
		(int) fw_update_start, (int) fw_update_size);

	if (do_relayout) {
		size_t update_size;

		update_size = relayout_fw_img(fw,
			    fw_update_ddr_base + fw->bytes_size,
			    fw_update_start + fw->bytes_size);
		fw_update_size += update_size;
	}

	LTRACEF("Update fw image from %s to end "
			"(fw_update_start 0x%llx fw_update_size 0x%lx "
			"fw_update_ddr_base@%p)\n",
			fw->name, fw_update_start, fw_update_size, fw_update_ddr_base);
	if (fw_update_size > FW_IMG_UPDATE_SIZE_MAX) {
		TRACEF("[ERROR] fw_update_size 0x%x > 0x%x\n",
			    (int)fw_update_size, FW_IMG_UPDATE_SIZE_MAX);
		fw_update_size = FW_IMG_UPDATE_SIZE_MAX;
	}

	/* update fw and fw_table */
	ret = storage_write(fw_update_start, fw_update_size, fw_update_ddr_base);

	if (ret < 0) {
		TRACEF("[ERROR] update fw image fail %s "
				"fw_update_start 0x%llx "
				"fw_update_size 0x%llx fw_update_ddr_base %p\n",
				fw->name,
				(int64_t)fw_update_start, (int64_t)fw_update_size,
				fw_update_ddr_base);
	}

	update_fw_table(fw);

	// free(fw_update_ddr_base);

	return 0;
}
