// find total unique way to make sum
#include<stdio.h>
#define SZ 3

int coinChange(int *coin, int sum){
	int arr[SZ+1][sum+1];
	for(int i = 0; i <= SZ; i++){
		for(int j = 0; j <= sum; j++){
			if(j == 0) arr[i][j] = 1;
			else if(i == 0 && j > 0) arr[i][j] = 0;
			else if(j < coin[i-1]) arr[i][j] = arr[i-1][j];
			else {
				int exCoin = arr[i-1][j];
				int inCoin = arr[i][j-coin[i-1]];
				arr[i][j] = exCoin + inCoin;
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
	int coin[] = {1, 2, 5};
	int sum = 25;
	printf("%d\n", coinChange(coin, sum));
	return 0;
}
