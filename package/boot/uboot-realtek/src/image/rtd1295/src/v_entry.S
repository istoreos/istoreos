/* Assigned Company values for bits 23:16 of the PRId Register
   (CP0 register 15, select 0).  As of the MIPS32 and MIPS64 specs from
   MTI, the PRId register is defined in this (backwards compatible)
   way:

   +----------------+----------------+----------------+----------------+
   | Company Options| Company ID     | Processor ID   | Revision       |
   +----------------+----------------+----------------+----------------+
   31            24 23            16 15             8 7

   I don't have docs for all the previous processors, but my impression is
   that bits 16-23 have been 0 for all MIPS processors before the MIPS32/64
   spec.
*/


/* Register */
#define REG_HW_SEMAPHORE		0xb801a000
#define REG_UART0_BASE			0xb8062300
#define REG_UART1_BASE			0xb801b100
#define DEFAULT_UART			REG_UART0_BASE

#define s0	$16
#define s1	$17

/* Value */
#define PRID_LX_5280_VCPU1		0x01A5C601
#define PRID_LX_5280_VCPU2		0x01A6C601
#define KSEG_MSK          		0xE0000000
#define KSEG0BASE				0x80000000
#define KSEG1BASE				0xA0000000
#define VIDEO_FW_ENTRY_PTR_V1	0xa00000e4
#define VIDEO_FW_ENTRY_PTR_V2	0xa00000dc

#define KSEG0A(reg)     and reg, ~KSEG_MSK; or reg, KSEG0BASE

	.section ".text", "ax"
	.globl	v_entry
	.ent	v_entry
v_entry:
	.set noreorder
/*LEAF(v_entry)*/

	/* check if A/V CPU BISR is done */

//1:

	//lw	$9, lk_5280_ready_addr
	//nop				/* 5181 need nop after lw */
	//beq	$9, zero, 1b
	//nop

	/* run v_entry at cached address */
//	la	$8, 1f
//	KSEG0A( $8)
//	j	$8
//	nop

//1:
	/* set 5280 CP0 status register and vector interrupt address */
#if 1
	.word 0x40106000,0x3c118000,0x36310001,0x02118025,\
	     0x3c11ffbf,0x3631ffff,0x02118024,0x40906000,\
	     0x3c108000,0x36101900,0x40f01000,0x00000000,\
	     0x3c1000ff,0x40f00000,0x00000000
#else

	mfc0	s0, $12
	lui		s1,0x8000
	ori		s1,s1,0x1
	or		s0,s0,s1
	lui		s1,0xffbf
	ori		s1,s1,0xffff
	and		s0,s0,s1
	mtc0	s0,$12
	lui		s0,0x8000
	ori		s0,s0,0x1900
	mtlxc0	s0,INTVEC
	nop
	lui		s0,0xff
	mtlxc0	s0,ESTATUS
	nop

#endif

#if 0
	.word 0x40106000,0x3c118000,0x36310001,0x02118025,\
	     0x3c11ffbf,0x3631ffff,0x02118024,0x40906000,\
	     0x3c1000ff,0x40f00000,0x00000000
#endif

	/* Print Vwait */
	li		$8, 0x56	/* V */
	sw		$8, DEFAULT_UART

	li		$8, 0x77	/* w */
	sw		$8, DEFAULT_UART

	li		$8, 0x61	/* a */
	sw		$8, DEFAULT_UART

	li		$8, 0x69	/* i */
	sw		$8, DEFAULT_UART

	li		$8, 0x74	/* t */
	sw		$8, DEFAULT_UART

	li		$8, 0x20
	sw		$8, DEFAULT_UART

	/* Wait for HW semaphore */
	li		$9, KSEG1BASE
	la		$8, REG_HW_SEMAPHORE
	or		$8, $9		/* Make sure it is uncached */

get_hw_semaphore :
	# delay a while (reduce bus traffic)
	li		$10, 100
1:
	subu	$10, 0x1
	bnez	$10, 1b
	nop

	# check if HW semaphore is available
	lw		$9, 0($8)
	nop		/* 5181 need nop after lw */
	beq		$9, $0, get_hw_semaphore
	nop

v12_go:
	/***************************************/
	/* distinguish between VCPU1 and VCPU2 */
	/***************************************/
	mfc0	$17, $15
	li		$18, PRID_LX_5280_VCPU1
	bne		$17, $18, v2_go
	nop
	b		v1_go
	nop

v12_hang_loop:
	b		v12_hang_loop
	nop

v1_go:
	/* Print V1go */
	li		$8, 0x56	/* V */
	sw		$8, DEFAULT_UART

	li		$8, 0x31	/* 1 */
	sw		$8, DEFAULT_UART

	li		$8, 0x67	/* g */
	sw		$8, DEFAULT_UART

	li		$8, 0x6F	/* o */
	sw		$8, DEFAULT_UART

	li		$8, 0x20
	sw		$8, DEFAULT_UART

//	b		v12_hang_loop
//	nop

	li		$17, VIDEO_FW_ENTRY_PTR_V1
	li		$18, REG_HW_SEMAPHORE
//	lw		$16, 8($17) 		// check if we need to do un-lzma
	nop
//	bnez	$16, 1f
//	lui 	$16, 0x8280
	lw		$16, 0($17)
	nop
	bnez	$16, 1f
	nop
	sw		$0, ($18)
v1_loop:
	b		v1_loop
	nop
1:
	jalr	$16
	sw		$0, ($18)


v2_go:
	/* Print V2go */
	li		$8, 0x56	/* V */
	sw		$8, DEFAULT_UART

	li		$8, 0x32	/* 2 */
	sw		$8, DEFAULT_UART

	li		$8, 0x67	/* g */
	sw		$8, DEFAULT_UART

	li		$8, 0x6F	/* o */
	sw		$8, DEFAULT_UART

	li		$8, 0x20
	sw		$8, DEFAULT_UART

//	b		v12_hang_loop
//	nop

	li		$17, VIDEO_FW_ENTRY_PTR_V2
	li		$18, REG_HW_SEMAPHORE
//	lw		$16, 8($17) 		// check if we need to do un-lzma
	nop
//	bnez	$16, 1f
//	lui 	$16, 0x8280
	lw		$16, 0($17)
	nop
	bnez	$16, 1f
	nop
	sw		$0, ($18)
v2_loop:
	b		v2_loop
	nop
1:
	jalr	$16
	sw		$0, ($18)

/*END(v_entry)	*/
	.set reorder
	.end v_entry

