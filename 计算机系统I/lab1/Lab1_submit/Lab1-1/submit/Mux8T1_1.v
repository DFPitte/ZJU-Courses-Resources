module Mux8T1_1( 
   input [7:0] I,
   input [2:0] S,
   output O 
);
wire [1:0] Mux4_out;
MUX4T1_1 fir(
   .I0(I[0]),
   .I1(I[1]),
   .I2(I[2]),
   .I3(I[3]),
   .S(S[1:0]),
   .O(Mux4_out[0])
);

MUX4T1_1 sec(
   .I0(I[4]),
   .I1(I[5]),
   .I2(I[6]),
   .I3(I[7]),
   .S(S[1:0]),
   .O(Mux4_out[1])
);


assign O = S[2] ? Mux4_out[1] : Mux4_out[0] ; 
   //your verilog code
   
endmodule
