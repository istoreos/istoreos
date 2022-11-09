/* SPDX-License-Identifier:     GPL-2.0+ */
/*
 * (C) Copyright 2019 Rockchip Electronics Co., Ltd
 */

#ifndef _ROCKCHIP_OTP_H_
#define _ROCKCHIP_OTP_H_

/* OTP Register Offsets */
#define OTPC_SBPI_CTRL			0x0020
#define OTPC_SBPI_CMD_VALID_PRE		0x0024
#define OTPC_SBPI_CS_VALID_PRE		0x0028
#define OTPC_SBPI_STATUS		0x002C
#define OTPC_USER_CTRL			0x0100
#define OTPC_USER_ADDR			0x0104
#define OTPC_USER_ENABLE		0x0108
#define OTPC_USER_QP			0x0120
#define OTPC_USER_Q			0x0124
#define OTPC_INT_STATUS			0x0304
#define OTPC_SBPI_CMD0_OFFSET		0x1000
#define OTPC_SBPI_CMD1_OFFSET		0x1004

/* OTP Register bits and masks */
#define OTPC_USER_ADDR_MASK		GENMASK(31, 16)
#define OTPC_USE_USER			BIT(0)
#define OTPC_USE_USER_MASK		GENMASK(16, 16)
#define OTPC_USER_FSM_ENABLE		BIT(0)
#define OTPC_USER_FSM_ENABLE_MASK	GENMASK(16, 16)
#define OTPC_SBPI_DONE			BIT(1)
#define OTPC_USER_DONE			BIT(2)

#define SBPI_DAP_ADDR			0x02
#define SBPI_DAP_ADDR_SHIFT		8
#define SBPI_DAP_ADDR_MASK		GENMASK(31, 24)
#define SBPI_CMD_VALID_MASK		GENMASK(31, 16)
#define SBPI_DAP_CMD_WRF		0xC0
#define SBPI_DAP_REG_ECC		0x3A
#define SBPI_ECC_ENABLE			0x00
#define SBPI_ECC_DISABLE		0x09
#define SBPI_ENABLE			BIT(0)
#define SBPI_ENABLE_MASK		GENMASK(16, 16)

#define OTPC_TIMEOUT			10000

#define OTPC_MODE_CTRL			0x2000
#define OTPC_IRQ_ST			0x2008
#define OTPC_ACCESS_ADDR		0x200c
#define OTPC_RD_DATA			0x2010
#define OTPC_REPR_RD_TRANS_NUM		0x2020
#define OTPC_DEEP_STANDBY		0x0
#define OTPC_STANDBY			0x1
#define OTPC_ACTIVE			0x2
#define OTPC_READ_ACCESS		0x3
#define OTPC_TRANS_NUM			0x1
#define OTPC_RDM_IRQ_ST			BIT(0)
#define OTPC_STB2ACT_IRQ_ST		BIT(7)
#define OTPC_DP2STB_IRQ_ST		BIT(8)
#define OTPC_ACT2STB_IRQ_ST		BIT(9)
#define OTPC_STB2DP_IRQ_ST		BIT(10)
#define RK3308BS_NBYTES			4
#define RK3308BS_MAX_BYTES		0x80
#define RK3308BS_NO_SECURE_OFFSET	224

#define RK3568_NBYTES			2

#define RK3588_OTPC_AUTO_CTRL		0x04
#define RK3588_OTPC_AUTO_EN		0x08
#define RK3588_OTPC_INT_ST		0x84
#define RK3588_OTPC_DOUT0		0x20
#define RK3588_NO_SECURE_OFFSET		0x300
#define RK3588_MAX_BYTES		0x400
#define RK3588_NBYTES			4
#define RK3588_BURST_NUM		1
#define RK3588_BURST_SHIFT		8
#define RK3588_ADDR_SHIFT		16
#define RK3588_AUTO_EN			BIT(0)
#define RK3588_RD_DONE			BIT(1)

#define RV1126_OTP_NVM_CEB		0x00
#define RV1126_OTP_NVM_RSTB		0x04
#define RV1126_OTP_NVM_ST		0x18
#define RV1126_OTP_NVM_RADDR		0x1C
#define RV1126_OTP_NVM_RSTART		0x20
#define RV1126_OTP_NVM_RDATA		0x24
#define RV1126_OTP_NVM_TRWH		0x28
#define RV1126_OTP_READ_ST		0x30
#define RV1126_OTP_NVM_PRADDR		0x34
#define RV1126_OTP_NVM_PRLEN		0x38
#define RV1126_OTP_NVM_PRDATA		0x3c
#define RV1126_OTP_NVM_FAILTIME		0x40
#define RV1126_OTP_NVM_PRSTART		0x44
#define RV1126_OTP_NVM_PRSTATE		0x48

struct rockchip_otp_platdata {
	void __iomem *base;
	unsigned long secure_conf_base;
	unsigned long otp_mask_base;
	unsigned long otp_cru_rst_base;
};

#endif
