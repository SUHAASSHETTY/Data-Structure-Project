#include <stdio.h>
#include <stdlib.h>

struct Node 
{
    int data;
    struct Node* next;
};

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Function to insert an element in sorted order in the linked list
void insert_sorted(struct Node** head, struct Node* element) {
    if (*head == NULL || element->data < (*head)->data) {
        element->next = *head;
        *head = element;
    } else {
        struct Node* current = *head;
        while (current->next != NULL && current->next->data <= element->data) {
            current = current->next;
        }
        element->next = current->next;
        current->next = element;
    }
}

void display(struct Node* head) {
    struct Node* temp = head;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int main() {
    struct Node* head = NULL;

    int elements[] = {23,45,10,20,35};

    for (int i = 0; i < sizeof(elements) / sizeof(elements[0]); i++) {
        struct Node* newNode = createNode(elements[i]);
        insert_sorted(&head, newNode);
    }

    printf("Linked List after inserting elements in sorted order: ");
    display(head);

    return 0;
}
