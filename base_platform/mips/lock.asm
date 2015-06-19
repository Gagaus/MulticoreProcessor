.section .text
.globl lockit
.type lockit, @function

lockit:	
pushl %ebp
movl %esp, %ebp
movl 8(%ebp),%eax
movl (%eax,%edi,4), %edx

ll 	r2, plock(r0)
bnez r2,  lockit
addi r2, r0, 1
sc   r2, plock(r0)
beqz r2, lockit