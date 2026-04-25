#include <iostream>
#include <queue>
#include <fstream>
#include <sstream>
#include <map>
#include <algorithm>
#include "graph.h"

using namespace std;

// Constructor: parses file to build the graph structure
Graph::Graph(const string& filename) {
    ifstream file(filename);
    if(!file.is_open()){
        cout << "Error: file could not be opened." << endl;
        return;
    }

    string line;
    // Read the header line to initialize vertices
    if (getline(file, line)) {
        stringstream ss(line);
        string vertexName;
        // Using >> handles varied whitespace more robustly than getline with '\t'
        while (ss >> vertexName) {
            insertVertex(vertexName);
        }
    }

    // Read subsequent lines to define edges between vertices
    while (getline(file, line)) {
        if (line.empty()) continue;

        stringstream stream(line);
        string v1Name, v2Name, labelText;

        // Extracting endpoints and edge weight
        getline(stream, v1Name, '\t');
        getline(stream, v2Name, '\t');
        getline(stream, labelText, '\t');

        Vertex* v1 = findVertex(v1Name);
        Vertex* v2 = findVertex(v2Name);

        if (v1 != nullptr && v2 != nullptr) {
            float edgeLabel = stof(labelText);
            insertEdge(v1, v2, edgeLabel);
        }
    }
}

// Destructor: releases all dynamically allocated memory for vertices and edges
Graph::~Graph() {
    for (Edge* e : allEdges) delete e;
    for (Vertex* v : allVertices) delete v;
}

// Internal helper to locate a vertex by its string name
Vertex* Graph::findVertex(const string& name){
    for(Vertex* v : allVertices){
        if(**v == name) return v;
    }
    return nullptr;
}

// Public interface for finding a vertex
Vertex* Graph::getVertex(const string& name){
    return findVertex(name);
}

// Locates an existing edge between two specific vertices
Edge* Graph::findEdge(Vertex* v1, Vertex* v2) {
    for (Edge* e : allEdges) {
        if (e->isIncidentOn(v1) && e->isIncidentOn(v2)) return e;
    }
    return nullptr;
}

vector<Vertex*> Graph::vertices() { return allVertices; }
vector<Edge*> Graph::edges() { return allEdges; }

// Creates a new vertex if it doesn't already exist
Vertex* Graph::insertVertex(const string& x) {
    Vertex* existing = findVertex(x);
    if (existing != nullptr) return existing;

    Vertex* newVertex = new Vertex(x);
    allVertices.push_back(newVertex);
    return newVertex;
}

// Creates a new edge and links it to the associated vertices
Edge* Graph::insertEdge(Vertex* v, Vertex* w, float x) {
    if (v == nullptr || w == nullptr || findEdge(v, w) != nullptr) return nullptr;

    Edge* newEdge = new Edge(v, w, x);
    allEdges.push_back(newEdge);
    v->addEdge(newEdge);
    w->addEdge(newEdge);

    return newEdge;
}

// Removes an edge from the graph and updates vertex adjacency lists
bool Graph::eraseEdge(Edge* e) {
    if (e == nullptr) return false;

    vector<Vertex*> endpoints = e->endVertices();
    endpoints[0]->removeEdge(e);
    endpoints[1]->removeEdge(e);

    for (auto it = allEdges.begin(); it != allEdges.end(); ++it) {
        if (*it == e) {
            allEdges.erase(it);
            delete e;
            return true;
        }
    }
    return false;
}

// Deletes a vertex and ensures all its connected edges are also removed
bool Graph::eraseVertex(Vertex* v) {
    if (v == nullptr) return false;

    vector<Edge*> incident = v->incidentEdges();
    for (Edge* e : incident) eraseEdge(e);

    for (auto it = allVertices.begin(); it != allVertices.end(); ++it) {
        if (*it == v) {
            allVertices.erase(it);
            delete v;
            return true;
        }
    }
    return false;
}

// Outputs all neighbors and edge weights for a given vertex
void Graph::printIncidentEdges(const string& name){
    Vertex* v = findVertex(name);
    if (v == nullptr) {
        cout << "Error: vertex not in graph." << endl;
        return;
    }

    vector<Edge*> incident = v->incidentEdges();
    if (incident.empty()) {
        cout << "No connected edges." << endl;
        return;
    }

    for (Edge* e : incident) {
        Vertex* other = e->opposite(v);
        cout << **v << " to " << **other << " is " << *(*e) << " mi" << endl;
    }
}

// Breadth-First Search to find the shortest unweighted path
void Graph::findPath(const string& startName, const string& endName) {
    Vertex* start = findVertex(startName);
    Vertex* end = findVertex(endName);

    if (start == nullptr || end == nullptr) {
        cout << "Error: One or both vertices not found." << endl;
        return;
    }

    queue<Vertex*> q;
    map<Vertex*, Vertex*> parent;
    map<Vertex*, bool> visited;

    q.push(start);
    visited[start] = true;
    parent[start] = nullptr;

    while (!q.empty()) {
        Vertex* current = q.front();
        q.pop();

        if (current == end) break;

        for (Edge* e : current->incidentEdges()) {
            Vertex* neighbor = e->opposite(current);
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                parent[neighbor] = current;
                q.push(neighbor);
            }
        }
    }

    if (!visited[end]) {
        cout << "No path found." << endl;
        return;
    }

    // Reconstruct path from end to start
    vector<Vertex*> path;
    for (Vertex* curr = end; curr != nullptr; curr = parent[curr]) {
        path.push_back(curr);
    }
    reverse(path.begin(), path.end());

    // Path must contain at least 2 vertices (start and end)
    if (path.size() < 2) {
        cout << "No valid path found." << endl;
        return;
    }

    // Print the final path
    for (int i = 0; i < path.size(); i++) {
        cout << **path[i] << (i != path.size() - 1 ? " to " : "");
    }
    cout << endl;
}