	.file	"revbyteorder_gcc.c"
	.text
	.globl	revbyteorder_gcc
	.type	revbyteorder_gcc, @function
revbyteorder_gcc:
.LFB0:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	call	__x86.get_pc_thunk.ax
	addl	$_GLOBAL_OFFSET_TABLE_, %eax
	movl	8(%ebp), %eax
	shrl	$24, %eax
	movl	%eax, %edx
	movl	8(%ebp), %eax
	sarl	$8, %eax
	andl	$65280, %eax
	orl	%eax, %edx
	movl	8(%ebp), %eax
	sall	$8, %eax
	andl	$16711680, %eax
	orl	%edx, %eax
	movl	%eax, %edx
	movl	8(%ebp), %eax
	sall	$24, %eax
	orl	%edx, %eax
	movl	%eax, 8(%ebp)
	movl	8(%ebp), %eax
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE0:
	.size	revbyteorder_gcc, .-revbyteorder_gcc
	.section	.text.__x86.get_pc_thunk.ax,"axG",@progbits,__x86.get_pc_thunk.ax,comdat
	.globl	__x86.get_pc_thunk.ax
	.hidden	__x86.get_pc_thunk.ax
	.type	__x86.get_pc_thunk.ax, @function
__x86.get_pc_thunk.ax:
.LFB1:
	.cfi_startproc
	movl	(%esp), %eax
	ret
	.cfi_endproc
.LFE1:
	.ident	"GCC: (Ubuntu 7.3.0-16ubuntu3) 7.3.0"
	.section	.note.GNU-stack,"",@progbits
