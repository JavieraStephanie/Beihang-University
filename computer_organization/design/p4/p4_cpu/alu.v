`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    03:05:54 07/19/2019 
// Design Name: 
// Module Name:    alu 
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
module alu(
    input [31:0] A,
    input [31:0] B,
    input [1:0] ALUctr,
	 input [2:0] nPC_sel,
    output zero,
    output [31:0] Output
    );

parameter 	addu 	= 2'b0,
				subu 	= 2'b01,
				or_op	= 2'b10;

assign Output = 	(ALUctr == addu)	? (A+B) :
						(ALUctr == subu) 	? (A-B) :
						(ALUctr == or_op)	? (A|B) :
						(A+B);

assign zero = (nPC_sel == 3'b100)	? ({31'b0, A[31]} == 0) : (A == B);

endmodule
