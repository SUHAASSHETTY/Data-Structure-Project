// finding  the maximum element in a stack
#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100
struct Stack 
{
    int items[MAX_SIZE];
    int top;
};

struct Stack* createStack() {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->top = -1;
    return stack;
}

int isEmpty(struct Stack* stack) {
    return (stack->top == -1);
}

int isFull(struct Stack* stack) {
    return (stack->top == MAX_SIZE - 1);
}

void push(struct Stack* stack, int item) {
    if (isFull(stack)) {
        printf("Stack overflow. Cannot push element.\n");
        return;
    }

    stack->top++;
    stack->items[stack->top] = item;
}

int pop(struct Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack underflow. Cannot pop element.\n");
        return -1;
    }

    int item = stack->items[stack->top];
    stack->top--;
    return item;
}

int getMax(struct Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty. Cannot get maximum.\n");
        return -1;
    }

    return stack->items[stack->top];
}

int main() {
    struct Stack* mainStack = createStack();
    struct Stack* auxStack = createStack();

    push(mainStack, 5);
    push(mainStack, 10);
    push(mainStack, 15);
    push(mainStack, 20);

    printf("Maximum element in the stack: %d\n", getMax(mainStack));

    push(mainStack, 25);
    push(mainStack, 18);
    push(mainStack, 30);

    printf("Maximum element in the stack: %d\n", getMax(mainStack));

    // Free the memory allocated for the stacks
    free(mainStack);
    free(auxStack);

    return 0;
}
