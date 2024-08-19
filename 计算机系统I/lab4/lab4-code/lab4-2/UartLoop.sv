`include "uart_struct.vh"

module UartLoop(
    input wire clk,
    input wire rstn,
    Decoupled_ift.Slave uart_rdata,
    Decoupled_ift.Master uart_tdata,

    input wire UartPack::uart_t debug_data,
    input wire debug_send,
    output wire UartPack::uart_t debug_rdata,
    output wire UartPack::uart_t debug_tdata
);
    import UartPack::*;

    uart_t rdata;
    logic rdata_valid = 0, send_debug_data = 0;

    always_ff @(posedge clk or negedge rstn) begin
        if (!rstn) begin
            rdata_valid <= 0;
            send_debug_data <= 0;
        end else begin
            if (debug_send) begin//如果有debug数据
                rdata <= debug_data;//将debug数据赋值给rdata
                rdata_valid <= 1;
                send_debug_data <= 1;
            end

            else if (uart_rdata.valid && !send_debug_data) begin//如果有uart数据
                rdata <= uart_rdata.data;//将uart数据赋值给rdata
                rdata_valid <= 1;
            end

            if (uart_tdata.ready && rdata_valid) begin//如果uart_tdata准备好了
                rdata_valid <= 0;
                send_debug_data <= 0;
            end
        end
    end
    assign uart_tdata.data = rdata;//将rdata赋值给uart_tdata
    assign uart_tdata.valid = rdata_valid;

    assign uart_rdata.ready = !rdata_valid;

    assign debug_rdata = rdata;
    assign debug_tdata = uart_tdata.valid ? rdata : 0;  // Show sent data only

endmodule