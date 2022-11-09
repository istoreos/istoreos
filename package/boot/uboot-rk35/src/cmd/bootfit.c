/*
 * (C) Copyright 2019 Rockchip Electronics Co., Ltd
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */

#include <common.h>
#include <android_ab.h>
#include <bootm.h>
#include <boot_rkimg.h>
#include <image.h>
#include <malloc.h>
#include <sysmem.h>
#include <asm/arch-rockchip/fit.h>

DECLARE_GLOBAL_DATA_PTR;

static void *do_boot_fit_storage(ulong *size)
{
	return fit_image_load_bootables(size);
}

static void *do_boot_fit_ram(char *const argv[], ulong *data_size)
{
	void *fit;
	int size;

	fit = (void *)simple_strtoul(argv[1], NULL, 16);
	if (!fit || fdt_check_header(fit)) {
		FIT_I("Invalid header\n");
		return NULL;
	}

	size = fit_image_get_bootables_size(fit);
	if (!size) {
		FIT_I("Failed to get bootable image size\n");
		return NULL;
	}

	/* reserve this full FIT image */
	if (!sysmem_alloc_base(MEM_FIT_USER,
			       (phys_addr_t)fit, ALIGN(size, 512)))
		return NULL;

	*data_size = size;

	return fit;
}

/*
 * argc == 1:
 *	FIT image is loaded from storage(eg. CONFIG_BOOTCOMMAND).
 *
 * argc == 2:
 *	FIT image is already in ram, the booflow is:
 *		CLI cmd "bootm <fit_addr>" => do_bootm() =>
 *		board_do_bootm() => boot_fit <fit_addr>
 */
static int do_boot_fit(cmd_tbl_t *cmdtp, int flag, int argc, char *const argv[])
{
	char *bootm_args[1];
	char fit_addr[12];
	ulong size;
	void *fit;
	int ret;

	if (argc > 2)
		return CMD_RET_USAGE;

	printf("## Booting FIT Image ");

	if (argc == 1)
		fit = do_boot_fit_storage(&size);
	else
		fit = do_boot_fit_ram(argv, &size);

	if (!fit) {
		FIT_I("No FIT image\n");
		goto out;
	}

	if (fdt_check_header(fit)) {
		FIT_I("Invalid FIT format\n");
		goto out;
	}

	/* fixup entry/load and alloc sysmem */
	if (fit_image_pre_process(fit))
		goto out;

	env_set("bootm-no-reloc", "y");
	snprintf(fit_addr, sizeof(fit_addr), "0x%lx", (ulong)fit);
	bootm_args[0] = fit_addr;

	printf("at %s with size 0x%08lx\n", fit_addr, size);

#ifdef CONFIG_ANDROID_AB
	char slot_suffix[3] = {0};
	char slot_info[21] = "android_slotsufix=";

	if (ab_get_slot_suffix(slot_suffix))
		goto out;

	strcat(slot_info, slot_suffix);
	env_update("bootargs", slot_info);
	ab_update_root_uuid();
#endif

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
		fit_image_fail_process(fit);
		goto out;
	}

	return CMD_RET_SUCCESS;
out:
	return CMD_RET_FAILURE;
}

U_BOOT_CMD_ALWAYS(
	boot_fit,  2,     1,      do_boot_fit,
	"Boot FIT Image from memory or boot/recovery partition",
	"boot_fit [addr]"
);
