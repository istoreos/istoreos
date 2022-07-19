#include <common.h>
#include <malloc.h>
#include <errno.h>

#include "layout.h"

#define TRACEF(str, x...) \
do { \
	printf("%s:%d: " str, __func__, __LINE__, ## x); \
} while (0)

#define LTRACEF debug

#define CACHE_LINE CONFIG_SYS_CACHELINE_SIZE
#define ROUNDUP(x, y)   (((x) + ((y) - 1)) & ~((y) - 1))

#define flash_blk_size EMMC_BLOCK_SIZE

/*To dump MBR or EBR info */
static void debug_dump_mbr_info(struct mbr_table *mbr)
{
	int i;
	LTRACEF("MBR@%p sign = %x\n", mbr, mbr->signature);

	for (i = 0; i < 4; i++) {
		LTRACEF("MBR partition %d:\n", i + 1);
		LTRACEF("active: 0x%x\n", mbr->part[i].active);
		LTRACEF("head_start: 0x%x sector_start 0x%x cylinder_start 0x%x\n",
				mbr->part[i].head_start,
				mbr->part[i].sector_start,
				mbr->part[i].cylinder_start);
		LTRACEF("head_end: 0x%x sector_end 0x%x cylinder_end 0x%x\n",
				mbr->part[i].head_end,
				mbr->part[i].sector_end,
				mbr->part[i].cylinder_end);
		LTRACEF("id: 0x%x rel_sector_start 0x%x sector_num 0x%x\n",
				mbr->part[i].id, mbr->part[i].rel_sector_start,
				mbr->part[i].sector_num);
	}
}

static int read_mbr(uint64_t addr, struct mbr_table **mbr)
{
	int ret = 0;
	uint64_t mbr_addr = addr;
	size_t mbr_size = MBR_SIZE;

	if (*mbr == 0)
		*mbr = memalign(CACHE_LINE, ROUNDUP(512, CACHE_LINE));
	if (!*mbr) {
		TRACEF("ERROR %s: No memory!!\n", __func__);
		return -ENOMEM;
	}

	/* read partition MBR and EBR*/
	ret = storage_read(mbr_addr, mbr_size, *mbr);
	if (ret == 0) {
		TRACEF("storage_read Error ret %d\n", ret);
	}

	LTRACEF("[DEBUG] read 0x%llx mbr info:\n", mbr_addr);
	debug_dump_mbr_info(*mbr);

	return 0;
}

static int write_mbr(uint64_t addr, struct mbr_table *mbr)
{
	int ret = 0;
	uint64_t mbr_addr = addr;
	size_t mbr_size = MBR_SIZE;

	/* read partition MBR and EBR*/
	ret = storage_write(mbr_addr, mbr_size, mbr);
	if (ret == 0) {
		TRACEF("storage_write Error ret %d\n", ret);
	}

	LTRACEF("[DEBUG] write 0x%llx mbr info:\n", mbr_addr);
	debug_dump_mbr_info(mbr);

	return 0;
}

int build_part_table_to_mbr(struct part_info *p_infos) {
	struct part_info *pinfo;
	struct mbr_table *mbr;
	int i;

	mbr = memalign(CACHE_LINE, ROUNDUP(MBR_SIZE, CACHE_LINE));
	if (!mbr) {
		TRACEF("ERROR %s: No Memory!!\n", __func__);
		return -ENOMEM;
	}

	memset(mbr, 0, MBR_SIZE);
	mbr->signature = MBR_SIGN;
	pinfo = &p_infos[0];
	pinfo->mbr = mbr;
	LTRACEF("pinfo %s MBR@%p\n", pinfo->name, pinfo->mbr);

	for (i = 0; i < 4; i++) {
		pinfo = &p_infos[i + 1];
		LTRACEF("#%d, pinfo@%p name %s\n",
			    i + 1, pinfo, pinfo->name);
		pinfo->mbr_addr = 0x0;

		pinfo->mbr = mbr;
		pinfo->mbr_index = i;
		pinfo->is_extend = false;

		pinfo->start_block = pinfo->start_addr / flash_blk_size;
		mbr->part[i].rel_sector_start = pinfo->start_block;
		pinfo->block_size = pinfo->bytes_size / flash_blk_size;
		mbr->part[i].sector_num = pinfo->block_size;

		mbr->part[i].id = 0x83;
		mbr->part[i].head_start = 0x3;
		mbr->part[i].sector_start = 0xd0;
		mbr->part[i].cylinder_start = 0xff;
		mbr->part[i].head_end = 0x3;
		mbr->part[i].sector_end = 0xd0;
		mbr->part[i].cylinder_end = 0xff;
		if (pinfo->id == PART_EXTEND)
			mbr->part[i].id = 0x5;
	}
	write_mbr(pinfo->mbr_addr, pinfo->mbr);

	i++;
	/* for extend partition */
	if (pinfo->id == PART_EXTEND && pinfo->start_addr) {
		struct ebr_table *ebr = NULL;
		uint64_t first_ebr_addr;
		uint64_t start_ebr_addr;
		LTRACEF("Build extend part pinfo@%p name %s\n", pinfo, pinfo->name);
		first_ebr_addr = pinfo->start_addr;
		start_ebr_addr = first_ebr_addr;
		while (i < MAX_PART_INFO) {
			pinfo = &p_infos[i];
			if (!pinfo->bytes_size) {
				TRACEF("#%d, pinfo name %s skip due to bytes_size = 0 \n",
					    i, pinfo->name);
				goto next_part;
			}
			if (ebr) { /* prve ebr next */
				uint64_t prev_ebr_addr;

				ebr->next_ebr_entry.sector_num =
						pinfo->bytes_size / flash_blk_size;
				prev_ebr_addr = first_ebr_addr + flash_blk_size * (
						ebr->next_ebr_entry.rel_sector_start
						- ebr->entry.rel_sector_start - ebr->entry.sector_num);
				write_mbr(prev_ebr_addr, (struct mbr_table *)ebr);
				ebr = NULL;
			}

			LTRACEF("#%d, pinfo@%p name %s start_addr 0x%llx\n",
				    i, pinfo, pinfo->name, pinfo->start_addr);
			mbr = memalign(CACHE_LINE, ROUNDUP(MBR_SIZE, CACHE_LINE));
			if (!mbr) {
				TRACEF("ERROR %s: No Memory!!\n", __func__);
				return -ENOMEM;
			}
			memset(mbr, 0, MBR_SIZE);
			mbr->signature = MBR_SIGN;
			ebr = (struct ebr_table *)mbr;
			pinfo->mbr_addr = start_ebr_addr;
			pinfo->mbr = mbr;
			pinfo->mbr_index = 0;
			pinfo->is_extend = true;
			pinfo->is_use = true;

			pinfo->start_addr = start_ebr_addr + EBR_PARTITION_OFFEST;
			pinfo->start_block = pinfo->start_addr / flash_blk_size;

			ebr->entry.rel_sector_start = EBR_PARTITION_OFFEST / flash_blk_size;

			pinfo->bytes_size -= EBR_PARTITION_OFFEST;
			pinfo->block_size = pinfo->bytes_size / flash_blk_size;

			ebr->entry.sector_num = pinfo->block_size;

			ebr->entry.id = 0x83;
			ebr->entry.head_start = 0x3;
			ebr->entry.sector_start = 0xd0;
			ebr->entry.cylinder_start = 0xff;
			ebr->entry.head_end = 0x3;
			ebr->entry.sector_end = 0xd0;
			ebr->entry.cylinder_end = 0xff;

			if (ebr) { /* prve ebr next */
				start_ebr_addr = start_ebr_addr + pinfo->bytes_size
					+ EBR_PARTITION_OFFEST;
				ebr->next_ebr_entry.rel_sector_start = (start_ebr_addr
					 - first_ebr_addr) / flash_blk_size;
				ebr->next_ebr_entry.id = 0x5;
				ebr->next_ebr_entry.head_start = 0x3;
				ebr->next_ebr_entry.sector_start = 0xd0;
				ebr->next_ebr_entry.cylinder_start = 0xff;
				ebr->next_ebr_entry.head_end = 0x3;
				ebr->next_ebr_entry.sector_end = 0xd0;
				ebr->next_ebr_entry.cylinder_end = 0xff;
			}
next_part:
			i++;
		}

		if (ebr) { /* Last partition */
			uint64_t prev_ebr_addr;
			prev_ebr_addr = first_ebr_addr + flash_blk_size * (
				    ebr->next_ebr_entry.rel_sector_start
				    - ebr->entry.rel_sector_start - ebr->entry.sector_num);
			write_mbr(prev_ebr_addr, (struct mbr_table *)ebr);
			ebr = NULL;
		}

	}
	return 0;
}

int read_part_info_from_mbr(struct part_info *p_infos) {
	struct mbr_table *mbr = NULL;
	struct part_info *pinfo = &p_infos[0];
	int count = 0;
	int i;

	if (read_mbr(0x0, &pinfo->mbr) >= 0) {
		mbr = pinfo->mbr;
		for (i = 0; i < 4; i++) {
			pinfo = &p_infos[i + 1];

			LTRACEF("Fill #%d pinfo %s by primary partitions#%d\n",
				    i + 1, pinfo->name, i);

			pinfo->mbr_addr = 0x0;
			pinfo->mbr = mbr;
			pinfo->mbr_index = i;
			pinfo->is_extend = false;

			pinfo->start_block = mbr->part[i].rel_sector_start;
			pinfo->start_addr = pinfo->start_block * flash_blk_size;
			pinfo->block_size = mbr->part[i].sector_num;
			pinfo->bytes_size = pinfo->block_size * flash_blk_size;

			if (pinfo->id != PART_EXTEND &&
				    pinfo->length != pinfo->bytes_size) {
				TRACEF("[ERROR] pinfo %s length 0x%x != "
					    "bytes_size %x\n",
					    pinfo->name,
					    (int)pinfo->length, (int)pinfo->bytes_size);
			}
		}
		count = i++;

		if (pinfo->id == PART_EXTEND && pinfo->start_addr) {
			struct ebr_table *ebr;
			uint64_t first_ebr_addr;
			uint64_t start_ebr_addr;
			first_ebr_addr = pinfo->start_addr;
			start_ebr_addr = first_ebr_addr;
			while (start_ebr_addr && i < MAX_PART_INFO) {
				pinfo = &p_infos[i];
				if (!pinfo->is_use) {
					i++;
					continue;
				}
				read_mbr(start_ebr_addr, &pinfo->mbr);
				ebr = (struct ebr_table *)pinfo->mbr;
				LTRACEF("Fill #%d pinfo %s by extend partitions\n",
					    i, pinfo->name);

				pinfo->mbr_addr = start_ebr_addr;
				pinfo->mbr_index = 0;
				pinfo->is_extend = true;

				pinfo->start_addr = start_ebr_addr
						+ (uint64_t)ebr->entry.rel_sector_start
						 * flash_blk_size;
				pinfo->start_block = pinfo->start_addr / flash_blk_size;
				pinfo->block_size = ebr->entry.sector_num;
				pinfo->bytes_size = pinfo->block_size * flash_blk_size;

				if (pinfo->length !=
					    (pinfo->bytes_size + EBR_PARTITION_OFFEST)) {
					TRACEF("[ERROR] pinfo %s "
						    "length 0x%x != "
						    "bytes_size 0x%x + EBR_PARTITION_OFFEST 0x%x\n",
						    pinfo->name,
						    (int)pinfo->length, (int)pinfo->bytes_size,
						    EBR_PARTITION_OFFEST);
				}

				if (ebr->next_ebr_entry.rel_sector_start)
					start_ebr_addr = first_ebr_addr +
							+ (uint64_t)ebr->next_ebr_entry.rel_sector_start
							 * flash_blk_size;
				else
					start_ebr_addr = 0;

				i++;
				count++;
			}
		}
	}

	return count;
}
