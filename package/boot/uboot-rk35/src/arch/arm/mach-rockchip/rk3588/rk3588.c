/*
 * Copyright (c) 2021 Rockchip Electronics Co., Ltd
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */
#include <common.h>
#include <mmc.h>
#include <spl.h>
#include <asm/io.h>
#include <asm/arch-rockchip/cpu.h>
#include <asm/arch-rockchip/hardware.h>
#include <asm/arch-rockchip/ioc_rk3588.h>
#include <dt-bindings/clock/rk3588-cru.h>

DECLARE_GLOBAL_DATA_PTR;

#define FIREWALL_DDR_BASE		0xfe030000
#define FW_DDR_MST5_REG			0x54
#define FW_DDR_MST13_REG		0x74
#define FW_DDR_MST21_REG		0x94
#define FW_DDR_MST26_REG		0xa8
#define FW_DDR_MST27_REG		0xac
#define FIREWALL_SYSMEM_BASE		0xfe038000
#define FW_SYSM_MST5_REG		0x54
#define FW_SYSM_MST13_REG		0x74
#define FW_SYSM_MST21_REG		0x94
#define FW_SYSM_MST26_REG		0xa8
#define FW_SYSM_MST27_REG		0xac
#define SYS_GRF_BASE			0xfd58c000
#define SYS_GRF_SOC_CON6		0x0318
#define USBGRF_BASE			0xfd5ac000
#define USB_GRF_USB3OTG0_CON1		0x001c
#define BUS_SGRF_BASE			0xfd586000
#define BUS_SGRF_FIREWALL_CON18		0x288
#define PMU_BASE			0xfd8d0000
#define PMU_PWR_GATE_SFTCON1		0x8150

#define USB2PHY1_GRF_BASE		0xfd5d4000
#define USB2PHY2_GRF_BASE		0xfd5d8000
#define USB2PHY3_GRF_BASE		0xfd5dc000
#define USB2PHY_GRF_CON2		0x0008

#define PMU1_IOC_BASE			0xfd5f0000
#define PMU2_IOC_BASE			0xfd5f4000

#define BUS_IOC_BASE			0xfd5f8000
#define BUS_IOC_GPIO2B_IOMUX_SEL_L	0x48
#define BUS_IOC_GPIO2D_IOMUX_SEL_L	0x58
#define BUS_IOC_GPIO3A_IOMUX_SEL_L	0x60

#define VCCIO3_5_IOC_BASE		0xfd5fa000
#define IOC_VCCIO3_5_GPIO2A_DS_H	0x44
#define IOC_VCCIO3_5_GPIO2B_DS_L	0x48
#define IOC_VCCIO3_5_GPIO2B_DS_H	0x4c
#define IOC_VCCIO3_5_GPIO3A_DS_L	0x60
#define IOC_VCCIO3_5_GPIO3A_DS_H	0x64
#define IOC_VCCIO3_5_GPIO3C_DS_H	0x74

#define EMMC_IOC_BASE			0xfd5fd000
#define EMMC_IOC_GPIO2A_DS_L		0x40
#define EMMC_IOC_GPIO2D_DS_L		0x58
#define EMMC_IOC_GPIO2D_DS_H		0x5c

#define CRU_BASE			0xfd7c0000
#define CRU_SOFTRST_CON77		0x0b34

#define PMU1CRU_BASE			0xfd7f0000
#define PMU1CRU_SOFTRST_CON03		0x0a0c
#define PMU1CRU_SOFTRST_CON04		0x0a10

#ifdef CONFIG_ARM64
#include <asm/armv8/mmu.h>

static struct mm_region rk3588_mem_map[] = {
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
	},  {
		.virt = 0x900000000,
		.phys = 0x900000000,
		.size = 0x150000000,
		.attrs = PTE_BLOCK_MEMTYPE(MT_DEVICE_NGNRNE) |
			 PTE_BLOCK_NON_SHARE |
			 PTE_BLOCK_PXN | PTE_BLOCK_UXN
	},  {
		/* List terminator */
		0,
	}
};

struct mm_region *mem_map = rk3588_mem_map;
#endif

/* GPIO0B_IOMUX_SEL_L */
enum {
	GPIO0B0_SHIFT		= 0,
	GPIO0B0_MASK		= GENMASK(3, 0),
	GPIO0B0_UART0_RX_M1	= 4,

	GPIO0B1_SHIFT		= 4,
	GPIO0B1_MASK		= GENMASK(7, 4),
	GPIO0B1_UART0_TX_M1	= 4,
};

/* GPIO0C_IOMUX_SEL_H */
enum {
	GPIO0C4_SHIFT		= 0,
	GPIO0C4_MASK		= GENMASK(3, 0),
	GPIO0C4_UART0_RX_M0	= 4,

	GPIO0C5_SHIFT		= 4,
	GPIO0C5_MASK		= GENMASK(7, 4),
	GPIO0C5_UART0_TX_M0	= 4,
};

/* GPIO0B_IOMUX_SEL_H */
enum {
	GPIO0B5_SHIFT		= 4,
	GPIO0B5_MASK		= GENMASK(7, 4),
	GPIO0B5_REFER		= 8,
	GPIO0B5_UART2_TX_M0	= 10,

	GPIO0B6_SHIFT		= 8,
	GPIO0B6_MASK		= GENMASK(11, 8),
	GPIO0B6_REFER		= 8,
	GPIO0B6_UART2_RX_M0	= 10,
};

/* GPIO0D_IOMUX_SEL_L */
enum {
	GPIO0D1_SHIFT		= 4,
	GPIO0D1_MASK		= GENMASK(7, 4),
	GPIO0D1_REFER		= 8,
	GPIO0D1_UART1_TX_M2	= 10,

	GPIO0D2_SHIFT		= 8,
	GPIO0D2_MASK		= GENMASK(11, 8),
	GPIO0D2_REFER		= 8,
	GPIO0D2_UART1_RX_M2	= 10,
};

/* GPIO1A_IOMUX_SEL_L */
enum {
	GPIO1A0_SHIFT		= 0,
	GPIO1A0_MASK		= GENMASK(3, 0),
	GPIO1A0_UART6_RX_M1	= 10,

	GPIO1A1_SHIFT		= 4,
	GPIO1A1_MASK		= GENMASK(7, 4),
	GPIO1A1_UART6_TX_M1	= 10,
};

/* GPIO1B_IOMUX_SEL_L */
enum {
	GPIO1B2_SHIFT		= 8,
	GPIO1B2_MASK		= GENMASK(11, 8),
	GPIO1B2_UART4_RX_M2	= 10,

	GPIO1B3_SHIFT		= 12,
	GPIO1B3_MASK		= GENMASK(15, 12),
	GPIO1B3_UART4_TX_M2	= 10,
};

/* GPIO1B_IOMUX_SEL_H */
enum {
	GPIO1B4_SHIFT		= 0,
	GPIO1B4_MASK		= GENMASK(3, 0),
	GPIO1B4_UART7_RX_M2	= 10,

	GPIO1B5_SHIFT		= 4,
	GPIO1B5_MASK		= GENMASK(7, 4),
	GPIO1B5_UART7_TX_M2	= 10,

	GPIO1B6_SHIFT		= 8,
	GPIO1B6_MASK		= GENMASK(11, 8),
	GPIO1B6_UART1_TX_M1	= 10,

	GPIO1B7_SHIFT		= 12,
	GPIO1B7_MASK		= GENMASK(15, 12),
	GPIO1B7_UART1_RX_M1	= 10,
};

/* GPIO1C_IOMUX_SEL_L */
enum {
	GPIO1C0_SHIFT		= 0,
	GPIO1C0_MASK		= GENMASK(3, 0),
	GPIO1C0_UART3_RX_M0	= 10,

	GPIO1C1_SHIFT		= 4,
	GPIO1C1_MASK		= GENMASK(7, 4),
	GPIO1C1_UART3_TX_M0	= 10,
};

/* GPIO1D_IOMUX_SEL_L */
enum {
	GPIO1D0_SHIFT		= 0,
	GPIO1D0_MASK		= GENMASK(3, 0),
	GPIO1D0_UART6_TX_M2	= 10,

	GPIO1D1_SHIFT		= 4,
	GPIO1D1_MASK		= GENMASK(7, 4),
	GPIO1D1_UART6_RX_M2	= 10,

	GPIO1D2_SHIFT		= 8,
	GPIO1D2_MASK		= GENMASK(11, 8),
	GPIO1D2_UART4_TX_M0	= 10,

	GPIO1D3_SHIFT		= 12,
	GPIO1D3_MASK		= GENMASK(15, 12),
	GPIO1D3_UART4_RX_M0	= 10,
};

/* GPIO2A_IOMUX_SEL_H */
enum {
	GPIO2A6_SHIFT		= 8,
	GPIO2A6_MASK		= GENMASK(11, 8),
	GPIO2A6_UART6_RX_M0	= 10,

	GPIO2A7_SHIFT		= 12,
	GPIO2A7_MASK		= GENMASK(15, 12),
	GPIO2A7_UART6_TX_M0	= 10,
};

/* GPIO2B_IOMUX_SEL_H */
enum {
	GPIO2B4_SHIFT		= 0,
	GPIO2B4_MASK		= GENMASK(3, 0),
	GPIO2B4_UART7_RX_M0	= 10,

	GPIO2B5_SHIFT		= 4,
	GPIO2B5_MASK		= GENMASK(7, 4),
	GPIO2B5_UART7_TX_M0	= 10,

	GPIO2B6_SHIFT		= 8,
	GPIO2B6_MASK		= GENMASK(11, 8),
	GPIO2B6_UART1_RX_M0	= 10,

	GPIO2B7_SHIFT		= 12,
	GPIO2B7_MASK		= GENMASK(15, 12),
	GPIO2B7_UART1_TX_M0	= 10,
};

/* GPIO2C_IOMUX_SEL_L */
enum {
	GPIO2C2_SHIFT		= 8,
	GPIO2C2_MASK		= GENMASK(11, 8),
	GPIO2C2_UART9_TX_M0	= 10,
};

/* GPIO2C_IOMUX_SEL_H */
enum {
	GPIO2C4_SHIFT		= 0,
	GPIO2C4_MASK		= GENMASK(3, 0),
	GPIO2C4_UART9_RX_M0	= 10,
};

/* GPIO2D_IOMUX_SEL_H */
enum {
	GPIO2D4_SHIFT		= 0,
	GPIO2D4_MASK		= GENMASK(3, 0),
	GPIO2D4_UART5_RX_M2	= 10,

	GPIO2D5_SHIFT		= 4,
	GPIO2D5_MASK		= GENMASK(7, 4),
	GPIO2D5_UART5_TX_M2	= 10,
};

/* GPIO3A_IOMUX_SEL_H */
enum {
	GPIO3A2_SHIFT		= 8,
	GPIO3A2_MASK		= GENMASK(11, 8),
	GPIO3A2_UART8_TX_M1	= 10,

	GPIO3A3_SHIFT		= 12,
	GPIO3A3_MASK		= GENMASK(15, 12),
	GPIO3A3_UART8_RX_M1	= 10,
};

/* GPIO3B_IOMUX_SEL_L */
enum {
	GPIO3B1_SHIFT		= 4,
	GPIO3B1_MASK		= GENMASK(7, 4),
	GPIO3B1_UART2_TX_M2	= 10,

	GPIO3B2_SHIFT		= 8,
	GPIO3B2_MASK		= GENMASK(11, 8),
	GPIO3B2_UART2_RX_M2	= 10,
};

/* GPIO3B_IOMUX_SEL_H */
enum {
	GPIO3B5_SHIFT		= 4,
	GPIO3B5_MASK		= GENMASK(7, 4),
	GPIO3B5_UART3_TX_M1	= 10,

	GPIO3B6_SHIFT		= 8,
	GPIO3B6_MASK		= GENMASK(11, 8),
	GPIO3B6_UART3_RX_M1	= 10,
};

/* GPIO3C_IOMUX_SEL_L */
enum {
	GPIO3C0_SHIFT		= 0,
	GPIO3C0_MASK		= GENMASK(3, 0),
	GPIO3C0_UART7_TX_M1	= 10,

	GPIO3C1_SHIFT		= 4,
	GPIO3C1_MASK		= GENMASK(7, 4),
	GPIO3C1_UART7_RX_M1	= 10,
};

/* GPIO3C_IOMUX_SEL_H */
enum {
	GPIO3C4_SHIFT		= 0,
	GPIO3C4_MASK		= GENMASK(3, 0),
	GPIO3C4_UART5_TX_M1	= 10,

	GPIO3C5_SHIFT		= 4,
	GPIO3C5_MASK		= GENMASK(7, 4),
	GPIO3C5_UART5_RX_M1	= 10,
};

/* GPIO3D_IOMUX_SEL_L */
enum {
	GPIO3D0_SHIFT		= 0,
	GPIO3D0_MASK		= GENMASK(3, 0),
	GPIO3D0_UART4_RX_M1	= 10,

	GPIO3D1_SHIFT		= 4,
	GPIO3D1_MASK		= GENMASK(7, 4),
	GPIO3D1_UART4_TX_M1	= 10,
};

/* GPIO3D_IOMUX_SEL_H */
enum {
	GPIO3D4_SHIFT		= 0,
	GPIO3D4_MASK		= GENMASK(3, 0),
	GPIO3D4_UART9_RX_M2	= 10,

	GPIO3D5_SHIFT		= 4,
	GPIO3D5_MASK		= GENMASK(7, 4),
	GPIO3D5_UART9_TX_M2	= 10,
};

/* GPIO4A_IOMUX_SEL_L */
enum {
	GPIO4A3_SHIFT		= 12,
	GPIO4A3_MASK		= GENMASK(15, 12),
	GPIO4A3_UART0_TX_M2	= 10,
};

/* GPIO4A_IOMUX_SEL_H */
enum {
	GPIO4A4_SHIFT		= 0,
	GPIO4A4_MASK		= GENMASK(3, 0),
	GPIO4A4_UART0_RX_M2	= 10,

	GPIO4A5_SHIFT		= 4,
	GPIO4A5_MASK		= GENMASK(7, 4),
	GPIO4A5_UART3_TX_M2	= 10,

	GPIO4A6_SHIFT		= 8,
	GPIO4A6_MASK		= GENMASK(11, 8),
	GPIO4A6_UART3_RX_M2	= 10,
};

/* GPIO4B_IOMUX_SEL_L */
enum {
	GPIO4B0_SHIFT		= 0,
	GPIO4B0_MASK		= GENMASK(3, 0),
	GPIO4B0_UART8_TX_M0	= 10,

	GPIO4B1_SHIFT		= 4,
	GPIO4B1_MASK		= GENMASK(7, 4),
	GPIO4B1_UART8_RX_M0	= 10,
};

/* GPIO4B_IOMUX_SEL_H */
enum {
	GPIO4B4_SHIFT		= 0,
	GPIO4B4_MASK		= GENMASK(3, 0),
	GPIO4B4_UART9_TX_M1	= 10,

	GPIO4B5_SHIFT		= 4,
	GPIO4B5_MASK		= GENMASK(7, 4),
	GPIO4B5_UART9_RX_M1	= 10,
};

/* GPIO4D_IOMUX_SEL_L */
enum {
	GPIO4D0_SHIFT		= 0,
	GPIO4D0_MASK		= GENMASK(3, 0),
	GPIO4D0_GPIO		= 0,
	GPIO4D0_SDMMC_D0	= 1,
	GPIO4D0_PDM1_SDI3_M0	= 2,
	GPIO4D0_JTAG_TCK_M1	= 5,
	GPIO4D0_I2C3_SCL_M4	= 9,
	GPIO4D0_UART2_TX_M1	= 10,
	GPIO4D0_PWM8_M1		= 12,

	GPIO4D1_SHIFT		= 4,
	GPIO4D1_MASK		= GENMASK(7, 4),
	GPIO4D1_GPIO		= 0,
	GPIO4D1_SDMMC_D1	= 1,
	GPIO4D1_PDM1_SDI2_M0	= 2,
	GPIO4D1_JTAG_TMS_M1	= 5,
	GPIO4D1_I2C3_SDA_M4	= 9,
	GPIO4D1_UART2_RX_M1	= 10,
	GPIO4D1_PWM9_M1		= 12,
};

/* GPIO4D_IOMUX_SEL_H */
enum {
	GPIO4D4_SHIFT		= 0,
	GPIO4D4_MASK		= GENMASK(3, 0),
	GPIO4D4_UART5_RX_M0	= 10,

	GPIO4D5_SHIFT		= 4,
	GPIO4D5_MASK		= GENMASK(7, 4),
	GPIO4D5_UART5_TX_M0	= 10,
};

void board_debug_uart_init(void)
{
	__maybe_unused static struct rk3588_bus_ioc * const bus_ioc = (void *)BUS_IOC_BASE;

/* UART 0 */
#if defined(CONFIG_DEBUG_UART_BASE) && (CONFIG_DEBUG_UART_BASE == 0xfd890000)

#if defined(CONFIG_ROCKCHIP_UART_MUX_SEL_M) && \
	(CONFIG_ROCKCHIP_UART_MUX_SEL_M == 0)
	static struct rk3588_pmu2_ioc * const pmu2_ioc = (void *)PMU2_IOC_BASE;

	/* UART0_M0 Switch iomux */
	rk_clrsetreg(&pmu2_ioc->gpio0c_iomux_sel_h,
			GPIO0C4_MASK | GPIO0C5_MASK,
			GPIO0C4_UART0_RX_M0 << GPIO0C4_SHIFT |
			GPIO0C5_UART0_TX_M0 << GPIO0C5_SHIFT);

#elif defined(CONFIG_ROCKCHIP_UART_MUX_SEL_M) && \
	(CONFIG_ROCKCHIP_UART_MUX_SEL_M == 1)
	static struct rk3588_pmu1_ioc * const pmu1_ioc = (void *)PMU1_IOC_BASE;

	/* UART0_M1 Switch iomux */
	rk_clrsetreg(&pmu1_ioc->gpio0b_iomux_sel_l,
			GPIO0B0_MASK | GPIO0B1_MASK,
			GPIO0B0_UART0_RX_M1 << GPIO0B0_SHIFT |
			GPIO0B1_UART0_TX_M1 << GPIO0B1_SHIFT);

#elif defined(CONFIG_ROCKCHIP_UART_MUX_SEL_M) && \
	(CONFIG_ROCKCHIP_UART_MUX_SEL_M == 2)

	/* UART0_M2 Switch iomux */
	rk_clrsetreg(&bus_ioc->gpio4a_iomux_sel_h,
			GPIO4A4_MASK,
			GPIO4A4_UART0_RX_M2 << GPIO4A4_SHIFT);
	rk_clrsetreg(&bus_ioc->gpio4a_iomux_sel_l,
			GPIO4A3_MASK,
			GPIO4A3_UART0_TX_M2 << GPIO4A3_SHIFT);

#endif

/* UART 1 */
#elif defined(CONFIG_DEBUG_UART_BASE) && (CONFIG_DEBUG_UART_BASE == 0xfeb40000)
#if defined(CONFIG_ROCKCHIP_UART_MUX_SEL_M) && \
	(CONFIG_ROCKCHIP_UART_MUX_SEL_M == 0)

	/* UART1_M0 Switch iomux */
	rk_clrsetreg(&bus_ioc->gpio2b_iomux_sel_h,
			GPIO2B6_MASK | GPIO2B7_MASK,
			GPIO2B6_UART1_RX_M0 << GPIO2B6_SHIFT |
			GPIO2B7_UART1_TX_M0 << GPIO2B7_SHIFT);

#elif defined(CONFIG_ROCKCHIP_UART_MUX_SEL_M) && \
	(CONFIG_ROCKCHIP_UART_MUX_SEL_M == 1)

	/* UART1_M1 Switch iomux */
	rk_clrsetreg(&bus_ioc->gpio1b_iomux_sel_h,
			GPIO1B7_MASK | GPIO1B6_MASK,
			GPIO1B7_UART1_RX_M1 << GPIO1B7_SHIFT |
			GPIO1B6_UART1_TX_M1 << GPIO1B6_SHIFT);

#elif defined(CONFIG_ROCKCHIP_UART_MUX_SEL_M) && \
	(CONFIG_ROCKCHIP_UART_MUX_SEL_M == 2)

	static struct rk3588_pmu2_ioc * const pmu2_ioc = (void *)PMU2_IOC_BASE;

	/* Refer to BUS_IOC */
	rk_clrsetreg(&pmu2_ioc->gpio0d_iomux_sel_l,
			GPIO0D2_MASK | GPIO0D1_MASK,
			GPIO0D2_REFER << GPIO0D2_SHIFT |
			GPIO0D1_REFER << GPIO0D1_SHIFT);

	/* UART1_M2 Switch iomux */
	rk_clrsetreg(&bus_ioc->gpio0d_iomux_sel_l,
			GPIO0D2_MASK | GPIO0D1_MASK,
			GPIO0D2_UART1_RX_M2 << GPIO0D2_SHIFT |
			GPIO0D1_UART1_TX_M2 << GPIO0D1_SHIFT);

#endif

/* UART 2 */
#elif defined(CONFIG_DEBUG_UART_BASE) && (CONFIG_DEBUG_UART_BASE == 0xfeb50000)
#if defined(CONFIG_ROCKCHIP_UART_MUX_SEL_M) && \
	(CONFIG_ROCKCHIP_UART_MUX_SEL_M == 0)

	static struct rk3588_pmu2_ioc * const pmu2_ioc = (void *)PMU2_IOC_BASE;

	/* Refer to BUS_IOC */
	rk_clrsetreg(&pmu2_ioc->gpio0b_iomux_sel_h,
			GPIO0B6_MASK | GPIO0B5_MASK,
			GPIO0B6_REFER << GPIO0B6_SHIFT |
			GPIO0B5_REFER << GPIO0B5_SHIFT);

	/* UART2_M0 Switch iomux */
	rk_clrsetreg(&bus_ioc->gpio0b_iomux_sel_h,
			GPIO0B6_MASK | GPIO0B5_MASK,
			GPIO0B6_UART2_RX_M0 << GPIO0B6_SHIFT |
			GPIO0B5_UART2_TX_M0 << GPIO0B5_SHIFT);

#elif defined(CONFIG_ROCKCHIP_UART_MUX_SEL_M) && \
	(CONFIG_ROCKCHIP_UART_MUX_SEL_M == 1)

	/* UART2_M1 Switch iomux */
	rk_clrsetreg(&bus_ioc->gpio4d_iomux_sel_l,
			GPIO4D1_MASK | GPIO4D0_MASK,
			GPIO4D1_UART2_RX_M1 << GPIO4D1_SHIFT |
			GPIO4D0_UART2_TX_M1 << GPIO4D0_SHIFT);

#elif defined(CONFIG_ROCKCHIP_UART_MUX_SEL_M) && \
	(CONFIG_ROCKCHIP_UART_MUX_SEL_M == 2)

	/* UART2_M2 Switch iomux */
	rk_clrsetreg(&bus_ioc->gpio3b_iomux_sel_l,
			GPIO3B2_MASK | GPIO3B1_MASK,
			GPIO3B2_UART2_RX_M2 << GPIO3B2_SHIFT |
			GPIO3B1_UART2_TX_M2 << GPIO3B1_SHIFT);

#endif

/* UART 3 */
#elif defined(CONFIG_DEBUG_UART_BASE) && (CONFIG_DEBUG_UART_BASE == 0xfeb60000)
#if defined(CONFIG_ROCKCHIP_UART_MUX_SEL_M) && \
	(CONFIG_ROCKCHIP_UART_MUX_SEL_M == 0)

	/* UART3_M0 Switch iomux */
	rk_clrsetreg(&bus_ioc->gpio1c_iomux_sel_l,
			GPIO1C0_MASK | GPIO1C1_MASK,
			GPIO1C0_UART3_RX_M0 << GPIO1C0_SHIFT |
			GPIO1C1_UART3_TX_M0 << GPIO1C1_SHIFT);

#elif defined(CONFIG_ROCKCHIP_UART_MUX_SEL_M) && \
	(CONFIG_ROCKCHIP_UART_MUX_SEL_M == 1)

	/* UART3_M1 Switch iomux */
	rk_clrsetreg(&bus_ioc->gpio3b_iomux_sel_h,
			GPIO3B6_MASK | GPIO3B5_MASK,
			GPIO3B6_UART3_RX_M1 << GPIO3B6_SHIFT |
			GPIO3B5_UART3_TX_M1 << GPIO3B5_SHIFT);

#elif defined(CONFIG_ROCKCHIP_UART_MUX_SEL_M) && \
	(CONFIG_ROCKCHIP_UART_MUX_SEL_M == 2)

	/* UART3_M2 Switch iomux */
	rk_clrsetreg(&bus_ioc->gpio4a_iomux_sel_h,
			GPIO4A6_MASK | GPIO4A5_MASK,
			GPIO4A6_UART3_RX_M2 << GPIO4A6_SHIFT |
			GPIO4A5_UART3_TX_M2 << GPIO4A5_SHIFT);

#endif

/* UART 4 */
#elif defined(CONFIG_DEBUG_UART_BASE) && (CONFIG_DEBUG_UART_BASE == 0xfeb70000)
#if defined(CONFIG_ROCKCHIP_UART_MUX_SEL_M) && \
	(CONFIG_ROCKCHIP_UART_MUX_SEL_M == 0)

	/* UART4_M0 Switch iomux */
	rk_clrsetreg(&bus_ioc->gpio1d_iomux_sel_l,
			GPIO1D3_MASK | GPIO1D2_MASK,
			GPIO1D3_UART4_RX_M0 << GPIO1D3_SHIFT |
			GPIO1D2_UART4_TX_M0 << GPIO1D2_SHIFT);

#elif defined(CONFIG_ROCKCHIP_UART_MUX_SEL_M) && \
	(CONFIG_ROCKCHIP_UART_MUX_SEL_M == 1)

	/* UART4_M1 Switch iomux */
	rk_clrsetreg(&bus_ioc->gpio3d_iomux_sel_l,
			GPIO3D0_MASK | GPIO3D1_MASK,
			GPIO3D0_UART4_RX_M1 << GPIO3D0_SHIFT |
			GPIO3D1_UART4_TX_M1 << GPIO3D1_SHIFT);

#elif defined(CONFIG_ROCKCHIP_UART_MUX_SEL_M) && \
	(CONFIG_ROCKCHIP_UART_MUX_SEL_M == 2)

	/* UART4_M2 Switch iomux */
	rk_clrsetreg(&bus_ioc->gpio1b_iomux_sel_l,
			GPIO1B2_MASK | GPIO1B3_MASK,
			GPIO1B2_UART4_RX_M2 << GPIO1B2_SHIFT |
			GPIO1B3_UART4_TX_M2 << GPIO1B3_SHIFT);

#endif

/* UART 5 */
#elif defined(CONFIG_DEBUG_UART_BASE) && (CONFIG_DEBUG_UART_BASE == 0xfeb80000)
#if defined(CONFIG_ROCKCHIP_UART_MUX_SEL_M) && \
	(CONFIG_ROCKCHIP_UART_MUX_SEL_M == 0)

	/* UART5_M0 Switch iomux */
	rk_clrsetreg(&bus_ioc->gpio4d_iomux_sel_h,
			GPIO4D4_MASK | GPIO4D5_MASK,
			GPIO4D4_UART5_RX_M0 << GPIO4D4_SHIFT |
			GPIO4D5_UART5_TX_M0 << GPIO4D5_SHIFT);

#elif defined(CONFIG_ROCKCHIP_UART_MUX_SEL_M) && \
	(CONFIG_ROCKCHIP_UART_MUX_SEL_M == 1)

	/* UART5_M1 Switch iomux */
	rk_clrsetreg(&bus_ioc->gpio3c_iomux_sel_h,
			GPIO3C5_MASK | GPIO3C4_MASK,
			GPIO3C5_UART5_RX_M1 << GPIO3C5_SHIFT |
			GPIO3C4_UART5_TX_M1 << GPIO3C4_SHIFT);

#elif defined(CONFIG_ROCKCHIP_UART_MUX_SEL_M) && \
	(CONFIG_ROCKCHIP_UART_MUX_SEL_M == 2)

	/* UART5_M2 Switch iomux */
	rk_clrsetreg(&bus_ioc->gpio2d_iomux_sel_h,
			GPIO2D4_MASK | GPIO2D5_MASK,
			GPIO2D4_UART5_RX_M2 << GPIO2D4_SHIFT |
			GPIO2D5_UART5_TX_M2 << GPIO2D5_SHIFT);

#endif

/* UART 6 */
#elif defined(CONFIG_DEBUG_UART_BASE) && (CONFIG_DEBUG_UART_BASE == 0xfeb90000)
#if defined(CONFIG_ROCKCHIP_UART_MUX_SEL_M) && \
	(CONFIG_ROCKCHIP_UART_MUX_SEL_M == 0)

	/* UART6_M0 Switch iomux */
	rk_clrsetreg(&bus_ioc->gpio2a_iomux_sel_h,
			GPIO2A6_MASK | GPIO2A7_MASK,
			GPIO2A6_UART6_RX_M0 << GPIO2A6_SHIFT |
			GPIO2A7_UART6_TX_M0 << GPIO2A7_SHIFT);

#elif defined(CONFIG_ROCKCHIP_UART_MUX_SEL_M) && \
	(CONFIG_ROCKCHIP_UART_MUX_SEL_M == 1)

	/* UART6_M1 Switch iomux */
	rk_clrsetreg(&bus_ioc->gpio1a_iomux_sel_l,
			GPIO1A0_MASK | GPIO1A1_MASK,
			GPIO1A0_UART6_RX_M1 << GPIO1A0_SHIFT |
			GPIO1A1_UART6_TX_M1 << GPIO1A1_SHIFT);

#elif defined(CONFIG_ROCKCHIP_UART_MUX_SEL_M) && \
	(CONFIG_ROCKCHIP_UART_MUX_SEL_M == 2)

	/* UART6_M2 Switch iomux */
	rk_clrsetreg(&bus_ioc->gpio1d_iomux_sel_l,
			GPIO1D1_MASK | GPIO1D0_MASK,
			GPIO1D1_UART6_RX_M2 << GPIO1D1_SHIFT |
			GPIO1D0_UART6_TX_M2 << GPIO1D0_SHIFT);

#endif

/* UART 7 */
#elif defined(CONFIG_DEBUG_UART_BASE) && (CONFIG_DEBUG_UART_BASE == 0xfeba0000)
#if defined(CONFIG_ROCKCHIP_UART_MUX_SEL_M) && \
	(CONFIG_ROCKCHIP_UART_MUX_SEL_M == 0)

	/* UART7_M0 Switch iomux */
	rk_clrsetreg(&bus_ioc->gpio2b_iomux_sel_h,
			GPIO2B4_MASK | GPIO2B5_MASK,
			GPIO2B4_UART7_RX_M0 << GPIO2B4_SHIFT |
			GPIO2B5_UART7_TX_M0 << GPIO2B5_SHIFT);

#elif defined(CONFIG_ROCKCHIP_UART_MUX_SEL_M) && \
	(CONFIG_ROCKCHIP_UART_MUX_SEL_M == 1)

	/* UART7_M1 Switch iomux */
	rk_clrsetreg(&bus_ioc->gpio3c_iomux_sel_l,
			GPIO3C1_MASK | GPIO3C0_MASK,
			GPIO3C1_UART7_RX_M1 << GPIO3C1_SHIFT |
			GPIO3C0_UART7_TX_M1 << GPIO3C0_SHIFT);

#elif defined(CONFIG_ROCKCHIP_UART_MUX_SEL_M) && \
	(CONFIG_ROCKCHIP_UART_MUX_SEL_M == 2)

	/* UART7_M2 Switch iomux */
	rk_clrsetreg(&bus_ioc->gpio1b_iomux_sel_h,
			GPIO1B4_MASK | GPIO1B5_MASK,
			GPIO1B4_UART7_RX_M2 << GPIO1B4_SHIFT |
			GPIO1B5_UART7_TX_M2 << GPIO1B5_SHIFT);

#endif

/* UART 8 */
#elif defined(CONFIG_DEBUG_UART_BASE) && (CONFIG_DEBUG_UART_BASE == 0xfebb0000)
#if defined(CONFIG_ROCKCHIP_UART_MUX_SEL_M) && \
	(CONFIG_ROCKCHIP_UART_MUX_SEL_M == 0)

	/* UART8_M0 Switch iomux */
	rk_clrsetreg(&bus_ioc->gpio4b_iomux_sel_l,
			GPIO4B1_MASK | GPIO4B0_MASK,
			GPIO4B1_UART8_RX_M0 << GPIO4B1_SHIFT |
			GPIO4B0_UART8_TX_M0 << GPIO4B0_SHIFT);

#elif defined(CONFIG_ROCKCHIP_UART_MUX_SEL_M) && \
	(CONFIG_ROCKCHIP_UART_MUX_SEL_M == 1)

	/* UART8_M1 Switch iomux */
	rk_clrsetreg(&bus_ioc->gpio3a_iomux_sel_l,
			GPIO3A3_MASK | GPIO3A2_MASK,
			GPIO3A3_UART8_RX_M1 << GPIO3A3_SHIFT |
			GPIO3A2_UART8_TX_M1 << GPIO3A2_SHIFT);

#endif

/* UART 9 */
#elif defined(CONFIG_DEBUG_UART_BASE) && (CONFIG_DEBUG_UART_BASE == 0xfebc0000)
#if defined(CONFIG_ROCKCHIP_UART_MUX_SEL_M) && \
	(CONFIG_ROCKCHIP_UART_MUX_SEL_M == 0)

	/* UART9_M0 Switch iomux */
	rk_clrsetreg(&bus_ioc->gpio2c_iomux_sel_h,
			GPIO2C4_MASK,
			GPIO2C4_UART9_RX_M0 << GPIO2C4_SHIFT);

	/* UART9_M0 Switch iomux */
	rk_clrsetreg(&bus_ioc->gpio2c_iomux_sel_l,
			GPIO2C2_MASK,
			GPIO2C2_UART9_TX_M0 << GPIO2C2_SHIFT);

#elif defined(CONFIG_ROCKCHIP_UART_MUX_SEL_M) && \
	(CONFIG_ROCKCHIP_UART_MUX_SEL_M == 1)

	/* UART9_M1 Switch iomux */
	rk_clrsetreg(&bus_ioc->gpio4b_iomux_sel_h,
			GPIO4B5_MASK | GPIO4B4_MASK,
			GPIO4B5_UART9_RX_M1 << GPIO4B5_SHIFT |
			GPIO4B4_UART9_TX_M1 << GPIO4B4_SHIFT);

#elif defined(CONFIG_ROCKCHIP_UART_MUX_SEL_M) && \
	(CONFIG_ROCKCHIP_UART_MUX_SEL_M == 2)

	/* UART9_M2 Switch iomux */
	rk_clrsetreg(&bus_ioc->gpio3d_iomux_sel_h,
			GPIO3D4_MASK | GPIO3D5_MASK,
			GPIO3D4_UART9_RX_M2 << GPIO3D4_SHIFT |
			GPIO3D5_UART9_TX_M2 << GPIO3D5_SHIFT);

#endif

#endif
}

#ifdef CONFIG_SPL_BUILD
void rockchip_stimer_init(void)
{
	/* If Timer already enabled, don't re-init it */
	u32 reg = readl(CONFIG_ROCKCHIP_STIMER_BASE + 0x4);

	if (reg & 0x1)
		return;

	asm volatile("msr CNTFRQ_EL0, %0" : : "r" (COUNTER_FREQUENCY));
	writel(0xffffffff, CONFIG_ROCKCHIP_STIMER_BASE + 0x14);
	writel(0xffffffff, CONFIG_ROCKCHIP_STIMER_BASE + 0x18);
	writel(0x1, CONFIG_ROCKCHIP_STIMER_BASE + 0x4);
}

static u32 gpio4d_iomux_sel_l = 0xffffffff;
static u32 gpio4d_iomux_sel_h;
static u32 gpio0a_iomux_sel_h;

void spl_board_sd_iomux_save(void)
{
	struct rk3588_bus_ioc * const bus_ioc = (void *)BUS_IOC_BASE;
	struct rk3588_pmu1_ioc * const pmu1_ioc = (void *)PMU1_IOC_BASE;

	gpio4d_iomux_sel_l = readl(&bus_ioc->gpio4d_iomux_sel_l);
	gpio4d_iomux_sel_h = readl(&bus_ioc->gpio4d_iomux_sel_h);
	gpio0a_iomux_sel_h = readl(&pmu1_ioc->gpio0a_iomux_sel_h);
}

void spl_board_storages_fixup(struct spl_image_loader *loader)
{
	int ret = 0;

	if (!loader)
		return;

	if (loader->boot_device == BOOT_DEVICE_MMC2 && gpio4d_iomux_sel_l != 0xffffffff) {
		struct rk3588_bus_ioc * const bus_ioc = (void *)BUS_IOC_BASE;
		struct rk3588_pmu1_ioc * const pmu1_ioc = (void *)PMU1_IOC_BASE;
		struct mmc *mmc = NULL;
		bool no_card;

		ret = spl_mmc_find_device(&mmc, BOOT_DEVICE_MMC2);
		if (ret)
			return;

		no_card = mmc_getcd(mmc) == 0;
		if (no_card) {
			writel(0xffffuL << 16 | gpio4d_iomux_sel_l, &bus_ioc->gpio4d_iomux_sel_l);
			writel(0xffffuL << 16 | gpio4d_iomux_sel_h, &bus_ioc->gpio4d_iomux_sel_h);
			writel(0xffffuL << 16 | gpio0a_iomux_sel_h, &pmu1_ioc->gpio0a_iomux_sel_h);
		}
	}
}
#endif

#ifndef CONFIG_TPL_BUILD
int arch_cpu_init(void)
{
#ifdef CONFIG_SPL_BUILD
	int secure_reg;

	/* Set the SDMMC eMMC crypto_ns FSPI access secure area */
	secure_reg = readl(FIREWALL_DDR_BASE + FW_DDR_MST5_REG);
	secure_reg &= 0xffff;
	writel(secure_reg, FIREWALL_DDR_BASE + FW_DDR_MST5_REG);
	secure_reg = readl(FIREWALL_DDR_BASE + FW_DDR_MST13_REG);
	secure_reg &= 0xffff;
	writel(secure_reg, FIREWALL_DDR_BASE + FW_DDR_MST13_REG);
	secure_reg = readl(FIREWALL_DDR_BASE + FW_DDR_MST21_REG);
	secure_reg &= 0xffff;
	writel(secure_reg, FIREWALL_DDR_BASE + FW_DDR_MST21_REG);
	secure_reg = readl(FIREWALL_DDR_BASE + FW_DDR_MST26_REG);
	secure_reg &= 0xffff;
	writel(secure_reg, FIREWALL_DDR_BASE + FW_DDR_MST26_REG);
	secure_reg = readl(FIREWALL_DDR_BASE + FW_DDR_MST27_REG);
	secure_reg &= 0xffff0000;
	writel(secure_reg, FIREWALL_DDR_BASE + FW_DDR_MST27_REG);

	secure_reg = readl(FIREWALL_SYSMEM_BASE + FW_SYSM_MST5_REG);
	secure_reg &= 0xffff;
	writel(secure_reg, FIREWALL_SYSMEM_BASE + FW_SYSM_MST5_REG);
	secure_reg = readl(FIREWALL_SYSMEM_BASE + FW_SYSM_MST13_REG);
	secure_reg &= 0xffff;
	writel(secure_reg, FIREWALL_SYSMEM_BASE + FW_SYSM_MST13_REG);
	secure_reg = readl(FIREWALL_SYSMEM_BASE + FW_SYSM_MST21_REG);
	secure_reg &= 0xffff;
	writel(secure_reg, FIREWALL_SYSMEM_BASE + FW_SYSM_MST21_REG);
	secure_reg = readl(FIREWALL_SYSMEM_BASE + FW_SYSM_MST26_REG);
	secure_reg &= 0xffff;
	writel(secure_reg, FIREWALL_SYSMEM_BASE + FW_SYSM_MST26_REG);
	secure_reg = readl(FIREWALL_SYSMEM_BASE + FW_SYSM_MST27_REG);
	secure_reg &= 0xffff0000;
	writel(secure_reg, FIREWALL_SYSMEM_BASE + FW_SYSM_MST27_REG);

	/* Select clk_tx source as default for i2s2/i2s3 */
	writel(0x03400340, SYS_GRF_BASE + SYS_GRF_SOC_CON6);

	if (readl(BUS_IOC_BASE + BUS_IOC_GPIO2D_IOMUX_SEL_L) == 0x2222) {
		writel(0x00070002, EMMC_IOC_BASE + EMMC_IOC_GPIO2A_DS_L);
		writel(0x77772222, EMMC_IOC_BASE + EMMC_IOC_GPIO2D_DS_L);
		writel(0x07000200, EMMC_IOC_BASE + EMMC_IOC_GPIO2D_DS_H);
	} else if (readl(BUS_IOC_BASE + BUS_IOC_GPIO2D_IOMUX_SEL_L) == 0x1111) {
		/*
		 * set the emmc io drive strength:
		 * data and cmd: 50ohm
		 * clock: 25ohm
		 */
		writel(0x00770052, EMMC_IOC_BASE + EMMC_IOC_GPIO2A_DS_L);
		writel(0x77772222, EMMC_IOC_BASE + EMMC_IOC_GPIO2D_DS_L);
		writel(0x77772222, EMMC_IOC_BASE + EMMC_IOC_GPIO2D_DS_H);
	} else if ((readl(BUS_IOC_BASE + BUS_IOC_GPIO2B_IOMUX_SEL_L) & 0xf0ff) == 0x3033) {
		writel(0x33002200, VCCIO3_5_IOC_BASE + IOC_VCCIO3_5_GPIO2A_DS_H);
		writel(0x30332022, VCCIO3_5_IOC_BASE + IOC_VCCIO3_5_GPIO2B_DS_L);
		writel(0x00030002, VCCIO3_5_IOC_BASE + IOC_VCCIO3_5_GPIO2B_DS_H);
	} else if (readl(BUS_IOC_BASE + BUS_IOC_GPIO3A_IOMUX_SEL_L) == 0x5555) {
		writel(0x77772222, VCCIO3_5_IOC_BASE + IOC_VCCIO3_5_GPIO3A_DS_L);
		writel(0x00700020, VCCIO3_5_IOC_BASE + IOC_VCCIO3_5_GPIO3A_DS_H);
		writel(0x00070002, VCCIO3_5_IOC_BASE + IOC_VCCIO3_5_GPIO3C_DS_H);
	}

	/*
	 * Assert reset the pipephy0, pipephy1 and pipephy2,
	 * and de-assert reset them in Kernel combphy driver.
	 */
	writel(0x01c001c0, CRU_BASE + CRU_SOFTRST_CON77);

	/*
	 * Assert SIDDQ for USB 2.0 PHY1, PHY2 and PHY3 to
	 * power down all analog block to save power. And
	 * PHY0 for OTG0 interface still in normal mode.
	 */
	writel(0x20002000, USB2PHY1_GRF_BASE + USB2PHY_GRF_CON2);
	writel(0x20002000, USB2PHY2_GRF_BASE + USB2PHY_GRF_CON2);
	writel(0x20002000, USB2PHY3_GRF_BASE + USB2PHY_GRF_CON2);

	/* Assert hdptxphy init,cmn,lane reset */
	writel(0xb800b800, PMU1CRU_BASE + PMU1CRU_SOFTRST_CON03);
	writel(0x00030003, PMU1CRU_BASE + PMU1CRU_SOFTRST_CON04);

	spl_board_sd_iomux_save();
#endif
	/* Select usb otg0 phy status to 0 that make rockusb can work at high-speed */
	writel(0x00080008, USBGRF_BASE + USB_GRF_USB3OTG0_CON1);

	return 0;
}
#endif
