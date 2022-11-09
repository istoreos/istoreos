/* SPDX-License-Identifier:     GPL-2.0+ */
/*
 * (C) Copyright 2018 Rockchip Electronics Co., Ltd
 */

#include <common.h>
#include <dm.h>
#include <dm/of_access.h>
#include <regmap.h>
#include <syscon.h>
#include <asm/arch-rockchip/clock.h>
#include <fdtdec.h>
#include <linux/compat.h>
#include <linux/err.h>
#include <power/regulator.h>

#define MAX_SUPPLIES		16

/*
 * The max voltage for 1.8V and 3.3V come from the Rockchip datasheet under
 * "Recommended Operating Conditions" for "Digital GPIO".   When the typical
 * is 3.3V the max is 3.6V.  When the typical is 1.8V the max is 1.98V.
 *
 * They are used like this:
 * - If the voltage on a rail is above the "1.8" voltage (1.98V) we'll tell the
 *   SoC we're at 3.3.
 * - If the voltage on a rail is above the "3.3" voltage (3.6V) we'll consider
 *   that to be an error.
 */
#define MAX_VOLTAGE_1_8	1980000
#define MAX_VOLTAGE_3_3	3600000

#define PX30_IO_VSEL			0x180
#define PX30_IO_VSEL_VCCIO6_SRC		BIT(0)
#define PX30_IO_VSEL_VCCIO6_SUPPLY_NUM	1

#define RK3288_SOC_CON2			0x24c
#define RK3288_SOC_CON2_FLASH0		BIT(7)
#define RK3288_SOC_FLASH_SUPPLY_NUM	2

#define RK3308_SOC_CON0			0x300
#define RK3308_SOC_CON0_VCCIO3		BIT(8)
#define RK3308_SOC_VCCIO3_SUPPLY_NUM	3

#define RK3328_SOC_CON4			0x410
#define RK3328_SOC_CON4_VCCIO2		BIT(7)
#define RK3328_SOC_VCCIO2_SUPPLY_NUM	1

#define RK3366_SOC_CON6			0x418
#define RK3366_SOC_CON6_FLASH0		BIT(14)
#define RK3366_SOC_FLASH_SUPPLY_NUM	2

#define RK3368_SOC_CON15		0x43c
#define RK3368_SOC_CON15_FLASH0		BIT(14)
#define RK3368_SOC_FLASH_SUPPLY_NUM	2

#define RK3399_PMUGRF_CON0		0x180
#define RK3399_PMUGRF_CON0_VSEL		BIT(8)
#define RK3399_PMUGRF_VSEL_SUPPLY_NUM	9

#define RK3568_PMU_GRF_IO_VSEL0		(0x0140)
#define RK3568_PMU_GRF_IO_VSEL1		(0x0144)
#define RK3568_PMU_GRF_IO_VSEL2		(0x0148)

#define RV1126_PMU_GRF_IO_RETENTION	(0x0144)

struct rockchip_iodomain_priv;

/**
 * @supplies: voltage settings matching the register bits.
 */
struct rockchip_iodomain_soc_data {
	int grf_offset;
	const char *supply_names[MAX_SUPPLIES];
	void (*init)(struct rockchip_iodomain_priv *iod);
};

struct rockchip_iodomain_supply {
	struct rockchip_iodomain_priv *iod;
	struct udevice *reg;
	int idx;
};

struct rockchip_iodomain_priv {
	struct regmap *regmap_base;
	struct rockchip_iodomain_soc_data *sdata;
	struct rockchip_iodomain_supply supplies[MAX_SUPPLIES];
	int (*write)(struct rockchip_iodomain_supply *supply, int uV);
};

static int rockchip_ofdata_to_platdata(struct udevice *dev)
{
	struct rockchip_iodomain_priv *priv = dev_get_priv(dev);
	struct syscon_uc_info *syscon_priv;
	struct regmap *regmap;

	syscon_priv = dev_get_uclass_priv(dev_get_parent(dev));
	regmap = syscon_priv->regmap;
	if (IS_ERR(regmap))
		return PTR_ERR(regmap);

	priv->regmap_base = regmap;

	return 0;
}

static int rk3568_pmu_iodomain_write(struct rockchip_iodomain_supply *supply,
				     int uV)
{
	struct rockchip_iodomain_priv *priv = supply->iod;
	struct regmap *regmap = priv->regmap_base;
	u32 is_3v3 = uV > MAX_VOLTAGE_1_8;
	u32 val0, val1;
	int b;

	switch (supply->idx) {
	case 0: /* pmuio1 */
	case 1: /* pmuio2 */
		b = supply->idx;
		val0 = BIT(16 + b) | (is_3v3 ? 0 : BIT(b));
		b = supply->idx + 4;
		val1 = BIT(16 + b) | (is_3v3 ? BIT(b) : 0);

		regmap_write(regmap, RK3568_PMU_GRF_IO_VSEL2, val0);
		regmap_write(regmap, RK3568_PMU_GRF_IO_VSEL2, val1);
		break;
	case 2: /* vccio1 */
	case 3: /* vccio2 */
	case 4: /* vccio3 */
	case 5: /* vccio4 */
	case 6: /* vccio5 */
	case 7: /* vccio6 */
	case 8: /* vccio7 */
		b = supply->idx - 1;
		val0 = BIT(16 + b) | (is_3v3 ? 0 : BIT(b));
		val1 = BIT(16 + b) | (is_3v3 ? BIT(b) : 0);

		regmap_write(regmap, RK3568_PMU_GRF_IO_VSEL0, val0);
		regmap_write(regmap, RK3568_PMU_GRF_IO_VSEL1, val1);
		break;
	default:
		return -EINVAL;
	};

	return 0;
}

static int rv1126_iodomain_write(struct rockchip_iodomain_supply *supply,
				 int uV)
{
	struct rockchip_iodomain_priv *priv = supply->iod;
	struct regmap *regmap = priv->regmap_base;
	u32 val, vret_hold, vret_release;

	/* set value bit */
	val = (uV > MAX_VOLTAGE_1_8) ? 0 : 1;
	val <<= supply->idx;
	/* apply hiword-mask */
	val |= (BIT(supply->idx) << 16);

	vret_hold = (BIT(supply->idx) << 16);
	vret_release = (BIT(supply->idx) << 16) | BIT(supply->idx);

	printf("%s: %d uv, vsel: 0x%x\n",
	       priv->sdata->supply_names[supply->idx], uV, val);

	regmap_write(regmap, RV1126_PMU_GRF_IO_RETENTION, vret_hold);
	regmap_write(regmap, priv->sdata->grf_offset, val);
	regmap_write(regmap, RV1126_PMU_GRF_IO_RETENTION, vret_release);

	return 0;
}

static int rockchip_iodomain_write(struct rockchip_iodomain_supply *supply,
				   int uV)
{
	struct rockchip_iodomain_priv *priv = supply->iod;
	struct regmap *regmap = priv->regmap_base;
	u32 val;
	int ret;

	/* set value bit */
	val = (uV > MAX_VOLTAGE_1_8) ? 0 : 1;
	val <<= supply->idx;

	/* apply hiword-mask */
	val |= (BIT(supply->idx) << 16);

	ret = regmap_write(regmap, priv->sdata->grf_offset, val);
	if (ret) {
		dev_err(priv->dev, "Couldn't write to GRF\n");
		return ret;
	}

	return 0;
}

static void px30_iodomain_init(struct rockchip_iodomain_priv *iod)
{
	int ret;
	u32 val;

	/* if no VCCIO0 supply we should leave things alone */
	if (!iod->supplies[PX30_IO_VSEL_VCCIO6_SUPPLY_NUM].reg)
		return;

	/*
	 * set vccio0 iodomain to also use this framework
	 * instead of a special gpio.
	 */
	val = PX30_IO_VSEL_VCCIO6_SRC | (PX30_IO_VSEL_VCCIO6_SRC << 16);
	ret = regmap_write(iod->regmap_base, PX30_IO_VSEL, val);
	if (ret < 0)
		dev_warn(iod->dev, "couldn't update vccio0 ctrl\n");
}

static void rk3288_iodomain_init(struct rockchip_iodomain_priv *iod)
{
	int ret;
	u32 val;

	/* if no flash supply we should leave things alone */
	if (!iod->supplies[RK3288_SOC_FLASH_SUPPLY_NUM].reg)
		return;

	/*
	 * set flash0 iodomain to also use this framework
	 * instead of a special gpio.
	 */
	val = RK3288_SOC_CON2_FLASH0 | (RK3288_SOC_CON2_FLASH0 << 16);
	ret = regmap_write(iod->regmap_base, RK3288_SOC_CON2, val);
	if (ret < 0)
		dev_warn(iod->dev, "couldn't update flash0 ctrl\n");
}

static void rk3308_iodomain_init(struct rockchip_iodomain_priv *iod)
{
	int ret;
	u32 val;

	/* if no vccio3 supply we should leave things alone */
	if (!iod->supplies[RK3308_SOC_VCCIO3_SUPPLY_NUM].reg)
		return;

	/*
	 * set vccio3 iodomain to also use this framework
	 * instead of a special gpio.
	 */
	val = RK3308_SOC_CON0_VCCIO3 | (RK3308_SOC_CON0_VCCIO3 << 16);
	ret = regmap_write(iod->regmap_base, RK3308_SOC_CON0, val);
	if (ret < 0)
		dev_warn(iod->dev, "couldn't update vccio3 vsel ctrl\n");
}

static void rk3328_iodomain_init(struct rockchip_iodomain_priv *iod)
{
	int ret;
	u32 val;

	/* if no vccio2 supply we should leave things alone */
	if (!iod->supplies[RK3328_SOC_VCCIO2_SUPPLY_NUM].reg)
		return;

	/*
	 * set vccio2 iodomain to also use this framework
	 * instead of a special gpio.
	 */
	val = RK3328_SOC_CON4_VCCIO2 | (RK3328_SOC_CON4_VCCIO2 << 16);
	ret = regmap_write(iod->regmap_base, RK3328_SOC_CON4, val);
	if (ret < 0)
		dev_warn(iod->dev, "couldn't update vccio2 vsel ctrl\n");
}

static void rk3366_iodomain_init(struct rockchip_iodomain_priv *iod)
{
	int ret;
	u32 val;

	/* if no flash supply we should leave things alone */
	if (!iod->supplies[RK3366_SOC_FLASH_SUPPLY_NUM].reg)
		return;

	/*
	 * set flash0 iodomain to also use this framework
	 * instead of a special gpio.
	 */
	val = RK3366_SOC_CON6_FLASH0 | (RK3366_SOC_CON6_FLASH0 << 16);
	ret = regmap_write(iod->regmap_base, RK3368_SOC_CON15, val);
	if (ret < 0)
		dev_warn(iod->dev, "couldn't update flash0 ctrl\n");
}

static void rk3368_iodomain_init(struct rockchip_iodomain_priv *iod)
{
	int ret;
	u32 val;

	/* if no flash supply we should leave things alone */
	if (!iod->supplies[RK3368_SOC_FLASH_SUPPLY_NUM].reg)
		return;

	/*
	 * set flash0 iodomain to also use this framework
	 * instead of a special gpio.
	 */
	val = RK3368_SOC_CON15_FLASH0 | (RK3368_SOC_CON15_FLASH0 << 16);
	ret = regmap_write(iod->regmap_base, RK3368_SOC_CON15, val);
	if (ret < 0)
		dev_warn(iod->dev, "couldn't update flash0 ctrl\n");
}

static void rk3399_pmu_iodomain_init(struct rockchip_iodomain_priv *iod)
{
	int ret;
	u32 val;

	/* if no pmu io supply we should leave things alone */
	if (!iod->supplies[RK3399_PMUGRF_VSEL_SUPPLY_NUM].reg)
		return;

	/*
	 * set pmu io iodomain to also use this framework
	 * instead of a special gpio.
	 */
	val = RK3399_PMUGRF_CON0_VSEL | (RK3399_PMUGRF_CON0_VSEL << 16);
	ret = regmap_write(iod->regmap_base, RK3399_PMUGRF_CON0, val);
	if (ret < 0)
		dev_warn(iod->dev, "couldn't update pmu io iodomain ctrl\n");
}

static const struct rockchip_iodomain_soc_data soc_data_px30 = {
	.grf_offset = 0x180,
	.supply_names = {
		NULL,
		"vccio6",
		"vccio1",
		"vccio2",
		"vccio3",
		"vccio4",
		"vccio5",
		"vccio-oscgpi",
	},
	.init = px30_iodomain_init,
};

static const struct rockchip_iodomain_soc_data soc_data_px30_pmu = {
	.grf_offset = 0x100,
	.supply_names = {
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		"pmuio1",
		"pmuio2",
	},
};

/*
 * On the rk3188 the io-domains are handled by a shared register with the
 * lower 8 bits being still being continuing drive-strength settings.
 */
static const struct rockchip_iodomain_soc_data soc_data_rk3188 = {
	.grf_offset = 0x104,
	.supply_names = {
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		"ap0",
		"ap1",
		"cif",
		"flash",
		"vccio0",
		"vccio1",
		"lcdc0",
		"lcdc1",
	},
};

static const struct rockchip_iodomain_soc_data soc_data_rk322x = {
	.grf_offset = 0x418,
	.supply_names = {
		"vccio1",
		"vccio2",
		"vccio3",
		"vccio4",
	},
};

static const struct rockchip_iodomain_soc_data soc_data_rk3288 = {
	.grf_offset = 0x380,
	.supply_names = {
		"lcdc",		/* LCDC_VDD */
		"dvp",		/* DVPIO_VDD */
		"flash0",	/* FLASH0_VDD (emmc) */
		"flash1",	/* FLASH1_VDD (sdio1) */
		"wifi",		/* APIO3_VDD  (sdio0) */
		"bb",		/* APIO5_VDD */
		"audio",	/* APIO4_VDD */
		"sdcard",	/* SDMMC0_VDD (sdmmc) */
		"gpio30",	/* APIO1_VDD */
		"gpio1830",	/* APIO2_VDD */
	},
	.init = rk3288_iodomain_init,
};

static const struct rockchip_iodomain_soc_data soc_data_rk3308 = {
	.grf_offset = 0x300,
	.supply_names = {
		"vccio0",
		"vccio1",
		"vccio2",
		"vccio3",
		"vccio4",
		"vccio5",
	},
	.init = rk3308_iodomain_init,
};

static const struct rockchip_iodomain_soc_data soc_data_rk3328 = {
	.grf_offset = 0x410,
	.supply_names = {
		"vccio1",
		"vccio2",
		"vccio3",
		"vccio4",
		"vccio5",
		"vccio6",
		"pmuio",
	},
	.init = rk3328_iodomain_init,
};

static const struct rockchip_iodomain_soc_data soc_data_rk3366 = {
	.grf_offset = 0x900,
	.supply_names = {
		"lcdc",         /* LCDC_IOVDD */
		"dvpts",        /* DVP_IOVDD */
		"flash",        /* FLASH_IOVDD (emmc) */
		"wifibt",       /* APIO1_IOVDD */
		NULL,
		"audio",        /* AUDIO_IODVDD */
		"sdcard",       /* SDMMC_IOVDD (sdmmc) */
		"tphdsor",      /* APIO2_IOVDD */
	},
	.init = rk3366_iodomain_init,
};

static const struct rockchip_iodomain_soc_data soc_data_rk3368 = {
	.grf_offset = 0x900,
	.supply_names = {
		NULL,		/* reserved */
		"dvp",		/* DVPIO_VDD */
		"flash0",	/* FLASH0_VDD (emmc) */
		"wifi",		/* APIO2_VDD (sdio0) */
		NULL,
		"audio",	/* APIO3_VDD */
		"sdcard",	/* SDMMC0_VDD (sdmmc) */
		"gpio30",	/* APIO1_VDD */
		"gpio1830",	/* APIO4_VDD (gpujtag) */
	},
	.init = rk3368_iodomain_init,
};

static const struct rockchip_iodomain_soc_data soc_data_rk3368_pmu = {
	.grf_offset = 0x100,
	.supply_names = {
		NULL,
		NULL,
		NULL,
		NULL,
		"pmu",	        /*PMU IO domain*/
		"vop",	        /*LCDC IO domain*/
	},
};

static const struct rockchip_iodomain_soc_data soc_data_rk3399 = {
	.grf_offset = 0xe640,
	.supply_names = {
		"bt656",		/* APIO2_VDD */
		"audio",		/* APIO5_VDD */
		"sdmmc",		/* SDMMC0_VDD */
		"gpio1830",		/* APIO4_VDD */
	},
};

static const struct rockchip_iodomain_soc_data soc_data_rk3399_pmu = {
	.grf_offset = 0x180,
	.supply_names = {
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		"pmu1830",		/* PMUIO2_VDD */
	},
	.init = rk3399_pmu_iodomain_init,
};

static const struct rockchip_iodomain_soc_data soc_data_rk3568_pmu = {
	.grf_offset = 0x140,
	.supply_names = {
		"pmuio1",
		"pmuio2",
		"vccio1",
		"vccio2",
		"vccio3",
		"vccio4",
		"vccio5",
		"vccio6",
		"vccio7",
	},
};

static const struct rockchip_iodomain_soc_data soc_data_rv1108 = {
	.grf_offset = 0x404,
	.supply_names = {
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		"vccio1",
		"vccio2",
		"vccio3",
		"vccio5",
		"vccio6",
	},

};

static const struct rockchip_iodomain_soc_data soc_data_rv1108_pmu = {
	.grf_offset = 0x104,
	.supply_names = {
		"pmu",
	},
};

static const struct rockchip_iodomain_soc_data soc_data_rv1126_pmu = {
	.grf_offset = 0x140,
	.supply_names = {
		NULL,
		"vccio1",
		"vccio2",
		"vccio3",
		"vccio4",
		"vccio5",
		"vccio6",
		"vccio7",
		"pmuio0",
		"pmuio1",
	},
};

static struct udevice *of_get_regulator(ofnode node, const char *supply)
{
	char sname[32]; /* 32 is max size of property name */
	struct udevice *sudev = NULL;
	ofnode snode;
	u32 phandle;
	int ret;

	snprintf(sname, 32, "%s-supply", supply);

	/* Get regulator and clk */
	if (!ofnode_read_u32(node, sname, &phandle)) {
		snode = ofnode_get_by_phandle(phandle);
		ret = regulator_get_by_devname(snode.np->name, &sudev);
		if (ret) {
			printf("%s: Get (%s) regulator: %s failed, ret=%d\n",
			       __func__,
			       sname, snode.np->full_name, ret);
			return NULL;
		}
		debug("IO-DOMAIN: supply: %s\n", snode.np->full_name);
	}

	return sudev;
}

static int rockchip_iodomain_probe(struct udevice *dev)
{
	struct rockchip_iodomain_priv *priv = dev_get_priv(dev);
	struct rockchip_iodomain_soc_data *sdata;
	int i, ret;

	sdata = (struct rockchip_iodomain_soc_data *)dev_get_driver_data(dev);
	priv->sdata = sdata;
	if (sdata == &soc_data_rk3568_pmu)
		priv->write = rk3568_pmu_iodomain_write;
	else if (sdata == &soc_data_rv1126_pmu)
		priv->write = rv1126_iodomain_write;
	else
		priv->write = rockchip_iodomain_write;

	if (!priv->regmap_base)
		return -1;

	for (i = 0; i < MAX_SUPPLIES; i++) {
		const char *supply_name = priv->sdata->supply_names[i];
		struct rockchip_iodomain_supply *supply = &priv->supplies[i];
		struct udevice *reg;
		u32 uV;

		if (!supply_name)
			continue;

		reg = of_get_regulator(dev_ofnode(dev), supply_name);
		if (!reg)
			continue;

		uV = regulator_get_value(reg);
		if (uV <= 0) {
			printf("voltage(%d uV) is invalid from %s\n", uV, reg->name);
			continue;
		}

		if (uV > MAX_VOLTAGE_3_3) {
			printf("%d uV is too high from %s\n", uV, reg->name);
			continue;
		}

		/* setup our supply */
		supply->idx = i;
		supply->iod = priv;
		supply->reg = reg;

		ret = priv->write(supply, uV);
		if (ret)
			supply->reg = NULL;
	}

	if (priv->sdata->init)
		priv->sdata->init(priv);

	return 0;
}

static const struct udevice_id rockchip_iodomain_match[] = {
	{
		.compatible = "rockchip,px30-io-voltage-domain",
		.data = (ulong)&soc_data_px30
	},
	{
		.compatible = "rockchip,px30-pmu-io-voltage-domain",
		.data = (ulong)&soc_data_px30_pmu
	},
	{
		.compatible = "rockchip,rk3188-io-voltage-domain",
		.data = (ulong)&soc_data_rk3188
	},
	{
		.compatible = "rockchip,rk322x-io-voltage-domain",
		.data = (ulong)&soc_data_rk322x
	},
	{
		.compatible = "rockchip,rk3288-io-voltage-domain",
		.data = (ulong)&soc_data_rk3288
	},
	{
		.compatible = "rockchip,rk3308-io-voltage-domain",
		.data = (ulong)&soc_data_rk3308
	},
	{
		.compatible = "rockchip,rk3328-io-voltage-domain",
		.data = (ulong)&soc_data_rk3328
	},
	{
		.compatible = "rockchip,rk3366-io-voltage-domain",
		.data = (ulong)&soc_data_rk3366
	},
	{
		.compatible = "rockchip,rk3368-io-voltage-domain",
		.data = (ulong)&soc_data_rk3368
	},
	{
		.compatible = "rockchip,rk3368-pmu-io-voltage-domain",
		.data = (ulong)&soc_data_rk3368_pmu
	},
	{
		.compatible = "rockchip,rk3399-io-voltage-domain",
		.data = (ulong)&soc_data_rk3399
	},
	{
		.compatible = "rockchip,rk3399-pmu-io-voltage-domain",
		.data = (ulong)&soc_data_rk3399_pmu
	},
	{
		.compatible = "rockchip,rk3568-pmu-io-voltage-domain",
		.data = (ulong)&soc_data_rk3568_pmu
	},
	{
		.compatible = "rockchip,rv1108-io-voltage-domain",
		.data = (ulong)&soc_data_rv1108
	},
	{
		.compatible = "rockchip,rv1108-pmu-io-voltage-domain",
		.data = (ulong)&soc_data_rv1108_pmu
	},
	{
		.compatible = "rockchip,rv1126-pmu-io-voltage-domain",
		.data = (ulong)&soc_data_rv1126_pmu
	},
	{ /* sentinel */ },
};

U_BOOT_DRIVER(io_domain) = {
	.name		= "io_domain",
	.id		= UCLASS_IO_DOMAIN,
	.of_match	= rockchip_iodomain_match,
	.priv_auto_alloc_size = sizeof(struct rockchip_iodomain_priv),
	.ofdata_to_platdata	= rockchip_ofdata_to_platdata,
	.probe		= rockchip_iodomain_probe,
};
