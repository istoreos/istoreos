/*
 * Copyright 2017, Rockchip Electronics Co., Ltd
 * hisping lin, <hisping.lin@rock-chips.com>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */
#ifndef _OPTEE_CLIENT_RPC_H_
#define _OPTEE_CLIENT_RPC_H_

#include <optee_include/tee_base_types.h>
#include <optee_include/OpteeClientApiLib.h>

typedef struct{
	unsigned int Arg0;
	unsigned int Arg1;
	unsigned int Arg2;
	unsigned int Arg3;
	unsigned int Arg4;
	unsigned int Arg5;
	unsigned int Arg6;
	unsigned int Arg7;
} ARM_SMC_ARGS;

#define RPMB_PACKET_DATA_TO_UINT16(d) ((d[0] << 8) + (d[1]))
#define RPMB_PACKET_DATA_TO_UINT16(d) ((d[0] << 8) + (d[1]))
#define RPMB_STUFF_DATA_SIZE                        196
#define RPMB_KEY_MAC_SIZE                           32
#define RPMB_DATA_SIZE                              256
#define RPMB_NONCE_SIZE                             16
#define RPMB_DATA_FRAME_SIZE                        512

typedef struct rpmb_data_frame {
	unsigned char stuff_bytes[RPMB_STUFF_DATA_SIZE];
	unsigned char key_mac[RPMB_KEY_MAC_SIZE];
	unsigned char data[RPMB_DATA_SIZE];
	unsigned char nonce[RPMB_NONCE_SIZE];
	unsigned char write_counter[4];
	unsigned char address[2];
	unsigned char block_count[2];
	unsigned char op_result[2];
	unsigned char msg_type[2];
} EFI_RK_RPMB_DATA_PACKET;

typedef struct s_rpmb_back {
	unsigned char stuff[RPMB_STUFF_DATA_SIZE];
	unsigned char mac[RPMB_KEY_MAC_SIZE];
	unsigned char data[RPMB_DATA_SIZE];
	unsigned char nonce[RPMB_NONCE_SIZE];
	unsigned int write_counter;
	unsigned short address;
	unsigned short block_count;
	unsigned short result;
	unsigned short request;
} EFI_RK_RPMB_DATA_PACKET_BACK;

TEEC_Result OpteeRpcCallback(ARM_SMC_ARGS *ArmSmcArgs);

#endif /*_OPTEE_CLIENT_RPC_H_*/
