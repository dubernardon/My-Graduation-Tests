module dcm 
(
  input clock, reset, update,
  input[2:0] prog_in,
  output clock1, clock2,
  output[2:0] prog_out
);

reg clk1,clk2;
reg[31:0] count_5M, count_CL, clock_prog;
reg[2:0] prog_reg;
wire[31:0] clock_prog_wire;

// Clock rapido
always @(posedge clock, posedge reset) begin
  if (reset == 1'b1) begin
    clk1 <= 1'b0;
    count_5M <= 32'd0;
  end
  else begin
    if(update == 1'b1)begin
      count_5M <= 32'b0;
    end
    if (count_5M == 32'd5000000 - 1) begin
      clk1   <= ~clk1;
      count_5M <= 32'd0;
    end
    else begin
      count_5M <= count_5M + 1'b1;
    end
  end
end

// Clock lento
always @(posedge clock, posedge reset) begin
  if (reset == 1'b1) begin
    clk2 <= 1'b0;
    count_CL <= 32'd0;
  end
  else begin
    if(update == 1'b1)begin
      count_CL<=32'b0;
    end
    else begin
    if (count_CL == clock_prog - 1'b1) begin
      clk2   <= ~clk2;
      count_CL <= 32'd0;
    end
    else begin
      count_CL <= count_CL + 1'b1;
    end
  end
  end
end

always @(posedge clock, posedge reset) begin
  if (reset == 1'b1) begin
    clock_prog <= 32'd5000000;
    prog_reg <= 3'b000;
  end
  else begin
    if (update == 1'b1) begin
      clock_prog <= clock_prog_wire;
      prog_reg <= prog_in;
    end
  end
end

assign clock_prog_wire =  (prog_in == 3'b111) ? 32'd640000000 : 
                          (prog_in == 3'b110) ? 32'd320000000 :
                          (prog_in == 3'b101) ? 32'd160000000 :
                          (prog_in == 3'b100) ?  32'd80000000 :
                          (prog_in == 3'b011) ?  32'd40000000 :
                          (prog_in == 3'b010) ?  32'd20000000 :
                          (prog_in == 3'b001) ?  32'd10000000 : 
                          32'd5000000; 

assign clock1 = clk1;
assign clock2 = clk2;
assign prog_out = prog_reg;

endmodule