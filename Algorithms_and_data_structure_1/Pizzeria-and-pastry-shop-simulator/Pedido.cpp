//
// pizzeria and pastry shop
//  Pedido.cpp


#include "Pedido.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>


using namespace std;


Pedido::Pedido(){   // Constructor of Class Pedido
  quantidadepasteis = 0;
  quantidadepizzas = 0;
  sequencia = 0;
  instantedetempo = 0;
  etapa = 0;
}

int Pedido::ReturnPasteis(){
  return quantidadepasteis;
}

int Pedido::ReturnPizzas(){ 
  return quantidadepizzas;
}

bool Pedido::chegadadepedidos() { // random function to arrive orders
  int valor;

  valor = rand() % 99; // random numbers from 0 to 99

  if (valor > 80) { //if the number is greater than 80, create a new order (20% of chance)
    return true;
  }
  return false;
}

void Pedido::SetTempoDeProcessamento(int v){
  tempoNecessarioAoProcessamento = v;
}

int Pedido::ReturnTempoNecessarioAoProcessamento(){
  return tempoNecessarioAoProcessamento;
}

void Pedido::SetTempoDeEntradaAoProcessamento(int t){
  tempoDeEntradaAoProcessamento = t;
}

int Pedido::ReturnTempoDeEntradaAoProcessamento(){ 
  return tempoDeEntradaAoProcessamento;
}

void Pedido::pasteis() {   //random numbers for pastry (1 to 5)
  quantidadepasteis = (rand() % 5) + 1; } 

void Pedido::pizzas() {   //random numbers for pizza (1 to 3)
    quantidadepizzas = (rand() % 3) + 1;
  }

void Pedido::gerainstantedetempo(int tempo) {  
  instantedetempo = tempo; 
  }

void Pedido::gerasequencia(int s) { 
  sequencia = s; 
  }


void Pedido::imprime() {        // print orders info;

  cout << "==================================================" << endl;

  cout << "Número do pedido:" << sequencia << endl;

  cout << "Tempo de chegada: " << instantedetempo << endl;

  cout << "Número de Pizzas: " << quantidadepizzas << endl;

  cout << "Número de Pasteis: " << quantidadepasteis << endl;

  cout << "Etapa: " << etapa << endl;

  cout << "Tempo De Entrada Na Unidade de Processamento: " << tempoDeEntradaAoProcessamento << endl;

  cout << "Tempo Necessario Ao Processamento: " << tempoNecessarioAoProcessamento << endl;

  cout << "==================================================" << endl;
}

void Pedido:: imprimetxt(ostream &file){ //relatory of the orders

  file << "==================================================" << endl;

  file << "Número do pedido:" << sequencia << endl;

  file << "Tempo de chegada: " << instantedetempo << endl;

  file << "Número de Pizzas: " << quantidadepizzas << endl;

  file << "Número de Pasteis: " << quantidadepasteis << endl;

  file << "Etapa: " << etapa << endl;

  file << "Tempo De Entrada Na Unidade de Processamento: " << tempoDeEntradaAoProcessamento << endl;

  file << "Tempo Necessario Ao Processamento: " << tempoNecessarioAoProcessamento << endl;

  file << "==================================================" << endl;

}

