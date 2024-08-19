module Cnt2num #(
    parameter BASE = 24,
    parameter INITIAL = 16
)(
    input clk,
    input rstn,
    input high_rst,
    input low_co,
    input en,
    output co,
    output [7:0] cnt
);

    localparam HIGH_BASE = 10;
    localparam LOW_BASE  = 10;
    localparam HIGH_INIT = INITIAL/10;
    localparam LOW_INIT  = INITIAL%10;
    localparam HIGH_CO   = (BASE-1)/10;
    localparam LOW_CO    = (BASE-1)%10;
    
    // fill the code
    reg in_high_rst,in_low_co,high_co;
    Cnt #(LOW_BASE, LOW_INIT) cnt_low(
        .clk(clk),
        .rstn(rstn),
        .low_co(1),
        .high_rst(in_high_rst),
        .en(en),
        .co(in_low_co),
        .cnt(cnt[3:0])
    );
    Cnt #(HIGH_BASE, HIGH_INIT) cnt_high(
        .clk(clk),
        .rstn(rstn),
        .low_co(in_low_co),
        .high_rst(in_high_rst),
        .en(en),
        .co(high_co),
        .cnt(cnt[7:4])
    );
    assign in_high_rst = (cnt[7:4] == HIGH_CO[3:0] && cnt[3:0] == LOW_CO[3:0]) ? 1'b1 : 1'b0;
    //当达到23时停止，high_rst=1,表示两个cnt全部复位
    assign co = (cnt[7:4] == HIGH_CO[3:0] && cnt[3:0] == LOW_CO[3:0]) ? 1'b1 : 1'b0;  
    //当达到23时停止，co也需置为1
endmodule