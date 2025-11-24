
.section .data
STR0:	.asciz "Enter two 4-byte integers: "
STR1:	.asciz "%d %d"
STR2:	.asciz "x: %d, y: %d\n"

LT:     .asciz "Less than\n"
GE:		.asciz "Greater or equal\n"

.section .text
.global cond_jmp 
.global cond_mov
.global main

main:
	pushq %rbp
	movq %rsp, %rbp

	movq $STR0, %rdi		# print "Enter two 4-byte ..."
	call printf

	subq $16, %rsp			# reserve room for 2 ints (8 bytes) + 8 to align boundary
	
	movq $STR1, %rdi		# scan x and y
	leaq 12(%rsp), %rsi
	leaq 8(%rsp), %rdx
	call scanf

	movq $STR2, %rdi		# print x and y
	movl 12(%rsp), %esi
	movl 8(%rsp), %edx
	call printf

	movl 12(%rsp), %edi		# pass x and y to cond_jmp	
	movl 8(%rsp), %esi
	call cond_jmp 

	movl 12(%rsp), %edi		# pass x and y to cond_mov
	movl 8(%rsp), %esi
	call cond_mov

	movq %rbp, %rsp
	popq %rbp

	ret

 # x in edi, y in esi
cond_jmp:
    pushq %rbp				# using call so have to align boundary

    # if x < y 
    #   print "less than" 
    # else 
    #   print "not less than"

    cmpl %esi, %edi			
    jge .XGEY				# if x >= y then jump to .XGEY

    movq $LT, %rdi			# print "Less than"
    call printf
    jmp .END

.XGEY:
    movq $GE, %rdi			# print "Greater or equal"
    call printf

.END:
    popq %rbp
    ret

 # x in edi, y in esi
cond_mov:
    pushq %rbp
	movq %rsp, %rbp

    # if x < y 
    #   print "Less than" 
    # else 
    #   print "Greater or equal"

	pushq %r12			# callee saved so have so save before using
	pushq %r13

    movl %edi, %r12d	# copy x to %r12d
    movl %esi, %r13d	# copy y to %r13d 

	movq $STR2, %rdi	# print x and y
	movl %r12d, %esi
	movl %r13d, %edx

	call printf

    movq $LT, %rdi		# assume x lt y, set up %rdi to print "Less than"
    movq $GE, %rsi		# assume x ge y, set up to %rsi to print "Greater or equal"

    cmpl %r13d, %r12d 
    cmovge %rsi, %rdi 	# if x ge y, move %rsi into %rdi to print "Greater or equal"
    call printf

	popq %r13
	popq %r12

	leave
    ret
