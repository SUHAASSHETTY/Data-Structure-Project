#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

struct Graph 
{
    int vertices;
    int** adjMatrix;
};

struct Graph* createGraph(int vertices) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->vertices = vertices;

    graph->adjMatrix = (int**)malloc(vertices * sizeof(int*));
    for (int i = 0; i < vertices; i++) {
        graph->adjMatrix[i] = (int*)calloc(vertices, sizeof(int));
    }

    return graph;
}

void addEdge(struct Graph* graph, int src, int dest) {
    graph->adjMatrix[src][dest] = 1;
    graph->adjMatrix[dest][src] = 1;
}
// Function to perform DFS to detect cycle in the graph
int hasCycleDFS(struct Graph* graph, int currentVertex, int* visited, int parent) {
    visited[currentVertex] = 1;

    for (int i = 0; i < graph->vertices; i++) {
        if (graph->adjMatrix[currentVertex][i]) {
            if (!visited[i]) {
                if (hasCycleDFS(graph, i, visited, currentVertex)) {
                    return 1;
                }
            } else if (i != parent) {
                return 1; 
            }
        }
    }

    return 0; 
}
// Function to detect a cycle in the graph using DFS
int hasCycle(struct Graph* graph) {
    int visited[MAX_VERTICES] = {0};

    for (int i = 0; i < graph->vertices; i++) {
        if (!visited[i]) {
            if (hasCycleDFS(graph, i, visited, -1)) {
                return 1;
            }
        }
    }

    return 0; 
}
int main() {
    int vertices, edges, src, dest;
    printf("Enter the number of vertices: ");
    scanf("%d", &vertices);

    struct Graph* graph = createGraph(vertices);

    printf("Enter the number of edges: ");
    scanf("%d", &edges);

    for (int i = 0; i < edges; i++) {
        printf("Enter edge %d (source destination): ", i + 1);
        scanf("%d %d", &src, &dest);
        addEdge(graph, src, dest);
    }

    if (hasCycle(graph)) {
        printf("The graph contains a cycle.\n");
    } else {
        printf("The graph does not contain a cycle.\n");
    }

    // Free the memory 
    for (int i = 0; i < vertices; i++) {
        free(graph->adjMatrix[i]);
    }
    free(graph->adjMatrix);
    free(graph);

    return 0;
}
