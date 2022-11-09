/*
 * Copyright (c) 2016, Fuzhou Rockchip Electronics Co.,Ltd.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef TEE_SUPP_RK_FS_H
#define TEE_SUPP_RK_FS_H

/*
 * Operations and defines shared with TEE.
 */
#define OPTEE_MRF_OPEN			0
#define OPTEE_MRF_CREATE		1
#define OPTEE_MRF_CLOSE			2
#define OPTEE_MRF_READ			3
#define OPTEE_MRF_WRITE			4
#define OPTEE_MRF_TRUNCATE		5
#define OPTEE_MRF_REMOVE		6
#define OPTEE_MRF_RENAME		7
#define OPTEE_MRF_OPENDIR		8
#define OPTEE_MRF_CLOSEDIR		9
#define OPTEE_MRF_READDIR		10

/*
 * Open flags, defines shared with TEE.
 */
#define TEE_FS_O_RDONLY 0x1
#define TEE_FS_O_WRONLY 0x2
#define TEE_FS_O_RDWR   0x4
#define TEE_FS_O_CREAT  0x8
#define TEE_FS_O_EXCL   0x10
#define TEE_FS_O_APPEND 0x20

/*
 * Seek flags, defines shared with TEE.
 */
#define TEE_FS_SEEK_SET 0x1
#define TEE_FS_SEEK_END 0x2
#define TEE_FS_SEEK_CUR 0x4

/*
 * Mkdir flags, defines shared with TEE.
 */
#define TEE_FS_S_IWUSR 0x1
#define TEE_FS_S_IRUSR 0x2

/*
 * Access flags, X_OK not supported, defines shared with TEE.
 */
#define TEE_FS_R_OK    0x1
#define TEE_FS_W_OK    0x2
#define TEE_FS_F_OK    0x4

#define RK_FS_R    0x1
#define RK_FS_W    0x2
#define RK_FS_D    0x8

#define TEE_IOCTL_PARAM_ATTR_TYPE_MASK		0xff
#define TEE_IOCTL_PARAM_ATTR_TYPE_VALUE_INPUT	1
#define TEE_IOCTL_PARAM_ATTR_TYPE_VALUE_OUTPUT	2
#define TEE_IOCTL_PARAM_ATTR_TYPE_VALUE_INOUT	3	/* input and output */

#define TEE_IOCTL_PARAM_ATTR_TYPE_MEMREF_INPUT	5
#define TEE_IOCTL_PARAM_ATTR_TYPE_MEMREF_OUTPUT	6
#define TEE_IOCTL_PARAM_ATTR_TYPE_MEMREF_INOUT	7	/* input and output */

struct tee_ioctl_param_memref {
	uint64_t shm_offs;
	uint64_t size;
	int64_t shm_id;
};

struct tee_ioctl_param_value {
	uint64_t a;
	uint64_t b;
	uint64_t c;
};

struct tee_ioctl_param {
	uint64_t attr;
	union {
		struct tee_ioctl_param_memref memref;
		struct tee_ioctl_param_value value;
	} u;
};

/* Function Defines */
#define UNREFERENCED_PARAMETER(P) (P = P)
#define CHECKFLAG(flags, flag) (flags & flag)
#define ADDFLAG(flags, flag) (flags | flag)

#define RKSS_VERSION_V1			1
#define RKSS_VERSION_V2			2
#define RKSS_VERSION_ERR			100

int tee_supp_rk_fs_init_v1(void);

int tee_supp_rk_fs_process_v1(size_t num_params,
			struct tee_ioctl_param *params);

int tee_supp_rk_fs_init_v2(void);

int tee_supp_rk_fs_process_v2(size_t num_params,
			struct tee_ioctl_param *params);

int OpteeClientRkFsInit(void);

int OpteeClientRkFsProcess(size_t num_params,
			struct tee_ioctl_param *params);

#endif
