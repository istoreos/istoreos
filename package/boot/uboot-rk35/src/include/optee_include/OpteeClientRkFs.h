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

#include <stddef.h>

/*
 * Operations and defines shared with TEE.
 */
#define TEE_FS_OPEN       1
#define TEE_FS_CLOSE      2
#define TEE_FS_READ       3
#define TEE_FS_WRITE      4
#define TEE_FS_SEEK       5
#define TEE_FS_UNLINK     6
#define TEE_FS_RENAME     7
#define TEE_FS_TRUNC      8
#define TEE_FS_MKDIR      9
#define TEE_FS_OPENDIR   10
#define TEE_FS_CLOSEDIR  11
#define TEE_FS_READDIR   12
#define TEE_FS_RMDIR     13
#define TEE_FS_ACCESS    14
#define TEE_FS_LINK      15

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

/* Function Defines */
#define UNREFERENCED_PARAMETER(P) (P = P)
#define CHECKFLAG(flags, flag) (flags & flag)
#define ADDFLAG(flags, flag) (flags | flag)

#define RKSS_VERSION_V1			1
#define RKSS_VERSION_V2			2
#define RKSS_VERSION_ERR			100

/*
 * Structure for file related RPC calls
 *
 * @op     The operation like open, close, read, write etc
 * @flags  Flags to the operation shared with secure world
 * @arg    Argument to operation
 * @fd     NW file descriptor
 * @len    Length of buffer at the end of this struct
 * @res    Result of the operation
 */
struct tee_fs_rpc {
	int op;
	int flags;
	int arg;
	int fd;
	uint32_t len;
	int res;
};

int tee_supp_rk_fs_init_v1(void);

int tee_supp_rk_fs_process_v1(void *cmd, size_t cmd_size);

int tee_supp_rk_fs_init_v2(void);

int tee_supp_rk_fs_process_v2(void *cmd, size_t cmd_size);

int OpteeClientRkFsInit(void);

int OpteeClientRkFsProcess(void *cmd, size_t cmd_size);

#endif
