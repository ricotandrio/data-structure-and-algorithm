#include<stdio.h>
#define MAX(a,b) a > b ? a : b
#define SZ 4

int knapsack(int *weight, int *value, int maxWeight){
	int arr[SZ+1][maxWeight+1];	
	for(int i = 0; i <= SZ; i++){
		for(int j = 0; j <= maxWeight; j++){
			if(i == 0 || j == 0) arr[i][j] = 0;
			else if(j < weight[i-1]) arr[i][j] = arr[i-1][j];
			else {
				arr[i][j] = MAX(arr[i-1][j], value[i-1] + arr[i - 1][j - weight[i - 1]]);
			}
		}
	}

	for(int i = -1; i <= SZ; i++){
		for(int j = -1; j <= maxWeight; j++){
			if(i == -1){
				printf("%d ", j == -1 ? 0 : j);
			} else if(j == -1) {
				printf("%d ", i);
			} else {
				printf("%d ", arr[i][j]);
			}
		} puts("");
	}

	return arr[SZ][maxWeight];
}

int main(){
	int weight[] = {2, 3, 4, 5};
	int value[] = {1, 2, 5, 6};
	int maxWeight = 8;
	printf("%d\n", knapsack(weight, value, maxWeight));
	return 0;
}
