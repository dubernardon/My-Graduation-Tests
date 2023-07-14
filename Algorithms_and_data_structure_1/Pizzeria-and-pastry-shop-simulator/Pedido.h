
#ifndef _PEDIDO_H
#define _PEDIDO_H

#include <iostream>
#include <fstream>

class Pedido
{

    int tempoNecessarioAoProcessamento;  
    int tempoDeEntradaAoProcessamento;

    int quantidadepizzas;
    int quantidadepasteis; 
    int sequencia;
    int instantedetempo;


public:

  Pedido();   

  void imprime();   

  int ReturnPasteis();  
  int ReturnPizzas();

  void SetTempoDeProcessamento(int v); 
  int ReturnTempoNecessarioAoProcessamento();

  void SetTempoDeEntradaAoProcessamento(int t); 
  int ReturnTempoDeEntradaAoProcessamento();

  bool chegadadepedidos();
  void pasteis();
  void pizzas();                        
  void gerainstantedetempo(int tempo);
  void gerasequencia(int sequencia);

  int etapa; // step=0 -> no order / setp=1 -> created order or order is waiting / setp=2 -> order is being produced / setp=3 -> order is finished / setp=4 ready order

void imprimetxt(std::ostream &file);

};

 #endif