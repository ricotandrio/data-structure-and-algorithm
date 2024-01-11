#include<stdio.h>
#include<limits.h>
#define SZ 3

int min(int a, int b){
	return a < b ? a : b;
}

int coinChange(int *coin, int sum){
	int arr[SZ+1][sum+1];
	for(int i = 0; i <= SZ; i++){
		for(int j = 0; j <= sum; j++){
			if(j == 0) arr[i][j] = 0;
			else if(i == 0 && j > 0) arr[i][j] = INT_MAX;
			else if(j == coin[i - 1]) arr[i][j] = 1;
			else {
				int include = arr[i][j - coin[i - 1]] + 1;
				int exclude = arr[i - 1][j];
				arr[i][j] = min(include, exclude);
			} 
		}
	}	
	for(int i = 0; i <= SZ; i++){
		for(int j = 0; j <= sum; j++){
			printf(" %d", arr[i][j]);
		} puts("");
	}
	return arr[SZ][sum];
}

int main(){
	int coin[] = {1, 3, 4};
	int sum = 6;
	printf("%d\n", coinChange(coin, sum));
	return 0;
}