module Testbench;

    reg [7:0] I;
    reg [2:0] S;
    wire O;

    initial begin
        I = 8'b10001011;
        S = 3'b000;
        repeat (8) begin
            #10
            S = S + 1;
        end
        #10
        $finish;
    end

    Mux8T1_1 dut( 
        .I(I),
        .S(S),
        .O(O) 
    );

    `ifdef VERILATE
		initial begin
			$dumpfile({`TOP_DIR,"/Testbench.vcd"});
			$dumpvars(0,dut);
			$dumpon;
		end
    `endif
    
endmodule
