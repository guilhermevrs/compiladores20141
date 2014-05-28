	.file	"t1.c"
	.globl	main
main:
	pushq	%rbp
	movq	%rsp, %rbp

	popq	%rbp
	ret
