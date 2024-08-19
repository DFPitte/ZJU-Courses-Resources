module wb_sel(
    input clk,
    input [1:0] wb_sel,
    input [63:0] alu_res,
    input [63:0] rdata,
    input [63:0] pc,
    output [63:0] wb_val
);
    reg [63:0] wb_tmp;
    always @(*) begin
        case (wb_sel)
            2'b00: wb_tmp = 0;  
            2'b01: wb_tmp = alu_res;  // ALU结果
            2'b10: wb_tmp = rdata;  // 内存读取结果
            2'b11: wb_tmp = pc + 4;  // PC值
            default: wb_tmp = 64'bx;
        endcase
        //$display("rdata=%h,wb_sel=%h", rdata,wb_sel);
    end
    assign wb_val = wb_tmp;
endmodule