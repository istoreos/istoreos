/*
 * Copyright 2017, Rockchip Electronics Co., Ltd
 * hisping lin, <hisping.lin@rock-chips.com>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */
#ifndef TEE_RPC_H
#define TEE_RPC_H

#include <optee_include/tee_base_types.h>
/*
 * tee_rpc_invoke cmd definitions, keep in sync with tee-supplicant
 */
#define TEE_RPC_LOAD_TA		0x10000001
#define TEE_RPC_FREE_TA		0x10000009
#define TEE_RPC_RPMB_CMD	0x1000000A
#define TEE_RPC_FS		0x10000010
#define TEE_RPC_GET_TIME	0x10000011

/* RPMB Related defines */
#define TEE_RPC_RPMB_CMD_DATA_REQ       0x00
#define TEE_RPC_RPMB_CMD_GET_DEV_INFO   0x01

#define TEE_RPC_RPMB_MSG_TYPE_REQ_AUTH_KEY_PROGRAM          0x0001
#define TEE_RPC_RPMB_MSG_TYPE_REQ_WRITE_COUNTER_VAL_READ    0x0002
#define TEE_RPC_RPMB_MSG_TYPE_REQ_AUTH_DATA_WRITE           0x0003
#define TEE_RPC_RPMB_MSG_TYPE_REQ_AUTH_DATA_READ            0x0004
#define TEE_RPC_RPMB_MSG_TYPE_REQ_RESULT_READ               0x0005
#define TEE_RPC_RPMB_MSG_TYPE_RESP_AUTH_KEY_PROGRAM         0x0100
#define TEE_RPC_RPMB_MSG_TYPE_RESP_WRITE_COUNTER_VAL_READ   0x0200
#define TEE_RPC_RPMB_MSG_TYPE_RESP_AUTH_DATA_WRITE          0x0300
#define TEE_RPC_RPMB_MSG_TYPE_RESP_AUTH_DATA_READ           0x0400

/* keep in sync with Linux driver */
#define TEE_RPC_WAIT_MUTEX	0x20000000
/* Values specific to TEE_RPC_WAIT_MUTEX */
#define TEE_WAIT_MUTEX_SLEEP	0
#define TEE_WAIT_MUTEX_WAKEUP	1
#define TEE_WAIT_MUTEX_DELETE	2
#define TEE_RPC_WAIT		0x30000000

#endif
