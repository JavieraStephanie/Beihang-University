.data
	testarr: .space 8
	k: .space 8
	# addu, subu, ori, lui, lw, sw, beq, jal, jr, j, nop
.text
addu $t1, $0, 00000000
clz $t0, $t1
clo $t0, $t1

addu $t1, $0, 00000001
clz $t0, $t1
clo $t0, $t1

subu $t1, $t1, 00000002
bgezal $t1, TEMP

addu $t1, $0, 00010001
clz $t0, $t1
clo $t0, $t1

addu $t1, $0, 0x00003098
jal TEMP

addu $t1, $0, 10000000
clz $t0, $t1
clo $t0, $t1

addu $t1, $0, 11111111
clz $t0, $t1
clo $t0, $t1

addu $t1, $0, 11110111
clz $t0, $t1
clo $t0, $t1

TEMP:
addu $t1, $0, 123456789
sb $t1, k($0)
sh $t1, k($0)
lb $t0, k($0)
lh $t0, k($0)
jr $ra

addu $t1, $0, 0
sb $t1, k($0)
sh $t1, k($0)
lb $t0, k($0)
lh $t0, k($0)

addu $t1, $0, 111111
sb $t1, k($0)
sh $t1, k($0)
lb $t0, k($0)
lh $t0, k($0)

addu $t1, $0, 999999
sb $t1, k($0)
sh $t1, k($0)
lb $t0, k($0)
lh $t0, k($0)

addu $t1, $0, -1
sb $t1, k($0)
sh $t1, k($0)
lb $t0, k($0)
lh $t0, k($0)

SKIP:
ori $gp, $zero, 0x0000
ori $sp, $zero, 0x0000
ori $at, $zero, 0x3456
addu $at, $at, $at

subu $t6, $t6, 1
bgez $t6, next
add $t5, $at, $at
lw $at, 0x0004
sw $at, 0x0004
lui $v0, 0x7878
subu $v1, $v0, $at
lui $a1, 0x1234

next:
bgez $zero, procedure

lw $at, 0x0004
sw $at, 0x0004
lui $v0, 0x7878
subu $v1, $v0, $at
lui $a1, 0x1234
ori $a0, $zero, 0x0005
nop
lui $v0, 0x8723
nop
ori $a3, $v1, 0x0404
nop
lui $t0, 0x7777
addu $at, $at, $v0
lw $at, 0x0000
ori $t0, $t0, 0xffff
addu $t1, $at, $v1
subu $zero, $zero, $t0
ori $zero, $zero, 0x1100
lw $t2, 0x0000
addu $t2, $a3, $t2
ori $at, $a3, 0x1010
sw $at, 0x0000
ori $t0, $zero, 0x0000
ori $t1, $zero, 0x0001
ori $t2, $zero, 0x0001
addu $t0, $t0, $t2
subu $zero, $0, $t0

nop
lui $t0, 0x1234  
ori $t1, $t0, 0x0001 	
lui $t0, 0x0000
ori $t1, $t0, 0x0000
nop 	
nop

addu $t2, $t1, 3 
subu $t3, $t1, $t2 
nop 

sw $t3, testarr($zero)
beq $t3, $t2, any 		
lw $t3, testarr($zero) 		
nop 	

any: ori $t0, $t0, 0x1010 	

jal procedure
lui $t0, 0x5678
jal end

procedure:
ori $t1, $t0, 0x0009
jr $ra

end:
