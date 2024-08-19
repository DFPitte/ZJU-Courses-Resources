`include "core_struct.vh"
module mem_ope(
    input clk,
    input rst,
    input re_mem,
    input we_mem,
    input [2:0] shift, // Shift in bytes
    input [2:0] memop,
    input [63:0] rdata,
    input [63:0] wdata,

    output [63:0] mem_rdata,
    output [63:0] mem_wdata
);
    reg [63:0] read_data, write_data;
    import CorePack::*;
    always@(posedge clk) begin
        if(re_mem) begin
            // Apply shift to the 
            reg [63:0] shifted_rdata = rdata;  // Shift rdata right by 'shift' bytes
            //$display("rdata=%h", rdata);
            
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
        end else if(we_mem) begin
            // Apply shift to the wdata
            reg [63:0] shifted_wdata = wdata ;  // Shift wdata right by 'shift' bytes
            case (memop)
                MEM_D:  write_data = shifted_wdata;
                MEM_W:  write_data = {32'b0, shifted_wdata[31:0]};
                MEM_H:  write_data = {48'b0, shifted_wdata[15:0]};
                MEM_B:  write_data = {56'b0, shifted_wdata[7:0]};
                default: write_data = 64'd0;
            endcase
            //$display("write_data=%h", write_data);
        end
    end
    assign mem_rdata = read_data;
    assign mem_wdata = write_data;
endmodule
