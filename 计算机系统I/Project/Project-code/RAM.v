`timescale 1ns / 1ps

// Copyright 2023 Sycuricon Group
// Author: Jinyan Xu (phantom@zju.edu.cn)

module RAM (
    input  clk,
    input  rw_wmode,
    input  [32:0] rw_addr,
    input  [63:0] rw_wdata,
    input  [7:0] rw_wmask,
    output [63:0] rw_rdata,

    input  [32:0] ro_addr,
    output [63:0] ro_rdata
);

    localparam FILE_PATH = "testcase.hex";
    integer i;
    reg [63:0] mem [0:511];
    wire [32:0] addr1;
    wire [32:0] addr2;
    assign addr1 = rw_addr/8;
    assign addr2 = ro_addr/8; 
    wire [8:0] add1 = addr1[8:0],add2 = addr2[8:0];
    initial begin
        $readmemh(FILE_PATH, mem);
    end
    always @(posedge clk) begin
        if (rw_wmode) begin
            for(i = 0; i < 8; i = i+1) begin
                if(rw_wmask[i]) begin
                    mem[add1][i*8 +: 8] = rw_wdata[i*8 +: 8];
                end
            end
        end
        
    end
    assign rw_rdata = mem[add1];
    assign ro_rdata = mem[add2];
    
endmodule
