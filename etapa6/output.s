
	.data

a: 
	.long	1

b: 
	.long	2

c: 
	.long	0

d: 
	.long	0

x: 
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0

z: 
	.long 0
	.long 1
	.long 2
	.long 3
	.long 4
	.long 5
	.long 6
	.long 7
	.long 8

e: 
	.long	0

x: 
	.long	0

n: 
	.long	0

.LC0:
	.string	"%d"

	.section	.rodata
	.globl	main
main:
.LFB0:
	pushq	%rbp
	movq	%rsp, %rbp
	movl a(%rip), %edx
	movl b(%rip), %eax
 	addl %edx, %eax

	movl __Temp17(%rip), %edx
	movl c(%rip), %eax
 	addl %edx, %eax

	movl	__Temp18(%rip), %eax
	movl	%eax, c(%rip)

	movl c(%rip), %edx
	movl a(%rip), %eax
	mull %edx, %eax

	movl	__Temp19(%rip), %eax
	movl	%eax, d(%rip)

	movl	c(%rip), %eax
	movl	a(%rip), %edx
	movl	%edx, -4(%rbp)
	movl	%eax, %edx
	sarl	$31, %edx
	idivl	-4(%rbp)

	movl	__Temp20(%rip), %eax
	movl	%eax, d(%rip)

	movl c(%rip), %edx
	movl a(%rip), %eax
	subl %edx, %eax

	movl	__Temp21(%rip), %eax
	movl	%eax, d(%rip)

	movl 30(%rip), %edx
	movl b(%rip), %eax
	mull %edx, %eax

	movl 100(%rip), %edx
	movl __Temp22(%rip), %eax
 	addl %edx, %eax

	movl 200(%rip), %edx
	movl __Temp23(%rip), %eax
	mull %edx, %eax

	movl	__Temp24(%rip), %eax
	movl	%eax, a(%rip)

	movl 30(%rip), %edx
	movl 'A'(%rip), %eax
	mull %edx, %eax

	movl 100(%rip), %edx
	movl __Temp25(%rip), %eax
 	addl %edx, %eax

	movl 200(%rip), %edx
	movl __Temp26(%rip), %eax
	mull %edx, %eax

	movl	__Temp27(%rip), %eax
	movl	%eax, a(%rip)

	movl	a(%rip), %edi
	movl	b(%rip), %esi
	movl	soma(%rip), %eax
	movl	%eax, b(%rip)

	movl	a(%rip), %edx
	movl	b(%rip), %eax
	cmpl	%eax, %edx
	setg	%al
	movzbl	%al, %eax

	movl	__Label3(%rip), %eax
	movl	$1, %edx
	cmpl	%eax, %edx
	jnz	__Temp28
	movl	"a maior que b"(%rip), %eax
	movl	%eax, %esi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf

__Label3:
	movl	c(%rip), %edx
	movl	a(%rip), %eax
	cmpl	%eax, %edx
	setg	%al
	movzbl	%al, %eax

	movl	__Temp29(%rip), %eax
	movl	%eax, e(%rip)

	movl	c(%rip), %edx
	movl	a(%rip), %eax
	cmpl	%eax, %edx
	setl	%al
	movzbl	%al, %eax

	movl	__Temp30(%rip), %eax
	movl	%eax, e(%rip)

__Label4:
	movl	a(%rip), %edx
	movl	1(%rip), %ecx
	movl	soma(%rip), %eax
	movl	%eax, a(%rip)

	movl b(%rip), %edx
	movl 1(%rip), %eax
 	addl %edx, %eax

	movl	__Temp31(%rip), %eax
	movl	%eax, b(%rip)

	movl	__Label5(%rip), %eax
	movl	$1, %edx
	cmpl	%eax, %edx
	jnz	__Temp32
	movl	c(%rip), %edx
	movl	10(%rip), %eax
	cmpl	%eax, %edx
	setl	%al
	movzbl	%al, %eax

	jmp	__Label4

	movl	a(%rip),%eax
	leave
	ret
.LFE0:
	.size	main,	.-main
	.globl	soma
soma:
.LFB1:
	pushq	%rbp
	movq	%rsp, %rbp
	movl x(%rip), %edx
	movl n(%rip), %eax
 	addl %edx, %eax

	movl	__Temp33(%rip),%eax
	leave
	ret
.LFE1:
	.size	soma,	.-soma
