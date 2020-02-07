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
	 input [4:0] s,
	 input [4:0] ALUctr,
	 output [31:0] Output
	 );
	
integer i;
reg [7:0] temp, temp2;

parameter	ADD 	= 5'b0,		//0
				SUB 	= 5'b00001,	//1
				OR		= 5'b00010,	//2
				NOR	= 5'b00011,	//3
				XOR	= 5'b00100,	//4
				AND	= 5'b00101,	//5
				SLL	= 5'b00110,	//6
				SLLV	= 5'b00111,	//7
				SRL	= 5'b01000,	//8
				SRLV	= 5'b01001,	//9
				SLT	= 5'b01010,	//10
				SLTU	= 5'b01011,	//11
				SRA	= 5'b01100,	//12
				SRAV	= 5'b01101,	//13
				REV	= 5'b01110,	//14
				CLZ	= 5'b01111,	//15
				CLO	= 5'b10000; //16

always @ (*)	begin
	temp <= 32;
	temp2 <= 32;
	
	for (i = 31; i >= 0; i = i - 1)	begin
		if	(A[i] == 1)	begin
			temp <= 31 - i;
			i = -1; //instead of break
		end
	end
	for (i = 31; i >= 0; i = i - 1)	begin
		if (A[i] == 0)	begin
			temp2 <= 31 - i;
			i = -1; //instead of break
		end
	end
end
		
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
						(ALUctr == CLZ)	? temp				:
						(ALUctr == CLO)	? temp2				:
						0;
						
endmodule