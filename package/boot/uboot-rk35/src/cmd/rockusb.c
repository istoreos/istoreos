/*
 * Copyright 2017 Rockchip Electronics Co., Ltd
 * Frank Wang <frank.wang@rock-chips.com>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <errno.h>
#include <common.h>
#include <command.h>
#include <console.h>
#include <g_dnl.h>
#include <part.h>
#include <usb.h>
#include <usb_mass_storage.h>
#include <rockusb.h>

static struct rockusb rkusb;
static struct rockusb *g_rkusb;

static int rkusb_read_sector(struct ums *ums_dev,
			     ulong start, lbaint_t blkcnt, void *buf)
{
	struct blk_desc *block_dev = &ums_dev->block_dev;
	lbaint_t blkstart = start + ums_dev->start_sector;
	int ret;

	if ((blkstart + blkcnt) > RKUSB_READ_LIMIT_ADDR) {
		memset(buf, 0xcc, blkcnt * SECTOR_SIZE);
		return blkcnt;
	} else {
		ret = blk_dread(block_dev, blkstart, blkcnt, buf);
		if (!ret)
			ret = -EIO;
		return ret;
	}
}

static int rkusb_write_sector(struct ums *ums_dev,
			      ulong start, lbaint_t blkcnt, const void *buf)
{
	struct blk_desc *block_dev = &ums_dev->block_dev;
	lbaint_t blkstart = start + ums_dev->start_sector;
	int ret;

	if (block_dev->if_type == IF_TYPE_MTD)
		block_dev->op_flag |= BLK_MTD_CONT_WRITE;

	ret = blk_dwrite(block_dev, blkstart, blkcnt, buf);
	if (!ret)
		ret = -EIO;

	if (block_dev->if_type == IF_TYPE_MTD)
		block_dev->op_flag &= ~(BLK_MTD_CONT_WRITE);
	return ret;
}

static int rkusb_erase_sector(struct ums *ums_dev,
			      ulong start, lbaint_t blkcnt)
{
	struct blk_desc *block_dev = &ums_dev->block_dev;
	lbaint_t blkstart = start + ums_dev->start_sector;

	return blk_derase(block_dev, blkstart, blkcnt);
}

static void rkusb_fini(void)
{
	int i;

	for (i = 0; i < g_rkusb->ums_cnt; i++)
		free((void *)g_rkusb->ums[i].name);
	free(g_rkusb->ums);
	g_rkusb->ums = NULL;
	g_rkusb->ums_cnt = 0;
	g_rkusb = NULL;
}

#define RKUSB_NAME_LEN 16

static int rkusb_init(const char *devtype, const char *devnums_part_str)
{
	char *s, *t, *devnum_part_str, *name;
	struct blk_desc *block_dev;
	disk_partition_t info;
	int partnum, cnt;
	int ret = -1;
	struct ums *ums_new;

	s = strdup(devnums_part_str);
	if (!s)
		return -1;

	t = s;
	g_rkusb->ums_cnt = 0;

	for (;;) {
		devnum_part_str = strsep(&t, ",");
		if (!devnum_part_str)
			break;

		partnum = blk_get_device_part_str(devtype, devnum_part_str,
					&block_dev, &info, 1);
		if (partnum < 0)
			goto cleanup;

		/* f_mass_storage.c assumes SECTOR_SIZE sectors */
		if (block_dev->blksz != SECTOR_SIZE)
			goto cleanup;

		ums_new = realloc(g_rkusb->ums, (g_rkusb->ums_cnt + 1) *
				  sizeof(*g_rkusb->ums));
		if (!ums_new)
			goto cleanup;
		g_rkusb->ums = ums_new;
		cnt = g_rkusb->ums_cnt;

		/* Expose all partitions for rockusb command */
		g_rkusb->ums[cnt].start_sector = 0;
		g_rkusb->ums[cnt].num_sectors = block_dev->lba;

		g_rkusb->ums[cnt].read_sector = rkusb_read_sector;
		g_rkusb->ums[cnt].write_sector = rkusb_write_sector;
		g_rkusb->ums[cnt].erase_sector = rkusb_erase_sector;

		name = malloc(RKUSB_NAME_LEN);
		if (!name)
			goto cleanup;
		snprintf(name, RKUSB_NAME_LEN, "rkusb disk %d", cnt);
		g_rkusb->ums[cnt].name = name;
		g_rkusb->ums[cnt].block_dev = *block_dev;

		printf("RKUSB: LUN %d, dev %d, hwpart %d, sector %#x, count %#x\n",
		       g_rkusb->ums_cnt,
		       g_rkusb->ums[cnt].block_dev.devnum,
		       g_rkusb->ums[cnt].block_dev.hwpart,
		       g_rkusb->ums[cnt].start_sector,
		       g_rkusb->ums[cnt].num_sectors);

		g_rkusb->ums_cnt++;
	}

	if (g_rkusb->ums_cnt)
		ret = 0;

cleanup:
	free(s);
	if (ret < 0)
		rkusb_fini();

	return ret;
}

static int do_rkusb(cmd_tbl_t *cmdtp, int flag, int argc, char *const argv[])
{
	const char *usb_controller;
	const char *devtype;
	const char *devnum;
	unsigned int controller_index;
	int rc;
	int cable_ready_timeout __maybe_unused;
	const char *s;

	if (argc != 4)
		return CMD_RET_USAGE;

	usb_controller = argv[1];
	devtype = argv[2];
	devnum	= argv[3];

	g_rkusb = &rkusb;
	rc = rkusb_init(devtype, devnum);
	if (rc < 0)
		return CMD_RET_FAILURE;

	if (g_rkusb->ums[0].block_dev.if_type == IF_TYPE_MTD &&
	    g_rkusb->ums[0].block_dev.devnum == BLK_MTD_NAND) {
#ifdef CONFIG_CMD_GO
		pr_err("Enter bootrom rockusb...\n");
		flushc();
		run_command("rbrom", 0);
#else
		pr_err("rockusb: count not support loader upgrade!\n");
#endif
	}

	controller_index = (unsigned int)(simple_strtoul(
				usb_controller,	NULL, 0));
	rc = usb_gadget_initialize(controller_index);
	if (rc) {
		pr_err("Couldn't init USB controller.");
		rc = CMD_RET_FAILURE;
		goto cleanup_rkusb;
	}

	rc = fsg_init(g_rkusb->ums, g_rkusb->ums_cnt);
	if (rc) {
		pr_err("fsg_init failed");
		rc = CMD_RET_FAILURE;
		goto cleanup_board;
	}

	s = env_get("serial#");
	if (s) {
		char *sn = (char *)calloc(strlen(s) + 1, sizeof(char));
		char *sn_p = sn;

		if (!sn)
			goto cleanup_board;

		memcpy(sn, s, strlen(s));
		while (*sn_p) {
			if (*sn_p == '\\' || *sn_p == '/')
				*sn_p = '_';
			sn_p++;
		}

		g_dnl_set_serialnumber(sn);
		free(sn);
	}

	rc = g_dnl_register("rkusb_ums_dnl");
	if (rc) {
		pr_err("g_dnl_register failed");
		rc = CMD_RET_FAILURE;
		goto cleanup_board;
	}

	/* Timeout unit: seconds */
	cable_ready_timeout = UMS_CABLE_READY_TIMEOUT;

	if (!g_dnl_board_usb_cable_connected()) {
		puts("Please connect USB cable.\n");

		while (!g_dnl_board_usb_cable_connected()) {
			if (ctrlc()) {
				puts("\rCTRL+C - Operation aborted.\n");
				rc = CMD_RET_SUCCESS;
				goto cleanup_register;
			}
			if (!cable_ready_timeout) {
				puts("\rUSB cable not detected.\nCommand exit.\n");
				rc = CMD_RET_SUCCESS;
				goto cleanup_register;
			}

			printf("\rAuto exit in: %.2d s.", cable_ready_timeout);
			mdelay(1000);
			cable_ready_timeout--;
		}
		puts("\r\n");
	}

	while (1) {
		usb_gadget_handle_interrupts(controller_index);

		rc = fsg_main_thread(NULL);
		if (rc) {
			/* Check I/O error */
			if (rc == -EIO)
				printf("\rCheck USB cable connection\n");

			/* Check CTRL+C */
			if (rc == -EPIPE)
				printf("\rCTRL+C - Operation aborted\n");

			rc = CMD_RET_SUCCESS;
			goto cleanup_register;
		}
	}

cleanup_register:
	g_dnl_unregister();
cleanup_board:
	usb_gadget_release(controller_index);
cleanup_rkusb:
	rkusb_fini();

	return rc;
}

U_BOOT_CMD_ALWAYS(rockusb, 4, 1, do_rkusb,
		  "Use the rockusb Protocol",
		  "<USB_controller> <devtype> <dev[:part]>  e.g. rockusb 0 mmc 0\n"
);
