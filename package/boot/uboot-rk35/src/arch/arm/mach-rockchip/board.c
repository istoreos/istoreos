/*
 * (C) Copyright 2017 Rockchip Electronics Co., Ltd.
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */

#include <common.h>
#include <amp.h>
#include <android_ab.h>
#include <android_bootloader.h>
#include <android_image.h>
#include <bidram.h>
#include <boot_rkimg.h>
#include <cli.h>
#include <clk.h>
#include <console.h>
#include <debug_uart.h>
#include <dm.h>
#include <dvfs.h>
#include <fdt_support.h>
#include <io-domain.h>
#include <image.h>
#include <key.h>
#include <memblk.h>
#include <misc.h>
#include <of_live.h>
#include <mtd_blk.h>
#include <ram.h>
#include <rockchip_debugger.h>
#include <syscon.h>
#include <sysmem.h>
#include <video_rockchip.h>
#include <xbc.h>
#include <asm/io.h>
#include <asm/gpio.h>
#include <android_avb/rk_avb_ops_user.h>
#include <dm/uclass-internal.h>
#include <dm/root.h>
#include <power/charge_display.h>
#include <power/regulator.h>
#include <optee_include/OpteeClientInterface.h>
#include <optee_include/OpteeClientApiLib.h>
#include <optee_include/tee_api_defines.h>
#include <asm/arch-rockchip/boot_mode.h>
#include <asm/arch-rockchip/clock.h>
#include <asm/arch-rockchip/cpu.h>
#include <asm/arch-rockchip/hotkey.h>
#include <asm/arch-rockchip/param.h>
#include <asm/arch-rockchip/periph.h>
#include <asm/arch-rockchip/resource_img.h>
#include <asm/arch-rockchip/rk_atags.h>
#include <asm/arch-rockchip/vendor.h>
#ifdef CONFIG_ROCKCHIP_EINK_DISPLAY
#include <rk_eink.h>
#endif

DECLARE_GLOBAL_DATA_PTR;

__weak int rk_board_late_init(void)
{
	return 0;
}

__weak int rk_board_fdt_fixup(void *blob)
{
	return 0;
}

__weak int soc_clk_dump(void)
{
	return 0;
}

__weak int set_armclk_rate(void)
{
	return 0;
}

__weak int rk_board_init(void)
{
	return 0;
}

#ifdef CONFIG_ROCKCHIP_SET_ETHADDR
/*
 * define serialno max length, the max length is 512 Bytes
 * The remaining bytes are used to ensure that the first 512 bytes
 * are valid when executing 'env_set("serial#", value)'.
 */
#define VENDOR_SN_MAX	513
#define CPUID_LEN	0x10
#define CPUID_OFF	0x07

#define MAX_ETHERNET	0x2

static int rockchip_set_ethaddr(void)
{
	__maybe_unused bool need_write = false;
	bool randomed = false;
	char buf[ARP_HLEN_ASCII + 1], mac[16];
	u8 ethaddr[ARP_HLEN * MAX_ETHERNET] = {0};
	int i, ret = -EINVAL;

#ifdef CONFIG_ROCKCHIP_VENDOR_PARTITION
	ret = vendor_storage_read(LAN_MAC_ID, ethaddr, sizeof(ethaddr));
#endif
	for (i = 0; i < MAX_ETHERNET; i++) {
		if (ret <= 0 || !is_valid_ethaddr(&ethaddr[i * ARP_HLEN])) {
			if (!randomed) {
				net_random_ethaddr(&ethaddr[i * ARP_HLEN]);
				randomed = true;
			} else {
				if (i > 0) {
					memcpy(&ethaddr[i * ARP_HLEN],
					       &ethaddr[(i - 1) * ARP_HLEN],
					       ARP_HLEN);
					ethaddr[i * ARP_HLEN] |= 0x02;
					ethaddr[i * ARP_HLEN] += (i << 2);
				}
			}

			need_write = true;
		}

		if (is_valid_ethaddr(&ethaddr[i * ARP_HLEN])) {
			sprintf(buf, "%pM", &ethaddr[i * ARP_HLEN]);
			if (i == 0)
				memcpy(mac, "ethaddr", sizeof("ethaddr"));
			else
				sprintf(mac, "eth%daddr", i);
			env_set(mac, buf);
		}
	}

#ifdef CONFIG_ROCKCHIP_VENDOR_PARTITION
	if (need_write) {
		ret = vendor_storage_write(LAN_MAC_ID,
					   ethaddr, sizeof(ethaddr));
		if (ret < 0)
			printf("%s: vendor_storage_write failed %d\n",
			       __func__, ret);
	}
#endif
	return 0;
}
#endif

#ifdef CONFIG_ROCKCHIP_SET_SN
static int rockchip_set_serialno(void)
{
	u8 low[CPUID_LEN / 2], high[CPUID_LEN / 2];
	u8 cpuid[CPUID_LEN] = {0};
	char serialno_str[VENDOR_SN_MAX];
	int ret = 0, i;
	u64 serialno;

	/* Read serial number from vendor storage part */
	memset(serialno_str, 0, VENDOR_SN_MAX);

#ifdef CONFIG_ROCKCHIP_VENDOR_PARTITION
	ret = vendor_storage_read(SN_ID, serialno_str, (VENDOR_SN_MAX-1));
	if (ret > 0) {
		i = strlen(serialno_str);
		for (; i > 0; i--) {
			if ((serialno_str[i] >= 'a' && serialno_str[i] <= 'z') ||
			    (serialno_str[i] >= 'A' && serialno_str[i] <= 'Z') ||
			    (serialno_str[i] >= '0' && serialno_str[i] <= '9'))
				break;
		}

		serialno_str[i + 1] = 0x0;
		env_set("serial#", serialno_str);
	} else {
#endif
#if defined(CONFIG_ROCKCHIP_EFUSE) || defined(CONFIG_ROCKCHIP_OTP)
		struct udevice *dev;

		/* retrieve the device */
		if (IS_ENABLED(CONFIG_ROCKCHIP_EFUSE))
			ret = uclass_get_device_by_driver(UCLASS_MISC,
							  DM_GET_DRIVER(rockchip_efuse),
							  &dev);
		else
			ret = uclass_get_device_by_driver(UCLASS_MISC,
							  DM_GET_DRIVER(rockchip_otp),
							  &dev);

		if (ret) {
			printf("%s: could not find efuse/otp device\n", __func__);
			return ret;
		}

		/* read the cpu_id range from the efuses */
		ret = misc_read(dev, CPUID_OFF, &cpuid, sizeof(cpuid));
		if (ret) {
			printf("%s: read cpuid from efuse/otp failed, ret=%d\n",
			       __func__, ret);
			return ret;
		}
#else
		/* generate random cpuid */
		for (i = 0; i < CPUID_LEN; i++)
			cpuid[i] = (u8)(rand());
#endif
		/* Generate the serial number based on CPU ID */
		for (i = 0; i < 8; i++) {
			low[i] = cpuid[1 + (i << 1)];
			high[i] = cpuid[i << 1];
		}

		serialno = crc32_no_comp(0, low, 8);
		serialno |= (u64)crc32_no_comp(serialno, high, 8) << 32;
		snprintf(serialno_str, sizeof(serialno_str), "%llx", serialno);

		env_set("serial#", serialno_str);
#ifdef CONFIG_ROCKCHIP_VENDOR_PARTITION
	}
#endif

	return ret;
}
#endif


#if defined(CONFIG_USB_FUNCTION_FASTBOOT)
int fb_set_reboot_flag(void)
{
	printf("Setting reboot to fastboot flag ...\n");
	writel(BOOT_FASTBOOT, CONFIG_ROCKCHIP_BOOT_MODE_REG);

	return 0;
}
#endif

#ifdef CONFIG_ROCKCHIP_USB_BOOT
static int boot_from_udisk(void)
{
	struct blk_desc *desc;

	if (!run_command("usb start", -1)) {
		desc = blk_get_devnum_by_type(IF_TYPE_USB, 0);
		if (!desc) {
			printf("No usb device found\n");
			return -ENODEV;
		} else {
			rockchip_set_bootdev(desc);
			env_set("devtype", "usb");
			env_set("devnum", "0");
			printf("Boot from usb 0\n");
		}
	}

	return 0;
}
#endif

static void env_fixup(void)
{
	struct memblock mem;
	ulong u_addr_r;
	phys_size_t end;
	char *addr_r;

#ifdef ENV_MEM_LAYOUT_SETTINGS1
	const char *env_addr0[] = {
		"scriptaddr", "pxefile_addr_r",
		"fdt_addr_r", "kernel_addr_r", "ramdisk_addr_r",
	};
	const char *env_addr1[] = {
		"scriptaddr1", "pxefile_addr1_r",
		"fdt_addr1_r", "kernel_addr1_r", "ramdisk_addr1_r",
	};
	int i;

	/* 128M is a typical ram size for most platform, so as default here */
	if (gd->ram_size <= SZ_128M) {
		/* Replace orignal xxx_addr_r */
		for (i = 0; i < ARRAY_SIZE(env_addr1); i++) {
			addr_r = env_get(env_addr1[i]);
			if (addr_r)
				env_set(env_addr0[i], addr_r);
		}
	}
#endif
	/* No BL32 ? */
	if (!(gd->flags & GD_FLG_BL32_ENABLED)) {
		/*
		 * [1] Move kernel to lower address if possible.
		 */
		addr_r = env_get("kernel_addr_no_low_bl32_r");
		if (addr_r)
			env_set("kernel_addr_r", addr_r);

		/*
		 * [2] Move ramdisk at BL32 position if need.
		 *
		 * 0x0a200000 and 0x08400000 are rockchip traditional address
		 * of BL32 and ramdisk:
		 *
		 * |------------|------------|
		 * |    BL32    |  ramdisk   |
		 * |------------|------------|
		 *
		 * Move ramdisk to BL32 address to fix sysmem alloc failed
		 * issue on the board with critical memory(ie. 256MB).
		 */
		if (gd->ram_size > SZ_128M && gd->ram_size <= SZ_256M) {
			u_addr_r = env_get_ulong("ramdisk_addr_r", 16, 0);
			if (u_addr_r == 0x0a200000)
				env_set("ramdisk_addr_r", "0x08400000");
		}
	} else {
		mem = param_parse_optee_mem();

		/*
		 * [1] Move kernel forward if possible.
		 */
		if (mem.base > SZ_128M) {
			addr_r = env_get("kernel_addr_no_low_bl32_r");
			if (addr_r)
				env_set("kernel_addr_r", addr_r);
		}

		/*
		 * [2] Move ramdisk backward if optee enlarge.
		 */
		end = mem.base + mem.size;
		u_addr_r = env_get_ulong("ramdisk_addr_r", 16, 0);
		if (u_addr_r >= mem.base && u_addr_r < end)
			env_set_hex("ramdisk_addr_r", end);
	}
}

static void cmdline_handle(void)
{
	struct blk_desc *dev_desc;

	param_parse_pubkey_fuse_programmed();

	dev_desc = rockchip_get_bootdev();
	if (!dev_desc)
		return;
#ifdef CONFIG_CMD_BOOT_ANDROID
	/*
	 * From rk356x, the sd/udisk update flag was moved from
	 * IDB to Android BCB.
	 */
	if (get_bcb_recovery_msg() == BCB_MSG_RECOVERY_RK_FWUPDATE) {
		if (dev_desc->if_type == IF_TYPE_MMC && dev_desc->devnum == 1)
			env_update("bootargs", "sdfwupdate");
		else if (dev_desc->if_type == IF_TYPE_USB && dev_desc->devnum == 0)
			env_update("bootargs", "usbfwupdate");
	}
#endif
}

int board_late_init(void)
{
#ifdef CONFIG_ROCKCHIP_SET_ETHADDR
	rockchip_set_ethaddr();
#endif
#ifdef CONFIG_ROCKCHIP_SET_SN
	rockchip_set_serialno();
#endif
	setup_download_mode();
#ifdef CONFIG_ROCKCHIP_USB_BOOT
	boot_from_udisk();
#endif
#if (CONFIG_ROCKCHIP_BOOT_MODE_REG > 0)
	setup_boot_mode();
#endif
#ifdef CONFIG_DM_CHARGE_DISPLAY
	charge_display();
#endif
#ifdef CONFIG_DRM_ROCKCHIP
	rockchip_show_logo();
#endif
#ifdef CONFIG_ROCKCHIP_EINK_DISPLAY
	rockchip_eink_show_uboot_logo();
#endif
	env_fixup();
	soc_clk_dump();
	cmdline_handle();
#ifdef CONFIG_AMP
	amp_cpus_on();
#endif
	return rk_board_late_init();
}

static void early_download(void)
{
#if defined(CONFIG_PWRKEY_DNL_TRIGGER_NUM) && \
		(CONFIG_PWRKEY_DNL_TRIGGER_NUM > 0)
	if (pwrkey_download_init())
		printf("Pwrkey download init failed\n");
#endif

#if (CONFIG_ROCKCHIP_BOOT_MODE_REG > 0)
	if (is_hotkey(HK_BROM_DNL)) {
		printf("Enter bootrom download...");
		flushc();
		writel(BOOT_BROM_DOWNLOAD, CONFIG_ROCKCHIP_BOOT_MODE_REG);
		do_reset(NULL, 0, 0, NULL);
		printf("failed!\n");
	}
#endif
}

static void board_debug_init(void)
{
	if (!gd->serial.using_pre_serial &&
	    !(gd->flags & GD_FLG_DISABLE_CONSOLE))
		debug_uart_init();

	if (tstc()) {
		gd->console_evt = getc();
		if (gd->console_evt <= 0x1a) /* 'z' */
			printf("Hotkey: ctrl+%c\n", gd->console_evt + 'a' - 1);
	}

	if (IS_ENABLED(CONFIG_CONSOLE_DISABLE_CLI))
		printf("Cmd interface: disabled\n");
}

#if defined(CONFIG_MTD_BLK) && defined(CONFIG_USING_KERNEL_DTB)
static void board_mtd_blk_map_partitions(void)
{
	struct blk_desc *dev_desc;

	dev_desc = rockchip_get_bootdev();
	if (dev_desc)
		mtd_blk_map_partitions(dev_desc);
}
#endif

int board_init(void)
{
	board_debug_init();
	/* optee select security level */
#ifdef CONFIG_OPTEE_CLIENT
	trusty_select_security_level();
#endif

#ifdef DEBUG
	soc_clk_dump();
#endif

#ifdef CONFIG_USING_KERNEL_DTB
#ifdef CONFIG_MTD_BLK
	board_mtd_blk_map_partitions();
#endif
	init_kernel_dtb();
#endif
	early_download();

	/*
	 * pmucru isn't referenced on some platforms, so pmucru driver can't
	 * probe that the "assigned-clocks" is unused.
	 */
	clks_probe();
#ifdef CONFIG_DM_REGULATOR
	if (regulators_enable_boot_on(is_hotkey(HK_REGULATOR)))
		debug("%s: Can't enable boot on regulator\n", __func__);
#endif

#ifdef CONFIG_ROCKCHIP_IO_DOMAIN
	io_domain_init();
#endif

	set_armclk_rate();

#ifdef CONFIG_DM_DVFS
	dvfs_init(true);
#endif

#ifdef CONFIG_ANDROID_AB
	if (ab_decrease_tries())
		printf("Decrease ab tries count fail!\n");
#endif

	return rk_board_init();
}

int interrupt_debugger_init(void)
{
#ifdef CONFIG_ROCKCHIP_DEBUGGER
	return rockchip_debugger_init();
#else
	return 0;
#endif
}

int board_fdt_fixup(void *blob)
{
	/* Common fixup for DRM */
#ifdef CONFIG_DRM_ROCKCHIP
	rockchip_display_fixup(blob);
#endif

	return rk_board_fdt_fixup(blob);
}

#if defined(CONFIG_ARM64_BOOT_AARCH32) || !defined(CONFIG_ARM64)
/*
 * Common for OP-TEE:
 *	64-bit & 32-bit mode: share memory dcache is always enabled;
 *
 * Common for U-Boot:
 *	64-bit mode: MMU table is static defined in rkxxx.c file, all memory
 *		     regions are mapped. That's good to match OP-TEE MMU policy.
 *
 *	32-bit mode: MMU table is setup according to gd->bd->bi_dram[..] where
 *		     the OP-TEE region has been reserved, so it can not be
 *		     mapped(i.e. dcache is disabled). That's *NOT* good to match
 *		     OP-TEE MMU policy.
 *
 * For the data coherence when communication between U-Boot and OP-TEE, U-Boot
 * should follow OP-TEE MMU policy.
 *
 * So 32-bit mode U-Boot should map OP-TEE share memory as dcache enabled.
 */
int board_initr_caches_fixup(void)
{
#ifdef CONFIG_OPTEE_CLIENT
	struct memblock mem;

	mem.base = 0;
	mem.size = 0;

	optee_get_shm_config(&mem.base, &mem.size);
	if (mem.size)
		mmu_set_region_dcache_behaviour(mem.base, mem.size,
						DCACHE_WRITEBACK);
#endif
	return 0;
}
#endif

void arch_preboot_os(uint32_t bootm_state, bootm_headers_t *images)
{
	if (!(bootm_state & BOOTM_STATE_OS_PREP))
		return;

#ifdef CONFIG_ARM64
	u8 *data = (void *)images->ep;

	/*
	 * Fix kernel 5.10 arm64 boot warning:
	 * "[Firmware Bug]: Kernel image misaligned at boot, please fix your bootloader!"
	 *
	 * kernel: 5.10 commit 120dc60d0bdb ("arm64: get rid of TEXT_OFFSET")
	 * arm64 kernel version:
	 *	data[10] == 0x00 if kernel version >= 5.10
	 *	data[10] == 0x08 if kernel version <  5.10
	 *
	 * Why fix here?
	 *   1. this is the common and final path for any boot command.
	 *   2. don't influence original boot flow, just fix it exactly before
	 *	jumping kernel.
	 *
	 * But relocation is in board_quiesce_devices() until all decompress
	 * done, mainly for saving boot time.
	 */
	if (data[10] == 0x00) {
		if (round_down(images->ep, SZ_2M) != images->ep)
			images->ep = round_down(images->ep, SZ_2M);
	} else {
		if (IS_ALIGNED(images->ep, SZ_2M))
			images->ep += 0x80000;
	}
#endif
	hotkey_run(HK_CLI_OS_PRE);
}

void enable_caches(void)
{
	icache_enable();
	dcache_enable();
}

#ifdef CONFIG_LMB
/*
 * Using last bi_dram[...] to initialize "bootm_low" and "bootm_mapsize".
 * This makes lmb_alloc_base() always alloc from tail of sdram.
 * If we don't assign it, bi_dram[0] is used by default and it may cause
 * lmb_alloc_base() fail when bi_dram[0] range is small.
 */
void board_lmb_reserve(struct lmb *lmb)
{
	char bootm_mapsize[32];
	char bootm_low[32];
	u64 start, size;
	int i;

	for (i = 0; i < CONFIG_NR_DRAM_BANKS; i++) {
		if (!gd->bd->bi_dram[i].size)
			break;
	}

	start = gd->bd->bi_dram[i - 1].start;
	size = gd->bd->bi_dram[i - 1].size;

	/*
	 * 32-bit kernel: ramdisk/fdt shouldn't be loaded to highmem area(768MB+),
	 * otherwise "Unable to handle kernel paging request at virtual address ...".
	 *
	 * So that we hope limit highest address at 768M, but there comes the the
	 * problem: ramdisk is a compressed image and it expands after descompress,
	 * so it accesses 768MB+ and brings the above "Unable to handle kernel ...".
	 *
	 * We make a appointment that the highest memory address is 512MB, it
	 * makes lmb alloc safer.
	 */
#ifndef CONFIG_ARM64
	if (start >= ((u64)CONFIG_SYS_SDRAM_BASE + SZ_512M)) {
		start = gd->bd->bi_dram[i - 2].start;
		size = gd->bd->bi_dram[i - 2].size;
	}

	if ((start + size) > ((u64)CONFIG_SYS_SDRAM_BASE + SZ_512M))
		size = (u64)CONFIG_SYS_SDRAM_BASE + SZ_512M - start;
#endif
	sprintf(bootm_low, "0x%llx", start);
	sprintf(bootm_mapsize, "0x%llx", size);
	env_set("bootm_low", bootm_low);
	env_set("bootm_mapsize", bootm_mapsize);
}
#endif

#ifdef CONFIG_BIDRAM
int board_bidram_reserve(struct bidram *bidram)
{
	struct memblock mem;
	int ret;

	/* ATF */
	mem = param_parse_atf_mem();
	ret = bidram_reserve(MEM_ATF, mem.base, mem.size);
	if (ret)
		return ret;

	/* PSTORE/ATAGS/SHM */
	mem = param_parse_common_resv_mem();
	ret = bidram_reserve(MEM_SHM, mem.base, mem.size);
	if (ret)
		return ret;

	/* OP-TEE */
	mem = param_parse_optee_mem();
	ret = bidram_reserve(MEM_OPTEE, mem.base, mem.size);
	if (ret)
		return ret;

	return 0;
}

#ifdef CONFIG_SYSMEM
int board_sysmem_reserve(struct sysmem *sysmem)
{
#ifdef CONFIG_SKIP_RELOCATE_UBOOT
	if (!sysmem_alloc_base_by_name("NO-RELOC-CODE",
	    CONFIG_SYS_TEXT_BASE, SZ_2M)) {
		printf("Failed to reserve sysmem for U-Boot code\n");
		return -ENOMEM;
	}
#endif
	return 0;
}
#endif

parse_fn_t board_bidram_parse_fn(void)
{
	return param_parse_ddr_mem;
}
#endif

int board_init_f_boot_flags(void)
{
	int boot_flags = 0;

	arch_fpga_init();

	param_parse_pre_serial();

	if (!gd->serial.enable)
		boot_flags |= GD_FLG_DISABLE_CONSOLE;

	/* The highest priority to turn off (override) console */
#if defined(CONFIG_DISABLE_CONSOLE)
	boot_flags |= GD_FLG_DISABLE_CONSOLE;
#endif

	return boot_flags;
}

#if defined(CONFIG_USB_GADGET) && defined(CONFIG_USB_GADGET_DWC2_OTG)
#include <fdt_support.h>
#include <usb.h>
#include <usb/dwc2_udc.h>

static struct dwc2_plat_otg_data otg_data = {
	.rx_fifo_sz	= 512,
	.np_tx_fifo_sz	= 16,
	.tx_fifo_sz	= 128,
};

int board_usb_init(int index, enum usb_init_type init)
{
	const void *blob = gd->fdt_blob;
	const fdt32_t *reg;
	fdt_addr_t addr;
	int node;

	/* find the usb_otg node */
	node = fdt_node_offset_by_compatible(blob, -1, "snps,dwc2");

retry:
	if (node > 0) {
		reg = fdt_getprop(blob, node, "reg", NULL);
		if (!reg)
			return -EINVAL;

		addr = fdt_translate_address(blob, node, reg);
		if (addr == OF_BAD_ADDR) {
			pr_err("Not found usb_otg address\n");
			return -EINVAL;
		}

#if defined(CONFIG_ROCKCHIP_RK3288)
		if (addr != 0xff580000) {
			node = fdt_node_offset_by_compatible(blob, node,
							     "snps,dwc2");
			goto retry;
		}
#endif
	} else {
		/*
		 * With kernel dtb support, rk3288 dwc2 otg node
		 * use the rockchip legacy dwc2 driver "dwc_otg_310"
		 * with the compatible "rockchip,rk3288_usb20_otg",
		 * and rk3368 also use the "dwc_otg_310" driver with
		 * the compatible "rockchip,rk3368-usb".
		 */
#if defined(CONFIG_ROCKCHIP_RK3288)
		node = fdt_node_offset_by_compatible(blob, -1,
				"rockchip,rk3288_usb20_otg");
#elif defined(CONFIG_ROCKCHIP_RK3368)
		node = fdt_node_offset_by_compatible(blob, -1,
				"rockchip,rk3368-usb");
#endif
		if (node > 0) {
			goto retry;
		} else {
			pr_err("Not found usb_otg device\n");
			return -ENODEV;
		}
	}

	otg_data.regs_otg = (uintptr_t)addr;

	return dwc2_udc_probe(&otg_data);
}

int board_usb_cleanup(int index, enum usb_init_type init)
{
	return 0;
}
#endif

static void bootm_no_reloc(void)
{
	char *ramdisk_high;
	char *fdt_high;

	if (!env_get_yesno("bootm-no-reloc"))
		return;

	ramdisk_high = env_get("initrd_high");
	fdt_high = env_get("fdt_high");

	if (!fdt_high) {
		env_set_hex("fdt_high", -1UL);
		printf("Fdt ");
	}

	if (!ramdisk_high) {
		env_set_hex("initrd_high", -1UL);
		printf("Ramdisk ");
	}

	if (!fdt_high || !ramdisk_high)
		printf("skip relocation\n");
}

int bootm_board_start(void)
{
	/*
	 * print console record data
	 *
	 * On some rockchip platforms, uart debug and sdmmc pin are multiplex.
	 * If boot from sdmmc mode, the console data would be record in buffer,
	 * we switch to uart debug function in order to print it after loading
	 * images.
	 */
#if defined(CONFIG_CONSOLE_RECORD)
	if (!strcmp("mmc", env_get("devtype")) &&
	    !strcmp("1", env_get("devnum"))) {
		printf("IOMUX: sdmmc => uart debug");
		pinctrl_select_state(gd->cur_serial_dev, "default");
		console_record_print_purge();
	}
#endif
	/* disable bootm relcation to save boot time */
	bootm_no_reloc();

#ifdef CONFIG_CMD_BOOT_ANDROID
	/* PCBA test needs more permission */
	if (get_bcb_recovery_msg() == BCB_MSG_RECOVERY_PCBA)
		env_update("bootargs", "androidboot.selinux=permissive");
#endif

	/* sysmem */
	hotkey_run(HK_SYSMEM);
	sysmem_overflow_check();

	return 0;
}

int bootm_image_populate_dtb(void *img)
{
	if ((gd->flags & GD_FLG_KDTB_READY) && !gd->fdt_blob_kern)
		sysmem_free((phys_addr_t)gd->fdt_blob);
	else
		gd->fdt_blob = (void *)env_get_ulong("fdt_addr_r", 16, 0);

	return rockchip_ram_read_dtb_file(img, (void *)gd->fdt_blob);
}

/*
 * Implement it to support CLI command:
 *   - Android: bootm [aosp addr]
 *   - FIT:     bootm [fit addr]
 *   - uImage:  bootm [uimage addr]
 *
 * Purpose:
 *   - The original bootm command args require fdt addr on AOSP,
 *     which is not flexible on rockchip boot/recovery.img.
 *   - Take Android/FIT/uImage image into sysmem management to avoid image
 *     memory overlap.
 */
#if defined(CONFIG_ANDROID_BOOTLOADER) ||	\
	defined(CONFIG_ROCKCHIP_FIT_IMAGE) ||	\
	defined(CONFIG_ROCKCHIP_UIMAGE)
int board_do_bootm(int argc, char * const argv[])
{
	int format;
	void *img;

	if (argc != 2)
		return 0;

	img = (void *)simple_strtoul(argv[1], NULL, 16);
	format = (genimg_get_format(img));

	/* Android */
#ifdef CONFIG_ANDROID_BOOT_IMAGE
	if (format == IMAGE_FORMAT_ANDROID) {
		struct andr_img_hdr *hdr;
		ulong load_addr;
		ulong size;
		int ret;

		hdr = (struct andr_img_hdr *)img;
		printf("BOOTM: transferring to board Android\n");

		load_addr = env_get_ulong("kernel_addr_r", 16, 0);
		load_addr -= hdr->page_size;
		size = android_image_get_end(hdr) - (ulong)hdr;

		if (!sysmem_alloc_base(MEM_ANDROID, (ulong)hdr, size))
			return -ENOMEM;

		ret = bootm_image_populate_dtb(img);
		if (ret) {
			printf("bootm can't read dtb, ret=%d\n", ret);
			return ret;
		}

		ret = android_image_memcpy_separate(hdr, &load_addr);
		if (ret) {
			printf("board do bootm failed, ret=%d\n", ret);
			return ret;
		}

		return android_bootloader_boot_kernel(load_addr);
	}
#endif

	/* FIT */
#if IMAGE_ENABLE_FIT
	if (format == IMAGE_FORMAT_FIT) {
		char boot_cmd[64];
		int ret;

		printf("BOOTM: transferring to board FIT\n");

		ret = bootm_image_populate_dtb(img);
		if (ret) {
			printf("bootm can't read dtb, ret=%d\n", ret);
			return ret;
		}
		snprintf(boot_cmd, sizeof(boot_cmd), "boot_fit %s", argv[1]);
		return run_command(boot_cmd, 0);
	}
#endif

	/* uImage */
#if 0
#if defined(CONFIG_IMAGE_FORMAT_LEGACY)
	if (format == IMAGE_FORMAT_LEGACY &&
	    image_get_type(img) == IH_TYPE_MULTI) {
		char boot_cmd[64];

		printf("BOOTM: transferring to board uImage\n");
		snprintf(boot_cmd, sizeof(boot_cmd), "boot_uimage %s", argv[1]);
		return run_command(boot_cmd, 0);
	}
#endif
#endif
	return 0;
}
#endif

void autoboot_command_fail_handle(void)
{
#ifdef CONFIG_ANDROID_AB
	if (rk_avb_ab_have_bootable_slot() == true)
		run_command("reset;", 0);
	else
		run_command("fastboot usb 0;", 0);
#endif

#ifdef CONFIG_AVB_VBMETA_PUBLIC_KEY_VALIDATE
	run_command("rockusb 0 ${devtype} ${devnum}", 0);
	run_command("fastboot usb 0;", 0);
#endif

}

#ifdef CONFIG_FIT_ROLLBACK_PROTECT

#define FIT_ROLLBACK_INDEX_LOCATION	0x66697472	/* "fitr" */

int fit_read_otp_rollback_index(uint32_t fit_index, uint32_t *otp_index)
{
#ifdef CONFIG_OPTEE_CLIENT
	u64 index;
	int ret;

	ret = trusty_read_rollback_index(FIT_ROLLBACK_INDEX_LOCATION, &index);
	if (ret) {
		if (ret != TEE_ERROR_ITEM_NOT_FOUND)
			return ret;

		index = 0;
		printf("Initial otp index as %d\n", fit_index);
	}

	*otp_index = (uint32_t)index;
#else
	*otp_index = 0;
#endif

	return 0;
}

int fit_write_trusty_rollback_index(u32 trusty_index)
{
	if (!trusty_index)
		return 0;

	return trusty_write_rollback_index(FIT_ROLLBACK_INDEX_LOCATION,
					   (u64)trusty_index);
}
#endif

void board_quiesce_devices(void *images)
{
	bootm_headers_t *bootm_images = (bootm_headers_t *)images;
	ulong kernel_addr;

#ifdef CONFIG_ROCKCHIP_PRELOADER_ATAGS
	/* Destroy atags makes next warm boot safer */
	atags_destroy();
#endif
#ifdef CONFIG_FIT_ROLLBACK_PROTECT
	int ret;

	ret = fit_write_trusty_rollback_index(gd->rollback_index);
	if (ret) {
		panic("Failed to write fit rollback index %d, ret=%d",
		      gd->rollback_index, ret);
	}
#endif
#ifdef CONFIG_ROCKCHIP_HW_DECOMPRESS
	misc_decompress_cleanup();
#endif
	/* relocate kernel after decompress cleanup */
	kernel_addr = env_get_ulong("kernel_addr_r", 16, 0);
	if (kernel_addr != bootm_images->ep) {
		memmove((char *)bootm_images->ep, (const char *)kernel_addr,
			bootm_images->os.image_len);
		printf("== DO RELOCATE == Kernel from 0x%08lx to 0x%08lx\n",
		       kernel_addr, bootm_images->ep);
	}

	hotkey_run(HK_CMDLINE);
	hotkey_run(HK_CLI_OS_GO);
#ifdef CONFIG_ROCKCHIP_REBOOT_TEST
	do_reset(NULL, 0, 0, NULL);
#endif
}

#ifdef CONFIG_CMD_BOOT_ANDROID
char *board_fdt_chosen_bootargs(void *fdt)
{
	/* bootargs_ext is used when dtbo is applied. */
	const char *arr_bootargs[] = { "bootargs", "bootargs_ext" };
	const char *bootargs;
	int nodeoffset;
	int i, dump;
	char *msg = "kernel";

	/* debug */
	hotkey_run(HK_INITCALL);
	dump = is_hotkey(HK_CMDLINE);
	if (dump)
		printf("## bootargs(u-boot): %s\n\n", env_get("bootargs"));

	/* find or create "/chosen" node. */
	nodeoffset = fdt_find_or_add_subnode(fdt, 0, "chosen");
	if (nodeoffset < 0)
		return NULL;

	for (i = 0; i < ARRAY_SIZE(arr_bootargs); i++) {
		bootargs = fdt_getprop(fdt, nodeoffset, arr_bootargs[i], NULL);
		if (!bootargs)
			continue;
		if (dump)
			printf("## bootargs(%s-%s): %s\n\n",
			       msg, arr_bootargs[i], bootargs);
		/*
		 * Append kernel bootargs
		 * If use AB system, delete default "root=" which route
		 * to rootfs. Then the ab bootctl will choose the
		 * high priority system to boot and add its UUID
		 * to cmdline. The format is "roo=PARTUUID=xxxx...".
		 */
#ifdef CONFIG_ANDROID_AB
		env_update_filter("bootargs", bootargs, "root=");
#else
		env_update("bootargs", bootargs);
#endif
	}

#ifdef CONFIG_ENVF
	char * sys_bootargs;

	sys_bootargs = env_get("sys_bootargs");
	if (sys_bootargs) {
		env_update("bootargs", sys_bootargs);
		if (dump)
			printf("## sys_bootargs: %s\n\n", sys_bootargs);
	}
#endif
#ifdef CONFIG_MTD_BLK
	if (!env_get("mtdparts")) {
		char *mtd_par_info = mtd_part_parse(NULL);

		if (mtd_par_info) {
			if (memcmp(env_get("devtype"), "mtd", 3) == 0)
				env_update("bootargs", mtd_par_info);
		}
	}
#endif
	/*
	 * Initrd fixup: remove unused "initrd=0x...,0x...",
	 * this for compatible with legacy parameter.txt
	 */
	env_delete("bootargs", "initrd=", 0);

	/*
	 * If uart is required to be disabled during
	 * power on, it would be not initialized by
	 * any pre-loader and U-Boot.
	 *
	 * If we don't remove earlycon from commandline,
	 * kernel hangs while using earlycon to putc/getc
	 * which may dead loop for waiting uart status.
	 * (It seems the root cause is baundrate is not
	 * initilalized)
	 *
	 * So let's remove earlycon from commandline.
	 */
	if (gd->flags & GD_FLG_DISABLE_CONSOLE)
		env_delete("bootargs", "earlycon=", 0);

	/* Android header v4+ need this handle */
#ifdef CONFIG_ANDROID_BOOT_IMAGE
	struct andr_img_hdr *hdr;

	hdr = (void *)env_get_ulong("android_addr_r", 16, 0);
	if (hdr && !android_image_check_header(hdr) && hdr->header_version >= 4) {
		if (env_update_extract_subset("bootargs", "andr_bootargs", "androidboot."))
			printf("extract androidboot.xxx error\n");
		if (dump)
			printf("## bootargs(android): %s\n\n", env_get("andr_bootargs"));
	}
#endif
	bootargs = env_get("bootargs");
	if (dump)
		printf("## bootargs(merged): %s\n\n", bootargs);

	return (char *)bootargs;
}
#endif

int ft_verify_fdt(void *fdt)
{
	/* for android header v4+, we load bootparams and fixup initrd */
#if defined(CONFIG_ANDROID_BOOT_IMAGE) && defined(CONFIG_XBC)
	struct andr_img_hdr *hdr;
	uint64_t initrd_start, initrd_end;
	char *bootargs, *p;
	int nodeoffset;
	int is_u64, err;
	u32 len;

	hdr = (void *)env_get_ulong("android_addr_r", 16, 0);
	if (!hdr || android_image_check_header(hdr) ||
	    hdr->header_version < 4)
		return 1;

	bootargs = env_get("andr_bootargs");
	if (!bootargs)
		return 1;

	/* trans character: space to new line */
	p = bootargs;
	while (*p++) {
		if (*p == ' ')
			*p = '\n';
	}

	debug("## andr_bootargs: %s\n", bootargs);

	/*
	 * add boot params right after bootconfig
	 *
	 * because we can get final full bootargs in board_fdt_chosen_bootargs(),
	 * android_image_get_ramdisk() is early than that.
	 *
	 * we have to add boot params by now.
	 */
	len = addBootConfigParameters((char *)bootargs, strlen(bootargs),
		(u64)hdr->ramdisk_addr + hdr->ramdisk_size +
		hdr->vendor_ramdisk_size, hdr->vendor_bootconfig_size);
	if (len < 0) {
		printf("error: addBootConfigParameters\n");
		return 0;
	}

	nodeoffset = fdt_subnode_offset(fdt, 0, "chosen");
	if (nodeoffset < 0) {
		printf("error: No /chosen node\n");
		return 0;
	}

	/* fixup initrd with real value */
	fdt_delprop(fdt, nodeoffset, "linux,initrd-start");
	fdt_delprop(fdt, nodeoffset, "linux,initrd-end");

	is_u64 = (fdt_address_cells(fdt, 0) == 2);
	initrd_start = hdr->ramdisk_addr;
	initrd_end = initrd_start + hdr->ramdisk_size +
			hdr->vendor_ramdisk_size +
			hdr->vendor_bootconfig_size + len;
	err = fdt_setprop_uxx(fdt, nodeoffset, "linux,initrd-start",
			      initrd_start, is_u64);
	if (err < 0) {
		printf("WARNING: could not set linux,initrd-start %s.\n",
		       fdt_strerror(err));
		return 0;
	}
	err = fdt_setprop_uxx(fdt, nodeoffset, "linux,initrd-end",
			      initrd_end, is_u64);
	if (err < 0) {
		printf("WARNING: could not set linux,initrd-end %s.\n",
		       fdt_strerror(err));
		return 0;
	}
#endif
	return 1;
}

