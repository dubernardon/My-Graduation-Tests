module dm 
(
  input clock, reset,
  input[1:0] module_d,
  input[2:0] prog,
  input[15:0] data_2,
  output[7:0] an, dec_ddp
);

dspl_drv_NexysA7 DSPL_inst (.reset(reset), .clock(clock), .d1({1'b1, data_2[3:0],1'b0}), .d2({1'b1, data_2[7:4], 1'b0}), .d3({1'b1, data_2[11:8], 1'b0}), .d4({1'b1, data_2[15:12], 1'b0}), .d5(6'b0), .d6({3'b100 ,module_d, 1'b0}), .d7(6'b0), .d8({2'b10, prog, 1'b0}), .dec_cat(dec_ddp), .an(an));
  
endmodule