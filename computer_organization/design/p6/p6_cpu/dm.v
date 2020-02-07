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
	 input [11:0] A,
	 input [31:0] WData,
	 input [31:0] PC,
	 input [31:0] addr,
	 output[31:0] RData
	 );
	 
reg [31:0] mem [4095:0];
wire [31:0] writeHolder;
integer i;

initial begin
	for(i = 0; i < 4096; i = i + 1)
		mem[i] = 32'b0;
end

assign RData = mem[A];

assign writeHolder = (storeSig == 1)	?	{mem[A][31:8], WData[7:0]}	:
							(storeSig == 2)	?	{mem[A][31:16], WData[7:0], mem[A][7:0]}	:
							(storeSig == 4)	?	{mem[A][31:24], WData[7:0], mem[A][15:0]}	:
							(storeSig == 8)	?	{WData[7:0], mem[A][23:0]}	:
							(storeSig == 3)	?	{mem[A][31:16], WData[15:0]}	:
							(storeSig == 12)	?	{WData[15:0], mem[A][15:0]}	:
														WData;

always @ (posedge clk) begin
	if(reset)
		for(i = 0; i < 4096; i = i + 1)
			mem[i] = 32'b0;
	else if(MemWrite) begin
		mem[A] = writeHolder;
		$display("%d@%h: *%h <= %h", $time, PC, {18'b0, A, 2'b0}, writeHolder);
		//addr is either {addr[31:2], 2'b00} OR {18'b0, A, 2'b0}
	end
end

endmodule