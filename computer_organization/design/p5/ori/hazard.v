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
	 
parameter 	ADDU 	 = 6'b100001,
				SUBU 	 = 6'b100011,
				
				ORI    = 6'b001101,
				LUI    = 6'b001111,
				
				LW     = 6'b100011,
				
				SW     = 6'b101011,
				
				BEQ    = 6'b000100,
				
				JAL    = 6'b000011,
				J      = 6'b000010,
				JR		 = 6'b001000;

wire [5:0] Op, Func;
wire [4:0] Special;
wire [1:0] Tnew_E, Tnew_M, Tnew_W;
wire b, b_nort, bal, clzo, cal_r, cal_i, j, jr, jalr, jal, load, store;

assign Op = ir[31:26];
assign Func = ir[5:0];
assign Special = ir[20:16];
				
assign b			= (Op == BEQ);

assign j			= (Op == J);
assign jr     	= (Op == 0)	& (Func == JR);
assign jal    	= (Op == JAL);

assign cal_r 	= (Op == 0) & ((Func == ADDU)	|	(Func == SUBU));

assign cal_i 	= (Op == ORI)	|	(Op == LUI);
assign load   	= (Op == LW);
assign store	= (Op == SW);


assign Tnew_E	= (cal_r)	? 1 : 
					  (cal_i)	? 2 : 3;
assign Tnew_M	= (cal_r) 	? 0 : 
					  (cal_i) 	? 1 : 2;
assign Tnew_W	= 0;


assign Tuse_rs	= (b | jr | jalr) 			? 0 :
					  (cal_r | cal_i | load | store) 	? 1 : 3;

assign Tuse_rt	= (b)			? 0 :
					  (cal_r) 	? 1 :
					  (store)	? 2 : 3;
					  
assign Tnew		= (TnewSrc == 0)	? Tnew_E :
					  (TnewSrc == 1)	? Tnew_M : Tnew_W;
					  
assign Tnew_i	=  (jal)				? 5 :
						(load)			? 4 :
						(store)			? 3 : 
						(cal_r)			? 2 :
						(cal_i)			? 1 : 0;

endmodule