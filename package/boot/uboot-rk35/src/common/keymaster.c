// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (c) 2019 Fuzhou Rockchip Electronics Co., Ltd
 */

#include <keymaster.h>
#include <common.h>
#include <boot_rkimg.h>
#include <malloc.h>

#include <optee_include/OpteeClientApiLib.h>
#include <optee_include/tee_client_api.h>
#include <optee_include/tee_api_defines.h>

TEEC_Result read_from_keymaster(uint8_t *filename,
				uint32_t filename_size,
				uint8_t *data,
				uint32_t size)
{
	TEEC_Result TeecResult;
	TEEC_Context TeecContext;
	TEEC_Session TeecSession;
	uint32_t ErrorOrigin;
	TEEC_UUID tempuuid = { 0x1b484ea5,
			       0x698b,
			       0x4142,
			       { 0x82, 0xb8, 0x3a,
				 0xcf, 0x16, 0xe9,
				 0x9e, 0x2a } };

	TEEC_UUID *TeecUuid = &tempuuid;
	TEEC_Operation TeecOperation = {0};
	struct blk_desc *dev_desc;

	dev_desc = rockchip_get_bootdev();
	if (!dev_desc) {
		printf("%s: dev_desc is NULL!\n", __func__);
		return -TEEC_ERROR_GENERIC;
	}

	debug("read_from_keymaster start\n");
	OpteeClientApiLibInitialize();

	TeecResult = TEEC_InitializeContext(NULL, &TeecContext);

	TeecOperation.paramTypes = TEEC_PARAM_TYPES(TEEC_VALUE_INPUT,
						    TEEC_NONE,
						    TEEC_NONE,
						    TEEC_NONE);

	/*0 nand or emmc "security" partition , 1 rpmb*/
	TeecOperation.params[0].value.a =
					 (dev_desc->if_type == IF_TYPE_MMC)
					 ? 1 : 0;
#ifdef CONFIG_OPTEE_ALWAYS_USE_SECURITY_PARTITION
	TeecOperation.params[0].value.a = 0;
#endif

	TeecResult = TEEC_OpenSession(&TeecContext,
				      &TeecSession,
				      TeecUuid,
				      TEEC_LOGIN_PUBLIC,
				      NULL,
				      &TeecOperation,
				      &ErrorOrigin);

	TEEC_SharedMemory SharedMem0 = {0};

	SharedMem0.size = filename_size;
	SharedMem0.flags = 0;

	TeecResult = TEEC_AllocateSharedMemory(&TeecContext, &SharedMem0);

	memcpy(SharedMem0.buffer, filename, SharedMem0.size);

	TEEC_SharedMemory SharedMem1 = {0};

	SharedMem1.size = size;
	SharedMem1.flags = 0;

	TeecResult = TEEC_AllocateSharedMemory(&TeecContext, &SharedMem1);

	TeecOperation.params[0].tmpref.buffer = SharedMem0.buffer;
	TeecOperation.params[0].tmpref.size = SharedMem0.size;

	TeecOperation.params[1].tmpref.buffer = SharedMem1.buffer;
	TeecOperation.params[1].tmpref.size = SharedMem1.size;

	TeecOperation.paramTypes = TEEC_PARAM_TYPES(TEEC_MEMREF_TEMP_INPUT,
						    TEEC_MEMREF_TEMP_INOUT,
						    TEEC_NONE,
						    TEEC_NONE);

	TeecResult = TEEC_InvokeCommand(&TeecSession,
					0,
					&TeecOperation,
					&ErrorOrigin);

	if (TeecResult == TEEC_SUCCESS)
		memcpy(data, SharedMem1.buffer, SharedMem1.size);
	TEEC_ReleaseSharedMemory(&SharedMem0);
	TEEC_ReleaseSharedMemory(&SharedMem1);
	TEEC_CloseSession(&TeecSession);
	TEEC_FinalizeContext(&TeecContext);
	debug("read_from_keymaster end\n");

	return TeecResult;
}

TEEC_Result write_to_keymaster(uint8_t *filename,
			       uint32_t filename_size,
			       uint8_t *data,
			       uint32_t data_size)
{
	TEEC_Result TeecResult;
	TEEC_Context TeecContext;
	TEEC_Session TeecSession;
	uint32_t ErrorOrigin;

	TEEC_UUID tempuuid = { 0x1b484ea5,
			       0x698b,
			       0x4142,
			       { 0x82, 0xb8, 0x3a,
				 0xcf, 0x16, 0xe9,
				 0x9e, 0x2a } };

	TEEC_UUID *TeecUuid = &tempuuid;
	TEEC_Operation TeecOperation = {0};
	struct blk_desc *dev_desc;

	dev_desc = rockchip_get_bootdev();
	if (!dev_desc) {
		printf("%s: dev_desc is NULL!\n", __func__);
		return -TEEC_ERROR_GENERIC;
	}

	debug("write_to_keymaster\n");
	OpteeClientApiLibInitialize();

	TeecResult = TEEC_InitializeContext(NULL, &TeecContext);

	TeecOperation.paramTypes = TEEC_PARAM_TYPES(TEEC_VALUE_INPUT,
						    TEEC_NONE,
						    TEEC_NONE,
						    TEEC_NONE);

	/*0 nand or emmc "security" partition , 1 rpmb*/
	TeecOperation.params[0].value.a = (dev_desc->if_type == IF_TYPE_MMC)
					   ? 1 : 0;

#ifdef CONFIG_OPTEE_ALWAYS_USE_SECURITY_PARTITION
	TeecOperation.params[0].value.a = 0;
#endif

	TeecResult = TEEC_OpenSession(&TeecContext,
				      &TeecSession,
				      TeecUuid,
				      TEEC_LOGIN_PUBLIC,

	NULL, &TeecOperation, &ErrorOrigin);

	TEEC_SharedMemory SharedMem0 = {0};

	SharedMem0.size = filename_size;
	SharedMem0.flags = 0;

	TeecResult = TEEC_AllocateSharedMemory(&TeecContext, &SharedMem0);

	memcpy(SharedMem0.buffer, filename, SharedMem0.size);

	TEEC_SharedMemory SharedMem1 = {0};

	SharedMem1.size = data_size;
	SharedMem1.flags = 0;

	TeecResult = TEEC_AllocateSharedMemory(&TeecContext, &SharedMem1);

	memcpy(SharedMem1.buffer, data, SharedMem1.size);

	TeecOperation.params[0].tmpref.buffer = SharedMem0.buffer;
	TeecOperation.params[0].tmpref.size = SharedMem0.size;

	TeecOperation.params[1].tmpref.buffer = SharedMem1.buffer;
	TeecOperation.params[1].tmpref.size = SharedMem1.size;

	TeecOperation.paramTypes = TEEC_PARAM_TYPES(TEEC_MEMREF_TEMP_INPUT,
						    TEEC_MEMREF_TEMP_INOUT,
						    TEEC_NONE,
						    TEEC_NONE);

	TeecResult = TEEC_InvokeCommand(&TeecSession,
					1,
					&TeecOperation,
					&ErrorOrigin);

	TEEC_ReleaseSharedMemory(&SharedMem0);
	TEEC_ReleaseSharedMemory(&SharedMem1);
	TEEC_CloseSession(&TeecSession);
	TEEC_FinalizeContext(&TeecContext);
	debug("write_to_keymaster end\n");
	debug("TeecResult %x\n", TeecResult);

	return TeecResult;
}

TEEC_Result trusty_write_oem_unlock(uint8_t unlock)
{
	char *file = "oem.unlock";
	TEEC_Result ret;

	ret = write_to_keymaster((uint8_t *)file,
				 strlen(file),
				 (uint8_t *)&unlock,
				 1);
	return ret;
}

TEEC_Result trusty_read_oem_unlock(uint8_t *unlock)
{
	char *file = "oem.unlock";
	TEEC_Result ret;

	ret = read_from_keymaster((uint8_t *)file,
				   strlen(file),
				   unlock,
				   1);

	if (ret == TEE_ERROR_ITEM_NOT_FOUND) {
		debug("init oem unlock status 0");
		ret = trusty_write_oem_unlock(0);
	}

	return ret;
}
