/******************************************************************************
 *
 *  Copyright (C) 2016 Realtek Corporation.
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at:
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 ******************************************************************************/
/******************************************************************************
*
*	Module Name:
*	    dlfw_main.c
*
*	Abstract:
*	    Contain HCI transport send/receive functions for UART H5 Interface.
*
*	Major Change History:
*	      When             Who       What
*	    ---------------------------------------------------------------
*	    2016-08-30      caicheng    created
*
*	Notes:
*	      This is designed for BOOT Loader download fw
*
******************************************************************************/
#include "./osi/include/osi_include_int.h"
#include "./osi/include/osi_include_ext.h"

#include "cmd_bt_init.h"
#include "include/hardware.h"
#include <command.h>

//#include "../drivers/gpio/rt_gpio.h"
#include <asm/arch/platform_lib/board/gpio.h>


/******************************************************************************
**  Extern variables
******************************************************************************/
extern char usb_started; /* flag for the started/stopped USB status */

/******************************************************************************
**  Static variables
******************************************************************************/
static u8 upio_state[UPIO_MAX_COUNT];

static const tUSERIAL_CFG userial_init_cfg =
{
    (USERIAL_DATABITS_8 | USERIAL_PARITY_EVEN | USERIAL_STOPBITS_1),
    USERIAL_BAUD_115200,
    USERIAL_HW_FLOW_CTRL_OFF
};


#ifdef CONFIG_USB_STORAGE
static int usb_stor_curr_dev = -1; /* current device */
#endif
#ifdef CONFIG_USB_HOST_ETHER
static int usb_ether_curr_dev = -1; /* current ethernet device */
#endif

/*******************************************************************************
**
** Function        upio_init
**
** Description     Initialization
**
** Returns         None
**
*******************************************************************************/
static void upio_init(void)
{
    osi_memset(upio_state, UPIO_UNKNOWN, UPIO_MAX_COUNT);
}

/*******************************************************************************
**
** Function        upio_set_bluetooth_power
**
** Description     Interact with low layer driver to set Bluetooth power
**                 on/off.
**
** Returns         0  : SUCCESS or Not-Applicable
**                 <0 : ERROR
**
*******************************************************************************/
int upio_set_bluetooth_power(int on)
{
    int ret = -1;

    RTK_INFO("upio_set_bluetooth_power : %d \n", on);
    switch(on)
    {
        case UPIO_BT_POWER_OFF:
            setISOGPIO(RTD1295_BT_DISABLE_PIN, on);
            break;

        case UPIO_BT_POWER_ON:
            setISOGPIO(RTD1295_BT_DISABLE_PIN, on);
            break;
    }


    return ret;
}
static void	rtkbt_usb_device_copy(struct usb_device *usb_device, struct osi_usb_device *osi_usb_device)
{
    osi_usb_device->devnum = usb_device->devnum;
    osi_usb_device->speed = usb_device->devnum;
    osi_usb_device->maxpacketsize = usb_device->maxpacketsize;
    osi_memcpy(osi_usb_device->mf, usb_device->mf, 32);
    osi_memcpy(osi_usb_device->prod, usb_device->prod, 32);
    osi_memcpy(osi_usb_device->serial, usb_device->serial, 32);
    osi_memcpy(&osi_usb_device->descriptor, &usb_device->descriptor, sizeof(struct osi_usb_device_descriptor));
}

static void	rtkbt_uart_start(void)
{
    userial_vendor_init();
    upio_init();

    upio_set_bluetooth_power(UPIO_BT_POWER_OFF);
    osi_rtk_mdelay(200);

    upio_set_bluetooth_power(UPIO_BT_POWER_ON);
    osi_rtk_mdelay(500);

    userial_vendor_open((tUSERIAL_CFG *) &userial_init_cfg);

    rtk_hw_init();
    return;
}

static void do_rtkusb_start(void)
{
    struct usb_device *udev = NULL;
    int i;
    bool rtkbt_usb_found= false;
    struct osi_usb_device dev;

	bootstage_mark_name(BOOTSTAGE_ID_USB_START, "usb_start");

	if (usb_init() < 0)
		return;

	/* Driver model will probe the devices as they are found */
//#ifndef CONFIG_DM_USB
//#ifdef CONFIG_USB_STORAGE
	/* try to recognize storage devices immediately */
//	usb_stor_curr_dev = usb_stor_scan(1);
//#endif
//#endif
//#ifdef CONFIG_USB_HOST_ETHER
	/* try to recognize ethernet devices immediately */
//	usb_ether_curr_dev = usb_host_eth_scan(1);
//#endif

    for (i = 0; i < USB_MAX_DEVICE; i++) {
        udev = usb_get_dev_index(i);
        RTK_INFO("i=%d udev->devnum:%d udev->mf:%s udev->prod:%s\n", i, udev->devnum, udev->mf, udev->prod);
        if(udev->devnum!=-1) {
            if(udev->descriptor.idVendor == 0x0bda && udev->descriptor.idProduct == 0xb820){
                rtkbt_usb_found = true;
                break;
            }
        }
    }

    if(rtkbt_usb_found) {
        dev.context = (void *)udev;
        rtkbt_usb_device_copy(udev, &dev);
        load_rtl_firmware_dev(&dev);
    }

}

static void	rtkbt_usb_start(void)
{
    if (usb_started)
        return; /* Already started */
    RTK_INFO("starting USB...\n");
    usb_started = 1;
    do_rtkusb_start();

    return;
}

static void	rtkbt_usb_stop(void)
{
    if (!usb_started)
        return; /* Already started */
    RTK_INFO("stoping USB...\n");
    usb_started = 0;
    usb_stop();

    return;
}

int do_rtk_bt_init(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    if (argc < 2)
		return CMD_RET_USAGE;

	if (strncmp(argv[1], "uart", 4) == 0) {
		RTK_INFO("starting UART BT...\n");
		rtkbt_uart_start();
	}
    else if(strncmp(argv[1], "usb", 3) == 0) {
		RTK_INFO("starting USB BT...\n");
		rtkbt_usb_start();
        rtkbt_usb_stop();
    }

    RTK_INFO("EXIT bt init process! \n");
    return 0;
}

U_BOOT_CMD(
	rtk_bt_init, 4,	1,	do_rtk_bt_init,
	"start bt download fw function",
	"usb interface: rtk_bt_init usb \n"
	"uart interface: rtk_bt_init uart \n"
);

