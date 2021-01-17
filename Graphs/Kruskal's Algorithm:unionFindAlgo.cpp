/*

Given an undirected, connected and weighted graph G(V, E) with V number of vertices (which are numbered from 0 to V-1) and E number of edges.
Find and print the Minimum Spanning Tree (MST) using Kruskal's algorithm.
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
1 2 1
0 1 3
0 3 5

*/


#include <bits/stdc++.h>
using namespace std;

class edge {
public:
    int src;
    int dest;
    int weight;
};

bool sortWithWeight (edge e1, edge e2) {
    return (e1.weight < e2.weight);
}

int getParent (int v, int *parent) {
    if (parent[v] == v)
        return v;
    return getParent(parent[v], parent);
}

// different components than true else false
bool unionFindAlgo (int *parent, int const v1, int const v2) {
    int srcParent = getParent (v1, parent);
    int destParent = getParent (v2, parent);
    
    if (srcParent != destParent) {
        parent[srcParent] = destParent;
        return true;
    }
    return false;
}

int main() {
    int v, e;
    cin >> v >> e;
    
    int v1, v2, weight;
    edge edges[e];
    for (int i = 0; i < e; ++i) {
        cin >> v1 >> v2 >> weight;
        if (v1 < v2) {
            edges[i].src = v1;
            edges[i].dest = v2;
        } else {
            edges[i].src = v2;
            edges[i].dest = v1;
        }
        
        edges[i].weight = weight;
    }
    sort (edges, edges + e, sortWithWeight);
    
    int parent[v];
    for (int i = 0; i < v; ++i)
        parent[i] = i;
    int count = 0, i = 0;
    vector<edge> ans;
    int ve1, ve2;
    edge x;
    while (count < v - 1) {
        ve1 = edges[i].src;
        ve2 = edges[i].dest;
        
        if (unionFindAlgo(parent, ve1, ve2)) {
            x.src = ve1;
            x.dest = ve2;
            x.weight = edges[i].weight;
//            parent[ve1] = parent[ve2];
            ans.push_back(x);
            ++count;
        }
        ++i;
    }
    
    for (int i = 0; i < ans.size(); ++i)
        cout << ans[i].src << " " << ans[i].dest << " " << ans[i].weight << endl;
    
    
    return 0;
}
