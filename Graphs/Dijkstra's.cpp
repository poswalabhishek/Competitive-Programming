
/*
Given an undirected, connected and weighted graph G(V, E) with V number of vertices (which are numbered from 0 to V-1) and E number of edges.
Find and print the shortest distance from the source vertex (i.e. Vertex 0) to all other vertices (including source vertex also) using Dijkstra's Algorithm.
Input Format :
Line 1: Two Integers V and E (separated by space)
Next E lines : Three integers ei, ej and wi, denoting that there exists an edge between vertex ei and vertex ej with weight wi (separated by space)
Output Format :
For each vertex, print its vertex number and its distance from source, in a separate line. The vertex number and its distance needs to be separated by a single space.
Note : Order of vertices in output doesn't matter.
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
0 0
1 3
2 4
3 5 
*/

#include <bits/stdc++.h>
using namespace std;

int getMinDisVer (bool *visited, int *distance, int n) {
    int minVertex = -1;
    
    for (int i = 0; i < n; ++i) 
        if (!visited[i] && (minVertex == -1 || distance[i] < distance[minVertex])) 
            minVertex = i;
    
    return minVertex;
}

void dijkstras (int **edges, int n, bool *visited, int *distance) {
    
    distance[0] = 0;
    // visited[0] = true;
    for (int i = 0; i < n; ++i) {

        // get unvisited vertex with minimum distance
        int minVertex = getMinDisVer (visited, distance, n);
        visited[minVertex] = true; 

        // explore all the neighbors of minvertex which are unvisited and update distance array if required
        for (int j = 0; j < n; ++j) {
            if (edges[minVertex][j] && !visited[j]) {
                int currD = distance[minVertex] + edges[minVertex][j];
                if (distance[j] > currD) {
                    distance[j] = currD;
                }
            }
        }
    }
    
    for (int i = 0; i < n; ++i) {
        if (visited[i])
            cout << i << " " << distance[i] << endl;
    }
}

int main() {
    int n, e;
    cin >> n >> e;
    
    int **edges = new int*[n];
    bool *visited = new bool[n];
    int *distance = new int[n];
    for (int i = 0; i < n; ++i) {
        edges[i] = new int[n];
        visited[i] = false;
        distance[i] = INT_MAX;
        for (int j = 0; j < n; ++j) 
            edges[i][j] = 0;
    }
    
    int a, b, weight;
    for (int i = 0; i < e; ++i) {
        cin >> a >> b >> weight;
        edges[a][b] = weight;
        edges[b][a] = weight;
    }
    
    dijkstras (edges, n, visited, distance);
    
    delete [] visited;
    for (int i = 0; i < n; ++i)
        delete [] edges[i];
    delete [] edges;
}