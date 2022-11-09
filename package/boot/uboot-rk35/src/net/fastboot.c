/*
* Copyright (C) 2016 The Android Open Source Project
*
* SPDX-License-Identifier: BSD-2-Clause
*/

#include <common.h>
#include <fastboot.h>
#include <fb_mmc.h>
#include <net.h>
#include <net/fastboot.h>
#include <part.h>
#include <stdlib.h>
#include <version.h>

/* Fastboot port # defined in spec */
#define WELL_KNOWN_PORT 5554

enum {
	FASTBOOT_ERROR = 0,
	FASTBOOT_QUERY = 1,
	FASTBOOT_INIT = 2,
	FASTBOOT_FASTBOOT = 3,
};

struct __attribute__((packed)) fastboot_header {
	uchar id;
	uchar flags;
	unsigned short seq;
};

#define PACKET_SIZE 1024
#define FASTBOOT_HEADER_SIZE sizeof(struct fastboot_header)
#define DATA_SIZE (PACKET_SIZE - FASTBOOT_HEADER_SIZE)
#define FASTBOOT_VERSION "0.4"

/* Sequence number sent for every packet */
static unsigned short fb_sequence_number = 1;
static const unsigned short fb_packet_size = PACKET_SIZE;
static const unsigned short fb_udp_version = 1;

/* Keep track of last packet for resubmission */
static uchar last_packet[PACKET_SIZE];
static unsigned int last_packet_len = 0;

/* Parsed from first fastboot command packet */
static char *cmd_string = NULL;
static char *cmd_parameter = NULL;

/* Fastboot download parameters */
static unsigned int bytes_received = 0;
static unsigned int bytes_expected = 0;
static unsigned int image_size = 0;

static struct in_addr fastboot_remote_ip;
/* The UDP port at their end */
static int fastboot_remote_port;
/* The UDP port at our end */
static int fastboot_our_port;

static void fb_getvar(char*);
static void fb_download(char*, unsigned int, char*);
static void fb_flash(char*);
static void fb_erase(char*);
static void fb_continue(char*);
static void fb_reboot(char*);
static void boot_downloaded_image(void);
static void cleanup_command_data(void);
static void write_fb_response(const char*, const char*, char*);

void fastboot_send_info(const char *msg)
{
	uchar *packet;
	uchar *packet_base;
	int len = 0;
	char response[FASTBOOT_RESPONSE_LEN] = {0};

	struct fastboot_header fb_response_header =
	{
		.id = FASTBOOT_FASTBOOT,
		.flags = 0,
		.seq = htons(fb_sequence_number)
	};
	++fb_sequence_number;
	packet = net_tx_packet + net_eth_hdr_size() + IP_UDP_HDR_SIZE;
	packet_base = packet;

	/* Write headers */
	memcpy(packet, &fb_response_header, sizeof(fb_response_header));
	packet += sizeof(fb_response_header);
	/* Write response */
	write_fb_response("INFO", msg, response);
	memcpy(packet, response, strlen(response));
	packet += strlen(response);

	len = packet-packet_base;

	/* Save packet for retransmitting */
	last_packet_len = len;
	memcpy(last_packet, packet_base, last_packet_len);

	net_send_udp_packet(net_server_ethaddr, fastboot_remote_ip,
			    fastboot_remote_port, fastboot_our_port, len);
}

/**
 * Constructs and sends a packet in response to received fastboot packet
 *
 * @param fb_header            Header for response packet
 * @param fastboot_data        Pointer to received fastboot data
 * @param fastboot_data_len    Length of received fastboot data
 * @param retransmit           Nonzero if sending last sent packet
 */
static void fastboot_send(struct fastboot_header fb_header, char *fastboot_data,
		unsigned int fastboot_data_len, uchar retransmit)
{
	uchar *packet;
	uchar *packet_base;
	int len = 0;
	const char *error_msg = "An error occurred.";
	short tmp;
	struct fastboot_header fb_response_header = fb_header;
	char response[FASTBOOT_RESPONSE_LEN] = {0};
	/*
	 *	We will always be sending some sort of packet, so
	 *	cobble together the packet headers now.
	 */
	packet = net_tx_packet + net_eth_hdr_size() + IP_UDP_HDR_SIZE;
	packet_base = packet;

	/* Resend last packet */
	if (retransmit) {
		memcpy(packet, last_packet, last_packet_len);
		net_send_udp_packet(net_server_ethaddr, fastboot_remote_ip,
				    fastboot_remote_port, fastboot_our_port, last_packet_len);
		return;
	}

	fb_response_header.seq = htons(fb_response_header.seq);
	memcpy(packet, &fb_response_header, sizeof(fb_response_header));
	packet += sizeof(fb_response_header);

	switch (fb_header.id) {
	case FASTBOOT_QUERY:
		tmp = htons(fb_sequence_number);
		memcpy(packet, &tmp, sizeof(tmp));
		packet += sizeof(tmp);
		break;
	case FASTBOOT_INIT:
		tmp = htons(fb_udp_version);
		memcpy(packet, &tmp, sizeof(tmp));
		packet += sizeof(tmp);
		tmp = htons(fb_packet_size);
		memcpy(packet, &tmp, sizeof(tmp));
		packet += sizeof(tmp);
		break;
	case FASTBOOT_ERROR:
		memcpy(packet, error_msg, strlen(error_msg));
		packet += strlen(error_msg);
		break;
	case FASTBOOT_FASTBOOT:
		if (cmd_string == NULL) {
			/* Parse command and send ack */
			cmd_parameter = fastboot_data;
			cmd_string = strsep(&cmd_parameter, ":");
			cmd_string = strdup(cmd_string);
			if (cmd_parameter) {
				cmd_parameter = strdup(cmd_parameter);
			}
		} else if (!strcmp("getvar", cmd_string)) {
			fb_getvar(response);
		} else if (!strcmp("download", cmd_string)) {
			fb_download(fastboot_data, fastboot_data_len, response);
		} else if (!strcmp("flash", cmd_string)) {
			fb_flash(response);
		} else if (!strcmp("erase", cmd_string)) {
			fb_erase(response);
		} else if (!strcmp("boot", cmd_string)) {
			write_fb_response("OKAY", "", response);
		} else if (!strcmp("continue", cmd_string)) {
			fb_continue(response);
		} else if (!strncmp("reboot", cmd_string, 6)) {
			fb_reboot(response);
		} else if (!strcmp("set_active", cmd_string)) {
			/* A/B not implemented, for now do nothing */
			write_fb_response("OKAY", "", response);
		} else {
			error("command %s not implemented.\n", cmd_string);
			write_fb_response("FAIL", "unrecognized command", response);
		}
		/* Sent some INFO packets, need to update sequence number in header */
		if (fb_header.seq != fb_sequence_number) {
			fb_response_header.seq = htons(fb_sequence_number);
			memcpy(packet_base, &fb_response_header, sizeof(fb_response_header));
		}
		/* Write response to packet */
		memcpy(packet, response, strlen(response));
		packet += strlen(response);
		break;
	default:
		error("ID %d not implemented.\n", fb_header.id);
		return;
	}

	len = packet-packet_base;

	/* Save packet for retransmitting */
	last_packet_len = len;
	memcpy(last_packet, packet_base, last_packet_len);

	net_send_udp_packet(net_server_ethaddr, fastboot_remote_ip,
			    fastboot_remote_port, fastboot_our_port, len);

	/* Continue boot process after sending response */
	if (!strncmp("OKAY", response, 4)) {
		if (!strcmp("boot", cmd_string)) {
			boot_downloaded_image();
		} else if (!strcmp("continue", cmd_string)) {
			run_command(getenv("bootcmd"), CMD_FLAG_ENV);
		} else if (!strncmp("reboot", cmd_string, 6)) {
			/* Matches reboot or reboot-bootloader */
			do_reset(NULL, 0, 0, NULL);
		}
	}

	/* OKAY and FAIL indicate command is complete */
	if (!strncmp("OKAY", response, 4) ||
			!strncmp("FAIL", response, 4)) {
		cleanup_command_data();
	}
}

/**
 * Writes ascii string specified by cmd_parameter to response.
 *
 * @param repsonse    Pointer to fastboot response buffer
 */
static void fb_getvar(char *response)
{

	if (cmd_parameter == NULL) {
		write_fb_response("FAIL", "missing var", response);
	} else if (!strcmp("version", cmd_parameter)) {
		write_fb_response("OKAY", FASTBOOT_VERSION, response);
	} else if (!strcmp("bootloader-version", cmd_parameter) ||
			!strcmp("version-bootloader", cmd_parameter)) {
		write_fb_response("OKAY", U_BOOT_VERSION, response);
	} else if (!strcmp("downloadsize", cmd_parameter) ||
			!strcmp("max-download-size", cmd_parameter)) {
		char buf_size_str[12];
		sprintf(buf_size_str, "0x%08x", CONFIG_FASTBOOT_BUF_SIZE);
		write_fb_response("OKAY", buf_size_str, response);
	} else if (!strcmp("serialno", cmd_parameter)) {
		const char *tmp = getenv("serial#");
		if (tmp) {
			write_fb_response("OKAY", tmp, response);
		} else {
			write_fb_response("FAIL", "Value not set", response);
		}
	} else if (!strcmp("version-baseband", cmd_parameter)) {
		write_fb_response("OKAY", "N/A", response);
	} else if (!strcmp("product", cmd_parameter)) {
		const char *board = getenv("board");
		if (board) {
			write_fb_response("OKAY", board, response);
		} else {
			write_fb_response("FAIL", "Board not set", response);
		}
	} else if (!strcmp("current-slot", cmd_parameter)) {
		/* A/B not implemented, for now always return _a */
		write_fb_response("OKAY", "_a", response);
	} else if (!strcmp("slot-suffixes", cmd_parameter)) {
		write_fb_response("OKAY", "_a,_b", response);
	} else if (!strncmp("has-slot", cmd_parameter, 8)) {
		char *part_name = cmd_parameter;

		cmd_parameter = strsep(&part_name, ":");
		if (!strcmp(part_name, "boot") || !strcmp(part_name, "system")) {
			write_fb_response("OKAY", "yes", response);
		} else {
			write_fb_response("OKAY", "no", response);
		}
	} else if (!strncmp("partition-type", cmd_parameter, 14) ||
		   !strncmp("partition-size", cmd_parameter, 14)) {
		disk_partition_t part_info;
		struct blk_desc *dev_desc;
		char *part_name = cmd_parameter;
		char part_size_str[20];

		cmd_parameter = strsep(&part_name, ":");
		dev_desc = blk_get_dev("mmc", 0);
		if (!dev_desc) {
			write_fb_response("FAIL", "block device not found", response);
		} else if (part_get_info_efi_by_name(dev_desc, part_name, &part_info) < 0) {
			write_fb_response("FAIL", "partition not found", response);
		} else if (!strncmp("partition-type", cmd_parameter, 14)) {
			write_fb_response("OKAY", (char*)part_info.type, response);
		} else if (!strncmp("partition-size", cmd_parameter, 14)) {
			sprintf(part_size_str, "0x%016x", (int)part_info.size);
			write_fb_response("OKAY", part_size_str, response);
		}
	} else {
		printf("WARNING: unknown variable: %s\n", cmd_parameter);
		write_fb_response("FAIL", "Variable not implemented", response);
	}
}

/**
 * Copies image data from fastboot_data to CONFIG_FASTBOOT_BUF_ADDR.
 * Writes to response.
 *
 * @param fastboot_data        Pointer to received fastboot data
 * @param fastboot_data_len    Length of received fastboot data
 * @param repsonse             Pointer to fastboot response buffer
 */
static void fb_download(char *fastboot_data, unsigned int fastboot_data_len,
		char *response)
{
	char *tmp;

	if (bytes_expected == 0) {
		if (cmd_parameter == NULL) {
			write_fb_response("FAIL", "Expected command parameter", response);
			return;
		}
		bytes_expected = simple_strtoul(cmd_parameter, &tmp, 16);
		if (bytes_expected == 0) {
			write_fb_response("FAIL", "Expected nonzero image size", response);
			return;
		}
	}
	if (fastboot_data_len == 0 && bytes_received == 0) {
		/* Nothing to download yet. Response is of the form:
		 * [DATA|FAIL]$cmd_parameter
		 *
		 * where cmd_parameter is an 8 digit hexadecimal number
		 */
		if (bytes_expected > CONFIG_FASTBOOT_BUF_SIZE) {
			write_fb_response("FAIL", cmd_parameter, response);
		} else {
			write_fb_response("DATA", cmd_parameter, response);
		}
	} else if (fastboot_data_len == 0 && (bytes_received >= bytes_expected)) {
		/* Download complete. Respond with "OKAY" */
		write_fb_response("OKAY", "", response);
		image_size = bytes_received;
		bytes_expected = bytes_received = 0;
	} else {
		if (fastboot_data_len == 0 ||
				(bytes_received + fastboot_data_len) > bytes_expected) {
			write_fb_response("FAIL", "Received invalid data length", response);
			return;
		}
		/* Download data to CONFIG_FASTBOOT_BUF_ADDR */
		memcpy((void*)CONFIG_FASTBOOT_BUF_ADDR + bytes_received, fastboot_data,
				fastboot_data_len);
		bytes_received += fastboot_data_len;
	}
}

/**
 * Writes the previously downloaded image to the partition indicated by
 * cmd_parameter. Writes to response.
 *
 * @param repsonse    Pointer to fastboot response buffer
 */
static void fb_flash(char *response)
{
	fb_mmc_flash_write(cmd_parameter, (void*)CONFIG_FASTBOOT_BUF_ADDR,
			image_size, response);
}

/**
 * Erases the partition indicated by cmd_parameter (clear to 0x00s). Writes
 * to response.
 *
 * @param repsonse    Pointer to fastboot response buffer
 */
static void fb_erase(char *response)
{
	fb_mmc_erase(cmd_parameter, response);
}

/**
 * Continues normal boot process by running "bootcmd". Writes
 * to response.
 *
 * @param repsonse    Pointer to fastboot response buffer
 */
static void fb_continue(char *response)
{
	char *bootcmd;
	bootcmd = getenv("bootcmd");
	if (bootcmd) {
		write_fb_response("OKAY", "", response);
	} else {
		write_fb_response("FAIL", "bootcmd not set", response);
	}
}

/**
 * Sets reboot bootloader flag if requested. Writes to response.
 *
 * @param repsonse    Pointer to fastboot response buffer
 */
static void fb_reboot(char *response)
{
	write_fb_response("OKAY", "", response);
	if (!strcmp("reboot-bootloader", cmd_string)) {
		strcpy((char*)CONFIG_FASTBOOT_BUF_ADDR, "reboot-bootloader");
	}
}

/**
 * Boots into downloaded image.
 */
static void boot_downloaded_image(void)
{
	char kernel_addr[12];
	char *fdt_addr = getenv("fdt_addr_r");
	char *bootm_args[] = { "bootm", kernel_addr, "-", fdt_addr, NULL };

	sprintf(kernel_addr, "0x%lx", (long)CONFIG_FASTBOOT_BUF_ADDR);

	printf("\nBooting kernel at %s with fdt at %s...\n\n\n",
			kernel_addr, fdt_addr);
	do_bootm(NULL, 0, 4, bootm_args);

	/* This only happens if image is faulty so we start over. */
	do_reset(NULL, 0, 0, NULL);
}

/**
 * Writes a response to response buffer of the form "$tag$reason".
 *
 * @param tag         The first part of the response
 * @param reason      The second part of the response
 * @param repsonse    Pointer to fastboot response buffer
 */
static void write_fb_response(const char* tag, const char *reason,
		char *response)
{
	strncpy(response, tag, strlen(tag));
	strncat(response, reason, FASTBOOT_RESPONSE_LEN - strlen(tag) - 1);
}

/**
 * Frees any resources allocated during current fastboot command.
 */
static void cleanup_command_data(void)
{
	/* cmd_parameter and cmd_string potentially point to memory allocated by
	 * strdup
	 */
	if (cmd_parameter) {
		free(cmd_parameter);
	}
	if (cmd_string) {
		free(cmd_string);
	}
	cmd_parameter = cmd_string = NULL;
}

/**
 * Incoming UDP packet handler.
 *
 * @param packet  Pointer to incoming UDP packet
 * @param dport   Destination UDP port
 * @param sip     Source IP address
 * @param sport   Source UDP port
 * @param len     Packet length
 */
static void fastboot_handler(uchar *packet, unsigned dport, struct in_addr sip,
		unsigned sport, unsigned len)
{
	struct fastboot_header fb_header;
	char fastboot_data[DATA_SIZE] = {0};
	unsigned int fastboot_data_len = 0;

	if (dport != fastboot_our_port) {
		return;
	}

	fastboot_remote_ip = sip;
	fastboot_remote_port = sport;

	if (len < FASTBOOT_HEADER_SIZE || len > PACKET_SIZE) {
		return;
	}
	memcpy(&fb_header, packet, sizeof(fb_header));
	fb_header.flags = 0;
	fb_header.seq = ntohs(fb_header.seq);
	packet += sizeof(fb_header);
	len -= sizeof(fb_header);

	switch (fb_header.id) {
	case FASTBOOT_QUERY:
		fastboot_send(fb_header, fastboot_data, 0, 0);
		break;
	case FASTBOOT_INIT:
	case FASTBOOT_FASTBOOT:
		fastboot_data_len = len;
		if (len > 0) {
			memcpy(fastboot_data, packet, len);
		}
		if (fb_header.seq == fb_sequence_number) {
			fastboot_send(fb_header, fastboot_data, fastboot_data_len, 0);
			fb_sequence_number++;
		} else if (fb_header.seq == fb_sequence_number - 1) {
			/* Retransmit last sent packet */
			fastboot_send(fb_header, fastboot_data, fastboot_data_len, 1);
		}
		break;
	default:
		error("ID %d not implemented.\n", fb_header.id);
		fb_header.id = FASTBOOT_ERROR;
		fastboot_send(fb_header, fastboot_data, 0, 0);
		break;
	}
}

void fastboot_start_server(void)
{
	printf("Using %s device\n", eth_get_name());
	printf("Listening for fastboot command on %pI4\n", &net_ip);

	fastboot_our_port = WELL_KNOWN_PORT;

	net_set_udp_handler(fastboot_handler);

	/* zero out server ether in case the server ip has changed */
	memset(net_server_ethaddr, 0, 6);
}
