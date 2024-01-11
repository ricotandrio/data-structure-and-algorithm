#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<vector>
#define maxN 100
using namespace std;

struct Adj{
	int destination, weight;
};

vector<Adj> adjList[maxN], queue;
bool visited[maxN] = {0};

struct Adj constructorAdj(int destination, int weight){
	struct Adj newEdge;
	newEdge.destination = destination;
	newEdge.weight = weight;
	return newEdge;
};

void insertQueueAndSort(Adj newAdj){
	queue.push_back(newAdj);
	int index = queue.size() - 1;
	while(index > 0 && queue[index].weight < queue[index - 1].weight){
		Adj t = queue[index];
		queue[index] = queue[index - 1];
		queue[index - 1] = t;
		index--;
 	}
}

void pickNode(int x){
	if(visited[x] == true) return;

	visited[x] = 1;
	for(int i = 0; i < adjList[x].size(); i++) {
		insertQueueAndSort(adjList[x][i]);
	}
}

int main(){
	adjList[0].push_back(constructorAdj(1, 9));
	adjList[1].push_back(constructorAdj(0, 9));
	adjList[1].push_back(constructorAdj(2, 95));
	adjList[2].push_back(constructorAdj(0, 75));
	adjList[2].push_back(constructorAdj(3, 51));
	adjList[3].push_back(constructorAdj(1, 19));
	adjList[4].push_back(constructorAdj(1, 42));

	int startingNode = 0, totalWeight = 0;;
	pickNode(startingNode);
	while(queue.size() > 0) {
		Adj curr = queue[0];
		queue.erase(queue.begin());

		if(visited[curr.destination] == true) continue;

		totalWeight += curr.weight;
		pickNode(curr.destination);
	}

	printf("%d\n", totalWeight);
}
