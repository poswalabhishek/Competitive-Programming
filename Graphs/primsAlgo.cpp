/*
Given an undirected, connected and weighted graph G(V, E) with V number of vertices (which are numbered from 0 to V-1) and E number of edges.
Find and print the Minimum Spanning Tree (MST) using Prim's algorithm.
For printing MST follow the steps -
1. In one line, print an edge which is part of MST in the format - 
v1 v2 w
where, v1 and v2 are the vertices of the edge which is included in MST and whose weight is w. And v1  <= v2 i.e. print the smaller vertex first while printing an edge.
2. Print V-1 edges in above format in different lines.
Note : Order of different edges doesn't matter.
Input Format :
Line 1: Two Integers V and E (separated by space)
Next E lines : Three integers ei, ej and wi, denoting that there exists an edge between vertex ei and vertex ej with weight wi (separated by space)
Output Format :
Print the MST, as described in the task.
Constraints :
2 <= V, E <= 10^5
Time Limit: 1 sec
Sample Input 1 :
4 4
0 1 3
0 3 5
1 2 1
2 3 8
Sample Output 1 :
0 1 3
1 2 1
0 3 5
*/

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