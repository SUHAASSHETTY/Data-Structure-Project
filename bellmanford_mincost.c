#include <stdio.h>
#include <stdlib.h>

#define INFINITY 99999

struct Edge 
{
    int u; 
    int v; 
    int w; 
};

struct Graph {
    int V;             
    int E;             
    struct Edge* edge; 
};

void bellmanFord(struct Graph* g, int source);
void display(int arr[], int size);

int main(void) {
    
    struct Graph* g = (struct Graph*)malloc(sizeof(struct Graph));

    
    printf("Enter the number of vertices: ");
    scanf("%d", &g->V);

    
    printf("Enter the number of edges: ");
    scanf("%d", &g->E);

    
    g->edge = (struct Edge*)malloc(g->E * sizeof(struct Edge));

    
    printf("Enter edges (start vertex end vertex weight):\n");
    for (int i = 0; i < g->E; i++) {
        scanf("%d %d %d", &g->edge[i].u, &g->edge[i].v, &g->edge[i].w);
    }

    int source;
    printf("Enter the source vertex: ");
    scanf("%d", &source);

    bellmanFord(g, source);

    return 0;
}

void bellmanFord(struct Graph* g, int source) {
    
    int i, j, u, v, w;
    int tV = g->V;
    int tE = g->E;
    int cost[tV];
    for (i = 0; i < tV; i++)
    {
        cost[i] = INFINITY;
    }

    cost[source] = 0;
    for (i = 1; i <= tV - 1; i++) {
        for (j = 0; j < tE; j++) 
        {
            u = g->edge[j].u;
            v = g->edge[j].v;
            w = g->edge[j].w;

            if (cost[u] != INFINITY && cost[v] > cost[u] + w) {
                cost[v] = cost[u] + w;
            }
        }
    }

    // Print the minimum cost to reach each vertex from the source vertex
    printf("Minimum cost to reach each vertex from the source vertex %d:\n", source);
    display(cost, tV);
}
void display(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("Vertex %d: %d\n", i, arr[i]);
    }
}
