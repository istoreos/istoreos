/*
 * (C) Copyright 2008-2015 Fuzhou Rockchip Electronics Co., Ltd
 * Peter, Software Engineering, <superpeter.cai@gmail.com>.
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifdef USE_HOSTCC
#include <arpa/inet.h>
#else
#include <common.h>
#endif
#include <compiler.h>
#include <u-boot/crc.h>
#include "u-boot/zlib.h"

#define tole(x) cpu_to_le32(x)

/* ========================================================================
 * Table of CRC-32's of all single-byte values (made by make_crc_table)
 */
static const uint32_t crc_table[256] = {
	tole(0x00000000L), tole(0x04c10db7L), tole(0x09821b6eL), tole(0x0d4316d9L),
	tole(0x130436dcL), tole(0x17c53b6bL), tole(0x1a862db2L), tole(0x1e472005L),
	tole(0x26086db8L), tole(0x22c9600fL), tole(0x2f8a76d6L), tole(0x2b4b7b61L),
	tole(0x350c5b64L), tole(0x31cd56d3L), tole(0x3c8e400aL), tole(0x384f4dbdL),
	tole(0x4c10db70L), tole(0x48d1d6c7L), tole(0x4592c01eL), tole(0x4153cda9L),
	tole(0x5f14edacL), tole(0x5bd5e01bL), tole(0x5696f6c2L), tole(0x5257fb75L),
	tole(0x6a18b6c8L), tole(0x6ed9bb7fL), tole(0x639aada6L), tole(0x675ba011L),
	tole(0x791c8014L), tole(0x7ddd8da3L), tole(0x709e9b7aL), tole(0x745f96cdL),
	tole(0x9821b6e0L), tole(0x9ce0bb57L), tole(0x91a3ad8eL), tole(0x9562a039L),
	tole(0x8b25803cL), tole(0x8fe48d8bL), tole(0x82a79b52L), tole(0x866696e5L),
	tole(0xbe29db58L), tole(0xbae8d6efL), tole(0xb7abc036L), tole(0xb36acd81L),
	tole(0xad2ded84L), tole(0xa9ece033L), tole(0xa4aff6eaL), tole(0xa06efb5dL),
	tole(0xd4316d90L), tole(0xd0f06027L), tole(0xddb376feL), tole(0xd9727b49L),
	tole(0xc7355b4cL), tole(0xc3f456fbL), tole(0xceb74022L), tole(0xca764d95L),
	tole(0xf2390028L), tole(0xf6f80d9fL), tole(0xfbbb1b46L), tole(0xff7a16f1L),
	tole(0xe13d36f4L), tole(0xe5fc3b43L), tole(0xe8bf2d9aL), tole(0xec7e202dL),
	tole(0x34826077L), tole(0x30436dc0L), tole(0x3d007b19L), tole(0x39c176aeL),
	tole(0x278656abL), tole(0x23475b1cL), tole(0x2e044dc5L), tole(0x2ac54072L),
	tole(0x128a0dcfL), tole(0x164b0078L), tole(0x1b0816a1L), tole(0x1fc91b16L),
	tole(0x018e3b13L), tole(0x054f36a4L), tole(0x080c207dL), tole(0x0ccd2dcaL),
	tole(0x7892bb07L), tole(0x7c53b6b0L), tole(0x7110a069L), tole(0x75d1addeL),
	tole(0x6b968ddbL), tole(0x6f57806cL), tole(0x621496b5L), tole(0x66d59b02L),
	tole(0x5e9ad6bfL), tole(0x5a5bdb08L), tole(0x5718cdd1L), tole(0x53d9c066L),
	tole(0x4d9ee063L), tole(0x495fedd4L), tole(0x441cfb0dL), tole(0x40ddf6baL),
	tole(0xaca3d697L), tole(0xa862db20L), tole(0xa521cdf9L), tole(0xa1e0c04eL),
	tole(0xbfa7e04bL), tole(0xbb66edfcL), tole(0xb625fb25L), tole(0xb2e4f692L),
	tole(0x8aabbb2fL), tole(0x8e6ab698L), tole(0x8329a041L), tole(0x87e8adf6L),
	tole(0x99af8df3L), tole(0x9d6e8044L), tole(0x902d969dL), tole(0x94ec9b2aL),
	tole(0xe0b30de7L), tole(0xe4720050L), tole(0xe9311689L), tole(0xedf01b3eL),
	tole(0xf3b73b3bL), tole(0xf776368cL), tole(0xfa352055L), tole(0xfef42de2L),
	tole(0xc6bb605fL), tole(0xc27a6de8L), tole(0xcf397b31L), tole(0xcbf87686L),
	tole(0xd5bf5683L), tole(0xd17e5b34L), tole(0xdc3d4dedL), tole(0xd8fc405aL),
	tole(0x6904c0eeL), tole(0x6dc5cd59L), tole(0x6086db80L), tole(0x6447d637L),
	tole(0x7a00f632L), tole(0x7ec1fb85L), tole(0x7382ed5cL), tole(0x7743e0ebL),
	tole(0x4f0cad56L), tole(0x4bcda0e1L), tole(0x468eb638L), tole(0x424fbb8fL),
	tole(0x5c089b8aL), tole(0x58c9963dL), tole(0x558a80e4L), tole(0x514b8d53L),
	tole(0x25141b9eL), tole(0x21d51629L), tole(0x2c9600f0L), tole(0x28570d47L),
	tole(0x36102d42L), tole(0x32d120f5L), tole(0x3f92362cL), tole(0x3b533b9bL),
	tole(0x031c7626L), tole(0x07dd7b91L), tole(0x0a9e6d48L), tole(0x0e5f60ffL),
	tole(0x101840faL), tole(0x14d94d4dL), tole(0x199a5b94L), tole(0x1d5b5623L),
	tole(0xf125760eL), tole(0xf5e47bb9L), tole(0xf8a76d60L), tole(0xfc6660d7L),
	tole(0xe22140d2L), tole(0xe6e04d65L), tole(0xeba35bbcL), tole(0xef62560bL),
	tole(0xd72d1bb6L), tole(0xd3ec1601L), tole(0xdeaf00d8L), tole(0xda6e0d6fL),
	tole(0xc4292d6aL), tole(0xc0e820ddL), tole(0xcdab3604L), tole(0xc96a3bb3L),
	tole(0xbd35ad7eL), tole(0xb9f4a0c9L), tole(0xb4b7b610L), tole(0xb076bba7L),
	tole(0xae319ba2L), tole(0xaaf09615L), tole(0xa7b380ccL), tole(0xa3728d7bL),
	tole(0x9b3dc0c6L), tole(0x9ffccd71L), tole(0x92bfdba8L), tole(0x967ed61fL),
	tole(0x8839f61aL), tole(0x8cf8fbadL), tole(0x81bbed74L), tole(0x857ae0c3L),
	tole(0x5d86a099L), tole(0x5947ad2eL), tole(0x5404bbf7L), tole(0x50c5b640L),
	tole(0x4e829645L), tole(0x4a439bf2L), tole(0x47008d2bL), tole(0x43c1809cL),
	tole(0x7b8ecd21L), tole(0x7f4fc096L), tole(0x720cd64fL), tole(0x76cddbf8L),
	tole(0x688afbfdL), tole(0x6c4bf64aL), tole(0x6108e093L), tole(0x65c9ed24L),
	tole(0x11967be9L), tole(0x1557765eL), tole(0x18146087L), tole(0x1cd56d30L),
	tole(0x02924d35L), tole(0x06534082L), tole(0x0b10565bL), tole(0x0fd15becL),
	tole(0x379e1651L), tole(0x335f1be6L), tole(0x3e1c0d3fL), tole(0x3add0088L),
	tole(0x249a208dL), tole(0x205b2d3aL), tole(0x2d183be3L), tole(0x29d93654L),
	tole(0xc5a71679L), tole(0xc1661bceL), tole(0xcc250d17L), tole(0xc8e400a0L),
	tole(0xd6a320a5L), tole(0xd2622d12L), tole(0xdf213bcbL), tole(0xdbe0367cL),
	tole(0xe3af7bc1L), tole(0xe76e7676L), tole(0xea2d60afL), tole(0xeeec6d18L),
	tole(0xf0ab4d1dL), tole(0xf46a40aaL), tole(0xf9295673L), tole(0xfde85bc4L),
	tole(0x89b7cd09L), tole(0x8d76c0beL), tole(0x8035d667L), tole(0x84f4dbd0L),
	tole(0x9ab3fbd5L), tole(0x9e72f662L), tole(0x9331e0bbL), tole(0x97f0ed0cL),
	tole(0xafbfa0b1L), tole(0xab7ead06L), tole(0xa63dbbdfL), tole(0xa2fcb668L),
	tole(0xbcbb966dL), tole(0xb87a9bdaL), tole(0xb5398d03L), tole(0xb1f880b4L)
};

/* ========================================================================= */
#define DO_CRC(x) crc = tab[((crc >> 24) ^ (x)) & 255] ^ (crc << 8)
uint32_t crc32_rk(uint32_t crc, const unsigned char *s, uint32_t len)
{
	const uint32_t *tab;
	tab = crc_table;
	crc = cpu_to_le32(crc);
	do {
		DO_CRC(*s++);
	} while (--len);
	return le32_to_cpu(crc);
}
#undef DO_CRC
