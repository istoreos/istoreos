/*
 * (C) Copyright 2017 Rockchip Electronics Co., Ltd
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */

#include <asm/io.h>
#include <asm/u-boot-arm.h>
#include <dm.h>
#include <irq-generic.h>
#include "irq-internal.h"

DECLARE_GLOBAL_DATA_PTR;

struct irq_desc {
	interrupt_handler_t *handle_irq;
	void *data;
	u32 flag;
	u32 count;
};

struct irqchip_desc {
	struct irq_chip *gic;
	struct irq_chip *gpio;
	struct irq_chip *virq;

	int suspend_irq[PLATFORM_SUSPEND_MAX_IRQ];
	int suspend_num;
};

static struct irq_desc irq_desc[PLATFORM_MAX_IRQ];
static struct irqchip_desc irqchip;
static bool intr_setup;

int bad_irq(int irq)
{
	if (!intr_setup) {
		IRQ_W("Interrupt framework is not setup\n");
		return -EINVAL;
	}

	if (irq < PLATFORM_MAX_IRQ) {
		if (!irq_desc[irq].handle_irq)
			return -EINVAL;
	} else {
		if (bad_virq(irq)) {
			IRQ_E("Unknown virq: %d\n", irq);
			return -EINVAL;
		}
	}

	return 0;
}

/* general interrupt handler for gpio chip */
void __generic_gpio_handle_irq(int irq)
{
	if (bad_irq(irq))
		return;

	if (irq < PLATFORM_GIC_MAX_IRQ) {
		IRQ_W("IRQ %d: Invalid GPIO irq\n", irq);
		return;
	}

	if (irq_desc[irq].handle_irq) {
		irq_desc[irq].count++;
		irq_desc[irq].handle_irq(irq, irq_desc[irq].data);
	}
}

void __do_generic_irq_handler(void)
{
	u32 irq;

	assert(irqchip.gic->irq_get);
	assert(irqchip.gic->irq_eoi);

	irq = irqchip.gic->irq_get();

	if (irq < PLATFORM_GIC_MAX_IRQ) {
		if (irq_desc[irq].handle_irq) {
			irq_desc[irq].count++;
			irq_desc[irq].handle_irq(irq, irq_desc[irq].data);
		}
	}

	irqchip.gic->irq_eoi(irq);
}

int irq_is_busy(int irq)
{
	return (irq >= 0 && irq_desc[irq].handle_irq) ? -EBUSY : 0;
}

static int bad_irq_chip(struct irq_chip *chip)
{
	return (!chip->name || !chip->irq_init || !chip->irq_enable ||
		!chip->irq_disable) ? -EINVAL : 0;
}

static int __do_arch_irq_init(void)
{
	int ret = -EINVAL;

	/* After relocation done, bss data intr_setup */
	if (!(gd->flags & GD_FLG_RELOC)) {
		IRQ_W("Interrupt framework should initialize after reloc\n");
		return -EINVAL;
	}

	/*
	 * We set true before arch_gpio_irq_init() to avoid fail when
	 * request irq for gpio banks.
	 */
	intr_setup = true;
	memset(irq_desc, 0, sizeof(irq_desc));

	irqchip.gic = arch_gic_get_irqchip();
	if (bad_irq_chip(irqchip.gic)) {
		IRQ_E("Bad gic irqchip\n");
		goto out;
	}

	irqchip.gpio = arch_gpio_get_irqchip();
	if (bad_irq_chip(irqchip.gpio)) {
		IRQ_E("Bad gpio irqchip\n");
		goto out;
	}

	irqchip.virq = arch_virq_get_irqchip();
	if (bad_irq_chip(irqchip.virq)) {
		IRQ_E("Bad virq irqchip\n");
		goto out;
	}

	ret = irqchip.gic->irq_init();
	if (ret) {
		IRQ_E("GIC Interrupt setup failed, ret=%d\n", ret);
		goto out;
	}

	ret = irqchip.gpio->irq_init();
	if (ret) {
		IRQ_E("GPIO Interrupt setup failed, ret=%d\n", ret);
		goto out;
	}

	ret = irqchip.virq->irq_init();
	if (ret) {
		IRQ_E("VIRQ Interrupt setup failed, ret=%d\n", ret);
		goto out;
	}

	return 0;

out:
	intr_setup = false;

	return ret;
}

int irq_handler_enable(int irq)
{
	int ret;

	if (bad_irq(irq))
		return -EINVAL;

	if (irq < PLATFORM_GIC_MAX_IRQ)
		ret = irqchip.gic->irq_enable(irq);
	else if (irq < PLATFORM_GPIO_MAX_IRQ)
		ret = irqchip.gpio->irq_enable(irq);
	else
		ret = irqchip.virq->irq_enable(irq);

	if (!ret && irq < PLATFORM_MAX_IRQ)
		irq_desc[irq].flag |= IRQ_FLG_ENABLE;

	return ret;
}

int irq_handler_disable(int irq)
{
	int ret;

	if (bad_irq(irq))
		return -EINVAL;

	if (irq < PLATFORM_GIC_MAX_IRQ)
		ret = irqchip.gic->irq_disable(irq);
	else if (irq < PLATFORM_GPIO_MAX_IRQ)
		ret = irqchip.gpio->irq_disable(irq);
	else
		ret = irqchip.virq->irq_disable(irq);

	if (!ret && irq < PLATFORM_MAX_IRQ)
		irq_desc[irq].flag &= ~IRQ_FLG_ENABLE;

	return ret;
}

int irq_set_irq_type(int irq, unsigned int type)
{
	if (bad_irq(irq))
		return -EINVAL;

	if (irq < PLATFORM_GIC_MAX_IRQ)
		return irqchip.gic->irq_set_type(irq, type);
	else if (irq < PLATFORM_GPIO_MAX_IRQ)
		return irqchip.gpio->irq_set_type(irq, type);
	else
		return -ENOSYS;
}

int irq_revert_irq_type(int irq)
{
	if (bad_irq(irq))
		return -EINVAL;

	if (irq < PLATFORM_GIC_MAX_IRQ)
		return 0;
	else if (irq < PLATFORM_GPIO_MAX_IRQ)
		return irqchip.gpio->irq_revert_type(irq);
	else
		return -ENOSYS;
}

int irq_get_gpio_level(int irq)
{
	if (bad_irq(irq))
		return -EINVAL;

	if (irq < PLATFORM_GIC_MAX_IRQ)
		return 0;
	else if (irq < PLATFORM_GPIO_MAX_IRQ)
		return irqchip.gpio->irq_get_gpio_level(irq);
	else
		return -ENOSYS;
}

void irq_install_handler(int irq, interrupt_handler_t *handler, void *data)
{
	if (!intr_setup) {
		IRQ_W("Interrupt framework is not intr_setup\n");
		return;
	}

	if (irq < PLATFORM_MAX_IRQ) {
		if (!handler || irq_desc[irq].handle_irq)
			return;
		irq_desc[irq].handle_irq = handler;
		irq_desc[irq].data = data;
	} else {
		virq_install_handler(irq, handler, data);
	}
}

void irq_free_handler(int irq)
{
	if (irq_handler_disable(irq))
		return;

	if (irq < PLATFORM_MAX_IRQ) {
		irq_desc[irq].handle_irq = NULL;
		irq_desc[irq].data = NULL;
	} else {
		virq_free_handler(irq);
	}
}

int irq_handler_enable_suspend_only(int irq)
{
	if (bad_irq(irq))
		return -EINVAL;

	if (irqchip.suspend_num >= PLATFORM_SUSPEND_MAX_IRQ) {
		printf("Over max count(%d) of suspend irq\n",
		       PLATFORM_SUSPEND_MAX_IRQ);
		return -EPERM;
	}

	irqchip.suspend_irq[irqchip.suspend_num++] = irq;
	return 0;
}

int irqs_suspend(void)
{
	int i;

	for (i = 0; i < irqchip.suspend_num; i++)
		irq_handler_enable(irqchip.suspend_irq[i]);

	return irqchip.gic->irq_suspend();
}

int irqs_resume(void)
{
	int i;

	for (i = 0; i < irqchip.suspend_num; i++)
		irq_handler_disable(irqchip.suspend_irq[i]);

	return irqchip.gic->irq_resume();
}

#ifdef CONFIG_ARM64
void do_irq(struct pt_regs *pt_regs, unsigned int esr)
{
#ifdef CONFIG_ROCKCHIP_DEBUGGER
	printf("\n>>> Rockchip Debugger:\n");
	show_regs(pt_regs);
#endif

	__do_generic_irq_handler();
}
#else
void do_irq(struct pt_regs *pt_regs)
{
#ifdef CONFIG_ROCKCHIP_DEBUGGER
	printf("\n>>> Rockchp Debugger:\n");
	show_regs(pt_regs);
#endif

	__do_generic_irq_handler();
}
#endif

int arch_interrupt_init(void)
{
#ifndef CONFIG_ARM64
	unsigned long cpsr __maybe_unused;

	/* stack has been reserved in: arch_reserve_stacks() */
	IRQ_STACK_START = gd->irq_sp;
	IRQ_STACK_START_IN = gd->irq_sp;

	__asm__ __volatile__("mrs %0, cpsr\n"
			     : "=r" (cpsr)
			     :
			     : "memory");

	__asm__ __volatile__("msr cpsr_c, %0\n"
			     "mov sp, %1\n"
			     :
			     : "r" (IRQ_MODE | I_BIT |
				    F_BIT | (cpsr & ~FIQ_MODE)),
			       "r" (IRQ_STACK_START)
			     : "memory");

	__asm__ __volatile__("msr cpsr_c, %0"
			     :
			     : "r" (cpsr)
			     : "memory");
#endif
	return __do_arch_irq_init();
}

int interrupt_init(void)
{
	return arch_interrupt_init();
}

void enable_interrupts(void)
{
	local_irq_enable();
}

int disable_interrupts(void)
{
	int flags;

	local_irq_save(flags);
	return flags;
}

static int do_dump_irqs(cmd_tbl_t *cmdtp, int flag,
			int argc, char * const argv[])

{
	struct udevice *dev;
	char *drv_name;
	int pirq;

	printf(" IRQ    En    Handler       Driver         Name              Trig\n");
	printf("----------------------------------------------------------------------\n");

	for (pirq = 0; pirq < PLATFORM_MAX_IRQ; pirq++) {
		if (!irq_desc[pirq].handle_irq)
			continue;

		dev = (struct udevice *)irq_desc[pirq].data;
		if (strstr(dev->name, "gpio"))
			drv_name = "IRQ";
		else
			drv_name = dev->driver->name;

		printf(" %3d	%d     0x%08lx    %-12s    %-12s       %d\n",
		       pirq, irq_desc[pirq].flag & IRQ_FLG_ENABLE ? 1 : 0,
		       (ulong)irq_desc[pirq].handle_irq,
		       drv_name, dev->name, irq_desc[pirq].count);

		virqs_show(pirq);
	}

	return 0;
}

U_BOOT_CMD(
	dump_irqs, 1, 1, do_dump_irqs, "Dump IRQs", ""
);
