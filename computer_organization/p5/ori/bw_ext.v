`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    04:32:43 08/02/2019 
// Design Name: 
// Module Name:    bw_ext 
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
module bw_ext(
	 input [31:0] DMRes,
	 input [1:0] Addr,
	 input [5:0] loadOp,
	 output reg [31:0] BWExt
    );
				
always @ (*) begin
	BWExt = DMRes;
end


endmodule
