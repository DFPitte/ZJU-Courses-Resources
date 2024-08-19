`include "core_struct.vh"

module Cmp (
    input CorePack::data_t a,
    input CorePack::data_t b,
    input CorePack::cmp_op_enum cmp_op,
    output cmp_res
);

    import CorePack::*;

    reg cmp_result;

    always @* begin
        //$display("a=%h, b=%h, cmp_op=%h", a, b, cmp_op);
        case (cmp_op)
            CMP_EQ: cmp_result = (a == b);
            CMP_NE: cmp_result = (a != b);
            CMP_LT: begin
            if(a == 0 && $signed(b)>0)cmp_result = 1;
            else
            cmp_result = ($signed(a) < $signed(b));
            end
            CMP_GE: cmp_result = ($signed(a) >= $signed(b));
            CMP_LTU: cmp_result = ($unsigned(a) < $unsigned(b)); // 无符号比较
            CMP_GEU: cmp_result = ($unsigned(a) >= $unsigned(b)); // 无符号比较
            default: cmp_result = 0; // 默认情况下，输出0
        endcase
    end

    assign cmp_res = cmp_result;

endmodule
