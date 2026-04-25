#include "edge.h"
#include "vertex.h"
#include <vector>
#include <string>

using namespace std;

// Returns the weight/label value of the edge
float Edge::operator*(){
    return label;
}

// Returns the two vertices that this edge connects
vector<Vertex*> Edge::endVertices(){
    return {v1, v2};
}

// Given one endpoint, returns the vertex at the other end
Vertex* Edge::opposite(Vertex* v){
    if(v == v1) return v2;
    if(v == v2) return v1;
    return nullptr; // Returns null if v is not an endpoint of this edge
}

// Checks if this edge and edge 'e' share at least one common vertex
bool Edge::isAdjacentTo(Edge* e){
    vector<Vertex*> otherVertices = e->endVertices();
    return (v1 == otherVertices[0] || v1 == otherVertices[1] || 
            v2 == otherVertices[0] || v2 == otherVertices[1]);
}

// Checks if vertex 'v' is one of the two endpoints of this edge
bool Edge::isIncidentOn(Vertex* v){
    return (v1 == v || v2 == v);
}