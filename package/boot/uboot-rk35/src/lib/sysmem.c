// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (c) 2019 Fuzhou Rockchip Electronics Co., Ltd
 */

#include <common.h>
#include <bidram.h>
#include <sysmem.h>
#include <lmb.h>
#include <malloc.h>
#include <asm/io.h>

DECLARE_GLOBAL_DATA_PTR;

#define SYSMEM_MAGIC		0x4D454D53	/* "SMEM" */

#define LMB_ALLOC_ANYWHERE	0		/* sync with lmb.c */
#define SYSMEM_ALLOC_NO_ALIGN	1
#define SYSMEM_ALLOC_ANYWHERE	2

#define SYSMEM_I(fmt, args...)	printf("Sysmem: "fmt, ##args)
#define SYSMEM_W(fmt, args...)	printf("Sysmem Warn: "fmt, ##args)
#define SYSMEM_E(fmt, args...)	printf("Sysmem Error: "fmt, ##args)
#define SYSMEM_D(fmt, args...)	 debug("Sysmem Debug: "fmt, ##args)

struct memcheck {
	uint32_t magic;
};

/* Global for platform, must in data section */
struct sysmem plat_sysmem __section(".data") = {
	.has_initf = false,
	.has_initr = false,
};

bool sysmem_has_init(void)
{
	return gd->flags & GD_FLG_RELOC ?
	       plat_sysmem.has_initr : plat_sysmem.has_initf;
}

static inline int sysmem_is_overlap(phys_addr_t base1, phys_size_t size1,
				    phys_addr_t base2, phys_size_t size2)
{
	return ((base1 < (base2 + size2)) && (base2 < (base1 + size1)));
}

static inline int sysmem_is_sub_region(struct memblock *sub,
				       struct memblock *main)
{
	if (!sub || !main)
		return false;

	return ((sub->base >= main->base) &&
		(sub->base + sub->size <= main->base + main->size));
}

void sysmem_dump(void)
{
	struct sysmem *sysmem = &plat_sysmem;
	struct lmb *lmb = &sysmem->lmb;
	struct memblock *mem;
	struct memcheck *check;
	struct list_head *node;
	ulong memory_size = 0;
	ulong reserved_size = 0;
	ulong allocated_size = 0;
	bool overflow = false;
	ulong i;

	if (!sysmem_has_init())
		return;

	printf("\nsysmem_dump_all:\n");

	/* Memory pool */
	printf("    --------------------------------------------------------------------\n");
	for (i = 0; i < lmb->memory.cnt; i++) {
		memory_size += lmb->memory.region[i].size;
		printf("    memory.rgn[%ld].addr     = 0x%08lx - 0x%08lx (size: 0x%08lx)\n", i,
		       (ulong)lmb->memory.region[i].base,
		       (ulong)lmb->memory.region[i].base +
		       (ulong)lmb->memory.region[i].size,
		       (ulong)lmb->memory.region[i].size);
	}
	printf("\n    memory.total	   = 0x%08lx (%ld MiB. %ld KiB)\n",
	       (ulong)memory_size,
	       SIZE_MB((ulong)memory_size),
	       SIZE_KB((ulong)memory_size));

	/* Allocated */
	i = 0;
	printf("    --------------------------------------------------------------------\n");
	list_for_each(node, &sysmem->allocated_head) {
		mem = list_entry(node, struct memblock, node);
		allocated_size += mem->size;
		if (mem->attr.flags & F_OFC) {
			check = (struct memcheck *)
				(mem->base + mem->size - sizeof(*check));
			overflow = (check->magic != SYSMEM_MAGIC);
		} else if (mem->attr.flags & F_HOFC) {
			check = (struct memcheck *)
				(mem->base - sizeof(*check));
			overflow = (check->magic != SYSMEM_MAGIC);
		} else {
			overflow = false;
		}

		printf("    allocated.rgn[%ld].name  = \"%s\" %s %s\n",
		       i, mem->attr.name, overflow ? "	   <Overflow!>" : "",
		       mem->orig_base != mem->base ? "<*>" : "");
		printf("		    .addr  = 0x%08lx - 0x%08lx (size: 0x%08lx)\n",
		       (ulong)mem->orig_base,
		       (ulong)(mem->orig_base + mem->size),
		       (ulong)mem->size);
		i++;
	}

	/* Kernel 'reserved-memory' */
	i = 0;
	printf("\n");
	list_for_each(node, &sysmem->kmem_resv_head) {
		mem = list_entry(node, struct memblock, node);
		allocated_size += mem->size;
		printf("    kmem-resv.rgn[%ld].name  = \"%s\" %s\n",
		       i, mem->attr.name,
		       mem->orig_base != mem->base ? "<*>" : "");
		printf("		    .addr  = 0x%08lx - 0x%08lx (size: 0x%08lx)\n",
		       (ulong)mem->orig_base,
		       (ulong)(mem->orig_base + mem->size),
		       (ulong)mem->size);
		i++;
	}

	printf("\n    framework malloc_r     = %3d MiB",
	       SIZE_MB(CONFIG_SYS_MALLOC_LEN));
	printf("\n    framework malloc_f     = %3d KiB\n",
	       SIZE_KB(CONFIG_SYS_MALLOC_F_LEN));

	printf("\n    allocated.total	   = 0x%08lx (%ld MiB. %ld KiB)\n",
	       (ulong)allocated_size,
	       SIZE_MB((ulong)allocated_size),
	       SIZE_KB((ulong)allocated_size));

	/* LMB core reserved */
	printf("    --------------------------------------------------------------------\n");
	reserved_size = 0;
	for (i = 0; i < lmb->reserved.cnt; i++) {
		reserved_size += lmb->reserved.region[i].size;
		printf("    LMB.allocated[%ld].addr  = 0x%08lx - 0x%08lx (size: 0x%08lx)\n", i,
		       (ulong)lmb->reserved.region[i].base,
		       (ulong)lmb->reserved.region[i].base +
		       (ulong)lmb->reserved.region[i].size,
		       (ulong)lmb->reserved.region[i].size);
	}

	printf("\n    reserved.core.total	   = 0x%08lx (%ld MiB. %ld KiB)\n",
	       (ulong)reserved_size,
	       SIZE_MB((ulong)reserved_size),
	       SIZE_KB((ulong)reserved_size));
	printf("    --------------------------------------------------------------------\n\n");
}

void sysmem_overflow_check(void)
{
	struct sysmem *sysmem = &plat_sysmem;
	struct list_head *node, *knode;
	struct memcheck *check;
	struct memblock *kmem;
	struct memblock *smem;
	struct memblock *rmem;
	int overflow = 0, overlap = 0;

	if (!sysmem_has_init())
		return;

#ifdef CONFIG_BIDRAM
	/*
	 * Check kernel 'reserved-memory' overlap with invisible regions
	 *
	 * Here, only print warning message when overlap with invisible region
	 */
	list_for_each(knode, &sysmem->kmem_resv_head) {
		kmem = list_entry(knode, struct memblock, node);
		rmem = bidram_reserved_is_overlap(kmem->base, kmem->size);
		if (rmem) {
			const char *alias;
			int i, dump = 1;

			/*
			 * Ignore the sub region of invisible region.
			 * eg: ramoops of SHM.
			 */
			alias = rmem->attr.alias[0];
			if (alias && sysmem_is_sub_region(kmem, rmem)) {
				for (i = 0; i < ALIAS_COUNT_MAX; i++, alias++) {
					alias = rmem->attr.alias[i];
					if (!alias)
						continue;
					if (!strncasecmp(kmem->attr.name, alias,
							 strlen(alias))) {
						dump = 0;
						break;
					}
				}
			}

			if (dump)
				SYSMEM_W("kernel 'reserved-memory' \"%s\"(0x%08lx - 0x%08lx) "
					 "is overlap with [invisible] \"%s\" (0x%08lx - 0x%08lx)\n",
					 kmem->attr.name, (ulong)kmem->base,
					 (ulong)(kmem->base + kmem->size),
					 rmem->attr.name, (ulong)rmem->base,
					 (ulong)(rmem->base + rmem->size));
		}
	}
#endif

	list_for_each(node, &sysmem->allocated_head) {
		smem = list_entry(node, struct memblock, node);
		/*
		 * Check kernel 'reserved-memory' overlap with sysmem allocated regions
		 */
		list_for_each(knode, &sysmem->kmem_resv_head) {
			kmem = list_entry(knode, struct memblock, node);
			if (sysmem_is_overlap(smem->base, smem->size,
					      kmem->base, kmem->size)) {
				if (smem->attr.flags & F_KMEM_CAN_OVERLAP)
					continue;

				overlap = 1;
				SYSMEM_W("kernel 'reserved-memory' \"%s\"(0x%08lx - 0x%08lx) "
					 "is overlap with \"%s\" (0x%08lx - 0x%08lx)\n",
					 kmem->attr.name, (ulong)kmem->base,
					 (ulong)(kmem->base + kmem->size),
					 smem->attr.name, (ulong)smem->base,
					 (ulong)(smem->base + smem->size));
			}
		}

		/*
		 * Check sysmem allocated regions overflow.
		 */
		if (smem->attr.flags & F_OFC) {
			check = (struct memcheck *)
				(smem->base + smem->size - sizeof(*check));
			overflow = (check->magic != SYSMEM_MAGIC);
		} else if (smem->attr.flags & F_HOFC) {
			check = (struct memcheck *)
				(smem->base - sizeof(*check));
			overflow = (check->magic != SYSMEM_MAGIC);
		} else {
			overflow = 0;
		}

		if (overflow) {
			SYSMEM_E("Found there is region overflow!\n");
			break;
		}
	}

	if (overflow || overlap)
		sysmem_dump();
}

static int sysmem_add(phys_addr_t base, phys_size_t size)
{
	struct sysmem *sysmem = &plat_sysmem;
	int ret;

	if (!size)
		return -EINVAL;

	ret = lmb_add(&sysmem->lmb, base, size);
	if (ret < 0)
		SYSMEM_E("Failed to add sysmem at 0x%08lx for 0x%08lx size\n",
			 (ulong)base, (ulong)size);

	return (ret >= 0) ? 0 : ret;
}

static const char *sysmem_alias2name(const char *name, int *id)
{
	const char *alias;
	int i, j;
	int match = 0;

	for (i = 0; i < MEM_MAX; i++) {
		/* Pirmary name */
		if (mem_attr[i].name && !strcasecmp(mem_attr[i].name, name)) {
			match = 1;
			goto finish;
		}

		/* Alias name */
		alias = mem_attr[i].alias[0];
		if (!alias)
			continue;

		for (j = 0; j < ALIAS_COUNT_MAX; j++) {
			alias = mem_attr[i].alias[j];
			if (alias && !strcasecmp(alias, name)) {
				match = 1;
				goto finish;
			}
		}
	}

finish:
	if (match) {
		*id = i;
		return mem_attr[i].name;
	}

	return name;
}

static void *sysmem_alloc_align_base(enum memblk_id id,
				     const char *mem_name,
				     phys_addr_t base,
				     phys_size_t size,
				     ulong align)
{
	struct sysmem *sysmem = &plat_sysmem;
	struct memblk_attr attr;
	struct memblock *mem;
	struct memcheck *check;
	struct list_head *node;
	const char *name;
	phys_addr_t paddr;
	phys_addr_t alloc_base;
	phys_size_t alloc_size;
	phys_addr_t orig_base = base;

	if (!sysmem_has_init())
		goto out;

	if (id == MEM_BY_NAME || id == MEM_KMEM_RESERVED) {
		if (!mem_name) {
			SYSMEM_E("NULL name for alloc sysmem\n");
			goto out;
		}

		/* Find: name, id and attr by outer mem_name & id */
		name = sysmem_alias2name(mem_name, (int *)&id);
		attr = mem_attr[id];
		if (!attr.name)
			attr.name = strdup(name);

		/* Always make kernel 'reserved-memory' alloc successfully */
		if (id == MEM_KMEM_RESERVED) {
			struct memblock *mem;

			mem = malloc(sizeof(*mem));
			if (!mem) {
				SYSMEM_E("No memory for \"%s\" alloc sysmem\n", name);
				return mem;
			}

			attr.flags |= F_KMEM_RESERVED;
			mem->orig_base = orig_base;
			mem->base = base;
			mem->size = size;
			mem->attr = attr;
			sysmem->kmem_resv_cnt++;
			list_add_tail(&mem->node, &sysmem->kmem_resv_head);

			return (void *)base;
		}
	} else if (id > MEM_UNK && id < MEM_MAX) {
		attr = mem_attr[id];
		name = attr.name;

		/*
		 * Special handle for Android AVB alloc(on any where)
		 *
		 * Fixup base and place right after U-Boot stack, adding a lot
		 * of space(4KB) maybe safer.
		 */
		if (attr.flags & F_HIGHEST_MEM) {
			base = gd->start_addr_sp -
					CONFIG_SYS_STACK_SIZE - size - 0x1000;

		/*
		 * The 0x0 address is usually allocated by 32-bit uncompressed
		 * kernel and this alloc action is just a peek.
		 *
		 * Due to LMB core doesn't support alloc at 0x0 address, we have
		 * to alloc the memblk backword a few bytes.
		 *
		 * ARCH_DMA_MINALIGN maybe a good choice.
		 */
		} else if (!base) {
			base += ARCH_DMA_MINALIGN;
		} else if (base < gd->bd->bi_dram[0].start) {
			/*
			 * On Rockchip platform:
			 *
			 * So far, we use F_IGNORE_INVISIBLE for uncompress
			 * kernel alloc, and for ARMv8 enabling AArch32 mode, the
			 * ATF is still AArch64 and ocuppies 0~1MB and shmem 1~2M.
			 * So let's ignore the region which overlap with them.
			 */
			if (attr.flags & F_IGNORE_INVISIBLE) {
				base = gd->bd->bi_dram[0].start;
			} else {
				SYSMEM_E("Failed to alloc invisible sub region 0x%08lx - 0x%08lx "
					 "of \"%s\" at 0x%08lx - 0x%08lx\n",
					 (ulong)base, (ulong)gd->bd->bi_dram[0].start,
					 name, (ulong)base, (ulong)(base + size));
				goto out;
			}
		}
	} else {
		SYSMEM_E("Unsupport memblk id %d for alloc sysmem\n", id);
		goto out;
	}

	if (!size) {
		SYSMEM_E("\"%s\" size is 0 for alloc sysmem\n", name);
		goto out;
	}

	/*
	 * Some modules use "sysmem_alloc()" to alloc region for storage
	 * read/write buffer, it should be aligned to cacheline size. eg: AVB.
	 *
	 * Aligned down to cacheline size if not aligned, otherwise the tail
	 * of region maybe overflow.
	 */
	if (attr.flags & F_CACHELINE_ALIGN &&
	    !IS_ALIGNED(base, ARCH_DMA_MINALIGN)) {
		base = ALIGN(base, ARCH_DMA_MINALIGN);
		base -= ARCH_DMA_MINALIGN;
	}

	if (base != SYSMEM_ALLOC_ANYWHERE && !IS_ALIGNED(base, 4)) {
		SYSMEM_E("\"%s\" base=0x%08lx is not 4-byte aligned\n",
			 name, (ulong)base);
		goto out;
	}

	/* Must be sizeof(long) byte aligned */
	size = ALIGN(size, sizeof(long));

	SYSMEM_D("Enter alloc: \"%s\" 0x%08lx - 0x%08lx\n",
		 name, (ulong)base, (ulong)(base + size));

	/* Already allocated ? */
	list_for_each(node, &sysmem->allocated_head) {
		mem = list_entry(node, struct memblock, node);
		SYSMEM_D("Has allcated: %s, 0x%08lx - 0x%08lx\n",
			 mem->attr.name, (ulong)mem->base,
			 (ulong)(mem->base + mem->size));
		if (!strcmp(mem->attr.name, name)) {
			/* Allow double alloc for same but smaller region */
			if (mem->base <= base && mem->size >= size)
				return (void *)base;

			SYSMEM_E("Failed to double alloc for existence \"%s\"\n", name);
			goto out;
		} else if (sysmem_is_overlap(mem->base, mem->size, base, size)) {
			SYSMEM_E("\"%s\" (0x%08lx - 0x%08lx) alloc is "
				 "overlap with existence \"%s\" (0x%08lx - "
				 "0x%08lx)\n",
				 name, (ulong)base, (ulong)(base + size),
				 mem->attr.name, (ulong)mem->base,
				 (ulong)(mem->base + mem->size));
			goto out;
		}
	}

	/* Add overflow check magic ? */
	if (attr.flags & F_OFC)
		alloc_size = size + sizeof(*check);
	else
		alloc_size = size;

	/* Alloc anywhere ? */
	if (base == SYSMEM_ALLOC_ANYWHERE)
		alloc_base = LMB_ALLOC_ANYWHERE;
	else
		alloc_base = base + alloc_size;	/* LMB is align down alloc mechanism */

	SYSMEM_D("DO alloc... base: 0x%08lx\n", (ulong)alloc_base);

	paddr = lmb_alloc_base(&sysmem->lmb, alloc_size, align, alloc_base);
	if (paddr) {
		if ((paddr == base) || (base == SYSMEM_ALLOC_ANYWHERE)) {
			mem = malloc(sizeof(*mem));
			if (!mem) {
				SYSMEM_E("No memory for \"%s\" alloc sysmem\n", name);
				goto out;
			}
			/* Record original base for dump */
			if (attr.flags & F_HIGHEST_MEM)
				mem->orig_base = base;
			else
				mem->orig_base = orig_base;

			mem->base = paddr;
			mem->size = alloc_size;
			mem->attr = attr;
			sysmem->allocated_cnt++;
			list_add_tail(&mem->node, &sysmem->allocated_head);

			/* Add overflow check magic */
			if (mem->attr.flags & F_OFC) {
				check = (struct memcheck *)(paddr + size);
				check->magic = SYSMEM_MAGIC;
			} else if (mem->attr.flags & F_HOFC) {
				check = (struct memcheck *)(paddr - sizeof(*check));
				check->magic = SYSMEM_MAGIC;
			}
		} else {
			SYSMEM_E("Failed to alloc \"%s\" expect at 0x%08lx - 0x%08lx "
				 "but at 0x%08lx - x%08lx\n",
				 name, (ulong)base, (ulong)(base + size),
				 (ulong)paddr, (ulong)(paddr + size));
			/* Free what we don't want allocated region */
			if (lmb_free(&sysmem->lmb, paddr, alloc_size) < 0)
				SYSMEM_E("Failed to free \"%s\"\n", name);

			goto out;
		}
	} else {
		SYSMEM_E("Failed to alloc \"%s\" at 0x%08lx - 0x%08lx\n",
			 name, (ulong)base, (ulong)(base + size));
		goto out;
	}

	SYSMEM_D("Exit alloc: \"%s\", paddr=0x%08lx, size=0x%08lx, align=0x%x, anywhere=%d\n",
		 name, (ulong)paddr, (ulong)size, (u32)align, !base);

	return (void *)paddr;

out:
	/*
	 * Why: base + sizeof(ulong) ?
	 * It's not a standard way to handle the case: the input base is 0.
	 * Because 0 equals NULL, but we don't want to return NULL when alloc
	 * successfully, so just return a !NULL value is okay.
	 *
	 * When it happens ?
	 * Maybe 32-bit platform would alloc region for uncompress kernel
	 * at 0 address.
	 */
	if (base == 0)
		base = base + sizeof(ulong);

	return (attr.flags & (F_IGNORE_INVISIBLE | F_NO_FAIL_DUMP)) ?
			(void *)base : NULL;
}

void *sysmem_alloc(enum memblk_id id, phys_size_t size)
{
	void *paddr;

	paddr = sysmem_alloc_align_base(id,
					NULL,
					SYSMEM_ALLOC_ANYWHERE,
					size,
					ARCH_DMA_MINALIGN);
	if (!paddr)
		sysmem_dump();

	return paddr;
}

void *sysmem_alloc_by_name(const char *name, phys_size_t size)
{
	void *paddr;

	paddr = sysmem_alloc_align_base(MEM_BY_NAME,
					name,
					SYSMEM_ALLOC_ANYWHERE,
					size,
					ARCH_DMA_MINALIGN);
	if (!paddr)
		sysmem_dump();

	return paddr;
}

void *sysmem_alloc_base(enum memblk_id id, phys_addr_t base, phys_size_t size)
{
	void *paddr;

	paddr = sysmem_alloc_align_base(id,
					NULL,
					base,
					size,
					SYSMEM_ALLOC_NO_ALIGN);
	if (!paddr)
		sysmem_dump();

	return paddr;
}

void *sysmem_alloc_base_by_name(const char *name,
				phys_addr_t base, phys_size_t size)
{
	void *paddr;

	paddr = sysmem_alloc_align_base(MEM_BY_NAME,
					name,
					base,
					size,
					SYSMEM_ALLOC_NO_ALIGN);
	if (!paddr)
		sysmem_dump();

	return paddr;
}

void *sysmem_fdt_reserve_alloc_base(const char *name,
				    phys_addr_t base, phys_size_t size)
{
	void *paddr;

	paddr = sysmem_alloc_align_base(MEM_KMEM_RESERVED,
					name,
					base,
					size,
					SYSMEM_ALLOC_NO_ALIGN);
	if (!paddr)
		sysmem_dump();

	return paddr;
}

ulong sysmem_alloc_temporary_mem(phys_size_t size)
{
	struct sysmem *sysmem = &plat_sysmem;
	phys_addr_t alloc_base;
	phys_addr_t paddr;
	phys_addr_t base;
	int ret;

	if (!sysmem_has_init())
		return false;

	base = (gd->start_addr_sp - CONFIG_SYS_STACK_SIZE - 0x2000) - size;

	/* LMB is align down alloc mechanism */
	alloc_base = base + size;
	paddr = __lmb_alloc_base(&sysmem->lmb, size, SZ_1K, alloc_base);
	if (paddr) {
		/* If free failed, return false */
		ret = lmb_free(&sysmem->lmb, paddr, size);
		if (ret < 0) {
			SYSMEM_E("Can't free at 0x%08lx - 0x%08lx, ret=%d\n",
				 (ulong)paddr, (ulong)(paddr + size), ret);
			return 0;
		}
	}

	return paddr;
}

int sysmem_free(phys_addr_t base)
{
	struct sysmem *sysmem = &plat_sysmem;
	struct memblock *mem;
	struct list_head *node;
	int ret, found = 0;

	if (!sysmem_has_init())
		return -ENOSYS;

	/* Find existence */
	list_for_each(node, &sysmem->allocated_head) {
		mem = list_entry(node, struct memblock, node);
		if (mem->base == base || mem->orig_base == base) {
			found = 1;
			break;
		}
	}

	if (!found) {
		SYSMEM_E("Failed to free no allocated sysmem at 0x%08lx\n",
			 (ulong)base);
		return -EINVAL;
	}

	ret = lmb_free(&sysmem->lmb, mem->base, mem->size);
	if (ret >= 0) {
		SYSMEM_D("Free: \"%s\" 0x%08lx - 0x%08lx\n",
			 mem->attr.name, (ulong)mem->base,
			 (ulong)(mem->base + mem->size));
		sysmem->allocated_cnt--;
		list_del(&mem->node);
		free(mem);
	} else {
		SYSMEM_E("Failed to free \"%s\" at 0x%08lx\n",
			 mem->attr.name, (ulong)base);
	}

	return (ret >= 0) ? 0 : ret;
}

int sysmem_initr(void)
{
	return sysmem_init();
}

int sysmem_init(void)
{
	struct sysmem *sysmem = &plat_sysmem;
	phys_addr_t mem_start;
	phys_size_t mem_size;
	int ret;

	lmb_init(&sysmem->lmb);
	INIT_LIST_HEAD(&sysmem->allocated_head);
	INIT_LIST_HEAD(&sysmem->kmem_resv_head);
	sysmem->allocated_cnt = 0;
	sysmem->kmem_resv_cnt = 0;

	if (gd->flags & GD_FLG_RELOC) {
		sysmem->has_initr = true;
	} else {
		SYSMEM_I("init\n");
		sysmem->has_initf = true;
	}

	/* Add all available system memory */
#ifdef CONFIG_NR_DRAM_BANKS
	int i;

	for (i = 0; i < CONFIG_NR_DRAM_BANKS; i++) {
		if (!gd->bd->bi_dram[i].size)
			continue;

		ret = sysmem_add(gd->bd->bi_dram[i].start,
				 gd->bd->bi_dram[i].size);
		if (ret) {
			SYSMEM_E("Failed to add sysmem from bi_dram[%d]\n", i);
			goto fail;
		}
	}
#else
	mem_start = env_get_bootm_low();
	mem_size = env_get_bootm_size();
	ret = sysmem_add(mem_start, mem_size);
	if (ret) {
		SYSMEM_E("Failed to add sysmem from bootm_low/size\n");
		goto fail;
	}
#endif
	/* Reserved for board */
	ret = board_sysmem_reserve(sysmem);
	if (ret) {
		SYSMEM_E("Failed to reserve sysmem for board\n");
		goto fail;
	}

	/* Reserved for U-boot framework: 'reserve_xxx()' */
	mem_start = gd->start_addr_sp;
	mem_size = gd->ram_top - mem_start;
	if (!sysmem_alloc_base(MEM_UBOOT, mem_start, mem_size)) {
		SYSMEM_E("Failed to reserve sysmem for U-Boot framework\n");
		ret = -ENOMEM;
		goto fail;
	}

	/* Reserved for U-Boot stack */
	mem_start = gd->start_addr_sp - CONFIG_SYS_STACK_SIZE;
	mem_size = CONFIG_SYS_STACK_SIZE;
	if (!sysmem_alloc_base(MEM_STACK, mem_start, mem_size)) {
		SYSMEM_E("Failed to reserve sysmem for stack\n");
		ret = -ENOMEM;
		goto fail;
	}

	return 0;

fail:
	if (ret && !(gd->flags & GD_FLG_RELOC)) {
		sysmem_dump();
		SYSMEM_W("Maybe malloc size %d MiB is too large?\n\n",
			 SIZE_MB(CONFIG_SYS_MALLOC_LEN));
	}

	return ret;
}

__weak int board_sysmem_reserve(struct sysmem *sysmem)
{
	/* please define platform specific board_sysmem_reserve() */
	return 0;
}

static int do_sysmem_dump(cmd_tbl_t *cmdtp, int flag,
			  int argc, char *const argv[])
{
	sysmem_dump();
	return 0;
}

static int do_sysmem_search(cmd_tbl_t *cmdtp, int flag,
			    int argc, char *const argv[])
{
	ulong addr, size;

	if (argc != 2)
		return CMD_RET_USAGE;

	size = simple_strtoul(argv[1], NULL, 16);
	if (!size)
		return CMD_RET_USAGE;

	addr = sysmem_alloc_temporary_mem(size);
	if (!addr) {
		SYSMEM_I("No available region with size 0x%08lx\n", size);
	} else {
		SYSMEM_I("Available region at address: 0x%08lx\n",addr);
	}
	env_set_hex("smem_addr", addr);

	return 0;
}

U_BOOT_CMD(
	sysmem_dump, 1, 1, do_sysmem_dump,
	"Dump sysmem layout",
	""
);

U_BOOT_CMD(
	sysmem_search, 2, 1, do_sysmem_search,
	"Search a available sysmem region",
	"<size in hex>"
);
