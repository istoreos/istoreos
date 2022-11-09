/*
 * Copyright (C) 2018 Rockchip Electronics Co., Ltd
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef __RKSFC_H__
#define __RKSFC_H__
/**
 * rksfc_scan_namespace - scan all namespaces attached to RK SFC
 * controllers
 *
 * This probes all registered RK SFC uclass device drivers in the
 * system,and tries to find all namespaces attached to the RK SFC
 * controllers.
 *
 * @return:	0 on success, -ve on error
 */
int rksfc_scan_namespace(void);
#endif
