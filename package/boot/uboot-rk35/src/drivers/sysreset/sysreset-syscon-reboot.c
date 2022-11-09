/*
 * (C) Copyright 2019 Rockchip Electronics Co., Ltd
 *
 * SPDX-License-Identifier: GPL-2.0
 */

#include <common.h>
#include <dm.h>
#include <sysreset.h>
#include <linux/io.h>
#include <asm/arch-rockchip/boot_mode.h>

#define CMD_PREFIX	"mode-"

struct command {
	const char *name;
	u32 magic;
};

static const struct command static_defined_command[] = {
	{ .name = "bootrom", .magic = BOOT_BROM_DOWNLOAD, }
};

static int syscon_reboot_request_by_mode(struct udevice *dev, const char *mode)
{
	const char *prefix = CMD_PREFIX;
	char *command;
	u32 magic;
	int i;

	if (!mode)
		return 0;

	command = calloc(1, strlen(mode) + sizeof(prefix));
	if (!command)
		return -ENOMEM;

	strcat(command, prefix);
	strcat(command, mode);

	magic = dev_read_u32_default(dev, command, BOOT_NORMAL);
	if (magic == BOOT_NORMAL) {
		for (i = 0; i < ARRAY_SIZE(static_defined_command); i++) {
			if (!strcmp(static_defined_command[i].name, mode)) {
				magic = static_defined_command[i].magic;
				break;
			}
		}
	}

	printf("## Reboot mode: %s(%x)\n\n", mode, magic);

	writel(magic, CONFIG_ROCKCHIP_BOOT_MODE_REG);
	free(command);

	return 0;
}

static const struct sysreset_ops syscon_reboot_ops = {
	.request_by_mode = syscon_reboot_request_by_mode,
};

static const struct udevice_id syscon_reboot_match[] = {
	{ .compatible = "syscon-reboot-mode", },
	{},
};

U_BOOT_DRIVER(sysreset_syscon_reboot) = {
	.name = "sysreset_syscon_reboot",
	.id = UCLASS_SYSRESET,
	.of_match = syscon_reboot_match,
	.ops = &syscon_reboot_ops,
};
