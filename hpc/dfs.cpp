// : Design and implement Parallel Breadth First Search based on existing algorithms using 
//OpenMP. Use a Tree or an undirected graph for BFS 

// sudo apt update
// sudo apt install g++

// g++ -fopenmp dfs.cpp -o dfs
// ./dfs
//dfs
#include <iostream>
#include <vector>
#include <omp.h>
using namespace std;

const int MAXN = 100000;
vector<int> adj[MAXN];
bool visited[MAXN];

void dfs(int node) {
    // Atomically check and mark visited
    bool alreadyVisited;

    #pragma omp atomic capture
    {
        alreadyVisited = visited[node];
        visited[node] = true;
    }

    if (alreadyVisited) return;

    // Critical only for printing (avoid mixed output)
    #pragma omp critical
    cout << node << " ";

    for (int i = 0; i < adj[node].size(); i++) {
        int next = adj[node][i];

        // Create task only if not visited (reduce overhead)
        if (!visited[next]) {
            #pragma omp task
            dfs(next);
        }
    }

    // Wait for all child tasks
    #pragma omp taskwait
}

int main() {
    int n, m;
    cout << "Enter nodes and edges: ";
    cin >> n >> m;

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int start;
    cout << "Enter start node: ";
    cin >> start;

    // Initialize visited array
    for (int i = 0; i <= n; i++)
        visited[i] = false;

    #pragma omp parallel
    {
        #pragma omp single
        {
            dfs(start);
        }
    }

    cout << endl;
    return 0;
}
// pranjal@DESKTOP-9S159J6:/mnt/d/deep learnin/hpc$ ./dfs
// Enter nodes and edges: 5 4
// 1 2
// 1 3
// 2 4
// 3 5
// Enter start node: 1
// 1 2 3 4 5