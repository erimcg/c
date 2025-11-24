.section .data
STR0:	.asciz "Arrays\n"

.section .text
.global main

main:
	pushq %rbp
	movq %rsp, %rbp

	movq $STR0, %rdi
	call printf

	subq $48, %rsp
	
	movq %rsp, %rdi		# arr
	movq $10, %rsi		# length = 10
	call print_array

	movq %rsp, %rdi		# arr
	movq $10, %rsi		# length = 10
	movl $1, %edx		# value = 1
	call init_array		# add to array: 1,2,3,4, etc

	movq %rsp, %rdi		# arr
	movq $10, %rsi		# length = 10
	call print_array

	movq %rbp, %rsp
	popq %rbp
	ret
