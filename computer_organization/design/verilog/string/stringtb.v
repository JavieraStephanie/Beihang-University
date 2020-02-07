`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer:
//
// Create Date:   00:17:25 11/17/2017
// Design Name:   string
// Module Name:   D:/HW/JiSuanJiZuCheng/Verilog/string/stringtb.v
// Project Name:  string
// Target Device:  
// Tool versions:  
// Description: 
//
// Verilog Test Fixture created by ISE for module: string
//
// Dependencies:
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
////////////////////////////////////////////////////////////////////////////////

module stringtb;

	// Inputs
	reg clk;
	reg clr;
	reg [7:0] in;

	// Outputs
	wire out;

	// Instantiate the Unit Under Test (UUT)
	string uut (
		.clk(clk), 
		.clr(clr), 
		.in(in), 
		.out(out)
	);

	initial begin
		// Initialize Inputs
		clk = 0;
		clr = 0;
		in = 0;

		// Wait 100 ns for global reset to finish
		#0 in = "1";
		#10 in = "+";
		#10 in = "2";
		#10 in = "*";
		#10 in = "3";
		#40 in = "1";
		#10 in = "*";
		#10 clr= 1;
			 in = "2";
		#10 in = "+";
		#10 in = "3";
				
	end
	always #5 clk = ~clk;
      
endmodule

