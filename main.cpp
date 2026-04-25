#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include "vertex.h"
#include "edge.h"
#include "graph.h"
using namespace std;


void incidentEdges(Vertex* vertex){
    for(auto edge : vertex->incidentEdges()){
        cout<<vertex->operator*()<<" to "<<edge->opposite(vertex)->operator*()<<" is "<<edge->operator*()<<endl;
    }
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
    string vertex1, vertex2;
    float edgeValue;
    int convertedInput;
    



    // Graph creation portion of the program
    cout<<"Hello!"<<endl;
    cout<<"Enter the file name: "<<endl;
    // REMOVE THIS COMMENT cin>>filename;
    filename = "inputfile-1.txt";
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
            cout<<"Enter the vertex you want to find incident edges for: "<<endl;
            cin>>input;
                if (findVertex(input, graph.allVertices) == nullptr){
                    cout<<"Vertex not found. Please try again."<<endl;
                    continue;
                }
            incidentEdges(findVertex(input, graph.allVertices));
            break;
        case 2:
            cout<<"Enter the starting vertex and ending vertex for the path you want to find: "<<endl;
            cin>>vertex1>>vertex2;
            if (findVertex(vertex1, graph.allVertices) == nullptr || findVertex(vertex2, graph.allVertices) == nullptr){
                cout<<"One or both vertices not found. Please try again."<<endl;
                continue;
            }
            cout<<"Path found from "<<vertex1<<" to "<<vertex2<<": "<<endl;
            findPath(findVertex(vertex1, graph.allVertices), findVertex(vertex2, graph.allVertices));
            break;
        case 3:
            cout<<"Enter the vertices you want to connect with an edge and give the edge value: "<<endl;
            
            cin>>vertex1>>vertex2>>edgeValue;
            if (findVertex(vertex1, graph.allVertices) == nullptr || findVertex(vertex2, graph.allVertices) == nullptr){
                cout<<"One or both vertices not found. Please try again."<<endl;
                continue;
            }
            insertEdge(findVertex(vertex1, graph.allVertices), findVertex(vertex2, graph.allVertices));
            cout<<"Edge inserted."<<endl;
            break;
        case 4:
            cout<<"Enter the vertex you want to erase: "<<endl;
            cin>>input;
            if (findVertex(input, graph.allVertices) == nullptr){
                cout<<"Vertex not found. Please try again."<<endl;
                continue;
            }
            eraseVertex(findVertex(input, graph.allVertices));
            cout<<"Vertex removed."<<endl;
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