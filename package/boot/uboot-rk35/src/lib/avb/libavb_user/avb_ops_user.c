/*
 * Copyright (C) 2017 The Android Open Source Project
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
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
#include <stdio.h>
#include <android_avb/avb_ops_user.h>
#include <android_avb/libavb_ab.h>
#include <android_avb/avb_atx_validate.h>
#include <android_avb/avb_atx_types.h>
#include <optee_include/OpteeClientInterface.h>
#include <optee_include/tee_api_defines.h>
#include <android_avb/avb_vbmeta_image.h>
#include <android_avb/avb_atx_validate.h>
#include <boot_rkimg.h>

static void byte_to_block(int64_t *offset,
			  size_t *num_bytes,
			  lbaint_t *offset_blk,
			  lbaint_t *blkcnt)
{
	*offset_blk = (lbaint_t)(*offset / 512);
	if (*num_bytes % 512 == 0) {
		if (*offset % 512 == 0)
			*blkcnt = (lbaint_t)(*num_bytes / 512);
		else
			*blkcnt = (lbaint_t)(*num_bytes / 512) + 1;
	} else {
		if (*offset % 512 == 0) {
			*blkcnt = (lbaint_t)(*num_bytes / 512) + 1;
		} else {
			if ((*offset % 512) + (*num_bytes % 512) < 512 ||
			    (*offset % 512) + (*num_bytes % 512) == 512) {
				*blkcnt = (lbaint_t)(*num_bytes / 512) + 1;
			} else {
				*blkcnt = (lbaint_t)(*num_bytes / 512) + 2;
			}
		}
	}
}

static AvbIOResult get_size_of_partition(AvbOps *ops,
					 const char *partition,
					 uint64_t *out_size_in_bytes)
{
	struct blk_desc *dev_desc;
	disk_partition_t part_info;

	dev_desc = rockchip_get_bootdev();
	if (!dev_desc) {
		printf("%s: Could not find device\n", __func__);
		return AVB_IO_RESULT_ERROR_NO_SUCH_PARTITION;
	}

	if (part_get_info_by_name(dev_desc, partition, &part_info) < 0) {
		printf("Could not find \"%s\" partition\n", partition);
		return AVB_IO_RESULT_ERROR_NO_SUCH_PARTITION;
	}
	*out_size_in_bytes = (part_info.size) * 512;
	return AVB_IO_RESULT_OK;
}

static AvbIOResult read_from_partition(AvbOps *ops,
				       const char *partition,
				       int64_t offset,
				       size_t num_bytes,
				       void *buffer,
				       size_t *out_num_read)
{
	struct blk_desc *dev_desc;
	lbaint_t offset_blk, blkcnt;
	disk_partition_t part_info;
	uint64_t partition_size;

	if (offset < 0) {
		if (get_size_of_partition(ops, partition, &partition_size))
			return AVB_IO_RESULT_ERROR_NO_SUCH_PARTITION;

		if (-offset > partition_size)
			return AVB_IO_RESULT_ERROR_RANGE_OUTSIDE_PARTITION;

		offset = partition_size - (-offset);
	}

	byte_to_block(&offset, &num_bytes, &offset_blk, &blkcnt);
	dev_desc = rockchip_get_bootdev();
	if (!dev_desc) {
		printf("%s: Could not find device\n", __func__);
		return AVB_IO_RESULT_ERROR_NO_SUCH_PARTITION;
	}

	if (part_get_info_by_name(dev_desc, partition, &part_info) < 0) {
		printf("Could not find \"%s\" partition\n", partition);
		return AVB_IO_RESULT_ERROR_NO_SUCH_PARTITION;
	}

	if ((offset % 512 == 0) && (num_bytes % 512 == 0)) {
		blk_dread(dev_desc, part_info.start + offset_blk,
			  blkcnt, buffer);
		*out_num_read = blkcnt * 512;
	} else {
		char *buffer_temp;

		buffer_temp = malloc(512 * blkcnt);
		if (!buffer_temp) {
			printf("malloc error!\n");
			return AVB_IO_RESULT_ERROR_OOM;
		}
		blk_dread(dev_desc, part_info.start + offset_blk,
			  blkcnt, buffer_temp);
		memcpy(buffer, buffer_temp + (offset % 512), num_bytes);
		*out_num_read = num_bytes;
		free(buffer_temp);
	}

	return AVB_IO_RESULT_OK;
}

static AvbIOResult write_to_partition(AvbOps *ops,
				      const char *partition,
				      int64_t offset,
				      size_t num_bytes,
				      const void *buffer)
{
	struct blk_desc *dev_desc;
	char *buffer_temp;
	disk_partition_t part_info;
	lbaint_t offset_blk, blkcnt;

	byte_to_block(&offset, &num_bytes, &offset_blk, &blkcnt);
	buffer_temp = malloc(512 * blkcnt);
	if (!buffer_temp) {
		printf("malloc error!\n");
		return AVB_IO_RESULT_ERROR_OOM;
	}
	memset(buffer_temp, 0, 512 * blkcnt);
	dev_desc = rockchip_get_bootdev();
	if (!dev_desc) {
		printf("%s: Could not find device\n", __func__);
		return AVB_IO_RESULT_ERROR_NO_SUCH_PARTITION;
	}

	if (part_get_info_by_name(dev_desc, partition, &part_info) < 0) {
		printf("Could not find \"%s\" partition\n", partition);
		return AVB_IO_RESULT_ERROR_NO_SUCH_PARTITION;
	}

	if ((offset % 512 != 0) && (num_bytes % 512) != 0)
		blk_dread(dev_desc, part_info.start + offset_blk,
			  blkcnt, buffer_temp);

	memcpy(buffer_temp, buffer + (offset % 512), num_bytes);
	blk_dwrite(dev_desc, part_info.start + offset_blk, blkcnt, buffer);
	free(buffer_temp);

	return AVB_IO_RESULT_OK;
}

static AvbIOResult
validate_vbmeta_public_key(AvbOps *ops,
			   const uint8_t *public_key_data,
			   size_t public_key_length,
			   const uint8_t *public_key_metadata,
			   size_t public_key_metadata_length,
			   bool *out_is_trusted)
{
/* remain AVB_VBMETA_PUBLIC_KEY_VALIDATE to compatible legacy code */
#if defined(CONFIG_AVB_VBMETA_PUBLIC_KEY_VALIDATE) || \
    defined(AVB_VBMETA_PUBLIC_KEY_VALIDATE)
	if (out_is_trusted) {
		avb_atx_validate_vbmeta_public_key(ops,
						   public_key_data,
						   public_key_length,
						   public_key_metadata,
						   public_key_metadata_length,
						   out_is_trusted);
	}
#else
	if (out_is_trusted)
		*out_is_trusted = true;
#endif
	return AVB_IO_RESULT_OK;
}

static AvbIOResult read_rollback_index(AvbOps *ops,
				       size_t rollback_index_location,
				       uint64_t *out_rollback_index)
{
	if (out_rollback_index) {
#ifdef CONFIG_OPTEE_CLIENT
		int ret;

		ret = trusty_read_rollback_index(rollback_index_location,
						 out_rollback_index);
		switch (ret) {
		case TEE_SUCCESS:
			ret = AVB_IO_RESULT_OK;
			break;
		case TEE_ERROR_GENERIC:
		case TEE_ERROR_NO_DATA:
		case TEE_ERROR_ITEM_NOT_FOUND:
			*out_rollback_index = 0;
			ret = trusty_write_rollback_index(rollback_index_location,
							  *out_rollback_index);
			if (ret) {
				printf("%s: init rollback index error\n",
				       __FILE__);
				ret = AVB_IO_RESULT_ERROR_IO;
			} else {
				ret =
				trusty_read_rollback_index(rollback_index_location,
							   out_rollback_index);
				if (ret)
					ret = AVB_IO_RESULT_ERROR_IO;
				else
					ret = AVB_IO_RESULT_OK;
			}
			break;
		default:
			ret = AVB_IO_RESULT_ERROR_IO;
			printf("%s: trusty_read_rollback_index failed",
			       __FILE__);
		}

		return ret;
#else
		*out_rollback_index = 0;

		return AVB_IO_RESULT_OK;
#endif
	}

	return AVB_IO_RESULT_ERROR_IO;
}

static AvbIOResult write_rollback_index(AvbOps *ops,
					size_t rollback_index_location,
					uint64_t rollback_index)
{
#ifdef CONFIG_OPTEE_CLIENT
	if (trusty_write_rollback_index(rollback_index_location,
					rollback_index)) {
		printf("%s: Fail to write rollback index\n", __FILE__);
		return AVB_IO_RESULT_ERROR_IO;
	}
	return AVB_IO_RESULT_OK;
#endif
	return AVB_IO_RESULT_ERROR_IO;
}

static AvbIOResult read_is_device_unlocked(AvbOps *ops, bool *out_is_unlocked)
{
	if (out_is_unlocked) {
#ifdef CONFIG_OPTEE_CLIENT
		int ret;

		ret = trusty_read_lock_state((uint8_t *)out_is_unlocked);
		switch (ret) {
		case TEE_SUCCESS:
			ret = AVB_IO_RESULT_OK;
			break;
		case TEE_ERROR_GENERIC:
		case TEE_ERROR_NO_DATA:
		case TEE_ERROR_ITEM_NOT_FOUND:
			*out_is_unlocked = 1;
			if (trusty_write_lock_state(*out_is_unlocked)) {
				printf("%s: init lock state error\n", __FILE__);
				ret = AVB_IO_RESULT_ERROR_IO;
			} else {
				ret =
				trusty_read_lock_state((uint8_t *)out_is_unlocked);
				if (ret == 0)
					ret = AVB_IO_RESULT_OK;
				else
					ret = AVB_IO_RESULT_ERROR_IO;
			}
			break;
		default:
			ret = AVB_IO_RESULT_ERROR_IO;
			printf("%s: trusty_read_lock_state failed\n", __FILE__);
		}
		return ret;
#else
		*out_is_unlocked = 1;

		return AVB_IO_RESULT_OK;
#endif
	}
	return AVB_IO_RESULT_ERROR_IO;
}

static AvbIOResult write_is_device_unlocked(AvbOps *ops, bool *out_is_unlocked)
{
	if (out_is_unlocked) {
#ifdef CONFIG_OPTEE_CLIENT
		if (trusty_write_lock_state(*out_is_unlocked)) {
			printf("%s: Fail to write lock state\n", __FILE__);
			return AVB_IO_RESULT_ERROR_IO;
		}
		return AVB_IO_RESULT_OK;
#endif
	}
	return AVB_IO_RESULT_ERROR_IO;
}

static AvbIOResult get_unique_guid_for_partition(AvbOps *ops,
						 const char *partition,
						 char *guid_buf,
						 size_t guid_buf_size)
{
	struct blk_desc *dev_desc;
	disk_partition_t part_info;

	dev_desc = rockchip_get_bootdev();
	if (!dev_desc) {
		printf("%s: Could not find device\n", __func__);
		return AVB_IO_RESULT_ERROR_NO_SUCH_PARTITION;
	}

	if (part_get_info_by_name(dev_desc, partition, &part_info) < 0) {
		printf("Could not find \"%s\" partition\n", partition);
		return AVB_IO_RESULT_ERROR_NO_SUCH_PARTITION;
	}
	if (guid_buf && guid_buf_size > 0)
		memcpy(guid_buf, part_info.uuid, guid_buf_size);

	return AVB_IO_RESULT_OK;
}

/* read permanent attributes from rpmb */
AvbIOResult avb_read_perm_attr(AvbAtxOps *atx_ops,
			       AvbAtxPermanentAttributes *attributes)
{
	if (attributes) {
#ifdef CONFIG_OPTEE_CLIENT
		trusty_read_permanent_attributes((uint8_t *)attributes,
						 sizeof(struct AvbAtxPermanentAttributes));
		return AVB_IO_RESULT_OK;
#endif
	}

	return -1;
}

/*read permanent attributes hash from efuse */
AvbIOResult avb_read_perm_attr_hash(AvbAtxOps *atx_ops,
				    uint8_t hash[AVB_SHA256_DIGEST_SIZE])
{
#ifndef CONFIG_ROCKCHIP_PRELOADER_PUB_KEY
#ifdef CONFIG_OPTEE_CLIENT
	if (trusty_read_attribute_hash((uint32_t *)hash,
				       AVB_SHA256_DIGEST_SIZE / 4))
		return -1;
#else
	avb_error("Please open the macro!\n");
	return -1;
#endif
#endif
	return AVB_IO_RESULT_OK;
}

static void avb_set_key_version(AvbAtxOps *atx_ops,
				size_t rollback_index_location,
				uint64_t key_version)
{
#ifdef CONFIG_OPTEE_CLIENT
	uint64_t key_version_temp = 0;

	if (trusty_read_rollback_index(rollback_index_location, &key_version_temp))
		printf("%s: Fail to read rollback index\n", __FILE__);
	if (key_version_temp == key_version)
		return;
	if (trusty_write_rollback_index(rollback_index_location, key_version))
		printf("%s: Fail to write rollback index\n", __FILE__);
#endif
}

AvbIOResult rk_get_random(AvbAtxOps *atx_ops,
			  size_t num_bytes,
			  uint8_t *output)
{
	int i;
	unsigned int seed;

	seed = (unsigned int)get_timer(0);
	for (i = 0; i < num_bytes; i++) {
		srand(seed);
		output[i] = (uint8_t)(rand());
		seed = (unsigned int)(output[i]);
	}

	return 0;
}

#ifdef CONFIG_ANDROID_BOOT_IMAGE
static AvbIOResult get_preloaded_partition(AvbOps* ops,
					   const char* partition,
					   size_t num_bytes,
					   uint8_t** out_pointer,
					   size_t* out_num_bytes_preloaded,
					   int allow_verification_error)
{
	struct blk_desc *dev_desc;
	ulong load_addr;
	int ret;

	/* no need go further */
	if (!allow_verification_error)
		return AVB_IO_RESULT_OK;

	printf("get image from preloaded partition...\n");
	dev_desc = rockchip_get_bootdev();
	if (!dev_desc)
	    return AVB_IO_RESULT_ERROR_NO_SUCH_PARTITION;

	load_addr = env_get_ulong("kernel_addr_r", 16, 0);
	if (!load_addr)
		return AVB_IO_RESULT_ERROR_NO_SUCH_VALUE;

	ret = android_image_load_by_partname(dev_desc, partition, &load_addr);
	if (!ret) {
		*out_pointer = (u8 *)load_addr;
		*out_num_bytes_preloaded = num_bytes; /* return what it expects */
		ret = AVB_IO_RESULT_OK;
	} else {
		ret = AVB_IO_RESULT_ERROR_IO;
	}

	return ret;
}
#endif

AvbIOResult validate_public_key_for_partition(AvbOps *ops,
					      const char *partition,
					      const uint8_t *public_key_data,
					      size_t public_key_length,
					      const uint8_t *public_key_metadata,
					      size_t public_key_metadata_length,
					      bool *out_is_trusted,
					      uint32_t *out_rollback_index_location)
{
/* remain AVB_VBMETA_PUBLIC_KEY_VALIDATE to compatible legacy code */
#if defined(CONFIG_AVB_VBMETA_PUBLIC_KEY_VALIDATE) || \
    defined(AVB_VBMETA_PUBLIC_KEY_VALIDATE)
	if (out_is_trusted) {
		avb_atx_validate_vbmeta_public_key(ops,
						   public_key_data,
						   public_key_length,
						   public_key_metadata,
						   public_key_metadata_length,
						   out_is_trusted);
	}
#else
	if (out_is_trusted)
		*out_is_trusted = true;
#endif
	*out_rollback_index_location = 0;
	return AVB_IO_RESULT_OK;
}

AvbOps *avb_ops_user_new(void)
{
	AvbOps *ops;

	ops = calloc(1, sizeof(AvbOps));
	if (!ops) {
		printf("Error allocating memory for AvbOps.\n");
		goto out;
	}
	ops->ab_ops = calloc(1, sizeof(AvbABOps));
	if (!ops->ab_ops) {
		printf("Error allocating memory for AvbABOps.\n");
		free(ops);
		goto out;
	}

	ops->atx_ops = calloc(1, sizeof(AvbAtxOps));
	if (!ops->atx_ops) {
		printf("Error allocating memory for AvbAtxOps.\n");
		free(ops->ab_ops);
		free(ops);
		goto out;
	}
	ops->ab_ops->ops = ops;
	ops->atx_ops->ops = ops;

	ops->read_from_partition = read_from_partition;
	ops->write_to_partition = write_to_partition;
	ops->validate_vbmeta_public_key = validate_vbmeta_public_key;
	ops->read_rollback_index = read_rollback_index;
	ops->write_rollback_index = write_rollback_index;
	ops->read_is_device_unlocked = read_is_device_unlocked;
	ops->write_is_device_unlocked = write_is_device_unlocked;
	ops->get_unique_guid_for_partition = get_unique_guid_for_partition;
	ops->get_size_of_partition = get_size_of_partition;
#ifdef CONFIG_ANDROID_BOOT_IMAGE
	ops->get_preloaded_partition = get_preloaded_partition;
#endif
	ops->validate_public_key_for_partition = validate_public_key_for_partition;
	ops->ab_ops->read_ab_metadata = avb_ab_data_read;
	ops->ab_ops->write_ab_metadata = avb_ab_data_write;
	ops->atx_ops->read_permanent_attributes = avb_read_perm_attr;
	ops->atx_ops->read_permanent_attributes_hash = avb_read_perm_attr_hash;
	ops->atx_ops->set_key_version = avb_set_key_version;
	ops->atx_ops->get_random = rk_get_random;

out:
	return ops;
}

void avb_ops_user_free(AvbOps *ops)
{
	free(ops->ab_ops);
	free(ops->atx_ops);
	free(ops);
}
