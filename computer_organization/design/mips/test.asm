.data
	testarr: .space 8
	
.text

lui $t0, 0x1000
ori $t1, $t0, 0x0001
nop

addu $t2, $t1, 3
subu $t3, $t1, 1
nop

sw $t3, testarr($zero)
beq $t3, $t2, any
lw $t3, testarr($zero)
nop

any:	ori $t0, $t0, 0x1010
