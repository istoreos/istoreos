/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the main directory of this archive
 * for more details.
 *
 * Copyright (C) 2012 by Chuck Chen <ycchen@realtek.com>
 *
 * IO mappings for RTD299X
 */

#ifndef _ASM_MACH_IO_H_
#define _ASM_MACH_IO_H_

#include <asm/io.h>

#define rtd_inb		__raw_readb
#define rtd_inw		__raw_readw
#define rtd_inl		__raw_readl

#define rtd_outb(a, v)	__raw_writeb(v, a)
#define rtd_outw(a, v)	__raw_writew(v, a)
#define rtd_outl(a, v)	__raw_writel(v, a)


#define rtd_maskl(offset, andMask, orMask) rtd_outl(offset, ((rtd_inl(offset) & (andMask)) | (orMask)))
#define rtd_setbits(offset, Mask) rtd_outl(offset, (rtd_inl(offset) | Mask))
#define rtd_clearbits(offset, Mask) rtd_outl(offset, ((rtd_inl(offset) & ~(Mask))))
#define rtd_readbits(offset, Mask)    ((rtd_inl(offset) >> (Mask)) & 0x1)

#define rtd_fld_get(val, start, end) (((val) & rtd_fld_mask(start, end)) >> (end))
#define rtd_fld_mask(start, end)    (((1 << (start - end + 1)) - 1) << (end))

#define _BIT0            0x00000001
#define _BIT1            0x00000002
#define _BIT2            0x00000004
#define _BIT3            0x00000008
#define _BIT4            0x00000010
#define _BIT5            0x00000020
#define _BIT6            0x00000040
#define _BIT7            0x00000080
#define _BIT8            0x00000100
#define _BIT9            0x00000200
#define _BIT10           0x00000400
#define _BIT11           0x00000800
#define _BIT12           0x00001000
#define _BIT13           0x00002000
#define _BIT14           0x00004000
#define _BIT15           0x00008000
#define _BIT16           0x00010000
#define _BIT17           0x00020000
#define _BIT18           0x00040000
#define _BIT19           0x00080000
#define _BIT20           0x00100000
#define _BIT21           0x00200000
#define _BIT22           0x00400000
#define _BIT23           0x00800000
#define _BIT24           0x01000000
#define _BIT25           0x02000000
#define _BIT26           0x04000000
#define _BIT27           0x08000000
#define _BIT28           0x10000000
#define _BIT29           0x20000000
#define _BIT30           0x40000000
#define _BIT31           0x80000000

#endif	//_ASM_MACH_IO_H_
