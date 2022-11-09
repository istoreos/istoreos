/*
 * (C) Copyright 2017 Rockchip Electronics Co., Ltd
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */

#include <common.h>
#include <asm/gic.h>
#include <config.h>
#include "irq-internal.h"

#define gicd_readl(offset)	readl((void *)GICD_BASE + (offset))
#define gicc_readl(offset)	readl((void *)GICC_BASE + (offset))
#define gicd_writel(v, offset)	writel(v, (void *)GICD_BASE + (offset))
#define gicc_writel(v, offset)	writel(v, (void *)GICC_BASE + (offset))

/* 64-bit write */
#define gicd_writeq(v, offset)	writeq(v, (void *)GICD_BASE + (offset))

#define IRQ_REG_X4(irq)		(4 * ((irq) / 4))
#define IRQ_REG_X16(irq)	(4 * ((irq) / 16))
#define IRQ_REG_X32(irq)	(4 * ((irq) / 32))
#define IRQ_REG_X4_OFFSET(irq)	((irq) % 4)
#define IRQ_REG_X16_OFFSET(irq)	((irq) % 16)
#define IRQ_REG_X32_OFFSET(irq)	((irq) % 32)

#define MPIDR_CPU_MASK		0xff

#define IROUTER_IRM_SHIFT	31
#define IROUTER_IRM_MASK	0x1
#define gicd_irouter_val_from_mpidr(mpidr, irm)		\
	((mpidr & ~(0xff << 24)) |			\
	 (irm & IROUTER_IRM_MASK) << IROUTER_IRM_SHIFT)

typedef enum INT_TRIG {
	INT_LEVEL_TRIGGER,
	INT_EDGE_TRIGGER
} eINT_TRIG;

struct gic_dist_data {
	uint32_t ctlr;
	uint32_t icfgr[DIV_ROUND_UP(1020, 16)];
	uint32_t itargetsr[DIV_ROUND_UP(1020, 4)];
	uint32_t ipriorityr[DIV_ROUND_UP(1020, 4)];
	uint32_t igroupr[DIV_ROUND_UP(1020, 32)];
	uint32_t ispendr[DIV_ROUND_UP(1020, 32)];
	uint32_t isenabler[DIV_ROUND_UP(1020, 32)];
};

struct gic_cpu_data {
	uint32_t ctlr;
	uint32_t pmr;
};

static struct gic_dist_data gicd_save;
static struct gic_cpu_data gicc_save;

static inline void int_set_prio_filter(u32 priority)
{
	gicc_writel(priority & 0xff, GICC_PMR);
}

static inline void int_enable_distributor(void)
{
	u32 val;

	val = gicd_readl(GICD_CTLR);
	val |= 0x01;
	gicd_writel(val, GICD_CTLR);
}

static inline void int_disable_distributor(void)
{
	u32 val;

	val = gicd_readl(GICD_CTLR);
	val &= ~0x01;
	gicd_writel(val, GICD_CTLR);
}

static inline void int_enable_secure_signal(void)
{
	u32 val;

	val = gicc_readl(GICC_CTLR);
	val |= 0x01;
	gicc_writel(val, GICC_CTLR);
}

static inline void int_disable_secure_signal(void)
{
	u32 val;

	val = gicc_readl(GICC_CTLR);
	val &= ~0x01;
	gicc_writel(val, GICC_CTLR);
}

static inline void int_enable_nosecure_signal(void)
{
	u32 val;

	val = gicc_readl(GICC_CTLR);
	val |= 0x02;
	gicc_writel(val, GICC_CTLR);
}

static inline void int_disable_nosecure_signal(void)
{
	u32 val;

	val = gicc_readl(GICC_CTLR);
	val &= ~0x02;
	gicc_writel(val, GICC_CTLR);
}

static int gic_irq_set_trigger(int irq, eINT_TRIG trig)
{
	u32 val;

	if (trig == INT_LEVEL_TRIGGER) {
		val = gicd_readl(GICD_ICFGR + IRQ_REG_X16(irq));
		val &= ~(1 << (2 * IRQ_REG_X16_OFFSET(irq) + 1));
		gicd_writel(val, GICD_ICFGR + IRQ_REG_X16(irq));
	} else {
		val = gicd_readl(GICD_ICFGR + IRQ_REG_X16(irq));
		val |= (1 << (2 * IRQ_REG_X16_OFFSET(irq) + 1));
		gicd_writel(val, GICD_ICFGR + IRQ_REG_X16(irq));
	}

	return 0;
}

static int gic_irq_enable(int irq)
{
#ifdef CONFIG_GICV2
	u32 val, cpu_mask;
	u32 shift = (irq % 4) * 8;

	if (irq >= PLATFORM_GIC_MAX_IRQ)
		return -EINVAL;

	/* set enable */
	val = gicd_readl(GICD_ISENABLERn + IRQ_REG_X32(irq));
	val |= 1 << IRQ_REG_X32_OFFSET(irq);
	gicd_writel(val, GICD_ISENABLERn + IRQ_REG_X32(irq));

	/* set target */
	cpu_mask = 1 << (read_mpidr() & MPIDR_CPU_MASK);
	val = gicd_readl(GICD_ITARGETSRn + IRQ_REG_X4(irq));
	val &= ~(0xFF << shift);
	val |= (cpu_mask << shift);
	gicd_writel(val, GICD_ITARGETSRn + IRQ_REG_X4(irq));
#else
	u32 val;
	u64 affinity_val;

	/* set enable */
	val = gicd_readl(GICD_ISENABLERn + IRQ_REG_X32(irq));
	val |= 1 << IRQ_REG_X32_OFFSET(irq);
	gicd_writel(val, GICD_ISENABLERn + IRQ_REG_X32(irq));

	/* set itouter(target) */
	affinity_val = gicd_irouter_val_from_mpidr(read_mpidr(), 0);
	gicd_writeq(affinity_val, GICD_IROUTERn + (irq << 3));
#endif

	return 0;
}

static int gic_irq_disable(int irq)
{
	gicd_writel(1 << IRQ_REG_X32_OFFSET(irq),
		    GICD_ICENABLERn + IRQ_REG_X32(irq));

	return 0;
}

/*
 * irq_set_type - set the irq trigger type for an irq
 *
 * @irq: irq number
 * @type: IRQ_TYPE_{LEVEL,EDGE}_* value - see asm/arch/irq.h
 */
static int gic_irq_set_type(int irq, unsigned int type)
{
	unsigned int int_type;

	switch (type) {
	case IRQ_TYPE_EDGE_RISING:
	case IRQ_TYPE_EDGE_FALLING:
		int_type = 0x1;
		break;
	case IRQ_TYPE_LEVEL_HIGH:
	case IRQ_TYPE_LEVEL_LOW:
		int_type = 0x0;
		break;
	default:
		return -EINVAL;
	}

	gic_irq_set_trigger(irq, int_type);

	return 0;
}

static void gic_irq_eoi(int irq)
{
#ifdef CONFIG_GICV2
	gicc_writel(irq, GICC_EOIR);
#else
	asm volatile("msr " __stringify(ICC_EOIR1_EL1) ", %0" : : "r" ((u64)irq));
	asm volatile("msr " __stringify(ICC_DIR_EL1) ", %0" : : "r" ((u64)irq));
	isb();
#endif
}

static int gic_irq_get(void)
{
#ifdef CONFIG_GICV2
	return gicc_readl(GICC_IAR) & 0x3fff; /* bit9 - bit0 */
#else
	u64 irqstat;

	asm volatile("mrs %0, " __stringify(ICC_IAR1_EL1) : "=r" (irqstat));
	return (u32)irqstat & 0x3ff;
#endif
}

static int gic_irq_suspend(void)
{
	int irq_nr, i, irq;
#ifndef CONFIG_GICV2
	u32 reg;
#endif
	/* irq nr */
	irq_nr = ((gicd_readl(GICD_TYPER) & 0x1f) + 1) * 32;
	if (irq_nr > 1020)
		irq_nr = 1020;

	/* GICC save */
#ifdef CONFIG_GICV2
	gicc_save.ctlr = gicc_readl(GICC_CTLR);
	gicc_save.pmr = gicc_readl(GICC_PMR);
#else
	asm volatile("mrs %0, " __stringify(ICC_CTLR_EL1) : "=r" (reg));
	gicc_save.ctlr = reg;
	asm volatile("mrs %0, " __stringify(ICC_PMR_EL1) : "=r" (reg));
	gicc_save.pmr = reg;
#endif

	/* GICD save */
	gicd_save.ctlr = gicd_readl(GICD_CTLR);

	for (i = 0, irq = 0; irq < irq_nr; irq += 16)
		gicd_save.icfgr[i++] =
			gicd_readl(GICD_ICFGR + IRQ_REG_X16(irq));

	for (i = 0, irq = 0; irq < irq_nr; irq += 4)
		gicd_save.itargetsr[i++] =
			gicd_readl(GICD_ITARGETSRn + IRQ_REG_X4(irq));

	for (i = 0, irq = 0; irq < irq_nr; irq += 4)
		gicd_save.ipriorityr[i++] =
			gicd_readl(GICD_IPRIORITYRn + IRQ_REG_X4(irq));

	for (i = 0, irq = 0; irq < irq_nr; irq += 32)
		gicd_save.igroupr[i++] =
			gicd_readl(GICD_IGROUPRn + IRQ_REG_X32(irq));

	for (i = 0, irq = 0; irq < irq_nr; irq += 32)
		gicd_save.ispendr[i++] =
			gicd_readl(GICD_ISPENDRn + IRQ_REG_X32(irq));

	for (i = 0, irq = 0; irq < irq_nr; irq += 32)
		gicd_save.isenabler[i++] =
			gicd_readl(GICD_ISENABLERn + IRQ_REG_X32(irq));

	dsb();

	return 0;
}

static int gic_irq_resume(void)
{
	int irq_nr, i, irq;
#ifndef CONFIG_GICV2
	u32 reg;
#endif
	irq_nr = ((gicd_readl(GICD_TYPER) & 0x1f) + 1) * 32;
	if (irq_nr > 1020)
		irq_nr = 1020;

	/* Disable ctrl register */
#ifdef CONFIG_GICV2
	gicc_writel(0, GICC_CTLR);
#else
	reg = 0;
	asm volatile("msr " __stringify(ICC_CTLR_EL1) ", %0" : : "r" (reg));
#endif
	gicd_writel(0, GICD_CTLR);
	dsb();

	/* Clear all interrupt */
	for (i = 0, irq = 0; irq < irq_nr; irq += 32)
		gicd_writel(0xffffffff,
			    GICD_ICENABLERn + IRQ_REG_X32(irq));

	for (i = 0, irq = 0; irq < irq_nr; irq += 16)
		gicd_writel(gicd_save.icfgr[i++],
			    GICD_ICFGR + IRQ_REG_X16(irq));

	for (i = 0, irq = 0; irq < irq_nr; irq += 4)
		gicd_writel(gicd_save.itargetsr[i++],
			    GICD_ITARGETSRn + IRQ_REG_X4(irq));

	for (i = 0, irq = 0; irq < irq_nr; irq += 4)
		gicd_writel(gicd_save.ipriorityr[i++],
			    GICD_IPRIORITYRn + IRQ_REG_X4(irq));

	for (i = 0, irq = 0; irq < irq_nr; irq += 32)
		gicd_writel(gicd_save.igroupr[i++],
			    GICD_IGROUPRn + IRQ_REG_X32(irq));

	for (i = 0, irq = 0; irq < irq_nr; irq += 32)
		gicd_writel(gicd_save.isenabler[i++],
			    GICD_ISENABLERn + IRQ_REG_X32(irq));

	for (i = 0, irq = 0; irq < irq_nr; irq += 32)
		gicd_writel(gicd_save.ispendr[i++],
			    GICD_ISPENDRn + IRQ_REG_X32(irq));

	dsb();
#ifdef CONFIG_GICV2
	gicc_writel(gicc_save.pmr, GICC_PMR);
	gicc_writel(gicc_save.ctlr, GICC_CTLR);
#else
	reg = gicc_save.pmr;
	asm volatile("msr " __stringify(ICC_PMR_EL1) ", %0" : : "r" (reg));
	reg = gicc_save.ctlr;
	asm volatile("msr " __stringify(ICC_CTLR_EL1) ", %0" : : "r" (reg));
#endif
	gicd_writel(gicd_save.ctlr, GICD_CTLR);
	dsb();

#if defined(CONFIG_GICV3)
	asm volatile("msr " __stringify(ICC_IGRPEN1_EL1) ", %0" : : "r" (1));
	dsb();
#endif

	return 0;
}

/**************************************regs save and resume**************************/
static int gic_irq_init(void)
{
	/* GICV3 done in: arch/arm/cpu/armv8/start.S */
#ifdef CONFIG_GICV2
	u32 val;

	/*
	 * If system boot without Miniloader:
	 *		"Maskrom => Trust(optional) => U-Boot"
	 *
	 * IRQ_USB_OTG must be acked by GICC_EIO due to maskrom jumps to the
	 * U-Boot in its USB interrupt. Without this ack, the GICC_IAR always
	 * return a spurious interrupt ID 1023 for USB OTG interrupt.
	 */
#ifdef IRQ_USB_OTG
	gicc_writel(IRQ_USB_OTG, GICC_EOIR);
#endif

	/* disable gicc and gicd */
	gicc_writel(0, GICC_CTLR);
	gicd_writel(0, GICD_CTLR);

	/* disable interrupt */
	gicd_writel(0xffffffff, GICD_ICENABLERn + 0);
	gicd_writel(0xffffffff, GICD_ICENABLERn + 4);
	gicd_writel(0xffffffff, GICD_ICENABLERn + 8);
	gicd_writel(0xffffffff, GICD_ICENABLERn + 12);

	val = gicd_readl(GICD_ICFGR + 12);
	val &= ~(1 << 1);
	gicd_writel(val, GICD_ICFGR + 12);

	/* set interrupt priority threhold min: 256 */
	int_set_prio_filter(0xff);
	int_enable_secure_signal();
	int_enable_nosecure_signal();
	int_enable_distributor();
#endif

	return 0;
}

static struct irq_chip gic_irq_chip = {
	.name		= "gic-irq-chip",
	.irq_init	= gic_irq_init,
	.irq_suspend	= gic_irq_suspend,
	.irq_resume	= gic_irq_resume,
	.irq_get	= gic_irq_get,
	.irq_enable	= gic_irq_enable,
	.irq_disable	= gic_irq_disable,
	.irq_eoi	= gic_irq_eoi,
	.irq_set_type	= gic_irq_set_type,
};

struct irq_chip *arch_gic_get_irqchip(void)
{
	return &gic_irq_chip;
}
