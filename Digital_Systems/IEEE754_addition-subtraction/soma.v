module soma 
(
  // Declaração das portas
    input clock, reset, start, op,
    input [31:0] data_a, data_b,
    output [31:0] data_o,
    output busy, ready

);

    reg [128:0] resultado;
    wire [128:0] resultado_wire;
    reg [127:0] operador_total;
    wire [127:0] operador_wire;
    reg [31:0] data_a_reg, data_b_reg, data_o_reg;
    reg [7:0] expoente_a, expoente_b, deslocamento, count_left, count_right, count_test, pos_1;
    wire [7:0] expoente_maior, add_zero, remove_zero;
    reg [2:0] EA;
    wire [1:0] arredondamento;
    reg signal_A, signal_B, signal_Resultado;
    reg op_reg;
    wire signal_wire, calculo_test, igual_test, maior_data_test, maior_expoente_test, signal_igual_test, signal_maior_test;


    always @(posedge clock or posedge reset)
    begin
      if(reset == 1'b1)begin
        EA <= 3'b000;
      end
      else begin
        if(EA ==  3'b000)begin   // Idle
            if (start == 1'b1) begin
                EA <= 3'b001;
            end
        end
        if(EA == 3'b001)begin    // Start
            EA <= 3'b010;
        end
        if(EA == 3'b010) begin  // Pre-Calculo
            EA <= 3'b011;
        end
        if (EA == 3'b011) begin  // Pre-Calculo -- Shift Left
            if (count_left == 8'd24) begin
                EA <= 3'b100; 
            end
        end
        if (EA == 3'b100) begin  // Calculo
            EA <= 3'b101; 
        end
        if (EA == 3'b101) begin  // Pos-Calculo -- Test
            if (count_test == 8'd0) begin    
                EA <= 3'b110;
            end
        end
        if (EA == 3'b110) begin  // Pos-Calculo -- Shift Right
            if ((count_right + add_zero - remove_zero > 8'd22) && count_right >= remove_zero) begin    
                EA <= 3'b111;
            end
        end
        if (EA == 3'b111) begin  // Pos-Calculo -- Arredondamento
            EA <= 3'b000;
        end
      end
    end



    always @(posedge clock or posedge reset) 
    begin
        if(reset == 1'b1)begin
            expoente_a <= 8'd0;
            expoente_b <= 8'd0;
            deslocamento <= 8'd0;
        end
        else begin
            if (EA == 3'b001) begin
                expoente_a <= data_a[30:23];
                expoente_b <= data_b[30:23];     
            end
            else if (EA == 3'b010) begin
                if (expoente_a > expoente_b) begin
                    deslocamento <= expoente_a - expoente_b;
                end
                else begin
                    deslocamento <= expoente_b - expoente_a;
                end
            end    
        end    
    end


    always @(posedge clock or posedge reset) 
    begin
        if(reset == 1'b1)begin
            data_a_reg <= 32'd0;
            data_b_reg <= 32'd0;
        end
        else begin
            if (EA == 3'b001) begin
                data_a_reg <= data_a;
                data_b_reg <= data_b;     
            end    
        end    
    end

//signal
    always @(posedge clock or posedge reset) 
    begin
        if(reset == 1'b1)begin
            signal_A <= 1'b0;
            signal_B <= 1'b0;
        end
        else begin
            if (EA == 3'b010) begin
                signal_A <= data_a_reg[31];
                signal_B <= data_b_reg[31];
            end    
        end    
    end


    always @(posedge clock or posedge reset) 
    begin
        if(reset == 1'b1)begin
            op_reg <= 1'b0;
        end
        else begin
            if (EA == 3'b001) begin
                op_reg <= op;   
            end    
        end    
    end


//deslocamento Left
    always @(posedge clock or posedge reset) 
    begin
        if(reset == 1'b1)begin
            operador_total <= 128'd0;
            count_left <= 8'd0;
        end
        else begin
            if (EA == 3'b001) begin
                operador_total <= 128'd0;
                count_left <= 8'd0;  
            end
            else if (EA == 3'b011) begin
                if (count_left < 8'd24) begin
                    operador_total[count_left + deslocamento] <= operador_wire[count_left];      
                    count_left <= count_left + 8'd1;
                end
            end
        end
    end 
        

    assign igual_test = (expoente_a == expoente_b) ? maior_data_test : maior_expoente_test;
    assign maior_data_test  = (data_a_reg[22:0] > data_b_reg[22:0]) ? 1'b1 : 1'b0;
    assign maior_expoente_test = (expoente_a > expoente_b) ? 1'b1 : 1'b0;


    assign operador_wire = (igual_test) ? {104'd0, 1'b1 ,data_a_reg[22:0]} : {104'd0, 1'b1, data_b_reg[22:0]};  

    

    always @(posedge clock or posedge reset) begin
        if(reset == 1'b1)begin
            resultado <= 129'd0;
            signal_Resultado <= 1'b0;
            count_test <= 8'd0;
            pos_1 <= 8'd0;
        end
        else begin
            if (EA == 3'b001) begin
                count_test <= 8'd128;
                pos_1 <= 8'd127;
            end
            if (EA == 3'b100)begin
                if(calculo_test)begin
                    resultado <= {1'b0, operador_total} + resultado_wire;
                end
                else begin
                    resultado <= {1'b0, operador_total} - resultado_wire;
                end
                signal_Resultado <= signal_wire;
            end
            if (EA == 3'b101)begin
                if (count_test > 8'd0) begin
                    if (resultado[count_test - 8'd1] == 1'b1) begin
                        count_test <= 8'd0;
                    end
                    else begin
                        count_test <= count_test - 8'd1;
                        pos_1 <= pos_1 - 8'd1;
                    end
                end
            end
        end
    end


    assign add_zero = ((8'd23 + deslocamento) > (pos_1)) ? (8'd23 + deslocamento) - (pos_1) : 8'd0;
    assign remove_zero = ((pos_1) > (8'd23 + deslocamento)) ? (pos_1) - (8'd23 + deslocamento) : 8'd0;

    assign calculo_test =   (op_reg && signal_A == signal_B) ? 1'b1 : 
                            (op_reg && signal_A != signal_B) ? 1'b0 : 
                            (!op_reg && signal_A == signal_B) ? 1'b0 :
                            (!op_reg && signal_A != signal_B) ? 1'b1 :
                            1'b0;

    assign resultado_wire = (igual_test) ? {104'd0, 2'b01, data_b_reg[22:0]} : {104'd0, 2'b01, data_a_reg[22:0]};

    assign signal_wire =    (op_reg && signal_A == signal_B) ? signal_A : 
                            (!op_reg && signal_A != signal_B) ? signal_A : 
                            (op_reg && !igual_test) ? signal_B :
                            (!op_reg && !igual_test) ? !signal_B :
                            signal_A;


//deslocamento Right
    always @(posedge clock or posedge reset) 
    begin
        if(reset == 1'b1)begin
            data_o_reg <= 128'd0;
            count_right <= 8'd0;
        end
        else begin
            if (EA == 3'b001) begin
                data_o_reg <= 128'd0;
                count_right <= 8'd0;
            end
            if (EA == 3'b110) begin
                if (count_right < remove_zero) begin
                    count_right <= count_right + 8'd1;
                end
                else if (count_right + add_zero - remove_zero < 8'd23) begin
                    data_o_reg[count_right + add_zero - remove_zero] <= resultado[count_right + deslocamento];      
                    count_right <= count_right + 8'd1;
                end
            end
            if (EA == 3'b111)begin
                if (arredondamento > 2'b01) begin
                    data_o_reg <= data_o_reg + 2'b01;
                end
                data_o_reg[30:23] <= expoente_maior - add_zero + remove_zero;
                data_o_reg[31] <= signal_Resultado;
            end
        end
    end 
   

    assign expoente_maior = (igual_test) ? expoente_a : expoente_b;
    assign arredondamento = (deslocamento > 8'd2) ? {resultado[deslocamento - 8'd1], resultado[deslocamento - 8'd2]} : 2'd0;

    assign busy = (EA != 3'b000) ? 1'b1 : 1'b0;
    assign ready = (EA == 3'b000) ? 1'b1 : 1'b0;

    assign data_o = (EA == 3'b000) ? data_o_reg : 32'd0;


endmodule