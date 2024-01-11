#include <stdio.h>
#define true 1
#define false 0

int interpolationSearch(int arr[], int key, int len) {
    int mid, min = 0, max = len - 1;
    while(arr[min] <= key && arr[max] >= key) {
        // Prevent division by zero
        if(arr[min] == arr[max]) {
            if(arr[min] == key){
                return true;
            } else {
                return false;
            }
        }

        mid = min + ((key - arr[min]) * (max - min)) / (arr[max] - arr[min]);

        if (arr[mid] < key) {
            min = mid + 1;
        } else if (arr[mid] > key) {
            max = mid - 1;
        } else {
            return true;
        }
    }
    return false;
}

int main() {
    int arr[] = {1, 3, 2, 4, 5, 11, 6, 7, 9, 10};
    int arrLen = sizeof(arr) / sizeof(int);

    // Sort the array before performing the interpolation search
    for (int i = 0; i < arrLen - 1; i++) {
        for (int j = 0; j < arrLen - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }

    printf("search for %d, result: %s\n", 3, interpolationSearch(arr, 3, arrLen) == true ? "found" : "not found");
    printf("search for %d, result: %s\n", 30, interpolationSearch(arr, 30, arrLen) == true ? "found" : "not found");
    printf("search for %d, result: %s\n", 10, interpolationSearch(arr, 10, arrLen) == true ? "found" : "not found");

    return 0;
}
