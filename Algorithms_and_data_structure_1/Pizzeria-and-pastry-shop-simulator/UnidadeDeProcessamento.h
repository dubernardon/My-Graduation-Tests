#include <iostream>
#include "FilaArray.h"

using namespace std;

#ifndef _UNIDADE_H
#define _UNIDADE_H

class UnidadeDeProcessamento
{

    FilaArray espera;  
    Pedido *processamento;  
    bool *livre;        
    int capacidade;       
    int unidadeslivres;      

    int tempoPizza;
    int tempoPasteis;

    double TempoTotal;        
    
public:

    UnidadeDeProcessamento(int Tpasteis, int Tpizza, int Cap);    

    bool montador;        
    bool forno;          
    bool empacotador;

    void QualtipoDeUnidade(int v); 

    int CalculaOTempo(Pedido P);   

    void ColocaNaFilaDeProcessamento(Pedido P); 

    Pedido RetiraPedidoDaFilaDeProcessamento();  

    bool temUnidadeDeProcessamentoLivre();   

    void AtribuiPedidoAoProcessadorLivre(Pedido P, int tempo);  

    bool temProcessamentoFinalizado(int tempo);  

    Pedido ConcluiProcessamento();   

    bool IfTempoTerminou(int tempo, int i); 

    void ImprimeRelatorio(int tempo, int sequencia, ostream &file2); 

};

#endif