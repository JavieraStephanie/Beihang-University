`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer:
//
// Create Date:   11:20:29 12/15/2017
// Design Name:   string4
// Module Name:   D:/HW/JiSuanJiZuCheng/Verilog/string4/string4tb.v
// Project Name:  string4
// Target Device:  
// Tool versions:  
// Description: 
//
// Verilog Test Fixture created by ISE for module: string4
//
// Dependencies:
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
////////////////////////////////////////////////////////////////////////////////

module string4tb;

	// Inputs
	reg clk;
	reg clr;
	reg [7:0] in;

	// Outputs
	wire out;
	wire [7:0] res;

	// Instantiate the Unit Under Test (UUT)
	string4 uut (
		.clk(clk), 
		.clr(clr), 
		.in(in), 
		.out(out), 
		.res(res)
	);

	initial begin
		// Initialize Inputs
		clk = 0;
		clr = 0;
		in = "1";

		#10 in = "+";
		#10 in = "2";

	end
   
	always #5 clk = ~clk;
endmodule

