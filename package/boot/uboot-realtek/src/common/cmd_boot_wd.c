/*
 * (C) Copyright 2000-2003
 * Wolfgang Denk, DENX Software Engineering, wd@denx.de.
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

/*
 * Misc boot support
 */
#include <common.h>
#ifdef CONFIG_BOOT_FOR_WD
#include <command.h>
#include <version.h>
#include <net.h>
#include <asm/arch/rbus/crt_reg.h>
#include <asm/arch/system.h>
//#include <asm/arch/fw_info.h>
#include <asm/arch/fw_info.h>
#include <asm/arch/mcp.h>
#include <asm/arch/pwm.h>
#include <watchdog.h>
#include <nand.h>
#include <asm/arch/rbus/nand_reg.h>
#include <asm/arch/rtk_ipc_shm.h>
#include <asm/sizes.h>
#ifdef CONFIG_CMD_SATA
#include <sata.h>
#endif
#include <asm/arch/factorylib.h>
#include <../drivers/mmc/rtkemmc.h>
#include <rtkspi.h>
#ifdef CONFIG_CUSTOMIZE_BOOTFLOW_1
#include <customized.h>
#endif
#if CONFIG_NAS_ENABLE
#include <fdt_support.h>
#include <version.h>
#endif


#ifdef CONFIG_LZMA
#include <lzma/LzmaTypes.h>
#include <lzma/LzmaDec.h>
#include <lzma/LzmaTools.h>
#endif /* CONFIG_LZMA */
#include "linux/lzo.h"

#define CONFIG_ANDROID_RECOVERY 0
#if CONFIG_ANDROID_RECOVERY
#include <asm/arch/factorylib.h>
#define RECOVERY_FILE_IN_FACTORY    FACTORY_HEADER_FILE_NAME"recovery"

typedef struct _bootloader_message {
    char command[32];
    char status[32];
    char recovery[1024];
} bootloader_message;
#endif

#define CONFIG_FW_TABLE_SIZE    0x8000
//#define CONFIG_FACTORY_SIZE          0x400000


//#define BYPASS_CHECKSUM
//#define EMMC_BLOCK_LOG

#define DEFAULT_SN "FFFFFFFFFFFF"

#define UBOOT_PINGPONG_NEW_DESIGN
#ifdef UBOOT_PINGPONG_NEW_DESIGN
  #define msleep(a)		udelay(a * 1000)
  // Boot config file is in following format:
  // bootstate:nbr:bna
  #define BOOT_CONFIG_FILE_NAME "bootConfig"
#endif /* UBOOT_PINGPONG_NEW_DESIGN */

#define DEFAULT_ANDORIDBOOT_HARDWARE_NAME "kylin"

DECLARE_GLOBAL_DATA_PTR;


typedef enum{
	BOOT_STATE_NO_OTA=0,
	BOOT_STATE_INIT,
	BOOT_STATE_OTA_TRIGGERED,
	BOOT_STATE_OTA_PASSED,
	BOOT_STATE_OTA_FAILED,
	BOOT_STATE_RECOVERY,
	BOOT_STATE_UNKNOWN
}BOOT_STATE_T;

typedef enum{
	BOOT_FROM_USB_DISABLE,
	BOOT_FROM_USB_UNCOMPRESSED,
	BOOT_FROM_USB_COMPRESSED
}BOOT_FROM_USB_T;

typedef enum{
	BOOT_FROM_FLASH_NORMAL_MODE,
	BOOT_FROM_FLASH_MANUAL_MODE
}BOOT_FROM_FLASH_T;

struct boot_config {
    BOOT_STATE_T bState;
    int numBootAttempts; // 1 ~ 5
    char nextBootRegion; //A or B
};

typedef enum {
    BOOT_CFG_STR_STATE=0,
    BOOT_CFG_STR_NBR,
    BOOT_CFG_STR_BNA,
    BOOT_CFG_STR_DONE
}BOOT_CFG_STR_T;

int gUSB_MODE = 0;

static struct boot_config gBootConfig = {0};
static const char cSATA_PART_A[] = "sata";
static const char cSATA_PART_B[] = "sata_b";

#if defined(CONFIG_RTD1195) || defined(CONFIG_RTD1295) || defined(CONFIG_RTD1395)

#ifdef CONFIG_CMD_SATA
  extern int sata_boot_debug;
  extern int sata_curr_device;
  extern block_dev_desc_t sata_dev_desc[CONFIG_SYS_SATA_MAX_DEVICE];
#endif /* CONFIG_CMD_SATA */

//[fw] share memory.
extern struct RTK119X_ipc_shm ipc_shm;

//[fw] image display.
uchar boot_logo_enable=0;
uint custom_logo_src_width=0;
uint custom_logo_src_height=0;
uint custom_logo_dst_width=0;
uint custom_logo_dst_height=0;
uchar sys_logo_is_HDMI = 0;
//uchar sys_logo_enabled = 0;

uint eMMC_bootcode_area_size = 0x220000;		// eMMC bootcode area size
uint eMMC_fw_desc_table_start = 0;				// start address of valid fw desc table in emmc
uint nand_fw_desc_table_start = 0;				// start address of valid fw desc table in nand
uint sata_fw_desc_table_start = 34;				// start address of valid fw desc table in sata

BOOT_FROM_FLASH_T boot_from_flash = BOOT_FROM_FLASH_NORMAL_MODE;
BOOT_FROM_USB_T boot_from_usb = BOOT_FROM_USB_DISABLE;
extern BOOT_MODE boot_mode;

#ifdef CONFIG_TEE
uint tee_enable=0;
#endif /* CONFIG_TEE */
#ifdef NAS_ENABLE
uint initrd_size=0;
#endif /* NAS_ENABLE */

#endif /* defined(CONFIG_RTD1195) || defined(CONFIG_RTD1295) || defined(CONFIG_RTD1395) */

#ifdef CONFIG_CMD_KEY_BURNING
extern int OTP_Get_Byte(int offset, unsigned char *ptr, unsigned int cnt);
extern unsigned int OTP_JUDGE_BIT(unsigned int offset);
#endif /* CONFIG_CMD_KEY_BURNING */

static int accelerate_state = 0;  /*The flag for controlling faster blue logo*/

extern const unsigned int Kh_key_default[4];

#ifdef CONFIG_CMD_GO

#if defined(CONFIG_UBOOT_DEFAULT) || defined(CONFIG_FT_RESCUE)
#if defined(CONFIG_RTD1195) || defined(CONFIG_RTD1295) || defined(CONFIG_RTD1395)

#define BIST_ROOTFS_ADDR    0x30000000
#define BIST_DTB            "rtd-1295-bist.dtb"

extern void delete_env(void);
extern void enable_clock(uint reg_reset, uint mask_reset, uint reg_clock, uint mask_clock);
extern int rtk_plat_boot_go(bootm_headers_t *images);

extern unsigned int mcp_dscpt_addr;
extern const unsigned int Kh_key_default[4];

int rtk_plat_prepare_fw_image_from_NAND(void);
int rtk_plat_prepare_fw_image_from_eMMC(void);
int rtk_plat_prepare_fw_image_from_SATA(void);
int rtk_plat_prepare_fw_image_from_SPI(void);
char *rtk_plat_prepare_fw_image_from_USB(int fw_type);
int rtk_plat_do_boot_linux(void);
int rtk_plat_boot_handler(void);
//static int rtk_call_bootm(void);
static int rtk_call_booti(void);
int decrypt_image(char *src, char *dst, uint length, uint *key);
int rtk_get_secure_boot_type(void);
void rtk_hexdump( const char * str, unsigned char * pcBuf, unsigned int length );
void GetKeyFromSRAM(unsigned int sram_addr, unsigned char* key, unsigned int length);

static void reset_shared_memory(void);


static unsigned long do_go_kernel_image(void)
{
    int ret = RTK_PLAT_ERR_OK;

#ifdef CONFIG_SYS_RTK_NAND_FLASH
	ret = rtk_plat_prepare_fw_image_from_NAND();
#elif defined(CONFIG_SYS_RTK_EMMC_FLASH)
	ret = rtk_plat_prepare_fw_image_from_eMMC();
#elif defined(CONFIG_SYS_RTK_SATA_STORAGE)
	ret = rtk_plat_prepare_fw_image_from_SATA();
#endif
	if (ret!= RTK_PLAT_ERR_OK)
		return ret;

	return rtk_plat_do_boot_linux();
}

static unsigned long do_go_audio_fw(void)
{
	int magic = SWAPEND32(0x16803001);
	int offset = SWAPEND32(MIPS_SHARED_MEMORY_ENTRY_ADDR);
	unsigned long fw_addr = getenv_ulong("audio_loadaddr", 16, 0);

	printf("Start Audio Firmware ...\n");

	reset_shared_memory();

	if (!fw_addr)
		fw_addr = CONFIG_FW_LOADADDR;
	if (!ipc_shm.audio_fw_entry_pt)
		ipc_shm.audio_fw_entry_pt = SWAPEND32(fw_addr | MIPS_KSEG0BASE);

	memcpy((unsigned char *)(MIPS_SHARED_MEMORY_ENTRY_ADDR+0xC4), &ipc_shm, sizeof(ipc_shm));
	memcpy((unsigned char *)(MIPS_SHARED_MEMORY_ENTRY_ADDR), &magic, sizeof(magic));
	memcpy((unsigned char *)(MIPS_SHARED_MEMORY_ENTRY_ADDR +4), &offset, sizeof(offset));

	flush_dcache_all();

	/* Enable ACPU */
	rtd_setbits(CLOCK_ENABLE2_reg,_BIT4);

	return 0;

}

static unsigned long do_go_all_fw(void)
{

	int ret = RTK_PLAT_ERR_OK;

	if (run_command("go a", 0) != 0) {
		printf("go a failed!\n");
		return RTK_PLAT_ERR_BOOT;
	}

	if (run_command("go k", 0) != 0) {
		printf("go k failed!\n");
		return RTK_PLAT_ERR_BOOT;
	}

	return ret;
}
#endif /* defined(CONFIG_RTD1195) || defined(CONFIG_RTD1295) || defined(CONFIG_RTD1395) */

static void led_flag_error(void)
{
#ifdef CONFIG_RTD129X_PWM
    pwm_enable(SYS_LED_PWM_PORT_NUM, 0);
    // Ok, the hdd is having issue, change the LED to tell the end user.
    pwm_set_freq(SYS_LED_PWM_PORT_NUM, 10);  // set the frequency to 1 HZ
    pwm_set_duty_rate(SYS_LED_PWM_PORT_NUM, 50);
    pwm_enable(SYS_LED_PWM_PORT_NUM, 1);
#endif /* CONFIG_RTD129X_PWM */
}

//
// hdd must be ready before we could mount the config partition
//
static int is_sata_initialized(void)
{
#if defined(CONFIG_BOARD_WD_PELICAN)
	// config partition is on the eMMC for Pelican
	return 1;
#elif defined(CONFIG_BOARD_WD_MONARCH)
	if (sata_curr_device == -1) {
		if (sata_initialize() !=0) {
            printf("Error, SATA device initialization failed!\n");
            led_flag_error();
			return 0;
		}
	}
	return 1;
#else
	echo "OPPS: please definbe valid macro for your BOARD"
#endif
}

#ifdef CONFIG_RESCUE_FROM_USB
int rtk_decrypt_rescue_from_usb(char* filename, unsigned int target)
{
	char tmpbuf[128];
	unsigned char ks[16],kh[16],kimg[16];
    unsigned char aes_key[16],rsa_key[256];
    unsigned int real_body_size = 0;
#ifdef CONFIG_CMD_KEY_BURNING
	unsigned int * Kh_key_ptr = NULL;
#else
	unsigned int * Kh_key_ptr = (unsigned int *)(uintptr_t)Kh_key_default;
#endif
	unsigned int img_truncated_size = RSA_SIGNATURE_LENGTH*2+NP_INV32_LENGTH; // install_a will append 256-byte signature data to it
	int ret;
	unsigned int image_size=0;

	extern unsigned int mcp_dscpt_addr;
	mcp_dscpt_addr = 0;


	sprintf(tmpbuf, "fatload usb 0:1 %x %s",ENCRYPTED_FW_ADDR,filename);
	if (run_command(tmpbuf, 0) != 0) {
			return RTK_PLAT_ERR_READ_FW_IMG;
	}

	image_size = getenv_ulong("filesize", 16, 0);

	memset(ks,0x00,16);
	memset(kh,0x00,16);
	memset(kimg,0x00,16);

    memset(aes_key,0x00,16);
	memset(rsa_key,0x00,256);

    GetKeyFromSRAM(KH_P_SRAM_ADDR, aes_key, AES_KEY_SIZE);
    GetKeyFromSRAM(RSA_KEY_FW_SRAM_ADDR, rsa_key, RSA_KEY_SIZE);
    flush_cache((unsigned int) (uintptr_t)aes_key, AES_KEY_SIZE);
    flush_cache((unsigned int) (uintptr_t)rsa_key, RSA_KEY_SIZE);

#ifdef CONFIG_CMD_KEY_BURNING
	OTP_Get_Byte(OTP_K_S, ks, 16);
	OTP_Get_Byte(OTP_K_H, kh, 16);
	sync();
	flush_cache((unsigned int) (uintptr_t)ks, 16);
	flush_cache((unsigned int) (uintptr_t)kh, 16);
#endif
	AES_ECB_encrypt(ks, 16, kimg, (unsigned int *)kh);
	flush_cache((unsigned int) (uintptr_t)kimg, 16);
	sync();

	//Kh_key_ptr = kimg;
	//Kh_key_ptr[0] = swap_endian(Kh_key_ptr[0]);
	//Kh_key_ptr[1] = swap_endian(Kh_key_ptr[1]);
	//Kh_key_ptr[2] = swap_endian(Kh_key_ptr[2]);
	//Kh_key_ptr[3] = swap_endian(Kh_key_ptr[3]);
    Kh_key_ptr = (unsigned int *) (uintptr_t)aes_key;
	flush_cache((unsigned int) (uintptr_t)aes_key, 16);

    // decrypt image
	printf("to decrypt...\n");

	flush_cache((unsigned int) ENCRYPTED_FW_ADDR, image_size);

    if (decrypt_image((char *)ENCRYPTED_FW_ADDR,
		(char *)(uintptr_t)target,
		image_size - img_truncated_size,
		Kh_key_ptr))
	{
		printf("decrypt image:%s error!\n", filename);
		return RTK_PLAT_ERR_READ_FW_IMG;
	}

	sync();
	memset(ks,0x00,16);
	memset(kh,0x00,16);
	memset(kimg,0x00,16);

    copy_memory((void *)(uintptr_t)target + image_size - img_truncated_size,(void *) ENCRYPTED_FW_ADDR + image_size - img_truncated_size, img_truncated_size);
	flush_cache((unsigned int) target, image_size);

    real_body_size = (UINT32)(REG32((volatile UINT32 *)(uintptr_t)target + (image_size - img_truncated_size) - 4));
    real_body_size = swap_endian(real_body_size);
	real_body_size /= 8;

	ret = Verify_SHA256_hash( (unsigned char *)(uintptr_t)target,
							real_body_size,
							(unsigned char *)(uintptr_t)(target + image_size - img_truncated_size),
							1, rsa_key);
	if( ret < 0 ) {
		printf("[ERR] %s: verify hash fail(%d)\n", __FUNCTION__, ret );
		return RTK_PLAT_ERR_READ_FW_IMG;
	}

	return RTK_PLAT_ERR_OK;
}

int boot_rescue_from_usb(void)
{
	char tmpbuf[128];
	int ret = RTK_PLAT_ERR_OK;
	char *filename;
	unsigned int secure_mode=0;

	secure_mode = rtk_get_secure_boot_type();

	printf("==== %s (secure mode:%d)=====\n", __func__, secure_mode);

	run_command("usb start", 0);	/* "usb start" always return 0 */
	if (run_command("usb dev", 0) != 0) {
		printf("No USB device found!\n");
		return RTK_PLAT_ERR_READ_RESCUE_IMG;
	}

    filename = "wd_uboot.bin";
	sprintf(tmpbuf, "fatload usb 0:1 0x1500000 %s", filename);
	if (run_command(tmpbuf, 0) == 0){
#ifdef CONFIG_RTD129X_PWM
        pwm_set_freq(SYS_LED_PWM_PORT_NUM, 20);  // set the frequency to 1 HZ
        pwm_set_duty_rate(SYS_LED_PWM_PORT_NUM, 50);
        pwm_enable(SYS_LED_PWM_PORT_NUM, 1);
#endif /* CONFIG_RTD129X_PWM */
		printf("Loading \"%s\" to 0x1500000 is OK.\n\n", filename);
        run_command_list("go 0x1500000", -1, 0);
	}else{
		printf("Loading \"%s\" from USB failed. Continue installing OS images\n", filename);
	}

	/* DTB */
	if ((filename = getenv("rescue_dtb")) == NULL) {
		filename =(char*) CONFIG_RESCUE_FROM_USB_DTB;
	}
	sprintf(tmpbuf, "fatload usb 0:1 %s %s", getenv("fdt_loadaddr"), filename);
	if (run_command(tmpbuf, 0) != 0) {
		goto loading_failed;
	}

	printf("Loading \"%s\" to %s is OK.\n\n", filename, getenv("fdt_loadaddr"));

	/* Linux kernel */
	if ((filename = getenv("rescue_vmlinux")) == NULL) {
		filename =(char*) CONFIG_RESCUE_FROM_USB_VMLINUX;
	}
	if(secure_mode == RTK_SECURE_BOOT)
	{
		if (rtk_decrypt_rescue_from_usb(filename,getenv_ulong("kernel_loadaddr", 16, 0)))
		goto loading_failed;
	}
	else
	{
		sprintf(tmpbuf, "fatload usb 0:1 %s %s", getenv("kernel_loadaddr"), filename);
		if (run_command(tmpbuf, 0) != 0) {
			goto loading_failed;
		}
	}

	printf("Loading \"%s\" to %s is OK.\n\n", filename, getenv("kernel_loadaddr"));

	/* rootfs */
	if ((filename = getenv("rescue_rootfs")) == NULL) {
		filename =(char*) CONFIG_RESCUE_FROM_USB_ROOTFS;
	}
	if(secure_mode == RTK_SECURE_BOOT)
	{
		if (rtk_decrypt_rescue_from_usb(filename, getenv_ulong("rootfs_loadaddr", 16, 0)))
		goto loading_failed;
	}
	else
	{
		sprintf(tmpbuf, "fatload usb 0:1 %s %s", getenv("rootfs_loadaddr"), filename);
		if (run_command(tmpbuf, 0) != 0) {
			goto loading_failed;
		}
	}

	printf("Loading \"%s\" to %s is OK.\n\n", filename, getenv("rootfs_loadaddr"));

#if 0
	/* TEE OS */
	filename = "tee.bin";
	sprintf(tmpbuf, "fatload usb 0:1 %x %s", CONFIG_TEE_OS_ADDR, filename);
	if (run_command(tmpbuf, 0) == 0){
		printf("Loading \"%s\" to 0x%08x is OK.\n\n", filename, CONFIG_TEE_OS_ADDR);
	}
	else{
		printf("Loading \"%s\" from USB failed.\n", filename);
		goto loading_failed;
	}

	/* BL31 */
	filename = "bl31.bin";
	sprintf(tmpbuf, "fatload usb 0:1 %x %s", CONFIG_BL31_ADDR, filename);
	if (run_command(tmpbuf, 0) == 0){
		printf("Loading \"%s\" to 0x%08x is OK.\n\n", filename, CONFIG_BL31_ADDR);
	}
	else{
		printf("Loading \"%s\" from USB failed.\n", filename);
		goto loading_failed;
	}
#endif

	/* audio firmware */
	if ((filename = getenv("rescue_audio")) == NULL) {
		filename =(char*) CONFIG_RESCUE_FROM_USB_AUDIO_CORE;
	}
	if(secure_mode == RTK_SECURE_BOOT)
	{
		if (!rtk_decrypt_rescue_from_usb(filename, MIPS_AUDIO_FW_ENTRY_ADDR))
		{
			printf("Loading \"%s\" to 0x%08x is OK.\n", filename, MIPS_AUDIO_FW_ENTRY_ADDR);
			run_command("go a", 0);
		}
		else
			printf("Loading \"%s\" from USB failed.\n", filename);
			/* Go on without Audio firmware. */
	}
	else
	{
		sprintf(tmpbuf, "fatload usb 0:1 0x%08x %s", MIPS_AUDIO_FW_ENTRY_ADDR, filename);
		if (run_command(tmpbuf, 0) == 0) {
			printf("Loading \"%s\" to 0x%08x is OK.\n", filename, MIPS_AUDIO_FW_ENTRY_ADDR);
			run_command("go a", 0);
		}
		else {
			printf("Loading \"%s\" from USB failed.\n", filename);
			/* Go on without Audio firmware. */
		}
    }
	boot_mode = BOOT_RESCUE_MODE;

	/* Clear the HYP ADDR since we don't want rescue jump to HYP mode */
	if (getenv("hyp_loadaddr"))
		setenv("hyp_loadaddr", "");

	//ret = rtk_call_bootm();
	ret = rtk_call_booti();
	/* Should not reach here */

	return ret;

loading_failed:
	printf("Loading \"%s\" from USB failed.\n", filename);
	return RTK_PLAT_ERR_READ_RESCUE_IMG;
}
#endif /* CONFIG_RESCUE_FROM_USB */

#ifdef CONFIG_RESCUE_FROM_DHCP
int boot_rescue_from_dhcp(void)
{
	char tmpbuf[128];
	int ret = RTK_PLAT_ERR_OK;
	char *filename;
	char *dhcp_server_ip;
	unsigned int secure_mode=0;

	secure_mode = rtk_get_secure_boot_type();

    if (!is_sata_initialized()) {
        // initialization sata failed.
		return RTK_PLAT_ERR_BOOT;
	}

	// generate the partition table
    // ey: gpt table should be visioned instead of by date
	// generate the partition table
    run_command("rtkgpt gen V3", 0);
    char gpt_ver_str[8];
    sprintf(gpt_ver_str, "%d", CURRENT_GPT_VER);
    setenv("gpt_ver", gpt_ver_str);
    run_command("env save", 0);

	/* DTB */
	if ((filename = getenv("rescue_dtb")) == NULL) {
		filename =(char*) CONFIG_RESCUE_FROM_USB_DTB;
	}

	dhcp_server_ip =(char*) CONFIG_BOOTP_SERVERIP;

	sprintf(tmpbuf, "dhcp %s %s:%s", getenv("fdt_loadaddr"),dhcp_server_ip, filename);
	if (run_command(tmpbuf, 0) != 0) {
		goto loading_failed;
	}

	printf("Loading \"%s\" to %s is OK.\n\n", filename, getenv("fdt_loadaddr"));

	/* Linux kernel */
	if ((filename = getenv("rescue_vmlinux")) == NULL) {
		filename =(char*) CONFIG_RESCUE_FROM_USB_VMLINUX;
	}

	if(secure_mode == RTK_SECURE_BOOT)
	{
		if (rtk_decrypt_rescue_from_usb(filename,getenv_ulong("kernel_loadaddr", 16, 0)))
		goto loading_failed;
	}
	else
	{
		sprintf(tmpbuf, "dhcp %s %s:%s", getenv("kernel_loadaddr"), dhcp_server_ip, filename);
		if (run_command(tmpbuf, 0) != 0) {
			goto loading_failed;
		}
	}

	printf("Loading \"%s\" to %s is OK.\n\n", filename, getenv("kernel_loadaddr"));

	/* rootfs */
	if ((filename = getenv("rescue_rootfs")) == NULL) {
		filename =(char*) CONFIG_RESCUE_FROM_USB_ROOTFS;
	}


	if(secure_mode == RTK_SECURE_BOOT)
	{
		if (rtk_decrypt_rescue_from_usb(filename, getenv_ulong("rootfs_loadaddr", 16, 0)))
		goto loading_failed;
	}
	else
	{

		sprintf(tmpbuf, "dhcp %s %s:%s", getenv("rootfs_loadaddr"), dhcp_server_ip, filename);
		if (run_command(tmpbuf, 0) != 0) {
			goto loading_failed;
		}
	}

	printf("Loading \"%s\" to %s is OK.\n\n", filename, getenv("rootfs_loadaddr"));


	/* audio firmware */
	if ((filename = getenv("rescue_audio")) == NULL) {
		filename =(char*) CONFIG_RESCUE_FROM_USB_AUDIO_CORE;
	}
	if(secure_mode == RTK_SECURE_BOOT)
	{
		if (!rtk_decrypt_rescue_from_usb(filename, MIPS_AUDIO_FW_ENTRY_ADDR))
		{
			printf("Loading \"%s\" to 0x%08x is OK.\n", filename, MIPS_AUDIO_FW_ENTRY_ADDR);
			run_command("go a", 0);
		}
		else
			printf("Loading \"%s\" from USB failed.\n", filename);
			/* Go on without Audio firmware. */
	}
	else
	{
		sprintf(tmpbuf, "dhcp 0x%08x %s:%s", MIPS_AUDIO_FW_ENTRY_ADDR, dhcp_server_ip, filename);

		if (run_command(tmpbuf, 0) == 0) {
			printf("Loading \"%s\" to 0x%08x is OK.\n", filename, MIPS_AUDIO_FW_ENTRY_ADDR);
			run_command("go a", 0);
		}
		else {
			printf("Loading \"%s\" from dhcp failed.\n", filename);
			/* Go on without Audio firmware. */
		}
    }
	boot_mode = BOOT_RESCUE_MODE;

	/* Clear the HYP ADDR since we don't want rescue jump to HYP mode */
	if (getenv("hyp_loadaddr"))
		setenv("hyp_loadaddr", "");

	//ret = rtk_call_bootm();
	ret = rtk_call_booti();
	/* Should not reach here */

	return ret;

loading_failed:
	printf("Loading \"%s\" from dhcp host %s failed.\n", filename, dhcp_server_ip);
	return RTK_PLAT_ERR_READ_RESCUE_IMG;
}
#endif /* CONFIG_RESCUE_FROM_DHCP */


#endif /* defined(CONFIG_UBOOT_DEFAULT) || defined(CONFIG_FT_RESCUE) */

/* Allow ports to override the default behavior */
__attribute__((weak))
unsigned long do_go_exec (ulong (*entry)(int, char * const []), int argc, char * const argv[])
{
	return entry (argc, argv);
}


int reflash_bootloader(int argc, char * const argv[])
{
	char tmpbuf[128];
	int ret = RTK_PLAT_ERR_OK;
	char *filename;
	unsigned int secure_mode = 0;
	ulong	addr;

	secure_mode = rtk_get_secure_boot_type();

	printf("==== %s (secure mode:%d)=====\n", __func__, secure_mode);

	run_command("usb start", 0);	/* "usb start" always return 0 */
	if (run_command("usb dev", 0) != 0) {
		printf("No USB device found!\n");
		return RTK_PLAT_ERR_READ_RESCUE_IMG;
	}

	/* load uboot.bin */
	filename = "uboot.bin";
	sprintf(tmpbuf, "fatload usb 0:1 %s %s", "0x01500000", filename);
	if (run_command(tmpbuf, 0) != 0) {
		goto loading_failed;
	}

	addr = simple_strtoul("0x1500000", NULL, 16);
	do_go_exec((void *)addr, argc -1 , argv + 1 );


	return ret;

loading_failed:
	printf("Loading \"%s\" from USB failed.\n", filename);
	return RTK_PLAT_ERR_READ_RESCUE_IMG;
}


int do_go (cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	ulong	addr, rc;
	int     rcode = 0;
	int     do_cleanup = 0;

	if (argc < 2)
		return CMD_RET_USAGE;

#if defined(CONFIG_UBOOT_DEFAULT) || defined(CONFIG_FT_RESCUE)
#if defined(CONFIG_RTD299X) || defined(CONFIG_RTD1195) || defined(CONFIG_RTD1295) || defined(CONFIG_RTD1395)
	if (argv[1][0] == 'a')
	{
		if (argv[1][1] == '\0')	// audio fw
		{
			return do_go_audio_fw();
		}
		else if (argv[1][1] == 'l' && argv[1][2] == 'l')	// all fw
		{
			return do_go_all_fw();
		}
		else
		{
			printf("Unknown command '%s'\n", argv[1]);
			return CMD_RET_USAGE;
		}
	}
#ifdef CONFIG_BOOT_FROM_SATA
	else if (argv[1][0] == 's')
	{
		sata_boot_debug = 0;
		if( argc > 2 ) {
			if( strncmp( argv[2], "debug", 5 ) == 0 ) {
				sata_boot_debug = 1;
			}
		}
		if( strncmp( argv[1], "snboot", 6 ) == 0 ) {
			boot_mode = BOOT_NORMAL_MODE;
			return rtk_plat_boot_handler();
		}
		else if( strncmp( argv[1], "saboot", 6 ) == 0 ) {
			boot_mode = BOOT_ANDROID_MODE;
			return rtk_plat_boot_handler();
		}
		else if( strncmp( argv[1], "srboot", 6 ) == 0 ) {
			boot_mode = BOOT_RESCUE_MODE;
			return rtk_plat_boot_handler();
		}
		else if( strncmp( argv[1], "sgboot", 6 ) == 0 ) {
			boot_mode = BOOT_GOLD_MODE;
			return rtk_plat_boot_handler();
		}
	}
	else if (argv[1][0] == 'i')
	{
		if( strncmp( argv[1], "info", 4 ) == 0 ) {
			printf("## boot_mode is %d\n", boot_mode);
			printf("## boot_flash_type is %d\n", boot_flash_type);
			printf("## sata_curr_device is %d\n", sata_curr_device);
			printf("## fw_desc_table_v1 struct size    = 0x%lx\n", sizeof(fw_desc_table_v1_t));
			printf("## part_entry struct size          = 0x%lx\n", sizeof(part_desc_entry_v1_t));
			printf("## fw_entry struct size            = 0x%lx\n", sizeof(fw_desc_entry_v1_t));
			return 0;
		}
	}
#endif
	else if (argv[1][0] == 'k')
	{
		if (argv[1][1] == '\0')	// getkernel image from ddr;
		{
			return rtk_plat_do_boot_linux();
		}
		else if (argv[1][1] == 'f')	// get kernel image from flash;
		{
			boot_mode = BOOT_KERNEL_ONLY_MODE;
			return do_go_kernel_image();
		}
		else
		{
			printf("Unknown command '%s'\n", argv[1]);
			return CMD_RET_USAGE;
		}

	}
	else if (argv[1][0] == 'r')
	{
		if (argv[1][1] == '\0') // rescue from flash
		{
			boot_mode = BOOT_RESCUE_MODE;
			return rtk_plat_boot_handler();
		}
		else if (argv[1][1] == 'a') // rescue for android
		{
			boot_mode = BOOT_ANDROID_MODE;
			return rtk_plat_boot_handler();
		}
		else if (argv[1][1] == 'b')
		{
			return reflash_bootloader(argc, argv);
		}
#ifdef CONFIG_RESCUE_FROM_USB
		else if (argv[1][1] == 'u') // rescue from usb
		{
			return boot_rescue_from_usb();
		}
#endif
		else
		{
			return 0;
		}
	}
#endif
#endif

	addr = simple_strtoul(argv[1], NULL, 16);

#ifdef CONFIG_CLEAR_ENV_AFTER_UPDATE_BOOTCODE
	if (addr == DVRBOOT_EXE_BIN_ENTRY_ADDR)
	{
		printf ("Clear env when updating bootcode ...\n");
		delete_env();
	}
#endif

	printf ("Starting application at 0x%08lX ...\n", addr);

	if( strncmp( argv[2], "nocache", 7 ) == 0 ) {
		do_cleanup = 1;
		printf ("Run application w/o any cache\n");
		//cleanup_before_dvrbootexe();
	}

	/*
	 * pass address parameter as argv[0] (aka command name),
	 * and all remaining args
	 */
	rc = do_go_exec ((void *)addr, argc - 1 - do_cleanup, argv + 1 + do_cleanup);
	if (rc != 0) rcode = 1;

	printf ("Application terminated, rc = 0x%lX\n", rc);
	return rcode;
}


int do_goru (cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	//boot_mode = BOOT_CONSOLE_MODE;
#ifdef CONFIG_RESCUE_FROM_USB
	WATCHDOG_DISABLE();
	setenv("bootcmd", "bootr");
	return boot_rescue_from_usb();
#else
	return 0;
#endif
}

/* -------------------------------------------------------------------- */

U_BOOT_CMD(
	go, CONFIG_SYS_MAXARGS, 1,	do_go,
	"start application at address 'addr' or start running fw",
	"[addr/a/v/v1/v2/k] [arg ...]\n"
	"\taddr  - start application at address 'addr'\n"
	"\ta     - start audio firmware\n"
	"\tk     - start kernel\n"
	"\tr     - start rescue linux\n"
#ifdef CONFIG_RESCUE_FROM_USB
	"\tru    - start rescue linux from usb\n"
#endif
#ifdef CONFIG_BOOT_FROM_SATA
    "\tsnboot - go sata boot flow(BOOT_NORMAL_MODE)\n"
    "\tsaboot - go sata boot flow(BOOT_ANDROID_MODE)\n"
    "\tsrboot - go sata rescue boot flow(BOOT_RESCUE_MODE)\n"
	"\tsgboot - go golden rescue boot flow(BOOT_GOLD_MODE)\n"
	"\tinfo   - show curren mode info\n"
#endif
	"\tall   - start all firmware\n"
	"\t[arg] - passing 'arg' as arguments\n"
);


/* -------------------------------------------------------------------- */

U_BOOT_CMD(
	goru, CONFIG_SYS_MAXARGS, 1,    do_goru,
	"start rescue linux from usb",
	""
);

#endif


U_BOOT_CMD(
	reset, 1, 0,	do_reset,
	"Perform RESET of the CPU",
	""
);

uint get_checksum(uchar *p, uint len) {
	uint checksum = 0;
	uint i;

	for(i = 0; i < len; i++) {
		checksum += *(p+i);

		if (i % 0x200000 == 0)
		{
			EXECUTE_CUSTOMIZE_FUNC(0); // insert execute customer callback at here
		}
	}
	return checksum;
}


uint get_mem_layout_when_read_image(MEM_LAYOUT_WHEN_READ_IMAGE_T *mem_layout)
{
	if (mem_layout->image_target_addr == 0)
	{
		printf("[ERROR] mem_layout->image_target_addr = 0x%08x\n", mem_layout->image_target_addr);

		return 1;
	}

	if (mem_layout->bIsEncrypted)
	{
#ifdef CONFIG_SYS_RTK_NAND_FLASH
		mem_layout->flash_to_ram_addr = mem_layout->image_target_addr;
#else
		mem_layout->flash_to_ram_addr = mem_layout->encrpyted_addr = ENCRYPTED_FW_ADDR;
#endif
		if (mem_layout->bIsCompressed)
		{
			mem_layout->decrypted_addr = mem_layout->compressed_addr = COMPRESSED_FW_IMAGE_ADDR;
			mem_layout->decompressed_addr = mem_layout->image_target_addr;
		}
		else
		{
			mem_layout->decrypted_addr = mem_layout->image_target_addr;
		}
	}
	else
	{
		if (mem_layout->bIsCompressed)
		{
			mem_layout->flash_to_ram_addr = mem_layout->compressed_addr = COMPRESSED_FW_IMAGE_ADDR;
			mem_layout->decompressed_addr = mem_layout->image_target_addr;
		}
		else
		{
			mem_layout->flash_to_ram_addr = mem_layout->image_target_addr;
		}
	}

	return 0;
}

int decrypt_image(char *src, char *dst, uint length, uint *key)
{
	//int i;
	//uint sblock_len;
	//uchar *sblock_dst, *sblock_src;

	printf("decrypt from 0x%08lu to 0x%08lu, len:0x%08x\n", (ulong)src, (ulong)dst, length);

    if (length & 0xf) {
        printf("%s %d, fail\n", __FUNCTION__, __LINE__);
        return -1;
    }

    if (AES_ECB_decrypt((uchar *)src, length, (uchar *)dst, key)) {
		printf("%s %d, fail\n", __FUNCTION__, __LINE__);
		return -1;
	}

#if 0
	// get short block size
	sblock_len = length & 0xf;

	if (AES_CBC_decrypt((uchar *)src, length - sblock_len, (uchar *)dst, key)) {
		printf("%s %d, fail\n", __FUNCTION__, __LINE__);
		return -1;
	}


	// handle short block (<16B)
	if (sblock_len) {
		// take the last 16B of AES CBC result as input, do AES ECB encrypt
		sblock_src = (uchar *)src + (length - sblock_len);
		sblock_dst = (uchar *)dst + (length - sblock_len);
		//printf("sblock_src: 0x%p, sblock_dst: 0x%p\n", sblock_src, sblock_dst);
		if (AES_ECB_encrypt((UINT8 *)(sblock_src - 16), 16, sblock_dst, key)) {
			printf("%s %d, fail\n", __FUNCTION__, __LINE__);
			return -1;
		}

		// XOR with short block data to generate final result
		for (i = 0; i < sblock_len; i++)
			sblock_dst[i] ^= sblock_src[i];
	}
#endif

	return 0;
}

//#define DUBUG_FW_DESC_TABLE
#ifdef DUBUG_FW_DESC_TABLE
void dump_fw_desc_table_v1(fw_desc_table_v1_t *fw_desc_table_v1)
{
	if (fw_desc_table_v1 != NULL) {
		printf("## Fw Desc Table ##############################\n");
		printf("## fw_desc_table_v1                = 0x%08x\n", fw_desc_table_v1);
		printf("## fw_desc_table_v1->signature     = %s\n", fw_desc_table_v1->signature);
		printf("## fw_desc_table_v1->checksum      = 0x%08x\n", fw_desc_table_v1->checksum);
		printf("## fw_desc_table_v1->version       = 0x%08x\n", fw_desc_table_v1->version);
		printf("## fw_desc_table_v1->paddings      = 0x%08x\n", fw_desc_table_v1->paddings);
		printf("## fw_desc_table_v1->part_list_len = 0x%08x\n", fw_desc_table_v1->part_list_len);
		printf("## fw_desc_table_v1->fw_list_len   = 0x%08x\n", fw_desc_table_v1->fw_list_len);
		printf("###############################################\n\n");
	}
	else {
		printf("[ERR] %s:%d fw_desc_table_v1 is NULL.\n", __FUNCTION__, __LINE__);
	}
}

void dump_part_desc_entry_v1(part_desc_entry_v1_t *part_entry)
{
	if (part_entry != NULL) {
		printf("## Part Desc Entry ############################\n");
		printf("## part_entry                      = 0x%08x\n", part_entry);
		printf("## part_entry->type                = 0x%08x\n", part_entry->type);
		printf("## part_entry->ro                  = 0x%08x\n", part_entry->ro);
		printf("## part_entry->length              = ");
		printn(part_entry->length,16);
		printf("\n");
		printf("## part_entry->fw_count            = 0x%08x\n", part_entry->fw_count);
		printf("## part_entry->fw_type             = 0x%08x\n", part_entry->fw_type);
		printf("###############################################\n\n");
	}
	else {
		printf("[ERR] %s:%d part_entry is NULL.\n", __FUNCTION__, __LINE__);
	}
}

void dump_fw_desc_entry_v1(fw_desc_entry_v1_t *fw_entry)
{
	if (fw_entry != NULL) {
		printf("## Fw Desc Entry ##############################\n");
		printf("## fw_entry                        = 0x%08x\n", fw_entry);
		printf("## fw_entry->type                  = 0x%08x\n", fw_entry->type);
		printf("## fw_entry->lzma                  = 0x%08x\n", fw_entry->lzma);
		printf("## fw_entry->ro                    = 0x%08x\n", fw_entry->ro);
		printf("## fw_entry->version               = 0x%08x\n", fw_entry->version);
		printf("## fw_entry->target_addr           = 0x%08x\n", fw_entry->target_addr);
		printf("## fw_entry->offset                = 0x%08x\n", fw_entry->offset);
		printf("## fw_entry->length                = 0x%08x\n", fw_entry->length);
		printf("## fw_entry->paddings              = 0x%08x\n", fw_entry->paddings);
		printf("## fw_entry->checksum              = 0x%08x\n", fw_entry->checksum);
		printf("###############################################\n\n");
	}
	else {
		printf("[ERR] %s:%d fw_entry is NULL.\n", __FUNCTION__, __LINE__);
	}
}

void dump_fw_desc_entry_v2(fw_desc_entry_v2_t *fw_entry)
{
	int i;

	if (fw_entry != NULL) {
		printf("## Fw Desc Entry ##############################\n");
		printf("## fw_entry                        = 0x%08x\n", fw_entry);
		printf("## fw_entry->type                  = 0x%08x\n", fw_entry->type);
		printf("## fw_entry->lzma                  = 0x%08x\n", fw_entry->lzma);
		printf("## fw_entry->ro                    = 0x%08x\n", fw_entry->ro);
		printf("## fw_entry->version               = 0x%08x\n", fw_entry->version);
		printf("## fw_entry->target_addr           = 0x%08x\n", fw_entry->target_addr);
		printf("## fw_entry->offset                = 0x%08Lx\n", fw_entry->offset);
		printf("## fw_entry->length                = 0x%08x\n", fw_entry->length);
		printf("## fw_entry->paddings              = 0x%08x\n", fw_entry->paddings);
		printf("## fw_entry->sha_hash              = ");
		for (i = 0 ; i < 32 ; i++)
			printf("%02x", fw_entry->sha_hash[i]);
		printf("\n");
		printf("###############################################\n\n");
	}
	else {
		printf("[ERR] %s:%d fw_entry is NULL.\n", __FUNCTION__, __LINE__);
	}
}
#endif

//#define DUBUG_BOOT_AV_INFO
#ifdef DUBUG_BOOT_AV_INFO
void dump_boot_av_info(boot_av_info_t *boot_av)
{
	if (boot_av != NULL) {
		printf("\n");
		printf("## Boot AV Info (0x%08x) ##################\n", boot_av);
		printf("## boot_av->dwMagicNumber          = 0x%08x\n", boot_av->dwMagicNumber);
		printf("## boot_av->dwVideoStreamAddress   = 0x%08x\n", boot_av->dwVideoStreamAddress);
		printf("## boot_av->dwVideoStreamLength    = 0x%08x\n", boot_av->dwVideoStreamLength);
		printf("## boot_av->dwAudioStreamAddress   = 0x%08x\n", boot_av->dwAudioStreamAddress);
		printf("## boot_av->dwAudioStreamLength    = 0x%08x\n", boot_av->dwAudioStreamLength);
		printf("## boot_av->bVideoDone             = 0x%08x\n", boot_av->bVideoDone);
		printf("## boot_av->bAudioDone             = 0x%08x\n", boot_av->bAudioDone);
		printf("## boot_av->bHDMImode              = 0x%08x\n", boot_av->bHDMImode);
		printf("## boot_av->dwAudioStreamVolume    = 0x%08x\n", boot_av->dwAudioStreamVolume);
		printf("## boot_av->dwAudioStreamRepeat    = 0x%08x\n", boot_av->dwAudioStreamRepeat);
		printf("## boot_av->bPowerOnImage          = 0x%08x\n", boot_av->bPowerOnImage);
		printf("## boot_av->bRotate                = 0x%08x\n", boot_av->bRotate);
		printf("## boot_av->dwVideoStreamType      = 0x%08x\n", boot_av->dwVideoStreamType);
		printf("## boot_av->audio_buffer_addr      = 0x%08x\n", boot_av->audio_buffer_addr);
		printf("## boot_av->audio_buffer_size      = 0x%08x\n", boot_av->audio_buffer_size);
		printf("## boot_av->video_buffer_addr      = 0x%08x\n", boot_av->video_buffer_addr);
		printf("## boot_av->video_buffer_size      = 0x%08x\n", boot_av->video_buffer_size);
		printf("## boot_av->last_image_addr        = 0x%08x\n", boot_av->last_image_addr);
		printf("## boot_av->last_image_size        = 0x%08x\n", boot_av->last_image_size);
		printf("###############################################\n\n");
	}
}
#endif

static void reset_shared_memory(void)
{
	boot_av_info_t *boot_av;

	boot_av = (boot_av_info_t *) MIPS_BOOT_AV_INFO_ADDR;
	if(boot_av-> dwMagicNumber != SWAPEND32(BOOT_AV_INFO_MAGICNO))
	{
		/* clear boot_av_info memory */
		memset(boot_av, 0, sizeof(boot_av_info_t));
	}
}

/*
 * read Efuse.
 */
int rtk_get_secure_boot_type(void)
{
#ifdef CONFIG_CMD_KEY_BURNING
	if(OTP_JUDGE_BIT(OTP_BIT_SECUREBOOT))
		return RTK_SECURE_BOOT;
#endif
	//return RTK_SECURE_BOOT;
	return NONE_SECURE_BOOT;
}


/*
 * Support boot from NAND or eMMC on squashfs/ext4 partition.
 */
#ifdef NAS_ENABLE
#define NAS_ROOT "/"
#define NAS_ETC "etc"
int rtk_plat_set_boot_flag_from_part_desc(
        part_desc_entry_v1_t* part_entry, int part_count)
{
    if(boot_mode == BOOT_RESCUE_MODE || boot_mode == BOOT_GOLD_MODE)
        return RTK_PLAT_ERR_OK;

    char *device_path = NULL;
    if (BOOT_EMMC == boot_flash_type)
        device_path = "/dev/mmcblk0p";
    else if (BOOT_NAND == boot_flash_type)
        device_path = "/dev/mtdblock";
	else if (BOOT_SATA == boot_flash_type)
        device_path = "/dev/satablk0p";
	else if (BOOT_NOR_SERIAL == boot_flash_type) {
#ifdef CONFIG_BOOT_FROM_SATA
        device_path = "/dev/satablk0p";
#endif
    }

    if (!device_path)
        return RTK_PLAT_ERR_BOOT;

    char *tmp_cmdline = NULL;
    tmp_cmdline = (char*)malloc(128);
    if (!tmp_cmdline) {
        printf("%s: Malloc failed\n", __func__);
        return RTK_PLAT_ERR_BOOT;
    }
    memset(tmp_cmdline, 0, 128);

    unsigned char empty_mount[sizeof(part_entry->mount_point)];
    memset(empty_mount, 0, sizeof(empty_mount));

    int i;
    for(i = 0; i < part_count; i++) {
        if (memcmp(empty_mount, part_entry[i].mount_point, sizeof(empty_mount)) != 0) {
            if (0 == strcmp((char *)part_entry[i].mount_point, NAS_ROOT)){
                int minor_num = i;
                if (i >= 3 && BOOT_EMMC == boot_flash_type)
                    minor_num += 1;

                strcpy(tmp_cmdline, "init=/etc/init ");

                int cmd_len = strlen(tmp_cmdline);
                char *rootfstype = "";
                char *opts = "";
                switch (part_entry[i].fw_type)
                {
                    case FS_TYPE_SQUASH:
                        rootfstype = "squashfs";
                        break;
                    case FS_TYPE_EXT4:
                        rootfstype = "ext4";
                        opts = " ro";
                        break;
                    case FS_TYPE_UBIFS:
                        rootfstype = "ubifs";
                        opts = " rw ubi.mtd=/";
                        break;
                    default:
                        free(tmp_cmdline);
                        return RTK_PLAT_ERR_PARSE_FW_DESC;
                }

                if(FS_TYPE_UBIFS == part_entry[i].fw_type){
                snprintf(tmp_cmdline+cmd_len, 127-cmd_len,
                        "root=ubi0:rootfs%s rootfstype=%s ",
                        opts,rootfstype);
                }
                else{
                    snprintf(tmp_cmdline+cmd_len, 127-cmd_len,
                            "root=%s%d%s rootfstype=%s rootwait ",
                            device_path,minor_num,opts,rootfstype);
                }
                debug("NASROOT found. cmd:%s\n", tmp_cmdline);
            }
            else if (0 == strcmp((char *)part_entry[i].mount_point, NAS_ETC)
                    && FS_TYPE_UBIFS == part_entry[i].fw_type){
                int cmd_len = strlen(tmp_cmdline);
                snprintf(tmp_cmdline+cmd_len, 127-cmd_len,
                        "ubi.mtd=etc ");
                debug("NASETC found. cmd:%s\n", tmp_cmdline);
            }
        }
    }
    setenv("nas_part", tmp_cmdline);
    free(tmp_cmdline);

    return RTK_PLAT_ERR_OK;
}
#endif

/*
 * Use firmware description table to read images from usb.
 */
int rtk_plat_read_fw_image_from_USB(int skip)
{
#ifdef CONFIG_BOOT_FROM_USB
	char tmpbuf[128];
	int ret = RTK_PLAT_ERR_OK;
	char *filename;
	unsigned int secure_mode=0;

	secure_mode = rtk_get_secure_boot_type();

	run_command("usb start", 0);	/* "usb start" always return 0 */
	if (run_command("usb dev", 0) != 0) {
		printf("No USB device found!\n");
		return RTK_PLAT_ERR_READ_RESCUE_IMG;
	}

	if(!skip) /* dtb */
	{
		if(boot_mode == BOOT_RESCUE_MODE || boot_mode == BOOT_ANDROID_MODE)
			filename = rtk_plat_prepare_fw_image_from_USB(FW_TYPE_RESCUE_DT);
		else
			filename = rtk_plat_prepare_fw_image_from_USB(FW_TYPE_KERNEL_DT);
		if(secure_mode == RTK_SECURE_BOOT)
		{
			if (rtk_decrypt_rescue_from_usb(filename, getenv_ulong("fdt_loadaddr", 16, 0)))
			goto loading_failed;
		}
		else
		{
			sprintf(tmpbuf, "fatload usb 0:1 %s %s", getenv("fdt_loadaddr"), filename);
			if (run_command(tmpbuf, 0) != 0) {
				goto loading_failed;
			}
		}

		printf("Loading \"%s\" to %s is OK.\n\n", filename, getenv("fdt_loadaddr"));
	}

	/* Linux kernel */
	filename = rtk_plat_prepare_fw_image_from_USB(FW_TYPE_KERNEL);
	if(secure_mode == RTK_SECURE_BOOT)
	{
		if (rtk_decrypt_rescue_from_usb(filename,getenv_ulong("kernel_loadaddr", 16, 0)))
		goto loading_failed;
	}
	else
	{
		sprintf(tmpbuf, "fatload usb 0:1 %s %s", getenv("kernel_loadaddr"), filename);
		if (run_command(tmpbuf, 0) != 0) {
			goto loading_failed;
		}
	}

	printf("Loading \"%s\" to %s is OK.\n\n", filename, getenv("kernel_loadaddr"));

	/* rootfs */
	if(boot_mode == BOOT_RESCUE_MODE || boot_mode == BOOT_ANDROID_MODE)
		filename = rtk_plat_prepare_fw_image_from_USB(FW_TYPE_RESCUE_ROOTFS);
	else
#ifdef NAS_ENABLE
	{
		filename = "nas_uuid";
		/* Use the second partition of HDD as root partition */
		if (run_command("usb uuid 0 2", 0) != 0) {
		//setenv("nas_part", "root=/dev/sda2 rootfstype=ext4 rootwait rw ");
			printf("Failed to find NAS boot partition UUID!\n\n");
			goto loading_failed;
		}
		else{
			sprintf(tmpbuf, "root=PARTUUID=%s rootfstype=ext4 rootwait rw ", getenv("nas_boot_uuid"));
			setenv("nas_part", tmpbuf);
		}
	}
#else
		/* No initrd on NAS normal boot */
		filename = rtk_plat_prepare_fw_image_from_USB(FW_TYPE_KERNEL_ROOTFS);
#endif /* NAS_ENABLE */
#ifdef NAS_ENABLE
	if(strncmp(filename, "nas_uuid", 9))
#endif /* NAS_ENABLE */
	if(secure_mode == RTK_SECURE_BOOT)
	{
		if (rtk_decrypt_rescue_from_usb(filename, getenv_ulong("rootfs_loadaddr", 16, 0)))
		goto loading_failed;
	}
	else
	{
		sprintf(tmpbuf, "fatload usb 0:1 %s %s", getenv("rootfs_loadaddr"), filename);
		if (run_command(tmpbuf, 0) != 0) {
			goto loading_failed;
		}
	}

	printf("Loading \"%s\" to %s is OK.\n\n", filename, getenv("rootfs_loadaddr"));

	/* audio firmware */
	filename = rtk_plat_prepare_fw_image_from_USB(FW_TYPE_AUDIO);
	if(secure_mode == RTK_SECURE_BOOT)
	{
		if (!rtk_decrypt_rescue_from_usb(filename, MIPS_AUDIO_FW_ENTRY_ADDR))
		{
			printf("Loading \"%s\" to 0x%08x is OK.\n", filename, MIPS_AUDIO_FW_ENTRY_ADDR);
			run_command("go a", 0);
		}
		else
			printf("Loading \"%s\" from USB failed.\n", filename);
			/* Go on without Audio firmware. */
	}
	else
	{
		sprintf(tmpbuf, "fatload usb 0:1 0x%08x %s", MIPS_AUDIO_FW_ENTRY_ADDR, filename);
		if (run_command(tmpbuf, 0) == 0) {
			printf("Loading \"%s\" to 0x%08x is OK.\n", filename, MIPS_AUDIO_FW_ENTRY_ADDR);
			run_command("go a", 0);
		}
		else {
			printf("Loading \"%s\" from USB failed.\n", filename);
			/* Go on without Audio firmware. */
		}
    }

	//ret = rtk_call_bootm();
	ret = rtk_call_booti();
	/* Should not reach here */

	return ret;

loading_failed:
	printf("Loading \"%s\" from USB failed.\n", filename);
	return RTK_PLAT_ERR_READ_RESCUE_IMG;

#endif /* CONFIG_BOOT_FROM_USB */

	return RTK_PLAT_ERR_OK;
}


int rtk_plat_get_dtb_target_address(int dtb_address)
{
	if( (CONFIG_FDT_LOADADDR<= dtb_address) && (dtb_address < CONFIG_LOGO_LOADADDR))
		return dtb_address;
	else
		{
			printf("original DT address=%x\n",dtb_address);
			return CONFIG_FDT_LOADADDR;
		}
}

#ifdef CONFIG_PRELOAD_BOOT_IMAGES
int rtk_preload_bootimages(void)
{
	uint block_no=0, img_addr=0, img_size=0;

#if  defined(CONFIG_PRELOAD_UBOOT_EMMC_ADDR) && defined(CONFIG_RTK_MMC)
	block_no = CONFIG_PRELOAD_UBOOT_EMMC_ADDR / EMMC_BLOCK_SIZE;
	img_addr = getenv_ulong("bootcode2ndtmp_loadaddr", 16, 0);
	img_size = SZ_1M;
	printf("%s : load U-Boot 64 from 0x%08x to 0x%08x with size 0x%08x\n", __func__, block_no, img_addr, img_size);
	if(!rtk_eMMC_read(block_no, img_size, img_addr)) {
		printf("Error!!!\n");
		return RTK_PLAT_ERR_READ_FW_IMG;
	}
#endif
#if defined(CONFIG_PRELOAD_KERNEL_EMMC_ADDR) && defined(CONFIG_RTK_MMC)
	block_no = CONFIG_PRELOAD_KERNEL_EMMC_ADDR / EMMC_BLOCK_SIZE;
	img_addr = getenv_ulong("kernel_loadaddr", 16, 0);
	img_size = 7 * SZ_1M;
	printf("%s : load Kernel from 0x%08x to 0x%08x with size 0x%08x\n", __func__, block_no, img_addr, img_size);
	if(!rtk_eMMC_read(block_no, img_size, img_addr)) {
		printf("Error!!!\n");
		return RTK_PLAT_ERR_READ_FW_IMG;
	}
#endif
#if defined(CONFIG_PRELOAD_DTB_EMMC_ADDR) && defined(CONFIG_RTK_MMC)
	block_no = CONFIG_PRELOAD_DTB_EMMC_ADDR / EMMC_BLOCK_SIZE;
	img_addr = getenv_ulong("fdt_loadaddr", 16, 0);
	img_size = SZ_32K;
	printf("%s : load Kernel from 0x%08x to 0x%08x with size 0x%08x\n", __func__, block_no, img_addr, img_size);
	if(!rtk_eMMC_read(block_no, img_size, img_addr)) {
		printf("Error!!!\n");
		return RTK_PLAT_ERR_READ_FW_IMG;
	}
#endif

	return 0;
}
#endif

void GetKeyFromSRAM(unsigned int sram_addr, unsigned char* key, unsigned int length)
{
        //#define REG8( addr )		(*(volatile unsigned int*) (addr))

        int i = 0;

        for(i = 0; i < length; i++) {
            *(key + i) = REG8((uintptr_t)sram_addr + i);
        }
}

#if defined(CONFIG_SYS_RTK_EMMC_FLASH) || defined(CONFIG_SYS_RTK_NAND_FLASH)
/* Rescue-ROOTFS has different load addr for B00 compatible. */
/* B00 rescue-rootfs is preload on DDR before entering LK.   */
/* LK will then copy img from fw-tbl-addr to final addr.     */
/* Uboot for A00/01 could just load it on default address.   */
static unsigned int get_rescue_rootfs_addr(unsigned int fw_tbl_addr)
{
	unsigned int final_addr = getenv_ulong("rescue_rootfs_loadaddr", 16, 0);

	if (final_addr == 0)
		final_addr = CONFIG_RESCUE_ROOTFS_LOADADDR;

	if (fw_tbl_addr != final_addr)
		printf("change recue-rootfs addr from 0x%08x to 0x%08x\n", fw_tbl_addr, final_addr);

	return final_addr;
}
#endif

/*
 * Use firmware description table to read images from eMMC flash.
 */
int rtk_plat_read_fw_image_from_eMMC(
		uint fw_desc_table_base, part_desc_entry_v1_t* part_entry, int part_count,
		void* fw_entry, int fw_count,
		uchar version)
{
#ifdef CONFIG_SYS_RTK_EMMC_FLASH
	void *this_entry;
	fw_desc_entry_v11_t *v11_entry;
	//fw_desc_entry_v21_t *v21_entry = NULL;
	fw_desc_entry_v12_t *v12_entry;
	//fw_desc_entry_v22_t *v22_entry = NULL;
	int i, j;
	uint unit_len;
	char buf[64];
	uint fw_checksum = 0;
#if 0 // mark secure boot
	char str_phash[256];
#if defined(Config_Secure_RSA_TRUE)
	char *checksum, *signature;
#endif
	char sha1_hash[SHA1_SIZE];
	char *hash_str;
#endif
	unsigned int secure_mode;
	unsigned char ks[16],kh[16],kimg[16];
	unsigned char aes_key[16];
	unsigned char rsa_key[256];
	unsigned char sha_hash[32];
#ifdef CONFIG_CMD_KEY_BURNING
	unsigned int * Kh_key_ptr = NULL;
#else
	unsigned int * Kh_key_ptr = (unsigned int *)(uintptr_t) Kh_key_default;
#endif
	unsigned int img_truncated_size; // install_a will append 256-byte signature data to it
	int ret;
	boot_av_info_t *boot_av;
//	uint source_addr;
//	uint target_addr;
	uint block_no;
	MEM_LAYOUT_WHEN_READ_IMAGE_T mem_layout;
	uint imageSize = 0;
	uint decompressedSize = 0;

	// extern variable
	extern unsigned int mcp_dscpt_addr;
	mcp_dscpt_addr = 0;

	secure_mode = rtk_get_secure_boot_type();
	img_truncated_size = RSA_SIGNATURE_LENGTH*2+NP_INV32_LENGTH;

	unsigned char str[16];// old array size is 5, change to 16. To avoid the risk in memory overlap.

	uchar entry_type = 0;
	uchar entry_lzma = 0;
	uint entry_target_addr = 0;
	u64 entry_offset = 0;
	uint entry_length = 0;

	/* find fw_entry structure according to version */
	switch (version)
	{
		case FW_DESC_TABLE_V1_T_VERSION_1:
			unit_len = sizeof(fw_desc_entry_v1_t);
			break;

		case FW_DESC_TABLE_V1_T_VERSION_11:
			unit_len = sizeof(fw_desc_entry_v11_t);
			break;

		case FW_DESC_TABLE_V1_T_VERSION_21:
			unit_len = sizeof(fw_desc_entry_v21_t);
			break;

		case FW_DESC_TABLE_V2_T_VERSION_2:
			unit_len = sizeof(fw_desc_entry_v2_t);
			break;

		case FW_DESC_TABLE_V2_T_VERSION_12:
			unit_len = sizeof(fw_desc_entry_v12_t);
			break;

		case FW_DESC_TABLE_V2_T_VERSION_22:
			unit_len = sizeof(fw_desc_entry_v22_t);
			break;

		default:
			return RTK_PLAT_ERR_READ_FW_IMG;
	}

#if 0 // mark secure boot
#if defined(Config_Secure_RSA_TRUE)
	checksum = (char *)alloc_freemem(sizeof(v21_entry->RSA_sign));
	signature = (char *)alloc_freemem(sizeof(v21_entry->RSA_sign)+1);

	// set RSA key to env variable
	if (env_split_and_save("RSA_KEY_MODULUS", Config_Secure_RSA_MODULUS, 96) != OK)
		return NULL;
#endif


	if (secure_mode == RTK_SECURE_BOOT)
	{
		// set AES img key to env variable
		setenv( "AES_IMG_KEY", SECURE_KH_KEY_STR);
	}

	//	memset(str_phash, 0, 256);
#endif
	/* clear boot_av_info memory */
	boot_av = (boot_av_info_t *) MIPS_BOOT_AV_INFO_ADDR;
	memset(boot_av, 0, sizeof(boot_av_info_t));


	/* parse each fw_entry */
	for (i = 0; i < fw_count; i++)
	{
		EXECUTE_CUSTOMIZE_FUNC(0); // insert execute customer callback at here

		this_entry = (fw_entry + unit_len * i);
		FW_ENTRY_MEMBER_GET(entry_target_addr, this_entry, target_addr, version);
		FW_ENTRY_MEMBER_GET(entry_type, this_entry, type, version);
		FW_ENTRY_MEMBER_GET(entry_length, this_entry, length, version);
		FW_ENTRY_MEMBER_GET(entry_offset, this_entry, offset, version);
		FW_ENTRY_MEMBER_GET(entry_lzma, this_entry, lzma, version);

		if (1 == accelerate_state && entry_type != FW_TYPE_AUDIO && entry_type != FW_TYPE_IMAGE_FILE)
			continue;
		else if (2 == accelerate_state && (entry_type == FW_TYPE_AUDIO || entry_type == FW_TYPE_IMAGE_FILE))
			continue;
		/*The condition for decision the order of loading FW*/

		if (entry_target_addr)
		{
			if (boot_mode == BOOT_RESCUE_MODE || boot_mode == BOOT_ANDROID_MODE)
			{
				switch(entry_type)
				{
					case FW_TYPE_KERNEL:
						memset(str, 0, sizeof(str));
						sprintf((char *)str, "%x", entry_target_addr); /* write entry-point into string */
						setenv("kernel_loadaddr", (char *) str);
						printf("Kernel:\n");
						break;

					case FW_TYPE_RESCUE_DT:
						entry_target_addr = rtk_plat_get_dtb_target_address(entry_target_addr);
						FW_ENTRY_MEMBER_SET(entry_target_addr, this_entry, target_addr, version);
						//printf("entry_target_addr =%x\n",entry_target_addr);
						memset(str, 0, sizeof(str));
						sprintf((char *) str, "%x", entry_target_addr); /* write entry-point into string */
						setenv("fdt_loadaddr",(char *) str);
						printf("Rescue DT:\n");
						break;

					case FW_TYPE_RESCUE_ROOTFS:
						printf("Rescue ROOTFS:\n");
						if(boot_mode == BOOT_BIST_MODE)
                            entry_target_addr = BIST_ROOTFS_ADDR;
                        else
						    entry_target_addr = get_rescue_rootfs_addr(entry_target_addr);
#ifdef NAS_ENABLE
						initrd_size = entry_length;
						if(secure_mode != NONE_SECURE_BOOT)
						{
							initrd_size -= img_truncated_size;
							/* Pad 1 ~ 64 bytes by do_sha256 */
							initrd_size -= 64;
						}
#endif
						break;

					case FW_TYPE_TEE:
#ifdef CONFIG_TEE
						printf("TEE:\n");
						tee_enable=1;
						break;
#else
						continue;
#endif
					case FW_TYPE_AUDIO:
						if(boot_mode == BOOT_KERNEL_ONLY_MODE)
							continue;
						else
						{
							ipc_shm.audio_fw_entry_pt = CPU_TO_BE32(entry_target_addr | MIPS_KSEG0BASE);
							printf("Audio FW:\n");
						}
						break;
                    case FW_TYPE_IMAGE_FILE:
						printf("IMAGE FILE:\n");

						/* assign boot_av structure */
						boot_av->dwMagicNumber = SWAPEND32(BOOT_AV_INFO_MAGICNO);
						if(boot_logo_enable)
						{
							boot_av-> logo_enable = boot_logo_enable;
							boot_av-> logo_addr = CPU_TO_BE32(entry_target_addr);
							boot_av-> src_width = CPU_TO_BE32(custom_logo_src_width);
							boot_av-> src_height = CPU_TO_BE32(custom_logo_src_height);
							boot_av-> dst_width = CPU_TO_BE32(custom_logo_dst_width);
							boot_av-> dst_height = CPU_TO_BE32(custom_logo_dst_height);
						}

						break;

					default:
						//printf("Unknown FW (%d):\n", entry_type);
						continue;
				}
			}
			else if(boot_mode == BOOT_GOLD_MODE)
			{
				switch(entry_type)
				{
					case FW_TYPE_GOLD_KERNEL:
						//entry_offset=entry_offset-1; //let load gold_fw fail, and it can test enter to USB mode
						memset(str, 0, sizeof(str));
						sprintf((char *) str, "%x", entry_target_addr); /* write entry-point into string */
						setenv("kernel_loadaddr",(char *) str);
						printf("GOLD Kernel:\n");
						break;
					case FW_TYPE_GOLD_RESCUE_DT:
						entry_target_addr = rtk_plat_get_dtb_target_address(entry_target_addr);
						FW_ENTRY_MEMBER_SET(entry_target_addr, this_entry, target_addr, version);
						//printf("entry_target_addr =%x\n",entry_target_addr);
						memset(str, 0, sizeof(str));
						sprintf((char *) str, "%x", entry_target_addr); /* write entry-point into string */
						setenv("fdt_loadaddr",(char *) str);
						printf("GOLD Rescue DT:\n");
						break;
					case FW_TYPE_GOLD_RESCUE_ROOTFS:
						printf("GOLD Rescue ROOTFS:\n");
						break;
					case FW_TYPE_GOLD_AUDIO:
						if(boot_mode == BOOT_KERNEL_ONLY_MODE)
							continue;
						else
						{
							ipc_shm.audio_fw_entry_pt = CPU_TO_BE32(entry_target_addr | MIPS_KSEG0BASE);
							printf("GOLD Audio FW:\n");
						}
						break;
					default:
						//printf("Unknown FW (%d):\n", entry_type);
						continue;
				}
			}
			else
			{
				switch(entry_type)
				{
					case FW_TYPE_BOOTCODE:
						printf("Boot Code:\n");
						break;

					case FW_TYPE_KERNEL:
						//entry_offset=entry_offset-1; //let load fw fail, and it can test enter to gold mode
						memset(str, 0, sizeof(str));
						sprintf((char *) str, "%x", entry_target_addr); /* write entry-point into string */
						setenv("kernel_loadaddr",(char *) str);
						printf("Kernel:\n");
						break;

					case FW_TYPE_KERNEL_DT:
						entry_target_addr = rtk_plat_get_dtb_target_address(entry_target_addr);
						FW_ENTRY_MEMBER_SET(entry_target_addr, this_entry, target_addr, version);
						//printf("entry_target_addr =%x\n",entry_target_addr);
						memset(str, 0, sizeof(str));
						sprintf((char *) str, "%x", entry_target_addr); /* write entry-point into string */
						setenv("fdt_loadaddr",(char *) str);
						printf("DT:\n");
						break;

					case FW_TYPE_KERNEL_ROOTFS:
						printf("ROOTFS:\n");
						break;

					case FW_TYPE_TEE:
#ifdef CONFIG_TEE
						printf("TEE:\n");
						tee_enable=1;
						break;
#else
						continue;
#endif

					case FW_TYPE_AUDIO:
						if(boot_mode == BOOT_KERNEL_ONLY_MODE)
							continue;
						else
						{
							ipc_shm.audio_fw_entry_pt = CPU_TO_BE32(entry_target_addr | MIPS_KSEG0BASE);
							printf("Audio FW:\n");
						}
						break;

					case FW_TYPE_JFFS2:
						printf("JFFS2 Image:\n");
						break;

					case FW_TYPE_SQUASH:
						printf("Squash Image:\n");
						break;

					case FW_TYPE_EXT3:
						printf("EXT3 Image:\n");
						break;

					case FW_TYPE_ODD:
						printf("ODD Image:\n");
						break;

					case FW_TYPE_YAFFS2:
						printf("YAFFS2 Image:\n");
						break;

					case FW_TYPE_AUDIO_FILE:
						//entry_target_addr = (POWER_ON_MUSIC_STREAM_ADDR | MIPS_KSEG0BASE);

						/* if enable boot music, need to assign boot_av structure */
						//boot_av->dwMagicNumber = SWAPEND32(BOOT_AV_INFO_MAGICNO);
						//boot_av->dwAudioStreamAddress = SWAPEND32(entry_target_addr);
						//boot_av->dwAudioStreamLength = SWAPEND32(entry_length);
						//boot_av->dwAudioStreamVolume = (-17);
						break;

					case FW_TYPE_VIDEO_FILE:

						/* if enable boot video/jpeg, need to assign boot_av structure */
						//boot_av->dwMagicNumber = SWAPEND32(BOOT_AV_INFO_MAGICNO);
						//boot_av->dwVideoStreamAddress = SWAPEND32(entry_target_addr);
						//boot_av->bPowerOnImage = 0;
						//boot_av->dwVideoStreamLength = SWAPEND32(entry_length);
						break;

					case FW_TYPE_IMAGE_FILE:
						printf("IMAGE FILE:\n");

						/* assign boot_av structure */
						boot_av->dwMagicNumber = SWAPEND32(BOOT_AV_INFO_MAGICNO);
						if(boot_logo_enable)
						{
							boot_av-> logo_enable = boot_logo_enable;
							boot_av-> logo_addr = CPU_TO_BE32(entry_target_addr);
							boot_av-> src_width = CPU_TO_BE32(custom_logo_src_width);
							boot_av-> src_height = CPU_TO_BE32(custom_logo_src_height);
							boot_av-> dst_width = CPU_TO_BE32(custom_logo_dst_width);
							boot_av-> dst_height = CPU_TO_BE32(custom_logo_dst_height);
						}

						break;

					case FW_TYPE_UBOOT: // 2nd stage bootcode
#if defined CONFIG_SECOND_BOOTCODE_SUPPORT && defined CONFIG_GOLDENBOOT_SUPPORT
						// due to 2nd bootcode run at the same ADDR as 1st, load to other place first
						printf("Support BootCode64\n");
						continue;
						memset(str, 0, sizeof(str));
						sprintf(str, "%x", CONFIG_BOOTCODE_2ND_TMP_ADDR);
						setenv("bootcode2ndtmp_loadaddr", str);

						memset(str, 0, sizeof(str));
						sprintf(str, "%x", entry_target_addr); /* write entry-point into string */
						setenv("bootcode2nd_loadaddr", str);
						printf("2nd BootCode:\n");

						FW_ENTRY_MEMBER_SET(CONFIG_BOOTCODE_2ND_TMP_ADDR, this_entry, target_addr, version);
#else
						printf("%s, 2nd bootloader not support!\n", __func__);
#endif
						break;

					case FW_TYPE_HYP:
						memset(str, 0, sizeof(str));
						sprintf((char *) str, "%x", entry_target_addr); /* write entry-point into string */
						setenv("hyp_loadaddr",(char *) str);
						printf("Hypervisor:\n");
						break;

					default:
						//printf("Unknown FW (%d):\n", entry_type);
						continue;
				}
			}
#ifdef CONFIG_RTD1395
                       // at 1395, audio fw belong to trusted fw and need to be loaded by FSBL
                       if (entry_type == FW_TYPE_AUDIO || entry_type == FW_TYPE_GOLD_AUDIO) {
                               printf("\t FW Image preload on 0x%08x, size=0x%08x (0x%08x)\n",
                                       entry_target_addr, entry_length, entry_target_addr + entry_length);
                               continue;
                       }
#endif
#ifdef EMMC_BLOCK_LOG
			printf("\t FW Image to 0x%08x ~ 0x%08x, size=0x%08x, 0x%x blocks\n",
					entry_target_addr,
					entry_target_addr + entry_length,
					entry_length,
					(entry_length%EMMC_BLOCK_SIZE)?(entry_length/EMMC_BLOCK_SIZE)+1:(entry_length/EMMC_BLOCK_SIZE));
			printf("\t FW Image fr 0x%08Lx, blk 0x%x\n",
					(u64)(eMMC_fw_desc_table_start + entry_offset),
					(eMMC_fw_desc_table_start + entry_offset)/EMMC_BLOCK_SIZE);
#else
			printf("\t FW Image to 0x%08x, size=0x%08x (0x%08x)\n",
					entry_target_addr, entry_length, entry_target_addr + entry_length);
			printf("\t FW Image fr 0x%08Lx \n", (u64)(eMMC_fw_desc_table_start + entry_offset));
#endif

			WATCHDOG_KICK();

				/* secure mode and lzma will only apply to fw image */
				if (entry_type == FW_TYPE_KERNEL ||
					entry_type == FW_TYPE_KERNEL_ROOTFS ||
					entry_type == FW_TYPE_RESCUE_ROOTFS ||
					entry_type == FW_TYPE_AUDIO ||
					entry_type == FW_TYPE_GOLD_KERNEL ||
                    			entry_type == FW_TYPE_GOLD_RESCUE_ROOTFS ||
                    			entry_type == FW_TYPE_GOLD_AUDIO)
				{
					/* get memory layout before copy fw image */
					mem_layout.bIsEncrypted = (secure_mode != NONE_SECURE_BOOT);
					mem_layout.bIsCompressed = entry_lzma;
					mem_layout.image_target_addr = entry_target_addr & (~MIPS_KSEG_MSK);
				}
				else
				{
					/* get memory layout before copy other image */
					mem_layout.bIsEncrypted = 0;
					mem_layout.bIsCompressed = 0;
					mem_layout.image_target_addr = entry_target_addr & (~MIPS_KSEG_MSK);
				}

				get_mem_layout_when_read_image(&mem_layout);

				imageSize = entry_length;

				// 512B aligned
				if (imageSize&(EMMC_BLOCK_SIZE-1)) {
					imageSize &= ~(EMMC_BLOCK_SIZE-1);
					imageSize += EMMC_BLOCK_SIZE;
				}

				block_no = (eMMC_fw_desc_table_start + entry_offset) / EMMC_BLOCK_SIZE ;

				if (!rtk_eMMC_read(block_no, imageSize, (uint *)(uintptr_t)mem_layout.flash_to_ram_addr))
				{
					printf("[ERR] Read fw error (type:%d)!\n", entry_type);

					return RTK_PLAT_ERR_READ_FW_IMG;
				}
#ifndef BYPASS_CHECKSUM
				/* Check checksum */
				if (FW_DESC_BASE_VERSION(version) == FW_DESC_TABLE_V1_T_VERSION_1) {
					fw_checksum = get_checksum((uchar *)(uintptr_t)mem_layout.flash_to_ram_addr, entry_length);
					if (((fw_desc_entry_v1_t*)this_entry)->checksum != fw_checksum &&
						secure_mode!= RTK_SECURE_BOOT) {
						printf("\t FW Image checksum FAILED\n");
						printf("\t FW Image entry  checksum=0x%08x\n",
							((fw_desc_entry_v1_t*)this_entry)->checksum);
						printf("\t FW Image result checksum=0x%08x\n", fw_checksum);
						return RTK_PLAT_ERR_READ_FW_IMG;
					}
				} else if (FW_DESC_BASE_VERSION(version) == FW_DESC_TABLE_V2_T_VERSION_2) {
					SHA256_hash((uchar *)(uintptr_t)mem_layout.flash_to_ram_addr, entry_length, sha_hash, NULL);
					if ((memcmp(((fw_desc_entry_v2_t*)this_entry)->sha_hash, sha_hash, SHA256_SIZE) != 0) &&
						secure_mode!= RTK_SECURE_BOOT) {
						printf("\t FW Image sha FAILED\n");
						printf("\t FW Image entry sha256==>\n");
						for (j = 0 ; j < 32 ; j++)
							printf("%02x ", ((fw_desc_entry_v2_t*)this_entry)->sha_hash[j]);
						printf("\n\t FW Image result sha256==>\n");
						for (j = 0 ; j < 32 ; j++)
							printf("%02x ", sha_hash[j]);
						printf("\n");
						return RTK_PLAT_ERR_READ_FW_IMG;
					}
				}
#endif
				/* if secure mode, do AES CBC decrypt */
				if (mem_layout.bIsEncrypted)
				{
					if (secure_mode == RTK_SECURE_BOOT)
					{
					    unsigned int real_body_size = 0;
						//rtk_hexdump("the first 32-byte encrypted data", (unsigned char *)mem_layout.encrpyted_addr, 32);
						//rtk_hexdump("the last 512-byte encrypted data", (unsigned char *)(ENCRYPTED_LINUX_KERNEL_ADDR+entry_length-512), 512);

                        memset(ks,0x00,16);
                        memset(kh,0x00,16);
                        memset(kimg,0x00,16);

                        memset(aes_key, 0x00, 16);
                        memset(rsa_key, 0x00, 256);

                        switch(entry_type)
                        {
                            case FW_TYPE_KERNEL:
                            case FW_TYPE_RESCUE_ROOTFS:
                            case FW_TYPE_KERNEL_ROOTFS:
                            case FW_TYPE_AUDIO:
                            case FW_TYPE_GOLD_KERNEL:
                            case FW_TYPE_GOLD_RESCUE_ROOTFS:
                            case FW_TYPE_GOLD_AUDIO:
                                GetKeyFromSRAM(KH_P_SRAM_ADDR, aes_key, AES_KEY_SIZE);
                                GetKeyFromSRAM(RSA_KEY_FW_SRAM_ADDR, rsa_key, RSA_KEY_SIZE);
                                flush_cache((unsigned long) aes_key, AES_KEY_SIZE);
                                flush_cache((unsigned long) aes_key, RSA_KEY_SIZE);
                                sync();
                                //rtk_hexdump("kh_p : ", aes_key, AES_KEY_SIZE);
                                //rtk_hexdump("rsa_key_fw : ", rsa_key, RSA_KEY_SIZE);
                                break;
                            case FW_TYPE_TEE:
                                GetKeyFromSRAM(KX_P_SRAM_ADDR, aes_key, AES_KEY_SIZE);
                                GetKeyFromSRAM(RSA_KEY_TEE_SRAM_ADDR, rsa_key, RSA_KEY_SIZE);
                                flush_cache((unsigned long) aes_key, AES_KEY_SIZE);
                                flush_cache((unsigned long) aes_key, RSA_KEY_SIZE);
                                sync();
                                //rtk_hexdump("kx_p : ", aes_key, 16);
                                //rtk_hexdump("rsa_key_tee : ", rsa_key, RSA_KEY_SIZE);
                                break;
                            default:
                                break;
                        }

#ifdef CONFIG_CMD_KEY_BURNING
                        OTP_Get_Byte(OTP_K_S, ks, 16);
                        OTP_Get_Byte(OTP_K_H, kh, 16);
                        sync();
						flush_cache((unsigned int) (uintptr_t)ks, 16);
						flush_cache((unsigned int) (uintptr_t)kh, 16);
#endif
                        AES_ECB_encrypt(ks, 16, kimg,(unsigned int *) kh);
						flush_cache((unsigned long) kimg, 16);
                        sync();

                        Kh_key_ptr = (unsigned int *) kimg;
                        Kh_key_ptr = (unsigned int *) aes_key;
                        //Kh_key_ptr[0] = swap_endian(Kh_key_ptr[0]);
                        //Kh_key_ptr[1] = swap_endian(Kh_key_ptr[1]);
                        //Kh_key_ptr[2] = swap_endian(Kh_key_ptr[2]);
                        //Kh_key_ptr[3] = swap_endian(Kh_key_ptr[3]);
						flush_cache((unsigned long) aes_key, 16);

						// decrypt image
						printf("to decrypt...\n");

						flush_cache((unsigned int) mem_layout.encrpyted_addr, entry_length);

						if (decrypt_image((char *)(uintptr_t)mem_layout.encrpyted_addr,
							(char *)(uintptr_t)mem_layout.decrypted_addr,
							entry_length  - img_truncated_size,
							Kh_key_ptr))
						{
							printf("decrypt image(%d) error!\n", entry_type);
							return RTK_PLAT_ERR_READ_FW_IMG;
						}

						sync();
                        memset(ks,0x00,16);
                        memset(kh,0x00,16);
                        memset(kimg,0x00,16);

						//rtk_hexdump("the first 32-byte decrypted data", (unsigned char *)mem_layout.decrypted_addr, 32);

						//reverse_signature( (unsigned char *)(mem_layout.decrypted_addr + imageSize - img_truncated_size) );

                        copy_memory( (void *)(uintptr_t)(mem_layout.decrypted_addr + entry_length - img_truncated_size), (void *)(uintptr_t)(mem_layout.encrpyted_addr + entry_length - img_truncated_size), img_truncated_size);
                        flush_cache((unsigned int) mem_layout.decrypted_addr, entry_length);

                        real_body_size = (UINT32)(REG32( (uintptr_t)(mem_layout.decrypted_addr + (entry_length - img_truncated_size) - 4) ));
                        real_body_size = swap_endian(real_body_size);
                    	real_body_size /= 8;

						flush_cache((unsigned int) mem_layout.decrypted_addr, entry_length);
						ret = Verify_SHA256_hash( (unsigned char *)(uintptr_t)mem_layout.decrypted_addr,
												  real_body_size,
												  (unsigned char *)(uintptr_t)(mem_layout.decrypted_addr + entry_length - img_truncated_size),
												  1, rsa_key);
						if( ret < 0 ) {
							printf("[ERR] %s: verify hash fail(%d)\n", __FUNCTION__, ret );
							return RTK_PLAT_ERR_READ_FW_IMG;
						}

						//imageSize = imageSize - img_truncated_size - SHA256_SIZE;
					}
				}

				/* if lzma type, decompress image */
				if (mem_layout.bIsCompressed)
				{
					#ifndef CONFIG_FT_RESCUE
					if (lzmaBuffToBuffDecompress((uchar*)(uintptr_t)mem_layout.decompressed_addr, (SizeT *)&decompressedSize, (uchar*)(uintptr_t)mem_layout.compressed_addr, imageSize) != 0)
					{
						printf("[ERR] %s:Decompress using LZMA error!!\n", __FUNCTION__);

						return RTK_PLAT_ERR_READ_FW_IMG;
					}
					#endif //CONFIG_FT_RESCUE
				}
		}
	}

#ifdef NAS_ENABLE
	if(1 != accelerate_state)
		rtk_plat_set_boot_flag_from_part_desc(part_entry, part_count);
#endif

	if (accelerate_state)
		accelerate_state++;
	/*The accelerate_flag for faster blue logo*/

		if (version == FW_DESC_TABLE_V1_T_VERSION_11)
		{
			v11_entry = (fw_desc_entry_v11_t*) (fw_entry + unit_len * i);

			if (v11_entry->act_size != 0)
			{
				// string format: "part_num:act_size:hash,"
				memset(buf, 0, sizeof(buf));
				sprintf(buf, "%d:%d:", v11_entry->part_num, v11_entry->act_size);
//				strncat(str_phash, buf, strlen(buf));
				memset(buf, 0, sizeof(buf));
				memcpy(buf, v11_entry->hash, sizeof(v11_entry->hash));
				buf[sizeof(v11_entry->hash)] = ',';
//				strncat(str_phash, buf, strlen(buf));
			}
		}
		else if (version == FW_DESC_TABLE_V1_T_VERSION_21)
		{
			//v21_entry = (fw_desc_entry_v21_t *)this_entry;

#if defined(Config_Secure_RSA_TRUE)
			// exclude partition 0 (contain bootcode/kernel/audio/video image)
			if ( (v21_entry->part_num != PART_TYPE_RESERVED) &&
				(v21_entry->act_size != 0) ){
				// recover hash value from signature
				memset(checksum, 0, sizeof(v21_entry->RSA_sign));
				memset(signature, 0, sizeof(v21_entry->RSA_sign)+1);
				memcpy(signature, v21_entry->RSA_sign, sizeof(v21_entry->RSA_sign));

				rsa_verify(signature, Config_Secure_RSA_MODULUS, checksum);

				// string format: "part_num:act_size:hash,"
				memset(buf, 0, sizeof(buf));
				sprintf(buf, "%d:%d:%s,", v21_entry->part_num, v21_entry->act_size, checksum);
//				strncat(str_phash, buf, strlen(buf));
				//printf("[DEBUG_MSG] part_num:%x, act_size:%x, recovered hash:%s\n", v21_entry->part_num, v21_entry->act_size, checksum);
			}
#endif	/* defined(Config_Secure_RSA_TRUE) */
		}
		else if (version == FW_DESC_TABLE_V2_T_VERSION_12)
		{
			v12_entry = (fw_desc_entry_v12_t*) (fw_entry + unit_len * i);

			if (v12_entry->act_size != 0)
			{
				// string format: "part_num:act_size:hash,"
				memset(buf, 0, sizeof(buf));
				sprintf(buf, "%d:%d:", v12_entry->part_num, v12_entry->act_size);
//				strncat(str_phash, buf, strlen(buf));
				memset(buf, 0, sizeof(buf));
				memcpy(buf, v12_entry->hash, sizeof(v12_entry->hash));
				buf[sizeof(v12_entry->hash)] = ',';
//				strncat(str_phash, buf, strlen(buf));
			}
		}
		else if (version == FW_DESC_TABLE_V2_T_VERSION_22)
		{
			//v22_entry = (fw_desc_entry_v22_t *)this_entry;

#if defined(Config_Secure_RSA_TRUE)
			// exclude partition 0 (contain bootcode/kernel/audio/video image)
			if ( (v22_entry->part_num != PART_TYPE_RESERVED) &&
				(v22_entry->act_size != 0) ){
				// recover hash value from signature
				memset(checksum, 0, sizeof(v22_entry->RSA_sign));
				memset(signature, 0, sizeof(v22_entry->RSA_sign)+1);
				memcpy(signature, v22_entry->RSA_sign, sizeof(v22_entry->RSA_sign));

				rsa_verify(signature, Config_Secure_RSA_MODULUS, checksum);

				// string format: "part_num:act_size:hash,"
				memset(buf, 0, sizeof(buf));
				sprintf(buf, "%d:%d:%s,", v22_entry->part_num, v22_entry->act_size, checksum);
//				strncat(str_phash, buf, strlen(buf));
				//printf("[DEBUG_MSG] part_num:%x, act_size:%x, recovered hash:%s\n", v22_entry->part_num, v22_entry->act_size, checksum);
			}
#endif	/* defined(Config_Secure_RSA_TRUE) */
		}


	//printf("Many message are v21 part %d  v22 part %d \n",v21_entry->part_num,v22_entry->part_num);


	/* set boot_av_info_ptr */
	if (boot_av->dwMagicNumber == SWAPEND32(BOOT_AV_INFO_MAGICNO))
	{
		boot_av->bHDMImode = sys_logo_is_HDMI;// ignored.

		// enable audio sound
		if (boot_av->dwAudioStreamLength != 0)
		{
			;
		}

		ipc_shm.pov_boot_av_info = SWAPEND32((uint)(uintptr_t) boot_av);

		#ifdef DUBUG_BOOT_AV_INFO
		dump_boot_av_info(boot_av);
		#endif
	}

	/* Flush caches */
	flush_dcache_all();

#endif /* CONFIG_SYS_RTK_EMMC_FLASH */

	return RTK_PLAT_ERR_OK;
}


/*
 * Use firmware description table to read images from NAND flash.
 */
int rtk_plat_read_fw_image_from_NAND(
		uint fw_desc_table_base, part_desc_entry_v1_t* part_entry, int part_count,
		void* fw_entry, int fw_count,
		uchar version)
{
#ifdef CONFIG_SYS_RTK_NAND_FLASH
	int ret = RTK_PLAT_ERR_OK;
	fw_desc_entry_v1_t *this_entry;
	fw_desc_entry_v11_t *v11_entry;
	fw_desc_entry_v21_t *v21_entry;
	int i;
	int videoFileNum=0, audioFileNum=0;
	uint unit_len;
	char buf[64];
	uint fw_checksum = 0;

	unsigned int secure_mode;
	unsigned int * Kh_key_ptr = DEFAULT_KEY_PTR;
	unsigned int img_truncated_size; // install_a will append 256-byte signature data to it
	boot_av_info_t *boot_av;
	MEM_LAYOUT_WHEN_READ_IMAGE_T mem_layout;
	uint imageSize = 0;
	uint decompressedSize = 0;

	// extern variable
	extern unsigned int mcp_dscpt_addr;
	mcp_dscpt_addr = 0;

	secure_mode = rtk_get_secure_boot_type();
	img_truncated_size = RSA_SIGNATURE_LENGTH;

	struct mtd_info *mtd = &nand_info[nand_curr_device];
	size_t rwsize;
	unsigned char str[16];// old array size is 5, change to 16. To avoid the risk in memory overlap.

	/* find fw_entry structure according to version */
	switch (version)
	{
		case FW_DESC_TABLE_V1_T_VERSION_1:
			unit_len = sizeof(fw_desc_entry_v1_t);
			break;

		case FW_DESC_TABLE_V1_T_VERSION_11:
			unit_len = sizeof(fw_desc_entry_v11_t);
			break;

		case FW_DESC_TABLE_V1_T_VERSION_21:
			unit_len = sizeof(fw_desc_entry_v21_t);
			break;

		default:
			return RTK_PLAT_ERR_READ_FW_IMG;
	}

	/* clear boot_av_info memory */
	boot_av = (boot_av_info_t *) MIPS_BOOT_AV_INFO_ADDR;
	memset(boot_av, 0, sizeof(boot_av_info_t));

	/* parse each fw_entry */
	for (i = 0; i < fw_count; i++)
	{
		EXECUTE_CUSTOMIZE_FUNC(0); // insert execute customer callback at here

		this_entry = (fw_desc_entry_v1_t *)(fw_entry + unit_len * i);

		if (this_entry->target_addr)
		{
			if (boot_mode == BOOT_RESCUE_MODE || boot_mode == BOOT_ANDROID_MODE)
			{
				switch(this_entry->type)
				{
					case FW_TYPE_KERNEL:
						memset(str, 0, sizeof(str));
						sprintf(str, "%x", this_entry->target_addr); /* write entry-point into string */
						setenv("kernel_loadaddr", str);
						printf("Kernel:\n");
						break;

					case FW_TYPE_RESCUE_DT:
						this_entry->target_addr = rtk_plat_get_dtb_target_address(this_entry->target_addr);
						//printf("this_entry->target_addr =%x\n",this_entry->target_addr);
						memset(str, 0, sizeof(str));
						sprintf(str, "%x", this_entry->target_addr); /* write entry-point into string */
						setenv("fdt_loadaddr", str);
						printf("Rescue DT:\n");
						break;

					case FW_TYPE_RESCUE_ROOTFS:
						printf("Rescue ROOTFS:\n");
#ifdef NAS_ENABLE
						initrd_size = this_entry->length;
						if(secure_mode != NONE_SECURE_BOOT)
						{
							initrd_size -= img_truncated_size;
							/* Pad 1 ~ 64 bytes by do_sha256 */
							initrd_size -= 64;
						}
#endif
						break;

					case FW_TYPE_TEE:
#ifdef CONFIG_TEE
						printf("TEE:\n");
						tee_enable=1;
						break;
#else
						continue;
#endif

					case FW_TYPE_AUDIO:
						if(boot_mode == BOOT_KERNEL_ONLY_MODE)
							continue;
						else
						{
							ipc_shm.audio_fw_entry_pt = CPU_TO_BE32(this_entry->target_addr | MIPS_KSEG0BASE);
							printf("Audio FW:\n");
						}
						break;

					default:
						//printf("Unknown FW (%d):\n", this_entry->type);
						continue;
				}
			}
			else
			{
				switch(this_entry->type)
				{
					case FW_TYPE_BOOTCODE:
						printf("Boot Code:\n");
						break;

					case FW_TYPE_KERNEL:
						memset(str, 0, sizeof(str));
						sprintf(str, "%x", this_entry->target_addr); /* write entry-point into string */
						setenv("kernel_loadaddr", str);
						printf("Kernel:\n");
						break;

					case FW_TYPE_KERNEL_DT:
						this_entry->target_addr = rtk_plat_get_dtb_target_address(this_entry->target_addr);
						//printf("this_entry->target_addr =%x\n",this_entry->target_addr);
						memset(str, 0, sizeof(str));
						sprintf(str, "%x", this_entry->target_addr); /* write entry-point into string */
						setenv("fdt_loadaddr", str);
						printf("DT:\n");
						break;

					case FW_TYPE_KERNEL_ROOTFS:
						printf("ROOTFS:\n");
						break;

					case FW_TYPE_AUDIO:
						if(boot_mode == BOOT_KERNEL_ONLY_MODE)
							continue;
						else
						{
							ipc_shm.audio_fw_entry_pt = CPU_TO_BE32(this_entry->target_addr | MIPS_KSEG0BASE);
							printf("Audio FW:\n");
						}
						break;

					case FW_TYPE_TEE:
#ifdef CONFIG_TEE
						printf("TEE:\n");
						tee_enable=1;
						break;
#else
						continue;
#endif

					case FW_TYPE_JFFS2:
						printf("JFFS2 Image:\n");
						break;

					case FW_TYPE_SQUASH:
						printf("Squash Image:\n");
						break;

					case FW_TYPE_EXT3:
						printf("EXT3 Image:\n");
						break;

					case FW_TYPE_ODD:
						printf("ODD Image:\n");
						break;

					case FW_TYPE_YAFFS2:
						printf("YAFFS2 Image:\n");
						break;

					case FW_TYPE_AUDIO_FILE:
						//this_entry->target_addr = (POWER_ON_MUSIC_STREAM_ADDR | MIPS_KSEG0BASE);

						/* if enable boot music, need to assign boot_av structure */
						//boot_av->dwMagicNumber = SWAPEND32(BOOT_AV_INFO_MAGICNO);
						//boot_av->dwAudioStreamAddress = SWAPEND32(this_entry->target_addr);
						//boot_av->dwAudioStreamLength = SWAPEND32(this_entry->length);
						//boot_av->dwAudioStreamVolume = (-17);
						break;

					case FW_TYPE_VIDEO_FILE:

						/* if enable boot video/jpeg, need to assign boot_av structure */
						//boot_av->dwMagicNumber = SWAPEND32(BOOT_AV_INFO_MAGICNO);
						//boot_av->dwVideoStreamAddress = SWAPEND32(this_entry->target_addr);
						//boot_av->bPowerOnImage = 0;
						//boot_av->dwVideoStreamLength = SWAPEND32(this_entry->length);
						break;

					case FW_TYPE_IMAGE_FILE:
						printf("IMAGE FILE:\n");

						/* assign boot_av structure */
						boot_av->dwMagicNumber = SWAPEND32(BOOT_AV_INFO_MAGICNO);
						if(boot_logo_enable)
						{
							boot_av-> logo_enable = boot_logo_enable;
							boot_av-> logo_addr = CPU_TO_BE32(this_entry->target_addr);
							boot_av-> src_width = CPU_TO_BE32(custom_logo_src_width);
							boot_av-> src_height = CPU_TO_BE32(custom_logo_src_height);
							boot_av-> dst_width = CPU_TO_BE32(custom_logo_dst_width);
							boot_av-> dst_height = CPU_TO_BE32(custom_logo_dst_height);
						}

						break;

					case FW_TYPE_HYP:
						memset(str, 0, sizeof(str));
						sprintf(str, "%x", this_entry->target_addr); /* write entry-point into string */
						setenv("hyp_loadaddr", str);
						printf("Hypervisor:\n");
						break;

					default:
						//printf("Unknown FW (%d):\n", this_entry->type);
						continue;
				}
			}

			printf("\t FW Image to 0x%08x, size=0x%08x (0x%08x)\n",
				this_entry->target_addr, this_entry->length, this_entry->target_addr + this_entry->length);

			printf("\t FW Image fr 0x%08x %s\n", nand_fw_desc_table_start + this_entry->offset, this_entry->lzma ? "(lzma)" : "(non-lzma)");

			WATCHDOG_KICK();

				/* secure mode and lzma will only apply to fw image */
				if (this_entry->type == FW_TYPE_AUDIO ||
					this_entry->type == FW_TYPE_KERNEL_ROOTFS ||
					this_entry->type == FW_TYPE_KERNEL  ||
					this_entry->type == FW_TYPE_RESCUE_ROOTFS )
				{
					/* get memory layout before copy fw image */
					mem_layout.bIsEncrypted = (secure_mode != NONE_SECURE_BOOT);
					mem_layout.bIsCompressed = this_entry->lzma;
					mem_layout.image_target_addr = this_entry->target_addr & (~MIPS_KSEG_MSK);
				}
				else
				{
					/* get memory layout before copy other image */
					mem_layout.bIsEncrypted = 0;
					mem_layout.bIsCompressed = 0;
					mem_layout.image_target_addr = this_entry->target_addr & (~MIPS_KSEG_MSK);
				}

				get_mem_layout_when_read_image(&mem_layout);

				/* read image from flash */
				imageSize = this_entry->length;

				rwsize = this_entry->length;
				if (rwsize&(mtd->oobblock-1))  // page aligned
				{
					rwsize &= ~(mtd->oobblock-1);
					rwsize += mtd->oobblock;
				}

				if(mem_layout.bIsEncrypted)
					ret = nand_read_skip_bad_on_the_fly(mtd, nand_fw_desc_table_start + this_entry->offset, &rwsize, (uint *)mem_layout.flash_to_ram_addr,CP_NF_AES_CBC_128);
				else
					ret = nand_read_skip_bad(mtd, nand_fw_desc_table_start + this_entry->offset, &rwsize, (uint *)mem_layout.flash_to_ram_addr);

				if(ret){
					printf("[ERR] Read fw error (type:%d)!\n", this_entry->type);
					return RTK_PLAT_ERR_READ_FW_IMG;
				}
#ifndef BYPASS_CHECKSUM
				/* Check checksum */
				fw_checksum = get_checksum((uchar *)mem_layout.flash_to_ram_addr, this_entry->length);

				if (this_entry->checksum != fw_checksum && secure_mode!= RTK_SECURE_BOOT)
				{
					printf("\t FW Image checksum FAILED\n");
					printf("\t FW Image entry  checksum=0x%08x\n", this_entry->checksum);
					printf("\t FW Image result checksum=0x%08x\n", fw_checksum);
					return RTK_PLAT_ERR_READ_FW_IMG;
				}
#endif
				/* if secure mode, do AES CBC decrypt */
				if (mem_layout.bIsEncrypted)
				{
					if (secure_mode == RTK_SECURE_BOOT)
					{
						ret = Verify_SHA256_hash( (unsigned char *)mem_layout.flash_to_ram_addr,
												  this_entry->length - img_truncated_size,
												  (unsigned char *)(mem_layout.flash_to_ram_addr + this_entry->length - img_truncated_size),
												  1, NULL );
						if( ret < 0 ) {
							printf("[ERR] %s: verify hash fail(%d)\n", __FUNCTION__, ret );
							return RTK_PLAT_ERR_READ_FW_IMG;
						}
						//imageSize = imageSize - img_truncated_size - SHA256_SIZE;
					}
				}

				/* if lzma type, decompress image */
				if (mem_layout.bIsCompressed)
				{
					if (lzmaBuffToBuffDecompress((uchar*)mem_layout.decompressed_addr, &decompressedSize, (uchar*)mem_layout.compressed_addr, imageSize) != 0)
					{
						printf("[ERR] %s:Decompress using LZMA error!!\n", __FUNCTION__);

						return RTK_PLAT_ERR_READ_FW_IMG;
					}
				}
		}

#ifdef NAS_ENABLE
	rtk_plat_set_boot_flag_from_part_desc(part_entry, part_count);
#endif

		if (version == FW_DESC_TABLE_V1_T_VERSION_11)
		{
			v11_entry = (fw_desc_entry_v11_t*) (fw_entry + unit_len * i);

			if (v11_entry->act_size != 0)
			{
				// string format: "part_num:act_size:hash,"
				memset(buf, 0, sizeof(buf));
				sprintf(buf, "%d:%d:", v11_entry->part_num, v11_entry->act_size);
//				strncat(str_phash, buf, strlen(buf));
				memset(buf, 0, sizeof(buf));
				memcpy(buf, v11_entry->hash, sizeof(v11_entry->hash));
				buf[sizeof(v11_entry->hash)] = ',';
//				strncat(str_phash, buf, strlen(buf));
			}
		}
		else if (version == FW_DESC_TABLE_V1_T_VERSION_21)
		{
			v21_entry = (fw_desc_entry_v21_t *)this_entry;
		}
	}



	/* set boot_av_info_ptr */
	if (boot_av->dwMagicNumber == SWAPEND32(BOOT_AV_INFO_MAGICNO))
	{
		boot_av->bHDMImode = sys_logo_is_HDMI; // ignored.

		// enable audio sound
		if (boot_av->dwAudioStreamLength != 0)
		{
			printf("skip enable audio sound\n ");
		}

		ipc_shm.pov_boot_av_info = SWAPEND32((uint) boot_av);

		#ifdef DUBUG_BOOT_AV_INFO
		dump_boot_av_info(boot_av);
		#endif
	}

	/* Flush caches */
	flush_dcache_all();

#endif /* CONFIG_SYS_RTK_NAND_FLASH */

	return RTK_PLAT_ERR_OK;
}

/*
 * Use firmware description table to read images from SPI flash.
 */
int rtk_plat_read_fw_image_from_SPI(void)
{
#if defined(CONFIG_SYS_RTK_SPI_FLASH) && defined (CONFIG_DTB_IN_SPI_NOR)
	unsigned int ret;
	// load DTS
	if (boot_mode == BOOT_RESCUE_MODE || boot_mode == BOOT_ANDROID_MODE)
	{
		ret = rtkspi_load_DT_for_rescure_android(0);
		if( ret ) {
			printf("Rescue DT:\n");
			printf("          fdt addr = 0x%08x, len = 0x%08x\n", CONFIG_FDT_LOADADDR, ret);
		}
		else {
			printf("Rescue DT: not found\n");
			return RTK_PLAT_ERR_PARSE_FW_DESC;
		}
	}
	else if (boot_mode == BOOT_MANUAL_MODE || boot_mode == BOOT_NORMAL_MODE || boot_mode == BOOT_CONSOLE_MODE)
	{
		ret = rtkspi_load_DT_for_kernel(0);
		if( ret ) {
			printf("DT:\n");
			printf("          fdt addr = 0x%08x, len = 0x%08x\n", CONFIG_FDT_LOADADDR, ret);
		}
		else {
			printf("DT: not found\n");
			return RTK_PLAT_ERR_PARSE_FW_DESC;
		}
	}
	else
	{
		printf("[TODO] boot from SPI is not ready! (boot mode=%d)\n", boot_mode);
		return RTK_PLAT_ERR_PARSE_FW_DESC;
	}

#endif
	/* Start audio fw for S5 power check */
	do_go_audio_fw();

	return RTK_PLAT_ERR_OK;
}

/*
 * Use firmware description table to read images from SATAflash.
 */
int rtk_plat_read_fw_image_from_SATA(
		uint fw_desc_table_base, part_desc_entry_v1_t* part_entry, int part_count,
		void* fw_entry, int fw_count,
		uchar version)
{
#ifdef CONFIG_SYS_RTK_SATA_STORAGE
	fw_desc_entry_v1_t *this_entry;
	//fw_desc_entry_v11_t *v11_entry;
	//fw_desc_entry_v21_t *v21_entry;
	int i;
	uint unit_len;
	//char buf[64];
	uint fw_checksum = 0;
#if 0 // mark secure boot
	char str_phash[256];
#if defined(Config_Secure_RSA_TRUE)
	char *checksum, *signature;
#endif
	char sha1_hash[SHA1_SIZE];
	char *hash_str;
#endif // mark secure boot
	unsigned int secure_mode;
	unsigned char ks[16],kh[16],kimg[16];
    unsigned char aes_key[16];
    unsigned char rsa_key[256];
#ifdef CONFIG_CMD_KEY_BURNING
	unsigned int * Kh_key_ptr = NULL;
#else
	unsigned int * Kh_key_ptr = (unsigned int *)Kh_key_default;
#endif
	unsigned int img_truncated_size; // install_a will append 256-byte signature data to it
	int ret;
	boot_av_info_t *boot_av;
	uint block_no;
	MEM_LAYOUT_WHEN_READ_IMAGE_T mem_layout;
	uint imageSize = 0;
	uint imageBlkSize = 0;
	uint decompressedSize = 0;

	// extern variable
	extern unsigned int mcp_dscpt_addr;
	mcp_dscpt_addr = 0;

	secure_mode = rtk_get_secure_boot_type();
	img_truncated_size = RSA_SIGNATURE_LENGTH*2+NP_INV32_LENGTH;

	char str[16];// old array size is 5, change to 16. To avoid the risk in memory overlap.

	/* find fw_entry structure according to version */
	switch (version)
	{
		case FW_DESC_TABLE_V1_T_VERSION_1:
			unit_len = sizeof(fw_desc_entry_v1_t);
			break;

		case FW_DESC_TABLE_V1_T_VERSION_11:
			unit_len = sizeof(fw_desc_entry_v11_t);
			break;

		case FW_DESC_TABLE_V1_T_VERSION_21:
			unit_len = sizeof(fw_desc_entry_v21_t);
			break;

		default:
			return RTK_PLAT_ERR_READ_FW_IMG;
	}

#if 0 // mark secure boot
#if defined(Config_Secure_RSA_TRUE)
	checksum = (char *)alloc_freemem(sizeof(v21_entry->RSA_sign));
	signature = (char *)alloc_freemem(sizeof(v21_entry->RSA_sign)+1);

	// set RSA key to env variable
	if (env_split_and_save("RSA_KEY_MODULUS", Config_Secure_RSA_MODULUS, 96) != OK)
		return NULL;
#endif // defined(Config_Secure_RSA_TRUE)


	if (secure_mode == RTK_SECURE_BOOT)
	{
		// set AES img key to env variable
		setenv( "AES_IMG_KEY", SECURE_KH_KEY_STR);
	}

	//	memset(str_phash, 0, 256);
#endif // mark secure boot

	/* clear boot_av_info memory */
	boot_av = (boot_av_info_t *) MIPS_BOOT_AV_INFO_ADDR;
	memset(boot_av, 0, sizeof(boot_av_info_t));

	//printf("****** %s %d, boot_mode %d\n", __FUNCTION__, __LINE__, boot_mode);

	/* parse each fw_entry */
	for (i = 0; i < fw_count; i++)
	{
		EXECUTE_CUSTOMIZE_FUNC(0); // insert execute customer callback at here

		this_entry = (fw_desc_entry_v1_t *)(fw_entry + unit_len * i);

		if (this_entry->target_addr)
		{
			if (boot_mode == BOOT_RESCUE_MODE || boot_mode == BOOT_ANDROID_MODE)
			{
				//printf("****** %s %d\n", __FUNCTION__, __LINE__);
				switch(this_entry->type)
				{
					case FW_TYPE_RESCUE_KERNEL:
						memset(str, 0, sizeof(str));
						sprintf(str, "%x", this_entry->target_addr); /* write entry-point into string */
						setenv("kernel_loadaddr", str);
						printf("Rescue Kernel:\n");
						break;

					case FW_TYPE_RESCUE_DT:
						this_entry->target_addr = rtk_plat_get_dtb_target_address(this_entry->target_addr);
						memset(str, 0, sizeof(str));
						sprintf(str, "%x", this_entry->target_addr); /* write entry-point into string */
						setenv("fdt_loadaddr", str);
						printf("Rescue DT:\n");
						break;

					case FW_TYPE_RESCUE_ROOTFS:
						printf("Rescue ROOTFS:\n");
						break;

					case FW_TYPE_TEE:
#ifdef CONFIG_TEE
						printf("TEE:\n");
						tee_enable=1;
						break;
#else
						continue;
#endif
					case FW_TYPE_RESCUE_AUDIO:
						if(boot_mode == BOOT_KERNEL_ONLY_MODE)
							continue;
						else
						{
							ipc_shm.audio_fw_entry_pt = CPU_TO_BE32(this_entry->target_addr | MIPS_KSEG0BASE);
							printf("Rescue Audio FW:\n");
						}
						break;

					default:
						//printf("Unknown FW (%d):\n", this_entry->type);
						continue;
				}
			}
			else if(boot_mode == BOOT_GOLD_MODE)
            {
                //printf("****** %s %d\n", __FUNCTION__, __LINE__);
                switch(this_entry->type)
                {
                    case FW_TYPE_GOLD_KERNEL:
                        memset(str, 0, sizeof(str));
                        sprintf(str, "%x", this_entry->target_addr); /* write entry-point into string */
                        setenv("kernel_loadaddr", str);
                        printf("GOLD Kernel:\n");
                        break;
                    case FW_TYPE_GOLD_RESCUE_DT:
                        this_entry->target_addr = rtk_plat_get_dtb_target_address(this_entry->target_addr);
                        memset(str, 0, sizeof(str));
                        sprintf(str, "%x", this_entry->target_addr); /* write entry-point into string */
                        setenv("fdt_loadaddr", str);
                        printf("GOLD Rescue DT:\n");
                        break;
                    case FW_TYPE_GOLD_RESCUE_ROOTFS:
                        printf("GOLD Rescue ROOTFS:\n");
                        break;
                    case FW_TYPE_GOLD_AUDIO:
                        if(boot_mode == BOOT_KERNEL_ONLY_MODE)
                            continue;
                        else
                        {
                            ipc_shm.audio_fw_entry_pt = CPU_TO_BE32(this_entry->target_addr | MIPS_KSEG0BASE);
                            printf("GOLD Audio FW:\n");
                        }
                        break;

                    default:
                        //printf("Unknown FW (%d):\n", this_entry->type);
                        continue;
                }

            }
			else
			{
				//printf("****** %s %d, fw desc type 0x%02x\n", __FUNCTION__, __LINE__, this_entry->type);
				switch(this_entry->type)
				{
					case FW_TYPE_KERNEL:
						memset(str, 0, sizeof(str));
						sprintf(str, "%x", this_entry->target_addr); /* write entry-point into string */
						setenv("kernel_loadaddr", str);
						printf("Kernel:\n");
						break;

					case FW_TYPE_KERNEL_DT:
						this_entry->target_addr = rtk_plat_get_dtb_target_address(this_entry->target_addr);
						memset(str, 0, sizeof(str));
						sprintf(str, "%x", this_entry->target_addr); /* write entry-point into string */
						setenv("fdt_loadaddr", str);
						printf("DT:\n");
						break;

					case FW_TYPE_KERNEL_ROOTFS:
						printf("ROOTFS:\n");
						break;

					case FW_TYPE_TEE:
#ifdef CONFIG_TEE
						printf("TEE:\n");
						tee_enable=1;
						break;
#else
						continue;
#endif

					case FW_TYPE_AUDIO:
						if(boot_mode == BOOT_KERNEL_ONLY_MODE)
							continue;
						else
						{
							ipc_shm.audio_fw_entry_pt = CPU_TO_BE32(this_entry->target_addr | MIPS_KSEG0BASE);
							printf("Audio FW:\n");
						}
						break;

					case FW_TYPE_IMAGE_FILE:
						printf("IMAGE FILE:\n");
						/* assign boot_av structure */
						boot_av->dwMagicNumber = SWAPEND32(BOOT_AV_INFO_MAGICNO);
						if(boot_logo_enable)
						{
							boot_av-> logo_enable = boot_logo_enable;
							boot_av-> logo_addr = CPU_TO_BE32(this_entry->target_addr);
							boot_av-> src_width = CPU_TO_BE32(custom_logo_src_width);
							boot_av-> src_height = CPU_TO_BE32(custom_logo_src_height);
							boot_av-> dst_width = CPU_TO_BE32(custom_logo_dst_width);
							boot_av-> dst_height = CPU_TO_BE32(custom_logo_dst_height);
						}

						break;

					case FW_TYPE_UBOOT: /* 37 */ // 2nd stage bootcode
#if defined(CONFIG_SECOND_BOOTCODE_SUPPORT) && defined(CONFIG_GOLDENBOOT_SUPPORT)
						// due to 2nd bootcode run at the same ADDR as 1st, load to other place first
						printf("Support BootCode64\n");
						continue;
#endif
						break;

					case FW_TYPE_HYP: /* 39 */
						memset(str, 0, sizeof(str));
						sprintf(str, "%x", this_entry->target_addr); /* write entry-point into string */
						setenv("hyp_loadaddr", str);
						printf("Hypervisor:\n");
						break;

					default:
						//printf("Unknown FW (%d):\n", this_entry->type);
						continue;
				}
			}
			printf("\t FW Image to 0x%08x, size=0x%08x (0x%08x)\n", this_entry->target_addr, this_entry->length, this_entry->target_addr + this_entry->length);
			printf("\t FW Image fr 0x%08x \n", this_entry->offset);

			WATCHDOG_KICK();

				/* secure mode and lzma will only apply to fw image */
				if (this_entry->type == FW_TYPE_KERNEL ||
					this_entry->type == FW_TYPE_KERNEL_ROOTFS ||
					this_entry->type == FW_TYPE_RESCUE_ROOTFS ||
					this_entry->type == FW_TYPE_AUDIO )
				{
					/* get memory layout before copy fw image */
					mem_layout.bIsEncrypted = (secure_mode != NONE_SECURE_BOOT);
					mem_layout.bIsCompressed = this_entry->lzma;
					mem_layout.image_target_addr = this_entry->target_addr & (~MIPS_KSEG_MSK);
				}
				else
				{
					/* get memory layout before copy other image */
					mem_layout.bIsEncrypted = 0;
					mem_layout.bIsCompressed = 0;
					mem_layout.image_target_addr = this_entry->target_addr & (~MIPS_KSEG_MSK);
				}

				get_mem_layout_when_read_image(&mem_layout);

				// 512B aligned
				imageSize = this_entry->length + 511;
				imageSize &= (~511UL);
				imageBlkSize = imageSize / 512;

				block_no = (this_entry->offset) / 512;

				if (!rtk_sata_read(block_no, imageBlkSize, (uint *)(uintptr_t)mem_layout.flash_to_ram_addr))
				{
					printf("[ERR] Read fw error (type:%d)!\n", this_entry->type);

					return RTK_PLAT_ERR_READ_FW_IMG;
				}
#ifndef BYPASS_CHECKSUM
				/* Check checksum */
				fw_checksum = get_checksum((uchar *)(uintptr_t)mem_layout.flash_to_ram_addr, this_entry->length);

				if (this_entry->checksum != fw_checksum && secure_mode!= RTK_SECURE_BOOT)
				{
					printf("\t FW Image checksum FAILED\n");
					printf("\t FW Image entry  checksum=0x%08x\n", this_entry->checksum);
					printf("\t FW Image result checksum=0x%08x\n", fw_checksum);
					return RTK_PLAT_ERR_READ_FW_IMG;
				}
#endif
				/* if secure mode, do AES CBC decrypt */
				if (mem_layout.bIsEncrypted)
				{
					if (secure_mode == RTK_SECURE_BOOT)
					{
						unsigned int real_body_size = 0;
						//rtk_hexdump("the first 32-byte encrypted data", (unsigned char *)mem_layout.encrpyted_addr, 32);
						//rtk_hexdump("the last 512-byte encrypted data", (unsigned char *)(ENCRYPTED_LINUX_KERNEL_ADDR+this_entry->length-512), 512);

                        memset(ks,0x00,16);
                        memset(kh,0x00,16);
                        memset(kimg,0x00,16);

                        memset(aes_key, 0x00, 16);
                        memset(rsa_key, 0x00, 256);

                        switch(this_entry->type)
                        {
                            case FW_TYPE_KERNEL:
                            case FW_TYPE_RESCUE_ROOTFS:
                            case FW_TYPE_KERNEL_ROOTFS:
                            case FW_TYPE_AUDIO:
                                GetKeyFromSRAM(KH_P_SRAM_ADDR, aes_key, AES_KEY_SIZE);
                                GetKeyFromSRAM(RSA_KEY_FW_SRAM_ADDR, rsa_key, RSA_KEY_SIZE);
                                flush_cache((unsigned long) aes_key, AES_KEY_SIZE);
                                flush_cache((unsigned long) aes_key, RSA_KEY_SIZE);
                                sync();
                                //rtk_hexdump("kh_p : ", aes_key, AES_KEY_SIZE);
                                //rtk_hexdump("rsa_key_fw : ", rsa_key, RSA_KEY_SIZE);
                                break;
                            case FW_TYPE_TEE:
                                GetKeyFromSRAM(KX_P_SRAM_ADDR, aes_key, AES_KEY_SIZE);
                                GetKeyFromSRAM(RSA_KEY_TEE_SRAM_ADDR, rsa_key, RSA_KEY_SIZE);
                                flush_cache((unsigned long) aes_key, AES_KEY_SIZE);
                                flush_cache((unsigned long) aes_key, RSA_KEY_SIZE);
                                sync();
                                //rtk_hexdump("kx_p : ", aes_key, 16);
                                //rtk_hexdump("rsa_key_tee : ", rsa_key, RSA_KEY_SIZE);
                                break;
                            default:
                                break;
                        }

#ifdef CONFIG_CMD_KEY_BURNING
                        OTP_Get_Byte(OTP_K_S, ks, 16);
                        OTP_Get_Byte(OTP_K_H, kh, 16);
                        sync();
						flush_cache((unsigned int) (uintptr_t)ks, 16);
						flush_cache((unsigned int) (uintptr_t)kh, 16);
#endif
                        AES_ECB_encrypt(ks, 16, kimg,(unsigned int *) kh);
						flush_cache((unsigned long) kimg, 16);
                        sync();

                        Kh_key_ptr = (unsigned int *) kimg;
                        Kh_key_ptr = (unsigned int *) aes_key;
                        //Kh_key_ptr[0] = swap_endian(Kh_key_ptr[0]);
                        //Kh_key_ptr[1] = swap_endian(Kh_key_ptr[1]);
                        //Kh_key_ptr[2] = swap_endian(Kh_key_ptr[2]);
                        //Kh_key_ptr[3] = swap_endian(Kh_key_ptr[3]);
						flush_cache((unsigned long) aes_key, 16);

						// decrypt image
						printf("to decrypt...\n");

						flush_cache((unsigned int) mem_layout.encrpyted_addr, this_entry->length);

						if (decrypt_image((char *)(uintptr_t)mem_layout.encrpyted_addr,
							(char *)(uintptr_t)mem_layout.decrypted_addr,
							this_entry->length  - img_truncated_size,
							Kh_key_ptr))
						{
							printf("decrypt image(%d) error!\n", this_entry->type);
							return RTK_PLAT_ERR_READ_FW_IMG;
						}

						sync();
                        memset(ks,0x00,16);
                        memset(kh,0x00,16);
                        memset(kimg,0x00,16);

						//rtk_hexdump("the first 32-byte decrypted data", (unsigned char *)mem_layout.decrypted_addr, 32);

						//reverse_signature( (unsigned char *)(mem_layout.decrypted_addr + imageSize - img_truncated_size) );

                        copy_memory((void *)(uintptr_t)(mem_layout.decrypted_addr + this_entry->length - img_truncated_size), (void *)(uintptr_t)(mem_layout.encrpyted_addr + this_entry->length - img_truncated_size), img_truncated_size);
						flush_cache((unsigned int) mem_layout.decrypted_addr, this_entry->length);

                        real_body_size = (UINT32)(REG32( (uintptr_t)(mem_layout.decrypted_addr + (this_entry->length - img_truncated_size) - 4)));
                        real_body_size = swap_endian(real_body_size);
						real_body_size /= 8;

						flush_cache((unsigned int) mem_layout.decrypted_addr, this_entry->length);
						ret = Verify_SHA256_hash( (unsigned char *)(uintptr_t)mem_layout.decrypted_addr,
												  real_body_size,
												  (unsigned char *)(uintptr_t)(mem_layout.decrypted_addr + this_entry->length - img_truncated_size),
												  1, rsa_key);
						if( ret < 0 ) {
							printf("[ERR] %s: verify hash fail(%d)\n", __FUNCTION__, ret );
							return RTK_PLAT_ERR_READ_FW_IMG;
						}

						//imageSize = imageSize - img_truncated_size - SHA256_SIZE;
					}
				}

				/* if lzma type, decompress image */
				if (mem_layout.bIsCompressed)
				{
					if (lzmaBuffToBuffDecompress((uchar*)(uintptr_t)mem_layout.decompressed_addr, (SizeT *)&decompressedSize, (uchar*)(uintptr_t)mem_layout.compressed_addr, imageSize) != 0)
					{
						printf("[ERR] %s:Decompress using LZMA error!!\n", __FUNCTION__);

						return RTK_PLAT_ERR_READ_FW_IMG;
					}
				}
		}
	} // end for-loop

		if (version == FW_DESC_TABLE_V1_T_VERSION_11)
		{
			// remove unusing code
			printf("****** %s %d, not implement\n", __FUNCTION__, __LINE__);
		}
		else if (version == FW_DESC_TABLE_V1_T_VERSION_21)
		{
			// remove unusing code
			printf("****** %s %d, not implement\n", __FUNCTION__, __LINE__);
		}

	/* set boot_av_info_ptr */
	if (boot_av->dwMagicNumber == SWAPEND32(BOOT_AV_INFO_MAGICNO))
	{
		boot_av->bHDMImode = sys_logo_is_HDMI;// ignored.

		// enable audio sound
		if (boot_av->dwAudioStreamLength != 0)
		{
			;
		}

		ipc_shm.pov_boot_av_info = SWAPEND32((uint)(uintptr_t) boot_av);

		#ifdef DUBUG_BOOT_AV_INFO
		dump_boot_av_info(boot_av);
		#endif
	}

	/* Flush caches */
	flush_dcache_all();

#endif /* CONFIG_SYS_RTK_EMMC_FLASH */
	return RTK_PLAT_ERR_OK;
}


#ifdef CONFIG_POWER_DOWN_S5
int start_audio_fw(void)
{
#if defined(CONFIG_RTKSPI) && defined(CONFIG_CMD_RTKSPI)
	SizeT decompressedSize = 0x00300000;
	SizeT imageSize = CONFIG_AFW_SIZE;
        unsigned int afw_addr = CONFIG_AFW_ADDR;
        unsigned int afw_size = CONFIG_AFW_SIZE;

	rtkspi_read32(COMPRESSED_FW_IMAGE_ADDR, SPI_RBUS_BASE_ADDR+afw_addr, afw_size);
	if (lzmaBuffToBuffDecompress((uchar*)MIPS_AUDIO_FW_ENTRY_ADDR, &decompressedSize, (uchar*)COMPRESSED_FW_IMAGE_ADDR, imageSize) != 0)
	{
		printf("[ERR] %s:Decompress using LZMA error!!\n", __FUNCTION__);

		return RTK_PLAT_ERR_READ_FW_IMG;
	}
#elif defined(CONFIG_RTK_MMC)
	run_command_list("bootr f", -1, 0);
#endif

	do_go_audio_fw();
	return RTK_PLAT_ERR_OK;
}
#endif


char *rtk_plat_prepare_fw_image_from_USB(int fw_type)
{
#ifdef CONFIG_BOOT_FROM_USB
	char *filename=NULL;

	switch(fw_type)
	{
		case FW_TYPE_KERNEL: /* Linux kernel */
			filename = getenv("rescue_vmlinux");
			return (filename==NULL)?(char*) CONFIG_RESCUE_FROM_USB_VMLINUX:filename;

		case FW_TYPE_RESCUE_ROOTFS:
			filename = getenv("rescue_rootfs");
			return (filename==NULL)?(char*) CONFIG_RESCUE_FROM_USB_ROOTFS:filename;

		case FW_TYPE_KERNEL_ROOTFS:
			filename = getenv("rootfs");
			return (filename==NULL)?(char*) CONFIG_NORMAL_FROM_USB_ROOTFS:filename;

		case FW_TYPE_RESCUE_DT:
			filename = getenv("rescue_dtb");
			return (filename==NULL)?(char*) CONFIG_RESCUE_FROM_USB_DTB:filename;

		case FW_TYPE_KERNEL_DT:
			filename = getenv("dtb");
			return (filename==NULL)?(char*) CONFIG_NORMAL_FROM_USB_DTB:filename;

		case FW_TYPE_AUDIO:
			filename = getenv("rescue_audio");
			return (filename==NULL)?(char*) CONFIG_RESCUE_FROM_USB_AUDIO_CORE:filename;

		default:
			printf("Unknown FW (%d):\n", fw_type);
			return NULL;
	}
#endif
	return NULL;
}

/*
 * Parse firmware description table and read all data from eMMC flash to ram except kernel image.
 */
int rtk_plat_prepare_fw_image_from_eMMC(void)
{
	int ret = RTK_PLAT_ERR_OK;
#ifdef CONFIG_SYS_RTK_EMMC_FLASH
	fw_desc_table_v1_t fw_desc_table_v1;
	part_desc_entry_v1_t *part_entry;
	fw_desc_entry_v1_t *fw_entry, *fw_entry_v1;
	fw_desc_entry_v2_t *fw_entry_v2;
	fw_desc_entry_v11_t *fw_entry_v11;
	fw_desc_entry_v21_t *fw_entry_v21;
	fw_desc_entry_v12_t *fw_entry_v12;
	fw_desc_entry_v22_t *fw_entry_v22;
	uint part_count = 0;
	uint fw_entry_num = 0;
	uint fw_entry_size = 0;
	uchar fw_desc_version;
	uint fw_desc_table_base;
	uint fw_desc_table_blk;	// block no of firmware description table
	uint checksum;
	int i;


    if(boot_mode==BOOT_GOLD_MODE)
    {
        printf("---------------LOAD  GOLD  FW  TABLE ---------------\n");
        eMMC_fw_desc_table_start = eMMC_bootcode_area_size + CONFIG_FACTORY_SIZE + CONFIG_FW_TABLE_SIZE;
    }
    else
    {
        printf("---------------LOAD  NORMAL FW  TABLE ---------------\n");
        eMMC_fw_desc_table_start = eMMC_bootcode_area_size + CONFIG_FACTORY_SIZE;
    }
	fw_desc_table_base = FIRMWARE_DESCRIPTION_TABLE_ADDR;

	/* Firmware Description Table is right behind bootcode blocks */
	fw_desc_table_blk = eMMC_fw_desc_table_start / EMMC_BLOCK_SIZE;

	/* copy Firmware Description Table Header from flash */
	if (!rtk_eMMC_read(fw_desc_table_blk, sizeof(fw_desc_table_v1_t), (uint *)(uintptr_t)fw_desc_table_base))
	{
		printf("[ERR] %s:Read fw_desc_table_v1_t error! (0x%x, 0x%lu, 0x%x)\n",
			__FUNCTION__, fw_desc_table_blk, sizeof(fw_desc_table_v1_t), fw_desc_table_base);

		return RTK_PLAT_ERR_PARSE_FW_DESC;
	}
	else
	{
		memcpy(&fw_desc_table_v1, (void*)(uintptr_t)fw_desc_table_base, sizeof(fw_desc_table_v1_t));
	}

	/* Check signature first! */
	if (strncmp((const char *)fw_desc_table_v1.signature,
			FIRMWARE_DESCRIPTION_TABLE_SIGNATURE,
			sizeof(fw_desc_table_v1.signature)) != 0)
	{
		printf("[ERR] %s:Signature(%s) error!\n", __FUNCTION__, fw_desc_table_v1.signature);
		return RTK_PLAT_ERR_PARSE_FW_DESC;
	}

	fw_desc_table_v1.checksum = BE32_TO_CPU(fw_desc_table_v1.checksum);
	fw_desc_table_v1.paddings = BE32_TO_CPU(fw_desc_table_v1.paddings);
	fw_desc_table_v1.part_list_len = BE32_TO_CPU(fw_desc_table_v1.part_list_len);
	fw_desc_table_v1.fw_list_len = BE32_TO_CPU(fw_desc_table_v1.fw_list_len);
	// In boot32 doesn't do the Big Endian

#ifdef DUBUG_FW_DESC_TABLE
	dump_fw_desc_table_v1(&fw_desc_table_v1);
#endif

	/* copy Firmware Description/Partition/Fw_entry Tables from flash */
	if (!rtk_eMMC_read(fw_desc_table_blk, fw_desc_table_v1.paddings, (uint *)(uintptr_t)fw_desc_table_base))
	{
		printf("[ERR] %s:Read all fw tables error! (0x%x, 0x%x, 0x%x)\n",
			__FUNCTION__, fw_desc_table_blk, fw_desc_table_v1.paddings, fw_desc_table_base);

		return RTK_PLAT_ERR_PARSE_FW_DESC;
	}

	/* Check checksum */
	checksum = get_checksum((uchar*)(uintptr_t)fw_desc_table_base +
			offsetof(fw_desc_table_v1_t, version),
			sizeof(fw_desc_table_v1_t) -
			offsetof(fw_desc_table_v1_t, version) +
			fw_desc_table_v1.part_list_len +
			fw_desc_table_v1.fw_list_len);

	if (fw_desc_table_v1.checksum != checksum)
	{
		printf("[ERR] %s:Checksum not match(0x%x != 0x%x)\n", __FUNCTION__,
			fw_desc_table_v1.checksum, checksum);

		return RTK_PLAT_ERR_PARSE_FW_DESC;
	}

	/* Check partition existence */
	if (fw_desc_table_v1.part_list_len == 0)
	{
		printf("[ERR] %s:No partition found!\n", __FUNCTION__);
		//return RTK_PLAT_ERR_PARSE_FW_DESC;
	}
	else
	{
		part_count = fw_desc_table_v1.part_list_len / sizeof(part_desc_entry_v1_t);
	}

	fw_entry_num = fw_desc_table_v1.fw_list_len / sizeof(fw_desc_entry_v1_t);
	printf("[Info] fw desc table base: 0x%08x, count: %d\n", eMMC_fw_desc_table_start, fw_entry_num);

	part_entry = (part_desc_entry_v1_t *)(fw_desc_table_base + sizeof(fw_desc_table_v1_t));
	fw_entry = (fw_desc_entry_v1_t *)(fw_desc_table_base +
			sizeof(fw_desc_table_v1_t) +
			fw_desc_table_v1.part_list_len);

	for (i = 0; i < part_count; i++)
	{
		part_entry[i].length = BE32_TO_CPU(part_entry[i].length);

#ifdef DUBUG_FW_DESC_TABLE
		dump_part_desc_entry_v1(&(part_entry[i]));
#endif
	}

	/* Check partition type */
    /*  It so weired that we use part_entry for checking fw count? So we mark it
	if (part_entry[0].type != PART_TYPE_FW)
	{
		printf("[ERR] %s:No firmware partition found!\n", __FUNCTION__);

		return RTK_PLAT_ERR_PARSE_FW_DESC;
	}
*/


	fw_desc_version = fw_desc_table_v1.version;

	switch (fw_desc_version) {
		case FW_DESC_TABLE_V1_T_VERSION_1:
			fw_entry_num = fw_desc_table_v1.fw_list_len / sizeof(fw_desc_entry_v1_t);
			fw_entry_size = sizeof(fw_desc_entry_v1_t);
			break;
		case FW_DESC_TABLE_V1_T_VERSION_11:
			fw_entry_num = fw_desc_table_v1.fw_list_len / sizeof(fw_desc_entry_v11_t);
			fw_entry_size = sizeof(fw_desc_entry_v11_t);
			break;
		case FW_DESC_TABLE_V1_T_VERSION_21:
			fw_entry_num = fw_desc_table_v1.fw_list_len / sizeof(fw_desc_entry_v21_t);
			fw_entry_size = sizeof(fw_desc_entry_v21_t);
			break;
		case FW_DESC_TABLE_V2_T_VERSION_2:
			fw_entry_num = fw_desc_table_v1.fw_list_len / sizeof(fw_desc_entry_v2_t);
			fw_entry_size = sizeof(fw_desc_entry_v2_t);
			break;
		case FW_DESC_TABLE_V2_T_VERSION_12:
			fw_entry_num = fw_desc_table_v1.fw_list_len / sizeof(fw_desc_entry_v12_t);
			fw_entry_size = sizeof(fw_desc_entry_v12_t);
			break;
		case FW_DESC_TABLE_V2_T_VERSION_22:
			fw_entry_num = fw_desc_table_v1.fw_list_len / sizeof(fw_desc_entry_v22_t);
			fw_entry_size = sizeof(fw_desc_entry_v22_t);
			break;
		default:
			printf("**** Error fw_desc_version 0x%x\n", fw_desc_version);
			return RTK_PLAT_ERR_PARSE_FW_DESC;
	}

	for (i = 0 ; i < fw_entry_num ; i++) {
		uint f_version;
		uint f_target_addr;
		u64 f_offset;
		uint f_length;
		uint f_paddings;
		//uint f_checksum;
		void *fw_desc_ptr;
		//uchar sha_hash[32]; no need to swap

		fw_desc_ptr = (void*)fw_entry + (i * fw_entry_size);

		/* version */
		FW_ENTRY_MEMBER_GET(f_version, fw_desc_ptr, version, fw_desc_version);
		FW_ENTRY_MEMBER_SET(BE32_TO_CPU(f_version), fw_desc_ptr, version, fw_desc_version);
		/* target_addr */
		FW_ENTRY_MEMBER_GET(f_target_addr, fw_desc_ptr, target_addr, fw_desc_version);
		FW_ENTRY_MEMBER_SET(BE32_TO_CPU(f_target_addr), fw_desc_ptr, target_addr, fw_desc_version);
		/* target_offset */
		FW_ENTRY_MEMBER_GET(f_offset, fw_desc_ptr, offset, fw_desc_version);
		if (FW_DESC_BASE_VERSION(fw_desc_version) == 1) {
			FW_ENTRY_MEMBER_SET(BE32_TO_CPU((uint)f_offset) - eMMC_fw_desc_table_start,
				fw_desc_ptr, offset, fw_desc_version);
		} else {// Version 2
			FW_ENTRY_MEMBER_SET(BE64_TO_CPU(f_offset) - eMMC_fw_desc_table_start,
				fw_desc_ptr, offset, fw_desc_version);
		}
		/* length */
		FW_ENTRY_MEMBER_GET(f_length, fw_desc_ptr, length, fw_desc_version);
		FW_ENTRY_MEMBER_SET(BE32_TO_CPU(f_length), fw_desc_ptr, length, fw_desc_version);
		/* paddings */
		FW_ENTRY_MEMBER_GET(f_paddings, fw_desc_ptr, paddings, fw_desc_version);
		FW_ENTRY_MEMBER_SET(BE32_TO_CPU(f_paddings), fw_desc_ptr, paddings, fw_desc_version);
		/* checksum */
		if (FW_DESC_BASE_VERSION(fw_desc_version) == 1) {
			fw_entry_v1 = (fw_desc_entry_v1_t*)fw_desc_ptr;
			fw_entry_v1->checksum = BE32_TO_CPU(fw_entry_v1->checksum);

			if (fw_desc_version == FW_DESC_TABLE_V1_T_VERSION_11) {
				fw_entry_v11 = (fw_desc_entry_v11_t*)fw_desc_ptr;
				printf("[OK] fw_entry[%d] offset = 0x%x length = 0x%x (paddings = 0x%x) act_size = %d part_num = %d\n",
					i, fw_entry_v1->offset, fw_entry_v1->length, fw_entry_v1->paddings,
					fw_entry_v11[i].act_size, fw_entry_v11[i].part_num);
			} else if (fw_desc_version == FW_DESC_TABLE_V1_T_VERSION_21) {
				fw_entry_v21 = (fw_desc_entry_v21_t*)fw_desc_ptr;
				printf("[OK] fw_entry[%d] offset = 0x%x length = 0x%x (paddings = 0x%x) act_size = %d part_num = %d\n",
					i, fw_entry_v1->offset, fw_entry_v1->length, fw_entry_v1->paddings,
					fw_entry_v21[i].act_size, fw_entry_v21[i].part_num);
			}
		} else if (FW_DESC_BASE_VERSION(fw_desc_version) == 2) {
			fw_entry_v2 = (fw_desc_entry_v2_t*)fw_desc_ptr;
			if (fw_desc_version == FW_DESC_TABLE_V2_T_VERSION_12) {
				fw_entry_v12 = (fw_desc_entry_v12_t*)fw_desc_ptr;
				printf("[OK] fw_entry[%d] offset = 0x%Lx length = 0x%x (paddings = 0x%x) act_size = %d part_num = %d\n",
					i, fw_entry_v2->offset, fw_entry_v2->length, fw_entry_v2->paddings,
					fw_entry_v12[i].act_size, fw_entry_v12[i].part_num);
			} else if (fw_desc_version == FW_DESC_TABLE_V2_T_VERSION_22) {
				fw_entry_v22 = (fw_desc_entry_v22_t*)fw_desc_ptr;
				printf("[OK] fw_entry[%d] offset = 0x%Lx length = 0x%x (paddings = 0x%x) act_size = %d part_num = %d\n",
					i, fw_entry_v2->offset, fw_entry_v2->length, fw_entry_v2->paddings,
					fw_entry_v22[i].act_size, fw_entry_v22[i].part_num);
			}

		}

#ifdef DUBUG_FW_DESC_TABLE
		if (FW_DESC_BASE_VERSION(fw_desc_version) == 1)
			dump_fw_desc_entry_v1((fw_desc_entry_v1_t*)fw_desc_ptr);
		else if (FW_DESC_BASE_VERSION(fw_desc_version) == 2)
			dump_fw_desc_entry_v2((fw_desc_entry_v2_t*)fw_desc_ptr);
#endif
	}

	printf("Normal boot fw follow...\n");
	ret = rtk_plat_read_fw_image_from_eMMC(
		fw_desc_table_base, part_entry, part_count,
		fw_entry, fw_entry_num,
		fw_desc_table_v1.version);

#endif
	return ret;
}

int rtk_plat_get_fw_desc_table_start(void)
{
#ifdef CONFIG_SYS_RTK_NAND_FLASH
	struct mtd_info *mtd = &nand_info[nand_curr_device];
	int uboot_512KB = 0x80000;
#ifdef NAS_ENABLE
	int factory_8MB = CONFIG_FACTORY_SIZE;
#else
	int factory_8MB = 0x800000;
#endif
	int reservedSize;

	reservedSize = 6* mtd->erasesize;  //NF profile + BBT
	reservedSize += 1*4* mtd->erasesize; //Hw_setting*4
	reservedSize += rtd_size_aligned(uboot_512KB ,mtd->erasesize)*4;
	reservedSize += rtd_size_aligned(factory_8MB ,mtd->erasesize);

	// add extra 20% space for safety.
	reservedSize = rtd_size_aligned(reservedSize*1.2 ,mtd->erasesize);

	return reservedSize;
#endif
	return 0;
}

/*
 * Parse firmware description table and read all data from NAND flash to ram except kernel image.
 */
int rtk_plat_prepare_fw_image_from_NAND(void)
{
	int ret = RTK_PLAT_ERR_OK;
#ifdef CONFIG_SYS_RTK_NAND_FLASH
	fw_desc_table_v1_t fw_desc_table_v1;
	part_desc_entry_v1_t *part_entry;
	fw_desc_entry_v1_t *fw_entry, *fw_entry_v1;
	fw_desc_entry_v11_t *fw_entry_v11;
	fw_desc_entry_v21_t *fw_entry_v21;
	uint part_count = 0;
	uint fw_total_len;
	uint fw_total_paddings;
	uint fw_entry_num = 0;
	uint fw_desc_table_base;
	uint checksum;
	int i;
	struct mtd_info *mtd = &nand_info[nand_curr_device];
	size_t rwsize;
	unsigned char empty_mount[sizeof(part_entry->mount_point)];
	unsigned char buf[64];
	unsigned char tmp[16];
	char *tmp_cmdline = NULL;
	u64 size;

#ifdef CONFIG_PROTECTED_AREA_OLD_LAYOUT
        //protected area:512 pages*31
	nand_fw_desc_table_start = (mtd->oobblock)*512*31;
#else
	if((nand_fw_desc_table_start = rtk_plat_get_fw_desc_table_start()) == RTK_PLAT_ERR_PARSE_FW_DESC)
		return RTK_PLAT_ERR_PARSE_FW_DESC;
#endif
	debug("nand_fw_desc_table_start=0x%x\n",nand_fw_desc_table_start);
	fw_desc_table_base = FIRMWARE_DESCRIPTION_TABLE_ADDR;

	/* copy Firmware Description Table from flash */
	// Firmware Description Table is right behind bootcode blockS
	rwsize= mtd->oobblock;
	/* copy Firmware Description Table Header from flash */
	if (nand_read_skip_bad(mtd,nand_fw_desc_table_start,&rwsize, (uint *)fw_desc_table_base)!=0)
	{
		printf("[ERR] %s:Read fw_desc_table_v1_t error! (0x%x, 0x%x, 0x%x)\n",
			__FUNCTION__, nand_fw_desc_table_start, sizeof(fw_desc_table_v1_t), fw_desc_table_base);

		return RTK_PLAT_ERR_PARSE_FW_DESC;
	}
	else
	{
		memcpy(&fw_desc_table_v1, (void*)fw_desc_table_base, sizeof(fw_desc_table_v1_t));
	}


	/* Check signature first! */
	if(strncmp((const char *)fw_desc_table_v1.signature,
			FIRMWARE_DESCRIPTION_TABLE_SIGNATURE,
			sizeof(fw_desc_table_v1.signature)) != 0) {

		printf("[ERR] %s:Signature(%s) error!\n", __FUNCTION__, fw_desc_table_v1.signature);
		return RTK_PLAT_ERR_PARSE_FW_DESC;
	}

	fw_desc_table_v1.checksum = BE32_TO_CPU(fw_desc_table_v1.checksum);
	fw_desc_table_v1.paddings = BE32_TO_CPU(fw_desc_table_v1.paddings);
	fw_desc_table_v1.part_list_len = BE32_TO_CPU(fw_desc_table_v1.part_list_len);
	fw_desc_table_v1.fw_list_len = BE32_TO_CPU(fw_desc_table_v1.fw_list_len);


#ifdef DUBUG_FW_DESC_TABLE
	dump_fw_desc_table_v1(&fw_desc_table_v1);
#endif


	/* copy Firmware Description/Partition/Fw_entry Tables from flash */
	rwsize= mtd->oobblock;
	if (nand_read_skip_bad(mtd,nand_fw_desc_table_start,&rwsize, (uint *)fw_desc_table_base)!=0)
	{
		printf("[ERR] %s:Read all fw tables error! (0x%x, 0x%x, 0x%x)\n",
			__FUNCTION__, nand_fw_desc_table_start, fw_desc_table_v1.paddings, fw_desc_table_base);

		return RTK_PLAT_ERR_PARSE_FW_DESC;
	}

	/* Check checksum */
	checksum = get_checksum((uchar*)fw_desc_table_base +
			offsetof(fw_desc_table_v1_t, version),
			sizeof(fw_desc_table_v1_t) -
			offsetof(fw_desc_table_v1_t, version) +
			fw_desc_table_v1.part_list_len +
			fw_desc_table_v1.fw_list_len);

	if(fw_desc_table_v1.checksum != checksum) {
		printf("Checksum not match(0x%x != 0x%x), Entering rescue linux...\n",
			fw_desc_table_v1.checksum, checksum);

		return RTK_PLAT_ERR_PARSE_FW_DESC;

	}

	if(fw_desc_table_v1.part_list_len == 0) {
		printf("[ERR] %s:No partition found!\n", __FUNCTION__);

		return RTK_PLAT_ERR_PARSE_FW_DESC;

	} else {
		part_count = fw_desc_table_v1.part_list_len /
					sizeof(part_desc_entry_v1_t);
	}

	part_entry = (part_desc_entry_v1_t *)(fw_desc_table_base + sizeof(fw_desc_table_v1_t));
	fw_entry = (fw_desc_entry_v1_t *)(fw_desc_table_base +
			sizeof(fw_desc_table_v1_t) +
			fw_desc_table_v1.part_list_len);

	for(i = 0; i < part_count; i++) {
		part_entry[i].length = BE64_TO_CPU(part_entry[i].length);
#ifdef DUBUG_FW_DESC_TABLE
		dump_part_desc_entry_v1(&(part_entry[i]));
#endif
	}
	if(part_entry[0].type != PART_TYPE_FW) {
		printf("[ERR] %s:No firmware partition found!\n", __FUNCTION__);
		return RTK_PLAT_ERR_PARSE_FW_DESC;

	}

	fw_total_len = 0;
	fw_total_paddings = 0;

	switch (fw_desc_table_v1.version) {
		case FW_DESC_TABLE_V1_T_VERSION_1:
			for(i = 0; i < part_entry[0].fw_count; i++) {
				fw_entry[i].offset = BE32_TO_CPU(fw_entry[i].offset);
				fw_entry[i].length = BE32_TO_CPU(fw_entry[i].length);
				fw_entry[i].paddings = BE32_TO_CPU(fw_entry[i].paddings);
				//printf("[DEBUG_MSG] fw_entry[%d] offset = 0x%x length = 0x%x (paddings = 0x%x)\n",
				//		i, fw_entry[i].offset, fw_entry[i].length, fw_entry[i].paddings);
				fw_total_len += fw_entry[i].length;
				fw_total_paddings += fw_entry[i].paddings;
			}

			fw_entry_num = fw_desc_table_v1.fw_list_len / sizeof(fw_desc_entry_v1_t);
			break;

		case FW_DESC_TABLE_V1_T_VERSION_11:
			fw_entry_v11 = (fw_desc_entry_v11_t*)fw_entry;
			for(i = 0; i < part_entry[0].fw_count; i++) {
				fw_entry_v1 = &fw_entry_v11[i].v1;
				fw_entry_v1->offset = BE32_TO_CPU(fw_entry_v1->offset);
				fw_entry_v1->length = BE32_TO_CPU(fw_entry_v1->length);
				fw_entry_v1->paddings = BE32_TO_CPU(fw_entry_v1->paddings);
				printf("[DEBUG_MSG] fw_entry[%d] offset = 0x%x length = 0x%x (paddings = 0x%x) act_size = %d part_num = %d\n",
					i, fw_entry_v1->offset, fw_entry_v1->length, fw_entry_v1->paddings, fw_entry_v11[i].act_size, fw_entry_v11[i].part_num);

				fw_total_len += fw_entry_v1->length;
				fw_total_paddings += fw_entry_v1->paddings;
			}

			fw_entry_num = fw_desc_table_v1.fw_list_len / sizeof(fw_desc_entry_v11_t);
			break;

		case FW_DESC_TABLE_V1_T_VERSION_21:
				fw_entry_v21 = (fw_desc_entry_v21_t*)fw_entry;
				for(i = 0; i < part_entry[0].fw_count; i++) {
					fw_entry_v1 = &fw_entry_v21[i].v1;
					fw_entry_v1->offset = BE32_TO_CPU(fw_entry_v1->offset);
					fw_entry_v1->length = BE32_TO_CPU(fw_entry_v1->length);
					fw_entry_v1->paddings = BE32_TO_CPU(fw_entry_v1->paddings);
					printf("[DEBUG_MSG] fw_entry[%d] offset = 0x%x length = 0x%x (paddings = 0x%x) act_size = %d part_num = %d\n",
						i, fw_entry_v1->offset, fw_entry_v1->length, fw_entry_v1->paddings, fw_entry_v21[i].act_size, fw_entry_v21[i].part_num);

					fw_total_len += fw_entry_v1->length;
					fw_total_paddings += fw_entry_v1->paddings;
				}

				fw_entry_num = fw_desc_table_v1.fw_list_len / sizeof(fw_desc_entry_v21_t);
				break;

			default:
				printf("unknown version:%d\n", fw_desc_table_v1.version);

				return RTK_PLAT_ERR_PARSE_FW_DESC;

		}

		memset(empty_mount, 0, sizeof(empty_mount));
		/* convert endian? */
		for(i = 0; i < part_count; i++) {
			part_entry[i].length =BE64_TO_CPU(part_entry[i].length);
			size=(part_entry[i].length >> 10);

			memset(buf, 0, sizeof(buf));
			memset(tmp, 0, sizeof(tmp));
			sprintn(size,10,tmp);

			if (memcmp(empty_mount, part_entry[i].mount_point, sizeof(empty_mount)) != 0) {
				sprintf(buf, "%sk(%s%s",tmp, part_entry[i].mount_point,i == part_count-1? ")" :"),");
			}
			else {
				sprintf(buf, "%s%s",tmp,i == part_count-1? "k" :"k,");
			}
			//printf("buf=%s\n",buf);
			tmp_cmdline = (char *)malloc(strlen(getenv("mtd_part")) + 60);
			if (!tmp_cmdline) {
				printf("%s: Malloc failed\n", __func__);
			}
			else {
				sprintf(tmp_cmdline, "%s%s", getenv("mtd_part"),buf);
				setenv("mtd_part", tmp_cmdline);
				free(tmp_cmdline);
			}
			//printf(">%s\n",getenv("mtd_part"));
		}

		switch (fw_desc_table_v1.version) {
			case FW_DESC_TABLE_V1_T_VERSION_1:
				for(i = 0; i < part_entry[0].fw_count; i++) {
					fw_entry[i].version = BE32_TO_CPU(fw_entry[i].version);
					fw_entry[i].target_addr = BE32_TO_CPU(fw_entry[i].target_addr);
					fw_entry[i].offset =(BE32_TO_CPU(fw_entry[i].offset) - nand_fw_desc_table_start);
					fw_entry[i].length = BE32_TO_CPU(fw_entry[i].length);
					fw_entry[i].paddings = BE32_TO_CPU(fw_entry[i].paddings);
					fw_entry[i].checksum = BE32_TO_CPU(fw_entry[i].checksum);
				}
				break;

			case FW_DESC_TABLE_V1_T_VERSION_11:
				fw_entry_v11 = (fw_desc_entry_v11_t*)fw_entry;
				for(i = 0; i < part_entry[0].fw_count; i++) {
					fw_entry_v1 = &fw_entry_v11[i].v1;
					fw_entry_v1->version = BE32_TO_CPU(fw_entry_v1->version);
					fw_entry_v1->target_addr = BE32_TO_CPU(fw_entry_v1->target_addr);
					fw_entry_v1->offset = (BE32_TO_CPU(fw_entry_v1->offset) - nand_fw_desc_table_start);
					fw_entry_v1->length = BE32_TO_CPU(fw_entry_v1->length);
					fw_entry_v1->paddings = BE32_TO_CPU(fw_entry_v1->paddings);
					fw_entry_v1->checksum = BE32_TO_CPU(fw_entry_v1->checksum);
				}
				break;

			case FW_DESC_TABLE_V1_T_VERSION_21:
				fw_entry_v21 = (fw_desc_entry_v21_t*)fw_entry;
				for(i = 0; i < part_entry[0].fw_count; i++) {
					fw_entry_v1 = &fw_entry_v21[i].v1;
					fw_entry_v1->version = BE32_TO_CPU(fw_entry_v1->version);
					fw_entry_v1->target_addr = BE32_TO_CPU(fw_entry_v1->target_addr);
					fw_entry_v1->offset = (BE32_TO_CPU(fw_entry_v1->offset) - nand_fw_desc_table_start);
					fw_entry_v1->length = BE32_TO_CPU(fw_entry_v1->length);
					fw_entry_v1->paddings = BE32_TO_CPU(fw_entry_v1->paddings);
					fw_entry_v1->checksum = BE32_TO_CPU(fw_entry_v1->checksum);
				}
				break;

			default:
				printf("unknown version:%d\n", fw_desc_table_v1.version);

				return RTK_PLAT_ERR_PARSE_FW_DESC;

		}

		ret = rtk_plat_read_fw_image_from_NAND(
				fw_desc_table_base, part_entry, part_count,
				fw_entry, fw_entry_num,
				fw_desc_table_v1.version);
#endif

	return ret;
}

/*
 * Parse firmware description table and read all data from SPI flash to ram except kernel image.
 */
int rtk_plat_prepare_fw_image_from_SPI(void)
{
	int ret = RTK_PLAT_ERR_OK;

#if 0 // for nor
	/* Get flash size. */
	if((rcode = SYSCON_read(SYSCON_BOARD_MONITORFLASH_SIZE_ID,
				&flash_size, sizeof(flash_size))) != OK) {
		printf("get flash size fail!!\n");
		return NULL;
	}

	flash_end_addr = 0xbec00000 + flash_size ;

	/* SCIT signature address */
	scit_signature_addr = (void*)0xbec00000 + 0x100000 + 0x10000 - 0x100;


	memcpy(&fw_desc_table, (void*)(flash_end_addr - sizeof(fw_desc_table)), sizeof(fw_desc_table));
	fw_desc_table.checksum = BE32_TO_CPU(fw_desc_table.checksum);
	memcpy(fw_desc_entry, (void*)(flash_end_addr - sizeof(fw_desc_table) -sizeof(fw_desc_entry)),
					sizeof(fw_desc_entry));

	checksum = get_checksum((uchar*)&fw_desc_table +
			offsetof(fw_desc_table_t, version),
			sizeof(fw_desc_table_t) - offsetof(fw_desc_table_t, version));
	checksum += get_checksum((uchar*)fw_desc_entry, sizeof(fw_desc_entry));

	memcpy(signature_str_buf, fw_desc_table.signature, sizeof(fw_desc_table.signature));

	/* Check checksum and signature. */
	if(fw_desc_table.checksum != checksum ||
			strncmp(fw_desc_table.signature,
			FIRMWARE_DESCRIPTION_TABLE_SIGNATURE,
			sizeof(fw_desc_table.signature)) != 0) {
		printf("Checksum(0x%x) or signature(%s) error! Entering rescue linux...\n",
			fw_desc_table.checksum, signature_str_buf);
#if defined(Rescue_Source_USB) && defined(Board_USB_Driver_Enabled)
		return run_rescue_from_usb(RESCUE_LINUX_FILE_NAME);
#elif defined(Rescue_Source_FLASH)
#if defined(Logo_Source_FLASH)
#if defined(Logo6_Source_FLASH)
		LOGO_DISP_change(5);
#endif
#endif
		return run_rescue_from_flash();
#else
		return NULL;
#endif /* defined(Rescue_Source_USB) && defined(Board_USB_Driver_Enabled) */
	}


	if(strncmp((char*)scit_signature_addr, VERONA_SCIT_SIGNATURE_STRING,
			strlen(VERONA_SCIT_SIGNATURE_STRING)) != 0) {
		printf("Can not find signature string, \"%s\"! Entering rescue linux...\n",
			VERONA_SCIT_SIGNATURE_STRING);
#if defined(Rescue_Source_USB) && defined(Board_USB_Driver_Enabled)
		return run_rescue_from_usb(rescue_file);
#elif defined(Rescue_Source_FLASH)
#if defined(Logo_Source_FLASH)
#if defined(Logo6_Source_FLASH)
		LOGO_DISP_change(5);
#endif
#endif
		return run_rescue_from_flash();
#else
		return NULL;
#endif /* defined(Rescue_Source_USB) && defined(Board_USB_Driver_Enabled) */
	}

	fw_desc_table.length = BE32_TO_CPU(fw_desc_table.length);

	for(i = 0; i < (int)ARRAY_COUNT(fw_desc_entry); i++) {
		fw_desc_entry[i].version =
			BE32_TO_CPU(fw_desc_entry[i].version);
		fw_desc_entry[i].target_addr =
			BE32_TO_CPU(fw_desc_entry[i].target_addr);
		fw_desc_entry[i].offset = BE32_TO_CPU(fw_desc_entry[i].offset);
		fw_desc_entry[i].length = BE32_TO_CPU(fw_desc_entry[i].length);
		fw_desc_entry[i].paddings = BE32_TO_CPU(fw_desc_entry[i].paddings);
		fw_desc_entry[i].checksum = BE32_TO_CPU(fw_desc_entry[i].checksum);
	}

	return run_kernel_from_flash(0x9ec00000, flash_size,
			fw_desc_entry, ARRAY_COUNT(fw_desc_entry));
#endif

	ret = rtk_plat_read_fw_image_from_SPI();

	return ret;
}

/*
 * Parse firmware description table and read all data from SATA to ram except kernel image.
 */
int rtk_plat_prepare_fw_image_from_SATA(void)
{
	int ret = RTK_PLAT_ERR_OK;
#ifdef CONFIG_SYS_RTK_SATA_STORAGE
	fw_desc_table_v1_t fw_desc_table_v1;
	part_desc_entry_v1_t *part_entry;
	fw_desc_entry_v1_t *fw_entry;
	//fw_desc_entry_v1_t *fw_entry_v1;
	//fw_desc_entry_v11_t *fw_entry_v11;
	//fw_desc_entry_v21_t *fw_entry_v21;
	uint part_count = 0;
	uint fw_total_len;
	uint fw_total_paddings;
	uint fw_entry_num = 0;
	uint fw_desc_table_base;
	uint fw_desc_table_blk;	// block no of firmware description table
	uint checksum;
	int i;
	char cmdline[512];
	char wd_sn[64];
	char wd_part_sel[8];
	char *psn;

	if (sata_curr_device == -1) {
		if (sata_initialize()) {
			printf("---------------SATA init fail, try again ---------------\n");
			if (sata_initialize()) {
				printf("---------------No SATA device ---------------\n");
				return RTK_PLAT_ERR_BOOT;
			}
		}
	}

    if(boot_mode==BOOT_GOLD_MODE)
    {
        printf("---------------LOAD  GOLD  FW  TABLE (%d) ---------------\n", boot_mode);
    }
    else if(boot_mode==BOOT_RESCUE_MODE)
    {
        printf("---------------LOAD  RESCUE FW  TABLE (%d) ---------------\n", boot_mode);
    }
    else if(boot_mode==BOOT_ANDROID_MODE)
    {
        printf("---------------LOAD  NORMAL FW  TABLE(%d) ---------------\n", boot_mode);
    }
    else
    {
        printf("---------------LOAD  NORMAL FW  TABLE(%d) ---------------\n", boot_mode);
    }

    sata_fw_desc_table_start = 0x4400;
	fw_desc_table_base = FIRMWARE_DESCRIPTION_TABLE_ADDR; /* 0x06400000 */

	/* Firmware Description Table is right behind bootcode blocks */
	fw_desc_table_blk = sata_fw_desc_table_start / 512;

	/* copy Firmware Description Table Header from flash */
	if (!rtk_sata_read(fw_desc_table_blk, sizeof(fw_desc_table_v1_t), (uint *)(uintptr_t)fw_desc_table_base))
	{
		printf("[ERR] %s:Read fw_desc_table_v1_t error! (0x%x, 0x%x, 0x%x)\n",
			__FUNCTION__, (unsigned int)fw_desc_table_blk, (unsigned int)sizeof(fw_desc_table_v1_t), (unsigned int)fw_desc_table_base);

		return RTK_PLAT_ERR_PARSE_FW_DESC;
	}
	else
	{
		memcpy(&fw_desc_table_v1, (void*)(uintptr_t)fw_desc_table_base, sizeof(fw_desc_table_v1_t));
	}

	/* Check signature first! */
	if (strncmp((const char *)fw_desc_table_v1.signature,
			FIRMWARE_DESCRIPTION_TABLE_SIGNATURE,
			sizeof(fw_desc_table_v1.signature)) != 0)
	{
		printf("[ERR] %s:Signature(%s) error!\n", __FUNCTION__, fw_desc_table_v1.signature);
		return RTK_PLAT_ERR_PARSE_FW_DESC;
	}

	fw_desc_table_v1.checksum = BE32_TO_CPU(fw_desc_table_v1.checksum);
	fw_desc_table_v1.paddings = BE32_TO_CPU(fw_desc_table_v1.paddings);
	fw_desc_table_v1.part_list_len = BE32_TO_CPU(fw_desc_table_v1.part_list_len);
	fw_desc_table_v1.fw_list_len = BE32_TO_CPU(fw_desc_table_v1.fw_list_len);

#ifdef DUBUG_FW_DESC_TABLE
	dump_fw_desc_table_v1(&fw_desc_table_v1);
#endif

	/* copy Firmware Description/Partition/Fw_entry Tables from flash */
	if (!rtk_sata_read(fw_desc_table_blk, fw_desc_table_v1.paddings, (uint *)(uintptr_t)fw_desc_table_base))
	{
		printf("[ERR] %s:Read all fw tables error! (0x%x, 0x%x, 0x%x)\n",
			__FUNCTION__, fw_desc_table_blk, fw_desc_table_v1.paddings, fw_desc_table_base);

		return RTK_PLAT_ERR_PARSE_FW_DESC;
	}

	/* Check checksum */
	checksum = get_checksum((uchar*)(uintptr_t)fw_desc_table_base +
			offsetof(fw_desc_table_v1_t, version),
			sizeof(fw_desc_table_v1_t) -
			offsetof(fw_desc_table_v1_t, version) +
			fw_desc_table_v1.part_list_len +
			fw_desc_table_v1.fw_list_len);

	if (fw_desc_table_v1.checksum != checksum)
	{
		printf("[ERR] %s:Checksum not match(0x%x != 0x%x)\n", __FUNCTION__,
			fw_desc_table_v1.checksum, checksum);

		return RTK_PLAT_ERR_PARSE_FW_DESC;
	}

	/* Check partition existence */
	if (fw_desc_table_v1.part_list_len == 0)
	{
		printf("[ERR] %s:No partition found!\n", __FUNCTION__);
		//return RTK_PLAT_ERR_PARSE_FW_DESC;
	}
	else
	{
		part_count = fw_desc_table_v1.part_list_len / sizeof(part_desc_entry_v1_t);
	}

	fw_entry_num = fw_desc_table_v1.fw_list_len / sizeof(fw_desc_entry_v1_t);
	printf("[Info] fw desc table base: 0x%08x, count: %d\n", sata_fw_desc_table_start, fw_entry_num);

	part_entry = (part_desc_entry_v1_t *)(fw_desc_table_base + sizeof(fw_desc_table_v1_t));
	fw_entry = (fw_desc_entry_v1_t *)(fw_desc_table_base +
			sizeof(fw_desc_table_v1_t) +
			fw_desc_table_v1.part_list_len);

	for (i = 0; i < part_count; i++)
	{
		part_entry[i].length = BE32_TO_CPU(part_entry[i].length);

#ifdef DUBUG_FW_DESC_TABLE
		dump_part_desc_entry_v1(&(part_entry[i]));
#endif
	}

	/* Check partition type */
    /*  It so weired that we use part_entry for checking fw count? So we mark it
	if (part_entry[0].type != PART_TYPE_FW)
	{
		printf("[ERR] %s:No firmware partition found!\n", __FUNCTION__);

		return RTK_PLAT_ERR_PARSE_FW_DESC;
	}
    */
	fw_total_len = 0;
	fw_total_paddings = 0;

	/* Parse firmware entries and compute fw_total_len */
	switch (fw_desc_table_v1.version)
	{
		case FW_DESC_TABLE_V1_T_VERSION_1:
			fw_entry_num = fw_desc_table_v1.fw_list_len / sizeof(fw_desc_entry_v1_t);

			for (i = 0; i < fw_entry_num; i++)
			{
				fw_entry[i].version     = BE32_TO_CPU(fw_entry[i].version);
				fw_entry[i].target_addr = BE32_TO_CPU(fw_entry[i].target_addr);
				fw_entry[i].offset      = BE32_TO_CPU(fw_entry[i].offset);
				fw_entry[i].length      = BE32_TO_CPU(fw_entry[i].length);
				fw_entry[i].paddings    = BE32_TO_CPU(fw_entry[i].paddings);
				fw_entry[i].checksum    = BE32_TO_CPU(fw_entry[i].checksum);

#ifdef DUBUG_FW_DESC_TABLE
				dump_fw_desc_entry_v1(&(fw_entry[i]));
#endif

				fw_total_len += fw_entry[i].length;
				fw_total_paddings += fw_entry[i].paddings;
			}


			break;

		case FW_DESC_TABLE_V1_T_VERSION_11:
			// remove unusing code
			printf("****** %s %d, not implement\n", __FUNCTION__, __LINE__);
			break;

		case FW_DESC_TABLE_V1_T_VERSION_21:
			// remove unusing code
			printf("****** %s %d, not implement\n", __FUNCTION__, __LINE__);
			break;

		default:
			printf("[ERR] %s:unknown version:%d\n", __FUNCTION__, fw_desc_table_v1.version);
			return RTK_PLAT_ERR_PARSE_FW_DESC;
	}

	if(sata_boot_debug) {
		return RTK_PLAT_ERR_PARSE_FW_DESC;
	}

	printf("Start loading fw (mode %d)...\n", boot_mode);

	ret = rtk_plat_read_fw_image_from_SATA(
		fw_desc_table_base, part_entry, part_count,
		fw_entry, fw_entry_num,
		fw_desc_table_v1.version);


#ifdef CONFIG_WD_AB
	if ( (psn = getenv("serial")) == NULL )
		strcpy(wd_sn,DEFAULT_SN);
	else
		strcpy(wd_sn,psn);

	// Rivers: overwrite bootarg for loading A/B partition
	// set bootarg using setenv
	if( (boot_mode == BOOT_NORMAL_MODE) || (boot_mode == BOOT_RESCUE_MODE) ) {
		memset(wd_part_sel, 0, sizeof(wd_part_sel));
		if(boot_mode == BOOT_NORMAL_MODE) {
			printf("Setting bootargs to " VT100_LIGHT_RED "A" VT100_NONE "\n");
			memcpy(wd_part_sel, cSATA_PART_A, sizeof(cSATA_PART_A));
		}
		else {
			printf("Setting bootargs to " VT100_LIGHT_RED "B" VT100_NONE "\n");
			memcpy(wd_part_sel, cSATA_PART_B, sizeof(cSATA_PART_B));
		}
#ifdef CONFIG_ANDORIDBOOT_HARDWARE_NAME
		DDDDYELLOW("[Info] androidboot.hardware=%s\n",CONFIG_ANDORIDBOOT_HARDWARE_NAME);
#else
		DDDDYELLOW("[Info] use default androidboot.hardware=%s\n",DEFAULT_ANDORIDBOOT_HARDWARE_NAME);
#endif
		snprintf(cmdline, sizeof(cmdline),
			"earlycon=uart8250,mmio32,0x98007800 console=ttyS0,115200 init=/init "
			"androidboot.hardware=%s "
			"androidboot.heapgrowthlimit=128m "
			"androidboot.heapsize=192m androidboot.storage=%s "
			"loglevel=4 androidboot.selinux=permissive ver=%s "
			"sn=%s",
#ifdef CONFIG_ANDORIDBOOT_HARDWARE_NAME
			CONFIG_ANDORIDBOOT_HARDWARE_NAME,
#else
			DEFAULT_ANDORIDBOOT_HARDWARE_NAME,
#endif
			wd_part_sel,
			version_string,
			wd_sn);
		setenv("bootargs", cmdline);
	}
	else if(boot_mode == BOOT_GOLD_MODE){
		printf("Booting golden image, use default bootarg\n");
	}else{
		printf("[ERROR]: Unknouwn boot_mode\n");
	}
#endif /* CONFIG_WD_AB */

#endif // CONFIG_SYS_RTK_SATA_STORAGE

	return ret;
}

//#define DEBUG_SKIP_BOOT_ALL
//#define DEBUG_SKIP_BOOT_LINUX
//#define DEBUG_SKIP_BOOT_AV

#if (defined(CONFIG_RTD1195) || defined(CONFIG_RTD1295)) && defined(NAS_ENABLE)
extern int rtk_plat_boot_prep_nas_partition(void);
#endif

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
#ifdef CONFIG_NAS_ENABLE
	void *fdt_addr = (void*)simple_strtoul(booti_argv[3], NULL, 16);

	int nodeoffset;
	struct fdt_property *prop;
	int err, oldlen, newlen;
	char *str = NULL;

	if(!fdt_check_header(fdt_addr)) {
		nodeoffset = fdt_find_or_add_subnode(fdt_addr, 0, "chosen");
		if(nodeoffset >= 0){
			prop = fdt_get_property_w(fdt_addr, nodeoffset, "bootargs", &oldlen);
			if (prop) {
				newlen = oldlen+8+strlen(PLAIN_VERSION)+2+strlen(U_BOOT_DATE)+3+strlen(U_BOOT_TIME)+1+1;
				str = (char *)malloc(newlen);
				if (str) {
					memset(str, 0, newlen);
					memcpy(str, prop->data, oldlen);
					sprintf(str+oldlen-1, " U-boot=%s (%s - %s)",
						PLAIN_VERSION, U_BOOT_DATE, U_BOOT_TIME);
				}
				err = fdt_setprop_string(fdt_addr, nodeoffset, "bootargs", str);
				if (err < 0) {
					printf("WARNING: could not set version in bootargs %s.\n",
					       fdt_strerror(err));
				}
				if (str)
					free(str);
			}

		}
	}
#endif

	/*
	 * - do the work -
	 * exec subcommands of do_booti to init the images
	 * data structure
	 */
	debug("booti_argv ={ ");
	for (j = 0; j < argc; j++)
			debug("%s,",booti_argv[j]);
	debug("}\n");

#if (defined(CONFIG_RTD1195) || defined(CONFIG_RTD1295)) && defined(NAS_ENABLE)
	rtk_plat_boot_prep_nas_partition();
#endif

#ifdef CONFIG_CMD_RTKFDT
	extern void rtkfdt_add_factory(void);
    DDDDYELLOW("[Info] convert some env variable to fdt:factory node\n");
	rtkfdt_add_factory();
#endif

	ret = do_booti(find_cmd("do_booti"), 0, argc, booti_argv);

	if (ret) {
		printf("ERROR do_booti failed!\n");
		return -1;
	}

	return 1;
}

/* Calls bootm with the parameters given */
#if 0
static int rtk_call_bootm(void)
{
	char *bootm_argv[] = { "bootm", NULL, "-", NULL, NULL };
	int ret = 0;
	int j;
	int argc=4;


	if ((bootm_argv[1] = getenv("kernel_loadaddr")) == NULL) {
		bootm_argv[1] =(char*) CONFIG_KERNEL_LOADADDR;
	}

	if ((bootm_argv[3] = getenv("fdt_loadaddr")) == NULL) {
		bootm_argv[3] =(char*) CONFIG_FDT_LOADADDR;
	}

	/*
	 * - do the work -
	 * exec subcommands of do_bootm to init the images
	 * data structure
	 */
	debug("bootm_argv ={ ");
	for (j = 0; j < argc; j++)
			debug("%s,",bootm_argv[j]);
	debug("}\n");

#if 0//def CONFIG_SECOND_BOOTCODE_SUPPORT && CONFIG_RTD1295
#if (defined(CONFIG_RTD1195) || defined(CONFIG_RTD1295)) && defined(NAS_ENABLE)
	rtk_plat_boot_prep_nas_partition();
#endif
	run_command_list("b2ndbc", -1, 0);
#else

	ret = do_bootm(find_cmd("do_bootm"), 0, argc,bootm_argv);

#endif


	if (ret) {
		printf("ERROR do_bootm failed!\n");
		return -1;
	}

	return 1;
}
#endif

int rtk_plat_set_fw(void)
{
	int ret = RTK_PLAT_ERR_OK;
	//char cmd[16];
	int magic = SWAPEND32(0x16803001);
	int offset = SWAPEND32(MIPS_SHARED_MEMORY_ENTRY_ADDR);

	printf("Start Boot Setup ... ");

	/* reset some shared memory */
	reset_shared_memory();

#ifdef DEBUG_SKIP_BOOT_ALL // Skip by CK
	printf("(CK skip)\n");
	return RTK_PLAT_ERR_PARSE_FW_DESC;
#else
	printf("\n");
#endif
	if (boot_from_usb != BOOT_FROM_USB_DISABLE) // workaround path that read fw img from usb
	{
		ret = rtk_plat_read_fw_image_from_USB(0);
	}
	else
	{
		/* parse fw_desc_table, and read all data from flash to ram except kernel image */
		if (boot_flash_type == BOOT_EMMC)
		{
			/* For eMMC */
			ret = rtk_plat_prepare_fw_image_from_eMMC();
		}
		else if (boot_flash_type == BOOT_SATA)
		{
			/* For SATA */
			ret = rtk_plat_prepare_fw_image_from_SATA();
		}
		else if (boot_flash_type == BOOT_NAND)
		{
			/* For NAND */
			ret = rtk_plat_prepare_fw_image_from_NAND();
		}
		else
		{
#ifdef CONFIG_BOOT_FROM_SATA
			ret = rtk_plat_prepare_fw_image_from_SATA();
#else
			/* For SPI */
			ret = rtk_plat_prepare_fw_image_from_SPI();
#ifdef CONFIG_BOOT_FROM_USB
			if(ret == RTK_PLAT_ERR_OK)
				ret = rtk_plat_read_fw_image_from_USB(0);
#endif /* CONFIG_BOOT_FROM_USB */
#endif /* CONFIG_BOOT_FROM_SATA */
		}
	}

#if CONFIG_ANDROID_RECOVERY
    /* factory save ---------work space----------------*/
    //gen recovery signature(update.zip from backup partition).
    if((ret == RTK_PLAT_ERR_OK) && (boot_mode == BOOT_GOLD_MODE))
    {
        printf("------------recovery write start--------------\n");

        /* write in emmc */
        bootloader_message *boot=(bootloader_message *)BACKUP_DESCRIPTION_RECOVERY_ADDR;
        memset(boot, 0, sizeof(bootloader_message));
        memset(boot->command, '\0', sizeof(boot->command));
        memset(boot->recovery, '\0', sizeof(boot->recovery));
        sprintf(boot->command, "boot-recovery");
        sprintf(boot->recovery, "recovery\n--update_package=BACKUP:update.zip\n--locale=en_GB");

#ifdef CONFIG_SYS_FACTORY
    	ret = factory_write(RECOVERY_FILE_IN_FACTORY, (char *)boot, CONFIG_RECOVERY_SIZE);
		if (ret != 0)
        {
            // failed case
    		printf("[ENV] write_recovery failed\n");
    	}
    	else
		    factory_save();
#else
	    printf("[ENV][WARN] CONFIG_SYS_FACTORY is not defined.\n");
#endif
        printf("------------recovery write end--------------\n");
        ret = RTK_PLAT_ERR_OK;
    }
#endif
#ifndef DEBUG_SKIP_BOOT_AV // mark for boot linux kernel only
	if (boot_from_flash == BOOT_FROM_FLASH_NORMAL_MODE)
	{
		if (ret == RTK_PLAT_ERR_OK)
		if(!accelerate_state)
		{
			/* Enable ACPU */
			if (ipc_shm.audio_fw_entry_pt != 0){
				printf("Start A/V Firmware ...\n");
				memcpy((unsigned char *)(MIPS_SHARED_MEMORY_ENTRY_ADDR+0xC4), &ipc_shm, sizeof(ipc_shm));
				memcpy((unsigned char *)(MIPS_SHARED_MEMORY_ENTRY_ADDR), &magic, sizeof(magic));
				memcpy((unsigned char *)(MIPS_SHARED_MEMORY_ENTRY_ADDR +4), &offset, sizeof(offset));
				flush_dcache_all();
				rtd_setbits(CLOCK_ENABLE2_reg,_BIT4);
#ifdef CONFIG_WAIT_AFW_1_SECOND
				mdelay(1000);
#endif
			}
		}
	}
	else
	{
		printf("[Skip A] boot manual mode\n");
	}
#endif

	return ret;
}

static void gmt_g2227_set_mode(void)
{
#ifdef CONFIG_GMT_G2227

#ifdef CONFIG_BOOT_DCDC1_FORCE_PWM
      run_command("pmic set dcdc1_mode force_pwm", 0);
#endif

#ifdef CONFIG_BOOT_DCDC2_FORCE_PWM
	run_command("pmic set dcdc2_mode force_pwm", 0);
#endif

#ifdef CONFIG_BOOT_DCDC3_FORCE_PWM
	run_command("pmic set dcdc3_mode force_pwm", 0);
#endif

#ifdef CONFIG_BOOT_DCDC4_FORCE_PWM
	run_command("pmic set dcdc4_mode force_pwm", 0);
#endif

#ifdef CONFIG_BOOT_DCDC5_FORCE_PWM
	run_command("pmic set dcdc5_mode force_pwm", 0);
#endif

#ifdef CONFIG_BOOT_DCDC6_FORCE_PWM
	run_command("pmic set dcdc6_mode force_pwm", 0);
#endif

#endif /* CONFIG_GMT_G2227 */
}



//all standard boot_cmd entry.
int rtk_plat_do_boot_linux(void)
{
	gmt_g2227_set_mode();

	//rtk_call_bootm();
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
#ifdef CONFIG_CUSTOMIZE_BOOTFLOW_1
extern int normal_boot;
#endif
int  rtk_plat_boot_handler(void)
{
	int ret = RTK_PLAT_ERR_OK;

	/* copy audio/video firmware and stream files from flash to ram */
	ret = rtk_plat_set_fw();

	if (ret == RTK_PLAT_ERR_OK)
	{
#ifndef DEBUG_SKIP_BOOT_LINUX
		if (boot_from_flash == BOOT_FROM_FLASH_NORMAL_MODE)
		{
			/* go Linux */
#ifdef CONFIG_REALTEK_WATCHDOG
			WATCHDOG_KICK();
#else
			WATCHDOG_DISABLE();
#endif

			EXECUTE_CUSTOMIZE_FUNC(1); // insert execute customer callback at here

#ifdef CONFIG_CUSTOMIZE_BOOTFLOW_1
			if (normal_boot)
				ret = rtk_plat_do_boot_linux ();
			else
				printf("Skip Normal BOOT flow\n");
#else
			ret = rtk_plat_do_boot_linux ();
#endif

		}
		else
		{
			printf("[Skip K] boot manual mode (execute \"go all\")\n");
		}
#endif
	}

	return ret;
}

#ifdef CONFIG_MODULE_TEST
void rtk_plat_do_bootr_after_mt()
{
	int ret = RTK_PLAT_ERR_OK;

	/* reset boot flags */
	boot_from_flash = BOOT_FROM_FLASH_NORMAL_MODE;
	boot_from_usb = BOOT_FROM_USB_DISABLE;

	WATCHDOG_KICK();
	ret = rtk_plat_boot_handler();
#if 0
    if (ret != RTK_PLAT_ERR_OK) {
        /*   LOAD GOLD FW   */
        ret = RTK_PLAT_ERR_OK;
        boot_mode=BOOT_GOLD_MODE;
        ret = rtk_plat_boot_handler();
    }
#endif
	return;
}
#endif /* CONFIG_MODULE_TEST */

#ifdef UBOOT_PINGPONG_NEW_DESIGN

static inline int is_digit(const char c)
{
	return ( c >= '0' && c <= '9');
}

// constuct the string and write back to config
static int wd_write_boot_config(const struct boot_config *pbcf)
{

	char tmpbuf[128];
	unsigned int addr = 0x04000000;
	char writeBuf[10];
	char str_bstate[2] = {0 ,'\0'};
	char str_nbr[2] = {0 ,'\0'};
	char str_bna[2] = {0 ,'\0'};

	memset(writeBuf, 0, sizeof(writeBuf));
	sprintf(writeBuf, "%d:%c:%d:;",
		pbcf->bState,
		pbcf->nextBootRegion,
		pbcf->numBootAttempts);

	memcpy((u_char *)(ulong)addr, writeBuf, sizeof(writeBuf));

#if defined (CONFIG_BOARD_WD_MONARCH)
	sprintf(tmpbuf, "fatwrite sata 0:12 0x%x %s 10", addr, BOOT_CONFIG_FILE_NAME);
#elif defined(CONFIG_BOARD_WD_PELICAN)
	sprintf(tmpbuf, "fatwrite mmc 0:1 0x%x %s 10", addr, BOOT_CONFIG_FILE_NAME);
#endif
	if (run_command(tmpbuf, 0) != 0) {
		printf("%s: File %s does not exist, run \"wdpp set\" command manually\n",
               __func__, BOOT_CONFIG_FILE_NAME);
		return -1;
	}

	printf("\n[Info]: write boot config %s\n", writeBuf);
	// pass to kernel /proc/device-tree/factory but not saving in flash
	str_bstate[0] = pbcf->bState + 48;
	str_bna[0] = pbcf->numBootAttempts + 48;
	str_nbr[0] = gBootConfig.nextBootRegion;
	setenv("bootstate", str_bstate);
	setenv("bna", str_bna);
	setenv("nbr", str_nbr);

	return 0;
}

//
// Function to read the boot config parameter from config partition
// Return NULL if failed
//
static int wd_read_boot_config(void)
{
	char cmdBuf[128];
	unsigned int addr = 0x04000000;
	char readBuf[10];
	char str_bstate[2] = {0 ,'\0'};
	char str_nbr[2] = {0 ,'\0'};
	char str_bna[2] = {0 ,'\0'};

	memset(cmdBuf, 0, sizeof(cmdBuf));
	memset(readBuf, 0, sizeof(readBuf));

#if defined(CONFIG_BOARD_WD_MONARCH)
	sprintf(cmdBuf, "fatload sata 0:12 0x%x %s 10", addr, BOOT_CONFIG_FILE_NAME);
#elif defined (CONFIG_BOARD_WD_PELICAN)
	sprintf(cmdBuf, "fatload mmc 0:1 0x%x %s 10", addr, BOOT_CONFIG_FILE_NAME);
#endif

	if (run_command(cmdBuf, 0) != 0) {
		printf("%s: Error, File %s does not exist, exit\n",
		__func__, BOOT_CONFIG_FILE_NAME);
		return -1;
	}

	// get the string
	memcpy(readBuf, (u_char *)(ulong)addr, sizeof(readBuf));

	DDDDYELLOW("[Info] %s: %s\n", BOOT_CONFIG_FILE_NAME, readBuf);

	// now parsing the string
	char *p = readBuf;
	char *p1 = readBuf;

	BOOT_CFG_STR_T s = BOOT_CFG_STR_STATE;
	// memset((u_char *)gBootConfig, 0, sizeof(gBootConfig));

	while(p && *p != ';' && *p != '\0') {
		if (*p ==':') {
			switch(s) {
			case BOOT_CFG_STR_STATE:
				if (is_digit(*p1)) {
					gBootConfig.bState = (BOOT_STATE_T)(*p1 - '0');
				}else {
					printf("%s: Error, invalid boot state. \n", __func__);
					return -1;
				}
				s = BOOT_CFG_STR_NBR;
				break;
			case BOOT_CFG_STR_NBR:
				if (*p1 != 'A' || *p1 != 'B') {
					gBootConfig.nextBootRegion = *p1;
					s = BOOT_CFG_STR_BNA;
				}else {
					printf("%s: Error, invalid NBR = %c\n",__func__, *p1);
					return -1;
				}
				break;
			case BOOT_CFG_STR_BNA:
				if (is_digit(*p1)) {
					gBootConfig.numBootAttempts = (int)(*p1 - '0');
				}else {
					printf("%s: Error, invalid bna.\n", __func__);
					return -1;
				}
				s = BOOT_CFG_STR_DONE;
				break;
			case BOOT_CFG_STR_DONE:
			default:
				break;
			}
		}
		if(p == p1) {
			p++;
		}else {
			p++;
			p1++;
		}
	}

	if (s != BOOT_CFG_STR_DONE) {
		return -1;
	}else {
		debug("bstate = %d, bna = %d, nbr = %c\n",
			gBootConfig.bState, gBootConfig.numBootAttempts,
			gBootConfig.nextBootRegion);

		// pass to kernel /proc/device-tree/factory but not saving in flash
		// 48 => ASCII character '0'
		// 65 => ASCII character 'A'
		str_bstate[0] = gBootConfig.bState + 48;
		str_bna[0] = gBootConfig.numBootAttempts + 48;
		str_nbr[0] = gBootConfig.nextBootRegion;
		setenv("bootstate", str_bstate);
		setenv("bna", str_bna);
		setenv("nbr", str_nbr);
	}

	return 0;
}

//
// Switch boot region via changing the boot_mode
static int wd_boot_cbr(void)
{
	char *cbr = NULL;
	cbr = getenv("cbr");
	if(cbr != NULL)	{
		if( strncmp(cbr, "A", 1 ) == 0 ){
		// set the boot_mode
			boot_mode = BOOT_NORMAL_MODE;		// A image
		} else if( strncmp(cbr, "B", 1 ) == 0 )	{
			boot_mode = BOOT_RESCUE_MODE;		// B image
		}else {
			printf("[FATAL ERROR] Invalid CBR(%s) from uboot env, boot USB rescue mode.", cbr);
			gUSB_MODE = 1;
			return -1;
		}
	}else {	//unknown cbr
		printf("[FATAL ERROR] CBR not found, boot USB rescue mode.\n");
		gUSB_MODE = 1;
		return -1;
	}

	return 0;
}

//
// Boot from NBR
//
static int wd_boot_nbr(void)
{
	if(gBootConfig.nextBootRegion == 'A'){
		boot_mode = BOOT_NORMAL_MODE;		// A image
	}else if(gBootConfig.nextBootRegion == 'B'){
		boot_mode = BOOT_RESCUE_MODE;		// B image
	}else{	//unknown nbr
		printf("[FATAL ERROR] Invalid nbr(%c) from CONFIG, boot CBR\n", gBootConfig.nextBootRegion);
		return wd_boot_cbr();
	}

	return 0;
}

//
static int update_cbr_from_nbr(void)
{
    char nbr[2] = { 0 ,'\0'};

    // update the cbr with valid nbr only
    if (gBootConfig.nextBootRegion == 'A' ||
        gBootConfig.nextBootRegion == 'B') {
        nbr[0] = gBootConfig.nextBootRegion;
        setenv("cbr", nbr);
		if (run_command("env save", 0) != 0) {
		    printf("Failed to write cbr to uboot env, exit\n");
		    return -1;
		}
    }else return -1;

    return 0;
}

#endif /* UBOOT_PINGPONG_NEW_DESIGN */

int rtk_plat_do_bootr(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	int ret = RTK_PLAT_ERR_OK;

    // flag that indicate if we need to update the boot config
    int updateBootConfig = 0;

	// make sure the HDD is ready
	if (!is_sata_initialized()) {
		// sata is not initialized, fail
		// FIXME! how to handle this case?
		// switch to USB boot?
		return -1;
	}

    // reading the gpt partition to make sure the
    // partition table is current, otherwise, regenerates
    // the partition table then reboot
#if defined (CONFIG_BOARD_WD_MONARCH)
    char *gpt_ver = getenv("gpt_ver");
    int ngpt_ver = gpt_ver ? simple_strtoul (gpt_ver, NULL, 10) : 0;
    printf("[Info] getting gpt_ver env and gpt version = %d\n", ngpt_ver);
    char gpt_ver_str[8];
    if (ngpt_ver < CURRENT_GPT_VER) {
        printf("[Info] Current gpt (%d) is not out of date. need to update to %d\n",
               ngpt_ver, CURRENT_GPT_VER);
        // generating GPU
        run_command("rtkgpt gen V3", 0);
        sprintf(gpt_ver_str, "%d", CURRENT_GPT_VER);
        setenv("gpt_ver", gpt_ver_str);
        run_command("env save", 0);
    }
#endif /* CONFIG_BOARD_WD_MONARCH */

#ifdef UBOOT_PINGPONG_NEW_DESIGN

	int bna = -1;

	BOOT_STATE_T bootState = BOOT_STATE_UNKNOWN;

    // always read the bootconfig from config partition
    //
	if (wd_read_boot_config() == 0) {
        bootState = gBootConfig.bState;
    }// else: if reading the config failed, the bootState is not changed, then boot CBR

	switch (bootState){
    case BOOT_STATE_NO_OTA:  // no OTA boot state is clean
		printf("\n[Info]: bootState: BOOT_STATE_NO_OTA\n");
        // nothing should have changed. No need to update
        // config partition
		wd_boot_cbr();
		break;
    case BOOT_STATE_INIT:
		// initial state (USB Installer will set to this state)
		printf("\n[Info]: bootState: BOOT_STATE_INIT\n");
		printf("[Info]: Re-initialize uboot env entries\n");
		setenv("cbr", "A");
		if (run_command("env save", 0) != 0) {
		    printf("Failed to initialize uboot env entries, exit\n");
		    return -1;
		}

		boot_mode = BOOT_NORMAL_MODE;

		// set bootState to BOOT_STATE_NO_OTA in CONFIG
		// why need to write the boot state back to config???
		//
        gBootConfig.bState = BOOT_STATE_NO_OTA;
        // write a invalid nbr here, to make sure next OTA has the right value
        // written to it
        gBootConfig.nextBootRegion = 'F';
        updateBootConfig = 1;
		break;
    case BOOT_STATE_OTA_TRIGGERED:
		bna = gBootConfig.numBootAttempts;
		printf("\n[Info]: bootState: BOOT_STATE_OTA_TRIGGERED, bna = %d\n", bna);
		if((bna > 0) && (bna <= 5)) {		//boot NBR for evaluation
		    printf("[Info]: boot nbr for evaluation\n");
		    wd_boot_nbr();
		}else{
            // this is the case wheren bna == 0 or bna > 5
            // in either case, we fall back to CBR, but need to reset the boot state as well,
            // so to allow OTA happen.
		    printf("[ERROR]: Failed to get Boot Next Attempt(%d), boot CBR\n", bna);
            gBootConfig.bState = BOOT_STATE_NO_OTA;
            // write a invalid nbr here, to make sure next OTA has the right value
            // written to it
            gBootConfig.nextBootRegion = 'F';
            updateBootConfig = 1;
		    wd_boot_cbr();
		}
		break;
    case BOOT_STATE_OTA_PASSED:
		printf("\n[Info]: OTA passed, boot NBR and update CBR\n");
        // Ok, the last nbr boot is sucessful, update the cbr
        if (update_cbr_from_nbr() == -1) {
            printf("[ERR]: %s return failure.\n", __func__);
        }
        //
        // Set bootState to BOOT_STATE_NO_OTA for next boot
        //
        gBootConfig.bState = BOOT_STATE_NO_OTA;
        // write a invalid nbr here, to make sure next OTA has the right value
        // written to it
        gBootConfig.nextBootRegion = 'F';
        updateBootConfig = 1;
		wd_boot_cbr();
		break;
    case BOOT_STATE_OTA_FAILED:	//boot CBR regardless of CONFIG
		printf("\n[Info]: OTA failed, boot CBR\n");
        gBootConfig.bState = BOOT_STATE_NO_OTA;
        // write a invalid nbr here, to make sure next OTA has the right value
        // written to it
        gBootConfig.nextBootRegion = 'F';
        updateBootConfig = 1;
		wd_boot_cbr();
		break;
   case BOOT_STATE_RECOVERY:
       printf("\n[Info]: Boot golden image\n");
       boot_mode = BOOT_GOLD_MODE;
       // The boot parameter is changed to following after factory reset in the recovery image:
       // 1. BOOT_STATE_RECOVERY -> BOOT_STATE_NO_OTA
       // 2. nbr set to 'F'
       // 3. bna set to 0
       // once the factory reset task is finished, reboot the device, since the cbr is not changed,
       // and boot state is BOOT_STATE_RECOVERY, the device should boot with cbr directly
	break;

    default:
		printf("\n[ERROR]: Unknown bootState(%d), boot CBR\n", bootState);
		wd_boot_cbr();
        gBootConfig.bState = BOOT_STATE_NO_OTA;
        gBootConfig.nextBootRegion = 'F';
        updateBootConfig = 1;
		break;
    }

    if (updateBootConfig) {
        wd_write_boot_config(&gBootConfig);
    }

#endif	/* UBOOT_PINGPONG_NEW_DESIGN*/

	/* reset boot flags */
	boot_from_flash = BOOT_FROM_FLASH_NORMAL_MODE;
	boot_from_usb = BOOT_FROM_USB_DISABLE;

	/* parse option */
	if (argc == 1)
	{
		boot_from_usb = BOOT_FROM_USB_DISABLE;
	}
	else if (argc == 2 && argv[1][0] == 'u')
	{
		if (argv[1][1] == 'z')
		{
			boot_from_usb = BOOT_FROM_USB_COMPRESSED;
		}
		else if (argv[1][1] == '\0')
		{
			boot_from_usb = BOOT_FROM_USB_UNCOMPRESSED;
		}
		else
		{
			return CMD_RET_USAGE;
		}
	}
	else if (argc == 2 && argv[1][0] == 'm')
	{
		boot_from_flash = BOOT_FROM_FLASH_MANUAL_MODE;
	}
	else if (argc == 2 && argv[1][0] == 'f')
	{
		boot_from_flash = BOOT_FROM_FLASH_MANUAL_MODE;
		accelerate_state = 1;
		/*The bootr f command is for faster blue logo*/
	}
	else
	{
		return CMD_RET_USAGE;
	}

	WATCHDOG_KICK();

	if(!gUSB_MODE){
		DDDDYELLOW("[Info] Not USB mode, run rtk_plat_boot_handler()...\n");
		ret = rtk_plat_boot_handler();
	}

#if 0	/** WD change:
	River: KAM-8762: Skip boot golden image
	**/
    if (ret != RTK_PLAT_ERR_OK) {
        /*   LOAD GOLD FW   */
        ret = RTK_PLAT_ERR_OK;
        boot_mode=BOOT_GOLD_MODE;
        accelerate_state = 0;
        ret = rtk_plat_boot_handler();
    }
#endif

#ifdef CONFIG_RESCUE_FROM_USB
	if (ret != RTK_PLAT_ERR_OK) {
		if( gUSB_MODE || (ret != RTK_PLAT_ERR_OK)) {
			DDDDYELLOW("[Info] rescue boot from USB\n");
			ret = boot_rescue_from_usb();
		}
	}
#endif /* CONFIG_RESCUE_FROM_USB */

#ifdef CONFIG_RESCUE_FROM_DHCP
	if (ret != RTK_PLAT_ERR_OK) {
		DDDDYELLOW("[Info] rescue boot from DHCP:%s\n", CONFIG_BOOTP_SERVERIP);
		ret = boot_rescue_from_dhcp();
	}
#endif

	return CMD_RET_SUCCESS;
}

U_BOOT_CMD(
	bootr, 2, 0,	rtk_plat_do_bootr,
	"boot realtek platform",
	"[u/uz]\n"
	"\tf   - boot faster of blue logo\n"
	"\tu   - boot from usb\n"
	"\tuz  - boot from usb (use lzma image)\n"
	"\tm   - read fw from flash but boot manually (go all)\n"
);

#endif /* CONFIG_BOOT_FOR_WD */

