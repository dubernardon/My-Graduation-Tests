module wrapper 
(
  input reset, data_1_en, clock1, clock2,
  input[15:0] data_1,
  output buffer_empty, buffer_full, data_2_valid,
  output[15:0] data_2
);

  reg[2:0] buffer_wr, buffer_rd;
  reg[15:0] buffer_reg [0:7]; // Array
  reg[15:0] data_2_reg;
  reg data_2_valid_reg;

  // WRITE
  always @(posedge clock1, posedge reset) begin
    if (reset == 1'b1) begin
      buffer_wr <= 3'b0;
      buffer_reg[0] <= 16'b0;
      buffer_reg[1] <= 16'b0;
      buffer_reg[2] <= 16'b0;
      buffer_reg[3] <= 16'b0;
      buffer_reg[4] <= 16'b0;
      buffer_reg[5] <= 16'b0;
      buffer_reg[6] <= 16'b0;
      buffer_reg[7] <= 16'b0;
    end
    else begin
      if (data_1_en == 1'b1 && buffer_full == 1'b0) begin
        buffer_reg[buffer_wr] <= data_1;
        buffer_wr <= buffer_wr + 1'b1;
      end
    end
  end

  // READ
  always @(posedge clock2, posedge reset) begin
    if (reset == 1'b1) begin
      buffer_rd <= 3'b0;
      data_2_reg <= 16'b0;
      data_2_valid_reg  <= 1'b0;
    end
    else begin
      if (buffer_empty == 1'b0) begin
        data_2_reg <= buffer_reg[buffer_rd];
        data_2_valid_reg <= 1'b1;
        buffer_rd <= buffer_rd + 1'b1;
      end
      else begin
        data_2_valid_reg <= 1'b0;
      end
    end
  end

  assign buffer_empty = (buffer_rd == buffer_wr) ? 1'b1 : 1'b0;

  assign buffer_full =  (buffer_rd - 3'd1  == buffer_wr) ? 1'b1 : 1'b0;

  assign data_2 = data_2_reg;

  assign data_2_valid = data_2_valid_reg;

  
endmodule