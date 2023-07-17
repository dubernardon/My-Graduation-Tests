`timescale 1 ns/10 ps  // time-unit = 1 ns, precision = 10 ps

module tb;
    reg clock, reset, start, stop, pause, porta, mais, menos, potencia, sec_mod;
    reg [1:0] min_mod;
    wire [7:0] an, dec_cat;
    wire [2:0] potencia_rgb;

    localparam PERIOD = 2;  

    ctrl_microondas DUT (.clock(clock), .reset(reset), .start(start), .pause(pause), .stop(stop), .min_mod(min_mod), .sec_mod(sec_mod), .an(an), .dec_cat(dec_cat), .porta(porta), .mais(mais), .menos(menos), .potencia(potencia), .potencia_rbg(potencia_rgb));

    initial begin
        clock <= 1'b0;
        forever #1 clock <= ~clock;
    end

    initial
    begin
        //testes: porta / mais / menos / potencia /sec_mod / min_mod
        reset <= 1'b1;
        start <= 1'b0;
        stop <= 1'b0;
        pause <= 1'b0;
        porta <= 1'b0;
        mais <= 1'b0;
        menos <= 1'b0;
        potencia <=1'b0;
        sec_mod <= 1'b0;
        min_mod <= 2'b00;
        #20
        reset <= 1'b0;
        sec_mod <= 1'b1;
        #70
        mais <= 1'b1;
        #100
        mais <= 1'b0;
        #130
        mais <= 1'b1;
        #160
        mais <= 1'b0;
        #190
        mais <= 1'b1;
        #210
        mais <= 1'b0;
        #250
        potencia <= 1'b1;
        #280
        mais <= 1'b1;
        #300
        mais <= 1'b0;
        #400
        start <= 1'b1;
        #470
        start <= 1'b0;
        #900
        pause <= 1'b1;
        #930
        pause <= 1'b0;
        #960
        porta <= 1'b1;
        #1100
        pause <= 1'b1;
        #1130
        pause <= 1'b0;
        #1250
        porta <= 1'b0;
        #1350
        pause <= 1'b1;
        #1380
        pause <= 1'b0;
        #4000
        stop <= 1'b1;
        #4030
        stop <= 1'b0;
        #4200
        sec_mod <= 1'b0;
        potencia <= 1'b0;
        min_mod <= 2'b01;
        #4300
        mais <= 1'b1;
        #4330
        mais <= 1'b0;
        #4360
        mais <= 1'b1;
        #4390
        mais <= 1'b0;
        #4500
        menos <= 1'b1;
        #4530
        menos <= 1'b0;
        #4600
        min_mod <= 2'b11;
        #4660
        mais <= 1'b1;
        #4690
        mais <= 1'b0;
        #4700
        menos <= 1'b1;
        #4730
        menos <= 1'b0;
        #4800
        start <= 1'b1;
        #4830
        start <= 1'b0;


    end
endmodule