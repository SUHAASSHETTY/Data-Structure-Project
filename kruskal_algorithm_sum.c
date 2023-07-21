#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_VERTICES 100

struct Edge 
{
    int src, dest, weight;
};

struct Graph {
    int vertices;
    int edges;
    struct Edge* edgeList;
};

struct DisjointSet {
    int parent[MAX_VERTICES];
    int rank[MAX_VERTICES];
};

struct Graph* createGraph(int vertices, int edges) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->vertices = vertices;
    graph->edges = edges;

    graph->edgeList = (struct Edge*)malloc(edges * sizeof(struct Edge));
    return graph;
}

struct DisjointSet* createDisjointSet() {
    struct DisjointSet* set = (struct DisjointSet*)malloc(sizeof(struct DisjointSet));
    for (int i = 0; i < MAX_VERTICES; i++) {
        set->parent[i] = i;
        set->rank[i] = 0;
    }
    return set;
}

int compareEdges(const void* a, const void* b) {
    return ((struct Edge*)a)->weight - ((struct Edge*)b)->weight;
}

int findParent(struct DisjointSet* set, int vertex) {
    if (set->parent[vertex] != vertex) {
        set->parent[vertex] = findParent(set, set->parent[vertex]);
    }
    return set->parent[vertex];
}

void unionSets(struct DisjointSet* set, int x, int y) {
    int xRoot = findParent(set, x);
    int yRoot = findParent(set, y);

    if (set->rank[xRoot] < set->rank[yRoot]) {
        set->parent[xRoot] = yRoot;
    } else if (set->rank[xRoot] > set->rank[yRoot]) {
        set->parent[yRoot] = xRoot;
    } else {
        set->parent[yRoot] = xRoot;
        set->rank[xRoot]++;
    }
}

void kruskalMST(struct Graph* graph) {
    struct DisjointSet* set = createDisjointSet();
    struct Edge resultMST[graph->vertices - 1];
    int mstEdges = 0, i = 0, mstWeight = 0;

    
    qsort(graph->edgeList, graph->edges, sizeof(struct Edge), compareEdges);

    while (mstEdges < graph->vertices - 1 && i < graph->edges) {
        struct Edge currentEdge = graph->edgeList[i++];
        int srcParent = findParent(set, currentEdge.src);
        int destParent = findParent(set, currentEdge.dest);

        if (srcParent != destParent) {
            resultMST[mstEdges++] = currentEdge;
            mstWeight += currentEdge.weight;
            unionSets(set, srcParent, destParent);
        }
    }

    printf("Edges in the Minimum Sum Spanning Tree:\n");
    for (int i = 0; i < mstEdges; i++) {
        printf("%d - %d with weight %d\n", resultMST[i].src, resultMST[i].dest, resultMST[i].weight);
    }

    printf("Sum of Minimum Sum Spanning Tree: %d\n", mstWeight);

    free(set);
}
int main() {
    int vertices, edges;

    printf("Enter the number of vertices in the graph: ");
    scanf("%d", &vertices);

    printf("Enter the number of edges in the graph: ");
    scanf("%d", &edges);

    struct Graph* graph = createGraph(vertices, edges);

    printf("Enter edges (source destination weight):\n");
    for (int i = 0; i < edges; i++) {
        scanf("%d %d %d", &graph->edgeList[i].src, &graph->edgeList[i].dest, &graph->edgeList[i].weight);
    }

    kruskalMST(graph);

    free(graph->edgeList);
    free(graph);

    return 0;
}

