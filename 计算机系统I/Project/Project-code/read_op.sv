`include "core_struct.vh"
module read_op(
    input clk,
    input rst,
    input re_mem,
    input [2:0] shift, // Shift in bytes
    input [2:0] memop,
    input [63:0] rdata,

    output [63:0] mem_rdata
);
    import CorePack::*;
    reg [63:0] read_data;
    always@(*)begin
        //if(re_mem) begin
            reg [63:0] shifted_rdata = rdata>>(shift*8);
            case (memop)
                MEM_D: read_data = shifted_rdata;
                MEM_W: read_data = {{32{shifted_rdata[31]}}, shifted_rdata[31:0]};
                MEM_H: read_data = {{48{shifted_rdata[15]}}, shifted_rdata[15:0]};
                MEM_B: read_data = {{56{shifted_rdata[7]}}, shifted_rdata[7:0]};
                MEM_UW: read_data = {32'b0, shifted_rdata[31:0]};
                MEM_UH: read_data = {48'b0, shifted_rdata[15:0]};
                MEM_UB: read_data = {56'b0, shifted_rdata[7:0]};
                default: read_data = 64'd0;
            endcase
            //$display("read_data=%h", read_data);
        end
    //end
    assign mem_rdata = read_data;
endmodule