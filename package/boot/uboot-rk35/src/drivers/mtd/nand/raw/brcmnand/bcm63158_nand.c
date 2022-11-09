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

struct bcm63158_nand_soc {
	struct brcmnand_soc soc;
	void __iomem *base;
};

#define BCM63158_NAND_INT		0x00
#define BCM63158_NAND_STATUS_SHIFT	0
#define BCM63158_NAND_STATUS_MASK	(0xfff << BCM63158_NAND_STATUS_SHIFT)

#define BCM63158_NAND_INT_EN		0x04
#define BCM63158_NAND_ENABLE_SHIFT	0
#define BCM63158_NAND_ENABLE_MASK	(0xffff << BCM63158_NAND_ENABLE_SHIFT)

enum {
	BCM63158_NP_READ		= BIT(0),
	BCM63158_BLOCK_ERASE	= BIT(1),
	BCM63158_COPY_BACK	= BIT(2),
	BCM63158_PAGE_PGM	= BIT(3),
	BCM63158_CTRL_READY	= BIT(4),
	BCM63158_DEV_RBPIN	= BIT(5),
	BCM63158_ECC_ERR_UNC	= BIT(6),
	BCM63158_ECC_ERR_CORR	= BIT(7),
};

static bool bcm63158_nand_intc_ack(struct brcmnand_soc *soc)
{
	struct bcm63158_nand_soc *priv =
			container_of(soc, struct bcm63158_nand_soc, soc);
	void __iomem *mmio = priv->base + BCM63158_NAND_INT;
	u32 val = brcmnand_readl(mmio);

	if (val & (BCM63158_CTRL_READY << BCM63158_NAND_STATUS_SHIFT)) {
		/* Ack interrupt */
		val &= ~BCM63158_NAND_STATUS_MASK;
		val |= BCM63158_CTRL_READY << BCM63158_NAND_STATUS_SHIFT;
		brcmnand_writel(val, mmio);
		return true;
	}

	return false;
}

static void bcm63158_nand_intc_set(struct brcmnand_soc *soc, bool en)
{
	struct bcm63158_nand_soc *priv =
			container_of(soc, struct bcm63158_nand_soc, soc);
	void __iomem *mmio = priv->base + BCM63158_NAND_INT_EN;
	u32 val = brcmnand_readl(mmio);

	/* Don't ack any interrupts */
	val &= ~BCM63158_NAND_STATUS_MASK;

	if (en)
		val |= BCM63158_CTRL_READY << BCM63158_NAND_ENABLE_SHIFT;
	else
		val &= ~(BCM63158_CTRL_READY << BCM63158_NAND_ENABLE_SHIFT);

	brcmnand_writel(val, mmio);
}

static int bcm63158_nand_probe(struct udevice *dev)
{
	struct udevice *pdev = dev;
	struct bcm63158_nand_soc *priv = dev_get_priv(dev);
	struct brcmnand_soc *soc;
	struct resource res;

	soc = &priv->soc;

	dev_read_resource_byname(pdev, "nand-int-base", &res);
	priv->base = devm_ioremap(dev, res.start, resource_size(&res));
	if (IS_ERR(priv->base))
		return PTR_ERR(priv->base);

	soc->ctlrdy_ack = bcm63158_nand_intc_ack;
	soc->ctlrdy_set_enabled = bcm63158_nand_intc_set;

	/* Disable and ack all interrupts  */
	brcmnand_writel(0, priv->base + BCM63158_NAND_INT_EN);
	brcmnand_writel(0, priv->base + BCM63158_NAND_INT);

	return brcmnand_probe(pdev, soc);
}

static const struct udevice_id bcm63158_nand_dt_ids[] = {
	{
		.compatible = "brcm,nand-bcm63158",
	},
	{ /* sentinel */ }
};

U_BOOT_DRIVER(bcm63158_nand) = {
	.name = "bcm63158-nand",
	.id = UCLASS_MTD,
	.of_match = bcm63158_nand_dt_ids,
	.probe = bcm63158_nand_probe,
	.priv_auto_alloc_size = sizeof(struct bcm63158_nand_soc),
};

void board_nand_init(void)
{
	struct udevice *dev;
	int ret;

	ret = uclass_get_device_by_driver(UCLASS_MTD,
					  DM_GET_DRIVER(bcm63158_nand), &dev);
	if (ret && ret != -ENODEV)
		pr_err("Failed to initialize %s. (error %d)\n", dev->name,
		       ret);
}
