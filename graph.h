#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <string>
#include "vertex.h"
#include "edge.h"

using namespace std;

class Graph {
private:
    vector<Vertex*> allVertices; // Internal storage for all nodes
    vector<Edge*> allEdges;      // Internal storage for all connections

    // Helper functions for internal lookups
    Vertex* findVertex(const string& name);
    Edge* findEdge(Vertex* v, Vertex* w);

public:
    // Lifecycle management
    Graph(const string& filename); // Load graph from a formatted text file
    ~Graph();                      // Clean up all dynamically allocated memory

    // Accessors for graph components
    vector<Vertex*> vertices();
    vector<Edge*> edges();

    // Modification methods
    Vertex* insertVertex(const string& x);
    Edge* insertEdge(Vertex* v, Vertex* w, float x);

    // Deletion methods
    bool eraseVertex(Vertex* v); // Removes vertex and all its incident edges
    bool eraseEdge(Edge* e);   // Removes specific edge from graph and vertices

    // Public utilities
    Vertex* getVertex(const string& name); // Interface for main.cpp access

    // Graph algorithms and reporting
    void printIncidentEdges(const string& name);                  // List edges of a specific node
    void findPath(const string& startName, const string& endName); // BFS-based pathfinding
};

#endif