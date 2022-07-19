/******************************************************************************
 *
 *  Copyright (C) 2014 Google, Inc.
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
 #ifndef RTK_H5_INT_H__
 #define RTK_H5_INT_H__

/***********************************************
****    internal include*****************************/
#include "../osi/include/osi_data_types.h"

/************************************************/
#define TIMER_H5_TOTAL_NUM_MAX             16

#define TIMER_H5_HW_INIT_READY              1
#define TIMER_H5_SYNC_RETRANS               2
#define TIMER_H5_CONF_RETRANS               4
#define TIMER_H5_DATA_RETRANS               8
#define TIMER_H5_WAIT_CT_BAUDRATE_READY     16


#define DATA_RETRANS_COUNT  40  //40*100 = 4000ms(4s)
#define SYNC_RETRANS_COUNT  20  //20*250 = 5000ms(5s)
#define CONF_RETRANS_COUNT  20


#define DATA_RETRANS_TIMEOUT_VALUE              100 //ms
#define SYNC_RETRANS_TIMEOUT_VALUE              250
#define CONF_RETRANS_TIMEOUT_VALUE              250
#define WAIT_CT_BAUDRATE_READY_TIMEOUT_VALUE    250
#define H5_HW_INIT_READY_TIMEOUT_VALUE          10000//4

/* Message event mask across Host/Controller lib and stack */
#define MSG_EVT_MASK                    0xFF00 /* eq. BT_EVT_MASK */
#define MSG_SUB_EVT_MASK                0x00FF /* eq. BT_SUB_EVT_MASK */

/* Message event ID passed from Host/Controller lib to stack */
#define MSG_HC_TO_STACK_HCI_ERR        0x1300 /* eq. BT_EVT_TO_BTU_HCIT_ERR */
#define MSG_HC_TO_STACK_HCI_ACL        0x1100 /* eq. BT_EVT_TO_BTU_HCI_ACL */
#define MSG_HC_TO_STACK_HCI_SCO        0x1200 /* eq. BT_EVT_TO_BTU_HCI_SCO */
#define MSG_HC_TO_STACK_HCI_EVT        0x1000 /* eq. BT_EVT_TO_BTU_HCI_EVT */
#define MSG_HC_TO_STACK_L2C_SEG_XMIT   0x1900 /* eq. BT_EVT_TO_BTU_L2C_SEG_XMIT */

/* Message event ID passed from stack to vendor lib */
#define MSG_STACK_TO_HC_HCI_ACL        0x2100 /* eq. BT_EVT_TO_LM_HCI_ACL */
#define MSG_STACK_TO_HC_HCI_SCO        0x2200 /* eq. BT_EVT_TO_LM_HCI_SCO */
#define MSG_STACK_TO_HC_HCI_CMD        0x2000 /* eq. BT_EVT_TO_LM_HCI_CMD */

typedef struct
{
    u16         total_num;
    u16         timer_event;
} rtk_timer_t;


typedef struct
{
    u16          event;
    u16          len;
    u16          offset;
    u16          layer_specific;
    u8           data[];
} HC_BT_HDR;

#define BT_HC_HDR_SIZE (sizeof(HC_BT_HDR))


/* Callback function for the returned event of internal issued command */
typedef void (*tINT_CMD_CBACK)(void *p_mem);

/* Initialize transport's control block */
typedef void (*tHCI_INIT)(void);

/* Do transport's control block clean-up */
typedef void (*tHCI_CLEANUP)(void);

/* Handler for HCI upstream path */
typedef bool (*tHCI_RCV_AND_CHK_TIMER)(void);

/* Handler for sending HCI command from the local module */
typedef u8 (*tHCI_SEND_INT)(u16 opcode, HC_BT_HDR *p_buf, tINT_CMD_CBACK p_cback);

typedef void* (*tHCI_ALLOC)(int size);

/* datapath buffer deallocation callback (callout) */
typedef void (*tHCI_DEALLOC)(void *p_buf);

/******************************************************************************
**  Extern variables and functions
******************************************************************************/
typedef struct {
    tHCI_INIT               init;
    tHCI_CLEANUP            cleanup;
    tHCI_SEND_INT           send_int_cmd;
    tHCI_RCV_AND_CHK_TIMER  rcv_and_chk_timer;
    tHCI_ALLOC              alloc;
    tHCI_DEALLOC            dealloc;
} tHCI_IF;

const tHCI_IF *hci_get_h5_interface(void);


#endif
