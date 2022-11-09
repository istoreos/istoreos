/*
 * Copyright (c) 2018 Fuzhou Rockchip Electronics Co., Ltd
 *
 * SPDX-License-Identifier:	GPL-2.0
 */

#include <blk.h>
#include <common.h>

#include "rkflash_debug.h"
#include "rkflash_blk.h"
#include "boot_rkimg.h"

static unsigned int rkflash_debug;

__printf(1, 2) int rkflash_print_dio(const char *fmt, ...)
{
	int nret = 0;
#if PRINT_SWI_CON_IO
	if (rkflash_debug & PRINT_BIT_CON_IO)  {
		va_list args;

		if (!fmt)
			return nret;

		va_start(args, fmt);
		nret = vprintf(fmt, args);
		va_end(args);
	}
#endif
	return nret;
}

__printf(1, 2) int rkflash_print_bio(const char *fmt, ...)
{
	int nret = 0;
#if PRINT_SWI_BLK_IO
	if (rkflash_debug & PRINT_BIT_BLK_IO)  {
		va_list args;

		if (!fmt)
			return nret;

		va_start(args, fmt);
		nret = vprintf(fmt, args);
		va_end(args);
	}
#endif
	return nret;
}

__printf(1, 2) int rkflash_print_info(const char *fmt, ...)
{
	int nret = 0;
#if PRINT_SWI_INFO
	va_list args;

	if (!fmt)
		return nret;

	va_start(args, fmt);
	nret = vprintf(fmt, args);
	va_end(args);
#endif
	return nret;
}

__printf(1, 2) int rkflash_print_error(const char *fmt, ...)
{
	int nret = 0;
#if PRINT_SWI_ERROR
	va_list args;

	if (!fmt)
		return nret;

	va_start(args, fmt);
	nret = vprintf(fmt, args);
	va_end(args);
#endif
	return nret;
}

void rkflash_print_hex(const char *s, const void *buf, int w, size_t len)
{
}

#if (BLK_STRESS_TEST_EN)
#define max_test_sector 64
static u8 pwrite[max_test_sector * 512];
static u8 pread[max_test_sector * 512];
static u32 *pwrite32;
void blk_stress_test(struct udevice *udev)
{
	struct blk_desc *block_dev = rockchip_get_bootdev();
	u16 i, j, loop = 0;
	u32 test_end_lba, test_begin_lba;
	u32 test_lba;
	u16 test_sec_count = 1;
	u16 print_flag;

	if (!block_dev) {
		printf("device unknown\n");
		return;
	}

	if (block_dev->if_type == IF_TYPE_SPINOR)
		test_begin_lba = 0x4000;
	else
		test_begin_lba = 0x8000;

	test_end_lba = block_dev->lba;
	pwrite32 = (u32 *)pwrite;
	for (i = 0; i < (max_test_sector * 512); i++)
		pwrite[i] = i;
	for (loop = 0; loop < 100; loop++) {
		test_lba = test_begin_lba;
		printf("---------Test loop = %d---------\n", loop);
		printf("---------Test ftl write---------\n");
		test_sec_count = 1;
		printf("test_end_lba = %x\n", test_end_lba);
		printf("test_lba = %x\n", test_lba);
		for (; (test_lba + test_sec_count) < test_end_lba;) {
			pwrite32[0] = test_lba;
			blk_dwrite(block_dev, test_lba, test_sec_count, pwrite);
			blk_dread(block_dev, test_lba, test_sec_count, pread);
			for (j = 0; j < test_sec_count * 512; j++) {
				if (pwrite[j] != pread[j]) {
					printf("rkflash stress test fail\n");
					rkflash_print_hex("w:",
							  pwrite,
							  4,
							  test_sec_count * 128);
					rkflash_print_hex("r:",
							  pread,
							  4,
							  test_sec_count * 128);
					printf("r=%x, n=%x, w=%x, r=%x\n",
					       test_lba,
					       j,
					       pwrite[j],
					       pread[j]);
					while (1)
						;
				}
			}
			print_flag = test_lba & 0x1FF;
			if (print_flag < test_sec_count)
				printf("test_lba = %x\n", test_lba);
			test_lba += test_sec_count;
			test_sec_count++;
			if (test_sec_count > max_test_sector)
				test_sec_count = 1;
		}
		printf("---------Test ftl check---------\n");

		test_lba = test_begin_lba;
		test_sec_count = 1;
		for (; (test_lba + test_sec_count) < test_end_lba;) {
			pwrite32[0] = test_lba;
			blk_dread(block_dev, test_lba, test_sec_count, pread);
			print_flag = test_lba & 0x7FF;
			if (print_flag < test_sec_count)
				printf("test_lba = %x\n", test_lba);

			for (j = 0; j < test_sec_count * 512; j++) {
				if (pwrite[j] != pread[j]) {
					printf("rkflash stress test fail\n");
					printf("r=%x, n=%x, w=%x, r=%x\n",
					       test_lba,
					       j,
					       pwrite[j],
					       pread[j]);
					while (1)
						;
				}
			}
			test_lba += test_sec_count;
			test_sec_count++;
			if (test_sec_count > max_test_sector)
				test_sec_count = 1;
		}
	}
	printf("---------Test end---------\n");
	/* while(1); */
}
#endif

void rkflash_test(struct udevice *udev)
{
#if (BLK_STRESS_TEST_EN)
	blk_stress_test(udev);
#endif
}

