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
	 input [1:0] extop,
    input [9:0] A,
    input [31:0] WData,
	 input [31:0] PC,
	 input [31:0] addr,
    output reg [31:0] RData
    );

reg [31:0] mem [1023:0];
reg [31:0] temp;
integer i;

initial begin
	for (i = 0; i < 1024; i = i+1)
		mem[i] = 32'h0;
end

always @ (*) begin
	temp = mem[A];
	if (extop == 2'b10) begin
		RData = {{24'b0}, {temp[7:0]}};
	end
	else RData = temp;
end

always @ (posedge clk) begin
	if (reset)
		for (i = 0; i < 1024; i = i+1)
			mem[i] = 7'h0;
	else if (MemWrite) begin
		mem[A] = WData;
		$display("@%h: *%h <= %h", PC, addr, mem[A]);
	end
end

//ext	ext_lbu	(temp[31:0], extop1, RData);

endmodule
