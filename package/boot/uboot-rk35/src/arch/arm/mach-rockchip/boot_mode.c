/*
 * (C) Copyright 2016 Rockchip Electronics Co., Ltd
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */

#include <common.h>
#include <boot_rkimg.h>
#include <malloc.h>
#include <asm/io.h>
#include <asm/arch-rockchip/boot_mode.h>
#include <usb.h>
#include <dm/device.h>

DECLARE_GLOBAL_DATA_PTR;

enum {
	PH = 0,	/* P: Priority, H: high, M: middle, L: low*/
	PM,
	PL,
};

#ifdef CONFIG_ANDROID_BOOT_IMAGE
static int misc_require_recovery(u32 bcb_offset, int *bcb_recovery_msg)
{
	struct bootloader_message *bmsg;
	struct blk_desc *dev_desc;
	disk_partition_t part;
	int cnt, recovery = 0;

	dev_desc = rockchip_get_bootdev();
	if (!dev_desc) {
		printf("dev_desc is NULL!\n");
		goto out;
	}

	if (part_get_info_by_name(dev_desc, PART_MISC, &part) < 0) {
		printf("No misc partition\n");
		goto out;
	}

	cnt = DIV_ROUND_UP(sizeof(struct bootloader_message), dev_desc->blksz);
	bmsg = memalign(ARCH_DMA_MINALIGN, cnt * dev_desc->blksz);
	if (blk_dread(dev_desc, part.start + bcb_offset, cnt, bmsg) != cnt) {
		recovery = 0;
	} else {
		recovery = !strcmp(bmsg->command, "boot-recovery");
		if (bcb_recovery_msg) {
			if (!strcmp(bmsg->recovery, "recovery\n--rk_fwupdate\n"))
				*bcb_recovery_msg = BCB_MSG_RECOVERY_RK_FWUPDATE;
			else if (!strcmp(bmsg->recovery, "recovery\n--factory_mode=whole") ||
				 !strcmp(bmsg->recovery, "recovery\n--factory_mode=small"))
				*bcb_recovery_msg = BCB_MSG_RECOVERY_PCBA;
		}
	}

	free(bmsg);
out:
	return recovery;
}

int get_bcb_recovery_msg(void)
{
	int bcb_recovery_msg = BCB_MSG_RECOVERY_NONE;
	u32 bcb_offset = android_bcb_msg_sector_offset();
	misc_require_recovery(bcb_offset, &bcb_recovery_msg);

	return bcb_recovery_msg;
}
#endif

/*
 * There are three ways to get reboot-mode:
 *
 * No1. Android BCB which is defined in misc.img (0KB or 16KB offset)
 * No2. CONFIG_ROCKCHIP_BOOT_MODE_REG that supports "reboot xxx" commands
 * No3. Env variable "reboot_mode" which is added by U-Boot
 *
 * Recovery mode from:
 *	- Android BCB in misc.img
 *	- "reboot recovery" command
 *	- recovery key pressed without usb attach
 */
int rockchip_get_boot_mode(void)
{
	static int boot_mode[] =		/* static */
		{ -EINVAL, -EINVAL, -EINVAL };
	static int bcb_offset = -EINVAL;	/* static */
	uint32_t reg_boot_mode;
	char *env_reboot_mode;
	int clear_boot_reg = 0;
#ifdef CONFIG_ANDROID_BOOT_IMAGE
	int recovery_msg = 0;
	u32 offset = android_bcb_msg_sector_offset();
#else
	u32 offset = BCB_MESSAGE_BLK_OFFSET;
#endif

	/*
	 * Env variable "reboot_mode" which is added by U-Boot, reading ever time.
	 */
	env_reboot_mode = env_get("reboot_mode");
	if (env_reboot_mode) {
		if (!strcmp(env_reboot_mode, "recovery-key")) {
			printf("boot mode: recovery (key)\n");
			return BOOT_MODE_RECOVERY;
		} else if (!strcmp(env_reboot_mode, "recovery-usb")) {
			printf("boot mode: recovery (usb)\n");
			return BOOT_MODE_RECOVERY;
		} else if (!strcmp(env_reboot_mode, "recovery")) {
			printf("boot mode: recovery (env)\n");
			return BOOT_MODE_RECOVERY;
		} else if (!strcmp(env_reboot_mode, "fastboot")) {
			printf("boot mode: fastboot\n");
			return BOOT_MODE_BOOTLOADER;
		}
	}

	/*
	 * Android BCB special handle:
	 *    Once the Android BCB offset changed, reinitalize "boot_mode[PM]".
	 *
	 * Background:
	 *    1. there are two Android BCB at the 0KB(google) and 16KB(rk)
	 *       offset in misc.img
	 *    2. Android image: return 0KB offset if image version >= 10,
	 *	 otherwise 16KB
	 *    3. Not Android image: return 16KB offset, eg: FIT image.
	 *
	 * To handle the cases of 16KB and 0KB, we reinitial boot_mode[PM] once
	 * Android BCB is changed.
	 *
	 * PH and PL is from boot mode register and reading once.
	 * PM is from misc.img and should be updated if BCB offset is changed.
	 * Return the boot mode according to priority: PH > PM > PL.
	 */
	if (bcb_offset != offset) {
		boot_mode[PM] = -EINVAL;
		bcb_offset = offset;
	}

	/* directly return if there is already valid mode */
	if (boot_mode[PH] != -EINVAL)
		return boot_mode[PH];
	else if (boot_mode[PM] != -EINVAL)
		return boot_mode[PM];
	else if (boot_mode[PL] != -EINVAL)
		return boot_mode[PL];

	/*
	 * Boot mode priority
	 *
	 * Anyway, we should set download boot mode as the highest priority, so:
	 * reboot loader/bootloader/fastboot > misc partition "recovery" > reboot xxx.
	 */
	reg_boot_mode = readl((void *)CONFIG_ROCKCHIP_BOOT_MODE_REG);
	if (reg_boot_mode == BOOT_LOADER) {
		printf("boot mode: loader\n");
		boot_mode[PH] = BOOT_MODE_LOADER;
		clear_boot_reg = 1;
	} else if (reg_boot_mode == BOOT_DFU) {
		printf("boot mode: dfu\n");
		boot_mode[PH] = BOOT_MODE_DFU;
		clear_boot_reg = 1;
	} else if (reg_boot_mode == BOOT_FASTBOOT) {
		printf("boot mode: bootloader\n");
		boot_mode[PH] = BOOT_MODE_BOOTLOADER;
		clear_boot_reg = 1;
#ifdef CONFIG_ANDROID_BOOT_IMAGE
	} else if (misc_require_recovery(bcb_offset, &recovery_msg)) {
		printf("boot mode: recovery (misc)\n");
		boot_mode[PM] = BOOT_MODE_RECOVERY;
#endif
	} else {
		switch (reg_boot_mode) {
		case BOOT_NORMAL:
			printf("boot mode: normal\n");
			boot_mode[PL] = BOOT_MODE_NORMAL;
			clear_boot_reg = 1;
			break;
		case BOOT_RECOVERY:
			printf("boot mode: recovery (cmd)\n");
			boot_mode[PL] = BOOT_MODE_RECOVERY;
			clear_boot_reg = 1;
			break;
		case BOOT_UMS:
			printf("boot mode: ums\n");
			boot_mode[PL] = BOOT_MODE_UMS;
			clear_boot_reg = 1;
			break;
		case BOOT_CHARGING:
			printf("boot mode: charging\n");
			boot_mode[PL] = BOOT_MODE_CHARGING;
			clear_boot_reg = 1;
			break;
		case BOOT_PANIC:
			printf("boot mode: panic\n");
			boot_mode[PL] = BOOT_MODE_PANIC;
			break;
		case BOOT_WATCHDOG:
			printf("boot mode: watchdog\n");
			boot_mode[PL] = BOOT_MODE_WATCHDOG;
			break;
		default:
			printf("boot mode: None\n");
			boot_mode[PL] = BOOT_MODE_UNDEFINE;
		}
	}

	/*
	 * We don't clear boot mode reg when its value stands for the reboot
	 * reason or others(in the future), the kernel will need and clear it.
	 */
	if (clear_boot_reg)
		writel(BOOT_NORMAL, (void *)CONFIG_ROCKCHIP_BOOT_MODE_REG);

	if (boot_mode[PH] != -EINVAL)
		return boot_mode[PH];
	else if (boot_mode[PM] != -EINVAL)
		return boot_mode[PM];
	else
		return boot_mode[PL];
}

int setup_boot_mode(void)
{
	char env_preboot[256] = {0};
	int dev_type;
	int devnum;
	struct blk_desc *dev_desc;
	const char *storage_node;
	const char *bootargs;
	char boot_options[1024] = {0};

	dev_type = get_bootdev_type();
	devnum = env_get_ulong("devnum", 10, 0);

	dev_desc = blk_get_devnum_by_type(dev_type, devnum);
	if (!dev_desc) {
		printf("%s: Can't find dev_desc!\n", __func__);
		return -1;
	}

	if (dev_type == IF_TYPE_MMC) {
		storage_node = dev_desc->bdev->parent->node.np->full_name;
	} else if (dev_type == IF_TYPE_USB) {
		struct udevice *usb_bus;
		usb_bus = usb_get_bus(dev_desc->bdev);
		storage_node = usb_bus->node.np->full_name;
	} else if (dev_type == IF_TYPE_SCSI) {
		struct udevice *sata_dev = dev_desc->bdev;
		struct udevice *sata_bus;
		for (sata_bus = sata_dev; sata_bus && device_get_uclass_id(sata_bus) != UCLASS_AHCI; )
			sata_bus = sata_bus->parent;
		if (!sata_bus) {
			/* By design this cannot happen */
			assert(sata_bus);
		}
		storage_node = sata_bus->node.np->full_name;
	} else if (dev_type == IF_TYPE_NVME) {
		struct udevice *nvme_dev = dev_desc->bdev;
		struct udevice *nvme_bus;
		for (nvme_bus = nvme_dev; nvme_bus && device_get_uclass_id(nvme_bus) != UCLASS_PCI; )
			nvme_bus = nvme_bus->parent;
		nvme_bus = nvme_bus->parent;
		if (!nvme_bus) {
			/* By design this cannot happen */
			assert(nvme_bus);
		}
		storage_node = nvme_bus->node.np->full_name;
	} else {
		storage_node = "null";
	}
	bootargs = env_get("bootargs");
	snprintf(boot_options, sizeof(boot_options),
		"%s storagenode=%s ", bootargs, storage_node);
	env_update("bootargs", boot_options);

	switch (rockchip_get_boot_mode()) {
	case BOOT_MODE_BOOTLOADER:
		printf("enter fastboot!\n");
#if defined(CONFIG_FASTBOOT_FLASH_MMC_DEV)
		snprintf(env_preboot, 256,
				"setenv preboot; mmc dev %x; fastboot usb 0; ",
				CONFIG_FASTBOOT_FLASH_MMC_DEV);
#elif defined(CONFIG_FASTBOOT_FLASH_NAND_DEV)
		snprintf(env_preboot, 256,
				"setenv preboot; fastboot usb 0; ");
#endif
		env_set("preboot", env_preboot);
		break;
	case BOOT_MODE_UMS:
		printf("enter UMS!\n");
		env_set("preboot", "setenv preboot; ums mmc 0");
		break;
#if defined(CONFIG_CMD_DFU)
	case BOOT_MODE_DFU:
		printf("enter DFU!\n");
		env_set("preboot", "setenv preboot; dfu 0 ${devtype} ${devnum}; rbrom");
		break;
#endif
	case BOOT_MODE_LOADER:
		printf("enter Rockusb!\n");
		env_set("preboot", "setenv preboot; rockusb 0 ${devtype} ${devnum}; rbrom");
		break;
	case BOOT_MODE_CHARGING:
		printf("enter charging!\n");
		env_set("preboot", "setenv preboot; charge");
		break;
	}

	return 0;
}
