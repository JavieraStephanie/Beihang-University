`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    00:46:14 12/05/2019 
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
	 input [4:0] s,
	 input [4:0] ALUctr,
	 output [31:0] Output
	 );
	 
parameter	ADD 	= 5'b0,
				SUB 	= 5'b00001,
				OR		= 5'b00010,
				NOR	= 5'b00011,
				XOR	= 5'b00100,
				AND	= 5'b00101,
				SLL	= 5'b00110,
				SLLV	= 5'b00111,
				SRL	= 5'b01000,
				SRLV	= 5'b01001,
				SLT	= 5'b01010,
				SLTU	= 5'b01011,
				SRA	= 5'b01100,
				SRAV	= 5'b01101,
				REV	= 5'b01110;
				
assign Output = 	(ALUctr == ADD)	?	(A + B)			:
						(ALUctr == SUB)	?	(A - B)			:
						(ALUctr == OR)		?	(A | B)			:
						(ALUctr == NOR)	? ~(A | B)			:
						(ALUctr == XOR)	?	(A ^ B)			:
						(ALUctr == AND)	?	(A & B)			:
						(ALUctr == SLL)	?	(B << s)			:
						(ALUctr == SLLV)	?	(B << A[4:0])	:
						(ALUctr == SRL)	?	(B >> s)			:
						(ALUctr == SRLV)	?	(B >> A[4:0])	:
						(ALUctr == SLT)	?	($signed(A) < $signed(B))	:
						(ALUctr == SLTU)	?	({1'b0, A} < {1'b0, B})		:
						(ALUctr == SRA)	?	$signed($signed(B) >>> s)	:
						(ALUctr == SRAV)	?	$signed($signed(B) >>> A[4:0])	:
						(ALUctr == REV)	? ({A[0],A[1],A[2],A[3],A[4],A[5],A[6],A[7],
													 A[8],A[9],A[10],A[11],A[12],A[13],A[14],A[15],
													 A[16],A[17],A[18],A[19],A[20],A[21],A[22],A[23],
													 A[24],A[25],A[26],A[27],A[28],A[29],A[30],A[31]}) : 
						0;


endmodule
