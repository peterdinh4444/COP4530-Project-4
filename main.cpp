#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include "vertex.h"
#include "edge.h"
#include "graph.h"
using namespace std;


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