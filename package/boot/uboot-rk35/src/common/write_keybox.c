// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (c) 2019 Fuzhou Rockchip Electronics Co., Ltd
 */

#include <common.h>
#include <boot_rkimg.h>
#include <stdlib.h>
#include <attestation_key.h>
#include <write_keybox.h>
#include <keymaster.h>
#include <optee_include/OpteeClientApiLib.h>
#include <optee_include/tee_client_api.h>
#include <optee_include/tee_api_defines.h>

#define STORAGE_CMD_WRITE	6
#define	SIZE_OF_TAG		4
#define	BOOT_FROM_EMMC	(1 << 1)
#define	WIDEVINE_TAG	"KBOX"
#define	ATTESTATION_TAG	"ATTE"
#define PLAYREADY30_TAG	"SL30"

TEEC_Result write_to_security_storage(uint8_t is_use_rpmb,
				      uint8_t *filename,
				      uint32_t filename_size,
				      uint8_t *data,
				      uint32_t data_size)
{
	TEEC_Result TeecResult;
	TEEC_Context TeecContext;
	TEEC_Session TeecSession;
	TEEC_SharedMemory SharedMem0 = {0};
	TEEC_SharedMemory SharedMem1 = {0};
	uint32_t ErrorOrigin;

	TEEC_UUID tempuuid = { 0x1b484ea5,
			       0x698b,
			       0x4142,
			       { 0x82, 0xb8, 0x3a,
				 0xcf, 0x16, 0xe9,
				 0x9e, 0x2a } };

	TEEC_UUID *TeecUuid = &tempuuid;
	TEEC_Operation TeecOperation = {0};

	TeecResult = OpteeClientApiLibInitialize();
	if (TeecResult) {
		printf("OpteeClientApiLibInitialize fail\n");
		return TeecResult;
	}
	TeecResult = TEEC_InitializeContext(NULL, &TeecContext);
	if (TeecResult) {
		printf("TEEC_InitializeContext fail\n");
		return TeecResult;
	}
	TeecOperation.paramTypes = TEEC_PARAM_TYPES(TEEC_VALUE_INPUT,
						    TEEC_NONE,
						    TEEC_NONE,
						    TEEC_NONE);

	/*0 nand or emmc "security" partition , 1 rpmb*/
	TeecOperation.params[0].value.a = is_use_rpmb;

	TeecResult = TEEC_OpenSession(&TeecContext,
				      &TeecSession,
				      TeecUuid,
				      TEEC_LOGIN_PUBLIC,
				      NULL, &TeecOperation,
				      &ErrorOrigin);
	if (TeecResult) {
		printf("TEEC_OpenSession fail\n");
		return TeecResult;
	}

	SharedMem0.size = filename_size;
	SharedMem0.flags = 0;
	TeecResult = TEEC_AllocateSharedMemory(&TeecContext, &SharedMem0);
	if (TeecResult) {
		printf("TEEC_AllocateSharedMemory fail\n");
		return TeecResult;
	}
	memcpy(SharedMem0.buffer, filename, SharedMem0.size);

	SharedMem1.size = data_size;
	SharedMem1.flags = 0;
	TeecResult = TEEC_AllocateSharedMemory(&TeecContext, &SharedMem1);
	if (TeecResult) {
		printf("TEEC_AllocateSharedMemory fail\n");
		return TeecResult;
	}
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
	if (TeecResult) {
		printf("TEEC_InvokeCommand fail\n");
		return TeecResult;
	}
	TEEC_ReleaseSharedMemory(&SharedMem0);
	TEEC_ReleaseSharedMemory(&SharedMem1);
	TEEC_CloseSession(&TeecSession);
	TEEC_FinalizeContext(&TeecContext);
	debug("TeecResult %x\n", TeecResult);

	return TeecResult;
}

uint32_t rk_send_keybox_to_ta(uint8_t *filename, uint32_t filename_size,
			      TEEC_UUID uuid,
			      uint8_t *key, uint32_t key_size,
			      uint8_t *data, uint32_t data_size)
{
	uint32_t ErrorOrigin;
	TEEC_Result TeecResult;
	TEEC_Context TeecContext;
	TEEC_Session TeecSession;
	TEEC_UUID *TeecUuid = &uuid;
	TEEC_Operation TeecOperation = {0};
	TEEC_SharedMemory SharedMem0 = {0};
	TEEC_SharedMemory SharedMem1 = {0};
	TEEC_SharedMemory SharedMem2 = {0};
	struct blk_desc *dev_desc;

	dev_desc = rockchip_get_bootdev();
	if (!dev_desc) {
		printf("%s: dev_desc is NULL!\n", __func__);
		return -TEEC_ERROR_GENERIC;
	}

	TeecResult = OpteeClientApiLibInitialize();
	if (TeecResult != TEEC_SUCCESS)
		return TeecResult;
	TeecResult = TEEC_InitializeContext(NULL, &TeecContext);
	if (TeecResult != TEEC_SUCCESS)
		return TeecResult;
	TeecOperation.paramTypes = TEEC_PARAM_TYPES(TEEC_VALUE_INPUT,
						    TEEC_NONE,
						    TEEC_NONE,
						    TEEC_NONE);

	/* 0 nand or emmc "security" partition , 1 rpmb */
	TeecOperation.params[0].value.a =
		(dev_desc->if_type == IF_TYPE_MMC) ? 1 : 0;
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
	if (TeecResult != TEEC_SUCCESS)
		return TeecResult;

	SharedMem0.size = filename_size;
	SharedMem0.flags = 0;
	TeecResult = TEEC_AllocateSharedMemory(&TeecContext, &SharedMem0);
	if (TeecResult != TEEC_SUCCESS)
		return TeecResult;
	memcpy(SharedMem0.buffer, filename, SharedMem0.size);

	SharedMem1.size = key_size;
	SharedMem1.flags = 0;
	TeecResult = TEEC_AllocateSharedMemory(&TeecContext, &SharedMem1);
	if (TeecResult != TEEC_SUCCESS)
		return TeecResult;
	memcpy(SharedMem1.buffer, key, SharedMem1.size);

	SharedMem2.size = data_size;
	SharedMem2.flags = 0;
	TeecResult = TEEC_AllocateSharedMemory(&TeecContext, &SharedMem2);
	if (TeecResult != TEEC_SUCCESS)
		return TeecResult;
	memcpy(SharedMem2.buffer, data, SharedMem2.size);

	TeecOperation.params[0].tmpref.buffer = SharedMem0.buffer;
	TeecOperation.params[0].tmpref.size = SharedMem0.size;
	TeecOperation.params[1].tmpref.buffer = SharedMem1.buffer;
	TeecOperation.params[1].tmpref.size = SharedMem1.size;
	TeecOperation.params[2].tmpref.buffer = SharedMem2.buffer;
	TeecOperation.params[2].tmpref.size = SharedMem2.size;

	TeecOperation.paramTypes = TEEC_PARAM_TYPES(TEEC_MEMREF_TEMP_INPUT,
						    TEEC_MEMREF_TEMP_INPUT,
						    TEEC_MEMREF_TEMP_INOUT,
						    TEEC_NONE);

	printf("write keybox to secure storage\n");
	TeecResult = TEEC_InvokeCommand(&TeecSession,
					STORAGE_CMD_WRITE,
					&TeecOperation,
					&ErrorOrigin);
	if (TeecResult != TEEC_SUCCESS)
		printf("send data to TA failed with code 0x%x\n", TeecResult);
	else
		printf("send data to TA success with code 0x%x\n", TeecResult);

	TEEC_ReleaseSharedMemory(&SharedMem0);
	TEEC_ReleaseSharedMemory(&SharedMem1);
	TEEC_ReleaseSharedMemory(&SharedMem2);

	TEEC_CloseSession(&TeecSession);
	TEEC_FinalizeContext(&TeecContext);

	return TeecResult;
}

uint32_t write_keybox_to_secure_storage(uint8_t *received_data, uint32_t len)
{
	uint8_t *widevine_data;
	uint8_t *attestation_data;
	uint8_t *playready_sl30_data;
	uint32_t key_size;
	uint32_t data_size;
	int rc = 0;
	TEEC_Result ret;
	struct blk_desc *dev_desc;
	uint8_t is_use_rpmb;

	dev_desc = rockchip_get_bootdev();
	if (!dev_desc) {
		printf("%s: dev_desc is NULL!\n", __func__);
		return -EIO;
	}
	is_use_rpmb = (dev_desc->if_type == IF_TYPE_MMC) ? 1 : 0;
#ifdef CONFIG_OPTEE_ALWAYS_USE_SECURITY_PARTITION
	is_use_rpmb = 0;
#endif
	if (is_use_rpmb)
		printf("I will write key to rpmb\n");
	else
		printf("I will write key to security partition\n");

	rc = write_to_security_storage(0, (uint8_t *)"security_partition",
				       sizeof("security_partition"),
				       &is_use_rpmb, sizeof(is_use_rpmb));
	if (rc)
		return -EIO;
	widevine_data = (uint8_t *)new_strstr((char *)received_data,
					      WIDEVINE_TAG, len);
	attestation_data = (uint8_t *)new_strstr((char *)received_data,
						 ATTESTATION_TAG, len);
	playready_sl30_data = (uint8_t *)new_strstr((char *)received_data,
						    PLAYREADY30_TAG, len);
	if (widevine_data) {
		/* widevine keybox */
		TEEC_UUID widevine_uuid = { 0x1b484ea5, 0x698b, 0x4142,
			{ 0x82, 0xb8, 0x3a, 0xcf, 0x16, 0xe9, 0x9e, 0x2a } };

		key_size = *(widevine_data + SIZE_OF_TAG);
		data_size = *(widevine_data + SIZE_OF_TAG + sizeof(key_size));

		ret = rk_send_keybox_to_ta((uint8_t *)"widevine_keybox",
					   sizeof("widevine_keybox"),
					   widevine_uuid,
					   widevine_data + SIZE_OF_TAG +
					   sizeof(key_size) + sizeof(data_size),
					   key_size,
					   widevine_data + 12 + key_size,
					   data_size);
		if (ret == TEEC_SUCCESS) {
			rc = 0;
			printf("write widevine keybox to secure storage success\n");
		} else {
			rc = -EIO;
			printf("write widevine keybox to secure storage fail\n");
		}
	} else if (attestation_data) {
		/* attestation key */
		atap_result ret;

		ret = write_attestation_key_to_secure_storage(attestation_data,
							      len);
		if (ret == ATAP_RESULT_OK) {
			rc = 0;
			printf("write attestation key to secure storage success\n");
		} else {
			rc = -EIO;
			printf("write attestation key to secure storage fail\n");
		}
	} else if (playready_sl30_data) {
		/* PlayReady SL3000 root key */
		uint32_t ret;

		data_size = *(playready_sl30_data + SIZE_OF_TAG);
		ret = write_to_security_storage(is_use_rpmb,
						(uint8_t *)"PlayReady_SL3000",
						sizeof("PlayReady_SL3000"),
						playready_sl30_data +
						SIZE_OF_TAG +sizeof(data_size),
						data_size);
		if (ret == TEEC_SUCCESS) {
			rc = 0;
			printf("write PlayReady SL3000 root key to secure storage success\n");
		} else {
			rc = -EIO;
			printf("write PlayReady SL3000 root key to secure storage fail\n");
		}
	}

	/* write all data to secure storage for readback check */
	if (!rc) {
		uint32_t ret;
		uint8_t *raw_data = malloc(len + sizeof(uint32_t));

		/* add raw_data_len(4 byte) in begin of raw_data */
		memcpy(raw_data, &len, sizeof(uint32_t));
		memcpy((raw_data + sizeof(uint32_t)), received_data, len);

		ret = write_to_security_storage(is_use_rpmb,
						(uint8_t *)"raw_data",
						sizeof("raw_data"),
						raw_data,
						len + sizeof(uint32_t));
		if (ret == TEEC_SUCCESS)
			rc = 0;
		else
			rc = -EIO;
		free(raw_data);
	}
	return rc;
}

uint32_t read_raw_data_from_secure_storage(uint8_t *data, uint32_t data_size)
{
	uint32_t rc;
	uint32_t key_size;
	uint8_t *read_data = malloc(1024 * 40);

	rc = read_from_keymaster((uint8_t *)"raw_data", sizeof("raw_data"),
				 read_data, data_size);
	if (rc != TEEC_SUCCESS)
		return 0;

	memcpy(&key_size, read_data, sizeof(uint32_t));
	memcpy(data, read_data + sizeof(uint32_t), key_size);
	rc = key_size;
	free(read_data);

	return rc;
}

char *new_strstr(const char *s1, const char *s2, uint32_t l1)
{
	uint32_t l2;

	l2 = strlen(s2);
	if (!l2)
		return (char *)s1;
	while (l1 >= l2) {
		l1--;
		if (!memcmp(s1, s2, l2))
			return (char *)s1;
		s1++;
	}
	return NULL;
}
