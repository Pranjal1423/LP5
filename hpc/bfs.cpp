// : Design and implement Parallel Breadth First Search based on existing algorithms using 
//OpenMP. Use a Tree or an undirected graph for BFS 

// sudo apt update
// sudo apt install g++

// g++ -fopenmp bfs.cpp -o bfs
// ./bfs
//bfs
#include <iostream>
#include <vector>
#include <omp.h>
using namespace std;

int main() {
    int n, m, source;

    cout << "Enter number of vertices, edges, and source: ";
    cin >> n >> m >> source;

    // Adjacency list
    vector<vector<int>> adj(n + 1);

    cout << "Enter edges (u v):\n";
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u); // undirected graph
    }

    // IMPORTANT: use int instead of bool for atomic operations
    vector<int> visited(n + 1, 0);

    vector<int> current_level;
    vector<int> next_level;

    // Start BFS
    current_level.push_back(source);
    visited[source] = 1;

    cout << "BFS Traversal: ";

    while (!current_level.empty()) {

        // Print current level
        for (int node : current_level) {
            cout << node << " ";
        }

        next_level.clear();

        #pragma omp parallel
        {
            vector<int> local_next; // thread-local vector

            #pragma omp for nowait
            for (int i = 0; i < current_level.size(); i++) {
                int node = current_level[i];

                for (int j = 0; j < adj[node].size(); j++) {
                    int neighbour = adj[node][j];

                    int alreadyVisited;

                    // Atomic check + update
                    #pragma omp atomic capture
                    {
                        alreadyVisited = visited[neighbour];
                        visited[neighbour]=1;

                    }

                    if (!alreadyVisited) {
                        local_next.push_back(neighbour);
                    }
                }
            }

            // Merge safely into next_level
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

// Enter number of vertices, edges, and source: 4 4 1
// Enter edges (u v):
// 1 2
// 1 3
// 2 4
// 3 4
// BFS Traversal: 1 2 3 4
