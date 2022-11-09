/*
 * (C) Copyright 2018 Rockchip Electronics Co., Ltd
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */

#include <common.h>
#include <dm.h>
#include <dm/pinctrl.h>
#include <dm/ofnode.h>
#include <linux/bitops.h>
#include <regmap.h>
#include <syscon.h>
#include <asm/arch-rockchip/cpu.h>
#include <dt-bindings/pinctrl/rockchip.h>

#define MAX_ROCKCHIP_GPIO_PER_BANK	32
#define RK_FUNC_GPIO			0
#define MAX_ROCKCHIP_PINS_ENTRIES	30

enum rockchip_pinctrl_type {
	PX30,
	RV1108,
	RV1126,
	RK1808,
	RK2928,
	RK3066B,
	RK3128,
	RK3188,
	RK3288,
	RK3308,
	RK3368,
	RK3399,
};

#define RK_GENMASK_VAL(h, l, v) \
	(GENMASK(((h) + 16), ((l) + 16)) | (((v) << (l)) & GENMASK((h), (l))))

/**
 * Encode variants of iomux registers into a type variable
 */
#define IOMUX_GPIO_ONLY		BIT(0)
#define IOMUX_WIDTH_4BIT	BIT(1)
#define IOMUX_SOURCE_PMU	BIT(2)
#define IOMUX_UNROUTED		BIT(3)
#define IOMUX_WIDTH_3BIT	BIT(4)
#define IOMUX_8WIDTH_2BIT	BIT(5)
#define IOMUX_WRITABLE_32BIT	BIT(6)
#define IOMUX_L_SOURCE_PMU	BIT(7)

/**
 * @type: iomux variant using IOMUX_* constants
 * @offset: if initialized to -1 it will be autocalculated, by specifying
 *	    an initial offset value the relevant source offset can be reset
 *	    to a new value for autocalculating the following iomux registers.
 */
struct rockchip_iomux {
	int				type;
	int				offset;
};

#define DRV_TYPE_IO_MASK		GENMASK(31, 16)
#define DRV_TYPE_WRITABLE_32BIT		BIT(31)

/**
 * enum type index corresponding to rockchip_perpin_drv_list arrays index.
 */
enum rockchip_pin_drv_type {
	DRV_TYPE_IO_DEFAULT = 0,
	DRV_TYPE_IO_1V8_OR_3V0,
	DRV_TYPE_IO_1V8_ONLY,
	DRV_TYPE_IO_1V8_3V0_AUTO,
	DRV_TYPE_IO_3V3_ONLY,
	DRV_TYPE_IO_SMIC,
	DRV_TYPE_MAX
};

#define PULL_TYPE_IO_MASK		GENMASK(31, 16)
#define PULL_TYPE_WRITABLE_32BIT	BIT(31)

/**
 * enum type index corresponding to rockchip_pull_list arrays index.
 */
enum rockchip_pin_pull_type {
	PULL_TYPE_IO_DEFAULT = 0,
	PULL_TYPE_IO_1V8_ONLY,
	PULL_TYPE_MAX
};

/**
 * enum mux route register type, should be invalid/default/topgrf/pmugrf.
 * INVALID: means do not need to set mux route
 * DEFAULT: means same regmap as pin iomux
 * TOPGRF: means mux route setting in topgrf
 * PMUGRF: means mux route setting in pmugrf
 */
enum rockchip_pin_route_type {
	ROUTE_TYPE_DEFAULT = 0,
	ROUTE_TYPE_TOPGRF = 1,
	ROUTE_TYPE_PMUGRF = 2,

	ROUTE_TYPE_INVALID = -1,
};

/**
 * @drv_type: drive strength variant using rockchip_perpin_drv_type
 * @offset: if initialized to -1 it will be autocalculated, by specifying
 *	    an initial offset value the relevant source offset can be reset
 *	    to a new value for autocalculating the following drive strength
 *	    registers. if used chips own cal_drv func instead to calculate
 *	    registers offset, the variant could be ignored.
 */
struct rockchip_drv {
	enum rockchip_pin_drv_type	drv_type;
	int				offset;
};

/**
 * @priv: common pinctrl private basedata
 * @pin_base: first pin number
 * @nr_pins: number of pins in this bank
 * @name: name of the bank
 * @bank_num: number of the bank, to account for holes
 * @iomux: array describing the 4 iomux sources of the bank
 * @drv: array describing the 4 drive strength sources of the bank
 * @pull_type: array describing the 4 pull type sources of the bank
 * @recalced_mask: bits describing the mux recalced pins of per bank
 * @route_mask: bits describing the routing pins of per bank
 */
struct rockchip_pin_bank {
	struct rockchip_pinctrl_priv	*priv;
	u32				pin_base;
	u8				nr_pins;
	char				*name;
	u8				bank_num;
	struct rockchip_iomux		iomux[4];
	struct rockchip_drv		drv[4];
	enum rockchip_pin_pull_type	pull_type[4];
	u32				recalced_mask;
	u32				route_mask;
};

#define PIN_BANK(id, pins, label)			\
	{						\
		.bank_num	= id,			\
		.nr_pins	= pins,			\
		.name		= label,		\
		.iomux		= {			\
			{ .offset = -1 },		\
			{ .offset = -1 },		\
			{ .offset = -1 },		\
			{ .offset = -1 },		\
		},					\
	}

#define PIN_BANK_IOMUX_FLAGS(id, pins, label, iom0, iom1, iom2, iom3)	\
	{								\
		.bank_num	= id,					\
		.nr_pins	= pins,					\
		.name		= label,				\
		.iomux		= {					\
			{ .type = iom0, .offset = -1 },			\
			{ .type = iom1, .offset = -1 },			\
			{ .type = iom2, .offset = -1 },			\
			{ .type = iom3, .offset = -1 },			\
		},							\
	}

#define PIN_BANK_IOMUX_FLAGS_OFFSET(id, pins, label, iom0, iom1, iom2,	\
				    iom3, offset0, offset1, offset2,	\
				    offset3)				\
	{								\
		.bank_num	= id,					\
		.nr_pins	= pins,					\
		.name		= label,				\
		.iomux		= {					\
			{ .type = iom0, .offset = offset0 },		\
			{ .type = iom1, .offset = offset1 },		\
			{ .type = iom2, .offset = offset2 },		\
			{ .type = iom3, .offset = offset3 },		\
		},							\
	}

#define PIN_BANK_DRV_FLAGS(id, pins, label, type0, type1, type2, type3) \
	{								\
		.bank_num	= id,					\
		.nr_pins	= pins,					\
		.name		= label,				\
		.iomux		= {					\
			{ .offset = -1 },				\
			{ .offset = -1 },				\
			{ .offset = -1 },				\
			{ .offset = -1 },				\
		},							\
		.drv		= {					\
			{ .drv_type = type0, .offset = -1 },		\
			{ .drv_type = type1, .offset = -1 },		\
			{ .drv_type = type2, .offset = -1 },		\
			{ .drv_type = type3, .offset = -1 },		\
		},							\
	}

#define PIN_BANK_DRV_FLAGS_PULL_FLAGS(id, pins, label, drv0, drv1,	\
				      drv2, drv3, pull0, pull1,		\
				      pull2, pull3)			\
	{								\
		.bank_num	= id,					\
		.nr_pins	= pins,					\
		.name		= label,				\
		.iomux		= {					\
			{ .offset = -1 },				\
			{ .offset = -1 },				\
			{ .offset = -1 },				\
			{ .offset = -1 },				\
		},							\
		.drv		= {					\
			{ .drv_type = drv0, .offset = -1 },		\
			{ .drv_type = drv1, .offset = -1 },		\
			{ .drv_type = drv2, .offset = -1 },		\
			{ .drv_type = drv3, .offset = -1 },		\
		},							\
		.pull_type[0] = pull0,					\
		.pull_type[1] = pull1,					\
		.pull_type[2] = pull2,					\
		.pull_type[3] = pull3,					\
	}

#define PIN_BANK_IOMUX_DRV_FLAGS_OFFSET(id, pins, label, iom0, iom1,	\
					iom2, iom3, drv0, drv1, drv2,	\
					drv3, offset0, offset1,		\
					offset2, offset3)		\
	{								\
		.bank_num	= id,					\
		.nr_pins	= pins,					\
		.name		= label,				\
		.iomux		= {					\
			{ .type = iom0, .offset = -1 },			\
			{ .type = iom1, .offset = -1 },			\
			{ .type = iom2, .offset = -1 },			\
			{ .type = iom3, .offset = -1 },			\
		},							\
		.drv		= {					\
			{ .drv_type = drv0, .offset = offset0 },	\
			{ .drv_type = drv1, .offset = offset1 },	\
			{ .drv_type = drv2, .offset = offset2 },	\
			{ .drv_type = drv3, .offset = offset3 },	\
		},							\
	}

#define PIN_BANK_IOMUX_DRV_PULL_FLAGS(id, pins, label, iom0, iom1,	\
				      iom2, iom3, drv0, drv1, drv2,	\
				      drv3, pull0, pull1, pull2,	\
				      pull3)				\
	{								\
		.bank_num	= id,					\
		.nr_pins	= pins,					\
		.name		= label,				\
		.iomux		= {					\
			{ .type = iom0, .offset = -1 },			\
			{ .type = iom1, .offset = -1 },			\
			{ .type = iom2, .offset = -1 },			\
			{ .type = iom3, .offset = -1 },			\
		},							\
		.drv		= {					\
			{ .drv_type = drv0, .offset = -1 },		\
			{ .drv_type = drv1, .offset = -1 },		\
			{ .drv_type = drv2, .offset = -1 },		\
			{ .drv_type = drv3, .offset = -1 },		\
		},							\
		.pull_type[0] = pull0,					\
		.pull_type[1] = pull1,					\
		.pull_type[2] = pull2,					\
		.pull_type[3] = pull3,					\
	}

#define PIN_BANK_IOMUX_FLAGS_DRV_FLAGS_OFFSET_PULL_FLAGS(id, pins,	\
					      label, iom0, iom1, iom2,  \
					      iom3, drv0, drv1, drv2,   \
					      drv3, offset0, offset1,   \
					      offset2, offset3, pull0,  \
					      pull1, pull2, pull3)	\
	{								\
		.bank_num	= id,					\
		.nr_pins	= pins,					\
		.name		= label,				\
		.iomux		= {					\
			{ .type = iom0, .offset = -1 },			\
			{ .type = iom1, .offset = -1 },			\
			{ .type = iom2, .offset = -1 },			\
			{ .type = iom3, .offset = -1 },			\
		},							\
		.drv		= {					\
			{ .drv_type = drv0, .offset = offset0 },	\
			{ .drv_type = drv1, .offset = offset1 },	\
			{ .drv_type = drv2, .offset = offset2 },	\
			{ .drv_type = drv3, .offset = offset3 },	\
		},							\
		.pull_type[0] = pull0,					\
		.pull_type[1] = pull1,					\
		.pull_type[2] = pull2,					\
		.pull_type[3] = pull3,					\
	}

#define PIN_BANK_MUX_ROUTE_FLAGS(ID, PIN, FUNC, REG, VAL, FLAG)		\
	{								\
		.bank_num	= ID,					\
		.pin		= PIN,					\
		.func		= FUNC,					\
		.route_offset	= REG,					\
		.route_val	= VAL,					\
		.route_type	= FLAG,					\
	}

#define MR_DEFAULT(ID, PIN, FUNC, REG, VAL)	\
	PIN_BANK_MUX_ROUTE_FLAGS(ID, PIN, FUNC, REG, VAL, ROUTE_TYPE_DEFAULT)

#define MR_TOPGRF(ID, PIN, FUNC, REG, VAL)	\
	PIN_BANK_MUX_ROUTE_FLAGS(ID, PIN, FUNC, REG, VAL, ROUTE_TYPE_TOPGRF)

#define MR_PMUGRF(ID, PIN, FUNC, REG, VAL)	\
	PIN_BANK_MUX_ROUTE_FLAGS(ID, PIN, FUNC, REG, VAL, ROUTE_TYPE_PMUGRF)

/**
 * struct rockchip_mux_recalced_data: represent a pin iomux data.
 * @num: bank number.
 * @pin: pin number.
 * @bit: index at register.
 * @reg: register offset.
 * @mask: mask bit
 */
struct rockchip_mux_recalced_data {
	u8 num;
	u8 pin;
	u32 reg;
	u8 bit;
	u8 mask;
};

/**
 * struct rockchip_mux_recalced_data: represent a pin iomux data.
 * @bank_num: bank number.
 * @pin: index at register or used to calc index.
 * @func: the min pin.
 * @route_type: the register type.
 * @route_offset: the max pin.
 * @route_val: the register offset.
 */
struct rockchip_mux_route_data {
	u8 bank_num;
	u8 pin;
	u8 func;
	enum rockchip_pin_route_type route_type : 8;
	u32 route_offset;
	u32 route_val;
};

/**
 */
struct rockchip_pin_ctrl {
	struct rockchip_pin_bank	*pin_banks;
	u32				nr_banks;
	u32				nr_pins;
	char				*label;
	enum rockchip_pinctrl_type	type;
	int				grf_mux_offset;
	int				pmu_mux_offset;
	int				grf_drv_offset;
	int				pmu_drv_offset;
	struct rockchip_mux_recalced_data *iomux_recalced;
	u32				niomux_recalced;
	struct rockchip_mux_route_data *iomux_routes;
	u32				niomux_routes;

	int	(*ctrl_data_re_init)(const struct rockchip_pin_ctrl *ctrl);

	int	(*soc_data_init)(struct rockchip_pinctrl_priv *info);

	void	(*pull_calc_reg)(struct rockchip_pin_bank *bank,
				 int pin_num, struct regmap **regmap,
				 int *reg, u8 *bit);
	void	(*drv_calc_reg)(struct rockchip_pin_bank *bank,
				int pin_num, struct regmap **regmap,
				int *reg, u8 *bit);
	int	(*schmitt_calc_reg)(struct rockchip_pin_bank *bank,
				    int pin_num, struct regmap **regmap,
				    int *reg, u8 *bit);
	int	(*slew_rate_calc_reg)(struct rockchip_pin_bank *bank,
				      int pin_num, struct regmap **regmap,
				      int *reg, u8 *bit);
};

/**
 */
struct rockchip_pinctrl_priv {
	struct rockchip_pin_ctrl	*ctrl;
	struct regmap			*regmap_base;
	struct regmap			*regmap_pmu;

};

static int rockchip_verify_config(struct udevice *dev, u32 bank, u32 pin)
{
	struct rockchip_pinctrl_priv *priv = dev_get_priv(dev);
	struct rockchip_pin_ctrl *ctrl = priv->ctrl;

	if (bank >= ctrl->nr_banks) {
		debug("pin conf bank %d >= nbanks %d\n", bank, ctrl->nr_banks);
		return -EINVAL;
	}

	if (pin >= MAX_ROCKCHIP_GPIO_PER_BANK) {
		debug("pin conf pin %d >= %d\n", pin,
		      MAX_ROCKCHIP_GPIO_PER_BANK);
		return -EINVAL;
	}

	return 0;
}

static struct rockchip_mux_recalced_data rv1108_mux_recalced_data[] = {
	{
		.num = 1,
		.pin = 0,
		.reg = 0x418,
		.bit = 0,
		.mask = 0x3
	}, {
		.num = 1,
		.pin = 1,
		.reg = 0x418,
		.bit = 2,
		.mask = 0x3
	}, {
		.num = 1,
		.pin = 2,
		.reg = 0x418,
		.bit = 4,
		.mask = 0x3
	}, {
		.num = 1,
		.pin = 3,
		.reg = 0x418,
		.bit = 6,
		.mask = 0x3
	}, {
		.num = 1,
		.pin = 4,
		.reg = 0x418,
		.bit = 8,
		.mask = 0x3
	}, {
		.num = 1,
		.pin = 5,
		.reg = 0x418,
		.bit = 10,
		.mask = 0x3
	}, {
		.num = 1,
		.pin = 6,
		.reg = 0x418,
		.bit = 12,
		.mask = 0x3
	}, {
		.num = 1,
		.pin = 7,
		.reg = 0x418,
		.bit = 14,
		.mask = 0x3
	}, {
		.num = 1,
		.pin = 8,
		.reg = 0x41c,
		.bit = 0,
		.mask = 0x3
	}, {
		.num = 1,
		.pin = 9,
		.reg = 0x41c,
		.bit = 2,
		.mask = 0x3
	},
};

static struct rockchip_mux_recalced_data rv1126_mux_recalced_data[] = {
	{
		.num = 0,
		.pin = 20,
		.reg = 0x10000,
		.bit = 0,
		.mask = 0xf
	},
	{
		.num = 0,
		.pin = 21,
		.reg = 0x10000,
		.bit = 4,
		.mask = 0xf
	},
	{
		.num = 0,
		.pin = 22,
		.reg = 0x10000,
		.bit = 8,
		.mask = 0xf
	},
	{
		.num = 0,
		.pin = 23,
		.reg = 0x10000,
		.bit = 12,
		.mask = 0xf
	},
};

static  struct rockchip_mux_recalced_data rk3128_mux_recalced_data[] = {
	{
		.num = 2,
		.pin = 20,
		.reg = 0xe8,
		.bit = 0,
		.mask = 0x7
	}, {
		.num = 2,
		.pin = 21,
		.reg = 0xe8,
		.bit = 4,
		.mask = 0x7
	}, {
		.num = 2,
		.pin = 22,
		.reg = 0xe8,
		.bit = 8,
		.mask = 0x7
	}, {
		.num = 2,
		.pin = 23,
		.reg = 0xe8,
		.bit = 12,
		.mask = 0x7
	}, {
		.num = 2,
		.pin = 24,
		.reg = 0xd4,
		.bit = 12,
		.mask = 0x7
	},
};

static struct rockchip_mux_recalced_data rk3308_mux_recalced_data[] = {
	{
		.num = 1,
		.pin = 14,
		.reg = 0x28,
		.bit = 12,
		.mask = 0x7
	}, {
		.num = 1,
		.pin = 15,
		.reg = 0x2c,
		.bit = 0,
		.mask = 0x3
	}, {
		.num = 1,
		.pin = 18,
		.reg = 0x30,
		.bit = 4,
		.mask = 0x7
	}, {
		.num = 1,
		.pin = 19,
		.reg = 0x30,
		.bit = 8,
		.mask = 0x7
	}, {
		.num = 1,
		.pin = 20,
		.reg = 0x30,
		.bit = 12,
		.mask = 0x7
	}, {
		.num = 1,
		.pin = 21,
		.reg = 0x34,
		.bit = 0,
		.mask = 0x7
	}, {
		.num = 1,
		.pin = 22,
		.reg = 0x34,
		.bit = 4,
		.mask = 0x7
	}, {
		.num = 1,
		.pin = 23,
		.reg = 0x34,
		.bit = 8,
		.mask = 0x7
	}, {
		.num = 3,
		.pin = 12,
		.reg = 0x68,
		.bit = 8,
		.mask = 0x7
	}, {
		.num = 3,
		.pin = 13,
		.reg = 0x68,
		.bit = 12,
		.mask = 0x7
	},
};

static struct rockchip_mux_recalced_data rk3308b_mux_recalced_data[] = {
	{
		.num = 1,
		.pin = 14,
		.reg = 0x28,
		.bit = 12,
		.mask = 0xf
	}, {
		.num = 1,
		.pin = 15,
		.reg = 0x2c,
		.bit = 0,
		.mask = 0x3
	}, {
		.num = 1,
		.pin = 18,
		.reg = 0x30,
		.bit = 4,
		.mask = 0xf
	}, {
		.num = 1,
		.pin = 19,
		.reg = 0x30,
		.bit = 8,
		.mask = 0xf
	}, {
		.num = 1,
		.pin = 20,
		.reg = 0x30,
		.bit = 12,
		.mask = 0xf
	}, {
		.num = 1,
		.pin = 21,
		.reg = 0x34,
		.bit = 0,
		.mask = 0xf
	}, {
		.num = 1,
		.pin = 22,
		.reg = 0x34,
		.bit = 4,
		.mask = 0xf
	}, {
		.num = 1,
		.pin = 23,
		.reg = 0x34,
		.bit = 8,
		.mask = 0xf
	}, {
		.num = 3,
		.pin = 12,
		.reg = 0x68,
		.bit = 8,
		.mask = 0xf
	}, {
		.num = 3,
		.pin = 13,
		.reg = 0x68,
		.bit = 12,
		.mask = 0xf
	}, {
		.num = 2,
		.pin = 2,
		.reg = 0x608,
		.bit = 0,
		.mask = 0x7
	}, {
		.num = 2,
		.pin = 3,
		.reg = 0x608,
		.bit = 4,
		.mask = 0x7
	}, {
		.num = 2,
		.pin = 16,
		.reg = 0x610,
		.bit = 8,
		.mask = 0x7
	}, {
		.num = 3,
		.pin = 10,
		.reg = 0x610,
		.bit = 0,
		.mask = 0x7
	}, {
		.num = 3,
		.pin = 11,
		.reg = 0x610,
		.bit = 4,
		.mask = 0x7
	},
};

static struct rockchip_mux_recalced_data rk3328_mux_recalced_data[] = {
	{
		.num = 2,
		.pin = 12,
		.reg = 0x24,
		.bit = 8,
		.mask = 0x3
	}, {
		.num = 2,
		.pin = 15,
		.reg = 0x28,
		.bit = 0,
		.mask = 0x7
	}, {
		.num = 2,
		.pin = 23,
		.reg = 0x30,
		.bit = 14,
		.mask = 0x3
	},
};

static struct rockchip_mux_route_data rv1126_mux_route_data[] = {
	MR_TOPGRF(RK_GPIO3, RK_PD2, RK_FUNC_1, 0x10260, RK_GENMASK_VAL(0, 0, 0)), /* I2S0_MCLK_M0 */
	MR_TOPGRF(RK_GPIO3, RK_PB0, RK_FUNC_3, 0x10260, RK_GENMASK_VAL(0, 0, 1)), /* I2S0_MCLK_M1 */

	MR_TOPGRF(RK_GPIO0, RK_PD4, RK_FUNC_4, 0x10260, RK_GENMASK_VAL(3, 2, 0)), /* I2S1_MCLK_M0 */
	MR_TOPGRF(RK_GPIO1, RK_PD5, RK_FUNC_2, 0x10260, RK_GENMASK_VAL(3, 2, 1)), /* I2S1_MCLK_M1 */
	MR_TOPGRF(RK_GPIO2, RK_PC7, RK_FUNC_6, 0x10260, RK_GENMASK_VAL(3, 2, 2)), /* I2S1_MCLK_M2 */

	MR_TOPGRF(RK_GPIO1, RK_PD0, RK_FUNC_1, 0x10260, RK_GENMASK_VAL(4, 4, 0)), /* I2S2_MCLK_M0 */
	MR_TOPGRF(RK_GPIO2, RK_PB3, RK_FUNC_2, 0x10260, RK_GENMASK_VAL(4, 4, 1)), /* I2S2_MCLK_M1 */

	MR_TOPGRF(RK_GPIO3, RK_PD4, RK_FUNC_2, 0x10260, RK_GENMASK_VAL(12, 12, 0)), /* PDM_CLK0_M0 */
	MR_TOPGRF(RK_GPIO3, RK_PC0, RK_FUNC_3, 0x10260, RK_GENMASK_VAL(12, 12, 1)), /* PDM_CLK0_M1 */

	MR_TOPGRF(RK_GPIO3, RK_PC6, RK_FUNC_1, 0x10264, RK_GENMASK_VAL(0, 0, 0)), /* CIF_CLKOUT_M0 */
	MR_TOPGRF(RK_GPIO2, RK_PD1, RK_FUNC_3, 0x10264, RK_GENMASK_VAL(0, 0, 1)), /* CIF_CLKOUT_M1 */

	MR_TOPGRF(RK_GPIO3, RK_PA4, RK_FUNC_5, 0x10264, RK_GENMASK_VAL(5, 4, 0)), /* I2C3_SCL_M0 */
	MR_TOPGRF(RK_GPIO2, RK_PD4, RK_FUNC_7, 0x10264, RK_GENMASK_VAL(5, 4, 1)), /* I2C3_SCL_M1 */
	MR_TOPGRF(RK_GPIO1, RK_PD6, RK_FUNC_3, 0x10264, RK_GENMASK_VAL(5, 4, 2)), /* I2C3_SCL_M2 */

	MR_TOPGRF(RK_GPIO3, RK_PA0, RK_FUNC_7, 0x10264, RK_GENMASK_VAL(6, 6, 0)), /* I2C4_SCL_M0 */
	MR_TOPGRF(RK_GPIO4, RK_PA0, RK_FUNC_4, 0x10264, RK_GENMASK_VAL(6, 6, 1)), /* I2C4_SCL_M1 */

	MR_TOPGRF(RK_GPIO2, RK_PA5, RK_FUNC_7, 0x10264, RK_GENMASK_VAL(9, 8, 0)), /* I2C5_SCL_M0 */
	MR_TOPGRF(RK_GPIO3, RK_PB0, RK_FUNC_5, 0x10264, RK_GENMASK_VAL(9, 8, 1)), /* I2C5_SCL_M1 */
	MR_TOPGRF(RK_GPIO1, RK_PD0, RK_FUNC_4, 0x10264, RK_GENMASK_VAL(9, 8, 2)), /* I2C5_SCL_M2 */

	MR_TOPGRF(RK_GPIO3, RK_PC0, RK_FUNC_5, 0x10264, RK_GENMASK_VAL(11, 10, 0)), /* SPI1_CLK_M0 */
	MR_TOPGRF(RK_GPIO1, RK_PC6, RK_FUNC_3, 0x10264, RK_GENMASK_VAL(11, 10, 1)), /* SPI1_CLK_M1 */
	MR_TOPGRF(RK_GPIO2, RK_PD5, RK_FUNC_6, 0x10264, RK_GENMASK_VAL(11, 10, 2)), /* SPI1_CLK_M2 */

	MR_TOPGRF(RK_GPIO3, RK_PC0, RK_FUNC_2, 0x10264, RK_GENMASK_VAL(12, 12, 0)), /* RGMII_CLK_M0 */
	MR_TOPGRF(RK_GPIO2, RK_PB7, RK_FUNC_2, 0x10264, RK_GENMASK_VAL(12, 12, 1)), /* RGMII_CLK_M1 */

	MR_TOPGRF(RK_GPIO3, RK_PA1, RK_FUNC_3, 0x10264, RK_GENMASK_VAL(13, 13, 0)), /* CAN_TXD_M0 */
	MR_TOPGRF(RK_GPIO3, RK_PA7, RK_FUNC_5, 0x10264, RK_GENMASK_VAL(13, 13, 1)), /* CAN_TXD_M1 */

	MR_TOPGRF(RK_GPIO3, RK_PA4, RK_FUNC_6, 0x10268, RK_GENMASK_VAL(0, 0, 0)), /* PWM8_M0 */
	MR_TOPGRF(RK_GPIO2, RK_PD7, RK_FUNC_5, 0x10268, RK_GENMASK_VAL(0, 0, 1)), /* PWM8_M1 */

	MR_TOPGRF(RK_GPIO3, RK_PA5, RK_FUNC_6, 0x10268, RK_GENMASK_VAL(2, 2, 0)), /* PWM9_M0 */
	MR_TOPGRF(RK_GPIO2, RK_PD6, RK_FUNC_5, 0x10268, RK_GENMASK_VAL(2, 2, 1)), /* PWM9_M1 */

	MR_TOPGRF(RK_GPIO3, RK_PA6, RK_FUNC_6, 0x10268, RK_GENMASK_VAL(4, 4, 0)), /* PWM10_M0 */
	MR_TOPGRF(RK_GPIO2, RK_PD5, RK_FUNC_5, 0x10268, RK_GENMASK_VAL(4, 4, 1)), /* PWM10_M1 */

	MR_TOPGRF(RK_GPIO3, RK_PA7, RK_FUNC_6, 0x10268, RK_GENMASK_VAL(6, 6, 0)), /* PWM11_IR_M0 */
	MR_TOPGRF(RK_GPIO3, RK_PA1, RK_FUNC_5, 0x10268, RK_GENMASK_VAL(6, 6, 1)), /* PWM11_IR_M1 */

	MR_TOPGRF(RK_GPIO1, RK_PA5, RK_FUNC_3, 0x10268, RK_GENMASK_VAL(8, 8, 0)), /* UART2_TX_M0 */
	MR_TOPGRF(RK_GPIO3, RK_PA2, RK_FUNC_1, 0x10268, RK_GENMASK_VAL(8, 8, 1)), /* UART2_TX_M1 */

	MR_TOPGRF(RK_GPIO3, RK_PC6, RK_FUNC_3, 0x10268, RK_GENMASK_VAL(11, 10, 0)), /* UART3_TX_M0 */
	MR_TOPGRF(RK_GPIO1, RK_PA7, RK_FUNC_2, 0x10268, RK_GENMASK_VAL(11, 10, 1)), /* UART3_TX_M1 */
	MR_TOPGRF(RK_GPIO3, RK_PA0, RK_FUNC_4, 0x10268, RK_GENMASK_VAL(11, 10, 2)), /* UART3_TX_M2 */

	MR_TOPGRF(RK_GPIO3, RK_PA4, RK_FUNC_4, 0x10268, RK_GENMASK_VAL(13, 12, 0)), /* UART4_TX_M0 */
	MR_TOPGRF(RK_GPIO2, RK_PA6, RK_FUNC_4, 0x10268, RK_GENMASK_VAL(13, 12, 1)), /* UART4_TX_M1 */
	MR_TOPGRF(RK_GPIO1, RK_PD5, RK_FUNC_3, 0x10268, RK_GENMASK_VAL(13, 12, 2)), /* UART4_TX_M2 */

	MR_TOPGRF(RK_GPIO3, RK_PA6, RK_FUNC_4, 0x10268, RK_GENMASK_VAL(15, 14, 0)), /* UART5_TX_M0 */
	MR_TOPGRF(RK_GPIO2, RK_PB0, RK_FUNC_4, 0x10268, RK_GENMASK_VAL(15, 14, 1)), /* UART5_TX_M1 */
	MR_TOPGRF(RK_GPIO2, RK_PA0, RK_FUNC_3, 0x10268, RK_GENMASK_VAL(15, 14, 2)), /* UART5_TX_M2 */

	MR_PMUGRF(RK_GPIO0, RK_PB6, RK_FUNC_3, 0x0114, RK_GENMASK_VAL(0, 0, 0)), /* PWM0_M0 */
	MR_PMUGRF(RK_GPIO2, RK_PB3, RK_FUNC_5, 0x0114, RK_GENMASK_VAL(0, 0, 1)), /* PWM0_M1 */

	MR_PMUGRF(RK_GPIO0, RK_PB7, RK_FUNC_3, 0x0114, RK_GENMASK_VAL(2, 2, 0)), /* PWM1_M0 */
	MR_PMUGRF(RK_GPIO2, RK_PB2, RK_FUNC_5, 0x0114, RK_GENMASK_VAL(2, 2, 1)), /* PWM1_M1 */

	MR_PMUGRF(RK_GPIO0, RK_PC0, RK_FUNC_3, 0x0114, RK_GENMASK_VAL(4, 4, 0)), /* PWM2_M0 */
	MR_PMUGRF(RK_GPIO2, RK_PB1, RK_FUNC_5, 0x0114, RK_GENMASK_VAL(4, 4, 1)), /* PWM2_M1 */

	MR_PMUGRF(RK_GPIO0, RK_PC1, RK_FUNC_3, 0x0114, RK_GENMASK_VAL(6, 6, 0)), /* PWM3_IR_M0 */
	MR_PMUGRF(RK_GPIO2, RK_PB0, RK_FUNC_5, 0x0114, RK_GENMASK_VAL(6, 6, 1)), /* PWM3_IR_M1 */

	MR_PMUGRF(RK_GPIO0, RK_PC2, RK_FUNC_3, 0x0114, RK_GENMASK_VAL(8, 8, 0)), /* PWM4_M0 */
	MR_PMUGRF(RK_GPIO2, RK_PA7, RK_FUNC_5, 0x0114, RK_GENMASK_VAL(8, 8, 1)), /* PWM4_M1 */

	MR_PMUGRF(RK_GPIO0, RK_PC3, RK_FUNC_3, 0x0114, RK_GENMASK_VAL(10, 10, 0)), /* PWM5_M0 */
	MR_PMUGRF(RK_GPIO2, RK_PA6, RK_FUNC_5, 0x0114, RK_GENMASK_VAL(10, 10, 1)), /* PWM5_M1 */

	MR_PMUGRF(RK_GPIO0, RK_PB2, RK_FUNC_3, 0x0114, RK_GENMASK_VAL(12, 12, 0)), /* PWM6_M0 */
	MR_PMUGRF(RK_GPIO2, RK_PD4, RK_FUNC_5, 0x0114, RK_GENMASK_VAL(12, 12, 1)), /* PWM6_M1 */

	MR_PMUGRF(RK_GPIO0, RK_PB1, RK_FUNC_3, 0x0114, RK_GENMASK_VAL(14, 14, 0)), /* PWM7_IR_M0 */
	MR_PMUGRF(RK_GPIO3, RK_PA0, RK_FUNC_5, 0x0114, RK_GENMASK_VAL(14, 14, 1)), /* PWM7_IR_M1 */

	MR_PMUGRF(RK_GPIO0, RK_PB0, RK_FUNC_1, 0x0118, RK_GENMASK_VAL(1, 0, 0)), /* SPI0_CLK_M0 */
	MR_PMUGRF(RK_GPIO2, RK_PA1, RK_FUNC_1, 0x0118, RK_GENMASK_VAL(1, 0, 1)), /* SPI0_CLK_M1 */
	MR_PMUGRF(RK_GPIO2, RK_PB2, RK_FUNC_6, 0x0118, RK_GENMASK_VAL(1, 0, 2)), /* SPI0_CLK_M2 */

	MR_PMUGRF(RK_GPIO0, RK_PB6, RK_FUNC_2, 0x0118, RK_GENMASK_VAL(2, 2, 0)), /* UART1_TX_M0 */
	MR_PMUGRF(RK_GPIO1, RK_PD0, RK_FUNC_5, 0x0118, RK_GENMASK_VAL(2, 2, 1)), /* UART1_TX_M1 */
	MR_PMUGRF(RK_GPIO0, RK_PC3, RK_FUNC_1, 0x0118, RK_GENMASK_VAL(4, 4, 1)), /* I2C2 */
};

static void rockchip_get_recalced_mux(struct rockchip_pin_bank *bank, int pin,
				      int *reg, u8 *bit, int *mask)
{
	struct rockchip_pinctrl_priv *priv = bank->priv;
	struct rockchip_pin_ctrl *ctrl = priv->ctrl;
	struct rockchip_mux_recalced_data *data;
	int i;

	for (i = 0; i < ctrl->niomux_recalced; i++) {
		data = &ctrl->iomux_recalced[i];
		if (data->num == bank->bank_num &&
		    data->pin == pin)
			break;
	}

	if (i >= ctrl->niomux_recalced)
		return;

	*reg = data->reg;
	*mask = data->mask;
	*bit = data->bit;
}

static struct rockchip_mux_route_data px30_mux_route_data[] = {
	{
		/* cif-d2m0 */
		.bank_num = 2,
		.pin = 0,
		.func = 1,
		.route_offset = 0x184,
		.route_val = BIT(16 + 7),
	}, {
		/* cif-d2m1 */
		.bank_num = 3,
		.pin = 3,
		.func = 3,
		.route_offset = 0x184,
		.route_val = BIT(16 + 7) | BIT(7),
	}, {
		/* pdm-m0 */
		.bank_num = 3,
		.pin = 22,
		.func = 2,
		.route_offset = 0x184,
		.route_val = BIT(16 + 8),
	}, {
		/* pdm-m1 */
		.bank_num = 2,
		.pin = 22,
		.func = 1,
		.route_offset = 0x184,
		.route_val = BIT(16 + 8) | BIT(8),
	}, {
		/* uart2-rxm0 */
		.bank_num = 1,
		.pin = 27,
		.func = 2,
		.route_offset = 0x184,
		.route_val = BIT(16 + 10),
	}, {
		/* uart2-rxm1 */
		.bank_num = 2,
		.pin = 14,
		.func = 2,
		.route_offset = 0x184,
		.route_val = BIT(16 + 10) | BIT(10),
	}, {
		/* uart3-rxm0 */
		.bank_num = 0,
		.pin = 17,
		.func = 2,
		.route_offset = 0x184,
		.route_val = BIT(16 + 9),
	}, {
		/* uart3-rxm1 */
		.bank_num = 1,
		.pin = 15,
		.func = 2,
		.route_offset = 0x184,
		.route_val = BIT(16 + 9) | BIT(9),
	},
};

static struct rockchip_mux_route_data rk1808_mux_route_data[] = {
	{
		/* i2c2m0_sda */
		.bank_num = 3,
		.pin = 12,
		.func = 2,
		.route_offset = 0x190,
		.route_val = BIT(16 + 3),
	}, {
		/* i2c2m1_sda */
		.bank_num = 1,
		.pin = 13,
		.func = 2,
		.route_offset = 0x190,
		.route_val = BIT(16 + 3) | BIT(3),
	}, {
		/* uart2_rxm0 */
		.bank_num = 4,
		.pin = 3,
		.func = 2,
		.route_offset = 0x190,
		.route_val = BIT(16 + 14) | BIT(16 + 15),
	}, {
		/* uart2_rxm1 */
		.bank_num = 2,
		.pin = 25,
		.func = 2,
		.route_offset = 0x190,
		.route_val = BIT(16 + 14) | BIT(14) | BIT(16 + 15),
	}, {
		/* uart2_rxm2 */
		.bank_num = 3,
		.pin = 4,
		.func = 2,
		.route_offset = 0x190,
		.route_val = BIT(16 + 14) | BIT(16 + 15) | BIT(15),
	},
};

static struct rockchip_mux_route_data rk3128_mux_route_data[] = {
	{
		/* spi-0 */
		.bank_num = 1,
		.pin = 10,
		.func = 1,
		.route_offset = 0x144,
		.route_val = BIT(16 + 3) | BIT(16 + 4),
	}, {
		/* spi-1 */
		.bank_num = 1,
		.pin = 27,
		.func = 3,
		.route_offset = 0x144,
		.route_val = BIT(16 + 3) | BIT(16 + 4) | BIT(3),
	}, {
		/* spi-2 */
		.bank_num = 0,
		.pin = 13,
		.func = 2,
		.route_offset = 0x144,
		.route_val = BIT(16 + 3) | BIT(16 + 4) | BIT(4),
	}, {
		/* i2s-0 */
		.bank_num = 1,
		.pin = 5,
		.func = 1,
		.route_offset = 0x144,
		.route_val = BIT(16 + 5),
	}, {
		/* i2s-1 */
		.bank_num = 0,
		.pin = 14,
		.func = 1,
		.route_offset = 0x144,
		.route_val = BIT(16 + 5) | BIT(5),
	}, {
		/* emmc-0 */
		.bank_num = 1,
		.pin = 22,
		.func = 2,
		.route_offset = 0x144,
		.route_val = BIT(16 + 6),
	}, {
		/* emmc-1 */
		.bank_num = 2,
		.pin = 4,
		.func = 2,
		.route_offset = 0x144,
		.route_val = BIT(16 + 6) | BIT(6),
	},
};

static struct rockchip_mux_route_data rk3228_mux_route_data[] = {
	{
		/* pwm0-0 */
		.bank_num = 0,
		.pin = 26,
		.func = 1,
		.route_offset = 0x50,
		.route_val = BIT(16),
	}, {
		/* pwm0-1 */
		.bank_num = 3,
		.pin = 21,
		.func = 1,
		.route_offset = 0x50,
		.route_val = BIT(16) | BIT(0),
	}, {
		/* pwm1-0 */
		.bank_num = 0,
		.pin = 27,
		.func = 1,
		.route_offset = 0x50,
		.route_val = BIT(16 + 1),
	}, {
		/* pwm1-1 */
		.bank_num = 0,
		.pin = 30,
		.func = 2,
		.route_offset = 0x50,
		.route_val = BIT(16 + 1) | BIT(1),
	}, {
		/* pwm2-0 */
		.bank_num = 0,
		.pin = 28,
		.func = 1,
		.route_offset = 0x50,
		.route_val = BIT(16 + 2),
	}, {
		/* pwm2-1 */
		.bank_num = 1,
		.pin = 12,
		.func = 2,
		.route_offset = 0x50,
		.route_val = BIT(16 + 2) | BIT(2),
	}, {
		/* pwm3-0 */
		.bank_num = 3,
		.pin = 26,
		.func = 1,
		.route_offset = 0x50,
		.route_val = BIT(16 + 3),
	}, {
		/* pwm3-1 */
		.bank_num = 1,
		.pin = 11,
		.func = 2,
		.route_offset = 0x50,
		.route_val = BIT(16 + 3) | BIT(3),
	}, {
		/* sdio-0_d0 */
		.bank_num = 1,
		.pin = 1,
		.func = 1,
		.route_offset = 0x50,
		.route_val = BIT(16 + 4),
	}, {
		/* sdio-1_d0 */
		.bank_num = 3,
		.pin = 2,
		.func = 1,
		.route_offset = 0x50,
		.route_val = BIT(16 + 4) | BIT(4),
	}, {
		/* spi-0_rx */
		.bank_num = 0,
		.pin = 13,
		.func = 2,
		.route_offset = 0x50,
		.route_val = BIT(16 + 5),
	}, {
		/* spi-1_rx */
		.bank_num = 2,
		.pin = 0,
		.func = 2,
		.route_offset = 0x50,
		.route_val = BIT(16 + 5) | BIT(5),
	}, {
		/* emmc-0_cmd */
		.bank_num = 1,
		.pin = 22,
		.func = 2,
		.route_offset = 0x50,
		.route_val = BIT(16 + 7),
	}, {
		/* emmc-1_cmd */
		.bank_num = 2,
		.pin = 4,
		.func = 2,
		.route_offset = 0x50,
		.route_val = BIT(16 + 7) | BIT(7),
	}, {
		/* uart2-0_rx */
		.bank_num = 1,
		.pin = 19,
		.func = 2,
		.route_offset = 0x50,
		.route_val = BIT(16 + 8),
	}, {
		/* uart2-1_rx */
		.bank_num = 1,
		.pin = 10,
		.func = 2,
		.route_offset = 0x50,
		.route_val = BIT(16 + 8) | BIT(8),
	}, {
		/* uart1-0_rx */
		.bank_num = 1,
		.pin = 10,
		.func = 1,
		.route_offset = 0x50,
		.route_val = BIT(16 + 11),
	}, {
		/* uart1-1_rx */
		.bank_num = 3,
		.pin = 13,
		.func = 1,
		.route_offset = 0x50,
		.route_val = BIT(16 + 11) | BIT(11),
	},
};

static struct rockchip_mux_route_data rk3288_mux_route_data[] = {
	{
		/* edphdmi_cecinoutt1 */
		.bank_num = 7,
		.pin = 16,
		.func = 2,
		.route_offset = 0x264,
		.route_val = BIT(16 + 12) | BIT(12),
	}, {
		/* edphdmi_cecinout */
		.bank_num = 7,
		.pin = 23,
		.func = 4,
		.route_offset = 0x264,
		.route_val = BIT(16 + 12),
	},
};

static struct rockchip_mux_route_data rk3308_mux_route_data[] = {
	{
		/* rtc_clk */
		.bank_num = 0,
		.pin = 19,
		.func = 1,
		.route_offset = 0x314,
		.route_val = BIT(16 + 0) | BIT(0),
	}, {
		/* uart2_rxm0 */
		.bank_num = 1,
		.pin = 22,
		.func = 2,
		.route_offset = 0x314,
		.route_val = BIT(16 + 2) | BIT(16 + 3),
	}, {
		/* uart2_rxm1 */
		.bank_num = 4,
		.pin = 26,
		.func = 2,
		.route_offset = 0x314,
		.route_val = BIT(16 + 2) | BIT(16 + 3) | BIT(2),
	}, {
		/* i2c3_sdam0 */
		.bank_num = 0,
		.pin = 23,
		.func = 2,
		.route_offset = 0x314,
		.route_val = BIT(16 + 4),
	}, {
		/* i2c3_sdam1 */
		.bank_num = 3,
		.pin = 12,
		.func = 2,
		.route_offset = 0x314,
		.route_val = BIT(16 + 4) | BIT(4),
	}, {
		/* i2s-8ch-1-sclktxm0 */
		.bank_num = 1,
		.pin = 3,
		.func = 2,
		.route_offset = 0x308,
		.route_val = BIT(16 + 3),
	}, {
		/* i2s-8ch-1-sclkrxm0 */
		.bank_num = 1,
		.pin = 4,
		.func = 2,
		.route_offset = 0x308,
		.route_val = BIT(16 + 3),
	}, {
		/* i2s-8ch-1-sclktxm1 */
		.bank_num = 1,
		.pin = 13,
		.func = 2,
		.route_offset = 0x308,
		.route_val = BIT(16 + 3) | BIT(3),
	}, {
		/* i2s-8ch-1-sclkrxm1 */
		.bank_num = 1,
		.pin = 14,
		.func = 2,
		.route_offset = 0x308,
		.route_val = BIT(16 + 3) | BIT(3),
	}, {
		/* pdm-clkm0 */
		.bank_num = 1,
		.pin = 4,
		.func = 3,
		.route_offset = 0x308,
		.route_val = BIT(16 + 12) | BIT(16 + 13),
	}, {
		/* pdm-clkm1 */
		.bank_num = 1,
		.pin = 14,
		.func = 4,
		.route_offset = 0x308,
		.route_val = BIT(16 + 12) | BIT(16 + 13) | BIT(12),
	}, {
		/* pdm-clkm2 */
		.bank_num = 2,
		.pin = 6,
		.func = 2,
		.route_offset = 0x308,
		.route_val = BIT(16 + 12) | BIT(16 + 13) | BIT(13),
	}, {
		/* pdm-clkm-m2 */
		.bank_num = 2,
		.pin = 4,
		.func = 3,
		.route_offset = 0x600,
		.route_val = BIT(16 + 2) | BIT(2),
	},
};

static struct rockchip_mux_route_data rk3308b_mux_route_data[] = {
	{
		/* rtc_clk */
		.bank_num = 0,
		.pin = 19,
		.func = 1,
		.route_offset = 0x314,
		.route_val = BIT(16 + 0) | BIT(0),
	}, {
		/* uart2_rxm0 */
		.bank_num = 1,
		.pin = 22,
		.func = 2,
		.route_offset = 0x314,
		.route_val = BIT(16 + 2) | BIT(16 + 3),
	}, {
		/* uart2_rxm1 */
		.bank_num = 4,
		.pin = 26,
		.func = 2,
		.route_offset = 0x314,
		.route_val = BIT(16 + 2) | BIT(16 + 3) | BIT(2),
	}, {
		/* i2c3_sdam0 */
		.bank_num = 0,
		.pin = 15,
		.func = 2,
		.route_offset = 0x608,
		.route_val = BIT(16 + 8) | BIT(16 + 9),
	}, {
		/* i2c3_sdam1 */
		.bank_num = 3,
		.pin = 12,
		.func = 2,
		.route_offset = 0x608,
		.route_val = BIT(16 + 8) | BIT(16 + 9) | BIT(8),
	}, {
		/* i2c3_sdam2 */
		.bank_num = 2,
		.pin = 0,
		.func = 3,
		.route_offset = 0x608,
		.route_val = BIT(16 + 8) | BIT(16 + 9) | BIT(9),
	}, {
		/* i2s-8ch-1-sclktxm0 */
		.bank_num = 1,
		.pin = 3,
		.func = 2,
		.route_offset = 0x308,
		.route_val = BIT(16 + 3),
	}, {
		/* i2s-8ch-1-sclkrxm0 */
		.bank_num = 1,
		.pin = 4,
		.func = 2,
		.route_offset = 0x308,
		.route_val = BIT(16 + 3),
	}, {
		/* i2s-8ch-1-sclktxm1 */
		.bank_num = 1,
		.pin = 13,
		.func = 2,
		.route_offset = 0x308,
		.route_val = BIT(16 + 3) | BIT(3),
	}, {
		/* i2s-8ch-1-sclkrxm1 */
		.bank_num = 1,
		.pin = 14,
		.func = 2,
		.route_offset = 0x308,
		.route_val = BIT(16 + 3) | BIT(3),
	}, {
		/* pdm-clkm0 */
		.bank_num = 1,
		.pin = 4,
		.func = 3,
		.route_offset = 0x308,
		.route_val =  BIT(16 + 12) | BIT(16 + 13),
	}, {
		/* pdm-clkm1 */
		.bank_num = 1,
		.pin = 14,
		.func = 4,
		.route_offset = 0x308,
		.route_val = BIT(16 + 12) | BIT(16 + 13) | BIT(12),
	}, {
		/* pdm-clkm2 */
		.bank_num = 2,
		.pin = 6,
		.func = 2,
		.route_offset = 0x308,
		.route_val = BIT(16 + 12) | BIT(16 + 13) | BIT(13),
	}, {
		/* pdm-clkm-m2 */
		.bank_num = 2,
		.pin = 4,
		.func = 3,
		.route_offset = 0x600,
		.route_val = BIT(16 + 2) | BIT(2),
	}, {
		/* spi1_miso */
		.bank_num = 3,
		.pin = 10,
		.func = 3,
		.route_offset = 0x314,
		.route_val = BIT(16 + 9),
	}, {
		/* spi1_miso_m1 */
		.bank_num = 2,
		.pin = 4,
		.func = 2,
		.route_offset = 0x314,
		.route_val = BIT(16 + 9) | BIT(9),
	}, {
		/* owire_m0 */
		.bank_num = 0,
		.pin = 11,
		.func = 3,
		.route_offset = 0x314,
		.route_val = BIT(16 + 10) | BIT(16 + 11),
	}, {
		/* owire_m1 */
		.bank_num = 1,
		.pin = 22,
		.func = 7,
		.route_offset = 0x314,
		.route_val = BIT(16 + 10) | BIT(16 + 11) | BIT(10),
	}, {
		/* owire_m2 */
		.bank_num = 2,
		.pin = 2,
		.func = 5,
		.route_offset = 0x314,
		.route_val = BIT(16 + 10) | BIT(16 + 11) | BIT(11),
	}, {
		/* can_rxd_m0 */
		.bank_num = 0,
		.pin = 11,
		.func = 2,
		.route_offset = 0x314,
		.route_val = BIT(16 + 12) | BIT(16 + 13),
	}, {
		/* can_rxd_m1 */
		.bank_num = 1,
		.pin = 22,
		.func = 5,
		.route_offset = 0x314,
		.route_val = BIT(16 + 12) | BIT(16 + 13) | BIT(12),
	}, {
		/* can_rxd_m2 */
		.bank_num = 2,
		.pin = 2,
		.func = 4,
		.route_offset = 0x314,
		.route_val = BIT(16 + 12) | BIT(16 + 13) | BIT(13),
	}, {
		/* mac_rxd0_m0 */
		.bank_num = 1,
		.pin = 20,
		.func = 3,
		.route_offset = 0x314,
		.route_val = BIT(16 + 14),
	}, {
		/* mac_rxd0_m1 */
		.bank_num = 4,
		.pin = 2,
		.func = 2,
		.route_offset = 0x314,
		.route_val = BIT(16 + 14) | BIT(14),
	}, {
		/* uart3_rx */
		.bank_num = 3,
		.pin = 12,
		.func = 4,
		.route_offset = 0x314,
		.route_val = BIT(16 + 15),
	}, {
		/* uart3_rx_m1 */
		.bank_num = 0,
		.pin = 17,
		.func = 3,
		.route_offset = 0x314,
		.route_val = BIT(16 + 15) | BIT(15),
	},
};

static struct rockchip_mux_route_data rk3328_mux_route_data[] = {
	{
		/* uart2dbg_rxm0 */
		.bank_num = 1,
		.pin = 1,
		.func = 2,
		.route_offset = 0x50,
		.route_val = BIT(16) | BIT(16 + 1),
	}, {
		/* uart2dbg_rxm1 */
		.bank_num = 2,
		.pin = 1,
		.func = 1,
		.route_offset = 0x50,
		.route_val = BIT(16) | BIT(16 + 1) | BIT(0),
	}, {
		/* gmac-m1_rxd0 */
		.bank_num = 1,
		.pin = 11,
		.func = 2,
		.route_offset = 0x50,
		.route_val = BIT(16 + 2) | BIT(2),
	}, {
		/* gmac-m1-optimized_rxd3 */
		.bank_num = 1,
		.pin = 14,
		.func = 2,
		.route_offset = 0x50,
		.route_val = BIT(16 + 10) | BIT(10),
	}, {
		/* pdm_sdi0m0 */
		.bank_num = 2,
		.pin = 19,
		.func = 2,
		.route_offset = 0x50,
		.route_val = BIT(16 + 3),
	}, {
		/* pdm_sdi0m1 */
		.bank_num = 1,
		.pin = 23,
		.func = 3,
		.route_offset = 0x50,
		.route_val =  BIT(16 + 3) | BIT(3),
	}, {
		/* spi_rxdm2 */
		.bank_num = 3,
		.pin = 2,
		.func = 4,
		.route_offset = 0x50,
		.route_val =  BIT(16 + 4) | BIT(16 + 5) | BIT(5),
	}, {
		/* i2s2_sdim0 */
		.bank_num = 1,
		.pin = 24,
		.func = 1,
		.route_offset = 0x50,
		.route_val = BIT(16 + 6),
	}, {
		/* i2s2_sdim1 */
		.bank_num = 3,
		.pin = 2,
		.func = 6,
		.route_offset = 0x50,
		.route_val =  BIT(16 + 6) | BIT(6),
	}, {
		/* card_iom1 */
		.bank_num = 2,
		.pin = 22,
		.func = 3,
		.route_offset = 0x50,
		.route_val =  BIT(16 + 7) | BIT(7),
	}, {
		/* tsp_d5m1 */
		.bank_num = 2,
		.pin = 16,
		.func = 3,
		.route_offset = 0x50,
		.route_val =  BIT(16 + 8) | BIT(8),
	}, {
		/* cif_data5m1 */
		.bank_num = 2,
		.pin = 16,
		.func = 4,
		.route_offset = 0x50,
		.route_val =  BIT(16 + 9) | BIT(9),
	},
};

static struct rockchip_mux_route_data rk3399_mux_route_data[] = {
	{
		/* uart2dbga_rx */
		.bank_num = 4,
		.pin = 8,
		.func = 2,
		.route_offset = 0xe21c,
		.route_val = BIT(16 + 10) | BIT(16 + 11),
	}, {
		/* uart2dbgb_rx */
		.bank_num = 4,
		.pin = 16,
		.func = 2,
		.route_offset = 0xe21c,
		.route_val = BIT(16 + 10) | BIT(16 + 11) | BIT(10),
	}, {
		/* uart2dbgc_rx */
		.bank_num = 4,
		.pin = 19,
		.func = 1,
		.route_offset = 0xe21c,
		.route_val = BIT(16 + 10) | BIT(16 + 11) | BIT(11),
	}, {
		/* pcie_clkreqn */
		.bank_num = 2,
		.pin = 26,
		.func = 2,
		.route_offset = 0xe21c,
		.route_val = BIT(16 + 14),
	}, {
		/* pcie_clkreqnb */
		.bank_num = 4,
		.pin = 24,
		.func = 1,
		.route_offset = 0xe21c,
		.route_val = BIT(16 + 14) | BIT(14),
	},
};

static enum rockchip_pin_route_type
rockchip_get_mux_route(struct rockchip_pin_bank *bank, int pin,
		       int mux, u32 *reg, u32 *value)
{
	struct rockchip_pinctrl_priv *priv = bank->priv;
	struct rockchip_pin_ctrl *ctrl = priv->ctrl;
	struct rockchip_mux_route_data *data;
	int i;

	for (i = 0; i < ctrl->niomux_routes; i++) {
		data = &ctrl->iomux_routes[i];
		if ((data->bank_num == bank->bank_num) &&
		    (data->pin == pin) && (data->func == mux))
			break;
	}

	if (i >= ctrl->niomux_routes)
		return ROUTE_TYPE_INVALID;

	*reg = data->route_offset;
	*value = data->route_val;

	return data->route_type;
}

static int rockchip_get_mux(struct rockchip_pin_bank *bank, int pin)
{
	struct rockchip_pinctrl_priv *priv = bank->priv;
	int iomux_num = (pin / 8);
	struct regmap *regmap;
	unsigned int val;
	int reg, ret, mask, mux_type;
	u8 bit;

	if (iomux_num > 3)
		return -EINVAL;

	if (bank->iomux[iomux_num].type & IOMUX_UNROUTED) {
		debug("pin %d is unrouted\n", pin);
		return -EINVAL;
	}

	if (bank->iomux[iomux_num].type & IOMUX_GPIO_ONLY)
		return RK_FUNC_GPIO;

	if (bank->iomux[iomux_num].type & IOMUX_SOURCE_PMU)
		regmap = priv->regmap_pmu;
	else if (bank->iomux[iomux_num].type & IOMUX_L_SOURCE_PMU)
		regmap = (pin % 8 < 4) ? priv->regmap_pmu : priv->regmap_base;
	else
		regmap = priv->regmap_base;

	/* get basic quadrupel of mux registers and the correct reg inside */
	mux_type = bank->iomux[iomux_num].type;
	reg = bank->iomux[iomux_num].offset;
	if (mux_type & IOMUX_WIDTH_4BIT) {
		if ((pin % 8) >= 4)
			reg += 0x4;
		bit = (pin % 4) * 4;
		mask = 0xf;
	} else if (mux_type & IOMUX_WIDTH_3BIT) {
		if ((pin % 8) >= 5)
			reg += 0x4;
		bit = (pin % 8 % 5) * 3;
		mask = 0x7;
	} else {
		bit = (pin % 8) * 2;
		mask = 0x3;
	}

	if (bank->recalced_mask & BIT(pin))
		rockchip_get_recalced_mux(bank, pin, &reg, &bit, &mask);

	ret = regmap_read(regmap, reg, &val);
	if (ret)
		return ret;

	return ((val >> bit) & mask);
}

static int rockchip_pinctrl_get_gpio_mux(struct udevice *dev, int banknum,
					 int index)
{	struct rockchip_pinctrl_priv *priv = dev_get_priv(dev);
	struct rockchip_pin_ctrl *ctrl = priv->ctrl;

	return rockchip_get_mux(&ctrl->pin_banks[banknum], index);
}

static int rockchip_verify_mux(struct rockchip_pin_bank *bank,
			       int pin, int mux)
{
	int iomux_num = (pin / 8);

	if (iomux_num > 3)
		return -EINVAL;

	if (bank->iomux[iomux_num].type & IOMUX_UNROUTED) {
		debug("pin %d is unrouted\n", pin);
		return -EINVAL;
	}

	if (bank->iomux[iomux_num].type & IOMUX_GPIO_ONLY) {
		if (mux != IOMUX_GPIO_ONLY) {
			debug("pin %d only supports a gpio mux\n", pin);
			return -ENOTSUPP;
		}
	}

	return 0;
}

/*
 * Set a new mux function for a pin.
 *
 * The register is divided into the upper and lower 16 bit. When changing
 * a value, the previous register value is not read and changed. Instead
 * it seems the changed bits are marked in the upper 16 bit, while the
 * changed value gets set in the same offset in the lower 16 bit.
 * All pin settings seem to be 2 bit wide in both the upper and lower
 * parts.
 * @bank: pin bank to change
 * @pin: pin to change
 * @mux: new mux function to set
 */
static int rockchip_set_mux(struct rockchip_pin_bank *bank, int pin, int mux)
{
	struct rockchip_pinctrl_priv *priv = bank->priv;
	int iomux_num = (pin / 8);
	struct regmap *regmap;
	int reg, ret, mask, mux_type;
	u8 bit;
	u32 data;

	ret = rockchip_verify_mux(bank, pin, mux);
	if (ret < 0)
		return ret;

	if (bank->iomux[iomux_num].type & IOMUX_GPIO_ONLY)
		return 0;

	debug("setting mux of GPIO%d-%d to %d\n", bank->bank_num, pin, mux);

	if (bank->iomux[iomux_num].type & IOMUX_SOURCE_PMU)
		regmap = priv->regmap_pmu;
	else if (bank->iomux[iomux_num].type & IOMUX_L_SOURCE_PMU)
		regmap = (pin % 8 < 4) ? priv->regmap_pmu : priv->regmap_base;
	else
		regmap = priv->regmap_base;

	/* get basic quadrupel of mux registers and the correct reg inside */
	mux_type = bank->iomux[iomux_num].type;
	reg = bank->iomux[iomux_num].offset;
	if (mux_type & IOMUX_WIDTH_4BIT) {
		if ((pin % 8) >= 4)
			reg += 0x4;
		bit = (pin % 4) * 4;
		mask = 0xf;
	} else if (mux_type & IOMUX_WIDTH_3BIT) {
		if ((pin % 8) >= 5)
			reg += 0x4;
		bit = (pin % 8 % 5) * 3;
		mask = 0x7;
	} else {
		bit = (pin % 8) * 2;
		mask = 0x3;
	}

	if (bank->recalced_mask & BIT(pin))
		rockchip_get_recalced_mux(bank, pin, &reg, &bit, &mask);

	if (bank->route_mask & BIT(pin)) {
		u32 route_reg = 0, route_val = 0;

		ret = rockchip_get_mux_route(bank, pin, mux,
					     &route_reg, &route_val);
		switch (ret) {
		case ROUTE_TYPE_DEFAULT:
			regmap_write(regmap, route_reg, route_val);
			break;
		case ROUTE_TYPE_TOPGRF:
			regmap_write(priv->regmap_base, route_reg, route_val);
			break;
		case ROUTE_TYPE_PMUGRF:
			regmap_write(priv->regmap_pmu, route_reg, route_val);
			break;
		case ROUTE_TYPE_INVALID: /* Fall through */
		default:
			break;
		}
	}

	if (mux_type & IOMUX_WRITABLE_32BIT) {
		regmap_read(regmap, reg, &data);
		data &= ~(mask << bit);
	} else {
		data = (mask << (bit + 16));
	}

	data |= (mux & mask) << bit;
	ret = regmap_write(regmap, reg, data);

	return ret;
}

#define PX30_PULL_PMU_OFFSET		0x10
#define PX30_PULL_GRF_OFFSET		0x60
#define PX30_PULL_BITS_PER_PIN		2
#define PX30_PULL_PINS_PER_REG		8
#define PX30_PULL_BANK_STRIDE		16

static void px30_calc_pull_reg_and_bit(struct rockchip_pin_bank *bank,
				       int pin_num, struct regmap **regmap,
				       int *reg, u8 *bit)
{
	struct rockchip_pinctrl_priv *priv = bank->priv;

	/* The first 32 pins of the first bank are located in PMU */
	if (bank->bank_num == 0) {
		*regmap = priv->regmap_pmu;
		*reg = PX30_PULL_PMU_OFFSET;
	} else {
		*regmap = priv->regmap_base;
		*reg = PX30_PULL_GRF_OFFSET;

		/* correct the offset, as we're starting with the 2nd bank */
		*reg -= 0x10;
		*reg += bank->bank_num * PX30_PULL_BANK_STRIDE;
	}

	*reg += ((pin_num / PX30_PULL_PINS_PER_REG) * 4);
	*bit = (pin_num % PX30_PULL_PINS_PER_REG);
	*bit *= PX30_PULL_BITS_PER_PIN;
}

#define PX30_DRV_PMU_OFFSET		0x20
#define PX30_DRV_GRF_OFFSET		0xf0
#define PX30_DRV_BITS_PER_PIN		2
#define PX30_DRV_PINS_PER_REG		8
#define PX30_DRV_BANK_STRIDE		16

static void px30_calc_drv_reg_and_bit(struct rockchip_pin_bank *bank,
				      int pin_num, struct regmap **regmap,
				      int *reg, u8 *bit)
{
	struct rockchip_pinctrl_priv *priv = bank->priv;

	/* The first 32 pins of the first bank are located in PMU */
	if (bank->bank_num == 0) {
		*regmap = priv->regmap_pmu;
		*reg = PX30_DRV_PMU_OFFSET;
	} else {
		*regmap = priv->regmap_base;
		*reg = PX30_DRV_GRF_OFFSET;

		/* correct the offset, as we're starting with the 2nd bank */
		*reg -= 0x10;
		*reg += bank->bank_num * PX30_DRV_BANK_STRIDE;
	}

	*reg += ((pin_num / PX30_DRV_PINS_PER_REG) * 4);
	*bit = (pin_num % PX30_DRV_PINS_PER_REG);
	*bit *= PX30_DRV_BITS_PER_PIN;
}

#define PX30_SCHMITT_PMU_OFFSET			0x38
#define PX30_SCHMITT_GRF_OFFSET			0xc0
#define PX30_SCHMITT_PINS_PER_PMU_REG		16
#define PX30_SCHMITT_BANK_STRIDE		16
#define PX30_SCHMITT_PINS_PER_GRF_REG		8

static int px30_calc_schmitt_reg_and_bit(struct rockchip_pin_bank *bank,
					 int pin_num,
					 struct regmap **regmap,
					 int *reg, u8 *bit)
{
	struct rockchip_pinctrl_priv *priv = bank->priv;
	int pins_per_reg;

	if (bank->bank_num == 0) {
		*regmap = priv->regmap_pmu;
		*reg = PX30_SCHMITT_PMU_OFFSET;
		pins_per_reg = PX30_SCHMITT_PINS_PER_PMU_REG;
	} else {
		*regmap = priv->regmap_base;
		*reg = PX30_SCHMITT_GRF_OFFSET;
		pins_per_reg = PX30_SCHMITT_PINS_PER_GRF_REG;
		*reg += (bank->bank_num - 1) * PX30_SCHMITT_BANK_STRIDE;
	}
	*reg += ((pin_num / pins_per_reg) * 4);
	*bit = pin_num % pins_per_reg;

	return 0;
}

#define RV1108_PULL_PMU_OFFSET		0x10
#define RV1108_PULL_OFFSET		0x110
#define RV1108_PULL_PINS_PER_REG	8
#define RV1108_PULL_BITS_PER_PIN	2
#define RV1108_PULL_BANK_STRIDE		16

static void rv1108_calc_pull_reg_and_bit(struct rockchip_pin_bank *bank,
					 int pin_num, struct regmap **regmap,
					 int *reg, u8 *bit)
{
	struct rockchip_pinctrl_priv *priv = bank->priv;

	/* The first 24 pins of the first bank are located in PMU */
	if (bank->bank_num == 0) {
		*regmap = priv->regmap_pmu;
		*reg = RV1108_PULL_PMU_OFFSET;
	} else {
		*reg = RV1108_PULL_OFFSET;
		*regmap = priv->regmap_base;
		/* correct the offset, as we're starting with the 2nd bank */
		*reg -= 0x10;
		*reg += bank->bank_num * RV1108_PULL_BANK_STRIDE;
	}

	*reg += ((pin_num / RV1108_PULL_PINS_PER_REG) * 4);
	*bit = (pin_num % RV1108_PULL_PINS_PER_REG);
	*bit *= RV1108_PULL_BITS_PER_PIN;
}

#define RV1108_DRV_PMU_OFFSET		0x20
#define RV1108_DRV_GRF_OFFSET		0x210
#define RV1108_DRV_BITS_PER_PIN		2
#define RV1108_DRV_PINS_PER_REG		8
#define RV1108_DRV_BANK_STRIDE		16

static void rv1108_calc_drv_reg_and_bit(struct rockchip_pin_bank *bank,
					int pin_num, struct regmap **regmap,
					int *reg, u8 *bit)
{
	struct rockchip_pinctrl_priv *priv = bank->priv;

	/* The first 24 pins of the first bank are located in PMU */
	if (bank->bank_num == 0) {
		*regmap = priv->regmap_pmu;
		*reg = RV1108_DRV_PMU_OFFSET;
	} else {
		*regmap = priv->regmap_base;
		*reg = RV1108_DRV_GRF_OFFSET;

		/* correct the offset, as we're starting with the 2nd bank */
		*reg -= 0x10;
		*reg += bank->bank_num * RV1108_DRV_BANK_STRIDE;
	}

	*reg += ((pin_num / RV1108_DRV_PINS_PER_REG) * 4);
	*bit = pin_num % RV1108_DRV_PINS_PER_REG;
	*bit *= RV1108_DRV_BITS_PER_PIN;
}

#define RV1108_SCHMITT_PMU_OFFSET		0x30
#define RV1108_SCHMITT_GRF_OFFSET		0x388
#define RV1108_SCHMITT_BANK_STRIDE		8
#define RV1108_SCHMITT_PINS_PER_GRF_REG		16
#define RV1108_SCHMITT_PINS_PER_PMU_REG		8

static int rv1108_calc_schmitt_reg_and_bit(struct rockchip_pin_bank *bank,
					   int pin_num,
					   struct regmap **regmap,
					   int *reg, u8 *bit)
{
	struct rockchip_pinctrl_priv *priv = bank->priv;
	int pins_per_reg;

	if (bank->bank_num == 0) {
		*regmap = priv->regmap_pmu;
		*reg = RV1108_SCHMITT_PMU_OFFSET;
		pins_per_reg = RV1108_SCHMITT_PINS_PER_PMU_REG;
	} else {
		*regmap = priv->regmap_base;
		*reg = RV1108_SCHMITT_GRF_OFFSET;
		pins_per_reg = RV1108_SCHMITT_PINS_PER_GRF_REG;
		*reg += (bank->bank_num  - 1) * RV1108_SCHMITT_BANK_STRIDE;
	}
	*reg += ((pin_num / pins_per_reg) * 4);
	*bit = pin_num % pins_per_reg;

	return 0;
}

#define RV1126_PULL_PMU_OFFSET		0x40
#define RV1126_PULL_GRF_GPIO1A0_OFFSET		0x10108
#define RV1126_PULL_PINS_PER_REG	8
#define RV1126_PULL_BITS_PER_PIN	2
#define RV1126_PULL_BANK_STRIDE		16
#define RV1126_GPIO_C4_D7(p)	(p >= 20 && p <= 31) /* GPIO0_C4 ~ GPIO0_D7 */

static void rv1126_calc_pull_reg_and_bit(struct rockchip_pin_bank *bank,
					 int pin_num, struct regmap **regmap,
					 int *reg, u8 *bit)
{
	struct rockchip_pinctrl_priv *priv = bank->priv;

	/* The first 24 pins of the first bank are located in PMU */
	if (bank->bank_num == 0) {
		if (RV1126_GPIO_C4_D7(pin_num)) {
			*regmap = priv->regmap_base;
			*reg = RV1126_PULL_GRF_GPIO1A0_OFFSET;
			*reg -= (((31 - pin_num) / RV1126_PULL_PINS_PER_REG + 1) * 4);
			*bit = pin_num % RV1126_PULL_PINS_PER_REG;
			*bit *= RV1126_PULL_BITS_PER_PIN;
			return;
		}
		*regmap = priv->regmap_pmu;
		*reg = RV1126_PULL_PMU_OFFSET;
	} else {
		*reg = RV1126_PULL_GRF_GPIO1A0_OFFSET;
		*regmap = priv->regmap_base;
		*reg += (bank->bank_num - 1) * RV1126_PULL_BANK_STRIDE;
	}

	*reg += ((pin_num / RV1126_PULL_PINS_PER_REG) * 4);
	*bit = (pin_num % RV1126_PULL_PINS_PER_REG);
	*bit *= RV1126_PULL_BITS_PER_PIN;
}

#define RV1126_DRV_PMU_OFFSET		0x20
#define RV1126_DRV_GRF_GPIO1A0_OFFSET		0x10090
#define RV1126_DRV_BITS_PER_PIN		4
#define RV1126_DRV_PINS_PER_REG		4
#define RV1126_DRV_BANK_STRIDE		32

static void rv1126_calc_drv_reg_and_bit(struct rockchip_pin_bank *bank,
					int pin_num, struct regmap **regmap,
					int *reg, u8 *bit)
{
	struct rockchip_pinctrl_priv *priv = bank->priv;

	/* The first 24 pins of the first bank are located in PMU */
	if (bank->bank_num == 0) {
		if (RV1126_GPIO_C4_D7(pin_num)) {
			*regmap = priv->regmap_base;
			*reg = RV1126_DRV_GRF_GPIO1A0_OFFSET;
			*reg -= (((31 - pin_num) / RV1126_DRV_PINS_PER_REG + 1) * 4);
			*reg -= 0x4;
			*bit = pin_num % RV1126_DRV_PINS_PER_REG;
			*bit *= RV1126_DRV_BITS_PER_PIN;
			return;
		}
		*regmap = priv->regmap_pmu;
		*reg = RV1126_DRV_PMU_OFFSET;
	} else {
		*regmap = priv->regmap_base;
		*reg = RV1126_DRV_GRF_GPIO1A0_OFFSET;
		*reg += (bank->bank_num - 1) * RV1126_DRV_BANK_STRIDE;
	}

	*reg += ((pin_num / RV1126_DRV_PINS_PER_REG) * 4);
	*bit = pin_num % RV1126_DRV_PINS_PER_REG;
	*bit *= RV1126_DRV_BITS_PER_PIN;
}

#define RV1126_SCHMITT_PMU_OFFSET		0x60
#define RV1126_SCHMITT_GRF_GPIO1A0_OFFSET		0x10188
#define RV1126_SCHMITT_BANK_STRIDE		16
#define RV1126_SCHMITT_PINS_PER_GRF_REG		8
#define RV1126_SCHMITT_PINS_PER_PMU_REG		8

static int rv1126_calc_schmitt_reg_and_bit(struct rockchip_pin_bank *bank,
					   int pin_num,
					   struct regmap **regmap,
					   int *reg, u8 *bit)
{
	struct rockchip_pinctrl_priv *priv = bank->priv;
	int pins_per_reg;

	if (bank->bank_num == 0) {
		if (RV1126_GPIO_C4_D7(pin_num)) {
			*regmap = priv->regmap_base;
			*reg = RV1126_SCHMITT_GRF_GPIO1A0_OFFSET;
			*reg -= (((31 - pin_num) / RV1126_SCHMITT_PINS_PER_GRF_REG + 1) * 4);
			*bit = pin_num % RV1126_SCHMITT_PINS_PER_GRF_REG;
			return 0;
		}
		*regmap = priv->regmap_pmu;
		*reg = RV1126_SCHMITT_PMU_OFFSET;
		pins_per_reg = RV1126_SCHMITT_PINS_PER_PMU_REG;
	} else {
		*regmap = priv->regmap_base;
		*reg = RV1126_SCHMITT_GRF_GPIO1A0_OFFSET;
		pins_per_reg = RV1126_SCHMITT_PINS_PER_GRF_REG;
		*reg += (bank->bank_num - 1) * RV1126_SCHMITT_BANK_STRIDE;
	}
	*reg += ((pin_num / pins_per_reg) * 4);
	*bit = pin_num % pins_per_reg;

	return 0;
}

#define RK1808_PULL_PMU_OFFSET		0x10
#define RK1808_PULL_GRF_OFFSET		0x80
#define RK1808_PULL_PINS_PER_REG	8
#define RK1808_PULL_BITS_PER_PIN	2
#define RK1808_PULL_BANK_STRIDE		16

static void rk1808_calc_pull_reg_and_bit(struct rockchip_pin_bank *bank,
					 int pin_num,
					 struct regmap **regmap,
					 int *reg, u8 *bit)
{
	struct rockchip_pinctrl_priv *priv = bank->priv;

	if (bank->bank_num == 0) {
		*regmap = priv->regmap_pmu;
		*reg = RK1808_PULL_PMU_OFFSET;
	} else {
		*reg = RK1808_PULL_GRF_OFFSET;
		*regmap = priv->regmap_base;
	}

	*reg += ((pin_num / RK1808_PULL_PINS_PER_REG) * 4);
	*bit = (pin_num % RK1808_PULL_PINS_PER_REG);
	*bit *= RK1808_PULL_BITS_PER_PIN;
}

#define RK1808_DRV_PMU_OFFSET		0x20
#define RK1808_DRV_GRF_OFFSET		0x140
#define RK1808_DRV_BITS_PER_PIN		2
#define RK1808_DRV_PINS_PER_REG		8
#define RK1808_DRV_BANK_STRIDE		16

static void rk1808_calc_drv_reg_and_bit(struct rockchip_pin_bank *bank,
					int pin_num,
					struct regmap **regmap,
					int *reg, u8 *bit)
{
	struct rockchip_pinctrl_priv *priv = bank->priv;

	if (bank->bank_num == 0) {
		*regmap = priv->regmap_pmu;
		*reg = RK1808_DRV_PMU_OFFSET;
	} else {
		*regmap = priv->regmap_base;
		*reg = RK1808_DRV_GRF_OFFSET;
	}

	*reg += ((pin_num / RK1808_DRV_PINS_PER_REG) * 4);
	*bit = pin_num % RK1808_DRV_PINS_PER_REG;
	*bit *= RK1808_DRV_BITS_PER_PIN;
}

#define RK1808_SCHMITT_PMU_OFFSET		0x0040
#define RK1808_SCHMITT_GRF_OFFSET		0x0100
#define RK1808_SCHMITT_BANK_STRIDE		16
#define RK1808_SCHMITT_PINS_PER_REG		8

static int rk1808_calc_schmitt_reg_and_bit(struct rockchip_pin_bank *bank,
					   int pin_num,
					   struct regmap **regmap,
					   int *reg, u8 *bit)
{
	struct rockchip_pinctrl_priv *priv = bank->priv;

	if (bank->bank_num == 0) {
		*regmap = priv->regmap_pmu;
		*reg = RK1808_SCHMITT_PMU_OFFSET;
	} else {
		*regmap = priv->regmap_base;
		*reg = RK1808_SCHMITT_GRF_OFFSET;
		*reg += (bank->bank_num  - 1) * RK1808_SCHMITT_BANK_STRIDE;
	}
	*reg += ((pin_num / RK1808_SCHMITT_PINS_PER_REG) * 4);
	*bit = pin_num % RK1808_SCHMITT_PINS_PER_REG;

	return 0;
}

#define RK2928_PULL_OFFSET		0x118
#define RK2928_PULL_PINS_PER_REG	16
#define RK2928_PULL_BANK_STRIDE		8

static void rk2928_calc_pull_reg_and_bit(struct rockchip_pin_bank *bank,
					 int pin_num, struct regmap **regmap,
					 int *reg, u8 *bit)
{
	struct rockchip_pinctrl_priv *priv = bank->priv;

	*regmap = priv->regmap_base;
	*reg = RK2928_PULL_OFFSET;
	*reg += bank->bank_num * RK2928_PULL_BANK_STRIDE;
	*reg += (pin_num / RK2928_PULL_PINS_PER_REG) * 4;

	*bit = pin_num % RK2928_PULL_PINS_PER_REG;
};

#define RK3128_PULL_OFFSET	0x118

static void rk3128_calc_pull_reg_and_bit(struct rockchip_pin_bank *bank,
					 int pin_num, struct regmap **regmap,
					 int *reg, u8 *bit)
{
	struct rockchip_pinctrl_priv *priv = bank->priv;

	*regmap = priv->regmap_base;
	*reg = RK3128_PULL_OFFSET;
	*reg += bank->bank_num * RK2928_PULL_BANK_STRIDE;
	*reg += ((pin_num / RK2928_PULL_PINS_PER_REG) * 4);

	*bit = pin_num % RK2928_PULL_PINS_PER_REG;
}

#define RK3188_PULL_OFFSET		0x164
#define RK3188_PULL_BITS_PER_PIN	2
#define RK3188_PULL_PINS_PER_REG	8
#define RK3188_PULL_BANK_STRIDE		16
#define RK3188_PULL_PMU_OFFSET		0x64

static void rk3188_calc_pull_reg_and_bit(struct rockchip_pin_bank *bank,
					 int pin_num, struct regmap **regmap,
					 int *reg, u8 *bit)
{
	struct rockchip_pinctrl_priv *priv = bank->priv;

	/* The first 12 pins of the first bank are located elsewhere */
	if (bank->bank_num == 0 && pin_num < 12) {
		*regmap = priv->regmap_pmu;
		*reg = RK3188_PULL_PMU_OFFSET;

		*reg += ((pin_num / RK3188_PULL_PINS_PER_REG) * 4);
		*bit = pin_num % RK3188_PULL_PINS_PER_REG;
		*bit *= RK3188_PULL_BITS_PER_PIN;
	} else {
		*regmap = priv->regmap_base;
		*reg = RK3188_PULL_OFFSET;

		/* correct the offset, as it is the 2nd pull register */
		*reg -= 4;
		*reg += bank->bank_num * RK3188_PULL_BANK_STRIDE;
		*reg += ((pin_num / RK3188_PULL_PINS_PER_REG) * 4);

		/*
		 * The bits in these registers have an inverse ordering
		 * with the lowest pin being in bits 15:14 and the highest
		 * pin in bits 1:0
		 */
		*bit = 7 - (pin_num % RK3188_PULL_PINS_PER_REG);
		*bit *= RK3188_PULL_BITS_PER_PIN;
	}
}

#define RK3288_PULL_OFFSET		0x140
static void rk3288_calc_pull_reg_and_bit(struct rockchip_pin_bank *bank,
					 int pin_num, struct regmap **regmap,
					 int *reg, u8 *bit)
{
	struct rockchip_pinctrl_priv *priv = bank->priv;

	/* The first 24 pins of the first bank are located in PMU */
	if (bank->bank_num == 0) {
		*regmap = priv->regmap_pmu;
		*reg = RK3188_PULL_PMU_OFFSET;

		*reg += ((pin_num / RK3188_PULL_PINS_PER_REG) * 4);
		*bit = pin_num % RK3188_PULL_PINS_PER_REG;
		*bit *= RK3188_PULL_BITS_PER_PIN;
	} else {
		*regmap = priv->regmap_base;
		*reg = RK3288_PULL_OFFSET;

		/* correct the offset, as we're starting with the 2nd bank */
		*reg -= 0x10;
		*reg += bank->bank_num * RK3188_PULL_BANK_STRIDE;
		*reg += ((pin_num / RK3188_PULL_PINS_PER_REG) * 4);

		*bit = (pin_num % RK3188_PULL_PINS_PER_REG);
		*bit *= RK3188_PULL_BITS_PER_PIN;
	}
}

#define RK3288_DRV_PMU_OFFSET		0x70
#define RK3288_DRV_GRF_OFFSET		0x1c0
#define RK3288_DRV_BITS_PER_PIN		2
#define RK3288_DRV_PINS_PER_REG		8
#define RK3288_DRV_BANK_STRIDE		16

static void rk3288_calc_drv_reg_and_bit(struct rockchip_pin_bank *bank,
					int pin_num, struct regmap **regmap,
					int *reg, u8 *bit)
{
	struct rockchip_pinctrl_priv *priv = bank->priv;

	/* The first 24 pins of the first bank are located in PMU */
	if (bank->bank_num == 0) {
		*regmap = priv->regmap_pmu;
		*reg = RK3288_DRV_PMU_OFFSET;

		*reg += ((pin_num / RK3288_DRV_PINS_PER_REG) * 4);
		*bit = pin_num % RK3288_DRV_PINS_PER_REG;
		*bit *= RK3288_DRV_BITS_PER_PIN;
	} else {
		*regmap = priv->regmap_base;
		*reg = RK3288_DRV_GRF_OFFSET;

		/* correct the offset, as we're starting with the 2nd bank */
		*reg -= 0x10;
		*reg += bank->bank_num * RK3288_DRV_BANK_STRIDE;
		*reg += ((pin_num / RK3288_DRV_PINS_PER_REG) * 4);

		*bit = (pin_num % RK3288_DRV_PINS_PER_REG);
		*bit *= RK3288_DRV_BITS_PER_PIN;
	}
}

#define RK3228_PULL_OFFSET		0x100

static void rk3228_calc_pull_reg_and_bit(struct rockchip_pin_bank *bank,
					 int pin_num, struct regmap **regmap,
					 int *reg, u8 *bit)
{
	struct rockchip_pinctrl_priv *priv = bank->priv;

	*regmap = priv->regmap_base;
	*reg = RK3228_PULL_OFFSET;
	*reg += bank->bank_num * RK3188_PULL_BANK_STRIDE;
	*reg += ((pin_num / RK3188_PULL_PINS_PER_REG) * 4);

	*bit = (pin_num % RK3188_PULL_PINS_PER_REG);
	*bit *= RK3188_PULL_BITS_PER_PIN;
}

#define RK3228_DRV_GRF_OFFSET		0x200

static void rk3228_calc_drv_reg_and_bit(struct rockchip_pin_bank *bank,
					int pin_num, struct regmap **regmap,
					int *reg, u8 *bit)
{
	struct rockchip_pinctrl_priv *priv = bank->priv;

	*regmap = priv->regmap_base;
	*reg = RK3228_DRV_GRF_OFFSET;
	*reg += bank->bank_num * RK3288_DRV_BANK_STRIDE;
	*reg += ((pin_num / RK3288_DRV_PINS_PER_REG) * 4);

	*bit = (pin_num % RK3288_DRV_PINS_PER_REG);
	*bit *= RK3288_DRV_BITS_PER_PIN;
}

#define RK3308_PULL_OFFSET		0xa0

static void rk3308_calc_pull_reg_and_bit(struct rockchip_pin_bank *bank,
					 int pin_num, struct regmap **regmap,
					 int *reg, u8 *bit)
{
	struct rockchip_pinctrl_priv *priv = bank->priv;

	*regmap = priv->regmap_base;
	*reg = RK3308_PULL_OFFSET;
	*reg += bank->bank_num * RK3188_PULL_BANK_STRIDE;
	*reg += ((pin_num / RK3188_PULL_PINS_PER_REG) * 4);

	*bit = (pin_num % RK3188_PULL_PINS_PER_REG);
	*bit *= RK3188_PULL_BITS_PER_PIN;
}

#define RK3308_DRV_GRF_OFFSET		0x100

static void rk3308_calc_drv_reg_and_bit(struct rockchip_pin_bank *bank,
					int pin_num, struct regmap **regmap,
					int *reg, u8 *bit)
{
	struct rockchip_pinctrl_priv *priv = bank->priv;

	*regmap = priv->regmap_base;
	*reg = RK3308_DRV_GRF_OFFSET;
	*reg += bank->bank_num * RK3288_DRV_BANK_STRIDE;
	*reg += ((pin_num / RK3288_DRV_PINS_PER_REG) * 4);

	*bit = (pin_num % RK3288_DRV_PINS_PER_REG);
	*bit *= RK3288_DRV_BITS_PER_PIN;
}

#define RK3308_SCHMITT_PINS_PER_REG	8
#define RK3308_SCHMITT_BANK_STRIDE	16
#define RK3308_SCHMITT_GRF_OFFSET	0x1a0

static int rk3308_calc_schmitt_reg_and_bit(struct rockchip_pin_bank *bank,
					   int pin_num,
					   struct regmap **regmap,
					   int *reg, u8 *bit)
{
	struct rockchip_pinctrl_priv *priv = bank->priv;

	*regmap = priv->regmap_base;
	*reg = RK3308_SCHMITT_GRF_OFFSET;

	*reg += bank->bank_num * RK3308_SCHMITT_BANK_STRIDE;
	*reg += ((pin_num / RK3308_SCHMITT_PINS_PER_REG) * 4);
	*bit = pin_num % RK3308_SCHMITT_PINS_PER_REG;

	return 0;
}

#define RK3368_PULL_GRF_OFFSET		0x100
#define RK3368_PULL_PMU_OFFSET		0x10

static void rk3368_calc_pull_reg_and_bit(struct rockchip_pin_bank *bank,
					 int pin_num, struct regmap **regmap,
					 int *reg, u8 *bit)
{
	struct rockchip_pinctrl_priv *priv = bank->priv;

	/* The first 32 pins of the first bank are located in PMU */
	if (bank->bank_num == 0) {
		*regmap = priv->regmap_pmu;
		*reg = RK3368_PULL_PMU_OFFSET;

		*reg += ((pin_num / RK3188_PULL_PINS_PER_REG) * 4);
		*bit = pin_num % RK3188_PULL_PINS_PER_REG;
		*bit *= RK3188_PULL_BITS_PER_PIN;
	} else {
		*regmap = priv->regmap_base;
		*reg = RK3368_PULL_GRF_OFFSET;

		/* correct the offset, as we're starting with the 2nd bank */
		*reg -= 0x10;
		*reg += bank->bank_num * RK3188_PULL_BANK_STRIDE;
		*reg += ((pin_num / RK3188_PULL_PINS_PER_REG) * 4);

		*bit = (pin_num % RK3188_PULL_PINS_PER_REG);
		*bit *= RK3188_PULL_BITS_PER_PIN;
	}
}

#define RK3368_DRV_PMU_OFFSET		0x20
#define RK3368_DRV_GRF_OFFSET		0x200

static void rk3368_calc_drv_reg_and_bit(struct rockchip_pin_bank *bank,
					int pin_num, struct regmap **regmap,
					int *reg, u8 *bit)
{
	struct rockchip_pinctrl_priv *priv = bank->priv;

	/* The first 32 pins of the first bank are located in PMU */
	if (bank->bank_num == 0) {
		*regmap = priv->regmap_pmu;
		*reg = RK3368_DRV_PMU_OFFSET;

		*reg += ((pin_num / RK3288_DRV_PINS_PER_REG) * 4);
		*bit = pin_num % RK3288_DRV_PINS_PER_REG;
		*bit *= RK3288_DRV_BITS_PER_PIN;
	} else {
		*regmap = priv->regmap_base;
		*reg = RK3368_DRV_GRF_OFFSET;

		/* correct the offset, as we're starting with the 2nd bank */
		*reg -= 0x10;
		*reg += bank->bank_num * RK3288_DRV_BANK_STRIDE;
		*reg += ((pin_num / RK3288_DRV_PINS_PER_REG) * 4);

		*bit = (pin_num % RK3288_DRV_PINS_PER_REG);
		*bit *= RK3288_DRV_BITS_PER_PIN;
	}
}

#define RK3399_PULL_GRF_OFFSET		0xe040
#define RK3399_PULL_PMU_OFFSET		0x40
#define RK3399_DRV_3BITS_PER_PIN	3

static void rk3399_calc_pull_reg_and_bit(struct rockchip_pin_bank *bank,
					 int pin_num, struct regmap **regmap,
					 int *reg, u8 *bit)
{
	struct rockchip_pinctrl_priv *priv = bank->priv;

	/* The bank0:16 and bank1:32 pins are located in PMU */
	if ((bank->bank_num == 0) || (bank->bank_num == 1)) {
		*regmap = priv->regmap_pmu;
		*reg = RK3399_PULL_PMU_OFFSET;

		*reg += bank->bank_num * RK3188_PULL_BANK_STRIDE;

		*reg += ((pin_num / RK3188_PULL_PINS_PER_REG) * 4);
		*bit = pin_num % RK3188_PULL_PINS_PER_REG;
		*bit *= RK3188_PULL_BITS_PER_PIN;
	} else {
		*regmap = priv->regmap_base;
		*reg = RK3399_PULL_GRF_OFFSET;

		/* correct the offset, as we're starting with the 3rd bank */
		*reg -= 0x20;
		*reg += bank->bank_num * RK3188_PULL_BANK_STRIDE;
		*reg += ((pin_num / RK3188_PULL_PINS_PER_REG) * 4);

		*bit = (pin_num % RK3188_PULL_PINS_PER_REG);
		*bit *= RK3188_PULL_BITS_PER_PIN;
	}
}

static void rk3399_calc_drv_reg_and_bit(struct rockchip_pin_bank *bank,
					int pin_num, struct regmap **regmap,
					int *reg, u8 *bit)
{
	struct rockchip_pinctrl_priv *priv = bank->priv;
	int drv_num = (pin_num / 8);

	/*  The bank0:16 and bank1:32 pins are located in PMU */
	if ((bank->bank_num == 0) || (bank->bank_num == 1))
		*regmap = priv->regmap_pmu;
	else
		*regmap = priv->regmap_base;

	*reg = bank->drv[drv_num].offset;
	if ((bank->drv[drv_num].drv_type == DRV_TYPE_IO_1V8_3V0_AUTO) ||
	    (bank->drv[drv_num].drv_type == DRV_TYPE_IO_3V3_ONLY))
		*bit = (pin_num % 8) * 3;
	else
		*bit = (pin_num % 8) * 2;
}

#define RK3308_SLEW_RATE_GRF_OFFSET		0x150
#define RK3308_SLEW_RATE_BANK_STRIDE		16
#define RK3308_SLEW_RATE_PINS_PER_GRF_REG	8

static void rk3308_calc_slew_rate_reg_and_bit(struct rockchip_pin_bank *bank,
					      int pin_num,
					      struct regmap **regmap,
					      int *reg, u8 *bit)
{
	struct rockchip_pinctrl_priv *priv = bank->priv;
	int pins_per_reg;

	*regmap = priv->regmap_base;
	*reg = RK3308_SLEW_RATE_GRF_OFFSET;
	*reg += (bank->bank_num) * RK3308_SLEW_RATE_BANK_STRIDE;
	pins_per_reg = RK3308_SLEW_RATE_PINS_PER_GRF_REG;

	*reg += ((pin_num / pins_per_reg) * 4);
	*bit = pin_num % pins_per_reg;
}

static int rockchip_perpin_drv_list[DRV_TYPE_MAX][8] = {
	{ 2, 4, 8, 12, -1, -1, -1, -1 },
	{ 3, 6, 9, 12, -1, -1, -1, -1 },
	{ 5, 10, 15, 20, -1, -1, -1, -1 },
	{ 4, 6, 8, 10, 12, 14, 16, 18 },
	{ 4, 7, 10, 13, 16, 19, 22, 26 },
	{ 0, 2, 4, 6, 6, 8, 10, 12 }
};

static int rockchip_set_drive_perpin(struct rockchip_pin_bank *bank,
				     int pin_num, int strength)
{
	struct rockchip_pinctrl_priv *priv = bank->priv;
	struct rockchip_pin_ctrl *ctrl = priv->ctrl;
	struct regmap *regmap;
	int reg, ret, i;
	u32 data, rmask_bits, temp;
	u8 bit;
	/* Where need to clean the special mask for rockchip_perpin_drv_list */
	int drv_type = bank->drv[pin_num / 8].drv_type & (~DRV_TYPE_IO_MASK);

	debug("setting drive of GPIO%d-%d to %d\n", bank->bank_num,
	      pin_num, strength);

	ctrl->drv_calc_reg(bank, pin_num, &regmap, &reg, &bit);
	if (ctrl->type == RV1126) {
		rmask_bits = RV1126_DRV_BITS_PER_PIN;
		ret = strength;
		goto config;
	}
	if (soc_is_rk3308bs())
		drv_type = DRV_TYPE_IO_SMIC;

	ret = -EINVAL;
	for (i = 0; i < ARRAY_SIZE(rockchip_perpin_drv_list[drv_type]); i++) {
		if (rockchip_perpin_drv_list[drv_type][i] == strength) {
			ret = i;
			break;
		} else if (rockchip_perpin_drv_list[drv_type][i] < 0) {
			ret = rockchip_perpin_drv_list[drv_type][i];
			break;
		}
	}

	if (ret < 0) {
		debug("unsupported driver strength %d\n", strength);
		return ret;
	}

	switch (drv_type) {
	case DRV_TYPE_IO_SMIC:
		if (ctrl->type == RK3308) { /* RK3308B-S */
			int regval = ret;

			data = 0x3 << (bit + 16);
			data |= ((regval & 0x3) << bit);

			ret = regmap_write(regmap, reg, data);
			if (ret < 0)
				return ret;

			rk3308_calc_slew_rate_reg_and_bit(bank, pin_num, &regmap, &reg, &bit);
			data = BIT(bit + 16) | (((regval > 3) ? 1 : 0) << bit);

			return regmap_write(regmap, reg, data);
		}

		dev_err(info->dev, "unsupported type DRV_TYPE_IO_SMIC\n");
		return -EINVAL;
	case DRV_TYPE_IO_1V8_3V0_AUTO:
	case DRV_TYPE_IO_3V3_ONLY:
		rmask_bits = RK3399_DRV_3BITS_PER_PIN;
		switch (bit) {
		case 0 ... 12:
			/* regular case, nothing to do */
			break;
		case 15:
			/*
			 * drive-strength offset is special, as it is spread
			 * over 2 registers, the bit data[15] contains bit 0
			 * of the value while temp[1:0] contains bits 2 and 1
			 */
			data = (ret & 0x1) << 15;
			temp = (ret >> 0x1) & 0x3;

			data |= BIT(31);
			ret = regmap_write(regmap, reg, data);
			if (ret)
				return ret;

			temp |= (0x3 << 16);
			reg += 0x4;
			ret = regmap_write(regmap, reg, temp);

			return ret;
		case 18 ... 21:
			/* setting fully enclosed in the second register */
			reg += 4;
			bit -= 16;
			break;
		default:
			debug("unsupported bit: %d for pinctrl drive type: %d\n",
			      bit, drv_type);
			return -EINVAL;
		}
		break;
	case DRV_TYPE_IO_DEFAULT:
	case DRV_TYPE_IO_1V8_OR_3V0:
	case DRV_TYPE_IO_1V8_ONLY:
		rmask_bits = RK3288_DRV_BITS_PER_PIN;
		break;
	default:
		debug("unsupported pinctrl drive type: %d\n",
		      drv_type);
		return -EINVAL;
	}

config:
	if (bank->drv[pin_num / 8].drv_type & DRV_TYPE_WRITABLE_32BIT) {
		regmap_read(regmap, reg, &data);
		data &= ~(((1 << rmask_bits) - 1) << bit);
	} else {
		/* enable the write to the equivalent lower bits */
		data = ((1 << rmask_bits) - 1) << (bit + 16);
	}

	data |= (ret << bit);
	ret = regmap_write(regmap, reg, data);
	return ret;
}

static int rockchip_pull_list[PULL_TYPE_MAX][4] = {
	{
		PIN_CONFIG_BIAS_DISABLE,
		PIN_CONFIG_BIAS_PULL_UP,
		PIN_CONFIG_BIAS_PULL_DOWN,
		PIN_CONFIG_BIAS_BUS_HOLD
	},
	{
		PIN_CONFIG_BIAS_DISABLE,
		PIN_CONFIG_BIAS_PULL_DOWN,
		PIN_CONFIG_BIAS_DISABLE,
		PIN_CONFIG_BIAS_PULL_UP
	},
};

static int rockchip_set_pull(struct rockchip_pin_bank *bank,
			     int pin_num, int pull)
{
	struct rockchip_pinctrl_priv *priv = bank->priv;
	struct rockchip_pin_ctrl *ctrl = priv->ctrl;
	struct regmap *regmap;
	int reg, ret, i, pull_type;
	u8 bit;
	u32 data;

	debug("setting pull of GPIO%d-%d to %d\n", bank->bank_num,
	      pin_num, pull);

	/* rk3066b does support any pulls */
	if (ctrl->type == RK3066B)
		return pull ? -EINVAL : 0;

	ctrl->pull_calc_reg(bank, pin_num, &regmap, &reg, &bit);

	switch (ctrl->type) {
	case RK2928:
	case RK3128:
		data = BIT(bit + 16);
		if (pull == PIN_CONFIG_BIAS_DISABLE)
			data |= BIT(bit);
		ret = regmap_write(regmap, reg, data);
		break;
	case PX30:
	case RV1108:
	case RV1126:
	case RK1808:
	case RK3188:
	case RK3288:
	case RK3308:
	case RK3368:
	case RK3399:
		/*
		 * Where need to clean the special mask for
		 * rockchip_pull_list.
		 */
		pull_type = bank->pull_type[pin_num / 8] & (~PULL_TYPE_IO_MASK);
		ret = -EINVAL;
		for (i = 0; i < ARRAY_SIZE(rockchip_pull_list[pull_type]);
			i++) {
			if (rockchip_pull_list[pull_type][i] == pull) {
				ret = i;
				break;
			}
		}

		if (ret < 0) {
			debug("unsupported pull setting %d\n", pull);
			return ret;
		}

		if (bank->pull_type[pin_num / 8] & PULL_TYPE_WRITABLE_32BIT) {
			regmap_read(regmap, reg, &data);
			data &= ~(((1 << RK3188_PULL_BITS_PER_PIN) - 1) << bit);
		} else {
			/* enable the write to the equivalent lower bits */
			data = ((1 << RK3188_PULL_BITS_PER_PIN) - 1) << (bit + 16);
		}

		data |= (ret << bit);
		ret = regmap_write(regmap, reg, data);
		break;
	default:
		debug("unsupported pinctrl type\n");
		return -EINVAL;
	}

	return ret;
}

#define RK3328_SCHMITT_BITS_PER_PIN		1
#define RK3328_SCHMITT_PINS_PER_REG		16
#define RK3328_SCHMITT_BANK_STRIDE		8
#define RK3328_SCHMITT_GRF_OFFSET		0x380

static int rk3328_calc_schmitt_reg_and_bit(struct rockchip_pin_bank *bank,
					   int pin_num,
					   struct regmap **regmap,
					   int *reg, u8 *bit)
{
	struct rockchip_pinctrl_priv *priv = bank->priv;

	*regmap = priv->regmap_base;
	*reg = RK3328_SCHMITT_GRF_OFFSET;

	*reg += bank->bank_num * RK3328_SCHMITT_BANK_STRIDE;
	*reg += ((pin_num / RK3328_SCHMITT_PINS_PER_REG) * 4);
	*bit = pin_num % RK3328_SCHMITT_PINS_PER_REG;

	return 0;
}

static int rockchip_set_schmitt(struct rockchip_pin_bank *bank,
				int pin_num, int enable)
{
	struct rockchip_pinctrl_priv *priv = bank->priv;
	struct rockchip_pin_ctrl *ctrl = priv->ctrl;
	struct regmap *regmap;
	int reg, ret;
	u8 bit;
	u32 data;

	debug("setting input schmitt of GPIO%d-%d to %d\n", bank->bank_num,
	      pin_num, enable);

	ret = ctrl->schmitt_calc_reg(bank, pin_num, &regmap, &reg, &bit);
	if (ret)
		return ret;

	/* enable the write to the equivalent lower bits */
	data = BIT(bit + 16) | (enable << bit);

	return regmap_write(regmap, reg, data);
}

#define PX30_SLEW_RATE_PMU_OFFSET		0x30
#define PX30_SLEW_RATE_GRF_OFFSET		0x90
#define PX30_SLEW_RATE_PINS_PER_PMU_REG		16
#define PX30_SLEW_RATE_BANK_STRIDE		16
#define PX30_SLEW_RATE_PINS_PER_GRF_REG		8

static int px30_calc_slew_rate_reg_and_bit(struct rockchip_pin_bank *bank,
					   int pin_num,
					   struct regmap **regmap,
					   int *reg, u8 *bit)
{
	struct rockchip_pinctrl_priv *priv = bank->priv;
	int pins_per_reg;

	if (bank->bank_num == 0) {
		*regmap = priv->regmap_pmu;
		*reg = PX30_SLEW_RATE_PMU_OFFSET;
		pins_per_reg = PX30_SCHMITT_PINS_PER_PMU_REG;
	} else {
		*regmap = priv->regmap_base;
		*reg = PX30_SCHMITT_GRF_OFFSET;
		pins_per_reg = PX30_SCHMITT_PINS_PER_GRF_REG;
		*reg += (bank->bank_num  - 1) * PX30_SCHMITT_BANK_STRIDE;
	}
	*reg += ((pin_num / pins_per_reg) * 4);
	*bit = pin_num % pins_per_reg;

	return 0;
}

static int rockchip_set_slew_rate(struct rockchip_pin_bank *bank,
				  int pin_num, int speed)
{
	struct rockchip_pinctrl_priv *priv = bank->priv;
	struct rockchip_pin_ctrl *ctrl = priv->ctrl;
	struct regmap *regmap;
	int reg, ret;
	u8 bit;
	u32 data;

	debug("setting slew rate of GPIO%d-%d to %d\n", bank->bank_num,
	      pin_num, speed);

	ret = ctrl->slew_rate_calc_reg(bank, pin_num, &regmap, &reg, &bit);
	if (ret)
		return ret;

	/* enable the write to the equivalent lower bits */
	data = BIT(bit + 16) | (speed << bit);

	return regmap_write(regmap, reg, data);
}

/*
 * Pinconf_ops handling
 */
static bool rockchip_pinconf_pull_valid(struct rockchip_pin_ctrl *ctrl,
					unsigned int pull)
{
	switch (ctrl->type) {
	case RK2928:
	case RK3128:
		return (pull == PIN_CONFIG_BIAS_PULL_PIN_DEFAULT ||
			pull == PIN_CONFIG_BIAS_DISABLE);
	case RK3066B:
		return pull ? false : true;
	case PX30:
	case RV1108:
	case RV1126:
	case RK1808:
	case RK3188:
	case RK3288:
	case RK3308:
	case RK3368:
	case RK3399:
		return (pull != PIN_CONFIG_BIAS_PULL_PIN_DEFAULT);
	}

	return false;
}

/* set the pin config settings for a specified pin */
static int rockchip_pinconf_set(struct rockchip_pin_bank *bank,
				u32 pin, u32 param, u32 arg)
{
	struct rockchip_pinctrl_priv *priv = bank->priv;
	struct rockchip_pin_ctrl *ctrl = priv->ctrl;
	int rc;

	switch (param) {
	case PIN_CONFIG_BIAS_DISABLE:
		rc =  rockchip_set_pull(bank, pin, param);
		if (rc)
			return rc;
		break;

	case PIN_CONFIG_BIAS_PULL_UP:
	case PIN_CONFIG_BIAS_PULL_DOWN:
	case PIN_CONFIG_BIAS_PULL_PIN_DEFAULT:
	case PIN_CONFIG_BIAS_BUS_HOLD:
		if (!rockchip_pinconf_pull_valid(ctrl, param))
			return -ENOTSUPP;

		if (!arg)
			return -EINVAL;

		rc = rockchip_set_pull(bank, pin, param);
		if (rc)
			return rc;
		break;

	case PIN_CONFIG_DRIVE_STRENGTH:
		if (!ctrl->drv_calc_reg)
			return -ENOTSUPP;

		rc = rockchip_set_drive_perpin(bank, pin, arg);
		if (rc < 0)
			return rc;
		break;

	case PIN_CONFIG_INPUT_SCHMITT_ENABLE:
		if (!ctrl->schmitt_calc_reg)
			return -ENOTSUPP;

		rc = rockchip_set_schmitt(bank, pin, arg);
		if (rc < 0)
			return rc;
		break;

	case PIN_CONFIG_SLEW_RATE:
		if (!ctrl->slew_rate_calc_reg)
			return -ENOTSUPP;

		rc = rockchip_set_slew_rate(bank,
					    pin - bank->pin_base, arg);
		if (rc < 0)
			return rc;
		break;

	default:
		break;
	}

	return 0;
}

static const struct pinconf_param rockchip_conf_params[] = {
	{ "bias-disable", PIN_CONFIG_BIAS_DISABLE, 0 },
	{ "bias-bus-hold", PIN_CONFIG_BIAS_BUS_HOLD, 0 },
	{ "bias-pull-up", PIN_CONFIG_BIAS_PULL_UP, 1 },
	{ "bias-pull-down", PIN_CONFIG_BIAS_PULL_DOWN, 1 },
	{ "drive-strength", PIN_CONFIG_DRIVE_STRENGTH, 0 },
	{ "input-enable", PIN_CONFIG_INPUT_ENABLE, 1 },
	{ "input-disable", PIN_CONFIG_INPUT_ENABLE, 0 },
	{ "input-schmitt-disable", PIN_CONFIG_INPUT_SCHMITT_ENABLE, 0 },
	{ "input-schmitt-enable", PIN_CONFIG_INPUT_SCHMITT_ENABLE, 1 },
	{ "slew-rate", PIN_CONFIG_SLEW_RATE, 0 },
};

static int rockchip_pinconf_prop_name_to_param(const char *property,
					       u32 *default_value)
{
	const struct pinconf_param *p, *end;

	p = rockchip_conf_params;
	end = p + sizeof(rockchip_conf_params) / sizeof(struct pinconf_param);

	/* See if this pctldev supports this parameter */
	for (; p < end; p++) {
		if (!strcmp(property, p->property)) {
			*default_value = p->default_value;
			return p->param;
		}
	}

	*default_value = 0;
	return -EPERM;
}

static int rockchip_pinctrl_set_state(struct udevice *dev,
				      struct udevice *config)
{
	struct rockchip_pinctrl_priv *priv = dev_get_priv(dev);
	struct rockchip_pin_ctrl *ctrl = priv->ctrl;
	u32 cells[MAX_ROCKCHIP_PINS_ENTRIES * 4];
	u32 bank, pin, mux, conf, arg, default_val;
	int ret, count, i;
	const char *prop_name;
	const void *value;
	int prop_len, param;
	const u32 *data;
	ofnode node;
#if defined(CONFIG_OF_LIVE) && !defined(CONFIG_SPL_BUILD)
	const struct device_node *np;
	struct property *pp;
#else
	int property_offset, pcfg_node;
	const void *blob = gd->fdt_blob;
#endif
	data = dev_read_prop(config, "rockchip,pins", &count);
	if (count < 0) {
		debug("%s: bad array size %d\n", __func__, count);
		return -EINVAL;
	}

	count /= sizeof(u32);
	if (count > MAX_ROCKCHIP_PINS_ENTRIES * 4) {
		debug("%s: unsupported pins array count %d\n",
		      __func__, count);
		return -EINVAL;
	}

	for (i = 0; i < count; i++)
		cells[i] = fdt32_to_cpu(data[i]);

	for (i = 0; i < (count >> 2); i++) {
		bank = cells[4 * i + 0];
		pin = cells[4 * i + 1];
		mux = cells[4 * i + 2];
		conf = cells[4 * i + 3];

		ret = rockchip_verify_config(dev, bank, pin);
		if (ret)
			return ret;

		ret = rockchip_set_mux(&ctrl->pin_banks[bank], pin, mux);
		if (ret)
			return ret;

		node = ofnode_get_by_phandle(conf);
		if (!ofnode_valid(node))
			return -ENODEV;
#if defined(CONFIG_OF_LIVE) && !defined(CONFIG_SPL_BUILD)
		np = ofnode_to_np(node);
		for (pp = np->properties; pp; pp = pp->next) {
			prop_name = pp->name;
			prop_len = pp->length;
			value = pp->value;
#else
		pcfg_node = ofnode_to_offset(node);
		fdt_for_each_property_offset(property_offset, blob, pcfg_node) {
			value = fdt_getprop_by_offset(blob, property_offset,
						      &prop_name, &prop_len);
			if (!value)
				return -ENOENT;
#endif
			param = rockchip_pinconf_prop_name_to_param(prop_name,
								    &default_val);
			if (param < 0)
				break;

			if (prop_len >= sizeof(fdt32_t))
				arg = fdt32_to_cpu(*(fdt32_t *)value);
			else
				arg = default_val;

			ret = rockchip_pinconf_set(&ctrl->pin_banks[bank], pin,
						   param, arg);
			if (ret) {
				debug("%s: rockchip_pinconf_set fail: %d\n",
				      __func__, ret);
				return ret;
			}
		}
	}

	return 0;
}

static int rockchip_pinctrl_get_pins_count(struct udevice *dev)
{
	struct rockchip_pinctrl_priv *priv = dev_get_priv(dev);
	struct rockchip_pin_ctrl *ctrl = priv->ctrl;

	return ctrl->nr_pins;
}

static struct pinctrl_ops rockchip_pinctrl_ops = {
	.get_pins_count			= rockchip_pinctrl_get_pins_count,
	.set_state			= rockchip_pinctrl_set_state,
	.get_gpio_mux			= rockchip_pinctrl_get_gpio_mux,
};

static const struct rockchip_pin_ctrl rk3308b_pin_ctrl;

/* retrieve the soc specific data */
static const struct rockchip_pin_ctrl *
rockchip_pinctrl_get_soc_data(struct udevice *dev)
{
	struct rockchip_pinctrl_priv *priv = dev_get_priv(dev);
	const struct rockchip_pin_ctrl *ctrl =
		(const struct rockchip_pin_ctrl *)dev_get_driver_data(dev);
	struct rockchip_pin_bank *bank;
	int grf_offs, pmu_offs, drv_grf_offs, drv_pmu_offs, i, j;
	u32 nr_pins;

	if (soc_is_rk3308b() || soc_is_rk3308bs())
		ctrl = &rk3308b_pin_ctrl;

	grf_offs = ctrl->grf_mux_offset;
	pmu_offs = ctrl->pmu_mux_offset;
	drv_pmu_offs = ctrl->pmu_drv_offset;
	drv_grf_offs = ctrl->grf_drv_offset;
	bank = ctrl->pin_banks;

	/* Ctrl data re-initialize for some Socs */
	if (ctrl->ctrl_data_re_init) {
		if (ctrl->ctrl_data_re_init(ctrl))
			return NULL;
	}

	nr_pins = 0;
	for (i = 0; i < ctrl->nr_banks; ++i, ++bank) {
		int bank_pins = 0;

		bank->priv = priv;
		bank->pin_base = nr_pins;
		nr_pins += bank->nr_pins;

		/* calculate iomux and drv offsets */
		for (j = 0; j < 4; j++) {
			struct rockchip_iomux *iom = &bank->iomux[j];
			struct rockchip_drv *drv = &bank->drv[j];
			int inc;

			if (bank_pins >= bank->nr_pins)
				break;

			/* preset iomux offset value, set new start value */
			if (iom->offset >= 0) {
				if ((iom->type & IOMUX_SOURCE_PMU) || (iom->type & IOMUX_L_SOURCE_PMU))
					pmu_offs = iom->offset;
				else
					grf_offs = iom->offset;
			} else { /* set current iomux offset */
				iom->offset = ((iom->type & IOMUX_SOURCE_PMU) ||
					       (iom->type & IOMUX_L_SOURCE_PMU)) ?
							pmu_offs : grf_offs;
			}

			/* preset drv offset value, set new start value */
			if (drv->offset >= 0) {
				if (iom->type & IOMUX_SOURCE_PMU)
					drv_pmu_offs = drv->offset;
				else
					drv_grf_offs = drv->offset;
			} else { /* set current drv offset */
				drv->offset = (iom->type & IOMUX_SOURCE_PMU) ?
						drv_pmu_offs : drv_grf_offs;
			}

			debug("bank %d, iomux %d has iom_offset 0x%x drv_offset 0x%x\n",
			      i, j, iom->offset, drv->offset);

			/*
			 * Increase offset according to iomux width.
			 * 4bit iomux'es are spread over two registers.
			 */
			inc = (iom->type & (IOMUX_WIDTH_4BIT |
					    IOMUX_WIDTH_3BIT |
					    IOMUX_8WIDTH_2BIT)) ? 8 : 4;
			if ((iom->type & IOMUX_SOURCE_PMU) || (iom->type & IOMUX_L_SOURCE_PMU))
				pmu_offs += inc;
			else
				grf_offs += inc;

			/*
			 * Increase offset according to drv width.
			 * 3bit drive-strenth'es are spread over two registers.
			 */
			if ((drv->drv_type == DRV_TYPE_IO_1V8_3V0_AUTO) ||
			    (drv->drv_type == DRV_TYPE_IO_3V3_ONLY))
				inc = 8;
			else
				inc = 4;

			if (iom->type & IOMUX_SOURCE_PMU)
				drv_pmu_offs += inc;
			else
				drv_grf_offs += inc;

			bank_pins += 8;
		}

		/* calculate the per-bank recalced_mask */
		for (j = 0; j < ctrl->niomux_recalced; j++) {
			int pin = 0;

			if (ctrl->iomux_recalced[j].num == bank->bank_num) {
				pin = ctrl->iomux_recalced[j].pin;
				bank->recalced_mask |= BIT(pin);
			}
		}

		/* calculate the per-bank route_mask */
		for (j = 0; j < ctrl->niomux_routes; j++) {
			int pin = 0;

			if (ctrl->iomux_routes[j].bank_num == bank->bank_num) {
				pin = ctrl->iomux_routes[j].pin;
				bank->route_mask |= BIT(pin);
			}
		}
	}

	WARN_ON(nr_pins != ctrl->nr_pins);

	return ctrl;
}

/* SoC data specially handle */

/* rk3308b SoC data initialize */
#define RK3308B_GRF_SOC_CON13			0x608
#define RK3308B_GRF_SOC_CON15			0x610

/* RK3308B_GRF_SOC_CON13 */
#define RK3308B_GRF_I2C3_IOFUNC_SRC_CTRL	(BIT(16 + 10) | BIT(10))
#define RK3308B_GRF_GPIO2A3_SEL_SRC_CTRL	(BIT(16 + 7)  | BIT(7))
#define RK3308B_GRF_GPIO2A2_SEL_SRC_CTRL	(BIT(16 + 3)  | BIT(3))

/* RK3308B_GRF_SOC_CON15 */
#define RK3308B_GRF_GPIO2C0_SEL_SRC_CTRL	(BIT(16 + 11) | BIT(11))
#define RK3308B_GRF_GPIO3B3_SEL_SRC_CTRL	(BIT(16 + 7)  | BIT(7))
#define RK3308B_GRF_GPIO3B2_SEL_SRC_CTRL	(BIT(16 + 3)  | BIT(3))

static int rk3308b_soc_data_init(struct rockchip_pinctrl_priv *priv)
{
	int ret;

	/*
	 * Enable the special ctrl  of selected sources.
	 */
	ret = regmap_write(priv->regmap_base, RK3308B_GRF_SOC_CON13,
			   RK3308B_GRF_I2C3_IOFUNC_SRC_CTRL |
			   RK3308B_GRF_GPIO2A3_SEL_SRC_CTRL |
			   RK3308B_GRF_GPIO2A2_SEL_SRC_CTRL);
	if (ret)
		return ret;

	ret = regmap_write(priv->regmap_base, RK3308B_GRF_SOC_CON15,
			   RK3308B_GRF_GPIO2C0_SEL_SRC_CTRL |
			   RK3308B_GRF_GPIO3B3_SEL_SRC_CTRL |
			   RK3308B_GRF_GPIO3B2_SEL_SRC_CTRL);
	if (ret)
		return ret;

	return 0;
}

static int rockchip_pinctrl_probe(struct udevice *dev)
{
	struct rockchip_pinctrl_priv *priv = dev_get_priv(dev);
	const struct rockchip_pin_ctrl *ctrl;
	struct udevice *syscon;
	struct regmap *regmap;
	int ret = 0;

	/* get rockchip grf syscon phandle */
	ret = uclass_get_device_by_phandle(UCLASS_SYSCON, dev, "rockchip,grf",
					   &syscon);
	if (ret) {
		debug("unable to find rockchip,grf syscon device (%d)\n", ret);
		return ret;
	}

	/* get grf-reg base address */
	regmap = syscon_get_regmap(syscon);
	if (!regmap) {
		debug("unable to find rockchip grf regmap\n");
		return -ENODEV;
	}
	priv->regmap_base = regmap;

	/* option: get pmu-reg base address */
	ret = uclass_get_device_by_phandle(UCLASS_SYSCON, dev, "rockchip,pmu",
					   &syscon);
	if (!ret) {
		/* get pmugrf-reg base address */
		regmap = syscon_get_regmap(syscon);
		if (!regmap) {
			debug("unable to find rockchip pmu regmap\n");
			return -ENODEV;
		}
		priv->regmap_pmu = regmap;
	}

	ctrl = rockchip_pinctrl_get_soc_data(dev);
	if (!ctrl) {
		debug("driver data not available\n");
		return -EINVAL;
	}

	/* Special handle for some Socs */
	if (ctrl->soc_data_init) {
		ret = ctrl->soc_data_init(priv);
		if (ret)
			return ret;
	}

	priv->ctrl = (struct rockchip_pin_ctrl *)ctrl;
	return 0;
}

static struct rockchip_pin_bank px30_pin_banks[] = {
	PIN_BANK_IOMUX_FLAGS(0, 32, "gpio0", IOMUX_SOURCE_PMU,
					     IOMUX_SOURCE_PMU,
					     IOMUX_SOURCE_PMU,
					     IOMUX_SOURCE_PMU
			    ),
	PIN_BANK_IOMUX_FLAGS(1, 32, "gpio1", IOMUX_WIDTH_4BIT,
					     IOMUX_WIDTH_4BIT,
					     IOMUX_WIDTH_4BIT,
					     IOMUX_WIDTH_4BIT
			    ),
	PIN_BANK_IOMUX_FLAGS(2, 32, "gpio2", IOMUX_WIDTH_4BIT,
					     IOMUX_WIDTH_4BIT,
					     IOMUX_WIDTH_4BIT,
					     IOMUX_WIDTH_4BIT
			    ),
	PIN_BANK_IOMUX_FLAGS(3, 32, "gpio3", IOMUX_WIDTH_4BIT,
					     IOMUX_WIDTH_4BIT,
					     IOMUX_WIDTH_4BIT,
					     IOMUX_WIDTH_4BIT
			    ),
};

static const struct rockchip_pin_ctrl px30_pin_ctrl = {
	.pin_banks		= px30_pin_banks,
	.nr_banks		= ARRAY_SIZE(px30_pin_banks),
	.nr_pins		= 128,
	.label			= "PX30-GPIO",
	.type			= PX30,
	.grf_mux_offset		= 0x0,
	.pmu_mux_offset		= 0x0,
	.iomux_routes		= px30_mux_route_data,
	.niomux_routes		= ARRAY_SIZE(px30_mux_route_data),
	.pull_calc_reg		= px30_calc_pull_reg_and_bit,
	.drv_calc_reg		= px30_calc_drv_reg_and_bit,
	.schmitt_calc_reg	= px30_calc_schmitt_reg_and_bit,
	.slew_rate_calc_reg	= px30_calc_slew_rate_reg_and_bit,
};

static struct rockchip_pin_bank rv1108_pin_banks[] = {
	PIN_BANK_IOMUX_FLAGS(0, 32, "gpio0", IOMUX_SOURCE_PMU,
					     IOMUX_SOURCE_PMU,
					     IOMUX_SOURCE_PMU,
					     IOMUX_SOURCE_PMU),
	PIN_BANK_IOMUX_FLAGS(1, 32, "gpio1", 0, 0, 0, 0),
	PIN_BANK_IOMUX_FLAGS(2, 32, "gpio2", 0, 0, 0, 0),
	PIN_BANK_IOMUX_FLAGS(3, 32, "gpio3", 0, 0, 0, 0),
};

static const struct rockchip_pin_ctrl rv1108_pin_ctrl = {
	.pin_banks		= rv1108_pin_banks,
	.nr_banks		= ARRAY_SIZE(rv1108_pin_banks),
	.nr_pins		= 128,
	.label			= "RV1108-GPIO",
	.type			= RV1108,
	.grf_mux_offset		= 0x10,
	.pmu_mux_offset		= 0x0,
	.iomux_recalced		= rv1108_mux_recalced_data,
	.niomux_recalced	= ARRAY_SIZE(rv1108_mux_recalced_data),
	.pull_calc_reg		= rv1108_calc_pull_reg_and_bit,
	.drv_calc_reg		= rv1108_calc_drv_reg_and_bit,
	.schmitt_calc_reg	= rv1108_calc_schmitt_reg_and_bit,
};

static struct rockchip_pin_bank rv1126_pin_banks[] = {
	PIN_BANK_IOMUX_FLAGS(0, 32, "gpio0",
			     IOMUX_WIDTH_4BIT | IOMUX_SOURCE_PMU,
			     IOMUX_WIDTH_4BIT | IOMUX_SOURCE_PMU,
			     IOMUX_WIDTH_4BIT | IOMUX_L_SOURCE_PMU,
			     IOMUX_WIDTH_4BIT),
	PIN_BANK_IOMUX_FLAGS_OFFSET(1, 32, "gpio1",
			     IOMUX_WIDTH_4BIT,
			     IOMUX_WIDTH_4BIT,
			     IOMUX_WIDTH_4BIT,
			     IOMUX_WIDTH_4BIT,
			     0x10010, 0x10018, 0x10020, 0x10028),
	PIN_BANK_IOMUX_FLAGS(2, 32, "gpio2",
			     IOMUX_WIDTH_4BIT,
			     IOMUX_WIDTH_4BIT,
			     IOMUX_WIDTH_4BIT,
			     IOMUX_WIDTH_4BIT),
	PIN_BANK_IOMUX_FLAGS(3, 32, "gpio3",
			     IOMUX_WIDTH_4BIT,
			     IOMUX_WIDTH_4BIT,
			     IOMUX_WIDTH_4BIT,
			     IOMUX_WIDTH_4BIT),
	PIN_BANK_IOMUX_FLAGS(4, 2, "gpio4",
			     IOMUX_WIDTH_4BIT, 0, 0, 0),
};

static const struct rockchip_pin_ctrl rv1126_pin_ctrl = {
	.pin_banks		= rv1126_pin_banks,
	.nr_banks		= ARRAY_SIZE(rv1126_pin_banks),
	.nr_pins		= 130,
	.label			= "RV1126-GPIO",
	.type			= RV1126,
	.grf_mux_offset		= 0x10004, /* mux offset from GPIO0_D0 */
	.pmu_mux_offset		= 0x0,
	.iomux_routes		= rv1126_mux_route_data,
	.niomux_routes		= ARRAY_SIZE(rv1126_mux_route_data),
	.iomux_recalced		= rv1126_mux_recalced_data,
	.niomux_recalced	= ARRAY_SIZE(rv1126_mux_recalced_data),
	.pull_calc_reg		= rv1126_calc_pull_reg_and_bit,
	.drv_calc_reg		= rv1126_calc_drv_reg_and_bit,
	.schmitt_calc_reg	= rv1126_calc_schmitt_reg_and_bit,
};

static struct rockchip_pin_bank rk1808_pin_banks[] = {
	PIN_BANK_IOMUX_FLAGS(0, 32, "gpio0",
			     IOMUX_SOURCE_PMU,
			     IOMUX_SOURCE_PMU,
			     IOMUX_SOURCE_PMU,
			     IOMUX_SOURCE_PMU),
	PIN_BANK_IOMUX_FLAGS(1, 32, "gpio1",
			     IOMUX_WIDTH_4BIT,
			     IOMUX_WIDTH_4BIT,
			     IOMUX_WIDTH_4BIT,
			     IOMUX_WIDTH_4BIT),
	PIN_BANK_IOMUX_FLAGS(2, 32, "gpio2",
			     IOMUX_WIDTH_4BIT,
			     IOMUX_WIDTH_4BIT,
			     IOMUX_WIDTH_4BIT,
			     IOMUX_WIDTH_4BIT),
	PIN_BANK_IOMUX_FLAGS(3, 32, "gpio3",
			     IOMUX_WIDTH_4BIT,
			     IOMUX_WIDTH_4BIT,
			     IOMUX_WIDTH_4BIT,
			     IOMUX_WIDTH_4BIT),
	PIN_BANK_IOMUX_FLAGS(4, 32, "gpio4",
			     IOMUX_WIDTH_4BIT,
			     IOMUX_WIDTH_4BIT,
			     IOMUX_WIDTH_4BIT,
			     IOMUX_WIDTH_4BIT),
};

static const struct rockchip_pin_ctrl rk1808_pin_ctrl = {
	.pin_banks		= rk1808_pin_banks,
	.nr_banks		= ARRAY_SIZE(rk1808_pin_banks),
	.nr_pins		= 160,
	.label			= "RK1808-GPIO",
	.type			= RK1808,
	.iomux_routes		= rk1808_mux_route_data,
	.niomux_routes		= ARRAY_SIZE(rk1808_mux_route_data),
	.grf_mux_offset		= 0x0,
	.pmu_mux_offset		= 0x0,
	.pull_calc_reg		= rk1808_calc_pull_reg_and_bit,
	.drv_calc_reg		= rk1808_calc_drv_reg_and_bit,
	.schmitt_calc_reg	= rk1808_calc_schmitt_reg_and_bit,
};

static struct rockchip_pin_bank rk2928_pin_banks[] = {
	PIN_BANK(0, 32, "gpio0"),
	PIN_BANK(1, 32, "gpio1"),
	PIN_BANK(2, 32, "gpio2"),
	PIN_BANK(3, 32, "gpio3"),
};

static const struct rockchip_pin_ctrl rk2928_pin_ctrl = {
	.pin_banks		= rk2928_pin_banks,
	.nr_banks		= ARRAY_SIZE(rk2928_pin_banks),
	.nr_pins		= 128,
	.label			= "RK2928-GPIO",
	.type			= RK2928,
	.grf_mux_offset		= 0xa8,
	.pull_calc_reg		= rk2928_calc_pull_reg_and_bit,
};

static struct rockchip_pin_bank rk3036_pin_banks[] = {
	PIN_BANK(0, 32, "gpio0"),
	PIN_BANK(1, 32, "gpio1"),
	PIN_BANK(2, 32, "gpio2"),
};

static const struct rockchip_pin_ctrl rk3036_pin_ctrl = {
	.pin_banks		= rk3036_pin_banks,
	.nr_banks		= ARRAY_SIZE(rk3036_pin_banks),
	.nr_pins		= 96,
	.label			= "RK3036-GPIO",
	.type			= RK2928,
	.grf_mux_offset		= 0xa8,
	.pull_calc_reg		= rk2928_calc_pull_reg_and_bit,
};

static struct rockchip_pin_bank rk3066a_pin_banks[] = {
	PIN_BANK(0, 32, "gpio0"),
	PIN_BANK(1, 32, "gpio1"),
	PIN_BANK(2, 32, "gpio2"),
	PIN_BANK(3, 32, "gpio3"),
	PIN_BANK(4, 32, "gpio4"),
	PIN_BANK(6, 16, "gpio6"),
};

static const struct rockchip_pin_ctrl rk3066a_pin_ctrl = {
	.pin_banks		= rk3066a_pin_banks,
	.nr_banks		= ARRAY_SIZE(rk3066a_pin_banks),
	.nr_pins		= 176,
	.label			= "RK3066a-GPIO",
	.type			= RK2928,
	.grf_mux_offset		= 0xa8,
	.pull_calc_reg		= rk2928_calc_pull_reg_and_bit,
};

static struct rockchip_pin_bank rk3066b_pin_banks[] = {
	PIN_BANK(0, 32, "gpio0"),
	PIN_BANK(1, 32, "gpio1"),
	PIN_BANK(2, 32, "gpio2"),
	PIN_BANK(3, 32, "gpio3"),
};

static const struct rockchip_pin_ctrl rk3066b_pin_ctrl = {
	.pin_banks		= rk3066b_pin_banks,
	.nr_banks		= ARRAY_SIZE(rk3066b_pin_banks),
	.nr_pins		= 128,
	.label			= "RK3066b-GPIO",
	.type			= RK3066B,
	.grf_mux_offset		= 0x60,
};

static struct rockchip_pin_bank rk3128_pin_banks[] = {
	PIN_BANK(0, 32, "gpio0"),
	PIN_BANK(1, 32, "gpio1"),
	PIN_BANK(2, 32, "gpio2"),
	PIN_BANK(3, 32, "gpio3"),
};

static const struct rockchip_pin_ctrl rk3128_pin_ctrl = {
	.pin_banks		= rk3128_pin_banks,
	.nr_banks		= ARRAY_SIZE(rk3128_pin_banks),
	.nr_pins		= 128,
	.label			= "RK3128-GPIO",
	.type			= RK3128,
	.grf_mux_offset		= 0xa8,
	.iomux_recalced		= rk3128_mux_recalced_data,
	.niomux_recalced	= ARRAY_SIZE(rk3128_mux_recalced_data),
	.iomux_routes		= rk3128_mux_route_data,
	.niomux_routes		= ARRAY_SIZE(rk3128_mux_route_data),
	.pull_calc_reg		= rk3128_calc_pull_reg_and_bit,
};

static struct rockchip_pin_bank rk3188_pin_banks[] = {
	PIN_BANK_IOMUX_FLAGS(0, 32, "gpio0", IOMUX_GPIO_ONLY, 0, 0, 0),
	PIN_BANK(1, 32, "gpio1"),
	PIN_BANK(2, 32, "gpio2"),
	PIN_BANK(3, 32, "gpio3"),
};

static const struct rockchip_pin_ctrl rk3188_pin_ctrl = {
	.pin_banks		= rk3188_pin_banks,
	.nr_banks		= ARRAY_SIZE(rk3188_pin_banks),
	.nr_pins		= 128,
	.label			= "RK3188-GPIO",
	.type			= RK3188,
	.grf_mux_offset		= 0x60,
	.pull_calc_reg		= rk3188_calc_pull_reg_and_bit,
};

static struct rockchip_pin_bank rk3228_pin_banks[] = {
	PIN_BANK(0, 32, "gpio0"),
	PIN_BANK(1, 32, "gpio1"),
	PIN_BANK(2, 32, "gpio2"),
	PIN_BANK(3, 32, "gpio3"),
};

static const struct rockchip_pin_ctrl rk3228_pin_ctrl = {
	.pin_banks		= rk3228_pin_banks,
	.nr_banks		= ARRAY_SIZE(rk3228_pin_banks),
	.nr_pins		= 128,
	.label			= "RK3228-GPIO",
	.type			= RK3288,
	.grf_mux_offset		= 0x0,
	.iomux_routes		= rk3228_mux_route_data,
	.niomux_routes		= ARRAY_SIZE(rk3228_mux_route_data),
	.pull_calc_reg		= rk3228_calc_pull_reg_and_bit,
	.drv_calc_reg		= rk3228_calc_drv_reg_and_bit,
};

static struct rockchip_pin_bank rk3288_pin_banks[] = {
	PIN_BANK_IOMUX_DRV_PULL_FLAGS(0, 24, "gpio0",
				      IOMUX_SOURCE_PMU | IOMUX_WRITABLE_32BIT,
				      IOMUX_SOURCE_PMU | IOMUX_WRITABLE_32BIT,
				      IOMUX_SOURCE_PMU | IOMUX_WRITABLE_32BIT,
				      IOMUX_UNROUTED,
				      DRV_TYPE_WRITABLE_32BIT,
				      DRV_TYPE_WRITABLE_32BIT,
				      DRV_TYPE_WRITABLE_32BIT,
				      0,
				      PULL_TYPE_WRITABLE_32BIT,
				      PULL_TYPE_WRITABLE_32BIT,
				      PULL_TYPE_WRITABLE_32BIT,
				      0
			    ),
	PIN_BANK_IOMUX_FLAGS(1, 32, "gpio1", IOMUX_UNROUTED,
					     IOMUX_UNROUTED,
					     IOMUX_UNROUTED,
					     0
			    ),
	PIN_BANK_IOMUX_FLAGS(2, 32, "gpio2", 0, 0, 0, IOMUX_UNROUTED),
	PIN_BANK_IOMUX_FLAGS(3, 32, "gpio3", 0, 0, 0, IOMUX_WIDTH_4BIT),
	PIN_BANK_IOMUX_FLAGS(4, 32, "gpio4", IOMUX_WIDTH_4BIT,
					     IOMUX_WIDTH_4BIT,
					     0,
					     0
			    ),
	PIN_BANK_IOMUX_FLAGS(5, 32, "gpio5", IOMUX_UNROUTED,
					     0,
					     0,
					     IOMUX_UNROUTED
			    ),
	PIN_BANK_IOMUX_FLAGS(6, 32, "gpio6", 0, 0, 0, IOMUX_UNROUTED),
	PIN_BANK_IOMUX_FLAGS(7, 32, "gpio7", 0,
					     0,
					     IOMUX_WIDTH_4BIT,
					     IOMUX_UNROUTED
			    ),
	PIN_BANK(8, 16, "gpio8"),
};

static const struct rockchip_pin_ctrl rk3288_pin_ctrl = {
	.pin_banks		= rk3288_pin_banks,
	.nr_banks		= ARRAY_SIZE(rk3288_pin_banks),
	.nr_pins		= 264,
	.label			= "RK3288-GPIO",
	.type			= RK3288,
	.grf_mux_offset		= 0x0,
	.pmu_mux_offset		= 0x84,
	.iomux_routes		= rk3288_mux_route_data,
	.niomux_routes		= ARRAY_SIZE(rk3288_mux_route_data),
	.pull_calc_reg		= rk3288_calc_pull_reg_and_bit,
	.drv_calc_reg		= rk3288_calc_drv_reg_and_bit,
};

static struct rockchip_pin_bank rk3308_pin_banks[] = {
	PIN_BANK_IOMUX_FLAGS(0, 32, "gpio0", IOMUX_8WIDTH_2BIT,
					     IOMUX_8WIDTH_2BIT,
					     IOMUX_8WIDTH_2BIT,
					     IOMUX_8WIDTH_2BIT),
	PIN_BANK_IOMUX_FLAGS(1, 32, "gpio1", IOMUX_8WIDTH_2BIT,
					     IOMUX_8WIDTH_2BIT,
					     IOMUX_8WIDTH_2BIT,
					     IOMUX_8WIDTH_2BIT),
	PIN_BANK_IOMUX_FLAGS(2, 32, "gpio2", IOMUX_8WIDTH_2BIT,
					     IOMUX_8WIDTH_2BIT,
					     IOMUX_8WIDTH_2BIT,
					     IOMUX_8WIDTH_2BIT),
	PIN_BANK_IOMUX_FLAGS(3, 32, "gpio3", IOMUX_8WIDTH_2BIT,
					     IOMUX_8WIDTH_2BIT,
					     IOMUX_8WIDTH_2BIT,
					     IOMUX_8WIDTH_2BIT),
	PIN_BANK_IOMUX_FLAGS(4, 32, "gpio4", IOMUX_8WIDTH_2BIT,
					     IOMUX_8WIDTH_2BIT,
					     IOMUX_8WIDTH_2BIT,
					     IOMUX_8WIDTH_2BIT),
};

static struct rockchip_pin_ctrl rk3308_pin_ctrl = {
		.pin_banks		= rk3308_pin_banks,
		.nr_banks		= ARRAY_SIZE(rk3308_pin_banks),
		.nr_pins		= 160,
		.label			= "RK3308-GPIO",
		.type			= RK3308,
		.grf_mux_offset		= 0x0,
		.iomux_recalced		= rk3308_mux_recalced_data,
		.niomux_recalced	= ARRAY_SIZE(rk3308_mux_recalced_data),
		.iomux_routes		= rk3308_mux_route_data,
		.niomux_routes		= ARRAY_SIZE(rk3308_mux_route_data),
		.pull_calc_reg		= rk3308_calc_pull_reg_and_bit,
		.drv_calc_reg		= rk3308_calc_drv_reg_and_bit,
		.schmitt_calc_reg	= rk3308_calc_schmitt_reg_and_bit,
};

static const struct rockchip_pin_ctrl rk3308b_pin_ctrl = {
	.pin_banks		= rk3308_pin_banks,
	.nr_banks		= ARRAY_SIZE(rk3308_pin_banks),
	.nr_pins		= 160,
	.label			= "RK3308-GPIO",
	.type			= RK3308,
	.grf_mux_offset		= 0x0,
	.iomux_recalced		= rk3308b_mux_recalced_data,
	.niomux_recalced	= ARRAY_SIZE(rk3308b_mux_recalced_data),
	.iomux_routes		= rk3308b_mux_route_data,
	.niomux_routes		= ARRAY_SIZE(rk3308b_mux_route_data),
	.soc_data_init		= rk3308b_soc_data_init,
	.pull_calc_reg		= rk3308_calc_pull_reg_and_bit,
	.drv_calc_reg		= rk3308_calc_drv_reg_and_bit,
	.schmitt_calc_reg	= rk3308_calc_schmitt_reg_and_bit,
};

static struct rockchip_pin_bank rk3328_pin_banks[] = {
	PIN_BANK_IOMUX_FLAGS(0, 32, "gpio0", 0, 0, 0, 0),
	PIN_BANK_IOMUX_FLAGS(1, 32, "gpio1", 0, 0, 0, 0),
	PIN_BANK_IOMUX_FLAGS(2, 32, "gpio2", 0,
			     IOMUX_WIDTH_3BIT,
			     IOMUX_WIDTH_3BIT,
			     0),
	PIN_BANK_IOMUX_FLAGS(3, 32, "gpio3",
			     IOMUX_WIDTH_3BIT,
			     IOMUX_WIDTH_3BIT,
			     0,
			     0),
};

static const struct rockchip_pin_ctrl rk3328_pin_ctrl = {
	.pin_banks		= rk3328_pin_banks,
	.nr_banks		= ARRAY_SIZE(rk3328_pin_banks),
	.nr_pins		= 128,
	.label			= "RK3328-GPIO",
	.type			= RK3288,
	.grf_mux_offset		= 0x0,
	.iomux_recalced		= rk3328_mux_recalced_data,
	.niomux_recalced	= ARRAY_SIZE(rk3328_mux_recalced_data),
	.iomux_routes		= rk3328_mux_route_data,
	.niomux_routes		= ARRAY_SIZE(rk3328_mux_route_data),
	.pull_calc_reg		= rk3228_calc_pull_reg_and_bit,
	.drv_calc_reg		= rk3228_calc_drv_reg_and_bit,
	.schmitt_calc_reg	= rk3328_calc_schmitt_reg_and_bit,
};

static struct rockchip_pin_bank rk3368_pin_banks[] = {
	PIN_BANK_IOMUX_FLAGS(0, 32, "gpio0", IOMUX_SOURCE_PMU,
					     IOMUX_SOURCE_PMU,
					     IOMUX_SOURCE_PMU,
					     IOMUX_SOURCE_PMU
			    ),
	PIN_BANK(1, 32, "gpio1"),
	PIN_BANK(2, 32, "gpio2"),
	PIN_BANK(3, 32, "gpio3"),
};

static const struct rockchip_pin_ctrl rk3368_pin_ctrl = {
	.pin_banks		= rk3368_pin_banks,
	.nr_banks		= ARRAY_SIZE(rk3368_pin_banks),
	.nr_pins		= 128,
	.label			= "RK3368-GPIO",
	.type			= RK3368,
	.grf_mux_offset		= 0x0,
	.pmu_mux_offset		= 0x0,
	.pull_calc_reg		= rk3368_calc_pull_reg_and_bit,
	.drv_calc_reg		= rk3368_calc_drv_reg_and_bit,
};

static struct rockchip_pin_bank rk3399_pin_banks[] = {
	PIN_BANK_IOMUX_FLAGS_DRV_FLAGS_OFFSET_PULL_FLAGS(0, 32, "gpio0",
							 IOMUX_SOURCE_PMU,
							 IOMUX_SOURCE_PMU,
							 IOMUX_SOURCE_PMU,
							 IOMUX_SOURCE_PMU,
							 DRV_TYPE_IO_1V8_ONLY,
							 DRV_TYPE_IO_1V8_ONLY,
							 DRV_TYPE_IO_DEFAULT,
							 DRV_TYPE_IO_DEFAULT,
							 0x80,
							 0x88,
							 -1,
							 -1,
							 PULL_TYPE_IO_1V8_ONLY,
							 PULL_TYPE_IO_1V8_ONLY,
							 PULL_TYPE_IO_DEFAULT,
							 PULL_TYPE_IO_DEFAULT
							),
	PIN_BANK_IOMUX_DRV_FLAGS_OFFSET(1, 32, "gpio1", IOMUX_SOURCE_PMU,
					IOMUX_SOURCE_PMU,
					IOMUX_SOURCE_PMU,
					IOMUX_SOURCE_PMU,
					DRV_TYPE_IO_1V8_OR_3V0,
					DRV_TYPE_IO_1V8_OR_3V0,
					DRV_TYPE_IO_1V8_OR_3V0,
					DRV_TYPE_IO_1V8_OR_3V0,
					0xa0,
					0xa8,
					0xb0,
					0xb8
					),
	PIN_BANK_DRV_FLAGS_PULL_FLAGS(2, 32, "gpio2", DRV_TYPE_IO_1V8_OR_3V0,
				      DRV_TYPE_IO_1V8_OR_3V0,
				      DRV_TYPE_IO_1V8_ONLY,
				      DRV_TYPE_IO_1V8_ONLY,
				      PULL_TYPE_IO_DEFAULT,
				      PULL_TYPE_IO_DEFAULT,
				      PULL_TYPE_IO_1V8_ONLY,
				      PULL_TYPE_IO_1V8_ONLY
				      ),
	PIN_BANK_DRV_FLAGS(3, 32, "gpio3", DRV_TYPE_IO_3V3_ONLY,
			   DRV_TYPE_IO_3V3_ONLY,
			   DRV_TYPE_IO_3V3_ONLY,
			   DRV_TYPE_IO_1V8_OR_3V0
			   ),
	PIN_BANK_DRV_FLAGS(4, 32, "gpio4", DRV_TYPE_IO_1V8_OR_3V0,
			   DRV_TYPE_IO_1V8_3V0_AUTO,
			   DRV_TYPE_IO_1V8_OR_3V0,
			   DRV_TYPE_IO_1V8_OR_3V0
			   ),
};

static const struct rockchip_pin_ctrl rk3399_pin_ctrl = {
	.pin_banks		= rk3399_pin_banks,
	.nr_banks		= ARRAY_SIZE(rk3399_pin_banks),
	.nr_pins		= 160,
	.label			= "RK3399-GPIO",
	.type			= RK3399,
	.grf_mux_offset		= 0xe000,
	.pmu_mux_offset		= 0x0,
	.grf_drv_offset		= 0xe100,
	.pmu_drv_offset		= 0x80,
	.iomux_routes		= rk3399_mux_route_data,
	.niomux_routes		= ARRAY_SIZE(rk3399_mux_route_data),
	.pull_calc_reg		= rk3399_calc_pull_reg_and_bit,
	.drv_calc_reg		= rk3399_calc_drv_reg_and_bit,
};

static const struct udevice_id rockchip_pinctrl_dt_match[] = {
	{ .compatible = "rockchip,px30-pinctrl",
		.data = (ulong)&px30_pin_ctrl },
	{ .compatible = "rockchip,rv1108-pinctrl",
		.data = (ulong)&rv1108_pin_ctrl },
	{ .compatible = "rockchip,rv1126-pinctrl-legency",
		.data = (ulong)&rv1126_pin_ctrl },
	{ .compatible = "rockchip,rk1808-pinctrl",
		.data = (ulong)&rk1808_pin_ctrl },
	{ .compatible = "rockchip,rk2928-pinctrl",
		.data = (ulong)&rk2928_pin_ctrl },
	{ .compatible = "rockchip,rk3036-pinctrl",
		.data = (ulong)&rk3036_pin_ctrl },
	{ .compatible = "rockchip,rk3066a-pinctrl",
		.data = (ulong)&rk3066a_pin_ctrl },
	{ .compatible = "rockchip,rk3066b-pinctrl",
		.data = (ulong)&rk3066b_pin_ctrl },
	{ .compatible = "rockchip,rk3128-pinctrl",
		.data = (ulong)&rk3128_pin_ctrl },
	{ .compatible = "rockchip,rk3188-pinctrl",
		.data = (ulong)&rk3188_pin_ctrl },
	{ .compatible = "rockchip,rk3228-pinctrl",
		.data = (ulong)&rk3228_pin_ctrl },
	{ .compatible = "rockchip,rk3288-pinctrl",
		.data = (ulong)&rk3288_pin_ctrl },
	{ .compatible = "rockchip,rk3308-pinctrl",
		.data = (ulong)&rk3308_pin_ctrl },
	{ .compatible = "rockchip,rk3328-pinctrl",
		.data = (ulong)&rk3328_pin_ctrl },
	{ .compatible = "rockchip,rk3368-pinctrl",
		.data = (ulong)&rk3368_pin_ctrl },
	{ .compatible = "rockchip,rk3399-pinctrl",
		.data = (ulong)&rk3399_pin_ctrl },
	{},
};

U_BOOT_DRIVER(pinctrl_rockchip) = {
	.name		= "rockchip_pinctrl",
	.id		= UCLASS_PINCTRL,
	.of_match	= rockchip_pinctrl_dt_match,
	.priv_auto_alloc_size = sizeof(struct rockchip_pinctrl_priv),
	.ops		= &rockchip_pinctrl_ops,
#if !CONFIG_IS_ENABLED(OF_PLATDATA)
	.bind		= dm_scan_fdt_dev,
#endif
	.probe		= rockchip_pinctrl_probe,
};
