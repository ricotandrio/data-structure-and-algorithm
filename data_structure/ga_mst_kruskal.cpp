#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#define maxN 100

int parent[maxN];
void initDisjoint(){
	for(int i = 0; i < maxN; i++){
		parent[i] = i; // parent of initialize node is it self
	}
}

int getAncestor(int x){
	if (parent[x] == x) {
		return x;
	}
	// when parent is different then check another parent
	return getAncestor(parent[x]);
}

bool isSameAncestor(int x, int y) {
	return getAncestor(x) == getAncestor(y);
}

void merge(int x, int y) { // merge ancestor of x and ancestor of y
	int ancX = getAncestor(x), ancY = getAncestor(y);

	if(ancX == ancY) return;

	parent[ancX] = ancY;
}

struct Edge {
	int source, destination, weight;
};

struct Edge constructorEdge(int source, int destination, int weight){
	struct Edge newEdge;
	newEdge.source = source;
	newEdge.destination = destination;
	newEdge.weight = weight;
	return newEdge;
};

struct Edge edgeList[] = {
  	constructorEdge(0, 1, 10),
  	constructorEdge(0, 2, 15),
  	constructorEdge(1, 2, 35),
  	constructorEdge(1, 3, 10),
  	constructorEdge(1, 4, 22),
  	constructorEdge(2, 3, 43),
	constructorEdge(3, 4, 32)
};

int edgeListSize = 7;

void sortEdgeList(){
	for(int i = 0; i < edgeListSize; i++){
		int index = i;
		while(index > 0 && edgeList[index].weight < edgeList[index - 1].weight){
			Edge t = edgeList[index];
			edgeList[index] = edgeList[index - 1];
			edgeList[index - 1] = t;
			index--;
		}
	}
}

int main(){
	initDisjoint();
	sortEdgeList();
	int totalWeight = 0;

	for(int i = 0; i < edgeListSize; i++) {
		struct Edge edge = edgeList[i];

		if(isSameAncestor(edge.source, edge.destination)) continue;

		totalWeight += edge.weight;
		merge(edge.source, edge.destination);
		printf("%d %d %d\n", edge.source, edge.destination, edge.weight);
	}

	printf("%d\n", totalWeight);
	return 0;
}
