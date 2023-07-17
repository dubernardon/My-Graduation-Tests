module fibonacci 
(
  input reset, clock, f_en,
  output f_valid,
  output[15:0] f_out
);

  reg[15:0] ant, res;
  reg f_valid_reg;
  reg hold;

  always @(posedge clock, posedge reset) begin
    if (reset == 1'b1) begin
      ant <= 16'b0;
      res <= 16'b0;
      f_valid_reg <= 1'b0;
      hold <= 1'b0;
    end
    else begin
      if(f_en == 1)begin
        f_valid_reg <= 1'b1;
        if (hold == 1'b1) begin
          hold <= 1'b0;
        end
        else begin
          if (res == 16'b0) begin
            res <= 16'd1;
          end
          else begin
            res <= res + ant;
            ant <= res;
          end
        end
      end
      else begin
        hold <= 1'b1;
        f_valid_reg <= 1'b0;
      end
    end
  end


  assign f_valid = f_valid_reg;
  assign f_out = res;

endmodule