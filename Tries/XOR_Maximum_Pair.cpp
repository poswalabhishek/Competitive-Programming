#include<bits/stdc++.h>
using namespace std;

class trieNode {
public:
    trieNode* left;
    trieNode* right;
};

void insert (int n, trieNode* root) {

    trieNode* curr = root;
    for (int i = 31; i >= 0; --i) {
        int b = (n >> i) & 1;

        if (b == 0) {
            if (!curr->left) {
                curr->left = new trieNode();
            }
            curr = curr->left;
        } else {
            if (!curr->right) {
                curr->right = new trieNode();
            }
            curr = curr->right;
        }
    }
}

int findMaXorPair (trieNode* root, int *arr, int n) {

    int max_xor = INT_MIN;
    for (int i = 0; i< n; ++i) {
        trieNode* curr = root;
        int value = arr[i];
        int curr_xor = 0;
        for (int j = 31; j >= 0; --j) {
            int b = (value >> j) & 1;

            if (b == 0) {
                // move towards right if it exists
                if (curr->right) {
                    // 2 ^ 31 * 1 + 2 ^ 30 * 2
                    curr_xor += pow(2, j);
                    curr = curr->right;
                } else {
                    curr = curr->left;
                }

            } else {
                // move towards left if it exists
                if (curr->left) {
                    curr_xor += pow(2, j);
                    curr = curr->left;
                } else {
                    curr = curr->right;
                }
            }

            if (max_xor < curr_xor)
                max_xor = curr_xor;
        }
    }

    return max_xor;
}

int main () {

    int n;
    cin >> n;
    int arr[n];
    trieNode* root = new trieNode();
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }

    for (int i = 0; i < n; ++i) {
        insert (arr[i], root);
    }
    

    cout << findMaXorPair (root, arr, n) << endl;
    
    return 0;
}
