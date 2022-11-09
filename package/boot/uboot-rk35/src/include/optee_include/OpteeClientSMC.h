/*
 * Copyright 2017, Rockchip Electronics Co., Ltd
 * hisping lin, <hisping.lin@rock-chips.com>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */
#ifndef _OPTEE_CLIENT_SMC_H_
#define _OPTEE_CLIENT_SMC_H_

#include <optee_include/tee_base_types.h>
#include <optee_include/OpteeClientApiLib.h>

TEEC_Result TEEC_SMC_OpenSession(TEEC_Context * context,
				TEEC_Session * session,
				const TEEC_UUID * destination,
				TEEC_Operation * operation,
				uint32_t *error_origin);

TEEC_Result TEEC_SMC_CloseSession(TEEC_Session *session,
				uint32_t *error_origin);

TEEC_Result TEEC_SMC_InvokeCommand(TEEC_Session *session,
				uint32_t cmd_id,
				TEEC_Operation *operation,
				uint32_t *error_origin);

TEEC_Result TEEC_SMC_RequestCancellation(TEEC_Operation *operation,
				uint32_t *error_origin);

#endif /*_OPTEE_CLIENT_SMC_H_*/
