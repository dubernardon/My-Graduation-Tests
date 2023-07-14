#include <iostream>

using namespace std;

#include "BinarySearchTreeOfInteger.h"

  BinarySearchTreeOfInteger b;
  
int main(){

int caso1[] = {100, 90, 80, 70, 60};
int caso2[] = {60, 70, 80, 90, 100};
int caso3[] = {100, 50, 60, 70};
int caso4[] = {100, 90, 80, 82, 84, 86};
int caso5[] = {100, 90, 80, 110, 105, 108,107};
int caso6[] = {100, 90, 80, 70, 110, 120, 130};

// 20 Numeros aleatorios menores que 40 que não se repetem.
int v[20] = {38, 15, 37, 33, 2, 21, 14 ,34 ,18 ,24 ,23 ,35 ,12 ,6 ,29 ,25 ,4 ,39 ,11 ,30};

  for (int i = 0; i < 7; i++){
    b.add(caso6[i]);
  }
  

  
  cout << "Árvore: (antes do balanceamento)" << endl;
  cout << endl;

  
  b.GeraDOT();

  
  cout << "--------------" << endl;
  if (b.isBalanced())
    cout << "Balanceada" << endl;
  else
    cout << "Nao Balanceada"<< endl;
  cout << "--------------" << endl;


  cout << endl;
  cout << "Aplicando o Balanceamento:" << endl; 
  cout << endl;
  //b.testBalance();  // Faz o balanceamento dessa arvore específica passo a passo.
  b.ApplyBalancing();

  
  cout << "--------------" << endl;
  if (b.isBalanced())
    cout << "Balanceada" << endl;
  else
    cout << "Nao Balanceada"<< endl;
  cout << "--------------" << endl;

  cout << "Árvore: (depois do balanceamento)" << endl;
  cout << endl;
  
  b.GeraDOT();
}