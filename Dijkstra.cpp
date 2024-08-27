#include <iostream>
#include <vector>
#include <cfloat>  // For DBL_MAX
#include <limits>  // For numeric_limits

using namespace std;

void Dijkstra(int vertices, int source, vector<vector<double>>& adjMatrix) {
    vector<double> Label(vertices, DBL_MAX);  // Distance from the source to each vertex
    vector<int> Prev(vertices, -1);           // Previous vertex in the path
    vector<bool> S(vertices, false);          // Set of vertices for which the shortest path is found

    Label[source] = 0; // Distance from the source to itself is 0

    for (int i = 0; i < vertices - 1; ++i) {
        // Find the vertex u that is not in S and has the minimum label
        int u = -1;
        double minLabel = DBL_MAX;

        for (int j = 0; j < vertices; ++j) {
            if (!S[j] && Label[j] < minLabel) {
                minLabel = Label[j];
                u = j;
            }
        }

        // If u is not found, break (this indicates that all reachable vertices have been processed)
        if (u == -1) break;

        // Mark u as part of the set S
        S[u] = true;

        // Update labels for all vertices v not in S
        for (int v = 0; v < vertices; ++v) {
            if (!S[v] && adjMatrix[u][v] != DBL_MAX && Label[u] + adjMatrix[u][v] < Label[v]) {
                Label[v] = Label[u] + adjMatrix[u][v];
                Prev[v] = u;
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
    int vertices = 8; // Number of vertices
    int source = 1;   // Source vertex '1'

    // Initialize the adjacency matrix based on the graph
    vector<vector<double>> adjMatrix = {
        {DBL_MAX, DBL_MAX, 0.26, DBL_MAX, 0.38, DBL_MAX, 0.58, 0.16}, // 0 -> other vertices
        {DBL_MAX, DBL_MAX, 0.36, 0.29, DBL_MAX, 0.32, DBL_MAX, 0.19}, // 1 -> other vertices
        {0.26, 0.36, DBL_MAX, 0.17, DBL_MAX, DBL_MAX, DBL_MAX, 0.34}, // 2 -> other vertices
        {DBL_MAX, 0.29, 0.17, DBL_MAX, DBL_MAX, DBL_MAX, DBL_MAX, 0.36}, // 3 -> other vertices
        {0.38, DBL_MAX, DBL_MAX, DBL_MAX, DBL_MAX, 0.35, 0.93, 0.37}, // 4 -> other vertices
        {DBL_MAX, 0.32, DBL_MAX, DBL_MAX, 0.35, DBL_MAX, DBL_MAX, 0.28}, // 5 -> other vertices (NO path to 6)
        {0.58, DBL_MAX, DBL_MAX, DBL_MAX, 0.93, DBL_MAX, DBL_MAX, DBL_MAX}, // 6 -> other vertices
        {0.16, 0.19, 0.34, 0.36, 0.37, 0.28, DBL_MAX, DBL_MAX} // 7 -> other vertices
    };

    Dijkstra(vertices, source, adjMatrix);

    return 0;
}

