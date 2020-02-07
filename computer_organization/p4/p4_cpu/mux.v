`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    04:23:32 07/19/2019 
// Design Name: 
// Module Name:    mux2_5 
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
module mux3_5(
    input [4:0] a, b,
    input [1:0] select,
    output [4:0] x
    );

wire [4:0] reg31 = 31;

assign x = 	(select == 2'b0) 	? a : 
				(select == 2'b01)	? b :
				(select == 2'b10) ? reg31 :
				a;

endmodule

module mux2_32(
	 input [31:0] a, b,
	 input select,
	 output [31:0] x
	 );

assign x = (select == 0) ? a : b;

endmodule

module mux3_32(
	 input [31:0] a, b, c,
	 input [31:0] pc,
	 input [1:0] select,
	 output [31:0] x
	 );

assign x = 	(select == 2'b00) ? a :
				(select == 2'b01) ? b : 
				(select == 2'b10) ? c :
				(select == 2'b11) ? pc + 4 :
				a;

endmodule