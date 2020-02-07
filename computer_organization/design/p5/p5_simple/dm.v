`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    00:47:20 12/05/2019 
// Design Name: 
// Module Name:    dm 
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
module dm(
	 input clk,
	 input reset,
	 input MemWrite,
	 input [3:0] storeSig,
	 input [9:0] A,
	 input [31:0] WData,
	 input [31:0] PC,
	 input [31:0] addr,
	 output[31:0] RData
	 );
	 
reg [31:0] mem [1023:0];
integer i;

initial begin
	for(i = 0; i < 1024; i = i + 1)
		mem[i] = 32'h0;
end

assign RData = mem[A];

always @ (posedge clk) begin
	if(reset)
		for(i = 0; i < 1024; i = i + 1)
			mem[i] = 32'h0;
	else if(MemWrite) begin
		case (storeSig)
			1:	begin
				mem[A][7:0] = WData[7:0];
			end
			2: begin
				mem[A][15:8] = WData[7:0];
			end
			4: begin
				mem[A][23:16] = WData[7:0];
			end
			8: begin
				mem[A][31:24] = WData[7:0];
			end
			3: begin
				mem[A][15:0] = WData[15:0];
			end
			9: begin
				mem[A][31:16] = WData[15:0];
			end
			default: begin
			mem[A] = WData;
			end
		endcase
		$display("%d@%h: *%h <= %h", $time, PC, addr, mem[A]);
	end
end


endmodule
