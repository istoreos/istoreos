/*
 * (C) Copyright 2009
 * Heiko Schocher, DENX Software Engineering, hs@denx.de
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <common.h>
#include <nand.h>
#include <asm/io.h>

#define CONFIG_NAND_MODE_REG	(void *)(CONFIG_SYS_NAND_BASE + 0x20000)
#define CONFIG_NAND_DATA_REG	(void *)(CONFIG_SYS_NAND_BASE + 0x30000)

#define read_mode()	in_8(CONFIG_NAND_MODE_REG)
#define write_mode(val)	out_8(CONFIG_NAND_MODE_REG, val)
#define read_data()	in_8(CONFIG_NAND_DATA_REG)
#define write_data(val)	out_8(CONFIG_NAND_DATA_REG, val)

#define KPN_RDY2	(1 << 7)
#define KPN_RDY1	(1 << 6)
#define KPN_WPN		(1 << 4)
#define KPN_CE2N	(1 << 3)
#define KPN_CE1N	(1 << 2)
#define KPN_ALE		(1 << 1)
#define KPN_CLE		(1 << 0)

#define KPN_DEFAULT_CHIP_DELAY 50

static int kpn_chip_ready(void)
{
	if (read_mode() & KPN_RDY1)
		return 1;

	return 0;
}

static void kpn_wait_rdy(void)
{
	int cnt = 1000000;

	while (--cnt && !kpn_chip_ready())
		udelay(1);

	if (!cnt)
		printf ("timeout while waiting for RDY\n");
}

static void kpn_nand_hwcontrol(struct mtd_info *mtd, int cmd, unsigned int ctrl)
{
	u8 reg_val = read_mode();

	if (ctrl & NAND_CTRL_CHANGE) {
		reg_val = reg_val & ~(KPN_ALE + KPN_CLE);

		if (ctrl & NAND_CLE)
			reg_val = reg_val | KPN_CLE;
		if (ctrl & NAND_ALE)
			reg_val = reg_val | KPN_ALE;
		if (ctrl & NAND_NCE)
			reg_val = reg_val & ~KPN_CE1N;
		else
			reg_val = reg_val | KPN_CE1N;

		write_mode(reg_val);
	}
	if (cmd != NAND_CMD_NONE)
		write_data(cmd);

	/* wait until flash is ready */
	kpn_wait_rdy();
}

static u_char kpn_nand_read_byte(struct mtd_info *mtd)
{
	return read_data();
}

static void kpn_nand_write_buf(struct mtd_info *mtd, const u_char *buf, int len)
{
	int i;

	for (i = 0; i < len; i++) {
		write_data(buf[i]);
		kpn_wait_rdy();
	}
}

static void kpn_nand_read_buf(struct mtd_info *mtd, u_char *buf, int len)
{
	int i;

	for (i = 0; i < len; i++)
		buf[i] = read_data();
}

static int kpn_nand_dev_ready(struct mtd_info *mtd)
{
	kpn_wait_rdy();

	return 1;
}

int board_nand_init(struct nand_chip *nand)
{
#if defined(CONFIG_NAND_ECC_BCH)
	nand->ecc.mode = NAND_ECC_SOFT_BCH;
#else
	nand->ecc.mode = NAND_ECC_SOFT;
#endif

	/* Reference hardware control function */
	nand->cmd_ctrl  = kpn_nand_hwcontrol;
	nand->read_byte  = kpn_nand_read_byte;
	nand->write_buf  = kpn_nand_write_buf;
	nand->read_buf   = kpn_nand_read_buf;
	nand->dev_ready  = kpn_nand_dev_ready;
	nand->chip_delay = KPN_DEFAULT_CHIP_DELAY;

	/* reset mode register */
	write_mode(KPN_CE1N + KPN_CE2N + KPN_WPN);
	return 0;
}
