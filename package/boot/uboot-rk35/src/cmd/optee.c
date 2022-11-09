/* SPDX-License-Identifier:     GPL-2.0+
 *
 * Copyright 2019, Rockchip Electronics Co., Ltd
 *
 */

#include <common.h>
#include <optee_include/OpteeClientApiLib.h>
#include <optee_include/tee_client_api.h>
#include <optee_include/tee_api_defines.h>
#include <boot_rkimg.h>
#include <stdlib.h>

int test_secure_storage_default(void)
{
	TEEC_Result TeecResult;
	TEEC_Context TeecContext;
	TEEC_Session TeecSession;
	uint32_t ErrorOrigin;
	TEEC_UUID tempuuid = { 0x1b484ea5, 0x698b, 0x4142,
		{ 0x82, 0xb8, 0x3a, 0xcf, 0x16, 0xe9, 0x9e, 0x2a } };
	TEEC_UUID *TeecUuid = &tempuuid;
	TEEC_Operation TeecOperation = {0};
	struct blk_desc *dev_desc;

	dev_desc = rockchip_get_bootdev();
	if (!dev_desc) {
		printf("%s: dev_desc is NULL!\n", __func__);
		return -1;
	}

	debug("%s start\n", __func__);
	TeecResult = OpteeClientApiLibInitialize();
	if (TeecResult != TEEC_SUCCESS)
		return -1;

	TeecResult = TEEC_InitializeContext(NULL, &TeecContext);
	if (TeecResult != TEEC_SUCCESS)
		return -1;

	TeecOperation.paramTypes = TEEC_PARAM_TYPES(TEEC_VALUE_INPUT,
						    TEEC_NONE,
						    TEEC_NONE,
						    TEEC_NONE);
	/*0 nand or emmc "security" partition , 1 rpmb*/
	if (dev_desc->if_type == IF_TYPE_MMC && dev_desc->devnum == 0)
		TeecOperation.params[0].value.a = 1;
	else
		TeecOperation.params[0].value.a = 0;

	TeecResult = TEEC_OpenSession(&TeecContext,
				      &TeecSession,
				      TeecUuid,
				      TEEC_LOGIN_PUBLIC,
				      NULL,
				      &TeecOperation,
				      &ErrorOrigin);
	if (TeecResult != TEEC_SUCCESS) {
		printf("%s TEEC_OpenSession fail!\n", __func__);
		return -1;
	}

	TEEC_SharedMemory SharedMem0 = {0};

	SharedMem0.size = sizeof("filename_test_secure_storage_default");
	SharedMem0.flags = 0;

	TeecResult = TEEC_AllocateSharedMemory(&TeecContext, &SharedMem0);
	if (TeecResult != TEEC_SUCCESS) {
		printf("%s TEEC_AllocateSharedMemory fail!\n", __func__);
		return -1;
	}

	memcpy(SharedMem0.buffer,
	       "filename_test_secure_storage_default",
	       SharedMem0.size);

	TEEC_SharedMemory SharedMem1 = {0};

	SharedMem1.size = 1024 * 8;
	SharedMem1.flags = 0;

	TeecResult = TEEC_AllocateSharedMemory(&TeecContext, &SharedMem1);
	if (TeecResult != TEEC_SUCCESS) {
		printf("%s TEEC_AllocateSharedMemory fail!\n", __func__);
		return -1;
	}

	memset(SharedMem1.buffer, 'a', SharedMem1.size);

	TeecOperation.params[0].tmpref.buffer = SharedMem0.buffer;
	TeecOperation.params[0].tmpref.size = SharedMem0.size;

	TeecOperation.params[1].tmpref.buffer = SharedMem1.buffer;
	TeecOperation.params[1].tmpref.size = SharedMem1.size;

	TeecOperation.paramTypes = TEEC_PARAM_TYPES(TEEC_MEMREF_TEMP_INPUT,
						    TEEC_MEMREF_TEMP_INOUT,
						    TEEC_NONE,
						    TEEC_NONE);

	TeecResult = TEEC_InvokeCommand(&TeecSession,//write data
					1,
					&TeecOperation,
					&ErrorOrigin);
	if (TeecResult != TEEC_SUCCESS) {
		printf("%s TEEC_InvokeCommand fail!\n", __func__);
		return -1;
	}

	TEEC_SharedMemory SharedMem2 = {0};

	SharedMem2.size = 1024 * 8;
	SharedMem2.flags = 0;

	TeecResult = TEEC_AllocateSharedMemory(&TeecContext, &SharedMem2);
	if (TeecResult != TEEC_SUCCESS) {
		printf("%s TEEC_AllocateSharedMemory fail!\n", __func__);
		return -1;
	}

	TeecOperation.params[0].tmpref.buffer = SharedMem0.buffer;
	TeecOperation.params[0].tmpref.size = SharedMem0.size;

	TeecOperation.params[1].tmpref.buffer = SharedMem2.buffer;
	TeecOperation.params[1].tmpref.size = SharedMem2.size;

	TeecResult = TEEC_InvokeCommand(&TeecSession,//read data
					0,
					&TeecOperation,
					&ErrorOrigin);
	if (TeecResult != TEEC_SUCCESS) {
		printf("%s TEEC_InvokeCommand fail!\n", __func__);
		return -1;
	}
	if (memcmp(SharedMem1.buffer, SharedMem2.buffer,
	    SharedMem1.size) != 0) {
		printf("error! %s read not equal to write!\n", __func__);
		return -1;
	}

	TEEC_ReleaseSharedMemory(&SharedMem0);
	TEEC_ReleaseSharedMemory(&SharedMem1);
	TEEC_ReleaseSharedMemory(&SharedMem2);

	TEEC_CloseSession(&TeecSession);

	TEEC_FinalizeContext(&TeecContext);

	debug("%s end\n", __func__);
	return 0;
}

int test_secure_storage_security_partition(void)
{
	TEEC_Result TeecResult;
	TEEC_Context TeecContext;
	TEEC_Session TeecSession;
	uint32_t ErrorOrigin;
	TEEC_UUID tempuuid = { 0x1b484ea5, 0x698b, 0x4142,
		{ 0x82, 0xb8, 0x3a, 0xcf, 0x16, 0xe9, 0x9e, 0x2a } };
	TEEC_UUID *TeecUuid = &tempuuid;
	TEEC_Operation TeecOperation = {0};
	struct blk_desc *dev_desc;

	dev_desc = rockchip_get_bootdev();
	if (!dev_desc) {
		printf("%s: dev_desc is NULL!\n", __func__);
		return -1;
	}

	debug("%s start\n", __func__);
	TeecResult = OpteeClientApiLibInitialize();
	if (TeecResult != TEEC_SUCCESS)
		return -1;

	TeecResult = TEEC_InitializeContext(NULL, &TeecContext);
	if (TeecResult != TEEC_SUCCESS)
		return -1;

	TeecOperation.paramTypes = TEEC_PARAM_TYPES(TEEC_VALUE_INPUT,
						    TEEC_NONE,
						    TEEC_NONE,
						    TEEC_NONE);
	/*0 nand or emmc "security" partition , 1 rpmb*/
	TeecOperation.params[0].value.a = 0;//use security partition

	TeecResult = TEEC_OpenSession(&TeecContext,
				      &TeecSession,
				      TeecUuid,
				      TEEC_LOGIN_PUBLIC,
				      NULL,
				      &TeecOperation,
				      &ErrorOrigin);
	if (TeecResult != TEEC_SUCCESS) {
		printf("%s TEEC_OpenSession fail!\n", __func__);
		return -1;
	}

	TEEC_SharedMemory SharedMem0 = {0};

	SharedMem0.size = sizeof("filename_test_secure_storage_security_partition");
	SharedMem0.flags = 0;

	TeecResult = TEEC_AllocateSharedMemory(&TeecContext, &SharedMem0);
	if (TeecResult != TEEC_SUCCESS) {
		printf("%s TEEC_AllocateSharedMemory fail!\n", __func__);
		return -1;
	}

	memcpy(SharedMem0.buffer,
	       "filename_test_secure_storage_security_partition",
	       SharedMem0.size);

	TEEC_SharedMemory SharedMem1 = {0};

	SharedMem1.size = 1024 * 8;
	SharedMem1.flags = 0;

	TeecResult = TEEC_AllocateSharedMemory(&TeecContext, &SharedMem1);
	if (TeecResult != TEEC_SUCCESS) {
		printf("%s TEEC_AllocateSharedMemory fail!\n", __func__);
		return -1;
	}

	memset(SharedMem1.buffer, 'b', SharedMem1.size);

	TeecOperation.params[0].tmpref.buffer = SharedMem0.buffer;
	TeecOperation.params[0].tmpref.size = SharedMem0.size;

	TeecOperation.params[1].tmpref.buffer = SharedMem1.buffer;
	TeecOperation.params[1].tmpref.size = SharedMem1.size;

	TeecOperation.paramTypes = TEEC_PARAM_TYPES(TEEC_MEMREF_TEMP_INPUT,
						    TEEC_MEMREF_TEMP_INOUT,
						    TEEC_NONE,
						    TEEC_NONE);

	TeecResult = TEEC_InvokeCommand(&TeecSession,//write data
					1,
					&TeecOperation,
					&ErrorOrigin);
	if (TeecResult != TEEC_SUCCESS) {
		printf("%s TEEC_InvokeCommand fail!\n", __func__);
		return -1;
	}

	TEEC_SharedMemory SharedMem2 = {0};

	SharedMem2.size = 1024 * 8;
	SharedMem2.flags = 0;

	TeecResult = TEEC_AllocateSharedMemory(&TeecContext, &SharedMem2);
	if (TeecResult != TEEC_SUCCESS) {
		printf("%s TEEC_AllocateSharedMemory fail!\n", __func__);
		return -1;
	}

	TeecOperation.params[0].tmpref.buffer = SharedMem0.buffer;
	TeecOperation.params[0].tmpref.size = SharedMem0.size;

	TeecOperation.params[1].tmpref.buffer = SharedMem2.buffer;
	TeecOperation.params[1].tmpref.size = SharedMem2.size;

	TeecResult = TEEC_InvokeCommand(&TeecSession,//read data
					0,
					&TeecOperation,
					&ErrorOrigin);
	if (TeecResult != TEEC_SUCCESS) {
		printf("%s TEEC_InvokeCommand fail!\n", __func__);
		return -1;
	}
	if (memcmp(SharedMem1.buffer, SharedMem2.buffer,
	    SharedMem1.size) != 0) {
		printf("error! %s read not equal to write!\n", __func__);
		return -1;
	}

	TEEC_ReleaseSharedMemory(&SharedMem0);
	TEEC_ReleaseSharedMemory(&SharedMem1);
	TEEC_ReleaseSharedMemory(&SharedMem2);

	TEEC_CloseSession(&TeecSession);

	TEEC_FinalizeContext(&TeecContext);

	debug("%s end\n", __func__);
	return 0;
}
