#include <iostream>
#include <vector>
#include <omp.h>
using namespace std;

const int MAXN = 1e5;

vector<int> adj[MAXN + 5];   // adjacency list to store graph
bool visited[MAXN + 5];      // array to mark visited nodes

// DFS function
void dfs(int node) {
    visited[node] = true;    // mark current node as visited

    // explore all adjacent nodes in parallel
    #pragma omp parallel for
    for (int i = 0; i < adj[node].size(); i++) {
        int next_node = adj[node][i];

        // if not visited, go deeper
        if (!visited[next_node]) {
            dfs(next_node);
        }
    }
}

int main() {
    cout << "Please enter nodes and edges: ";

    int n, m;   // n = number of nodes, m = number of edges
    cin >> n >> m;

    // taking edges input
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;

        adj[u].push_back(v);
        adj[v].push_back(u);   // undirected graph
    }

    int start_node;   // starting node for DFS
    cin >> start_node;

    dfs(start_node);

    // print visited nodes
    cout << "Visited nodes: ";
    for (int i = 1; i <= n; i++) {
        if (visited[i]) {
            cout << i << " ";
        }
    }

    cout << endl;
    return 0;
}