`timescale 1ns / 1ps

`define opcode 31:26
`define func 	5:0
`define rs 		25:21
`define rt 		20:16
`define rd 		15:11
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    00:06:03 07/29/2019 
// Design Name: 
// Module Name:    hazard 
// Project Name: 
// Target Devices: 
// Tool versions: 
// Description: 
//
// Dependencies: 
//
// Revision: 
// Revision 0.01 - File Created
// Additional Comments: 
//
//////////////////////////////////////////////////////////////////////////////////
module hazard(
	 input [31:0] ir,
	 input [1:0] TnewSrc,
	 output [1:0] Tuse_rs,
	 output [1:0] Tuse_rt,
	 output [1:0] Tnew,
	 output [2:0] Tnew_i
	 );
	 
parameter 	ADD	 = 6'b100000,
				ADDU 	 = 6'b100001,
				AND	 = 6'b100100,
				NOR	 = 6'b100111,
				OR		 = 6'b100101,
				SLL	 = 6'b000000,
				SLLV	 = 6'b000100,
				SLT	 = 6'b101010,
				SLTU	 = 6'b101011,
				SRA	 = 6'b000011,
				SRAV	 = 6'b000111,
				SRL	 = 6'b000010,
				SRLV	 = 6'b000110,
				SUB	 = 6'b100010,
				SUBU 	 = 6'b100011,
				XOR	 = 6'b100110,
				
				ADDI	 = 6'b001000,
				ADDIU	 = 6'b001001,
				ANDI	 = 6'b001100,
				ORI    = 6'b001101,
				LUI    = 6'b001111,
				SLTI	 = 6'b001010,
				SLTIU	 = 6'b001011,
				XORI	 = 6'b001110,
				
				LB		 = 6'b100000,
				LBU	 = 6'b100100,
				LH		 = 6'b100001,
				LHU	 = 6'b100101,
				LW     = 6'b100011,
				
				SB		 = 6'b101000,
				SH		 = 6'b101001,
				SW     = 6'b101011,
				
				BEQ    = 6'b000100,
				BNE	 = 6'b000101,
				BGEZ	 = 6'b000001,
				BGEZAL = 6'b000001, //not added yet
				BGTZ	 = 6'b000111,
				BLEZ	 = 6'b000110,
				BLTZ	 = 6'b000001,
				BLTZAL = 6'b000001, //not added yet
				JAL    = 6'b000011,
				J      = 6'b000010,
				JR		 = 6'b001000,
				JALR	 = 6'b001001,
			
				REV	 = 6'b010100,
				CLZO	 = 6'b011100; //CLZ will have 5:0 100000 while CLO 100001

wire [5:0] Op, Func;
wire [4:0] Special;
wire [1:0] Tnew_E, Tnew_M, Tnew_W;
wire b, b_nort, bal, clzo, cal_r, cal_i, j, jr, jalr, jal, load, store;

assign Op = ir[31:26];
assign Func = ir[5:0];
assign Special = ir[20:16];
				
assign b			= (Op == BEQ)	|	(Op == BNE);
assign b_nort	= ((Op == BGEZ) & (Special == 5'b00001))	|	((Op == BGTZ) & (Special == 0))			|	
					  ((Op == BLEZ) & (Special == 0))			|	((Op == BLTZ) & (Special == 0));
assign bal		= ((Op == BGEZAL) & (Special == 5'b10001));

assign j			= (Op == J);
assign jr     	= (Op == 0)	& (Func == JR);
assign jalr   	= (Op == 0)	& (Func == JALR);
assign jal    	= (Op == JAL);

assign cal_r 	= (Op == 0) & ((Func == ADD)	|	(Func == ADDU)	|	(Func == AND)	|	(Func == NOR)	|	(Func == OR)	|	
									   (Func == SLL)	|	(Func == SLLV)	|	(Func == SLT)	|	(Func == SLTU)	|	(Func == SRA)	|	
										(Func == SRAV)	|	(Func == SRL)	|	(Func == SRLV)	|	(Func == SUB)	|	(Func == SUBU)	|	
										(Func == XOR));
assign clzo		= ((Op == CLZO) & ((Func == 6'b100000) | (Func == 6'b100001)));

assign cal_i 	= (Op == ADDI)	|	(Op == ADDIU)	|	(Op == ANDI)	|	(Op == ORI)	|	(Op == LUI)	|
					  (Op == SLTI)	|	(Op == SLTIU)	|	(Op == XORI);
assign load   	= (Op == LB)	|	(Op == LBU)	|	(Op == LH)		|	(Op == LHU)		|	(Op == LW);
assign store	= (Op == SB) 	|	(Op == SH)	|	(Op == SW);


assign Tnew_E	= (cal_r | clzo)	? 1 : 
					  (cal_i)			? 2 : 3;
assign Tnew_M	= (cal_r | clzo) 	? 0 : 
					  (cal_i) 			? 1 : 2;
assign Tnew_W	= 0;


assign Tuse_rs	= (b | b_nort | bal | jr | jalr) 			? 0 :
					  (clzo | cal_r | cal_i | load | store) 	? 1 : 3;

assign Tuse_rt	= (b)			? 0 :
					  (cal_r) 	? 1 :
					  (store)	? 2 : 3;
					  
assign Tnew		= (TnewSrc == 0)	? Tnew_E :
					  (TnewSrc == 1)	? Tnew_M : Tnew_W;
					  
assign Tnew_i	=  (jal|bal)		? 5 :
						(load)			? 4 :
						(store)			? 3 : 
						(cal_r|clzo)	? 2 :
						(cal_i)			? 1 : 0;

endmodule