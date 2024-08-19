`include "core_struct.vh"
module RegFile (
    input clk,
    input we,
    input [4:0] read_addr_1,
    input [4:0] read_addr_2,
    input [4:0] write_addr,
    input [63:0] write_data,
    output [63:0] read_data_1,
    output [63:0] read_data_2
);
    import CorePack::*;

    integer i;
    data_t register [0:31]; // 总共31个寄存器，地址为1-31
    // Asynchronous read operation
    assign read_data_1 = (read_addr_1 == 0) ? 0 : register[read_addr_1];
    assign read_data_2 = (read_addr_2 == 0) ? 0 : register[read_addr_2];

    always @(posedge clk) begin
        if (we && write_addr != 0) begin
            register[write_addr] = write_data;
        end
    end
endmodule