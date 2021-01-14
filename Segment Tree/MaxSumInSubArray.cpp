/* 
    You are given a sequence A[1], A[2], ..., A[N] . ( |A[i]| ≤ 15007 , 1 ≤ N ≤ 50000 ). A query is defined as follows:
    Query(x,y) = Max { a[i]+a[i+1]+...+a[j] ; x ≤ i ≤ j ≤ y }.
    Given M queries, your program must output the results of these queries.

    Input
    The first line of the input file contains the integer N.
    In the second line, N numbers follow.
    The third line contains the integer M.
    M lines follow, where line i contains 2 numbers xi and yi.

    Output
    Your program should output the results of the M queries, one 
    query per line.

    Sample Input:
    3 
    -1 2 3 
    1
    1 2

    Sample Output:
    2
*/
#include <bits/stdc++.h>
using namespace std;

struct node {
    int sum, maxSum, prefixSum, suffixSum;
};

void buildTree (int *arr, node *tree, int s, int e, int index) {
    if (s == e) {
        tree[index].sum = arr[s];
        tree[index].maxSum = arr[s];
        tree[index].prefixSum = arr[s];
        tree[index].suffixSum = arr[s];
        return;
    }
    int m = (s + e) / 2;
    int left = 2*index;
    int right = 2*index + 1;
    buildTree (arr, tree, s, m, left);
    buildTree (arr, tree, m + 1, e, right);

    tree[index].sum = tree[left].sum + tree[right].sum;
    tree[index].prefixSum = max (tree[left].prefixSum, tree[left].sum + tree[right].prefixSum);
    tree[index].suffixSum = max (tree[right].suffixSum, tree[right].sum + tree[left].suffixSum);
    tree[index].maxSum = max (tree[index].prefixSum, max (tree[index].suffixSum, max (tree[left].maxSum,
                         max (tree[right].maxSum, tree[left].suffixSum + tree[right].prefixSum))));
}

node query (node *tree, int s, int e, int l, int r, int index) {
    node result;
    result.sum = result.maxSum = result.prefixSum = result.suffixSum = INT_MIN;

    if (s > r || e < l)
        return result;

    if (s >= l && e <= r)
        return tree[index];

    int m = (s + e) / 2;
    
    if (m < l) 
        return query (tree, m + 1, e, l, r, 2 * index + 1);
    if (r <= m) 
        return query (tree, s, m, l, r, 2 * index);
    
    
    node left = query (tree, s, m, l, r, 2 * index);
    node right = query (tree, m + 1, e, l, r, 2 * index + 1);

    result.sum = left.sum + right.sum;
    result.prefixSum = max (left.prefixSum, left.sum + right.prefixSum);
    result.suffixSum = max (right.suffixSum, right.sum + left.suffixSum);
    result.maxSum = max (result.prefixSum, max (result.suffixSum, max (left.maxSum,
                    max (right.maxSum, left.suffixSum + right.prefixSum))));

    return result;
}

int main () {
    int n;
    cin >> n;
    int arr[n];
    for (int i = 0; i < n; ++i) 
        cin >> arr[i];

    int q;
    cin >> q;
    node tree[4*n];
    buildTree (arr, tree, 0, n - 1, 1);
    while (q--) {
        int x, y;
        cin >> x >> y;
        node t = query (tree, 0, n - 1, x - 1, y - 1, 1);
        cout << t.maxSum << endl;
    }
}