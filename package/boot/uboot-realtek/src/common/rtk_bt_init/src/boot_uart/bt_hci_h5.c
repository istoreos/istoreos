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
*	    hci_h5.c
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
*	      This is designed for UART H5 HCI Interface in Android 6.0.
*
******************************************************************************/
#define LOG_TAG "bt_h5"
#include "../../osi/include/osi_include_int.h"
#include "../../osi/include/osi_include_ext.h"

/******************************************************************************
**  Constants & Macros
******************************************************************************/

#define H5_TRACE_DATA_ENABLE 0//if you want to see data tx and rx, set H5_TRACE_DATA_ENABLE 1
#define H5_LOG_VERBOSE      0

/* Maximum numbers of allowed internal
** outstanding command packets at any time
*/
#define INT_CMD_PKT_MAX_COUNT       8
#define INT_CMD_PKT_IDX_MASK        0x07


#define PATCH_DATA_FIELD_MAX_SIZE     252
#define READ_DATA_SIZE  16

// HCI data types //
#define H5_RELIABLE_PKT         0x01
#define H5_UNRELIABLE_PKT       0x00

#define H5_ACK_PKT              0x00
#define HCI_COMMAND_PKT         0x01
#define HCI_ACLDATA_PKT         0x02
#define HCI_SCODATA_PKT         0x03
#define HCI_EVENT_PKT           0x04
#define H5_VDRSPEC_PKT          0x0E
#define H5_LINK_CTL_PKT         0x0F

#define H5_HDR_SEQ(hdr)         ((hdr)[0] & 0x07)
#define H5_HDR_ACK(hdr)         (((hdr)[0] >> 3) & 0x07)
#define H5_HDR_CRC(hdr)         (((hdr)[0] >> 6) & 0x01)
#define H5_HDR_RELIABLE(hdr)    (((hdr)[0] >> 7) & 0x01)
#define H5_HDR_PKT_TYPE(hdr)    ((hdr)[1] & 0x0f)
#define H5_HDR_LEN(hdr)         ((((hdr)[1] >> 4) & 0xff) + ((hdr)[2] << 4))
#define H5_HDR_SIZE             4

#define H5_CFG_SLID_WIN(cfg)    ((cfg) & 0x07)
#define H5_CFG_OOF_CNTRL(cfg)   (((cfg) >> 3) & 0x01)
#define H5_CFG_DIC_TYPE(cfg)    (((cfg) >> 4) & 0x01)
#define H5_CFG_VER_NUM(cfg)     (((cfg) >> 5) & 0x07)
#define H5_CFG_SIZE             1



/******************************************************************************
**  Local type definitions
******************************************************************************/
typedef struct
{
    u16 opcode;        /* OPCODE of outstanding internal commands */
    tINT_CMD_CBACK cback;   /* Callback function when return of internal * command is received */
} tINT_CMD_Q;

typedef RTK_BUFFER sk_buff;

typedef enum H5_RX_STATE
{
    H5_W4_PKT_DELIMITER,
    H5_W4_PKT_START,
    H5_W4_HDR,
    H5_W4_DATA,
    H5_W4_CRC
} tH5_RX_STATE;

typedef enum H5_RX_ESC_STATE
{
    H5_ESCSTATE_NOESC,
    H5_ESCSTATE_ESC
} tH5_RX_ESC_STATE;

typedef enum H5_LINK_STATE
{
    H5_UNINITIALIZED,
    H5_INITIALIZED,
    H5_ACTIVE
} tH5_LINK_STATE;


/* Control block for HCISU_H5 */
typedef struct HCI_H5_CB
{
    HC_BT_HDR       *p_rcv_msg;          /* Buffer to hold current rx HCI message */
    u16             rcv_len;               /* Size of current incoming message */
    u8              rcv_msg_type;           /* Current incoming message type */
    int             int_cmd_rsp_pending;        /* Num of internal cmds pending for ack */
    u8              int_cmd_rd_idx;         /* Read index of int_cmd_opcode queue */
    u8              int_cmd_wrt_idx;        /* Write index of int_cmd_opcode queue */
    tINT_CMD_Q      int_cmd[INT_CMD_PKT_MAX_COUNT]; /* FIFO queue */

    tINT_CMD_CBACK  cback_h5sync;   /* Callback function when h5 sync*/

    u8              sliding_window_size;
    u8              oof_flow_control;
    u8              dic_type;


    RTB_QUEUE_HEAD  *unack;      // Unack'ed packets queue
    RTB_QUEUE_HEAD  *rel;        // Reliable packets queue

    RTB_QUEUE_HEAD  *unrel;      // Unreliable packets queue


    u8              rxseq_txack;        // rxseq == txack. // expected rx SeqNumber,    (rx sequence number +1) = tx Acknowledgement number
    u8              rxack;             // Last packet sent by us that the peer ack'ed // rx Acknowledgement number

    u8              use_crc;
    u8              is_txack_req;      // txack required? Do we need to send ack's to the peer? //

    // Reliable packet sequence number - used to assign seq to each rel pkt. */
    u8              msgq_txseq;         //next pkt seq,  tx sequence

    u16             message_crc;
    u32             rx_count;       //expected pkts to recv

    tH5_RX_STATE    rx_state;
    tH5_RX_ESC_STATE    rx_esc_state;
    tH5_LINK_STATE  link_estab_state;

    sk_buff         *rx_skb;
    sk_buff         *host_last_cmd;

/************   retran timer block  ******************/
    rtk_timer_t     timer_cb;
    u32             timer_h5_hw_init_ready;             //event mask 0x01
    u32             timer_sync_retrans;                 //event mask 0x02
    u32             timer_conf_retrans;                 //event mask 0x04
    u32             timer_data_retrans;                 //event mask 0x08
    u32             timer_wait_ct_baudrate_ready;       //event mask 0x10
/***********************************************/
    u32             data_retrans_count;
    u32             sync_retrans_count;
    u32             conf_retrans_count;

    u8              cleanuping;
}tHCI_H5_CB;

static tHCI_H5_CB rtk_h5;

/******************************************************************************
**  Variables
******************************************************************************/

/* Num of allowed outstanding HCI CMD packets */
volatile int num_hci_cmd_pkts = 1;

/******************************************************************************
**  Static variables
******************************************************************************/


/******************************************************************************
**  Static function
******************************************************************************/
static bool h5_data_retrans_timeout_handler(void);
static bool h5_sync_retrans_timeout_handler(void);
static bool h5_conf_retrans_timeout_handler(void);
static bool h5_wait_controller_baudrate_ready_timeout_handler(void);
static bool h5_hw_init_ready_timeout_handler(void);

static u16 h5_wake_up(void);

static char * dump_h5_packet_type(u8 pkt_type);

/******************************************************************************
**  Externs
******************************************************************************/
u8 hci_h5_send_int_cmd(u16 opcode, HC_BT_HDR *p_buf, tINT_CMD_CBACK p_cback);

//timer API for retransfer
void h5_alloc_data_retrans_timer(void);
void h5_free_data_retrans_timer(void);
void h5_stop_data_retrans_timer(void);
void h5_start_data_retrans_timer(void);

void h5_alloc_sync_retrans_timer(void);
void h5_free_sync_retrans_timer(void);
void h5_stop_sync_retrans_timer(void);
void h5_start_sync_retrans_timer(void);

void h5_alloc_conf_retrans_timer(void);
void h5_free_conf_retrans_timer(void);
void h5_stop_conf_retrans_timer(void);
void h5_start_conf_retrans_timer(void);

void h5_alloc_wait_controller_baudrate_ready_timer(void);
void h5_free_wait_controller_baudrate_ready_timer(void);
void h5_stop_wait_controller_baudrate_ready_timer(void);
void h5_start_wait_controller_baudrate_ready_timer(void);

void h5_alloc_hw_init_ready_timer(void);
void h5_free_hw_init_ready_timer(void);
void h5_stop_hw_init_ready_timer(void);
void h5_start_hw_init_ready_timer(void);


// bite reverse in bytes
// 00000001 -> 10000000
// 00000100 -> 00100000
const u8 byte_rev_table[256] = {
    0x00, 0x80, 0x40, 0xc0, 0x20, 0xa0, 0x60, 0xe0,
    0x10, 0x90, 0x50, 0xd0, 0x30, 0xb0, 0x70, 0xf0,
    0x08, 0x88, 0x48, 0xc8, 0x28, 0xa8, 0x68, 0xe8,
    0x18, 0x98, 0x58, 0xd8, 0x38, 0xb8, 0x78, 0xf8,
    0x04, 0x84, 0x44, 0xc4, 0x24, 0xa4, 0x64, 0xe4,
    0x14, 0x94, 0x54, 0xd4, 0x34, 0xb4, 0x74, 0xf4,
    0x0c, 0x8c, 0x4c, 0xcc, 0x2c, 0xac, 0x6c, 0xec,
    0x1c, 0x9c, 0x5c, 0xdc, 0x3c, 0xbc, 0x7c, 0xfc,
    0x02, 0x82, 0x42, 0xc2, 0x22, 0xa2, 0x62, 0xe2,
    0x12, 0x92, 0x52, 0xd2, 0x32, 0xb2, 0x72, 0xf2,
    0x0a, 0x8a, 0x4a, 0xca, 0x2a, 0xaa, 0x6a, 0xea,
    0x1a, 0x9a, 0x5a, 0xda, 0x3a, 0xba, 0x7a, 0xfa,
    0x06, 0x86, 0x46, 0xc6, 0x26, 0xa6, 0x66, 0xe6,
    0x16, 0x96, 0x56, 0xd6, 0x36, 0xb6, 0x76, 0xf6,
    0x0e, 0x8e, 0x4e, 0xce, 0x2e, 0xae, 0x6e, 0xee,
    0x1e, 0x9e, 0x5e, 0xde, 0x3e, 0xbe, 0x7e, 0xfe,
    0x01, 0x81, 0x41, 0xc1, 0x21, 0xa1, 0x61, 0xe1,
    0x11, 0x91, 0x51, 0xd1, 0x31, 0xb1, 0x71, 0xf1,
    0x09, 0x89, 0x49, 0xc9, 0x29, 0xa9, 0x69, 0xe9,
    0x19, 0x99, 0x59, 0xd9, 0x39, 0xb9, 0x79, 0xf9,
    0x05, 0x85, 0x45, 0xc5, 0x25, 0xa5, 0x65, 0xe5,
    0x15, 0x95, 0x55, 0xd5, 0x35, 0xb5, 0x75, 0xf5,
    0x0d, 0x8d, 0x4d, 0xcd, 0x2d, 0xad, 0x6d, 0xed,
    0x1d, 0x9d, 0x5d, 0xdd, 0x3d, 0xbd, 0x7d, 0xfd,
    0x03, 0x83, 0x43, 0xc3, 0x23, 0xa3, 0x63, 0xe3,
    0x13, 0x93, 0x53, 0xd3, 0x33, 0xb3, 0x73, 0xf3,
    0x0b, 0x8b, 0x4b, 0xcb, 0x2b, 0xab, 0x6b, 0xeb,
    0x1b, 0x9b, 0x5b, 0xdb, 0x3b, 0xbb, 0x7b, 0xfb,
    0x07, 0x87, 0x47, 0xc7, 0x27, 0xa7, 0x67, 0xe7,
    0x17, 0x97, 0x57, 0xd7, 0x37, 0xb7, 0x77, 0xf7,
    0x0f, 0x8f, 0x4f, 0xcf, 0x2f, 0xaf, 0x6f, 0xef,
    0x1f, 0x9f, 0x5f, 0xdf, 0x3f, 0xbf, 0x7f, 0xff,
};

/* Copy, swap, convert BD Address */
static inline int bacmp(bdaddr_t *ba1, bdaddr_t *ba2)
{
    return osi_memcmp(ba1, ba2, sizeof(bdaddr_t));
}
static inline void bacpy(bdaddr_t *dst, bdaddr_t *src)
{
    osi_memcpy(dst, src, sizeof(bdaddr_t));
}

static inline void baPrint(bdaddr_t ba)
{
    UNUSED(ba);
    RTK_DEBUG("BT_ADDR: 0x%02X%02X%02X%02X%02X%02X \n",ba.b[5], ba.b[4], ba.b[3], ba.b[2], ba.b[1], ba.b[0]);
}
// reverse bit
static __inline u8 bit_rev8(u8 byte)
{
    return byte_rev_table[byte];
}

// reverse bit
static __inline u16 bit_rev16(u16 x)
{
    return (bit_rev8(x & 0xff) << 8) | bit_rev8(x >> 8);
}

static const u16 crc_table[] =
{
    0x0000, 0x1081, 0x2102, 0x3183,
    0x4204, 0x5285, 0x6306, 0x7387,
    0x8408, 0x9489, 0xa50a, 0xb58b,
    0xc60c, 0xd68d, 0xe70e, 0xf78f
};


static u16 h5_receive_data(u8 *data)
{
    u32 byte_recv = 0;
    byte_recv = userial_vendor_receive_data(data);
    return byte_recv;
}

static u16 h5_transmit_data(u8 *data, u16 length)
{
    u32 byte_sent = 0;
    byte_sent = userial_vendor_send_data(data, length);
    return byte_sent;
}

// Initialise the crc calculator
#define H5_CRC_INIT(x) x = 0xffff

/***********************************************
//
//skb related functions
//
//
//
***********************************************/
u8 *skb_get_data(IN sk_buff *skb)
{
    return skb->Data;
}

u32 skb_get_data_length(IN sk_buff *skb)
{
    return skb->Length;
}

u32 skb_get_hci_data_length(IN sk_buff *skb_acl)
{
    u8     *data;
    u16    handle, hci_len;

    data = skb_get_data(skb_acl);
    STREAM_TO_UINT16 (handle, data);
    STREAM_TO_UINT16 (hci_len, data);
    if(!handle)
        RTK_ERROR("skb_get_hci_data_length handle = 0x%04x",handle);
    return hci_len;

}

void skb_set_hci_data_length(IN sk_buff *skb_acl, IN u32 hci_len)
{
    u8     *data;

    data = skb_get_data(skb_acl);
    data = data + 2;
    UINT16_TO_STREAM(data, hci_len);
}

sk_buff * skb_alloc(IN unsigned int len)
{
    sk_buff * skb = (sk_buff * )RtbAllocate(len, 0);
    return skb;
}

void skb_free(IN OUT sk_buff **skb)
{
    RtbFree(*skb);
    *skb = NULL;
    return;
}

static  void skb_unlink(sk_buff *skb, struct _RTB_QUEUE_HEAD * list)
{
    RtbRemoveNode(list, skb);
}

// increase the date length in sk_buffer by len,
// and return the increased header pointer
u8 *skb_put(OUT sk_buff* skb, IN u32 len)
{
    RTK_BUFFER * rtb = (RTK_BUFFER * )skb;

    return RtbAddTail(rtb, len);
}

// change skb->len to len
// !!! len should less than skb->len
void skb_trim( sk_buff *skb, unsigned int len)
{
    RTK_BUFFER * rtb = (RTK_BUFFER * )skb;
    u32 skb_len = skb_get_data_length(skb);

    RtbRemoveTail(rtb, (skb_len - len));
    return;
}

u8 skb_get_pkt_type( sk_buff *skb)
{
    return BT_CONTEXT(skb)->PacketType;
}

void skb_set_pkt_type( sk_buff *skb, u8 pkt_type)
{
    BT_CONTEXT(skb)->PacketType = pkt_type;
}


// decrease the data length in sk_buffer by len,
// and move the content forward to the header.
// the data in header will be removed.
void skb_pull(OUT  sk_buff * skb, IN u32 len)
{
    RTK_BUFFER * rtb = (RTK_BUFFER * )skb;
    RtbRemoveHead(rtb, len);
    return;
}

sk_buff * skb_alloc_and_init(IN u8 PktType, IN u8 * Data, IN u32  DataLen)
{
    sk_buff * skb = skb_alloc(DataLen);
    if (NULL == skb)
        return NULL;

    osi_memcpy(skb_put(skb, DataLen), Data, DataLen);
    skb_set_pkt_type(skb, PktType);

    return skb;
}

static void skb_queue_head(IN RTB_QUEUE_HEAD * skb_head, IN RTK_BUFFER * skb)
{
    RtbQueueHead(skb_head, skb);
}

static void skb_queue_tail(IN RTB_QUEUE_HEAD * skb_head, IN RTK_BUFFER * skb)
{
    RtbQueueTail(skb_head, skb);
}

static RTK_BUFFER* skb_dequeue_head(IN RTB_QUEUE_HEAD * skb_head)
{
    return RtbDequeueHead(skb_head);
}

static RTK_BUFFER* skb_dequeue_tail(IN RTB_QUEUE_HEAD * skb_head)
{
    return RtbDequeueTail(skb_head);
}

static u32 skb_queue_get_length(IN RTB_QUEUE_HEAD * skb_head)
{
    return RtbGetQueueLen(skb_head);
}


/**
* Add "d" into crc scope, caculate the new crc value
*
* @param crc crc data
* @param d one byte data
*/
static void h5_crc_update(u16 *crc, u8 d)
{
    u16 reg = *crc;

    reg = (reg >> 4) ^ crc_table[(reg ^ d) & 0x000f];
    reg = (reg >> 4) ^ crc_table[(reg ^ (d >> 4)) & 0x000f];

    *crc = reg;
}


/**
* Get crc data.
*
* @param h5 realtek h5 struct
* @return crc data
*/
static u16 h5_get_crc(tHCI_H5_CB *h5)
{
   u16 crc = 0;
   u8 * data = skb_get_data(h5->rx_skb) + skb_get_data_length(h5->rx_skb) - 2;
   crc = data[1] + (data[0] << 8);
   return crc;
}

/**
* Just add 0xc0 at the end of skb,
* we can also use this to add 0xc0 at start while there is no data in skb
*
* @param skb socket buffer
*/
static void h5_slip_msgdelim(sk_buff *skb)
{
    const unsigned char pkt_delim = 0xc0;;
    osi_memcpy((u8*)skb_put(skb, 1), (u8*)&pkt_delim, 1);
}

/**
* Slip ecode one byte in h5 proto, as follows:
* 0xc0 -> 0xdb, 0xdc
* 0xdb -> 0xdb, 0xdd
* 0x11 -> 0xdb, 0xde
* 0x13 -> 0xdb, 0xdf
* others will not change
*
* @param skb socket buffer
* @c pure data in the one byte
*/
static void h5_slip_one_byte(sk_buff *skb, u8 unencode_form)
{
    const unsigned char esc_c0[2] = { 0xdb, 0xdc };
    const unsigned char esc_db[2] = { 0xdb, 0xdd };
    const unsigned char esc_11[2] = { 0xdb, 0xde };
    const unsigned char esc_13[2] = { 0xdb, 0xdf };

    switch (unencode_form)
    {
    case 0xc0:
        osi_memcpy(skb_put(skb, 2), &esc_c0, 2);
        break;
    case 0xdb:
        osi_memcpy(skb_put(skb, 2), &esc_db, 2);
        break;

    case 0x11:
    {
        if(rtk_h5.oof_flow_control)
        {
            osi_memcpy(skb_put(skb, 2), &esc_11, 2);
        }
        else
        {
            osi_memcpy(skb_put(skb, 1), &unencode_form, 1);
        }
    }
    break;

    case 0x13:
    {
        if(rtk_h5.oof_flow_control)
        {
            osi_memcpy(skb_put(skb, 2), &esc_13, 2);
        }
        else
        {
            osi_memcpy(skb_put(skb, 1), &unencode_form, 1);
        }
    }
    break;

    default:
        osi_memcpy(skb_put(skb, 1), &unencode_form, 1);
    }
}

/**
* Decode one byte in h5 proto, as follows:
* 0xdb, 0xdc -> 0xc0
* 0xdb, 0xdd -> 0xdb
* 0xdb, 0xde -> 0x11
* 0xdb, 0xdf -> 0x13
* others will not change
*
* @param h5 realtek h5 struct
* @byte pure data in the one byte
*/
static void h5_unslip_one_byte(tHCI_H5_CB *h5, unsigned char byte)
{
    const u8 c0 = 0xc0, db = 0xdb;
    const u8 oof1 = 0x11, oof2 = 0x13;
    u8 *hdr = (u8 *)skb_get_data(h5->rx_skb);

    if (H5_ESCSTATE_NOESC == h5->rx_esc_state)
    {
        if (0xdb == byte)
        {
            h5->rx_esc_state = H5_ESCSTATE_ESC;
        }
        else
        {
            osi_memcpy(skb_put(h5->rx_skb, 1), &byte, 1);
            //Check Pkt Header's CRC enable bit
            if (H5_HDR_CRC(hdr) && h5->rx_state != H5_W4_CRC)
            {
                h5_crc_update(&h5->message_crc, byte);
            }
            h5->rx_count--;
        }
    }
    else if(H5_ESCSTATE_ESC == h5->rx_esc_state)
    {
        switch (byte)
        {
        case 0xdc:
            osi_memcpy(skb_put(h5->rx_skb, 1), &c0, 1);
            if (H5_HDR_CRC(hdr) && h5->rx_state != H5_W4_CRC)
                h5_crc_update(&h5-> message_crc, 0xc0);
            h5->rx_esc_state = H5_ESCSTATE_NOESC;
            h5->rx_count--;
            break;
        case 0xdd:
            osi_memcpy(skb_put(h5->rx_skb, 1), &db, 1);
             if (H5_HDR_CRC(hdr) && h5->rx_state != H5_W4_CRC)
                h5_crc_update(&h5-> message_crc, 0xdb);
            h5->rx_esc_state = H5_ESCSTATE_NOESC;
            h5->rx_count--;
            break;
        case 0xde:
            osi_memcpy(skb_put(h5->rx_skb, 1), &oof1, 1);
            if (H5_HDR_CRC(hdr) && h5->rx_state != H5_W4_CRC)
                h5_crc_update(&h5-> message_crc, oof1);
            h5->rx_esc_state = H5_ESCSTATE_NOESC;
            h5->rx_count--;
            break;
        case 0xdf:
            osi_memcpy(skb_put(h5->rx_skb, 1), &oof2, 1);
            if (H5_HDR_CRC(hdr) && h5->rx_state != H5_W4_CRC)
                h5_crc_update(&h5-> message_crc, oof2);
            h5->rx_esc_state = H5_ESCSTATE_NOESC;
            h5->rx_count--;
            break;
        default:
            RTK_ERROR("Error: Invalid byte %02x after esc byte \n", byte);
            skb_free(&h5->rx_skb);
            h5->rx_skb = NULL;
            h5->rx_state = H5_W4_PKT_DELIMITER;
            h5->rx_count = 0;
            break;
        }
    }
}
/**
* Prepare h5 packet, packet format as follow:
*  | LSB 4 octets  | 0 ~4095| 2 MSB
*  |packet header | payload | data integrity check |
*
* pakcket header fromat is show below:
*  | LSB 3 bits         | 3 bits             | 1 bits                       | 1 bits          |
*  | 4 bits     | 12 bits        | 8 bits MSB
*  |sequence number | acknowledgement number | data integrity check present | reliable packet |
*  |packet type | payload length | header checksum
*
* @param h5 realtek h5 struct
* @param data pure data
* @param len the length of data
* @param pkt_type packet type
* @return socket buff after prepare in h5 proto
*/
static sk_buff * h5_prepare_pkt(tHCI_H5_CB *h5, u8 *data, signed long len, u8 pkt_type)
{
    sk_buff *nskb;
    u8 hdr[4];
    u16 H5_CRC_INIT(h5_txmsg_crc);
    int rel, i;
    RTK_DEBUG("HCI h5_prepare_pkt,len = %ld pkt_type=%s \n", len, dump_h5_packet_type(pkt_type));

    switch (pkt_type)
    {
    case HCI_COMMAND_PKT:
    case HCI_EVENT_PKT:
    rel = H5_RELIABLE_PKT;  // reliable
    break;
    case H5_ACK_PKT:
    case H5_VDRSPEC_PKT:
    case H5_LINK_CTL_PKT:
    rel = H5_UNRELIABLE_PKT;// unreliable
    break;
    default:
    RTK_ERROR("Unknown packet type \n");
    return NULL;
    }

    // Max len of packet: (original len +4(h5 hdr) +2(crc))*2
    //   (because bytes 0xc0 and 0xdb are escaped, worst case is
    //   when the packet is all made of 0xc0 and 0xdb :) )
    //   + 2 (0xc0 delimiters at start and end).

    nskb = skb_alloc((len + 6) * 2 + 2);
    if (!nskb)
    {
        RTK_DEBUG("nskb is NULL \n");
        return NULL;
    }

    //Add SLIP start byte: 0xc0
    h5_slip_msgdelim(nskb);
    // set AckNumber in SlipHeader
    hdr[0] = h5->rxseq_txack << 3;
    h5->is_txack_req = 0;

    if (H5_RELIABLE_PKT == rel)
    {
        RTK_DEBUG("Sending packet with seqno %u \n", h5->msgq_txseq);
        // set reliable pkt bit and SeqNumber
        hdr[0] |= 0x80 + h5->msgq_txseq;
        //RTK_DEBUG("Sending packet with seqno(%u)", h5->msgq_txseq);
        ++(h5->msgq_txseq);
        h5->msgq_txseq = (h5->msgq_txseq) & 0x07;
    }

    RTK_DEBUG("Sending packet wait %u\n", h5->rxseq_txack);
    // set DicPresent bit
    if (h5->use_crc)
    hdr[0] |= 0x40;

    // set packet type and payload length
    hdr[1] = ((len << 4) & 0xff) | pkt_type;
    hdr[2] = (u8)(len >> 4);
    // set checksum
    hdr[3] = ~(hdr[0] + hdr[1] + hdr[2]);

    // Put h5 header */
    for (i = 0; i < 4; i++)
    {
        h5_slip_one_byte(nskb, hdr[i]);

        if (h5->use_crc)
            h5_crc_update(&h5_txmsg_crc, hdr[i]);
    }

    // Put payload */
    for (i = 0; i < len; i++)
    {
        h5_slip_one_byte(nskb, data[i]);

       if (h5->use_crc)
       h5_crc_update(&h5_txmsg_crc, data[i]);
    }

    // Put CRC */
    if (h5->use_crc)
    {
        h5_txmsg_crc = bit_rev16(h5_txmsg_crc);
        h5_slip_one_byte(nskb, (u8) ((h5_txmsg_crc >> 8) & 0x00ff));
        h5_slip_one_byte(nskb, (u8) (h5_txmsg_crc & 0x00ff));
    }

    // Add SLIP end byte: 0xc0
    h5_slip_msgdelim(nskb);
    return nskb;
}
/**
* Removed controller acked packet from Host's unacked lists
*
* @param h5 realtek h5 struct
*/
static void h5_remove_acked_pkt(tHCI_H5_CB *h5)
{
    RT_LIST_HEAD* Head = NULL;
    RT_LIST_ENTRY* Iter = NULL, *Temp = NULL;
    RTK_BUFFER *skb = NULL;

    int pkts_to_be_removed = 0;
    int seqno = 0;
    int i = 0;

    seqno = h5->msgq_txseq;
    pkts_to_be_removed = RtbGetQueueLen(h5->unack);

    RTK_DEBUG("h5_remove_acked_pkt pkts_to_be_removed = %d, seqno = %d\n", pkts_to_be_removed, seqno);
    while (pkts_to_be_removed)
    {
        if (h5->rxack == seqno)
        break;

        pkts_to_be_removed--;
        seqno = (seqno - 1) & 0x07;
    }

    if (h5->rxack != seqno)
    {
        RTK_DEBUG("Peer acked invalid packet\n");
    }


    // remove ack'ed packet from bcsp->unack queue
    i = 0;//  number of pkts has been removed from un_ack queue.
    Head = (RT_LIST_HEAD *)(h5->unack);
    LIST_FOR_EACH_SAFELY(Iter, Temp, Head)
    {
        skb = LIST_ENTRY(Iter, sk_buff, List);
        if (i >= pkts_to_be_removed)
            break;

        skb_unlink(skb, h5->unack);
        skb_free(&skb);
        i++;
    }

    if (0 == skb_queue_get_length(h5->unack))
    {
        h5_stop_data_retrans_timer();
        rtk_h5.data_retrans_count = 0;
    }

    if (i != pkts_to_be_removed)
    {
        RTK_DEBUG("Removed only (%u) out of (%u) pkts \n", i, pkts_to_be_removed);
    }
}

/**
* Realtek send pure ack, send a packet only with an ack
*
* @param fd uart file descriptor
*
*/
static void hci_h5_send_pure_ack(void)
{

    //convert h4 data to h5
    u16 bytes_sent = 0;

    sk_buff *nskb = h5_prepare_pkt(&rtk_h5, NULL, 0, H5_ACK_PKT);
    if(nskb == NULL)
    {
        RTK_ERROR("h5_prepare_pkt allocate memory fail \n");
        return;
    }
    RTK_DEBUG("H5: --->>>send pure ack \n");
    u8 * data = skb_get_data(nskb);

#if H5_TRACE_DATA_ENABLE
    {
        u32 iTemp = 0;
        u32 iTempTotal = 16;

        RTK_DEBUG("H5 TX: length(%d) \n", skb_get_data_length(nskb));
        if(iTempTotal > skb_get_data_length(nskb))
        {
            iTempTotal = skb_get_data_length(nskb);
        }

        for(iTemp = 0; iTemp < iTempTotal; iTemp++)
        {
            RTK_DEBUG("0x%x \n", data[iTemp]);
        }
    }
#endif

    bytes_sent = h5_transmit_data(data, skb_get_data_length(nskb));
    RTK_DEBUG("bytes_sent(%d) \n", bytes_sent);

    skb_free(&nskb);

    return;

}

static void hci_h5_send_sync_req(void)
{
    u16 bytes_sent = 0;
    unsigned char    h5sync[2]     = {0x01, 0x7E};

    sk_buff *nskb = h5_prepare_pkt(&rtk_h5, h5sync, sizeof(h5sync), H5_LINK_CTL_PKT);
    if(nskb == NULL)
    {
        RTK_ERROR("h5_prepare_pkt allocate memory fail \n");
        return;
    }
    RTK_DEBUG("H5: --->>>send sync req \n");
    u8 * data = skb_get_data(nskb);
    RTK_DEBUG("H5: --->>>send sync req data = %p\n",data);
#if H5_TRACE_DATA_ENABLE
    {
        u32 iTemp = 0;
        u32 iTempTotal = 16;
        RTK_DEBUG("H5 TX: length(%d) \n", skb_get_data_length(nskb));
        if(iTempTotal > skb_get_data_length(nskb))
        {
            iTempTotal = skb_get_data_length(nskb);
        }
        for(iTemp = 0; iTemp < iTempTotal; iTemp++)
        {
            RTK_DEBUG("0x%x \n", data[iTemp]);
        }
    }
#endif

    bytes_sent = h5_transmit_data(data, skb_get_data_length(nskb));
    RTK_DEBUG("bytes_sent(%d) \n", bytes_sent);

    skb_free(&nskb);

    return;
}

static void hci_h5_send_sync_resp(void)
{
    u16 bytes_sent = 0;
    unsigned char h5syncresp[2] = {0x02, 0x7D};

    sk_buff *nskb = h5_prepare_pkt(&rtk_h5, h5syncresp, sizeof(h5syncresp), H5_LINK_CTL_PKT);
    if(nskb == NULL)
    {
        RTK_ERROR("h5_prepare_pkt allocate memory fail \n");
        return;
    }
    RTK_DEBUG("H5: --->>>send sync resp \n");
    u8 * data = skb_get_data(nskb);

#if H5_TRACE_DATA_ENABLE
    {
        u32 iTemp = 0;
        u32 iTempTotal = 16;
        RTK_DEBUG("H5 TX: length(%d) \n", skb_get_data_length(nskb));
        if(iTempTotal > skb_get_data_length(nskb))
        {
            iTempTotal = skb_get_data_length(nskb);
        }
        for(iTemp = 0; iTemp < iTempTotal; iTemp++)
        {
            RTK_DEBUG("0x%x \n", data[iTemp]);
        }
    }
#endif

    bytes_sent = h5_transmit_data(data, skb_get_data_length(nskb));
    RTK_DEBUG("bytes_sent(%d) \n", bytes_sent);

    skb_free(&nskb);

    return;
}

static void hci_h5_send_conf_req(void)
{
    u16 bytes_sent = 0;
    unsigned char h5conf[3] = {0x03, 0xFC, 0x14};

    sk_buff *nskb = h5_prepare_pkt(&rtk_h5, h5conf, sizeof(h5conf), H5_LINK_CTL_PKT);
    if(nskb == NULL)
    {
        RTK_ERROR("h5_prepare_pkt allocate memory fail \n");
        return;
    }
    RTK_DEBUG("H5: --->>>send conf req \n");
    u8 * data = skb_get_data(nskb);

#if H5_TRACE_DATA_ENABLE
    {
        u32 iTemp = 0;
        u32 iTempTotal = 16;
        RTK_DEBUG("H5 TX: length(%d)\n", skb_get_data_length(nskb));
        if(iTempTotal > skb_get_data_length(nskb))
        {
            iTempTotal = skb_get_data_length(nskb);
        }
        for(iTemp = 0; iTemp < iTempTotal; iTemp++)
        {
            RTK_DEBUG("0x%x\n", data[iTemp]);
        }
    }
#endif

    bytes_sent = h5_transmit_data(data, skb_get_data_length(nskb));
    RTK_DEBUG("bytes_sent(%d) \n", bytes_sent);

    skb_free(&nskb);

    return;
}


static void hci_h5_send_conf_resp(void)
{
    u16 bytes_sent = 0;
    unsigned char h5confresp[2] = {0x04, 0x7B};

    sk_buff *nskb = h5_prepare_pkt(&rtk_h5, h5confresp, sizeof(h5confresp), H5_LINK_CTL_PKT);
    if(nskb == NULL)
    {
        RTK_ERROR("h5_prepare_pkt allocate memory fail \n");
        return;
    }
    RTK_DEBUG("H5: --->>>send conf resp \n");
    u8 * data = skb_get_data(nskb);

#if H5_TRACE_DATA_ENABLE
    {
        u32 iTemp = 0;
        u32 iTempTotal = 16;
        RTK_DEBUG("H5 TX: length(%d) \n", skb_get_data_length(nskb));
        if(iTempTotal > skb_get_data_length(nskb))
        {
            iTempTotal = skb_get_data_length(nskb);
        }
        for(iTemp = 0; iTemp < iTempTotal; iTemp++)
        {
            RTK_DEBUG("0x%x \n", data[iTemp]);
        }
    }
#endif

    bytes_sent = h5_transmit_data(data, skb_get_data_length(nskb));
    RTK_DEBUG("bytes_sent(%d) \n", bytes_sent);

    skb_free(&nskb);

    return;
}

static void rtk_notify_hw_h5_init_result(void)
{
    RTK_DEBUG("rtk_notify_hw_h5_init_result \n");
    if(rtk_h5.cback_h5sync)
        rtk_h5.cback_h5sync(NULL);
}


static sk_buff * h5_dequeue(void)
{
    sk_buff *skb = NULL;
    //   First of all, check for unreliable messages in the queue,
    //   since they have higher priority
    if ((skb = (sk_buff*)skb_dequeue_head(rtk_h5.unrel)) != NULL)
    {
        sk_buff *nskb = h5_prepare_pkt(&rtk_h5,
                                         skb_get_data(skb),
                                         skb_get_data_length(skb),
                                         skb_get_pkt_type(skb));
        if (nskb)
        {
            skb_free(&skb);
            return nskb;
        }
        else
        {
            skb_queue_head(rtk_h5.unrel, skb);
        }
    }
    //   Now, try to send a reliable pkt. We can only send a
    //   reliable packet if the number of packets sent but not yet ack'ed
    //   is < than the winsize

//    RTK_DEBUG("RtbGetQueueLen(rtk_h5.unack) = (%d), sliding_window_size = (%d)", RtbGetQueueLen(rtk_h5.unack), rtk_h5.sliding_window_size);

    if (RtbGetQueueLen(rtk_h5.unack)< rtk_h5.sliding_window_size &&
        (skb = (sk_buff *)skb_dequeue_head(rtk_h5.rel)) != NULL)
    {
        sk_buff *nskb = h5_prepare_pkt(&rtk_h5,
                                         skb_get_data(skb),
                                         skb_get_data_length(skb),
                                         skb_get_pkt_type(skb));
        if (nskb)
        {
            skb_queue_tail(rtk_h5.unack, skb);
            h5_start_data_retrans_timer();
            return nskb;
        }
        else
        {
            skb_queue_head(rtk_h5.rel, skb);
        }
    }
    //   We could not send a reliable packet, either because there are
    //   none or because there are too many unack'ed packets. Did we receive
    //   any packets we have not acknowledged yet
    if (rtk_h5.is_txack_req)
    {
        // if so, craft an empty ACK pkt and send it on BCSP unreliable
        // channel
        sk_buff *nskb = h5_prepare_pkt(&rtk_h5, NULL, 0, H5_ACK_PKT);
        RTK_DEBUG("h5_dequeue send pure ack packet! \n");
        return nskb;
    }
    // We have nothing to send
    return NULL;
}

int h5_enqueue(IN sk_buff *skb)
{
    //Pkt length must be less than 4095 bytes
    if (skb_get_data_length(skb) > 0xFFF)
    {
        RTK_ERROR("skb len > 0xFFF \n");
        skb_free(&skb);
        return 0;
    }

    switch (skb_get_pkt_type(skb))
    {
    case HCI_COMMAND_PKT:
        skb_queue_tail(rtk_h5.rel, skb);
        break;


    case H5_LINK_CTL_PKT:
    case H5_ACK_PKT:
    case H5_VDRSPEC_PKT:
        skb_queue_tail(rtk_h5.unrel, skb);/* 3-wire LinkEstablishment*/
        break;
    default:
        skb_free(&skb);
        break;
    }
    return 0;
}


static u16 h5_wake_up(void)
{
    u16 bytes_sent = 0;
    sk_buff *skb = NULL;
    u8 * data = NULL;
    u32 data_len = 0;

    RTK_DEBUG("h5_wake_up \n");
    while (NULL != (skb = h5_dequeue()))
    {
        data = skb_get_data(skb);
        data_len = skb_get_data_length(skb);

        //we adopt the hci_h5 interface to send data
        bytes_sent = h5_transmit_data(data, data_len);

        RTK_DEBUG("bytes_sent(%d) \n", bytes_sent);

#if H5_TRACE_DATA_ENABLE
        {
            u32 iTemp = 0;
            u32 iTempTotal = 16;
            RTK_DEBUG("H5 TX: length(%d) \n", data_len);
            if(iTempTotal > data_len)
            {
                iTempTotal = data_len;
            }
            for(iTemp = 0; iTemp < iTempTotal; iTemp++)
            {
                RTK_DEBUG("0x%x \n", data[iTemp]);
            }
        }
#endif
        skb_free(&skb);
    }

    return bytes_sent;
}


void h5_process_ctl_pkts(void)
{
    //process h5 link establish
    u8 cfg;

    tHCI_H5_CB *p_cb = &rtk_h5;
    sk_buff * skb = rtk_h5.rx_skb;

    RTK_DEBUG("h5_process_ctl_pkts \n");
    static const unsigned char  h5sync[2]       = {0x01, 0x7E},
                                h5syncresp[2]   = {0x02, 0x7D},
                                h5conf[3]       = {0x03, 0xFC, 0x14},
                                h5confresp[2]   = {0x04, 0x7B},
                                h5InitOk[2]     = {0xF1, 0xF1};

    u8 *ph5_payload = NULL;
    ph5_payload = (u8 *)(p_cb->p_rcv_msg + 1);


    if(rtk_h5.link_estab_state == H5_UNINITIALIZED) {  //sync
        if (!osi_memcmp(skb_get_data(skb), h5sync, 2))
        {
            RTK_DEBUG("H5: <<<---recv sync req \n");
            hci_h5_send_sync_resp();
        }
        else if (!osi_memcmp(skb_get_data(skb), h5syncresp, 2))
        {
            RTK_DEBUG("H5: <<<---recv sync resp \n");
            h5_stop_sync_retrans_timer();
            rtk_h5.sync_retrans_count  = 0;
            rtk_h5.link_estab_state = H5_INITIALIZED;

            //send config req
            hci_h5_send_conf_req();
            h5_start_conf_retrans_timer();
        }

    }
    else if(rtk_h5.link_estab_state == H5_INITIALIZED) {  //config
        if (!osi_memcmp(skb_get_data(skb), h5sync, 0x2)) {

            RTK_DEBUG("H5: <<<---recv sync req in H5_INITIALIZED \n");
            hci_h5_send_sync_resp();
        }
        else if (!osi_memcmp(skb_get_data(skb), h5conf, 0x2)) {
             RTK_DEBUG("H5: <<<---recv conf req \n");
             hci_h5_send_conf_resp();
        }
        else if (!osi_memcmp(skb_get_data(skb), h5confresp,  0x2)) {
            RTK_DEBUG("H5: <<<---recv conf resp \n");
            h5_stop_conf_retrans_timer();
            rtk_h5.conf_retrans_count  = 0;

            rtk_h5.link_estab_state = H5_ACTIVE;
            //notify hw to download patch
            osi_memcpy(&cfg, skb_get_data(skb)+2, H5_CFG_SIZE);
            rtk_h5.sliding_window_size = H5_CFG_SLID_WIN(cfg);
            rtk_h5.oof_flow_control = H5_CFG_OOF_CNTRL(cfg);
            rtk_h5.dic_type = H5_CFG_DIC_TYPE(cfg);
            RTK_DEBUG("rtk_h5.sliding_window_size(%d), oof_flow_control(%d), dic_type(%d) \n",
            rtk_h5.sliding_window_size, rtk_h5.oof_flow_control, rtk_h5.dic_type);
         if(rtk_h5.dic_type)
            rtk_h5.use_crc = 1;

            rtk_notify_hw_h5_init_result();
        }
        else {
            RTK_DEBUG("H5_INITIALIZED receive event, ingnore \n");
        }
    }
    else if(rtk_h5.link_estab_state == H5_ACTIVE) {
        if (!osi_memcmp(skb_get_data(skb), h5sync, 0x2)) {

            RTK_DEBUG("H5: <<<---recv sync req in H5_ACTIVE \n");
            hci_h5_send_sync_resp();
            RTK_DEBUG("H5 : H5_ACTIVE transit to H5_UNINITIALIZED \n");
            rtk_h5.link_estab_state = H5_UNINITIALIZED;
            hci_h5_send_sync_req();
            h5_start_sync_retrans_timer();
        }
        else if (!osi_memcmp(skb_get_data(skb), h5conf, 0x2)) {
             RTK_DEBUG("H5: <<<---recv conf req in H5_ACTIVE \n");
             hci_h5_send_conf_resp();
        }
        else if (!osi_memcmp(skb_get_data(skb), h5confresp,  0x2)) {
            RTK_DEBUG("H5: <<<---recv conf resp in H5_ACTIVE, discard \n");
        }
        else {
            RTK_DEBUG("H5_ACTIVE receive unknown link control msg, ingnore \n");
        }

    }
}


/*******************************************************************************
**
** Function         internal_event_intercept_h5
**
** Description      This function is called to parse received HCI event and
**                  - update the Num_HCI_Command_Packets
**                  - intercept the event if it is the result of an early
**                    issued internal command.
**
** Returns          TRUE : if the event had been intercepted for internal process
**                  FALSE : send this event to core stack
**
*******************************************************************************/
u8 internal_event_intercept_h5(void)
{
    u8 internal_command = 0;//if it is internal event, you need to set internal_command = 1;
    tHCI_H5_CB *p_cb = &rtk_h5;
    //sk_buff * skb = rtk_h5.rx_skb;
    u8 *ph5_payload = NULL;
    ph5_payload = (u8 *)(p_cb->p_rcv_msg + 1);

    //process fw change baudrate and patch download
    u8     *p;
    u8     event_code;
    u16    opcode, len;
    p = (u8 *)(p_cb->p_rcv_msg + 1);

    event_code = *p++;
    len = *p++;
    RTK_DEBUG("internal_event_intercept_h5 event_code(0x%x) \n", event_code);
#if 1
    if (event_code == HCI_COMMAND_COMPLETE_EVT)
    {
        internal_command = 1;
        num_hci_cmd_pkts = *p++;
        STREAM_TO_UINT16(opcode, p);
        RTK_DEBUG("event_code(0x%x)  opcode (0x%x) p_cb->int_cmd_rsp_pending %d\n", event_code,opcode,p_cb->int_cmd_rsp_pending);

        if (p_cb->int_cmd_rsp_pending > 0)
        {
            RTK_DEBUG("CommandCompleteEvent for command (0x%04X) \n", opcode);
            if (opcode == p_cb->int_cmd[p_cb->int_cmd_rd_idx].opcode)
            {
                //ONLY HANDLE H5 INIT CMD COMMAND COMPLETE EVT
                if(opcode == HCI_VSC_UPDATE_BAUDRATE)
                {
                    //need to set a timer, add wait for retransfer packet from controller.
                    //if there is no packet rx from controller, we can assure baudrate change success.
                    RTK_DEBUG("CommandCompleteEvent for command 2 h5_start_wait_controller_baudrate_ready_timer (0x%04X) \n", opcode);
                    h5_start_wait_controller_baudrate_ready_timer();
                }
                else
                {
                    if (p_cb->int_cmd[p_cb->int_cmd_rd_idx].cback != NULL)
                    {
                        RTK_DEBUG("CommandCompleteEvent for command (0x%04X) p_cb->int_cmd[p_cb->int_cmd_rd_idx].cback(p_cb->p_rcv_msg) \n", opcode);
                        p_cb->int_cmd[p_cb->int_cmd_rd_idx].cback(p_cb->p_rcv_msg);
                    }
                    else
                    {
                        RTK_DEBUG("CommandCompleteEvent for command Missing cback function buffer_allocator->free(p_cb->p_rcv_msg) (0x%04x) \n", opcode);
                        osi_free(p_cb->p_rcv_msg);
                    }
                }

                p_cb->int_cmd_rd_idx = ((p_cb->int_cmd_rd_idx+1) & INT_CMD_PKT_IDX_MASK);
                p_cb->int_cmd_rsp_pending--;
            }
        }
    }
#endif
    else if (event_code == HCI_COMMAND_STATUS_EVT)
    {
        internal_command = 1;
        num_hci_cmd_pkts = *(++p);
        STREAM_TO_UINT16(opcode, p);
        osi_free(p_cb->p_rcv_msg);
    }

    return internal_command;

}


/**
* Check if it's a hci frame, if it is, complete it with response or parse the cmd complete event
*
* @param skb socket buffer
*
*/
static void hci_recv_frame(sk_buff *skb, u8 pkt_type)
{
    u8 intercepted = FALSE;
    u32 data_len = skb_get_data_length(skb);

    RTK_DEBUG("hci_recv_frame RX: length = %d \n", data_len);

#if H5_TRACE_DATA_ENABLE
    u8 *data = skb_get_data(skb);
    {
        u32 iTemp = 0;
        u32 iTempTotal = 16;
        RTK_DEBUG("H5 RX: length(%d) \n", data_len);
        if(iTempTotal > data_len)
        {
            iTempTotal = data_len;
        }
        for(iTemp = 0; iTemp < iTempTotal; iTemp++)
        {
            RTK_DEBUG("0x%x \n", data[iTemp]);
        }
    }
#endif
    //we only intercept evt packet here
    if(pkt_type == HCI_EVENT_PKT)
    {
        intercepted = internal_event_intercept_h5();
    }
}


static char * dump_h5_packet_type(u8 pkt_type)
{
    switch(pkt_type) {
        case H5_ACK_PKT:
            return "H5_ACK_PKT";
        case HCI_EVENT_PKT:
            return "HCI_EVENT_PKT";
        case H5_VDRSPEC_PKT:
            return "H5_VDRSPEC_PKT";
        case HCI_COMMAND_PKT:
            return "HCI_COMMAND_PKT";
        case HCI_ACLDATA_PKT:
            return "HCI_ACLDATA_PKT";
        case HCI_SCODATA_PKT:
            return "HCI_SCODATA_PKT";
        case H5_LINK_CTL_PKT:
            return "H5_LINK_CTL_PKT";
        default :
            return "unknown h5 packet type!";
    }
}


/**
* after rx data is parsed, and we got a rx frame saved in h5->rx_skb,
* this routinue is called.
* things todo in this function:
* 1. check if it's a hci frame, if it is, complete it with response or ack
* 2. see the ack number, free acked frame in queue
* 3. reset h5->rx_state, set rx_skb to null.
*
* @param h5 realtek h5 struct
*
*/
static void h5_complete_rx_pkt(tHCI_H5_CB *h5)
{
    int pass_up = 1;
    u16 eventtype = 0;
    u8 *h5_hdr = NULL;
    u8 complete_pkt = TRUE;
    u8 pkt_type = 0;
    //tHCI_H5_CB *p_cb=&rtk_h5;

    h5_hdr = (u8 *)skb_get_data(h5->rx_skb);
    RTK_DEBUG("h5_complete_rx_pkt SeqNumber(%d), AckNumber(%d) \n", H5_HDR_SEQ(h5_hdr), H5_HDR_ACK(h5_hdr));

    if (H5_HDR_RELIABLE(h5_hdr))
    {
        RTK_DEBUG("h5_complete_rx_pkt Received reliable seqno %u from card \n", h5->rxseq_txack);
        h5->rxseq_txack = H5_HDR_SEQ(h5_hdr) + 1;
        h5->rxseq_txack %= 8;
        h5->is_txack_req = 1;
    // send down an empty ack if needed.
        h5_wake_up();
    }

    h5->rxack = H5_HDR_ACK(h5_hdr);
    pkt_type = H5_HDR_PKT_TYPE(h5_hdr);
    RTK_DEBUG("h5_complete_rx_pkt pkt_type = %s \n", dump_h5_packet_type(pkt_type));
    switch (pkt_type)
    {
        case HCI_EVENT_PKT:
            pass_up = 1;
            break;

        case HCI_COMMAND_PKT:
            pass_up = 1;
            break;

        case H5_LINK_CTL_PKT:
            pass_up = 0;
        break;

        case H5_ACK_PKT:
            pass_up = 0;
            break;

        default:
          RTK_ERROR("Unknown pkt type(%d) \n", H5_HDR_PKT_TYPE(h5_hdr));
          pass_up = 0;
          break;
    }

    // remove h5 header and send packet to hci
    h5_remove_acked_pkt(h5);

    if(H5_HDR_PKT_TYPE(h5_hdr) == H5_LINK_CTL_PKT)
    {

        skb_pull(h5->rx_skb, H5_HDR_SIZE);
        h5_process_ctl_pkts();
    }

    // decide if we need to pass up.
    if (pass_up)
    {
        skb_pull(h5->rx_skb, H5_HDR_SIZE);

        //send command or complete acl data it to bluedroid stack
        if(complete_pkt)
        {
            u16 len = 0;
            sk_buff * skb_complete_pkt = h5->rx_skb;

            /* Allocate a buffer for message */

            len = BT_HC_HDR_SIZE + skb_get_data_length(skb_complete_pkt);
            h5->p_rcv_msg = (HC_BT_HDR *) osi_malloc(len);

            if (h5->p_rcv_msg)
            {
                /* Initialize buffer with received h5 data */
                h5->p_rcv_msg->offset = 0;
                h5->p_rcv_msg->layer_specific = 0;
                h5->p_rcv_msg->event = eventtype;
                h5->p_rcv_msg->len = skb_get_data_length(skb_complete_pkt);
                osi_memcpy((u8 *)(h5->p_rcv_msg + 1), skb_get_data(skb_complete_pkt), skb_get_data_length(skb_complete_pkt));
            }

            hci_recv_frame(skb_complete_pkt, pkt_type);
        }

    }


    skb_free(&h5->rx_skb);

    h5->rx_state = H5_W4_PKT_DELIMITER;
    h5->rx_skb = NULL;
}

static char * dump_h5_parse_state(tH5_RX_STATE state)
{
    switch(state) {
        case H5_W4_PKT_DELIMITER:
            return "H5_W4_PKT_DELIMITER";
        case H5_W4_PKT_START:
            return "H5_W4_PKT_START";
        case H5_W4_HDR:
            return "H5_W4_HDR";
        case H5_W4_DATA:
            return "H5_W4_DATA";
        case H5_W4_CRC:
            return "H5_W4_CRC";
        default :
            return "unknown h5 parse state!";
    }
}

/**
* Parse the receive data in h5 proto.
*
* @param h5 realtek h5 struct
* @param data point to data received before parse
* @param count num of data
* @return reserved count
*/
static int h5_recv(tHCI_H5_CB *h5, u8 *data, int count)
{
//   unsigned char *ptr;
    u8 *ptr;
    u8 * skb_data = NULL;
    u8 *hdr = NULL;

    ptr = (u8 *)data;
    RTK_DEBUG("count %d rx_state %s rx_count %d data:0x%x \n", count, dump_h5_parse_state(h5->rx_state), h5->rx_count,*ptr);
#if H5_TRACE_DATA_ENABLE
    int iTemp = 0;
    int iTempTotal = 32;
    RTK_DEBUG("H5 RX: length(%d) \n", count);
    if(iTempTotal > count)
    {
        iTempTotal = count;
    }
    for(iTemp = 0; iTemp < iTempTotal; iTemp++)
    {
        RTK_DEBUG("0x%x \n", data[iTemp]);
    }
#endif

    while (count)
    {
        if (h5->rx_count)
        {
            if (*ptr == 0xc0)
            {
                RTK_ERROR("short h5 packet \n");
                skb_free(&h5->rx_skb);
                h5->rx_state = H5_W4_PKT_START;
                h5->rx_count = 0;
            } else
                h5_unslip_one_byte(h5, *ptr);

            ptr++; count--;
            continue;
        }

        RTK_DEBUG("h5_recv rx_state=%s  count = %d \n", dump_h5_parse_state(h5->rx_state), count);
        switch (h5->rx_state)
        {
        case H5_W4_HDR:
            // check header checksum. see Core Spec V4 "3-wire uart" page 67
            skb_data = skb_get_data(h5->rx_skb);
            hdr = (u8 *)skb_data;

            if ((0xff & (u8) ~ (skb_data[0] + skb_data[1] +
                                   skb_data[2])) != skb_data[3])
            {
                RTK_ERROR("h5 hdr checksum error!!! \n");
                skb_free(&h5->rx_skb);
                h5->rx_state = H5_W4_PKT_DELIMITER;
                h5->rx_count = 0;
                continue;
            }

            if (H5_HDR_RELIABLE(hdr)
                && (H5_HDR_SEQ(hdr) != h5->rxseq_txack))
            {
                RTK_ERROR("Out-of-order packet arrived, got(%u)expected(%u) \n",
                   H5_HDR_SEQ(hdr), h5->rxseq_txack);
                h5->is_txack_req = 1;
                h5_wake_up();

                skb_free(&h5->rx_skb);
                h5->rx_state = H5_W4_PKT_DELIMITER;
                h5->rx_count = 0;

                continue;
            }
            h5->rx_state = H5_W4_DATA;
            //payload length: May be 0
            h5->rx_count = H5_HDR_LEN(hdr);
            continue;
        case H5_W4_DATA:
            hdr = (u8 *)skb_get_data(h5->rx_skb);
            if (H5_HDR_CRC(hdr))
            {   // pkt with crc /
                h5->rx_state = H5_W4_CRC;
                h5->rx_count = 2;
            }
            else
            {
                h5_complete_rx_pkt(h5); //Send ACK
                RTK_DEBUG("--------> H5_W4_DATA ACK\n");
            }
            continue;

        case H5_W4_CRC:
            if (bit_rev16(h5->message_crc) != h5_get_crc(h5))
            {
                RTK_ERROR("Checksum failed, computed(%04x)received(%04x) \n",
                    bit_rev16(h5->message_crc), h5_get_crc(h5));
                skb_free(&h5->rx_skb);
                h5->rx_state = H5_W4_PKT_DELIMITER;
                h5->rx_count = 0;
                continue;
            }
            skb_trim(h5->rx_skb, skb_get_data_length(h5->rx_skb) - 2);
            h5_complete_rx_pkt(h5);
            continue;

        case H5_W4_PKT_DELIMITER:
            switch (*ptr)
            {
            case 0xc0:
                h5->rx_state = H5_W4_PKT_START;
                break;
            default:
                break;
            }
            ptr++; count--;
            break;

        case H5_W4_PKT_START:
            switch (*ptr)
            {
            case 0xc0:
                ptr++; count--;
                break;
            default:
                h5->rx_state = H5_W4_HDR;
                h5->rx_count = 4;
                h5->rx_esc_state = H5_ESCSTATE_NOESC;
                H5_CRC_INIT(h5->message_crc);

                // Do not increment ptr or decrement count
                // Allocate packet. Max len of a H5 pkt=
                // 0xFFF (payload) +4 (header) +2 (crc)
                h5->rx_skb = skb_alloc(0x1005);
                if (!h5->rx_skb)
                {
                    h5->rx_state = H5_W4_PKT_DELIMITER;
                    h5->rx_count = 0;
                    return 0;
                }
                break;
            }
            break;
        }
    }
    return count;
}

/******************************************************************************
**  Static functions
******************************************************************************/
static void data_retransfer_function(void)
{
    u32 data_len = 0;
    u8* pdata = NULL;
    u32 i = 0;
    sk_buff *skb;

    RTK_ERROR("retransmitting (%u) pkts, retransfer count(%d) \n", skb_queue_get_length(rtk_h5.unack), rtk_h5.data_retrans_count);
    if(rtk_h5.data_retrans_count < DATA_RETRANS_COUNT) {
        while ((skb = skb_dequeue_tail(rtk_h5.unack)) != NULL)
        {
            data_len = skb_get_data_length(skb);
            pdata = skb_get_data(skb);
            if(data_len > 16)
                data_len=16;

            for(i = 0 ; i < data_len; i++)
                RTK_DEBUG("0x%02x \n", pdata[i]);

            rtk_h5.msgq_txseq = (rtk_h5.msgq_txseq - 1) & 0x07;
            skb_queue_head(rtk_h5.rel, skb);

        }
        rtk_h5.data_retrans_count++;
        h5_wake_up();
    }
}

/*****************************************************************************
**   HCI H5 INTERFACE FUNCTIONS
*****************************************************************************/

/*******************************************************************************
**
** Function        hci_h5_init
**
** Description     Initialize H5 module
**
** Returns         None
**
*******************************************************************************/
void hci_h5_init(void)
{
    RTK_DEBUG("hci_h5_init \n");

    osi_memset(&rtk_h5, 0, sizeof(tHCI_H5_CB));


    /* Per HCI spec., always starts with 1 */
    num_hci_cmd_pkts = 1;
    /* Give an initial values of Host Controller's ACL data packet length
     * Will update with an internal HCI(_LE)_Read_Buffer_Size request
     */

    h5_alloc_data_retrans_timer();
    h5_alloc_sync_retrans_timer();
    h5_alloc_conf_retrans_timer();
    h5_alloc_wait_controller_baudrate_ready_timer();
    h5_alloc_hw_init_ready_timer();

    rtk_h5.unack = RtbQueueInit();
    rtk_h5.rel = RtbQueueInit();
    rtk_h5.unrel = RtbQueueInit();

    rtk_h5.rx_state = H5_W4_PKT_DELIMITER;
    rtk_h5.rx_esc_state = H5_ESCSTATE_NOESC;
}

/*******************************************************************************
**
** Function        hci_h5_cleanup
**
** Description     Clean H5 module
**
** Returns         None
**
*******************************************************************************/
void hci_h5_cleanup(void)
{
    rtk_h5.cleanuping = 1;

    h5_free_data_retrans_timer();
    h5_free_sync_retrans_timer();
    h5_free_conf_retrans_timer();
    h5_free_wait_controller_baudrate_ready_timer();
    h5_free_hw_init_ready_timer();

    osi_rtk_mdelay(200);

    RtbQueueFree(rtk_h5.unack);
    RtbQueueFree(rtk_h5.rel);
    RtbQueueFree(rtk_h5.unrel);

    RTK_DEBUG("hci_h5_cleanup \n");

}





/*******************************************************************************
**
** Function        hci_h5_send_msg
**
** Description     Determine message type, set HCI H5 packet indicator, and
**                 send message through USERIAL driver
**
** Returns         None
**
*******************************************************************************/
void hci_h5_send_msg(HC_BT_HDR *p_msg)
{
    u8 type = 0;
    u16 bytes_to_send, lay_spec = 0;
    u8 *p = ((u8 *)(p_msg + 1)) + p_msg->offset;
    u16 event = p_msg->event & MSG_EVT_MASK;
    //u16 sub_event = p_msg->event & MSG_SUB_EVT_MASK;
    u16 bytes_sent;

/*
    u8 *pdata_h5 = NULL;
    u16 len_h5_data = 0;

    u8 *p_h5 = NULL;
    u32 iTemp = 0;
    u32 iTempTotal = 16;
*/
    sk_buff * skb = NULL;

    RTK_DEBUG("hci_h5_send_msg, len =%d \n", p_msg->len);
    RTK_DEBUG("p_msg->layer_specific 0x%04X, lay_spec:0x%04X \n",p_msg->layer_specific,lay_spec);

    if (event == MSG_STACK_TO_HC_HCI_ACL)
        type = HCI_ACLDATA_PKT;
    else if (event == MSG_STACK_TO_HC_HCI_SCO)
        type = HCI_SCODATA_PKT;
    else if (event == MSG_STACK_TO_HC_HCI_CMD)
        type = HCI_COMMAND_PKT;


    /* remember layer_specific because uart borrow
       one byte from layer_specific for packet type */
    lay_spec = p_msg->layer_specific;

    /* Put the HCI Transport packet type 1 byte before the message */
    p = ((u8 *)(p_msg + 1)) + p_msg->offset -1;

    switch (event) {
        case MSG_STACK_TO_HC_HCI_CMD :
            skb = skb_alloc_and_init(type, p+1, p_msg->len);
            h5_enqueue(skb);
        break;

        default:
            RTK_DEBUG("Don't support other event:%d now \n", event);
            osi_free(p_msg);
            return;
    }
    //

    p_msg->layer_specific = lay_spec;

    if (event == MSG_STACK_TO_HC_HCI_CMD)
    {
        num_hci_cmd_pkts--;

        /* If this is an internal Cmd packet, the layer_specific field would
         * have stored with the opcode of HCI command.
         * Retrieve the opcode from the Cmd packet.
         */
        p++;
        STREAM_TO_UINT16(lay_spec, p);
        RTK_DEBUG("HCI Command opcode(0x%04x) \n", lay_spec);
        if(lay_spec == 0x0c03)
        {
            RTK_DEBUG("RX HCI RESET Command, stop hw init timer \n");
            h5_stop_hw_init_ready_timer();
        }
    }

    RTK_DEBUG("p_msg->layer_specific 0x%04x, lay_spec:0x%04x \n",p_msg->layer_specific,lay_spec);
    if ((event == MSG_STACK_TO_HC_HCI_CMD)) {
       //For int_cm as H5 INIT cmd and Coex cmd ... just free it, while hold the other CMD
       if((rtk_h5.int_cmd_rsp_pending > 0) && (p_msg->layer_specific == lay_spec)){
         /* dealloc buffer of internal command */
        osi_free(p_msg);
       }
    } else {
        //For Acl sent complete, just free it
        osi_free(p_msg);
    }

    h5_wake_up();
    return;
}


/*******************************************************************************
**
** Function        hci_h5_parse_msg
**
** Description     Construct HCI EVENT/ACL packets and send them to stack once
**                 complete packet has been received.
**
** Returns         Number of need to be red bytes
**
*******************************************************************************/
u16  hci_h5_parse_msg(u8 *byte, u16 count)
{
    u16 bytes_needed = 0;
    u8     h5_byte;
    h5_byte  = *byte;
    //RTK_DEBUG("hci_h5_receive_msg byte:%d",h5_byte);
    h5_recv(&rtk_h5, &h5_byte, count);
    return 1;
}



/*******************************************************************************
**
** Function        hci_h5_receive_msg
**
** Description     Construct HCI EVENT/ACL packets and send them to stack once
**                 complete packet has been received.
**
** Returns         Number of read bytes
**
*******************************************************************************/
bool  hci_h5_rcv_and_chk_timer(void)
{
    static u8     h5_byte[500];
    u32 count = h5_receive_data(h5_byte);
    int i = 0;
    if(count) {
        h5_recv(&rtk_h5, h5_byte, count);
    }
    else {
        if(rtk_h5.timer_cb.total_num) {
            if((rtk_h5.timer_cb.timer_event & 0x01)) {
                if(rtk_h5.timer_h5_hw_init_ready)
                    rtk_h5.timer_h5_hw_init_ready--;
                else {
                    h5_hw_init_ready_timeout_handler();
                    return false;
                }
            }

            if((rtk_h5.timer_cb.timer_event & 0x02)) {
                if(rtk_h5.timer_sync_retrans)
                    rtk_h5.timer_sync_retrans--;
                else if(!h5_sync_retrans_timeout_handler()) {
                    return false;
                }
            }

            if((rtk_h5.timer_cb.timer_event & 0x04)) {
                if(rtk_h5.timer_conf_retrans)
                    rtk_h5.timer_conf_retrans--;
                else if(!h5_conf_retrans_timeout_handler()) {
                    return false;
                }
            }

            if((rtk_h5.timer_cb.timer_event & 0x08)) {
                if(rtk_h5.timer_data_retrans)
                    rtk_h5.timer_data_retrans--;
                else if(!h5_data_retrans_timeout_handler()) {
                    return false;
                }
            }

            if((rtk_h5.timer_cb.timer_event & 0x10)) {
                if(rtk_h5.timer_wait_ct_baudrate_ready)
                    rtk_h5.timer_wait_ct_baudrate_ready--;
                else if(!h5_wait_controller_baudrate_ready_timeout_handler()) {
                    return false;
                }
            }

        }
    }
    return true;
}


/*******************************************************************************
**
** Function        hci_h5_send_int_cmd
**
** Description     Place the internal commands (issued internally by vendor lib)
**                 in the tx_q.
**
** Returns         TRUE/FALSE
**
*******************************************************************************/
u8 hci_h5_send_int_cmd(u16 opcode, HC_BT_HDR *p_buf, tINT_CMD_CBACK p_cback)
{
   // u8 * p =  (u8 *) (p_buf + 1);
    RTK_DEBUG("hci_h5_send_int_cmd, rtk_h5.link_estab_state = %d \n", rtk_h5.link_estab_state);

    if(rtk_h5.link_estab_state == H5_UNINITIALIZED)
    {
        if(opcode == HCI_VSC_H5_INIT)
        {
            h5_start_hw_init_ready_timer();
            rtk_h5.cback_h5sync = p_cback;
            h5_start_sync_retrans_timer();
            hci_h5_send_sync_req();
        }
    }
    else if(rtk_h5.link_estab_state == H5_ACTIVE)
    {
        if(opcode == HCI_VSC_UPDATE_BAUDRATE)
            rtk_h5.cback_h5sync = p_cback;

        RTK_DEBUG("hci_h5_send_int_cmd(0x%x) \n", opcode);
        if (rtk_h5.int_cmd_rsp_pending > INT_CMD_PKT_MAX_COUNT)
        {
            RTK_ERROR("Allow only %d outstanding internal commands at a time [Reject 0x%04X] \n", INT_CMD_PKT_MAX_COUNT, opcode);
            return FALSE;
        }

        rtk_h5.int_cmd_rsp_pending++;
        rtk_h5.int_cmd[rtk_h5.int_cmd_wrt_idx].opcode = opcode;
        rtk_h5.int_cmd[rtk_h5.int_cmd_wrt_idx].cback = p_cback;
        rtk_h5.int_cmd_wrt_idx = ((rtk_h5.int_cmd_wrt_idx + 1) & INT_CMD_PKT_IDX_MASK);

        p_buf->layer_specific = opcode;

        if(opcode == HCI_VSC_UPDATE_BAUDRATE
            ||opcode == HCI_VSC_DOWNLOAD_FW_PATCH
            ||opcode == HCI_VSC_READ_ROM_VERSION
            ||opcode == HCI_VSC_READ_CHIP_TYPE
            ||opcode == HCI_READ_LMP_VERSION
            ||opcode == HCI_READ_BUFFER_SIZE
            ||opcode ==HCI_LE_READ_BUFFER_SIZE )
        {
            /* stamp signature to indicate an internal command */
        if(p_buf != NULL)
             hci_h5_send_msg(p_buf);
        }
    }


    return TRUE;
}

 /*******************************************************************************
 **
 ** Function        hci_h5_alloc
 **
 ** Description     hci h5 alloc buffer
 ** Returns         Number of buffer alloc
 **
 *******************************************************************************/
 void*  hci_h5_alloc(int size)
 {
    return osi_malloc(size);
 }

 /*******************************************************************************
 **
 ** Function        hci_h5_dealloc
 **
 ** Description     hci h5 dealloc buffer
 ** Returns         Number of buffer dealloc
 **
 *******************************************************************************/
void hci_h5_dealloc(void *p_buf)
 {
    osi_free(p_buf);
    p_buf = NULL;
    return ;
 }


static bool h5_data_retrans_timeout_handler() {
    RTK_DEBUG("h5_retransfer_timeout_handler \n");
    bool status = true;
    if(rtk_h5.cleanuping)
    {
        RTK_ERROR("H5 is cleanuping, EXIT here! \n");
        return false;
    }
    if(rtk_h5.data_retrans_count < DATA_RETRANS_COUNT) {
        data_retransfer_function();
        status = true;
    }
    else {
        RTK_ERROR("h5_data_retrans_timeout_handler stop! data_retrans_count = %d \n", rtk_h5.data_retrans_count);
        h5_stop_data_retrans_timer();
        status = false;
    }
    return status;
}

static bool h5_sync_retrans_timeout_handler(void) {
    RTK_DEBUG("h5_sync_retrans_timeout_handler \n");
    bool status = true;
    if(rtk_h5.cleanuping)
    {
        RTK_ERROR("H5 is cleanuping, EXIT here! \n");
        return false;
    }
    if(rtk_h5.sync_retrans_count < SYNC_RETRANS_COUNT)
    {
        h5_start_sync_retrans_timer();
        hci_h5_send_sync_req();
        rtk_h5.sync_retrans_count ++;
        status = true;
    }
    else
    {
        RTK_ERROR("h5_sync_retrans_timeout_handler stop! sync_retrans_count = %d \n",rtk_h5.sync_retrans_count);
        h5_stop_sync_retrans_timer();
        status = false;
    }
    return status;
}

static bool h5_conf_retrans_timeout_handler(void) {
    RTK_DEBUG("h5_conf_retrans_timeout_handler \n");
    bool status = true;
    if(rtk_h5.cleanuping)
    {
        RTK_ERROR("h5_conf_retrans_timeout_handler H5 is cleanuping, EXIT here! \n");
        return false;
    }

    RTK_DEBUG("Wait H5 Conf Resp timeout, %d times \n", rtk_h5.conf_retrans_count);
    if(rtk_h5.conf_retrans_count < CONF_RETRANS_COUNT)
    {
        h5_start_conf_retrans_timer();
        hci_h5_send_conf_req();
        rtk_h5.conf_retrans_count++;
        status = true;
    }
    else
    {
        RTK_ERROR("h5_conf_retrans_timeout_handler stop! conf_retrans_count = %d \n ", rtk_h5.conf_retrans_count);
        h5_stop_conf_retrans_timer();
        status = false;
    }
    return status;
}

static bool h5_wait_controller_baudrate_ready_timeout_handler(void) {
    RTK_DEBUG("h5_wait_ct_baundrate_ready_timeout_handler \n");
    bool status = true;
    if(rtk_h5.cleanuping)
    {
        RTK_ERROR("H5 is cleanuping, EXIT here! \n");
        return false;
    }
    RTK_DEBUG("No Controller retransfer, baudrate of controller ready \n");
    if (rtk_h5.cback_h5sync!= NULL)
    {
        h5_stop_wait_controller_baudrate_ready_timer();
        rtk_h5.cback_h5sync(rtk_h5.p_rcv_msg);
        status = true;
    }
    else
    {
        RTK_ERROR("h5_wait_ct_baundrate_ready_timeout_handler stop! \n");
        osi_free(rtk_h5.p_rcv_msg);
        status = false;
    }
    return status;
}

static bool h5_hw_init_ready_timeout_handler(void) {
    RTK_DEBUG("h5_hw_init_ready_timeout_handler \n");

    if(rtk_h5.cleanuping)
    {
        RTK_ERROR("H5 is cleanuping, EXIT here! \n");
    }
    RTK_ERROR("TIMER_H5_HW_INIT_READY timeout, kill restart BT \n");
    return false;
}


/*
** h5 data retrans timer functions
*/
void h5_alloc_data_retrans_timer(void)
 {
    rtk_h5.timer_data_retrans = 0;
    if((rtk_h5.timer_cb.timer_event & 0x08))
    {
        rtk_h5.timer_cb.timer_event &= (~0x08);
        rtk_h5.timer_cb.total_num--;
    }
 }

void h5_free_data_retrans_timer(void)
{
    rtk_h5.timer_data_retrans = 0;
    if((rtk_h5.timer_cb.timer_event & 0x08))
    {
        rtk_h5.timer_cb.timer_event &= (~0x08);
        rtk_h5.timer_cb.total_num--;
    }
}


void h5_start_data_retrans_timer(void)
{
    rtk_h5.timer_data_retrans = DATA_RETRANS_TIMEOUT_VALUE;
    if(!(rtk_h5.timer_cb.timer_event & 0x08))
    {
        rtk_h5.timer_cb.timer_event |= 0x08;
        rtk_h5.timer_cb.total_num++;
    }
}

void h5_stop_data_retrans_timer(void)
{
    rtk_h5.timer_data_retrans = 0;
    if((rtk_h5.timer_cb.timer_event & 0x08))
    {
        rtk_h5.timer_cb.timer_event &= (~0x08);
        rtk_h5.timer_cb.total_num--;
    }
}



/*
** h5 sync retrans timer functions
*/
void h5_alloc_sync_retrans_timer(void)
{
    rtk_h5.timer_sync_retrans = 0;
    if((rtk_h5.timer_cb.timer_event & 0x02))
    {
        rtk_h5.timer_cb.timer_event &= (~0x02);
        rtk_h5.timer_cb.total_num--;
    }
}

void h5_free_sync_retrans_timer(void)
{
    rtk_h5.timer_sync_retrans = 0;
    if((rtk_h5.timer_cb.timer_event & 0x02))
    {
        rtk_h5.timer_cb.timer_event &= (~0x02);
        rtk_h5.timer_cb.total_num--;
    }
}


void h5_start_sync_retrans_timer(void)
{
    rtk_h5.timer_sync_retrans = SYNC_RETRANS_TIMEOUT_VALUE;
    if(!(rtk_h5.timer_cb.timer_event & 0x02))
    {
        rtk_h5.timer_cb.timer_event |= 0x02;
        rtk_h5.timer_cb.total_num++;
    }
}

void h5_stop_sync_retrans_timer(void)
{
    rtk_h5.timer_sync_retrans = 0;
    if((rtk_h5.timer_cb.timer_event & 0x02))
    {
        rtk_h5.timer_cb.timer_event &= (~0x02);
        rtk_h5.timer_cb.total_num--;
    }
}


/*
** h5 config retrans timer functions
*/
void h5_alloc_conf_retrans_timer(void)
 {
    rtk_h5.timer_conf_retrans = 0;
    if((rtk_h5.timer_cb.timer_event & 0x04))
    {
        rtk_h5.timer_cb.timer_event &= (~0x04);
        rtk_h5.timer_cb.total_num--;
    }
 }

void h5_free_conf_retrans_timer(void)
{
    rtk_h5.timer_conf_retrans = 0;
    if((rtk_h5.timer_cb.timer_event & 0x04))
    {
        rtk_h5.timer_cb.timer_event &= (~0x04);
        rtk_h5.timer_cb.total_num--;
    }
}


void h5_start_conf_retrans_timer(void)
{
    rtk_h5.timer_conf_retrans = CONF_RETRANS_TIMEOUT_VALUE;
    if(!(rtk_h5.timer_cb.timer_event & 0x04))
    {
        rtk_h5.timer_cb.timer_event |= 0x04;
        rtk_h5.timer_cb.total_num++;
    }
}

void h5_stop_conf_retrans_timer(void)
{
    rtk_h5.timer_conf_retrans = 0;
    if((rtk_h5.timer_cb.timer_event & 0x04))
    {
        rtk_h5.timer_cb.timer_event &= (~0x04);
        rtk_h5.timer_cb.total_num--;
    }
}


/*
** h5 wait controller baudrate ready timer functions
*/
void h5_alloc_wait_controller_baudrate_ready_timer(void)
{
    rtk_h5.timer_wait_ct_baudrate_ready = 0;
    if((rtk_h5.timer_cb.timer_event & 0x10))
    {
        rtk_h5.timer_cb.timer_event &= (~0x10);
        rtk_h5.timer_cb.total_num--;
    }
 }

void h5_free_wait_controller_baudrate_ready_timer(void)
{
    rtk_h5.timer_wait_ct_baudrate_ready = 0;
    if((rtk_h5.timer_cb.timer_event & 0x10))
    {
        rtk_h5.timer_cb.timer_event &= (~0x10);
        rtk_h5.timer_cb.total_num--;
    }
}


void h5_start_wait_controller_baudrate_ready_timer(void)
{
    rtk_h5.timer_wait_ct_baudrate_ready = WAIT_CT_BAUDRATE_READY_TIMEOUT_VALUE;
    if(!(rtk_h5.timer_cb.timer_event & 0x10))
    {
        rtk_h5.timer_cb.timer_event |= 0x10;
        rtk_h5.timer_cb.total_num++;
    }
}

void h5_stop_wait_controller_baudrate_ready_timer(void)
{
    rtk_h5.timer_wait_ct_baudrate_ready = 0;
    if((rtk_h5.timer_cb.timer_event & 0x10))
    {
        rtk_h5.timer_cb.timer_event &= (~0x10);
        rtk_h5.timer_cb.total_num--;
    }
}


/*
** h5 hw init ready timer functions
*/
void h5_alloc_hw_init_ready_timer(void)
{
    rtk_h5.timer_h5_hw_init_ready = 0;
    if((rtk_h5.timer_cb.timer_event & 0x01))
    {
        rtk_h5.timer_cb.timer_event &= (~0x01);
        rtk_h5.timer_cb.total_num--;
    }
 }

void h5_free_hw_init_ready_timer(void)
{
    rtk_h5.timer_h5_hw_init_ready = 0;
    if((rtk_h5.timer_cb.timer_event & 0x01))
    {
        rtk_h5.timer_cb.timer_event &= (~0x01);
        rtk_h5.timer_cb.total_num--;
    }
}


void h5_start_hw_init_ready_timer(void)
{
    rtk_h5.timer_h5_hw_init_ready = H5_HW_INIT_READY_TIMEOUT_VALUE;
    if(!(rtk_h5.timer_cb.timer_event & 0x01))
    {
        rtk_h5.timer_cb.timer_event |= 0x01;
        rtk_h5.timer_cb.total_num++;
    }
}

void h5_stop_hw_init_ready_timer(void)
{
    rtk_h5.timer_h5_hw_init_ready = 0;
    if((rtk_h5.timer_cb.timer_event & 0x01))
    {
        rtk_h5.timer_cb.timer_event &= (~0x01);
        rtk_h5.timer_cb.total_num--;
    }
}


/******************************************************************************
**  HCI H5 Services interface table
******************************************************************************/

const tHCI_IF hci_h5_func_table =
{
    hci_h5_init,
    hci_h5_cleanup,
    hci_h5_send_int_cmd,
    hci_h5_rcv_and_chk_timer,
    hci_h5_alloc,
    hci_h5_dealloc
};

const tHCI_IF *hci_get_h5_interface() {
  return &hci_h5_func_table;
}


