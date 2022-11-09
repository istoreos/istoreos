/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Cadence USB3 DRD header file.
 *
 * Copyright (C) 2018-2019 Cadence.
 *
 * Author: Pawel Laszczak <pawell@cadence.com>
 */
#ifndef __LINUX_CDNS3_DRD
#define __LINUX_CDNS3_DRD

#include <linux/types.h>
#include <linux/usb/otg.h>
#include "core.h"

/*  DRD register interface for version v1. */
struct cdns3_otg_regs {
	__le32 did;
	__le32 rid;
	__le32 capabilities;
	__le32 reserved1;
	__le32 cmd;
	__le32 sts;
	__le32 state;
	__le32 reserved2;
	__le32 ien;
	__le32 ivect;
	__le32 refclk;
	__le32 tmr;
	__le32 reserved3[4];
	__le32 simulate;
	__le32 override;
	__le32 susp_ctrl;
	__le32 reserved4;
	__le32 anasts;
	__le32 adp_ramp_time;
	__le32 ctrl1;
	__le32 ctrl2;
};

/*  DRD register interface for version v0. */
struct cdns3_otg_legacy_regs {
	__le32 cmd;
	__le32 sts;
	__le32 state;
	__le32 refclk;
	__le32 ien;
	__le32 ivect;
	__le32 reserved1[3];
	__le32 tmr;
	__le32 reserved2[2];
	__le32 version;
	__le32 capabilities;
	__le32 reserved3[2];
	__le32 simulate;
	__le32 reserved4[5];
	__le32 ctrl1;
};

/*
 * Common registers interface for both version of DRD.
 */
struct cdns3_otg_common_regs {
	__le32 cmd;
	__le32 sts;
	__le32 state;
	__le32 different1;
	__le32 ien;
	__le32 ivect;
};

/* CDNS_RID - bitmasks */
#define CDNS_RID(p)			((p) & GENMASK(15, 0))

/* CDNS_VID - bitmasks */
#define CDNS_DID(p)			((p) & GENMASK(31, 0))

/* OTGCMD - bitmasks */
/* "Request the bus for Device mode. */
#define OTGCMD_DEV_BUS_REQ		BIT(0)
/* Request the bus for Host mode */
#define OTGCMD_HOST_BUS_REQ		BIT(1)
/* Enable OTG mode. */
#define OTGCMD_OTG_EN			BIT(2)
/* Disable OTG mode */
#define OTGCMD_OTG_DIS			BIT(3)
/*"Configure OTG as A-Device. */
#define OTGCMD_A_DEV_EN			BIT(4)
/*"Configure OTG as A-Device. */
#define OTGCMD_A_DEV_DIS		BIT(5)
/* Drop the bus for Device mod	e. */
#define OTGCMD_DEV_BUS_DROP		BIT(8)
/* Drop the bus for Host mode*/
#define OTGCMD_HOST_BUS_DROP		BIT(9)
/* Power Down USBSS-DEV. */
#define OTGCMD_DEV_POWER_OFF		BIT(11)
/* Power Down CDNSXHCI. */
#define OTGCMD_HOST_POWER_OFF		BIT(12)

/* OTGIEN - bitmasks */
/* ID change interrupt enable */
#define OTGIEN_ID_CHANGE_INT		BIT(0)
/* Vbusvalid fall detected interrupt enable.*/
#define OTGIEN_VBUSVALID_RISE_INT	BIT(4)
/* Vbusvalid fall detected interrupt enable */
#define OTGIEN_VBUSVALID_FALL_INT	BIT(5)

/* OTGSTS - bitmasks */
/*
 * Current value of the ID pin. It is only valid when idpullup in
 *  OTGCTRL1_TYPE register is set to '1'.
 */
#define OTGSTS_ID_VALUE			BIT(0)
/* Current value of the vbus_valid */
#define OTGSTS_VBUS_VALID		BIT(1)
/* Current value of the b_sess_vld */
#define OTGSTS_SESSION_VALID		BIT(2)
/*Device mode is active*/
#define OTGSTS_DEV_ACTIVE		BIT(3)
/* Host mode is active. */
#define OTGSTS_HOST_ACTIVE		BIT(4)
/* OTG Controller not ready. */
#define OTGSTS_OTG_NRDY_MASK		BIT(11)
#define OTGSTS_OTG_NRDY(p)		((p) & OTGSTS_OTG_NRDY_MASK)
/*
 * Value of the strap pins.
 * 000 - no default configuration
 * 010 - Controller initiall configured as Host
 * 100 - Controller initially configured as Device
 */
#define OTGSTS_STRAP(p)			(((p) & GENMASK(14, 12)) >> 12)
#define OTGSTS_STRAP_NO_DEFAULT_CFG	0x00
#define OTGSTS_STRAP_HOST_OTG		0x01
#define OTGSTS_STRAP_HOST		0x02
#define OTGSTS_STRAP_GADGET		0x04
/* Host mode is turned on. */
#define OTGSTS_XHCI_READY		BIT(26)
/* "Device mode is turned on .*/
#define OTGSTS_DEV_READY		BIT(27)

/* OTGSTATE- bitmasks */
#define OTGSTATE_DEV_STATE_MASK		GENMASK(2, 0)
#define OTGSTATE_HOST_STATE_MASK	GENMASK(5, 3)
#define OTGSTATE_HOST_STATE_IDLE	0x0
#define OTGSTATE_HOST_STATE_VBUS_FALL	0x7
#define OTGSTATE_HOST_STATE(p)		(((p) & OTGSTATE_HOST_STATE_MASK) >> 3)

/* OTGREFCLK - bitmasks */
#define OTGREFCLK_STB_CLK_SWITCH_EN	BIT(31)

/* OVERRIDE - bitmasks */
#define OVERRIDE_IDPULLUP		BIT(0)
/* Only for CDNS3_CONTROLLER_V0 version */
#define OVERRIDE_IDPULLUP_V0		BIT(24)

int cdns3_is_host(struct cdns3 *cdns);
int cdns3_is_device(struct cdns3 *cdns);
int cdns3_get_id(struct cdns3 *cdns);
int cdns3_get_vbus(struct cdns3 *cdns);
int cdns3_drd_init(struct cdns3 *cdns);
int cdns3_drd_exit(struct cdns3 *cdns);
int cdns3_drd_update_mode(struct cdns3 *cdns);
int cdns3_drd_switch_gadget(struct cdns3 *cdns, int on);
int cdns3_drd_switch_host(struct cdns3 *cdns, int on);

#endif /* __LINUX_CDNS3_DRD */
