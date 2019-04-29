`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    23:57:00 10/26/2017 
// Design Name: 
// Module Name:    buffer 
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
module buffer(
    input clk,
    input in,
    output reg out = 0
    );
	 reg buff = 0;
	 always @(posedge clk) begin
		buff <= in;
		out = buff;
	 end
endmodule

module buffer_tb;

	reg clk;
	reg in;
	
	wire out;
	
	buffer uut (
		.clk(clk),
		.in(in),
		.out(out)
	);
	initial begin
	
		clk <= 1;
		in <= 0;
		#10;
		in = 1;
		#10;
		in = 0;
		#10
		in = 1;
	end
	always #5 clk = ~clk;
	
endmodule
