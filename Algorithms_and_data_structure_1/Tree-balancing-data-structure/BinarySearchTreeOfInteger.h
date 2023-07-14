#ifndef _ABP
#define _ABP
#include <iostream>
#include <cstdlib>
#include <list>
using namespace std;

#include "NodoAB.h"

class BinarySearchTreeOfInteger
{
private:
  NodoAB *root;
  int count;

  int countLeaves(NodoAB *n);
  NodoAB* searchNodeRef(int elem, NodoAB *n);
  NodoAB* smallest(NodoAB *n);
  void positionsPreAux(NodoAB *n, list<int> &lista);
  void positionsPosAux(NodoAB *n, list<int> &lista);
  void positionsCentralAux(NodoAB *n, list<int> &lista);
  int height(NodoAB *n);
  int countNodos(NodoAB *n);
  void GeraConexoesDOT(NodoAB *nodo);
  void GeraNodosDOT(NodoAB *nodo);

  NodoAB* rotateLeftLeft(NodoAB *r);
  NodoAB* rotateRightRight(NodoAB *r);
  NodoAB* rotateLeftRight(NodoAB *r);
  NodoAB* rotateRightLeft(NodoAB *r);
  NodoAB* Balance(NodoAB *root);
  bool isBalanced(NodoAB *root);

public:
    BinarySearchTreeOfInteger();
    void clear();
    bool isEmpty();
    int size();
    int getRoot();
    void add(int element);
    NodoAB* add(NodoAB* nodo, int element, NodoAB* father);
    bool contains(int elem);
    NodoAB* getLeft(int element);
    NodoAB* getRigh(int element);
    NodoAB* getParent(int element);
    bool remove(int element);
    bool set(int old, int element);
    list<int> positionsWidth();
    list<int> positionsCentral();
    list<int> positionsPre();
    list<int> positionsPos();
    bool isExternal(int element);
    bool isInternal(int element);
    int height();
    int level(int element);
    int countLeaves();
    void GeraConexoesDOT();
    void GeraNodosDOT();
    void GeraDOT();

    bool isBalanced();
    void ApplyBalancing();

    void testBalance();
};
#endif
