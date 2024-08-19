module Cnt #(
    parameter BASE = 10,
    parameter INITIAL = 0
) (
    
    input clk,
    input rstn,
    input low_co,
    input high_rst,
    input en,
    output co,
    output reg [3:0] cnt
);
    reg [3:0] out;
    always @(posedge clk or negedge rstn) begin
        if(en)begin
            if(!rstn) begin
            out <= INITIAL[3:0];
            end
            else if(high_rst) begin
            out <= 0;
            end
            else if(low_co) begin
            if(out == BASE-1) begin
                out <= 0;
            end 
            else begin
                out <= out + 1;
            end
            end 
        end 
        
        end
    assign co = (out == BASE-1) ? 1 : 0;
    assign cnt = out;

endmodule