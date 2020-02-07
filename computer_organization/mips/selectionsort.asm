.data
	array: .space 400
	ispace:		.asciiz " "
.text
	li $v0, 5
	syscall
	move $t0, $v0	# input n
	
	move $s0, $zero	# i=0
	subi $t5, $t0, 1	# $t5 = i-1 (then $t5 would be the end address of the array)

input:	li $v0, 5
	syscall
	move $t1, $v0	# input the value to be stored
	
	sll $s1, $s0, 2
	
	sw $t1, array($s1)	# store the input value to the array
	addi $s0, $s0, 1	# i++
	blt $s0, $t0, input	#while i<n
	
	move $s0, $zero		#reset counter i=0
	
sorti:	beq $s0, $t5, end	# if i=n-1, then end the sorting (since sorting only needs to be until one number before the last one)
	
	addi $s2, $s0, 1	# j = i+1
	
	sll $s1, $s0, 2
	
	move $s5, $s1	#min_idx=i (but in address format because it will be used as an address)
	j sortj
	
sortj: 	bge $s2, $t0, swap	# while j<n, else if j >= n, then swap array[min_idx] with array[i]

	sll $s3, $s2, 2
	
	lw $t2, array($s5)	#array[min_idx]
	lw $t3, array($s3)	#array[j]
	blt $t3, $t2, min	#if array[j] < array[min_idx], then swap min_idx with j
	
	addi $s2, $s2, 1	#i++
	j sortj #loop

min:	move $s5, $s3
	addi $s2, $s2, 1
	j sortj
	
swap:	lw $t2, array($s5)
	lw $t3, array($s1)
	
	sw $t3, array($s5)
	sw $t2, array($s1)
	
	addi $s0, $s0, 1
	j sorti
	
end:	move $s0, $zero #restart count i=0

print:	sll $s1, $s0, 2

	lw $t1, array($s1)
	move $a0, $t1
	li $v0, 1
	syscall
	
	la $a0, ispace
	li $v0, 4
	syscall
	addi $s0, $s0, 1 #i++
	bne $s0, $t0, print                
