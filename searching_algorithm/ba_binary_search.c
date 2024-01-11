#include<stdio.h>
#define true 1
#define false 0

int binarySearch(int key, int arr[], int l, int r){
    while(l <= r){
        int mid = (l + r) / 2;
        if(arr[mid] == key){
            return true;
        } else if(arr[mid] > key){
            r = mid - 1;
        } else if(arr[mid] < key){
            l = mid + 1;
        }
    }
    return false;
}


int main(){
    int arr[] = {1, 3, 2, 4, 5, 11, 6, 7, 9, 10};
    int arrLen = sizeof(arr) / sizeof(int);

    // Sort the array before performing the binary search
    for (int i = 0; i < arrLen - 1; i++) {
        for (int j = 0; j < arrLen - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }

    printf("search for %d, result: %s\n", 3, binarySearch(3, arr, 0, arrLen - 1) == true ? "found" : "not found");
    printf("search for %d, result: %s\n", 30, binarySearch(30, arr, 0, arrLen - 1) == true ? "found" : "not found");
    printf("search for %d, result: %s\n", 10, binarySearch(10, arr, 0, arrLen - 1) == true ? "found" : "not found");

    return 0;
}
