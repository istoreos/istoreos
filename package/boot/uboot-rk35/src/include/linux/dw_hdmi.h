/*
 * Copyright (C) 2011 Freescale Semiconductor, Inc.
 * (C) Copyright 2008-2017 Fuzhou Rockchip Electronics Co., Ltd
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */
#ifndef __DW_HDMI__
#define __DW_HDMI__

struct dw_hdmi;
struct drm_display_mode;
struct ddc_adapter;
struct i2c_msg;

/**
 * DOC: Supported input formats and encodings
 *
 * Depending on the Hardware configuration of the Controller IP, it supports
 * a subset of the following input formats and encodings on its internal
 * 48bit bus.
 *
 * +----------------------+----------------------------------+------------------------------+
 * + Format Name          + Format Code                      + Encodings                    +
 * +----------------------+----------------------------------+------------------------------+
 * + RGB 4:4:4 8bit       + ``MEDIA_BUS_FMT_RGB888_1X24``    + ``V4L2_YCBCR_ENC_DEFAULT``   +
 * +----------------------+----------------------------------+------------------------------+
 * + RGB 4:4:4 10bits     + ``MEDIA_BUS_FMT_RGB101010_1X30`` + ``V4L2_YCBCR_ENC_DEFAULT``   +
 * +----------------------+----------------------------------+------------------------------+
 * + RGB 4:4:4 12bits     + ``MEDIA_BUS_FMT_RGB121212_1X36`` + ``V4L2_YCBCR_ENC_DEFAULT``   +
 * +----------------------+----------------------------------+------------------------------+
 * + RGB 4:4:4 16bits     + ``MEDIA_BUS_FMT_RGB161616_1X48`` + ``V4L2_YCBCR_ENC_DEFAULT``   +
 * +----------------------+----------------------------------+------------------------------+
 * + YCbCr 4:4:4 8bit     + ``MEDIA_BUS_FMT_YUV8_1X24``      + ``V4L2_YCBCR_ENC_601``       +
 * +                      +                                  + or ``V4L2_YCBCR_ENC_709``    +
 * +                      +                                  + or ``V4L2_YCBCR_ENC_XV601``  +
 * +                      +                                  + or ``V4L2_YCBCR_ENC_XV709``  +
 * +----------------------+----------------------------------+------------------------------+
 * + YCbCr 4:4:4 10bits   + ``MEDIA_BUS_FMT_YUV10_1X30``     + ``V4L2_YCBCR_ENC_601``       +
 * +                      +                                  + or ``V4L2_YCBCR_ENC_709``    +
 * +                      +                                  + or ``V4L2_YCBCR_ENC_XV601``  +
 * +                      +                                  + or ``V4L2_YCBCR_ENC_XV709``  +
 * +----------------------+----------------------------------+------------------------------+
 * + YCbCr 4:4:4 12bits   + ``MEDIA_BUS_FMT_YUV12_1X36``     + ``V4L2_YCBCR_ENC_601``       +
 * +                      +                                  + or ``V4L2_YCBCR_ENC_709``    +
 * +                      +                                  + or ``V4L2_YCBCR_ENC_XV601``  +
 * +                      +                                  + or ``V4L2_YCBCR_ENC_XV709``  +
 * +----------------------+----------------------------------+------------------------------+
 * + YCbCr 4:4:4 16bits   + ``MEDIA_BUS_FMT_YUV16_1X48``     + ``V4L2_YCBCR_ENC_601``       +
 * +                      +                                  + or ``V4L2_YCBCR_ENC_709``    +
 * +                      +                                  + or ``V4L2_YCBCR_ENC_XV601``  +
 * +                      +                                  + or ``V4L2_YCBCR_ENC_XV709``  +
 * +----------------------+----------------------------------+------------------------------+
 * + YCbCr 4:2:2 8bit     + ``MEDIA_BUS_FMT_UYVY8_1X16``     + ``V4L2_YCBCR_ENC_601``       +
 * +                      +                                  + or ``V4L2_YCBCR_ENC_709``    +
 * +----------------------+----------------------------------+------------------------------+
 * + YCbCr 4:2:2 10bits   + ``MEDIA_BUS_FMT_UYVY10_1X20``    + ``V4L2_YCBCR_ENC_601``       +
 * +                      +                                  + or ``V4L2_YCBCR_ENC_709``    +
 * +----------------------+----------------------------------+------------------------------+
 * + YCbCr 4:2:2 12bits   + ``MEDIA_BUS_FMT_UYVY12_1X24``    + ``V4L2_YCBCR_ENC_601``       +
 * +                      +                                  + or ``V4L2_YCBCR_ENC_709``    +
 * +----------------------+----------------------------------+------------------------------+
 * + YCbCr 4:2:0 8bit     + ``MEDIA_BUS_FMT_UYYVYY8_0_5X24`` + ``V4L2_YCBCR_ENC_601``       +
 * +                      +                                  + or ``V4L2_YCBCR_ENC_709``    +
 * +----------------------+----------------------------------+------------------------------+
 * + YCbCr 4:2:0 10bits   + ``MEDIA_BUS_FMT_UYYVYY10_0_5X30``+ ``V4L2_YCBCR_ENC_601``       +
 * +                      +                                  + or ``V4L2_YCBCR_ENC_709``    +
 * +----------------------+----------------------------------+------------------------------+
 * + YCbCr 4:2:0 12bits   + ``MEDIA_BUS_FMT_UYYVYY12_0_5X36``+ ``V4L2_YCBCR_ENC_601``       +
 * +                      +                                  + or ``V4L2_YCBCR_ENC_709``    +
 * +----------------------+----------------------------------+------------------------------+
 * + YCbCr 4:2:0 16bits   + ``MEDIA_BUS_FMT_UYYVYY16_0_5X48``+ ``V4L2_YCBCR_ENC_601``       +
 * +                      +                                  + or ``V4L2_YCBCR_ENC_709``    +
 * +----------------------+----------------------------------+------------------------------+
 */

enum {
	DW_HDMI_RES_8,
	DW_HDMI_RES_10,
	DW_HDMI_RES_12,
	DW_HDMI_RES_MAX,
};

enum dw_hdmi_devtype {
	IMX6Q_HDMI,
	IMX6DL_HDMI,
	RK3228_HDMI,
	RK3288_HDMI,
	RK3328_HDMI,
	RK3366_HDMI,
	RK3368_HDMI,
	RK3399_HDMI,
	RK3568_HDMI,
};

struct dw_hdmi_audio_tmds_n {
	unsigned long tmds;
	unsigned int n_32k;
	unsigned int n_44k1;
	unsigned int n_48k;
};

enum dw_hdmi_phy_type {
	DW_HDMI_PHY_DWC_HDMI_TX_PHY = 0x00,
	DW_HDMI_PHY_DWC_MHL_PHY_HEAC = 0xb2,
	DW_HDMI_PHY_DWC_MHL_PHY = 0xc2,
	DW_HDMI_PHY_DWC_HDMI_3D_TX_PHY_HEAC = 0xe2,
	DW_HDMI_PHY_DWC_HDMI_3D_TX_PHY = 0xf2,
	DW_HDMI_PHY_DWC_HDMI20_TX_PHY = 0xf3,
	DW_HDMI_PHY_VENDOR_PHY = 0xfe,
};

struct dw_hdmi_mpll_config {
	unsigned long mpixelclock;
	struct {
		u16 cpce;
		u16 gmp;
	} res[DW_HDMI_RES_MAX];
};

struct dw_hdmi_curr_ctrl {
	unsigned long mpixelclock;
	u16 curr[DW_HDMI_RES_MAX];
};

struct dw_hdmi_phy_config {
	unsigned long mpixelclock;
	u16 sym_ctr;    /*clock symbol and transmitter control*/
	u16 term;       /*transmission termination value*/
	u16 vlev_ctr;   /* voltage level control */
};

struct dw_hdmi_phy_ops {
	int (*init)(struct dw_hdmi *hdmi, void *data);
	void (*disable)(struct dw_hdmi *hdmi, void *data);
	enum drm_connector_status (*read_hpd)(struct dw_hdmi *hdmi,
					      void *data);
	void (*mode_valid)(struct dw_hdmi *hdmi, void *data);
};

struct dw_hdmi_qp_phy_ops {
	int (*init)(void *hdmi, void *data);
	void (*disable)(void *hdmi, void *data);
	enum drm_connector_status (*read_hpd)(void *data);
	void (*mode_valid)(void *hdmi, void *data);
	void (*set_pll)(void *hdmi, void *data);
};

struct dw_hdmi_link_config {
	bool dsc_mode;
	bool frl_mode;
	int frl_lanes;
	int rate_per_lane;
	int hcactive;
	u8 pps_payload[128];
};

struct dw_hdmi_plat_data {
	enum dw_hdmi_devtype dev_type;
	unsigned long input_bus_format;
	unsigned long input_bus_encoding;
	u32 vop_sel_bit;
	u32 grf_vop_sel_reg;
	/* Vendor PHY support */
	const struct dw_hdmi_phy_ops *phy_ops;
	const struct dw_hdmi_qp_phy_ops *qp_phy_ops;
	const struct dw_hdmi_audio_tmds_n *tmds_n_table;
	const char *phy_name;
	void *phy_data;
	void *hdmi;

	/* Synopsys PHY support */
	const struct dw_hdmi_mpll_config *mpll_cfg;
	const struct dw_hdmi_mpll_config *mpll_cfg_420;
	const struct dw_hdmi_curr_ctrl *cur_ctr;
	const struct dw_hdmi_phy_config *phy_config;
	int (*configure_phy)(struct dw_hdmi *hdmi,
			     const struct dw_hdmi_plat_data *pdata,
			     unsigned long mpixelclock);
	unsigned long (*get_input_bus_format)(void *data);
	unsigned long (*get_output_bus_format)(void *data);
	unsigned long (*get_enc_in_encoding)(void *data);
	unsigned long (*get_enc_out_encoding)(void *data);
	unsigned long (*get_quant_range)(void *data);
};

#endif /* __IMX_HDMI_H__ */
