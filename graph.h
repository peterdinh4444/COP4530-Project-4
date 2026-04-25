#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <string>
#include "vertex.h"
#include "edge.h"
using namespace std;


// Graph Class definition
class Graph{
private:
vector<Vertex*> allVertices;
vector<Edge*> allEdges;

Vertex* findVertex(const string& name);
Edge* findEdge(Vertex* v, Vertex* w);

public:
Graph(const string& filename);
~Graph();

vector<Vertex*> vertices();
vector<Edge*> edges();

Vertex* insertVertex(const string& x);
Edge* insertEdge(Vertex* v, Vertex* w, float x);

bool eraseVertex(Vertex* v);
bool eraseEdge(Edge* e);

Vertex* getVertex(const string& name);

void printIncidentEdges(const string& name);
void findPath(const string& startName, const string& endName);
};

#endif