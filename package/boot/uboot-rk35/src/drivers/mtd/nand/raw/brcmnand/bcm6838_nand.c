// SPDX-License-Identifier: GPL-2.0+

#include <common.h>
#include <asm/io.h>
#include <memalign.h>
#include <nand.h>
#include <linux/errno.h>
#include <linux/io.h>
#include <linux/ioport.h>
#include <dm.h>

#include "brcmnand.h"

struct bcm6838_nand_soc {
	struct brcmnand_soc soc;
	void __iomem *base;
};

#define BCM6838_NAND_INT		0x00
#define  BCM6838_NAND_STATUS_SHIFT	0
#define  BCM6838_NAND_STATUS_MASK	(0xfff << BCM6838_NAND_STATUS_SHIFT)
#define  BCM6838_NAND_ENABLE_SHIFT	16
#define  BCM6838_NAND_ENABLE_MASK	(0xffff << BCM6838_NAND_ENABLE_SHIFT)

enum {
	BCM6838_NP_READ		= BIT(0),
	BCM6838_BLOCK_ERASE	= BIT(1),
	BCM6838_COPY_BACK	= BIT(2),
	BCM6838_PAGE_PGM	= BIT(3),
	BCM6838_CTRL_READY	= BIT(4),
	BCM6838_DEV_RBPIN	= BIT(5),
	BCM6838_ECC_ERR_UNC	= BIT(6),
	BCM6838_ECC_ERR_CORR	= BIT(7),
};

static bool bcm6838_nand_intc_ack(struct brcmnand_soc *soc)
{
	struct bcm6838_nand_soc *priv =
			container_of(soc, struct bcm6838_nand_soc, soc);
	void __iomem *mmio = priv->base + BCM6838_NAND_INT;
	u32 val = brcmnand_readl(mmio);

	if (val & (BCM6838_CTRL_READY << BCM6838_NAND_STATUS_SHIFT)) {
		/* Ack interrupt */
		val &= ~BCM6838_NAND_STATUS_MASK;
		val |= BCM6838_CTRL_READY << BCM6838_NAND_STATUS_SHIFT;
		brcmnand_writel(val, mmio);
		return true;
	}

	return false;
}

static void bcm6838_nand_intc_set(struct brcmnand_soc *soc, bool en)
{
	struct bcm6838_nand_soc *priv =
			container_of(soc, struct bcm6838_nand_soc, soc);
	void __iomem *mmio = priv->base + BCM6838_NAND_INT;
	u32 val = brcmnand_readl(mmio);

	/* Don't ack any interrupts */
	val &= ~BCM6838_NAND_STATUS_MASK;

	if (en)
		val |= BCM6838_CTRL_READY << BCM6838_NAND_ENABLE_SHIFT;
	else
		val &= ~(BCM6838_CTRL_READY << BCM6838_NAND_ENABLE_SHIFT);

	brcmnand_writel(val, mmio);
}

static int bcm6838_nand_probe(struct udevice *dev)
{
	struct udevice *pdev = dev;
	struct bcm6838_nand_soc *priv = dev_get_priv(dev);
	struct brcmnand_soc *soc;
	struct resource res;

	soc = &priv->soc;

	dev_read_resource_byname(pdev, "nand-int-base", &res);
	priv->base = ioremap(res.start, resource_size(&res));
	if (IS_ERR(priv->base))
		return PTR_ERR(priv->base);

	soc->ctlrdy_ack = bcm6838_nand_intc_ack;
	soc->ctlrdy_set_enabled = bcm6838_nand_intc_set;

	/* Disable and ack all interrupts  */
	brcmnand_writel(0, priv->base + BCM6838_NAND_INT);
	brcmnand_writel(BCM6838_NAND_STATUS_MASK,
			priv->base + BCM6838_NAND_INT);

	return brcmnand_probe(pdev, soc);
}

static const struct udevice_id bcm6838_nand_dt_ids[] = {
	{
		.compatible = "brcm,nand-bcm6838",
	},
	{ /* sentinel */ }
};

U_BOOT_DRIVER(bcm6838_nand) = {
	.name = "bcm6838-nand",
	.id = UCLASS_MTD,
	.of_match = bcm6838_nand_dt_ids,
	.probe = bcm6838_nand_probe,
	.priv_auto_alloc_size = sizeof(struct bcm6838_nand_soc),
};

void board_nand_init(void)
{
	struct udevice *dev;
	int ret;

	ret = uclass_get_device_by_driver(UCLASS_MTD,
					  DM_GET_DRIVER(bcm6838_nand), &dev);
	if (ret && ret != -ENODEV)
		pr_err("Failed to initialize %s. (error %d)\n", dev->name,
		       ret);
}
