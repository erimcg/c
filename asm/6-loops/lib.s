
.section .data
STR0:	.asciz "sum: %d"

.section .text
.global sum1to10
.global sum1toX
.global sumXtoY
.global fact

# Jump to the Middle Form
# sum 1 to 10 (inclusive)
sum1to10:
	movl $0, %eax
	movl $1, %edi

	jmp .TEST1
.LOOP1:
	addl %edi, %eax
	incl %edi
.TEST1:
	cmpl $10, %edi
	jle .LOOP1

	rep; ret	

# Guarded-do Form
# sum(x) sum 1 to x (inclusive)
# x in %edi
sum1toX:	
	movl $0, %eax
	movl %edi, %esi
	movl $1, %edi

	cmpl %esi, %edi
	jg .DONE2

.LOOP2:
	addl %edi, %eax
	incl %edi

	cmpl %esi, %edi
	jle .LOOP2

.DONE2:
	rep; ret	

# Jump to the Middle Form
# sum(x,y) sum x to y (inclusive)
# x in %edi, y in %esi
sumXtoY:
	movl $0, %eax

	jmp .TEST3
.LOOP3:
	addl %edi, %eax
	incl %edi
.TEST3:
	cmpl %esi, %edi
	jle .LOOP3

	rep; ret

# Jump to the Middle Form
# fact(n)
# n in %edi
fact:
	movl $1, %eax
	movl $1, %esi
	jmp .TEST4

.LOOP4:
	imull %esi, %eax
	incl %esi

.TEST4:
	cmpl %edi, %esi
	jle .LOOP4

	rep; ret
