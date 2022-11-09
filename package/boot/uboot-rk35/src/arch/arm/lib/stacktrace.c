// SPDX-License-Identifier: BSD-2-Clause
/*
 * Copyright (c) 2019 Fuzhou Rockchip Electronics Co., Ltd
 *
 * This file is taken and modified from the OP-TEE project.
 */

#include <common.h>
#include <stacktrace.h>
#include <asm/sections.h>

DECLARE_GLOBAL_DATA_PTR;

/* The register names */
#define	FP	11
#define	SP	13
#define	LR	14
#define	PC	15

/*
 * Definitions for the instruction interpreter.
 *
 * The ARM EABI specifies how to perform the frame unwinding in the
 * Exception Handling ABI for the ARM Architecture document. To perform
 * the unwind we need to know the initial frame pointer, stack pointer,
 * link register and program counter. We then find the entry within the
 * index table that points to the function the program counter is within.
 * This gives us either a list of three instructions to process, a 31-bit
 * relative offset to a table of instructions, or a value telling us
 * we can't unwind any further.
 *
 * When we have the instructions to process we need to decode them
 * following table 4 in section 9.3. This describes a collection of bit
 * patterns to encode that steps to take to update the stack pointer and
 * link register to the correct values at the start of the function.
 */

/* A special case when we are unable to unwind past this function */
#define	EXIDX_CANTUNWIND	1

/*
 * Entry types.
 * These are the only entry types that have been seen in the kernel.
 */
#define	ENTRY_MASK		0xff000000
#define	ENTRY_ARM_SU16		0x80000000
#define	ENTRY_ARM_LU16		0x81000000

/* Instruction masks. */
#define	INSN_VSP_MASK		0xc0
#define	INSN_VSP_SIZE_MASK	0x3f
#define	INSN_STD_MASK		0xf0
#define	INSN_STD_DATA_MASK	0x0f
#define	INSN_POP_TYPE_MASK	0x08
#define	INSN_POP_COUNT_MASK	0x07
#define	INSN_VSP_LARGE_INC_MASK	0xff

/* Instruction definitions */
#define	INSN_VSP_INC		0x00
#define	INSN_VSP_DEC		0x40
#define	INSN_POP_MASKED		0x80
#define	INSN_VSP_REG		0x90
#define	INSN_POP_COUNT		0xa0
#define	INSN_FINISH		0xb0
#define	INSN_POP_REGS		0xb1
#define	INSN_VSP_LARGE_INC	0xb2

#define SHIFT_U32(v, shift)	((uint32_t)(v) << (shift))

/* The state of the unwind process (32-bit mode) */
struct unwind_state_arm32 {
	uint32_t registers[16];
	uint32_t start_pc;
	ulong insn;
	unsigned int entries;
	unsigned int byte;
	uint16_t update_mask;
};

/* An item in the exception index table */
struct unwind_idx {
	uint32_t offset;
	uint32_t insn;
};

static __always_inline uint32_t read_pc(void)
{
	uint32_t val;

	asm volatile ("adr %0, ." : "=r" (val));
	return val;
}

static __always_inline uint32_t read_sp(void)
{
	uint32_t val;

	asm volatile ("mov %0, sp" : "=r" (val));
	return val;
}

static __always_inline uint32_t read_lr(void)
{
	uint32_t val;

	asm volatile ("mov %0, lr" : "=r" (val));
	return val;
}

static __always_inline uint32_t read_fp(void)
{
	uint32_t val;

	asm volatile ("mov %0, fp" : "=r" (val));
	return val;
}

static __always_inline uint32_t read_r7(void)
{
	uint32_t val;

	asm volatile ("mov %0, r7" : "=r" (val));
	return val;
}

static bool copy_in(void *dst, const void *src, size_t n, bool kernel_data)
{
	if (!kernel_data)
		return false;

	memcpy(dst, src, n);

	return true;
}

/* Expand a 31-bit signed value to a 32-bit signed value */
static int32_t expand_prel31(uint32_t prel31)
{
	return prel31 | SHIFT_U32(prel31 & BIT(30), 1);
}

/*
 * Perform a binary search of the index table to find the function
 * with the largest address that doesn't exceed addr.
 */
static struct unwind_idx *find_index(uint32_t addr, ulong exidx,
				     size_t exidx_sz)
{
	ulong idx_start, idx_end;
	unsigned int min, mid, max;
	struct unwind_idx *start;
	struct unwind_idx *item;
	int32_t prel31_addr;
	ulong func_addr;

	start = (struct unwind_idx *)exidx;
	idx_start = exidx;
	idx_end = exidx + exidx_sz;

	min = 0;
	max = (idx_end - idx_start) / sizeof(struct unwind_idx);

	while (min != max) {
		mid = min + (max - min + 1) / 2;

		item = &start[mid];

		prel31_addr = expand_prel31(item->offset);
		func_addr = (ulong)&item->offset + prel31_addr;

		if (func_addr <= addr) {
			min = mid;
		} else {
			max = mid - 1;
		}
	}

	return &start[min];
}

/* Reads the next byte from the instruction list */
static bool unwind_exec_read_byte(struct unwind_state_arm32 *state,
				  uint32_t *ret_insn, bool kernel_stack)
{
	uint32_t insn;

	if (!copy_in(&insn, (void *)state->insn, sizeof(insn), kernel_stack))
		return false;

	/* Read the unwind instruction */
	*ret_insn = (insn >> (state->byte * 8)) & 0xff;

	/* Update the location of the next instruction */
	if (state->byte == 0) {
		state->byte = 3;
		state->insn += sizeof(uint32_t);
		state->entries--;
	} else {
		state->byte--;
	}

	return true;
}

static bool pop_vsp(uint32_t *reg, ulong *vsp, bool kernel_stack,
		    ulong stack, size_t stack_size)
{
	if (*vsp > gd->start_addr_sp ||
	    *vsp < gd->start_addr_sp - CONFIG_SYS_STACK_SIZE)
		return false;

	if (!copy_in(reg, (void *)*vsp, sizeof(*reg), kernel_stack))
		return false;

	(*vsp) += sizeof(*reg);

	return true;
}

/* Executes the next instruction on the list */
static bool unwind_exec_insn(struct unwind_state_arm32 *state,
			     bool kernel_stack, ulong stack,
			     size_t stack_size)
{
	uint32_t insn;
	ulong vsp = state->registers[SP];
	int update_vsp = 0;

	/* Read the next instruction */
	if (!unwind_exec_read_byte(state, &insn, kernel_stack))
		return false;

	if ((insn & INSN_VSP_MASK) == INSN_VSP_INC) {
		state->registers[SP] += ((insn & INSN_VSP_SIZE_MASK) << 2) + 4;

	} else if ((insn & INSN_VSP_MASK) == INSN_VSP_DEC) {
		state->registers[SP] -= ((insn & INSN_VSP_SIZE_MASK) << 2) + 4;

	} else if ((insn & INSN_STD_MASK) == INSN_POP_MASKED) {
		uint32_t mask;
		unsigned int reg;

		/* Load the mask */
		if (!unwind_exec_read_byte(state, &mask, kernel_stack))
			return false;
		mask |= (insn & INSN_STD_DATA_MASK) << 8;

		/* We have a refuse to unwind instruction */
		if (mask == 0)
			return false;

		/* Update SP */
		update_vsp = 1;

		/* Load the registers */
		for (reg = 4; mask && reg < 16; mask >>= 1, reg++) {
			if (mask & 1) {
				if (!pop_vsp(&state->registers[reg], &vsp,
					     kernel_stack, stack, stack_size))
					return false;
				state->update_mask |= 1 << reg;

				/* If we have updated SP kep its value */
				if (reg == SP)
					update_vsp = 0;
			}
		}

	} else if ((insn & INSN_STD_MASK) == INSN_VSP_REG &&
	    ((insn & INSN_STD_DATA_MASK) != 13) &&
	    ((insn & INSN_STD_DATA_MASK) != 15)) {
		/* sp = register */
		state->registers[SP] =
		    state->registers[insn & INSN_STD_DATA_MASK];

	} else if ((insn & INSN_STD_MASK) == INSN_POP_COUNT) {
		unsigned int count, reg;

		/* Read how many registers to load */
		count = insn & INSN_POP_COUNT_MASK;

		/* Update sp */
		update_vsp = 1;

		/* Pop the registers */
		for (reg = 4; reg <= 4 + count; reg++) {
			if (!pop_vsp(&state->registers[reg], &vsp,
				     kernel_stack, stack, stack_size))
				return false;
			state->update_mask |= 1 << reg;
		}

		/* Check if we are in the pop r14 version */
		if ((insn & INSN_POP_TYPE_MASK) != 0) {
			if (!pop_vsp(&state->registers[14], &vsp, kernel_stack,
				     stack, stack_size))
				return false;
		}

	} else if (insn == INSN_FINISH) {
		/* Stop processing */
		state->entries = 0;

	} else if (insn == INSN_POP_REGS) {
		uint32_t mask;
		unsigned int reg;

		if (!unwind_exec_read_byte(state, &mask, kernel_stack))
			return false;
		if (mask == 0 || (mask & 0xf0) != 0)
			return false;

		/* Update SP */
		update_vsp = 1;

		/* Load the registers */
		for (reg = 0; mask && reg < 4; mask >>= 1, reg++) {
			if (mask & 1) {
				if (!pop_vsp(&state->registers[reg], &vsp,
					     kernel_stack, stack, stack_size))
					return false;
				state->update_mask |= 1 << reg;
			}
		}

	} else if ((insn & INSN_VSP_LARGE_INC_MASK) == INSN_VSP_LARGE_INC) {
		uint32_t uleb128;

		/* Read the increment value */
		if (!unwind_exec_read_byte(state, &uleb128, kernel_stack))
			return false;

		state->registers[SP] += 0x204 + (uleb128 << 2);

	} else {
		/* We hit a new instruction that needs to be implemented */
		printf("Unhandled instruction %.2x\n", insn);
		return false;
	}

	if (update_vsp)
		state->registers[SP] = vsp;

	return true;
}

/* Performs the unwind of a function */
static bool unwind_tab(struct unwind_state_arm32 *state, bool kernel_stack,
		       ulong stack, size_t stack_size)
{
	uint32_t entry;
	uint32_t insn;

	/* Set PC to a known value */
	state->registers[PC] = 0;

	if (!copy_in(&insn, (void *)state->insn, sizeof(insn), kernel_stack)) {
		printf("Bad insn addr %p", (void *)state->insn);
		return true;
	}

	/* Read the personality */
	entry = insn & ENTRY_MASK;

	if (entry == ENTRY_ARM_SU16) {
		state->byte = 2;
		state->entries = 1;
	} else if (entry == ENTRY_ARM_LU16) {
		state->byte = 1;
		state->entries = ((insn >> 16) & 0xFF) + 1;
	} else {
		printf("Unknown entry: %x\n", entry);
		return true;
	}

	while (state->entries > 0) {
		if (!unwind_exec_insn(state, kernel_stack, stack, stack_size))
			return true;
	}

	/*
	 * The program counter was not updated, load it from the link register.
	 */
	if (state->registers[PC] == 0) {
		state->registers[PC] = state->registers[LR];

		/*
		 * If the program counter changed, flag it in the update mask.
		 */
		if (state->start_pc != state->registers[PC])
			state->update_mask |= 1 << PC;

		/* Check again */
		if (state->registers[PC] == 0)
			return true;
	}

	return false;
}

bool unwind_stack_arm32(struct unwind_state_arm32 *state, ulong exidx,
			size_t exidx_sz, bool kernel_stack, ulong stack,
			size_t stack_size)
{
	struct unwind_idx *index;
	bool finished;

	if (!exidx_sz)
		return false;

	/* Reset the mask of updated registers */
	state->update_mask = 0;

	/* The pc value is correct and will be overwritten, save it */
	state->start_pc = state->registers[PC];

	/* Find the item to run */
	index = find_index(state->start_pc, exidx, exidx_sz);

	finished = false;
	if (index->insn != EXIDX_CANTUNWIND) {
		if (index->insn & (1U << 31)) {
			/* The data is within the instruction */
			state->insn = (ulong)&index->insn;
		} else {
			/* A prel31 offset to the unwind table */
			state->insn = (ulong)&index->insn +
				      expand_prel31(index->insn);
		}

		/* Run the unwind function */
		finished = unwind_tab(state, kernel_stack, stack, stack_size);
	}

	/* This is the top of the stack, finish */
	if (index->insn == EXIDX_CANTUNWIND)
		finished = true;

	return !finished;
}

static uint32_t offset_prel31(uint32_t addr, int32_t offset)
{
	return (addr + offset) & 0x7FFFFFFFUL;
}

int relocate_exidx(void *exidx, size_t exidx_sz, int32_t offset)
{
	size_t num_items = exidx_sz / sizeof(struct unwind_idx);
	struct unwind_idx *start = (struct unwind_idx *)exidx;
	size_t n;

	for (n = 0; n < num_items; n++) {
		struct unwind_idx *item = &start[n];

		if (item->offset & BIT(31))
			return -EINVAL;

		/* Offset to the start of the function has to be adjusted */
		item->offset = offset_prel31(item->offset, offset);

		if (item->insn == EXIDX_CANTUNWIND)
			continue;
		if (item->insn & BIT(31)) {
			/* insn is a table entry itself */
			continue;
		}
		/*
		 * insn is an offset to an entry in .ARM.extab so it has to be
		 * adjusted
		 */
		item->insn = offset_prel31(item->insn, offset);
	}
	return 0;
}

void print_stack_arm32(struct unwind_state_arm32 *state,
		       ulong exidx, size_t exidx_sz, bool kernel_stack,
		       ulong stack, size_t stack_size)
{
	ulong pc, lr;
#if defined(CONFIG_TPL_BUILD)
	char *build = "tpl";
#elif defined(CONFIG_SPL_BUILD)
	char *build = "spl";
#else
	char *build = "";
#endif

	if (gd->flags & GD_FLG_RELOC) {
		pc = (ulong)state->registers[PC] - gd->reloc_off;
		lr = (ulong)state->registers[LR] - gd->reloc_off;
	} else {
		pc = (ulong)state->registers[PC];
		lr = (ulong)state->registers[LR];
	}

	printf("\nCall trace:\n");
	printf("  PC:	[< %08lx >]\n", pc);
	printf("  LR:	[< %08lx >]\n", lr);

	printf("\nStack:\n");
	do {
		if (gd->flags & GD_FLG_RELOC)
			pc = (ulong)state->registers[PC] - gd->reloc_off;
		else
			pc = (ulong)state->registers[PC];

		printf("	[< %08lx >]\n", pc);
	} while (unwind_stack_arm32(state, exidx, exidx_sz,
				    kernel_stack, stack, stack_size));

	printf("\nCopy info from \"Call trace...\" to a file(eg. dump.txt), and run\n"
	       "command in your U-Boot project: "
	       "./scripts/stacktrace.sh dump.txt %s\n\n", build);
}

void dump_core_stack(struct pt_regs *regs)
{
	struct unwind_state_arm32 state;
	ulong exidx = (ulong)__exidx_start;
	size_t exidx_sz = (ulong)__exidx_end - (ulong)__exidx_start;
	ulong stack = gd->start_addr_sp;
	size_t stack_size = CONFIG_SYS_STACK_SIZE;
	int i;

	/* Don't use memset(), which updates LR ! */
	for (i = 0; i < 16; i++)
		state.registers[i] = 0;
	state.update_mask = 0;
	state.start_pc = 0;
	state.entries = 0;
	state.insn = 0;
	state.byte = 0;

	/* r7: Thumb-style frame pointer */
	state.registers[7] = regs->ARM_r7;
	/* r11: ARM-style frame pointer */
	state.registers[FP] = regs->ARM_ip;
	state.registers[SP] = regs->ARM_sp;
	state.registers[LR] = regs->ARM_lr;
	state.registers[PC] = regs->ARM_pc;

	print_stack_arm32(&state, exidx, exidx_sz,
			  true, stack, stack_size);
}

void dump_stack(void)
{
	struct pt_regs regs;

	regs.ARM_r7 = read_r7();
	regs.ARM_ip = read_fp();
	regs.ARM_sp = read_sp();
	regs.ARM_lr = read_lr();
	regs.ARM_pc = (uint32_t)dump_stack;

	dump_core_stack(&regs);
}
