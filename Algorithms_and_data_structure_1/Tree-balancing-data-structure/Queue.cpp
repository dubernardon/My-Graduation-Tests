//
//  Queue.cpp
//  Implementa um TAD Fila
//

#include "Queue.h"

#define FullQueueException 1
#define EmptyQueueException 2

void Queue::enqueue(NodoAB* n)
{
    dados.push_back(n);
}

NodoAB* Queue::dequeue()
{
    NodoAB* n = dados[0];
    dados.erase(dados.begin());
    return n;
}

bool Queue::isEmpty()
{
    return dados.empty();
}

void Queue::clear()
{
    dados.clear();
}

