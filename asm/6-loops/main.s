
.section .data

STR0:	.asciz "Enter a 4-byte integers: "
STR1:	.asciz "%d"
STR2:	.asciz "x: %d\n"
STR3:	.asciz "y: %d\n"
STR4:	.asciz "sum 1 to 10: %d\n"
STR5:	.asciz "sum 1 to %d: %d\n"
STR6:	.asciz "sum %d to %d: %d\n"
STR7:	.asciz "%d! = %d\n"

.section .text
.global main

main:
	pushq %rbp
	movq %rsp, %rbp

# sum 1 to 10
	call sum1to10
	movl %eax, %edi

	movq $STR4, %rdi
	movl %eax, %esi
	call printf

# read in x
	subq $16, %rsp
	
	movq $STR0, %rdi
	call printf

	movq $STR1, %rdi
	leaq 12(%rsp), %rsi
	call scanf

	movq $STR2, %rdi
	movl 12(%rsp), %esi
	call printf

# sum 1 to x
	movl 12(%rsp), %edi
	call sum1toX

	movq $STR5, %rdi
	movl 12(%rsp), %esi
	movl %eax, %edx
	call printf

# read in y
	movq $STR0, %rdi
	call printf

	movq $STR1, %rdi
	leaq 8(%rsp), %rsi
	call scanf

	movq $STR3, %rdi
	movl 8(%rsp), %esi
	call printf

# sum x to y
	movl 12(%rsp), %edi
	movl 8(%rsp), %esi
	call sumXtoY

	movq $STR6, %rdi
	movl 12(%rsp), %esi
	movl 8(%rsp), %edx
	movl %eax, %ecx
	call printf

# fact(x)
	movl 12(%rsp), %edi
	call fact

	movq $STR7, %rdi
	movl 12(%rsp), %esi
	movl %eax, %edx
	call printf

	movq %rbp, %rsp
	popq %rbp

	ret
