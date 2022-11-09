/*
 * (C) Copyright 2018 Rockchip Electronics Co., Ltd
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */

#include <common.h>
#include <boot_rkimg.h>
#include <debug_uart.h>
#include <dm.h>
#include <key.h>
#include <led.h>
#include <misc.h>
#include <ram.h>
#include <spl.h>
#include <optee_include/OpteeClientInterface.h>
#include <power/fuel_gauge.h>
#include <asm/arch-rockchip/bootrom.h>
#ifdef CONFIG_ROCKCHIP_PRELOADER_ATAGS
#include <asm/arch-rockchip/rk_atags.h>
#endif
#include <asm/arch-rockchip/sdram.h>
#include <asm/arch-rockchip/boot_mode.h>
#include <asm/arch-rockchip/sys_proto.h>
#include <asm/io.h>

DECLARE_GLOBAL_DATA_PTR;

void board_return_to_bootrom(void)
{
	back_to_bootrom(BROM_BOOT_NEXTSTAGE);
}

__weak const char * const boot_devices[BROM_LAST_BOOTSOURCE + 1] = {
};

const char *board_spl_was_booted_from(void)
{
	u32  bootdevice_brom_id = readl(BROM_BOOTSOURCE_ID_ADDR);
	const char *bootdevice_ofpath = NULL;

	if (bootdevice_brom_id < ARRAY_SIZE(boot_devices))
		bootdevice_ofpath = boot_devices[bootdevice_brom_id];

	if (bootdevice_ofpath)
		debug("%s: brom_bootdevice_id %x maps to '%s'\n",
		      __func__, bootdevice_brom_id, bootdevice_ofpath);
	else
		debug("%s: failed to resolve brom_bootdevice_id %x\n",
		      __func__, bootdevice_brom_id);

	return bootdevice_ofpath;
}

u32 spl_boot_device(void)
{
	u32 boot_device = BOOT_DEVICE_MMC1;

#if defined(CONFIG_TARGET_CHROMEBOOK_JERRY) || \
		defined(CONFIG_TARGET_CHROMEBIT_MICKEY) || \
		defined(CONFIG_TARGET_CHROMEBOOK_MINNIE)
	return BOOT_DEVICE_SPI;
#endif
	if (CONFIG_IS_ENABLED(ROCKCHIP_BACK_TO_BROM))
		return BOOT_DEVICE_BOOTROM;

	return boot_device;
}

u32 spl_boot_mode(const u32 boot_device)
{
	return MMCSD_MODE_RAW;
}

__weak void rockchip_stimer_init(void)
{
	/* If Timer already enabled, don't re-init it */
	u32 reg = readl(CONFIG_ROCKCHIP_STIMER_BASE + 0x10);
	if ( reg & 0x1 )
		return;
#ifndef CONFIG_ARM64
	asm volatile("mcr p15, 0, %0, c14, c0, 0"
		     : : "r"(COUNTER_FREQUENCY));
#endif
	writel(0, CONFIG_ROCKCHIP_STIMER_BASE + 0x10);
	writel(0xffffffff, CONFIG_ROCKCHIP_STIMER_BASE);
	writel(0xffffffff, CONFIG_ROCKCHIP_STIMER_BASE + 4);
	writel(1, CONFIG_ROCKCHIP_STIMER_BASE + 0x10);
}

__weak int arch_cpu_init(void)
{
	return 0;
}

__weak int rk_board_init_f(void)
{
	return 0;
}

#ifndef CONFIG_SPL_LIBGENERIC_SUPPORT
void udelay(unsigned long usec)
{
	__udelay(usec);
}

void hang(void)
{
	bootstage_error(BOOTSTAGE_ID_NEED_RESET);
	for (;;)
		;
}

/**
 * memset - Fill a region of memory with the given value
 * @s: Pointer to the start of the area.
 * @c: The byte to fill the area with
 * @count: The size of the area.
 *
 * Do not use memset() to access IO space, use memset_io() instead.
 */
void *memset(void *s, int c, size_t count)
{
	unsigned long *sl = (unsigned long *)s;
	char *s8;

#if !CONFIG_IS_ENABLED(TINY_MEMSET)
	unsigned long cl = 0;
	int i;

	/* do it one word at a time (32 bits or 64 bits) while possible */
	if (((ulong)s & (sizeof(*sl) - 1)) == 0) {
		for (i = 0; i < sizeof(*sl); i++) {
			cl <<= 8;
			cl |= c & 0xff;
		}
		while (count >= sizeof(*sl)) {
			*sl++ = cl;
			count -= sizeof(*sl);
		}
	}
#endif /* fill 8 bits at a time */
	s8 = (char *)sl;
	while (count--)
		*s8++ = c;

	return s;
}
#endif

void board_init_f(ulong dummy)
{
#ifdef CONFIG_SPL_FRAMEWORK
	int ret;
#if !defined(CONFIG_SUPPORT_TPL)
	struct udevice *dev;
#endif
#endif
	gd->flags = dummy;
	rockchip_stimer_init();
#define EARLY_UART
#if defined(EARLY_UART) && defined(CONFIG_DEBUG_UART)
	/*
	 * Debug UART can be used from here if required:
	 *
	 * debug_uart_init();
	 * printch('a');
	 * printhex8(0x1234);
	 * printascii("string");
	 */
	if (!gd->serial.using_pre_serial &&
	    !(gd->flags & GD_FLG_DISABLE_CONSOLE))
		debug_uart_init();
	printascii("U-Boot SPL board init");
#endif
	gd->sys_start_tick = get_ticks();
#ifdef CONFIG_SPL_FRAMEWORK
	ret = spl_early_init();
	if (ret) {
		printf("spl_early_init() failed: %d\n", ret);
		hang();
	}
#if !defined(CONFIG_SUPPORT_TPL)
	debug("\nspl:init dram\n");
	ret = uclass_get_device(UCLASS_RAM, 0, &dev);
	if (ret) {
		printf("DRAM init failed: %d\n", ret);
		return;
	}
#endif
	preloader_console_init();
#else
	/* Some SoCs like rk3036 does not use any frame work */
	sdram_init();
#endif

	arch_cpu_init();
	rk_board_init_f();
#if CONFIG_IS_ENABLED(ROCKCHIP_BACK_TO_BROM) && !defined(CONFIG_SPL_BOARD_INIT)
	back_to_bootrom(BROM_BOOT_NEXTSTAGE);
#endif

}

#ifdef CONFIG_SPL_LOAD_FIT
int board_fit_config_name_match(const char *name)
{
	/* Just empty function now - can't decide what to choose */
	debug("%s: %s\n", __func__, name);

	return 0;
}
#endif

int board_init_f_boot_flags(void)
{
	int boot_flags = 0;

	/* pre-loader serial */
#if defined(CONFIG_ROCKCHIP_PRELOADER_SERIAL) && \
    defined(CONFIG_ROCKCHIP_PRELOADER_ATAGS)
	struct tag *t;


	t = atags_get_tag(ATAG_SERIAL);
	if (t) {
		gd->serial.using_pre_serial = 1;
		gd->serial.enable = t->u.serial.enable;
		gd->serial.baudrate = t->u.serial.baudrate;
		gd->serial.addr = t->u.serial.addr;
		gd->serial.id = t->u.serial.id;
		gd->baudrate = t->u.serial.baudrate;
		if (!t->u.serial.enable)
			boot_flags |= GD_FLG_DISABLE_CONSOLE;
		debug("preloader: enable=%d, addr=0x%x, baudrate=%d, id=%d\n",
		      t->u.serial.enable, (u32)t->u.serial.addr,
		      t->u.serial.baudrate, t->u.serial.id);
	} else
#endif
	{
		gd->baudrate = CONFIG_BAUDRATE;
		gd->serial.baudrate = CONFIG_BAUDRATE;
		gd->serial.addr = CONFIG_DEBUG_UART_BASE;
	}

	/* The highest priority to turn off (override) console */
#if defined(CONFIG_DISABLE_CONSOLE)
	boot_flags |= GD_FLG_DISABLE_CONSOLE;
#endif

	return boot_flags;
}

#ifdef CONFIG_SPL_BOARD_INIT
__weak int rk_spl_board_init(void)
{
	return 0;
}

static int setup_led(void)
{
#ifdef CONFIG_SPL_LED
	struct udevice *dev;
	char *led_name;
	int ret;

	led_name = fdtdec_get_config_string(gd->fdt_blob, "u-boot,boot-led");
	if (!led_name)
		return 0;
	ret = led_get_by_label(led_name, &dev);
	if (ret) {
		debug("%s: get=%d\n", __func__, ret);
		return ret;
	}
	ret = led_set_state(dev, LEDST_ON);
	if (ret)
		return ret;
#endif

	return 0;
}

void spl_board_init(void)
{
	int ret;

	ret = setup_led();

	if (ret) {
		debug("LED ret=%d\n", ret);
		hang();
	}

	rk_spl_board_init();
#if CONFIG_IS_ENABLED(ROCKCHIP_BACK_TO_BROM)
	back_to_bootrom(BROM_BOOT_NEXTSTAGE);
#endif
	return;
}
#endif

void spl_perform_fixups(struct spl_image_info *spl_image)
{
#ifdef CONFIG_ROCKCHIP_PRELOADER_ATAGS
	atags_set_bootdev_by_spl_bootdevice(spl_image->boot_device);
#endif
	return;
}

#ifdef CONFIG_SPL_KERNEL_BOOT
static int spl_rockchip_dnl_key_pressed(void)
{
#if defined(CONFIG_SPL_INPUT)
	return key_read(KEY_VOLUMEUP);
#else
	return 0;
#endif
}

#ifdef CONFIG_SPL_DM_FUEL_GAUGE
bool spl_is_low_power(void)
{
	struct udevice *dev;
	int ret, voltage;

	ret = uclass_get_device(UCLASS_FG, 0, &dev);
	if (ret) {
		debug("Get charge display failed, ret=%d\n", ret);
		return false;
	}

	voltage = fuel_gauge_get_voltage(dev);
	if (voltage >= CONFIG_SPL_POWER_LOW_VOLTAGE_THRESHOLD)
		return false;

	return true;
}
#endif

void spl_next_stage(struct spl_image_info *spl)
{
	uint32_t reg_boot_mode;

	if (spl_rockchip_dnl_key_pressed()) {
		spl->next_stage = SPL_NEXT_STAGE_UBOOT;
		return;
	}
#ifdef CONFIG_SPL_DM_FUEL_GAUGE
	if (spl_is_low_power()) {
		spl->next_stage = SPL_NEXT_STAGE_UBOOT;
		return;
	}
#endif

	reg_boot_mode = readl((void *)CONFIG_ROCKCHIP_BOOT_MODE_REG);
	switch (reg_boot_mode) {
	case BOOT_COLD:
	case BOOT_PANIC:
	case BOOT_WATCHDOG:
	case BOOT_NORMAL:
	case BOOT_RECOVERY:
		spl->next_stage = SPL_NEXT_STAGE_KERNEL;
		break;
	default:
		spl->next_stage = SPL_NEXT_STAGE_UBOOT;
	}
}
#endif

#ifdef CONFIG_SPL_KERNEL_BOOT
const char *spl_kernel_partition(struct spl_image_info *spl,
				 struct spl_load_info *info)
{
	struct bootloader_message *bmsg = NULL;
	u32 boot_mode;
	int ret, cnt;
	u32 sector = 0;

#ifdef CONFIG_SPL_LIBDISK_SUPPORT
	disk_partition_t part_info;

	ret = part_get_info_by_name(info->dev, PART_MISC, &part_info);
	if (ret >= 0)
		sector = part_info.start;
#else
	sector = CONFIG_SPL_MISC_SECTOR;
#endif
	if (sector) {
		cnt = DIV_ROUND_UP(sizeof(*bmsg), info->bl_len);
		bmsg = memalign(ARCH_DMA_MINALIGN, cnt * info->bl_len);
		ret = info->read(info, sector + BCB_MESSAGE_BLK_OFFSET,
				 cnt, bmsg);
		if (ret == cnt && !strcmp(bmsg->command, "boot-recovery")) {
			free(bmsg);
			return PART_RECOVERY;
		} else {
			free(bmsg);
		}
	}

	boot_mode = readl((void *)CONFIG_ROCKCHIP_BOOT_MODE_REG);

	return (boot_mode == BOOT_RECOVERY) ? PART_RECOVERY : PART_BOOT;
}
#endif

void spl_hang_reset(void)
{
	printf("# Reset the board to bootrom #\n");
#if defined(CONFIG_SPL_SYSRESET) && defined(CONFIG_SPL_DRIVERS_MISC_SUPPORT)
	/* reset is available after dm setup */
	if (gd->flags & GD_FLG_SPL_EARLY_INIT) {
		writel(BOOT_BROM_DOWNLOAD, CONFIG_ROCKCHIP_BOOT_MODE_REG);
		do_reset(NULL, 0, 0, NULL);
	}
#endif
}

#ifdef CONFIG_SPL_FIT_ROLLBACK_PROTECT
int fit_read_otp_rollback_index(uint32_t fit_index, uint32_t *otp_index)
{
	int ret = 0;

	*otp_index = 0;
#if defined(CONFIG_SPL_ROCKCHIP_SECURE_OTP)
	struct udevice *dev;
	u32 index, i, otp_version;
	u32 bit_count;

	dev = misc_otp_get_device(OTP_S);
	if (!dev)
		return -ENODEV;

	otp_version = 0;
	for (i = 0; i < OTP_UBOOT_ROLLBACK_WORDS; i++) {
		if (misc_otp_read(dev, OTP_UBOOT_ROLLBACK_OFFSET + i * 4,
		    &index,
		    4)) {
			printf("Can't read rollback index\n");
			return -EIO;
		}

		bit_count = fls(index);
		otp_version += bit_count;
	}
	*otp_index = otp_version;
#endif

	return ret;
}

static int fit_write_otp_rollback_index(u32 fit_index)
{
#if defined(CONFIG_SPL_ROCKCHIP_SECURE_OTP)
	struct udevice *dev;
	u32 index, i, otp_index;

	if (!fit_index)
		return 0;

	if (fit_index > OTP_UBOOT_ROLLBACK_WORDS * 32)
		return -EINVAL;

	dev = misc_otp_get_device(OTP_S);
	if (!dev)
		return -ENODEV;

	if (fit_read_otp_rollback_index(fit_index, &otp_index))
		return -EIO;

	if (otp_index < fit_index) {
		/* Write new SW version to otp */
		for (i = 0; i < OTP_UBOOT_ROLLBACK_WORDS; i++) {
			/*
			 * If fit_index is equal to 0, then execute 0xffffffff >> 32.
			 * But the operand can only be 0 - 31. The "0xffffffff >> 32" is
			 * actually be "0xffffffff >> 0".
			 */
			if (!fit_index)
				break;
			/* convert to base-1 representation */
			index = 0xffffffff >> (OTP_ALL_ONES_NUM_BITS -
				min(fit_index, (u32)OTP_ALL_ONES_NUM_BITS));
			fit_index -= min(fit_index,
					  (u32)OTP_ALL_ONES_NUM_BITS);
			if (index) {
				if (misc_otp_write(dev, OTP_UBOOT_ROLLBACK_OFFSET + i * 4,
				    &index,
				    4)) {
					printf("Can't write rollback index\n");
					return -EIO;
				}
			}
		}
	}
#endif

	return 0;
}
#endif

int spl_board_prepare_for_jump(struct spl_image_info *spl_image)
{
#ifdef CONFIG_SPL_FIT_ROLLBACK_PROTECT
	int ret;

	ret = fit_write_otp_rollback_index(gd->rollback_index);
	if (ret) {
		panic("Failed to write fit rollback index %d, ret=%d",
		      gd->rollback_index, ret);
	}
#endif

#ifdef CONFIG_SPL_ROCKCHIP_HW_DECOMPRESS
	misc_decompress_cleanup();
#endif
	return 0;
}
