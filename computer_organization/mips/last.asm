.data
	array: .space 28
	symbol:.space 28
.text
	li $v0, 5
	syscall
	move $t0, $v0
	
	move $s0, $t0 #n
	move $s1, $zero #index
	move $s2, $zero #i=0
	j fullarray

fullarray:
	bge $s1, $s0, print #if index is larger or equal to n, go to print loop
	j always

print:
	move $s2, $zero #i=0
	j print2

print2:
	bge $s2, $s0, always #if i>=n, else go to the always loop
	
	sll $s3, $s2, 2
	
	lw $t0, array($s3)
	
	move $a0, $t0
	li $v0, 1
	syscall
	
	li $a0, ' '
	li $v0, 11
	syscall
	
	addi $s2, $s2, 1 #i++
	blt $s2, $s0, print2 #while i<n
	
	li $a0, '\n'
	li $v0, 11
	syscall
	
	jr $ra
	
always:
	move $s2, $zero #i=0
	j always2

always2:
	bge $s2, $s0, end #while i<n
	
	sll $s3, $s2, 2
	
	lw $t0, symbol($s3) #load symbol of the current array number
	beq $t0, $zero, storearray #store array value
	addi $s2, $s2, 1 #i++
	blt $s2, $s0, always2
	
	jr $ra
	
storearray:
	sll $s4, $s1, 2
	
	addi $t2, $s2, 1 #set array number to i+1
	sw $t2, array($s4)
	
	addi $t2, $zero, 1
	sw $t2, symbol($s3) #set the symbol of the current array number to 1
	
	sub $sp, $sp, 12
	sw $ra, 0($sp) #save $ra
	sw $s1, 4($sp) #save index
	sw $s2, 8($sp) #save i
	
	addi $s1, $s1, 1 #index + 1
	
	jal fullarray	
	
	lw $s1, 4($sp) #load index
	lw $s2, 8($sp) #load i
	lw $ra, 0($sp) #load address
	add $sp, $sp, 12
	
	sll $s4, $s1, 2
	
	sll $s3, $s2, 2
	
	sw $zero, symbol($s3) #set the symbol of current array number to 0
	addi $s2, $s2, 1 #i++
	blt $s2, $s0, always2
	beq $s1, $zero, end
	jr $ra
	
end: