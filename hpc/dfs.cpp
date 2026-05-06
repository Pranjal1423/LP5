// : Design and implement Parallel Breadth First Search based on existing algorithms using 
//OpenMP. Use a Tree or an undirected graph for BFS 

// sudo apt update
// sudo apt install g++
// Parallel DFS using OpenMP
// Compile:
// g++ -fopenmp dfs.cpp -o dfs
// Run:
// ./dfs

#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;

const int MAXN = 100000;

// Graph
vector<int> adj[MAXN];

// Visited array
int visited[MAXN];

// DFS Function
void dfs(int node) {

    int alreadyVisited;

    // Atomic check and update
    #pragma omp atomic capture
    {
        alreadyVisited = visited[node];
        visited[node] = 1;
    }

    // If already visited
    if (alreadyVisited)
        return;

    // Critical section for printing
    #pragma omp critical
    {
        cout << node << " ";
    }

    // Traverse neighbours
    for (int i = 0; i < adj[node].size(); i++) {

        int next = adj[node][i];

        // Create parallel task
        #pragma omp task
        dfs(next);
    }

    // Wait for child tasks
    #pragma omp taskwait
}

int main() {

    int n, m;

    cout << "Enter nodes and edges: ";
    cin >> n >> m;

    cout << "Enter edges:\n";

    // Input graph
    for (int i = 0; i < m; i++) {

        int u, v;
        cin >> u >> v;

        adj[u].push_back(v);
        adj[v].push_back(u); // Undirected graph
    }

    int start;

    cout << "Enter start node: ";
    cin >> start;

    // Initialize visited array
    for (int i = 0; i <= n; i++)
        visited[i] = 0;

    // Thread Information
    cout << "\nMaximum Threads Available: "
         << omp_get_max_threads() << endl;

    #pragma omp parallel
    {
        #pragma omp single
        {
            cout << "Threads Being Used: "
                 << omp_get_num_threads() << endl;

            cout << "\nDFS Traversal: ";

            dfs(start);
        }
    }

    cout << endl;

    return 0;
}