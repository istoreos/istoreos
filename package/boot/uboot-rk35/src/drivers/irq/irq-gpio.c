/*
 * (C) Copyright 2017 Rockchip Electronics Co., Ltd
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */

#include <dm.h>
#include <malloc.h>
#include "irq-internal.h"

typedef enum GPIOIntType {
	GPIOLevelLow = 0,
	GPIOLevelHigh,
	GPIOEdgelFalling,
	GPIOEdgelRising
} eGPIOIntType_t;

typedef enum eGPIOPinLevel {
	GPIO_LOW = 0,
	GPIO_HIGH
} eGPIOPinLevel_t;

typedef enum eGPIOPinDirection {
	GPIO_IN = 0,
	GPIO_OUT
} eGPIOPinDirection_t;

#define GPIO_SWPORT_DR		0x00
#define GPIO_SWPORT_DDR		0x04
#define GPIO_INTEN		0x30
#define GPIO_INTMASK		0x34
#define GPIO_INTTYPE_LEVEL	0x38
#define GPIO_INT_POLARITY	0x3c
#define GPIO_INT_STATUS		0x40
#define GPIO_INT_RAWSTATUS	0x44
#define GPIO_DEBOUNCE		0x48
#define GPIO_PORTS_EOI		0x4c
#define GPIO_EXT_PORT		0x50
#define GPIO_LS_SYNC		0x60

static inline unsigned pin_to_bit(unsigned pin)
{
	return (1 << pin);
}

static inline unsigned offset_to_bit(unsigned offset)
{
	return (1 << offset);
}

static void gpio_bit_op(void __iomem *regbase, unsigned int offset,
			u32 bit, unsigned char flag)
{
	u32 val = readl(regbase + offset);

	if (flag)
		val |= bit;
	else
		val &= ~bit;

	writel(val, regbase + offset);
}

static int gpio_bit_rd(void __iomem *regbase, unsigned int offset, u32 bit)
{
	return readl(regbase + offset) & bit ? 1 : 0;
}

static void gpio_irq_unmask(void __iomem *regbase, unsigned int bit)
{
	gpio_bit_op(regbase, GPIO_INTEN, bit, 1);
}

static void gpio_irq_mask(void __iomem *regbase, unsigned int bit)
{
	gpio_bit_op(regbase, GPIO_INTEN, bit, 0);
}

static void gpio_irq_ack(void __iomem *regbase, unsigned int bit)
{
	gpio_bit_op(regbase, GPIO_PORTS_EOI, bit, 1);
}

static void generic_gpio_handle_irq(int irq, void *data __always_unused)
{
	struct gpio_bank *bank = gpio_id_to_bank(irq - IRQ_GPIO0);
	unsigned gpio_irq, pin, unmasked = 0;
	u32 isr, ilr;

	isr = readl(bank->regbase + GPIO_INT_STATUS);
	ilr = readl(bank->regbase + GPIO_INTTYPE_LEVEL);

	gpio_irq = bank->irq_base;

	while (isr) {
		pin = fls(isr) - 1;

		/* first mask and ack irq */
		gpio_irq_mask(bank->regbase, offset_to_bit(pin));
		gpio_irq_ack(bank->regbase, offset_to_bit(pin));

		/*
		 * If gpio is edge triggered, clear condition before executing
		 * the handler, so that we don't miss next edges trigger.
		 */
		if (ilr & (1 << pin)) {
			unmasked = 1;
			gpio_irq_unmask(bank->regbase, offset_to_bit(pin));
		}

		__generic_gpio_handle_irq(gpio_irq + pin);

		isr &= ~(1 << pin);

		if (!unmasked)
			gpio_irq_unmask(bank->regbase, offset_to_bit(pin));
	}
}

static void gpio_set_intr_type(void __iomem *regbase,
			       unsigned int bit,
			       eGPIOIntType_t type)
{
	switch (type) {
	case GPIOLevelLow:
		gpio_bit_op(regbase, GPIO_INT_POLARITY, bit, 0);
		gpio_bit_op(regbase, GPIO_INTTYPE_LEVEL, bit, 0);
		break;
	case GPIOLevelHigh:
		gpio_bit_op(regbase, GPIO_INTTYPE_LEVEL, bit, 0);
		gpio_bit_op(regbase, GPIO_INT_POLARITY, bit, 1);
		break;
	case GPIOEdgelFalling:
		gpio_bit_op(regbase, GPIO_INTTYPE_LEVEL, bit, 1);
		gpio_bit_op(regbase, GPIO_INT_POLARITY, bit, 0);
		break;
	case GPIOEdgelRising:
		gpio_bit_op(regbase, GPIO_INTTYPE_LEVEL, bit, 1);
		gpio_bit_op(regbase, GPIO_INT_POLARITY, bit, 1);
		break;
	}
}

static int gpio_get_intr_type(void __iomem *regbase,
			      unsigned int bit)
{
	u32 polarity, level, magic = 0;
	int type;

	polarity = gpio_bit_rd(regbase, GPIO_INT_POLARITY, bit);
	level = gpio_bit_rd(regbase, GPIO_INTTYPE_LEVEL, bit);
	magic = (polarity << 1) | (level << 0);

	switch (magic) {
	case 0x00:
		type = GPIOLevelLow;
		break;
	case 0x02:
		type = GPIOLevelHigh;
		break;
	case 0x01:
		type = GPIOEdgelFalling;
		break;
	case 0x03:
		type = GPIOEdgelRising;
		break;
	default:
		type = -EINVAL;
	}

	return type;
}

static int gpio_irq_set_type(int gpio_irq, unsigned int type)
{
	int gpio = irq_to_gpio(gpio_irq);
	struct gpio_bank *bank = gpio_to_bank(gpio);
	eGPIOIntType_t int_type = 0;

	if (!bank)
		return -EINVAL;

	gpio &= GPIO_PIN_MASK;
	if (gpio >= bank->ngpio)
		return -EINVAL;

	switch (type) {
	case IRQ_TYPE_EDGE_RISING:
		int_type = GPIOEdgelRising;
		break;
	case IRQ_TYPE_EDGE_FALLING:
		int_type = GPIOEdgelFalling;
		break;
	case IRQ_TYPE_LEVEL_HIGH:
		int_type = GPIOLevelHigh;
		break;
	case IRQ_TYPE_LEVEL_LOW:
		int_type = GPIOLevelLow;
		break;
	default:
		return -EINVAL;
	}

	/* Before set interrupt type, gpio must set input */
	gpio_bit_op(bank->regbase, GPIO_SWPORT_DDR,
		    offset_to_bit(gpio), GPIO_IN);
	gpio_set_intr_type(bank->regbase, offset_to_bit(gpio), int_type);

	return 0;
}

static int gpio_irq_revert_type(int gpio_irq)
{
	int gpio = irq_to_gpio(gpio_irq);
	struct gpio_bank *bank = gpio_to_bank(gpio);
	eGPIOIntType_t int_type = 0;
	int type;

	if (!bank)
		return -EINVAL;

	gpio &= GPIO_PIN_MASK;
	if (gpio >= bank->ngpio)
		return -EINVAL;

	type = gpio_get_intr_type(bank->regbase, offset_to_bit(gpio));
	switch (type) {
	case GPIOEdgelFalling:
		int_type = GPIOEdgelRising;
		break;
	case GPIOEdgelRising:
		int_type = GPIOEdgelFalling;
		break;
	case GPIOLevelHigh:
		int_type = GPIOLevelLow;
		break;
	case GPIOLevelLow:
		int_type = GPIOLevelHigh;
		break;
	default:
		return -EINVAL;
	}

	gpio_set_intr_type(bank->regbase, offset_to_bit(gpio), int_type);

	return 0;
}

static int gpio_irq_get_gpio_level(int gpio_irq)
{
	int gpio = irq_to_gpio(gpio_irq);
	struct gpio_bank *bank = gpio_to_bank(gpio);

	if (!bank)
		return -EINVAL;

	gpio &= GPIO_PIN_MASK;
	if (gpio >= bank->ngpio)
		return -EINVAL;

	return gpio_bit_rd(bank->regbase, GPIO_EXT_PORT, offset_to_bit(gpio));
}

static int gpio_irq_enable(int gpio_irq)
{
	int gpio = irq_to_gpio(gpio_irq);
	struct gpio_bank *bank = gpio_to_bank(gpio);

	if (!bank)
		return -EINVAL;

	gpio &= GPIO_PIN_MASK;
	if (gpio >= bank->ngpio)
		return -EINVAL;

	gpio_irq_unmask(bank->regbase, offset_to_bit(gpio));

	if (bank->use_count == 0)
		irq_handler_enable(IRQ_GPIO0 + bank->id);
	bank->use_count++;

	return 0;
}

static int gpio_irq_disable(int irq)
{
	int gpio = irq_to_gpio(irq);
	struct gpio_bank *bank = gpio_to_bank(gpio);

	if (!bank)
		return -EINVAL;

	if (bank->use_count <= 0)
		return 0;

	gpio &= GPIO_PIN_MASK;
	if (gpio >= bank->ngpio)
		return -EINVAL;

	gpio_irq_mask(bank->regbase, offset_to_bit(gpio));

	if (bank->use_count == 1)
		irq_handler_disable(IRQ_GPIO0 + bank->id);
	bank->use_count--;

	return 0;
}

static int gpio_irq_init(void)
{
	struct gpio_bank *bank = NULL;
	int i = 0;

	for (i = 0; i < GPIO_BANK_NUM; i++) {
		struct udevice *dev;

		dev = malloc(sizeof(*dev));
		if (!dev)
			return -ENOMEM;

		bank = gpio_id_to_bank(i);
		if (bank) {
			dev->name = bank->name;

			/* disable gpio pin interrupt */
			writel(0, bank->regbase + GPIO_INTEN);

			/* register gpio group irq handler */
			irq_install_handler(IRQ_GPIO0 + bank->id,
			(interrupt_handler_t *)generic_gpio_handle_irq, dev);

			/* default disable all gpio group interrupt */
			irq_handler_disable(IRQ_GPIO0 + bank->id);
		}
	}

	return 0;
}

static struct irq_chip gpio_irq_chip = {
	.name		= "gpio-irq-chip",
	.irq_init	= gpio_irq_init,
	.irq_enable	= gpio_irq_enable,
	.irq_disable	= gpio_irq_disable,
	.irq_set_type	= gpio_irq_set_type,
	.irq_revert_type = gpio_irq_revert_type,
	.irq_get_gpio_level = gpio_irq_get_gpio_level,
};

struct irq_chip *arch_gpio_get_irqchip(void)
{
	return &gpio_irq_chip;
}
