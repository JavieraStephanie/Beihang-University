.data
	count:	.space 256
	string:	.space 256
.text
	li $v0, 5
	syscall
	move $t0, $v0
	
	move $s0, $zero # i = 0
	
input:
	li $v0, 12
	syscall
	move $t1, $v0 # char input
	
	sll $s2, $s0, 2 # true address of string
	
	sw $t1, string($s2) # store char
	
	addi $s0, $s0, 1 # i++
	
	blt $s0, $t0, input # if i < string length
	
	move $s0, $zero  # i=0
	
sort:
	
	
	