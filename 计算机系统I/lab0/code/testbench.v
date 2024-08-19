module Testbench;

    reg I0,I1,I2,I3;
    wire O;

    initial begin
        //your test sample
        I0=1'b0;I1=1'b0;I2=1'b0;I3=1'b0;
        #5;
        I0=1'b0;I1=1'b0;I2=1'b0;I3=1'b1;
        #5;
        I0=1'b0;I1=1'b0;I2=1'b1;I3=1'b0;
        #5;
        I0=1'b0;I1=1'b0;I2=1'b1;I3=1'b1;
        #5;
        I0=1'b0;I1=1'b1;I2=1'b0;I3=1'b0;
        #5;
        I0=1'b0;I1=1'b1;I2=1'b0;I3=1'b1;
        #5;
        I0=1'b0;I1=1'b1;I2=1'b1;I3=1'b0;
        #5;
        I0=1'b0;I1=1'b1;I2=1'b1;I3=1'b1;
        #5;
        I0=1'b1;I1=1'b0;I2=1'b0;I3=1'b0;
        #5;
        I0=1'b1;I1=1'b0;I2=1'b0;I3=1'b1;
        #5;
        I0=1'b1;I1=1'b0;I2=1'b1;I3=1'b0;
        #5;
        I0=1'b1;I1=1'b0;I2=1'b1;I3=1'b1;
        #5;
        I0=1'b1;I1=1'b1;I2=1'b0;I3=1'b0;
        #5;
        I0=1'b1;I1=1'b1;I2=1'b0;I3=1'b1;
        #5;
        I0=1'b1;I1=1'b1;I2=1'b1;I3=1'b0;
        #5;
        I0=1'b1;I1=1'b1;I2=1'b1;I3=1'b1;
        #5;
        $finish;
    end
    //此处使用脚本对输入进行排列组合
    main dut( 
        .I0(I0),
        .I1(I1),
        .I2(I2),
        .I3(I3),
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
