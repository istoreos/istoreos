// SPDX-License-Identifier: GPL-2.0+
/*
 * The 'rng' command prints bytes from the hardware random number generator.
 *
 * Copyright (c) 2019, Heinrich Schuchardt <xypron.glpk@gmx.de>
 */
#include <common.h>
#include <command.h>
#include <dm.h>
#include <hexdump.h>
#include <rng.h>

static int do_rng(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	size_t n = 0x40;
	struct udevice *dev;
	void *buf;
	int ret = CMD_RET_SUCCESS;

	if (uclass_get_device(UCLASS_RNG, 0, &dev) || !dev) {
		printf("No RNG device\n");
		return CMD_RET_FAILURE;
	}

	if (argc >= 2)
		n = simple_strtoul(argv[1], NULL, 16);

	buf = malloc(n);
	if (!buf) {
		printf("Out of memory\n");
		return CMD_RET_FAILURE;
	}

	if (dm_rng_read(dev, buf, n)) {
		printf("Reading RNG failed\n");
		ret = CMD_RET_FAILURE;
	} else {
		print_hex_dump_bytes("", DUMP_PREFIX_OFFSET, buf, n);
	}

	free(buf);

	return ret;
}

#ifdef CONFIG_SYS_LONGHELP
static char rng_help_text[] =
	"[n]\n"
	"  - print n random bytes\n";
#endif

U_BOOT_CMD(
	rng, 2, 0, do_rng,
	"print bytes from the hardware random number generator",
	rng_help_text
);
