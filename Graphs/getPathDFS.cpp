/*

Given an undirected graph G(V, E) and two vertices v1 and v2(as integers), find and print the path from v1 to v2 (if exists). Print nothing if there is no path between v1 and v2.
Find the path using DFS and print the first path that you encountered.
Note:
1. V is the number of vertices present in graph G and vertices are numbered from 0 to V-1. 
2. E is the number of edges present in graph G.
3. Print the path in reverse order. That is, print v2 first, then intermediate vertices and v1 at last.
4. Save the input graph in Adjacency Matrix.
Input Format :
The first line of input contains two integers, that denote the value of V and E.
Each of the following E lines contains two integers, that denote that there exists an edge between vertex 'a' and 'b'.
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

vector<int>* getPathDFS (int arr[][10000], int n, int v1, int v2, bool* visited) {
    
    if (v1 == v2) {
        vector<int> *output = new vector<int> ();
        output->push_back(v2);
        visited[v2] = true;
        return output;
    }
    visited[v1] = true;
    for (int i = 0; i < n; ++i) {
        if (arr[v1][i] == 1 && !visited[i]) {
            vector<int>* smallOutput = getPathDFS (arr, n, i, v2, visited);
            if (smallOutput != NULL) {
                smallOutput->push_back(v1);
                return smallOutput;
            }
            
        }
    }
    return NULL;
}

int main() {
    int numVertices, numEdges;
    cin >> numVertices >> numEdges;
    
    int a, b;
    int arr[numVertices][10000];
    for (int i = 0; i < numEdges; ++i) {
        cin >> a >> b;
        arr[a][b] = 1;
        arr[b][a] = 1;
    }
    int vertex1, vertex2;
    cin >> vertex1 >> vertex2;
    
    bool visited[numVertices];
    memset(visited, false, sizeof(visited));
	
    vector<int>* output = getPathDFS (arr, numVertices, vertex1, vertex2, visited);
    
    if (output != NULL) {
    	for (int i = 0; i < output->size(); ++i)
            cout << output->at(i) << " ";
        delete output;
    }
    
    return 0;
}