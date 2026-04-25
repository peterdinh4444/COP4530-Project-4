#include "vertex.h"
#include "edge.h"

using namespace std;

// Returns the name/data stored within the vertex
string Vertex::operator*() {
    return element;
}

// Returns the collection of all edges connected to this vertex
vector<Edge*> Vertex::incidentEdges(){
    return adjEdges;
}

// Determines if this vertex is directly connected to vertex 'v' via an edge
bool Vertex::isAdjacentTo(Vertex* v){
    for(Edge* e: adjEdges){
        // If the vertex on the other side of the edge is 'v', they are neighbors
        if (e->opposite(this) == v) return true;
    }
    return false;
}

// Adds a pointer to an edge into the local adjacency list
void Vertex::addEdge(Edge* e){
    adjEdges.push_back(e);
}

// Locates and removes a specific edge pointer from the adjacency list
void Vertex::removeEdge(Edge* e){
    for(auto it = adjEdges.begin(); it != adjEdges.end(); ++it){
        if (*it == e) {
            adjEdges.erase(it);
            return;
        }
    }
}