/*
 * (C) Copyright 2003
 * Kyle Harris, kharris@nexus-tech.net
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <common.h>
#include <command.h>
#include <mmc.h>

static int curr_sd_device = -1;

enum mmc_state {
	MMC_INVALID,
	MMC_READ,
	MMC_WRITE,
	MMC_ERASE,
	MMC_RPMB_CHANGE,
	MMC_UDA_CHANGE,
	MMC_RPMB_WRITE_KEY,
	MMC_RPMB_WRITE_DATA,
	MMC_RPMB_READ_DATA,
	MMC_RPMB_GET_COUNTER,
	MMC_KS,
	MMC_CID,
};

extern block_dev_desc_t *sd_get_dev(int dev);

int do_sdops(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	enum mmc_state state;

    if (argc < 2) {
		return CMD_RET_USAGE;
	}

	if (curr_sd_device < 0) {
		if (get_mmc_num() > 0)
			curr_sd_device = 0;
		else {
			printf("No SD device available(%d)\n", get_mmc_num());
			return -1;
		}
	}

	if ( !strcmp(argv[1], "init") || !strcmp(argv[1], "rescan") ) {

		struct mmc *mmc = find_sd_device();

		if (!mmc) {
			printf("no SD device at slot %x\n", curr_sd_device);
			return -1;
		}
		mmc->has_init = 0;

		if (sd_init(mmc)!=0) {
			printf("initialize SD device at slot %x failed\n", curr_sd_device);
			return -1; /* error */
		}
		else {
			return 0; /* successful */
		}
	}

	if (strncmp(argv[1], "part", 4) == 0) {

		int dev = 0;
		block_dev_desc_t * dev_desc;

		if (argc > 2) {
			dev = (int)simple_strtoul(argv[2], NULL, 10);
		}
		dev_desc = sd_get_dev(dev);
		if( dev_desc == NULL ) {
			printf("\nSD device %d not available\n", dev);
		}
		print_part(dev_desc);

		return 0;
	}

	if (strcmp(argv[1], "read") == 0)
		state = MMC_READ;
	else if (strcmp(argv[1], "write") == 0)
		state = MMC_WRITE;
	else
		state = MMC_INVALID;

	if (state != MMC_INVALID) {
		struct mmc *mmc = find_sd_device();
		int idx = 2;
		u32 blk, cnt, n;
		void *addr;

		if (state != MMC_ERASE) {
			addr = (void *)simple_strtoul(argv[idx], NULL, 16);
			++idx;
		} else
			addr = 0;

		blk = simple_strtoul(argv[idx], NULL, 16);
		cnt = simple_strtoul(argv[idx + 1], NULL, 16);

		if (!mmc) {
			printf("no sd device at slot %x\n", curr_sd_device);
			return -1;
		}

		printf("SD %s: dev# %d, block# %d, count# %d ... \n",
			argv[1], curr_sd_device, blk, cnt);


		if( mmc->has_init == 0 ) {
			if(sd_init(mmc)!=0) {
				printf("initialize SD device at slot %x fail\n", curr_sd_device);
				return -1; /* error */
			}
			else {
				return 0; /* successful */
			}
		}

		switch (state) {
		case MMC_READ:
			printf("do sd_ops MMC_READ\n");
			n = mmc->block_dev.block_read(curr_sd_device, blk, cnt, addr);
			/* flush cache after read */
			flush_cache((ulong)addr, cnt * 512); /* FIXME */
			break;
		case MMC_WRITE:
			printf("do sd_ops MMC_WRITE\n");
			n = mmc->block_dev.block_write(curr_sd_device, blk, cnt, addr);
			break;
		/*case MMC_ERASE:
			n = mmc->block_dev.block_erase(curr_sd_device, blk, cnt);
			break;*/
		default:
			BUG();
		}

		printf("%d blocks %s: %s\n",
			n, argv[1], (n == cnt) ? "OK" : "ERROR");

		return (n == cnt) ? 0 : -1;
	}

	return CMD_RET_USAGE;
}

U_BOOT_CMD(
	sd, 6, 1, do_sdops,
	"SD sub system",
	"cmd_type argument1  argument2\n"
	"sd init\n"
	"sd rescan\n"
	"sd part\n"
	"sd read addr blk# cnt#\n"
	"sd write addr blk# cnt#\n"
);
