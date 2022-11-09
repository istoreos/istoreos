/*
 * (C) Copyright 2017 Rockchip Electronics Co., Ltd
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */

#include <asm/suspend.h>
#include <common.h>

DECLARE_GLOBAL_DATA_PTR;

void cpu_suspend_save(struct pm_ctx *ctx, unsigned long sp)
{
	gd->pm_ctx_phys = (phys_addr_t)ctx;

	/* The content will be passed to cpu_do_resume as register sp */
	ctx->sp = sp;
	ctx->cpu_resume_addr = (phys_addr_t)cpu_do_resume;

	cpu_do_suspend(ctx->suspend_regs);

	flush_dcache_all();
}
