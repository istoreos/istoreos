// SPDX-License-Identifier: GPL-2.0-only
/*
 * Copyright (c) 2016-2017, The Linux Foundation. All rights reserved.
 */

#define pr_fmt(fmt)	"io-pgtable-fast: " fmt

#include <linux/iommu.h>
#include <linux/kernel.h>
#include <linux/io-pgtable.h>
#include <linux/scatterlist.h>
#include <linux/sizes.h>
#include <linux/slab.h>
#include <linux/types.h>
#include <linux/io-pgtable-fast.h>
#include <linux/mm.h>
#include <asm/cacheflush.h>
#include <linux/vmalloc.h>

#define AV8L_FAST_MAX_ADDR_BITS		48

/* Struct accessors */
#define iof_pgtable_to_data(x)						\
	container_of((x), struct av8l_fast_io_pgtable, iop)

#define iof_pgtable_ops_to_pgtable(x)					\
	container_of((x), struct io_pgtable, ops)

#define iof_pgtable_ops_to_data(x)					\
	iof_pgtable_to_data(iof_pgtable_ops_to_pgtable(x))

struct av8l_fast_io_pgtable {
	struct io_pgtable	  iop;
	av8l_fast_iopte		 *pgd;
	av8l_fast_iopte		 *puds[4];
	av8l_fast_iopte		 *pmds;
	struct page		**pages; /* page table memory */
	int			nr_pages;
	dma_addr_t		base;
	dma_addr_t		start;
	dma_addr_t		end;
};

/* Page table bits */
#define AV8L_FAST_PTE_TYPE_SHIFT	0
#define AV8L_FAST_PTE_TYPE_MASK		0x3

#define AV8L_FAST_PTE_TYPE_BLOCK	1
#define AV8L_FAST_PTE_TYPE_TABLE	3
#define AV8L_FAST_PTE_TYPE_PAGE		3

#define AV8L_FAST_PTE_NSTABLE		(((av8l_fast_iopte)1) << 63)
#define AV8L_FAST_PTE_XN		(((av8l_fast_iopte)3) << 53)
#define AV8L_FAST_PTE_AF		(((av8l_fast_iopte)1) << 10)
#define AV8L_FAST_PTE_SH_NS		(((av8l_fast_iopte)0) << 8)
#define AV8L_FAST_PTE_SH_OS		(((av8l_fast_iopte)2) << 8)
#define AV8L_FAST_PTE_SH_IS		(((av8l_fast_iopte)3) << 8)
#define AV8L_FAST_PTE_SH_MASK		(((av8l_fast_iopte)3) << 8)
#define AV8L_FAST_PTE_NS		(((av8l_fast_iopte)1) << 5)
#define AV8L_FAST_PTE_VALID		(((av8l_fast_iopte)1) << 0)

#define AV8L_FAST_PTE_ATTR_LO_MASK	(((av8l_fast_iopte)0x3ff) << 2)
/* Ignore the contiguous bit for block splitting */
#define AV8L_FAST_PTE_ATTR_HI_MASK	(((av8l_fast_iopte)6) << 52)
#define AV8L_FAST_PTE_ATTR_MASK		(AV8L_FAST_PTE_ATTR_LO_MASK |	\
					 AV8L_FAST_PTE_ATTR_HI_MASK)
#define AV8L_FAST_PTE_ADDR_MASK		((av8l_fast_iopte)0xfffffffff000)


/* Stage-1 PTE */
#define AV8L_FAST_PTE_AP_PRIV_RW	(((av8l_fast_iopte)0) << 6)
#define AV8L_FAST_PTE_AP_RW		(((av8l_fast_iopte)1) << 6)
#define AV8L_FAST_PTE_AP_PRIV_RO	(((av8l_fast_iopte)2) << 6)
#define AV8L_FAST_PTE_AP_RO		(((av8l_fast_iopte)3) << 6)
#define AV8L_FAST_PTE_ATTRINDX_SHIFT	2
#define AV8L_FAST_PTE_ATTRINDX_MASK	0x7
#define AV8L_FAST_PTE_nG		(((av8l_fast_iopte)1) << 11)

/* Stage-2 PTE */
#define AV8L_FAST_PTE_HAP_FAULT		(((av8l_fast_iopte)0) << 6)
#define AV8L_FAST_PTE_HAP_READ		(((av8l_fast_iopte)1) << 6)
#define AV8L_FAST_PTE_HAP_WRITE		(((av8l_fast_iopte)2) << 6)
#define AV8L_FAST_PTE_MEMATTR_OIWB	(((av8l_fast_iopte)0xf) << 2)
#define AV8L_FAST_PTE_MEMATTR_NC	(((av8l_fast_iopte)0x5) << 2)
#define AV8L_FAST_PTE_MEMATTR_DEV	(((av8l_fast_iopte)0x1) << 2)

/* Register bits */
#define ARM_32_LPAE_TCR_EAE		(1 << 31)
#define ARM_64_LPAE_S2_TCR_RES1		(1 << 31)

#define AV8L_FAST_TCR_TG0_4K		(0 << 14)
#define AV8L_FAST_TCR_TG0_64K		(1 << 14)
#define AV8L_FAST_TCR_TG0_16K		(2 << 14)

#define AV8L_FAST_TCR_SH0_SHIFT		12
#define AV8L_FAST_TCR_SH0_MASK		0x3
#define AV8L_FAST_TCR_SH_NS		0
#define AV8L_FAST_TCR_SH_OS		2
#define AV8L_FAST_TCR_SH_IS		3

#define AV8L_FAST_TCR_ORGN0_SHIFT	10
#define AV8L_FAST_TCR_IRGN0_SHIFT	8
#define AV8L_FAST_TCR_RGN_MASK		0x3
#define AV8L_FAST_TCR_RGN_NC		0
#define AV8L_FAST_TCR_RGN_WBWA		1
#define AV8L_FAST_TCR_RGN_WT		2
#define AV8L_FAST_TCR_RGN_WB		3

#define AV8L_FAST_TCR_SL0_SHIFT		6
#define AV8L_FAST_TCR_SL0_MASK		0x3

#define AV8L_FAST_TCR_T0SZ_SHIFT	0
#define AV8L_FAST_TCR_SZ_MASK		0xf

#define AV8L_FAST_TCR_PS_SHIFT		16
#define AV8L_FAST_TCR_PS_MASK		0x7

#define AV8L_FAST_TCR_IPS_SHIFT		32
#define AV8L_FAST_TCR_IPS_MASK		0x7

#define AV8L_FAST_TCR_PS_32_BIT		0x0ULL
#define AV8L_FAST_TCR_PS_36_BIT		0x1ULL
#define AV8L_FAST_TCR_PS_40_BIT		0x2ULL
#define AV8L_FAST_TCR_PS_42_BIT		0x3ULL
#define AV8L_FAST_TCR_PS_44_BIT		0x4ULL
#define AV8L_FAST_TCR_PS_48_BIT		0x5ULL

#define AV8L_FAST_TCR_EPD1_SHIFT	23
#define AV8L_FAST_TCR_EPD1_FAULT	1

#define AV8L_FAST_MAIR_ATTR_SHIFT(n)	((n) << 3)
#define AV8L_FAST_MAIR_ATTR_MASK	0xff
#define AV8L_FAST_MAIR_ATTR_DEVICE	0x04
#define AV8L_FAST_MAIR_ATTR_NC		0x44
#define AV8L_FAST_MAIR_ATTR_WBRWA	0xff
#define AV8L_FAST_MAIR_ATTR_UPSTREAM	0xf4
#define AV8L_FAST_MAIR_ATTR_IDX_NC	0
#define AV8L_FAST_MAIR_ATTR_IDX_CACHE	1
#define AV8L_FAST_MAIR_ATTR_IDX_DEV	2
#define AV8L_FAST_MAIR_ATTR_IDX_UPSTREAM	3

#define AV8L_FAST_PAGE_SHIFT		12

#define PTE_MAIR_IDX(pte)				\
	((pte >> AV8L_FAST_PTE_ATTRINDX_SHIFT) &	\
	 AV8L_FAST_PTE_ATTRINDX_MASK)

#define PTE_SH_IDX(pte) (pte & AV8L_FAST_PTE_SH_MASK)

#define iopte_pmd_offset(pmds, base, iova) (pmds + ((iova - base) >> 12))

#ifdef CONFIG_IOMMU_IO_PGTABLE_FAST_PROVE_TLB

#include <asm/cacheflush.h>
#include <linux/notifier.h>

static ATOMIC_NOTIFIER_HEAD(av8l_notifier_list);

void av8l_register_notify(struct notifier_block *nb)
{
	atomic_notifier_chain_register(&av8l_notifier_list, nb);
}
EXPORT_SYMBOL(av8l_register_notify);

static void __av8l_check_for_stale_tlb(av8l_fast_iopte *ptep)
{
	if (unlikely(*ptep)) {
		atomic_notifier_call_chain(
			&av8l_notifier_list, MAPPED_OVER_STALE_TLB,
			(void *) ptep);
		pr_err("Tried to map over a non-vacant pte: 0x%llx @ %p\n",
		       *ptep, ptep);
		pr_err("Nearby memory:\n");
		print_hex_dump(KERN_ERR, "pgtbl: ", DUMP_PREFIX_ADDRESS,
			       32, 8, ptep - 16, 32 * sizeof(*ptep), false);
	}
}

void av8l_fast_clear_stale_ptes(struct io_pgtable_ops *ops, u64 base,
		u64 start, u64 end, bool skip_sync)
{
	int i;
	struct av8l_fast_io_pgtable *data = iof_pgtable_ops_to_data(ops);
	av8l_fast_iopte *pmdp = iopte_pmd_offset(pmds, base, start);

	for (i = start >> AV8L_FAST_PAGE_SHIFT;
			i <= (end >> AV8L_FAST_PAGE_SHIFT); ++i) {
		if (!(*pmdp & AV8L_FAST_PTE_VALID)) {
			*pmdp = 0;
			if (!skip_sync)
				dmac_clean_range(pmdp, pmdp + 1);
		}
		pmdp++;
	}
}
#else
static void __av8l_check_for_stale_tlb(av8l_fast_iopte *ptep)
{
}
#endif

static void av8l_clean_range(struct io_pgtable_ops *ops,
			av8l_fast_iopte *start, av8l_fast_iopte *end)
{
	struct io_pgtable *iop = iof_pgtable_ops_to_pgtable(ops);

	if (!(iop->cfg.quirks & IO_PGTABLE_QUIRK_NO_DMA))
		dmac_clean_range(start, end);
}

static av8l_fast_iopte
av8l_fast_prot_to_pte(struct av8l_fast_io_pgtable *data, int prot)
{
	av8l_fast_iopte pte = AV8L_FAST_PTE_XN
		| AV8L_FAST_PTE_TYPE_PAGE
		| AV8L_FAST_PTE_AF
		| AV8L_FAST_PTE_nG
		| AV8L_FAST_PTE_SH_OS;

	if (prot & IOMMU_MMIO)
		pte |= (AV8L_FAST_MAIR_ATTR_IDX_DEV
			<< AV8L_FAST_PTE_ATTRINDX_SHIFT);
	else if (prot & IOMMU_CACHE)
		pte |= (AV8L_FAST_MAIR_ATTR_IDX_CACHE
			<< AV8L_FAST_PTE_ATTRINDX_SHIFT);
	else if (prot & IOMMU_USE_UPSTREAM_HINT)
		pte |= (AV8L_FAST_MAIR_ATTR_IDX_UPSTREAM
			<< AV8L_FAST_PTE_ATTRINDX_SHIFT);

	if (!(prot & IOMMU_WRITE))
		pte |= AV8L_FAST_PTE_AP_RO;
	else
		pte |= AV8L_FAST_PTE_AP_RW;

	return pte;
}

static int av8l_fast_map(struct io_pgtable_ops *ops, unsigned long iova,
			 phys_addr_t paddr, size_t size, int prot)
{
	struct av8l_fast_io_pgtable *data = iof_pgtable_ops_to_data(ops);
	av8l_fast_iopte *ptep = iopte_pmd_offset(data->pmds, data->base, iova);
	unsigned long i, nptes = size >> AV8L_FAST_PAGE_SHIFT;
	av8l_fast_iopte pte;

	pte = av8l_fast_prot_to_pte(data, prot);
	paddr &= AV8L_FAST_PTE_ADDR_MASK;
	for (i = 0; i < nptes; i++, paddr += SZ_4K) {
		__av8l_check_for_stale_tlb(ptep + i);
		*(ptep + i) = pte | paddr;
	}
	av8l_clean_range(ops, ptep, ptep + nptes);

	return 0;
}

int av8l_fast_map_public(struct io_pgtable_ops *ops, unsigned long iova,
			 phys_addr_t paddr, size_t size, int prot)
{
	return av8l_fast_map(ops, iova, paddr, size, prot);
}

static size_t
__av8l_fast_unmap(struct io_pgtable_ops *ops, unsigned long iova,
			size_t size, bool allow_stale_tlb)
{
	struct av8l_fast_io_pgtable *data = iof_pgtable_ops_to_data(ops);
	unsigned long nptes;
	av8l_fast_iopte *ptep;
	int val = allow_stale_tlb
		? AV8L_FAST_PTE_UNMAPPED_NEED_TLBI
		: 0;

	ptep = iopte_pmd_offset(data->pmds, data->base, iova);
	nptes = size >> AV8L_FAST_PAGE_SHIFT;

	memset(ptep, val, sizeof(*ptep) * nptes);
	av8l_clean_range(ops, ptep, ptep + nptes);
	if (!allow_stale_tlb)
		io_pgtable_tlb_flush_all(&data->iop);

	return size;
}

/* caller must take care of tlb cache maintenance */
void av8l_fast_unmap_public(struct io_pgtable_ops *ops, unsigned long iova,
				size_t size)
{
	__av8l_fast_unmap(ops, iova, size, true);
}

static size_t av8l_fast_unmap(struct io_pgtable_ops *ops, unsigned long iova,
			      size_t size)
{
	return __av8l_fast_unmap(ops, iova, size, false);
}

static int av8l_fast_map_sg(struct io_pgtable_ops *ops,
			unsigned long iova, struct scatterlist *sgl,
			unsigned int nents, int prot, size_t *size)
{
	struct scatterlist *sg;
	int i;

	for_each_sg(sgl, sg, nents, i) {
		av8l_fast_map(ops, iova, sg_phys(sg), sg->length, prot);
		iova += sg->length;
	}

	return nents;
}

int av8l_fast_map_sg_public(struct io_pgtable_ops *ops,
			    unsigned long iova, struct scatterlist *sgl,
			    unsigned int nents, int prot, size_t *size)
{
	return av8l_fast_map_sg(ops, iova, sgl, nents, prot, size);
}

#if defined(CONFIG_ARM64)
#define FAST_PGDNDX(va) (((va) & 0x7fc0000000) >> 27)
#elif defined(CONFIG_ARM)
#define FAST_PGDNDX(va) (((va) & 0xc0000000) >> 27)
#endif

static phys_addr_t av8l_fast_iova_to_phys(struct io_pgtable_ops *ops,
					  unsigned long iova)
{
	struct av8l_fast_io_pgtable *data = iof_pgtable_ops_to_data(ops);
	av8l_fast_iopte pte, *pgdp, *pudp, *pmdp;
	unsigned long pgd;
	phys_addr_t phys;
	const unsigned long pts = AV8L_FAST_PTE_TYPE_SHIFT;
	const unsigned long ptm = AV8L_FAST_PTE_TYPE_MASK;
	const unsigned long ptt = AV8L_FAST_PTE_TYPE_TABLE;
	const unsigned long ptp = AV8L_FAST_PTE_TYPE_PAGE;
	const av8l_fast_iopte am = AV8L_FAST_PTE_ADDR_MASK;

	/* TODO: clean up some of these magic numbers... */

	pgd = (unsigned long)data->pgd | FAST_PGDNDX(iova);
	pgdp = (av8l_fast_iopte *)pgd;

	pte = *pgdp;
	if (((pte >> pts) & ptm) != ptt)
		return 0;
	pudp = phys_to_virt((pte & am) | ((iova & 0x3fe00000) >> 18));

	pte = *pudp;
	if (((pte >> pts) & ptm) != ptt)
		return 0;
	pmdp = phys_to_virt((pte & am) | ((iova & 0x1ff000) >> 9));

	pte = *pmdp;
	if (((pte >> pts) & ptm) != ptp)
		return 0;
	phys = pte & am;

	return phys | (iova & 0xfff);
}

phys_addr_t av8l_fast_iova_to_phys_public(struct io_pgtable_ops *ops,
					  unsigned long iova)
{
	return av8l_fast_iova_to_phys(ops, iova);
}

static bool av8l_fast_iova_coherent(struct io_pgtable_ops *ops,
					unsigned long iova)
{
	struct av8l_fast_io_pgtable *data = iof_pgtable_ops_to_data(ops);
	av8l_fast_iopte *ptep = iopte_pmd_offset(data->pmds, data->base, iova);

	return ((PTE_MAIR_IDX(*ptep) == AV8L_FAST_MAIR_ATTR_IDX_CACHE) &&
		((PTE_SH_IDX(*ptep) == AV8L_FAST_PTE_SH_OS) ||
		 (PTE_SH_IDX(*ptep) == AV8L_FAST_PTE_SH_IS)));
}

bool av8l_fast_iova_coherent_public(struct io_pgtable_ops *ops,
					unsigned long iova)
{
	return av8l_fast_iova_coherent(ops, iova);
}

static struct av8l_fast_io_pgtable *
av8l_fast_alloc_pgtable_data(struct io_pgtable_cfg *cfg)
{
	struct av8l_fast_io_pgtable *data;

	data = kmalloc(sizeof(*data), GFP_KERNEL);
	if (!data)
		return NULL;

	data->iop.ops = (struct io_pgtable_ops) {
		.map		= av8l_fast_map,
		.map_sg		= av8l_fast_map_sg,
		.unmap		= av8l_fast_unmap,
		.iova_to_phys	= av8l_fast_iova_to_phys,
		.is_iova_coherent = av8l_fast_iova_coherent,
	};

	return data;
}

/*
 * We need max 1 page for the pgd, 4 pages for puds (1GB VA per pud page) and
 * 2048 pages for pmds (each pud page contains 512 table entries, each
 * pointing to a pmd).
 */
#define NUM_PGD_PAGES 1
#define NUM_PUD_PAGES 4
#define NUM_PMD_PAGES 2048
#define NUM_PGTBL_PAGES (NUM_PGD_PAGES + NUM_PUD_PAGES + NUM_PMD_PAGES)

/* undefine arch specific definitions which depends on page table format */
#undef pud_index
#undef pud_mask
#undef pud_next
#undef pmd_index
#undef pmd_mask
#undef pmd_next

#define pud_index(addr)		(((addr) >> 30) & 0x3)
#define pud_mask(addr)		((addr) & ~((1UL << 30) - 1))
#define pud_next(addr, end)					\
({	unsigned long __boundary = pud_mask(addr + (1UL << 30));\
	(__boundary - 1 < (end) - 1) ? __boundary : (end);	\
})

#define pmd_index(addr)		(((addr) >> 21) & 0x1ff)
#define pmd_mask(addr)		((addr) & ~((1UL << 21) - 1))
#define pmd_next(addr, end)					\
({	unsigned long __boundary = pmd_mask(addr + (1UL << 21));\
	(__boundary - 1 < (end) - 1) ? __boundary : (end);	\
})

static int
av8l_fast_prepopulate_pgtables(struct av8l_fast_io_pgtable *data,
			       struct io_pgtable_cfg *cfg, void *cookie)
{
	int i, j, pg = 0;
	struct page **pages, *page;
	dma_addr_t base = cfg->iova_base;
	dma_addr_t end = cfg->iova_end;
	dma_addr_t pud, pmd;
	int pmd_pg_index;

	pages = kmalloc(sizeof(*pages) * NUM_PGTBL_PAGES, __GFP_NOWARN |
							__GFP_NORETRY);

	if (!pages)
		pages = vmalloc(sizeof(*pages) * NUM_PGTBL_PAGES);

	if (!pages)
		return -ENOMEM;

	page = alloc_page(GFP_KERNEL | __GFP_ZERO);
	if (!page)
		goto err_free_pages_arr;
	pages[pg++] = page;
	data->pgd = page_address(page);

	/*
	 * We need max 2048 entries at level 2 to map 4GB of VA space. A page
	 * can hold 512 entries, so we need max 4 pages.
	 */
	for (i = pud_index(base), pud = base; pud < end;
			++i, pud = pud_next(pud, end)) {
		av8l_fast_iopte pte, *ptep;

		page = alloc_page(GFP_KERNEL | __GFP_ZERO);
		if (!page)
			goto err_free_pages;
		pages[pg++] = page;
		data->puds[i] = page_address(page);
		pte = page_to_phys(page) | AV8L_FAST_PTE_TYPE_TABLE;
		ptep = ((av8l_fast_iopte *)data->pgd) + i;
		*ptep = pte;
	}
	dmac_clean_range(data->pgd, data->pgd + 4);

	/*
	 * We have max 4 puds, each of which can point to 512 pmds, so we'll
	 * have max 2048 pmds, each of which can hold 512 ptes, for a grand
	 * total of 2048*512=1048576 PTEs.
	 */
	pmd_pg_index = pg;
	for (i = pud_index(base), pud = base; pud < end;
			++i, pud = pud_next(pud, end)) {
		for (j = pmd_index(pud), pmd = pud; pmd < pud_next(pud, end);
				++j, pmd = pmd_next(pmd, end)) {
			av8l_fast_iopte pte, *pudp;
			void *addr;

			page = alloc_page(GFP_KERNEL | __GFP_ZERO);
			if (!page)
				goto err_free_pages;
			pages[pg++] = page;

			addr = page_address(page);
			dmac_clean_range(addr, addr + SZ_4K);

			pte = page_to_phys(page) | AV8L_FAST_PTE_TYPE_TABLE;
			pudp = data->puds[i] + j;
			*pudp = pte;
		}
		dmac_clean_range(data->puds[i], data->puds[i] + 512);
	}

	/*
	 * We map the pmds into a virtually contiguous space so that we
	 * don't have to traverse the first two levels of the page tables
	 * to find the appropriate pud.  Instead, it will be a simple
	 * offset from the virtual base of the pmds.
	 */
	data->pmds = vmap(&pages[pmd_pg_index], pg - pmd_pg_index,
			  VM_IOREMAP, PAGE_KERNEL);
	if (!data->pmds)
		goto err_free_pages;

	data->pages = pages;
	data->nr_pages = pg;
	data->base = base;
	data->end = end;
	return 0;

err_free_pages:
	for (i = 0; i < pg; ++i)
		__free_page(pages[i]);
err_free_pages_arr:
	kvfree(pages);
	return -ENOMEM;
}

static struct io_pgtable *
av8l_fast_alloc_pgtable(struct io_pgtable_cfg *cfg, void *cookie)
{
	u64 reg;
	struct av8l_fast_io_pgtable *data =
		av8l_fast_alloc_pgtable_data(cfg);

	if (!data)
		return NULL;

	/* restrict according to the fast map requirements */
	cfg->ias = 32;
	cfg->pgsize_bitmap = SZ_4K;

	/* TCR */
	if (cfg->quirks & IO_PGTABLE_QUIRK_QCOM_USE_UPSTREAM_HINT)
		reg = (AV8L_FAST_TCR_SH_OS << AV8L_FAST_TCR_SH0_SHIFT) |
			(AV8L_FAST_TCR_RGN_NC << AV8L_FAST_TCR_IRGN0_SHIFT) |
			(AV8L_FAST_TCR_RGN_WBWA << AV8L_FAST_TCR_ORGN0_SHIFT);
	else if (cfg->quirks & IO_PGTABLE_QUIRK_NO_DMA)
		reg = (AV8L_FAST_TCR_SH_OS << AV8L_FAST_TCR_SH0_SHIFT) |
			(AV8L_FAST_TCR_RGN_WBWA << AV8L_FAST_TCR_IRGN0_SHIFT) |
			(AV8L_FAST_TCR_RGN_WBWA << AV8L_FAST_TCR_ORGN0_SHIFT);
	else
		reg = (AV8L_FAST_TCR_SH_OS << AV8L_FAST_TCR_SH0_SHIFT) |
			(AV8L_FAST_TCR_RGN_NC << AV8L_FAST_TCR_IRGN0_SHIFT) |
			(AV8L_FAST_TCR_RGN_NC << AV8L_FAST_TCR_ORGN0_SHIFT);

	reg |= AV8L_FAST_TCR_TG0_4K;

	switch (cfg->oas) {
	case 32:
		reg |= (AV8L_FAST_TCR_PS_32_BIT << AV8L_FAST_TCR_IPS_SHIFT);
		break;
	case 36:
		reg |= (AV8L_FAST_TCR_PS_36_BIT << AV8L_FAST_TCR_IPS_SHIFT);
		break;
	case 40:
		reg |= (AV8L_FAST_TCR_PS_40_BIT << AV8L_FAST_TCR_IPS_SHIFT);
		break;
	case 42:
		reg |= (AV8L_FAST_TCR_PS_42_BIT << AV8L_FAST_TCR_IPS_SHIFT);
		break;
	case 44:
		reg |= (AV8L_FAST_TCR_PS_44_BIT << AV8L_FAST_TCR_IPS_SHIFT);
		break;
	case 48:
		reg |= (AV8L_FAST_TCR_PS_48_BIT << AV8L_FAST_TCR_IPS_SHIFT);
		break;
	default:
		goto out_free_data;
	}

	reg |= (64ULL - cfg->ias) << AV8L_FAST_TCR_T0SZ_SHIFT;
	reg |= AV8L_FAST_TCR_EPD1_FAULT << AV8L_FAST_TCR_EPD1_SHIFT;
#if defined(CONFIG_ARM)
	reg |= ARM_32_LPAE_TCR_EAE;
#endif
	cfg->av8l_fast_cfg.tcr = reg;

	/* MAIRs */
	reg = (AV8L_FAST_MAIR_ATTR_NC
	       << AV8L_FAST_MAIR_ATTR_SHIFT(AV8L_FAST_MAIR_ATTR_IDX_NC)) |
	      (AV8L_FAST_MAIR_ATTR_WBRWA
	       << AV8L_FAST_MAIR_ATTR_SHIFT(AV8L_FAST_MAIR_ATTR_IDX_CACHE)) |
	      (AV8L_FAST_MAIR_ATTR_DEVICE
	       << AV8L_FAST_MAIR_ATTR_SHIFT(AV8L_FAST_MAIR_ATTR_IDX_DEV)) |
	      (AV8L_FAST_MAIR_ATTR_UPSTREAM
	       << AV8L_FAST_MAIR_ATTR_SHIFT(AV8L_FAST_MAIR_ATTR_IDX_UPSTREAM));

	cfg->av8l_fast_cfg.mair[0] = reg;
	cfg->av8l_fast_cfg.mair[1] = 0;

	/* Allocate all page table memory! */
	if (av8l_fast_prepopulate_pgtables(data, cfg, cookie))
		goto out_free_data;

	cfg->av8l_fast_cfg.pmds = data->pmds;

	/* TTBRs */
	cfg->av8l_fast_cfg.ttbr[0] = virt_to_phys(data->pgd);
	cfg->av8l_fast_cfg.ttbr[1] = 0;
	return &data->iop;

out_free_data:
	kfree(data);
	return NULL;
}

static void av8l_fast_free_pgtable(struct io_pgtable *iop)
{
	int i;
	struct av8l_fast_io_pgtable *data = iof_pgtable_to_data(iop);

	vunmap(data->pmds);
	for (i = 0; i < data->nr_pages; ++i)
		__free_page(data->pages[i]);
	kvfree(data->pages);
	kfree(data);
}

struct io_pgtable_init_fns io_pgtable_av8l_fast_init_fns = {
	.alloc	= av8l_fast_alloc_pgtable,
	.free	= av8l_fast_free_pgtable,
};


#ifdef CONFIG_IOMMU_IO_PGTABLE_FAST_SELFTEST

#include <linux/dma-contiguous.h>

static struct io_pgtable_cfg *cfg_cookie;

static void dummy_tlb_flush_all(void *cookie)
{
	WARN_ON(cookie != cfg_cookie);
}

static void dummy_tlb_add_flush(unsigned long iova, size_t size, size_t granule,
				bool leaf, void *cookie)
{
	WARN_ON(cookie != cfg_cookie);
	WARN_ON(!(size & cfg_cookie->pgsize_bitmap));
}

static void dummy_tlb_sync(void *cookie)
{
	WARN_ON(cookie != cfg_cookie);
}

static struct iommu_gather_ops dummy_tlb_ops __initdata = {
	.tlb_flush_all	= dummy_tlb_flush_all,
	.tlb_add_flush	= dummy_tlb_add_flush,
	.tlb_sync	= dummy_tlb_sync,
};

/*
 * Returns true if the iova range is successfully mapped to the contiguous
 * phys range in ops.
 */
static bool av8l_fast_range_has_specific_mapping(struct io_pgtable_ops *ops,
						 const unsigned long iova_start,
						 const phys_addr_t phys_start,
						 const size_t size)
{
	u64 iova = iova_start;
	phys_addr_t phys = phys_start;

	while (iova < (iova_start + size)) {
		/* + 42 just to make sure offsetting is working */
		if (ops->iova_to_phys(ops, iova + 42) != (phys + 42))
			return false;
		iova += SZ_4K;
		phys += SZ_4K;
	}
	return true;
}

static int __init av8l_fast_positive_testing(void)
{
	int failed = 0;
	u64 iova;
	struct io_pgtable_ops *ops;
	struct io_pgtable_cfg cfg;
	struct av8l_fast_io_pgtable *data;
	av8l_fast_iopte *pmds;
	u64 max = SZ_1G * 4ULL - 1;
	u64 base = 0;

	cfg = (struct io_pgtable_cfg) {
		.quirks = 0,
		.tlb = &dummy_tlb_ops,
		.ias = 32,
		.oas = 32,
		.pgsize_bitmap = SZ_4K,
		.iova_base = base,
		.iova_end = max,
	};

	cfg_cookie = &cfg;
	ops = alloc_io_pgtable_ops(ARM_V8L_FAST, &cfg, &cfg);

	if (WARN_ON(!ops))
		return 1;

	data = iof_pgtable_ops_to_data(ops);
	pmds = data->pmds;

	/* map the entire 4GB VA space with 4K map calls */
	for (iova = base; iova < max; iova += SZ_4K) {
		if (WARN_ON(ops->map(ops, iova, iova, SZ_4K, IOMMU_READ))) {
			failed++;
			continue;
		}
	}
	if (WARN_ON(!av8l_fast_range_has_specific_mapping(ops, base,
					base, max - base)))
		failed++;

	/* unmap it all */
	for (iova = base; iova < max; iova += SZ_4K) {
		if (WARN_ON(ops->unmap(ops, iova, SZ_4K) != SZ_4K))
			failed++;
	}

	/* sweep up TLB proving PTEs */
	av8l_fast_clear_stale_ptes(pmds, base, base, max, false);

	/* map the entire 4GB VA space with 8K map calls */
	for (iova = base; iova < max; iova += SZ_8K) {
		if (WARN_ON(ops->map(ops, iova, iova, SZ_8K, IOMMU_READ))) {
			failed++;
			continue;
		}
	}

	if (WARN_ON(!av8l_fast_range_has_specific_mapping(ops, base,
					base, max - base)))
		failed++;

	/* unmap it all with 8K unmap calls */
	for (iova = base; iova < max; iova += SZ_8K) {
		if (WARN_ON(ops->unmap(ops, iova, SZ_8K) != SZ_8K))
			failed++;
	}

	/* sweep up TLB proving PTEs */
	av8l_fast_clear_stale_ptes(pmds, base, base, max, false);

	/* map the entire 4GB VA space with 16K map calls */
	for (iova = base; iova < max; iova += SZ_16K) {
		if (WARN_ON(ops->map(ops, iova, iova, SZ_16K, IOMMU_READ))) {
			failed++;
			continue;
		}
	}

	if (WARN_ON(!av8l_fast_range_has_specific_mapping(ops, base,
					base, max - base)))
		failed++;

	/* unmap it all */
	for (iova = base; iova < max; iova += SZ_16K) {
		if (WARN_ON(ops->unmap(ops, iova, SZ_16K) != SZ_16K))
			failed++;
	}

	/* sweep up TLB proving PTEs */
	av8l_fast_clear_stale_ptes(pmds, base, base, max, false);

	/* map the entire 4GB VA space with 64K map calls */
	for (iova = base; iova < max; iova += SZ_64K) {
		if (WARN_ON(ops->map(ops, iova, iova, SZ_64K, IOMMU_READ))) {
			failed++;
			continue;
		}
	}

	if (WARN_ON(!av8l_fast_range_has_specific_mapping(ops, base,
					base, max - base)))
		failed++;

	/* unmap it all at once */
	if (WARN_ON(ops->unmap(ops, base, max - base) != (max - base)))
		failed++;

	free_io_pgtable_ops(ops);
	return failed;
}

static int __init av8l_fast_do_selftests(void)
{
	int failed = 0;

	failed += av8l_fast_positive_testing();

	pr_err("selftest: completed with %d failures\n", failed);

	return 0;
}
subsys_initcall(av8l_fast_do_selftests);
#endif
