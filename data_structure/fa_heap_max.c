#include<stdio.h>
#include<stdlib.h>
#define SIZE 30
#define parent(x) x / 2
#define left(x) x * 2
#define right(x) x * 2 + 1

struct node {
	int n;
} *heap[SIZE + 1] = {};

int filled = 0;

void swap(int a, int b){
	struct node *temp = heap[a];
	heap[a] = heap[b];
	heap[b] = temp;
}

void upheap(int index){
	if(filled <= 1) return;

	while(index != 1 && heap[index]->n > heap[parent(index)]->n){
		swap(index, parent(index));
		index = parent(index);
	}
}

void downheap(int index){
	if(index > filled || filled <= 1) return;

	int leftidx = left(index);
	int rightidx = right(index);

	if(leftidx <= filled && heap[leftidx] > heap[index]){
		swap(leftidx, index);
		downheap(leftidx);
	}

	if(rightidx <= filled && heap[rightidx] > heap[index]){
		swap(rightidx, index);
		downheap(rightidx);
	}
}

void push(int n){
	struct node *heapnew = (struct node *) malloc (sizeof(struct node));
	heapnew->n = n;

	heap[++filled] = heapnew;
	upheap(filled);
}

void view(){

	for(int i = 1; i <= filled; i++){
		printf("heap val %d: %d\n", i, heap[i]->n);
	}

}

void pop(){
	if(filled > 1){
		swap(1, filled);
	}
	free(heap[filled]);
	heap[filled] = NULL;
	filled--;

	if(filled > 1) downheap(1);
}

int main(){
	push(5);
	push(15);
	push(7);
	push(8);
	pop();
	view();
	return 0;
}
