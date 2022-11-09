/*
 * (C) Copyright 2017 Rockchip Electronics Co., Ltd
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */

#ifndef TEESMC_V2_H
#define TEESMC_V2_H

#define OPTEE_SMC_CALL_WITH_ARG_V2 0x32000004

struct optee_msg_param_tmem_v2 {
	uint64_t buf_ptr;
	uint64_t size;
	uint64_t shm_ref;
};

struct optee_msg_param_rmem_v2 {
	uint64_t offs;
	uint64_t size;
	uint64_t shm_ref;
};

struct optee_msg_param_value_v2 {
	uint64_t a;
	uint64_t b;
	uint64_t c;
};

struct optee_msg_param_v2 {
	uint64_t attr;
	union {
		struct optee_msg_param_tmem_v2 memref;
		struct optee_msg_param_rmem_v2 rmem;
		struct optee_msg_param_value_v2 value;
	} u;
};

struct optee_msg_arg_v2 {
	uint32_t cmd;
	uint32_t ta_func;
	uint32_t session;
	uint32_t cancel_id;
	uint32_t pad;
	uint32_t ret;
	uint32_t ret_origin;
	uint32_t num_params;

	/* num_params tells the actual number of element in params */
	struct optee_msg_param_v2 params[];
};

typedef struct optee_msg_arg_v2        t_teesmc32_arg;
typedef struct optee_msg_param_v2      t_teesmc32_param;

#define TEESMC32_GET_ARG_SIZE(num_params) \
	(sizeof(struct optee_msg_arg_v2) + \
	 sizeof(struct optee_msg_param_v2) * (num_params))

#define TEESMC32_GET_PARAMS(x) \
	(struct optee_msg_param_v2 *)(((struct optee_msg_arg_v2 *)(x)) + 1)

#define OPTEE_MSG_ATTR_TYPE_NONE_V2		0x0
#define OPTEE_MSG_ATTR_TYPE_VALUE_INPUT_V2		0x1
#define OPTEE_MSG_ATTR_TYPE_VALUE_OUTPUT_V2		0x2
#define OPTEE_MSG_ATTR_TYPE_VALUE_INOUT_V2		0x3
#define OPTEE_MSG_ATTR_TYPE_RMEM_INPUT_V2		0x5
#define OPTEE_MSG_ATTR_TYPE_RMEM_OUTPUT_V2		0x6
#define OPTEE_MSG_ATTR_TYPE_RMEM_INOUT_V2		0x7
#define OPTEE_MSG_ATTR_TYPE_TMEM_INPUT_V2		0x9
#define OPTEE_MSG_ATTR_TYPE_TMEM_OUTPUT_V2		0xa
#define OPTEE_MSG_ATTR_TYPE_TMEM_INOUT_V2		0xb

#define OPTEE_MSG_ATTR_META_V2			(1 << (8))

#define OPTEE_MSG_RPC_CMD_SHM_ALLOC_V2	6
#define OPTEE_MSG_RPC_CMD_SHM_FREE_V2	7

#define OPTEE_MSG_RPC_CMD_LOAD_TA_V2	0

#define OPTEE_MSG_RPC_CMD_RPMB_V2		1

#define OPTEE_MSG_RPC_CMD_FS_V2		2

#define OPTEE_SMC_32_V2			0
#define OPTEE_SMC_64_V2			0x40000000
#define OPTEE_SMC_FAST_CALL_V2		0x80000000
#define OPTEE_SMC_STD_CALL_V2		0

#define OPTEE_SMC_OWNER_MASK_V2		0x3F
#define OPTEE_SMC_OWNER_SHIFT_V2		24

#define OPTEE_SMC_FUNC_MASK_V2		0xFFFF

#define OPTEE_SMC_OWNER_TRUSTED_OS_V2	50
#define OPTEE_SMC_OWNER_TRUSTED_OS_API	63

#define OPTEE_SMC_FUNCID_GET_SHM_CONFIG_V2	7
#define OPTEE_SMC_GET_SHM_CONFIG_V2 \
	OPTEE_SMC_FAST_CALL_VAL_V2(OPTEE_SMC_FUNCID_GET_SHM_CONFIG_V2)

#define OPTEE_SMC_FUNCID_CALLS_REVISION	0xFF03
#define OPTEE_SMC_CALLS_REVISION \
	OPTEE_SMC_CALL_VAL_V2(OPTEE_SMC_32_V2, OPTEE_SMC_FAST_CALL_V2, \
			      OPTEE_SMC_OWNER_TRUSTED_OS_API, \
			      OPTEE_SMC_FUNCID_CALLS_REVISION)

#define OPTEE_SMC_FAST_CALL_VAL_V2(func_num) \
	OPTEE_SMC_CALL_VAL_V2(OPTEE_SMC_32_V2, OPTEE_SMC_FAST_CALL_V2, \
			   OPTEE_SMC_OWNER_TRUSTED_OS_V2, (func_num))

#define OPTEE_SMC_CALL_VAL_V2(type, calling_convention, owner, func_num) \
			((type) | (calling_convention) | \
			(((owner) & OPTEE_SMC_OWNER_MASK_V2) << \
				OPTEE_SMC_OWNER_SHIFT_V2) |\
			((func_num) & OPTEE_SMC_FUNC_MASK_V2))

#endif /* TEESMC_V2_H */
