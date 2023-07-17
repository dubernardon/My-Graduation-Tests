`timescale 1 ns/10 ps  // time-unit = 1 ns, precision = 10 ps

module tb;
    reg clock, reset, start, op;
    reg [31:0] data_a, data_b;
    wire [31:0] data_o;
    wire busy, ready;

    localparam PERIOD = 10;  

    soma DUT (.clock(clock), .reset(reset), .start(start), .op(op), .data_a(data_a), .data_b(data_b), .data_o(data_o), .busy(busy), .ready(ready));

    initial begin
        clock <= 1'b0;
        forever #(PERIOD/2) clock <= ~clock;
    end

    initial
    begin
        reset <= 1'b1;
        start <= 1'b0;
        op <= 1'b0;
        data_a <= 0;
        data_b <= 0;
        #20
        reset <= 1'b0;
        #40

        // Teste 1 -- Soma valores grandes positivos
        data_a <= 32'b01011001111111010011110110010111;
        data_b <= 32'b01010001111001011111010010111110;
        op <= 1'b1;
        #20
        start <= 1'b1;
        #20
        start <= 1'b0;
        op <= 1'b0;

        // Teste 2 -- Soma valores grandes negativos
        #2400
        data_a <= 32'b11001111111101000000000000000000;
        data_b <= 32'b11001100111111010100000000000010;
        op <= 1'b1;
        #20
        start <= 1'b1;
        #20
        start <= 1'b0;
        op <= 1'b0;

        // Teste 3 -- Soma valores grandes positivo e negativo
        #2400
        data_a <= 32'b11001110111111111100000000000010;
        data_b <= 32'b01001110110000011100000110010110;
        op <= 1'b1;
        #20
        start <= 1'b1;
        #20
        start <= 1'b0;
        op <= 1'b0;

        // Teste 4 -- Subtracao valores grandes positivos
        #2400
        data_a <= 32'b01001100000111111011010000110000;
        data_b <= 32'b01110000000000000001010000110000;
        op <= 1'b0;
        #20
        start <= 1'b1;
        #20
        start <= 1'b0;
        op <= 1'b0;

        // Teste 5 -- Subtracao valores grandes negativos
        #2400
        data_a <= 32'b11011000011111000011110110110011;
        data_b <= 32'b11110000111010010010000101000010;
        op <= 1'b0;
        #20
        start <= 1'b1;
        #20
        start <= 1'b0;
        op <= 1'b0;
        
        // Teste 6 -- Subtracao valores grandes positivo e negativo
        #2400
        data_a <= 32'b11101110010011111110010110001101;
        data_b <= 32'b01101101010010000110010110001101;
        op <= 1'b0;
        #20
        start <= 1'b1;
        #20
        start <= 1'b0;
        op <= 1'b0;

        // Teste 7 -- Soma valores pequenos positivos
        #2400
        data_a <= 32'b00000111100000000101010000001001;
        data_b <= 32'b00000100100111001100110000000111;
        op <= 1'b1;
        #20
        start <= 1'b1;
        #20
        start <= 1'b0;
        op <= 1'b0;

        // Teste 8 -- Soma valores pequenos negativos
        #2400
        data_a <= 32'b10001100000101001000000100000000;
        data_b <= 32'b10011000000000001001100100001111;
        op <= 1'b1;
        #20
        start <= 1'b1;
        #20
        start <= 1'b0;
        op <= 1'b0;

        // Teste 9 -- Soma valores pequenos positivo e negativo
        #2400
        data_a <= 32'b10100010000111001010000000001001;
        data_b <= 32'b00101010001001001010110011101001;
        op <= 1'b1;
        #20
        start <= 1'b1;
        #20
        start <= 1'b0;
        op <= 1'b0;

        // Teste 10 -- Subtracao valores pequenos positivos
        #2400
        data_a <= 32'b00000111100000000101010000001001;
        data_b <= 32'b00000100100111001100110000000111;
        op <= 1'b0;
        #20
        start <= 1'b1;
        #20
        start <= 1'b0;
        op <= 1'b0;

        // Teste 11 -- Subtracao valores pequenos negativos
        #2400
        data_a <= 32'b10001100000101001000000100000000;
        data_b <= 32'b10011000000000001001100100001111;
        op <= 1'b0;
        #20
        start <= 1'b1;
        #20
        start <= 1'b0;
        op <= 1'b0;

        // Teste 12 -- Subtracao valores pequenos positivo e negativo
        #2400
        data_a <= 32'b10100010000111001010000000001001;
        data_b <= 32'b00101010001001001010110011101001;
        op <= 1'b0;
        #20
        start <= 1'b1;
        #20
        start <= 1'b0;
        op <= 1'b0;
    end
endmodule