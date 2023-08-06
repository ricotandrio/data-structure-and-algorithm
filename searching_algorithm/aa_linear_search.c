#include<stdio.h>
#define true 1
#define false 0

int linearSearch(int key, int *arr, int arrLen){
    for(int i = 0; i < arrLen; i++){
        if(key == arr[i]){
            return true;
        }
    }
    return false;
}

int main(){
    int arr[] = {1, 3, 2, 4, 5, 11, 6, 7, 9, 10};
    int arrLen = sizeof(arr) / sizeof(int);

    printf("search for %d, result: %s\n", 3, linearSearch(3, arr, arrLen) == true ? "found" : "not found");
    printf("search for %d, result: %s\n", 30, linearSearch(30, arr, arrLen) == true ? "found" : "not found");
    printf("search for %d, result: %s\n", 10, linearSearch(10, arr, arrLen) == true ? "found" : "not found");

    return 0;
}
