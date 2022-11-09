/*
 * (C) Copyright 2019 Rockchip Electronics Co., Ltd
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */

#include <common.h>
#include <dm.h>
#include <power/pmic.h>
#include <power/rk8xx_pmic.h>
#include <irq-generic.h>
#include <asm/arch/periph.h>
#include <dm/pinctrl.h>
#include <rtc.h>

#define	RK817_INT_STS_REG0	0xf8
#define	RK817_INT_MSK_REG0	0xf9

#define	RK816_INT_STS_REG2	0x4c
#define	RK816_INT_MSK_REG2	0x4d

#define	RK808_INT_STS_REG1	0x4c
#define	RK808_INT_MSK_REG1	0x4d

#define	RK805_INT_STS_REG	0x4c
#define	RK805_INT_MSK_REG	0x4d

#define RK808_RTC_CTRL_REG	0x10
#define RK808_RTC_STATUS_REG	0x11
#define RK808_RTC_INT_REG	0x12

#define RK817_RTC_CTRL_REG	0x0d
#define RK817_RTC_STATUS_REG	0x0e
#define RK817_RTC_INT_REG	0x0f

#define RTC_ALARM_EN		5
#define RTC_ALARM_STATUS	BIT(6)

struct rk8xx_rtc_priv {
	u8 rtc_int_sts_reg;
	u8 rtc_int_msk_reg;
	u8 int_sts_reg;
	u8 int_msk_reg;
	int rtc_alarm_trigger;
	int irq_is_busy;
};

static void rtc_irq_handler(int irq, void *data)
{
	struct udevice *dev = data;
	struct rk8xx_rtc_priv *priv = dev_get_priv(dev);
	int ret, val;

	debug("%s: irq = %d\n", __func__, irq);

	if (priv->rtc_int_sts_reg) {
		val = pmic_reg_read(dev->parent, priv->rtc_int_sts_reg);
		if (val < 0) {
			printf("%s: i2c read reg 0x%x failed, ret=%d\n",
			       __func__, priv->rtc_int_sts_reg, val);
			return;
		}

		if (val & RTC_ALARM_STATUS) {
			priv->rtc_alarm_trigger = 1;
			printf("RTC: alarm interrupt\n");
		}

		ret = pmic_reg_write(dev->parent,
				     priv->rtc_int_sts_reg, 0xfe);
		if (ret < 0) {
			printf("%s: i2c write reg 0x%x failed, ret=%d\n",
			       __func__, priv->rtc_int_sts_reg, ret);
			return;
		}
	}

	ret = pmic_reg_write(dev->parent,
			     priv->int_sts_reg, 0xff);
	if (ret < 0) {
		printf("%s: i2c write reg 0x%x failed, ret=%d\n",
		       __func__, priv->int_sts_reg, ret);
		return;
	}
	debug("%s: reg[0x%x] = 0x%x\n", __func__, priv->int_sts_reg,
	      pmic_reg_read(dev->parent, priv->int_sts_reg));
}

static int rtc_interrupt_init(struct udevice *dev)
{
	struct rk8xx_rtc_priv *priv = dev_get_priv(dev);
	u32 interrupt[2], phandle;
	int irq, ret;

	phandle = dev_read_u32_default(dev->parent, "interrupt-parent", -1);
	if (phandle < 0) {
		printf("failed get 'interrupt-parent', ret=%d\n", phandle);
		return phandle;
	}

	ret = dev_read_u32_array(dev->parent, "interrupts", interrupt, 2);
	if (ret) {
		printf("failed get 'interrupt', ret=%d\n", ret);
		return ret;
	}

	irq = phandle_gpio_to_irq(phandle, interrupt[0]);
	if (irq < 0) {
		if (irq == -EBUSY) {
			priv->irq_is_busy = 1;
			return 0;
		}
		return irq;
	}
	irq_install_handler(irq, rtc_irq_handler, dev);
	irq_set_irq_type(irq, IRQ_TYPE_EDGE_FALLING);
	irq_handler_enable(irq);

	return 0;
}

static int rk8xx_rtc_alarm_trigger(struct udevice *dev)
{
	struct rk8xx_rtc_priv *priv = dev_get_priv(dev);
	int val, ret, alarm_trigger = 0;

	if (priv->irq_is_busy) {
		val = pmic_reg_read(dev->parent, priv->rtc_int_sts_reg);
		if (val < 0) {
			printf("%s: i2c read reg 0x%x failed, ret=%d\n",
			       __func__, priv->rtc_int_sts_reg, val);
			return val;
		}
		if (val & RTC_ALARM_STATUS) {
			alarm_trigger = 1;
			printf("rtc alarm interrupt\n");
		}
		ret = pmic_reg_write(dev->parent,
				     priv->rtc_int_sts_reg, 0xfe);
		if (ret < 0) {
			printf("%s: i2c write reg 0x%x failed, ret=%d\n",
			       __func__, priv->rtc_int_sts_reg, ret);
			return ret;
		}
		return alarm_trigger;
	} else {
		return priv->rtc_alarm_trigger;
	}
}

static struct rtc_ops rk8xx_rtc_ops = {
	.alarm_trigger = rk8xx_rtc_alarm_trigger,
};

static int rk8xx_rtc_probe(struct udevice *dev)
{
	struct rk8xx_priv *rk8xx = dev_get_priv(dev->parent);
	struct rk8xx_rtc_priv *priv = dev_get_priv(dev);
	int ret, val;

	priv->rtc_int_sts_reg = RK808_RTC_STATUS_REG;
	priv->rtc_int_msk_reg = RK808_RTC_INT_REG;
	switch (rk8xx->variant) {
	case RK808_ID:
	case RK818_ID:
		priv->int_msk_reg = RK808_INT_MSK_REG1;
		priv->int_sts_reg = RK808_INT_STS_REG1;
		break;
	case RK805_ID:
		priv->int_msk_reg = RK805_INT_MSK_REG;
		priv->int_sts_reg = RK805_INT_STS_REG;
		break;
	case RK816_ID:
		priv->int_msk_reg = RK816_INT_MSK_REG2;
		priv->int_sts_reg = RK816_INT_STS_REG2;
		break;
	case RK809_ID:
	case RK817_ID:
		priv->rtc_int_sts_reg = RK817_RTC_STATUS_REG;
		priv->rtc_int_msk_reg = RK817_RTC_INT_REG;
		priv->int_msk_reg = RK817_INT_MSK_REG0;
		priv->int_sts_reg = RK817_INT_STS_REG0;
		break;
	default:
		return -EINVAL;
	}

	priv->rtc_alarm_trigger = 0;
	priv->irq_is_busy = 0;
	/* mask and clear interrupt */
	val = pmic_reg_read(dev->parent, priv->int_msk_reg);
	if (val < 0) {
		printf("%s: i2c read reg 0x%x failed, ret=%d\n",
		       __func__, priv->int_msk_reg, val);
		return val;
	}
	ret = pmic_reg_write(dev->parent,
			     priv->int_msk_reg, val | 0xc1);
	if (ret < 0) {
		printf("%s: i2c write reg 0x%x failed, ret=%d\n",
		       __func__, priv->int_msk_reg, ret);
		return ret;
	}
	val = pmic_reg_read(dev->parent, priv->int_sts_reg);
	if (val < 0) {
		printf("%s: i2c read reg 0x%x failed, ret=%d\n",
		       __func__, priv->int_sts_reg, val);
		return val;
	}
	ret = pmic_reg_write(dev->parent,
			     priv->int_sts_reg,
			     val | (1 << RTC_ALARM_EN));
	if (ret < 0) {
		printf("%s: i2c write reg 0x%x failed, ret=%d\n",
		       __func__, priv->int_sts_reg, ret);
		return ret;
	}
	debug("%s: reg[0x%x] = 0x%x\n", __func__, priv->int_msk_reg,
	      pmic_reg_read(dev->parent, priv->int_msk_reg));
	debug("%s: reg[0x%x] = 0x%x\n", __func__, priv->int_sts_reg,
	      pmic_reg_read(dev->parent, priv->int_sts_reg));

	return rtc_interrupt_init(dev);
}

U_BOOT_DRIVER(rk8xx_rtc) = {
	.name   = "rk8xx_rtc",
	.id     = UCLASS_RTC,
	.probe  = rk8xx_rtc_probe,
	.ops	= &rk8xx_rtc_ops,
	.priv_auto_alloc_size = sizeof(struct rk8xx_rtc_priv),
};
