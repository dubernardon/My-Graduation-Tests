module top 
(
  input reset, clock, start_f, start_t, stop_f_t, update,
  input [2:0] prog,
  output [5:0] led,
  output [7:0] an, dec_ddp
);

  wire start_f_ed, start_t_ed, stop_f_t_ed, update_ed;

  edge_detector startF(.rising(start_f_ed), .din(start_f), .clock(clock), .reset(reset));
  edge_detector startT(.rising(start_t_ed), .din(start_t), .clock(clock), .reset(reset));
  edge_detector stopFT(.rising(stop_f_t_ed), .din(stop_f_t), .clock(clock), .reset(reset));
  edge_detector updateED(.rising(update_ed), .din(update), .clock(clock), .reset(reset));
  

  reg[2:0] EA;
  wire buffer_full, buffer_empty, data_2_valid;
  wire f_en, t_en;
  wire clock1, clock2;
  wire data_1_en, f_valid, t_valid;
  wire[15:0] f_out, t_out, data_1, data_2;
  wire[1:0] module_d, module_wire;
  reg[1:0] module_reg;
  wire[2:0] prog_out;


  // Maquina de Estados
  always @(posedge clock, posedge reset) begin
    if (reset == 1'b1)begin
      EA <= 3'b000;
    end
    else begin
      if (EA == 3'b000) begin   // IDLE
        if (start_f_ed == 1'b1) begin
          EA <= 3'b001;
        end
        if (start_t_ed == 1'b1) begin
          EA <= 3'b010;
        end
      end
      if (EA == 3'b001) begin   // Start Fibonacci (S_COMM_F)
        if (buffer_full == 1'b1) begin
          EA <= 3'b011;
        end
        if (stop_f_t_ed == 1'b1) begin
          EA <= 3'b101;
        end
      end
      if (EA == 3'b010) begin   // Start Timer (S_COMM_T)
        if (buffer_full == 1'b1) begin
          EA <= 3'b100;
        end
        if (stop_f_t_ed == 1'b1) begin
          EA <= 3'b101;
        end
      end
      if (EA == 3'b011) begin   // Wait Fibonacci (S_WAIT_F)
        if (!buffer_full == 1'b1) begin
          EA <= 3'b001;
        end
        if (stop_f_t_ed == 1'b1) begin
          EA <= 3'b101;
        end
      end
      if (EA == 3'b100) begin   // Wait Timer (S_WAIT_T)
        if (!buffer_full == 1'b1) begin
           EA <= 3'b010;
        end
        if (stop_f_t_ed == 1'b1) begin
          EA <= 3'b101;
        end
      end
      if (EA == 3'b101) begin   // Buffer Empty (S_BUF_EMPTY)
        if ((buffer_empty == 1'b1 && !data_2_valid == 1'b1)) begin
          EA <= 3'b000;
        end
      end
    end
  end


  // Flip Flop Module
  always @(posedge clock, posedge reset) begin
    if (reset == 1'b1) begin
      module_reg <= 2'b00;
    end
    else begin
      if (!(EA == 3'b101)) begin
        module_reg <= module_wire;
      end
    end
  end


  assign f_en = (EA == 3'b001 && !buffer_full) ? 1'b1 : 1'b0;
  assign t_en = (EA == 3'b010 && !buffer_full) ? 1'b1 : 1'b0;

  assign data_1_en = t_valid | f_valid;

  assign data_1 = (f_valid == 1'b1) ? f_out :
                  (t_valid == 1'b1) ? t_out :
                  16'b0;

  assign module_wire =  (EA == 3'b001 || EA == 3'b011) ? 2'b01 :
                        (EA == 3'b010 || EA == 3'b100) ? 2'b10 :
                        2'b00;
  assign module_d = (data_2_valid == 1'b1) ? module_reg : 2'b00;

  assign led =  (EA == 3'b000) ? 6'b000001 :
                (EA == 3'b001) ? 6'b000010 :
                (EA == 3'b010) ? 6'b000100 :
                (EA == 3'b011) ? 6'b001000 :
                (EA == 3'b100) ? 6'b010000 :
                6'b100000;

  fibonacci FIB_inst(.reset(reset), .clock(clock1), .f_en(f_en), .f_valid(f_valid), .f_out(f_out));

  timer TIM_inst(.reset(reset), .clock(clock1), .t_en(t_en), .t_valid(t_valid), .t_out(t_out));

  dcm DCM_inst(.reset(reset), .clock(clock), .update(update_ed), .prog_in(prog), .prog_out(prog_out), .clock1(clock1), .clock2(clock2));
  
  dm DM_inst(.reset(reset), .clock(clock), .an(an), .dec_ddp(dec_ddp), .module_d(module_d), .prog(prog_out), .data_2(data_2));

  wrapper WRP_inst(.reset(reset), .clock1(clock1), .clock2(clock2), .data_1_en(data_1_en), .data_1(data_1), .data_2(data_2), .data_2_valid(data_2_valid), .buffer_empty(buffer_empty), .buffer_full(buffer_full));

endmodule