#ifndef EDGE_H
#define EDGE_H

#include <vector>
#include <string>

using namespace std;

// Forward declaration to resolve circular dependency
class Vertex;

class Edge {
private:
    Vertex* v1;    // First endpoint of the edge
    Vertex* v2;    // Second endpoint of the edge
    float label;   // Distance or weight value for this edge

public:
    // Constructor: links two vertices with a numeric weight
    Edge(Vertex* u, Vertex* v, const float& x) : v1(u), v2(v), label(x) {}

    // Operator overload to return the weight (label) value
    float operator*();

    // Returns a list containing the two endpoints
    vector<Vertex*> endVertices();

    // Given one endpoint, returns the vertex at the other side
    Vertex* opposite(Vertex* v);

    // Determines if this edge shares a vertex with another edge
    bool isAdjacentTo(Edge* e);

    // Determines if a specific vertex is one of the endpoints
    bool isIncidentOn(Vertex* v);
};

#endif