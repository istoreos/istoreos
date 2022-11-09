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
#include <rksfc.h>
#include <asm/arch/vendor.h>

#include "rkflash_blk.h"
#include "rkflash_api.h"

static struct flash_operation sfc_nor_op = {
#ifdef	CONFIG_RKSFC_NOR
	IF_TYPE_SPINOR,
	rksfc_nor_init,
	rksfc_nor_get_capacity,
	rksfc_nor_read,
	rksfc_nor_write,
	NULL,
	rksfc_nor_vendor_read,
	rksfc_nor_vendor_write,
#else
	-1, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
#endif
};

static struct flash_operation sfc_nand_op = {
#ifdef CONFIG_RKSFC_NAND
	IF_TYPE_SPINAND,
	rksfc_nand_init,
	rksfc_nand_get_density,
	rksfc_nand_read,
	rksfc_nand_write,
	NULL,
	rksfc_nand_vendor_read,
	rksfc_nand_vendor_write,
#else
	-1, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
#endif
};

static struct flash_operation *spi_flash_op[2] = {
	&sfc_nor_op,
	&sfc_nand_op,
};

int rksfc_scan_namespace(void)
{
	struct uclass *uc;
	struct udevice *dev;
	int ret;

	ret = uclass_get(UCLASS_SPI_FLASH, &uc);
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

static int rksfc_blk_bind(struct udevice *udev)
{
	struct udevice *bdev;
	int ret;

	ret = blk_create_devicef(udev, "rkflash_blk", "spinand.blk",
				 IF_TYPE_SPINAND,
				 0, 512, 0, &bdev);
	ret = blk_create_devicef(udev, "rkflash_blk", "spinor.blk",
				 IF_TYPE_SPINOR,
				 1, 512, 0, &bdev);

	if (ret) {
		debug("Cannot create block device\n");
		return ret;
	}

	return 0;
}

static int rockchip_rksfc_ofdata_to_platdata(struct udevice *dev)
{
	struct rkflash_info *priv = dev_get_priv(dev);

	priv->ioaddr = dev_read_addr_ptr(dev);

	return 0;
}

static int rockchip_rksfc_probe(struct udevice *udev)
{
	int ret = 0;
	int i;
	struct rkflash_info *priv = dev_get_priv(udev);

	debug("%s %d %p ndev = %p\n", __func__, __LINE__, udev, priv);

	sfc_init(priv->ioaddr);
	for (i = 0; i < 2; i++) {
		if (spi_flash_op[i]->id <= 0) {
			debug("%s no optional spi flash for type %x\n",
			      __func__, i);
			continue;
		}
		ret = spi_flash_op[i]->flash_init(udev);
		if (!ret) {
			priv->flash_con_type = spi_flash_op[i]->id;
			priv->density =
				spi_flash_op[i]->flash_get_capacity(udev);
			priv->read = spi_flash_op[i]->flash_read;
			priv->write = spi_flash_op[i]->flash_write;
#ifdef CONFIG_ROCKCHIP_VENDOR_PARTITION
			flash_vendor_dev_ops_register(spi_flash_op[i]->vendor_read,
						      spi_flash_op[i]->vendor_write);
#endif
			debug("%s probe success\n", __func__);
			break;
		} else {
			pr_err("ret %d\n", ret);
		}
	}

	return ret;
}

UCLASS_DRIVER(rksfc) = {
	.id		= UCLASS_SPI_FLASH,
	.name		= "rksfc",
	.flags		= DM_UC_FLAG_SEQ_ALIAS,
};

static const struct udevice_id rockchip_sfc_ids[] = {
	{ .compatible = "rockchip,rksfc" },
	{ }
};

U_BOOT_DRIVER(rksfc) = {
	.name		= "rksfc",
	.id		= UCLASS_SPI_FLASH,
	.of_match	= rockchip_sfc_ids,
	.bind		= rksfc_blk_bind,
	.probe		= rockchip_rksfc_probe,
	.priv_auto_alloc_size = sizeof(struct rkflash_info),
	.ofdata_to_platdata = rockchip_rksfc_ofdata_to_platdata,
};

