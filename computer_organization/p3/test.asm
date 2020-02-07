.data
	testarr: .space 8
	# addu, subu, ori, lui, lw, sw, beq, nop
.text
ori $gp, $zero, 0x0000
ori $sp, $zero, 0x0000
ori $at, $zero, 0x3456
addu $at, $at, $at

subu $t1, $zero, 1
bgez $t1, procedure
nop

sw $at, 0
lbu $t1, 0

addu $t2, $t1, 3 
subu $t3, $t1, $t2
sw $t3, testarr($zero) 
sw $t2, 0x0004($4)
lw $at, testarr($zero)
lbu $t2, testarr($zero)

lui $t1, 0x0000
bgez $t1, procedure

lw $at, 0x0004
sw $at, 0x0004
lui $v0, 0x7878
subu $v1, $v0, $at
lui $a1, 0x1234
ori $a0, $zero, 0x0005
nop
nop
ori $a3, $v1, 0x0404
nop
lui $t0, 0x7777
ori $t0, $t0, 0xffff
subu $zero, $zero, $t0
ori $zero, $zero, 0x1100
addu $t2, $a3, $a2
ori $t0, $zero, 0x0000
ori $t1, $zero, 0x0001
ori $t2, $zero, 0x0001
addu $t0, $t0, $t2

nop
lui $t0, 0x1234  			#Load upper immediate (of high-order 16-bit),write 0x12340000 to $t0
ori $t1, $t0, 0x0001 		#Set $t1 to bitwise OR of $t0 and 0x12340001
lui $t0, 0x0000
ori $t1, $t0, 0x0000
nop 					#Null op
nop

addu $t2, $t1, 3 		#Set $t2 to 0x10000004
subu $t3, $t1, $t2 		#Set $t3 to (ALU operation $t1 - $t2), no overflow (nothing changed)
nop #Null op

sw $t3, testarr($zero) 		#Write $t3’s value to DM[testarr+$zero] 0x10000000
beq $t3, $t2, any 		#ALU checks if GRF[t3]==GRF[t2], if yes then goto any, else PC+4
lw $t3, testarr($zero) 		#Load DM[testarr+$zero] to GRF[t2] 0x10000000
nop 					#Null op

any: ori $t0, $t0, 0x1010 	#Set $t0 to bitwise OR of itself ($t0) and 0x1000001 -> 0x10001010

jal procedure
lui $t0, 0x5678
jal end

procedure:
ori $t1, $t0, 0x0009
jr $ra

end:
