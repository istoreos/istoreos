/* SPDX-License-Identifier:     GPL-2.0+ */
/*
 * (C) Copyright 2019 Rockchip Electronics Co., Ltd
 */

#ifndef _SYSMEM_H
#define _SYSMEM_H

#include <memblk.h>
#include <malloc.h>

/*
 * CONFIG_SYS_FDT_PAD default value is sync with bootm framework in:
 * common/image-fdt.c
 */
#ifndef CONFIG_SYS_FDT_PAD
#define CONFIG_SYS_FDT_PAD		0x3000
#endif

struct sysmem {
	struct lmb lmb;
	struct list_head allocated_head;
	struct list_head kmem_resv_head;
	ulong allocated_cnt;
	ulong kmem_resv_cnt;
	bool has_initf;
	bool has_initr;
};

#ifdef CONFIG_SYSMEM
/**
 * sysmem_has_init() - Is sysmem initialized
 *
 * @return true or false
 */
bool sysmem_has_init(void);

/**
 * sysmem_init() - Sysmem initialization
 *
 * @return 0 on success, otherwise error
 */
int sysmem_init(void);

/**
 * sysmem_initr() - Sysmem initialization after relocation
 *
 * @return 0 on success, otherwise error
 */
int sysmem_initr(void);

/**
 * sysmem_alloc() - Alloc sysmem region at anywhere
 *
 * @id: memblk id
 * @size: region size
 *
 * @return NULL on error, otherwise the allocated region address ptr
 */
void *sysmem_alloc(enum memblk_id id, phys_size_t size);

/**
 * sysmem_alloc_by_name() - Alloc sysmem region by name at the expect addr
 *
 * @name: memblk name
 * @size: region size
 *
 * @return NULL on error, otherwise the allocated region address ptr
 */
void *sysmem_alloc_by_name(const char *name, phys_size_t size);

/**
 * sysmem_alloc_base() - Alloc sysmem region at the expect addr
 *
 * @id: memblk id
 * @base: region base
 * @size: region size
 *
 * @return NULL on error, otherwise the allocated region address ptr
 */
void *sysmem_alloc_base(enum memblk_id id, phys_addr_t base, phys_size_t size);

/**
 * sysmem_alloc_base_by_name() - Alloc sysmem region at the expect addr by name
 *
 * @name: memblk name
 * @base: region base
 * @size: region size
 *
 * @return NULL on error, otherwise the allocated region address ptr
 */
void *sysmem_alloc_base_by_name(const char *name,
				phys_addr_t base, phys_size_t size);

/**
 * sysmem_fdt_reserve_alloc_base() - Alloc sysmem region at the expect addr by name,
 *				     called only for reserve memory from fdt.
 *
 * @name: memblk name
 * @base: region base
 * @size: region size
 *
 * @return NULL on error, otherwise the allocated region address ptr
 */
void *sysmem_fdt_reserve_alloc_base(const char *name,
				    phys_addr_t base, phys_size_t size);

/**
 * sysmem_alloc_temporary_mem() - Alloc a temporary shared memory buffer
 *
 * @size: region size
 *
 * @return 0 on failed, otherwise allocated addr.
 */
ulong sysmem_alloc_temporary_mem(phys_size_t size);

/**
 * sysmem_free() - Free allocated sysmem region
 *
 * @base: region base
 *
 * @return 0 on success, otherwise error
 */
int sysmem_free(phys_addr_t base);

/**
 * sysmem_dump() - Dump all sysmem region state
 */
void sysmem_dump(void);

/**
 * sysmem_overflow_check() - Sysmem regions overflow check
 */
void sysmem_overflow_check(void);

/**
 * board_sysmem_reserve() - Weak function for board to implement
 *
 * @sysmem: global sysmem point, ignored
 *
 * @return 0 on success, otherwise error
 */
int board_sysmem_reserve(struct sysmem *sysmem);
#else
static inline bool sysmem_has_init(void) { return false; }
static inline int sysmem_init(void) { return 0; }
static inline int sysmem_initr(void) { return 0; }
static inline int sysmem_free(phys_addr_t base) { return 0; }
static inline void sysmem_dump(void) {}
static inline void sysmem_overflow_check(void) {}
__weak int board_sysmem_reserve(struct sysmem *sysmem) { return 0; }

static inline void *sysmem_alloc(enum memblk_id id, phys_size_t size)
{
	return malloc(size);
}

static inline ulong sysmem_alloc_temporary_mem(phys_size_t size)
{
	return 0;
}

static inline void *sysmem_alloc_base(enum memblk_id id,
				      phys_addr_t base, phys_size_t size)
{
	return (void *)base;
}
static inline void *sysmem_alloc_base_by_name(const char *name,
					      phys_addr_t base,
					      phys_size_t size)
{
	return (void *)base;
}
static inline void *sysmem_fdt_reserve_alloc_base(const char *name,
						  phys_addr_t base,
						  phys_size_t size)
{
	return (void *)base;
}
#endif /* CONFIG_SYSMEM */
#endif /* _SYSMEM_H */
