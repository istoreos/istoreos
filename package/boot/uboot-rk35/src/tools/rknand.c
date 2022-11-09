/*
 * Copyright (c) 2017 Paweł Jarosz <paweljarosz3691@gmail.com>
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */

#include "imagetool.h"
#include <image.h>
#include <rc4.h>
#include "mkimage.h"
#include "rkcommon.h"

#define DIV_ROUND_UP(n, d)	(((n) + (d) - 1) / (d))

enum {
	RKNAND_SECT_LEN = RK_BLK_SIZE * 4,
};

struct rknand_info {
	uint32_t pagesize;
	uint32_t itersize;
	uint32_t tplsplsize;
};

struct rknand_info ninfo;

static void rknand_set_header(void *buf, struct stat *sbuf, int ifd,
			     struct image_tool_params *params)
{
	int sector;
	unsigned int size;

	size = params->orig_file_size;

	rkcommon_set_header(buf, sbuf, ifd, params);

	/*
	 * Spread the image out so we only use the first 2KB of each pagesize
	 * region. This is a feature of the NAND format required by the Rockchip
	 * boot ROM.
	 */
	if (params->vflag)
		fprintf(stderr, "Spreading nand image from %u to %u\n",
			size, params->file_size);

	for (sector = ninfo.tplsplsize / ninfo.itersize - 1; sector >= 0;
	     sector--) {
		memmove(buf + ninfo.pagesize + sector * ninfo.itersize,
			buf + RK_SPL_HDR_START + sector * RKNAND_SECT_LEN,
			RKNAND_SECT_LEN);

		memset(buf + ninfo.pagesize + sector * ninfo.itersize +
		       RKNAND_SECT_LEN, 0xFF,
		       ninfo.itersize - RKNAND_SECT_LEN);
	}

	/* Fill up padded area of the header. */
	memset(buf + RK_SPL_HDR_START, 0xFF, ninfo.pagesize - RK_SPL_HDR_START);
}

static int rknand_check_image_type(uint8_t type)
{
	if (type == IH_TYPE_RKNAND)
		return EXIT_SUCCESS;
	else
		return EXIT_FAILURE;
}

static int rknand_vrec_header(struct image_tool_params *params,
			     struct image_type_params *tparams)
{
	int tplsplsize;
	uint32_t skippages;
	int ret;

	rkcommon_vrec_header(params, tparams);

	ret = sscanf(params->extraparams, "%u,%u", &ninfo.pagesize, &skippages);
	if (ret != 2 || (ninfo.pagesize % RKNAND_SECT_LEN)) {
		fprintf(stderr, "%s: Wrong nand params\n", params->cmdname);
		exit(EXIT_FAILURE);
	}

	ninfo.itersize = ninfo.pagesize * (skippages + 1);

	tplsplsize = params->file_size - RK_SPL_HDR_START;
	ninfo.tplsplsize =
		DIV_ROUND_UP(tplsplsize, RKNAND_SECT_LEN) * ninfo.itersize;

	/* Padded file size = padded header + padded tpl & spl. */
	params->file_size = ninfo.pagesize + ninfo.tplsplsize;

	return 0;
}

/*
 * rknand parameters
 */
U_BOOT_IMAGE_TYPE(
	rknand,
	"Rockchip NAND Boot Image support",
	0,
	NULL,
	rkcommon_check_params,
	/* TODO: Support rknand in there helpers */
	NULL, //rkcommon_verify_header,
	NULL, //rkcommon_print_header,
	rknand_set_header,
	NULL,
	rknand_check_image_type,
	NULL,
	rknand_vrec_header
);
