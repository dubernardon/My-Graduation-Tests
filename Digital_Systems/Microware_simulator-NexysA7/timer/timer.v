module timer
#(parameter HALF_MS_COUNT = 50000 *1000 )//50000 *1000)
(  
  // Declaração das portas
  input clock, reset, start, stop, pause,
  input [6:0] min, sec,
  output done,
  output [7:0] an, dec_cat
);

  wire pause_ed, start_ed, stop_ed;
  edge_detector operationDetectorPause (.rising(pause_ed), .din(pause), .clock(clock), .reset(reset));
  edge_detector operationDetectorStart (.rising(start_ed), .din(start), .clock(clock), .reset(reset));
  edge_detector operationDetectorStop (.rising(stop_ed), .din(stop), .clock(clock), .reset(reset));

    // Declaração dos sinais
    reg [6:0] sec_left, min_left;
    reg [2:0] EA, PE;
    wire [3:0] sec_uni, sec_dec, min_uni, min_dec;
  
    // Divisor de clock para gerar o clk1seg
    reg clk1seg;
    reg [31:0] count_50M;
  
    // 1KHz clock generation
    always @(posedge clock or posedge reset)
    begin
      if (reset == 1'b1) begin
        clk1seg   <= 1'b0;
        count_50M <= 32'd0;
      end
      else begin
        if (count_50M == HALF_MS_COUNT-1) begin
          clk1seg   <= ~clk1seg;
          count_50M <= 32'd0;
        end
        else begin
          count_50M <= count_50M + 1;
        end
      end
    end

    // Máquina de estados para determinar o estado atual (EA)
    //idle = 0;
    //cd = 1;
    //paused = 2;
    always @(posedge clock or posedge reset)
    begin
      if(reset==1'b1)begin
        PE <= 2'b00;
        EA <= 2'b00;
      end
      else begin
        EA <= PE;
        if(EA ==  2'b00)begin
          if(start_ed==1)begin
            PE <= 2'b01;
          end
        end
        if(EA == 2'b01)begin
          if(pause_ed == 1)begin
            PE <= 2'b10;
          end
          if(stop_ed == 1 || sec_left == 6'b0 && min_left== 6'b0)begin 
            PE <= 2'b00; 
          end
        end
        if(EA == 2'b10 ) begin
          if(stop_ed == 1) begin
            PE <= 2'b00;
          end
          if(pause_ed == 1 || start_ed == 1)begin
            PE <= 2'b01;
          end
        end
      end
    end

    // Decrementador de tempo (minutos e segundos)
    always @(posedge clk1seg or posedge reset)
    begin
      if(reset==1'b1)begin
        sec_left<=7'b0;
        min_left<=7'b0;
      end
      else begin
        if(EA==2'b00)begin
          if(sec >7'b0111011)begin
            sec_left <= 7'b0111011;
          end
          else begin
            sec_left<=sec;
          end
          if(min > 7'b1100011)begin
            min_left <=7'b1100011;
          end
          else begin 
            min_left<=min;
          end       
        end
        if(EA==2'b01)begin
          if(sec_left>0)begin
            sec_left<=sec_left-1;
          end
          if(sec_left==0 && min_left>0)begin
            min_left<=min_left-1;
            sec_left<=7'b0111011;
          end
        end
      end
    end

    assign done = (EA == 2'b00) ? 1 : 0;

    integer minutes;
    always@(min_left)
    minutes = min_left;

    integer seconds;
    always@(sec_left)
    seconds = sec_left;

    assign sec_uni = seconds % 10;
    assign sec_dec = seconds / 10;
    assign min_uni =  minutes % 10;
    assign min_dec = minutes / 10;

    // Instanciação da display 7seg
    dspl_drv_NexysA7 instaciacao (.reset(reset), .clock(clock), .d1({1'b1, sec_uni,1'b0}), .d2({1'b1, sec_dec, 1'b0}), .d3({1'b1, min_uni, 1'b0}), .d4({1'b1, min_dec, 1'b0}), .d5(6'b0), .d6(6'b0), .d7(6'b0), .d8(6'b0), .dec_cat(dec_cat), .an(an));
    
endmodule