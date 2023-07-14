//
//  pizzeria and pastry shop
//  UnidadeDeprocessamento.cpp
//


#include <iostream>
#include "UnidadeDeProcessamento.h"



using namespace std;


// processing unit constructor
UnidadeDeProcessamento::UnidadeDeProcessamento(int Tpasteis, int Tpizza, int Cap){
  capacidade = Cap;                            // number of units
  processamento = new Pedido[capacidade];    // how many units
  livre = new bool[capacidade];
  for(int i = 0; i < capacidade; i++){     
    livre[i] = true;                         // all units start free
  }
  unidadeslivres = capacidade; 
  TempoTotal = 0; 
  tempoPasteis = Tpasteis;
  tempoPizza = Tpizza;
}


void UnidadeDeProcessamento::QualtipoDeUnidade(int v){
  switch(v){
    case 1: { // v=1 -> mounting order
      montador = true;
      forno = false;
      empacotador = false;
      break;
    }
    case 2: { // v=2-> cooking order
      montador = false;
      forno = true;
      empacotador = false;
      break;
    }
    case 3: { // v=3 -> packing order
      montador = false;
      forno = false;
      empacotador = true;
      break;
    }
  }
}

int UnidadeDeProcessamento::CalculaOTempo(Pedido P){ 
      int a = (P.ReturnPasteis()* tempoPasteis) + (P.ReturnPizzas() * tempoPizza);
     return a;
} //calculate how long it will take on each unit separately

void UnidadeDeProcessamento::ColocaNaFilaDeProcessamento(Pedido P){  // waiting step
  if(P.etapa == 1){   //only created orders go to the processing unit
    espera.enqueue(P); 
  }
}


Pedido UnidadeDeProcessamento::RetiraPedidoDaFilaDeProcessamento(){  // remove of waiting step
  return espera.dequeue();  
}  

 bool UnidadeDeProcessamento::temUnidadeDeProcessamentoLivre(){  
     if (unidadeslivres > 0  && espera.size() > 0 ){
      return true;
    }     
   return false;
 } // if have space in the unit or not;

void UnidadeDeProcessamento::AtribuiPedidoAoProcessadorLivre(Pedido P, int tempo){
  for(int i = 0; i < capacidade; i++){   // verify all positions of a processing unit
    if (livre[i] == true && P.etapa == 1){   //verify a free position and if a order is waiting
      P.etapa = 2;   //change the order step
      int a = CalculaOTempo(P);    //calculate order time
      TempoTotal += a; //adds time
      P.SetTempoDeProcessamento(a); // save the time in the order
      P.SetTempoDeEntradaAoProcessamento(tempo); //// save the time of start processing
      processamento[i] = P; // order to free space in the unit
      livre[i] = false; // space is no longer free

      unidadeslivres--; // less spaces free
    }
  }
}

bool UnidadeDeProcessamento::IfTempoTerminou(int tempo, int i){
    if (processamento[i].ReturnTempoNecessarioAoProcessamento() == tempo - processamento[i].ReturnTempoDeEntradaAoProcessamento()){ 
      return true;
    }
  return false;
} // ready order / not ready order


bool UnidadeDeProcessamento::temProcessamentoFinalizado(int tempo){
  for(int i = 0; i < capacidade;  i++){
    if(IfTempoTerminou(tempo, i) && processamento[i].etapa == 2 && livre[i] == false){
      processamento[i].etapa = 3; // ready order
      return true;
    }
  }
  return false;
}

Pedido UnidadeDeProcessamento::ConcluiProcessamento(){
  Pedido aux;
  for(int i = 0; i < capacidade; i++){ 
    if (processamento[i].etapa == 3 && livre[i] == false){ 
        aux = processamento[i]; 
        aux.etapa = 1; 
        livre[i] = true; 
        unidadeslivres++;
    }
  }
  return aux; // return the completly order.
} 


void UnidadeDeProcessamento::ImprimeRelatorio(int tempo, int sequencia, ostream &file2){//relatory of processing units
  int quantos = 0;
  file2 << endl;
  file2 << "=========================================================================" << endl;
  file2 << "Relatorio: " << endl;
  //print relatory
    if(montador == true){ 
      file2 << "Montador: " << endl;
    }
    if(forno == true){
      file2 << "Fornos: " << endl;
    }
    if(empacotador == true){
      file2 << "Empacotadores: " << endl;
  }
  file2 << "Capacidade: " << capacidade << endl;
  file2 << "Unidades em Processamento: " << capacidade - unidadeslivres << endl;
  for (int i = 0; i < capacidade; i++){
    if (processamento[i].etapa == 2 && livre[i] == false){
      file2 << "Unidade " << i << " em Processamento." << endl;
      file2 << "Faltam " << processamento[i].ReturnTempoNecessarioAoProcessamento() - (tempo - processamento[i].ReturnTempoDeEntradaAoProcessamento()) << " unidades de tempo para finalizacao do Processamento da Unidade " << i << endl;    //time to end the order
      file2 << endl;
    }
  }
  file2 << "Fila de Espera: " << espera.size() << endl;
  file2 << "Tempo Medio Necessario Para Processamento: " << TempoTotal / sequencia << endl; //average time for each order
  file2 << "=========================================================================" << endl;
  file2 << endl;
} //imprime todos os dados dos pedidos.
