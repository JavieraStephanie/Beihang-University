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
	 input [31:0] Instr,
	 input [5:0] funct,
	 input [5:0] opcode,
	 output [1:0] RegDst,
	 output ALUSrc,
	 output [1:0]MemtoReg,
	 output RegWrite,
	 output MemWrite,
	 output [3:0] nPC_sel,
	 output [1:0] ExtOp,
	 output [4:0] ALUctr
	 );

reg [1:0] regdst;
reg alusrc;
reg [1:0] memtoreg;
reg regwrite;
reg memwrite;
reg [1:0] extop;
reg [3:0] npc_sel;
reg [4:0] aluctr;
						
parameter 	ADDU 	 = 6'b100001,
				SUBU 	 = 6'b100011,
				
				ADDI	 = 6'b001000,
				ORI    = 6'b001101,
				LUI    = 6'b001111,
				
				LW     = 6'b100011,
				
				SW     = 6'b101011,
				
				BEQ    = 6'b000100,
				
				JAL    = 6'b000011,
				J      = 6'b000010,
				JR		 = 6'b001000;

initial begin
	regdst = 2'b0;
	alusrc = 0;
	memtoreg = 2'b0;
	regwrite = 0;
	memwrite = 0;
	npc_sel = 0;
	extop = 2'b0;
	aluctr = 2'b0;
end

always @ (opcode or funct) begin
	if (opcode == 6'b0) begin
		case(funct)
			ADDU:	begin
				regdst	=	2'b01;	alusrc	=	0;		memtoreg	=	2'b0;		regwrite	=	1;
				memwrite	=	0;			npc_sel	=	0;		extop		=	2'b0;		aluctr	=	0;
			end
			SUBU: begin
				regdst	=	2'b01;	alusrc	=	0;		memtoreg	=	2'b0;		regwrite	=	1;
				memwrite	=	0;			npc_sel	=	0;		extop		=	2'b0;		aluctr	=	1;
			end
			JR:	begin
				if (Instr[20:11] == 0)	begin
					regdst	=	2'b0;		alusrc	=	0;		memtoreg	=	2'b0;		regwrite	=	0;
					memwrite	=	0;			npc_sel	=	3;		extop		=	2'b0;		aluctr	=	0;
				end
			end
			default:	begin
				regdst	=	2'b0;		alusrc	=	0;		memtoreg	=	2'b0;		regwrite	=	0;
				memwrite	=	0;			npc_sel	=	0;		extop		=	2'b0;		aluctr	=	0;
			end
		endcase
	end
	else begin
		case(opcode)
			LUI:		begin
				regdst	=	2'b0;		alusrc	=	1;		memtoreg	=	2'b0;		regwrite	=	1;
				memwrite	=	0;			npc_sel	=	0;		extop		=	2'b10;	aluctr	=	0;
			end
			ORI:	begin
				regdst	=	2'b0;		alusrc	=	1;		memtoreg	=	2'b0;		regwrite	=	1;
				memwrite	=	0;			npc_sel	=	0;		extop		=	2'b01;	aluctr	=	2;
			end
			LW:	begin
				regdst	=	2'b0;		alusrc	=	1;		memtoreg	=	2'b01;	regwrite	=	1;
				memwrite	=	0;			npc_sel	=	0;		extop		=	2'b0;		aluctr	=	0;
			end
			SW:	begin
				regdst	=	2'b0;		alusrc	=	1;		memtoreg	=	2'b0;		regwrite	=	0;
				memwrite	=	1;			npc_sel	=	0;		extop		=	2'b0;		aluctr	=	0;
			end
			BEQ:	begin
				regdst	=	2'b0;		alusrc	=	0;		memtoreg	=	2'b0;		regwrite	=	0;
				memwrite	=	0;			npc_sel	=	1;		extop		=	2'b0;		aluctr	=	0;
			end
			JAL:	begin
				regdst	=	2'b10;	alusrc	=	0;		memtoreg	=	2'b10;	regwrite	=	1;
				memwrite	=	0;			npc_sel	=	2;		extop		=	2'b0;		aluctr	=	0;
			end
			J:		begin
				regdst	=	2'b0;		alusrc	=	0;		memtoreg	=	2'b0;		regwrite	=	0;
				memwrite	=	0;			npc_sel	=	2;		extop		=	2'b0;		aluctr	=	0;
			end
			default:	begin
				regdst	=	2'b0;		alusrc	=	0;		memtoreg	=	2'b0;		regwrite	=	0;
				memwrite	=	0;			npc_sel	=	0;		extop		=	2'b0;		aluctr	=	0;
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
assign ExtOp      = extop;
assign ALUctr		= aluctr;

endmodule