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
 *	RK Secure Storage Version 2
 *		Area0 Backup 0 Size : 256 kb	<---->	Area0 Backup 1 Size : 256 kb
 *		Area1 Backup 0 Size : 256 kb	<---->	Area1 Backup 1 Size : 256 kb
 *
 *	------ 1 section is 512 bytes -----
 *	------ Area0 Backup0 section from 0 to 511 --------
 *	1 section for file header		[0]
 *	1 section for used flags		[1]
 *		- 1 byte = 2 flag
 *	62 section for file tables		[2-63]
 *		- size of table 128 bytes
 *	447 section for data			[64-510]
 *	1 section for file footer		[511]
 *
 * 	------ Area0 Backup1 section from 512 to 1023 --------
 *	1 section for file header		[512]
 *	1 section for used flags		[513]
 *		- 1 byte = 2 flag
 *	62 section for file tables		[514-575]
 *		- size of table 128 bytes
 *	447 section for data			[576-1022]
 *	1 section for file footer		[1023]
 *
 * 	------ Area1 Backup0 section from 1024 to 1535 --------
 *	1 section for file header		[1024]
 *	1 section for used flags		[1025]
 *		- 1 byte = 2 flag
 *	62 section for file tables		[1026-1087]
 *		- size of table 128 bytes
 *	447 section for data			[1088-1534]
 *	1 section for file footer		[1535]
 *
 * 	------ Area1 Backup1 section from 1536 to 2047 --------
 *	1 section for file header		[1536]
 *	1 section for used flags		[1537]
 *		- 1 byte = 2 flag
 *	62 section for file tables		[1538-1599]
 *		- size of table 128 bytes
 *	447 section for data			[1600-2046]
 *	1 section for file footer		[2047]
 */

/* define for backup */
#define RKSS_HEADER_INDEX		0
#define RKSS_HEADER_COUNT		1
#define RKSS_USEDFLAGS_INDEX		1
#define RKSS_USEDFLAGS_COUNT		1
#define RKSS_TABLE_INDEX		2
#define RKSS_TABLE_COUNT		62
#define RKSS_DATA_INDEX			64
#define RKSS_DATA_COUNT			447
#define RKSS_FOOTER_INDEX		511
#define RKSS_FOOTER_COUNT		1
#define RKSS_SECTION_COUNT		512

#define RKSS_MAX_AREA_NUM		8
#define RKSS_ACTIVE_AREA_NUM		2
#define RKSS_DATA_LEN			512
#define RKSS_EACH_FILEFOLDER_COUNT	4
#define RKSS_TABLE_SIZE			128
#define RKSS_NAME_MAX_LENGTH		112
#define RKSS_BACKUP_NUM			2
#define RKSS_TAG			0x524B5353

struct rkss_file_header {
	uint32_t	tag;
	uint32_t	version;
	uint32_t	backup_count;
	uint16_t	backup_index;
	uint16_t	backup_dirty;
	uint8_t		reserve[496];
};
struct rkss_file_table {
	uint32_t	size;
	uint16_t	index;
	uint8_t		flags;
	uint8_t		used;
	char		name[RKSS_NAME_MAX_LENGTH];
	uint8_t		reserve[8];
};
struct rkss_file_footer {
	uint8_t		reserve[508];
	uint32_t	backup_count;
};
struct rkss_file {
	struct rkss_file_header *header;
	uint8_t	*flags;
	struct rkss_file_table *table;
	uint8_t	*data;
	struct rkss_file_footer *footer;
};

/* RK Secure Storage Calls */
static int file_seek;
static char dir_cache[RKSS_NAME_MAX_LENGTH][12];
static int dir_num;
static int dir_seek;
static uint8_t *rkss_buffer[RKSS_MAX_AREA_NUM];
static struct rkss_file rkss_info[RKSS_MAX_AREA_NUM];

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

static int rkss_verify_usedflags(unsigned int area_index)
{
	uint8_t *flags;
	int i, duel, flag, n, value;
	uint8_t *flagw;
	int used_count;

	if (area_index >= RKSS_MAX_AREA_NUM) {
		printf("TEEC: Not support area_index 0x%x\n", area_index);
		return -1;
	}

	flags = rkss_info[area_index].flags;
	if (flags == NULL) {
		printf("TEEC: %s flags is null\n", __func__);
		return -1;
	}

	used_count = RKSS_HEADER_COUNT +
		RKSS_USEDFLAGS_COUNT +
		RKSS_TABLE_COUNT;

	for (i = 0; i < used_count; i++) {
		duel = *(flags + (int)i/2);
		flag = i & 0x1 ? duel & 0x0F : (duel & 0xF0) >> 4;
		if (flag != 0x1)
			goto init;
	}

	for (i = RKSS_FOOTER_INDEX; i < RKSS_USEDFLAGS_COUNT * RKSS_DATA_LEN * 2; i++) {
		duel = *(flags + (int)i/2);
		flag = i & 0x1 ? duel & 0x0F : (duel & 0xF0) >> 4;
		if (flag != 0x1)
			goto init;
	}

	debug("TEEC: %s: success.\n", __func__);
	return 0;

init:
	debug("TEEC: init usedflags section ...\n");
	memset(flags, 0, RKSS_USEDFLAGS_COUNT * RKSS_DATA_LEN);
	for (n = 0; n < used_count; n++) {
		flagw = flags + (int)n/2;
		value = 0x1;
		*flagw = n & 0x1 ? (*flagw & 0xF0) | (value & 0x0F) :
				(*flagw & 0x0F) | (value << 4);
	}

	for (n = RKSS_FOOTER_INDEX; n < RKSS_USEDFLAGS_COUNT * RKSS_DATA_LEN * 2; n++) {
		flagw = flags + (int)n/2;
		value = 0x1;
		*flagw = n & 0x1 ? (*flagw & 0xF0) | (value & 0x0F) :
				(*flagw & 0x0F) | (value << 4);
	}
	return 0;
}

#ifdef DEBUG_CLEAN_RKSS
static int rkss_storage_delete(uint32_t area_index)
{
	int ret;
	uint32_t size;
	uint8_t *delete_buff;

	if (area_index >= RKSS_MAX_AREA_NUM) {
		printf("TEEC: Not support area_index 0x%x\n", area_index);
		return -1;
	}

	printf("TEEC: delete area index 0x%x!\n", area_index);
	size = RKSS_SECTION_COUNT * RKSS_BACKUP_NUM * RKSS_DATA_LEN;
	delete_buff = (uint8_t *)memalign(CONFIG_SYS_CACHELINE_SIZE, size);
	if (!delete_buff) {
		printf("TEEC: Malloc failed!\n");
		return -1;
	}
	memset(delete_buff, 0, size);
	ret = blk_dwrite(dev_desc,
		part_info.start + area_index * RKSS_SECTION_COUNT * RKSS_BACKUP_NUM,
		RKSS_SECTION_COUNT * RKSS_BACKUP_NUM, delete_buff);
	if (ret != RKSS_SECTION_COUNT * RKSS_BACKUP_NUM) {
		free(delete_buff);
		printf("TEEC: blk_dwrite fail\n");
		return -1;
	}

	if (delete_buff)
		free(delete_buff);
	printf("TEEC: delete area success!\n");
	return 0;
}

static int rkss_storage_reset(void)
{
	if (rkss_storage_delete(0) < 0)
		return -1;
	if (rkss_storage_delete(1) < 0)
		return -1;
	return 0;
}
#endif

#ifdef DEBUG_RKSS
static void rkss_dump(void *data, unsigned int len)
{
	char *p = (char *)data;
	unsigned int i = 0;

	printf("-------------- DUMP %d --------------\n", len);
	for (i = 0; i < len; i++) {
		if (i % 32 == 0)
			printf("\n");
		printf("%02x ", *(p + i));
	}
	printf("\n------------- DUMP END -------------\n");
}

static void rkss_dump_ptable(void)
{
	int i, j, n;
	struct rkss_file_table *ptable;

	printf("-------------- DUMP ptable --------------\n");

	for (i = 0; i < RKSS_MAX_AREA_NUM; i++) {
		ptable = rkss_info[i].table;
		if (rkss_info[i].table == NULL)
			continue;
		printf("--------------- area[%d] tables ------------\n", i);
		for (j = 0; j < RKSS_TABLE_COUNT; j++) {
			for (n = 0; n < RKSS_EACH_FILEFOLDER_COUNT; n++) {
				printf("[%02d][%c] %s , inx:%d, size:%d\n",
						j * RKSS_EACH_FILEFOLDER_COUNT + n,
						ptable->used == 0 ? 'F':'T', ptable->name,
						ptable->index, ptable->size);

				ptable++;
			}
		}
	}
	printf("-------------- DUMP END --------------\n");
}

static void rkss_dump_usedflags(void)
{
	int i;

	for (i = 0; i < RKSS_MAX_AREA_NUM; i++) {
		if (rkss_info[i].flags == NULL)
			continue;
		printf("--------------- area[%d] flags ------------\n", i);
		rkss_dump(rkss_info[i].flags, RKSS_USEDFLAGS_COUNT * RKSS_DATA_LEN);
	}
}
#endif

static int rkss_read_multi_sections(unsigned int area_index,
		unsigned char *data, unsigned long index, unsigned int num)
{
	if (area_index >= RKSS_MAX_AREA_NUM) {
		printf("TEEC: %s area_index invalid\n", __func__);
		return -1;
	}
	if (index >= RKSS_SECTION_COUNT || num > RKSS_SECTION_COUNT ||
		(index + num) > RKSS_SECTION_COUNT) {
		printf("TEEC: %s index num invalid\n", __func__);
		return -1;
	}
	if (rkss_buffer[area_index] == NULL) {
		printf("TEEC: %s rkss_buffer is null\n", __func__);
		return -1;
	}
	memcpy(data, rkss_buffer[area_index] + index * RKSS_DATA_LEN, num * RKSS_DATA_LEN);
	return 0;
}

static int rkss_write_multi_sections(unsigned int area_index,
		unsigned char *data, unsigned long index, unsigned int num)
{
	if (num == 0)
		return 0;

	if (area_index >= RKSS_MAX_AREA_NUM) {
		printf("TEEC: %s area_index invalid\n", __func__);
		return -1;
	}

	if (index >= RKSS_SECTION_COUNT || num > RKSS_SECTION_COUNT ||
		(index + num) > RKSS_SECTION_COUNT) {
		printf("TEEC: %s index num invalid\n", __func__);
		return -1;
	}

	if (rkss_buffer[area_index] == NULL) {
		printf("TEEC: %s rkss_buffer is null\n", __func__);
		return -1;
	}

	memcpy(rkss_buffer[area_index] + index * RKSS_DATA_LEN, data, num * RKSS_DATA_LEN);
	rkss_info[area_index].header->backup_dirty = 1;
	return 0;
}

static int rkss_get_fileinfo_by_index(int fd,
		struct rkss_file_table *ptable, unsigned int *out_area_index)
{
	struct rkss_file_table *p;
	unsigned int area_index;

	area_index = fd / (RKSS_TABLE_COUNT * RKSS_EACH_FILEFOLDER_COUNT);
	if (area_index >= RKSS_MAX_AREA_NUM) {
		printf("TEEC: %s area_index invalid\n", __func__);
		return -1;
	}

	p = rkss_info[area_index].table;
	if (p == NULL) {
		printf("TEEC: %s table is null\n", __func__);
		return -1;
	}

	p += fd % (RKSS_TABLE_COUNT * RKSS_EACH_FILEFOLDER_COUNT);
	if (p->used != 1) {
		debug("TEEC: %s unused table!\n", __func__);
		return -1;
	}
	debug("TEEC: %s p->used = %d p->name=%s p->index=%d p->size=%d\n",
		__func__, p->used, p->name, p->index, p->size);
	memcpy(ptable, p, sizeof(struct rkss_file_table));
	*out_area_index = area_index;
	return 0;
}

static int rkss_get_fileinfo_by_name(char *filename,
		struct rkss_file_table *ptable, unsigned int *out_area_index)
{
	int ret;
	unsigned int i, j, n, len;
	struct rkss_file_table *p;

	len = strlen(filename);
	if (len > RKSS_NAME_MAX_LENGTH - 1) {
		printf("TEEC: filename is too long. length:%u\n", len);
		return -1;
	}

	for (i = 0; i < RKSS_MAX_AREA_NUM; i++) {
		if (rkss_info[i].table == NULL)
			continue;
		for (j = 0; j < RKSS_TABLE_COUNT; j++) {
			for (n = 0; n < RKSS_EACH_FILEFOLDER_COUNT; n++) {
				p = rkss_info[i].table + j * RKSS_EACH_FILEFOLDER_COUNT + n;

				if (p->used == 0)
					continue;

				if (!strcmp(p->name, filename)) {
					debug("TEEC: %s: area%d hit table[%d/%d], index[%d/%d]\n",
						__func__, i, j, RKSS_TABLE_COUNT, n, RKSS_EACH_FILEFOLDER_COUNT);
					memcpy(ptable, p, sizeof(struct rkss_file_table));
					*out_area_index = i;
					ret = i * RKSS_TABLE_COUNT * RKSS_EACH_FILEFOLDER_COUNT +
						j * RKSS_EACH_FILEFOLDER_COUNT + n;
					return ret;
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
				return -100;
UNMATCHFOLDER:
				debug("TEEC: Unmatched ...");
			}
		}
	}
	debug("TEEC: %s: file or dir no found!\n", __func__);
	return -1;
}

static int rkss_get_dirs_by_name(char *filename)
{
	int ret;
	unsigned int i, j, n, len;
	struct rkss_file_table *p;

	len = strlen(filename);
	if (len > RKSS_NAME_MAX_LENGTH - 1) {
		printf("TEEC: filename is too long. length:%u\n", len);
		return -1;
	}

	dir_num = 0;
	for (i = 0; i < RKSS_MAX_AREA_NUM; i++) {
		if (rkss_info[i].table == NULL)
			continue;
		for (j = 0; j < RKSS_TABLE_COUNT; j++) {
			for (n = 0; n < RKSS_EACH_FILEFOLDER_COUNT; n++) {
				p = rkss_info[i].table + j * RKSS_EACH_FILEFOLDER_COUNT + n;

				if (p->used == 0)
					continue;

				// Full Matching
				ret = memcmp(p->name, filename, strlen(filename));
				debug("TEEC: comparing [fd:%d] : %s ?= %s, ret: %d\n",
					(i * RKSS_TABLE_COUNT + j) * RKSS_EACH_FILEFOLDER_COUNT + n,
					p->name, filename, ret);
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
	}
	return dir_num;
}

static int rkss_get_empty_section_from_usedflags(
		unsigned int area_index, int section_size)
{
	int i = 0;
	int count0 = 0;

	if (area_index >= RKSS_MAX_AREA_NUM) {
		printf("TEEC: %s area_index invalid\n", __func__);
		return -1;
	}
	if (rkss_info[area_index].flags == NULL) {
		printf("TEEC: %s flags is null\n", __func__);
		return -1;
	}
	for (i = 0; i < RKSS_SECTION_COUNT; i++) {
		uint8_t *flag = rkss_info[area_index].flags + (int)i/2;
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

static int rkss_incref_multi_usedflags_sections(
	unsigned int area_index, unsigned int index, unsigned int num)
{
	int value, i;
	uint8_t *flag;

	if (area_index >= RKSS_MAX_AREA_NUM) {
		printf("TEEC: %s area_index invalid\n", __func__);
		return -1;
	}

	if (index >= RKSS_SECTION_COUNT || num > RKSS_SECTION_COUNT ||
		(index + num) > RKSS_SECTION_COUNT) {
		printf("TEEC: index[%d] out of range.\n", index);
		return -1;
	}
	if (rkss_info[area_index].flags == NULL) {
		printf("TEEC: %s flags is null\n", __func__);
		return -1;
	}

	for (i = 0; i < num; i++, index++) {
		flag = rkss_info[area_index].flags + (int)index / 2;
		value = index & 0x1 ? *flag & 0x0F : (*flag & 0xF0) >> 4;
		if (++value > 0xF) {
			printf("TEEC: reference out of data: %d\n", value);
			value = 0xF;
		}
		*flag = index & 0x1 ? (*flag & 0xF0) | (value & 0x0F) :
				(*flag & 0x0F) | (value << 4);
	}
	rkss_info[area_index].header->backup_dirty = 1;
	return 0;
}

static int rkss_decref_multi_usedflags_sections(
	unsigned int area_index, unsigned int index, unsigned int num)
{
	int value, i;
	uint8_t *flag;

	if (area_index >= RKSS_MAX_AREA_NUM) {
		printf("TEEC: %s area_index invalid\n", __func__);
		return -1;
	}

	if (index >= RKSS_SECTION_COUNT || num > RKSS_SECTION_COUNT ||
		(index + num) > RKSS_SECTION_COUNT) {
		printf("TEEC: index[%d] out of range.\n", index);
		return -1;
	}
	if (rkss_info[area_index].flags == NULL) {
		printf("TEEC: %s flags is null\n", __func__);
		return -1;
	}

	for (i = 0; i < num; i++, index++) {
		flag = rkss_info[area_index].flags + (int)index / 2;
		value = index & 0x1 ? *flag & 0x0F : (*flag & 0xF0) >> 4;
		if (--value < 0) {
			printf("TEEC: reference out of data: %d\n", value);
			value = 0x0;
		}
		*flag = index & 0x1 ? (*flag & 0xF0) | (value & 0x0F) :
				(*flag & 0x0F) | (value << 4);
	}
	rkss_info[area_index].header->backup_dirty = 1;
	return 0;
}

static int rkss_get_remain_tables(struct rkss_file_table *p)
{
	unsigned int i, n;
	int count = 0;

	if (p == NULL)
		return -1;

	for (i = 0; i < RKSS_TABLE_COUNT; i++) {
		for (n = 0; n < RKSS_EACH_FILEFOLDER_COUNT; n++) {
			if (p->used == 0)
				count++;
			p++;
		}
	}
	return count;
}

static int rkss_get_remain_flags(uint8_t *flags)
{
	unsigned int i, value;
	uint8_t *flag;
	int count = 0;

	if (flags == NULL)
		return -1;

	for (i = 0; i < RKSS_SECTION_COUNT; i++) {
		flag = flags + (int)i / 2;
		value = i & 0x1 ? *flag & 0x0F : (*flag & 0xF0) >> 4;
		if (value == 0)
			count++;
	}
	return count;
}

static int rkss_get_larger_area(void)
{
	int i, tables, flags, max_flags = 0;
	int area_index = -1;

	for (i = 0; i < RKSS_MAX_AREA_NUM; i++) {
		if (rkss_info[i].table == NULL ||
		rkss_info[i].flags == NULL)
			continue;
		tables = rkss_get_remain_tables(rkss_info[i].table);
		flags = rkss_get_remain_flags(rkss_info[i].flags);
		if (tables > 0 && flags > 0 && flags > max_flags) {
			max_flags = flags;
			area_index = i;
		}
	}
	return area_index;
}

static int rkss_write_area_empty_ptable(
	unsigned int area_index, struct rkss_file_table *pfile_table)
{
	int i, n, ret;
	struct rkss_file_table *p;

	if (rkss_info[area_index].table == NULL) {
		printf("TEEC: %s table is null\n", __func__);
		return -1;
	}
	for (i = 0; i < RKSS_TABLE_COUNT; i++) {
		for (n = 0; n < RKSS_EACH_FILEFOLDER_COUNT; n++) {
			p = rkss_info[area_index].table + i * RKSS_EACH_FILEFOLDER_COUNT + n;
			if (p->used == 0) {
				memcpy(p, pfile_table, sizeof(struct rkss_file_table));
				p->used = 1;
				debug("TEEC: write emt ptable : [%d,%d] name:%s, index:%d, size:%d, used:%d\n",
						i, n, p->name, p->index, p->size, p->used);
				rkss_info[area_index].header->backup_dirty = 1;
				ret = area_index * RKSS_TABLE_COUNT * RKSS_EACH_FILEFOLDER_COUNT +
					i * RKSS_EACH_FILEFOLDER_COUNT + n;
				return ret;
			}
		}
	}
	printf("TEEC: No enough ptable space available in secure storage.\n");
	return -1;
}

static int rkss_write_empty_ptable(struct rkss_file_table *pfile_table)
{
	int area_index;

	area_index = rkss_get_larger_area();
	if (area_index < 0) {
		printf("TEEC: get area index fail\n");
		return -1;
	}

	return rkss_write_area_empty_ptable(area_index, pfile_table);
}

static int rkss_write_back_ptable(
	int fd, struct rkss_file_table *pfile_table)
{
	struct rkss_file_table *p;
	unsigned int area_index;

	area_index = fd / (RKSS_TABLE_COUNT * RKSS_EACH_FILEFOLDER_COUNT);
	if (area_index >= RKSS_MAX_AREA_NUM) {
		printf("TEEC: %s area_index invalid\n", __func__);
		return -1;
	}

	p = rkss_info[area_index].table;
	if (p == NULL) {
		printf("TEEC: %s table is null\n", __func__);
		return -1;
	}

	p += fd % (RKSS_TABLE_COUNT * RKSS_EACH_FILEFOLDER_COUNT);

	memcpy(p, pfile_table, sizeof(struct rkss_file_table));
	debug("TEEC: write ptable : name:%s, index:%d, size:%d, used:%d\n",
		p->name, p->index, p->size, p->used);

	rkss_info[area_index].header->backup_dirty = 1;
	return 0;
}

static int rkss_storage_write(void)
{
	int ret, i;

	for (i = 0; i < RKSS_MAX_AREA_NUM; i++) {
		if (rkss_info[i].header != NULL && rkss_info[i].header->backup_dirty == 1) {
			rkss_info[i].header->backup_count++;
			rkss_info[i].footer->backup_count = rkss_info[i].header->backup_count;
			rkss_info[i].header->backup_index++;
			if (rkss_info[i].header->backup_index >= RKSS_BACKUP_NUM)
				rkss_info[i].header->backup_index = 0;
			rkss_info[i].header->backup_dirty = 0;

			if (rkss_info[i].header->backup_count == 0xffffffff) {
				rkss_info[i].header->backup_count = 1;
				rkss_info[i].footer->backup_count = 1;
				ret = blk_dwrite(dev_desc,
					part_info.start + i * RKSS_SECTION_COUNT * RKSS_BACKUP_NUM +
					rkss_info[i].header->backup_index * RKSS_SECTION_COUNT,
					RKSS_SECTION_COUNT, rkss_buffer[i]);
				if (ret != RKSS_SECTION_COUNT) {
					printf("TEEC: blk_dwrite fail\n");
					return -1;
				}

				rkss_info[i].header->backup_count = 2;
				rkss_info[i].footer->backup_count = 2;
				rkss_info[i].header->backup_index++;
				if (rkss_info[i].header->backup_index >= RKSS_BACKUP_NUM)
					rkss_info[i].header->backup_index = 0;
				ret = blk_dwrite(dev_desc,
					part_info.start + i * RKSS_SECTION_COUNT * RKSS_BACKUP_NUM +
					rkss_info[i].header->backup_index * RKSS_SECTION_COUNT,
					RKSS_SECTION_COUNT, rkss_buffer[i]);
				if (ret != RKSS_SECTION_COUNT) {
					printf("TEEC: blk_dwrite fail\n");
					return -1;
				}
			} else {
				ret = blk_dwrite(dev_desc,
					part_info.start + i * RKSS_SECTION_COUNT * RKSS_BACKUP_NUM +
					rkss_info[i].header->backup_index * RKSS_SECTION_COUNT,
					RKSS_SECTION_COUNT, rkss_buffer[i]);
				if (ret != RKSS_SECTION_COUNT) {
					printf("TEEC: blk_dwrite fail\n");
					return -1;
				}
			}
		}
	}
	return 0;
}

static int rkss_storage_init(uint32_t area_index)
{
	unsigned long ret = 0;
	uint32_t size, i;
	uint32_t max_ver = 0;
	uint32_t max_index = 0;
	uint32_t flags_offset, table_offset, data_offset, footer_offset;

	if (area_index >= RKSS_MAX_AREA_NUM) {
		printf("TEEC: Not support index=0x%x\n", area_index);
		return -1;
	}

	size = RKSS_SECTION_COUNT * RKSS_DATA_LEN;
	flags_offset = RKSS_USEDFLAGS_INDEX * RKSS_DATA_LEN;
	table_offset = RKSS_TABLE_INDEX * RKSS_DATA_LEN;
	data_offset = RKSS_DATA_INDEX * RKSS_DATA_LEN;
	footer_offset = RKSS_FOOTER_INDEX * RKSS_DATA_LEN;

	if (rkss_buffer[area_index] == NULL) {
		/* Always use, no need to release */
		rkss_buffer[area_index] = (uint8_t *)memalign(CONFIG_SYS_CACHELINE_SIZE, size);
		if (!(rkss_buffer[area_index])) {
			printf("TEEC: Malloc failed!\n");
			return -1;
		}

		/* Pointer initialization */
		rkss_info[area_index].header = (struct rkss_file_header *)(rkss_buffer[area_index]);
		rkss_info[area_index].flags = (uint8_t *)(rkss_buffer[area_index] + flags_offset);
		rkss_info[area_index].table = (struct rkss_file_table *)(rkss_buffer[area_index] + table_offset);
		rkss_info[area_index].data = (uint8_t *)(rkss_buffer[area_index] + data_offset);
		rkss_info[area_index].footer = (struct rkss_file_footer *)(rkss_buffer[area_index] + footer_offset);

		/* Find valid from (backup0 - backup1) */
		for (i = 0; i < RKSS_BACKUP_NUM; i++) {
			ret = blk_dread(dev_desc,
				part_info.start +
				area_index * RKSS_SECTION_COUNT * RKSS_BACKUP_NUM +
				i * RKSS_SECTION_COUNT,
				RKSS_SECTION_COUNT, rkss_buffer[area_index]);
			if (ret != RKSS_SECTION_COUNT) {
				printf("TEEC: blk_dread fail\n");
				return -1;
			}

			if ((rkss_info[area_index].header->tag == RKSS_TAG) &&
			    (rkss_info[area_index].footer->backup_count == rkss_info[area_index].header->backup_count)) {
				if (max_ver < rkss_info[area_index].header->backup_count) {
					max_index = i;
					max_ver = rkss_info[area_index].header->backup_count;
				}
			}
		}

		if (max_ver) {
			debug("TEEC: max_ver=%d, max_index=%d.\n",
				max_ver, max_index);

			if (max_index != (RKSS_BACKUP_NUM - 1)) {
				ret = blk_dread(dev_desc,
					part_info.start +
					area_index * RKSS_SECTION_COUNT * RKSS_BACKUP_NUM +
					max_index * RKSS_SECTION_COUNT,
					RKSS_SECTION_COUNT, rkss_buffer[area_index]);
				if (ret != RKSS_SECTION_COUNT) {
					printf("TEEC: blk_dread fail\n");
					return -1;
				}
			}

			if (rkss_info[area_index].header->version == RKSS_VERSION_V2) {
				debug("TEEC: data version equal to image version, do nothing!\n");
			} else if (rkss_info[area_index].header->version < RKSS_VERSION_V2) {
				printf("TEEC: data version lower than image version!\n");
				/* convert rkss version 2 to higher rkss version */
				free(rkss_buffer[area_index]);
				rkss_buffer[area_index] = NULL;
				return -1;
			} else {
				printf("TEEC: data version higher than image version!\n");
				printf("TEEC: please update image!\n");
				free(rkss_buffer[area_index]);
				rkss_buffer[area_index] = NULL;
				return -1;
			}
		} else {
			printf("TEEC: Reset area[%d] info...\n", area_index);
			memset(rkss_buffer[area_index], 0, size);
			rkss_info[area_index].header->tag = RKSS_TAG;
			rkss_info[area_index].header->version = RKSS_VERSION_V2;
			rkss_info[area_index].header->backup_count = 1;
			rkss_info[area_index].footer->backup_count = 1;
			/* Verify Usedflags Section */
			if (rkss_verify_usedflags(area_index) < 0) {
				printf("TEEC: rkss_verify_usedflags fail !\n");
				return -1;
			}
		}
	}
	return 0;
}

static int tee_fs_open(struct tee_fs_rpc *fsrpc)
{
	int make_newfile = 0;
	char *filename = (char *)(fsrpc + 1);
	struct rkss_file_table p = {0};
	int ret;
	unsigned int area_index;

	if (strlen(filename) > RKSS_NAME_MAX_LENGTH) {
		debug("TEEC: %s: file name too long. %s\n", __func__, filename);
		return -1;
	}

	debug("TEEC: %s open file: %s, len: %zu\n",
		__func__, filename, strlen(filename));

	ret = rkss_get_fileinfo_by_name(filename, &p, &area_index);
	if (ret < 0) {
		debug("TEEC: %s : no such file. %s\n", __func__, filename);
		make_newfile = 1;
	} else {
		fsrpc->fd = ret;
		file_seek = 0;
		if (CHECKFLAG(fsrpc->flags, TEE_FS_O_APPEND))
			file_seek = p.size;
	}

	if (make_newfile) {
		if (CHECKFLAG(fsrpc->flags, TEE_FS_O_CREAT)) {
			debug("TEEC: %s create new file: %s\n",
				__func__, filename);
			strcpy(p.name, filename);
			p.index = 0;
			p.size = 0;
			p.used = 1;
			p.flags = RK_FS_R | RK_FS_W;
			ret = rkss_write_empty_ptable(&p);
			if (ret < 0) {
				printf("TEEC: %s : error. %s\n",
					__func__, filename);
				return -1;
			}
			fsrpc->fd = ret;
			file_seek = 0;
		} else {
			debug("TEEC: and no create flag found.\n");
			return -1;
		}
	}

	debug("TEEC: %s ! %s , fd:%d, flag: %x, len: %d\n",
		__func__, filename, fsrpc->fd, fsrpc->flags, fsrpc->len);

	return fsrpc->fd;
}

static int tee_fs_close(struct tee_fs_rpc *fsrpc)
{
	debug("TEEC: %s !\n", __func__);

	UNREFERENCED_PARAMETER(fsrpc);
	return 0;
}

static int tee_fs_read(struct tee_fs_rpc *fsrpc)
{
	void *data = (void *)(fsrpc + 1);
	struct rkss_file_table p = {0};
	int ret, num, di;
	uint8_t *temp_file_data;
	unsigned int area_index;

	debug("TEEC: %s! fd:%d, len:%d\n", __func__, fsrpc->fd, fsrpc->len);

	ret = rkss_get_fileinfo_by_index(fsrpc->fd, &p, &area_index);
	if (ret < 0) {
		printf("TEEC: unavailable fd !\n");
		return -1;
	}

	if (file_seek != 0)
		printf("TEEC: warning !!! file_seek != 0. unsupported now.\n");

	num = fsrpc->len / RKSS_DATA_LEN + 1;
	di = 0;
	debug("TEEC: reading section[%d], fd:%d, len:%d, filesize:%d\n",
			p.index, fsrpc->fd, fsrpc->len, p.size);

	temp_file_data = malloc(num * RKSS_DATA_LEN);
	ret = rkss_read_multi_sections(area_index, temp_file_data, p.index, num);
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
	void *data = (void *)(fsrpc + 1);
	struct rkss_file_table p = {0};
	int ret, num;
	uint8_t *temp_file_data;
	unsigned int area_index;

	debug("TEEC: %s ! fd:%d, lenth:%d\n", __func__, fsrpc->fd, fsrpc->len);

	if (fsrpc->fd < 0) {
		printf("TEEC: %s error ! wrong fd : %d\n", __func__, fsrpc->fd);
		return -1;
	}

	if (file_seek != 0)
		printf("TEEC: warning !!! file_seek != 0. unsupported now.\n");

	ret = rkss_get_fileinfo_by_index(fsrpc->fd, &p, &area_index);
	if (ret < 0) {
		printf("TEEC: %s: fd unvailable!\n", __func__);
		return -1;
	}

	if (p.size != 0) {
		num = p.size / RKSS_DATA_LEN + 1;
		ret = rkss_decref_multi_usedflags_sections(area_index, p.index, num);
		if (ret < 0) {
			printf("TEEC: rkss decref usedflags error !\n");
			return -1;
		}
	}

	p.size = fsrpc->len;
	num = fsrpc->len / RKSS_DATA_LEN + 1;
	p.index = rkss_get_empty_section_from_usedflags(area_index, num);
	debug("TEEC: Get Empty section in %d\n", p.index);
	p.used = 1;

	ret = rkss_incref_multi_usedflags_sections(area_index, p.index, num);
	if (ret < 0) {
		printf("TEEC: rkss_incref_multi_usedflags_sections error !\n");
		ret = -1;
	}

	ret = rkss_write_back_ptable(fsrpc->fd, &p);
	if (ret < 0) {
		printf("TEEC: %s: write ptable error!\n", __func__);
		return -1;
	}

	temp_file_data = malloc(num * RKSS_DATA_LEN);
	if (temp_file_data == NULL) {
		printf("TEEC: Malloc failed!\n");
		return -1;
	}
	memset(temp_file_data, 0, num * RKSS_DATA_LEN);
	memcpy(temp_file_data, data, p.size);
	rkss_write_multi_sections(area_index, temp_file_data, p.index, num);
	free(temp_file_data);
	temp_file_data = 0;

	return fsrpc->len;
}

static int tee_fs_seek(struct tee_fs_rpc *fsrpc)
{
	struct rkss_file_table p = {0};
	int ret;
	unsigned int area_index;

	debug("TEEC: %s ! fd:%d, seek:%d, flag:%x\n",
		__func__, fsrpc->fd, fsrpc->arg, fsrpc->flags);

	if (fsrpc->flags == TEE_FS_SEEK_CUR) {
		fsrpc->res = file_seek + fsrpc->arg;
	} else if (fsrpc->flags == TEE_FS_SEEK_SET) {
		file_seek = fsrpc->arg;
		fsrpc->res = file_seek;
	} else if (fsrpc->flags == TEE_FS_SEEK_END) {
		ret = rkss_get_fileinfo_by_index(fsrpc->fd, &p, &area_index);
		if (ret < 0) {
			printf("TEEC: unavilable fd.\n");
			return -1;
		}
		file_seek = p.size + fsrpc->arg;
		fsrpc->res = file_seek;
	} else {
		printf("TEEC: %s: unsupport seed mode.\n", __func__);
		return -1;
	}

	return fsrpc->res;
}

static int tee_fs_unlink(struct tee_fs_rpc *fsrpc)
{
	char *filename = (char *)(fsrpc + 1);
	struct rkss_file_table p = {0};
	int ret, fd, num;
	unsigned int area_index;

	fd = rkss_get_fileinfo_by_name(filename, &p, &area_index);
	if (fd < 0) {
		printf("TEEC: %s : no such file. %s\n", __func__, filename);
		return 0;
	}

	debug("TEEC: %s ! %s fd:%d index:%d size:%d\n",
		__func__, filename, fd, p.index, p.size);

	/* decrease ref from usedflags */
	num = p.size / RKSS_DATA_LEN + 1;
	ret = rkss_decref_multi_usedflags_sections(area_index, p.index, num);
	if (ret < 0) {
		printf("TEEC: rkss_decref_multi_usedflags_sections error !\n");
		return -1;
	}

	/* rm from ptable */
	memset(&p, 0, sizeof(struct rkss_file_table));
	ret = rkss_write_back_ptable(fd, &p);
	if (ret < 0) {
		printf("TEEC: %s : write back error %d\n", __func__, ret);
		return -1;
	}

	return 0;
}

static int tee_fs_link(struct tee_fs_rpc *fsrpc)
{
	char *filename = (char *)(fsrpc + 1);
	size_t offset_new_fn = strlen(filename) + 1;
	char *newfilename = filename + offset_new_fn;
	struct rkss_file_table p_old = {0};
	struct rkss_file_table p_check = {0};
	struct rkss_file_table p_new = {0};
	int ret, num;
	unsigned int old_area, new_area;

	debug("TEEC: %s ! %s -> %s\n", __func__, filename, newfilename);

	ret = rkss_get_fileinfo_by_name(filename, &p_old, &old_area);
	if (ret < 0) {
		printf("TEEC: cannot find src file %s.\n", filename);
		return -1;
	}

	ret = rkss_get_fileinfo_by_name(newfilename, &p_check, &new_area);
	if (ret >= 0) {
		printf("TEEC: file exist ! %s.\n", newfilename);
		return -1;
	}

	memcpy(&p_new, &p_old, sizeof(struct rkss_file_table));
	strcpy(p_new.name, newfilename);
	ret = rkss_write_area_empty_ptable(old_area, &p_new);
	if (ret < 0) {
		printf("TEEC: tee_fs_open : error. %s\n", filename);
		return -1;
	}

	num = p_new.size / RKSS_DATA_LEN + 1;
	ret = rkss_incref_multi_usedflags_sections(old_area, p_new.index, num);
	if (ret < 0) {
		printf("TEEC: rkss_incref_multi_usedflags_sections error !\n");
		return -1;
	}

	return 0;
}

static int tee_fs_rename(struct tee_fs_rpc *fsrpc)
{
	char *filenames = (char *)(fsrpc + 1);
	char *newnames = filenames + strlen(filenames) + 1;
	struct rkss_file_table p = {0};
	int ret;
	unsigned int area_index;

	debug("TEEC: rename: %s -> %s\n", filenames, newnames);

	ret = rkss_get_fileinfo_by_name(filenames, &p, &area_index);
	if (ret < 0) {
		printf("TEEC: filename no found .\n");
		return -1;
	}

	strcpy(p.name, newnames);

	ret = rkss_write_back_ptable(ret, &p);
	if (ret < 0) {
		printf("TEEC: write ptable error!\n");
		return -1;
	}

	return 0;
}

static int tee_fs_truncate(struct tee_fs_rpc *fsrpc)
{
	int section_num, new_section_num, free_section_num;
	uint16_t free_index;
	struct rkss_file_table p = {0};
	int ret;
	unsigned int area_index;

	debug("TEEC: %s: fd:%d, lenth:%d\n",
		__func__, fsrpc->fd, fsrpc->arg);
	if (fsrpc->fd < 0) {
		printf("TEEC: %s: fd unavilable !\n", __func__);
		return -1;
	}

	ret = rkss_get_fileinfo_by_index(fsrpc->fd, &p, &area_index);
	if (ret < 0) {
		printf("TEEC: fd unvailable!\n");
		return -1;
	}

	if (p.size < fsrpc->arg) {
		printf("TEEC: truncate size not support!\n ");
		return -1;
	} else {
		section_num = p.size / RKSS_DATA_LEN + 1;
		new_section_num = fsrpc->arg / RKSS_DATA_LEN + 1;
		free_section_num = section_num - new_section_num;
		free_index = p.index + new_section_num;
		ret = rkss_decref_multi_usedflags_sections(area_index, free_index, free_section_num);
		if (ret < 0) {
			printf("TEEC: rkss decref usedflags error!\n");
			return -1;
		}
		p.size = fsrpc->arg;
		ret = rkss_write_back_ptable(fsrpc->fd, &p);
		if (ret < 0) {
			printf("TEEC: rkss_write_back_ptable error!\n");
			return -1;
		}
	}

	return 0;
}

static int tee_fs_mkdir(struct tee_fs_rpc *fsrpc)
{
	char *dirname = (char *)(fsrpc + 1);

	UNREFERENCED_PARAMETER(dirname);
	debug("TEEC: %s: %s\n", __func__, dirname);
	return 0;
}

static int tee_fs_opendir(struct tee_fs_rpc *fsrpc)
{
	char *dirname = (char *)(fsrpc + 1);
	int ret;

	dir_seek = 0;
	ret = rkss_get_dirs_by_name(dirname);
	if (ret < 0)
		printf("TEEC: %s: error\n", __func__);

	debug("TEEC: %s: %s, seek/num:%d/%d\n", __func__,
		dirname, dir_seek, dir_num);
	return 0;
}

static int tee_fs_closedir(struct tee_fs_rpc *fsrpc)
{
	char *dirname = (char *)(fsrpc + 1);

	UNREFERENCED_PARAMETER(dirname);
	debug("TEEC: %s: %s\n", __func__, dirname);
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
		debug("TEEC: %s: END\n", __func__);
		return -1;
	}

	strcpy(dirname, dir_cache[dir_seek]);
	fsrpc->len = strlen(dir_cache[dir_seek]) + 1;
	++dir_seek;

	debug("TEEC: %s: %s\n", __func__, dirname);
	return 0;
}

static int tee_fs_rmdir(struct tee_fs_rpc *fsrpc)
{
	char *dirname = (char *)(fsrpc + 1);
	struct rkss_file_table p = {0};
	int ret;
	unsigned int area_index;

	debug("TEEC: %s: %s\n", __func__, dirname);

	ret = rkss_get_fileinfo_by_name(dirname, &p, &area_index);
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
	struct rkss_file_table p = {0};
	int ret;
	unsigned int area_index;

	debug("TEEC: %s: name:%s,flag:%x\n",
		__func__, filename, fsrpc->flags);

	ret = rkss_get_fileinfo_by_name(filename, &p, &area_index);
	if (ret < 0 && ret != -100) {
		debug("TEEC: %s: %s no such file or directory.\n",
			__func__, filename);
		return -1;
	}

	if (CHECKFLAG(fsrpc->flags, TEE_FS_R_OK)) {
		if (!CHECKFLAG(p.flags, RK_FS_R)) {
			printf("TEEC: %s: no permission FS_R_OK in %x.\n",
				__func__, p.flags);
			return -1;
		}
	}

	if (CHECKFLAG(fsrpc->flags, TEE_FS_W_OK)) {
		if (!CHECKFLAG(p.flags, RK_FS_W)) {
			printf("TEEC: %s: no permission FS_W_OK in %x.\n",
				__func__, p.flags);
			return -1;
		}
	}
	return 0;
}

int tee_supp_rk_fs_init_v2(void)
{
	assert(sizeof(struct rkss_file_table) == RKSS_TABLE_SIZE);
	assert(RKSS_DATA_LEN / sizeof(struct rkss_file_table) ==
		RKSS_EACH_FILEFOLDER_COUNT);

	if (check_security_exist(0) < 0)
		return 0;

	/* clean secure storage */
#ifdef DEBUG_CLEAN_RKSS
	if (rkss_storage_reset() < 0)
		return -1;
#endif

	for (uint32_t i = 0; i < RKSS_ACTIVE_AREA_NUM; i++) {
		if (rkss_storage_init(i) < 0)
			return -1;
	}

#ifdef DEBUG_RKSS
	rkss_dump_ptable();
	rkss_dump_usedflags();
#endif

	return 0;
}

static int rkss_step;
int tee_supp_rk_fs_process_v2(void *cmd, size_t cmd_size)
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
		rkss_storage_write();
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
		rkss_storage_write();
		break;
	case TEE_FS_RENAME:
		debug(">>>>>>> [%d] TEE_FS_RENAME !\n", rkss_step++);
		ret = tee_fs_rename(fsrpc);
		rkss_storage_write();
		break;
	case TEE_FS_TRUNC:
		debug(">>>>>>> [%d] TEE_FS_TRUNC !\n", rkss_step++);
		ret = tee_fs_truncate(fsrpc);
		break;
	case TEE_FS_MKDIR:
		debug(">>>>>>> [%d] TEE_FS_MKDIR !\n", rkss_step++);
		ret = tee_fs_mkdir(fsrpc);
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
		rkss_storage_write();
		break;
	default:
		printf(">>>>> DEFAULT !! %d\n", fsrpc->op);
		break;
	}

	fsrpc->res = ret;
	debug(">>>>>>> fsrpc->res = [%d]	!\n", fsrpc->res);

	return ret;
}
