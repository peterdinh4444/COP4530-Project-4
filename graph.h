#ifndef GRAPH_H
#define GRAPH_H

#include "vertex.h"
#include "edge.h"
using namespace std;




// Helper function for Vertex Vector
Vertex* findVertex(string name, const vector<Vertex*>& allVertices){
    for (auto vertex : allVertices){
        if (vertex->operator*() == name){
            return vertex;
        }
    }
    return nullptr;
};


// Graph Class definition
class Graph{
public: 
    int numVertices;
    int numEdges;
    vector<Vertex*> allVertices;

    Graph(string filename){
        numVertices = 0;
        numEdges = 0;
        ifstream file(filename);
        string line;

        // Return if file didn't open
        if (!file.is_open())
            return; 

        // Handles first line of the text file
        if (getline(file, line)){
            stringstream stream(line);
            while(getline(stream, line, '\t')){
                Vertex* newVertex = new Vertex(line);
                allVertices.push_back(newVertex);
                numVertices++;
            }
        }

        // Handles Edges and appends them to Adjacency lists 
        while (getline(file, line)){
            stringstream stream(line);
            getline(stream, line, '\t');
            Vertex* v1 = findVertex(line, allVertices);
            getline(stream, line, '\t');
            Vertex* v2 = findVertex(line, allVertices);
            getline(stream, line, '\t');
            float edgeLabel = stof(line);
            Edge* newEdge = new Edge(v1, v2, edgeLabel);
            numEdges++;
            v1->addEdge(newEdge);
            v2->addEdge(newEdge);

        }
    }
};



#endif