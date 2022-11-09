/*
 * Genericish driver for memory mapped NAND devices
 *
 * Copyright (c) 2006-2009 Analog Devices Inc.
 * Licensed under the GPL-2 or later.
 */

/* Your board must implement the following macros:
 *  NAND_PLAT_WRITE_CMD(chip, cmd)
 *  NAND_PLAT_WRITE_ADR(chip, cmd)
 *  NAND_PLAT_INIT()
 *
 * It may also implement the following:
 *  NAND_PLAT_DEV_READY(chip)
 */

#include <common.h>
#include <asm/io.h>
#ifdef NAND_PLAT_GPIO_DEV_READY
# include <asm/gpio.h>
# define NAND_PLAT_DEV_READY(chip) gpio_get_value(NAND_PLAT_GPIO_DEV_READY)
#endif

#include <nand.h>

static void plat_cmd_ctrl(struct mtd_info *mtd, int cmd, unsigned int ctrl)
{
	struct nand_chip *this = mtd_to_nand(mtd);

	if (cmd == NAND_CMD_NONE)
		return;

	if (ctrl & NAND_CLE)
		NAND_PLAT_WRITE_CMD(this, cmd);
	else
		NAND_PLAT_WRITE_ADR(this, cmd);
}

#ifdef NAND_PLAT_DEV_READY
static int plat_dev_ready(struct mtd_info *mtd)
{
	return NAND_PLAT_DEV_READY((struct nand_chip *)mtd_to_nand(mtd));
}
#else
# define plat_dev_ready NULL
#endif

int board_nand_init(struct nand_chip *nand)
{
#ifdef NAND_PLAT_GPIO_DEV_READY
	gpio_request(NAND_PLAT_GPIO_DEV_READY, "nand-plat");
	gpio_direction_input(NAND_PLAT_GPIO_DEV_READY);
#endif

#ifdef NAND_PLAT_INIT
	NAND_PLAT_INIT();
#endif

	nand->cmd_ctrl = plat_cmd_ctrl;
	nand->dev_ready = plat_dev_ready;
	nand->ecc.mode = NAND_ECC_SOFT;

	return 0;
}
