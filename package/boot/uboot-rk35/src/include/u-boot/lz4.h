/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * Copyright 2019 Google LLC
 */

#ifndef __LZ4_H
#define __LZ4_H

#define LZ4F_MAGIC 0x184D2204

struct lz4_frame_header {
	u32 magic;
	union {
		u8 flags;
		struct {
			u8 reserved0:2;
			u8 has_content_checksum:1;
			u8 has_content_size:1;
			u8 has_block_checksum:1;
			u8 independent_blocks:1;
			u8 version:2;
		};
	};
	union {
		u8 block_descriptor;
		struct {
			u8 reserved1:4;
			u8 max_block_size:3;
			u8 reserved2:1;
		};
	};
	/* + u64 content_size iff has_content_size is set */
	/* + u8 header_checksum */
} __packed;

struct lz4_block_header {
	union {
		u32 raw;
		struct {
			u32 size:31;
			u32 not_compressed:1;
		};
	};
	/* + size bytes of data */
	/* + u32 block_checksum iff has_block_checksum is set */
} __packed;

bool lz4_is_valid_header(const unsigned char *h);

/**
 * ulz4fn() - Decompress LZ4 data
 *
 * @src: Source data to decompress
 * @srcn: Length of source data
 * @dst: Destination for uncompressed data
 * @dstn: Returns length of uncompressed data
 * @return 0 if OK, -EPROTONOSUPPORT if the magic number or version number are
 *	not recognised or independent blocks are used, -EINVAL if the reserved
 *	fields are non-zero, or input is overrun, -EENOBUFS if the destination
 *	buffer is overrun, -EEPROTO if the compressed data causes an error in
 *	the decompression algorithm
 */
int ulz4fn(const void *src, size_t srcn, void *dst, size_t *dstn);

#endif
