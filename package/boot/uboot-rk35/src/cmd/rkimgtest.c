/*
 * (C) Copyright 2019 Rockchip Electronics Co., Ltd
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */

#include <common.h>
#include <malloc.h>

static int do_rkimg_test(cmd_tbl_t *cmdtp, int flag,
			 int argc, char *const argv[])
{
	struct blk_desc *dev_desc;
	u32 *buffer;
	int ret;

	if (argc != 3)
		return CMD_RET_USAGE;

	dev_desc = blk_get_dev(argv[1], simple_strtoul(argv[2], NULL, 16));
	if (!dev_desc) {
		printf("%s: dev_desc is NULL!\n", __func__);
		return CMD_RET_FAILURE;
	}

	/* read one block from beginning of IDB data */
	buffer = memalign(ARCH_DMA_MINALIGN, 1024);
	ret = blk_dread(dev_desc, 64, 2, buffer);
	if (ret != 2) {
		printf("%s: Failed to read data from IDB\n", __func__);
		free(buffer);
		return CMD_RET_FAILURE;
	}

	if (buffer[0] == 0xFCDC8C3B) {
		ret = CMD_RET_SUCCESS;

		if (!strcmp("mmc", argv[1]))
			printf("Found IDB in SDcard\n");
		else
			printf("Found IDB in U-disk\n");

		/* TAG in IDB */
		if (0 == buffer[128 + 104 / 4]) {
			if (!strcmp("mmc", argv[1]))
				env_update("bootargs", "sdfwupdate");
			else
				env_update("bootargs", "usbfwupdate");
		}
	} else if (buffer[0] == 0x534e4b52 || buffer[0] == 0x534e5252) { // RKNS, RRNS
		/* The 0x534e4b52 & 0x534e5252 are the new idb block header tag */
		ret = CMD_RET_SUCCESS;
	} else {
		ret = CMD_RET_FAILURE;
	}

	free(buffer);

	return ret;
}

U_BOOT_CMD(
	rkimgtest, 3, 0,    do_rkimg_test,
	"Test if storage media have rockchip image",
	"<devtype> <devnum>"
);
