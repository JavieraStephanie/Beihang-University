`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    00:44:00 12/05/2019 
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
						
parameter 	ADD	 = 6'b100000,
				ADDU 	 = 6'b100001,
				AND	 = 6'b100100,
				NOR	 = 6'b100111,
				OR		 = 6'b100101,
				SLL	 = 6'b000000,
				SLLV	 = 6'b000100,
				SLT	 = 6'b101010,
				SLTU	 = 6'b101011,
				SRA	 = 6'b000011,
				SRAV	 = 6'b000111,
				SRL	 = 6'b000010,
				SRLV	 = 6'b000110,
				SUB	 = 6'b100010,
				SUBU 	 = 6'b100011,
				XOR	 = 6'b100110,
				
				ADDI	 = 6'b001000,
				ADDIU	 = 6'b001001,
				ANDI	 = 6'b001100,
				ORI    = 6'b001101,
				LUI    = 6'b001111,
				SLTI	 = 6'b001010,
				SLTIU	 = 6'b001011,
				XORI	 = 6'b001110,
				
				LB		 = 6'b100000,
				LBU	 = 6'b100100,
				LH		 = 6'b100001,
				LHU	 = 6'b100101,
				LW     = 6'b100011,
				
				SB		 = 6'b101000,
				SH		 = 6'b101001,
				SW     = 6'b101011,
				
				BEQ    = 6'b000100,
				BNE	 = 6'b000101,
				BGEZ	 = 6'b000001,
				BGEZAL = 6'b000001, //not added yet
				BGTZ	 = 6'b000111,
				BLEZ	 = 6'b000110,
				BLTZ	 = 6'b000001,
				BLTZAL = 6'b000001, //not added yet
				JAL    = 6'b000011,
				J      = 6'b000010,
				JR		 = 6'b001000,
				JALR	 = 6'b001001,
			
				REV	 = 6'b010100;

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
			ADD:	begin
				regdst	=	2'b01;	alusrc	=	0;		memtoreg	=	2'b0;		regwrite	=	1;
				memwrite	=	0;			npc_sel	=	0;		extop		=	2'b0;		aluctr	=	0;
			end
			ADDU:	begin
				regdst	=	2'b01;	alusrc	=	0;		memtoreg	=	2'b0;		regwrite	=	1;
				memwrite	=	0;			npc_sel	=	0;		extop		=	2'b0;		aluctr	=	0;
			end
			AND:	begin
				regdst	=	2'b01;	alusrc	=	0;		memtoreg	=	2'b0;		regwrite	=	1;
				memwrite	=	0;			npc_sel	=	0;		extop		=	2'b0;		aluctr	=	5;
			end
			NOR:	begin
				regdst	=	2'b01;	alusrc	=	0;		memtoreg	=	2'b0;		regwrite	=	1;
				memwrite	=	0;			npc_sel	=	0;		extop		=	2'b0;		aluctr	=	3;
			end
			OR:	begin
				regdst	=	2'b01;	alusrc	=	0;		memtoreg	=	2'b0;		regwrite	=	1;
				memwrite	=	0;			npc_sel	=	0;		extop		=	2'b0;		aluctr	=	2;
			end
			SLL:	begin
				regdst	=	2'b01;	alusrc	=	0;		memtoreg	=	2'b0;		regwrite	=	1;
				memwrite	=	0;			npc_sel	=	0;		extop		=	2'b0;		aluctr	=	6;
			end
			SLLV:	begin
				regdst	=	2'b01;	alusrc	=	0;		memtoreg	=	2'b0;		regwrite	=	1;
				memwrite	=	0;			npc_sel	=	0;		extop		=	2'b0;		aluctr	=	7;
			end
			SLT:	begin
				regdst	=	2'b01;	alusrc	=	0;		memtoreg	=	2'b0;		regwrite	=	1;
				memwrite	=	0;			npc_sel	=	0;		extop		=	2'b0;		aluctr	=	10;
			end
			SLTU:	begin
				regdst	=	2'b01;	alusrc	=	0;		memtoreg	=	2'b0;		regwrite	=	1;
				memwrite	=	0;			npc_sel	=	0;		extop		=	2'b0;		aluctr	=	11;
			end
			SRA:	begin
				regdst	=	2'b01;	alusrc	=	0;		memtoreg	=	2'b0;		regwrite	=	1;
				memwrite	=	0;			npc_sel	=	0;		extop		=	2'b0;		aluctr	=	12;
			end
			SRAV:	begin
				regdst	=	2'b01;	alusrc	=	0;		memtoreg	=	2'b0;		regwrite	=	1;
				memwrite	=	0;			npc_sel	=	0;		extop		=	2'b0;		aluctr	=	13;
			end
			SRL:	begin
				regdst	=	2'b01;	alusrc	=	0;		memtoreg	=	2'b0;		regwrite	=	1;
				memwrite	=	0;			npc_sel	=	0;		extop		=	2'b0;		aluctr	=	8;
			end
			SRLV:	begin
				regdst	=	2'b01;	alusrc	=	0;		memtoreg	=	2'b0;		regwrite	=	1;
				memwrite	=	0;			npc_sel	=	0;		extop		=	2'b0;		aluctr	=	9;
			end
			SUB: begin
				regdst	=	2'b01;	alusrc	=	0;		memtoreg	=	2'b0;		regwrite	=	1;
				memwrite	=	0;			npc_sel	=	0;		extop		=	2'b0;		aluctr	=	1;
			end
			SUBU: begin
				regdst	=	2'b01;	alusrc	=	0;		memtoreg	=	2'b0;		regwrite	=	1;
				memwrite	=	0;			npc_sel	=	0;		extop		=	2'b0;		aluctr	=	1;
			end
			XOR: begin
				regdst	=	2'b01;	alusrc	=	0;		memtoreg	=	2'b0;		regwrite	=	1;
				memwrite	=	0;			npc_sel	=	0;		extop		=	2'b0;		aluctr	=	4;
			end
			JR:	begin
				regdst	=	2'b0;		alusrc	=	0;		memtoreg	=	2'b0;		regwrite	=	0;
				memwrite	=	0;			npc_sel	=	3;		extop		=	2'b0;		aluctr	=	0;
			end
			JALR:	begin
				regdst	=	2'b01;	alusrc	=	0;		memtoreg	=	2'b10;	regwrite	=	1;
				memwrite	=	0;			npc_sel	=	3;		extop		=	2'b0;		aluctr	=	0;
			end
			REV:	begin
				regdst	=	2'b01;	alusrc	=	0;		memtoreg	=	2'b0;		regwrite	=	1;
				memwrite	=	0;			npc_sel	=	0;		extop		=	2'b0;		aluctr	=	14;
			end
			default:	begin
				regdst	=	2'b0;		alusrc	=	0;		memtoreg	=	2'b0;		regwrite	=	0;
				memwrite	=	0;			npc_sel	=	0;		extop		=	2'b0;		aluctr	=	0;
			end
		endcase
	end
	else begin
		case(opcode)
			ADDI:	begin
				regdst	=	2'b0;		alusrc	=	1;		memtoreg	=	2'b0;		regwrite	=	1;
				memwrite	=	0;			npc_sel	=	0;		extop		=	2'b0;		aluctr	=	0;
			end
			ADDIU:	begin
				regdst	=	2'b0;		alusrc	=	1;		memtoreg	=	2'b0;		regwrite	=	1;
				memwrite	=	0;			npc_sel	=	0;		extop		=	2'b0;		aluctr	=	0;
			end
			ANDI:	begin
				regdst	=	2'b0;		alusrc	=	1;		memtoreg	=	2'b0;		regwrite	=	1;
				memwrite	=	0;			npc_sel	=	0;		extop		=	2'b01;	aluctr	=	5;
			end
			LUI:		begin
				regdst	=	2'b0;		alusrc	=	1;		memtoreg	=	2'b0;		regwrite	=	1;
				memwrite	=	0;			npc_sel	=	0;		extop		=	2'b10;	aluctr	=	0;
			end
			ORI:	begin
				regdst	=	2'b0;		alusrc	=	1;		memtoreg	=	2'b0;		regwrite	=	1;
				memwrite	=	0;			npc_sel	=	0;		extop		=	2'b01;	aluctr	=	2;
			end
			SLTI:	begin
				regdst	=	2'b0;		alusrc	=	1;		memtoreg	=	2'b0;		regwrite	=	1;
				memwrite	=	0;			npc_sel	=	0;		extop		=	2'b0;		aluctr	=	10;
			end
			SLTIU:	begin
				regdst	=	2'b0;		alusrc	=	1;		memtoreg	=	2'b0;		regwrite	=	1;
				memwrite	=	0;			npc_sel	=	0;		extop		=	2'b0;		aluctr	=	11;
			end
			XORI:	begin
				regdst	=	2'b0;		alusrc	=	1;		memtoreg	=	2'b0;		regwrite	=	1;
				memwrite	=	0;			npc_sel	=	0;		extop		=	2'b01;	aluctr	=	4;
			end
			LB:	begin
				regdst	=	2'b0;		alusrc	=	1;		memtoreg	=	2'b01;	regwrite	=	1;
				memwrite	=	0;			npc_sel	=	0;		extop		=	2'b0;		aluctr	=	0;
			end
			LBU:	begin
				regdst	=	2'b0;		alusrc	=	1;		memtoreg	=	2'b01;	regwrite	=	1;
				memwrite	=	0;			npc_sel	=	0;		extop		=	2'b0;		aluctr	=	0;
			end
			LH:	begin
				regdst	=	2'b0;		alusrc	=	1;		memtoreg	=	2'b01;	regwrite	=	1;
				memwrite	=	0;			npc_sel	=	0;		extop		=	2'b0;		aluctr	=	0;
			end
			LHU:	begin
				regdst	=	2'b0;		alusrc	=	1;		memtoreg	=	2'b01;	regwrite	=	1;
				memwrite	=	0;			npc_sel	=	0;		extop		=	2'b0;		aluctr	=	0;
			end
			LW:	begin
				regdst	=	2'b0;		alusrc	=	1;		memtoreg	=	2'b01;	regwrite	=	1;
				memwrite	=	0;			npc_sel	=	0;		extop		=	2'b0;		aluctr	=	0;
			end
			SB:	begin
				regdst	=	2'b0;		alusrc	=	1;		memtoreg	=	2'b0;		regwrite	=	0;
				memwrite	=	1;			npc_sel	=	0;		extop		=	2'b0;		aluctr	=	0;
			end
			SH:	begin
				regdst	=	2'b0;		alusrc	=	1;		memtoreg	=	2'b0;		regwrite	=	0;
				memwrite	=	1;			npc_sel	=	0;		extop		=	2'b0;		aluctr	=	0;
			end
			SW:	begin
				regdst	=	2'b0;		alusrc	=	1;		memtoreg	=	2'b0;		regwrite	=	0;
				memwrite	=	1;			npc_sel	=	0;		extop		=	2'b0;		aluctr	=	0;
			end
			BEQ:	begin
				regdst	=	2'b0;		alusrc	=	0;		memtoreg	=	2'b0;		regwrite	=	0;
				memwrite	=	0;			npc_sel	=	1;		extop		=	2'b0;		aluctr	=	0;
			end
			BNE:	begin
				regdst	=	2'b0;		alusrc	=	0;		memtoreg	=	2'b0;		regwrite	=	0;
				memwrite	=	0;			npc_sel	=	4;		extop		=	2'b0;		aluctr	=	0;
			end
			BGEZ:	begin
				if (Instr[20:16] == 5'b00001)	begin
					regdst	=	2'b0;		alusrc	=	0;		memtoreg	=	2'b0;		regwrite	=	0;
					memwrite	=	0;			npc_sel	=	5;		extop		=	2'b0;		aluctr	=	0;
				end
			end
			BGEZAL:	begin
				if (Instr[20:16] == 5'b10001)	begin
					regdst	=	2'b10;	alusrc	=	0;		memtoreg	=	2'b10;	regwrite	=	1;
					memwrite	=	0;			npc_sel	=	5;		extop		=	2'b0;		aluctr	=	0;
				end
			end
			BGTZ:	begin
				regdst	=	2'b0;		alusrc	=	0;		memtoreg	=	2'b0;		regwrite	=	0;
				memwrite	=	0;			npc_sel	=	6;		extop		=	2'b0;		aluctr	=	0;
			end
			BLEZ:	begin
				regdst	=	2'b0;		alusrc	=	0;		memtoreg	=	2'b0;		regwrite	=	0;
				memwrite	=	0;			npc_sel	=	7;		extop		=	2'b0;		aluctr	=	0;
			end
			BLTZ:	begin
				if (Instr[20:16] == 5'b0)	begin
					regdst	=	2'b0;		alusrc	=	0;		memtoreg	=	2'b0;		regwrite	=	0;
					memwrite	=	0;			npc_sel	=	8;		extop		=	2'b0;		aluctr	=	0;
				end
			end
			BLTZAL:	begin
				if (Instr[20:16] == 5'b10000)	begin
					regdst	=	2'b10;	alusrc	=	0;		memtoreg	=	2'b10;	regwrite	=	1;
					memwrite	=	0;			npc_sel	=	8;		extop		=	2'b0;		aluctr	=	0;
				end
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
assign ExtOp     = extop;
assign ALUctr		= aluctr;

endmodule