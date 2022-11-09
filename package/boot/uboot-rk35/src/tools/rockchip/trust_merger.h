/*
 * Rockchip trust image generator
 *
 * (C) Copyright 2008-2015 Fuzhou Rockchip Electronics Co., Ltd
 * Peter, Software Engineering, <superpeter.cai@gmail.com>.
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */
#ifndef TRUST_MERGER_H
#define TRUST_MERGER_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <stdbool.h>


#define VERSION             "v1.0 (2015-06-15)"
#define DO_ALIGN(a, b)	(((a) > 0) ? ((((a) - 1) / (b) + 1) * (b)) : (a))


/* config file */
#define SEC_VERSION         "[VERSION]"
#define SEC_BL30            "[BL30_OPTION]"
#define SEC_BL31            "[BL31_OPTION]"
#define SEC_BL32            "[BL32_OPTION]"
#define SEC_BL33            "[BL33_OPTION]"
#define SEC_OUT             "[OUTPUT]"

#define OPT_MAJOR           "MAJOR"
#define OPT_MINOR           "MINOR"
#define OPT_SEC             "SEC"
#define OPT_PATH            "PATH"
#define OPT_ADDR            "ADDR"
#define OPT_OUT_PATH        "PATH"

/* options */
#define OPT_VERBOSE         "--verbose"
#define OPT_HELP            "--help"
#define OPT_VERSION         "--version"
#define OPT_MERGE           "--pack"
#define OPT_UNPACK          "--unpack"
#define OPT_SUBFIX          "--subfix"
#define OPT_REPLACE         "--replace"
#define OPT_PREPATH         "--prepath"
#define OPT_RSA		    "--rsa"
#define OPT_SHA		    "--sha"
#define OPT_SIZE	    "--size"
#define OPT_IGNORE_BL32     "--ignore-bl32"

#define DEF_MAJOR           0
#define DEF_MINOR           0
#define DEF_BL30_PATH       "bl30.bin"
#define DEF_BL31_PATH       "bl31.bin"
#define DEF_BL32_PATH       "bl32.bin"
#define DEF_BL33_PATH       "bl33.bin"

#define DEF_OUT_PATH        "trust.img"

#define DEF_CONFIG_FILE     "RKTRUST.ini"


#define MAX_LINE_LEN        256
#define SCANF_EAT(in)       fscanf(in, "%*[ \r\n\t/]")

#define ENTRY_ALIGN         (2048)

enum {
	BL30_SEC = 0,
	BL31_SEC,
	BL32_SEC,
	BL33_SEC,
	BL_MAX_SEC
};



typedef struct {
	bool		sec;
	uint32_t	id;
	char		path[MAX_LINE_LEN];
	uint32_t	addr;
	uint32_t	offset;
	uint32_t	size;
	uint32_t	align_size;
} bl_entry_t;

typedef struct {
	uint16_t	major;
	uint16_t	minor;
	bl_entry_t	bl3x[BL_MAX_SEC];
	char	outPath[MAX_LINE_LEN];
} OPT_T;


#define TRUST_HEAD_TAG			"BL3X"
#define SIGNATURE_SIZE			256
#define TRUST_HEADER_SIZE		2048

typedef struct {
	uint32_t tag;
	uint32_t version;
	uint32_t flags;
	uint32_t size;
	uint32_t reserved[4];
	uint32_t RSA_N[64];
	uint32_t RSA_E[64];
	uint32_t RSA_C[64];
} TRUST_HEADER, *PTRUST_HEADER;


typedef struct {
	uint32_t HashData[8];
	uint32_t LoadAddr;
	uint32_t LoadSize;
	uint32_t reserved[2];
} COMPONENT_DATA, *PCOMPONENT_DATA;


typedef struct {
	uint32_t ComponentID;
	uint32_t StorageAddr;
	uint32_t ImageSize;
	uint32_t reserved;
} TRUST_COMPONENT, *PTRUST_COMPONENT;

#define EI_NIDENT	16
#define ELF_MAGIC 0x464c457f

typedef struct {
	uint8_t	e_ident[EI_NIDENT];
	uint16_t	e_type;
	uint16_t	e_machine;
	uint32_t	e_version;
	uint32_t	e_entry;  /* Entry point */
	uint32_t	e_phoff;
	uint32_t	e_shoff;
	uint32_t	e_flags;
	uint16_t	e_ehsize;
	uint16_t	e_phentsize;
	uint16_t	e_phnum;
	uint16_t	e_shentsize;
	uint16_t	e_shnum;
	uint16_t	e_shstrndx;
} Elf32_Ehdr;

typedef struct {
	uint8_t	e_ident[EI_NIDENT];	/* ELF "magic number" */
	uint16_t e_type;
	uint16_t e_machine;
	uint32_t e_version;
	uint64_t e_entry;		/* Entry point virtual address */
	uint64_t e_phoff;		/* Program header table file offset */
	uint64_t e_shoff;		/* Section header table file offset */
	uint32_t e_flags;
	uint16_t e_ehsize;
	uint16_t e_phentsize;
	uint16_t e_phnum;
	uint16_t e_shentsize;
	uint16_t e_shnum;
	uint16_t e_shstrndx;
} Elf64_Ehdr;

typedef struct {
	uint32_t	p_type;
	uint32_t	p_offset;
	uint32_t	p_vaddr;
	uint32_t	p_paddr;
	uint32_t	p_filesz;
	uint32_t	p_memsz;
	uint32_t	p_flags;
	uint32_t	p_align;
} Elf32_Phdr;

typedef struct {
	uint32_t p_type;
	uint32_t p_flags;
	uint64_t p_offset;		/* Segment file offset */
	uint64_t p_vaddr;		/* Segment virtual address */
	uint64_t p_paddr;		/* Segment physical address */
	uint64_t p_filesz;		/* Segment size in file */
	uint64_t p_memsz;		/* Segment size in memory */
	uint64_t p_align;		/* Segment alignment, file & memory */
} Elf64_Phdr;

#endif /* TRUST_MERGER_H */
