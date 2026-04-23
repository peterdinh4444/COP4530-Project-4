#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include "vertex.h"
#include "edge.h"
#include "graph.h"
using namespace std;



//  Node class definition
class Node {
public: 
    Edge* edgePtr;
    Node* next;

    Node(Edge* e) {
        edgePtr = e;
        next = nullptr;
    }
};

// Vertex class definition
class Vertex{
public:
    string name;
    Node* adjacencyList;

    Vertex(string n){
        name = n;
        adjacencyList = nullptr;
    }
};

// Edge class definition
class Edge{
public:
    Vertex* v1;
    Vertex* v2;
    int edgeLabel;

    Edge(Vertex* vertex1, Vertex* vertex2, int label){
        v1 = vertex1;
        v2 = vertex2;
        edgeLabel = label;
    }
};

// Graph Class definition
class Graph{
    public: 
    int numVertices;
    int numEdges;
    vector<Vertex*> allVertices;


    Graph(string file){
        numVertices = 0;
        numEdges = 0;
        ifstream file(filename);
        string line;

        if (!file.is_open())
            return nullptr; // Return if file didn't open


        if (getline(file, line)){
            stringstream stream(line);
            if(getline(stream, line, "\t"))
        }
    }






};

void incidentEdges(Node* vertex){

};

void findPath(Node* start, Node* end){

};

void insertEdge(Node* vertex1, Node* vertex2){

};

void eraseVertex(Node* vertex){

};


int main(){
    // Declares and Initializes Variables and Graph
    bool running = true;
    string input;
    int convertedInput;
    Graph graph("inputfile-1.txt");

    // Running portion of the program
    while(running){
        cout<<"------------------------------------"<<endl;
        cout<<"What would you like to do?"<<endl;
        cout<<"-------------------------------------"<<endl;
        cout<<"1. Find edges incident on a vertex"<<endl;
        cout<<"2. Find a path in the graph"<<endl;
        cout<<"3. Insert an edge"<<endl;
        cout<<"4. Erase a vertex"<<endl;
        cout<<"5. Exit"<<endl;
        cin>>input;

        // Tries to convert input to an integer
        try{
            convertedInput = stoi(input);
        }
        catch(exception& e){
            cout<<"Invalid input. Please try again."<<endl;
            continue;
        }

        // Switch statement to handle user input
        switch (convertedInput)
        {
        case 1:
            /* code */
            break;
        case 2:
            /* code */
            break;
        case 3:
            /* code */
            break;
        case 4:
            /* code */
            break;
        case 5:
            running = false;
            break;
        default:
            cout<<"Invalid input. Please try again."<<endl;
            break;
        }   
    }


    return 0;
}