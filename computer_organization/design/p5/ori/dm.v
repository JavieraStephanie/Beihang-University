`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    04:11:49 07/19/2019 
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
		mem[i] = 32'b0;
end

assign RData = mem[A];

always @ (posedge clk) begin
	if(reset)
		for(i = 0; i < 1024; i = i + 1)
			mem[i] = 32'b0;
	else if(MemWrite) begin
		mem[A] = WData;
		$display("%d@%h: *%h <= %h", $time, PC, addr, mem[A]);
	end
end

endmodule