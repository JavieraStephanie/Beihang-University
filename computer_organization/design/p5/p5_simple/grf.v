`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    00:45:14 12/05/2019 
// Design Name: 
// Module Name:    grf 
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
module grf(
	 input clk,
	 input reset,
	 input RegWrite,
	 input [4:0] Reg1,
	 input [4:0] Reg2,
	 input [4:0] RegAddr,
	 input [31:0] RegData,
	 input [31:0] PC,
	 output [31:0] RData1,
	 output [31:0] RData2
	 );
	 
reg [31:0] registers[31:0];
integer i;
	 
initial begin
	for(i = 0; i < 32; i = i + 1)
		registers[i] = 32'h0;
end

assign RData1 = (Reg1 == RegAddr && RegAddr != 0 && RegWrite) ? RegData : registers[Reg1];
assign RData2 = (Reg2 == RegAddr && RegAddr != 0 && RegWrite) ? RegData : registers[Reg2];

always @ (posedge clk) begin
	if(reset)
		for(i = 0; i < 32; i = i + 1)
			registers[i] <= 32'h0;
	else if(RegWrite && RegAddr != 5'b0) begin
		registers[RegAddr] <= RegData;
		$display("%d@%h: $%d <= %h", $time, PC, RegAddr, RegData);
	end
end

endmodule
