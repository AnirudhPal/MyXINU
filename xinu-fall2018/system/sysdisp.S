/* sysdisp.s - sysdisp (x86) */

/*------------------------------------------------------------------------
 * sysdisp  -  Interrupt dispatcher for Software Interrupts - pal5, Sep 25
 *------------------------------------------------------------------------
 */
#include <icu.s>
		.text
		.globl	sysdisp		# System Call interrupt dispatcher
sysdisp:
		cli			# Disable further interrupts
		cmp	$3, %eax	# Compare EAX with 3
		jne	wrong		# Jump to trap if not 3
		call	getpid		# Call getpid
		sti			# Restore interrupt status
		iret			# Return from interrupt

wrong:					# Xtrap Clone
		pushl	%ebp
		movl	%esp,%ebp
		pushal
		movl	%esp, %eax
		pushl	%eax
		pushl	$33
		call	trap
		iret
		
