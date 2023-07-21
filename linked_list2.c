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

void insert(struct Node** head, int data) {
    struct Node* newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
    } else {
        struct Node* current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}

struct Node* reverseList(struct Node* head) {
    struct Node* prev = NULL;
    struct Node* current = head;
    struct Node* next = NULL;

    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }

    return prev;
}
// Function to check if a linked list is a palindrome
int isPalindrome(struct Node* head) {
    if (head == NULL || head->next == NULL) {
        return 1; 
    }
    struct Node* slow = head;
    struct Node* fast = head;

    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }

    struct Node* secondHalf = reverseList(slow);
    struct Node* firstHalf = head;
    // Compare the first half with the reversed second half
    while (firstHalf != NULL && secondHalf != NULL) {
        if (firstHalf->data != secondHalf->data) {
            return 0; // Not a palindrome
        }
        firstHalf = firstHalf->next;
        secondHalf = secondHalf->next;
    }

    return 1; // It's a palindrome
}
// Function to display the linked list
void display(struct Node* head) {
    struct Node* current = head;
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

void freeList(struct Node* head) {
    struct Node* current = head;
    while (current != NULL) {
        struct Node* temp = current;
        current = current->next;
        free(temp);
    }
}
int main() {
    struct Node* head = NULL;
    int data, n;

    printf("Enter the number of elements in the linked list: ");
    scanf("%d", &n);

    printf("Enter the elements: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &data);
        insert(&head, data);
    }

    printf("Linked List: ");
    display(head);

    if (isPalindrome(head)) {
        printf("The linked list is a palindrome.\n");
    } else {
        printf("The linked list is not a palindrome.\n");
    }

    // Free the memory allocated for the linked list
    freeList(head);

    return 0;
}
