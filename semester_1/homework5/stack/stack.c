#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "stack.h"

typedef struct Stack
{
    char element;
    struct Stack *previous;
} Stack;

StackErrorCode push(Stack **const stack, const char element)
{
    Stack *temp = (Stack *)calloc(1, sizeof(Stack));
    if (temp == NULL)
    {
        return outOfMemory;
    }
    temp->element = element;
    temp->previous = *stack;
    *stack = temp;
    return ok;
}

StackErrorCode pop(Stack **stack)
{
    if (*stack == NULL)
    {
        return stackIsEmpty;
    }

    Stack *temp;
    temp = (*stack)->previous;
    free(*stack);
    (*stack) = temp;
    return ok;
}

char top(Stack *stack, StackErrorCode *errorCode)
{
    if (isEmpty(stack))
    {
        *errorCode = stackIsEmpty;
        return '\0';
    }
    *errorCode = ok;
    return stack->element;
}

bool isEmpty(Stack *stack)
{
    return stack == NULL;
}

StackErrorCode printStack(Stack *stack)
{
    for (const Stack *elem = stack; elem != NULL; elem = elem->previous)
    {
        printf("%c ", elem->element);
    }
    printf("\n");
    return ok;
}

void deleteStack(Stack **stack)
{
    while (!isEmpty(*stack))
    {
        pop(stack);
    }
}
