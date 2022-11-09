// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (c) 2019 Fuzhou Rockchip Electronics Co., Ltd
 */

#include <common.h>
#include <command.h>
#include <dm.h>
#include <misc.h>

#ifdef CONFIG_ROCKCHIP_OTP
static int dump_otps(cmd_tbl_t *cmdtp, int flag,
		     int argc, char * const argv[])
{
	struct udevice *dev;
	u8 otps[64] = {0};
	int ret;

	/* retrieve the device */
	ret = uclass_get_device_by_driver(UCLASS_MISC,
					  DM_GET_DRIVER(rockchip_otp), &dev);
	if (ret) {
		printf("%s: no misc-device found\n", __func__);
		return 0;
	}

	ret = misc_read(dev, 0, &otps, sizeof(otps));
	if (ret) {
		printf("%s: misc_read failed\n", __func__);
		return 0;
	}

	printf("otp-contents:\n");
	print_buffer(0, otps, 1, 64, 16);

	return 0;
}

U_BOOT_CMD(
	rockchip_dump_otps, 1, 1, dump_otps,
	"Dump the content of the otps",
	""
);
#endif

#ifdef CONFIG_ROCKCHIP_EFUSE
static int dump_efuses(cmd_tbl_t *cmdtp, int flag,
		       int argc, char * const argv[])
{
	/*
	 * N.B.: This function is tailored towards the RK3399 and assumes that
	 *       there's always 32 fuses x 32 bits (i.e. 128 bytes of data) to
	 *       be read.
	 */

	struct udevice *dev;
	u8 fuses[128] = {0};
	int ret;

	/* retrieve the device */
	ret = uclass_get_device_by_driver(UCLASS_MISC,
					  DM_GET_DRIVER(rockchip_efuse), &dev);
	if (ret) {
		printf("%s: no misc-device found\n", __func__);
		return 0;
	}

	ret = misc_read(dev, 0, &fuses, sizeof(fuses));
	if (ret) {
		printf("%s: misc_read failed\n", __func__);
		return 0;
	}

	printf("efuse-contents:\n");
	print_buffer(0, fuses, 1, 128, 16);

	return 0;
}

U_BOOT_CMD(
	rockchip_dump_efuses, 1, 1, dump_efuses,
	"Dump the content of the efuses",
	""
);
#endif
