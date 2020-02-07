`timescale 1ns / 1ps

`define opcode 31:26
`define func 	5:0
`define rs 		25:21
`define rt 		20:16
`define rd 		15:11
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    00:48:51 12/05/2019 
// Design Name: 
// Module Name:    hazard_signal 
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
module hazard_sig(
	 input [31:0] ir_d,
	 input [31:0] ir_e,
	 input [31:0] ir_m,
	 input [31:0] ir_w,
	 input RegWrite_E, RegWrite_M, RegWrite_W,
	 output delay,
	 output [1:0] ForwardRSD, ForwardRTD, ForwardRSE, ForwardRTE, ForwardRTM
	 );

wire [1:0] Tnew_E, Tnew_M, Tnew_W;
wire [1:0] Tuse_rs, Tuse_rt;
wire [1:0] Tnew_ie, Tnew_im, Tnew_iw;

wire [4:0] rs_d, rt_d, rd_d;
wire [4:0] rs_e, rt_e, rd_e;
wire [4:0] rs_m, rt_m, rd_m;
wire [4:0] rs_w, rt_w, rd_w;

wire stall_rs1, stall_rs2, stall_rs3, stall_rs4;
wire stall_rt1, stall_rt2, stall_rt3, stall_rt4;

assign {rs_d, rt_d, rd_d} = {ir_d[`rs], ir_d[`rt], ir_d[`rd]};
assign {rs_e, rt_e, rd_e} = {ir_e[`rs], ir_e[`rt], ir_e[`rd]};
assign {rs_m, rt_m, rd_m} = {ir_m[`rs], ir_m[`rt], ir_m[`rd]};
assign {rs_w, rt_w, rd_w} = {ir_w[`rs], ir_w[`rt], ir_w[`rd]};

// NEXT: b or j instruction CUR: cal_r or cal_i instruction
assign stall_rs1	=	((rs_d == rd_e) & (Tuse_rs == 0) & (Tnew_E == 1) & RegWrite_E);
// NEXT: b or j instruction CUR: other than cal_r and cal_i instruction
assign stall_rs2	=	((rs_d == rd_e) & (Tuse_rs == 0) & (Tnew_E == 2) & RegWrite_E);
// NEXT: b or j instruction PREV: other than cal_r and cal_i instruction
assign stall_rs3	=	((rs_d == rd_m) & (Tuse_rs == 0) & (Tnew_M == 1) & RegWrite_M);
// NEXT: other than b or j instruction CUR: other than cal_r and cal_i instruction
assign stall_rs4	=	((rs_d == rd_e) & (Tuse_rs == 1) & (Tnew_E == 2) & RegWrite_E);

// NEXT: b instruction CUR: cal_r or cal_i instruction
assign stall_rt1	= 	((rt_d == rd_e) & (Tuse_rt == 0) & (Tnew_E == 1) & RegWrite_E);
// NEXT: b instruction CUR: other than cal_r or cal_i instruction
assign stall_rt2	= 	((rt_d == rd_e) & (Tuse_rt == 0) & (Tnew_E == 2) & RegWrite_E);
// NEXT: b instruction PREV: other than cal_r and cal_i instruction
assign stall_rt3	=	((rt_d == rd_m) & (Tuse_rt == 0) & (Tnew_M == 1) & RegWrite_M);
// NEXT: cal_r instruction CUR: other than cal_r and cal_i instruction
assign stall_rt4	=	((rt_d == rd_m) & (Tuse_rt == 1) & (Tnew_E == 2) & RegWrite_E);

assign delay = stall_rs1	|	stall_rs2	|	stall_rs3	|	stall_rs4	|
					stall_rt1	|	stall_rt2	|	stall_rt3	|	stall_rt4;
							
assign ForwardRSD	= 	((rs_d == rd_m) & (rs_d != 0) & (Tnew_im == 1)  & RegWrite_M)	? 2 :
							((rs_d == rt_m) & (rs_d != 0) & (Tnew_im == 0) & RegWrite_M)	? 2 :
							((rs_d == rd_w) & (rs_d != 0) & (Tnew_iw == 1)  & RegWrite_W)	? 1 : 
							((rs_d == rt_w) & (rs_d != 0) & (Tnew_iw == 0) & RegWrite_W)	? 1 : 0;
							
assign ForwardRTD = 	((rt_d == rd_m) & (rt_d != 0) & (Tnew_im == 1)  & RegWrite_M)	? 2 :
							((rt_d == rt_m) & (rt_d != 0) & (Tnew_im == 0) & RegWrite_M)	? 2 :
							((rt_d == rd_w) & (rt_d != 0) & (Tnew_iw == 1)  & RegWrite_W)	? 1 : 
							((rt_d == rt_w) & (rt_d != 0) & (Tnew_iw == 0) & RegWrite_W)	? 1 : 0;
							
assign ForwardRSE = 	((rs_e == rd_m) & (rs_e != 0) & (Tnew_im == 1)  & RegWrite_M) 	? 2 :
							((rs_e == rt_m) & (rs_e != 0) & (Tnew_im == 0) & RegWrite_M) 	? 2 :
							((rs_e == rd_w) & (rs_e != 0) & (Tnew_iw == 1)  & RegWrite_W) 	? 1 :
							((rs_e == rt_w) & (rs_e != 0) & (Tnew_iw == 0) & RegWrite_W) 	? 1 : 0;
							
assign ForwardRTE = 	((rt_e == rd_m) & (rt_e != 0) & (Tnew_im == 1)  & RegWrite_M) 	? 2 :
							((rt_e == rt_m) & (rt_e != 0) & (Tnew_im == 0) & RegWrite_M) 	? 2 :
							((rt_e == rd_w) & (rt_e != 0) & (Tnew_iw == 1)  & RegWrite_W) 	? 1 :
							((rt_e == rt_w) & (rt_e != 0) & (Tnew_iw == 0) & RegWrite_W) 	? 1 : 0;
							
assign ForwardRTM = 	((rt_m == rd_w) & (rt_m != 0) & (Tnew_iw == 1)  & RegWrite_W)	? 1 : 
							((rt_m == rt_w) & (rt_m != 0) & (Tnew_iw == 0) & RegWrite_W)	? 1 : 0;
							
							
hazard	Tuse	(.ir(ir_d), .Tuse_rs(Tuse_rs), .Tuse_rt(Tuse_rt));
hazard	T_e	(.ir(ir_e), .TnewSrc(2'b0), .Tnew(Tnew_E), .Tnew_i(Tnew_ie));
hazard	T_m	(.ir(ir_m), .TnewSrc(2'b01), .Tnew(Tnew_M), .Tnew_i(Tnew_im));
hazard	T_w	(.ir(ir_w), .TnewSrc(2'b10), .Tnew(Tnew_W), .Tnew_i(Tnew_iw));


endmodule
