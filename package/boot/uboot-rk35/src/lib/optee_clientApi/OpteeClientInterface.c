/*
 * Copyright 2017, Rockchip Electronics Co., Ltd
 * hisping lin, <hisping.lin@rock-chips.com>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <common.h>
#include <optee_include/OpteeClientInterface.h>
#include <optee_include/OpteeClientApiLib.h>
#include <optee_include/tee_client_api.h>
#include <optee_include/tee_api_defines.h>
#include <boot_rkimg.h>
#include <stdlib.h>
#include <attestation_key.h>

#define	BOOT_FROM_EMMC	(1 << 1)
#define STORAGE_CMD_READ_ATTRIBUTE_HASH		0
#define STORAGE_CMD_WRITE_ATTRIBUTE_HASH	1
#define STORAGE_CMD_UBOOT_END_OTP		2
#define STORAGE_CMD_READ_VBOOTKEY_HASH		3
#define STORAGE_CMD_WRITE_VBOOTKEY_HASH		4
#define STORAGE_CMD_READ_ENABLE_FLAG		5
#define STORAGE_CMD_WRITE_TA_ENCRYPTION_KEY	9
#define STORAGE_CMD_CHECK_SECURITY_LEVEL_FLAG	10
#define STORAGE_CMD_WRITE_OEM_HUK		11
#define STORAGE_CMD_WRITE_OEM_NS_OTP		12
#define STORAGE_CMD_READ_OEM_NS_OTP		13
#define STORAGE_CMD_WRITE_OEM_OTP_KEY		14
#define STORAGE_CMD_SET_OEM_HR_OTP_READ_LOCK	15
#define STORAGE_CMD_OEM_OTP_KEY_IS_WRITTEN	16

#define CRYPTO_SERVICE_CMD_OEM_OTP_KEY_PHYS_CIPHER	0x00000002

#define RK_CRYPTO_SERVICE_UUID	{ 0x0cacdb5d, 0x4fea, 0x466c, \
		{ 0x97, 0x16, 0x3d, 0x54, 0x16, 0x52, 0x83, 0x0f } }

static uint8_t b2hs_add_base(uint8_t in)
{
	if (in > 9)
		return in + 55;
	else
		return in + 48;
}

static uint32_t b2hs(uint8_t *b, uint8_t *hs, uint32_t blen, uint32_t hslen)
{
	uint32_t i = 0;

	if (blen * 2 + 1 > hslen)
		return 0;

	for (; i < blen; i++) {
		hs[i * 2 + 1] = b2hs_add_base(b[i] & 0xf);
		hs[i * 2] = b2hs_add_base(b[i] >> 4);
	}
	hs[blen * 2] = 0;

	return blen * 2;
}

static void crypto_flush_cacheline(uint32_t addr, uint32_t size)
{
	ulong alignment = CONFIG_SYS_CACHELINE_SIZE;
	ulong aligned_input, aligned_len;

	if (!addr || !size)
		return;

	/* Must flush dcache before crypto DMA fetch data region */
	aligned_input = round_down(addr, alignment);
	aligned_len = round_up(size + (addr - aligned_input), alignment);
	flush_cache(aligned_input, aligned_len);
}

static uint32_t trusty_base_write_security_data(char *filename,
						uint32_t filename_size,
						uint8_t *data,
						uint32_t data_size)
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
	/*0 nand or emmc "security" partition , 1 rpmb*/
	if (dev_desc->if_type == IF_TYPE_MMC && dev_desc->devnum == 0)
		TeecOperation.params[0].value.a = 1;
	else
		TeecOperation.params[0].value.a = 0;
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

	TEEC_SharedMemory SharedMem0 = {0};

	SharedMem0.size = filename_size;
	SharedMem0.flags = 0;

	TeecResult = TEEC_AllocateSharedMemory(&TeecContext, &SharedMem0);
	if (TeecResult != TEEC_SUCCESS)
		goto exit;

	memcpy(SharedMem0.buffer, filename, SharedMem0.size);

	TEEC_SharedMemory SharedMem1 = {0};

	SharedMem1.size = data_size;
	SharedMem1.flags = 0;

	TeecResult = TEEC_AllocateSharedMemory(&TeecContext, &SharedMem1);
	if (TeecResult != TEEC_SUCCESS)
		goto exit;

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
	if (TeecResult != TEEC_SUCCESS)
		goto exit;
exit:
	TEEC_ReleaseSharedMemory(&SharedMem0);
	TEEC_ReleaseSharedMemory(&SharedMem1);
	TEEC_CloseSession(&TeecSession);
	TEEC_FinalizeContext(&TeecContext);

	return TeecResult;
}

static uint32_t trusty_base_read_security_data(char *filename,
					       uint32_t filename_size,
					       uint8_t *data,
					       uint32_t data_size)
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
	/*0 nand or emmc "security" partition , 1 rpmb*/
	if (dev_desc->if_type == IF_TYPE_MMC && dev_desc->devnum == 0)
		TeecOperation.params[0].value.a = 1;
	else
		TeecOperation.params[0].value.a = 0;
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

	TEEC_SharedMemory SharedMem0 = {0};

	SharedMem0.size = filename_size;
	SharedMem0.flags = 0;

	TeecResult = TEEC_AllocateSharedMemory(&TeecContext, &SharedMem0);
	if (TeecResult != TEEC_SUCCESS)
		goto exit;

	memcpy(SharedMem0.buffer, filename, SharedMem0.size);

	TEEC_SharedMemory SharedMem1 = {0};

	SharedMem1.size = data_size;
	SharedMem1.flags = 0;

	TeecResult = TEEC_AllocateSharedMemory(&TeecContext, &SharedMem1);
	if (TeecResult != TEEC_SUCCESS)
		goto exit;

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
exit:
	TEEC_ReleaseSharedMemory(&SharedMem0);
	TEEC_ReleaseSharedMemory(&SharedMem1);
	TEEC_CloseSession(&TeecSession);
	TEEC_FinalizeContext(&TeecContext);

	return TeecResult;
}

static uint32_t trusty_base_end_security_data(void)
{
	TEEC_Result TeecResult;
	TEEC_Context TeecContext;
	TEEC_Session TeecSession;
	uint32_t ErrorOrigin;
	TEEC_UUID  tempuuid = { 0x1b484ea5, 0x698b, 0x4142,
		{ 0x82, 0xb8, 0x3a, 0xcf, 0x16, 0xe9, 0x9e, 0x2a } };
	TEEC_UUID *TeecUuid = &tempuuid;
	TEEC_Operation TeecOperation = {0};

	TeecResult = OpteeClientApiLibInitialize();
	if (TeecResult != TEEC_SUCCESS)
		return TeecResult;

	TeecResult = TEEC_InitializeContext(NULL, &TeecContext);
	if (TeecResult != TEEC_SUCCESS)
		return TeecResult;

	TeecResult = TEEC_OpenSession(&TeecContext,
				&TeecSession,
				TeecUuid,
				TEEC_LOGIN_PUBLIC,
				NULL,
				NULL,
				&ErrorOrigin);
	if (TeecResult != TEEC_SUCCESS)
		return TeecResult;

	TeecOperation.paramTypes = TEEC_PARAM_TYPES(TEEC_NONE,
						    TEEC_NONE,
						    TEEC_NONE,
						    TEEC_NONE);

	TeecResult = TEEC_InvokeCommand(&TeecSession,
					2,
					&TeecOperation,
					&ErrorOrigin);
	if (TeecResult != TEEC_SUCCESS)
		goto exit;
exit:
	TEEC_CloseSession(&TeecSession);
	TEEC_FinalizeContext(&TeecContext);

	return TeecResult;
}

uint32_t trusty_read_rollback_index(uint32_t slot, uint64_t *value)
{
	char hs[9];

	b2hs((uint8_t *)&slot, (uint8_t *)hs, 4, 9);

	return trusty_base_read_security_data(hs, 8, (uint8_t *)value, 8);
}

uint32_t trusty_write_rollback_index(uint32_t slot, uint64_t value)
{
	char hs[9];

	b2hs((uint8_t *)&slot, (uint8_t *)hs, 4, 9);

	return trusty_base_write_security_data(hs, 8, (uint8_t *)&value, 8);
}

uint32_t trusty_read_permanent_attributes(uint8_t *attributes, uint32_t size)
{
	return trusty_base_read_security_data("attributes",
		sizeof("attributes"), attributes, size);
}

uint32_t trusty_write_permanent_attributes(uint8_t *attributes, uint32_t size)
{
	return trusty_base_write_security_data("attributes",
		sizeof("attributes"), attributes, size);
}

uint32_t trusty_read_permanent_attributes_flag(uint8_t *attributes)
{
	return trusty_base_read_security_data("attributes_flag",
		sizeof("attributes_flag"), attributes, 1);
}

uint32_t trusty_write_permanent_attributes_flag(uint8_t attributes)
{
	return trusty_base_write_security_data("attributes_flag",
		sizeof("attributes_flag"), &attributes, 1);
}

uint32_t trusty_read_permanent_attributes_cer(uint8_t *attributes,
					      uint32_t size)
{
	return trusty_base_read_security_data("rsacer",
		sizeof("rsacer"), attributes, size);
}

uint32_t trusty_write_permanent_attributes_cer(uint8_t *attributes,
					       uint32_t size)
{
	return trusty_base_write_security_data("rsacer",
		sizeof("rsacer"), attributes, size);
}

uint32_t trusty_read_lock_state(uint8_t *lock_state)
{
	return trusty_base_read_security_data("lock_state",
		sizeof("lock_state"), lock_state, 1);
}

uint32_t trusty_write_lock_state(uint8_t lock_state)
{
	return trusty_base_write_security_data("lock_state",
		sizeof("lock_state"), &lock_state, 1);
}

uint32_t trusty_read_flash_lock_state(uint8_t *flash_lock_state)
{
	return trusty_base_read_security_data("flash_lock_state",
		sizeof("flash_lock_state"), flash_lock_state, 1);
}

uint32_t trusty_write_flash_lock_state(uint8_t flash_lock_state)
{
	return trusty_base_write_security_data("flash_lock_state",
		sizeof("flash_lock_state"), &flash_lock_state, 1);
}

static uint32_t trusty_base_end_efuse_or_otp(void)
{
	TEEC_Result TeecResult;
	TEEC_Context TeecContext;
	TEEC_Session TeecSession;
	uint32_t ErrorOrigin;
	TEEC_UUID tempuuid = { 0x2d26d8a8, 0x5134, 0x4dd8,
			{ 0xb3, 0x2f, 0xb3, 0x4b, 0xce, 0xeb, 0xc4, 0x71 } };

	TEEC_UUID *TeecUuid = &tempuuid;
	TEEC_Operation TeecOperation = {0};

	TeecResult = OpteeClientApiLibInitialize();
	if (TeecResult != TEEC_SUCCESS)
		return TeecResult;

	TeecResult = TEEC_InitializeContext(NULL, &TeecContext);
	if (TeecResult != TEEC_SUCCESS)
		return TeecResult;

	TeecResult = TEEC_OpenSession(&TeecContext,
				      &TeecSession,
				      TeecUuid,
				      TEEC_LOGIN_PUBLIC,
				      NULL,
				      NULL,
				      &ErrorOrigin);
	if (TeecResult != TEEC_SUCCESS)
		return TeecResult;

	TeecOperation.paramTypes = TEEC_PARAM_TYPES(TEEC_NONE,
						    TEEC_NONE,
						    TEEC_NONE,
						    TEEC_NONE);

	TeecResult = TEEC_InvokeCommand(&TeecSession,
					STORAGE_CMD_UBOOT_END_OTP,
					&TeecOperation,
					&ErrorOrigin);
	if (TeecResult != TEEC_SUCCESS)
		goto exit;
exit:
	TEEC_CloseSession(&TeecSession);
	TEEC_FinalizeContext(&TeecContext);

	return TeecResult;
}

static uint32_t trusty_base_efuse_or_otp_operation(uint32_t cmd,
						   uint8_t is_write,
						   uint32_t *buf,
						   uint32_t length)
{
	TEEC_Result TeecResult;
	TEEC_Context TeecContext;
	TEEC_Session TeecSession;
	uint32_t ErrorOrigin;

	TEEC_UUID tempuuid = { 0x2d26d8a8, 0x5134, 0x4dd8,
			{ 0xb3, 0x2f, 0xb3, 0x4b, 0xce, 0xeb, 0xc4, 0x71 } };
	TEEC_UUID *TeecUuid = &tempuuid;
	TEEC_Operation TeecOperation = {0};

	TeecResult = OpteeClientApiLibInitialize();
	if (TeecResult != TEEC_SUCCESS)
		return TeecResult;

	TeecResult = TEEC_InitializeContext(NULL, &TeecContext);
	if (TeecResult != TEEC_SUCCESS)
		return TeecResult;

	TeecResult = TEEC_OpenSession(&TeecContext,
				&TeecSession,
				TeecUuid,
				TEEC_LOGIN_PUBLIC,
				NULL,
				NULL,
				&ErrorOrigin);
	if (TeecResult != TEEC_SUCCESS)
		return TeecResult;

	TEEC_SharedMemory SharedMem0 = {0};

	SharedMem0.size = length * sizeof(uint32_t);
	SharedMem0.flags = 0;

	TeecResult = TEEC_AllocateSharedMemory(&TeecContext, &SharedMem0);
	if (TeecResult != TEEC_SUCCESS)
		goto exit;

	TeecOperation.params[0].tmpref.buffer = SharedMem0.buffer;
	TeecOperation.params[0].tmpref.size = SharedMem0.size;

	if (is_write) {
		memcpy(SharedMem0.buffer, buf, SharedMem0.size);
		TeecOperation.paramTypes = TEEC_PARAM_TYPES(TEEC_MEMREF_TEMP_INPUT,
							    TEEC_NONE,
							    TEEC_NONE,
							    TEEC_NONE);

	} else {
		TeecOperation.paramTypes = TEEC_PARAM_TYPES(TEEC_MEMREF_TEMP_OUTPUT,
							    TEEC_NONE,
							    TEEC_NONE,
							    TEEC_NONE);
	}

	TeecResult = TEEC_InvokeCommand(&TeecSession,
					cmd,
					&TeecOperation,
					&ErrorOrigin);
	if (TeecResult != TEEC_SUCCESS)
		goto exit;

	if (!is_write)
		memcpy(buf, SharedMem0.buffer, SharedMem0.size);

exit:
	TEEC_ReleaseSharedMemory(&SharedMem0);
	TEEC_CloseSession(&TeecSession);
	TEEC_FinalizeContext(&TeecContext);

	return TeecResult;
}

uint32_t trusty_read_attribute_hash(uint32_t *buf, uint32_t length)
{
	return trusty_base_efuse_or_otp_operation(STORAGE_CMD_READ_ATTRIBUTE_HASH,
						  false, buf, length);
}

uint32_t trusty_write_attribute_hash(uint32_t *buf, uint32_t length)
{
	return trusty_base_efuse_or_otp_operation(STORAGE_CMD_WRITE_ATTRIBUTE_HASH,
						  true, buf, length);
}

uint32_t trusty_notify_optee_uboot_end(void)
{
	TEEC_Result res;

	res = trusty_base_end_security_data();
	res |= trusty_base_end_efuse_or_otp();
	return res;
}

uint32_t trusty_read_vbootkey_hash(uint32_t *buf, uint32_t length)
{
	return trusty_base_efuse_or_otp_operation(STORAGE_CMD_READ_VBOOTKEY_HASH,
						  false, buf, length);
}

uint32_t trusty_write_vbootkey_hash(uint32_t *buf, uint32_t length)
{
	return trusty_base_efuse_or_otp_operation(STORAGE_CMD_WRITE_VBOOTKEY_HASH,
						  true, buf, length);
}

uint32_t trusty_read_vbootkey_enable_flag(uint8_t *flag)
{
	uint32_t bootflag;
	TEEC_Result TeecResult;

	*flag = 0;

	TeecResult = trusty_base_efuse_or_otp_operation(STORAGE_CMD_READ_ENABLE_FLAG,
							false, &bootflag, 1);

	if (TeecResult == TEEC_SUCCESS) {
#if defined(CONFIG_ROCKCHIP_RK3288)
		if (bootflag == 0x00000001)
			*flag = 1;
#else
		if (bootflag == 0x000000FF)
			*flag = 1;
#endif
	}
	return TeecResult;
}

uint32_t trusty_write_ta_encryption_key(uint32_t *buf, uint32_t length)
{
	return trusty_base_efuse_or_otp_operation(STORAGE_CMD_WRITE_TA_ENCRYPTION_KEY,
						  true, buf, length);
}

uint32_t trusty_check_security_level_flag(uint8_t flag)
{
	uint32_t levelflag;

	levelflag = flag;
	return trusty_base_efuse_or_otp_operation(STORAGE_CMD_CHECK_SECURITY_LEVEL_FLAG,
						  true, &levelflag, 1);
}

uint32_t trusty_write_oem_huk(uint32_t *buf, uint32_t length)
{
	return trusty_base_efuse_or_otp_operation(STORAGE_CMD_WRITE_OEM_HUK,
						  true, buf, length);
}

void trusty_select_security_level(void)
{
#if (CONFIG_OPTEE_SECURITY_LEVEL > 0)
	TEEC_Result TeecResult;

	TeecResult = trusty_check_security_level_flag(CONFIG_OPTEE_SECURITY_LEVEL);
	if (TeecResult == TEE_ERROR_CANCEL) {
		run_command("download", 0);
		return;
	}

	if (TeecResult == TEEC_SUCCESS)
		debug("optee select security level success!");
	else
		panic("optee select security level fail!");

	return;
#endif
}

uint32_t trusty_write_oem_ns_otp(uint32_t byte_off, uint8_t *byte_buf, uint32_t byte_len)
{
	TEEC_Result TeecResult;
	TEEC_Context TeecContext;
	TEEC_Session TeecSession;
	uint32_t ErrorOrigin;

	TEEC_UUID tempuuid = { 0x2d26d8a8, 0x5134, 0x4dd8,
			{ 0xb3, 0x2f, 0xb3, 0x4b, 0xce, 0xeb, 0xc4, 0x71 } };
	TEEC_UUID *TeecUuid = &tempuuid;
	TEEC_Operation TeecOperation = {0};

	TeecResult = OpteeClientApiLibInitialize();
	if (TeecResult != TEEC_SUCCESS)
		return TeecResult;

	TeecResult = TEEC_InitializeContext(NULL, &TeecContext);
	if (TeecResult != TEEC_SUCCESS)
		return TeecResult;

	TeecResult = TEEC_OpenSession(&TeecContext,
				&TeecSession,
				TeecUuid,
				TEEC_LOGIN_PUBLIC,
				NULL,
				NULL,
				&ErrorOrigin);
	if (TeecResult != TEEC_SUCCESS)
		return TeecResult;

	TeecOperation.params[0].value.a = byte_off;

	TEEC_SharedMemory SharedMem = {0};

	SharedMem.size = byte_len;
	SharedMem.flags = 0;

	TeecResult = TEEC_AllocateSharedMemory(&TeecContext, &SharedMem);
	if (TeecResult != TEEC_SUCCESS)
		goto exit;

	TeecOperation.params[1].tmpref.buffer = SharedMem.buffer;
	TeecOperation.params[1].tmpref.size = SharedMem.size;

	memcpy(SharedMem.buffer, byte_buf, SharedMem.size);
	TeecOperation.paramTypes = TEEC_PARAM_TYPES(TEEC_VALUE_INPUT,
						    TEEC_MEMREF_TEMP_INPUT,
						    TEEC_NONE,
						    TEEC_NONE);

	TeecResult = TEEC_InvokeCommand(&TeecSession,
					STORAGE_CMD_WRITE_OEM_NS_OTP,
					&TeecOperation,
					&ErrorOrigin);
	if (TeecResult != TEEC_SUCCESS)
		goto exit;

exit:
	TEEC_ReleaseSharedMemory(&SharedMem);
	TEEC_CloseSession(&TeecSession);
	TEEC_FinalizeContext(&TeecContext);

	return TeecResult;
}

uint32_t trusty_read_oem_ns_otp(uint32_t byte_off, uint8_t *byte_buf, uint32_t byte_len)
{
	TEEC_Result TeecResult;
	TEEC_Context TeecContext;
	TEEC_Session TeecSession;
	uint32_t ErrorOrigin;

	TEEC_UUID tempuuid = { 0x2d26d8a8, 0x5134, 0x4dd8,
			{ 0xb3, 0x2f, 0xb3, 0x4b, 0xce, 0xeb, 0xc4, 0x71 } };
	TEEC_UUID *TeecUuid = &tempuuid;
	TEEC_Operation TeecOperation = {0};

	TeecResult = OpteeClientApiLibInitialize();
	if (TeecResult != TEEC_SUCCESS)
		return TeecResult;

	TeecResult = TEEC_InitializeContext(NULL, &TeecContext);
	if (TeecResult != TEEC_SUCCESS)
		return TeecResult;

	TeecResult = TEEC_OpenSession(&TeecContext,
				&TeecSession,
				TeecUuid,
				TEEC_LOGIN_PUBLIC,
				NULL,
				NULL,
				&ErrorOrigin);
	if (TeecResult != TEEC_SUCCESS)
		return TeecResult;

	TeecOperation.params[0].value.a = byte_off;

	TEEC_SharedMemory SharedMem = {0};

	SharedMem.size = byte_len;
	SharedMem.flags = 0;

	TeecResult = TEEC_AllocateSharedMemory(&TeecContext, &SharedMem);
	if (TeecResult != TEEC_SUCCESS)
		goto exit;

	TeecOperation.params[1].tmpref.buffer = SharedMem.buffer;
	TeecOperation.params[1].tmpref.size = SharedMem.size;

	TeecOperation.paramTypes = TEEC_PARAM_TYPES(TEEC_VALUE_INPUT,
						    TEEC_MEMREF_TEMP_OUTPUT,
						    TEEC_NONE,
						    TEEC_NONE);

	TeecResult = TEEC_InvokeCommand(&TeecSession,
					STORAGE_CMD_READ_OEM_NS_OTP,
					&TeecOperation,
					&ErrorOrigin);
	if (TeecResult != TEEC_SUCCESS)
		goto exit;

	memcpy(byte_buf, SharedMem.buffer, SharedMem.size);

exit:
	TEEC_ReleaseSharedMemory(&SharedMem);
	TEEC_CloseSession(&TeecSession);
	TEEC_FinalizeContext(&TeecContext);

	return TeecResult;
}

uint32_t trusty_write_oem_otp_key(enum RK_OEM_OTP_KEYID key_id,
				  uint8_t *byte_buf, uint32_t byte_len)
{
	TEEC_Result TeecResult;
	TEEC_Context TeecContext;
	TEEC_Session TeecSession;
	uint32_t ErrorOrigin;

	TEEC_UUID tempuuid = { 0x2d26d8a8, 0x5134, 0x4dd8,
			{ 0xb3, 0x2f, 0xb3, 0x4b, 0xce, 0xeb, 0xc4, 0x71 } };
	TEEC_UUID *TeecUuid = &tempuuid;
	TEEC_Operation TeecOperation = {0};

	TeecResult = OpteeClientApiLibInitialize();
	if (TeecResult != TEEC_SUCCESS)
		return TeecResult;

	TeecResult = TEEC_InitializeContext(NULL, &TeecContext);
	if (TeecResult != TEEC_SUCCESS)
		return TeecResult;

	TeecResult = TEEC_OpenSession(&TeecContext,
				&TeecSession,
				TeecUuid,
				TEEC_LOGIN_PUBLIC,
				NULL,
				NULL,
				&ErrorOrigin);
	if (TeecResult != TEEC_SUCCESS)
		return TeecResult;

	TeecOperation.params[0].value.a = key_id;

	TEEC_SharedMemory SharedMem = {0};

	SharedMem.size = byte_len;
	SharedMem.flags = 0;

	TeecResult = TEEC_AllocateSharedMemory(&TeecContext, &SharedMem);
	if (TeecResult != TEEC_SUCCESS)
		goto exit;

	TeecOperation.params[1].tmpref.buffer = SharedMem.buffer;
	TeecOperation.params[1].tmpref.size = SharedMem.size;

	memcpy(SharedMem.buffer, byte_buf, SharedMem.size);
	TeecOperation.paramTypes = TEEC_PARAM_TYPES(TEEC_VALUE_INPUT,
						    TEEC_MEMREF_TEMP_INPUT,
						    TEEC_NONE,
						    TEEC_NONE);

	TeecResult = TEEC_InvokeCommand(&TeecSession,
					STORAGE_CMD_WRITE_OEM_OTP_KEY,
					&TeecOperation,
					&ErrorOrigin);
	if (TeecResult != TEEC_SUCCESS)
		goto exit;

exit:
	TEEC_ReleaseSharedMemory(&SharedMem);
	TEEC_CloseSession(&TeecSession);
	TEEC_FinalizeContext(&TeecContext);

	return TeecResult;
}

uint32_t trusty_oem_otp_key_is_written(enum RK_OEM_OTP_KEYID key_id, uint8_t *value)
{
	TEEC_Result TeecResult;
	TEEC_Context TeecContext;
	TEEC_Session TeecSession;
	uint32_t ErrorOrigin;

	*value = 0xFF;

	TEEC_UUID tempuuid = { 0x2d26d8a8, 0x5134, 0x4dd8,
			{ 0xb3, 0x2f, 0xb3, 0x4b, 0xce, 0xeb, 0xc4, 0x71 } };
	TEEC_UUID *TeecUuid = &tempuuid;
	TEEC_Operation TeecOperation = {0};

	TeecResult = OpteeClientApiLibInitialize();
	if (TeecResult != TEEC_SUCCESS)
		return TeecResult;

	TeecResult = TEEC_InitializeContext(NULL, &TeecContext);
	if (TeecResult != TEEC_SUCCESS)
		return TeecResult;

	TeecResult = TEEC_OpenSession(&TeecContext,
				&TeecSession,
				TeecUuid,
				TEEC_LOGIN_PUBLIC,
				NULL,
				NULL,
				&ErrorOrigin);
	if (TeecResult != TEEC_SUCCESS)
		return TeecResult;

	TeecOperation.params[0].value.a = key_id;

	TeecOperation.paramTypes = TEEC_PARAM_TYPES(TEEC_VALUE_INOUT,
						    TEEC_NONE,
						    TEEC_NONE,
						    TEEC_NONE);

	TeecResult = TEEC_InvokeCommand(&TeecSession,
					STORAGE_CMD_OEM_OTP_KEY_IS_WRITTEN,
					&TeecOperation,
					&ErrorOrigin);
	if (TeecResult == TEEC_SUCCESS)
		*value = TeecOperation.params[0].value.b;

	TEEC_CloseSession(&TeecSession);
	TEEC_FinalizeContext(&TeecContext);

	return TeecResult;
}

uint32_t trusty_set_oem_hr_otp_read_lock(enum RK_OEM_OTP_KEYID key_id)
{
	TEEC_Result TeecResult;
	TEEC_Context TeecContext;
	TEEC_Session TeecSession;
	uint32_t ErrorOrigin;

	TEEC_UUID tempuuid = { 0x2d26d8a8, 0x5134, 0x4dd8,
			{ 0xb3, 0x2f, 0xb3, 0x4b, 0xce, 0xeb, 0xc4, 0x71 } };
	TEEC_UUID *TeecUuid = &tempuuid;
	TEEC_Operation TeecOperation = {0};

	TeecResult = OpteeClientApiLibInitialize();
	if (TeecResult != TEEC_SUCCESS)
		return TeecResult;

	TeecResult = TEEC_InitializeContext(NULL, &TeecContext);
	if (TeecResult != TEEC_SUCCESS)
		return TeecResult;

	TeecResult = TEEC_OpenSession(&TeecContext,
				&TeecSession,
				TeecUuid,
				TEEC_LOGIN_PUBLIC,
				NULL,
				NULL,
				&ErrorOrigin);
	if (TeecResult != TEEC_SUCCESS)
		return TeecResult;

	TeecOperation.params[0].value.a = key_id;

	TeecOperation.paramTypes = TEEC_PARAM_TYPES(TEEC_VALUE_INPUT,
						    TEEC_NONE,
						    TEEC_NONE,
						    TEEC_NONE);

	TeecResult = TEEC_InvokeCommand(&TeecSession,
					STORAGE_CMD_SET_OEM_HR_OTP_READ_LOCK,
					&TeecOperation,
					&ErrorOrigin);
	if (TeecResult != TEEC_SUCCESS)
		goto exit;

exit:
	TEEC_CloseSession(&TeecSession);
	TEEC_FinalizeContext(&TeecContext);

	return TeecResult;
}

uint32_t trusty_oem_otp_key_cipher(enum RK_OEM_OTP_KEYID key_id, rk_cipher_config *config,
				   uint32_t src_phys_addr, uint32_t dst_phys_addr,
				   uint32_t len)
{
	TEEC_Result TeecResult;
	TEEC_Context TeecContext;
	TEEC_Session TeecSession;
	TEEC_Operation TeecOperation = {0};
	uint32_t ErrorOrigin;
	TEEC_UUID uuid = RK_CRYPTO_SERVICE_UUID;
	TEEC_SharedMemory SharedMem_config = {0};

	if (key_id != RK_OEM_OTP_KEY0 &&
	    key_id != RK_OEM_OTP_KEY1 &&
	    key_id != RK_OEM_OTP_KEY2 &&
	    key_id != RK_OEM_OTP_KEY3 &&
	    key_id != RK_OEM_OTP_KEY_FW)
		return TEEC_ERROR_BAD_PARAMETERS;

	if (!config)
		return TEEC_ERROR_BAD_PARAMETERS;

	if (config->algo != RK_ALGO_AES && config->algo != RK_ALGO_SM4)
		return TEEC_ERROR_BAD_PARAMETERS;

	if (config->mode >= RK_CIPHER_MODE_XTS)
		return TEEC_ERROR_BAD_PARAMETERS;

	if (config->operation != RK_MODE_ENCRYPT &&
	    config->operation != RK_MODE_DECRYPT)
		return TEEC_ERROR_BAD_PARAMETERS;

	if (config->key_len != 16 &&
	    config->key_len != 24 &&
	    config->key_len != 32)
		return TEEC_ERROR_BAD_PARAMETERS;

	if (key_id == RK_OEM_OTP_KEY_FW && config->key_len != 16)
		return TEEC_ERROR_BAD_PARAMETERS;

#if defined(CONFIG_ROCKCHIP_RV1126)
	if (config->key_len == 24)
		return TEEC_ERROR_BAD_PARAMETERS;
#endif

	if (len % AES_BLOCK_SIZE ||
	    len == 0)
		return TEEC_ERROR_BAD_PARAMETERS;

	if (!src_phys_addr || !dst_phys_addr)
		return TEEC_ERROR_BAD_PARAMETERS;

	TeecResult = OpteeClientApiLibInitialize();
	if (TeecResult != TEEC_SUCCESS)
		return TeecResult;

	TeecResult = TEEC_InitializeContext(NULL, &TeecContext);
	if (TeecResult != TEEC_SUCCESS)
		return TeecResult;

	TeecResult = TEEC_OpenSession(&TeecContext,
				      &TeecSession,
				      &uuid,
				      TEEC_LOGIN_PUBLIC,
				      NULL,
				      NULL,
				      &ErrorOrigin);
	if (TeecResult != TEEC_SUCCESS)
		goto exit;

	SharedMem_config.size = sizeof(rk_cipher_config);
	TeecResult = TEEC_AllocateSharedMemory(&TeecContext, &SharedMem_config);
	if (TeecResult != TEEC_SUCCESS)
		goto exit;

	memcpy(SharedMem_config.buffer, config, sizeof(rk_cipher_config));
	TeecOperation.params[0].value.a       = key_id;
	TeecOperation.params[1].tmpref.buffer = SharedMem_config.buffer;
	TeecOperation.params[1].tmpref.size   = SharedMem_config.size;
	TeecOperation.params[2].value.a       = src_phys_addr;
	TeecOperation.params[2].value.b       = len;
	TeecOperation.params[3].value.a       = dst_phys_addr;
	TeecOperation.paramTypes = TEEC_PARAM_TYPES(TEEC_VALUE_INPUT,
						    TEEC_MEMREF_TEMP_INPUT,
						    TEEC_VALUE_INPUT,
						    TEEC_VALUE_INPUT);

	crypto_flush_cacheline(src_phys_addr, len);
	crypto_flush_cacheline(dst_phys_addr, len);

	TeecResult = TEEC_InvokeCommand(&TeecSession,
					CRYPTO_SERVICE_CMD_OEM_OTP_KEY_PHYS_CIPHER,
					&TeecOperation,
					&ErrorOrigin);

exit:
	TEEC_ReleaseSharedMemory(&SharedMem_config);
	TEEC_CloseSession(&TeecSession);
	TEEC_FinalizeContext(&TeecContext);
	return TeecResult;
}

uint32_t trusty_attest_dh(uint8_t *dh, uint32_t *dh_size)
{
	TEEC_Result TeecResult;
	TEEC_Context TeecContext;
	TEEC_Session TeecSession;
	uint32_t ErrorOrigin;
	TEEC_UUID tempuuid = { 0x258be795, 0xf9ca, 0x40e6,
				{ 0xa8, 0x69, 0x9c, 0xe6,
				  0x88, 0x6c, 0x5d, 0x5d
				}
			     };
	TEEC_UUID *TeecUuid = &tempuuid;
	TEEC_Operation TeecOperation = {0};
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
	/*0 nand or emmc "security" partition , 1 rpmb*/
	if (dev_desc->if_type == IF_TYPE_MMC && dev_desc->devnum == 0)
		TeecOperation.params[0].value.a = 1;
	else
		TeecOperation.params[0].value.a = 0;

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

	TEEC_SharedMemory SharedMem0 = {0};

	SharedMem0.size = *dh_size;
	SharedMem0.flags = 0;

	TeecResult = TEEC_AllocateSharedMemory(&TeecContext, &SharedMem0);
	if (TeecResult != TEEC_SUCCESS)
		goto exit;

	TeecOperation.params[0].tmpref.buffer = SharedMem0.buffer;
	TeecOperation.params[0].tmpref.size = SharedMem0.size;

	TeecOperation.paramTypes = TEEC_PARAM_TYPES(TEEC_MEMREF_TEMP_INOUT,
						    TEEC_NONE,
						    TEEC_NONE,
						    TEEC_NONE);

	TeecResult = TEEC_InvokeCommand(&TeecSession,
					143,
					&TeecOperation,
					&ErrorOrigin);
	if (TeecResult != TEEC_SUCCESS)
		goto exit;

	*dh_size = TeecOperation.params[0].tmpref.size;
	memcpy(dh, SharedMem0.buffer, SharedMem0.size);
exit:
	TEEC_ReleaseSharedMemory(&SharedMem0);
	TEEC_CloseSession(&TeecSession);
	TEEC_FinalizeContext(&TeecContext);

	return TeecResult;
}

uint32_t trusty_attest_uuid(uint8_t *uuid, uint32_t *uuid_size)
{
	TEEC_Result TeecResult;
	TEEC_Context TeecContext;
	TEEC_Session TeecSession;
	uint32_t ErrorOrigin;
	TEEC_UUID tempuuid = { 0x258be795, 0xf9ca, 0x40e6,
				{ 0xa8, 0x69, 0x9c, 0xe6,
				  0x88, 0x6c, 0x5d, 0x5d
				}
			     };
	TEEC_UUID *TeecUuid = &tempuuid;
	TEEC_Operation TeecOperation = {0};
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
	/*0 nand or emmc "security" partition , 1 rpmb*/
	if (dev_desc->if_type == IF_TYPE_MMC && dev_desc->devnum == 0)
		TeecOperation.params[0].value.a = 1;
	else
		TeecOperation.params[0].value.a = 0;

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

	TEEC_SharedMemory SharedMem0 = {0};

	SharedMem0.size = *uuid_size;
	SharedMem0.flags = 0;

	TeecResult = TEEC_AllocateSharedMemory(&TeecContext, &SharedMem0);
	if (TeecResult != TEEC_SUCCESS)
		goto exit;

	TeecOperation.params[0].tmpref.buffer = SharedMem0.buffer;
	TeecOperation.params[0].tmpref.size = SharedMem0.size;

	TeecOperation.paramTypes = TEEC_PARAM_TYPES(TEEC_MEMREF_TEMP_INOUT,
						    TEEC_NONE,
						    TEEC_NONE,
						    TEEC_NONE);

	TeecResult = TEEC_InvokeCommand(&TeecSession,
					144,
					&TeecOperation,
					&ErrorOrigin);
	if (TeecResult != TEEC_SUCCESS)
		goto exit;

	*uuid_size = TeecOperation.params[0].tmpref.size;
	memcpy(uuid, SharedMem0.buffer, SharedMem0.size);
exit:
	TEEC_ReleaseSharedMemory(&SharedMem0);
	TEEC_CloseSession(&TeecSession);
	TEEC_FinalizeContext(&TeecContext);

	return TeecResult;
}

uint32_t trusty_attest_get_ca(uint8_t *operation_start,
			      uint32_t *operation_size,
			      uint8_t *out,
			      uint32_t *out_len)
{
	TEEC_Result TeecResult;
	TEEC_Context TeecContext;
	TEEC_Session TeecSession;
	uint32_t ErrorOrigin;

	TEEC_UUID tempuuid = { 0x258be795, 0xf9ca, 0x40e6,
				{ 0xa8, 0x69, 0x9c, 0xe6,
				  0x88, 0x6c, 0x5d, 0x5d
				}
			     };

	TEEC_UUID *TeecUuid = &tempuuid;
	TEEC_Operation TeecOperation = {0};
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
	/*0 nand or emmc "security" partition , 1 rpmb*/
	if (dev_desc->if_type == IF_TYPE_MMC && dev_desc->devnum == 0)
		TeecOperation.params[0].value.a = 1;
	else
		TeecOperation.params[0].value.a = 0;

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

	TEEC_SharedMemory SharedMem0 = {0};

	SharedMem0.size = *operation_size;
	SharedMem0.flags = 0;

	TeecResult = TEEC_AllocateSharedMemory(&TeecContext, &SharedMem0);
	if (TeecResult != TEEC_SUCCESS)
		goto exit;

	memcpy(SharedMem0.buffer, operation_start, SharedMem0.size);

	TeecOperation.params[0].tmpref.buffer = SharedMem0.buffer;
	TeecOperation.params[0].tmpref.size = SharedMem0.size;

	TEEC_SharedMemory SharedMem1 = {0};

	SharedMem1.size = *out_len;
	SharedMem1.flags = 0;

	TeecResult = TEEC_AllocateSharedMemory(&TeecContext, &SharedMem1);
	if (TeecResult != TEEC_SUCCESS)
		goto exit;

	TeecOperation.params[1].tmpref.buffer = SharedMem1.buffer;
	TeecOperation.params[1].tmpref.size = SharedMem1.size;

	TeecOperation.paramTypes = TEEC_PARAM_TYPES(TEEC_MEMREF_TEMP_INOUT,
						    TEEC_MEMREF_TEMP_INOUT,
						    TEEC_NONE,
						    TEEC_NONE);

	TeecResult = TEEC_InvokeCommand(&TeecSession,
					145,
					&TeecOperation,
					&ErrorOrigin);
	if (TeecResult != TEEC_SUCCESS)
		goto exit;

	*out_len = TeecOperation.params[1].tmpref.size;
	memcpy(out, SharedMem1.buffer, SharedMem1.size);
exit:
	TEEC_ReleaseSharedMemory(&SharedMem0);
	TEEC_ReleaseSharedMemory(&SharedMem1);
	TEEC_CloseSession(&TeecSession);
	TEEC_FinalizeContext(&TeecContext);

	return TeecResult;
}

uint32_t trusty_attest_set_ca(uint8_t *ca_response, uint32_t *ca_response_size)
{
	TEEC_Result TeecResult;
	TEEC_Context TeecContext;
	TEEC_Session TeecSession;
	uint32_t ErrorOrigin;
	TEEC_UUID tempuuid = { 0x258be795, 0xf9ca, 0x40e6,
				{ 0xa8, 0x69, 0x9c, 0xe6,
				  0x88, 0x6c, 0x5d, 0x5d
				}
			     };
	TEEC_UUID *TeecUuid = &tempuuid;
	TEEC_Operation TeecOperation = {0};
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
	/*0 nand or emmc "security" partition , 1 rpmb*/
	if (dev_desc->if_type == IF_TYPE_MMC && dev_desc->devnum == 0)
		TeecOperation.params[0].value.a = 1;
	else
		TeecOperation.params[0].value.a = 0;

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

	TEEC_SharedMemory SharedMem0 = {0};

	SharedMem0.size = *ca_response_size;
	SharedMem0.flags = 0;

	TeecResult = TEEC_AllocateSharedMemory(&TeecContext, &SharedMem0);
	if (TeecResult != TEEC_SUCCESS)
		goto exit;

	memcpy(SharedMem0.buffer, ca_response, SharedMem0.size);

	TeecOperation.params[0].tmpref.buffer = SharedMem0.buffer;
	TeecOperation.params[0].tmpref.size = SharedMem0.size;

	TeecOperation.paramTypes = TEEC_PARAM_TYPES(TEEC_MEMREF_TEMP_INOUT,
						    TEEC_NONE,
						    TEEC_NONE,
						    TEEC_NONE);

	TeecResult = TEEC_InvokeCommand(&TeecSession,
					146,
					&TeecOperation,
					&ErrorOrigin);
	if (TeecResult != TEEC_SUCCESS)
		goto exit;
exit:
	TEEC_ReleaseSharedMemory(&SharedMem0);
	TEEC_CloseSession(&TeecSession);
	TEEC_FinalizeContext(&TeecContext);

	return TeecResult;
}
