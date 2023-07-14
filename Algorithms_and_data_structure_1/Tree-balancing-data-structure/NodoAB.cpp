#include <iostream>
using namespace std;

#include "NodoAB.h"

NodoAB::NodoAB(int elem)
{
  left = NULL;
  right = NULL;
  father = NULL;
  element = elem;
}

void NodoAB::print()
{
  cout << "Nodo: " << element << endl;
  cout << "\tEsq: ";
  if (left != NULL)
    cout << left->element;
  else cout << "NULL";
  cout << endl;

  cout << "\tDir: ";
  if (right != NULL)
    cout << right->element;
  else cout << "NULL";
  cout << endl;
}



