`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    03:05:54 07/19/2019 
// Design Name: 
// Module Name:    comp 
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
module comp(
	 input [31:0] A,
	 input [31:0] B,
	 output eq,
	 output gez,
	 output gtz,
	 output lez,
	 output ltz
	 );

assign eq 	= (A == B);
//assign gez 	= (A == 0 || A[31] == 0);
assign gez	= ($signed(A) >= 0);
//assign gtz	= (A != 0 && A[31] == 0);
assign gtz	= ($signed(A) > 0);
//assign lez 	= (A == 0 || A[31] == 1);
assign lez	= ($signed(A) <= 0);
//assign ltz	= (A != 0 && A[31] == 1);
assign ltz	= ($signed(A) < 0);

endmodule