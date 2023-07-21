#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

struct Queue 
{
    int items[MAX_VERTICES];
    int front;
    int rear;
};
 
struct Graph {
    int vertices;
    int** adjMatrix;
};

struct Queue* createQueue() {
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    queue->front = -1;
    queue->rear = -1;
    return queue;
}

int isEmpty(struct Queue* queue) {
    return (queue->front == -1);
}

int isFull(struct Queue* queue) {
    return (queue->rear == MAX_VERTICES - 1);
}

void enqueue(struct Queue* queue, int item) {
    if (isFull(queue)) {
        printf("Queue is full. Cannot enqueue.\n");
        return;
    }

    if (isEmpty(queue)) {
        queue->front = 0;
    }

    queue->rear++;
    queue->items[queue->rear] = item;
}

//remove an item from the front of the queue
int dequeue(struct Queue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty. Cannot dequeue.\n");
        return -1;
    }

    int item = queue->items[queue->front];
    if (queue->front == queue->rear) {
        queue->front = -1;
        queue->rear = -1;
    } else {
        queue->front++;
    }

    return item;
}

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

int hasCycle(struct Graph* graph, int startVertex, int* visited) {
    struct Queue* queue = createQueue();
    enqueue(queue, startVertex);
    visited[startVertex] = 1;

    int parent[MAX_VERTICES];
    for (int i = 0; i < graph->vertices; i++) {
        parent[i] = -1;
    }

    while (!isEmpty(queue)) {
        int currentVertex = dequeue(queue);

        for (int i = 0; i < graph->vertices; i++) {
            if (graph->adjMatrix[currentVertex][i]) {
                if (!visited[i]) {
                    enqueue(queue, i);
                    visited[i] = 1;
                    parent[i] = currentVertex;
                } else if (parent[currentVertex] != i) {
                    return 1; 
                }
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

    int visited[MAX_VERTICES] = {0};
    int cycle = 0;

    for (int i = 0; i < graph->vertices; i++) {
        if (!visited[i]) {
            cycle = hasCycle(graph, i, visited);
            if (cycle) {
                break;
            }
        }
    }

    if (cycle) {
        printf("The graph contains a cycle.\n");
    } else {
        printf("The graph does not contain a cycle.\n");
    }

    // Free the memory allocated for the graph
    for (int i = 0; i < vertices; i++) {
        free(graph->adjMatrix[i]);
    }
    free(graph->adjMatrix);
    free(graph);

    return 0;
}
