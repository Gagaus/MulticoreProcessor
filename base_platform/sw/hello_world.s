	.file	1 "hello_world.c"
	.section .mdebug.abi32
	.previous
	.gnu_attribute 4, 3
	.globl	procCounter
	.section	.sbss,"aw",@nobits
	.align	2
	.type	procCounter, @object
	.size	procCounter, 4
procCounter:
	.space	4

	.comm	procN,4,4
	.globl	lock_aux
	.section	.sdata,"aw",@progbits
	.align	2
	.type	lock_aux, @object
	.size	lock_aux, 4
lock_aux:
	.word	8388608
	.text
	.align	2
	.globl	lock_init
	.set	nomips16
	.ent	lock_init
	.type	lock_init, @function
lock_init:
	.frame	$fp,8,$31		# vars= 0, regs= 1/0, args= 0, gp= 0
	.mask	0x40000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-8
	sw	$fp,4($sp)
	move	$fp,$sp
	sw	$4,8($fp)
	lw	$2,8($fp)
	sw	$0,0($2)
	move	$sp,$fp
	lw	$fp,4($sp)
	addiu	$sp,$sp,8
	j	$31
	nop

	.set	macro
	.set	reorder
	.end	lock_init
	.size	lock_init, .-lock_init
	.rdata
	.align	2
$LC0:
	.ascii	"Aparentemente o lock t\303\241 livre\000"
	.align	2
$LC1:
	.ascii	"To no core %d\012\000"
	.align	2
$LC2:
	.ascii	"Peguei o lock\000"
	.text
	.align	2
	.globl	lock
	.set	nomips16
	.ent	lock
	.type	lock, @function
lock:
	.frame	$fp,40,$31		# vars= 16, regs= 2/0, args= 16, gp= 0
	.mask	0xc0000000,-4
	.fmask	0x00000000,0
	addiu	$sp,$sp,-40
	sw	$31,36($sp)
	sw	$fp,32($sp)
	move	$fp,$sp
	sw	$4,40($fp)
	lw	$2,40($fp)
	sw	$2,24($fp)
$L3:
	lw	$2,24($fp)
	lw	$3,16($fp)
 #APP
 # 24 "hello_world.c" 1
	ll $3, 0($2) 

 # 0 "" 2
 #NO_APP
	lw	$2,16($fp)
	bne	$2,$0,$L3
	lui	$2,%hi($LC0)
	addiu	$4,$2,%lo($LC0)
	jal	puts
	sw	$0,20($fp)
	j	$L4
$L5:
	lw	$2,20($fp)
	addiu	$2,$2,1
	sw	$2,20($fp)
$L4:
	lw	$3,20($fp)
	li	$2,65536			# 0x10000
	ori	$2,$2,0x86a0
	slt	$2,$3,$2
	bne	$2,$0,$L5
	li	$2,1			# 0x1
	sw	$2,16($fp)
	lw	$2,%gp_rel(procN)($28)
	lui	$3,%hi($LC1)
	addiu	$4,$3,%lo($LC1)
	move	$5,$2
	jal	printf
	lw	$2,24($fp)
 #APP
 # 37 "hello_world.c" 1
	sc 0($2), $2 

 # 0 "" 2
 #NO_APP
	sw	$2,16($fp)
	lw	$2,16($fp)
	bne	$2,$0,$L6
	j	$L3
$L6:
	lui	$2,%hi($LC2)
	addiu	$4,$2,%lo($LC2)
	jal	puts
	move	$sp,$fp
	lw	$31,36($sp)
	lw	$fp,32($sp)
	addiu	$sp,$sp,40
	j	$31
	.end	lock
	.size	lock, .-lock
	.rdata
	.align	2
$LC3:
	.ascii	"Soltei o lock\000"
	.text
	.align	2
	.globl	unlock
	.set	nomips16
	.ent	unlock
	.type	unlock, @function
unlock:
	.frame	$fp,24,$31		# vars= 0, regs= 2/0, args= 16, gp= 0
	.mask	0xc0000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-24
	sw	$31,20($sp)
	sw	$fp,16($sp)
	move	$fp,$sp
	sw	$4,24($fp)
	lw	$2,24($fp)
	sw	$0,0($2)
	lui	$2,%hi($LC3)
	addiu	$4,$2,%lo($LC3)
	jal	puts
	nop

	move	$sp,$fp
	lw	$31,20($sp)
	lw	$fp,16($sp)
	addiu	$sp,$sp,24
	j	$31
	nop

	.set	macro
	.set	reorder
	.end	unlock
	.size	unlock, .-unlock
	.rdata
	.align	2
$LC4:
	.ascii	"Hi from processor PowerPC %d!\012\000"
	.text
	.align	2
	.globl	RecursiveHello
	.set	nomips16
	.ent	RecursiveHello
	.type	RecursiveHello, @function
RecursiveHello:
	.frame	$fp,24,$31		# vars= 0, regs= 2/0, args= 16, gp= 0
	.mask	0xc0000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-24
	sw	$31,20($sp)
	sw	$fp,16($sp)
	move	$fp,$sp
	sw	$4,24($fp)
	sw	$5,28($fp)
	lw	$2,24($fp)
	beq	$2,$0,$L8
	nop

	lui	$2,%hi($LC4)
	addiu	$4,$2,%lo($LC4)
	lw	$5,28($fp)
	jal	printf
	nop

	lw	$2,24($fp)
	addiu	$2,$2,-1
	move	$4,$2
	lw	$5,28($fp)
	jal	RecursiveHello
	nop

$L8:
	move	$sp,$fp
	lw	$31,20($sp)
	lw	$fp,16($sp)
	addiu	$sp,$sp,24
	j	$31
	nop

	.set	macro
	.set	reorder
	.end	RecursiveHello
	.size	RecursiveHello, .-RecursiveHello
	.rdata
	.align	2
$LC5:
	.ascii	"Come\303\247ou essa bagaca\000"
	.text
	.align	2
	.globl	main
	.set	nomips16
	.ent	main
	.type	main, @function
main:
	.frame	$fp,32,$31		# vars= 8, regs= 2/0, args= 16, gp= 0
	.mask	0xc0000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-32
	sw	$31,28($sp)
	sw	$fp,24($sp)
	move	$fp,$sp
	sw	$4,32($fp)
	sw	$5,36($fp)
	lw	$2,%gp_rel(procCounter)($28)
	sw	$2,%gp_rel(procN)($28)
	lw	$2,%gp_rel(procCounter)($28)
	addiu	$2,$2,1
	sw	$2,%gp_rel(procCounter)($28)
	lui	$2,%hi($LC5)
	addiu	$4,$2,%lo($LC5)
	jal	puts
	nop

	lw	$2,%gp_rel(lock_aux)($28)
	move	$4,$2
	jal	lock_init
	nop

	lw	$2,%gp_rel(lock_aux)($28)
	li	$3,1			# 0x1
	sw	$3,0($2)
	sw	$0,16($fp)
	j	$L11
	nop

$L12:
	lw	$2,16($fp)
	addiu	$2,$2,1
	sw	$2,16($fp)
$L11:
	lw	$2,16($fp)
	slt	$2,$2,1000
	bne	$2,$0,$L12
	nop

	lw	$2,%gp_rel(lock_aux)($28)
	move	$4,$2
	jal	lock
	nop

	lw	$2,%gp_rel(procCounter)($28)
	sw	$2,%gp_rel(procN)($28)
	lw	$2,%gp_rel(procCounter)($28)
	addiu	$2,$2,1
	sw	$2,%gp_rel(procCounter)($28)
	lw	$2,%gp_rel(procN)($28)
	li	$4,10			# 0xa
	move	$5,$2
	jal	RecursiveHello
	nop

	lw	$2,%gp_rel(lock_aux)($28)
	move	$4,$2
	jal	unlock
	nop

	move	$4,$0
	jal	exit
	nop

	.set	macro
	.set	reorder
	.end	main
	.size	main, .-main
	.ident	"GCC: (GNU) 4.8.2"
