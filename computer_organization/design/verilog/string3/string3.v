`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    00:53:26 12/15/2017 
// Design Name: 
// Module Name:    string3 
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
module string3(
    input clk,
    input in,
    output reg out
    );
	 
	 integer state;
	 initial begin state = 0;
						out = 0;
						end
	
	always @(posedge clk)begin
		case(state)
		0:
			begin
				state <= in == 1 ? 1:0;
				out <= 0;
			end
		1:
			begin
				state <= in == 1 ? 2:0;
				out <= 0;
			end
		2:
			begin
				state <= in == 0 ? 3:0;
				out <= 0;
			end
		3:
			begin
				state <= in == 1 ? 4:0;
				out <= 0;
			end
		4:
			begin
				state <= in == 1 ? 5:0;
				out <= 0;
			end
		5:
			begin
				state <= in == 1 ? 2:3;
				out <= (in==1);
			end
		endcase
	end


endmodule
