.global get_ten
.global add
.global test_movq
.global increment

get_ten:
	movq $0xa, %rax
	ret

add:
	movq %rdi, %rax
	addq %rsi, %rax
	ret

test_movq:
	movabsq $0xaaaaaaaaaaaaaaaa, %rax
	#movl $0xffffffff, %eax		# 0's out 4 high order bytes
	movq $0xffffffff, %rax
	ret

increment:
	addl $1, (%rdi) 
	ret

