//
//  pizzeria and pastry shop
//


#include "UnidadeDeProcessamento.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

Pedido geraPedido(int tempo, int sequencia) {
  Pedido p;

  p.pasteis();                  // pastry quantity
  
  p.pizzas();                   // pizza quantity
  
  p.gerainstantedetempo(tempo); // order time arrived
  p.gerasequencia(sequencia);   // save the number of order
  p.etapa = 1; // step 1: order created/waiting

  return p;
}

int main() {

  ofstream file, file2;

  file.open("RelatorioPedidos.txt", ios::out);
  file2.open("RelatorioUnidades.txt", ios::out);

  if (!file.is_open()) {
    cout << "Erro na abertura do arquivo para salvar o relatório";
  }
  if (!file2.is_open()) {
    cout << "Erro na abertura do arquivo para salvar o relatório";
  }

  Pedido P;

  UnidadeDeProcessamento Montadores(1, 3, 5), Fornos(2, 4, 5),
      Empacotadores(1, 1, 5);

  // Select which processing unit is
  Montadores.QualtipoDeUnidade(1);
  Fornos.QualtipoDeUnidade(2);
  Empacotadores.QualtipoDeUnidade(3);

  srand(time(NULL));

  int tempo = 0;
  int sequencia = 0; //ordering number

  do {
    if (P.chegadadepedidos()) { //  random function to arrive orders
      sequencia++; // ordering number
      P = geraPedido(tempo, sequencia); // order constructor
      Montadores.ColocaNaFilaDeProcessamento(P);
    }

    // mounting order

    while (
        Montadores.temUnidadeDeProcessamentoLivre()) // start mounting
    {
      P = Montadores.RetiraPedidoDaFilaDeProcessamento();
      Montadores.AtribuiPedidoAoProcessadorLivre(P, tempo);
    }

    while (
        Montadores.temProcessamentoFinalizado(tempo)) // finish mounting
    {
      P = Montadores.ConcluiProcessamento();
      Fornos.ColocaNaFilaDeProcessamento(P);
    }

    // cooking order

    while (Fornos.temUnidadeDeProcessamentoLivre()) // start cooking
    {
      P = Fornos.RetiraPedidoDaFilaDeProcessamento();
      Fornos.AtribuiPedidoAoProcessadorLivre(P, tempo);
    }

    while (Fornos.temProcessamentoFinalizado(tempo)) // finish cooking
    {
      P = Fornos.ConcluiProcessamento();
      Empacotadores.ColocaNaFilaDeProcessamento(P);
    }

    // pack order

    while (Empacotadores
               .temUnidadeDeProcessamentoLivre()) // start packaging

    {
      P = Empacotadores.RetiraPedidoDaFilaDeProcessamento();
      Empacotadores.AtribuiPedidoAoProcessadorLivre(P, tempo);
    }

    while (Empacotadores.temProcessamentoFinalizado(
        tempo)) // finish packaging

    {
      P = Empacotadores.ConcluiProcessamento();
      P.etapa = 4;
      P.imprime();
      P.imprimetxt(file);
    }

     Montadores.ImprimeRelatorio(tempo, sequencia,file2);
     Fornos.ImprimeRelatorio(tempo, sequencia,file2);
     Empacotadores.ImprimeRelatorio(tempo, sequencia,file2);

    tempo++;

  } while (tempo < 8 * 60); // 8 hours, 60 minutes

  file.close();
  file2.close();

  return 0;
}