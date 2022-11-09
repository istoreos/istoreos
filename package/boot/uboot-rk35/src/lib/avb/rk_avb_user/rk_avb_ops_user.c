/*
 * (C) Copyright 2017 Rockchip Electronics Co., Ltd
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */

#include <common.h>
#include <image.h>
#include <android_image.h>
#include <malloc.h>
#include <mapmem.h>
#include <errno.h>
#include <command.h>
#include <mmc.h>
#include <blk.h>
#include <part.h>
#include <android_avb/avb_ops_user.h>
#include <android_avb/libavb_ab.h>
#include <android_avb/avb_atx_validate.h>
#include <android_avb/avb_atx_types.h>
#include <optee_include/OpteeClientInterface.h>
#include <optee_include/tee_api_defines.h>
#include <android_avb/avb_vbmeta_image.h>
#include <android_avb/avb_atx_validate.h>
#include <android_avb/rk_avb_ops_user.h>
#include <boot_rkimg.h>
#include <u-boot/sha256.h>
#include <asm/arch-rockchip/rk_atags.h>

/* rk used */
int rk_avb_get_pub_key(struct rk_pub_key *pub_key)
{
	struct tag *t = NULL;

	t = atags_get_tag(ATAG_PUB_KEY);
	if (!t)
		return -1;

	memcpy(pub_key, t->u.pub_key.data, sizeof(struct rk_pub_key));

	return 0;
}

int rk_avb_get_perm_attr_cer(uint8_t *cer, uint32_t size)
{
#ifdef CONFIG_OPTEE_CLIENT
	if (trusty_read_permanent_attributes_cer((uint8_t *)cer, size)) {
		printf("AVB: perm attr cer is not exist.\n");
		return -EIO;
	}

	return 0;
#else
	return -1;
#endif
}

int rk_avb_set_perm_attr_cer(uint8_t *cer, uint32_t size)
{
#ifdef CONFIG_OPTEE_CLIENT
	if (trusty_write_permanent_attributes_cer((uint8_t *)cer, size))
		return -EIO;

	return 0;
#else
	return -1;
#endif
}

int rk_avb_read_permanent_attributes(uint8_t *attributes, uint32_t size)
{
#ifdef CONFIG_OPTEE_CLIENT
	if(trusty_read_permanent_attributes(attributes, size) != 0) {
		printf("trusty_read_permanent_attributes failed!\n");
		return -1;
	}

	return 0;
#else
	return -1;
#endif
}

int rk_avb_write_permanent_attributes(uint8_t *attributes, uint32_t size)
{
#ifdef CONFIG_OPTEE_CLIENT
	if(trusty_write_permanent_attributes(attributes, size) != 0) {
		printf("trusty_write_permanent_attributes failed!\n");
		return -1;
	}

	return 0;
#else
	return -1;
#endif
}

int rk_avb_read_flash_lock_state(uint8_t *flash_lock_state)
{
#ifdef CONFIG_OPTEE_CLIENT
	int ret;

	ret = trusty_read_flash_lock_state(flash_lock_state);
	switch (ret) {
	case TEE_SUCCESS:
		break;
	case TEE_ERROR_GENERIC:
	case TEE_ERROR_NO_DATA:
	case TEE_ERROR_ITEM_NOT_FOUND:
		*flash_lock_state = 1;
		if (trusty_write_flash_lock_state(*flash_lock_state)) {
			avb_error("trusty_write_flash_lock_state error!");
			ret = -1;
		} else {
			ret = trusty_read_flash_lock_state(flash_lock_state);
		}
		break;
	default:
		printf("%s: trusty_read_flash_lock_state failed\n", __FILE__);
	}

	return ret;
#else
	*flash_lock_state = 1;

	return 0;
#endif
}

int rk_avb_write_flash_lock_state(uint8_t flash_lock_state)
{
#ifdef CONFIG_OPTEE_CLIENT
	if (trusty_write_flash_lock_state(flash_lock_state)) {
		printf("trusty_write_flash_lock_state error!\n");
		return -1;
	}

	return 0;
#else
	return -1;
#endif
}

int rk_avb_write_lock_state(uint8_t lock_state)
{
#ifdef CONFIG_OPTEE_CLIENT
	if (trusty_write_lock_state(lock_state)) {
		printf("trusty_write_lock_state error!\n");
		return -1;
	}

	return 0;
#else
	return -1;
#endif
}

int rk_avb_read_lock_state(uint8_t *lock_state)
{
#ifdef CONFIG_OPTEE_CLIENT
	int ret;

	ret = trusty_read_lock_state(lock_state);
	switch (ret) {
	case TEE_SUCCESS:
		break;
	case TEE_ERROR_GENERIC:
	case TEE_ERROR_NO_DATA:
	case TEE_ERROR_ITEM_NOT_FOUND:
		*lock_state = 1;
		if (rk_avb_write_lock_state(*lock_state)) {
			avb_error("avb_write_lock_state error!");
			ret = -1;
		} else {
			ret = trusty_read_lock_state(lock_state);
		}
		break;
	default:
		printf("%s: trusty_read_lock_state failed\n", __FILE__);
	}

	return ret;
#else
	return -1;
#endif
}

int rk_avb_write_perm_attr_flag(uint8_t flag)
{
#ifdef CONFIG_OPTEE_CLIENT
	if (trusty_write_permanent_attributes_flag(flag)) {
		printf("trusty_write_permanent_attributes_flag error!\n");
		return -1;
	}

	return 0;
#else
	return -1;
#endif
}

int rk_avb_read_perm_attr_flag(uint8_t *flag)
{
#ifdef CONFIG_OPTEE_CLIENT
	int ret;

	ret = trusty_read_permanent_attributes_flag(flag);
	switch (ret) {
	case TEE_SUCCESS:
		break;
	case TEE_ERROR_GENERIC:
	case TEE_ERROR_NO_DATA:
	case TEE_ERROR_ITEM_NOT_FOUND:
		*flag = 0;
		if (rk_avb_write_perm_attr_flag(*flag)) {
			avb_error("avb_write_perm_attr_flag error!");
			ret = -1;
		} else {
			ret = trusty_read_permanent_attributes_flag(flag);
		}
		break;
	default:
		printf("%s: trusty_read_permanent_attributes_flag failed",
		       __FILE__);
	}

	return ret;
#else
	return -1;
#endif
}

int rk_avb_read_vbootkey_hash(uint8_t *buf, uint8_t length)
{
#ifdef CONFIG_OPTEE_CLIENT
	if (trusty_read_vbootkey_hash((uint32_t *)buf,
				      (uint32_t)length / sizeof(uint32_t))) {
		printf("trusty_read_vbootkey_hash error!\n");
		return -1;
	}

	return 0;
#else
	return -1;
#endif
}

int rk_avb_write_vbootkey_hash(uint8_t *buf, uint8_t length)
{
#ifdef CONFIG_OPTEE_CLIENT
	if (trusty_write_vbootkey_hash((uint32_t *)buf,
				       (uint32_t)length / sizeof(uint32_t))) {
		printf("trusty_write_vbootkey_hash error!\n");
		return -1;
	}

	return 0;
#else
	return -1;
#endif
}

int rk_avb_close_optee_client(void)
{
#ifdef CONFIG_OPTEE_CLIENT
	if(trusty_notify_optee_uboot_end()) {
		printf("trusty_notify_optee_uboot_end error!\n");
		return -1;
	}

	return 0;
#else
	return -1;
#endif
}

int rk_avb_read_attribute_hash(uint8_t *buf, uint8_t length)
{
#ifdef CONFIG_OPTEE_CLIENT
	if (trusty_read_attribute_hash((uint32_t *)buf,
	    (uint32_t)(length/sizeof(uint32_t)))) {
		printf("trusty_read_attribute_hash error!\n");
		return -1;
	}

	return 0;
#else
	return -1;
#endif
}

int rk_avb_write_attribute_hash(uint8_t *buf, uint8_t length)
{
#ifdef CONFIG_OPTEE_CLIENT
	if (trusty_write_attribute_hash((uint32_t *)buf,
	    (uint32_t)(length/sizeof(uint32_t)))) {
		printf("trusty_write_attribute_hash error!\n");
		return -1;
	}

	return 0;
#else
	return -1;
#endif
}

int rk_avb_read_all_rollback_index(char *buffer)
{
	AvbOps* ops;
	uint64_t stored_rollback_index = 0;
	AvbIOResult io_ret;
	char temp[ROLLBACK_MAX_SIZE] = {0};

	ops = avb_ops_user_new();
	if (ops == NULL) {
		printf("avb_ops_user_new() failed!\n");
		return -1;
	}

	/* Actually the rollback_index_location 0 is used. */
	io_ret = ops->read_rollback_index(ops, 0, &stored_rollback_index);
	if (io_ret != AVB_IO_RESULT_OK)
		goto out;
	snprintf(temp, sizeof(int) + 1, "%d", 0);
	strncat(buffer, temp, ROLLBACK_MAX_SIZE);
	strncat(buffer, ":", 1);
	snprintf(temp, sizeof(uint64_t) + 1, "%lld",
		 stored_rollback_index);
	strncat(buffer, temp, ROLLBACK_MAX_SIZE);
	strncat(buffer, ",", 1);

	io_ret =
		ops->read_rollback_index(ops,
					 AVB_ATX_PIK_VERSION_LOCATION,
					 &stored_rollback_index);
	if (io_ret != AVB_IO_RESULT_OK) {
		avb_error("Failed to read PIK minimum version.\n");
		goto out;
	}
	/* PIK rollback index */
	snprintf(temp, sizeof(int) + 1, "%d", AVB_ATX_PIK_VERSION_LOCATION);
	strncat(buffer, temp, ROLLBACK_MAX_SIZE);
	strncat(buffer, ":", 1);
	snprintf(temp, sizeof(uint64_t) + 1, "%lld", stored_rollback_index);
	strncat(buffer, temp, ROLLBACK_MAX_SIZE);
	strncat(buffer, ",", 1);
	io_ret = ops->read_rollback_index(ops,
					  AVB_ATX_PSK_VERSION_LOCATION,
					  &stored_rollback_index);
	if (io_ret != AVB_IO_RESULT_OK) {
		avb_error("Failed to read PSK minimum version.\n");
		goto out;
	}
	/* PSK rollback index */
	snprintf(temp, sizeof(int) + 1, "%d", AVB_ATX_PSK_VERSION_LOCATION);
	strncat(buffer, temp, ROLLBACK_MAX_SIZE);
	strncat(buffer, ":", 1);
	snprintf(temp, sizeof(uint64_t) + 1, "%lld", stored_rollback_index);
	strncat(buffer, temp, ROLLBACK_MAX_SIZE);
	debug("%s\n", buffer);
	avb_ops_user_free(ops);

	return 0;
out:
	avb_ops_user_free(ops);

	return -1;
}

int rk_avb_read_bootloader_locked_flag(uint8_t *flag)
{
#ifdef CONFIG_OPTEE_CLIENT
	if (trusty_read_vbootkey_enable_flag(flag))
		return -1;
#endif
	return 0;
}

#ifdef CONFIG_SUPPORT_EMMC_RPMB
static int curr_device = -1;

int rk_bootloader_rollback_index_read(uint32_t offset, uint32_t bytes,
				      void *rb_index)
{

	struct mmc *mmc;
	uint8_t rpmb_buf[256] = {0};
	uint32_t n;
	char original_part;

	if ((offset + bytes) > 256)
		return -1;

	if (curr_device < 0) {
		if (get_mmc_num() > 0)
			curr_device = 0;
		else {
			avb_error("No MMC device available");
			return -1;
		}
	}

	mmc = find_mmc_device(curr_device);
	/* Switch to the RPMB partition */
#ifndef CONFIG_BLK
	original_part = mmc->block_dev.hwpart;
#else
	original_part = mmc_get_blk_desc(mmc)->hwpart;
#endif
	if (blk_select_hwpart_devnum(IF_TYPE_MMC, curr_device, MMC_PART_RPMB) !=
	    0)
		return -1;

	n =  mmc_rpmb_read(mmc, rpmb_buf, RPMB_BASE_ADDR, 1, NULL);
	if (n != 1)
		return -1;

	/* Return to original partition */
	if (blk_select_hwpart_devnum(IF_TYPE_MMC, curr_device, original_part) !=
	    0)
		return -1;

	memcpy(rb_index, (void*)&rpmb_buf[offset], bytes);

	return 0;
}

int rk_avb_get_bootloader_min_version(char *buffer)
{
	uint32_t rb_index;
	char temp[ROLLBACK_MAX_SIZE] = {0};

	if (rk_bootloader_rollback_index_read(UBOOT_RB_INDEX_OFFSET,
					      sizeof(uint32_t), &rb_index)) {
		avb_error("Can not read uboot rollback index");
		return -1;
	}
	snprintf(temp, sizeof(int) + 1, "%d", 0);
	strncat(buffer, temp, ROLLBACK_MAX_SIZE);
	strncat(buffer, ":", 1);
	snprintf(temp, sizeof(uint32_t) + 1, "%d", rb_index);
	strncat(buffer, temp, ROLLBACK_MAX_SIZE);
	strncat(buffer, ",", 1);

	if (rk_bootloader_rollback_index_read(TRUST_RB_INDEX_OFFSET,
					      sizeof(uint32_t), &rb_index)) {
		avb_error("Can not read trust rollback index");
		return -1;
	}

	snprintf(temp, sizeof(int) + 1, "%d", 1);
	strncat(buffer, temp, ROLLBACK_MAX_SIZE);
	strncat(buffer, ":", 1);
	snprintf(temp, sizeof(uint32_t) + 1, "%d", rb_index);
	strncat(buffer, temp, ROLLBACK_MAX_SIZE);

	return 0;
}
#endif

void rk_avb_get_at_vboot_state(char *buf)
{
	char temp_flag = 0;
	char *lock_val = NULL;
	char *unlock_dis_val = NULL;
	char *perm_attr_flag = NULL;
	char *bootloader_locked_flag = NULL;
	char *rollback_indices;
	char min_versions[ROLLBACK_MAX_SIZE + 1] = {0};
	int n;

	if (rk_avb_read_perm_attr_flag((uint8_t *)&temp_flag)) {
		avb_error("Can not read perm_attr_flag!");
		perm_attr_flag = "";
	} else {
		perm_attr_flag = temp_flag ? "1" : "0";
	}

	temp_flag = 0;
	if (rk_avb_read_lock_state((uint8_t *)&temp_flag)) {
		avb_error("Can not read lock state!");
		lock_val = "";
		unlock_dis_val = "";
	} else {
		lock_val = (temp_flag & LOCK_MASK) ? "0" : "1";
		unlock_dis_val = (temp_flag & UNLOCK_DISABLE_MASK) ? "1" : "0";
	}

	temp_flag = 0;
	if (rk_avb_read_bootloader_locked_flag((uint8_t *)&temp_flag)) {
		avb_error("Can not read bootloader locked flag!");
		bootloader_locked_flag = "";
	} else {
		bootloader_locked_flag = temp_flag ? "1" : "0";
	}

	rollback_indices = malloc(VBOOT_STATE_SIZE);
	if (!rollback_indices) {
		avb_error("No buff to malloc!");
		return;
	}

	memset(rollback_indices, 0, VBOOT_STATE_SIZE);
	if (rk_avb_read_all_rollback_index(rollback_indices))
		avb_error("Can not read avb_min_ver!");
#ifdef CONFIG_SUPPORT_EMMC_RPMB
	/* bootloader-min-versions */
	if (rk_avb_get_bootloader_min_version(min_versions))
		avb_error("Call rk_avb_get_bootloader_min_version error!");
#endif
	n = snprintf(buf, VBOOT_STATE_SIZE - 1,
		     "avb-perm-attr-set=%s\n"
		     "avb-locked=%s\n"
		     "avb-unlock-disabled=%s\n"
		     "bootloader-locked=%s\n"
		     "avb-min-versions=%s\n"
		     "bootloader-min-versions=%s\n",
		     perm_attr_flag,
		     lock_val,
		     unlock_dis_val,
		     bootloader_locked_flag,
		     rollback_indices,
		     min_versions);
	if (n >= VBOOT_STATE_SIZE) {
		avb_error("The VBOOT_STATE buf is truncated\n");
		buf[VBOOT_STATE_SIZE - 1] = 0;
	}
	debug("The vboot state buf is %s\n", buf);
	free(rollback_indices);
}

int rk_avb_get_ab_info(AvbABData* ab_data)
{
	AvbOps* ops;
	AvbIOResult io_ret = AVB_IO_RESULT_OK;
	int ret = 0;

	ops = avb_ops_user_new();
	if (ops == NULL) {
		printf("%s: avb_ops_user_new() failed!\n", __FILE__);
		return -1;
	}

	io_ret = ops->ab_ops->read_ab_metadata(ops->ab_ops, ab_data);
	if (io_ret != AVB_IO_RESULT_OK) {
		avb_error("I/O error while loading A/B metadata.\n");
		ret = -1;
	}

	avb_ops_user_free(ops);

	return ret;
}

int rk_avb_get_part_has_slot_info(const char *base_name)
{
	char *part_name;
	int part_num;
	size_t part_name_len;
	disk_partition_t part_info;
	struct blk_desc *dev_desc;
	const char *slot_suffix = "_a";

	dev_desc = rockchip_get_bootdev();
	if (!dev_desc) {
		printf("%s: Could not find device!\n", __func__);
		return -1;
	}

	if (base_name == NULL) {
		printf("The base_name is NULL!\n");
		return -1;
	}

	part_name_len = strlen(base_name) + 1;
	part_name_len += strlen(slot_suffix);
	part_name = malloc(part_name_len);
	if (!part_name) {
		printf("%s can not malloc a buffer!\n", __FILE__);
		return -1;
	}

	memset(part_name, 0, part_name_len);
	snprintf(part_name, part_name_len, "%s%s", base_name, slot_suffix);
	part_num = part_get_info_by_name(dev_desc, part_name, &part_info);
	if (part_num < 0) {
		printf("Could not find partition \"%s\"\n", part_name);
		part_num = -1;
	}

	free(part_name);
	return part_num;
}

int rk_auth_unlock(void *buffer, char *out_is_trusted)
{
	AvbOps* ops;

	ops = avb_ops_user_new();
	if (ops == NULL) {
		avb_error("avb_ops_user_new() failed!");
		return -1;
	}

	if (avb_atx_validate_unlock_credential(ops->atx_ops,
					   (AvbAtxUnlockCredential*)buffer,
					   (bool*)out_is_trusted)) {
		avb_ops_user_free(ops);
		return -1;
	}
	avb_ops_user_free(ops);
	if (*out_is_trusted == true)
		return 0;
	else
		return -1;
}

int rk_generate_unlock_challenge(void *buffer, uint32_t *challenge_len)
{
	AvbOps* ops;
	AvbIOResult result = AVB_IO_RESULT_OK;

	ops = avb_ops_user_new();
	if (ops == NULL) {
		avb_error("avb_ops_user_new() failed!");
		return -1;
	}

	result = avb_atx_generate_unlock_challenge(ops->atx_ops,
						   (AvbAtxUnlockChallenge *)buffer);
	avb_ops_user_free(ops);
	*challenge_len = sizeof(AvbAtxUnlockChallenge);
	if (result == AVB_IO_RESULT_OK)
		return 0;
	else
		return -1;
}

int rk_avb_init_ab_metadata(void)
{
	AvbOps *ops;
	AvbABData ab_data;

	memset(&ab_data, 0, sizeof(AvbABData));
	debug("sizeof(AvbABData) = %d\n", (int)(size_t)sizeof(AvbABData));

	ops = avb_ops_user_new();
	if (ops == NULL) {
		printf("avb_ops_user_new() failed!\n");
		return -1;
	}

	avb_ab_data_init(&ab_data);
	if (ops->ab_ops->write_ab_metadata(ops->ab_ops, &ab_data) != 0) {
		printf("do_avb_init_ab_metadata error!\n");
		avb_ops_user_free(ops);
		return -1;
	}

	printf("Initialize ab data to misc partition success.\n");
	avb_ops_user_free(ops);

	return 0;
}

#define AT_PERM_ATTR_FUSE		1
#define AT_PERM_ATTR_CER_FUSE		2
#define AT_LOCK_VBOOT			3

int rk_avb_write_perm_attr(u16 id, void *pbuf, u16 size)
{
	uint8_t lock_state;
#ifndef CONFIG_ROCKCHIP_PRELOADER_PUB_KEY
	sha256_context ctx;
	uint8_t digest[SHA256_SUM_LEN] = {0};
	uint8_t digest_temp[SHA256_SUM_LEN] = {0};
	uint8_t perm_attr_temp[PERM_ATTR_TOTAL_SIZE] = {0};
	uint8_t flag = 0;
#endif

	switch (id) {
	case AT_PERM_ATTR_FUSE:
		if (size != PERM_ATTR_TOTAL_SIZE) {
			debug("%s Permanent attribute size is not equal!\n", __func__);
			return -EINVAL;
		}

#ifndef CONFIG_ROCKCHIP_PRELOADER_PUB_KEY
		if (rk_avb_read_perm_attr_flag(&flag)) {
			debug("%s rk_avb_read_perm_attr_flag error!\n", __func__);
			return -EIO;
		}

		if (flag == PERM_ATTR_SUCCESS_FLAG) {
			if (rk_avb_read_attribute_hash(digest_temp,
						       SHA256_SUM_LEN)) {
				debug("%s The efuse IO can not be used!\n", __func__);
				return -EIO;
			}

			if (memcmp(digest, digest_temp, SHA256_SUM_LEN) != 0) {
				if (rk_avb_read_permanent_attributes(perm_attr_temp,
								     PERM_ATTR_TOTAL_SIZE)) {
					debug("%s rk_avb_write_permanent_attributes error!\n", __func__);
					return -EIO;
				}

				sha256_starts(&ctx);
				sha256_update(&ctx,
					      (const uint8_t *)perm_attr_temp,
					      PERM_ATTR_TOTAL_SIZE);
				sha256_finish(&ctx, digest);
				if (memcmp(digest, digest_temp, SHA256_SUM_LEN) == 0) {
					debug("%s The hash has been written!\n", __func__);
					return 0;
				}
			}

			if (rk_avb_write_perm_attr_flag(0)) {
				debug("%s Perm attr flag write failure\n", __func__);
				return -EIO;
			}
		}
#endif
		if (rk_avb_write_permanent_attributes((uint8_t *)
						      pbuf,
						      size)) {
			if (rk_avb_write_perm_attr_flag(0)) {
				debug("%s Perm attr flag write failure\n", __func__);
				return -EIO;
			}

			debug("%s Perm attr write failed\n", __func__);
			return -EIO;
		}
#ifndef CONFIG_ROCKCHIP_PRELOADER_PUB_KEY
		memset(digest, 0, SHA256_SUM_LEN);
		sha256_starts(&ctx);
		sha256_update(&ctx, (const uint8_t *)pbuf,
			      PERM_ATTR_TOTAL_SIZE);
		sha256_finish(&ctx, digest);

		if (rk_avb_write_attribute_hash((uint8_t *)digest,
						SHA256_SUM_LEN)) {
			if (rk_avb_read_attribute_hash(digest_temp,
						       SHA256_SUM_LEN)) {
				debug("%s The efuse IO can not be used!\n", __func__);
				return -EIO;
			}

			if (memcmp(digest, digest_temp, SHA256_SUM_LEN) != 0) {
				if (rk_avb_write_perm_attr_flag(0)) {
					debug("%s Perm attr flag write failure\n", __func__);
					return -EIO;
				}
				debug("%s The hash has been written, but is different!\n", __func__);
				return -EIO;
			}
		}
#endif
		if (rk_avb_write_perm_attr_flag(PERM_ATTR_SUCCESS_FLAG)) {
			debug("%s, Perm attr flag write failure\n", __func__);
			return -EIO;
		}

		break;
	case AT_PERM_ATTR_CER_FUSE:
		if (size != 256) {
			debug("%s Permanent attribute rsahash size is not equal!\n",
			      __func__);
			return -EINVAL;
		}
		if (rk_avb_set_perm_attr_cer((uint8_t *)pbuf, size)) {
			debug("%s FAILSet perm attr cer fail!\n", __func__);
			return -EIO;
		}
		break;
	case AT_LOCK_VBOOT:
		lock_state = 0;
		if (rk_avb_write_lock_state(lock_state)) {
			debug("%s FAILwrite lock state failed\n", __func__);
			return -EIO;
		} else {
			debug("%s OKAY\n", __func__);
		}
		break;
	}
	return 0;
}

int rk_avb_read_perm_attr(u16 id, void *pbuf, u16 size)
{
	int ret = 0;
	debug("%s %d\n", __func__, size);

	switch (id) {
	case AT_PERM_ATTR_FUSE:
		size = PERM_ATTR_TOTAL_SIZE;
		ret = rk_avb_read_permanent_attributes((uint8_t *)pbuf, PERM_ATTR_TOTAL_SIZE);
		break;
	case AT_PERM_ATTR_CER_FUSE:
		size = PERM_ATTR_TOTAL_SIZE;
		ret = rk_avb_get_perm_attr_cer((uint8_t *)pbuf, 256);
		break;
	case AT_LOCK_VBOOT:
		break;
	}

	return ret;
}

int rk_avb_update_stored_rollback_indexes_for_slot(AvbOps* ops, AvbSlotVerifyData* slot_data)
{
	uint64_t rollback_index = slot_data->rollback_indexes[0];
	uint64_t current_stored_rollback_index;
	AvbIOResult io_ret;

	if (rollback_index > 0) {
		io_ret = ops->read_rollback_index(ops, 0, &current_stored_rollback_index);
		if (io_ret != AVB_IO_RESULT_OK)
			return -1;

		if (rollback_index > current_stored_rollback_index) {
			io_ret = ops->write_rollback_index(ops, 0, rollback_index);
			if (io_ret != AVB_IO_RESULT_OK)
				return -1;
		}
	}

	return 0;
}
