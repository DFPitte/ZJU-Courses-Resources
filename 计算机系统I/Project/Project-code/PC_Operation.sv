module PC_OP(
    input clk,
    input rstn,
    output [63:0] pc,
    input [63:0] next_pc
);
    logic [63:0] ppc;
    always@(posedge clk or negedge rstn)begin
        if(~rstn)begin
            ppc = 64'b0;
        end
        else begin
        ppc = next_pc;
    end
    end
    assign pc = ppc;
endmodule