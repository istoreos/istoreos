/*
 * Copyright (c) 2021 Rockchip Electronics Co., Ltd
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */

#ifndef _NONDM_BOARD_HANDLE_H
#define _NONDM_BOARD_HANDLE_H

typedef void (*sysrest_request_t)(void enum sysreset_t type);
typedef int (*pinctrl_select_state_t)(enum uclass_id id, int devnum,
				      const char * statename);
typedef int (*clk_set_rate_t)(int clk_id, unsigned long rate);

struct nondm_ops {
	clk_set_rate_t *clk_set_rate;
	sysrest_request_t *sysreset_request;
	pinctrl_select_state_t *pinctrl_select_state;
};




















#endif
