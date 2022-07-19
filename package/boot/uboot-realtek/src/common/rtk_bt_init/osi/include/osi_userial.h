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
 *  Filename:      userial_vendor.h
 *
 *  Description:   Contains vendor-specific definitions used in serial port
 *                 controls
 *
 ******************************************************************************/
#ifndef USERIAL_VENDOR_H
#define USERIAL_VENDOR_H

#include "osi_data_types.h"

/******************************************************************************
**  Constants & Macros
******************************************************************************/

/**** baud rates ****/
#define USERIAL_BAUD_300        0
#define USERIAL_BAUD_600        1
#define USERIAL_BAUD_1200       2
#define USERIAL_BAUD_2400       3
#define USERIAL_BAUD_9600       4
#define USERIAL_BAUD_19200      5
#define USERIAL_BAUD_57600      6
#define USERIAL_BAUD_115200     7
#define USERIAL_BAUD_230400     8
#define USERIAL_BAUD_460800     9
#define USERIAL_BAUD_921600     10
#define USERIAL_BAUD_1M         11
#define USERIAL_BAUD_1_5M       12
#define USERIAL_BAUD_2M         13
#define USERIAL_BAUD_3M         14
#define USERIAL_BAUD_4M         15
#define USERIAL_BAUD_AUTO       16

/**** Data Format ****/
/* Stop Bits */
#define USERIAL_STOPBITS_1      1
#define USERIAL_STOPBITS_1_5    (1<<1)
#define USERIAL_STOPBITS_2      (1<<2)

/* Parity Bits */
#define USERIAL_PARITY_NONE     (1<<3)
#define USERIAL_PARITY_EVEN     (1<<4)
#define USERIAL_PARITY_ODD      (1<<5)

/* Data Bits */
#define USERIAL_DATABITS_5      (1<<6)
#define USERIAL_DATABITS_6      (1<<7)
#define USERIAL_DATABITS_7      (1<<8)
#define USERIAL_DATABITS_8      (1<<9)


#define USERIAL_HW_FLOW_CTRL_OFF  0
#define USERIAL_HW_FLOW_CTRL_ON    1


/******************************************************************************
**  Type definitions
******************************************************************************/

/* Structure used to configure serial port during open */
typedef struct
{
    u16 fmt;       /* Data format */
    u8  baud;      /* Baud rate */
    u8 hw_fctrl; /*hardware flowcontrol*/
} tUSERIAL_CFG;

typedef enum {
    USERIAL_OP_NOP,
} userial_vendor_ioctl_op_t;

/******************************************************************************
**  Extern variables and functions
******************************************************************************/

/******************************************************************************
**  Functions
******************************************************************************/

/*******************************************************************************
**
** Function        userial_vendor_init
**
** Description     Initialize userial vendor-specific control block
**
** Returns         None
**
*******************************************************************************/
void userial_vendor_init(void);

/*******************************************************************************
**
** Function        userial_vendor_open
**
** Description     Open the serial port with the given configuration
**
** Returns         device fd
**
*******************************************************************************/
int userial_vendor_open(tUSERIAL_CFG *p_cfg);

/*******************************************************************************
**
** Function        userial_vendor_close
**
** Description     Conduct vendor-specific close work
**
** Returns         None
**
*******************************************************************************/
void userial_vendor_close(void);

/*******************************************************************************
**
** Function        userial_vendor_set_baud
**
** Description     Set new baud rate
**
** Returns         None
**
*******************************************************************************/
BOOLEAN userial_vendor_set_baud(u8 userial_baud);

/*******************************************************************************
**
** Function        userial_vendor_ioctl
**
** Description     ioctl inteface
**
** Returns         None
**
*******************************************************************************/
void userial_vendor_ioctl(userial_vendor_ioctl_op_t op, void *p_data);

BOOLEAN userial_vendor_set_hw_fctrl(u8 hw_fctrl);

u32 userial_vendor_send_data(u8* data, u32 len);

u32 userial_vendor_receive_data(u8* data);

#endif /* USERIAL_VENDOR_H */
