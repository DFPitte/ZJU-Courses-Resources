module ALU_SEL(
    input [1:0] alu_asel,
    input [1:0] alu_bsel,
    input [63:0] reg_data1,
    input [63:0] reg_data2,
    input [63:0] pc,
    input [63:0] imm_val,
    output [63:0] alu_op1,
    output [63:0] alu_op2
);
    reg [63:0] alu_tp1, alu_tp2;
    always @* begin//ld指令将alu_op1设置为reg_data1，将alu_op2设置为imm_val
        alu_tp1 = (alu_asel-1 == 0) ? reg_data1 : pc;  // ALU A 选择
        alu_tp2 = (alu_bsel-1 == 0) ? reg_data2 : imm_val;  // ALU B 选
    end
    assign alu_op1 = alu_tp1;
    assign alu_op2 = alu_tp2;
endmodule