// SPDX-License-Identifier: GPL-2.0-only
/*
 * Compatible with the IOMMU of av1 decode
 *
 * Module Authors:	Yandong Lin <yandong.lin@rock-chips.com>
 *			Simon Xue <xxm@rock-chips.com>
 */

#include <linux/clk.h>
#include <linux/compiler.h>
#include <linux/delay.h>
#include <linux/device.h>
#include <linux/dma-mapping.h>
#include <linux/dma-map-ops.h>
#include <linux/errno.h>
#include <linux/interrupt.h>
#include <linux/io.h>
#include <linux/iommu.h>
#include <linux/iopoll.h>
#include <linux/list.h>
#include <linux/mm.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/of.h>
#include <linux/of_iommu.h>
#include <linux/of_platform.h>
#include <linux/platform_device.h>
#include <linux/pm_runtime.h>
#include <linux/slab.h>
#include <linux/spinlock.h>
#include "rockchip_iommu.h"

struct av1d_iommu {
	struct device *dev;
	void __iomem **bases;
	int num_mmu;
	int num_irq;
	struct clk_bulk_data *clocks;
	int num_clocks;
	struct iommu_device iommu;
	struct iommu_domain *domain; /* domain to which iommu is attached */
	struct iommu_group *group;

	u32 *dt; /* page directory table */
	dma_addr_t dt_dma;
	spinlock_t iommus_lock; /* lock for iommus list */
	spinlock_t dt_lock; /* lock for modifying page directory table */
	/* for av1 iommu */
	u64 *pta; /* page directory table */
	dma_addr_t pta_dma;
};

#define RK_IOMMU_AV1	0xa
#define NUM_DT_ENTRIES	1024
#define NUM_PT_ENTRIES	1024

#define SPAGE_ORDER	12
#define SPAGE_SIZE	(1 << SPAGE_ORDER)

/* av1 iommu regs address */
#define AV1_CLOCK_CTRL_BASE			0x0
#define AV1_IDLE_ST_BASE			0x4
#define AV1_MMU_CONFIG0_BASE			0x184
#define AV1_MMU_CONFIG1_BASE			0x1ac
#define AV1_MMU_AHB_EXCEPTION_BASE		0x380
#define AV1_MMU_AHB_STATUS_BASE			0x384
#define AV1_MMU_AHB_CONTROL_BASE		0x388
#define AV1_MMU_AHB_TBL_ARRAY_BASE_L_BASE	0x38C
#define AV1_MMU_AHB_TBL_ARRAY_BASE_H_BASE	0x390
#define AV1_MMU_AHB_CTX_PD_BASE			0x3b4
#define AV1_MMU_BUTT_BASE			0xffff

/* MMU register offsets */
#define AV1_MMU_FLUSH_BASE		0x184
#define AV1_MMU_BIT_FLUSH		BIT(4)

#define AV1_MMU_PAGE_FAULT_ADDR		0x380
#define AV1_MMU_STATUS_BASE		0x384	/* IRQ status */

#define AV1_MMU_EN_BASE			0x388
#define AV1_MMU_BIT_ENABLE		BIT(0)

#define AV1_MMU_OUT_OF_BOUND		BIT(28)
/* Irq mask */
#define AV1_MMU_IRQ_MASK		0x7

#define AV1_DTE_PT_ADDRESS_MASK		0xffffffc0
#define AV1_DTE_PT_VALID		BIT(0)

#define AV1_PAGE_DESC_LO_MASK		0xfffff000
#define AV1_PAGE_DESC_HI_MASK		GENMASK_ULL(39, 32)
#define AV1_PAGE_DESC_HI_SHIFT		(32-4)

#define AV1_IOMMU_PGSIZE_BITMAP 0x007ff000

static inline phys_addr_t av1_dte_pt_address(u32 dte)
{
	return (phys_addr_t)dte & AV1_DTE_PT_ADDRESS_MASK;
}

static inline u32 av1_mk_dte(dma_addr_t pt_dma)
{
	return (pt_dma) | AV1_DTE_PT_VALID;
}

#define AV1_PTE_PAGE_ADDRESS_MASK	0xfffffff0
#define AV1_PTE_PAGE_WRITABLE		BIT(2)
#define AV1_PTE_PAGE_VALID		BIT(0)

static struct device *dma_dev;

static inline phys_addr_t av1_pte_page_address(u32 pte)
{
	u64 pte_av1 = pte;

	pte_av1 = ((pte_av1 & AV1_PAGE_DESC_HI_MASK) << AV1_PAGE_DESC_HI_SHIFT) |
		  (pte_av1 & AV1_PAGE_DESC_LO_MASK);

	return (phys_addr_t)pte_av1;
}

static u32 av1_mk_pte(phys_addr_t page, int prot)
{
	u32 flags = 0;

	flags |= (prot & IOMMU_WRITE) ? AV1_PTE_PAGE_WRITABLE : 0;
	page = (page & AV1_PAGE_DESC_LO_MASK) |
	       ((page & AV1_PAGE_DESC_HI_MASK) >> AV1_PAGE_DESC_HI_SHIFT);
	page &= AV1_PTE_PAGE_ADDRESS_MASK;

	return page | flags | AV1_PTE_PAGE_VALID;
}

#define AV1_DTE_PT_VALID	BIT(0)

static inline bool av1_dte_is_pt_valid(u32 dte)
{
	return dte & AV1_DTE_PT_VALID;
}

static inline bool av1_pte_is_page_valid(u32 pte)
{
	return pte & AV1_PTE_PAGE_VALID;
}

static u32 av1_mk_pte_invalid(u32 pte)
{
	return pte & ~AV1_PTE_PAGE_VALID;
}

#define AV1_MASTER_TLB_MASK	GENMASK_ULL(31, 10)
/* mode 0 : 4k */
#define AV1_PTA_4K_MODE	0

static u64 av1_mk_pta(dma_addr_t dt_dma)
{
	u64 val = (dt_dma & AV1_MASTER_TLB_MASK) | AV1_PTA_4K_MODE;

	return val;
}

static void av1d_iommu_disable(struct av1d_iommu *iommu)
{
	int i;

	/* Ignore error while disabling, just keep going */
	WARN_ON(clk_bulk_enable(iommu->num_clocks, iommu->clocks));
	for (i = 0; i < iommu->num_mmu; i++)
		writel(0, iommu->bases[i] + AV1_MMU_AHB_CONTROL_BASE);

	clk_bulk_disable(iommu->num_clocks, iommu->clocks);
}

static int av1_iommu_disable(struct device *dev)
{
	struct av1d_iommu *av1d_iommu = (struct av1d_iommu *)dev_get_platdata(dev);

	if (!av1d_iommu->domain)
		return 0;

	av1d_iommu_disable(av1d_iommu);

	return 0;
}

static int av1d_iommu_enable(struct av1d_iommu *av1d_iommu)
{
	int ret, i;

	ret = clk_bulk_enable(av1d_iommu->num_clocks, av1d_iommu->clocks);
	if (ret)
		return ret;

	for (i = 0; i < av1d_iommu->num_mmu; i++) {
		u32 val = readl(av1d_iommu->bases[i] + AV1_MMU_AHB_CONTROL_BASE);

		if (!(val & AV1_MMU_BIT_ENABLE)) {
			writel(av1d_iommu->pta_dma,
			       av1d_iommu->bases[i] + AV1_MMU_AHB_TBL_ARRAY_BASE_L_BASE);
			writel(AV1_MMU_OUT_OF_BOUND, av1d_iommu->bases[i] + AV1_MMU_CONFIG1_BASE);
			writel(AV1_MMU_BIT_ENABLE,
			       av1d_iommu->bases[i] + AV1_MMU_AHB_EXCEPTION_BASE);
			writel(AV1_MMU_BIT_ENABLE, av1d_iommu->bases[i] + AV1_MMU_AHB_CONTROL_BASE);
		}
	}
	clk_bulk_disable(av1d_iommu->num_clocks, av1d_iommu->clocks);
	return ret;
}

static int av1_iommu_enable(struct device *dev)
{
	struct av1d_iommu *av1d_iommu = (struct av1d_iommu *)dev_get_platdata(dev);

	if (!av1d_iommu->domain)
		return 0;

	return av1d_iommu_enable(av1d_iommu);
}

static inline void av1_table_flush(dma_addr_t dma, unsigned int count)
{
	size_t size = count * sizeof(u32); /* count of u32 entry */

	dma_sync_single_for_device(dma_dev, dma, size, DMA_TO_DEVICE);
}

#define AV1_IOVA_DTE_MASK	0xffc00000
#define AV1_IOVA_DTE_SHIFT	22
#define AV1_IOVA_PTE_MASK	0x003ff000
#define AV1_IOVA_PTE_SHIFT	12
#define AV1_IOVA_PAGE_MASK	0x00000fff
#define AV1_IOVA_PAGE_SHIFT	0

static u32 av1_iova_dte_index(dma_addr_t iova)
{
	return (u32)(iova & AV1_IOVA_DTE_MASK) >> AV1_IOVA_DTE_SHIFT;
}

static u32 av1_iova_pte_index(dma_addr_t iova)
{
	return (u32)(iova & AV1_IOVA_PTE_MASK) >> AV1_IOVA_PTE_SHIFT;
}

static u32 av1_iova_page_offset(dma_addr_t iova)
{
	return (u32)(iova & AV1_IOVA_PAGE_MASK) >> AV1_IOVA_PAGE_SHIFT;
}

static u32 av1_iommu_read(void __iomem *base, u32 offset)
{
	return readl(base + offset);
}

static void av1_iommu_write(void __iomem *base, u32 offset, u32 value)
{
	writel(value, base + offset);
}


static void av1_iommu_flush_tlb_all(struct iommu_domain *domain, struct device *dev)
{
	struct av1d_iommu *av1d_iommu = (struct av1d_iommu *)dev_get_platdata(dev);
	unsigned long flags;
	int i, ret;

	if (WARN_ON(!av1d_iommu))
		return;

	spin_lock_irqsave(&av1d_iommu->iommus_lock, flags);
	ret = pm_runtime_get_if_in_use(av1d_iommu->dev);
	if (WARN_ON_ONCE(ret < 0)) {
		spin_unlock_irqrestore(&av1d_iommu->iommus_lock, flags);
		return;
	}
	if (ret) {
		WARN_ON(clk_bulk_enable(av1d_iommu->num_clocks, av1d_iommu->clocks));
		for (i = 0; i < av1d_iommu->num_mmu; i++) {
			writel(AV1_MMU_BIT_FLUSH,
				av1d_iommu->bases[i] + AV1_MMU_FLUSH_BASE);
			writel(0, av1d_iommu->bases[i] + AV1_MMU_FLUSH_BASE);
		}
		clk_bulk_disable(av1d_iommu->num_clocks, av1d_iommu->clocks);
		pm_runtime_put(av1d_iommu->dev);
	}
	spin_unlock_irqrestore(&av1d_iommu->iommus_lock, flags);
}

static irqreturn_t av1_iommu_irq(int irq, void *dev_id)
{
	struct av1d_iommu *av1d_iommu = dev_id;
	u32 int_status;
	dma_addr_t iova;
	irqreturn_t ret = IRQ_NONE;
	int i, err;

	err = pm_runtime_get_if_in_use(av1d_iommu->dev);
	if (!err || WARN_ON_ONCE(err < 0))
		return ret;

	if (WARN_ON(clk_bulk_enable(av1d_iommu->num_clocks, av1d_iommu->clocks)))
		goto out;

	for (i = 0; i < av1d_iommu->num_mmu; i++) {
		int_status = av1_iommu_read(av1d_iommu->bases[i], AV1_MMU_STATUS_BASE);
		if (int_status & AV1_MMU_IRQ_MASK) {
			dev_err(av1d_iommu->dev, "unexpected int_status=%08x\n", int_status);
			iova = av1_iommu_read(av1d_iommu->bases[i], AV1_MMU_PAGE_FAULT_ADDR);

			if (av1d_iommu->domain)
				report_iommu_fault(av1d_iommu->domain, av1d_iommu->dev,
						   iova, int_status);
			else
				dev_err(av1d_iommu->dev,
					"Page fault while av1d_iommu not attached to domain?\n");
		}
		av1_iommu_write(av1d_iommu->bases[i], AV1_MMU_STATUS_BASE, 0);
		ret = IRQ_HANDLED;
	}

	clk_bulk_disable(av1d_iommu->num_clocks, av1d_iommu->clocks);

out:
	pm_runtime_put(av1d_iommu->dev);
	return ret;
}

static int av1d_iommu_init(struct av1d_iommu *av1d_iommu)
{
	if (!dma_dev)
		return -ENAVAIL;

	/*
	 * av132xx iommus use a 2 level pagetable.
	 * Each level1 (dt) and level2 (pt) table has 1024 4-byte entries.
	 * Allocate one 4 KiB page for each table.
	 */
	av1d_iommu->dt = (u32 *)get_zeroed_page(GFP_KERNEL | GFP_DMA32);
	if (!av1d_iommu->dt)
		return -1;

	av1d_iommu->dt_dma = dma_map_single(dma_dev, av1d_iommu->dt,
					   SPAGE_SIZE, DMA_TO_DEVICE);
	if (dma_mapping_error(dma_dev, av1d_iommu->dt_dma)) {
		dev_err(dma_dev, "DMA map error for DT\n");
		goto err_free_dt;
	}

	av1d_iommu->pta = (u64 *)get_zeroed_page(GFP_KERNEL | GFP_DMA32);
	if (!av1d_iommu->pta)
		goto err_unmap_dt;

	av1d_iommu->pta_dma = dma_map_single(dma_dev, av1d_iommu->pta,
					SPAGE_SIZE, DMA_TO_DEVICE);
	if (dma_mapping_error(dma_dev, av1d_iommu->pta_dma)) {
		dev_err(dma_dev, "DMA map error for PTA\n");
		goto err_free_pta;
	}
	av1d_iommu->pta[0] = av1_mk_pta(av1d_iommu->dt_dma);

	av1_table_flush(av1d_iommu->pta_dma, 1024);
	av1_table_flush(av1d_iommu->dt_dma, NUM_DT_ENTRIES);

	spin_lock_init(&av1d_iommu->iommus_lock);
	spin_lock_init(&av1d_iommu->dt_lock);

	return 0;
err_free_pta:
	free_page((unsigned long)av1d_iommu->pta);
err_unmap_dt:
	dma_unmap_single(dma_dev, av1d_iommu->dt_dma,
			 SPAGE_SIZE, DMA_TO_DEVICE);
err_free_dt:
	free_page((unsigned long)av1d_iommu->dt);

	return -1;
}

static phys_addr_t av1_iommu_iova_to_phys(struct iommu_domain *domain, dma_addr_t iova,
					  struct device *dev)
{
	struct av1d_iommu *av1d_iommu = (struct av1d_iommu *)dev_get_platdata(dev);
	unsigned long flags;
	phys_addr_t pt_phys, phys = 0;
	u32 dte, pte;
	u32 *page_table;

	spin_lock_irqsave(&av1d_iommu->dt_lock, flags);

	dte = av1d_iommu->dt[av1_iova_dte_index(iova)];
	if (!av1_dte_is_pt_valid(dte))
		goto out;

	pt_phys = av1_dte_pt_address(dte);
	page_table = (u32 *)phys_to_virt(pt_phys);
	pte = page_table[av1_iova_pte_index(iova)];
	if (!av1_pte_is_page_valid(pte))
		goto out;

	phys = av1_pte_page_address(pte) + av1_iova_page_offset(iova);
out:
	spin_unlock_irqrestore(&av1d_iommu->dt_lock, flags);

	return phys;
}

static u32 *av1_dte_get_page_table(struct av1d_iommu *av1d_iommu, dma_addr_t iova)
{
	u32 *page_table, *dte_addr;
	u32 dte_index, dte;
	phys_addr_t pt_phys;
	dma_addr_t pt_dma;

	assert_spin_locked(&av1d_iommu->dt_lock);

	dte_index = av1_iova_dte_index(iova);
	dte_addr = &av1d_iommu->dt[dte_index];
	dte = *dte_addr;
	if (av1_dte_is_pt_valid(dte))
		goto done;

	page_table = (u32 *)get_zeroed_page(GFP_ATOMIC | GFP_DMA32);
	if (!page_table)
		return ERR_PTR(-ENOMEM);

	pt_dma = dma_map_single(dma_dev, page_table, SPAGE_SIZE, DMA_TO_DEVICE);
	if (dma_mapping_error(dma_dev, pt_dma)) {
		dev_err(dma_dev, "DMA mapping error while allocating page table\n");
		free_page((unsigned long)page_table);
		return ERR_PTR(-ENOMEM);
	}

	dte = av1_mk_dte(pt_dma);
	*dte_addr = dte;

	av1_table_flush(pt_dma, NUM_PT_ENTRIES);
	av1_table_flush(av1d_iommu->dt_dma + dte_index * sizeof(u32), 1);
done:
	pt_phys = av1_dte_pt_address(dte);

	return (u32 *)phys_to_virt(pt_phys);
}

static size_t av1_iommu_unmap_iova(struct av1d_iommu *av1d_iommu,
				   u32 *pte_addr, dma_addr_t pte_dma,
				   size_t size)
{
	unsigned int pte_count;
	unsigned int pte_total = size / SPAGE_SIZE;

	assert_spin_locked(&av1d_iommu->dt_lock);

	for (pte_count = 0; pte_count < pte_total; pte_count++) {
		u32 pte = pte_addr[pte_count];

		if (!av1_pte_is_page_valid(pte))
			break;

		pte_addr[pte_count] = av1_mk_pte_invalid(pte);
	}

	av1_table_flush(pte_dma, pte_count);

	return pte_count * SPAGE_SIZE;
}

static int av1_iommu_map_iova(struct av1d_iommu *av1_iommu, u32 *pte_addr,
			      dma_addr_t pte_dma, dma_addr_t iova,
			      phys_addr_t paddr, size_t size, int prot)
{
	unsigned int pte_count;
	unsigned int pte_total = size / SPAGE_SIZE;
	phys_addr_t page_phys;

	assert_spin_locked(&av1_iommu->dt_lock);

	for (pte_count = 0; pte_count < pte_total; pte_count++) {
		u32 pte = pte_addr[pte_count];

		if (av1_pte_is_page_valid(pte))
			goto unwind;

		pte_addr[pte_count] = av1_mk_pte(paddr, prot);

		paddr += SPAGE_SIZE;
	}

	av1_table_flush(pte_dma, pte_total);

	return 0;
unwind:
	/* Unmap the range of iovas that we just mapped */
	av1_iommu_unmap_iova(av1_iommu, pte_addr, pte_dma,
			    pte_count * SPAGE_SIZE);

	iova += pte_count * SPAGE_SIZE;
	page_phys = av1_pte_page_address(pte_addr[pte_count]);
	pr_err("iova: %pad already mapped to %pa cannot remap to phys: %pa prot: %#x\n",
	       &iova, &page_phys, &paddr, prot);

	return -EADDRINUSE;
}

static size_t av1_iommu_unmap(struct iommu_domain *domain, unsigned long _iova,
			      size_t size, struct iommu_iotlb_gather *gather, struct device *dev)
{
	struct av1d_iommu *av1d_iommu = (struct av1d_iommu *)dev_get_platdata(dev);
	unsigned long flags;
	dma_addr_t pte_dma, iova = (dma_addr_t)_iova;
	phys_addr_t pt_phys;
	u32 dte;
	u32 *pte_addr;
	size_t unmap_size;

	spin_lock_irqsave(&av1d_iommu->dt_lock, flags);

	dte = av1d_iommu->dt[av1_iova_dte_index(iova)];
	/* Just return 0 if iova is unmapped */
	if (!av1_dte_is_pt_valid(dte)) {
		spin_unlock_irqrestore(&av1d_iommu->dt_lock, flags);
		return 0;
	}

	pt_phys = av1_dte_pt_address(dte);
	pte_addr = (u32 *)phys_to_virt(pt_phys) + av1_iova_pte_index(iova);
	pte_dma = pt_phys + av1_iova_pte_index(iova) * sizeof(u32);
	unmap_size = av1_iommu_unmap_iova(av1d_iommu, pte_addr, pte_dma, size);

	spin_unlock_irqrestore(&av1d_iommu->dt_lock, flags);

	return unmap_size;
}

static int av1_iommu_map(struct iommu_domain *domain, unsigned long _iova, phys_addr_t paddr,
			 size_t size, int prot, gfp_t gfp, struct device *dev)
{
	struct av1d_iommu *av1d_iommu = (struct av1d_iommu *)dev_get_platdata(dev);
	unsigned long flags;
	dma_addr_t pte_dma, iova = (dma_addr_t)_iova;
	u32 *page_table, *pte_addr;
	u32 dte, pte_index;
	int ret;

	if (WARN_ON(!av1d_iommu))
		return -1;

	spin_lock_irqsave(&av1d_iommu->dt_lock, flags);

	page_table = av1_dte_get_page_table(av1d_iommu, iova);
	if (IS_ERR(page_table)) {
		spin_unlock_irqrestore(&av1d_iommu->dt_lock, flags);
		return PTR_ERR(page_table);
	}

	dte = av1d_iommu->dt[av1_iova_dte_index(iova)];
	pte_index = av1_iova_pte_index(iova);
	pte_addr = &page_table[pte_index];
	pte_dma = av1_dte_pt_address(dte) + pte_index * sizeof(u32);
	ret = av1_iommu_map_iova(av1d_iommu, pte_addr, pte_dma, iova,
				   paddr, size, prot);

	spin_unlock_irqrestore(&av1d_iommu->dt_lock, flags);

	return ret;
}

static void av1_iommu_detach_device(struct iommu_domain *domain, struct device *dev)
{
	struct av1d_iommu *iommu = (struct av1d_iommu *)dev_get_platdata(dev);
	int ret;

	if (WARN_ON(!iommu))
		return;

	dev_dbg(dev, "Detaching from iommu domain\n");

	if (!iommu->domain)
		return;

	ret = pm_runtime_get_if_in_use(iommu->dev);
	WARN_ON_ONCE(ret < 0);
	if (ret > 0) {
		av1d_iommu_disable(iommu);
		pm_runtime_put(iommu->dev);
	}
	iommu->domain = NULL;
}

static int av1_iommu_attach_device(struct iommu_domain *domain, struct device *dev)
{
	struct av1d_iommu *iommu = (struct av1d_iommu *)dev_get_platdata(dev);
	int ret;

	if (WARN_ON(!iommu))
		return -ENODEV;

	if (iommu->domain)
		av1_iommu_detach_device(iommu->domain, dev);

	iommu->domain = domain;

	/* Attach NULL for disable iommu */
	if (!domain)
		return 0;

	ret = pm_runtime_get_if_in_use(iommu->dev);
	if (!ret || WARN_ON_ONCE(ret < 0))
		return 0;

	ret = av1d_iommu_enable(iommu);
	if (ret)
		av1_iommu_detach_device(iommu->domain, dev);

	pm_runtime_put(iommu->dev);

	return ret;
}

static void av1_iommu_domain_free(struct iommu_domain *domain, struct device *dev)
{
	struct av1d_iommu *av1d_iommu = (struct av1d_iommu *)dev_get_platdata(dev);
	int i;

	for (i = 0; i < NUM_DT_ENTRIES; i++) {
		u32 dte = av1d_iommu->dt[i];

		if (av1_dte_is_pt_valid(dte)) {
			phys_addr_t pt_phys = av1_dte_pt_address(dte);
			u32 *page_table = phys_to_virt(pt_phys);

			dma_unmap_single(dma_dev, pt_phys,
					 SPAGE_SIZE, DMA_TO_DEVICE);
			free_page((unsigned long)page_table);
		}
	}

	dma_unmap_single(dma_dev, av1d_iommu->dt_dma,
			 SPAGE_SIZE, DMA_TO_DEVICE);
	free_page((unsigned long)av1d_iommu->dt);

	dma_unmap_single(dma_dev, av1d_iommu->pta_dma,
			 SPAGE_SIZE, DMA_TO_DEVICE);
	free_page((unsigned long)av1d_iommu->pta);

	kfree(av1d_iommu);
}

static int av1_iommu_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct av1d_iommu *iommu;
	struct resource *res;
	int num_res = pdev->num_resources;
	int err, i;

	iommu = devm_kzalloc(dev, sizeof(*iommu), GFP_KERNEL);
	if (!iommu)
		return -ENOMEM;

	iommu->dev = dev;
	iommu->num_mmu = 0;

	iommu->bases = devm_kcalloc(dev, num_res, sizeof(*iommu->bases),
				    GFP_KERNEL);
	if (!iommu->bases)
		return -ENOMEM;

	for (i = 0; i < num_res; i++) {
		res = platform_get_resource(pdev, IORESOURCE_MEM, i);
		if (!res)
			continue;
		iommu->bases[i] = devm_ioremap_resource(&pdev->dev, res);
		if (IS_ERR(iommu->bases[i]))
			continue;
		iommu->num_mmu++;
	}
	if (iommu->num_mmu == 0) {
		dev_err(dev, "get iommu base failed\n");
		return PTR_ERR(iommu->bases[0]);
	}

	iommu->num_irq = platform_irq_count(pdev);
	if (iommu->num_irq < 0) {
		dev_err(dev, "get av1 iommu irq num failed\n");
		return iommu->num_irq;
	}

	err = devm_clk_bulk_get_all(dev, &iommu->clocks);
	if (err >= 0)
		iommu->num_clocks = err;
	else if (err == -ENOENT)
		iommu->num_clocks = 0;
	else {
		dev_err(dev, "get av1 iommu clocks failed\n");
		return err;
	}

	err = clk_bulk_prepare(iommu->num_clocks, iommu->clocks);
	if (err)
		return err;

	if (!dma_dev)
		dma_dev = &pdev->dev;

	pm_runtime_enable(dev);

	for (i = 0; i < iommu->num_irq; i++) {
		int irq = platform_get_irq(pdev, i);

		if (irq < 0) {
			err = -ENODEV;
			dev_err(dev, "av1 iommu get irq failed\n");
			goto err_disable_runtime;
		}

		err = devm_request_irq(iommu->dev, irq, av1_iommu_irq,
				       IRQF_SHARED, dev_name(dev), iommu);
		if (err) {
			dev_err(dev, "av1 iommu request irq handle failed\n");
			goto err_disable_runtime;
		}

	}

	err = av1d_iommu_init(iommu);
	if (err) {
		dev_err(dev, "av1 iommu init failed err %d\n", err);
		goto err_disable_runtime;
	}

	/* store av1d-iommu data to dev->platform_data */
	dev->platform_data = iommu;

	return 0;
err_disable_runtime:
	pm_runtime_disable(dev);
	clk_bulk_unprepare(iommu->num_clocks, iommu->clocks);

	return err;
}

static void av1_iommu_shutdown(struct platform_device *pdev)
{
	struct av1d_iommu *av1d_iommu = (struct av1d_iommu *)dev_get_platdata(&pdev->dev);
	int i;

	for (i = 0; i < av1d_iommu->num_irq; i++) {
		int irq = platform_get_irq(pdev, i);

		devm_free_irq(av1d_iommu->dev, irq, av1d_iommu);
	}

	pm_runtime_force_suspend(&pdev->dev);
}

static int __maybe_unused av1_iommu_suspend(struct device *dev)
{
	struct av1d_iommu *av1d_iommu = (struct av1d_iommu *)dev_get_platdata(dev);

	if (!av1d_iommu->domain)
		return 0;

	av1d_iommu_disable(av1d_iommu);
	return 0;
}

static int __maybe_unused av1_iommu_resume(struct device *dev)
{
	struct av1d_iommu *av1d_iommu = (struct av1d_iommu *)dev_get_platdata(dev);

	if (!av1d_iommu->domain)
		return 0;

	return av1d_iommu_enable(av1d_iommu);
}

static struct third_iommu_ops_wrap av1d_iommu_ops = {
	.attach_dev      = av1_iommu_attach_device,
	.detach_dev      = av1_iommu_detach_device,
	.map             = av1_iommu_map,
	.unmap           = av1_iommu_unmap,
	.flush_iotlb_all = av1_iommu_flush_tlb_all,
	.iova_to_phys    = av1_iommu_iova_to_phys,
	.free            = av1_iommu_domain_free,
	.enable          = av1_iommu_enable,
	.disable         = av1_iommu_disable,
	.shutdown        = av1_iommu_shutdown,
	.suspend         = av1_iommu_suspend,
	.resume          = av1_iommu_resume,
	.probe           = av1_iommu_probe,
};

struct third_iommu_ops_wrap *av1d_iommu_get_ops(void)
{
	return &av1d_iommu_ops;
}
