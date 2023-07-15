#ifndef GRAPH
#define GRAPH

#include <iostream>
#include <vector>
#include <sstream>

using namespace std;


class Graph{

private:

 int V;
 int E;
 vector <vector<int>> adj;

public:

Graph(int v);
int returnV();
int returnE();
vector<int> returnConections(int u); 
void validateVertex(int v);
void addEdge(int v, int w);
int degree(int v);
stringstream toString();
};

#endif