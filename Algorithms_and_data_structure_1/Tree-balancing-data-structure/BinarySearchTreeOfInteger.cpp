#include <cstdlib>
#include <iostream>
using namespace std;

#include "BinarySearchTreeOfInteger.h"
#include "Queue.h"

BinarySearchTreeOfInteger::BinarySearchTreeOfInteger() {
  root = NULL;
  count = 0;
}

/**
 * Remove todos os elementos da arvore.
 */
void BinarySearchTreeOfInteger::clear() {
  root = NULL;
  count = 0;
}

/**
 * Verifica se a arvore esta vazia ou nao.
 * @return true se arvore vazia e false caso contrario.
 */
bool BinarySearchTreeOfInteger::isEmpty() { return (root == NULL); }

/**
 * Retorna o total de elementos da arvore.
 * @return total de elementos
 */
int BinarySearchTreeOfInteger::size() { return count; }

/**
 * Retorna o elemento armazenado na raiz da arvore.
 * @throw excecao se arvore vazia.
 * @return elemento da raiz.
 */
int BinarySearchTreeOfInteger::getRoot() {
  if (isEmpty()) {
    throw 0;
  }
  return root->element;
}

/**
 * Insere o elemento na arvore.
 * @param element a ser inserido.
 */
void BinarySearchTreeOfInteger::add(int element) {
  root = add(root, element, NULL);
  count++;
}

NodoAB *BinarySearchTreeOfInteger::add(NodoAB *nodo, int element,
                                       NodoAB *father) {
  if (nodo == NULL) // Encontrou o lugar onde deve ser inserido
  {
    NodoAB *aux = new NodoAB(element);
    aux->father = father;
    return aux;
  }

  // Se elemento eh maior que o nodo atual, entao insere na sub-árvore da
  // direita
  if (element > nodo->element) {
    nodo->right = add(nodo->right, element, nodo);
  } else {
    nodo->left = add(nodo->left, element, nodo);
  }

  return nodo;
}
// Metodo privado que procura por element a partir de n
// e retorna a referencia para o nodo no qual elem esta
// armazenado.
NodoAB *BinarySearchTreeOfInteger::searchNodeRef(int element, NodoAB *nodo) {

  if (nodo == NULL) // não achou!
    return NULL;

  if (nodo->element == element) // achou!
    return nodo;

  if (element < nodo->element) // Se o elemento buscado é menor que o nodo atual
    return searchNodeRef(element, nodo->left); // então, busca à esquerda
  else
    return searchNodeRef(element, nodo->right); // senão, busca à direita

  return NULL;
}

/**
 * Verifica se element esta ou nao armazenado na arvore.
 * @param element
 * @return true se element estiver na arvore, false caso contrario.
 */
bool BinarySearchTreeOfInteger::contains(int elem) {
  NodoAB *nAux = searchNodeRef(elem, root);
  return (nAux != NULL);
}

/**
 * Retorna o filho a esquerda de element.
 * @param element
 * @return o filho a esquerda, ou null se nao tiver filho a esquerda.
 */
NodoAB *BinarySearchTreeOfInteger::getLeft(int element) {
  NodoAB *aux = searchNodeRef(element, root);
  if (aux == NULL)
    throw 0;
  if (aux->left == NULL)
    return NULL;
  return aux->left;
}

/**
 * Retorna o filho a direita de element.
 * @param element
 * @return o filho a direita, ou null se nao tiver filho a direita.
 */
NodoAB *BinarySearchTreeOfInteger::getRigh(int element) {
  NodoAB *aux = searchNodeRef(element, root);
  if (aux == NULL)
    throw 0;
  if (aux->right == NULL)
    return NULL;
  return aux->right;
}

/**
 * Retorna quem e o elemento pai do elemento passado por parametro.
 * @param element
 * @return pai de element
 */
NodoAB *BinarySearchTreeOfInteger::getParent(int element) {
  NodoAB *aux = searchNodeRef(element, root);
  if (aux == NULL)
    throw 0;

  return aux->father;
}

/**
 * Remove element da arvore.
 * @param element elemento a ser removido.
 * @return true se for feita a remocao.
 */
bool BinarySearchTreeOfInteger::remove(int element) { return false; }

/**
 * Troca um elemento da arvore pelo elemento passado por parametro.
 * @param old elemento a ser encontrado para ser substituido.
 * @param element elemento a ser colocado no lugar de old.
 * @return true se fez a troca, false caso contrario.
 */
bool BinarySearchTreeOfInteger::set(int old, int element) { return 0; }

/**
 * Retorna uma lista com todos os elementos da arvore na ordem do
 * caminhamento em largura (por niveis).
 * @return lista com todos os elementos da arvore.
 */
list<int> BinarySearchTreeOfInteger::positionsWidth() {
  list<int> lista;
  Queue fila;

  if (root != NULL) {
    fila.enqueue(root);
    while (!fila.isEmpty()) {

      // Tira o nodo da fila
      NodoAB *aux = fila.dequeue();

      // Coloca o elemento na lista
      lista.push_back(aux->element);

      // Coloca os filhos na fila
      if (aux->left != NULL)
        fila.enqueue(aux->left);
      if (aux->right != NULL)
        fila.enqueue(aux->right);
    }
  }

  return lista;
}

/**
 * Retorna uma lista com todos os elementos da arvore na ordem do
 * caminhamento pre-fixado.
 * @return lista com todos os elementos da arvore.
 */
list<int> BinarySearchTreeOfInteger::positionsPre() {
  list<int> lista;
  positionsPreAux(root, lista);
  return lista;
}
void BinarySearchTreeOfInteger::positionsPreAux(NodoAB *n, list<int> &lista) {
  if (n != NULL) {
    // Visita a raiz
    lista.push_back(n->element);
    // Visita subarvore da esquerda
    positionsPreAux(n->left, lista);
    // Visita subarvore da direita
    positionsPreAux(n->right, lista);
  }
}

/**
 * Retorna uma lista com todos os elementos da arvore na ordem do
 * caminhamento pos-fixado.
 * @return lista com todos os elementos da arvore.
 */
list<int> BinarySearchTreeOfInteger::positionsPos() {
  list<int> lista;
  positionsPosAux(root, lista);
  return lista;
}
void BinarySearchTreeOfInteger::positionsPosAux(NodoAB *n, list<int> &lista) {
  if (n != NULL) {
    // Visita subarvore da esquerda
    positionsPosAux(n->left, lista);
    // Visita subarvore da direita
    positionsPosAux(n->right, lista);
    // Visita a raiz
    lista.push_back(n->element);
  }
}

/**
 * Retorna uma lista com todos os elementos da arvore na ordem do
 * caminhamento central.
 * @return lista com todos os elementos da arvore.
 */
list<int> BinarySearchTreeOfInteger::positionsCentral() {
  list<int> lista;
  positionsCentralAux(root, lista);
  return lista;
}
void BinarySearchTreeOfInteger::positionsCentralAux(NodoAB *n,
                                                    list<int> &lista) {
  if (n != NULL) {
    // Visita subarvore da esquerda
    positionsCentralAux(n->left, lista);
    // Visita a raiz
    lista.push_back(n->element);
    // Visita subarvore da direita
    positionsCentralAux(n->right, lista);
  }
}

/**
 * Retorna true se element esta armazenado em um nodo externo.
 * @param element
 * @return true se element esta em um nodo externo.
 */
bool BinarySearchTreeOfInteger::isExternal(int element) { return false; }

/**
 * Retorna true se element esta armazenado em um nodo interno.
 * @param element
 * @return true se element esta em um nodo interno.
 */
bool BinarySearchTreeOfInteger::isInternal(int element) { return false; }

// Conta o numero de nodos a partir de "n"
int BinarySearchTreeOfInteger::countNodos(NodoAB *n) { return 0; }

int BinarySearchTreeOfInteger::height() {
  if (root == NULL)
    return 0;
  return height(root);
}
int BinarySearchTreeOfInteger::height(NodoAB *n) {
  if (n == NULL){
    return 0;
  }
  else{
  int altesquerda = height(n->left); 
  int altdireita = height(n->right);

  int h;

    if (altesquerda > altdireita){
      h = altesquerda;
    }
    else{
      h = altdireita;
    }

    return h + 1;
  }
}

int BinarySearchTreeOfInteger::level(int element) { return -1; }

int BinarySearchTreeOfInteger::countLeaves() { return 0; }
int BinarySearchTreeOfInteger::countLeaves(NodoAB *n) { return 0; }

void BinarySearchTreeOfInteger::GeraConexoesDOT(NodoAB *nodo) {
  if (nodo == NULL)
    return;

  GeraConexoesDOT(nodo->left);
  //   "nodeA":esq -> "nodeB" [color="0.650 0.700 0.700"]
  if (nodo->left)
    cout << "\"node" << nodo->element << "\":esq -> \"node"
         << nodo->left->element << "\" " <<
        //"[label = " << nodo->hEsq << "]" << endl;
        endl;
  GeraConexoesDOT(nodo->right);
  //   "nodeA":dir -> "nodeB";
  if (nodo->right)
    cout << "\"node" << nodo->element << "\":dir -> \"node"
         << nodo->right->element << "\" " <<
        //"[label = " << nodo->hDir << "]" <<endl;
        endl;
}

void BinarySearchTreeOfInteger::GeraNodosDOT(NodoAB *nodo) {
  if (nodo == NULL)
    return;

  GeraNodosDOT(nodo->left);
  // node10[label = "<esq> | 10 | <dir> "];
  cout << "node" << nodo->element << "[label = \"<esq> | " << nodo->element
       << " | <dir> \"]" << endl;
  GeraNodosDOT(nodo->right);
}

void BinarySearchTreeOfInteger::GeraConexoesDOT() { GeraConexoesDOT(root); }

void BinarySearchTreeOfInteger::GeraNodosDOT() { GeraNodosDOT(root); }

void BinarySearchTreeOfInteger::GeraDOT() {
  cout << "digraph g { \nnode [shape = record,height=.1];\n" << endl;
  // node [style=filled];

  GeraNodosDOT();
  cout << endl;
  GeraConexoesDOT();
  cout << "}" << endl;
}

// Retorna se a arvore inteira esta balanceada ou não.
// Metodo publico da classe.
bool BinarySearchTreeOfInteger::isBalanced(){
  return isBalanced(root);
}


// Retorna se um nodo da arvore esta balanceado ou não.
// Metodo privado da classe, só podendo ser acessado por funções dela mesma.
bool BinarySearchTreeOfInteger::isBalanced(NodoAB *r) {

  int altdireita, altesquerda, diferenca;

  if (r == NULL)
    return true;
  
  altesquerda = height(r->left); 
  altdireita = height(r->right);

  diferenca = altesquerda - altdireita;
  if (diferenca < 0){
    diferenca *= -1;
    }

  if (diferenca <= 1 && isBalanced(r->left) && isBalanced(r->right)){
      return true;
    }
  
  return false;
}

// Aplica o balanceamento da arvore inteira.
// Metodo publico da classe.
void BinarySearchTreeOfInteger::ApplyBalancing() {
  if (isBalanced(root)) {
    cout << "Já esta balanceada" << endl;
    exit(1);
  }

  root = Balance(root);
}

// Aplica o balanceamento de um nodo da arvore.
// Metodo privado da classe, só podendo ser acessado por funções dela mesma.
NodoAB *BinarySearchTreeOfInteger::Balance(NodoAB *r) {
  //cout << "Begin Balance" << endl;
  //cout << r->element << endl;
  
  if (isBalanced(r)){
    return r;
  }  

  
  int dif = height(r->left) - height(r->right);
  if(dif < 0)
    dif *=-1;

  //cout << "Diferenca: " << dif << endl;

  if(height(r->left) > height(r->right) && dif > 1){
    if(height(r->left->right) > height(r->left->left)){
      r = rotateLeftRight(r);
    }
    else{
      r = rotateLeftLeft(r);
    }
  }

  
  dif = height(r->left) - height(r->right);
  if(dif < 0)
    dif *=-1;
  
  if(height(r->left) < height(r->right) && dif > 1){
    if(height(r->right->left) > height(r->right->right)){
       r = rotateRightLeft(r);
    }
    else{
      r = rotateRightRight(r);    
    }
  }

  
  dif = height(r->left) - height(r->right); 
  if(dif < 0)
    dif *=-1;
  
  if(dif <= 1){
    if(isBalanced(r->right) == false){
      r->right = Balance(r->right);
    }
    if(isBalanced(r->left) == false){
      r->left = Balance(r->left);
    }
  }
  

  if (isBalanced(r) == false){
    r = Balance(r);
  }

 // cout << "End Balance" << endl;
  return r;
}

// Faz o movimento de rotação Esquerda Esquerda.
NodoAB* BinarySearchTreeOfInteger::rotateLeftLeft(NodoAB *r){
  cout << "Rotate Left Left" << endl;
  cout << "Valor rotacionado: " << r->element << endl;
  cout << endl;
  
  NodoAB *aux = r->left;
  r->left = aux->right;
  aux->right = r; 
  aux->father = r->father;  
  r->father = aux;
  
  //cout << "End Rotate Left" << endl;
  return aux;
}

// Faz o movimento de rotação Direita Direita.
NodoAB* BinarySearchTreeOfInteger::rotateRightRight(NodoAB *r){
  cout << "Rotate Right Right" << endl;
  cout << "Valor rotacionado: " << r->element << endl;
  cout << endl;
  
  NodoAB *aux = r->right;
  r->right = aux->left;
  aux->left = r;
  aux->father = r->father;
  r->father = aux;

  //cout << "End Rotate Right" << endl;
  return aux;
}

// Faz o movimento de rotação Direita Esquerda.
NodoAB* BinarySearchTreeOfInteger::rotateRightLeft(NodoAB *r){
  cout << "Rotate Right Left" << endl;
  cout << "Valor rotacionado: " << r->element << endl;
  cout << endl;
  
  r->right = rotateLeftLeft(r->right);
  r = rotateRightRight(r);

//  cout << "End Rotate Right Left" << endl;
  return r;
}

// Faz o movimento de rotação Esquerda Direita.
NodoAB* BinarySearchTreeOfInteger::rotateLeftRight(NodoAB *r){
  cout << "Rotate Left Right" << endl;
  cout << "Valor rotacionado: " << r->element << endl;
  cout << endl;
  
  r->left = rotateRightRight(r->left);
  r = rotateLeftLeft(r);
  
 // cout << "End Rotate Left Right" << endl;
  return r;
}


// Faz o balanceamento da arvore especifica que esta sendo criada nesse programa,
// para cada arvore diferente a funcao deve ser alterada.
void BinarySearchTreeOfInteger::testBalance(){
  root = rotateLeftRight(root);
  GeraDOT();
  root = rotateLeftLeft(root);
  GeraDOT();
  root->right = rotateLeftLeft(root->right);
  GeraDOT();
  root->right->left = rotateRightRight(root->right->left);
  GeraDOT();
  root->left = rotateRightLeft(root->left);
  GeraDOT();
  root->left = rotateLeftRight(root->left);
  GeraDOT();
}