`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    03:57:44 07/29/2019 
// Design Name: 
// Module Name:    mips 
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
module mips(
	 input clk,
	 input reset
	 );
 
// Signal Variables
wire [4:0] ALUctr_D;
wire [3:0] nPC_sel_D;
wire [1:0] RegDst_D, MemtoReg_D, ExtOp_D;
wire ALUSrc_D, RegWrite_D, MemWrite_D;

wire [4:0] ALUctr_E;
wire [3:0] nPC_sel_E;
wire [1:0] RegDst_E, MemtoReg_E, ExtOp_E;
wire ALUSrc_E, RegWrite_E, MemWrite_E;

wire [4:0] ALUctr_M, WriteReg;
wire [3:0] nPC_sel_M;
wire [1:0] RegDst_M, MemtoReg_M, ExtOp_M;
wire ALUSrc_M, RegWrite_M, MemWrite_M;

wire [4:0] ALUctr_W;
wire [3:0] nPC_sel_W;
wire [1:0] RegDst_W, MemtoReg_W, ExtOp_W;
wire ALUSrc_W, RegWrite_W, MemWrite_W;
// ~Signal Variables

// Instructions
wire [31:0] Instr, Instr_D, Instr_E, Instr_M, Instr_W;
wire [31:0] PC, PC_D, PC_E, PC_M, PC_W, nPC;
// ~Instructions

// Data
wire [31:0] RD1, RD2, RegData, WData, RData, RData1, RData2, RData1_E, RData2_E, RData2_M, DR_W, Shifted, EXTOutput;
wire [31:0] ALUOutput, ALUA, ALUB, ALUB_Extended, AO_M, AO_W, Extended, BWExt;
wire [3:0] storeSig;
// ~Data

// Registers
wire [4:0] RegAddr, RS_E, RT_E, RD_E, RD_M, RD_W;
// ~Registers

wire [2:0] ForwardRSD, ForwardRTD, ForwardRSE, ForwardRTE, ForwardRTM;
wire delay, eq, gez, gtz, lez, ltz;

// F Level
// --- includes PC, IM, Reg_D
pc		pc_f	(.clk(clk), .reset(reset), .delay(delay), .nPC(nPC),.PC(PC));

im		im_f	(.PC(PC[11:2]), .Instr(Instr));

reg_d 	reg_d 	(.clk(clk), .reset(reset), .delay(delay), .Instr(Instr), .PC(PC), .Instr_D(Instr_D), .PC_D(PC_D));
// ~F Level


// D Level
// --- includes CTRL, NPC, GRF, EXT, ALU, Mux, Reg_E
ctrl 		ctrl_d 	(.Instr(Instr_D), .funct(Instr_D[5:0]), .opcode(Instr_D[31:26]), .RegDst(RegDst_D), .ALUSrc(ALUSrc_D),
					.MemtoReg(MemtoReg_D), .RegWrite(RegWrite_D), .MemWrite(MemWrite_D), .nPC_sel(nPC_sel_D),
					.ExtOp(ExtOp_D), .ALUctr(ALUctr_D));
	
mux5_32 	alua_d	(.a(RData1), .b(RegData), .c(PC_M+8), .d(AO_M), .e(PC_E+8), .select(ForwardRSD), .x(RD1));
	
mux5_32 	alub_d	(.a(RData2), .b(RegData), .c(PC_M+8), .d(AO_M), .e(PC_E+8), .select(ForwardRTD), .x(RD2));

comp 		comp_d 	(.A(RD1), .B(RD2), .eq(eq), .gez(gez), .gtz(gtz), .lez(lez), .ltz(ltz));

npc 		npc_d 	(.Instr(Instr_D), .PC(PC), .PC_D(PC_D), .rs(RD1), .eq(eq), .gez(gez), .gtz(gtz), .lez(lez), .ltz(ltz), 
						.nPC_sel(nPC_sel_D), .Shifted(Shifted), .npc(nPC));
	
grf 		grf_d 	(.clk(clk), .reset(reset), .RegWrite(RegWrite_W), .Reg1(Instr_D[25:21]), .Reg2(Instr_D[20:16]),
					.RegAddr(RD_W), .RegData(RegData), .PC(PC_W), .RData1(RData1), .RData2(RData2));
	
ext 		ext_d 	(.offset(Instr_D[15:0]), .ExtOp(ExtOp_D),  .Output(EXTOutput), .Shifted(Shifted));

mux3_5 	regdst_mux 	(.a(Instr_D[20:16]), .b(Instr_D[15:11]), .c(5'h1f), .select(RegDst_D), .x(RegAddr));
	
reg_e 		reg_e 	(.clk(clk),  .reset(reset | delay), .Instr_D(Instr_D), .RD_D(RegAddr), .RF_RD1(RData1), .RF_RD2(RData2), 
					.PC_D(PC_D), .EXT(EXTOutput), .Instr_E(Instr_E), .RF_RD1_E(RData1_E), .RF_RD2_E(RData2_E),
					.RS_E(RS_E), .RT_E(RT_E), .RD_E(RD_E), .Extended(Extended), .PC_E(PC_E));
// ~D Level


// E Level
// --- includes CTRL, Mux, ALU, Reg_M
assign ALUB_Extended = (ALUSrc_E == 0) ? ALUB : Extended;

ctrl 		ctrl_e 	(.Instr(Instr_E), .funct(Instr_E[5:0]), .opcode(Instr_E[31:26]), .RegDst(RegDst_E), .ALUSrc(ALUSrc_E),
					.MemtoReg(MemtoReg_E), .RegWrite(RegWrite_E), .MemWrite(MemWrite_E), .nPC_sel(nPC_sel_E),
					.ExtOp(ExtOp_E), .ALUctr(ALUctr_E));

mux4_32 	alua_e 	(.a(RData1_E), .b(RegData), .c(PC_M+8), .d(AO_M), .select(ForwardRSE), .x(ALUA));   
	
mux4_32 	alub_e 	(.a(RData2_E), .b(RegData), .c(PC_M+8), .d(AO_M), .select(ForwardRTE), .x(ALUB));
	
alu 		alu_e 	(.A(ALUA), .B(ALUB_Extended), .s(Instr_E[10:6]), .ALUctr(ALUctr_E), .Output(ALUOutput));

mux3_5	write_reg	(.a(RT_E), .b(RD_E), .c(5'h1f), .select(RegDst_E), .x(WriteReg));
	
reg_m 	reg_m 	(.clk(clk), .reset(reset), .ALURes(ALUOutput), .ALUB(ALUB), .Instr_E(Instr_E), .PC_E(PC_E),
						.RD_E(WriteReg), .Instr_M(Instr_M), .RF_RD2_M(RData2_M), .AO_M(AO_M), .RD_M(RD_M), .PC_M(PC_M));
// ~E Level


// M Level
// --- includes CTRL, DM, Reg_W	
assign WData = (ForwardRTM == 1) ? RegData : RData2_M;

ctrl 		ctrl_m	(.Instr(Instr_M), .funct(Instr_M[5:0]), .opcode(Instr_M[31:26]), .RegDst(RegDst_M), .ALUSrc(ALUSrc_M),
						.MemtoReg(MemtoReg_M), .RegWrite(RegWrite_M), .MemWrite(MemWrite_M), .nPC_sel(nPC_sel_M),
						.ExtOp(ExtOp_M), .ALUctr(ALUctr_M));

storeOpt	storeOpt	(.storeOp(Instr_M[31:26]), .Addr(AO_M[1:0]), .storeSig(storeSig));

dm 		dm_m		(.clk(clk), .reset(reset), .MemWrite(MemWrite_M), .storeSig(storeSig), .A(AO_M[11:2]), .WData(WData), 
						.PC(PC_M), .addr(AO_M), .RData(RData));
	
reg_w 	reg_w		(.clk(clk), .reset(reset),  .Instr_M(Instr_M), .RD_M(RD_M), .AO_M(AO_M), .PC_M(PC_M), .DMRes(RData),
						.Instr_W(Instr_W), .RD_W(RD_W), .PC_W(PC_W), .AO_W(AO_W), .DR_W(DR_W));
// ~M Level


// W Level
// --- includes CTRL, Mux	
ctrl 		ctrl_w	(.Instr(Instr_W), .funct(Instr_W[5:0]), .opcode(Instr_W[31:26]), .RegDst(RegDst_W), .ALUSrc(ALUSrc_W),
						.MemtoReg(MemtoReg_W), .RegWrite(RegWrite_W), .MemWrite(MemWrite_W), .nPC_sel(nPC_sel_W),
						.ExtOp(ExtOp_W), .ALUctr(ALUctr_W));

bw_ext 	bw_ext	(.DMRes(DR_W), .Addr(AO_W[1:0]), .loadOp(Instr_W[31:26]), .BWExt(BWExt));
	 
mux3_32 memreg_mux	(.a(AO_W), .b(BWExt), .c(PC_W + 8), .select(MemtoReg_W), .x(RegData));
// ~W Level


// Pause/Delay and Forwards
hazard_sig 	hazard_sig 	(.ir_d(Instr_D), .ir_e(Instr_E), .ir_m(Instr_M), .ir_w(Instr_W), 
								 .RegWrite_E(RegWrite_E), .RegWrite_M(RegWrite_M), .RegWrite_W(RegWrite_W),
								 .delay(delay), 
								 .ForwardRSD(ForwardRSD), .ForwardRTD(ForwardRTD), .ForwardRSE(ForwardRSE), .ForwardRTE(ForwardRTE), .ForwardRTM(ForwardRTM));

// ~Pause/Delay and Forwards

endmodule