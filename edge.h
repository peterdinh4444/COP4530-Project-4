#ifndef EDGE_H
#define EDGE_H

#include <vector>
#include <string>

using namespace std;

class Vertex;

class Edge{
private:
    Vertex* v1; //pointers for different vertexes
    Vertex* v2;
    float label;   //the weight for the edge

public:
    //Constructor to initialize an edge with two vertices and a label
    Edge(Vertex* u, Vertex* v, const float& x) : v1(u), v2(v), label(x){}

    //function to get data stored in edge
    string operator*();

    //returns the two vertex objects the edge connects
    vector<Vertex*> endVertices();

    //function to return the vertex on the other end given a vertex
    Vertex* opposite(Vertex* v);

    //check if edge shares a vertex with edge e
    bool isAdjacentTo(Edge* e);

    //check if edge is connected to vertex v
    bool isIncidentOn(Vertex* v);
};

#endif