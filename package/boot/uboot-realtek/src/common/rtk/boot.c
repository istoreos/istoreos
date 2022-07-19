#include <common.h>
#include <command.h>

#include <rtk/boot.h>
#include <rtk/watchdog_api.h>
#include <rtk/fw_info.h>

#if 0
BOOT_FROM_FLASH_T boot_from_flash = BOOT_FROM_FLASH_NORMAL_MODE;
BOOT_FROM_USB_T boot_from_usb = BOOT_FROM_USB_DISABLE;


int rtk_plat_set_fw(void)
{
	printf("%s not port yet, use default configs\n", __FUNCTION__);
	return RTK_PLAT_ERR_OK;
}

/* Calls booti with the parameters given */
static int rtk_call_booti(void)
{
	char *booti_argv[] = { "booti", NULL, "-", NULL, NULL };
	int ret = 0;
	int j;
	int argc=4;

	if (getenv("hyp_loadaddr")) {
		booti_argv[1] = getenv("hyp_loadaddr");
	} else if ((booti_argv[1] = getenv("kernel_loadaddr")) == NULL) {
		booti_argv[1] =(char*) CONFIG_KERNEL_LOADADDR;
	}

	if ((booti_argv[3] = getenv("fdt_loadaddr")) == NULL) {
		booti_argv[3] =(char*) CONFIG_FDT_LOADADDR;
	}

	/*
	 * - do the work -
	 * exec subcommands of do_booti to init the images
	 * data structure
	 */
	debug("booti_argv ={ ");
	for (j = 0; j < argc; j++)
			debug("%s,",booti_argv[j]);
	debug("}\n");

	ret = do_booti(find_cmd("do_booti"), 0, argc, booti_argv);

	if (ret) {
		printf("ERROR do_booti failed!\n");
		return -1;
	}

	return 1;
}

//all standard boot_cmd entry.
int rtk_plat_do_boot_linux(void)
{
	rtk_call_booti();

	/* Reached here means jump to kernel entry flow failed */
	return RTK_PLAT_ERR_BOOT;
}

/*
 ************************************************************************
 *
 * This is the final part before booting Linux in realtek platform:
 * we need to move audio/video firmware and stream files
 * from flash to ram. We will also decompress or decrypt image files,
 * if necessary, which depends on the information from flash writer.
 *
 ************************************************************************
 */
int  rtk_plat_boot_handler(void)
{
	int ret = RTK_PLAT_ERR_OK;

	/* copy audio/video firmware and stream files from flash to ram */
	ret = rtk_plat_set_fw();

	if (ret == RTK_PLAT_ERR_OK) {
#ifndef DEBUG_SKIP_BOOT_LINUX
		if (boot_from_flash == BOOT_FROM_FLASH_NORMAL_MODE) {
			/* go Linux */
#ifdef CONFIG_REALTEK_WATCHDOG
			WATCHDOG_KICK();
#else
			WATCHDOG_DISABLE();
#endif
			ret = rtk_plat_do_boot_linux();
		} else {
			printf("[Skip K] boot manual mode (execute \"go all\")\n");
		}
#endif
	}

	return ret;
}
#endif