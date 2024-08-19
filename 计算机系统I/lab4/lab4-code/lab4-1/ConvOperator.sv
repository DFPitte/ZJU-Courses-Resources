`include "conv_struct.vh"
//import Conv::*;
module ConvOperator(
    input clk,
    input rst,
    input Conv::data_vector kernel,
    input Conv::data_vector data,
    input in_valid,
    output reg in_ready,

    output Conv::result_t result,
    output reg out_valid,
    input out_ready
);

    typedef struct {
        Conv::result_t data;
        logic valid;
    } mid_vector;
    typedef struct {
        Conv::result_t data [Conv::LEN-1:0]/* verilator split_var */;
        logic valid[Conv::LEN-1:0];
    } mid_vector2;
    Conv::result_t vector_stage1 [Conv::LEN-1:0];
    mid_vector vector_stage2;

    typedef enum logic [1:0] {RDATA, WORK, TDATA} fsm_state;
    fsm_state state_reg;

    logic [Conv::WIDTH*2-1:0] products [Conv::LEN-1:0];//127位
    wire [Conv::LEN-1:0] multiply_finish,finished;

    // 实例化乘法器
    reg start_multiply;
    genvar i;
    generate
        for (i = 0; i < Conv::LEN; i = i + 1) begin : mults
            Multiplier #(Conv::WIDTH) mux(
                .rst(rst),
                .clk(clk),
                .multiplicand(data.data[i]),  // 直接访问data_vector的data字段
                .multiplier(kernel.data[i]),  // 直接访问data_vector的data字段
                .start(start_multiply),
                .product(products[i]),
                .finish(multiply_finish[i])
            );
        end
    endgenerate
    Conv::result_t add_tmp [Conv::LEN-1:1] /* verilator split_var */;
    generate
    for(genvar i=1;i<Conv::LEN;i=i+1)begin
        if(i<Conv::LEN/2)begin
            assign add_tmp[i] = add_tmp[i*2] + add_tmp[i*2+1];
        end else begin
            assign add_tmp[i] = stage1_data[(i-Conv::LEN/2)*2] + stage1_data[(i-Conv::LEN/2)*2+1]; 
        end
    end
    endgenerate
    integer j,k,m;
    always @(posedge clk or posedge rst) begin
        if (rst) begin
            state_reg <= RDATA;
            out_valid <= 0;
            in_ready <= 1;
        end else begin
            case (state_reg)
                RDATA: begin
                    out_valid <= 0;//此时停止输出数据
                    if (in_valid && in_ready) begin//如果准备好接受
                        in_ready <= 0;//停止接受其他数据
                        
                        start_multiply <= 1;//开始计算乘法
                        for (j = 0; j < Conv::LEN; j++) begin
                            vector_stage1[j] = 0;
                        end
                        vector_stage2.data = 0;
                        vector_stage2.valid = 0;
                        state_reg <= WORK;//切换至工作状态
                    end
                    else begin
                        state_reg <= RDATA;
                    end
                end
                WORK: begin
                    #50;
                    if (&multiply_finish) begin  // 检查所有乘法器是否完成
                        for (k = 0; k < Conv::LEN; k++) begin
                            vector_stage1[k] = products[k];//将product赋值
                        end
                        state_reg <= TDATA;//切换至传输状态
                    end
                    else begin
                        state_reg <= WORK;
                    end
                end
                TDATA: begin
                    reg [Conv::WIDTH*2-1:0] sum/* verilator split_var */;
                    //$display("sum = %h", sum);
                    vector_stage2.data = sum;
                    vector_stage2.valid = 1;
                    if (out_ready && vector_stage2.valid) begin
                        result = vector_stage2.data;//赋值给最终结果
                        out_valid <= 1;
                        in_ready <= 1;
                        state_reg <= RDATA;
                        
                    end 
                    else begin
                        out_valid <= 0;
                    end
                end
                default: ;
            endcase
        end
    end
endmodule