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
            cout << "Enter vertex1 vertex2 edgeValue: ";
            cin >> vertex1 >> vertex2 >> edgeValue;

            Vertex* v = graph.getVertex(vertex1);
            Vertex* w = graph.getVertex(vertex2);

            graph.insertEdge(v, w, edgeValue);

            cout << "Edge inserted." << endl;
            break;
        }

        case 4: {
            cout << "Enter vertex to erase: ";
            cin >> vertex1;

            Vertex* v = graph.getVertex(vertex1);

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