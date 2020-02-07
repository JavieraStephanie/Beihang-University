`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    16:49:05 07/18/2019 
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

wire [31:0] PC, nPC;
wire [31:0] Instr;

wire [1:0] RegDst, ALUSrc, RegWrite, MemWrite, ExtOP;
wire [1:0] MemtoReg, ALUctr, nPC_sel;

wire [4:0] RegAddr;

wire [31:0] ALUOutput;
wire zero;

wire [31:0] EXTOutput, Shifted, Shifted2;

wire [31:0] RData1, RData2, RegData;

wire [31:0] ALUB;

wire [31:0] RData;

pc 		pc_mod 		(.clk(clk), .reset(reset), .nPC(nPC), .PC(PC));
im 		im_mod 		(.PC(PC[11:2]), .Instr(Instr));
npc 		npc_mod 		(.Instr(Instr), .RData1(RData1), .Shifted(Shifted), .nPC_sel(nPC_sel), .zero(zero), .pc(PC), .nPC(nPC));

ctrl 		ctrl_mod 	(.funct(Instr[5:0]), .opcode(Instr[31:26]), .RegDst(RegDst), .ALUSrc(ALUSrc), 
							 .MemtoReg(MemtoReg), .RegWrite(RegWrite), .MemWrite(MemWrite), .nPC_sel(nPC_sel), 
							 .ExtOP(ExtOP), .ALUctr(ALUctr));

mux3_5 	regdst_mux 	(.a(Instr[20:16]), .b(Instr[15:11]), .select(RegDst), .x(RegAddr));

grf 		grf_mod 		(.clk(clk), .reset(reset), .Reg1(Instr[25:21]), .Reg2(Instr[20:16]), .RegAddr(RegAddr), 
							 .RegWrite(RegWrite), .PC(PC), .RegData(RegData), .RData1(RData1), .RData2(RData2));

mux2_32 	alusrc_mux 	(.a(RData2), .b(EXTOutput), .select(ALUSrc), .x(ALUB));

alu 		alu_mod 		(.A(RData1), .B(ALUB), .ALUctr(ALUctr), .zero(zero), .Output(ALUOutput));

ext 		ext_mod 		(.offset(Instr[15:0]), .extop(ExtOP), .Output(EXTOutput), .Shifted(Shifted), .Shifted2(Shifted2));

mux3_32 	memreg_mux 	(.a(ALUOutput), .b(RData), .c(Shifted2), .pc(PC), .select(MemtoReg), .x(RegData));

dm 		dm_mod 		(.clk(clk), .reset(reset), .MemWrite(MemWrite), .A(ALUOutput[11:2]), .WData(RData2), .PC(PC), .addr(ALUOutput), .RData(RData));

endmodule
