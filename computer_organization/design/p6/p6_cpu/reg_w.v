`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    23:57:13 07/28/2019 
// Design Name: 
// Module Name:    reg_w 
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
module reg_w(
	 input clk,
	 input reset,
	 input [31:0] Instr_M,
	 input [4:0] RD_M,
	 input [31:0] AO_M,
	 input [31:0] PC_M,
	 input [31:0] DMRes,
	 output reg [31:0] Instr_W,
	 output reg [4:0] RD_W,
	 output reg [31:0] PC_W,
	 output reg [31:0] AO_W,
	 output reg [31:0] DR_W
	 );
	
initial begin
	{Instr_W, RD_W, AO_W, DR_W} = 0;
	PC_W = 32'h0000_3000;
end

always @ (posedge clk) begin
	if(reset) begin
		PC_W    	<= 32'h0000_3000;
		Instr_W  <= 0;
		RD_W    	<= 0;
		AO_W    	<= 0;
		DR_W    	<= 0;
	end
	else begin
		PC_W    	<= PC_M;
		Instr_W  <= Instr_M;
		RD_W    	<= RD_M;
		AO_W    	<= AO_M;
		DR_W    	<= DMRes;
	end
end

endmodule