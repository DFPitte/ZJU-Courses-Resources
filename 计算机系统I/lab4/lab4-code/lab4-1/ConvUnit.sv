`include"conv_struct.vh"
module ConvUnit (
    input clk,
    input rst,
    input Conv::data_t in_data,
    input Conv::data_vector kernel,
    input in_valid,
    output in_ready,
    output Conv::result_t result,
    output out_valid,
    input out_ready
);

    // fill the code
    Conv::data_vector shift_data;
    logic shift_out_valid, shift_in_ready;
    logic operator_in_ready;
    //assign in_ready = 1'b1;
        Shift shift_module (
            .clk(clk),
            .rst(rst),
            .in_data(in_data),
            .in_valid(in_valid),
            .in_ready(in_ready),

            .data(shift_data),
            .out_valid(shift_out_valid),
            .out_ready(operator_in_ready)
        );
        ConvOperator conv_operator_module (
        .clk(clk),
        .rst(rst),
        .kernel(kernel),
        .data(shift_data),
        .in_valid(shift_out_valid),
        .in_ready(operator_in_ready),
        .result(result),
        .out_valid(out_valid),
        .out_ready(out_ready)
    );
    
endmodule