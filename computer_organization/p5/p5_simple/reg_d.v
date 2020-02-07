`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    00:43:35 12/05/2019 
// Design Name: 
// Module Name:    reg_d 
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
module reg_d(
	 input clk,
	 input reset,
	 input delay,
	 input [31:0] Instr,
	 input [31:0] PC,
	 output reg [31:0] Instr_D,
	 output reg [31:0] PC_D
	 );
	 
initial begin
	Instr_D  = 0;
	PC_D = 0;
end

always @ (posedge clk) begin
	if(reset) begin
		Instr_D  <= 0;
		PC_D 	 	<= 0;
	end
	else if(delay) begin
		Instr_D  <= Instr_D;
		PC_D 	 	<= PC_D;
	end
	else begin
		Instr_D  <= Instr;
		PC_D 	 	<= PC;
	end
end

endmodule
