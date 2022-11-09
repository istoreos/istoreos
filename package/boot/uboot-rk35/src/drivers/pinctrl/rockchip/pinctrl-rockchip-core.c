// SPDX-License-Identifier: GPL-2.0+
/*
 * (C) Copyright 2019 Rockchip Electronics Co., Ltd
 */

#include <common.h>
#include <dm.h>
#include <dm/pinctrl.h>
#include <regmap.h>
#include <syscon.h>
#include <fdtdec.h>

#include "pinctrl-rockchip.h"

#define MAX_ROCKCHIP_PINS_ENTRIES	30
#define MAX_ROCKCHIP_GPIO_PER_BANK      32
#define RK_FUNC_GPIO                    0

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

void rockchip_get_recalced_mux(struct rockchip_pin_bank *bank, int pin,
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
		if (data->bank_num == bank->bank_num &&
		    data->pin == pin && data->func == mux)
			break;
	}

	if (i >= ctrl->niomux_routes)
		return ROUTE_TYPE_INVALID;

	*reg = data->route_offset;
	*value = data->route_val;

	return data->route_type;
}

int rockchip_get_mux_data(int mux_type, int pin, u8 *bit, int *mask)
{
	int offset = 0;

	if (mux_type & IOMUX_WIDTH_4BIT) {
		if ((pin % 8) >= 4)
			offset = 0x4;
		*bit = (pin % 4) * 4;
		*mask = 0xf;
	} else if (mux_type & IOMUX_WIDTH_3BIT) {
		/*
		 * pin0 ~ pin4 are at first register, and
		 * pin5 ~ pin7 are at second register.
		 */
		if ((pin % 8) >= 5)
			offset = 0x4;
		*bit = (pin % 8 % 5) * 3;
		*mask = 0x7;
	} else {
		*bit = (pin % 8) * 2;
		*mask = 0x3;
	}

	return offset;
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
		return -ENOTSUPP;
	}

	if (bank->iomux[iomux_num].type & IOMUX_GPIO_ONLY)
		return RK_FUNC_GPIO;

	regmap = (bank->iomux[iomux_num].type & IOMUX_SOURCE_PMU)
				? priv->regmap_pmu : priv->regmap_base;

	/* get basic quadrupel of mux registers and the correct reg inside */
	mux_type = bank->iomux[iomux_num].type;
	reg = bank->iomux[iomux_num].offset;
	reg += rockchip_get_mux_data(mux_type, pin, &bit, &mask);

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
		return -ENOTSUPP;
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
	struct rockchip_pin_ctrl *ctrl = priv->ctrl;
	int iomux_num = (pin / 8);
	int ret;

	ret = rockchip_verify_mux(bank, pin, mux);
	if (ret < 0)
		return ret == -ENOTSUPP ? 0 : ret;

	if (bank->iomux[iomux_num].type & IOMUX_GPIO_ONLY)
		return 0;

	debug("setting mux of GPIO%d-%d to %d\n", bank->bank_num, pin, mux);

	if (!ctrl->set_mux)
		return -ENOTSUPP;

	ret = ctrl->set_mux(bank, pin, mux);
	if (ret)
		return ret;

	if (bank->route_mask & BIT(pin)) {
		struct regmap *regmap;
		u32 route_reg = 0, route_val = 0;

		ret = rockchip_get_mux_route(bank, pin, mux,
					     &route_reg, &route_val);
		switch (ret) {
		case ROUTE_TYPE_DEFAULT:
			if (bank->iomux[iomux_num].type & IOMUX_SOURCE_PMU)
				regmap = priv->regmap_pmu;
			else if (bank->iomux[iomux_num].type & IOMUX_L_SOURCE_PMU)
				regmap = (pin % 8 < 4) ? priv->regmap_pmu : priv->regmap_base;
			else
				regmap = priv->regmap_base;

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

	return 0;
}

static int rockchip_perpin_drv_list[DRV_TYPE_MAX][8] = {
	{ 2, 4, 8, 12, -1, -1, -1, -1 },
	{ 3, 6, 9, 12, -1, -1, -1, -1 },
	{ 5, 10, 15, 20, -1, -1, -1, -1 },
	{ 4, 6, 8, 10, 12, 14, 16, 18 },
	{ 4, 7, 10, 13, 16, 19, 22, 26 }
};

int rockchip_translate_drive_value(int type, int strength)
{
	int i, ret;

	ret = -EINVAL;
	for (i = 0; i < ARRAY_SIZE(rockchip_perpin_drv_list[type]); i++) {
		if (rockchip_perpin_drv_list[type][i] == strength) {
			ret = i;
			break;
		} else if (rockchip_perpin_drv_list[type][i] < 0) {
			ret = rockchip_perpin_drv_list[type][i];
			break;
		}
	}

	return ret;
}

static int rockchip_set_drive_perpin(struct rockchip_pin_bank *bank,
				     int pin_num, int strength)
{
	struct rockchip_pinctrl_priv *priv = bank->priv;
	struct rockchip_pin_ctrl *ctrl = priv->ctrl;

	debug("setting drive of GPIO%d-%d to %d\n", bank->bank_num,
	      pin_num, strength);

	if (!ctrl->set_drive)
		return -ENOTSUPP;

	return ctrl->set_drive(bank, pin_num, strength);
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

int rockchip_translate_pull_value(int type, int pull)
{
	int i, ret;

	ret = -EINVAL;
	for (i = 0; i < ARRAY_SIZE(rockchip_pull_list[type]);
		i++) {
		if (rockchip_pull_list[type][i] == pull) {
			ret = i;
			break;
		}
	}

	return ret;
}

static int rockchip_set_pull(struct rockchip_pin_bank *bank,
			     int pin_num, int pull)
{
	struct rockchip_pinctrl_priv *priv = bank->priv;
	struct rockchip_pin_ctrl *ctrl = priv->ctrl;

	debug("setting pull of GPIO%d-%d to %d\n", bank->bank_num,
	      pin_num, pull);

	if (!ctrl->set_pull)
		return -ENOTSUPP;

	return ctrl->set_pull(bank, pin_num, pull);
}

static int rockchip_set_schmitt(struct rockchip_pin_bank *bank,
				int pin_num, int enable)
{
	struct rockchip_pinctrl_priv *priv = bank->priv;
	struct rockchip_pin_ctrl *ctrl = priv->ctrl;

	debug("setting input schmitt of GPIO%d-%d to %d\n", bank->bank_num,
	      pin_num, enable);

	if (!ctrl->set_schmitt)
		return -ENOTSUPP;

	return ctrl->set_schmitt(bank, pin_num, enable);
}

/* set the pin config settings for a specified pin */
static int rockchip_pinconf_set(struct rockchip_pin_bank *bank,
				u32 pin, u32 param, u32 arg)
{
	int rc;

	switch (param) {
	case PIN_CONFIG_BIAS_DISABLE:
	case PIN_CONFIG_BIAS_PULL_UP:
	case PIN_CONFIG_BIAS_PULL_DOWN:
	case PIN_CONFIG_BIAS_PULL_PIN_DEFAULT:
	case PIN_CONFIG_BIAS_BUS_HOLD:
		rc = rockchip_set_pull(bank, pin, param);
		if (rc)
			return rc;
		break;

	case PIN_CONFIG_DRIVE_STRENGTH:
		rc = rockchip_set_drive_perpin(bank, pin, arg);
		if (rc < 0)
			return rc;
		break;

	case PIN_CONFIG_INPUT_SCHMITT_ENABLE:
		rc = rockchip_set_schmitt(bank, pin, arg);
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
	{ "bias-pull-pin-default", PIN_CONFIG_BIAS_PULL_PIN_DEFAULT, 1 },
	{ "drive-strength", PIN_CONFIG_DRIVE_STRENGTH, 0 },
	{ "input-schmitt-disable", PIN_CONFIG_INPUT_SCHMITT_ENABLE, 0 },
	{ "input-schmitt-enable", PIN_CONFIG_INPUT_SCHMITT_ENABLE, 1 },
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
#if CONFIG_IS_ENABLED(OF_LIVE)
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
#if CONFIG_IS_ENABLED(OF_LIVE)
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

const struct pinctrl_ops rockchip_pinctrl_ops = {
	.get_pins_count			= rockchip_pinctrl_get_pins_count,
	.set_state			= rockchip_pinctrl_set_state,
	.get_gpio_mux			= rockchip_pinctrl_get_gpio_mux,
};

/* retrieve the soc specific data */
static struct rockchip_pin_ctrl *rockchip_pinctrl_get_soc_data(struct udevice *dev)
{
	struct rockchip_pinctrl_priv *priv = dev_get_priv(dev);
	struct rockchip_pin_ctrl *ctrl =
			(struct rockchip_pin_ctrl *)dev_get_driver_data(dev);
	struct rockchip_pin_bank *bank;
	int grf_offs, pmu_offs, drv_grf_offs, drv_pmu_offs, i, j;
	u32 nr_pins;

	grf_offs = ctrl->grf_mux_offset;
	pmu_offs = ctrl->pmu_mux_offset;
	drv_pmu_offs = ctrl->pmu_drv_offset;
	drv_grf_offs = ctrl->grf_drv_offset;
	bank = ctrl->pin_banks;

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

			if (bank_pins >= nr_pins)
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

int rockchip_pinctrl_probe(struct udevice *dev)
{
	struct rockchip_pinctrl_priv *priv = dev_get_priv(dev);
	struct rockchip_pin_ctrl *ctrl;
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

	priv->ctrl = ctrl;
	return 0;
}
