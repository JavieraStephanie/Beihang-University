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
	 input [4:0] a, b, c,
	 input [1:0] select,
	 output [4:0] x
	 );
	 
assign x = 	(select == 2'b0) 	? a :
			(select == 2'b01) 	? b : c;
				
endmodule

module mux3_32(
	 input [31:0] a, b, c,
	 input [1:0] select,
	 output [31:0] x
	 );
	 
assign x = 	(select == 2'b0) 	? a :
			(select == 2'b01) 	? b : c;

endmodule

module mux4_32(
	 input [31:0] a, b, c, d,
	 input [2:0] select,
	 output [31:0] x
	 );
	 
assign x = 	(select == 2'b0) 	? a :
			(select == 2'b01) 	? b :
			(select == 2'b10) 	? c : d;

endmodule

module mux5_32(
	 input [31:0] a, b, c, d, e,
	 input [2:0] select,
	 output [31:0] x
	 );
	 
assign x = 	(select == 3'b0) 	? a :
			(select == 3'b001) 	? b :
			(select == 3'b010) 	? c :
			(select == 3'b011) 	? d : e;

endmodule