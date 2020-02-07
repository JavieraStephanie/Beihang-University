`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    22:08:28 12/14/2017 
// Design Name: 
// Module Name:    string2 
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
module string2(
    input clk,
    input clr,
    input [7:0] in,
    output reg out
    );
	 
	 integer state;
	 
	 initial begin state = 1;
						out = 0;
						end
						
	always @(posedge clk or posedge clr)begin
		if(clr)begin
			out <= 0;
			state <= 1;
		end
		else begin
			case(state)
			0:
				begin
					state <= 0;
					out <= 0;
				end
			1:
				begin
					state <= in == "1" ? 2:
								in == "2" ? 2:
								in == "3" ? 2:
								in == "4" ? 2:
								in == "5" ? 2:
								in == "6" ? 2:
								in == "7" ? 2:
								in == "8" ? 2:
								in == "9" ? 2:
								in == "0" ? 2:
								in == "(" ? 3:0;
					out <= (in=="1"|in=="2"|in=="3"|in=="4"|in=="5"|in=="6"|in=="7"|in=="8"|in=="9"|in=="0"|in=="(");
				end
			2:
				begin
					state <= in == "+" ? 1:
								in == "*" ? 1:0;
					out <= 0;
				end
			3:
				begin
					state <= in == "1" ? 4:
								in == "2" ? 4:
								in == "3" ? 4:
								in == "4" ? 4:
								in == "5" ? 4:
								in == "6" ? 4:
								in == "7" ? 4:
								in == "8" ? 4:
								in == "9" ? 4:
								in == "0" ? 4:0;
					out <= 0;
				end
			4:
				begin
					state <= in == "+" ? 5:
								in == "*" ? 5:0;
					out <= 0;
				end
			5:
				begin
					state <= in == "1" ? 6:
								in == "2" ? 6:
								in == "3" ? 6:
								in == "4" ? 6:
								in == "5" ? 6:
								in == "6" ? 6:
								in == "7" ? 6:
								in == "8" ? 6:
								in == "9" ? 6:
								in == "0" ? 6:0;
					out <= 0;
				end
			6:
				begin
					state <= in == "+" ? 5:
								in == "*" ? 5:
								in == ")" ? 2:0;
					out <= (in==")");
				end
			endcase
		end
	end


endmodule
