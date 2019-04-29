`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    11:14:26 12/15/2017 
// Design Name: 
// Module Name:    string4 
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
module string4(
    input clk,
    input clr,
    input [7:0] in,
    output reg out,
    output reg [7:0] res
    );
	 
	 integer state;
	 integer in2;
	 integer res2;
	
	initial begin out = 0;
					  state = 0;
					  res = "0";
					  res2 = 0;
					  end
					  
	always @ (posedge clk or posedge clr)
	begin
		if(clr)begin
			out <= 0;
			state <= 0;
			res <= "0";
			in2 <= 0;
			res2 <= 0;
		end
		
		else begin
			case(state)
			0:
				begin
				state <= in=="0"? 1:
							in=="1"? 1:
							in=="2"? 1:
							in=="3"? 1:
							in=="4"? 1:
							in=="5"? 1:
							in=="6"? 1:
							in=="7"? 1:
							in=="8"? 1:
							in=="9"? 1:2;
				out<=(in=="0"|in=="1"|in=="2"|in=="3"|in=="4"|in=="5"|in=="6"|in=="7"|in=="8"|in=="9");
				in2 <= in - "0";
				res2 <= (res - "0") + in2;
				res <= res2 + "0";
				end
			1:
				begin
				state <= in=="+"? 0:
							in=="*"? 0:2;
				out<=0;
				end
			2:
				begin
				state<=3;
				out<=0;
				end
			endcase
		end
	end


endmodule
