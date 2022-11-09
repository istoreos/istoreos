// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright © 2000-2010 David Woodhouse <dwmw2@infradead.org> et al.
 *
 */

#ifndef __MTD_CFI_H__
#define __MTD_CFI_H__

#define CFI_MFR_ANY		0xFFFF
#define CFI_ID_ANY		0xFFFF
#define CFI_MFR_CONTINUATION	0x007F

#define CFI_MFR_AMD		0x0001
#define CFI_MFR_AMIC		0x0037
#define CFI_MFR_ATMEL		0x001F
#define CFI_MFR_EON		0x001C
#define CFI_MFR_FUJITSU		0x0004
#define CFI_MFR_HYUNDAI		0x00AD
#define CFI_MFR_INTEL		0x0089
#define CFI_MFR_MACRONIX	0x00C2
#define CFI_MFR_NEC		0x0010
#define CFI_MFR_PMC		0x009D
#define CFI_MFR_SAMSUNG		0x00EC
#define CFI_MFR_SHARP		0x00B0
#define CFI_MFR_SST		0x00BF
#define CFI_MFR_ST		0x0020 /* STMicroelectronics */
#define CFI_MFR_MICRON		0x002C	/* Micron */
#define CFI_MFR_TOSHIBA		0x0098
#define CFI_MFR_WINBOND		0x00DA

#endif /* __MTD_CFI_H__ */
