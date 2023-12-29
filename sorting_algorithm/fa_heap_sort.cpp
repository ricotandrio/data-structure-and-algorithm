#include<bits/stdc++.h>
using namespace std;
#define parent(x) (x - 1) / 2
#define left(x) x * 2 + 1  
#define right(x) x * 2 + 2

int pop(int *heap, int *size_heap){
    int returnValue = heap[0];
    int curr = heap[--(*size_heap)];
    int i = 0;

    while(left(i) < (*size_heap)){
        int j = left(i);
        
        if(right(i) < (*size_heap) && heap[right(i)] > heap[left(i)]){
            j = right(i);
        }

        if(heap[j] <= curr) break;

        heap[i] = heap[j];

        i = j;
    }

    heap[i] = curr;

    return returnValue;
}

void push(int *heap, int val, int *size_heap){
    int curr = (*size_heap)++;
    while(curr > 0){
        int parentIndex = parent(curr);

        if(heap[parentIndex] >= val) break;

        heap[curr] = heap[parentIndex];

        curr = parentIndex; 
    }

    heap[curr] = val;
}

int main(){
    int arr[] = {1, 3, 4, 9, 3, 5, 2, 9};
	int len = sizeof(arr)/sizeof(int);

    int heap[len + 1] =  {}, size_heap = 0;

    for(int i = 0; i < len; i++){
        push(heap, arr[i], &size_heap);
    }

    for(int i = len - 1; i >= 0; i--){
        arr[i] =  pop(heap, &size_heap);
    }

    for(int i = 0; i < len; i++){
        cout << arr[i] << " ";
    } 
    
    cout << endl;
	
    return 0;
}
