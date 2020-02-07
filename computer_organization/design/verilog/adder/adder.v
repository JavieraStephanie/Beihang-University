`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    02:23:13 10/26/2017 
// Design Name: 
// Module Name:    adder 
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
module adder(
    input [3:0] A,
    input [3:0] B,
    input Clk,
    input En,
    output [3:0] Sum,
    output Overflow
    );
	 
	reg [3:0] a_input; 
	reg [3:0] b_input;
	
	assign {Overflow, Sum} = a_input + b_input;
	
	always @(posedge Clk)begin
		if(En) begin
			a_input <= A;
			b_input <= B;
		end
	end


endmodule
