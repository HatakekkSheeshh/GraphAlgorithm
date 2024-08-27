#include <iostream>
#include <vector>
#include <climits>

using namespace std;

struct Edge {
    int u, v; // u -> v
    int weight;
};

void BellmanFord(int vertices, int source, vector<Edge>& edges) {
    vector<int> Label(vertices, INT_MAX); // Distance from the source to each vertex
    vector<int> Prev(vertices, -1); // Previous vertex in the path

    Label[source] = 0; // Distance from the source to itself is 0

    // Iteration step to update vertices
    for (int i = 1; i <= vertices - 1; ++i) {
        for (auto edge : edges) {
            int u = edge.u;
            int v = edge.v;
            int weight = edge.weight;
            if (Label[u] != INT_MAX && Label[u] + weight < Label[v]) {
                Label[v] = Label[u] + weight;
                Prev[v] = u;
            }
        }
    }

    // Check for negative weight cycles
    for (auto edge : edges) {
        int u = edge.u;
        int v = edge.v;
        int weight = edge.weight;
        if (Label[u] != INT_MAX && Label[u] + weight < Label[v]) {
            cout << "Error: Graph contains a negative weight cycle!" << endl;
            return;
        }
    }

    // Output the results
    cout << "Distance from the source vertex:" << endl;
    for (int i = 0; i < vertices; ++i) {
        cout << "Vertex " << char(i + 'a') << ": " << Label[i] << " (Prev: " << (Prev[i] != -1 ? char(Prev[i] + 'a') : '-') << ")" << endl;
    }
}

int main() {
    int vertices = 6; // Number of vertices
    int source = 0;   // Source vertex 'a'

    vector<Edge> edges = {
        {0, 1, 5},   // a -> b
        {0, 5, 4},   // a -> f
        {0, 3, 1},   // a -> d
        {1, 2, -5},  // b -> c
        {1, 4, 1},   // b -> e
        {2, 3, 1},   // c -> d
        {3, 4, 3},   // d -> e
        {5, 1, 1},   // f -> b
        {2, 5, 1}    // c -> f
    };

    BellmanFord(vertices, source, edges);

    return 0;
}

