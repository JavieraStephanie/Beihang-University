`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    21:40:13 12/19/2019 
// Design Name: 
// Module Name:    MDU 
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
module mdu(
	 input clk,
	 input reset,
	 input [31:0] Instr,
	 input [31:0] D1,
    input [31:0] D2,
    input [3:0] MDUctr,
    output Busy,
	 output delayMDU,
    output reg [31:0] HI,
    output reg [31:0] LO,
	 output HiLo
    );
	 
reg [3:0] busy;
reg start;
wire mult, multu, div, divu, mfhi, mflo, mthi, mtlo;

parameter MULT		=	1,
			 MULTU	=	2,
			 DIV		=	3,
			 DIVU		=	4,
			 MTHI		=	5,
			 MTLO		=	6;
				
assign div	=	(Instr[5:0] == 6'b011010) & (Instr[15:6] == 0);
assign divu =	(Instr[5:0] == 6'b011011) & (Instr[15:6] == 0);
assign mfhi =	(Instr[5:0] == 6'b010000) & (Instr[25:16] == 0 & Instr[10:6] == 0);
assign mflo =	(Instr[5:0] == 6'b010010) & (Instr[25:16] == 0 & Instr[10:6] == 0);
assign mthi =	(Instr[5:0] == 6'b010001) & (Instr[20:6] == 0);
assign mtlo =	(Instr[5:0] == 6'b010011) & (Instr[20:6] == 0);
assign mult =	(Instr[5:0] == 6'b011000) & (Instr[15:6] == 0);
assign multu=	(Instr[5:0] == 6'b011001) & (Instr[15:6] == 0);

initial begin
	HI = 0;
	LO = 0;
	busy = 0;
end

				
assign delayMDU	=	(Busy | busy | start) & (div | divu | mult | multu | mfhi | mflo | mthi | mtlo);

always @(negedge clk) begin
	if (start == 0 & Busy == 0 & (MDUctr == 1 | MDUctr == 2 | MDUctr == 3 | MDUctr == 4))	begin
		start = 1;
	end
end

always @(posedge clk) begin
	if(reset) begin
		HI = 0;
		LO = 0;
		busy = 0;
	end
	else begin
		if (start == 1 & busy == 0) begin
			//start = 0;
			case(MDUctr)
				MULT:		begin
					{HI, LO} = $signed(D1) * $signed(D2);
					busy = 5;
				end
				MULTU:	begin
					{HI, LO} = D1 * D2;
					busy = 5;
				end
				DIV:		begin
					HI = $signed(D1) % $signed(D2);
					LO = $signed(D1) / $signed(D2);
					busy = 10;
				end
				DIVU:		begin
					HI = D1 % D2;
					LO = D1 / D2;
					busy = 10;
				end
				MTHI:		begin
					HI = D1;
					busy = 0;
				end
				MTLO:		begin
					LO = D1;
					busy = 0;
				end
				default:	busy = 0;
			endcase
		end
		if (busy != 0)
			busy = busy - 1;
	end
end

assign Busy = (busy != 0);

endmodule
