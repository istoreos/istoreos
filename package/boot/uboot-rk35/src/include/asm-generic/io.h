/*
 * Generic I/O functions.
 *
 * Copyright (c) 2016 Imagination Technologies Ltd.
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef __ASM_GENERIC_IO_H__
#define __ASM_GENERIC_IO_H__

/*
 * This file should be included at the end of each architecture-specific
 * asm/io.h such that we may provide generic implementations without
 * conflicting with architecture-specific code.
 */

#ifndef __ASSEMBLY__

/**
 * phys_to_virt() - Return a virtual address mapped to a given physical address
 * @paddr: the physical address
 *
 * Returns a virtual address which the CPU can access that maps to the physical
 * address @paddr. This should only be used where it is known that no dynamic
 * mapping is required. In general, map_physmem should be used instead.
 *
 * Returns: a virtual address which maps to @paddr
 */
#ifndef phys_to_virt
static inline void *phys_to_virt(phys_addr_t paddr)
{
	return (void *)(unsigned long)paddr;
}
#endif

/**
 * virt_to_phys() - Return the physical address that a virtual address maps to
 * @vaddr: the virtual address
 *
 * Returns the physical address which the CPU-accessible virtual address @vaddr
 * maps to.
 *
 * Returns: the physical address which @vaddr maps to
 */
#ifndef virt_to_phys
static inline phys_addr_t virt_to_phys(void *vaddr)
{
	return (phys_addr_t)((unsigned long)vaddr);
}
#endif

/*
 * Flags for use with map_physmem() & unmap_physmem(). Architectures need not
 * support all of these, in which case they will be defined as zero here &
 * ignored. Callers that may run on multiple architectures should therefore
 * treat them as hints rather than requirements.
 */
#ifndef MAP_NOCACHE
# define MAP_NOCACHE	0	/* Produce an uncached mapping */
#endif
#ifndef MAP_WRCOMBINE
# define MAP_WRCOMBINE	0	/* Allow write-combining on the mapping */
#endif
#ifndef MAP_WRBACK
# define MAP_WRBACK	0	/* Map using write-back caching */
#endif
#ifndef MAP_WRTHROUGH
# define MAP_WRTHROUGH	0	/* Map using write-through caching */
#endif

/**
 * map_physmem() - Return a virtual address mapped to a given physical address
 * @paddr: the physical address
 * @len: the length of the required mapping
 * @flags: flags affecting the type of mapping
 *
 * Return a virtual address through which the CPU may access the memory at
 * physical address @paddr. The mapping will be valid for at least @len bytes,
 * and may be affected by flags passed to the @flags argument. This function
 * may create new mappings, so should generally be paired with a matching call
 * to unmap_physmem once the caller is finished with the memory in question.
 *
 * Returns: a virtual address suitably mapped to @paddr
 */
#ifndef map_physmem
static inline void *map_physmem(phys_addr_t paddr, unsigned long len,
				unsigned long flags)
{
	return phys_to_virt(paddr);
}
#endif

/**
 * unmap_physmem() - Remove mappings created by a prior call to map_physmem()
 * @vaddr: the virtual address which map_physmem() previously returned
 * @flags: flags matching those originally passed to map_physmem()
 *
 * Unmap memory which was previously mapped by a call to map_physmem(). If
 * map_physmem() dynamically created a mapping for the memory in question then
 * unmap_physmem() will remove that mapping.
 */
#ifndef unmap_physmem
static inline void unmap_physmem(void *vaddr, unsigned long flags)
{
}
#endif

#endif /* !__ASSEMBLY__ */
#endif /* __ASM_GENERIC_IO_H__ */
