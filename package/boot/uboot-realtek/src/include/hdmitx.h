/*
 * hdmitx.h - RTK hdmitx driver header file
 *
 * Copyright (C) 2017 Realtek Semiconductor Corporation
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

enum HDMI_FORMAT_MODE {
	FORMAT_MODE_OFF = 0,
	FORMAT_MODE_DVI = 1,
	FORMAT_MODE_HDMI = 2,
};

enum HDMI_VIDEO_ID_CODE {
	VIC_720X480P60 = 2,
	VIC_1280X720P60 = 4,
	VIC_1920X1080I60 = 5,
	VIC_720X480I60 = 6,
	VIC_1920X1080P60 = 16,
	VIC_720X576P50 = 17,
	VIC_1280X720P50 = 19,
	VIC_1920X1080I50 = 20,
	VIC_720X576I50 = 21,
	VIC_1920X1080P50 = 31,
	VIC_1920X1080P24 = 32,
	VIC_1920X1080P25 = 33,
	VIC_1920X1080P30 = 34,
	VIC_3840X2160P24 = 93,
	VIC_3840X2160P25 = 94,
	VIC_3840X2160P30 = 95,
	VIC_3840X2160P50 = 96,
	VIC_3840X2160P60 = 97,
	VIC_4096X2160P24 = 98,
	VIC_4096X2160P25 = 99,
	VIC_4096X2160P30 = 100,
	VIC_4096X2160P50 = 101,
	VIC_4096X2160P60 = 102,
};

enum HDMI_COLOR_FORMAT {
	COLOR_RGB444 = 0,
	COLOR_YUV422 = 1,
	COLOR_YUV444 = 2,
	COLOR_YUV420 = 3,
};

enum HDMI_3D_MODE {
	FORMAT_3D_OFF = 0,
	/* Frame Packing */
	FORMAT_3D_FP = 1,
	/* Side by side half */
	FORMAT_3D_SS = 2,
	/* Top and Buttom */
	FORMAT_3D_TB = 3,
};

enum HDMI_HDR_MODE {
	HDR_MODE_OFF = 0,
	/* Dolby Vision */
	HDR_MODE_DV = 1,
	HDR_MODE_SDR = 2,
	HDR_MODE_GAMMA =3,
	/* HDR10 */
	HDR_MODE_HDR10 = 4,
	/* reserved future */
	HDR_MODE_FUTURE = 5,
	/* SDR/HDR by video */
	HDR_MODE_INPUT = 6,
};

/**
 * struct hdmi_format_setting - HDMI output format setting
 * @mode: 0-OFF; 1-DVI; 2-HDMI
 * @vic: Video ID code
 * @freq_shift: 0-No freq shift, 1-set freq shift
 * @color: 0-RGB444; 1-YUV422; 2-YUV444; 3-YUV420
 * @color_depth: 8-8bit, 10-10bit, 12-12bit
 * @_3d_format: enum HDMI_3D_MODE
 * @hdr: enum HDMI_HDR_MODE
 */
struct hdmi_format_setting {
	unsigned char mode;
	unsigned char vic;
	unsigned char freq_shift;
	unsigned char color;
	unsigned char color_depth;
	unsigned char _3d_format;
	unsigned char hdr;
	unsigned char reserved;
};

/**
 * struct ONE_STEP_INFO
 * @mHeaderFormat: The first three character should be 'F' 'M' 'T'
 * @mSetting: One step format
 * @mHeaderEDIDCheckSum: should be 'E' 'D' 'I' 'D'
 * @mChecksum: One step EDID checksum
 */
#define ONE_STEP_INFO_HDR_LEN   16
struct ONE_STEP_INFO {
	unsigned char mHeaderFormat[ONE_STEP_INFO_HDR_LEN];
	struct hdmi_format_setting mSetting;
	unsigned char mHeaderEDIDCheckSum[ONE_STEP_INFO_HDR_LEN];
	unsigned char mChecksum[2];
	unsigned char reserved[6];
};

int set_hdmitx_format(struct hdmi_format_setting *format);

