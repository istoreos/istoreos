/*
 * Copyright (c) 2020 Rockchip Electronics Co., Ltd
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */
#include <common.h>
#include <clk.h>
#include <dm.h>
#include <asm/io.h>
#include <asm/arch-rockchip/cpu.h>
#include <asm/arch-rockchip/hardware.h>
#include <asm/arch-rockchip/grf_rk3568.h>
#include <asm/arch-rockchip/rk_atags.h>
#include <linux/libfdt.h>
#include <fdt_support.h>
#include <asm/arch-rockchip/clock.h>
#include <dt-bindings/clock/rk3568-cru.h>

DECLARE_GLOBAL_DATA_PTR;

#define PMUGRF_BASE		0xfdc20000
#define GRF_BASE		0xfdc60000
#define GRF_GPIO1B_IOMUX_H	0x0C
#define GRF_GPIO1C_IOMUX_L	0x10
#define GRF_GPIO1C_IOMUX_H	0x14
#define GRF_GPIO1D_IOMUX_L	0x18
#define GRF_GPIO1D_IOMUX_H	0x1C
#define GRF_GPIO1B_DS_2		0x218
#define GRF_GPIO1B_DS_3		0x21c
#define GRF_GPIO1C_DS_0		0x220
#define GRF_GPIO1C_DS_1		0x224
#define GRF_GPIO1C_DS_2		0x228
#define GRF_GPIO1C_DS_3		0x22c
#define GRF_GPIO1D_DS_0		0x230
#define GRF_GPIO1D_DS_1		0x234
#define GRF_GPIO1D_DS_2		0x238
#define GRF_SOC_CON4		0x510
#define PMU_BASE_ADDR		0xfdd90000
#define PMU_NOC_AUTO_CON0	(0x70)
#define PMU_NOC_AUTO_CON1	(0x74)
#define CRU_BASE		0xfdd20000
#define CRU_SOFTRST_CON26	0x468
#define CRU_SOFTRST_CON28	0x470
#define SGRF_BASE		0xFDD18000
#define SGRF_SOC_CON3		0xC
#define SGRF_SOC_CON4		0x10
#define PMUGRF_SOC_CON15	0xfdc20100
#define CPU_GRF_BASE		0xfdc30000
#define GRF_CORE_PVTPLL_CON0	(0x10)
#define USBPHY_U3_GRF		0xfdca0000
#define USBPHY_U3_GRF_CON1	(USBPHY_U3_GRF + 0x04)
#define USBPHY_U2_GRF		0xfdca8000
#define USBPHY_U2_GRF_CON0	(USBPHY_U2_GRF + 0x00)
#define USBPHY_U2_GRF_CON1	(USBPHY_U2_GRF + 0x04)

#define PMU_PWR_GATE_SFTCON	(0xA0)
#define PMU_PWR_DWN_ST		(0x98)
#define PMU_BUS_IDLE_SFTCON0	(0x50)
#define PMU_BUS_IDLE_ST		(0x68)
#define PMU_BUS_IDLE_ACK	(0x60)

#define EBC_PRIORITY_REG	(0xfe158008)

enum {
	/* PMU_GRF_GPIO0C_IOMUX_L */
	GPIO0C1_SHIFT		= 4,
	GPIO0C1_MASK		= GENMASK(6, 4),
	GPIO0C1_GPIO		= 0,
	GPIO0C1_PWM2_M0,
	GPIO0C1_NPU_AVS,
	GPIO0C1_UART0_TX,
	GPIO0C1_MCU_JTAGTDI,

	GPIO0C0_SHIFT		= 0,
	GPIO0C0_MASK		= GENMASK(2, 0),
	GPIO0C0_GPIO		= 0,
	GPIO0C0_PWM1_M0,
	GPIO0C0_GPU_AVS,
	GPIO0C0_UART0_RX,

	/* PMU_GRF_GPIO0D_IOMUX_L */
	GPIO0D1_SHIFT		= 4,
	GPIO0D1_MASK		= GENMASK(6, 4),
	GPIO0D1_GPIO		= 0,
	GPIO0D1_UART2_TXM0,

	GPIO0D0_SHIFT		= 0,
	GPIO0D0_MASK		= GENMASK(2, 0),
	GPIO0D0_GPIO		= 0,
	GPIO0D0_UART2_RXM0,

	/* PMU_GRF_SOC_CON0 */
	UART0_IO_SEL_SHIFT	= 8,
	UART0_IO_SEL_MASK	= GENMASK(9, 8),
	UART0_IO_SEL_M0		= 0,
	UART0_IO_SEL_M1,
	UART0_IO_SEL_M2,
};

enum {
	/* GRF_GPIO1A_IOMUX_L */
	GPIO1A1_SHIFT		= 4,
	GPIO1A1_MASK		= GENMASK(6, 4),
	GPIO1A1_GPIO		= 0,
	GPIO1A1_I2C3_SCLM0,
	GPIO1A1_UART3_TXM0,
	GPIO1A1_CAN1_TXM0,
	GPIO1A1_AUDIOPWM_ROUT,
	GPIO1A1_ACODEC_ADCCLK,
	GPIO1A1_AUDIOPWM_LOUT,

	GPIO1A0_SHIFT		= 0,
	GPIO1A0_MASK		= GENMASK(2, 0),
	GPIO1A0_GPIO		= 0,
	GPIO1A0_I2C3_SDAM0,
	GPIO1A0_UART3_RXM0,
	GPIO1A0_CAN1_RXM0,
	GPIO1A0_AUDIOPWM_LOUT,
	GPIO1A0_ACODEC_ADCDATA,
	GPIO1A0_AUDIOPWM_LOUTP,

	/* GRF_GPIO1A_IOMUX_H */
	GPIO1A6_SHIFT		= 8,
	GPIO1A6_MASK		= GENMASK(10, 8),
	GPIO1A6_GPIO		= 0,
	GPIO1A6_I2S1_LRCKRXM0,
	GPIO1A6_UART4_TXM0,
	GPIO1A6_PDM_CLK0M0,
	GPIO1A6_AUDIOPWM_ROUTP,

	GPIO1A4_SHIFT		= 0,
	GPIO1A4_MASK		= GENMASK(2, 0),
	GPIO1A4_GPIO		= 0,
	GPIO1A4_I2S1_SCLKRXM0,
	GPIO1A4_UART4_RXM0,
	GPIO1A4_PDM_CLK1M0,
	GPIO1A4_SPDIF_TXM0,

	/* GRF_GPIO1D_IOMUX_H */
	GPIO1D6_SHIFT		= 8,
	GPIO1D6_MASK		= GENMASK(10, 8),
	GPIO1D6_GPIO		= 0,
	GPIO1D6_SDMMC0_D1,
	GPIO1D6_UART2_RXM1,
	GPIO1D6_UART6_RXM1,
	GPIO1D6_PWM9_M1,

	GPIO1D5_SHIFT		= 4,
	GPIO1D5_MASK		= GENMASK(6, 4),
	GPIO1D5_GPIO		= 0,
	GPIO1D5_SDMMC0_D0,
	GPIO1D5_UART2_TXM1,
	GPIO1D5_UART6_TXM1,
	GPIO1D5_PWM8_M1,

	/* GRF_GPIO2A_IOMUX_L */
	GPIO2A3_SHIFT		= 12,
	GPIO2A3_MASK		= GENMASK(14, 12),
	GPIO2A3_GPIO		= 0,
	GPIO2A3_SDMMC1_D0,
	GPIO2A3_GMAC0_RXD2,
	GPIO2A3_UART6_RXM0,

	GPIO2A2_SHIFT		= 8,
	GPIO2A2_MASK		= GENMASK(10, 8),
	GPIO2A2_GPIO		= 0,
	GPIO2A2_SDMMC0_CLK,
	GPIO2A2_TEST_CLKOUT,
	GPIO2A2_UART5_TXM0,
	GPIO2A2_CAN0_RXM1,

	GPIO2A1_SHIFT		= 4,
	GPIO2A1_MASK		= GENMASK(6, 4),
	GPIO2A1_GPIO		= 0,
	GPIO2A1_SDMMC0_CMD,
	GPIO2A1_PWM10_M1,
	GPIO2A1_UART5_RXM0,
	GPIO2A1_CAN0_TXM1,

	/* GRF_GPIO2A_IOMUX_H */
	GPIO2A7_SHIFT		= 12,
	GPIO2A7_MASK		= GENMASK(14, 12),
	GPIO2A7_GPIO		= 0,
	GPIO2A7_SDMMC1_CMD,
	GPIO2A7_GMAC0_TXD3,
	GPIO2A7_UART9_RXM0,

	GPIO2A6_SHIFT		= 8,
	GPIO2A6_MASK		= GENMASK(10, 8),
	GPIO2A6_GPIO		= 0,
	GPIO2A6_SDMMC1_D3,
	GPIO2A6_GMAC0_TXD2,
	GPIO2A6_UART7_TXM0,

	GPIO2A5_SHIFT		= 4,
	GPIO2A5_MASK		= GENMASK(6, 4),
	GPIO2A5_GPIO		= 0,
	GPIO2A5_SDMMC1_D2,
	GPIO2A5_GMAC0_RXCLK,
	GPIO2A5_UART7_RXM0,

	GPIO2A4_SHIFT		= 0,
	GPIO2A4_MASK		= GENMASK(2, 0),
	GPIO2A4_GPIO		= 0,
	GPIO2A4_SDMMC1_D1,
	GPIO2A4_GMAC0_RXD3,
	GPIO2A4_UART6_TXM0,

	/* GRF_GPIO2B_IOMUX_L */
	GPIO2B3_SHIFT		= 12,
	GPIO2B3_MASK		= GENMASK(14, 12),
	GPIO2B3_GPIO		= 0,
	GPIO2B3_GMAC0_TXD0,
	GPIO2B3_UART1_RXM0,

	GPIO2B0_SHIFT		= 0,
	GPIO2B0_MASK		= GENMASK(2, 0),
	GPIO2B0_GPIO		= 0,
	GPIO2B0_SDMMC1_CLK,
	GPIO2B0_GMAC0_TXCLK,
	GPIO2B0_UART9_TXM0,

	/* GRF_GPIO2B_IOMUX_H */
	GPIO2B4_SHIFT		= 0,
	GPIO2B4_MASK		= GENMASK(2, 0),
	GPIO2B4_GPIO		= 0,
	GPIO2B4_GMAC0_TXD1,
	GPIO2B4_UART1_TXM0,

	/* GRF_GPIO2C_IOMUX_L */
	GPIO2C2_SHIFT		= 8,
	GPIO2C2_MASK		= GENMASK(10, 8),
	GPIO2C2_GPIO		= 0,
	GPIO2C2_GMAC0_MCLKINOUT	= 2,

	/* GRF_GPIO2C_IOMUX_H */
	GPIO2C6_SHIFT		= 8,
	GPIO2C6_MASK		= GENMASK(10, 8),
	GPIO2C6_GPIO		= 0,
	GPIO2C6_CLK32K_OUT1,
	GPIO2C6_UART8_RXM0,
	GPIO2C6_SPI1_CS1M0,

	GPIO2C5_SHIFT		= 4,
	GPIO2C5_MASK		= GENMASK(6, 4),
	GPIO2C5_GPIO		= 0,
	GPIO2C5_I2S2_SDIM0,
	GPIO2C5_GMAC0_RXER,
	GPIO2C5_UART8_TXM0,
	GPIO2C5_SPI2_CS1M0,

	/* GRF_GPIO2D_IOMUX_H */
	GPIO2D7_SHIFT		= 12,
	GPIO2D7_MASK		= GENMASK(14, 12),
	GPIO2D7_GPIO		= 0,
	GPIO2D7_LCDC_D7,
	GPIO2D7_BT656_D7M0,
	GPIO2D7_SPI2_MISOM1,
	GPIO2D7_UART8_TXM1,
	GPIO2D7_I2S1_SDO0M2,

	/* GRF_GPIO3A_IOMUX_L */
	GPIO3A0_SHIFT		= 0,
	GPIO3A0_MASK		= GENMASK(2, 0),
	GPIO3A0_GPIO		= 0,
	GPIO3A0_LCDC_CLK,
	GPIO3A0_BT656_CLKM0,
	GPIO3A0_SPI2_CLKM1,
	GPIO3A0_UART8_RXM1,
	GPIO3A0_I2S1_SDO1M2,

	/* GRF_GPIO3B_IOMUX_L */
	GPIO3B2_SHIFT		= 8,
	GPIO3B2_MASK		= GENMASK(10, 8),
	GPIO3B2_GPIO		= 0,
	GPIO3B2_LCDC_D17,
	GPIO3B2_BT1120_D8,
	GPIO3B2_GMAC1_RXD1M0,
	GPIO3B2_UART4_TXM1,
	GPIO3B2_PWM9_M0,

	GPIO3B1_SHIFT		= 4,
	GPIO3B1_MASK		= GENMASK(6, 4),
	GPIO3B1_GPIO		= 0,
	GPIO3B1_LCDC_D16,
	GPIO3B1_BT1120_D7,
	GPIO3B1_GMAC1_RXD0M0,
	GPIO3B1_UART4_RXM1,
	GPIO3B1_PWM8_M0,

	/* GRF_GPIO3B_IOMUX_H */
	GPIO3B7_SHIFT		= 12,
	GPIO3B7_MASK		= GENMASK(14, 12),
	GPIO3B7_GPIO		= 0,
	GPIO3B7_LCDC_D22,
	GPIO3B7_PWM12_M0,
	GPIO3B7_GMAC1_TXENM0,
	GPIO3B7_UART3_TXM1,
	GPIO3B7_PDM_SDI2M2,

	/* GRF_GPIO3C_IOMUX_L */
	GPIO3C3_SHIFT		= 12,
	GPIO3C3_MASK		= GENMASK(14, 12),
	GPIO3C3_GPIO		= 0,
	GPIO3C3_LCDC_DEN,
	GPIO3C3_BT1120_D15,
	GPIO3C3_SPI1_CLKM1,
	GPIO3C3_UART5_RXM1,
	GPIO3C3_I2S1_SCLKRXM,

	GPIO3C2_SHIFT		= 8,
	GPIO3C2_MASK		= GENMASK(10, 8),
	GPIO3C2_GPIO		= 0,
	GPIO3C2_LCDC_VSYNC,
	GPIO3C2_BT1120_D14,
	GPIO3C2_SPI1_MISOM1,
	GPIO3C2_UART5_TXM1,
	GPIO3C2_I2S1_SDO3M2,

	GPIO3C0_SHIFT		= 0,
	GPIO3C0_MASK		= GENMASK(2, 0),
	GPIO3C0_GPIO		= 0,
	GPIO3C0_LCDC_D23,
	GPIO3C0_PWM13_M0,
	GPIO3C0_GMAC1_MCLKINOUTM0,
	GPIO3C0_UART3_RXM1,
	GPIO3C0_PDM_SDI3M2,

	/* GRF_GPIO3C_IOMUX_H */
	GPIO3C5_SHIFT		= 4,
	GPIO3C5_MASK		= GENMASK(6, 4),
	GPIO3C5_GPIO		= 0,
	GPIO3C5_PWM15_IRM0,
	GPIO3C5_SPDIF_TXM1,
	GPIO3C5_GMAC1_MDIOM0,
	GPIO3C5_UART7_RXM1,
	GPIO3C5_I2S1_LRCKRXM2,

	GPIO3C4_SHIFT		= 0,
	GPIO3C4_MASK		= GENMASK(2, 0),
	GPIO3C4_GPIO		= 0,
	GPIO3C4_PWM14_M0,
	GPIO3C4_VOP_PWMM1,
	GPIO3C4_GMAC1_MDCM0,
	GPIO3C4_UART7_TXM1,
	GPIO3C4_PDM_CLK1M2,

	/* GRF_GPIO3D_IOMUX_H */
	GPIO3D7_SHIFT		= 12,
	GPIO3D7_MASK		= GENMASK(14, 12),
	GPIO3D7_GPIO		= 0,
	GPIO3D7_CIF_D9,
	GPIO3D7_EBC_SDDO9,
	GPIO3D7_GMAC1_TXD3M1,
	GPIO3D7_UART1_RXM1,
	GPIO3D7_PDM_SDI0M1,

	GPIO3D6_SHIFT		= 8,
	GPIO3D6_MASK		= GENMASK(10, 8),
	GPIO3D6_GPIO		= 0,
	GPIO3D6_CIF_D8,
	GPIO3D6_EBC_SDDO8,
	GPIO3D6_GMAC1_TXD2M1,
	GPIO3D6_UART1_TXM1,
	GPIO3D6_PDM_CLK0M1,

	/* GRF_GPIO4A_IOMUX_L */
	GPIO4A3_SHIFT		= 12,
	GPIO4A3_MASK		= GENMASK(14, 12),
	GPIO4A3_GPIO		= 0,
	GPIO4A3_CIF_D13,
	GPIO4A3_EBC_SDDO13,
	GPIO4A3_GMAC1_RXCLKM1,
	GPIO4A3_UART7_RXM2,
	GPIO4A3_PDM_SDI3M1,

	GPIO4A2_SHIFT		= 8,
	GPIO4A2_MASK		= GENMASK(10, 8),
	GPIO4A2_GPIO		= 0,
	GPIO4A2_CIF_D12,
	GPIO4A2_EBC_SDDO12,
	GPIO4A2_GMAC1_RXD3M1,
	GPIO4A2_UART7_TXM2,
	GPIO4A2_PDM_SDI2M1,

	/* GRF_GPIO4A_IOMUX_H */
	GPIO4A5_SHIFT		= 4,
	GPIO4A5_MASK		= GENMASK(6, 4),
	GPIO4A5_GPIO		= 0,
	GPIO4A5_CIF_D15,
	GPIO4A5_EBC_SDDO15,
	GPIO4A5_GMAC1_TXD1M1,
	GPIO4A5_UART9_RXM2,
	GPIO4A5_I2S2_LRCKRXM1,

	GPIO4A4_SHIFT		= 0,
	GPIO4A4_MASK		= GENMASK(2, 0),
	GPIO4A4_GPIO		= 0,
	GPIO4A4_CIF_D14,
	GPIO4A4_EBC_SDDO14,
	GPIO4A4_GMAC1_TXD0M1,
	GPIO4A4_UART9_TXM2,
	GPIO4A4_I2S2_LRCKTXM1,

	/* GRF_GPIO4C_IOMUX_L */
	GPIO4C1_SHIFT		= 4,
	GPIO4C1_MASK		= GENMASK(6, 4),
	GPIO4C1_GPIO		= 0,
	GPIO4C1_CIF_CLKIN,
	GPIO4C1_EBC_SDCLK,
	GPIO4C1_GMAC1_MCLKINOUTM1,

	/* GRF_GPIO4C_IOMUX_H */
	GPIO4C6_SHIFT		= 8,
	GPIO4C6_MASK		= GENMASK(10, 8),
	GPIO4C6_GPIO		= 0,
	GPIO4C6_PWM13_M1,
	GPIO4C6_SPI3_CS0M1,
	GPIO4C6_SATA0_ACTLED,
	GPIO4C6_UART9_RXM1,
	GPIO4C6_I2S3_SDIM1,

	GPIO4C5_SHIFT		= 4,
	GPIO4C5_MASK		= GENMASK(6, 4),
	GPIO4C5_GPIO		= 0,
	GPIO4C5_PWM12_M1,
	GPIO4C5_SPI3_MISOM1,
	GPIO4C5_SATA1_ACTLED,
	GPIO4C5_UART9_TXM1,
	GPIO4C5_I2S3_SDOM1,

	/* GRF_IOFUNC_SEL3 */
	UART4_IO_SEL_SHIFT	= 14,
	UART4_IO_SEL_MASK	= GENMASK(14, 14),
	UART4_IO_SEL_M0		= 0,
	UART4_IO_SEL_M1,

	UART3_IO_SEL_SHIFT	= 12,
	UART3_IO_SEL_MASK	= GENMASK(12, 12),
	UART3_IO_SEL_M0		= 0,
	UART3_IO_SEL_M1,

	UART2_IO_SEL_SHIFT	= 10,
	UART2_IO_SEL_MASK	= GENMASK(11, 10),
	UART2_IO_SEL_M0		= 0,
	UART2_IO_SEL_M1,

	UART1_IO_SEL_SHIFT	= 8,
	UART1_IO_SEL_MASK	= GENMASK(8, 8),
	UART1_IO_SEL_M0		= 0,
	UART1_IO_SEL_M1,

	/* GRF_IOFUNC_SEL4 */
	UART9_IO_SEL_SHIFT	= 8,
	UART9_IO_SEL_MASK	= GENMASK(9, 8),
	UART9_IO_SEL_M0		= 0,
	UART9_IO_SEL_M1,
	UART9_IO_SEL_M2,

	UART8_IO_SEL_SHIFT	= 6,
	UART8_IO_SEL_MASK	= GENMASK(6, 6),
	UART8_IO_SEL_M0		= 0,
	UART8_IO_SEL_M1,

	UART7_IO_SEL_SHIFT	= 4,
	UART7_IO_SEL_MASK	= GENMASK(5, 4),
	UART7_IO_SEL_M0		= 0,
	UART7_IO_SEL_M1,
	UART7_IO_SEL_M2,

	UART6_IO_SEL_SHIFT	= 2,
	UART6_IO_SEL_MASK	= GENMASK(2, 2),
	UART6_IO_SEL_M0		= 0,
	UART6_IO_SEL_M1,

	UART5_IO_SEL_SHIFT	= 0,
	UART5_IO_SEL_MASK	= GENMASK(0, 0),
	UART5_IO_SEL_M0		= 0,
	UART5_IO_SEL_M1,
};

#ifdef CONFIG_ARM64
#include <asm/armv8/mmu.h>

static struct mm_region rk3568_mem_map[] = {
	{
		.virt = 0x0UL,
		.phys = 0x0UL,
		.size = 0xf0000000UL,
		.attrs = PTE_BLOCK_MEMTYPE(MT_NORMAL) |
			 PTE_BLOCK_INNER_SHARE
	}, {
		.virt = 0xf0000000UL,
		.phys = 0xf0000000UL,
		.size = 0x10000000UL,
		.attrs = PTE_BLOCK_MEMTYPE(MT_DEVICE_NGNRNE) |
			 PTE_BLOCK_NON_SHARE |
			 PTE_BLOCK_PXN | PTE_BLOCK_UXN
	}, {
		.virt = 0x300000000,
		.phys = 0x300000000,
		.size = 0x0c0c00000,
		.attrs = PTE_BLOCK_MEMTYPE(MT_DEVICE_NGNRNE) |
			 PTE_BLOCK_NON_SHARE |
			 PTE_BLOCK_PXN | PTE_BLOCK_UXN
	}, {
		/* List terminator */
		0,
	}
};

struct mm_region *mem_map = rk3568_mem_map;
#endif

void board_debug_uart_init(void)
{
#if defined(CONFIG_DEBUG_UART_BASE) && (CONFIG_DEBUG_UART_BASE == 0xfdd50000)
	static struct rk3568_pmugrf * const pmugrf = (void *)PMUGRF_BASE;
	/* UART0 M0 */
	rk_clrsetreg(&pmugrf->pmu_soc_con0, UART0_IO_SEL_MASK,
		     UART0_IO_SEL_M0 << UART0_IO_SEL_SHIFT);

	/* Switch iomux */
	rk_clrsetreg(&pmugrf->pmu_gpio0c_iomux_l,
		     GPIO0C1_MASK | GPIO0C0_MASK,
		     GPIO0C1_UART0_TX << GPIO0C1_SHIFT |
		     GPIO0C0_UART0_RX << GPIO0C0_SHIFT);

#elif defined(CONFIG_DEBUG_UART_BASE) && (CONFIG_DEBUG_UART_BASE == 0xfe650000)
	static struct rk3568_grf * const grf = (void *)GRF_BASE;

#if defined(CONFIG_ROCKCHIP_UART_MUX_SEL_M) && \
	(CONFIG_ROCKCHIP_UART_MUX_SEL_M == 0)
	/* UART1 M0 */
	rk_clrsetreg(&grf->iofunc_sel3, UART1_IO_SEL_MASK,
		     UART1_IO_SEL_M0 << UART1_IO_SEL_SHIFT);

	/* Switch iomux */
	rk_clrsetreg(&grf->gpio2b_iomux_l,
		     GPIO2B3_MASK, GPIO2B3_UART1_RXM0 << GPIO2B3_SHIFT);
	rk_clrsetreg(&grf->gpio2b_iomux_h,
		     GPIO2B4_MASK, GPIO2B4_UART1_TXM0 << GPIO2B4_SHIFT);
#else
	/* UART1 M1 */
	rk_clrsetreg(&grf->iofunc_sel3, UART1_IO_SEL_MASK,
		     UART1_IO_SEL_M1 << UART1_IO_SEL_SHIFT);

	/* Switch iomux */
	rk_clrsetreg(&grf->gpio3d_iomux_h,
		     GPIO3D7_MASK | GPIO3D6_MASK,
		     GPIO3D7_UART1_RXM1 << GPIO3D7_SHIFT |
		     GPIO3D6_UART1_TXM1 << GPIO3D6_SHIFT);
#endif
#elif defined(CONFIG_DEBUG_UART_BASE) && (CONFIG_DEBUG_UART_BASE == 0xfe660000)
	static struct rk3568_grf * const grf = (void *)GRF_BASE;

#if defined(CONFIG_ROCKCHIP_UART_MUX_SEL_M) && \
	(CONFIG_ROCKCHIP_UART_MUX_SEL_M == 0)
	static struct rk3568_pmugrf * const pmugrf = (void *)PMUGRF_BASE;
	/* UART2 M0 */
	rk_clrsetreg(&grf->iofunc_sel3, UART2_IO_SEL_MASK,
		     UART2_IO_SEL_M0 << UART2_IO_SEL_SHIFT);

	/* Switch iomux */
	rk_clrsetreg(&pmugrf->pmu_gpio0d_iomux_l,
		     GPIO0D1_MASK | GPIO0D0_MASK,
		     GPIO0D1_UART2_TXM0 << GPIO0D1_SHIFT |
		     GPIO0D0_UART2_RXM0 << GPIO0D0_SHIFT);
#else
	/* UART2 M1 */
	rk_clrsetreg(&grf->iofunc_sel3, UART2_IO_SEL_MASK,
		     UART2_IO_SEL_M1 << UART2_IO_SEL_SHIFT);

	/* Switch iomux */
	rk_clrsetreg(&grf->gpio1d_iomux_h,
		     GPIO1D6_MASK | GPIO1D5_MASK,
		     GPIO1D6_UART2_RXM1 << GPIO1D6_SHIFT |
		     GPIO1D5_UART2_TXM1 << GPIO1D5_SHIFT);
#endif
#elif defined(CONFIG_DEBUG_UART_BASE) && (CONFIG_DEBUG_UART_BASE == 0xfe670000)
	static struct rk3568_grf * const grf = (void *)GRF_BASE;

#if defined(CONFIG_ROCKCHIP_UART_MUX_SEL_M) && \
	(CONFIG_ROCKCHIP_UART_MUX_SEL_M == 0)
	/* UART3 M0 */
	rk_clrsetreg(&grf->iofunc_sel3, UART3_IO_SEL_MASK,
		     UART3_IO_SEL_M0 << UART3_IO_SEL_SHIFT);

	/* Switch iomux */
	rk_clrsetreg(&grf->gpio1a_iomux_l,
		     GPIO1A1_MASK | GPIO1A0_MASK,
		     GPIO1A1_UART3_TXM0 << GPIO1A1_SHIFT |
		     GPIO1A0_UART3_RXM0 << GPIO1A0_SHIFT);
#else
	/* UART3 M1 */
	rk_clrsetreg(&grf->iofunc_sel3, UART3_IO_SEL_MASK,
		     UART3_IO_SEL_M1 << UART3_IO_SEL_SHIFT);

	/* Switch iomux */
	rk_clrsetreg(&grf->gpio3b_iomux_h,
		     GPIO3B7_MASK, GPIO3B7_UART3_TXM1 << GPIO3B7_SHIFT);
	rk_clrsetreg(&grf->gpio3c_iomux_l,
		     GPIO3C0_MASK, GPIO3C0_UART3_RXM1 << GPIO3C0_SHIFT);
#endif
#elif defined(CONFIG_DEBUG_UART_BASE) && (CONFIG_DEBUG_UART_BASE == 0xfe680000)
	static struct rk3568_grf * const grf = (void *)GRF_BASE;

#if defined(CONFIG_ROCKCHIP_UART_MUX_SEL_M) && \
	(CONFIG_ROCKCHIP_UART_MUX_SEL_M == 0)
	/* UART4 M0 */
	rk_clrsetreg(&grf->iofunc_sel3, UART4_IO_SEL_MASK,
		     UART4_IO_SEL_M0 << UART4_IO_SEL_SHIFT);

	/* Switch iomux */
	rk_clrsetreg(&grf->gpio1a_iomux_h,
		     GPIO1A6_MASK | GPIO1A4_MASK,
		     GPIO1A6_UART4_TXM0 << GPIO1A6_SHIFT |
		     GPIO1A4_UART4_RXM0 << GPIO1A4_SHIFT);
#else
	/* UART4 M1 */
	rk_clrsetreg(&grf->iofunc_sel3, UART4_IO_SEL_MASK,
		     UART4_IO_SEL_M1 << UART4_IO_SEL_SHIFT);

	/* Switch iomux */
	rk_clrsetreg(&grf->gpio3b_iomux_l,
		     GPIO3B2_MASK | GPIO3B1_MASK,
		     GPIO3B2_UART4_TXM1 << GPIO3B2_SHIFT |
		     GPIO3B1_UART4_RXM1 << GPIO3B1_SHIFT);
#endif
#elif defined(CONFIG_DEBUG_UART_BASE) && (CONFIG_DEBUG_UART_BASE == 0xfe690000)
	static struct rk3568_grf * const grf = (void *)GRF_BASE;

#if defined(CONFIG_ROCKCHIP_UART_MUX_SEL_M) && \
	(CONFIG_ROCKCHIP_UART_MUX_SEL_M == 0)
	/* UART5 M0 */
	rk_clrsetreg(&grf->iofunc_sel4, UART5_IO_SEL_MASK,
		     UART5_IO_SEL_M0 << UART5_IO_SEL_SHIFT);

	/* Switch iomux */
	rk_clrsetreg(&grf->gpio2a_iomux_l,
		     GPIO2A2_MASK | GPIO2A1_MASK,
		     GPIO2A2_UART5_TXM0 << GPIO2A2_SHIFT |
		     GPIO2A1_UART5_RXM0 << GPIO2A1_SHIFT);
#else
	/* UART5 M1 */
	rk_clrsetreg(&grf->iofunc_sel4, UART5_IO_SEL_MASK,
		     UART5_IO_SEL_M1 << UART5_IO_SEL_SHIFT);

	/* Switch iomux */
	rk_clrsetreg(&grf->gpio3c_iomux_l,
		     GPIO3C3_MASK | GPIO3C2_MASK,
		     GPIO3C3_UART5_RXM1 << GPIO3C3_SHIFT |
		     GPIO3C2_UART5_TXM1 << GPIO3C2_SHIFT);
#endif
#elif defined(CONFIG_DEBUG_UART_BASE) && (CONFIG_DEBUG_UART_BASE == 0xfe6a0000)
	static struct rk3568_grf * const grf = (void *)GRF_BASE;

#if defined(CONFIG_ROCKCHIP_UART_MUX_SEL_M) && \
	(CONFIG_ROCKCHIP_UART_MUX_SEL_M == 0)
	/* UART6 M0 */
	rk_clrsetreg(&grf->iofunc_sel4, UART6_IO_SEL_MASK,
		     UART6_IO_SEL_M0 << UART6_IO_SEL_SHIFT);

	/* Switch iomux */
	rk_clrsetreg(&grf->gpio2a_iomux_l,
		     GPIO2A3_MASK, GPIO2A3_UART6_RXM0 << GPIO2A3_SHIFT);
	rk_clrsetreg(&grf->gpio2a_iomux_h,
		     GPIO2A4_MASK, GPIO2A4_UART6_TXM0 << GPIO2A4_SHIFT);
#else
	/* UART6 M1 */
	rk_clrsetreg(&grf->iofunc_sel4, UART6_IO_SEL_MASK,
		     UART6_IO_SEL_M1 << UART6_IO_SEL_SHIFT);

	/* Switch iomux */
	rk_clrsetreg(&grf->gpio1d_iomux_h,
		     GPIO1D6_MASK | GPIO1D5_MASK,
		     GPIO1D6_UART6_RXM1 << GPIO1D6_SHIFT |
		     GPIO1D5_UART6_TXM1 << GPIO1D5_SHIFT);
#endif
#elif defined(CONFIG_DEBUG_UART_BASE) && (CONFIG_DEBUG_UART_BASE == 0xfe6b0000)
	static struct rk3568_grf * const grf = (void *)GRF_BASE;

#if defined(CONFIG_ROCKCHIP_UART_MUX_SEL_M) && \
	(CONFIG_ROCKCHIP_UART_MUX_SEL_M == 0)
	/* UART7 M0 */
	rk_clrsetreg(&grf->iofunc_sel4, UART7_IO_SEL_MASK,
		     UART7_IO_SEL_M0 << UART7_IO_SEL_SHIFT);

	/* Switch iomux */
	rk_clrsetreg(&grf->gpio2a_iomux_h,
		     GPIO2A6_MASK | GPIO2A5_MASK,
		     GPIO2A6_UART7_TXM0 << GPIO2A6_SHIFT |
		     GPIO2A5_UART7_RXM0 << GPIO2A5_SHIFT);
#elif defined(CONFIG_ROCKCHIP_UART_MUX_SEL_M) && \
	(CONFIG_ROCKCHIP_UART_MUX_SEL_M == 1)
	/* UART7 M1 */
	rk_clrsetreg(&grf->iofunc_sel4, UART7_IO_SEL_MASK,
		     UART7_IO_SEL_M1 << UART7_IO_SEL_SHIFT);

	/* Switch iomux */
	rk_clrsetreg(&grf->gpio3c_iomux_h,
		     GPIO3C5_MASK | GPIO3C4_MASK,
		     GPIO3C5_UART7_RXM1 << GPIO3C5_SHIFT |
		     GPIO3C4_UART7_TXM1 << GPIO3C4_SHIFT);
#else
	/* UART7 M2 */
	rk_clrsetreg(&grf->iofunc_sel4, UART7_IO_SEL_MASK,
		     UART7_IO_SEL_M2 << UART7_IO_SEL_SHIFT);

	/* Switch iomux */
	rk_clrsetreg(&grf->gpio4a_iomux_l,
		     GPIO4A3_MASK | GPIO4A2_MASK,
		     GPIO4A3_UART7_RXM2 << GPIO4A3_SHIFT |
		     GPIO4A2_UART7_TXM2 << GPIO4A2_SHIFT);
#endif
#elif defined(CONFIG_DEBUG_UART_BASE) && (CONFIG_DEBUG_UART_BASE == 0xfe6c0000)
	static struct rk3568_grf * const grf = (void *)GRF_BASE;

#if defined(CONFIG_ROCKCHIP_UART_MUX_SEL_M) && \
	(CONFIG_ROCKCHIP_UART_MUX_SEL_M == 0)
	/* UART8 M0 */
	rk_clrsetreg(&grf->iofunc_sel4, UART8_IO_SEL_MASK,
		     UART8_IO_SEL_M0 << UART8_IO_SEL_SHIFT);

	/* Switch iomux */
	rk_clrsetreg(&grf->gpio2c_iomux_h,
		     GPIO2C6_MASK | GPIO2C5_MASK,
		     GPIO2C6_UART8_RXM0 << GPIO2C6_SHIFT |
		     GPIO2C5_UART8_TXM0 << GPIO2C5_SHIFT);
#else
	/* UART8 M1 */
	rk_clrsetreg(&grf->iofunc_sel4, UART8_IO_SEL_MASK,
		     UART8_IO_SEL_M1 << UART8_IO_SEL_SHIFT);

	/* Switch iomux */
	rk_clrsetreg(&grf->gpio2d_iomux_h,
		     GPIO2D7_MASK | GPIO3A0_MASK,
		     GPIO2D7_UART8_TXM1 << GPIO2D7_SHIFT |
		     GPIO3A0_UART8_RXM1 << GPIO3A0_SHIFT);
#endif
#elif defined(CONFIG_DEBUG_UART_BASE) && (CONFIG_DEBUG_UART_BASE == 0xfe6d0000)
	static struct rk3568_grf * const grf = (void *)GRF_BASE;

#if defined(CONFIG_ROCKCHIP_UART_MUX_SEL_M) && \
	(CONFIG_ROCKCHIP_UART_MUX_SEL_M == 0)
	/* UART9 M0 */
	rk_clrsetreg(&grf->iofunc_sel4, UART9_IO_SEL_MASK,
		     UART9_IO_SEL_M0 << UART9_IO_SEL_SHIFT);

	/* Switch iomux */
	rk_clrsetreg(&grf->gpio2a_iomux_h,
		     GPIO2A7_MASK, GPIO2A7_UART9_RXM0 << GPIO2A7_SHIFT);
	rk_clrsetreg(&grf->gpio2b_iomux_l,
		     GPIO2B0_MASK, GPIO2B0_UART9_TXM0 << GPIO2B0_SHIFT);
#elif defined(CONFIG_ROCKCHIP_UART_MUX_SEL_M) && \
	(CONFIG_ROCKCHIP_UART_MUX_SEL_M == 1)
	/* UART9 M1 */
	rk_clrsetreg(&grf->iofunc_sel4, UART9_IO_SEL_MASK,
		     UART9_IO_SEL_M1 << UART9_IO_SEL_SHIFT);

	/* Switch iomux */
	rk_clrsetreg(&grf->gpio4c_iomux_h,
		     GPIO4C6_MASK | GPIO4C5_MASK,
		     GPIO4C6_UART9_RXM1 << GPIO4C6_SHIFT |
		     GPIO4C5_UART9_TXM1 << GPIO4C5_SHIFT);
#else
	/* UART9 M2 */
	rk_clrsetreg(&grf->iofunc_sel4, UART9_IO_SEL_MASK,
		     UART9_IO_SEL_M2 << UART9_IO_SEL_SHIFT);

	/* Switch iomux */
	rk_clrsetreg(&grf->gpio4a_iomux_h,
		     GPIO4A5_MASK | GPIO4A4_MASK,
		     GPIO4A5_UART9_RXM2 << GPIO4A5_SHIFT |
		     GPIO4A4_UART9_TXM2 << GPIO4A4_SHIFT);
#endif
#endif
}

#if defined(CONFIG_SPL_BUILD) && !defined(CONFIG_TPL_BUILD)
static void qos_priority_init(void)
{
	u32 delay;

	/* enable all pd except npu and gpu */
	writel(0xffff0000 & ~(BIT(0 + 16) | BIT(1 + 16)),
	       PMU_BASE_ADDR + PMU_PWR_GATE_SFTCON);
	delay = 1000;
	do {
		udelay(1);
		delay--;
		if (delay == 0) {
			printf("Fail to set domain.");
			hang();
		}
	} while (readl(PMU_BASE_ADDR + PMU_PWR_DWN_ST) & ~(BIT(0) | BIT(1)));

	/* release all idle request except npu and gpu */
	writel(0xffff0000 & ~(BIT(1 + 16) | BIT(2 + 16)),
	       PMU_BASE_ADDR + PMU_BUS_IDLE_SFTCON0);

	delay = 1000;
	/* wait ack status */
	do {
		udelay(1);
		delay--;
		if (delay == 0) {
			printf("Fail to get ack on domain.\n");
			hang();
		}
	} while (readl(PMU_BASE_ADDR + PMU_BUS_IDLE_ACK) & ~(BIT(1) | BIT(2)));

	delay = 1000;
	/* wait idle status */
	do {
		udelay(1);
		delay--;
		if (delay == 0) {
			printf("Fail to set idle on domain.\n");
			hang();
		}
	} while (readl(PMU_BASE_ADDR + PMU_BUS_IDLE_ST) & ~(BIT(1) | BIT(2)));

	writel(0x303, EBC_PRIORITY_REG);
}
#endif

int arch_cpu_init(void)
{
#ifdef CONFIG_SPL_BUILD
	/*
	 * When perform idle operation, corresponding clock can
	 * be opened or gated automatically.
	 */
	writel(0xffffffff, PMU_BASE_ADDR + PMU_NOC_AUTO_CON0);
	writel(0x000f000f, PMU_BASE_ADDR + PMU_NOC_AUTO_CON1);

	/* Set the emmc sdmmc0 to secure */
	writel(((0x3 << 11 | 0x1 << 4) << 16), SGRF_BASE + SGRF_SOC_CON4);
	/* set the emmc ds to level 2 */
	writel(0x3f3f0707, GRF_BASE + GRF_GPIO1B_DS_2);
	writel(0x3f3f0707, GRF_BASE + GRF_GPIO1B_DS_3);
	writel(0x3f3f0707, GRF_BASE + GRF_GPIO1C_DS_0);
	writel(0x3f3f0707, GRF_BASE + GRF_GPIO1C_DS_1);
	writel(0x3f3f0707, GRF_BASE + GRF_GPIO1C_DS_2);
	writel(0x3f3f0707, GRF_BASE + GRF_GPIO1C_DS_3);

#if defined(CONFIG_ROCKCHIP_SFC)
	/* Set the fspi to secure */
	writel(((0x1 << 14) << 16) | (0x0 << 14), SGRF_BASE + SGRF_SOC_CON3);
#endif

#ifndef CONFIG_TPL_BUILD
	/* set the fspi d0~3 cs0 to level 2 */
	if (get_bootdev_by_brom_bootsource() == BOOT_TYPE_SPI_NOR ||
	    get_bootdev_by_brom_bootsource() == BOOT_TYPE_SPI_NAND) {
		writel(0x3f000700, GRF_BASE + GRF_GPIO1C_DS_3);
		writel(0x3f000700, GRF_BASE + GRF_GPIO1D_DS_0);
		writel(0x3f3f0707, GRF_BASE + GRF_GPIO1D_DS_1);
		writel(0x003f0007, GRF_BASE + GRF_GPIO1D_DS_2);
	}
#endif

	/* Set core pvtpll ring length */
	writel(0x00ff002b, CPU_GRF_BASE + GRF_CORE_PVTPLL_CON0);

	/*
	 * Assert reset the pipephy0, pipephy1 and pipephy2,
	 * and de-assert reset them in Kernel combphy driver.
	 */
	 writel(0x02a002a0, CRU_BASE + CRU_SOFTRST_CON28);

	 /*
	  * Set USB 2.0 PHY0 port1 and PHY1 port0 and port1
	  * enter suspend mode to to save power. And USB 2.0
	  * PHY0 port0 for OTG interface still in normal mode.
	  */
	 writel(0x01ff01d1, USBPHY_U3_GRF_CON1);
	 writel(0x01ff01d1, USBPHY_U2_GRF_CON0);
	 writel(0x01ff01d1, USBPHY_U2_GRF_CON1);

#ifndef CONFIG_TPL_BUILD
	qos_priority_init();
#endif
#elif defined(CONFIG_SUPPORT_USBPLUG)
	/*
	 * When perform idle operation, corresponding clock can
	 * be opened or gated automatically.
	 */
	writel(0xffffffff, PMU_BASE_ADDR + PMU_NOC_AUTO_CON0);
	writel(0x000f000f, PMU_BASE_ADDR + PMU_NOC_AUTO_CON1);

	writel(0x00030000, SGRF_BASE + SGRF_SOC_CON4); /* usb3otg0 master secure setting */

	/* Set the emmc sdmmc0 to secure */
	writel(((0x3 << 11 | 0x1 << 4) << 16), SGRF_BASE + SGRF_SOC_CON4);
	/* set the emmc ds to level 2 */
	writel(0x3f3f0707, GRF_BASE + GRF_GPIO1B_DS_2);
	writel(0x3f3f0707, GRF_BASE + GRF_GPIO1B_DS_3);
	writel(0x3f3f0707, GRF_BASE + GRF_GPIO1C_DS_0);
	writel(0x3f3f0707, GRF_BASE + GRF_GPIO1C_DS_1);
	writel(0x3f3f0707, GRF_BASE + GRF_GPIO1C_DS_2);
	writel(0x3f3f0707, GRF_BASE + GRF_GPIO1C_DS_3);

	/* emmc and sfc iomux */
	writel((0x7777UL << 16) | (0x1111), GRF_BASE + GRF_GPIO1B_IOMUX_H);
	writel((0x7777UL << 16) | (0x1111), GRF_BASE + GRF_GPIO1C_IOMUX_L);
	writel((0x7777UL << 16) | (0x2111), GRF_BASE + GRF_GPIO1C_IOMUX_H);
	writel((0x7777UL << 16) | (0x1111), GRF_BASE + GRF_GPIO1D_IOMUX_L);
	writel(((7 << 0) << 16) | (1 << 0), GRF_BASE + GRF_GPIO1D_IOMUX_H);

	/* Set the fspi to secure */
	writel(((0x1 << 14) << 16) | (0x0 << 14), SGRF_BASE + SGRF_SOC_CON3);
#endif

	return 0;
}

#ifdef CONFIG_SPL_BUILD
int spl_fit_standalone_release(char *id, uintptr_t entry_point)
{
	/* Reset the scr1 */
	writel(0x04000400, CRU_BASE + CRU_SOFTRST_CON26);
	udelay(100);
	/* set the scr1 addr */
	writel((0xffff0000) | (entry_point >> 16), GRF_BASE + GRF_SOC_CON4);
	udelay(10);
	/* release the scr1 */
	writel(0x04000000, CRU_BASE + CRU_SOFTRST_CON26);

	return 0;
}
#endif

#if CONFIG_IS_ENABLED(CLK_SCMI)
#include <dm.h>
/*
 * armclk: 1104M:
 *	rockchip,clk-init = <1104000000>,
 *	vdd_cpu : regulator-init-microvolt = <825000>;
 * armclk: 1416M(by default):
 *	rockchip,clk-init = <1416000000>,
 *	vdd_cpu : regulator-init-microvolt = <900000>;
 * armclk: 1608M:
 *	rockchip,clk-init = <1608000000>,
 *	vdd_cpu : regulator-init-microvolt = <975000>;
 */

int set_armclk_rate(void)
{
	struct clk clk;
	u32 *rates = NULL;
	int ret, size, num_rates;

	ret = rockchip_get_scmi_clk(&clk.dev);
	if (ret) {
		printf("Failed to get scmi clk dev\n");
		return ret;
	}

	size = dev_read_size(clk.dev, "rockchip,clk-init");
	if (size < 0)
		return 0;

	num_rates = size / sizeof(u32);
	rates = calloc(num_rates, sizeof(u32));
	if (!rates)
		return -ENOMEM;

	ret = dev_read_u32_array(clk.dev, "rockchip,clk-init",
				 rates, num_rates);
	if (ret) {
		printf("Cannot get rockchip,clk-init reg\n");
		return -EINVAL;
	}
	clk.id = 0;
	ret = clk_set_rate(&clk, rates[clk.id]);
	if (ret < 0) {
		printf("Failed to set armclk\n");
		return ret;
	}
	return 0;
}
#endif

#define CRU_NODE_FDT_PATH	"/clock-controller@fdd20000"
#define CRU_RATE_CNT_MIN	6
#define CRU_PARENT_CNT_MIN	3

#define RKVDEC_NODE_FDT_PATH    "/rkvdec@fdf80200"
#define RKVDEC_NORMAL_RATE_CNT_MIN     5
#define RKVDEC_RATE_CNT_MIN     4

#define GMAC0_NODE_FDT_PATH    "/ethernet@fe2a0000"
#define GMAC1_NODE_FDT_PATH    "/ethernet@fe010000"

#define GMAC0_CLKIN_NODE_FDT_PATH "/external-gmac0-clock"
#define GMAC1_CLKIN_NODE_FDT_PATH "/external-gmac1-clock"

#define GMAC1M0_MIIM_PINCTRL_PATH "/pinctrl/gmac1/gmac1m0-miim"

static int rk3568_board_fdt_fixup_ethernet(const void *blob, int id)
{
	int gmac_node, clkin_node, miim_node, len;
	const char *gmac_path, *clkin_path;
	void *fdt = (void *)gd->fdt_blob;
	u32 phandle, *pp;

	/* get the gmac node and clockin node path at DTB */
	if (id == 1) {
		gmac_path = GMAC1_NODE_FDT_PATH;
		clkin_path = GMAC1_CLKIN_NODE_FDT_PATH;
	} else {
		gmac_path = GMAC0_NODE_FDT_PATH;
		clkin_path = GMAC0_CLKIN_NODE_FDT_PATH;
	}

	gmac_node = fdt_path_offset(gd->fdt_blob, gmac_path);
	if (gmac_node < 0)
		return 0;

	/* only fixes the RGMII clock input mode for gmac node */
	if (fdt_stringlist_search(fdt, gmac_node,
				  "status", "disabled") < 0) {
		if (fdt_stringlist_search(fdt, gmac_node,
					  "phy-mode", "rgmii") >= 0) {
			if (fdt_stringlist_search(fdt, gmac_node,
						  "clock_in_out", "output") >= 0) {
				struct rk3568_grf *grf = (void *)GRF_BASE;

				clkin_node = fdt_path_offset(fdt, clkin_path);
				if (clkin_node < 0)
					return 0;
				phandle = fdt_get_phandle(blob, clkin_node);
				if (!phandle)
					return 0;
				/*
				 * before fixed:
				 *	assigned-clock-parents = <&cru SCLK_GMAC0_RGMII_SPEED>, <&cru CLK_MAC0_2TOP>;
				 * after fixed:
				 *	assigned-clock-parents = <&cru SCLK_GMAC0_RGMII_SPEED>, <&gmac_clkin 0>;
				 */
				pp = (u32 *)fdt_getprop(blob, gmac_node,
							"assigned-clock-parents",
							&len);
				if (!pp)
					return 0;
				if ((len / 8) >= 2) {
					pp[2] = cpu_to_fdt32(phandle);
					pp[3] = cpu_to_fdt32(0);
				}

				/*
				 * before fixed:
				 *	clock_in_out = "output";
				 * after fixed:
				 *	clock_in_out = "input";
				 */

				do_fixup_by_path(fdt, gmac_path, "clock_in_out",
						 "input", 6, 0);
				/*
				 * set gmac_clkinout pin iomux for rgmii
				 * input mode.
				 */
				if (!id) {
					rk_clrsetreg(&grf->gpio2c_iomux_l,
						     GPIO2C2_MASK,
						     GPIO2C2_GMAC0_MCLKINOUT << GPIO2C2_SHIFT);
				} else {
					/*
					 * get the miim pins phandle to check
					 * m0 or m1 for gmac1_clkinout.
					 */
					miim_node = fdt_path_offset(fdt,
								    GMAC1M0_MIIM_PINCTRL_PATH);
					if (miim_node < 0)
						goto gmac1_mclkinoutm1;
					phandle = fdt_get_phandle(blob, miim_node);
					if (!phandle)
						goto gmac1_mclkinoutm1;

					pp = (u32 *)fdt_getprop(blob, gmac_node, "pinctrl-0", &len);
					if (!pp)
						goto gmac1_mclkinoutm1;
					if (pp[0] == cpu_to_fdt32(phandle)) {
						rk_clrsetreg(&grf->gpio3c_iomux_l,
							     GPIO3C0_MASK,
							     GPIO3C0_GMAC1_MCLKINOUTM0 << GPIO3C0_SHIFT);
						return 0;
					}
gmac1_mclkinoutm1:
					rk_clrsetreg(&grf->gpio4c_iomux_l,
						     GPIO4C1_MASK,
						     GPIO4C1_GMAC1_MCLKINOUTM1 << GPIO4C1_SHIFT);
				}
			}
		}
	}

	return 0;
}

int rk_board_fdt_fixup(const void *blob)
{
	int node, len;
	u32 *pp;

	/* Don't go further if new variant */
	if (rockchip_get_cpu_version() > 0)
		return 0;

	node = fdt_path_offset(blob, CRU_NODE_FDT_PATH);
	if (node < 0)
		return 0;

	/*
	 * fixup as:
	 *	rate[1] = <400000000>;	// ACLK_RKVDEC_PRE
	 *	rate[2] = <400000000>;	// CLK_RKVDEC_CORE
	 *	rate[5] = <400000000>;	// PLL_CPLL
	 */
	pp = (u32 *)fdt_getprop(blob, node, "assigned-clock-rates", &len);
	if (!pp)
		return 0;
	if ((len / 4) >= CRU_RATE_CNT_MIN) {
		pp[1] = cpu_to_fdt32(400000000);
		pp[2] = cpu_to_fdt32(400000000);
		pp[5] = cpu_to_fdt32(400000000);
	}

	/*
	 * fixup as:
	 *	parents[1] = <&cru PLL_CPLL>;
	 *	parents[2] = <&cru PLL_CPLL>;
	 */
	pp = (u32 *)fdt_getprop(blob, node, "assigned-clock-parents", &len);
	if (!pp)
		return 0;
	if ((len / 8) >= CRU_PARENT_CNT_MIN) {
		pp[3] = cpu_to_fdt32(PLL_CPLL);
		pp[5] = cpu_to_fdt32(PLL_CPLL);
	}

	node = fdt_path_offset(blob, RKVDEC_NODE_FDT_PATH);
	if (node < 0)
		return 0;
	pp = (u32 *)fdt_getprop(blob, node, "rockchip,normal-rates", &len);
	if (!pp)
		return 0;

	if ((len / 4) >= RKVDEC_NORMAL_RATE_CNT_MIN) {
		pp[0] = cpu_to_fdt32(400000000);
		pp[1] = cpu_to_fdt32(0);
		pp[2] = cpu_to_fdt32(400000000);
		pp[3] = cpu_to_fdt32(400000000);
		pp[4] = cpu_to_fdt32(400000000);
	}

	pp = (u32 *)fdt_getprop(blob, node, "assigned-clock-rates", &len);
	if (!pp)
		return 0;

	if ((len / 4) >= RKVDEC_RATE_CNT_MIN) {
		pp[0] = cpu_to_fdt32(400000000);
		pp[1] = cpu_to_fdt32(400000000);
		pp[2] = cpu_to_fdt32(400000000);
		pp[3] = cpu_to_fdt32(400000000);
	}

	rk3568_board_fdt_fixup_ethernet(blob, 0);
	rk3568_board_fdt_fixup_ethernet(blob, 1);

	return 0;
}

#if !defined(CONFIG_SPL_BUILD) && defined(CONFIG_ROCKCHIP_DMC_FSP)
int rk_board_init(void)
{
	struct udevice *dev;
	u32 ret = 0;

	ret = uclass_get_device_by_driver(UCLASS_DMC, DM_GET_DRIVER(dmc_fsp), &dev);
	if (ret) {
		printf("dmc_fsp failed, ret=%d\n", ret);
		return 0;
	}

	return 0;
}
#endif
