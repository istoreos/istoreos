/*
 * hdmitx.c - RTK hdmitx driver
 *
 * Copyright (C) 2017 Realtek Semiconductor Corporation
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */
#include <common.h>
#include <malloc.h>
#include <asm/arch/system.h>

#include "rtk_rpc.h"
#include "rtk_edid.h"
#include "rtk_avi_infoframe.h"
#include "hdmitx.h"

#define xvYCC601 0x01
#define xvYCC709 0x02
#define BT2020_YCC 0x40
#define BT2020_RGB 0x80

extern struct edid_hdmi2p0_info hdmi2p0_info;
extern int hdmitx_send_scdc_TmdsConfig(unsigned int standard, unsigned int dataInt0);
extern void set_one_step_info(struct VIDEO_RPC_VOUT_CONFIG_TV_SYSTEM *tv_system);

unsigned int vic_to_vo_standard(unsigned char vic, unsigned char freq_shift, unsigned char color, unsigned char en_3d)
{
	unsigned int ret_val;

	switch (vic) {
	case VIC_720X480P60:
		if (en_3d)
			ret_val = VO_STANDARD_ERROR;
		else
			ret_val = VO_STANDARD_NTSC_J;
		break;
	case VIC_1280X720P60:
		if (freq_shift) {
			if (en_3d)
				ret_val = VO_STANDARD_HDTV_720P_59_3D;
			else
				ret_val = VO_STANDARD_HDTV_720P_59;
		} else {
			if (en_3d)
				ret_val = VO_STANDARD_HDTV_720P_60_3D;
			else
				ret_val = VO_STANDARD_HDTV_720P_60;
		}
		break;
	case VIC_1920X1080I60:
		if (freq_shift) {
			if (en_3d)
				ret_val = VO_STANDARD_HDTV_1080I_59_3D;
			else
				ret_val = VO_STANDARD_HDTV_1080I_59;
		} else {
			if (en_3d)
				ret_val = VO_STANDARD_HDTV_1080I_60_3D;
			else
				ret_val = VO_STANDARD_HDTV_1080I_60;
		}
		break;
	case VIC_720X480I60:
		if (en_3d)
			ret_val = VO_STANDARD_ERROR;
		else
			ret_val = VO_STANDARD_NTSC_J;
		break;
	case VIC_1920X1080P60:
		if (freq_shift) {
			if (en_3d)
				ret_val = VO_STANDARD_ERROR;
			else
				ret_val = VO_STANDARD_HDTV_1080P_59;
		} else {
			if (en_3d)
				ret_val = VO_STANDARD_HDTV_1080P_60_3D;
			else
				ret_val = VO_STANDARD_HDTV_1080P_60;
		}
		break;
	case VIC_720X576P50:
		if (en_3d)
			ret_val = VO_STANDARD_ERROR;
		else
			ret_val = VO_STANDARD_PAL_I;
		break;
	case VIC_1280X720P50:
		if (freq_shift) {
			ret_val = VO_STANDARD_ERROR;
		} else {
			if (en_3d)
				ret_val = VO_STANDARD_HDTV_720P_50_3D;
			else
				ret_val = VO_STANDARD_HDTV_720P_50;
		}
		break;
	case VIC_1920X1080I50:
		if (freq_shift)
			ret_val = VO_STANDARD_ERROR;
		else if (en_3d)
			ret_val = VO_STANDARD_HDTV_1080I_50_3D;
		else
			ret_val = VO_STANDARD_HDTV_1080I_50;
		break;
	case VIC_720X576I50:
		if (en_3d)
			ret_val = VO_STANDARD_ERROR;
		else
			ret_val = VO_STANDARD_PAL_I;
		break;
	case VIC_1920X1080P50:
		if (freq_shift)
			ret_val = VO_STANDARD_ERROR;
		else if (en_3d)
			ret_val = VO_STANDARD_HDTV_1080P_50_3D;
		else
			ret_val = VO_STANDARD_HDTV_1080P_50;
		break;
	case VIC_1920X1080P24:
		if (freq_shift) {
			if (en_3d)
				ret_val = VO_STANDARD_HDTV_1080P_23_3D;
			else
				ret_val = VO_STANDARD_HDTV_1080P_23;
		} else {
			if (en_3d)
				ret_val = VO_STANDARD_HDTV_1080P_24_3D;
			else
				ret_val = VO_STANDARD_HDTV_1080P_24;
		}
		break;
	case VIC_1920X1080P25:
		if (freq_shift || en_3d)
			ret_val = VO_STANDARD_ERROR;
		else
			ret_val = VO_STANDARD_HDTV_1080P_25;
		break;
	case VIC_1920X1080P30:
		if (freq_shift)
			ret_val = VO_STANDARD_ERROR;
		else if (en_3d)
			ret_val = VO_STANDARD_HDTV_1080P_30_3D;
		else
			ret_val = VO_STANDARD_HDTV_1080P_30;
		break;
	case VIC_3840X2160P24:
		if (freq_shift) {
			if (en_3d)
				ret_val = VO_STANDARD_HDTV_2160P_23_3D;
			else
				ret_val = VO_STANDARD_HDTV_2160P_23;
		} else {
			if (en_3d)
				ret_val = VO_STANDARD_HDTV_2160P_24_3D;
			else
				ret_val = VO_STANDARD_HDTV_2160P_24;
		}
		break;
	case VIC_3840X2160P25:
		if (freq_shift)
			ret_val = VO_STANDARD_ERROR;
		else if (en_3d)
			ret_val = VO_STANDARD_HDTV_2160P_25_3D;
		else
			ret_val = VO_STANDARD_HDTV_2160P_25;
		break;
	case VIC_3840X2160P30:
		if (freq_shift) {
			if (en_3d)
				ret_val = VO_STANDARD_ERROR;
			else
				ret_val = VO_STANDARD_HDTV_2160P_29;
		} else {
			if (en_3d)
				ret_val = VO_STANDARD_HDTV_2160P_30_3D;
			else
				ret_val = VO_STANDARD_HDTV_2160P_30;
		}
		break;
	case VIC_3840X2160P50:
		if (color == COLOR_YUV420) {
			if (freq_shift || en_3d)
				ret_val = VO_STANDARD_ERROR;
			else
				ret_val = VO_STANDARD_HDTV_2160P_50_420;
		} else {
			if (freq_shift) {
				ret_val = VO_STANDARD_ERROR;
			} else {
				if (en_3d)
					ret_val = VO_STANDARD_HDTV_2160P_50_3D;
				else
					ret_val = VO_STANDARD_HDTV_2160P_50;
			}
		}
		break;
	case VIC_3840X2160P60:
		if (color == COLOR_YUV420) {
			if (en_3d)
				ret_val = VO_STANDARD_ERROR;
			else if (freq_shift)
				ret_val = VO_STANDARD_HDTV_2160P_59_420;
			else
				ret_val = VO_STANDARD_HDTV_2160P_60_420;
		} else {
			if (freq_shift && en_3d)
				ret_val = VO_STANDARD_ERROR;
			else if (freq_shift)
				ret_val = VO_STANDARD_HDTV_2160P_59;
			else if (en_3d)
				ret_val = VO_STANDARD_HDTV_2160P_60_3D;
			else
				ret_val = VO_STANDARD_HDTV_2160P_60;
		}
		break;
	case VIC_4096X2160P24:
		if (freq_shift)
			ret_val = VO_STANDARD_ERROR;
		else if (en_3d)
			ret_val = VO_STANDARD_HDTV_4096_2160P_24_3D;
		else
			ret_val = VO_STANDARD_HDTV_4096_2160P_24;
		break;
	case VIC_4096X2160P25:
		if (freq_shift)
			ret_val = VO_STANDARD_ERROR;
		else if (en_3d)
			ret_val = VO_STANDARD_HDTV_4096_2160P_25_3D;
		else
			ret_val = VO_STANDARD_HDTV_4096_2160P_25;
		break;
	case VIC_4096X2160P30:
		if (freq_shift)
			ret_val = VO_STANDARD_ERROR;
		else if (en_3d)
			ret_val = VO_STANDARD_HDTV_4096_2160P_30_3D;
		else
			ret_val = VO_STANDARD_HDTV_4096_2160P_30;
		break;
	case VIC_4096X2160P50:
		if (color == COLOR_YUV420) {
			if (freq_shift || en_3d)
				ret_val = VO_STANDARD_ERROR;
			else
				ret_val = VO_STANDARD_HDTV_4096_2160P_50_420;
		} else {
			if (freq_shift)
				ret_val = VO_STANDARD_ERROR;
			else if (en_3d)
				ret_val = VO_STANDARD_HDTV_4096_2160P_50_3D;
			else
				ret_val = VO_STANDARD_HDTV_4096_2160P_50;
		}
		break;
	case VIC_4096X2160P60:
		if (color == COLOR_YUV420) {
			if (freq_shift || en_3d)
				ret_val = VO_STANDARD_ERROR;
			else
				ret_val = VO_STANDARD_HDTV_4096_2160P_60_420;
		} else {
			if (freq_shift)
				ret_val = VO_STANDARD_ERROR;
			else if (en_3d)
				ret_val = VO_STANDARD_HDTV_4096_2160P_60_3D;
			else
				ret_val = VO_STANDARD_HDTV_4096_2160P_60;
		}
		break;
	default:
		ret_val = VO_STANDARD_ERROR;
		break;
	} /* end of switch (vic) */

	if (ret_val >= VO_STANDARD_ERROR)
		printf("Convert VO_STANDARD fail, vic(%u) freq_shift(%u) color(%u) 3d(%u)",
			vic, freq_shift, color, en_3d);

	return ret_val;
}

unsigned int is_interlace_mode(unsigned int vic)
{
	unsigned int ret_val;

	switch (vic) {
	case VIC_1920X1080I60:
	case VIC_720X480I60:
	case VIC_1920X1080I50:
	case VIC_720X576I50:
		ret_val = 1;
		break;
	default:
		ret_val = 0;
		break;
	}

	return ret_val;
}

void set_colorimetry(unsigned int color_mode, struct VIDEO_RPC_VOUT_CONFIG_TV_SYSTEM *tv_system)
{
	unsigned int standard;
	unsigned char data_byte2;
	unsigned char data_byte3;
	unsigned char colorimetry;

	standard = tv_system->videoInfo.standard;
	/* mask out C1:C0 */
	data_byte2 = tv_system->hdmiInfo.dataByte2&0x3F;
	/* mask out EC2:EC1:EC0 */
	data_byte3 = tv_system->hdmiInfo.dataByte3&0x8F;

	colorimetry = hdmi2p0_info.colorimetry;

	if (color_mode == COLOR_RGB444) {

		if (colorimetry&BT2020_RGB) {
			data_byte2 |= 0xC0;
			data_byte3 |= 0x60;
		} else if (standard >= VO_STANDARD_HDTV_720P_60) {
			data_byte2 |= 0x80;/* BT.709 */
		} else {
			data_byte2 |= 0x40;/* SMPTE170M */
		}

	} else {

		if (colorimetry&BT2020_YCC) {
			data_byte2 |= 0xC0;
			data_byte3 |= 0x60;
		} else if ((colorimetry&xvYCC709) &&
			(standard >= VO_STANDARD_HDTV_720P_60)) {
			data_byte2 |= 0xC0;
			data_byte3 |= 0x10;
		} else if ((colorimetry&xvYCC601) &&
			(standard < VO_STANDARD_HDTV_720P_60)) {
			data_byte2 |= 0xC0;
			data_byte3 |= 0x00;
		} else if (standard >= VO_STANDARD_HDTV_720P_60) {
			data_byte2 |= 0x80;
		} else {
			data_byte2 |= 0x40;
		}

	}

	tv_system->hdmiInfo.dataByte2 = data_byte2;
	tv_system->hdmiInfo.dataByte3 = data_byte3;

}

void set_aspect_ratio(unsigned int vic, struct VIDEO_RPC_VOUT_CONFIG_TV_SYSTEM *tv_system)
{
	unsigned char data_byte2;

	/* mask out M1:R0 */
	data_byte2 = tv_system->hdmiInfo.dataByte2&0xC0;

	switch (vic) {
	case 2:
	case 6:
	case 17:
	case 21:
		data_byte2 |= 0x18;
		break;
	default:
		data_byte2 |= 0x28;
		break;
	}

	tv_system->hdmiInfo.dataByte2 = data_byte2;
}

void config_avi_infoframe(unsigned int vic, unsigned int color_mode, struct VIDEO_RPC_VOUT_CONFIG_TV_SYSTEM *tv_system)
{
	unsigned char data_byte1;
	unsigned char data_byte4;

	/* Data Byte1 */
	switch (color_mode) {
	case COLOR_RGB444:
		data_byte1 = 0x0;
		break;
	case COLOR_YUV422:
		data_byte1 = 0x20;
		break;
	case COLOR_YUV444:
		data_byte1 = 0x40;
		break;
	case COLOR_YUV420:
		data_byte1 = 0x60;
		break;
	default:
		data_byte1 = 0x0;
		printf("Unknown color_mode");
		break;
	}

	tv_system->hdmiInfo.dataByte1 = data_byte1;

	/* Data Byte2, Data Byte3 */
	set_colorimetry(color_mode, tv_system);
	set_aspect_ratio(vic, tv_system);

	/* Data Byte4 */
	data_byte4 = (unsigned char)vic;
	tv_system->hdmiInfo.dataByte4 = data_byte4;

}

void set_cvbs(unsigned int vic, struct VIDEO_RPC_VOUT_CONFIG_TV_SYSTEM *tv_system)
{
	unsigned char video_dataint0;

	switch (vic) {
	case VIC_720X576P50:
	case VIC_1280X720P50:
	case VIC_1920X1080I50:
	case VIC_720X576I50:
	case VIC_1920X1080P50:
	case VIC_1920X1080P25:
	case VIC_3840X2160P25:
	case VIC_3840X2160P50:
	case VIC_4096X2160P25:
	case VIC_4096X2160P50:
		/* CVBS PAL */
		video_dataint0 = 0x2;
		break;
	default:
		/* CVBS NTSC */
		video_dataint0 = 0x4;
		break;
	}

	tv_system->videoInfo.dataInt0 = video_dataint0;
}

int set_hdmitx_format(struct hdmi_format_setting *format)
{
	int ret = 0;
	struct VIDEO_RPC_VOUT_CONFIG_TV_SYSTEM tv_system;
	unsigned int standard;
	unsigned int interlace;
	unsigned int dataint0;
	int scramble;
	unsigned char en_3d;

	printf("Set mode=%u vic=%u freq_shift=%u color_mode=%u color_depth=%u 3d=%u hdr=%u\n",
		format->mode, format->vic, format->freq_shift, format->color, format->color_depth,
		format->_3d_format, format->hdr);

	memset(&tv_system, 0, sizeof(tv_system));

	if ((format->vic == 0) || (format->mode == FORMAT_MODE_OFF)) {
		/* HDMI OFF */
		tv_system.videoInfo.standard = VO_STANDARD_NTSC_J;
		tv_system.videoInfo.enProg = 0x1;
		tv_system.videoInfo.pedType = 0x1;
		tv_system.videoInfo.dataInt0 = 0x4;
		tv_system.hdmiInfo.hdmiMode = VO_HDMI_OFF;
		goto config;
	}

	if (format->_3d_format == FORMAT_3D_FP)
		en_3d = 1;
	else
		en_3d = 0;

	standard =  vic_to_vo_standard(format->vic, format->freq_shift, format->color, en_3d);
	if (standard < VO_STANDARD_ERROR)
		tv_system.videoInfo.standard = standard;
	else
		ret = -1;

	if (format->mode == FORMAT_MODE_DVI)
		tv_system.hdmiInfo.hdmiMode = VO_DVI_ON;
	else
		tv_system.hdmiInfo.hdmiMode = VO_HDMI_ON;

	tv_system.videoInfo.enDIF = 0x1;
	tv_system.videoInfo.enCompRGB = 0;
	tv_system.videoInfo.pedType = 0x1;
	tv_system.hdmiInfo.audioSampleFreq = 0x3;
	tv_system.hdmiInfo.audioChannelCount = 0x1;

	interlace = is_interlace_mode(format->vic);
	if (interlace != 0)
		tv_system.videoInfo.enProg = 0;
	else
		tv_system.videoInfo.enProg = 1;

	config_avi_infoframe(format->vic, format->color, &tv_system);

	/* mask out  color_depth */
	dataint0 = tv_system.hdmiInfo.dataInt0&(~0x3E);

	switch (format->color_depth) {
	case 8:
		dataint0 |= 0x0;
		break;
	case 10:
		dataint0 |= 0x16;
		break;
	case 12:
		dataint0 |= 0x1A;
		break;
	default:
		printf("Unknown color_depth");
		break;
	}

	tv_system.hdmiInfo.dataInt0 = dataint0;

	/* CVBS format */
	set_cvbs(format->vic, &tv_system);

	/* Force set HDR OFF */
	tv_system.hdmiInfo.hdr_ctrl_mode = VO_HDR_CTRL_SDR;

	if (tv_system.hdmiInfo.hdmiMode == VO_HDMI_ON) {
		if (hdmi2p0_info.hdmi_id == HDMI_2P0_IDENTIFIER)
			tv_system.hdmiInfo.hdmi2p0_feature |= 0x1;

		scramble = hdmitx_send_scdc_TmdsConfig(tv_system.videoInfo.standard, tv_system.hdmiInfo.dataInt0);
		if (scramble < 0) {
			/* Send scdc fail, skip one step */
			ret = -1;
			goto exit;
		} else if (scramble > 0) {
			tv_system.hdmiInfo.hdmi2p0_feature |= 0x2;
		}
	}

config:
	set_one_step_info(&tv_system);
exit:
	return ret;
}

