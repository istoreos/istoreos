/*
 * (C) Copyright 2017 Rockchip Electronics Co., Ltd
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */

#ifndef _FG_RK8XX_H_
#define _FG_RK8XX_H_

/* register definition */
#define SECONDS_REG		0X00
#define VB_MON_REG		0x21
#define THERMAL_REG		0x22
#define SUP_STS_REG		0xA0
#define USB_CTRL_REG		0xA1
#define CHRG_CTRL_REG1		0xA3
#define CHRG_CTRL_REG2		0xA4
#define CHRG_CTRL_REG3		0xA5
#define BAT_CTRL_REG		0xA6
#define BAT_HTS_TS_REG		0xA8
#define BAT_LTS_TS_REG		0xA9
#define TS_CTRL_REG		0xAC
#define ADC_CTRL_REG		0xAD
#define GGCON_REG		0xB0
#define GGSTS_REG		0xB1
#define ZERO_CUR_ADC_REGH	0xB2
#define ZERO_CUR_ADC_REGL	0xB3
#define GASCNT_CAL_REG3		0xB4
#define GASCNT_CAL_REG2		0xB5
#define GASCNT_CAL_REG1		0xB6
#define GASCNT_CAL_REG0		0xB7
#define GASCNT_REG3		0xB8
#define GASCNT_REG2		0xB9
#define GASCNT_REG1		0xBA
#define GASCNT_REG0		0xBB
#define BAT_CUR_AVG_REGH	0xBC
#define BAT_CUR_AVG_REGL	0xBD
#define TS_ADC_REGH		0xBE
#define TS_ADC_REGL		0xBF
#define RK818_TS2_ADC_REGH	0xC0
#define RK818_TS2_ADC_REGL	0xC1
#define RK816_USB_ADC_REGH	0xC0
#define RK816_USB_ADC_REGL	0xC1
#define BAT_OCV_REGH		0xC2
#define BAT_OCV_REGL		0xC3
#define BAT_VOL_REGH		0xC4
#define BAT_VOL_REGL		0xC5
#define RELAX_ENTRY_THRES_REGH	0xC6
#define RELAX_ENTRY_THRES_REGL	0xC7
#define RELAX_EXIT_THRES_REGH	0xC8
#define RELAX_EXIT_THRES_REGL	0xC9
#define RELAX_VOL1_REGH		0xCA
#define RELAX_VOL1_REGL		0xCB
#define RELAX_VOL2_REGH		0xCC
#define RELAX_VOL2_REGL		0xCD
#define RELAX_CUR1_REGH		0xCE
#define RELAX_CUR1_REGL		0xCF
#define RELAX_CUR2_REGH		0xD0
#define RELAX_CUR2_REGL		0xD1
#define CAL_OFFSET_REGH		0xD2
#define CAL_OFFSET_REGL		0xD3
#define NON_ACT_TIMER_CNT_REG	0xD4
#define VCALIB0_REGH		0xD5
#define VCALIB0_REGL		0xD6
#define VCALIB1_REGH		0xD7
#define VCALIB1_REGL		0xD8
#define FCC_GASCNT_REG3		0xD9
#define FCC_GASCNT_REG2		0xDA
#define FCC_GASCNT_REG1		0xDB
#define FCC_GASCNT_REG0		0xDC
#define IOFFSET_REGH		0xDD
#define IOFFSET_REGL		0xDE
#define SLEEP_CON_SAMP_CUR_REG	0xDF
#define SOC_REG			0xE0
#define	REMAIN_CAP_REG3		0xE1
#define	REMAIN_CAP_REG2		0xE2
#define	REMAIN_CAP_REG1		0xE3
#define	REMAIN_CAP_REG0		0xE4
#define	UPDAT_LEVE_REG		0xE5
#define	NEW_FCC_REG3		0xE6
#define	NEW_FCC_REG2		0xE7
#define	NEW_FCC_REG1		0xE8
#define	NEW_FCC_REG0		0xE9
#define NON_ACT_TIMER_CNT_SAVE_REG 0xEA
#define OCV_VOL_VALID_REG	0xEB
#define REBOOT_CNT_REG		0xEC
#define POFFSET_REG		0xED
#define MISC_MARK_REG		0xEE
#define HALT_CNT_REG          	0xEF
#define DATA15_REG		0xEF
#define DATA16_REG		0xF0
#define DATA17_REG		0xF1
#define DATA18_REG		0xF2

#endif
