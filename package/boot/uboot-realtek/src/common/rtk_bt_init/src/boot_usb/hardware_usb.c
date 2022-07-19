/******************************************************************************
*    Copyright (c) 2009-2016 by Realtek.
*    All rights reserved.
*
*    Create by Cheng_cai. 2016-05-24
*
******************************************************************************/

#include "osi_include_int.h"
#include "osi_include_ext.h"

#define CHIP_TYPE        "fw_8821c_b.txt"

#define MAX_PATCH_SIZE_24K              (1024*24)   //24K
#define MAX_PATCH_SIZE_40K              (1024*40)   //40K

//need to change size
#define RTK_PATCH_LENGTH_MAX    MAX_PATCH_SIZE_40K

//patch txt formate: total length(2 bytes) || fw patch || config patch
static unsigned char lu8Code[] = {
#include CHIP_TYPE
};

firmware_info *firmware_info_init(struct osi_usb_device *dev)
{
	struct osi_usb_device *udev = dev;
	firmware_info *fw_info;

	RTK_DEBUG("%s[%d]: start.\n", __func__, __LINE__);
    osi_buff_init();

	fw_info = osi_malloc(sizeof(*fw_info));
    osi_memset(fw_info, 0, sizeof(*fw_info));

	if (!fw_info)
		return NULL;


	fw_info->fw_data = osi_malloc(RTK_PATCH_LENGTH_MAX);
    osi_memset(fw_info->fw_data, 0, RTK_PATCH_LENGTH_MAX);
	if (!fw_info->fw_data) {
		osi_free(fw_info);
		return NULL;
	}

	fw_info->send_pkt = osi_malloc(PKT_LEN);
    osi_memset(fw_info->send_pkt, 0, PKT_LEN);
	if (!fw_info->send_pkt) {
        osi_free(fw_info->fw_data);
		osi_free(fw_info);
		return NULL;
	}

	fw_info->rcv_pkt = osi_malloc(PKT_LEN);
    osi_memset(fw_info->rcv_pkt, 0, PKT_LEN);
	if (!fw_info->rcv_pkt) {
        osi_free(fw_info->fw_data);
		osi_free(fw_info->send_pkt);
		osi_free(fw_info);
		return NULL;
	}


	fw_info->intf = NULL;
	fw_info->udev = udev;
	fw_info->pipe_in = osi_usb_rcvintpipe(fw_info->udev, INTR_EP);
	fw_info->pipe_out = osi_usb_sndctrlpipe(fw_info->udev, CTRL_EP);
	fw_info->cmd_hdr = (struct hci_command_hdr *)(fw_info->send_pkt);
	fw_info->evt_hdr = (struct hci_event_hdr *)(fw_info->rcv_pkt);
	fw_info->cmd_cmp = (struct hci_ev_cmd_complete *)(fw_info->rcv_pkt + EVT_HDR_LEN);
	fw_info->req_para = fw_info->send_pkt + CMD_HDR_LEN;
	fw_info->rsp_para = fw_info->rcv_pkt + EVT_HDR_LEN + CMD_CMP_LEN;

	return fw_info;
}

void firmware_info_destroy(firmware_info *fw_info)
{
    osi_free(fw_info->fw_data);
	osi_free(fw_info->rcv_pkt);
	osi_free(fw_info->send_pkt);
	osi_free(fw_info);
}
int load_firmware(firmware_info *fw_info, unsigned char **buff)
{
    UNUSED(fw_info);
    unsigned int size;
    unsigned int i;

    size = lu8Code[0] | (lu8Code[1] << 8);
    RTK_DEBUG("%s,size is %d \n",__func__, size);
    if(size >= RTK_PATCH_LENGTH_MAX) {
        RTK_ERROR("firmware is larger than %d \n", RTK_PATCH_LENGTH_MAX);
        return -1;
    }

    osi_memcpy(*buff, &lu8Code[2], size);
    return size;
}
int send_hci_cmd(firmware_info *fw_info)
{
	int ret_val;

	ret_val = osi_usb_control_msg(
		fw_info->udev, fw_info->pipe_out,
		0, OSI_USB_TYPE_CLASS, 0, 0,
		(void *)(fw_info->send_pkt),
		fw_info->pkt_len, MSG_TO);

	return ret_val;
}


int rcv_hci_evt(firmware_info *fw_info)
{
    int ret_len = 0, ret_val = 0;
    int i;
    u16 opcode = 0;

	while (1) {
		for(i = 0; i < 5; i++) {
            ret_val = osi_usb_submit_int_msg(
                fw_info->udev, fw_info->pipe_in,
                (void *)(fw_info->rcv_pkt), RCV_PKT_LEN,
                MSG_TO);
                if (ret_val >= 0)
                    break;

		}
        RTK_DEBUG("fw_info->rcv_pkt : 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x \n",
        fw_info->rcv_pkt[0],
        fw_info->rcv_pkt[1],
        fw_info->rcv_pkt[2],
        fw_info->rcv_pkt[3],
        fw_info->rcv_pkt[4],
        fw_info->rcv_pkt[5],
        fw_info->rcv_pkt[6]);
		if (ret_val < 0)
			return ret_val;

		if (HCI_COMMAND_COMPLETE_EVT == fw_info->evt_hdr->evt) {
            opcode = fw_info->cmd_cmp->opcode[0] | (fw_info->cmd_cmp->opcode[1] << 8);
            RTK_DEBUG("opcode :0x%02x \n",opcode);
			if (fw_info->cmd_hdr->opcode == *(u16 *)fw_info->cmd_cmp->opcode)
				return 0;
		}
	}
}

int get_firmware(firmware_info *fw_info)
{
    fw_info->fw_len = load_firmware(fw_info, &fw_info->fw_data);
    RTK_DEBUG("%s[%d]: fw_len=%d\n", __func__, __LINE__, fw_info->fw_len);
    if (fw_info->fw_len <= 0)
        return -1;

	return 0;
}
/*reset_controller is aimed to reset_bt_fw before updata Fw patch*/
int reset_controller(firmware_info* fw_info)
{
    int ret_val;
    RTK_INFO("reset_controller \n");

    if (!fw_info)
        return -ENODEV;

    fw_info->cmd_hdr->opcode = cpu_to_le16(HCI_VENDOR_FORCE_RESET_AND_PATCHABLE);
    fw_info->cmd_hdr->plen = 0;
    fw_info->pkt_len = CMD_HDR_LEN;
    ret_val = send_hci_cmd(fw_info);

    if (ret_val < 0) {
        RTK_ERROR("%s: Failed to send hci cmd 0x%04x, errno %d \n",
                __func__, fw_info->cmd_hdr->opcode, ret_val);
        return ret_val;
    }

    //sleep 1s for firmware reset.
    osi_rtk_mdelay(200);
    RTK_DEBUG("%s: Wait fw reset for 1ms \n",__func__);

    return ret_val;
}
/*reset_controller is aimed to reset_bt_fw before updata Fw patch*/

/*reset_channel to recover the communication between wifi 8192eu with 8761 bt controller in case of geteversion error*/
int reset_channel(firmware_info* fw_info)
{
    struct rtk_reset_evt *ever_evt;
    int ret_val;

    if (!fw_info)
        return -ENODEV;

    fw_info->cmd_hdr->opcode = cpu_to_le16(HCI_VENDOR_RESET);
    fw_info->cmd_hdr->plen = 0;
    fw_info->pkt_len = CMD_HDR_LEN;

    ret_val = send_hci_cmd(fw_info);
    if (ret_val < 0) {
        RTK_ERROR("%s: Failed to send  hci cmd 0x%04x, errno %d \n",
                __func__, fw_info->cmd_hdr->opcode, ret_val);
        return ret_val;
    }

    ret_val = rcv_hci_evt(fw_info);
    if (ret_val < 0) {
        RTK_ERROR("%s: Failed to receive  hci event, errno %d \n",
                __func__, ret_val);
        return ret_val;
    }

    ever_evt = (struct rtk_reset_evt *)(fw_info->rsp_para);

    RTK_DEBUG("%s: status %d \n", __func__, ever_evt->status);

    //sleep 300ms for channel reset.
    osi_rtk_mdelay(300);
    RTK_DEBUG("%s: Wait channel reset for 300ms \n",__func__);

    return ret_val;
}


int download_data(firmware_info *fw_info)
{
	download_cp *cmd_para;
	download_rp *evt_para;
	unsigned char *pcur;
	int pkt_len, frag_num, frag_len;
	int i, ret_val;
	int ncmd = 1, step = 1;

	RTK_DEBUG("%s: start\n", __func__);

	cmd_para = (download_cp *)fw_info->req_para;
	evt_para = (download_rp *)fw_info->rsp_para;
	pcur = fw_info->fw_data;
	pkt_len = CMD_HDR_LEN + sizeof(download_cp);
	frag_num = fw_info->fw_len / PATCH_SEG_MAX + 1;
	frag_len = PATCH_SEG_MAX;

	for (i = 0; i < frag_num; i++) {
		cmd_para->index = i;
		if (i == (frag_num - 1)) {
			cmd_para->index |= DATA_END;
			frag_len = fw_info->fw_len % PATCH_SEG_MAX;
			pkt_len -= (PATCH_SEG_MAX - frag_len);
		}
		fw_info->cmd_hdr->opcode = cpu_to_le16(HCI_VSC_DOWNLOAD_FW_PATCH);
		fw_info->cmd_hdr->plen = sizeof(unsigned char) + frag_len;
		fw_info->pkt_len = pkt_len;
		osi_memcpy(cmd_para->data, pcur, frag_len);

		if (step > 0) {
			ret_val = send_hci_cmd(fw_info);
			if (ret_val < 0) {
				RTK_ERROR("%s: Failed to send frag num %d\n", __func__, cmd_para->index);
				return ret_val;
			} else {
				RTK_DEBUG("%s: Send frag num %d\n", __func__, cmd_para->index);
            }

			if (--step > 0 && i < frag_num - 1) {
				RTK_DEBUG("%s: Continue to send frag num %d\n", __func__, cmd_para->index + 1);
				pcur += PATCH_SEG_MAX;
				continue;
			}
		}

		while (ncmd > 0) {
			ret_val = rcv_hci_evt(fw_info);
			if (ret_val < 0) {
				RTK_ERROR("%s: rcv_hci_evt err %d\n", __func__, ret_val);
				return ret_val;
			} else {
				RTK_DEBUG("%s: Receive acked frag num %d\n", __func__, evt_para->index);
				ncmd--;
			}

			if (0 != evt_para->status) {
				RTK_ERROR("%s: Receive acked frag num %d, err status %d\n",
						__func__, ret_val, evt_para->status);
				return -1;
			}

			if ((evt_para->index & DATA_END) || (evt_para->index == frag_num - 1)) {
				RTK_DEBUG("%s: Receive last acked index %d\n", __func__, evt_para->index);
				goto end;
			}
		}

		ncmd = step = fw_info->cmd_cmp->ncmd;
		pcur += PATCH_SEG_MAX;
		RTK_DEBUG("%s: HCI command packet num %d\n", __func__, ncmd);
	}

	/*
	 * It is tricky that Host cannot receive DATA_END index from BT
	 * controller, at least for 8723au. We are doomed if failed.
	 */

end:
	RTK_DEBUG("%s: done, sent %d frag pkts, received %d frag events\n",
			__func__, cmd_para->index, evt_para->index);
	return fw_info->fw_len;
}

int set_wakeup_device(firmware_info* fw_info)
{
	struct rtk_eversion_evt *ever_evt;
	int ret_val;

    static unsigned char bdaddr[7] = {0x00, 0xd7, 0xe3,0x3e,0xf8, 0xe6,0xa0};
	if (!fw_info)
		return -ENODEV;

	fw_info->cmd_hdr->opcode = cpu_to_le16(HCI_VSC_SET_WAKE_UP_DEVICE);
	fw_info->cmd_hdr->plen = 7;
    osi_memcpy(fw_info->req_para, bdaddr, 7);
	fw_info->pkt_len = CMD_HDR_LEN + 7;

	ret_val = send_hci_cmd(fw_info);
	if (ret_val < 0) {
		RTK_ERROR("%s: Failed to send hci cmd 0x%04x, errno %d\n",
				__func__, fw_info->cmd_hdr->opcode, ret_val);
		return ret_val;
	}

	ret_val = rcv_hci_evt(fw_info);
	if (ret_val < 0) {
		RTK_ERROR("%s: Failed to receive hci event, errno %d\n",
				__func__, ret_val);
		return ret_val;
	}

	ever_evt = (struct rtk_eversion_evt *)(fw_info->rsp_para);

	RTK_DEBUG("%s: status %d, eversion %d", __func__, ever_evt->status, ever_evt->version);

	return ret_val;
}


int get_eversion(firmware_info* fw_info)
{
	struct rtk_eversion_evt *ever_evt;
	int ret_val;

	if (!fw_info)
		return -ENODEV;

	fw_info->cmd_hdr->opcode = cpu_to_le16(HCI_READ_LMP_VERSION);
	fw_info->cmd_hdr->plen = 0;
	fw_info->pkt_len = CMD_HDR_LEN;

	ret_val = send_hci_cmd(fw_info);
	if (ret_val < 0) {
		RTK_ERROR("%s: Failed to send hci cmd 0x%04x, errno %d\n",
				__func__, fw_info->cmd_hdr->opcode, ret_val);
		return ret_val;
	}

	ret_val = rcv_hci_evt(fw_info);
	if (ret_val < 0) {
		RTK_ERROR("%s: Failed to receive hci event, errno %d\n",
				__func__, ret_val);
		return ret_val;
	}

	ever_evt = (struct rtk_eversion_evt *)(fw_info->rsp_para);

	RTK_DEBUG("%s: status %d, eversion %d", __func__, ever_evt->status, ever_evt->version);

	return ret_val;
}
#if 0 // just for reference
void load_rtl_firmware(void){
    firmware_info *fw_info;
    int ret_val,i;
    struct usb_device *dev;

    usb_init();

   /* scan all USB Devices */
   dev = NULL;
   for(i=0;i<USB_MAX_DEVICE;i++){
       dev=usb_get_dev_index(i); /* get device */
       if(dev == NULL)
            return;
       if(dev->devnum!=-1) {
           if(!strcmp(dev->mf,"Realtek") && !strcmp(dev->prod,"Bluetooth Radio")){
               /* Download BT Fireware */
               printf("Now Download BT Firmware.\n");
               fw_info = firmware_info_init(dev);
               get_firmware(fw_info);
                ret_val = download_data(fw_info);
        		if (ret_val > 0)
                    printf("Download fw patch done, fw len %d\n",ret_val);
                mdelay(10);
                set_wakeup_device(fw_info);
 //               set_bt_wakeup(fw_info);
               firmware_info_destroy(fw_info);
               }
         }
    }
}
#endif
int load_rtl_firmware_dev(struct osi_usb_device *dev)
{
    firmware_info *fw_info;
    int ret_val = -1;

    /* Download BT Fireware */
    RTK_DEBUG("Now Download BT Firmware.\n");
    fw_info = firmware_info_init(dev);
    if(NULL == fw_info)
        return -1;
    ret_val = get_firmware(fw_info);

    ret_val = reset_controller(fw_info);

    if(-1 == ret_val)
        return ret_val;
    ret_val = download_data(fw_info);

    if (ret_val > 0)
        RTK_DEBUG("Download fw patch done, fw len %d\n",ret_val);
    else
    {
        firmware_info_destroy(fw_info);
        return ret_val;
    }
    osi_rtk_mdelay(10);
    firmware_info_destroy(fw_info);
    return 0;
}

