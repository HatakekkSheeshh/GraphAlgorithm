#include <iostream>
#include <vector>
#include <cfloat>  // For DBL_MAX
#include <chrono>  // For measuring time
#include <iomanip> // For fixed and setprecision

using namespace std;
using namespace chrono;

void FloydWarshall(int vertices, vector<vector<double>>& adjMatrix) {
    vector<vector<double>> dist(vertices, vector<double>(vertices, DBL_MAX));
    vector<vector<int>> next(vertices, vector<int>(vertices, -1));

    // Initialize the distance matrix and the next matrix
    for (int i = 0; i < vertices; ++i) {
        for (int j = 0; j < vertices; ++j) {
            if (i == j) {
                dist[i][j] = 0;
            } else if (adjMatrix[i][j] != DBL_MAX) {
                dist[i][j] = adjMatrix[i][j];
                next[i][j] = j;
            }
        }
    }

    // Perform Floyd-Warshall algorithm
    for (int k = 0; k < vertices; ++k) {
        for (int i = 0; i < vertices; ++i) {
            for (int j = 0; j < vertices; ++j) {
                if (dist[i][k] < DBL_MAX && dist[k][j] < DBL_MAX && dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    next[i][j] = next[i][k];
                }
            }
        }
    }

    // Output the results specifically from vertex A
    int startVertex = 0;  // Start from vertex A
    cout << "\nPath and total cost from vertex A:" << endl;
    for (int j = 0; j < vertices; ++j) {
        if (startVertex != j) {
            cout << "Path from A to " << char('A' + j) << ": ";
            if (dist[startVertex][j] == DBL_MAX) {
                cout << "No path" << endl;
            } else {
                int pathVertex = startVertex;
                cout << char('A' + pathVertex);
                while (pathVertex != j) {
                    pathVertex = next[pathVertex][j];
                    cout << " -> " << char('A' + pathVertex);
                }
                cout << " (Cost: " << dist[startVertex][j] << ")" << endl;
            }
        }
    }
}

int main() {
    int vertices = 8; // Number of vertices

    // Initialize the adjacency matrix based on the graph
    vector<vector<double>> adjMatrix = {
        {0, 4, DBL_MAX, DBL_MAX, DBL_MAX, 1, DBL_MAX, DBL_MAX}, // A -> other vertices
        {4, 0, 2, 5, DBL_MAX, DBL_MAX, DBL_MAX, DBL_MAX},       // B -> other vertices
        {DBL_MAX, 2, 0, 4, DBL_MAX, DBL_MAX, DBL_MAX, 5},       // C -> other vertices
        {DBL_MAX, 5, 4, 0, 4, DBL_MAX, DBL_MAX, DBL_MAX},       // D -> other vertices
        {DBL_MAX, DBL_MAX, DBL_MAX, 4, 0, 3, 1, 2},             // E -> other vertices
        {1, DBL_MAX, DBL_MAX, DBL_MAX, 3, 0, 2, DBL_MAX},       // F -> other vertices
        {DBL_MAX, DBL_MAX, DBL_MAX, DBL_MAX, 1, 2, 0, 4},       // G -> other vertices
        {DBL_MAX, DBL_MAX, 5, DBL_MAX, 2, DBL_MAX, 4, 0}        // H -> other vertices
    };

    // Measure the execution time of the Floyd-Warshall algorithm over multiple iterations
    auto start = high_resolution_clock::now();

    for (int i = 0; i < 1000; ++i) {
        FloydWarshall(vertices, adjMatrix);
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<nanoseconds>(stop - start);

    // Output the time taken
    cout << "\nAverage time taken by Floyd-Warshall algorithm over 1000 iterations: "
         << fixed << setprecision(4) << duration.count() / 1000.0 << " nanoseconds per iteration" << endl;

    return 0;
}
