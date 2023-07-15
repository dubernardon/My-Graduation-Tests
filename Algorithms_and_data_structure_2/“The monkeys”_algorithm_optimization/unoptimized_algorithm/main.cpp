#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <vector>
#include <time.h>

#include "Macaquinho.h"

using namespace std;

int rodadas;

vector<Macaquinhos> readArchive() {

  vector<Macaquinhos> macaquinhos;

  ifstream macaquinhosCSV;

  macaquinhosCSV.open("./caso_200Macacos_20000Rodadas.txt", ios::in);

  if (!macaquinhosCSV.is_open()) {
    cout << "Erro ao abrir o dados.csv" << endl;
  }

  string linha;
  stringstream linhaRodadas;
  string rodadaPronta;

  // rodadas:
  getline(macaquinhosCSV, linha);
  linhaRodadas << linha;
  // pega até o espaço antes do valor:
  getline(linhaRodadas, rodadaPronta, ' ');
  // pega o valor
  getline(linhaRodadas, rodadaPronta, ' ');

  // passando a quantidade de rodadas
  rodadas = stoi(rodadaPronta);

  while (getline(macaquinhosCSV, linha)) {

    stringstream delimitarString;
    delimitarString << linha;
    string stringPronta;
    int particaoAtual = 0;

    Macaquinhos *novoMacaco = new Macaquinhos();

    // pega o Macaco ;
    getline(delimitarString, stringPronta, ' ');
    // pega o valor
    getline(delimitarString, stringPronta, ' ');
    novoMacaco->setMacaco(stoi(stringPronta));
    // pega o par
    getline(delimitarString, stringPronta, ' ');
    // pega a ->
    getline(delimitarString, stringPronta, ' ');
    // pega o valor par
    getline(delimitarString, stringPronta, ' ');
    novoMacaco->setPar(stoi(stringPronta));
    // pega o impar
    getline(delimitarString, stringPronta, ' ');
    // pega a ->
    getline(delimitarString, stringPronta, ' ');
    // pega o valor impar
    getline(delimitarString, stringPronta, ' ');
    novoMacaco->setImpar(stoi(stringPronta));
    // pega tudo antes da quantidade de cocos
    getline(delimitarString, stringPronta, ' ');
    // pega a quantidade de cocos
    getline(delimitarString, stringPronta, ' ');
    
    novoMacaco->setCocos(stoi(stringPronta));
    getline(delimitarString, stringPronta, ' ');
    // começa a pegar a sequencia de pedrinhas
    while (getline(delimitarString, stringPronta, ' ')) {
      novoMacaco->setPedrinhas(stoi(stringPronta));
    }
    // coloca os macacos em um vector
    macaquinhos.push_back(*novoMacaco);
  }

  return macaquinhos;
}
// realiza a troca de cocos de cada rodada
vector<Macaquinhos> trocaDeCocos(vector<Macaquinhos> macaquinhos) {

  // passa por todos macacos em cada rodada
  for (auto i = macaquinhos.begin(); i < macaquinhos.end(); i++) {
    // se o macaco ainda tiver cocos, ele pode passar adiante pedrinhas.
    while (i->getCocos() != 0) {
      int pedrinhas = i->getPedrinhas();
      // se for par
      if (pedrinhas % 2 == 0) {
        // aumenta a quantidade de cocos e coloca as pedrinhas no vector do
        // macaco que recebeu.
        macaquinhos[i->getPar()].setPedrinhas(pedrinhas);
        macaquinhos[i->getPar()].aumentaCocos();
      } // se for impar
      else {
        // aumenta a quantidade de cocos e coloca as pedrinhas no vector do
        // macaco que recebeu.
        macaquinhos[i->getImpar()].setPedrinhas(pedrinhas);
        macaquinhos[i->getImpar()].aumentaCocos();
      }
      // diminui um coco
      i->reduzCocos();
    }
  }
  return macaquinhos;
}
// busca no vector de macacos o que tem a maior quantidade de cocos
int procuraVencedor(vector<Macaquinhos> macaquinhos) {
  int numeroMacaco = 0, numeroCocos = 0;
  for (auto i = macaquinhos.begin(); i < macaquinhos.end(); i++) {
    if (i->getCocos() > numeroCocos) {
      numeroCocos = i->getCocos();
      numeroMacaco = i->getMacaco();
    }
  }

  return numeroMacaco;
}

void writeTXT(vector<Macaquinhos> macaquinhos) {

  cout << "O arquivo macacos.txt possui um relatório final de pedrinhas por "
          "macaco!"
       << endl;

  cout << "Salvando relatório de pedrinhas por macaco..." << endl;

  ofstream macacosTXT;

  macacosTXT.open(" macacos.txt ", ios ::out);

  if (!macacosTXT.is_open()) {
    cout << "Erro na escrita do macacos.TXT (relatorio das pedrinhas" << endl;
  } // Se houver erro , avisa

  macacosTXT << "Número de pedrinhas para cada macaco:" << endl << endl;
  // mostra todas as pedrinhas do vector de cada macaco
  for (auto i = macaquinhos.begin(); i < macaquinhos.end(); i++) {
    macacosTXT << "Macaco: " << i->getMacaco() << endl;
    macacosTXT << "Numero de cocos: " << i->getCocos() << endl;
    macacosTXT << "Pedrinhas: " << endl;
    i->showPedrinhas(macacosTXT);
    macacosTXT << "==================" << endl;
  }

  macacosTXT.close();
}

int main() {

  clock_t comeco, fim;

  // coloca os macacos em um vector
  vector<Macaquinhos> macaquinhos = readArchive();

  //pega o tempo de começo de execução do algoritmo de troca
    comeco = clock();

  // realiza a quantidade de rodadas que foram lidas
  for (int i = 0; i < rodadas; i++) {
    macaquinhos = trocaDeCocos(macaquinhos);
  }


 // writeTXT(macaquinhos);


  int macacoVencedor = procuraVencedor(macaquinhos);
    
    //pega o tempo de fim de execução
    fim = clock();
  
    // Calculando o tempo total
    double tempo = double(fim - comeco) / double(CLOCKS_PER_SEC);
    cout << "Tempo de execução: " << fixed 
         << tempo;
    cout << " segundos " << endl;
   cout << "O macaco vencedor é o: " << macacoVencedor << endl;
    return 0;
}