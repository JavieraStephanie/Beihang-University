.data
	otrue: .asciiz "1"
	ofalse: .asciiz "0"
	array: .space 80
.text
	li $v0, 5
	syscall
	move $t0, $v0 # input N
	
	move $s0, $zero # i

input:	li $v0, 12
	syscall
	move $t1, $v0 # char input
	
	sll $s3, $s0, 2
	
	sll $s4, $s0, 2
	
	sw $t1, array($s3) # store the char in the array at $s3 location
	addi $s0, $s0, 1 # i++
	blt $s0, $t0, input #while i < n
	
	subi $s1, $s0, 1 # j = i-1 (because now i equals to n)
	move $s0, $zero #restart i = 0
	
	rem $s2, $t0, 2
	beq $s2, $0, check2 # if n is even number then use check2, else use check1
	
check1:	sll $s3, $s0, 2
	
	sll $s4, $s1, 2
	
	lw $t2, array($s3) # load array[i]
	lw $t3, array($s4) #load array[j]
	
	beq $t2, $t3, checkcounter1 # if array[i] == array[j] go to checkcounter
	j false # else the output is sure to be false

checkcounter1:	
	beq $s3, $s4, true # if i==j, means it has done checking, then the output is true
	#else, continue checking
	addi $s0, $s0, 1 # i++
	subi $s1, $s1, 1 #j--
	j check1
	
check2: sll $s3, $s0, 2
	
	sll $s4, $s1, 2
	
	lw $t2, array($s3) # load array[i]
	lw $t3, array($s4) # load array[j]
	beq $t2, $t3, checkcounter2 # if array[i]==array[j] go to checkcounter
	j false # else the output is sure to be false
	
checkcounter2: 
	addi $s0, $s0, 1 # i++	
	beq $s0, $s1, true #because it's even number, then we can know it's done checking if i+1=j, then the result would be true
	subi $s1, $s1, 1 # else, j-- and then continue checking
	j check2
	
false: 	la $a0, ofalse
	li $v0, 4
	syscall
	j end
	nop
	
true:	la $a0, otrue
	li $v0, 4
	syscall
	j end
	nop

end:	li $v0, 10
	syscall
