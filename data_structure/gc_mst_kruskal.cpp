#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <algorithm>
#define maxN 100
using namespace std;

int parent[maxN];
int ranks[maxN]; // used to keep track of the depth (or height) of the trees

void initDisjoint() {
    for (int i = 0; i < maxN; i++) {
        parent[i] = i; // parent of initialize node is itself
        ranks[i] = 0; // initialize rank to 0
    }
}

int find(int x) {
    if (parent[x] != x) {
        parent[x] = find(parent[x]); // path compression
    }
    return parent[x];
}

void merge(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);

    if (rootX == rootY) return;

    // union by rank
    if (ranks[rootX] < ranks[rootY]) {
        parent[rootX] = rootY;
    } else if (ranks[rootX] > ranks[rootY]) {
        parent[rootY] = rootX;
    } else {
        parent[rootY] = rootX;
        ranks[rootX]++;
    }
}

struct Edge {
    int source, destination, weight;
};

struct Edge constructorEdge(int source, int destination, int weight) {
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

void sortEdgeList() {
    sort(edgeList, edgeList + edgeListSize, [](const Edge &a, const Edge &b) {
        return a.weight < b.weight;
    });
}

int main() {
    initDisjoint();
    sortEdgeList();
    int totalWeight = 0;

    for (int i = 0; i < edgeListSize; i++) {
        struct Edge edge = edgeList[i];

        if (find(edge.source) == find(edge.destination)) continue;

        totalWeight += edge.weight;
        merge(edge.source, edge.destination);
        printf("%d %d %d\n", edge.source, edge.destination, edge.weight);
    }

    printf("%d\n", totalWeight);
    return 0;
}
