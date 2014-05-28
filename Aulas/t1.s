	.file	"t1.c"
	.globl	a
	.data
	.align 4
	.type	a, @object
	.size	a, 4
a:
	.long	3
	.globl	b
	.align 4
	.type	b, @object
	.size	b, 4
b:
	.long	2
	.globl	c
	.bss
	.align 4
	.type	c, @object
	.size	c, 4
c:
	.zero	4
	.section	.rodata
.LC0:
	.string	"%d\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	a(%rip), %ecx
	movl	b(%rip), %eax
	subl	%eax, %ecx
	movl	%ecx, %eax
	movl	%eax, c(%rip)
	movl	c(%rip), %edx
	movl	$.LC0, %eax
	movl	%edx, %esi
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Ubuntu/Linaro 4.6.3-1ubuntu5) 4.6.3"
	.section	.note.GNU-stack,"",@progbits
