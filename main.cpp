#include <iostream>
#include <string>
#include "graph.h"

using namespace std;

int main() {
    bool running = true;
    string filename;
    string input;
    string vertex1, vertex2;
    float edgeValue;
    int convertedInput;

    cout << "Hello!" << endl;
    cout << "Enter the file name: " << endl;

    filename = "inputfile-1.txt"; 
    Graph graph(filename); // Initialize graph from file

    cout << "\nThank you. Your graph is ready." << endl;

    while (running) {
        cout << "------------------------------------" << endl;
        cout << "What would you like to do?" << endl;
        cout << "-------------------------------------" << endl;
        cout << "1. Find edges incident on a vertex" << endl;
        cout << "2. Find a path in the graph" << endl;
        cout << "3. Insert an edge" << endl;
        cout << "4. Erase a vertex" << endl;
        cout << "5. Exit" << endl;

        cin >> input;

        // Validate menu selection is an integer
        try {
            convertedInput = stoi(input);
        } catch (exception& e) {
            cout << "Invalid input. Please try again." << endl;
            continue;
        }

        switch (convertedInput) {

        case 1: {
            cout << "Enter vertex: ";
            cin >> vertex1;
            graph.printIncidentEdges(vertex1); // Show all edges connected to vertex
            break;
        }

        case 2: {
            cout << "Enter start and end vertex: ";
            cin >> vertex1 >> vertex2;
            graph.findPath(vertex1, vertex2); // BFS search for path between two nodes
            break;
        }

        case 3: {
            cout << "Enter vertex1 vertex2 and edge value: ";
            // Ensure float input is valid to prevent cin stream errors
            if (!(cin >> vertex1 >> vertex2 >> edgeValue)) {
                cout << "Invalid input format. Please enter: string string float" << endl;
                cin.clear(); 
                cin.ignore(1000, '\n');
                break;
            }

            Vertex* v = graph.getVertex(vertex1);
            Vertex* w = graph.getVertex(vertex2);

            if (v == nullptr || w == nullptr) {
                cout << "Error: One or both vertices not found." << endl;
                break;
            }

            // Verify if edge was successfully created or already existed
            Edge* newEdge = graph.insertEdge(v, w, edgeValue);

            if (newEdge != nullptr) {
                cout << "Edge inserted successfully." << endl;
            } else {
                cout << "Edge insertion failed: Connection already exists." << endl;
            }
            break;
        }

        case 4: {
            cout << "Enter vertex to erase: ";
            cin >> vertex1;

            Vertex* v = graph.getVertex(vertex1);

            if (v == nullptr) {
                cout << "Vertex not found." << endl;
                break;
            }

            graph.eraseVertex(v); // Deletes vertex and all associated incident edges
            cout << "Vertex removed." << endl;
            break;
        }

        case 5:
            running = false;
            break;

        default:
            cout << "Invalid input. Try again." << endl;
            break;
        }
    }

    return 0;
}