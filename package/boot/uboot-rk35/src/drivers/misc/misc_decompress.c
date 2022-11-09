// SPDX-License-Identifier:     GPL-2.0+
/*
 * Copyright (C) 2020 Rockchip Electronics Co., Ltd
 */
#include <common.h>
#include <dm.h>
#include <misc.h>
#include <dm/uclass.h>
#include <dm/uclass-internal.h>

#define HEAD_CRC		2
#define EXTRA_FIELD		4
#define ORIG_NAME		8
#define COMMENT			0x10
#define RESERVED		0xe0
#define DEFLATED		8

static u32 misc_decomp_async, misc_decomp_sync;

static void decomp_set_flags(u32 *flags, u8 comp)
{
	if (comp == IH_COMP_GZIP)
		*flags |= DECOM_GZIP;
	else if (comp == IH_COMP_LZ4)
		*flags |= DECOM_LZ4;
}

void misc_decompress_async(u8 comp)
{
	decomp_set_flags(&misc_decomp_async, comp);
}

void misc_decompress_sync(u8 comp)
{
	decomp_set_flags(&misc_decomp_sync, comp);
}

static int misc_gzip_parse_header(const unsigned char *src, unsigned long len)
{
	int i, flags;

	/* skip header */
	i = 10;
	flags = src[3];
	if (src[2] != DEFLATED || (flags & RESERVED) != 0) {
		debug("Error: Bad gzipped data\n");
		return (-1);
	}
	if ((flags & EXTRA_FIELD) != 0)
		i = 12 + src[10] + (src[11] << 8);
	if ((flags & ORIG_NAME) != 0)
		while (src[i++] != 0)
			;
	if ((flags & COMMENT) != 0)
		while (src[i++] != 0)
			;
	if ((flags & HEAD_CRC) != 0)
		i += 2;
	if (i >= len) {
		puts("Error: gunzip out of data in header\n");
		return (-1);
	}
	return i;
}

static int misc_lz4_header_is_valid(const unsigned char *h)
{
	const struct lz4_frame_header *hdr  = (const struct lz4_frame_header *)h;
	/* We assume there's always only a single, standard frame. */
	if (le32_to_cpu(hdr->magic) != LZ4F_MAGIC || hdr->version != 1)
		return 0;        /* unknown format */
	if (hdr->reserved0 || hdr->reserved1 || hdr->reserved2)
		return 0; /* reserved must be zero */
	if (!hdr->independent_blocks)
		return 0; /* we can't support this yet */

	return 1;
}

static u64 misc_get_data_size(unsigned long src, unsigned long len, u32 comp)
{
	u64 size = 0;

	if (comp == DECOM_GZIP) {
		size = *(u32 *)(src + len - 4);
	} else if (comp == DECOM_LZ4) {
		const struct lz4_frame_header *hdr =
			(const struct lz4_frame_header *)src;
		/*
		 * Here is the way to add size information in image:
		 *
		 * 1. lz4 command use arg: --content-size.
		 * 2. append u32 size at the end of image as kernel does.
		 */
		size = hdr->has_content_size ?
			*(u64 *)(src + sizeof(*hdr)) : *(u32 *)(src + len - 4);
	}

	return size;
}

static void misc_setup_default_sync(u32 comp)
{
	if (comp == DECOM_GZIP)
		misc_decompress_sync(IH_COMP_GZIP);
	else if (comp == DECOM_LZ4)
		misc_decompress_sync(IH_COMP_LZ4);
}

static struct udevice *misc_decompress_get_device(u32 comp)
{
	return misc_get_device_by_capability(comp);
}

static int misc_decompress_start(struct udevice *dev, unsigned long dst,
				 unsigned long src, unsigned long src_len,
				 u32 flags)
{
	struct decom_param param;

	param.addr_dst = dst;
	param.addr_src = src;
	param.flags = flags;
	if (misc_gzip_parse_header((unsigned char *)src, 0xffff) > 0) {
		param.mode = DECOM_GZIP;
	} else if (misc_lz4_header_is_valid((void *)src)) {
		param.mode = DECOM_LZ4;
	} else {
		printf("Unsupported decompression format.\n");
		return -EPERM;
	}

	param.size_src = src_len;
	param.size_dst = misc_get_data_size(src, src_len, param.mode);

	if (!param.size_src || !param.size_dst)
		return -EINVAL;

	return misc_ioctl(dev, IOCTL_REQ_START, &param);
}

static int misc_decompress_stop(struct udevice *dev)
{
	return misc_ioctl(dev, IOCTL_REQ_STOP, NULL);
}

static bool misc_decompress_is_complete(struct udevice *dev)
{
	if (misc_ioctl(dev, IOCTL_REQ_POLL, NULL))
		return false;
	else
		return true;
}

static int misc_decompress_data_size(struct udevice *dev, u64 *size, u32 comp)
{
	struct decom_param param;
	int ret;

	param.mode = comp;
	param.size_dst = 0; /* clear */

	ret = misc_ioctl(dev, IOCTL_REQ_DATA_SIZE, &param);
	if (!ret)
		*size = param.size_dst;

	return ret;
}

static int misc_decompress_finish(struct udevice *dev, u32 comp)
{
	int timeout = 200000;	/* 2s */

	while (!misc_decompress_is_complete(dev)) {
		if (timeout < 0)
			return -ETIMEDOUT;
		timeout--;
		udelay(10);
	}

	return misc_decompress_stop(dev);
}

int misc_decompress_cleanup(void)
{
	const struct misc_ops *ops;
	struct udevice *dev;
	struct uclass *uc;
	int ret;
	u32 comp;

	ret = uclass_get(UCLASS_MISC, &uc);
	if (ret)
		return 0;

	/* use "find_" */
	for (uclass_find_first_device(UCLASS_MISC, &dev);
	     dev;
	     uclass_find_next_device(&dev)) {
		ops = device_get_ops(dev);
		if (!ops || !ops->ioctl)
			continue;
		else if (ops->ioctl(dev, IOCTL_REQ_CAPABILITY, &comp))
			continue;
		else if (misc_decomp_async & comp)
			continue;

		if (misc_decomp_sync & comp) {
			ret = misc_decompress_finish(dev, comp);
			if (ret) {
				printf("Failed to stop decompress: %s, ret=%d\n",
				       dev->name, ret);
				return ret;
			}
		}
	}

	return 0;
}

int misc_decompress_process(unsigned long dst, unsigned long src,
			    unsigned long src_len, u32 comp, bool sync,
			    u64 *size, u32 flags)
{
	struct udevice *dev;
	ulong dst_org = dst;
	u64 dst_size = 0;
	int ret;

	dev = misc_decompress_get_device(comp);
	if (!dev)
		return -ENODEV;

	/* Wait last finish */
	ret = misc_decompress_finish(dev, comp);
	if (ret)
		return ret;

	/*
	 * Check if ARCH_DMA_MINALIGN aligned, otherwise use sync action
	 * for output data memcpy.
	 */
	if (!IS_ALIGNED(dst, ARCH_DMA_MINALIGN)) {
		dst_org = dst;
		dst = ALIGN(dst, ARCH_DMA_MINALIGN);
		sync = true;
	}

	ret = misc_decompress_start(dev, dst, src, src_len, flags);
	if (ret)
		return ret;

	/*
	 * Wait this round finish ?
	 *
	 * If sync, return original data length after decompress done.
	 * otherwise return from compressed file information.
	 */
	if (sync) {
		ret = misc_decompress_finish(dev, comp);
		if (ret)
			return ret;

		if (size || (dst != dst_org)) {
			ret = misc_decompress_data_size(dev, &dst_size, comp);
			if (size)
				*size = dst_size;
			if (dst != dst_org)
				memcpy((char *)dst_org,
				       (const char *)dst, dst_size);
		}
	} else {
		/*
		 * setup cleanup sync flags by default if this is a sync request,
		 * unless misc_decompress_async() is called by manual.
		 *
		 * This avoid caller to forget to setup cleanup sync flags when
		 * they use a async operation, otherwise cpu jump to kernel
		 * before decompress done.
		 */
		misc_setup_default_sync(comp);

		if (size)
			*size = misc_get_data_size(src, src_len, comp);
	}

	return ret;
}
