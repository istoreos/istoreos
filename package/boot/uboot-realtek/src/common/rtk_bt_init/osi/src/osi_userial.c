/******************************************************************************
 *
 *  Copyright (C) 2009-2012 Realtek Corporation
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
 *  Filename:      userial_vendor.c
 *
 *  Description:   Contains vendor-specific userial functions
 *
 ******************************************************************************/
#include "../include/osi_include_int.h"
#include "../include/osi_include_ext.h"


/******************************************************************************
**  Constants & Macros
******************************************************************************/
#define VND_PORT_NAME_MAXLEN    256

/******************************************************************************
**  Local type definitions
******************************************************************************/
static struct serial_device* bt_uart;

/******************************************************************************
**  Static variables
******************************************************************************/


/*****************************************************************************
**   Helper Functions
*****************************************************************************/

/*******************************************************************************
**
** Function        userial_to_tcio_baud
**
** Description     helper function converts USERIAL baud rates into TCIO
**                  conforming baud rates
**
** Returns         TRUE/FALSE
**
*******************************************************************************/
u8 userial_to_tcio_baud(u8 cfg_baud, u32 *baud)
{
    UNUSED(cfg_baud);
    UNUSED(baud);
    return 0;
}


/*****************************************************************************
**   Userial Vendor API Functions
*****************************************************************************/

/*******************************************************************************
**
** Function        userial_vendor_init
**
** Description     Initialize userial vendor-specific control block
**
** Returns         None
**
*******************************************************************************/
void userial_vendor_init()
{
    RTK_DEBUG ("Bring up UART1\n");
    RTK_DEBUG ("baudrate    = %u bps\n", gd->baudrate);

    /* disable uart1 reset bits and uart1 clocl bits , then enable it */
    *(volatile unsigned int *)0x98000004 = (unsigned int)0xf840e01;
    *(volatile unsigned int *)0x98000010 = (unsigned int)0x4801e406;
    /* disable uart1 reset bits and uart1 clocl bits , then enable it */
    *(volatile unsigned int *)0x98000004 = (unsigned int)0x1f840e01;
    *(volatile unsigned int *)0x98000010 = (unsigned int)0x5801e406;

    *(volatile unsigned int *)0x98007310 = (unsigned int)0x155400;  /*Setup ISO MUX PAD0 for uart1 pins*/
    *(volatile unsigned int *)0x9801B200 = (unsigned int)0x90;      /*UART1_LCR*/
    *(volatile unsigned int *)0x9801B200 = (unsigned int)0xea;      /*UART1_DLL Set baud rate to 115200 base on 432 MHz*/
    *(volatile unsigned int *)0x9801B204 = (unsigned int)0x0;       /*UART1_DLM*/
    //*(volatile unsigned int *)0x9801B20c = (unsigned int)0x03;      /*UART1_LCR (8-N-1)*/
    *(volatile unsigned int *)0x9801B20c = (unsigned int)0x1b;      /*UART1_LCR (8-E-1)*/
    *(volatile unsigned int *)0x9801B208 = (unsigned int)0xc7;      /*UART1_FCR*/
    *(volatile unsigned int *)0x9801B204 = (unsigned int)0x01;      /*UART1_IER*/

    serial_init_uart(UART1);    /*UART1 initialization and setting clock HZ.*/

    bt_uart = get_uart(UART1);

    return;
}


/*******************************************************************************
**
** Function        userial_vendor_open
**
** Description     Open the serial port with the given configuration
**
** Returns         device fd
**
*******************************************************************************/
int userial_vendor_open(tUSERIAL_CFG *p_cfg)
{
    UNUSED(p_cfg);
   return 0;
}

/*******************************************************************************
**
** Function        userial_vendor_close
**
** Description     Conduct vendor-specific close work
**
** Returns         None
**
*******************************************************************************/
void userial_vendor_close(void)
{
    return;
}

/*******************************************************************************
**
** Function        userial_vendor_set_baud
**
** Description     Set new baud rate
**
** Returns         None
**
*******************************************************************************/
BOOLEAN userial_vendor_set_baud(u8 baud)
{
    RTK_DEBUG ("origin baudrate    = %u bps\n", gd->baudrate);
    u32 gb_baund_temp = gd->baudrate;

    if (baud == USERIAL_BAUD_4M)
        gd->baudrate = 4000000;
    else if (baud == USERIAL_BAUD_3M)
        gd->baudrate = 3000000;
    else if (baud == USERIAL_BAUD_2M)
        gd->baudrate = 2000000;
    else if (baud == USERIAL_BAUD_1_5M)
        gd->baudrate = 1500000;
    else if (baud == USERIAL_BAUD_1M)
        gd->baudrate = 1000000;
    else if (baud == USERIAL_BAUD_921600)
        gd->baudrate = 921600;
    else if (baud == USERIAL_BAUD_460800)
        gd->baudrate = 460800;
    else if (baud == USERIAL_BAUD_230400)
        gd->baudrate = 230400;
    else if (baud == USERIAL_BAUD_115200)
        gd->baudrate = 115200;
    else if (baud == USERIAL_BAUD_57600)
        gd->baudrate = 57600;
    else if (baud == USERIAL_BAUD_19200)
        gd->baudrate = 19200;
    else if (baud == USERIAL_BAUD_9600)
        gd->baudrate = 9600;
    else if (baud == USERIAL_BAUD_1200)
        gd->baudrate = 1200;
    else if (baud == USERIAL_BAUD_600)
        gd->baudrate = 600;
    else
    {
        RTK_ERROR( "userial vendor: unsupported baud speed %d \n", baud);
    }

    bt_uart->setbrg();
    gd->baudrate = gb_baund_temp;
    return TRUE;
}

/*******************************************************************************
**
** Function        userial_vendor_ioctl
**
** Description     ioctl inteface
**
** Returns         None
**
*******************************************************************************/
void userial_vendor_ioctl(userial_vendor_ioctl_op_t op, void *p_data)
{
    UNUSED(op);
    UNUSED(p_data);
    return;
}

/*******************************************************************************
**
** Function        userial_set_port
**
** Description     Configure UART port name
**
** Returns         0 : Success
**                 Otherwise : Fail
**
*******************************************************************************/
int userial_set_port(char *p_conf_name, char *p_conf_value, int param)
{
    UNUSED(p_conf_name);
    UNUSED(p_conf_value);

    UNUSED(param);
    return 0;
}

/*******************************************************************************
**
** Function        userial_vendor_set_hw_fctrl
**
** Description     Conduct vendor-specific close work
**
** Returns         None
**
*******************************************************************************/
BOOLEAN userial_vendor_set_hw_fctrl(u8 hw_fctrl)
{
    UNUSED(hw_fctrl);
    return TRUE;
}

u32 userial_vendor_send_data(u8* data, u32 len)
{
    u32 bytes_send = len;
    if(!data || !len) {
        RTK_ERROR("DATA IS ERROR len = %d", len);
        return 0;
    }
    while(len) {
        bt_uart->putc_raw(*data);
        data++;
        len--;
    }
    return (bytes_send - len);
}

u32 userial_vendor_receive_data(u8* data)
{
    unsigned int read_len = 0;
    int i = 0;
    while(i < 10) {
        while(bt_uart->tstc()) {
            data[read_len] = bt_uart->getc();
            read_len++;
        }
        osi_rtk_udelay(100);
        i++;
    }
    return read_len;
}


