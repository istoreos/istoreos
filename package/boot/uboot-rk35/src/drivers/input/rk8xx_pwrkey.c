/*
 * (C) Copyright 2017 Rockchip Electronics Co., Ltd
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */

#include <common.h>
#include <dm.h>
#include <key.h>
#include <linux/input.h>
#include <power/rk8xx_pmic.h>
#include <irq-generic.h>

static void rk8xx_pwron_rise_handler(int irq, void *data)
{
	struct udevice *dev = data;
	struct dm_key_uclass_platdata *key;

	key = dev_get_uclass_platdata(dev);
	key->rise_ms = key_timer(0);

	debug("%s: %llu ms\n", __func__, key->rise_ms);
}

static void rk8xx_pwron_fall_handler(int irq, void *data)
{
	struct udevice *dev = data;
	struct dm_key_uclass_platdata *key;

	key = dev_get_uclass_platdata(dev);
	key->fall_ms = key_timer(0);

	debug("%s: %llu ms\n", __func__, key->fall_ms);
}

static int rk8xx_pwrkey_probe(struct udevice *dev)
{
	struct rk8xx_priv *rk8xx = dev_get_priv(dev->parent);
	struct dm_key_uclass_platdata *key = dev_get_uclass_platdata(dev);
	int fall_irq, rise_irq;

	if (!rk8xx->irq_chip) {
		printf("Failed to get parent irq chip\n");
		return -ENOENT;
	}

	fall_irq = virq_to_irq(rk8xx->irq_chip, RK8XX_IRQ_PWRON_FALL);
	if (fall_irq < 0) {
		printf("Failed to register pwron fall irq, ret=%d\n", fall_irq);
		return fall_irq;
	}

	rise_irq = virq_to_irq(rk8xx->irq_chip, RK8XX_IRQ_PWRON_RISE);
	if (rise_irq < 0) {
		printf("Failed to register pwron rise irq, ret=%d\n", rise_irq);
		return rise_irq;
	}

	key->name = "rk8xx_pwr";
	key->type = GPIO_KEY;
	key->code = KEY_POWER;
	key->skip_irq_init = 1;

	irq_install_handler(fall_irq, rk8xx_pwron_fall_handler, dev);
	irq_install_handler(rise_irq, rk8xx_pwron_rise_handler, dev);
	irq_handler_enable(fall_irq);
	irq_handler_enable(rise_irq);

	return 0;
}

U_BOOT_DRIVER(rk8xx_pwrkey) = {
	.name   = "rk8xx_pwrkey",
	.id     = UCLASS_KEY,
	.probe  = rk8xx_pwrkey_probe,
};
