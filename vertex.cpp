#include "vertex.h"
#include "edge.h"

using namespace std;

//function to return the data in vertex
string Vertex::operator*() {
    return element;
}

//function to return the vectors its connected with
vector<Edge*> Vertex::incidentEdges(){
    return adjEdges;
}

//function to check if v is a neighbor to current vertex
bool Vertex::isAdjacentTo(Vertex* v){
    for(Edge* e: adjEdges){
        if (e->opposite(this) == v) return true;
    }
    return false;
}

//function to insert an edge
void Vertex::addEdge(Edge* e){
    adjEdges.push_back(e);
}

//function to remove an Edge
void Vertex::removeEdge(Edge* e){
    for(auto it = adjEdges.begin(); it != adjEdges.end(); ++it){
        if (*it == e) {
            adjEdges.erase(it);
            return;
        }
    }
}
