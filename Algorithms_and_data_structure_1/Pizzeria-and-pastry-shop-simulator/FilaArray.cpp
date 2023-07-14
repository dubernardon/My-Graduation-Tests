// 
//  Created by Márcio Sarroglia Pinho on 08/10/21. My algorithms and data structures teacher;
//


#include "FilaArray.h"

#define FullQueueException 1
#define EmptyQueueException 2



FilaArray::FilaArray()
{
    capacidade = 120;
    fila = new Pedido[capacidade];
    count = 0;
    primeiro = 0;
    ultimo = 0;
}


void FilaArray::enqueue(Pedido element)
{
    if (count == capacidade)
       throw FullQueueException;

    fila[ultimo] = element;
    count++;
    ultimo = (ultimo+1) % capacidade;
}


Pedido FilaArray::dequeue()
{

    if (count == 0){
       throw EmptyQueueException;
      }
    Pedido elem = fila[primeiro];
    count--;
    primeiro = (primeiro+1) % capacidade;
    return elem;
}


Pedido FilaArray::head()
{
    if (count == 0)
        throw  EmptyQueueException;
    
    return fila[primeiro];
}


int FilaArray::size()
{
    return count;
}


bool FilaArray::isEmpty()
{
    return count == 0;
}


void FilaArray::clear()
{
    delete[] fila;

    fila = new Pedido[capacidade];
    count = 0;
    primeiro = 0;
    ultimo = 0;
}

int FilaArray::ReturnCapacidade(){
  return capacidade;
}