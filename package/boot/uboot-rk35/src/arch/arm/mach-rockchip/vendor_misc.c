/*
 * Copyright 2022 Rockchip Electronics Co., Ltd
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <common.h>
#include <asm/arch-rockchip/rockchip_smccc.h>
#include <asm/arch-rockchip/vendor.h>

#define HDCP_SIGNED		0x4B534541	/* "AESK" */
#define HDCP_FLG_AES		(1 << 0)

struct hdcpdata {
	unsigned int signature;
	unsigned int length;
	unsigned int crc32;
	unsigned int flags;
	unsigned char data[0];
};

int vendor_handle_hdcp(struct vendor_item *vhead)
{
	struct arm_smccc_res res;
	struct hdcpdata *hdcp;
	char *shm;
	u32 crc, len;
	int ret;

	hdcp = (void *)vhead + sizeof(struct vendor_item);
	if ((hdcp->signature != HDCP_SIGNED) || !(hdcp->flags & HDCP_FLG_AES))
		return 0;

	crc = crc32(0, hdcp->data, hdcp->length);
	if (crc != hdcp->crc32) {
		printf("%s: bad crc32 0x%08x != 0x%08x\n",
		       __func__, crc, hdcp->crc32);
		return -EIO;
	}

	res = sip_smc_request_share_mem(2, SHARE_PAGE_TYPE_HDCP);
	if (res.a0) {
		printf("%s: Can't get share mem\n", __func__);
		return -EIO;
	}

	shm = (char *)res.a1;
	len = sizeof(struct hdcpdata) + hdcp->length;

	memcpy(shm, hdcp, len);
	flush_dcache_range((ulong)shm, (ulong)(shm + len));

	ret = sip_smc_hdcp_config(HDCP_FUNC_STORAGE_ENCRYPT, 0, 0);
	if (ret) {
		printf("%s: failed, ret=%d\n", __func__, ret);
		return -EIO;
	}

	invalidate_dcache_range((ulong)shm, (ulong)(shm + len));
	memcpy(hdcp, shm, len);

	return 0;
}

