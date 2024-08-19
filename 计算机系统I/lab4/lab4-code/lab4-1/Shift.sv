`include "conv_struct.vh"

module Shift (
    input clk,
    input rst,
    input Conv::data_t in_data,
    input in_valid,
    output reg in_ready,

    output Conv::data_vector data,  // data是data_vector结构体类型
    output reg out_valid,
    input out_ready
);

    typedef enum logic {RDATA, TDATA} fsm_state;
    fsm_state state_reg;
    Conv::data_t data_reg [Conv::LEN-1:0];  // 临时存储移位数据
    integer i,j;
    
    always@(posedge clk or posedge rst) begin
        if(rst) begin
            state_reg <= RDATA;
            for (i = 0; i < Conv::LEN; i = i + 1) begin
                data_reg[i] = 0;  // 初始化数组
            end
            out_valid <= 0;
            in_ready <= 1;
        end
        else begin
            case(state_reg)
                RDATA: begin
                    out_valid <= 0;
                    if(in_valid && in_ready) begin
                        in_ready <= 0;//停止接受其他数据
                        
                        for(i = 0; i < Conv::LEN-1; i = i + 1) begin
                            data_reg[i] = data_reg[i+1];
                        end
                        data_reg[Conv::LEN-1] = in_data;
                        state_reg <= TDATA;//转移到下一个状态
                    end
                    else begin
                        state_reg <= RDATA;
                    end
                end
                TDATA: begin
                    if(out_ready) begin
                        for(j = 0; j < Conv::LEN; j = j + 1) begin
                            data.data[j] = data_reg[j];
                            //$display("data.data[%0d] = %h", j, data.data[j]);
                        end
                        out_valid <= 1;
                        in_ready <= 1;
                        state_reg <= RDATA;
                    end
                    else begin
                        out_valid <= 0;
                        state_reg <= TDATA;
                    end
                end
                default:  ;
            endcase
        end
    end
endmodule
