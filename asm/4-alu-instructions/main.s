.section .data
STR1:
	.asciz "Division\n"
STR2:
	.asciz "Enter integer: "
STR3:
	.asciz "%ld"
STR4:
	.asciz "x: %ld, y: %ld\n"
STR5:
	.asciz "x/y: %ld, x%y: %ld\n"

.section .text
.global main
main:
	pushq %rbp
	movq %rsp, %rbp

	movq $STR1, %rdi	# print "Division\n"
	call printf

	subq $16, %rsp		# reserve space on stack for x and y
	movq $0, 8(%rsp)	# set x to 0
	movq $0, (%rsp)		# set y to 0
	
	movq $STR2, %rdi	# print "Enter integer: "
	call printf

	movq $STR3, %rdi	# read in x
	leaq 8(%rsp), %rsi
	call scanf

	movq $STR2, %rdi	# print "Enter integer: "
	call printf			

	movq $STR3, %rdi	# read in y
	leaq (%rsp), %rsi
	call scanf

	movq $STR4, %rdi	# " Print x: %ld, y: %ld\n"
	movq 8(%rsp), %rsi
	movq (%rsp), %rdx
	call printf

	movq 8(%rsp), %rax	# set %rax to x
	cqto 				# sign extend %rax into %rdx
	idivq (%rsp)		# divide %rdx:%rax by y
	
	movq $STR5, %rdi	# print "x/y: %ld, x%y: %ld\n"	
	movq %rax, %rsi
	# remainder already in %rdx
	call printf

	movq %rbp, %rsp
	popq %rbp
	ret
