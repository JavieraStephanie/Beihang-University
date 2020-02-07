ori $gp, $zero, 0x0000
ori $sp, $zero, 0x0000
ori $at, $zero, 0x3456
start: addu $at, $at, $at
lw $at, 0x0004
sw $at, 0x0004
lui $v0, 0x7878
subu $v1, $v0, $at
lui $a1, 0x1234
ori $a0, $zero, 0x0005
nothing: nop
sw $a1, 0xFFFF
lw $v1, 0xFFFF
jump: beq $v1, $a1, start
nop
beq $zero, $zero, nothing
nop
ori $a3, $v1, 0x0404
beq $a3, $v1, jump
nop
lui $t0, 0x7777
ori $t0, $t0, 0xFFFF
subu $zero, $zero, $t0
ori $zero, $zero, 0x1100
addu $t2, $a3, $a2
ori $t0, $zero, 0x0000
ori $t1, $zero, 0x0001
ori $t2, $zero, 0x0001
addu $t0, $t0, $t2
beq $t0, $t1, 0xFFFE
jal 0x0000C22
nop
addu $t2, $t2, $t2
beq $zero, $zero, 0xFFFF
addu $t2, $t2, $t2
jr $ra
nop