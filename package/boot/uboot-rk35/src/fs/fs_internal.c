/*
 * 2017 by Marek Behun <marek.behun@nic.cz>
 *
 * Derived from code in ext4/dev.c, which was based on reiserfs/dev.c
 *
 * SPDX-License-Identifier:	GPL-2.0
 */

#include <common.h>
#include <compiler.h>
#include <part.h>
#include <memalign.h>

int fs_devread(struct blk_desc *blk, disk_partition_t *partition,
	       lbaint_t sector, int byte_offset, int byte_len, char *buf)
{
	unsigned block_len;
	int log2blksz;
	ALLOC_CACHE_ALIGN_BUFFER(char, sec_buf, (blk ? blk->blksz : 0));
	if (blk == NULL) {
		printf("** Invalid Block Device Descriptor (NULL)\n");
		return 0;
	}
	log2blksz = blk->log2blksz;

	/* Check partition boundaries */
	if ((sector + ((byte_offset + byte_len - 1) >> log2blksz))
	    >= partition->size) {
		printf("%s read outside partition " LBAFU "\n", __func__,
		       sector);
		return 0;
	}

	/* Get the read to the beginning of a partition */
	sector += byte_offset >> log2blksz;
	byte_offset &= blk->blksz - 1;

	debug(" <" LBAFU ", %d, %d>\n", sector, byte_offset, byte_len);

	if (byte_offset != 0) {
		int readlen;
		/* read first part which isn't aligned with start of sector */
		if (blk_dread(blk, partition->start + sector, 1,
			      (void *)sec_buf) != 1) {
			printf(" ** %s read error **\n", __func__);
			return 0;
		}
		readlen = min((int)blk->blksz - byte_offset,
			      byte_len);
		memcpy(buf, sec_buf + byte_offset, readlen);
		buf += readlen;
		byte_len -= readlen;
		sector++;
	}

	if (byte_len == 0)
		return 1;

	/* read sector aligned part */
	block_len = byte_len & ~(blk->blksz - 1);

	if (block_len == 0) {
		ALLOC_CACHE_ALIGN_BUFFER(u8, p, blk->blksz);

		block_len = blk->blksz;
		blk_dread(blk, partition->start + sector, 1,
			  (void *)p);
		memcpy(buf, p, byte_len);
		return 1;
	}

	if (blk_dread(blk, partition->start + sector,
		      block_len >> log2blksz, (void *)buf) !=
			block_len >> log2blksz) {
		printf(" ** %s read error - block\n", __func__);
		return 0;
	}
	block_len = byte_len & ~(blk->blksz - 1);
	buf += block_len;
	byte_len -= block_len;
	sector += block_len / blk->blksz;

	if (byte_len != 0) {
		/* read rest of data which are not in whole sector */
		if (blk_dread(blk, partition->start + sector, 1,
			      (void *)sec_buf) != 1) {
			printf("* %s read error - last part\n", __func__);
			return 0;
		}
		memcpy(buf, sec_buf, byte_len);
	}
	return 1;
}
