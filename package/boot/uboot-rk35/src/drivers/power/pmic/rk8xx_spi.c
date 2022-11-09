/*
 **Copyright (C) 2021 Rockchip Electronics Co., Ltd
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <common.h>
#include <dm.h>
#include <errno.h>
#include <irq-generic.h>
#include <power/rk8xx_pmic.h>
#include <power/pmic.h>
#include <spi.h>

DECLARE_GLOBAL_DATA_PTR;

#define RK806_CHIP_NAME			0x5A
#define RK806_CHIP_VER			0x5B
#define RK806_HW_VER			0x21
#define HW_DUAL_PMIC			0x28
#define HW_SINGLE_PMIC			0xe8

#define RK806_CMD_READ			0
#define RK806_CMD_WRITE			BIT(7)
#define RK806_CMD_CRC_EN		BIT(6)
#define RK806_CMD_CRC_DIS		0
#define RK806_CMD_LEN_MSK		0x0f
#define RK806_REG_H			0x00

#define RK806_SYS_CFG1			0x5f
#define RK806_SYS_CFG3			0x72
#define RK806_PWRON_KEY			0x76
#define RK806_INT_STS0			0x77
#define RK806_INT_MSK0			0x78
#define RK806_INT_STS1			0x79
#define RK806_INT_MSK1			0x7A
#define RK806_GPIO_INT_CONFIG		0x7B
#define RK806_IRQ_PWRON_FALL_MSK	BIT(0)
#define RK806_IRQ_PWRON_RISE_MSK	BIT(1)
#define RK806_DEV_OFF			BIT(0)
#define RK806_RST_MODE1			0x01
#define RK806_RST_MODE2			0x02
#define VERSION_AB			0x01

#if CONFIG_IS_ENABLED(IRQ)
/* RK805 */
static const struct virq_reg rk806_irqs[] = {
	[RK8XX_IRQ_PWRON_FALL] = {
		.mask = RK806_IRQ_PWRON_FALL_MSK,
		.reg_offset = 0,
	},
	[RK8XX_IRQ_PWRON_RISE] = {
		.mask = RK806_IRQ_PWRON_RISE_MSK,
		.reg_offset = 0,
	},
};

static struct virq_chip rk806_irq_chip = {
	.status_base		= RK806_INT_STS0,
	.mask_base		= RK806_INT_MSK0,
	.num_regs		= 1,
	.read			= pmic_reg_read,
	.write			= pmic_reg_write,
	.irqs			= rk806_irqs,
	.num_irqs		= ARRAY_SIZE(rk806_irqs),
};
#endif

static const struct pmic_child_info pmic_children_info[] = {
	{ .prefix = "DCDC", .driver = "rk8xx_spi_buck"},
	{ .prefix = "NLDO", .driver = "rk8xx_spi_ldo"},
	{ .prefix = "PLDO", .driver = "rk8xx_spi_pldo"},
	{ },
};

static const struct pmic_child_info power_key_info[] = {
	{ .prefix = "pwrkey", .driver = "rk8xx_pwrkey"},
	{ },
};

static int _spi_read(struct udevice *dev, u32 reg, u8 *buffer, int len)
{
	struct rk8xx_priv *priv = dev_get_priv(dev);
	u8 txbuf[3];
	int ret;

	if (spi_claim_bus(priv->slave))
		return -EBUSY;

	txbuf[0] = RK806_CMD_READ;
	txbuf[1] = reg;
	txbuf[2] = RK806_REG_H;

	ret = spi_write_then_read(priv->slave, txbuf, 3, NULL, buffer, 1);
	spi_release_bus(priv->slave);

	return ret;
}

static int _spi_write(struct udevice *dev, uint reg, const u8 *buffer, int len)
{
	struct rk8xx_priv *priv = dev_get_priv(dev);
	u8 txbuf[4];
	int ret;

	if (len < 1) {
		dev_err(dev, "rk806 write error: len < 1\n");
		return -EINVAL;
	}

	if (spi_claim_bus(priv->slave))
		return -EBUSY;

	txbuf[0] = RK806_CMD_WRITE;
	txbuf[1] = reg;
	txbuf[2] = RK806_REG_H;
	txbuf[3] = *buffer;

	ret = spi_write_then_read(priv->slave, txbuf, 4, NULL, NULL, 0);
	spi_release_bus(priv->slave);

	return ret;
}

static int rk806_spi_read(struct udevice *dev,
			  uint reg,
			  u8 *buffer,
			  int len)
{
	int ret;

	ret = _spi_read(dev, reg, buffer, len);
	if (ret)
		dev_err(dev, "rk806 read reg(0x%x) error: %d\n", reg, ret);

	return ret;
}

static int rk806_spi_write(struct udevice *dev,
			   uint reg,
			   const u8 *buffer,
			   int len)
{
	int ret;

	ret = _spi_write(dev, reg, buffer, len);
	if (ret)
		dev_err(dev, "rk806 write reg(0x%x) error: %d\n", reg, ret);

	return ret;
}

static int rk8xx_spi_reg_count(struct udevice *dev)
{
	return 0xff;
}

#if CONFIG_IS_ENABLED(PMIC_CHILDREN)
static int rk8xx_spi_bind(struct udevice *dev)
{
	ofnode regulators_node;
	int children;

	regulators_node = dev_read_subnode(dev, "regulators");
	if (!ofnode_valid(regulators_node)) {
		debug("%s: %s regulators subnode not found!\n", __func__,
		      dev->name);
		return -ENXIO;
	}

	children = pmic_bind_children(dev, regulators_node, pmic_children_info);
	if (!children)
		debug("%s: %s - no child found\n", __func__, dev->name);

	children = pmic_bind_children(dev, dev->node, power_key_info);
	if (!children)
		debug("%s: %s - no child found\n", __func__, dev->name);

	return 0;
}
#endif
#if CONFIG_IS_ENABLED(IRQ)
static int rk8xx_spi_ofdata_to_platdata(struct udevice *dev)
{
	struct rk8xx_priv *rk8xx = dev_get_priv(dev);
	u32 interrupt, phandle;
	int ret;

	rk8xx->rst_fun = dev_read_u32_default(dev, "pmic-reset-func", 0);

	phandle = dev_read_u32_default(dev, "interrupt-parent", -ENODATA);
	if (phandle == -ENODATA) {
		printf("Read 'interrupt-parent' failed, ret=%d\n", phandle);
		return phandle;
	}

	ret = dev_read_u32_array(dev, "interrupts", &interrupt, 1);
	if (ret) {
		printf("Read 'interrupts' failed, ret=%d\n", ret);
		return ret;
	}

	rk8xx->irq = phandle_gpio_to_irq(phandle, interrupt);
	if (rk8xx->irq < 0)
		printf("Failed to request rk8xx irq, ret=%d\n", rk8xx->irq);

	return 0;
}

static int rk8xx_spi_irq_chip_init(struct udevice *dev)
{
	struct rk8xx_priv *priv = dev_get_priv(dev);
	struct virq_chip *irq_chip = NULL;
	u8 value;
	int ret;

	value = 0xff;
	rk806_spi_write(dev, RK806_INT_STS0, &value, 1);
	rk806_spi_write(dev, RK806_INT_STS1, &value, 1);
	rk806_spi_write(dev, RK806_INT_MSK0, &value, 1);
	rk806_spi_write(dev, RK806_INT_MSK1, &value, 1);
	value = 0x00;
	rk806_spi_write(dev, RK806_GPIO_INT_CONFIG, &value, 1);

	irq_chip = &rk806_irq_chip;

	if (irq_chip && priv->irq > 0) {
		ret = virq_add_chip(dev, irq_chip, priv->irq);
		if (ret) {
			printf("Failed to add irqchip(irq=%d), ret=%d\n",
			       priv->irq, ret);
			return ret;
		}
		priv->irq_chip = irq_chip;
	}

	return 0;
}
#else
static inline int rk8xx_spi_ofdata_to_platdata(struct udevice *dev)
{
	return 0;
}

static inline int rk8xx_spi_irq_chip_init(struct udevice *dev)
{
	return 0;
}
#endif

static int rk8xx_spi_probe(struct udevice *dev)
{
	struct dm_spi_slave_platdata *plat = dev_get_parent_platdata(dev);
	struct rk8xx_priv *priv = dev_get_priv(dev);
	struct udevice *spi = dev_get_parent(dev);
	struct spi_slave *slave = NULL;
	u8 msb, lsb, value = 0;
	int ret;

	if (spi->seq < 0) {
		dev_err(dev, "Failed to configure the spi num\n");
		return -EINVAL;
	}

	slave = spi_setup_slave(spi->seq, plat->cs, plat->max_hz,
				plat->mode);
	if (!slave)
		return -ENODEV;
	priv->slave = slave;

	/* read Chip variant */
	ret = rk806_spi_read(dev, RK806_CHIP_NAME, &msb, 1);
	if (ret) {
		dev_err(dev, "rk806 name read error: %d\n", ret);
		return ret;
	}

	ret = rk806_spi_read(dev, RK806_CHIP_VER, &lsb, 1);
	if (ret) {
		dev_err(dev, "rk806 version read error: %d\n", ret);
		return ret;
	}

	priv->variant = ((msb << 8) | lsb) & RK8XX_ID_MSK;
	printf("spi%d: RK%x%x: %d\n", spi->seq, msb, (lsb >> 4), lsb & 0x0f);

	ret = rk806_spi_read(dev, RK806_HW_VER, &value, 1);
	if (ret)
		panic("RK806: read RK806_HW_VER error!\n");
	/* dual rk806 dev name: "rk806master@0", "rk806slave@1"
	 * single rk806 dev name: " rk806single@0"
	 */
	if ((!strcmp(dev->name, "rk806master@0")) || (!strcmp(dev->name, "rk806slave@1"))) {
		if (value != HW_DUAL_PMIC) {
			dev_err(dev, "HW single pmic, the firmware dual pmic(0x%x)!\n", value);
			run_command("download", 0);
		}
	} else {
		if (value != HW_SINGLE_PMIC) {
			dev_err(dev, "HW dual pmic, the firmware single pmic(0x%x)!\n", value);
			run_command("download", 0);
		}
	}

	if ((lsb & 0x0f) == VERSION_AB) {
		ret = rk806_spi_read(dev, RK806_SYS_CFG1, &value, 1);
		if (ret) {
			dev_err(dev, "rk806 RK806_SYS_CFG1 read error: %d\n", ret);
			return ret;
		}
		value |= 0x80;
		rk806_spi_write(dev, RK806_SYS_CFG1, &value, 1);
	}

	if (priv->rst_fun) {
		rk806_spi_read(dev, RK806_SYS_CFG3, &value, 1);
		value &= 0x3f;
		if (priv->rst_fun == RK806_RST_MODE1) {
			value |= (RK806_RST_MODE1 << 6);
			rk806_spi_write(dev, RK806_SYS_CFG3, &value, 1);
		} else if (priv->rst_fun == RK806_RST_MODE2) {
			value |= (RK806_RST_MODE2 << 6);
			rk806_spi_write(dev, RK806_SYS_CFG3, &value, 1);
		}
	}

	rk8xx_spi_irq_chip_init(dev);

	return 0;
}

static int rk8xx_spi_shutdown(struct udevice *dev)
{
	u8 dev_off;
	int ret = 0;

	ret = rk806_spi_read(dev, RK806_SYS_CFG3, &dev_off, 1);
	if (ret)
		return ret;

	dev_off |= RK806_DEV_OFF;
	ret = rk806_spi_write(dev, RK806_SYS_CFG3, &dev_off, 1);
	if (ret) {
		dev_err(dev, "rk806 shutdown error: %d\n", ret);
		return ret;
	}

	while (1)
		;

	return 0;
}

static struct dm_pmic_ops rk8xx_spi_ops = {
	.reg_count = rk8xx_spi_reg_count,
	.read = rk806_spi_read,
	.write = rk806_spi_write,
	.shutdown = rk8xx_spi_shutdown,
};

static const struct udevice_id rk8xx_spi_ids[] = {
	{ .compatible = "rockchip,rk806" },
	{ }
};

U_BOOT_DRIVER(pmic_rk8xx_spi) = {
	.name = "rk806-pmic",
	.id = UCLASS_PMIC,
	.of_match = rk8xx_spi_ids,
#if CONFIG_IS_ENABLED(PMIC_CHILDREN)
	.bind = rk8xx_spi_bind,
#endif
	.ofdata_to_platdata = rk8xx_spi_ofdata_to_platdata,
	.priv_auto_alloc_size = sizeof(struct rk8xx_priv),
	.probe = rk8xx_spi_probe,
	.ops = &rk8xx_spi_ops,
};
