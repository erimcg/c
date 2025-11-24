.section .data
STR0:
	.asciz "hello\n"

.section .text
.global main
main:
	# return address pushed onto stack before main is called
	# %rsp not 16-byte aligned before call instruction
	# subtract 8 from %rsp to align

	subq $8, %rsp
	
	movq $STR0, %rdi	
	call printf

	addq $8, %rsp
	ret
