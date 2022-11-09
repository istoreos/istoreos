/*
 * (C) Copyright 2019 Rockchip Electronics Co., Ltd
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */

#include <common.h>
#include <bootm.h>
#include <boot_rkimg.h>
#include <console.h>
#include <image.h>
#include <malloc.h>
#include <sysmem.h>
#include <linux/libfdt.h>
#include <asm/arch-rockchip/hotkey.h>
#include <asm/arch-rockchip/resource_img.h>
#include <asm/arch-rockchip/boot_mode.h>
#include <asm/arch-rockchip/uimage.h>

DECLARE_GLOBAL_DATA_PTR;

static void *do_boot_uimage_storage(void)
{
	return uimage_load_bootables();
}

static void *do_boot_uimage_ram(char *const argv[])
{
	image_header_t *hdr;
	int blknum;
	
	hdr = (void *)simple_strtoul(argv[1], NULL, 16);
	if (!hdr || !image_check_magic(hdr)) {
		UIMG_I("Invalid header");
		return NULL;
	}

	if (image_get_type(hdr) != IH_TYPE_MULTI) {
		UIMG_I("Invalid multi images\n");
		return NULL;
	}

	/* reserve this full uImage */
	blknum = DIV_ROUND_UP(image_get_image_size(hdr), RK_BLK_SIZE);
	if (!sysmem_alloc_base(MEM_UIMAGE_USER, (phys_addr_t)hdr,
			       blknum * RK_BLK_SIZE))
		return NULL;

	return hdr;
}

static int do_boot_uimage(cmd_tbl_t *cmdtp, int flag,
			  int argc, char *const argv[])
{
	char *bootm_args[1];
	image_header_t *img;
	char uimg_addr[12];
	u32 ramdisk_sz = 0;
	int ret;

	if (argc > 2)
		return CMD_RET_USAGE;

	printf("\n## Booting Multi uImage ");

	if (argc == 1)
		img = do_boot_uimage_storage();
	else
		img = do_boot_uimage_ram(argv);

	if (!img) {
		UIMG_I("Failed to load multi images\n");
		goto out;
	}

	if (uimage_sysmem_reserve_each(img, &ramdisk_sz))
		goto out;

	snprintf(uimg_addr, sizeof(uimg_addr), "0x%lx", (ulong)img);
	bootm_args[0] = uimg_addr;

	printf("at %s\n", uimg_addr);

	ret = do_bootm_states(NULL, 0, ARRAY_SIZE(bootm_args), bootm_args,
		BOOTM_STATE_START |
		BOOTM_STATE_FINDOS | BOOTM_STATE_FINDOTHER |
		BOOTM_STATE_LOADOS |
#ifdef CONFIG_SYS_BOOT_RAMDISK_HIGH
		BOOTM_STATE_RAMDISK |
#endif
		BOOTM_STATE_OS_PREP | BOOTM_STATE_OS_FAKE_GO |
		BOOTM_STATE_OS_GO, &images, 1);

	if (ret && argc != 1) {
		uimage_sysmem_free_each(img, ramdisk_sz);
		goto out;
	}

	return CMD_RET_SUCCESS;
out:
	return CMD_RET_FAILURE;
}

U_BOOT_CMD(
	boot_uimage,  2,     1,      do_boot_uimage,
	"Boot Legacy uImage from memory or boot(recovery) partitions",
	"boot_uimage [addr]"
);
