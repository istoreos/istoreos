/*
 * Copyright 2020, Rockchip Electronics Co., Ltd
 * hisping lin, <hisping.lin@rock-chips.com>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <common.h>
#include <stdlib.h>
#include <command.h>
#include <boot_rkimg.h>
#include <part.h>
#include <optee_include/OpteeClientRkFs.h>

//#define DEBUG_RKSS
//#define DEBUG_CLEAN_RKSS

/*
 *	RK Secure Storage Ctrl
 *		Storage Size : 512 kb
 *		Header Size : 8 byte * 2 for each top of 512 byte
 *		Partision Table Size : 128 * 512 b (24 Files And Folder)
 *		File number: 128 * 4 = 512
 *		Data Size : 895 * 512 b
 *
 *	------ RKSS Structure --------
 *	- 512 byte patition table1 [0]
 *		- 126 * 4 = 504 byte table info
 *		- 8 byte verification
 *	- 512 byte patition table2 [1]
 *	             ...
 *	- 512 byte patition table128 [127]
 *	- 512 byte section used refs [128]
 *		- 1 byte = 2 flag
 *	- 895 * 512 byte data	[129 - 1023]
 *	------ RKSS Backup Structure --------
 *	- 512 byte backup header  [1024]
 *		- 1 * rkss_backup_verification + 31 * rkss_backup_info
 *	- 255 * 512 byte backup data [1025 - 1279]
 *
 */
#define RKSS_DATA_SECTION_COUNT		1024
#define RKSS_DATA_SECTION_LEN		512
#define RKSS_PARTITION_TABLE_COUNT	128		// total size 512 * 128
#define RKSS_EACH_SECTION_FILECOUNT	4		// 504 / 126 = 4
#define RKSS_MAX_NAME_LENGTH		117		// 116 char + "\0"
#define RKSS_USED_FLAGS_INDEX		RKSS_PARTITION_TABLE_COUNT
#define RKSS_BACKUP_INDEX		RKSS_DATA_SECTION_COUNT
#define RKSS_BACKUP_COUNT		256

#define RKSS_BACKUP_VERSION		(unsigned int)0x1
#define RKSS_BACKUP_ENABLE		(unsigned int)0x55667788
#define RKSS_BACKUP_USEDFLAG		(unsigned int)0xAABBCCDD

struct rkss_backup_verification {
	unsigned int backup_version;
	unsigned int backup_count;
	unsigned int reserve;
	unsigned int backup_enable;
};

struct rkss_backup_info {
	unsigned int backup_index;
	unsigned int backup_num;
	unsigned int backup_data_index;
	unsigned int backup_usedflag;
};

typedef struct rkss_file_info {
	uint8_t		used;
	char 		name[RKSS_MAX_NAME_LENGTH];
	uint16_t	index;	// from 129 to 1024
	uint16_t	size;	// size of data
	uint16_t	father;
	uint8_t 	id; // file folder count index
	uint8_t		flags;
} rkss_file_info; // 126 byte for each

#define RKSS_CHECK_STR	(uint32_t)0x12345678
#define RKSS_CHECK_PT		(uint8_t)0xFC
typedef struct rkss_file_verification {
	uint32_t version;
	uint32_t checkstr;
} rkss_file_verification; // 8 byte

typedef struct rk_secure_storage {
	unsigned long index;
	unsigned char data[RKSS_DATA_SECTION_LEN];
} rk_secure_storage;

/* RK Secure Storage Calls */
static int file_seek;
static char dir_cache[RKSS_MAX_NAME_LENGTH][12];
static int dir_num;
static int dir_seek;

static struct blk_desc *dev_desc;
static disk_partition_t part_info;

static int check_security_exist(int print_flag)
{
	if (!dev_desc) {
		dev_desc = rockchip_get_bootdev();
		if (!dev_desc) {
			printf("TEEC: %s: Could not find device\n", __func__);
			return -1;
		}

		if (part_get_info_by_name(dev_desc,
					  "security", &part_info) < 0) {
			dev_desc = NULL;
			if (print_flag != 0)
				printf("TEEC: Could not find security partition\n");
			return -1;
		}
	}
	return 0;
}

/*
 * action1:
 * rkss_begin_commit	set enable flag
 * rkss_backup_sections	backup data
 * blk_dwrite
 * rkss_finish_commit	clear enable flag, clear backup data
 * reboot
 * rkss_resume	not find enable flag, do nothing
 *
 * action2:
 * rkss_begin_commit	set enable flag
 * rkss_backup_sections	backup data
 * power off when blk_dwrite
 *
 * power on
 * rkss_resume	find enable flag, resume all backup data
 */
static int rkss_begin_commit(void)
{
	unsigned char *data = NULL;
	struct rkss_backup_verification p;
	unsigned long ret;

	if (check_security_exist(1) < 0)
		return -1;

	debug("TEEC: %s\n", __func__);
	p.backup_version = RKSS_BACKUP_VERSION;
	p.backup_enable = RKSS_BACKUP_ENABLE;
	p.backup_count = 0;

	data = memalign(CONFIG_SYS_CACHELINE_SIZE, RKSS_DATA_SECTION_LEN);
	if (!data) {
		printf("TEEC: malloc data fail\n");
		return -1;
	}
	memset(data, 0, RKSS_DATA_SECTION_LEN);
	memcpy(data, &p, sizeof(p));

	ret = blk_dwrite(dev_desc, part_info.start + RKSS_BACKUP_INDEX, 1, data);
	free(data);
	if (ret != 1) {
		printf("TEEC: blk_dwrite fail\n");
		return -1;
	}
	return 0;
}

static int rkss_finish_commit(void)
{
	unsigned char *data = NULL;
	unsigned long ret;

	if (check_security_exist(1) < 0)
		return -1;

	debug("TEEC: %s\n", __func__);
	data = memalign(CONFIG_SYS_CACHELINE_SIZE, RKSS_DATA_SECTION_LEN);
	if (!data) {
		printf("TEEC: malloc data fail\n");
		return -1;
	}
	memset(data, 0, RKSS_DATA_SECTION_LEN);

	ret = blk_dwrite(dev_desc, part_info.start + RKSS_BACKUP_INDEX, 1, data);
	free(data);
	if (ret != 1) {
		printf("TEEC: blk_dwrite fail\n");
		return -1;
	}
	return 0;
}

static int rkss_backup_sections(unsigned long index, unsigned int num)
{
	unsigned char *data = NULL;
	unsigned char *backup_data = NULL;
	struct rkss_backup_verification p;
	struct rkss_backup_info info_last, info_current;
	unsigned long ret;

	if (check_security_exist(1) < 0)
		return -1;

	data = memalign(CONFIG_SYS_CACHELINE_SIZE, RKSS_DATA_SECTION_LEN);
	if (!data) {
		printf("TEEC: malloc data fail\n");
		goto error;
	}
	ret = blk_dread(dev_desc, part_info.start + RKSS_BACKUP_INDEX, 1, data);
	if (ret != 1) {
		printf("TEEC: blk_dread fail\n");
		goto error;
	}

	memcpy(&p, data, sizeof(p));
	if (p.backup_version == RKSS_BACKUP_VERSION &&
	    p.backup_enable == RKSS_BACKUP_ENABLE) {
		if (p.backup_count == 0) {
			info_current.backup_usedflag = RKSS_BACKUP_USEDFLAG;
			info_current.backup_index = index;
			info_current.backup_num = num;
			info_current.backup_data_index = RKSS_BACKUP_INDEX + 1;
		} else {
			memcpy(&info_last,
			       data + sizeof(p) + (p.backup_count - 1) *
			       sizeof(info_last), sizeof(info_last));
			info_current.backup_usedflag = RKSS_BACKUP_USEDFLAG;
			info_current.backup_index = index;
			info_current.backup_num = num;
			info_current.backup_data_index =
				info_last.backup_data_index +
				info_last.backup_num;
		}
		if ((info_current.backup_data_index + info_current.backup_num) >
			(RKSS_BACKUP_INDEX + RKSS_BACKUP_COUNT)) {
			printf("TEEC: Not enough backup sections!");
			goto error;
		}
		debug("TEEC: %s index=0x%lx num=0x%x backup_data_index=0x%x\n",
		      __func__, index, num, info_current.backup_data_index);

		backup_data = memalign(CONFIG_SYS_CACHELINE_SIZE, num * RKSS_DATA_SECTION_LEN);
		if (!backup_data) {
			printf("TEEC: malloc backup_data fail\n");
			goto error;
		}

		ret = blk_dread(dev_desc, part_info.start + index, num, backup_data);
		if (ret != num) {
			printf("TEEC: blk_dread fail\n");
			goto error;
		}

		ret = blk_dwrite(dev_desc, part_info.start + info_current.backup_data_index,
				 num, backup_data);
		if (ret != num) {
			printf("TEEC: blk_dwrite fail\n");
			goto error;
		}
		free(backup_data);

		p.backup_count += 1;

		memcpy(data, &p, sizeof(p));
		memcpy(data + sizeof(p) +
		       (p.backup_count - 1) * sizeof(info_current),
		       &info_current, sizeof(info_current));

		ret = blk_dwrite(dev_desc, part_info.start + RKSS_BACKUP_INDEX, 1, data);
		if (ret != 1) {
			printf("TEEC: blk_dwrite fail\n");
			goto error;
		}
	}
	free(data);
	return 0;

error:
	if (data)
		free(data);
	if (backup_data)
		free(backup_data);
	return -1;
}

static int rkss_resume(void)
{
	unsigned char *data = NULL;
	unsigned char *backup_data = NULL;
	struct rkss_backup_verification p;
	struct rkss_backup_info info_current;
	unsigned int i;
	unsigned long ret;

	if (check_security_exist(1) < 0)
		return -1;

	data = memalign(CONFIG_SYS_CACHELINE_SIZE, RKSS_DATA_SECTION_LEN);
	if (!data) {
		printf("TEEC: malloc data fail\n");
		goto error;
	}
	ret = blk_dread(dev_desc, part_info.start + RKSS_BACKUP_INDEX, 1, data);
	if (ret != 1) {
		printf("TEEC: blk_dread fail\n");
		goto error;
	}

	memcpy(&p, data, sizeof(p));
	if (p.backup_version == RKSS_BACKUP_VERSION &&
	    p.backup_enable == RKSS_BACKUP_ENABLE) {
		for (i = p.backup_count; i > 0; i--) {
			memcpy(&info_current, data + sizeof(p) + (i - 1) *
			       sizeof(info_current), sizeof(info_current));

			if (info_current.backup_usedflag ==
			    RKSS_BACKUP_USEDFLAG) {
				debug("TEEC: rkss_resume backup_index=0x%x \
				      backup_num=0x%x \
				      info_current.backup_data_index=0x%x\n",
				      info_current.backup_index,
				      info_current.backup_num,
				      info_current.backup_data_index);
				if ((info_current.backup_data_index +
				     info_current.backup_num) >
				    (RKSS_BACKUP_INDEX + RKSS_BACKUP_COUNT)) {
					printf("TEEC: backup sections error!");
					goto error;
				}
				if ((info_current.backup_index +
				     info_current.backup_num) >
				    RKSS_DATA_SECTION_COUNT) {
					printf("TEEC: original sections error!");
					goto error;
				}

				backup_data = memalign(CONFIG_SYS_CACHELINE_SIZE,
						       info_current.backup_num * RKSS_DATA_SECTION_LEN);
				if (!backup_data) {
					printf("TEEC: malloc backup_data fail\n");
					goto error;
				}

				ret = blk_dread(dev_desc,
						part_info.start + info_current.backup_data_index,
						info_current.backup_num,
						backup_data);
				if (ret != info_current.backup_num) {
					printf("TEEC: blk_dread fail\n");
					goto error;
				}

				ret = blk_dwrite(dev_desc,
						 part_info.start + info_current.backup_index,
						 info_current.backup_num,
						 backup_data);
				if (ret != info_current.backup_num) {
					printf("TEEC: blk_dwrite fail\n");
					goto error;
				}
				free(backup_data);
			}
		}
	}
	memset(data, 0, RKSS_DATA_SECTION_LEN);
	ret = blk_dwrite(dev_desc, part_info.start + RKSS_BACKUP_INDEX, 1, data);
	if (ret != 1) {
		printf("TEEC: blk_dwrite fail\n");
		goto error;
	}
	free(data);
	return 0;

error:
	if (data)
		free(data);
	if (backup_data)
		free(backup_data);
	return -1;
}

static int rkss_read_multi_sections(unsigned char *data, unsigned long index, unsigned int num)
{
	unsigned char *tmp_data = NULL;
	unsigned long ret;

	if (check_security_exist(1) < 0)
		return -1;

	tmp_data = memalign(CONFIG_SYS_CACHELINE_SIZE, num * RKSS_DATA_SECTION_LEN);
	if (!tmp_data) {
		printf("TEEC: malloc tmp_data fail\n");
		return -1;
	}
	ret = blk_dread(dev_desc, part_info.start + index, num, tmp_data);
	if (ret != num) {
		printf("TEEC: blk_dread fail\n");
		free(tmp_data);
		return -1;
	}
	memcpy(data, tmp_data, num * RKSS_DATA_SECTION_LEN);
	free(tmp_data);
	return 0;
}

static int rkss_read_section(struct rk_secure_storage *rkss)
{
	return rkss_read_multi_sections(rkss->data, rkss->index, 1);
}

static int rkss_write_multi_sections(unsigned char *data, unsigned long index, unsigned int num)
{
	unsigned char *tmp_data = NULL;
	unsigned long ret;
	int result;

	result = rkss_backup_sections(index, num);
	if (result < 0) {
		printf("TEEC: rkss_backup_sections fail\n");
		return -1;
	}

	if (check_security_exist(1) < 0)
		return -1;

	tmp_data = memalign(CONFIG_SYS_CACHELINE_SIZE, num * RKSS_DATA_SECTION_LEN);
	if (!tmp_data) {
		printf("TEEC: malloc tmp_data fail\n");
		return -1;
	}
	memcpy(tmp_data, data, num * RKSS_DATA_SECTION_LEN);
	ret = blk_dwrite(dev_desc, part_info.start + index, num, tmp_data);
	free(tmp_data);
	if (ret != num) {
		printf("TEEC: blk_dwrite fail\n");
		return -1;
	}
	return 0;
}

static int rkss_write_section(struct rk_secure_storage *rkss)
{
	return rkss_write_multi_sections(rkss->data, rkss->index, 1);
}

static int rkss_read_patition_tables(unsigned char *data)
{
	unsigned long ret;
	unsigned char *table_data = NULL;

	if (check_security_exist(1) < 0)
		return -1;

	table_data = memalign(CONFIG_SYS_CACHELINE_SIZE,
			      RKSS_DATA_SECTION_LEN * RKSS_PARTITION_TABLE_COUNT);
	if (!table_data) {
		printf("TEEC: malloc table_data fail\n");
		return -1;
	}
	ret = blk_dread(dev_desc, part_info.start, RKSS_PARTITION_TABLE_COUNT, table_data);
	if (ret != RKSS_PARTITION_TABLE_COUNT) {
		printf("TEEC: blk_dread fail\n");
		free(table_data);
		return -1;
	}
	memcpy(data, table_data, RKSS_DATA_SECTION_LEN * RKSS_PARTITION_TABLE_COUNT);
	free(table_data);
	return 0;
}

#ifdef DEBUG_RKSS
static void rkss_dump(void *data, unsigned int len)
{
	char *p = (char *)data;
	unsigned int i = 0;
	printf("-------------- DUMP %d --------------\n", len);
	for (i = 0; i < len; i++) {
		printf("%02x ", *(p + i));
	}
	printf("\n");
	printf("------------- DUMP END -------------\n");
}

static void rkss_dump_ptable(void)
{
	printf("-------------- DUMP ptable --------------\n");
	int i = 0, ret;
	unsigned char *table_data;

	table_data = malloc(RKSS_DATA_SECTION_LEN * RKSS_PARTITION_TABLE_COUNT);
	if (table_data == NULL) {
		printf("TEEC: malloc table_data fail\n");
		return;
	}
	ret = rkss_read_patition_tables(table_data);
	if (ret < 0) {
		printf("TEEC: rkss_read_patition_tables fail ! ret: %d.\n", ret);
		free(table_data);
		return;
	}

	for (i = 0; i < RKSS_PARTITION_TABLE_COUNT; i++) {
		struct rk_secure_storage rkss = {0};
		rkss.index = i;
		memcpy(rkss.data, table_data + rkss.index * RKSS_DATA_SECTION_LEN, RKSS_DATA_SECTION_LEN);

		int n ;
		for (n = 0; n < RKSS_EACH_SECTION_FILECOUNT; n++) {
			void *pdata = rkss.data;
			struct rkss_file_info *p = (struct rkss_file_info *)pdata;
			p += n;

			printf("[%02d][%c] %s , inx:%d, size:%d",
					i*RKSS_EACH_SECTION_FILECOUNT+n, p->used == 0 ? 'F':'T', p->name,
					p->index, p->size);
		}
	}
	free(table_data);
	printf("-------------- DUMP END --------------\n");
}

static void rkss_dump_usedflags(void)
{
	struct rk_secure_storage rkss = {0};
	rkss.index = RKSS_USED_FLAGS_INDEX;
	int ret = rkss_read_section(&rkss);
	if (ret < 0) {
		printf("TEEC: rkss_read_section fail ! ret: %d.\n", ret);
		return;
	}
	rkss_dump(rkss.data, RKSS_DATA_SECTION_LEN);
}
#endif

static int rkss_verify_ptable(unsigned char *table_data)
{
	unsigned char *cp, *vp;
	struct rkss_file_verification *verify;
	int ret, i, write_table_flag = 0;

	for (i = 0; i < RKSS_PARTITION_TABLE_COUNT; i++) {
		cp = table_data + (i * RKSS_DATA_SECTION_LEN);
		vp = cp + RKSS_DATA_SECTION_LEN - sizeof(struct rkss_file_verification);
		verify = (struct rkss_file_verification *)(void *)vp;

		if (verify->version != RKSS_VERSION_V1
				|| verify->checkstr != RKSS_CHECK_STR) {
			printf("TEEC: verify [%d] fail, cleanning ....", i);
			memset(cp, 0, RKSS_DATA_SECTION_LEN);
			verify->checkstr = RKSS_CHECK_STR;
			verify->version = RKSS_VERSION_V1;
			write_table_flag = 1;
		}
	}
	if (write_table_flag == 1) {
		ret = rkss_write_multi_sections(table_data, 0, RKSS_PARTITION_TABLE_COUNT);
		if (ret < 0) {
			printf("TEEC: rkss_write_multi_sections failed!!! ret: %d.\n", ret);
			return -1;
		}
	}
	debug("TEEC: verify ptable success.\n");
	return 0;
}

static int rkss_verify_usedflags(struct rk_secure_storage *rkss)
{
	uint8_t *flags = (uint8_t *)rkss->data;
	int i, duel, flag, n, value, ret;
	uint8_t *flagw;

	for (i = 0; i < RKSS_PARTITION_TABLE_COUNT + 1; i++) {
		duel = *(flags + (int)i/2);
		flag = i & 0x1 ? duel & 0x0F : (duel & 0xF0) >> 4;
		if (flag != 0x1) {
			debug("TEEC: init usedflags section ...\n");
			memset(rkss->data, 0x00, RKSS_DATA_SECTION_LEN);
			for (n = 0; n < RKSS_PARTITION_TABLE_COUNT + 1; n++) {
				flagw = (uint8_t *)rkss->data + (int)n/2;
				value = 0x1;
				*flagw = n & 0x1 ? (*flagw & 0xF0) | (value & 0x0F) :
						(*flagw & 0x0F) | (value << 4);
			}
			ret = rkss_write_multi_sections(rkss->data, rkss->index, 1);
			if (ret < 0) {
				printf("TEEC: clean usedflags section failed!!! ret: %d.\n", ret);
				return -1;
			}

			return 0;
		}
	}
	debug("TEEC: rkss_verify_usedflags: sucess.\n");
	return 0;
}

static int rkss_get_fileinfo_by_index(int fd, struct rkss_file_info *pfileinfo)
{
	int i = fd / RKSS_EACH_SECTION_FILECOUNT;
	int n = fd - (RKSS_EACH_SECTION_FILECOUNT * i);
	struct rk_secure_storage rkss = {0};
	int ret;
	void *pdata;
	struct rkss_file_info *p;

	rkss.index = i;
	ret = rkss_read_multi_sections(rkss.data, rkss.index, 1);
	if (ret < 0) {
		printf("TEEC: rkss_read_multi_sections fail ! ret: %d.\n", ret);
		return -1;
	}

	pdata = rkss.data;
	p = (struct rkss_file_info *)pdata;
	p += n;

	if (p->used != 1) {
		debug("TEEC: error: unused section!\n");
		return -1;
	}
	debug("TEEC: rkss_get_fileinfo_by_index p->used = %d p->name=%s p->index=%d p->size=%d\n",
		p->used, p->name, p->index, p->size);
	memcpy(pfileinfo, p, sizeof(struct rkss_file_info));

	return 0;
}

static int rkss_get_fileinfo_by_name(
		char *filename, struct rkss_file_info *pfileinfo)
{
	int i = 0, ret;
	uint8_t n = 0;
	unsigned int len;
	unsigned char *table_data;

	len = strlen(filename);
	if (len > RKSS_MAX_NAME_LENGTH - 1) {
		printf("TEEC: filename is too long. length:%u\n", len);
		return -1;
	}

	table_data = malloc(RKSS_DATA_SECTION_LEN * RKSS_PARTITION_TABLE_COUNT);
	if (table_data == NULL) {
		printf("TEEC: malloc table_data fail\n");
		return -1;
	}
	ret = rkss_read_patition_tables(table_data);
	if (ret < 0) {
		printf("TEEC: rkss_read_patition_tables fail ! ret: %d.\n", ret);
		free(table_data);
		return -1;
	}

	for (i = 0; i < RKSS_PARTITION_TABLE_COUNT; i++) {
		struct rk_secure_storage rkss = {0};
		rkss.index = i;
		memcpy(rkss.data, table_data + rkss.index * RKSS_DATA_SECTION_LEN, RKSS_DATA_SECTION_LEN);

		for (n = 0; n < RKSS_EACH_SECTION_FILECOUNT; n++) {
			void *pdata = rkss.data;
			struct rkss_file_info *p = (struct rkss_file_info *)pdata;
			p += n;

			if (p->used == 0)
				continue;

			if (!strcmp(p->name, filename)) {
				debug("TEEC: rkss_get_fileinfo_by_name: hit table[%d/%d], index[%d/%d]\n",
						i, RKSS_PARTITION_TABLE_COUNT, n, RKSS_EACH_SECTION_FILECOUNT);
				memcpy(pfileinfo, p, sizeof(struct rkss_file_info));
				free(table_data);
				return i * RKSS_EACH_SECTION_FILECOUNT + n;
			}

			// Folder Matching
			const char *split = "/";
			char *last_inpos = filename;
			char *last_svpos = p->name;
			char *cur_inpos = NULL;
			char *cur_svpos = NULL;
			do {
				cur_inpos = strstr(last_inpos, split);
				cur_svpos = strstr(last_svpos, split);
				int size_in = cur_inpos == NULL ?
						(int)strlen(last_inpos) : cur_inpos - last_inpos;
				int size_sv = cur_svpos == NULL ?
						(int)strlen(last_svpos) : cur_svpos - last_svpos;

				ret = memcmp(last_inpos, last_svpos, size_in);

				last_inpos = cur_inpos + 1;
				last_svpos = cur_svpos + 1;

				if (size_in != size_sv || ret)
					goto UNMATCHFOLDER;

			} while (cur_inpos && cur_svpos);

			debug("TEEC: Matched folder: %s\n", p->name);
			free(table_data);
			return -100;
UNMATCHFOLDER:
			debug("TEEC: Unmatched ...");
		}
	}
	debug("TEEC: rkss_get_fileinfo_by_name: file or dir no found!\n");
	free(table_data);
	return -1;
}

static int rkss_get_dirs_by_name(char *filename)
{
	int i = 0, ret;
	uint8_t n = 0;
	unsigned int len;
	unsigned char *table_data;

	len = strlen(filename);
	if (len > RKSS_MAX_NAME_LENGTH - 1) {
		printf("TEEC: filename is too long. length:%u\n", len);
		return -1;
	}

	table_data = malloc(RKSS_DATA_SECTION_LEN * RKSS_PARTITION_TABLE_COUNT);
	if (table_data == NULL) {
		printf("TEEC: malloc table_data fail\n");
		return -1;
	}
	ret = rkss_read_patition_tables(table_data);
	if (ret < 0) {
		printf("TEEC: rkss_read_patition_tables fail ! ret: %d.\n", ret);
		free(table_data);
		return -1;
	}

	dir_num = 0;
	for (i = 0; i < RKSS_PARTITION_TABLE_COUNT; i++) {
		struct rk_secure_storage rkss = {0};
		rkss.index = i;
		memcpy(rkss.data, table_data + rkss.index * RKSS_DATA_SECTION_LEN, RKSS_DATA_SECTION_LEN);

		for (n = 0; n < RKSS_EACH_SECTION_FILECOUNT; n++) {
			void *pdata = rkss.data;
			struct rkss_file_info *p = (struct rkss_file_info *)pdata;
			p += n;

			if (p->used == 0)
				continue;

			// Full Matching
			ret = memcmp(p->name, filename, strlen(filename));
			debug("TEEC: comparing [fd:%d] : %s ?= %s , ret:%d\n",
					i*RKSS_EACH_SECTION_FILECOUNT+n, p->name, filename, ret);
			if (!ret && strlen(p->name) > strlen(filename)) {
				char *chk = p->name + strlen(filename);
				if (*chk == '/') {
					char *file = p->name + strlen(filename) + 1;
					char *subdir = strtok(file, "/");
					debug("TEEC: found: %s\n", subdir);
					strcpy(dir_cache[dir_num], subdir);
					++dir_num;
				}
			}
		}
	}
	free(table_data);
	return dir_num;
}

static int rkss_get_empty_section_from_usedflags(int section_size)
{
	struct rk_secure_storage rkss = {0};
	rkss.index = RKSS_USED_FLAGS_INDEX;
	int ret = rkss_read_section(&rkss);
	if (ret < 0) {
		printf("TEEC: rkss_read_section fail ! ret: %d.\n", ret);
		return -1;
	}

	int i = 0;
	int count0 = 0;
	for (i = 0; i < RKSS_DATA_SECTION_COUNT; i++) {
		uint8_t *flag = (uint8_t *)rkss.data + (int)i/2;
		uint8_t value = i & 0x1 ? *flag & 0x0F : (*flag & 0xF0) >> 4;

		if (value == 0x0) {
			if (++count0 == section_size)
				return (i + 1 - section_size);
		} else {
			count0 = 0;
		}
	}

	printf("TEEC: Not enough space available in secure storage !\n");
	return -10;
}

static int rkss_incref_multi_usedflags_sections(unsigned int index, unsigned int num)
{
	struct rk_secure_storage rkss = {0};
	int ret, value, i;
	uint8_t *flag;

	if ((index + num) >= RKSS_DATA_SECTION_COUNT) {
		printf("TEEC: index[%d] out of range.\n", index);
		return -1;
	}

	rkss.index = RKSS_USED_FLAGS_INDEX;
	ret = rkss_read_multi_sections(rkss.data, rkss.index, 1);
	if (ret < 0) {
		printf("TEEC: rkss_read_multi_sections fail ! ret: %d.\n", ret);
		return -1;
	}

	for (i = 0; i < num; i++, index++) {
		flag = (uint8_t *)rkss.data + (int)index/2;
		value = index & 0x1 ? *flag & 0x0F : (*flag & 0xF0) >> 4;
		if (++value > 0xF) {
			printf("TEEC: reference out of data: %d\n", value);
			value = 0xF;
		}
		*flag = index & 0x1 ? (*flag & 0xF0) | (value & 0x0F) :
				(*flag & 0x0F) | (value << 4);
	}
	ret = rkss_write_multi_sections(rkss.data, rkss.index, 1);
	if (ret < 0) {
		printf("TEEC: rkss_write_multi_sections fail ! ret: %d.\n", ret);
		return -1;
	}
	return 0;
}

static int rkss_decref_multi_usedflags_sections(unsigned int index, unsigned int num)
{
	struct rk_secure_storage rkss = {0};
	int ret, value, i;
	uint8_t *flag;

	if ((index + num) >= RKSS_DATA_SECTION_COUNT) {
		printf("TEEC: index[%d] out of range.\n", index);
		return -1;
	}

	rkss.index = RKSS_USED_FLAGS_INDEX;
	ret = rkss_read_multi_sections(rkss.data, rkss.index, 1);
	if (ret < 0) {
		printf("TEEC: rkss_read_multi_sections fail ! ret: %d.\n", ret);
		return -1;
	}
	for (i = 0; i < num; i++, index++) {
		flag = (uint8_t *)rkss.data + (int)index/2;
		value = index & 0x1 ? *flag & 0x0F : (*flag & 0xF0) >> 4;
		if (--value < 0) {
			printf("TEEC: reference out of data: %d\n", value);
			value = 0x0;
		}
		*flag = index & 0x1 ? (*flag & 0xF0) | (value & 0x0F) :
				(*flag & 0x0F) | (value << 4);
	}
	ret = rkss_write_multi_sections(rkss.data, rkss.index, 1);
	if (ret < 0) {
		printf("TEEC: rkss_write_multi_sections fail ! ret: %d.\n", ret);
		return -1;
	}
	return 0;
}

static int rkss_write_empty_ptable(struct rkss_file_info *pfileinfo)
{
	int i = 0, ret;
	unsigned char *table_data;

	table_data = malloc(RKSS_DATA_SECTION_LEN * RKSS_PARTITION_TABLE_COUNT);
	if (table_data == NULL) {
		printf("TEEC: malloc table_data fail\n");
		return -1;
	}

	ret = rkss_read_patition_tables(table_data);
	if (ret < 0) {
		printf("TEEC: rkss_read_patition_tables fail ! ret: %d.\n", ret);
		free(table_data);
		return -1;
	}

	for (i = 0; i < RKSS_PARTITION_TABLE_COUNT; i++) {
		struct rk_secure_storage rkss = {0};
		rkss.index = i;
		memcpy(rkss.data, table_data + rkss.index * RKSS_DATA_SECTION_LEN, RKSS_DATA_SECTION_LEN);

		int n = 0;
		for (n = 0; n < RKSS_EACH_SECTION_FILECOUNT; n++) {
			void *pdata = rkss.data;
			struct rkss_file_info *p = (struct rkss_file_info *)pdata;
			p += n;
			if (p->used == 0) {
				debug("TEEC: write ptable in [%d][%d] .\n", i, n);
				memcpy(p, pfileinfo, sizeof(struct rkss_file_info));
				p->used = 1;
				p->id = n;
				debug("TEEC: write emt ptable : [%d,%d] name:%s, index:%d, size:%d, used:%d\n",
						i, n, p->name, p->index, p->size, p->used);
				ret = rkss_write_section(&rkss);
				if (ret < 0) {
					printf("TEEC: rkss_write_section fail ! ret: %d.\n", ret);
					free(table_data);
					return -1;
				}
				free(table_data);
				return i * RKSS_EACH_SECTION_FILECOUNT + n;
			}
		}
	}
	printf("TEEC: No enough ptable space available in secure storage.\n");
	free(table_data);
	return -1;
}

static int rkss_write_back_ptable(int fd, struct rkss_file_info *pfileinfo)
{
	int i = fd / RKSS_EACH_SECTION_FILECOUNT;
	int n = fd - (RKSS_EACH_SECTION_FILECOUNT * i);

	struct rk_secure_storage rkss = {0};
	rkss.index = i;
	int ret = rkss_read_section(&rkss);
	if (ret < 0) {
		debug("TEEC: rkss_read_section fail ! ret: %d.\n", ret);
		return -1;
	}

	void *pdata = rkss.data;
	struct rkss_file_info *p = (struct rkss_file_info *)pdata;
	p += n;

	memcpy(p, pfileinfo, sizeof(struct rkss_file_info));
	debug("TEEC: write ptable : [%d,%d] name:%s, index:%d, size:%d, used:%d\n",
			i, n, p->name, p->index, p->size, p->used);

	ret = rkss_write_section(&rkss);
	if (ret < 0) {
		debug("TEEC: rkss_write_section fail ! ret: %d.\n", ret);
		return -1;
	}

	return 0;
}

static int tee_fs_open(struct tee_fs_rpc *fsrpc)
{
	int make_newfile = 0;
	char *filename = (char *)(fsrpc + 1);

	if (strlen(filename) > RKSS_MAX_NAME_LENGTH) {
		debug("TEEC: tee_fs_open: file name too long. %s\n", filename);
		return -1;
	}

	debug("TEEC: tee_fs_open open file: %s, len: %zu\n", filename, strlen(filename));
	struct rkss_file_info p = {0};
	int ret = rkss_get_fileinfo_by_name(filename, &p);
	if (ret < 0) {
		debug("TEEC: tee_fs_open : no such file. %s\n", filename);
		make_newfile = 1;
	} else {
		fsrpc->fd = ret;
		file_seek = 0;
		if (CHECKFLAG(fsrpc->flags, TEE_FS_O_APPEND)) {
			file_seek = p.size;
		}
	}

	ret = rkss_begin_commit();
	if (ret < 0) {
		printf("TEEC: rkss_begin_commit failed!");
		return -1;
	}

	if (make_newfile) {
		if (CHECKFLAG(fsrpc->flags, TEE_FS_O_CREAT)) {
			debug("TEEC: tee_fs_open create new file: %s\n", filename);
			strcpy(p.name, filename);
			p.index = 0;
			p.size = fsrpc->len;
			p.used = 1;
			p.flags = RK_FS_R | RK_FS_W;
			ret = rkss_write_empty_ptable(&p);
			if (ret < 0) {
				printf("TEEC: tee_fs_open : error. %s\n", filename);
				return -1;
			}
			fsrpc->fd = ret;
			file_seek = 0;
		} else {
			debug("TEEC: and no create flag found.\n");
			return -1;
		}
	}

	debug("TEEC: tee_fs_open ! %s , fd:%d, flag: %x, len: %d\n",
			filename, fsrpc->fd, fsrpc->flags, fsrpc->len);

	ret = rkss_finish_commit();
	if (ret < 0) {
		printf("TEEC: rkss_finish_commit failed!");
		return -1;
	}

	return fsrpc->fd;
}

static int tee_fs_close(struct tee_fs_rpc *fsrpc)
{
	debug("TEEC: tee_fs_close !\n");
	UNREFERENCED_PARAMETER(fsrpc);
	return 0;
}

static int tee_fs_read(struct tee_fs_rpc *fsrpc)
{
	debug("TEEC: tee_fs_read! fd:%d, len:%d\n", fsrpc->fd, fsrpc->len);
	void *data = (void *)(fsrpc + 1);

	struct rkss_file_info p = {0};
	int ret = rkss_get_fileinfo_by_index(fsrpc->fd, &p);
	if (ret < 0) {
		printf("TEEC: unavailable fd !\n");
		return -1;
	}

	if (file_seek != 0) {
		printf("TEEC: warning !!! file_seek != 0. unsupported now.\n");
	}

	int num = fsrpc->len / RKSS_DATA_SECTION_LEN + 1;
	int di = 0;
	debug("TEEC: reading section[%d], fd:%d, len:%d, filesize:%d\n",
			p.index, fsrpc->fd, fsrpc->len, p.size);

	uint8_t *temp_file_data = malloc(num * RKSS_DATA_SECTION_LEN);
	ret = rkss_read_multi_sections(temp_file_data, p.index, num);
	if (ret < 0) {
		printf("TEEC: unavailable file index\n");
		free(temp_file_data);
		return -1;
	}
	di = fsrpc->len > p.size ? p.size : fsrpc->len;
	memcpy(data, temp_file_data, di);
	free(temp_file_data);
	temp_file_data = 0;
	return di;
}

static int tee_fs_write(struct tee_fs_rpc *fsrpc)
{
	debug("TEEC: tee_fs_write ! fd:%d, lenth:%d\n", fsrpc->fd, fsrpc->len);
	void *data = (void *)(fsrpc + 1);

	if (fsrpc->fd < 0) {
		printf("TEEC: tee_fs_write error ! wrong fd : %d\n", fsrpc->fd);
		return -1;
	}

	if (file_seek != 0) {
		printf("TEEC: warning !!! file_seek != 0. unsupported now.\n");
	}

	struct rkss_file_info p = {0};
	int ret = rkss_get_fileinfo_by_index(fsrpc->fd, &p);
	if (ret < 0) {
		printf("TEEC: tee_fs_write: fd unvailable!\n");
		return -1;
	}

	ret = rkss_begin_commit();
	if (ret < 0) {
		printf("TEEC: rkss_begin_commit failed!");
		return -1;
	}
	int num;
	if (p.size != 0) {
		num = p.size / RKSS_DATA_SECTION_LEN + 1;
		ret = rkss_decref_multi_usedflags_sections(p.index, num);
		if (ret < 0) {
			printf("TEEC: rkss_decref_multi_usedflags_sections error !\n");
			return -1;
		}
	}

	p.size = fsrpc->len;
	num = fsrpc->len / RKSS_DATA_SECTION_LEN + 1;
	p.index = rkss_get_empty_section_from_usedflags(num);
	debug("TEEC: Get Empty section in %d\n", p.index);
	p.used = 1;

	ret = rkss_incref_multi_usedflags_sections(p.index, num);
	if (ret < 0) {
		printf("TEEC: rkss_incref_multi_usedflags_sections error !\n");
		ret = -1;
	}

	ret = rkss_write_back_ptable(fsrpc->fd, &p);
	if (ret < 0) {
		printf("TEEC: tee_fs_write: write ptable error!\n");
		return -1;
	}

	uint8_t *temp_file_data = malloc(num * RKSS_DATA_SECTION_LEN);
	memset(temp_file_data, 0, num * RKSS_DATA_SECTION_LEN);
	memcpy(temp_file_data, data, p.size);
	rkss_write_multi_sections(temp_file_data, p.index, num);
	free(temp_file_data);
	temp_file_data = 0;

#ifdef DEBUG_RKSS
	rkss_dump_usedflags();
#endif

	ret = rkss_finish_commit();
	if (ret < 0) {
		printf("TEEC: rkss_finish_commit failed!");
		return -1;
	}

	return fsrpc->len;
}

static int tee_fs_seek(struct tee_fs_rpc *fsrpc)
{
	debug("TEEC: tee_fs_seek ! fd:%d, seek:%d, flag:%x\n", fsrpc->fd, fsrpc->arg, fsrpc->flags);

	if (fsrpc->flags == TEE_FS_SEEK_CUR) {
		fsrpc->res = file_seek + fsrpc->arg;
	} else if (fsrpc->flags == TEE_FS_SEEK_SET) {
		file_seek = fsrpc->arg;
		fsrpc->res = file_seek;
	} else if (fsrpc->flags == TEE_FS_SEEK_END) {
		struct rkss_file_info p = {0};
		int ret = rkss_get_fileinfo_by_index(fsrpc->fd, &p);
		if (ret < 0) {
			printf("TEEC: unavilable fd.\n");
			return -1;
		}
		file_seek = p.size + fsrpc->arg;
		fsrpc->res = file_seek;
	} else {
		printf("TEEC: tee_fs_seek: unsupport seed mode.\n");
		return -1;
	}

	return fsrpc->res;
}

static int tee_fs_unlink(struct tee_fs_rpc *fsrpc)
{
	char *filename = (char *)(fsrpc + 1);

	struct rkss_file_info p = {0};
	int ret = rkss_get_fileinfo_by_name(filename, &p);
	if (ret < 0) {
		printf("TEEC: tee_fs_unlink : no such file. %s\n", filename);
		return 0;
	}
	int fd = ret;

	debug("TEEC: tee_fs_unlink ! %s fd:%d index:%d size:%d\n", filename, fd, p.index, p.size);

	ret = rkss_begin_commit();
	if (ret < 0) {
		printf("TEEC: rkss_begin_commit failed!");
		return -1;
	}

	/* decrease ref from usedflags */
	int num = p.size / RKSS_DATA_SECTION_LEN + 1;
	ret = rkss_decref_multi_usedflags_sections(p.index, num);
	if (ret < 0) {
		printf("TEEC: rkss_decref_multi_usedflags_sections error !\n");
		return -1;
	}

	/* rm from ptable */
	memset(&p, 0, sizeof(struct rkss_file_info));
	ret = rkss_write_back_ptable(fd, &p);
	if (ret < 0) {
		printf("TEEC: tee_fs_unlink : write back error %d\n", ret);
		return -1;
	}

#ifdef DEBUG_RKSS
	rkss_dump_ptable();
#endif

	ret = rkss_finish_commit();
	if (ret < 0) {
		printf("TEEC: rkss_finish_commit failed!");
		return -1;
	}

	return 0;
}

static int tee_fs_link(struct tee_fs_rpc *fsrpc)
{
	char *filename = (char *)(fsrpc + 1);
	size_t offset_new_fn = strlen(filename) + 1;
	char *newfilename = filename + offset_new_fn;
	debug("TEEC: tee_fs_link ! %s -> %s\n", filename, newfilename);

	struct rkss_file_info p_old = {0};
	int ret = rkss_get_fileinfo_by_name(filename, &p_old);
	if (ret < 0) {
		printf("TEEC: cannot find src file %s.\n", filename);
		return -1;
	}

	struct rkss_file_info p_check = {0};
	ret = rkss_get_fileinfo_by_name(newfilename, &p_check);
	if (ret >= 0) {
		printf("TEEC: file exist ! %s.\n", newfilename);
		return -1;
	}
	ret = rkss_begin_commit();
	if (ret < 0) {
		printf("TEEC: rkss_begin_commit failed!");
		return -1;
	}

	struct rkss_file_info p_new = {0};
	memcpy(&p_new, &p_old, sizeof(struct rkss_file_info));
	strcpy(p_new.name, newfilename);
	ret = rkss_write_empty_ptable(&p_new);
	if (ret < 0) {
		printf("TEEC: tee_fs_open : error. %s\n", filename);
		return -1;
	}

	int num = p_new.size / RKSS_DATA_SECTION_LEN + 1;
	ret = rkss_incref_multi_usedflags_sections(p_new.index, num);
	if (ret < 0) {
		printf("TEEC: rkss_incref_multi_usedflags_sections error !\n");
		return -1;
	}

#ifdef DEBUG_RKSS
	rkss_dump_ptable();
#endif
	ret = rkss_finish_commit();
	if (ret < 0) {
		printf("TEEC: rkss_finish_commit failed!");
		return -1;
	}

	return 0;
}

static int tee_fs_rename(struct tee_fs_rpc *fsrpc)
{
	char *filenames = (char *)(fsrpc + 1);
	char *newnames = filenames + strlen(filenames) + 1;
	debug("TEEC: rename: %s -> %s\n", filenames, newnames);

	struct rkss_file_info p = {0};
	int ret = rkss_get_fileinfo_by_name(filenames, &p);
	if (ret < 0) {
		printf("TEEC: filename no found .\n");
		return -1;
	}

	ret = rkss_begin_commit();
	if (ret < 0) {
		printf("TEEC: rkss_begin_commit failed!");
		return -1;
	}

	strcpy(p.name, newnames);

	ret = rkss_write_back_ptable(ret, &p);
	if (ret < 0) {
		printf("TEEC: write ptable error!\n");
		return -1;
	}

	ret = rkss_finish_commit();
	if (ret < 0) {
		printf("TEEC: rkss_finish_commit failed!");
		return -1;
	}

	return 0;
}

static int tee_fs_truncate(struct tee_fs_rpc *fsrpc)
{
	int section_num, new_section_num, free_section_num;
	uint16_t free_index;

	debug("TEEC: tee_fs_truncate: fd:%d, lenth:%d\n", fsrpc->fd, fsrpc->arg);
	if (fsrpc->fd < 0) {
		printf("TEEC: tee_fs_truncate: fd unavilable !\n");
		return -1;
	}

	struct rkss_file_info p = {0};
	int ret = rkss_get_fileinfo_by_index(fsrpc->fd, &p);
	if (ret < 0) {
		printf("TEEC: fd unvailable!\n");
		return -1;
	}
	ret = rkss_begin_commit();
	if (ret < 0) {
		printf("TEEC: rkss_begin_commit failed!");
		return -1;
	}
	if (p.size < fsrpc->arg) {
		printf("TEEC: truncate size not support!\n ");
		return -1;
	} else {
		section_num = p.size / RKSS_DATA_SECTION_LEN + 1;
		new_section_num = fsrpc->arg / RKSS_DATA_SECTION_LEN + 1;
		free_section_num = section_num - new_section_num;
		free_index = p.index + new_section_num;
		ret = rkss_decref_multi_usedflags_sections(free_index, free_section_num);
		if (ret < 0) {
			printf("TEEC: rkss_decref_multi_usedflags_sections error!\n");
			return -1;
		}
		p.size = fsrpc->arg;
		ret = rkss_write_back_ptable(fsrpc->fd, &p);
		if (ret < 0) {
			printf("TEEC: rkss_write_back_ptable error!\n");
			return -1;
		}
	}

	ret = rkss_finish_commit();
	if (ret < 0) {
		printf("TEEC: rkss_finish_commit failed!");
		return -1;
	}
	return 0;
}

static int tee_fs_mkdir(struct tee_fs_rpc *fsrpc)
{
	char *dirname = (char *)(fsrpc + 1);
	UNREFERENCED_PARAMETER(dirname);
	debug("TEEC: tee_fs_mkdir: %s\n", dirname);
	return 0;
}

static int tee_fs_opendir(struct tee_fs_rpc *fsrpc)
{
	char *dirname = (char *)(fsrpc + 1);
	dir_seek = 0;
	int ret = rkss_get_dirs_by_name(dirname);
	if (ret < 0) {
		printf("TEEC: tee_fs_opendir: error\n");
	}
	debug("TEEC: tee_fs_opendir: %s, seek/num:%d/%d\n", dirname, dir_seek, dir_num);
	return 0;
}

static int tee_fs_closedir(struct tee_fs_rpc *fsrpc)
{
	char *dirname = (char *)(fsrpc + 1);
	UNREFERENCED_PARAMETER(dirname);
	debug("TEEC: tee_fs_closedir: %s\n", dirname);
	dir_seek = 0;
	dir_num = 0;
	return 0;
}

static int tee_fs_readdir(struct tee_fs_rpc *fsrpc)
{
	char *dirname = (char *)(fsrpc + 1);
	debug("TEEC: seek/num:%d/%d\n", dir_seek, dir_num);
	if (dir_seek == dir_num) {
		dirname = NULL;
		fsrpc->len = 0;
		debug("TEEC: tee_fs_readdir: END\n");
		return -1;
	}

	strcpy(dirname, dir_cache[dir_seek]);
	fsrpc->len = strlen(dir_cache[dir_seek]) + 1;
	++dir_seek;

	debug("TEEC: tee_fs_readdir: %s\n", dirname);
	return 0;
}

static int tee_fs_rmdir(struct tee_fs_rpc *fsrpc)
{
	char *dirname = (char *)(fsrpc + 1);
	debug("TEEC: tee_fs_rmdir: %s\n", dirname);

	struct rkss_file_info p = {0};
	int ret = rkss_get_fileinfo_by_name(dirname, &p);
	if (ret == -100) {
		printf("TEEC: dir is not empty.\n");
		return -1;
	} else if (ret >= 0) {
		printf("TEEC: %s is not a dir.\n", p.name);
		return -1;
	}
	debug("TEEC: rmdir success.\n");
	return 0;
}

static int tee_fs_access(struct tee_fs_rpc *fsrpc)
{
	char *filename = (char *)(fsrpc + 1);
	debug("TEEC: tee_fs_access: name:%s,flag:%x\n", filename, fsrpc->flags);

	struct rkss_file_info p = {0};
	int ret = rkss_get_fileinfo_by_name(filename, &p);
	if (ret < 0 && ret != -100) {
		debug("TEEC: tee_fs_access: %s no such file or directory.\n", filename);
		return -1;
	}

	if (CHECKFLAG(fsrpc->flags, TEE_FS_R_OK)) {
		if (!CHECKFLAG(p.flags, RK_FS_R)) {
			printf("TEEC: tee_fs_access: no permission FS_R_OK in %x.\n", p.flags);
			return -1;
		}
	}

	if (CHECKFLAG(fsrpc->flags, TEE_FS_W_OK)) {
		if (!CHECKFLAG(p.flags, RK_FS_W)) {
			printf("TEEC: tee_fs_access: no permission FS_W_OK in %x.\n", p.flags);
			return -1;
		}
	}
	return 0;
}

int tee_supp_rk_fs_init_v1(void)
{
	assert(sizeof(struct rkss_file_info) == 126);
	assert(512 / sizeof(struct rkss_file_info) == RKSS_EACH_SECTION_FILECOUNT);

	__maybe_unused int i = 0;
	unsigned char *table_data;
	int ret;

	if (check_security_exist(0) < 0)
		return 0;

	ret = rkss_resume();
	if (ret < 0) {
		printf("TEEC: rkss_resume failed!\n");
		return -1;
	}
#ifdef DEBUG_CLEAN_RKSS // clean secure storage
	for (i = 0; i < RKSS_DATA_SECTION_COUNT; i++) {
		struct rk_secure_storage rkss = {0};
		memset(rkss.data, 0, RKSS_DATA_SECTION_LEN);
		rkss.index = i;
		rkss_write_section(&rkss);
		printf("TEEC: cleaned [%d]", i);
	}
#endif

	ret = rkss_begin_commit();
	if (ret < 0) {
		printf("TEEC: rkss_begin_commit failed!\n");
		return -1;
	}

	// Verify Partition Table
	table_data = malloc(RKSS_DATA_SECTION_LEN * RKSS_PARTITION_TABLE_COUNT);
	if (table_data == NULL) {
		printf("TEEC: malloc table_data fail\n");
		return -1;
	}
	ret = rkss_read_patition_tables(table_data);
	if (ret < 0) {
		printf("TEEC: rkss_read_patition_tables fail ! ret: %d.\n", ret);
		free(table_data);
		return -1;
	}

	/* Verify Partition Table*/
	ret = rkss_verify_ptable(table_data);
	if (ret < 0) {
		printf("TEEC: rkss_verify_ptable fail ! ret: %d.\n", ret);
		free(table_data);
		return -1;
	}
	free(table_data);
	table_data = NULL;

	// Verify Usedflags Section
	struct rk_secure_storage rkss = {0};
	rkss.index = RKSS_USED_FLAGS_INDEX;
	ret = rkss_read_section(&rkss);
	if (ret < 0) {
		printf("TEEC: rkss_read_section fail ! ret: %d.\n", ret);
		return -1;
	}
	ret = rkss_verify_usedflags(&rkss);
	if (ret < 0) {
		printf("TEEC: rkss_verify_usedflags fail ! ret: %d.\n", ret);
		return -1;
	}

#ifdef DEBUG_RKSS
	rkss_dump_ptable();
	rkss_dump_usedflags();
#endif

	ret = rkss_begin_commit();
	if (ret < 0) {
		printf("TEEC: rkss_begin_commit failed!\n");
		return -1;
	}

	return 0;
}

static int rkss_step;
int tee_supp_rk_fs_process_v1(void *cmd, size_t cmd_size)
{
	struct tee_fs_rpc *fsrpc = cmd;
	int ret = -1;

	if (check_security_exist(0) < 0) {
		printf("TEEC: security partition not exist! unable to use RK FS!\n");
		return ret;
	}

	if (cmd_size < sizeof(struct tee_fs_rpc)) {
		printf(">>>cmd_size < sizeof(struct tee_fs_rpc) !\n");
		return ret;
	}

	if (cmd == NULL) {
		printf(">>>cmd == NULL !\n");
		return ret;
	}

	switch (fsrpc->op) {
	case TEE_FS_OPEN:
		debug(">>>>>>> [%d] TEE_FS_OPEN !\n", rkss_step++);
		ret = tee_fs_open(fsrpc);
		break;
	case TEE_FS_CLOSE:
		debug(">>>>>>> [%d] TEE_FS_CLOSE !\n", rkss_step++);
		ret = tee_fs_close(fsrpc);
		break;
	case TEE_FS_READ:
		debug(">>>>>>> [%d] TEE_FS_READ !\n", rkss_step++);
		ret = tee_fs_read(fsrpc);
		break;
	case TEE_FS_WRITE:
		debug(">>>>>>> [%d] TEE_FS_WRITE !\n", rkss_step++);
		ret = tee_fs_write(fsrpc);
		break;
	case TEE_FS_SEEK:
		debug(">>>>>>> [%d] TEE_FS_SEEK !\n", rkss_step++);
		ret = tee_fs_seek(fsrpc);
		break;
	case TEE_FS_UNLINK:
		debug(">>>>>>> [%d] TEE_FS_UNLINK !\n", rkss_step++);
		ret = tee_fs_unlink(fsrpc);
		break;
	case TEE_FS_RENAME:
		debug(">>>>>>> [%d] TEE_FS_RENAME !\n", rkss_step++);
		ret = tee_fs_rename(fsrpc);
		break;
	case TEE_FS_TRUNC:
		debug(">>>>>>> [%d] TEE_FS_TRUNC !\n", rkss_step++);
		ret = tee_fs_truncate(fsrpc);
		break;
	case TEE_FS_MKDIR:
		debug(">>>>>>> [%d] TEE_FS_MKDIR !\n", rkss_step++);
		ret = tee_fs_mkdir(fsrpc);
		debug(">>>>>>> ret = [%d]  ! \n", ret);
		break;
	case TEE_FS_OPENDIR:
		debug(">>>>>>> [%d] TEE_FS_OPENDIR !\n", rkss_step++);
		ret = tee_fs_opendir(fsrpc);
		break;
	case TEE_FS_CLOSEDIR:
		debug(">>>>>>> [%d] TEE_FS_CLOSEDIR !\n", rkss_step++);
		ret = tee_fs_closedir(fsrpc);
		break;
	case TEE_FS_READDIR:
		debug(">>>>>>> [%d] TEE_FS_READDIR !\n", rkss_step++);
		ret = tee_fs_readdir(fsrpc);
		break;
	case TEE_FS_RMDIR:
		debug(">>>>>>> [%d] TEE_FS_RMDIR !\n", rkss_step++);
		ret = tee_fs_rmdir(fsrpc);
		break;
	case TEE_FS_ACCESS:
		debug(">>>>>>> [%d] TEE_FS_ACCESS !\n", rkss_step++);
		ret = tee_fs_access(fsrpc);
		break;
	case TEE_FS_LINK:
		debug(">>>>>>> [%d] TEE_FS_LINK !\n", rkss_step++);
		ret = tee_fs_link(fsrpc);
		break;
	default:
		printf(">>>>> DEFAULT !! %d\n", fsrpc->op);
		break;
	}

	fsrpc->res = ret;
	debug(">>>>>>> fsrpc->res = [%d]	!\n", fsrpc->res);

	return ret;
}

