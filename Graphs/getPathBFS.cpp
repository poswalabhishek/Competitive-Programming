/*

Given an undirected graph G(V, E) and two vertices v1 and v2 (as integers), find and print the path from v1 to v2 (if exists). Print nothing if there is no path between v1 and v2.
Find the path using BFS and print the shortest path available.
Note:
1. V is the number of vertices present in graph G and vertices are numbered from 0 to V-1. 
2. E is the number of edges present in graph G.
3. Print the path in reverse order. That is, print v2 first, then intermediate vertices and v1 at last.
4. Save the input graph in Adjacency Matrix.
Input Format :
The first line of input contains two integers, that denote the value of V and E.
Each of the following E lines contains two integers, that denote that there exists an edge between vertex a and b.
The following line contain two integers, that denote the value of v1 and v2.
Output Format :
Print the path from v1 to v2 in reverse order.
Constraints :
2 <= V <= 1000
1 <= E <= (V * (V - 1)) / 2
0 <= a <= V - 1
0 <= b <= V - 1
0 <= v1 <= 2^31 - 1
0 <= v2 <= 2^31 - 1
Time Limit: 1 second
Sample Input 1 :
4 4
0 1
0 3
1 2
2 3
1 3
Sample Output 1 :
3 0 1
Sample Input 2 :
6 3
5 3
0 1
3 4
0 3
Sample Output 2 :
*/

#include <bits/stdc++.h>
using namespace std;

void getPathBFS (int **edges, int n, int v1, int v2, bool *visited, unordered_map <int, int> &m) {
    queue <int> pendingVertices;
    pendingVertices.push(v1);
    visited[v1] = true;
    
    while (!pendingVertices.empty()) {
        int currVertex = pendingVertices.front();
        pendingVertices.pop();
        if (currVertex == v2)
            return;
        for (int i = 0; i < n; ++i) {  
            if (edges[currVertex][i] == 1 && !visited[i]) {
                pendingVertices.push(i);
                m[i] = currVertex;
                visited[i] = true;
            }
        }
    }
}

int main () {
    int numVertices, numEdges;
    cin >> numVertices >> numEdges;

    int **edges = new int*[numVertices];
    for (int i = 0; i < numVertices; ++i) {
        edges[i] = new int[numVertices];
        for (int j = 0; j < numVertices; ++j)
            edges[i][j] = 0;
    }

    int first, second;
    // int startIndex;
    for (int i = 0; i < numEdges; ++i){
        cin >> first >> second;
        // if (i == 0)
        //     startIndex = first;
        edges[first][second] = 1;
        edges[second][first] = 1;
    }
    bool *visited = new bool[numVertices];
    for (int i = 0; i < numVertices; ++i)
        visited[i] = false;
	
    int vertex1, vertex2;
    cin >> vertex1 >> vertex2;
    unordered_map <int, int> whoPutWhom;
    getPathBFS (edges, numVertices, vertex1, vertex2, visited, whoPutWhom);
    
    if (visited[vertex2]) {
        int t = vertex2;
        while (t != vertex1) {
            cout << t << " ";
            t = whoPutWhom[t];
        }
        cout << t << endl;
    }
    
    delete [] visited;
    for (int i = 0; i < numVertices; ++i)
        delete [] edges[i];
    delete [] edges;
    
    return 0;
}