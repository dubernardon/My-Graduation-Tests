module ctrl_microondas 
(
  // Declaração das portas
    input clock, reset, start, stop, pause, porta, mais, menos, potencia, sec_mod,
    input [1:0] min_mod,
    output [7:0] an, 
    output [7:0] dec_cat,
    output [2:0] potencia_rbg
);

//limpando sinais
  wire start_ed, pause_ed, stop_ed, mais_ed, menos_ed;
  edge_detector operationDetectorStart (.rising(start_ed), .din(start), .clock(clock), .reset(reset));
  edge_detector operationDetectorStop (.rising(stop_ed), .din(stop), .clock(clock), .reset(reset));
  edge_detector operationDetectorPause (.rising(pause_ed), .din(pause), .clock(clock), .reset(reset));
  edge_detector operationDetectorMais (.rising(mais_ed), .din(mais), .clock(clock), .reset(reset));
  edge_detector operationDetectorMenos (.rising(menos_ed), .din(menos), .clock(clock), .reset(reset));

  reg [1:0] EA, PE;
  reg [1:0] potencia_atual;
  reg [6:0] min, sec;
  wire done, pause_timer, start_timer;
  wire [2:0] potencia_rgb_comb;
  wire [7:0] dec_cat_potencia; 
  wire [7:0] display;

    //maquina de estados
	  always @(posedge clock or posedge reset)
    begin
      if(reset == 1'b1)begin //mesmo sendo um circuito sequencial, foi optado por tratar por combinacional (PE->EA)
        PE <= 2'b00;
        EA <= 2'b00;
      end
      else begin
        EA <= PE;
        if(EA ==  2'b00)begin
          if(start_ed == 1 && porta == 0)begin
            PE <= 2'b11;
          end
        end
        if(EA == 2'b01)begin
          if(pause_ed == 1 || porta == 1)begin
              PE <= 2'b10;
          end
          if(stop_ed == 1 || done == 1)begin 
              PE <= 2'b00; 
          end
        end
        if(EA == 2'b10 ) begin
          if(stop_ed == 1) begin
              PE <= 2'b00;
          end
          if((pause_ed == 1 || start_ed == 1) && porta == 0)begin
              PE <= 2'b01;
          end
        end
        if (EA == 2'b11) begin
          if (done == 1) begin
            PE <= 2'b11;
          end
          else begin
            PE <= 2'b01;
          end
        end
      end
    end

    // Botoes mais e menos minutos e segundos
    always @(posedge clock or posedge reset)
    begin
      if(reset == 1'b1)begin
        min <= 6'b0;
        sec <= 6'b0;
      end
      else begin
      if(EA ==  2'b00) begin
        // Botao MAIS
        if (mais_ed == 1 && potencia == 0) begin
          // MAIS Minutos
          if(min_mod[1] == 1)begin
            if(min >= 7'b1011010) begin //90
              min <= 7'b1100011;
              sec <=  6'b111011;
            end
            else begin
            min <= min + 6'b001010;
            end
          end
          else if(min_mod[0] == 1)begin
            if(min >= 7'b1100011)begin //99
              min <= 7'b1100011;
              sec <=  6'b111011;
            end
            else begin
            min <= min + 6'b000001;
            end
          end
          // MAIS Segundos
          else if(sec_mod == 1)begin
            if(sec >= 6'b110010 && min == 7'b1100011)begin //50  99
                sec <= 6'b111011;
              end
            else if (sec >= 6'b110010) begin //50
              min <= min + 6'b000001;
              sec <= sec - 6'b110010; 
            end
            else begin
              sec <= sec + 6'b001010;
            end
          end
          else begin
            if(sec >= 6'b111011 && min == 7'b1100011)begin //59  99
              sec <= 6'b111011;
            end
            else if (sec >= 6'b111011) begin //59
              min <= min + 6'b000001;
              sec <= 6'b000000; 
            end
            else begin
              sec <= sec + 6'b000001;
            end
          end
        end
        // Botao Menos
        if (menos_ed == 1 && potencia == 0) begin
          // MENOS Minutos
          if(min_mod[1] == 1'b1)begin
            if (min < 6'b001010) begin //10
              min <= 6'b0;
              sec <= 6'b0;
            end
            else begin
            min <= min - 6'b001010;
            end
          end
          else if(min_mod[0] == 1'b1)begin
            if (min < 6'b000001) begin 
              min <= 6'b0;
              sec <= 6'b0;
            end
            else begin
            min <= min - 6'b000001;
            end
          end
          // MENOS Segundos
          else if(sec_mod == 1)begin
            if (sec < 6'b001010 && min == 6'b0) begin
              sec <= 6'b0;
            end
            else if (sec < 6'b001010) begin 
              sec <= sec + 6'b110010;
              min <= min - 1;
            end
            else begin
            sec <= sec - 6'b001010;
            end
          end
          else begin
            if (sec == 6'b0 && min == 6'b0) begin
              sec <= 6'b0; 
            end
            else if (sec == 6'b000000) begin
              sec <= 6'b111011; //59
              min <= min - 1;
            end
            else begin
              sec <= sec - 6'b000001;
            end
          end
        end
      end
      if (EA == 2'b01) begin
        min <= 6'b0;
        sec <= 6'b0;
      end
      end
    end

    // Botoes mais e menos potencia
    always @(posedge clock or posedge reset)
    begin
      if(reset == 1'b1)begin
        potencia_atual <= 2'b0;
      end
      else if(EA ==  2'b00) begin
        // Botao MAIS
        if (mais_ed == 1 && potencia == 1) begin
          if(potencia_atual < 2'b10)begin
            potencia_atual <= potencia_atual + 1'b1;
          end
        end
        // Botao Menos
        if (menos_ed == 1 && potencia == 1) begin
          if(potencia_atual > 2'b00)begin
            potencia_atual <= potencia_atual - 1'b1;
          end
        end
      end
    end

  assign start_timer = (EA == 2'b11 || EA == 2'b01) ? 1'b1 : 1'b0;
  assign pause_timer = (EA == 2'b10) ? 1'b1 : 1'b0;

  assign potencia_rbg = ( EA == 2'b01 ) ? potencia_rgb_comb : 3'b000;
  assign potencia_rgb_comb = (potencia_atual == 2'b00) ? 3'b001 :
                              (potencia_atual == 2'b01) ? 3'b010 :
                              3'b100 ;

  assign dec_cat = (an[5] == 1'b0 ) ? dec_cat_potencia : display;
  assign dec_cat_potencia = (potencia_atual == 2'b00) ? 8'b11101111 :
                            (potencia_atual == 2'b01) ? 8'b11111101 :
                            8'b01111111 ;

  timer tempo(.clock(clock), .reset(reset), .start(start_timer), .stop(stop_ed), .pause(pause_timer), .an(an), .sec(sec), .min(min), .dec_cat(display), .done(done));

endmodule