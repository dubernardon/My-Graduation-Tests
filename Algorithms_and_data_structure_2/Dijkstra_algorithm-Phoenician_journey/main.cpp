#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>
#include <stdlib.h>
#include "Graph.h"

using namespace std;

#define FilePath "Casos de teste/case0.map"

typedef pair <int,int> pii;



void divideLinha(string linha, char** map, int linhaAtual){
  for(int i = 0; i < linha.size(); i++){
    map[linhaAtual][i] = linha[i];
  }
}



void readHeader(int* linhas, int* colunas, const char* filename){
  ifstream arquivo;

  arquivo.open(filename, ios::in);
    if (!arquivo) {
    cout << "Erro na abertura do arquivo '" << filename << endl;
    exit(1);
  }

  string linha;
  getline(arquivo, linha);

  stringstream S;
  S.str(linha);
  string palavra;
  int count = 0;

  while(getline(S, palavra, ' ')){
    if (count == 0)  *linhas = stoi(palavra);
    if (count == 1)  *colunas = stoi(palavra);
    count++;
  }
  
  arquivo.close();
}



void readFile(char** map, const char* filename){
  ifstream arquivo;

  arquivo.open(filename, ios::in);
    if (!arquivo) {
    cout << "Erro na abertura do arquivo '" << filename << endl;
    exit(1);
  }

  string linha;
  getline(arquivo, linha);

  int linhaAtual = 0;
  while(getline(arquivo, linha)){
    divideLinha(linha, map, linhaAtual);
    linhaAtual++;
  }
  arquivo.close();
}



void writeGraph(Graph navegacao){
  string linha;
  stringstream s = navegacao.toString();
  
  ofstream GraphArestas;

   GraphArestas.open("GraphArestas.txt", ios :: out );
  
  if (!GraphArestas) {
    cout << "Erro na abertura do arquivo '" << "GraphArestas" << endl;
    exit(1);
    
  }
  while(getline(s,linha))
  GraphArestas << linha << endl;
  
  GraphArestas.close();
}



void printMap(char** map, int linhas, int colunas){
  cout << linhas <<  " " << colunas << endl;

  for(int i = 0; i < linhas; i++){
    for(int j = 0; j < colunas; j++){
      cout << map[i][j];
    }
    cout << endl;
  }

  cout << "Numero de Vertices: " << linhas * colunas <<  endl;
}



Graph createGraph(char** map, int linhas, int colunas, int* portos){
  Graph navegacao(linhas * colunas);
  int v, w;
  //percorre linhas e colunas
  for(int l = 0; l < linhas; l++){
    for(int c = 0; c < colunas; c++){   
      if(map[l][c] != '*'){
       //se não for * e ainda for coluna salva 
        if(map[l][c+1] != '*' && c+1 < colunas){
          v = c + (l * colunas);
          w = (c + 1) + (l * colunas);
          navegacao.addEdge(v, w);
        }
        //se não for * e ainda for linha salva 
        if(map[l+1][c] != '*' && l+1 < linhas){
          v = c + (l * colunas);
          w = c + ((l + 1) * colunas);
          navegacao.addEdge(v, w);
        }
        //se não for * e for linha salva 
        if(map[l-1][c] != '*' && l != 0){
          v = c + (l * colunas);
          w = c + ((l - 1) * colunas);
          navegacao.addEdge(v, w);
        }
        //se não for * e for coluna salva 
        if(map[l][c-1] != '*' && c != 0){
          v = c + (l * colunas);
          w = (c - 1) + (l * colunas);
          navegacao.addEdge(v, w);
        }
      }  
      //se for um porto, salva o porto
      if( map[l][c] <= '9' && map[l][c] > '0'){
        int por = map[l][c] - '0';
        portos[por] = c + (l * colunas);
      }
    }
  }
  
  return navegacao;
}



vector<int> caminhamento(Graph navegacao, int source){
  //retorna a quantidade de vertices
  int n = navegacao.returnV();
  vector<int> distTo(n, 0);
  vector<bool> visitado(n, false);
  priority_queue<pii, vector<pii>, greater<pii>> pq;

  distTo[source] = 0;
  pq.push(make_pair(0,source));

  while(!pq.empty()){
    int u = pq.top().second;
    pq.pop();
   //se já foi visitado, continua
    if (visitado[u]){
      continue;
    }
    //marca se o vértice foi visitacado
    visitado[u] = true;
    //encontra os possíveis destinos
    for(const auto& edge : navegacao.returnConections(u)){
      int v = edge;
      int weight = 1;

      if (distTo[u] + weight < distTo[v] || distTo[v] < 1){
        distTo[v] = distTo[u] + weight;
        pq.push(make_pair(distTo[v], v));
      }  
    }  
  }
  return distTo;
}



int findDistTo(int* portos, Graph navegacao, int* portoAtual, int* destino){
  vector<int> distTo = caminhamento(navegacao, portos[*portoAtual]);
  //verifica se achou o porto, ou seja, se é acessível e retorna o caminho curto
  while(*destino < 10){
    if (distTo[portos[*destino]] != 0){
      cout << "Achou: " << *portoAtual << " -> " << *destino
      << " : " << distTo[portos[*destino]] << endl;
      *portoAtual = *destino;
      return distTo[portos[*destino]];
    }
    else{
      cout << "Nao Achou: " << *portoAtual << " -> " << *destino << endl;
      //se não achou vai para o próximo porto disponível
      *destino += 1;
    }
  }
  
  return 0;
}



int findDistTotal(Graph navegacao, int* portos){
  int distTotal = 0;
  int dist = 0;

  int *portoAtual, *destino;
  portoAtual = new int;
  destino = new int;
  *portoAtual = 1;
  *destino = 2;

  int portoInicial = 1;
  //percorre todos os portos
  while(*portoAtual != 9 && *destino < 10){
    //pega a menor distancia para acessar todos os portos
    dist = findDistTo(portos, navegacao, portoAtual, destino);
    //se o porto for bloqueado, passa para o próximo
    if(dist != 0){
      *destino = *portoAtual + 1;
      distTotal += dist;
    }
    else{ 
      //se não tem saída o porto inicial, inicia pelo próximo porto
      if(*portoAtual == portoInicial && *destino == 10 && distTotal == 0){
        *portoAtual += 1;
        portoInicial = *portoAtual;
        *destino = *portoAtual + 1;
      }
    }
  }

  *destino = portoInicial;
  distTotal += findDistTo(portos, navegacao, portoAtual, destino);

  delete portoAtual;
  delete destino;
  
  return distTotal;
}



int main() {
  int *linhas, *colunas;
  linhas = new int;
  colunas = new int;
  
  readHeader(linhas, colunas, FilePath);

  char** map;
  const int l = *linhas;
  const int c = *colunas;

  delete linhas;
  delete colunas;
  
  map = new char *[l];
  for(int i = 0; i < l; i++){
    map[i] = new char[c];
  }

  readFile(map, FilePath);

 // printMap(map, l, c); // Imprime o mapa no console.

  Graph navegacao(l * c);
  int portos[10];

  navegacao = createGraph(map, l, c, portos);

  delete map;

  
  for(int i = 1; i < 10; i++){                          // Imprime no console
    cout <<"Porto " << i << ": " << portos[i] << endl;  // as coordenadas dos
  }                                                     // portos.
  

 // writeGraph(navegacao);  // Cria um arquivo .txt com o grafo,
                            // com todos os vertices e suas conexões.

  int distTotal = findDistTotal(navegacao, portos);

  cout << "Distancia Total(combustivel): " << distTotal << endl;
}