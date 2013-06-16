#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

struct Stack {
    int val;
    struct Stack *next;
};

int peek(struct Stack **head);
int isEmpty(struct Stack **head);

void push(struct Stack **head, int val) {
    struct Stack *newStack = malloc(sizeof(struct Stack));
    newStack->val = val;
    newStack->next = *head;
    *head = newStack;
}

int pop(struct Stack **head) {
    if(!isEmpty(head)) {
        int val = (*head)->val;
        *head = (*head)->next;
        return val;
    } else {
        printf("Trying to pop empty stack\n");
        exit(1);
    }
}

int isEmpty(struct Stack **head) {
    if((*head)->next) {
        return 0;
    } else {
        return 1;
    }
}

void minPush(struct Stack **minStack, struct Stack **head, int val) {
    if(val <= peek(minStack) || isEmpty(minStack)) { //Push onto minStack
        push(minStack, val);
    }
    //Push onto regular stack regardless
    push(head, val); 
}

int minPop(struct Stack **minStack, struct Stack **head) {
    int val = pop(head);
    if(val == peek(minStack)) {
        pop(minStack);
    }
    return val;
}

int peek(struct Stack **head) {
    return (*head)->val;
}

struct Stack *emptyStack() {
    struct Stack *stack = malloc(sizeof(struct Stack));
    struct Stack *nullStack = NULL;
    stack->next = nullStack;
    return stack;
}

int main(int argc, char *argv[]) {
    struct Stack *stack = emptyStack();
    struct Stack *minStack = emptyStack();
    minPush(&minStack, &stack, 5);
    minPush(&minStack, &stack, 7);
    minPush(&minStack, &stack, 1);
    minPush(&minStack, &stack, 3);
    printf("peek: %d, %d\n", peek(&minStack), peek(&stack));
    printf("pop: %d\n", minPop(&minStack, &stack));
    printf("peek: %d, %d\n", peek(&minStack), peek(&stack));
    printf("pop: %d\n", minPop(&minStack, &stack));
    printf("peek: %d, %d\n", peek(&minStack), peek(&stack));
    return 0;
}
