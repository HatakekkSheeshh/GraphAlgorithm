#include <iostream>
#include <vector>
#include <cfloat>  // For DBL_MAX

using namespace std;

struct Edge {
    int u, v; // u -> v
    double weight;
};

void Dijkstra(int vertices, int source, vector<Edge>& edges) {
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
        for (auto edge : edges) {
            if (edge.u == u && !S[edge.v] && Label[u] + edge.weight < Label[edge.v]) {
                Label[edge.v] = Label[u] + edge.weight;
                Prev[edge.v] = u;
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

    vector<Edge> edges = {
        {0, 2, 0.26},   // 0 -> 2
        {0, 4, 0.38},   // 0 -> 4
        {0, 6, 0.58},   // 0 -> 6
        {0, 7, 0.16},   // 0 -> 7
        {1, 2, 0.36},   // 1 -> 2
        {1, 3, 0.29},   // 1 -> 3
        {1, 5, 0.32},   // 1 -> 5
        {1, 7, 0.19},   // 1 -> 7
        {2, 0, 0.26},   // 2 -> 0
        {2, 1, 0.36},   // 2 -> 1
        {2, 3, 0.17},   // 2 -> 3
        {2, 7, 0.34},   // 2 -> 7
        {3, 1, 0.29},   // 3 -> 1
        {3, 2, 0.17},   // 3 -> 2
        {3, 7, 0.36},   // 3 -> 7
        {4, 0, 0.38},   // 4 -> 0
        {4, 5, 0.35},   // 4 -> 5
        {4, 6, 0.93},   // 4 -> 6
        {4, 7, 0.37},   // 4 -> 7
        {5, 1, 0.32},   // 5 -> 1
        {5, 4, 0.35},   // 5 -> 4
        {5, 7, 0.28},   // 5 -> 7
        {6, 0, 0.58},   // 6 -> 0
        {6, 4, 0.93},   // 6 -> 4
        {7, 0, 0.16},   // 7 -> 0
        {7, 1, 0.19},   // 7 -> 1
        {7, 2, 0.34},   // 7 -> 2
        {7, 3, 0.36},   // 7 -> 3
        {7, 4, 0.37},   // 7 -> 4
        {7, 5, 0.28}    // 7 -> 5
    };

    Dijkstra(vertices, source, edges);

    return 0;
}
