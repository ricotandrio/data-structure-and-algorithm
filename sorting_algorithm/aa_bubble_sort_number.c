#include<stdio.h>

void swap(int *a, int *b){
	int temp = *a;
	*a = *b;
	*b = temp;
}

void bubbleSort(int arr[], int len){
    for(int i = 0; i < len - 1; i++){
        for(int j = 0; j < len - i - 1; j++){
            if(arr[j] > arr[j+1]){
                swap(&arr[j], &arr[j+1]);
            }
        }
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
	bubbleSort(arr, len);
    print(arr, len);
	return 0;
}