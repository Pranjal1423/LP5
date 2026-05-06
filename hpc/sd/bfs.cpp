#include <iostream>
#include <queue>
#include <vector>
#include <omp.h>
using namespace std;

int main() {
    int num_vertices, num_edges, source;

    // input: number of vertices, edges, starting node
    cin >> num_vertices >> num_edges >> source;

    vector<vector<int>> adj_list(num_vertices + 1);

    // take edges input
    for (int i = 0; i < num_edges; i++) {
        int u, v;
        cin >> u >> v;

        adj_list[u].push_back(v);
        adj_list[v].push_back(u);   // undirected graph
    }

    queue<int> q;                         // queue for BFS
    vector<bool> visited(num_vertices + 1, false);

    q.push(source);                      // start node
    visited[source] = true;

    // BFS traversal
    while (!q.empty()) {
        int curr_vertex = q.front();
        q.pop();

        cout << curr_vertex << " ";

        // parallel exploration of neighbours
        #pragma omp parallel for schedule(dynamic)
        for (int i = 0; i < adj_list[curr_vertex].size(); i++) {
            int neighbour = adj_list[curr_vertex][i];

            // if not visited, mark and push
            if (!visited[neighbour]) {
                visited[neighbour] = true;
                q.push(neighbour);
            }
        }
    }

    return 0;
}