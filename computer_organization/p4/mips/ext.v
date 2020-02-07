`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    03:26:56 07/19/2019 
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
    input extop,
    output [31:0] Output,
	 output [31:0] Shifted,
	 output [31:0] Shifted2
    );

assign Output = (extop == 0) ? {{16{offset[15]}}, offset} : {{16'b0}, offset};
assign Shifted = {{14{offset[15]}}, offset, 2'b0};
assign Shifted2 = {offset, {16'b0}};

endmodule
