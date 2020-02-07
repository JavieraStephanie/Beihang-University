.data
	matrix1:	.space 256
	transpose1:	.space 256

.text
	li $v0, 5
	syscall
	move $t0, $v0 # total row number
	
	li $v0, 5
	syscall
	move $t1, $v0 # total column number
	
	move $s0, $zero #current row number
	move $s1, $zero #current column number
	move $s2, $zero #current position in the matrix
	
input:
	li $v0, 5
	syscall
	move $t2, $v0 # value to store
	
	mul $s2, $s0, $t1 # current row * total column
	add $s2, $s2, $s1 # mult result + current column
	sll $s2, $s2, 2   # the true address of the current position
	
	sw $t2, matrix1($s2) # store the value in the current position of the matrix
	
	addi $s1, $s1, 1 # column++
	blt $s1, $t1, input # if column < total column
	
	addi $s0, $s0, 1 # row++
	move $s1, $zero  # reset column counter
	blt $s0, $t0, input # if row < total row
	
	move $s0, $zero
	move $s1, $zero
	move $s2, $zero

print:
	mul $s2, $s0, $t1 # current row * total column
	add $s2, $s2, $s1 # mult result + current column
	sll $s2, $s2, 2   # true address of the current position
	
	lw $a0, matrix1($s2) 
	li $v0, 1
	syscall
	
	li $a0, ' '
	li $v0, 11
	syscall
	
	addi $s1, $s1, 1 # column++
	blt $s1, $t1, print # if column < total column
	
	li $a0, '\n'
	li $v0, 11
	syscall
	
	addi $s0, $s0, 1 # row++
	move $s1, $zero # reset column counter
	blt $s0, $t0, print # if row < total row
	
	move $s0, $zero # row counter matrix1
	move $s1, $zero # column counter matrix1
	move $s2, $zero # true address of current position matrix1
	move $s3, $zero # row counter transpose1
	move $s4, $zero # column counter transpose1
	move $s5, $zero # true address of current position tranpose1
	
switch:
	move $t3, $t1
	move $t4, $t0

transpose:
	mul $s2, $s0, $t1 # current row * total column
	add $s2, $s2, $s1 # mult result + column counter
	sll $s2, $s2, 2   # true address of the current position matrix1
	
	mul $s5, $s3, $t4 # current row * total column
	add $s5, $s5, $s4 # mult result + column counter
	sll $s5, $s5, 2   # true address of the current position transpose1
	
	lw $a0, matrix1($s2)
	sw $a0, transpose1($s5)
	
	addi $s4, $s4, 1 # column++ transpose1
	addi $s0, $s0, 1 # row++ matrix1
	blt $s4, $t4, transpose # if column < total column transpose1
	
	addi $s1, $s1, 1 # column++ matrix1
	move $s0, $zero  # reset row counter matrix1
	
	addi $s3, $s3, 1 # row++ transpose1
	move $s4, $zero  # reset column counter transpose1
	
	blt $s3, $t3, transpose # if row < total row transpose1
end:	li $v0, 10
	syscall