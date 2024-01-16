#include<bits/stdc++.h>
using namespace std;

int maxCoins(int coins[], int n, int target) {
    int dp[target + 1];
    dp[0] = 0;

    for(int i = 1; i <= target; i++){
        dp[i] = INT_MAX;
        for(int j = 0; j < n; ++j){
            if(coins[j] <= i && dp[i - coins[j]] != INT_MAX)
                dp[i] = max(dp[i], dp[i - coins[j]] + 1);
        }
    }

    for(int i = 0; i <= target; i++){
        cout << (dp[i] == INT_MAX ? 0 : dp[i]) << " ";
    } cout << endl;

    return (dp[target] == INT_MAX ? -1 : dp[target]);
}

int main() {
    int coins1[] = {3, 10, 20};
    int target1 = 32;
    int n1 = sizeof(coins1) / sizeof(coins1[0]);
    cout << "Case 1 Output: " << minCoins(coins1, n1, target1) << endl;

    int coins2[] = {5, 10, 20};
    int target2 = 35;
    int n2 = sizeof(coins2) / sizeof(coins2[0]);
    cout << "Case 2 Output: " << minCoins(coins2, n2, target2) << endl;

    int coins3[] = {1, 2, 5};
    int target3 = 9;
    int n3 = sizeof(coins3) / sizeof(coins3[0]);
    cout << "Case 3 Output: " << minCoins(coins3, n3, target3) << endl;

    return 0;
}