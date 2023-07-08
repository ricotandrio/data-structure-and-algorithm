#include<stdio.h>

long long int getMax(long long int a, long long int b){
	return a > b ? a : b;
}

long long int knapsackGetMax(long long int maxWeight, long long int weight[], long long int value[], long long int size){
    if(size == 0 || maxWeight == 0){
		return 0;
	}
    if(weight[size - 1] > maxWeight){
		return knapsackGetMax(maxWeight, weight, value, size - 1);
	} else{
		return getMax(value[size - 1] + knapsackGetMax(maxWeight - weight[size - 1], weight, value, size - 1),
			knapsackGetMax(maxWeight, weight, value, size - 1));
	}
}

int main(){
	long long int maxWeight = 30, valueCount = 5;
	long long int weight[100] = {10, 15, 12, 6, 20};
	long long int value[100] = {3, 2, 4, 5, 7};

	long long int maxValue = knapsackGetMax(maxWeight, weight, value, valueCount);

	printf("Max Weight: %lld\n", maxValue);
	return 0;
}
