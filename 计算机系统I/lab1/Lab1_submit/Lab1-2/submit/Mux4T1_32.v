module Mux4T1_32(
    input [31:0] I0,
    input [31:0] I1,
    input [31:0] I2,
    input [31:0] I3,
    input [1:0] S,
    output [31:0] O
);

    //fill your code
    assign O = S[1] ? (S[0]?I0:I1) : (S[0]?I2:I3);
endmodule

