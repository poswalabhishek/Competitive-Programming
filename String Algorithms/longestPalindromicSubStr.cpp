#include<bits/stdc++.h>
using namespace std;

int lps (string s) {
    int max = 0;
    int n = s.length();

    for (int i = 0; i < n; ++i) {
        // odd length
        int  l = i;
        int r = i;
        
        while (l >= 0 && r < n && s[l] == s[r]) {
            int curr_l = r - l + 1;
            if (curr_l > max) {
                max = curr_l;
            }
            --l;
            ++r;
        }

        // even length

        l = i;
        r = i + 1;
        while (l >= 0 && r < n && s[l] == s[r]) {
            int curr_l = r - l + 1;
            if (curr_l > max) {
                max = curr_l;
            }
            --l;
            ++r;
        }
    }
    return max;
}

int main () {
    string s;
    cin >> s;

    cout << lps (s) << endl;

    return 0;
}