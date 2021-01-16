/*
Given an undirected graph G(V, E) and two vertices v1 and v2 (as integers), check if there exists any path between them or not. Print true if the path exists and false otherwise.
Note:
1. V is the number of vertices present in graph G and vertices are numbered from 0 to V-1. 
2. E is the number of edges present in graph G.
Input Format :
The first line of input contains two integers, that denote the value of V and E.
Each of the following E lines contains two integers, that denote that there exists an edge between vertex 'a' and 'b'.
The following line contain two integers, that denote the value of v1 and v2.
Output Format :
The first and only line of output contains true, if there is a path between v1 and v2 and false otherwise.
Constraints :
0 <= V <= 1000
0 <= E <= 1000
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
true
Sample Input 2 :
6 3
5 3
0 1
3 4
0 3
Sample Output 2 :
false
*/

#include <bits/stdc++.h>
using namespace std;

//using bfs
bool hasPath (int arr[][1000], int n, int v1, int v2, bool *visited) {
    
    queue<int> pendingVertices;
    pendingVertices.push(v1);
    visited[v1] = true;
    while (!pendingVertices.empty()) {
        int curr = pendingVertices.front();
        if (curr == v2)
            return true;
        pendingVertices.pop();
        for (int i = 0; i < n; ++i) {
            if (curr == i)
                continue;
            if (arr[curr][i] == 1 && !visited[i]) {
                pendingVertices.push(i);
                visited[i] = true;
            }
        }
    }
    return false;
}

int main() {
    int numVertices, numEdges;
    cin >> numVertices >> numEdges;
    
    int a, b;
    int arr[numVertices][1000];
    for (int i = 0; i < numEdges; ++i) {
        cin >> a >> b;
        arr[a][b] = 1;
        arr[b][a] = 1;
    }
    int vertex1, vertex2;
    cin >> vertex1 >> vertex2;
    
    bool visited[numVertices];
    memset(visited, false, sizeof(visited));

    
    if (hasPath (arr, numVertices, vertex1, vertex2, visited))
        cout << "true" << endl;
    else
        cout << "false" << endl;
}

