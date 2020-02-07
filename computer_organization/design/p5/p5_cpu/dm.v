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
wire [31:0] writeHolder;
integer i;

initial begin
	for(i = 0; i < 1024; i = i + 1)
		mem[i] = 32'b0;
end

assign RData = mem[A];

assign writeHolder = (storeSig == 1)	?	{mem[A][31:8], WData[7:0]}	:
							(storeSig == 2)	?	{mem[A][31:16], WData[7:0], mem[A][7:0]}	:
							(storeSig == 4)	?	{mem[A][31:24], WData[7:0], mem[A][15:0]}	:
							(storeSig == 8)	?	{WData[7:0], mem[A][23:0]}	:
							(storeSig == 3)	?	{mem[A][31:16], WData[15:0]}	:
							(storeSig == 9)	?	{WData[15:0], mem[A][15:0]}	:
														WData;

always @ (posedge clk) begin
	if(reset)
		for(i = 0; i < 1024; i = i + 1)
			mem[i] = 32'b0;
	else if(MemWrite) begin
		/*case (storeSig)
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
		endcase*/
		mem[A] = writeHolder;
		$display("%d@%h: *%h <= %h", $time, PC, addr, mem[A]);
	end
end

endmodule