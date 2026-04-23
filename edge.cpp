#include "edge.h"
#include "vertex.h"
#include <vector>
#include <string>

using namespace std;

//function to return label of current node
string Edge::operator*(){
    return label;
}

//function to return the two vertices the edge connects
vector<Vertex*> Edge::endVertices(){
    return {v1, v2};
}

//function for returning opposite vertex
Vertex* Edge::opposite(Vertex* v){
if(v == v1)
return v2;  //return opposite
if(v == v2)
return v1;  //return opposite
return nullptr; //if V is not part of edge return null
}

//function to check if edge shares a vertex with another edge
bool Edge::isAdjacentTo(Edge* e){
    vector<Vertex*> otherVertices = e->endVertices();   //get the vertexes e connects to

    //check if any of the vertexes are the same if they are they have an edge connecting them
    return (v1 == otherVertices[0] || v1 == otherVertices[1] || v2 == otherVertices[0] || v2 == otherVertices[1]);
}

//check if edge is connected to a vertex v
bool Edge::isIncidentOn(Vertex* v){
    return(v1 == v || v2 == v); //return true if edges vertices are the vertex
}