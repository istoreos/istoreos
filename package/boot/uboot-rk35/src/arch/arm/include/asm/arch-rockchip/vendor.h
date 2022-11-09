/*
 * (C) Copyright 2008-2017 Fuzhou Rockchip Electronics Co., Ltd
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */
#ifndef __ROCKCHIP_VENDOR_
#define __ROCKCHIP_VENDOR_

#define RSV_ID				0
#define SN_ID				1
#define WIFI_MAC_ID			2
#define LAN_MAC_ID			3
#define BT_MAC_ID			4
#define HDCP_14_HDMI_ID			5
#define HDCP_14_DP_ID			6
#define HDCP_2X_ID			7
#define DRM_KEY_ID			8
#define PLAYREADY_CERT_ID		9
#define ATTENTION_KEY_ID		10
#define PLAYREADY_ROOT_KEY_0_ID		11
#define PLAYREADY_ROOT_KEY_1_ID		12
#define HDCP_14_HDMIRX_ID		13
#define SENSOR_CALIBRATION_ID		14
#define IMEI_ID				15
#define LAN_RGMII_DL_ID			16
#define EINK_VCOM_ID			17
#define FIRMWARE_VER_ID			18

struct vendor_item {
	u16  id;
	u16  offset;
	u16  size;
	u16  flag;
};

int vendor_storage_test(void);
int vendor_storage_read(u16 id, void *pbuf, u16 size);
int vendor_storage_write(u16 id, void *pbuf, u16 size);
int flash_vendor_dev_ops_register(int (*read)(struct blk_desc *dev_desc,
					      u32 sec,
					      u32 n_sec,
					      void *p_data),
				  int (*write)(struct blk_desc *dev_desc,
					       u32 sec,
					       u32 n_sec,
					       void *p_data));

int vendor_handle_hdcp(struct vendor_item *vhead);
#endif /* _ROCKCHIP_VENDOR_ */
