/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * Copyright (c) 2020 Rockchip Electronics Co. Ltd.
 */

#ifndef _PINCTRL_ROCKCHIP_H
#define _PINCTRL_ROCKCHIP_H

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
	RK3568,
};

struct rockchip_gpio_regs {
	u32 port_dr;
	u32 port_ddr;
	u32 int_en;
	u32 int_mask;
	u32 int_type;
	u32 int_polarity;
	u32 int_bothedge;
	u32 int_status;
	u32 int_rawstatus;
	u32 debounce;
	u32 dbclk_div_en;
	u32 dbclk_div_con;
	u32 port_eoi;
	u32 ext_port;
	u32 version_id;
};

/**
 * @type: iomux variant using IOMUX_* constants
 * @offset: if initialized to -1 it will be autocalculated, by specifying
 *	    an initial offset value the relevant source offset can be reset
 *	    to a new value for autocalculating the following iomux registers.
 */
struct rockchip_iomux {
	int type;
	int offset;
};

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

/**
 * enum type index corresponding to rockchip_pull_list arrays index.
 */
enum rockchip_pin_pull_type {
	PULL_TYPE_IO_DEFAULT = 0,
	PULL_TYPE_IO_1V8_ONLY,
	PULL_TYPE_MAX
};

enum rockchip_mux_route_location {
	ROCKCHIP_ROUTE_SAME = 0,
	ROCKCHIP_ROUTE_PMU,
	ROCKCHIP_ROUTE_GRF,
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
 * @dev: device of the gpio bank
 * @reg_base: register base of the gpio bank
 * @reg_pull: optional separate register for additional pull settings
 * @clk: clock of the gpio bank
 * @db_clk: clock of the gpio debounce
 * @irq: interrupt of the gpio bank
 * @saved_masks: Saved content of GPIO_INTEN at suspend time.
 * @pin_base: first pin number
 * @nr_pins: number of pins in this bank
 * @name: name of the bank
 * @bank_num: number of the bank, to account for holes
 * @iomux: array describing the 4 iomux sources of the bank
 * @drv: array describing the 4 drive strength sources of the bank
 * @pull_type: array describing the 4 pull type sources of the bank
 * @of_node: dt node of this bank
 * @drvdata: common pinctrl basedata
 * @domain: irqdomain of the gpio bank
 * @gpio_chip: gpiolib chip
 * @grange: gpio range
 * @slock: spinlock for the gpio bank
 * @route_mask: bits describing the routing pins of per bank
 */
struct rockchip_pin_bank {
	struct device *dev;

	void __iomem			*reg_base;
	struct regmap			*regmap_pull;
	struct clk			*clk;
	struct clk			*db_clk;
	int				irq;
	u32				saved_masks;
	u32				pin_base;
	u8				nr_pins;
	char				*name;
	u8				bank_num;
	struct rockchip_iomux		iomux[4];
	struct rockchip_drv		drv[4];
	enum rockchip_pin_pull_type	pull_type[4];
	struct device_node		*of_node;
	struct rockchip_pinctrl		*drvdata;
	struct irq_domain		*domain;
	struct gpio_chip		gpio_chip;
	struct pinctrl_gpio_range	grange;
	raw_spinlock_t			slock;
	const struct rockchip_gpio_regs	*gpio_regs;
	u32				gpio_type;
	u32				toggle_edge_mode;
	u32				recalced_mask;
	u32				route_mask;
};

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
 * @route_location: the mux route location (same, pmu, grf).
 * @route_offset: the max pin.
 * @route_val: the register offset.
 */
struct rockchip_mux_route_data {
	u8 bank_num;
	u8 pin;
	u8 func;
	enum rockchip_mux_route_location route_location;
	u32 route_offset;
	u32 route_val;
};

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

	int	(*ctrl_data_re_init)(struct rockchip_pin_ctrl *ctrl);

	int	(*soc_data_init)(struct rockchip_pinctrl *info);

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

struct rockchip_pin_config {
	unsigned int		func;
	unsigned long		*configs;
	unsigned int		nconfigs;
};

/**
 * struct rockchip_pin_group: represent group of pins of a pinmux function.
 * @name: name of the pin group, used to lookup the group.
 * @pins: the pins included in this group.
 * @npins: number of pins included in this group.
 * @func: the mux function number to be programmed when selected.
 * @configs: the config values to be set for each pin
 * @nconfigs: number of configs for each pin
 */
struct rockchip_pin_group {
	const char			*name;
	unsigned int			npins;
	unsigned int			*pins;
	struct rockchip_pin_config	*data;
};

/**
 * struct rockchip_pmx_func: represent a pin function.
 * @name: name of the pin function, used to lookup the function.
 * @groups: one or more names of pin groups that provide this function.
 * @num_groups: number of groups included in @groups.
 */
struct rockchip_pmx_func {
	const char		*name;
	const char		**groups;
	u8			ngroups;
};

struct rockchip_pinctrl {
	struct regmap			*regmap_base;
	int				reg_size;
	struct regmap			*regmap_pull;
	struct regmap			*regmap_pmu;
	struct device			*dev;
	struct rockchip_pin_ctrl	*ctrl;
	struct pinctrl_desc		pctl;
	struct pinctrl_dev		*pctl_dev;
	struct rockchip_pin_group	*groups;
	unsigned int			ngroups;
	struct rockchip_pmx_func	*functions;
	unsigned int			nfunctions;
};

#endif
