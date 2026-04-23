#ifndef VERTEX_H
#define VERTEX_H

#include <vector>
#include <string>

using namespace std;

class Edge;

class Vertex{
    private:
    string element; //the data stored in the vertex
    vector <Edge*> adjEdges; //vector of edges connected to the vertex

    public:
    //constructor for vertex
    Vertex(string x) : element(x){}

    //function to get data stored in vertex
    string operator*();

    //function to get edges incident on vertex
    vector<Edge*> incidentEdges();

    //function to check if the vertex is adjacent to vertex 
    bool isAdjacentTo(Vertex* v);

    //function for graph class and adding edges
    void addEdge(Edge* e);

    //function for erasing an edge from vertex list
    void removeEdge(Edge* e);
};

#endif