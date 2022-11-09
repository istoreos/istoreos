/* SPDX-License-Identifier:     GPL-2.0+ */
/*
 * (C) Copyright 2019 Rockchip Electronics Co., Ltd
 */

#ifndef _STACKTRACE_
#define _STACKTRACE_

#include <common.h>

/* User should never call it */
void dump_core_stack(struct pt_regs *regs);

/* User API */
void dump_stack(void);

#endif
