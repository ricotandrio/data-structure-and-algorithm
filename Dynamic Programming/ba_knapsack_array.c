#include<stdio.h>
#define MAX(a,b) a > b ? a : b
#define SZ 3

int knapsack(int *weight, int *value, int maxWeight){
	int arr[SZ+1][maxWeight+1];	
	for(int i = 0; i <= SZ; i++){
		for(int j = 0; j <= maxWeight; j++){
			if(i == 0 && j == 0) arr[i][j] = 0;
			else if(j < weight[i-1]) arr[i][j] = arr[i-1][j];
			else {
				arr[i][j] = MAX(weight[i-1], value[i-1] + arr[i-1][j - weight[i-1]]);
			}
		}
	}
	return arr[SZ][maxWeight];
}

int main(){
	int weight[] = {10, 20, 30};
	int value[] = {60, 100, 120};
	int maxWeight = 50;
	printf("%d\n", knapsack(weight, value, maxWeight));
	return 0;
}
