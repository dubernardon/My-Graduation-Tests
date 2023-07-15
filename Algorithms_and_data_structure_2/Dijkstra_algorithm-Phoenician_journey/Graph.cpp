#include <iostream>
#include <sstream>
#include "Graph.h"

using namespace std;

Graph:: Graph(int V) {
        if (V < 0) {
          cout << "Number of vertices must be nonnegative" << endl;
        }
        this->V = V;
        this->E = 0;
        vector<int> pilha;
        for (int v = 0; v < V; v++) {
          this->adj.push_back(pilha);
        }        
    }


 void Graph::validateVertex(int v) {
        if (v < 0 || v >= V)
            cout << "vertex " << v << " is not between 0 and " << (V-1) << endl;
    }


  void Graph::addEdge(int v, int w) {
        validateVertex(v);
        validateVertex(w);
        this->E++;
        this->adj[v].push_back(w);
        this->adj[w].push_back(v);
    }

int Graph:: returnV() {
  return this->V;
    }

int Graph:: returnE(){
  return this->E;
}

int Graph::degree(int v) {
        validateVertex(v);
        return adj[v].size();
    }

 stringstream Graph::toString() {
  stringstream s;
    s << this->V << " vertices, " << this->E << " edges " << endl;
      for (int v = 0; v < V; v++) {
        s << v << ": ";
          for (int w : adj[v]) {
            s << w << " ";
          }
        s << endl;
      }

  return s;
 }

vector<int> Graph::returnConections(int u){
  return this->adj[u];
}