/*
 * Copyright 2020, Rockchip Electronics Co., Ltd
 * hisping lin, <hisping.lin@rock-chips.com>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <common.h>
#include <stdlib.h>
#include <command.h>
#include <boot_rkimg.h>
#include <part.h>
#ifdef CONFIG_OPTEE_V1
#include <optee_include/OpteeClientRkFs.h>
#endif
#ifdef CONFIG_OPTEE_V2
#include <optee_include/OpteeClientRkNewFs.h>
#endif

static int rkss_version;
static int get_rkss_version(void)
{
	struct blk_desc *dev_desc = NULL;
	disk_partition_t part_info;
	uint8_t *read_buff;
	unsigned long ret = 0;
	uint32_t *version;
	uint32_t *checkstr;

	if (rkss_version != 0)
		return rkss_version;

	dev_desc = rockchip_get_bootdev();
	if (!dev_desc) {
		printf("TEEC: %s: Could not find device\n", __func__);
		return -1;
	}

	if (part_get_info_by_name(dev_desc,
				  "security", &part_info) < 0) {
		printf("TEEC: Waring: Could not find security partition\n");
		rkss_version = RKSS_VERSION_ERR;
		return rkss_version;
	}

	read_buff = (uint8_t *)memalign(CONFIG_SYS_CACHELINE_SIZE, 512);
	if (!read_buff) {
		printf("TEEC: Malloc failed!\n");
		return -1;
	}

	ret = blk_dread(dev_desc, part_info.start, 1, read_buff);
	if (ret != 1) {
		printf("TEEC: blk_dread fail\n");
		free(read_buff);
		return -1;
	}

	version = (uint32_t *)(read_buff + 512 - 8);
	checkstr = (uint32_t *)(read_buff + 512 - 4);

	if (*version == 1 && *checkstr == 0x12345678)
		rkss_version = RKSS_VERSION_V1;
	else
		rkss_version = RKSS_VERSION_V2;

	free(read_buff);
	return rkss_version;
}

int OpteeClientRkFsInit(void)
{
	int version;

	version = get_rkss_version();
	debug("TEEC: OpteeClientRkFsInit version=%d\n", version);
	if (version == RKSS_VERSION_V1)
		return tee_supp_rk_fs_init_v1();
	else if (version == RKSS_VERSION_V2)
		return tee_supp_rk_fs_init_v2();
	else if (version == RKSS_VERSION_ERR)
		return 0;
	else
		return -1;
}

#ifdef CONFIG_OPTEE_V1
int OpteeClientRkFsProcess(void *cmd, size_t cmd_size)
{
	int version;

	version = get_rkss_version();
	debug("TEEC: OpteeClientRkFsProcess version=%d\n", version);
	if (version == RKSS_VERSION_V1)
		return tee_supp_rk_fs_process_v1(cmd, cmd_size);
	else if (version == RKSS_VERSION_V2)
		return tee_supp_rk_fs_process_v2(cmd, cmd_size);
	else
		return -1;
}
#endif

#ifdef CONFIG_OPTEE_V2
int OpteeClientRkFsProcess(size_t num_params,
			struct tee_ioctl_param *params)
{
	int version;

	version = get_rkss_version();
	debug("TEEC: OpteeClientRkFsProcess version=%d\n", version);
	if (version == RKSS_VERSION_V1)
		return tee_supp_rk_fs_process_v1(num_params, params);
	else if (version == RKSS_VERSION_V2)
		return tee_supp_rk_fs_process_v2(num_params, params);
	else
		return -1;
}
#endif
