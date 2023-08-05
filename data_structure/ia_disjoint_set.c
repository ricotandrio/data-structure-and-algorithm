#include<stdio.h>

int parent[100] = {};
void makeSet(int size){
	for(int i = 0; i < size; i++){
		parent[i] = i;
	}
}

int findparent(int x){
	if(parent[x] != x){
		parent[x] = findparent(parent[x]);
	}
	return parent[x];
}

void unionset(int x, int y){
	int rootx = findparent(x);
	int rooty = findparent(y);
	if(rootx != rooty) parent[y] = rootx;
	else puts(" Cyclic");
}

int main(){
	makeSet(5);
	unionset(1, 2);
	unionset(2, 3);
	unionset(0, 1);
	printf("Parent 3 : %d\n", findparent(3));
	return 0;
}
