`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer:
//
// Create Date:   18:58:17 11/09/2017
// Design Name:   gray
// Module Name:   D:/HW/JiSuanJiZuCheng/Verilog/gray/graytb.v
// Project Name:  gray
// Target Device:  
// Tool versions:  
// Description: 
//
// Verilog Test Fixture created by ISE for module: gray
//
// Dependencies:
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
////////////////////////////////////////////////////////////////////////////////

module graytb;

	// Inputs
	reg Clk;
	reg Reset;
	reg En;

	// Outputs
	wire [2:0] Output;
	wire Overflow;

	// Instantiate the Unit Under Test (UUT)
	gray uut (
		.Clk(Clk), 
		.Reset(Reset), 
		.En(En), 
		.Output(Output), 
		.Overflow(Overflow)
	);

	initial begin
		// Initialize Inputs
		#0 Clk = 0;
			Reset = 0;
			En = 0;
		#100 En = 1;
		#20 Reset = 1;
		#10 Reset = 0;
		#100 Reset = 1;
		#10 Reset = 0;
	end
	always #5 Clk=~Clk;
      
endmodule

