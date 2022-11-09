/*
 * Copyright (c) 2019 Rockchip Electronics Co., Ltd
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */
#include <common.h>
#include <ramdisk.h>
#include <asm/io.h>
#include <asm/arch-rockchip/boot_mode.h>
#include <asm/arch-rockchip/hardware.h>
#include <asm/arch-rockchip/grf_rv1126.h>

DECLARE_GLOBAL_DATA_PTR;

#define FIREWALL_APB_BASE	0xffa60000
#define FW_DDR_CON_REG		0x80

#define USB_HOST_PRIORITY_REG	0xfe810008
#define USB_OTG_PRIORITY_REG	0xfe810088
#define DECOM_PRIORITY_REG	0xfe820088
#define DMA_PRIORITY_REG	0xfe820108
#define MCU_DM_PRIORITY_REG	0xfe820188
#define MCU_IM_PRIORITY_REG	0xfe820208
#define A7_PRIORITY_REG		0xfe830008
#define GMAC_PRIORITY_REG	0xfe840008
#define NPU_PRIORITY_REG	0xfe850008
#define EMMC_PRIORITY_REG	0xfe860008
#define NANDC_PRIORITY_REG	0xfe860088
#define SFC_PRIORITY_REG	0xfe860208
#define SDMMC_PRIORITY_REG	0xfe868008
#define SDIO_PRIORITY_REG	0xfe86c008
#define VEPU_RD0_PRIORITY_REG	0xfe870008
#define VEPU_RD1_PRIORITY_REG	0xfe870088
#define VEPU_WR_PRIORITY_REG	0xfe870108
#define ISPP_M0_PRIORITY_REG	0xfe880008
#define ISPP_M1_PRIORITY_REG	0xfe880088
#define ISP_PRIORITY_REG	0xfe890008
#define CIF_LITE_PRIORITY_REG	0xfe890088
#define CIF_PRIORITY_REG	0xfe890108
#define IEP_PRIORITY_REG	0xfe8a0008
#define RGA_RD_PRIORITY_REG	0xfe8a0088
#define RGA_WR_PRIORITY_REG	0xfe8a0108
#define VOP_PRIORITY_REG	0xfe8a0188
#define VDPU_PRIORITY_REG	0xfe8b0008
#define JPEG_PRIORITY_REG	0xfe8c0008
#define CRYPTO_PRIORITY_REG	0xfe8d0008
/* external priority register */
#define ISPP_M0_PRIORITY_EX_REG	0xfe880018
#define ISPP_M1_PRIORITY_EX_REG	0xfe880098
#define ISP_PRIORITY_EX_REG	0xfe890018
#define CIF_LT_PRIORITY_EX_REG	0xfe890098
#define CIF_PRIORITY_EX_REG	0xfe890118
#define VOP_PRIORITY_EX_REG	0xfe8a0198
#define VDPU_PRIORITY_EX_REG	0xfe8b0018

#define PMU_BASE_ADDR		0xff3e0000

#define PMU_BUS_IDLE_SFTCON(n)	(0xc0 + (n) * 4)
#define PMU_BUS_IDLE_ACK	(0xd0)
#define PMU_BUS_IDLE_ST		(0xd8)
#define PMU_NOC_AUTO_CON0	(0xe0)
#define PMU_NOC_AUTO_CON1	(0xe4)
#define PMU_PWR_DWN_ST		(0x108)
#define PMU_PWR_GATE_SFTCON	(0x110)

#define CRU_BASE		0xFF490000
#define CRU_CLKSEL_CON02	0x108
#define CRU_CLKSEL_CON03	0x10c
#define CRU_CLKSEL_CON27	0x16c
#define CRU_CLKSEL_CON31	0x17c
#define CRU_CLKSEL_CON33	0x184
#define CRU_CLKSEL_CON40	0x1a0
#define CRU_CLKSEL_CON49	0x1c4
#define CRU_CLKSEL_CON50	0x1c8
#define CRU_CLKSEL_CON51	0x1cc
#define CRU_CLKSEL_CON54	0x1d8
#define CRU_CLKSEL_CON61	0x1f4
#define CRU_CLKSEL_CON63	0x1fc
#define CRU_CLKSEL_CON65	0x204
#define CRU_CLKSEL_CON67	0x20c
#define CRU_CLKSEL_CON68	0x210
#define CRU_CLKSEL_CON69	0x214
#define CRU_SOFTRST_CON02	0x308

#define CRU_PMU_BASE		0xFF480000
#define CRU_PMU_GPLL_CON0	0x10
#define CRU_PMU_GPLL_CON1	0x14

#define GRF_BASE		0xFE000000
#define GRF_SOC_CON2		0x008
#define PMUGRF_BASE		0xFE020000
#define SGRF_BASE		0xFE0A0000
#define SGRF_CON_SCR1_BOOT_ADDR	0x0b0
#define SGRF_SOC_CON3		0x00c
#define CRU_SOFTRST_CON11	0xFF49032C
#define PMUGRF_SOC_CON1		0xFE020104
#define PMUGRF_RSTFUNC_STATUS	0xFE020230
#define PMUGRF_RSTFUNC_CLR	0xFE020234
#define WDT_RESET_SRC		BIT(1)
#define WDT_RESET_SRC_CLR	BIT(1)
#define GRF_IOFUNC_CON3		0xFF01026C
#define GRF1_GPIO0D_P		0xFE010104
#define OTP_NS_BASE		0xFF5C0000
#define OTP_S_BASE		0xFF5D0000
#define OTP_NVM_TRWH		0x28

#define PMU_GRF_BASE		0xFE020000
#define PMUGRF_GPIO0B_IOMUX_H	0xc

enum {
	GPIO1A7_SHIFT		= 12,
	GPIO1A7_MASK		= GENMASK(14, 12),
	GPIO1A7_GPIO		= 0,
	GPIO1A7_SDMMC0_D3,
	GPIO1A7_UART3_TX_M1,
	GPIO1A7_A7_JTAG_TMS_M0,
	GPIO1A7_RISCV_JTAG_TMS,

	GPIO1A6_SHIFT		= 8,
	GPIO1A6_MASK		= GENMASK(10, 8),
	GPIO1A6_GPIO		= 0,
	GPIO1A6_SDMMC0_D2,
	GPIO1A6_UART3_RX_M1,
	GPIO1A6_A7_JTAG_TCK_M0,
	GPIO1A6_RISCV_JTAG_TCK,

	GPIO1A5_SHIFT		= 4,
	GPIO1A5_MASK		= GENMASK(6, 4),
	GPIO1A5_GPIO		= 0,
	GPIO1A5_SDMMC0_D1,
	GPIO1A5_TEST_CLK0_OUT,
	GPIO1A5_UART2_TX_M0,
	GPIO1A5_RISCV_JTAG_TRSTN,

	GPIO1A4_SHIFT		= 0,
	GPIO1A4_MASK		= GENMASK(2, 0),
	GPIO1A4_GPIO		= 0,
	GPIO1A4_SDMMC0_D0,
	GPIO1A4_TEST_CLK1_OUT,
	GPIO1A4_UART2_RX_M0,

	GPIO1C3_SHIFT		= 12,
	GPIO1C3_MASK		= GENMASK(14, 12),
	GPIO1C3_GPIO		= 0,
	GPIO1C3_UART0_TX,

	GPIO1C2_SHIFT		= 8,
	GPIO1C2_MASK		= GENMASK(10, 8),
	GPIO1C2_GPIO		= 0,
	GPIO1C2_UART0_RX,

	GPIO1D5_SHIFT		= 4,
	GPIO1D5_MASK		= GENMASK(6, 4),
	GPIO1D5_GPIO		= 0,
	GPIO1D5_SPI0_CS1N_M1,
	GPIO1D5_I2S1_MCLK_M1,
	GPIO1D5_UART4_TX_M2,

	GPIO1D4_SHIFT		= 0,
	GPIO1D4_MASK		= GENMASK(2, 0),
	GPIO1D4_GPIO		= 0,
	GPIO1D4_RESERVED0,
	GPIO1D4_RESERVED1,
	GPIO1D4_UART4_RX_M2,

	GPIO1D1_SHIFT		= 4,
	GPIO1D1_MASK		= GENMASK(6, 4),
	GPIO1D1_GPIO		= 0,
	GPIO1D1_RESERVED0,
	GPIO1D1_SDMMC1_PWR,
	GPIO1D1_RESERVED1,
	GPIO1D1_I2C5_SDA_M2,
	GPIO1D1_UART1_RX_M1,

	GPIO1D0_SHIFT		= 0,
	GPIO1D0_MASK		= GENMASK(2, 0),
	GPIO1D0_GPIO		= 0,
	GPIO1D0_I2S2_MCLK_M0,
	GPIO1D0_SDMMC1_DET,
	GPIO1D0_SPI1_CS1N_M1,
	GPIO1D0_I2C5_SCL_M2,
	GPIO1D0_UART1_TX_M1,

	GPIO2A7_SHIFT		= 12,
	GPIO2A7_MASK		= GENMASK(14, 12),
	GPIO2A7_GPIO		= 0,
	GPIO2A7_LCDC_D3,
	GPIO2A7_I2S2_SDO_M1,
	GPIO2A7_RESERVED,
	GPIO2A7_UART4_RX_M1,
	GPIO2A7_PWM4_M1,
	GPIO2A7_SPI0_CS0N_M2,

	GPIO2A6_SHIFT		= 8,
	GPIO2A6_MASK		= GENMASK(10, 8),
	GPIO2A6_GPIO		= 0,
	GPIO2A6_LCDC_D2,
	GPIO2A6_RGMII_COL_M1,
	GPIO2A6_CIF_D2_M1,
	GPIO2A6_UART4_TX_M1,
	GPIO2A6_PWM5_M1,

	GPIO2A1_SHIFT		= 4,
	GPIO2A1_MASK		= GENMASK(6, 4),
	GPIO2A1_GPIO		= 0,
	GPIO2A1_SPI0_CLK_M1,
	GPIO2A1_I2S1_SDO_M1,
	GPIO2A1_UART5_RX_M2,

	GPIO2A0_SHIFT		= 0,
	GPIO2A0_MASK		= GENMASK(2, 0),
	GPIO2A0_GPIO		= 0,
	GPIO2A0_SPI0_CS0N_M1,
	GPIO2A0_I2S1_SDI_M1,
	GPIO2A0_UART5_TX_M2,

	GPIO2B1_SHIFT		= 4,
	GPIO2B1_MASK		= GENMASK(6, 4),
	GPIO2B1_GPIO		= 0,
	GPIO2B1_LCDC_D5,
	GPIO2B1_I2S2_SCLK_M1,
	GPIO2B1_RESERVED,
	GPIO2B1_UART5_RX_M1,
	GPIO2B1_PWM2_M1,
	GPIO2B1_SPI0_MISO_M2,

	GPIO2B0_SHIFT		= 0,
	GPIO2B0_MASK		= GENMASK(2, 0),
	GPIO2B0_GPIO		= 0,
	GPIO2B0_LCDC_D4,
	GPIO2B0_I2S2_SDI_M1,
	GPIO2B0_RESERVED,
	GPIO2B0_UART5_TX_M1,
	GPIO2B0_PWM3_IR_M1,
	GPIO2B0_SPI0_MOSI_M2,

	GPIO3A7_SHIFT		= 12,
	GPIO3A7_MASK		= GENMASK(14, 12),
	GPIO3A7_GPIO		= 0,
	GPIO3A7_CIF_D3_M0,
	GPIO3A7_RGMII_RXD2_M0,
	GPIO3A7_I2S0_SDI0_M1,
	GPIO3A7_UART5_RX_M0,
	GPIO3A7_CAN_TXD_M1,
	GPIO3A7_PWM11_IR_M0,

	GPIO3A6_SHIFT		= 8,
	GPIO3A6_MASK		= GENMASK(10, 8),
	GPIO3A6_GPIO		= 0,
	GPIO3A6_CIF_D2_M0,
	GPIO3A6_RGMII_COL_M0,
	GPIO3A6_I2S0_SDO0_M1,
	GPIO3A6_UART5_TX_M0,
	GPIO3A6_CAN_RXD_M1,
	GPIO3A6_PWM10_M0,

	GPIO3A5_SHIFT		= 4,
	GPIO3A5_MASK		= GENMASK(6, 4),
	GPIO3A5_GPIO		= 0,
	GPIO3A5_CIF_D1_M0,
	GPIO3A5_RGMII_CRS_M0,
	GPIO3A5_I2S0_LRCK_TX_M1,
	GPIO3A5_UART4_RX_M0,
	GPIO3A5_I2C3_SDA_M0,
	GPIO3A5_PWM9_M0,

	GPIO3A4_SHIFT		= 0,
	GPIO3A4_MASK		= GENMASK(2, 0),
	GPIO3A4_GPIO		= 0,
	GPIO3A4_CIF_D0_M0,
	GPIO3A4_RESERVED,
	GPIO3A4_I2S0_SCLK_TX_M1,
	GPIO3A4_UART4_TX_M0,
	GPIO3A4_I2C3_SCL_M0,
	GPIO3A4_PWM8_M0,

	GPIO3A3_SHIFT		= 12,
	GPIO3A3_MASK		= GENMASK(14, 12),
	GPIO3A3_GPIO		= 0,
	GPIO3A3_UART2_RX_M1,
	GPIO3A3_A7_JTAG_TMS_M1,

	GPIO3A2_SHIFT		= 8,
	GPIO3A2_MASK		= GENMASK(10, 8),
	GPIO3A2_GPIO		= 0,
	GPIO3A2_UART2_TX_M1,
	GPIO3A2_A7_JTAG_TCK_M1,

	GPIO3A1_SHIFT		= 4,
	GPIO3A1_MASK		= GENMASK(6, 4),
	GPIO3A1_GPIO		= 0,
	GPIO3A1_RESERVED0,
	GPIO3A1_RESERVED1,
	GPIO3A1_CAN_TXD_M0,
	GPIO3A1_UART3_RX_M2,
	GPIO3A1_PWM6_M1,
	GPIO3A1_RESERVED2,
	GPIO3A1_I2C4_SDA_M0,

	GPIO3A0_SHIFT		= 0,
	GPIO3A0_MASK		= GENMASK(2, 0),
	GPIO3A0_GPIO		= 0,
	GPIO3A0_RESERVED0,
	GPIO3A0_RESERVED1,
	GPIO3A0_CAN_RXD_M0,
	GPIO3A0_UART3_TX_M2,
	GPIO3A0_PWM7_IR_M1,
	GPIO3A0_SPI1_CS1N_M2,
	GPIO3A0_I2C4_SCL_M0,

	GPIO3C7_SHIFT		= 12,
	GPIO3C7_MASK		= GENMASK(14, 12),
	GPIO3C7_GPIO		= 0,
	GPIO3C7_CIF_HSYNC_M0,
	GPIO3C7_RGMII_RXCLK_M0,
	GPIO3C7_RESERVED,
	GPIO3C7_UART3_RX_M0,

	GPIO3C6_SHIFT		= 8,
	GPIO3C6_MASK		= GENMASK(10, 0),
	GPIO3C6_GPIO		= 0,
	GPIO3C6_CIF_CLKOUT_M0,
	GPIO3C6_RGMII_TXCLK_M0,
	GPIO3C6_RESERVED,
	GPIO3C6_UART3_TX_M0,

	UART2_IO_SEL_SHIFT	= 8,
	UART2_IO_SEL_MASK	= GENMASK(8, 8),
	UART2_IO_SEL_M0		= 0,
	UART2_IO_SEL_M1,

	UART3_IO_SEL_SHIFT	= 10,
	UART3_IO_SEL_MASK	= GENMASK(11, 10),
	UART3_IO_SEL_M0		= 0,
	UART3_IO_SEL_M1,
	UART3_IO_SEL_M2,

	UART4_IO_SEL_SHIFT	= 12,
	UART4_IO_SEL_MASK	= GENMASK(13, 12),
	UART4_IO_SEL_M0		= 0,
	UART4_IO_SEL_M1,
	UART4_IO_SEL_M2,

	UART5_IO_SEL_SHIFT	= 14,
	UART5_IO_SEL_MASK	= GENMASK(15, 14),
	UART5_IO_SEL_M0		= 0,
	UART5_IO_SEL_M1,
	UART5_IO_SEL_M2,
};

enum {
	UART1_IO_SEL_SHIFT	= 2,
	UART1_IO_SEL_MASK	= GENMASK(2, 2),
	UART1_IO_SEL_M0		= 0,
	UART1_IO_SEL_M1,

	GPIO0B7_SHIFT		= 12,
	GPIO0B7_MASK		= GENMASK(14, 12),
	GPIO0B7_GPIO		= 0,
	GPIO0B7_RESERVED,
	GPIO0B7_UART1_RX_M0,
	GPIO0B7_PWM1_M0,

	GPIO0B6_SHIFT		= 8,
	GPIO0B6_MASK		= GENMASK(10, 8),
	GPIO0B6_GPIO		= 0,
	GPIO0B6_RESERVED,
	GPIO0B6_UART1_TX_M0,
	GPIO0B6_PWM0_M0,
};

void board_debug_uart_init(void)
{
#if defined(CONFIG_DEBUG_UART_BASE) && (CONFIG_DEBUG_UART_BASE == 0xff560000)
	static struct rv1126_grf * const grf = (void *)GRF_BASE;

	/* UART0 Switch iomux */
	rk_clrsetreg(&grf->gpio1c_iomux_l,
		     GPIO1C3_MASK | GPIO1C2_MASK,
		     GPIO1C3_UART0_TX << GPIO1C3_SHIFT |
		     GPIO1C2_UART0_RX << GPIO1C2_SHIFT);

#elif defined(CONFIG_DEBUG_UART_BASE) && (CONFIG_DEBUG_UART_BASE == 0xff410000)
	static struct rv1126_pmugrf * const pmugrf = (void *)PMUGRF_BASE;
	static struct rv1126_grf * const grf = (void *)GRF_BASE;
#if defined(CONFIG_ROCKCHIP_UART_MUX_SEL_M) && \
    (CONFIG_ROCKCHIP_UART_MUX_SEL_M == 0)
	/* UART1 M0 */
	rk_clrsetreg(&pmugrf->soc_con[6], UART1_IO_SEL_MASK,
		     UART1_IO_SEL_M0 << UART1_IO_SEL_SHIFT);

	/* Switch iomux */
	rk_clrsetreg(&pmugrf->gpio0b_iomux_h,
		     GPIO0B7_MASK | GPIO0B6_MASK,
		     GPIO0B7_UART1_RX_M0 << GPIO0B7_SHIFT |
		     GPIO0B6_UART1_TX_M0 << GPIO0B6_SHIFT);
#else
	/* UART1 M1 */
	rk_clrsetreg(&pmugrf->soc_con[6], UART1_IO_SEL_MASK,
		     UART1_IO_SEL_M1 << UART1_IO_SEL_SHIFT);

	/* Switch iomux */
	rk_clrsetreg(&grf->gpio1d_iomux_l,
		     GPIO1D1_MASK | GPIO1D0_MASK,
		     GPIO1D1_UART1_RX_M1 << GPIO1D1_SHIFT |
		     GPIO1D0_UART1_TX_M1 << GPIO1D0_SHIFT);
#endif

#elif defined(CONFIG_DEBUG_UART_BASE) && (CONFIG_DEBUG_UART_BASE == 0xff570000)
	static struct rv1126_grf * const grf = (void *)GRF_BASE;
#if defined(CONFIG_ROCKCHIP_UART_MUX_SEL_M) && \
    (CONFIG_ROCKCHIP_UART_MUX_SEL_M == 0)
	/* Enable early UART2 channel m0 on the rv1126 */
	rk_clrsetreg(&grf->iofunc_con2, UART2_IO_SEL_MASK,
		     UART2_IO_SEL_M0 << UART2_IO_SEL_SHIFT);

	/* Switch iomux */
	rk_clrsetreg(&grf->gpio1a_iomux_h,
		     GPIO1A5_MASK | GPIO1A4_MASK,
		     GPIO1A5_UART2_TX_M0 << GPIO1A5_SHIFT |
		     GPIO1A4_UART2_RX_M0 << GPIO1A4_SHIFT);
#else
	/* Enable early UART2 channel m1 on the rv1126 */
	rk_clrsetreg(&grf->iofunc_con2, UART2_IO_SEL_MASK,
		     UART2_IO_SEL_M1 << UART2_IO_SEL_SHIFT);

	/* Switch iomux */
	rk_clrsetreg(&grf->gpio3a_iomux_l,
		     GPIO3A3_MASK | GPIO3A2_MASK,
		     GPIO3A3_UART2_RX_M1 << GPIO3A3_SHIFT |
		     GPIO3A2_UART2_TX_M1 << GPIO3A2_SHIFT);
#endif

#elif defined(CONFIG_DEBUG_UART_BASE) && (CONFIG_DEBUG_UART_BASE == 0xff580000)
	static struct rv1126_grf * const grf = (void *)GRF_BASE;
#if defined(CONFIG_ROCKCHIP_UART_MUX_SEL_M) && \
    (CONFIG_ROCKCHIP_UART_MUX_SEL_M == 0)
	/* UART3 m0*/
	rk_clrsetreg(&grf->iofunc_con2, UART3_IO_SEL_MASK,
		     UART3_IO_SEL_M0 << UART3_IO_SEL_SHIFT);

	/* Switch iomux */
	rk_clrsetreg(&grf->gpio3c_iomux_h,
		     GPIO3C7_MASK | GPIO3C6_MASK,
		     GPIO3C7_UART3_RX_M0 << GPIO3C7_SHIFT |
		     GPIO3C6_UART3_TX_M0 << GPIO3C6_SHIFT);
#elif defined(CONFIG_ROCKCHIP_UART_MUX_SEL_M) && \
      (CONFIG_ROCKCHIP_UART_MUX_SEL_M == 1)
	/* UART3 m1*/
	rk_clrsetreg(&grf->iofunc_con2, UART3_IO_SEL_MASK,
		     UART3_IO_SEL_M1 << UART3_IO_SEL_SHIFT);

	/* Switch iomux */
	rk_clrsetreg(&grf->gpio1a_iomux_h,
		     GPIO1A7_MASK | GPIO1A6_MASK,
		     GPIO1A7_UART3_TX_M1 << GPIO1A7_SHIFT |
		     GPIO1A6_UART3_RX_M1 << GPIO1A6_SHIFT);
#else
	/* UART3 m2*/
	rk_clrsetreg(&grf->iofunc_con2, UART3_IO_SEL_MASK,
		     UART3_IO_SEL_M2 << UART3_IO_SEL_SHIFT);

	/* Switch iomux */
	rk_clrsetreg(&grf->gpio3a_iomux_l,
		     GPIO3A1_MASK | GPIO3A0_MASK,
		     GPIO3A1_UART3_RX_M2 << GPIO3A1_SHIFT |
		     GPIO3A0_UART3_TX_M2 << GPIO3A0_SHIFT);
#endif

#elif defined(CONFIG_DEBUG_UART_BASE) && (CONFIG_DEBUG_UART_BASE == 0xff590000)
	static struct rv1126_grf * const grf = (void *)GRF_BASE;
#if defined(CONFIG_ROCKCHIP_UART_MUX_SEL_M) && \
    (CONFIG_ROCKCHIP_UART_MUX_SEL_M == 0)
	/* UART4 m0*/
	rk_clrsetreg(&grf->iofunc_con2, UART4_IO_SEL_MASK,
		     UART4_IO_SEL_M0 << UART4_IO_SEL_SHIFT);

	/* Switch iomux */
	rk_clrsetreg(&grf->gpio3a_iomux_h,
		     GPIO3A5_MASK | GPIO3A4_MASK,
		     GPIO3A5_UART4_RX_M0 << GPIO3A5_SHIFT |
		     GPIO3A4_UART4_TX_M0 << GPIO3A4_SHIFT);
#elif defined(CONFIG_ROCKCHIP_UART_MUX_SEL_M) && \
      (CONFIG_ROCKCHIP_UART_MUX_SEL_M == 1)
	/* UART4 m1*/
	rk_clrsetreg(&grf->iofunc_con2, UART4_IO_SEL_MASK,
		     UART4_IO_SEL_M1 << UART4_IO_SEL_SHIFT);

	/* Switch iomux */
	rk_clrsetreg(&grf->gpio2a_iomux_h,
		     GPIO2A7_MASK | GPIO2A6_MASK,
		     GPIO2A7_UART4_RX_M1 << GPIO2A7_SHIFT |
		     GPIO2A6_UART4_TX_M1 << GPIO2A6_SHIFT);
#else
	/* UART4 m2*/
	rk_clrsetreg(&grf->iofunc_con2, UART4_IO_SEL_MASK,
		     UART4_IO_SEL_M2 << UART4_IO_SEL_SHIFT);

	/* Switch iomux */
	rk_clrsetreg(&grf->gpio1d_iomux_h,
		     GPIO1D5_MASK | GPIO1D4_MASK,
		     GPIO1D5_UART4_TX_M2 << GPIO1D5_SHIFT |
		     GPIO1D4_UART4_RX_M2 << GPIO1D4_SHIFT);
#endif

#elif defined(CONFIG_DEBUG_UART_BASE) && (CONFIG_DEBUG_UART_BASE == 0xff5a0000)
	static struct rv1126_grf * const grf = (void *)GRF_BASE;
#if defined(CONFIG_ROCKCHIP_UART_MUX_SEL_M) && \
    (CONFIG_ROCKCHIP_UART_MUX_SEL_M == 0)
	/* UART5 m0*/
	rk_clrsetreg(&grf->iofunc_con2, UART5_IO_SEL_MASK,
		     UART5_IO_SEL_M0 << UART5_IO_SEL_SHIFT);

	/* Switch iomux */
	rk_clrsetreg(&grf->gpio3a_iomux_h,
		     GPIO3A7_MASK | GPIO3A6_MASK,
		     GPIO3A7_UART5_RX_M0 << GPIO3A7_SHIFT |
		     GPIO3A6_UART5_TX_M0 << GPIO3A6_SHIFT);
#elif defined(CONFIG_ROCKCHIP_UART_MUX_SEL_M) && \
      (CONFIG_ROCKCHIP_UART_MUX_SEL_M == 1)
	/* UART5 m1*/
	rk_clrsetreg(&grf->iofunc_con2, UART5_IO_SEL_MASK,
		     UART5_IO_SEL_M1 << UART5_IO_SEL_SHIFT);

	/* Switch iomux */
	rk_clrsetreg(&grf->gpio2b_iomux_l,
		     GPIO2B1_MASK | GPIO2B0_MASK,
		     GPIO2B1_UART5_RX_M1 << GPIO2B1_SHIFT |
		     GPIO2B0_UART5_TX_M1 << GPIO2B0_SHIFT);
#else
	/* UART5 m2*/
	rk_clrsetreg(&grf->iofunc_con2, UART5_IO_SEL_MASK,
		     UART5_IO_SEL_M2 << UART5_IO_SEL_SHIFT);

	/* Switch iomux */
	rk_clrsetreg(&grf->gpio2a_iomux_l,
		     GPIO2A1_MASK | GPIO2A0_MASK,
		     GPIO2A1_UART5_RX_M2 << GPIO2A1_SHIFT |
		     GPIO2A0_UART5_TX_M2 << GPIO2A0_SHIFT);
#endif
#endif /* CONFIG_DEBUG_UART_BASE && CONFIG_DEBUG_UART_BASE == ... */
}

#ifndef CONFIG_TPL_BUILD
int arch_cpu_init(void)
{
	/*
	 * CONFIG_DM_RAMDISK: for ramboot that without SPL.
	 */
#if defined(CONFIG_SPL_BUILD) || defined(CONFIG_DM_RAMDISK)
	int delay;

	/*
	 * Don't rely on CONFIG_DM_RAMDISK since it can be a default
	 * configuration after disk/part_rkram.c was introduced.
	 *
	 * This is compatible code.
	 */
  #ifndef CONFIG_SPL_BUILD
	if (!dm_ramdisk_is_enabled())
		return 0;
  #endif

	/* write BOOT_WATCHDOG to boot mode register, if reset by wdt */
	if (readl(PMUGRF_RSTFUNC_STATUS) & WDT_RESET_SRC) {
		writel(BOOT_WATCHDOG, CONFIG_ROCKCHIP_BOOT_MODE_REG);
		/* clear flag for reset by wdt trigger */
		writel(WDT_RESET_SRC_CLR, PMUGRF_RSTFUNC_CLR);
	}

  #ifdef CONFIG_SPL_BUILD
	/* set otp tRWH to 0x9 for stable read */
	writel(0x9, OTP_NS_BASE + OTP_NVM_TRWH);
	writel(0x9, OTP_S_BASE + OTP_NVM_TRWH);

	/*
	 * Just set region 0 to unsecure.
	 * (Note: only secure-world can access this register)
	 */
	writel(0, FIREWALL_APB_BASE + FW_DDR_CON_REG);
  #endif

	/* disable force jtag mux route to both group0 and group1 */
	writel(0x00300000, GRF_IOFUNC_CON3);

	/* make npu aclk and sclk less then 300MHz when reset */
	writel(0x00ff0055, CRU_BASE + CRU_CLKSEL_CON65);
	writel(0x00ff0055, CRU_BASE + CRU_CLKSEL_CON67);

	/*
	 * When perform idle operation, corresponding clock can
	 * be opened or gated automatically.
	 */
	writel(0xffffffff, PMU_BASE_ADDR + PMU_NOC_AUTO_CON0);
	writel(0xffffffff, PMU_BASE_ADDR + PMU_NOC_AUTO_CON1);

  #ifdef CONFIG_SPL_KERNEL_BOOT
	/* Adjust the parameters of GPLL's VCO for reduce power*/
	writel(0x00030000, CRU_PMU_BASE);
	writel(0xffff1063, CRU_PMU_BASE + CRU_PMU_GPLL_CON0);
	writel(0xffff1442, CRU_PMU_BASE + CRU_PMU_GPLL_CON1);
	writel(0x00030001, CRU_PMU_BASE);

	/* mux clocks to none-cpll */
	writel(0x00ff0003, CRU_BASE + CRU_CLKSEL_CON02);
	writel(0x00ff0005, CRU_BASE + CRU_CLKSEL_CON03);
	writel(0xffff8383, CRU_BASE + CRU_CLKSEL_CON27);
	writel(0x00ff0083, CRU_BASE + CRU_CLKSEL_CON31);
	writel(0x00ff0083, CRU_BASE + CRU_CLKSEL_CON33);
	writel(0xffff4385, CRU_BASE + CRU_CLKSEL_CON40);
	writel(0x00ff0043, CRU_BASE + CRU_CLKSEL_CON49);
	writel(0x00ff0003, CRU_BASE + CRU_CLKSEL_CON50);
	writel(0x00ff0003, CRU_BASE + CRU_CLKSEL_CON51);
	writel(0xff000300, CRU_BASE + CRU_CLKSEL_CON54);
	writel(0xff008900, CRU_BASE + CRU_CLKSEL_CON61);
	writel(0x00ff0089, CRU_BASE + CRU_CLKSEL_CON63);
	writel(0x00ff0045, CRU_BASE + CRU_CLKSEL_CON68);
	writel(0x00ff0043, CRU_BASE + CRU_CLKSEL_CON69);

  #endif
	/* enable all pd */
	writel(0xffff0000, PMU_BASE_ADDR + PMU_PWR_GATE_SFTCON);
	delay = 1000;
	do {
		udelay(1);
		delay--;
		if (delay == 0) {
			printf("Fail to set domain.");
			hang();
		}
	} while (readl(PMU_BASE_ADDR + PMU_PWR_DWN_ST));

	/* release all idle request */
	writel(0xffff0000, PMU_BASE_ADDR + PMU_BUS_IDLE_SFTCON(0));
	writel(0xffff0000, PMU_BASE_ADDR + PMU_BUS_IDLE_SFTCON(1));

	delay = 1000;
	/* wait ack status */
	do {
		udelay(1);
		delay--;
		if (delay == 0) {
			printf("Fail to get ack on domain.\n");
			hang();
		}
	} while (readl(PMU_BASE_ADDR + PMU_BUS_IDLE_ACK));

	delay = 1000;
	/* wait idle status */
	do {
		udelay(1);
		delay--;
		if (delay == 0) {
			printf("Fail to set idle on domain.\n");
			hang();
		}
	} while (readl(PMU_BASE_ADDR + PMU_BUS_IDLE_ST));

	writel(0x303, USB_HOST_PRIORITY_REG);
	writel(0x303, USB_OTG_PRIORITY_REG);
	writel(0x101, DECOM_PRIORITY_REG);
	writel(0x303, DMA_PRIORITY_REG);
	writel(0x101, MCU_DM_PRIORITY_REG);
	writel(0x101, MCU_IM_PRIORITY_REG);
	writel(0x101, A7_PRIORITY_REG);
	writel(0x303, GMAC_PRIORITY_REG);
	writel(0x101, NPU_PRIORITY_REG);
	writel(0x303, EMMC_PRIORITY_REG);
	writel(0x303, NANDC_PRIORITY_REG);
	writel(0x303, SFC_PRIORITY_REG);
	writel(0x303, SDMMC_PRIORITY_REG);
	writel(0x303, SDIO_PRIORITY_REG);
	writel(0x101, VEPU_RD0_PRIORITY_REG);
	writel(0x101, VEPU_RD1_PRIORITY_REG);
	writel(0x101, VEPU_WR_PRIORITY_REG);
	writel(0x101, ISPP_M0_PRIORITY_REG);
	writel(0x101, ISPP_M1_PRIORITY_REG);
	writel(0x101, ISP_PRIORITY_REG);
	writel(0x202, CIF_LITE_PRIORITY_REG);
	writel(0x202, CIF_PRIORITY_REG);
	writel(0x101, IEP_PRIORITY_REG);
	writel(0x101, RGA_RD_PRIORITY_REG);
	writel(0x101, RGA_WR_PRIORITY_REG);
	writel(0x202, VOP_PRIORITY_REG);
	writel(0x101, VDPU_PRIORITY_REG);
	writel(0x101, JPEG_PRIORITY_REG);
	writel(0x101, CRYPTO_PRIORITY_REG);
	/* enable dynamic priority */
	writel(0x1, ISP_PRIORITY_EX_REG);

	/*
	 * Init the i2c0 iomux and use it to control electronic voltmeter
	 * to detect voltage.
	 */
  #if defined(CONFIG_SPL_KERNEL_BOOT) && defined(CONFIG_SPL_DM_FUEL_GAUGE)
	writel(0x00770011, PMU_GRF_BASE + PMUGRF_GPIO0B_IOMUX_H);
  #endif

#elif defined(CONFIG_SUPPORT_USBPLUG)
	/* Just set region 0 to unsecure */
	writel(0, FIREWALL_APB_BASE + FW_DDR_CON_REG);

	/* reset usbphy_otg usbphypor_otg */
	writel(((0x1 << 6 | (1 << 8)) << 16) | (0x1 << 6) | (1 << 8), CRU_SOFTRST_CON11);
	udelay(50);
	writel(((0x1 << 6 | (1 << 8)) << 16) | (0), CRU_SOFTRST_CON11);

	/* hold pmugrf's io reset */
	writel(0x1 << 7 | 1 << 23, PMUGRF_SOC_CON1);

#else /* U-Boot */
	/* uboot: config iomux for sd boot upgrade firmware */
  #if defined(CONFIG_ROCKCHIP_SFC_IOMUX)
	static struct rv1126_grf * const grf = (void *)GRF_BASE;

	writel(0x0F0F0303, &grf->gpio0d_iomux_h);
	writel(0xFFFF3333, &grf->gpio1a_iomux_l);
  #elif defined(CONFIG_ROCKCHIP_EMMC_IOMUX)
	static struct rv1126_grf * const grf = (void *)GRF_BASE;

	writel(0xFFFF2222, &grf->gpio0c_iomux_h);
	writel(0xFFFF2222, &grf->gpio0d_iomux_l);
	writel(0xF0F02020, &grf->gpio0d_iomux_h);
  #elif defined(CONFIG_ROCKCHIP_NAND_IOMUX)
	static struct rv1126_grf * const grf = (void *)GRF_BASE;

	writel(0xFFFF1111, &grf->gpio0c_iomux_h);
	writel(0xFFFF1111, &grf->gpio0d_iomux_l);
	writel(0xF0FF1011, &grf->gpio0d_iomux_h);
	writel(0xFFFF1111, &grf->gpio1a_iomux_l);
  #endif

#endif
#if defined(CONFIG_ROCKCHIP_SFC)
	/* GPIO0_D6 pull down in default, pull up it for SPI Flash */
	writel(((0x3 << 12) << 16) | (0x1 << 12), GRF1_GPIO0D_P);
#endif

	return 0;
}
#endif

#ifdef CONFIG_SPL_BUILD
int spl_fit_standalone_release(char *id, uintptr_t entry_point)
{
	/*
	 * Fix mcu does not work probabilistically through reset the
	 * mcu debug module. If use the jtag debug, reset it.
	 */
	writel(0x80008000, GRF_BASE + GRF_SOC_CON2);
	/* Reset the scr1 */
	writel(0x04000400, CRU_BASE + CRU_SOFTRST_CON02);
	udelay(100);
	/* set the scr1 addr */
	writel(entry_point, SGRF_BASE + SGRF_CON_SCR1_BOOT_ADDR);
	writel(0x00ff00bf, SGRF_BASE + SGRF_SOC_CON3);
	udelay(10);
	/* release the scr1 */
	writel(0x04000000, CRU_BASE + CRU_SOFTRST_CON02);

	return 0;
}
#endif
