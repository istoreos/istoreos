/*
 * Copyright (C) (C) Copyright 2017 Rockchip Electronics Co., Ltd
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef __RKNAND_H__
#define __RKNAND_H__
/**
 * rknand_scan_namespace - scan all namespaces attached to RK NAND
 * controllers
 *
 * This probes all registered RK NAND uclass device drivers in the
 * system,and tries to find all namespaces attached to the RK NAND
 * controllers.
 *
 * @return:	0 on success, -ve on error
 */
int rknand_scan_namespace(void);
#endif /* __RKNAND_H__ */
