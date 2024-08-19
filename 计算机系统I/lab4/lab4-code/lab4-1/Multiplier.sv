`include"conv_struct.vh"
module Multiplier #(
    parameter LEN = 64
) (
    input clk,
    input rst,
    input [LEN-1:0] multiplicand,
    input [LEN-1:0] multiplier,
    input start,
    
    output [LEN*2-1:0] product,
    output finish
);

    // fill the code
    localparam PRODUCT_LEN = LEN*2;
    logic [LEN-1:0] multiplicand_reg;
    logic [PRODUCT_LEN-1:0] product_reg;

    //localparam CNT_LEN = $clog2(LEN);
    
    localparam CNT_NUM = LEN - 1;
    typedef enum [1:0] {IDLE, WORK, FINAL} fsm_state;
    fsm_state fsm_state_reg;
    integer work_cnt;
    logic [LEN:0] high_product_tmp;
    logic [LEN-1:0] high_product;
    logic [LEN-1:0] low_product;
    // fill the code
    reg finish_tmp;
    always@(posedge clk)begin
        if(rst)begin
            fsm_state_reg <= IDLE;
            product_reg = 0;
            high_product = 0;
            low_product = 0;
        end
        else begin
        case (fsm_state_reg)
            IDLE:begin
                if(start)begin
                    product_reg = 0;
                    high_product = 0;
                    high_product_tmp = 0;
                    low_product = multiplier; 
                    fsm_state_reg <= WORK;
                    work_cnt = 0;
                    finish_tmp = 0;
                end
            end
            WORK:begin
                
                if(work_cnt == LEN)begin
                    fsm_state_reg <= FINAL;
                end
                else begin
                    work_cnt = work_cnt + 1;
                    high_product_tmp = 0;
                    fsm_state_reg <= WORK;
                    if (low_product[0] == 1) begin
                    high_product_tmp = high_product + multiplicand;
                end else begin
                    high_product_tmp[LEN-1:0] = high_product;
                end
                {high_product, low_product} = {high_product_tmp[LEN-1:0], low_product} >> 1;
                high_product[LEN-1] = high_product_tmp[LEN];
                end
            end
            FINAL:begin
                //$display("3");
                finish_tmp = 1;
                product_reg = {high_product, low_product};
                //$display("product_reg = %h", product_reg);
                fsm_state_reg <= IDLE;
            end
            default: ;
        endcase 
        end
    end
    assign finish = finish_tmp;
    assign product = product_reg;
endmodule