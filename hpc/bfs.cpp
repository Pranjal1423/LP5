// : Design and implement Parallel Breadth First Search based on existing algorithms using 
//OpenMP. Use a Tree or an undirected graph for BFS 

// sudo apt update
// sudo apt install g++

// Parallel BFS using OpenMP
// Compile:
// g++ -fopenmp bfs.cpp -o bfs
// Run:
// ./bfs

#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;

int main() {

    int n, m, source;

    cout << "Enter number of vertices, edges, and source: ";
    cin >> n >> m >> source;

    // Adjacency List
    vector<vector<int>> adj(n + 1);

    cout << "Enter edges (u v):\n";

    for (int i = 0; i < m; i++) {

        int u, v;
        cin >> u >> v;

        adj[u].push_back(v);
        adj[v].push_back(u); // Undirected graph
    }

    // Visited array
    vector<int> visited(n + 1, 0);

    // BFS Levels
    vector<int> current_level;
    vector<int> next_level;

    // Start from source
    current_level.push_back(source);
    visited[source] = 1;

    // Thread Information
    cout << "\nMaximum Threads Available: "
         << omp_get_max_threads() << endl;

    #pragma omp parallel
    {
        #pragma omp single
        {
            cout << "Threads Being Used: "
                 << omp_get_num_threads() << endl;
        }
    }

    cout << "\nBFS Traversal: ";

    // BFS Loop
    while (!current_level.empty()) {

        // Print current level nodes
        for (int node : current_level)
            cout << node << " ";

        next_level.clear();

        #pragma omp parallel
        {

            // Local vector for each thread
            vector<int> local_next;

            #pragma omp for nowait
            for (int i = 0; i < current_level.size(); i++) {

                int node = current_level[i];

                // Traverse neighbours
                for (int j = 0; j < adj[node].size(); j++) {

                    int neighbour = adj[node][j];

                    int alreadyVisited;

                    // Atomic check and update
                    #pragma omp atomic capture
                    {
                        alreadyVisited = visited[neighbour];
                        visited[neighbour] = 1;
                    }

                    // If not visited before
                    if (!alreadyVisited) {
                        local_next.push_back(neighbour);
                    }
                }
            }

            // Merge thread-local vectors safely
            #pragma omp critical
            {
                next_level.insert(next_level.end(),
                                  local_next.begin(),
                                  local_next.end());
            }
        }

        // Move to next level
        current_level = next_level;
    }

    cout << endl;

    return 0;
}