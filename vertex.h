#ifndef VERTEX_H
#define VERTEX_H

#include <vector>
#include <string>

using namespace std;

// Forward declaration to resolve circular dependency with Edge class
class Edge;

class Vertex {
private:
    string element;           // The name or data stored in the vertex (e.g., "USF")
    vector<Edge*> adjEdges;   // List of all edges connected to this vertex

public:
    // Constructor: initializes vertex with a string identifier
    Vertex(string x) : element(x) {}

    // Operator overload to return the vertex name
    string operator*();

    // Returns a vector of all edges incident on this vertex
    vector<Edge*> incidentEdges();

    // Checks if this vertex shares an edge with vertex 'v'
    bool isAdjacentTo(Vertex* v);

    // Adds a pointer to an edge into the adjacency list
    void addEdge(Edge* e);

    // Removes a specific edge pointer from the adjacency list
    void removeEdge(Edge* e);
};

#endif