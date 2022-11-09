/*
 * (C) Copyright 2017 Rockchip Electronics Co., Ltd
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */

#ifndef _IRQ_GIC_H_
#define _IRQ_GIC_H_

#include <asm/io.h>
#include <irq-generic.h>
#include <irq-platform.h>
#include "irq-internal.h"

/*
 * IRQ FLAG
 */
#define IRQ_FLG_ENABLE			BIT(0)

/*
 * IRQ-NUMBERS
 */
#define PLATFORM_SUSPEND_MAX_IRQ	12
#define PLATFORM_GIC_MAX_IRQ		(GIC_IRQS_NR)
#define PLATFORM_GPIO_MAX_IRQ		(GIC_IRQS_NR + GPIO_IRQS_NR)
#define PLATFORM_MAX_IRQ		(GIC_IRQS_NR + GPIO_IRQS_NR)

/*
 * IRQ-CHIP
 */
struct irq_chip *arch_gic_get_irqchip(void);
struct irq_chip *arch_gpio_get_irqchip(void);
struct irq_chip *arch_virq_get_irqchip(void);

/*
 * IRQ-VIRTUAL
 */
int bad_virq(int irq);
void virqs_show(int pirq);
void virq_free_handler(int irq);
int virq_install_handler(int irq, interrupt_handler_t *handler, void *data);

/*
 * Other
 */
int bad_irq(int irq);

/*
 * IRQ-GPIO-SWITCH
 */
#define GPIO_BANK_MASK		0xFFFFFF00
#define GPIO_BANK_OFFSET	8
#define GPIO_PIN_MASK		0x000000FF
#define GPIO_PIN_OFFSET		0
#define EINVAL_GPIO		-1
#define PIN_BASE		GIC_IRQS_NR

struct gpio_bank {
	char *name;
	void __iomem *regbase;
	int id;
	int irq_base;
	int ngpio;
	int use_count;
};

#define GPIO_BANK_REGISTER(ID, GPIO_BANK_NUM)			\
{								\
	.name	  = __stringify(gpio##ID),			\
	.regbase  = (unsigned char __iomem *)GPIO##ID##_PHYS,	\
	.id	  = ID,						\
	.irq_base = PIN_BASE + (ID) * (GPIO_BANK_NUM),		\
	.ngpio    = GPIO_BANK_NUM,				\
	.use_count = 0						\
}

/* gpio bank[31:8] and pin[7:0] */
#define GPIO_BANK(gpio)		((gpio & GPIO_BANK_MASK) >> GPIO_BANK_OFFSET)
#define GPIO_PIN(gpio)		((gpio & GPIO_PIN_MASK) >> GPIO_PIN_OFFSET)
#define GPIO_BANK_VALID(gpio)	(GPIO_BANK(gpio) < GPIO_BANK_NUM)
#define GPIO_PIN_VALID(gpio)	(GPIO_PIN(gpio) < GPIO_BANK_PINS)

int hard_gpio_to_irq(u32 gpio);
int irq_to_gpio(int irq);
struct gpio_bank *gpio_id_to_bank(unsigned int id);
struct gpio_bank *gpio_to_bank(unsigned gpio);

void __generic_gpio_handle_irq(int irq);

#endif /* _IRQ_GIC_H_ */
