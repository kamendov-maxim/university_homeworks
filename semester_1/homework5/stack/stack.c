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

StackErrorCode pop(Stack ** const stack)
{
    if (isEmpty(*stack))
    {
        return stackIsEmpty;
    }

    Stack *temp = ((*stack)->previous);
    free(*stack);
    (*stack) = temp;
    return ok;
}

char top(Stack *stack, StackErrorCode * const errorCode)
{
    if (isEmpty(stack))
    {
        *errorCode = stackIsEmpty;
        return '\0';
    }
    *errorCode = ok;
    return stack->element;
}

bool isEmpty(const Stack * const stack)
{
    return stack == NULL;
}

StackErrorCode printStack(const Stack * stack)
{
    for (;stack != NULL; stack = stack->previous)
    {
        printf("%c ", stack->element);
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
