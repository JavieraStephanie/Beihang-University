`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    03:36:51 07/19/2019 
// Design Name: 
// Module Name:    ifu 
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
module pc(
    input clk,
    input reset,
    input [31:0] nPC,
    output reg [31:0] PC
    );

initial begin
	PC <= 32'h0000_3000;
end

always @ (posedge clk) begin
	if(reset) PC <= 32'h0000_3000;
	else				PC <= nPC;
end

endmodule

module im(
	input [9:0] PC,
	output [31:0] Instr
	);

reg [31:0] mem [1023:0];
integer i;

initial begin
	for (i = 0; i < 1024; i = i+1)
		mem[i] = 32'h0;
	$readmemh("code.txt", mem);
end

assign Instr = mem[PC];

endmodule

module npc(
	input [31:0] Instr,
	input [31:0] RData1,
	input [31:0] Shifted,
	input [2:0] nPC_sel,
	input zero,
	input [31:0] pc,
	output [31:0] nPC
	);

assign nPC = 	(nPC_sel == 3'b0) 					? pc + 4 : 
					(nPC_sel == 3'b001 && zero)		? pc + 4 + Shifted :
					(nPC_sel == 3'b010)					? {pc[31:28], Instr[25:0], 2'b0} :
					(nPC_sel == 3'b011)					? RData1 :
					(nPC_sel == 3'b100 && zero)		? pc + 4 + Shifted :
					pc + 4;
endmodule