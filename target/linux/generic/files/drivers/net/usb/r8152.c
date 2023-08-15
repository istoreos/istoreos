// SPDX-License-Identifier: GPL-2.0-only
/*
 *  Copyright (c) 2021 Realtek Semiconductor Corp. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation.
 *
 *  This product is covered by one or more of the following patents:
 *  US6,570,884, US6,115,776, and US6,327,625.
 */

#include <linux/signal.h>
#include <linux/slab.h>
#include <linux/module.h>
#include <linux/netdevice.h>
#include <linux/etherdevice.h>
#include <linux/mii.h>
#include <linux/ethtool.h>
#include <linux/usb.h>
#include <linux/crc32.h>
#include <linux/if_vlan.h>
#include <linux/uaccess.h>
#include <linux/list.h>
#include <linux/ip.h>
#include <linux/ipv6.h>
#include <net/ip6_checksum.h>
#include <linux/usb/cdc.h>
#include <linux/suspend.h>
#include <linux/atomic.h>
#include <linux/acpi.h>
#include "r8152_compatibility.h"

/* Version Information */
#define DRIVER_VERSION "v2.16.3 (2022/07/06)"
#define DRIVER_AUTHOR "Realtek nic sw <nic_swsd@realtek.com>"
#define DRIVER_DESC "Realtek RTL8152/RTL8153 Based USB Ethernet Adapters"
#define MODULENAME "r8152"

#define PATENTS		"This product is covered by one or more of the " \
			"following patents:\n" \
			"\t\tUS6,570,884, US6,115,776, and US6,327,625.\n"

#define R8152_PHY_ID		32

#define PLA_IDR			0xc000
#define PLA_RCR			0xc010
#define PLA_RCR1		0xc012
#define PLA_RMS			0xc016
#define PLA_RXFIFO_CTRL0	0xc0a0
#define PLA_RXFIFO_FULL		0xc0a2
#define PLA_RXFIFO_CTRL1	0xc0a4
#define PLA_RX_FIFO_FULL	0xc0a6
#define PLA_RXFIFO_CTRL2	0xc0a8
#define PLA_RX_FIFO_EMPTY	0xc0aa
#define PLA_DMY_REG0		0xc0b0
#define PLA_FMC			0xc0b4
#define PLA_CFG_WOL		0xc0b6
#define PLA_TEREDO_CFG		0xc0bc
#define PLA_TEREDO_WAKE_BASE	0xc0c4
#define PLA_MAR			0xcd00
#define PLA_BACKUP		0xd000
#define PLA_BDC_CR		0xd1a0
#define PLA_TEREDO_TIMER	0xd2cc
#define PLA_REALWOW_TIMER	0xd2e8
#define PLA_UPHY_TIMER		0xd388
#define PLA_SUSPEND_FLAG	0xd38a
#define PLA_INDICATE_FALG	0xd38c
#define PLA_MACDBG_PRE		0xd38c	/* RTL_VER_04 only */
#define PLA_MACDBG_POST		0xd38e	/* RTL_VER_04 only */
#define PLA_EXTRA_STATUS	0xd398
#define PLA_GPHY_CTRL		0xd3ae
#define PLA_POL_GPIO_CTRL	0xdc6a
#define PLA_EFUSE_DATA		0xdd00
#define PLA_EFUSE_CMD		0xdd02
#define PLA_LEDSEL		0xdd90
#define PLA_LED_FEATURE		0xdd92
#define PLA_PHYAR		0xde00
#define PLA_BOOT_CTRL		0xe004
#define PLA_LWAKE_CTRL_REG	0xe007
#define PLA_GPHY_INTR_IMR	0xe022
#define PLA_EEE_CR		0xe040
#define PLA_EEE_TXTWSYS		0xe04c
#define PLA_EEE_TXTWSYS_2P5G	0xe058
#define PLA_EEEP_CR		0xe080
#define PLA_MAC_PWR_CTRL	0xe0c0
#define PLA_MAC_PWR_CTRL2	0xe0ca
#define PLA_MAC_PWR_CTRL3	0xe0cc
#define PLA_MAC_PWR_CTRL4	0xe0ce
#define PLA_WDT6_CTRL		0xe428
#define PLA_TCR0		0xe610
#define PLA_TCR1		0xe612
#define PLA_MTPS		0xe615
#define PLA_TXFIFO_CTRL		0xe618
#define PLA_TXFIFO_FULL		0xe61a
#define PLA_RSTTALLY		0xe800
#define PLA_CR			0xe813
#define PLA_CRWECR		0xe81c
#define PLA_CONFIG12		0xe81e	/* CONFIG1, CONFIG2 */
#define PLA_CONFIG34		0xe820	/* CONFIG3, CONFIG4 */
#define PLA_CONFIG5		0xe822
#define PLA_PHY_PWR		0xe84c
#define PLA_OOB_CTRL		0xe84f
#define PLA_CPCR		0xe854
#define PLA_MISC_0		0xe858
#define PLA_MISC_1		0xe85a
#define PLA_OCP_GPHY_BASE	0xe86c
#define PLA_TALLYCNT		0xe890
#define PLA_SFF_STS_7		0xe8de
#define PLA_PHYSTATUS		0xe908
#define PLA_CONFIG6		0xe90a /* CONFIG6 */
#define PLA_USB_CFG		0xe952
#define PLA_BP_BA		0xfc26
#define PLA_BP_0		0xfc28
#define PLA_BP_1		0xfc2a
#define PLA_BP_2		0xfc2c
#define PLA_BP_3		0xfc2e
#define PLA_BP_4		0xfc30
#define PLA_BP_5		0xfc32
#define PLA_BP_6		0xfc34
#define PLA_BP_7		0xfc36
#define PLA_BP_EN		0xfc38
#define PLA_BP_8		0xfc38		/* RTL8153C */
#define PLA_BP_9		0xfc3a
#define PLA_BP_10		0xfc3c
#define PLA_BP_11		0xfc3e
#define PLA_BP_12		0xfc40
#define PLA_BP_13		0xfc42
#define PLA_BP_14		0xfc44
#define PLA_BP_15		0xfc46
#define PLA_BP2_EN		0xfc48

#define USB_USB2PHY		0xb41e
#define USB_SSPHYLINK1		0xb426
#define USB_SSPHYLINK2		0xb428
#define USB_L1_CTRL		0xb45e
#define USB_U2P3_CTRL		0xb460
#define USB_CSR_DUMMY1		0xb464
#define USB_CSR_DUMMY2		0xb466
#define USB_DEV_STAT		0xb808
#define USB_CONNECT_TIMER	0xcbf8
#define USB_MSC_TIMER		0xcbfc
#define USB_BURST_SIZE		0xcfc0
#define USB_FW_FIX_EN0		0xcfca
#define USB_FW_FIX_EN1		0xcfcc
#define USB_LPM_CONFIG		0xcfd8
#define USB_EFUSE		0xcfdb
#define USB_ECM_OPTION		0xcfee
#define USB_CSTMR		0xcfef	/* RTL8153A */
#define USB_MISC_2		0xcfff
#define USB_ECM_OP		0xd26b
#define USB_GPHY_CTRL		0xd284
#define USB_SPEED_OPTION	0xd32a
#define USB_FW_CTRL		0xd334	/* RTL8153B */
#define USB_FC_TIMER		0xd340
#define USB_USB_CTRL		0xd406
#define USB_PHY_CTRL		0xd408
#define USB_TX_AGG		0xd40a
#define USB_RX_BUF_TH		0xd40c
#define USB_USB_TIMER		0xd428
#define USB_RX_EARLY_TIMEOUT	0xd42c
#define USB_RX_EARLY_SIZE	0xd42e
#define USB_PM_CTRL_STATUS	0xd432	/* RTL8153A */
#define USB_RX_EXTRA_AGGR_TMR	0xd432	/* RTL8153B */
#define USB_TX_DMA		0xd434
#define USB_UPT_RXDMA_OWN	0xd437
#define USB_UPHY3_MDCMDIO	0xd480
#define USB_TOLERANCE		0xd490
#define USB_LPM_CTRL		0xd41a
#define USB_BMU_RESET		0xd4b0
#define USB_BMU_CONFIG		0xd4b4
#define USB_U1U2_TIMER		0xd4da
#define USB_FW_TASK		0xd4e8	/* RTL8153B */
#define USB_RX_AGGR_NUM		0xd4ee
#define USB_UPS_CTRL		0xd800
#define USB_POWER_CUT		0xd80a
#define USB_MISC_0		0xd81a
#define USB_MISC_1		0xd81f
#define USB_AFE_CTRL2		0xd824
#define USB_UPHY_XTAL		0xd826
#define USB_UPS_CFG		0xd842
#define USB_UPS_FLAGS		0xd848
#define USB_WDT1_CTRL		0xe404
#define USB_WDT11_CTRL		0xe43c
#define USB_BP_BA		PLA_BP_BA
#define USB_BP_0		PLA_BP_0
#define USB_BP_1		PLA_BP_1
#define USB_BP_2		PLA_BP_2
#define USB_BP_3		PLA_BP_3
#define USB_BP_4		PLA_BP_4
#define USB_BP_5		PLA_BP_5
#define USB_BP_6		PLA_BP_6
#define USB_BP_7		PLA_BP_7
#define USB_BP_EN		PLA_BP_EN	/* RTL8153A */
#define USB_BP_8		0xfc38		/* RTL8153B */
#define USB_BP_9		0xfc3a
#define USB_BP_10		0xfc3c
#define USB_BP_11		0xfc3e
#define USB_BP_12		0xfc40
#define USB_BP_13		0xfc42
#define USB_BP_14		0xfc44
#define USB_BP_15		0xfc46
#define USB_BP2_EN		0xfc48

/* OCP Registers */
#define OCP_ALDPS_CONFIG	0x2010
#define OCP_EEE_CONFIG1		0x2080
#define OCP_EEE_CONFIG2		0x2092
#define OCP_EEE_CONFIG3		0x2094
#define OCP_BASE_MII		0xa400
#define OCP_EEE_AR		0xa41a
#define OCP_EEE_DATA		0xa41c
#define OCP_PHY_STATUS		0xa420
#define OCP_NCTL_CFG		0xa42c
#define OCP_POWER_CFG		0xa430
#define OCP_EEE_CFG		0xa432
#define OCP_SRAM_ADDR		0xa436
#define OCP_SRAM_DATA		0xa438
#define OCP_DOWN_SPEED		0xa442
#define OCP_EEE_ABLE		0xa5c4
#define OCP_EEE_ADV		0xa5d0
#define OCP_EEE_LPABLE		0xa5d2
#define OCP_10GBT_CTRL		0xa5d4
#define OCP_10GBT_STAT		0xa5d6
#define OCP_EEE_ADV2		0xa6d4
#define OCP_PHY_STATE		0xa708		/* nway state for 8153 */
#define OCP_PHY_PATCH_STAT	0xb800
#define OCP_PHY_PATCH_CMD	0xb820
#define OCP_PHY_LOCK		0xb82e
#define OCP_ADC_IOFFSET		0xbcfc
#define OCP_ADC_CFG		0xbc06
#define OCP_SYSCLK_CFG		0xc416

/* SRAM Register */
#define SRAM_GREEN_CFG		0x8011
#define SRAM_LPF_CFG		0x8012
#define SRAM_GPHY_FW_VER	0x801e
#define SRAM_10M_AMP1		0x8080
#define SRAM_10M_AMP2		0x8082
#define SRAM_IMPEDANCE		0x8084
#define SRAM_PHY_LOCK		0xb82e

/* PLA_RCR */
#define RCR_AAP			0x00000001
#define RCR_APM			0x00000002
#define RCR_AM			0x00000004
#define RCR_AB			0x00000008
#define RCR_ACPT_ALL		(RCR_AAP | RCR_APM | RCR_AM | RCR_AB)
#define SLOT_EN			BIT(11)

/* PLA_RCR1 */
#define OUTER_VLAN		BIT(7)
#define INNER_VLAN		BIT(6)

/* PLA_RXFIFO_CTRL0 */
#define RXFIFO_THR1_NORMAL	0x00080002
#define RXFIFO_THR1_OOB		0x01800003

/* PLA_RXFIFO_FULL */
#define RXFIFO_FULL_MASK	0xfff

/* PLA_RXFIFO_CTRL1 */
#define RXFIFO_THR2_FULL	0x00000060
#define RXFIFO_THR2_HIGH	0x00000038
#define RXFIFO_THR2_OOB		0x0000004a
#define RXFIFO_THR2_NORMAL	0x00a0

/* PLA_RXFIFO_CTRL2 */
#define RXFIFO_THR3_FULL	0x00000078
#define RXFIFO_THR3_HIGH	0x00000048
#define RXFIFO_THR3_OOB		0x0000005a
#define RXFIFO_THR3_NORMAL	0x0110

/* PLA_TXFIFO_CTRL */
#define TXFIFO_THR_NORMAL	0x00400008
#define TXFIFO_THR_NORMAL2	0x01000008

/* PLA_DMY_REG0 */
#define ECM_ALDPS		0x0002

/* PLA_FMC */
#define FMC_FCR_MCU_EN		0x0001

/* PLA_EEEP_CR */
#define EEEP_CR_EEEP_TX		0x0002

/* PLA_WDT6_CTRL */
#define WDT6_SET_MODE		0x0010

/* PLA_TCR0 */
#define TCR0_TX_EMPTY		0x0800
#define TCR0_AUTO_FIFO		0x0080

/* PLA_TCR1 */
#define VERSION_MASK		0x7cf0
#define IFG_MASK		(BIT(3) | BIT(9) | BIT(8))
#define IFG_144NS		BIT(9)
#define IFG_96NS		(BIT(9) | BIT(8))

/* PLA_MTPS */
#define MTPS_JUMBO		(12 * 1024 / 64)
#define MTPS_DEFAULT		(6 * 1024 / 64)

/* PLA_RSTTALLY */
#define TALLY_RESET		0x0001

/* PLA_CR */
#define CR_RST			0x10
#define CR_RE			0x08
#define CR_TE			0x04

/* PLA_CRWECR */
#define CRWECR_NORAML		0x00
#define CRWECR_CONFIG		0xc0

/* PLA_OOB_CTRL */
#define NOW_IS_OOB		0x80
#define TXFIFO_EMPTY		0x20
#define RXFIFO_EMPTY		0x10
#define LINK_LIST_READY		0x02
#define DIS_MCU_CLROOB		0x01
#define FIFO_EMPTY		(TXFIFO_EMPTY | RXFIFO_EMPTY)

/* PLA_MISC_1 */
#define RXDY_GATED_EN		0x0008

/* PLA_SFF_STS_7 */
#define RE_INIT_LL		0x8000
#define MCU_BORW_EN		0x4000

/* PLA_CPCR */
#define FLOW_CTRL_EN		BIT(0)
#define CPCR_RX_VLAN		0x0040

/* PLA_CFG_WOL */
#define MAGIC_EN		0x0001

/* PLA_TEREDO_CFG */
#define TEREDO_SEL		0x8000
#define TEREDO_WAKE_MASK	0x7f00
#define TEREDO_RS_EVENT_MASK	0x00fe
#define OOB_TEREDO_EN		0x0001

/* PLA_BDC_CR */
#define ALDPS_PROXY_MODE	0x0001

/* PLA_EFUSE_CMD */
#define EFUSE_READ_CMD		BIT(15)
#define EFUSE_DATA_BIT16	BIT(7)

/* PLA_CONFIG34 */
#define LINK_ON_WAKE_EN		0x0010
#define LINK_OFF_WAKE_EN	0x0008

/* PLA_CONFIG6 */
#define LANWAKE_CLR_EN		BIT(0)

/* PLA_USB_CFG */
#define EN_XG_LIP		BIT(1)
#define EN_G_LIP		BIT(2)

/* PLA_CONFIG5 */
#define BWF_EN			0x0040
#define MWF_EN			0x0020
#define UWF_EN			0x0010
#define SPI_EN			BIT(3)
#define LAN_WAKE_EN		0x0002

/* PLA_LED_FEATURE */
#define LED_MODE_MASK		0x0700

/* PLA_PHY_PWR */
#define TX_10M_IDLE_EN		0x0080
#define PFM_PWM_SWITCH		0x0040
#define TEST_IO_OFF		BIT(4)

/* PLA_MAC_PWR_CTRL */
#define D3_CLK_GATED_EN		0x00004000
#define MCU_CLK_RATIO		0x07010f07
#define MCU_CLK_RATIO_MASK	0x0f0f0f0f
#define ALDPS_SPDWN_RATIO	0x0f87

/* PLA_MAC_PWR_CTRL2 */
#define EEE_SPDWN_RATIO		0x8007
#define MAC_CLK_SPDWN_EN	BIT(15)
#define EEE_SPDWN_RATIO_MASK	0xff

/* PLA_MAC_PWR_CTRL3 */
#define PLA_MCU_SPDWN_EN	BIT(14)
#define PKT_AVAIL_SPDWN_EN	0x0100
#define SUSPEND_SPDWN_EN	0x0004
#define U1U2_SPDWN_EN		0x0002
#define L1_SPDWN_EN		0x0001

/* PLA_MAC_PWR_CTRL4 */
#define PWRSAVE_SPDWN_EN	0x1000
#define RXDV_SPDWN_EN		0x0800
#define TX10MIDLE_EN		0x0100
#define IDLE_SPDWN_EN		BIT(6)
#define TP100_SPDWN_EN		0x0020
#define TP500_SPDWN_EN		0x0010
#define TP1000_SPDWN_EN		0x0008
#define EEE_SPDWN_EN		0x0001

/* PLA_GPHY_INTR_IMR */
#define GPHY_STS_MSK		0x0001
#define SPEED_DOWN_MSK		0x0002
#define SPDWN_RXDV_MSK		0x0004
#define SPDWN_LINKCHG_MSK	0x0008

/* PLA_PHYAR */
#define PHYAR_FLAG		0x80000000

/* PLA_EEE_CR */
#define EEE_RX_EN		0x0001
#define EEE_TX_EN		0x0002

/* PLA_BOOT_CTRL */
#define AUTOLOAD_DONE		0x0002

/* PLA_LWAKE_CTRL_REG */
#define LANWAKE_PIN		BIT(7)

/* PLA_SUSPEND_FLAG */
#define LINK_CHG_EVENT		BIT(0)

/* PLA_INDICATE_FALG */
#define UPCOMING_RUNTIME_D3	BIT(0)

/* PLA_MACDBG_PRE and PLA_MACDBG_POST */
#define DEBUG_OE		BIT(0)
#define DEBUG_LTSSM		0x0082

/* PLA_EXTRA_STATUS */
#define CUR_LINK_OK		BIT(15)
#define U3P3_CHECK_EN		BIT(7)	/* RTL_VER_05 only */
#define LINK_CHANGE_FLAG	BIT(8)
#define POLL_LINK_CHG		BIT(0)

/* PLA_GPHY_CTRL */
#define GPHY_FLASH		BIT(1)

/* PLA_POL_GPIO_CTRL */
#define DACK_DET_EN		BIT(15)
#define POL_GPHY_PATCH		BIT(4)

/* USB_USB2PHY */
#define USB2PHY_SUSPEND		0x0001
#define USB2PHY_L1		0x0002

/* USB_SSPHYLINK1 */
#define DELAY_PHY_PWR_CHG	BIT(1)

/* USB_SSPHYLINK2 */
#define pwd_dn_scale_mask	0x3ffe
#define pwd_dn_scale(x)		((x) << 1)

/* USB_CSR_DUMMY1 */
#define DYNAMIC_BURST		0x0001

/* USB_CSR_DUMMY2 */
#define EP4_FULL_FC		0x0001

/* USB_DEV_STAT */
#define STAT_SPEED_MASK		0x0006
#define STAT_SPEED_HIGH		0x0000
#define STAT_SPEED_FULL		0x0002

/* USB_FW_FIX_EN0 */
#define FW_FIX_SUSPEND		BIT(14)

/* USB_FW_FIX_EN1 */
#define FW_IP_RESET_EN		BIT(9)

/* USB_LPM_CONFIG */
#define LPM_U1U2_EN		BIT(0)

/* USB_EFUSE */
#define PASS_THRU_MASK		BIT(0)

/* USB_TX_AGG */
#define TX_AGG_MAX_THRESHOLD	0x03

/* USB_RX_BUF_TH */
#define RX_THR_SUPPER		0x0c350180
#define RX_THR_HIGH		0x7a120180
#define RX_THR_SLOW		0xffff0180
#define RX_THR_B		0x00010001

/* USB_TX_DMA */
#define TEST_MODE_DISABLE	0x00000001
#define TX_SIZE_ADJUST1		0x00000100

/* USB_BMU_RESET */
#define BMU_RESET_EP_IN		0x01
#define BMU_RESET_EP_OUT	0x02

/* USB_BMU_CONFIG */
#define ACT_ODMA		BIT(1)

/* USB_UPT_RXDMA_OWN */
#define OWN_UPDATE		BIT(0)
#define OWN_CLEAR		BIT(1)

/* USB_FW_TASK */
#define FC_PATCH_TASK		BIT(1)

/* USB_RX_AGGR_NUM */
#define RX_AGGR_NUM_MASK	0x1ff

/* USB_UPS_CTRL */
#define POWER_CUT		0x0100

/* USB_PM_CTRL_STATUS */
#define RESUME_INDICATE		0x0001

/* USB_ECM_OPTION */
#define BYPASS_MAC_RESET	BIT(5)

/* USB_CSTMR */
#define FORCE_SUPER		BIT(0)

/* USB_MISC_2 */
#define UPS_NO_UPS		BIT(7)
#define UPS_FORCE_PWR_DOWN	BIT(0)

/* USB_ECM_OP */
#define	EN_ALL_SPEED		BIT(0)

/* USB_GPHY_CTRL */
#define GPHY_PATCH_DONE		BIT(2)
#define BYPASS_FLASH		BIT(5)
#define BACKUP_RESTRORE		BIT(6)

/* USB_SPEED_OPTION */
#define RG_PWRDN_EN		BIT(8)
#define ALL_SPEED_OFF		BIT(9)

/* USB_FW_CTRL */
#define FLOW_CTRL_PATCH_OPT	BIT(1)
#define AUTO_SPEEDUP		BIT(3)
#define FLOW_CTRL_PATCH_2	BIT(8)

/* USB_FC_TIMER */
#define CTRL_TIMER_EN		BIT(15)

/* USB_USB_CTRL */
#define CDC_ECM_EN		BIT(3)
#define RX_AGG_DISABLE		0x0010
#define RX_ZERO_EN		0x0080

/* USB_U2P3_CTRL */
#define U2P3_ENABLE		0x0001
#define RX_DETECT8		BIT(3)

/* USB_POWER_CUT */
#define PWR_EN			0x0001
#define PHASE2_EN		0x0008
#define UPS_EN			BIT(4)
#define USP_PREWAKE		BIT(5)

/* USB_MISC_0 */
#define PCUT_STATUS		0x0001
#define AD_MASK			0xfee0

/* USB_MISC_1 */
#define BD_MASK			BIT(0)
#define BND_MASK		BIT(2)
#define BL_MASK			BIT(3)

/* USB_RX_EARLY_TIMEOUT */
#define COALESCE_SUPER		 85000U
#define COALESCE_HIGH		250000U
#define COALESCE_SLOW		524280U

/* USB_WDT1_CTRL */
#define WTD1_EN			BIT(0)

/* USB_WDT11_CTRL */
#define TIMER11_EN		0x0001

/* USB_LPM_CTRL */
/* bit 4 ~ 5: fifo empty boundary */
#define FIFO_EMPTY_1FB		0x30	/* 0x1fb * 64 = 32448 bytes */
/* bit 2 ~ 3: LMP timer */
#define LPM_TIMER_MASK		0x0c
#define LPM_TIMER_500MS		0x04	/* 500 ms */
#define LPM_TIMER_500US		0x0c	/* 500 us */
#define ROK_EXIT_LPM		0x02

/* USB_AFE_CTRL2 */
#define SEN_VAL_MASK		0xf800
#define SEN_VAL_NORMAL		0xa000
#define SEL_RXIDLE		0x0100

/* USB_UPHY_XTAL */
#define OOBS_POLLING		BIT(8)

/* USB_UPS_CFG */
#define SAW_CNT_1MS_MASK	0x0fff
#define MID_REVERSE		BIT(5)	/* RTL8156A */

/* USB_UPS_FLAGS */
#define UPS_FLAGS_R_TUNE		BIT(0)
#define UPS_FLAGS_EN_10M_CKDIV		BIT(1)
#define UPS_FLAGS_250M_CKDIV		BIT(2)
#define UPS_FLAGS_EN_ALDPS		BIT(3)
#define UPS_FLAGS_CTAP_SHORT_DIS	BIT(4)
#define UPS_FLAGS_SPEED_MASK		(0xf << 16)
#define ups_flags_speed(x)		((x) << 16)
#define UPS_FLAGS_EN_EEE		BIT(20)
#define UPS_FLAGS_EN_500M_EEE		BIT(21)
#define UPS_FLAGS_EN_EEE_CKDIV		BIT(22)
#define UPS_FLAGS_EEE_PLLOFF_100	BIT(23)
#define UPS_FLAGS_EEE_PLLOFF_GIGA	BIT(24)
#define UPS_FLAGS_EEE_CMOD_LV_EN	BIT(25)
#define UPS_FLAGS_EN_GREEN		BIT(26)
#define UPS_FLAGS_EN_FLOW_CTR		BIT(27)

enum spd_duplex {
	NWAY_10M_HALF,
	NWAY_10M_FULL,
	NWAY_100M_HALF,
	NWAY_100M_FULL,
	NWAY_1000M_FULL,
	FORCE_10M_HALF,
	FORCE_10M_FULL,
	FORCE_100M_HALF,
	FORCE_100M_FULL,
	FORCE_1000M_FULL,
	NWAY_2500M_FULL,
};

/* OCP_ALDPS_CONFIG */
#define ENPWRSAVE		0x8000
#define ENPDNPS			0x0200
#define LINKENA			0x0100
#define DIS_SDSAVE		0x0010

/* OCP_PHY_STATUS */
#define PHY_STAT_MASK		0x0007
#define PHY_STAT_EXT_INIT	2
#define PHY_STAT_LAN_ON		3
#define PHY_STAT_PWRDN		5

/* OCP_NCTL_CFG */
#define PGA_RETURN_EN		BIT(1)

/* OCP_POWER_CFG */
#define EEE_CLKDIV_EN		0x8000
#define EN_ALDPS		0x0004
#define EN_10M_PLLOFF		0x0001

/* OCP_EEE_CONFIG1 */
#define RG_TXLPI_MSK_HFDUP	0x8000
#define RG_MATCLR_EN		0x4000
#define EEE_10_CAP		0x2000
#define EEE_NWAY_EN		0x1000
#define TX_QUIET_EN		0x0200
#define RX_QUIET_EN		0x0100
#define sd_rise_time_mask	0x0070
#define sd_rise_time(x)		(min(x, 7) << 4)	/* bit 4 ~ 6 */
#define RG_RXLPI_MSK_HFDUP	0x0008
#define SDFALLTIME		0x0007	/* bit 0 ~ 2 */

/* OCP_EEE_CONFIG2 */
#define RG_LPIHYS_NUM		0x7000	/* bit 12 ~ 15 */
#define RG_DACQUIET_EN		0x0400
#define RG_LDVQUIET_EN		0x0200
#define RG_CKRSEL		0x0020
#define RG_EEEPRG_EN		0x0010

/* OCP_EEE_CONFIG3 */
#define fast_snr_mask		0xff80
#define fast_snr(x)		(min(x, 0x1ff) << 7)	/* bit 7 ~ 15 */
#define RG_LFS_SEL		0x0060	/* bit 6 ~ 5 */
#define MSK_PH			0x0006	/* bit 0 ~ 3 */

/* OCP_EEE_AR */
/* bit[15:14] function */
#define FUN_ADDR		0x0000
#define FUN_DATA		0x4000
/* bit[4:0] device addr */

/* OCP_EEE_CFG */
#define CTAP_SHORT_EN		0x0040
#define EEE10_EN		0x0010

/* OCP_DOWN_SPEED */
#define EN_EEE_CMODE		BIT(14)
#define EN_EEE_1000		BIT(13)
#define EN_EEE_100		BIT(12)
#define EN_10M_CLKDIV		BIT(11)
#define EN_10M_BGOFF		0x0080

/* OCP_10GBT_CTRL */
#define RTL_ADV2_5G_F_R		BIT(5)	/* Advertise 2.5GBASE-T fast-retrain */

/* OCP_PHY_STATE */
#define TXDIS_STATE		0x01
#define ABD_STATE		0x02

/* OCP_PHY_PATCH_STAT */
#define PATCH_READY		BIT(6)

/* OCP_PHY_PATCH_CMD */
#define PATCH_REQUEST		BIT(4)

/* OCP_PHY_LOCK */
#define PATCH_LOCK		BIT(0)

/* OCP_ADC_CFG */
#define CKADSEL_L		0x0100
#define ADC_EN			0x0080
#define EN_EMI_L		0x0040

/* OCP_SYSCLK_CFG */
#define sysclk_div_expo(x)	(min(x, 5) << 8)
#define clk_div_expo(x)		(min(x, 5) << 4)

/* SRAM_GREEN_CFG */
#define GREEN_ETH_EN		BIT(15)
#define R_TUNE_EN		BIT(11)

/* SRAM_LPF_CFG */
#define LPF_AUTO_TUNE		0x8000

/* SRAM_10M_AMP1 */
#define GDAC_IB_UPALL		0x0008

/* SRAM_10M_AMP2 */
#define AMP_DN			0x0200

/* SRAM_IMPEDANCE */
#define RX_DRIVING_MASK		0x6000

/* SRAM_PHY_LOCK */
#define PHY_PATCH_LOCK		0x0001

enum rtl_register_content {
	_2500bps	= BIT(10),
	_1250bps	= BIT(9),
	_500bps		= BIT(8),
	_tx_flow	= BIT(6),
	_rx_flow	= BIT(5),
	_1000bps	= 0x10,
	_100bps		= 0x08,
	_10bps		= 0x04,
	LINK_STATUS	= 0x02,
	FULL_DUP	= 0x01,
};

#define is_speed_2500(_speed)	(((_speed) & (_2500bps | LINK_STATUS)) == (_2500bps | LINK_STATUS))
#define is_flow_control(_speed)	(((_speed) & (_tx_flow | _rx_flow)) == (_tx_flow | _rx_flow))

#define RTL8152_MAX_TX		4
#define RTL8152_MAX_RX		10
#define INTBUFSIZE		2
#define TX_ALIGN		4
#define RX_ALIGN		8

#define RTL8152_RX_MAX_PENDING	4096
#define RTL8152_RXFG_HEADSZ	256

#define INTR_LINK		0x0004

#define RTL8152_REQT_READ	0xc0
#define RTL8152_REQT_WRITE	0x40
#define RTL8152_REQ_GET_REGS	0x05
#define RTL8152_REQ_SET_REGS	0x05

#define BYTE_EN_DWORD		0xff
#define BYTE_EN_WORD		0x33
#define BYTE_EN_BYTE		0x11
#define BYTE_EN_SIX_BYTES	0x3f
#define BYTE_EN_START_MASK	0x0f
#define BYTE_EN_END_MASK	0xf0

#define RTL8152_RMS		(VLAN_ETH_FRAME_LEN + ETH_FCS_LEN)
#define RTL8153_RMS		RTL8153_MAX_PACKET
#define RTL8152_TX_TIMEOUT	(5 * HZ)
#define mtu_to_size(m)		((m) + VLAN_ETH_HLEN + ETH_FCS_LEN)
#define size_to_mtu(s)		((s) - VLAN_ETH_HLEN - ETH_FCS_LEN)
#define rx_reserved_size(x)	(mtu_to_size(x) + sizeof(struct rx_desc) + RX_ALIGN)

#define RTL_MAX_SG_NUM		64

/* rtl8152 flags */
enum rtl8152_flags {
	RTL8152_UNPLUG = 0,
	RTL8152_SET_RX_MODE,
	WORK_ENABLE,
	RTL8152_LINK_CHG,
	SELECTIVE_SUSPEND,
	PHY_RESET,
	SCHEDULE_TASKLET,
	GREEN_ETHERNET,
	RX_EPROTO,
	RECOVER_SPEED,
};

/* Define these values to match your device */
#define VENDOR_ID_REALTEK		0x0bda
#define VENDOR_ID_MICROSOFT		0x045e
#define VENDOR_ID_SAMSUNG		0x04e8
#define VENDOR_ID_LENOVO		0x17ef
#define VENDOR_ID_LINKSYS		0x13b1
#define VENDOR_ID_NVIDIA		0x0955
#define VENDOR_ID_TPLINK		0x2357

#define MCU_TYPE_PLA			0x0100
#define MCU_TYPE_USB			0x0000

struct tally_counter {
	__le64	tx_packets;
	__le64	rx_packets;
	__le64	tx_errors;
	__le32	rx_errors;
	__le16	rx_missed;
	__le16	align_errors;
	__le32	tx_one_collision;
	__le32	tx_multi_collision;
	__le64	rx_unicast;
	__le64	rx_broadcast;
	__le32	rx_multicast;
	__le16	tx_aborted;
	__le16	tx_underrun;
};

struct rx_desc {
	__le32 opts1;
#define RD_CRC				BIT(15)
#define RX_LEN_MASK			0x7fff

	__le32 opts2;
#define RD_UDP_CS			BIT(23)
#define RD_TCP_CS			BIT(22)
#define RD_IPV6_CS			BIT(20)
#define RD_IPV4_CS			BIT(19)

	__le32 opts3;
#define IPF				BIT(23) /* IP checksum fail */
#define UDPF				BIT(22) /* UDP checksum fail */
#define TCPF				BIT(21) /* TCP checksum fail */
#define RX_VLAN_TAG			BIT(16)

	__le32 opts4;
	__le32 opts5;
	__le32 opts6;
};

struct tx_desc {
	__le32 opts1;
#define TX_FS			BIT(31) /* First segment of a packet */
#define TX_LS			BIT(30) /* Final segment of a packet */
#define LGSEND			BIT(29)
#define GTSENDV4		BIT(28)
#define GTSENDV6		BIT(27)
#define GTTCPHO_SHIFT		18
#define GTTCPHO_MAX		0x7fU
#define TX_LEN_MAX		0x3ffffU

	__le32 opts2;
#define UDP_CS			BIT(31) /* Calculate UDP/IP checksum */
#define TCP_CS			BIT(30) /* Calculate TCP/IP checksum */
#define IPV4_CS			BIT(29) /* Calculate IPv4 checksum */
#define IPV6_CS			BIT(28) /* Calculate IPv6 checksum */
#define MSS_SHIFT		17
#define MSS_MAX			0x7ffU
#define TCPHO_SHIFT		17
#define TCPHO_MAX		0x7ffU
#define TX_VLAN_TAG		BIT(16)
};

struct r8152;

struct rx_agg {
	struct list_head list, info_list;
	struct urb *urb;
	struct r8152 *context;
	struct page *page;
	void *buffer;
};

struct tx_agg {
	struct list_head list;
	struct urb *urb;
	struct r8152 *context;
	struct sk_buff_head tx_skb;
	void *buffer;
	void *head;
	u32 skb_num;
	u32 skb_len;
};

struct r8152 {
	unsigned long flags;
	struct usb_device *udev;
	struct napi_struct napi;
	struct usb_interface *intf;
	struct net_device *netdev;
	struct urb *intr_urb;
	struct tx_agg tx_info[RTL8152_MAX_TX];
	struct list_head rx_info, rx_used;
	struct list_head rx_done, tx_free;
	struct sk_buff_head tx_queue, rx_queue;
	spinlock_t rx_lock, tx_lock;
	struct delayed_work schedule, hw_phy_work;
	struct mii_if_info mii;
	struct mutex control;	/* use for hw setting */
#if LINUX_VERSION_CODE < KERNEL_VERSION(3,0,0)
	struct vlan_group *vlgrp;
#endif
#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,22)
	struct net_device_stats stats;
#endif
#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,23) && defined(CONFIG_PM_SLEEP)
	struct notifier_block pm_notifier;
#endif
#if defined(RTL8152_S5_WOL) && defined(CONFIG_PM)
	struct notifier_block reboot_notifier;
#endif /* defined(RTL8152_S5_WOL) && defined(CONFIG_PM) */
	struct tasklet_struct tx_tl;

	struct rtl_ops {
		void (*init)(struct r8152 *tp);
		int (*enable)(struct r8152 *tp);
		void (*disable)(struct r8152 *tp);
		void (*up)(struct r8152 *tp);
		void (*down)(struct r8152 *tp);
		void (*unload)(struct r8152 *tp);
#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,6,0)
		int (*eee_get)(struct r8152 *tp, struct ethtool_eee *eee);
		int (*eee_set)(struct r8152 *tp, struct ethtool_eee *eee);
#endif /* LINUX_VERSION_CODE >= KERNEL_VERSION(3,6,0) */
		bool (*in_nway)(struct r8152 *tp);
		void (*hw_phy_cfg)(struct r8152 *tp);
		void (*autosuspend_en)(struct r8152 *tp, bool enable);
		void (*change_mtu)(struct r8152 *tp);
	} rtl_ops;

	struct ups_info {
		u32 r_tune:1;
		u32 _10m_ckdiv:1;
		u32 _250m_ckdiv:1;
		u32 aldps:1;
		u32 lite_mode:2;
		u32 speed_duplex:4;
		u32 eee:1;
		u32 eee_lite:1;
		u32 eee_ckdiv:1;
		u32 eee_plloff_100:1;
		u32 eee_plloff_giga:1;
		u32 eee_cmod_lv:1;
		u32 green:1;
		u32 flow_control:1;
		u32 ctap_short_off:1;
	} ups_info;

	atomic_t rx_count;

	bool eee_en;
	int intr_interval;
	u32 saved_wolopts;
	u32 msg_enable;
	u32 tx_qlen;
	u32 coalesce;
	u32 advertising;
	u32 rx_buf_sz;
	u32 rx_copybreak;
	u32 rx_pending;
	u32 fc_pause_on, fc_pause_off;

	unsigned int pipe_in, pipe_out, pipe_intr, pipe_ctrl_in, pipe_ctrl_out;

	u32 support_2500full:1;
	u32 sg_use:1;
//	u32 dash_mode:1;
	u32 lenovo_macpassthru:1;
	u32 dell_macpassthru:1;

	u16 ocp_base;
	u16 speed;
	u16 eee_adv;
	u8 *intr_buff;
	u8 version;
	u8 rtk_enable_diag;
	u8 duplex;
	u8 autoneg;
};

enum rtl_version {
	RTL_VER_UNKNOWN = 0,
	RTL_VER_01,
	RTL_VER_02,
	RTL_VER_03,
	RTL_VER_04,
	RTL_VER_05,
	RTL_VER_06,
	RTL_VER_07,
	RTL_VER_08,
	RTL_VER_09,

	RTL_TEST_01,
	RTL_VER_10,
	RTL_VER_11,
	RTL_VER_12,
	RTL_VER_13,
	RTL_VER_14,
	RTL_VER_15,

	RTL_VER_MAX
};

enum tx_csum_stat {
	TX_CSUM_SUCCESS = 0,
	TX_CSUM_TSO,
	TX_CSUM_NONE
};

#define RTL_ADVERTISED_10_HALF			BIT(0)
#define RTL_ADVERTISED_10_FULL			BIT(1)
#define RTL_ADVERTISED_100_HALF			BIT(2)
#define RTL_ADVERTISED_100_FULL			BIT(3)
#define RTL_ADVERTISED_1000_HALF		BIT(4)
#define RTL_ADVERTISED_1000_FULL		BIT(5)
#define RTL_ADVERTISED_2500_FULL		BIT(6)

/* Maximum number of multicast addresses to filter (vs. Rx-all-multicast).
 * The RTL chips use a 64 element hash table based on the Ethernet CRC.
 */
static const int multicast_filter_limit = 32;
static unsigned int agg_buf_sz = 16384;

#define RTL_LIMITED_TSO_SIZE	(size_to_mtu(agg_buf_sz) - sizeof(struct tx_desc))

static
int get_registers(struct r8152 *tp, u16 value, u16 index, u16 size, void *data)
{
	int ret;
	void *tmp;

	tmp = kmalloc(size, GFP_KERNEL);
	if (!tmp)
		return -ENOMEM;

	ret = usb_control_msg(tp->udev, tp->pipe_ctrl_in,
			      RTL8152_REQ_GET_REGS, RTL8152_REQT_READ,
			      value, index, tmp, size, 500);
	if (ret < 0)
		memset(data, 0xff, size);
	else
		memcpy(data, tmp, size);

	kfree(tmp);

	if (ret < 0) {
		if (ret == -ETIMEDOUT)
			usb_queue_reset_device(tp->intf);
		netif_err(tp, drv, tp->netdev, "get_registers %d\n", ret);
	}

	return ret;
}

static
int set_registers(struct r8152 *tp, u16 value, u16 index, u16 size, void *data)
{
	int ret;
	void *tmp;

	tmp = kmemdup(data, size, GFP_KERNEL);
	if (!tmp)
		return -ENOMEM;

	ret = usb_control_msg(tp->udev, tp->pipe_ctrl_out,
			      RTL8152_REQ_SET_REGS, RTL8152_REQT_WRITE,
			      value, index, tmp, size, 500);

	kfree(tmp);

	if (ret < 0) {
		if (ret == -ETIMEDOUT)
			usb_queue_reset_device(tp->intf);
		netif_err(tp, drv, tp->netdev, "set_registers %d\n", ret);
	}

	return ret;
}

static void rtl_set_unplug(struct r8152 *tp)
{
	if (tp->udev->state == USB_STATE_NOTATTACHED) {
		set_bit(RTL8152_UNPLUG, &tp->flags);
		smp_mb__after_atomic();
	}
}

static int generic_ocp_read(struct r8152 *tp, u16 index, u16 size,
			    void *data, u16 type)
{
	u16 limit = 64;
	int ret = 0;

	if (test_bit(RTL8152_UNPLUG, &tp->flags))
		return -ENODEV;

	/* both size and indix must be 4 bytes align */
	if ((size & 3) || !size || (index & 3) || !data)
		return -EPERM;

	if ((u32)index + (u32)size > 0xffff)
		return -EPERM;

	while (size) {
		if (size > limit) {
			ret = get_registers(tp, index, type, limit, data);
			if (ret < 0)
				break;

			index += limit;
			data += limit;
			size -= limit;
		} else {
			ret = get_registers(tp, index, type, size, data);
			if (ret < 0)
				break;

			index += size;
			data += size;
			size = 0;
			break;
		}
	}

	if (ret == -ENODEV)
		rtl_set_unplug(tp);

	return ret;
}

static int generic_ocp_write(struct r8152 *tp, u16 index, u16 byteen,
			     u16 size, void *data, u16 type)
{
	int ret;
	u16 byteen_start, byteen_end, byen;
	u16 limit = 512;

	if (test_bit(RTL8152_UNPLUG, &tp->flags))
		return -ENODEV;

	/* both size and indix must be 4 bytes align */
	if ((size & 3) || !size || (index & 3) || !data)
		return -EPERM;

	if ((u32)index + (u32)size > 0xffff)
		return -EPERM;

	byteen_start = byteen & BYTE_EN_START_MASK;
	byteen_end = byteen & BYTE_EN_END_MASK;

	byen = byteen_start | (byteen_start << 4);
	ret = set_registers(tp, index, type | byen, 4, data);
	if (ret < 0)
		goto error1;

	index += 4;
	data += 4;
	size -= 4;

	if (size) {
		size -= 4;

		while (size) {
			if (size > limit) {
				ret = set_registers(tp, index,
						    type | BYTE_EN_DWORD,
						    limit, data);
				if (ret < 0)
					goto error1;

				index += limit;
				data += limit;
				size -= limit;
			} else {
				ret = set_registers(tp, index,
						    type | BYTE_EN_DWORD,
						    size, data);
				if (ret < 0)
					goto error1;

				index += size;
				data += size;
				size = 0;
				break;
			}
		}

		byen = byteen_end | (byteen_end >> 4);
		ret = set_registers(tp, index, type | byen, 4, data);
		if (ret < 0)
			goto error1;
	}

error1:
	if (ret == -ENODEV)
		rtl_set_unplug(tp);

	return ret;
}

static inline
int pla_ocp_read(struct r8152 *tp, u16 index, u16 size, void *data)
{
	return generic_ocp_read(tp, index, size, data, MCU_TYPE_PLA);
}

static inline
int pla_ocp_write(struct r8152 *tp, u16 index, u16 byteen, u16 size, void *data)
{
	return generic_ocp_write(tp, index, byteen, size, data, MCU_TYPE_PLA);
}

static inline
int usb_ocp_read(struct r8152 *tp, u16 index, u16 size, void *data)
{
	return generic_ocp_read(tp, index, size, data, MCU_TYPE_USB);
}

static inline
int usb_ocp_write(struct r8152 *tp, u16 index, u16 byteen, u16 size, void *data)
{
	return generic_ocp_write(tp, index, byteen, size, data, MCU_TYPE_USB);
}

static u32 ocp_read_dword(struct r8152 *tp, u16 type, u16 index)
{
	__le32 data;

	generic_ocp_read(tp, index, sizeof(data), &data, type);

	return __le32_to_cpu(data);
}

static void ocp_write_dword(struct r8152 *tp, u16 type, u16 index, u32 data)
{
	__le32 tmp = __cpu_to_le32(data);

	generic_ocp_write(tp, index, BYTE_EN_DWORD, sizeof(tmp), &tmp, type);
}

static u16 ocp_read_word(struct r8152 *tp, u16 type, u16 index)
{
	u32 data;
	__le32 tmp;
	u16 byen = BYTE_EN_WORD;
	u8 shift = index & 2;

	index &= ~3;
	byen <<= shift;

	generic_ocp_read(tp, index, sizeof(tmp), &tmp, type | byen);

	data = __le32_to_cpu(tmp);
	data >>= (shift * 8);
	data &= 0xffff;

	return (u16)data;
}

static void ocp_write_word(struct r8152 *tp, u16 type, u16 index, u32 data)
{
	u32 mask = 0xffff;
	__le32 tmp;
	u16 byen = BYTE_EN_WORD;
	u8 shift = index & 2;

	data &= mask;

	if (index & 2) {
		byen <<= shift;
		mask <<= (shift * 8);
		data <<= (shift * 8);
		index &= ~3;
	}

	tmp = __cpu_to_le32(data);

	generic_ocp_write(tp, index, byen, sizeof(tmp), &tmp, type);
}

static u8 ocp_read_byte(struct r8152 *tp, u16 type, u16 index)
{
	u32 data;
	__le32 tmp;
	u8 shift = index & 3;

	index &= ~3;

	generic_ocp_read(tp, index, sizeof(tmp), &tmp, type);

	data = __le32_to_cpu(tmp);
	data >>= (shift * 8);
	data &= 0xff;

	return (u8)data;
}

static void ocp_write_byte(struct r8152 *tp, u16 type, u16 index, u32 data)
{
	u32 mask = 0xff;
	__le32 tmp;
	u16 byen = BYTE_EN_BYTE;
	u8 shift = index & 3;

	data &= mask;

	if (index & 3) {
		byen <<= shift;
		mask <<= (shift * 8);
		data <<= (shift * 8);
		index &= ~3;
	}

	tmp = __cpu_to_le32(data);

	generic_ocp_write(tp, index, byen, sizeof(tmp), &tmp, type);
}

static u16 ocp_reg_read(struct r8152 *tp, u16 addr)
{
	u16 ocp_base, ocp_index;

	ocp_base = addr & 0xf000;
	if (ocp_base != tp->ocp_base) {
		ocp_write_word(tp, MCU_TYPE_PLA, PLA_OCP_GPHY_BASE, ocp_base);
		tp->ocp_base = ocp_base;
	}

	ocp_index = (addr & 0x0fff) | 0xb000;
	return ocp_read_word(tp, MCU_TYPE_PLA, ocp_index);
}

static void ocp_reg_write(struct r8152 *tp, u16 addr, u16 data)
{
	u16 ocp_base, ocp_index;

	ocp_base = addr & 0xf000;
	if (ocp_base != tp->ocp_base) {
		ocp_write_word(tp, MCU_TYPE_PLA, PLA_OCP_GPHY_BASE, ocp_base);
		tp->ocp_base = ocp_base;
	}

	ocp_index = (addr & 0x0fff) | 0xb000;
	ocp_write_word(tp, MCU_TYPE_PLA, ocp_index, data);
}

static inline void r8152_mdio_write(struct r8152 *tp, u32 reg_addr, u32 value)
{
	ocp_reg_write(tp, OCP_BASE_MII + reg_addr * 2, value);
}

static inline int r8152_mdio_read(struct r8152 *tp, u32 reg_addr)
{
	return ocp_reg_read(tp, OCP_BASE_MII + reg_addr * 2);
}

static void sram_write(struct r8152 *tp, u16 addr, u16 data)
{
	ocp_reg_write(tp, OCP_SRAM_ADDR, addr);
	ocp_reg_write(tp, OCP_SRAM_DATA, data);
}

static u16 sram_read(struct r8152 *tp, u16 addr)
{
	ocp_reg_write(tp, OCP_SRAM_ADDR, addr);
	return ocp_reg_read(tp, OCP_SRAM_DATA);
}

static int read_mii_word(struct net_device *netdev, int phy_id, int reg)
{
	struct r8152 *tp = netdev_priv(netdev);
	int ret, lock;

	if (test_bit(RTL8152_UNPLUG, &tp->flags))
		return -ENODEV;

	if (phy_id != R8152_PHY_ID)
		return -EINVAL;

	lock = mutex_trylock(&tp->control);

	ret = r8152_mdio_read(tp, reg);

	if (lock) {
		mutex_unlock(&tp->control);
		netif_warn(tp, drv, netdev, "miss mutex for read_mii_word?\n");
	}

	return ret;
}

static
void write_mii_word(struct net_device *netdev, int phy_id, int reg, int val)
{
	struct r8152 *tp = netdev_priv(netdev);
	int lock;

	if (test_bit(RTL8152_UNPLUG, &tp->flags))
		return;

	if (phy_id != R8152_PHY_ID)
		return;

	lock = mutex_trylock(&tp->control);

	r8152_mdio_write(tp, reg, val);

	if (lock) {
		mutex_unlock(&tp->control);
		netif_warn(tp, drv, netdev, "miss mutex for write_mii_word?\n");
	}
}

static int
r8152_submit_rx(struct r8152 *tp, struct rx_agg *agg, gfp_t mem_flags);

static int
rtl8152_set_speed(struct r8152 *tp, u8 autoneg, u32 speed, u8 duplex,
		  u32 advertising);

static int __rtl8152_set_mac_address(struct net_device *netdev, void *p,
				     bool in_resume)
{
	struct r8152 *tp = netdev_priv(netdev);
	struct sockaddr *addr = p;
	int ret = -EADDRNOTAVAIL;

	if (unlikely(tp->rtk_enable_diag))
		return -EBUSY;

	if (!is_valid_ether_addr(addr->sa_data))
		goto out1;

	if (!in_resume) {
		ret = usb_autopm_get_interface(tp->intf);
		if (ret < 0)
			goto out1;
	}

	mutex_lock(&tp->control);

	eth_hw_addr_set(netdev, addr->sa_data);

	ocp_write_byte(tp, MCU_TYPE_PLA, PLA_CRWECR, CRWECR_CONFIG);
	pla_ocp_write(tp, PLA_IDR, BYTE_EN_SIX_BYTES, 8, addr->sa_data);
	ocp_write_byte(tp, MCU_TYPE_PLA, PLA_CRWECR, CRWECR_NORAML);

	mutex_unlock(&tp->control);

	if (!in_resume)
		usb_autopm_put_interface(tp->intf);
out1:
	return ret;
}

static int rtl8152_set_mac_address(struct net_device *netdev, void *p)
{
	return __rtl8152_set_mac_address(netdev, p, false);
}

static int rtl_mapt_read(struct r8152 *tp, char *mac_obj_name,
			 acpi_object_type mac_obj_type, int mac_strlen,
			 struct sockaddr *sa)
{
	struct acpi_buffer buffer = { ACPI_ALLOCATE_BUFFER, NULL };
	union acpi_object *obj;
	unsigned char buf[6];
	acpi_status status;
	int ret = -EINVAL;

	/* returns _AUXMAC_#AABBCCDDEEFF# */
	status = acpi_evaluate_object(NULL, mac_obj_name, NULL, &buffer);
	obj = (union acpi_object *)buffer.pointer;
	if (!ACPI_SUCCESS(status))
		return -ENODEV;
	if (obj->type != mac_obj_type || obj->string.length != mac_strlen) {
		netif_warn(tp, probe, tp->netdev,
			   "Invalid buffer for pass-thru MAC addr: (%d, %d)\n",
			   obj->type, obj->string.length);
		goto amacout;
	}

	if (strncmp(obj->string.pointer, "_AUXMAC_#", 9) != 0 ||
	    strncmp(obj->string.pointer + 0x15, "#", 1) != 0) {
		netif_warn(tp, probe, tp->netdev,
			   "Invalid header when reading pass-thru MAC addr\n");
		goto amacout;
	}

	ret = hex2bin(buf, obj->string.pointer + 9, sizeof(buf));
	if (ret < 0 || !is_valid_ether_addr(buf)) {
		netif_warn(tp, probe, tp->netdev,
			   "Invalid MAC for pass-thru MAC addr: %d, %pM\n",
			   ret, buf);
		ret = -EINVAL;
		goto amacout;
	}

	memcpy(sa->sa_data, buf, sizeof(buf));
	netif_info(tp, probe, tp->netdev,
		   "Using pass-thru MAC addr %pM\n", sa->sa_data);

amacout:
	kfree(obj);
	return ret;
}

/* Devices containing proper chips can support a persistent
 * host system provided MAC address.
 * Examples of this are Dell TB15 and Dell WD15 docks
 */
static int vendor_mac_passthru_addr_read(struct r8152 *tp, struct sockaddr *sa)
{
	int ret = -EOPNOTSUPP;

	if (tp->dell_macpassthru)
		ret = rtl_mapt_read(tp, "\\_SB.AMAC", ACPI_TYPE_BUFFER, 0x17,
				    sa);
	else if (tp->lenovo_macpassthru)
		ret = rtl_mapt_read(tp, "\\MACA", ACPI_TYPE_STRING, 0x16, sa);

	return ret;
}

static int rtl_hw_ether_addr(struct r8152 *tp, struct sockaddr *sa)
{
	u32 ocp_data = 0;
	int ret;

	if (tp->version == RTL_VER_05) {
		/* Determine the hardware default ethernet address.
		 * Check USB 0xcf0e bit 0
		 *  1: read from USB 0xcf08
		 *  0: read from PLA_BACKUP
		 */
		ocp_data = ocp_read_byte(tp, MCU_TYPE_USB, 0xcf0e);

		if (ocp_data & BIT(0))
			return usb_ocp_read(tp, 0xcf08, 8, sa->sa_data);

		ocp_data |= BIT(0);
	}

	ret = pla_ocp_read(tp, PLA_BACKUP, 8, sa->sa_data);
	if (ret < 0)
		goto out;

	if (tp->version == RTL_VER_05) {
		/* Backup default ethernet address to USB 0xcf08.
		 * Set USB 0xcf0e bit 0 to 1. Then, next time, read the default
		 * ethernet address from USB 0xcf08 rather than PLA_BACKUP.
		 */
		usb_ocp_write(tp, 0xcf08, BYTE_EN_SIX_BYTES, 8, sa->sa_data);
		ocp_write_byte(tp, MCU_TYPE_USB, 0xcf0e, ocp_data);
	}

out:
	return ret;
}

static int determine_ethernet_addr(struct r8152 *tp, struct sockaddr *sa)
{
	struct net_device *dev = tp->netdev;
	int ret;

	sa->sa_family = dev->type;

	ret = eth_platform_get_mac_address(&tp->udev->dev, sa->sa_data);
	if (ret < 0) {
		if (tp->version == RTL_VER_01) {
			ret = pla_ocp_read(tp, PLA_IDR, 8, sa->sa_data);
		} else {
			/* if device doesn't support MAC pass through this will
			 * be expected to be non-zero
			 */
			ret = vendor_mac_passthru_addr_read(tp, sa);
			if (ret < 0)
				ret = rtl_hw_ether_addr(tp, sa);
		}
	}

	if (ret < 0) {
		netif_err(tp, probe, dev, "Get ether addr fail\n");
	} else if (!is_valid_ether_addr(sa->sa_data)) {
		netif_err(tp, probe, dev, "Invalid ether addr %pM\n",
			  sa->sa_data);
		eth_hw_addr_random(dev);
		ether_addr_copy(sa->sa_data, dev->dev_addr);
		netif_info(tp, probe, dev, "Random ether addr %pM\n",
			   sa->sa_data);
		return 0;
	}

	return ret;
}

static int set_ethernet_addr(struct r8152 *tp, bool in_resume)
{
	struct net_device *dev = tp->netdev;
	struct sockaddr sa;
	int ret;

	ret = determine_ethernet_addr(tp, &sa);
	if (ret < 0)
		return ret;

	if (tp->version == RTL_VER_01)
		eth_hw_addr_set(dev, sa.sa_data);
	else
		ret = __rtl8152_set_mac_address(dev, &sa, in_resume);

	return ret;
}

static inline struct net_device_stats *rtl8152_get_stats(struct net_device *dev)
{
#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,22)
	struct rtl8152 *tp = netdev_priv(dev);

	return (struct net_device_stats *)&tp->stats;
#else
	return &dev->stats;
#endif
}

static void read_bulk_callback(struct urb *urb)
{
	struct net_device *netdev;
	int status = urb->status;
	struct rx_agg *agg;
	struct r8152 *tp;
	unsigned long flags;

	agg = urb->context;
	if (!agg)
		return;

	tp = agg->context;
	if (!tp)
		return;

	if (test_bit(RTL8152_UNPLUG, &tp->flags))
		return;

	if (!test_bit(WORK_ENABLE, &tp->flags))
		return;

	netdev = tp->netdev;

	/* When link down, the driver would cancel all bulks. */
	/* This avoid the re-submitting bulk */
	if (!netif_carrier_ok(netdev))
		return;

	usb_mark_last_busy(tp->udev);

	switch (status) {
	case 0:
		if (urb->actual_length < ETH_ZLEN)
			break;

		spin_lock_irqsave(&tp->rx_lock, flags);
		list_add_tail(&agg->list, &tp->rx_done);
		spin_unlock_irqrestore(&tp->rx_lock, flags);
		napi_schedule(&tp->napi);
		return;
	case -ESHUTDOWN:
		rtl_set_unplug(tp);
		netif_device_detach(tp->netdev);
		return;
	case -EPROTO:
		urb->actual_length = 0;
		spin_lock_irqsave(&tp->rx_lock, flags);
		list_add_tail(&agg->list, &tp->rx_done);
		spin_unlock_irqrestore(&tp->rx_lock, flags);
		set_bit(RX_EPROTO, &tp->flags);
		schedule_delayed_work(&tp->schedule, 1);
		return;
	case -ENOENT:
		return;	/* the urb is in unlink state */
	case -ETIME:
		if (net_ratelimit())
			netif_warn(tp, rx_err, netdev,
				   "maybe reset is needed?\n");
		break;
	default:
		if (net_ratelimit())
			netif_warn(tp, rx_err, netdev,
				   "Rx status %d\n", status);
		break;
	}

	r8152_submit_rx(tp, agg, GFP_ATOMIC);
}

static void write_bulk_callback(struct urb *urb)
{
	struct net_device_stats *stats;
	struct net_device *netdev;
	struct tx_agg *agg;
	struct r8152 *tp;
	unsigned long flags;
	int status = urb->status;

	agg = urb->context;
	if (!agg)
		return;

	tp = agg->context;
	if (!tp)
		return;

	netdev = tp->netdev;
	stats = rtl8152_get_stats(netdev);
	if (status) {
		if (net_ratelimit())
			netif_warn(tp, tx_err, netdev,
				   "Tx status %d\n", status);
		stats->tx_errors += agg->skb_num;
	} else {
		stats->tx_packets += agg->skb_num;
		stats->tx_bytes += agg->skb_len;
	}

	spin_lock_irqsave(&tp->tx_lock, flags);
	list_add_tail(&agg->list, &tp->tx_free);
	spin_unlock_irqrestore(&tp->tx_lock, flags);

	usb_autopm_put_interface_async(tp->intf);

	if (!netif_carrier_ok(netdev))
		return;

	if (!test_bit(WORK_ENABLE, &tp->flags))
		return;

	if (test_bit(RTL8152_UNPLUG, &tp->flags))
		return;

	if (!skb_queue_empty(&tp->tx_queue))
		tasklet_schedule(&tp->tx_tl);
}

static void write_bulk_sg_callback(struct urb *urb)
{
	struct net_device *netdev;
	struct tx_agg *agg;
	struct r8152 *tp;
	unsigned long flags;
	int status = urb->status;

	agg = urb->context;
	if (!agg)
		return;

	tp = agg->context;
	if (!tp)
		return;

	netdev = tp->netdev;
	if (status && net_ratelimit())
		netif_warn(tp, tx_err, netdev, "Tx status %d\n", status);

	while (!skb_queue_empty(&agg->tx_skb)) {
		struct sk_buff *skb = __skb_dequeue(&agg->tx_skb);
		struct net_device_stats *stats = rtl8152_get_stats(netdev);

		if (status) {
			stats->tx_errors += skb_shinfo(skb)->gso_segs ?: 1;
			dev_kfree_skb_any(skb);
		} else {
			stats->tx_packets += skb_shinfo(skb)->gso_segs ?: 1;
			stats->tx_bytes += skb->len - skb->cb[0];
			dev_consume_skb_any(skb);
		}
	}

	spin_lock_irqsave(&tp->tx_lock, flags);
	list_add_tail(&agg->list, &tp->tx_free);
	spin_unlock_irqrestore(&tp->tx_lock, flags);

	usb_autopm_put_interface_async(tp->intf);

	if (!netif_carrier_ok(netdev))
		return;

	if (!test_bit(WORK_ENABLE, &tp->flags))
		return;

	if (test_bit(RTL8152_UNPLUG, &tp->flags))
		return;

	if (!skb_queue_empty(&tp->tx_queue))
		tasklet_schedule(&tp->tx_tl);
}

static void intr_callback(struct urb *urb)
{
	struct r8152 *tp;
	__le16 *d;
	int status = urb->status;
	int res;

	tp = urb->context;
	if (!tp)
		return;

	if (!test_bit(WORK_ENABLE, &tp->flags))
		return;

	if (test_bit(RTL8152_UNPLUG, &tp->flags))
		return;

	switch (status) {
	case 0:			/* success */
		break;
	case -ECONNRESET:	/* unlink */
	case -ESHUTDOWN:
		netif_device_detach(tp->netdev);
		fallthrough;
	case -ENOENT:
	case -EPROTO:
		netif_info(tp, intr, tp->netdev,
			   "Stop submitting intr, status %d\n", status);
		return;
	case -EOVERFLOW:
		netif_info(tp, intr, tp->netdev, "intr status -EOVERFLOW\n");
		goto resubmit;
	/* -EPIPE:  should clear the halt */
	default:
		netif_info(tp, intr, tp->netdev, "intr status %d\n", status);
		goto resubmit;
	}

	d = urb->transfer_buffer;
	if (INTR_LINK & __le16_to_cpu(d[0])) {
		if (!netif_carrier_ok(tp->netdev)) {
			set_bit(RTL8152_LINK_CHG, &tp->flags);
			schedule_delayed_work(&tp->schedule, 0);
		}
	} else {
		if (netif_carrier_ok(tp->netdev)) {
			netif_stop_queue(tp->netdev);
			set_bit(RTL8152_LINK_CHG, &tp->flags);
			schedule_delayed_work(&tp->schedule, 0);
		}
	}

resubmit:
	res = usb_submit_urb(urb, GFP_ATOMIC);
	if (res == -ENODEV) {
		rtl_set_unplug(tp);
		netif_device_detach(tp->netdev);
	} else if (res) {
		netif_err(tp, intr, tp->netdev,
			  "can't resubmit intr, status %d\n", res);
	}
}

static inline void *rx_agg_align(void *data)
{
	return (void *)ALIGN((uintptr_t)data, RX_ALIGN);
}

static inline void *tx_agg_align(void *data)
{
	return (void *)ALIGN((uintptr_t)data, TX_ALIGN);
}

static void free_rx_agg(struct r8152 *tp, struct rx_agg *agg)
{
	list_del(&agg->info_list);

	usb_free_urb(agg->urb);
	put_page(agg->page);
	kfree(agg);

	atomic_dec(&tp->rx_count);
}

static struct rx_agg *alloc_rx_agg(struct r8152 *tp, gfp_t mflags)
{
	struct net_device *netdev = tp->netdev;
	int node = netdev->dev.parent ? dev_to_node(netdev->dev.parent) : -1;
	unsigned int order = get_order(tp->rx_buf_sz);
	struct rx_agg *rx_agg;
	unsigned long flags;

	rx_agg = kmalloc_node(sizeof(*rx_agg), mflags, node);
	if (!rx_agg)
		return NULL;

	rx_agg->page = alloc_pages(mflags | __GFP_COMP, order);
	if (!rx_agg->page)
		goto free_rx;

	rx_agg->buffer = page_address(rx_agg->page);

	rx_agg->urb = usb_alloc_urb(0, mflags);
	if (!rx_agg->urb)
		goto free_buf;

	rx_agg->context = tp;

	INIT_LIST_HEAD(&rx_agg->list);
	INIT_LIST_HEAD(&rx_agg->info_list);
	spin_lock_irqsave(&tp->rx_lock, flags);
	list_add_tail(&rx_agg->info_list, &tp->rx_info);
	spin_unlock_irqrestore(&tp->rx_lock, flags);

	atomic_inc(&tp->rx_count);

	return rx_agg;

free_buf:
	__free_pages(rx_agg->page, order);
free_rx:
	kfree(rx_agg);
	return NULL;
}

static void free_all_mem(struct r8152 *tp)
{
	struct rx_agg *agg, *agg_next;
	unsigned long flags;
	int i;

	spin_lock_irqsave(&tp->rx_lock, flags);

	list_for_each_entry_safe(agg, agg_next, &tp->rx_info, info_list)
		free_rx_agg(tp, agg);

	spin_unlock_irqrestore(&tp->rx_lock, flags);

	WARN_ON(atomic_read(&tp->rx_count));

	for (i = 0; i < RTL8152_MAX_TX; i++) {
		usb_free_urb(tp->tx_info[i].urb);
		tp->tx_info[i].urb = NULL;

		kfree(tp->tx_info[i].buffer);
		tp->tx_info[i].buffer = NULL;
		tp->tx_info[i].head = NULL;
	}

	usb_free_urb(tp->intr_urb);
	tp->intr_urb = NULL;

	kfree(tp->intr_buff);
	tp->intr_buff = NULL;
}

static int alloc_all_mem(struct r8152 *tp)
{
	struct net_device *netdev = tp->netdev;
	struct usb_interface *intf = tp->intf;
	struct usb_host_interface *alt = intf->cur_altsetting;
	struct usb_host_endpoint *ep_intr = alt->endpoint + 2;
	int node, i;

	node = netdev->dev.parent ? dev_to_node(netdev->dev.parent) : -1;

	spin_lock_init(&tp->rx_lock);
	spin_lock_init(&tp->tx_lock);
	INIT_LIST_HEAD(&tp->rx_info);
	INIT_LIST_HEAD(&tp->tx_free);
	INIT_LIST_HEAD(&tp->rx_done);
	skb_queue_head_init(&tp->tx_queue);
	skb_queue_head_init(&tp->rx_queue);
	atomic_set(&tp->rx_count, 0);

	for (i = 0; i < RTL8152_MAX_RX; i++) {
		if (!alloc_rx_agg(tp, GFP_KERNEL))
			goto err1;
	}

	for (i = 0; i < RTL8152_MAX_TX; i++) {
		struct urb *urb;
		u8 *buf;

		buf = kmalloc_node(agg_buf_sz, GFP_KERNEL, node);
		if (!buf)
			goto err1;

		if (buf != tx_agg_align(buf)) {
			kfree(buf);
			buf = kmalloc_node(agg_buf_sz + TX_ALIGN, GFP_KERNEL,
					   node);
			if (!buf)
				goto err1;
		}

		urb = usb_alloc_urb(0, GFP_KERNEL);
		if (!urb) {
			kfree(buf);
			goto err1;
		}

		INIT_LIST_HEAD(&tp->tx_info[i].list);
		tp->tx_info[i].context = tp;
		tp->tx_info[i].urb = urb;
		tp->tx_info[i].buffer = buf;
		tp->tx_info[i].head = tx_agg_align(buf);

		list_add_tail(&tp->tx_info[i].list, &tp->tx_free);
		skb_queue_head_init(&tp->tx_info[i].tx_skb);
	}

	tp->intr_urb = usb_alloc_urb(0, GFP_KERNEL);
	if (!tp->intr_urb)
		goto err1;

	tp->intr_buff = kmalloc(INTBUFSIZE, GFP_KERNEL);
	if (!tp->intr_buff)
		goto err1;

	tp->intr_interval = (int)ep_intr->desc.bInterval;
	usb_fill_int_urb(tp->intr_urb, tp->udev, tp->pipe_intr,
			 tp->intr_buff, INTBUFSIZE, intr_callback,
			 tp, tp->intr_interval);

	return 0;

err1:
	free_all_mem(tp);
	return -ENOMEM;
}

static struct tx_agg *r8152_get_tx_agg(struct r8152 *tp)
{
	struct tx_agg *agg = NULL;
	unsigned long flags;

	if (list_empty(&tp->tx_free))
		return NULL;

	spin_lock_irqsave(&tp->tx_lock, flags);
	if (!list_empty(&tp->tx_free)) {
		struct list_head *cursor;

		cursor = tp->tx_free.next;
		list_del_init(cursor);
		agg = list_entry(cursor, struct tx_agg, list);
	}
	spin_unlock_irqrestore(&tp->tx_lock, flags);

	return agg;
}

/* r8152_csum_workaround()
 * The hw limits the value of the transport offset. When the offset is out of
 * range, calculate the checksum by sw.
 */
static void r8152_csum_workaround(struct r8152 *tp, struct sk_buff *skb,
				  struct sk_buff_head *list)
{
	if (skb_shinfo(skb)->gso_size) {
		netdev_features_t features = tp->netdev->features;
		struct sk_buff *segs, *seg, *next;
		struct sk_buff_head seg_list;

		features &= ~(NETIF_F_SG | NETIF_F_IPV6_CSUM | NETIF_F_TSO6);
		segs = skb_gso_segment(skb, features);
		if (IS_ERR(segs) || !segs)
			goto drop;

		__skb_queue_head_init(&seg_list);

		skb_list_walk_safe(segs, seg, next) {
			skb_mark_not_on_list(seg);
			__skb_queue_tail(&seg_list, seg);
		}

		skb_queue_splice(&seg_list, list);
		dev_kfree_skb(skb);
	} else if (skb->ip_summed == CHECKSUM_PARTIAL) {
		if (skb_checksum_help(skb) < 0)
			goto drop;

		__skb_queue_head(list, skb);
	} else {
		struct net_device_stats *stats;

drop:
		stats = rtl8152_get_stats(tp->netdev);
		stats->tx_dropped++;
		dev_kfree_skb(skb);
	}
}

static inline void rtl_tx_vlan_tag(struct tx_desc *desc, struct sk_buff *skb)
{
	if (skb_vlan_tag_present(skb)) {
		u32 opts2;

		opts2 = TX_VLAN_TAG | swab16(skb_vlan_tag_get(skb));
		desc->opts2 |= cpu_to_le32(opts2);
	}
}

#if LINUX_VERSION_CODE < KERNEL_VERSION(3,0,0)

static inline bool
rtl_rx_vlan_tag(struct r8152 *tp, struct rx_desc *desc, struct sk_buff *skb)
{
	u32 opts2 = le32_to_cpu(desc->opts2);

	if (tp->vlgrp && (opts2 & RX_VLAN_TAG)) {
		vlan_gro_receive(&tp->napi, tp->vlgrp, swab16(opts2 & 0xffff),
				 skb);
		return true;
	}

	return false;
}

static inline void
rtl_vlan_put_tag(struct r8152 *tp, struct rx_desc *desc, struct sk_buff *skb)
{
	u32 opts2 = le32_to_cpu(desc->opts2);

	if (tp->vlgrp && (opts2 & RX_VLAN_TAG))
		__vlan_hwaccel_put_tag(skb, swab16(opts2 & 0xffff));
}

static inline __u16
rtl_vlan_get_tag(struct sk_buff *skb)
{
	__u16 tag;

#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,27)
	__vlan_hwaccel_get_tag(skb, &tag);
#else
	tag = skb->vlan_tci;
#endif

	return tag;
}

#else

static inline void rtl_rx_vlan_tag(struct rx_desc *desc, struct sk_buff *skb)
{
	u32 opts2 = le32_to_cpu(desc->opts2);

	if (opts2 & RX_VLAN_TAG)
#if LINUX_VERSION_CODE < KERNEL_VERSION(3,10,0)
		__vlan_hwaccel_put_tag(skb, swab16(opts2 & 0xffff));
#else
		__vlan_hwaccel_put_tag(skb, htons(ETH_P_8021Q),
				       swab16(opts2 & 0xffff));
#endif /* LINUX_VERSION_CODE < KERNEL_VERSION(3,10,0) */
}

#endif /* LINUX_VERSION_CODE < KERNEL_VERSION(3,0,0) */

static int r8152_tx_csum(struct r8152 *tp, struct tx_desc *desc,
			 struct sk_buff *skb, u32 len, u32 transport_offset)
{
	u32 mss = skb_shinfo(skb)->gso_size;
	u32 opts1, opts2 = 0;
	int ret = TX_CSUM_SUCCESS;

	WARN_ON_ONCE(len > TX_LEN_MAX);

	opts1 = len | TX_FS | TX_LS;

	if (mss) {
		if (transport_offset > GTTCPHO_MAX) {
			netif_warn(tp, tx_err, tp->netdev,
				   "Invalid transport offset 0x%x for TSO\n",
				   transport_offset);
			ret = TX_CSUM_TSO;
			goto unavailable;
		}

		switch (vlan_get_protocol(skb)) {
		case htons(ETH_P_IP):
			opts1 |= GTSENDV4;
			break;

		case htons(ETH_P_IPV6):
			if (skb_cow_head(skb, 0)) {
				ret = TX_CSUM_TSO;
				goto unavailable;
			}
			tcp_v6_gso_csum_prep(skb);
			opts1 |= GTSENDV6;
			break;

		default:
			WARN_ON_ONCE(1);
			break;
		}

		opts1 |= transport_offset << GTTCPHO_SHIFT;
		opts2 |= min(mss, MSS_MAX) << MSS_SHIFT;
	} else if (skb->ip_summed == CHECKSUM_PARTIAL) {
		u8 ip_protocol;

		if (transport_offset > TCPHO_MAX) {
			netif_warn(tp, tx_err, tp->netdev,
				   "Invalid transport offset 0x%x\n",
				   transport_offset);
			ret = TX_CSUM_NONE;
			goto unavailable;
		}

		switch (vlan_get_protocol(skb)) {
		case htons(ETH_P_IP):
			opts2 |= IPV4_CS;
			ip_protocol = ip_hdr(skb)->protocol;
			break;

		case htons(ETH_P_IPV6):
			opts2 |= IPV6_CS;
			ip_protocol = ipv6_hdr(skb)->nexthdr;
			break;

		default:
			ip_protocol = IPPROTO_RAW;
			break;
		}

		if (ip_protocol == IPPROTO_TCP)
			opts2 |= TCP_CS;
		else if (ip_protocol == IPPROTO_UDP)
			opts2 |= UDP_CS;
		else
			WARN_ON_ONCE(1);

		opts2 |= transport_offset << TCPHO_SHIFT;
	}

	desc->opts2 = cpu_to_le32(opts2);
	desc->opts1 = cpu_to_le32(opts1);

unavailable:
	return ret;
}

static int r8152_tx_agg_fill(struct r8152 *tp, struct tx_agg *agg)
{
	struct sk_buff_head skb_head, *tx_queue = &tp->tx_queue;
	int remain, ret;
	u8 *tx_data;

	__skb_queue_head_init(&skb_head);
	spin_lock(&tx_queue->lock);
	skb_queue_splice_init(tx_queue, &skb_head);
	spin_unlock(&tx_queue->lock);

	tx_data = agg->head;
	agg->skb_num = 0;
	agg->skb_len = 0;
	remain = agg_buf_sz;

	while (remain >= ETH_ZLEN + sizeof(struct tx_desc)) {
		struct tx_desc *tx_desc;
		struct sk_buff *skb;
		unsigned int len;
		u32 offset;

		skb = __skb_dequeue(&skb_head);
		if (!skb)
			break;

		len = skb->len + sizeof(*tx_desc);

		if (len > remain) {
			__skb_queue_head(&skb_head, skb);
			break;
		}

		tx_data = tx_agg_align(tx_data);
		tx_desc = (struct tx_desc *)tx_data;

		offset = (u32)skb_transport_offset(skb);

		if (r8152_tx_csum(tp, tx_desc, skb, skb->len, offset)) {
			r8152_csum_workaround(tp, skb, &skb_head);
			continue;
		}

		rtl_tx_vlan_tag(tx_desc, skb);

		tx_data += sizeof(*tx_desc);

		len = skb->len;
		if (skb_copy_bits(skb, 0, tx_data, len) < 0) {
			struct net_device_stats *stats = &tp->netdev->stats;

			stats->tx_dropped++;
			dev_kfree_skb_any(skb);
			tx_data -= sizeof(*tx_desc);
			continue;
		}

		tx_data += len;
		agg->skb_len += len;
		agg->skb_num += skb_shinfo(skb)->gso_segs ?: 1;

		dev_consume_skb_any(skb);

		remain = agg_buf_sz - (int)(tx_agg_align(tx_data) - agg->head);
	}

	if (!skb_queue_empty(&skb_head)) {
		spin_lock(&tx_queue->lock);
		skb_queue_splice(&skb_head, tx_queue);
		spin_unlock(&tx_queue->lock);
	}

	netif_tx_lock(tp->netdev);

	if (netif_queue_stopped(tp->netdev) &&
	    skb_queue_len(&tp->tx_queue) < tp->tx_qlen)
		netif_wake_queue(tp->netdev);

	netif_tx_unlock(tp->netdev);

	ret = usb_autopm_get_interface_async(tp->intf);
	if (ret < 0)
		goto out_tx_fill;

	usb_fill_bulk_urb(agg->urb, tp->udev, tp->pipe_out,
			  agg->head, (int)(tx_data - (u8 *)agg->head),
			  (usb_complete_t)write_bulk_callback, agg);

	agg->urb->sg = NULL;
	agg->urb->num_sgs = 0;

	ret = usb_submit_urb(agg->urb, GFP_ATOMIC);
	if (ret < 0)
		usb_autopm_put_interface_async(tp->intf);

out_tx_fill:
	return ret;
}

static int r8152_tx_agg_sg_fill(struct r8152 *tp, struct tx_agg *agg)
{
	struct sk_buff_head skb_head, *tx_queue = &tp->tx_queue;
	int max_sg_num, ret, sg_num;
	struct scatterlist *sg;
	int padding = 0;

	__skb_queue_head_init(&skb_head);
	spin_lock(&tx_queue->lock);
	skb_queue_splice_init(tx_queue, &skb_head);
	spin_unlock(&tx_queue->lock);

	sg = agg->head;
	max_sg_num = (agg_buf_sz / sizeof(*sg)) - 1;
	max_sg_num = min_t(int, RTL_MAX_SG_NUM, max_sg_num);
	sg_init_table(sg, max_sg_num + 1);
	agg->skb_num = 0;
	agg->skb_len = 0;

	for (sg_num = 0; sg_num < max_sg_num;) {
		struct tx_desc tx_desc;
		struct sk_buff *skb;
		int num_sgs, headroom;
		unsigned int len;
		u32 offset;

		skb = __skb_dequeue(&skb_head);
		if (!skb)
			break;

		headroom = skb_headroom(skb) - padding - sizeof(tx_desc);

		if (skb_header_cloned(skb) || headroom < 0) {
			struct sk_buff *tx_skb;

			headroom = padding + sizeof(tx_desc);
			tx_skb = skb_copy_expand(skb, headroom, 0, GFP_ATOMIC);
			dev_kfree_skb_any(skb);
			if (!tx_skb) {
				struct net_device_stats *stats;

				stats = rtl8152_get_stats(tp->netdev);
				stats->tx_dropped++;
				netif_wake_queue(tp->netdev);
				return NETDEV_TX_OK;
			}
			skb = tx_skb;
			headroom = skb_headroom(skb) - headroom;
		}

		 /* calculate the fragment numbers for skb */
		num_sgs = 1 + skb_shinfo(skb)->nr_frags;
		len = skb->len;

		if ((num_sgs + sg_num) > max_sg_num) {
			__skb_queue_head(&skb_head, skb);
			break;
		}

		offset = (u32)skb_transport_offset(skb);

		if (r8152_tx_csum(tp, &tx_desc, skb, len, offset)) {
			r8152_csum_workaround(tp, skb, &skb_head);
			continue;
		}

		rtl_tx_vlan_tag(&tx_desc, skb);

		WARN_ON(padding < 0);

		/* use skb_headroom for tx desc */
		skb->cb[0] = padding + sizeof(tx_desc);
		memcpy(skb_push(skb, sizeof(tx_desc)), &tx_desc,
		       sizeof(tx_desc));
		if (padding)
			memset(skb_push(skb, padding), 0, padding);

		num_sgs = skb_to_sgvec_nomark(skb, sg, 0, skb->len);
		if (num_sgs < 0) {
			netif_err(tp, tx_err, tp->netdev,
				  "skb_to_sgvec fail %d\n", num_sgs);
			__skb_queue_head(&skb_head, skb);
			break;
		}

		sg += num_sgs;

		__skb_queue_tail(&agg->tx_skb, skb);

		sg_num += num_sgs;
		agg->skb_len += skb->len;
		padding = len + sizeof(tx_desc);

		agg->skb_num++;

		padding = ALIGN(padding, TX_ALIGN) - padding;
	}

	sg_mark_end(sg);

	if (!skb_queue_empty(&skb_head)) {
		spin_lock(&tx_queue->lock);
		skb_queue_splice(&skb_head, tx_queue);
		spin_unlock(&tx_queue->lock);
	}

	netif_tx_lock(tp->netdev);

	if (netif_queue_stopped(tp->netdev) &&
	    skb_queue_len(&tp->tx_queue) < tp->tx_qlen)
		netif_wake_queue(tp->netdev);

	netif_tx_unlock(tp->netdev);

	if (sg_num == 0) {
		unsigned long flags;

		spin_lock_irqsave(&tp->tx_lock, flags);
		list_add_tail(&agg->list, &tp->tx_free);
		spin_unlock_irqrestore(&tp->tx_lock, flags);

		ret = 0;
		goto out_tx_fill;
	}

	ret = usb_autopm_get_interface_async(tp->intf);
	if (ret < 0)
		goto out_tx_fill;

	usb_fill_bulk_urb(agg->urb, tp->udev, tp->pipe_out,
			  NULL, (int)agg->skb_len,
			  (usb_complete_t)write_bulk_sg_callback, agg);

	agg->urb->sg = agg->head;
	agg->urb->num_sgs = sg_num;

	ret = usb_submit_urb(agg->urb, GFP_ATOMIC);
	if (ret < 0)
		usb_autopm_put_interface_async(tp->intf);

out_tx_fill:
	return ret;
}

static u8 r8152_rx_csum(struct r8152 *tp, struct rx_desc *rx_desc)
{
	u8 checksum = CHECKSUM_NONE;
	u32 opts2, opts3;

	if (!(tp->netdev->features & NETIF_F_RXCSUM))
		goto return_result;

	opts2 = le32_to_cpu(rx_desc->opts2);
	opts3 = le32_to_cpu(rx_desc->opts3);

	if (opts2 & RD_IPV4_CS) {
		if (opts3 & IPF)
			checksum = CHECKSUM_NONE;
		else if ((opts2 & RD_UDP_CS) && !(opts3 & UDPF))
			checksum = CHECKSUM_UNNECESSARY;
		else if ((opts2 & RD_TCP_CS) && !(opts3 & TCPF))
			checksum = CHECKSUM_UNNECESSARY;
	} else if (opts2 & RD_IPV6_CS) {
		if ((opts2 & RD_UDP_CS) && !(opts3 & UDPF))
			checksum = CHECKSUM_UNNECESSARY;
		else if ((opts2 & RD_TCP_CS) && !(opts3 & TCPF))
			checksum = CHECKSUM_UNNECESSARY;
	}

return_result:
	return checksum;
}

static inline bool rx_count_exceed(struct r8152 *tp)
{
	return atomic_read(&tp->rx_count) > RTL8152_MAX_RX;
}

static inline int agg_offset(struct rx_agg *agg, void *addr)
{
	return (int)(addr - agg->buffer);
}

static struct rx_agg *rtl_get_free_rx(struct r8152 *tp, gfp_t mflags)
{
	struct rx_agg *agg, *agg_next, *agg_free = NULL;
	unsigned long flags;

	spin_lock_irqsave(&tp->rx_lock, flags);

	list_for_each_entry_safe(agg, agg_next, &tp->rx_used, list) {
		if (page_count(agg->page) == 1) {
			if (!agg_free) {
				list_del_init(&agg->list);
				agg_free = agg;
				continue;
			}
			if (rx_count_exceed(tp)) {
				list_del_init(&agg->list);
				free_rx_agg(tp, agg);
			}
			break;
		}
	}

	spin_unlock_irqrestore(&tp->rx_lock, flags);

	if (!agg_free && atomic_read(&tp->rx_count) < tp->rx_pending)
		agg_free = alloc_rx_agg(tp, mflags);

	return agg_free;
}

static int rx_bottom(struct r8152 *tp, int budget)
{
	unsigned long flags;
	struct list_head *cursor, *next, rx_queue;
	int ret = 0, work_done = 0;
	struct napi_struct *napi = &tp->napi;

	if (!skb_queue_empty(&tp->rx_queue)) {
		while (work_done < budget) {
			struct sk_buff *skb = __skb_dequeue(&tp->rx_queue);
			struct net_device *netdev = tp->netdev;
			struct net_device_stats *stats;
			unsigned int pkt_len;
#if LINUX_VERSION_CODE < KERNEL_VERSION(3,0,0)
			u16 vlan_tci;
#endif

			if (!skb)
				break;

			pkt_len = skb->len;
			stats = rtl8152_get_stats(netdev);
#if LINUX_VERSION_CODE < KERNEL_VERSION(3,0,0)
			vlan_tci = rtl_vlan_get_tag(skb);

			if (vlan_tci)
				vlan_gro_receive(napi, tp->vlgrp, vlan_tci,
						 skb);
			else
				napi_gro_receive(napi, skb);
#else
			napi_gro_receive(napi, skb);
#endif

			work_done++;

#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,29)
			netdev->last_rx = jiffies;
#endif
			stats->rx_packets++;
			stats->rx_bytes += pkt_len;
		}
	}

	if (list_empty(&tp->rx_done))
		goto out1;

	clear_bit(RX_EPROTO, &tp->flags);
	INIT_LIST_HEAD(&rx_queue);
	spin_lock_irqsave(&tp->rx_lock, flags);
	list_splice_init(&tp->rx_done, &rx_queue);
	spin_unlock_irqrestore(&tp->rx_lock, flags);

	list_for_each_safe(cursor, next, &rx_queue) {
		struct rx_desc *rx_desc;
		struct rx_agg *agg, *agg_free;
		int len_used = 0;
		struct urb *urb;
		u8 *rx_data;

		list_del_init(cursor);

		agg = list_entry(cursor, struct rx_agg, list);
		urb = agg->urb;
		if (urb->status != 0 || urb->actual_length < ETH_ZLEN)
			goto submit;

		agg_free = rtl_get_free_rx(tp, GFP_ATOMIC);

		rx_desc = agg->buffer;
		rx_data = agg->buffer;
		len_used += sizeof(struct rx_desc);

		while (urb->actual_length > len_used) {
			struct net_device *netdev = tp->netdev;
			struct net_device_stats *stats;
			unsigned int pkt_len, rx_frag_head_sz;
			struct sk_buff *skb;

			/* limit the skb numbers for rx_queue */
			if (unlikely(skb_queue_len(&tp->rx_queue) >= 1000))
				break;

			pkt_len = le32_to_cpu(rx_desc->opts1) & RX_LEN_MASK;
			if (pkt_len < ETH_ZLEN)
				break;

			len_used += pkt_len;
			if (urb->actual_length < len_used)
				break;

			stats = rtl8152_get_stats(netdev);

			pkt_len -= ETH_FCS_LEN;
			rx_data += sizeof(struct rx_desc);

			if (!agg_free || tp->rx_copybreak > pkt_len)
				rx_frag_head_sz = pkt_len;
			else
				rx_frag_head_sz = tp->rx_copybreak;

			skb = napi_alloc_skb(napi, rx_frag_head_sz);
			if (!skb) {
				stats->rx_dropped++;
				goto find_next_rx;
			}

			skb->ip_summed = r8152_rx_csum(tp, rx_desc);
			memcpy(skb->data, rx_data, rx_frag_head_sz);
			skb_put(skb, rx_frag_head_sz);
			pkt_len -= rx_frag_head_sz;
			rx_data += rx_frag_head_sz;
			if (pkt_len) {
				skb_add_rx_frag(skb, 0, agg->page,
						agg_offset(agg, rx_data),
						pkt_len,
						SKB_DATA_ALIGN(pkt_len));
				get_page(agg->page);
			}

#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,22)
			skb->dev = netdev;
#endif /* LINUX_VERSION_CODE < KERNEL_VERSION(2,6,22) */
			skb->protocol = eth_type_trans(skb, netdev);

#if LINUX_VERSION_CODE < KERNEL_VERSION(3,0,0)
			if (work_done < budget) {
				if (!rtl_rx_vlan_tag(tp, rx_desc, skb))
					napi_gro_receive(napi, skb);
#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,29)
				netdev->last_rx = jiffies;
#endif /* LINUX_VERSION_CODE < KERNEL_VERSION(2,6,29) */
				work_done++;
				stats->rx_packets++;
				stats->rx_bytes += skb->len;
			} else {
				rtl_vlan_put_tag(tp, rx_desc, skb);
				__skb_queue_tail(&tp->rx_queue, skb);
			}
#else
			rtl_rx_vlan_tag(rx_desc, skb);
			if (work_done < budget) {
				work_done++;
				stats->rx_packets++;
				stats->rx_bytes += skb->len;
				napi_gro_receive(napi, skb);
			} else {
				__skb_queue_tail(&tp->rx_queue, skb);
			}
#endif /* LINUX_VERSION_CODE < KERNEL_VERSION(3,0,0) */

find_next_rx:
			rx_data = rx_agg_align(rx_data + pkt_len + ETH_FCS_LEN);
			rx_desc = (struct rx_desc *)rx_data;
			len_used = agg_offset(agg, rx_data);
			len_used += sizeof(struct rx_desc);
		}

		WARN_ON(!agg_free && page_count(agg->page) > 1);

		if (agg_free) {
			spin_lock_irqsave(&tp->rx_lock, flags);
			if (page_count(agg->page) == 1) {
				list_add(&agg_free->list, &tp->rx_used);
			} else {
				list_add_tail(&agg->list, &tp->rx_used);
				agg = agg_free;
				urb = agg->urb;
			}
			spin_unlock_irqrestore(&tp->rx_lock, flags);
		}

submit:
		if (!ret) {
			ret = r8152_submit_rx(tp, agg, GFP_ATOMIC);
		} else {
			urb->actual_length = 0;
			list_add_tail(&agg->list, next);
		}
	}

	if (!list_empty(&rx_queue)) {
		spin_lock_irqsave(&tp->rx_lock, flags);
		list_splice_tail(&rx_queue, &tp->rx_done);
		spin_unlock_irqrestore(&tp->rx_lock, flags);
	}

out1:
	return work_done;
}

static void tx_bottom(struct r8152 *tp)
{
	int res;

	do {
		struct net_device *netdev = tp->netdev;
		struct tx_agg *agg;

		if (skb_queue_empty(&tp->tx_queue))
			break;

		agg = r8152_get_tx_agg(tp);
		if (!agg)
			break;

		if (tp->sg_use)
			res = r8152_tx_agg_sg_fill(tp, agg);
		else
			res = r8152_tx_agg_fill(tp, agg);

		if (!res)
			continue;

		if (res == -ENODEV) {
			rtl_set_unplug(tp);
			netif_device_detach(netdev);
		} else {
			struct net_device_stats *stats = &netdev->stats;
			unsigned long flags;

			netif_warn(tp, tx_err, netdev,
				   "failed tx_urb %d\n", res);
			stats->tx_dropped += agg->skb_num;

			spin_lock_irqsave(&tp->tx_lock, flags);
			list_add_tail(&agg->list, &tp->tx_free);
			spin_unlock_irqrestore(&tp->tx_lock, flags);
		}
	} while (res == 0);
}

#if LINUX_VERSION_CODE < KERNEL_VERSION(5,9,0)
static void bottom_half(unsigned long t)
#else
static void bottom_half(struct tasklet_struct *t)
#endif
{
	struct r8152 *tp = from_tasklet(tp, t, tx_tl);

	if (test_bit(RTL8152_UNPLUG, &tp->flags))
		return;

	if (!test_bit(WORK_ENABLE, &tp->flags))
		return;

	/* When link down, the driver would cancel all bulks. */
	/* This avoid the re-submitting bulk */
	if (!netif_carrier_ok(tp->netdev))
		return;

	clear_bit(SCHEDULE_TASKLET, &tp->flags);

	tx_bottom(tp);
}

static inline int __r8152_poll(struct r8152 *tp, int budget)
{
	struct napi_struct *napi = &tp->napi;
	int work_done;

	work_done = rx_bottom(tp, budget);

	if (work_done < budget) {
#if LINUX_VERSION_CODE < KERNEL_VERSION(4,10,0)
		napi_complete_done(napi, work_done);
#else
		if (!napi_complete_done(napi, work_done))
			goto out;
#endif
		if (!list_empty(&tp->rx_done))
			napi_schedule(napi);
	}

#if LINUX_VERSION_CODE >= KERNEL_VERSION(4,10,0)
out:
#endif
	return work_done;
}

#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,24)

static int r8152_poll(struct net_device *dev, int *budget)
{
	struct r8152 *tp = netdev_priv(dev);
	int quota = min(dev->quota, *budget);
	int work_done;

	work_done = __r8152_poll(tp, quota);

	*budget -= work_done;
	dev->quota -= work_done;

	return (work_done >= quota);
}

#else

static int r8152_poll(struct napi_struct *napi, int budget)
{
	struct r8152 *tp = container_of(napi, struct r8152, napi);

	return __r8152_poll(tp, budget);
}

#endif /* LINUX_VERSION_CODE < KERNEL_VERSION(2,6,24) */

static
int r8152_submit_rx(struct r8152 *tp, struct rx_agg *agg, gfp_t mem_flags)
{
	int ret;

	/* The rx would be stopped, so skip submitting */
	if (test_bit(RTL8152_UNPLUG, &tp->flags) ||
	    !test_bit(WORK_ENABLE, &tp->flags) || !netif_carrier_ok(tp->netdev))
		return 0;

	usb_fill_bulk_urb(agg->urb, tp->udev, tp->pipe_in,
			  agg->buffer, tp->rx_buf_sz,
			  (usb_complete_t)read_bulk_callback, agg);

	ret = usb_submit_urb(agg->urb, mem_flags);
	if (ret == -ENODEV) {
		rtl_set_unplug(tp);
		netif_device_detach(tp->netdev);
	} else if (ret) {
		struct urb *urb = agg->urb;
		unsigned long flags;

		urb->actual_length = 0;
		spin_lock_irqsave(&tp->rx_lock, flags);
		list_add_tail(&agg->list, &tp->rx_done);
		spin_unlock_irqrestore(&tp->rx_lock, flags);

		netif_err(tp, rx_err, tp->netdev,
			  "Couldn't submit rx[%p], ret = %d\n", agg, ret);

		napi_schedule(&tp->napi);
	}

	return ret;
}

static void rtl_drop_queued_tx(struct r8152 *tp)
{
	struct net_device_stats *stats = rtl8152_get_stats(tp->netdev);
	struct sk_buff_head skb_head, *tx_queue = &tp->tx_queue;
	struct sk_buff *skb;

	if (skb_queue_empty(tx_queue))
		return;

	__skb_queue_head_init(&skb_head);
	spin_lock_bh(&tx_queue->lock);
	skb_queue_splice_init(tx_queue, &skb_head);
	spin_unlock_bh(&tx_queue->lock);

	while ((skb = __skb_dequeue(&skb_head))) {
		dev_kfree_skb(skb);
		stats->tx_dropped++;
	}
}

#if LINUX_VERSION_CODE < KERNEL_VERSION(5,6,0)
static void rtl8152_tx_timeout(struct net_device *netdev)
#else
static void rtl8152_tx_timeout(struct net_device *netdev, unsigned int txqueue)
#endif /* LINUX_VERSION_CODE < KERNEL_VERSION(5,6,0) */
{
	struct r8152 *tp = netdev_priv(netdev);
#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,29)
	int i;
#endif

	netif_warn(tp, tx_err, netdev, "Tx timeout\n");

#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,29)
	for (i = 0; i < RTL8152_MAX_TX; i++)
		usb_unlink_urb(tp->tx_info[i].urb);
#else
	usb_queue_reset_device(tp->intf);
#endif
}

static void rtl8152_set_rx_mode(struct net_device *netdev)
{
	struct r8152 *tp = netdev_priv(netdev);
	u32 mc_filter[2];	/* Multicast hash filter */
	__le32 tmp[2];
	u32 ocp_data;

	if (in_atomic()) {
		if (netif_carrier_ok(netdev)) {
			set_bit(RTL8152_SET_RX_MODE, &tp->flags);
			schedule_delayed_work(&tp->schedule, 0);
		}
		return;
	}

	clear_bit(RTL8152_SET_RX_MODE, &tp->flags);

	if (!netif_carrier_ok(netdev))
		return;

	netif_stop_queue(netdev);
	ocp_data = ocp_read_dword(tp, MCU_TYPE_PLA, PLA_RCR);
	ocp_data &= ~RCR_ACPT_ALL;
	ocp_data |= RCR_AB | RCR_APM;

	if (netdev->flags & IFF_PROMISC) {
		/* Unconditionally log net taps. */
		netif_notice(tp, link, netdev, "Promiscuous mode enabled\n");
		ocp_data |= RCR_AM | RCR_AAP;
		mc_filter[1] = 0xffffffff;
		mc_filter[0] = 0xffffffff;
	} else if ((netdev_mc_count(netdev) > multicast_filter_limit) ||
		   (netdev->flags & IFF_ALLMULTI)) {
		/* Too many to filter perfectly -- accept all multicasts. */
		ocp_data |= RCR_AM;
		mc_filter[1] = 0xffffffff;
		mc_filter[0] = 0xffffffff;
	} else {
#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,35)
		struct dev_mc_list *mclist;
		unsigned int i;

		mc_filter[1] = mc_filter[0] = 0;
		for (i = 0, mclist = netdev->mc_list;
		     mclist && i < netdev->mc_count;
		     i++, mclist = mclist->next) {
			int bit_nr;

			bit_nr = ether_crc(ETH_ALEN, mclist->dmi_addr) >> 26;
			mc_filter[bit_nr >> 5] |= 1 << (bit_nr & 31);
			ocp_data |= RCR_AM;
		}
#else
		struct netdev_hw_addr *ha;

		mc_filter[1] = 0;
		mc_filter[0] = 0;
		netdev_for_each_mc_addr(ha, netdev) {
			int bit_nr = ether_crc(ETH_ALEN, ha->addr) >> 26;

			mc_filter[bit_nr >> 5] |= 1 << (bit_nr & 31);
			ocp_data |= RCR_AM;
		}
#endif
	}

	tmp[0] = __cpu_to_le32(swab32(mc_filter[1]));
	tmp[1] = __cpu_to_le32(swab32(mc_filter[0]));

	pla_ocp_write(tp, PLA_MAR, BYTE_EN_DWORD, sizeof(tmp), tmp);
	ocp_write_dword(tp, MCU_TYPE_PLA, PLA_RCR, ocp_data);
	netif_wake_queue(netdev);
}

static inline bool rtl_gso_check(struct net_device *dev, struct sk_buff *skb)
{
	struct r8152 *tp = netdev_priv(dev);

	if (tp->sg_use)
		return true;
	else if ((skb->len + sizeof(struct tx_desc)) <= agg_buf_sz)
		return true;
	else
		return false;
}

#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,18,4)

static netdev_features_t
rtl8152_features_check(struct sk_buff *skb, struct net_device *dev,
		       netdev_features_t features)
{
	u32 mss = skb_shinfo(skb)->gso_size;
	int max_offset = mss ? GTTCPHO_MAX : TCPHO_MAX;
	int offset = skb_transport_offset(skb);

	if ((mss || skb->ip_summed == CHECKSUM_PARTIAL) && offset > max_offset)
		features &= ~(NETIF_F_CSUM_MASK | NETIF_F_GSO_MASK);
	else if (!rtl_gso_check(dev, skb))
		features &= ~NETIF_F_GSO_MASK;

	return features;
}
#endif /* LINUX_VERSION_CODE >= KERNEL_VERSION(3,18,4) */

static netdev_tx_t rtl8152_start_xmit(struct sk_buff *skb,
				      struct net_device *netdev)
{
	struct r8152 *tp = netdev_priv(netdev);

#if LINUX_VERSION_CODE < KERNEL_VERSION(3,18,4)
	if (unlikely(!rtl_gso_check(netdev, skb))) {
		netdev_features_t features = netdev->features;
		struct sk_buff *segs, *nskb;

		features &= ~(NETIF_F_TSO | NETIF_F_TSO6);
		segs = skb_gso_segment(skb, features);
		if (IS_ERR(segs) || !segs)
			goto free_skb;

		do {
			nskb = segs;
			segs = segs->next;
			nskb->next = NULL;
			rtl8152_start_xmit(nskb, netdev);
		} while (segs);

free_skb:
		dev_kfree_skb_any(skb);

		return NETDEV_TX_OK;
	}
#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,31)
	netdev->trans_start = jiffies
#endif /* LINUX_VERSION_CODE < KERNEL_VERSION(2,6,31) */
#endif /* LINUX_VERSION_CODE < KERNEL_VERSION(3,18,4) */

	skb_tx_timestamp(skb);

	skb_queue_tail(&tp->tx_queue, skb);

	if (!list_empty(&tp->tx_free)) {
		if (test_bit(SELECTIVE_SUSPEND, &tp->flags)) {
			set_bit(SCHEDULE_TASKLET, &tp->flags);
			schedule_delayed_work(&tp->schedule, 0);
		} else {
			usb_mark_last_busy(tp->udev);
			tasklet_schedule(&tp->tx_tl);
		}
	} else if (skb_queue_len(&tp->tx_queue) > tp->tx_qlen) {
		netif_stop_queue(netdev);
	}

	return NETDEV_TX_OK;
}

static void r8152b_reset_packet_filter(struct r8152 *tp)
{
	u32 ocp_data;

	ocp_data = ocp_read_word(tp, MCU_TYPE_PLA, PLA_FMC);
	ocp_data &= ~FMC_FCR_MCU_EN;
	ocp_write_word(tp, MCU_TYPE_PLA, PLA_FMC, ocp_data);
	ocp_data |= FMC_FCR_MCU_EN;
	ocp_write_word(tp, MCU_TYPE_PLA, PLA_FMC, ocp_data);
}

static void rtl8152_nic_reset(struct r8152 *tp)
{
	u32 ocp_data;
	int i;

	switch (tp->version) {
	case RTL_TEST_01:
	case RTL_VER_10:
	case RTL_VER_11:
		ocp_data = ocp_read_byte(tp, MCU_TYPE_PLA, PLA_CR);
		ocp_data &= ~CR_TE;
		ocp_write_byte(tp, MCU_TYPE_PLA, PLA_CR, ocp_data);

		ocp_data = ocp_read_word(tp, MCU_TYPE_USB, USB_BMU_RESET);
		ocp_data &= ~BMU_RESET_EP_IN;
		ocp_write_word(tp, MCU_TYPE_USB, USB_BMU_RESET, ocp_data);

		ocp_data = ocp_read_word(tp, MCU_TYPE_USB, USB_USB_CTRL);
		ocp_data |= CDC_ECM_EN;
		ocp_write_word(tp, MCU_TYPE_USB, USB_USB_CTRL, ocp_data);

		ocp_data = ocp_read_byte(tp, MCU_TYPE_PLA, PLA_CR);
		ocp_data &= ~CR_RE;
		ocp_write_byte(tp, MCU_TYPE_PLA, PLA_CR, ocp_data);

		ocp_data = ocp_read_word(tp, MCU_TYPE_USB, USB_BMU_RESET);
		ocp_data |= BMU_RESET_EP_IN;
		ocp_write_word(tp, MCU_TYPE_USB, USB_BMU_RESET, ocp_data);

		ocp_data = ocp_read_word(tp, MCU_TYPE_USB, USB_USB_CTRL);
		ocp_data &= ~CDC_ECM_EN;
		ocp_write_word(tp, MCU_TYPE_USB, USB_USB_CTRL, ocp_data);
		break;

	default:
		ocp_write_byte(tp, MCU_TYPE_PLA, PLA_CR, CR_RST);

		for (i = 0; i < 1000; i++) {
			if (!(ocp_read_byte(tp, MCU_TYPE_PLA, PLA_CR) & CR_RST))
				break;
			usleep_range(100, 400);
		}
		break;
	}
}

static void set_tx_qlen(struct r8152 *tp)
{
	if (tp->sg_use)
		tp->tx_qlen = RTL_MAX_SG_NUM;
	else
		tp->tx_qlen = agg_buf_sz / (mtu_to_size(tp->netdev->mtu) + sizeof(struct tx_desc));
}

static inline u16 rtl8152_get_speed(struct r8152 *tp)
{
	return ocp_read_word(tp, MCU_TYPE_PLA, PLA_PHYSTATUS);
}

static void rtl_eee_plus_en(struct r8152 *tp, bool enable)
{
	u32 ocp_data;

	ocp_data = ocp_read_word(tp, MCU_TYPE_PLA, PLA_EEEP_CR);
	if (enable)
		ocp_data |= EEEP_CR_EEEP_TX;
	else
		ocp_data &= ~EEEP_CR_EEEP_TX;
	ocp_write_word(tp, MCU_TYPE_PLA, PLA_EEEP_CR, ocp_data);
}

static void rtl_set_eee_plus(struct r8152 *tp)
{
	if (rtl8152_get_speed(tp) & _10bps)
		rtl_eee_plus_en(tp, true);
	else
		rtl_eee_plus_en(tp, false);
}

static void rxdy_gated_en(struct r8152 *tp, bool enable)
{
	u32 ocp_data;

	ocp_data = ocp_read_word(tp, MCU_TYPE_PLA, PLA_MISC_1);
	if (enable)
		ocp_data |= RXDY_GATED_EN;
	else
		ocp_data &= ~RXDY_GATED_EN;
	ocp_write_word(tp, MCU_TYPE_PLA, PLA_MISC_1, ocp_data);
}

static int rtl_start_rx(struct r8152 *tp)
{
	struct rx_agg *agg, *agg_next;
	struct list_head tmp_list;
	unsigned long flags;
	int ret = 0, i = 0;

	INIT_LIST_HEAD(&tmp_list);

	spin_lock_irqsave(&tp->rx_lock, flags);

	INIT_LIST_HEAD(&tp->rx_done);
	INIT_LIST_HEAD(&tp->rx_used);

	list_splice_init(&tp->rx_info, &tmp_list);

	spin_unlock_irqrestore(&tp->rx_lock, flags);

	list_for_each_entry_safe(agg, agg_next, &tmp_list, info_list) {
		INIT_LIST_HEAD(&agg->list);

		/* Only RTL8152_MAX_RX rx_agg need to be submitted. */
		if (++i > RTL8152_MAX_RX) {
			spin_lock_irqsave(&tp->rx_lock, flags);
			list_add_tail(&agg->list, &tp->rx_used);
			spin_unlock_irqrestore(&tp->rx_lock, flags);
		} else if (unlikely(ret < 0)) {
			spin_lock_irqsave(&tp->rx_lock, flags);
			list_add_tail(&agg->list, &tp->rx_done);
			spin_unlock_irqrestore(&tp->rx_lock, flags);
		} else {
			ret = r8152_submit_rx(tp, agg, GFP_KERNEL);
		}
	}

	spin_lock_irqsave(&tp->rx_lock, flags);
	WARN_ON(!list_empty(&tp->rx_info));
	list_splice(&tmp_list, &tp->rx_info);
	spin_unlock_irqrestore(&tp->rx_lock, flags);

	return ret;
}

static int rtl_stop_rx(struct r8152 *tp)
{
	struct rx_agg *agg, *agg_next;
	struct list_head tmp_list;
	unsigned long flags;

	INIT_LIST_HEAD(&tmp_list);

	/* The usb_kill_urb() couldn't be used in atomic.
	 * Therefore, move the list of rx_info to a tmp one.
	 * Then, list_for_each_entry_safe could be used without
	 * spin lock.
	 */

	spin_lock_irqsave(&tp->rx_lock, flags);
	list_splice_init(&tp->rx_info, &tmp_list);
	spin_unlock_irqrestore(&tp->rx_lock, flags);

	list_for_each_entry_safe(agg, agg_next, &tmp_list, info_list) {
		/* At least RTL8152_MAX_RX rx_agg have the page_count being
		 * equal to 1, so the other ones could be freed safely.
		 */
		if (page_count(agg->page) > 1)
			free_rx_agg(tp, agg);
		else
			usb_kill_urb(agg->urb);
	}

	/* Move back the list of temp to the rx_info */
	spin_lock_irqsave(&tp->rx_lock, flags);
	WARN_ON(!list_empty(&tp->rx_info));
	list_splice(&tmp_list, &tp->rx_info);
	spin_unlock_irqrestore(&tp->rx_lock, flags);

	while (!skb_queue_empty(&tp->rx_queue))
		dev_kfree_skb(__skb_dequeue(&tp->rx_queue));

	return 0;
}

static void rtl_set_ifg(struct r8152 *tp, u16 speed)
{
	u32 ocp_data;

	ocp_data = ocp_read_word(tp, MCU_TYPE_PLA, PLA_TCR1);
	ocp_data &= ~IFG_MASK;
	if ((speed & (_10bps | _100bps)) && !(speed & FULL_DUP)) {
		ocp_data |= IFG_144NS;
		ocp_write_word(tp, MCU_TYPE_PLA, PLA_TCR1, ocp_data);

		ocp_data = ocp_read_word(tp, MCU_TYPE_PLA, PLA_MAC_PWR_CTRL4);
		ocp_data &= ~TX10MIDLE_EN;
		ocp_write_word(tp, MCU_TYPE_PLA, PLA_MAC_PWR_CTRL4, ocp_data);
	} else {
		ocp_data |= IFG_96NS;
		ocp_write_word(tp, MCU_TYPE_PLA, PLA_TCR1, ocp_data);

		ocp_data = ocp_read_word(tp, MCU_TYPE_PLA, PLA_MAC_PWR_CTRL4);
		ocp_data |= TX10MIDLE_EN;
		ocp_write_word(tp, MCU_TYPE_PLA, PLA_MAC_PWR_CTRL4, ocp_data);
	}
}

static inline void r8153b_rx_agg_chg_indicate(struct r8152 *tp)
{
	ocp_write_byte(tp, MCU_TYPE_USB, USB_UPT_RXDMA_OWN,
		       OWN_UPDATE | OWN_CLEAR);
}

static int rtl_enable(struct r8152 *tp)
{
	u32 ocp_data;

	r8152b_reset_packet_filter(tp);

	ocp_data = ocp_read_byte(tp, MCU_TYPE_PLA, PLA_CR);
	ocp_data |= CR_RE | CR_TE;
	ocp_write_byte(tp, MCU_TYPE_PLA, PLA_CR, ocp_data);

	switch (tp->version) {
	case RTL_VER_08:
	case RTL_VER_09:
	case RTL_VER_14:
		r8153b_rx_agg_chg_indicate(tp);
		break;
	default:
		break;
	}

	rxdy_gated_en(tp, false);

	return 0;
}

static int rtl8152_enable(struct r8152 *tp)
{
	if (test_bit(RTL8152_UNPLUG, &tp->flags))
		return -ENODEV;

	set_tx_qlen(tp);
	rtl_set_eee_plus(tp);

	return rtl_enable(tp);
}

static void r8153_set_rx_early_timeout(struct r8152 *tp)
{
	u32 ocp_data = tp->coalesce / 8;

	switch (tp->version) {
	case RTL_VER_03:
	case RTL_VER_04:
	case RTL_VER_05:
	case RTL_VER_06:
		ocp_write_word(tp, MCU_TYPE_USB, USB_RX_EARLY_TIMEOUT,
			       ocp_data);
		break;

	case RTL_VER_08:
	case RTL_VER_09:
	case RTL_VER_14:
		/* The RTL8153B uses USB_RX_EXTRA_AGGR_TMR for rx timeout
		 * primarily. For USB_RX_EARLY_TIMEOUT, we fix it to 1264ns.
		 */
		ocp_write_word(tp, MCU_TYPE_USB, USB_RX_EARLY_TIMEOUT,
			       1264 / 8);
		ocp_write_word(tp, MCU_TYPE_USB, USB_RX_EXTRA_AGGR_TMR,
			       ocp_data);
		break;

	case RTL_VER_10:
	case RTL_VER_11:
	case RTL_VER_12:
	case RTL_VER_13:
	case RTL_VER_15:
		ocp_write_word(tp, MCU_TYPE_USB, USB_RX_EARLY_TIMEOUT,
			       640 / 8);
		ocp_write_word(tp, MCU_TYPE_USB, USB_RX_EXTRA_AGGR_TMR,
			       ocp_data);
		r8153b_rx_agg_chg_indicate(tp);
		break;

	default:
		break;
	}
}

static void r8153_set_rx_early_size(struct r8152 *tp)
{
	u32 ocp_data = tp->rx_buf_sz - rx_reserved_size(tp->netdev->mtu);

	switch (tp->version) {
	case RTL_VER_03:
	case RTL_VER_04:
	case RTL_VER_05:
	case RTL_VER_06:
		ocp_write_word(tp, MCU_TYPE_USB, USB_RX_EARLY_SIZE,
			       ocp_data / 4);
		break;
	case RTL_VER_08:
	case RTL_VER_09:
	case RTL_VER_14:
		ocp_write_word(tp, MCU_TYPE_USB, USB_RX_EARLY_SIZE,
			       ocp_data / 8);
		break;
	case RTL_TEST_01:
	case RTL_VER_10:
	case RTL_VER_11:
	case RTL_VER_12:
	case RTL_VER_13:
	case RTL_VER_15:
		ocp_write_word(tp, MCU_TYPE_USB, USB_RX_EARLY_SIZE,
			       ocp_data / 8);
		r8153b_rx_agg_chg_indicate(tp);
		break;
	default:
		WARN_ON_ONCE(1);
		break;
	}
}

static int rtl8153_enable(struct r8152 *tp)
{
	u32 ocp_data;

	if (test_bit(RTL8152_UNPLUG, &tp->flags))
		return -ENODEV;

	set_tx_qlen(tp);
	rtl_set_eee_plus(tp);
	r8153_set_rx_early_timeout(tp);
	r8153_set_rx_early_size(tp);

	rtl_set_ifg(tp, rtl8152_get_speed(tp));

	switch (tp->version) {
	case RTL_VER_09:
	case RTL_VER_14:
		ocp_data = ocp_read_word(tp, MCU_TYPE_USB, USB_FW_TASK);
		ocp_data &= ~FC_PATCH_TASK;
		ocp_write_word(tp, MCU_TYPE_USB, USB_FW_TASK, ocp_data);
		usleep_range(1000, 2000);
		ocp_data |= FC_PATCH_TASK;
		ocp_write_word(tp, MCU_TYPE_USB, USB_FW_TASK, ocp_data);
		break;
	default:
		break;
	}

	return rtl_enable(tp);
}

static void rtl_disable(struct r8152 *tp)
{
	u32 ocp_data;
	int i;

	if (test_bit(RTL8152_UNPLUG, &tp->flags)) {
		rtl_drop_queued_tx(tp);
		return;
	}

	ocp_data = ocp_read_dword(tp, MCU_TYPE_PLA, PLA_RCR);
	ocp_data &= ~RCR_ACPT_ALL;
	ocp_write_dword(tp, MCU_TYPE_PLA, PLA_RCR, ocp_data);

	rtl_drop_queued_tx(tp);

	for (i = 0; i < RTL8152_MAX_TX; i++)
		usb_kill_urb(tp->tx_info[i].urb);

	rxdy_gated_en(tp, true);

	for (i = 0; i < 1000; i++) {
		ocp_data = ocp_read_byte(tp, MCU_TYPE_PLA, PLA_OOB_CTRL);
		if ((ocp_data & FIFO_EMPTY) == FIFO_EMPTY)
			break;
		usleep_range(1000, 2000);
	}

	for (i = 0; i < 1000; i++) {
		if (ocp_read_word(tp, MCU_TYPE_PLA, PLA_TCR0) & TCR0_TX_EMPTY)
			break;
		usleep_range(1000, 2000);
	}

	rtl_stop_rx(tp);

	rtl8152_nic_reset(tp);
}

static void r8152_power_cut_en(struct r8152 *tp, bool enable)
{
	u32 ocp_data;

	ocp_data = ocp_read_word(tp, MCU_TYPE_USB, USB_UPS_CTRL);
	if (enable)
		ocp_data |= POWER_CUT;
	else
		ocp_data &= ~POWER_CUT;
	ocp_write_word(tp, MCU_TYPE_USB, USB_UPS_CTRL, ocp_data);

	ocp_data = ocp_read_word(tp, MCU_TYPE_USB, USB_PM_CTRL_STATUS);
	ocp_data &= ~RESUME_INDICATE;
	ocp_write_word(tp, MCU_TYPE_USB, USB_PM_CTRL_STATUS, ocp_data);
}

static void rtl_rx_vlan_en(struct r8152 *tp, bool enable)
{
	u32 ocp_data;

	switch (tp->version) {
	case RTL_VER_01:
	case RTL_VER_02:
	case RTL_VER_03:
	case RTL_VER_04:
	case RTL_VER_05:
	case RTL_VER_06:
	case RTL_VER_07:
	case RTL_VER_08:
	case RTL_VER_09:
	case RTL_VER_14:
		ocp_data = ocp_read_word(tp, MCU_TYPE_PLA, PLA_CPCR);
		if (enable)
			ocp_data |= CPCR_RX_VLAN;
		else
			ocp_data &= ~CPCR_RX_VLAN;
		ocp_write_word(tp, MCU_TYPE_PLA, PLA_CPCR, ocp_data);
		break;

	case RTL_TEST_01:
	case RTL_VER_10:
	case RTL_VER_11:
	case RTL_VER_12:
	case RTL_VER_13:
	case RTL_VER_15:
	default:
		ocp_data = ocp_read_word(tp, MCU_TYPE_PLA, PLA_RCR1);
		if (enable)
			ocp_data |= OUTER_VLAN | INNER_VLAN;
		else
			ocp_data &= ~(OUTER_VLAN | INNER_VLAN);
		ocp_write_word(tp, MCU_TYPE_PLA, PLA_RCR1, ocp_data);
		break;
	}
}

#if LINUX_VERSION_CODE < KERNEL_VERSION(3,0,0)

static void
rtl8152_vlan_rx_register(struct net_device *dev, struct vlan_group *grp)
{
	struct r8152 *tp = netdev_priv(dev);

	if (unlikely(tp->rtk_enable_diag))
		return;

	if (usb_autopm_get_interface(tp->intf) < 0)
		return;

	mutex_lock(&tp->control);

	tp->vlgrp = grp;
	if (tp->vlgrp)
		rtl_rx_vlan_en(tp, true);
	else
		rtl_rx_vlan_en(tp, false);

	mutex_unlock(&tp->control);
}

#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,22)

static void rtl8152_vlan_rx_kill_vid(struct net_device *dev, unsigned short vid)
{
	struct r8152 *tp = netdev_priv(dev);

	vlan_group_set_device(tp->vlgrp, vid, NULL);
}

#endif /* LINUX_VERSION_CODE < KERNEL_VERSION(2,6,22) */

#else

static int rtl8152_set_features(struct net_device *dev,
				netdev_features_t features)
{
	netdev_features_t changed = features ^ dev->features;
	struct r8152 *tp = netdev_priv(dev);
	int ret;

	if (unlikely(tp->rtk_enable_diag))
		return -EBUSY;

	ret = usb_autopm_get_interface(tp->intf);
	if (ret < 0)
		goto out;

	mutex_lock(&tp->control);

	if (changed & NETIF_F_HW_VLAN_CTAG_RX) {
		if (features & NETIF_F_HW_VLAN_CTAG_RX)
			rtl_rx_vlan_en(tp, true);
		else
			rtl_rx_vlan_en(tp, false);
	}

	mutex_unlock(&tp->control);

	usb_autopm_put_interface(tp->intf);

out:
	return ret;
}

#endif /* LINUX_VERSION_CODE < KERNEL_VERSION(3,0,0) */

#define WAKE_ANY (WAKE_PHY | WAKE_MAGIC | WAKE_UCAST | WAKE_BCAST | WAKE_MCAST)

static u32 __rtl_get_wol(struct r8152 *tp)
{
	u32 ocp_data;
	u32 wolopts = 0;

	ocp_data = ocp_read_word(tp, MCU_TYPE_PLA, PLA_CONFIG34);
	if (ocp_data & LINK_ON_WAKE_EN)
		wolopts |= WAKE_PHY;

	ocp_data = ocp_read_word(tp, MCU_TYPE_PLA, PLA_CONFIG5);
	if (ocp_data & UWF_EN)
		wolopts |= WAKE_UCAST;
	if (ocp_data & BWF_EN)
		wolopts |= WAKE_BCAST;
	if (ocp_data & MWF_EN)
		wolopts |= WAKE_MCAST;

	ocp_data = ocp_read_word(tp, MCU_TYPE_PLA, PLA_CFG_WOL);
	if (ocp_data & MAGIC_EN)
		wolopts |= WAKE_MAGIC;

	return wolopts;
}

static void __rtl_set_wol(struct r8152 *tp, u32 wolopts)
{
	u32 ocp_data;

	ocp_write_byte(tp, MCU_TYPE_PLA, PLA_CRWECR, CRWECR_CONFIG);

	ocp_data = ocp_read_word(tp, MCU_TYPE_PLA, PLA_CONFIG34);
	ocp_data &= ~LINK_ON_WAKE_EN;
	if (wolopts & WAKE_PHY)
		ocp_data |= LINK_ON_WAKE_EN;
	ocp_write_word(tp, MCU_TYPE_PLA, PLA_CONFIG34, ocp_data);

	ocp_data = ocp_read_word(tp, MCU_TYPE_PLA, PLA_CONFIG5);
	ocp_data &= ~(UWF_EN | BWF_EN | MWF_EN);
	if (wolopts & WAKE_UCAST)
		ocp_data |= UWF_EN;
	if (wolopts & WAKE_BCAST)
		ocp_data |= BWF_EN;
	if (wolopts & WAKE_MCAST)
		ocp_data |= MWF_EN;
	ocp_write_word(tp, MCU_TYPE_PLA, PLA_CONFIG5, ocp_data);

	ocp_write_byte(tp, MCU_TYPE_PLA, PLA_CRWECR, CRWECR_NORAML);

	ocp_data = ocp_read_word(tp, MCU_TYPE_PLA, PLA_CFG_WOL);
	ocp_data &= ~MAGIC_EN;
	if (wolopts & WAKE_MAGIC)
		ocp_data |= MAGIC_EN;
	ocp_write_word(tp, MCU_TYPE_PLA, PLA_CFG_WOL, ocp_data);

	if (wolopts & WAKE_ANY)
		device_set_wakeup_enable(&tp->udev->dev, true);
	else
		device_set_wakeup_enable(&tp->udev->dev, false);
}

static void r8153_mac_clk_speed_down(struct r8152 *tp, bool enable)
{
	u32 ocp_data = ocp_read_word(tp, MCU_TYPE_PLA, PLA_MAC_PWR_CTRL2);

	/* MAC clock speed down */
	if (enable)
		ocp_data |= MAC_CLK_SPDWN_EN;
	else
		ocp_data &= ~MAC_CLK_SPDWN_EN;

	ocp_write_word(tp, MCU_TYPE_PLA, PLA_MAC_PWR_CTRL2, ocp_data);
}

static void r8156_mac_clk_spd(struct r8152 *tp, bool enable)
{
	u32 ocp_data;

	/* MAC clock speed down */
	if (enable) {
		/* aldps_spdwn_ratio, tp10_spdwn_ratio */
		ocp_write_word(tp, MCU_TYPE_PLA, PLA_MAC_PWR_CTRL,
			       0x0403);

		ocp_data = ocp_read_word(tp, MCU_TYPE_PLA, PLA_MAC_PWR_CTRL2);
		ocp_data &= ~EEE_SPDWN_RATIO_MASK;
		ocp_data |= MAC_CLK_SPDWN_EN | 0x03; /* eee_spdwn_ratio */
		ocp_write_word(tp, MCU_TYPE_PLA, PLA_MAC_PWR_CTRL2, ocp_data);
	} else {
		ocp_data = ocp_read_word(tp, MCU_TYPE_PLA, PLA_MAC_PWR_CTRL2);
		ocp_data &= ~MAC_CLK_SPDWN_EN;
		ocp_write_word(tp, MCU_TYPE_PLA, PLA_MAC_PWR_CTRL2, ocp_data);
	}
}

static void r8153_u1u2en(struct r8152 *tp, bool enable)
{
	u8 u1u2[8];

	if (enable)
		memset(u1u2, 0xff, sizeof(u1u2));
	else
		memset(u1u2, 0x00, sizeof(u1u2));

	usb_ocp_write(tp, USB_TOLERANCE, BYTE_EN_SIX_BYTES, sizeof(u1u2), u1u2);
}

static void r8153b_u1u2en(struct r8152 *tp, bool enable)
{
	u32 ocp_data;

	ocp_data = ocp_read_word(tp, MCU_TYPE_USB, USB_LPM_CONFIG);
	if (enable)
		ocp_data |= LPM_U1U2_EN;
	else
		ocp_data &= ~LPM_U1U2_EN;

	ocp_write_word(tp, MCU_TYPE_USB, USB_LPM_CONFIG, ocp_data);
}

static void r8153_u2p3en(struct r8152 *tp, bool enable)
{
	u32 ocp_data;

	ocp_data = ocp_read_word(tp, MCU_TYPE_USB, USB_U2P3_CTRL);
	if (enable)
		ocp_data |= U2P3_ENABLE;
	else
		ocp_data &= ~U2P3_ENABLE;
	ocp_write_word(tp, MCU_TYPE_USB, USB_U2P3_CTRL, ocp_data);
}

static void r8153b_ups_flags(struct r8152 *tp)
{
	u32 ups_flags = 0;

	if (tp->ups_info.green)
		ups_flags |= UPS_FLAGS_EN_GREEN;

	if (tp->ups_info.aldps)
		ups_flags |= UPS_FLAGS_EN_ALDPS;

	if (tp->ups_info.eee)
		ups_flags |= UPS_FLAGS_EN_EEE;

	if (tp->ups_info.flow_control)
		ups_flags |= UPS_FLAGS_EN_FLOW_CTR;

	if (tp->ups_info.eee_ckdiv)
		ups_flags |= UPS_FLAGS_EN_EEE_CKDIV;

	if (tp->ups_info.eee_cmod_lv)
		ups_flags |= UPS_FLAGS_EEE_CMOD_LV_EN;

	if (tp->ups_info.r_tune)
		ups_flags |= UPS_FLAGS_R_TUNE;

	if (tp->ups_info._10m_ckdiv)
		ups_flags |= UPS_FLAGS_EN_10M_CKDIV;

	if (tp->ups_info.eee_plloff_100)
		ups_flags |= UPS_FLAGS_EEE_PLLOFF_100;

	if (tp->ups_info.eee_plloff_giga)
		ups_flags |= UPS_FLAGS_EEE_PLLOFF_GIGA;

	if (tp->ups_info._250m_ckdiv)
		ups_flags |= UPS_FLAGS_250M_CKDIV;

	if (tp->ups_info.ctap_short_off)
		ups_flags |= UPS_FLAGS_CTAP_SHORT_DIS;

	switch (tp->ups_info.speed_duplex) {
	case NWAY_10M_HALF:
		ups_flags |= ups_flags_speed(1);
		break;
	case NWAY_10M_FULL:
		ups_flags |= ups_flags_speed(2);
		break;
	case NWAY_100M_HALF:
		ups_flags |= ups_flags_speed(3);
		break;
	case NWAY_100M_FULL:
		ups_flags |= ups_flags_speed(4);
		break;
	case NWAY_1000M_FULL:
		ups_flags |= ups_flags_speed(5);
		break;
	case FORCE_10M_HALF:
		ups_flags |= ups_flags_speed(6);
		break;
	case FORCE_10M_FULL:
		ups_flags |= ups_flags_speed(7);
		break;
	case FORCE_100M_HALF:
		ups_flags |= ups_flags_speed(8);
		break;
	case FORCE_100M_FULL:
		ups_flags |= ups_flags_speed(9);
		break;
	default:
		break;
	}

	ocp_write_dword(tp, MCU_TYPE_USB, USB_UPS_FLAGS, ups_flags);
}

static void r8156_ups_flags(struct r8152 *tp)
{
	u32 ups_flags = 0;

	if (tp->ups_info.green)
		ups_flags |= UPS_FLAGS_EN_GREEN;

	if (tp->ups_info.aldps)
		ups_flags |= UPS_FLAGS_EN_ALDPS;

	if (tp->ups_info.eee)
		ups_flags |= UPS_FLAGS_EN_EEE;

	if (tp->ups_info.flow_control)
		ups_flags |= UPS_FLAGS_EN_FLOW_CTR;

	if (tp->ups_info.eee_ckdiv)
		ups_flags |= UPS_FLAGS_EN_EEE_CKDIV;

	if (tp->ups_info._10m_ckdiv)
		ups_flags |= UPS_FLAGS_EN_10M_CKDIV;

	if (tp->ups_info.eee_plloff_100)
		ups_flags |= UPS_FLAGS_EEE_PLLOFF_100;

	if (tp->ups_info.eee_plloff_giga)
		ups_flags |= UPS_FLAGS_EEE_PLLOFF_GIGA;

	if (tp->ups_info._250m_ckdiv)
		ups_flags |= UPS_FLAGS_250M_CKDIV;

	switch (tp->ups_info.speed_duplex) {
	case FORCE_10M_HALF:
		ups_flags |= ups_flags_speed(0);
		break;
	case FORCE_10M_FULL:
		ups_flags |= ups_flags_speed(1);
		break;
	case FORCE_100M_HALF:
		ups_flags |= ups_flags_speed(2);
		break;
	case FORCE_100M_FULL:
		ups_flags |= ups_flags_speed(3);
		break;
	case NWAY_10M_HALF:
		ups_flags |= ups_flags_speed(4);
		break;
	case NWAY_10M_FULL:
		ups_flags |= ups_flags_speed(5);
		break;
	case NWAY_100M_HALF:
		ups_flags |= ups_flags_speed(6);
		break;
	case NWAY_100M_FULL:
		ups_flags |= ups_flags_speed(7);
		break;
	case NWAY_1000M_FULL:
		ups_flags |= ups_flags_speed(8);
		break;
	case NWAY_2500M_FULL:
		ups_flags |= ups_flags_speed(9);
		break;
	default:
		break;
	}

	switch (tp->ups_info.lite_mode) {
	case 1:
		ups_flags |= 0 << 5;
		break;
	case 2:
		ups_flags |= 2 << 5;
		break;
	case 0:
	default:
		ups_flags |= 1 << 5;
		break;
	}

	ocp_write_dword(tp, MCU_TYPE_USB, USB_UPS_FLAGS, ups_flags);
}

static void rtl_green_en(struct r8152 *tp, bool enable)
{
	u16 data;

	data = sram_read(tp, SRAM_GREEN_CFG);
	if (enable)
		data |= GREEN_ETH_EN;
	else
		data &= ~GREEN_ETH_EN;
	sram_write(tp, SRAM_GREEN_CFG, data);

	tp->ups_info.green = enable;
}

static void r8153b_green_en(struct r8152 *tp, bool enable)
{
	if (enable) {
		sram_write(tp, 0x8045, 0);	/* 10M abiq&ldvbias */
		sram_write(tp, 0x804d, 0x1222);	/* 100M short abiq&ldvbias */
		sram_write(tp, 0x805d, 0x0022);	/* 1000M short abiq&ldvbias */
	} else {
		sram_write(tp, 0x8045, 0x2444);	/* 10M abiq&ldvbias */
		sram_write(tp, 0x804d, 0x2444);	/* 100M short abiq&ldvbias */
		sram_write(tp, 0x805d, 0x2444);	/* 1000M short abiq&ldvbias */
	}

	rtl_green_en(tp, true);
}

static u16 r8153_phy_status(struct r8152 *tp, u16 desired)
{
	u16 data;
	int i;

	for (i = 0; i < 500; i++) {
		data = ocp_reg_read(tp, OCP_PHY_STATUS);
		data &= PHY_STAT_MASK;
		if (desired) {
			if (data == desired)
				break;
		} else if (data == PHY_STAT_LAN_ON || data == PHY_STAT_PWRDN ||
			   data == PHY_STAT_EXT_INIT) {
			break;
		}

		msleep(20);
		if (test_bit(RTL8152_UNPLUG, &tp->flags))
			break;
	}

	return data;
}

static void r8153b_ups_en(struct r8152 *tp, bool enable)
{
	u32 ocp_data = ocp_read_byte(tp, MCU_TYPE_USB, USB_POWER_CUT);

	if (enable) {
		r8153b_ups_flags(tp);

		ocp_data |= UPS_EN | USP_PREWAKE | PHASE2_EN;
		ocp_write_byte(tp, MCU_TYPE_USB, USB_POWER_CUT, ocp_data);

		ocp_data = ocp_read_byte(tp, MCU_TYPE_USB, USB_MISC_2);
		ocp_data |= UPS_FORCE_PWR_DOWN;
		ocp_write_byte(tp, MCU_TYPE_USB, USB_MISC_2, ocp_data);
	} else {
		ocp_data &= ~(UPS_EN | USP_PREWAKE);
		ocp_write_byte(tp, MCU_TYPE_USB, USB_POWER_CUT, ocp_data);

		ocp_data = ocp_read_byte(tp, MCU_TYPE_USB, USB_MISC_2);
		ocp_data &= ~(UPS_FORCE_PWR_DOWN | UPS_NO_UPS);
		ocp_write_byte(tp, MCU_TYPE_USB, USB_MISC_2, ocp_data);

		if (ocp_read_word(tp, MCU_TYPE_USB, USB_MISC_0) & PCUT_STATUS) {
			int i;

			for (i = 0; i < 500; i++) {
				if (ocp_read_word(tp, MCU_TYPE_PLA, PLA_BOOT_CTRL) &
				    AUTOLOAD_DONE)
					break;
				msleep(20);
			}

			tp->rtl_ops.hw_phy_cfg(tp);

			rtl8152_set_speed(tp, tp->autoneg, tp->speed,
					  tp->duplex, tp->advertising);
		}
	}
}

static void r8153c_ups_en(struct r8152 *tp, bool enable)
{
	u32 ocp_data = ocp_read_byte(tp, MCU_TYPE_USB, USB_POWER_CUT);

	if (enable) {
		r8153b_ups_flags(tp);

		ocp_data |= UPS_EN | USP_PREWAKE | PHASE2_EN;
		ocp_write_byte(tp, MCU_TYPE_USB, USB_POWER_CUT, ocp_data);

		ocp_data = ocp_read_byte(tp, MCU_TYPE_USB, USB_MISC_2);
		ocp_data |= UPS_FORCE_PWR_DOWN;
		ocp_data &= ~BIT(7);
		ocp_write_byte(tp, MCU_TYPE_USB, USB_MISC_2, ocp_data);
	} else {
		ocp_data &= ~(UPS_EN | USP_PREWAKE);
		ocp_write_byte(tp, MCU_TYPE_USB, USB_POWER_CUT, ocp_data);

		ocp_data = ocp_read_byte(tp, MCU_TYPE_USB, USB_MISC_2);
		ocp_data &= ~(UPS_FORCE_PWR_DOWN | UPS_NO_UPS);
		ocp_write_byte(tp, MCU_TYPE_USB, USB_MISC_2, ocp_data);

		if (ocp_read_word(tp, MCU_TYPE_USB, USB_MISC_0) & PCUT_STATUS) {
			int i;

			for (i = 0; i < 500; i++) {
				if (ocp_read_word(tp, MCU_TYPE_PLA, PLA_BOOT_CTRL) &
				    AUTOLOAD_DONE)
					break;
				msleep(20);
			}

			tp->rtl_ops.hw_phy_cfg(tp);

			rtl8152_set_speed(tp, tp->autoneg, tp->speed,
					  tp->duplex, tp->advertising);
		}

		ocp_write_byte(tp, MCU_TYPE_PLA, PLA_CRWECR, CRWECR_CONFIG);

		ocp_data = ocp_read_word(tp, MCU_TYPE_PLA, PLA_CONFIG34);
		ocp_data |= BIT(8);
		ocp_write_word(tp, MCU_TYPE_PLA, PLA_CONFIG34, ocp_data);

		ocp_write_byte(tp, MCU_TYPE_PLA, PLA_CRWECR, CRWECR_NORAML);
	}
}

static void r8156_ups_en(struct r8152 *tp, bool enable)
{
	u32 ocp_data = ocp_read_byte(tp, MCU_TYPE_USB, USB_POWER_CUT);

	if (enable) {
		r8156_ups_flags(tp);

		ocp_data |= UPS_EN | USP_PREWAKE | PHASE2_EN;
		ocp_write_byte(tp, MCU_TYPE_USB, USB_POWER_CUT, ocp_data);

		ocp_data = ocp_read_byte(tp, MCU_TYPE_USB, USB_MISC_2);
		ocp_data |= UPS_FORCE_PWR_DOWN;
		ocp_write_byte(tp, MCU_TYPE_USB, USB_MISC_2, ocp_data);

		switch (tp->version) {
		case RTL_VER_13:
		case RTL_VER_15:
			ocp_data = ocp_read_word(tp, MCU_TYPE_USB, USB_UPHY_XTAL);
			ocp_data &= ~OOBS_POLLING;
			ocp_write_byte(tp, MCU_TYPE_USB, USB_UPHY_XTAL, ocp_data);
			break;
		default:
			break;
		}
	} else {
		ocp_data &= ~(UPS_EN | USP_PREWAKE);
		ocp_write_byte(tp, MCU_TYPE_USB, USB_POWER_CUT, ocp_data);

		ocp_data = ocp_read_byte(tp, MCU_TYPE_USB, USB_MISC_2);
		ocp_data &= ~(UPS_FORCE_PWR_DOWN | UPS_NO_UPS);
		ocp_write_byte(tp, MCU_TYPE_USB, USB_MISC_2, ocp_data);

		if (ocp_read_word(tp, MCU_TYPE_USB, USB_MISC_0) & PCUT_STATUS) {
			tp->rtl_ops.hw_phy_cfg(tp);

			rtl8152_set_speed(tp, tp->autoneg, tp->speed,
					  tp->duplex, tp->advertising);
		}
	}
}

static void r8153_power_cut_en(struct r8152 *tp, bool enable)
{
	u32 ocp_data;

	ocp_data = ocp_read_word(tp, MCU_TYPE_USB, USB_POWER_CUT);
	if (enable)
		ocp_data |= PWR_EN | PHASE2_EN;
	else
		ocp_data &= ~(PWR_EN | PHASE2_EN);
	ocp_write_word(tp, MCU_TYPE_USB, USB_POWER_CUT, ocp_data);

	ocp_data = ocp_read_word(tp, MCU_TYPE_USB, USB_MISC_0);
	ocp_data &= ~PCUT_STATUS;
	ocp_write_word(tp, MCU_TYPE_USB, USB_MISC_0, ocp_data);
}

static void r8153b_power_cut_en(struct r8152 *tp, bool enable)
{
	u32 ocp_data;

	ocp_data = ocp_read_word(tp, MCU_TYPE_USB, USB_POWER_CUT);
	if (enable)
		ocp_data |= PWR_EN | PHASE2_EN;
	else
		ocp_data &= ~PWR_EN;
	ocp_write_word(tp, MCU_TYPE_USB, USB_POWER_CUT, ocp_data);

	ocp_data = ocp_read_word(tp, MCU_TYPE_USB, USB_MISC_0);
	ocp_data &= ~PCUT_STATUS;
	ocp_write_word(tp, MCU_TYPE_USB, USB_MISC_0, ocp_data);
}

static void r8153_queue_wake(struct r8152 *tp, bool enable)
{
	u32 ocp_data;

	ocp_data = ocp_read_byte(tp, MCU_TYPE_PLA, PLA_INDICATE_FALG);
	if (enable)
		ocp_data |= UPCOMING_RUNTIME_D3;
	else
		ocp_data &= ~UPCOMING_RUNTIME_D3;
	ocp_write_byte(tp, MCU_TYPE_PLA, PLA_INDICATE_FALG, ocp_data);

	ocp_data = ocp_read_byte(tp, MCU_TYPE_PLA, PLA_SUSPEND_FLAG);
	ocp_data &= ~LINK_CHG_EVENT;
	ocp_write_byte(tp, MCU_TYPE_PLA, PLA_SUSPEND_FLAG, ocp_data);

	ocp_data = ocp_read_word(tp, MCU_TYPE_PLA, PLA_EXTRA_STATUS);
	ocp_data &= ~LINK_CHANGE_FLAG;
	ocp_write_word(tp, MCU_TYPE_PLA, PLA_EXTRA_STATUS, ocp_data);
}

static bool rtl_can_wakeup(struct r8152 *tp)
{
	struct usb_device *udev = tp->udev;

	return (udev->actconfig->desc.bmAttributes & USB_CONFIG_ATT_WAKEUP);
}

static void rtl_runtime_suspend_enable(struct r8152 *tp, bool enable)
{
	if (enable) {
		u32 ocp_data;

		__rtl_set_wol(tp, WAKE_ANY);

		ocp_write_byte(tp, MCU_TYPE_PLA, PLA_CRWECR, CRWECR_CONFIG);

		ocp_data = ocp_read_word(tp, MCU_TYPE_PLA, PLA_CONFIG34);
		ocp_data |= LINK_OFF_WAKE_EN;
		ocp_write_word(tp, MCU_TYPE_PLA, PLA_CONFIG34, ocp_data);

		ocp_write_byte(tp, MCU_TYPE_PLA, PLA_CRWECR, CRWECR_NORAML);
	} else {
		u32 ocp_data;

		__rtl_set_wol(tp, tp->saved_wolopts);

		ocp_write_byte(tp, MCU_TYPE_PLA, PLA_CRWECR, CRWECR_CONFIG);

		ocp_data = ocp_read_word(tp, MCU_TYPE_PLA, PLA_CONFIG34);
		ocp_data &= ~LINK_OFF_WAKE_EN;
		ocp_write_word(tp, MCU_TYPE_PLA, PLA_CONFIG34, ocp_data);

		ocp_write_byte(tp, MCU_TYPE_PLA, PLA_CRWECR, CRWECR_NORAML);
	}
}

static void rtl8153_runtime_enable(struct r8152 *tp, bool enable)
{
	if (enable) {
		if (tp->version == RTL_VER_06)
			r8153_queue_wake(tp, true);
		r8153_u1u2en(tp, false);
		r8153_u2p3en(tp, false);
		rtl_runtime_suspend_enable(tp, true);
	} else {
		if (tp->version == RTL_VER_06)
			r8153_queue_wake(tp, false);
		rtl_runtime_suspend_enable(tp, false);

		switch (tp->version) {
		case RTL_VER_03:
		case RTL_VER_04:
			break;
		case RTL_VER_05:
		case RTL_VER_06:
		default:
			r8153_u2p3en(tp, true);
			break;
		}

		r8153_u1u2en(tp, true);
	}
}

static void rtl8153b_runtime_enable(struct r8152 *tp, bool enable)
{
	if (enable) {
		r8153_queue_wake(tp, true);
		r8153b_u1u2en(tp, false);
		r8153_u2p3en(tp, false);
		rtl_runtime_suspend_enable(tp, true);
		r8153b_ups_en(tp, true);
	} else {
		r8153b_ups_en(tp, false);
		r8153_queue_wake(tp, false);
		rtl_runtime_suspend_enable(tp, false);
//		r8153_u2p3en(tp, true);
		if (tp->udev->speed >= USB_SPEED_SUPER)
			r8153b_u1u2en(tp, true);
	}
}

static void rtl8153c_runtime_enable(struct r8152 *tp, bool enable)
{
	if (enable) {
		r8153_queue_wake(tp, true);
		r8153b_u1u2en(tp, false);
		r8153_u2p3en(tp, false);
		rtl_runtime_suspend_enable(tp, true);
		r8153c_ups_en(tp, true);
	} else {
		r8153c_ups_en(tp, false);
		r8153_queue_wake(tp, false);
		rtl_runtime_suspend_enable(tp, false);
//		r8153_u2p3en(tp, true);
		r8153b_u1u2en(tp, true);
	}
}

static void rtl8156_runtime_enable(struct r8152 *tp, bool enable)
{
	if (enable) {
		r8153_queue_wake(tp, true);
		r8153b_u1u2en(tp, false);
		r8153_u2p3en(tp, false);
		rtl_runtime_suspend_enable(tp, true);
//		if (tp->version != RTL_VER_10 ||
//		    tp->udev->speed == USB_SPEED_HIGH)
//			r8156_ups_en(tp, true);
	} else {
//		r8156_ups_en(tp, false);
		r8153_queue_wake(tp, false);
		rtl_runtime_suspend_enable(tp, false);
		r8153_u2p3en(tp, true);
		if (tp->udev->speed >= USB_SPEED_SUPER)
			r8153b_u1u2en(tp, true);
	}
}

static int rtl_nway_restart(struct r8152 *tp)
{
	int r = -EINVAL;
	int bmcr;

	/* if autoneg is off, it's an error */
	bmcr = r8152_mdio_read(tp, MII_BMCR);

	if (bmcr & BMCR_ANENABLE) {
		bmcr |= BMCR_ANRESTART;
		r8152_mdio_write(tp, MII_BMCR, bmcr);
		r = 0;
	}

	return r;
}

static void r8153_teredo_off(struct r8152 *tp)
{
	u32 ocp_data;

	switch (tp->version) {
	case RTL_VER_01:
	case RTL_VER_02:
	case RTL_VER_03:
	case RTL_VER_04:
	case RTL_VER_05:
	case RTL_VER_06:
	case RTL_VER_07:
		ocp_data = ocp_read_word(tp, MCU_TYPE_PLA, PLA_TEREDO_CFG);
		ocp_data &= ~(TEREDO_SEL | TEREDO_RS_EVENT_MASK |
			      OOB_TEREDO_EN);
		ocp_write_word(tp, MCU_TYPE_PLA, PLA_TEREDO_CFG, ocp_data);
		break;

	case RTL_VER_08:
	case RTL_VER_09:
	case RTL_TEST_01:
	case RTL_VER_10:
	case RTL_VER_11:
	case RTL_VER_12:
	case RTL_VER_13:
	case RTL_VER_14:
	case RTL_VER_15:
	default:
		/* The bit 0 ~ 7 are relative with teredo settings. They are
		 * W1C (write 1 to clear), so set all 1 to disable it.
		 */
		ocp_write_byte(tp, MCU_TYPE_PLA, PLA_TEREDO_CFG, 0xff);
		break;
	}

	ocp_write_word(tp, MCU_TYPE_PLA, PLA_WDT6_CTRL, WDT6_SET_MODE);
	ocp_write_word(tp, MCU_TYPE_PLA, PLA_REALWOW_TIMER, 0);
	ocp_write_dword(tp, MCU_TYPE_PLA, PLA_TEREDO_TIMER, 0);
}

static void rtl_reset_bmu(struct r8152 *tp)
{
	u32 ocp_data;

	ocp_data = ocp_read_byte(tp, MCU_TYPE_USB, USB_BMU_RESET);
	ocp_data &= ~(BMU_RESET_EP_IN | BMU_RESET_EP_OUT);
	ocp_write_byte(tp, MCU_TYPE_USB, USB_BMU_RESET, ocp_data);
	ocp_data |= BMU_RESET_EP_IN | BMU_RESET_EP_OUT;
	ocp_write_byte(tp, MCU_TYPE_USB, USB_BMU_RESET, ocp_data);
}

/* Clear the bp to stop the firmware before loading a new one */
static void rtl_clear_bp(struct r8152 *tp, u16 type)
{
	switch (tp->version) {
	case RTL_VER_01:
	case RTL_VER_02:
	case RTL_VER_07:
		break;
	case RTL_VER_03:
	case RTL_VER_04:
	case RTL_VER_05:
	case RTL_VER_06:
		ocp_write_byte(tp, type, PLA_BP_EN, 0);
		break;
	case RTL_VER_14:
		ocp_write_word(tp, type, USB_BP2_EN, 0);

		ocp_write_word(tp, type, USB_BP_8, 0);
		ocp_write_word(tp, type, USB_BP_9, 0);
		ocp_write_word(tp, type, USB_BP_10, 0);
		ocp_write_word(tp, type, USB_BP_11, 0);
		ocp_write_word(tp, type, USB_BP_12, 0);
		ocp_write_word(tp, type, USB_BP_13, 0);
		ocp_write_word(tp, type, USB_BP_14, 0);
		ocp_write_word(tp, type, USB_BP_15, 0);
		break;
	case RTL_VER_08:
	case RTL_VER_09:
	case RTL_VER_10:
	case RTL_VER_11:
	case RTL_VER_12:
	case RTL_VER_13:
	case RTL_VER_15:
	default:
		if (type == MCU_TYPE_USB) {
			ocp_write_word(tp, MCU_TYPE_USB, USB_BP2_EN, 0);

			ocp_write_word(tp, MCU_TYPE_USB, USB_BP_8, 0);
			ocp_write_word(tp, MCU_TYPE_USB, USB_BP_9, 0);
			ocp_write_word(tp, MCU_TYPE_USB, USB_BP_10, 0);
			ocp_write_word(tp, MCU_TYPE_USB, USB_BP_11, 0);
			ocp_write_word(tp, MCU_TYPE_USB, USB_BP_12, 0);
			ocp_write_word(tp, MCU_TYPE_USB, USB_BP_13, 0);
			ocp_write_word(tp, MCU_TYPE_USB, USB_BP_14, 0);
			ocp_write_word(tp, MCU_TYPE_USB, USB_BP_15, 0);
		} else {
			ocp_write_byte(tp, MCU_TYPE_PLA, PLA_BP_EN, 0);
		}
		break;
	}

	ocp_write_word(tp, type, PLA_BP_0, 0);
	ocp_write_word(tp, type, PLA_BP_1, 0);
	ocp_write_word(tp, type, PLA_BP_2, 0);
	ocp_write_word(tp, type, PLA_BP_3, 0);
	ocp_write_word(tp, type, PLA_BP_4, 0);
	ocp_write_word(tp, type, PLA_BP_5, 0);
	ocp_write_word(tp, type, PLA_BP_6, 0);
	ocp_write_word(tp, type, PLA_BP_7, 0);

	/* wait 3 ms to make sure the firmware is stopped */
	usleep_range(3000, 6000);
	ocp_write_word(tp, type, PLA_BP_BA, 0);
}

static inline void rtl_reset_ocp_base(struct r8152 *tp)
{
	tp->ocp_base = -1;
}

static int rtl_phy_patch_request(struct r8152 *tp, bool request, bool wait)
{
	u16 data, check;
	int i;

	data = ocp_reg_read(tp, OCP_PHY_PATCH_CMD);
	if (request) {
		data |= PATCH_REQUEST;
		check = 0;
	} else {
		data &= ~PATCH_REQUEST;
		check = PATCH_READY;
	}
	ocp_reg_write(tp, OCP_PHY_PATCH_CMD, data);

	for (i = 0; wait && i < 5000; i++) {
		u32 ocp_data;

		usleep_range(1000, 2000);
		ocp_data = ocp_reg_read(tp, OCP_PHY_PATCH_STAT);
		if ((ocp_data & PATCH_READY) ^ check)
			break;
	}

	if (request && wait &&
	    !(ocp_reg_read(tp, OCP_PHY_PATCH_STAT) & PATCH_READY)) {
		dev_err(&tp->intf->dev, "PHY patch request fail\n");
		rtl_phy_patch_request(tp, false, false);
		return -ETIME;
	} else {
		return 0;
	}
}

static void rtl_patch_key_set(struct r8152 *tp, u16 key_addr, u16 patch_key)
{
	if (patch_key && key_addr) {
		sram_write(tp, key_addr, patch_key);
		sram_write(tp, SRAM_PHY_LOCK, PHY_PATCH_LOCK);
	} else if (key_addr) {
		u16 data;

		sram_write(tp, 0x0000, 0x0000);

		data = ocp_reg_read(tp, OCP_PHY_LOCK);
		data &= ~PATCH_LOCK;
		ocp_reg_write(tp, OCP_PHY_LOCK, data);

		sram_write(tp, key_addr, 0x0000);
	} else {
		WARN_ON_ONCE(1);
	}
}

static int
rtl_pre_ram_code(struct r8152 *tp, u16 key_addr, u16 patch_key, bool wait)
{
	if (rtl_phy_patch_request(tp, true, wait))
		return -ETIME;

	rtl_patch_key_set(tp, key_addr, patch_key);

	return 0;
}

static int rtl_post_ram_code(struct r8152 *tp, u16 key_addr, bool wait)
{
	rtl_patch_key_set(tp, key_addr, 0);

	rtl_phy_patch_request(tp, false, wait);

	return 0;
}

static void patch4(struct r8152 *tp)
{
	u8 data;

	data = ocp_read_byte(tp, MCU_TYPE_USB, 0xd429);
	data |= 0x80;
	ocp_write_byte(tp, MCU_TYPE_USB, 0xd429, data);
	ocp_write_word(tp, MCU_TYPE_USB, 0xc0ce, 0x0210);
	data = ocp_read_byte(tp, MCU_TYPE_USB, 0xd429);
	data &= ~0x80;
	ocp_write_byte(tp, MCU_TYPE_USB, 0xd429, data);
}

static void r8152b_firmware(struct r8152 *tp)
{
	if (tp->version == RTL_VER_01) {
		int i;
		static u8 pla_patch_a[] = {
			0x08, 0xe0, 0x40, 0xe0,
			0x78, 0xe0, 0x85, 0xe0,
			0x5d, 0xe1, 0xa1, 0xe1,
			0xa3, 0xe1, 0xab, 0xe1,
			0x31, 0xc3, 0x60, 0x72,
			0xa0, 0x49, 0x10, 0xf0,
			0xa4, 0x49, 0x0e, 0xf0,
			0x2c, 0xc3, 0x62, 0x72,
			0x26, 0x70, 0x80, 0x49,
			0x05, 0xf0, 0x2f, 0x48,
			0x62, 0x9a, 0x24, 0x70,
			0x60, 0x98, 0x24, 0xc3,
			0x60, 0x99, 0x23, 0xc3,
			0x00, 0xbb, 0x2c, 0x75,
			0xdc, 0x21, 0xbc, 0x25,
			0x04, 0x13, 0x0a, 0xf0,
			0x03, 0x13, 0x08, 0xf0,
			0x02, 0x13, 0x06, 0xf0,
			0x01, 0x13, 0x04, 0xf0,
			0x08, 0x13, 0x02, 0xf0,
			0x03, 0xe0, 0xd4, 0x49,
			0x04, 0xf1, 0x14, 0xc2,
			0x12, 0xc3, 0x00, 0xbb,
			0x12, 0xc3, 0x60, 0x75,
			0xd0, 0x49, 0x05, 0xf1,
			0x50, 0x48, 0x60, 0x9d,
			0x09, 0xc6, 0x00, 0xbe,
			0xd0, 0x48, 0x60, 0x9d,
			0xf3, 0xe7, 0xc2, 0xc0,
			0x38, 0xd2, 0xc6, 0xd2,
			0x84, 0x17, 0xa2, 0x13,
			0x0c, 0x17, 0xbc, 0xc0,
			0xa2, 0xd1, 0x33, 0xc5,
			0xa0, 0x74, 0xc0, 0x49,
			0x1f, 0xf0, 0x30, 0xc5,
			0xa0, 0x73, 0x00, 0x13,
			0x04, 0xf1, 0xa2, 0x73,
			0x00, 0x13, 0x14, 0xf0,
			0x28, 0xc5, 0xa0, 0x74,
			0xc8, 0x49, 0x1b, 0xf1,
			0x26, 0xc5, 0xa0, 0x76,
			0xa2, 0x74, 0x01, 0x06,
			0x20, 0x37, 0xa0, 0x9e,
			0xa2, 0x9c, 0x1e, 0xc5,
			0xa2, 0x73, 0x23, 0x40,
			0x10, 0xf8, 0x04, 0xf3,
			0xa0, 0x73, 0x33, 0x40,
			0x0c, 0xf8, 0x15, 0xc5,
			0xa0, 0x74, 0x41, 0x48,
			0xa0, 0x9c, 0x14, 0xc5,
			0xa0, 0x76, 0x62, 0x48,
			0xe0, 0x48, 0xa0, 0x9e,
			0x10, 0xc6, 0x00, 0xbe,
			0x0a, 0xc5, 0xa0, 0x74,
			0x48, 0x48, 0xa0, 0x9c,
			0x0b, 0xc5, 0x20, 0x1e,
			0xa0, 0x9e, 0xe5, 0x48,
			0xa0, 0x9e, 0xf0, 0xe7,
			0xbc, 0xc0, 0xc8, 0xd2,
			0xcc, 0xd2, 0x28, 0xe4,
			0x22, 0x02, 0xf0, 0xc0,
			0x0b, 0xc0, 0x00, 0x71,
			0x0a, 0xc0, 0x00, 0x72,
			0xa0, 0x49, 0x04, 0xf0,
			0xa4, 0x49, 0x02, 0xf0,
			0x93, 0x48, 0x04, 0xc0,
			0x00, 0xb8, 0x00, 0xe4,
			0xc2, 0xc0, 0x8c, 0x09,
			0x14, 0xc2, 0x40, 0x73,
			0xba, 0x48, 0x40, 0x9b,
			0x11, 0xc2, 0x40, 0x73,
			0xb0, 0x49, 0x17, 0xf0,
			0xbf, 0x49, 0x03, 0xf1,
			0x09, 0xc5, 0x00, 0xbd,
			0xb1, 0x49, 0x11, 0xf0,
			0xb1, 0x48, 0x40, 0x9b,
			0x02, 0xc2, 0x00, 0xba,
			0x82, 0x18, 0x00, 0xa0,
			0x1e, 0xfc, 0xbc, 0xc0,
			0xf0, 0xc0, 0xde, 0xe8,
			0x00, 0x80, 0x00, 0x60,
			0x2c, 0x75, 0xd4, 0x49,
			0x12, 0xf1, 0x29, 0xe0,
			0xf8, 0xc2, 0x46, 0x71,
			0xf7, 0xc2, 0x40, 0x73,
			0xbe, 0x49, 0x03, 0xf1,
			0xf5, 0xc7, 0x02, 0xe0,
			0xf2, 0xc7, 0x4f, 0x30,
			0x26, 0x62, 0xa1, 0x49,
			0xf0, 0xf1, 0x22, 0x72,
			0xa0, 0x49, 0xed, 0xf1,
			0x25, 0x25, 0x18, 0x1f,
			0x97, 0x30, 0x91, 0x30,
			0x36, 0x9a, 0x2c, 0x75,
			0x32, 0xc3, 0x60, 0x73,
			0xb1, 0x49, 0x0d, 0xf1,
			0xdc, 0x21, 0xbc, 0x25,
			0x27, 0xc6, 0xc0, 0x77,
			0x04, 0x13, 0x18, 0xf0,
			0x03, 0x13, 0x19, 0xf0,
			0x02, 0x13, 0x1a, 0xf0,
			0x01, 0x13, 0x1b, 0xf0,
			0xd4, 0x49, 0x03, 0xf1,
			0x1c, 0xc5, 0x00, 0xbd,
			0xcd, 0xc6, 0xc6, 0x67,
			0x2e, 0x75, 0xd7, 0x22,
			0xdd, 0x26, 0x05, 0x15,
			0x1a, 0xf0, 0x14, 0xc6,
			0x00, 0xbe, 0x13, 0xc5,
			0x00, 0xbd, 0x12, 0xc5,
			0x00, 0xbd, 0xf1, 0x49,
			0xfb, 0xf1, 0xef, 0xe7,
			0xf4, 0x49, 0xfa, 0xf1,
			0xec, 0xe7, 0xf3, 0x49,
			0xf7, 0xf1, 0xe9, 0xe7,
			0xf2, 0x49, 0xf4, 0xf1,
			0xe6, 0xe7, 0xb6, 0xc0,
			0x6a, 0x14, 0xac, 0x13,
			0xd6, 0x13, 0xfa, 0x14,
			0xa0, 0xd1, 0x00, 0x00,
			0xc0, 0x75, 0xd0, 0x49,
			0x46, 0xf0, 0x26, 0x72,
			0xa7, 0x49, 0x43, 0xf0,
			0x22, 0x72, 0x25, 0x25,
			0x20, 0x1f, 0x97, 0x30,
			0x91, 0x30, 0x40, 0x73,
			0xf3, 0xc4, 0x1c, 0x40,
			0x04, 0xf0, 0xd7, 0x49,
			0x05, 0xf1, 0x37, 0xe0,
			0x53, 0x48, 0xc0, 0x9d,
			0x08, 0x02, 0x40, 0x66,
			0x64, 0x27, 0x06, 0x16,
			0x30, 0xf1, 0x46, 0x63,
			0x3b, 0x13, 0x2d, 0xf1,
			0x34, 0x9b, 0x18, 0x1b,
			0x93, 0x30, 0x2b, 0xc3,
			0x10, 0x1c, 0x2b, 0xe8,
			0x01, 0x14, 0x25, 0xf1,
			0x00, 0x1d, 0x26, 0x1a,
			0x8a, 0x30, 0x22, 0x73,
			0xb5, 0x25, 0x0e, 0x0b,
			0x00, 0x1c, 0x2c, 0xe8,
			0x1f, 0xc7, 0x27, 0x40,
			0x1a, 0xf1, 0x38, 0xe8,
			0x32, 0x1f, 0x8f, 0x30,
			0x08, 0x1b, 0x24, 0xe8,
			0x36, 0x72, 0x46, 0x77,
			0x00, 0x17, 0x0d, 0xf0,
			0x13, 0xc3, 0x1f, 0x40,
			0x03, 0xf1, 0x00, 0x1f,
			0x46, 0x9f, 0x44, 0x77,
			0x9f, 0x44, 0x5f, 0x44,
			0x17, 0xe8, 0x0a, 0xc7,
			0x27, 0x40, 0x05, 0xf1,
			0x02, 0xc3, 0x00, 0xbb,
			0x50, 0x1a, 0x06, 0x1a,
			0xff, 0xc7, 0x00, 0xbf,
			0xb8, 0xcd, 0xff, 0xff,
			0x02, 0x0c, 0x54, 0xa5,
			0xdc, 0xa5, 0x2f, 0x40,
			0x05, 0xf1, 0x00, 0x14,
			0xfa, 0xf1, 0x01, 0x1c,
			0x02, 0xe0, 0x00, 0x1c,
			0x80, 0xff, 0xb0, 0x49,
			0x04, 0xf0, 0x01, 0x0b,
			0xd3, 0xa1, 0x03, 0xe0,
			0x02, 0x0b, 0xd3, 0xa5,
			0x27, 0x31, 0x20, 0x37,
			0x02, 0x0b, 0xd3, 0xa5,
			0x27, 0x31, 0x20, 0x37,
			0x00, 0x13, 0xfb, 0xf1,
			0x80, 0xff, 0x22, 0x73,
			0xb5, 0x25, 0x18, 0x1e,
			0xde, 0x30, 0xd9, 0x30,
			0x64, 0x72, 0x11, 0x1e,
			0x68, 0x23, 0x16, 0x31,
			0x80, 0xff, 0xd4, 0x49,
			0x28, 0xf0, 0x02, 0xb4,
			0x2a, 0xc4, 0x00, 0x1d,
			0x2e, 0xe8, 0xe0, 0x73,
			0xb9, 0x21, 0xbd, 0x25,
			0x04, 0x13, 0x02, 0xf0,
			0x1a, 0xe0, 0x22, 0xc4,
			0x23, 0xc3, 0x2f, 0xe8,
			0x23, 0xc3, 0x2d, 0xe8,
			0x00, 0x1d, 0x21, 0xe8,
			0xe2, 0x73, 0xbb, 0x49,
			0xfc, 0xf0, 0xe0, 0x73,
			0xb7, 0x48, 0x03, 0xb4,
			0x81, 0x1d, 0x19, 0xe8,
			0x40, 0x1a, 0x84, 0x1d,
			0x16, 0xe8, 0x12, 0xc3,
			0x1e, 0xe8, 0x03, 0xb0,
			0x81, 0x1d, 0x11, 0xe8,
			0x0e, 0xc3, 0x19, 0xe8,
			0x02, 0xb0, 0x06, 0xc7,
			0x04, 0x1e, 0xe0, 0x9e,
			0x02, 0xc6, 0x00, 0xbe,
			0x22, 0x02, 0x20, 0xe4,
			0x04, 0xb8, 0x34, 0xb0,
			0x00, 0x02, 0x00, 0x03,
			0x00, 0x0e, 0x00, 0x0c,
			0x09, 0xc7, 0xe0, 0x9b,
			0xe2, 0x9a, 0xe4, 0x9c,
			0xe6, 0x8d, 0xe6, 0x76,
			0xef, 0x49, 0xfe, 0xf1,
			0x80, 0xff, 0x08, 0xea,
			0x82, 0x1d, 0xf5, 0xef,
			0x00, 0x1a, 0x88, 0x1d,
			0xf2, 0xef, 0xed, 0xc2,
			0xf0, 0xef, 0x80, 0xff,
			0x02, 0xc6, 0x00, 0xbe,
			0x46, 0x06, 0x08, 0xc2,
			0x40, 0x73, 0x3a, 0x48,
			0x40, 0x9b, 0x06, 0xff,
			0x02, 0xc6, 0x00, 0xbe,
			0x86, 0x17, 0x1e, 0xfc,
			0x36, 0xf0, 0x08, 0x1c,
			0xea, 0x8c, 0xe3, 0x64,
			0xc7, 0x49, 0x25, 0xf1,
			0xe0, 0x75, 0xff, 0x1b,
			0xeb, 0x47, 0xff, 0x1b,
			0x6b, 0x47, 0xe0, 0x9d,
			0x15, 0xc3, 0x60, 0x75,
			0xd8, 0x49, 0x04, 0xf0,
			0x81, 0x1d, 0xe2, 0x8d,
			0x05, 0xe0, 0xe2, 0x63,
			0x81, 0x1d, 0xdd, 0x47,
			0xe2, 0x8b, 0x0b, 0xc3,
			0x00, 0x1d, 0x61, 0x8d,
			0x3c, 0x03, 0x60, 0x75,
			0xd8, 0x49, 0x06, 0xf1,
			0xdf, 0x48, 0x61, 0x95,
			0x16, 0xe0, 0x4e, 0xe8,
			0x12, 0xe8, 0x21, 0xc5,
			0xa0, 0x73, 0xb0, 0x49,
			0x03, 0xf0, 0x31, 0x48,
			0xa0, 0x9b, 0x0d, 0xe0,
			0xc0, 0x49, 0x0b, 0xf1,
			0xe2, 0x63, 0x7e, 0x1d,
			0xdd, 0x46, 0xe2, 0x8b,
			0xe0, 0x75, 0x83, 0x1b,
			0xeb, 0x46, 0xfe, 0x1b,
			0x6b, 0x46, 0xe0, 0x9d,
			0xe4, 0x49, 0x11, 0xf0,
			0x10, 0x1d, 0xea, 0x8d,
			0xe3, 0x64, 0xc6, 0x49,
			0x09, 0xf1, 0x07, 0xc5,
			0xa0, 0x73, 0xb1, 0x48,
			0xa0, 0x9b, 0x02, 0xc5,
			0x00, 0xbd, 0xe6, 0x04,
			0xa0, 0xd1, 0x02, 0xc5,
			0x00, 0xbd, 0xfe, 0x04,
			0x02, 0xc5, 0x00, 0xbd,
			0x30, 0x05, 0x00, 0x00 };
		static u16 ram_code1[] = {
			0x9700, 0x7fe0, 0x4c00, 0x4007,
			0x4400, 0x4800, 0x7c1f, 0x4c00,
			0x5310, 0x6000, 0x7c07, 0x6800,
			0x673e, 0x0000, 0x0000, 0x571f,
			0x5ffb, 0xaa05, 0x5b58, 0x7d80,
			0x6100, 0x3019, 0x5b64, 0x7d80,
			0x6080, 0xa6f8, 0xdcdb, 0x0015,
			0xb915, 0xb511, 0xd16b, 0x000f,
			0xb40f, 0xd06b, 0x000d, 0xb206,
			0x7c01, 0x5800, 0x7c04, 0x5c00,
			0x3011, 0x7c01, 0x5801, 0x7c04,
			0x5c04, 0x3019, 0x30a5, 0x3127,
			0x31d5, 0x7fe0, 0x4c60, 0x7c07,
			0x6803, 0x7d00, 0x6900, 0x65a0,
			0x0000, 0x0000, 0xaf03, 0x6015,
			0x303e, 0x6017, 0x57e0, 0x580c,
			0x588c, 0x7fdd, 0x5fa2, 0x4827,
			0x7c1f, 0x4c00, 0x7c1f, 0x4c10,
			0x8400, 0x7c30, 0x6020, 0x48bf,
			0x7c1f, 0x4c00, 0x7c1f, 0x4c01,
			0x7c07, 0x6803, 0xb806, 0x7c08,
			0x6800, 0x0000, 0x0000, 0x305c,
			0x7c08, 0x6808, 0x0000, 0x0000,
			0xae06, 0x7c02, 0x5c02, 0x0000,
			0x0000, 0x3067, 0x8e05, 0x7c02,
			0x5c00, 0x0000, 0x0000, 0xad06,
			0x7c20, 0x5c20, 0x0000, 0x0000,
			0x3072, 0x8d05, 0x7c20, 0x5c00,
			0x0000, 0x0000, 0xa008, 0x7c07,
			0x6800, 0xb8db, 0x7c07, 0x6803,
			0xd9b3, 0x00d7, 0x7fe0, 0x4c80,
			0x7c08, 0x6800, 0x0000, 0x0000,
			0x7c23, 0x5c23, 0x481d, 0x7c1f,
			0x4c00, 0x7c1f, 0x4c02, 0x5310,
			0x81ff, 0x30f5, 0x7fe0, 0x4d00,
			0x4832, 0x7c1f, 0x4c00, 0x7c1f,
			0x4c10, 0x7c08, 0x6000, 0xa49e,
			0x7c07, 0x6800, 0xb89b, 0x7c07,
			0x6803, 0xd9b3, 0x00f9, 0x7fe0,
			0x4d20, 0x7e00, 0x6200, 0x3001,
			0x7fe0, 0x4dc0, 0xd09d, 0x0002,
			0xb4fe, 0x7fe0, 0x4d80, 0x7c04,
			0x6004, 0x7c07, 0x6802, 0x6728,
			0x0000, 0x0000, 0x7c08, 0x6000,
			0x486c, 0x7c1f, 0x4c00, 0x7c1f,
			0x4c01, 0x9503, 0x7e00, 0x6200,
			0x571f, 0x5fbb, 0xaa05, 0x5b58,
			0x7d80, 0x6100, 0x30c2, 0x5b64,
			0x7d80, 0x6080, 0xcdab, 0x0063,
			0xcd8d, 0x0061, 0xd96b, 0x005f,
			0xd0a0, 0x00d7, 0xcba0, 0x0003,
			0x80ec, 0x30cf, 0x30dc, 0x7fe0,
			0x4ce0, 0x4832, 0x7c1f, 0x4c00,
			0x7c1f, 0x4c08, 0x7c08, 0x6008,
			0x8300, 0xb902, 0x30a5, 0x308a,
			0x7fe0, 0x4da0, 0x65a8, 0x0000,
			0x0000, 0x56a0, 0x590c, 0x7ffd,
			0x5fa2, 0xae06, 0x7c02, 0x5c02,
			0x0000, 0x0000, 0x30f0, 0x8e05,
			0x7c02, 0x5c00, 0x0000, 0x0000,
			0xcba4, 0x0004, 0xcd8d, 0x0002,
			0x80f1, 0x7fe0, 0x4ca0, 0x7c08,
			0x6408, 0x0000, 0x0000, 0x7d00,
			0x6800, 0xb603, 0x7c10, 0x6010,
			0x7d1f, 0x551f, 0x5fb3, 0xaa07,
			0x7c80, 0x5800, 0x5b58, 0x7d80,
			0x6100, 0x310f, 0x7c80, 0x5800,
			0x5b64, 0x7d80, 0x6080, 0x4827,
			0x7c1f, 0x4c00, 0x7c1f, 0x4c10,
			0x8400, 0x7c10, 0x6000, 0x7fe0,
			0x4cc0, 0x5fbb, 0x4824, 0x7c1f,
			0x4c00, 0x7c1f, 0x4c04, 0x8200,
			0x7ce0, 0x5400, 0x6728, 0x0000,
			0x0000, 0x30cf, 0x3001, 0x7fe0,
			0x4e00, 0x4007, 0x4400, 0x5310,
			0x7c07, 0x6800, 0x673e, 0x0000,
			0x0000, 0x570f, 0x5fff, 0xaa05,
			0x585b, 0x7d80, 0x6100, 0x313b,
			0x5867, 0x7d80, 0x6080, 0x9403,
			0x7e00, 0x6200, 0xcda3, 0x00e7,
			0xcd85, 0x00e5, 0xd96b, 0x00e3,
			0x96e3, 0x7c07, 0x6800, 0x673e,
			0x0000, 0x0000, 0x7fe0, 0x4e20,
			0x96db, 0x8b04, 0x7c08, 0x5008,
			0xab03, 0x7c08, 0x5000, 0x7c07,
			0x6801, 0x677e, 0x0000, 0x0000,
			0xdb7c, 0x00ec, 0x0000, 0x7fe1,
			0x4f40, 0x4837, 0x4418, 0x41c7,
			0x7fe0, 0x4e40, 0x7c40, 0x5400,
			0x7c1f, 0x4c01, 0x7c1f, 0x4c01,
			0x8fbf, 0xd2a0, 0x004b, 0x9204,
			0xa042, 0x3168, 0x3127, 0x7fe1,
			0x4f60, 0x489c, 0x4628, 0x7fe0,
			0x4e60, 0x7e28, 0x4628, 0x7c40,
			0x5400, 0x7c01, 0x5800, 0x7c04,
			0x5c00, 0x41e8, 0x7c1f, 0x4c01,
			0x7c1f, 0x4c01, 0x8fa5, 0xb241,
			0xa02a, 0x3182, 0x7fe0, 0x4ea0,
			0x7c02, 0x4402, 0x4448, 0x4894,
			0x7c1f, 0x4c01, 0x7c1f, 0x4c03,
			0x4824, 0x7c1f, 0x4c07, 0x41ef,
			0x41ff, 0x4891, 0x7c1f, 0x4c07,
			0x7c1f, 0x4c17, 0x8400, 0x8ef8,
			0x41c7, 0x8f8a, 0x92d5, 0xa10f,
			0xd480, 0x0008, 0xd580, 0x00b8,
			0xa202, 0x319d, 0x7c04, 0x4404,
			0x319d, 0xd484, 0x00f3, 0xd484,
			0x00f1, 0x3127, 0x7fe0, 0x4ee0,
			0x7c40, 0x5400, 0x4488, 0x41cf,
			0x3127, 0x7fe0, 0x4ec0, 0x48f3,
			0x7c1f, 0x4c01, 0x7c1f, 0x4c09,
			0x4508, 0x41c7, 0x8fb0, 0xd218,
			0x00ae, 0xd2a4, 0x009e, 0x31be,
			0x7fe0, 0x4e80, 0x4832, 0x7c1f,
			0x4c01, 0x7c1f, 0x4c11, 0x4428,
			0x7c40, 0x5440, 0x7c01, 0x5801,
			0x7c04, 0x5c04, 0x41e8, 0xa4b3,
			0x31d3, 0x7fe0, 0x4f20, 0x7c07,
			0x6800, 0x673e, 0x0000, 0x0000,
			0x570f, 0x5fff, 0xaa04, 0x585b,
			0x6100, 0x31e4, 0x5867, 0x6080,
			0xbcf1, 0x3001 };

		patch4(tp);
		rtl_clear_bp(tp, MCU_TYPE_PLA);

		generic_ocp_write(tp, 0xf800, 0x3f, sizeof(pla_patch_a),
				  pla_patch_a, MCU_TYPE_PLA);

		ocp_write_word(tp, MCU_TYPE_PLA, 0xfc26, 0x8000);

		ocp_write_word(tp, MCU_TYPE_PLA, 0xfc28, 0x170b);
		ocp_write_word(tp, MCU_TYPE_PLA, 0xfc2a, 0x01e1);
		ocp_write_word(tp, MCU_TYPE_PLA, 0xfc2c, 0x0989);
		ocp_write_word(tp, MCU_TYPE_PLA, 0xfc2e, 0x1349);
		ocp_write_word(tp, MCU_TYPE_PLA, 0xfc30, 0x01b7);
		ocp_write_word(tp, MCU_TYPE_PLA, 0xfc32, 0x061d);

		ocp_write_word(tp, MCU_TYPE_PLA, 0xe422, 0x0020);
		ocp_write_word(tp, MCU_TYPE_PLA, 0xe420, 0x0018);
		ocp_write_word(tp, MCU_TYPE_PLA, 0xfc34, 0x1785);
		ocp_write_word(tp, MCU_TYPE_PLA, 0xfc36, 0x047b);

		ocp_write_word(tp, MCU_TYPE_PLA, PLA_OCP_GPHY_BASE, 0x2000);
		ocp_write_word(tp, MCU_TYPE_PLA, 0xb092, 0x7070);
		ocp_write_word(tp, MCU_TYPE_PLA, 0xb098, 0x0600);
		for (i = 0; i < ARRAY_SIZE(ram_code1); i++)
			ocp_write_word(tp, MCU_TYPE_PLA, 0xb09a, ram_code1[i]);
		ocp_write_word(tp, MCU_TYPE_PLA, 0xb098, 0x0200);
		ocp_write_word(tp, MCU_TYPE_PLA, 0xb092, 0x7030);

		rtl_reset_ocp_base(tp);
	} else if (tp->version == RTL_VER_02) {
		static u8 pla_patch_a2[] = {
			0x08, 0xe0, 0x1a, 0xe0,
			0xf2, 0xe0, 0xfa, 0xe0,
			0x32, 0xe1, 0x34, 0xe1,
			0x36, 0xe1, 0x38, 0xe1,
			0x2c, 0x75, 0xdc, 0x21,
			0xbc, 0x25, 0x04, 0x13,
			0x0b, 0xf0, 0x03, 0x13,
			0x09, 0xf0, 0x02, 0x13,
			0x07, 0xf0, 0x01, 0x13,
			0x05, 0xf0, 0x08, 0x13,
			0x03, 0xf0, 0x04, 0xc3,
			0x00, 0xbb, 0x03, 0xc3,
			0x00, 0xbb, 0xd2, 0x17,
			0xbc, 0x17, 0x14, 0xc2,
			0x40, 0x73, 0xba, 0x48,
			0x40, 0x9b, 0x11, 0xc2,
			0x40, 0x73, 0xb0, 0x49,
			0x17, 0xf0, 0xbf, 0x49,
			0x03, 0xf1, 0x09, 0xc5,
			0x00, 0xbd, 0xb1, 0x49,
			0x11, 0xf0, 0xb1, 0x48,
			0x40, 0x9b, 0x02, 0xc2,
			0x00, 0xba, 0x4e, 0x19,
			0x00, 0xa0, 0x1e, 0xfc,
			0xbc, 0xc0, 0xf0, 0xc0,
			0xde, 0xe8, 0x00, 0x80,
			0x00, 0x60, 0x2c, 0x75,
			0xd4, 0x49, 0x12, 0xf1,
			0x29, 0xe0, 0xf8, 0xc2,
			0x46, 0x71, 0xf7, 0xc2,
			0x40, 0x73, 0xbe, 0x49,
			0x03, 0xf1, 0xf5, 0xc7,
			0x02, 0xe0, 0xf2, 0xc7,
			0x4f, 0x30, 0x26, 0x62,
			0xa1, 0x49, 0xf0, 0xf1,
			0x22, 0x72, 0xa0, 0x49,
			0xed, 0xf1, 0x25, 0x25,
			0x18, 0x1f, 0x97, 0x30,
			0x91, 0x30, 0x36, 0x9a,
			0x2c, 0x75, 0x32, 0xc3,
			0x60, 0x73, 0xb1, 0x49,
			0x0d, 0xf1, 0xdc, 0x21,
			0xbc, 0x25, 0x27, 0xc6,
			0xc0, 0x77, 0x04, 0x13,
			0x18, 0xf0, 0x03, 0x13,
			0x19, 0xf0, 0x02, 0x13,
			0x1a, 0xf0, 0x01, 0x13,
			0x1b, 0xf0, 0xd4, 0x49,
			0x03, 0xf1, 0x1c, 0xc5,
			0x00, 0xbd, 0xcd, 0xc6,
			0xc6, 0x67, 0x2e, 0x75,
			0xd7, 0x22, 0xdd, 0x26,
			0x05, 0x15, 0x1a, 0xf0,
			0x14, 0xc6, 0x00, 0xbe,
			0x13, 0xc5, 0x00, 0xbd,
			0x12, 0xc5, 0x00, 0xbd,
			0xf1, 0x49, 0xfb, 0xf1,
			0xef, 0xe7, 0xf4, 0x49,
			0xfa, 0xf1, 0xec, 0xe7,
			0xf3, 0x49, 0xf7, 0xf1,
			0xe9, 0xe7, 0xf2, 0x49,
			0xf4, 0xf1, 0xe6, 0xe7,
			0xb6, 0xc0, 0xf6, 0x14,
			0x36, 0x14, 0x62, 0x14,
			0x86, 0x15, 0xa0, 0xd1,
			0x00, 0x00, 0xc0, 0x75,
			0xd0, 0x49, 0x46, 0xf0,
			0x26, 0x72, 0xa7, 0x49,
			0x43, 0xf0, 0x22, 0x72,
			0x25, 0x25, 0x20, 0x1f,
			0x97, 0x30, 0x91, 0x30,
			0x40, 0x73, 0xf3, 0xc4,
			0x1c, 0x40, 0x04, 0xf0,
			0xd7, 0x49, 0x05, 0xf1,
			0x37, 0xe0, 0x53, 0x48,
			0xc0, 0x9d, 0x08, 0x02,
			0x40, 0x66, 0x64, 0x27,
			0x06, 0x16, 0x30, 0xf1,
			0x46, 0x63, 0x3b, 0x13,
			0x2d, 0xf1, 0x34, 0x9b,
			0x18, 0x1b, 0x93, 0x30,
			0x2b, 0xc3, 0x10, 0x1c,
			0x2b, 0xe8, 0x01, 0x14,
			0x25, 0xf1, 0x00, 0x1d,
			0x26, 0x1a, 0x8a, 0x30,
			0x22, 0x73, 0xb5, 0x25,
			0x0e, 0x0b, 0x00, 0x1c,
			0x2c, 0xe8, 0x1f, 0xc7,
			0x27, 0x40, 0x1a, 0xf1,
			0x38, 0xe8, 0x32, 0x1f,
			0x8f, 0x30, 0x08, 0x1b,
			0x24, 0xe8, 0x36, 0x72,
			0x46, 0x77, 0x00, 0x17,
			0x0d, 0xf0, 0x13, 0xc3,
			0x1f, 0x40, 0x03, 0xf1,
			0x00, 0x1f, 0x46, 0x9f,
			0x44, 0x77, 0x9f, 0x44,
			0x5f, 0x44, 0x17, 0xe8,
			0x0a, 0xc7, 0x27, 0x40,
			0x05, 0xf1, 0x02, 0xc3,
			0x00, 0xbb, 0x1c, 0x1b,
			0xd2, 0x1a, 0xff, 0xc7,
			0x00, 0xbf, 0xb8, 0xcd,
			0xff, 0xff, 0x02, 0x0c,
			0x54, 0xa5, 0xdc, 0xa5,
			0x2f, 0x40, 0x05, 0xf1,
			0x00, 0x14, 0xfa, 0xf1,
			0x01, 0x1c, 0x02, 0xe0,
			0x00, 0x1c, 0x80, 0xff,
			0xb0, 0x49, 0x04, 0xf0,
			0x01, 0x0b, 0xd3, 0xa1,
			0x03, 0xe0, 0x02, 0x0b,
			0xd3, 0xa5, 0x27, 0x31,
			0x20, 0x37, 0x02, 0x0b,
			0xd3, 0xa5, 0x27, 0x31,
			0x20, 0x37, 0x00, 0x13,
			0xfb, 0xf1, 0x80, 0xff,
			0x22, 0x73, 0xb5, 0x25,
			0x18, 0x1e, 0xde, 0x30,
			0xd9, 0x30, 0x64, 0x72,
			0x11, 0x1e, 0x68, 0x23,
			0x16, 0x31, 0x80, 0xff,
			0x08, 0xc2, 0x40, 0x73,
			0x3a, 0x48, 0x40, 0x9b,
			0x06, 0xff, 0x02, 0xc6,
			0x00, 0xbe, 0x4e, 0x18,
			0x1e, 0xfc, 0x33, 0xc5,
			0xa0, 0x74, 0xc0, 0x49,
			0x1f, 0xf0, 0x30, 0xc5,
			0xa0, 0x73, 0x00, 0x13,
			0x04, 0xf1, 0xa2, 0x73,
			0x00, 0x13, 0x14, 0xf0,
			0x28, 0xc5, 0xa0, 0x74,
			0xc8, 0x49, 0x1b, 0xf1,
			0x26, 0xc5, 0xa0, 0x76,
			0xa2, 0x74, 0x01, 0x06,
			0x20, 0x37, 0xa0, 0x9e,
			0xa2, 0x9c, 0x1e, 0xc5,
			0xa2, 0x73, 0x23, 0x40,
			0x10, 0xf8, 0x04, 0xf3,
			0xa0, 0x73, 0x33, 0x40,
			0x0c, 0xf8, 0x15, 0xc5,
			0xa0, 0x74, 0x41, 0x48,
			0xa0, 0x9c, 0x14, 0xc5,
			0xa0, 0x76, 0x62, 0x48,
			0xe0, 0x48, 0xa0, 0x9e,
			0x10, 0xc6, 0x00, 0xbe,
			0x0a, 0xc5, 0xa0, 0x74,
			0x48, 0x48, 0xa0, 0x9c,
			0x0b, 0xc5, 0x20, 0x1e,
			0xa0, 0x9e, 0xe5, 0x48,
			0xa0, 0x9e, 0xf0, 0xe7,
			0xbc, 0xc0, 0xc8, 0xd2,
			0xcc, 0xd2, 0x28, 0xe4,
			0x22, 0x02, 0xf0, 0xc0,
			0x02, 0xc6, 0x00, 0xbe,
			0x00, 0x00, 0x02, 0xc6,
			0x00, 0xbe, 0x00, 0x00,
			0x02, 0xc6, 0x00, 0xbe,
			0x00, 0x00, 0x02, 0xc6,
			0x00, 0xbe, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00 };
		static u8 usb_patch_a2[] = {
			0x10, 0xe0, 0x2d, 0xe0,
			0x0e, 0xe0, 0x0d, 0xe0,
			0x0c, 0xe0, 0x0b, 0xe0,
			0x0a, 0xe0, 0x09, 0xe0,
			0x08, 0xe0, 0x07, 0xe0,
			0x06, 0xe0, 0x05, 0xe0,
			0x04, 0xe0, 0x03, 0xe0,
			0x02, 0xe0, 0x01, 0xe0,
			0x1c, 0xc2, 0x40, 0x71,
			0x9f, 0x48, 0x40, 0x99,
			0x1f, 0x48, 0x40, 0x99,
			0x15, 0xc2, 0x40, 0x61,
			0x90, 0x49, 0x0a, 0xf0,
			0x42, 0x70, 0x80, 0x49,
			0x07, 0xf0, 0x80, 0x48,
			0x42, 0x98, 0x0b, 0xc2,
			0x40, 0x60, 0x03, 0x48,
			0x40, 0x88, 0x0a, 0xc2,
			0x08, 0x18, 0x55, 0x60,
			0x55, 0x88, 0x02, 0xc0,
			0x00, 0xb8, 0xc2, 0x09,
			0x28, 0xd4, 0xd4, 0xc4,
			0x06, 0xd4, 0x00, 0xb0,
			0x61, 0xc7, 0x5a, 0xc6,
			0xe4, 0x9e, 0x0f, 0x1e,
			0xe6, 0x8e, 0xe6, 0x76,
			0xef, 0x49, 0xfe, 0xf1,
			0xe0, 0x73, 0xe2, 0x74,
			0xb8, 0x26, 0xb8, 0x21,
			0xb8, 0x25, 0x48, 0x23,
			0x68, 0x27, 0x04, 0xb4,
			0x05, 0xb4, 0x06, 0xb4,
			0x4a, 0xc6, 0xe3, 0x23,
			0xfe, 0x39, 0x00, 0x1c,
			0x00, 0x1d, 0x00, 0x13,
			0x0a, 0xf0, 0xb0, 0x49,
			0x04, 0xf1, 0x01, 0x05,
			0xb1, 0x25, 0xfa, 0xe7,
			0xb8, 0x33, 0x35, 0x43,
			0x30, 0x31, 0xf6, 0xe7,
			0x06, 0xb0, 0x05, 0xb0,
			0xae, 0x41, 0x25, 0x31,
			0x37, 0xc5, 0x6c, 0x41,
			0x04, 0xb0, 0x48, 0x26,
			0x05, 0xb4, 0x36, 0xc7,
			0x2f, 0xc6, 0x04, 0x06,
			0xe4, 0x9e, 0x0f, 0x1e,
			0xe6, 0x8e, 0xe6, 0x76,
			0xef, 0x49, 0xfe, 0xf1,
			0xe0, 0x76, 0xe8, 0x25,
			0xe8, 0x23, 0xf8, 0x27,
			0x24, 0xc5, 0x6c, 0x41,
			0x33, 0x22, 0x23, 0x39,
			0x7c, 0x41, 0xfd, 0x31,
			0x1f, 0xc6, 0x7e, 0x41,
			0x20, 0xc6, 0xc4, 0x9f,
			0xf2, 0x21, 0xdf, 0x30,
			0xdf, 0x30, 0x05, 0xb0,
			0xc2, 0x9d, 0x53, 0x22,
			0x25, 0x31, 0xa3, 0x31,
			0x12, 0xc7, 0xb7, 0x31,
			0x12, 0xc7, 0x77, 0x41,
			0x12, 0xc7, 0xe6, 0x9e,
			0x0f, 0xc3, 0xde, 0x30,
			0x60, 0x64, 0xe8, 0x8c,
			0x06, 0xc7, 0x04, 0x1e,
			0xe0, 0x8e, 0x02, 0xc4,
			0x00, 0xbc, 0xb6, 0x02,
			0x34, 0xe4, 0x00, 0xc0,
			0x25, 0x00, 0xff, 0x00,
			0x7f, 0x00, 0x00, 0xf8,
			0xf0, 0xc4, 0x08, 0xdc };
		u32 ocp_data;

		rtl_clear_bp(tp, MCU_TYPE_PLA);

		generic_ocp_write(tp, 0xf800, 0xff, sizeof(pla_patch_a2),
				  pla_patch_a2, MCU_TYPE_PLA);

		ocp_write_word(tp, MCU_TYPE_PLA, 0xfc26, 0x8000);

		ocp_write_word(tp, MCU_TYPE_PLA, 0xfc28, 0x17a5);
		ocp_write_word(tp, MCU_TYPE_PLA, 0xfc2a, 0x13ad);
		ocp_write_word(tp, MCU_TYPE_PLA, 0xfc2c, 0x184d);
		ocp_write_word(tp, MCU_TYPE_PLA, 0xfc2e, 0x01e1);

		rtl_clear_bp(tp, MCU_TYPE_USB);

		generic_ocp_write(tp, 0xf800, 0xff, sizeof(usb_patch_a2),
				  usb_patch_a2, MCU_TYPE_USB);

		ocp_write_word(tp, MCU_TYPE_USB, 0xfc26, 0xA000);

		ocp_write_word(tp, MCU_TYPE_USB, 0xfc28, 0x0c87);
		ocp_write_word(tp, MCU_TYPE_USB, 0xfc2a, 0x024f);
		ocp_write_word(tp, MCU_TYPE_USB, 0xfc2c, 0x0000);
		ocp_write_word(tp, MCU_TYPE_USB, 0xfc2e, 0x0000);

		ocp_data = ocp_read_word(tp, MCU_TYPE_USB, 0xd428);
		ocp_data |= BIT(15);
		ocp_write_word(tp, MCU_TYPE_USB, 0xd428, ocp_data);

		ocp_data = ocp_read_word(tp, MCU_TYPE_USB, 0xc4d4);
		ocp_data |= BIT(0);
		ocp_write_word(tp, MCU_TYPE_USB, 0xc4d4, ocp_data);

		ocp_data = ocp_read_word(tp, MCU_TYPE_USB, 0xc4d6);
		ocp_data &= ~BIT(0);
		ocp_write_word(tp, MCU_TYPE_USB, 0xc4d6, ocp_data);

		ocp_data = ocp_read_word(tp, MCU_TYPE_USB, 0xd428);
		ocp_data &= ~BIT(15);
		ocp_write_word(tp, MCU_TYPE_USB, 0xd428, ocp_data);

		rtl_reset_ocp_base(tp);
	}

	rtl_reset_ocp_base(tp);
}

static void r8152_aldps_en(struct r8152 *tp, bool enable)
{
	if (enable) {
		ocp_reg_write(tp, OCP_ALDPS_CONFIG, ENPWRSAVE | ENPDNPS |
						    LINKENA | DIS_SDSAVE);
	} else {
		ocp_reg_write(tp, OCP_ALDPS_CONFIG, ENPDNPS | LINKENA |
						    DIS_SDSAVE);
		msleep(20);
	}
}

static inline void r8152_mmd_indirect(struct r8152 *tp, u16 dev, u16 reg)
{
	ocp_reg_write(tp, OCP_EEE_AR, FUN_ADDR | dev);
	ocp_reg_write(tp, OCP_EEE_DATA, reg);
	ocp_reg_write(tp, OCP_EEE_AR, FUN_DATA | dev);
}

#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,6,0)
static u16 r8152_mmd_read(struct r8152 *tp, u16 dev, u16 reg)
{
	u16 data;

	r8152_mmd_indirect(tp, dev, reg);
	data = ocp_reg_read(tp, OCP_EEE_DATA);
	ocp_reg_write(tp, OCP_EEE_AR, 0x0000);

	return data;
}
#endif /* LINUX_VERSION_CODE >= KERNEL_VERSION(3,6,0) */

static void r8152_mmd_write(struct r8152 *tp, u16 dev, u16 reg, u16 data)
{
	r8152_mmd_indirect(tp, dev, reg);
	ocp_reg_write(tp, OCP_EEE_DATA, data);
	ocp_reg_write(tp, OCP_EEE_AR, 0x0000);
}

static void r8152_eee_en(struct r8152 *tp, bool enable)
{
	u16 config1, config2, config3;
	u32 ocp_data;

	ocp_data = ocp_read_word(tp, MCU_TYPE_PLA, PLA_EEE_CR);
	config1 = ocp_reg_read(tp, OCP_EEE_CONFIG1) & ~sd_rise_time_mask;
	config2 = ocp_reg_read(tp, OCP_EEE_CONFIG2);
	config3 = ocp_reg_read(tp, OCP_EEE_CONFIG3) & ~fast_snr_mask;

	if (enable) {
		ocp_data |= EEE_RX_EN | EEE_TX_EN;
		config1 |= EEE_10_CAP | EEE_NWAY_EN | TX_QUIET_EN | RX_QUIET_EN;
		config1 |= sd_rise_time(1);
		config2 |= RG_DACQUIET_EN | RG_LDVQUIET_EN;
		config3 |= fast_snr(42);
	} else {
		ocp_data &= ~(EEE_RX_EN | EEE_TX_EN);
		config1 &= ~(EEE_10_CAP | EEE_NWAY_EN | TX_QUIET_EN |
			     RX_QUIET_EN);
		config1 |= sd_rise_time(7);
		config2 &= ~(RG_DACQUIET_EN | RG_LDVQUIET_EN);
		config3 |= fast_snr(511);
	}

	ocp_write_word(tp, MCU_TYPE_PLA, PLA_EEE_CR, ocp_data);
	ocp_reg_write(tp, OCP_EEE_CONFIG1, config1);
	ocp_reg_write(tp, OCP_EEE_CONFIG2, config2);
	ocp_reg_write(tp, OCP_EEE_CONFIG3, config3);
}

static void r8153_eee_en(struct r8152 *tp, bool enable)
{
	u32 ocp_data;
	u16 config;

	ocp_data = ocp_read_word(tp, MCU_TYPE_PLA, PLA_EEE_CR);
	config = ocp_reg_read(tp, OCP_EEE_CFG);

	if (enable) {
		ocp_data |= EEE_RX_EN | EEE_TX_EN;
		config |= EEE10_EN;
	} else {
		ocp_data &= ~(EEE_RX_EN | EEE_TX_EN);
		config &= ~EEE10_EN;
	}

	ocp_write_word(tp, MCU_TYPE_PLA, PLA_EEE_CR, ocp_data);
	ocp_reg_write(tp, OCP_EEE_CFG, config);

	tp->ups_info.eee = enable;
}

static void r8156_eee_en(struct r8152 *tp, bool enable)
{
	u16 config;

	r8153_eee_en(tp, enable);

	config = ocp_reg_read(tp, OCP_EEE_ADV2);

	if (enable)
		config |= MDIO_EEE_2_5GT;
	else
		config &= ~MDIO_EEE_2_5GT;

	ocp_reg_write(tp, OCP_EEE_ADV2, config);
}

static void rtl_eee_enable(struct r8152 *tp, bool enable)
{
	switch (tp->version) {
	case RTL_VER_01:
	case RTL_VER_02:
	case RTL_VER_07:
		if (enable) {
			r8152_eee_en(tp, true);
			r8152_mmd_write(tp, MDIO_MMD_AN, MDIO_AN_EEE_ADV,
					tp->eee_adv);
		} else {
			r8152_eee_en(tp, false);
			r8152_mmd_write(tp, MDIO_MMD_AN, MDIO_AN_EEE_ADV, 0);
		}
		break;
	case RTL_VER_03:
	case RTL_VER_04:
	case RTL_VER_05:
	case RTL_VER_06:
	case RTL_VER_08:
	case RTL_VER_09:
	case RTL_VER_14:
		if (enable) {
			r8153_eee_en(tp, true);
			ocp_reg_write(tp, OCP_EEE_ADV, tp->eee_adv);
		} else {
			r8153_eee_en(tp, false);
			ocp_reg_write(tp, OCP_EEE_ADV, 0);
		}
		break;
	case RTL_VER_10:
	case RTL_VER_11:
	case RTL_VER_12:
	case RTL_VER_13:
	case RTL_VER_15:
		if (enable) {
			r8156_eee_en(tp, true);
			ocp_reg_write(tp, OCP_EEE_ADV, tp->eee_adv);
		} else {
			r8156_eee_en(tp, false);
			ocp_reg_write(tp, OCP_EEE_ADV, 0);
		}
		break;
	default:
		break;
	}
}

static void r8152b_enable_fc(struct r8152 *tp)
{
	u16 anar;

	anar = r8152_mdio_read(tp, MII_ADVERTISE);
	anar |= ADVERTISE_PAUSE_CAP | ADVERTISE_PAUSE_ASYM;
	r8152_mdio_write(tp, MII_ADVERTISE, anar);

	tp->ups_info.flow_control = true;
}

static void rtl8152_disable(struct r8152 *tp)
{
	r8152_aldps_en(tp, false);
	rtl_disable(tp);
	r8152_aldps_en(tp, true);
}

static void r8152b_hw_phy_cfg(struct r8152 *tp)
{
	r8152b_firmware(tp);

	rtl_eee_enable(tp, tp->eee_en);
	r8152_aldps_en(tp, true);
	r8152b_enable_fc(tp);

	set_bit(PHY_RESET, &tp->flags);
}

static void wait_oob_link_list_ready(struct r8152 *tp)
{
	u32 ocp_data;
	int i;

	for (i = 0; i < 1000; i++) {
		ocp_data = ocp_read_byte(tp, MCU_TYPE_PLA, PLA_OOB_CTRL);
		if (ocp_data & LINK_LIST_READY)
			break;
		usleep_range(1000, 2000);
	}
}

static void r8156b_wait_loading_flash(struct r8152 *tp)
{
	if ((ocp_read_word(tp, MCU_TYPE_PLA, PLA_GPHY_CTRL) & GPHY_FLASH) &&
	    !(ocp_read_word(tp, MCU_TYPE_USB, USB_GPHY_CTRL) & BYPASS_FLASH)) {
		int i;

		for (i = 0; i < 100; i++) {
			if (ocp_read_word(tp, MCU_TYPE_USB, USB_GPHY_CTRL) & GPHY_PATCH_DONE)
				break;
			usleep_range(1000, 2000);
		}
	}
}

static void r8152b_exit_oob(struct r8152 *tp)
{
	u32 ocp_data;

	ocp_data = ocp_read_dword(tp, MCU_TYPE_PLA, PLA_RCR);
	ocp_data &= ~RCR_ACPT_ALL;
	ocp_write_dword(tp, MCU_TYPE_PLA, PLA_RCR, ocp_data);

	rxdy_gated_en(tp, true);
	r8153_teredo_off(tp);
	ocp_write_byte(tp, MCU_TYPE_PLA, PLA_CRWECR, CRWECR_NORAML);
	ocp_write_byte(tp, MCU_TYPE_PLA, PLA_CR, 0x00);

	ocp_data = ocp_read_byte(tp, MCU_TYPE_PLA, PLA_OOB_CTRL);
	ocp_data &= ~NOW_IS_OOB;
	ocp_write_byte(tp, MCU_TYPE_PLA, PLA_OOB_CTRL, ocp_data);

	ocp_data = ocp_read_word(tp, MCU_TYPE_PLA, PLA_SFF_STS_7);
	ocp_data &= ~MCU_BORW_EN;
	ocp_write_word(tp, MCU_TYPE_PLA, PLA_SFF_STS_7, ocp_data);

	wait_oob_link_list_ready(tp);

	ocp_data = ocp_read_word(tp, MCU_TYPE_PLA, PLA_SFF_STS_7);
	ocp_data |= RE_INIT_LL;
	ocp_write_word(tp, MCU_TYPE_PLA, PLA_SFF_STS_7, ocp_data);

	wait_oob_link_list_ready(tp);

	rtl8152_nic_reset(tp);

	/* rx share fifo credit full threshold */
	ocp_write_dword(tp, MCU_TYPE_PLA, PLA_RXFIFO_CTRL0, RXFIFO_THR1_NORMAL);

	if (tp->udev->speed == USB_SPEED_FULL ||
	    tp->udev->speed == USB_SPEED_LOW) {
		/* rx share fifo credit near full threshold */
		ocp_write_dword(tp, MCU_TYPE_PLA, PLA_RXFIFO_CTRL1,
				RXFIFO_THR2_FULL);
		ocp_write_dword(tp, MCU_TYPE_PLA, PLA_RXFIFO_CTRL2,
				RXFIFO_THR3_FULL);
	} else {
		/* rx share fifo credit near full threshold */
		ocp_write_dword(tp, MCU_TYPE_PLA, PLA_RXFIFO_CTRL1,
				RXFIFO_THR2_HIGH);
		ocp_write_dword(tp, MCU_TYPE_PLA, PLA_RXFIFO_CTRL2,
				RXFIFO_THR3_HIGH);
	}

	/* TX share fifo free credit full threshold */
	ocp_write_dword(tp, MCU_TYPE_PLA, PLA_TXFIFO_CTRL, TXFIFO_THR_NORMAL2);

	ocp_write_byte(tp, MCU_TYPE_USB, USB_TX_AGG, TX_AGG_MAX_THRESHOLD);
	ocp_write_dword(tp, MCU_TYPE_USB, USB_RX_BUF_TH, RX_THR_HIGH);
	ocp_write_dword(tp, MCU_TYPE_USB, USB_TX_DMA,
			TEST_MODE_DISABLE | TX_SIZE_ADJUST1);

	rtl_rx_vlan_en(tp, tp->netdev->features & NETIF_F_HW_VLAN_CTAG_RX);

	ocp_write_word(tp, MCU_TYPE_PLA, PLA_RMS, RTL8152_RMS);

	ocp_data = ocp_read_word(tp, MCU_TYPE_PLA, PLA_TCR0);
	ocp_data |= TCR0_AUTO_FIFO;
	ocp_write_word(tp, MCU_TYPE_PLA, PLA_TCR0, ocp_data);
}

static void r8152b_enter_oob(struct r8152 *tp)
{
	u32 ocp_data;

	ocp_data = ocp_read_byte(tp, MCU_TYPE_PLA, PLA_OOB_CTRL);
	ocp_data &= ~NOW_IS_OOB;
	ocp_write_byte(tp, MCU_TYPE_PLA, PLA_OOB_CTRL, ocp_data);

	ocp_write_dword(tp, MCU_TYPE_PLA, PLA_RXFIFO_CTRL0, RXFIFO_THR1_OOB);
	ocp_write_dword(tp, MCU_TYPE_PLA, PLA_RXFIFO_CTRL1, RXFIFO_THR2_OOB);
	ocp_write_dword(tp, MCU_TYPE_PLA, PLA_RXFIFO_CTRL2, RXFIFO_THR3_OOB);

	rtl_disable(tp);

	wait_oob_link_list_ready(tp);

	ocp_data = ocp_read_word(tp, MCU_TYPE_PLA, PLA_SFF_STS_7);
	ocp_data |= RE_INIT_LL;
	ocp_write_word(tp, MCU_TYPE_PLA, PLA_SFF_STS_7, ocp_data);

	wait_oob_link_list_ready(tp);

	ocp_write_word(tp, MCU_TYPE_PLA, PLA_RMS, RTL8152_RMS);

	rtl_rx_vlan_en(tp, true);

	ocp_data = ocp_read_word(tp, MCU_TYPE_PLA, PLA_BDC_CR);
	ocp_data |= ALDPS_PROXY_MODE;
	ocp_write_word(tp, MCU_TYPE_PLA, PLA_BDC_CR, ocp_data);

	ocp_data = ocp_read_byte(tp, MCU_TYPE_PLA, PLA_OOB_CTRL);
	ocp_data |= NOW_IS_OOB | DIS_MCU_CLROOB;
	ocp_write_byte(tp, MCU_TYPE_PLA, PLA_OOB_CTRL, ocp_data);

	rxdy_gated_en(tp, false);

	ocp_data = ocp_read_dword(tp, MCU_TYPE_PLA, PLA_RCR);
	ocp_data |= RCR_APM | RCR_AM | RCR_AB;
	ocp_write_dword(tp, MCU_TYPE_PLA, PLA_RCR, ocp_data);
}

static int r8156_lock_main(struct r8152 *tp, bool lock)
{
	u16 data;
	int i;

	data = ocp_reg_read(tp, 0xa46a);
	if (lock)
		data |= BIT(1);
	else
		data &= ~BIT(1);
	ocp_reg_write(tp, 0xa46a, data);

	if (lock) {
		for (i = 0; i < 100; i++) {
			usleep_range(1000, 2000);
			data = ocp_reg_read(tp, 0xa730) & 0xff;
			if (data == 1)
				break;
		}
	} else {
		for (i = 0; i < 100; i++) {
			usleep_range(1000, 2000);
			data = ocp_reg_read(tp, 0xa730) & 0xff;
			if (data != 1)
				break;
		}
	}

	if (i == 100)
		return -ETIME;
	else
		return 0;
}

static void r8153_wdt1_end(struct r8152 *tp)
{
	int i;

	/* Wait till the WTD timer is ready. It would take at most 104 ms. */
	for (i = 0; i < 104; i++) {
		u32 ocp_data = ocp_read_byte(tp, MCU_TYPE_USB, USB_WDT1_CTRL);

		if (!(ocp_data & WTD1_EN))
			break;
		usleep_range(1000, 2000);
	}
}

#define DBG_COUNTER_MASK		0x1f
#define DBG_DRV_RUNNING			(1 << 5)
#define DBG_IS_LINUX			8
#define DGB_DRV_STATE_MASK		(3 << 14)
#define DGB_DRV_STATE_LOAD		(2 << 14)
#define DGB_DRV_STATE_UNLOAD		(1 << 14)
static void rtl_set_dbg_info_init(struct r8152 *tp)
{
	u32 counter;

	counter = ocp_read_byte(tp, MCU_TYPE_USB, 0xcfcf);
	counter = (counter & DBG_COUNTER_MASK) + 1;
	ocp_write_byte(tp, MCU_TYPE_USB, 0xcfcf, counter | DBG_DRV_RUNNING);
	counter = (counter << 5) | DBG_IS_LINUX;
	ocp_write_word(tp, MCU_TYPE_USB, 0xcfd0, counter);
}

static void rtl_set_dbg_info_state(struct r8152 *tp, u16 state)
{
	u32 ocp_data;

	ocp_data = ocp_read_word(tp, MCU_TYPE_USB, 0xcfd0);
	ocp_data &= ~DGB_DRV_STATE_MASK;
	ocp_write_word(tp, MCU_TYPE_USB, 0xcfd0, state | ocp_data);
}

static void r8153_firmware(struct r8152 *tp)
{
	if (tp->version == RTL_VER_03) {
		rtl_reset_ocp_base(tp);

		rtl_pre_ram_code(tp, 0x8146, 0x7000, true);
		sram_write(tp, 0xb820, 0x0290);
		sram_write(tp, 0xa012, 0x0000);
		sram_write(tp, 0xa014, 0x2c04);
		ocp_write_word(tp, MCU_TYPE_PLA, 0xb438, 0x2c18);
		ocp_write_word(tp, MCU_TYPE_PLA, 0xb438, 0x2c45);
		ocp_write_word(tp, MCU_TYPE_PLA, 0xb438, 0x2c45);
		ocp_write_word(tp, MCU_TYPE_PLA, 0xb438, 0xd502);
		ocp_write_word(tp, MCU_TYPE_PLA, 0xb438, 0x8301);
		ocp_write_word(tp, MCU_TYPE_PLA, 0xb438, 0x8306);
		ocp_write_word(tp, MCU_TYPE_PLA, 0xb438, 0xd500);
		ocp_write_word(tp, MCU_TYPE_PLA, 0xb438, 0x8208);
		ocp_write_word(tp, MCU_TYPE_PLA, 0xb438, 0xd501);
		ocp_write_word(tp, MCU_TYPE_PLA, 0xb438, 0xe018);
		ocp_write_word(tp, MCU_TYPE_PLA, 0xb438, 0x0308);
		ocp_write_word(tp, MCU_TYPE_PLA, 0xb438, 0x60f2);
		ocp_write_word(tp, MCU_TYPE_PLA, 0xb438, 0x8404);
		ocp_write_word(tp, MCU_TYPE_PLA, 0xb438, 0x607d);
		ocp_write_word(tp, MCU_TYPE_PLA, 0xb438, 0xc117);
		ocp_write_word(tp, MCU_TYPE_PLA, 0xb438, 0x2c16);
		ocp_write_word(tp, MCU_TYPE_PLA, 0xb438, 0xc116);
		ocp_write_word(tp, MCU_TYPE_PLA, 0xb438, 0x2c16);
		ocp_write_word(tp, MCU_TYPE_PLA, 0xb438, 0x607d);
		ocp_write_word(tp, MCU_TYPE_PLA, 0xb438, 0xc117);
		ocp_write_word(tp, MCU_TYPE_PLA, 0xb438, 0xa404);
		ocp_write_word(tp, MCU_TYPE_PLA, 0xb438, 0xd500);
		ocp_write_word(tp, MCU_TYPE_PLA, 0xb438, 0x0800);
		ocp_write_word(tp, MCU_TYPE_PLA, 0xb438, 0xd501);
		ocp_write_word(tp, MCU_TYPE_PLA, 0xb438, 0x62d2);
		ocp_write_word(tp, MCU_TYPE_PLA, 0xb438, 0x615d);
		ocp_write_word(tp, MCU_TYPE_PLA, 0xb438, 0xc115);
		ocp_write_word(tp, MCU_TYPE_PLA, 0xb438, 0xa404);
		ocp_write_word(tp, MCU_TYPE_PLA, 0xb438, 0xc307);
		ocp_write_word(tp, MCU_TYPE_PLA, 0xb438, 0xd502);
		ocp_write_word(tp, MCU_TYPE_PLA, 0xb438, 0x8301);
		ocp_write_word(tp, MCU_TYPE_PLA, 0xb438, 0x8306);
		ocp_write_word(tp, MCU_TYPE_PLA, 0xb438, 0xd500);
		ocp_write_word(tp, MCU_TYPE_PLA, 0xb438, 0x8208);
		ocp_write_word(tp, MCU_TYPE_PLA, 0xb438, 0x2c42);
		ocp_write_word(tp, MCU_TYPE_PLA, 0xb438, 0xc114);
		ocp_write_word(tp, MCU_TYPE_PLA, 0xb438, 0x8404);
		ocp_write_word(tp, MCU_TYPE_PLA, 0xb438, 0xc317);
		ocp_write_word(tp, MCU_TYPE_PLA, 0xb438, 0xd701);
		ocp_write_word(tp, MCU_TYPE_PLA, 0xb438, 0x435d);
		ocp_write_word(tp, MCU_TYPE_PLA, 0xb438, 0xd500);
		ocp_write_word(tp, MCU_TYPE_PLA, 0xb438, 0xa208);
		ocp_write_word(tp, MCU_TYPE_PLA, 0xb438, 0xd502);
		ocp_write_word(tp, MCU_TYPE_PLA, 0xb438, 0xa306);
		ocp_write_word(tp, MCU_TYPE_PLA, 0xb438, 0xa301);
		ocp_write_word(tp, MCU_TYPE_PLA, 0xb438, 0x2c42);
		ocp_write_word(tp, MCU_TYPE_PLA, 0xb438, 0x8404);
		ocp_write_word(tp, MCU_TYPE_PLA, 0xb438, 0x613d);
		ocp_write_word(tp, MCU_TYPE_PLA, 0xb438, 0xc115);
		ocp_write_word(tp, MCU_TYPE_PLA, 0xb438, 0xc307);
		ocp_write_word(tp, MCU_TYPE_PLA, 0xb438, 0xd502);
		ocp_write_word(tp, MCU_TYPE_PLA, 0xb438, 0x8301);
		ocp_write_word(tp, MCU_TYPE_PLA, 0xb438, 0x8306);
		ocp_write_word(tp, MCU_TYPE_PLA, 0xb438, 0xd500);
		ocp_write_word(tp, MCU_TYPE_PLA, 0xb438, 0x8208);
		ocp_write_word(tp, MCU_TYPE_PLA, 0xb438, 0x2c42);
		ocp_write_word(tp, MCU_TYPE_PLA, 0xb438, 0xc114);
		ocp_write_word(tp, MCU_TYPE_PLA, 0xb438, 0xc317);
		ocp_write_word(tp, MCU_TYPE_PLA, 0xb438, 0xd701);
		ocp_write_word(tp, MCU_TYPE_PLA, 0xb438, 0x40dd);
		ocp_write_word(tp, MCU_TYPE_PLA, 0xb438, 0xd500);
		ocp_write_word(tp, MCU_TYPE_PLA, 0xb438, 0xa208);
		ocp_write_word(tp, MCU_TYPE_PLA, 0xb438, 0xd502);
		ocp_write_word(tp, MCU_TYPE_PLA, 0xb438, 0xa306);
		ocp_write_word(tp, MCU_TYPE_PLA, 0xb438, 0xa301);
		ocp_write_word(tp, MCU_TYPE_PLA, 0xb438, 0xd500);
		ocp_write_word(tp, MCU_TYPE_PLA, 0xb438, 0xd702);
		ocp_write_word(tp, MCU_TYPE_PLA, 0xb438, 0x0800);
		sram_write(tp, 0xa01a, 0x0000);
		sram_write(tp, 0xa006, 0x0fff);
		sram_write(tp, 0xa004, 0x0fff);
		sram_write(tp, 0xa002, 0x05a3);
		sram_write(tp, 0xa000, 0x3591);
		sram_write(tp, 0xb820, 0x0210);
		rtl_post_ram_code(tp, 0x8146, true);
	} else if (tp->version == RTL_VER_04) {
		static u8 usb_patch_b[] = {
			0x08, 0xe0, 0x0f, 0xe0,
			0x18, 0xe0, 0x24, 0xe0,
			0x26, 0xe0, 0x3a, 0xe0,
			0x84, 0xe0, 0x9c, 0xe0,
			0xc2, 0x49, 0x04, 0xf0,
			0x02, 0xc0, 0x00, 0xb8,
			0x14, 0x18, 0x02, 0xc0,
			0x00, 0xb8, 0x2e, 0x18,
			0x06, 0x89, 0x08, 0xc0,
			0x0c, 0x61, 0x92, 0x48,
			0x93, 0x48, 0x0c, 0x89,
			0x02, 0xc0, 0x00, 0xb8,
			0x08, 0x05, 0x40, 0xb4,
			0x16, 0x89, 0x6d, 0xc0,
			0x00, 0x61, 0x95, 0x49,
			0x06, 0xf0, 0xfa, 0xc0,
			0x0c, 0x61, 0x92, 0x48,
			0x93, 0x48, 0x0c, 0x89,
			0x02, 0xc0, 0x00, 0xb8,
			0xe2, 0x04, 0x02, 0xc2,
			0x00, 0xba, 0xec, 0x11,
			0x60, 0x60, 0x85, 0x49,
			0x0d, 0xf1, 0x11, 0xc6,
			0xd2, 0x61, 0x91, 0x49,
			0xfd, 0xf0, 0x74, 0x60,
			0x04, 0x48, 0x74, 0x88,
			0x08, 0xc6, 0x08, 0xc0,
			0xc4, 0x98, 0x01, 0x18,
			0xc0, 0x88, 0x02, 0xc0,
			0x00, 0xb8, 0x6e, 0x12,
			0x04, 0xe4, 0x0d, 0x00,
			0x00, 0xd4, 0xd1, 0x49,
			0x3c, 0xf1, 0xd2, 0x49,
			0x16, 0xf1, 0xd3, 0x49,
			0x18, 0xf1, 0xd4, 0x49,
			0x19, 0xf1, 0xd5, 0x49,
			0x1a, 0xf1, 0xd6, 0x49,
			0x1b, 0xf1, 0xd7, 0x49,
			0x1c, 0xf1, 0xd8, 0x49,
			0x1d, 0xf1, 0xd9, 0x49,
			0x20, 0xf1, 0xda, 0x49,
			0x23, 0xf1, 0xdb, 0x49,
			0x24, 0xf1, 0x02, 0xc4,
			0x00, 0xbc, 0x20, 0x04,
			0xe5, 0x8e, 0x02, 0xc4,
			0x00, 0xbc, 0x14, 0x02,
			0x02, 0xc4, 0x00, 0xbc,
			0x16, 0x02, 0x02, 0xc4,
			0x00, 0xbc, 0x18, 0x02,
			0x02, 0xc4, 0x00, 0xbc,
			0x1a, 0x02, 0x02, 0xc4,
			0x00, 0xbc, 0x1c, 0x02,
			0x02, 0xc4, 0x00, 0xbc,
			0x94, 0x02, 0x10, 0xc7,
			0xe0, 0x8e, 0x02, 0xc4,
			0x00, 0xbc, 0x8a, 0x02,
			0x0b, 0xc7, 0xe4, 0x8e,
			0x02, 0xc4, 0x00, 0xbc,
			0x88, 0x02, 0x02, 0xc4,
			0x00, 0xbc, 0x6e, 0x02,
			0x02, 0xc4, 0x00, 0xbc,
			0x5a, 0x02, 0x30, 0xe4,
			0x0c, 0xc3, 0x60, 0x64,
			0xc5, 0x49, 0x04, 0xf1,
			0x74, 0x64, 0xc4, 0x48,
			0x74, 0x8c, 0x06, 0xc3,
			0x64, 0x8e, 0x02, 0xc4,
			0x00, 0xbc, 0x20, 0x04,
			0x00, 0xd8, 0x00, 0xe4,
			0xb2, 0xc0, 0x00, 0x61,
			0x90, 0x49, 0x09, 0xf1,
			0x8b, 0xc6, 0xca, 0x61,
			0x94, 0x49, 0x0e, 0xf1,
			0xf6, 0xc6, 0xda, 0x60,
			0x81, 0x49, 0x0a, 0xf0,
			0x65, 0x60, 0x03, 0x48,
			0x65, 0x88, 0xef, 0xc6,
			0xdc, 0x60, 0x80, 0x48,
			0xdc, 0x88, 0x05, 0xc6,
			0x00, 0xbe, 0x02, 0xc6,
			0x00, 0xbe, 0x36, 0x13,
			0x4c, 0x17, 0x99, 0xc4,
			0x80, 0x65, 0xd0, 0x49,
			0x04, 0xf1, 0xfa, 0x75,
			0x04, 0xc4, 0x00, 0xbc,
			0x03, 0xc4, 0x00, 0xbc,
			0x9a, 0x00, 0xee, 0x01 };
		static u8 pla_patch_b[] = {
			0x08, 0xe0, 0xea, 0xe0,
			0xf2, 0xe0, 0x04, 0xe1,
			0x09, 0xe1, 0x0e, 0xe1,
			0x46, 0xe1, 0xf7, 0xe1,
			0x14, 0xc2, 0x40, 0x73,
			0xba, 0x48, 0x40, 0x9b,
			0x11, 0xc2, 0x40, 0x73,
			0xb0, 0x49, 0x17, 0xf0,
			0xbf, 0x49, 0x03, 0xf1,
			0x09, 0xc5, 0x00, 0xbd,
			0xb1, 0x49, 0x11, 0xf0,
			0xb1, 0x48, 0x40, 0x9b,
			0x02, 0xc2, 0x00, 0xba,
			0x1a, 0x17, 0x00, 0xe0,
			0x1e, 0xfc, 0xbc, 0xc0,
			0xf0, 0xc0, 0xde, 0xe8,
			0x00, 0x80, 0x00, 0x20,
			0x2c, 0x75, 0xd4, 0x49,
			0x12, 0xf1, 0x32, 0xe0,
			0xf8, 0xc2, 0x46, 0x71,
			0xf7, 0xc2, 0x40, 0x73,
			0xbe, 0x49, 0x03, 0xf1,
			0xf5, 0xc7, 0x02, 0xe0,
			0xf2, 0xc7, 0x4f, 0x30,
			0x26, 0x62, 0xa1, 0x49,
			0xf0, 0xf1, 0x22, 0x72,
			0xa0, 0x49, 0xed, 0xf1,
			0x25, 0x25, 0x18, 0x1f,
			0x97, 0x30, 0x91, 0x30,
			0x36, 0x9a, 0x2c, 0x75,
			0x3c, 0xc3, 0x60, 0x73,
			0xb1, 0x49, 0x0d, 0xf1,
			0xdc, 0x21, 0xbc, 0x25,
			0x30, 0xc6, 0xc0, 0x77,
			0x04, 0x13, 0x21, 0xf0,
			0x03, 0x13, 0x22, 0xf0,
			0x02, 0x13, 0x23, 0xf0,
			0x01, 0x13, 0x24, 0xf0,
			0x08, 0x13, 0x08, 0xf1,
			0x2e, 0x73, 0xba, 0x21,
			0xbd, 0x25, 0x05, 0x13,
			0x03, 0xf1, 0x24, 0xc5,
			0x00, 0xbd, 0xd4, 0x49,
			0x03, 0xf1, 0x1c, 0xc5,
			0x00, 0xbd, 0xc4, 0xc6,
			0xc6, 0x67, 0x2e, 0x75,
			0xd7, 0x22, 0xdd, 0x26,
			0x05, 0x15, 0x1b, 0xf0,
			0x14, 0xc6, 0x00, 0xbe,
			0x13, 0xc5, 0x00, 0xbd,
			0x12, 0xc5, 0x00, 0xbd,
			0xf1, 0x49, 0xfb, 0xf1,
			0xef, 0xe7, 0xf4, 0x49,
			0xfa, 0xf1, 0xec, 0xe7,
			0xf3, 0x49, 0xf7, 0xf1,
			0xe9, 0xe7, 0xf2, 0x49,
			0xf4, 0xf1, 0xe6, 0xe7,
			0xb6, 0xc0, 0x9e, 0x12,
			0xde, 0x11, 0x0a, 0x12,
			0x3c, 0x13, 0x00, 0xa0,
			0xa0, 0xd1, 0x00, 0x00,
			0xc0, 0x75, 0xd0, 0x49,
			0x46, 0xf0, 0x26, 0x72,
			0xa7, 0x49, 0x43, 0xf0,
			0x22, 0x72, 0x25, 0x25,
			0x20, 0x1f, 0x97, 0x30,
			0x91, 0x30, 0x40, 0x73,
			0xf3, 0xc4, 0x1c, 0x40,
			0x04, 0xf0, 0xd7, 0x49,
			0x05, 0xf1, 0x37, 0xe0,
			0x53, 0x48, 0xc0, 0x9d,
			0x08, 0x02, 0x40, 0x66,
			0x64, 0x27, 0x06, 0x16,
			0x30, 0xf1, 0x46, 0x63,
			0x3b, 0x13, 0x2d, 0xf1,
			0x34, 0x9b, 0x18, 0x1b,
			0x93, 0x30, 0x2b, 0xc3,
			0x10, 0x1c, 0x2b, 0xe8,
			0x01, 0x14, 0x25, 0xf1,
			0x00, 0x1d, 0x26, 0x1a,
			0x8a, 0x30, 0x22, 0x73,
			0xb5, 0x25, 0x0e, 0x0b,
			0x00, 0x1c, 0x2c, 0xe8,
			0x1f, 0xc7, 0x27, 0x40,
			0x1a, 0xf1, 0x38, 0xe8,
			0x32, 0x1f, 0x8f, 0x30,
			0x08, 0x1b, 0x24, 0xe8,
			0x36, 0x72, 0x46, 0x77,
			0x00, 0x17, 0x0d, 0xf0,
			0x13, 0xc3, 0x1f, 0x40,
			0x03, 0xf1, 0x00, 0x1f,
			0x46, 0x9f, 0x44, 0x77,
			0x9f, 0x44, 0x5f, 0x44,
			0x17, 0xe8, 0x0a, 0xc7,
			0x27, 0x40, 0x05, 0xf1,
			0x02, 0xc3, 0x00, 0xbb,
			0xfa, 0x18, 0xb0, 0x18,
			0xff, 0xc7, 0x00, 0xbf,
			0xb8, 0xcd, 0xff, 0xff,
			0x02, 0x0c, 0x54, 0xa5,
			0xdc, 0xa5, 0x2f, 0x40,
			0x05, 0xf1, 0x00, 0x14,
			0xfa, 0xf1, 0x01, 0x1c,
			0x02, 0xe0, 0x00, 0x1c,
			0x80, 0xff, 0xb0, 0x49,
			0x04, 0xf0, 0x01, 0x0b,
			0xd3, 0xa1, 0x03, 0xe0,
			0x02, 0x0b, 0xd3, 0xa5,
			0x27, 0x31, 0x20, 0x37,
			0x02, 0x0b, 0xd3, 0xa5,
			0x27, 0x31, 0x20, 0x37,
			0x00, 0x13, 0xfb, 0xf1,
			0x80, 0xff, 0x22, 0x73,
			0xb5, 0x25, 0x18, 0x1e,
			0xde, 0x30, 0xd9, 0x30,
			0x64, 0x72, 0x11, 0x1e,
			0x68, 0x23, 0x16, 0x31,
			0x80, 0xff, 0x08, 0xc2,
			0x40, 0x73, 0x3a, 0x48,
			0x40, 0x9b, 0x06, 0xff,
			0x02, 0xc6, 0x00, 0xbe,
			0x08, 0x16, 0x1e, 0xfc,
			0x2c, 0x75, 0xdc, 0x21,
			0xbc, 0x25, 0x04, 0x13,
			0x0b, 0xf0, 0x03, 0x13,
			0x09, 0xf0, 0x02, 0x13,
			0x07, 0xf0, 0x01, 0x13,
			0x05, 0xf0, 0x08, 0x13,
			0x03, 0xf0, 0x04, 0xc3,
			0x00, 0xbb, 0x03, 0xc3,
			0x00, 0xbb, 0x8c, 0x15,
			0x76, 0x15, 0xa0, 0x64,
			0x40, 0x48, 0xa0, 0x8c,
			0x02, 0xc4, 0x00, 0xbc,
			0x82, 0x00, 0xa0, 0x62,
			0x21, 0x48, 0xa0, 0x8a,
			0x02, 0xc2, 0x00, 0xba,
			0x40, 0x03, 0x33, 0xc5,
			0xa0, 0x74, 0xc0, 0x49,
			0x1f, 0xf0, 0x30, 0xc5,
			0xa0, 0x73, 0x00, 0x13,
			0x04, 0xf1, 0xa2, 0x73,
			0x00, 0x13, 0x14, 0xf0,
			0x28, 0xc5, 0xa0, 0x74,
			0xc8, 0x49, 0x1b, 0xf1,
			0x26, 0xc5, 0xa0, 0x76,
			0xa2, 0x74, 0x01, 0x06,
			0x20, 0x37, 0xa0, 0x9e,
			0xa2, 0x9c, 0x1e, 0xc5,
			0xa2, 0x73, 0x23, 0x40,
			0x10, 0xf8, 0x04, 0xf3,
			0xa0, 0x73, 0x33, 0x40,
			0x0c, 0xf8, 0x15, 0xc5,
			0xa0, 0x74, 0x41, 0x48,
			0xa0, 0x9c, 0x14, 0xc5,
			0xa0, 0x76, 0x62, 0x48,
			0xe0, 0x48, 0xa0, 0x9e,
			0x10, 0xc6, 0x00, 0xbe,
			0x0a, 0xc5, 0xa0, 0x74,
			0x48, 0x48, 0xa0, 0x9c,
			0x0b, 0xc5, 0x20, 0x1e,
			0xa0, 0x9e, 0xe5, 0x48,
			0xa0, 0x9e, 0xf0, 0xe7,
			0xbc, 0xc0, 0xc8, 0xd2,
			0xcc, 0xd2, 0x28, 0xe4,
			0xe6, 0x01, 0xf0, 0xc0,
			0x18, 0x89, 0x00, 0x1d,
			0x3c, 0xc3, 0x64, 0x71,
			0x3c, 0xc0, 0x02, 0x99,
			0x00, 0x61, 0x67, 0x11,
			0x3c, 0xf1, 0x69, 0x33,
			0x35, 0xc0, 0x28, 0x40,
			0xf6, 0xf1, 0x34, 0xc0,
			0x00, 0x19, 0x81, 0x1b,
			0x91, 0xe8, 0x31, 0xc0,
			0x04, 0x1a, 0x84, 0x1b,
			0x8d, 0xe8, 0x82, 0xe8,
			0xa3, 0x49, 0xfe, 0xf0,
			0x2b, 0xc0, 0x7e, 0xe8,
			0xa1, 0x48, 0x28, 0xc0,
			0x84, 0x1b, 0x84, 0xe8,
			0x00, 0x1d, 0x69, 0x33,
			0x00, 0x1e, 0x01, 0x06,
			0xff, 0x18, 0x30, 0x40,
			0xfd, 0xf1, 0x19, 0xc0,
			0x00, 0x76, 0x2e, 0x40,
			0xf7, 0xf1, 0x21, 0x48,
			0x19, 0xc0, 0x84, 0x1b,
			0x75, 0xe8, 0x10, 0xc0,
			0x69, 0xe8, 0xa1, 0x49,
			0xfd, 0xf0, 0x11, 0xc0,
			0x00, 0x1a, 0x84, 0x1b,
			0x6d, 0xe8, 0x62, 0xe8,
			0xa5, 0x49, 0xfe, 0xf0,
			0x09, 0xc0, 0x01, 0x19,
			0x81, 0x1b, 0x66, 0xe8,
			0x54, 0xe0, 0x10, 0xd4,
			0x88, 0xd3, 0xb8, 0x0b,
			0x50, 0xe8, 0x20, 0xb4,
			0x10, 0xd8, 0x84, 0xd4,
			0xfd, 0xc0, 0x52, 0xe8,
			0x48, 0x33, 0xf9, 0xc0,
			0x00, 0x61, 0x9c, 0x20,
			0x9c, 0x24, 0xd0, 0x49,
			0x04, 0xf0, 0x04, 0x11,
			0x02, 0xf1, 0x03, 0xe0,
			0x00, 0x11, 0x06, 0xf1,
			0x5c, 0xc0, 0x00, 0x61,
			0x92, 0x48, 0x00, 0x89,
			0x3a, 0xe0, 0x06, 0x11,
			0x06, 0xf1, 0x55, 0xc0,
			0x00, 0x61, 0x11, 0x48,
			0x00, 0x89, 0x33, 0xe0,
			0x05, 0x11, 0x08, 0xf1,
			0x4e, 0xc0, 0x00, 0x61,
			0x91, 0x49, 0x04, 0xf0,
			0x91, 0x48, 0x00, 0x89,
			0x11, 0xe0, 0xd9, 0xc0,
			0x00, 0x61, 0x98, 0x20,
			0x98, 0x24, 0x25, 0x11,
			0x24, 0xf1, 0x44, 0xc0,
			0x29, 0xe8, 0x95, 0x49,
			0x20, 0xf0, 0xcf, 0xc0,
			0x00, 0x61, 0x98, 0x20,
			0x98, 0x24, 0x25, 0x11,
			0x1a, 0xf1, 0x37, 0xc0,
			0x00, 0x61, 0x92, 0x49,
			0x16, 0xf1, 0x12, 0x48,
			0x00, 0x89, 0x2f, 0xc0,
			0x00, 0x19, 0x00, 0x89,
			0x2d, 0xc0, 0x01, 0x89,
			0x2d, 0xc0, 0x04, 0x19,
			0x81, 0x1b, 0x1c, 0xe8,
			0x2a, 0xc0, 0x14, 0x19,
			0x81, 0x1b, 0x18, 0xe8,
			0x21, 0xc0, 0x0c, 0xe8,
			0x1f, 0xc0, 0x12, 0x48,
			0x81, 0x1b, 0x12, 0xe8,
			0xae, 0xc3, 0x66, 0x71,
			0xae, 0xc0, 0x02, 0x99,
			0x02, 0xc0, 0x00, 0xb8,
			0x96, 0x07, 0x13, 0xc4,
			0x84, 0x98, 0x00, 0x1b,
			0x86, 0x8b, 0x86, 0x73,
			0xbf, 0x49, 0xfe, 0xf1,
			0x80, 0x71, 0x82, 0x72,
			0x80, 0xff, 0x09, 0xc4,
			0x84, 0x98, 0x80, 0x99,
			0x82, 0x9a, 0x86, 0x8b,
			0x86, 0x73, 0xbf, 0x49,
			0xfe, 0xf1, 0x80, 0xff,
			0x08, 0xea, 0x30, 0xd4,
			0x10, 0xc0, 0x12, 0xe8,
			0x8a, 0xd3, 0x28, 0xe4,
			0x2c, 0xe4, 0x00, 0xd8,
			0x00, 0x00, 0x00, 0x00 };

		rtl_pre_ram_code(tp, 0x8146, 0x7001, true);
		sram_write(tp, 0xb820, 0x0290);
		sram_write(tp, 0xa012, 0x0000);
		sram_write(tp, 0xa014, 0x2c04);
		ocp_write_word(tp, MCU_TYPE_PLA, 0xb438, 0x2c07);
		ocp_write_word(tp, MCU_TYPE_PLA, 0xb438, 0x2c0a);
		ocp_write_word(tp, MCU_TYPE_PLA, 0xb438, 0x2c0d);
		ocp_write_word(tp, MCU_TYPE_PLA, 0xb438, 0xa240);
		ocp_write_word(tp, MCU_TYPE_PLA, 0xb438, 0xa104);
		ocp_write_word(tp, MCU_TYPE_PLA, 0xb438, 0x292d);
		ocp_write_word(tp, MCU_TYPE_PLA, 0xb438, 0x8620);
		ocp_write_word(tp, MCU_TYPE_PLA, 0xb438, 0xa480);
		ocp_write_word(tp, MCU_TYPE_PLA, 0xb438, 0x2a2c);
		ocp_write_word(tp, MCU_TYPE_PLA, 0xb438, 0x8480);
		ocp_write_word(tp, MCU_TYPE_PLA, 0xb438, 0xa101);
		ocp_write_word(tp, MCU_TYPE_PLA, 0xb438, 0x2a36);
		ocp_write_word(tp, MCU_TYPE_PLA, 0xb438, 0xd056);
		ocp_write_word(tp, MCU_TYPE_PLA, 0xb438, 0x2223);
		sram_write(tp, 0xa01a, 0x0000);
		sram_write(tp, 0xa006, 0x0222);
		sram_write(tp, 0xa004, 0x0a35);
		sram_write(tp, 0xa002, 0x0a2b);
		sram_write(tp, 0xa000, 0xf92c);
		sram_write(tp, 0xb820, 0x0210);
		rtl_post_ram_code(tp, 0x8146, true);

		r8153_wdt1_end(tp);

		rtl_clear_bp(tp, MCU_TYPE_USB);

		generic_ocp_write(tp, 0xf800, 0xff, sizeof(usb_patch_b),
				  usb_patch_b, MCU_TYPE_USB);
		ocp_write_word(tp, MCU_TYPE_USB, 0xfc26, 0xa000);
		ocp_write_word(tp, MCU_TYPE_USB, 0xfc28, 0x180c);
		ocp_write_word(tp, MCU_TYPE_USB, 0xfc2a, 0x0506);
		ocp_write_word(tp, MCU_TYPE_USB, 0xfc2c, 0x04E0);
		ocp_write_word(tp, MCU_TYPE_USB, 0xfc2e, 0x11E4);
		ocp_write_word(tp, MCU_TYPE_USB, 0xfc30, 0x125C);
		ocp_write_word(tp, MCU_TYPE_USB, 0xfc32, 0x0232);
		ocp_write_word(tp, MCU_TYPE_USB, 0xfc34, 0x131E);
		ocp_write_word(tp, MCU_TYPE_USB, 0xfc36, 0x0098);
		ocp_write_word(tp, MCU_TYPE_USB, USB_BP_EN, 0x00FF);

		rtl_clear_bp(tp, MCU_TYPE_PLA);

		/* Enable backup/restore of MACDBG. This is required after
		 * clearing PLA break points and before applying the PLA
		 * firmware.
		 */
		if (!(ocp_read_word(tp, MCU_TYPE_PLA, PLA_MACDBG_POST) &
		      DEBUG_OE)) {
			ocp_write_word(tp, MCU_TYPE_PLA, PLA_MACDBG_PRE,
				       DEBUG_LTSSM);
			ocp_write_word(tp, MCU_TYPE_PLA, PLA_MACDBG_POST,
				       DEBUG_LTSSM);
		}

		generic_ocp_write(tp, 0xf800, 0xff, sizeof(pla_patch_b),
				  pla_patch_b, MCU_TYPE_PLA);
		ocp_write_word(tp, MCU_TYPE_PLA, 0xfc26, 0x8000);
		ocp_write_word(tp, MCU_TYPE_PLA, 0xfc28, 0x1154);
		ocp_write_word(tp, MCU_TYPE_PLA, 0xfc2a, 0x1606);
		ocp_write_word(tp, MCU_TYPE_PLA, 0xfc2c, 0x155a);
		ocp_write_word(tp, MCU_TYPE_PLA, 0xfc2e, 0x0080);
		ocp_write_word(tp, MCU_TYPE_PLA, 0xfc30, 0x033c);
		ocp_write_word(tp, MCU_TYPE_PLA, 0xfc32, 0x01a0);
		ocp_write_word(tp, MCU_TYPE_PLA, 0xfc34, 0x0794);
		ocp_write_word(tp, MCU_TYPE_PLA, 0xfc36, 0x0000);
		ocp_write_word(tp, MCU_TYPE_PLA, PLA_BP_EN, 0x007f);

		/* reset UPHY timer to 36 ms */
		ocp_write_word(tp, MCU_TYPE_PLA, PLA_UPHY_TIMER, 36000 / 16);

		rtl_reset_ocp_base(tp);
	} else if (tp->version == RTL_VER_05) {
		u32 ocp_data;
		static u8 usb_patch_c[] = {
			0x08, 0xe0, 0x0a, 0xe0,
			0x14, 0xe0, 0x58, 0xe0,
			0x64, 0xe0, 0x79, 0xe0,
			0xab, 0xe0, 0xb6, 0xe0,
			0x02, 0xc5, 0x00, 0xbd,
			0x38, 0x3b, 0xdb, 0x49,
			0x04, 0xf1, 0x06, 0xc3,
			0x00, 0xbb, 0x5a, 0x02,
			0x05, 0xc4, 0x03, 0xc3,
			0x00, 0xbb, 0xa4, 0x04,
			0x7e, 0x02, 0x30, 0xd4,
			0x65, 0xc6, 0x66, 0x61,
			0x92, 0x49, 0x12, 0xf1,
			0x3e, 0xc0, 0x02, 0x61,
			0x97, 0x49, 0x05, 0xf0,
			0x3c, 0xc0, 0x00, 0x61,
			0x90, 0x49, 0x0a, 0xf1,
			0xca, 0x63, 0xb0, 0x49,
			0x09, 0xf1, 0xb1, 0x49,
			0x05, 0xf0, 0x32, 0xc0,
			0x00, 0x71, 0x9e, 0x49,
			0x03, 0xf1, 0xb0, 0x48,
			0x05, 0xe0, 0x30, 0x48,
			0xda, 0x61, 0x10, 0x48,
			0xda, 0x89, 0x4a, 0xc6,
			0xc0, 0x60, 0x85, 0x49,
			0x03, 0xf0, 0x31, 0x48,
			0x04, 0xe0, 0xb1, 0x48,
			0xb2, 0x48, 0x0f, 0xe0,
			0x30, 0x18, 0x1b, 0xc1,
			0x0f, 0xe8, 0x1a, 0xc6,
			0xc7, 0x65, 0xd0, 0x49,
			0x05, 0xf0, 0x32, 0x48,
			0x02, 0xc2, 0x00, 0xba,
			0x3e, 0x16, 0x02, 0xc2,
			0x00, 0xba, 0x48, 0x16,
			0x02, 0xc2, 0x00, 0xba,
			0x4a, 0x16, 0x02, 0xb4,
			0x09, 0xc2, 0x40, 0x99,
			0x0e, 0x48, 0x42, 0x98,
			0x42, 0x70, 0x8e, 0x49,
			0xfe, 0xf1, 0x02, 0xb0,
			0x80, 0xff, 0xc0, 0xd4,
			0xe4, 0x40, 0x20, 0xd4,
			0xca, 0xcf, 0x00, 0xcf,
			0x3c, 0xe4, 0x0c, 0xc0,
			0x00, 0x63, 0xb5, 0x49,
			0x09, 0xc0, 0x30, 0x18,
			0x06, 0xc1, 0xea, 0xef,
			0xf5, 0xc7, 0x02, 0xc0,
			0x00, 0xb8, 0xd0, 0x10,
			0xe4, 0x4b, 0x00, 0xd8,
			0x14, 0xc3, 0x60, 0x61,
			0x90, 0x49, 0x06, 0xf0,
			0x11, 0xc3, 0x70, 0x61,
			0x12, 0x48, 0x70, 0x89,
			0x08, 0xe0, 0x0a, 0xc6,
			0xd4, 0x61, 0x93, 0x48,
			0xd4, 0x89, 0x02, 0xc1,
			0x00, 0xb9, 0x72, 0x17,
			0x02, 0xc1, 0x00, 0xb9,
			0x9c, 0x15, 0x00, 0xd8,
			0xef, 0xcf, 0x20, 0xd4,
			0x30, 0x18, 0xe7, 0xc1,
			0xcb, 0xef, 0x2b, 0xc5,
			0xa0, 0x77, 0x00, 0x1c,
			0xa0, 0x9c, 0x28, 0xc5,
			0xa0, 0x64, 0xc0, 0x48,
			0xc1, 0x48, 0xc2, 0x48,
			0xa0, 0x8c, 0xb1, 0x64,
			0xc0, 0x48, 0xb1, 0x8c,
			0x20, 0xc5, 0xa0, 0x64,
			0x40, 0x48, 0x41, 0x48,
			0xc2, 0x48, 0xa0, 0x8c,
			0x19, 0xc5, 0xa4, 0x64,
			0x44, 0x48, 0xa4, 0x8c,
			0xb1, 0x64, 0x40, 0x48,
			0xb1, 0x8c, 0x14, 0xc4,
			0x80, 0x73, 0x13, 0xc4,
			0x82, 0x9b, 0x11, 0x1b,
			0x80, 0x9b, 0x0c, 0xc5,
			0xa0, 0x64, 0x40, 0x48,
			0x41, 0x48, 0x42, 0x48,
			0xa0, 0x8c, 0x05, 0xc5,
			0xa0, 0x9f, 0x02, 0xc5,
			0x00, 0xbd, 0x6c, 0x3a,
			0x1e, 0xfc, 0x10, 0xd8,
			0x86, 0xd4, 0xf8, 0xcb,
			0x20, 0xe4, 0x0a, 0xc0,
			0x16, 0x61, 0x91, 0x48,
			0x16, 0x89, 0x07, 0xc0,
			0x11, 0x19, 0x0c, 0x89,
			0x02, 0xc1, 0x00, 0xb9,
			0x02, 0x06, 0x00, 0xd4,
			0x40, 0xb4, 0xfe, 0xc0,
			0x16, 0x61, 0x91, 0x48,
			0x16, 0x89, 0xfb, 0xc0,
			0x11, 0x19, 0x0c, 0x89,
			0x02, 0xc1, 0x00, 0xb9,
			0xd2, 0x05, 0x00, 0x00 };
		static u8 pla_patch_c[] = {
			0x5d, 0xe0, 0x07, 0xe0,
			0x0f, 0xe0, 0x5a, 0xe0,
			0x59, 0xe0, 0x1f, 0xe0,
			0x57, 0xe0, 0x3e, 0xe1,
			0x08, 0xc2, 0x40, 0x73,
			0x3a, 0x48, 0x40, 0x9b,
			0x06, 0xff, 0x02, 0xc6,
			0x00, 0xbe, 0xcc, 0x17,
			0x1e, 0xfc, 0x2c, 0x75,
			0xdc, 0x21, 0xbc, 0x25,
			0x04, 0x13, 0x0b, 0xf0,
			0x03, 0x13, 0x09, 0xf0,
			0x02, 0x13, 0x07, 0xf0,
			0x01, 0x13, 0x05, 0xf0,
			0x08, 0x13, 0x03, 0xf0,
			0x04, 0xc3, 0x00, 0xbb,
			0x03, 0xc3, 0x00, 0xbb,
			0x50, 0x17, 0x3a, 0x17,
			0x33, 0xc5, 0xa0, 0x74,
			0xc0, 0x49, 0x1f, 0xf0,
			0x30, 0xc5, 0xa0, 0x73,
			0x00, 0x13, 0x04, 0xf1,
			0xa2, 0x73, 0x00, 0x13,
			0x14, 0xf0, 0x28, 0xc5,
			0xa0, 0x74, 0xc8, 0x49,
			0x1b, 0xf1, 0x26, 0xc5,
			0xa0, 0x76, 0xa2, 0x74,
			0x01, 0x06, 0x20, 0x37,
			0xa0, 0x9e, 0xa2, 0x9c,
			0x1e, 0xc5, 0xa2, 0x73,
			0x23, 0x40, 0x10, 0xf8,
			0x04, 0xf3, 0xa0, 0x73,
			0x33, 0x40, 0x0c, 0xf8,
			0x15, 0xc5, 0xa0, 0x74,
			0x41, 0x48, 0xa0, 0x9c,
			0x14, 0xc5, 0xa0, 0x76,
			0x62, 0x48, 0xe0, 0x48,
			0xa0, 0x9e, 0x10, 0xc6,
			0x00, 0xbe, 0x0a, 0xc5,
			0xa0, 0x74, 0x48, 0x48,
			0xa0, 0x9c, 0x0b, 0xc5,
			0x20, 0x1e, 0xa0, 0x9e,
			0xe5, 0x48, 0xa0, 0x9e,
			0xf0, 0xe7, 0xbc, 0xc0,
			0xc8, 0xd2, 0xcc, 0xd2,
			0x28, 0xe4, 0xfa, 0x01,
			0xf0, 0xc0, 0x18, 0x89,
			0x74, 0xc0, 0xcd, 0xe8,
			0x80, 0x76, 0x00, 0x1d,
			0x6e, 0xc3, 0x66, 0x62,
			0xa0, 0x49, 0x06, 0xf0,
			0x64, 0xc0, 0x02, 0x71,
			0x60, 0x99, 0x62, 0xc1,
			0x03, 0xe0, 0x5f, 0xc0,
			0x60, 0xc1, 0x02, 0x99,
			0x00, 0x61, 0x0f, 0x1b,
			0x59, 0x41, 0x03, 0x13,
			0x18, 0xf1, 0xe4, 0x49,
			0x20, 0xf1, 0xe5, 0x49,
			0x1e, 0xf0, 0x59, 0xc6,
			0xd0, 0x73, 0xb7, 0x49,
			0x08, 0xf0, 0x01, 0x0b,
			0x80, 0x13, 0x03, 0xf0,
			0xd0, 0x8b, 0x03, 0xe0,
			0x3f, 0x48, 0xd0, 0x9b,
			0x51, 0xc0, 0x10, 0x1a,
			0x84, 0x1b, 0xb1, 0xe8,
			0x4b, 0xc2, 0x40, 0x63,
			0x30, 0x48, 0x0a, 0xe0,
			0xe5, 0x49, 0x09, 0xf0,
			0x47, 0xc0, 0x00, 0x1a,
			0x84, 0x1b, 0xa7, 0xe8,
			0x41, 0xc2, 0x40, 0x63,
			0xb0, 0x48, 0x40, 0x8b,
			0x67, 0x11, 0x3f, 0xf1,
			0x69, 0x33, 0x32, 0xc0,
			0x28, 0x40, 0xd2, 0xf1,
			0x33, 0xc0, 0x00, 0x19,
			0x81, 0x1b, 0x99, 0xe8,
			0x30, 0xc0, 0x04, 0x1a,
			0x84, 0x1b, 0x95, 0xe8,
			0x8a, 0xe8, 0xa3, 0x49,
			0xfe, 0xf0, 0x2a, 0xc0,
			0x86, 0xe8, 0xa1, 0x48,
			0x84, 0x1b, 0x8d, 0xe8,
			0x00, 0x1d, 0x69, 0x33,
			0x00, 0x1e, 0x01, 0x06,
			0xff, 0x18, 0x30, 0x40,
			0xfd, 0xf1, 0x1f, 0xc0,
			0x00, 0x76, 0x2e, 0x40,
			0xf7, 0xf1, 0x21, 0x48,
			0x19, 0xc0, 0x84, 0x1b,
			0x7e, 0xe8, 0x74, 0x08,
			0x72, 0xe8, 0xa1, 0x49,
			0xfd, 0xf0, 0x11, 0xc0,
			0x00, 0x1a, 0x84, 0x1b,
			0x76, 0xe8, 0x6b, 0xe8,
			0xa5, 0x49, 0xfe, 0xf0,
			0x09, 0xc0, 0x01, 0x19,
			0x81, 0x1b, 0x6f, 0xe8,
			0x5a, 0xe0, 0xb8, 0x0b,
			0x50, 0xe8, 0x83, 0x00,
			0x82, 0x00, 0x20, 0xb4,
			0x10, 0xd8, 0x84, 0xd4,
			0x88, 0xd3, 0x10, 0xe0,
			0x00, 0xd8, 0x24, 0xd4,
			0xf9, 0xc0, 0x57, 0xe8,
			0x48, 0x33, 0xf3, 0xc0,
			0x00, 0x61, 0x6a, 0xc0,
			0x47, 0x11, 0x03, 0xf0,
			0x57, 0x11, 0x05, 0xf1,
			0x00, 0x61, 0x17, 0x48,
			0x00, 0x89, 0x41, 0xe0,
			0x9c, 0x20, 0x9c, 0x24,
			0xd0, 0x49, 0x09, 0xf0,
			0x04, 0x11, 0x07, 0xf1,
			0x00, 0x61, 0x97, 0x49,
			0x38, 0xf0, 0x97, 0x48,
			0x00, 0x89, 0x2b, 0xe0,
			0x00, 0x11, 0x05, 0xf1,
			0x00, 0x61, 0x92, 0x48,
			0x00, 0x89, 0x2f, 0xe0,
			0x06, 0x11, 0x05, 0xf1,
			0x00, 0x61, 0x11, 0x48,
			0x00, 0x89, 0x29, 0xe0,
			0x05, 0x11, 0x0f, 0xf1,
			0x00, 0x61, 0x93, 0x49,
			0x1a, 0xf1, 0x91, 0x49,
			0x0a, 0xf0, 0x91, 0x48,
			0x00, 0x89, 0x0f, 0xe0,
			0xc6, 0xc0, 0x00, 0x61,
			0x98, 0x20, 0x98, 0x24,
			0x25, 0x11, 0x80, 0xff,
			0xfa, 0xef, 0x17, 0xf1,
			0x38, 0xc0, 0x1f, 0xe8,
			0x95, 0x49, 0x13, 0xf0,
			0xf4, 0xef, 0x11, 0xf1,
			0x31, 0xc0, 0x00, 0x61,
			0x92, 0x49, 0x0d, 0xf1,
			0x12, 0x48, 0x00, 0x89,
			0x29, 0xc0, 0x00, 0x19,
			0x00, 0x89, 0x27, 0xc0,
			0x01, 0x89, 0x23, 0xc0,
			0x0e, 0xe8, 0x12, 0x48,
			0x81, 0x1b, 0x15, 0xe8,
			0xae, 0xc3, 0x66, 0x62,
			0xa0, 0x49, 0x04, 0xf0,
			0x64, 0x71, 0xa3, 0xc0,
			0x02, 0x99, 0x02, 0xc0,
			0x00, 0xb8, 0xd6, 0x07,
			0x13, 0xc4, 0x84, 0x98,
			0x00, 0x1b, 0x86, 0x8b,
			0x86, 0x73, 0xbf, 0x49,
			0xfe, 0xf1, 0x80, 0x71,
			0x82, 0x72, 0x80, 0xff,
			0x09, 0xc4, 0x84, 0x98,
			0x80, 0x99, 0x82, 0x9a,
			0x86, 0x8b, 0x86, 0x73,
			0xbf, 0x49, 0xfe, 0xf1,
			0x80, 0xff, 0x08, 0xea,
			0x30, 0xd4, 0x10, 0xc0,
			0x12, 0xe8, 0x8a, 0xd3,
			0x00, 0xd8, 0x02, 0xc6,
			0x00, 0xbe, 0xe0, 0x08 };

		rtl_pre_ram_code(tp, 0x8146, 0x7001, true);
		sram_write(tp, 0xb820, 0x0290);
		sram_write(tp, 0xa012, 0x0000);
		sram_write(tp, 0xa014, 0x2c04);
		ocp_write_word(tp, MCU_TYPE_PLA, 0xb438, 0x2c07);
		ocp_write_word(tp, MCU_TYPE_PLA, 0xb438, 0x2c0a);
		ocp_write_word(tp, MCU_TYPE_PLA, 0xb438, 0x2c0d);
		ocp_write_word(tp, MCU_TYPE_PLA, 0xb438, 0xa240);
		ocp_write_word(tp, MCU_TYPE_PLA, 0xb438, 0xa104);
		ocp_write_word(tp, MCU_TYPE_PLA, 0xb438, 0x292d);
		ocp_write_word(tp, MCU_TYPE_PLA, 0xb438, 0x8620);
		ocp_write_word(tp, MCU_TYPE_PLA, 0xb438, 0xa480);
		ocp_write_word(tp, MCU_TYPE_PLA, 0xb438, 0x2a2c);
		ocp_write_word(tp, MCU_TYPE_PLA, 0xb438, 0x8480);
		ocp_write_word(tp, MCU_TYPE_PLA, 0xb438, 0xa101);
		ocp_write_word(tp, MCU_TYPE_PLA, 0xb438, 0x2a36);
		ocp_write_word(tp, MCU_TYPE_PLA, 0xb438, 0xd056);
		ocp_write_word(tp, MCU_TYPE_PLA, 0xb438, 0x2223);
		sram_write(tp, 0xa01a, 0x0000);
		sram_write(tp, 0xa006, 0x0222);
		sram_write(tp, 0xa004, 0x0a35);
		sram_write(tp, 0xa002, 0x0a2b);
		sram_write(tp, 0xa000, 0xf92c);
		sram_write(tp, 0xb820, 0x0210);
		rtl_post_ram_code(tp, 0x8146, true);

		r8153_wdt1_end(tp);

		ocp_data = ocp_read_word(tp, MCU_TYPE_USB, USB_FW_FIX_EN0);
		ocp_data &= ~FW_FIX_SUSPEND;
		ocp_write_word(tp, MCU_TYPE_USB, USB_FW_FIX_EN0, ocp_data);

		rtl_clear_bp(tp, MCU_TYPE_USB);

		generic_ocp_write(tp, 0xf800, 0xff, sizeof(usb_patch_c),
				  usb_patch_c, MCU_TYPE_USB);
		ocp_write_word(tp, MCU_TYPE_USB, 0xfc26, 0xa000);
		ocp_write_word(tp, MCU_TYPE_USB, 0xfc28, 0x3b34);
		ocp_write_word(tp, MCU_TYPE_USB, 0xfc2a, 0x027c);
		ocp_write_word(tp, MCU_TYPE_USB, 0xfc2c, 0x15de);
		ocp_write_word(tp, MCU_TYPE_USB, 0xfc2e, 0x10ce);
		if (ocp_read_byte(tp, MCU_TYPE_USB, USB_CSTMR) & FORCE_SUPER)
			ocp_write_word(tp, MCU_TYPE_USB, 0xfc30, 0x1578);
		else
			ocp_write_word(tp, MCU_TYPE_USB, 0xfc30, 0x1adc);
		ocp_write_word(tp, MCU_TYPE_USB, 0xfc32, 0x3a28);
		ocp_write_word(tp, MCU_TYPE_USB, 0xfc34, 0x05f8);
		ocp_write_word(tp, MCU_TYPE_USB, 0xfc36, 0x05c8);
		ocp_write_word(tp, MCU_TYPE_USB, USB_BP_EN, 0x00ff);

		rtl_clear_bp(tp, MCU_TYPE_PLA);

		generic_ocp_write(tp, 0xf800, 0xff, sizeof(pla_patch_c),
				  pla_patch_c, MCU_TYPE_PLA);
		ocp_write_word(tp, MCU_TYPE_PLA, 0xfc26, 0x8000);
		ocp_write_word(tp, MCU_TYPE_PLA, 0xfc28, 0x1306);
		ocp_write_word(tp, MCU_TYPE_PLA, 0xfc2a, 0x17ca);
		ocp_write_word(tp, MCU_TYPE_PLA, 0xfc2c, 0x171e);
		ocp_write_word(tp, MCU_TYPE_PLA, 0xfc2e, 0x0000);
		ocp_write_word(tp, MCU_TYPE_PLA, 0xfc30, 0x0000);
		ocp_write_word(tp, MCU_TYPE_PLA, 0xfc32, 0x01b4);
		ocp_write_word(tp, MCU_TYPE_PLA, 0xfc34, 0x07d4);
		ocp_write_word(tp, MCU_TYPE_PLA, 0xfc36, 0x0894);
		ocp_write_word(tp, MCU_TYPE_PLA, PLA_BP_EN, 0x00e6);

		/* reset UPHY timer to 36 ms */
		ocp_write_word(tp, MCU_TYPE_PLA, PLA_UPHY_TIMER, 36000 / 16);

		/* enable U3P3 check, set the counter to 4 */
		ocp_write_word(tp, MCU_TYPE_PLA, PLA_EXTRA_STATUS,
			       U3P3_CHECK_EN | 4);

		ocp_data = ocp_read_word(tp, MCU_TYPE_USB, USB_FW_FIX_EN0);
		ocp_data |= FW_FIX_SUSPEND;
		ocp_write_word(tp, MCU_TYPE_USB, USB_FW_FIX_EN0, ocp_data);

		ocp_data = ocp_read_byte(tp, MCU_TYPE_USB, USB_USB2PHY);
		ocp_data |= USB2PHY_L1 | USB2PHY_SUSPEND;
		ocp_write_byte(tp, MCU_TYPE_USB, USB_USB2PHY, ocp_data);

		rtl_reset_ocp_base(tp);
	} else if (tp->version == RTL_VER_06) {
		u32 ocp_data;
		static u8 usb_patch_d[] = {
			0x08, 0xe0, 0x0e, 0xe0,
			0x11, 0xe0, 0x24, 0xe0,
			0x2b, 0xe0, 0x33, 0xe0,
			0x3a, 0xe0, 0x3c, 0xe0,
			0x1e, 0xc3, 0x70, 0x61,
			0x12, 0x48, 0x70, 0x89,
			0x02, 0xc3, 0x00, 0xbb,
			0x02, 0x17, 0x32, 0x19,
			0x02, 0xc3, 0x00, 0xbb,
			0x44, 0x14, 0x30, 0x18,
			0x11, 0xc1, 0x05, 0xe8,
			0x10, 0xc6, 0x02, 0xc2,
			0x00, 0xba, 0x94, 0x17,
			0x02, 0xb4, 0x09, 0xc2,
			0x40, 0x99, 0x0e, 0x48,
			0x42, 0x98, 0x42, 0x70,
			0x8e, 0x49, 0xfe, 0xf1,
			0x02, 0xb0, 0x80, 0xff,
			0xc0, 0xd4, 0xe4, 0x40,
			0x20, 0xd4, 0x30, 0x18,
			0x06, 0xc1, 0xf1, 0xef,
			0xfc, 0xc7, 0x02, 0xc0,
			0x00, 0xb8, 0x38, 0x12,
			0xe4, 0x4b, 0x0c, 0x61,
			0x92, 0x48, 0x93, 0x48,
			0x95, 0x48, 0x96, 0x48,
			0x0c, 0x89, 0x02, 0xc0,
			0x00, 0xb8, 0x0e, 0x06,
			0x30, 0x18, 0xf5, 0xc1,
			0xe0, 0xef, 0x04, 0xc5,
			0x02, 0xc4, 0x00, 0xbc,
			0x76, 0x3c, 0x1e, 0xfc,
			0x02, 0xc6, 0x00, 0xbe,
			0x00, 0x00, 0x02, 0xc6,
			0x00, 0xbe, 0x00, 0x00 };
		static u8 pla_patch_d[] = {
			0x03, 0xe0, 0x16, 0xe0,
			0x30, 0xe0, 0x12, 0xc2,
			0x40, 0x73, 0xb0, 0x49,
			0x08, 0xf0, 0xb8, 0x49,
			0x06, 0xf0, 0xb8, 0x48,
			0x40, 0x9b, 0x0b, 0xc2,
			0x40, 0x76, 0x05, 0xe0,
			0x02, 0x61, 0x02, 0xc3,
			0x00, 0xbb, 0x54, 0x08,
			0x02, 0xc3, 0x00, 0xbb,
			0x64, 0x08, 0x98, 0xd3,
			0x1e, 0xfc, 0xfe, 0xc0,
			0x02, 0x62, 0xa0, 0x48,
			0x02, 0x8a, 0x00, 0x72,
			0xa0, 0x49, 0x11, 0xf0,
			0x13, 0xc1, 0x20, 0x62,
			0x2e, 0x21, 0x2f, 0x25,
			0x00, 0x71, 0x9f, 0x24,
			0x0a, 0x40, 0x09, 0xf0,
			0x00, 0x71, 0x18, 0x48,
			0xa0, 0x49, 0x03, 0xf1,
			0x9f, 0x48, 0x02, 0xe0,
			0x1f, 0x48, 0x00, 0x99,
			0x02, 0xc2, 0x00, 0xba,
			0xac, 0x0c, 0x08, 0xe9,
			0x36, 0xc0, 0x00, 0x61,
			0x9c, 0x20, 0x9c, 0x24,
			0x33, 0xc0, 0x07, 0x11,
			0x05, 0xf1, 0x00, 0x61,
			0x17, 0x48, 0x00, 0x89,
			0x0d, 0xe0, 0x04, 0x11,
			0x0b, 0xf1, 0x00, 0x61,
			0x97, 0x49, 0x08, 0xf0,
			0x97, 0x48, 0x00, 0x89,
			0x23, 0xc0, 0x0e, 0xe8,
			0x12, 0x48, 0x81, 0x1b,
			0x15, 0xe8, 0x1f, 0xc0,
			0x00, 0x61, 0x67, 0x11,
			0x04, 0xf0, 0x02, 0xc0,
			0x00, 0xb8, 0x42, 0x09,
			0x02, 0xc0, 0x00, 0xb8,
			0x90, 0x08, 0x13, 0xc4,
			0x84, 0x98, 0x00, 0x1b,
			0x86, 0x8b, 0x86, 0x73,
			0xbf, 0x49, 0xfe, 0xf1,
			0x80, 0x71, 0x82, 0x72,
			0x80, 0xff, 0x09, 0xc4,
			0x84, 0x98, 0x80, 0x99,
			0x82, 0x9a, 0x86, 0x8b,
			0x86, 0x73, 0xbf, 0x49,
			0xfe, 0xf1, 0x80, 0xff,
			0x08, 0xea, 0x30, 0xd4,
			0x50, 0xe8, 0x8a, 0xd3 };

		rtl_pre_ram_code(tp, 0x8146, 0x7003, true);
		sram_write(tp, 0xb820, 0x0290);
		sram_write(tp, 0xa012, 0x0000);
		sram_write(tp, 0xa014, 0x2c04);
		ocp_write_word(tp, MCU_TYPE_PLA, 0xb438, 0x2c07);
		ocp_write_word(tp, MCU_TYPE_PLA, 0xb438, 0x2c07);
		ocp_write_word(tp, MCU_TYPE_PLA, 0xb438, 0x2c07);
		ocp_write_word(tp, MCU_TYPE_PLA, 0xb438, 0xa240);
		ocp_write_word(tp, MCU_TYPE_PLA, 0xb438, 0xa104);
		ocp_write_word(tp, MCU_TYPE_PLA, 0xb438, 0x2944);
		sram_write(tp, 0xa01a, 0x0000);
		sram_write(tp, 0xa006, 0x0fff);
		sram_write(tp, 0xa004, 0x0fff);
		sram_write(tp, 0xa002, 0x0fff);
		sram_write(tp, 0xa000, 0x1943);
		sram_write(tp, 0xb820, 0x0210);
		rtl_post_ram_code(tp, 0x8146, true);

		rtl_clear_bp(tp, MCU_TYPE_USB);

		generic_ocp_write(tp, 0xf800, 0xff, sizeof(usb_patch_d),
				  usb_patch_d, MCU_TYPE_USB);
		ocp_write_word(tp, MCU_TYPE_USB, 0xfc26, 0xa000);
		ocp_write_word(tp, MCU_TYPE_USB, 0xfc28, 0x16de);
		ocp_write_word(tp, MCU_TYPE_USB, 0xfc2a, 0x1442);
		ocp_write_word(tp, MCU_TYPE_USB, 0xfc2c, 0x1792);
		ocp_write_word(tp, MCU_TYPE_USB, 0xfc2e, 0x1236);
		ocp_write_word(tp, MCU_TYPE_USB, 0xfc30, 0x0606);
		ocp_write_word(tp, MCU_TYPE_USB, 0xfc32, 0x3C74);
		ocp_write_word(tp, MCU_TYPE_USB, 0xfc34, 0x0000);
		ocp_write_word(tp, MCU_TYPE_USB, 0xfc36, 0x0000);
		if (ocp_read_byte(tp, MCU_TYPE_USB, USB_CSTMR) & FORCE_SUPER)
			ocp_write_word(tp, MCU_TYPE_USB, USB_BP_EN, 0x003f);
		else
			ocp_write_word(tp, MCU_TYPE_USB, USB_BP_EN, 0x003e);

		rtl_clear_bp(tp, MCU_TYPE_PLA);

		generic_ocp_write(tp, 0xf800, 0xff, sizeof(pla_patch_d),
				  pla_patch_d, MCU_TYPE_PLA);
		ocp_write_word(tp, MCU_TYPE_PLA, 0xfc26, 0x8000);
		ocp_write_word(tp, MCU_TYPE_PLA, 0xfc28, 0x0852);
		ocp_write_word(tp, MCU_TYPE_PLA, 0xfc2a, 0x0c92);
		ocp_write_word(tp, MCU_TYPE_PLA, 0xfc2c, 0x088c);
		ocp_write_word(tp, MCU_TYPE_PLA, 0xfc2e, 0x0000);
		ocp_write_word(tp, MCU_TYPE_PLA, 0xfc30, 0x0000);
		ocp_write_word(tp, MCU_TYPE_PLA, 0xfc32, 0x0000);
		ocp_write_word(tp, MCU_TYPE_PLA, 0xfc34, 0x0000);
		ocp_write_word(tp, MCU_TYPE_PLA, 0xfc36, 0x0000);
		ocp_write_word(tp, MCU_TYPE_PLA, PLA_BP_EN, 0x0007);

		ocp_data = ocp_read_byte(tp, MCU_TYPE_USB, USB_USB2PHY);
		ocp_data |= USB2PHY_L1 | USB2PHY_SUSPEND;
		ocp_write_byte(tp, MCU_TYPE_USB, USB_USB2PHY, ocp_data);

		ocp_data = ocp_read_word(tp, MCU_TYPE_USB, USB_FW_FIX_EN1);
		ocp_data |= FW_IP_RESET_EN;
		ocp_write_word(tp, MCU_TYPE_USB, USB_FW_FIX_EN1, ocp_data);

		rtl_reset_ocp_base(tp);
	}

	rtl_reset_ocp_base(tp);
}

static void r8153b_firmware(struct r8152 *tp)
{
	if (tp->version == RTL_VER_09) {
		u32 ocp_data;
		static u8 usb_patch2_b[] = {
			0x10, 0xe0, 0x26, 0xe0,
			0x3a, 0xe0, 0x58, 0xe0,
			0x6c, 0xe0, 0x85, 0xe0,
			0xa5, 0xe0, 0xbe, 0xe0,
			0xd8, 0xe0, 0xdb, 0xe0,
			0xf3, 0xe0, 0x05, 0xe1,
			0x0d, 0xe1, 0x6b, 0xe1,
			0x71, 0xe1, 0x92, 0xe1,
			0x16, 0xc0, 0x00, 0x75,
			0xd1, 0x49, 0x0d, 0xf0,
			0x0f, 0xc0, 0x0f, 0xc5,
			0x00, 0x1e, 0x08, 0x9e,
			0x0c, 0x9d, 0x0c, 0xc6,
			0x0a, 0x9e, 0x8f, 0x1c,
			0x0e, 0x8c, 0x0e, 0x74,
			0xcf, 0x49, 0xfe, 0xf1,
			0x02, 0xc0, 0x00, 0xb8,
			0x96, 0x31, 0x00, 0xdc,
			0x24, 0xe4, 0x80, 0x02,
			0x34, 0xd3, 0xff, 0xc3,
			0x60, 0x72, 0xa1, 0x49,
			0x0d, 0xf0, 0xf8, 0xc3,
			0xf8, 0xc2, 0x00, 0x1c,
			0x68, 0x9c, 0xf6, 0xc4,
			0x6a, 0x9c, 0x6c, 0x9a,
			0x8f, 0x1c, 0x6e, 0x8c,
			0x6e, 0x74, 0xcf, 0x49,
			0xfe, 0xf1, 0x04, 0xc0,
			0x02, 0xc2, 0x00, 0xba,
			0xa8, 0x28, 0xf8, 0xc7,
			0xea, 0xc0, 0x00, 0x75,
			0xd1, 0x49, 0x15, 0xf0,
			0x19, 0xc7, 0x17, 0xc2,
			0xec, 0x9a, 0x00, 0x19,
			0xee, 0x89, 0xee, 0x71,
			0x9f, 0x49, 0xfe, 0xf1,
			0xea, 0x71, 0x9f, 0x49,
			0x0a, 0xf0, 0xd9, 0xc2,
			0xec, 0x9a, 0x00, 0x19,
			0xe8, 0x99, 0x81, 0x19,
			0xee, 0x89, 0xee, 0x71,
			0x9f, 0x49, 0xfe, 0xf1,
			0x06, 0xc3, 0x02, 0xc2,
			0x00, 0xba, 0xf0, 0x1d,
			0x4c, 0xe8, 0x00, 0xdc,
			0x00, 0xd4, 0xcb, 0xc0,
			0x00, 0x75, 0xd1, 0x49,
			0x0d, 0xf0, 0xc4, 0xc0,
			0xc4, 0xc5, 0x00, 0x1e,
			0x08, 0x9e, 0xc2, 0xc6,
			0x0a, 0x9e, 0x0c, 0x9d,
			0x8f, 0x1c, 0x0e, 0x8c,
			0x0e, 0x74, 0xcf, 0x49,
			0xfe, 0xf1, 0x04, 0xc0,
			0x02, 0xc1, 0x00, 0xb9,
			0xc4, 0x16, 0x20, 0xd4,
			0xb6, 0xc0, 0x00, 0x75,
			0xd1, 0x48, 0x00, 0x9d,
			0xe5, 0xc7, 0xaf, 0xc2,
			0xec, 0x9a, 0x00, 0x19,
			0xe8, 0x9a, 0x81, 0x19,
			0xee, 0x89, 0xee, 0x71,
			0x9f, 0x49, 0xfe, 0xf1,
			0x2c, 0xc1, 0xec, 0x99,
			0x81, 0x19, 0xee, 0x89,
			0xee, 0x71, 0x9f, 0x49,
			0xfe, 0xf1, 0x04, 0xc3,
			0x02, 0xc2, 0x00, 0xba,
			0x96, 0x1c, 0xc0, 0xd4,
			0xc0, 0x88, 0x1e, 0xc6,
			0xc0, 0x70, 0x8f, 0x49,
			0x0e, 0xf0, 0x8f, 0x48,
			0x93, 0xc6, 0xca, 0x98,
			0x11, 0x18, 0xc8, 0x98,
			0x16, 0xc0, 0xcc, 0x98,
			0x8f, 0x18, 0xce, 0x88,
			0xce, 0x70, 0x8f, 0x49,
			0xfe, 0xf1, 0x0b, 0xe0,
			0x43, 0xc6, 0x00, 0x18,
			0xc8, 0x98, 0x0b, 0xc0,
			0xcc, 0x98, 0x81, 0x18,
			0xce, 0x88, 0xce, 0x70,
			0x8f, 0x49, 0xfe, 0xf1,
			0x02, 0xc0, 0x00, 0xb8,
			0xf2, 0x19, 0x40, 0xd3,
			0x20, 0xe4, 0x33, 0xc2,
			0x40, 0x71, 0x91, 0x48,
			0x40, 0x99, 0x30, 0xc2,
			0x00, 0x19, 0x48, 0x99,
			0xf8, 0xc1, 0x4c, 0x99,
			0x81, 0x19, 0x4e, 0x89,
			0x4e, 0x71, 0x9f, 0x49,
			0xfe, 0xf1, 0x0b, 0xc1,
			0x4c, 0x99, 0x81, 0x19,
			0x4e, 0x89, 0x4e, 0x71,
			0x9f, 0x49, 0xfe, 0xf1,
			0x02, 0x71, 0x02, 0xc2,
			0x00, 0xba, 0x0e, 0x34,
			0x24, 0xe4, 0x19, 0xc2,
			0x40, 0x71, 0x91, 0x48,
			0x40, 0x99, 0x16, 0xc2,
			0x00, 0x19, 0x48, 0x99,
			0xde, 0xc1, 0x4c, 0x99,
			0x81, 0x19, 0x4e, 0x89,
			0x4e, 0x71, 0x9f, 0x49,
			0xfe, 0xf1, 0xf1, 0xc1,
			0x4c, 0x99, 0x81, 0x19,
			0x4e, 0x89, 0x4e, 0x71,
			0x9f, 0x49, 0xfe, 0xf1,
			0x02, 0x71, 0x02, 0xc2,
			0x00, 0xba, 0x60, 0x33,
			0x34, 0xd3, 0x00, 0xdc,
			0x1e, 0x89, 0x02, 0xc0,
			0x00, 0xb8, 0xfa, 0x12,
			0x18, 0xc0, 0x00, 0x65,
			0xd1, 0x49, 0x0d, 0xf0,
			0x11, 0xc0, 0x11, 0xc5,
			0x00, 0x1e, 0x08, 0x9e,
			0x0c, 0x9d, 0x0e, 0xc6,
			0x0a, 0x9e, 0x8f, 0x1c,
			0x0e, 0x8c, 0x0e, 0x74,
			0xcf, 0x49, 0xfe, 0xf1,
			0x04, 0xc0, 0x02, 0xc2,
			0x00, 0xba, 0xa0, 0x41,
			0x06, 0xd4, 0x00, 0xdc,
			0x24, 0xe4, 0x80, 0x02,
			0x34, 0xd3, 0x9e, 0x49,
			0x0a, 0xf0, 0x0f, 0xc2,
			0x40, 0x71, 0x9f, 0x49,
			0x02, 0xf1, 0x08, 0xe0,
			0x0b, 0xc2, 0x40, 0x61,
			0x91, 0x48, 0x40, 0x89,
			0x02, 0xc5, 0x00, 0xbd,
			0x82, 0x24, 0x02, 0xc5,
			0x00, 0xbd, 0xf8, 0x23,
			0xfe, 0xcf, 0x1e, 0xd4,
			0xfe, 0xc7, 0xe0, 0x75,
			0x5f, 0x48, 0xe0, 0x9d,
			0x04, 0xc7, 0x02, 0xc5,
			0x00, 0xbd, 0x82, 0x18,
			0x14, 0xd8, 0xc0, 0x88,
			0x5d, 0xc7, 0x56, 0xc6,
			0xe4, 0x9e, 0x0f, 0x1e,
			0xe6, 0x8e, 0xe6, 0x76,
			0xef, 0x49, 0xfe, 0xf1,
			0xe2, 0x75, 0xe0, 0x74,
			0xd8, 0x25, 0xd8, 0x22,
			0xd8, 0x26, 0x48, 0x23,
			0x68, 0x27, 0x48, 0x26,
			0x04, 0xb4, 0x05, 0xb4,
			0x06, 0xb4, 0x45, 0xc6,
			0xe2, 0x23, 0xfe, 0x39,
			0x00, 0x1c, 0x00, 0x1d,
			0x00, 0x13, 0x0c, 0xf0,
			0xb0, 0x49, 0x04, 0xf1,
			0x01, 0x05, 0xb1, 0x25,
			0xfa, 0xe7, 0xb8, 0x33,
			0x35, 0x43, 0x26, 0x31,
			0x01, 0x05, 0xb1, 0x25,
			0xf4, 0xe7, 0x06, 0xb0,
			0x05, 0xb0, 0xae, 0x41,
			0x25, 0x31, 0x30, 0xc5,
			0x6c, 0x41, 0x04, 0xb0,
			0x05, 0xb4, 0x30, 0xc7,
			0x29, 0xc6, 0x04, 0x06,
			0xe4, 0x9e, 0x0f, 0x1e,
			0xe6, 0x8e, 0xe6, 0x76,
			0xef, 0x49, 0xfe, 0xf1,
			0xe0, 0x76, 0xe8, 0x25,
			0xe8, 0x23, 0xf8, 0x27,
			0x1e, 0xc5, 0x6f, 0x41,
			0x33, 0x23, 0xb3, 0x31,
			0x74, 0x41, 0xf5, 0x31,
			0x19, 0xc6, 0x7e, 0x41,
			0x1a, 0xc6, 0xc4, 0x9f,
			0xf1, 0x21, 0xdf, 0x30,
			0x05, 0xb0, 0xc2, 0x9d,
			0x52, 0x22, 0xa3, 0x31,
			0x0e, 0xc7, 0xb7, 0x31,
			0x0e, 0xc7, 0x77, 0x41,
			0x0e, 0xc7, 0xe6, 0x9e,
			0x0b, 0xc3, 0xde, 0x30,
			0x60, 0x64, 0xe8, 0x8c,
			0x02, 0xc4, 0x00, 0xbc,
			0xe8, 0x19, 0x00, 0xc0,
			0x41, 0x00, 0xff, 0x00,
			0x7f, 0x00, 0x00, 0xe6,
			0x60, 0xd3, 0x08, 0xdc,
			0x40, 0x60, 0x80, 0x48,
			0x81, 0x48, 0x82, 0x48,
			0x02, 0xc1, 0x00, 0xb9,
			0x72, 0x16, 0x1c, 0xc6,
			0xc0, 0x61, 0x04, 0x11,
			0x15, 0xf1, 0x19, 0xc6,
			0xc0, 0x61, 0x9c, 0x20,
			0x9c, 0x24, 0x09, 0x11,
			0x0f, 0xf1, 0x14, 0xc6,
			0x01, 0x19, 0xc0, 0x89,
			0x13, 0xc1, 0x13, 0xc6,
			0x24, 0x9e, 0x00, 0x1e,
			0x26, 0x8e, 0x26, 0x76,
			0xef, 0x49, 0xfe, 0xf1,
			0x22, 0x76, 0x08, 0xc1,
			0x22, 0x9e, 0x07, 0xc6,
			0x02, 0xc1, 0x00, 0xb9,
			0x8c, 0x08, 0x18, 0xb4,
			0x4a, 0xb4, 0x90, 0xcc,
			0x80, 0xd4, 0x08, 0xdc,
			0x10, 0xe8, 0xfc, 0xc6,
			0xc0, 0x67, 0xf0, 0x49,
			0x13, 0xf0, 0xf0, 0x48,
			0xc0, 0x8f, 0xc2, 0x77,
			0xf7, 0xc1, 0xf7, 0xc6,
			0x24, 0x9e, 0x22, 0x9f,
			0x8c, 0x1e, 0x26, 0x8e,
			0x26, 0x76, 0xef, 0x49,
			0xfe, 0xf1, 0xfb, 0x49,
			0x05, 0xf0, 0x07, 0xc6,
			0xc0, 0x61, 0x10, 0x48,
			0xc0, 0x89, 0x02, 0xc6,
			0x00, 0xbe, 0x7e, 0x36,
			0x6c, 0xb4, 0x00, 0x00 };
		static u8 pla_patch2_b[] = {
			0x05, 0xe0, 0x1b, 0xe0,
			0x2c, 0xe0, 0x60, 0xe0,
			0x73, 0xe0, 0x15, 0xc6,
			0xc2, 0x64, 0xd2, 0x49,
			0x06, 0xf1, 0xc4, 0x48,
			0xc5, 0x48, 0xc6, 0x48,
			0xc7, 0x48, 0x05, 0xe0,
			0x44, 0x48, 0x45, 0x48,
			0x46, 0x48, 0x47, 0x48,
			0xc2, 0x8c, 0xc0, 0x64,
			0x46, 0x48, 0xc0, 0x8c,
			0x05, 0xc5, 0x02, 0xc4,
			0x00, 0xbc, 0x18, 0x02,
			0x06, 0xdc, 0xb0, 0xc0,
			0x10, 0xc5, 0xa0, 0x77,
			0xa0, 0x74, 0x46, 0x48,
			0x47, 0x48, 0xa0, 0x9c,
			0x0b, 0xc5, 0xa0, 0x74,
			0x44, 0x48, 0x43, 0x48,
			0xa0, 0x9c, 0x05, 0xc5,
			0xa0, 0x9f, 0x02, 0xc5,
			0x00, 0xbd, 0x3c, 0x03,
			0x1c, 0xe8, 0x20, 0xe8,
			0xd4, 0x49, 0x04, 0xf1,
			0xd5, 0x49, 0x20, 0xf1,
			0x28, 0xe0, 0x2a, 0xc7,
			0xe0, 0x75, 0xda, 0x49,
			0x14, 0xf0, 0x27, 0xc7,
			0xe0, 0x75, 0xdc, 0x49,
			0x10, 0xf1, 0x24, 0xc7,
			0xe0, 0x75, 0x25, 0xc7,
			0xe0, 0x74, 0x2c, 0x40,
			0x0a, 0xfa, 0x1f, 0xc7,
			0xe4, 0x75, 0xd0, 0x49,
			0x09, 0xf1, 0x1c, 0xc5,
			0xe6, 0x9d, 0x11, 0x1d,
			0xe4, 0x8d, 0x04, 0xe0,
			0x16, 0xc7, 0x00, 0x1d,
			0xe4, 0x8d, 0xe0, 0x8e,
			0x11, 0x1d, 0xe0, 0x8d,
			0x07, 0xe0, 0x0c, 0xc7,
			0xe0, 0x75, 0xda, 0x48,
			0xe0, 0x9d, 0x0b, 0xc7,
			0xe4, 0x8e, 0x02, 0xc4,
			0x00, 0xbc, 0x28, 0x03,
			0x02, 0xc4, 0x00, 0xbc,
			0x14, 0x03, 0x12, 0xe8,
			0x4e, 0xe8, 0x1c, 0xe6,
			0x20, 0xe4, 0x80, 0x02,
			0xa4, 0xc0, 0x12, 0xc2,
			0x40, 0x73, 0xb0, 0x49,
			0x08, 0xf0, 0xb8, 0x49,
			0x06, 0xf0, 0xb8, 0x48,
			0x40, 0x9b, 0x0b, 0xc2,
			0x40, 0x76, 0x05, 0xe0,
			0x02, 0x61, 0x02, 0xc3,
			0x00, 0xbb, 0x0a, 0x0a,
			0x02, 0xc3, 0x00, 0xbb,
			0x1a, 0x0a, 0x98, 0xd3,
			0x1e, 0xfc, 0xfe, 0xc0,
			0x02, 0x62, 0xa0, 0x48,
			0x02, 0x8a, 0x00, 0x72,
			0xa0, 0x49, 0x11, 0xf0,
			0x13, 0xc1, 0x20, 0x62,
			0x2e, 0x21, 0x2f, 0x25,
			0x00, 0x71, 0x9f, 0x24,
			0x0a, 0x40, 0x09, 0xf0,
			0x00, 0x71, 0x18, 0x48,
			0xa0, 0x49, 0x03, 0xf1,
			0x9f, 0x48, 0x02, 0xe0,
			0x1f, 0x48, 0x00, 0x99,
			0x02, 0xc2, 0x00, 0xba,
			0xda, 0x0e, 0x08, 0xe9 };

		rtl_clear_bp(tp, MCU_TYPE_USB);

		/* enable fc timer and set timer to 1 second. */
		ocp_write_word(tp, MCU_TYPE_USB, USB_FC_TIMER,
			       CTRL_TIMER_EN | (1000 / 8));

		generic_ocp_write(tp, 0xe600, 0xff, sizeof(usb_patch2_b),
				  usb_patch2_b, MCU_TYPE_USB);

		ocp_write_word(tp, MCU_TYPE_USB, USB_BP_BA, 0xa000);
		ocp_write_word(tp, MCU_TYPE_USB, USB_BP_0, 0x2a20);
		ocp_write_word(tp, MCU_TYPE_USB, USB_BP_1, 0x28a6);
		ocp_write_word(tp, MCU_TYPE_USB, USB_BP_2, 0x1dee);
		ocp_write_word(tp, MCU_TYPE_USB, USB_BP_3, 0x16c2);
		ocp_write_word(tp, MCU_TYPE_USB, USB_BP_4, 0x1c94);
		ocp_write_word(tp, MCU_TYPE_USB, USB_BP_5, 0x19f0);
		ocp_write_word(tp, MCU_TYPE_USB, USB_BP_6, 0x340c);
		ocp_write_word(tp, MCU_TYPE_USB, USB_BP_7, 0x335e);
		ocp_write_word(tp, MCU_TYPE_USB, USB_BP_8, 0x12f8);
		ocp_write_word(tp, MCU_TYPE_USB, USB_BP_9, 0x419e);
		ocp_write_word(tp, MCU_TYPE_USB, USB_BP_10, 0x23f4);
		ocp_write_word(tp, MCU_TYPE_USB, USB_BP_11, 0x186e);
		ocp_write_word(tp, MCU_TYPE_USB, USB_BP_12, 0x19e6);
		ocp_write_word(tp, MCU_TYPE_USB, USB_BP_13, 0x1670);
		ocp_write_word(tp, MCU_TYPE_USB, USB_BP_14, 0x088a);
		ocp_write_word(tp, MCU_TYPE_USB, USB_BP_15, 0x35a8);
		ocp_write_word(tp, MCU_TYPE_USB, USB_BP2_EN, 0xffff);
		ocp_write_byte(tp, MCU_TYPE_USB, 0xcfd7, 0x04);

		rtl_clear_bp(tp, MCU_TYPE_PLA);

		generic_ocp_write(tp, 0xf800, 0xff, sizeof(pla_patch2_b),
				  pla_patch2_b, MCU_TYPE_PLA);

		ocp_write_word(tp, MCU_TYPE_PLA, PLA_BP_BA, 0x8000);
		ocp_write_word(tp, MCU_TYPE_PLA, PLA_BP_0, 0x0216);
		ocp_write_word(tp, MCU_TYPE_PLA, PLA_BP_1, 0x0332);
		ocp_write_word(tp, MCU_TYPE_PLA, PLA_BP_2, 0x030c);
		ocp_write_word(tp, MCU_TYPE_PLA, PLA_BP_3, 0x0a08);
		ocp_write_word(tp, MCU_TYPE_PLA, PLA_BP_4, 0x0ec0);
		ocp_write_word(tp, MCU_TYPE_PLA, PLA_BP_5, 0x0000);
		ocp_write_word(tp, MCU_TYPE_PLA, PLA_BP_6, 0x0000);
		ocp_write_word(tp, MCU_TYPE_PLA, PLA_BP_7, 0x0000);
		ocp_write_word(tp, MCU_TYPE_PLA, PLA_BP_EN, 0x001e);
		ocp_write_byte(tp, MCU_TYPE_USB, 0xcfd6, 0x02);

		if (ocp_read_byte(tp, MCU_TYPE_USB, USB_MISC_1) & BND_MASK) {
			ocp_data = ocp_read_word(tp, MCU_TYPE_PLA, PLA_BP_EN);
			ocp_data |= BIT(0);
			ocp_write_word(tp, MCU_TYPE_PLA, PLA_BP_EN, ocp_data);
		}

		ocp_data = ocp_read_word(tp, MCU_TYPE_USB, USB_FW_CTRL);
		ocp_data |= FLOW_CTRL_PATCH_OPT;
		ocp_write_word(tp, MCU_TYPE_USB, USB_FW_CTRL, ocp_data);

		ocp_data = ocp_read_word(tp, MCU_TYPE_USB, USB_FW_TASK);
		ocp_data |= FC_PATCH_TASK;
		ocp_write_word(tp, MCU_TYPE_USB, USB_FW_TASK, ocp_data);

		ocp_data = ocp_read_word(tp, MCU_TYPE_USB, USB_FW_FIX_EN1);
		ocp_data |= FW_IP_RESET_EN;
		ocp_write_word(tp, MCU_TYPE_USB, USB_FW_FIX_EN1, ocp_data);

		rtl_reset_ocp_base(tp);
	} else if (tp->version == RTL_VER_14) {
		u32 ocp_data;
		static u8 usb_patch3_a[] = {
			0x10, 0xe0, 0x79, 0xe0,
			0x97, 0xe0, 0x99, 0xe0,
			0xa0, 0xe0, 0xa2, 0xe0,
			0xa4, 0xe0, 0xa6, 0xe0,
			0xa8, 0xe0, 0xaa, 0xe0,
			0xac, 0xe0, 0xae, 0xe0,
			0xb0, 0xe0, 0xb2, 0xe0,
			0xb4, 0xe0, 0xb6, 0xe0,
			0x01, 0xb4, 0x03, 0xb4,
			0x04, 0xb4, 0x05, 0xb4,
			0x07, 0xb4, 0x64, 0xc6,
			0xc0, 0x60, 0x82, 0x48,
			0xc0, 0x88, 0x5f, 0xc7,
			0x58, 0xc6, 0xe4, 0x9e,
			0x0f, 0x1e, 0xe6, 0x8e,
			0xe6, 0x76, 0xef, 0x49,
			0xfe, 0xf1, 0xe2, 0x73,
			0xe0, 0x74, 0xb8, 0x22,
			0xd8, 0x26, 0xb8, 0x25,
			0x48, 0x23, 0x68, 0x27,
			0x48, 0x26, 0x04, 0xb4,
			0x05, 0xb4, 0x06, 0xb4,
			0x47, 0xc6, 0xe2, 0x23,
			0xfe, 0x39, 0x00, 0x1c,
			0x00, 0x1d, 0x00, 0x13,
			0x0c, 0xf0, 0xb0, 0x49,
			0x04, 0xf1, 0x01, 0x05,
			0xb1, 0x25, 0xfa, 0xe7,
			0xb8, 0x33, 0x35, 0x43,
			0x26, 0x31, 0x01, 0x05,
			0xb1, 0x25, 0xf4, 0xe7,
			0x06, 0xb0, 0x05, 0xb0,
			0xae, 0x41, 0x25, 0x31,
			0x32, 0xc5, 0x6c, 0x41,
			0x04, 0xb0, 0x05, 0xb4,
			0x32, 0xc7, 0x2b, 0xc6,
			0x04, 0x06, 0xe4, 0x9e,
			0x0f, 0x1e, 0xe6, 0x8e,
			0xe6, 0x76, 0xef, 0x49,
			0xfe, 0xf1, 0xe0, 0x76,
			0xe8, 0x25, 0xe8, 0x23,
			0xf8, 0x27, 0x20, 0xc5,
			0x6f, 0x41, 0xb3, 0x20,
			0x4b, 0x30, 0x4c, 0x41,
			0x4d, 0x30, 0x1b, 0xc6,
			0x4e, 0x41, 0x91, 0x21,
			0xd9, 0x30, 0x05, 0xb0,
			0x52, 0x22, 0xa3, 0x31,
			0x13, 0xc7, 0xb7, 0x31,
			0x13, 0xc7, 0x77, 0x41,
			0x12, 0xc3, 0xde, 0x30,
			0x60, 0x65, 0x10, 0xc7,
			0xe0, 0x8d, 0xe2, 0x9e,
			0x07, 0xb0, 0x05, 0xb0,
			0x04, 0xb0, 0x03, 0xb0,
			0x01, 0xb0, 0x02, 0xc0,
			0x00, 0xb8, 0xd6, 0x20,
			0x00, 0xc0, 0x41, 0x00,
			0xff, 0x00, 0x7f, 0x00,
			0x00, 0xe6, 0x7a, 0xd3,
			0x08, 0xdc, 0xe8, 0xd4,
			0x04, 0xb4, 0x05, 0xb4,
			0x06, 0xb4, 0x1b, 0xc0,
			0x00, 0x75, 0xd8, 0x49,
			0x0d, 0xf0, 0x14, 0xc0,
			0x14, 0xc5, 0x00, 0x1e,
			0x08, 0x9e, 0x0c, 0x9d,
			0x11, 0xc6, 0x0a, 0x9e,
			0x8f, 0x1c, 0x0e, 0x8c,
			0x0e, 0x74, 0xcf, 0x49,
			0xfe, 0xf1, 0x07, 0xc1,
			0x06, 0xb0, 0x05, 0xb0,
			0x04, 0xb0, 0x02, 0xc0,
			0x00, 0xb8, 0xdc, 0x5c,
			0xe0, 0xcb, 0x00, 0xdc,
			0x24, 0xe4, 0x80, 0x02,
			0x34, 0xd3, 0x02, 0xc2,
			0x00, 0xba, 0x42, 0x08,
			0x40, 0x60, 0x80, 0x48,
			0x81, 0x48, 0x82, 0x48,
			0x40, 0x88, 0x02, 0xc2,
			0x00, 0xba, 0xf0, 0x1b,
			0x02, 0xc0, 0x00, 0xb8,
			0x3a, 0x4e, 0x02, 0xc0,
			0x00, 0xb8, 0x3a, 0x4e,
			0x02, 0xc0, 0x00, 0xb8,
			0x3a, 0x4e, 0x02, 0xc0,
			0x00, 0xb8, 0x3a, 0x4e,
			0x02, 0xc0, 0x00, 0xb8,
			0x00, 0x00, 0x02, 0xc0,
			0x00, 0xb8, 0x00, 0x00,
			0x02, 0xc0, 0x00, 0xb8,
			0x00, 0x00, 0x02, 0xc0,
			0x00, 0xb8, 0x00, 0x00,
			0x02, 0xc0, 0x00, 0xb8,
			0x00, 0x00, 0x02, 0xc0,
			0x00, 0xb8, 0x00, 0x00,
			0x02, 0xc0, 0x00, 0xb8,
			0x00, 0x00, 0x02, 0xc0,
			0x00, 0xb8, 0x00, 0x00 };
		static u8 pla_patch3_a[] = {
			0x10, 0xe0, 0x12, 0xe0,
			0x15, 0xe0, 0x1a, 0xe0,
			0x25, 0xe0, 0x31, 0xe0,
			0x33, 0xe0, 0x35, 0xe0,
			0x37, 0xe0, 0x39, 0xe0,
			0x3b, 0xe0, 0x3d, 0xe0,
			0x3f, 0xe0, 0x41, 0xe0,
			0x43, 0xe0, 0x45, 0xe0,
			0x02, 0xc6, 0x00, 0xbe,
			0xec, 0x2c, 0x94, 0x49,
			0x02, 0xc6, 0x00, 0xbe,
			0xae, 0x2b, 0x05, 0xc0,
			0x00, 0x72, 0x02, 0xc6,
			0x00, 0xbe, 0xd6, 0x2b,
			0x20, 0xe8, 0x08, 0xc3,
			0x60, 0x65, 0xd0, 0x49,
			0x06, 0xf1, 0xe0, 0x75,
			0x02, 0xc3, 0x00, 0xbb,
			0x3e, 0x08, 0xb4, 0xd3,
			0x02, 0xc3, 0x00, 0xbb,
			0x5e, 0x08, 0x6c, 0x74,
			0xc4, 0x75, 0xe5, 0x41,
			0xc2, 0x49, 0x05, 0xf0,
			0x07, 0xc6, 0x01, 0x1c,
			0xc0, 0x8c, 0xc1, 0x8c,
			0x02, 0xc4, 0x00, 0xbc,
			0x16, 0x02, 0x99, 0xd3,
			0x02, 0xc0, 0x00, 0xb8,
			0x3a, 0x4e, 0x02, 0xc0,
			0x00, 0xb8, 0x3a, 0x4e,
			0x02, 0xc0, 0x00, 0xb8,
			0x3a, 0x4e, 0x02, 0xc0,
			0x00, 0xb8, 0x00, 0x00,
			0x02, 0xc0, 0x00, 0xb8,
			0x00, 0x00, 0x02, 0xc0,
			0x00, 0xb8, 0x00, 0x00,
			0x02, 0xc0, 0x00, 0xb8,
			0x00, 0x00, 0x02, 0xc0,
			0x00, 0xb8, 0x00, 0x00,
			0x02, 0xc0, 0x00, 0xb8,
			0x00, 0x00, 0x02, 0xc0,
			0x00, 0xb8, 0x00, 0x00,
			0x02, 0xc0, 0x00, 0xb8,
			0x00, 0x00, 0x00, 0x00 };

		rtl_clear_bp(tp, MCU_TYPE_PLA);

		generic_ocp_write(tp, 0xf800, 0xff, sizeof(pla_patch3_a),
				  pla_patch3_a, MCU_TYPE_PLA);

		ocp_write_word(tp, MCU_TYPE_PLA, PLA_BP_BA, 0x8000);
		ocp_write_word(tp, MCU_TYPE_PLA, PLA_BP_0, 0x2be6);
		ocp_write_word(tp, MCU_TYPE_PLA, PLA_BP_1, 0x2bac);
		ocp_write_word(tp, MCU_TYPE_PLA, PLA_BP_2, 0x2bd4);
		ocp_write_word(tp, MCU_TYPE_PLA, PLA_BP_3, 0x083c);
		ocp_write_word(tp, MCU_TYPE_PLA, PLA_BP_4, 0x0214);
		ocp_write_word(tp, MCU_TYPE_PLA, PLA_BP_5, 0x0000);
		ocp_write_word(tp, MCU_TYPE_PLA, PLA_BP_6, 0x0000);
		ocp_write_word(tp, MCU_TYPE_PLA, PLA_BP_7, 0x0000);
		ocp_write_word(tp, MCU_TYPE_PLA, PLA_BP_8, 0x0000);
		ocp_write_word(tp, MCU_TYPE_PLA, PLA_BP_9, 0x0000);
		ocp_write_word(tp, MCU_TYPE_PLA, PLA_BP_10, 0x0000);
		ocp_write_word(tp, MCU_TYPE_PLA, PLA_BP_11, 0x0000);
		ocp_write_word(tp, MCU_TYPE_PLA, PLA_BP_12, 0x0000);
		ocp_write_word(tp, MCU_TYPE_PLA, PLA_BP_13, 0x0000);
		ocp_write_word(tp, MCU_TYPE_PLA, PLA_BP_14, 0x0000);
		ocp_write_word(tp, MCU_TYPE_PLA, PLA_BP_15, 0x0000);
		ocp_write_word(tp, MCU_TYPE_PLA, PLA_BP2_EN, 0x001f);

		ocp_write_byte(tp, MCU_TYPE_USB, 0xcfd6, 0x02);

		rtl_clear_bp(tp, MCU_TYPE_USB);

		/* enable fc timer and set timer to 1 second. */
		ocp_write_word(tp, MCU_TYPE_USB, USB_FC_TIMER,
			       CTRL_TIMER_EN | (1000 / 8));

		generic_ocp_write(tp, 0xe600, 0xff, sizeof(usb_patch3_a),
				  usb_patch3_a, MCU_TYPE_USB);

		ocp_write_word(tp, MCU_TYPE_USB, USB_BP_BA, 0xa000);
		ocp_write_word(tp, MCU_TYPE_USB, USB_BP_0, 0x02ce);
		ocp_write_word(tp, MCU_TYPE_USB, USB_BP_1, 0x5cda);
		ocp_write_word(tp, MCU_TYPE_USB, USB_BP_2, 0x0834);
		ocp_write_word(tp, MCU_TYPE_USB, USB_BP_3, 0x1bec);
		ocp_write_word(tp, MCU_TYPE_USB, USB_BP_4, 0x0000);
		ocp_write_word(tp, MCU_TYPE_USB, USB_BP_5, 0x0000);
		ocp_write_word(tp, MCU_TYPE_USB, USB_BP_6, 0x0000);
		ocp_write_word(tp, MCU_TYPE_USB, USB_BP_7, 0x0000);
		ocp_write_word(tp, MCU_TYPE_USB, USB_BP_8, 0x0000);
		ocp_write_word(tp, MCU_TYPE_USB, USB_BP_9, 0x0000);
		ocp_write_word(tp, MCU_TYPE_USB, USB_BP_10, 0x0000);
		ocp_write_word(tp, MCU_TYPE_USB, USB_BP_11, 0x0000);
		ocp_write_word(tp, MCU_TYPE_USB, USB_BP_12, 0x0000);
		ocp_write_word(tp, MCU_TYPE_USB, USB_BP_13, 0x0000);
		ocp_write_word(tp, MCU_TYPE_USB, USB_BP_14, 0x0000);
		ocp_write_word(tp, MCU_TYPE_USB, USB_BP_15, 0x0000);
		ocp_write_word(tp, MCU_TYPE_USB, USB_BP2_EN, 0x000f);

		ocp_write_byte(tp, MCU_TYPE_USB, 0xcfd7, 0x02);

		ocp_data = ocp_read_word(tp, MCU_TYPE_USB, USB_FW_CTRL);
		ocp_data |= FLOW_CTRL_PATCH_2;
		ocp_write_word(tp, MCU_TYPE_USB, USB_FW_CTRL, ocp_data);

		ocp_data = ocp_read_word(tp, MCU_TYPE_USB, USB_FW_TASK);
		ocp_data |= FC_PATCH_TASK;
		ocp_write_word(tp, MCU_TYPE_USB, USB_FW_TASK, ocp_data);

		rtl_reset_ocp_base(tp);
	}

	rtl_reset_ocp_base(tp);
}

static void r8156_firmware(struct r8152 *tp)
{
	if (tp->version == RTL_TEST_01) {
		static u8 usb3_patch_t[] = {
			0x01, 0xe0, 0x05, 0xc7,
			0xf6, 0x65, 0x02, 0xc0,
			0x00, 0xb8, 0x40, 0x03,
			0x00, 0xd4, 0x00, 0x00 };
		u16 data;

		rtl_reset_ocp_base(tp);

		ocp_reg_write(tp, 0xb87c, 0x8099);
		ocp_reg_write(tp, 0xb87e, 0x2a50);
		ocp_reg_write(tp, 0xb87c, 0x80a1);
		ocp_reg_write(tp, 0xb87e, 0x2a50);
		ocp_reg_write(tp, 0xb87c, 0x809a);
		ocp_reg_write(tp, 0xb87e, 0x5010);
		ocp_reg_write(tp, 0xb87c, 0x80a2);
		ocp_reg_write(tp, 0xb87e, 0x500f);
		ocp_reg_write(tp, 0xb87c, 0x8087);
		ocp_reg_write(tp, 0xb87e, 0xc0cf);
		ocp_reg_write(tp, 0xb87c, 0x8080);
		ocp_reg_write(tp, 0xb87e, 0x0f16);
		ocp_reg_write(tp, 0xb87c, 0x8089);
		ocp_reg_write(tp, 0xb87e, 0x161b);
		ocp_reg_write(tp, 0xb87c, 0x808a);
		ocp_reg_write(tp, 0xb87e, 0x1b1f);

		ocp_reg_write(tp, 0xac36, 0x0080);
		ocp_reg_write(tp, 0xac4a, 0xff00);
		data = ocp_reg_read(tp, 0xac34);
		data &= ~BIT(4);
		data |= BIT(2) | BIT(3);
		ocp_reg_write(tp, 0xac34, data);

		data = ocp_reg_read(tp, 0xac54);
		data &= ~(BIT(9) | BIT(10));
		ocp_reg_write(tp, 0xac54, data);
		ocp_reg_write(tp, 0xb87c, 0x8099);
		ocp_reg_write(tp, 0xb87e, 0x2050);
		ocp_reg_write(tp, 0xb87c, 0x80a1);
		ocp_reg_write(tp, 0xb87e, 0x2050);
		ocp_reg_write(tp, 0xb87c, 0x809a);
		ocp_reg_write(tp, 0xb87e, 0x5010);
		ocp_reg_write(tp, 0xb87c, 0x80a2);
		ocp_reg_write(tp, 0xb87e, 0x500f);
		data = ocp_reg_read(tp, 0xac34);
		data &= ~BIT(5);
		data |= BIT(6) | BIT(7);
		ocp_reg_write(tp, 0xac34, data);

		if (rtl_phy_patch_request(tp, true, true)) {
			netif_err(tp, drv, tp->netdev,
				  "patch request error\n");
			return;
		}

		data = ocp_reg_read(tp, 0xb896);
		data &= ~BIT(0);
		ocp_reg_write(tp, 0xb896, data);
		ocp_reg_write(tp, 0xb892, 0x0000);
		ocp_reg_write(tp, 0xb88e, 0xc089);
		ocp_reg_write(tp, 0xb890, 0xc1d0);
		ocp_reg_write(tp, 0xb88e, 0xc08a);
		ocp_reg_write(tp, 0xb890, 0xe0f0);
		ocp_reg_write(tp, 0xb88e, 0xc08b);
		ocp_reg_write(tp, 0xb890, 0xe0f0);
		ocp_reg_write(tp, 0xb88e, 0xc08c);
		ocp_reg_write(tp, 0xb890, 0xffff);
		ocp_reg_write(tp, 0xb88e, 0xc08d);
		ocp_reg_write(tp, 0xb890, 0xffff);
		ocp_reg_write(tp, 0xb88e, 0xc08e);
		ocp_reg_write(tp, 0xb890, 0xffff);
		ocp_reg_write(tp, 0xb88e, 0xc08f);
		ocp_reg_write(tp, 0xb890, 0xffff);
		ocp_reg_write(tp, 0xb88e, 0xc090);
		ocp_reg_write(tp, 0xb890, 0xff12);

		ocp_reg_write(tp, 0xb88e, 0xc09a);
		ocp_reg_write(tp, 0xb890, 0x191a);
		ocp_reg_write(tp, 0xb88e, 0xc09b);
		ocp_reg_write(tp, 0xb890, 0x191a);
		ocp_reg_write(tp, 0xb88e, 0xc09e);
		ocp_reg_write(tp, 0xb890, 0x1d1e);
		ocp_reg_write(tp, 0xb88e, 0xc09f);
		ocp_reg_write(tp, 0xb890, 0x1d1e);
		ocp_reg_write(tp, 0xb88e, 0xc0a0);
		ocp_reg_write(tp, 0xb890, 0x1f20);
		ocp_reg_write(tp, 0xb88e, 0xc0a1);
		ocp_reg_write(tp, 0xb890, 0x1f20);
		ocp_reg_write(tp, 0xb88e, 0xc0a2);
		ocp_reg_write(tp, 0xb890, 0x2122);
		ocp_reg_write(tp, 0xb88e, 0xc0a3);
		ocp_reg_write(tp, 0xb890, 0x2122);
		ocp_reg_write(tp, 0xb88e, 0xc0a4);
		ocp_reg_write(tp, 0xb890, 0x2324);
		ocp_reg_write(tp, 0xb88e, 0xc0a5);
		ocp_reg_write(tp, 0xb890, 0x2324);

		ocp_reg_write(tp, 0xb88e, 0xc029);
		ocp_reg_write(tp, 0xb890, 0xdff3);
		ocp_reg_write(tp, 0xb88e, 0xc02a);
		ocp_reg_write(tp, 0xb890, 0xf3f3);
		ocp_reg_write(tp, 0xb88e, 0xc02b);
		ocp_reg_write(tp, 0xb890, 0xf3f3);
		ocp_reg_write(tp, 0xb88e, 0xc02c);
		ocp_reg_write(tp, 0xb890, 0xf3ef);
		ocp_reg_write(tp, 0xb88e, 0xc02d);
		ocp_reg_write(tp, 0xb890, 0xf3ef);
		ocp_reg_write(tp, 0xb88e, 0xc02e);
		ocp_reg_write(tp, 0xb890, 0xebe7);
		ocp_reg_write(tp, 0xb88e, 0xc02f);
		ocp_reg_write(tp, 0xb890, 0xebe7);
		ocp_reg_write(tp, 0xb88e, 0xc030);
		ocp_reg_write(tp, 0xb890, 0xe4e2);
		ocp_reg_write(tp, 0xb88e, 0xc031);
		ocp_reg_write(tp, 0xb890, 0xe4e2);
		ocp_reg_write(tp, 0xb88e, 0xc032);
		ocp_reg_write(tp, 0xb890, 0xdfdf);
		ocp_reg_write(tp, 0xb88e, 0xc033);
		ocp_reg_write(tp, 0xb890, 0xdfdf);
		ocp_reg_write(tp, 0xb88e, 0xc034);
		ocp_reg_write(tp, 0xb890, 0xdfdf);
		ocp_reg_write(tp, 0xb88e, 0xc035);
		ocp_reg_write(tp, 0xb890, 0xdfdf);
		ocp_reg_write(tp, 0xb88e, 0xc036);
		ocp_reg_write(tp, 0xb890, 0xdfdf);
		ocp_reg_write(tp, 0xb88e, 0xc037);
		ocp_reg_write(tp, 0xb890, 0xdfdf);
		ocp_reg_write(tp, 0xb88e, 0xc038);
		ocp_reg_write(tp, 0xb890, 0xdfdf);
		ocp_reg_write(tp, 0xb88e, 0xc039);
		ocp_reg_write(tp, 0xb890, 0xdfdf);
		ocp_reg_write(tp, 0xb88e, 0xc03a);
		ocp_reg_write(tp, 0xb890, 0xdfdf);
		ocp_reg_write(tp, 0xb88e, 0xc03b);
		ocp_reg_write(tp, 0xb890, 0xdfdf);
		ocp_reg_write(tp, 0xb88e, 0xc03c);
		ocp_reg_write(tp, 0xb890, 0xdf00);

		data = ocp_reg_read(tp, 0xb896);
		data |= BIT(0);
		ocp_reg_write(tp, 0xb896, data);

		rtl_patch_key_set(tp, 0x8024, 0x0000);
		sram_write(tp, SRAM_PHY_LOCK, PHY_PATCH_LOCK);

		data = ocp_reg_read(tp, OCP_PHY_PATCH_CMD);
		data |= BIT(7);
		ocp_reg_write(tp, OCP_PHY_PATCH_CMD, data);

		/* nc0_patch_171220_loop_test_USB */
		sram_write(tp, 0xA016, 0x0000);
		sram_write(tp, 0xA012, 0x0000);
		ocp_reg_write(tp, OCP_SRAM_ADDR, 0xA014);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8010);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8027);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x802e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8035);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x806d);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8077);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x808c);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8091);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x12ad);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd708);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x3709);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8017);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x3bdd);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x801f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xc100);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x38c0);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1034);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x4061);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xb902);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa501);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x37b8);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1034);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x12ad);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd71e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5fa6);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x12ad);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1044);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x12ad);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd708);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x3b0f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1032);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x12ed);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x12ad);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd708);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x2109);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1032);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x12e5);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd501);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xce01);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa130);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd010);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd1a2);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd700);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x401a);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa140);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd020);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd1a1);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x401a);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8120);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa8c0);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd020);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd1a1);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x401a);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8140);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd093);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd1a5);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x401a);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa63f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd010);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd1a2);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x401a);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa73f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd09e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd1a2);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x401a);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa180);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xce00);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd0dc);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd1a5);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x401a);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd502);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa401);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd03b);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd1c4);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd704);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x401c);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x617d);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd502);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8401);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd503);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xcdc7);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xaf01);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd500);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd704);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x4013);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0f7a);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd502);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8401);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8280);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd500);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0f7a);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd504);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8208);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd500);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xcc08);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x08ba);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x08c6);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0ee6);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x068b);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0e9d);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd719);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x34a1);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0da2);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd704);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5f1c);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd75e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x3ffd);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0dca);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd707);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5e67);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd719);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x2f79);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0dc0);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd75e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x2a51);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0db6);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xffec);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa540);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1308);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x159e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xc445);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xdb02);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0c28);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0608);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0c47);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0542);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd00a);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x408d);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd075);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x6045);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd05d);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd1a4);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd07a);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd1b5);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0771);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x3b4d);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x809f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x2635);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0241);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x2745);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0241);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x27d0);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x80aa);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5ec8);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xc446);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xdb04);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa602);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd064);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd1a1);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd018);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd1b0);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x068b);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd701);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0753);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x407b);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0771);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x2745);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0241);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x61da);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x608a);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x6306);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x80c5);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5e28);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x2730);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x80b1);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x80c5);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0771);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8103);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xc447);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xdb08);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x406d);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0c07);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0501);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd056);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd1c2);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x3ce1);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x01ae);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x2734);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x80c5);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x7f8a);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0c07);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0501);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd04e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd1b2);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd0a8);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd1a7);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xdb08);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xc447);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x26d7);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8103);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x648a);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5fbb);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0ca0);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0320);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd501);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x80f0);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xce01);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa208);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xce00);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xc317);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd500);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x2c51);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8103);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xdb10);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xc448);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa620);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8710);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x41dd);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd502);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa306);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x415f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa210);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0c1f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0004);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa330);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd501);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xc575);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8210);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd502);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8320);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa301);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd500);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x2c59);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8103);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x3a33);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x80ff);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd502);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8301);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd098);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd191);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x609f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8306);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8110);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa320);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd501);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa210);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd006);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd1e3);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd501);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xc30f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x4093);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xc033);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x02fb);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa0f0);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xce01);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8208);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xce00);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x02fb);
		sram_write(tp, 0xA026, 0x0279);
		sram_write(tp, 0xA024, 0x159c);
		sram_write(tp, 0xA022, 0x0d94);
		sram_write(tp, 0xA020, 0x0ee1);
		sram_write(tp, 0xA006, 0x0f46);
		sram_write(tp, 0xA004, 0x12e2);
		sram_write(tp, 0xA002, 0x12ea);
		sram_write(tp, 0xA000, 0x1034);
		sram_write(tp, 0xA008, 0xff00);

		/* nc2_patch_171109_USB */
		sram_write(tp, 0xA016, 0x0020);
		sram_write(tp, 0xA012, 0x0000);
		ocp_reg_write(tp, OCP_SRAM_ADDR, 0xA014);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8010);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8014);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8018);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8024);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8056);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8062);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8069);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8080);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa404);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8708);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0390);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd37a);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd21a);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0508);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8301);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd164);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd04d);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0441);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd700);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5fb4);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xcf0c);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0437);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x010c);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xcb60);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd71f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x61ee);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd71f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x210c);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x001a);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd700);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5f57);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xbb80);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd700);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x605f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x9b80);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8301);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd1c3);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd074);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa301);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xfff1);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xcb62);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xb910);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd71f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x7fae);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x9930);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xcb80);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8190);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x82a0);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x800a);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8406);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa780);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd141);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd040);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0441);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd700);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5fb4);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xcb82);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8701);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa70c);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa190);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa2b4);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa00a);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa404);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd700);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x6041);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa402);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0441);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd700);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5fa7);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x02ed);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8301);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd164);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd04d);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0441);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd700);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5fb4);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0450);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xb401);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0236);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xb808);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xbb80);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa301);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd1c3);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd074);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x03f3);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xcb17);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0441);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8ec0);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0426);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xae40);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0426);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0cc0);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0e80);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0426);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xaec0);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0426);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd700);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x34a0);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x012c);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd701);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5d8e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0134);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xcb23);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0441);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8ec0);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0426);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xae40);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0426);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0cc0);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0e80);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0426);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xaec0);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0426);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd701);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5dee);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0249);
		sram_write(tp, 0xA10E, 0x0239);
		sram_write(tp, 0xA10C, 0x0119);
		sram_write(tp, 0xA10A, 0x03f2);
		sram_write(tp, 0xA108, 0x0231);
		sram_write(tp, 0xA106, 0x0413);
		sram_write(tp, 0xA104, 0x0108);
		sram_write(tp, 0xA102, 0x0506);
		sram_write(tp, 0xA100, 0x038e);
		sram_write(tp, 0xA110, 0x00ff);

		/* uc2_patch_171006_calc_txcrc_reg_write_seq_USB */
		sram_write(tp, 0xb87c, 0x82c1);
		sram_write(tp, 0xb87e, 0xaf82);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xcdaf);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x82d6);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xaf82);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd9af);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x82dc);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0282);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xdc02);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x830c);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xaf03);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd7af);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0eea);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xaf0f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xe4f8);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xfaef);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x69e0);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8169);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xac23);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1ee0);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x815d);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xad23);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1bf7);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0ee0);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xffcf);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xad26);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xfa02);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0b99);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0283);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x3cf6);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0ee0);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xffcf);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xac26);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xfaae);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0302);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0d70);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xef96);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xfefc);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x04f8);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xfaef);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x69e0);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8169);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xac24);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1ee0);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x815d);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xad24);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1bf7);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0ee0);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xffcf);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xad26);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xfa02);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8349);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0283);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x3cf6);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0ee0);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xffcf);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xac26);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xfaae);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0302);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x861d);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xef96);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xfefc);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x04f8);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xf70f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xe0ff);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xcfad);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x27fa);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xf60f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xfc04);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xf8f9);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xfaef);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x69e0);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x81a3);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0502);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8375);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xae16);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa001);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0502);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x83aa);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xae0e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa002);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0502);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x848f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xae06);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa003);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0302);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x857e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xef96);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xfefd);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xfc04);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xf8f9);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xfaef);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x69e1);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8010);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xad2b);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x16ee);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x81a4);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x00ee);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x81a5);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x00ee);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x81a6);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x01ee);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x81a7);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x01ee);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x81a3);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x01ae);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0ee1);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x815d);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xf62c);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xe581);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5dbf);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8663);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0243);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5cef);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x96fe);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xfdfc);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x04f8);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xf9fa);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xef69);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xe281);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa6e3);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x81a7);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xef13);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x3905);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xac2f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1da2);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0417);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0285);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xf0e1);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x815d);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xf62c);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xe581);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5dbf);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8663);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0243);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5cee);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x81a3);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x00ae);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x4412);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd301);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0284);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x20e6);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x81a6);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xe781);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa75d);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0303);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xef12);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0c12);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1e13);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xe281);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa4e3);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x81a5);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5d03);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x030c);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x260c);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x341e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x121e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x13bf);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8666);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x023e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xe8d1);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x09bf);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8669);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x023e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xe8bf);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x866c);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0243);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5cbf);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8675);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0243);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5cee);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x81a3);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x02ef);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x96fe);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xfdfc);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x04f8);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xf9fa);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xef69);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa201);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0abf);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x867b);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x023f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x2cef);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x64ae);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x22a2);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x020a);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xbf86);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x7e02);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x3f2c);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xef64);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xae15);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa203);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0abf);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8681);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x023f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x2cef);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x64ae);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x08bf);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8684);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x023f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x2cef);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x6483);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0c64);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0c32);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1a63);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xbf81);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa81a);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x961f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x66ef);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x563d);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0004);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xad37);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1fd9);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xef79);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xbf86);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x6602);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x3ee8);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xef16);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x290a);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xbf86);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x6902);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x3ee8);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xbf86);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x6c02);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x435c);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xef97);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1916);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xaed9);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xef96);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xfefd);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xfc04);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xf8f9);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xfaef);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x69bf);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8678);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x023f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x2cad);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x2879);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd103);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xbf86);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x7202);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x3ee8);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xbf86);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x6f02);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x3f2c);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa094);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x62e2);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x81a6);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xe381);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa7d1);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x04bf);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8672);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x023e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xe8bf);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x866f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x023f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x2cef);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x100d);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x121f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1259);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x03a1);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0043);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xef10);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1f13);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5903);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa100);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x3a02);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x851c);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xe681);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa4e7);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x81a5);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5d03);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x03ef);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x120c);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x121e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x130c);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x121e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x120c);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x121e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x13bf);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8666);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x023e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xe8d1);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x09bf);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8669);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x023e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xe8bf);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x866c);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0243);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5cbf);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8675);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0243);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5cee);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x81a3);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x03ae);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x06bf);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8675);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0243);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5cef);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x96fe);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xfdfc);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x04f8);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xf9fa);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xef69);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1f66);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8283);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0c32);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xef12);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xbf86);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8702);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x3ee8);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xef46);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x3c00);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x02ad);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x2741);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xef46);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x2c00);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x05bf);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8672);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x023e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xe8bf);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x866f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x023f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x2cbf);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x868a);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x023e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xe8ef);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x13bf);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x868d);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x023e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xe8bf);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8690);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0243);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5cef);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x10bf);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x868a);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x023e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xe8ef);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1311);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xbf86);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8d02);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x3ee8);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xbf86);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x9002);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x435c);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x2b02);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x16ae);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xb7ef);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x96fe);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xfdfc);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x04f8);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xf9fa);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xef69);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xbf86);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x7802);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x3f2c);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xad28);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5ee2);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x81a6);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xe381);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa7d1);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x03bf);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8672);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x023e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xe8bf);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x866f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x023f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x2cef);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1259);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x03a1);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0014);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xef13);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5903);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa100);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0da0);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x900a);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x13e7);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x81a7);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xee81);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa301);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xae2f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa094);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x26d1);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x04bf);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8672);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x023e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xe8bf);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x866f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x023f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x2cef);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x100d);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x161f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1259);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x03a1);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x000d);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xef10);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0d14);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1f13);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5903);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa100);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x02ae);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xcdbf);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8675);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0243);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5cef);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x96fe);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xfdfc);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x04f8);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xf9fa);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xef69);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd209);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd100);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xbf86);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x6602);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x3ee8);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xef32);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x3b0e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xad3f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x11ef);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x12bf);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8669);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x023e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xe8bf);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x866c);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0243);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5c12);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xaee8);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xef96);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xfefd);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xfc04);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xf8f9);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xfaef);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x69e1);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8010);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xad2b);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0602);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x85f0);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0286);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x44e1);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8169);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xf62c);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xe581);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x69e1);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x815d);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xf62c);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xe581);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5def);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x96fe);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xfdfc);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x04f8);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xf9fa);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xef69);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xee81);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa400);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xee81);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa500);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xee81);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa601);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xee81);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa701);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xee81);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa300);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xef96);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xfefd);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xfc04);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x44a6);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xe070);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xb468);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xdab4);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x68ff);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xb468);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xf0b6);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x3a20);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xb638);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xeeb6);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x38ff);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xb638);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x10b5);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0032);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xb500);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x54b5);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0076);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xb500);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x10b4);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x4e70);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xb450);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x52b4);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x4e66);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xb44e);
		sram_write(tp, 0xb85e, 0x03d1);
		sram_write(tp, 0xb860, 0x0ee4);
		sram_write(tp, 0xb862, 0x0fde);
		sram_write(tp, 0xb864, 0xffff);
		sram_write(tp, 0xb878, 0x0001);

		data = ocp_reg_read(tp, OCP_PHY_PATCH_CMD);
		data &= ~BIT(7);
		ocp_reg_write(tp, OCP_PHY_PATCH_CMD, data);

		/* uc_patch_171212_customer_USB */
		sram_write(tp, 0x8586, 0xaf85);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x92af);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8598);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xaf85);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa1af);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x85a1);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0285);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa1af);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0414);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0286);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x7e02);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1273);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xaf10);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1cf8);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xf9e3);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x83ab);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xe0a6);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x00e1);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa601);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xef01);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0d04);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x580f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa008);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x4659);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0f9e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x4239);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0aab);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x3ee0);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xffcf);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xad26);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x07f7);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0ead);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x2729);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xae02);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xf60e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xe283);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xab1f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x239f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x28e0);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xb714);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xe1b7);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x155c);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0c00);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x9fee);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0285);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xfee0);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xffcf);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xad26);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0af7);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0fe0);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xffcf);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xac27);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xfaf6);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0fe2);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x83ab);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1f23);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x9f03);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xaf85);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa6fd);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xfc04);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xf8f9);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xfb02);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x866d);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1f77);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xe0b7);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x2ee1);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xb72f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0286);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x4ce0);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xb72c);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xe1b7);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x2d02);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x864c);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xe0b7);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x2ae1);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xb72b);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0286);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x4ce0);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xb728);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xe1b7);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x2902);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x864c);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xe0b7);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x26e1);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xb727);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0286);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x4cef);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x47d2);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xb8e6);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xb468);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xe5b4);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x69d2);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xbce6);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xb468);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xe4b4);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x6902);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x866d);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xfffd);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xfc04);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xf8f9);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xfad2);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x00ef);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x675e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0001);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1f46);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0d71);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5f7f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xffad);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x2803);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x7fa0);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x010d);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x4112);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa210);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xe8fe);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xfdfc);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x04f8);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xe0b4);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x62e1);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xb463);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x6901);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xe4b4);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x62e5);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xb463);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xfc04);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xf8f9);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xfaef);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x69e1);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8016);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xad2d);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x3bbf);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x86fd);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x023f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x08ac);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x2832);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xbf87);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0002);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x3f08);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xad28);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x29d2);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x03bf);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8703);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x023f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x080d);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x11f6);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x2fef);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x31e0);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8ff3);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0d01);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xf627);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1b03);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xaa01);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x82e0);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8ff2);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0d01);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xf627);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1b03);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xaa01);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8202);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x86ca);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xef69);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xfefd);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xfc04);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xfbfa);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xef69);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xf9f8);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xbf8f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xf4e1);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8fed);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1c21);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1a92);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xe08f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xeee1);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8fef);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xef74);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xe08f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xf0e1);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8ff1);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xef64);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0217);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x70fc);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xfdef);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x96fe);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xff04);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x2087);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0620);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8709);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0087);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0cbb);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa880);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xeea8);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8070);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa880);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x60a8);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x18e8);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa818);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x60a8);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1a00);
		sram_write(tp, 0xb818, 0x040e);
		sram_write(tp, 0xb81a, 0x1019);
		sram_write(tp, 0xb81c, 0xffff);
		sram_write(tp, 0xb81e, 0xffff);
		sram_write(tp, 0xb832, 0x0003);

		rtl_patch_key_set(tp, 0x8024, 0x0000);
		ocp_reg_write(tp, 0xc414, 0x0200);

		rtl_phy_patch_request(tp, false, true);

		r8156_lock_main(tp, true);

		sram_write(tp, 0x80c9, 0x3478);
		sram_write(tp, 0x80d0, 0xfe8f);
		sram_write(tp, 0x80ca, 0x7843);
		sram_write(tp, 0x80cb, 0x43b0);
		sram_write(tp, 0x80cb, 0x4380);
		sram_write(tp, 0x80cc, 0xb00b);
		sram_write(tp, 0x80cd, 0x0ba1);
		sram_write(tp, 0x80d8, 0x1078);
		sram_write(tp, 0x8016, 0x3f00);
		sram_write(tp, 0x8fed, 0x0386);
		sram_write(tp, 0x8fee, 0x86f4);
		sram_write(tp, 0x8fef, 0xf486);
		sram_write(tp, 0x8ff0, 0x86fd);
		sram_write(tp, 0x8ff1, 0xfd28);
		sram_write(tp, 0x8ff2, 0x285a);
		sram_write(tp, 0x8ff3, 0x5a70);
		sram_write(tp, 0x8ff4, 0x7000);
		sram_write(tp, 0x8ff5, 0x005d);
		sram_write(tp, 0x8ff6, 0x5d77);
		sram_write(tp, 0x8ff7, 0x7778);
		sram_write(tp, 0x8ff8, 0x785f);
		sram_write(tp, 0x8ff9, 0x5f74);
		sram_write(tp, 0x8ffa, 0x7478);
		sram_write(tp, 0x8ffb, 0x7858);
		sram_write(tp, 0x8ffc, 0x5870);
		sram_write(tp, 0x8ffd, 0x7078);
		sram_write(tp, 0x8ffe, 0x7850);
		sram_write(tp, 0x8fff, 0x5000);
		sram_write(tp, 0x80dd, 0x34a4);
		sram_write(tp, 0x80e4, 0xfe7f);
		sram_write(tp, 0x80e6, 0x4a19);
		sram_write(tp, 0x80de, 0xa443);
		sram_write(tp, 0x80df, 0x43a0);
		sram_write(tp, 0x80df, 0x43a0);
		sram_write(tp, 0x80e0, 0xa00a);
		sram_write(tp, 0x80e1, 0x0a00);
		sram_write(tp, 0x80e8, 0x700c);
		sram_write(tp, 0x80e2, 0x0007);
		sram_write(tp, 0x80e3, 0x07fe);
		sram_write(tp, 0x80ec, 0x0e78);
		sram_write(tp, 0x80b5, 0x42f7);
		sram_write(tp, 0x80bc, 0xfaa4);
		sram_write(tp, 0x80bf, 0x1f80);
		sram_write(tp, 0x80be, 0xff1f);
		sram_write(tp, 0x80b7, 0x4280);
		sram_write(tp, 0x80b6, 0xf742);
		sram_write(tp, 0x80b8, 0x800f);
		sram_write(tp, 0x80b9, 0x0fab);
		sram_write(tp, 0x80c1, 0x1e0a);
		sram_write(tp, 0x80c0, 0x801e);
		sram_write(tp, 0x80bd, 0xa4ff);
		sram_write(tp, 0x80bb, 0x0bfa);
		sram_write(tp, 0x80ba, 0xab0b);
		ocp_reg_write(tp, OCP_SRAM_ADDR, 0x818d);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x003d);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x009b);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x00cb);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x00e5);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x00f2);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x00f9);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x00fd);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x00ff);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x00c2);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0065);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0034);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x001b);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x000e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0007);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0003);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0002);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0001);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0000);
		sram_write(tp, 0x8163, 0xdb06);
		sram_write(tp, 0x816a, 0xdb06);
		sram_write(tp, 0x8171, 0xdb06);

		r8156_lock_main(tp, false);

		rtl_clear_bp(tp, MCU_TYPE_USB);

		generic_ocp_write(tp, 0xe600, 0xff, sizeof(usb3_patch_t),
				  usb3_patch_t, MCU_TYPE_USB);

		ocp_write_word(tp, MCU_TYPE_USB, USB_BP_BA, 0xa000);
		ocp_write_word(tp, MCU_TYPE_USB, USB_BP_0, 0x033e);
//		ocp_write_word(tp, MCU_TYPE_USB, USB_BP_1, 0x0000);
//		ocp_write_word(tp, MCU_TYPE_USB, USB_BP_2, 0x0000);
//		ocp_write_word(tp, MCU_TYPE_USB, USB_BP_3, 0x0000);
//		ocp_write_word(tp, MCU_TYPE_USB, USB_BP_4, 0x0000);
//		ocp_write_word(tp, MCU_TYPE_USB, USB_BP_5, 0x0000);
//		ocp_write_word(tp, MCU_TYPE_USB, USB_BP_6, 0x0000);
//		ocp_write_word(tp, MCU_TYPE_USB, USB_BP_7, 0x0000);
//		ocp_write_word(tp, MCU_TYPE_USB, USB_BP_8, 0x0000);
//		ocp_write_word(tp, MCU_TYPE_USB, USB_BP_9, 0x0000);
//		ocp_write_word(tp, MCU_TYPE_USB, USB_BP_10, 0x0000);
//		ocp_write_word(tp, MCU_TYPE_USB, USB_BP_11, 0x0000);
//		ocp_write_word(tp, MCU_TYPE_USB, USB_BP_12, 0x0000);
//		ocp_write_word(tp, MCU_TYPE_USB, USB_BP_13, 0x0000);
//		ocp_write_word(tp, MCU_TYPE_USB, USB_BP_14, 0x0000);
//		ocp_write_word(tp, MCU_TYPE_USB, USB_BP_15, 0x0000);
		ocp_write_word(tp, MCU_TYPE_USB, USB_BP2_EN, 0x0001);
	}

	rtl_reset_ocp_base(tp);
}

static void r8153_aldps_en(struct r8152 *tp, bool enable)
{
	u16 data;

	data = ocp_reg_read(tp, OCP_POWER_CFG);
	if (enable) {
		data |= EN_ALDPS;
		ocp_reg_write(tp, OCP_POWER_CFG, data);
	} else {
		int i;

		data &= ~EN_ALDPS;
		ocp_reg_write(tp, OCP_POWER_CFG, data);
		for (i = 0; i < 20; i++) {
			usleep_range(1000, 2000);
			if (ocp_read_word(tp, MCU_TYPE_PLA, 0xe000) & 0x0100)
				break;
		}
	}

	tp->ups_info.aldps = enable;
}

static void r8153b_mcu_spdown_en(struct r8152 *tp, bool enable)
{
	u32 ocp_data;

	ocp_data = ocp_read_word(tp, MCU_TYPE_PLA, PLA_MAC_PWR_CTRL3);
	if (enable)
		ocp_data |= PLA_MCU_SPDWN_EN;
	else
		ocp_data &= ~PLA_MCU_SPDWN_EN;
	ocp_write_word(tp, MCU_TYPE_PLA, PLA_MAC_PWR_CTRL3, ocp_data);
}

static void r8153_hw_phy_cfg(struct r8152 *tp)
{
	u32 ocp_data;
	u16 data;

	/* disable ALDPS before updating the PHY parameters */
	r8153_aldps_en(tp, false);

	/* disable EEE before updating the PHY parameters */
	rtl_eee_enable(tp, false);

	r8153_firmware(tp);

	if (tp->version == RTL_VER_03) {
		data = ocp_reg_read(tp, OCP_EEE_CFG);
		data &= ~CTAP_SHORT_EN;
		ocp_reg_write(tp, OCP_EEE_CFG, data);
	}

	data = ocp_reg_read(tp, OCP_POWER_CFG);
	data |= EEE_CLKDIV_EN;
	ocp_reg_write(tp, OCP_POWER_CFG, data);

	data = ocp_reg_read(tp, OCP_DOWN_SPEED);
	data |= EN_10M_BGOFF;
	ocp_reg_write(tp, OCP_DOWN_SPEED, data);
	data = ocp_reg_read(tp, OCP_POWER_CFG);
	data |= EN_10M_PLLOFF;
	ocp_reg_write(tp, OCP_POWER_CFG, data);
	sram_write(tp, SRAM_IMPEDANCE, 0x0b13);

	ocp_data = ocp_read_word(tp, MCU_TYPE_PLA, PLA_PHY_PWR);
	ocp_data |= PFM_PWM_SWITCH;
	ocp_write_word(tp, MCU_TYPE_PLA, PLA_PHY_PWR, ocp_data);

	/* Enable LPF corner auto tune */
	sram_write(tp, SRAM_LPF_CFG, 0xf70f);

	/* Adjust 10M Amplitude */
	sram_write(tp, SRAM_10M_AMP1, 0x00af);
	sram_write(tp, SRAM_10M_AMP2, 0x0208);

	if (tp->eee_en)
		rtl_eee_enable(tp, true);

	r8153_aldps_en(tp, true);
	r8152b_enable_fc(tp);

	switch (tp->version) {
	case RTL_VER_03:
	case RTL_VER_04:
		break;
	case RTL_VER_05:
	case RTL_VER_06:
	default:
		r8153_u2p3en(tp, true);
		break;
	}

	set_bit(PHY_RESET, &tp->flags);
}

static u32 r8152_efuse_read(struct r8152 *tp, u8 addr)
{
	u32 ocp_data;

	ocp_write_word(tp, MCU_TYPE_PLA, PLA_EFUSE_CMD, EFUSE_READ_CMD | addr);
	ocp_data = ocp_read_word(tp, MCU_TYPE_PLA, PLA_EFUSE_CMD);
	ocp_data = (ocp_data & EFUSE_DATA_BIT16) << 9;	/* data of bit16 */
	ocp_data |= ocp_read_word(tp, MCU_TYPE_PLA, PLA_EFUSE_DATA);

	return ocp_data;
}

static void r8153b_hw_phy_cfg(struct r8152 *tp)
{
	u32 ocp_data;
	u16 data;

	ocp_data = ocp_read_word(tp, MCU_TYPE_USB, USB_MISC_0);
	if (ocp_data & PCUT_STATUS) {
		ocp_data &= ~PCUT_STATUS;
		ocp_write_word(tp, MCU_TYPE_USB, USB_MISC_0, ocp_data);
	}

	/* disable ALDPS before updating the PHY parameters */
	r8153_aldps_en(tp, false);

	/* disable EEE before updating the PHY parameters */
	rtl_eee_enable(tp, false);

	/* U1/U2/L1 idle timer. 500 us */
	ocp_write_word(tp, MCU_TYPE_USB, USB_U1U2_TIMER, 500);

	data = r8153_phy_status(tp, 0);

	switch (data) {
	case PHY_STAT_PWRDN:
	case PHY_STAT_EXT_INIT:
		r8153b_firmware(tp);

		data = r8152_mdio_read(tp, MII_BMCR);
		data &= ~BMCR_PDOWN;
		r8152_mdio_write(tp, MII_BMCR, data);
		break;
	case PHY_STAT_LAN_ON:
	default:
		r8153b_firmware(tp);
		break;
	}

	r8153b_green_en(tp, test_bit(GREEN_ETHERNET, &tp->flags));

	data = sram_read(tp, SRAM_GREEN_CFG);
	data |= R_TUNE_EN;
	sram_write(tp, SRAM_GREEN_CFG, data);
	data = ocp_reg_read(tp, OCP_NCTL_CFG);
	data |= PGA_RETURN_EN;
	ocp_reg_write(tp, OCP_NCTL_CFG, data);

	/* ADC Bias Calibration:
	 * read efuse offset 0x7d to get a 17-bit data. Remove the dummy/fake
	 * bit (bit3) to rebuild the real 16-bit data. Write the data to the
	 * ADC ioffset.
	 */
	ocp_data = r8152_efuse_read(tp, 0x7d);
	data = (u16)(((ocp_data & 0x1fff0) >> 1) | (ocp_data & 0x7));
	if (data != 0xffff)
		ocp_reg_write(tp, OCP_ADC_IOFFSET, data);

	/* ups mode tx-link-pulse timing adjustment:
	 * rg_saw_cnt = OCP reg 0xC426 Bit[13:0]
	 * swr_cnt_1ms_ini = 16000000 / rg_saw_cnt
	 */
	ocp_data = ocp_reg_read(tp, 0xc426);
	ocp_data &= 0x3fff;
	if (ocp_data) {
		u32 swr_cnt_1ms_ini;

		swr_cnt_1ms_ini = (16000000 / ocp_data) & SAW_CNT_1MS_MASK;
		ocp_data = ocp_read_word(tp, MCU_TYPE_USB, USB_UPS_CFG);
		ocp_data = (ocp_data & ~SAW_CNT_1MS_MASK) | swr_cnt_1ms_ini;
		ocp_write_word(tp, MCU_TYPE_USB, USB_UPS_CFG, ocp_data);
	}

	ocp_data = ocp_read_word(tp, MCU_TYPE_PLA, PLA_PHY_PWR);
	ocp_data |= PFM_PWM_SWITCH;
	ocp_write_word(tp, MCU_TYPE_PLA, PLA_PHY_PWR, ocp_data);

#ifdef CONFIG_CTAP_SHORT_OFF
	data = ocp_reg_read(tp, OCP_EEE_CFG);
	data &= ~CTAP_SHORT_EN;
	ocp_reg_write(tp, OCP_EEE_CFG, data);

	tp->ups_info.ctap_short_off = true;
#endif
	/* Advnace EEE */
	if (!rtl_phy_patch_request(tp, true, true)) {
		data = ocp_reg_read(tp, OCP_POWER_CFG);
		data |= EEE_CLKDIV_EN;
		ocp_reg_write(tp, OCP_POWER_CFG, data);
		tp->ups_info.eee_ckdiv = true;

		data = ocp_reg_read(tp, OCP_DOWN_SPEED);
		data |= EN_EEE_CMODE | EN_EEE_1000 | EN_10M_CLKDIV;
		ocp_reg_write(tp, OCP_DOWN_SPEED, data);
		tp->ups_info.eee_cmod_lv = true;
		tp->ups_info._10m_ckdiv = true;
		tp->ups_info.eee_plloff_giga = true;

		ocp_reg_write(tp, OCP_SYSCLK_CFG, 0);
		ocp_reg_write(tp, OCP_SYSCLK_CFG, clk_div_expo(5));
		tp->ups_info._250m_ckdiv = true;

		rtl_phy_patch_request(tp, false, true);
	}

	if (tp->eee_en)
		rtl_eee_enable(tp, true);

	r8153_aldps_en(tp, true);
	r8152b_enable_fc(tp);
//	r8153_u2p3en(tp, true);

	set_bit(PHY_RESET, &tp->flags);
	rtl_set_dbg_info_state(tp, DGB_DRV_STATE_LOAD);
}

static void r8153c_hw_phy_cfg(struct r8152 *tp)
{
	r8153b_hw_phy_cfg(tp);

	tp->ups_info.r_tune = true;
}

static void rtl8153_change_mtu(struct r8152 *tp)
{
	ocp_write_word(tp, MCU_TYPE_PLA, PLA_RMS, mtu_to_size(tp->netdev->mtu));
	ocp_write_byte(tp, MCU_TYPE_PLA, PLA_MTPS, MTPS_JUMBO);
}

static void r8153_first_init(struct r8152 *tp)
{
	u32 ocp_data;

	rxdy_gated_en(tp, true);
	r8153_teredo_off(tp);

	ocp_data = ocp_read_dword(tp, MCU_TYPE_PLA, PLA_RCR);
	ocp_data &= ~RCR_ACPT_ALL;
	ocp_write_dword(tp, MCU_TYPE_PLA, PLA_RCR, ocp_data);

	rtl8152_nic_reset(tp);
	rtl_reset_bmu(tp);

	ocp_data = ocp_read_byte(tp, MCU_TYPE_PLA, PLA_OOB_CTRL);
	ocp_data &= ~NOW_IS_OOB;
	ocp_write_byte(tp, MCU_TYPE_PLA, PLA_OOB_CTRL, ocp_data);

	ocp_data = ocp_read_word(tp, MCU_TYPE_PLA, PLA_SFF_STS_7);
	ocp_data &= ~MCU_BORW_EN;
	ocp_write_word(tp, MCU_TYPE_PLA, PLA_SFF_STS_7, ocp_data);

	wait_oob_link_list_ready(tp);

	ocp_data = ocp_read_word(tp, MCU_TYPE_PLA, PLA_SFF_STS_7);
	ocp_data |= RE_INIT_LL;
	ocp_write_word(tp, MCU_TYPE_PLA, PLA_SFF_STS_7, ocp_data);

	wait_oob_link_list_ready(tp);

	rtl_rx_vlan_en(tp, tp->netdev->features & NETIF_F_HW_VLAN_CTAG_RX);

	rtl8153_change_mtu(tp);

	ocp_data = ocp_read_word(tp, MCU_TYPE_PLA, PLA_TCR0);
	ocp_data |= TCR0_AUTO_FIFO;
	ocp_write_word(tp, MCU_TYPE_PLA, PLA_TCR0, ocp_data);

	rtl8152_nic_reset(tp);

	/* rx share fifo credit full threshold */
	ocp_write_dword(tp, MCU_TYPE_PLA, PLA_RXFIFO_CTRL0, RXFIFO_THR1_NORMAL);
	ocp_write_word(tp, MCU_TYPE_PLA, PLA_RXFIFO_CTRL1, RXFIFO_THR2_NORMAL);
	ocp_write_word(tp, MCU_TYPE_PLA, PLA_RXFIFO_CTRL2, RXFIFO_THR3_NORMAL);
	/* TX share fifo free credit full threshold */
	ocp_write_dword(tp, MCU_TYPE_PLA, PLA_TXFIFO_CTRL, TXFIFO_THR_NORMAL2);
}

static void r8153_enter_oob(struct r8152 *tp)
{
	u32 ocp_data;

	ocp_data = ocp_read_byte(tp, MCU_TYPE_PLA, PLA_OOB_CTRL);
	ocp_data &= ~NOW_IS_OOB;
	ocp_write_byte(tp, MCU_TYPE_PLA, PLA_OOB_CTRL, ocp_data);

	rtl_disable(tp);
	rtl_reset_bmu(tp);

	wait_oob_link_list_ready(tp);

	ocp_data = ocp_read_word(tp, MCU_TYPE_PLA, PLA_SFF_STS_7);
	ocp_data |= RE_INIT_LL;
	ocp_write_word(tp, MCU_TYPE_PLA, PLA_SFF_STS_7, ocp_data);

	wait_oob_link_list_ready(tp);

	ocp_write_word(tp, MCU_TYPE_PLA, PLA_RMS, mtu_to_size(tp->netdev->mtu));
	ocp_write_byte(tp, MCU_TYPE_PLA, PLA_MTPS, MTPS_DEFAULT);

	switch (tp->version) {
	case RTL_VER_03:
	case RTL_VER_04:
	case RTL_VER_05:
	case RTL_VER_06:
		ocp_data = ocp_read_word(tp, MCU_TYPE_PLA, PLA_TEREDO_CFG);
		ocp_data &= ~TEREDO_WAKE_MASK;
		ocp_write_word(tp, MCU_TYPE_PLA, PLA_TEREDO_CFG, ocp_data);
		break;

	case RTL_VER_08:
	case RTL_VER_09:
	case RTL_VER_14:
		/* Clear teredo wake event. bit[15:8] is the teredo wakeup
		 * type. Set it to zero. bits[7:0] are the W1C bits about
		 * the events. Set them to all 1 to clear them.
		 */
		ocp_write_word(tp, MCU_TYPE_PLA, PLA_TEREDO_WAKE_BASE, 0x00ff);
		break;

	default:
		break;
	}

	rtl_rx_vlan_en(tp, true);

	ocp_data = ocp_read_word(tp, MCU_TYPE_PLA, PLA_BDC_CR);
	ocp_data |= ALDPS_PROXY_MODE;
	ocp_write_word(tp, MCU_TYPE_PLA, PLA_BDC_CR, ocp_data);

	ocp_data = ocp_read_byte(tp, MCU_TYPE_PLA, PLA_OOB_CTRL);
	ocp_data |= NOW_IS_OOB | DIS_MCU_CLROOB;
	ocp_write_byte(tp, MCU_TYPE_PLA, PLA_OOB_CTRL, ocp_data);

	ocp_data = ocp_read_word(tp, MCU_TYPE_PLA, PLA_SFF_STS_7);
	ocp_data |= MCU_BORW_EN;
	ocp_write_word(tp, MCU_TYPE_PLA, PLA_SFF_STS_7, ocp_data);

	rxdy_gated_en(tp, false);

	ocp_data = ocp_read_dword(tp, MCU_TYPE_PLA, PLA_RCR);
	ocp_data |= RCR_APM | RCR_AM | RCR_AB;
	ocp_write_dword(tp, MCU_TYPE_PLA, PLA_RCR, ocp_data);
}

static void rtl8153_disable(struct r8152 *tp)
{
	r8153_aldps_en(tp, false);
	rtl_disable(tp);
	rtl_reset_bmu(tp);
	r8153_aldps_en(tp, true);
}

static int rtl8156_enable(struct r8152 *tp)
{
	u32 ocp_data;
	u16 speed;

	if (test_bit(RTL8152_UNPLUG, &tp->flags))
		return -ENODEV;

	set_tx_qlen(tp);
	rtl_set_eee_plus(tp);
	r8153_set_rx_early_timeout(tp);
	r8153_set_rx_early_size(tp);

	switch (tp->version) {
	case RTL_TEST_01:
		ocp_data = ocp_read_byte(tp, MCU_TYPE_PLA, 0xe95a);
		ocp_data &= ~0xf;
		ocp_data |= 5;
		ocp_write_byte(tp, MCU_TYPE_PLA, 0xe95a, ocp_data);

		ocp_data = ocp_read_byte(tp, MCU_TYPE_PLA, 0xe940);
		ocp_data &= ~0x1f;
		ocp_data |= 4;
		ocp_write_byte(tp, MCU_TYPE_PLA, 0xe940, ocp_data);
		break;
	default:
		break;
	}

	speed = rtl8152_get_speed(tp);
	rtl_set_ifg(tp, speed);

	ocp_data = ocp_read_word(tp, MCU_TYPE_PLA, PLA_MAC_PWR_CTRL4);
	if (speed & _2500bps)
		ocp_data &= ~IDLE_SPDWN_EN;
	else
		ocp_data |= IDLE_SPDWN_EN;
	ocp_write_word(tp, MCU_TYPE_PLA, PLA_MAC_PWR_CTRL4, ocp_data);

	if (speed & _1000bps)
		ocp_write_word(tp, MCU_TYPE_PLA, PLA_EEE_TXTWSYS, 0x11);
	else if (speed & _500bps)
		ocp_write_word(tp, MCU_TYPE_PLA, PLA_EEE_TXTWSYS, 0x3d);

	if (tp->udev->speed == USB_SPEED_HIGH) {
		/* USB 0xb45e[3:0] l1_nyet_hird */
		ocp_data = ocp_read_word(tp, MCU_TYPE_USB, USB_L1_CTRL);
		ocp_data &= ~0xf;
		if (is_flow_control(speed))
			ocp_data |= 0xf;
		else
			ocp_data |= 0x1;
		ocp_write_word(tp, MCU_TYPE_USB, USB_L1_CTRL, ocp_data);
	}

	return rtl_enable(tp);
}

static int rtl8156b_enable(struct r8152 *tp)
{
	u32 ocp_data;
	u16 speed;

	if (test_bit(RTL8152_UNPLUG, &tp->flags))
		return -ENODEV;

	set_tx_qlen(tp);
	rtl_set_eee_plus(tp);

	ocp_data = ocp_read_word(tp, MCU_TYPE_USB, USB_RX_AGGR_NUM);
	ocp_data &= ~RX_AGGR_NUM_MASK;
//	ocp_data |= 2;
	ocp_write_word(tp, MCU_TYPE_USB, USB_RX_AGGR_NUM, ocp_data);

	r8153_set_rx_early_timeout(tp);
	r8153_set_rx_early_size(tp);

	speed = rtl8152_get_speed(tp);
	rtl_set_ifg(tp, speed);

	ocp_data = ocp_read_word(tp, MCU_TYPE_PLA, PLA_MAC_PWR_CTRL4);
	if (speed & _2500bps)
		ocp_data &= ~IDLE_SPDWN_EN;
	else
		ocp_data |= IDLE_SPDWN_EN;
	ocp_write_word(tp, MCU_TYPE_PLA, PLA_MAC_PWR_CTRL4, ocp_data);

	if (tp->udev->speed == USB_SPEED_HIGH) {
		ocp_data = ocp_read_word(tp, MCU_TYPE_USB, USB_L1_CTRL);
		ocp_data &= ~0xf;
		if (is_flow_control(speed))
			ocp_data |= 0xf;
		else
			ocp_data |= 0x1;
		ocp_write_word(tp, MCU_TYPE_USB, USB_L1_CTRL, ocp_data);
	}

	ocp_data = ocp_read_word(tp, MCU_TYPE_USB, USB_FW_TASK);
	ocp_data &= ~FC_PATCH_TASK;
	ocp_write_word(tp, MCU_TYPE_USB, USB_FW_TASK, ocp_data);
	usleep_range(1000, 2000);
	ocp_data |= FC_PATCH_TASK;
	ocp_write_word(tp, MCU_TYPE_USB, USB_FW_TASK, ocp_data);

	return rtl_enable(tp);
}

static int rtl8152_set_speed(struct r8152 *tp, u8 autoneg, u32 speed, u8 duplex,
			     u32 advertising)
{
	u16 bmcr;
	int ret = 0;

	if (autoneg == AUTONEG_DISABLE) {
		if (duplex != DUPLEX_HALF && duplex != DUPLEX_FULL)
			return -EINVAL;

		switch (speed) {
		case SPEED_10:
			bmcr = BMCR_SPEED10;
			if (duplex == DUPLEX_FULL) {
				bmcr |= BMCR_FULLDPLX;
				tp->ups_info.speed_duplex = FORCE_10M_FULL;
			} else {
				tp->ups_info.speed_duplex = FORCE_10M_HALF;
			}
			break;
		case SPEED_100:
			bmcr = BMCR_SPEED100;
			if (duplex == DUPLEX_FULL) {
				bmcr |= BMCR_FULLDPLX;
				tp->ups_info.speed_duplex = FORCE_100M_FULL;
			} else {
				tp->ups_info.speed_duplex = FORCE_100M_HALF;
			}
			break;
		case SPEED_1000:
			if (tp->mii.supports_gmii) {
				bmcr = BMCR_SPEED1000 | BMCR_FULLDPLX;
				tp->ups_info.speed_duplex = NWAY_1000M_FULL;
				break;
			}
			fallthrough;
		default:
			ret = -EINVAL;
			goto out;
		}

		if (duplex == DUPLEX_FULL)
			tp->mii.full_duplex = 1;
		else
			tp->mii.full_duplex = 0;

		tp->mii.force_media = 1;
	} else {
		u16 orig, new1;
		u32 support;

		support = RTL_ADVERTISED_10_HALF | RTL_ADVERTISED_10_FULL |
			  RTL_ADVERTISED_100_HALF | RTL_ADVERTISED_100_FULL;

		if (tp->mii.supports_gmii) {
			support |= RTL_ADVERTISED_1000_FULL;

			if (tp->support_2500full)
				support |= RTL_ADVERTISED_2500_FULL;
		}

		if (!(advertising & support))
			return -EINVAL;

		orig = r8152_mdio_read(tp, MII_ADVERTISE);
		new1 = orig & ~(ADVERTISE_10HALF | ADVERTISE_10FULL |
				ADVERTISE_100HALF | ADVERTISE_100FULL);
		if (advertising & RTL_ADVERTISED_10_HALF) {
			new1 |= ADVERTISE_10HALF;
			tp->ups_info.speed_duplex = NWAY_10M_HALF;
		}
		if (advertising & RTL_ADVERTISED_10_FULL) {
			new1 |= ADVERTISE_10FULL;
			tp->ups_info.speed_duplex = NWAY_10M_FULL;
		}

		if (advertising & RTL_ADVERTISED_100_HALF) {
			new1 |= ADVERTISE_100HALF;
			tp->ups_info.speed_duplex = NWAY_100M_HALF;
		}
		if (advertising & RTL_ADVERTISED_100_FULL) {
			new1 |= ADVERTISE_100FULL;
			tp->ups_info.speed_duplex = NWAY_100M_FULL;
		}

		if (orig != new1) {
			r8152_mdio_write(tp, MII_ADVERTISE, new1);
			tp->mii.advertising = new1;
		}

		if (tp->mii.supports_gmii) {
			orig = r8152_mdio_read(tp, MII_CTRL1000);
			new1 = orig & ~(ADVERTISE_1000FULL |
					ADVERTISE_1000HALF);

			if (advertising & RTL_ADVERTISED_1000_FULL) {
				new1 |= ADVERTISE_1000FULL;
				tp->ups_info.speed_duplex = NWAY_1000M_FULL;
			}

			if (orig != new1)
				r8152_mdio_write(tp, MII_CTRL1000, new1);
		}

		if (tp->support_2500full) {
			orig = ocp_reg_read(tp, OCP_10GBT_CTRL);
			new1 = orig & ~MDIO_AN_10GBT_CTRL_ADV2_5G;

			if (advertising & RTL_ADVERTISED_2500_FULL) {
				new1 |= MDIO_AN_10GBT_CTRL_ADV2_5G;
				tp->ups_info.speed_duplex = NWAY_2500M_FULL;
			}

			if (orig != new1)
				ocp_reg_write(tp, OCP_10GBT_CTRL, new1);
		}

		bmcr = BMCR_ANENABLE | BMCR_ANRESTART;

		tp->mii.force_media = 0;
	}

	if (test_and_clear_bit(PHY_RESET, &tp->flags))
		bmcr |= BMCR_RESET;

	r8152_mdio_write(tp, MII_BMCR, bmcr);

	if (bmcr & BMCR_RESET) {
		int i;

		for (i = 0; i < 50; i++) {
			msleep(20);
			if ((r8152_mdio_read(tp, MII_BMCR) & BMCR_RESET) == 0)
				break;
		}
	}

out:
	return ret;
}

static bool rtl_speed_down(struct r8152 *tp)
{
	bool ret = false;

	if (test_bit(RTL8152_UNPLUG, &tp->flags))
		return ret;

	if ((tp->saved_wolopts & WAKE_ANY) && !(tp->saved_wolopts & WAKE_PHY)) {
		u16 bmcr;

		bmcr = r8152_mdio_read(tp, MII_BMCR);

		if (netif_carrier_ok(tp->netdev) && (bmcr & BMCR_ANENABLE) &&
		    (r8152_mdio_read(tp, MII_EXPANSION) & EXPANSION_NWAY)) {
			u16 anar, gbcr = 0, lpa, gbcr2 = 0;

			anar = r8152_mdio_read(tp, MII_ADVERTISE);
			anar &= ~(ADVERTISE_10HALF | ADVERTISE_10FULL |
				  ADVERTISE_100HALF | ADVERTISE_100FULL);

			if (tp->mii.supports_gmii) {
				gbcr = r8152_mdio_read(tp, MII_CTRL1000);
				gbcr &= ~(ADVERTISE_1000FULL |
					  ADVERTISE_1000HALF);
				if (tp->support_2500full) {
					gbcr2 = ocp_reg_read(tp, 0xa5d4);
					gbcr2 &= ~BIT(7);
				}
			}

			lpa = r8152_mdio_read(tp, MII_LPA);
			if (lpa & (LPA_10HALF | LPA_10FULL)) {
				anar |= ADVERTISE_10HALF | ADVERTISE_10FULL;
				rtl_eee_plus_en(tp, true);
			} else if (lpa & (LPA_100HALF | LPA_100FULL)) {
				anar |= ADVERTISE_10HALF | ADVERTISE_10FULL |
					ADVERTISE_100HALF | ADVERTISE_100FULL;
			} else {
				goto out1;
			}

			if (tp->mii.supports_gmii) {
				r8152_mdio_write(tp, MII_CTRL1000, gbcr);
				if (tp->support_2500full)
					ocp_reg_write(tp, 0xa5d4, gbcr2);
			}

			r8152_mdio_write(tp, MII_ADVERTISE, anar);
			r8152_mdio_write(tp, MII_BMCR, bmcr | BMCR_ANRESTART);

			set_bit(RECOVER_SPEED, &tp->flags);
			ret = true;
		}
	}

out1:
	return ret;
}

static void rtl8152_up(struct r8152 *tp)
{
	if (test_bit(RTL8152_UNPLUG, &tp->flags))
		return;

	r8152_aldps_en(tp, false);
	r8152b_exit_oob(tp);
	r8152_aldps_en(tp, true);
}

static void rtl8152_down(struct r8152 *tp)
{
	if (test_bit(RTL8152_UNPLUG, &tp->flags)) {
		rtl_drop_queued_tx(tp);
		return;
	}

	r8152_power_cut_en(tp, false);
	r8152_aldps_en(tp, false);
	r8152b_enter_oob(tp);
	r8152_aldps_en(tp, true);
}

static void rtl8153_up(struct r8152 *tp)
{
	u32 ocp_data;

	if (test_bit(RTL8152_UNPLUG, &tp->flags))
		return;

	r8153_u1u2en(tp, false);
	r8153_u2p3en(tp, false);
	r8153_aldps_en(tp, false);
	r8153_first_init(tp);

	ocp_data = ocp_read_byte(tp, MCU_TYPE_PLA, PLA_CONFIG6);
	ocp_data |= LANWAKE_CLR_EN;
	ocp_write_byte(tp, MCU_TYPE_PLA, PLA_CONFIG6, ocp_data);

	ocp_data = ocp_read_byte(tp, MCU_TYPE_PLA, PLA_LWAKE_CTRL_REG);
	ocp_data &= ~LANWAKE_PIN;
	ocp_write_byte(tp, MCU_TYPE_PLA, PLA_LWAKE_CTRL_REG, ocp_data);

	ocp_data = ocp_read_word(tp, MCU_TYPE_USB, USB_SSPHYLINK1);
	ocp_data &= ~DELAY_PHY_PWR_CHG;
	ocp_write_word(tp, MCU_TYPE_USB, USB_SSPHYLINK1, ocp_data);

	r8153_aldps_en(tp, true);

	switch (tp->version) {
	case RTL_VER_03:
	case RTL_VER_04:
		break;
	case RTL_VER_05:
	case RTL_VER_06:
	default:
		r8153_u2p3en(tp, true);
		break;
	}

	r8153_u1u2en(tp, true);
}

static void rtl8153_down(struct r8152 *tp)
{
	u32 ocp_data;

	if (test_bit(RTL8152_UNPLUG, &tp->flags)) {
		rtl_drop_queued_tx(tp);
		return;
	}

	ocp_data = ocp_read_byte(tp, MCU_TYPE_PLA, PLA_CONFIG6);
	ocp_data &= ~LANWAKE_CLR_EN;
	ocp_write_byte(tp, MCU_TYPE_PLA, PLA_CONFIG6, ocp_data);

	r8153_u1u2en(tp, false);
	r8153_u2p3en(tp, false);
	r8153_power_cut_en(tp, false);
	r8153_aldps_en(tp, false);
	r8153_enter_oob(tp);
	r8153_aldps_en(tp, true);
}

static void rtl8153b_up(struct r8152 *tp)
{
	if (test_bit(RTL8152_UNPLUG, &tp->flags))
		return;

	r8153b_u1u2en(tp, false);
	r8153_u2p3en(tp, false);
	r8153_aldps_en(tp, false);

	r8153_first_init(tp);
	ocp_write_dword(tp, MCU_TYPE_USB, USB_RX_BUF_TH, RX_THR_B);

	r8153b_mcu_spdown_en(tp, false);
	r8153_aldps_en(tp, true);
//	r8153_u2p3en(tp, true);
	if (tp->udev->speed >= USB_SPEED_SUPER)
		r8153b_u1u2en(tp, true);
}

static void rtl8153b_down(struct r8152 *tp)
{
	if (test_bit(RTL8152_UNPLUG, &tp->flags)) {
		rtl_drop_queued_tx(tp);
		return;
	}

	r8153b_mcu_spdown_en(tp, true);
	r8153b_u1u2en(tp, false);
	r8153_u2p3en(tp, false);
	r8153b_power_cut_en(tp, false);
	r8153_aldps_en(tp, false);
	r8153_enter_oob(tp);
	r8153_aldps_en(tp, true);
}

static void rtl8153c_change_mtu(struct r8152 *tp)
{
	ocp_write_word(tp, MCU_TYPE_PLA, PLA_RMS, mtu_to_size(tp->netdev->mtu));
	ocp_write_byte(tp, MCU_TYPE_PLA, PLA_MTPS, 10 * 1024 / 64);

	ocp_write_word(tp, MCU_TYPE_PLA, PLA_TXFIFO_CTRL, 512 / 64);

	/* Adjust the tx fifo free credit full threshold, otherwise
	 * the fifo would be too small to send a jumbo frame packet.
	 */
	if (tp->netdev->mtu < 8000)
		ocp_write_word(tp, MCU_TYPE_PLA, PLA_TXFIFO_FULL, 2048 / 8);
	else
		ocp_write_word(tp, MCU_TYPE_PLA, PLA_TXFIFO_FULL, 900 / 8);
}

static void rtl8153c_up(struct r8152 *tp)
{
	u32 ocp_data;

	if (test_bit(RTL8152_UNPLUG, &tp->flags))
		return;

	r8153b_u1u2en(tp, false);
	r8153_u2p3en(tp, false);
	r8153_aldps_en(tp, false);

	rxdy_gated_en(tp, true);
	r8153_teredo_off(tp);

	ocp_data = ocp_read_dword(tp, MCU_TYPE_PLA, PLA_RCR);
	ocp_data &= ~RCR_ACPT_ALL;
	ocp_write_dword(tp, MCU_TYPE_PLA, PLA_RCR, ocp_data);

	rtl8152_nic_reset(tp);
	rtl_reset_bmu(tp);

	ocp_data = ocp_read_byte(tp, MCU_TYPE_PLA, PLA_OOB_CTRL);
	ocp_data &= ~NOW_IS_OOB;
	ocp_write_byte(tp, MCU_TYPE_PLA, PLA_OOB_CTRL, ocp_data);

	ocp_data = ocp_read_word(tp, MCU_TYPE_PLA, PLA_SFF_STS_7);
	ocp_data &= ~MCU_BORW_EN;
	ocp_write_word(tp, MCU_TYPE_PLA, PLA_SFF_STS_7, ocp_data);

	wait_oob_link_list_ready(tp);

	ocp_data = ocp_read_word(tp, MCU_TYPE_PLA, PLA_SFF_STS_7);
	ocp_data |= RE_INIT_LL;
	ocp_write_word(tp, MCU_TYPE_PLA, PLA_SFF_STS_7, ocp_data);

	wait_oob_link_list_ready(tp);

	rtl_rx_vlan_en(tp, tp->netdev->features & NETIF_F_HW_VLAN_CTAG_RX);

	rtl8153c_change_mtu(tp);

	rtl8152_nic_reset(tp);

	/* rx share fifo credit full threshold */
	ocp_write_byte(tp, MCU_TYPE_PLA, PLA_RXFIFO_CTRL0, 0x02);
	ocp_write_byte(tp, MCU_TYPE_PLA, PLA_RXFIFO_FULL, 0x08);
	ocp_write_word(tp, MCU_TYPE_PLA, PLA_RXFIFO_CTRL1, RXFIFO_THR2_NORMAL);
	ocp_write_word(tp, MCU_TYPE_PLA, PLA_RXFIFO_CTRL2, RXFIFO_THR3_NORMAL);

	ocp_write_dword(tp, MCU_TYPE_USB, USB_RX_BUF_TH, RX_THR_B);

	ocp_write_byte(tp, MCU_TYPE_PLA, PLA_CRWECR, CRWECR_CONFIG);

	ocp_data = ocp_read_word(tp, MCU_TYPE_PLA, PLA_CONFIG34);
	ocp_data |= BIT(8);
	ocp_write_word(tp, MCU_TYPE_PLA, PLA_CONFIG34, ocp_data);

	ocp_write_byte(tp, MCU_TYPE_PLA, PLA_CRWECR, CRWECR_NORAML);

	r8153b_mcu_spdown_en(tp, false);

	r8153_aldps_en(tp, true);
//	r8153_u2p3en(tp, true);
	r8153b_u1u2en(tp, true);
}

static inline u32 fc_pause_on_auto(struct r8152 *tp)
{
	return (ALIGN(mtu_to_size(tp->netdev->mtu), 1024) + 6 * 1024);
}

static inline u32 fc_pause_off_auto(struct r8152 *tp)
{
	return (ALIGN(mtu_to_size(tp->netdev->mtu), 1024) + 14 * 1024);
}

static void r8156_fc_parameter(struct r8152 *tp)
{
	u32 pause_on = tp->fc_pause_on ? tp->fc_pause_on : fc_pause_on_auto(tp);
	u32 pause_off = tp->fc_pause_off ? tp->fc_pause_off : fc_pause_off_auto(tp);

	switch (tp->version) {
	case RTL_VER_10:
	case RTL_VER_11:
		ocp_write_word(tp, MCU_TYPE_PLA, PLA_RX_FIFO_FULL, pause_on / 8);
		ocp_write_word(tp, MCU_TYPE_PLA, PLA_RX_FIFO_EMPTY, pause_off / 8);
		break;
	case RTL_VER_12:
	case RTL_VER_13:
	case RTL_VER_15:
		ocp_write_word(tp, MCU_TYPE_PLA, PLA_RX_FIFO_FULL, pause_on / 16);
		ocp_write_word(tp, MCU_TYPE_PLA, PLA_RX_FIFO_EMPTY, pause_off / 16);
		break;
	default:
		break;
	}
}

static void rtl8156_change_mtu(struct r8152 *tp)
{
	u32 rx_max_size = mtu_to_size(tp->netdev->mtu);

	ocp_write_word(tp, MCU_TYPE_PLA, PLA_RMS, rx_max_size);
	ocp_write_byte(tp, MCU_TYPE_PLA, PLA_MTPS, MTPS_JUMBO);
	r8156_fc_parameter(tp);

	/* TX share fifo free credit full threshold */
	ocp_write_word(tp, MCU_TYPE_PLA, PLA_TXFIFO_CTRL, 512 / 64);
	ocp_write_word(tp, MCU_TYPE_PLA, PLA_TXFIFO_FULL,
		       ALIGN(rx_max_size + sizeof(struct tx_desc), 1024) / 16);
}

static void rtl8156_up(struct r8152 *tp)
{
	u32 ocp_data;

	if (test_bit(RTL8152_UNPLUG, &tp->flags))
		return;

	r8153b_u1u2en(tp, false);
	r8153_u2p3en(tp, false);
	r8153_aldps_en(tp, false);

	rxdy_gated_en(tp, true);
	r8153_teredo_off(tp);

	ocp_data = ocp_read_dword(tp, MCU_TYPE_PLA, PLA_RCR);
	ocp_data &= ~RCR_ACPT_ALL;
	ocp_write_dword(tp, MCU_TYPE_PLA, PLA_RCR, ocp_data);

	rtl8152_nic_reset(tp);
	rtl_reset_bmu(tp);

	ocp_data = ocp_read_byte(tp, MCU_TYPE_PLA, PLA_OOB_CTRL);
	ocp_data &= ~NOW_IS_OOB;
	ocp_write_byte(tp, MCU_TYPE_PLA, PLA_OOB_CTRL, ocp_data);

	ocp_data = ocp_read_word(tp, MCU_TYPE_PLA, PLA_SFF_STS_7);
	ocp_data &= ~MCU_BORW_EN;
	ocp_write_word(tp, MCU_TYPE_PLA, PLA_SFF_STS_7, ocp_data);

	rtl_rx_vlan_en(tp, tp->netdev->features & NETIF_F_HW_VLAN_CTAG_RX);

	rtl8156_change_mtu(tp);

	switch (tp->version) {
	case RTL_TEST_01:
	case RTL_VER_10:
	case RTL_VER_11:
		ocp_data = ocp_read_word(tp, MCU_TYPE_USB, USB_BMU_CONFIG);
		ocp_data |= ACT_ODMA;
		ocp_write_word(tp, MCU_TYPE_USB, USB_BMU_CONFIG, ocp_data);
		break;
	default:
		break;
	}

	/* share FIFO settings */
	ocp_data = ocp_read_word(tp, MCU_TYPE_PLA, PLA_RXFIFO_FULL);
	ocp_data &= ~RXFIFO_FULL_MASK;
	ocp_data |= 0x08;
	ocp_write_word(tp, MCU_TYPE_PLA, PLA_RXFIFO_FULL, ocp_data);

	r8153b_mcu_spdown_en(tp, false);

	ocp_data = ocp_read_word(tp, MCU_TYPE_USB, USB_SPEED_OPTION);
	ocp_data &= ~(RG_PWRDN_EN | ALL_SPEED_OFF);
	ocp_write_word(tp, MCU_TYPE_USB, USB_SPEED_OPTION, ocp_data);

	ocp_write_dword(tp, MCU_TYPE_USB, USB_RX_BUF_TH, 0x00600400);

	if (tp->saved_wolopts != __rtl_get_wol(tp)) {
		netif_warn(tp, ifup, tp->netdev, "wol setting is changed\n");
		__rtl_set_wol(tp, tp->saved_wolopts);
	}

	r8153_aldps_en(tp, true);
	r8153_u2p3en(tp, true);

	if (tp->udev->speed >= USB_SPEED_SUPER)
		r8153b_u1u2en(tp, true);
}

static void rtl8156_down(struct r8152 *tp)
{
	u32 ocp_data;

	if (test_bit(RTL8152_UNPLUG, &tp->flags)) {
		rtl_drop_queued_tx(tp);
		return;
	}

	r8153b_mcu_spdown_en(tp, true);
	r8153b_u1u2en(tp, false);
	r8153_u2p3en(tp, false);
	r8153b_power_cut_en(tp, false);
	r8153_aldps_en(tp, false);

	ocp_data = ocp_read_byte(tp, MCU_TYPE_PLA, PLA_OOB_CTRL);
	ocp_data &= ~NOW_IS_OOB;
	ocp_write_byte(tp, MCU_TYPE_PLA, PLA_OOB_CTRL, ocp_data);

	rtl_disable(tp);
	rtl_reset_bmu(tp);

	/* Clear teredo wake event. bit[15:8] is the teredo wakeup
	 * type. Set it to zero. bits[7:0] are the W1C bits about
	 * the events. Set them to all 1 to clear them.
	 */
	ocp_write_word(tp, MCU_TYPE_PLA, PLA_TEREDO_WAKE_BASE, 0x00ff);

	ocp_data = ocp_read_byte(tp, MCU_TYPE_PLA, PLA_OOB_CTRL);
	ocp_data |= NOW_IS_OOB;
	ocp_write_byte(tp, MCU_TYPE_PLA, PLA_OOB_CTRL, ocp_data);

	rtl_rx_vlan_en(tp, true);
	rxdy_gated_en(tp, false);

	ocp_data = ocp_read_dword(tp, MCU_TYPE_PLA, PLA_RCR);
	ocp_data |= RCR_APM | RCR_AM | RCR_AB;
	ocp_write_dword(tp, MCU_TYPE_PLA, PLA_RCR, ocp_data);

	r8153_aldps_en(tp, true);
}

static bool rtl8152_in_nway(struct r8152 *tp)
{
	u16 nway_state;

	ocp_write_word(tp, MCU_TYPE_PLA, PLA_OCP_GPHY_BASE, 0x2000);
	tp->ocp_base = 0x2000;
	ocp_write_byte(tp, MCU_TYPE_PLA, 0xb014, 0x4c);		/* phy state */
	nway_state = ocp_read_word(tp, MCU_TYPE_PLA, 0xb01a);

	/* bit 15: TXDIS_STATE, bit 14: ABD_STATE */
	if (nway_state & 0xc000)
		return false;
	else
		return true;
}

static bool rtl8153_in_nway(struct r8152 *tp)
{
	u16 phy_state = ocp_reg_read(tp, OCP_PHY_STATE) & 0xff;

	if (phy_state == TXDIS_STATE || phy_state == ABD_STATE)
		return false;
	else
		return true;
}

static void r8156_mdio_force_mode(struct r8152 *tp)
{
	u16 data;

	/* Select force mode through 0xa5b4 bit 15
	 * 0: MDIO force mode
	 * 1: MMD force mode
	 */
	data = ocp_reg_read(tp, 0xa5b4);
	if (data & BIT(15)) {
		data &= ~BIT(15);
		ocp_reg_write(tp, 0xa5b4, data);
	}
}

static void set_carrier(struct r8152 *tp)
{
	struct net_device *netdev = tp->netdev;
	struct napi_struct *napi = &tp->napi;
	u16 speed;

	speed = rtl8152_get_speed(tp);

	if (speed & LINK_STATUS) {
		if (!netif_carrier_ok(netdev)) {
			tp->rtl_ops.enable(tp);
			netif_stop_queue(netdev);
			napi_disable(napi);
			netif_carrier_on(netdev);
			rtl_start_rx(tp);
			rtl8152_set_rx_mode(netdev);
			napi_enable(napi);
			netif_wake_queue(netdev);
			netif_info(tp, link, netdev, "carrier on\n");
		} else if (netif_queue_stopped(netdev) &&
			   skb_queue_len(&tp->tx_queue) < tp->tx_qlen) {
			netif_wake_queue(netdev);
		}
	} else {
		if (netif_carrier_ok(netdev)) {
			netif_carrier_off(netdev);
			tasklet_disable(&tp->tx_tl);
			napi_disable(napi);
			tp->rtl_ops.disable(tp);
			napi_enable(napi);
			tasklet_enable(&tp->tx_tl);
			netif_info(tp, link, netdev, "carrier off\n");
		}
	}
}

static inline void __rtl_work_func(struct r8152 *tp)
{
	/* If the device is unplugged or !netif_running(), the workqueue
	 * doesn't need to wake the device, and could return directly.
	 */
	if (test_bit(RTL8152_UNPLUG, &tp->flags) || !netif_running(tp->netdev))
		return;

	if (usb_autopm_get_interface(tp->intf) < 0)
		return;

	if (!test_bit(WORK_ENABLE, &tp->flags))
		goto out1;

	if (!mutex_trylock(&tp->control)) {
		if (tp->rtk_enable_diag)
			goto link_chg_only;

		schedule_delayed_work(&tp->schedule, 0);
		goto out1;
	}

	if (test_and_clear_bit(RTL8152_LINK_CHG, &tp->flags))
		set_carrier(tp);

	if (test_bit(RTL8152_SET_RX_MODE, &tp->flags))
		rtl8152_set_rx_mode(tp->netdev);

	/* don't schedule tasket before linking */
	if (test_and_clear_bit(SCHEDULE_TASKLET, &tp->flags) &&
	    netif_carrier_ok(tp->netdev))
		tasklet_schedule(&tp->tx_tl);

	if (test_and_clear_bit(RX_EPROTO, &tp->flags) &&
	    !list_empty(&tp->rx_done))
		napi_schedule(&tp->napi);

	mutex_unlock(&tp->control);

out1:
	usb_autopm_put_interface(tp->intf);

link_chg_only:
	if (test_and_clear_bit(RTL8152_LINK_CHG, &tp->flags)) {
		int lock;

		rtnl_lock();
		lock = mutex_trylock(&tp->control);
		set_carrier(tp);
		if (lock)
			mutex_unlock(&tp->control);
		rtnl_unlock();
		goto out1;
	}
}

static inline void __rtl_hw_phy_work_func(struct r8152 *tp)
{
	if (test_bit(RTL8152_UNPLUG, &tp->flags))
		return;

	if (usb_autopm_get_interface(tp->intf) < 0)
		return;

	mutex_lock(&tp->control);

	tp->rtl_ops.hw_phy_cfg(tp);

	rtl8152_set_speed(tp, tp->autoneg, tp->speed, tp->duplex,
			  tp->advertising);

	mutex_unlock(&tp->control);

	usb_autopm_put_interface(tp->intf);
}

#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,20)

static void rtl_work_func_t(void *data)
{
	struct r8152 *tp = (struct r8152 *)data;

	__rtl_work_func(tp);
}

static void rtl_hw_phy_work_func_t(void *data)
{
	struct r8152 *tp = (struct r8152 *)data;

	__rtl_hw_phy_work_func(tp);
}

#else

static void rtl_work_func_t(struct work_struct *work)
{
	struct r8152 *tp = container_of(work, struct r8152, schedule.work);

	__rtl_work_func(tp);
}

static void rtl_hw_phy_work_func_t(struct work_struct *work)
{
	struct r8152 *tp = container_of(work, struct r8152, hw_phy_work.work);

	__rtl_hw_phy_work_func(tp);
}

#endif

#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,23) && defined(CONFIG_PM_SLEEP)
static int rtl_notifier(struct notifier_block *nb, unsigned long action,
			void *data)
{
	struct r8152 *tp = container_of(nb, struct r8152, pm_notifier);

	switch (action) {
	case PM_HIBERNATION_PREPARE:
	case PM_SUSPEND_PREPARE:
		if (usb_autopm_get_interface(tp->intf) < 0)
			netif_info(tp, drv, tp->netdev, "Auto-wake fail\n");
		break;

	case PM_POST_HIBERNATION:
	case PM_POST_SUSPEND:
		usb_autopm_put_interface(tp->intf);
		break;

	case PM_POST_RESTORE:
	case PM_RESTORE_PREPARE:
	default:
		break;
	}

	return NOTIFY_DONE;
}
#endif /* LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,23) && defined(CONFIG_PM_SLEEP) */

#if defined(RTL8152_S5_WOL) && defined(CONFIG_PM)
static int rtl_s5_wol(struct r8152 *tp)
{
	struct usb_device *udev = tp->udev;
	u32 ocp_data;

	if (!tp->saved_wolopts)
		return -EOPNOTSUPP;

	switch (tp->version) {
	case RTL_VER_01:
	case RTL_VER_02:
	case RTL_VER_07:
		return -EOPNOTSUPP;
	case RTL_VER_03:
	case RTL_VER_04:
	case RTL_VER_05:
	case RTL_VER_06:
		goto remote_wake;
	default:
		break;
	}

	if (!(ocp_read_word(tp, MCU_TYPE_PLA, PLA_CONFIG5) & LAN_WAKE_EN))
		return -EOPNOTSUPP;

	ocp_data = ocp_read_byte(tp, MCU_TYPE_PLA, PLA_INDICATE_FALG);
	ocp_data |= BIT(1);
	ocp_write_byte(tp, MCU_TYPE_PLA, PLA_INDICATE_FALG, ocp_data);

remote_wake:
	/* usb_enable_remote_wakeup */
	if (udev->speed < USB_SPEED_SUPER)
		return usb_control_msg(udev, usb_sndctrlpipe(udev, 0),
				USB_REQ_SET_FEATURE, USB_RECIP_DEVICE,
				USB_DEVICE_REMOTE_WAKEUP, 0, NULL, 0,
				USB_CTRL_SET_TIMEOUT);
	else
		return usb_control_msg(udev, usb_sndctrlpipe(udev, 0),
				USB_REQ_SET_FEATURE, USB_RECIP_INTERFACE,
				USB_INTRF_FUNC_SUSPEND,
				USB_INTRF_FUNC_SUSPEND_RW |
				USB_INTRF_FUNC_SUSPEND_LP,
				NULL, 0, USB_CTRL_SET_TIMEOUT);
}

static
int rtl_reboot_notifier(struct notifier_block *nb, unsigned long action,
			void *data)
{
	struct r8152 *tp = container_of(nb, struct r8152, reboot_notifier);

	switch (action) {
	case SYS_POWER_OFF:
		if (test_and_clear_bit(WORK_ENABLE, &tp->flags)) {
			int ret;

			if (usb_autopm_get_interface(tp->intf) < 0)
				break;

			mutex_lock(&tp->control);
			tp->rtl_ops.down(tp);
			ret = rtl_s5_wol(tp);
			if (ret < 0)
				netif_info(tp, drv, tp->netdev,
					   "S5 WOL is not enabled, %d\n", ret);
			else
				netif_info(tp, drv, tp->netdev, "Enable S5 WOL\n");

			mutex_unlock(&tp->control);
			usb_autopm_put_interface(tp->intf);
		}
		break;

	case SYS_RESTART:
	default:
		break;
	}

	return NOTIFY_DONE;
}
#endif /* defined(RTL8152_S5_WOL) && defined(CONFIG_PM) */

static int rtk_disable_diag(struct r8152 *tp)
{
	tp->rtk_enable_diag--;
	rtl_reset_ocp_base(tp);

	if (tp->support_2500full)
		r8156_mdio_force_mode(tp);

	netif_info(tp, drv, tp->netdev, "disable rtk diag %d\n",
		   tp->rtk_enable_diag);
	mutex_unlock(&tp->control);
	if (test_bit(WORK_ENABLE, &tp->flags))
		schedule_delayed_work(&tp->schedule, 0);
	usb_autopm_put_interface(tp->intf);

	return 0;
}

static int rtl8152_open(struct net_device *netdev)
{
	struct r8152 *tp = netdev_priv(netdev);
	int res = 0;

	if (unlikely(tp->rtk_enable_diag))
		return -EBUSY;

	if (work_busy(&tp->hw_phy_work.work) & WORK_BUSY_PENDING) {
		cancel_delayed_work_sync(&tp->hw_phy_work);
		__rtl_hw_phy_work_func(tp);
	}

	res = alloc_all_mem(tp);
	if (res)
		goto out;

	res = usb_autopm_get_interface(tp->intf);
	if (res < 0)
		goto out_free;

	mutex_lock(&tp->control);

	tp->rtl_ops.up(tp);

	netif_carrier_off(netdev);
	netif_start_queue(netdev);
	smp_mb__before_atomic();
	set_bit(WORK_ENABLE, &tp->flags);
	smp_mb__after_atomic();

	if (test_and_clear_bit(RECOVER_SPEED, &tp->flags))
		rtl8152_set_speed(tp, tp->autoneg, tp->speed, tp->duplex,
				  tp->advertising);

	res = usb_submit_urb(tp->intr_urb, GFP_KERNEL);
	if (res) {
		if (res == -ENODEV)
			netif_device_detach(tp->netdev);
		netif_warn(tp, ifup, netdev, "intr_urb submit failed: %d\n",
			   res);
		goto out_unlock;
	}
	napi_enable(&tp->napi);
	tasklet_enable(&tp->tx_tl);

	mutex_unlock(&tp->control);

	usb_autopm_put_interface(tp->intf);
#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,23) && defined(CONFIG_PM_SLEEP)
	tp->pm_notifier.notifier_call = rtl_notifier;
	register_pm_notifier(&tp->pm_notifier);
#endif
#if defined(RTL8152_S5_WOL) && defined(CONFIG_PM)
	tp->reboot_notifier.notifier_call = rtl_reboot_notifier;
	register_reboot_notifier(&tp->reboot_notifier);
#endif /* defined(RTL8152_S5_WOL) && defined(CONFIG_PM) */
	return 0;

out_unlock:
	mutex_unlock(&tp->control);
	usb_autopm_put_interface(tp->intf);
out_free:
	free_all_mem(tp);
out:
	return res;
}

static int rtl8152_close(struct net_device *netdev)
{
	struct r8152 *tp = netdev_priv(netdev);
	int res = 0;

#if defined(RTL8152_S5_WOL) && defined(CONFIG_PM)
	unregister_reboot_notifier(&tp->reboot_notifier);
#endif /* defined(RTL8152_S5_WOL) && defined(CONFIG_PM) */
#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,23) && defined(CONFIG_PM_SLEEP)
	unregister_pm_notifier(&tp->pm_notifier);
#endif
	tasklet_disable(&tp->tx_tl);
	smp_mb__before_atomic();
	clear_bit(WORK_ENABLE, &tp->flags);
	smp_mb__after_atomic();
	usb_kill_urb(tp->intr_urb);
	cancel_delayed_work_sync(&tp->schedule);
	napi_disable(&tp->napi);
	netif_stop_queue(netdev);

	if (unlikely(tp->rtk_enable_diag)) {
		netif_err(tp, drv, tp->netdev, "rtk diag isn't disabled\n");
		rtk_disable_diag(tp);
	}

	res = usb_autopm_get_interface(tp->intf);
	if (res < 0 || test_bit(RTL8152_UNPLUG, &tp->flags)) {
		rtl_drop_queued_tx(tp);
		rtl_stop_rx(tp);
	} else {
		mutex_lock(&tp->control);

		tp->rtl_ops.down(tp);

#if defined(RTL8152_S5_WOL) && defined(CONFIG_PM)
		if (rtl_s5_wol(tp) < 0)
			netif_info(tp, drv, tp->netdev,
				   "S5 WOL is not enabled\n");
		else
			netif_info(tp, drv, tp->netdev, "Enable S5 WOL\n");
#endif /* defined(RTL8152_S5_WOL) && defined(CONFIG_PM) */

		if (tp->version == RTL_VER_01)
			rtl8152_set_speed(tp, AUTONEG_ENABLE, 0, 0, 3);
		else
			rtl_speed_down(tp);

		mutex_unlock(&tp->control);

		usb_autopm_put_interface(tp->intf);
	}

	free_all_mem(tp);

	return res;
}

static void rtl_tally_reset(struct r8152 *tp)
{
	u32 ocp_data;

	ocp_data = ocp_read_word(tp, MCU_TYPE_PLA, PLA_RSTTALLY);
	ocp_data |= TALLY_RESET;
	ocp_write_word(tp, MCU_TYPE_PLA, PLA_RSTTALLY, ocp_data);
}

static void rtl_disable_spi(struct r8152 *tp)
{
	u32 ocp_data;

	ocp_write_byte(tp, MCU_TYPE_PLA, PLA_CRWECR, CRWECR_CONFIG);
	ocp_data = ocp_read_word(tp, MCU_TYPE_PLA, PLA_CONFIG5);
	ocp_data &= ~SPI_EN;
	ocp_write_word(tp, MCU_TYPE_PLA, PLA_CONFIG5, ocp_data);
	ocp_data = ocp_read_word(tp, MCU_TYPE_USB, 0xcbf0);
	ocp_data |= BIT(1);
	ocp_write_word(tp, MCU_TYPE_USB, 0xcbf0, ocp_data);
}

static void r8152b_init(struct r8152 *tp)
{
	u32 ocp_data;
	u16 data;

	if (test_bit(RTL8152_UNPLUG, &tp->flags))
		return;

#if 0
	/* Clear EP3 Fifo before using interrupt transfer */
	if (ocp_read_byte(tp, MCU_TYPE_USB, 0xb963) & 0x80) {
		ocp_write_byte(tp, MCU_TYPE_USB, 0xb963, 0x08);
		ocp_write_byte(tp, MCU_TYPE_USB, 0xb963, 0x40);
		ocp_write_byte(tp, MCU_TYPE_USB, 0xb963, 0x00);
		ocp_write_byte(tp, MCU_TYPE_USB, 0xb968, 0x00);
		ocp_write_word(tp, MCU_TYPE_USB, 0xb010, 0x00e0);
		ocp_write_byte(tp, MCU_TYPE_USB, 0xb963, 0x04);
	}
#endif

	data = r8152_mdio_read(tp, MII_BMCR);
	if (data & BMCR_PDOWN) {
		data &= ~BMCR_PDOWN;
		r8152_mdio_write(tp, MII_BMCR, data);
	}

	r8152_aldps_en(tp, false);

	if (tp->version == RTL_VER_01) {
		ocp_data = ocp_read_word(tp, MCU_TYPE_PLA, PLA_LED_FEATURE);
		ocp_data &= ~LED_MODE_MASK;
		ocp_write_word(tp, MCU_TYPE_PLA, PLA_LED_FEATURE, ocp_data);
	}

	r8152_power_cut_en(tp, false);
	rtl_runtime_suspend_enable(tp, false);

	ocp_data = ocp_read_word(tp, MCU_TYPE_PLA, PLA_PHY_PWR);
	ocp_data |= TX_10M_IDLE_EN | PFM_PWM_SWITCH;
	ocp_write_word(tp, MCU_TYPE_PLA, PLA_PHY_PWR, ocp_data);
	ocp_data = ocp_read_dword(tp, MCU_TYPE_PLA, PLA_MAC_PWR_CTRL);
	ocp_data &= ~MCU_CLK_RATIO_MASK;
	ocp_data |= MCU_CLK_RATIO | D3_CLK_GATED_EN;
	ocp_write_dword(tp, MCU_TYPE_PLA, PLA_MAC_PWR_CTRL, ocp_data);
	ocp_data = GPHY_STS_MSK | SPEED_DOWN_MSK |
		   SPDWN_RXDV_MSK | SPDWN_LINKCHG_MSK;
	ocp_write_word(tp, MCU_TYPE_PLA, PLA_GPHY_INTR_IMR, ocp_data);

	ocp_data = ocp_read_word(tp, MCU_TYPE_USB, USB_USB_TIMER);
	ocp_data |= BIT(15);
	ocp_write_word(tp, MCU_TYPE_USB, USB_USB_TIMER, ocp_data);
	ocp_write_word(tp, MCU_TYPE_USB, 0xcbfc, 0x03e8);
	ocp_data &= ~BIT(15);
	ocp_write_word(tp, MCU_TYPE_USB, USB_USB_TIMER, ocp_data);

	rtl_tally_reset(tp);

	/* enable rx aggregation */
	ocp_data = ocp_read_word(tp, MCU_TYPE_USB, USB_USB_CTRL);
	ocp_data &= ~(RX_AGG_DISABLE | RX_ZERO_EN);
	ocp_write_word(tp, MCU_TYPE_USB, USB_USB_CTRL, ocp_data);
}

static void r8153_init(struct r8152 *tp)
{
	u32 ocp_data;
	u16 data;
	int i;

	if (test_bit(RTL8152_UNPLUG, &tp->flags))
		return;

	r8153_u1u2en(tp, false);

	for (i = 0; i < 500; i++) {
		if (ocp_read_word(tp, MCU_TYPE_PLA, PLA_BOOT_CTRL) &
		    AUTOLOAD_DONE)
			break;

		msleep(20);
		if (test_bit(RTL8152_UNPLUG, &tp->flags))
			break;
	}

	data = r8153_phy_status(tp, 0);

	if (tp->version == RTL_VER_03 || tp->version == RTL_VER_04 ||
	    tp->version == RTL_VER_05)
		ocp_reg_write(tp, OCP_ADC_CFG, CKADSEL_L | ADC_EN | EN_EMI_L);

	data = r8152_mdio_read(tp, MII_BMCR);
	if (data & BMCR_PDOWN) {
		data &= ~BMCR_PDOWN;
		r8152_mdio_write(tp, MII_BMCR, data);
	}

	data = r8153_phy_status(tp, PHY_STAT_LAN_ON);

	r8153_u2p3en(tp, false);

	if (tp->version == RTL_VER_04) {
		ocp_data = ocp_read_word(tp, MCU_TYPE_USB, USB_SSPHYLINK2);
		ocp_data &= ~pwd_dn_scale_mask;
		ocp_data |= pwd_dn_scale(96);
		ocp_write_word(tp, MCU_TYPE_USB, USB_SSPHYLINK2, ocp_data);

		ocp_data = ocp_read_byte(tp, MCU_TYPE_USB, USB_USB2PHY);
		ocp_data |= USB2PHY_L1 | USB2PHY_SUSPEND;
		ocp_write_byte(tp, MCU_TYPE_USB, USB_USB2PHY, ocp_data);
	} else if (tp->version == RTL_VER_05) {
		ocp_data = ocp_read_byte(tp, MCU_TYPE_PLA, PLA_DMY_REG0);
		ocp_data &= ~ECM_ALDPS;
		ocp_write_byte(tp, MCU_TYPE_PLA, PLA_DMY_REG0, ocp_data);

		ocp_data = ocp_read_byte(tp, MCU_TYPE_USB, USB_CSR_DUMMY1);
		if (ocp_read_word(tp, MCU_TYPE_USB, USB_BURST_SIZE) == 0)
			ocp_data &= ~DYNAMIC_BURST;
		else
			ocp_data |= DYNAMIC_BURST;
		ocp_write_byte(tp, MCU_TYPE_USB, USB_CSR_DUMMY1, ocp_data);
	} else if (tp->version == RTL_VER_06) {
		ocp_data = ocp_read_byte(tp, MCU_TYPE_USB, USB_CSR_DUMMY1);
		if (ocp_read_word(tp, MCU_TYPE_USB, USB_BURST_SIZE) == 0)
			ocp_data &= ~DYNAMIC_BURST;
		else
			ocp_data |= DYNAMIC_BURST;
		ocp_write_byte(tp, MCU_TYPE_USB, USB_CSR_DUMMY1, ocp_data);

		r8153_queue_wake(tp, false);

		ocp_data = ocp_read_word(tp, MCU_TYPE_PLA, PLA_EXTRA_STATUS);
		if (rtl8152_get_speed(tp) & LINK_STATUS)
			ocp_data |= CUR_LINK_OK;
		else
			ocp_data &= ~CUR_LINK_OK;

		/* r8153_queue_wake() has set this bit */
		/* ocp_data &= ~BIT(8); */

		ocp_data |= POLL_LINK_CHG;
		ocp_write_word(tp, MCU_TYPE_PLA, PLA_EXTRA_STATUS, ocp_data);
	}

	ocp_data = ocp_read_byte(tp, MCU_TYPE_USB, USB_CSR_DUMMY2);
	ocp_data |= EP4_FULL_FC;
	ocp_write_byte(tp, MCU_TYPE_USB, USB_CSR_DUMMY2, ocp_data);

	ocp_data = ocp_read_word(tp, MCU_TYPE_USB, USB_WDT11_CTRL);
	ocp_data &= ~TIMER11_EN;
	ocp_write_word(tp, MCU_TYPE_USB, USB_WDT11_CTRL, ocp_data);

	ocp_data = ocp_read_word(tp, MCU_TYPE_PLA, PLA_LED_FEATURE);
	ocp_data &= ~LED_MODE_MASK;
	ocp_write_word(tp, MCU_TYPE_PLA, PLA_LED_FEATURE, ocp_data);

	ocp_data = FIFO_EMPTY_1FB | ROK_EXIT_LPM;
	if (tp->version == RTL_VER_04 && tp->udev->speed < USB_SPEED_SUPER)
		ocp_data |= LPM_TIMER_500MS;
	else
		ocp_data |= LPM_TIMER_500US;
	ocp_write_byte(tp, MCU_TYPE_USB, USB_LPM_CTRL, ocp_data);

	ocp_data = ocp_read_word(tp, MCU_TYPE_USB, USB_AFE_CTRL2);
	ocp_data &= ~SEN_VAL_MASK;
	ocp_data |= SEN_VAL_NORMAL | SEL_RXIDLE;
	ocp_write_word(tp, MCU_TYPE_USB, USB_AFE_CTRL2, ocp_data);

	ocp_write_word(tp, MCU_TYPE_USB, USB_CONNECT_TIMER, 0x0001);

	r8153_power_cut_en(tp, false);
	rtl_runtime_suspend_enable(tp, false);
	r8153_mac_clk_speed_down(tp, false);
	r8153_u1u2en(tp, true);
	usb_enable_lpm(tp->udev);

	ocp_data = ocp_read_byte(tp, MCU_TYPE_PLA, PLA_CONFIG6);
	ocp_data |= LANWAKE_CLR_EN;
	ocp_write_byte(tp, MCU_TYPE_PLA, PLA_CONFIG6, ocp_data);

	ocp_data = ocp_read_byte(tp, MCU_TYPE_PLA, PLA_LWAKE_CTRL_REG);
	ocp_data &= ~LANWAKE_PIN;
	ocp_write_byte(tp, MCU_TYPE_PLA, PLA_LWAKE_CTRL_REG, ocp_data);

	/* rx aggregation */
	ocp_data = ocp_read_word(tp, MCU_TYPE_USB, USB_USB_CTRL);
	ocp_data &= ~(RX_AGG_DISABLE | RX_ZERO_EN);
	ocp_write_word(tp, MCU_TYPE_USB, USB_USB_CTRL, ocp_data);

	rtl_tally_reset(tp);

	switch (tp->udev->speed) {
	case USB_SPEED_SUPER:
#if LINUX_VERSION_CODE >= KERNEL_VERSION(4,6,0)
	case USB_SPEED_SUPER_PLUS:
#endif
		tp->coalesce = COALESCE_SUPER;
		break;
	case USB_SPEED_HIGH:
		tp->coalesce = COALESCE_HIGH;
		break;
	default:
		tp->coalesce = COALESCE_SLOW;
		break;
	}
}

static void r8153b_init(struct r8152 *tp)
{
	u32 ocp_data;
	u16 data;
	int i;

	if (test_bit(RTL8152_UNPLUG, &tp->flags))
		return;

	rtl_set_dbg_info_init(tp);
	r8153b_u1u2en(tp, false);
	rtl_disable_spi(tp);

	for (i = 0; i < 500; i++) {
		if (ocp_read_word(tp, MCU_TYPE_PLA, PLA_BOOT_CTRL) &
		    AUTOLOAD_DONE)
			break;

		msleep(20);
		if (test_bit(RTL8152_UNPLUG, &tp->flags))
			break;
	}

	data = r8153_phy_status(tp, 0);

	data = r8152_mdio_read(tp, MII_BMCR);
	if (data & BMCR_PDOWN) {
		data &= ~BMCR_PDOWN;
		r8152_mdio_write(tp, MII_BMCR, data);
	}

	data = r8153_phy_status(tp, PHY_STAT_LAN_ON);

	r8153_u2p3en(tp, false);

	/* MSC timer = 0xfff * 8ms = 32760 ms */
	ocp_write_word(tp, MCU_TYPE_USB, USB_MSC_TIMER, 0x0fff);

	r8153b_power_cut_en(tp, false);
	r8153b_ups_en(tp, false);
	r8153_queue_wake(tp, false);
	rtl_runtime_suspend_enable(tp, false);

	ocp_data = ocp_read_word(tp, MCU_TYPE_PLA, PLA_EXTRA_STATUS);
	if (rtl8152_get_speed(tp) & LINK_STATUS)
		ocp_data |= CUR_LINK_OK;
	else
		ocp_data &= ~CUR_LINK_OK;

	/* r8153_queue_wake() has set this bit */
	/* ocp_data &= ~BIT(8); */

	ocp_data |= POLL_LINK_CHG;
	ocp_write_word(tp, MCU_TYPE_PLA, PLA_EXTRA_STATUS, ocp_data);

	ocp_data = ocp_read_byte(tp, MCU_TYPE_PLA, PLA_CONFIG6);
	ocp_data |= LANWAKE_CLR_EN;
	ocp_write_byte(tp, MCU_TYPE_PLA, PLA_CONFIG6, ocp_data);

	ocp_data = ocp_read_byte(tp, MCU_TYPE_PLA, PLA_LWAKE_CTRL_REG);
	ocp_data &= ~LANWAKE_PIN;
	ocp_write_byte(tp, MCU_TYPE_PLA, PLA_LWAKE_CTRL_REG, ocp_data);

	ocp_data = ocp_read_byte(tp, MCU_TYPE_PLA, PLA_CONFIG6);
	ocp_data &= ~LANWAKE_CLR_EN;
	ocp_write_byte(tp, MCU_TYPE_PLA, PLA_CONFIG6, ocp_data);

	if (tp->udev->descriptor.idVendor == VENDOR_ID_LENOVO &&
	    tp->udev->descriptor.idProduct == 0x3069)
		ocp_write_word(tp, MCU_TYPE_USB, USB_SSPHYLINK2, 0x0c8c);

//	if (tp->udev->speed >= USB_SPEED_SUPER)
//		r8153b_u1u2en(tp, true);

	usb_enable_lpm(tp->udev);

	/* MAC clock speed down */
	r8153_mac_clk_speed_down(tp, true);

	r8153b_mcu_spdown_en(tp, false);

	if (tp->version == RTL_VER_09) {
		/* Disable Test IO for 32QFN */
		if (ocp_read_byte(tp, MCU_TYPE_PLA, 0xdc00) & BIT(5)) {
			ocp_data = ocp_read_word(tp, MCU_TYPE_PLA, PLA_PHY_PWR);
			ocp_data |= TEST_IO_OFF;
			ocp_write_word(tp, MCU_TYPE_PLA, PLA_PHY_PWR, ocp_data);
		}
	}

	set_bit(GREEN_ETHERNET, &tp->flags);

	/* rx aggregation */
	ocp_data = ocp_read_word(tp, MCU_TYPE_USB, USB_USB_CTRL);
	ocp_data &= ~(RX_AGG_DISABLE | RX_ZERO_EN);
	ocp_write_word(tp, MCU_TYPE_USB, USB_USB_CTRL, ocp_data);

	rtl_tally_reset(tp);

	tp->coalesce = 15000;	/* 15 us */
}

static void r8153c_init(struct r8152 *tp)
{
	u32 ocp_data;
	u16 data;
	int i;

	if (test_bit(RTL8152_UNPLUG, &tp->flags))
		return;

	r8153b_u1u2en(tp, false);

	rtl_disable_spi(tp);

	for (i = 0; i < 500; i++) {
		if (ocp_read_word(tp, MCU_TYPE_PLA, PLA_BOOT_CTRL) &
		    AUTOLOAD_DONE)
			break;

		msleep(20);
		if (test_bit(RTL8152_UNPLUG, &tp->flags))
			return;
	}

	data = r8153_phy_status(tp, 0);

	data = r8152_mdio_read(tp, MII_BMCR);
	if (data & BMCR_PDOWN) {
		data &= ~BMCR_PDOWN;
		r8152_mdio_write(tp, MII_BMCR, data);
	}

	data = r8153_phy_status(tp, PHY_STAT_LAN_ON);

	r8153_u2p3en(tp, false);

	/* MSC timer = 0xfff * 8ms = 32760 ms */
	ocp_write_word(tp, MCU_TYPE_USB, USB_MSC_TIMER, 0x0fff);

	r8153b_power_cut_en(tp, false);
	r8153c_ups_en(tp, false);
	r8153_queue_wake(tp, false);
	rtl_runtime_suspend_enable(tp, false);

	ocp_data = ocp_read_word(tp, MCU_TYPE_PLA, PLA_EXTRA_STATUS);
	if (rtl8152_get_speed(tp) & LINK_STATUS)
		ocp_data |= CUR_LINK_OK;
	else
		ocp_data &= ~CUR_LINK_OK;

	/* r8153_queue_wake() has set this bit */
	/* ocp_data &= ~BIT(8); */

	ocp_data |= POLL_LINK_CHG;
	ocp_write_word(tp, MCU_TYPE_PLA, PLA_EXTRA_STATUS, ocp_data);

	r8153b_u1u2en(tp, true);

	usb_enable_lpm(tp->udev);

	/* MAC clock speed down */
	r8153_mac_clk_speed_down(tp, true);

	ocp_data = ocp_read_byte(tp, MCU_TYPE_USB, USB_MISC_2);
	ocp_data &= ~BIT(7);
	ocp_write_byte(tp, MCU_TYPE_USB, USB_MISC_2, ocp_data);

	set_bit(GREEN_ETHERNET, &tp->flags);

	/* rx aggregation */
	ocp_data = ocp_read_word(tp, MCU_TYPE_USB, USB_USB_CTRL);
	ocp_data &= ~(RX_AGG_DISABLE | RX_ZERO_EN);
	ocp_write_word(tp, MCU_TYPE_USB, USB_USB_CTRL, ocp_data);

	rtl_tally_reset(tp);

	tp->coalesce = 15000;	/* 15 us */
}

static void r8156_patch_code(struct r8152 *tp)
{
	if (tp->version == RTL_TEST_01) {
		static u8 usb3_patch_t[] = {
			0x01, 0xe0, 0x05, 0xc7,
			0xf6, 0x65, 0x02, 0xc0,
			0x00, 0xb8, 0x40, 0x03,
			0x00, 0xd4, 0x00, 0x00 };

		rtl_clear_bp(tp, MCU_TYPE_USB);

		generic_ocp_write(tp, 0xe600, 0xff, sizeof(usb3_patch_t),
				  usb3_patch_t, MCU_TYPE_USB);

		ocp_write_word(tp, MCU_TYPE_USB, USB_BP_BA, 0xa000);
		ocp_write_word(tp, MCU_TYPE_USB, USB_BP_0, 0x033e);
//		ocp_write_word(tp, MCU_TYPE_USB, USB_BP_1, 0x0000);
//		ocp_write_word(tp, MCU_TYPE_USB, USB_BP_2, 0x0000);
//		ocp_write_word(tp, MCU_TYPE_USB, USB_BP_3, 0x0000);
//		ocp_write_word(tp, MCU_TYPE_USB, USB_BP_4, 0x0000);
//		ocp_write_word(tp, MCU_TYPE_USB, USB_BP_5, 0x0000);
//		ocp_write_word(tp, MCU_TYPE_USB, USB_BP_6, 0x0000);
//		ocp_write_word(tp, MCU_TYPE_USB, USB_BP_7, 0x0000);
//		ocp_write_word(tp, MCU_TYPE_USB, USB_BP_8, 0x0000);
//		ocp_write_word(tp, MCU_TYPE_USB, USB_BP_9, 0x0000);
//		ocp_write_word(tp, MCU_TYPE_USB, USB_BP_10, 0x0000);
//		ocp_write_word(tp, MCU_TYPE_USB, USB_BP_11, 0x0000);
//		ocp_write_word(tp, MCU_TYPE_USB, USB_BP_12, 0x0000);
//		ocp_write_word(tp, MCU_TYPE_USB, USB_BP_13, 0x0000);
//		ocp_write_word(tp, MCU_TYPE_USB, USB_BP_14, 0x0000);
//		ocp_write_word(tp, MCU_TYPE_USB, USB_BP_15, 0x0000);
		ocp_write_word(tp, MCU_TYPE_USB, USB_BP2_EN, 0x0001);
	} else if (tp->version == RTL_VER_11) {
		u32 ocp_data;
		static u8 usb_patch3_b[] = {
			0x10, 0xe0, 0x28, 0xe0,
			0x3d, 0xe0, 0x85, 0xe0,
			0x99, 0xe0, 0xb4, 0xe0,
			0xd4, 0xe0, 0xfa, 0xe0,
			0x20, 0xe1, 0x39, 0xe1,
			0x65, 0xe1, 0xab, 0xe1,
			0xba, 0xe1, 0xcc, 0xe1,
			0xe3, 0xe1, 0xc0, 0xe2,
			0x18, 0xc0, 0x00, 0x75,
			0xd8, 0x49, 0x0e, 0xf0,
			0x10, 0xc0, 0x10, 0xc5,
			0x00, 0x1e, 0x08, 0x9e,
			0x0c, 0x9d, 0x0e, 0xc6,
			0x0a, 0x9e, 0x8f, 0x1c,
			0x0e, 0x8c, 0x0e, 0x74,
			0xcf, 0x49, 0xfe, 0xf1,
			0x45, 0xe8, 0x02, 0xc0,
			0x00, 0xb8, 0xf0, 0x4b,
			0x00, 0xdc, 0x24, 0xe4,
			0x04, 0xe4, 0x80, 0x02,
			0x34, 0xd3, 0xff, 0xc3,
			0x60, 0x72, 0xa8, 0x49,
			0x0e, 0xf0, 0xf7, 0xc3,
			0xf7, 0xc2, 0x00, 0x1c,
			0x68, 0x9c, 0xf6, 0xc4,
			0x6a, 0x9c, 0x6c, 0x9a,
			0x8f, 0x1c, 0x6e, 0x8c,
			0x6e, 0x74, 0xcf, 0x49,
			0xfe, 0xf1, 0x2c, 0xe8,
			0x04, 0xc0, 0x02, 0xc2,
			0x00, 0xba, 0x9a, 0x3c,
			0x80, 0xc3, 0x26, 0xe8,
			0x23, 0xc7, 0x21, 0xc2,
			0xec, 0x9a, 0x00, 0x19,
			0xee, 0x89, 0xee, 0x71,
			0x9f, 0x49, 0xfe, 0xf1,
			0xea, 0x71, 0x9f, 0x49,
			0x14, 0xf0, 0xda, 0xc2,
			0xec, 0x9a, 0x00, 0x19,
			0xe8, 0x99, 0x81, 0x19,
			0xee, 0x89, 0xee, 0x71,
			0x9f, 0x49, 0xfe, 0xf1,
			0xd2, 0xc2, 0xec, 0x9a,
			0x00, 0x19, 0x98, 0x20,
			0xe8, 0x99, 0x82, 0x19,
			0xee, 0x89, 0xee, 0x71,
			0x9f, 0x49, 0xfe, 0xf1,
			0x06, 0xc3, 0x02, 0xc2,
			0x00, 0xba, 0x3e, 0x29,
			0x4c, 0xe8, 0x00, 0xdc,
			0x00, 0xd4, 0x00, 0xb4,
			0x04, 0xb4, 0x05, 0xb4,
			0x06, 0xb4, 0xbf, 0xc0,
			0x00, 0x75, 0xd9, 0x49,
			0x17, 0xf0, 0xb7, 0xc0,
			0xb8, 0xc5, 0x00, 0x1e,
			0x68, 0x23, 0x08, 0x9e,
			0x0c, 0x9d, 0x82, 0x1c,
			0x0e, 0x8c, 0x0e, 0x74,
			0xcf, 0x49, 0xfe, 0xf1,
			0xac, 0xc0, 0xad, 0xc5,
			0x11, 0x1e, 0x68, 0x23,
			0x08, 0x9e, 0x0c, 0x9d,
			0x82, 0x1c, 0x0e, 0x8c,
			0x0e, 0x74, 0xcf, 0x49,
			0xfe, 0xf1, 0x06, 0xb0,
			0x05, 0xb0, 0x04, 0xb0,
			0x00, 0xb0, 0x80, 0xff,
			0xa0, 0xc0, 0x00, 0x75,
			0xd8, 0x49, 0x0d, 0xf0,
			0x98, 0xc0, 0x98, 0xc5,
			0x00, 0x1e, 0x08, 0x9e,
			0x97, 0xc6, 0x0a, 0x9e,
			0x0c, 0x9d, 0x8f, 0x1c,
			0x0e, 0x8c, 0x0e, 0x74,
			0xcf, 0x49, 0xfe, 0xf1,
			0x04, 0xc0, 0x02, 0xc1,
			0x00, 0xb9, 0x00, 0x1d,
			0x20, 0xd4, 0xc8, 0xef,
			0x8a, 0xc0, 0x00, 0x75,
			0xd8, 0x48, 0x00, 0x9d,
			0xc1, 0xc7, 0x15, 0xc2,
			0xec, 0x9a, 0x00, 0x19,
			0xe8, 0x9a, 0x81, 0x19,
			0xee, 0x89, 0xee, 0x71,
			0x9f, 0x49, 0xfe, 0xf1,
			0x2d, 0xc1, 0xec, 0x99,
			0x81, 0x19, 0xee, 0x89,
			0xee, 0x71, 0x9f, 0x49,
			0xfe, 0xf1, 0x04, 0xc3,
			0x02, 0xc2, 0x00, 0xba,
			0x3a, 0x27, 0xc0, 0xd4,
			0x24, 0xe4, 0xc0, 0x88,
			0x1e, 0xc6, 0xc0, 0x70,
			0x8f, 0x49, 0x0e, 0xf0,
			0x8f, 0x48, 0x68, 0xc6,
			0xca, 0x98, 0x11, 0x18,
			0xc8, 0x98, 0x16, 0xc0,
			0xcc, 0x98, 0x8f, 0x18,
			0xce, 0x88, 0xce, 0x70,
			0x8f, 0x49, 0xfe, 0xf1,
			0x0b, 0xe0, 0x5c, 0xc6,
			0x00, 0x18, 0xc8, 0x98,
			0x0b, 0xc0, 0xcc, 0x98,
			0x81, 0x18, 0xce, 0x88,
			0xce, 0x70, 0x8f, 0x49,
			0xfe, 0xf1, 0x02, 0xc0,
			0x00, 0xb8, 0xbc, 0x21,
			0x40, 0xd3, 0x20, 0xe4,
			0x4c, 0xc2, 0x40, 0x71,
			0x98, 0x48, 0x99, 0x48,
			0x40, 0x99, 0x48, 0xc2,
			0x00, 0x19, 0x98, 0x20,
			0x48, 0x99, 0x1d, 0xc1,
			0x4c, 0x99, 0x82, 0x19,
			0x4e, 0x89, 0x4e, 0x71,
			0x9f, 0x49, 0xfe, 0xf1,
			0x3d, 0xc2, 0x00, 0x19,
			0x48, 0x99, 0xec, 0xc1,
			0x4c, 0x99, 0x81, 0x19,
			0x4e, 0x89, 0x4e, 0x71,
			0x9f, 0x49, 0xfe, 0xf1,
			0x0b, 0xc1, 0x4c, 0x99,
			0x81, 0x19, 0x4e, 0x89,
			0x4e, 0x71, 0x9f, 0x49,
			0xfe, 0xf1, 0x02, 0x71,
			0x02, 0xc2, 0x00, 0xba,
			0xfe, 0x4e, 0x24, 0xe4,
			0x04, 0xe4, 0x25, 0xc2,
			0x40, 0x71, 0x98, 0x48,
			0x99, 0x48, 0x40, 0x99,
			0x21, 0xc2, 0x00, 0x19,
			0x98, 0x20, 0x48, 0x99,
			0xf6, 0xc1, 0x4c, 0x99,
			0x82, 0x19, 0x4e, 0x89,
			0x4e, 0x71, 0x9f, 0x49,
			0xfe, 0xf1, 0x16, 0xc2,
			0x00, 0x19, 0x48, 0x99,
			0xc5, 0xc1, 0x4c, 0x99,
			0x81, 0x19, 0x4e, 0x89,
			0x4e, 0x71, 0x9f, 0x49,
			0xfe, 0xf1, 0xe4, 0xc1,
			0x4c, 0x99, 0x81, 0x19,
			0x4e, 0x89, 0x4e, 0x71,
			0x9f, 0x49, 0xfe, 0xf1,
			0x02, 0x71, 0x02, 0xc2,
			0x00, 0xba, 0x00, 0x4e,
			0x34, 0xd3, 0x00, 0xdc,
			0x3d, 0xef, 0x18, 0xc0,
			0x00, 0x72, 0xa8, 0x49,
			0x0d, 0xf0, 0x11, 0xc0,
			0x11, 0xc2, 0x00, 0x19,
			0x08, 0x99, 0x0c, 0x9a,
			0x0e, 0xc1, 0x0a, 0x99,
			0x8f, 0x1b, 0x0e, 0x8b,
			0x0e, 0x73, 0xbf, 0x49,
			0xfe, 0xf1, 0x04, 0xc0,
			0x02, 0xc2, 0x00, 0xba,
			0x64, 0x62, 0x02, 0xcf,
			0x00, 0xdc, 0x24, 0xe4,
			0x80, 0x02, 0x34, 0xd3,
			0x2c, 0xc3, 0x60, 0x70,
			0x80, 0x49, 0xfd, 0xf0,
			0x27, 0xc3, 0x66, 0x60,
			0x80, 0x48, 0x02, 0x48,
			0x66, 0x88, 0x00, 0x48,
			0x82, 0x48, 0x66, 0x88,
			0x1b, 0xc3, 0x60, 0x70,
			0x17, 0xc4, 0x88, 0x98,
			0x14, 0xc0, 0x8c, 0x98,
			0x83, 0x18, 0x8e, 0x88,
			0x8e, 0x70, 0x8f, 0x49,
			0xfe, 0xf1, 0x62, 0x70,
			0x8a, 0x98, 0x0d, 0xc0,
			0x8c, 0x98, 0x84, 0x18,
			0x8e, 0x88, 0x8e, 0x70,
			0x8f, 0x49, 0xfe, 0xf1,
			0x08, 0xc3, 0x02, 0xc4,
			0x00, 0xbc, 0x68, 0x0f,
			0x6c, 0xe9, 0x00, 0xdc,
			0x50, 0xe8, 0x30, 0xc1,
			0x36, 0xd3, 0x80, 0x10,
			0x00, 0x00, 0x80, 0xd4,
			0x26, 0xd8, 0x44, 0xc2,
			0x4a, 0x41, 0x94, 0x20,
			0x42, 0xc0, 0x16, 0x00,
			0x00, 0x73, 0x40, 0xc4,
			0x5c, 0x41, 0x8b, 0x41,
			0x0b, 0x18, 0x38, 0xc6,
			0xc0, 0x88, 0xc1, 0x99,
			0x21, 0xe8, 0x35, 0xc0,
			0x00, 0x73, 0xbd, 0x48,
			0x0d, 0x18, 0x30, 0xc6,
			0xc0, 0x88, 0xc1, 0x9b,
			0x19, 0xe8, 0x2d, 0xc0,
			0x02, 0x73, 0x35, 0x48,
			0x0e, 0x18, 0x28, 0xc6,
			0xc0, 0x88, 0xc1, 0x9b,
			0x11, 0xe8, 0xdf, 0xc3,
			0xdd, 0xc6, 0x01, 0x03,
			0x1e, 0x40, 0xfe, 0xf1,
			0x20, 0xc0, 0x02, 0x73,
			0xb5, 0x48, 0x0e, 0x18,
			0x1b, 0xc6, 0xc0, 0x88,
			0xc1, 0x9b, 0x04, 0xe8,
			0x02, 0xc6, 0x00, 0xbe,
			0xb6, 0x10, 0x00, 0xb4,
			0x01, 0xb4, 0x02, 0xb4,
			0x03, 0xb4, 0x10, 0xc3,
			0x0e, 0xc2, 0x61, 0x71,
			0x40, 0x99, 0x60, 0x60,
			0x0e, 0x48, 0x42, 0x98,
			0x42, 0x70, 0x8e, 0x49,
			0xfe, 0xf1, 0x03, 0xb0,
			0x02, 0xb0, 0x01, 0xb0,
			0x00, 0xb0, 0x80, 0xff,
			0xc0, 0xd4, 0x8f, 0xcb,
			0xaa, 0xc7, 0x1e, 0x00,
			0x90, 0xc7, 0x1f, 0xfe,
			0x0a, 0x10, 0x0c, 0xf0,
			0x0b, 0x10, 0x0a, 0xf0,
			0x0d, 0x10, 0x08, 0xf0,
			0x0e, 0x10, 0x06, 0xf0,
			0x24, 0x10, 0x04, 0xf0,
			0x02, 0xc7, 0x00, 0xbf,
			0x58, 0x11, 0x02, 0xc7,
			0x00, 0xbf, 0x62, 0x11,
			0xec, 0xc0, 0x02, 0x75,
			0xd5, 0x48, 0x0e, 0x18,
			0xe7, 0xc6, 0xc0, 0x88,
			0xc1, 0x9d, 0xd0, 0xef,
			0xe4, 0xc0, 0x02, 0x75,
			0x55, 0x48, 0x0e, 0x18,
			0xdf, 0xc6, 0xc0, 0x88,
			0xc1, 0x9d, 0xc8, 0xef,
			0x02, 0xc7, 0x00, 0xbf,
			0x8e, 0x11, 0x16, 0xc0,
			0xbb, 0x21, 0xb9, 0x25,
			0x00, 0x71, 0x13, 0xc2,
			0x4a, 0x41, 0x8b, 0x41,
			0x24, 0x18, 0xd0, 0xc6,
			0xc0, 0x88, 0xc1, 0x99,
			0xb9, 0xef, 0x0a, 0xc0,
			0x08, 0x71, 0x28, 0x18,
			0xc9, 0xc6, 0xc0, 0x88,
			0xc1, 0x99, 0xb2, 0xef,
			0x02, 0xc0, 0x00, 0xb8,
			0x3c, 0x11, 0xd8, 0xc7,
			0x83, 0xff, 0x01, 0xb4,
			0x02, 0xb4, 0x03, 0xb4,
			0x04, 0xb4, 0x05, 0xb4,
			0x43, 0xc4, 0x44, 0xc0,
			0x47, 0xc1, 0x81, 0x1b,
			0xcd, 0xe8, 0x45, 0xc0,
			0x43, 0xc2, 0x84, 0x1b,
			0xc9, 0xe8, 0x58, 0xc0,
			0x00, 0x1b, 0xc6, 0xe8,
			0x80, 0x65, 0xdb, 0x22,
			0xdd, 0x26, 0x03, 0x15,
			0x12, 0xf1, 0x4d, 0xc0,
			0x36, 0xc1, 0x81, 0x1b,
			0xbd, 0xe8, 0x4a, 0xc0,
			0x31, 0xc1, 0x88, 0x1b,
			0xb9, 0xe8, 0x47, 0xc0,
			0x48, 0xc1, 0x81, 0x1b,
			0xb5, 0xe8, 0x04, 0x00,
			0x45, 0xc1, 0x45, 0xc2,
			0x8f, 0x1b, 0xb0, 0xe8,
			0x24, 0xc0, 0x28, 0xc1,
			0x2a, 0xc2, 0xac, 0xe8,
			0x04, 0x00, 0x3e, 0xc1,
			0x27, 0xc2, 0xa8, 0xe8,
			0x04, 0x00, 0x2b, 0xc1,
			0x2b, 0xc2, 0xa4, 0xe8,
			0x04, 0x00, 0x29, 0xc1,
			0x2b, 0xc2, 0xa0, 0xe8,
			0x04, 0x00, 0x26, 0xc1,
			0x26, 0xc2, 0x9c, 0xe8,
			0x04, 0x00, 0x24, 0xc1,
			0x21, 0xc2, 0x98, 0xe8,
			0x04, 0x00, 0x21, 0xc1,
			0x1f, 0xc2, 0x94, 0xe8,
			0x04, 0x00, 0x1a, 0xc1,
			0x1d, 0xc2, 0x90, 0xe8,
			0x3d, 0xe0, 0x08, 0xdc,
			0x3c, 0xe8, 0x14, 0xe8,
			0x00, 0xf8, 0x00, 0x40,
			0x00, 0x00, 0x01, 0x00,
			0x9a, 0xd3, 0x04, 0xe0,
			0x02, 0xe0, 0x0b, 0xe0,
			0x0c, 0xe0, 0x25, 0xe0,
			0xef, 0x1f, 0xa8, 0x8f,
			0x02, 0xc7, 0x00, 0xbf,
			0x76, 0x15, 0x66, 0x15,
			0xa0, 0x49, 0x05, 0xf1,
			0xa4, 0x49, 0x00, 0xbe,
			0xca, 0x1a, 0x02, 0xc6,
			0xe0, 0x1a, 0xce, 0x13,
			0x80, 0xe0, 0xcb, 0xe0,
			0xe0, 0xe8, 0x28, 0xdc,
			0x13, 0x00, 0x08, 0x11,
			0x42, 0x80, 0x0e, 0xe0,
			0x06, 0xb4, 0x84, 0x76,
			0x31, 0x40, 0x82, 0x71,
			0x0c, 0xe8, 0x81, 0x24,
			0x1f, 0x48, 0x84, 0x99,
			0x08, 0xe8, 0x80, 0x49,
			0x03, 0xf1, 0x80, 0x71,
			0x80, 0xff, 0x85, 0x61,
			0x96, 0x24, 0xfd, 0xf1,
			0x06, 0xb0, 0x00, 0x11,
			0x6c, 0x0f, 0x34, 0x1c,
			0x28, 0xfc, 0x38, 0xfc,
			0x0f, 0x00, 0xc8, 0x1a,
			0xbe, 0x13, 0x04, 0x00,
			0xe6, 0xc1, 0xea, 0xc2,
			0x4f, 0xe8, 0x04, 0x00,
			0xe3, 0xc1, 0xe3, 0xc2,
			0x4b, 0xe8, 0x04, 0x00,
			0xe8, 0xc1, 0xe0, 0xc2,
			0x47, 0xe8, 0x04, 0x00,
			0xc1, 0xc1, 0xdd, 0xc2,
			0x43, 0xe8, 0x04, 0x00,
			0xdb, 0xc1, 0xdb, 0xc2,
			0x3f, 0xe8, 0x04, 0x00,
			0xd9, 0xc1, 0xd9, 0xc2,
			0x3b, 0xe8, 0x04, 0x00,
			0xd7, 0xc1, 0xd7, 0xc2,
			0x37, 0xe8, 0x04, 0x00,
			0xd5, 0xc1, 0xaf, 0xc2,
			0x33, 0xe8, 0x04, 0x00,
			0xc9, 0xc1, 0xd5, 0xc2,
			0x2f, 0xe8, 0x04, 0x00,
			0xce, 0xc1, 0xce, 0xc2,
			0x2b, 0xe8, 0x04, 0x00,
			0xcc, 0xc1, 0xce, 0xc2,
			0x27, 0xe8, 0x04, 0x00,
			0xc9, 0xc1, 0xc5, 0xc2,
			0x23, 0xe8, 0x04, 0x00,
			0xa0, 0xc1, 0xa0, 0xc2,
			0x1f, 0xe8, 0x04, 0x00,
			0x9e, 0xc1, 0x9e, 0xc2,
			0x1b, 0xe8, 0x04, 0x00,
			0x9c, 0xc1, 0x83, 0x1b,
			0x17, 0xe8, 0xbf, 0xc0,
			0xc1, 0xc1, 0xc1, 0xc2,
			0x8f, 0x1b, 0x12, 0xe8,
			0x04, 0x00, 0xb8, 0xc1,
			0x93, 0xc2, 0x8f, 0x1b,
			0x0d, 0xe8, 0xb6, 0xc0,
			0xb6, 0xc1, 0x81, 0x1b,
			0x09, 0xe8, 0x05, 0xb0,
			0x04, 0xb0, 0x03, 0xb0,
			0x02, 0xb0, 0x01, 0xb0,
			0x60, 0x70, 0xa9, 0xc3,
			0x00, 0xbb, 0x84, 0x98,
			0x80, 0x99, 0x82, 0x9a,
			0x86, 0x8b, 0x86, 0x75,
			0xdf, 0x49, 0xfe, 0xf1,
			0x80, 0xff, 0x02, 0xc0,
			0x00, 0xb8, 0x00, 0x00};
		static u8 pla_patch11[] = {
			0x05, 0xe0, 0x0a, 0xe0,
			0x38, 0xe0, 0x3a, 0xe0,
			0x57, 0xe0, 0x05, 0xc2,
			0x40, 0x76, 0x02, 0xc4,
			0x00, 0xbc, 0xd6, 0x0b,
			0x1e, 0xfc, 0x29, 0xc5,
			0xa0, 0x77, 0x2b, 0xc4,
			0xa0, 0x9c, 0x26, 0xc5,
			0xa0, 0x64, 0x01, 0x14,
			0x0b, 0xf0, 0x02, 0x14,
			0x09, 0xf0, 0x01, 0x07,
			0xf1, 0x49, 0x06, 0xf0,
			0x21, 0xc7, 0xe0, 0x8e,
			0x11, 0x1e, 0xe0, 0x8e,
			0x14, 0xe0, 0x17, 0xc5,
			0x00, 0x1f, 0xa0, 0x9f,
			0x13, 0xc5, 0xa0, 0x77,
			0xa0, 0x74, 0x46, 0x48,
			0x47, 0x48, 0xa0, 0x9c,
			0x11, 0xc5, 0xa0, 0x74,
			0x44, 0x48, 0x43, 0x48,
			0xa0, 0x9c, 0x08, 0xc5,
			0xa0, 0x9f, 0x02, 0xc5,
			0x00, 0xbd, 0xea, 0x03,
			0x02, 0xc5, 0x00, 0xbd,
			0xf6, 0x03, 0x1c, 0xe8,
			0xaa, 0xd3, 0x08, 0xb7,
			0x6c, 0xe8, 0x20, 0xe8,
			0x00, 0xa0, 0x38, 0xe4,
			0x02, 0xc5, 0x00, 0xbd,
			0xcc, 0x06, 0xd4, 0x49,
			0x17, 0xf0, 0x19, 0xc5,
			0xa4, 0x64, 0xc1, 0x49,
			0x07, 0xf1, 0x16, 0xc5,
			0xa0, 0x64, 0xc7, 0x48,
			0x46, 0x48, 0xa0, 0x8c,
			0x06, 0xe0, 0x10, 0xc5,
			0xa0, 0x64, 0x47, 0x48,
			0xc6, 0x48, 0xa0, 0x8c,
			0x0c, 0xc7, 0xe0, 0x8e,
			0x11, 0x1e, 0xe0, 0x8e,
			0x02, 0xc7, 0x00, 0xbf,
			0x88, 0x04, 0x02, 0xc7,
			0x00, 0xbf, 0xbe, 0x03,
			0x5c, 0xdc, 0xf0, 0xd3,
			0x20, 0xe4, 0xd2, 0x49,
			0x08, 0xf1, 0xd3, 0x49,
			0x55, 0xf1, 0xd4, 0x49,
			0x1e, 0xf1, 0xd5, 0x49,
			0x45, 0xf1, 0x4d, 0xe0,
			0x5a, 0xc7, 0xe0, 0x72,
			0xa0, 0x49, 0x05, 0xf0,
			0x54, 0xc7, 0xe0, 0x72,
			0xaf, 0x49, 0x0e, 0xf1,
			0x53, 0xc7, 0xff, 0x1a,
			0xe0, 0x9a, 0x51, 0xc2,
			0xe4, 0x9a, 0x50, 0xc2,
			0xe6, 0x9a, 0x01, 0x1a,
			0xe0, 0x9a, 0x4d, 0xc2,
			0xe4, 0x9a, 0x4a, 0xc2,
			0xe6, 0x9a, 0x44, 0xc7,
			0xe5, 0x8e, 0x00, 0x1d,
			0xe5, 0x8d, 0x30, 0xe0,
			0x38, 0xc7, 0xe0, 0x75,
			0xda, 0x49, 0x1f, 0xf0,
			0x35, 0xc7, 0xe0, 0x75,
			0xdc, 0x49, 0x1b, 0xf1,
			0x32, 0xc7, 0xe0, 0x75,
			0xd5, 0x49, 0x17, 0xf0,
			0x39, 0xc7, 0xe0, 0x75,
			0xd8, 0x48, 0xd9, 0x48,
			0xda, 0x48, 0xdb, 0x48,
			0xe0, 0x9d, 0x2a, 0xc7,
			0xe0, 0x75, 0xdb, 0x49,
			0x03, 0xf1, 0xde, 0x49,
			0x0d, 0xf0, 0x22, 0xc7,
			0xe4, 0x75, 0xd0, 0x49,
			0x09, 0xf1, 0x1f, 0xc5,
			0xe6, 0x9d, 0x11, 0x1d,
			0xe4, 0x8d, 0x04, 0xe0,
			0x19, 0xc7, 0x00, 0x1d,
			0xe4, 0x8d, 0xe0, 0x8e,
			0x11, 0x1d, 0xe0, 0x8d,
			0x07, 0xe0, 0x0f, 0xc7,
			0xe0, 0x75, 0xda, 0x48,
			0xe0, 0x9d, 0x0e, 0xc7,
			0xe4, 0x8e, 0x02, 0xc4,
			0x00, 0xbc, 0xd6, 0x03,
			0x02, 0xc4, 0x00, 0xbc,
			0xc2, 0x03, 0x02, 0xc4,
			0x00, 0xbc, 0x5a, 0x04,
			0x12, 0xe8, 0x4e, 0xe8,
			0x08, 0xe9, 0x20, 0xe4,
			0x80, 0x02, 0x9a, 0xc0,
			0x4e, 0xe8, 0x00, 0xe4,
			0x10, 0xe0, 0xe0, 0xe8,
			0x80, 0x11, 0x02, 0x80,
			0x30, 0x10, 0xb4, 0xc0};

		rtl_clear_bp(tp, MCU_TYPE_USB);

		generic_ocp_write(tp, 0xe600, 0xff, sizeof(usb_patch3_b),
				  usb_patch3_b, MCU_TYPE_USB);

		ocp_write_word(tp, MCU_TYPE_USB, USB_BP_BA, 0xa000);
		ocp_write_word(tp, MCU_TYPE_USB, USB_BP_0, 0x39d4);
		ocp_write_word(tp, MCU_TYPE_USB, USB_BP_1, 0x3c98);
		ocp_write_word(tp, MCU_TYPE_USB, USB_BP_2, 0x293c);
		ocp_write_word(tp, MCU_TYPE_USB, USB_BP_3, 0x1cfe);
		ocp_write_word(tp, MCU_TYPE_USB, USB_BP_4, 0x2738);
		ocp_write_word(tp, MCU_TYPE_USB, USB_BP_5, 0x21ba);
		ocp_write_word(tp, MCU_TYPE_USB, USB_BP_6, 0x4efc);
		ocp_write_word(tp, MCU_TYPE_USB, USB_BP_7, 0x4dfe);
		ocp_write_word(tp, MCU_TYPE_USB, USB_BP_8, 0x6262);
		ocp_write_word(tp, MCU_TYPE_USB, USB_BP_9, 0x0f66);
		ocp_write_word(tp, MCU_TYPE_USB, USB_BP_10, 0x1098);
		ocp_write_word(tp, MCU_TYPE_USB, USB_BP_11, 0x1148);
		ocp_write_word(tp, MCU_TYPE_USB, USB_BP_12, 0x116c);
		ocp_write_word(tp, MCU_TYPE_USB, USB_BP_13, 0x10e0);
		ocp_write_word(tp, MCU_TYPE_USB, USB_BP_14, 0x0f6a);
		ocp_write_word(tp, MCU_TYPE_USB, USB_BP_15, 0x0000);
		ocp_write_word(tp, MCU_TYPE_USB, USB_BP2_EN, 0x7fff);
		ocp_write_byte(tp, MCU_TYPE_USB, 0xcfd7, 0x04);

		ocp_data = ocp_read_word(tp, MCU_TYPE_USB, USB_FW_FIX_EN1);
		ocp_data |= FW_IP_RESET_EN;
		ocp_write_word(tp, MCU_TYPE_USB, USB_FW_FIX_EN1, ocp_data);

		ocp_write_dword(tp, MCU_TYPE_USB, USB_UPHY3_MDCMDIO, 0x4026840e);
		ocp_write_dword(tp, MCU_TYPE_USB, USB_UPHY3_MDCMDIO, 0x4001acc9);

		rtl_clear_bp(tp, MCU_TYPE_PLA);

		generic_ocp_write(tp, 0xf800, 0xff, sizeof(pla_patch11),
				  pla_patch11, MCU_TYPE_PLA);

		ocp_write_word(tp, MCU_TYPE_PLA, PLA_BP_BA, 0x8000);
		ocp_write_word(tp, MCU_TYPE_PLA, PLA_BP_0, 0x0bc2);
		ocp_write_word(tp, MCU_TYPE_PLA, PLA_BP_1, 0x03e0);
		ocp_write_word(tp, MCU_TYPE_PLA, PLA_BP_2, 0x06b8);
		ocp_write_word(tp, MCU_TYPE_PLA, PLA_BP_3, 0x03ba);
		ocp_write_word(tp, MCU_TYPE_PLA, PLA_BP_4, 0x03b2);
		ocp_write_word(tp, MCU_TYPE_PLA, PLA_BP_5, 0x0000);
		ocp_write_word(tp, MCU_TYPE_PLA, PLA_BP_6, 0x0000);
		ocp_write_word(tp, MCU_TYPE_PLA, PLA_BP_7, 0x0000);
		ocp_write_word(tp, MCU_TYPE_PLA, PLA_BP_EN, 0x0017);
		ocp_write_byte(tp, MCU_TYPE_USB, 0xcfd6, 0x06);
	} else if (tp->version == RTL_VER_12) {
		static u8 usb_patch4_a[] = {
			0x10, 0xe0, 0x38, 0xe0,
			0x4e, 0xe0, 0x8b, 0xe0,
			0xc1, 0xe0, 0xcd, 0xe0,
			0xd5, 0xe0, 0xed, 0xe0,
			0xf9, 0xe0, 0xfb, 0xe0,
			0xfd, 0xe0, 0xff, 0xe0,
			0x01, 0xe1, 0x03, 0xe1,
			0x05, 0xe1, 0x07, 0xe1,
			0x22, 0xc2, 0x4a, 0x41,
			0x91, 0x20, 0x20, 0xc0,
			0x16, 0x00, 0x00, 0x73,
			0x1e, 0xc4, 0x5c, 0x41,
			0x8b, 0x41, 0x1a, 0xc0,
			0x1a, 0x00, 0x00, 0x73,
			0xbd, 0x48, 0x0d, 0x18,
			0x17, 0xc6, 0xc0, 0x88,
			0xc1, 0x9b, 0x15, 0xe8,
			0x0b, 0x18, 0x12, 0xc6,
			0xc0, 0x88, 0xc1, 0x99,
			0x10, 0xe8, 0x0c, 0xc0,
			0x1c, 0x00, 0x00, 0x73,
			0x0e, 0x18, 0x0a, 0xc6,
			0xc0, 0x88, 0xc1, 0x9b,
			0x08, 0xe8, 0x02, 0xc6,
			0x00, 0xbe, 0x10, 0x12,
			0xf0, 0x00, 0x90, 0xc7,
			0x1f, 0xfe, 0x8f, 0xcb,
			0x02, 0xc6, 0x00, 0xbe,
			0x66, 0x3f, 0x11, 0x21,
			0x2b, 0x25, 0x13, 0xc4,
			0xa2, 0x41, 0x80, 0x63,
			0xf5, 0xc0, 0x48, 0x00,
			0xbb, 0x21, 0xb9, 0x25,
			0x00, 0x71, 0x0c, 0xc2,
			0x4a, 0x41, 0x8b, 0x41,
			0x24, 0x18, 0xee, 0xc6,
			0xc0, 0x88, 0xc1, 0x99,
			0xec, 0xef, 0x02, 0xc6,
			0x00, 0xbe, 0x8a, 0x12,
			0xa0, 0xf9, 0x83, 0xff,
			0xd4, 0x18, 0x20, 0x88,
			0x36, 0xe8, 0x22, 0x60,
			0x85, 0x48, 0x06, 0x48,
			0x21, 0x88, 0xf4, 0x18,
			0x20, 0x88, 0x32, 0xe8,
			0x2d, 0xc3, 0xc0, 0x18,
			0x20, 0x88, 0x2b, 0xe8,
			0x22, 0x60, 0x60, 0x88,
			0xc1, 0x18, 0x20, 0x88,
			0x26, 0xe8, 0x22, 0x60,
			0x61, 0x88, 0xc2, 0x18,
			0x20, 0x88, 0x21, 0xe8,
			0x22, 0x60, 0x62, 0x88,
			0xc3, 0x18, 0x20, 0x88,
			0x1c, 0xe8, 0x22, 0x60,
			0x63, 0x88, 0xc4, 0x18,
			0x20, 0x88, 0x17, 0xe8,
			0x22, 0x60, 0x64, 0x88,
			0xc5, 0x18, 0x20, 0x88,
			0x12, 0xe8, 0x22, 0x60,
			0x65, 0x88, 0xc6, 0x18,
			0x20, 0x88, 0x0d, 0xe8,
			0x22, 0x60, 0x66, 0x88,
			0xc7, 0x18, 0x20, 0x88,
			0x08, 0xe8, 0x22, 0x60,
			0x67, 0x88, 0xd4, 0x18,
			0x02, 0xc5, 0x00, 0xbd,
			0xc2, 0x35, 0xc0, 0xd3,
			0x02, 0xc5, 0x00, 0xbd,
			0xb2, 0x3e, 0x02, 0xc5,
			0x00, 0xbd, 0x08, 0x3f,
			0xd4, 0x18, 0xc0, 0x88,
			0xf8, 0xef, 0xc2, 0x60,
			0x85, 0x48, 0x06, 0x48,
			0xc1, 0x88, 0xf4, 0x18,
			0xc0, 0x88, 0xf4, 0xef,
			0xef, 0xc3, 0x60, 0x60,
			0xc1, 0x88, 0xe0, 0x18,
			0xc0, 0x88, 0xee, 0xef,
			0x61, 0x60, 0xc1, 0x88,
			0xe1, 0x18, 0xc0, 0x88,
			0xe9, 0xef, 0x62, 0x60,
			0xc1, 0x88, 0xe2, 0x18,
			0xc0, 0x88, 0xe4, 0xef,
			0x63, 0x60, 0xc1, 0x88,
			0xe3, 0x18, 0xc0, 0x88,
			0xdf, 0xef, 0x64, 0x60,
			0xc1, 0x88, 0xe4, 0x18,
			0xc0, 0x88, 0xda, 0xef,
			0x65, 0x60, 0xc1, 0x88,
			0xe5, 0x18, 0xc0, 0x88,
			0xd5, 0xef, 0x66, 0x60,
			0xc1, 0x88, 0xe6, 0x18,
			0xc0, 0x88, 0xd0, 0xef,
			0x67, 0x60, 0xc1, 0x88,
			0xe7, 0x18, 0xc0, 0x88,
			0xcb, 0xef, 0xd4, 0x18,
			0x02, 0xc2, 0x00, 0xba,
			0x3a, 0x15, 0x0b, 0xc6,
			0xc7, 0x65, 0xd0, 0x49,
			0x05, 0xf1, 0x08, 0xc0,
			0x02, 0xc6, 0x00, 0xbe,
			0x50, 0x2f, 0x02, 0xc7,
			0x00, 0xbf, 0x56, 0x2f,
			0x20, 0xd4, 0x00, 0xd4,
			0x08, 0xc3, 0x60, 0x60,
			0x03, 0x48, 0x60, 0x88,
			0x00, 0x1b, 0x02, 0xc6,
			0x00, 0xbe, 0xda, 0x2c,
			0x60, 0xb4, 0x17, 0xc1,
			0x17, 0xc2, 0x4c, 0x99,
			0x00, 0x19, 0x4e, 0x89,
			0x4f, 0x61, 0x97, 0x49,
			0xfe, 0xf1, 0x48, 0x61,
			0x01, 0xb4, 0x16, 0x48,
			0x17, 0x48, 0x48, 0x89,
			0x0a, 0xc1, 0x4c, 0x99,
			0x81, 0x19, 0x4e, 0x89,
			0x4f, 0x61, 0x97, 0x49,
			0xfe, 0xf1, 0x02, 0xc0,
			0x00, 0xb8, 0x32, 0x7c,
			0x1c, 0xe8, 0x00, 0xdc,
			0x01, 0xb0, 0xfe, 0xc2,
			0x48, 0x89, 0xfb, 0xc1,
			0x4c, 0x99, 0x81, 0x19,
			0x4e, 0x89, 0x4f, 0x61,
			0x97, 0x49, 0xfe, 0xf1,
			0x02, 0xc0, 0x00, 0xb8,
			0x96, 0x7c, 0x02, 0xc0,
			0x00, 0xb8, 0x00, 0x00,
			0x02, 0xc0, 0x00, 0xb8,
			0x00, 0x00, 0x02, 0xc0,
			0x00, 0xb8, 0x00, 0x00,
			0x02, 0xc0, 0x00, 0xb8,
			0x00, 0x00, 0x02, 0xc0,
			0x00, 0xb8, 0x00, 0x00,
			0x02, 0xc0, 0x00, 0xb8,
			0x00, 0x00, 0x02, 0xc0,
			0x00, 0xb8, 0x00, 0x00,
			0x02, 0xc0, 0x00, 0xb8,
			0x00, 0x00, 0x00, 0x00};
		static u8 pla_patch4_a[] = {
			0x08, 0xe0, 0x0c, 0xe0,
			0x10, 0xe0, 0x3e, 0xe0,
			0x40, 0xe0, 0x42, 0xe0,
			0x44, 0xe0, 0x46, 0xe0,
			0x03, 0xb4, 0x02, 0xb4,
			0x02, 0xc7, 0x00, 0xbf,
			0xb4, 0x03, 0x02, 0xb0,
			0x03, 0xb0, 0x02, 0xc6,
			0x00, 0xbe, 0x8c, 0x05,
			0xaf, 0x49, 0x17, 0xf1,
			0x20, 0xc6, 0x00, 0x1a,
			0x23, 0xe8, 0x21, 0xc6,
			0xc0, 0x61, 0x91, 0x49,
			0x0c, 0xf0, 0x95, 0x49,
			0x0a, 0xf1, 0x14, 0x48,
			0x16, 0xc6, 0x81, 0x1a,
			0x19, 0xe8, 0x14, 0xc6,
			0xc0, 0x62, 0x24, 0x48,
			0xc0, 0x8a, 0x0c, 0xe0,
			0x10, 0xc6, 0xc0, 0x62,
			0xa5, 0x49, 0x08, 0xf1,
			0x0d, 0xc6, 0xc0, 0x62,
			0xa0, 0x48, 0xc0, 0x8a,
			0xc2, 0x62, 0xa3, 0x48,
			0xc2, 0x8a, 0x02, 0xc6,
			0x00, 0xbe, 0xd2, 0x16,
			0x84, 0xd2, 0x6a, 0xdc,
			0x90, 0xd3, 0x66, 0xb4,
			0x08, 0xea, 0xff, 0xc0,
			0x04, 0x9e, 0x00, 0x99,
			0x06, 0x8a, 0x06, 0x72,
			0xaf, 0x49, 0xfe, 0xf1,
			0x80, 0xff, 0x02, 0xc6,
			0x00, 0xbe, 0x00, 0x00,
			0x02, 0xc6, 0x00, 0xbe,
			0x00, 0x00, 0x02, 0xc6,
			0x00, 0xbe, 0x00, 0x00,
			0x02, 0xc6, 0x00, 0xbe,
			0x00, 0x00, 0x02, 0xc6,
			0x00, 0xbe, 0x00, 0x00};

		rtl_clear_bp(tp, MCU_TYPE_USB);

		generic_ocp_write(tp, 0xe600, 0xff, sizeof(usb_patch4_a),
				  usb_patch4_a, MCU_TYPE_USB);

		ocp_write_word(tp, MCU_TYPE_USB, USB_BP_BA, 0xc000);
		ocp_write_word(tp, MCU_TYPE_USB, USB_BP_0, 0x11e2);
		ocp_write_word(tp, MCU_TYPE_USB, USB_BP_1, 0x1268);
		ocp_write_word(tp, MCU_TYPE_USB, USB_BP_2, 0x35c0);
		ocp_write_word(tp, MCU_TYPE_USB, USB_BP_3, 0x1538);
		ocp_write_word(tp, MCU_TYPE_USB, USB_BP_4, 0x2f4e);
		ocp_write_word(tp, MCU_TYPE_USB, USB_BP_5, 0x2cd8);
		ocp_write_word(tp, MCU_TYPE_USB, USB_BP_6, 0x7c26);
		ocp_write_word(tp, MCU_TYPE_USB, USB_BP_7, 0x7c90);
		ocp_write_word(tp, MCU_TYPE_USB, USB_BP_8, 0x0000);
//		ocp_write_word(tp, MCU_TYPE_USB, USB_BP_9, 0x0000);
		ocp_write_word(tp, MCU_TYPE_USB, USB_BP_10, 0x0000);
		ocp_write_word(tp, MCU_TYPE_USB, USB_BP_11, 0x0000);
		ocp_write_word(tp, MCU_TYPE_USB, USB_BP_12, 0x0000);
		ocp_write_word(tp, MCU_TYPE_USB, USB_BP_13, 0x0000);
		ocp_write_word(tp, MCU_TYPE_USB, USB_BP_14, 0x0000);
		ocp_write_word(tp, MCU_TYPE_USB, USB_BP_15, 0x0000);
		ocp_write_word(tp, MCU_TYPE_USB, USB_BP2_EN, 0x00df);
		ocp_write_byte(tp, MCU_TYPE_USB, 0xcfd7, 0x02);

//		ocp_data = ocp_read_word(tp, MCU_TYPE_USB, USB_FW_FIX_EN1);
//		ocp_data |= FW_IP_RESET_EN;
//		ocp_write_word(tp, MCU_TYPE_USB, USB_FW_FIX_EN1, ocp_data);

//		ocp_write_dword(tp, MCU_TYPE_USB, 0xd480, 0x4026840e);
//		ocp_write_dword(tp, MCU_TYPE_USB, 0xd480, 0x4001acc9);

		rtl_clear_bp(tp, MCU_TYPE_PLA);

		generic_ocp_write(tp, 0xf800, 0xff, sizeof(pla_patch4_a),
				  pla_patch4_a, MCU_TYPE_PLA);

		ocp_write_word(tp, MCU_TYPE_PLA, PLA_BP_BA, 0x8000);
		ocp_write_word(tp, MCU_TYPE_PLA, PLA_BP_0, 0x03b2);
		ocp_write_word(tp, MCU_TYPE_PLA, PLA_BP_1, 0x058a);
		ocp_write_word(tp, MCU_TYPE_PLA, PLA_BP_2, 0x16c0);
		ocp_write_word(tp, MCU_TYPE_PLA, PLA_BP_3, 0x0000);
		ocp_write_word(tp, MCU_TYPE_PLA, PLA_BP_4, 0x0000);
		ocp_write_word(tp, MCU_TYPE_PLA, PLA_BP_5, 0x0000);
		ocp_write_word(tp, MCU_TYPE_PLA, PLA_BP_6, 0x0000);
		ocp_write_word(tp, MCU_TYPE_PLA, PLA_BP_7, 0x0000);
		ocp_write_word(tp, MCU_TYPE_PLA, PLA_BP_EN, 0x0007);
		ocp_write_byte(tp, MCU_TYPE_USB, 0xcfd6, 0x02);
	} else if (tp->version == RTL_VER_13 || tp->version == RTL_VER_15) {
		static u8 usb_patch_13[] = {
			0x10, 0xe0, 0x25, 0xe0,
			0x29, 0xe0, 0x2d, 0xe0,
			0x52, 0xe0, 0xff, 0xe0,
			0x02, 0xe1, 0x06, 0xe1,
			0x16, 0xe1, 0x18, 0xe1,
			0x39, 0xe1, 0x52, 0xe1,
			0x54, 0xe1, 0x56, 0xe1,
			0x58, 0xe1, 0x5a, 0xe1,
			0x13, 0xc3, 0x60, 0x70,
			0x8b, 0x49, 0x0d, 0xf1,
			0x10, 0xc3, 0x60, 0x60,
			0x85, 0x49, 0x09, 0xf1,
			0x40, 0x03, 0x64, 0x60,
			0x82, 0x49, 0x05, 0xf1,
			0x09, 0xc3, 0x60, 0x60,
			0x80, 0x48, 0x60, 0x88,
			0x02, 0xc0, 0x00, 0xb8,
			0xde, 0x0f, 0xca, 0xcf,
			0x00, 0xd8, 0x1e, 0xb4,
			0x04, 0xc3, 0x02, 0xc0,
			0x00, 0xb8, 0x62, 0x36,
			0xc8, 0xd3, 0x04, 0xc3,
			0x02, 0xc0, 0x00, 0xb8,
			0x7a, 0x14, 0xc8, 0xd3,
			0x00, 0xb4, 0x01, 0xb4,
			0x02, 0xb4, 0x03, 0xb4,
			0x1f, 0xc1, 0x02, 0x1b,
			0x2c, 0x8b, 0x0c, 0x62,
			0xa7, 0x49, 0x0a, 0xf1,
			0x00, 0x1b, 0x08, 0x72,
			0x13, 0x40, 0x04, 0xf1,
			0x0a, 0x72, 0x13, 0x40,
			0x03, 0xf0, 0x01, 0x1b,
			0x2c, 0x8b, 0x12, 0xc0,
			0x01, 0x1a, 0x08, 0x8a,
			0x0a, 0x8a, 0x0d, 0xc0,
			0x12, 0x71, 0x19, 0x48,
			0x1a, 0x48, 0x12, 0x99,
			0x03, 0xb0, 0x02, 0xb0,
			0x01, 0xb0, 0x00, 0xb0,
			0x02, 0xc0, 0x00, 0xb8,
			0xb0, 0x77, 0x20, 0xc3,
			0x18, 0xb4, 0x80, 0xcb,
			0x00, 0xb4, 0x01, 0xb4,
			0x02, 0xb4, 0x03, 0xb4,
			0x07, 0xb4, 0x23, 0xc0,
			0x24, 0xc1, 0x08, 0x1a,
			0x2a, 0x8a, 0x24, 0x01,
			0x0d, 0x1a, 0x20, 0x9a,
			0x24, 0x09, 0x00, 0x1a,
			0x22, 0x9a, 0x04, 0x72,
			0x06, 0x73, 0x18, 0xc7,
			0xe4, 0x9a, 0xe6, 0x9b,
			0x17, 0xc2, 0x17, 0xc3,
			0xe0, 0x9a, 0xe2, 0x9b,
			0x80, 0x1b, 0x32, 0x8b,
			0x00, 0x1a, 0x24, 0x9f,
			0x26, 0x9a, 0x01, 0x1a,
			0x28, 0x8a, 0x0f, 0xe8,
			0x07, 0xb0, 0x03, 0xb0,
			0x02, 0xb0, 0x01, 0xb0,
			0x00, 0xb0, 0x02, 0xc6,
			0x00, 0xbe, 0xe6, 0x60,
			0x00, 0xc3, 0x20, 0xc3,
			0x80, 0xcb, 0x55, 0x53,
			0x42, 0x53, 0x80, 0xcb,
			0x03, 0xb4, 0x06, 0xb4,
			0x07, 0xb4, 0xfc, 0xc7,
			0x79, 0xc7, 0xe0, 0x73,
			0xba, 0x49, 0x0d, 0xf0,
			0xf7, 0xc6, 0x24, 0x06,
			0xc0, 0x77, 0xfa, 0x25,
			0x76, 0x23, 0x66, 0x27,
			0x70, 0xc7, 0xe1, 0x9e,
			0x00, 0x16, 0x10, 0xf0,
			0x01, 0x03, 0x0e, 0xe0,
			0xb9, 0x49, 0x10, 0xf0,
			0xe9, 0xc6, 0x24, 0x06,
			0xc0, 0x77, 0xf9, 0x25,
			0x77, 0x23, 0x67, 0x27,
			0x62, 0xc7, 0xe1, 0x9e,
			0x00, 0x16, 0x02, 0xf0,
			0x01, 0x03, 0x5e, 0xc7,
			0xe0, 0x8b, 0x12, 0xe8,
			0x0d, 0xe0, 0xda, 0xc6,
			0x24, 0x06, 0xc0, 0x77,
			0xf6, 0x25, 0x7a, 0x23,
			0x6a, 0x27, 0x53, 0xc7,
			0xe1, 0x9e, 0x00, 0x16,
			0xf3, 0xf0, 0x01, 0x03,
			0xf1, 0xe7, 0x07, 0xb0,
			0x06, 0xb0, 0x03, 0xb0,
			0x80, 0xff, 0x03, 0xb4,
			0x06, 0xb4, 0x07, 0xb4,
			0xc7, 0xc6, 0xc4, 0x77,
			0x40, 0xc3, 0x7c, 0x9f,
			0x41, 0xc6, 0xc0, 0x73,
			0xba, 0x49, 0x05, 0xf1,
			0x00, 0x13, 0x05, 0xf1,
			0x39, 0xc3, 0x04, 0xe0,
			0x38, 0xc3, 0x02, 0xe0,
			0x40, 0x1b, 0xb8, 0xc6,
			0xfb, 0x31, 0xc4, 0x9f,
			0x35, 0xc6, 0xc0, 0x67,
			0x01, 0x17, 0x07, 0xfc,
			0x30, 0xc6, 0xc1, 0x77,
			0x01, 0x1b, 0xc0, 0x8b,
			0x00, 0x17, 0x0c, 0xf1,
			0x29, 0xc6, 0xc0, 0x73,
			0xba, 0x49, 0x05, 0xf1,
			0xb9, 0x49, 0x05, 0xf0,
			0x21, 0xc7, 0x04, 0xe0,
			0x20, 0xc7, 0x02, 0xe0,
			0x40, 0x1f, 0x1a, 0xc6,
			0x7e, 0x41, 0x1d, 0xc6,
			0xc0, 0x63, 0xbb, 0x21,
			0xbb, 0x41, 0x15, 0xc3,
			0x66, 0x9f, 0x18, 0xc6,
			0xc0, 0x67, 0xf9, 0x3b,
			0xc0, 0x8f, 0x01, 0x17,
			0x03, 0xfd, 0x00, 0x1f,
			0x02, 0xe0, 0x01, 0x1f,
			0x0e, 0xc6, 0xc0, 0x8f,
			0x08, 0xc3, 0x04, 0x1e,
			0x60, 0x8e, 0x07, 0xb0,
			0x06, 0xb0, 0x03, 0xb0,
			0x80, 0xff, 0xff, 0x07,
			0x40, 0xd4, 0x00, 0x02,
			0x00, 0x04, 0x80, 0xb9,
			0xfd, 0xcb, 0xa2, 0xcb,
			0xe8, 0x74, 0x02, 0xc5,
			0x00, 0xbd, 0x96, 0x6d,
			0x04, 0xc4, 0x02, 0xc3,
			0x00, 0xbb, 0x50, 0x28,
			0x7f, 0x00, 0x00, 0x1e,
			0x00, 0x11, 0x0c, 0xf0,
			0x90, 0x49, 0x04, 0xf1,
			0x01, 0x06, 0x91, 0x24,
			0xfa, 0xe7, 0x28, 0x32,
			0x06, 0x43, 0xf8, 0x31,
			0x01, 0x06, 0x91, 0x24,
			0xf4, 0xe7, 0x02, 0xc0,
			0x00, 0xb8, 0x0e, 0x28,
			0x02, 0xc7, 0x00, 0xbf,
			0x48, 0x31, 0x1c, 0xc6,
			0xc0, 0x61, 0x04, 0x11,
			0x15, 0xf1, 0x19, 0xc6,
			0xc0, 0x61, 0x9c, 0x20,
			0x9c, 0x24, 0x09, 0x11,
			0x0f, 0xf1, 0x14, 0xc6,
			0x01, 0x19, 0xc0, 0x89,
			0x13, 0xc1, 0x13, 0xc6,
			0x24, 0x9e, 0x00, 0x1e,
			0x26, 0x8e, 0x26, 0x76,
			0xef, 0x49, 0xfe, 0xf1,
			0x22, 0x76, 0x08, 0xc1,
			0x22, 0x9e, 0x07, 0xc6,
			0x02, 0xc1, 0x00, 0xb9,
			0xae, 0x09, 0x18, 0xb4,
			0x4a, 0xb4, 0xe0, 0xcc,
			0x80, 0xd4, 0x08, 0xdc,
			0x10, 0xe8, 0xfc, 0xc6,
			0xc0, 0x67, 0xf0, 0x49,
			0x13, 0xf0, 0xf0, 0x48,
			0xc0, 0x8f, 0xc2, 0x77,
			0xf7, 0xc1, 0xf7, 0xc6,
			0x24, 0x9e, 0x22, 0x9f,
			0x8c, 0x1e, 0x26, 0x8e,
			0x26, 0x76, 0xef, 0x49,
			0xfe, 0xf1, 0xfb, 0x49,
			0x05, 0xf0, 0x07, 0xc6,
			0xc0, 0x61, 0x10, 0x48,
			0xc0, 0x89, 0x02, 0xc6,
			0x00, 0xbe, 0x06, 0x5f,
			0x6c, 0xb4, 0x02, 0xc0,
			0x00, 0xb8, 0x00, 0x00,
			0x02, 0xc0, 0x00, 0xb8,
			0x00, 0x00, 0x02, 0xc0,
			0x00, 0xb8, 0x00, 0x00,
			0x02, 0xc0, 0x00, 0xb8,
			0x00, 0x00, 0x02, 0xc0,
			0x00, 0xb8, 0x00, 0x00};
		static u8 pla_patch_13[] = {
			0x08, 0xe0, 0x14, 0xe0,
			0x18, 0xe0, 0x32, 0xe0,
			0xc8, 0xe0, 0xd4, 0xe0,
			0x0e, 0xe1, 0x10, 0xe1,
			0x0c, 0xc4, 0x04, 0x40,
			0x05, 0xf0, 0x8c, 0x26,
			0x0b, 0x15, 0x02, 0xf0,
			0x03, 0xe0, 0x00, 0x9a,
			0x01, 0xe0, 0x02, 0xc4,
			0x00, 0xbc, 0x36, 0x37,
			0x6c, 0xe8, 0x3a, 0x73,
			0xbb, 0x49, 0x02, 0xc6,
			0x00, 0xbe, 0xde, 0x27,
			0x3a, 0x73, 0xb5, 0x21,
			0xbc, 0x25, 0x04, 0x13,
			0x11, 0xf1, 0x12, 0x1b,
			0x2a, 0x1d, 0x68, 0x31,
			0xda, 0x3a, 0xab, 0x31,
			0x00, 0x1a, 0xc0, 0x9a,
			0x00, 0x13, 0xfb, 0xf1,
			0x20, 0x76, 0x6e, 0x23,
			0x6f, 0x27, 0x3c, 0x1a,
			0xa1, 0x22, 0xb5, 0x41,
			0xe2, 0x9e, 0xe4, 0x76,
			0x6f, 0x48, 0xe4, 0x9e,
			0x02, 0xc6, 0x00, 0xbe,
			0x62, 0x2a, 0x87, 0x49,
			0x62, 0xf0, 0x03, 0x1b,
			0x58, 0x41, 0x33, 0xf0,
			0x20, 0x73, 0x0b, 0xc5,
			0xa4, 0x74, 0xc0, 0x49,
			0x1b, 0xf1, 0x08, 0xc4,
			0x14, 0x40, 0x07, 0xf1,
			0x01, 0x1c, 0xa6, 0x9c,
			0xa0, 0x9b, 0x27, 0xe0,
			0xb8, 0xd3, 0x6c, 0xe8,
			0x2c, 0x26, 0x0b, 0x14,
			0x0f, 0xf1, 0x70, 0xc4,
			0xa6, 0x73, 0xb0, 0x49,
			0x08, 0xf0, 0xb0, 0x48,
			0xa6, 0x9b, 0xa0, 0x73,
			0x80, 0x9b, 0x20, 0x73,
			0x40, 0x83, 0x17, 0xe0,
			0x20, 0x73, 0x40, 0x83,
			0x14, 0xe0, 0x70, 0xc4,
			0x22, 0x40, 0x0a, 0xf1,
			0x38, 0x22, 0x48, 0x26,
			0xe8, 0x14, 0x06, 0xfb,
			0x6b, 0xc4, 0x80, 0x74,
			0xca, 0x49, 0x02, 0xf1,
			0xbe, 0x48, 0x40, 0x83,
			0x56, 0xc4, 0x22, 0x40,
			0x57, 0xf0, 0x54, 0xc4,
			0x22, 0x40, 0x57, 0xf0,
			0x0c, 0x1b, 0x58, 0x41,
			0x57, 0xf0, 0x02, 0x24,
			0x03, 0x1b, 0x58, 0x41,
			0x53, 0xf0, 0x47, 0xc5,
			0xa4, 0x74, 0xc0, 0x49,
			0x0e, 0xf1, 0x2c, 0x26,
			0x0b, 0x14, 0x0b, 0xf1,
			0x41, 0xc4, 0x80, 0x73,
			0xa2, 0x9b, 0xa0, 0x73,
			0x80, 0x9b, 0x22, 0x73,
			0x42, 0x83, 0xa2, 0x73,
			0x80, 0x9b, 0x42, 0xe0,
			0x22, 0x73, 0x45, 0xc4,
			0x22, 0x40, 0x0a, 0xf1,
			0x39, 0x22, 0x4e, 0x26,
			0x03, 0x14, 0x06, 0xf1,
			0x3f, 0xc4, 0x80, 0x74,
			0xca, 0x49, 0x02, 0xf1,
			0xbe, 0x48, 0x42, 0x83,
			0x2a, 0xc4, 0x22, 0x40,
			0x31, 0xf1, 0x29, 0xc4,
			0x82, 0x83, 0x2e, 0xe0,
			0x22, 0xc5, 0xa4, 0x74,
			0xc0, 0x49, 0x12, 0xf1,
			0x2c, 0x26, 0x0b, 0x14,
			0x0f, 0xf1, 0x1b, 0xc5,
			0x1b, 0xc4, 0xa6, 0x73,
			0xb0, 0x49, 0x05, 0xf0,
			0xb0, 0x48, 0xa6, 0x9b,
			0xa0, 0x73, 0x80, 0x9b,
			0x40, 0x73, 0x20, 0x9b,
			0x42, 0x73, 0x22, 0x9b,
			0x19, 0xe0, 0x86, 0x49,
			0x03, 0xf0, 0x84, 0x49,
			0x03, 0xf0, 0x40, 0x73,
			0x20, 0x9b, 0x86, 0x49,
			0x03, 0xf0, 0x85, 0x49,
			0x0f, 0xf0, 0x42, 0x73,
			0x22, 0x9b, 0x0c, 0xe0,
			0xb8, 0xd3, 0x6c, 0xe8,
			0x00, 0xc0, 0x04, 0xc0,
			0x82, 0xcc, 0xff, 0xc4,
			0x80, 0x83, 0xab, 0xe7,
			0xfc, 0xc4, 0x84, 0x83,
			0xa8, 0xe7, 0x02, 0xc5,
			0x00, 0xbd, 0x66, 0x0a,
			0x00, 0xea, 0x04, 0xdd,
			0x02, 0xdd, 0x5a, 0xe8,
			0x04, 0xe8, 0x02, 0xc1,
			0x00, 0xb9, 0xac, 0x35,
			0x08, 0xc1, 0x20, 0x70,
			0x87, 0x48, 0x20, 0x98,
			0x36, 0x70, 0x80, 0x48,
			0x36, 0x98, 0x80, 0xff,
			0xd4, 0xb5, 0x04, 0x10,
			0x07, 0xf1, 0x27, 0xc1,
			0x32, 0x70, 0x89, 0x48,
			0x32, 0x98, 0xf1, 0xef,
			0x18, 0xe0, 0x05, 0x10,
			0x07, 0xf1, 0x1f, 0xc1,
			0x32, 0x70, 0x89, 0x48,
			0x32, 0x98, 0x1d, 0xe8,
			0x10, 0xe0, 0x06, 0x10,
			0x07, 0xf1, 0x17, 0xc1,
			0x32, 0x70, 0x09, 0x48,
			0x32, 0x98, 0x15, 0xe8,
			0x08, 0xe0, 0x07, 0x10,
			0x0d, 0xf1, 0x0f, 0xc1,
			0x32, 0x70, 0x09, 0x48,
			0x32, 0x98, 0x15, 0xe8,
			0x0b, 0xc1, 0x28, 0x70,
			0x09, 0x48, 0x28, 0x98,
			0x02, 0xc1, 0x00, 0xb9,
			0x44, 0x36, 0x02, 0xc1,
			0x00, 0xb9, 0x52, 0x36,
			0x00, 0xb4, 0x20, 0xb4,
			0xd4, 0xc1, 0x20, 0x70,
			0x87, 0x48, 0x20, 0x98,
			0x36, 0x70, 0x00, 0x48,
			0x36, 0x98, 0x80, 0xff,
			0xcc, 0xc1, 0x20, 0x70,
			0x07, 0x48, 0x20, 0x98,
			0x36, 0x70, 0x00, 0x48,
			0x36, 0x98, 0x80, 0xff,
			0x02, 0xc0, 0x00, 0xb8,
			0x3a, 0x4e, 0x02, 0xc0,
			0x00, 0xb8, 0x3a, 0x4e};

		if (ocp_read_byte(tp, MCU_TYPE_USB, 0xcfd7) < 0x04) {
			rtl_clear_bp(tp, MCU_TYPE_USB);

			generic_ocp_write(tp, 0xe600, 0xff,
					  sizeof(usb_patch_13),
					  usb_patch_13, MCU_TYPE_USB);

			ocp_write_word(tp, MCU_TYPE_USB, USB_BP_BA, 0xc000);
			ocp_write_word(tp, MCU_TYPE_USB, USB_BP_0, 0x0fba);
			ocp_write_word(tp, MCU_TYPE_USB, USB_BP_1, 0x3660);
			ocp_write_word(tp, MCU_TYPE_USB, USB_BP_2, 0x1478);
			ocp_write_word(tp, MCU_TYPE_USB, USB_BP_3, 0x77ae);
			ocp_write_word(tp, MCU_TYPE_USB, USB_BP_4, 0x60e0);
			ocp_write_word(tp, MCU_TYPE_USB, USB_BP_5, 0x6d94);
			ocp_write_word(tp, MCU_TYPE_USB, USB_BP_6, 0x284e);
			ocp_write_word(tp, MCU_TYPE_USB, USB_BP_7, 0x27f6);
			ocp_write_word(tp, MCU_TYPE_USB, USB_BP_8, 0x3140);
			ocp_write_word(tp, MCU_TYPE_USB, USB_BP_9, 0x09ac);
			ocp_write_word(tp, MCU_TYPE_USB, USB_BP_10, 0x5e2a);
			ocp_write_word(tp, MCU_TYPE_USB, USB_BP_11, 0x0000);
			ocp_write_word(tp, MCU_TYPE_USB, USB_BP_12, 0x0000);
			ocp_write_word(tp, MCU_TYPE_USB, USB_BP_13, 0x0000);
			ocp_write_word(tp, MCU_TYPE_USB, USB_BP_14, 0x0000);
			ocp_write_word(tp, MCU_TYPE_USB, USB_BP_15, 0x0000);
			ocp_write_word(tp, MCU_TYPE_USB, USB_BP2_EN, 0x07ff);
			ocp_write_byte(tp, MCU_TYPE_USB, 0xcfd7, 0x04);
		}

		if (ocp_read_byte(tp, MCU_TYPE_USB, 0xcfd6) < 0x06) {
			rtl_clear_bp(tp, MCU_TYPE_PLA);

			generic_ocp_write(tp, 0xf800, 0xff,
					  sizeof(pla_patch_13),
					  pla_patch_13, MCU_TYPE_PLA);

			ocp_write_word(tp, MCU_TYPE_PLA, PLA_BP_BA, 0x8000);
			ocp_write_word(tp, MCU_TYPE_PLA, PLA_BP_0, 0x374e);
			ocp_write_word(tp, MCU_TYPE_PLA, PLA_BP_1, 0x27dc);
			ocp_write_word(tp, MCU_TYPE_PLA, PLA_BP_2, 0x2a5c);
			ocp_write_word(tp, MCU_TYPE_PLA, PLA_BP_3, 0x09d0);
			ocp_write_word(tp, MCU_TYPE_PLA, PLA_BP_4, 0x359e);
			ocp_write_word(tp, MCU_TYPE_PLA, PLA_BP_5, 0x35b6);
			ocp_write_word(tp, MCU_TYPE_PLA, PLA_BP_6, 0x0000);
			ocp_write_word(tp, MCU_TYPE_PLA, PLA_BP_7, 0x0000);
			ocp_write_word(tp, MCU_TYPE_PLA, PLA_BP_EN, 0x003f);
			ocp_write_byte(tp, MCU_TYPE_USB, 0xcfd6, 0x06);
		}
	}

	rtl_reset_ocp_base(tp);
}

static void rtl_ram_code_speed_up(struct r8152 *tp, bool wait)
{
	u32 ocp_data, len = 0;
	u8 *data = NULL;

	rtl_reset_ocp_base(tp);

	if (tp->version == RTL_VER_13 || tp->version == RTL_VER_15) {
		static u8 ram13[] = {
			0x6c, 0xe8, 0x00, 0xa0,
			0x36, 0xb4, 0x24, 0x80,
			0x38, 0xb4, 0x01, 0x37,
			0x36, 0xb4, 0x2e, 0xb8,
			0x38, 0xb4, 0x01, 0x00,
			0x6c, 0xe8, 0x00, 0xb0,
			0x20, 0xb8, 0x90, 0x00,
			0x6c, 0xe8, 0x00, 0xa0,
			0x36, 0xb4, 0x16, 0xa0,
			0x38, 0xb4, 0x00, 0x00,
			0x36, 0xb4, 0x12, 0xa0,
			0x38, 0xb4, 0x00, 0x00,
			0x36, 0xb4, 0x14, 0xa0,
			0x38, 0xb4, 0x00, 0x18,
			0x38, 0xb4, 0x10, 0x80,
			0x38, 0xb4, 0x00, 0x18,
			0x38, 0xb4, 0x1a, 0x80,
			0x38, 0xb4, 0x00, 0x18,
			0x38, 0xb4, 0x3f, 0x80,
			0x38, 0xb4, 0x00, 0x18,
			0x38, 0xb4, 0x45, 0x80,
			0x38, 0xb4, 0x00, 0x18,
			0x38, 0xb4, 0x67, 0x80,
			0x38, 0xb4, 0x00, 0x18,
			0x38, 0xb4, 0x6d, 0x80,
			0x38, 0xb4, 0x00, 0x18,
			0x38, 0xb4, 0x71, 0x80,
			0x38, 0xb4, 0x00, 0x18,
			0x38, 0xb4, 0xb1, 0x80,
			0x38, 0xb4, 0x93, 0xd0,
			0x38, 0xb4, 0xc4, 0xd1,
			0x38, 0xb4, 0x00, 0x10,
			0x38, 0xb4, 0x5c, 0x13,
			0x38, 0xb4, 0x04, 0xd7,
			0x38, 0xb4, 0xbc, 0x5f,
			0x38, 0xb4, 0x04, 0xd5,
			0x38, 0xb4, 0xf1, 0xc9,
			0x38, 0xb4, 0x00, 0x18,
			0x38, 0xb4, 0xc9, 0x0f,
			0x38, 0xb4, 0x50, 0xbb,
			0x38, 0xb4, 0x05, 0xd5,
			0x38, 0xb4, 0x02, 0xa2,
			0x38, 0xb4, 0x04, 0xd5,
			0x38, 0xb4, 0x0f, 0x8c,
			0x38, 0xb4, 0x00, 0xd5,
			0x38, 0xb4, 0x00, 0x10,
			0x38, 0xb4, 0x19, 0x15,
			0x38, 0xb4, 0x00, 0x10,
			0x38, 0xb4, 0x5c, 0x13,
			0x38, 0xb4, 0x5e, 0xd7,
			0x38, 0xb4, 0xae, 0x5f,
			0x38, 0xb4, 0x50, 0x9b,
			0x38, 0xb4, 0x00, 0x10,
			0x38, 0xb4, 0x5c, 0x13,
			0x38, 0xb4, 0x5e, 0xd7,
			0x38, 0xb4, 0xae, 0x7f,
			0x38, 0xb4, 0x00, 0x10,
			0x38, 0xb4, 0x5c, 0x13,
			0x38, 0xb4, 0x07, 0xd7,
			0x38, 0xb4, 0xa7, 0x40,
			0x38, 0xb4, 0x19, 0xd7,
			0x38, 0xb4, 0x71, 0x40,
			0x38, 0xb4, 0x00, 0x18,
			0x38, 0xb4, 0x57, 0x15,
			0x38, 0xb4, 0x19, 0xd7,
			0x38, 0xb4, 0x70, 0x2f,
			0x38, 0xb4, 0x3b, 0x80,
			0x38, 0xb4, 0x73, 0x2f,
			0x38, 0xb4, 0x6a, 0x15,
			0x38, 0xb4, 0x70, 0x5e,
			0x38, 0xb4, 0x00, 0x18,
			0x38, 0xb4, 0x5d, 0x15,
			0x38, 0xb4, 0x05, 0xd5,
			0x38, 0xb4, 0x02, 0xa2,
			0x38, 0xb4, 0x00, 0xd5,
			0x38, 0xb4, 0xed, 0xff,
			0x38, 0xb4, 0x09, 0xd7,
			0x38, 0xb4, 0x54, 0x40,
			0x38, 0xb4, 0x88, 0xa7,
			0x38, 0xb4, 0x0b, 0xd7,
			0x38, 0xb4, 0x00, 0x18,
			0x38, 0xb4, 0x2a, 0x17,
			0x38, 0xb4, 0xc1, 0xc0,
			0x38, 0xb4, 0xc0, 0xc0,
			0x38, 0xb4, 0x5a, 0xd0,
			0x38, 0xb4, 0xba, 0xd1,
			0x38, 0xb4, 0x01, 0xd7,
			0x38, 0xb4, 0x29, 0x25,
			0x38, 0xb4, 0x2a, 0x02,
			0x38, 0xb4, 0xa7, 0xd0,
			0x38, 0xb4, 0xb9, 0xd1,
			0x38, 0xb4, 0x08, 0xa2,
			0x38, 0xb4, 0x00, 0x10,
			0x38, 0xb4, 0x0e, 0x08,
			0x38, 0xb4, 0x01, 0xd7,
			0x38, 0xb4, 0x8b, 0x40,
			0x38, 0xb4, 0x00, 0x10,
			0x38, 0xb4, 0x65, 0x0a,
			0x38, 0xb4, 0x03, 0xf0,
			0x38, 0xb4, 0x00, 0x10,
			0x38, 0xb4, 0x6b, 0x0a,
			0x38, 0xb4, 0x01, 0xd7,
			0x38, 0xb4, 0x00, 0x10,
			0x38, 0xb4, 0x20, 0x09,
			0x38, 0xb4, 0x00, 0x10,
			0x38, 0xb4, 0x15, 0x09,
			0x38, 0xb4, 0x00, 0x10,
			0x38, 0xb4, 0x09, 0x09,
			0x38, 0xb4, 0x8f, 0x22,
			0x38, 0xb4, 0x4e, 0x80,
			0x38, 0xb4, 0x01, 0x98,
			0x38, 0xb4, 0x1e, 0xd7,
			0x38, 0xb4, 0x61, 0x5d,
			0x38, 0xb4, 0x01, 0xd7,
			0x38, 0xb4, 0x00, 0x18,
			0x38, 0xb4, 0x2a, 0x02,
			0x38, 0xb4, 0x05, 0x20,
			0x38, 0xb4, 0x1a, 0x09,
			0x38, 0xb4, 0xd9, 0x3b,
			0x38, 0xb4, 0x19, 0x09,
			0x38, 0xb4, 0x00, 0x18,
			0x38, 0xb4, 0x16, 0x09,
			0x38, 0xb4, 0x90, 0xd0,
			0x38, 0xb4, 0xc9, 0xd1,
			0x38, 0xb4, 0x00, 0x18,
			0x38, 0xb4, 0x64, 0x10,
			0x38, 0xb4, 0x96, 0xd0,
			0x38, 0xb4, 0xa9, 0xd1,
			0x38, 0xb4, 0x03, 0xd5,
			0x38, 0xb4, 0x04, 0xa1,
			0x38, 0xb4, 0x07, 0x0c,
			0x38, 0xb4, 0x02, 0x09,
			0x38, 0xb4, 0x00, 0xd5,
			0x38, 0xb4, 0x10, 0xbc,
			0x38, 0xb4, 0x01, 0xd5,
			0x38, 0xb4, 0x01, 0xce,
			0x38, 0xb4, 0x01, 0xa2,
			0x38, 0xb4, 0x01, 0x82,
			0x38, 0xb4, 0x00, 0xce,
			0x38, 0xb4, 0x00, 0xd5,
			0x38, 0xb4, 0x84, 0xc4,
			0x38, 0xb4, 0x03, 0xd5,
			0x38, 0xb4, 0x02, 0xcc,
			0x38, 0xb4, 0x0d, 0xcd,
			0x38, 0xb4, 0x01, 0xaf,
			0x38, 0xb4, 0x00, 0xd5,
			0x38, 0xb4, 0x03, 0xd7,
			0x38, 0xb4, 0x71, 0x43,
			0x38, 0xb4, 0x08, 0xbd,
			0x38, 0xb4, 0x00, 0x10,
			0x38, 0xb4, 0x5c, 0x13,
			0x38, 0xb4, 0x5e, 0xd7,
			0x38, 0xb4, 0xb3, 0x5f,
			0x38, 0xb4, 0x03, 0xd5,
			0x38, 0xb4, 0xf5, 0xd0,
			0x38, 0xb4, 0xc6, 0xd1,
			0x38, 0xb4, 0xf0, 0x0c,
			0x38, 0xb4, 0x50, 0x0e,
			0x38, 0xb4, 0x04, 0xd7,
			0x38, 0xb4, 0x1c, 0x40,
			0x38, 0xb4, 0xf5, 0xd0,
			0x38, 0xb4, 0xc6, 0xd1,
			0x38, 0xb4, 0xf0, 0x0c,
			0x38, 0xb4, 0xa0, 0x0e,
			0x38, 0xb4, 0x1c, 0x40,
			0x38, 0xb4, 0x7b, 0xd0,
			0x38, 0xb4, 0xc5, 0xd1,
			0x38, 0xb4, 0xf0, 0x8e,
			0x38, 0xb4, 0x1c, 0x40,
			0x38, 0xb4, 0x08, 0x9d,
			0x38, 0xb4, 0x00, 0x10,
			0x38, 0xb4, 0x5c, 0x13,
			0x38, 0xb4, 0x5e, 0xd7,
			0x38, 0xb4, 0xb3, 0x7f,
			0x38, 0xb4, 0x00, 0x10,
			0x38, 0xb4, 0x5c, 0x13,
			0x38, 0xb4, 0x5e, 0xd7,
			0x38, 0xb4, 0xad, 0x5f,
			0x38, 0xb4, 0x00, 0x10,
			0x38, 0xb4, 0xc5, 0x14,
			0x38, 0xb4, 0x03, 0xd7,
			0x38, 0xb4, 0x81, 0x31,
			0x38, 0xb4, 0xaf, 0x80,
			0x38, 0xb4, 0xad, 0x60,
			0x38, 0xb4, 0x00, 0x10,
			0x38, 0xb4, 0x5c, 0x13,
			0x38, 0xb4, 0x03, 0xd7,
			0x38, 0xb4, 0xba, 0x5f,
			0x38, 0xb4, 0x00, 0x18,
			0x38, 0xb4, 0xc7, 0x0c,
			0x38, 0xb4, 0x02, 0xa8,
			0x38, 0xb4, 0x01, 0xa3,
			0x38, 0xb4, 0x01, 0xa8,
			0x38, 0xb4, 0x04, 0xc0,
			0x38, 0xb4, 0x10, 0xd7,
			0x38, 0xb4, 0x00, 0x40,
			0x38, 0xb4, 0x00, 0x18,
			0x38, 0xb4, 0x79, 0x1e,
			0x36, 0xb4, 0x26, 0xa0,
			0x38, 0xb4, 0x78, 0x1e,
			0x36, 0xb4, 0x24, 0xa0,
			0x38, 0xb4, 0x93, 0x0c,
			0x36, 0xb4, 0x22, 0xa0,
			0x38, 0xb4, 0x62, 0x10,
			0x36, 0xb4, 0x20, 0xa0,
			0x38, 0xb4, 0x15, 0x09,
			0x36, 0xb4, 0x06, 0xa0,
			0x38, 0xb4, 0x0a, 0x02,
			0x36, 0xb4, 0x04, 0xa0,
			0x38, 0xb4, 0x26, 0x17,
			0x36, 0xb4, 0x02, 0xa0,
			0x38, 0xb4, 0x42, 0x15,
			0x36, 0xb4, 0x00, 0xa0,
			0x38, 0xb4, 0xc7, 0x0f,
			0x36, 0xb4, 0x08, 0xa0,
			0x38, 0xb4, 0x00, 0xff,
			0x6c, 0xe8, 0x00, 0xa0,
			0x36, 0xb4, 0x16, 0xa0,
			0x38, 0xb4, 0x10, 0x00,
			0x36, 0xb4, 0x12, 0xa0,
			0x38, 0xb4, 0x00, 0x00,
			0x36, 0xb4, 0x14, 0xa0,
			0x38, 0xb4, 0x00, 0x18,
			0x38, 0xb4, 0x10, 0x80,
			0x38, 0xb4, 0x00, 0x18,
			0x38, 0xb4, 0x1d, 0x80,
			0x38, 0xb4, 0x00, 0x18,
			0x38, 0xb4, 0x2c, 0x80,
			0x38, 0xb4, 0x00, 0x18,
			0x38, 0xb4, 0x2c, 0x80,
			0x38, 0xb4, 0x00, 0x18,
			0x38, 0xb4, 0x2c, 0x80,
			0x38, 0xb4, 0x00, 0x18,
			0x38, 0xb4, 0x2c, 0x80,
			0x38, 0xb4, 0x00, 0x18,
			0x38, 0xb4, 0x2c, 0x80,
			0x38, 0xb4, 0x00, 0x18,
			0x38, 0xb4, 0x2c, 0x80,
			0x38, 0xb4, 0x00, 0xd7,
			0x38, 0xb4, 0x90, 0x60,
			0x38, 0xb4, 0xd1, 0x60,
			0x38, 0xb4, 0x5c, 0xc9,
			0x38, 0xb4, 0x07, 0xf0,
			0x38, 0xb4, 0xb1, 0x60,
			0x38, 0xb4, 0x5a, 0xc9,
			0x38, 0xb4, 0x04, 0xf0,
			0x38, 0xb4, 0x56, 0xc9,
			0x38, 0xb4, 0x02, 0xf0,
			0x38, 0xb4, 0x4e, 0xc9,
			0x38, 0xb4, 0x00, 0x18,
			0x38, 0xb4, 0xcd, 0x00,
			0x38, 0xb4, 0x00, 0xd7,
			0x38, 0xb4, 0x90, 0x60,
			0x38, 0xb4, 0xd1, 0x60,
			0x38, 0xb4, 0x5c, 0xc9,
			0x38, 0xb4, 0x07, 0xf0,
			0x38, 0xb4, 0xb1, 0x60,
			0x38, 0xb4, 0x5a, 0xc9,
			0x38, 0xb4, 0x04, 0xf0,
			0x38, 0xb4, 0x56, 0xc9,
			0x38, 0xb4, 0x02, 0xf0,
			0x38, 0xb4, 0x4e, 0xc9,
			0x38, 0xb4, 0x00, 0x10,
			0x38, 0xb4, 0x2a, 0x02,
			0x38, 0xb4, 0x00, 0x18,
			0x38, 0xb4, 0x32, 0x01,
			0x36, 0xb4, 0x8e, 0xa0,
			0x38, 0xb4, 0xff, 0xff,
			0x36, 0xb4, 0x8c, 0xa0,
			0x38, 0xb4, 0xff, 0xff,
			0x36, 0xb4, 0x8a, 0xa0,
			0x38, 0xb4, 0xff, 0xff,
			0x36, 0xb4, 0x88, 0xa0,
			0x38, 0xb4, 0xff, 0xff,
			0x36, 0xb4, 0x86, 0xa0,
			0x38, 0xb4, 0xff, 0xff,
			0x36, 0xb4, 0x84, 0xa0,
			0x38, 0xb4, 0xff, 0xff,
			0x36, 0xb4, 0x82, 0xa0,
			0x38, 0xb4, 0x2f, 0x01,
			0x36, 0xb4, 0x80, 0xa0,
			0x38, 0xb4, 0xcc, 0x00,
			0x36, 0xb4, 0x90, 0xa0,
			0x38, 0xb4, 0x03, 0x01,
			0x6c, 0xe8, 0x00, 0xa0,
			0x36, 0xb4, 0x16, 0xa0,
			0x38, 0xb4, 0x20, 0x00,
			0x36, 0xb4, 0x12, 0xa0,
			0x38, 0xb4, 0x00, 0x00,
			0x36, 0xb4, 0x14, 0xa0,
			0x38, 0xb4, 0x00, 0x18,
			0x38, 0xb4, 0x10, 0x80,
			0x38, 0xb4, 0x00, 0x18,
			0x38, 0xb4, 0x20, 0x80,
			0x38, 0xb4, 0x00, 0x18,
			0x38, 0xb4, 0x2a, 0x80,
			0x38, 0xb4, 0x00, 0x18,
			0x38, 0xb4, 0x35, 0x80,
			0x38, 0xb4, 0x00, 0x18,
			0x38, 0xb4, 0x3c, 0x80,
			0x38, 0xb4, 0x00, 0x18,
			0x38, 0xb4, 0x3c, 0x80,
			0x38, 0xb4, 0x00, 0x18,
			0x38, 0xb4, 0x3c, 0x80,
			0x38, 0xb4, 0x00, 0x18,
			0x38, 0xb4, 0x3c, 0x80,
			0x38, 0xb4, 0x07, 0xd1,
			0x38, 0xb4, 0x42, 0xd0,
			0x38, 0xb4, 0x04, 0xa4,
			0x38, 0xb4, 0x00, 0x10,
			0x38, 0xb4, 0xdf, 0x09,
			0x38, 0xb4, 0x00, 0xd7,
			0x38, 0xb4, 0xb4, 0x5f,
			0x38, 0xb4, 0x80, 0x82,
			0x38, 0xb4, 0x00, 0xd7,
			0x38, 0xb4, 0x65, 0x60,
			0x38, 0xb4, 0x25, 0xd1,
			0x38, 0xb4, 0x02, 0xf0,
			0x38, 0xb4, 0x2b, 0xd1,
			0x38, 0xb4, 0x40, 0xd0,
			0x38, 0xb4, 0x00, 0x18,
			0x38, 0xb4, 0x7f, 0x07,
			0x38, 0xb4, 0xf0, 0x0c,
			0x38, 0xb4, 0x50, 0x0c,
			0x38, 0xb4, 0x04, 0xd1,
			0x38, 0xb4, 0x40, 0xd0,
			0x38, 0xb4, 0x00, 0x10,
			0x38, 0xb4, 0xa8, 0x0a,
			0x38, 0xb4, 0x00, 0xd7,
			0x38, 0xb4, 0xb4, 0x5f,
			0x38, 0xb4, 0x00, 0x18,
			0x38, 0xb4, 0x2e, 0x0a,
			0x38, 0xb4, 0x9b, 0xcb,
			0x38, 0xb4, 0x10, 0xd1,
			0x38, 0xb4, 0x40, 0xd0,
			0x38, 0xb4, 0x00, 0x10,
			0x38, 0xb4, 0x7b, 0x0b,
			0x38, 0xb4, 0x00, 0x10,
			0x38, 0xb4, 0xdf, 0x09,
			0x38, 0xb4, 0x00, 0xd7,
			0x38, 0xb4, 0xb4, 0x5f,
			0x38, 0xb4, 0x00, 0x18,
			0x38, 0xb4, 0x1b, 0x08,
			0x38, 0xb4, 0x00, 0x10,
			0x38, 0xb4, 0xdf, 0x09,
			0x38, 0xb4, 0x04, 0xd7,
			0x38, 0xb4, 0xb8, 0x7f,
			0x38, 0xb4, 0x18, 0xa7,
			0x38, 0xb4, 0x00, 0x18,
			0x38, 0xb4, 0x4e, 0x07,
			0x36, 0xb4, 0x0e, 0xa1,
			0x38, 0xb4, 0xff, 0xff,
			0x36, 0xb4, 0x0c, 0xa1,
			0x38, 0xb4, 0xff, 0xff,
			0x36, 0xb4, 0x0a, 0xa1,
			0x38, 0xb4, 0xff, 0xff,
			0x36, 0xb4, 0x08, 0xa1,
			0x38, 0xb4, 0xff, 0xff,
			0x36, 0xb4, 0x06, 0xa1,
			0x38, 0xb4, 0x4d, 0x07,
			0x36, 0xb4, 0x04, 0xa1,
			0x38, 0xb4, 0x18, 0x08,
			0x36, 0xb4, 0x02, 0xa1,
			0x38, 0xb4, 0x2c, 0x0a,
			0x36, 0xb4, 0x00, 0xa1,
			0x38, 0xb4, 0x7e, 0x07,
			0x36, 0xb4, 0x10, 0xa1,
			0x38, 0xb4, 0x0f, 0x00,
			0x6c, 0xe8, 0x00, 0xa0,
			0x36, 0xb4, 0x7c, 0xb8,
			0x38, 0xb4, 0x25, 0x86,
			0x36, 0xb4, 0x7e, 0xb8,
			0x38, 0xb4, 0x86, 0xaf,
			0x38, 0xb4, 0xaf, 0x3d,
			0x38, 0xb4, 0x89, 0x86,
			0x38, 0xb4, 0x88, 0xaf,
			0x38, 0xb4, 0xaf, 0x69,
			0x38, 0xb4, 0x87, 0x88,
			0x38, 0xb4, 0x88, 0xaf,
			0x38, 0xb4, 0xaf, 0x9c,
			0x38, 0xb4, 0x9c, 0x88,
			0x38, 0xb4, 0x88, 0xaf,
			0x38, 0xb4, 0xaf, 0x9c,
			0x38, 0xb4, 0x9c, 0x88,
			0x38, 0xb4, 0x86, 0xbf,
			0x38, 0xb4, 0xd7, 0x49,
			0x38, 0xb4, 0x40, 0x00,
			0x38, 0xb4, 0x77, 0x02,
			0x38, 0xb4, 0xaf, 0x7d,
			0x38, 0xb4, 0x27, 0x27,
			0x38, 0xb4, 0x00, 0x00,
			0x38, 0xb4, 0x05, 0x72,
			0x38, 0xb4, 0x00, 0x00,
			0x38, 0xb4, 0x08, 0x72,
			0x38, 0xb4, 0x00, 0x00,
			0x38, 0xb4, 0xf3, 0x71,
			0x38, 0xb4, 0x00, 0x00,
			0x38, 0xb4, 0xf6, 0x71,
			0x38, 0xb4, 0x00, 0x00,
			0x38, 0xb4, 0x29, 0x72,
			0x38, 0xb4, 0x00, 0x00,
			0x38, 0xb4, 0x2c, 0x72,
			0x38, 0xb4, 0x00, 0x00,
			0x38, 0xb4, 0x17, 0x72,
			0x38, 0xb4, 0x00, 0x00,
			0x38, 0xb4, 0x1a, 0x72,
			0x38, 0xb4, 0x00, 0x00,
			0x38, 0xb4, 0x1d, 0x72,
			0x38, 0xb4, 0x00, 0x00,
			0x38, 0xb4, 0x11, 0x72,
			0x38, 0xb4, 0x00, 0x00,
			0x38, 0xb4, 0x20, 0x72,
			0x38, 0xb4, 0x00, 0x00,
			0x38, 0xb4, 0x14, 0x72,
			0x38, 0xb4, 0x00, 0x00,
			0x38, 0xb4, 0x2f, 0x72,
			0x38, 0xb4, 0x00, 0x00,
			0x38, 0xb4, 0x23, 0x72,
			0x38, 0xb4, 0x00, 0x00,
			0x38, 0xb4, 0x32, 0x72,
			0x38, 0xb4, 0x00, 0x00,
			0x38, 0xb4, 0x26, 0x72,
			0x38, 0xb4, 0xf9, 0xf8,
			0x38, 0xb4, 0xe0, 0xfa,
			0x38, 0xb4, 0xb3, 0x85,
			0x38, 0xb4, 0x02, 0x38,
			0x38, 0xb4, 0x27, 0xad,
			0x38, 0xb4, 0xae, 0x02,
			0x38, 0xb4, 0xaf, 0x03,
			0x38, 0xb4, 0x30, 0x88,
			0x38, 0xb4, 0x66, 0x1f,
			0x38, 0xb4, 0x65, 0xef,
			0x38, 0xb4, 0xc2, 0xbf,
			0x38, 0xb4, 0x1a, 0x1f,
			0x38, 0xb4, 0xf7, 0x96,
			0x38, 0xb4, 0xee, 0x05,
			0x38, 0xb4, 0xd2, 0xff,
			0x38, 0xb4, 0xda, 0x00,
			0x38, 0xb4, 0x05, 0xf6,
			0x38, 0xb4, 0xc2, 0xbf,
			0x38, 0xb4, 0x1a, 0x2f,
			0x38, 0xb4, 0xf7, 0x96,
			0x38, 0xb4, 0xee, 0x05,
			0x38, 0xb4, 0xd2, 0xff,
			0x38, 0xb4, 0xdb, 0x00,
			0x38, 0xb4, 0x05, 0xf6,
			0x38, 0xb4, 0x02, 0xef,
			0x38, 0xb4, 0x11, 0x1f,
			0x38, 0xb4, 0x42, 0x0d,
			0x38, 0xb4, 0x88, 0xbf,
			0x38, 0xb4, 0x02, 0x42,
			0x38, 0xb4, 0x7d, 0x6e,
			0x38, 0xb4, 0x02, 0xef,
			0x38, 0xb4, 0x03, 0x1b,
			0x38, 0xb4, 0x11, 0x1f,
			0x38, 0xb4, 0x42, 0x0d,
			0x38, 0xb4, 0x88, 0xbf,
			0x38, 0xb4, 0x02, 0x45,
			0x38, 0xb4, 0x7d, 0x6e,
			0x38, 0xb4, 0x02, 0xef,
			0x38, 0xb4, 0x03, 0x1a,
			0x38, 0xb4, 0x11, 0x1f,
			0x38, 0xb4, 0x42, 0x0d,
			0x38, 0xb4, 0x88, 0xbf,
			0x38, 0xb4, 0x02, 0x48,
			0x38, 0xb4, 0x7d, 0x6e,
			0x38, 0xb4, 0xc2, 0xbf,
			0x38, 0xb4, 0x1a, 0x3f,
			0x38, 0xb4, 0xf7, 0x96,
			0x38, 0xb4, 0xee, 0x05,
			0x38, 0xb4, 0xd2, 0xff,
			0x38, 0xb4, 0xda, 0x00,
			0x38, 0xb4, 0x05, 0xf6,
			0x38, 0xb4, 0xc2, 0xbf,
			0x38, 0xb4, 0x1a, 0x4f,
			0x38, 0xb4, 0xf7, 0x96,
			0x38, 0xb4, 0xee, 0x05,
			0x38, 0xb4, 0xd2, 0xff,
			0x38, 0xb4, 0xdb, 0x00,
			0x38, 0xb4, 0x05, 0xf6,
			0x38, 0xb4, 0x02, 0xef,
			0x38, 0xb4, 0x11, 0x1f,
			0x38, 0xb4, 0x42, 0x0d,
			0x38, 0xb4, 0x88, 0xbf,
			0x38, 0xb4, 0x02, 0x4b,
			0x38, 0xb4, 0x7d, 0x6e,
			0x38, 0xb4, 0x02, 0xef,
			0x38, 0xb4, 0x03, 0x1b,
			0x38, 0xb4, 0x11, 0x1f,
			0x38, 0xb4, 0x42, 0x0d,
			0x38, 0xb4, 0x88, 0xbf,
			0x38, 0xb4, 0x02, 0x4e,
			0x38, 0xb4, 0x7d, 0x6e,
			0x38, 0xb4, 0x02, 0xef,
			0x38, 0xb4, 0x03, 0x1a,
			0x38, 0xb4, 0x11, 0x1f,
			0x38, 0xb4, 0x42, 0x0d,
			0x38, 0xb4, 0x88, 0xbf,
			0x38, 0xb4, 0x02, 0x51,
			0x38, 0xb4, 0x7d, 0x6e,
			0x38, 0xb4, 0x56, 0xef,
			0x38, 0xb4, 0x20, 0xd0,
			0x38, 0xb4, 0x11, 0x1f,
			0x38, 0xb4, 0x88, 0xbf,
			0x38, 0xb4, 0x02, 0x54,
			0x38, 0xb4, 0x7d, 0x6e,
			0x38, 0xb4, 0x88, 0xbf,
			0x38, 0xb4, 0x02, 0x57,
			0x38, 0xb4, 0x7d, 0x6e,
			0x38, 0xb4, 0x88, 0xbf,
			0x38, 0xb4, 0x02, 0x5a,
			0xff, 0xff, 0xff, 0xff,
			0x38, 0xb4, 0x7d, 0x6e,
			0x38, 0xb4, 0x85, 0xe1,
			0x38, 0xb4, 0xef, 0xa0,
			0x38, 0xb4, 0x48, 0x03,
			0x38, 0xb4, 0x28, 0x0a,
			0x38, 0xb4, 0xef, 0x05,
			0x38, 0xb4, 0x1b, 0x20,
			0x38, 0xb4, 0xad, 0x01,
			0x38, 0xb4, 0x35, 0x27,
			0x38, 0xb4, 0x44, 0x1f,
			0x38, 0xb4, 0x85, 0xe0,
			0x38, 0xb4, 0xe1, 0x88,
			0x38, 0xb4, 0x89, 0x85,
			0x38, 0xb4, 0x88, 0xbf,
			0x38, 0xb4, 0x02, 0x5d,
			0x38, 0xb4, 0x7d, 0x6e,
			0x38, 0xb4, 0x85, 0xe0,
			0x38, 0xb4, 0xe1, 0x8e,
			0x38, 0xb4, 0x8f, 0x85,
			0x38, 0xb4, 0x88, 0xbf,
			0x38, 0xb4, 0x02, 0x60,
			0x38, 0xb4, 0x7d, 0x6e,
			0x38, 0xb4, 0x85, 0xe0,
			0x38, 0xb4, 0xe1, 0x94,
			0x38, 0xb4, 0x95, 0x85,
			0x38, 0xb4, 0x88, 0xbf,
			0x38, 0xb4, 0x02, 0x63,
			0x38, 0xb4, 0x7d, 0x6e,
			0x38, 0xb4, 0x85, 0xe0,
			0x38, 0xb4, 0xe1, 0x9a,
			0x38, 0xb4, 0x9b, 0x85,
			0x38, 0xb4, 0x88, 0xbf,
			0x38, 0xb4, 0x02, 0x66,
			0x38, 0xb4, 0x7d, 0x6e,
			0x38, 0xb4, 0x88, 0xaf,
			0x38, 0xb4, 0xbf, 0x3c,
			0x38, 0xb4, 0x3f, 0x88,
			0x38, 0xb4, 0x6e, 0x02,
			0x38, 0xb4, 0xad, 0x9c,
			0x38, 0xb4, 0x35, 0x28,
			0x38, 0xb4, 0x44, 0x1f,
			0x38, 0xb4, 0x8f, 0xe0,
			0x38, 0xb4, 0xe1, 0xf8,
			0x38, 0xb4, 0xf9, 0x8f,
			0x38, 0xb4, 0x88, 0xbf,
			0x38, 0xb4, 0x02, 0x5d,
			0x38, 0xb4, 0x7d, 0x6e,
			0x38, 0xb4, 0x8f, 0xe0,
			0x38, 0xb4, 0xe1, 0xfa,
			0x38, 0xb4, 0xfb, 0x8f,
			0x38, 0xb4, 0x88, 0xbf,
			0x38, 0xb4, 0x02, 0x60,
			0x38, 0xb4, 0x7d, 0x6e,
			0x38, 0xb4, 0x8f, 0xe0,
			0x38, 0xb4, 0xe1, 0xfc,
			0x38, 0xb4, 0xfd, 0x8f,
			0x38, 0xb4, 0x88, 0xbf,
			0x38, 0xb4, 0x02, 0x63,
			0x38, 0xb4, 0x7d, 0x6e,
			0x38, 0xb4, 0x8f, 0xe0,
			0x38, 0xb4, 0xe1, 0xfe,
			0x38, 0xb4, 0xff, 0x8f,
			0x38, 0xb4, 0x88, 0xbf,
			0x38, 0xb4, 0x02, 0x66,
			0x38, 0xb4, 0x7d, 0x6e,
			0x38, 0xb4, 0x88, 0xaf,
			0x38, 0xb4, 0xe1, 0x3c,
			0x38, 0xb4, 0xa1, 0x85,
			0x38, 0xb4, 0x21, 0x1b,
			0x38, 0xb4, 0x37, 0xad,
			0x38, 0xb4, 0x1f, 0x34,
			0x38, 0xb4, 0xe0, 0x44,
			0x38, 0xb4, 0x8a, 0x85,
			0x38, 0xb4, 0x85, 0xe1,
			0x38, 0xb4, 0xbf, 0x8b,
			0x38, 0xb4, 0x5d, 0x88,
			0x38, 0xb4, 0x6e, 0x02,
			0x38, 0xb4, 0xe0, 0x7d,
			0x38, 0xb4, 0x90, 0x85,
			0x38, 0xb4, 0x85, 0xe1,
			0x38, 0xb4, 0xbf, 0x91,
			0x38, 0xb4, 0x60, 0x88,
			0x38, 0xb4, 0x6e, 0x02,
			0x38, 0xb4, 0xe0, 0x7d,
			0x38, 0xb4, 0x96, 0x85,
			0x38, 0xb4, 0x85, 0xe1,
			0x38, 0xb4, 0xbf, 0x97,
			0x38, 0xb4, 0x63, 0x88,
			0x38, 0xb4, 0x6e, 0x02,
			0x38, 0xb4, 0xe0, 0x7d,
			0x38, 0xb4, 0x9c, 0x85,
			0x38, 0xb4, 0x85, 0xe1,
			0x38, 0xb4, 0xbf, 0x9d,
			0x38, 0xb4, 0x66, 0x88,
			0x38, 0xb4, 0x6e, 0x02,
			0x38, 0xb4, 0xae, 0x7d,
			0x38, 0xb4, 0x1f, 0x40,
			0x38, 0xb4, 0xe0, 0x44,
			0x38, 0xb4, 0x8c, 0x85,
			0x38, 0xb4, 0x85, 0xe1,
			0x38, 0xb4, 0xbf, 0x8d,
			0x38, 0xb4, 0x5d, 0x88,
			0x38, 0xb4, 0x6e, 0x02,
			0x38, 0xb4, 0xe0, 0x7d,
			0x38, 0xb4, 0x92, 0x85,
			0x38, 0xb4, 0x85, 0xe1,
			0x38, 0xb4, 0xbf, 0x93,
			0x38, 0xb4, 0x60, 0x88,
			0x38, 0xb4, 0x6e, 0x02,
			0x38, 0xb4, 0xe0, 0x7d,
			0x38, 0xb4, 0x98, 0x85,
			0x38, 0xb4, 0x85, 0xe1,
			0x38, 0xb4, 0xbf, 0x99,
			0x38, 0xb4, 0x63, 0x88,
			0x38, 0xb4, 0x6e, 0x02,
			0x38, 0xb4, 0xe0, 0x7d,
			0x38, 0xb4, 0x9e, 0x85,
			0x38, 0xb4, 0x85, 0xe1,
			0x38, 0xb4, 0xbf, 0x9f,
			0x38, 0xb4, 0x66, 0x88,
			0x38, 0xb4, 0x6e, 0x02,
			0x38, 0xb4, 0xae, 0x7d,
			0x38, 0xb4, 0xe1, 0x0c,
			0x38, 0xb4, 0xb3, 0x85,
			0x38, 0xb4, 0x04, 0x39,
			0x38, 0xb4, 0x2f, 0xac,
			0x38, 0xb4, 0xee, 0x04,
			0x38, 0xb4, 0xb3, 0x85,
			0x38, 0xb4, 0xaf, 0x00,
			0x38, 0xb4, 0xd9, 0x39,
			0x38, 0xb4, 0xac, 0x22,
			0x38, 0xb4, 0xf0, 0xea,
			0x38, 0xb4, 0xf6, 0xac,
			0x38, 0xb4, 0xac, 0xf0,
			0x38, 0xb4, 0xf0, 0xfa,
			0x38, 0xb4, 0xf8, 0xac,
			0x38, 0xb4, 0xac, 0xf0,
			0x38, 0xb4, 0xf0, 0xfc,
			0x38, 0xb4, 0x00, 0xad,
			0x38, 0xb4, 0xac, 0xf0,
			0x38, 0xb4, 0xf0, 0xfe,
			0x38, 0xb4, 0xf0, 0xac,
			0x38, 0xb4, 0xac, 0xf0,
			0x38, 0xb4, 0xf0, 0xf4,
			0x38, 0xb4, 0xf2, 0xac,
			0x38, 0xb4, 0xac, 0xf0,
			0x38, 0xb4, 0xf0, 0xb0,
			0x38, 0xb4, 0xae, 0xac,
			0x38, 0xb4, 0xac, 0xf0,
			0x38, 0xb4, 0xf0, 0xac,
			0x38, 0xb4, 0xaa, 0xac,
			0x38, 0xb4, 0x00, 0xa1,
			0x38, 0xb4, 0xe1, 0x0c,
			0x38, 0xb4, 0xf7, 0x8f,
			0x38, 0xb4, 0x88, 0xbf,
			0x38, 0xb4, 0x02, 0x84,
			0x38, 0xb4, 0x7d, 0x6e,
			0x38, 0xb4, 0x26, 0xaf,
			0x38, 0xb4, 0xe1, 0xe9,
			0x38, 0xb4, 0xf6, 0x8f,
			0x38, 0xb4, 0x88, 0xbf,
			0x38, 0xb4, 0x02, 0x84,
			0x38, 0xb4, 0x7d, 0x6e,
			0x38, 0xb4, 0x26, 0xaf,
			0x38, 0xb4, 0x20, 0xf5,
			0x38, 0xb4, 0x86, 0xac,
			0x38, 0xb4, 0x88, 0xbf,
			0x38, 0xb4, 0x02, 0x3f,
			0x38, 0xb4, 0x9c, 0x6e,
			0x38, 0xb4, 0x28, 0xad,
			0x38, 0xb4, 0xaf, 0x03,
			0x38, 0xb4, 0x24, 0x33,
			0x38, 0xb4, 0x38, 0xad,
			0x38, 0xb4, 0xaf, 0x03,
			0x38, 0xb4, 0xe6, 0x32,
			0x38, 0xb4, 0x32, 0xaf,
			0x38, 0xb4, 0x00, 0xfb,
			0x36, 0xb4, 0x7c, 0xb8,
			0x38, 0xb4, 0xf6, 0x8f,
			0x36, 0xb4, 0x7e, 0xb8,
			0x38, 0xb4, 0x05, 0x07,
			0x36, 0xb4, 0x7c, 0xb8,
			0x38, 0xb4, 0xf8, 0x8f,
			0x36, 0xb4, 0x7e, 0xb8,
			0x38, 0xb4, 0xcc, 0x19,
			0x36, 0xb4, 0x7c, 0xb8,
			0x38, 0xb4, 0xfa, 0x8f,
			0x36, 0xb4, 0x7e, 0xb8,
			0x38, 0xb4, 0xe3, 0x28,
			0x36, 0xb4, 0x7c, 0xb8,
			0x38, 0xb4, 0xfc, 0x8f,
			0x36, 0xb4, 0x7e, 0xb8,
			0x38, 0xb4, 0x47, 0x10,
			0x36, 0xb4, 0x7c, 0xb8,
			0x38, 0xb4, 0xfe, 0x8f,
			0x36, 0xb4, 0x7e, 0xb8,
			0x38, 0xb4, 0x45, 0x0a,
			0x36, 0xb4, 0x5e, 0xb8,
			0x38, 0xb4, 0x1e, 0x27,
			0x36, 0xb4, 0x60, 0xb8,
			0x38, 0xb4, 0x46, 0x38,
			0x36, 0xb4, 0x62, 0xb8,
			0x38, 0xb4, 0xe6, 0x26,
			0x36, 0xb4, 0x64, 0xb8,
			0x38, 0xb4, 0xe3, 0x32,
			0x36, 0xb4, 0x86, 0xb8,
			0x38, 0xb4, 0xff, 0xff,
			0x36, 0xb4, 0x88, 0xb8,
			0x38, 0xb4, 0xff, 0xff,
			0x36, 0xb4, 0x8a, 0xb8,
			0x38, 0xb4, 0xff, 0xff,
			0x36, 0xb4, 0x8c, 0xb8,
			0x38, 0xb4, 0xff, 0xff,
			0x36, 0xb4, 0x38, 0xb8,
			0x38, 0xb4, 0x0f, 0x00,
			0x6c, 0xe8, 0x00, 0xb0,
			0x20, 0xb8, 0x10, 0x00,
			0x6c, 0xe8, 0x00, 0xa0,
			0x36, 0xb4, 0x6e, 0x84,
			0x38, 0xb4, 0x84, 0xaf,
			0x38, 0xb4, 0xaf, 0x86,
			0x38, 0xb4, 0x90, 0x86,
			0x38, 0xb4, 0x86, 0xaf,
			0x38, 0xb4, 0xaf, 0xa4,
			0x38, 0xb4, 0xa4, 0x86,
			0x38, 0xb4, 0x86, 0xaf,
			0x38, 0xb4, 0xaf, 0xa4,
			0x38, 0xb4, 0xa4, 0x86,
			0x38, 0xb4, 0x86, 0xaf,
			0x38, 0xb4, 0xaf, 0xa4,
			0x38, 0xb4, 0xa4, 0x86,
			0x38, 0xb4, 0x82, 0xee,
			0x38, 0xb4, 0x00, 0x5f,
			0x38, 0xb4, 0x84, 0x02,
			0x38, 0xb4, 0xaf, 0x90,
			0x38, 0xb4, 0x41, 0x04,
			0x38, 0xb4, 0xe0, 0xf8,
			0x38, 0xb4, 0xf3, 0x8f,
			0x38, 0xb4, 0x00, 0xa0,
			0x38, 0xb4, 0x02, 0x05,
			0x38, 0xb4, 0xa4, 0x84,
			0x38, 0xb4, 0x06, 0xae,
			0x38, 0xb4, 0x01, 0xa0,
			0x38, 0xb4, 0x02, 0x03,
			0x38, 0xb4, 0xc8, 0x84,
			0x38, 0xb4, 0x04, 0xfc,
			0x38, 0xb4, 0xf9, 0xf8,
			0x38, 0xb4, 0x59, 0xef,
			0x38, 0xb4, 0x80, 0xe0,
			0x38, 0xb4, 0xad, 0x15,
			0x38, 0xb4, 0x02, 0x27,
			0x38, 0xb4, 0x03, 0xae,
			0x38, 0xb4, 0x84, 0xaf,
			0x38, 0xb4, 0xbf, 0xc3,
			0x38, 0xb4, 0xca, 0x53,
			0x38, 0xb4, 0x52, 0x02,
			0x38, 0xb4, 0xad, 0xc8,
			0x38, 0xb4, 0x07, 0x28,
			0x38, 0xb4, 0x85, 0x02,
			0x38, 0xb4, 0xee, 0x2c,
			0x38, 0xb4, 0xf3, 0x8f,
			0x38, 0xb4, 0xef, 0x01,
			0x38, 0xb4, 0xfd, 0x95,
			0x38, 0xb4, 0x04, 0xfc,
			0x38, 0xb4, 0xf9, 0xf8,
			0x38, 0xb4, 0xef, 0xfa,
			0x38, 0xb4, 0xbf, 0x69,
			0x38, 0xb4, 0xca, 0x53,
			0x38, 0xb4, 0x52, 0x02,
			0x38, 0xb4, 0xac, 0xc8,
			0x38, 0xb4, 0x22, 0x28,
			0x38, 0xb4, 0x80, 0xd4,
			0x38, 0xb4, 0xbf, 0x00,
			0x38, 0xb4, 0x84, 0x86,
			0x38, 0xb4, 0x52, 0x02,
			0x38, 0xb4, 0xbf, 0xa9,
			0x38, 0xb4, 0x87, 0x86,
			0x38, 0xb4, 0x52, 0x02,
			0x38, 0xb4, 0xbf, 0xa9,
			0x38, 0xb4, 0x8a, 0x86,
			0x38, 0xb4, 0x52, 0x02,
			0x38, 0xb4, 0xbf, 0xa9,
			0x38, 0xb4, 0x8d, 0x86,
			0x38, 0xb4, 0x52, 0x02,
			0x38, 0xb4, 0xee, 0xa9,
			0x38, 0xb4, 0xf3, 0x8f,
			0x38, 0xb4, 0xaf, 0x00,
			0x38, 0xb4, 0x26, 0x85,
			0x38, 0xb4, 0x8f, 0xe0,
			0x38, 0xb4, 0xe1, 0xf4,
			0x38, 0xb4, 0xf5, 0x8f,
			0x38, 0xb4, 0x8f, 0xe2,
			0x38, 0xb4, 0xe3, 0xf6,
			0x38, 0xb4, 0xf7, 0x8f,
			0x38, 0xb4, 0x45, 0x1b,
			0x38, 0xb4, 0x27, 0xac,
			0x38, 0xb4, 0xee, 0x0e,
			0x38, 0xb4, 0xf4, 0x8f,
			0x38, 0xb4, 0xee, 0x00,
			0x38, 0xb4, 0xf5, 0x8f,
			0x38, 0xb4, 0x02, 0x00,
			0x38, 0xb4, 0x2c, 0x85,
			0x38, 0xb4, 0x85, 0xaf,
			0x38, 0xb4, 0xe0, 0x26,
			0x38, 0xb4, 0xf4, 0x8f,
			0x38, 0xb4, 0x8f, 0xe1,
			0x38, 0xb4, 0x2c, 0xf5,
			0x38, 0xb4, 0x01, 0x00,
			0x38, 0xb4, 0x8f, 0xe4,
			0x38, 0xb4, 0xe5, 0xf4,
			0x38, 0xb4, 0xf5, 0x8f,
			0x38, 0xb4, 0x96, 0xef,
			0x38, 0xb4, 0xfd, 0xfe,
			0x38, 0xb4, 0x04, 0xfc,
			0x38, 0xb4, 0xf9, 0xf8,
			0x38, 0xb4, 0x59, 0xef,
			0x38, 0xb4, 0x53, 0xbf,
			0x38, 0xb4, 0x02, 0x22,
			0x38, 0xb4, 0xc8, 0x52,
			0x38, 0xb4, 0x8b, 0xa1,
			0x38, 0xb4, 0xae, 0x02,
			0x38, 0xb4, 0xaf, 0x03,
			0x38, 0xb4, 0xda, 0x85,
			0x38, 0xb4, 0x57, 0xbf,
			0x38, 0xb4, 0x02, 0x72,
			0x38, 0xb4, 0xc8, 0x52,
			0x38, 0xb4, 0x8f, 0xe4,
			0x38, 0xb4, 0xe5, 0xf8,
			0x38, 0xb4, 0xf9, 0x8f,
			0x38, 0xb4, 0x57, 0xbf,
			0x38, 0xb4, 0x02, 0x75,
			0x38, 0xb4, 0xc8, 0x52,
			0x38, 0xb4, 0x8f, 0xe4,
			0x38, 0xb4, 0xe5, 0xfa,
			0x38, 0xb4, 0xfb, 0x8f,
			0x38, 0xb4, 0x57, 0xbf,
			0x38, 0xb4, 0x02, 0x78,
			0x38, 0xb4, 0xc8, 0x52,
			0x38, 0xb4, 0x8f, 0xe4,
			0x38, 0xb4, 0xe5, 0xfc,
			0x38, 0xb4, 0xfd, 0x8f,
			0x38, 0xb4, 0x57, 0xbf,
			0x38, 0xb4, 0x02, 0x7b,
			0x38, 0xb4, 0xc8, 0x52,
			0x38, 0xb4, 0x8f, 0xe4,
			0x38, 0xb4, 0xe5, 0xfe,
			0x38, 0xb4, 0xff, 0x8f,
			0x38, 0xb4, 0x57, 0xbf,
			0x38, 0xb4, 0x02, 0x6c,
			0x38, 0xb4, 0xc8, 0x52,
			0x38, 0xb4, 0x02, 0xa1,
			0x38, 0xb4, 0xee, 0x13,
			0x38, 0xb4, 0xfc, 0x8f,
			0x38, 0xb4, 0xee, 0x80,
			0x38, 0xb4, 0xfd, 0x8f,
			0x38, 0xb4, 0xee, 0x00,
			0x38, 0xb4, 0xfe, 0x8f,
			0x38, 0xb4, 0xee, 0x80,
			0x38, 0xb4, 0xff, 0x8f,
			0x38, 0xb4, 0xaf, 0x00,
			0x38, 0xb4, 0x99, 0x85,
			0x38, 0xb4, 0x01, 0xa1,
			0x38, 0xb4, 0xbf, 0x0c,
			0x38, 0xb4, 0x4c, 0x53,
			0x38, 0xb4, 0x52, 0x02,
			0x38, 0xb4, 0xa1, 0xc8,
			0x38, 0xb4, 0x03, 0x03,
			0x38, 0xb4, 0x85, 0xaf,
			0x38, 0xb4, 0xbf, 0x77,
			0x38, 0xb4, 0x22, 0x53,
			0x38, 0xb4, 0x52, 0x02,
			0x38, 0xb4, 0xa1, 0xc8,
			0x38, 0xb4, 0x02, 0x8b,
			0x38, 0xb4, 0x03, 0xae,
			0x38, 0xb4, 0x86, 0xaf,
			0x38, 0xb4, 0xe0, 0x64,
			0x38, 0xb4, 0xf8, 0x8f,
			0x38, 0xb4, 0x8f, 0xe1,
			0x38, 0xb4, 0xbf, 0xf9,
			0x38, 0xb4, 0x84, 0x86,
			0x38, 0xb4, 0x52, 0x02,
			0x38, 0xb4, 0xe0, 0xa9,
			0x38, 0xb4, 0xfa, 0x8f,
			0x38, 0xb4, 0x8f, 0xe1,
			0x38, 0xb4, 0xbf, 0xfb,
			0x38, 0xb4, 0x87, 0x86,
			0x38, 0xb4, 0x52, 0x02,
			0x38, 0xb4, 0xe0, 0xa9,
			0x38, 0xb4, 0xfc, 0x8f,
			0x38, 0xb4, 0x8f, 0xe1,
			0x38, 0xb4, 0xbf, 0xfd,
			0x38, 0xb4, 0x8a, 0x86,
			0x38, 0xb4, 0x52, 0x02,
			0x38, 0xb4, 0xe0, 0xa9,
			0x38, 0xb4, 0xfe, 0x8f,
			0x38, 0xb4, 0x8f, 0xe1,
			0x38, 0xb4, 0xbf, 0xff,
			0x38, 0xb4, 0x8d, 0x86,
			0x38, 0xb4, 0x52, 0x02,
			0x38, 0xb4, 0xaf, 0xa9,
			0x38, 0xb4, 0x7f, 0x86,
			0x38, 0xb4, 0x53, 0xbf,
			0x38, 0xb4, 0x02, 0x22,
			0x38, 0xb4, 0xc8, 0x52,
			0x38, 0xb4, 0x44, 0xa1,
			0x38, 0xb4, 0xbf, 0x3c,
			0x38, 0xb4, 0x7b, 0x54,
			0x38, 0xb4, 0x52, 0x02,
			0x38, 0xb4, 0xe4, 0xc8,
			0x38, 0xb4, 0xf8, 0x8f,
			0x38, 0xb4, 0x8f, 0xe5,
			0x38, 0xb4, 0xbf, 0xf9,
			0x38, 0xb4, 0x7e, 0x54,
			0x38, 0xb4, 0x52, 0x02,
			0x38, 0xb4, 0xe4, 0xc8,
			0x38, 0xb4, 0xfa, 0x8f,
			0x38, 0xb4, 0x8f, 0xe5,
			0x38, 0xb4, 0xbf, 0xfb,
			0x38, 0xb4, 0x81, 0x54,
			0x38, 0xb4, 0x52, 0x02,
			0x38, 0xb4, 0xe4, 0xc8,
			0x38, 0xb4, 0xfc, 0x8f,
			0x38, 0xb4, 0x8f, 0xe5,
			0x38, 0xb4, 0xbf, 0xfd,
			0x38, 0xb4, 0x84, 0x54,
			0x38, 0xb4, 0x52, 0x02,
			0x38, 0xb4, 0xe4, 0xc8,
			0x38, 0xb4, 0xfe, 0x8f,
			0x38, 0xb4, 0x8f, 0xe5,
			0x38, 0xb4, 0xbf, 0xff,
			0x38, 0xb4, 0x22, 0x53,
			0x38, 0xb4, 0x52, 0x02,
			0x38, 0xb4, 0xa1, 0xc8,
			0x38, 0xb4, 0x48, 0x44,
			0x38, 0xb4, 0x85, 0xaf,
			0x38, 0xb4, 0xbf, 0xa7,
			0x38, 0xb4, 0x22, 0x53,
			0x38, 0xb4, 0x52, 0x02,
			0x38, 0xb4, 0xa1, 0xc8,
			0x38, 0xb4, 0x3c, 0x31,
			0x38, 0xb4, 0x54, 0xbf,
			0x38, 0xb4, 0x02, 0x7b,
			0x38, 0xb4, 0xc8, 0x52,
			0x38, 0xb4, 0x8f, 0xe4,
			0x38, 0xb4, 0xe5, 0xf8,
			0x38, 0xb4, 0xf9, 0x8f,
			0x38, 0xb4, 0x54, 0xbf,
			0x38, 0xb4, 0x02, 0x7e,
			0x38, 0xb4, 0xc8, 0x52,
			0x38, 0xb4, 0x8f, 0xe4,
			0x38, 0xb4, 0xe5, 0xfa,
			0x38, 0xb4, 0xfb, 0x8f,
			0x38, 0xb4, 0x54, 0xbf,
			0x38, 0xb4, 0x02, 0x81,
			0x38, 0xb4, 0xc8, 0x52,
			0x38, 0xb4, 0x8f, 0xe4,
			0x38, 0xb4, 0xe5, 0xfc,
			0x38, 0xb4, 0xfd, 0x8f,
			0x38, 0xb4, 0x54, 0xbf,
			0x38, 0xb4, 0x02, 0x84,
			0x38, 0xb4, 0xc8, 0x52,
			0x38, 0xb4, 0x8f, 0xe4,
			0x38, 0xb4, 0xe5, 0xfe,
			0x38, 0xb4, 0xff, 0x8f,
			0x38, 0xb4, 0x53, 0xbf,
			0x38, 0xb4, 0x02, 0x22,
			0x38, 0xb4, 0xc8, 0x52,
			0x38, 0xb4, 0x31, 0xa1,
			0x38, 0xb4, 0xaf, 0x03,
			0x38, 0xb4, 0xa7, 0x85,
			0x38, 0xb4, 0x80, 0xd4,
			0x38, 0xb4, 0xbf, 0x00,
			0x38, 0xb4, 0x84, 0x86,
			0x38, 0xb4, 0x52, 0x02,
			0x38, 0xb4, 0xbf, 0xa9,
			0x38, 0xb4, 0x87, 0x86,
			0x38, 0xb4, 0x52, 0x02,
			0x38, 0xb4, 0xbf, 0xa9,
			0x38, 0xb4, 0x8a, 0x86,
			0x38, 0xb4, 0x52, 0x02,
			0x38, 0xb4, 0xbf, 0xa9,
			0x38, 0xb4, 0x8d, 0x86,
			0x38, 0xb4, 0x52, 0x02,
			0x38, 0xb4, 0xef, 0xa9,
			0x38, 0xb4, 0xfd, 0x95,
			0x38, 0xb4, 0x04, 0xfc,
			0x38, 0xb4, 0xd1, 0xf0,
			0x38, 0xb4, 0xf0, 0x2a,
			0x38, 0xb4, 0x2c, 0xd1,
			0x38, 0xb4, 0xd1, 0xf0,
			0x38, 0xb4, 0xf0, 0x44,
			0x38, 0xb4, 0x46, 0xd1,
			0x38, 0xb4, 0x86, 0xbf,
			0x38, 0xb4, 0x02, 0xa1,
			0x38, 0xb4, 0xc8, 0x52,
			0x38, 0xb4, 0x86, 0xbf,
			0x38, 0xb4, 0x02, 0xa1,
			0x38, 0xb4, 0xc8, 0x52,
			0x38, 0xb4, 0x01, 0xd1,
			0x38, 0xb4, 0x06, 0xaf,
			0x38, 0xb4, 0x70, 0xa5,
			0x38, 0xb4, 0x42, 0xce,
			0x36, 0xb4, 0x18, 0xb8,
			0x38, 0xb4, 0x3d, 0x04,
			0x36, 0xb4, 0x1a, 0xb8,
			0x38, 0xb4, 0xa3, 0x06,
			0x36, 0xb4, 0x1c, 0xb8,
			0x38, 0xb4, 0xff, 0xff,
			0x36, 0xb4, 0x1e, 0xb8,
			0x38, 0xb4, 0xff, 0xff,
			0x36, 0xb4, 0x50, 0xb8,
			0xff, 0xff, 0xff, 0xff,
			0x38, 0xb4, 0xff, 0xff,
			0x36, 0xb4, 0x52, 0xb8,
			0x38, 0xb4, 0xff, 0xff,
			0x36, 0xb4, 0x78, 0xb8,
			0x38, 0xb4, 0xff, 0xff,
			0x36, 0xb4, 0x84, 0xb8,
			0x38, 0xb4, 0xff, 0xff,
			0x36, 0xb4, 0x32, 0xb8,
			0x38, 0xb4, 0x03, 0x00,
			0x36, 0xb4, 0x00, 0x00,
			0x38, 0xb4, 0x00, 0x00,
			0x36, 0xb4, 0x2e, 0xb8,
			0x38, 0xb4, 0x00, 0x00,
			0x36, 0xb4, 0x24, 0x80,
			0x38, 0xb4, 0x00, 0x00,
			0x36, 0xb4, 0x1e, 0x80,
			0x38, 0xb4, 0x21, 0x00,
			0x6c, 0xe8, 0x00, 0xb0,
			0x20, 0xb8, 0x00, 0x00,
			0xff, 0xff, 0xff, 0xff};

		if (sram_read(tp, SRAM_GPHY_FW_VER) < 0x0021) {
			data = ram13;
			len = sizeof(ram13);
		}
	}

	if (!data)
		return;

	if (rtl_phy_patch_request(tp, true, wait))
		return;

	while (len) {
		u32 size;
		int i;

		if (len < 2048)
			size = len;
		else
			size = 2048;

		ocp_data = ocp_read_word(tp, MCU_TYPE_USB, USB_GPHY_CTRL);
		ocp_data |= GPHY_PATCH_DONE | BACKUP_RESTRORE;
		ocp_write_word(tp, MCU_TYPE_USB, USB_GPHY_CTRL, ocp_data);

		generic_ocp_write(tp, 0x9A00, 0xff, size, data, MCU_TYPE_USB);

		data += size;
		len -= size;

		ocp_data = ocp_read_word(tp, MCU_TYPE_PLA, PLA_POL_GPIO_CTRL);
		ocp_data |= POL_GPHY_PATCH;
		ocp_write_word(tp, MCU_TYPE_PLA, PLA_POL_GPIO_CTRL, ocp_data);

		for (i = 0; i < 1000; i++) {
			if (!(ocp_read_word(tp, MCU_TYPE_PLA, PLA_POL_GPIO_CTRL) & POL_GPHY_PATCH))
				break;
		}

		if (i == 1000) {
			dev_err(&tp->intf->dev, "ram code speedup mode fail\n");
			break;
		}
	}

	rtl_reset_ocp_base(tp);

	rtl_phy_patch_request(tp, false, wait);
}

static void r8156_ram_code(struct r8152 *tp, bool power_cut)
{
	u16 data;

	rtl_reset_ocp_base(tp);

	if (tp->version == RTL_VER_10) {
		rtl_pre_ram_code(tp, 0x8024, 0x8600, !power_cut);

		data = ocp_reg_read(tp, OCP_PHY_PATCH_CMD);
		data |= BIT(7);
		ocp_reg_write(tp, OCP_PHY_PATCH_CMD, data);

		/* nc0_patch_180504_usb */
		sram_write(tp, 0xA016, 0x0000);
		sram_write(tp, 0xA012, 0x0000);
		ocp_reg_write(tp, OCP_SRAM_ADDR, 0xA014);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8010);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8013);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8021);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x802f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x803d);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8042);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8051);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8051);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa088);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a50);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8008);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd014);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd1a3);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd700);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x401a);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd707);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x40c2);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x60a6);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd700);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5f8b);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a86);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a6c);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8080);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd019);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd1a2);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd700);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x401a);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd707);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x40c4);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x60a6);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd700);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5f8b);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a86);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a84);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd503);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8970);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0c07);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0901);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd500);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xce01);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xcf09);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd705);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x4000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xceff);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xaf0a);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd504);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1213);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8401);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd500);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8580);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1253);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd064);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd181);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd704);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x4018);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd504);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xc50f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd706);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x2c59);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x804d);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xc60f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xf002);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xc605);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xae02);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x10fd);
		sram_write(tp, 0xA026, 0xffff);
		sram_write(tp, 0xA024, 0xffff);
		sram_write(tp, 0xA022, 0x10f4);
		sram_write(tp, 0xA020, 0x1252);
		sram_write(tp, 0xA006, 0x1206);
		sram_write(tp, 0xA004, 0x0a78);
		sram_write(tp, 0xA002, 0x0a60);
		sram_write(tp, 0xA000, 0x0a4f);
		sram_write(tp, 0xA008, 0x3f00);

		/* nc1_patch_180423_cml_usb */
		sram_write(tp, 0xA016, 0x0010);
		sram_write(tp, 0xA012, 0x0000);
		ocp_reg_write(tp, OCP_SRAM_ADDR, 0xA014);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8010);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8066);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x807c);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8089);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x808e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x80a0);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x80b2);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x80c2);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd501);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xce01);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd700);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x62db);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x655c);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd73e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x60e9);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x614a);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x61ab);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0c0f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0501);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0304);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0c0f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0503);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0304);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0c0f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0505);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0304);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0c0f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0509);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0304);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x653c);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd73e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x60e9);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x614a);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x61ab);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0c0f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0503);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0304);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0c0f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0502);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0304);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0c0f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0506);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0304);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0c0f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x050a);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0304);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd73e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x60e9);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x614a);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x61ab);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0c0f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0505);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0304);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0c0f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0506);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0304);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0c0f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0504);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0304);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0c0f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x050c);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0304);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd73e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x60e9);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x614a);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x61ab);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0c0f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0509);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0304);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0c0f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x050a);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0304);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0c0f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x050c);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0304);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0c0f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0508);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0304);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd501);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xce01);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd73e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x60e9);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x614a);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x61ab);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0c0f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0501);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0321);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0c0f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0502);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0321);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0c0f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0504);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0321);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0c0f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0508);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0321);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0346);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd501);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xce01);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8208);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x609d);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa50f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x001a);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0c0f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0503);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x001a);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x607d);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x00ab);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x00ab);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd501);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xce01);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd700);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x60fd);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa50f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xce00);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd500);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xaa0f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x017b);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0c0f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0503);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xce00);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd500);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0c0f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a05);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x017b);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd501);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xce01);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd700);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x60fd);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa50f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xce00);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd500);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xaa0f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x01e0);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0c0f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0503);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xce00);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd500);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0c0f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a05);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x01e0);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd700);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x60fd);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa50f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xce00);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd500);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xaa0f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0231);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0c0f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0503);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xce00);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd500);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0c0f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a05);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0231);
		sram_write(tp, 0xA08E, 0xffff);
		sram_write(tp, 0xA08C, 0x0221);
		sram_write(tp, 0xA08A, 0x01ce);
		sram_write(tp, 0xA088, 0x0169);
		sram_write(tp, 0xA086, 0x00a6);
		sram_write(tp, 0xA084, 0x000d);
		sram_write(tp, 0xA082, 0x0308);
		sram_write(tp, 0xA080, 0x029f);
		sram_write(tp, 0xA090, 0x007f);

		/* nc2_patch_180508_usb */
		sram_write(tp, 0xA016, 0x0020);
		sram_write(tp, 0xA012, 0x0000);
		ocp_reg_write(tp, OCP_SRAM_ADDR, 0xA014);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8010);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8017);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x801b);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8029);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8054);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x805a);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8064);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x80a7);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x9430);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x9480);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xb408);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd120);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd057);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x064b);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xcb80);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x9906);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0567);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xcb94);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8190);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x82a0);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x800a);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8406);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8010);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa740);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8dff);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x07e4);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa840);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0773);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xcb91);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd700);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x4063);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd139);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xf002);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd140);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd040);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xb404);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0c0f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0d00);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x07dc);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa610);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa110);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa2a0);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa404);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd704);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x4045);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa180);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd704);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x405d);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa720);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0742);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x07ec);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd700);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5f74);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0742);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd702);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x7fb6);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8190);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x82a0);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8404);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8610);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0c0f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0d01);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x07dc);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x064b);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x07c0);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd700);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5fa7);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0481);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x94bc);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x870c);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa190);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa00a);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa280);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa404);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8220);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x078e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xcb92);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa840);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd700);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x4063);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd140);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xf002);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd150);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd040);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd703);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x60a0);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x6121);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x61a2);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x6223);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xf02f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0cf0);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0d10);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8010);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa740);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xf00f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0cf0);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0d20);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8010);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa740);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xf00a);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0cf0);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0d30);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8010);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa740);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xf005);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0cf0);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0d40);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8010);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa740);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x07e4);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa610);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa008);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd704);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x4046);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa002);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd704);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x405d);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa720);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0742);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x07f7);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd700);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5f74);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0742);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd702);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x7fb5);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x800a);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0cf0);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0d00);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x07e4);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8010);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa740);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd701);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x3ad4);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0537);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8610);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8840);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x064b);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8301);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x800a);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8190);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x82a0);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8404);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa70c);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x9402);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x890c);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8840);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x064b);
		sram_write(tp, 0xA10E, 0x0642);
		sram_write(tp, 0xA10C, 0x0686);
		sram_write(tp, 0xA10A, 0x0788);
		sram_write(tp, 0xA108, 0x047b);
		sram_write(tp, 0xA106, 0x065c);
		sram_write(tp, 0xA104, 0x0769);
		sram_write(tp, 0xA102, 0x0565);
		sram_write(tp, 0xA100, 0x06f9);
		sram_write(tp, 0xA110, 0x00ff);

		/* uc2_patch_180507_usb */
		sram_write(tp, 0xb87c, 0x8530);
		ocp_reg_write(tp, OCP_SRAM_ADDR, 0xb87e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xaf85);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x3caf);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8593);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xaf85);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x9caf);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x85a5);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xbf86);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd702);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5afb);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xe083);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xfb0c);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x020d);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x021b);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x10bf);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x86d7);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x025a);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xb7bf);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x86da);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x025a);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xfbe0);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x83fc);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0c02);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0d02);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1b10);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xbf86);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xda02);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5ab7);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xbf86);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xdd02);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5afb);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xe083);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xfd0c);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x020d);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x021b);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x10bf);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x86dd);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x025a);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xb7bf);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x86e0);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x025a);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xfbe0);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x83fe);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0c02);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0d02);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1b10);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xbf86);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xe002);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5ab7);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xaf2f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xbd02);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x2cac);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0286);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x65af);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x212b);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x022c);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x6002);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x86b6);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xaf21);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0cd1);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x03bf);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8710);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x025a);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xb7bf);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x870d);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x025a);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xb7bf);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8719);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x025a);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xb7bf);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8716);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x025a);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xb7bf);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x871f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x025a);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xb7bf);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x871c);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x025a);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xb7bf);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8728);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x025a);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xb7bf);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8725);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x025a);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xb7bf);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8707);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x025a);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xfbad);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x281c);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd100);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xbf87);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a02);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5ab7);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xbf87);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1302);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5ab7);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xbf87);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x2202);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5ab7);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xbf87);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x2b02);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5ab7);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xae1a);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd101);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xbf87);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a02);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5ab7);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xbf87);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1302);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5ab7);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xbf87);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x2202);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5ab7);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xbf87);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x2b02);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5ab7);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd101);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xbf87);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x3402);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5ab7);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xbf87);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x3102);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5ab7);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xbf87);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x3d02);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5ab7);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xbf87);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x3a02);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5ab7);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xbf87);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x4302);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5ab7);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xbf87);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x4002);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5ab7);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xbf87);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x4c02);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5ab7);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xbf87);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x4902);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5ab7);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd100);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xbf87);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x2e02);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5ab7);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xbf87);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x3702);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5ab7);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xbf87);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x4602);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5ab7);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xbf87);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x4f02);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5ab7);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xaf35);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x7ff8);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xfaef);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x69bf);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x86e3);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x025a);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xfbbf);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x86fb);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x025a);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xb7bf);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x86e6);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x025a);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xfbbf);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x86fe);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x025a);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xb7bf);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x86e9);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x025a);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xfbbf);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8701);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x025a);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xb7bf);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x86ec);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x025a);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xfbbf);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8704);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x025a);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xb7bf);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x86ef);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0262);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x7cbf);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x86f2);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0262);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x7cbf);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x86f5);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0262);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x7cbf);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x86f8);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0262);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x7cef);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x96fe);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xfc04);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xf8fa);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xef69);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xbf86);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xef02);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x6273);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xbf86);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xf202);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x6273);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xbf86);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xf502);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x6273);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xbf86);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xf802);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x6273);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xef96);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xfefc);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0420);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xb540);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x53b5);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x4086);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xb540);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xb9b5);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x40c8);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xb03a);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xc8b0);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xbac8);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xb13a);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xc8b1);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xba77);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xbd26);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xffbd);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x2677);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xbd28);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xffbd);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x2840);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xbd26);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xc8bd);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x2640);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xbd28);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xc8bd);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x28bb);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa430);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x98b0);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1eba);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xb01e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xdcb0);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1e98);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xb09e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xbab0);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x9edc);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xb09e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x98b1);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1eba);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xb11e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xdcb1);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1e98);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xb19e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xbab1);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x9edc);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xb19e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x11b0);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1e22);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xb01e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x33b0);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1e11);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xb09e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x22b0);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x9e33);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xb09e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x11b1);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1e22);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xb11e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x33b1);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1e11);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xb19e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x22b1);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x9e33);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xb19e);
		sram_write(tp, 0xb85e, 0x2f71);
		sram_write(tp, 0xb860, 0x20d9);
		sram_write(tp, 0xb862, 0x2109);
		sram_write(tp, 0xb864, 0x34e7);
		sram_write(tp, 0xb878, 0x000f);

		data = ocp_reg_read(tp, OCP_PHY_PATCH_CMD);
		data &= ~BIT(7);
		ocp_reg_write(tp, OCP_PHY_PATCH_CMD, data);

		rtl_post_ram_code(tp, 0x8024, !power_cut);
	} else if (tp->version == RTL_VER_11) {
		rtl_pre_ram_code(tp, 0x8024, 0x8601, !power_cut);

		data = ocp_reg_read(tp, OCP_PHY_PATCH_CMD);
		data |= BIT(7);
		ocp_reg_write(tp, OCP_PHY_PATCH_CMD, data);

		/* nc_patch */
		sram_write(tp, 0xA016, 0x0000);
		sram_write(tp, 0xA012, 0x0000);
		ocp_reg_write(tp, OCP_SRAM_ADDR, 0xA014);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8010);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x808b);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x808f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8093);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8097);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x809d);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x80a1);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x80aa);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd718);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x607b);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x40da);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xf00e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x42da);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xf01e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd718);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x615b);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1456);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x14a4);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x14bc);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd718);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5f2e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xf01c);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1456);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x14a4);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x14bc);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd718);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5f2e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xf024);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1456);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x14a4);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x14bc);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd718);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5f2e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xf02c);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1456);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x14a4);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x14bc);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd718);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5f2e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xf034);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd719);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x4118);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd504);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xac11);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd501);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xce01);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa410);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xce00);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd500);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x4779);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd504);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xac0f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xae01);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd500);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1444);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xf034);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd719);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x4118);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd504);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xac22);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd501);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xce01);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa420);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xce00);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd500);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x4559);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd504);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xac0f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xae01);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd500);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1444);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xf023);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd719);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x4118);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd504);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xac44);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd501);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xce01);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa440);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xce00);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd500);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x4339);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd504);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xac0f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xae01);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd500);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1444);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xf012);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd719);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x4118);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd504);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xac88);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd501);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xce01);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa480);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xce00);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd500);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x4119);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd504);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xac0f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xae01);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd500);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1444);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xf001);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1456);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd718);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5fac);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xc48f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x141b);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd504);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8010);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x121a);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd0b4);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd1bb);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0898);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd0b4);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd1bb);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a0e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd064);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd18a);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0b7e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x401c);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd501);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa804);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8804);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x053b);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd500);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa301);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0648);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xc520);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa201);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd701);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x252d);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1646);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd708);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x4006);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1646);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0308);
		sram_write(tp, 0xA026, 0x0307);
		sram_write(tp, 0xA024, 0x1645);
		sram_write(tp, 0xA022, 0x0647);
		sram_write(tp, 0xA020, 0x053a);
		sram_write(tp, 0xA006, 0x0b7c);
		sram_write(tp, 0xA004, 0x0a0c);
		sram_write(tp, 0xA002, 0x0896);
		sram_write(tp, 0xA000, 0x11a1);
		sram_write(tp, 0xA008, 0xff00);

		/* nc1_patch */
		sram_write(tp, 0xA016, 0x0010);
		sram_write(tp, 0xA012, 0x0000);
		ocp_reg_write(tp, OCP_SRAM_ADDR, 0xA014);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8010);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8015);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x801a);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x801a);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x801a);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x801a);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x801a);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x801a);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xad02);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x02d7);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x00ed);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0c0f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0509);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xc100);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x008f);
		sram_write(tp, 0xA08E, 0xffff);
		sram_write(tp, 0xA08C, 0xffff);
		sram_write(tp, 0xA08A, 0xffff);
		sram_write(tp, 0xA088, 0xffff);
		sram_write(tp, 0xA086, 0xffff);
		sram_write(tp, 0xA084, 0xffff);
		sram_write(tp, 0xA082, 0x008d);
		sram_write(tp, 0xA080, 0x00eb);
		sram_write(tp, 0xA090, 0x0103);

		/* nc2_patch */
		sram_write(tp, 0xA016, 0x0020);
		sram_write(tp, 0xA012, 0x0000);
		ocp_reg_write(tp, OCP_SRAM_ADDR, 0xA014);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8010);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8014);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8018);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8024);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8051);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8055);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8072);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x80dc);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xfffd);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xfffd);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8301);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x800a);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8190);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x82a0);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8404);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa70c);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x9402);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x890c);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8840);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa380);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x066e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xcb91);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd700);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x4063);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd139);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xf002);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd140);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd040);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xb404);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0c0f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0d00);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x07e0);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa610);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa110);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa2a0);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa404);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd704);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x4085);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa180);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa404);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8280);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd704);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x405d);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa720);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0743);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x07f0);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd700);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5f74);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0743);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd702);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x7fb6);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8190);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x82a0);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8404);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8610);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0c0f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0d01);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x07e0);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x066e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd158);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd04d);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x03d4);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x94bc);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x870c);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8380);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd10d);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd040);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x07c4);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd700);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5fb4);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa190);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa00a);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa280);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa404);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa220);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd130);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd040);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x07c4);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd700);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5fb4);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xbb80);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd1c4);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd074);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa301);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd704);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x604b);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa90c);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0556);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xcb92);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd700);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x4063);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd116);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xf002);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd119);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd040);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd703);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x60a0);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x6241);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x63e2);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x6583);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xf054);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd701);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x611e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd701);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x40da);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0cf0);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0d10);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa010);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8740);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xf02f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0cf0);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0d50);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8010);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa740);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xf02a);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd701);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x611e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd701);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x40da);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0cf0);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0d20);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa010);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8740);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xf021);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0cf0);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0d60);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8010);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa740);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xf01c);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd701);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x611e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd701);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x40da);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0cf0);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0d30);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa010);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8740);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xf013);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0cf0);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0d70);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8010);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa740);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xf00e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd701);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x611e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd701);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x40da);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0cf0);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0d40);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa010);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8740);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xf005);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0cf0);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0d80);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8010);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa740);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x07e8);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa610);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd704);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x405d);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa720);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd700);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5ff4);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa008);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd704);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x4046);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa002);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0743);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x07fb);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd703);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x7f6f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x7f4e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x7f2d);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x7f0c);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x800a);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0cf0);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0d00);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x07e8);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8010);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa740);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0743);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd702);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x7fb5);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd701);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x3ad4);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0556);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8610);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x066e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd1f5);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd049);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x01ec);
		sram_write(tp, 0xA10E, 0x01ea);
		sram_write(tp, 0xA10C, 0x06a9);
		sram_write(tp, 0xA10A, 0x078a);
		sram_write(tp, 0xA108, 0x03d2);
		sram_write(tp, 0xA106, 0x067f);
		sram_write(tp, 0xA104, 0x0665);
		sram_write(tp, 0xA102, 0x0000);
		sram_write(tp, 0xA100, 0x0000);
		sram_write(tp, 0xA110, 0x00fc);

		/* uc2 */
		sram_write(tp, 0xb87c, 0x8530);
		ocp_reg_write(tp, OCP_SRAM_ADDR, 0xb87e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xaf85);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x3caf);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8545);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xaf85);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x45af);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8545);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xee82);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xf900);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0103);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xaf03);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xb7f8);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xe0a6);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x00e1);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa601);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xef01);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x58f0);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa080);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x37a1);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8402);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xae16);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa185);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x02ae);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x11a1);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8702);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xae0c);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa188);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x02ae);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x07a1);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8902);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xae02);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xae1c);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xe0b4);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x62e1);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xb463);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x6901);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xe4b4);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x62e5);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xb463);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xe0b4);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x62e1);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xb463);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x6901);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xe4b4);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x62e5);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xb463);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xfc04);
		sram_write(tp, 0xb85e, 0x03b3);
		sram_write(tp, 0xb860, 0xffff);
		sram_write(tp, 0xb862, 0xffff);
		sram_write(tp, 0xb864, 0xffff);
		sram_write(tp, 0xb878, 0x0001);

		/* data_ram_patch_v02_usb */
		sram_write(tp, 0xb892, 0x0000);
		sram_write(tp, 0xb88e, 0xc089);
		ocp_reg_write(tp, OCP_SRAM_ADDR, 0xb890);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x6050);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5f6e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x6e6e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x6e6e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x6e12);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1214);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1516);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x171b);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1b1c);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1f1f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x2021);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x2224);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x2424);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x2424);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x2424);
		sram_write(tp, 0xb88e, 0xc018);
		ocp_reg_write(tp, OCP_SRAM_ADDR, 0xb890);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0af2);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0d4a);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0f26);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x118d);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x14f3);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x175a);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x19c0);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1c26);

		data = ocp_reg_read(tp, OCP_PHY_PATCH_CMD);
		data &= ~BIT(7);
		ocp_reg_write(tp, OCP_PHY_PATCH_CMD, data);

		rtl_post_ram_code(tp, 0x8024, !power_cut);

		/* 100M MLT-3 Tx interpolator coefficient */
		ocp_reg_write(tp, OCP_SRAM_ADDR, 0x81b3);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0043);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x00a7);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x00d6);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x00ec);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x00f6);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x00fb);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x00fd);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x00ff);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x00bb);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0058);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0029);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0013);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0009);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0004);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0002);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0000);
	} else if (tp->version == RTL_VER_12) {
		rtl_pre_ram_code(tp, 0x8024, 0x3700, !power_cut);

		data = ocp_reg_read(tp, OCP_PHY_PATCH_CMD);
		data |= BIT(7);
		ocp_reg_write(tp, OCP_PHY_PATCH_CMD, data);

		/* nc_patch */
		sram_write(tp, 0xA016, 0x0000);
		sram_write(tp, 0xA012, 0x0000);
		ocp_reg_write(tp, OCP_SRAM_ADDR, 0xA014);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8010);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8025);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x803a);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8044);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8083);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x808d);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x808d);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x808d);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd712);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x4077);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd71e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x4159);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd71e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x6099);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x7f44);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1a14);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x9040);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x9201);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1b1a);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd71e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x2425);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1a14);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd71f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x3ce5);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1afb);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1b00);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd712);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x4077);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd71e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x4159);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd71e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x60b9);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x2421);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1c17);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1a14);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x9040);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1c2c);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd71e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x2425);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1a14);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd71f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x3ce5);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1c0f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1c13);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd702);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd501);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x6072);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8401);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xf002);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa401);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x146e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0b77);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd703);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x665d);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x653e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x641f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd700);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x62c4);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x6185);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x6066);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x165a);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xc101);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xcb00);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1945);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd700);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x7fa6);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x807d);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xc102);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xcb00);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1945);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd700);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x2569);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8058);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x807d);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xc104);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xcb00);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1945);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd700);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x7fa4);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x807d);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xc120);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xcb00);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1945);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd703);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x7fbf);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x807d);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xc140);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xcb00);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1945);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd703);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x7fbe);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x807d);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xc180);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xcb00);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1945);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd703);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x7fbd);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xc100);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xcb00);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd708);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x6018);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x165a);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x14f6);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd014);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd1e3);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1356);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd705);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5fbe);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1559);
		sram_write(tp, 0xA026, 0xffff);
		sram_write(tp, 0xA024, 0xffff);
		sram_write(tp, 0xA022, 0xffff);
		sram_write(tp, 0xA020, 0x1557);
		sram_write(tp, 0xA006, 0x1677);
		sram_write(tp, 0xA004, 0x0b75);
		sram_write(tp, 0xA002, 0x1c17);
		sram_write(tp, 0xA000, 0x1b04);
		sram_write(tp, 0xA008, 0x1f00);

		/* nc1_patch */

		/* nc2_patch */
		sram_write(tp, 0xA016, 0x0020);
		sram_write(tp, 0xA012, 0x0000);
		ocp_reg_write(tp, OCP_SRAM_ADDR, 0xA014);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8010);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x817f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x82ab);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x83f8);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8444);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8454);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8459);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8465);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xcb11);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa50c);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8310);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd701);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x4076);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0c03);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0903);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd700);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x6083);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0c1f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0d00);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xf003);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0c1f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0d00);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a7d);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a4d);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xcb12);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a5e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd71f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5f84);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd102);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd040);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a5e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd700);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5fb4);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd701);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x60f3);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd413);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a37);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd410);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a37);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xcb13);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa108);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a42);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8108);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa00a);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa910);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa780);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd14a);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd048);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a5e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd701);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x6255);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd700);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5f74);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x6326);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd702);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5f07);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x800a);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa004);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a42);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8004);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa001);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a42);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8001);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0c03);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0902);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xffe2);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a5e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd71f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5fab);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xba08);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a5e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd71f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x7f8b);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x9a08);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x800a);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd702);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x6535);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd40d);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a37);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xcb14);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa004);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a42);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8004);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa001);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a42);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8001);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa00a);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa780);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd14a);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd048);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a5e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd700);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5fb4);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x6206);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd702);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5f47);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x800a);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa004);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a42);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8004);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa001);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a42);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8001);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0c03);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0902);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8064);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x800a);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd40e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a37);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xb920);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a5e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd71f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5fac);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x9920);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a5e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd71f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x7f8c);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd701);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x6073);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd701);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x4216);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa004);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a42);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8004);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa001);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a42);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8001);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd120);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd040);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a5e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd700);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5fb4);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8504);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xcb21);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa301);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a5e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd700);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5f9f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8301);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd704);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x40e0);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd196);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd04d);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a5e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd700);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5fb4);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xcb22);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a6d);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0c03);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1502);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa640);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x9503);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8910);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8720);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd700);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x6083);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0c1f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0d01);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xf003);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0c1f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0d01);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a7d);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0c1f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0f14);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xcb23);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8fc0);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a25);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xaf40);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a25);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0cc0);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0f80);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a25);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xafc0);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a25);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a5e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd701);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5dee);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xcb24);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8f1f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a5e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd701);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x7f6e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa111);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa215);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa401);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8404);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa720);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xcb25);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0c03);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1502);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8640);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x9503);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0b43);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0b86);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a5e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xb920);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a5e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd71f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5fac);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x9920);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a5e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd71f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x7f8c);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xcb26);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a5e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd71f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5f82);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8111);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8205);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8404);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xcb27);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd404);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a37);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd700);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x6083);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0c1f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0d02);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xf003);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0c1f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0d02);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a7d);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa710);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa104);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a42);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8104);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa001);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a42);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8001);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa120);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xaa0f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8110);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa284);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa404);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa00a);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd193);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd046);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a5e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd700);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5fb4);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xcb28);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa110);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a5e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd700);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5fa8);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8110);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8284);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa404);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x800a);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8710);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xb804);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a5e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd71f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x7f82);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x9804);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xcb29);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a5e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd71f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5f85);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa710);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xb820);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a5e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd71f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x7f65);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x9820);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xcb2a);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa190);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa284);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa404);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa00a);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd13d);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd04a);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a5e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd700);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x3444);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8149);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa220);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd1a0);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd040);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a5e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd700);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x3444);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8151);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd702);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5f51);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xcb2f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa302);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a5e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd708);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5f63);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd411);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a37);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8302);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd409);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a37);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xb920);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a5e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd71f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5fac);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x9920);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a5e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd71f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x7f8c);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a5e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd71f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5fa3);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8190);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x82a4);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8404);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x800a);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xb808);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a5e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd71f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x7fa3);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x9808);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0433);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xcb15);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa508);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd700);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x6083);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0c1f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0d01);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xf003);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0c1f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0d01);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a7d);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a4d);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa301);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a5e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd700);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5f9f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8301);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd704);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x40e0);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd115);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd04f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a5e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd700);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5fb4);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd413);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a37);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xcb16);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a6d);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0c03);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1502);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa640);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x9503);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8720);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd17a);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd04c);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0c1f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0f14);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xcb17);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8fc0);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a25);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xaf40);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a25);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0cc0);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0f80);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a25);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xafc0);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a25);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a5e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd701);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x61ce);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd700);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5db4);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xcb18);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0c03);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1502);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8640);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x9503);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa720);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0b43);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a5e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xffd6);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8f1f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a5e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd701);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x7f8e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa131);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xaa0f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa2d5);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa407);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa720);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8310);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa308);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8308);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xcb19);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0c03);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1502);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8640);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x9503);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0b43);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0b86);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a5e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xb920);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a5e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd71f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5fac);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x9920);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a5e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd71f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x7f8c);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xcb1a);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a5e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd71f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5f82);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8111);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x82c5);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa404);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8402);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xb804);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a5e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd71f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x7f82);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x9804);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xcb1b);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a5e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd71f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5f85);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa710);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xb820);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a5e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd71f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x7f65);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x9820);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xcb1c);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd700);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x6083);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0c1f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0d02);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xf003);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0c1f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0d02);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a7d);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa110);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa284);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa404);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8402);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a5e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd700);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5fa8);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xcb1d);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa180);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa402);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a5e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd700);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5fa8);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa220);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd1f5);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd049);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a5e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd700);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x3444);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8221);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd702);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5f51);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xb920);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a5e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd71f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5fac);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x9920);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a5e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd71f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x7f8c);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a5e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd71f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5fa3);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa504);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd700);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x6083);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0c1f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0d00);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xf003);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0c1f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0d00);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a7d);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa00a);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8190);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x82a4);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8402);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa404);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xb808);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a5e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd71f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x7fa3);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x9808);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xcb2b);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xcb2c);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a5e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd71f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5f84);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd14a);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd048);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa780);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xcb2d);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a5e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd700);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5f94);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x6208);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd702);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5f27);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x800a);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa004);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a42);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8004);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa001);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a42);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8001);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0c03);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0902);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa00a);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xffe9);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xcb2e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd700);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x6083);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0c1f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0d02);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xf003);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0c1f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0d02);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a7d);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa190);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa284);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa406);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a5e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd700);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5fa8);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa220);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd1a0);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd040);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a5e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd700);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x3444);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x827d);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd702);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5f51);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xcb2f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa302);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a5e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd708);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5f63);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd411);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a37);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8302);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd409);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a37);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xb920);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a5e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd71f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5fac);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x9920);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a5e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd71f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x7f8c);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a5e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd71f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5fa3);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8190);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x82a4);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8406);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x800a);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xb808);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a5e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd71f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x7fa3);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x9808);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0433);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xcb30);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8380);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xcb31);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a5e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd71f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5f86);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x9308);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xb204);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xb301);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a5e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd701);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5fa2);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xb302);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x9204);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xcb32);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd408);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a37);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd141);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd043);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a5e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd700);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5fb4);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd704);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x4ccc);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd700);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x4c81);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd702);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x609e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd1e5);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd04d);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xf003);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd1e5);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd04d);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a5e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd700);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5fb4);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd700);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x6083);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0c1f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0d01);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xf003);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0c1f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0d01);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a7d);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8710);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa108);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a42);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8108);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa203);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8120);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8a0f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa111);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8204);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa140);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a42);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8140);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd17a);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd04b);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a5e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd700);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5fb4);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa204);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a5e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd700);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5fa7);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xb920);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a5e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd71f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5fac);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x9920);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a5e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd71f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x7f8c);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd404);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a37);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd700);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x6083);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0c1f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0d02);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xf003);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0c1f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0d02);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a7d);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa710);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8101);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8201);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa104);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a42);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8104);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa120);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xaa0f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8110);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa284);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa404);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa00a);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd193);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd047);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a5e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd700);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5fb4);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa110);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a5e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd700);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5fa8);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa180);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd13d);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd04a);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a5e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd700);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5fb4);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xf024);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa710);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa00a);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8190);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8204);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa280);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa404);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a5e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd700);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5fa7);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8710);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xb920);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a5e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd71f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5fac);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x9920);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a5e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd71f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x7f8c);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x800a);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8190);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8284);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8406);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd700);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x4121);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd701);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x60f3);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd1e5);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd04d);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a5e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd700);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5fb4);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8710);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa00a);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8190);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8204);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa280);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa404);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xb920);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a5e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd71f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5fac);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x9920);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a5e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd71f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x7f8c);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xcb33);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a5e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd71f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5f85);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa710);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xb820);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a5e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd71f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x7f65);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x9820);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xcb34);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa00a);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa190);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa284);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa404);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a5e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd700);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5fa9);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd701);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x6853);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd700);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x6083);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0c1f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0d00);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xf003);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0c1f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0d00);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a7d);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8190);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8284);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xcb35);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd407);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a37);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8110);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8204);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa280);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa00a);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd704);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x4215);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa304);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a5e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd700);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5fb8);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd1c3);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd043);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a5e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd700);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5fb4);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8304);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd700);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x4109);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xf01e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xcb36);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd412);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a37);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd700);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x6309);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd702);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x42c7);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x800a);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8180);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8280);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8404);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa004);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a42);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8004);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa001);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a42);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8001);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0c03);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0902);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa00a);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd14a);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd048);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a5e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd700);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5fb4);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd700);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x6083);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0c1f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0d02);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xf003);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0c1f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0d02);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a7d);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xcc55);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xcb37);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa00a);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa190);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa2a4);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa404);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd700);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x6041);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa402);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd13d);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd04a);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a5e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd700);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5fb4);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a5e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd700);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5fa9);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd702);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5f71);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xcb38);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8224);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa288);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8180);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa110);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa404);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x800a);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd700);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x6041);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8402);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd415);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a37);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd13d);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd04a);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a5e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd700);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5fb4);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xcb39);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa00a);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa190);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa2a0);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa404);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd700);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x6041);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa402);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd17a);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd047);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a5e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd700);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5fb4);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0560);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa111);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd3f5);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd219);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0c31);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd708);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5fa5);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa215);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd30e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd21a);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0c31);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd708);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x63e9);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd708);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5f65);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd708);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x7f36);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa004);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0c35);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8004);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa001);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0c35);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8001);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd708);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x4098);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd102);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x9401);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xf003);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd103);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xb401);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0c27);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa108);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0c35);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8108);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8110);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8294);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa202);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0bdb);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd39c);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd210);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0c31);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd708);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5fa5);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd39c);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd210);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0c31);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd708);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5fa5);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0c31);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd708);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x29b5);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x840e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd708);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5f4a);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0c1f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1014);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0c31);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd709);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x7fa4);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x901f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0c23);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xcb43);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa508);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd701);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x3699);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x844a);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa504);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa190);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa2a0);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa404);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa00a);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd700);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x2109);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x05ea);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa402);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x05ea);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xcb90);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0cf0);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0ca0);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x06db);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd1ff);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd052);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa508);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8718);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa00a);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa190);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa2a0);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa404);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0cf0);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0c50);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x09ef);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a5e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd704);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x2e70);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x06da);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd700);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5f55);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa90c);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0645);
		sram_write(tp, 0xA10E, 0x0644);
		sram_write(tp, 0xA10C, 0x09e9);
		sram_write(tp, 0xA10A, 0x06da);
		sram_write(tp, 0xA108, 0x05e1);
		sram_write(tp, 0xA106, 0x0be4);
		sram_write(tp, 0xA104, 0x0435);
		sram_write(tp, 0xA102, 0x0141);
		sram_write(tp, 0xA100, 0x026d);
		sram_write(tp, 0xA110, 0x00ff);

		/* uc2 */
		sram_write(tp, 0xb87c, 0x85fe);
		ocp_reg_write(tp, OCP_SRAM_ADDR, 0xb87e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xaf86);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x16af);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8699);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xaf86);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xe5af);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x86f9);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xaf87);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x7aaf);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x883a);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xaf88);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x58af);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8b6c);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd48b);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x7c02);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8644);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x2c00);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x503c);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xffd6);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xac27);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x18e1);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x82fe);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xad28);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0cd4);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8b84);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0286);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x442c);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x003c);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xac27);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x06ee);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8299);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x01ae);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x04ee);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8299);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x00af);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x23dc);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xf9fa);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xcefa);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xfbef);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x79fb);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xc4bf);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8b76);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x026c);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x6dac);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x2804);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd203);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xae02);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd201);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xbdd8);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x19d9);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xef94);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x026c);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x6d78);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x03ef);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x648a);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0002);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xbdd8);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x19d9);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xef94);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x026c);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x6d78);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x03ef);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x7402);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x72cd);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xac50);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x02ef);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x643a);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x019f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xe4ef);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x4678);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x03ac);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x2002);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xae02);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd0ff);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xffef);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x97ff);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xfec6);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xfefd);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x041f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x771f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x221c);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x450d);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x481f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x00ac);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x7f04);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1a94);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xae08);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1a94);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xac7f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x03d7);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0100);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xef46);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0d48);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1f00);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1c45);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xef69);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xef57);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xef74);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0272);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xe8a7);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xffff);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0d1a);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x941b);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x979e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x072d);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0100);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1a64);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xef76);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xef97);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0d98);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd400);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xff1d);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x941a);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x89cf);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1a75);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xaf74);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xf9bf);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8b79);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x026c);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x6da1);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0005);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xe180);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa0ae);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x03e1);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x80a1);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xaf26);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x9aac);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x284d);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xe08f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xffef);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x10c0);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xe08f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xfe10);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1b08);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x04c8);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xaf40);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x67c8);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xbf8b);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8c02);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x6c4e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xc4bf);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8b8f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x026c);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x6def);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x74e0);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x830c);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xad20);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0302);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x74ac);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xccef);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x971b);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x76ad);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5f02);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xae13);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xef69);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xef30);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1b32);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xc4ef);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x46e4);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8ffb);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xe58f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xfce7);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8ffd);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xcc10);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x11ae);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xb8d1);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x00a1);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1f03);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xaf40);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x4fbf);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8b8c);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x026c);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x4ec4);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xbf8b);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8f02);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x6c6d);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xef74);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xe083);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0cad);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x2003);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0274);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xaccc);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xef97);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1b76);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xad5f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x02ae);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x04ef);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x69ef);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x3111);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xaed1);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0287);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x80af);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x2293);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xf8f9);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xfafb);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xef59);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xe080);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x13ad);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x252f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xbf88);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x2802);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x6c6d);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xef64);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1f44);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xe18f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xb91b);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x64ad);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x4f1d);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd688);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x2bd7);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x882e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0274);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x73ad);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5008);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xbf88);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x3102);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x737c);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xae03);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0287);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd0bf);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x882b);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0273);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x73e0);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x824c);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xf621);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xe482);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x4cbf);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8834);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0273);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x7cef);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x95ff);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xfefd);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xfc04);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xf8f9);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xfafb);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xef79);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xbf88);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1f02);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x737c);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1f22);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xac32);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x31ef);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x12bf);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8822);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x026c);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x4ed6);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8fba);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1f33);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xac3c);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1eef);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x13bf);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8837);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x026c);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x4eef);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x96d8);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x19d9);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xbf88);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x2502);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x6c4e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xbf88);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x2502);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x6c4e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1616);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x13ae);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xdf12);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xaecc);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xbf88);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1f02);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x7373);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xef97);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xfffe);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xfdfc);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0466);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xac88);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x54ac);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x88f0);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xac8a);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x92ac);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xbadd);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xac6c);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xeeac);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x6cff);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xad02);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x99ac);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0030);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xac88);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd4c3);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0000);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x00b4);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xecee);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8298);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x00af);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1412);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xf8bf);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8b5d);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x026c);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x6d58);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x03e1);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8fb8);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x2901);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xe58f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xb8a0);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0049);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xef47);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xe483);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x02e5);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8303);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xbfc2);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5f1a);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x95f7);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x05ee);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xffd2);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x00d8);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xf605);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1f11);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xef60);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xbf8b);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x3002);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x6c4e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xbf8b);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x3302);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x6c6d);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xf728);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xbf8b);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x3302);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x6c4e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xf628);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xbf8b);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x3302);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x6c4e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0c64);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xef46);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xbf8b);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x6002);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x6c4e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0289);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x9902);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x3920);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xaf89);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x96a0);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0149);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xef47);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xe483);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x04e5);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8305);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xbfc2);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5f1a);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x95f7);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x05ee);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xffd2);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x00d8);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xf605);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1f11);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xef60);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xbf8b);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x3002);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x6c4e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xbf8b);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x3302);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x6c6d);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xf729);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xbf8b);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x3302);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x6c4e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xf629);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xbf8b);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x3302);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x6c4e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0c64);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xef46);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xbf8b);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x6302);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x6c4e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0289);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x9902);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x3920);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xaf89);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x96a0);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0249);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xef47);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xe483);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x06e5);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8307);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xbfc2);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5f1a);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x95f7);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x05ee);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xffd2);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x00d8);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xf605);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1f11);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xef60);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xbf8b);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x3002);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x6c4e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xbf8b);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x3302);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x6c6d);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xf72a);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xbf8b);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x3302);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x6c4e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xf62a);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xbf8b);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x3302);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x6c4e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0c64);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xef46);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xbf8b);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x6602);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x6c4e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0289);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x9902);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x3920);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xaf89);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x96ef);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x47e4);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8308);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xe583);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x09bf);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xc25f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1a95);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xf705);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xeeff);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd200);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd8f6);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x051f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x11ef);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x60bf);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8b30);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x026c);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x4ebf);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8b33);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x026c);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x6df7);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x2bbf);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8b33);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x026c);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x4ef6);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x2bbf);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8b33);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x026c);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x4e0c);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x64ef);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x46bf);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8b69);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x026c);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x4e02);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8999);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0239);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x20af);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8996);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xaf39);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1ef8);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xf9fa);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xe08f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xb838);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x02ad);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x2702);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xae03);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xaf8b);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x201f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x66ef);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x65bf);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xc21f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1a96);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xf705);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xeeff);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd200);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xdaf6);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x05bf);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xc22f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1a96);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xf705);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xeeff);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd200);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xdbf6);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x05ef);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x021f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x110d);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x42bf);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8b3c);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x026c);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x4eef);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x021b);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x031f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x110d);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x42bf);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8b36);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x026c);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x4eef);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x021a);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x031f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x110d);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x42bf);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8b39);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x026c);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x4ebf);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xc23f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1a96);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xf705);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xeeff);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd200);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xdaf6);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x05bf);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xc24f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1a96);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xf705);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xeeff);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd200);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xdbf6);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x05ef);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x021f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x110d);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x42bf);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8b45);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x026c);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x4eef);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x021b);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x031f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x110d);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x42bf);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8b3f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x026c);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x4eef);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x021a);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x031f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x110d);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x42bf);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8b42);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x026c);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x4eef);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x56d0);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x201f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x11bf);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8b4e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x026c);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x4ebf);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8b48);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x026c);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x4ebf);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8b4b);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x026c);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x4ee1);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8578);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xef03);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x480a);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x2805);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xef20);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1b01);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xad27);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x3f1f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x44e0);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8560);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xe185);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x61bf);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8b51);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x026c);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x4ee0);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8566);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xe185);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x67bf);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8b54);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x026c);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x4ee0);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x856c);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xe185);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x6dbf);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8b57);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x026c);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x4ee0);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8572);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xe185);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x73bf);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8b5a);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x026c);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x4ee1);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8fb8);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5900);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xf728);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xe58f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xb8af);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8b2c);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xe185);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x791b);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x21ad);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x373e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1f44);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xe085);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x62e1);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8563);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xbf8b);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5102);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x6c4e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xe085);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x68e1);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8569);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xbf8b);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5402);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x6c4e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xe085);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x6ee1);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x856f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xbf8b);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5702);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x6c4e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xe085);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x74e1);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8575);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xbf8b);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5a02);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x6c4e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xe18f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xb859);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x00f7);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x28e5);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8fb8);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xae4a);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1f44);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xe085);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x64e1);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8565);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xbf8b);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5102);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x6c4e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xe085);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x6ae1);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x856b);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xbf8b);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5402);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x6c4e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xe085);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x70e1);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8571);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xbf8b);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5702);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x6c4e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xe085);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x76e1);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8577);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xbf8b);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5a02);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x6c4e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xe18f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xb859);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x00f7);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x28e5);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8fb8);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xae0c);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xe18f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xb839);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x04ac);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x2f04);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xee8f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xb800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xfefd);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xfc04);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xf0ac);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8efc);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xac8c);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xf0ac);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xfaf0);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xacf8);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xf0ac);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xf6f0);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xad00);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xf0ac);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xfef0);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xacfc);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xf0ac);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xf4f0);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xacf2);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xf0ac);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xf0f0);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xacb0);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xf0ac);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xaef0);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xacac);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xf0ac);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xaaf0);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xacee);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xf0b0);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x24f0);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xb0a4);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xf0b1);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x24f0);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xb1a4);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xee8f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xb800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd400);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x00af);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x3976);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x66ac);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xeabb);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa430);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x6e50);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x6e53);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x6e56);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x6e59);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x6e5c);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x6e5f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x6e62);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x6e65);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd9ac);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x70f0);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xac6a);
		sram_write(tp, 0xb85e, 0x23b7);
		sram_write(tp, 0xb860, 0x74db);
		sram_write(tp, 0xb862, 0x268c);
		sram_write(tp, 0xb864, 0x3FE5);
		sram_write(tp, 0xb886, 0x2250);
		sram_write(tp, 0xb888, 0x140e);
		sram_write(tp, 0xb88a, 0x3696);
		sram_write(tp, 0xb88c, 0x3973);
		sram_write(tp, 0xb838, 0x00ff);

		data = ocp_reg_read(tp, OCP_PHY_PATCH_CMD);
		data &= ~BIT(7);
		ocp_reg_write(tp, OCP_PHY_PATCH_CMD, data);

		/* uc */
		ocp_reg_write(tp, OCP_SRAM_ADDR, 0x8464);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xaf84);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x7caf);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8485);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xaf85);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x13af);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x851e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xaf85);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xb9af);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8684);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xaf87);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x01af);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8701);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xac38);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x03af);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x38bb);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xaf38);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xc302);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x4618);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xbf85);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0a02);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x54b7);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xbf85);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1002);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x54c0);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd400);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0fbf);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8507);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x024f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x48bf);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8504);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x024f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x6759);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xf0a1);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x3008);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xbf85);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0d02);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x54c0);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xae06);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xbf85);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0d02);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x54b7);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xbf85);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0402);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x4f67);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa183);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x02ae);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x15a1);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8502);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xae10);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x59f0);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa180);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x16bf);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8501);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x024f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x67a1);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x381b);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xae0b);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xe18f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xffbf);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x84fe);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x024f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x48ae);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x17bf);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x84fe);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0254);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xb7bf);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x84fb);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0254);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xb7ae);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x09a1);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x5006);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xbf84);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xfb02);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x54c0);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xaf04);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x4700);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xad34);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xfdad);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0670);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xae14);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xf0a6);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x00b8);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xbd32);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x30bd);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x30aa);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xbd2c);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xccbd);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x2ca1);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x0705);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xec80);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xaf40);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xf7af);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x40f5);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd101);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xbf85);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa402);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x4f48);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xbf85);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa702);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x54c0);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd10f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xbf85);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xaa02);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x4f48);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x024d);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x6abf);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x85ad);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x024f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x67bf);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8ff7);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xddbf);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x85b0);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x024f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x67bf);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8ff8);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xddbf);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x85b3);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x024f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x67bf);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8ff9);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xddbf);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x85b6);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x024f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x67bf);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8ffa);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xddd1);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x00bf);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x85aa);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x024f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x4802);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x4d6a);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xbf85);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xad02);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x4f67);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xbf8f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xfbdd);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xbf85);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xb002);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x4f67);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xbf8f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xfcdd);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xbf85);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xb302);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x4f67);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xbf8f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xfddd);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xbf85);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xb602);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x4f67);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xbf8f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xfedd);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xbf85);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa702);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x54b7);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xbf85);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa102);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x54b7);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xaf3c);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x2066);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xb800);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xb8bd);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x30ee);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xbd2c);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xb8bd);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x7040);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xbd86);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xc8bd);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8640);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xbd88);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xc8bd);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8802);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1929);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa202);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x02ae);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x03a2);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x032e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd10f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xbf85);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xaa02);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x4f48);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xe18f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xf7bf);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x85ad);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x024f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x48e1);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8ff8);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xbf85);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xb002);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x4f48);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xe18f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xf9bf);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x85b3);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x024f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x48e1);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8ffa);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xbf85);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xb602);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x4f48);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xae2c);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd100);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xbf85);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xaa02);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x4f48);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xe18f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xfbbf);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x85ad);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x024f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x48e1);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8ffc);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xbf85);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xb002);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x4f48);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xe18f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xfdbf);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x85b3);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x024f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x48e1);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8ffe);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xbf85);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xb602);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x4f48);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xbf86);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x7e02);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x4f67);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa100);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x02ae);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x25a1);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x041d);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xe18f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xf1bf);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8675);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x024f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x48e1);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8ff2);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xbf86);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x7802);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x4f48);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xe18f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xf3bf);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x867b);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x024f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x48ae);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x29a1);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x070b);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xae24);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xbf86);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8102);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x4f67);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xad28);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1be1);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8ff4);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xbf86);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x7502);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x4f48);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xe18f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xf5bf);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8678);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x024f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x48e1);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8ff6);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xbf86);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x7b02);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x4f48);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xaf09);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8420);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xbc32);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x20bc);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x3e76);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xbc08);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xfda6);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x1a00);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xb64e);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd101);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xbf85);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa402);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x4f48);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xbf85);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa702);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x54c0);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xd10f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xbf85);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xaa02);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x4f48);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x024d);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x6abf);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x85ad);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x024f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x67bf);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8ff7);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xddbf);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x85b0);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x024f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x67bf);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8ff8);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xddbf);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x85b3);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x024f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x67bf);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8ff9);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xddbf);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x85b6);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x024f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x67bf);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8ffa);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xddd1);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x00bf);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x85aa);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x024f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x4802);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x4d6a);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xbf85);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xad02);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x4f67);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xbf8f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xfbdd);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xbf85);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xb002);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x4f67);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xbf8f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xfcdd);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xbf85);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xb302);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x4f67);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xbf8f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xfddd);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xbf85);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xb602);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x4f67);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xbf8f);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xfedd);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xbf85);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xa702);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x54b7);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0xaf00);
		ocp_reg_write(tp, OCP_SRAM_DATA, 0x8800);
		sram_write(tp, 0xb818, 0x38b8);
		sram_write(tp, 0xb81a, 0x0444);
		sram_write(tp, 0xb81c, 0x40ee);
		sram_write(tp, 0xb81e, 0x3C1A);
		sram_write(tp, 0xb850, 0x0981);
		sram_write(tp, 0xb852, 0x0085);
		sram_write(tp, 0xb878, 0xffff);
		sram_write(tp, 0xb884, 0xffff);
		sram_write(tp, 0xb832, 0x003f);

		rtl_post_ram_code(tp, 0x8024, !power_cut);
	} else {
		rtl_ram_code_speed_up(tp, !power_cut);
	}

	rtl_reset_ocp_base(tp);
}

static void r8156_hw_phy_cfg(struct r8152 *tp)
{
	u32 ocp_data;
	u16 data;

	r8156_patch_code(tp);

	ocp_data = ocp_read_word(tp, MCU_TYPE_USB, USB_MISC_0);
	if (ocp_data & PCUT_STATUS) {
		ocp_data &= ~PCUT_STATUS;
		ocp_write_word(tp, MCU_TYPE_USB, USB_MISC_0, ocp_data);
	}

	data = r8153_phy_status(tp, 0);
	switch (data) {
	case PHY_STAT_EXT_INIT:
		r8156_ram_code(tp, true);

		data = ocp_reg_read(tp, 0xa468);
		data &= ~(BIT(3) | BIT(1));
		ocp_reg_write(tp, 0xa468, data);
		break;
	case PHY_STAT_LAN_ON:
	case PHY_STAT_PWRDN:
	default:
		r8156_ram_code(tp, false);
		break;
	}

	/* disable ALDPS before updating the PHY parameters */
	r8153_aldps_en(tp, false);

	/* disable EEE before updating the PHY parameters */
	rtl_eee_enable(tp, false);

	data = r8153_phy_status(tp, PHY_STAT_LAN_ON);
	WARN_ON_ONCE(data != PHY_STAT_LAN_ON);

	ocp_data = ocp_read_word(tp, MCU_TYPE_PLA, PLA_PHY_PWR);
	ocp_data |= PFM_PWM_SWITCH;
	ocp_write_word(tp, MCU_TYPE_PLA, PLA_PHY_PWR, ocp_data);

	switch (tp->version) {
	case RTL_VER_10:
		data = ocp_reg_read(tp, 0xad40);
		data &= ~0x3ff;
		data |= BIT(7) | BIT(2);
		ocp_reg_write(tp, 0xad40, data);

		data = ocp_reg_read(tp, 0xad4e);
		data |= BIT(4);
		ocp_reg_write(tp, 0xad4e, data);
		data = ocp_reg_read(tp, 0xad16);
		data &= ~0x3ff;
		data |= 0x6;
		ocp_reg_write(tp, 0xad16, data);
		data = ocp_reg_read(tp, 0xad32);
		data &= ~0x3f;
		data |= 6;
		ocp_reg_write(tp, 0xad32, data);
		data = ocp_reg_read(tp, 0xac08);
		data &= ~(BIT(12) | BIT(8));
		ocp_reg_write(tp, 0xac08, data);
		data = ocp_reg_read(tp, 0xac8a);
		data |= BIT(12) | BIT(13) | BIT(14);
		data &= ~BIT(15);
		ocp_reg_write(tp, 0xac8a, data);
		data = ocp_reg_read(tp, 0xad18);
		data |= BIT(10);
		ocp_reg_write(tp, 0xad18, data);
		data = ocp_reg_read(tp, 0xad1a);
		data |= 0x3ff;
		ocp_reg_write(tp, 0xad1a, data);
		data = ocp_reg_read(tp, 0xad1c);
		data |= 0x3ff;
		ocp_reg_write(tp, 0xad1c, data);

		data = sram_read(tp, 0x80ea);
		data &= ~0xff00;
		data |= 0xc400;
		sram_write(tp, 0x80ea, data);
		data = sram_read(tp, 0x80eb);
		data &= ~0x0700;
		data |= 0x0300;
		sram_write(tp, 0x80eb, data);
		data = sram_read(tp, 0x80f8);
		data &= ~0xff00;
		data |= 0x1c00;
		sram_write(tp, 0x80f8, data);
		data = sram_read(tp, 0x80f1);
		data &= ~0xff00;
		data |= 0x3000;
		sram_write(tp, 0x80f1, data);

		data = sram_read(tp, 0x80fe);
		data &= ~0xff00;
		data |= 0xa500;
		sram_write(tp, 0x80fe, data);
		data = sram_read(tp, 0x8102);
		data &= ~0xff00;
		data |= 0x5000;
		sram_write(tp, 0x8102, data);
		data = sram_read(tp, 0x8015);
		data &= ~0xff00;
		data |= 0x3300;
		sram_write(tp, 0x8015, data);
		data = sram_read(tp, 0x8100);
		data &= ~0xff00;
		data |= 0x7000;
		sram_write(tp, 0x8100, data);
		data = sram_read(tp, 0x8014);
		data &= ~0xff00;
		data |= 0xf000;
		sram_write(tp, 0x8014, data);
		data = sram_read(tp, 0x8016);
		data &= ~0xff00;
		data |= 0x6500;
		sram_write(tp, 0x8016, data);
		data = sram_read(tp, 0x80dc);
		data &= ~0xff00;
		data |= 0xed00;
		sram_write(tp, 0x80dc, data);
		data = sram_read(tp, 0x80df);
		data |= BIT(8);
		sram_write(tp, 0x80df, data);
		data = sram_read(tp, 0x80e1);
		data &= ~BIT(8);
		sram_write(tp, 0x80e1, data);

		data = ocp_reg_read(tp, 0xbf06);
		data &= ~0x003f;
		data |= 0x0038;
		ocp_reg_write(tp, 0xbf06, data);

		sram_write(tp, 0x819f, 0xddb6);

		ocp_reg_write(tp, 0xbc34, 0x5555);
		data = ocp_reg_read(tp, 0xbf0a);
		data &= ~0x0e00;
		data |= 0x0a00;
		ocp_reg_write(tp, 0xbf0a, data);

		data = ocp_reg_read(tp, 0xbd2c);
		data &= ~BIT(13);
		ocp_reg_write(tp, 0xbd2c, data);
		break;
	case RTL_VER_11:
		/* 2.5G INRX */
		data = ocp_reg_read(tp, 0xad16);
		data |= 0x3ff;
		ocp_reg_write(tp, 0xad16, data);
		data = ocp_reg_read(tp, 0xad32);
		data &= ~0x3f;
		data |= 6;
		ocp_reg_write(tp, 0xad32, data);
		data = ocp_reg_read(tp, 0xac08);
		data &= ~(BIT(12) | BIT(8));
		ocp_reg_write(tp, 0xac08, data);
		data = ocp_reg_read(tp, 0xacc0);
		data &= ~0x3;
		data |= BIT(1);
		ocp_reg_write(tp, 0xacc0, data);
		data = ocp_reg_read(tp, 0xad40);
		data &= ~0xe7;
		data |= BIT(6) | BIT(2);
		ocp_reg_write(tp, 0xad40, data);
		data = ocp_reg_read(tp, 0xac14);
		data &= ~BIT(7);
		ocp_reg_write(tp, 0xac14, data);
		data = ocp_reg_read(tp, 0xac80);
		data &= ~(BIT(8) | BIT(9));
		ocp_reg_write(tp, 0xac80, data);
		data = ocp_reg_read(tp, 0xac5e);
		data &= ~0x7;
		data |= BIT(1);
		ocp_reg_write(tp, 0xac5e, data);
		ocp_reg_write(tp, 0xad4c, 0x00a8);
		ocp_reg_write(tp, 0xac5c, 0x01ff);
		data = ocp_reg_read(tp, 0xac8a);
		data &= ~0xf0;
		data |= BIT(4) | BIT(5);
		ocp_reg_write(tp, 0xac8a, data);
		ocp_reg_write(tp, 0xb87c, 0x8157);
		data = ocp_reg_read(tp, 0xb87e);
		data &= ~0xff00;
		data |= 0x0500;
		ocp_reg_write(tp, 0xb87e, data);
		ocp_reg_write(tp, 0xb87c, 0x8159);
		data = ocp_reg_read(tp, 0xb87e);
		data &= ~0xff00;
		data |= 0x0700;
		ocp_reg_write(tp, 0xb87e, data);

		/* AAGC */
		ocp_reg_write(tp, 0xb87c, 0x80a2);
		ocp_reg_write(tp, 0xb87e, 0x0153);
		ocp_reg_write(tp, 0xb87c, 0x809c);
		ocp_reg_write(tp, 0xb87e, 0x0153);

		/* EEE parameter */
		ocp_write_word(tp, MCU_TYPE_PLA, PLA_EEE_TXTWSYS_2P5G, 0x0056);

		ocp_data = ocp_read_word(tp, MCU_TYPE_PLA, PLA_USB_CFG);
		ocp_data |= EN_XG_LIP | EN_G_LIP;
		ocp_write_word(tp, MCU_TYPE_PLA, PLA_USB_CFG, ocp_data);

		sram_write(tp, 0x8257, 0x020f); /*  XG PLL */
		sram_write(tp, 0x80ea, 0x7843); /* GIGA Master */

		if (rtl_phy_patch_request(tp, true, true))
			return;

		/* Advance EEE */
		ocp_data = ocp_read_word(tp, MCU_TYPE_PLA, PLA_MAC_PWR_CTRL4);
		ocp_data |= EEE_SPDWN_EN;
		ocp_write_word(tp, MCU_TYPE_PLA, PLA_MAC_PWR_CTRL4, ocp_data);

		data = ocp_reg_read(tp, OCP_DOWN_SPEED);
		data &= ~(EN_EEE_100 | EN_EEE_1000);
		data |= EN_10M_CLKDIV;
		ocp_reg_write(tp, OCP_DOWN_SPEED, data);
		tp->ups_info._10m_ckdiv = true;
		tp->ups_info.eee_plloff_100 = false;
		tp->ups_info.eee_plloff_giga = false;

		data = ocp_reg_read(tp, OCP_POWER_CFG);
		data &= ~EEE_CLKDIV_EN;
		ocp_reg_write(tp, OCP_POWER_CFG, data);
		tp->ups_info.eee_ckdiv = false;

		ocp_reg_write(tp, OCP_SYSCLK_CFG, 0);
		ocp_reg_write(tp, OCP_SYSCLK_CFG, sysclk_div_expo(5));
		tp->ups_info._250m_ckdiv = false;

		rtl_phy_patch_request(tp, false, true);

		/* enable ADC Ibias Cal */
		data = ocp_reg_read(tp, 0xd068);
		data |= BIT(13);
		ocp_reg_write(tp, 0xd068, data);

		/* enable Thermal Sensor */
		data = sram_read(tp, 0x81a2);
		data &= ~BIT(8);
		sram_write(tp, 0x81a2, data);
		data = ocp_reg_read(tp, 0xb54c);
		data &= ~0xff00;
		data |= 0xdb00;
		ocp_reg_write(tp, 0xb54c, data);

		/* Nway 2.5G Lite */
		data = ocp_reg_read(tp, 0xa454);
		data &= ~BIT(0);
		ocp_reg_write(tp, 0xa454, data);

		/* CS DSP solution */
		data = ocp_reg_read(tp, OCP_10GBT_CTRL);
		data |= RTL_ADV2_5G_F_R;
		ocp_reg_write(tp, OCP_10GBT_CTRL, data);
		data = ocp_reg_read(tp, 0xad4e);
		data &= ~BIT(4);
		ocp_reg_write(tp, 0xad4e, data);
		data = ocp_reg_read(tp, 0xa86a);
		data &= ~BIT(0);
		ocp_reg_write(tp, 0xa86a, data);

		/* MDI SWAP */
		if ((ocp_read_word(tp, MCU_TYPE_USB, USB_UPS_CFG) & MID_REVERSE) &&
		    (ocp_reg_read(tp, 0xd068) & BIT(1))) {
			u16 swap_a, swap_b;

			data = ocp_reg_read(tp, 0xd068);
			data &= ~0x1f;
			data |= 0x1; /* p0 */
			ocp_reg_write(tp, 0xd068, data);
			swap_a = ocp_reg_read(tp, 0xd06a);
			data &= ~0x18;
			data |= 0x18; /* p3 */
			ocp_reg_write(tp, 0xd068, data);
			swap_b = ocp_reg_read(tp, 0xd06a);
			data &= ~0x18; /* p0 */
			ocp_reg_write(tp, 0xd068, data);
			ocp_reg_write(tp, 0xd06a,
				      (swap_a & ~0x7ff) | (swap_b & 0x7ff));
			data |= 0x18; /* p3 */
			ocp_reg_write(tp, 0xd068, data);
			ocp_reg_write(tp, 0xd06a,
				      (swap_b & ~0x7ff) | (swap_a & 0x7ff));
			data &= ~0x18;
			data |= 0x08; /* p1 */
			ocp_reg_write(tp, 0xd068, data);
			swap_a = ocp_reg_read(tp, 0xd06a);
			data &= ~0x18;
			data |= 0x10; /* p2 */
			ocp_reg_write(tp, 0xd068, data);
			swap_b = ocp_reg_read(tp, 0xd06a);
			data &= ~0x18;
			data |= 0x08; /* p1 */
			ocp_reg_write(tp, 0xd068, data);
			ocp_reg_write(tp, 0xd06a,
				      (swap_a & ~0x7ff) | (swap_b & 0x7ff));
			data &= ~0x18;
			data |= 0x10; /* p2 */
			ocp_reg_write(tp, 0xd068, data);
			ocp_reg_write(tp, 0xd06a,
				      (swap_b & ~0x7ff) | (swap_a & 0x7ff));
			swap_a = ocp_reg_read(tp, 0xbd5a);
			swap_b = ocp_reg_read(tp, 0xbd5c);
			ocp_reg_write(tp, 0xbd5a, (swap_a & ~0x1f1f) |
				      ((swap_b & 0x1f) << 8) |
				      ((swap_b >> 8) & 0x1f));
			ocp_reg_write(tp, 0xbd5c, (swap_b & ~0x1f1f) |
				      ((swap_a & 0x1f) << 8) |
				      ((swap_a >> 8) & 0x1f));
			swap_a = ocp_reg_read(tp, 0xbc18);
			swap_b = ocp_reg_read(tp, 0xbc1a);
			ocp_reg_write(tp, 0xbc18, (swap_a & ~0x1f1f) |
				      ((swap_b & 0x1f) << 8) |
				      ((swap_b >> 8) & 0x1f));
			ocp_reg_write(tp, 0xbc1a, (swap_b & ~0x1f1f) |
				      ((swap_a & 0x1f) << 8) |
				      ((swap_a >> 8) & 0x1f));
		}
		break;
	default:
		break;
	}

	rtl_green_en(tp, test_bit(GREEN_ETHERNET, &tp->flags));

	data = ocp_reg_read(tp, 0xa428);
	data &= ~BIT(9);
	ocp_reg_write(tp, 0xa428, data);
	data = ocp_reg_read(tp, 0xa5ea);
	data &= ~BIT(0);
	ocp_reg_write(tp, 0xa5ea, data);
	tp->ups_info.lite_mode = 0;

	if (tp->eee_en)
		rtl_eee_enable(tp, true);

	r8153_aldps_en(tp, true);
	r8152b_enable_fc(tp);
	r8153_u2p3en(tp, true);

	set_bit(PHY_RESET, &tp->flags);
}

static void r8156b_hw_phy_cfg(struct r8152 *tp)
{
	u32 ocp_data;
	u16 data;

	r8156_patch_code(tp);

	switch (tp->version) {
	case RTL_VER_12:
		ocp_reg_write(tp, 0xbf86, 0x9000);
		data = ocp_reg_read(tp, 0xc402);
		data |= BIT(10);
		ocp_reg_write(tp, 0xc402, data);
		data &= ~BIT(10);
		ocp_reg_write(tp, 0xc402, data);
		ocp_reg_write(tp, 0xbd86, 0x1010);
		ocp_reg_write(tp, 0xbd88, 0x1010);
		data = ocp_reg_read(tp, 0xbd4e);
		data &= ~(BIT(10) | BIT(11));
		data |= BIT(11);
		ocp_reg_write(tp, 0xbd4e, data);
		data = ocp_reg_read(tp, 0xbf46);
		data &= ~0xf00;
		data |= 0x700;
		ocp_reg_write(tp, 0xbf46, data);
		break;
	case RTL_VER_13:
	case RTL_VER_15:
		r8156b_wait_loading_flash(tp);
		break;
	default:
		break;
	}

	ocp_data = ocp_read_word(tp, MCU_TYPE_USB, USB_MISC_0);
	if (ocp_data & PCUT_STATUS) {
		ocp_data &= ~PCUT_STATUS;
		ocp_write_word(tp, MCU_TYPE_USB, USB_MISC_0, ocp_data);
	}

	data = r8153_phy_status(tp, 0);
	switch (data) {
	case PHY_STAT_EXT_INIT:
		r8156_ram_code(tp, true);

		data = ocp_reg_read(tp, 0xa466);
		data &= ~BIT(0);
		ocp_reg_write(tp, 0xa466, data);

		data = ocp_reg_read(tp, 0xa468);
		data &= ~(BIT(3) | BIT(1));
		ocp_reg_write(tp, 0xa468, data);
		break;
	case PHY_STAT_LAN_ON:
	case PHY_STAT_PWRDN:
	default:
		r8156_ram_code(tp, false);
		break;
	}

	data = r8152_mdio_read(tp, MII_BMCR);
	if (data & BMCR_PDOWN) {
		data &= ~BMCR_PDOWN;
		r8152_mdio_write(tp, MII_BMCR, data);
	}

	/* disable ALDPS before updating the PHY parameters */
	r8153_aldps_en(tp, false);

	/* disable EEE before updating the PHY parameters */
	rtl_eee_enable(tp, false);

	data = r8153_phy_status(tp, PHY_STAT_LAN_ON);
	WARN_ON_ONCE(data != PHY_STAT_LAN_ON);

	ocp_data = ocp_read_word(tp, MCU_TYPE_PLA, PLA_PHY_PWR);
	ocp_data |= PFM_PWM_SWITCH;
	ocp_write_word(tp, MCU_TYPE_PLA, PLA_PHY_PWR, ocp_data);

	switch (tp->version) {
	case RTL_VER_12:
		data = ocp_reg_read(tp, 0xbc08);
		data |= BIT(3) | BIT(2);
		ocp_reg_write(tp, 0xbc08, data);

		data = sram_read(tp, 0x8fff);
		data &= ~0xff00;
		data |= 0x0400;
		sram_write(tp, 0x8fff, data);

		data = ocp_reg_read(tp, 0xacda);
		data |= 0xff00;
		ocp_reg_write(tp, 0xacda, data);
		data = ocp_reg_read(tp, 0xacde);
		data |= 0xf000;
		ocp_reg_write(tp, 0xacde, data);
		ocp_reg_write(tp, 0xac8c, 0x0ffc);
		ocp_reg_write(tp, 0xac46, 0xb7b4);
		ocp_reg_write(tp, 0xac50, 0x0fbc);
		ocp_reg_write(tp, 0xac3c, 0x9240);
		ocp_reg_write(tp, 0xac4e, 0x0db4);
		ocp_reg_write(tp, 0xacc6, 0x0707);
		ocp_reg_write(tp, 0xacc8, 0xa0d3);
		ocp_reg_write(tp, 0xad08, 0x0007);

		ocp_reg_write(tp, 0xb87c, 0x8560);
		ocp_reg_write(tp, 0xb87e, 0x19cc);
		ocp_reg_write(tp, 0xb87c, 0x8562);
		ocp_reg_write(tp, 0xb87e, 0x19cc);
		ocp_reg_write(tp, 0xb87c, 0x8564);
		ocp_reg_write(tp, 0xb87e, 0x19cc);
		ocp_reg_write(tp, 0xb87c, 0x8566);
		ocp_reg_write(tp, 0xb87e, 0x147d);
		ocp_reg_write(tp, 0xb87c, 0x8568);
		ocp_reg_write(tp, 0xb87e, 0x147d);
		ocp_reg_write(tp, 0xb87c, 0x856a);
		ocp_reg_write(tp, 0xb87e, 0x147d);
		ocp_reg_write(tp, 0xb87c, 0x8ffe);
		ocp_reg_write(tp, 0xb87e, 0x0907);
		ocp_reg_write(tp, 0xb87c, 0x80d6);
		ocp_reg_write(tp, 0xb87e, 0x2801);
		ocp_reg_write(tp, 0xb87c, 0x80f2);
		ocp_reg_write(tp, 0xb87e, 0x2801);
		ocp_reg_write(tp, 0xb87c, 0x80f4);
		ocp_reg_write(tp, 0xb87e, 0x6077);
		ocp_reg_write(tp, 0xb506, 0x01e7);

		ocp_reg_write(tp, 0xb87c, 0x8013);
		ocp_reg_write(tp, 0xb87e, 0x0700);
		ocp_reg_write(tp, 0xb87c, 0x8fb9);
		ocp_reg_write(tp, 0xb87e, 0x2801);
		ocp_reg_write(tp, 0xb87c, 0x8fba);
		ocp_reg_write(tp, 0xb87e, 0x0100);
		ocp_reg_write(tp, 0xb87c, 0x8fbc);
		ocp_reg_write(tp, 0xb87e, 0x1900);
		ocp_reg_write(tp, 0xb87c, 0x8fbe);
		ocp_reg_write(tp, 0xb87e, 0xe100);
		ocp_reg_write(tp, 0xb87c, 0x8fc0);
		ocp_reg_write(tp, 0xb87e, 0x0800);
		ocp_reg_write(tp, 0xb87c, 0x8fc2);
		ocp_reg_write(tp, 0xb87e, 0xe500);
		ocp_reg_write(tp, 0xb87c, 0x8fc4);
		ocp_reg_write(tp, 0xb87e, 0x0f00);
		ocp_reg_write(tp, 0xb87c, 0x8fc6);
		ocp_reg_write(tp, 0xb87e, 0xf100);
		ocp_reg_write(tp, 0xb87c, 0x8fc8);
		ocp_reg_write(tp, 0xb87e, 0x0400);
		ocp_reg_write(tp, 0xb87c, 0x8fca);
		ocp_reg_write(tp, 0xb87e, 0xf300);
		ocp_reg_write(tp, 0xb87c, 0x8fcc);
		ocp_reg_write(tp, 0xb87e, 0xfd00);
		ocp_reg_write(tp, 0xb87c, 0x8fce);
		ocp_reg_write(tp, 0xb87e, 0xff00);
		ocp_reg_write(tp, 0xb87c, 0x8fd0);
		ocp_reg_write(tp, 0xb87e, 0xfb00);
		ocp_reg_write(tp, 0xb87c, 0x8fd2);
		ocp_reg_write(tp, 0xb87e, 0x0100);
		ocp_reg_write(tp, 0xb87c, 0x8fd4);
		ocp_reg_write(tp, 0xb87e, 0xf400);
		ocp_reg_write(tp, 0xb87c, 0x8fd6);
		ocp_reg_write(tp, 0xb87e, 0xff00);
		ocp_reg_write(tp, 0xb87c, 0x8fd8);
		ocp_reg_write(tp, 0xb87e, 0xf600);

		ocp_data = ocp_read_byte(tp, MCU_TYPE_PLA, PLA_USB_CFG);
		ocp_data |= EN_XG_LIP | EN_G_LIP;
		ocp_write_byte(tp, MCU_TYPE_PLA, PLA_USB_CFG, ocp_data);
		ocp_reg_write(tp, 0xb87c, 0x813d);
		ocp_reg_write(tp, 0xb87e, 0x390e);
		ocp_reg_write(tp, 0xb87c, 0x814f);
		ocp_reg_write(tp, 0xb87e, 0x790e);
		ocp_reg_write(tp, 0xb87c, 0x80b0);
		ocp_reg_write(tp, 0xb87e, 0x0f31);
		data = ocp_reg_read(tp, 0xbf4c);
		data |= BIT(1);
		ocp_reg_write(tp, 0xbf4c, data);
		data = ocp_reg_read(tp, 0xbcca);
		data |= BIT(9) | BIT(8);
		ocp_reg_write(tp, 0xbcca, data);
		ocp_reg_write(tp, 0xb87c, 0x8141);
		ocp_reg_write(tp, 0xb87e, 0x320e);
		ocp_reg_write(tp, 0xb87c, 0x8153);
		ocp_reg_write(tp, 0xb87e, 0x720e);
		ocp_reg_write(tp, 0xb87c, 0x8529);
		ocp_reg_write(tp, 0xb87e, 0x050e);
		data = ocp_reg_read(tp, OCP_EEE_CFG);
		data &= ~CTAP_SHORT_EN;
		ocp_reg_write(tp, OCP_EEE_CFG, data);

		sram_write(tp, 0x816c, 0xc4a0);
		sram_write(tp, 0x8170, 0xc4a0);
		sram_write(tp, 0x8174, 0x04a0);
		sram_write(tp, 0x8178, 0x04a0);
		sram_write(tp, 0x817c, 0x0719);
		sram_write(tp, 0x8ff4, 0x0400);
		sram_write(tp, 0x8ff1, 0x0404);

		ocp_reg_write(tp, 0xbf4a, 0x001b);
		ocp_reg_write(tp, 0xb87c, 0x8033);
		ocp_reg_write(tp, 0xb87e, 0x7c13);
		ocp_reg_write(tp, 0xb87c, 0x8037);
		ocp_reg_write(tp, 0xb87e, 0x7c13);
		ocp_reg_write(tp, 0xb87c, 0x803b);
		ocp_reg_write(tp, 0xb87e, 0xfc32);
		ocp_reg_write(tp, 0xb87c, 0x803f);
		ocp_reg_write(tp, 0xb87e, 0x7c13);
		ocp_reg_write(tp, 0xb87c, 0x8043);
		ocp_reg_write(tp, 0xb87e, 0x7c13);
		ocp_reg_write(tp, 0xb87c, 0x8047);
		ocp_reg_write(tp, 0xb87e, 0x7c13);

		ocp_reg_write(tp, 0xb87c, 0x8145);
		ocp_reg_write(tp, 0xb87e, 0x370e);
		ocp_reg_write(tp, 0xb87c, 0x8157);
		ocp_reg_write(tp, 0xb87e, 0x770e);
		ocp_reg_write(tp, 0xb87c, 0x8169);
		ocp_reg_write(tp, 0xb87e, 0x0d0a);
		ocp_reg_write(tp, 0xb87c, 0x817b);
		ocp_reg_write(tp, 0xb87e, 0x1d0a);

		data = sram_read(tp, 0x8217);
		data &= ~0xff00;
		data |= 0x5000;
		sram_write(tp, 0x8217, data);
		data = sram_read(tp, 0x821a);
		data &= ~0xff00;
		data |= 0x5000;
		sram_write(tp, 0x821a, data);
		sram_write(tp, 0x80da, 0x0403);
		data = sram_read(tp, 0x80dc);
		data &= ~0xff00;
		data |= 0x1000;
		sram_write(tp, 0x80dc, data);
		sram_write(tp, 0x80b3, 0x0384);
		sram_write(tp, 0x80b7, 0x2007);
		data = sram_read(tp, 0x80ba);
		data &= ~0xff00;
		data |= 0x6c00;
		sram_write(tp, 0x80ba, data);
		sram_write(tp, 0x80b5, 0xf009);
		data = sram_read(tp, 0x80bd);
		data &= ~0xff00;
		data |= 0x9f00;
		sram_write(tp, 0x80bd, data);
		sram_write(tp, 0x80c7, 0xf083);
		sram_write(tp, 0x80dd, 0x03f0);
		data = sram_read(tp, 0x80df);
		data &= ~0xff00;
		data |= 0x1000;
		sram_write(tp, 0x80df, data);
		sram_write(tp, 0x80cb, 0x2007);
		data = sram_read(tp, 0x80ce);
		data &= ~0xff00;
		data |= 0x6c00;
		sram_write(tp, 0x80ce, data);
		sram_write(tp, 0x80c9, 0x8009);
		data = sram_read(tp, 0x80d1);
		data &= ~0xff00;
		data |= 0x8000;
		sram_write(tp, 0x80d1, data);
		sram_write(tp, 0x80a3, 0x200a);
		sram_write(tp, 0x80a5, 0xf0ad);
		sram_write(tp, 0x809f, 0x6073);
		sram_write(tp, 0x80a1, 0x000b);
		data = sram_read(tp, 0x80a9);
		data &= ~0xff00;
		data |= 0xc000;
		sram_write(tp, 0x80a9, data);

		if (rtl_phy_patch_request(tp, true, true))
			return;

		data = ocp_reg_read(tp, 0xb896);
		data &= ~BIT(0);
		ocp_reg_write(tp, 0xb896, data);
		data = ocp_reg_read(tp, 0xb892);
		data &= ~0xff00;
		ocp_reg_write(tp, 0xb892, data);
		ocp_reg_write(tp, 0xb88e, 0xc23e);
		ocp_reg_write(tp, 0xb890, 0x0000);
		ocp_reg_write(tp, 0xb88e, 0xc240);
		ocp_reg_write(tp, 0xb890, 0x0103);
		ocp_reg_write(tp, 0xb88e, 0xc242);
		ocp_reg_write(tp, 0xb890, 0x0507);
		ocp_reg_write(tp, 0xb88e, 0xc244);
		ocp_reg_write(tp, 0xb890, 0x090b);
		ocp_reg_write(tp, 0xb88e, 0xc246);
		ocp_reg_write(tp, 0xb890, 0x0c0e);
		ocp_reg_write(tp, 0xb88e, 0xc248);
		ocp_reg_write(tp, 0xb890, 0x1012);
		ocp_reg_write(tp, 0xb88e, 0xc24a);
		ocp_reg_write(tp, 0xb890, 0x1416);
		data = ocp_reg_read(tp, 0xb896);
		data |= BIT(0);
		ocp_reg_write(tp, 0xb896, data);

		rtl_phy_patch_request(tp, false, true);

		data = ocp_reg_read(tp, 0xa86a);
		data |= BIT(0);
		ocp_reg_write(tp, 0xa86a, data);
		data = ocp_reg_read(tp, 0xa6f0);
		data |= BIT(0);
		ocp_reg_write(tp, 0xa6f0, data);

		ocp_reg_write(tp, 0xbfa0, 0xd70d);
		ocp_reg_write(tp, 0xbfa2, 0x4100);
		ocp_reg_write(tp, 0xbfa4, 0xe868);
		ocp_reg_write(tp, 0xbfa6, 0xdc59);
		ocp_reg_write(tp, 0xb54c, 0x3c18);
		data = ocp_reg_read(tp, 0xbfa4);
		data &= ~BIT(5);
		ocp_reg_write(tp, 0xbfa4, data);
		data = sram_read(tp, 0x817d);
		data |= BIT(12);
		sram_write(tp, 0x817d, data);
		break;
	case RTL_VER_13:
		/* 2.5G INRX */
		data = ocp_reg_read(tp, 0xac46);
		data &= ~0x00f0;
		data |= 0x0090;
		ocp_reg_write(tp, 0xac46, data);
		data = ocp_reg_read(tp, 0xad30);
		data &= ~0x0003;
		data |= 0x0001;
		ocp_reg_write(tp, 0xad30, data);
		fallthrough;
	case RTL_VER_15:
		/* EEE parameter */
		ocp_reg_write(tp, 0xb87c, 0x80f5);
		ocp_reg_write(tp, 0xb87e, 0x760e);
		ocp_reg_write(tp, 0xb87c, 0x8107);
		ocp_reg_write(tp, 0xb87e, 0x360e);
		ocp_reg_write(tp, 0xb87c, 0x8551);
		data = ocp_reg_read(tp, 0xb87e);
		data &= ~0xff00;
		data |= 0x0800;
		ocp_reg_write(tp, 0xb87e, data);

		/* ADC_PGA parameter */
		data = ocp_reg_read(tp, 0xbf00);
		data &= ~0xe000;
		data |= 0xa000;
		ocp_reg_write(tp, 0xbf00, data);
		data = ocp_reg_read(tp, 0xbf46);
		data &= ~0x0f00;
		data |= 0x0300;
		ocp_reg_write(tp, 0xbf46, data);

		/* Green Table-PGA, 1G full viterbi */
		sram_write(tp, 0x8044, 0x2417);
		sram_write(tp, 0x804a, 0x2417);
		sram_write(tp, 0x8050, 0x2417);
		sram_write(tp, 0x8056, 0x2417);
		sram_write(tp, 0x805c, 0x2417);
		sram_write(tp, 0x8062, 0x2417);
		sram_write(tp, 0x8068, 0x2417);
		sram_write(tp, 0x806e, 0x2417);
		sram_write(tp, 0x8074, 0x2417);
		sram_write(tp, 0x807a, 0x2417);

		/* XG PLL */
		data = ocp_reg_read(tp, 0xbf84);
		data &= ~0xe000;
		data |= 0xa000;
		ocp_reg_write(tp, 0xbf84, data);
		break;
	default:
		break;
	}

	if (rtl_phy_patch_request(tp, true, true))
		return;

	ocp_data = ocp_read_word(tp, MCU_TYPE_PLA, PLA_MAC_PWR_CTRL4);
	ocp_data |= EEE_SPDWN_EN;
	ocp_write_word(tp, MCU_TYPE_PLA, PLA_MAC_PWR_CTRL4, ocp_data);

	data = ocp_reg_read(tp, OCP_DOWN_SPEED);
	data &= ~(EN_EEE_100 | EN_EEE_1000);
	data |= EN_10M_CLKDIV;
	ocp_reg_write(tp, OCP_DOWN_SPEED, data);
	tp->ups_info._10m_ckdiv = true;
	tp->ups_info.eee_plloff_100 = false;
	tp->ups_info.eee_plloff_giga = false;

	data = ocp_reg_read(tp, OCP_POWER_CFG);
	data &= ~EEE_CLKDIV_EN;
	ocp_reg_write(tp, OCP_POWER_CFG, data);
	tp->ups_info.eee_ckdiv = false;

	rtl_phy_patch_request(tp, false, true);

	rtl_green_en(tp, test_bit(GREEN_ETHERNET, &tp->flags));

	data = ocp_reg_read(tp, 0xa428);
	data &= ~BIT(9);
	ocp_reg_write(tp, 0xa428, data);
	data = ocp_reg_read(tp, 0xa5ea);
	data &= ~BIT(0);
	ocp_reg_write(tp, 0xa5ea, data);
	tp->ups_info.lite_mode = 0;

	if (tp->eee_en)
		rtl_eee_enable(tp, true);

	r8153_aldps_en(tp, true);
	r8152b_enable_fc(tp);
	r8153_u2p3en(tp, true);

	set_bit(PHY_RESET, &tp->flags);
}

static void r8156_hw_phy_cfg_test(struct r8152 *tp)
{
	u32 ocp_data;
	u16 data;

	data = r8153_phy_status(tp, PHY_STAT_LAN_ON);

	/* disable ALDPS before updating the PHY parameters */
	r8153_aldps_en(tp, false);

	/* disable EEE before updating the PHY parameters */
	r8153_eee_en(tp, false);
	ocp_reg_write(tp, OCP_EEE_ADV, 0);

	r8156_firmware(tp);

	data = ocp_reg_read(tp, 0xa5d4);
	data |= BIT(7) | BIT(0);
	ocp_reg_write(tp, 0xa5d4, data);
	ocp_reg_write(tp, 0xa5e6, 0x6290);

	data = ocp_reg_read(tp, 0xa5e8);
	data &= ~BIT(3);
	ocp_reg_write(tp, 0xa5e8, data);
	data = ocp_reg_read(tp, 0xa428);
	data |= BIT(9);
	ocp_reg_write(tp, 0xa428, data);

	ocp_reg_write(tp, 0xb636, 0x2c00);
	data = ocp_reg_read(tp, 0xb460);
	data &= ~BIT(13);
	ocp_reg_write(tp, 0xb460, data);
	ocp_reg_write(tp, 0xb83e, 0x00a9);
	ocp_reg_write(tp, 0xb840, 0x0035);
	ocp_reg_write(tp, 0xb680, 0x0022);
	ocp_reg_write(tp, 0xb468, 0x10c0);
	ocp_reg_write(tp, 0xb468, 0x90c0);

	data = ocp_reg_read(tp, 0xb60a);
	data &= ~0xfff;
	data |= 0xc0;
	ocp_reg_write(tp, 0xb60a, data);
	data = ocp_reg_read(tp, 0xb628);
	data &= ~0xfff;
	data |= 0xc0;
	ocp_reg_write(tp, 0xb628, data);
	data = ocp_reg_read(tp, 0xb62a);
	data &= ~0xfff;
	data |= 0xc0;
	ocp_reg_write(tp, 0xb62a, data);

	data = ocp_reg_read(tp, 0xbc1e);
	data &= 0xf;
	data |= (data << 4) | (data << 8) | (data << 12);
	ocp_reg_write(tp, 0xbce0, data);
	data = ocp_reg_read(tp, 0xbd42);
	data &= ~BIT(8);
	ocp_reg_write(tp, 0xbd42, data);

	data = ocp_reg_read(tp, 0xbf90);
	data &= ~0xf0;
	data |= BIT(7);
	ocp_reg_write(tp, 0xbf90, data);
	data = ocp_reg_read(tp, 0xbf92);
	data &= ~0x3f;
	data |= 0x3fc0;
	ocp_reg_write(tp, 0xbf92, data);

	data = ocp_reg_read(tp, 0xbf94);
	data |= 0x3e00;
	ocp_reg_write(tp, 0xbf94, data);
	data = ocp_reg_read(tp, 0xbf88);
	data &= ~0x3eff;
	data |= 0x1e01;
	ocp_reg_write(tp, 0xbf88, data);

	data = ocp_reg_read(tp, 0xbc58);
	data &= ~BIT(1);
	ocp_reg_write(tp, 0xbc58, data);

	data = ocp_reg_read(tp, 0xbd0c);
	data &= ~0x3f;
	ocp_reg_write(tp, 0xbd0c, data);

	data = ocp_reg_read(tp, 0xbcc2);
	data &= ~BIT(14);
	ocp_reg_write(tp, 0xbcc2, data);

	ocp_reg_write(tp, 0xd098, 0x0427);

	data = ocp_reg_read(tp, 0xa430);
	data &= ~BIT(12);
	ocp_reg_write(tp, 0xa430, data);

	ocp_data = ocp_read_dword(tp, MCU_TYPE_PLA, 0xe84c);
	ocp_data |= BIT(6);
	ocp_write_dword(tp, MCU_TYPE_PLA, 0xe84c, ocp_data);

	data = ocp_reg_read(tp, 0xbeb4);
	data &= ~BIT(1);
	ocp_reg_write(tp, 0xbeb4, data);
	data = ocp_reg_read(tp, 0xbf0c);
	data &= ~BIT(13);
	data |= BIT(12);
	ocp_reg_write(tp, 0xbf0c, data);
	data = ocp_reg_read(tp, 0xbd44);
	data &= ~BIT(2);
	ocp_reg_write(tp, 0xbd44, data);

	data = ocp_reg_read(tp, 0xa442);
	data |= BIT(11);
	ocp_reg_write(tp, 0xa442, data);
	ocp_data = ocp_read_dword(tp, MCU_TYPE_PLA, 0xe84c);
	ocp_data |= BIT(7);
	ocp_write_dword(tp, MCU_TYPE_PLA, 0xe84c, ocp_data);

	r8156_lock_main(tp, true);
	data = ocp_reg_read(tp, 0xcc46);
	data &= ~0x700;
	ocp_reg_write(tp, 0xcc46, data);
	data = ocp_reg_read(tp, 0xcc46);
	data &= ~0x70;
	ocp_reg_write(tp, 0xcc46, data);
	data = ocp_reg_read(tp, 0xcc46);
	data &= ~0x70;
	data |= BIT(6) | BIT(4);
	ocp_reg_write(tp, 0xcc46, data);
	r8156_lock_main(tp, false);

	data = ocp_reg_read(tp, 0xbd38);
	data &= ~BIT(13);
	ocp_reg_write(tp, 0xbd38, data);
	data = ocp_reg_read(tp, 0xbd38);
	data |= BIT(12);
	ocp_reg_write(tp, 0xbd38, data);
	ocp_reg_write(tp, 0xbd36, 0x0fb4);
	data = ocp_reg_read(tp, 0xbd38);
	data |= BIT(13);
	ocp_reg_write(tp, 0xbd38, data);

//	if (tp->eee_en) {
//		r8153_eee_en(tp, true);
//		ocp_reg_write(tp, OCP_EEE_ADV, tp->eee_adv);
//	}

	r8153_aldps_en(tp, true);
	r8152b_enable_fc(tp);
	r8153_u2p3en(tp, true);
}

static void r8156_init(struct r8152 *tp)
{
	u32 ocp_data;
	u16 data;
	int i;

	if (test_bit(RTL8152_UNPLUG, &tp->flags))
		return;

	ocp_data = ocp_read_byte(tp, MCU_TYPE_USB, USB_ECM_OP);
	ocp_data &= ~EN_ALL_SPEED;
	ocp_write_byte(tp, MCU_TYPE_USB, USB_ECM_OP, ocp_data);

	ocp_write_word(tp, MCU_TYPE_USB, USB_SPEED_OPTION, 0);

	ocp_data = ocp_read_word(tp, MCU_TYPE_USB, USB_ECM_OPTION);
	ocp_data |= BYPASS_MAC_RESET;
	ocp_write_word(tp, MCU_TYPE_USB, USB_ECM_OPTION, ocp_data);

	r8153b_u1u2en(tp, false);

	for (i = 0; i < 500; i++) {
		if (ocp_read_word(tp, MCU_TYPE_PLA, PLA_BOOT_CTRL) &
		    AUTOLOAD_DONE)
			break;

		msleep(20);
		if (test_bit(RTL8152_UNPLUG, &tp->flags))
			return;
	}

	data = r8153_phy_status(tp, 0);
	if (data == PHY_STAT_EXT_INIT) {
		data = ocp_reg_read(tp, 0xa468);
		data &= ~(BIT(3) | BIT(1));
		ocp_reg_write(tp, 0xa468, data);
	}

	data = r8152_mdio_read(tp, MII_BMCR);
	if (data & BMCR_PDOWN) {
		data &= ~BMCR_PDOWN;
		r8152_mdio_write(tp, MII_BMCR, data);
	}

	data = r8153_phy_status(tp, PHY_STAT_LAN_ON);
	WARN_ON_ONCE(data != PHY_STAT_LAN_ON);

	r8153_u2p3en(tp, false);

	/* MSC timer = 0xfff * 8ms = 32760 ms */
	ocp_write_word(tp, MCU_TYPE_USB, USB_MSC_TIMER, 0x0fff);

	/* U1/U2/L1 idle timer. 500 us */
	ocp_write_word(tp, MCU_TYPE_USB, USB_U1U2_TIMER, 500);

	r8153b_power_cut_en(tp, false);
	r8156_ups_en(tp, false);
	r8153_queue_wake(tp, false);
	rtl_runtime_suspend_enable(tp, false);

	if (tp->udev->speed >= USB_SPEED_SUPER)
		r8153b_u1u2en(tp, true);

	usb_enable_lpm(tp->udev);

//	ocp_data = ocp_read_word(tp, MCU_TYPE_USB, 0xd850) & 0xc000;
//	switch (ocp_data) {
//	case 0x4000:
//		tp->dash_mode = 1;
//		r8156_mac_clk_spd(tp, false);
//		break;
//	case 0x8000:
//		tp->dash_mode = 0;
		r8156_mac_clk_spd(tp, true);
//		break;
//	default:
//		netif_warn(tp, drv, tp->netdev, "Invalid type %x\n", ocp_data);
//		break;
//	}


	r8153b_mcu_spdown_en(tp, false);

	ocp_data = ocp_read_word(tp, MCU_TYPE_PLA, PLA_EXTRA_STATUS);
	if (rtl8152_get_speed(tp) & LINK_STATUS)
		ocp_data |= CUR_LINK_OK;
	else
		ocp_data &= ~CUR_LINK_OK;
	/* r8153_queue_wake() has cleared this bit */
	/* ocp_data &= ~BIT(8); */
	ocp_data |= POLL_LINK_CHG;
	ocp_write_word(tp, MCU_TYPE_PLA, PLA_EXTRA_STATUS, ocp_data);

	set_bit(GREEN_ETHERNET, &tp->flags);

	/* rx aggregation */
	ocp_data = ocp_read_word(tp, MCU_TYPE_USB, USB_USB_CTRL);
	ocp_data &= ~(RX_AGG_DISABLE | RX_ZERO_EN);
	ocp_write_word(tp, MCU_TYPE_USB, USB_USB_CTRL, ocp_data);

	/* Set Rx aggregation parameters to default value
	ocp_data = ocp_read_byte(tp, MCU_TYPE_USB, 0xd4c9);
	ocp_data |= BIT(2);
	ocp_write_byte(tp, MCU_TYPE_USB, 0xd4c9, ocp_data);
	*/

	ocp_data = ocp_read_byte(tp, MCU_TYPE_USB, USB_BMU_CONFIG);
	ocp_data |= ACT_ODMA;
	ocp_write_byte(tp, MCU_TYPE_USB, USB_BMU_CONFIG, ocp_data);

	r8156_mdio_force_mode(tp);
	rtl_tally_reset(tp);

	tp->coalesce = 15000;	/* 15 us */
}

static void r8156b_init(struct r8152 *tp)
{
	u32 ocp_data;
	u16 data;
	int i;

	if (test_bit(RTL8152_UNPLUG, &tp->flags))
		return;

	ocp_data = ocp_read_byte(tp, MCU_TYPE_USB, USB_ECM_OP);
	ocp_data &= ~EN_ALL_SPEED;
	ocp_write_byte(tp, MCU_TYPE_USB, USB_ECM_OP, ocp_data);

	ocp_write_word(tp, MCU_TYPE_USB, USB_SPEED_OPTION, 0);

	ocp_data = ocp_read_word(tp, MCU_TYPE_USB, USB_ECM_OPTION);
	ocp_data |= BYPASS_MAC_RESET;
	ocp_write_word(tp, MCU_TYPE_USB, USB_ECM_OPTION, ocp_data);

	ocp_data = ocp_read_word(tp, MCU_TYPE_USB, USB_U2P3_CTRL);
	ocp_data |= RX_DETECT8;
	ocp_write_word(tp, MCU_TYPE_USB, USB_U2P3_CTRL, ocp_data);

	r8153b_u1u2en(tp, false);

	switch (tp->version) {
	case RTL_VER_13:
	case RTL_VER_15:
		r8156b_wait_loading_flash(tp);
		break;
	default:
		break;
	}

	for (i = 0; i < 500; i++) {
		if (ocp_read_word(tp, MCU_TYPE_PLA, PLA_BOOT_CTRL) &
		    AUTOLOAD_DONE)
			break;

		msleep(20);
		if (test_bit(RTL8152_UNPLUG, &tp->flags))
			return;
	}

	data = r8153_phy_status(tp, 0);
	if (data == PHY_STAT_EXT_INIT) {
		data = ocp_reg_read(tp, 0xa468);
		data &= ~(BIT(3) | BIT(1));
		ocp_reg_write(tp, 0xa468, data);

		data = ocp_reg_read(tp, 0xa466);
		data &= ~BIT(0);
		ocp_reg_write(tp, 0xa466, data);
	}

	data = r8152_mdio_read(tp, MII_BMCR);
	if (data & BMCR_PDOWN) {
		data &= ~BMCR_PDOWN;
		r8152_mdio_write(tp, MII_BMCR, data);
	}

	data = r8153_phy_status(tp, PHY_STAT_LAN_ON);

	r8153_u2p3en(tp, false);

	/* MSC timer = 0xfff * 8ms = 32760 ms */
	ocp_write_word(tp, MCU_TYPE_USB, USB_MSC_TIMER, 0x0fff);

	/* U1/U2/L1 idle timer. 500 us */
	ocp_write_word(tp, MCU_TYPE_USB, USB_U1U2_TIMER, 500);

	r8153b_power_cut_en(tp, false);
	r8156_ups_en(tp, false);
	r8153_queue_wake(tp, false);
	rtl_runtime_suspend_enable(tp, false);

	if (tp->udev->speed >= USB_SPEED_SUPER)
		r8153b_u1u2en(tp, true);

	usb_enable_lpm(tp->udev);

	ocp_data = ocp_read_word(tp, MCU_TYPE_PLA, PLA_RCR);
	ocp_data &= ~SLOT_EN;
	ocp_write_word(tp, MCU_TYPE_PLA, PLA_RCR, ocp_data);

	ocp_data = ocp_read_word(tp, MCU_TYPE_PLA, PLA_CPCR);
	ocp_data |= FLOW_CTRL_EN;
	ocp_write_word(tp, MCU_TYPE_PLA, PLA_CPCR, ocp_data);

	/* enable fc timer and set timer to 600 ms. */
	ocp_write_word(tp, MCU_TYPE_USB, USB_FC_TIMER,
		       CTRL_TIMER_EN | (600 / 8));

	ocp_data = ocp_read_word(tp, MCU_TYPE_USB, USB_FW_CTRL);
	if (!(ocp_read_word(tp, MCU_TYPE_PLA, PLA_POL_GPIO_CTRL) & DACK_DET_EN))
		ocp_data |= FLOW_CTRL_PATCH_2;
	ocp_data &= ~AUTO_SPEEDUP;
	ocp_write_word(tp, MCU_TYPE_USB, USB_FW_CTRL, ocp_data);

	ocp_data = ocp_read_word(tp, MCU_TYPE_USB, USB_FW_TASK);
	ocp_data |= FC_PATCH_TASK;
	ocp_write_word(tp, MCU_TYPE_USB, USB_FW_TASK, ocp_data);

	r8156_mac_clk_spd(tp, true);
	r8153b_mcu_spdown_en(tp, false);

	ocp_data = ocp_read_word(tp, MCU_TYPE_PLA, PLA_EXTRA_STATUS);
	if (rtl8152_get_speed(tp) & LINK_STATUS)
		ocp_data |= CUR_LINK_OK;
	else
		ocp_data &= ~CUR_LINK_OK;
	/* r8153_queue_wake() has cleared this bit */
	/* ocp_data &= ~BIT(8); */
	ocp_data |= POLL_LINK_CHG;
	ocp_write_word(tp, MCU_TYPE_PLA, PLA_EXTRA_STATUS, ocp_data);

	set_bit(GREEN_ETHERNET, &tp->flags);

	/* rx aggregation */
	ocp_data = ocp_read_word(tp, MCU_TYPE_USB, USB_USB_CTRL);
	ocp_data &= ~(RX_AGG_DISABLE | RX_ZERO_EN);
	ocp_write_word(tp, MCU_TYPE_USB, USB_USB_CTRL, ocp_data);

	/* Set Rx aggregation parameters to default value
	ocp_data = ocp_read_byte(tp, MCU_TYPE_USB, 0xd4c9);
	ocp_data |= BIT(2);
	ocp_write_byte(tp, MCU_TYPE_USB, 0xd4c9, ocp_data);
	*/

	r8156_mdio_force_mode(tp);
	rtl_tally_reset(tp);

	tp->coalesce = 15000;	/* 15 us */
}

static bool rtl_check_vendor_ok(struct usb_interface *intf)
{
	struct usb_host_interface *alt = intf->cur_altsetting;
#if LINUX_VERSION_CODE < KERNEL_VERSION(4,12,0)
	struct usb_host_endpoint *in = NULL, *out = NULL, *intr = NULL;
	unsigned int ep;

	if (alt->desc.bNumEndpoints < 3) {
		dev_err(&intf->dev, "Unexpected bNumEndpoints %d\n", alt->desc.bNumEndpoints);
		return false;
	}

	for (ep = 0; ep < alt->desc.bNumEndpoints; ep++) {
		struct usb_host_endpoint *e;

		e = alt->endpoint + ep;

		/* ignore endpoints which cannot transfer data */
		if (!usb_endpoint_maxp(&e->desc))
			continue;

		switch (e->desc.bmAttributes) {
		case USB_ENDPOINT_XFER_INT:
			if (!usb_endpoint_dir_in(&e->desc))
				continue;
			if (!intr)
				intr = e;
			break;
		case USB_ENDPOINT_XFER_BULK:
			if (usb_endpoint_dir_in(&e->desc)) {
				if (!in)
					in = e;
			} else if (!out) {
				out = e;
			}
			break;
		default:
			continue;
		}
	}

	if (!in || !out || !intr) {
		dev_err(&intf->dev, "Miss Endpoints\n");
		return false;
	}

	if ((in->desc.bEndpointAddress & USB_ENDPOINT_NUMBER_MASK) != 1) {
		dev_err(&intf->dev, "Invalid Rx endpoint address\n");
		return false;
	}

	if ((out->desc.bEndpointAddress & USB_ENDPOINT_NUMBER_MASK) != 2) {
		dev_err(&intf->dev, "Invalid Tx endpoint address\n");
		return false;
	}

	if ((intr->desc.bEndpointAddress & USB_ENDPOINT_NUMBER_MASK) != 3) {
		dev_err(&intf->dev, "Invalid interrupt endpoint address\n");
		return false;
	}
#else
	struct usb_endpoint_descriptor *in, *out, *intr;

	if (usb_find_common_endpoints(alt, &in, &out, &intr, NULL) < 0) {
		dev_err(&intf->dev, "Expected endpoints are not found\n");
		return false;
	}

	/* Check Rx endpoint address */
	if (usb_endpoint_num(in) != 1) {
		dev_err(&intf->dev, "Invalid Rx endpoint address\n");
		return false;
	}

	/* Check Tx endpoint address */
	if (usb_endpoint_num(out) != 2) {
		dev_err(&intf->dev, "Invalid Tx endpoint address\n");
		return false;
	}

	/* Check interrupt endpoint address */
	if (usb_endpoint_num(intr) != 3) {
		dev_err(&intf->dev, "Invalid interrupt endpoint address\n");
		return false;
	}
#endif /* LINUX_VERSION_CODE < KERNEL_VERSION(4,12,0) */

	return true;
}

static bool rtl_vendor_mode(struct usb_interface *intf)
{
	struct usb_host_interface *alt = intf->cur_altsetting;
	struct usb_device *udev;
	struct usb_host_config *c;
	int i, num_configs;

	if (alt->desc.bInterfaceClass == USB_CLASS_VENDOR_SPEC)
		return rtl_check_vendor_ok(intf);

#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,19)
	dev_err(&intf->dev, "The kernel is too old to set configuration\n");
#else
	/* The vendor mode is not always config #1, so to find it out. */
	udev = interface_to_usbdev(intf);
	c = udev->config;
	num_configs = udev->descriptor.bNumConfigurations;
	if (num_configs < 2)
		return false;

	for (i = 0; i < num_configs; (i++, c++)) {
		struct usb_interface_descriptor	*desc = NULL;

		if (c->desc.bNumInterfaces > 0)
			desc = &c->intf_cache[0]->altsetting->desc;
		else
			continue;

		if (desc->bInterfaceClass == USB_CLASS_VENDOR_SPEC) {
			usb_driver_set_configuration(udev, c->desc.bConfigurationValue);
			break;
		}
	}

	if (i == num_configs)
		dev_err(&intf->dev, "Unexpected Device\n");
#endif

	return false;
}

static int rtl8152_pre_reset(struct usb_interface *intf)
{
	struct r8152 *tp = usb_get_intfdata(intf);
	struct net_device *netdev;

	if (!tp)
		return 0;

	netdev = tp->netdev;
	if (!netif_running(netdev))
		return 0;

	netif_stop_queue(netdev);
	tasklet_disable(&tp->tx_tl);
	smp_mb__before_atomic();
	clear_bit(WORK_ENABLE, &tp->flags);
	smp_mb__after_atomic();
	usb_kill_urb(tp->intr_urb);
	cancel_delayed_work_sync(&tp->schedule);
	napi_disable(&tp->napi);
	if (netif_carrier_ok(netdev)) {
		mutex_lock(&tp->control);
		tp->rtl_ops.disable(tp);
		mutex_unlock(&tp->control);
	}

	return 0;
}

static int rtl8152_post_reset(struct usb_interface *intf)
{
	struct r8152 *tp = usb_get_intfdata(intf);
	struct net_device *netdev;
	struct sockaddr sa;

	if (!tp)
		return 0;

	/* reset the MAC address in case of policy change */
	if (determine_ethernet_addr(tp, &sa) >= 0) {
		rtnl_lock();
#if LINUX_VERSION_CODE < KERNEL_VERSION(5,0,0)
		dev_set_mac_address(tp->netdev, &sa);
#else
		dev_set_mac_address(tp->netdev, &sa, NULL);
#endif /* LINUX_VERSION_CODE < KERNEL_VERSION(5,0,0) */
		rtnl_unlock();
	}

	netdev = tp->netdev;
	if (!netif_running(netdev))
		return 0;

	smp_mb__before_atomic();
	set_bit(WORK_ENABLE, &tp->flags);
	smp_mb__after_atomic();
	if (netif_carrier_ok(netdev)) {
		mutex_lock(&tp->control);
		tp->rtl_ops.enable(tp);
		rtl_start_rx(tp);
		rtl8152_set_rx_mode(netdev);
		mutex_unlock(&tp->control);
	}

	napi_enable(&tp->napi);
	tasklet_enable(&tp->tx_tl);
	netif_wake_queue(netdev);
	usb_submit_urb(tp->intr_urb, GFP_KERNEL);

	if (!list_empty(&tp->rx_done))
		napi_schedule(&tp->napi);

	return 0;
}

static bool delay_autosuspend(struct r8152 *tp)
{
	bool sw_linking = !!netif_carrier_ok(tp->netdev);
	bool hw_linking = !!(rtl8152_get_speed(tp) & LINK_STATUS);

	/* This means a linking change occurs and the driver doesn't detect it,
	 * yet. If the driver has disabled tx/rx and hw is linking on, the
	 * device wouldn't wake up by receiving any packet.
	 */
	if (work_busy(&tp->schedule.work) || sw_linking != hw_linking)
		return true;

	/* If the linking down is occurred by nway, the device may miss the
	 * linking change event. And it wouldn't wake when linking on.
	 */
	if (!sw_linking && tp->rtl_ops.in_nway(tp))
		return true;
	else if (!skb_queue_empty(&tp->tx_queue))
		return true;
	else
		return false;
}

static int rtl8152_runtime_resume(struct r8152 *tp)
{
	struct net_device *netdev = tp->netdev;

	if (netif_running(netdev) && netdev->flags & IFF_UP) {
		struct napi_struct *napi = &tp->napi;

		tp->rtl_ops.autosuspend_en(tp, false);
		napi_disable(napi);
		smp_mb__before_atomic();
		set_bit(WORK_ENABLE, &tp->flags);
		smp_mb__after_atomic();

		if (netif_carrier_ok(netdev)) {
			if (rtl8152_get_speed(tp) & LINK_STATUS) {
				rtl_start_rx(tp);
			} else {
				netif_carrier_off(netdev);
				tp->rtl_ops.disable(tp);
				netif_info(tp, link, netdev, "linking down\n");
			}
		}

		napi_enable(napi);
		clear_bit(SELECTIVE_SUSPEND, &tp->flags);
		smp_mb__after_atomic();

		if (!list_empty(&tp->rx_done)) {
			local_bh_disable();
			napi_schedule(&tp->napi);
			local_bh_enable();
		}

		usb_submit_urb(tp->intr_urb, GFP_NOIO);
	} else {
		if (netdev->flags & IFF_UP)
			tp->rtl_ops.autosuspend_en(tp, false);

		clear_bit(SELECTIVE_SUSPEND, &tp->flags);
		smp_mb__after_atomic();
	}

	return 0;
}

static int rtl8152_system_resume(struct r8152 *tp)
{
	struct net_device *netdev = tp->netdev;

	netif_device_attach(netdev);

	if (netif_running(netdev) && (netdev->flags & IFF_UP)) {
		tp->rtl_ops.up(tp);
		netif_carrier_off(netdev);
		smp_mb__before_atomic();
		set_bit(WORK_ENABLE, &tp->flags);
		smp_mb__after_atomic();
		if (test_and_clear_bit(RECOVER_SPEED, &tp->flags))
			rtl8152_set_speed(tp, tp->autoneg, tp->speed,
					  tp->duplex, tp->advertising);
		usb_submit_urb(tp->intr_urb, GFP_NOIO);
	}

	return 0;
}

static int rtl8152_runtime_suspend(struct r8152 *tp)
{
	struct net_device *netdev = tp->netdev;
	int ret = 0;

	if (!tp->rtl_ops.autosuspend_en)
		return -EBUSY;

	set_bit(SELECTIVE_SUSPEND, &tp->flags);
	smp_mb__after_atomic();

	if (netif_running(netdev) && test_bit(WORK_ENABLE, &tp->flags)) {
		u32 rcr = 0;

		if (netif_carrier_ok(netdev)) {
			u32 ocp_data;

			rcr = ocp_read_dword(tp, MCU_TYPE_PLA, PLA_RCR);
			ocp_data = rcr & ~RCR_ACPT_ALL;
			ocp_write_dword(tp, MCU_TYPE_PLA, PLA_RCR, ocp_data);
			rxdy_gated_en(tp, true);
			ocp_data = ocp_read_byte(tp, MCU_TYPE_PLA,
						 PLA_OOB_CTRL);
			if (!(ocp_data & RXFIFO_EMPTY)) {
				rxdy_gated_en(tp, false);
				ocp_write_dword(tp, MCU_TYPE_PLA, PLA_RCR, rcr);
				clear_bit(SELECTIVE_SUSPEND, &tp->flags);
				smp_mb__after_atomic();
				ret = -EBUSY;
				goto out1;
			}
		}

		smp_mb__before_atomic();
		clear_bit(WORK_ENABLE, &tp->flags);
		smp_mb__after_atomic();
		usb_kill_urb(tp->intr_urb);

		tp->rtl_ops.autosuspend_en(tp, true);

		if (netif_carrier_ok(netdev)) {
			struct napi_struct *napi = &tp->napi;

			napi_disable(napi);
			rtl_stop_rx(tp);
			rxdy_gated_en(tp, false);
			ocp_write_dword(tp, MCU_TYPE_PLA, PLA_RCR, rcr);
			napi_enable(napi);
		}

		if (delay_autosuspend(tp)) {
			rtl8152_runtime_resume(tp);
			ret = -EBUSY;
		}
	}

out1:
	return ret;
}

static int rtl8152_system_suspend(struct r8152 *tp)
{
	struct net_device *netdev = tp->netdev;

	netif_device_detach(netdev);

	if (netif_running(netdev) && test_bit(WORK_ENABLE, &tp->flags)) {
		struct napi_struct *napi = &tp->napi;

		smp_mb__before_atomic();
		clear_bit(WORK_ENABLE, &tp->flags);
		smp_mb__after_atomic();
		usb_kill_urb(tp->intr_urb);
		tasklet_disable(&tp->tx_tl);
		napi_disable(napi);
		cancel_delayed_work_sync(&tp->schedule);
		tp->rtl_ops.down(tp);

		if (tp->version == RTL_VER_01)
			rtl8152_set_speed(tp, AUTONEG_ENABLE, 0, 0, 3);
		else
			rtl_speed_down(tp);

		napi_enable(napi);
		tasklet_enable(&tp->tx_tl);
	}

	return 0;
}

static int rtl8152_suspend(struct usb_interface *intf, pm_message_t message)
{
	struct r8152 *tp = usb_get_intfdata(intf);
	int ret;

	mutex_lock(&tp->control);

	if (PMSG_IS_AUTO(message))
		ret = rtl8152_runtime_suspend(tp);
	else
		ret = rtl8152_system_suspend(tp);

	mutex_unlock(&tp->control);

	return ret;
}

static int rtl8152_resume(struct usb_interface *intf)
{
	struct r8152 *tp = usb_get_intfdata(intf);
	int ret;

	mutex_lock(&tp->control);

	rtl_reset_ocp_base(tp);

	if (test_bit(SELECTIVE_SUSPEND, &tp->flags))
		ret = rtl8152_runtime_resume(tp);
	else
		ret = rtl8152_system_resume(tp);

	mutex_unlock(&tp->control);

	return ret;
}

static int rtl8152_reset_resume(struct usb_interface *intf)
{
	struct r8152 *tp = usb_get_intfdata(intf);

	clear_bit(SELECTIVE_SUSPEND, &tp->flags);
	rtl_reset_ocp_base(tp);
	tp->rtl_ops.init(tp);
	queue_delayed_work(system_long_wq, &tp->hw_phy_work, 0);
	set_ethernet_addr(tp, true);
	return rtl8152_resume(intf);
}

static void rtl8152_get_wol(struct net_device *dev, struct ethtool_wolinfo *wol)
{
	struct r8152 *tp = netdev_priv(dev);

	if (usb_autopm_get_interface(tp->intf) < 0)
		return;

	if (!rtl_can_wakeup(tp)) {
		wol->supported = 0;
		wol->wolopts = 0;
	} else {
		mutex_lock(&tp->control);
		wol->supported = WAKE_ANY;
		wol->wolopts = __rtl_get_wol(tp);
		mutex_unlock(&tp->control);
	}

	usb_autopm_put_interface(tp->intf);
}

static int rtl8152_set_wol(struct net_device *dev, struct ethtool_wolinfo *wol)
{
	struct r8152 *tp = netdev_priv(dev);
	int ret;

	if (!rtl_can_wakeup(tp))
		return -EOPNOTSUPP;

	if (wol->wolopts & ~WAKE_ANY)
		return -EINVAL;

	ret = usb_autopm_get_interface(tp->intf);
	if (ret < 0)
		goto out_set_wol;

	mutex_lock(&tp->control);

	__rtl_set_wol(tp, wol->wolopts);
	tp->saved_wolopts = wol->wolopts & WAKE_ANY;

	mutex_unlock(&tp->control);

	usb_autopm_put_interface(tp->intf);

out_set_wol:
	return ret;
}

static u32 rtl8152_get_msglevel(struct net_device *dev)
{
	struct r8152 *tp = netdev_priv(dev);

	return tp->msg_enable;
}

static void rtl8152_set_msglevel(struct net_device *dev, u32 value)
{
	struct r8152 *tp = netdev_priv(dev);

	tp->msg_enable = value;
}

static void rtl8152_get_drvinfo(struct net_device *netdev,
				struct ethtool_drvinfo *info)
{
	struct r8152 *tp = netdev_priv(netdev);

	strlcpy(info->driver, MODULENAME, sizeof(info->driver));
	strlcpy(info->version, DRIVER_VERSION, sizeof(info->version));
	usb_make_path(tp->udev, info->bus_info, sizeof(info->bus_info));
}

#if LINUX_VERSION_CODE < KERNEL_VERSION(4,20,0)
static
int rtl8152_get_settings(struct net_device *netdev, struct ethtool_cmd *cmd)
{
	struct r8152 *tp = netdev_priv(netdev);
	u16 bmcr, bmsr;
	int ret, advert;

	ret = usb_autopm_get_interface(tp->intf);
	if (ret < 0)
		goto out;

	cmd->supported =
	    (SUPPORTED_10baseT_Half | SUPPORTED_10baseT_Full |
	     SUPPORTED_100baseT_Half | SUPPORTED_100baseT_Full |
	     SUPPORTED_Autoneg | SUPPORTED_MII);

	/* only supports twisted-pair */
	cmd->port = PORT_MII;

	/* only supports internal transceiver */
	cmd->transceiver = XCVR_INTERNAL;
	cmd->phy_address = 32;
#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,31)
	cmd->mdio_support = ETH_MDIO_SUPPORTS_C22;
#endif
	cmd->advertising = ADVERTISED_MII;

	mutex_lock(&tp->control);

	bmcr = r8152_mdio_read(tp, MII_BMCR);
	bmsr = r8152_mdio_read(tp, MII_BMSR);

	advert = r8152_mdio_read(tp, MII_ADVERTISE);
	if (advert & ADVERTISE_10HALF)
		cmd->advertising |= ADVERTISED_10baseT_Half;
	if (advert & ADVERTISE_10FULL)
		cmd->advertising |= ADVERTISED_10baseT_Full;
	if (advert & ADVERTISE_100HALF)
		cmd->advertising |= ADVERTISED_100baseT_Half;
	if (advert & ADVERTISE_100FULL)
		cmd->advertising |= ADVERTISED_100baseT_Full;
	if (advert & ADVERTISE_PAUSE_CAP)
		cmd->advertising |= ADVERTISED_Pause;
	if (advert & ADVERTISE_PAUSE_ASYM)
		cmd->advertising |= ADVERTISED_Asym_Pause;
	if (tp->mii.supports_gmii) {
		u16 ctrl1000 = r8152_mdio_read(tp, MII_CTRL1000);

		cmd->supported |= SUPPORTED_1000baseT_Full;

		if (tp->support_2500full) {
			u16 data = ocp_reg_read(tp, 0xa5d4);

			cmd->supported |= SUPPORTED_2500baseX_Full;
			if (data & BIT(7))
				cmd->advertising |= ADVERTISED_2500baseX_Full;
		}

		if (ctrl1000 & ADVERTISE_1000HALF)
			cmd->advertising |= ADVERTISED_1000baseT_Half;
		if (ctrl1000 & ADVERTISE_1000FULL)
			cmd->advertising |= ADVERTISED_1000baseT_Full;
	}

#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,31)
	if (bmsr & BMSR_ANEGCOMPLETE) {
		advert = r8152_mdio_read(tp, MII_LPA);
		if (advert & LPA_LPACK)
			cmd->lp_advertising |= ADVERTISED_Autoneg;
		if (advert & ADVERTISE_10HALF)
			cmd->lp_advertising |=
				ADVERTISED_10baseT_Half;
		if (advert & ADVERTISE_10FULL)
			cmd->lp_advertising |=
				ADVERTISED_10baseT_Full;
		if (advert & ADVERTISE_100HALF)
			cmd->lp_advertising |=
				ADVERTISED_100baseT_Half;
		if (advert & ADVERTISE_100FULL)
			cmd->lp_advertising |=
				ADVERTISED_100baseT_Full;

		if (tp->mii.supports_gmii) {
			u16 stat1000 = r8152_mdio_read(tp, MII_STAT1000);

			if (stat1000 & LPA_1000HALF)
				cmd->lp_advertising |=
					ADVERTISED_1000baseT_Half;
			if (stat1000 & LPA_1000FULL)
				cmd->lp_advertising |=
					ADVERTISED_1000baseT_Full;
		}
	} else {
		cmd->lp_advertising = 0;
	}
#endif

	if (bmcr & BMCR_ANENABLE) {
		cmd->advertising |= ADVERTISED_Autoneg;
		cmd->autoneg = AUTONEG_ENABLE;
	} else {
		cmd->autoneg = AUTONEG_DISABLE;
	}


	if (netif_running(netdev) && netif_carrier_ok(netdev)) {
		u16 speed = rtl8152_get_speed(tp);

		if (speed & _100bps)
			cmd->speed = SPEED_100;
		else if (speed & _10bps)
			cmd->speed = SPEED_10;
		else if (tp->mii.supports_gmii && (speed & _1000bps))
			cmd->speed = SPEED_1000;
		else if (tp->support_2500full && (speed & _2500bps))
			cmd->speed = SPEED_2500;

		cmd->duplex = (speed & FULL_DUP) ? DUPLEX_FULL : DUPLEX_HALF;
	} else {
		cmd->speed = SPEED_UNKNOWN;
		cmd->duplex = DUPLEX_UNKNOWN;
	}

	mutex_unlock(&tp->control);

	usb_autopm_put_interface(tp->intf);

out:
	return ret;
}

static int rtl8152_set_settings(struct net_device *dev, struct ethtool_cmd *cmd)
{
	struct r8152 *tp = netdev_priv(dev);
	u32 advertising = 0;
	int ret;

	ret = usb_autopm_get_interface(tp->intf);
	if (ret < 0)
		goto out;

	if (cmd->advertising & ADVERTISED_10baseT_Half)
		advertising |= RTL_ADVERTISED_10_HALF;
	if (cmd->advertising & ADVERTISED_10baseT_Full)
		advertising |= RTL_ADVERTISED_10_FULL;
	if (cmd->advertising & ADVERTISED_100baseT_Half)
		advertising |= RTL_ADVERTISED_100_HALF;
	if (cmd->advertising & ADVERTISED_100baseT_Full)
		advertising |= RTL_ADVERTISED_100_FULL;
	if (cmd->advertising & ADVERTISED_1000baseT_Half)
		advertising |= RTL_ADVERTISED_1000_HALF;
	if (cmd->advertising & ADVERTISED_1000baseT_Full)
		advertising |= RTL_ADVERTISED_1000_FULL;
	if (cmd->advertising & ADVERTISED_2500baseX_Full)
		advertising |= RTL_ADVERTISED_2500_FULL;

	mutex_lock(&tp->control);

	ret = rtl8152_set_speed(tp, cmd->autoneg, cmd->speed, cmd->duplex,
				advertising);
	if (!ret) {
		tp->autoneg = cmd->autoneg;
		tp->speed = cmd->speed;
		tp->duplex = cmd->duplex;
		tp->advertising = advertising;
	}

	mutex_unlock(&tp->control);

	usb_autopm_put_interface(tp->intf);

out:
	return ret;
}
#endif /* LINUX_VERSION_CODE < KERNEL_VERSION(4,20,0) */

#if LINUX_VERSION_CODE >= KERNEL_VERSION(4,6,0)
static int rtl8152_get_link_ksettings(struct net_device *netdev,
				      struct ethtool_link_ksettings *cmd)
{
	struct r8152 *tp = netdev_priv(netdev);
	u16 bmcr, bmsr, advert;
	int ret;

	ret = usb_autopm_get_interface(tp->intf);
	if (ret < 0)
		goto out1;

	/* only supports twisted-pair */
	cmd->base.port = PORT_MII;

	/* this isn't fully supported at higher layers */
	cmd->base.phy_address = 32;
	cmd->base.mdio_support = ETH_MDIO_SUPPORTS_C22;

	linkmode_set_bit(ETHTOOL_LINK_MODE_10baseT_Half_BIT,
			 cmd->link_modes.supported);
	linkmode_set_bit(ETHTOOL_LINK_MODE_10baseT_Full_BIT,
			 cmd->link_modes.supported);
	linkmode_set_bit(ETHTOOL_LINK_MODE_100baseT_Half_BIT,
			 cmd->link_modes.supported);
	linkmode_set_bit(ETHTOOL_LINK_MODE_100baseT_Full_BIT,
			 cmd->link_modes.supported);
	linkmode_set_bit(ETHTOOL_LINK_MODE_Autoneg_BIT,
			 cmd->link_modes.supported);
	linkmode_set_bit(ETHTOOL_LINK_MODE_MII_BIT,
			 cmd->link_modes.supported);
	linkmode_mod_bit(ETHTOOL_LINK_MODE_1000baseT_Full_BIT,
			 cmd->link_modes.supported, tp->mii.supports_gmii);
	linkmode_mod_bit(ETHTOOL_LINK_MODE_2500baseT_Full_BIT,
			 cmd->link_modes.supported, tp->support_2500full);

	ret = mutex_lock_interruptible(&tp->control);
	if (ret < 0)
		goto out2;

	bmcr = r8152_mdio_read(tp, MII_BMCR);
	bmsr = r8152_mdio_read(tp, MII_BMSR);

	linkmode_mod_bit(ETHTOOL_LINK_MODE_Autoneg_BIT,
			 cmd->link_modes.advertising, bmcr & BMCR_ANENABLE);

	if (bmcr & BMCR_ANENABLE)
		cmd->base.autoneg = AUTONEG_ENABLE;
	else
		cmd->base.autoneg = AUTONEG_DISABLE;

	advert = r8152_mdio_read(tp, MII_ADVERTISE);
	linkmode_mod_bit(ETHTOOL_LINK_MODE_10baseT_Half_BIT,
			 cmd->link_modes.advertising,
			 advert & ADVERTISE_10HALF);
	linkmode_mod_bit(ETHTOOL_LINK_MODE_10baseT_Full_BIT,
			 cmd->link_modes.advertising,
			 advert & ADVERTISE_10FULL);
	linkmode_mod_bit(ETHTOOL_LINK_MODE_100baseT_Half_BIT,
			 cmd->link_modes.advertising,
			 advert & ADVERTISE_100HALF);
	linkmode_mod_bit(ETHTOOL_LINK_MODE_100baseT_Full_BIT,
			 cmd->link_modes.advertising,
			 advert & ADVERTISE_100FULL);
	linkmode_mod_bit(ETHTOOL_LINK_MODE_Pause_BIT,
			 cmd->link_modes.advertising,
			 advert & ADVERTISE_PAUSE_CAP);
	linkmode_mod_bit(ETHTOOL_LINK_MODE_Asym_Pause_BIT,
			 cmd->link_modes.advertising,
			 advert & ADVERTISE_PAUSE_ASYM);

	if (tp->mii.supports_gmii) {
		u16 ctrl1000 = r8152_mdio_read(tp, MII_CTRL1000);

		linkmode_mod_bit(ETHTOOL_LINK_MODE_1000baseT_Half_BIT,
				 cmd->link_modes.advertising,
				 ctrl1000 & ADVERTISE_1000HALF);
		linkmode_mod_bit(ETHTOOL_LINK_MODE_1000baseT_Full_BIT,
				 cmd->link_modes.advertising,
				 ctrl1000 & ADVERTISE_1000FULL);
	}

	if (tp->support_2500full) {
		linkmode_mod_bit(ETHTOOL_LINK_MODE_2500baseT_Full_BIT,
				 cmd->link_modes.advertising,
				 ocp_reg_read(tp, OCP_10GBT_CTRL) & MDIO_AN_10GBT_CTRL_ADV2_5G);
	}

	if (bmsr & BMSR_ANEGCOMPLETE) {
		advert = r8152_mdio_read(tp, MII_LPA);

		linkmode_mod_bit(ETHTOOL_LINK_MODE_Autoneg_BIT,
				 cmd->link_modes.lp_advertising,
				 advert & LPA_LPACK);
		linkmode_mod_bit(ETHTOOL_LINK_MODE_10baseT_Half_BIT,
				 cmd->link_modes.lp_advertising,
				 advert & ADVERTISE_10HALF);
		linkmode_mod_bit(ETHTOOL_LINK_MODE_10baseT_Full_BIT,
				 cmd->link_modes.lp_advertising,
				 advert & ADVERTISE_10FULL);
		linkmode_mod_bit(ETHTOOL_LINK_MODE_100baseT_Half_BIT,
				 cmd->link_modes.lp_advertising,
				 advert & ADVERTISE_100HALF);
		linkmode_mod_bit(ETHTOOL_LINK_MODE_100baseT_Full_BIT,
				 cmd->link_modes.lp_advertising,
				 advert & ADVERTISE_100FULL);

		if (tp->mii.supports_gmii) {
			u16 stat1000 = r8152_mdio_read(tp, MII_STAT1000);

			linkmode_mod_bit(ETHTOOL_LINK_MODE_1000baseT_Half_BIT,
					 cmd->link_modes.lp_advertising,
					 stat1000 & LPA_1000HALF);
			linkmode_mod_bit(ETHTOOL_LINK_MODE_1000baseT_Full_BIT,
					 cmd->link_modes.lp_advertising,
					 stat1000 & LPA_1000FULL);
		}

		if (tp->support_2500full) {
			u16 data = ocp_reg_read(tp, OCP_10GBT_STAT);

			linkmode_mod_bit(ETHTOOL_LINK_MODE_2500baseT_Full_BIT,
					 cmd->link_modes.lp_advertising,
					 data & MDIO_AN_10GBT_STAT_LP2_5G);
		}
	}

	if (netif_running(netdev) && netif_carrier_ok(netdev)) {
		u16 speed = rtl8152_get_speed(tp);

		if (speed & _100bps)
			cmd->base.speed = SPEED_100;
		else if (speed & _10bps)
			cmd->base.speed = SPEED_10;
		else if (tp->mii.supports_gmii && (speed & _1000bps))
			cmd->base.speed = SPEED_1000;
		else if (tp->support_2500full && (speed & _2500bps))
			cmd->base.speed = SPEED_2500;

		cmd->base.duplex = (speed & FULL_DUP) ? DUPLEX_FULL :
							DUPLEX_HALF;
	} else {
		cmd->base.speed = SPEED_UNKNOWN;
		cmd->base.duplex = DUPLEX_UNKNOWN;
	}

	mutex_unlock(&tp->control);

out2:
	usb_autopm_put_interface(tp->intf);
out1:
	return ret;
}

static int rtl8152_set_link_ksettings(struct net_device *dev,
				      const struct ethtool_link_ksettings *cmd)
{
	struct r8152 *tp = netdev_priv(dev);
	u32 advertising = 0;
	int ret;

	ret = usb_autopm_get_interface(tp->intf);
	if (ret < 0)
		goto out;

	if (test_bit(ETHTOOL_LINK_MODE_10baseT_Half_BIT,
		     cmd->link_modes.advertising))
		advertising |= RTL_ADVERTISED_10_HALF;

	if (test_bit(ETHTOOL_LINK_MODE_10baseT_Full_BIT,
		     cmd->link_modes.advertising))
		advertising |= RTL_ADVERTISED_10_FULL;

	if (test_bit(ETHTOOL_LINK_MODE_100baseT_Half_BIT,
		     cmd->link_modes.advertising))
		advertising |= RTL_ADVERTISED_100_HALF;

	if (test_bit(ETHTOOL_LINK_MODE_100baseT_Full_BIT,
		     cmd->link_modes.advertising))
		advertising |= RTL_ADVERTISED_100_FULL;

	if (test_bit(ETHTOOL_LINK_MODE_1000baseT_Half_BIT,
		     cmd->link_modes.advertising))
		advertising |= RTL_ADVERTISED_1000_HALF;

	if (test_bit(ETHTOOL_LINK_MODE_1000baseT_Full_BIT,
		     cmd->link_modes.advertising))
		advertising |= RTL_ADVERTISED_1000_FULL;

	if (test_bit(ETHTOOL_LINK_MODE_2500baseT_Full_BIT,
		     cmd->link_modes.advertising))
		advertising |= RTL_ADVERTISED_2500_FULL;

	mutex_lock(&tp->control);

	ret = rtl8152_set_speed(tp, cmd->base.autoneg, cmd->base.speed,
				cmd->base.duplex, advertising);
	if (!ret) {
		tp->autoneg = cmd->base.autoneg;
		tp->speed = cmd->base.speed;
		tp->duplex = cmd->base.duplex;
		tp->advertising = advertising;
	}

	mutex_unlock(&tp->control);

	usb_autopm_put_interface(tp->intf);

out:
	return ret;
}
#endif /* LINUX_VERSION_CODE >= KERNEL_VERSION(4,6,0) */

static const char rtl8152_gstrings[][ETH_GSTRING_LEN] = {
	"tx_packets",
	"rx_packets",
	"tx_errors",
	"rx_errors",
	"rx_missed",
	"align_errors",
	"tx_single_collisions",
	"tx_multi_collisions",
	"rx_unicast",
	"rx_broadcast",
	"rx_multicast",
	"tx_aborted",
	"tx_underrun",
};

#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,33)
static int rtl8152_get_sset_count(struct net_device *dev)
{
	return ARRAY_SIZE(rtl8152_gstrings);
}
#else
static int rtl8152_get_sset_count(struct net_device *dev, int sset)
{
	switch (sset) {
	case ETH_SS_STATS:
		return ARRAY_SIZE(rtl8152_gstrings);
	default:
		return -EOPNOTSUPP;
	}
}
#endif

static void rtl8152_get_ethtool_stats(struct net_device *dev,
				      struct ethtool_stats *stats, u64 *data)
{
	struct r8152 *tp = netdev_priv(dev);
	struct tally_counter tally;

	if (usb_autopm_get_interface(tp->intf) < 0)
		return;

	if (mutex_lock_interruptible(&tp->control) < 0) {
		usb_autopm_put_interface(tp->intf);
		return;
	}

	generic_ocp_read(tp, PLA_TALLYCNT, sizeof(tally), &tally, MCU_TYPE_PLA);

	mutex_unlock(&tp->control);

	usb_autopm_put_interface(tp->intf);

	data[0] = le64_to_cpu(tally.tx_packets);
	data[1] = le64_to_cpu(tally.rx_packets);
	data[2] = le64_to_cpu(tally.tx_errors);
	data[3] = le32_to_cpu(tally.rx_errors);
	data[4] = le16_to_cpu(tally.rx_missed);
	data[5] = le16_to_cpu(tally.align_errors);
	data[6] = le32_to_cpu(tally.tx_one_collision);
	data[7] = le32_to_cpu(tally.tx_multi_collision);
	data[8] = le64_to_cpu(tally.rx_unicast);
	data[9] = le64_to_cpu(tally.rx_broadcast);
	data[10] = le32_to_cpu(tally.rx_multicast);
	data[11] = le16_to_cpu(tally.tx_aborted);
	data[12] = le16_to_cpu(tally.tx_underrun);
}

static void rtl8152_get_strings(struct net_device *dev, u32 stringset, u8 *data)
{
	switch (stringset) {
	case ETH_SS_STATS:
		memcpy(data, rtl8152_gstrings, sizeof(rtl8152_gstrings));
		break;
	}
}

#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,6,0)
static int r8152_get_eee(struct r8152 *tp, struct ethtool_eee *eee)
{
	u32 lp, adv, supported = 0;
	u16 val;

	val = r8152_mmd_read(tp, MDIO_MMD_PCS, MDIO_PCS_EEE_ABLE);
	supported = mmd_eee_cap_to_ethtool_sup_t(val);

	val = r8152_mmd_read(tp, MDIO_MMD_AN, MDIO_AN_EEE_ADV);
	adv = mmd_eee_adv_to_ethtool_adv_t(val);

	val = r8152_mmd_read(tp, MDIO_MMD_AN, MDIO_AN_EEE_LPABLE);
	lp = mmd_eee_adv_to_ethtool_adv_t(val);

	eee->eee_enabled = tp->eee_en;
	eee->eee_active = !!(supported & adv & lp);
	eee->supported = supported;
	eee->advertised = tp->eee_adv;
	eee->lp_advertised = lp;

	return 0;
}

static int r8152_set_eee(struct r8152 *tp, struct ethtool_eee *eee)
{
	u16 val = ethtool_adv_to_mmd_eee_adv_t(eee->advertised);

	tp->eee_en = eee->eee_enabled;
	tp->eee_adv = val;

	rtl_eee_enable(tp, tp->eee_en);

	return 0;
}

static int r8153_get_eee(struct r8152 *tp, struct ethtool_eee *eee)
{
	u32 lp, adv, supported = 0;
	u16 val;

	val = ocp_reg_read(tp, OCP_EEE_ABLE);
	supported = mmd_eee_cap_to_ethtool_sup_t(val);

	val = ocp_reg_read(tp, OCP_EEE_ADV);
	adv = mmd_eee_adv_to_ethtool_adv_t(val);

	val = ocp_reg_read(tp, OCP_EEE_LPABLE);
	lp = mmd_eee_adv_to_ethtool_adv_t(val);

	eee->eee_enabled = tp->eee_en;
	eee->eee_active = !!(supported & adv & lp);
	eee->supported = supported;
	eee->advertised = tp->eee_adv;
	eee->lp_advertised = lp;

	return 0;
}

static int
rtl_ethtool_get_eee(struct net_device *net, struct ethtool_eee *edata)
{
	struct r8152 *tp = netdev_priv(net);
	int ret;

	if (!tp->rtl_ops.eee_get) {
		ret = -EOPNOTSUPP;
		goto out;
	}

	ret = usb_autopm_get_interface(tp->intf);
	if (ret < 0)
		goto out;

	mutex_lock(&tp->control);

	ret = tp->rtl_ops.eee_get(tp, edata);

	mutex_unlock(&tp->control);

	usb_autopm_put_interface(tp->intf);

out:
	return ret;
}

static int
rtl_ethtool_set_eee(struct net_device *net, struct ethtool_eee *edata)
{
	struct r8152 *tp = netdev_priv(net);
	int ret;

	if (!tp->rtl_ops.eee_set) {
		ret = -EOPNOTSUPP;
		goto out;
	}

	ret = usb_autopm_get_interface(tp->intf);
	if (ret < 0)
		goto out;

	mutex_lock(&tp->control);

	ret = tp->rtl_ops.eee_set(tp, edata);
	if (!ret)
		ret = rtl_nway_restart(tp);

	mutex_unlock(&tp->control);

	usb_autopm_put_interface(tp->intf);

out:
	return ret;
}
#endif /* LINUX_VERSION_CODE >= KERNEL_VERSION(3,6,0) */

static int rtl8152_nway_reset(struct net_device *dev)
{
	struct r8152 *tp = netdev_priv(dev);
	int ret;

	ret = usb_autopm_get_interface(tp->intf);
	if (ret < 0)
		goto out;

	mutex_lock(&tp->control);

	ret = rtl_nway_restart(tp);

	mutex_unlock(&tp->control);

	usb_autopm_put_interface(tp->intf);

out:
	return ret;
}

static int rtl8152_get_coalesce(struct net_device *netdev,
#if LINUX_VERSION_CODE < KERNEL_VERSION(5,15,0)
				struct ethtool_coalesce *coalesce)
#else
				struct ethtool_coalesce *coalesce,
				struct kernel_ethtool_coalesce *kernel_coal,
				struct netlink_ext_ack *extack)
#endif /* LINUX_VERSION_CODE < KERNEL_VERSION(5,15,0) */
{
	struct r8152 *tp = netdev_priv(netdev);

	switch (tp->version) {
	case RTL_VER_01:
	case RTL_VER_02:
	case RTL_VER_07:
		return -EOPNOTSUPP;
	default:
		break;
	}

	coalesce->rx_coalesce_usecs = tp->coalesce / 1000;

	return 0;
}

static int rtl8152_set_coalesce(struct net_device *netdev,
#if LINUX_VERSION_CODE < KERNEL_VERSION(5,15,0)
				struct ethtool_coalesce *coalesce)
#else
				struct ethtool_coalesce *coalesce,
				struct kernel_ethtool_coalesce *kernel_coal,
				struct netlink_ext_ack *extack)
#endif /* LINUX_VERSION_CODE < KERNEL_VERSION(5,15,0) */
{
	struct r8152 *tp = netdev_priv(netdev);
	u32 rx_coalesce_nsecs;
	int ret;

	switch (tp->version) {
	case RTL_VER_01:
	case RTL_VER_02:
	case RTL_VER_07:
	case RTL_TEST_01: /* fix me */
		return -EOPNOTSUPP;
	default:
		break;
	}

	rx_coalesce_nsecs = coalesce->rx_coalesce_usecs * 1000;

	if (rx_coalesce_nsecs > COALESCE_SLOW)
		return -EINVAL;

	ret = usb_autopm_get_interface(tp->intf);
	if (ret < 0)
		return ret;

	mutex_lock(&tp->control);

	if (tp->coalesce != rx_coalesce_nsecs) {
		tp->coalesce = rx_coalesce_nsecs;

		if (netif_running(netdev) && netif_carrier_ok(netdev)) {
			netif_stop_queue(netdev);
			napi_disable(&tp->napi);
			tp->rtl_ops.disable(tp);
			tp->rtl_ops.enable(tp);
			rtl_start_rx(tp);
			napi_enable(&tp->napi);
			rtl8152_set_rx_mode(netdev);
			netif_wake_queue(netdev);
		}
	}

	mutex_unlock(&tp->control);

	usb_autopm_put_interface(tp->intf);

	return ret;
}

static int rtl8152_ethtool_begin(struct net_device *netdev)
{
	struct r8152 *tp = netdev_priv(netdev);

	if (unlikely(tp->rtk_enable_diag))
		return -EBUSY;

	return 0;
}

#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,18,0)
static int rtl8152_get_tunable(struct net_device *netdev,
			       const struct ethtool_tunable *tunable, void *d)
{
	struct r8152 *tp = netdev_priv(netdev);

	switch (tunable->id) {
	case ETHTOOL_RX_COPYBREAK:
		*(u32 *)d = tp->rx_copybreak;
		break;
	default:
		return -EOPNOTSUPP;
	}

	return 0;
}

static int rtl8152_set_tunable(struct net_device *netdev,
			       const struct ethtool_tunable *tunable,
			       const void *d)
{
	struct r8152 *tp = netdev_priv(netdev);
	u32 val;

	switch (tunable->id) {
	case ETHTOOL_RX_COPYBREAK:
		val = *(u32 *)d;
		if (val < ETH_ZLEN) {
			netif_err(tp, rx_err, netdev,
				  "Invalid rx copy break value\n");
			return -EINVAL;
		}

		if (tp->rx_copybreak != val) {
			if (netdev->flags & IFF_UP) {
				mutex_lock(&tp->control);
				napi_disable(&tp->napi);
				tp->rx_copybreak = val;
				napi_enable(&tp->napi);
				mutex_unlock(&tp->control);
			} else {
				tp->rx_copybreak = val;
			}
		}
		break;
	default:
		return -EOPNOTSUPP;
	}

	return 0;
}
#endif /* LINUX_VERSION_CODE >= KERNEL_VERSION(3,18,0) */

static void rtl8152_get_ringparam(struct net_device *netdev,
#if LINUX_VERSION_CODE < KERNEL_VERSION(5,17,0)
				  struct ethtool_ringparam *ring)
#else
				  struct ethtool_ringparam *ring,
				  struct kernel_ethtool_ringparam *kernel_ring,
				  struct netlink_ext_ack *extack)
#endif /* LINUX_VERSION_CODE < KERNEL_VERSION(5,15,0) */
{
	struct r8152 *tp = netdev_priv(netdev);

	ring->rx_max_pending = RTL8152_RX_MAX_PENDING;
	ring->rx_pending = tp->rx_pending;
}

static int rtl8152_set_ringparam(struct net_device *netdev,
#if LINUX_VERSION_CODE < KERNEL_VERSION(5,17,0)
				 struct ethtool_ringparam *ring)
#else
				 struct ethtool_ringparam *ring,
				 struct kernel_ethtool_ringparam *kernel_ring,
				 struct netlink_ext_ack *extack)
#endif /* LINUX_VERSION_CODE < KERNEL_VERSION(5,15,0) */
{
	struct r8152 *tp = netdev_priv(netdev);

	if (ring->rx_pending < (RTL8152_MAX_RX * 2))
		return -EINVAL;

	if (tp->rx_pending != ring->rx_pending) {
		if (netdev->flags & IFF_UP) {
			mutex_lock(&tp->control);
			napi_disable(&tp->napi);
			tp->rx_pending = ring->rx_pending;
			napi_enable(&tp->napi);
			mutex_unlock(&tp->control);
		} else {
			tp->rx_pending = ring->rx_pending;
		}
	}

	return 0;
}

static void rtl8152_get_pauseparam(struct net_device *netdev, struct ethtool_pauseparam *pause)
{
	struct r8152 *tp = netdev_priv(netdev);
	u16 bmcr, lcladv, rmtadv;
	u8 cap;

	if (usb_autopm_get_interface(tp->intf) < 0)
		return;

	mutex_lock(&tp->control);

	bmcr = r8152_mdio_read(tp, MII_BMCR);
	lcladv = r8152_mdio_read(tp, MII_ADVERTISE);
	rmtadv = r8152_mdio_read(tp, MII_LPA);

	mutex_unlock(&tp->control);

	usb_autopm_put_interface(tp->intf);

	if (!(bmcr & BMCR_ANENABLE)) {
		pause->autoneg = 0;
		pause->rx_pause = 0;
		pause->tx_pause = 0;
		return;
	}

	pause->autoneg = 1;

	cap = mii_resolve_flowctrl_fdx(lcladv, rmtadv);

	if (cap & FLOW_CTRL_RX)
		pause->rx_pause = 1;

	if (cap & FLOW_CTRL_TX)
		pause->tx_pause = 1;
}

static int rtl8152_set_pauseparam(struct net_device *netdev, struct ethtool_pauseparam *pause)
{
	struct r8152 *tp = netdev_priv(netdev);
	u16 old, new1;
	u8 cap = 0;
	int ret;

	ret = usb_autopm_get_interface(tp->intf);
	if (ret < 0)
		return ret;

	mutex_lock(&tp->control);

	if (pause->autoneg && !(r8152_mdio_read(tp, MII_BMCR) & BMCR_ANENABLE)) {
		ret = -EINVAL;
		goto out;
	}

	if (pause->rx_pause)
		cap |= FLOW_CTRL_RX;

	if (pause->tx_pause)
		cap |= FLOW_CTRL_TX;

	old = r8152_mdio_read(tp, MII_ADVERTISE);
	new1 = (old & ~(ADVERTISE_PAUSE_CAP | ADVERTISE_PAUSE_ASYM)) | mii_advertise_flowctrl(cap);
	if (old != new1)
		r8152_mdio_write(tp, MII_ADVERTISE, new1);

	if (new1 & (ADVERTISE_PAUSE_CAP | ADVERTISE_PAUSE_ASYM))
		tp->ups_info.flow_control = true;
	else
		tp->ups_info.flow_control = false;

out:
	mutex_unlock(&tp->control);
	usb_autopm_put_interface(tp->intf);

	return ret;
}

static const struct ethtool_ops ops = {
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,7,0)
	.supported_coalesce_params = ETHTOOL_COALESCE_USECS,
#endif /* LINUX_VERSION_CODE >= KERNEL_VERSION(5,7,0) */
	.get_drvinfo = rtl8152_get_drvinfo,
#if LINUX_VERSION_CODE < KERNEL_VERSION(4,20,0)
	.get_settings = rtl8152_get_settings,
	.set_settings = rtl8152_set_settings,
#endif /* LINUX_VERSION_CODE < KERNEL_VERSION(4,20,0) */
	.get_link = ethtool_op_get_link,
	.nway_reset = rtl8152_nway_reset,
	.get_msglevel = rtl8152_get_msglevel,
	.set_msglevel = rtl8152_set_msglevel,
	.get_wol = rtl8152_get_wol,
	.set_wol = rtl8152_set_wol,
	.get_strings = rtl8152_get_strings,
	.get_sset_count = rtl8152_get_sset_count,
	.get_ethtool_stats = rtl8152_get_ethtool_stats,
#if LINUX_VERSION_CODE < KERNEL_VERSION(3,3,0)
	.get_tx_csum = ethtool_op_get_tx_csum,
	.set_tx_csum = ethtool_op_set_tx_csum,
	.get_sg = ethtool_op_get_sg,
	.set_sg = ethtool_op_set_sg,
#ifdef NETIF_F_TSO
	.get_tso = ethtool_op_get_tso,
	.set_tso = ethtool_op_set_tso,
#endif
#endif /* LINUX_VERSION_CODE < KERNEL_VERSION(3,3,0) */
	.get_coalesce = rtl8152_get_coalesce,
	.set_coalesce = rtl8152_set_coalesce,
#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,6,0)
	.get_eee = rtl_ethtool_get_eee,
	.set_eee = rtl_ethtool_set_eee,
#endif /* LINUX_VERSION_CODE >= KERNEL_VERSION(3,6,0) */
#if LINUX_VERSION_CODE >= KERNEL_VERSION(4,6,0)
	.get_link_ksettings = rtl8152_get_link_ksettings,
	.set_link_ksettings = rtl8152_set_link_ksettings,
#endif /* LINUX_VERSION_CODE >= KERNEL_VERSION(4,6,0) */
	.begin = rtl8152_ethtool_begin,
#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,18,0)
	.get_tunable = rtl8152_get_tunable,
	.set_tunable = rtl8152_set_tunable,
#endif /* LINUX_VERSION_CODE >= KERNEL_VERSION(3,18,0) */
	.get_ringparam = rtl8152_get_ringparam,
	.set_ringparam = rtl8152_set_ringparam,
	.get_pauseparam = rtl8152_get_pauseparam,
	.set_pauseparam = rtl8152_set_pauseparam,
};

static int rtltool_ioctl(struct r8152 *tp, struct ifreq *ifr)
{
	struct net_device *netdev = tp->netdev;
	struct rtltool_cmd my_cmd, *myptr;
	struct usb_device_info *uinfo;
	struct usb_device *udev;
	__le32	ocp_data;
	void	*buffer;
	int	ret;

	myptr = (struct rtltool_cmd *)ifr->ifr_data;
	if (copy_from_user(&my_cmd, myptr, sizeof(my_cmd)))
		return -EFAULT;

	ret = 0;

	switch (my_cmd.cmd) {
	case RTLTOOL_PLA_OCP_READ_DWORD:
		pla_ocp_read(tp, (u16)my_cmd.offset, sizeof(ocp_data),
			     &ocp_data);
		my_cmd.data = __le32_to_cpu(ocp_data);

		if (copy_to_user(myptr, &my_cmd, sizeof(my_cmd))) {
			ret = -EFAULT;
			break;
		}
		break;

	case RTLTOOL_PLA_OCP_WRITE_DWORD:
		if (!tp->rtk_enable_diag && net_ratelimit())
			netif_warn(tp, drv, netdev,
				   "rtk diag isn't enable\n");

		ocp_data = __cpu_to_le32(my_cmd.data);
		pla_ocp_write(tp, (u16)my_cmd.offset, (u16)my_cmd.byteen,
			      sizeof(ocp_data), &ocp_data);
		break;

	case RTLTOOL_USB_OCP_READ_DWORD:
		usb_ocp_read(tp, (u16)my_cmd.offset, sizeof(ocp_data),
			     &ocp_data);
		my_cmd.data = __le32_to_cpu(ocp_data);

		if (copy_to_user(myptr, &my_cmd, sizeof(my_cmd))) {
			ret = -EFAULT;
			break;
		}
		break;


	case RTLTOOL_USB_OCP_WRITE_DWORD:
		if (!tp->rtk_enable_diag && net_ratelimit())
			netif_warn(tp, drv, netdev,
				   "rtk diag isn't enable\n");

		ocp_data = __cpu_to_le32(my_cmd.data);
		usb_ocp_write(tp, (u16)my_cmd.offset, (u16)my_cmd.byteen,
			      sizeof(ocp_data), &ocp_data);
		break;

	case RTLTOOL_PLA_OCP_READ:
		buffer = kmalloc(my_cmd.data, GFP_KERNEL);
		if (!buffer) {
			ret = -ENOMEM;
			break;
		}

		pla_ocp_read(tp, (u16)my_cmd.offset, my_cmd.data, buffer);

		if (copy_to_user(my_cmd.buf, buffer, my_cmd.data))
			ret = -EFAULT;

		kfree(buffer);
		break;

	case RTLTOOL_PLA_OCP_WRITE:
		if (!tp->rtk_enable_diag && net_ratelimit())
			netif_warn(tp, drv, netdev,
				   "rtk diag isn't enable\n");

		buffer = kmalloc(my_cmd.data, GFP_KERNEL);
		if (!buffer) {
			ret = -ENOMEM;
			break;
		}

		if (copy_from_user(buffer, my_cmd.buf, my_cmd.data)) {
			ret = -EFAULT;
			kfree(buffer);
			break;
		}

		pla_ocp_write(tp, (u16)my_cmd.offset, (u16)my_cmd.byteen,
			      my_cmd.data, buffer);
		kfree(buffer);
		break;

	case RTLTOOL_USB_OCP_READ:
		buffer = kmalloc(my_cmd.data, GFP_KERNEL);
		if (!buffer) {
			ret = -ENOMEM;
			break;
		}

		usb_ocp_read(tp, (u16)my_cmd.offset, my_cmd.data, buffer);

		if (copy_to_user(my_cmd.buf, buffer, my_cmd.data))
			ret = -EFAULT;

		kfree(buffer);
		break;

	case RTLTOOL_USB_OCP_WRITE:
		if (!tp->rtk_enable_diag && net_ratelimit())
			netif_warn(tp, drv, netdev,
				   "rtk diag isn't enable\n");

		buffer = kmalloc(my_cmd.data, GFP_KERNEL);
		if (!buffer) {
			ret = -ENOMEM;
			break;
		}

		if (copy_from_user(buffer, my_cmd.buf, my_cmd.data)) {
			ret = -EFAULT;
			kfree(buffer);
			break;
		}

		usb_ocp_write(tp, (u16)my_cmd.offset, (u16)my_cmd.byteen,
			      my_cmd.data, buffer);
		kfree(buffer);
		break;

	case RTLTOOL_USB_INFO:
		uinfo = (struct usb_device_info *)&my_cmd.nic_info;
		udev = tp->udev;
		uinfo->idVendor = __le16_to_cpu(udev->descriptor.idVendor);
		uinfo->idProduct = __le16_to_cpu(udev->descriptor.idProduct);
		uinfo->bcdDevice = __le16_to_cpu(udev->descriptor.bcdDevice);
		strlcpy(uinfo->devpath, udev->devpath, sizeof(udev->devpath));
		pla_ocp_read(tp, PLA_IDR, sizeof(uinfo->dev_addr),
			     uinfo->dev_addr);

		if (copy_to_user(myptr, &my_cmd, sizeof(my_cmd)))
			ret = -EFAULT;

		break;

	case RTL_ENABLE_USB_DIAG:
		ret = usb_autopm_get_interface(tp->intf);
		if (ret < 0)
			break;

		mutex_lock(&tp->control);
		tp->rtk_enable_diag++;
		netif_info(tp, drv, netdev, "enable rtk diag %d\n",
			   tp->rtk_enable_diag);
		break;

	case RTL_DISABLE_USB_DIAG:
		if (!tp->rtk_enable_diag) {
			netif_err(tp, drv, netdev,
				  "Invalid using rtk diag\n");
			ret = -EPERM;
			break;
		}

		rtk_disable_diag(tp);
		break;

	default:
		ret = -EOPNOTSUPP;
		break;
	}

	return ret;
}

#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,15,0)
static int rtl8152_siocdevprivate(struct net_device *netdev, struct ifreq *rq,
				  void __user *data, int cmd)
{
	struct r8152 *tp = netdev_priv(netdev);
	int ret;

	if (test_bit(RTL8152_UNPLUG, &tp->flags))
		return -ENODEV;

	ret = usb_autopm_get_interface(tp->intf);
	if (ret < 0)
		goto out;

	switch (cmd) {
	case SIOCDEVPRIVATE:
		if (!capable(CAP_NET_ADMIN)) {
			ret = -EPERM;
			break;
		}
		ret = rtltool_ioctl(tp, rq);
		break;

	default:
		ret = -EOPNOTSUPP;
	}

	usb_autopm_put_interface(tp->intf);

out:
	return ret;
}
#endif /* LINUX_VERSION_CODE >= KERNEL_VERSION(5,15,0) */

static int rtl8152_ioctl(struct net_device *netdev, struct ifreq *rq, int cmd)
{
	struct r8152 *tp = netdev_priv(netdev);
	struct mii_ioctl_data *data = if_mii(rq);
	int ret;

	if (test_bit(RTL8152_UNPLUG, &tp->flags))
		return -ENODEV;

	ret = usb_autopm_get_interface(tp->intf);
	if (ret < 0)
		goto out;

	switch (cmd) {
	case SIOCGMIIPHY:
		data->phy_id = R8152_PHY_ID; /* Internal PHY */
		break;

	case SIOCGMIIREG:
		if (unlikely(tp->rtk_enable_diag)) {
			ret = -EBUSY;
			break;
		}

		mutex_lock(&tp->control);
		data->val_out = r8152_mdio_read(tp, data->reg_num);
		mutex_unlock(&tp->control);
		break;

	case SIOCSMIIREG:
		if (!capable(CAP_NET_ADMIN)) {
			ret = -EPERM;
			break;
		}

		if (unlikely(tp->rtk_enable_diag)) {
			ret = -EBUSY;
			break;
		}

		mutex_lock(&tp->control);
		r8152_mdio_write(tp, data->reg_num, data->val_in);
		mutex_unlock(&tp->control);
		break;

#if LINUX_VERSION_CODE < KERNEL_VERSION(5,15,0)
	case SIOCDEVPRIVATE:
		if (!capable(CAP_NET_ADMIN)) {
			ret = -EPERM;
			break;
		}
		ret = rtltool_ioctl(tp, rq);
		break;
#endif /* LINUX_VERSION_CODE < KERNEL_VERSION(5,15,0) */

	default:
		ret = -EOPNOTSUPP;
	}

	usb_autopm_put_interface(tp->intf);

out:
	return ret;
}

static int rtl8152_change_mtu(struct net_device *dev, int new_mtu)
{
	struct r8152 *tp = netdev_priv(dev);
	int ret;
#if LINUX_VERSION_CODE < KERNEL_VERSION(4,10,0)
	u32 max_mtu;
#endif /* LINUX_VERSION_CODE < KERNEL_VERSION(4,10,0) */

	switch (tp->version) {
	case RTL_VER_01:
	case RTL_VER_02:
	case RTL_VER_07:
#if LINUX_VERSION_CODE < KERNEL_VERSION(4,10,0)
		return eth_change_mtu(dev, new_mtu);
#else
		dev->mtu = new_mtu;
		return 0;
#endif
	default:
		break;
	}

#if LINUX_VERSION_CODE < KERNEL_VERSION(4,10,0)
	switch (tp->version) {
	case RTL_VER_03:
	case RTL_VER_04:
	case RTL_VER_05:
	case RTL_VER_06:
	case RTL_VER_08:
	case RTL_VER_09:
	case RTL_VER_14:
		max_mtu = size_to_mtu(9 * 1024);
		break;
	case RTL_VER_10:
	case RTL_VER_11:
		max_mtu = size_to_mtu(15 * 1024);
		break;
	case RTL_VER_12:
	case RTL_VER_13:
	case RTL_VER_15:
		max_mtu = size_to_mtu(16 * 1024);
		break;
	case RTL_VER_01:
	case RTL_VER_02:
	case RTL_VER_07:
	default:
		max_mtu = ETH_DATA_LEN;
		break;
	}

	if (new_mtu < 68 || new_mtu > max_mtu)
		return -EINVAL;
#endif /* LINUX_VERSION_CODE < KERNEL_VERSION(4,10,0) */

	ret = usb_autopm_get_interface(tp->intf);
	if (ret < 0)
		return ret;

	mutex_lock(&tp->control);

	dev->mtu = new_mtu;

	if (netif_running(dev)) {
		if (tp->rtl_ops.change_mtu)
			tp->rtl_ops.change_mtu(tp);

		if (netif_carrier_ok(dev)) {
			netif_stop_queue(dev);
			napi_disable(&tp->napi);
			tasklet_disable(&tp->tx_tl);
			tp->rtl_ops.disable(tp);
			tp->rtl_ops.enable(tp);
			rtl_start_rx(tp);
			tasklet_enable(&tp->tx_tl);
			napi_enable(&tp->napi);
			rtl8152_set_rx_mode(dev);
			netif_wake_queue(dev);
		}
	}

	mutex_unlock(&tp->control);

	usb_autopm_put_interface(tp->intf);

	return ret;
}

#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,29)
static const struct net_device_ops rtl8152_netdev_ops = {
	.ndo_open		= rtl8152_open,
	.ndo_stop		= rtl8152_close,
#if LINUX_VERSION_CODE < KERNEL_VERSION(5,15,0)
	.ndo_do_ioctl		= rtl8152_ioctl,
#else
	.ndo_siocdevprivate	= rtl8152_siocdevprivate,
	.ndo_eth_ioctl		= rtl8152_ioctl,
#endif /* LINUX_VERSION_CODE < KERNEL_VERSION(5,15,0) */
	.ndo_start_xmit		= rtl8152_start_xmit,
	.ndo_tx_timeout		= rtl8152_tx_timeout,
#if LINUX_VERSION_CODE < KERNEL_VERSION(3,0,0)
	.ndo_vlan_rx_register	= rtl8152_vlan_rx_register,
#else
	.ndo_set_features	= rtl8152_set_features,
#endif /* LINUX_VERSION_CODE < KERNEL_VERSION(3,0,0) */
	.ndo_set_rx_mode	= rtl8152_set_rx_mode,
	.ndo_set_mac_address	= rtl8152_set_mac_address,
	.ndo_change_mtu		= rtl8152_change_mtu,
	.ndo_validate_addr	= eth_validate_addr,
#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,18,4)
	.ndo_features_check	= rtl8152_features_check,
#endif /* LINUX_VERSION_CODE >= KERNEL_VERSION(3,18,4) */
};
#endif

static void rtl8152_unload(struct r8152 *tp)
{
	if (test_bit(RTL8152_UNPLUG, &tp->flags))
		return;

	r8152_power_cut_en(tp, false);
}

static void rtl8153_unload(struct r8152 *tp)
{
	if (test_bit(RTL8152_UNPLUG, &tp->flags))
		return;

	r8153_power_cut_en(tp, false);
}

static void rtl8153b_unload(struct r8152 *tp)
{
	if (test_bit(RTL8152_UNPLUG, &tp->flags))
		return;

	r8153b_power_cut_en(tp, false);
	rtl_set_dbg_info_state(tp, DGB_DRV_STATE_UNLOAD);
}

static int rtl_ops_init(struct r8152 *tp)
{
	struct rtl_ops *ops = &tp->rtl_ops;
	int ret = 0;

	switch (tp->version) {
	case RTL_VER_01:
	case RTL_VER_02:
	case RTL_VER_07:
		ops->init		= r8152b_init;
		ops->enable		= rtl8152_enable;
		ops->disable		= rtl8152_disable;
		ops->up			= rtl8152_up;
		ops->down		= rtl8152_down;
		ops->unload		= rtl8152_unload;
#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,6,0)
		ops->eee_get		= r8152_get_eee;
		ops->eee_set		= r8152_set_eee;
#endif /* LINUX_VERSION_CODE >= KERNEL_VERSION(3,6,0) */
		ops->in_nway		= rtl8152_in_nway;
		ops->hw_phy_cfg		= r8152b_hw_phy_cfg;
		ops->autosuspend_en	= rtl_runtime_suspend_enable;
		tp->rx_buf_sz		= 16 * 1024;
		tp->eee_en		= true;
		tp->eee_adv		= MDIO_EEE_100TX;
		break;

	case RTL_VER_03:
	case RTL_VER_04:
	case RTL_VER_05:
	case RTL_VER_06:
		ops->init		= r8153_init;
		ops->enable		= rtl8153_enable;
		ops->disable		= rtl8153_disable;
		ops->up			= rtl8153_up;
		ops->down		= rtl8153_down;
		ops->unload		= rtl8153_unload;
#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,6,0)
		ops->eee_get		= r8153_get_eee;
		ops->eee_set		= r8152_set_eee;
#endif /* LINUX_VERSION_CODE >= KERNEL_VERSION(3,6,0) */
		ops->in_nway		= rtl8153_in_nway;
		ops->hw_phy_cfg		= r8153_hw_phy_cfg;
		ops->autosuspend_en	= rtl8153_runtime_enable;
		ops->change_mtu		= rtl8153_change_mtu;
		if (tp->udev->speed < USB_SPEED_SUPER)
			tp->rx_buf_sz	= 16 * 1024;
		else
			tp->rx_buf_sz	= 32 * 1024;
		tp->eee_en		= true;
		tp->eee_adv		= MDIO_EEE_1000T | MDIO_EEE_100TX;
		break;

	case RTL_VER_08:
	case RTL_VER_09:
		ops->init		= r8153b_init;
		ops->enable		= rtl8153_enable;
		ops->disable		= rtl8153_disable;
		ops->up			= rtl8153b_up;
		ops->down		= rtl8153b_down;
		ops->unload		= rtl8153b_unload;
#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,6,0)
		ops->eee_get		= r8153_get_eee;
		ops->eee_set		= r8152_set_eee;
#endif /* LINUX_VERSION_CODE >= KERNEL_VERSION(3,6,0) */
		ops->in_nway		= rtl8153_in_nway;
		ops->hw_phy_cfg		= r8153b_hw_phy_cfg;
		ops->autosuspend_en	= rtl8153b_runtime_enable;
		ops->change_mtu		= rtl8153_change_mtu;
		tp->rx_buf_sz		= 32 * 1024;
		tp->eee_en		= true;
		tp->eee_adv		= MDIO_EEE_1000T | MDIO_EEE_100TX;
		break;

	case RTL_TEST_01:
		ops->init		= r8156_init;
		ops->enable		= rtl8156_enable;
		ops->disable		= rtl8153_disable;
		ops->up			= rtl8156_up;
		ops->down		= rtl8156_down;
		ops->unload		= rtl8153_unload;
//#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,6,0)
//		ops->eee_get		= r8156_get_eee;
//		ops->eee_set		= r8156_set_eee;
//#endif /* LINUX_VERSION_CODE >= KERNEL_VERSION(3,6,0) */
		ops->in_nway		= rtl8153_in_nway;
		ops->hw_phy_cfg		= r8156_hw_phy_cfg_test;
		ops->autosuspend_en	= rtl8156_runtime_enable;
		tp->rx_buf_sz		= 48 * 1024;
		tp->support_2500full	= 1;
		break;

	case RTL_VER_11:
		tp->eee_en		= true;
		tp->eee_adv		= MDIO_EEE_1000T | MDIO_EEE_100TX;
		fallthrough;
	case RTL_VER_10:
		ops->init		= r8156_init;
		ops->enable		= rtl8156_enable;
		ops->disable		= rtl8153_disable;
		ops->up			= rtl8156_up;
		ops->down		= rtl8156_down;
		ops->unload		= rtl8153_unload;
#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,6,0)
		ops->eee_get		= r8153_get_eee;
		ops->eee_set		= r8152_set_eee;
#endif /* LINUX_VERSION_CODE >= KERNEL_VERSION(3,6,0) */
		ops->in_nway		= rtl8153_in_nway;
		ops->hw_phy_cfg		= r8156_hw_phy_cfg;
		ops->autosuspend_en	= rtl8156_runtime_enable;
		ops->change_mtu		= rtl8156_change_mtu;
		tp->rx_buf_sz		= 48 * 1024;
		tp->support_2500full	= 1;
		break;

	case RTL_VER_12:
	case RTL_VER_13:
		tp->support_2500full	= 1;
		fallthrough;
	case RTL_VER_15:
		tp->eee_en		= true;
		tp->eee_adv		= MDIO_EEE_1000T | MDIO_EEE_100TX;
		ops->init		= r8156b_init;
		ops->enable		= rtl8156b_enable;
		ops->disable		= rtl8153_disable;
		ops->up			= rtl8156_up;
		ops->down		= rtl8156_down;
		ops->unload		= rtl8153_unload;
#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,6,0)
		ops->eee_get		= r8153_get_eee;
		ops->eee_set		= r8152_set_eee;
#endif /* LINUX_VERSION_CODE >= KERNEL_VERSION(3,6,0) */
		ops->in_nway		= rtl8153_in_nway;
		ops->hw_phy_cfg		= r8156b_hw_phy_cfg;
		ops->autosuspend_en	= rtl8156_runtime_enable;
		ops->change_mtu		= rtl8156_change_mtu;
		tp->rx_buf_sz		= 48 * 1024;
		break;

	case RTL_VER_14:
		ops->init		= r8153c_init;
		ops->enable		= rtl8153_enable;
		ops->disable		= rtl8153_disable;
		ops->up			= rtl8153c_up;
		ops->down		= rtl8153b_down;
		ops->unload		= rtl8153_unload;
#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,6,0)
		ops->eee_get		= r8153_get_eee;
		ops->eee_set		= r8152_set_eee;
#endif /* LINUX_VERSION_CODE >= KERNEL_VERSION(3,6,0) */
		ops->in_nway		= rtl8153_in_nway;
		ops->hw_phy_cfg		= r8153c_hw_phy_cfg;
		ops->autosuspend_en	= rtl8153c_runtime_enable;
		ops->change_mtu		= rtl8153c_change_mtu;
		tp->rx_buf_sz		= 32 * 1024;
		tp->eee_en		= true;
		tp->eee_adv		= MDIO_EEE_1000T | MDIO_EEE_100TX;
		break;

	default:
		ret = -ENODEV;
		dev_err(&tp->intf->dev, "Unknown Device\n");
		break;
	}

	return ret;
}

u8 rtl8152_get_version(struct usb_interface *intf)
{
	struct usb_device *udev = interface_to_usbdev(intf);
	u32 ocp_data = 0;
	__le32 *tmp;
	u8 version;
	int ret;

	tmp = kmalloc(sizeof(*tmp), GFP_KERNEL);
	if (!tmp)
		return 0;

	ret = usb_control_msg(udev, usb_rcvctrlpipe(udev, 0),
			      RTL8152_REQ_GET_REGS, RTL8152_REQT_READ,
			      PLA_TCR0, MCU_TYPE_PLA, tmp, sizeof(*tmp), 500);
	if (ret > 0)
		ocp_data = (__le32_to_cpu(*tmp) >> 16) & VERSION_MASK;

	kfree(tmp);

	switch (ocp_data) {
	case 0x4c00:
		version = RTL_VER_01;
		break;
	case 0x4c10:
		version = RTL_VER_02;
		break;
	case 0x5c00:
		version = RTL_VER_03;
		break;
	case 0x5c10:
		version = RTL_VER_04;
		break;
	case 0x5c20:
		version = RTL_VER_05;
		break;
	case 0x5c30:
		version = RTL_VER_06;
		break;
	case 0x4800:
		version = RTL_VER_07;
		break;
	case 0x6000:
		version = RTL_VER_08;
		break;
	case 0x6010:
		version = RTL_VER_09;
		break;
	case 0x7010:
		version = RTL_TEST_01;
		break;
	case 0x7020:
		version = RTL_VER_10;
		break;
	case 0x7030:
		version = RTL_VER_11;
		break;
	case 0x7400:
		version = RTL_VER_12;
		break;
	case 0x7410:
		version = RTL_VER_13;
		break;
	case 0x6400:
		version = RTL_VER_14;
		break;
	case 0x7420:
		version = RTL_VER_15;
		break;
	default:
		version = RTL_VER_UNKNOWN;
		dev_info(&intf->dev, "Unknown version 0x%04x\n", ocp_data);
		break;
	}

	dev_dbg(&intf->dev, "Detected version 0x%04x\n", version);

	return version;
}
EXPORT_SYMBOL_GPL(rtl8152_get_version);

#ifdef RTL8152_DEBUG

static ssize_t
ocp_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	struct net_device *netdev = to_net_dev(dev);
	struct r8152 *tp = netdev_priv(netdev);
	struct usb_interface *intf = tp->intf;
	char tmp[256];
	struct tally_counter tally;
	int ret;

	strcpy(buf, dev_name(dev));
	strcat(buf, "\n");
	strcat(buf, DRIVER_VERSION);
	strcat(buf, "\n");

	switch (tp->version) {
	case RTL_VER_05:
		strcat(buf, "RTL_VER_05\n");
		strcat(buf, "usb_patch_code_20190904\n");
		strcat(buf, "pla_patch_code_20190220_0\n");
		strcat(buf, "\n\n\n\n");
		break;
	case RTL_VER_06:
		strcat(buf, "RTL_VER_06\n");
		strcat(buf, "usb_patch_20190909\n");
		strcat(buf, "pla_patch_code_20190408_0\n");
		strcat(buf, "\n\n\n\n");
		break;
	case RTL_VER_09:
		strcat(buf, "RTL_VER_09\n");
		strcat(buf, "usb_patch_code_20190906.cfg\n");
		strcat(buf, "plamcu_patch_code_20190408_0\n");
		strcat(buf, "\n\n\n\n");
		break;
	case RTL_VER_11:
		strcat(buf, "RTL_VER_11\n");
		strcat(buf, "nc0_patch_190128_usb\n");
		strcat(buf, "nc1_patch_181029_usb\n");
		strcat(buf, "nc2_patch_180821_usb\n");
		strcat(buf, "uc2_patch_181018_usb\n");
		strcat(buf, "data_ram_patch_v02_usb\n");
		strcat(buf, "100m_tx_coefficient_180716_usb\n");
		strcat(buf, "USB_patch_code_20210310_v4\n");
		strcat(buf, "PLA_patch_code_20210318_v6\n");
		break;
	case RTL_VER_12:
		strcat(buf, "RTL_VER_12\n");
		strcat(buf, "nc_patch_190821_usb\n");
		strcat(buf, "nc2_patch_190823_usb\n");
		strcat(buf, "uc2_patch_190817_usb\n");
		strcat(buf, "uc_patch_190731_usb\n");
		strcat(buf, "USB_patch_code_20190816_v2\n");
		strcat(buf, "PLA_patch_code_20190827_v2\n");
		break;
	case RTL_VER_13:
	case RTL_VER_15:
		strcat(buf, "RTL_VER_13\n");
		strcat(buf, "tgphy_ramcode_v21_usb_20220324\n");
		strcat(buf, "\n");
		strcat(buf, "\n");
		strcat(buf, "\n");
		strcat(buf, "USB_patch_code_20220314_v4\n");
		strcat(buf, "PLA_SVN8948_20220330_v06\n");
		break;
	case RTL_VER_14:
		strcat(buf, "RTL_VER_14\n");
		strcat(buf, "USB_Patch_Code_svn3347\n");
		strcat(buf, "PLA_Patch_Code_svn3346\n");
		strcat(buf, "\n\n\n\n");
		break;
	default:
		strcat(buf, "\n\n\n\n\n\n\n");
		break;
	}

	ret = usb_autopm_get_interface(intf);
	if (ret < 0)
		return ret;

	ret = mutex_lock_interruptible(&tp->control);
	if (ret < 0) {
		usb_autopm_put_interface(intf);
		goto err1;
	}

	generic_ocp_read(tp, PLA_TALLYCNT, sizeof(tally), &tally, MCU_TYPE_PLA);

	mutex_unlock(&tp->control);

	usb_autopm_put_interface(intf);

	sprintf(tmp, "tx_packets = %Lu\n", le64_to_cpu(tally.tx_packets));
	strcat(buf, tmp);
	sprintf(tmp, "rx_packets = %Lu\n", le64_to_cpu(tally.rx_packets));
	strcat(buf, tmp);
	sprintf(tmp, "tx_errors = %Lu\n", le64_to_cpu(tally.tx_errors));
	strcat(buf, tmp);
	sprintf(tmp, "tx_errors = %u\n", le32_to_cpu(tally.rx_errors));
	strcat(buf, tmp);
	sprintf(tmp, "rx_missed = %u\n", le16_to_cpu(tally.rx_missed));
	strcat(buf, tmp);
	sprintf(tmp, "align_errors = %u\n", le16_to_cpu(tally.align_errors));
	strcat(buf, tmp);
	sprintf(tmp, "tx_one_collision = %u\n",
		le32_to_cpu(tally.tx_one_collision));
	strcat(buf, tmp);
	sprintf(tmp, "tx_multi_collision = %u\n",
		le32_to_cpu(tally.tx_multi_collision));
	strcat(buf, tmp);
	sprintf(tmp, "rx_unicast = %Lu\n", le64_to_cpu(tally.rx_unicast));
	strcat(buf, tmp);
	sprintf(tmp, "rx_broadcast = %Lu\n", le64_to_cpu(tally.rx_broadcast));
	strcat(buf, tmp);
	sprintf(tmp, "rx_multicast = %u\n", le32_to_cpu(tally.rx_multicast));
	strcat(buf, tmp);
	sprintf(tmp, "tx_aborted = %u\n", le16_to_cpu(tally.tx_aborted));
	strcat(buf, tmp);
	sprintf(tmp, "tx_underrun = %u\n", le16_to_cpu(tally.tx_underrun));
	strcat(buf, tmp);

err1:
	if (ret < 0)
		return ret;
	else
		return strlen(buf);
}

static inline bool hex_value(char p)
{
	return (p >= '0' && p <= '9') ||
	       (p >= 'a' && p <= 'f') ||
	       (p >= 'A' && p <= 'F');
}

static int ocp_count(char *v1)
{
	int len = strlen(v1), count = 0;
	char *v2 = strchr(v1, ' ');
	bool is_vaild = false;

	if (len < 5 || !v2)
		goto out1;
//	else if (strncmp(v1, "pla ", 4) && strncmp(v1, "usb ", 4))
//		goto out1;

	v1 = v2;
	len = strlen(v2);
	while(len) {
		if (*v1 != ' ')
			break;
		v1++;
		len--;
	}

	if (!len || *v1 == '\n')
		goto out1;

check:
	v2 = strchr(v1, ' ');

	if (len > 2 && !strncasecmp(v1, "0x", 2)) {
		v1 += 2;
		len -= 2;
		if (v1 == v2 || *v1 == '\n')
			goto out1;
	}

	if (v2) {
		while (v1 < v2) {
			if (!hex_value(*v1))
				goto out1;
			v1++;
			len--;
		}

		count++;

		while(len) {
			if (*v1 != ' ')
				break;
			v1++;
			len--;
		}

		if (len)
			goto check;

		is_vaild = true;
	} else {
		int i;

		if (len && v1[len - 1] == '\n')
			len--;

		for (i = 0; i < len; i++) {
			if (!hex_value(*v1))
				goto out1;
			v1++;
		}

		if (len)
			count++;

		is_vaild = true;
	}

out1:
	if (is_vaild)
		return count;
	else
		return 0;
}

static ssize_t ocp_store(struct device *dev, struct device_attribute *attr,
			 const char *buf, size_t count)
{
	struct net_device *netdev = to_net_dev(dev);
	struct r8152 *tp = netdev_priv(netdev);
	struct usb_interface *intf = tp->intf;
	u32 v1, v2, v3, v4;
	u16 type;
	int num, ret;

	if (!strncmp(buf, "pla ", 4))
		type = MCU_TYPE_PLA;
	else if (!strncmp(buf, "usb ", 4))
		type = MCU_TYPE_USB;
	else
		return -EINVAL;

	if (!ocp_count((char *)buf))
		return -EINVAL;

	num = sscanf(strchr(buf, ' '), "%x %x %x %x\n", &v1, &v2, &v3, &v4);

	if (num > 1) {
		if ((v1 == 2 && (v2 & 1)) ||
		    (v1 == 4 && (v2 & 3)) ||
		    (type == MCU_TYPE_PLA &&
		     (v2 < 0xc000 || (v2 & ~3) == PLA_OCP_GPHY_BASE)))
			return -EINVAL;
	}

	ret = usb_autopm_get_interface(intf);
	if (ret < 0)
		return ret;

	ret = mutex_lock_interruptible(&tp->control);
	if (ret < 0)
		goto put;

	switch(num) {
	case 2:
		switch (v1) {
		case 1:
			netif_info(tp, drv, netdev, "%s read byte %x = %x\n",
				   type ? "PLA" : "USB", v2,
				   ocp_read_byte(tp, type, v2));
			break;
		case 2:
			netif_info(tp, drv, netdev, "%s read word %x = %x\n",
				   type ? "PLA" : "USB", v2,
				   ocp_read_word(tp, type, v2));
			break;
		case 4:
			netif_info(tp, drv, netdev, "%s read dword %x = %x\n",
				   type ? "PLA" : "USB", v2,
				   ocp_read_dword(tp, type, v2));
			break;
		default:
			ret = -EINVAL;
			break;
		}
		break;
	case 3:
		switch (v1) {
		case 1:
			netif_info(tp, drv, netdev, "%s write byte %x = %x\n",
				   type ? "PLA" : "USB", v2, v3);
			ocp_write_byte(tp, type, v2, v3);
			break;
		case 2:
			netif_info(tp, drv, netdev, "%s write word %x = %x\n",
				   type ? "PLA" : "USB", v2, v3);
			ocp_write_word(tp, type, v2, v3);
			break;
		case 4:
			netif_info(tp, drv, netdev, "%s write dword %x = %x\n",
				   type ? "PLA" : "USB", v2, v3);
			ocp_write_dword(tp, type, v2, v3);
			break;
		default:
			ret = -EINVAL;
			break;
		}
		break;
	case 4:
	case 1:
	default:
		ret = -EINVAL;
		break;
	}

	mutex_unlock(&tp->control);

put:
	usb_autopm_put_interface(intf);

	if (ret < 0)
		return ret;
	else
		return count;
}

static DEVICE_ATTR_RW(ocp);

static struct attribute *rtk_attrs[] = {
	&dev_attr_ocp.attr,
	NULL
};

#define ATTR_PLA_SIZE	0x3000

/* hexdump -e '"%04_ax\t" 16/1 "%02X " "\n"' pla */
static ssize_t pla_read(struct file *fp, struct kobject *kobj,
			struct bin_attribute *attr, char *buf, loff_t offset,
			size_t size)
{
	struct device *dev = kobj_to_dev(kobj);
	struct net_device *netdev = to_net_dev(dev);
	struct r8152 *tp = netdev_priv(netdev);
	int ret;

	if (size <= ATTR_PLA_SIZE)
		size = min(size, ATTR_PLA_SIZE - (size_t)offset);
	else
		return -EINVAL;

	ret = usb_autopm_get_interface(tp->intf);
	if (ret < 0)
		return ret;

	/* rtnl_lock(); */
	ret = mutex_lock_interruptible(&tp->control);
	if (ret < 0)
		goto put;

	ret = pla_ocp_read(tp, offset + 0xc000, (u16)size, buf);
	if (ret < 0)
		netif_err(tp, drv, netdev,
			  "Read PLA offset 0x%Lx, len = %zd fail\n",
			  offset + 0xc000, size);

	mutex_unlock(&tp->control);
	/* rtnl_unlock(); */

put:
	usb_autopm_put_interface(tp->intf);

	if (ret < 0)
		return ret;
	else
		return size;
}

static BIN_ATTR_RO(pla, ATTR_PLA_SIZE);

static struct bin_attribute *rtk_bin_attrs[] = {
	&bin_attr_pla,
	NULL
};

static struct attribute_group rtk_dbg_grp = {
	.name = "nic_swsd",
	.attrs = rtk_attrs,
	.bin_attrs = rtk_bin_attrs,
};

#endif /* RTL8152_DEBUG */

static ssize_t rx_copybreak_show(struct device *dev,
				 struct device_attribute *attr, char *buf)
{
	struct net_device *netdev = to_net_dev(dev);
	struct r8152 *tp = netdev_priv(netdev);

	sprintf(buf, "%u\n", tp->rx_copybreak);

	return strlen(buf);
}

static ssize_t rx_copybreak_store(struct device *dev,
				  struct device_attribute *attr,
				  const char *buf, size_t count)
{
	struct net_device *netdev = to_net_dev(dev);
	struct r8152 *tp = netdev_priv(netdev);
	u32 rx_copybreak;

	if (sscanf(buf, "%u\n", &rx_copybreak) != 1)
		return -EINVAL;

	if (rx_copybreak < ETH_ZLEN)
		return -EINVAL;

	if (test_bit(RTL8152_UNPLUG, &tp->flags))
		return -ENODEV;

	if (tp->rx_copybreak != rx_copybreak) {
		if (tp->netdev->flags & IFF_UP) {
			int ret;

			ret = mutex_lock_interruptible(&tp->control);
			if (ret < 0)
				return ret;

			napi_disable(&tp->napi);
			tp->rx_copybreak = rx_copybreak;
			napi_enable(&tp->napi);

			mutex_unlock(&tp->control);
		} else {
			tp->rx_copybreak = rx_copybreak;
		}
	}

	return count;
}

static DEVICE_ATTR_RW(rx_copybreak);

static ssize_t fc_pause_on_show(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	struct r8152 *tp = netdev_priv(to_net_dev(dev));

	if (!tp->fc_pause_on)
		sprintf(buf, "(Auto)%u\n", fc_pause_on_auto(tp));
	else
		sprintf(buf, "%u\n", tp->fc_pause_on);

	return strlen(buf);
}

static ssize_t fc_pause_on_store(struct device *dev,
				 struct device_attribute *attr,
				 const char *buf, size_t count)
{
	struct net_device *netdev = to_net_dev(dev);
	struct r8152 *tp = netdev_priv(netdev);
	struct usb_interface *intf = tp->intf;
	u32 pause_on, pause_off, tmp;
	int ret = 0;

	if (test_bit(RTL8152_UNPLUG, &tp->flags))
		return -ENODEV;

	if (sscanf(buf, "%u\n", &pause_on) != 1)
		return -EINVAL;

	if (tp->fc_pause_off)
		pause_off = tp->fc_pause_off;
	else
		pause_off = fc_pause_off_auto(tp);

	if (pause_on)
		tmp = pause_on;
	else
		tmp = fc_pause_on_auto(tp);

	if (tmp >= pause_off) {
		netif_err(tp, drv, netdev, "fc_pause_on must be less than %u\n",
			  pause_off);
		return -EINVAL;
	}

	if (tp->fc_pause_on != pause_on) {
		ret = usb_autopm_get_interface(intf);
		if (ret < 0)
			return ret;

		ret = mutex_lock_interruptible(&tp->control);
		if (ret < 0)
			goto put;

		tp->fc_pause_on = pause_on;

		if (netdev->flags & IFF_UP) {
			r8156_fc_parameter(tp);

			if (netif_carrier_ok(netdev)) {
				netif_stop_queue(netdev);
				napi_disable(&tp->napi);
				tasklet_disable(&tp->tx_tl);
				tp->rtl_ops.disable(tp);
				tp->rtl_ops.enable(tp);
				rtl_start_rx(tp);
				tasklet_enable(&tp->tx_tl);
				napi_enable(&tp->napi);
				rtl8152_set_rx_mode(netdev);
				netif_wake_queue(netdev);
			}
		}

		mutex_unlock(&tp->control);

put:
		usb_autopm_put_interface(intf);
	}

	if (ret < 0)
		return ret;
	else
		return count;
}

static DEVICE_ATTR_RW(fc_pause_on);

static ssize_t fc_pause_off_show(struct device *dev,
				 struct device_attribute *attr, char *buf)
{
	struct r8152 *tp = netdev_priv(to_net_dev(dev));

	if (!tp->fc_pause_off)
		sprintf(buf, "(Auto)%u\n", fc_pause_off_auto(tp));
	else
		sprintf(buf, "%u\n", tp->fc_pause_off);

	return strlen(buf);
}

static ssize_t fc_pause_off_store(struct device *dev,
				  struct device_attribute *attr,
				  const char *buf, size_t count)
{
	struct net_device *netdev = to_net_dev(dev);
	struct r8152 *tp = netdev_priv(netdev);
	struct usb_interface *intf = tp->intf;
	u32 pause_on, pause_off, tmp;
	int ret = 0;

	if (test_bit(RTL8152_UNPLUG, &tp->flags))
		return -ENODEV;

	if (sscanf(buf, "%u\n", &pause_off) != 1)
		return -EINVAL;

	if (tp->fc_pause_on)
		pause_on = tp->fc_pause_on;
	else
		pause_on = fc_pause_on_auto(tp);

	if (pause_off)
		tmp = pause_off;
	else
		tmp = fc_pause_off_auto(tp);

	if (tmp <= pause_on){
		netif_err(tp, drv, netdev, "fc_pause_off must be more than %u\n",
			  pause_on);
		return -EINVAL;
	}

	if (tp->fc_pause_off != pause_off) {
		ret = usb_autopm_get_interface(intf);
		if (ret < 0)
			return ret;

		ret = mutex_lock_interruptible(&tp->control);
		if (ret < 0)
			goto put;

		tp->fc_pause_off = pause_off;

		if (netdev->flags & IFF_UP) {
			r8156_fc_parameter(tp);

			if (netif_carrier_ok(netdev)) {
				netif_stop_queue(netdev);
				napi_disable(&tp->napi);
				tasklet_disable(&tp->tx_tl);
				tp->rtl_ops.disable(tp);
				tp->rtl_ops.enable(tp);
				rtl_start_rx(tp);
				tasklet_enable(&tp->tx_tl);
				napi_enable(&tp->napi);
				rtl8152_set_rx_mode(netdev);
				netif_wake_queue(netdev);
			}
		}

		mutex_unlock(&tp->control);

put:
		usb_autopm_put_interface(intf);
	}

	if (ret < 0)
		return ret;
	else
		return count;
}

static DEVICE_ATTR_RW(fc_pause_off);

static ssize_t
sg_en_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	struct net_device *netdev = to_net_dev(dev);
	struct r8152 *tp = netdev_priv(netdev);

	if (tp->sg_use)
		strcat(buf, "enable\n");
	else
		strcat(buf, "disable\n");

	return strlen(buf);
}

static ssize_t sg_en_store(struct device *dev, struct device_attribute *attr,
			   const char *buf, size_t count)
{
	struct net_device *netdev = to_net_dev(dev);
	struct r8152 *tp = netdev_priv(netdev);
	u32 tso_size;

	if (!strncmp(buf, "enable", 6) &&
	    usb_device_no_sg_constraint(tp->udev)) {
		tp->sg_use = true;
		tso_size = GSO_MAX_SIZE;
	} else if (!strncmp(buf, "disable", 7)) {
		tp->sg_use = false;
		tso_size = RTL_LIMITED_TSO_SIZE;
	} else {
		return -EINVAL;
	}

#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,26)
	netif_set_gso_max_size(netdev, tso_size);
#endif /* LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,26) */

	return count;
}

static DEVICE_ATTR_RW(sg_en);

static struct attribute *rtk_adv_attrs[] = {
	&dev_attr_rx_copybreak.attr,
	&dev_attr_sg_en.attr,
	&dev_attr_fc_pause_on.attr,
	&dev_attr_fc_pause_off.attr,
	NULL
};

static struct attribute_group rtk_adv_grp = {
	.name = "rtl_adv",
	.attrs = rtk_adv_attrs,
};

static void rtl_get_mapt_ver(struct r8152 *tp)
{
	struct usb_device *udev = tp->udev;
	u32 ocp_data;

	if (le16_to_cpu(udev->descriptor.idVendor) == VENDOR_ID_LENOVO) {
		tp->lenovo_macpassthru = 1;
		return;
	}

	/* test for -AD variant of RTL8153 */
	ocp_data = ocp_read_word(tp, MCU_TYPE_USB, USB_MISC_0);
	if ((ocp_data & AD_MASK) == 0x1000) {
		/* test for MAC address pass-through bit */
		ocp_data = ocp_read_byte(tp, MCU_TYPE_USB, USB_EFUSE);
		if (ocp_data & PASS_THRU_MASK) {
			tp->dell_macpassthru = 1;
			return;
		}
	}

	/* test for RTL8153-BND and RTL8153-BD */
	ocp_data = ocp_read_byte(tp, MCU_TYPE_USB, USB_MISC_1);
	if ((ocp_data & BND_MASK) || (ocp_data & BD_MASK)) {
		tp->dell_macpassthru = 1;
		return;
	} else if (tp->version == RTL_VER_09 && (ocp_data & BL_MASK)) {
		tp->lenovo_macpassthru = 1;
		return;
	}
}

static int rtl8152_probe(struct usb_interface *intf,
			 const struct usb_device_id *id)
{
	struct usb_device *udev = interface_to_usbdev(intf);
	u8 version = rtl8152_get_version(intf);
	struct r8152 *tp;
	struct net_device *netdev;
	int ret;

	if (version == RTL_VER_UNKNOWN)
		return -ENODEV;

	if (!rtl_vendor_mode(intf))
		return -ENODEV;

	usb_reset_device(udev);
	netdev = alloc_etherdev(sizeof(struct r8152));
	if (!netdev) {
		dev_err(&intf->dev, "Out of memory\n");
		return -ENOMEM;
	}

	SET_NETDEV_DEV(netdev, &intf->dev);
	tp = netdev_priv(netdev);
	tp->msg_enable = 0x7FFF;

	tp->udev = udev;
	tp->netdev = netdev;
	tp->intf = intf;
	tp->version = version;

	tp->pipe_ctrl_in = usb_rcvctrlpipe(udev, 0);
	tp->pipe_ctrl_out = usb_sndctrlpipe(udev, 0);
	tp->pipe_in = usb_rcvbulkpipe(udev, 1);
	tp->pipe_out = usb_sndbulkpipe(udev, 2);
	tp->pipe_intr = usb_rcvintpipe(udev, 3);

	switch (version) {
	case RTL_VER_01:
	case RTL_VER_02:
	case RTL_VER_07:
		tp->mii.supports_gmii = 0;
		break;
	default:
		tp->mii.supports_gmii = 1;
		break;
	}

	ret = rtl_ops_init(tp);
	if (ret)
		goto out;

	mutex_init(&tp->control);
	INIT_DELAYED_WORK(&tp->schedule, rtl_work_func_t);
	INIT_DELAYED_WORK(&tp->hw_phy_work, rtl_hw_phy_work_func_t);
	tasklet_setup(&tp->tx_tl, bottom_half);
	tasklet_disable(&tp->tx_tl);

#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,2,3)
	if (usb_device_no_sg_constraint(udev))
		tp->sg_use = true;
#endif /* LINUX_VERSION_CODE >= KERNEL_VERSION(5,2,3) */

#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,29)
	netdev->open = rtl8152_open;
	netdev->stop = rtl8152_close;
	netdev->get_stats = rtl8152_get_stats;
	netdev->hard_start_xmit = rtl8152_start_xmit;
	netdev->tx_timeout = rtl8152_tx_timeout;
	netdev->change_mtu = rtl8152_change_mtu;
	netdev->set_mac_address = rtl8152_set_mac_address;
	netdev->do_ioctl = rtl8152_ioctl;
	netdev->set_multicast_list = rtl8152_set_rx_mode;
	netdev->vlan_rx_register = rtl8152_vlan_rx_register;
#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,22)
	netdev->vlan_rx_kill_vid = rtl8152_vlan_rx_kill_vid;
#endif /* LINUX_VERSION_CODE < KERNEL_VERSION(2,6,22) */
#else
	netdev->netdev_ops = &rtl8152_netdev_ops;
#endif /* HAVE_NET_DEVICE_OPS */

	netdev->watchdog_timeo = RTL8152_TX_TIMEOUT;

	netdev->features |= NETIF_F_RXCSUM | NETIF_F_IP_CSUM | NETIF_F_SG |
			    NETIF_F_TSO | NETIF_F_FRAGLIST | NETIF_F_IPV6_CSUM |
			    NETIF_F_TSO6 | NETIF_F_HW_VLAN_CTAG_RX |
			    NETIF_F_HW_VLAN_CTAG_TX;

#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,39)
	netdev->hw_features = NETIF_F_RXCSUM | NETIF_F_IP_CSUM | NETIF_F_SG |
			      NETIF_F_TSO | NETIF_F_FRAGLIST |
			      NETIF_F_IPV6_CSUM | NETIF_F_TSO6 |
			      NETIF_F_HW_VLAN_CTAG_RX | NETIF_F_HW_VLAN_CTAG_TX;
	netdev->vlan_features = NETIF_F_SG | NETIF_F_IP_CSUM | NETIF_F_TSO |
				NETIF_F_HIGHDMA | NETIF_F_FRAGLIST |
				NETIF_F_IPV6_CSUM | NETIF_F_TSO6;
#endif /* LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,39) */

	if (tp->version == RTL_VER_01) {
		netdev->features &= ~NETIF_F_RXCSUM;
#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,39)
		netdev->hw_features &= ~NETIF_F_RXCSUM;
#endif /* LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,39) */
	}

	rtl_get_mapt_ver(tp);

	netdev->ethtool_ops = &ops;
#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,26)
	if (!tp->sg_use)
		netif_set_gso_max_size(netdev, RTL_LIMITED_TSO_SIZE);
#else
	netdev->features &= ~(NETIF_F_TSO | NETIF_F_TSO6);
#endif /* LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,26) */

#if LINUX_VERSION_CODE >= KERNEL_VERSION(4,10,0)
	/* MTU range: 68 - 1500 or 9194 */
	netdev->min_mtu = ETH_MIN_MTU;
	switch (tp->version) {
	case RTL_VER_03:
	case RTL_VER_04:
	case RTL_VER_05:
	case RTL_VER_06:
	case RTL_VER_08:
	case RTL_VER_09:
	case RTL_VER_14:
		netdev->max_mtu = size_to_mtu(9 * 1024);
		break;
	case RTL_VER_10:
	case RTL_VER_11:
		netdev->max_mtu = size_to_mtu(15 * 1024);
		break;
	case RTL_VER_12:
	case RTL_VER_13:
	case RTL_VER_15:
		netdev->max_mtu = size_to_mtu(16 * 1024);
		break;
	case RTL_VER_01:
	case RTL_VER_02:
	case RTL_VER_07:
	default:
		netdev->max_mtu = ETH_DATA_LEN;
		break;
	}
#endif /* LINUX_VERSION_CODE >= KERNEL_VERSION(4,10,0) */

	tp->mii.dev = netdev;
	tp->mii.mdio_read = read_mii_word;
	tp->mii.mdio_write = write_mii_word;
	tp->mii.phy_id_mask = 0x3f;
	tp->mii.reg_num_mask = 0x1f;
	tp->mii.phy_id = R8152_PHY_ID;
	tp->mii.force_media = 0;
	tp->mii.advertising = ADVERTISE_10HALF | ADVERTISE_10FULL |
			      ADVERTISE_100HALF | ADVERTISE_100FULL;

	tp->autoneg = AUTONEG_ENABLE;
	tp->speed = SPEED_100;
	tp->advertising = RTL_ADVERTISED_10_HALF | RTL_ADVERTISED_10_FULL |
			  RTL_ADVERTISED_100_HALF | RTL_ADVERTISED_100_FULL;
	if (tp->mii.supports_gmii) {
		if (tp->support_2500full &&
		    tp->udev->speed >= USB_SPEED_SUPER) {
			tp->speed = SPEED_2500;
			tp->advertising |= RTL_ADVERTISED_2500_FULL;
		} else {
			tp->speed = SPEED_1000;
		}
		tp->advertising |= RTL_ADVERTISED_1000_FULL;
	}
	tp->duplex = DUPLEX_FULL;

	tp->rx_copybreak = RTL8152_RXFG_HEADSZ;
	tp->rx_pending = 10 * RTL8152_MAX_RX;

	intf->needs_remote_wakeup = 1;

	if (!rtl_can_wakeup(tp))
		__rtl_set_wol(tp, 0);
	else
		tp->saved_wolopts = __rtl_get_wol(tp);

	tp->rtl_ops.init(tp);
	queue_delayed_work(system_long_wq, &tp->hw_phy_work, 0);
	set_ethernet_addr(tp, false);

	usb_set_intfdata(intf, tp);

	if (tp->support_2500full)
		netif_napi_add(netdev, &tp->napi, r8152_poll, 256);
	else
		netif_napi_add(netdev, &tp->napi, r8152_poll, 64);

	ret = register_netdev(netdev);
	if (ret != 0) {
		dev_err(&intf->dev, "couldn't register the device\n");
		goto out1;
	}

	if (tp->saved_wolopts)
		device_set_wakeup_enable(&udev->dev, true);
	else
		device_set_wakeup_enable(&udev->dev, false);

	/* usb_enable_autosuspend(udev); */

	netif_info(tp, probe, netdev, "%s\n", DRIVER_VERSION);
	netif_info(tp, probe, netdev, "%s\n", PATENTS);

	ret = sysfs_create_group(&netdev->dev.kobj, &rtk_adv_grp);
	if (ret < 0) {
		netif_err(tp, probe, netdev, "creat rtk_adv_grp fail\n");
		goto out2;
	}

#ifdef RTL8152_DEBUG
	ret = sysfs_create_group(&netdev->dev.kobj, &rtk_dbg_grp);
	if (ret < 0) {
		netif_err(tp, probe, netdev, "creat rtk_dbg_grp fail\n");
		goto out3;
	}
#endif

	return 0;

#ifdef RTL8152_DEBUG
out3:
	sysfs_remove_group(&netdev->dev.kobj, &rtk_adv_grp);
#endif
out2:
	unregister_netdev(netdev);
out1:
	netif_napi_del(&tp->napi);
	tasklet_kill(&tp->tx_tl);
	usb_set_intfdata(intf, NULL);
out:
	free_netdev(netdev);
	return ret;
}

static void rtl8152_disconnect(struct usb_interface *intf)
{
	struct r8152 *tp = usb_get_intfdata(intf);

	usb_set_intfdata(intf, NULL);
	if (tp) {
		struct net_device *netdev = tp->netdev;

#ifdef RTL8152_DEBUG
		sysfs_remove_group(&netdev->dev.kobj, &rtk_dbg_grp);
#endif
		sysfs_remove_group(&netdev->dev.kobj, &rtk_adv_grp);

		rtl_set_unplug(tp);
		unregister_netdev(netdev);
		netif_napi_del(&tp->napi);
		tasklet_kill(&tp->tx_tl);
		cancel_delayed_work_sync(&tp->hw_phy_work);
		if (tp->rtl_ops.unload)
			tp->rtl_ops.unload(tp);
		free_netdev(netdev);
	}
}

#define REALTEK_USB_DEVICE(vend, prod)	{ \
	USB_DEVICE_INTERFACE_CLASS(vend, prod, USB_CLASS_VENDOR_SPEC), \
}, \
{ \
	USB_DEVICE_AND_INTERFACE_INFO(vend, prod, USB_CLASS_COMM, \
			USB_CDC_SUBCLASS_ETHERNET, USB_CDC_PROTO_NONE), \
}, \
{ \
	USB_DEVICE_AND_INTERFACE_INFO(vend, prod, USB_CLASS_COMM, \
			USB_CDC_SUBCLASS_NCM, USB_CDC_PROTO_NONE), \
}

/* table of devices that work with this driver */
static const struct usb_device_id rtl8152_table[] = {
	/* Realtek */
	REALTEK_USB_DEVICE(VENDOR_ID_REALTEK, 0x8050),
	REALTEK_USB_DEVICE(VENDOR_ID_REALTEK, 0x8053),
	REALTEK_USB_DEVICE(VENDOR_ID_REALTEK, 0x8152),
	REALTEK_USB_DEVICE(VENDOR_ID_REALTEK, 0x8153),
	REALTEK_USB_DEVICE(VENDOR_ID_REALTEK, 0x8155),
	REALTEK_USB_DEVICE(VENDOR_ID_REALTEK, 0x8156),

	/* Microsoft */
	REALTEK_USB_DEVICE(VENDOR_ID_MICROSOFT, 0x07ab),
	REALTEK_USB_DEVICE(VENDOR_ID_MICROSOFT, 0x07c6),
	REALTEK_USB_DEVICE(VENDOR_ID_MICROSOFT, 0x0927),

	/* Samsung */
	REALTEK_USB_DEVICE(VENDOR_ID_SAMSUNG, 0xa101),

	/* Lenovo */
	REALTEK_USB_DEVICE(VENDOR_ID_LENOVO, 0x304f),
	REALTEK_USB_DEVICE(VENDOR_ID_LENOVO, 0x3052),
	REALTEK_USB_DEVICE(VENDOR_ID_LENOVO, 0x3054),
	REALTEK_USB_DEVICE(VENDOR_ID_LENOVO, 0x3057),
	REALTEK_USB_DEVICE(VENDOR_ID_LENOVO, 0x3062),
	REALTEK_USB_DEVICE(VENDOR_ID_LENOVO, 0x3069),
	REALTEK_USB_DEVICE(VENDOR_ID_LENOVO, 0x3082),
	REALTEK_USB_DEVICE(VENDOR_ID_LENOVO, 0x3098),
	REALTEK_USB_DEVICE(VENDOR_ID_LENOVO, 0x7205),
	REALTEK_USB_DEVICE(VENDOR_ID_LENOVO, 0x720a),
	REALTEK_USB_DEVICE(VENDOR_ID_LENOVO, 0x720b),
	REALTEK_USB_DEVICE(VENDOR_ID_LENOVO, 0x720c),
	REALTEK_USB_DEVICE(VENDOR_ID_LENOVO, 0x7214),
	REALTEK_USB_DEVICE(VENDOR_ID_LENOVO, 0x721e),
	REALTEK_USB_DEVICE(VENDOR_ID_LENOVO, 0x8153),
	REALTEK_USB_DEVICE(VENDOR_ID_LENOVO, 0xa359),
	REALTEK_USB_DEVICE(VENDOR_ID_LENOVO, 0xa387),

	/* TP-LINK */
	REALTEK_USB_DEVICE(VENDOR_ID_TPLINK, 0x0601),

	/* Nvidia */
	REALTEK_USB_DEVICE(VENDOR_ID_NVIDIA,  0x09ff),

	/* LINKSYS */
	REALTEK_USB_DEVICE(VENDOR_ID_LINKSYS, 0x0041),

	/* Getac */
	REALTEK_USB_DEVICE(0x2baf, 0x0012),

	{}
};

MODULE_DEVICE_TABLE(usb, rtl8152_table);

static struct usb_driver rtl8152_driver = {
	.name =		MODULENAME,
	.id_table =	rtl8152_table,
	.probe =	rtl8152_probe,
	.disconnect =	rtl8152_disconnect,
	.suspend =	rtl8152_suspend,
	.resume =	rtl8152_resume,
	.reset_resume =	rtl8152_reset_resume,
	.pre_reset =	rtl8152_pre_reset,
	.post_reset =	rtl8152_post_reset,
	.supports_autosuspend = 1,
#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,5,0)
	.disable_hub_initiated_lpm = 1,
#endif
};

module_usb_driver(rtl8152_driver);

MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");
MODULE_VERSION(DRIVER_VERSION);
