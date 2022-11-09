/*
 * Copyright 2017, Rockchip Electronics Co., Ltd
 * hisping lin, <hisping.lin@rock-chips.com>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */
#ifndef TEE_RPC_TYPES_H
#define TEE_RPC_TYPES_H

#include <optee_include/tee_base_types.h>
#include <optee_include/tee_api_types.h>

struct tee_rpc_load_ta_cmd {
	TEE_UUID uuid;
	uint32_t va;
};

struct tee_rpc_rpmb_cmd {
	uint16_t cmd;
	uint16_t dev_id;
	uint16_t block_count;
	/* variable length of data */
	/* uint8_t data[]; REMOVED! */
};

#define TEE_RPC_RPMB_EMMC_CID_SIZE 16
struct tee_rpc_rpmb_dev_info {
	uint8_t cid[TEE_RPC_RPMB_EMMC_CID_SIZE];
	/* EXT CSD-slice 168 "RPMB Size" */
	uint8_t rpmb_size_mult;
	/* EXT CSD-slice 222 "Reliable Write Sector Count" */
	uint8_t rel_wr_sec_c;
	/* Check the ret code and accept the data only if it is OK. */
	uint8_t ret_code;
};

#endif
