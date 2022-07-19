#include <common.h>
#include <malloc.h>

#include <linux/usb/ch9.h>
#include <linux/usb/gadget.h>
#include <asm/arch/fw_info.h>

#include "bootimg.h"
#include "rtk_storage_layout.h"

#define PAGE_MASK 2047
#define ROUND_TO_PAGE(x) (((x) + PAGE_MASK) & (~PAGE_MASK))

#define KERNEL_MAX_SIZE 0x1400000

#define TRACEF(str, x...) \
do { \
	printf("%s:%d: " str, __func__, __LINE__, ## x); \
} while (0)

#define LTRACEF debug

#define ADDR_BUF_LEN   32

extern BOOT_MODE boot_mode;
extern int rtk_plat_prepare_fw_image_from_eMMC(void);

static bool set_flash_bootcode = false;
static bool set_manual_boot = false;

enum image_type {
	UNKNOW_IMAGE = 0,
	KERNEL_IMAGE = 1,
	DTB_IMAGE,
	ROOTFS_IMAGE,
	AUDIO_IMAGE,
};

static enum image_type load_image_type = UNKNOW_IMAGE;

struct Kernel_Img_Header {
	uint32_t	instruction0;
	uint32_t	instruction1;
	uint64_t	image_offset;
	uint64_t	image_size;
	uint64_t	ignr1;
	uint64_t	ignr2;
	uint64_t	ignr3;
	uint64_t	ignr4;
	uint32_t	magic;
	uint32_t	ignr5;
};

__maybe_unused
static unsigned hex2unsigned(const char *x)
{
    unsigned n = 0;

    while(*x) {
        switch(*x) {
        case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9':
            n = (n << 4) | (*x - '0');
            break;
        case 'a': case 'b': case 'c':
        case 'd': case 'e': case 'f':
            n = (n << 4) | (*x - 'a' + 10);
            break;
        case 'A': case 'B': case 'C':
        case 'D': case 'E': case 'F':
            n = (n << 4) | (*x - 'A' + 10);
            break;
        default:
            return n;
        }
        x++;
    }

    return n;
}

#ifdef CONFIG_USB_FUNCTION_FASTBOOT
extern void fastboot_ack(char *code, char *reason);
extern void fastboot_okay_and_complete(
	void (*complete)(struct usb_ep *ep, struct usb_request *req));
#else
void fastboot_ack(char *code, char *reason) {}
void fastboot_okay_and_complete(
	void (*complete)(struct usb_ep *ep, struct usb_request *req)) {}
#endif

void fastboot_fail(char *reason)
{
	printf("%s reason %s\n", __func__, reason);
	fastboot_ack("FAIL", reason);
}

void fastboot_okay(char *reason)
{
	printf("%s reason %s\n", __func__, reason);
	fastboot_ack("OKAY", reason);
}

void fastboot_info(char *reason)
{
	printf("%s reason %s\n", __func__, reason);
	fastboot_ack("INFO", reason);
}

#ifdef CONFIG_USB_GADGET_RTK
extern void udc_usb_dev_stop(void);
#else
void udc_usb_dev_stop(void) {}
#endif

void fastboot_usb_stop(void)
{
	udc_usb_dev_stop();
}

static int load_image(char *name, void *addr, unsigned int size)
{
	uint64_t img_addr;

	img_addr = getenv_ulong(name, 16, 0);
	if (img_addr <= 0) {
		printf("%s, %s read error\n", __func__, name);
		return -1;
	}

	printf("%s: %p, from addr: %p, size: %d\n", name,
		    (void *)img_addr, addr, size);

	memmove((void*)img_addr, (void*)addr, size);
	flush_cache((unsigned long)img_addr, size);

	return 0;
}

static int load_bootcode_image(void *addr, unsigned int size) {
	uint64_t img_addr = 0x1500000;
	printf("%s, load bootcode to %p, from addr: %p, size: %d\n",
		    __func__, (void *) img_addr, addr, size);
	memmove((void*)img_addr, (void*)addr, size);
	flush_cache((unsigned long)img_addr, size);
	return 0;
}

static void complete_flash_bootcode(
	    struct usb_ep *ep, struct usb_request *req)
{
	printf("%s, flash bootcode from 0x1500000\n", __func__);

	fastboot_usb_stop();

	run_command("go 0x1500000", 0);
}

static void complete_cmd_go_all(
	    struct usb_ep *ep, struct usb_request *req);

int cmd_boot_rtk(const char *arg, void *data, unsigned sz)
{
	unsigned kernel_actual;
	unsigned ramdisk_actual;
	unsigned second_actual;
	static struct boot_img_hdr hdr;
	struct Kernel_Img_Header *kernel_img_header = NULL;
	char *ptr = ((char*) data);

	printf("fastboot: cmd_boot\n");

	if (sz < sizeof(hdr)) {
		fastboot_fail("invalid bootimage header");
		return 0;
	}

	memcpy(&hdr, data, sizeof(hdr));

	/* ensure commandline is terminated */
	hdr.cmdline[BOOT_ARGS_SIZE-1] = 0;

	kernel_actual = ROUND_TO_PAGE(hdr.kernel_size);
	ramdisk_actual = ROUND_TO_PAGE(hdr.ramdisk_size);
	second_actual = ROUND_TO_PAGE(hdr.second_size);

	if (2048 + kernel_actual + ramdisk_actual + second_actual < sz) {
		fastboot_fail("incomplete bootimage");
		return 0;
	}

	kernel_img_header = (struct Kernel_Img_Header*)(ptr + 2048);

	printf("Bootimg header magic %s kernel_size %d ramdisk_size %d "
		    "second_size %d\n",
		    hdr.magic, hdr.kernel_size, hdr.ramdisk_size, hdr.second_size);

	if (set_flash_bootcode && hdr.kernel_size > 0) {
		load_bootcode_image((void*) (ptr + 2048), hdr.kernel_size);
		fastboot_info("To flash bootcode");
	} else if (set_manual_boot && hdr.kernel_size > 0) {
		switch (load_image_type) {
		case KERNEL_IMAGE:
			load_image("kernel_loadaddr",
				    (void*) (ptr + 2048), hdr.kernel_size);
			fastboot_info("Load Kernel Image, "
				    "use \"fastboot continue\" to boot");
			break;
		case DTB_IMAGE:
			load_image("fdt_loadaddr",
				    (void*) (ptr + 2048), hdr.kernel_size);
			fastboot_info("Load dtb Image, "
				    "use \"fastboot continue\" to boot");
			break;
		case ROOTFS_IMAGE:
			load_image("rootfs_loadaddr",
				    (void*) (ptr + 2048), hdr.kernel_size);
			fastboot_info("Load rootfs Image, "
				    "use \"fastboot continue\" to boot");
			break;
		case AUDIO_IMAGE:
			load_image("audio_loadaddr",
				    (void*) (ptr + 2048), hdr.kernel_size);
			fastboot_info("Load Audio Image, "
				    "use \"fastboot continue\" to boot");
			break;
		default:
			fastboot_info("UNKNOW_IMAGE");
			break;
		}
	} else {
		if (hdr.kernel_size > 0)
			load_image("kernel_loadaddr", (void*) (ptr + 2048),
				    kernel_img_header->image_size);
		if (hdr.kernel_size > KERNEL_MAX_SIZE)
			load_image("fdt_loadaddr", (void*) (ptr + 2048 + KERNEL_MAX_SIZE),
				    hdr.kernel_size - KERNEL_MAX_SIZE);
		if (hdr.ramdisk_size > 0)
			load_image("rootfs_loadaddr", (void*) (ptr + 2048 + kernel_actual),
				    hdr.ramdisk_size);
		if (hdr.second_size > 0)
			load_image("audio_loadaddr", (void *) (ptr + 2048 + kernel_actual +
				    ramdisk_actual), hdr.second_size);
		fastboot_info("To load bootimg");
	}


	*(volatile unsigned int*)(0x98015934) = 0x0;

	if (set_flash_bootcode) {
		fastboot_okay_and_complete(complete_flash_bootcode);
	} else if (set_manual_boot) {
		fastboot_okay("");
		// Do nothing
	} else {
		fastboot_okay_and_complete(complete_cmd_go_all);
	}
	return 1;
}

int cmd_continue_rtk(void)
{
	if (boot_mode == BOOT_NORMAL_MODE) {
		printf("boot normal images");
	} if (boot_mode == BOOT_RESCUE_MODE) {
		printf("boot resuce images");
	}

	fastboot_usb_stop();

	//thread_sleep(250);
	if (run_command("go a", 0) != 0) {
		printf("run_command \"go a\" failed!\n");
	}
	if (run_command("go k", 0) != 0) {
		printf("go k failed!\n");
	}
	return 1;
}

__maybe_unused
static void cmd_erase(const char *arg, void *data, unsigned sz)
{
	fastboot_fail("No support erase command");
}

extern int parse_sparse_image(const char *arg, void *data, size_t sz,
		int (*flash_image)(const char *arg, uint64_t file_size, uint64_t offset,
			void *data, unsigned size));
extern int process_tar_image(void *data, size_t sz,
		int (*flash_image)(const char *arg, uint64_t file_size, uint64_t offset,
			void *data, unsigned size));

int flash_image(const char *arg, uint64_t file_size, uint64_t offset,
		void *data, unsigned sz)
{
	int ret = 0;
	static uint32_t type = ORIGIN;

	LTRACEF("To flash:%s offset 0x%llx/0x%llx (data@%p size %x)\n",
			arg, offset, file_size, data, sz);

	if (!strcmp(arg, "img")) {
		/* process install.img */
		LTRACEF("To flash install.img\n");
		type = BUILD_MBR;
		process_tar_image(data, sz, flash_image);

		LTRACEF("To flash install.img OK ...)\n");

		return 0;
	}
	if (!strcmp(arg, "gimg")) {
		LTRACEF("To flash gpt install.img\n");
		type = BUILD_GPT;
		process_tar_image(data, sz, flash_image);

		return 0;
	}

	if (data == NULL) {
		LTRACEF("NO data to flash:%s offset 0x%llx (data@%p size %x)\n",
			arg, offset, data, sz);
		return 0;
	}

	ret = write_to_storage(arg, type, file_size, offset, data, sz);

	LTRACEF("To flash OK ... (%s offset 0x%llx/0x%llx data@%p size %x)\n",
		    arg, offset, file_size, data, sz);

	return ret;
}

int cmd_flash_rtk(const char *arg, void *data, unsigned sz)
{
	printf("fastboot: cmd_flash_rtk\n");

	parse_sparse_image(arg, data, sz, flash_image);

	printf("fastboot: cmd_flash_rtk Done\n");

	fastboot_okay("");
	return 1;
}

__maybe_unused
static void cmd_reboot_bootloader(const char *arg, void *data, unsigned sz)
{
	printf("fastboot: cmd_reboot_bootloader\n");
	fastboot_info("rebooting the device to fastboot mode\n");
	fastboot_okay("");

//	writel(REBOOT_MAGIC | RESET_ACTION_FASTBOOT, REBOOT_ACTION_ADDR);
//	writel(0x0, 0x980076C4);

	//thread_sleep(250);
	do_reset(NULL, 0, 0, NULL);
}

static void cmd_load_default_images(const char *arg, void *data, unsigned sz)
{
	printf("fastboot: cmd_load_default_images\n");
	set_manual_boot = true;
	boot_mode = BOOT_NORMAL_MODE;
	rtk_plat_prepare_fw_image_from_eMMC();
	fastboot_info("load_default_images");

	fastboot_okay("");
}

static void cmd_load_rescue_images(const char *arg, void *data, unsigned sz)
{
	printf("fastboot: cmd_load_rescue_images\n");
	set_manual_boot = true;
	boot_mode = BOOT_RESCUE_MODE;
	rtk_plat_prepare_fw_image_from_eMMC();

	fastboot_info("load_rescue_images");

	fastboot_okay("");
}

static void cmd_set_load_kernel(const char *arg, void *data, unsigned sz)
{
	printf("fastboot: cmd_set_load_kernel\n");
	set_manual_boot = true;
	load_image_type = KERNEL_IMAGE;
	fastboot_info("boot command set to load kernel");
	fastboot_info("run \"fastboot boot kernel\"");

	fastboot_okay("");
}

static void cmd_set_load_dtb(const char *arg, void *data, unsigned sz)
{
	printf("fastboot: cmd_set_load_dtb\n");
	set_manual_boot = true;
	load_image_type = DTB_IMAGE;
	fastboot_info("boot command set to load dtb");
	fastboot_info("run \"fastboot boot dtb\"");

	fastboot_okay("");
}

static void cmd_set_load_rootfs(const char *arg, void *data, unsigned sz)
{
	printf("fastboot: cmd_set_load_rootfs\n");
	set_manual_boot = true;
	load_image_type = ROOTFS_IMAGE;
	fastboot_info("boot command set to load rootfs");
	fastboot_info("run \"fastboot boot rootfs\"");

	fastboot_okay("");
}

static void cmd_set_load_audio(const char *arg, void *data, unsigned sz)
{
	printf("fastboot: cmd_set_load_audio\n");
	set_manual_boot = true;
	load_image_type = AUDIO_IMAGE;
	fastboot_info("boot command set to load audio");
	fastboot_info("run \"fastboot boot audio\"");

	fastboot_okay("");
}

static void cmd_set_flash_boorcode(const char *arg, void *data, unsigned sz)
{
	printf("fastboot: cmd_set_flash_boorcode\n");
	boot_mode = BOOT_FASTBOOT_MODE;
	set_flash_bootcode = true;

	fastboot_info("boot command set to flash bootcode");
	fastboot_info("run \"fastboot boot dvrboot.exe.bin\"");
	fastboot_okay("");
}

static void complete_cmd_go_a(
	    struct usb_ep *ep, struct usb_request *req)
{
	printf("%s\n", __func__);
	fastboot_usb_stop();

	//thread_sleep(250);
	if (run_command("go a", 0) != 0) {
		printf("run_command \"go a\" failed!\n");
	}
}

static void cmd_go_a(const char *arg, void *data, unsigned sz)
{
	printf("fastboot: cmd_go_a\n");
	fastboot_info("Boot audio FW");

	fastboot_okay_and_complete(complete_cmd_go_a);
}

static void complete_cmd_go_k(
	    struct usb_ep *ep, struct usb_request *req)
{
	printf("%s\n", __func__);
	fastboot_usb_stop();

	//thread_sleep(250);
	if (run_command("go k", 0) != 0) {
		printf("run_command \"go k\" failed!\n");
	}
}

static void cmd_go_k(const char *arg, void *data, unsigned sz)
{
	printf("fastboot: cmd_go_k\n");
	fastboot_info("Boot kernel only");

	fastboot_okay_and_complete(complete_cmd_go_k);
}

static void complete_cmd_go_all(
	    struct usb_ep *ep, struct usb_request *req)
{
	printf("%s\n", __func__);
	fastboot_usb_stop();

	//thread_sleep(250);
	if (run_command("go all", 0) != 0) {
		printf("run_command \"go all\" failed!\n");
	}
}

static void cmd_go_all(const char *arg, void *data, unsigned sz)
{
	printf("fastboot: cmd_go_all\n");
	fastboot_info("Boot kernel and audio");

	fastboot_okay_and_complete(complete_cmd_go_all);
}

__maybe_unused
static void cmd_get_emmc_layout(const char *arg, void *data, unsigned sz)
{
	size_t count = 0;
	size_t buf_sz = 1024*20;
	char *buf = malloc(buf_sz);
	char *line = NULL;

	printf("fastboot: cmd_get_emmc_layout\n");

	count = dump_fw_layout(buf, buf_sz);

	printf("fastboot: count = %d\n", (int)count);

	line = strtok(buf, "\n");

	while (line != NULL) {
		fastboot_info(line);
		line = strtok(NULL, "\n");
	}

	free(buf);
	fastboot_okay("");
}

__maybe_unused
static void cmd_get_part_info(const char *arg, void *data, unsigned sz)
{
	size_t count = 0;
	size_t buf_sz = 1024*20;
	char *buf = malloc(buf_sz);
	char *line = NULL;

	printf("fastboot: cmd_get_part_info\n");

	count = dump_part_info(buf, buf_sz);

	printf("fastboot: count = %d\n", (int)count);

	line = strtok(buf, "\n");

	while (line != NULL) {
		fastboot_info(line);
		line = strtok(NULL, "\n");
	}

	free(buf);
	fastboot_okay("");
}

__maybe_unused
static void cmd_get_fw_info(const char *arg, void *data, unsigned sz)
{
	size_t count = 0;
	size_t buf_sz = 1024*20;
	char *buf = malloc(buf_sz);
	char *line = NULL;

	printf("fastboot: cmd_get_fw_info\n");

	count = dump_fw_info(buf, buf_sz);

	printf("fastboot: count = %d\n", (int)count);

	line = strtok(buf, "\n");

	while (line != NULL) {
		fastboot_info(line);
		line = strtok(NULL, "\n");
	}

	free(buf);
	fastboot_okay("");
}

size_t dump_help(void *buf, unsigned buf_sz)
{
	size_t count = 0;

	count += snprintf(buf + count, buf_sz - count,
		    "List RTK fastboot command usage:\n");
	count += snprintf(buf + count, buf_sz - count,
		    "Update BootCode by fastboot:\n"
		    "    fastboot oem set_flash_bootcode\n"
			"    fastboot boot dvrboot.ext.bin\n");
	count += snprintf(buf + count, buf_sz - count,
		    "Load Normal(default)/resuce Images\n"
		    "    fastboot oem load_default_images\n"
		    "    fastboot oem load_rescue_images\n");
	count += snprintf(buf + count, buf_sz - count,
		    "Use boot command to boot resuce.boot.img\n"
		    "    fastboot boot resuce.boot.img\n");
	count += snprintf(buf + count, buf_sz - count,
		    "Use boot command to load Kernel/dtb/rootfs/audio_fw image\n"
		    "    fastboot oem load_default_images\n"
		    "    fastboot oem set_load_kernel\n"
		    "    fastboot boot emmc.uImage\n"
		    "    fastboot oem set_load_dtb\n"
		    "    fastboot boot android.emmc.dtb\n"
		    "    fastboot oem set_load_rootfs\n"
		    "    fastboot boot android.root.emmc.cpio.gz_pad.img\n"
		    "    fastboot oem set_load_audio\n"
		    "    fastboot boot bluecore.audio\n");
	count += snprintf(buf + count, buf_sz - count,
		    "Command continue to boot\n"
		    "    fastboot.exe continue\n"
		    "    fastboot oem go_k\n"
		    "    fastboot oem go_a\n"
		    "    fastboot oem go_all\n");
	count += snprintf(buf + count, buf_sz - count,
		    "Command to reboot\n"
		    "    fastboot reboot-bootloader\n"
		    "    fastboot reboot\n");
	count += snprintf(buf + count, buf_sz - count,
		    "Command for debug\n"
		    "    fastboot oem get_emmc_layout\n"
		    "    fastboot oem get_part_info\n"
		    "    fastboot oem get_fw_info\n");
	count += snprintf(buf + count, buf_sz - count,
		    "Command usage for flash:\n"
		    "    fastboot flash img install.img\n"
		    "    fastboot flash kernelDT android.emmc.dtb\n"
		    "    fastboot flash rescueDT rescue.emmc.dtb\n"
		    "    fastboot flash rescueRootFS \n"
		    "        rescue.root.emmc.cpio.gz_pad.img\n"
		    "    fastboot flash kernelRootFS \n"
		    "        android.root.emmc.cpio.gz_pad.img\n"
		    "    fastboot flash linuxKernel emmc.uImage\n"
		    "    fastboot flash audioKernel bluecore.audio\n"
		    "    fastboot flash imageFile bootfile.image\n"
		    "    fastboot flash system system.bin\n"
		    "    fastboot flash data data.bin\n"
		    "    fastboot flash cache cache.bin\n"
		    "    fastboot flash vendor vendor.bin\n");
	return count;
}

static void cmd_help(const char *arg, void *data, unsigned sz)
{
	printf("fastboot: cmd_help\n");
	size_t count = 0;
	size_t buf_sz = 1024*20;
	char *buf = malloc(buf_sz);
	char *line = NULL;

	count = dump_help(buf, buf_sz);

	printf("fastboot: count = %d (buf_sz=%d)\n",
		    (int)count, (int)buf_sz);

	line = strtok(buf, "\n");

	while (line != NULL) {
		fastboot_info(line);
		line = strtok(NULL, "\n");
	}

	free(buf);
	fastboot_okay("");
}

int cmd_oem_rtk(char *cmd)
{
	if (!strncmp("help", cmd, 4)) {
		cmd_help(cmd + 4, NULL, 0);
	} if (!strncmp("set_flash_bootcode", cmd,
		    strlen("set_flash_bootcode"))) {
		cmd_set_flash_boorcode(cmd + strlen("set_flash_bootcode"), NULL, 0);
	} else if (!strncmp("load_default_images", cmd,
		    strlen("load_default_images"))) {
		cmd_load_default_images(cmd + strlen("load_default_images"), NULL, 0);
	} else if (!strncmp("load_rescue_images", cmd,
		    strlen("load_rescue_images"))) {
		cmd_load_rescue_images(cmd + strlen("load_rescue_images"), NULL, 0);
	} else if (!strncmp("set_load_kernel", cmd,
		    strlen("set_load_kernel"))) {
		cmd_set_load_kernel(cmd + strlen("set_load_kernel"), NULL, 0);
	} else if (!strncmp("set_load_dtb", cmd,
		    strlen("set_load_dtb"))) {
		cmd_set_load_dtb(cmd + strlen("set_load_dtb"), NULL, 0);
	} else if (!strncmp("set_load_rootfs", cmd,
		    strlen("set_load_rootfs"))) {
		cmd_set_load_rootfs(cmd + strlen("set_load_rootfs"), NULL, 0);
	} else if (!strncmp("set_load_audio", cmd,
		    strlen("set_load_audio"))) {
		cmd_set_load_audio(cmd + strlen("set_load_audio"), NULL, 0);
	} else if (!strncmp("go_all", cmd, 6)) {
		cmd_go_all(cmd + 6, NULL, 0);
	} else if (!strncmp("go_k", cmd, 4)) {
		cmd_go_k(cmd + 4, NULL, 0);
	} else if (!strncmp("go_a", cmd, 4)) {
		cmd_go_a(cmd + 4, NULL, 0);
/*
	} else if (!strncmp("get_emmc_layout", cmd,
		    strlen("get_emmc_layout"))) {
		cmd_get_emmc_layout(cmd + strlen("get_emmc_layout"), NULL, 0);
	} else if (!strncmp("get_part_info", cmd,
		    strlen("get_part_info"))) {
		cmd_get_part_info(cmd + strlen("get_part_info"), NULL, 0);
	} else if (!strncmp("get_fw_info", cmd,
		    strlen("get_fw_info"))) {
		cmd_get_fw_info(cmd + strlen("get_fw_info"), NULL, 0);
*/
	} else {
		return 0;
	}
	return 1;
}
