module top(
  input SW0,
  input SW1,
  input SW2,
  input SW3,
  output LD0
);

  // add connection from FPGA IO to the main
  main ldut( 
        .I0(SW0),
        .I1(SW1),
        .I2(SW2),
        .I3(SW3),
        .O(LD0) 
    );

endmodule