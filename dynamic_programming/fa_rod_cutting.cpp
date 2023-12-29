#include<bits/stdc++.h>
#define max(a, b) a > b ? a : b
using namespace std;
 
int cutrod(int *price, int n){
    if(n == 1) return price[0];

    int arr[n+1] = {0};
    int s[n+1] = {0};

    for(int i = 1; i <= n; i++){
        int max_val = INT_MIN;

        for(int j = 0; j < i; j++){
            /* Update the maximum value if the current price plus the optimal price 
                when the rod is at length 'i' minus the price at length 'j' is greater than maximum value
            */
            if(price[j] + arr[i - j - 1] > max_val){
                max_val = price[j] + arr[i - j - 1];
                s[i] = j + 1;
            }
        }
        arr[i] = max_val;
    }

    
    cout << "DP Table : " << endl;
    for(int i = 0; i <= n; i++){
        cout << arr[i] << " ";
    } cout << "\n";
    
    for(int i = 0 ; i <= n; i++){
        cout << s[i] << " ";
    } cout << "\n";

    return arr[n];
}
 
int main(){
    int price[] = {1, 5, 8, 9, 10, 17, 17, 20, 24, 30};
    int length = 4;

    cout << "Maximum Obtainable Value is "<< cutrod(price, length);
    return 0;
}
