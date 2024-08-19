module pc_upd(
    input clk,
    input rstn,
    input [63:0] next_pc,

    output [63:0] pc
);
    reg [63:0] ppc;
    always@(posedge clk or negedge rstn)begin
        if(~rstn)begin
            ppc = 64'b0;
        end
        else begin
        ppc = next_pc;
        //$display("pc=%h",pc);
    end
    end
    assign pc = ppc;
endmodule