	.section ".text", "ax"
	.globl	a_entry
	.ent		a_entry
a_entry:
	.set 	noreorder

	/* set 5280 CP0 status register and vector interrupt address */
#if 1
	.word 0x40106000,0x3c118000,0x36310001,0x02118025,\
		 0x3c11ffbf,0x3631ffff,0x02118024,0x40906000,\
		 0x3c108000,0x36101900,0x40f01000,0x00000000,\
		 0x3c1000ff,0x40f00000,0x00000000
#else

	mfc0	s0, $12
	lui 	s1,0x8000
	ori 	s1,s1,0x1
	or		s0,s0,s1
	lui 	s1,0xffbf
	ori 	s1,s1,0xffff
	and 	s0,s0,s1
	mtc0	s0,$12
	lui 	s0,0x8000
	ori 	s0,s0,0x1900
	mtlxc0	s0,INTVEC
	nop
	lui 	s0,0xff
	mtlxc0	s0,ESTATUS
	nop

#endif

	/* audio */
a1:
	li		$17, 0xa001f0e0			// default reg. (arm romcode size(124KB; page alignment)+0xe0,MIPS_AUDIO_FW_ENTRY_PTR_ADDR, please refer to rtd1295's system.h)	
	li		$18, 0xd801a000			// hw semaphore reg 
//	lw		$16, 8($17)				// check if we need to do un-lzma
	nop
//	bnez	$16, 1f
//	lui		$16, 0x8200
	lw		$16, 0($17)
	nop
	bnez	$16, 1f
	nop
	sw		$0, ($18)
a_loop:
	b		a_loop
	nop
1:
	jalr		$16
	sw		$0, ($18)

	.set	reorder
	.end	a_entry
