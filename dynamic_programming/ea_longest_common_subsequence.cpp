#include<bits/stdc++.h>
#include<cstring>
using namespace std;

int lcs(string X, string Y, int m, int n, string &lcsString) {
    int arr[m + 1][n + 1];

    // Initialize DP table
    for(int i = 0; i <= m; i++) {
        for(int j = 0; j <= n; j++) {
            if(i == 0 || j == 0) arr[i][j] = 0;
            else if(X[i - 1] == Y[j - 1]) arr[i][j] = arr[i - 1][j - 1] + 1;
            else arr[i][j] = max(arr[i - 1][j], arr[i][j - 1]);
        }
    }

    // Construct LCS string
    int index = arr[m][n], i = m, j = n;  
    char lcs[index + 1] = {'\0'};

    while(i > 0 && j > 0) {
        if(X[i - 1] == Y[j - 1]) {
            lcs[--index] = X[--i];
            j--;
        } else if(arr[i - 1][j] >= arr[i][j - 1]) {
            i--;
        } else {
            j--;
        }
    }

    // update original string 
    lcsString = lcs;
    
    cout << "DP Table : " << endl;
    for(int i = 0; i <= m; i++){
        for(int j = 0; j <= n; j++){
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
    
    return arr[m][n];
}

int main() {
    string S1 = "ABCBDAB", S2 = "BDCABA";
    int m = S1.size(), n = S2.size();
    string lcsString;

    cout << "Length of Longest Common Subsequence is " << lcs(S1, S2, m, n, lcsString) << endl;
    cout << "Possible Longest Common Subsequence is " << lcsString << endl;

    return 0;
}
