//
//  Queue.h
//  Fila de NodoAB.
//

#ifndef Queue_h
#define Queue_h

#include <vector>

using namespace std;
#include "NodoAB.h"

class Queue{
    vector<NodoAB*> dados;

public:

    void enqueue(NodoAB* element);
    NodoAB* dequeue();
    bool isEmpty();
    NodoAB* head();
    int size();
    void clear();
};

#endif

