/* SPDX-License-Identifier: GPL-2.0+  */
/*
 * Rockchip Electronics Co., Ltd.
 *
 */

#ifndef __ASM_ARCH_CPU_H
#define __ASM_ARCH_CPU_H

#include <asm/io.h>
#include <dm/device.h>

#define ROCKCHIP_CPU_MASK       0xffff0000
#define ROCKCHIP_CPU_PX30	0x33260000
#define ROCKCHIP_CPU_RK312X     0x31260000
#define ROCKCHIP_CPU_RK3288     0x32880000
#define ROCKCHIP_CPU_RK3308	0x33080000
#define ROCKCHIP_CPU_RK3566	0x35660000
#define ROCKCHIP_CPU_RK3568	0x35680000

#define ROCKCHIP_SOC_MASK	(ROCKCHIP_CPU_MASK | 0xff)
#define ROCKCHIP_SOC_PX30	(ROCKCHIP_CPU_PX30 | 0x00)
#define ROCKCHIP_SOC_PX30S	(ROCKCHIP_CPU_PX30 | 0x01)
#define ROCKCHIP_SOC_RK3126     (ROCKCHIP_CPU_RK312X | 0x00)
#define ROCKCHIP_SOC_RK3126B    (ROCKCHIP_CPU_RK312X | 0x10)
#define ROCKCHIP_SOC_RK3126C    (ROCKCHIP_CPU_RK312X | 0x20)
#define ROCKCHIP_SOC_RK3128     (ROCKCHIP_CPU_RK312X | 0x01)
#define ROCKCHIP_SOC_RK3288     (ROCKCHIP_CPU_RK3288 | 0x00)
#define ROCKCHIP_SOC_RK3288W    (ROCKCHIP_CPU_RK3288 | 0x01)
#define ROCKCHIP_SOC_RK3308	(ROCKCHIP_CPU_RK3308 | 0x00)
#define ROCKCHIP_SOC_RK3308B	(ROCKCHIP_CPU_RK3308 | 0x01)
#define ROCKCHIP_SOC_RK3308BS	(ROCKCHIP_CPU_RK3308 | 0x02)
#define ROCKCHIP_SOC_RK3566	(ROCKCHIP_CPU_RK3566 | 0x00)
#define ROCKCHIP_SOC_RK3568	(ROCKCHIP_CPU_RK3568 | 0x00)

static inline unsigned long rockchip_get_cpu_version(void)
{
#if defined(CONFIG_ROCKCHIP_RK3568)
#define PMUGRF_SOC_CON15	0xfdc20100
	if (readl(PMUGRF_SOC_CON15) & GENMASK(15, 14))
		return 1;
	else
		return 0;
#else
	return 0;
#endif
}

static inline int rockchip_soc_id(void)
{
#if defined(CONFIG_ROCKCHIP_PX30)
	u32 v = readl(0xFF630004);

	/* The CHIP_ID is stored in DDRGRF CON1[15:14]
	 * PX30:  0x00
	 * PX30S: 0x03
	 */
	if (((v >> 14) & 0x03) == 0x03)
		return ROCKCHIP_SOC_PX30S;
	else
		return ROCKCHIP_SOC_PX30;
#elif defined(CONFIG_ROCKCHIP_RK3288)
	/* RK3288W HDMI Revision ID is 0x1A */
	if (readl(0xFF980004) == 0x1A)
		return ROCKCHIP_SOC_RK3288W;
	else
		return ROCKCHIP_SOC_RK3288;
#elif defined(CONFIG_ROCKCHIP_RK3308)
	/*
	 * The CHIP_ID is stored in GRF_CHIP_ID:
	 * RK3308:  0xcea (3306 in decimal)
	 * RK3308B: 0x3308
	 * RK3308BS: 0x3308c
	 */
	u32 v = readl(0xFF000800);

	if (v == 3306)
		return ROCKCHIP_SOC_RK3308;
	else if (v == 0x3308c)
		return ROCKCHIP_SOC_RK3308BS;
	else
		return ROCKCHIP_SOC_RK3308B;
#elif defined(CONFIG_ROCKCHIP_RK3568)
	if (of_machine_is_compatible("rockchip,rk3566"))
		return ROCKCHIP_SOC_RK3566;
	else
		return ROCKCHIP_SOC_RK3568;
#else
	return 0;
#endif
}

#define ROCKCHIP_SOC(id, ID) \
static inline bool soc_is_##id(void) \
{ \
	int soc_id = rockchip_soc_id(); \
	if (soc_id) \
		return ((soc_id & ROCKCHIP_SOC_MASK) == ROCKCHIP_SOC_ ##ID); \
	return false; \
}

ROCKCHIP_SOC(px30, PX30)
ROCKCHIP_SOC(px30s, PX30S)
ROCKCHIP_SOC(rk3126, RK3126)
ROCKCHIP_SOC(rk3126b, RK3126B)
ROCKCHIP_SOC(rk3126c, RK3126C)
ROCKCHIP_SOC(rk3128, RK3128)
ROCKCHIP_SOC(rk3288, RK3288)
ROCKCHIP_SOC(rk3288w, RK3288W)
ROCKCHIP_SOC(rk3308, RK3308)
ROCKCHIP_SOC(rk3308b, RK3308B)
ROCKCHIP_SOC(rk3308bs, RK3308BS)
ROCKCHIP_SOC(rk3566, RK3566)
ROCKCHIP_SOC(rk3568, RK3568)

#endif
