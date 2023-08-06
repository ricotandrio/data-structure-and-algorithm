#include<stdio.h>

void insertionSort(int arr[], int len){
    int temp, i, j;
    for(i = 1; i < len; i++){
        temp = arr[i];
        for(j = i - 1; j >= 0 && temp < arr[j]; j--){
            arr[j + 1] = arr[j];
        }
        arr[j + 1] = temp;
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
	insertionSort(arr, len);
    print(arr, len);
	return 0;
}
