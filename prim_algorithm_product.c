#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include <math.h>

#define MAX_VERTICES 100

int findMinProductVertex(double product[], bool inMST[], int vertices) {
    double min = INFINITY;
    int minIndex;

    for (int v = 0; v < vertices; v++) {
        if (!inMST[v] && product[v] < min) {
            min = product[v];
            minIndex = v;
        }
    }

    return minIndex;
}

void printMST(int parent[], int graph[MAX_VERTICES][MAX_VERTICES], int vertices) {
    printf("Edge \tWeight\n");
    for (int i = 1; i < vertices; i++) {
        printf("%d - %d \t%d\n", parent[i], i, graph[i][parent[i]]);
    }
}

void primMST(int graph[MAX_VERTICES][MAX_VERTICES], int vertices) {
    int parent[MAX_VERTICES];
    double product[MAX_VERTICES]; 
    bool inMST[MAX_VERTICES] = { false }; 

    for (int i = 0; i < vertices; i++) {
        product[i] = INFINITY;
    }
    product[0] = 1;
    parent[0] = -1;

    for (int count = 0; count < vertices - 1; count++) {
        int u = findMinProductVertex(product, inMST, vertices);
        inMST[u] = true;

        for (int v = 0; v < vertices; v++) {
            if (graph[u][v] && !inMST[v] && graph[u][v] < product[v]) {
                parent[v] = u;
                product[v] = graph[u][v];
            }
        }
    }

    double totalProduct = 1;
    for (int i = 0; i < vertices; i++) {
        totalProduct *= product[i];
    }

    printf("Product of Minimum Product Spanning Tree: %lf\n", totalProduct);
    printMST(parent, graph, vertices);
}

int main() {
    int vertices;

    printf("Enter the number of vertices in the graph: ");
    scanf("%d", &vertices);

    int graph[MAX_VERTICES][MAX_VERTICES];

    printf("Enter the adjacency matrix of the graph:\n");
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            scanf("%d", &graph[i][j]);
        }
    }

    printf("Minimum Product Spanning Tree:\n");
    primMST(graph, vertices);

    return 0;
}
