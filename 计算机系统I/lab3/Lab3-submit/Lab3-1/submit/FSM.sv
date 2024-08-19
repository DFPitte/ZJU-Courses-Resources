module FSM(
    input rstn,
    input clk,
    input a,
    input b,
    output [1:0] state
);

     typedef enum logic [1:0] {S0,S1,S2,S3} fsm_state;
     fsm_state state1;
     always @(posedge clk or negedge rstn) begin
        if(~rstn) begin
            state1 <= S0;
        end
        else begin
            case(state1)
                S0: begin
                    if(a) begin
                        state1 <= S1;
                    end
                    else begin
                        state1 <= S0;
                    end
                end
                S1: begin
                    if(a) begin
                        state1 <= S2;
                    end
                    else if(a == 0 && b == 1)begin
                        state1 <= S0;
                    end
                    else begin
                        state1 <= S1;
                    end
                end
                S2: begin
                    if(a) begin
                        state1 <= S3;
                    end
                    else if(b)begin
                        state1 <= S0;
                    end
                    else begin
                        state1 <= S2;
                    end
                end
                S3: begin
                    state1 <= S3;
                end
                default: state1 <= S0;
            endcase
        end
     end
     assign state = state1;
endmodule