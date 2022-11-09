/*
 * Copied from Linux kernel crypto/crc32c.c
 * Copyright (c) 2004 Cisco Systems, Inc.
 * Copyright (c) 2008 Herbert Xu <herbert@gondor.apana.org.au>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <common.h>
#include <compiler.h>

uint32_t crc32c_cal(uint32_t crc, const char *data, int length,
		    uint32_t *crc32c_table)
{
	while (length--)
		crc = crc32c_table[(u8)(crc ^ *data++)] ^ (crc >> 8);

	return crc;
}

void crc32c_init(uint32_t *crc32c_table, uint32_t pol)
{
	int i, j;
	uint32_t v;
	const uint32_t poly = pol; /* Bit-reflected CRC32C polynomial */

	for (i = 0; i < 256; i++) {
		v = i;
		for (j = 0; j < 8; j++)
			v = (v >> 1) ^ ((v & 1) ? poly : 0);

		crc32c_table[i] = v;
	}
}
