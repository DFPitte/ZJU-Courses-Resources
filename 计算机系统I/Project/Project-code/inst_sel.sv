module inst_sel(
    input [63:0] in,
    input [63:0] pc,

    output [31:0] inst
);
    reg [31:0] tmp;
    always @(*)begin
        tmp = (pc%8==0)? in[31:0] : in[63:32];
    end
    assign inst = tmp;
endmodule