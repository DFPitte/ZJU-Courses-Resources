module Immgen(
    input [31:0] inst,
    input [2:0] immgen_op,
    output [63:0] imm_val

);
reg [63:0] reg_val;
always @(*) begin
        case (immgen_op)
            3'b001: reg_val = {{52{inst[31]}}, inst[31:20]};  // I-Type
            3'b010: reg_val = {{52{inst[31]}}, inst[31:25], inst[11:7]};  // S-Type
            3'b011: reg_val = {{52{inst[31]}}, inst[7], inst[30:25], inst[11:8], 1'b0};  // B-Type
            3'b100: reg_val = {inst[31:12], 44'b0};  // U-Type
            3'b101: reg_val = {{44{inst[31]}}, inst[19:12], inst[20], inst[30:21], 1'b0};  // J-Type
            default: reg_val = 64'b0;  // Default case
        endcase
    end
assign imm_val = reg_val;
endmodule