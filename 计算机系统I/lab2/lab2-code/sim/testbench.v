module Testbench;

    reg [31:0] a;
    reg [31:0] b;
    reg do_sub;
    wire [31:0] s;
    wire c;

    integer i;
    initial begin
        for(i = 0; i < 20; i = i + 1) begin
            a = $random;
            b = $random;
            do_sub = a[0];
            #200;
        end
        $finish;
    end

    AddSubers #(
        .LENGTH(32)
    ) add_sub (
        .a(a),
        .b(b),
        .do_sub(do_sub),
        .s(s),
        .c(c)
    );

    `ifdef VERILATE
        reg clk;
        initial begin
            clk=1'b0;
        end
        always begin
            clk=~clk;
            #5;
        end
        
        wire error;
        Judge judge(
            .a(a),
            .b(b),
            .do_sub(do_sub),
            .s(s),
            .c(c),
            .error(error)
        );

        always@(posedge clk)begin
            if(error)begin
                $display("a=%d, b=%d, do_sub=%d, s=%d, c=%d, error", a, b, do_sub, s, c);
            end
        end

		initial begin
			$dumpfile({`TOP_DIR,"/Testbench.vcd"});
			$dumpvars(0,dut);
			$dumpon;
		end
    `endif
    
endmodule
