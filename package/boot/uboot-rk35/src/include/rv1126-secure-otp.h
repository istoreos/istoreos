/* SPDX-License-Identifier:     GPL-2.0+ */
/*
 * (C) Copyright 2019 Rockchip Electronics Co., Ltd
 */

#ifndef _RV1126_SECURE_OTP_H_
#define _RV1126_SECURE_OTP_H_

#define NVM_CEB			0x00
#define NVM_RSTB		0x04
#define NVM_TCSRST		0x08
#define NVM_TCEW		0x0c
#define NVM_TRW			0x10
#define NVM_TRS			0x14
#define NVM_ST			0x18
#define NVM_RADDR		0x1c
#define NVM_RSTART		0x20
#define NVM_RDATA		0x24
#define NVM_TRWH		0x28
#define NVM_TREW		0x2c
#define NVM_READ_ST		0x30
#define NVM_PRADDR		0x34
#define NVM_PRLEN		0x38
#define NVM_PRDATA		0x3c
#define NVM_FAILTIME		0x40
#define NVM_PRSTART		0x44
#define NVM_PRSTATE		0x48
#define NVM_PRSUCCESS		0x4c
#define NVM_TAS			0x50
#define NVM_TWWL		0x54
#define NVM_TDLEH		0x58
#define NVM_TDPD		0x5c
#define NVM_TPES		0x60
#define NVM_TCPS		0x64
#define NVM_TPW			0x68
#define NVM_TCPH		0x6c
#define NVM_TPEH		0x70
#define NVM_TPTPD		0x74
#define NVM_TPGMAS		0x78
#define OTPC_INT_ST		0x7c
#define NVM_INT_EN		0x80
#define OTP_PROG_MASK_BASE	0x0200
#define OTP_READ_MASK_BASE	0x0300
#define OTP_MASK_BYPASS		0x0400
#define OTP_MASK_INT_CON	0x0404
#define OTP_MASK_INT_STATUS	0x0408
#define OTP_MASK_STATUS		0x040C
#define OTP_MASK_PROG_LOCK	0x0410
#define OTP_MASK_READ_LOCK	0x0414
#define OTP_MASK_BYPASS_LOCK	0x0418
#define OTP_SLICE_LOCK		0x041c
#define OTP_SLICE		0x0420

struct rockchip_otp_platdata {
	void __iomem *base;
	unsigned long secure_conf_base;
};

#endif

