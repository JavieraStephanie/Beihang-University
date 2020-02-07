`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    17:00:47 07/18/2019 
// Design Name: 
// Module Name:    ctrl 
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
module ctrl(
    input [5:0] funct,
    input [5:0] opcode,
    output [1:0] RegDst,
    output ALUSrc,
    output [1:0] MemtoReg,
    output RegWrite,
    output MemWrite,
    output [1:0] nPC_sel,
    output ExtOP,
    output [1:0] ALUctr
    );

reg [1:0] regdst;
reg alusrc;
reg [1:0] memtoreg;
reg regwrite;
reg memwrite;
reg [1:0] npc_sel;
reg extop;
reg [1:0] aluctr;

parameter 	addu_f 	= 6'b100001,
				subu_f 	= 6'b100011,
				ori		= 6'b001101,
				lw			= 6'b100011,
				sw			= 6'b101011,
				beq		= 6'b000100,
				lui		= 6'b001111,
				jal		= 6'b000011,
				jr_f		= 6'b001000;
				//nop		= 6'b0;

always @ (opcode or funct) begin
	if (opcode == 6'b0) begin
		case (funct)
			addu_f: begin
				regdst = 2'b01;
				alusrc = 0;
				memtoreg = 2'b0;
				regwrite = 1;
				memwrite = 0;
				npc_sel = 2'b0;
				//extop = 1'bx;
				extop = 0;
				aluctr = 2'b0;
			end
			subu_f: begin
				regdst = 2'b01;
				alusrc = 0;
				memtoreg = 2'b0;
				regwrite = 1;
				memwrite = 0;
				npc_sel = 2'b0;
				//extop = 1'bx;
				extop = 0;
				aluctr = 2'b01;
			end			
			jr_f: begin
				regdst = 2'b0;
				alusrc = 0;
				memtoreg = 2'b0;
				regwrite = 0;
				memwrite = 0;
				npc_sel = 2'b11;
				extop = 0;
				aluctr = 2'b0;
			end
			default: begin
				regdst = 2'b0;
				alusrc = 0;
				memtoreg = 2'b0;
				regwrite = 0;
				memwrite = 0;
				npc_sel = 2'b0;
				extop = 0;
				aluctr = 2'b0;
			end
		endcase
	end
	else begin
		case (opcode)
			ori: begin
				regdst = 2'b0;
				alusrc = 1;
				memtoreg = 2'b0;
				regwrite = 1;
				memwrite = 0;
				npc_sel = 2'b0;
				extop = 1;
				aluctr = 2'b10;
			end
			lw: begin
				regdst = 2'b0;
				alusrc = 1;
				memtoreg = 2'b01;
				regwrite = 1;
				memwrite = 0;
				npc_sel = 2'b0;
				extop = 0;
				aluctr = 2'b0;
			end
			sw: begin
				regdst = 2'b0;
				alusrc = 1;
				memtoreg = 2'b0;
				regwrite = 0;
				memwrite = 1;
				npc_sel = 2'b0;
				extop = 0;
				aluctr = 2'b0;
			end
			beq: begin
				regdst = 2'b0;
				alusrc = 0;
				memtoreg = 2'b0;
				regwrite = 0;
				memwrite = 0;
				npc_sel = 2'b01;
				extop = 0;
				aluctr = 2'b0;
			end
			jal: begin
				regdst = 2'b10;
				alusrc = 0;
				memtoreg = 2'b11;
				regwrite = 1;
				memwrite = 0;
				npc_sel = 2'b10;
				extop = 0;
				aluctr = 2'b0;
			end
			lui: begin
				regdst = 2'b0;
				alusrc = 0;
				memtoreg = 2'b10;
				regwrite = 1;
				memwrite = 0;
				npc_sel = 2'b0;
				extop = 0;
				aluctr = 2'b0;
			end
			default: begin
				regdst = 2'b0;
				alusrc = 0;
				memtoreg = 2'b0;
				regwrite = 0;
				memwrite = 0;
				npc_sel = 2'b0;
				extop = 0;
				aluctr = 2'b0;
			end
		endcase
	end
end

assign RegDst 		= regdst;
assign ALUSrc 		= alusrc;
assign MemtoReg	= memtoreg;
assign RegWrite	= regwrite;
assign MemWrite	= memwrite;
assign nPC_sel		= npc_sel;
assign ExtOP		= extop;
assign ALUctr		= aluctr;

endmodule
