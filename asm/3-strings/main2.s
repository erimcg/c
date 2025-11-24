.section .data
STR0:
	.asciz "hello you!\n"

.section .text
printHello:
	movq	$STR0, %rdi
	# printf calls puts
	call puts
	ret

.global main
main:
	# save %rsp in %rbp
	# but first save %rbp since it is a callee register
	# this also aligns %rsp before function call
	# called function prelude
	pushq %rbp
	movq %rsp, %rbp

	call printHello

	movq %rbp, %rsp		# reset %rsp
	popq %rbp

	movq $0, %rax		# return 0
	ret
	
