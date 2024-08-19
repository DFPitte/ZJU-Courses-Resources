module Adders #(
    parameter LENGTH = 32
)(
    input [LENGTH-1:0] a,
    input [LENGTH-1:0] b,
    input c_in,
    output [LENGTH-1:0] s,
    output c_out
);


    //fill your code here
    wire [LENGTH-1:0] sum;
    wire [LENGTH-2:0] carry_out;

    Adder add1(
        .a(a[0]),
        .b(b[0]),
        .c_in(c_in),
        .s(sum[0]),
        .c_out(carry_out[0])
    );
    genvar i;
    generate
        for (i = 1; i < LENGTH - 1; i = i + 1) begin  
            Adder adder(
                .a(a[i]),
                .b(b[i]),
                .c_in(carry_out[i-1]),  
                .s(sum[i]),
                .c_out(carry_out[i])
            );
        end
    endgenerate
    Adder adder(
        .a(a[LENGTH-1]),
        .b(b[LENGTH-1]),
        .c_in(carry_out[LENGTH-2]),
        .s(sum[LENGTH-1]),
        .c_out(c_out)
    );
    assign s = sum[LENGTH-1:0];  

endmodule
