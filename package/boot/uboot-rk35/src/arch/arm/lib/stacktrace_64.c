// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (c) 2019 Fuzhou Rockchip Electronics Co., Ltd
 */

#include <common.h>
#include <stacktrace.h>

DECLARE_GLOBAL_DATA_PTR;

struct stackframe {
	uint64_t fp;
	uint64_t sp;
	uint64_t pc;
};

static __always_inline uint64_t read_fp(void)
{
	uint64_t val;

	asm volatile ("mov %0, x29" : "=r" (val));
	return val;
}

static __always_inline uint64_t read_lr(void)
{
	uint64_t val;

	asm volatile ("mov %0, x30" : "=r" (val));
	return val;
}

static __always_inline uint64_t read_pc(void)
{
	uint64_t val;

	asm volatile ("adr %0, ." : "=r" (val));
	return val;
}

/* It's not allowed to access sp_el2 in EL2, so always return a valid sp */
static __always_inline uint64_t read_sp(void)
{
	return gd->start_addr_sp - (CONFIG_SYS_STACK_SIZE / 2);
}

static bool walk_stackframe(struct stackframe *frame)
{
	ulong fp = frame->fp;

	if (fp > gd->start_addr_sp ||
	    fp < gd->start_addr_sp - CONFIG_SYS_STACK_SIZE)
		return false;

	frame->sp = fp + 0x10;
	frame->fp = *(ulong *)(fp);
	frame->pc = *(ulong *)(fp + 8);

	return true;
}

void dump_core_stack(struct pt_regs *regs)
{
	struct stackframe frame;
	ulong pc, lr;
#if defined(CONFIG_TPL_BUILD)
	char *build = "tpl";
#elif defined(CONFIG_SPL_BUILD)
	char *build = "spl";
#else
	char *build = "";
#endif

	frame.fp = regs->regs[29];
	frame.sp = regs->sp;
	frame.pc = regs->elr;

	if (gd->flags & GD_FLG_RELOC) {
		pc = (ulong)frame.pc - gd->reloc_off;
		lr = (ulong)regs->regs[30] - gd->reloc_off;
	} else {
		pc = (ulong)frame.pc;
		lr = (ulong)regs->regs[30];
	}

	printf("\nCall trace:\n");
	printf("  PC:	[< %08lx >]\n", pc);
	printf("  LR:	[< %08lx >]\n", lr);

	printf("\nStack:\n");
	do {
		if (gd->flags & GD_FLG_RELOC)
			pc = (ulong)frame.pc - gd->reloc_off;
		else
			pc = (ulong)frame.pc;

		printf("	[< %08lx >]\n", pc);
	} while (walk_stackframe(&frame));

	printf("\nCopy info from \"Call trace...\" to a file(eg. dump.txt), and run\n"
	       "command in your U-Boot project: "
	       "./scripts/stacktrace.sh dump.txt %s\n\n", build);
}

void dump_stack(void)
{
	struct pt_regs regs;

	regs.regs[29] = read_fp();
	regs.regs[30] = read_lr();
	regs.sp = read_sp();
	regs.elr = read_pc();

	dump_core_stack(&regs);
}
