#include<stdio.h>

void swap(int *a, int *b){
	int temp = *a;
	*a = *b;
	*b = temp;
}

int partition(int arr[], int l, int r){
	int pivot = arr[r];
	int i = l - 1;
	for(int j = l; j < r; j++){
		printf("%d\n", j);
		if(arr[j] < pivot){
			i++;
			swap(&arr[i], &arr[j]);
		}
	}
	swap(&arr[i+1], &arr[r]);
	return i + 1;
}

void quickSort(int arr[], int l, int r){
	if(l < r){
		int part = partition(arr, l, r);
		quickSort(arr, l, part-1);
		quickSort(arr, part+1, r);
	}
}

void print(int arr[], int n){
	for(int i = 0; i < n; i++){
		printf("%d ", arr[i]);
	}
}

int main(){
	int arr[] = {1, 3, 4, 9, 3, 5, 2, 9};
	int len = sizeof(arr)/sizeof(int);
	quickSort(arr, 0, len-1);
	print(arr, len);
	return 0;
}
