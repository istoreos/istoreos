/*
 * NXP GPMI NAND flash driver (DT initialization)
 *
 * Copyright (C) 2018 Toradex
 * Authors:
 * Stefan Agner <stefan.agner@toradex.com>
 *
 * Based on denali_dt.c
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <dm.h>
#include <linux/io.h>
#include <linux/ioport.h>
#include <linux/printk.h>

#include "mxs_nand.h"

struct mxs_nand_dt_data {
	unsigned int max_ecc_strength_supported;
};

static const struct mxs_nand_dt_data mxs_nand_imx6q_data = {
	.max_ecc_strength_supported = 40,
};

static const struct mxs_nand_dt_data mxs_nand_imx7d_data = {
	.max_ecc_strength_supported = 62,
};

static const struct udevice_id mxs_nand_dt_ids[] = {
	{
		.compatible = "fsl,imx6q-gpmi-nand",
		.data = (unsigned long)&mxs_nand_imx6q_data,
	},
	{
		.compatible = "fsl,imx7d-gpmi-nand",
		.data = (unsigned long)&mxs_nand_imx7d_data,
	},
	{ /* sentinel */ }
};

static int mxs_nand_dt_probe(struct udevice *dev)
{
	struct mxs_nand_info *info = dev_get_priv(dev);
	const struct mxs_nand_dt_data *data;
	struct resource res;
	int ret;

	data = (void *)dev_get_driver_data(dev);
	if (data)
		info->max_ecc_strength_supported = data->max_ecc_strength_supported;

	info->dev = dev;

	ret = dev_read_resource_byname(dev, "gpmi-nand", &res);
	if (ret)
		return ret;

	info->gpmi_regs = devm_ioremap(dev, res.start, resource_size(&res));


	ret = dev_read_resource_byname(dev, "bch", &res);
	if (ret)
		return ret;

	info->bch_regs = devm_ioremap(dev, res.start, resource_size(&res));

	info->use_minimum_ecc = dev_read_bool(dev, "fsl,use-minimum-ecc");

	return mxs_nand_init_ctrl(info);
}

U_BOOT_DRIVER(mxs_nand_dt) = {
	.name = "mxs-nand-dt",
	.id = UCLASS_MTD,
	.of_match = mxs_nand_dt_ids,
	.probe = mxs_nand_dt_probe,
	.priv_auto_alloc_size = sizeof(struct mxs_nand_info),
};

void board_nand_init(void)
{
	struct udevice *dev;
	int ret;

	ret = uclass_get_device_by_driver(UCLASS_MTD,
					  DM_GET_DRIVER(mxs_nand_dt),
					  &dev);
	if (ret && ret != -ENODEV)
		pr_err("Failed to initialize MXS NAND controller. (error %d)\n",
		       ret);
}
