.section .data
STR0:
	.asciz "Enter integer: "
STR1:
	.asciz	"%d"
STR2:
	.asciz "x: %d, y: %d\n"

.section .text
.global main

main:
	pushq %rbp			# prelude to align boundary
	movq %rsp, %rbp

	pushq $0			# declare x
	pushq $0			# declare y

	movq $STR0, %rdi	# print "Enter integer: "
	call printf

	movq $STR1, %rdi	# scan in x
	leaq 8(%rsp), %rsi
	call scanf

	movq $STR0, %rdi	# print "Enter integer: "
	call printf

	movq $STR1, %rdi	# scan in y
	leaq (%rsp), %rsi
	call scanf

	movq $STR2, %rdi	# print x: %d, y: %d\n"
	movq 8(%rsp), %rsi
	movq (%rsp), %rdx
	call printf

	movq %rbp, %rsp		# reset rsp
	popq %rbp

	movq $0, %rax		# return 0
	ret
	
