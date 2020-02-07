`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    23:50:57 07/28/2019 
// Design Name: 
// Module Name:    reg_m 
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
module reg_m(
	 input clk,
	 input reset,
	 input [31:0] ALURes,
	 input [31:0] ALUB,
	 input [31:0] Instr_E,
	 input [31:0] PC_E,
	 input [4:0] RD_E,
	 output reg [31:0] Instr_M,
	 output reg [31:0] RF_RD2_M,
	 output reg [31:0] AO_M,
	 output reg [4:0] RD_M,
	 output reg [31:0] PC_M
	 );

initial begin
	{Instr_M, RF_RD2_M, AO_M, RD_M}	=	0;
	PC_M		=	32'h0000_3000;
end

always @ (posedge clk) begin
	if(reset) begin
		PC_M    		<= 32'h0000_3000;
		Instr_M     <= 0;
		RF_RD2_M    <= 0;
		AO_M    		<= 0;
		RD_M    		<= 0;
	end
	else begin
		PC_M    		<= PC_E;
		Instr_M     <= Instr_E;
		RF_RD2_M    <= ALUB;
		AO_M    		<= ALURes;
		RD_M    		<= RD_E;
	end
end

endmodule