	.section ".text", "ax"
	.globl	ros_bootvector
	.ent	ros_bootvector
ros_bootvector:
	.set 	noreorder
	j		0x80
	nop
	j		0x80
	nop
	j		0x80
	nop
	j		0x80
	nop
	j		0x80
	nop
	j		0x80
	nop
	j		0x80
	nop
	j		0x80
	nop
	.set	reorder
	.end	ros_bootvector
