// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (c) 2019 Fuzhou Rockchip Electronics Co., Ltd
 */

#ifndef _ROCKCHIP_CRYPTO_V2_PKA_H_
#define _ROCKCHIP_CRYPTO_V2_PKA_H_
#include <common.h>
#include <rockchip/crypto_v2.h>
#include <rockchip/crypto_v2_util.h>

#define CRYPTO_BASE crypto_base

#define MPA_USE_ALLOC	1

struct mpa_num {
	u32 alloc;
	s32 size;
	u32 *d;
};

#define RK_MAX_RSA_NBITS	4096
#define RK_MAX_RSA_NCHARS	((RK_MAX_RSA_NBITS) / 8)
#define RK_MAX_RSA_BWORDS	((RK_MAX_RSA_NBITS) / 32)

/* define NpCreateFlag values */
#define RK_PKA_CREATE_NP		1
#define RK_PKA_SET_NP		0
/* size of buffer for Barrett modulus tag NP, used in PKI algorithms */
#define RK_PKA_BARRETT_IN_WORDS	5
/* Barrett modulus tag type - 5 words size array */
typedef u32 RK_PKA_NP_t[RK_PKA_BARRETT_IN_WORDS];

#define RK_PKA_MemSetZero(buf, size) \
			util_word_memset((void *)buf, 0x00, size)

#define RK_PKA_FastMemCpy(dst, src, size) \
			util_word_memcpy((void *)dst, (void *)src, size)

#define RK_PKA_ReverseMemcpy(dst, src, size) \
			util_reverse_word_memcpy((void *)dst, (void *)src, size)

#define RES_DISCARD 0x3F

/* base address -  0x00F10B00 */
#define RK_PKI_ERROR_BASE			0x00F10B00
#define RK_PKI_HW_VER_INCORRECT_ERROR		(RK_PKI_ERROR_BASE + 0x0UL)
#define RK_PKI_HW_DECRYPED_ERROR		(RK_PKI_ERROR_BASE + 0x1UL)
#define RK_PKI_KEY_SIZE_ERROR			(RK_PKI_ERROR_BASE + 0x2UL)

/* Error definitions for PKA using */
#define RK_PKA_ILLEGAL_PTR_ERROR		(RK_PKI_ERROR_BASE + 0x20UL)
#define RK_PKA_ENTRIES_COUNT_ERROR		(RK_PKI_ERROR_BASE + 0x21UL)
#define RK_PKA_REGISTER_SIZES_ERROR		(RK_PKI_ERROR_BASE + 0x22UL)
#define RK_PKA_SET_MAP_MODE_ERROR		(RK_PKI_ERROR_BASE + 0x23UL)

#define RK_PKA_DIVIDER_IS_NULL_ERROR		(RK_PKI_ERROR_BASE + 0x2EUL)
#define RK_PKA_MODULUS_IS_NULL_ERROR		(RK_PKI_ERROR_BASE + 0x2FUL)
#define RK_PKA_DATA_SIZE_ERROR			(RK_PKI_ERROR_BASE + 0x30UL)
#define RK_PKA_OPERATION_SIZE_ERROR		(RK_PKI_ERROR_BASE + 0x31UL)

#define RK_PKA_MAX_REGS_COUNT			8
#define RK_PKA_MAX_PHYS_MEM_REGS_COUNT		32
#define RK_PKA_MAX_REGS_MEM_SIZE_BYTES		4096

/* PKA control values  */
#define RK_PKA_PIPE_READY			1
#define RK_PKA_OP_DONE				1
#define RK_PKA_SW_REST				1

/* PKA N_NP_T0_T1 register fields positions (low bit position) */
#define RK_PKA_N_NP_T0_T1_REG_N_POS		CRYPTO_N_VIRTUAL_ADDR_SHIFT
#define RK_PKA_N_NP_T0_T1_REG_NP_POS		CRYPTO_NP_VIRTUAL_ADDR_SHIFT
#define RK_PKA_N_NP_T0_T1_REG_T0_POS		CRYPTO_T0_VIRTUAL_ADDR_SHIFT
#define RK_PKA_N_NP_T0_T1_REG_T1_POS		CRYPTO_T1_VIRTUAL_ADDR_SHIFT

/* PKA N_NP_T0_T1 register default (reset) value: N=0, NP=1, T0=30, T1=31 */
#define PKA_N					0UL
#define PKA_NP					1UL
#define PKA_T0					30UL
#define PKA_T1					31UL
#define RK_PKA_N_NP_T0_T1_REG_DEFAULT_VAL \
				(PKA_N  << RK_PKA_N_NP_T0_T1_REG_N_POS | \
				PKA_NP << RK_PKA_N_NP_T0_T1_REG_NP_POS | \
				PKA_T0 << RK_PKA_N_NP_T0_T1_REG_T0_POS | \
				PKA_T1 << RK_PKA_N_NP_T0_T1_REG_T1_POS)

/* PKA STATUS register fields positions (low bit position) */
#define RK_PKA_STATUS_PIPE_IS_REDY_POS		0
#define RK_PKA_STATUS_PKA_BUSY_POS		1
#define RK_PKA_STATUS_ALU_OUT_ZERO_POS		2
#define RK_PKA_STATUS_ALU_MODOVRFLW_POS		3
#define RK_PKA_STATUS_DIV_BY_ZERO_POS		4
#define RK_PKA_STATUS_ALU_CARRY_POS		5
#define RK_PKA_STATUS_ALU_SIGN_OUT_POS		6
#define RK_PKA_STATUS_MODINV_OF_ZERO_POS	7
#define RK_PKA_STATUS_PKA_CPU_BUSY_POS		8
#define RK_PKA_STATUS_OPCODE_POS		9
#define RK_PKA_STATUS_TAG_POS			14

#define RK_PKA_STATUS_OPCODE_MASK		0x1FUl
#define RK_PKA_STATUS_TAG_MASK			0x3FUl

/* PKA OPCODE register fields positions (low bit position) */
#define RK_PKA_OPCODE_TAG_POS			0
#define RK_PKA_OPCODE_RESULT_POS		6
#define RK_PKA_OPCODE_R_DISCARD_POS		11
#define RK_PKA_OPCODE_OPERAND_2_POS		12
#define RK_PKA_OPCODE_OPERAND_2_IMMED_POS	17
#define RK_PKA_OPCODE_OPERAND_1_POS		18
#define RK_PKA_OPCODE_OPERAND_1_IMMED_POS	23
#define RK_PKA_OPCODE_LEN_POS			24
#define RK_PKA_OPCODE_OPERATION_ID_POS		27

/* PKA data registers base address
 *should be always zero since it's the offset
 * from the start of the PKA memory and not from the HOST memory
 */
#define RK_PKA_DATA_REGS_BASE_ADDR		(CRYPTO_BASE + CRYPTO_SRAM_BASE)
#define RK_PKA_DATA_REGS_MEMORY_OFFSET_ADDR	(CRYPTO_BASE + CRYPTO_SRAM_BASE)

/* Machine Opcodes definitions (according to HW CRS ) */
#define   RK_PKA_MIN_OPCODE			0x00

#define PKA_Add					0x04
#define PKA_AddIm				0x04
#define PKA_Sub					0x05
#define PKA_SubIm				0x05
#define PKA_Neg					0x05
#define PKA_ModAdd				0x06
#define PKA_ModAddIm				0x06
#define PKA_ModSub				0x07
#define PKA_ModSubIm				0x07
#define PKA_ModNeg				0x07
#define PKA_AND					0x08
#define PKA_Test0				0x08
#define PKA_Clr0				0x08
#define PKA_Clr					0x08
#define PKA_OR					0x09
#define PKA_Copy				0x09
#define PKA_SetBit0				0x09
#define PKA_XOR					0x0A
#define PKA_Flip0				0x0A
#define PKA_InvertBits				0x0A
#define PKA_Compare				0x0A
#define PKA_SHR0				0x0C
#define PKA_SHR1				0x0D
#define PKA_SHL0				0x0E
#define PKA_SHL1				0x0F
#define PKA_LMul				0x10
#define PKA_ModMul				0x11
#define PKA_ModMulNR				0x12
#define PKA_ModExp				0x13
#define PKA_Div					0x14
#define PKA_ModInv				0x15
#define PKA_ModDiv				0x16
#define PKA_HMul				0x17
#define PKA_Terminate				0x00

#define RK_PKA_MAX_OPCODE			0x17

/*************************************************************/
/* Macros for waiting PKA machine ready states               */
/*************************************************************/

void rk_pka_ram_ctrl_enable(void);

void rk_pka_ram_ctrl_disable(void);

void rk_pka_wait_on_ram_ready(void);

void rk_pka_wait_on_pipe_ready(void);

void rk_pka_wait_on_done(void);

/*****************************************************
 *  Macros for controlling PKA machine and changing  *
 *  PKA sizes table and mapping table settings.      *
 *****************************************************/
#define PKA_CLK_ENABLE()

#define PKA_CLK_DISABLE()

void rk_pka_set_startmemaddr_reg(u32 start_mem_addr);

void rk_pka_set_N_NP_T0_T1_reg(u32 N, u32 NP, u32 T0, u32 T1);

void rk_pka_set_default_N_NP_T0_T1_reg(void);

void rk_pka_get_status(u32 *status);

void rk_pka_get_status_alu_outzero(u32 *status);

void rk_pka_get_status_mod_overfl(u32 *status);

void rk_pka_get_status_div_byzero(u32 *status);

void rk_pka_get_status_carry(u32 *status);

void rk_pka_get_status_alu_signout(u32 *status);

void rk_pka_get_status_modinv_ofzero(u32 *status);

void rk_pka_get_status_opcode(u32 *status);

void rk_pka_get_status_tag(u32 *status);

/******************************************************************
 * Macros for setting and reading sizes from PKA regsSizesTable   *
 ******************************************************************/
void rk_pka_set_regsize(u32 size_bits, u32 entry_num);

void rk_pka_read_regsize(u32 *size_bits, u32 entry_num);

/******************************************************************
 * Macros for setting and reading addresses of PKA data registers *
 ******************************************************************/
void rk_pka_set_regaddr(u32 vir_reg, u32 phys_addr);

void rk_pka_get_regaddr(u32 vir_reg, u32 *phys_addr);

void rk_pka_read_regaddr(u32 vir_reg, u32 *phys_addr);

/**********************************************
 *    Macros for setting Full PKI opcode      *
 **********************************************/
u32 rk_pka_make_full_opcode(u32 opcode, u32 len_id,
			    u32 is_a_immed, u32 op_a,
			    u32 is_b_immed, u32 op_b,
			    u32 res_discard, u32 res,
			    u32 tag);

/******************************************************
 * Macros for reading and loading PKA memory data     *
 ******************************************************/
void rk_pka_hw_load_value2pka_mem(u32 addr, u32 val);

void rk_pka_hw_load_block2pka_mem(u32 addr, u32 *ptr,
				  u32 size_words);

void rk_pka_hw_reverse_load_block2pka_mem(u32 addr, u32 *ptr,
					  u32 size_words);

void rk_pka_hw_clear_pka_mem(u32 addr, u32 size_words);

void rk_pka_hw_read_value_from_pka_mem(u32 addr, u32 *val);

void rk_pka_hw_read_block_from_pka_mem(u32 addr, u32 *ptr,
				       u32 size_words);

void rk_pka_hw_reverse_read_block_from_pka_mem(u32 addr, u32 *ptr,
					       u32 size_words);

u32 rk_pka_exec_operation(u32 opcode, u8 len_id,
			  u8 is_a_immed, s8 op_a,
			  u8 is_b_immed, s8 op_b,
			  u8	res_discard, s8 res, u8 tag);

/*************************************************************************
 * Macros for calling PKA operations (names according to operation issue *
 *************************************************************************/

/*--------------------------------------*/
/*	 1.  ADD - SUBTRACT operations	*/
/*--------------------------------------*/
/*	Add:   res =  op_a + op_b	*/
#define   RK_PKA_Add(len_id, op_a, op_b, res, tag)   \
			rk_pka_exec_operation(PKA_Add, (len_id), 0, (op_a),\
					      0, (op_b), 0, (res), (tag))

/*	AddIm:	res =  op_a + op_b_im	*/
#define   RK_PKA_AddIm(len_id, op_a, op_b_im, res, tag)   \
			rk_pka_exec_operation(PKA_Add, (len_id), 0, (op_a), \
					      1, (op_b_im), 0, (res), (tag))

/*	Sub:  res =  op_a - op_b	*/
#define   RK_PKA_Sub(len_id, op_a, op_b, res, tag)   \
			rk_pka_exec_operation(PKA_Sub, (len_id), 0, (op_a), \
					      0, (op_b), 0, (res), (tag))

/*	SubIm:	res =  op_a - op_b_im	*/
#define   RK_PKA_SubIm(len_id, op_a, op_b_im, res, tag)   \
			rk_pka_exec_operation(PKA_Sub, (len_id), 0, (op_a), \
					      1, (op_b_im), 0, (res), (tag))

/*	Neg:  res =  0 - op_b  */
#define   RK_PKA_Neg(len_id, op_b, res, tag)   \
			rk_pka_exec_operation(PKA_Sub, (len_id), 1, 0, \
					      0, (op_b), 0, (res), (tag))

/*	ModAdd:  res =	(op_a + op_b) mod N  */
#define   RK_PKA_ModAdd(len_id, op_a, op_b, res, tag)   \
			rk_pka_exec_operation(PKA_ModAdd, (len_id), 0, (op_a), \
					      0, (op_b), 0, (res), (tag))

/*	ModAddIm:  res =  (op_a + op_b_im) mod N  */
#define   RK_PKA_ModAddIm(len_id, op_a, op_b_im, res, tag)   \
			rk_pka_exec_operation(PKA_ModAdd, (len_id), 0, (op_a), \
					      1, (op_b_im), 0, (res), (tag))

/*	ModSub:  res =	(op_a - op_b) mod N  */
#define   RK_PKA_ModSub(len_id, op_a, op_b, res, tag)   \
			rk_pka_exec_operation(PKA_ModSub, (len_id), 0, (op_a), \
					      0, (op_b), 0, (res), (tag))

/*	ModSubIm:  res =  (op_a - op_b_im) mod N  */
#define   RK_PKA_ModSubIm(len_id, op_a, op_b_im, res, tag)   \
			rk_pka_exec_operation(PKA_ModSub, (len_id), 0, (op_a), \
					      1, (op_b_im), 0, (res), (tag))

/*	ModNeg:  res =	(0 - op_b) mod N  */
#define   RK_PKA_ModNeg(len_id, op_b, res, tag)   \
			rk_pka_exec_operation(PKA_ModSub, (len_id), 1, 0, \
					      0, (op_b), 0, (res), (tag))

/*--------------------------------------*/
/*	 2.  Logical   operations	*/
/*--------------------------------------*/

/*	AND:  res =  op_a & op_b	*/
#define   RK_PKA_AND(len_id, op_a, op_b, res, tag)   \
			rk_pka_exec_operation(PKA_AND, (len_id), 0, (op_a), \
					      0, (op_b), 0, (res), (tag))

/*	AndIm:	res =  op_a & op_b  */
#define   RK_PKA_AndIm(len_id, op_a, op_b, res, tag)   \
			rk_pka_exec_operation(PKA_AND, (len_id), 0, (op_a), \
					      1, (op_b), 0, (res), (tag))

/*	Tst0:  op_a & 0x1 - tests the bit 0 of operand A. */
/*	If bit0 = 0, then ZeroOfStatus = 1, else 0  */
#define   RK_PKA_Tst0(len_id, op_a, tag)   \
			rk_pka_exec_operation(PKA_AND, (len_id), 0, (op_a), \
					      1, 0x01, 1, RES_DISCARD, (tag))

/*	Clr0:  res =  op_a & (-2)  - clears the bit 0 of operand A. */
/*	Note:  -2 = 0x1E  for 5-bit size */
#define   RK_PKA_Clr0(len_id, op_a, res, tag)   \
			rk_pka_exec_operation(PKA_AND, (len_id), 0, (op_a), \
					      1, 0x1E, 0, (res), (tag))

/*	Clr:  res =  op_a & 0  - clears the operand A.  */
#define   RK_PKA_Clr(len_id, op_a, tag)   \
			rk_pka_exec_operation(PKA_AND, (len_id), 0, (op_a), \
					      1, 0x00, 0, (op_a), (tag))

/*	Clear:	for full clearing the actual register op_a,
 *	this macro calls Clr operation twice.
 */
#define   RK_PKA_Clear(len_id, op_a, tag)   \
		       RK_PKA_Clr(len_id, op_a, tag)

/*	OR:  res =	op_a || op_b	*/
#define   RK_PKA_OR(len_id, op_a, op_b, res, tag)   \
			rk_pka_exec_operation(PKA_OR, (len_id), 0, (op_a), \
					      0, (op_b), 0, (res), (tag))

/*	OrIm:  res =  op_a || op_b  */
#define   RK_PKA_OrIm(len_id, op_a, op_b, res, tag)   \
			rk_pka_exec_operation(PKA_OR, (len_id), 0, (op_a), \
					      1, (op_b), 0, (res), (tag))

/*	Copy:  OpDest =  OpSrc || 0  */
#define   RK_PKA_Copy(len_id, op_dest, op_src, tag)   \
			rk_pka_exec_operation(PKA_OR, (len_id), 0, (op_src), \
					      1, 0x00, 0, (op_dest), (tag))

/*	Set0:  res =  op_a || 1	: set bit0 = 1, other bits are not changed */
#define   RK_PKA_Set0(len_id, op_a, res, tag)   \
			rk_pka_exec_operation(PKA_OR, (len_id), 0, (op_a), \
					      1, 0x01, 0, (res), (tag))

/*	Xor:  res =  op_a ^ op_b	*/
#define   RK_PKA_Xor(len_id, op_a, op_b, res, tag)   \
			rk_pka_exec_operation(PKA_XOR, (len_id), 0, (op_a), \
					      0, (op_b), 0, (res), (tag))

/*	XorIm:	res =  op_a ^ op_b  */
#define   RK_PKA_XorIm(len_id, op_a, op_b, res, tag)   \
			rk_pka_exec_operation(PKA_XOR, (len_id), 0, (op_a), \
					      1, (op_b), 0, (res), (tag))

/*	Flip0:	res =  op_a || 1  - inverts the bit 0 of operand A  */
#define   RK_PKA_Flip0(len_id, op_a, res, tag)   \
			rk_pka_exec_operation(PKA_XOR, (len_id), 0, (op_a), \
					      1, 0x01, 0, (res), (tag))

/*	Invert:  res =	op_a ^ 0xFFF.FF	:  inverts all bits of op_a . */
/* Note: 0xFFFFF =  0x1F for 5 bits size of second operand */
#define   RK_PKA_Invert(len_id, op_a, res, tag)   \
			rk_pka_exec_operation(PKA_XOR, (len_id), 0, (op_a), \
					      1, 0x1F, 0, (res), (tag))

/*	Compare:  op_a ^ op_b . Rsult of compare in ZeroBitOfStatus: */
/*	If op_a == op_b then Z = 1 */
#define   RK_PKA_Compare(len_id, op_a, op_b, tag)   \
			rk_pka_exec_operation(PKA_XOR, (len_id), 0, (op_a), \
					      0, (op_b), 1, (0), (tag))

/*	CompareImmediate:  op_a ^ op_b . Rsult of compare in ZeroBitOfStatus: */
/*	If op_a == op_b then status Z = 1 */
#define   RK_PKA_CompareIm(len_id, op_a, op_b, tag)   \
			rk_pka_exec_operation(PKA_XOR, (len_id), 0, (op_a), \
					      1, (op_b), 1, (0), (tag))

/*----------------------------------------------*/
/*	 3.  SHIFT	  operations		*/
/*----------------------------------------------*/

/*	SHR0:  res =  op_a >> (S+1) :
 *	shifts right operand A by S+1 bits, insert 0 to left most bits
 */
#define   RK_PKA_SHR0(len_id, op_a, S, res, tag)   \
			rk_pka_exec_operation(PKA_SHR0, (len_id), 0, (op_a), \
					      0, (S), 0, (res), (tag))

/*	SHR1:  res =  op_a >> (S+1) :
 *	shifts right operand A by S+1 bits, insert 1 to left most bits
 */
#define   RK_PKA_SHR1(len_id, op_a, S, res, tag)   \
			rk_pka_exec_operation(PKA_SHR1, (len_id), 0, (op_a), \
					      0, (S), 0, (res), (tag))

/*	SHL0:  res =  op_a << (S+1) :
 *	shifts left operand A by S+1 bits, insert 0 to right most bits
 */
#define   RK_PKA_SHL0(len_id, op_a, S, res, tag)   \
			rk_pka_exec_operation(PKA_SHL0, (len_id), 0, (op_a), \
					      0, (S), 0, (res), (tag))

/*	SHL1:  res =  op_a << (S+1) :
 *	shifts left operand A by S+1 bits, insert 1 to right most bits
 */
#define   RK_PKA_SHL1(len_id, op_a, S, res, tag)   \
			rk_pka_exec_operation(PKA_SHL1, (len_id), 0, (op_a), \
					      0, (S), 0, (res), (tag))

/*--------------------------------------------------------------*/
/*	 2.  Multiplication and other	operations		*/
/*		 Note:	See notes to RK_PKAExecOperation	*/
/*--------------------------------------------------------------*/

/*	RMul:  res =  LowHalfOf(op_a * op_b), where size of operands and result
 *	is equaled to operation size, defined by len_id. Note: for receiving
 *	full result, the len_id must be set according to (sizeA + sizeB) and
 *	leading not significant bits of operands must be zeroed
 */
#define   RK_PKA_LMul(len_id, op_a, op_b, res, tag)   \
			rk_pka_exec_operation(PKA_LMul, (len_id), 0, (op_a), \
					      0, (op_b), 0, (res), (tag))

/*	HMul:  res =  HighHalfOf(op_a * op_b) + one high word of low half of
 *	(op_a * op_b), where size of operands is equaled to operation size,
 *	defined by len_id. Note: Size of operation result is by one word large,
 *	than operation size
 */
#define   RK_PKA_HMul(len_id, op_a, op_b, res, tag)   \
			rk_pka_exec_operation(PKA_HMul, (len_id), 0, (op_a), \
					      0, (op_b), 0, (res), (tag))

/*	ModMul:  res =	op_a * op_b  mod N - modular multiplication */
#define   RK_PKA_ModMul(len_id, op_a, op_b, res, tag)   \
			rk_pka_exec_operation(PKA_ModMul, (len_id), 0, (op_a), \
					      0, (op_b), 0, (res), (tag))

/*	ModMulN:  res =  op_a * op_b	mod N
 *	- modular multiplication (final reduction is omitted)
 */
#define   RK_PKA_ModMulN(len_id, op_a, op_b, res, tag)   \
			rk_pka_exec_operation(PKA_ModMulNR, (len_id), 0, \
					      (op_a), 0, (op_b), 0, \
					      (res), (tag))

/*	ModExp:  res =	op_a ** op_b	mod N - modular exponentiation */
#define   RK_PKA_ModExp(len_id, op_a, op_b, res, tag)   \
			rk_pka_exec_operation(PKA_ModExp, (len_id), 0, (op_a), \
					      0, (op_b), 0, (res), (tag))

/*	Divide:  res =	op_a / op_b , op_a = op_a mod op_b - division,  */
#define   RK_PKA_Div(len_id, op_a, op_b, res, tag)   \
			rk_pka_exec_operation(PKA_Div, (len_id), 0, (op_a), \
					      0, (op_b), 0, (res), (tag))

/*	ModInv:  Modular inversion: calculates	 res = 1/op_b mod N	*/
#define   RK_PKA_ModInv(len_id, op_b, res, tag)   \
			rk_pka_exec_operation(PKA_ModInv, (len_id), 0, 1, \
					      0, (op_b), 0, (res), (tag))
#define   RK_PKA_ModDiv(len_id, op_a, op_b, res, tag)   \
			rk_pka_exec_operation(PKA_ModDiv, (len_id), 0, (op_a), \
					      0, (op_b), 0, (res), (tag))

/*	Terminate  - special operation, which allows HOST access */
/*	to PKA data memory registers after end of PKA operations */
#define   RK_PKA_Terminate(tag)   \
			rk_pka_exec_operation(PKA_Terminate, 0, 0, 0, 0, \
					      0, 0, 0, (tag))

struct rk_pka_regs_map {
	u32 reges_num[RK_PKA_MAX_PHYS_MEM_REGS_COUNT];
	u32 regs_addr[RK_PKA_MAX_PHYS_MEM_REGS_COUNT];
};

u32 rk_pka_set_sizes_tab(u32 regs_sizes_ptr[RK_PKA_MAX_REGS_COUNT],
			 u32 count_of_sizes,
			 u32 max_size_bits,
			 u32 is_default_map);

#define RK_PKA_DefaultSetRegsSizesTab(max_size_bits) \
			rk_pka_set_sizes_tab(0, 0, (max_size_bits), 1)
u32 rk_pka_set_map_tab(struct rk_pka_regs_map *regs_map_ptr, u32 *count_of_regs,
		       u32 maxsize_words, u32 N_NP_T0_T1,
		       u32 is_default_map);

#define RK_PKA_DefaultSetRegsMapTab(maxsize_words, count_of_regs) \
			rk_pka_set_map_tab(NULL, (count_of_regs), \
					   (maxsize_words), 0, 1)

u32 rk_pka_clear_block_of_regs(u8 first_reg, u8 count_of_regs, u8 len_id);

u32 rk_pka_init(u32 regs_sizes_ptr[RK_PKA_MAX_REGS_COUNT],
		u32 count_of_sizes,
		struct rk_pka_regs_map *regs_map_ptr,
		u32 count_of_regs,
		u32 op_size_bits,
		u32 regsize_words,
		u32 N_NP_T0_T1,
		u32 is_default_map);
#define RK_PKA_DefaultInitPKA(max_size_bits, regsize_words) \
			rk_pka_init(0, 0, 0, 0, (max_size_bits), \
				    (regsize_words), 0, 1)

void rk_pka_finish(void);
u32 rk_pka_calcNp_and_initmodop(u32 len_id, u32 mod_size_bits,
				s8 r_t0, s8 r_t1, s8 r_t2);

u32 rk_pka_div_long_num(u8 len_id, s8 op_a, u32 s, s8 op_b,
			s8 res, s8 r_t1, s8 r_t2);

u32 rk_calcNp_and_initmodop(u32 *N_ptr, u32 N_size_bits,
			    u32 *NP_ptr, u8 np_create_flag,
			    s8 r_t0, s8 r_t1, s8 r_t2);

void rk_pka_copy_data_into_reg(s8 dst_reg, u8 len_id, u32 *src_ptr,
			       u32 size_words);
void rk_pka_copy_data_from_reg(u32 *dst_ptr, u32  size_words,
			       s8 src_reg);
int test_rk3326_rsa(void);
int rk_mpa_alloc(struct mpa_num **mpa, void *data, u32 word_size);
void rk_mpa_free(struct mpa_num **mpa);
int rk_abs_add(void *a, void *b, void *c);
int rk_mod(void *a, void *b, void *c);
int rk_exptmod(void *a, void *b, void *c, void *d);
int rk_exptmod_np(void *m, void *e, void *n, void *np, void *d);

#endif
