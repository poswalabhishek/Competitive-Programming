#include <bits/stdc++.h>
using namespace std;

int getMinVertex (bool *visited, int* weight, int n) {

    int minVertex = -1;
    for (int i = 0; i < n; ++i) {
        if (!visited[i] && ((minVertex == -1) || (weight[minVertex] > weight[i])))
            minVertex = i;
    }
    return minVertex;
}

void prims (int edges[1000][1000], int n) {
    bool visited[n];
    int parent[n];
    int weight[n];

    for (int i = 0; i < n; ++i) 
        weight[i] = INT_MAX;

    parent[0] = -1;
    weight[0] = 0;
    for (int i = 0; i < n - 1; ++i) {
        // get minVertex i.e. unvisited vertex with minimum weight
        int minVertex = getMinVertex (visited, weight, n);
        visited[minVertex] = true;

        // explore all the neighbors of minVertex and update parent and weight array accordingly
        for (int j = 0; j < n; ++j) {
            if (edges[minVertex][j] != 0 && !visited[j]) {
                if (weight[j] > edges[minVertex][j]) {
                    weight[j] = edges[minVertex][j];
                    parent[j] = minVertex;
                }
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        if (parent[i] < i) 
            cout << parent[i] << " " << i << " " << weight << endl;
        else
            cout << i << " " << parent[i] << " " << weight << endl;
    }
}

int main() {
    int v, e;
    cin >> v >> e;
    
    int edges[1000][1000];
    memset (edges, 0, sizeof(edges));

    int a, b, weight;
    for (int i = 0; i < e; ++i) {
        cin >> a >> b >> weight;
        edges[a][b] = weight;
        edges[b][a] = weight; 
    }

    cout << endl;
    prims (edges, v);


    return 0;
}