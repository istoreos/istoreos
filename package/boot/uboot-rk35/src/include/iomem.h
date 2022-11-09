/*
 * SPDX-License-Identifier:     GPL-2.0+
 *
 * (C) Copyright 2018 Rockchip Electronics Co., Ltd
 *
 */

#ifndef _ROCKCHIP_IOMEM_H_
#define _ROCKCHIP_IOMEM_H_

/**
 * iomem_show() - Show iomem data. Usually for peripheral registers.
 *
 * @lable:	Title to show
 * @base:	Base address of iomem
 * @start:	Start offset
 * @end:	End offset
 */
void iomem_show(const char *label, unsigned long base, size_t start, size_t end);

/**
 * iomem_show_by_compatible() - Show iomem data and auto find base address by
 *				compabile(sub string match).
 *
 * @compat:	Compatible name, sub string match.
 * @start:	Start offset
 * @end:	End offset
 *
 * eg: iomem_show_by_compatible("-grf", 0x0, 0x200);
 *     first node that contains "-grf" will be dump.
 *
 */
void iomem_show_by_compatible(const char *compat, size_t start, size_t end);

#endif
