module branch_taken(
    input clk,
    input rstn,
    input [63:0] pc,
    input branch_taken,
    input jump_taken,
    input [63:0] alu_res,
    input [63:0] imm_val,

    output reg [63:0] next_pc
);
    logic [63:0] next_ppc;
    always @(negedge clk or negedge rstn) begin
        if(~rstn) begin
            next_pc = 64'b0;
        end
        else begin
        if (branch_taken) begin
            next_pc = alu_res;
        end
        else if(jump_taken) begin
            next_pc = pc + imm_val;
        end
        else begin
            next_pc = pc + 4;  // 下一条指令
        end
        end
        end
endmodule