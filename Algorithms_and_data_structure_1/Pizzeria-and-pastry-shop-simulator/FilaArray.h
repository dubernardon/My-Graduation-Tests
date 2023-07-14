#include "Pedido.h"

#ifndef Fila_h
#define Fila_h

class FilaArray{
    Pedido *fila;
    int capacidade;
    int count;
    int primeiro;
    int ultimo;
    
public:
    FilaArray();
    void enqueue(Pedido element);
    Pedido dequeue();
    bool isEmpty();
    Pedido head();
    int size();
    void clear();
    int ReturnCapacidade();
};

#endif
