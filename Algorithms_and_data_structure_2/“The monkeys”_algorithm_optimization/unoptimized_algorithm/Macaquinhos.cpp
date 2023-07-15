#include <iostream>
#include <iterator>
#include <vector>

#include "Macaquinho.h"

using namespace std;

Macaquinhos::Macaquinhos() {
  this->macaco = 0;
  this->par = 0;
  this->impar = 0;
  this->cocos = 0;
}

void Macaquinhos::setMacaco(int macaco) { this->macaco = macaco; }
void Macaquinhos::setPar(int par) { this->par = par; }
void Macaquinhos::setImpar(int impar) { this->impar = impar; }
void Macaquinhos::setCocos(int cocos) { this->cocos = cocos; }
// adiciona no vector as pedrinhas de outro macaco
void Macaquinhos::setPedrinhas(int pedrinhas) {
  this->pedrinhas.push_back(pedrinhas);
}

int Macaquinhos::getMacaco() { return this->macaco; }

int Macaquinhos::getPar() { return this->par; }

int Macaquinhos::getImpar() { return this->impar; }

int Macaquinhos::getCocos() { return this->cocos; }
// mostra todas as pedrinhas do vector do macaco
void Macaquinhos::showPedrinhas(ostream &arquivo) {
  for (auto i = this->pedrinhas.begin(); i < pedrinhas.end(); i++) {
    arquivo << *i << endl;
  }
}

void Macaquinhos::reduzCocos() { this->cocos--; }

// pega a primeira pedrinha do vector para outro macaco
int Macaquinhos::getPedrinhas() {
  int valor = this->pedrinhas[0];
  // já remove as pedrinhas do vector do macaco
  this->pedrinhas.erase(this->pedrinhas.begin());
  return valor;
}

void Macaquinhos::aumentaCocos() { this->cocos++; }