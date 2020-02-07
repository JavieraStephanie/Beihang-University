`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    04:46:55 08/02/2019 
// Design Name: 
// Module Name:    storeOpt 
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
module storeOpt(
	 input [5:0] storeOp,
	 input [1:0] Addr,
	 output reg [3:0] storeSig
    );
	 
parameter	SB		 = 6'b101000,
				SH		 = 6'b101001;

always @ (*) begin
	case (storeOp)
		SB:	begin
			case (Addr)
				0:	begin
					storeSig = 1;
				end
				1:	begin
					storeSig = 2;
				end
				2:	begin
					storeSig = 4;
				end
				3: begin
					storeSig = 8;
				end
			endcase
		end
		SH:	begin
			case (Addr[1])
				0:	begin
					storeSig = 3;
				end
				1:	begin
					storeSig = 9;
				end
			endcase
		end
		default: storeSig = 15;
	endcase
end

endmodule
