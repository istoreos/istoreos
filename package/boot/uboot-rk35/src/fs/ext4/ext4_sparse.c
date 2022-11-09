/*
 * (C) Copyright 2022 Rockchip Electronics Co., Ltd
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */

#include <common.h>
#include <blk.h>
#include <memalign.h>
#include <image-sparse.h>
#include <u-boot/sha256.h>

/******************************************************************************/
#define PER_BLK_WRITE_SIZE	SZ_8M	  /* Avoid -ENOMEM, eg: bounce buffer */
#define DEBUG_SPARSE

/******************************************************************************/
static void print_header_info(sparse_header_t *header)
{
#ifdef DEBUG_SPARSE
	printf("  ==== sparse header ===\n");
	printf("  magic:          0x%x\n", header->magic);
	printf("  major_version:  0x%x\n", header->major_version);
	printf("  minor_version:  0x%x\n", header->minor_version);
	printf("  file_hdr_sz:    %d\n", header->file_hdr_sz);
	printf("  chunk_hdr_sz:   %d\n", header->chunk_hdr_sz);
	printf("  blk_sz:         %d\n", header->blk_sz);
	printf("  total_blks:     %d\n", header->total_blks);
	printf("  total_chunks:   %d\n", header->total_chunks);
	printf("  image_checksum: %d\n\n", header->image_checksum);
#endif
}

static void print_chunk_info(chunk_header_t *chunk, u32 id,
			     const u8 *ptr, sparse_header_t *header)
{
#ifdef DEBUG_SPARSE
	const char *type;

	if (chunk->chunk_type == CHUNK_TYPE_RAW)
		type = "RAW";
	else if (chunk->chunk_type == CHUNK_TYPE_DONT_CARE)
		type = "DONT CARE";
	else if (chunk->chunk_type == CHUNK_TYPE_FILL)
		type = "FILL";
	else if (chunk->chunk_type == CHUNK_TYPE_CRC32)
		type = "CRC32";
	else
		type = "UNK";

	printf("  === [chunk.%d]\n", id + 1);
	printf("  chunk_type: %s\n", type);
	printf("  chunk_sz:   %d\n", chunk->chunk_sz);
	printf("  total_sz:   %d\n", chunk->total_sz);
	printf("  offset:     %ld\n", (ulong)ptr - (ulong)header);
	printf("  buf:        0x%08lx\n", (ulong)ptr);
#endif
}

static int flash_write_data(struct blk_desc *desc, const u8 *data,
			    ulong offset, ulong blocks)
{	const u8 *buf = data;
	u32 step = BLOCK_CNT(PER_BLK_WRITE_SIZE, desc);
	long left = blocks;	/* signed long ! */
	ulong lba = offset;
	ulong blks;

#ifdef DEBUG_SPARSE
	printf("  lba:        0x%08lx - 0x%08lx\n", lba, lba + blocks);
#ifdef CONFIG_SHA256
	u8 hash[32];
	int i;

	sha256_csum(data, blocks * desc->blksz, hash);
	printf("  sha256sum:  ");
	for (i = 0; i < ARRAY_SIZE(hash); i++)
		printf("%02x", hash[i]);
	printf("\n");
#endif
#endif
	while (left > 0) {
		if (left < step)
			blks = left;
		else
			blks = step;

		if (blks != blk_dwrite(desc, lba, blks, buf)) {
			printf("Raw data: LBA 0x%lx written error.\n", lba);
			return -EIO;
		}
		buf += blks * desc->blksz;
		lba += blks;
		left -= step;
	}

	return 0;
}

static int flash_fill_data(struct blk_desc *desc, ulong offset, ulong blocks,
			   u32 fill_val)
{
	u32 step = BLOCK_CNT(PER_BLK_WRITE_SIZE, desc);
	long left = blocks;	/* signed long ! */
	ulong lba = offset;
	ulong blks;
	char *buf;

	buf = malloc(PER_BLK_WRITE_SIZE);
	if (!buf) {
		printf("No memory\n");
		return -ENOMEM;
	}
#ifdef DEBUG_SPARSE
	printf("  lba:        0x%08lx - 0x%08lx\n", lba, lba + blocks);
	printf("  fill:       0x%08x\n", fill_val);
#endif
	memset((char *)buf, fill_val, PER_BLK_WRITE_SIZE);
	while (left > 0) {
		if (left < step)
			blks = left;
		else
			blks = step;

		if (blks != blk_dwrite(desc, lba, blks, buf)) {
			printf("Fill data: LBA 0x%lx write error.\n", lba);
			free(buf);
			return -EIO;
		}
		lba += blks;
		left -= step;
	}
	free(buf);

	return 0;
}

/******************************************************************************/
int ext4_unsparse(struct blk_desc *desc, const u8 *buf, ulong start)
{
	sparse_header_t *header = (sparse_header_t *)buf;
	chunk_header_t *chunk = NULL;
	ulong blk = start;
	ulong chunk_len;
	u64 img_size;
	u32 i, fill;

	putc('\n');

	if (!is_sparse_image(header)) {
		printf("Invalid sparse format.\n");
		return -EINVAL;
	}

	print_header_info(header);

	/* check fs img's real size is larger than partition size */
	img_size = (u64)(header->total_blks * header->blk_sz);

	/* erase area: ensure DONT-CARE is 0 and FILL(0x0) is 0 */
	if (blk_derase(desc, start, BLOCK_CNT(img_size, desc)) !=
			BLOCK_CNT(img_size, desc))
		return -EIO;

	printf("Erase 0x%08lx - 0x%08lx blocks OK.\n\n",
	       start, start + (ulong)BLOCK_CNT(img_size, desc));

	/* skip the sparse header,to visit first chunk */
	buf += header->file_hdr_sz;

	/* to visit each chunk */
	for (i = 0; i < header->total_chunks; i++) {
		/* here the chunk_header */
		chunk = (chunk_header_t *)buf;

		/* go to next chunk's data */
		buf += header->chunk_hdr_sz;

		switch (chunk->chunk_type) {
		case CHUNK_TYPE_RAW:
			print_chunk_info(chunk, i, buf, header);

			/* to calculate the length of each chunk */
			chunk_len = chunk->chunk_sz * header->blk_sz;

			/* verify every chunk to asure it is valid */
			if (chunk->total_sz
			    != (chunk_len + header->chunk_hdr_sz)) {
				printf("No.%d chunk size error.\n", i + 1);
				return -EINVAL;
			}

			if (flash_write_data(desc, buf,
					     blk, BLOCK_CNT(chunk_len, desc)))
				return -EIO;

			buf += chunk_len;
			blk += BLOCK_CNT(chunk_len, desc);
			break;
		case CHUNK_TYPE_DONT_CARE:
			print_chunk_info(chunk, i, buf, header);

			if (chunk->total_sz != header->chunk_hdr_sz) {
				printf("No.%d chunk size error.\n", i + 1);
				return -EINVAL;
			}

			chunk_len = chunk->chunk_sz * header->blk_sz;
			blk += BLOCK_CNT(chunk_len, desc);
			break;
		case CHUNK_TYPE_FILL:
			print_chunk_info(chunk, i, buf, header);

			/* verify every chunk to asure it is valid */
			if (chunk->total_sz - header->chunk_hdr_sz != 4) {
				printf("No.%d chunk size error.\n", i);
				return -EINVAL;
			}

			/* to calculate the length of each chunk */
			chunk_len = chunk->chunk_sz * header->blk_sz;

			/* ignore fill value "0", as we have erased yet */
			fill = *(u32 *)buf;
			if (fill != 0) {
				if (flash_fill_data(desc, blk,
					BLOCK_CNT(chunk_len, desc), fill))
					return -EIO;
			}
			buf += 4;
			blk += BLOCK_CNT(chunk_len, desc);
			break;
		case CHUNK_TYPE_CRC32:
			print_chunk_info(chunk, i, buf, header);
			printf("No.%d chunk type CRC32, Cannot handle!\n", i + 1);
			return -ENOTSUPP;
		default:
			printf("sparse: unknown chunk type %04x.\n", chunk->chunk_type);
			return -ENOTSUPP;
		}
	}

	printf("\nUnsparsed is %lld MiB and 0x%08lx - 0x%08lx blocks written OK.\n",
	       img_size >> 20, start, blk);

	return 0;
}

