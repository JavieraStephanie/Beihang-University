.data
	true: .asciiz "1"
	false: .asciiz "0"
.text
	li $v0, 5
	syscall
	move $t3, $v0
	
	rem $t1, $t3, 4
	seq $t2, $t1, $zero
	beq $t2, $1, if_dividebyfour
	nop
	rem $t1, $t3, 400
	seq $t2, $t1, $zero
	beq $t2, $1, if_divideby100
	nop
	la $a0, false
	li $v0, 4
	syscall
	j if_dividebyfour_end
	nop
	nop
	
if_dividebyfour:
	rem $t1, $t3, 100
	sne $t2, $t1, $zero
	bne $t2, $zero, if_divideby100
	nop
	rem $t1, $t3, 400
	seq $t2, $t1, $zero
	beq $t2, $1, if_divideby100
	nop
	la $a0, false
	li $v0, 4
	syscall
	j if_divideby100_end
	nop
	nop
	
if_divideby100:
	la $a0, true
	li $v0, 4
	syscall
	nop
	
if_dividebyfour_end:
if_divideby100_end:
