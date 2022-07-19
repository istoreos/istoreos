#include <common.h>

#include "layout.h"
#include "rtk_storage_layout.h"

#define LOCAL_TRACE CRITICAL /* level: CRITICAL, ALWAYS, INFO, SPEW*/

#define TRACEF(str, x...) \
do { \
	printf("%s:%d: " str, __func__, __LINE__, ## x); \
} while (0)

#define LTRACEF debug

int check_part_table_type(void)
{
	struct mbr_table mbr;
	int ret;
	int type;

	ret = storage_read(0, 512, &mbr);
	if (ret == 0) {
		TRACEF("storage_read Error ret %d\n", ret);
		return -1;
	}

	type = mbr.part[0].id;
	if(type != GPT_SIGN)
		return PART_TBL_MBR;
	else
		return PART_TBL_GPT;
}

int build_part_table(int type, struct fw_info *fw_infos, struct part_info *p_infos)
{
	if(type == PART_TBL_MBR)
		return build_part_table_to_mbr(p_infos);
	else if(type == PART_TBL_GPT)
		return build_part_table_to_gpt(fw_infos, p_infos);
	else
		return -1;
}

int read_part_info(int type, struct part_info *p_infos)
{
	if(type == PART_TBL_MBR)
		return read_part_info_from_mbr(p_infos);
	else if(type == PART_TBL_GPT)
		return read_part_info_from_gpt(p_infos);
	else
		return -1;
}

void destroy_partition_img(struct part_info *part)
{
	uint64_t start;
	unsigned char data[512];
	int i;

	TRACEF("enter %s\n", __func__);

	memset(data, 0, 512);
	start = part->start_addr;

	for(i=0; i<1000; i++)
		storage_write(start + i*512, 512, data);
}

int write_partition_img(struct part_info *part, uint64_t file_size,
		uint64_t offset, void *data, size_t sz)
{
	uint64_t start;
	int ret = 0;

	if (part->id != PART_EXTEND && file_size > part->length) {
		TRACEF("[ERROR] write %s file_size 0x%llx > "
				"part length 0x%lx\n",
				part->name, file_size, part->length);
		return -1;
	}

	LTRACEF("Write part %s (start_addr 0x%llx bytes_size 0x%lx) "
			"file size 0x%llx offest 0x%llx data@%p sz=0x%lx\n",
			part->name, part->start_addr, part->bytes_size,
			file_size, offset, data, sz);

	start = part->start_addr + offset;

	ret = storage_write(start, sz, data);

	LTRACEF("[DEBUG] Write part from 0x%x to 0x%x\n",
			(uint32_t)start, (uint32_t)(start + sz) );
	if (ret < 0) {
		TRACEF("[ERROR] write RAW data ERROR %d\n", ret);
	}

	return ret;
}
