/*
 * MIPS exception dispatch.
 * Need to use the register $k0~$k1 that were reserved for kernel usage.
 */

#define k0	$26
#define k1	$27

//#define PRID_LX_5281_ACPU			0x025ADC02
//#define PRID_LX_5280_ACPU			0x025AC601
//#define PRID_LX_5280_VCPU1		0x01A5C601
//#define PRID_LX_5280_VCPU2		0x01A6C601

#define AUDIO_EXC_ENTRY				0x94
#define VIDEO_1_EXC_ENTRY			0xa4
#define VIDEO_2_EXC_ENTRY			0xb4

	.section ".text", "ax"
	.globl	ros_exc_dispatch
	.ent	ros_exc_dispatch
ros_exc_dispatch:
	.set 	noreorder

	mfc0	k0, $15
	lui		k1, 0x025A
	ori		k1, k1, 0xC601
	bne		k0, k1, v12
	nop

a1:
	j		AUDIO_EXC_ENTRY	/* reserve for audio fw at AUDIO_EXC_ENTRY */
	nop

v12:
	lui		k1, 0x01A5
	ori		k1, k1, 0xC601
	bne		k0, k1, v2
	nop

v1:
	j		VIDEO_1_EXC_ENTRY	/* reserve for video fw 1 at VIDEO_1_EXC_ENTRY */
	nop

v2:
	j		VIDEO_2_EXC_ENTRY	/* reserve for video fw 2 at VIDEO_2_EXC_ENTRY */
	nop

	.set	reorder
	.end	ros_exc_dispatch
