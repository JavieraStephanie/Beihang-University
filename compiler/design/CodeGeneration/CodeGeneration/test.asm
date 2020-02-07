.data
	vars: .space 0
.align 2
.align 1
	str0: .asciiz "Enter a positive integer number: "
	str1: .asciiz "Total digits in number %d is: %d\\n"
.text
	main :
	addi $sp, $sp, -8
	addi $sp, $sp, -8
	addi $t1, $0, 0
	move $s1, $t1
	sw $s1, 12($sp)
	la $a0, str0
	li $v0, 4
	syscall
	li $a0, '\n'
	li $v0, 11
	syscall
	li $v0, 5
	syscall
	sw $v0, 8($sp)
	lw $t0, 8($sp)
	move $s0, $t0
	jal LABEL1
	move $s1, $v1
	sw $s1, 12($sp)
	la $a0, str1
	li $v0, 4
	syscall
	li $a0, '\n'
	li $v0, 11
	syscall
	lw $a0, 8($sp)
	li $v0, 1
	syscall
	li $a0, '\n'
	li $v0, 11
	syscall
	lw $a0, 12($sp)
	li $v0, 1
	syscall
	li $a0, '\n'
	li $v0, 11
	syscall
	lw $ra, 4($sp)
	addi $sp, $sp, 8
	addi $sp, $sp, 8
	jr $ra
	addi $sp, $sp, 8
	j exit
	LABEL1:
	addi $sp, $sp, -8
	addi $sp, $sp, -4
	addi $sp, $sp, -4
	sw $s0, 8($sp)
	sw $ra, 4($sp)
	addi $t0, $0, 0
	move $s0, $t0
	sw $s0, 12($sp)
	lw $t0, 8($sp)
	addi $t1, $0, 0
	ble $t0, $t1, LABEL3
	addi $t4, $0, 1
	add $t2, $t3, $t4
	move $s0, $t2
	sw $s0, 12($sp)
	lw $t1, 8($sp)
	addi $t2, $0, 10
	div $t1, $t2
	mflo $t0
	move $s0, $t0
	jal LABEL1
	b LABEL4
	LABEL3:
	lw $s0, 8($sp)
	lw $ra, 4($sp)
	addi $sp, $sp, 4
	addi $sp, $sp, 12
	jr $ra
	b LABEL4
	LABEL4:
	exit:
