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
// Function to insert a node at the end of the linked list
void insertEnd(struct Node** head, int data) {
    struct Node* newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    struct Node* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
}
// Function to concatenate two linked lists
struct Node* concatenate(struct Node* head1, struct Node* head2) {
    if (head1 == NULL) {
        return head2;
    }
    if (head2 == NULL) {
        return head1;
    }
    struct Node* temp = head1;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = head2;
    return head1;
}
// Function to display the linked list
void display(struct Node* head) {
    struct Node* temp = head;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int main() {
    struct Node* head1 = NULL;
    struct Node* head2 = NULL;

    //  first linked list
    insertEnd(&head1, 11);
    insertEnd(&head1, 22);
    insertEnd(&head1, 33);

    //  the second linked list
    insertEnd(&head2, 10);
    insertEnd(&head2, 50);
    insertEnd(&head2, 60);

    printf("First Linked List: ");
    display(head1);

    printf("Second Linked List: ");
    display(head2);

    struct Node* bigList = concatenate(head1, head2);
    printf("Concatenated Linked List: ");
    display(bigList);

    return 0;
}
