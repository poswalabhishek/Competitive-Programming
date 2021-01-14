#include <bits/stdc++.h>
using namespace std;

void printBFS (int **edges, int numVertices, int startVertex, bool *visited) {
    
    queue <int> pendingVertices;
    pendingVertices.push(startVertex);
    visited[startVertex] = true;
    while (!pendingVertices.empty()) {
        int currVertex = pendingVertices.front();
        pendingVertices.pop();
        cout << currVertex << " ";
        for (int i = 0; i < numVertices; ++i) {
            if (i == currVertex)
                continue;
            if (edges[currVertex][i] == 1 && !visited[i]) {
                pendingVertices.push(i);
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

    printBFS (edges, numVertices, 0, visited);

    delete [] visited;
    for (int i = 0; i < numVertices; ++i)
        delete [] edges[i];
    delete [] edges;

    return 0;
}
