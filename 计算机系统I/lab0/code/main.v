module main( 
   input I0,
   input I1,
   input I2,
   input I3,
   output O 
);

   //your verilog code

assign O = (I0&I2)|(~I1&~I3)|(~I0&I1&I3)|(I3&I2);


endmodule
