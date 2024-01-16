#include<bits/stdc++.h>
using namespace std;

void display_dp(int *diff_at, int *total_at, int n);

int main(){
    int n = 5, k = 3;

    int diff_at[n] = {k}, total_at[n] = {k};

    for(int i = 1; i < n; i++){  
        int same = diff_at[i - 1];
        int diff = total_at[i - 1] * (k - 1);

        diff_at[i] = diff;
        total_at[i] = same + diff;
    }

    display_dp(diff_at, total_at, n);

    cout << "Total: " << total_at[n - 1] << endl;

    return 0;
}

void display_dp(int *diff_at, int *total_at, int n) {
    for(int i = 0; i < n; i++){
        cout << total_at[i] - diff_at[i] << " ";
    } cout << endl;

    for(int i = 0; i < n; i++){
        cout << diff_at[i] << " ";
    } cout << endl;

    for(int i = 0; i < n; i++){
        cout << total_at[i] << " ";
    } cout << endl;
}

