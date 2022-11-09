/*
 * Copyright 2017, Rockchip Electronics Co., Ltd
 * hisping lin, <hisping.lin@rock-chips.com>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */
#ifndef _OPTEE_CLIENT_APILIB_H_
#define _OPTEE_CLIENT_APILIB_H_

#include <optee_include/tee_base_types.h>
#include <optee_include/tee_client_api.h>

TEEC_Result OpteeClientApiLibInitialize(void);
void optee_get_shm_config(phys_addr_t *base, phys_size_t *size);

#endif /*_OPTEE_CLIENT_APILIB_H_*/
