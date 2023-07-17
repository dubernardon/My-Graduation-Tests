module timer 
(
  input reset, clock, t_en,
  output t_valid,
  output[15:0] t_out
);

  reg[15:0] res;
  reg t_valid_reg;
  reg hold;

  always @(posedge clock, posedge reset) begin
    if (reset == 1'b1) begin
      res <= 16'b0;
      t_valid_reg <= 1'b0;
      hold <= 1'b0;
    end
    else begin
      if(t_en == 1'b1)begin
        t_valid_reg <= 1'b1;
        if (res == 16'b0) begin
          res <= 16'd1;
        end
        if (hold) begin
          hold <= 1'b0;
        end
        else begin
          res <= res + 1'b1;
        end
      end
      else begin
        hold <= 1'b1;
        t_valid_reg <= 1'b0;
      end
    end
  end

  assign t_valid = t_valid_reg;
  assign t_out = res;

endmodule