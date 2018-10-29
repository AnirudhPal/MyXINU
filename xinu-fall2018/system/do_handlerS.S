
	.text
	.globl	do_handlerS

do_handlerS:
	call disable
	call restore
	call do_handler
	movl proctab, %ecx
	movl currpid(%ecx), %ecx 
	call disable
	ret
