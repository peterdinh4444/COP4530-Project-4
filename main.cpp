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
    float edgeLabel;

    Edge(Vertex* vertex1, Vertex* vertex2, float label){
        v1 = vertex1;
        v2 = vertex2;
        edgeLabel = label;
    }
};

// Helper function for Vertex Vector
Vertex* findVertex(string name, const vector<Vertex*>& allVertices){
    for (auto vertex : allVertices){
        if (vertex->name == name){
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
            Node* newNode1 = new Node(newEdge);
            Node* newNode2 = new Node(newEdge);
            newNode1->next = v1->adjacencyList;
            v1->adjacencyList = newNode1;
            newNode2->next = v2->adjacencyList;
            v2->adjacencyList = newNode2;
        }
    }
};

void incidentEdges(Vertex* vertex){

};

void findPath(Vertex* start, Vertex* end){

};

void insertEdge(Vertex* vertex1, Vertex* vertex2){

};

void eraseVertex(Vertex* vertex){

};


int main(){
    // Declares and Initializes Variables
    bool running = true;
    string filename;
    string input;
    int convertedInput;
    



    // Graph creation portion of the program
    cout<<"Hello!"<<endl;
    cout<<"Enter the file name: "<<endl;
    cin>>filename;
    Graph graph(filename);
    cout<<endl<<"\n"<<"Thank you. Your graph is ready."<<endl;





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