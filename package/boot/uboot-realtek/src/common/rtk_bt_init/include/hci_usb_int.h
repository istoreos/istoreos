#ifndef __RTLFW_H__
#define __RTLFW_H__

#include "../osi/include/osi_include_int.h"
#include "../osi/include/osi_include_ext.h"


/*******************************
**    Reasil patch code
********************************/
#define PKT_LEN			300
#define RCV_PKT_LEN     16
#define MSG_TO			1000
#define PATCH_SEG_MAX	252
#define DATA_END		0x80
#define CMD_HDR_LEN		sizeof(struct hci_command_hdr)
#define EVT_HDR_LEN		sizeof(struct hci_event_hdr)
#define CMD_CMP_LEN		sizeof(struct hci_ev_cmd_complete)

enum rtk_endpoit {
	CTRL_EP = 0,
	INTR_EP = 1,
	BULK_EP = 2,
	ISOC_EP = 3
};

#define MAX_URBS_QUEUED         5
struct hci_command_hdr {
	u16	opcode;		/* OCF & OGF */
	unsigned char	plen;
} __attribute__((packed));

struct hci_event_hdr {
	unsigned char	evt;
	unsigned char	plen;
} __attribute__((packed));

struct hci_ev_cmd_complete {
	unsigned char     ncmd;
	unsigned char     opcode[2];
} __attribute__((packed));

struct rtk_reset_evt {
    uint8_t status;
} __attribute__ ((packed));

struct rtk_eversion_evt {
	unsigned char status;
	unsigned char version;
} __attribute__ ((packed));

struct rtk_epatch_entry {
	unsigned short chip_id;
	unsigned short patch_length;
	unsigned int start_offset;
	unsigned int coex_version;
	unsigned int svn_version;
	unsigned int fw_version;
} __attribute__ ((packed));

struct rtk_epatch {
	unsigned char signature[8];
	unsigned int fw_version;
	unsigned short number_of_total_patch;
	struct rtk_epatch_entry entry[0];
} __attribute__ ((packed));

struct rtk_extension_entry {
	unsigned char opcode;
	unsigned char length;
	unsigned char *data;
} __attribute__ ((packed));


typedef struct {
	unsigned char index;
	unsigned char data[PATCH_SEG_MAX];
} __attribute__((packed)) download_cp;

typedef struct {
	unsigned char status;
	unsigned char index;
} __attribute__((packed)) download_rp;

typedef struct {
	struct osi_usb_interface	*intf;
	struct osi_usb_device		*udev;
	int			            pipe_in, pipe_out;
	unsigned char		*send_pkt;
	unsigned char		*rcv_pkt;
	struct hci_command_hdr		*cmd_hdr;
	struct hci_event_hdr		*evt_hdr;
	struct hci_ev_cmd_complete	*cmd_cmp;
	unsigned char		*req_para,	*rsp_para;
	unsigned char		*fw_data;
	int			pkt_len;
	int			fw_len;
} firmware_info;

extern int load_rtl_firmware_dev(struct osi_usb_device *dev);
#endif
