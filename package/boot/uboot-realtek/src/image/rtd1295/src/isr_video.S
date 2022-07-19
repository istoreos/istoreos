#define zero	$0
#define k0	$26
#define k1	$27
#define ra	$31

	.section ".text", "ax"
	.globl	ros_isr_video
	.ent	ros_isr_video
ros_isr_video:
	.set	noreorder
        .set	noat

	/* check i channel interrupt */
	lui		k0, 0xb801
	ori		k0, 0x8020
	lw		k1, 0(k0)
	andi		k1, k1, 0x4		# only intst_i
	beqz		k1, 7f
	nop

	/* TVE_INTPOS_I_reg : update vpos */
	lui		k0, 0xb801
	ori		k0, 0x8014
	lw		k1, 0(k0)
	srl		k0, k1, 23		# only i_field
	andi		k0, 0x1
	bnez		k0, 2f
	li		k1, 0
	
	/* check Mixer 1 height */
	lui		k0, 0xb800
	lw		k1, 0x5788(k0)
	andi		k1, k1, 0x7ff
	li		k0, 480
	beq		k0, k1, 2f
	li		k1, 263
	
	li		k1, 313
	
2:
	sll		k1, k1, 14
	lui		k0, 0x01ff
	ori		k0, 0xc000
	and		k1, k1, k0
	lui		k0, 0x0200
	or		k1, k1, k0
	lui		k0, 0xb801
	ori		k0, 0x8020
	sw		k1, 0x4(k0)		# sw	k1, 0xb8018024 (k0 set to 0xb8018020 is to save code space)

	/* TVE_INTST_reg : clear interrupt status */
	li		k1, 0x4
	sw		k1, 0(k0)		# //TVE_INTST_reg : clear interrupt status

7:
        /* check p channel interrupt */
	lw		k1, 0(k0)
	andi		k1, 0x2
	beqz		k1, 8f
	nop
	
	li		k1, 0x2
	sw		k1, 0(k0)		# //TVE_INTST_reg : clear interrupt status
	
8:	
        
        /* check finish of ch1 */
	lui		k0, 0xb800
	lw		k1, 0x5864(k0)
	andi		k1, 0x2
	beqz		k1, 9f
	nop

	/* toggle itop of VO_CH1_reg based on i_field of TVE_SYNCGEN_STATUS_I_reg */
	lui		k0, 0xb801
	ori		k0, 0x8014
	lw		k1, 0(k0)
	srl		k1, k1, 23		# only i_field
	andi		k1, k1, 0x1
	li		k0, 0x1
	subu		k1, k0, k1
	ori		k1, k1, 32
	lui		k0, 0xb800
	sw		k1, 0x57fc(k0)

        /* need change sub-pic ? */
	
	lui		k0, 0xa000
	lw		k0, 0x17fc(k0)
        srl             k0, k0, 8
        lui		k1, 0xde
        ori		k1, k1, 0xadbe
	bne             k0, k1, clean_status /* old style showing */
	nop
	lui		k0, 0xa000
	lw		k0, 0x17fc(k0)
	lui		k1, 0xdead
	ori		k1, k1, 0xbe78
        beq             k0, k1, roller_pic /* new style rolling logo*/
        nop
	/* new style still picture */
	andi 		k0, 0x000000ff

	lui		k1, 0xa000
	sw		k0, 0x1804(k1)
	b		show_pic		
	nop


roller_pic:
	/* check timer count */
	lui  		k0, 0xa000
	lw		k1, 0x1800(k0)
	bnez		k1, dec_count
	nop

        /* is roller pic */
	/* check pic count */
	lui		k0, 0xa000
	lw		k0, 0x1804(k0)

	add		k0, 1

	/* we only allow 5 roller logos */
	li		k1, 0x5
	bne             k0, k1, wr_pic_num
 	nop
	move            k0, zero

wr_pic_num:
	lui 		k1, 0xa000
	sw		k0, 0x1804(k1)
	
show_pic:
	/* write Top address of sub-pic */
	sll		k1, k0, 0x3
	
	lui		k0, 0xa000
	ori		k0, 0x1808
	add		k0, k1

	lw		k1, (k0)
	lui		k0, 0x0fff
	ori		k0, k0, 0xffff
	and		k1, k1, k0
	lui		k0, 0xb800
	sw		k1, 0x53d0(k0)
	/* write bottom address of sub-pic */
        lui 		k1, 0xa000
	lw		k0, 0x1804(k1)
 	
	sll		k1, k0, 0x3

	lui		k0, 0xa000
	ori		k0, 0x180c
	add		k0, k1

	lw		k1, (k0)
	lui		k0, 0x0fff
	ori		k0, k0, 0xffff
	and		k1, k1, k0
	lui		k0, 0xb800
	sw		k1, 0x53d4(k0)
	/* write color lookup table address */
	lui 		k1, 0xa000
	lw		k0, 0x1804(k1)

	sll		k1, k0, 0x4

	lui		k0, 0xa000
	ori		k0, 0x1880
	add		k1, k0	
	lui		k0, 0x0fff
	ori		k0, k0, 0xffff
	and		k1, k1, k0
	lui		k0, 0xb800
	sw		k1, 0x53cc(k0)

reset_count:
	lui 		k0, 0xa000
        lw              k1, 0x17f8(k0)
	sw              k1, 0x1800(k0)
	b		clean_status
	nop

dec_count:
	ori		k0, zero, 1
	sub		k1, k1, k0
	lui             k0, 0xa000
	sw		k1, 0x1800(k0)		


clean_status:

	/* VO_INTST_reg : clear "finish of ch1" status */
	lui		k0, 0xb800

	li		k1, 0x2
	sw		k1, 0x5864(k0)

	/* VO_FC_reg : set ch1 go bit */
	li		k1, 0x3
	sw		k1, 0x5018(k0)

9:
	
/********************************************************/
return:
	mfc0		k0, $14
	nop
	jr		k0
	rfe

	.set	reorder
	.end	ros_isr_video
