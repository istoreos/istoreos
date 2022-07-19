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
 *  Filename:      hardware.c
 *
 *  Description:   Contains controller-specific functions, like
 *                      firmware patch download
 *                      low power mode operations
 *
 ******************************************************************************/
#include "../../osi/include/osi_include_int.h"
#include "../../osi/include/osi_include_ext.h"


/******************************************************************************
**  Constants &  Macros
******************************************************************************/
#define RTK_VERSION "5.0.0_r1"

#define PATCH_DATA_FIELD_MAX_SIZE       252
#define RTK_VENDOR_CONFIG_MAGIC         0x8723ab55
#define MAX_PATCH_SIZE_24K              (1024*24)   //24K
#define MAX_PATCH_SIZE_40K              (1024*40)   //40K

#define RTK_DOWNLOAD_FW                 1
#define RTK_SET_HW_FLCNTRL              2
#define RTK_SET_CONTROLLER_BAUD         3

struct rtk_bt_vendor_config_entry{
    u16 offset;
    u8 entry_len;
    u8 entry_data[0];
} __attribute__ ((packed));

struct rtk_bt_vendor_config{
    u32 signature;
    u16 data_len;
    struct rtk_bt_vendor_config_entry entry[0];
} __attribute__ ((packed));


#define HCI_EVT_CMD_CMPL_OP1001_HCI_VERSION_OFFSET      (6)     //HCI_Version's offset in COMMAND Completed Event for OpCode 0x1001(Read Local Version Information Command)
#define HCI_EVT_CMD_CMPL_OP1001_HCI_REVISION_OFFSET     (7)     //HCI_Revision's offset in COMMAND Completed Event for OpCode 0x1001(Read Local Version Information Command)
#define HCI_EVT_CMD_CMPL_OP1001_LMP_SUBVERSION_OFFSET   (12)    //LMP Subversion's offset in COMMAND Completed Event for OpCode 0x1001(Read Local Version Information Command)
#define HCI_EVT_CMD_CMPL_OP0C14_LOCAL_NAME_OFFSET       (6)     //Local Name's offset in COMMAND Completed Event for OpCode 0x0C14(Read Local Name Command)
#define HCI_EVT_CMD_CMPL_OP1009_BDADDR_OFFSET           (6)     //BD_ADDR's offset in COMMAND Completed Event for OpCode 0x1009(Read BD_ADDR Command)
#define HCI_EVT_CMD_CMPL_OPFC6D_EVERSION_OFFSET         (6)  //eversion's offset in COMMAND Completed Event for OpCode 0xfc6d(Read eVERSION Vendor Command)
#define HCI_EVT_CMD_CMPL_OPFC61_CHIPTYPE_OFFSET         (6)  //chip type's offset in COMMAND Completed Event for OpCode 0xfc61(Read ChipType Vendor Command)

#define H5_SYNC_REQ_SIZE    (2)
#define H5_SYNC_RESP_SIZE   (2)
#define H5_CONF_REQ_SIZE    (3)
#define H5_CONF_RESP_SIZE   (2)

/******************************************************************************
**  Local type definitions
******************************************************************************/

/* Hardware Configuration State */
enum {
    HW_CFG_H5_INIT = 1,
    HW_CFG_READ_LOCAL_VER,
    HW_CFG_READ_ECO_VER,   //eco version
    HW_CFG_READ_CHIP_TYPE,
    HW_CFG_START,
    HW_CFG_SET_UART_BAUD_HOST,//change FW baudrate
    HW_CFG_SET_UART_BAUD_CONTROLLER,//change Host baudrate
    HW_CFG_SET_UART_HW_FLOW_CONTROL,
    HW_CFG_DL_FW_PATCH
};

/* h/w config control block */
typedef struct
{
    u32    max_patch_size;
    u32    baudrate;
    u8     state;          /* Hardware configuration state */
    s32    fw_len;          /* FW patch file len */
    s32    config_len;      /* Config patch file len */
    u32    total_len;       /* FW & config extracted buf len */
    u8     *fw_buf;         /* FW patch file buf */
    u8     *config_buf;     /* Config patch file buf */
    u8     *total_buf;      /* FW & config extracted buf */
    u8     patch_frag_cnt;  /* Patch fragment count download */
    u8     patch_frag_idx;  /* Current patch fragment index */
    u8     patch_frag_len;  /* Patch fragment length */
    u8     patch_frag_tail; /* Last patch fragment length */
    u8     hw_flow_cntrl;   /* Uart flow control, bit7:set, bit0:enable */
    u8     patch_iIndexRx;
} bt_hw_cfg_cb_t;


/******************************************************************************
**  Externs
******************************************************************************/
void hw_config_start(void);
void hw_config_cback(void *p_evt_buf);
void rtk_hw_destory(void);

/******************************************************************************
**  Static variables
******************************************************************************/
static bt_hw_cfg_cb_t hw_cfg_cb;
static const tHCI_IF *bt_h5_if = NULL;
//signature: realtech
const u8 RTK_EPATCH_SIGNATURE[8]={0x52,0x65,0x61,0x6C,0x74,0x65,0x63,0x68};

//Extension Section IGNATURE:0x77FD0451
const u8 EXTENSION_SECTION_SIGNATURE[4]={0x51,0x04,0xFD,0x77};

//need to change MAX_PATCH_SIZE && fw_data && config_data
#define MAX_PATCH_SIZE        MAX_PATCH_SIZE_24K

static u8 fw_data[] = {
#include "fw_8822bs_c.txt"
};

static u8 config_data[] = {
#include "config_8822bs_c.txt"
};

/*******************************************************************************
**
** Function        line_speed_to_userial_baud
**
** Description     helper function converts line speed number into USERIAL baud
**                 rate symbol
**
** Returns         unit8_t (USERIAL baud symbol)
**
*******************************************************************************/
u8 line_speed_to_userial_baud(u32 line_speed)
{
    u8 baud;

    if (line_speed == 4000000)
        baud = USERIAL_BAUD_4M;
    else if (line_speed == 3000000)
        baud = USERIAL_BAUD_3M;
    else if (line_speed == 2000000)
        baud = USERIAL_BAUD_2M;
    else if (line_speed == 1500000)
        baud = USERIAL_BAUD_1_5M;
    else if (line_speed == 1000000)
        baud = USERIAL_BAUD_1M;
    else if (line_speed == 921600)
        baud = USERIAL_BAUD_921600;
    else if (line_speed == 460800)
        baud = USERIAL_BAUD_460800;
    else if (line_speed == 230400)
        baud = USERIAL_BAUD_230400;
    else if (line_speed == 115200)
        baud = USERIAL_BAUD_115200;
    else if (line_speed == 57600)
        baud = USERIAL_BAUD_57600;
    else if (line_speed == 19200)
        baud = USERIAL_BAUD_19200;
    else if (line_speed == 9600)
        baud = USERIAL_BAUD_9600;
    else if (line_speed == 1200)
        baud = USERIAL_BAUD_1200;
    else if (line_speed == 600)
        baud = USERIAL_BAUD_600;
    else
    {
        RTK_ERROR( "userial vendor: unsupported baud speed %d \n", line_speed);
        baud = USERIAL_BAUD_115200;
    }

    return baud;
}

typedef struct _baudrate_ex
{
    u32 rtk_speed;
    u32 uart_speed;
}baudrate_ex;

baudrate_ex baudrates[] =
{
    {0x00006004, 921600},
    {0x05F75004, 921600},//RTL8723BS
    {0x00004003, 1500000},
    {0x04928002, 1500000},//RTL8723BS
    {0x00005002, 2000000},//same as RTL8723AS
    {0x00008001, 3000000},
    {0x04928001, 3000000},//RTL8723BS
    {0x06B58001, 3000000},//add RTL8703as
    {0x00007001, 3500000},
    {0x052A6001, 3500000},//RTL8723BS
    {0x00005001, 4000000},//same as RTL8723AS
    {0x0000701d, 115200},
    {0x0252C014, 115200}//RTL8723BS
};

/**
* Change realtek Bluetooth speed to uart speed. It is matching in the struct baudrates:
*
* @code
* baudrate_ex baudrates[] =
* {
*   {0x7001, 3500000},
*   {0x6004, 921600},
*   {0x4003, 1500000},
*   {0x5001, 4000000},
*   {0x5002, 2000000},
*   {0x8001, 3000000},
*   {0x701d, 115200}
* };
* @endcode
*
* If there is no match in baudrates, uart speed will be set as #115200.
*
* @param rtk_speed realtek Bluetooth speed
* @param uart_speed uart speed
*
*/
static void rtk_speed_to_uart_speed(u32 rtk_speed, u32* uart_speed)
{
    *uart_speed = 115200;

    u8 i;
    for (i=0; i< sizeof(baudrates)/sizeof(baudrate_ex); i++)
    {
        if (baudrates[i].rtk_speed == rtk_speed)
        {
            *uart_speed = baudrates[i].uart_speed;
            return;
        }
    }
    return;
}

/**
* Change uart speed to realtek Bluetooth speed. It is matching in the struct baudrates:
*
* @code
* baudrate_ex baudrates[] =
* {
*   {0x7001, 3500000},
*   {0x6004, 921600},
*   {0x4003, 1500000},
*   {0x5001, 4000000},
*   {0x5002, 2000000},
*   {0x8001, 3000000},
*   {0x701d, 115200}
* };
* @endcode
*
* If there is no match in baudrates, realtek Bluetooth speed will be set as #0x701D.
*
* @param uart_speed uart speed
* @param rtk_speed realtek Bluetooth speed
*
*/
static inline void uart_speed_to_rtk_speed(u32 uart_speed, u32* rtk_speed)
{
    *rtk_speed = 0x701D;

    unsigned int i;
    for (i=0; i< sizeof(baudrates)/sizeof(baudrate_ex); i++)
    {
      if (baudrates[i].uart_speed == uart_speed)
      {
          *rtk_speed = baudrates[i].rtk_speed;
          return;
      }
    }
    return;
}


/*******************************************************************************
**
** Function         hw_config_set_bdaddr
**
** Description      Program controller's Bluetooth Device Address
**
** Returns          TRUE, if valid address is sent
**                  FALSE, otherwise
**
*******************************************************************************/
static u8 hw_config_set_controller_baudrate(HC_BT_HDR *p_buf, u32 baudrate)
{
    u8 retval = FALSE;
    u8 *p = (u8 *) (p_buf + 1);

    UINT16_TO_STREAM(p, HCI_VSC_UPDATE_BAUDRATE);
    *p++ = 4; /* parameter length */
    UINT32_TO_STREAM(p, baudrate);

    p_buf->len = HCI_CMD_PREAMBLE_SIZE + 4;

    retval = bt_h5_if->send_int_cmd(HCI_VSC_UPDATE_BAUDRATE, p_buf, hw_config_cback);

    return (retval);
}

static u32 rtk_parse_config_file(unsigned char** config_buf, u32* filelen)
{
    struct rtk_bt_vendor_config* config = (struct rtk_bt_vendor_config*) *config_buf;
    u16 config_len = le16_to_cpu(config->data_len), temp = 0;
    struct rtk_bt_vendor_config_entry* entry = config->entry;
    unsigned int i = 0;
    u32 baudrate = 0;
    u32 config_has_bdaddr = 0;
    u8 *p;

    if (le32_to_cpu(config->signature) != RTK_VENDOR_CONFIG_MAGIC)
    {
        RTK_ERROR("config signature magic number(0x%x) is not set to RTK_VENDOR_CONFIG_MAGIC \n", config->signature);
        return 0;
    }

    int right_len = *filelen - sizeof(struct rtk_bt_vendor_config);
    if (config_len != right_len)
    {
        RTK_ERROR("config len(0x%x) is not right(%d) \n", config_len, right_len);
        return 0;
    }

    for (i=0; i<config_len;)
    {
        switch(le16_to_cpu(entry->offset))
        {
            case 0xc:
            {
                p = (u8 *)entry->entry_data;
                STREAM_TO_UINT32(baudrate, p);
                if (entry->entry_len >= 12)
                {
                    hw_cfg_cb.hw_flow_cntrl |= 0x80; /* bit7 set hw flow control */
                    if (entry->entry_data[12] & 0x04) /* offset 0x18, bit2 */
                        hw_cfg_cb.hw_flow_cntrl |= 1; /* bit0 enable hw flow control */
                }

                RTK_DEBUG("config baud rate to :0x%08x, hwflowcontrol:0x%x, 0x%x \n", baudrate, entry->entry_data[12], hw_cfg_cb.hw_flow_cntrl);
                break;
            }
            default:
                RTK_DEBUG("config offset(0x%x),length(0x%x) \n", entry->offset, entry->entry_len);
                break;
        }
        temp = entry->entry_len + sizeof(struct rtk_bt_vendor_config_entry);
        i += temp;
        entry = (struct rtk_bt_vendor_config_entry*)((u8*)entry + temp);
    }
    return baudrate;
}

static u32 rtk_get_bt_config(unsigned char** config_buf, u32* config_baud_rate)
{
    u32 filelen;

    filelen = sizeof(config_data);
    if ((*config_buf = osi_malloc(filelen)) == NULL)
    {
        RTK_ERROR("malloc buffer for config file fail(0x%x)\n", filelen);
        return -1;
    }

    osi_memcpy(*config_buf, config_data, filelen);
    *config_baud_rate = rtk_parse_config_file(config_buf, &filelen);
    RTK_DEBUG("Get config baud rate from config file:0x%x \n", *config_baud_rate);

    return filelen;
}

static u32 rtk_get_bt_firmware(u8** fw_buf)
{
    int buf_size = 0;

    buf_size = sizeof(fw_data);
    if (!(*fw_buf = osi_malloc(buf_size)))
    {
        RTK_ERROR("Can't alloc memory for fw&config \n");
        return -1;
    }

    osi_memcpy(*fw_buf, fw_data, buf_size);
    RTK_DEBUG("Load FW OK \n");
    return buf_size;
}


static void rtk_get_bt_final_patch(bt_hw_cfg_cb_t* cfg_cb)
{
    cfg_cb->total_len = cfg_cb->fw_len + cfg_cb->config_len;
    RTK_DEBUG("total_len = 0x%x \n", cfg_cb->total_len);

    if (!(cfg_cb->total_buf = osi_malloc(cfg_cb->total_len)))
    {
        cfg_cb->total_len = 0;
        goto free_buf;
    }

    osi_memcpy(cfg_cb->total_buf, cfg_cb->fw_buf, cfg_cb->fw_len);
    osi_memcpy((cfg_cb->total_buf+cfg_cb->fw_len), cfg_cb->config_buf, cfg_cb->config_len);
    RTK_DEBUG("Fw:%s exists, config file:%s exists \n", (cfg_cb->fw_len>0)?"":"not", (cfg_cb->config_len>0)?"":"not");

free_buf:
    if (cfg_cb->fw_len > 0)
    {
        osi_free(cfg_cb->fw_buf);
        cfg_cb->fw_len = 0;
    }

    if (cfg_cb->config_len > 0)
    {
        osi_free(cfg_cb->config_buf);
        cfg_cb->config_len = 0;
    }
}

static BOOLEAN rtk_h5_initialize(void)
{
    RTK_INFO("rtk_h5_initialize \n");
    BOOLEAN status = FALSE;
    if (bt_h5_if)
    {
        hw_cfg_cb.state = HW_CFG_H5_INIT;
        bt_h5_if->send_int_cmd(HCI_VSC_H5_INIT, NULL, hw_config_cback);
        do {
            status = bt_h5_if->rcv_and_chk_timer();
        }while(hw_cfg_cb.state == HW_CFG_H5_INIT && status);
    }
    return status;
}

static int rtk_h5_get_fw(void)
{
    hw_cfg_cb.max_patch_size = MAX_PATCH_SIZE;
    hw_cfg_cb.config_len = rtk_get_bt_config(&hw_cfg_cb.config_buf, &hw_cfg_cb.baudrate);

    if (hw_cfg_cb.config_len < 0) {
        RTK_ERROR("Get Config file fail, just use efuse settings \n");
        hw_cfg_cb.config_len = 0;
    }

    hw_cfg_cb.fw_len = rtk_get_bt_firmware(&hw_cfg_cb.fw_buf);

    if (hw_cfg_cb.fw_len < 0)
    {
        RTK_ERROR("Get BT firmware fail\n");
        hw_cfg_cb.fw_len = 0;
        return -1;
    }

    rtk_get_bt_final_patch(&hw_cfg_cb);

    RTK_INFO("Check total_len(%d) max_patch_size(%d) \n", hw_cfg_cb.total_len, hw_cfg_cb.max_patch_size);
    if (hw_cfg_cb.total_len > hw_cfg_cb.max_patch_size) {
        RTK_ERROR("total length of fw&config(0x%08x) larger than max_patch_size(0x%08x)\n", hw_cfg_cb.total_len, hw_cfg_cb.max_patch_size);
        return -1;
    }

    if ((hw_cfg_cb.total_len > 0)) {
        hw_cfg_cb.patch_frag_cnt = hw_cfg_cb.total_len / PATCH_DATA_FIELD_MAX_SIZE;
        hw_cfg_cb.patch_frag_tail = hw_cfg_cb.total_len % PATCH_DATA_FIELD_MAX_SIZE;
        if (hw_cfg_cb.patch_frag_tail)
            hw_cfg_cb.patch_frag_cnt += 1;
        else
            hw_cfg_cb.patch_frag_tail = PATCH_DATA_FIELD_MAX_SIZE;

        RTK_DEBUG("patch fragment count %d, tail len %d\n", hw_cfg_cb.patch_frag_cnt, hw_cfg_cb.patch_frag_tail);
    }

    if ((hw_cfg_cb.baudrate == 0) && ((hw_cfg_cb.hw_flow_cntrl & 0x80) == 0)) {
        RTK_DEBUG("no baudrate to set and no need to set hw flow control\n");
        return RTK_DOWNLOAD_FW;
    }

    if ((hw_cfg_cb.baudrate == 0) && (hw_cfg_cb.hw_flow_cntrl & 0x80)) {
        RTK_DEBUG("no baudrate to set but set hw flow control is needed\n");
        return RTK_SET_HW_FLCNTRL;
    }

    return RTK_SET_CONTROLLER_BAUD;
}

static BOOLEAN rtk_h5_set_controller_baudrate(void)
{
    BOOLEAN status = FALSE;
    if (hw_cfg_cb.baudrate == 0)
        return TRUE;

    hw_cfg_cb.state = HW_CFG_SET_UART_BAUD_CONTROLLER;
    HC_BT_HDR *p_buf = (HC_BT_HDR *)bt_h5_if->alloc(BT_HC_HDR_SIZE + HCI_CMD_MAX_LEN);

    if (p_buf != NULL)
    {
        p_buf->event = MSG_STACK_TO_HC_HCI_CMD;
        p_buf->offset = 0;
        p_buf->len = 0;
        p_buf->layer_specific = 0;

        RTK_DEBUG("rtk_h5_set_controller_baudrate baundrate %d\n", hw_cfg_cb.baudrate);
        hw_config_set_controller_baudrate(p_buf, hw_cfg_cb.baudrate);

        do {
            status = bt_h5_if->rcv_and_chk_timer();
        }while(hw_cfg_cb.state == HW_CFG_SET_UART_BAUD_CONTROLLER && status);
    }
    return status;
}


static BOOLEAN rtk_h5_set_host_baudrate(void)
{
    u32    host_baudrate = 0;
    BOOLEAN status = FALSE;
    if (hw_cfg_cb.baudrate == 0)
        return TRUE;

    hw_cfg_cb.state = HW_CFG_SET_UART_BAUD_HOST;
    rtk_speed_to_uart_speed(hw_cfg_cb.baudrate, &host_baudrate);
    RTK_DEBUG("rtk_h5_set_host_baudrate: set HOST UART baud %i\n", host_baudrate);
    status = userial_vendor_set_baud(line_speed_to_userial_baud(host_baudrate));

    osi_rtk_mdelay(100);
    return status;
}

static BOOLEAN rtk_h5_set_hw_cntrl(void)
{
    BOOLEAN status = FALSE;
    if((hw_cfg_cb.hw_flow_cntrl & 0x80) == 0)
        return TRUE;

    RTK_DEBUG("Change HW flowcontrol setting\n");
    hw_cfg_cb.state = HW_CFG_SET_UART_HW_FLOW_CONTROL;
    if(hw_cfg_cb.hw_flow_cntrl & 0x01) {
        status = userial_vendor_set_hw_fctrl(1);
    }
    else {
        status = userial_vendor_set_hw_fctrl(0);
    }
    osi_rtk_mdelay(100);
    return status;
}

static int hci_download_patch_h4(HC_BT_HDR *p_buf, int index, u8 *data, int len)
{
    u8 retval = FALSE;
    u8 *p = (u8 *) (p_buf + 1);

    UINT16_TO_STREAM(p, HCI_VSC_DOWNLOAD_FW_PATCH);
    *p++ = 1 + len;  /* parameter length */
    *p++ = index;
    osi_memcpy(p, data, len);
    p_buf->len = HCI_CMD_PREAMBLE_SIZE + 1 + len;

    retval = bt_h5_if->send_int_cmd(HCI_VSC_DOWNLOAD_FW_PATCH, p_buf, hw_config_cback);
    return retval;
}

static BOOLEAN rtk_h5_dlfw_patch(void)
{
    RTK_DEBUG("rtk_h5_dlfw_patch start\n");
    BOOLEAN status;
    HC_BT_HDR *p_buf = (HC_BT_HDR *)bt_h5_if->alloc(BT_HC_HDR_SIZE + HCI_CMD_MAX_LEN);
    if (p_buf != NULL)
    {
        p_buf->event = MSG_STACK_TO_HC_HCI_CMD;
        p_buf->offset = 0;
        p_buf->len = 0;
        p_buf->layer_specific = 0;
        hw_cfg_cb.state = HW_CFG_DL_FW_PATCH;
        hw_cfg_cb.patch_frag_idx = 0;
        hw_cfg_cb.patch_frag_len = PATCH_DATA_FIELD_MAX_SIZE;
        hci_download_patch_h4(p_buf, hw_cfg_cb.patch_frag_idx,
                                    hw_cfg_cb.total_buf+(hw_cfg_cb.patch_frag_idx & 0x7F)*PATCH_DATA_FIELD_MAX_SIZE,
                                    hw_cfg_cb.patch_frag_len);
    }
    else {
        RTK_ERROR("rtk_h5_dlfw_patch can't alloc buffer");
        return FALSE;
    }

    do {
        status = bt_h5_if->rcv_and_chk_timer();
    }while(hw_cfg_cb.state == HW_CFG_DL_FW_PATCH && status);

    if(hw_cfg_cb.total_buf) {
        bt_h5_if->dealloc(hw_cfg_cb.total_buf);
    }
    if(status)
        RTK_INFO("rtk_h5_dlfw_patch done\n");
    return status;
}

static char * dump_hw_config_cback_state(u8 state)
{
    switch(state)
    {
        case HW_CFG_H5_INIT:
            return "HW_CFG_H5_INIT";
        case HW_CFG_READ_LOCAL_VER:
            return "HW_CFG_READ_LOCAL_VER";
        case HW_CFG_READ_ECO_VER:
            return "HW_CFG_READ_ECO_VER";
        case HW_CFG_READ_CHIP_TYPE:
            return "HW_CFG_READ_CHIP_TYPE";
        case HW_CFG_START:
            return "HW_CFG_START";
        case HW_CFG_SET_UART_BAUD_HOST:
            return "HW_CFG_SET_UART_BAUD_HOST";
        case HW_CFG_SET_UART_BAUD_CONTROLLER:
            return "HW_CFG_SET_UART_BAUD_CONTROLLER";
        case HW_CFG_SET_UART_HW_FLOW_CONTROL:
            return "HW_CFG_SET_UART_HW_FLOW_CONTROL";
        case HW_CFG_DL_FW_PATCH:
            return "HW_CFG_DL_FW_PATCH";
        default:
            return "unknown config cback state!";
    }
}

/*******************************************************************************
**
** Function         hw_config_cback
**
** Description      Callback function for controller configuration
**
** Returns          None
**
*******************************************************************************/
void hw_config_cback(void *p_mem)
{
    HC_BT_HDR   *p_evt_buf = NULL;
    u8     *p = NULL;
    u8     status = 0;
    u16    opcode = 0;
    HC_BT_HDR   *p_buf = NULL;
    int         i = 0;
    u32    host_baudrate = 0;

    if(p_mem != NULL)
    {
        p_evt_buf = (HC_BT_HDR *) p_mem;
        status = *((u8 *)(p_evt_buf + 1) + HCI_EVT_CMD_CMPL_STATUS_OFFSET);
        p = (u8 *)(p_evt_buf + 1) + HCI_EVT_CMD_CMPL_OPCODE_OFFSET;
        STREAM_TO_UINT16(opcode, p);
        if(opcode == HCI_VSC_DOWNLOAD_FW_PATCH)
        {
            hw_cfg_cb.patch_iIndexRx = *((u8 *)(p_evt_buf + 1) + HCI_EVT_CMD_CMPL_STATUS_OFFSET + 1);
        }

        /* Free the RX event buffer */
        if ((bt_h5_if) && (p_evt_buf != NULL))
            bt_h5_if->dealloc(p_evt_buf);
    }

    /* Ask a new buffer big enough to hold any HCI commands sent in here */
    /*a cut fc6d status==1*/
    if ((status == 0) && bt_h5_if)
        p_buf = (HC_BT_HDR *)bt_h5_if->alloc(BT_HC_HDR_SIZE + HCI_CMD_MAX_LEN);

    if (p_buf != NULL)
    {
        p_buf->event = MSG_STACK_TO_HC_HCI_CMD;
        p_buf->offset = 0;
        p_buf->len = 0;
        p_buf->layer_specific = 0;

        RTK_DEBUG("hw_config_cback hw_cfg_cb.state = %s \n", dump_hw_config_cback_state(hw_cfg_cb.state));
        switch (hw_cfg_cb.state)
        {
            case HW_CFG_H5_INIT:
            {
                hw_cfg_cb.state = HW_CFG_START;
                if (p_buf != NULL)
                    bt_h5_if->dealloc(p_buf);
            }
                break;

            case HW_CFG_START:
                RTK_DEBUG("ignore this state \n");
                if (p_buf != NULL)
                    bt_h5_if->dealloc(p_buf);
                break;


            case HW_CFG_SET_UART_BAUD_CONTROLLER:
                RTK_DEBUG("hw_config_cback: set CONTROLLER UART baud 0x%x \n", hw_cfg_cb.baudrate);
                if(opcode == HCI_VSC_UPDATE_BAUDRATE)
                    hw_cfg_cb.state = HW_CFG_SET_UART_BAUD_HOST;
                break;

            case HW_CFG_SET_UART_BAUD_HOST:
                RTK_DEBUG("ignore this state \n");
                if (p_buf != NULL)
                    bt_h5_if->dealloc(p_buf);
                hw_cfg_cb.state = HW_CFG_SET_UART_HW_FLOW_CONTROL;
                break;

            case HW_CFG_SET_UART_HW_FLOW_CONTROL:
                RTK_DEBUG("ignore this state \n");
                if (p_buf != NULL)
                    bt_h5_if->dealloc(p_buf);
                break;

            case HW_CFG_DL_FW_PATCH:
                RTK_DEBUG("hw_config_cback: HW_CFG_DL_FW_PATCH status:%i, opcode:0x%x \n", status, opcode);

                //recv command complete event for patch code download command
                if(opcode == HCI_VSC_DOWNLOAD_FW_PATCH)
                {
                    RTK_DEBUG("hw_config_cback: HW_CFG_DL_FW_PATCH status:%i, iIndexRx:%i \n", status, hw_cfg_cb.patch_iIndexRx);
                    hw_cfg_cb.patch_frag_idx++;

                    if(hw_cfg_cb.patch_iIndexRx & 0x80)
                    {
                        RTK_DEBUG("hw_config_cback fwcfg completed \n");
                        bt_h5_if->dealloc(hw_cfg_cb.total_buf);
                        hw_cfg_cb.total_len = 0;

                        bt_h5_if->dealloc(p_buf);
                        hw_cfg_cb.state = 0;
                        break;
                    }
                }
                else {
                    bt_h5_if->dealloc(p_buf);
                    break;
                }

                if (hw_cfg_cb.patch_frag_idx < hw_cfg_cb.patch_frag_cnt)
                {
                    hw_cfg_cb.patch_iIndexRx = hw_cfg_cb.patch_frag_idx?((hw_cfg_cb.patch_frag_idx-1)%0x7f+1):0;
                    if (hw_cfg_cb.patch_frag_idx == hw_cfg_cb.patch_frag_cnt - 1)
                    {
                        hw_cfg_cb.patch_iIndexRx |= 0x80;
                        hw_cfg_cb.patch_frag_len = hw_cfg_cb.patch_frag_tail;
                        RTK_DEBUG("HW_CFG_DL_FW_PATCH: send last fw fragment idx = %d, len = %d\n", hw_cfg_cb.patch_frag_idx, hw_cfg_cb.patch_frag_len);
                    }
                    else
                    {
                        hw_cfg_cb.patch_iIndexRx &= 0x7F;
                        hw_cfg_cb.patch_frag_len = PATCH_DATA_FIELD_MAX_SIZE;
                    }
                }

                hci_download_patch_h4(p_buf, hw_cfg_cb.patch_iIndexRx,
                                    hw_cfg_cb.total_buf+(hw_cfg_cb.patch_frag_idx&0x7F)*PATCH_DATA_FIELD_MAX_SIZE,
                                    hw_cfg_cb.patch_frag_len);
                break;

            default:
                break;
        } // switch(hw_cfg_cb.state)
    } // if (p_buf != NULL)
}


/*****************************************************************************
**   Hardware Configuration Interface Functions
*****************************************************************************/

/*******************************************************************************
**
** Function        rtk_hw_init
**
** Description     rtk_hw_init for boot loader
**
** Returns         None
**
*******************************************************************************/
void rtk_hw_init(void)
{
    osi_memset(&hw_cfg_cb, 0, sizeof(bt_hw_cfg_cb_t));
    RTK_INFO("\nRealtek libbt-vendor_uart Version %s \n",RTK_VERSION);

    bt_h5_if = hci_get_h5_interface();
    if(bt_h5_if) {
        bt_h5_if->init();
    }
    hw_config_start();
}

/*******************************************************************************
**
** Function        hw_config_start
**
** Description     Kick off controller initialization process
**
** Returns         None
**
*******************************************************************************/
void hw_config_start(void)
{
    int     state =0;
    RTK_DEBUG("hw_config_start\n");

    /* Start from sending H5 SYNC */
    if(!rtk_h5_initialize()) {
        RTK_ERROR("rtk h5 initialize fail! \n");
        goto done;
    }

    state = rtk_h5_get_fw();
    RTK_DEBUG("hw_config_start state = %d \n", state);

    RTK_INFO("rtk set controller and host baudrate baundrate %d\n", hw_cfg_cb.baudrate);
    if(!rtk_h5_set_controller_baudrate()) {
        RTK_ERROR("rtk h5 set controller_baudrate fail! \n");
        goto done;
    }

    if(!rtk_h5_set_host_baudrate()) {
        RTK_ERROR("rtk h5 set host baudrate fail! \n");
        goto done;
    }
/*
    if(!rtk_h5_set_hw_cntrl()) {
        RTK_ERROR("rtk h5 set hw cntrl fail! \n");
        goto done;
    }
*/
    if(!rtk_h5_dlfw_patch()) {
        RTK_ERROR("rtk_h5_dlfw_patch fail! \n");
    }

done:
    rtk_hw_destory();
}

/*******************************************************************************
**
** Function        rtk_hw_destory
**
** Description     rtk_hw_destory for boot loader
**
** Returns         None
**
*******************************************************************************/
void rtk_hw_destory(void)
{
    RTK_DEBUG("rtk_hw_destory\n");
    osi_memset(&hw_cfg_cb, 0, sizeof(bt_hw_cfg_cb_t));
    if(bt_h5_if) {
        bt_h5_if->cleanup();
        bt_h5_if = NULL;
    }
}
