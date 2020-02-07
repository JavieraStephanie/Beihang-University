`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    00:47:59 12/05/2019 
// Design Name: 
// Module Name:    bw_ext 
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
module bw_ext(
	 input [31:0] DMRes,
	 input [1:0] Addr,
	 input [5:0] loadOp,
	 output reg [31:0] BWExt
    );
	 
parameter	LB		 = 6'b100000,
				LBU	 = 6'b100100,
				LH		 = 6'b100001,
				LHU	 = 6'b100101;
				
always @ (*) begin
	case (loadOp)
		LB:	begin
			case (Addr)
				0:	begin
					BWExt = {{24{DMRes[7]}}, DMRes[7:0]};
				end
				1:	begin
					BWExt = {{24{DMRes[15]}}, DMRes[15:8]};
				end
				2:	begin
					BWExt = {{24{DMRes[23]}}, DMRes[23:16]};
				end
				3: begin
					BWExt = {{24{DMRes[31]}}, DMRes[31:24]};
				end
			endcase
		end
		LBU:	begin
			case (Addr)
				0:	begin
					BWExt = {{24'b0}, DMRes[7:0]};
				end
				1:	begin
					BWExt = {{24'b0}, DMRes[15:8]};
				end
				2:	begin
					BWExt = {{24'b0}, DMRes[23:16]};
				end
				3: begin
					BWExt = {{24'b0}, DMRes[31:24]};
				end
			endcase
		end
		LH:	begin
			case (Addr)
				0:	begin
					BWExt = {{16{DMRes[15]}}, DMRes[15:0]};
				end
				2:	begin
					BWExt = {{16{DMRes[31]}}, DMRes[31:16]};
				end
			endcase
		end
		LHU:	begin
			case (Addr)
				0:	begin
					BWExt = {{16'b0}, DMRes[15:0]};
				end
				2:	begin
					BWExt = {{16'b0}, DMRes[31:16]};
				end
			endcase
		end
		default: BWExt = DMRes;
	endcase
end

endmodule
