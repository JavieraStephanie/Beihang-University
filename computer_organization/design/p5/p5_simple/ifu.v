`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    00:43:05 12/05/2019 
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
	 input delay,
	 input [31:0] nPC,
	 output reg [31:0] PC
	 );
	 
initial begin
	PC <= 32'h0000_3000;
end

always @ (posedge clk) begin
	if(reset)		PC <= 32'h0000_3000;
	else if(delay)	PC <= PC;
	else 				PC <= nPC;
end

endmodule

module im(
	 input [9:0] PC,
	 output [31:0] Instr
	 );

	reg [31:0] mem [1023:0];
	integer i;
	
initial begin
	for(i = 0; i < 1024; i = i + 1)
		mem[i] = 32'h0;
	$readmemh("code.txt", mem);
end

assign Instr = mem[PC];

endmodule

module npc(
	 input [31:0] Instr,
	 input [31:0] PC,
	 input [31:0] PC_D,
	 input [31:0] rs,
	 input eq, gez, gtz, lez, ltz,
	 input [3:0] nPC_sel,
	 input [31:0] Shifted,
	 output [31:0] npc
	 );
	
	assign npc =	(nPC_sel == 0)				? PC + 4 :
						(nPC_sel == 1 && eq)		? PC_D + 4 + Shifted :					 //beq
						(nPC_sel == 4 && ~eq)	? PC_D + 4 + Shifted :					 //bne
						(nPC_sel == 5 && gez)	? PC_D + 4 + Shifted :					 //bgez, bgezal
						(nPC_sel == 6 && gtz)	? PC_D + 4 + Shifted :					 //bgtz
						(nPC_sel == 7 && lez)	? PC_D + 4 + Shifted :					 //blez
						(nPC_sel == 8 && ltz)	? PC_D + 4 + Shifted :					 //bltz, bltzal
						(nPC_sel == 2)				? {PC_D[31:28], Instr[25:0], 2'b0} : //j
						(nPC_sel == 3)				? rs :										 //jr, jal
						PC_D + 8;
						
endmodule
