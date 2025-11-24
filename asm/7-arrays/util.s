.section .data
STR0:	.asciz "start of array: %p\n"
STR1:	.asciz "length of array: %ld\n"
STR2:	.asciz "i = %ld\n"
STR3:	.asciz "arr[%ld] = %d\n"
STR4:	.asciz "value: %d\n"

.section .text
.global print_array
.global init_array

# arr in %rdi, length in %rsi
print_array:
	pushq %rbp
	movq %rsp, %rbp	
	pushq %r12
	pushq %r13

	movq %rdi, %r12		# arr
	movq %rsi, %r13		# length 
	movq $0, %rbx		# i = 0

	movq $STR0, %rdi
	movq %r12, %rsi
	call printf

	movq $STR1, %rdi
	movq %r13, %rsi
	call printf

	jmp .TEST1

.LOOP1:
	movq $STR3, %rdi
	movq %rbx, %rsi
	movl (%r12,%rbx,4), %edx
	call printf
	incq %rbx

.TEST1:

	#movq $STR1, %rdi
	#movq %r13, %rsi
	#call printf

	#movq $STR2, %rdi
	#movq %rbx, %rsi
	#call printf

	cmpq %r13, %rbx
	jl .LOOP1

	popq %r13
	popq %r12

	leave
	ret

# arr in %rdi, length in %rsi, value in %edx
# insert into arr value, value+1, value+2, etc
init_array:
	pushq %rbp
	movq %rsp, %rbp	
	pushq %r12
	pushq %r13

	movq %rdi, %r12		# arr
	movq %rsi, %r13		# length 
	movl %edx, %r14d	# value
	movq $0, %rbx		# i = 0

	movq $STR0, %rdi
	movq %r12, %rsi
	call printf

	movq $STR1, %rdi
	movq %r13, %rsi
	call printf

	movq $STR4, %rdi
	movl %r14d, %esi
	call printf

	jmp .TEST2

.LOOP2:
	movl %r14d, (%r12,%rbx,4)
	incq %rbx
	incl %r14d

.TEST2:
	cmpq %r13, %rbx
	jl .LOOP2

	popq %r13
	popq %r12
	leave
	ret
