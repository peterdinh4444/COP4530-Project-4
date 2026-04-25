#include <iostream>
#include <queue>
#include <fstream>
#include <sstream>
#include <map>
#include <algorithm>
#include "graph.h"

using namespace std;

//Constructor for graph class reads input file and builds graph
Graph::Graph(const string& filename) {
    ifstream file(filename);   //open file with input from user

    if(!file.is_open()){   //if cannot be opened print error message
        cout << "Error: file could not be opened." << endl;
        return;
    }
    string line;

        //Read the first line of the file
    if (getline(file, line)) {
        stringstream ss(line);
        string vertexName;

        //read each vertex name from first line and add it to graph
        while (ss >> vertexName) {
            insertVertex(vertexName);
        }
    }

    //read the rest of the lines in the file
    while (getline(file, line)) {
        if (line.empty()) {
            continue;
        }
    stringstream stream(line);  //read two endpoint vertex names and edge label
        string v1Name;
        string v2Name;
        string labelText;

        //read the two endpoint vertex names and the edge labels
        getline(stream, v1Name, '\t');
        getline(stream, v2Name, '\t');
        getline(stream, labelText, '\t');

        //find the vertex objects that match the name
        Vertex* v1 = findVertex(v1Name);
        Vertex* v2 = findVertex(v2Name);

        float edgeLabel = stof(labelText);
        //if both vertices exist create a edge between
        if (v1 != nullptr && v2 != nullptr) {
            insertEdge(v1, v2, edgeLabel);
        }
    }

    // //close the file
    // file.close();
}

//destructor to delete all dynamically allocated edges and vertices
Graph::~Graph() {
    //delete every edge in the graph
    for (Edge* e : allEdges) {
        delete e;
    }

    //delete every vertex stored in the graph
    for (Vertex* v : allVertices) {
        delete v;
    }
}

//searches for a vertex from the name
Vertex* Graph::findVertex(const string& name){
    for(Vertex* v : allVertices){
        if(**v == name){    //if vertex is found return pointer
            return v;
        }
    }
    return nullptr; //return null ptr if vertex not found
}

Vertex* Graph::getVertex(const string& name){   //sso main.cpp can access vertices
    return findVertex(name);
}

//finds edge between two vertices
Edge* Graph::findEdge(Vertex* v1, Vertex* v2) {
    for (Edge* e : allEdges) {
        vector<Vertex*> endpoints = e->endVertices();
        //if the edge is on both vertices then it connects them
        if (e->isIncidentOn(v1) && e->isIncidentOn(v2)) {
            return e;
        }
    }

    return nullptr; //return null ptr if not
}

//return all vertices in the graph
vector<Vertex*> Graph::vertices() {
    return allVertices;
}

//return all edges in the graph
vector<Edge*> Graph::edges() {
    return allEdges;
}



//insert a new vertex into the graph
Vertex* Graph::insertVertex(const string& x) {
    Vertex* existing = findVertex(x);
    if (existing != nullptr) {  //if vertex already exists return existing one
        return existing;
    }
    // otherwise create the new vertex and store in graph
    Vertex* newVertex = new Vertex(x);
    allVertices.push_back(newVertex);
    return newVertex;
}

//inserts a new edge between two existing vertices
Edge* Graph::insertEdge(Vertex* v, Vertex* w, float x) {
        //both vertices must exist before edge is created
    if (v == nullptr || w == nullptr) {
        return nullptr;
    }

    //dont let duplicate or parallel edges
    if (findEdge(v, w) != nullptr) {
        return nullptr;
    }
    //create the new edge and to graphs edge list
    Edge* newEdge = new Edge(v, w, x);
    allEdges.push_back(newEdge);

    // adding the edge to bothvertices
    v->addEdge(newEdge);
    w->addEdge(newEdge);

    return newEdge;
}

//function to remove an edge from teh graph
bool Graph::eraseEdge(Edge* e) {
    if (e == nullptr) { //if edge is null return false
        return false;
    }

    vector<Vertex*> endpoints = e->endVertices();   //get both vertices connected by edge

    // remove edge from both the vertices
    endpoints[0]->removeEdge(e);
    endpoints[1]->removeEdge(e);

    // remove the edge from the graph list
    for (auto it = allEdges.begin(); it != allEdges.end(); ++it) {
        if (*it == e) {
            allEdges.erase(it);
            delete e;
            return true;
        }
    }

    return false;
}

// remove a vertex and the edges connected to it
bool Graph::eraseVertex(Vertex* v) {
    if (v == nullptr) {
        return false;
    }

    // copy connected edges before deleting so eraseEdge can change the vertex edge list
    vector<Edge*> incident = v->incidentEdges();

    //remove the edges connected to the vertex
    for (Edge* e : incident) {
        eraseEdge(e);
    }

    // remove the vertex from the graphs vertex list
    for (auto it = allVertices.begin(); it != allVertices.end(); ++it) {
        if (*it == v) {
            allVertices.erase(it);
            delete v;
            return true;
        }
    }

    return false;
}

//prints all edges connected to a given vertex
void Graph::printIncidentEdges(const string& name){
    Vertex* v = findVertex(name);

    //check that the vertex is in the graph
    if (v == nullptr) {
        cout << "Error: vertex not in graph." << endl;
        return;
    }

    //get the edges connected to the vertex
    vector<Edge*> incident = v->incidentEdges();

    //if no edges print message
    if (incident.empty()) {
        cout << "No connected edges." << endl;
        return;
    }

    //print each connected edge in the right format
    for (Edge* e : incident) {
        Vertex* other = e->opposite(v);

        cout << **v << " to " << **other << " is " << *(*e) << " mi" << endl;
    }
}

//Finds and prints a path between two vertices using BFS
void Graph::findPath(const string& startName, const string& endName) {
    Vertex* start = findVertex(startName);
    Vertex* end = findVertex(endName);

    //check if both vertices exist
    if (start == nullptr || end == nullptr) {
        cout << "Error: One or both vertices not found." << endl;
        return;
    }

    queue<Vertex*> q;   //store vertices that have not been visited
    map<Vertex*, Vertex*> parent;   //tracks how each vertex was reached
    map<Vertex*, bool> visited; //tracks which vertices have been seen

    //BFS from the starting index
    q.push(start);
    visited[start] = true;
    parent[start] = nullptr;

    //BFS loop
    while (!q.empty()) {
        Vertex* current = q.front();
        q.pop();

        if (current == end) {   //stop searching once the end vertex is found
            break;
        }

        //visit neighboring vertex
        for (Edge* e : current->incidentEdges()) {
            Vertex* neighbor = e->opposite(current);

            //if neighnbor has not been visited add to queue
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                parent[neighbor] = current;
                q.push(neighbor);
            }
        }
    }

    //if end vertex not reached there is no path to it
    if (!visited[end]) {
        cout << "No path found." << endl;
        return;
    }

    vector<Vertex*> path;
    Vertex* current = end;

    while (current != nullptr) {
        path.push_back(current);
        current = parent[current];
    }

    //get path by going backwards from end to start
    reverse(path.begin(), path.end());

    //path must contain at least 3 vertices
    if (path.size() < 3) {
        cout << "No path with at least 3 vertices found." << endl;
        return;
    }

    //Print the path using vertex names
    for (int i = 0; i < path.size(); i++) {
        cout << **path[i];

        if (i != path.size() - 1) {
            cout << " to ";
        }
    }

    cout << endl;
}
