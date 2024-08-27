#include <iostream>
#include <vector>
#include <climits>  // For INT_MAX

using namespace std;

void BellmanFord(int vertices, int source, vector<vector<int>>& adjMatrix) {
    vector<int> Label(vertices, INT_MAX);  // Distance from the source to each vertex
    vector<int> Prev(vertices, -1);        // Previous vertex in the path

    Label[source] = 0; // Distance from the source to itself is 0

    for (int i = 0; i < vertices - 1; ++i) {
        for (int u = 0; u < vertices; ++u) {
            for (int v = 0; v < vertices; ++v) {
                if (adjMatrix[u][v] != INT_MAX && Label[u] != INT_MAX && Label[u] + adjMatrix[u][v] < Label[v]) {
                    Label[v] = Label[u] + adjMatrix[u][v];
                    Prev[v] = u;
                }
            }
        }
    }

    // Check for negative weight cycles
    for (int u = 0; u < vertices; ++u) {
        for (int v = 0; v < vertices; ++v) {
            if (adjMatrix[u][v] != INT_MAX && Label[u] != INT_MAX && Label[u] + adjMatrix[u][v] < Label[v]) {
                cout << "Error: Graph contains a negative weight cycle!" << endl;
                return;
            }
        }
    }

    // Output the results
    cout << "Distance from the source vertex:" << endl;
    for (int i = 0; i < vertices; ++i) {
        cout << "Vertex " << i << ": " << Label[i] << " (Prev: " << (Prev[i] != -1 ? Prev[i] : -1) << ")" << endl;
    }
}

int main() {
    int vertices = 6; // Number of vertices
    int source = 0;   // Source vertex '0'

    // Initialize the adjacency matrix based on the graph
    vector<vector<int>> adjMatrix = {
        {0, 5, INT_MAX, 1, INT_MAX, 4},   // 0 -> other vertices
        {INT_MAX, 0, -5, INT_MAX, 1, INT_MAX}, // 1 -> other vertices
        {INT_MAX, INT_MAX, 0, 1, INT_MAX, 1}, // 2 -> other vertices
        {INT_MAX, INT_MAX, INT_MAX, 0, 3, INT_MAX}, // 3 -> other vertices
        {INT_MAX, INT_MAX, INT_MAX, INT_MAX, 0, INT_MAX}, // 4 -> other vertices
        {INT_MAX, 1, INT_MAX, INT_MAX, INT_MAX, 0}  // 5 -> other vertices
    };

    BellmanFord(vertices, source, adjMatrix);

    return 0;
}
