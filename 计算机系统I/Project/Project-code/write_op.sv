`include "core_struct.vh"
module write_op(
    input clk,
    input rst,
    input we_mem,
    input [2:0] shift, // Shift in bytes
    input [2:0] memop,
    input [63:0] wdata,

    output [63:0] mem_wdata 
);
    import CorePack::*;
    reg [63:0] write_data,shifted_wdata;
    always@(*)begin
            case (memop)
                MEM_D:  write_data = wdata;
                MEM_W:  write_data = {32'b0, wdata[31:0]};
                MEM_H:  write_data = {48'b0, wdata[15:0]};
                MEM_B:  write_data = {56'b0, wdata[7:0]};
                default: write_data = 64'd0;
            endcase
            shifted_wdata = write_data<<(shift*8);
    //end
    end
    assign mem_wdata = shifted_wdata;
endmodule