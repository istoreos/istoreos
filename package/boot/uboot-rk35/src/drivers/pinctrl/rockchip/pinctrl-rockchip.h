/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * (C) Copyright 2019 Rockchip Electronics Co., Ltd
 */

#ifndef __DRIVERS_PINCTRL_ROCKCHIP_H
#define __DRIVERS_PINCTRL_ROCKCHIP_H

#include <dt-bindings/pinctrl/rockchip.h>
#include <linux/types.h>

#define RK_GPIO0_A0	0
#define RK_GPIO0_A1	1
#define RK_GPIO0_A2	2
#define RK_GPIO0_A3	3
#define RK_GPIO0_A4	4
#define RK_GPIO0_A5	5
#define RK_GPIO0_A6	6
#define RK_GPIO0_A7	7
#define RK_GPIO0_B0	8
#define RK_GPIO0_B1	9
#define RK_GPIO0_B2	10
#define RK_GPIO0_B3	11
#define RK_GPIO0_B4	12
#define RK_GPIO0_B5	13
#define RK_GPIO0_B6	14
#define RK_GPIO0_B7	15
#define RK_GPIO0_C0	16
#define RK_GPIO0_C1	17
#define RK_GPIO0_C2	18
#define RK_GPIO0_C3	19
#define RK_GPIO0_C4	20
#define RK_GPIO0_C5	21
#define RK_GPIO0_C6	22
#define RK_GPIO0_C7	23
#define RK_GPIO0_D0	24
#define RK_GPIO0_D1	25
#define RK_GPIO0_D2	26
#define RK_GPIO0_D3	27
#define RK_GPIO0_D4	28
#define RK_GPIO0_D5	29
#define RK_GPIO0_D6	30
#define RK_GPIO0_D7	31

#define RK_GPIO1_A0	32
#define RK_GPIO1_A1	33
#define RK_GPIO1_A2	34
#define RK_GPIO1_A3	35
#define RK_GPIO1_A4	36
#define RK_GPIO1_A5	37
#define RK_GPIO1_A6	38
#define RK_GPIO1_A7	39
#define RK_GPIO1_B0	40
#define RK_GPIO1_B1	41
#define RK_GPIO1_B2	42
#define RK_GPIO1_B3	43
#define RK_GPIO1_B4	44
#define RK_GPIO1_B5	45
#define RK_GPIO1_B6	46
#define RK_GPIO1_B7	47
#define RK_GPIO1_C0	48
#define RK_GPIO1_C1	49
#define RK_GPIO1_C2	50
#define RK_GPIO1_C3	51
#define RK_GPIO1_C4	52
#define RK_GPIO1_C5	53
#define RK_GPIO1_C6	54
#define RK_GPIO1_C7	55
#define RK_GPIO1_D0	56
#define RK_GPIO1_D1	57
#define RK_GPIO1_D2	58
#define RK_GPIO1_D3	59
#define RK_GPIO1_D4	60
#define RK_GPIO1_D5	61
#define RK_GPIO1_D6	62
#define RK_GPIO1_D7	63

#define RK_GPIO2_A0	64
#define RK_GPIO2_A1	65
#define RK_GPIO2_A2	66
#define RK_GPIO2_A3	67
#define RK_GPIO2_A4	68
#define RK_GPIO2_A5	69
#define RK_GPIO2_A6	70
#define RK_GPIO2_A7	71
#define RK_GPIO2_B0	72
#define RK_GPIO2_B1	73
#define RK_GPIO2_B2	74
#define RK_GPIO2_B3	75
#define RK_GPIO2_B4	76
#define RK_GPIO2_B5	77
#define RK_GPIO2_B6	78
#define RK_GPIO2_B7	79
#define RK_GPIO2_C0	80
#define RK_GPIO2_C1	81
#define RK_GPIO2_C2	82
#define RK_GPIO2_C3	83
#define RK_GPIO2_C4	84
#define RK_GPIO2_C5	85
#define RK_GPIO2_C6	86
#define RK_GPIO2_C7	87
#define RK_GPIO2_D0	88
#define RK_GPIO2_D1	89
#define RK_GPIO2_D2	90
#define RK_GPIO2_D3	91
#define RK_GPIO2_D4	92
#define RK_GPIO2_D5	93
#define RK_GPIO2_D6	94
#define RK_GPIO2_D7	95

#define RK_GPIO3_A0	96
#define RK_GPIO3_A1	97
#define RK_GPIO3_A2	98
#define RK_GPIO3_A3	99
#define RK_GPIO3_A4	100
#define RK_GPIO3_A5	101
#define RK_GPIO3_A6	102
#define RK_GPIO3_A7	103
#define RK_GPIO3_B0	104
#define RK_GPIO3_B1	105
#define RK_GPIO3_B2	106
#define RK_GPIO3_B3	107
#define RK_GPIO3_B4	108
#define RK_GPIO3_B5	109
#define RK_GPIO3_B6	110
#define RK_GPIO3_B7	111
#define RK_GPIO3_C0	112
#define RK_GPIO3_C1	113
#define RK_GPIO3_C2	114
#define RK_GPIO3_C3	115
#define RK_GPIO3_C4	116
#define RK_GPIO3_C5	117
#define RK_GPIO3_C6	118
#define RK_GPIO3_C7	119
#define RK_GPIO3_D0	120
#define RK_GPIO3_D1	121
#define RK_GPIO3_D2	122
#define RK_GPIO3_D3	123
#define RK_GPIO3_D4	124
#define RK_GPIO3_D5	125
#define RK_GPIO3_D6	126
#define RK_GPIO3_D7	127

#define RK_GPIO4_A0	128
#define RK_GPIO4_A1	129
#define RK_GPIO4_A2	130
#define RK_GPIO4_A3	131
#define RK_GPIO4_A4	132
#define RK_GPIO4_A5	133
#define RK_GPIO4_A6	134
#define RK_GPIO4_A7	135
#define RK_GPIO4_B0	136
#define RK_GPIO4_B1	137
#define RK_GPIO4_B2	138
#define RK_GPIO4_B3	139
#define RK_GPIO4_B4	140
#define RK_GPIO4_B5	141
#define RK_GPIO4_B6	142
#define RK_GPIO4_B7	143
#define RK_GPIO4_C0	144
#define RK_GPIO4_C1	145
#define RK_GPIO4_C2	146
#define RK_GPIO4_C3	147
#define RK_GPIO4_C4	148
#define RK_GPIO4_C5	149
#define RK_GPIO4_C6	150
#define RK_GPIO4_C7	151
#define RK_GPIO4_D0	152
#define RK_GPIO4_D1	153
#define RK_GPIO4_D2	154
#define RK_GPIO4_D3	155
#define RK_GPIO4_D4	156
#define RK_GPIO4_D5	157
#define RK_GPIO4_D6	158
#define RK_GPIO4_D7	159

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
 * Defined some common pins constants
 */
#define ROCKCHIP_PULL_BITS_PER_PIN	2
#define ROCKCHIP_PULL_PINS_PER_REG	8
#define ROCKCHIP_PULL_BANK_STRIDE	16
#define ROCKCHIP_DRV_BITS_PER_PIN	2
#define ROCKCHIP_DRV_PINS_PER_REG	8
#define ROCKCHIP_DRV_BANK_STRIDE	16
#define ROCKCHIP_DRV_3BITS_PER_PIN	3

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

#define PIN_BANK_IOMUX_FLAGS_PULL_FLAGS(id, pins, label, iom0, iom1,	\
					iom2, iom3, pull0, pull1,	\
					pull2, pull3)			\
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
		.pull_type[0] = pull0,					\
		.pull_type[1] = pull1,					\
		.pull_type[2] = pull2,					\
		.pull_type[3] = pull3,					\
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

#define RK3588_PIN_BANK_FLAGS(ID, PIN, LABEL, M, P)			\
	PIN_BANK_IOMUX_FLAGS_PULL_FLAGS(ID, PIN, LABEL, M, M, M, M, P, P, P, P)

/**
 * struct rockchip_mux_recalced_data: recalculate a pin iomux data.
 * @num: bank number.
 * @pin: pin number.
 * @reg: register offset.
 * @bit: index at register.
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
 * struct rockchip_mux_route_data: route a pin iomux data.
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
	int				grf_mux_offset;
	int				pmu_mux_offset;
	int				grf_drv_offset;
	int				pmu_drv_offset;
	struct rockchip_mux_recalced_data *iomux_recalced;
	u32				niomux_recalced;
	struct rockchip_mux_route_data *iomux_routes;
	u32				niomux_routes;

	int	(*set_mux)(struct rockchip_pin_bank *bank,
			   int pin, int mux);
	int	(*set_pull)(struct rockchip_pin_bank *bank,
			    int pin_num, int pull);
	int	(*set_drive)(struct rockchip_pin_bank *bank,
			     int pin_num, int strength);
	int	(*set_schmitt)(struct rockchip_pin_bank *bank,
			       int pin_num, int enable);
};

/**
 */
struct rockchip_pinctrl_priv {
	struct rockchip_pin_ctrl	*ctrl;
	struct regmap			*regmap_base;
	struct regmap			*regmap_pmu;
};

extern const struct pinctrl_ops rockchip_pinctrl_ops;
int rockchip_pinctrl_probe(struct udevice *dev);
void rockchip_get_recalced_mux(struct rockchip_pin_bank *bank, int pin,
			       int *reg, u8 *bit, int *mask);
int rockchip_get_mux_data(int mux_type, int pin, u8 *bit, int *mask);
int rockchip_translate_drive_value(int type, int strength);
int rockchip_translate_pull_value(int type, int pull);

#endif /* __DRIVERS_PINCTRL_ROCKCHIP_H */
