/*
 * Copyright (c) 2018 Fuzhou Rockchip Electronics Co., Ltd
 *
 * SPDX-License-Identifier:	GPL-2.0
 */

#include <common.h>
#include <clk.h>
#include <dm.h>
#include <dm/device-internal.h>
#include <asm/arch/clock.h>
#include <asm/arch/vendor.h>

#include "rkflash_blk.h"
#include "rkflash_api.h"

static struct flash_operation nandc_flash_op = {
#ifdef	CONFIG_RKNANDC_NAND
	IF_TYPE_RKNAND,
	rknand_flash_init,
	rknand_flash_get_density,
	rknand_flash_read,
	rknand_flash_write,
	NULL,
	rknand_flash_vendor_read,
	rknand_flash_vendor_write,
#else
	-1, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
#endif
};

int rknand_scan_namespace(void)
{
	struct uclass *uc;
	struct udevice *dev;
	int ret;

	ret = uclass_get(UCLASS_RKNAND, &uc);
	if (ret)
		return ret;

	uclass_foreach_dev(dev, uc) {
		debug("%s %d %p\n", __func__, __LINE__, dev);
		ret = device_probe(dev);
		if (ret)
			return ret;
	}

	return 0;
}

static int rknand_blk_bind(struct udevice *udev)
{
	struct udevice *bdev;
	int ret;

	ret = blk_create_devicef(udev, "rkflash_blk", "blk",
				 IF_TYPE_RKNAND,
				 0, 512, 0, &bdev);
	if (ret) {
		debug("Cannot create block device\n");
		return ret;
	}

	return 0;
}

static int rockchip_nand_ofdata_to_platdata(struct udevice *dev)
{
	struct rkflash_info *priv = dev_get_priv(dev);

	priv->ioaddr = dev_read_addr_ptr(dev);

	return 0;
}

static int rockchip_nand_probe(struct udevice *udev)
{
	int ret;
	struct rkflash_info *priv = dev_get_priv(udev);

	debug("%s %d %p ndev = %p\n", __func__, __LINE__, udev, priv);

	ret = nandc_flash_init(priv->ioaddr);
	if (ret) {
		debug("nandc_flash_init failed, ret %d", ret);
		return ret;
	}
	ret = nandc_flash_op.flash_init(udev);
	if (!ret) {
		priv->flash_con_type = nandc_flash_op.id;
		priv->density = nandc_flash_op.flash_get_capacity(udev);
		priv->read = nandc_flash_op.flash_read;
		priv->write = nandc_flash_op.flash_write;
		priv->erase = nandc_flash_op.flash_erase;
#ifdef CONFIG_ROCKCHIP_VENDOR_PARTITION
		flash_vendor_dev_ops_register(nandc_flash_op.vendor_read,
					      nandc_flash_op.vendor_write);
#endif
		debug("%s probe success\n", __func__);
	} else {
		pr_err("ret %d\n", ret);
	}

	return ret;
}

UCLASS_DRIVER(rknand) = {
	.id		= UCLASS_RKNAND,
	.name		= "rknand",
	.flags		= DM_UC_FLAG_SEQ_ALIAS,
};

static const struct udevice_id rockchip_nand_ids[] = {
	{ .compatible = "rockchip,rk-nandc" },
	{ }
};

U_BOOT_DRIVER(rknand) = {
	.name		= "rknand",
	.id		= UCLASS_RKNAND,
	.of_match	= rockchip_nand_ids,
	.bind		= rknand_blk_bind,
	.probe		= rockchip_nand_probe,
	.priv_auto_alloc_size = sizeof(struct rkflash_info),
	.ofdata_to_platdata = rockchip_nand_ofdata_to_platdata,
};

