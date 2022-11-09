/*
 * (C) Copyright 2017 Rockchip Electronics Co., Ltd
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */

#ifndef SUSPEND_H
#define SUSPEND_H
#include <common.h>
#include <asm-generic/global_data.h>

/* suspend/resume core functions */
void cpu_suspend_save(struct pm_ctx *ptr, unsigned long sp);
void cpu_do_suspend(unsigned long *ptr);

void cpu_resume(void);
void cpu_do_resume(void);

/*
 * Exported to platform suspend, arg will be passed to fn as r0
 * Return value: 0  - cpu resumed from suspended state.
 *               -1 - cpu not suspended.
 */
int cpu_suspend(unsigned long arg, int (*fn)(unsigned long));
#endif
