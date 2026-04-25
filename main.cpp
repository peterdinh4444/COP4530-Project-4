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

    filename = "inputfile-1.txt"; // for testing
    Graph graph(filename);

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

            graph.printIncidentEdges(vertex1);
            break;
        }

        case 2: {
            cout << "Enter start and end vertex: ";
            cin >> vertex1 >> vertex2;

            graph.findPath(vertex1, vertex2);
            break;
        }

        case 3: {
            cout << "Enter vertex1 vertex2 and edge value: ";
            if (!(cin >> vertex1 >> vertex2 >> edgeValue)) {
                cout << "Invalid input format. Please enter: string string float" << endl;
                cin.clear(); 
                cin.ignore(1000, '\n');
                break;
            }

            Vertex* v = graph.getVertex(vertex1);
            Vertex* w = graph.getVertex(vertex2);

            if (v == nullptr || w == nullptr) {
                cout << "Error: One or both vertices (" << vertex1 << ", " << vertex2 << ") not found." << endl;
                break;
            }

            // Capture the return pointer to verify success
            Edge* newEdge = graph.insertEdge(v, w, edgeValue);

            if (newEdge != nullptr) {
                cout << "Edge inserted successfully between " << vertex1 << " and " << vertex2 << "." << endl;
            } else {
                // This handles the logic in Graph::insertEdge where it returns nullptr for duplicates
                cout << "Edge insertion failed: A connection already exists between these vertices." << endl;
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

            graph.eraseVertex(v);

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