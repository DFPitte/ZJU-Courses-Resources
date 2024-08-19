module AddSubers #(
    parameter LENGTH = 32
)(
    input [LENGTH-1:0] a,
    input [LENGTH-1:0] b,
    input do_sub,
    output [LENGTH-1:0] s,
    output c
);
    wire [LENGTH-1:0] inverted_b;
    assign inverted_b = (do_sub) ? ~b + 1: b;
    wire tmp;

    Adders #(LENGTH) add_sub (
        .a(a),
        .b(inverted_b),
        .s(s),
        .c_in(0),
        .c_out(tmp)
    );
    assign c = tmp;
endmodule