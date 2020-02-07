`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    18:52:37 11/09/2017 
// Design Name: 
// Module Name:    gray 
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
module gray(
    input Clk,
    input Reset,
    input En,
    output reg [2:0] Output,
    output reg Overflow
    );
	
	reg [3:0] Cnt;
	
	initial begin Output = 0;
					  Overflow = 0;
					  Cnt = 0;
					  end
	
	always @(posedge Clk, negedge Reset) 
	begin
		if(Reset)begin
			Cnt <= 0;
			Output <= 0;
			Overflow <= 0;
		end
		
		else if(En)begin
		
			Cnt <= Cnt + 1;
			
			if(Overflow == 0)begin
				Overflow <= Cnt[3];
				if(Overflow == 1)
					Cnt <= 0;
			end
		
			Output [2:0] <= { Cnt[2], (Cnt[2] ^ Cnt[1]),(Cnt[1] ^ Cnt[0]) };
		end
	end
endmodule
