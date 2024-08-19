module Judge(
    input [31:0] a,
    input [31:0] b,
    input do_sub,
    input [31:0] s,
    input c,
    output error
);

    wire [31:0] s_result;
    wire c_result;
    assign {c_result,s_result}=do_sub?{1'b0,a}-{1'b1,b}:{1'b0,a}+{1'b0,b};
    assign error=~((c_result==c)&(s_result==s));
    
endmodule //Judge
