.section .data
STR1: .asciz "Conditionals\n"
STR2: .asciz "Enter integer: "
STR3: .asciz "%ld"
STR4: .asciz "x: %ld\n"
XLT0: .asciz "x < 0\n"
XEQ0: .asciz "x == 0\n"
XGT0: .asciz "x > 0\n"

.section .text
.global main
main:
	pushq %rbp
	movq %rsp, %rbp

	movq $STR1, %rdi
	call printf

	movq $STR2, %rdi
	call printf

	subq $16, %rsp
	movq $0, 8(%rsp)		
	
	movq $STR3, %rdi
	leaq 8(%rsp), %rsi
	call scanf

	movq $STR4, %rdi
	movq 8(%rsp), %rsi
	call printf

	movq 8(%rsp), %rax 		#copy x into %rax
	test %rax, %rax 
	jl .XLT0				# if x < 0 then jmp
	je .XEQ0				# if x == 0 then jmp
	jg .XGT0				# if x > 0 then jmp

.XLT0:
	movq $XLT0, %rdi
	call printf
	jmp .END

.XEQ0:	
	movq $XEQ0, %rdi
	call printf
	jmp .END

.XGT0:
	movq $XGT0, %rdi
	call printf

.END:
	movq %rbp, %rsp
	popq %rbp
	ret
