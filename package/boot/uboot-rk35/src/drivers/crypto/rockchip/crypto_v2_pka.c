// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (c) 2019 Fuzhou Rockchip Electronics Co., Ltd
 */

#include <common.h>
#include <crypto.h>
#include <dm.h>
#include <linux/errno.h>
#include <rockchip/crypto_v2.h>
#include <rockchip/crypto_v2_pka.h>

#define CRYPT_OK	(0)
#define CRYPT_ERROR	(-1)

void rk_pka_ram_ctrl_enable(void)
{
	crypto_write((CRYPTO_RAM_PKA_RDY << CRYPTO_WRITE_MASK_SHIFT) |
		     CRYPTO_RAM_PKA_RDY, CRYPTO_RAM_CTL);
}

void rk_pka_ram_ctrl_disable(void)
{
	crypto_write((CRYPTO_RAM_PKA_RDY << CRYPTO_WRITE_MASK_SHIFT),
		     CRYPTO_RAM_CTL);
}

void rk_pka_wait_on_ram_ready(void)
{
	u32 output_reg_val;

	do {
		output_reg_val = crypto_read(CRYPTO_RAM_ST);
	} while ((output_reg_val & 0x01) != CRYPTO_CLK_RAM_RDY);
}

void rk_pka_wait_on_pipe_ready(void)
{
	u32 output_reg_val;

	do {
		output_reg_val = crypto_read(CRYPTO_PKA_PIPE_RDY);
	} while ((output_reg_val & 0x01) != RK_PKA_PIPE_READY);
}

void rk_pka_wait_on_done(void)
{
	u32 output_reg_val;

	do {
		output_reg_val = crypto_read(CRYPTO_PKA_DONE);
	} while ((output_reg_val & 0x01) != RK_PKA_OP_DONE);
}

void rk_pka_set_startmemaddr_reg(u32 start_mem_addr)
{
	crypto_write(start_mem_addr, CRYPTO_PKA_MON_READ);
}

void rk_pka_set_N_NP_T0_T1_reg(u32 N, u32 NP, u32 T0,
			       u32 T1)
{
	rk_pka_wait_on_done();
	crypto_write((u32)((N) << RK_PKA_N_NP_T0_T1_REG_N_POS |
				(NP) << RK_PKA_N_NP_T0_T1_REG_NP_POS |
				(T0) << RK_PKA_N_NP_T0_T1_REG_T0_POS |
				(T1) << RK_PKA_N_NP_T0_T1_REG_T1_POS),
				CRYPTO_N_NP_T0_T1_ADDR);
}

void rk_pka_set_default_N_NP_T0_T1_reg(void)
{
	crypto_write(RK_PKA_N_NP_T0_T1_REG_DEFAULT_VAL, CRYPTO_N_NP_T0_T1_ADDR);
}

void rk_pka_get_status(u32 *status)
{
	rk_pka_wait_on_done();
	*status = crypto_read(CRYPTO_PKA_STATUS);
}

void rk_pka_get_status_alu_outzero(u32 *status)
{
	rk_pka_wait_on_done();
	*status = crypto_read(CRYPTO_PKA_STATUS);
	*status = ((*status) >> RK_PKA_STATUS_ALU_OUT_ZERO_POS) & 1UL;
}

void rk_pka_get_status_mod_overfl(u32 *status)
{
	rk_pka_wait_on_done();
	*status = crypto_read(CRYPTO_PKA_STATUS);
	*status = ((*status) >> RK_PKA_STATUS_ALU_MODOVRFLW_POS) & 1;
}

void rk_pka_get_status_div_byzero(u32 *status)
{
	rk_pka_wait_on_done();
	*status = crypto_read(CRYPTO_PKA_STATUS);
	*status = ((*status) >> RK_PKA_STATUS_DIV_BY_ZERO_POS) & 1;
}

void rk_pka_get_status_carry(u32 *status)
{
	rk_pka_wait_on_done();
	*status = crypto_read(CRYPTO_PKA_STATUS);
	*status = ((*status) >> RK_PKA_STATUS_ALU_CARRY_POS) & 1;
}

void rk_pka_get_status_alu_signout(u32 *status)
{
	rk_pka_wait_on_done();
	*status = crypto_read(CRYPTO_PKA_STATUS);
	*status = ((*status) >> RK_PKA_STATUS_ALU_SIGN_OUT_POS) & 1;
}

void rk_pka_get_status_modinv_ofzero(u32 *status)
{
	rk_pka_wait_on_done();
	*status = crypto_read(CRYPTO_PKA_STATUS);
	*status = ((*status) >> RK_PKA_STATUS_MODINV_OF_ZERO_POS) & 1;
}

void rk_pka_get_status_opcode(u32 *status)
{
	rk_pka_wait_on_done();
	*status = crypto_read(CRYPTO_PKA_STATUS);
	*status = ((*status) >> RK_PKA_STATUS_OPCODE_POS) &
			  RK_PKA_STATUS_OPCODE_MASK;
}

void rk_pka_get_status_tag(u32 *status)
{
	rk_pka_wait_on_done();
	*status = crypto_read(CRYPTO_PKA_STATUS);
	*status = ((*status) >> RK_PKA_STATUS_TAG_POS) & RK_PKA_STATUS_TAG_MASK;
}

void rk_pka_set_regsize(u32 size_bits, u32 entry_num)
{
	rk_pka_wait_on_done();
	crypto_write(size_bits, CRYPTO_PKA_L0 + 4 * (entry_num));
}

void rk_pka_read_regsize(u32 *size_bits, u32 entry_num)
{
	rk_pka_wait_on_done();
	*size_bits = crypto_read(CRYPTO_PKA_L0 + 4 * (entry_num));
}

void rk_pka_set_regaddr(u32 vir_reg, u32 phys_addr)
{
	rk_pka_wait_on_done();
	crypto_write(phys_addr, CRYPTO_MEMORY_MAP0 + 4 * (vir_reg));
}

void rk_pka_get_regaddr(u32 vir_reg, u32 *phys_addr)
{
	*phys_addr = crypto_read(CRYPTO_MEMORY_MAP0 + 4 * (vir_reg));
}

void rk_pka_read_regaddr(u32 vir_reg, u32 *phys_addr)
{
	rk_pka_wait_on_done();
	*phys_addr = crypto_read(CRYPTO_MEMORY_MAP0 + 4 * (vir_reg));
}

u32 rk_pka_make_full_opcode(u32 opcode, u32 len_id,
			    u32 is_a_immed, u32 op_a,
			    u32 is_b_immed, u32 op_b,
			    u32 res_discard, u32 res,
			    u32 tag)
{
	u32 full_opcode;

	full_opcode =
		(((u32)(opcode) & 31) << RK_PKA_OPCODE_OPERATION_ID_POS |
		((u32)(len_id) & 7) << RK_PKA_OPCODE_LEN_POS |
		((u32)(is_a_immed) & 1) << RK_PKA_OPCODE_OPERAND_1_IMMED_POS |
		((u32)(op_a) & 31)	<< RK_PKA_OPCODE_OPERAND_1_POS	|
		((u32)(is_b_immed) & 1) << RK_PKA_OPCODE_OPERAND_2_IMMED_POS |
		((u32)(op_b) & 31) << RK_PKA_OPCODE_OPERAND_2_POS	|
		((u32)(res_discard) & 1) << RK_PKA_OPCODE_R_DISCARD_POS	|
		((u32)(res) & 31) << RK_PKA_OPCODE_RESULT_POS |
		((u32)(tag) & 31) << RK_PKA_OPCODE_TAG_POS);
	return full_opcode;
}

void rk_pka_hw_load_value2pka_mem(u32 addr, u32 val)
{
	u32 *vaddr;

	vaddr = (u32 *)((addr) + RK_PKA_DATA_REGS_MEMORY_OFFSET_ADDR);
	rk_pka_ram_ctrl_disable();
	rk_pka_wait_on_ram_ready();
	*vaddr = val;
	rk_pka_ram_ctrl_enable();
}

void rk_pka_hw_load_block2pka_mem(u32 addr, u32 *ptr,
				  u32 size_words)
{
	u8 *vaddr =
		(u8 *)((addr) + RK_PKA_DATA_REGS_MEMORY_OFFSET_ADDR);

	rk_pka_ram_ctrl_disable();
	rk_pka_wait_on_ram_ready();
	RK_PKA_FastMemCpy(vaddr, (u8 *)ptr, size_words);
	rk_pka_ram_ctrl_enable();
}

void rk_pka_hw_reverse_load_block2pka_mem(u32 addr, u32 *ptr,
					  u32 size_words)
{
	u8 *vaddr =
		(u8 *)((addr) + RK_PKA_DATA_REGS_MEMORY_OFFSET_ADDR);

	rk_pka_ram_ctrl_disable();
	rk_pka_wait_on_ram_ready();
	RK_PKA_ReverseMemcpy(vaddr, (u8 *)ptr, size_words);
	rk_pka_ram_ctrl_enable();
}

void rk_pka_hw_clear_pka_mem(u32 addr, u32 size_words)
{
	u8 *vaddr =
		(u8 *)((addr) + RK_PKA_DATA_REGS_MEMORY_OFFSET_ADDR);

	rk_pka_ram_ctrl_disable();
	rk_pka_wait_on_ram_ready();
	RK_PKA_MemSetZero(vaddr, size_words);
	rk_pka_ram_ctrl_enable();
}

void rk_pka_hw_read_value_from_pka_mem(u32 addr, u32 *val)
{
	u32 *vaddr;

	vaddr = (u32 *)((addr) + RK_PKA_DATA_REGS_MEMORY_OFFSET_ADDR);
	rk_pka_ram_ctrl_disable();
	rk_pka_wait_on_ram_ready();
	*val = *vaddr;
	rk_pka_ram_ctrl_enable();
}

void rk_pka_hw_read_block_from_pka_mem(u32 addr, u32 *ptr,
				       u32 size_words)
{
	u8 *vaddr =
		(u8 *)((addr) + RK_PKA_DATA_REGS_MEMORY_OFFSET_ADDR);

	rk_pka_ram_ctrl_disable();
	rk_pka_wait_on_ram_ready();
	RK_PKA_FastMemCpy((u8 *)(ptr), vaddr, size_words);
	rk_pka_ram_ctrl_enable();
}

void rk_pka_hw_reverse_read_block_from_pka_mem(u32 addr, u32 *ptr,
					       u32 size_words)
{
	u8 *vaddr =
		(u8 *)((addr) + RK_PKA_DATA_REGS_MEMORY_OFFSET_ADDR);

	rk_pka_ram_ctrl_disable();
	rk_pka_wait_on_ram_ready();
	RK_PKA_ReverseMemcpy((u8 *)(ptr), vaddr,
			     size_words * sizeof(u32));
	rk_pka_ram_ctrl_enable();
}

u32 rk_pka_exec_operation(u32 opcode, u8 len_id,
			  u8 is_a_immed, s8 op_a,
			  u8 is_b_immed, s8 op_b,
			  u8 res_discard, s8 res, u8 tag)
{
	u32 status;
	u32 full_opcode;
	u32 error = CRYPT_OK;

	if (res == RES_DISCARD) {
		res_discard = 1;
		res = 0;
	}

	full_opcode = rk_pka_make_full_opcode(opcode, len_id,
					      is_a_immed, op_a,
					      is_b_immed, op_b,
					      res_discard, res, tag);

	/* write full opcode into PKA CRYPTO_OPCODE register */
	crypto_write(full_opcode, CRYPTO_OPCODE);

	/*************************************************/
	/* finishing operations for different cases      */
	/*************************************************/
	switch (opcode) {
	case PKA_Div:
		/* for Div operation check, that op_b != 0*/
		rk_pka_get_status_div_byzero(&status);
		if (status == 1) {
			error = RK_PKA_DIVIDER_IS_NULL_ERROR;
			goto end;
		}
		break;
	case PKA_Terminate:
		/* wait for PKA done bit */
		rk_pka_wait_on_done();
		break;
	default:
		/* wait for PKA pipe ready bit */
		rk_pka_wait_on_pipe_ready();
	}

end:
	return error;
}

u32 rk_pka_set_sizes_tab(u32 regs_sizes_ptr[RK_PKA_MAX_REGS_COUNT],
			 u32 count_of_sizes, u32 max_size_bits,
			 u32 is_default_map)
{
	u32 i;
	u32 error;
	u32 max_size, min_size, maxsize_words;

	error = CRYPT_OK;
	max_size = 0;
	min_size = 0xFFFFFFFF;

	if (is_default_map > 1)
		return  RK_PKA_SET_MAP_MODE_ERROR;

	/* 1. Case of user defined settings */
	if (is_default_map == 0) {
		/* find maximal and minimal sizes  */
		for (i = 0; i < count_of_sizes; i++) {
			if (max_size < regs_sizes_ptr[i] &&
			    regs_sizes_ptr[i] != 0xFFFFFFFF)
				max_size = regs_sizes_ptr[i];

			if (min_size > regs_sizes_ptr[i])
				min_size = regs_sizes_ptr[i];
		}

		/* set sizes into PKA registers sizes table */
		for (i = 0; i < count_of_sizes; i++)
			crypto_write(regs_sizes_ptr[i], CRYPTO_PKA_L0 + 4 * i);
	} else {
		/* 2. Case of default settings */
		maxsize_words = (max_size_bits + 31) / 32;
		/* write exact size into first table entry */
		crypto_write(max_size_bits, CRYPTO_PKA_L0);

		/* write size with extra word into tab[1] = tab[0] + 32 */
		crypto_write(32 * maxsize_words + 32, CRYPTO_PKA_L0 + 4);

		/* count of entries, which was set */
		count_of_sizes = 2;
	}

	for (i = count_of_sizes; i < 8; i++)
		crypto_write(0xFFFFFFFF, CRYPTO_PKA_L0 + 4 * i);

	return error;
}

u32 rk_pka_set_map_tab(struct rk_pka_regs_map *regs_map_ptr,
		       u32 *count_of_regs, u32 maxsize_words,
		       u32 N_NP_T0_T1, u32 is_default_map)
{
	u32 i;
	u32 error;
	u32 cur_addr;
	u32 default_max_size, default_count_of_regs;

	error = CRYPT_OK;
	cur_addr = 0;

	if (is_default_map == 1) {
		default_max_size = 32 * maxsize_words;
		default_count_of_regs =
			min(32, (8 * RK_PKA_MAX_REGS_MEM_SIZE_BYTES) /
				default_max_size);

		for (i = 0; i < 32 - 2; i++) {
			if (i < default_count_of_regs - 2) {
				crypto_write(cur_addr,
					     CRYPTO_MEMORY_MAP0 + 4 * i);
				cur_addr = cur_addr + default_max_size / 8;
			} else {
				crypto_write(0xFFC, CRYPTO_MEMORY_MAP0 + 4 * i);
			}
		}
		crypto_write(cur_addr, CRYPTO_MEMORY_MAP0 + 4 * 30);
		cur_addr = cur_addr + default_max_size / 8;
		crypto_write(cur_addr, CRYPTO_MEMORY_MAP0 + 4 * 31);
		*count_of_regs = default_count_of_regs;
		crypto_write((u32)RK_PKA_N_NP_T0_T1_REG_DEFAULT_VAL,
			     CRYPTO_N_NP_T0_T1_ADDR);
	}

	if (is_default_map == 0) {
		for (i = 0; i < *count_of_regs; i++)
			crypto_write(regs_map_ptr->regs_addr[i],
				     CRYPTO_MEMORY_MAP0 +
				     4 * regs_map_ptr->reges_num[i]);

		crypto_write(N_NP_T0_T1, CRYPTO_N_NP_T0_T1_ADDR);
	}

	return error;
}

u32 rk_pka_clear_block_of_regs(u8 first_reg, u8 count_of_regs,
			       u8 len_id)
{
	u32 i;
	u32 size, addr;
	s32 count_temps;

	rk_pka_read_regsize(&size, len_id);

	count_temps = 0;

	if (first_reg + count_of_regs > 30) {
		count_temps = min((count_of_regs + first_reg - 30), 2);
		count_of_regs = 30;
	} else {
		count_temps = 2;
	}

	/* clear ordinary registers */
	for (i = 0; i < count_of_regs; i++)
		RK_PKA_Clr(len_id, first_reg + i/*regNum*/, 0/*tag*/);

	/* clear PKA temp registers using macros (without PKA operations */
	if (count_temps > 0) {
		/* calculate size of register in words */
		size = (size + 31) / 32;
		rk_pka_wait_on_done();
		rk_pka_get_regaddr(30/*vir_reg*/, &addr/*phys_addr*/);
		rk_pka_hw_clear_pka_mem(addr, size);

		if (count_temps > 1) {
			rk_pka_get_regaddr(31/*vir_reg*/, &addr/*phys_addr*/);
			rk_pka_hw_clear_pka_mem(addr, size);
		}
	}
	return CRYPT_OK;
}

u32 rk_pka_init(u32 regs_sizes_ptr[RK_PKA_MAX_REGS_COUNT], u32 count_of_sizes,
		struct rk_pka_regs_map *regs_map_ptr, u32 count_of_regs,
		u32 op_size_bits, u32 regsize_words,
		u32 N_NP_T0_T1, u32 is_default_map)
{
	u32 addr;
	u32 error;

	error = CRYPT_OK;

	PKA_CLK_ENABLE();
	rk_pka_ram_ctrl_enable();

	error = rk_pka_set_sizes_tab(regs_sizes_ptr, count_of_sizes,
				     op_size_bits, is_default_map);

	if (error != CRYPT_OK)
		return error;

	error = rk_pka_set_map_tab(regs_map_ptr, &count_of_regs, regsize_words,
				   N_NP_T0_T1, is_default_map);

	if (error != CRYPT_OK)
		return error;

	/* set size of register into RegsSizesTable */
	crypto_write(32 * regsize_words, CRYPTO_PKA_L0 + 3 * 4);

	/* clean PKA data memory */
	rk_pka_clear_block_of_regs(0, count_of_regs - 2, 3);

	/* clean temp PKA registers 30,31 */
	rk_pka_wait_on_done();
	rk_pka_get_regaddr(30/*vir_reg*/, &addr/*phys_addr*/);
	rk_pka_hw_clear_pka_mem(addr, regsize_words);
	rk_pka_get_regaddr(31/*vir_reg*/, &addr/*phys_addr*/);
	rk_pka_hw_clear_pka_mem(addr, regsize_words);

	return error;
}

void rk_pka_finish(void)
{
	RK_PKA_Terminate(0);
	PKA_CLK_DISABLE();
}

void rk_pka_copy_data_into_reg(s8 dst_reg, u8 len_id,
			       u32 *src_ptr, u32 size_words)
{
	u32 cur_addr;
	u32 reg_size;

	RK_PKA_Terminate(0);

	rk_pka_read_regaddr(dst_reg, &cur_addr);

	rk_pka_read_regsize(&reg_size, len_id);
	reg_size = (reg_size + 31) / 32;

	rk_pka_hw_load_block2pka_mem(cur_addr, src_ptr, size_words);
	cur_addr = cur_addr + sizeof(u32) * size_words;

	rk_pka_hw_clear_pka_mem(cur_addr, reg_size - size_words);
}

void rk_pka_copy_data_from_reg(u32 *dst_ptr, u32 size_words,
			       s8 src_reg)
{
	u32 cur_addr;

	crypto_write(0, CRYPTO_OPCODE);

	rk_pka_wait_on_done();

	rk_pka_read_regaddr(src_reg, &cur_addr);

	rk_pka_hw_read_block_from_pka_mem(cur_addr, dst_ptr, size_words);
}

u32 rk_pka_calcNp_and_initmodop(u32 len_id, u32 mod_size_bits,
				s8 r_t0, s8 r_t1, s8 r_t2)
{
	u32 i;
	u32 s;
	u32 error;
	u32 num_bits, num_words;

	/* Set s = 132 */
	s = 132;

	/*-------------------------------------------------------------------*/
	/* Step 1,2. Set registers: Set op_a = 2^(sizeN+32)                  */
	/*           Registers using: 0 - N (is set in register 0,           */
	/*           1 - NP, temp regs: r_t0 (A), r_t1, r_t2.                */
	/*           len_id: 0 - exact size, 1 - exact+32 bit                */
	/*-------------------------------------------------------------------*/

	/* set register r_t0 = 0 */
	RK_PKA_Clr(len_id + 1, r_t0/*op_a*/, 0/*tag*/); /* r2 = 0 */

	/* calculate bit position of said bit in the word */
	num_bits = mod_size_bits % 32;
	num_words = mod_size_bits / 32;

	/* set 1 into register r_t0 */
	RK_PKA_Set0(len_id + 1, r_t0/*op_a*/, r_t0/*res*/, 0/*tag*/);

	/* shift 1 to num_bits+31 position */
	if (num_bits > 0)
		RK_PKA_SHL0(len_id + 1, r_t0/*op_a*/, num_bits - 1/*s*/,
			    r_t0/*res*/, 0/*tag*/);

	/* shift to word position */
	for (i = 0; i < num_words; i++)
		RK_PKA_SHL0(len_id + 1, r_t0/*op_a*/, 31/*s*/,
			    r_t0/*res*/, 0/*tag*/);

	/*-------------------------------------------------------------------*/
	/* Step 3.  Dividing:  (op_a * 2**s) / N                             */
	/*-------------------------------------------------------------------*/
	error = rk_pka_div_long_num(len_id,        /*len_id*/
				    r_t0,          /*op_a*/
				    s,            /*shift*/
				    0,            /*op_b = N*/
				    1,            /*res NP*/
				    r_t1,          /*temp reg*/
				    r_t2           /*temp reg*/);

	return error;

}  /* END OF LLF_PKI_PKA_ExecCalcNpAndInitModOp */

/***********   LLF_PKI_PKA_DivLongNum function      **********************/
/**
 * @brief The function divides long number A*(2^S) by B:
 *            res =  A*(2^S) / B,  remainder A = A*(2^S) % B.
 *        where: A,B - are numbers of size, which is not grate than,
 *		 maximal operands size,
 *		 and B > 2^S;
 *               S  - exponent of binary factor of A.
 *               ^  - exponentiation operator.
 *
 *        The function algorithm:
 *
 *        1. Let nWords = S/32; nBits = S % 32;
 *        2. Set res = 0, r_t1 = op_a;
 *        3. for(i=0; i<=nWords; i++) do:
 *            3.1. if(i < nWords )
 *                   s1 = 32;
 *                 else
 *                   s1 = nBits;
 *            3.2. r_t1 = r_t1 << s1;
 *            3.3. call PKA_div for calculating the quotient and remainder:
 *                      r_t2 = floor(r_t1/op_b) //quotient;
 *                      r_t1 = r_t1 % op_b   //remainder (is in r_t1 register);
 *            3.4. res = (res << s1) + r_t2;
 *           end do;
 *        4. Exit.
 *
 *        Assuming:
 *                  - 5 PKA registers are used: op_a, op_b, res, r_t1, r_t2.
 *                  - The registers sizes and mapping tables are set on
 *                    default mode according to operands size.
 *                  - The PKA clocks are initialized.
 *        NOTE !   Operand op_a shall be overwritten by remainder.
 *
 * @param[in] len_id    - ID of operation size (modSize+32).
 * @param[in] op_a      - Operand A: virtual register pointer of A.
 * @param[in] S        - exponent of binary factor of A.
 * @param[in] op_b      - Operand B: virtual register pointer of B.
 * @param[in] res      - Virtual register pointer for result quotient.
 * @param[in] r_t1      - Virtual pointer to remainder.
 * @param[in] r_t2      - Virtual pointer of temp register.
 * @param[in] VirtualHwBaseAddr -  Virtual HW base address, passed by user.
 *
 * @return CRYSError_t - On success CRYPT_OK is returned:
 *
 */
u32 rk_pka_div_long_num(u8 len_id, s8 op_a, u32 s,
			s8 op_b, s8 res, s8 r_t1, s8 r_t2)
{
	s8 s1;
	u32  i;
	u32  n_bits, n_words;

	/* calculate shifting parameters (words and bits ) */
	n_words = ((u32)s + 31) / 32;
	n_bits = (u32)s % 32;

	/* copy operand op_a (including extra word) into temp reg r_t1 */
	RK_PKA_Copy(len_id + 1, r_t1/*dst*/, op_a/*src*/, 0 /*tag*/);

	/* set res = 0 (including extra word) */
	RK_PKA_Clear(len_id + 1, res/*dst*/, 0 /*tag*/);

	/* set s1 = 0 for first dividing in loop */
	s1 = 0;

	/*----------------------------------------------------*/
	/* Step 1.  Shifting and dividing loop                */
	/*----------------------------------------------------*/
	for (i = 0; i < n_words; i++) {
		/* 3.1 set shift value s1  */
		if (i > 0)
			s1 = 32;
		else
			s1 = n_bits;

		/* 3.2. shift: r_t1 = r_t1 * 2**s1 (in code (s1-1),
		 * because PKA performs s+1 shifts)
		 */
		if (s1 > 0)
			RK_PKA_SHL0(len_id + 1, r_t1/*op_a*/, (s1 - 1)/*s*/,
				    r_t1/*res*/, 0/*tag*/);

		/* 3.3. perform PKA_Div for calculating a quotient
		 * r_t2 = floor(r_t1 / N)
		and remainder r_t1 = r_t1 % op_b
		 */
		RK_PKA_Div(len_id + 1, r_t1/*op_a*/, op_b/*B*/, r_t2/*res*/,
			   0/*tag*/);

		/* 3.4. res = res * 2**s1 + res;   */
		if (s1 > 0)
			RK_PKA_SHL0(len_id + 1, res /*op_a*/, (s1 - 1)/*s*/,
				    res /*res*/, 0 /*tag*/);

		RK_PKA_Add(len_id + 1, res/*op_a*/, r_t2/*op_b*/, res/*res*/,
			   0/*tag*/);
	}

	rk_pka_wait_on_done();
	return CRYPT_OK;
}  /* END OF LLF_PKI_PKA_DivLongNum */

/******LLF_PKI_CalcNpAndInitModOp function (physical pointers)***************/
/**
 * @brief The function initializes  modulus and Barret tag NP,
 *	      used in modular PKA operations.
 *
 *        The function does the following:
 *          - calculates mod size in bits and sets it into PKA table sizes;
 *          - if parameter NpCreateFlag = PKA_CreateNP, then the function
 *            writes the modulus and the tag into registers
 *            r0 and r1 accordingly;
 *          - if NpCreateFlag= PKA_SetNP, the function calls the
 *            LLF_PKI_PKA_ExecCalcNpAndInitModOp, which calculates the Barret
 *            tag NP and initializes PKA registers; then the function outputs
 *            calcu1lated NP value.
 *
 *       Assumings: - The registers mapping table is set on default mode,
 *            according to modulus size:
 *         -- count of allowed registers is not less, than 7 (including 3
 *            registers r_t0,r_t2,rT3 for internal calculations and 4 default
 *            special registers N,NP,T0,T1);
 *         -- modulus exact and exact+32 bit sizes should be set into first
 *            two entries of sizes-table accordingly.
 *
 * @param[in]  N_ptr        - The pointer to the buffer, containing modulus N,
 * @param[in]  N_sizeBits   - The size of modulus in bytes, must be
 *				16 <= N_sizeBytes <= 264.
 * @param[out] NP_ptr       - The pointer to the buffer, containing
 *				result - modulus tag NP.
 * @param[in]  NpCreateFlag - Parameter, defining whether the NP shall be
 *				taken from NP buffer and set into
 *                            PKA register NP ( NpCreateFlag= PKA_CreateNP= 1 )
 *                            or it shall be calculated and send to
 *                            NP buffer ( NpCreateFlag= PKA_SetNP= 0 ).
 * @param[in]  r_t0,r_t1,r_t2  - Virtual pointers to temp registers
 *						  (sequence numbers).
 * @param[in]  VirtualHwBaseAddr -  Virtual HW base address, passed by user.
 *
 * @return CRYSError_t - On success CRYPT_OK is returned,
 *				on failure an error code:
 *				LLF_PKI_PKA_ILLEGAL_PTR_ERROR
 *				LLF_PKI_PKA_ILLEGAL_OPERAND_LEN_ERROR
 *
 */
u32 rk_calcNp_and_initmodop(u32 *N_ptr, u32 N_size_bits,
			    u32 *NP_ptr, u8 np_create_flag,
			    s8 r_t0, s8 r_t1, s8 r_t2)
{
	u32 N_size_words;
	u32 error = CRYPT_OK;

	/* calculate size of modulus in bytes and in words */
	N_size_words = (N_size_bits + 31) / 32;

	/* copy modulus N into r0 register */
	rk_pka_copy_data_into_reg(0/*dst_reg*/, 1/*len_id*/, N_ptr/*src_ptr*/,
				  N_size_words);

	/* if np_create_flag == PKA_SetNP, then set NP into PKA register r1 */
	if (np_create_flag == RK_PKA_SET_NP) {
		/* copy the NP into r1 register NP */
		rk_pka_copy_data_into_reg(1/*dst_reg*/, 1/*len_id*/,
					  NP_ptr/*src_ptr*/,
					  RK_PKA_BARRETT_IN_WORDS);
	} else {
		/*---------------------------------------------------------*/
		/*     execute calculation of NP and initialization of PKA */
		/*---------------------------------------------------------*/

		rk_pka_calcNp_and_initmodop(0/*len_id*/, N_size_bits,
					    r_t0, r_t1, r_t2);

		/* output of NP value */
		rk_pka_copy_data_from_reg(NP_ptr/*dst_ptr*/,
					  RK_PKA_BARRETT_IN_WORDS,
					  1/*srcReg*/);
	}
	/* End of the function */
	return error;
} /* END OF LLF_PKI_CalcNpAndInitModOp */

#define RK_NEG_SIGN -1
#define RK_POS_SIGN  1

#define RK_WORD_SIZE                  32

#define rk_mpanum_is_zero(x) ((x)->size == 0)
#define rk_mpanum_neg(x) ((x)->size = -((x)->size))
#define rk_mpanum_size(x) ((int)((x)->size >= 0 ? \
				 (x)->size : -(x)->size))
#define rk_mpanum_sign(x) ((x)->size >= 0 ? RK_POS_SIGN : RK_NEG_SIGN)
#define rk_mpanum_msw(x) ((x)->d[rk_mpanum_size(x) - 1])

/*  --------------------------------------------------------------------
 *  Function:  mpa_highest_bit_index
 *  Returns the index of the highest 1 in |src|.
 *  The index starts at 0 for the least significant bit.
 *  If src == zero, it will return -1
 *
 */
static int mpa_highest_bit_index(const struct mpa_num *src)
{
	u32 w;
	u32 b;

	if (rk_mpanum_is_zero(src))
		return -1;

	w = rk_mpanum_msw(src);

	for (b = 0; b < RK_WORD_SIZE; b++) {
		w >>= 1;
		if (w == 0)
			break;
	}
	return (int)(rk_mpanum_size(src) - 1) * RK_WORD_SIZE + b;
}

/*get bignum data length*/
static int rk_check_size(u32 *data, u32 max_word_size)
{
	for (int i = (max_word_size - 1); i >= 0; i--) {
		if (data[i] == 0)
			continue;
		else
			return (i + 1);
	}
	return 0;
}

int rk_mpa_alloc(struct mpa_num **mpa, void *data, u32 word_size)
{
	u32 alignment = sizeof(u32);
	u32 byte_size = word_size * sizeof(u32);
	struct mpa_num *tmp_mpa = NULL;

	if (!mpa || word_size == 0)
		return -EINVAL;

	*mpa = NULL;

	tmp_mpa = malloc(sizeof(*tmp_mpa));
	if (!tmp_mpa)
		return -ENOMEM;

	memset(tmp_mpa, 0x00, sizeof(*tmp_mpa));

	if (!data || (unsigned long)data % alignment) {
		tmp_mpa->d = memalign(alignment, byte_size);
		if (!tmp_mpa->d) {
			free(tmp_mpa);
			return -ENOMEM;
		}

		if (data)
			memcpy(tmp_mpa->d, data, byte_size);
		else
			memset(tmp_mpa->d, 0x00, byte_size);

		tmp_mpa->alloc = MPA_USE_ALLOC;
	} else {
		tmp_mpa->d = data;
	}

	tmp_mpa->size  = word_size;

	*mpa = tmp_mpa;

	return 0;
}

void rk_mpa_free(struct mpa_num **mpa)
{
	struct mpa_num *tmp_mpa = NULL;

	if (mpa && (*mpa)) {
		tmp_mpa = *mpa;
		if (tmp_mpa->alloc == MPA_USE_ALLOC)
			free(tmp_mpa->d);

		free(tmp_mpa);
	}
}

/* c = |a| + |b| */
int rk_abs_add(void *a, void *b, void *c)
{
	int max_word_size;
	u32 error = CRYPT_OK;
	struct mpa_num *m_a, *m_b, *m_c;

	m_a = (struct mpa_num *)a;
	m_b = (struct mpa_num *)b;
	m_c = (struct mpa_num *)c;

	max_word_size = rk_mpanum_size(m_a);
	if (max_word_size < rk_mpanum_size(m_b))
		max_word_size = rk_mpanum_size(m_b);

	error = RK_PKA_DefaultInitPKA(max_word_size * 32, max_word_size + 1);
	if (error != CRYPT_OK)
		goto exit;

	rk_pka_copy_data_into_reg(2/*dst_reg*/, 1/*len_id*/, m_a->d,
				  rk_mpanum_size(m_a));
	rk_pka_copy_data_into_reg(3/*dst_reg*/, 1/*len_id*/, m_b->d,
				  rk_mpanum_size(m_b));
	RK_PKA_Add(1/*len_id*/, 2/*op_a*/, 3/*op_b*/, 4/*res*/, 0/*tag*/);
	rk_pka_copy_data_from_reg(m_c->d, max_word_size + 1,
				  4/*srcReg*/);

	m_c->size = rk_check_size(m_c->d,  max_word_size + 1);

	rk_pka_clear_block_of_regs(0/*FirstReg*/, 5/*Count*/, 1/*len_id*/);
	rk_pka_clear_block_of_regs(30/*FirstReg*/, 2/*Count*/, 1/*len_id*/);
	rk_pka_finish();

exit:
	return error;
}

/*c = a % b*/
int rk_mod(void *a, void *b, void *c)
{
	int max_word_size;
	u32 error = CRYPT_OK;
	struct mpa_num *m_a, *m_b, *m_c;

	m_a = (struct mpa_num *)a;
	m_b = (struct mpa_num *)b;
	m_c = (struct mpa_num *)c;

	if (!a || !b || !c || rk_mpanum_size(m_b) == 0) {
		error = CRYPT_ERROR;
		goto exit;
	}

	max_word_size = rk_mpanum_size(m_a);
	if (max_word_size < rk_mpanum_size(m_b))
		max_word_size = rk_mpanum_size(m_b);

	error = RK_PKA_DefaultInitPKA(max_word_size * 32, max_word_size + 1);
	if (error != CRYPT_OK)
		goto exit;

	rk_pka_copy_data_into_reg(2/*dst_reg*/, 1/*len_id*/,
				  m_a->d/*src_ptr*/,
				  rk_mpanum_size(m_a));
	rk_pka_copy_data_into_reg(3/*dst_reg*/, 1/*len_id*/,
				  m_b->d/*src_ptr*/,
				  rk_mpanum_size(m_b));
	RK_PKA_Div(0/*len_id*/, 2/*op_a*/, 3/*op_b*/, 4/*res*/, 0/*tag*/);
	rk_pka_copy_data_from_reg(m_c->d,  max_word_size, 2/*srcReg*/);
	m_c->size = rk_check_size(m_c->d, max_word_size);

	rk_pka_clear_block_of_regs(0/*FirstReg*/, 5/*Count*/, 1/*len_id*/);
	rk_pka_clear_block_of_regs(30/*FirstReg*/, 2/*Count*/, 1/*len_id*/);
	rk_pka_finish();

exit:
	return error;
}

/*d = (a ^ b) % c*/
int rk_exptmod(void *a, void *b, void *c, void *d)
{
	struct mpa_num *tmpa;
	u32 op_Np[5];
	u32 error = CRYPT_OK;
	int max_word_size, exact_size;
	struct mpa_num *m_b, *m_c, *m_d;

	m_b = (struct mpa_num *)b;
	m_c = (struct mpa_num *)c;
	m_d = (struct mpa_num *)d;

	if (rk_mpa_alloc(&tmpa, NULL, RK_MAX_RSA_BWORDS) != 0)
		return CRYPT_ERROR;

	error = rk_mod(a, c, tmpa);
	if (error) {
		error = CRYPT_ERROR;
		goto exit;
	}

	if (!a || !b || !c || !d || rk_mpanum_size(m_c) == 0) {
		error = CRYPT_ERROR;
		goto exit;
	}

	max_word_size = rk_mpanum_size(tmpa);
	if (max_word_size < rk_mpanum_size(m_b))
		max_word_size = rk_mpanum_size(m_b);
	if (max_word_size < rk_mpanum_size(m_c))
		max_word_size = rk_mpanum_size(m_c);

	error = RK_PKA_DefaultInitPKA(max_word_size * 32, max_word_size + 1);
	if (error != CRYPT_OK)
		goto exit;

	/* write exact size into first table entry */
	exact_size = mpa_highest_bit_index(m_c) + 1;
	crypto_write(exact_size, CRYPTO_PKA_L0);

	/* write size with extra word into tab[1] = tab[0] + 32 */
	crypto_write(exact_size + 32, CRYPTO_PKA_L0 + 4);

	/* calculate NP by initialization PKA for modular operations */
	error = rk_calcNp_and_initmodop(
					(m_c)->d, /*in N*/
					exact_size, /*in N size*/
					op_Np, /*out NP*/
					RK_PKA_CREATE_NP, /*in caculate NP*/
					2, /*in *r_t0*/
					3, /*in r_t1*/
					4 /*in r_t2*/);
	if (error != CRYPT_OK) {
		printf("rk_calcNp_and_initmodop fail");
		goto exit;
	}
	rk_pka_clear_block_of_regs(2/* FirstReg*/, 3, 1/*len_id*/);

	rk_pka_copy_data_into_reg(2/*dst_reg*/, 1/*len_id*/,
				  tmpa->d/*src_ptr*/,
				  rk_mpanum_size(tmpa));
	rk_pka_copy_data_into_reg(3/*dst_reg*/, 1/*len_id*/,
				  (m_b)->d/*src_ptr*/,
				  rk_mpanum_size(m_b));
	rk_pka_copy_data_into_reg(0/*dst_reg*/, 1/*len_id*/,
				  m_c->d/*src_ptr*/,
				  rk_mpanum_size(m_c));
	RK_PKA_ModExp(0, 2, 3, 4, 0);
	rk_pka_copy_data_from_reg(m_d->d,  max_word_size, 4/*srcReg*/);

	m_d->size = rk_check_size(m_d->d, max_word_size);

	rk_pka_clear_block_of_regs(0/*FirstReg*/, 5/*Count*/, 1/*len_id*/);
	rk_pka_clear_block_of_regs(30/*FirstReg*/, 2/*Count*/, 1/*len_id*/);
	rk_pka_finish();

exit:
	rk_mpa_free(&tmpa);
	return error;
}

/*d = (a ^ b) % c*/
int rk_exptmod_np(void *m, void *e, void *n, void *np, void *d)
{
	struct mpa_num *tmpa;
	u32 op_Np[5];
	u32 error = CRYPT_OK;
	int max_word_size, exact_size;
	struct mpa_num *m_e, *m_n, *m_np, *m_d;

	m_e = (struct mpa_num *)e;
	m_n = (struct mpa_num *)n;
	m_np = (struct mpa_num *)np;
	m_d = (struct mpa_num *)d;

	if (rk_mpa_alloc(&tmpa, NULL, RK_MAX_RSA_BWORDS) != 0)
		return CRYPT_ERROR;

	error = rk_mod(m, n, tmpa);
	if (error) {
		error = CRYPT_ERROR;
		goto exit;
	}

	if (!m || !e || !n || !d || rk_mpanum_size(m_n) == 0) {
		error = CRYPT_ERROR;
		goto exit;
	}

	max_word_size = rk_mpanum_size(tmpa);
	if (max_word_size < rk_mpanum_size(m_e))
		max_word_size = rk_mpanum_size(m_e);
	if (max_word_size < rk_mpanum_size(m_n))
		max_word_size = rk_mpanum_size(m_n);

	error = RK_PKA_DefaultInitPKA(max_word_size * 32, max_word_size + 1);
	if (error != CRYPT_OK)
		goto exit;

	/* write exact size into first table entry */
	exact_size = mpa_highest_bit_index(m_n) + 1;
	crypto_write(exact_size, CRYPTO_PKA_L0);

	/* write size with extra word into tab[1] = tab[0] + 32 */
	crypto_write(exact_size + 32, CRYPTO_PKA_L0 + 4);

	/* calculate NP by initialization PKA for modular operations */
	if (m_np && m_np->d)
		error = rk_calcNp_and_initmodop((m_n)->d, /*in N*/
						exact_size,	/*in N size*/
						m_np->d,	/*out NP*/
						RK_PKA_SET_NP, /*in set NP*/
						2,	/*in *r_t0*/
						3,	/*in r_t1*/
						4	/*in r_t2*/);
	else
		error = rk_calcNp_and_initmodop((m_n)->d,/*in N*/
						exact_size,	/*in N size*/
						op_Np,	/*out NP*/
						RK_PKA_CREATE_NP,
						2,	/*in *r_t0*/
						3,	/*in r_t1*/
						4	/*in r_t2*/);
	if (error != CRYPT_OK) {
		printf("rk_calcNp_and_initmodop fail");
		goto exit;
	}
	rk_pka_clear_block_of_regs(2/* FirstReg*/, 3, 1/*len_id*/);

	rk_pka_copy_data_into_reg(2/*dst_reg*/, 1/*len_id*/,
				  (tmpa)->d/*src_ptr*/,
				  rk_mpanum_size(tmpa));
	rk_pka_copy_data_into_reg(3/*dst_reg*/, 1/*len_id*/,
				  m_e->d/*src_ptr*/,
				  rk_mpanum_size(m_e));
	rk_pka_copy_data_into_reg(0/*dst_reg*/, 1/*len_id*/,
				  (m_n)->d/*src_ptr*/,
				  rk_mpanum_size(m_n));
	RK_PKA_ModExp(0, 2, 3, 4, 0);
	rk_pka_copy_data_from_reg(m_d->d, max_word_size, 4/*srcReg*/);

	m_d->size = rk_check_size(m_d->d, max_word_size);

	rk_pka_clear_block_of_regs(0/*FirstReg*/, 5/*Count*/, 1/*len_id*/);
	rk_pka_clear_block_of_regs(30/*FirstReg*/, 2/*Count*/, 1/*len_id*/);
	rk_pka_finish();

exit:
	rk_mpa_free(&tmpa);
	return error;
}
