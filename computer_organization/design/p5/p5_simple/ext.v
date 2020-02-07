`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    00:45:28 12/05/2019 
// Design Name: 
// Module Name:    ext 
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
module ext(
	 input [15:0] offset,
	 input [1:0] ExtOp,
	 output [31:0] Output,
	 output [31:0] Shifted
	 );
					
assign Output = (ExtOp == 2'b0) 	? {{16{offset[15]}}, offset} :
					 (ExtOp == 2'b01) ? {{16'b0}, offset} :
					 (ExtOp == 2'b10) ? {offset, {16'b0}} :
					 {{14{offset[15]}}, offset, 2'b0};

assign Shifted = {{14{offset[15]}}, offset, 2'b0};
//assign Shifted2 = {offset, {16'b0}};

endmodule
