#include <iostream>
using namespace std;

void printDFS (int **edges, int numVertices, int startVertex, bool *visited) {
    cout << startVertex << endl;
    visited[startVertex] = true;
    for (int i = 0; i < numVertices; ++i) {
        if (i == startVertex)
            continue;
        if (edges[startVertex][i] == 1) {
            if (visited[i])
                continue;
            printDFS (edges, numVertices, i, visited);
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

    printDFS (edges, numVertices, 0, visited);

    delete [] visited;
    for (int i = 0; i < numVertices; ++i)
        delete [] edges[i];
    delete [] edges;

    return 0;
}