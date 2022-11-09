/*
 * Copyright (C) 2016 The Android Open Source Project
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef __ANDROID_BOOTLOADER_H
#define __ANDROID_BOOTLOADER_H

#include <common.h>

enum android_boot_mode {
	ANDROID_BOOT_MODE_NORMAL = 0,

	/* "recovery" mode is triggered by the "reboot recovery" command or
	 * equivalent adb/fastboot command. It can also be triggered by writing
	 * "boot-recovery" in the BCB message. This mode should boot the
	 * recovery kernel.
	 */
	ANDROID_BOOT_MODE_RECOVERY,

	/* "bootloader" mode is triggered by the "reboot bootloader" command or
	 * equivalent adb/fastboot command. It can also be triggered by writing
	 * "bootonce-bootloader" in the BCB message. This mode should boot into
	 * fastboot.
	 */
	ANDROID_BOOT_MODE_BOOTLOADER,
};

/** android_bootloader_boot_flow - Execute the Android Bootloader Flow.
 * Performs the Android Bootloader boot flow, loading the appropriate Android
 * image (normal kernel, recovery kernel or "bootloader" mode) and booting it.
 * The boot mode is determined by the contents of the Android Bootloader
 * Message. On success it doesn't return.
 *
 * @dev_desc:		device where to load the kernel and system to boot from.
 * @load_address:	address where to load the boot img if needed.
 *
 * @return a negative number in case of error, otherwise it doesn't return.
 */
int android_bootloader_boot_flow(struct blk_desc *dev_desc,
				 unsigned long load_address);

/** android_avb_boot_flow - Execute the Android Bootloader Flow.
 * This fuction use to select and boot kernel through ab_suffix.
 *
 * @kernel_address:	address where to load the kernel if needed.
 *
 * @return a negative number in case of error, otherwise it doesn't return.
 */
int android_avb_boot_flow(unsigned long kernel_address);

/** android_assemble_cmdline - Assemble args for cmdline.
 *
 * @ab_suffix:		the boot slot to boot from.
 * @extra_args:   	select the args to command line.
 *
 * @return a negative number in case of error, otherwise it doesn't return.
 */
char *android_assemble_cmdline(const char *slot_suffix,
			       const char *extra_args);

/** android_bootloader_boot_kernel- Execute the kernel boot.
 *
 * @kernel_address:	address where to load the kernel if needed.
 *
 * @return a negative number in case of error, otherwise it doesn't return.
 */
int android_bootloader_boot_kernel(unsigned long kernel_address);

/** android_bootloader_boot_kernel- Load and execute the kernel boot.
 *
 * @kernel_address:	address where to load the kernel if needed.
 *
 * @return a negative number in case of error, otherwise it doesn't return.
 */
int android_boot_flow(unsigned long kernel_address);

/** str_append- add str to tail.
 *
 * @base_name:	base name address.
 * @slot_suffix: suffix.
 *
 * @return (base name + suffix)address.
 */
char *android_str_append(char *base_name, char *slot_suffix);

/** anrdroid_fdt_overlay_apply- apply fdt overlay.
 *
 * @fdt_addr: fdt blob.
 *
 * @return 0 on success, otherwise failed.
 */
int android_fdt_overlay_apply(void *fdt_addr);

/** android_bcb_write- write the android bootloader message.
 *
 * @cmd: boot command
 *
 * @return 0 on success, otherwise failed.
 */
int android_bcb_write(char *cmd);

#endif  /* __ANDROID_BOOTLOADER_H */
