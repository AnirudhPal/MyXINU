	.globl	revbyteorder_asm
	.type	revbyteorder_asm, %function

revbyteorder_asm:
	pushl	%ebp
	movl	%esp, %ebp
	movl	8(%ebp), %eax
	bswap	%eax
	movl	%ebp, %esp
	pop	%ebp
	ret
