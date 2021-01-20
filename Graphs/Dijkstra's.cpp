#include <bits/stdc++.h>
using namespace std;

int getMinVertex (bool *visited, int* weight, int n) {

    int minVertex = -1;
    for (int i = 0; i < n; ++i) 
        if (!visited[i] && ((minVertex == -1) || (weight[minVertex] > weight[i])))
            minVertex = i;
        
    return minVertex;
}

void prims (int **edges, int n) {
    bool *visited = new bool[n];
    int *weight = new int[n];
    int *parent = new int[n];

    for (int i = 0; i < n; ++i) 
        weight[i] = INT_MAX;

    parent[0] = -1;
    weight[0] = 0;
    for (int i = 0; i < n; ++i) {
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

    for (int i = 1; i < n; ++i) {
        if (parent[i] < i) 
            cout << parent[i] << " " << i << " " << weight[i] << endl;
        else
            cout << i << " " << parent[i] << " " << weight[i] << endl;
    }
    delete [] visited;
    delete [] weight;
    delete [] parent;
}


int main() {
    int n, e;
    cin >> n >> e;
    
    int **edges = new int*[n];
    
    for (int i = 0; i < n; ++i) {
        edges[i] = new int[n];
        for (int j = 0; j < n; ++j) 
            edges[i][j] = 0;
    }
    
    int a, b, weight;
    for (int i = 0; i < e; ++i) {
        cin >> a >> b >> weight;
        edges[a][b] = weight;
        edges[b][a] = weight;
    }

    prims (edges, n);
    
    for (int i = 0; i < n; ++i)
        delete [] edges[i];
    delete [] edges;
}