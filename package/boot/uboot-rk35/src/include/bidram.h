/* SPDX-License-Identifier:     GPL-2.0+ */
/*
 * (C) Copyright 2019 Rockchip Electronics Co., Ltd
 */

#ifndef _BIDRAM_H
#define _BIDRAM_H

#include <memblk.h>

typedef struct memblock *(*parse_fn_t)(int *);

struct bidram {
	struct lmb lmb;
	struct list_head reserved_head;
	bool has_init;
	bool fixup;
	u64 base_u64[MEM_RESV_COUNT]; /* 4GB+ */
	u64 size_u64[MEM_RESV_COUNT];
};

#ifdef CONFIG_BIDRAM
/**
 * bidram_initr() - Initial bidram after relocation.
 *
 * @return 0 on success, otherwise error
 */
int bidram_initr(void);

/**
 * bidram_get_ram_size() - Initial bidram and get ram size.
 *
 * @parse_fn: function to parse ddr memory regions
 *
 * @return ram size, 0 on success, otherwise the effect ram size.
 */
phys_size_t bidram_get_ram_size(void);

/**
 * bidram_gen_gd_bi_dram() - Update gd->bd->bi_dram[] according to bidram state.
 */
void bidram_gen_gd_bi_dram(void);

/**
 * bidram_reserve() - Reserve bidram region
 *
 * @id: memblk id
 * @base: region base address
 * @size: region size
 *
 * @return 0 on success, otherwise error
 */
int bidram_reserve(enum memblk_id id, phys_addr_t base, phys_size_t size);

/**
 * bidram_reserve_by_name() - Reserve bidram region by name
 *
 * @name: region name
 * @base: region base address
 * @size: region size
 *
 * @return 0 on success, otherwise error
 */
int bidram_reserve_by_name(const char *name, phys_addr_t base, phys_size_t size);

/**
 * bidram_dump_all() - Dump all bidram stat
 */
void bidram_dump(void);

/**
 * bidram_fixup() - Fixup bi_dram[] for 4GB+ memory
 *
 * @return 0 on success, otherwise error
 */
int bidram_fixup(void);

/**
 * bidram_append_size() - Append 4GB+ memory
 *
 * @return 4GB+ size
 */
u64 bidram_append_size(void);

/**
 * bidram_reserved_is_overlap() - Check outside memory is overlap with reserved
 *
 * @base: region base address
 * @size: region size
 *
 * @return memblk struct when overlap, otherwise NULL
 */
struct memblock *bidram_reserved_is_overlap(phys_addr_t base, phys_size_t size);

/**
 * board_bidram_parse_fn() - Weak function for board to implement
 */
parse_fn_t board_bidram_parse_fn(void);

/**
 * board_bidram_reserve() - Weak function for board to implement
 *
 * @bidram: global bidram point, ignored
 *
 * @return 0 on success, otherwise error
 */
int board_bidram_reserve(struct bidram *bidram);
#else
static inline int bidram_initr(void) { return 0; }
static inline phys_size_t bidram_get_ram_size(void) { return 0; }
static inline void bidram_gen_gd_bi_dram(void) { }
static inline int bidram_reserve(enum memblk_id id, phys_addr_t base,
				 phys_size_t size) { return 0; }
static inline int bidram_reserve_by_name(const char *name, phys_addr_t base,
					 phys_size_t size) { return 0; }
static inline void bidram_dump(void) {}
static inline int bidram_fixup(void) { return 0; }
static inline u64 bidram_append_size(void) { return 0; }
static inline parse_fn_t board_bidram_parse_fn(void) { return NULL; }
static inline int board_bidram_reserve(struct bidram *bidram) { return 0; }
static inline struct memblock *
	bidram_reserved_is_overlap(phys_addr_t base, phys_size_t size)
{
	return NULL;
}

#endif

#endif /* _BIDRAM_H */
