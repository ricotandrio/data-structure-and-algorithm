#include<stdio.h>

// swap array by address
void swap(int *a, int *b){
	int temp = *a;
	*a = *b;
	*b = temp;
}

void selectionSort(int arr[], int len){
    for(int i = 0; i < len - 1; i++){
        int smallest = i; // create index to store smallest index
        for(int j = i + 1; j < len; j++){
            if(arr[j] < arr[smallest]){
                smallest = j; // change smallest index to j, if arr[j] < arr[smallest]
            }
        }
        if(smallest != i) swap(&arr[i], &arr[smallest]);
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
	selectionSort(arr, len);
    print(arr, len);
	return 0;
}
