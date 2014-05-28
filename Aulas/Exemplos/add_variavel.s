    .file   "t1.c"
    .data

    .align 4
    .size   a, 4
a:
    .long   32765

    .align 4
    .size   b, 4
b:
    .long   10

    .align 4
    .size   c, 4
c:
    .long   10

    .text
    .globl  main
main:
    pushq   %rbp
    movq    %rsp, %rbp

    movl    a(%rip), %edx
    movl    b(%rip), %eax
    addl    %edx, %eax
    movl    %eax, c(%rip)

    popq    %rbp
    ret
