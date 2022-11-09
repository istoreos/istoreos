/* SPDX-License-Identifier:     GPL-2.0+
 *
 * Copyright 2019, Rockchip Electronics Co., Ltd
 * hisping lin, <hisping.lin@rock-chips.com>
 *
 */
#ifndef _OPTEE_TEST_H_
#define _OPTEE_TEST_H_

/*
 * test secure storage in rpmb when use emmc
 * test secure storage in security partition when use nand
 */
int test_secure_storage_default(void);

/*
 * test secure storage in security partition
 */
int test_secure_storage_security_partition(void);

#endif /*_OPTEE_TEST_H_*/
