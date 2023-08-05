#include<stdio.h>

void conquer(int arr[], int l, int m, int r){
	int temp[r-l+1], tempIdx = 0;
	int ml = l, mr = m+1;
	while(ml <= m && mr <= r){
		if(arr[ml] < arr[mr]){
			temp[tempIdx++] = arr[ml++];
		} else {
			temp[tempIdx++] = arr[mr++];
		}
	}
	while(ml <= m){
		temp[tempIdx++] = arr[ml++];
	}
	for(int i = 0; i < tempIdx; i++){
		arr[i+l] = temp[i];
	}
}

void divide(int arr[], int l, int r){
	if(l != r){
		int m = l + (r-l)/2;
		divide(arr, l, m);
		divide(arr, m+1, r);
		conquer(arr, l, m, r);
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
	divide(arr, 0, len-1);
	print(arr, len);
	return 0;
}
