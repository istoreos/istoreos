/*
 * MIPS exception redirect.
 */

	.section ".text", "ax"
	.globl	ros_exc_redirect
	.ent	ros_exc_redirect
ros_exc_redirect:
	.set 	noreorder

	// Note: Let all mips cpu jump to 0xa0000100 to do exception dispatch.
mips_exc_0x80:
	j		0x100
	nop						/* reserve for jump */
	nop						/* reserve for audio fw gdb vector gdb_thread_syscall_rmt at 0xa000_0088 */
	nop						/* reserve for video fw 1 gdb vector gdb_thread_syscall_rmt at 0xa000_008c */
	nop						/* reserve for video fw 2 gdb vector gdb_thread_syscall_rmt at 0xa000_0090 */

	// Notes: Audio firmware will overwrite instructions from 0x94 to 0xa0.
	//        Video firmware 1 will overwrite instructions from 0xa4 to 0xb0.
	//        Video firmware 2 will overwrite instructions from 0xb4 to 0xc0.
	//        We need to reserve 4 instructions for each of them.

a1_exec_0x94:
	b		a1_exec_0x94	/* reserve for audio fw at 0xa000_0094 */
	nop						/* reserve for audio fw at 0xa000_0098 */
	nop						/* reserve for audio fw at 0xa000_009c */
	nop						/* reserve for audio fw at 0xa000_00a0 */

v1_exec_0xa4:
	b		v1_exec_0xa4	/* reserve for video fw 1 at 0xa000_00a4 */
	nop						/* reserve for video fw 1 at 0xa000_00a8 */
	nop						/* reserve for video fw 1 at 0xa000_00ac */
	nop						/* reserve for video fw 1 at 0xa000_00b0 */

v2_exec_0xb4:
	b		v2_exec_0xb4	/* reserve for video fw 2 at 0xa000_00b4 */
	nop						/* reserve for video fw 2 at 0xa000_00b8 */
	nop						/* reserve for video fw 2 at 0xa000_00bc */
	nop						/* reserve for video fw 2 at 0xa000_00c0 */

	.set	reorder
	.end	ros_exc_redirect

