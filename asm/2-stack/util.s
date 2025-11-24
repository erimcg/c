.global stack_swap
.global increment
.global sum
.global err

# long* px in %rdi, long* py in %rsi
# swaps values add addresses

stack_swap:
	pushq (%rdi)
	pushq (%rsi)
	
	popq (%rdi)
	popq (%rsi)
	ret

sum:
	movq %rdi, %rax
	addq %rsi, %rax
	addq %rdx, %rax
	addq %rcx, %rax
	addq %r8, %rax
	addq %r9, %rax
	# skip 8 bytes at %rsp which holds return address back to main
	addq 8(%rsp), %rax
	addq 16(%rsp), %rax
	ret

err:
	# commenting either creates seg fault
	# must reset %rsp before returning
	subq $8, %rsp
	addq $8, %rsp
	ret	
