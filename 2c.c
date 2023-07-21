#include <stdio.h>
#include <stdlib.h>

struct ListNode 
{
    int data;
    struct ListNode* next;
};

struct Deque {
    struct ListNode* front; 
    struct ListNode* rear;  
};

struct ListNode* createNode(int data) {
    struct ListNode* newNode = (struct ListNode*)malloc(sizeof(struct ListNode));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void initDeque(struct Deque* deque) {
    deque->front = NULL;
    deque->rear = NULL;
}

void insertFront(struct Deque* deque, int data) {
    struct ListNode* newNode = createNode(data);

    if (deque->front == NULL) {
        deque->front = newNode;
        deque->rear = newNode;
    } else {
        newNode->next = deque->front;
        deque->front = newNode;
    }
}

int deleteRear(struct Deque* deque) {
    if (deque->rear == NULL) {
        printf("Deque is empty.\n");
        return -1;
    }

    int data = deque->rear->data;

    if (deque->front == deque->rear) {
        free(deque->rear);
        deque->front = NULL;
        deque->rear = NULL;
    } else {
        struct ListNode* temp = deque->front;
        while (temp->next != deque->rear) {
            temp = temp->next;
        }
        temp->next = NULL;
        free(deque->rear);
        deque->rear = temp;
    }

    return data;
}

void printDeque(struct Deque* deque) {
    struct ListNode* current = deque->front;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

void freeDeque(struct Deque* deque) {
    struct ListNode* temp;
    while (deque->front != NULL) {
        temp = deque->front;
        deque->front = deque->front->next;
        free(temp);
    }
    deque->rear = NULL;
}

int main() {
    struct Deque deque;
    initDeque(&deque);

    insertFront(&deque, 7);
    insertFront(&deque, 8);
    insertFront(&deque, 10);
    insertFront(&deque, 14);
    insertFront(&deque, 17);

    printf("Deque after insertion at the front: ");
    printDeque(&deque);

    int rearElement = deleteRear(&deque);
    printf("Deleted element from the rear: %d\n", rearElement);

    printf("Deque after deletion from the rear: ");
    printDeque(&deque);

    freeDeque(&deque);

    return 0;
}