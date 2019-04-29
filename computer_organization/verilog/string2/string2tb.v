`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer:
//
// Create Date:   23:44:53 12/14/2017
// Design Name:   string2
// Module Name:   D:/HW/JiSuanJiZuCheng/Verilog/string2/string2tb.v
// Project Name:  string2
// Target Device:  
// Tool versions:  
// Description: 
//
// Verilog Test Fixture created by ISE for module: string2
//
// Dependencies:
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
////////////////////////////////////////////////////////////////////////////////

module string2tb;

	// Inputs
	reg clk;
	reg clr;
	reg [7:0] in;

	// Outputs
	wire out;

	// Instantiate the Unit Under Test (UUT)
	string2 uut (
		.clk(clk), 
		.clr(clr), 
		.in(in), 
		.out(out)
	);

	initial begin
		// Initialize Inputs
		clk = 0;
		clr = 0;
		in = "(";
		
		#10 in = "1";
		#10 in = "+";
		#10 in = "2";
		#10 in = ")";
		#10 in = "+";
		#10 in = "2";
		#10 in = "*";
		#10 in = "(";
		#10 in = "2";
		#10 in = "*";
		#10 in = ")";
		#10 in = "1";


	end
   
	always #5 clk = ~clk;
endmodule

