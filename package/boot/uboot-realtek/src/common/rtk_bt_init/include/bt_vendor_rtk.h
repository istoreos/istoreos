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
 *  Filename:      bt_vendor_rtk.h
 *
 *  Description:   A wrapper header file of bt_vendor_lib.h
 *
 *                 Contains definitions specific for interfacing with Realtek
 *                 Bluetooth chipsets
 *
 ******************************************************************************/

#ifndef BT_VENDOR_RTK_H
#define BT_VENDOR_RTK_H

#include "../osi/include/osi_include_ext.h"
#include "../osi/include/osi_data_types.h"

/******************************************************************************
**  Constants & Macros
******************************************************************************/
#define	ENODEV		                        19	/* No such device */

//HCI Command opcodes
#define HCI_RESET                       0x0C03
#define HCI_READ_LMP_VERSION            0x1001
#define HCI_READ_BUFFER_SIZE            0x1005
#define HCI_LE_READ_BUFFER_SIZE         0x2002
#define HCI_READ_BD_ADDR                0x1009

//HCI VENDOR Command opcode
#define HCI_VSC_H5_INIT                 0xFCEE
#define HCI_VSC_UPDATE_BAUDRATE         0xFC17
#define HCI_VSC_DOWNLOAD_FW_PATCH       0xFC20
#define HCI_VSC_READ_ROM_VERSION        0xFC6D
#define HCI_VSC_READ_CHIP_TYPE          0xFC61
#define HCI_VSC_SET_WAKE_UP_DEVICE      0xFC7B
#define HCI_VSC_BT_OFF                  0xFC28
#define HCI_VENDOR_FORCE_RESET_AND_PATCHABLE    0xFC66
#define HCI_VENDOR_RESET                        0x0C03



//HCI Event codes
#define HCI_CONNECTION_COMP_EVT         0x03
#define HCI_DISCONNECTION_COMP_EVT      0x05
#define HCI_COMMAND_COMPLETE_EVT        0x0E
#define HCI_COMMAND_STATUS_EVT          0x0F
#define HCI_NUM_OF_CMP_PKTS_EVT         0x13
#define HCI_BLE_EVT                     0x3E


#define HCI_CMD_PREAMBLE_SIZE           3
#define HCI_EVT_PREAMBLE_SIZE           2
#define HCI_EVT_CMD_CMPL_OPCODE_OFFSET          (3)     //opcode's offset in COMMAND Completed Event
#define HCI_EVT_CMD_CMPL_STATUS_OFFSET          (5)     //status's offset in COMMAND Completed Event



#define UPDATE_BAUDRATE_CMD_PARAM_SIZE          (6)
#define HCD_REC_PAYLOAD_LEN_BYTE                (2)
#define LOCAL_NAME_BUFFER_LEN                   (32)
#define LOCAL_BDADDR_PATH_BUFFER_LEN            (256)


#define BD_ADDR_LEN                             (6)
#define HCI_CMD_MAX_LEN                         258

/******************************************************************************
**  Type define
******************************************************************************/
typedef struct {
    u8 b[6];
} __attribute__((packed)) bdaddr_t;

/******************************************************************************
**  Extern variables and functions
******************************************************************************/
#define STREAM_TO_UINT16(u16_v, p) {u16_v = ((u16)(*(p)) + (((u16)(*((p) + 1))) << 8)); (p) += 2;}
#define UINT16_TO_STREAM(p, u16_v) {*(p)++ = (u8)(u16_v); *(p)++ = (u8)((u16_v) >> 8);}
#define UINT32_TO_STREAM(p, u32_v) {*(p)++ = (u8)(u32_v); *(p)++ = (u8)((u32_v) >> 8); *(p)++ = (u8)((u32_v) >> 16); *(p)++ = (u8)((u32_v) >> 24);}
#define STREAM_TO_UINT32(u32_v, p) {u32_v = (((u32)(*(p))) + ((((u32)(*((p) + 1)))) << 8) + ((((u32)(*((p) + 2)))) << 16) + ((((u32)(*((p) + 3)))) << 24)); (p) += 4;}
#define UINT8_TO_STREAM(p, u8_v)   {*(p)++ = (u8)(u8_v);}

#endif /* BT_VENDOR_RTK_H */
