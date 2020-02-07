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
// Create Date:    00:50:33 12/05/2019 
// Design Name: 
// Module Name:    forward 
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
module forward(
	 input [31:0] ir_d,
	 input [31:0] ir_e,
	 input [31:0] ir_m,
	 input [31:0] ir_w,
	 output delay,
	 output [2:0] ForwardRSD, ForwardRTD, ForwardRSE, ForwardRTE, ForwardRTM
    );

parameter 	addu_f = 6'b100001,
				subu_f = 6'b100011,
				
				ori    = 6'b001101,
				lui    = 6'b001111,
				
				lb		 = 6'b100000,
				lbu	 = 6'b100100,
				lh		 = 6'b100001,
				lhu	 = 6'b100101,
				lw     = 6'b100011,
				
				sb		 = 6'b101000,
				sh		 = 6'b101001,
				sw     = 6'b101011,
				
				beq    = 6'b000100,
				bne	 = 6'b000101,
				bgez	 = 6'b000001,
				bgezal = 6'b000001,
				bgtz	 = 6'b000111,
				blez	 = 6'b000110,
				bltz	 = 6'b000001,
				bltzal = 6'b000001,
				jal    = 6'b000011,
				j      = 6'b000010,
				jr_f   = 6'b001000,
				jalr_f = 6'b001001,
			
				rev_f	 = 6'b010100,
				nop    = 6'b000000;

wire b_D;
wire cal_r_D, cal_i_D, j_D, jr_D, jalr_D, jal_D, load_D, save_D;
wire cal_r_E, cal_i_E, j_E, jr_E, jalr_E, jal_E, load_E, save_E;
wire cal_r_M, cal_i_M, j_M, jr_M, jalr_M, jal_M, load_M, save_M;
wire cal_r_W, cal_i_W, j_W, jr_W, jalr_W, jal_W, load_W, save_W;

wire [4:0] rs_d, rt_d, rd_d;
wire [4:0] rs_e, rt_e, rd_e;
wire [4:0] rs_m, rt_m, rd_m;
wire [4:0] rs_w, rt_w, rd_w;

wire stall_b_r, stall_b_i, stall_b_load, stall_b_loadM;
wire stall_cal_r_load, stall_cal_i_load;
wire stall_load_load, stall_save_load;
wire stall_jr_r, stall_jr_i, stall_jr_load, stall_jr_loadM;

assign {rs_d, rt_d, rd_d} = {ir_d[`rs], ir_d[`rt], ir_d[`rd]};
assign {rs_e, rt_e, rd_e} = {ir_e[`rs], ir_e[`rt], ir_e[`rd]};
assign {rs_m, rt_m, rd_m} = {ir_m[`rs], ir_m[`rt], ir_m[`rd]};
assign {rs_w, rt_w, rd_w} = {ir_w[`rs], ir_w[`rt], ir_w[`rd]};


//b instructions
assign b_D        = (ir_d[`opcode] == beq) | (ir_d[`opcode] == bne) | (ir_d[`opcode] == bgez) | (ir_d[`opcode] == bgtz) |
						  (ir_d[`opcode] == blez)| (ir_d[`opcode] == bltz)| (ir_d[`opcode] == bgezal)| (ir_d[`opcode] == bltzal);

//j
assign j_D    	= (ir_d[`opcode] == j);
assign j_E    	= (ir_e[`opcode] == j);
assign j_M    	= (ir_m[`opcode] == j);
assign j_W    	= (ir_w[`opcode] == j);

//jr
assign jr_D     	= (ir_d[`opcode] == nop)	& (ir_d[`func]		== jr_f);
assign jr_E     	= (ir_e[`opcode] == nop)	& (ir_e[`func]		== jr_f);
assign jr_M     	= (ir_m[`opcode] == nop)	& (ir_m[`func]		== jr_f);
assign jr_W     	= (ir_w[`opcode] == nop)	& (ir_w[`func]		== jr_f);

//jalr
assign jalr_D     	= (ir_d[`opcode] == nop)	& (ir_d[`func]		== jalr_f);
assign jalr_E     	= (ir_e[`opcode] == nop)	& (ir_e[`func]		== jalr_f);
assign jalr_M     	= (ir_m[`opcode] == nop)	& (ir_m[`func]		== jalr_f);
assign jalr_W     	= (ir_w[`opcode] == nop)	& (ir_w[`func]		== jalr_f);

//jal instructions
assign jal_D    	= (ir_d[`opcode] == jal);
assign jal_E    	= (ir_e[`opcode] == jal);
assign jal_M    	= (ir_m[`opcode] == jal);
assign jal_W    	= (ir_w[`opcode] == jal);

//register calculation instructions
assign cal_r_D 	= (ir_d[`opcode] == nop)	& (ir_d[`func]		!= jr_f);
assign cal_r_E 	= (ir_e[`opcode] == nop)	& (ir_e[`func]		!= jr_f);
assign cal_r_M 	= (ir_m[`opcode] == nop)	& (ir_m[`func]		!= jr_f);
assign cal_r_W 	= (ir_w[`opcode] == nop)	& (ir_w[`func]		!= jr_f);

//immediate calculation instructions
assign cal_i_D 	= (ir_d[`opcode] == ori)	| (ir_d[`opcode]	== lui);
assign cal_i_E 	= (ir_e[`opcode] == ori)	| (ir_e[`opcode]	== lui);
assign cal_i_M 	= (ir_m[`opcode] == ori)	| (ir_m[`opcode]	== lui);
assign cal_i_W 	= (ir_w[`opcode] == ori)	| (ir_w[`opcode]	== lui);

//load instructions
assign load_D    	= (ir_d[`opcode] == lb)	| (ir_d[`opcode] == lbu)	| (ir_d[`opcode] == lh)	| (ir_d[`opcode] == lhu)	| (ir_d[`opcode] == lw);
assign load_E    	= (ir_e[`opcode] == lb)	| (ir_e[`opcode] == lbu)	| (ir_e[`opcode] == lh)	| (ir_e[`opcode] == lhu)	| (ir_e[`opcode] == lw);
assign load_M    	= (ir_m[`opcode] == lb)	| (ir_m[`opcode] == lbu)	| (ir_m[`opcode] == lh)	| (ir_m[`opcode] == lhu)	| (ir_m[`opcode] == lw);
assign load_W    	= (ir_w[`opcode] == lb)	| (ir_w[`opcode] == lbu)	| (ir_w[`opcode] == lh)	| (ir_w[`opcode] == lhu)	| (ir_w[`opcode] == lw);

//store instructions
assign save_D 		= (ir_d[`opcode] == sb)	| (ir_d[`opcode] == sh)	| (ir_d[`opcode] == sw);
assign save_E 		= (ir_e[`opcode] == sb)	| (ir_e[`opcode] == sh)	| (ir_e[`opcode] == sw);
assign save_M 		= (ir_m[`opcode] == sb)	| (ir_m[`opcode] == sh)	| (ir_m[`opcode] == sw);
assign save_W 		= (ir_w[`opcode] == sb)	| (ir_w[`opcode] == sh)	| (ir_w[`opcode] == sw);


assign stall_b_r			= b_D & cal_r_E & ((rs_d == rd_e) | (rt_d == rd_e)); //DONE1
assign stall_b_i			= b_D & cal_i_E & ((rs_d == rt_e) | (rt_d == rt_e)); //DONE1
assign stall_b_load		= b_D & load_E  & ((rs_d == rt_e) | (rt_d == rt_e)); //DONE2
assign stall_b_loadM		= b_D & load_M  & ((rs_d == rt_m) | (rt_d == rt_m)); //DONE3

assign stall_cal_r_load = cal_r_D & load_E & ((rs_d == rt_e) | (rt_d == rt_e)); //DONE4
assign stall_cal_i_load = cal_i_D & load_E & (rs_d == rt_e); //DONE4

assign stall_load_load	= load_D  & load_E & (rs_d == rt_e); //DONE4
assign stall_save_load 	= save_D & load_E & (rs_d == rt_e); //DONE4

//stall signal if CUR is calr instr and NEXT is jr instr
assign stall_jr_r			= jr_D & cal_r_E & (rs_d == rd_e); //DONE1
//stall signal if CUR is cali instr and NEXT is jr instr
assign stall_jr_i       = jr_D & cal_i_E & (rs_d == rt_e); //DONE1
//stall signal if CUR is load instr and NEXT is jr instr
assign stall_jr_load		= jr_D & load_E  & (rs_d == rt_e); //DONE2
//stall signal if PREV is load instr and NEXT is jr instr
assign stall_jr_loadM	= jr_D & load_M  & (rs_d == rt_m); //DONE3

assign delay = stall_b_r 			| stall_b_i 			| stall_b_load 		| stall_b_loadM 		|
					stall_cal_r_load 	| stall_cal_i_load 	| stall_load_load 	| stall_save_load 	|
					stall_jr_r 			| stall_jr_i 			| stall_jr_load 		| stall_jr_loadM;
					

assign ForwardRSD	= 	((b_D | jr_D) & jal_E   & (rs_d == 31) )                 ? 4 :
							((b_D | jr_D) & cal_r_M & (rs_d == rd_m) & (rs_d != 0) ) ? 3 :
							((b_D | jr_D) & cal_i_M & (rs_d == rt_m) & (rs_d != 0) ) ? 3 :
							((b_D | jr_D) & jal_M   & (rs_d == 31) )                 ? 2 :
							((b_D | jr_D) & cal_r_W & (rs_d == rd_w) & (rs_d != 0) ) ? 1 :
							((b_D | jr_D) & cal_i_W & (rs_d == rt_w) & (rs_d != 0) ) ? 1 :
							((b_D | jr_D) & load_W  & (rs_d == rt_w) & (rs_d != 0) ) ? 1 :
							((b_D | jr_D) & jal_W   & (rs_d == 31) )                 ? 1 : 0;
							
assign ForwardRTD = 	(b_D & jal_E   & (rt_d == 31) )                      		? 4 :
							(b_D & cal_r_M & (rt_d == rd_m) & (rt_d != 0) ) 			? 3 :
							(b_D & cal_i_M & (rt_d == rt_m) & (rt_d != 0) ) 			? 3 :
							(b_D & jal_M   & (rt_d == 31) )                      		? 2 :
							(b_D & cal_r_W & (rt_d == rd_w) & (rt_d != 0) ) 			? 1 :
							(b_D & cal_i_W & (rt_d == rt_w) & (rt_d != 0) ) 			? 1 :
							(b_D & load_W  & (rt_d == rt_w) & (rt_d != 0) ) 			? 1 :
							(b_D & jal_W   & (rt_d == 31) )                      		? 1 : 0;
							
assign ForwardRSE = 	((cal_r_E | cal_i_E | load_E | save_E) & cal_r_M & (rs_e == rd_m) & (rs_e != 0) ) ? 3 :
							((cal_r_E | cal_i_E | load_E | save_E) & cal_i_M & (rs_e == rt_m) & (rs_e != 0) ) ? 3 :
							((cal_r_E | cal_i_E | load_E | save_E) & jal_M   & (rs_e == 31) )                 ? 2 :
							((cal_r_E | cal_i_E | load_E | save_E) & cal_r_W & (rs_e == rd_w) & (rs_e != 0) ) ? 1 :
							((cal_r_E | cal_i_E | load_E | save_E) & cal_i_W & (rs_e == rt_w) & (rs_e != 0) ) ? 1 :
							((cal_r_E | cal_i_E | load_E | save_E) & load_W  & (rs_e == rt_w) & (rs_e != 0) ) ? 1 :
							((cal_r_E | cal_i_E | load_E | save_E) & jal_W   & (rs_e == 31) )                 ? 1 : 0;

assign ForwardRTE = 	((cal_r_E | save_E) & cal_r_M & (rt_e == rd_m) & (rt_e != 0) ) ? 3 :
							((cal_r_E | save_E) & cal_i_M & (rt_e == rt_m) & (rt_e != 0) ) ? 3 :
							((cal_r_E | save_E) & jal_M   & (rt_e == 31) )                 ? 2 :
							((cal_r_E | save_E) & cal_r_W & (rt_e == rd_w) & (rt_e != 0) ) ? 1 :
							((cal_r_E | save_E) & cal_i_W & (rt_e == rt_w) & (rt_e != 0) ) ? 1 :
							((cal_r_E | save_E) & load_W  & (rt_e == rt_w) & (rt_e != 0) ) ? 1 :
							((cal_r_E | save_E) & jal_W   & (rt_e == 31) )                 ? 1 : 0;

assign ForwardRTM = 	(save_M & cal_r_W & (rt_m == rd_w) & (rt_m != 0)) ? 1 :
							(save_M & cal_i_W & (rt_m == rt_w) & (rt_m != 0)) ? 1 :
							(save_M & load_W  & (rt_m == rt_w) & (rt_m != 0)) ? 1 :
							(save_M & jal_W   & (rt_m == 31) )                ? 1 : 0;

endmodule
