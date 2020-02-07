`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    23:44:18 07/28/2019 
// Design Name: 
// Module Name:    reg_e 
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
module reg_e(
	 input clk,
	 input reset,
	 input [31:0] Instr_D,
	 input [4:0] RD_D,
	 input [31:0] RF_RD1,
	 input [31:0] RF_RD2,
	 input [31:0] PC_D,
	 input [31:0] EXT,
	 output reg [31:0] Instr_E,
	 output reg [31:0] RF_RD1_E,
	 output reg [31:0] RF_RD2_E,
	 output reg [4:0] RS_E,
	 output reg [4:0] RT_E,
	 output reg [4:0] RD_E,
	 output reg [31:0] Extended,
	 output reg [31:0] PC_E
	 );

wire [4:0] RS, RT;
assign RS = Instr_D[25:21];
assign RT = Instr_D[20:16];

initial begin
	{Instr_E, RF_RD1_E, RF_RD2_E, RS_E, RT_E, RD_E, Extended} = 0;
	PC_E = 32'h0000_3000;
end

always @ (posedge clk) begin
	if(reset) begin
		PC_E 			<= 32'h0000_3000;
		Instr_E     <= 0;
		Extended 	<= 0;
		RF_RD1_E    <= 0;
		RF_RD2_E    <= 0;
		RS_E     	<= 0;
		RT_E     	<= 0;
		RD_E     	<= 0;
	end
	else begin
		PC_E 			<= PC_D;
		Instr_E     <= Instr_D;
		Extended 	<= EXT;
		RF_RD1_E    <= RF_RD1;
		RF_RD2_E    <= RF_RD2;
		RS_E     	<= RS;
		RT_E     	<= RT;
		RD_E     	<= RD_D;
	end
end

endmodule