#ifndef __RTK_BOOT_H__
#define __RTK_BOOT_H__

typedef enum{
	BOOT_FROM_USB_DISABLE,
	BOOT_FROM_USB_UNCOMPRESSED,
	BOOT_FROM_USB_COMPRESSED
}BOOT_FROM_USB_T;

typedef enum{
	BOOT_FROM_FLASH_NORMAL_MODE,
	BOOT_FROM_FLASH_MANUAL_MODE
}BOOT_FROM_FLASH_T;

extern BOOT_FROM_FLASH_T boot_from_flash;
extern BOOT_FROM_USB_T boot_from_usb;

int  rtk_plat_boot_handler(void);
int boot_rescue_from_usb(void);

#endif
